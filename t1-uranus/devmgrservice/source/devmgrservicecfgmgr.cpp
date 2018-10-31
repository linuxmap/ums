#include "kdvtype.h"
#include "kdvdef.h"
#include "tplog.h"
#include "tpsys.h"
#include "kdvsys.h"
#include "devmgrserviceinst.h"
#include "umsapi.h"
#include "umsxmltype.h"

s8 sz_ServiceCfg[] = "ServiceCfg";
s8 sz_ServiceIP[] = "LocalIP";

s8 sz_DevCfgInfo[] = "DevCfgInfo_";
s8 sz_DevType[] = "DevType";
s8 sz_DevUpdateType[] = "UpdateType";
s8 sz_DevVer[] = "DevVer";
s8 sz_DevFileName[] = "FilePathName";

TDevMgrCfg g_tDevMgrCfg;

extern s8* GetUpdateServiceCfgFile();
BOOL32 GetIntValue( s8* lpszSectionName, s8* lpszKeyName, s32* pdwRetValue )
{
	BOOL32 bRet = GetRegKeyInt( GetUpdateServiceCfgFile(),
		lpszSectionName, 
		lpszKeyName,
		-1, pdwRetValue);
	if( !bRet)
	{
		//msgprintnotime(" Read Dev Cfg Failed! SectionName:%s, KeyName:%s\n", lpszSectionName, lpszKeyName);
	}

	return bRet;
}

BOOL32 GetStringValue(s8* lpszSectionName, s8* lpszKeyName, s8* pszRetValue, u32 szRetValueLen)
{
	BOOL32 bRet = GetRegKeyString( GetUpdateServiceCfgFile(),
		lpszSectionName, 
		lpszKeyName,
		"",
		pszRetValue,
		szRetValueLen);
	if( !bRet)
	{
		//msgprintnotime(" Read Dev Cfg Failed! SectionName:%s, KeyName:%s\n", lpszSectionName, lpszKeyName);
	}
	
	return bRet;
}

void ReadUpdateInfoCfg()
{
	memset(&g_tDevMgrCfg.m_tUpdateCfg, 0, sizeof(g_tDevMgrCfg.m_tUpdateCfg));

	u16				wCfgNum = 0;
	s8				szKeySectionNameTmp[64] = {0};
	TDevUpdateCfg	tCfgTmp;
	s32				sIntValue = -1;
	for ( u16 wIndex = 0; wIndex < DEV_CFG_MAX_CFG; wIndex ++)
	{
		tCfgTmp.Clear();
		tCfgTmp.m_bUsed = TRUE;
		
		memset(szKeySectionNameTmp, 0, sizeof(szKeySectionNameTmp));
		sprintf(szKeySectionNameTmp, "%s%d", sz_DevCfgInfo, wIndex);
		
		//读取设备类型
		if(!GetIntValue(szKeySectionNameTmp, sz_DevType, &sIntValue))
		{
			continue;
		}
		else
		{
			tCfgTmp.m_emDevType = (EmTPDevRegUpdateSer)sIntValue;
		}
		
		//读取升级方式
		if(!GetIntValue(szKeySectionNameTmp, sz_DevUpdateType, &sIntValue))
		{
			tCfgTmp.m_emTPUpdateType = emTPUpdateForced;
		}
		else
		{
			tCfgTmp.m_emTPUpdateType = (EmTPUpdateType)sIntValue;
		}
		
		//读取版本号
		if(!GetStringValue(szKeySectionNameTmp, sz_DevVer, tCfgTmp.m_acDevVer, MAX_DEVICEVER_LEN))
		{
			continue;
		}
		else
		{
			if ( 0 == strlen(tCfgTmp.m_acDevVer) )
			{
				continue;
			}
		}
		
		//读取文件名
		if(!GetStringValue(szKeySectionNameTmp, sz_DevFileName, tCfgTmp.m_achFileName, TP_MAX_FILESRV_FILENAME_LEN))
		{
			continue;
		}
		else
		{
			if ( 0 == strlen(tCfgTmp.m_achFileName) )
			{
				continue;
			}
		}
		
		msgprintnotime(" Read Dev Cfg! Index:%d DevType:%d-%s UpdateType:%d-%s Ver:%s FileName:%s \n", 
			wIndex, 
			TpEnumIdString( EmTPDevRegUpdateSer, tCfgTmp.m_emDevType), 
			TpEnumIdString(EmTPUpdateType, tCfgTmp.m_emTPUpdateType), 
			tCfgTmp.m_acDevVer, tCfgTmp.m_achFileName);
		
		memcpy(&g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wCfgNum], &tCfgTmp, sizeof(tCfgTmp));
		wCfgNum ++;
	}

	g_tDevMgrCfg.m_tUpdateCfg.m_wDevCfgNum = wCfgNum;
}

void ReadServiceLocalCfg()
{
	s8 szData[512];
	memset( &szData, 0, sizeof(szData) );
	s32 sIntValue = -1;

	if(GetStringValue(sz_ServiceCfg, sz_ServiceIP, szData, sizeof(szData)))
	{
		Trim(szData);
		g_tDevMgrCfg.m_dwLocalSerIP = inet_addr(szData);
	}
	else
	{
		u32 dwIp = CTpTypeAdpt::GetLocalIP(0);
		if (dwIp == 0)
		{
			dwIp = CTpTypeAdpt::GetLocalIP(1);
		}
		
		g_tDevMgrCfg.m_dwLocalSerIP = dwIp;
	}

	msgprintnotime(" Ftp Service IP:"TPIPFORMAT" \n", Tpu32ToIP(g_tDevMgrCfg.m_dwLocalSerIP));
	
	return ;
}

void ReadDevMgrServiceCfg()
{
	//升级配置信息
	ReadUpdateInfoCfg();
	
	//升级服务器ftpip
	ReadServiceLocalCfg();
	
	return ;
}