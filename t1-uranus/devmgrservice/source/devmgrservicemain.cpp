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
#define emDevMgrServiceKdvLogCfg "devmgrservicelog.ini" // logclient������
#define emDevMgrServiceCfg "devmgrservicecfg.ini"
#else

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#define emDevMgrServiceExeFileName "/usr/bin/devmgrservice"
#define emDevMgrServiceExceptionFileName "/usr/conf/devmgrserviceexception.txt"
#define emDevMgrServiceKdvLogCfg "/usr/conf/devmgrservicelog.ini" // logclient������
#define emDevMgrServiceCfg "/usr/conf/devmgrservicecfg.ini"
#else
#define emDevMgrServiceExeFileName "/tp/devmgrservice"
#define emDevMgrServiceExceptionFileName "/tp/devmgrserviceexception.txt"
#define emDevMgrServiceKdvLogCfg "/tp/devmgrservicelog.ini" // logclient������
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

// #ifdef _LINUX_ //�쳣����
// 	regist_exception(emDevMgrServiceExeFileName, emDevMgrServiceExceptionFileName);
// #endif
	
	//��ʼ��OSP
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
	BrdWebsEnable(BRD_WEBS_DISABLE); // ����nip��web����ʧЧ
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
{// ͨ��iptables����23�˿ڣ��رհ忨����telnet����
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	system("/usr/bin/telnetportonoff.sh off &");
#else
	msgprint("This command is not valid!\n");
#endif
}

API void telnetporton()
{// ͨ��iptables�ſ�23�˿ڣ������忨����telnet����
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
	msgprint("reboot()                                     --- ��������������\n");
	msgprint("ver()                                        --- ��ʾ�����������汾��\n");
	msgprint("showcfg()                                    --- ��ʾ����������������Ϣ\n");
	msgprint("showdev()                                    --- ��ʾ��ǰ�����豸�İ汾��\n");
	msgprint("reload()                                     --- �������뵱ǰ�����ļ���Ϣ\n");

	msgprint("telnetportoff()                              --- �ر�telnet\n");
	msgprint("telnetporton()                               --- ��telnet\n");
	msgprint("switchftp(0/1)                               --- �رմ�ftp\n");

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

 	//����APP
	StartDevMgrService();
}

BOOL32 g_bQuitIng = TRUE;
void StopApp()
{
	//ֹͣAPP
	StopDevMgrService();

	while( g_bQuitIng )
	{
		OspDelay(100);
	}

	OspQuit();
}
