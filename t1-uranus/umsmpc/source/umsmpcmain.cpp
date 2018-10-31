#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "umsobject.h"
#include "tpmsginit.h"
#include "mpccfg.h"
#include "umsmpcinst.h"
#include "tpsys.h"
#include "tpstruct.h"
#include "umsapi.h"
#include "umsboardinst.h"
#include "umsboardcfg.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif

namespace UmsTpmsg{
extern void regist_tpmsg_commond();
} //namespace UmsTpmsg

s8* GetMpcCfgFile()
{
	return emUmsBrdCfg;
}

int StartApp(u32 dwNode);
void StopApp();

BOOL32 g_bSysRuning = TRUE;
u32	g_dwUmsNode = INVALID_NODE;
BOOL32 g_bCreatApp = TRUE;

API void RegAllXmlCommand();
API void reboot()
{
	g_bSysRuning = FALSE;
}
API void help();
API void showcfg();
API void showmpc(  );
API void setumsip( s8* uIp );
API void setmpcalias(s8* mpcalias);
API void ver();
API void showms();

int main(int argc, char* argv[])
{
	printf("\n\n\n");
	printf("\t**********************************************\n");
	printf("\t*                                            *\n");
	printf("\t*           KDV mpc SYSTEM                   *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");

#ifdef _LINUX_ //异常捕获
	regist_exception(emUmsmpcExeFileName, emUmsmpcExceptionFileName);
#endif
	
	//初始化OSP
	if(!OspInit( TRUE, TELNET_MPC_PORT ) )
	{
		printf("Osp Init failed! \n");
	}

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TpMakeDir("/usr/conf/");
#endif
	
	setmdllogname(Ums_Mdl_Mpc, "[Mpc]");
	
	InitUmsEvent();
#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");
	OspRegCommand("showcfg", (void*)showcfg, "showcfg()");
	OspRegCommand("reboot", (void*)reboot, "reboot()");
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("setumsip", (void*)setumsip, "setumsip(s8* uIp)");
	OspRegCommand("showmpc", (void*)showmpc, "showmpc(s8* uIp)");
	OspRegCommand("setmpcalias", (void*)setmpcalias, "setmpcalias(s8* mpcalias)");
	OspRegCommand("showms", (void*)showms, "showms()");
#endif
	
#ifdef _DEBUG
	tplogon(0);
#endif
	
	regist_tpmsg_commond();
	regist_tp_commond();

	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
	OspSetPrompt("UmsMpc");
	RegAllXmlCommand();

	StartApp(g_dwUmsNode);

	while(g_bSysRuning)
	{
		OspDelay(100);
	}
	
	StopApp();
	
	return 0;
}

#define VER_umsmpc_ver   UMS_VerID
API void ver()
{
	msgprint("umsmpc ver: %s  compile time: %s, %s\n", VER_umsmpc_ver, __DATE__,  __TIME__);
}

API void help()
{	
	msgprint("reboot()                      --- 重启umsmpc\n");
	msgprint("ver()							--- 显示umsmpc版本号\n");
	msgprint("showcfg()						--- 显示umsmpc配置信息\n");
	msgprint("setumsip( s8* uIp )           --- 设置umsmpc注册IP\n");
	msgprint("setmpcalias(s8* mpcalias)     --- 设置umsmpcC外设别名\n");
	msgprint("showmpc( )					--- 显示umsmpc信息\n");
	msgprint("showms()                      --- 显示当前MS灯状态.\n");
}
int StartApp(u32 dwNode)
{
	g_dwUmsNode = dwNode;
	ReadMpcCfg();

	//启动APP
	StartMpcServer();
	return 0;
}

void StopApp()
{
	//停止APP
	StopMpcServer();
	OspQuit();
}
