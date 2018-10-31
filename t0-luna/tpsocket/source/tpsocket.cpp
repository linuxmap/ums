/******************************************************************************
文件实现功能：socket功能封装的主要实现文件
******************************************************************************/
#ifdef _LINUX_
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sched.h>
#include <sys/vfs.h>
#include <linux/sockios.h>
#include <linux/types.h>
#endif //_LINUX_

#include "tpsocket.h"
#include "osp.h"


#define INVALIDU16						0xFFFF

#define UNIFYSOCKETTYPE					u16
#define UNIFYSOCKET_INVALID_TYPE		INVALIDU16
#define UNIFYSOCKET_CONNECT_TYPE		(u16)1
#define UNIFYSOCKET_LISTEN_TYPE			(u16)2
#define UNIFYSOCKET_CLIENT_TYPE			(u16)3
#define UNIFYSOCKET_UDP_TYPE			(u16)4

#define UNIFYSOCKET_INVALIDINDEX			0
#define UNIFYSOCKET_SOCKET_MAX_NUM			(u16)1024
#define UNIFYSOCKET_LISTEN_MAX_NUM			16

#define UNIFYSOCKET_UDPCONNECT_BINDPORT_BEGIN		50000
#define UNIFYSOCKET_UDPCONNECT_BINDPORT_END			55000

//coretask优先级
#define UNIFYSOCKET_CORE_TASKPRI				(u8)70
//coretask堆栈大小
#define UNIFYSOCKET_CORE_STACKSIZE				(u32)(800<<10)

// 2M; SOCKET的发送缓冲大小
#define SOCKET_SEND_BUF                 (1024 * 1024 * 2)
// 2M; SOCKET的接收缓冲大小
#define SOCKET_RECV_BUF                 (1024 * 1024 * 2)

#ifdef _LINUX_
#if !defined(_IOS_PLATFORM_)
#define SOCK_SEND_FLAGS             (int)MSG_NOSIGNAL
#else
#define SOCK_SEND_FLAGS             (int)0
#endif // _IOS_PLATFORM_
typedef socklen_t                   socklen;
#else
#define SOCK_SEND_FLAGS             (int)0
typedef int                         socklen;
#define MAX_MSG_QUEUE_MAX_MSG		1024
#endif //_LINUX_

#define UNIFYSOCKET_RCVDATA_MAX_BUF			16*1024

char  g_achBuf[UNIFYSOCKET_RCVDATA_MAX_BUF+1] = {0};

typedef struct tagTUnifyIpPort
{
	u16			m_wPort;
	u32			m_wIp;

	tagTUnifyIpPort()
	{
		Clear();
	}

	void Clear()
	{
		m_wPort = 0;
		m_wIp = 0;
	}
}TUnifyIpPort;

typedef struct tagTUnifySocketInfo
{
	UNIFYSOCKETTYPE			m_wType;
	SOCKHANDLE				m_hSocket;								

	TUnifyIpPort			m_tIpPort;
	
	CUnifySocketBaseItem*	m_pcSocketItem;
	
	tagTUnifySocketInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wType = UNIFYSOCKET_INVALID_TYPE;
		m_hSocket = INVALID_SOCKET;
		m_tIpPort.Clear();
		m_pcSocketItem = NULL;
	}
	
	BOOL32 IsValid()
	{
		return m_hSocket != INVALID_SOCKET;
	}
	
}TUnifySocketInfo;

//
class CUnifySocketInfoPool
{
public:
	CUnifySocketInfoPool();
	virtual ~CUnifySocketInfoPool();
	
	BOOL32		Init(u16 wArraySize);
	void		Show();
	
	u16			RegistSock(SOCKHANDLE hSock, u32  dwIp, u16 wPort, UNIFYSOCKETTYPE wType, CUnifySocketBaseItem* pItem);
	BOOL32		UnRegistSock(u16 wPoolIndex);
	
	u16			RegistListenSock(SOCKHANDLE hSock, u32 dwIp, u16 wPort, CUnifySocketBaseItem* pItem);
	BOOL32		UnRegistListenSock(u16 wPoolIndex); 
	
	BOOL32					m_bInitOk;
	SEMHANDLE				m_hPoolSemLock;
	u16						m_wArraySize;
	TUnifySocketInfo*		m_ptRegSocketArray;
	TUnifySocketInfo		m_atListenSocketArray[UNIFYSOCKET_LISTEN_MAX_NUM];
};

// socket pool
CUnifySocketInfoPool				g_cSocketInfoPool;

inline u32  MAKEU32( u16 wParam1, u16 wParam2)
{
	return (wParam1 << 16) + wParam2;
}

inline u16 GetParam1( u32 dwParam )
{
	return (u16)(dwParam >> 16);
}

inline u16 GetParam2( u32 dwParam )
{
	return (u16)(dwParam);
}

static s8* GetSocketTypeName(UNIFYSOCKETTYPE wType)
{
	switch(wType)
	{
	case UNIFYSOCKET_CONNECT_TYPE:
		return "connect";
	case UNIFYSOCKET_LISTEN_TYPE:
		return "listen";
	case UNIFYSOCKET_CLIENT_TYPE:
		return "client";
	case UNIFYSOCKET_UDP_TYPE:
		return "udp";
	default:
		break;
	}
	return "invalid";
}

static void UnifyPrintf(const s8* format,... )
{
#define MAX_ONE_LOG_LEN		6000
	s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
	va_list args;
	va_start(args,format);
	u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
	va_end(args);
	if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
	{
		return;
	}
	OspPrintf(1, 0, "%s", abuf);
}

static void UnifyTaskDelay(u32 dwMseconds)
{
	OspDelay(dwMseconds);
}

static u32 UnifyGetTick()
{
#ifdef _MSC_VER
	return GetTickCount();
#endif //_MSC_VER

#ifdef _LINUX_
	struct tms t;
	clock_t ret = times(&t);
	//times always valid!
	if (-1 == ret) {
		ret = 0xffffffff - errno;
	}

	return (u32)ret;
#endif //_LINUX_
	return 0;
}

static u32 UnifyGetTickRate()
{
#ifdef _MSC_VER
	return 1000;
#endif //_MSC_VER

#ifdef _LINUX_
	long ret = sysconf(_SC_CLK_TCK);
	//assert(ret > 0);
	return (u32)ret;
#endif //_LINUX_
	return 0;
}

static u32 UnifyTickToMs(u32 dwTick)
{
#ifdef _MSC_VER
	return dwTick;
#endif // _MSC_VER

#ifdef _LINUX_
	return dwTick * ( 1000 / UnifyGetTickRate());
#endif // _LINUX_
	return 0;
}

static u32 UnifyMsToTick(u32 dwMsCount)
{
#ifdef _MSC_VER
	return dwMsCount;
#endif //_MSC_VER

#ifdef _LINUX_
	u32 dwValue = dwMsCount / ( 1000 / UnifyGetTickRate());
	if ( dwValue == 0 && dwMsCount != 0 )
		dwValue = 1;

	return dwValue;
#endif //_LINUX_
	return 0;
}

static s32 UnifyGetSockError(void)
{
#ifdef _MSC_VER
	return WSAGetLastError ();
#else
	return errno;
#endif // _MSC_VER
	return -1;
}

static BOOL32 UnifySockClose(SOCKHANDLE hSock)
{
	if(hSock == INVALID_SOCKET) {
		return FALSE;
	}

#ifdef _MSC_VER
	return ( 0 == closesocket(hSock) );
#endif //_MSC_VER 

#ifdef _LINUX_
	/* 不准用户关闭标准输入\输出 */
	if(hSock < 3) {
		return FALSE;
	}

	return ( 0 == close(hSock) );
#endif //_LINUX_

	return FALSE;
}

static void UnifySetSockNoBlock(SOCKHANDLE sock)
{
	u32 on = TRUE;

#ifdef _MSC_VER
	ioctlsocket(sock, FIONBIO, (unsigned long *)&on);
#else
	ioctl(sock, FIONBIO, &on);
#endif // _MSC_VER

	return;
}

static SOCKHANDLE UnifyCreateUdpSockBind(u32 dwIP, u16 wPort, BOOL32 bSockReuse = FALSE)
{
	SOCKHANDLE tSock = INVALID_SOCKET;
	SOCKADDR_IN tSvrINAddr;
	u32 optVal = 0;
	
	//Allocate a socket
	tSock = socket(AF_INET, SOCK_DGRAM, 0);
	if(tSock == INVALID_SOCKET) {
		UnifyPrintf("UnifyCreateUdpSockBind create socket failed!\n");
		return INVALID_SOCKET;
	}

	memset( &tSvrINAddr, 0, sizeof(tSvrINAddr) );	
	// set up the local address
	tSvrINAddr.sin_family = AF_INET;
	tSvrINAddr.sin_port = htons(wPort);
	if(dwIP == 0)
		tSvrINAddr.sin_addr.s_addr = INADDR_ANY;
	else
		tSvrINAddr.sin_addr.s_addr = dwIP;

	/*set the sock can reuserd immediated*/
	if(bSockReuse) {
		optVal = 1;
		setsockopt(tSock, SOL_SOCKET, SO_REUSEADDR, (char *)&optVal, sizeof(optVal));
	}
	
	if(bind(tSock, (SOCKADDR *)&tSvrINAddr, sizeof(tSvrINAddr)) == SOCKET_ERROR) {
		UnifyPrintf("UnifyCreateUdpSockBind bind error!\n");
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}

	//设置套接字选项: 设置套接口发送缓冲的大小
	optVal = SOCKET_SEND_BUF;
	int set_result = setsockopt(tSock, SOL_SOCKET, SO_SNDBUF, (char *)&optVal, sizeof(optVal));
	if(set_result == SOCKET_ERROR) {
		UnifyPrintf("UnifyCreateUdpSockBind set sock option fail %d\n", UnifyGetSockError());
	}
	optVal = SOCKET_RECV_BUF;
	set_result = setsockopt(tSock, SOL_SOCKET, SO_RCVBUF, (char *)&optVal, sizeof(optVal));
	if(set_result == SOCKET_ERROR) {
		UnifyPrintf("UnifyCreateUdpSockBind set sock option fail %d\n",  UnifyGetSockError());
	}
	
	//设置sock非阻塞
	UnifySetSockNoBlock(tSock);
	
	UnifyPrintf("Unify: CreateUdpSockBind "UnifyIpForMat"@%d OK!\n", UnifyU32ToIp(dwIP), wPort);
	
	return tSock;
}

static SOCKHANDLE UnifyCreateTcpSockListen(u32 dwIP, u16 wPort, BOOL32 bSockReuse = FALSE)
{
	SOCKHANDLE tSock = INVALID_SOCKET;
	SOCKADDR_IN tSvrINAddr;
	u32 optVal = 0;

	memset( &tSvrINAddr, 0, sizeof(tSvrINAddr) );

	// set up the local address
	tSvrINAddr.sin_family = AF_INET;
	tSvrINAddr.sin_port = htons(wPort);
	if(dwIP == 0)
		tSvrINAddr.sin_addr.s_addr = INADDR_ANY;
	else
		tSvrINAddr.sin_addr.s_addr = dwIP;
	//Allocate a socket
	tSock = socket(AF_INET, SOCK_STREAM, 0);
	if(tSock == INVALID_SOCKET) {
		UnifyPrintf("UnifyCreateTcpSockListen create socket failed! Ip:"UnifyIpForMat", port:%u.\n",
			UnifyU32ToIp(dwIP), wPort);
		return INVALID_SOCKET;
	}

	/*set the sock can reuserd immediated*/
	if(bSockReuse) {
		optVal = 1;
		setsockopt(tSock, SOL_SOCKET, SO_REUSEADDR, (char *)&optVal, sizeof(optVal));
	}

	if(bind(tSock, (SOCKADDR *)&tSvrINAddr, sizeof(tSvrINAddr)) == SOCKET_ERROR) {
		UnifyPrintf("UnifyCreateTcpSockListen bind error! Ip:"UnifyIpForMat", port:%u.\n",
			UnifyU32ToIp(dwIP), wPort);
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}

	if(listen(tSock, 15) == SOCKET_ERROR) { // max 15 waiting connection
		UnifyPrintf("UnifyCreateTcpSockListen can't listen! Ip:"UnifyIpForMat", port:%u.\n",
			UnifyU32ToIp(dwIP), wPort);
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}

	UnifyPrintf("UnifyCreateTcpSockListen "UnifyIpForMat"@%d OK!\n", UnifyU32ToIp(dwIP), wPort);

	return tSock;
}

static SOCKHANDLE UnifyConnectTcpSocket(u32 dwIpv4Addr, u16 wTcpPort, 
	u32 dwTimeOutMs = 0, u32* pdwLocalIP = NULL)
{
	u32 optVal;
	int set_result;
	SOCKHANDLE tSock = INVALID_SOCKET;
	SOCKADDR_IN tSvrINAddr;

	memset(&tSvrINAddr, 0, sizeof(tSvrINAddr));

	/* 准备SERVER地址 */
	tSvrINAddr.sin_family = AF_INET;
	tSvrINAddr.sin_port = htons(wTcpPort);
	tSvrINAddr.sin_addr.s_addr = dwIpv4Addr;

	/* 创建一个 socket */
	tSock = socket(AF_INET, SOCK_STREAM, 0);
	if(tSock == INVALID_SOCKET) {
		UnifyPrintf("Unify: UnifyConnectTcpSocket create socket failed!\n");
		return INVALID_SOCKET;
	}

	UnifyPrintf("Unify: connecting to "UnifyIpForMat"@%d, please wait...\n", UnifyU32ToIp(dwIpv4Addr), wTcpPort);

	/* 连接服务结点 */
#if defined(_MSC_VER)
	int ret;
	//设置非阻塞方式连接
	unsigned long unblock = 1;

	ret = ioctlsocket(tSock, FIONBIO, (unsigned long *)&unblock);
	if(ret == SOCKET_ERROR) {
		UnifyPrintf("Unify: UnifyConnectTcpSocket Set Socket NonBlock Failed!\n");
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}

	ret = connect(tSock, (SOCKADDR *)&tSvrINAddr, sizeof(tSvrINAddr)) ;

	if(ret == SOCKET_ERROR) {
		/* if connect error */
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			UnifyPrintf("Unify: UnifyConnectTcpSocket Connecting Failed!\n");
			UnifySockClose(tSock);
			return INVALID_SOCKET;
		} else {
			struct timeval tTimeVal;
			struct timeval *pTimeVal;
			int bWait;
			fd_set rset, wset, eset;
			int error = 0;
			int len = sizeof(error);

			FD_ZERO(&rset);
			FD_SET(tSock, &rset);

			wset = rset;
			eset = rset;
			if (dwTimeOutMs == 0) {
				pTimeVal = NULL;
			} else {
				tTimeVal.tv_sec = dwTimeOutMs / 1000;
				tTimeVal.tv_usec = (dwTimeOutMs % 1000) * 1000;
				pTimeVal = &tTimeVal;
			}

			bWait = select(tSock + 1, &rset, &wset, &eset, pTimeVal);
			if (bWait <= 0) {
				UnifyPrintf("Unify: UnifyConnectTcpSocket Connect TimeOut!\n");
				UnifySockClose(tSock);
				return INVALID_SOCKET;
			}

			if (getsockopt(tSock, SOL_SOCKET, SO_ERROR, (char *)&error, &len) < 0) {
				UnifyPrintf("Unify: UnifyConnectTcpSocket Get Socket Error !\n");
				UnifySockClose(tSock);
				return INVALID_SOCKET;
			}

			if (error > 0) {
				UnifyPrintf("Unify: UnifyConnectTcpSocket Socket Error %d !\n", error );
				UnifySockClose(tSock);
				return INVALID_SOCKET;
			}
		}
	}


	unblock = 0;

	ret = ioctlsocket(tSock, FIONBIO, (unsigned long *)&unblock);
	if(ret == SOCKET_ERROR) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket Set Socket NonBlock Failed!\n");
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}
#elif defined(_LINUX_)
	int flags;
	int ret;

	flags = fcntl(tSock, F_GETFL, 0);
	if (flags < 0) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket Get Socket Flags Failed!\n");
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}

	if (fcntl(tSock, F_SETFL, flags | O_NONBLOCK) < 0) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket Set Socket NonBlock Failed!\n");
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}

	ret = connect(tSock, (SOCKADDR *)&tSvrINAddr, sizeof(tSvrINAddr)) ;
#ifdef _USE_SELECT_
	if(ret < 0) {
		/* if connect error */
		if (errno != EINPROGRESS) {
			UnifyPrintf("\nUnify: UnifyConnectTcpSocket Connecting Failed!\n");
			UnifySockClose(tSock);
			return INVALID_SOCKET;
		} else {
			struct timeval tTimeVal;
			struct timeval *pTimeVal;
			int bWait;
			fd_set rset, wset;
			int error = 0;
			socklen_t len = sizeof(error);

			FD_ZERO(&rset);
			FD_SET(tSock, &rset);
			wset = rset;
			if (dwTimeOutMs == 0) {
				pTimeVal = NULL;
			} else {
				tTimeVal.tv_sec = dwTimeOutMs / 1000;
				tTimeVal.tv_usec = (dwTimeOutMs % 1000) * 1000;
				pTimeVal = &tTimeVal;
			}

			bWait = select(tSock + 1, &rset, &wset, NULL, pTimeVal);
			if (bWait <= 0) {
				UnifyPrintf("\nUnify: UnifyConnectTcpSocket Connect TimeOut!\n");
				UnifySockClose(tSock);
				return INVALID_SOCKET;
			}

			if (getsockopt(tSock, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
				UnifyPrintf("\nUnify: UnifyConnectTcpSocket Get Socket Error !\n");
				UnifySockClose(tSock);
				return INVALID_SOCKET;
			}

			if (error > 0) {
				UnifyPrintf("\nUnify: UnifyConnectTcpSocket Get Socket Error %d\n", error);
				UnifySockClose(tSock);
				return INVALID_SOCKET;
			}
		}
	}
#endif//_USE_SELECT_
#ifdef _USE_EPOLL_
	if (ret < 0) { /* if connect error */
		if (errno != EINPROGRESS) {
			UnifyPrintf("\nUnify: UnifyConnectTcpSocket Connecting Failed!\n");
			UnifySockClose(tSock);
			return INVALID_SOCKET;
		} else {
			int epfd, nfds;
			struct epoll_event ev, events[2];
			epfd = epoll_create(2);
			ev.data.fd = tSock;
			ev.events = EPOLLOUT;
			epoll_ctl(epfd, EPOLL_CTL_ADD, tSock, &ev);
			if (dwTimeOutMs == 0)
				dwTimeOutMs = 30 * 1000;
			nfds = epoll_wait(epfd, events, 2, dwTimeOutMs);
			if (nfds <= 0) {
				UnifyPrintf("\nUnify: UnifyConnectTcpSocket Connect TimeOut!\n");
				UnifySockClose(tSock);
				UnifySockClose(epfd);
				return INVALID_SOCKET;
			}
			//需要继续判断是否connect 成功.
			struct sockaddr_in tLocalAddr;
			s32 dwAddrLen = sizeof(struct sockaddr_in);
			if (0 != getpeername(tSock, (struct sockaddr *)&tLocalAddr,
				(socklen_t *) (&dwAddrLen))) {
					UnifyPrintf("\nUnify: UnifyConnectTcpSocket Error :%s\n",
						strerror(errno));
					UnifySockClose(tSock);
					UnifySockClose(epfd);
					return INVALID_SOCKET;
			}

			UnifySockClose(epfd);

		}
	}
#endif//_USE_EPOLL_
	if (fcntl(tSock, F_SETFL, flags) < 0) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket ReSet Socket Block failed!\n");
		UnifySockClose(tSock);
		return INVALID_SOCKET;
	}
#endif//defined(_MSC_VER)

#ifdef _LINUX_
	// 获取当前连接所用的IP地址
	if (pdwLocalIP != NULL) {
		struct sockaddr_in tClientAddr;
		int length = sizeof(tClientAddr);
		if (getsockname(tSock, (struct sockaddr *)&tClientAddr, (socklen_t *)&length) == 0) {
			*pdwLocalIP = (u32) tClientAddr.sin_addr.s_addr;
		}
	}
#else
	// 获取当前连接所用的IP地址
	if (pdwLocalIP != NULL) {
		struct sockaddr_in tClientAddr;
		int length = sizeof(tClientAddr);
		if (getsockname(tSock, (struct sockaddr *)&tClientAddr, &length) == 0) {
			*pdwLocalIP = (u32) tClientAddr.sin_addr.s_addr;
		}
	}
#endif//_LINUX_

	/* 设置套接字选项: 立即发送(不采用任何避免竞争的算法) */
	optVal = 1;
	set_result = setsockopt(tSock, IPPROTO_TCP, TCP_NODELAY, (char *)&optVal, sizeof(optVal));
	if(set_result == SOCKET_ERROR) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket set sock option fail  %d\n", UnifyGetSockError());
	}

	/* 设置套接字选项: 设置套接口发送缓冲的大小 */
	optVal = SOCKET_SEND_BUF;
	set_result = setsockopt(tSock, SOL_SOCKET, SO_SNDBUF, (char *)&optVal, sizeof(optVal));
	if(set_result == SOCKET_ERROR) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket set sock option fail  %d\n", UnifyGetSockError());
	}
	optVal = SOCKET_RECV_BUF;
	set_result = setsockopt(tSock, SOL_SOCKET, SO_RCVBUF, (char *)&optVal, sizeof(optVal));
	if(set_result == SOCKET_ERROR) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket set sock option fail  %d\n",  UnifyGetSockError());
	}

	/* 设置套接字选项: 启用TCP连接检测功能 */
	optVal = 1;
	set_result = setsockopt(tSock, SOL_SOCKET, SO_KEEPALIVE, (char *)&optVal, sizeof(optVal));
	if(set_result == SOCKET_ERROR ) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket set sock option fail, errno %d\n", UnifyGetSockError());
	}

	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;

	set_result = setsockopt(tSock, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));
	if (set_result == SOCKET_ERROR) {
		UnifyPrintf("\nUnify: UnifyConnectTcpSocket set sock option fail, errno %d\n", UnifyGetSockError());
	}

	// #ifdef _LINUX_ 
	// 	u32 optVal = 1;
	// 	// 与BSD系统兼容
	// 	setsockopt (tSock, SOL_SOCKET, SO_BSDCOMPAT, (char*)&optVal, sizeof (optVal));
	// #endif//_LINUX_

	UnifyPrintf("Unify: connecting to "UnifyIpForMat"@%d ok!\n", UnifyU32ToIp(dwIpv4Addr), wTcpPort);

	return tSock;
}

static BOOL32 UnifySockRecv(SOCKHANDLE tSock, char* pchBuf, u32 dwLen, u32* puRcvLen)
{
	int ret = SOCKET_ERROR;

	if ((tSock == INVALID_SOCKET) || (pchBuf == NULL)) {
		return FALSE;
	}

	if (puRcvLen != NULL)
		*puRcvLen = 0;

	// 接收数据大小若为零，则立即返回；
	// 否则，会导致recv也返回零，导致语义冲突
	if (dwLen == 0) {
		return TRUE;
	}

	while (1) {
		ret = recv(tSock, pchBuf, dwLen, 0);

		if (ret > 0) {
			if (puRcvLen != NULL)
				*puRcvLen = (u32) ret;
			return TRUE;
		} else if (!ret) {
			UnifyPrintf("UnifySockRecvt %d peer shutdown send!\n", tSock);
			break;
		} else {
			int err = UnifyGetSockError();
#ifdef _LINUX_
			if (err == EINTR)
				continue;
#endif //_LINUX_
			UnifyPrintf("UnifySockRecv receive error, errno %d!\n", err);
			break;
		}
	}

	return FALSE;
}

static BOOL32 UnifySockRecvFrom( SOCKHANDLE tSock, char* pchBuf, u32 dwLen, u32* puRcvLen, u32* pdwSrcIp, u16* pwSrcPort )
{
	int ret = SOCKET_ERROR;

	if ((tSock == INVALID_SOCKET) || (pchBuf == NULL)) {
		return FALSE;
	}

	if (puRcvLen != NULL)
		*puRcvLen = 0;

	if (pdwSrcIp != NULL)
		*pdwSrcIp = 0;

	if (pwSrcPort != NULL)
		*pwSrcPort = 0;

	// 接收数据大小若为零，则立即返回；
	// 否则，会导致recv也返回零，导致语义冲突
	if (dwLen == 0) {
		return TRUE;
	}

	SOCKADDR_IN tAddr;
	socklen nAddrLen = sizeof(SOCKADDR);
	memset( &tAddr, 0, sizeof(tAddr) );

	while (1) {
		ret = recvfrom(tSock, pchBuf, dwLen, 0, (SOCKADDR *)&tAddr, &nAddrLen);

		if (ret > 0) {
			if (puRcvLen != NULL)
				*puRcvLen = (u32) ret;
			if (pdwSrcIp != NULL)
				*pdwSrcIp = tAddr.sin_addr.s_addr;
			if (pwSrcPort != NULL)
				*pwSrcPort = ntohs(tAddr.sin_port);
			return TRUE;
		} else if (!ret) {
			UnifyPrintf("UnifySockRecvFrom %d peer shutdown send!\n", tSock);
			break;
		} else {
			int err = UnifyGetSockError();
#ifdef _LINUX_
			if (err == EINTR)
				continue;
#endif //_LINUX_
			UnifyPrintf("UnifySockRecvFrom receive error, errno %d!\n", err);
			break;
		}
	}

	return FALSE;
}

static BOOL32 UnifySockSend(SOCKHANDLE tSock, const char* pchBuf, u32 dwLen)
{
	int ret = SOCKET_ERROR;
	u32 nTotalSendLen;
	int nTryNum, nErrNo;

	if((tSock == INVALID_SOCKET) || (pchBuf == NULL)) {
		return FALSE;
	}

	nTotalSendLen = 0;
	while (nTotalSendLen < dwLen) {
		nTryNum = 0;

		//发送失败原因为底层没有Buf时，要重新尝试发送3次
		while (nTryNum < 3) {
			ret = send(tSock, (char *)(pchBuf + nTotalSendLen), dwLen - nTotalSendLen, SOCK_SEND_FLAGS);
			if (ret == SOCKET_ERROR) {
			    nErrNo = UnifyGetSockError();
#ifdef _LINUX_
				if (nErrNo != EINTR)
					nTryNum++;

				continue;
#endif //_LINUX_
#ifdef _MSC_VER
				if (nErrNo != WSAENOBUFS)
					break;
				nTryNum++;
				UnifyTaskDelay(50);
#endif //_MSC_VER
			} else {
				break;
			}
		}

		if (ret == SOCKET_ERROR) {
			return FALSE;
		} else
			nTotalSendLen += ret;
	}
	return TRUE;
}

static BOOL32 UnifySockSendByTimeOut(SOCKHANDLE tSock, const char* pchBuf, u32 dwLen, u32 dwCurTick, u32 dwNodeId)
{
	int ret = SOCKET_ERROR;
	int nTotalSendLen = 0;

	if ((tSock == INVALID_SOCKET) || (pchBuf == NULL)) {
		return FALSE;
	}

#ifdef _MSC_VER
	while( (u32)nTotalSendLen < dwLen ) {
		//发送失败原因为底层没有Buf时，要重新尝试发送3次
		for(int nTryNum = 0; nTryNum < 3; nTryNum++) {
			int nErrNo;
    			ret = send(tSock, (char *)(pchBuf + nTotalSendLen), (dwLen - nTotalSendLen), SOCK_SEND_FLAGS);

			if(ret != SOCKET_ERROR)
				break;

			nErrNo = WSAGetLastError();
			if (nErrNo == WSAECONNRESET)
				return FALSE;

			else if(nErrNo != WSAENOBUFS) {
				UnifyPrintf("Unify: UnifySockSendByTimeOut node(%d) sock send error, currtick:%u, errno:%d.\n", dwNodeId, dwCurTick, nErrNo);
				return FALSE;
			}

			UnifyTaskDelay(50);

		}
		nTotalSendLen += ret;
	}
#else
	//超时时间固定为5秒
	const u32 MAX_SEND_TIMEOUT = 5000;
    int nTryNum, nErrNo;
	u32 dwSendTimeOut = UnifyGetTick() + UnifyMsToTick(MAX_SEND_TIMEOUT);
    nTotalSendLen = 0;
	nTryNum = 3;
	/*
	 * 每次发送后, 判断是否发完, 发完直接退出, 如果发送失败,
	 * 判断错误码是否为EINTR, 如果不是, 累计3次错误强行退出
	 */
	while (nTotalSendLen < dwLen) {
		ret = send(tSock, (char *)(pchBuf + nTotalSendLen), dwLen - nTotalSendLen, SOCK_SEND_FLAGS);

		if (ret >= 0) {
			nTotalSendLen += ret;
			continue;
		}

		if (UnifyGetSockError() != EINTR && !(--nTryNum))
			break;

		continue;
	}

	if (nTotalSendLen < dwLen) {
		if (UnifyGetTick() > dwSendTimeOut)
			// 不能超过一个包发送的时间
			UnifyPrintf("Unify: UnifySockSendByTimeOut node(%d) send TimeOut, PackLen:%d, currtick:%u, errno:%d.\n", 
			dwNodeId, dwLen, dwCurTick, UnifyGetSockError());
		return FALSE;
	}
#endif//_MSC_VER
	return TRUE;
}

static BOOL32 UnifySockSendTo( SOCKHANDLE tSock, const char* pchBuf, u32 dwLen, u32 dwDstIp, u16 wDstPort )
{
	int ret = SOCKET_ERROR;
	u32 nTotalSendLen;
	int nTryNum, nErrNo;
	
	if((tSock == INVALID_SOCKET) || (pchBuf == NULL)
		|| (0 == dwDstIp) || (0 == wDstPort)) {
		return FALSE;
	}
	
	SOCKADDR_IN UdpSockAddr;
	memset( &UdpSockAddr, 0, sizeof(UdpSockAddr) );
	UdpSockAddr.sin_family = AF_INET;
	UdpSockAddr.sin_addr.s_addr = dwDstIp;
	UdpSockAddr.sin_port = htons(wDstPort);

	nTotalSendLen = 0;
	while (nTotalSendLen < dwLen) {
		nTryNum = 0;
		
		//发送失败原因为底层没有Buf时，要重新尝试发送3次
		while (nTryNum < 3) {
			ret =  sendto(tSock, (char *)(pchBuf + nTotalSendLen), dwLen - nTotalSendLen, SOCK_SEND_FLAGS, (SOCKADDR *)&UdpSockAddr, sizeof(SOCKADDR));
			if (ret == SOCKET_ERROR) {
				nErrNo = UnifyGetSockError();
#ifdef _LINUX_
				if (nErrNo != EINTR)
					nTryNum++;
				
				continue;
#endif //_LINUX_
#ifdef _MSC_VER
				if (nErrNo != WSAENOBUFS)
					break;
				nTryNum++;
				UnifyTaskDelay(50);
#endif //_MSC_VER
			} else {
				break;
			}
		}
		
		if (ret == SOCKET_ERROR) {
			return FALSE;
		} else
			nTotalSendLen += ret;
	}
	return TRUE;
}



#ifdef _USE_EPOLL_

int		g_nEpollFd = -1;
u32		g_dwMaxEpollFdNum = 0;

static BOOL32 CreatEpollFd(u32 dwNum)
{//创建epoll文件描述符
	g_nEpollFd = epoll_create(dwNum);
	if (-1 == g_nEpollFd) {
		UnifyPrintf("[unifysocket] CreatEpollFd: epoll_create failed num(%u)errno(%d)(%s).\n",dwNum, errno, strerror(errno));
		return FALSE;
	}
	return TRUE;
}

static BOOL32 AddEpollFd(SOCKHANDLE hSock, u32 dwUserParam)
{//join in epoll set
	epoll_event tEpollEvent;
	u64 qdwUserParam = 0;
	memset(&tEpollEvent, 0, sizeof(epoll_event));
	tEpollEvent.events = EPOLLIN | EPOLLPRI;
	qdwUserParam = dwUserParam;
	tEpollEvent.data.u64 = (qdwUserParam << 32) + hSock;
	if (0 != epoll_ctl(g_nEpollFd, EPOLL_CTL_ADD, hSock, &tEpollEvent)) {
		UnifyPrintf("[unifysocket] AddEpollFd: epoll_ctl add socket failed! sock(%d)errno(%d)(%s).",
			hSock, errno, strerror(errno));
		return FALSE;
	}
//	UnifyPrintf("addepollfd hSock:%u, dwUserParam:%u.\n", hSock, dwUserParam);
	return TRUE;
}

static BOOL32 DelEpollFd(SOCKHANDLE hSock)
{
	//从epoll中删除对应的sock
	epoll_event tEpollEvent;
	tEpollEvent.events = EPOLLIN | EPOLLPRI;
	// 对于EPOLL_CTL_DEL 最后一个参数 epoll_event可以为NULL , 此处为兼容linux2.6以前版本
	if (0 != epoll_ctl(g_nEpollFd, EPOLL_CTL_DEL, hSock, &tEpollEvent)) {
		UnifyPrintf("[unifysocket] DelEpollFd: epoll_ctl del socket failed! sock(%d)errno(%d)(%s).\n", hSock, errno, strerror(errno));
	}
}

#endif//_USE_EPOLL_

// task
#ifdef _LINUX_
void* UnifySocketCoreTask(void* pParam); 
#else
u32 UnifySocketCoreTask(void* pParam); 
#endif

#define		INNERUDP_BIND_IP	"127.0.0.1"

SOCKHANDLE	g_hInnerUdpSocket = INVALID_SOCKET;
u32			g_dwInnerUdpIp = 0;
u16			g_wInnerUdpPort = 0;

static void AwakeCoreTask()
{
	if (INVALID_SOCKET != g_hInnerUdpSocket)
	{
		s8 buf[]="wake up!";
		UnifySockSendTo(g_hInnerUdpSocket, buf, strlen(buf), g_dwInnerUdpIp, g_wInnerUdpPort);
	}
}

TPSOCKET_API BOOL32 UnifySocketMoudleInit(u16 wInnerUdpPort)
{
	static int falg = 0;
	if (1 == falg)
	{
		return TRUE;
	}

	SockInit();

	g_dwInnerUdpIp = inet_addr(INNERUDP_BIND_IP);

	g_hInnerUdpSocket = UnifyCreateUdpSockBind(g_dwInnerUdpIp, wInnerUdpPort);
	if (INVALID_SOCKET == g_hInnerUdpSocket)
	{
		UnifyPrintf("[unifysocket] UnifySocketMoudleInit failed! wInnerUdpPort:%d.\n", 
			wInnerUdpPort);
		return FALSE;
	}
	g_wInnerUdpPort = wInnerUdpPort;

	if (!g_cSocketInfoPool.Init(UNIFYSOCKET_SOCKET_MAX_NUM))
	{
		return FALSE;
	}

#ifdef _USE_EPOLL_
	g_dwMaxEpollFdNum = (u32)(UNIFYSOCKET_LISTEN_MAX_NUM+UNIFYSOCKET_SOCKET_MAX_NUM);
	if (!CreatEpollFd(g_dwMaxEpollFdNum))
	{
		return FALSE;
	}
#endif//_USE_EPOLL_

	if (!OspTaskCreate(UnifySocketCoreTask, "UnifySocketCoreTask", 
		UNIFYSOCKET_CORE_TASKPRI, 
		UNIFYSOCKET_CORE_STACKSIZE,
		0,
		NULL))
	{
		return FALSE;
	}

	falg = 1;
	return TRUE;
}

TPSOCKET_API void UnifySocketPoolShow()
{
	UnifyPrintf("[tpsocket compile time: %s, %s.]\n", __DATE__, __TIME__);
#ifdef _USE_EPOLL_
	UnifyPrintf("[tpsocket] Use Epoll mode, g_hInnerUdpSocket:%u, g_dwInnerUdpIp:"UnifyIpForMat", g_wInnerUdpPort:%d!\n", 
		g_hInnerUdpSocket, UnifyU32ToIp(g_dwInnerUdpIp), g_wInnerUdpPort);
#endif//_USE_EPOLL_
#ifdef _USE_SELECT_
	UnifyPrintf("[tpsocket] Use Select mode, g_hInnerUdpSocket:%u, g_dwInnerUdpIp:"UnifyIpForMat", g_wInnerUdpPort:%d!\n", 
		g_hInnerUdpSocket, UnifyU32ToIp(g_dwInnerUdpIp), g_wInnerUdpPort);
#endif//_USE_SELECT_
	g_cSocketInfoPool.Show();
}

// 每行输出消息内容的16个字节
#define DUMPMSG_BUF_LEN_FOR_LINE			16
// 缺省输出的行数
#define DUMPMSG_BUF_LINES	                64

#define DUMPMSG_MAX_MSG_LEN					6000

static char g_achDumpBuf[DUMPMSG_MAX_MSG_LEN+1] = {0};

TPSOCKET_API void UnifySocketDumpMsg( const char* buf, u16 wLen, CBMsgPrintf pcbPrintFun /*= NULL*/ )
{
	if (NULL == buf)
	{
		if (NULL == pcbPrintFun)
		{
			UnifyPrintf("[DumpMsg] Buf is null!\n");
		}
		else
		{
			pcbPrintFun("[DumpMsg] Buf is null!\n");
		}
		return;
	}
	memset(g_achDumpBuf, 0, DUMPMSG_MAX_MSG_LEN+1);
	u16 wPrintLen = 0;
	wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "[DumpMsg][Begin][Len:%d].\n", wLen);

	u16 wIndex = 0;
	int iChar = 0; // used for char print
	u32 iBlank = 0;
	u32 iBCount = 0;
	BOOL32 bPrintAll = TRUE;
	for (wIndex = 0; wIndex < wLen; wIndex++ , buf++)
	{
		if (wIndex>=DUMPMSG_BUF_LEN_FOR_LINE*DUMPMSG_BUF_LINES)
		{
			bPrintAll = FALSE;
			break;
		}

		/* 每16个u8为一行 */
		if( (wIndex & 0x0F) == 0 ) {
			wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "%4dh: ", wIndex/16+1);
		}

		wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "%.2X ", (u8)*buf);
		if( ((wIndex + 1) & 0x0F) == 0 ) {
			wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "; "); // 每输出16个u8，打印该行的字符提示
			for(iChar = 15; iChar >= 0; iChar--) {
				if( ((*(buf - iChar)) >= 0x21) && ((*(buf - iChar)) <= 0x7E) ) { // 可打印字符(32空格,33-126)
					wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "%1c", *(buf - iChar));
				} else { // 不可打印字符
					wPrintLen += sprintf(g_achDumpBuf + wPrintLen, ".");
				}
			}
			if (wIndex != (wLen-1))
			{// 最后一行，不输出换行
				wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "\n");
			}
		}

		if( (wIndex == (wLen - 1)) && (((wIndex + 1) & 0x0F) != 0) ) { // 最后一行
			iBlank = 16 - ((wIndex + 1) & 0x0F);
			for(iBCount = 0; iBCount < iBlank; iBCount++) { // print black space
				wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "   ");
			}

			wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "; ");
			for(iChar = (wIndex & 0x0F); iChar >= 0; iChar--) { // print the char
				if(((*(buf - iChar)) >= 0x21) && ((*(buf - iChar)) <= 0x7e)) {
					wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "%1c", *(buf - iChar));
				} else {
					wPrintLen += sprintf(g_achDumpBuf + wPrintLen, ".");
				}
			}  //end for
		} //end if

	}

	if (bPrintAll)
	{
		wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "\n[DumpMsg][End].\n");
	}
	else
	{
		wPrintLen += sprintf(g_achDumpBuf + wPrintLen, "%4dh: Msg is too long, can't dump more!\n[DumpMsg][End].\n", DUMPMSG_BUF_LINES+1);
	}

	if (NULL == pcbPrintFun)
	{
		UnifyPrintf("%s", g_achDumpBuf);
	}
	else
	{
		pcbPrintFun("%s", g_achDumpBuf);
	}

	return;
}

/////////////////////////////////////////////////////////////////
CUnifySocketBaseItem::CUnifySocketBaseItem(u32 dwUserParam /*= 0*/ )
:m_bUsed(FALSE)
,m_dwUserParam(dwUserParam)
{	
}

CUnifySocketBaseItem::~CUnifySocketBaseItem()
{
	m_bUsed = FALSE;
	m_dwUserParam = 0;
}

/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
CUnifySocketInfoPool::CUnifySocketInfoPool()
{
	m_bInitOk = FALSE;
	m_hPoolSemLock = NULL;
	m_wArraySize = 0;
	m_ptRegSocketArray = NULL;
}

CUnifySocketInfoPool::~CUnifySocketInfoPool()
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < UNIFYSOCKET_LISTEN_MAX_NUM; wIndex++)
	{
		m_atListenSocketArray[wIndex].Clear();
	}
	if (NULL != m_ptRegSocketArray)
	{
		for (wIndex = 0; wIndex < m_wArraySize; wIndex++)
		{
			m_ptRegSocketArray[wIndex].Clear();
		}
		delete [] m_ptRegSocketArray;
		m_ptRegSocketArray = NULL;
		m_wArraySize = 0;
	}
	if (NULL != m_hPoolSemLock)
	{
		OspSemDelete(m_hPoolSemLock);
		m_hPoolSemLock = NULL;
	}
	m_bInitOk = FALSE;
}

BOOL32 CUnifySocketInfoPool::Init( u16 wArraySize )
{
	if (wArraySize > UNIFYSOCKET_SOCKET_MAX_NUM || wArraySize == 0)
	{
		return FALSE;
	}

	if (!OspSemBCreate(&m_hPoolSemLock))
	{
		return FALSE;
	}

	m_ptRegSocketArray = new TUnifySocketInfo[wArraySize];
	if (NULL == m_ptRegSocketArray)
	{
		OspSemDelete(m_hPoolSemLock);
		m_hPoolSemLock = NULL;
		return FALSE;
	}
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < wArraySize; wIndex++)
	{
		m_ptRegSocketArray[wIndex].Clear();
	}
	m_wArraySize = wArraySize;

	for (wIndex = 0; wIndex < UNIFYSOCKET_LISTEN_MAX_NUM; wIndex++)
	{
		m_atListenSocketArray[wIndex].Clear();
	}
	m_bInitOk = TRUE;
	return TRUE;
}

void CUnifySocketInfoPool::Show()
{
	UnifyPrintf("[unifysocket] CUnifySocketInfoPool Info:\n");
	UnifyPrintf("  m_bInitOk=%d.\n", m_bInitOk);
	UnifyPrintf("  m_wArraySize=%d.\n", m_wArraySize);
	
	u16 wIndex = 0;
	TUnifySocketInfo* ptInfo;

	UnifyPrintf("  m_ptRegSocketArray::\n");
	for (wIndex = 0; wIndex < m_wArraySize; wIndex++)
	{
		ptInfo = &m_ptRegSocketArray[wIndex];
		if (ptInfo->IsValid())
		{
			UnifyPrintf("    wIndex:%d, socket type:%d-%s, socket:%d, ip:"UnifyIpForMat", port:%d, item:%p.\n",
				wIndex+1, ptInfo->m_wType, GetSocketTypeName(ptInfo->m_wType), ptInfo->m_hSocket, 
				UnifyU32ToIp(ptInfo->m_tIpPort.m_wIp), ptInfo->m_tIpPort.m_wPort, ptInfo->m_pcSocketItem);
		}
	}

	UnifyPrintf("  m_atListenSocketArray::\n");
	for (wIndex = 0; wIndex < UNIFYSOCKET_LISTEN_MAX_NUM; wIndex++)
	{
		ptInfo = &m_atListenSocketArray[wIndex];
		if (ptInfo->IsValid())
		{
			UnifyPrintf("    wIndex:%d, socket type:%d-%s, socket:%d, ip:"UnifyIpForMat", port:%d, item:%p.\n",
				wIndex+1, ptInfo->m_wType, GetSocketTypeName(ptInfo->m_wType), ptInfo->m_hSocket, 
				UnifyU32ToIp(ptInfo->m_tIpPort.m_wIp), ptInfo->m_tIpPort.m_wPort, ptInfo->m_pcSocketItem);
		}
	}

	UnifyPrintf("\n");
}

u16 CUnifySocketInfoPool::RegistSock( SOCKHANDLE hSock, u32 dwIp, u16 wPort, UNIFYSOCKETTYPE wType, CUnifySocketBaseItem* pItem )
{
	if (!m_bInitOk || INVALID_SOCKET == hSock || NULL == pItem)
	{
		return UNIFYSOCKET_INVALIDINDEX;
	}

	OspSemTake(m_hPoolSemLock);
	static u16 wFindIndex = 0;
	for (u16 wIndex = 0; wIndex < m_wArraySize; wIndex++)
	{
		wFindIndex++;
		wFindIndex = wFindIndex % (m_wArraySize+1);
		if (0 == wFindIndex)
		{
			wFindIndex = 1;
		}
		if (!m_ptRegSocketArray[wFindIndex-1].IsValid())
		{
#ifdef _USE_EPOLL_
			u32 dwUserParam = MAKEU32(wType, wFindIndex-1);
			AddEpollFd(hSock, dwUserParam);
#endif//_USE_EPOLL_
			m_ptRegSocketArray[wFindIndex-1].m_wType = wType;
			m_ptRegSocketArray[wFindIndex-1].m_hSocket = hSock;
			m_ptRegSocketArray[wFindIndex-1].m_tIpPort.m_wIp = dwIp;
			m_ptRegSocketArray[wFindIndex-1].m_tIpPort.m_wPort = wPort;
			m_ptRegSocketArray[wFindIndex-1].m_pcSocketItem = pItem;
			
			OspSemGive(m_hPoolSemLock);
			return wFindIndex;
		}
	}

	OspSemGive(m_hPoolSemLock);
	return UNIFYSOCKET_INVALIDINDEX;
}

BOOL32 CUnifySocketInfoPool::UnRegistSock( u16 wPoolIndex )
{
	wPoolIndex = wPoolIndex - 1; // 真正的数组索引需要减1
	if (wPoolIndex >= m_wArraySize)
	{
		return FALSE;
	}

	OspSemTake(m_hPoolSemLock);

	if (m_ptRegSocketArray[wPoolIndex].m_hSocket != INVALID_SOCKET)
	{
#ifdef _USE_EPOLL_
		DelEpollFd(m_ptRegSocketArray[wPoolIndex].m_hSocket);
#endif//_USE_EPOLL_
		UnifySockClose(m_ptRegSocketArray[wPoolIndex].m_hSocket);
		m_ptRegSocketArray[wPoolIndex].m_hSocket = INVALID_SOCKET;
	}
	m_ptRegSocketArray[wPoolIndex].Clear();

	OspSemGive(m_hPoolSemLock);
	return TRUE;
}

u16 CUnifySocketInfoPool::RegistListenSock(SOCKHANDLE hSock, u32 dwIp, u16 wPort, CUnifySocketBaseItem* pItem)
{
	if (!m_bInitOk || INVALID_SOCKET == hSock || NULL == pItem)
	{
		return UNIFYSOCKET_INVALIDINDEX;
	}
	
	OspSemTake(m_hPoolSemLock);
	
	static u16 wFindIndex = 0;
	for (u16 wIndex = 0; wIndex < UNIFYSOCKET_LISTEN_MAX_NUM; wIndex++)
	{
		wFindIndex++;
		wFindIndex = wFindIndex % (m_wArraySize+1);
		if (0 == wFindIndex)
		{
			wFindIndex = 1;
		}
		if (!m_atListenSocketArray[wFindIndex-1].IsValid())
		{
#ifdef _USE_EPOLL_
			u32 dwUserParam = MAKEU32(UNIFYSOCKET_LISTEN_TYPE, wFindIndex-1);
			AddEpollFd(hSock, dwUserParam);
#endif//_USE_EPOLL_
			m_atListenSocketArray[wFindIndex-1].m_wType = UNIFYSOCKET_LISTEN_TYPE;
			m_atListenSocketArray[wFindIndex-1].m_hSocket = hSock;
			m_atListenSocketArray[wFindIndex-1].m_tIpPort.m_wIp = dwIp;
			m_atListenSocketArray[wFindIndex-1].m_tIpPort.m_wPort = wPort;
			m_atListenSocketArray[wFindIndex-1].m_pcSocketItem = pItem;
			
			OspSemGive(m_hPoolSemLock);
			return wFindIndex;
		}
	}
	
	OspSemGive(m_hPoolSemLock);
	return UNIFYSOCKET_INVALIDINDEX;
}

BOOL32 CUnifySocketInfoPool::UnRegistListenSock( u16 wPoolIndex )
{
	wPoolIndex = wPoolIndex - 1; // 真正的数组索引需要减1
	if (wPoolIndex >= UNIFYSOCKET_LISTEN_MAX_NUM)
	{
		return FALSE;
	}
	
	OspSemTake(m_hPoolSemLock);
	
	if (m_atListenSocketArray[wPoolIndex].m_hSocket != INVALID_SOCKET)
	{
#ifdef _USE_EPOLL_
		DelEpollFd(m_atListenSocketArray[wPoolIndex].m_hSocket);
#endif//_USE_EPOLL_
		UnifySockClose(m_atListenSocketArray[wPoolIndex].m_hSocket);
		m_atListenSocketArray[wPoolIndex].m_hSocket = INVALID_SOCKET;
	}
	m_atListenSocketArray[wPoolIndex].Clear();
	
	OspSemGive(m_hPoolSemLock);
	return TRUE;
}
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
#ifdef _USE_SELECT_

u32	g_dwSlectNum = 0;
u32 g_dwMaxSocket = 0;

void UnifySocketSelectFdSet(fd_set *ptSet)
{
	u32 i = 0;
	g_dwSlectNum = 0;
	FD_ZERO(ptSet);

	u16 wIndex = 0;

	FD_SET(g_hInnerUdpSocket, ptSet);
	g_dwSlectNum++;
	g_dwMaxSocket = g_hInnerUdpSocket;

	for (wIndex = 0; wIndex < UNIFYSOCKET_LISTEN_MAX_NUM; wIndex++)
	{
		if (INVALID_SOCKET != g_cSocketInfoPool.m_atListenSocketArray[wIndex].m_hSocket)
		{
			FD_SET(g_cSocketInfoPool.m_atListenSocketArray[wIndex].m_hSocket, ptSet);
			if (g_cSocketInfoPool.m_atListenSocketArray[wIndex].m_hSocket > g_dwMaxSocket)
			{
				g_dwMaxSocket = g_cSocketInfoPool.m_atListenSocketArray[wIndex].m_hSocket;
			}
			g_dwSlectNum++;
		}
	}

	for (wIndex = 0; wIndex < g_cSocketInfoPool.m_wArraySize; wIndex++)
	{
		if (INVALID_SOCKET != g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_hSocket)
		{
			FD_SET(g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_hSocket, ptSet);
			if (g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_hSocket > g_dwMaxSocket)
			{
				g_dwMaxSocket = g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_hSocket;
			}
			g_dwSlectNum++;
		}
	}

	return;
}

#ifdef _LINUX_
void* UnifySocketCoreTask(void* pParam)
#else
u32 UnifySocketCoreTask(void* pParam)
#endif
{
	fd_set tWaitFd;
	SOCKHANDLE hHandleSocket;
	SOCKHANDLE hSockClient;
	u32  dwClientIp;
	sockaddr_in tAddrClient;
#ifdef _LINUX_
	socklen_t addrLenIn = sizeof(tAddrClient);
#else
	int addrLenIn = sizeof(tAddrClient);
#endif//_LINUX_
	u32   dwRcvLen = 0;
	u32   dwSrcIp = 0;
	u16	  wSrcPort = 0;
	u16 wIndex = 0;
	u16 wPoolIndex = UNIFYSOCKET_INVALIDINDEX;
	UNIFYSOCKETTYPE wUserType = UNIFYSOCKET_INVALID_TYPE;
	CUnifySocketTcpConnectItem* pcConnectItem = NULL;
	CUnifySocketTcpListenItem* pcListenItem = NULL;
	CUnifySocketUdpBindItem* pcUdpItem = NULL;
	
	struct timeval tTimeVal;
	struct timeval *pTimeVal;
	tTimeVal.tv_sec = 0;
	tTimeVal.tv_usec = 0;
	pTimeVal = &tTimeVal;

	BOOL32 bExit = FALSE;
	while(!bExit) {
//		printf("before select.\n");
		UnifySocketSelectFdSet(&tWaitFd);
//		printf("select FD_SETSIZE %d, g_dwMaxSocket %d, g_dwSlectNum %d.\n", FD_SETSIZE, g_dwMaxSocket, g_dwSlectNum);
		if (g_dwSlectNum == 0)
		{
			UnifyTaskDelay(100);
			continue;
		}

		int ret = select(g_dwMaxSocket+1, &tWaitFd, NULL, NULL, pTimeVal);
		if(ret == SOCKET_ERROR || ret == 0) {
			UnifyTaskDelay(100);
//			printf("[select] select ret %d!\n", ret);
//			UnifyPrintf("[select] select ret %d!\n", ret);
			continue;
		}
//		printf("[select] select ret %d!\n", ret);
//		UnifyPrintf("[select] select ret %d!\n", ret);

		// client connect
		for(wIndex = 0; wIndex < UNIFYSOCKET_LISTEN_MAX_NUM; wIndex++)
		{
			hHandleSocket = g_cSocketInfoPool.m_atListenSocketArray[wIndex].m_hSocket;
			if (INVALID_SOCKET == hHandleSocket)
			{
				continue;
			}
			pcListenItem = (CUnifySocketTcpListenItem*)g_cSocketInfoPool.m_atListenSocketArray[wIndex].m_pcSocketItem;
			if (NULL == pcListenItem)
			{
				UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray[dwIndex].m_pcSocketItem is NULL! listen wIndex:%d!\n", 
					wIndex);
				continue;
			}

			if (FD_ISSET(hHandleSocket, &tWaitFd))
			{
				hSockClient = accept(hHandleSocket, (sockaddr *)&tAddrClient, &addrLenIn);
				if (INVALID_SOCKET == hSockClient)
				{
#ifdef _IOS_PLATFORM_
					if (errno == EWOULDBLOCK || errno == ECONNABORTED || errno == EPROTO || errno == EINTR)
						continue;
					else if (errno == EAGAIN) {
						u32 on = 0;
						ioctl(hHandleSocket, FIONBIO, &on);
					} else {
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: accept sock connect fail, errno %d.\n" , errno );
					}
#endif//_IOS_PLATFORM_
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: accept sock connect fail!\n");
				}
				else
				{
					// set the socket's property, as heartbeat,
					u32 optVal;
					int set_result;
					
					optVal = 1;
					set_result = setsockopt(hSockClient, IPPROTO_TCP , TCP_NODELAY , (char *) &optVal, sizeof(optVal) );
					if(set_result == SOCKET_ERROR ) {
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail  %d\n", UnifyGetSockError());
					}
					
					optVal = SOCKET_SEND_BUF;
					set_result = setsockopt(hSockClient, SOL_SOCKET , SO_SNDBUF, (char *)&optVal, sizeof(optVal) );
					if(set_result == SOCKET_ERROR ) {
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail  %d\n", UnifyGetSockError());
					}
#ifdef _MSC_VER
					optVal = SOCKET_RECV_BUF;
					set_result = setsockopt(hSockClient, SOL_SOCKET , SO_RCVBUF, (char *)&optVal, sizeof(optVal) );
					if(set_result == SOCKET_ERROR ) {
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail  %d\n", UnifyGetSockError());
					}
#endif//_MSC_VER
					optVal = 1;
					set_result = setsockopt(hSockClient, SOL_SOCKET , SO_KEEPALIVE, (char *)&optVal, sizeof(optVal));
					if(set_result == SOCKET_ERROR ) {
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail  %d\n", UnifyGetSockError());
					}
					
					dwClientIp =  (u32)tAddrClient.sin_addr.s_addr;
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: client "UnifyIpForMat" accepted on port %d! the client sock is = %d!\n", 
						UnifyU32ToIp(dwClientIp), pcListenItem->GetListenPort(), hSockClient);
					
					wPoolIndex = g_cSocketInfoPool.RegistSock(hSockClient, dwClientIp, 0, UNIFYSOCKET_CLIENT_TYPE, (CUnifySocketBaseItem*)pcListenItem);
					if (UNIFYSOCKET_INVALIDINDEX != wPoolIndex)
					{
						pcListenItem->AddClientPoolIndex(wPoolIndex);
						pcListenItem->CallBackClientConnect(hSockClient, dwClientIp, wPoolIndex);
					}
					else
					{
						UnifySockClose(hSockClient);
						UnifyPrintf("[unifysocket] UnifySocketCoreTask RegistSock failed, close socket:%d!!! wPoolIndex:%d.\n", 
							hSockClient, wPoolIndex);
					}
				}
			}
		}

		if (FD_ISSET(g_hInnerUdpSocket, &tWaitFd))
		{
			memset(g_achBuf, 0, sizeof(g_achBuf));
			dwRcvLen = 0;
			dwSrcIp = 0;
			wSrcPort = 0;
			if (UnifySockRecvFrom(g_hInnerUdpSocket, g_achBuf, UNIFYSOCKET_RCVDATA_MAX_BUF, &dwRcvLen, &dwSrcIp, &wSrcPort))
			{
				UnifyPrintf("[unifysocket] UnifySocketCoreTask InnerUdp rcv ok! socket:%d, rcvBuf:%s, len:%d, srcIp:"UnifyIpForMat", srcPort:%d.\n", 
					g_hInnerUdpSocket, g_achBuf, dwRcvLen, UnifyU32ToIp(dwSrcIp), wSrcPort);
			}
		}

		// rcv data
		for(wIndex = 0; wIndex < g_cSocketInfoPool.m_wArraySize; wIndex++)
		{
			hHandleSocket = g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_hSocket;
			if (INVALID_SOCKET == hHandleSocket)
			{
				continue;
			}

			wUserType = g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_wType;
			if (wUserType == UNIFYSOCKET_CONNECT_TYPE)
			{
				pcConnectItem = (CUnifySocketTcpConnectItem*)g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_pcSocketItem;
				if (NULL == pcConnectItem)
				{
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray[dwIndex].m_pcSocketItem is NULL! wUserType:%d, wIndex:%u!\n", 
						wUserType, wIndex);
					continue;
				}
			}
			else if (wUserType == UNIFYSOCKET_CLIENT_TYPE)
			{
				pcListenItem = (CUnifySocketTcpListenItem*)g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_pcSocketItem;
				if (NULL == pcListenItem)
				{
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray[dwIndex].m_pcSocketItem is NULL! wUserType:%d, wIndex:%u!\n", 
						wUserType, wIndex);
					continue;
				}
			}
			else if (wUserType == UNIFYSOCKET_UDP_TYPE)
			{
				pcUdpItem = (CUnifySocketUdpBindItem*)g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_pcSocketItem;
				if (NULL == pcUdpItem)
				{
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray[dwIndex].m_pcSocketItem is NULL! wUserType:%d, wIndex:%u!\n", 
						wUserType, wIndex);
					continue;
				}
			}
			else
			{
				UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray is invalid type! wIndex:%u!\n", wIndex);
				continue;
			}

//			UnifyPrintf("[unifysocket] FD_ISSET begin! socket:%d, type:%d.\n", hHandleSocket, wUserType);

			if (FD_ISSET(hHandleSocket, &tWaitFd))
			{
				memset(g_achBuf, 0, sizeof(g_achBuf));
				dwRcvLen = 0;
				dwSrcIp = 0;
				wSrcPort = 0;
				if (wUserType == UNIFYSOCKET_UDP_TYPE)
				{
					if (UnifySockRecvFrom(hHandleSocket, g_achBuf, UNIFYSOCKET_RCVDATA_MAX_BUF, &dwRcvLen, &dwSrcIp, &wSrcPort))
					{
// 						UnifyPrintf("[unifysocket] UnifySocketCoreTask: rcvfrom ok! socket:%d, rcvBuf:%s, len:%d, srcIp:"UnifyIpForMat", srcPort:%d, type:%d-%s.\n", 
// 							hHandleSocket, achBuf, dwRcvLen, UnifyU32ToIp(dwSrcIp), wSrcPort, wUserType, GetSocketTypeName(wUserType));
						pcUdpItem->CallBackRcvData(hHandleSocket, g_achBuf, dwRcvLen, dwSrcIp, wSrcPort);
					}
					continue;
				}

//				UnifyPrintf("[unifysocket] UnifySockRecv begin! socket:%d, type:%d.\n", hHandleSocket, wUserType);

				if (UnifySockRecv(hHandleSocket, g_achBuf, UNIFYSOCKET_RCVDATA_MAX_BUF, &dwRcvLen))
				{
//					UnifyPrintf("[unifysocket] UnifySocketCoreTask: rcv ok! socket:%d, rcvBuf:%s, len:%d, type:%d.\n", hHandleSocket, achBuf, dwRcvLen, wUserType);
					if (wUserType == UNIFYSOCKET_CONNECT_TYPE)
					{
						pcConnectItem->CallBackRcvData(hHandleSocket, g_achBuf, dwRcvLen);
					}
					else if (wUserType == UNIFYSOCKET_CLIENT_TYPE)
					{
						pcListenItem->CallBackClientRcvData(hHandleSocket, g_achBuf, dwRcvLen);
					}
					else
					{

					}
				}
				else
				{
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: disconnect! socket:%d, type:%d.\n", hHandleSocket, wUserType);
					if (wUserType == UNIFYSOCKET_CONNECT_TYPE)
					{
						pcConnectItem->CallBackDisConnect(hHandleSocket);
						g_cSocketInfoPool.UnRegistSock(wIndex+1);
					}
					else if (wUserType == UNIFYSOCKET_CLIENT_TYPE)
					{
						pcListenItem->CallBackClientDisConnect(hHandleSocket);
						pcListenItem->DelClientPoolIndex(wIndex+1);
						g_cSocketInfoPool.UnRegistSock(wIndex+1);
					}
					else
					{

					}
				}
			}
		}
	}

	OspTaskExit();
	return 0;
}
#endif//_USE_SELECT_
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
#ifdef _USE_EPOLL_
#ifdef _LINUX_
void* UnifySocketCoreTask(void* pParam)
#else
u32 UnifySocketCoreTask(void* pParam)
#endif
{
	SOCKHANDLE hSockClient;
	sockaddr_in tAddrClient;
	socklen_t addrLenIn = sizeof(tAddrClient);
	u32  dwClientIp;
	u32 optVal = 0;
	int set_result = -1;

	u32   dwRcvLen = 0;
	u32   dwSrcIp = 0;
	u16   wSrcPort = 0;

	SOCKHANDLE hHandleSocket;
	u32 dwParam = 0;
	UNIFYSOCKETTYPE wUserType = UNIFYSOCKET_INVALID_TYPE;
	u16 wIndex = 0xffff;
	u16 wPoolIndex = UNIFYSOCKET_INVALIDINDEX;
	s32 sIndex = 0;
	s32 sEventCount = -1;
	epoll_event atEpollEvent[g_dwMaxEpollFdNum];
	memset(atEpollEvent, 0, sizeof(atEpollEvent));
	epoll_event *ptEpollEvent = NULL;

	CUnifySocketTcpListenItem* pcListenItem = NULL;
	CUnifySocketTcpConnectItem* pcConnectItem = NULL;
	CUnifySocketUdpBindItem* pcUdpItem = NULL;

	BOOL32 bExit = FALSE;
	while(!bExit) {

		sEventCount = epoll_wait(g_nEpollFd, atEpollEvent, g_dwMaxEpollFdNum, -1);
		if (0 > sEventCount) {
			UnifyTaskDelay(10);
			continue;
		}

		for (sIndex = 0; sIndex < sEventCount; sIndex++) {
			ptEpollEvent = atEpollEvent + sIndex;
			if (0 == (ptEpollEvent->events & (EPOLLIN | EPOLLPRI | EPOLLERR))) {
				UnifyTaskDelay(10);
				continue;
			}
			
			hHandleSocket = (u32) (ptEpollEvent->data.u64);
			dwParam = (u32) ((ptEpollEvent->data.u64) >> 32);
			wUserType = GetParam1(dwParam);
			wIndex = GetParam2(dwParam);
//			UnifyPrintf("handlesocket:%u, dwparam:%u, wusertype:%d, wIndex:%d.\n", hHandleSocket, dwParam, wUserType, wIndex);
			if (wUserType == UNIFYSOCKET_LISTEN_TYPE)
			{
				pcListenItem = (CUnifySocketTcpListenItem*)g_cSocketInfoPool.m_atListenSocketArray[wIndex].m_pcSocketItem;
				if (NULL != pcListenItem)
				{
					addrLenIn = sizeof(tAddrClient);
					hSockClient = accept(hHandleSocket, (sockaddr*)&tAddrClient, &addrLenIn);
					if (hSockClient == INVALID_SOCKET) {
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: accept sock connect fail, errno %d\n", errno);
					} else {
						// set the socket's property, as heartbeat,
						optVal = 1;
						set_result = setsockopt(hSockClient, IPPROTO_TCP , TCP_NODELAY , (char *) &optVal, sizeof(optVal) );
						if (set_result == SOCKET_ERROR) {
							UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail  %d\n", UnifyGetSockError());
						}
						
						/*optVal = 8192 * 4; */
						optVal = 4 * 1024 * 1024;
						set_result = setsockopt(hSockClient, SOL_SOCKET , SO_SNDBUF, (char *)&optVal, sizeof(optVal) );
						if (set_result == SOCKET_ERROR) {
							UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail  %d\n", UnifyGetSockError());
						}
						
						optVal = 1;
						set_result = setsockopt(hSockClient, SOL_SOCKET , SO_KEEPALIVE, (char *)&optVal, sizeof(optVal));
						if (set_result == SOCKET_ERROR) {
							UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail  %d\n", UnifyGetSockError());
						}
						
						struct timeval tv;
						tv.tv_sec = 1;
						tv.tv_usec = 0;
						set_result = setsockopt(hSockClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv));
						if (set_result == SOCKET_ERROR) {
							UnifyPrintf("[unifysocket] UnifySocketCoreTask: set sock option fail, errno %d\n", UnifyGetSockError());
						}
						
						dwClientIp =  (u32)tAddrClient.sin_addr.s_addr;
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: client "UnifyIpForMat" accepted on port %d! the client sock is = %d!\n", 
							UnifyU32ToIp(dwClientIp), pcListenItem->GetListenPort(), hSockClient);
						
						wPoolIndex = g_cSocketInfoPool.RegistSock(hSockClient, dwClientIp, 0, UNIFYSOCKET_CLIENT_TYPE, (CUnifySocketBaseItem*)pcListenItem);
						if (UNIFYSOCKET_INVALIDINDEX != wPoolIndex)
						{
							pcListenItem->AddClientPoolIndex(wPoolIndex);
							pcListenItem->CallBackClientConnect(hSockClient, dwClientIp, wPoolIndex);
						}
						else
						{
							UnifySockClose(hSockClient);
							UnifyPrintf("[unifysocket] UnifySocketCoreTask RegistSock failed, close socket:%d!!! wPoolIndex:%d.\n", 
								hSockClient, wPoolIndex);
						}
					}
				}
			}
			else
			{
				if (wUserType == UNIFYSOCKET_CONNECT_TYPE)
				{
					pcConnectItem = (CUnifySocketTcpConnectItem*)g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_pcSocketItem;
					if (NULL == pcConnectItem)
					{
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray[dwIndex].m_pcSocketItem is NULL! wUserType:%d, wIndex:%u!\n", 
							wUserType, wIndex);
						continue;
					}
				}
				else if (wUserType == UNIFYSOCKET_CLIENT_TYPE)
				{
					pcListenItem = (CUnifySocketTcpListenItem*)g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_pcSocketItem;
					if (NULL == pcListenItem)
					{
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray[dwIndex].m_pcSocketItem is NULL! wUserType:%d, wIndex:%u!\n", 
							wUserType, wIndex);
						continue;
					}
				}
				else if (wUserType == UNIFYSOCKET_UDP_TYPE)
				{
					pcUdpItem = (CUnifySocketUdpBindItem*)g_cSocketInfoPool.m_ptRegSocketArray[wIndex].m_pcSocketItem;
					if (NULL == pcUdpItem)
					{
						UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray[dwIndex].m_pcSocketItem is NULL! wUserType:%d, wIndex:%u!\n", 
							wUserType, wIndex);
						continue;
					}
				}
				else
				{
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: g_cSocketInfoPool.m_ptRegSocketArray is invalid type %d! wIndex:%u!\n", wUserType, wIndex);
					continue;
				}

				memset(g_achBuf, 0, sizeof(g_achBuf));
				dwRcvLen = 0;
				dwSrcIp = 0;
				wSrcPort = 0;
				if (wUserType == UNIFYSOCKET_UDP_TYPE)
				{
					if (UnifySockRecvFrom(hHandleSocket, g_achBuf, UNIFYSOCKET_RCVDATA_MAX_BUF, &dwRcvLen, &dwSrcIp, &wSrcPort))
					{
						//UnifyPrintf("[unifysocket] UnifySocketCoreTask: rcvfrom ok! socket:%d, rcvBuf:%s, len:%d, srcIp:"UnifyIpForMat", srcPort:%d, type:%d-%s.\n", 
						// 							hHandleSocket, achBuf, dwRcvLen, UnifyU32ToIp(dwSrcIp), wSrcPort, wUserType, GetSocketTypeName(wUserType));
						pcUdpItem->CallBackRcvData(hHandleSocket, g_achBuf, dwRcvLen, dwSrcIp, wSrcPort);
					}
					continue;
				}

				if (UnifySockRecv(hHandleSocket, g_achBuf, UNIFYSOCKET_RCVDATA_MAX_BUF, &dwRcvLen))
				{
//					UnifyPrintf("[unifysocket] UnifySocketCoreTask: rcv ok! socket:%d, rcvBuf:%s, len:%d, type:%d.\n", hHandleSocket, achBuf, dwRcvLen, wUserType);
					if (wUserType == UNIFYSOCKET_CONNECT_TYPE)
					{
						pcConnectItem->CallBackRcvData(hHandleSocket, g_achBuf, dwRcvLen);
					}
					else if (wUserType == UNIFYSOCKET_CLIENT_TYPE)
					{
						pcListenItem->CallBackClientRcvData(hHandleSocket, g_achBuf, dwRcvLen);
					}
					else
					{

					}
				}
				else
				{
					UnifyPrintf("[unifysocket] UnifySocketCoreTask: disconnect! socket:%d, type:%d.\n", hHandleSocket, wUserType);
					if (wUserType == UNIFYSOCKET_CONNECT_TYPE)
					{
						pcConnectItem->CallBackDisConnect(hHandleSocket);
						g_cSocketInfoPool.UnRegistSock(wIndex+1);
					}
					else if (wUserType == UNIFYSOCKET_CLIENT_TYPE)
					{
						pcListenItem->CallBackClientDisConnect(hHandleSocket);
						pcListenItem->DelClientPoolIndex(wIndex+1);
						g_cSocketInfoPool.UnRegistSock(wIndex+1);
					}
					else
					{

					}
				}
			}
		}
	}


	OspTaskExit();
	return 0;
}
#endif//_USE_EPOLL_
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
CUnifySocketTcpConnectItem::CUnifySocketTcpConnectItem(u32 dwUserParam /*= 0*/):CUnifySocketBaseItem(dwUserParam)
,m_wSocketPoolIndex(UNIFYSOCKET_INVALIDINDEX)
,m_hConnectSocket(INVALID_SOCKET)
,m_dwDstIP(0)
,m_wDstPort(0)
,m_pCBRcvData(NULL)
,m_pCBDisConnect(NULL)
{	
}

CUnifySocketTcpConnectItem::~CUnifySocketTcpConnectItem()
{
	CleanSocket();
}

SOCKHANDLE CUnifySocketTcpConnectItem::CreatConnectSocket( u32 dwdstip, u16 wdstport, 
													   CBTcpConnectRcvData pcbRcvFun /*= NULL*/, 
													   CBTcpConnectDisConnect pcbDisFun /*= NULL*/ )
{	
	if (m_bUsed)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpConnectItem::CreatConnectSocket m_bUsed is TRUE!\n" );
		return INVALID_SOCKET;
	}

	m_hConnectSocket = UnifyConnectTcpSocket(dwdstip, wdstport, 300);
	if (INVALID_SOCKET == m_hConnectSocket)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpConnectItem::CreatConnectSocket connect fail!.\n");
		return INVALID_SOCKET;
	}

	m_bUsed = TRUE;
	m_dwDstIP = dwdstip;
	m_wDstPort = wdstport;
	m_pCBRcvData = pcbRcvFun;
	m_pCBDisConnect = pcbDisFun;

	m_wSocketPoolIndex = g_cSocketInfoPool.RegistSock(m_hConnectSocket, m_dwDstIP, m_wDstPort, UNIFYSOCKET_CONNECT_TYPE, (CUnifySocketBaseItem*)this);
	if (UNIFYSOCKET_INVALIDINDEX == m_wSocketPoolIndex)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpConnectItem::CreatConnectSocket RegistSock failed!.\n");
		UnifySockClose(m_hConnectSocket);
		CleanSocket();
		return INVALID_SOCKET;
	}

	return m_hConnectSocket;
}

BOOL32 CUnifySocketTcpConnectItem::SendData( const char* pData, u32 dwLen )
{
	if(m_hConnectSocket == INVALID_SOCKET)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpConnectItem::SendData m_hConnectSocket is INVALID_SOCKET!\n");
		return FALSE;
	}
	BOOL32 bRet = UnifySockSend(m_hConnectSocket, pData, dwLen);
	return bRet;
}

void CUnifySocketTcpConnectItem::CleanSocket()
{
	if (UNIFYSOCKET_INVALIDINDEX != m_wSocketPoolIndex)
	{
		g_cSocketInfoPool.UnRegistSock(m_wSocketPoolIndex);
	}

	m_bUsed = FALSE;
	m_dwUserParam = 0;

	m_wSocketPoolIndex = UNIFYSOCKET_INVALIDINDEX;
	m_hConnectSocket = INVALID_SOCKET;
	m_dwDstIP = 0;
	m_wDstPort = 0;
	m_pCBRcvData = NULL;
	m_pCBDisConnect = NULL;

	return;
}

void CUnifySocketTcpConnectItem::Show()
{
	UnifyPrintf("[unifysocket] CUnifySocketTcpConnectItem (%p) Info:\n", this);
	UnifyPrintf("  m_bUsed=%d.\n", m_bUsed);
	UnifyPrintf("  m_dwUserParam=%u.\n", m_dwUserParam);
	UnifyPrintf("  m_wSocketPoolIndex=%d.\n", m_wSocketPoolIndex);
	UnifyPrintf("  m_hConnectSocket=%d.\n", m_hConnectSocket);
	UnifyPrintf("  m_dwDstIP="UnifyIpForMat".\n", UnifyU32ToIp(m_dwDstIP));
	UnifyPrintf("  m_wDstPort=%d.\n", m_wDstPort);
	UnifyPrintf("  m_pCBRcvData=%p.\n", m_pCBRcvData);
	UnifyPrintf("  m_pCBDisConnect=%p.\n\n", m_pCBDisConnect);
}

void CUnifySocketTcpConnectItem::CallBackRcvData(SOCKHANDLE handleSocket, char* pDataBuf, u32 dwLen)
{
	if (NULL != m_pCBRcvData)
	{
		m_pCBRcvData(m_dwUserParam, handleSocket, pDataBuf, dwLen);
	}
}

void CUnifySocketTcpConnectItem::CallBackDisConnect( SOCKHANDLE handleSocket )
{
	if (NULL != m_pCBDisConnect)
	{
		m_pCBDisConnect(m_dwUserParam, handleSocket);
	}
	CleanSocket();
}
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
CUnifySocketTcpListenItem::CUnifySocketTcpListenItem(u32 dwUserParam /*= 0*/):CUnifySocketBaseItem(dwUserParam)
,m_wListenPoolIndex(UNIFYSOCKET_INVALIDINDEX)
,m_hListenSocket(INVALID_SOCKET)
,m_dwListenIP(0)
,m_wListenPort(0)
,m_pCBClientConnect(NULL)
,m_pCBClientRcvData(NULL)
,m_pCBClientDisConnect(NULL)
,m_semClient(NULL)
{
}

CUnifySocketTcpListenItem::~CUnifySocketTcpListenItem()
{
	CleanSocket();
}

SOCKHANDLE CUnifySocketTcpListenItem::CreatListenSocket( u32 dwlistenip, u16 wlistenport, 
														CBTcpListenClientConnect pcbConnectFun /*= NULL*/, 
														CBTcpListenClientRcvData pcbRcvFun /*= NULL*/, 
														CBTcpListenClientDisConnect pcbDisFun /*= NULL*/ )
{	
	if (m_bUsed)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem::CreatListenSocket m_bUsed is TRUE!\n" );
		return INVALID_SOCKET;
	}

	m_hListenSocket = UnifyCreateTcpSockListen(dwlistenip, wlistenport);
	if (INVALID_SOCKET == m_hListenSocket)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem::CreatListenSocket failed! ip:"UnifyIpForMat", port:%d.\n", 
			UnifyU32ToIp(dwlistenip), wlistenport);
		return INVALID_SOCKET;
	}

	if (NULL == m_semClient)
	{
		if (!OspSemBCreate(&m_semClient))
		{
			UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem::CreatListenSocket OspSemBCreate failed!.\n");
			m_semClient = NULL;
			CleanSocket();
			return INVALID_SOCKET;
		}
	}

	m_bUsed = TRUE;
	m_dwListenIP = dwlistenip;
	m_wListenPort = wlistenport;
	m_pCBClientConnect = pcbConnectFun;
	m_pCBClientRcvData = pcbRcvFun;
	m_pCBClientDisConnect = pcbDisFun;
	

	m_wListenPoolIndex = g_cSocketInfoPool.RegistListenSock(m_hListenSocket, m_dwListenIP, m_wListenPort, (CUnifySocketBaseItem*)this);
	if (UNIFYSOCKET_INVALIDINDEX == m_wListenPoolIndex)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem::CreatListenSocket RegistListenSock failed!.\n");
		UnifySockClose(m_hListenSocket);
		CleanSocket();
		return INVALID_SOCKET;
	}
	m_awClientPoolIndex.m_tDefault = UNIFYSOCKET_INVALIDINDEX;

	return m_hListenSocket;	
}

BOOL32 CUnifySocketTcpListenItem::SendData( SOCKHANDLE hClientSocket, const char* pData, u32 dwLen )
{	
	if (INVALID_SOCKET == hClientSocket)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem::SendData hClientSocket is INVALID_SOCKET!\n");
		return FALSE;
	}
	BOOL32 bRet = UnifySockSend(hClientSocket, pData, dwLen);
	return bRet;
}

void CUnifySocketTcpListenItem::CloseClient(u16 wClientIndex)
{
	if (wClientIndex == UNIFYSOCKET_INVALIDINDEX)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem::CloseClient error! wClientIndex is %d!\n", wClientIndex);
		return;
	}
	OspSemTake(m_semClient);
	u32 dwNum = m_awClientPoolIndex.Size();
	BOOL32 bDel = FALSE;
	for (u32 dwLoop = 0; dwLoop < dwNum; dwLoop++)
	{
		if (m_awClientPoolIndex[dwLoop] == wClientIndex)
		{
			m_awClientPoolIndex.Delete(dwLoop); // delete操作后，dwLoop已经失效
			bDel = TRUE;
			break;
		}
	}
	OspSemGive(m_semClient);
	if (bDel)
	{
		g_cSocketInfoPool.UnRegistSock(wClientIndex);
		AwakeCoreTask();
	}

	return;
}

void CUnifySocketTcpListenItem::CleanSocket()
{
	u32 dwNum = m_awClientPoolIndex.Size();
	u16 wClientPoolIndex = UNIFYSOCKET_INVALIDINDEX;
	for (u32 dwLoop = 0; dwLoop < dwNum; dwLoop++)
	{
		wClientPoolIndex = m_awClientPoolIndex[dwLoop];
		if (UNIFYSOCKET_INVALIDINDEX != wClientPoolIndex)
		{
			// 不能在循环中对m_awClientPoolIndex进行delete操作，否则dwLoop会失效
			g_cSocketInfoPool.UnRegistSock(wClientPoolIndex);
		}
	}

	// 遍历后再对m_awClientPoolIndex进行clear操作
	m_awClientPoolIndex.Clear();

	if (UNIFYSOCKET_INVALIDINDEX != m_wListenPoolIndex)
	{
		g_cSocketInfoPool.UnRegistListenSock(m_wListenPoolIndex);
	}

	if (NULL != m_semClient)
	{
		OspSemDelete(m_semClient);
		m_semClient = NULL;
	}

	m_bUsed = FALSE;
	m_dwUserParam = 0;

	m_wListenPoolIndex = UNIFYSOCKET_INVALIDINDEX;
	m_hListenSocket = INVALID_SOCKET;
	m_dwListenIP = 0;
	m_wListenPort = 0;
	m_pCBClientConnect = NULL;
	m_pCBClientRcvData = NULL;
	m_pCBClientDisConnect = NULL;
}

void CUnifySocketTcpListenItem::Show()
{
	UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem (%p) Info:\n", this);
	UnifyPrintf("  m_bUsed=%d.\n", m_bUsed);
	UnifyPrintf("  m_dwUserParam=%u.\n", m_dwUserParam);
	UnifyPrintf("  m_wListenPoolIndex=%d.\n", m_wListenPoolIndex);
	UnifyPrintf("  m_hListenSocket=%d.\n", m_hListenSocket);
	UnifyPrintf("  m_dwListenIP="UnifyIpForMat".\n", UnifyU32ToIp(m_dwListenIP));
	UnifyPrintf("  m_wListenPort=%d.\n", m_wListenPort);
	UnifyPrintf("  m_pCBClientConnect=%p.\n", m_pCBClientConnect);
	UnifyPrintf("  m_pCBRcvData=%p.\n", m_pCBClientRcvData);
	UnifyPrintf("  m_pCBDisConnect=%p.\n", m_pCBClientDisConnect);
	UnifyPrintf("  m_awClientPoolIndex size=%d.\n", m_awClientPoolIndex.Size());
	u16 wPoolIndex = UNIFYSOCKET_INVALIDINDEX;
	TUnifySocketInfo* pSocketInfo = NULL;
	for (u32 dwIndex = 0; dwIndex < m_awClientPoolIndex.Size(); dwIndex++)
	{
		wPoolIndex = m_awClientPoolIndex[dwIndex];
		if (UNIFYSOCKET_INVALIDINDEX != wPoolIndex && (wPoolIndex-1) < g_cSocketInfoPool.m_wArraySize )
		{
			pSocketInfo = &g_cSocketInfoPool.m_ptRegSocketArray[wPoolIndex-1];
			UnifyPrintf("    dwIndex:%d, wPoolIndex:%d, Type:%d-%s, Socket:%d, ClientIp:"UnifyIpForMat", SocketItem:%p.\n",
				dwIndex, wPoolIndex, pSocketInfo->m_wType, GetSocketTypeName(pSocketInfo->m_wType),
				pSocketInfo->m_hSocket, UnifyU32ToIp(pSocketInfo->m_tIpPort.m_wIp),
				pSocketInfo->m_pcSocketItem);
		}
	}
	UnifyPrintf("\n");
}

void CUnifySocketTcpListenItem::AddClientPoolIndex( u16 wPoolIndex )
{
	OspSemTake(m_semClient);
	m_awClientPoolIndex.Add(&wPoolIndex);
	OspSemGive(m_semClient);
}

void CUnifySocketTcpListenItem::DelClientPoolIndex( u16 wPoolIndex )
{
	OspSemTake(m_semClient);
	u32 dwNum = m_awClientPoolIndex.Size();
	for (u32 dwLoop = 0; dwLoop < dwNum; dwLoop++)
	{
		if (m_awClientPoolIndex[dwLoop] == wPoolIndex)
		{
			m_awClientPoolIndex.Delete(dwLoop); // delete操作后，dwLoop已经失效
			OspSemGive(m_semClient);
			return;
		}
	}
	OspSemGive(m_semClient);
}

void CUnifySocketTcpListenItem::CallBackClientConnect( SOCKHANDLE hClientSocket, u32 dwClientIp, u16 wClientIndex )
{
	if (NULL != m_pCBClientConnect)
	{
		m_pCBClientConnect(m_dwUserParam, hClientSocket, dwClientIp, wClientIndex);
	}
}

void CUnifySocketTcpListenItem::CallBackClientRcvData( SOCKHANDLE hClientSocket, char* pDataBuf, u32 dwLen )
{
	if (NULL != m_pCBClientRcvData)
	{
		m_pCBClientRcvData(m_dwUserParam, hClientSocket, pDataBuf, dwLen);
	}
}

void CUnifySocketTcpListenItem::CallBackClientDisConnect( SOCKHANDLE hClientSocket )
{
	if (NULL != m_pCBClientDisConnect)
	{
		m_pCBClientDisConnect(m_dwUserParam, hClientSocket);
	}
}

/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
CUnifySocketUdpBindItem::CUnifySocketUdpBindItem(u32 dwUserParam /*= 0*/ ):CUnifySocketBaseItem(dwUserParam)
,m_wSocketPoolIndex(UNIFYSOCKET_INVALIDINDEX)
,m_hUdpBindSocket(INVALID_SOCKET)
,m_dwUdpBindIp(0)
,m_wUdpBindPort(0)
,m_pCBRcvData(NULL)
{
	
}

CUnifySocketUdpBindItem::~CUnifySocketUdpBindItem()
{
	
}

SOCKHANDLE CUnifySocketUdpBindItem::CreatUdpBindSocket( u32 dwLocalIp, u16 wBindPort, CBSocketUdpRcvData pcbRcvFun /*= NULL*/ )
{
	if (m_bUsed)
	{
		UnifyPrintf("[unifysocket] CUnifySocketUdpBindItem::CreatUdpBindSocket m_bUsed is TRUE!\n" );
		return INVALID_SOCKET;
	}

	m_hUdpBindSocket = UnifyCreateUdpSockBind(dwLocalIp, wBindPort);
	if (INVALID_SOCKET == m_hUdpBindSocket)
	{
		UnifyPrintf("[unifysocket] CUnifySocketTcpListenItem::CreatUdpBindSocket failed! ip:"UnifyIpForMat", port:%d.\n", 
			UnifyU32ToIp(dwLocalIp), wBindPort);
		return INVALID_SOCKET;
	}

	m_bUsed = TRUE;
	m_dwUdpBindIp = dwLocalIp;
	m_wUdpBindPort = wBindPort;
	m_pCBRcvData = pcbRcvFun;

	m_wSocketPoolIndex = g_cSocketInfoPool.RegistSock(m_hUdpBindSocket, m_dwUdpBindIp, m_wUdpBindPort, UNIFYSOCKET_UDP_TYPE, (CUnifySocketBaseItem*)this);
	if (UNIFYSOCKET_INVALIDINDEX == m_wSocketPoolIndex)
	{
		UnifyPrintf("[unifysocket] CUnifySocketUdpBindItem::CreatUdpBindSocket RegistSock failed!.\n");
		UnifySockClose(m_hUdpBindSocket);
		CleanSocket();
		return INVALID_SOCKET;
	}

	return m_hUdpBindSocket;
}

BOOL32 CUnifySocketUdpBindItem::SendData( const char* pData, u32 dwLen, u32 dwDstIp, u16 wDstPort )
{
	if(m_hUdpBindSocket == INVALID_SOCKET)
	{
		UnifyPrintf("[unifysocket] CUnifySocketUdpBindItem::SendData m_hUdpBindSocket is INVALID_SOCKET!\n");
		return FALSE;
	}
	BOOL32 bRet = UnifySockSendTo(m_hUdpBindSocket, pData, dwLen, dwDstIp, wDstPort);
	return bRet;
}

void CUnifySocketUdpBindItem::CleanSocket()
{
	if (UNIFYSOCKET_INVALIDINDEX != m_wSocketPoolIndex)
	{
		g_cSocketInfoPool.UnRegistSock(m_wSocketPoolIndex);
	}

	m_bUsed = FALSE;
	m_dwUserParam = 0;

	m_wSocketPoolIndex = UNIFYSOCKET_INVALIDINDEX;
	m_hUdpBindSocket = INVALID_SOCKET;
	m_dwUdpBindIp = 0;
	m_wUdpBindPort = 0;
	m_pCBRcvData = NULL;
}

void CUnifySocketUdpBindItem::Show()
{
	UnifyPrintf("[unifysocket] CUnifySocketUdpBindItem (%p) Info:\n", this);
	UnifyPrintf("  m_bUsed=%d.\n", m_bUsed);
	UnifyPrintf("  m_dwUserParam=%u.\n", m_dwUserParam);
	UnifyPrintf("  m_wSocketPoolIndex=%d.\n", m_wSocketPoolIndex);
	UnifyPrintf("  m_hUdpBindSocket=%d.\n", m_hUdpBindSocket);
	UnifyPrintf("  m_dwUdpBindIp="UnifyIpForMat".\n", UnifyU32ToIp(m_dwUdpBindIp));
	UnifyPrintf("  m_wUdpBindPort=%d.\n", m_wUdpBindPort);
	UnifyPrintf("  m_pCBRcvData=%p.\n", m_pCBRcvData);
}

void CUnifySocketUdpBindItem::CallBackRcvData( SOCKHANDLE hUdpBindSocket, char* pDataBuf, u32 dwLen, u32 dwSrcIp, u16 wSrcPort )
{
	if (NULL!=m_pCBRcvData)
	{
		m_pCBRcvData(m_dwUserParam, hUdpBindSocket, pDataBuf, dwLen, dwSrcIp, wSrcPort);
	}
}

/////////////////////////////////////////////////////////////////