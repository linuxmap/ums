#include "osp.h"
#include "testmode.h"
#include "tpsocket.h"

BOOL32 g_bRun = TRUE;
int main()
{

	if(!OspInit( TRUE, 2510 ) )
	{
		printf("Osp Init failed! \n");
		return 1;
	}

	OspDelay(200);

	OspSetPrompt("TpTestServer");

	TestServerInit();

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

API void help()
{
	OspPrintf(1, 0, "\n");
	OspPrintf(1, 0, "quit                 -------quit test server\n");
	OspPrintf(1, 0, "showtest             -------show test server info\n");
	OspPrintf(1, 0, "logon                -------open test server log\n");
	OspPrintf(1, 0, "logoff               -------close test server log\n");
	OspPrintf(1, 0, "\n");
}