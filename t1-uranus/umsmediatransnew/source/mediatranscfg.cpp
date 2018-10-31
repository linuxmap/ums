#include "mediatranscfg.h"
#include "kdvsys.h"
#include "tplog.h"
#include "umsapi.h"
extern s8* GetMediatransCfgFile();

u32 g_dwLocalIp = 0;
TIpmaskinfo	g_tIpMaskInfo;
u32 g_dwUmsListenIp = 0;
u16 g_wUmsListenPort = UMS_LISTIONPORT_CMS;
u32 g_dwTest = 0;

API void settest(u32 dwTest)
{
	g_dwTest = dwTest;
	msgprintnotime("g_dwTest = %d.\n", g_dwTest);
}

API void showcfg()
{
	msgprintnotime("LocalIP = "TPIPFORMAT"\n", Tpu32ToIP(g_dwLocalIp));
	msgprintnotime("UmsIP = "TPIPFORMAT"\n", Tpu32ToIP(g_dwUmsListenIp));
	msgprintnotime("UmsPort = %d\n", g_wUmsListenPort);
	msgprintnotime("g_tIpMaskInfo ipa:"TPIPFORMAT", maska:"TPIPFORMAT", ipb:"TPIPFORMAT", maskb:"TPIPFORMAT", outip:"TPIPFORMAT".\n",
		Tpu32ToIP(g_tIpMaskInfo.m_dwIpa), Tpu32ToIP(g_tIpMaskInfo.m_dwMaska), 
		Tpu32ToIP(g_tIpMaskInfo.m_dwIpb), Tpu32ToIP(g_tIpMaskInfo.m_dwMaskb),
		Tpu32ToIP(g_tIpMaskInfo.m_dwOutIp));
	msgprintnotime("g_dwTest = %d.\n", g_dwTest);
}

static u32 GetLocalEqpIp()
{
	u32 dwIp = CTpTypeAdpt::GetLocalIPPerfer(0,2);
	if (0 == dwIp)
	{
		dwIp = CTpTypeAdpt::GetLocalIPPerfer(1,2);
	}
	return dwIp;	 
}
void ReadMediatransCfg()
{
	BOOL32 bRet;
	s8 szData[512];
	memset( &szData, 0, sizeof(szData) );

#ifndef WIN32
	g_tIpMaskInfo.m_dwIpa = CTpTypeAdpt::GetLocalIPPerfer(0,2);
	g_tIpMaskInfo.m_dwIpb = CTpTypeAdpt::GetLocalIPPerfer(1,2);
	g_tIpMaskInfo.m_dwMaska = CTpTypeAdpt::GetLocalNetMaskPerfer(0,2);
	g_tIpMaskInfo.m_dwMaskb = CTpTypeAdpt::GetLocalNetMaskPerfer(1,2);
#endif

	const s8* pszCfgFile = GetMediatransCfgFile();
	bRet = GetRegKeyString( pszCfgFile,
		"LocalInfo", 
		"BrdIp",
		"127.0.0.1",
		szData,
		sizeof(szData) );
	if( !bRet)
	{
		g_dwLocalIp = GetLocalEqpIp();
		msgprint(" Read LocalIP failed. usr localip:"TPIPFORMAT"\n", Tpu32ToIP(g_dwLocalIp));
	}
	else
	{
		Trim(szData);
		msgprint(" Local ip:%s.\n", szData);
		g_dwLocalIp = inet_addr(szData);
	}

	memset( &szData, 0, sizeof(szData) );
	bRet = GetRegKeyString( pszCfgFile,
		"LocalInfo", 
		"BrdOutIp",
		"127.0.0.1",
		szData,
		sizeof(szData) );
	if( !bRet)
	{		
		g_tIpMaskInfo.m_dwOutIp = 0;
		msgprint(" Read brdout IP failed. usr outip:"TPIPFORMAT"\n", Tpu32ToIP(g_tIpMaskInfo.m_dwOutIp));
	}
	else
	{
		Trim(szData);
		msgprint(" LocalOutIp ip:%s.\n", szData);
		g_tIpMaskInfo.m_dwOutIp = inet_addr(szData);
	}

	memset( &szData, 0, sizeof(szData) );
	bRet = GetRegKeyString( pszCfgFile,
		"LocalInfo", 
		"UmsIp",
		"127.0.0.1",
		szData,
		sizeof(szData) );
	if( !bRet)
	{		
		g_dwUmsListenIp = GetLocalEqpIp();
		msgprint(" Read UmsIP failed. usr localip:"TPIPFORMAT"\n", Tpu32ToIP(g_dwLocalIp));
	}
	else
	{
		Trim(szData);
		msgprint(" ums ip:%s.\n", szData);
		g_dwUmsListenIp = inet_addr(szData);
	}

	int value = 0;
	bRet = GetRegKeyInt(pszCfgFile, "LocalInfo", "UmsPort", UMS_LISTIONPORT_CMS, &value);
	if( !bRet)
	{
		msgprint(" Read umsport Failed.\n");
		g_wUmsListenPort = UMS_LISTIONPORT_CMS;
	}
	else
	{
		g_wUmsListenPort = value;
		msgprint(" Read umsport:%d.\n", g_wUmsListenPort);
	}
}


u32 GetUmsListenIp()
{
	return g_dwUmsListenIp;
}

u16 GetUmsListenPort()
{
	return g_wUmsListenPort;
}

u32	GetLocalIP()
{
	return g_dwLocalIp;
}



