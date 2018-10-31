#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "umsobject.h"
#include "umsconfig.h"
#include "tpmsginit.h"
#include "umscallinit.h"
#include "tpconfig.h"
#include "umsconfigex.h"

#include "tpsys.h"
#include "tpstruct.h"
#include "umsapi.h"
#include "readlicense.h"

#define SUCCESS_LICENSE	0
#define DEVICE_ID "KEY_DEVICE_ID"
#define ACCESS_LIMIT "KEY_CONNECT_ACCESS_LIMIT"
#define len_limit 6

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#include "snmp_linux/api/api_snmp/api_snmp.h"
#endif

extern void regist_ums_service_commond();
extern void regist_configRegCommand();

namespace UmsTpmsg{
extern void regist_tpmsg_commond();
} //namespace UmsTpmsg

extern void regist_ums_ue_commond();
extern void regist_ums_eqp_commond();
extern void regist_ums_tool_command();
extern void regist_ums_hdu_command();
extern void regist_ums_apu2_mpu2_command();
API void RegAllXmlCommand();

#ifdef _USE_XMPUEQP_
extern void regist_ums_xmpueqp_commond();
#endif

void StopApp();

BOOL32 g_bSysRuning = TRUE;
BOOL32 g_bKedaManuOn = FALSE;

API void reboot()
{
	g_bSysRuning = FALSE;
}
API void help();
API void loglog();
API void showums();
API void showpid();
API void setmanuon(BOOL32 bManuON);
API void getlocalnet(u16 wIndex);

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
static u32 g_dwIpConflictNum = 0;
static u32 g_dwMacConflictNum = 0;
static u32 g_dwUnkownConflictNum = 0;
void UmsIpConflictCallBack(u32 conflictEvent, u8 *pbyMacAddr, u32 dwIpAdrs)
{
	if (conflictEvent == KDC_MAC_CONFLICT)
	{
		g_dwMacConflictNum++;
	}
	else if (conflictEvent == KDC_IP_CONFLICT)
	{
		g_dwIpConflictNum++;
	}
	else
	{
		g_dwUnkownConflictNum++;
	}

	msgprint("\t**********************************************\n");
	msgprint("\t*          Ums Ip Conflict Note              *\n");
	msgprint("\t**********************************************\n");
	msgprint("UmsIpConflictCallBack! ConflictEvent:%u, Ip:"TPIPFORMAT", IpConflictNum:%u, MacConflictNum:%u, UnkownConflictNum:%u.\n", 
		conflictEvent, Tpu32ToIP(dwIpAdrs), g_dwIpConflictNum, g_dwMacConflictNum, g_dwUnkownConflictNum);
}
#endif

EMBrdType ConverBrdID(u32 dwID)
{
	msgprint("ConverBrdID brdID:%d.\n", dwID);	
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	switch(dwID)
	{
	case BRD_HWID_APU2:
		return em_eapu_brd;
	case BRD_HWID_MPC2:
		return em_mpc_brd;
	case BRD_HWID_CRI2:
		return em_cri2_brd;
	case BRD_HWID_IS2_2:
		return em_is22_brd;
	case BRD_HWID_MPU2:
		return em_mpu2_tp_brd;
	default:
		return em_unknow_brd;
	}
#endif
	return em_unknow_brd;
}

void ReadChanLicense()
{
#if defined(_LINUX_)
	u8 abybuf[len_limit] = {0};
	u16 wRet = 0;
	if(SUCCESS_LICENSE != ReadLicenseFile( (s8*)(LPCSTR)"/usr/connect/kedalicense.key" )) 
	{
		OspPrintf(1, 0, "Open channel kedalicense.key failed!\n");
		return;
	}

	s32 wNum = GetKeyValueNum();
	printf( "Open key num:%d.\n", wNum);
	OspPrintf(1, 0, "Open key num:%d.\n", wNum);

	TKeyValue* ptValue = new TKeyValue[wNum];
	if (NULL != ptValue)
	{
		EnumKeyList(ptValue, wNum);

		for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
		{
			printf("  key:%s = %s.\n", ptValue[wIndex].achKey, ptValue[wIndex].achValue);
			OspPrintf(1, 0, "  key:%s = %s.\n", ptValue[wIndex].achKey, ptValue[wIndex].achValue);
		}

		delete[] ptValue;
		ptValue = NULL;
	}

	TKeyValue tValue;
	s32 wValueLen;
	//////////////////////////////////////////////////////////////////////////
	//mac校验 任何一个网口校验正确就可以
	wValueLen = sizeof(tValue.achValue);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, DEVICE_ID);	
	if( SUCCESS_LICENSE != GetValue(tValue.achKey, tValue.achValue, wValueLen) )
	{
		printf("Read channel kedalicense.key KEY_DEVICE_ID failed!\n");
		OspPrintf(1, 0, "Read channel kedalicense.key KEY_DEVICE_ID failed!\n");
		return ;
	}
	Trim(tValue.achValue);

	printf(" Read channel kedalicense.key KEY_DEVICE_ID is %s.\n", tValue.achValue);
	OspPrintf(1, 0, " Read channel kedalicense.key KEY_DEVICE_ID is %s.\n", tValue.achValue);
	CTpTypeAdpt::GetLocalMacAddr(0,abybuf);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, "%02X:%02X:%02X:%02X:%02X:%02X", abybuf[0], abybuf[1], abybuf[2], abybuf[3], abybuf[4], abybuf[5]);

	StrUpper(tValue.achValue);
	StrUpper(tValue.achKey);
	OspPrintf(1, 0, " Get Eth0 KEY_DEVICE_ID is %s.\n", tValue.achKey);
	if(strcmp(tValue.achValue, tValue.achKey) == 0)
	{
		printf("Get Key success.\n");
		OspPrintf(1,0,"Get Key success.\n");
	}
	else
	{
		CTpTypeAdpt::GetLocalMacAddr(1,abybuf);
		snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, "%02X:%02X:%02X:%02X:%02X:%02X", abybuf[0], abybuf[1], abybuf[2], abybuf[3], abybuf[4], abybuf[5]);

		StrUpper(tValue.achValue);
		StrUpper(tValue.achKey);
		printf( "Get Eth1 KEY_DEVICE_ID is %s.\n", tValue.achKey);
		OspPrintf(1, 0, "Get Eth1 KEY_DEVICE_ID is %s.\n", tValue.achKey);
		if(strcmp(tValue.achValue, tValue.achKey) == 0)
		{
			printf(" Get Key success.\n");
			OspPrintf(1,0," Get Key success.\n");
		}
		else
		{
			printf("Read channel kedalicense.key KEY_DEVICE_ID failed.\n");
			OspPrintf(1,0,"Read channel kedalicense.key KEY_DEVICE_ID failed.\n");
			return;

		}

	}
	//////////////////////////////////////////////////////////////////////////
	//渠道限制是否开启
	wValueLen = sizeof(tValue.achValue);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, ACCESS_LIMIT);	
	if( SUCCESS_LICENSE != GetValue(tValue.achKey, tValue.achValue, wValueLen) )
	{
		printf(" Read channel kedalicense.key KEY_ACCESS_NUM failed!\n");
		OspPrintf(1, 0, " Read channel kedalicense.key KEY_ACCESS_NUM failed!\n");
		return;
	}
	Trim(tValue.achValue);

	printf("Read channel kedalicense.key ACCESS_LIMIT is %s.\n", tValue.achValue);
	OspPrintf(1, 0, "Read channel kedalicense.key ACCESS_LIMIT is %s.\n", tValue.achValue);

	u8 abybuf1[len_limit] = "on"; 
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, "%s", abybuf1);

	StrUpper(tValue.achValue);
	StrUpper(tValue.achKey);
	printf(" Get  ACCESS_LIMIT is %s.\n", tValue.achKey);
	OspPrintf(1, 0, " Get  ACCESS_LIMIT is %s.\n", tValue.achKey);
	if(strcmp(tValue.achValue, tValue.achKey) == 0)
	{
		g_bKedaManuOn = TRUE;
	}
	else
	{
		g_bKedaManuOn = FALSE;
	}
	printf(" g_bKedaManuOn is %d.\n", g_bKedaManuOn);
	OspPrintf(1, 0, " g_bKedaManuOn is %d.\n", g_bKedaManuOn);
#endif
}

s8*	GetUmsRunTypeName(EmUmsRunType emType)
{
	switch(emType)
	{
	case Ums_Run_On_Win32:
		return "Win32";
	case Ums_Run_On_Mpc2:
		return "Mpc2";
	case Ums_Run_On_Cri2:
		return "Cri2";
	case Ums_Run_On_Linux:
		return "Linux";
	default:
		return "Unkown";
	}
	return "Unkown";
}

API BOOL StartupTpServer();
API void switchssh(BOOL32 bIson);
API void StartNtpd();
int main(int argc, char* argv[])
{
	printf("\n\n\n");
	printf("\t**********************************************\n");
	printf("\t*                                            *\n");
	printf("\t*           KDV UMS SYSTEM                   *\n");
	printf("\t*                                            *\n");
	printf("\t**********************************************\n");
	printf("\n\n\n");
	
// #ifdef _LINUX_ //异常捕获
// #ifdef _USE_LOG4CPLUS_
// 	regist_exception(UmsGetFileName(emUmsLog4cpExeFile), UmsGetFileName(emUmsLog4cpExceptionFile));
// #else
// 	regist_exception(UmsGetFileName(emUmsExeFile), UmsGetFileName(emUmsExceptionFile));
// #endif
// #endif

	g_dwSysApp = UMS_SERVICE_APP_INST;

	//初始化OSP
	if(!OspInit( TRUE, TELNET_UMS_PORT ) )
	{
		printf("Osp Init failed! \n");
		return -1;
	}
	
	EmUmsRunType emType = Ums_Run_On_Unkonw;

#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TpMakeDir("/usr/conf/");

	int iRes = BrdInit();
	printf("BrdInit Res:%d.\n", iRes);
	BrdDelUser (UMS_UserName,UMS_UserName, USER_TYPE_FTP);
	BrdAddUser(UMS_UserName_New,UMS_PassWord_New,USER_TYPE_FTP);
	BrdDelUser(UMS_UserName,UMS_UserName, USER_TYPE_TELNET_SUPER);
	BrdAddUser(UMS_UserName_New, UMS_PassWord_New, USER_TYPE_TELNET_SUPER);
	BrdWebsEnable(BRD_WEBS_DISABLE); // 设置nip的web服务失效，释放80端口给apache

	iRes = snmp_config_server_no_enable();
	printf("snmp_config_server_no_enable res:%d.\n", iRes);

	TBrdPosition tPos;
	BrdQueryPosition(&tPos);
	EMBrdType emBrdType = ConverBrdID(tPos.byBrdID);
	printf("Brdtype is %d.\n", emBrdType);
	if (emBrdType == em_unknow_brd)
	{
		printf("unkonw brdtype !\n");
		return -1;
	}

	if (em_mpc_brd == emBrdType)
	{// mpc板卡熄灭outs灯
		emType = Ums_Run_On_Mpc2;
		BrdLedStatusSet(LED_MPC_OUS, BRD_LED_OFF);
	}
	else if (em_cri2_brd == emBrdType)
	{
		emType = Ums_Run_On_Cri2;
		TTPTime tTime; // cri2板卡重启后，时间会重置成1931年，会导致apache服务启动异常；所以这里先设置下默认时间
		tTime.m_wYear = 2000;
		tTime.m_byMonth = 1;
		tTime.m_byMDay = 1;
		tTime.m_byHour = 8;
		TPSetSysTime(tTime);
	}
	else
	{
		// other...
	}

	TBrdE2PromInfo tInfo;
	BrdGetE2PromInfo(&tInfo);
	if (tInfo.dwProductId == BRD_PID_MPC2_KedaManu)
	{
		g_bKedaManuOn = TRUE;
		printf("MPC2 keda manu is ON !\n");
	}
#else
	ReadChanLicense();
	emType = Ums_Run_On_Linux;
#endif //defined(_PPC_82XX_) || defined(_PPC_85XX_)
#else
#ifdef WIN32
	emType = Ums_Run_On_Win32;
#endif //WIN32
#endif //_LINUX_

	printf("Ums Run Type is %d-%s.\n", emType, GetUmsRunTypeName(emType));

#ifdef _USE_LOG4CPLUS_
	initLog4CPlusLog(UmsGetFileName(emUmsserverLog4cplusCfg), "umsserver", TRUE);
#else
	initKdvLog( UmsGetFileName(emUmsLogCfgFile), TRUE);
#endif//_USE_LOG4CPLUS_

	setmdllogname(Ums_Mdl_Ue, "[Ue]");
	setmdllogname(Ums_Mdl_Cfg, "[Cfg]");
	setmdllogname(Ums_Mdl_Service, "[Service]");
	setmdllogname(Ums_Mdl_Call, "[Call]");
	setmdllogname(Ums_Mdl_Stack, "[Stack]");
	setmdllogname(Ums_Mdl_Media, "[Media]");

#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");
	OspRegCommand("reboot", (void*)reboot, "reboot()");
	OspRegCommand("loglog", (void*)loglog, "loglog()");
	OspRegCommand("showums", (void*)showums, "showums()");
	OspRegCommand("showpid", (void*)showpid, "showpid()");
	OspRegCommand("setmanuon", (void*)setmanuon, "setmanuon()");
	OspRegCommand("getlocalnet", (void*)getlocalnet, "getlocalnet()");
#endif
	
#ifdef _DEBUG
	tploglow(0);
#else
	tplogoff();
#endif

	OspDelay(100);
	msgprint("\t**********************************************\n");
	msgprint("\t*                                            *\n");
	msgprint("\t*        KDV umsserver Starting ...          *\n");
	msgprint("\t*                                            *\n");
	msgprint("\t**********************************************\n");
	
	regist_ums_ue_commond();
	regist_configRegCommand();
	regist_tpmsg_commond();
	
	regist_tp_commond();
	regist_ums_call_commond();
	regist_ums_service_commond();
	regist_ums_tool_command();
	regist_ums_hdu_command();
	regist_ums_apu2_mpu2_command();
	
#ifdef _USE_XMPUEQP_
	regist_ums_xmpueqp_commond();
#endif
	regist_ums_eqp_commond();
	
	RegAllXmlCommand();

	InitUmsEvent();

#ifndef WIN32
//	OspTelAuthor(UMS_UserName_New, UMS_PassWord_New);
#endif

	OspSetPrompt("ums");

	InitUmsCfg();
	
	BOOL32 bIsToCom = CUmsConfigEx::GetInstance()->GetPrintState();
	SetPrintToCom(bIsToCom);
	
	// 保存ums运行的一个环境
	CUmsConfigEx::GetInstance()->SetUmsRunType(emType);
	InitTpCfg();
	
	StartupTpServer();
	//switchssh(FALSE);
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
// 	OspDelay(2000);
// 	iRes = BrdIpConflictCallBackReg(UmsIpConflictCallBack);
// 	msgprint("BrdIpConflictCallBackReg Res:%d.\n", iRes);
#endif

	StartNtpd();

	while(g_bSysRuning)
	{
		OspDelay(100);
	}

	OspDelay(2000);

#ifdef _LINUX_
	system("reboot");
#endif
	StopApp();
	return 0;
}

API void help()
{	
	//ums
	msgprintnotime("ver()                           --- 显示UMSServer版本号\n");
	msgprintnotime("reboot()                        --- 重启UMS\n");
	msgprintnotime("loglog()                        --- 将缓存中的日志写到文件\n");
	msgprintnotime("showums()                       --- 显示UMS运行环境及ip冲突记录（win下无效）\n");
	msgprintnotime("showpid()                       --- 显示UMS运行板卡信息（win下无效）\n");
	msgprintnotime("\n");

	msgprintnotime("callhelp()                      --- 显示会议相关(umscall)的帮助信息\n");
	msgprintnotime("eqphelp()                       --- 显示外设相关(umseqp)的帮助信息\n");
	msgprintnotime("\n");

	msgprintnotime("serverhelp()                    --- 显示umsserver相关帮助信息\n");
	msgprintnotime("msghelp()                       --- 显示tpmsgmgr的帮助信息\n");
	msgprintnotime("cfghelp()                       --- 显示umsconfig的帮助信息\n");
	msgprintnotime("uehelp()                        --- 显示umsue的帮助信息\n");
}

API void getlocalnet(u16 wIndex)
{
	u32 dwIp0 = CTpTypeAdpt::GetLocalIP(wIndex,0);
	u32 dwIp1 = CTpTypeAdpt::GetLocalIP(wIndex);
	u32 dwIp2 = CTpTypeAdpt::GetLocalIP(wIndex,2);
	u32 dwIp3 = CTpTypeAdpt::GetLocalIP(wIndex,3);
	u32 dwIpPerfer2 = CTpTypeAdpt::GetLocalIPPerfer(wIndex,2);
	u32 dwIpPerfer3 = CTpTypeAdpt::GetLocalIPPerfer(wIndex,3);

	u32 dwMask0 = CTpTypeAdpt::GetLocalNetMask(wIndex,0);
	u32 dwMask1 = CTpTypeAdpt::GetLocalNetMask(wIndex);
	u32 dwMask2 = CTpTypeAdpt::GetLocalNetMask(wIndex,2);
	u32 dwMask3 = CTpTypeAdpt::GetLocalNetMask(wIndex,3);
	u32 dwMaskPerfer2 = CTpTypeAdpt::GetLocalNetMaskPerfer(wIndex,2);
	u32 dwMaskPerfer3 = CTpTypeAdpt::GetLocalNetMaskPerfer(wIndex,3);

	msgprintnotime("[eth%d info]\n", wIndex);

	msgprintnotime("dwIp0:"IPFORMAT", dwIp1:"IPFORMAT", dwIp2:"IPFORMAT", dwIp3:"IPFORMAT", dwIpPerfer2:"IPFORMAT", dwIpPerfer3:"IPFORMAT".\n",
		Tpu32ToIP(dwIp0), Tpu32ToIP(dwIp1), Tpu32ToIP(dwIp2), Tpu32ToIP(dwIp3), Tpu32ToIP(dwIpPerfer2), Tpu32ToIP(dwIpPerfer3));

	msgprintnotime("dwMask0:"IPFORMAT", dwMask1:"IPFORMAT", dwMask2:"IPFORMAT", dwMask3:"IPFORMAT", dwMaskPerfer2:"IPFORMAT", dwMaskPerfer3:"IPFORMAT".\n",
		Tpu32ToIP(dwMask0), Tpu32ToIP(dwMask1), Tpu32ToIP(dwMask2), Tpu32ToIP(dwMask3), Tpu32ToIP(dwMaskPerfer2), Tpu32ToIP(dwMaskPerfer3));
}

API void loglog()
{
	SetLogFlush();
}

API void showums()
{
	EmUmsRunType emType = CUmsConfigEx::GetInstance()->GetUmsRunType();
	msgprintnotime("ums is run on %d-%s.\n", emType, GetUmsRunTypeName(emType));
	msgprintnotime("\n");

// #if defined(_PPC_82XX_) || defined(_PPC_85XX_)
// 	msgprintnotime("IpConflictNum:%d, MacConflictNum:%d, UnkownConflictNum:%d.\n", 
// 		g_dwIpConflictNum, g_dwMacConflictNum, g_dwUnkownConflictNum);
// #endif
}

void QuitUmsConfMgr();
void StopApp()
{
	QuitUmsConfMgr();

	QuitTp();
	QuitUmsCfg();

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
		tInfo.dwProductId, BRD_PID_MPC2_KedaManu, g_bKedaManuOn);
#else
	msgprintnotime("g_bKedaManuOn:%d\n", g_bKedaManuOn);
#endif
}

API void setmanuon(BOOL32 bManuON)
{
	g_bKedaManuOn = bManuON;
	msgprint("g_bKedaManuOn = %d.\n", g_bKedaManuOn);
}

