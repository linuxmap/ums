#include "displaydata.h"
#include <stdio.h>
#include "mtmacro.h"
#include "persistfile.h"
#include "umsconfigex.h"
#include "tplog.h"
#include "jdconfig.h"

#define GetIPStr(dwIp,achStr)\
{\
	struct in_addr addr;\
	addr.s_addr = dwIp;\
	sprintf(achStr,IPFORMAT,u32ToIP(dwIp));\
}

API void  CfgLocalUmsInfo(void)
{
	s8 abyIp[20];
	
	msgprintnotime("[%s]\n", umsLocalInfo);
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tEth.dwIP, abyIp);
	msgprintnotime("%s = %s\n", umsKeyUmsIp, abyIp);

	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tEth.dwMask, abyIp);
	msgprintnotime("%s = %s\n", umsKeyNetMask, abyIp);

	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tEth.dwGateWay, abyIp);
	msgprintnotime("%s = %s\n", umsKeyGateWay, abyIp);
	msgprintnotime("\n");
	msgprintnotime("[%s]\n", umsLocalInfoVir);
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth.dwIP, abyIp);
	msgprintnotime("%s = %s\n", umsKeyUmsIp, abyIp);
	
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth.dwMask, abyIp);
	msgprintnotime("%s = %s\n", umsKeyNetMask, abyIp);
	
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth.dwGateWay, abyIp);
	msgprintnotime("%s = %s\n", umsKeyGateWay, abyIp);
	msgprintnotime("\n");
	msgprintnotime("[%s]\n", umsLocalInfoEth1);
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tEth1.dwIP, abyIp);
	msgprintnotime("%s = %s\n", umsKeyUmsIp, abyIp);
	
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tEth1.dwMask, abyIp);
	msgprintnotime("%s = %s\n", umsKeyNetMask, abyIp);
	
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tEth1.dwGateWay, abyIp);
	msgprintnotime("%s = %s\n", umsKeyGateWay, abyIp);
	msgprintnotime("\n");
	msgprintnotime("[%s]\n", umsLocalInfoEth1Vir);
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth1.dwIP, abyIp);
	msgprintnotime("%s = %s\n", umsKeyUmsIp, abyIp);
	
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth1.dwMask, abyIp);
	msgprintnotime("%s = %s\n", umsKeyNetMask, abyIp);
	
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth1.dwGateWay, abyIp);
	msgprintnotime("%s = %s\n", umsKeyGateWay, abyIp);
	msgprintnotime("\n");
	GetIPStr(g_tALLConfigData.m_tLocalCnsInfo.m_dwUmsoldIP, abyIp);
	msgprintnotime("%s = %s\n", umsKeyOldIP, abyIp);
	msgprintnotime("%s = %d\n", umsKeyBeginUdpTransPort, g_tALLConfigData.m_tLocalCnsInfo.m_wBeginUdpTransPort);
	msgprintnotime("%s = %d\n", umsKeyListionPortForUi, g_tALLConfigData.m_tLocalCnsInfo.m_wListionPortForUi);
	msgprintnotime("%s = %d\n", umsKeyNumMaxOnecCall, g_tALLConfigData.m_tLocalCnsInfo.m_wNumMaxOnecCall);
}


API void  CfgRegServerInfo(void)
{
	s8 abyIp[20];
	GetIPStr(g_tALLConfigData.m_tTPSipRegistrarCfg.dwRegIP, abyIp);
	msgprintnotime("[%s]\n", umsSipReg);
	msgprintnotime("%s = %d\n", umsKeySipRegUsed, g_tALLConfigData.m_tTPSipRegistrarCfg.bUsed);
	msgprintnotime("%s = %s\n", umsKeySipRegIP, abyIp);
	msgprintnotime("%s = %d\n", umsKeySipRegPort, g_tALLConfigData.m_tTPSipRegistrarCfg.wRegPort);
	msgprintnotime("%s = %d\n", umsKeySipRegExpire, g_tALLConfigData.m_tTPSipRegistrarCfg.wExpire);
}


API void  CfgGKRegServerInfo(void)
{
	s8 abyIp[20];
	GetIPStr(g_tALLConfigData.m_tGKRegCfg.dwGKIP, abyIp);
	msgprintnotime("[%s]\n", umsGKReg);
	msgprintnotime("%s = %d\n", umsKeyGKRegUsed, g_tALLConfigData.m_tGKRegCfg.bUsed);
	msgprintnotime("%s = %s\n", umsKeyGKRegIP, abyIp);
	msgprintnotime("%s = %d\n", umsKeyGKRegExpire, g_tALLConfigData.m_tGKRegCfg.wExpire);
}


API void CfgRegUmsCallInfo(void)
{
	msgprintnotime("[%s]\n", umsSipCall);
	msgprintnotime("%s = %d\n", umsKeySipCallingPort, g_tALLConfigData.m_tSipStackCallCfg.m_wCallingPort);
	msgprintnotime("%s = %d\n", umsKeySipMaxCallNum, g_tALLConfigData.m_tSipStackCallCfg.m_wMaxCallNum);
	msgprintnotime("%s = %d\n", umsKeySipCallKeepAliveTime, g_tALLConfigData.m_tSipStackCallCfg.m_dwKeepAliveTime);
}

API void QtInfo(void)
{
	msgprintnotime("[%s]\n", umsSecQuanTumEncInfo);
	msgprintnotime("%s = %d\n", umsKeyQtOn, g_tALLConfigData.m_tTPQTEncryptInfo.m_bIsEncQT);
	msgprintnotime("%s = "TPIPFORMAT"\n", umsKeyQTIP, u32ToIP(g_tALLConfigData.m_tTPQTEncryptInfo.m_dwQuanTumIP));
	msgprintnotime("%s = %d\n", umsKeyQTID, g_tALLConfigData.m_tTPQTEncryptInfo.m_dwQuanTumID);
}

API void PwdCycleInfo(void)
{
	msgprintnotime("[%s]\n", umsPwdCycleInfo);
	msgprintnotime("%s = %d\n", umsPwdCycleUsed, g_tALLConfigData.m_tPwdCycleInfo.m_bStartUpdate);
	msgprintnotime("%s = %d\n", umsPwdCycleTimer, g_tALLConfigData.m_tPwdCycleInfo.m_emPwdCycle);

}

API void  CfgNtpdInfo(void)
{
	s8 abyIp[20];
	GetIPStr(g_tALLConfigData.m_tNtpdInfo.m_dwNtpdIp, abyIp);
	msgprintnotime("[%s]\n", umsNtpdInfo);
	msgprintnotime("%s = %s\n", umsNtpdIp, abyIp);
}

API void showcfg()
{
	CfgLocalUmsInfo();
	
	msgprintnotime("\n");
	CfgRegServerInfo();
	
	msgprintnotime("\n");
	CfgGKRegServerInfo();
	
	msgprintnotime("\n");
	CfgRegUmsCallInfo();
	
	msgprintnotime("\n");
	QtInfo();

	msgprintnotime("\n");
	PwdCycleInfo();
	
	msgprintnotime("\n");
	CfgNtpdInfo();

	CUmsConfigEx::GetInstance()->ShowAll();
	CJDConfig::GetInstance()->ShowAll();
}

API void cfgexsetvmpupstyle(BOOL32 bUpStyle)
{
	CUmsConfigEx::GetInstance()->SetVmptpStyleUp(bUpStyle);
	msgprintnotime("cfgex GetVmptpStyleUp:%d.\n", CUmsConfigEx::GetInstance()->GetVmptpStyleUp());
	msgprintnotime("\n");
}


API void cfgexsetmcuon(BOOL32 bMcuOn)
{
	CUmsConfigEx::GetInstance()->SetCasecadeMcuOn(bMcuOn);
	msgprintnotime("cfgex IsCasecadeMcuOn:%d.\n", CUmsConfigEx::GetInstance()->IsCasecadeMcuOn());
	msgprintnotime("\n");
}


API void cfgexsetvmpused(BOOL32 bVmpUsed)
{
	CUmsConfigEx::GetInstance()->SetVmpUsed(bVmpUsed);
	msgprintnotime("cfgex IsVmpUsed:%d.\n", CUmsConfigEx::GetInstance()->GetVmpUsed());
	msgprintnotime("\n");
}

API void cfgexreload()
{
	CUmsConfigEx::GetInstance()->ReadFromFile();
	CUmsConfigEx::GetInstance()->ShowAll();
}

API void cfgexsetxmpu5used(BOOL32 bUsed)
{
	CUmsConfigEx::GetInstance()->SetXmpu5Used(bUsed);
	msgprintnotime("cfgex IsXmpu5Used:%d.\n", CUmsConfigEx::GetInstance()->GetXmpu5Used());
	msgprintnotime("\n");
}

API void cfgver();
API void SaveData();
API void ResetAllData();

API void cfghelp()
{
	msgprintnotime("cfgver()                                          --  cfgver\n");
	msgprintnotime("showcfg()                                         --  显示config信息\n");
	msgprintnotime("SaveData()                                        --  保存所有cfg配置\n");
	msgprintnotime("ResetAllData()                                    --  恢复所有的默认配置\n\n");


	msgprintnotime("cfgexreload()                                     --  重新载入debug配置文件\n");
	msgprintnotime("cfgexsetmcuon(BOOL32 bMcuOn)                      --  设置是否开启级联mcu能力(debug配置)\n");
	msgprintnotime("cfgexsetvmpused(BOOL32 bMcuOn)                    --  设置是否发言人合成(debug配置)\n\n");
}

void regist_configRegCommand()
{
#ifdef _LINUX_
	OspRegCommand("cfghelp", (void*)cfghelp, "cfghelp()");
	OspRegCommand("cfgver", (void*)cfgver, "cfgver()");
	OspRegCommand("showcfg", (void*)showcfg, "showcfg()");
	OspRegCommand("SaveData", (void*)SaveData, "SaveData()");
	OspRegCommand("ResetAllData", (void*)ResetAllData, "ResetAllData()");

	OspRegCommand("cfgexreload", (void*)cfgexreload, "cfgexreload()");
	OspRegCommand("cfgexsetmcuon", (void*)cfgexsetmcuon, "cfgexsetmcuon(BOOL32)");
	OspRegCommand("cfgexsetvmpupstyle", (void*)cfgexsetvmpupstyle, "cfgexsetvmpupstyle(BOOL32)");
	OspRegCommand("cfgexsetvmpused", (void*)cfgexsetvmpused, "cfgexsetvmpused(BOOL32)");
	OspRegCommand("cfgexsetxmpu5used", (void*)cfgexsetxmpu5used, "cfgexsetxmpu5used(BOOL32)");
#endif
}

