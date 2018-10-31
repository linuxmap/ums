#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "umsobject.h"
#include "tpmsginit.h"
#include "devmgrserviceinst.h"
#include "tpsys.h"
#include "tpstruct.h"
#include "eventoutupdateservice.h"
#include "umsapi.h"
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif

#ifdef WIN32
#define emDevMgrServiceExeFileName "devmgrservice"
#define emDevMgrServiceKdvLogCfg "devmgrservicelog.ini" // logclient的配置
#define emDevMgrServiceCfg "devmgrservicecfg.ini"
#else

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#define emDevMgrServiceExeFileName "/usr/bin/devmgrservice"
#define emDevMgrServiceExceptionFileName "/usr/conf/devmgrserviceexception.txt"
#define emDevMgrServiceKdvLogCfg "/usr/conf/devmgrservicelog.ini" // logclient的配置
#define emDevMgrServiceCfg "/usr/conf/devmgrservicecfg.ini"
#else
#define emDevMgrServiceExeFileName "/tp/devmgrservice"
#define emDevMgrServiceExceptionFileName "/tp/devmgrserviceexception.txt"
#define emDevMgrServiceKdvLogCfg "/tp/devmgrservicelog.ini" // logclient的配置
#define emDevMgrServiceCfg "/tp/devmgrservicecfg.ini"
#endif

#endif

s8* GetUpdateServiceCfgFile()
{
	return emDevMgrServiceCfg;
}

void StartApp();
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
	printf("\t*           KDV DevMgrService SYSTEM         *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");

// #ifdef _LINUX_ //异常捕获
// 	regist_exception(emDevMgrServiceExeFileName, emDevMgrServiceExceptionFileName);
// #endif
	
	//初始化OSP
	if(!OspInit( TRUE, TELNET_UPDATESERVICE_PORT ) )
	{
		printf("Osp Init failed! \n");
	}

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TpMakeDir("/usr/conf/");
	int iRes = BrdInit();
	printf("BrdInit Res:%d.\n", iRes);
	BrdDelUser (UMS_UserName,UMS_UserName, USER_TYPE_FTP);
	BrdAddUser(UMS_UserName_New,UMS_PassWord_New,USER_TYPE_FTP);
	BrdDelUser(UMS_UserName,UMS_UserName, USER_TYPE_TELNET_SUPER);
	BrdAddUser(UMS_UserName_New, UMS_PassWord_New, USER_TYPE_TELNET_SUPER);
	BrdWebsEnable(BRD_WEBS_DISABLE); // 设置nip的web服务失效
#endif

	setmdllogname(Ums_Mdl_UpdateSer, "[DevMgrService]");
	
	InitUmsEvent();
	
#ifndef WIN32
	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
#endif
	OspSetPrompt("DevMgrService");
	
	StartApp();
	
	while(g_bSysRuning)
	{
		OspDelay(100);
	}
	
	StopApp();
	
	return 0;
}


#define VER_devmgrservice_ver    UMS_VerID
API void ver()
{
	msgprint("devmgrservice ver: %s  compile time: %s, %s\n", VER_devmgrservice_ver, __DATE__,  __TIME__);
}

API void telnetportoff()
{// 通过iptables限制23端口，关闭板卡对外telnet服务
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	system("/usr/bin/telnetportonoff.sh off &");
#else
	msgprint("This command is not valid!\n");
#endif
}

API void telnetporton()
{// 通过iptables放开23端口，开启板卡对外telnet服务
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	system("/usr/bin/telnetportonoff.sh on &");
#else
	msgprint("This command is not valid!\n");
#endif
}

//ftp
API void switchftp(u8 byFtpOn)
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	if (byFtpOn)
	{
		BrdEnableFtpd();
	}
	else 
	{
		BrdDisableFtpd();
	}
#else
	msgprint("This command is not valid!\n");	
#endif	
}

API void help()
{
	msgprint("reboot()                                     --- 重启升级服务器\n");
	msgprint("ver()                                        --- 显示升级服务器版本号\n");
	msgprint("showcfg()                                    --- 显示升级服务器配置信息\n");
	msgprint("showdev()                                    --- 显示当前在线设备的版本号\n");
	msgprint("reload()                                     --- 重新载入当前配置文件信息\n");

	msgprint("telnetportoff()                              --- 关闭telnet\n");
	msgprint("telnetporton()                               --- 打开telnet\n");
	msgprint("switchftp(0/1)                               --- 关闭打开ftp\n");

}

API u16 showdev()
{
	OspInstDump(AID_UPDATESERVER_APP, 1, devmgr_service_dump_show_devlist);
	return 0;
}
API u16 showcfg()
{
	OspInstDump(AID_UPDATESERVER_APP, 1, devmgr_service_dump_show_localinfo);
	return 0;
}

API u16 reload()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_ReloadCfg_Req);
	cMsg.Post(MAKEIID(AID_UPDATESERVER_APP, 1));
	return 0;
}

API void RegAllXmlCommand();

namespace UmsTpmsg{
extern void regist_tpmsg_commond();
} //namespace UmsTpmsg

void StartApp()
{
#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");
	OspRegCommand("showcfg", (void*)showcfg, "showcfg()");
	OspRegCommand("reboot", (void*)reboot, "reboot()");
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("reload", (void*)reload, "reload()");
	OspRegCommand("showdev", (void*)showdev, "showdev()");

	OspRegCommand("telnetportoff", (void*)telnetportoff, "telnetportoff()");
    OspRegCommand("telnetporton", (void*)telnetporton, "telnetporton()");
	OspRegCommand("switchftp", (void*)switchftp, "switchftp()");
#endif

#ifdef _DEBUG
	tplogon(0);
#endif
	
	regist_tpmsg_commond();
	regist_tp_commond();
	RegAllXmlCommand();

 	//启动APP
	StartDevMgrService();
}

BOOL32 g_bQuitIng = TRUE;
void StopApp()
{
	//停止APP
	StopDevMgrService();

	while( g_bQuitIng )
	{
		OspDelay(100);
	}

	OspQuit();
}
