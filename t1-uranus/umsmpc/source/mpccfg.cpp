#include "mpccfg.h"
#include "kdvsys.h"
#include "tplog.h"
#include "umsapi.h"

extern s8* GetMpcCfgFile();

u32 g_dwLocalIp = 0;
u32 g_dwUmsListenIp = 0;
u16 g_wUmsListenPort = UMS_LISTIONPORT_CMS;
s8  g_achAlias[16];
u16 g_wVersion = 0;
TTPTime g_tSetTime;	//配置本地时间的时间

API void showcfg()
{
	msgprintnotime("MpcVersion = %d\n", g_wVersion);
	msgprintnotime("LocalIP = "TPIPFORMAT"\n", Tpu32ToIP(g_dwLocalIp));
	msgprintnotime("UmsIP = "TPIPFORMAT"\n", Tpu32ToIP(g_dwUmsListenIp));
	msgprintnotime("UmsPort = %d\n", g_wUmsListenPort);
	msgprintnotime("MpcAlias = %s\n", g_achAlias);
	msgprintnotime("SetTime = %d-%d-%d %d:%d:%d\n", g_tSetTime.m_wYear, g_tSetTime.m_byMonth, g_tSetTime.m_byMDay, g_tSetTime.m_byHour, g_tSetTime.m_byMinute, g_tSetTime.m_bySecond);
}

API void setumsip( s8* uIp )
{
	g_dwUmsListenIp = inet_addr(uIp);
}

API void setmpcalias(s8* mpcalias)
{
	if (NULL == mpcalias)
	{
		return;
	}
	strncpy(g_achAlias, mpcalias, sizeof(g_achAlias));
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
void ReadSetTime();
void ReadMpcCfg()
{
	BOOL32 bRet;
	s8 szData[512];
	memset( &szData, 0, sizeof(szData) );

	g_dwLocalIp = GetLocalEqpIp();
	msgprint(" Read ums IP. localip:"TPIPFORMAT"\n", Tpu32ToIP(g_dwLocalIp));
	

	g_dwUmsListenIp = GetLocalEqpIp();
	msgprint(" Read ums IP:"TPIPFORMAT"\n", Tpu32ToIP(g_dwUmsListenIp));


	int value = 0;
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "UmsPort", UMS_LISTIONPORT_CMS, &value);
	if( !bRet)
	{
		msgprint(" Read umsport Failed. \n");
		g_wUmsListenPort = UMS_LISTIONPORT_CMS;
	}
	else
	{
		g_wUmsListenPort = value;
		msgprint(" Read umsport:%d.\n", g_wUmsListenPort);
	}

	bRet = GetRegKeyString(GetMpcCfgFile(), "LocalInfo", "MpcAlias", "mpc", szData, sizeof(szData));
	if (!bRet)
	{
		msgprint(" Read Mpc Alias Failed!\n");
		memcpy(g_achAlias, "mpc", sizeof(g_achAlias));
	}
	else
	{
		Trim(szData);
		memcpy(g_achAlias, szData, sizeof(g_achAlias));
		msgprint("Read Mpc Alias %s\n", g_achAlias);
	}
	
	value = 0;
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "MpcVersion", 0, &value);
	if (!bRet)
	{
		msgprint(" Read Regist Version Failed. \n");
		g_wVersion = 0;
	}
	else
	{
		g_wVersion = value;
		msgprint("Read Regist Version %d\n", g_wVersion);
	}

	ReadSetTime();
}
void ReadSetTime()
{
	BOOL32 bRet;
	int value = 0;
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetYear", 0, &value);
	if( !bRet)
	{
		msgprint(" Read SetYear Failed. \n");
		g_tSetTime.m_wYear = 0;
	}
	else
	{
		g_tSetTime.m_wYear = value;
		msgprint(" Read SetYear:%d.\n", g_tSetTime.m_wYear);
	}
	
	
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetMonth", 0, &value);
	if( !bRet)
	{
		msgprint(" Read SetMonth Failed. \n");
		g_tSetTime.m_byMonth = 0;
	}
	else
	{
		g_tSetTime.m_byMonth = value;
		msgprint(" Read SetMonth:%d.\n", g_tSetTime.m_byMonth);
	}
	
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetDay", 0, &value);
	if( !bRet)
	{
		msgprint(" Read SetDay Failed. \n");
		g_tSetTime.m_byMDay = 0;
	}
	else
	{
		g_tSetTime.m_byMDay = value;
		msgprint(" Read SetDay:%d.\n", g_tSetTime.m_byMDay);
	}
	
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetHour", 0, &value);
	if( !bRet)
	{
		msgprint(" Read SetHour Failed. \n");
		g_tSetTime.m_byHour = 0;
	}
	else
	{
		g_tSetTime.m_byHour = value;
		msgprint(" Read SetHour:%d.\n", g_tSetTime.m_byHour);
	}
	
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetMinute", 0, &value);
	if( !bRet)
	{
		msgprint(" Read SetMinute Failed. \n");
		g_tSetTime.m_byMinute = 0;
	}
	else
	{
		g_tSetTime.m_byMinute = value;
		msgprint(" Read SetMinute:%d.\n", g_tSetTime.m_byMinute);
	}
	
	bRet = GetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetSecond", 0, &value);
	if( !bRet)
	{
		msgprint(" Read SetSecond Failed. \n");
		g_tSetTime.m_bySecond = 0;
	}
	else
	{
		g_tSetTime.m_bySecond = value;
		msgprint(" Read SetSecond:%d.\n", g_tSetTime.m_bySecond);
	}
}

void WriteSetTime()
{
	SetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetYear", g_tSetTime.m_wYear);
	SetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetMonth", g_tSetTime.m_byMonth);
	SetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetDay", g_tSetTime.m_byMDay);
	SetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetHour", g_tSetTime.m_byHour);
	SetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetMinute", g_tSetTime.m_byMinute);
	SetRegKeyInt(GetMpcCfgFile(), "LocalInfo", "SetSecond", g_tSetTime.m_bySecond);
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

u16 GetMpcVersion()
{ 
	return ntohs(g_wVersion);
}

const s8* GetMpcAlias()
{
	return g_achAlias;
}
