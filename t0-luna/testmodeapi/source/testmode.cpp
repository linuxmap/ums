#include "testmode.h"

CTestClientApp	g_cClientApp;
CLockSemHandle	g_cLock;
BOOL32			g_bTestInit = FALSE;
s8				g_szAuthClientName[TEST_MODE_BUF_LEN_32+1] = {0};

#define INVALID_U32	0xFFFFFFFF

BOOL32	g_bLogOn = FALSE;
API void infolog(const s8* format,... );
API void errorlog( const s8* format,... );
API void staticlog( const s8* format,... );

API BOOL32 TestClientInit(s8* szName /* = NULL */)
{
	g_cLock.LOCK();

	if (g_bTestInit)
	{
		g_cLock.UNLOCK();
		return TRUE;
	}

	if (!IsOspInitd())
	{
		if(!OspInit( TRUE, 2500 ) )
		{
			printf("Osp Init failed! \n");
			return 1;
		}
	}

	int ret = g_cClientApp.CreateApp("TestClient", TEST_MODE_CLIENT_APP_ID, 100);
	if (ret != OSP_OK)
	{
		g_cLock.UNLOCK();
		return FALSE;
	}

	if (NULL != szName)
	{
		memcpy(g_szAuthClientName, szName, localmin(strlen(szName), TEST_MODE_BUF_LEN_32));
	}

#if (defined(WIN32) || defined(_WIN32) ) && defined(_USRTPTESTDLL)
	OspRegistModule("tptestapi.dll");
#endif

#ifdef _LINUX_
	OspRegCommand("testhelp", (void*)testhelp, "testhelp");
	OspRegCommand("showtest", (void*)showtest, "showtest");
	OspRegCommand("logon", (void*)logon, "logon");
	OspRegCommand("logoff", (void*)logoff, "logoff");
#endif

	printf("TestClientInit is ok!\n");

	g_bTestInit = TRUE;

	g_cLock.UNLOCK();
	return TRUE;
}

CTestClientInstance::CTestClientInstance()
{
	ClearInst();
}

CTestClientInstance::~CTestClientInstance()
{
}

void CTestClientInstance::DaemonInstanceEntry(CMessage *const pMsg, CApp* pcApp)
{
	return;
}

void CTestClientInstance::InstanceEntry( CMessage *const pMsg )
{
	switch (pMsg->event)
	{
	case em_event_Login_Req:
		EventLoginReq(pMsg);
		break;
	case em_event_Login_Req_OK:
		EventLoginRspOk(pMsg);
		break;
	case em_event_Login_Req_Fail:
		EventLoginRspFail(pMsg);
		break;
	case em_event_test_SendComData_Req:
		EventTestComDataReq(pMsg);
		break;
	case em_event_test_SendComData_Req_OK:
		EventTestComDataRspOk(pMsg);
		break;
	case em_event_test_SendComData_Req_Fail:
		EventTestComDataRspFail(pMsg);
		break;
	case em_event_test_SendIOData_Req:
		EventTestIODataReq(pMsg);
		break;
	case em_event_test_SendIOData_Req_OK:
		EventTestIODataRspOk(pMsg);
		break;
	case em_event_test_SendIOData_Req_Fail:
		EventTestIODataRspFail(pMsg);
		break;
	case em_event_Login_Quit:
		EventLoginQuit(pMsg);
		break;
	case OSP_DISCONNECT:
		EventDisConnect(pMsg);
		break;
	default:
		errorlog("CTestModeInstance::DaemonInstanceEntry event(%d) is unkown!\n", pMsg->event);
		break;
	}
	return;
}

void CTestClientInstance::InstanceDump( u32 /*= 0*/ )
{
	if (inst_idle == CurState())
	{
		return;
	}
	Show();
	return;
}

#define MAX_TEST_MSG_LEN		65535
static	s8 g_sBuf[MAX_TEST_MSG_LEN+1] = {0};

#define CLEAR_BUF				memset(g_sBuf, 0, sizeof(g_sBuf))

u32		g_dwServerAppInst = MAKEIID(TEST_MODE_SERVER_APP_ID, CInstance::DAEMON);

void CTestClientInstance::EventLoginReq( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestClientInstance::EventLoginReq Inst:%d, msg:%d.\n", GetInsID(), wMsgLen);

	u32 dwServerIp = *(u32*)g_sBuf;
	TPTestCBDefine fCB = *(TPTestCBDefine*)(g_sBuf+sizeof(u32));
	USERHANDLE hUserHandle = *(USERHANDLE*)(g_sBuf+sizeof(u32)+sizeof(u32));

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};	 
	do 
	{
		if (inst_run==CurState())
		{
			memcpy(szFailBuf, BUF_ERROR_CLIENT_BUSY, sizeof(BUF_ERROR_CLIENT_BUSY));
			break;
		}

		m_dwServerNode = OspConnectTcpNode(dwServerIp, TEST_LISTEN_PORT);
		if (INVALID_NODE == m_dwServerNode)
		{
			memcpy(szFailBuf, BUF_ERROR_SERVER_UNREACHABLE, sizeof(BUF_ERROR_SERVER_UNREACHABLE));
			break;
		}

		OspNodeDiscCBReg(m_dwServerNode, TEST_MODE_CLIENT_APP_ID, GetInsID());

		NextState(inst_run);

		m_dwServerIp = dwServerIp;
		m_fCB = fCB;
		m_hUserHandle = hUserHandle;

		//
		post(g_dwServerAppInst, em_event_Login_Req, g_szAuthClientName, sizeof(g_szAuthClientName), m_dwServerNode);

		return;

	} while (0);

	errorlog("CTestClientInstance::EventLoginReq Fail buf %s!.\n", szFailBuf);

	CTPSHandleManger::GetInst()->ReleaseHandle(GetInsID());

	infolog("[Begin CB em_CBType_Login_Fail-%s!]\n", szFailBuf);
	(*fCB)(GetInsID(), hUserHandle, em_CBType_Login_Fail, szFailBuf, sizeof(szFailBuf));
	infolog("[End CB em_CBType_Login_Fail-%s!\n]", szFailBuf);

	return;
}

void CTestClientInstance::EventLoginRspOk( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestClientInstance::EventLoginRspOk Inst:%d, msg:%d-%s.\n", GetInsID(), wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventLoginRspOk inst %d not run.\n", GetInsID());
		return;
	}

	infolog("[Begin CB em_CBType_Login_OK!]\n");
	(*m_fCB)(GetInsID(), m_hUserHandle, em_CBType_Login_OK, NULL, 0);
	infolog("[End CB em_CBType_Login_OK!]\n");

	CTPSHandleManger::GetInst()->SetLoginOk(GetInsID());

	return;
}

void CTestClientInstance::EventLoginRspFail( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestClientInstance::EventLoginRspFail Inst:%d, msg:%d-%s.\n", GetInsID(), wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventLoginRspFail inst %d not run.\n", GetInsID());
		return;
	}

	OspDisconnectTcpNode(m_dwServerNode);

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};

	memcpy(szFailBuf, g_sBuf, localmin(wMsgLen, TEST_MODE_BUF_LEN_64));

	TPTestCBDefine	fcb = m_fCB;
	USERHANDLE cbHandle = m_hUserHandle;
	ClearInst();
	CTPSHandleManger::GetInst()->ReleaseHandle(GetInsID());
	
	infolog("[Begin CB em_CBType_Login_Fail-%s!]\n", szFailBuf);
	(*fcb)(GetInsID(), cbHandle, em_CBType_Login_Fail, szFailBuf, sizeof(szFailBuf));
	infolog("[End CB em_CBType_Login_Fail-%s!]\n", szFailBuf);

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
	infolog("CTestClientInstance::EventTestComDataReq msg:%d-%s.\n", wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventTestComDataReq inst %d not run.\n", GetInsID());
		return;
	}

	post(g_dwServerAppInst, em_event_test_SendComData_Req, g_sBuf, strlen(g_sBuf)+1, m_dwServerNode);

	return;
}

void CTestClientInstance::EventTestComDataRspOk( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestClientInstance::EventTestComDataRspOk msg:%d-%s.\n", wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventTestComDataRspOk inst %d not run.\n", GetInsID());
		return;
	}

	infolog("[Begin CB em_CBType_TestComData_Ok!]\n");
	(*m_fCB)(GetInsID(), m_hUserHandle, em_CBType_TestComData_Ok, NULL, 0);
	infolog("[End CB em_CBType_TestComData_Ok!]\n");

	return;
}

void CTestClientInstance::EventTestComDataRspFail( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestClientInstance::EventTestComDataRspFail msg:%d-%s.\n", wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventTestComDataRspFail inst %d not run.\n", GetInsID());
		return;
	}

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};

	memcpy(szFailBuf, g_sBuf, localmin(wMsgLen, TEST_MODE_BUF_LEN_64));

	infolog("[Begin CB em_CBType_TestComData_Fail-%s!]\n", szFailBuf);
	(*m_fCB)(GetInsID(), m_hUserHandle, em_CBType_TestComData_Fail, szFailBuf, sizeof(szFailBuf));
	infolog("[End CB em_CBType_TestComData_Fail-%s!]\n", szFailBuf);

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
	infolog("CTestClientInstance::EventTestIODataReq msg:%d-%s.\n", wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventTestIODataReq inst %d not run.\n", GetInsID());
		return;
	}

	post(g_dwServerAppInst, em_event_test_SendIOData_Req, g_sBuf, strlen(g_sBuf)+1, m_dwServerNode);

	return;
}

void CTestClientInstance::EventTestIODataRspOk( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestClientInstance::EventTestIODataRspOk msg:%d-%s.\n", wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventTestIODataRspOk inst %d not run.\n", GetInsID());
		return;
	}

	infolog("[Begin CB em_CBType_TestIOData_Ok!]\n");
	(*m_fCB)(GetInsID(), m_hUserHandle, em_CBType_TestIOData_Ok, NULL, 0);
	infolog("[End CB em_CBType_TestIOData_Ok!]\n");

	return;
}

void CTestClientInstance::EventTestIODataRspFail( CMessage *const pMsg )
{
	CLEAR_BUF;
	u16 wMsgLen = pMsg->length;
	if (0 != wMsgLen)
	{
		memcpy(g_sBuf, pMsg->content, localmin(wMsgLen, MAX_TEST_MSG_LEN));
	}
	infolog("CTestClientInstance::EventTestIODataRspFail msg:%d-%s.\n", wMsgLen, g_sBuf);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventTestIODataRspFail inst %d not run.\n", GetInsID());
		return;
	}

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};

	memcpy(szFailBuf, g_sBuf, localmin(wMsgLen, TEST_MODE_BUF_LEN_64));

	infolog("[Begin CB em_CBType_TestIOData_Fail-%s!]\n", szFailBuf);
	(*m_fCB)(GetInsID(), m_hUserHandle, em_CBType_TestIOData_Fail, szFailBuf, sizeof(szFailBuf));
	infolog("[End CB em_CBType_TestIOData_Fail-%s!]\n", szFailBuf);

	return;
}

void CTestClientInstance::EventLoginQuit( CMessage *const pMsg )
{
	if (inst_idle == CurState())
	{
		errorlog("CTestClientInstance::EventLoginQuit inst %d is idle!\n", GetInsID());
		return;
	}
	infolog("CTestClientInstance::EventLoginQuit Inst:%d.\n", GetInsID());
	
	post(g_dwServerAppInst, em_event_Login_Quit, g_szAuthClientName, sizeof(g_szAuthClientName), m_dwServerNode);
	OspDelay(100);
	OspDisconnectTcpNode(m_dwServerNode);

	Show();
	ClearInst();
	return;
}

void CTestClientInstance::EventDisConnect( CMessage *const pMsg )
{
	u32 dwNode = *(u32*)pMsg->content;
	infolog("CTestClientInstance::EventDisConnect Inst:%d, dwNode:%d.\n", GetInsID(), dwNode);

	if (inst_run!=CurState())
	{
		errorlog("CTestClientInstance::EventDisConnect inst %d not run.\n", GetInsID());
		return;
	}

	s8 szFailBuf[TEST_MODE_BUF_LEN_64+1] = {0};

	memcpy(szFailBuf, BUF_ERROR_SERVER_DISCONNECT, sizeof(BUF_ERROR_SERVER_DISCONNECT));

	TPTestCBDefine	fcb = m_fCB;
	USERHANDLE cbHandle = m_hUserHandle;
	ClearInst();
	CTPSHandleManger::GetInst()->ReleaseHandle(GetInsID());

	infolog("[Begin CB em_CBType_Login_Fail-%s!]\n", szFailBuf);
	(*fcb)(GetInsID(), cbHandle, em_CBType_Login_Fail, szFailBuf, sizeof(szFailBuf));
	infolog("[End CB em_CBType_Login_Fail-%s!]\n", szFailBuf);

	return;
}

void CTestClientInstance::Show()
{
	staticlog("[CTestClientInstance Inst Info]\n");
	staticlog("  Inst:%d, CurState:%d.\n", GetInsID(), CurState());
	staticlog("  m_dwServerIp:"u32IpForMat".\n", u32ToIp(m_dwServerIp));
	staticlog("  m_dwServerNode:%d.\n", m_dwServerNode);
	staticlog("  m_fCB:%p.\n", m_fCB);
	staticlog("  m_hUserHandle:%p.\n", m_hUserHandle);
	return;
}

void CTestClientInstance::ClearInst()
{
	NextState(inst_idle);
	m_dwServerIp = 0;
	m_dwServerNode = INVALID_NODE;

	m_fCB = NULL;
	m_hUserHandle = NULL;
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

API void testhelp()
{
	staticlog("showtest                    ------show test client info\n");
	staticlog("logon                       ------open test client log\n");
	staticlog("logoff                      ------close test client log\n");
}

API void showtest()
{
	CTPSHandleManger::GetInst()->Show();
	staticlog("\n");
	staticlog("g_bTestInit:%d.\n", g_bTestInit);
	staticlog("g_bLogOn:%d.\n", g_bLogOn);
	staticlog("g_szAuthClientName:%s.\n\n", g_szAuthClientName);

	for (u16 wIndex = 0; wIndex < TPTESTHANDLE_MAX_NUM; wIndex++)
	{
		OspInstDump(TEST_MODE_CLIENT_APP_ID, wIndex+1, 0);
		staticlog("\n");
	}
}

API void logon()
{
	g_bLogOn = TRUE;
}
API void logoff()
{
	g_bLogOn = FALSE;
}