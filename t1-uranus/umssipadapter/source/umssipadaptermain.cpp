#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "umsobject.h"
#include "umsconfig.h"
#include "tpmsginit.h"
#include "umscallinit.h"
#include "tpconfig.h"
#include "adaptercfg.h"

#include "tpsys.h"
#include "tpstruct.h"
#include "umsapi.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif

BOOL32	g_bKedaManuOn = FALSE;

s8* GetAdapterCfgFile()
{
	return emUmsBrdCfg;
}


int StartApp();
void StopApp();

BOOL32 g_bSysRuning = TRUE;
BOOL32 g_bShowSendMsgInfo = FALSE;
u32  g_dwListenIp = 0;


API void reboot()
{
	g_bSysRuning = FALSE;
}

API void showcallinfo();

int main(int argc, char* argv[])
{
	printf("\n\n\n");
	printf("\t**********************************************\n");
	printf("\t*                                            *\n");
	printf("\t*           KDV SipAdapter SYSTEM            *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");
	
// #ifdef _LINUX_ //异常捕获
// #ifdef _USE_LOG4CPLUS_
// 	regist_exception(emUmsSipAdapterLog4cpExeFileName, emUmsSipAdapterLog4cpExceptionFileName);
// #else
// 	regist_exception(emUmsSipAdapterExeFileName, emUmsSipAdapterExceptionFileName);
// #endif
// #endif

	//初始化OSP
	if(!OspInit( TRUE, TELNET_SIPADAPTE_PORT ) )
	{
		printf("Osp Init failed! \n");
	}

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TpMakeDir("/usr/conf/");
	TBrdE2PromInfo tInfo;
	BrdGetE2PromInfo(&tInfo);
	if (tInfo.dwProductId == BRD_PID_IS2_KedaManu)
	{
		g_bKedaManuOn = TRUE;
		printf("IS2.2 keda manu is ON! \n");
	}
#endif
	 

#ifdef _USE_LOG4CPLUS_
	initLog4CPlusLog(emUmssipadapterLog4cplusCfg, "umssipadapter");
#else
	initKdvLog(emUmsSipAdapterLogCfgFileName);
#endif//_USE_LOG4CPLUS_

	setmdllogname(Ums_Mdl_Stack, "[Stack]");

#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	g_dwListenIp = 0;
#else
	g_dwListenIp = CTpTypeAdpt::GetLocalIP(0,2);
	if (0 == g_dwListenIp)
	{
		g_dwListenIp = CTpTypeAdpt::GetLocalIP(1,2);
	}
#endif//(_PPC_82XX_) || defined(_PPC_85XX_)
#else
	g_dwListenIp = 0;
#endif //_LINUX_

#ifdef _DEBUG
	tploglow(0);
#else
	tplogoff();
#endif
	
	OspDelay(100);
	msgprint("\t**********************************************\n");
	msgprint("\t*                                            *\n");
	msgprint("\t*       KDV umssipadapter Starting ...       *\n");
	msgprint("\t*                                            *\n");
	msgprint("\t**********************************************\n");

	InitUmsEvent();

#ifndef WIN32
	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
#endif

	OspSetPrompt("umsadapter");
	
	//启动业务
	StartApp();

	while(g_bSysRuning)
	{
		OspDelay(100);
	}

	StopApp();

	return 0;
}


API BOOL StartupTpServer();

namespace UmsTpmsg{
extern void regist_tpmsg_commond();
} //namespace UmsTpmsg


extern void regist_ums_sipadapter_commond();

API void RegAllXmlCommand();

API void help()
{	
	msgprint("reboot()                        --- 重启UMS\n");
	msgprint("ver()                           --- 显示umsadpater版本号\n");
	msgprint("showcfg()                       --- 显示配置信息\n");
	msgprint("showpid()                       --- 显示板卡信息\n");
	msgprint("setlistenip(s8* pszIp)          --- 设置监听ip\n");
	msgprint("showlistenip()                  --- 查询监听ip信息\n");
}

API void loglog()
{
	SetLogFlush();
}

API void showsendmsg(BOOL32 bShow)
{
	g_bShowSendMsgInfo = bShow?TRUE:FALSE;
	msgprint("g_bShowSendMsgInfo = %d.\n", g_bShowSendMsgInfo);
}

API void showcfg();
API void showpid();
API void setmanuon(BOOL32 bManuON);

API void setlistenip(s8* pszIp);
API void showlistenip(void);


int StartApp()
{
#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");
	OspRegCommand("showcfg", (void*)showcfg, "showcfg()");
	OspRegCommand("reboot", (void*)reboot, "reboot()");
	OspRegCommand("loglog", (void*)loglog, "loglog()");
	OspRegCommand("showsendmsg", (void*)showsendmsg, "showsendmsg()");
	OspRegCommand( "showpid", (void*)showpid, "showpid()");
	OspRegCommand("setmanuon", (void*)setmanuon, "setmanuon");
	OspRegCommand("showcallinfo", (void*)showcallinfo, "showcallinfo()");

	OspRegCommand("setlistenip", (void*)setlistenip, "setlistenip(s8* pszIp)");
	OspRegCommand("showlistenip", (void*)showlistenip, "showlistenip()");
#endif
	
#ifdef _DEBUG
	tplogon(0);
#endif

	regist_tpmsg_commond();

	regist_tp_commond();

	regist_ums_sipadapter_commond();

	RegAllXmlCommand();

	ReadAdapterCfg();

	StartupTpServer();
	return 0;
}

API void StopAdapterService();
void StopApp()
{
	StopAdapterService();

	SetLogFlush();
	ExitKdvLog();

	OspQuit();
}

API void showpid()
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TBrdE2PromInfo tInfo;
	BrdGetE2PromInfo(&tInfo);
	msgprintnotime("dwHardwareVersion:	0x%04x\n", tInfo.dwHardwareVersion);
	msgprintnotime("dwDeviceCode:		0x%04x\n", tInfo.dwDeviceCode);
	msgprintnotime("dwProductId:		0x%04x\n", tInfo.dwProductId);
	msgprintnotime("dwHWSubVersion:		0x%x\n", tInfo.dwHWSubVersion);
	msgprintnotime("dwProductDate:		0x%x\n", tInfo.dwProductDate);
	msgprintnotime("CurPid:0x%04x, KedaManuMpcPid:0x%04x, g_bKedaManuOn:%d\n",
		tInfo.dwProductId, BRD_PID_IS2_KedaManu, g_bKedaManuOn);
#else
	msgprintnotime("g_bKedaManuOn:%d\n",g_bKedaManuOn);
#endif
}

API void setmanuon(BOOL32 bManuON)
{
	g_bKedaManuOn = bManuON;
	msgprint("g_bKedaManuOn = %d.\n", g_bKedaManuOn);
}

API void setlistenip(s8* pszIp)
{
    g_dwListenIp = inet_addr(pszIp);
}

API void showlistenip(void)
{
	OspPrintf(TRUE, FALSE, "listen ip:"IPFORMAT".\n", u32ToIP(g_dwListenIp));
}
