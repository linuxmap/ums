#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "umsobject.h"
#include "umsconfig.h"
#include "tpmsginit.h"
#include "umscallinit.h"
#include "tpconfig.h"
#include "umsnetbufcfg.h"

#include "tpsys.h"
#include "tpstruct.h"
#include "umsapi.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif

s8* GetNetBufCfgFile()
{
	return emUmsBrdCfg;
}

int StartApp();
void StopApp();

BOOL32 g_bSysRuning = TRUE;

API void reboot()
{
	g_bSysRuning = FALSE;
}


int main(int argc, char* argv[])
{
	printf("\n\n\n");
	printf("\t**********************************************\n");
	printf("\t*                                            *\n");
	printf("\t*           KDV netbuf SYSTEM                *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");
	
// #ifdef _LINUX_ //异常捕获
// 	regist_exception(emUmsNetbufExeFileName, emUmsNetbufExceptionFileName);
// #endif

	//初始化OSP
	if(!OspInit( TRUE, TELNET_NETBUF_PORT ) )
	{
		printf("Osp Init failed! \n");
	}

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TpMakeDir("/usr/conf/");
#endif

#ifndef WIN32
	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
#endif
	OspSetPrompt("nb");
	
	setmdllogname(Ums_Mdl_Media, "[nb]");

	InitUmsEvent();

	
	
	//启动业务
	StartApp();

	while(g_bSysRuning)
	{
		OspDelay(100);
	}

	StopApp();

	return 0;
}


API BOOL StartupNetBuf();

namespace UmsTpmsg{
extern void regist_tpmsg_commond();
} //namespace UmsTpmsg

extern void regist_ums_mediatrans_commond();

API void RegAllXmlCommand();



API void showcfg();
extern void ReadNetbufCfg();
int StartApp()
{
	
#ifdef _DEBUG
	tplogon(0);
#endif

	regist_tpmsg_commond();

	regist_tp_commond();

	regist_ums_mediatrans_commond();

	RegAllXmlCommand();

	ReadNetbufCfg();

	StartupNetBuf();
	return 0;
}

API void StopNetBuf();
void StopApp()
{
	StopNetBuf();
	OspQuit();
}

