#include "testmode.h"
#include "tpsocket.h"

CTestClientApp	g_cClientApp;
BOOL32			g_bTestInit = FALSE;
s8				g_szAuthClientName[] = "DCS2000V2";

#define INVALID_U32	0xFFFFFFFF

BOOL32	g_bLogOn = FALSE;
BOOL32	g_bTestCom = FALSE;
BOOL32	g_bTestIO = FALSE;
API void infolog(const s8* format,... );
API void errorlog( const s8* format,... );
API void staticlog( const s8* format,... );

void CBFunUdpRcvData(u32 dwUserParam, SOCKHANDLE hUdpBindSocket, 
	char* pDataBuf, u32 dwLen,
	u32 dwSrcIp, u16 wSrcPort)
{
	OspPrintf(1, 0, "[CBFunUdpRcvData Begin]\n");
	OspPrintf(1, 0, "  dwUserParam:%u, hUdpBindSocket:%d, pDataBuf:%s, dwLen:%d, ip:"UnifyIpForMat", port:%d\n", dwUserParam, 
		hUdpBindSocket, pDataBuf, dwLen, UnifyU32ToIp(dwSrcIp), wSrcPort);
	OspPrintf(1, 0, "[CBFunUdpRcvData End]\n");
}

CUnifySocketUdpBindItem		g_cUdp1;
CUnifySocketUdpBindItem		g_cUdp2;
CUnifySocketUdpBindItem		g_cUdp3;

u16	g_wTestPort1=20001;
u16	g_wTestPort2=20002;
u16	g_wTestPort3=20003;

u32 g_dwDstIp=inet_addr("127.0.0.1");

API void showsock()
{
	UnifySocketPoolShow();
	OspPrintf(1, 0, "\n");
	OspPrintf(1, 0, "g_dwDstIp:"UnifyIpForMat"\n", UnifyU32ToIp(g_dwDstIp));
	OspPrintf(1, 0, "\n");
	g_cUdp1.Show();
	OspPrintf(1, 0, "\n");
	g_cUdp2.Show();
	OspPrintf(1, 0, "\n");
	g_cUdp3.Show();
}


API void setdstip(s8* szIp)
{
	if (NULL!=szIp)
	{
		g_dwDstIp = inet_addr(szIp);
	}
}

API void testudp(s8* szData, u16 wPort)
{
	if (NULL != szData)
	{
		g_cUdp1.SendData(szData, strlen(szData)+1, g_dwDstIp, wPort);
		g_cUdp2.SendData(szData, strlen(szData)+1, g_dwDstIp, wPort);
		g_cUdp3.SendData(szData, strlen(szData)+1, g_dwDstIp, wPort);
	}
}

API void TestServerInit()
{
	if (g_bTestInit)
	{
		return;
	}

	if (!UnifySocketMoudleInit())
	{
		return;
	}

	int ret = g_cClientApp.CreateApp("TestMode", TEST_MODE_SERVER_APP_ID, 100);
	if (ret != OSP_OK)
	{
		return;
	}

	OspCreateTcpNode(0, TEST_LISTEN_PORT);

#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help");
	OspRegCommand("quit", (void*)quit, "quit");
	OspRegCommand("showtest", (void*)showtest, "showtest");

	OspRegCommand("logon", (void*)logon, "logon");
	OspRegCommand("logoff", (void*)logoff, "logoff");
	OspRegCommand("login", (void*)login, "login");
	OspRegCommand("loginout", (void*)loginout, "loginout");
	OspRegCommand("sendcom", (void*)sendcom, "sendcom");
	OspRegCommand("sendio", (void*)sendio, "sendio");

	OspRegCommand("showsock", (void*)showsock, "showsock");
	OspRegCommand("setdstip", (void*)setdstip, "setdstip");
	OspRegCommand("testudp", (void*)testudp, "testudp");
#endif

	printf("TestModeInit is ok!\n");

	g_cUdp1.ResetUserParam(g_wTestPort1);
	g_cUdp1.CreatUdpBindSocket(0, g_wTestPort1, CBFunUdpRcvData);

	g_cUdp2.ResetUserParam(g_wTestPort2);
	g_cUdp2.CreatUdpBindSocket(0, g_wTestPort2, CBFunUdpRcvData);

	g_cUdp3.ResetUserParam(g_wTestPort3);
	g_cUdp3.CreatUdpBindSocket(0, g_wTestPort3, CBFunUdpRcvData);

	g_bTestInit = TRUE;

	return;
}

CTestClientInstance::CTestClientInstance()
{
	ClearClient();
}

CTestClientInstance::~CTestClientInstance()
{
}

void CTestClientInstance::DaemonInstanceEntry(CMessage *const pMsg, CApp* pcApp)
{
	if (OSP_DISCONNECT == pMsg->event)
	{
		EventDisConnect(pMsg);
		return;
	}

	u16 wSrcApp = GETAPP(pMsg->srcid);
	if (wSrcApp != TEST_MODE_CLIENT_APP_ID)
	{
		errorlog("CTestModeInstance::DaemonInstanceEntry app(%d) is unkown!\n", wSrcApp);
		OspDisconnectTcpNode(pMsg->srcnode);
		return;
	}

	switch (pMsg->event)
	{
	case em_event_Login_Req:
		EventLoginReq(pMsg);
		break;
	case em_event_test_SendComData_Req:
		EventTestComDataReq(pMsg);
		break;
	case em_event_test_SendIOData_Req:
		EventTestIODataReq(pMsg);
		break;
	case em_event_Login_Quit:
		EventLoginQuit(pMsg);
		break;
	default:
		errorlog("CTestModeInstance::DaemonInstanceEntry event(%d) is unkown!\n", pMsg->event);
		break;
	}
	return;
}

void CTestClientInstance::DaemonInstanceDump( u32 /*= 0*/ )
{
	Show();
	return;
}

#define MAX_TEST_MSG_LEN		65535
static	s8 g_sBuf[MAX_TEST_MSG_LEN+1] = {0};

#define CLEAR_BUF				memset(g_sBuf, 0, sizeof(g_sBuf))

void CTestClientInstance::EventLoginReq( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestModeInstance::EventLoginReq msg:%d-%s.\n", wMsgLen, g_sBuf);

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};	 
	do 
	{
		if (inst_run==CurState())
		{
			memcpy(szFailBuf, BUF_ERROR_CLIENT_FULL, sizeof(BUF_ERROR_CLIENT_FULL));
			break;
		}

		if (strlen(g_sBuf) != strlen(g_szAuthClientName)
			|| 0 != strncmp(g_sBuf, g_szAuthClientName, sizeof(g_szAuthClientName)))
		{
			memcpy(szFailBuf, BUF_ERROR_CLIENT_UNKOWN, sizeof(BUF_ERROR_CLIENT_UNKOWN));
			break;
		}

		NextState(inst_run);

		m_dwClientAppInstId = pMsg->srcid;
		m_dwClientNode = pMsg->srcnode;
		memcpy(m_szClientName, g_sBuf, TEST_MODE_CLIEN_NAME_LEN);
		
		OspNodeDiscCBReg(m_dwClientNode, TEST_MODE_SERVER_APP_ID, CInstance::DAEMON);

		TOspNodeAddr tAddr;
		OspGetNodeAddr(m_dwClientNode, &tAddr);
		m_dwClientIp = tAddr.m_dwPeerIP;

		post(m_dwClientAppInstId, em_event_Login_Req_OK, NULL, 0, m_dwClientNode);

		return;

	} while (0);

	errorlog("CTestModeInstance::EventLoginReq Fail buf %s!.\n", szFailBuf);

	post(pMsg->srcid, em_event_Login_Req_Fail, szFailBuf, sizeof(szFailBuf), pMsg->srcnode);

	return;
}

void CTestClientInstance::EventTestComDataReq( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestModeInstance::EventTestComDataReq msg:%d-%s.\n", wMsgLen, g_sBuf);

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};	 
	do 
	{
		if (inst_run!=CurState())
		{
			memcpy(szFailBuf, BUF_ERROR_CLIENT_NOTLOGIN, sizeof(BUF_ERROR_CLIENT_NOTLOGIN));
			break;
		}

		OspDelay(1000);

		if (g_bTestCom)
		{
			memcpy(szFailBuf, BUF_ERROR_CLIENT_COMDATA, sizeof(BUF_ERROR_CLIENT_COMDATA));
			post(m_dwClientAppInstId, em_event_test_SendComData_Req_Fail, szFailBuf, sizeof(szFailBuf), m_dwClientNode);
		}
		else
		{
			post(m_dwClientAppInstId, em_event_test_SendComData_Req_OK, NULL, 0, m_dwClientNode);
		}

		return;

	} while (0);

	errorlog("CTestModeInstance::EventTestComDataReq Fail buf %s!.\n", szFailBuf);

	post(pMsg->srcid, em_event_test_SendComData_Req_Fail, szFailBuf, sizeof(szFailBuf), pMsg->srcnode);

	return;
}

void CTestClientInstance::EventTestIODataReq( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestModeInstance::EventTestIODataReq msg:%d-%s.\n", wMsgLen, g_sBuf);

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};	 
	do 
	{
		if (inst_run!=CurState())
		{
			memcpy(szFailBuf, BUF_ERROR_CLIENT_NOTLOGIN, sizeof(BUF_ERROR_CLIENT_NOTLOGIN));
			break;
		}

		OspDelay(1000);

		if (g_bTestIO)
		{
			memcpy(szFailBuf, BUF_ERROR_CLIENT_IODATA, sizeof(BUF_ERROR_CLIENT_IODATA));
			post(m_dwClientAppInstId, em_event_test_SendIOData_Req_Fail, szFailBuf, sizeof(szFailBuf), m_dwClientNode);
		}
		else
		{
			post(m_dwClientAppInstId, em_event_test_SendIOData_Req_OK, NULL, 0, m_dwClientNode);
		}

		return;

	} while (0);

	errorlog("CTestModeInstance::EventTestIODataReq Fail buf %s!.\n", szFailBuf);

	post(pMsg->srcid, em_event_test_SendIOData_Req_Fail, szFailBuf, sizeof(szFailBuf), pMsg->srcnode);

	return;
}

void CTestClientInstance::EventLoginQuit( CMessage *const pMsg )
{
	infolog("CTestModeInstance::EventLoginQuit srcnode:%d.\n", pMsg->srcnode);
	Show();
	ClearClient();
	return;
}

void CTestClientInstance::EventDisConnect( CMessage *const pMsg )
{
	u32 dwNode = *(u32*)pMsg->content;
	infolog("CTestModeInstance::EventDisConnect dwNode:%d.\n", dwNode);
	Show();
	ClearClient();
	return;
}

void CTestClientInstance::Show()
{
	staticlog("[CTestClientInstance Daemon Info]\n");
	staticlog("  CurState:%d.\n", CurState());
	staticlog("  m_dwClientIp:"u32IpForMat".\n", u32ToIp(m_dwClientIp));
	staticlog("  m_dwClientInstId:%0x(%d-%d).\n", m_dwClientAppInstId, GETAPP(m_dwClientAppInstId), GETINS(m_dwClientAppInstId));
	staticlog("  m_dwClientNode:%d.\n", m_dwClientNode);
	staticlog("  m_szClientName:%s.\n", m_szClientName);
	return;
}

void CTestClientInstance::ClearClient()
{
	NextState(inst_idle);
	m_dwClientIp = 0;
	m_dwClientAppInstId = INVALID_U32;
	m_dwClientNode = INVALID_NODE;
	memset(m_szClientName, 0, sizeof(m_szClientName));
	return;
}

API void infolog( const s8* format,... )
{
	if (!g_bLogOn)
	{
		return;
	}
#define MAX_ONE_LOG_LEN		512
	s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
	va_list args;
	va_start(args,format);
	u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
	va_end(args);
	if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
	{
		return;
	}
	OspPrintf(1, 0, "[Info] %s", abuf);
//	printf("%s", abuf);
	return;
}

API void errorlog( const s8* format,... )
{
#define MAX_ONE_LOG_LEN		512
	s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
	va_list args;
	va_start(args,format);
	u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
	va_end(args);
	if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
	{
		return;
	}
	OspPrintf(1, 0, "[Error] %s", abuf);
//	printf("%s", abuf);
	return;
}

API void staticlog( const s8* format,... )
{
#define MAX_ONE_LOG_LEN		512
	s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
	va_list args;
	va_start(args,format);
	u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
	va_end(args);
	if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
	{
		return;
	}
	OspPrintf(1, 0, "[Static] %s", abuf);
//	printf("%s", abuf);
	return;
}

API void showtest()
{
	staticlog("g_bTestInit:%d.\n", g_bTestInit);
	staticlog("g_bLogOn:%d.\n", g_bLogOn);
	staticlog("g_szAuthClientName:%s.\n", g_szAuthClientName);
	staticlog("g_bTestCom:%d.\n", g_bTestCom);
	staticlog("g_bTestIO:%d.\n\n", g_bTestIO);

	OspInstDump(TEST_MODE_SERVER_APP_ID, CInstance::DAEMON, 0);
}

API void logon()
{
	g_bLogOn = TRUE;
}
API void logoff()
{
	g_bLogOn = FALSE;
}

API void login()
{
	s8 szName[] = "DCS2000V2";
	OspPost(MAKEIID(TEST_MODE_SERVER_APP_ID, CInstance::DAEMON), em_event_Login_Req, szName, strlen(szName), 0, MAKEIID(TEST_MODE_CLIENT_APP_ID, 1));
}

API void loginout()
{
	s8 szName[] = "DCS2000V2";
	OspPost(MAKEIID(TEST_MODE_SERVER_APP_ID, CInstance::DAEMON), em_event_Login_Quit, szName, strlen(szName), 0, MAKEIID(TEST_MODE_CLIENT_APP_ID, 1));
}

API void sendcom()
{
	if (g_bTestCom)
	{
		g_bTestCom = FALSE;
	}
	else
	{
		g_bTestCom = TRUE;
	}
	staticlog("g_bTestCom:%d.\n", g_bTestCom);
}

API void sendio()
{
	if (g_bTestIO)
	{
		g_bTestIO = FALSE;
	}
	else
	{
		g_bTestIO = TRUE;
	}
	staticlog("g_bTestIO:%d.\n", g_bTestIO);
}