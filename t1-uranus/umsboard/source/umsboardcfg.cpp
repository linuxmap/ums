#include "umsboardcfg.h"
#include "umsapi.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
#include "nipwrapper.h"
#endif

TBrdCfgBase g_tBrdCfg;  //单板基本配置信息

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
// 默认值取决于驱动设置
BOOL32 g_bBrdTelnetPortOn = TRUE; // 板卡的telnetport默认放开
BOOL32 g_bBrdFtpOn = TRUE; // 板卡的ftp默认放开 
#endif

s8* GetBrdCfgBaseFile()
{
	return emUmsBrdCfg;
}

static inline BOOL32 FileIsValid(FILE* pfFILE)
{
	fseek(pfFILE,0L,SEEK_END);
	u32  dwLen = ftell(pfFILE);
	return (dwLen > 0);
}

static void ReadLocalInfo()
{
	s8 szData[512];
	memset( &szData, 0, sizeof(szData) );
	BOOL32 bRet;
	bRet = GetRegKeyString(GetBrdCfgBaseFile(), "LocalInfo", "UmsIp", "127.0.0.1", szData, sizeof(szData));
	if (!bRet)
	{
		msgprint("read umsip failure.\n");
		g_tBrdCfg.m_dwUmsListenIp = inet_addr("127.0.0.1");
		
	}
	else
	{
		Trim(szData);
		g_tBrdCfg.m_dwUmsListenIp = inet_addr(szData);
		msgprint("read ums IP:"TPIPFORMAT".\n", Tpu32ToIP(g_tBrdCfg.m_dwUmsListenIp));
	}
	
	int wValue = 0;
	
	bRet = GetRegKeyString(GetBrdCfgBaseFile(), "LocalInfo", "BrdIp", "127.0.0.1", szData, sizeof(szData));
	if (!bRet)
	{
		msgprint("read board ip failure.\n");
		g_tBrdCfg.m_tBrdPos.m_dwBrdIP = inet_addr("127.0.0.1");
	}
	else
	{
		Trim(szData);
		g_tBrdCfg.m_tBrdPos.m_dwBrdIP = inet_addr(szData);
		msgprint("read board IP:"TPIPFORMAT".\n", Tpu32ToIP(g_tBrdCfg.m_tBrdPos.m_dwBrdIP));
	}
}

void ReadBrdCfgBaseInfo()
{
	msgprint("[ReadBrdCfgBaseInfo] Begin Read.\n");

	const s8* pszCfgFile = GetBrdCfgBaseFile();
	if (NULL == pszCfgFile)
	{
		msgprint("read failure\n");
		return ;

	}
	FILE* pfFile = fopen(pszCfgFile,"rb"); //文件不存在，创建
	if (NULL == pfFile)
	{
		msgprint("open brdcfg file %s failure. \n", pszCfgFile);
		pfFile = fopen(pszCfgFile, "w");
		if (NULL != pfFile)
		{
			fclose(pfFile);
			pfFile = NULL;
		}
		//默认值写到文件里
		WriteDefautCfgToFile();
	}

	if( NULL == pfFile )
	{
		pfFile = fopen(pszCfgFile,"rb");
		
		if ( pfFile == NULL )
		{
			msgprint("open file %s fail !!! \n", pszCfgFile);
			return ;
		}
	}

	if (!FileIsValid(pfFile))
	{
		WriteDefautCfgToFile();
	}

	if ( NULL != pfFile )
	{
		fclose(pfFile);
		pfFile = NULL;
	}

	ReadLocalInfo();

#ifdef WIN32
	s8 szData[512];
	memset( &szData, 0, sizeof(szData) );
	BOOL32 bRet;
	int wValue = 0;
	bRet = GetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Layer", TP_INVALID_INDEX, &wValue);
	if (!bRet)
	{
		msgprint("read board layer failure.\n");
		g_tBrdCfg.m_tBrdPos.m_byBrdLayer = (u8)TP_INVALID_INDEX;
	}
	else
	{
		g_tBrdCfg.m_tBrdPos.m_byBrdLayer = wValue;
		msgprint("read board layer:%d.\n", g_tBrdCfg.m_tBrdPos.m_byBrdLayer);
	}
	
	bRet = GetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Slot", TP_INVALID_INDEX, &wValue);
	if (!bRet)
	{
		msgprint("read board slot failure.\n");
		g_tBrdCfg.m_tBrdPos.m_byBrdSlot = (u8)TP_INVALID_INDEX;
	}
	else
	{
		g_tBrdCfg.m_tBrdPos.m_byBrdSlot = wValue;
		msgprint("read board slot:%d.\n", g_tBrdCfg.m_tBrdPos.m_byBrdSlot);
	}
	bRet = GetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Type", em_unknow_brd, &wValue);
	if (!bRet)
	{
		msgprint("read board type failure.\n");
		g_tBrdCfg.m_tBrdPos.m_emBrdType = em_unknow_brd;
	}
	else
	{
		g_tBrdCfg.m_tBrdPos.m_emBrdType = (EMBrdType)wValue;
		msgprint("read board type:(%d->%s).\n", TpEnumIdString(EMBrdType, g_tBrdCfg.m_tBrdPos.m_emBrdType));
	}
#endif

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	TBrdPosition tPos;
	if (ERROR == BrdQueryPosition(&tPos))
	{
		msgprint("[ReadBrdCfgBaseInfo] read board TBrdPosition error !\n ");
		return;
	}
	else
	{
		msgprint("[ReadBrdCfgBaseInfo] read board TBrdPosition right, id:%d, layer:%d, slot:%d.\n", tPos.byBrdID, tPos.byBrdLayer, tPos.byBrdSlot);
		
		g_tBrdCfg.m_tBrdPos.m_byBrdLayer = tPos.byBrdLayer;
		g_tBrdCfg.m_tBrdPos.m_byBrdSlot = tPos.byBrdSlot;

#ifdef _LINUX12_
		TBrdE2PromInfo tBrdE2PromInfo;
		memset( &tBrdE2PromInfo, 0x0, sizeof(tBrdE2PromInfo) );

		u32 dwBrdID = 0;
		if (ERROR == BrdGetE2PromInfo(&tBrdE2PromInfo))
		{
			msgprint("[ReadBrdCfgBaseInfo] BrdGetE2PromInfo error!\n");
			return ;
		}
		if ( BRD_PID_KDV8000A_MPU2 == tBrdE2PromInfo.dwProductId )
		{
			msgprint("[ReadBrdCfgBaseInfo] BRD_PID_KDV8000A_MPU2! %d\n", BRD_HWID_MPU2);

			dwBrdID = BRD_HWID_MPU2;

		}

		g_tBrdCfg.m_tBrdPos.m_emBrdType = ConverBrdID(dwBrdID);
#else
		g_tBrdCfg.m_tBrdPos.m_emBrdType = ConverBrdID(tPos.byBrdID);
#endif
		

		SetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Layer", tPos.byBrdLayer);
		SetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Slot", tPos.byBrdSlot);
		SetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Type", g_tBrdCfg.m_tBrdPos.m_emBrdType);
	}

#endif
}

void WriteDefautCfgToFile()
{
	SetRegKeyString(GetBrdCfgBaseFile(), "LocalInfo", "UmsIp", "127.0.0.1");
	SetRegKeyString(GetBrdCfgBaseFile(), "LocalInfo", "BrdIp", "127.0.0.1");
	SetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Layer", (u8)TP_INVALID_INDEX);
	SetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Slot", (u8)TP_INVALID_INDEX);
	SetRegKeyInt(GetBrdCfgBaseFile(), "BoardConfig", "Type", em_unknow_brd);
}

TBrdCfgBase GetBrdCfgBase()
{
	return g_tBrdCfg;
}

void SetBrdCfgBase(const TBrdCfgBase& tCfg)
{
	g_tBrdCfg = tCfg;
}

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

API void StartNtpd()
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	CTpTypeAdpt::StartNtpd(g_tBrdCfg.m_dwUmsListenIp);
#endif
}


API void telnetportoff()
{// 通过iptables限制23端口，关闭板卡对外telnet服务
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	system("/usr/bin/telnetportonoff.sh off &");
	g_bBrdTelnetPortOn = FALSE;
#else
	msgprint("This command is not valid!\n");
#endif
}

API void telnetporton()
{// 通过iptables放开23端口，开启板卡对外telnet服务
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	system("/usr/bin/telnetportonoff.sh on &");
	g_bBrdTelnetPortOn = TRUE;
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
		g_bBrdFtpOn = TRUE;
	}
	else 
	{
		BrdDisableFtpd();
		g_bBrdFtpOn = FALSE;
	}
#else
	msgprint("This command is not valid!\n");	
#endif	
}

API BOOL32 checkftp()
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
    STATUS nRet = BrdFtpdStatus();
	if (1 == nRet)
	{
		msgprint("The Ftp status is on, check ret is %d.\n", nRet);
		return TRUE;
	}
	else  
	{
		msgprint("The Ftp status is Off, check ret is %d.\n", nRet);
		return FALSE;
	}
#else
	msgprint("This command is not valid!\n");
	return FALSE;	
#endif	
}

API void showftptel()
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	msgprint("g_bBrdTelnetPortOn=%d, g_bBrdFtpOn=%d.\n", g_bBrdTelnetPortOn, g_bBrdFtpOn);
#endif
}
