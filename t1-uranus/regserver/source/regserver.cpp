#include "regserver.h"
#include "tpsys.h"
#include "eventtpsys.h"
#include "tpstruct.h"
#include "tpmsginit.h"
#include "tplog.h"
#include "innereventregsrv.h"
#include "regoprdb.h"
#include "umsapi.h"

#ifdef WIN32
const s8* g_pbyExeFileName = "regserver";
const s8* g_pbyExceptFileName = "regexception.txt";
const s8* g_pbyRegLogCfgFile = "regserverlog.ini"; // logclient������

#else
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
const s8* g_pbyExeFileName = "/usr/bin/regserver";
const s8* g_pbyExceptFileName = "/usr/conf/regexception.txt";
const s8* g_pbyRegLogCfgFile = "/usr/conf/regserverlog.ini"; // logclient������

#else
const s8* g_pbyExeFileName = "/tp/regserver";
const s8* g_pbyExceptFileName = "/tp/regexception.txt";
const s8* g_pbyRegLogCfgFile = "/tp/regserverlog.ini"; // logclient������

#endif

#endif

TIPCheck g_tIPCheck;
u32 g_dwListenIp = 0;

CTpRegServerApp g_cTPRegServerApp;


API BOOL StartupTpRegServer()
{
	g_cTPRegServerApp.CreateApp("RegServerApp",AID_REGSERVER_APP,100);
	
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( MAKEIID(AID_REGSERVER_APP,1) );

	return TRUE;
}


BOOL32 CTpRegServer::ObjectInit(u32 wParam, u32 lParam)
{
	SetLogTitle("CTpRegServer");

	return TRUE;
}


int StartApp();

int main(int argc, char* argv[])
{
	printf("\n\n\n");
	printf("\t**********************************************\n");
	printf("\t*                                            *\n");
	printf("\t*           KDV Register SYSTEM              *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");
	

// #ifdef _LINUX_ //�쳣����
// 	regist_exception(g_pbyExeFileName, g_pbyExceptFileName);
// #endif

	//��ʼ��OSP
	if(!OspInit( TRUE, TELNET_REG_PORT ) )
	{
		msgprint("Osp Init failed! \n");
		return 0;
	}

#ifdef _DEBUG
	tploglow(0);
#else
	tplogoff();
#endif

#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	g_dwListenIp = 0;
#else
	g_dwListenIp = CTpTypeAdpt::GetLocalIP(0);
	if (0 == g_dwListenIp)
	{
		g_dwListenIp = CTpTypeAdpt::GetLocalIP(1);
	}
#endif//(_PPC_82XX_) || defined(_PPC_85XX_)
#else
	g_dwListenIp = 0;
#endif //_LINUX_
	
	OspDelay(100);
	msgprint("\t**********************************************\n");
	msgprint("\t*                                            *\n");
	msgprint("\t*        KDV regserver Starting ...          *\n");
	msgprint("\t*                                            *\n");
	msgprint("\t**********************************************\n");

	InitUmsEvent();
	
#ifndef WIN32
	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
#endif

	OspSetPrompt("reg");

    g_tIPCheck.ReadIpFromCfg();
	//����APP
	StartApp();
	
	while(1)
	{
		OspDelay(100);
	}
	
	SetLogFlush();
	ExitKdvLog();

	OspQuit();

	return 0;
}


API void showip()
{
	g_tIPCheck.showIP();
}

API void loglog()
{
	SetLogFlush();
}

API BOOL StartupTpDBInterface();
API BOOL StartupRegStackOutApp();
API BOOL StartupRegStackInApp();



API void help()
{
	msgprint("ver()                           -- regver�汾");
	msgprint("msghelp()                       --  msghelp\n");
	msgprint("showreg()                       --  ��ʾ����ע��\n");
	msgprint("showtime()                      --  ��ʾ��ʱ��\n");
	msgprint("treg(s8* pCallID, s8* pszAlias, s8* pszIp, u16 wPort, u32 dwTimeOut)                  --  ���һ��ע��\n");
	msgprint("tunreg(s8* pCallID)             --  ɾ��һ��ע��\n");
	msgprint("tarq(s8* pAlias, u8 type)       -- ��ѯע��, 1Ϊ������2Ϊe164�ţ�3Ϊip\n");

	msgprint("tregs(u16 wNum, s8* szName, EmSipEndpointType type(1  =  cns  2  = ums)                          --ע��test1-test10\n");
	msgprint("reqcnsinfo()                     --��ѯCSNע����Ϣ\n");
	msgprint("requmsinfo()                     --��ѯUMSע����Ϣ\n");
	msgprint("reqallinfo()                     --��ѯ���е�ע����Ϣ\n");
	msgprint("setlistenip(s8*)                 --����Э�����ip\n");
	msgprint("showlistenip()                   --��ѯЭ�����ip\n");
}

#define  VER_regserver_Service  UMS_VerID
API void ver()
{
	msgprint("regserver ver: %s  compile time: %s:%s\n",
		VER_regserver_Service, __DATE__,  __TIME__);
}

API void treg(s8* pCallID, s8* pszAlias, s8* pszIp, u16 wPort, u32 dwTimeOut);
API void tunreg(s8* pCallID);
API void tarq(s8* pAlias, u8 type);

API void tregs();
API void reqcnsinfo();
API void requmsinfo();
API void reqallinfo();

API void showreg();
API void meminfo();
API void showtime();

using namespace UmsTpmsg;

namespace UmsTpmsg{
void regist_tpmsg_commond();

} //namespace UmsTpmsg

extern void regist_tpreg_test_commond();

API void setlistenip(s8* pszIp);
API void showlistenip(void);

int StartApp()
{
#ifdef _LINUX_
	regist_tpreg_test_commond();
	regist_tp_commond();
	regist_tpmsg_commond();
	
	OspRegCommand("help", (void*)help, "do sth");
	OspRegCommand("ver", (void*)ver, "do sth");

	OspRegCommand("showreg", (void*)showreg, "do sth");
	OspRegCommand("showtime", (void*)showtime, "do sth");
	OspRegCommand("treg", (void*)treg, "do sth");
	OspRegCommand("tunreg", (void*)tunreg, "do sth");
	OspRegCommand("tarq", (void*)tarq, "do sth");

	OspRegCommand("tregs", (void*)tregs, "do sth");
	OspRegCommand("reqcnsinfo", (void*)reqcnsinfo, "do sth");
	OspRegCommand("requmsinfo", (void*)requmsinfo, "do sth");
	OspRegCommand("reqallinfo", (void*)reqallinfo, "do sth");

	OspRegCommand("meminfo", (void*)meminfo, "do sth");
	OspRegCommand("loglog", (void*)loglog, "loglog");
	OspRegCommand("showip", (void*)showip, "--��ӡ�Ϸ�ip�б�");
    OspRegCommand("setlistenip", (void*)setlistenip, "--����Э�����ip--");
	OspRegCommand("showlistenip", (void*)showlistenip, "--��ѯЭ�����ip--");

#endif
	
	StartupTpDBInterface();
	StartupRegStackOutApp();
	StartupRegStackInApp();
	
#ifdef _DEBUG
	tplogon(0);
#endif
	
	return 0;
}

