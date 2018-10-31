#include "umsconfig.h"
#include "ummessagestruct.h"
#include "umsobject.h"

// 外部消息
#include "eventoutumslogin.h"
#include "eventoutumstool.h"
#include "eventoutumsconftemplate.h"
#include "eventoutumscfg.h"
#include "eventoutumshdu2.h"
#include "eventoutumsreg.h"
#include "eventoutumsboard.h"
#include "eventoutumscommonbrd.h"
#include "eventoutumscall.h"

/*	维护工具测试命令	*/
API void inittool()
{
	u16 wPort;
	umsGetUmsListenPortCfg(wPort);
	int toolNode = OspConnectTcpNode(inet_addr("127.0.0.1"), wPort);
	
	if (INVALID_NODE == toolNode)
	{
		OspPrintf(TRUE, FALSE, "init tool connect tcp failed.\n");
	}
	else
	{
		CLoginRequest cLogin;
		OspPost(UMS_UE_APP_INST, ev_UMSLoginReq, &cLogin, sizeof(CLoginRequest), toolNode, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
	}
}

API void getsysinfo()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_sysInfo_req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void getconfcount()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_confCount_req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void gethducount()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduCount_req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void downlicense()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_licenseOutput_req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
	
}

API void setumsip(s8* pszIp, s8* pszMask, s8* pszGate)
{
	TTPEthnetInfo tEthNet;
	tEthNet.bEnable = TRUE;
	tEthNet.dwIP = inet_addr(pszIp);
	tEthNet.dwMask = inet_addr(pszMask);
	tEthNet.dwGateWay = inet_addr(pszGate);
	EmEthInfoType emEthType = em_eth0_type;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsIPCfg);
	cMsg.SetBody(&tEthNet, sizeof(tEthNet));
	cMsg.CatBody(&emEthType, sizeof(emEthType));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void setregip(BOOL32 bUsed, s8* pszIP, u16 wPort, u16 wExpire)
{
	TTPSipRegistrarCfg tCfg;
	tCfg.bUsed = bUsed;
	tCfg.wRegPort = wPort;
	tCfg.wExpire = wExpire;
	tCfg.dwRegIP = inet_addr(pszIP);

	CTpMsg cMsg;
	cMsg.SetEvent(ev_umsreg_cmd);
	cMsg.SetBody(&tCfg, sizeof(TTPSipRegistrarCfg));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void setgkip(BOOL32 bUsed, s8* pszIP, u16 wExpire)
{
	TTPGKCfg tCfg;
	tCfg.bUsed = bUsed;
	tCfg.dwGKIP = inet_addr(pszIP);
	tCfg.wExpire = wExpire;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_umsGKReg_cmd);
	cMsg.SetBody(&tCfg, sizeof(TTPGKCfg));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void getsystime()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsGetSysTime_Req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void setsystime(u16 wYear, u8 wMonth, u8 wDay, u8 wHour, u8 wMin, u8 wSec)
{
	TTPTime tTime;
	tTime.m_wYear = wYear;
	tTime.m_byMonth = wMonth;
	tTime.m_byMDay = wDay;
	tTime.m_byHour = wHour;
	tTime.m_byMinute = wMin;
	tTime.m_bySecond = wSec;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsSetSysTime_Cmd);
	cMsg.SetBody(&tTime, sizeof(TTPTime));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void upload()
{
	s8 szFileName[] = "template_down.tar";
	
	CTpMsg cMsg;
	cMsg.SetBody(szFileName, sizeof(szFileName));
	cMsg.SetEvent(ev_uploadConftemp_req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void download()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_downloadConftemp_req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void mdyhdubrd(char* szIP, u8 byLayer, u8 bySlot, u8 byQtVer)
{
	TTPBrdPos tBrdPos;
	tBrdPos.m_byBrdLayer = byLayer;
	tBrdPos.m_byBrdSlot  = bySlot;
	tBrdPos.m_dwBrdIP = inet_addr(szIP);
	if (byQtVer)
	{
		tBrdPos.m_emBrdType = em_hdu2_qt_brd;
	}
	else
	{
		tBrdPos.m_emBrdType = em_hdu2_brd;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduBrdModify_req);
	cMsg.SetBody(&tBrdPos, sizeof(TTPBrdPos));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void mdyhduchan(u8 byLayer, u8 bySlot, s8* szName, u8 byQtVer)
{
	THduInfo tHduInfo;
	tHduInfo.m_byLayer = byLayer;
	tHduInfo.m_bySlot  = bySlot;
	tHduInfo.m_tName.SetAlias(szName);
	if (byQtVer)
	{
		tHduInfo.m_emBrdType = em_hdu2_qt_brd;
	}
	else
	{
		tHduInfo.m_emBrdType = em_hdu2_brd;
	}

	for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
	{
		tHduInfo.m_atChanInfo[byIndex].SetOutMode(em_hdu_outmode_YPbPr_1080P_24fps);
		tHduInfo.m_atChanInfo[byIndex].SetOutType(em_hdu_outport_YPbPr);
		tHduInfo.m_atChanInfo[byIndex].SetZoomRate(em_hdu_zoomrate_4_3);
		tHduInfo.m_atChanInfo[byIndex].SetShowMode(em_hdu_showmode_NONGEOMETRIC);
	}

	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduChanModify_req);
	cMsg.SetBody(&tHduInfo, sizeof(THduInfo));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void delhdubrd(u8 byLayer, u8 bySlot, u8 byQtVer)
{	
	TTPBrdPos tBrdPos;
	tBrdPos.m_byBrdLayer = byLayer;
	tBrdPos.m_byBrdSlot  = bySlot;
	if (byQtVer)
	{
		tBrdPos.m_emBrdType = em_hdu2_qt_brd;
	}
	else
	{
		tBrdPos.m_emBrdType = em_hdu2_brd;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduDel_req);
	cMsg.SetBody(&tBrdPos, sizeof(TTPBrdPos));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void delhduchan(u8 byLayer, u8 bySlot, u8 byQtVer)
{
	TTPBrdPos tBrdPos;
	tBrdPos.m_byBrdLayer = byLayer;
	tBrdPos.m_byBrdSlot = bySlot;
	if (byQtVer)
	{
		tBrdPos.m_emBrdType = em_hdu2_qt_brd;
	}
	else
	{
		tBrdPos.m_emBrdType = em_hdu2_brd;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduChanDel_req);
	cMsg.SetBody(&tBrdPos, sizeof(TTPBrdPos));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void addhdubrd(char* szIP, u8 byLayer, u8 bySlot, u8 byQtVer)
{
	TTPBrdPos tBrdPos;
	tBrdPos.m_byBrdLayer = byLayer;
	tBrdPos.m_byBrdSlot = bySlot;
	tBrdPos.m_dwBrdIP = inet_addr(szIP);
	if (byQtVer)
	{
		tBrdPos.m_emBrdType = em_hdu2_qt_brd;
	}
	else
	{
		tBrdPos.m_emBrdType = em_hdu2_brd;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduBrdAdd_req);
	cMsg.SetBody(&tBrdPos,sizeof(TTPBrdPos));
	cMsg.Post(UMS_UE_APP_INST,0,MAKEIID(AID_UMSTOOL2UMS_APP, 0));

// 	mdyhdubrd("127.0.0.1", 0, 0);
// 	mdyhduchan(0, 0, "test1");
// 	mdyhdubrd("127.0.0.1", 0, 1);
// 	mdyhduchan(0, 1, "test2");
// 	mdyhdubrd("127.0.0.1", 0, 2);
// 	mdyhduchan(0, 2, "test3");
// 	mdyhdubrd("127.0.0.1", 0, 3);
// 	mdyhduchan(0, 3, "test4");
}

API void addhdustyle()
{
	THduStyleData tData;
	tData.m_byCol = 2;
	tData.m_byRow = 2;

	tData.m_atUnits[0].m_bySlot = 0;
	tData.m_atUnits[0].m_byLayer = 0;
	tData.m_atUnits[0].m_byChanIndex = 0;

	tData.m_atUnits[1].m_bySlot = 0;
	tData.m_atUnits[1].m_byLayer = 0;
	tData.m_atUnits[1].m_byChanIndex = 1;

	tData.m_atUnits[2].m_bySlot = 1;
	tData.m_atUnits[2].m_byLayer = 0;
	tData.m_atUnits[2].m_byChanIndex = 0;

	tData.m_atUnits[3].m_bySlot = 1;
	tData.m_atUnits[3].m_byLayer = 0;
	tData.m_atUnits[3].m_byChanIndex = 1;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduStyle_Add);
	cMsg.SetBody(&tData, sizeof(THduStyleData));
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void delhdustyle()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_hduStyle_Del_Req);
	cMsg.Post(UMS_UE_APP_INST, 0, MAKEIID(AID_UMSTOOL2UMS_APP, 0));
}

API void toolhelp()
{
	msgprint("inittool()												初始化维护工具环境\n");
	msgprint("\n");
	msgprint("getsysinfo()												获得系统信息(cpu/mem)\n");
	msgprint("\n");
	msgprint("getconfcount()												获得正在进行会议数量\n");
	msgprint("\n");
	msgprint("gethducount()												获得电视墙的数量\n");
	msgprint("\n");
	msgprint("setumsip(s8* pszIp, s8* pszMask, s8* pszGate)					                   设置ums的ip\n");
	msgprint("\n");
	msgprint("setregip(BOOL32 bUsed, s8* pszIP, u16 wPort, u16 wExpire)					       设置注册服务器地址\n");
	msgprint("\n");
	msgprint("setgkip(BOOL32 bUsed, s8* pszIP, u16 wExpire)						               设置GK服务器地址\n");
	msgprint("\n");
	msgprint("getsystime()												获取系统时间\n");
	msgprint("\n");
	msgprint("setsystime(u16 wYear, u8 wMonth, u8 wDay, u8 wHour, u8 wMin, u8 wSec)			         设置系统时间\n");
	msgprint("\n");
	msgprint("upload()												       上传模板文件\n");
	msgprint("\n");
	msgprint("download()												下载模板文件\n");
	msgprint("\n");
	msgprint("mdyhdubrd(char* szIP, u8 byLayer, u8 bySlot, u8 byQtVer)					                    修改板子板子\n");
	msgprint("\n");
	msgprint("mdyhduchan(u8 byLayer, u8 bySlot, s8* szName, u8 byQtVer)						                修改通道\n");
	msgprint("\n");
	msgprint("delhdubrd(u8 byLayer, u8 bySlot, u8 byQtVer)									       删除板子\n");
	msgprint("\n");
	msgprint("delhduchan(u8 byLayer, u8 bySlot, u8 byQtVer)								           删除通道\n");
	msgprint("\n");
	msgprint("addhdustyle()												添加电视墙风格\n");
	msgprint("\n");
	msgprint("addhdubrd(char* szIP, u8 byLayer, u8 bySlot, u8 byQtVer)				 				添加测试的板子\n");
	msgprint("\n");
	msgprint("delhdustyle()												删除电视墙预案\n");
	msgprint("\n");
}

void regist_ums_tool_command()
{
#ifdef _LINUX_
	//测试维护工具命令
	OspRegCommand("toolhelp", (void*)toolhelp, "toolhelp");
	OspRegCommand("inittool", (void*)inittool, "inittool");
	OspRegCommand("getsysinfo", (void*)getsysinfo, "getsysinfo");
	OspRegCommand("getconfcount", (void*)getconfcount, "getconfcount");
	OspRegCommand("gethducount", (void*)gethducount, "gethducount");
	OspRegCommand("setumsip", (void*)setumsip, "setumsip(s8* pszIp, s8* pszMask, s8* pszGate)");
	OspRegCommand("setregip", (void*)setregip, "setregip(BOOL32 bUsed, s8* pszIP, u16 wPort, u16 wExpire)");
	OspRegCommand("setgkip", (void*)setgkip, "setgkip(BOOL32 bUsed, s8* pszIP, u16 wExpire)");
	OspRegCommand("getsystime", (void*)getsystime, "getsystime");
	OspRegCommand("setsystime", (void*)setsystime, "setsystime");
	OspRegCommand("upload", (void*)upload, "upload");
	OspRegCommand("download", (void*)download, "download");
	OspRegCommand("mdyhdubrd", (void*)mdyhdubrd, "mdyhdubrd(char* szIP, u8 byLayer, u8 bySlot, u8 byQtVer)");
	OspRegCommand("mdyhduchan", (void*)mdyhduchan, "mdyhduchan(u8 byLayer, u8 bySlot, s8* szName, u8 byQtVer)");
	OspRegCommand("delhdubrd", (void*)delhdubrd, "delhdubrd(u8 byLayer, u8 bySlot, u8 byQtVer)");
	OspRegCommand("delhduchan", (void*)delhduchan, "delhduchan(u8 byLayer, u8 bySlot, u8 byQtVer)");
	OspRegCommand("addhdustyle", (void*)addhdustyle, "addhdustyle()");
	OspRegCommand("addhdubrd", (void*)addhdubrd, "addhdubrd(char* szIP, u8 byLayer, u8 bySlot, u8 byQtVer)");
	OspRegCommand("downlicense", (void*)downlicense, "downlicense");
#endif
}

API void playhdu(u16 wConfid, u16 wDstep, BOOL32 bVmp, u16 wIndex, u16 wSubIndex = 0)
{
	TLogUser tLog;
	TTPHduPlayReq tReq;
	
	tReq.m_wConfID = wConfid;
	tReq.m_wDstID = wDstep;
	tReq.m_emType = EmEpType_Ter;
	tReq.m_wScreenNum = 1;
	
	tReq.m_bVmp = bVmp;
	tReq.m_wIndex = wIndex;
	tReq.m_bySubIndex = (u8)wSubIndex;
	
	CTpMsg cMsg;
	cMsg.SetEvent( ev_HduPlay_Req );
	cMsg.SetBody(&tLog, sizeof(tLog));
	cMsg.CatBody(&tReq, sizeof(tReq));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_BRDREG_APP_INST);
}

API void setvol(u16 wIndex, u16 wVol, BOOL32 bIsMute)
{
	TLogUser tLog;
	THduSetVolInfo tReq;
	tReq.m_tInfo.m_wIndex = wIndex;
	tReq.m_byVol = (u8)wVol;
	tReq.m_bMute = (u8)bIsMute;
	
	CTpMsg cMsg;
	cMsg.SetEvent( ev_Hdu_SetVol );
	cMsg.SetBody(&tLog, sizeof(tLog));
	cMsg.CatBody(&tReq, sizeof(tReq));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_BRDREG_APP_INST);
}

API void changemode(u16 wIndex, u16 wMode)
{
	TLogUser tLog;
	THduChanModeSetInfo tReq;
	
	tReq.m_wIndex = wIndex;
	tReq.m_byMode = (u8)wMode;
	
	CTpMsg cMsg;
	cMsg.SetEvent( ev_Hdu_ChangeChanMode_Req );
	cMsg.SetBody(&tLog, sizeof(tLog));
	cMsg.CatBody(&tReq, sizeof(tReq));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_BRDREG_APP_INST);
}

void regist_ums_hdu_command()
{
#ifdef _LINUX_

	OspRegCommand("setvol", (void*)setvol, "setvol()");
	OspRegCommand("changemode", (void*)changemode, "changemode()");
	OspRegCommand("playhdu", (void*)playhdu, "playhdu()");

#endif
}


//////////////////////////////////////////////////////////////////////////
//apu2 mpu2 test command

API void addapu2tp()
{
	TLogUser tUser;
	TTPBrdCfg tBrdInfo;
	tBrdInfo.m_byBrdID = 1;
	tBrdInfo.m_tBrdPos.m_byBrdLayer = 1;
	tBrdInfo.m_tBrdPos.m_byBrdSlot = 2;
	tBrdInfo.m_tBrdPos.m_dwBrdIP = 123;
	tBrdInfo.m_tBrdPos.m_emBrdType = em_apu2_tp_brd;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_cardAdd_req);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tBrdInfo, sizeof(tBrdInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);

	TTPBrdMdlInfo tMdlInfo;
	tMdlInfo.m_byLayer = 1;
	tMdlInfo.m_bySlot = 2;
	tMdlInfo.m_byIndex = 4;

	tMdlInfo.m_atMdlCfg[0].m_byAudmixNum = 16;
	tMdlInfo.m_atMdlCfg[0].m_emEqpType = em_audmix_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[0].m_szEqpAlias, "test1-apu2");

	tMdlInfo.m_atMdlCfg[1].m_byAudmixNum = 16;
	tMdlInfo.m_atMdlCfg[1].m_emEqpType = em_audmix_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[1].m_szEqpAlias, "test2-apu2"); 

	tMdlInfo.m_atMdlCfg[2].m_byAudmixNum = 16;
	tMdlInfo.m_atMdlCfg[2].m_emEqpType = em_audmix_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[2].m_szEqpAlias, "test3-apu2"); 
	
	tMdlInfo.m_atMdlCfg[3].m_byAudmixNum = 16;
	tMdlInfo.m_atMdlCfg[3].m_emEqpType = em_audmix_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[3].m_szEqpAlias, "test4-apu2"); 
	
	cMsg.SetEvent(ev_cardModeModify_req);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tMdlInfo, sizeof(tMdlInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void addmpu2tp()
{
	TLogUser tUser;
	TTPBrdCfg tBrdInfo;
	tBrdInfo.m_byBrdID = 2;
	tBrdInfo.m_tBrdPos.m_byBrdLayer = 1;
	tBrdInfo.m_tBrdPos.m_byBrdSlot = 1;
	tBrdInfo.m_tBrdPos.m_dwBrdIP = inet_addr("172.16.216.6");
	tBrdInfo.m_tBrdPos.m_emBrdType = em_mpu2_tp_brd;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_cardAdd_req);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tBrdInfo, sizeof(tBrdInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
	
	TTPBrdMdlInfo tMdlInfo;
	tMdlInfo.m_byLayer = 1;
	tMdlInfo.m_bySlot = 1;
	tMdlInfo.m_byIndex = 4;
	
	tMdlInfo.m_atMdlCfg[0].m_emEqpType = em_vmp_tp_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[0].m_szEqpAlias, "test1-mpu2");
	
	tMdlInfo.m_atMdlCfg[1].m_emEqpType = em_vmp_tp_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[1].m_szEqpAlias, "test2-mapu2"); 
	
	tMdlInfo.m_atMdlCfg[2].m_emEqpType = em_vmp_tp_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[2].m_szEqpAlias, "test3-mpu2"); 
	
	tMdlInfo.m_atMdlCfg[3].m_emEqpType = em_vmp_tp_mdl;
	strcpy(tMdlInfo.m_atMdlCfg[3].m_szEqpAlias, "test4-mapu2"); 
	
	cMsg.SetEvent(ev_cardModeModify_req);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tMdlInfo, sizeof(tMdlInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void mpu2tpreg()
{
	TTPBrdRegInfo tBrdReg;
	u8	byNetIndx = 0;
	EMOsType emOsType = em_Win32_OsType;
	tBrdReg.m_tBrdPos.m_byBrdLayer = 2;
	tBrdReg.m_tBrdPos.m_byBrdSlot = 1;
	tBrdReg.m_tBrdPos.m_dwBrdIP = 123;
	tBrdReg.m_tBrdPos.m_emBrdType = em_mpu2_tp_brd;
	tBrdReg.m_byNetIndx = byNetIndx;
	tBrdReg.m_emOsType = emOsType;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBrdReg_Req);
	cMsg.SetBody(&tBrdReg, sizeof(tBrdReg));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_BRDREG_APP_INST);

	cMsg;
	cMsg.SetEvent( ev_TPBrdGetCfg_Req );
	cMsg.SetBody(&tBrdReg.m_tBrdPos, sizeof(tBrdReg.m_tBrdPos));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_BRDREG_APP_INST);

}

///////////////不入会请求会议信息测试命令//////

API void getvmpvid(u16 wConfID, u16 wEqpID, s8* ip, u16 port)
{
	TUmsGetVmpVidInfo tInfo;
	TLogUser tUser;

	tInfo.m_wConfID = wConfID;
	tInfo.m_wEqpID  = wEqpID;
	tInfo.m_tRtpAddr.m_dwIP = inet_addr(ip);
	tInfo.m_tRtpAddr.m_wPort = port;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_GetConfVmpVid_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tInfo, sizeof(tInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}


API void relvmpvid(u16 wConfID, u16 wUserIndex)
{
	TUmsReleaseVmpVidInfo tInfo;
	TLogUser tUser;
	
	tInfo.m_wConfID = wConfID;
	tInfo.m_wVmpInfoIndex  = wUserIndex;
	
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ReleaseConfVmpVid_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tInfo, sizeof(tInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}


API void getvmpaskkey(u16 wConfID, u16 wUserIndex)
{
	TUmsGetVmpVidAskKey tInfo;
	TLogUser tUser;
	
	tInfo.m_wConfId = wConfID;
	tInfo.m_wVmpInfoIndex  = wUserIndex;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_GetConfVmpVidAskKey_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tInfo, sizeof(tInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}


void regist_ums_apu2_mpu2_command()
{
#ifdef _LINUX_
	OspRegCommand("addapu2tp", (void*)addapu2tp, "addapu2tp()");
	OspRegCommand("addmpu2tp", (void*)addmpu2tp, "addmpu2tp()");
	OspRegCommand("mpu2tpreg", (void*)mpu2tpreg, "mpu2tpreg()");

	OspRegCommand("getvmpvid", (void*)getvmpvid, "getvmpvid()");
	OspRegCommand("relvmpvid", (void*)relvmpvid, "relvmpvid()");
	OspRegCommand("getvmpaskkey", (void*)getvmpaskkey, "getvmpaskkey()");
#endif
}
