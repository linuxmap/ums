#include "osp.h"
#include "tptestapi.h"

BOOL32 g_bRun = TRUE;
int main()
{
	if(!OspInit( TRUE, 2500 ) )
	{
		printf("Osp Init failed! \n");
		return 1;
	}

	if (!tptest::TpTestClientInit("DCS2000V2")) //!!!!!πÃ∂®ÃÓ–¥DCS2000V2!!!!!
	{
		printf("TpTestClientInit failed! \n");
		OspQuit();
		return 1;
	}

	OspSetPrompt("TpTestClient");

	do 
	{
		OspDelay(1000);
	} while (g_bRun);

	OspQuit();
	OspDelay(1000);
	return 0;
}

API void quit()
{
	g_bRun = FALSE;
}

TPTESTHANDLE g_handle = INVAILD_TPTESTHANDLE;

u32			g_dwUser;

BOOL32 TestCBFun(
	TPTESTHANDLE hTpHandle,
	USERHANDLE hUserHandle,
	EmTpTestCBType	emCBType,
	s8 *pszBuf, 
	u32 nSize)
{
	OspPrintf(1, 0, "!!![TestCBFun Begin]!!!\n");
	OspPrintf(1, 0, "[TestCBFun] hTpHandle:%u, USERHANDLE:%p, emCBType:%d.\n", hTpHandle, hUserHandle, emCBType);
	if (pszBuf!=NULL)
	{
		OspPrintf(1, 0, "[TestCBFun] CB buf:%s, size:%d.\n", pszBuf, nSize);
	}
	OspPrintf(1, 0, "!!![TestCBFun End]!!!\n");
	return TRUE;
}

API void show()
{
	OspPrintf(1, 0, "g_dwUser addr:%p.\n", &g_dwUser);
	OspPrintf(1, 0, "g_handle:%u.\n", g_handle);
}

API void login()
{
	u32 dwIp = inet_addr("172.16.236.218");
	tptest::TpTestClientLogin(g_handle, dwIp, TestCBFun, (void*)&g_dwUser);
}

API void loginout()
{
	if (INVAILD_TPTESTHANDLE != g_handle)
	{
		tptest::TpTestClientLoginOut(g_handle);
		g_handle = INVAILD_TPTESTHANDLE;
	}
}

API void sendcom()
{
	s8 szBuf[]="test com data";
	tptest::TpTestClientComDataReq(g_handle, szBuf, sizeof(szBuf));
}

API void sendio()
{
	s8 szBuf[]="test io data";
	tptest::TpTestClientIODataReq(g_handle, szBuf, sizeof(szBuf));
}