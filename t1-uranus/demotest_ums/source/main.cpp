#include "osp.h"
#include "tpsocket.h"

#ifdef _MSC_VER
#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "tpsocket.lib")
#endif

BOOL32 g_bRun = TRUE;

CUnifySocketUdpBindItem		g_cUdp1;
CUnifySocketUdpBindItem		g_cUdp2;
CUnifySocketUdpBindItem		g_cUdp3;

CUnifySocketTcpConnectItem		g_cTcpConnect;

CUnifySocketTcpListenItem		g_cTcpListen;

#define USEPARM_UDP_BEGIN	1000

#define USEPARM_TCP_CONNECT_BEGIN	2000

#define USEPARM_TCP_LISTEN_BEGIN	3000

static s8* getuserparamname(u32 dwParam)
{
	if (dwParam>=USEPARM_UDP_BEGIN 
		&& dwParam<USEPARM_TCP_CONNECT_BEGIN)
	{
		return "UDP";
	}
	else if(dwParam>=USEPARM_TCP_CONNECT_BEGIN
		&& dwParam<USEPARM_TCP_LISTEN_BEGIN)
	{
		return "TCPCONNECT";
	}
	else if (dwParam>=USEPARM_TCP_LISTEN_BEGIN)
	{
		return "TCPLISTEN";
	}
	else
	{
		return "UNKOWN";
	}
}

#ifdef _LINUX_
u32 g_dwDstIp=inet_addr("172.16.160.215");
#else
u32 g_dwDstIp=inet_addr("172.16.160.160");
#endif

void CBFunUdpRcvData(u32 dwUserParam, SOCKHANDLE hUdpBindSocket, 
	char* pDataBuf, u32 dwLen,
	u32 dwSrcIp, u16 wSrcPort)
{
	OspPrintf(1, 0, "[CBFunUdpRcvData Begin]\n");
	OspPrintf(1, 0, "  dwUserParam:%u-%s, hUdpBindSocket:%d, ip:"UnifyIpForMat", port:%d\n", dwUserParam, getuserparamname(dwUserParam),
		hUdpBindSocket, UnifyU32ToIp(dwSrcIp), wSrcPort);
	UnifySocketDumpMsg(pDataBuf, dwLen);
	OspPrintf(1, 0, "[CBFunUdpRcvData End]\n");
}

void CBFunTcpClientConnect(u32 dwUserParam, SOCKHANDLE hClientSocket, u32 dwClientIp, u16 wClientIndex)
{
	OspPrintf(1, 0, "[CBFunTcpClientConnect Begin]\n");
	OspPrintf(1, 0, "  dwUserParam:%u-%s, wClientIndex:%d, hClientSocket:%d, dwClientIp:"UnifyIpForMat".\n", dwUserParam, getuserparamname(dwUserParam), 
		wClientIndex, hClientSocket, UnifyU32ToIp(dwClientIp));
	if (g_cTcpListen.IsUsed())
	{
		s8 szHello[] = "hello client!";
		g_cTcpListen.SendData(hClientSocket, szHello, strlen(szHello));
	}
	OspPrintf(1, 0, "[CBFunTcpClientConnect End]\n");
}

void CBFunTcpRcvData(u32 dwUserParam, SOCKHANDLE hSocket, char* pDataBuf, u32 dwLen)
{
	OspPrintf(1, 0, "[CBFunTcpRcvData Begin]\n");
	OspPrintf(1, 0, "  dwUserParam:%u-%s, hSocket:%d.\n", dwUserParam, getuserparamname(dwUserParam), 
		hSocket);
	UnifySocketDumpMsg(pDataBuf, dwLen);
	OspPrintf(1, 0, "[CBFunTcpRcvData End]\n");
}

void CBFunTcpDisconnect(u32 dwUserParam, SOCKHANDLE hSocket)
{
	OspPrintf(1, 0, "[CBFunTcpDisconnect Begin]\n");
	OspPrintf(1, 0, "  dwUserParam:%u-%s, hSocket:%d.\n", dwUserParam, getuserparamname(dwUserParam), 
		hSocket);
	OspPrintf(1, 0, "[CBFunTcpDisconnect End]\n");
}

API void testquit()
{
	g_bRun = FALSE;
}

API void show()
{
	OspPrintf(1, 0, "[UDP]\n");
	g_cUdp1.Show();
	g_cUdp2.Show();
	g_cUdp3.Show();

	OspPrintf(1, 0, "\n[TCPCONNECT]\n");
	g_cTcpConnect.Show();

	OspPrintf(1, 0, "[TCPLISTEN]\n");
	g_cTcpListen.Show();
}

API void showdst()
{	
	OspPrintf(1, 0, "g_dwDstIp:"UnifyIpForMat"\n\n", UnifyU32ToIp(g_dwDstIp));
}

API void showsock()
{
	UnifySocketPoolShow();
}

API void setdst(s8* szIp)
{
	if (NULL!=szIp)
	{
		g_dwDstIp = inet_addr(szIp);
	}
	else
	{
		if (g_dwDstIp == inet_addr("172.16.160.160"))
		{
			g_dwDstIp=inet_addr("172.16.160.215");
		}
		else
		{
			g_dwDstIp=inet_addr("172.16.160.160");
		}
	}
	showdst();
}

#define CHECK_PORT_IS_VALID(wPort)	if(0==(wPort)) return;

API void bindudp(u16 wPort)
{
	CHECK_PORT_IS_VALID(wPort);

	if (!g_cUdp1.IsUsed())
	{
		g_cUdp1.ResetUserParam(USEPARM_UDP_BEGIN);
		g_cUdp1.CreatUdpBindSocket(0, wPort, CBFunUdpRcvData);
	}

	if (!g_cUdp2.IsUsed())
	{
		g_cUdp2.ResetUserParam(USEPARM_UDP_BEGIN+1);
		g_cUdp2.CreatUdpBindSocket(0, wPort+1, CBFunUdpRcvData);
	}

	if (!g_cUdp3.IsUsed())
	{
		g_cUdp3.ResetUserParam(USEPARM_UDP_BEGIN+2);
		g_cUdp3.CreatUdpBindSocket(0, wPort+2, CBFunUdpRcvData);
	}
}

API void clearudp()
{
	if (g_cUdp1.IsUsed())
		g_cUdp1.CleanSocket();
	if (g_cUdp2.IsUsed())
		g_cUdp2.CleanSocket();
	if (g_cUdp3.IsUsed())
		g_cUdp3.CleanSocket();
}

API void testudp(s8* szData, u16 wPort)
{
	CHECK_PORT_IS_VALID(wPort);
	if (NULL != szData)
	{
		if (g_cUdp1.IsUsed())
			g_cUdp1.SendData(szData, strlen(szData), g_dwDstIp, wPort);
		if (g_cUdp2.IsUsed())
			g_cUdp2.SendData(szData, strlen(szData), g_dwDstIp, wPort);
		if (g_cUdp3.IsUsed())
			g_cUdp3.SendData(szData, strlen(szData), g_dwDstIp, wPort);
	}
}

API void tcpconnect(u16 wPort)
{
	CHECK_PORT_IS_VALID(wPort);
	if (!g_cTcpConnect.IsUsed())
	{
		g_cTcpConnect.ResetUserParam(USEPARM_TCP_CONNECT_BEGIN);
		g_cTcpConnect.CreatConnectSocket(g_dwDstIp, wPort, CBFunTcpRcvData, CBFunTcpDisconnect);
	}
}

API void tcpdisconnect()
{
	if (g_cTcpConnect.IsUsed())
	{
		g_cTcpConnect.CleanSocket();
	}
}

API void testtcp(s8* szData)
{
	if (g_cTcpConnect.IsUsed() && NULL != szData)
	{
		g_cTcpConnect.SendData(szData, strlen(szData));
	}
}

API void tcplisten(u16 wPort)
{
	CHECK_PORT_IS_VALID(wPort);
	if (!g_cTcpListen.IsUsed())
	{	
		g_cTcpListen.ResetUserParam(USEPARM_TCP_LISTEN_BEGIN);
		g_cTcpListen.CreatListenSocket(0,wPort,CBFunTcpClientConnect,CBFunTcpRcvData,CBFunTcpDisconnect);
	}
}

API void clearlisten()
{
	if (g_cTcpListen.IsUsed())
	{
		g_cTcpListen.CleanSocket();
	}
}

API void testclient(SOCKHANDLE hSock, s8* szData)
{
	if (g_cTcpListen.IsUsed() && NULL != szData && INVALID_SOCKET != hSock)
	{
		g_cTcpListen.SendData(hSock, szData, strlen(szData));
	}
}

API void help()
{
	OspPrintf(1, 0, "void help()\n");
	OspPrintf(1, 0, "void testquit()\n");
	OspPrintf(1, 0, "void show()\n");
	OspPrintf(1, 0, "void showsock()\n");
	OspPrintf(1, 0, "void setdst(s8* szIp)\n\n");

	OspPrintf(1, 0, "void bindudp(u16 wPort)\n");
	OspPrintf(1, 0, "void clearudp()\n");
	OspPrintf(1, 0, "void testudp(s8* szData, u16 wPort)\n\n");

	OspPrintf(1, 0, "void tcpconnect(u16 wPort)\n");
	OspPrintf(1, 0, "void tcpdisconnect()\n");
	OspPrintf(1, 0, "void testtcp(s8* szData)\n\n");


	OspPrintf(1, 0, "void tcplisten(u16 wPort)\n");
	OspPrintf(1, 0, "void clearlisten()\n");
	OspPrintf(1, 0, "void testclient(SOCKHANDLE hSock, s8* szData)\n");
}

int main()
{
	if (!OspInit(TRUE, 2520))
		return -1;
	OspSetPrompt("umsdemo");
	OspDelay(200);

	if (!UnifySocketMoudleInit(6666))
		return -1;

#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help");
	OspRegCommand("testquit", (void*)testquit, "testquit");
	OspRegCommand("show", (void*)show, "show");
	OspRegCommand("showdst", (void*)showdst, "showdst");
	OspRegCommand("showsock", (void*)showsock, "showsock");
	OspRegCommand("setdst", (void*)setdst, "setdst");

	OspRegCommand("bindudp", (void*)bindudp, "bindudp");
	OspRegCommand("clearudp", (void*)clearudp, "clearudp");
	OspRegCommand("testudp", (void*)testudp, "testudp");

	OspRegCommand("tcpconnect", (void*)tcpconnect, "tcpconnect");
	OspRegCommand("tcpdisconnect", (void*)tcpdisconnect, "tcpdisconnect");
	OspRegCommand("testtcp", (void*)testtcp, "testtcp");

	OspRegCommand("tcplisten", (void*)tcplisten, "tcplisten");
	OspRegCommand("clearlisten", (void*)clearlisten, "clearlisten");
	OspRegCommand("testclient", (void*)testclient, "testclient");
#endif

	do 
	{
		OspDelay(100);
	} while (g_bRun);

	OspQuit();
	OspDelay(2000);

	return 0;
}