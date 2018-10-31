
#include "cfgdata.h"

TALLConfigData g_tALLConfigData;

inline void UmsCfg_DefaultLocalUmsInfo(TLocalUmsInfo& tLocalCnsInfo)
{
	tLocalCnsInfo.m_tEth.dwIP = inet_addr("192.169.1.1");
	tLocalCnsInfo.m_tEth.dwMask = inet_addr("255.255.255.0");
	tLocalCnsInfo.m_tEth.dwGateWay = 0;
	tLocalCnsInfo.m_tEth.bEnable = 0;

	tLocalCnsInfo.m_tVirEth.dwIP = inet_addr("0.0.0.0");
	tLocalCnsInfo.m_tVirEth.dwMask = inet_addr("0.0.0.0");
	tLocalCnsInfo.m_tVirEth.dwGateWay = 0;
	tLocalCnsInfo.m_tVirEth.bEnable = 0;

	tLocalCnsInfo.m_tEth1.dwIP = inet_addr("0.0.0.0");
	tLocalCnsInfo.m_tEth1.dwMask = inet_addr("0.0.0.0");
	tLocalCnsInfo.m_tEth1.dwGateWay = 0;
	tLocalCnsInfo.m_tEth1.bEnable = 0;

	tLocalCnsInfo.m_tVirEth1.dwIP = inet_addr("0.0.0.0");
	tLocalCnsInfo.m_tVirEth1.dwMask = inet_addr("0.0.0.0");
	tLocalCnsInfo.m_tVirEth1.dwGateWay = 0;
	tLocalCnsInfo.m_tVirEth1.bEnable = 0;
	tLocalCnsInfo.m_wListionPortForUi = UMS_LISTIONPORT_CMS;
	tLocalCnsInfo.m_wBeginUdpTransPort = UMS_EP_TRANS_BEGIN_PORT;
	tLocalCnsInfo.m_wNumMaxOnecCall = 8;
	tLocalCnsInfo.m_dwUmsoldIP = inet_addr("0.0.0.0");
}

inline void UmsCfg_DefaultSipRegCfg(TTPSipRegistrarCfg& tSipRegCfg)
{
	tSipRegCfg.bUsed = FALSE;
	tSipRegCfg.dwRegIP = 0;
	tSipRegCfg.wRegPort = TP_UMS_SIP_LISTIEN_PORT;
	tSipRegCfg.wExpire = TP_EXPIRE_TIME;//100;
    memset(tSipRegCfg.achRegDomain, 0, sizeof(tSipRegCfg.achRegDomain));
	memset(tSipRegCfg.atTPRegName, 0, sizeof(tSipRegCfg.atTPRegName));
	memset(tSipRegCfg.achHostDomain, 0, sizeof(tSipRegCfg.achHostDomain));
	tSipRegCfg.dwHostIP = 0;
	tSipRegCfg.nTPRegNameSize = 0;
	tSipRegCfg.wHostPort = 0;
}

inline void UmsCfg_DefaultGKRegCfg(TTPGKCfg& tGKRegCfg)
{
	tGKRegCfg.bUsed = FALSE;
	tGKRegCfg.dwGKIP = 0;
	tGKRegCfg.wExpire = TP_EXPIRE_TIME;//30;
	memset(tGKRegCfg.achGkIpName, 0, sizeof(tGKRegCfg.achGkIpName));
	memset(tGKRegCfg.achGKPasswd, 0, sizeof(tGKRegCfg.achGKPasswd));
}

inline void UmsCfg_DefaultSipCallCfg(TUmsStackCallCfg& tSipCallCfg)
{
	tSipCallCfg.m_wCallingPort = TP_UMS_SIP_LISTIEN_PORT;
	tSipCallCfg.m_wMaxCallNum = TP_UMS_MAX_CALLNUM;
	tSipCallCfg.m_dwKeepAliveTime = TP_ROUNDTRIP_TIME;	
}

inline void umsCfg_DefaultQTEncryptInfo( TTPQTEncryptInfo &tTPQTEncryptInfo )
{
	tTPQTEncryptInfo.m_dwQuanTumIP = 0;
	tTPQTEncryptInfo.m_dwQuanTumID = 0;
}

inline void umsCfg_DefaultPwdCycleInfo( TPwdCycleInfo &tTPwdCycleInfo )
{
	tTPwdCycleInfo.m_bStartUpdate = FALSE;
	tTPwdCycleInfo.m_emPwdCycle = em_One_Month;
}

inline void umsCfg_DefaultNtpdInfo( TNtpdInfo &tNtpdInfo)
{
	tNtpdInfo.m_dwNtpdIp = 0;
}

BOOL InitData()
{
	UmsCfg_DefaultLocalUmsInfo( g_tALLConfigData.m_tLocalCnsInfo );
	UmsCfg_DefaultSipRegCfg( g_tALLConfigData.m_tTPSipRegistrarCfg );
	UmsCfg_DefaultGKRegCfg( g_tALLConfigData.m_tGKRegCfg );
	UmsCfg_DefaultSipCallCfg( g_tALLConfigData.m_tSipStackCallCfg );

	//…Ë÷√QT ƒ¨»œ≈‰÷√
	umsCfg_DefaultQTEncryptInfo( g_tALLConfigData.m_tTPQTEncryptInfo );
	umsCfg_DefaultPwdCycleInfo (g_tALLConfigData.m_tPwdCycleInfo);
	umsCfg_DefaultNtpdInfo (g_tALLConfigData.m_tNtpdInfo);
	return TRUE;
}



