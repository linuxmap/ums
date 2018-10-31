#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "umsobject.h"
#include "umsconfig.h"
#include "tpmsginit.h"
#include "umscallinit.h"
#include "tpconfig.h"
#include "mediatranscfg.h"
#include "innereventumsmediatrans.h"
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
}//namespace UmsTpmsg

extern void regist_ums_mediatrans_commond();

API void RegAllXmlCommand();
s8* GetMediatransCfgFile()
{
	return emUmsBrdCfg;
}

int StartApp(u32 dwNode);
void ReStartApp(u32 dwNode);

void StopApp();

BOOL32 g_bSysRuning = TRUE;
u32	g_dwUmsNode = INVALID_NODE;

API void reboot()
{
	g_bSysRuning = FALSE;
}

int main(int argc, char* argv[])
{
	printf("\n\n\n");
	printf("\t**********************************************\n");
	printf("\t*                                            *\n");
	printf("\t*           KDV umsmediatrans SYSTEM            *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");
	
// #ifdef _LINUX_ //异常捕获
// 	regist_exception(emUmsMdiatransExeFileName, emUmsMdiatransExceptionFileName);
// #endif

	//初始化OSP
	if(!OspInit( TRUE, TELNET_MEDIATRANS_PORT ) )
	{
		printf("Osp Init failed! \n");
	}

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TpMakeDir("/usr/conf/");
	BrdInit();
	BrdDelUser (UMS_UserName,UMS_UserName, USER_TYPE_FTP);
	BrdAddUser(UMS_UserName_New,UMS_PassWord_New,USER_TYPE_FTP);
	BrdDelUser(UMS_UserName,UMS_UserName, USER_TYPE_TELNET_SUPER);
	BrdAddUser(UMS_UserName_New, UMS_PassWord_New, USER_TYPE_TELNET_SUPER);
	BrdWebsEnable(BRD_WEBS_DISABLE);
#endif
	
	setmdllogname(Ums_Mdl_Media, "[ds]");

	InitUmsEvent();
#ifndef WIN32
	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
#endif
	OspSetPrompt("umsmediatrans");
	
#ifdef _DEBUG
	tplogon(0);
#endif

	regist_tpmsg_commond();
	
	regist_tp_commond();
	
	regist_ums_mediatrans_commond();

	RegAllXmlCommand();

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	EMBrdType emBrdType = em_cri2_brd;
	EMEqpType emMdlType = em_dataswitch_mdl;
	StartCallBack pCall = (StartCallBack)StartApp;
	StartCallBack pReCall = (StartCallBack)ReStartApp;
	StartBoardServer(emBrdType, pCall, pReCall);
#else
 	StartApp(g_dwUmsNode);
#endif
	while(g_bSysRuning)
	{
		OspDelay(100);
	}

	StopApp();

	return 0;
}

API BOOL StartupMediaTrans();

API void showcfg();
extern void ReadMediatransCfg();
int StartApp(u32 dwNode)
{
	g_dwUmsNode =dwNode;

	ReadMediatransCfg();

	StartupMediaTrans();
	return 0;
}


API void StopMediaTrans();
void StopApp()
{
	StopMediaTrans();
	OspQuit();
}

void ReStartApp(u32 dwNode)
{
	g_dwUmsNode =dwNode;
	CTpMsg cMsg;
	cMsg.SetEvent( ev_MediaConnectToUms_Time );
	cMsg.Post( UMS_MEDIATRANS_APP_INST);

}



