#include "tptestapi.h"
#include "testmode.h"

API void infolog(const s8* format,... );
API void errorlog( const s8* format,... );

extern	BOOL32	g_bTestInit;
CTPSHandleManger* CTPSHandleManger::m_pcInst = new CTPSHandleManger;

namespace tptest{

inline	BOOL32 CheckTPTestHandle(IN TPTESTHANDLE hHandle)
{
	if (!g_bTestInit){
		return FALSE;
	}

	if (!CTPSHandleManger::GetInst()->IsLoginOk(hHandle)){
		return FALSE;
	}

	return TRUE;
}

TPTEST_API BOOL32 TpTestClientInit(s8* szName)
{
	return TestClientInit(szName);
}

TPTEST_API BOOL32 TpTestClientLogin( OUT TPTESTHANDLE& hHandle, IN u32 dwIp, IN TPTestCBDefine fCB, IN USERHANDLE hUserHandle /*= NULL*/ )
{
	hHandle = INVAILD_TPTESTHANDLE;
	if (!g_bTestInit)
	{
		return FALSE;
	}

	if (0 == dwIp || NULL == fCB)
	{
		return FALSE;
	}

	hHandle = CTPSHandleManger::GetInst()->AssignHandle(dwIp);
	if (INVAILD_TPTESTHANDLE == hHandle)
	{
		return FALSE;
	}

	s8 szbuf[sizeof(u32)*3] = {0};

	memcpy(szbuf, &dwIp, sizeof(u32));
	memcpy(szbuf+sizeof(u32), &fCB, sizeof(u32));
	memcpy(szbuf+sizeof(u32)+sizeof(u32), &hUserHandle, sizeof(u32));

	OspPost(MAKEIID(TEST_MODE_CLIENT_APP_ID, hHandle), em_event_Login_Req, szbuf, sizeof(szbuf));

	return TRUE;
}

TPTEST_API BOOL32 TpTestClientLoginOut( IN TPTESTHANDLE hHandle )
{
	if (!CheckTPTestHandle(hHandle))
	{
		return FALSE;
	}

	if (!CTPSHandleManger::GetInst()->ReleaseHandle(hHandle)){
		return FALSE;
	}

	OspPost(MAKEIID(TEST_MODE_CLIENT_APP_ID, hHandle), em_event_Login_Quit, NULL, 0);

	return TRUE;
}

#define MAX_TEST_DATA_LEN		65535
static	s8 g_szData[MAX_TEST_DATA_LEN+1] = {0};

#define CLEAR_DATA				memset(g_szData, 0, sizeof(g_szData))

TPTEST_API BOOL32 TpTestClientComDataReq( IN TPTESTHANDLE hHandle, IN s8* szData, IN u16 wLen )
{
	if (!CheckTPTestHandle(hHandle))
	{
		return FALSE;
	}

	if (NULL == szData || 0 == wLen)
	{
		return FALSE;
	}

	CLEAR_DATA;
	memcpy(g_szData, szData, localmin(strlen(szData), MAX_TEST_DATA_LEN));

	OspPost(MAKEIID(TEST_MODE_CLIENT_APP_ID, hHandle), em_event_test_SendComData_Req, g_szData, strlen(g_szData)+1);

	return TRUE;
}

TPTEST_API BOOL32 TpTestClientIODataReq( IN TPTESTHANDLE hHandle, IN s8* szData, IN u16 wLen )
{
	if (!CheckTPTestHandle(hHandle))
	{
		return FALSE;
	}

	if (NULL == szData || 0 == wLen)
	{
		return FALSE;
	}

	CLEAR_DATA;
	memcpy(g_szData, szData, localmin(strlen(szData), MAX_TEST_DATA_LEN));

	OspPost(MAKEIID(TEST_MODE_CLIENT_APP_ID, hHandle), em_event_test_SendIOData_Req, g_szData, strlen(g_szData)+1);

	return TRUE;
}

}
