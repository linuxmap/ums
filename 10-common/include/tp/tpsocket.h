/******************************************************************************
文件实现功能：socket功能封装的主要包含头文件
******************************************************************************/
#ifndef _TP_SOCKET_H_
#define _TP_SOCKET_H_

#include <stdio.h>
#ifdef _MSC_VER
#include <winsock2.h>
#else
#include <pthread.h>
#endif//_MSC_VER

#include "kdvtype.h"
#include "temparray.h"
#include "osp.h"

#if (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPSOCKETDLL)

#ifdef TPSOCKETDLL_EXPORTS
#define TPSOCKET_API __declspec(dllexport)
#else
#define TPSOCKET_API __declspec(dllimport)
#endif

#else  // 其他平台的，或者是静态链接

#define TPSOCKET_API 

#endif// (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPSOCKETDLL)


#ifdef _MSC_VER
	#ifndef SOCKHANDLE
		#define SOCKHANDLE           SOCKET
	#endif//SOCKHANDLE
#else
	#ifndef SOCKHANDLE
		#define SOCKHANDLE           int
	#endif//SOCKHANDLE
#endif//_MSC_VER


#ifdef _LINUX_
	#ifndef INVALID_SOCKET
		#define INVALID_SOCKET        (-1)
	#endif//INVALID_SOCKET
#endif // _LINUX_

//以点分整数形式打印ip地址
#if !defined  UnifyIpForMat     
#define  UnifyIpForMat		"%u.%u.%u.%u"
#endif//u32IpForMat

#if !defined UnifyU32ToIp
#define UnifyU32ToIp(ip) ((u8 *)&(ip))[0], \
	((u8 *)&(ip))[1], \
	((u8 *)&(ip))[2], \
	((u8 *)&(ip))[3]
#endif//u32ToIp

#define UNIFYSOCKET_TYPE_TCP			(u16)1
#define UNIFYSOCKET_TYPE_UDP			(u16)2

// init
TPSOCKET_API BOOL32	UnifySocketMoudleInit(u16 wInnerUdpPort);

TPSOCKET_API void	UnifySocketPoolShow();

// 用于dump接收到的msg内容
typedef void (*CBMsgPrintf)(const char* szFormat, ...);
TPSOCKET_API void	UnifySocketDumpMsg(const char* buf, u16 wLen, CBMsgPrintf pcbPrintFun = NULL);

class TPSOCKET_API CUnifySocketBaseItem
{
public:
	CUnifySocketBaseItem(u32 dwUserParam = 0);
	virtual ~CUnifySocketBaseItem();

	virtual void		CleanSocket() = 0;
	virtual void		Show() = 0;

	virtual BOOL32      IsUsed()			
	{ 
		return m_bUsed;
	}
	virtual BOOL32		ResetUserParam(u32 dwUserParam = 0)
	{
		m_dwUserParam = dwUserParam;
		return TRUE;
	}

protected:
	CUnifySocketBaseItem(const CUnifySocketBaseItem&);
	CUnifySocketBaseItem& operator=(const CUnifySocketBaseItem&);

	BOOL32	m_bUsed;
	u32		m_dwUserParam;
};


////////////////////////////////////////////////////////////////////////////////
typedef void (*CBTcpConnectRcvData) (u32 dwUserParam, SOCKHANDLE hConnectSocket, char* pDataBuf, u32 dwLen);
typedef void (*CBTcpConnectDisConnect) (u32 dwUserParam, SOCKHANDLE hConnectSocket);

class TPSOCKET_API CUnifySocketTcpConnectItem : public CUnifySocketBaseItem
{
public:
	CUnifySocketTcpConnectItem(u32 dwUserParam = 0);
	virtual ~CUnifySocketTcpConnectItem();

	SOCKHANDLE			CreatConnectSocket(u32 dwdstip, u16 wdstport, 
											CBTcpConnectRcvData pcbRcvFun = NULL, 
											CBTcpConnectDisConnect pcbDisFun = NULL);
	BOOL32				SendData(const char* pData, u32 dwLen);

	virtual void		CleanSocket();
	virtual void		Show();
	
	SOCKHANDLE			GetConnectSocket()	{ return m_hConnectSocket;}
	u32					GetDstIp()			{ return m_dwDstIP;}
	u16					GetDstPort()		{ return m_wDstPort;}

	// 内部使用
	void				CallBackRcvData(SOCKHANDLE handleSocket, char* pDataBuf, u32 dwLen);
	void				CallBackDisConnect(SOCKHANDLE handleSocket);

protected:
	CUnifySocketTcpConnectItem(const CUnifySocketTcpConnectItem& );
	CUnifySocketTcpConnectItem& operator=(const CUnifySocketTcpConnectItem& );

	u16			m_wSocketPoolIndex; //poolindex从1开始
	SOCKHANDLE  m_hConnectSocket;
	u32			m_dwDstIP;
	u16			m_wDstPort;

	CBTcpConnectRcvData			m_pCBRcvData;
	CBTcpConnectDisConnect		m_pCBDisConnect;
};

////////////////////////////////////////////////////////////////////////////////
typedef void (*CBTcpListenClientConnect) (u32 dwUserParam, SOCKHANDLE hClientSocket, u32 dwClientIp, u16 wClientIndex); // wClientIndex 从1开始，0是无效值
typedef void (*CBTcpListenClientRcvData) (u32 dwUserParam, SOCKHANDLE hClientSocket, char* pDataBuf, u32 dwLen);
typedef void (*CBTcpListenClientDisConnect) (u32 dwUserParam, SOCKHANDLE hClientSocket);

class TPSOCKET_API CUnifySocketTcpListenItem : public CUnifySocketBaseItem
{
public:
	CUnifySocketTcpListenItem(u32 dwUserParam = 0);
	virtual ~CUnifySocketTcpListenItem();
	
	SOCKHANDLE			CreatListenSocket(u32 dwlistenip, u16 wlistenport, 
											CBTcpListenClientConnect pcbConnectFun = NULL, 
											CBTcpListenClientRcvData pcbRcvFun = NULL, 
											CBTcpListenClientDisConnect pcbDisFun = NULL);
	BOOL32				SendData(SOCKHANDLE hClientSocket, const char* pData, u32 dwLen);

	void				CloseClient(u16 wClientIndex);

	virtual void		CleanSocket();
	virtual void		Show();
	
	SOCKHANDLE			GetListenSocket()	{ return m_hListenSocket;}
	u32					GetListenIP()		{ return m_dwListenIP;}
	u16					GetListenPort()		{ return m_wListenPort;}

	// 内部使用
	void				AddClientPoolIndex(u16 wPoolIndex);
	void				DelClientPoolIndex(u16 wPoolIndex);

	// 内部使用
	void				CallBackClientConnect(SOCKHANDLE hClientSocket, u32 dwClientIp, u16 wClientIndex);
	void				CallBackClientRcvData(SOCKHANDLE hClientSocket, char* pDataBuf, u32 dwLen);
	void				CallBackClientDisConnect(SOCKHANDLE hClientSocket);

protected:
	CUnifySocketTcpListenItem(const CUnifySocketTcpListenItem& );
	CUnifySocketTcpListenItem& operator=(const CUnifySocketTcpListenItem& );
	
	u16			m_wListenPoolIndex; //poolindex从1开始
	SOCKHANDLE  m_hListenSocket;
	u32			m_dwListenIP;
	u16			m_wListenPort;
	
	SEMHANDLE							m_semClient;
	TempArray<u16>						m_awClientPoolIndex; //poolindex从1开始
	
	CBTcpListenClientConnect			m_pCBClientConnect;
	CBTcpListenClientRcvData			m_pCBClientRcvData;
	CBTcpListenClientDisConnect			m_pCBClientDisConnect;
};

////////////////////////////////////////////////////////////////////////////////
typedef void (*CBSocketUdpRcvData) (u32 dwUserParam, SOCKHANDLE hUdpBindSocket, 
									char* pDataBuf, u32 dwLen,
									u32 dwSrcIp, u16 wSrcPort);

class TPSOCKET_API CUnifySocketUdpBindItem : public CUnifySocketBaseItem
{
public:
	CUnifySocketUdpBindItem(u32 dwUserParam = 0);
	virtual ~CUnifySocketUdpBindItem();

	SOCKHANDLE			CreatUdpBindSocket(u32 dwLocalIp, u16 wBindPort, 
											CBSocketUdpRcvData pcbRcvFun = NULL);

	BOOL32				SendData(const char* pData, u32 dwLen, u32 dwDstIp, u16 wDstPort);
	
	virtual void		CleanSocket();
	virtual void		Show();

	//内部使用
	void				CallBackRcvData(SOCKHANDLE hUdpBindSocket, 
										char* pDataBuf, u32 dwLen,
										u32 dwSrcIp, u16 wSrcPort);

protected:
	CUnifySocketUdpBindItem(const CUnifySocketUdpBindItem& );
	CUnifySocketUdpBindItem& operator=(const CUnifySocketUdpBindItem& );

	u16				m_wSocketPoolIndex;
	SOCKHANDLE		m_hUdpBindSocket;
	u32				m_dwUdpBindIp;
	u16				m_wUdpBindPort; // 本地绑定的端口
	
	CBSocketUdpRcvData		m_pCBRcvData;
};

#endif //_TP_SOCKET_H_