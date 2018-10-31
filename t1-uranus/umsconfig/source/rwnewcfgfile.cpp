#include "rwnewcfgfile.h"
#include "kdvsys.h"
#include <string.h>

static FILE* s_pfCfgFile = NULL;
extern s8 g_szFileName[];

template<class T>  
static BOOL ReadSimpleValFromFile(s8* abyBuf,
								  u16 wLen,
								  T& val,
								  const s8* const  Section,
								  const s8* const  Key)
{
	if(NULL == s_pfCfgFile)
	{
		msgprint("The FILE pointer is NULL at %s :%d\n",
			__FILE__,__LINE__);
		return FALSE;
	}
	BOOL bResult = FALSE;
	memset(abyBuf,0,wLen);
	bResult = GetRegKeyString2(s_pfCfgFile,Section,Key,"",abyBuf,wLen);
	if(!bResult) return FALSE;
	if(strlen(abyBuf) == 0) return FALSE;

	s32 dwVal = 0;
	sscanf(abyBuf,"%d",&dwVal);
	val = (T)dwVal;
	return TRUE;
}

/*====================================================================
  函 数 名： BOOL  ReadStringVal
  功    能： 
  算法实现： 
  全局变量： 
  参    数： s8* const achBuf
             u16 wLen
             const s8*const  szSection
             const s8*const szKey
  返 回 值： static inline 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/6/30      1.0		    张 飞                   创建
======================================================================*/
static inline BOOL  ReadStringVal(s8* const achBuf,
								  u16 wLen,
								  const s8*const  szSection,
								  const s8*const szKey)
{
	s8 achTemp[256] = {0};
	BOOL bResult = GetRegKeyString2(s_pfCfgFile,szSection,
		szKey,"",achTemp,sizeof(achTemp));
	if(!bResult) return FALSE;

	strncpy(achBuf,achTemp,wLen);
	achBuf[wLen -1] = '\0';
	return TRUE;
}
/*====================================================================
  函 数 名： void GetIPVal
  功    能： 
  算法实现： 
  全局变量： 
  参    数： s8* const achBuf
             u16 wLen
             u32& dwVal
             const s8* const szSection
             const s8* const szKey
  返 回 值： static inline 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/6/30      1.0		    张 飞                   创建
======================================================================*/
static inline void GetIPVal(s8* const achBuf,
							u16 wLen,
							u32& dwVal,
							const s8* const szSection ,
							const s8* const szKey )
{
	BOOL bResult = ReadStringVal(achBuf,wLen,szSection,szKey);
	if(!bResult) return ;
	
	Trim(achBuf);
	dwVal = inet_addr(achBuf);
}


//写配置文件，理想的情况下应该用文件指针代替这里的文件名称
#define WriteSimpleVal(val,section,key)\
{\
	SetRegKeyInt(g_szFileName,section,key,(s32)val);\
}\
	
#define WriteStringVal(val,section,key)\
{\
	SetRegKeyString(g_szFileName,section,key,(s8*)val);\
}

#define GetIPStr(dwIp,achStr)\
{\
	struct in_addr addr;\
	addr.s_addr = dwIp;\
	sprintf(achStr,IPFORMAT,u32ToIP(dwIp));\
}

#define WriteIpVal(buf,wLen,val,secton,key)\
{\
	memset(buf,0,wLen);\
	GetIPStr(val,buf);\
	WriteStringVal(buf,secton,key);\
}


static void  ReadLocalUmsInfoFromFile(TLocalUmsInfo& tInfo)
{
	s8 abyBuf[20] = {0};
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth.dwIP, umsLocalInfo, umsKeyUmsIp);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth.dwMask, umsLocalInfo, umsKeyNetMask);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth.dwGateWay, umsLocalInfo, umsKeyGateWay);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth.dwIP, umsLocalInfoVir, umsKeyUmsIpVir);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth.dwMask, umsLocalInfoVir, umsKeyNetMaskVir);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth.dwGateWay, umsLocalInfoVir, umsKeyGateWayVir);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth1.dwIP, umsLocalInfoEth1, umsKeyUmsIpEth1);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth1.dwMask, umsLocalInfoEth1, umsKeyNetMaskEth1);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth1.dwGateWay, umsLocalInfoEth1, umsKeyGateWayEth1);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth1.dwIP, umsLocalInfoEth1Vir, umsKeyUmsIpEth1Vir);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth1.dwMask, umsLocalInfoEth1Vir, umsKeyNetMaskEth1Vir);	
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth1.dwGateWay, umsLocalInfoEth1Vir, umsKeyGateWayEth1Vir);
	GetIPVal( abyBuf, sizeof(abyBuf), tInfo.m_dwUmsoldIP, umsLocalInfoEth1Vir, umsKeyOldIP);
}


static void  SaveLocalUmsInfoToFile(const TLocalUmsInfo& tInfo)
{
	s8 abyBuf[20] = {0};
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth.dwIP, umsLocalInfo, umsKeyUmsIp );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth.dwMask, umsLocalInfo, umsKeyNetMask );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth.dwGateWay, umsLocalInfo, umsKeyGateWay );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth.dwIP, umsLocalInfoVir, umsKeyUmsIpVir );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth.dwMask, umsLocalInfoVir, umsKeyNetMaskVir );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth.dwGateWay, umsLocalInfoVir, umsKeyGateWayVir );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth1.dwIP, umsLocalInfoEth1, umsKeyUmsIpEth1 );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth1.dwMask, umsLocalInfoEth1, umsKeyNetMaskEth1 );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tEth1.dwGateWay, umsLocalInfoEth1, umsKeyGateWayEth1 );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth1.dwIP, umsLocalInfoEth1Vir, umsKeyUmsIpEth1Vir );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth1.dwMask, umsLocalInfoEth1Vir, umsKeyNetMaskEth1Vir );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_tVirEth1.dwGateWay, umsLocalInfoEth1Vir, umsKeyGateWayEth1Vir );
	WriteIpVal( abyBuf, sizeof(abyBuf), tInfo.m_dwUmsoldIP, umsLocalInfoEth1Vir, umsKeyOldIP);

}


static void ReadSipRegCfgFromFile(TTPSipRegistrarCfg& tSipRegCfg)
{
	s8 abyBuf[20]={0};
	GetIPVal(abyBuf,sizeof(abyBuf),tSipRegCfg.dwRegIP, umsSipReg, umsKeySipRegIP);
	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tSipRegCfg.bUsed, umsSipReg, umsKeySipRegUsed );
}


static void ReadGKRegCfgFromFile(TTPGKCfg& tGKRegCfg)
{
	s8 abyBuf[20]={0};
	GetIPVal(abyBuf,sizeof(abyBuf),tGKRegCfg.dwGKIP, umsGKReg, umsKeyGKRegIP);
	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tGKRegCfg.bUsed, umsGKReg, umsKeyGKRegUsed );
	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tGKRegCfg.wExpire, umsGKReg, umsKeyGKRegExpire );
}


static void ReadSipCallCfgFromFile(TUmsStackCallCfg& tCall)
{
	s8 abyBuf[20]={0};
 	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tCall.m_wCallingPort, umsSipCall, umsKeySipCallingPort );
 	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tCall.m_wMaxCallNum, umsSipCall, umsKeySipMaxCallNum );
 	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tCall.m_dwKeepAliveTime, umsSipCall, umsKeySipCallKeepAliveTime );
}

/*读取单板配置信息*/
static void ReadBoardInfoFromFile()
{
	s8 abyBuf[40] = {0};
	ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), g_tALLConfigData.m_byBrdValidNum, umsBoardInfo, umsBoardValidNum);
	
	s8 abySectionBuf[48] = {0};
	s8 abyKeyBuf[48] = {0};
	
	TTPBrdInfo* ptBrdCfg = NULL;
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; ++wIndex)
	{
		ptBrdCfg = &g_tALLConfigData.m_atBrdCfg[wIndex];
		sprintf(abySectionBuf, "%s%d", umsBoardInfo_, wIndex);
		
		sprintf(abyKeyBuf, "%s%d", umsBoardID_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdCfg.m_byBrdID, abySectionBuf, abyKeyBuf);
		
		sprintf(abyKeyBuf, "%s%d", umsBoardType_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_emBrdType, abySectionBuf, abyKeyBuf);
		
		sprintf(abyKeyBuf, "%s%d", umsBoardLayer_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdLayer, abySectionBuf, abyKeyBuf);
		
		sprintf(abyKeyBuf, "%s%d", umsBoardSlot_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdSlot, abySectionBuf, abyKeyBuf);
		
		sprintf(abyKeyBuf, "%s%d", umsBoardIP_, wIndex);
		GetIPVal(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_dwBrdIP, abySectionBuf, abyKeyBuf);
		
		//单板模式信息
		for (u16 wModeIndex = 0; wModeIndex < TP_UMS_BRD_MAXNUM_EQP; wModeIndex++)
		{
			sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardModeType_, wIndex, "[", wModeIndex, "]");
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdMode[wModeIndex].m_emEqpType, abySectionBuf, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardModeAlias_, wIndex, "[", wModeIndex, "]");
			ReadStringVal(ptBrdCfg->m_tBrdMode[wModeIndex].m_szEqpAlias, TP_MAXLEN_EQP_ALIAS, abySectionBuf, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardEqpModeType_, wIndex, "[", wModeIndex, "]");
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdMode[wModeIndex].m_emEqpMdlType, abySectionBuf, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardModeEapId_, wIndex, "[", wModeIndex, "]");
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdMode[wModeIndex].m_wEqpId, abySectionBuf, abyKeyBuf);
			if (em_audmix_mdl == ptBrdCfg->m_tBrdMode[wModeIndex].m_emEqpType)
			{
				sprintf(abyKeyBuf, "%s%d%s%d%s", umsAudmixChanNum_, wIndex, "[", wModeIndex, "]");
				ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdMode[wModeIndex].m_byAudmixNum, abySectionBuf, abyKeyBuf);
			}
		}
	}
}


//读取电视墙配置信息
static void ReadHduInfoFromFile()
{
	s8 abyBuf[48] = {0};
	s8 abySectionBuf[48] = {0};
	s8 abyKeyBuf[48] = {0};
	
	THduCfgInfo* ptHduCfg = NULL;
	for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; wIndex++)
	{
		s8 abyIpBuf[20] = {0};
	
		ptHduCfg = &(g_tALLConfigData.m_atHduCfg[wIndex]);
		sprintf(abySectionBuf, "%s%d", umsHduInfo, wIndex);
			
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_byLayer, abySectionBuf, umsKeyHduLayer);  //层号
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_bySlot, abySectionBuf, umsKeyHduSlot);    //槽位号
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_bQtHdu, abySectionBuf, umsKeyBQtHdu);    // bQtHdu
		GetIPVal(abyIpBuf, sizeof(abyIpBuf), ptHduCfg->m_dwIP, abySectionBuf, umsKeyHduIp);  //ip
		ReadStringVal(ptHduCfg->m_tName.m_abyAlias, (TP_MAX_ALIAS_LEN + 1), abySectionBuf, umsKeyHduAlias);    //名称
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_wStartPort, abySectionBuf, umsKeyHduStartPort);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_byChanNum, abySectionBuf, umsKeyHduChanNum); 
		for (u16 wChanIndex = 0; wChanIndex < ptHduCfg->m_byChanNum; wChanIndex++)
		{
			sprintf(abyKeyBuf, "%s%d", umsKeyHduVmp, (wChanIndex + 1));
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_atChanInfo[wChanIndex].m_bVmp, abySectionBuf, abyKeyBuf);

			sprintf(abyKeyBuf, "%s%d", umsKeyHduOutTypeChan_, (wChanIndex + 1));
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_atChanInfo[wChanIndex].m_emOutPortType, abySectionBuf, abyKeyBuf); //接口类型
				
			sprintf(abyKeyBuf, "%s%d", umsKeyHduOutModeChan_, (wChanIndex + 1));
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_atChanInfo[wChanIndex].m_emOutModeType, abySectionBuf, abyKeyBuf); //输出制式
				
			sprintf(abyKeyBuf, "%s%d", umsKeyHduZoomRateChan_, (wChanIndex + 1));
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_atChanInfo[wChanIndex].m_emZoomRate, abySectionBuf, abyKeyBuf);    //缩放比例
				
			sprintf(abyKeyBuf, "%s%d", umsKeyHduShowModeChan_, (wChanIndex + 1));
			ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptHduCfg->m_atChanInfo[wChanIndex].m_emShowMode, abySectionBuf, abyKeyBuf);    //输出比例
		}
	}
}
//读取电视墙风格信息
static void ReadHduStyleInfoFromFile()
{
	s8 abyBuf[40] = {0};
	ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), g_tALLConfigData.m_tHduStyleCfg.m_byRow, umsHduStyleInfo, umsKeyHduStyleRow);
	ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), g_tALLConfigData.m_tHduStyleCfg.m_byCol, umsHduStyleInfo, umsKeyHduStyleCol);

	s8 abyKeyBuf[48] = {0};
	THduStyleUnitCfg* ptStyle = NULL;
	for (u16 wIndex = 0; wIndex < HDU_STYLE_MAX_NUM; wIndex++)
	{
		ptStyle = &(g_tALLConfigData.m_tHduStyleCfg.m_atHduStyle[wIndex]);
		sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleVmp_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptStyle->m_bVmp, umsHduStyleInfo, abyKeyBuf);

		sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleLayer_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptStyle->m_byLayer, umsHduStyleInfo, abyKeyBuf);

		sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleSlot_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptStyle->m_bySlot, umsHduStyleInfo, abyKeyBuf);

		sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleChanIndex_, wIndex);
		ReadSimpleValFromFile(abyBuf, sizeof(abyBuf), ptStyle->m_byChanIndex, umsHduStyleInfo, abyKeyBuf);

		sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleChanName_, wIndex);
		ReadStringVal(ptStyle->m_tName.m_abyAlias, (TP_MAX_ALIAS_LEN + 1), umsHduStyleInfo, abyKeyBuf);
	}
}

 /*====================================================================
  函 数 名：SaveSipRegCfgToFile
  功    能：保存注册SIP配置信息到文件
  算法实现： 
  全局变量： 
  参    数：TTPSipRegistrarCfg& tSipRegCfg
  返 回 值：  
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
 2011/5/09      1.0		    肖楚然                  创建
======================================================================*/
static void SaveSipRegCfgToFile( const TTPSipRegistrarCfg& tSipRegCfg)
{
	s8 abyBuf[20] = {0};
	WriteSimpleVal( tSipRegCfg.bUsed, umsSipReg, umsKeySipRegUsed );
	WriteIpVal( abyBuf, sizeof(abyBuf), tSipRegCfg.dwRegIP, umsSipReg, umsKeySipRegIP );
}

static void SaveGKRegCfgToFile( const TTPGKCfg& tGKRegCfg)
{
	s8 abyBuf[20] = {0};
	WriteSimpleVal( tGKRegCfg.bUsed, umsGKReg, umsKeyGKRegUsed );
	WriteIpVal( abyBuf, sizeof(abyBuf), tGKRegCfg.dwGKIP, umsGKReg, umsKeyGKRegIP );
}

static void SaveSipCallCfgToFile(TUmsStackCallCfg& tCall)
{
	WriteSimpleVal( tCall.m_wCallingPort, umsSipCall, umsKeySipCallingPort );
	WriteSimpleVal( tCall.m_wMaxCallNum, umsSipCall, umsKeySipMaxCallNum );
	WriteSimpleVal( tCall.m_dwKeepAliveTime, umsSipCall, umsKeySipCallKeepAliveTime );
}

//保存单板配置信息
static void SaveBoardInfoToFile()
{
	s8 abyBuf[20] = {0};
	WriteSimpleVal(g_tALLConfigData.m_byBrdValidNum, umsBoardInfo, umsBoardValidNum);
	
	s8 abySectionBuf[40] = {0};
	s8 abyKeyBuf[40] = {0};
	
	TTPBrdInfo* ptBrdCfg = NULL;
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; ++wIndex)
	{
		s8 abyIpBuf[20] = {0};
		if (em_unknow_brd == g_tALLConfigData.m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			continue;
		}
		else
		{
			ptBrdCfg = &g_tALLConfigData.m_atBrdCfg[wIndex];
			
			sprintf(abySectionBuf, "%s%d", umsBoardInfo_, wIndex);
			
			sprintf(abyKeyBuf, "%s%d", umsBoardID_, wIndex);
			WriteSimpleVal(ptBrdCfg->m_tBrdCfg.m_byBrdID, abySectionBuf, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d", umsBoardType_, wIndex);
			WriteSimpleVal(ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_emBrdType, abySectionBuf, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d", umsBoardLayer_, wIndex);
			WriteSimpleVal(ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdLayer, abySectionBuf, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d", umsBoardSlot_, wIndex);
			WriteSimpleVal(ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdSlot, abySectionBuf, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d", umsBoardIP_, wIndex);
			WriteIpVal(abyBuf, sizeof(abyBuf), ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_dwBrdIP, abySectionBuf, abyKeyBuf);
			
			//单板模式信息
			for (u16 wModeIndex = 0; wModeIndex < TP_UMS_BRD_MAXNUM_EQP; wModeIndex++)
			{
				if (em_unknow_mdl == g_tALLConfigData.m_atBrdCfg[wIndex].m_tBrdMode[wModeIndex].m_emEqpType)
				{
					continue;
				}
				sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardModeType_, wIndex, "[", wModeIndex, "]");
				WriteSimpleVal(ptBrdCfg->m_tBrdMode[wModeIndex].m_emEqpType, abySectionBuf, abyKeyBuf);
				
				sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardModeAlias_, wIndex,"[", wModeIndex, "]");
				WriteStringVal(ptBrdCfg->m_tBrdMode[wModeIndex].m_szEqpAlias, abySectionBuf, abyKeyBuf);

				sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardEqpModeType_, wIndex, "[", wModeIndex, "]");
				WriteSimpleVal(ptBrdCfg->m_tBrdMode[wModeIndex].m_emEqpMdlType, abySectionBuf, abyKeyBuf);

				sprintf(abyKeyBuf, "%s%d%s%d%s", umsBoardModeEapId_, wIndex, "[", wModeIndex, "]");
				WriteSimpleVal(ptBrdCfg->m_tBrdMode[wModeIndex].m_wEqpId, abySectionBuf, abyKeyBuf);

				if (em_audmix_mdl == ptBrdCfg->m_tBrdMode[wModeIndex].m_emEqpType)
				{
					sprintf(abyKeyBuf, "%s%d%s%d%s", umsAudmixChanNum_, wIndex, "[", wModeIndex, "]");
					WriteSimpleVal(ptBrdCfg->m_tBrdMode[wModeIndex].m_byAudmixNum, abySectionBuf, abyKeyBuf);
				}
			}
			
		}	
	}
}

//保存电视墙配置信息
static void SaveHduInfoToFile()
{
	s8 abySectionBuf[48] = {0};
	s8 abyKeyBuf[48] = {0};

	THduCfgInfo* ptHduCfg = NULL;
	for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; wIndex++)
	{
		s8 abyIpBuf[20] = {0};
		if (0 == g_tALLConfigData.m_atHduCfg[wIndex].m_dwIP)
		{
			continue;
		}
		else
		{
			ptHduCfg = &(g_tALLConfigData.m_atHduCfg[wIndex]);
			sprintf(abySectionBuf, "%s%d", umsHduInfo, wIndex);
			
			WriteSimpleVal(ptHduCfg->m_byLayer, abySectionBuf, umsKeyHduLayer);  //层号
			WriteSimpleVal(ptHduCfg->m_bySlot, abySectionBuf, umsKeyHduSlot);    //槽位号
			WriteSimpleVal(ptHduCfg->m_bQtHdu, abySectionBuf, umsKeyBQtHdu);    // bQtHdu
			WriteIpVal(abyIpBuf, sizeof(abyIpBuf), ptHduCfg->m_dwIP, abySectionBuf, umsKeyHduIp);  //ip
			WriteStringVal(ptHduCfg->m_tName.m_abyAlias, abySectionBuf, umsKeyHduAlias);    //名称
			WriteSimpleVal(ptHduCfg->m_wStartPort, abySectionBuf, umsKeyHduStartPort);
			WriteSimpleVal(ptHduCfg->m_byChanNum, abySectionBuf, umsKeyHduChanNum); 
			for (u16 wChanIndex = 0; wChanIndex < ptHduCfg->m_byChanNum; wChanIndex++)
			{
				sprintf(abyKeyBuf, "%s%d", umsKeyHduVmp, (wChanIndex + 1));
				WriteSimpleVal(ptHduCfg->m_atChanInfo[wChanIndex].m_bVmp, abySectionBuf, abyKeyBuf);    //输出比例

				sprintf(abyKeyBuf, "%s%d", umsKeyHduOutTypeChan_, (wChanIndex + 1));
				WriteSimpleVal(ptHduCfg->m_atChanInfo[wChanIndex].m_emOutPortType, abySectionBuf, abyKeyBuf); //接口类型

				sprintf(abyKeyBuf, "%s%d", umsKeyHduOutModeChan_, (wChanIndex + 1));
				WriteSimpleVal(ptHduCfg->m_atChanInfo[wChanIndex].m_emOutModeType, abySectionBuf, abyKeyBuf); //输出制式

				sprintf(abyKeyBuf, "%s%d", umsKeyHduZoomRateChan_, (wChanIndex + 1));
				WriteSimpleVal(ptHduCfg->m_atChanInfo[wChanIndex].m_emZoomRate, abySectionBuf, abyKeyBuf);    //缩放比例

				sprintf(abyKeyBuf, "%s%d", umsKeyHduShowModeChan_, (wChanIndex + 1));
				WriteSimpleVal(ptHduCfg->m_atChanInfo[wChanIndex].m_emShowMode, abySectionBuf, abyKeyBuf);    //输出比例
			}
		}
	}
}

//保存电视墙风格配置
static void SaveHduStyleCfg()
{
	WriteSimpleVal(g_tALLConfigData.m_tHduStyleCfg.m_byRow, umsHduStyleInfo, umsKeyHduStyleRow);
	WriteSimpleVal(g_tALLConfigData.m_tHduStyleCfg.m_byCol, umsHduStyleInfo, umsKeyHduStyleCol);

	s8 abySectionBuf[48] = {0};
	s8 abyKeyBuf[48] = {0};
	u16 wStyleIndex = g_tALLConfigData.m_tHduStyleCfg.m_byRow * g_tALLConfigData.m_tHduStyleCfg.m_byCol;
	THduStyleUnitCfg* ptStyle = NULL;
	for(u16 wIndex = 0; wIndex < wStyleIndex; wIndex++)
	{
		ptStyle = &(g_tALLConfigData.m_tHduStyleCfg.m_atHduStyle[wIndex]);
		if ((HDU_MAX_LAYER == ptStyle->m_byLayer) && (HDU_MAX_SLOT == ptStyle->m_bySlot))
		{
			continue;
		}
		else
		{
			sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleVmp_, wIndex);
			WriteSimpleVal(ptStyle->m_bVmp, umsHduStyleInfo, abyKeyBuf);
			
			sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleLayer_, wIndex);
			WriteSimpleVal(ptStyle->m_byLayer, umsHduStyleInfo, abyKeyBuf);

			sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleSlot_, wIndex);
			WriteSimpleVal(ptStyle->m_bySlot, umsHduStyleInfo, abyKeyBuf);

			sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleChanIndex_, wIndex);
			WriteSimpleVal(ptStyle->m_byChanIndex, umsHduStyleInfo, abyKeyBuf);

			sprintf(abyKeyBuf, "%s%d", umsKeyHduStyleChanName_, wIndex);
			WriteStringVal(ptStyle->m_tName.m_abyAlias, umsHduStyleInfo, abyKeyBuf);
		}
	}
}

/*====================================================================
函 数 名： SetConfigVersionNumber
功    能： 
算法实现： 
全局变量： 
参    数： u32 dwVersionNumber
返 回 值：static void 
--------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人    修改内容
2005/8/31      1.0		    张 飞                   创建
======================================================================*/
static void SetConfigVersionNumber(u32 dwVersionNumber)
{
	WriteSimpleVal(dwVersionNumber,umsSecSystem,umsKeySysConfigFileVersion);
}

static void SaveQTEncryptInfo( const TTPQTEncryptInfo &tTPQTEncryptInfo )
{
	s8 abyBuf[20] = {0};
	WriteSimpleVal( tTPQTEncryptInfo.m_bIsEncQT, umsSecQuanTumEncInfo, umsKeyQtOn );
	WriteIpVal( abyBuf, sizeof(abyBuf), tTPQTEncryptInfo.m_dwQuanTumIP, umsSecQuanTumEncInfo, umsKeyQTIP );
	WriteSimpleVal( tTPQTEncryptInfo.m_dwQuanTumID, umsSecQuanTumEncInfo, umsKeyQTID );
}

static void SavePwdCycleInfo( const TPwdCycleInfo &tTPPwdCycleInfo )
{
	s8 abyBuf[20] = {0};
	WriteSimpleVal( tTPPwdCycleInfo.m_bStartUpdate, umsPwdCycleInfo, umsPwdCycleUsed );
	WriteSimpleVal( tTPPwdCycleInfo.m_emPwdCycle, umsPwdCycleInfo, umsPwdCycleTimer );
}

static void ReadQTEncryptInfo( TTPQTEncryptInfo &tTPQTEncryptInfo )
{
	s8 abyBuf[20] = {0};
	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tTPQTEncryptInfo.m_bIsEncQT, umsSecQuanTumEncInfo, umsKeyQtOn );
	GetIPVal( abyBuf, sizeof(abyBuf), tTPQTEncryptInfo.m_dwQuanTumIP, umsSecQuanTumEncInfo, umsKeyQTIP );
	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tTPQTEncryptInfo.m_dwQuanTumID, umsSecQuanTumEncInfo, umsKeyQTID );
}

static void ReadPwdCycleInfo(TPwdCycleInfo &tTPPwdCycleInfo)
{
	s8 abyBuf[20] = {0};
	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tTPPwdCycleInfo.m_bStartUpdate, umsPwdCycleInfo, umsPwdCycleUsed );
	ReadSimpleValFromFile( abyBuf, sizeof(abyBuf), tTPPwdCycleInfo.m_emPwdCycle, umsPwdCycleInfo, umsPwdCycleTimer );

}

static void ReadNtpdInfo(TNtpdInfo &tNtpdInfo)
{
	s8 abyBuf[20] = {0};
	GetIPVal( abyBuf, sizeof(abyBuf), tNtpdInfo.m_dwNtpdIp, umsNtpdInfo, umsNtpdIp );
}

static void SaveNtpdInfo(const TNtpdInfo &tNtpdInfo)
{
	s8 abyBuf[20] = {0};
	WriteIpVal( abyBuf, sizeof(abyBuf), tNtpdInfo.m_dwNtpdIp, umsNtpdInfo, umsNtpdIp );
}

/*====================================================================
  函 数 名： LoadDataFromCfgFile
  功    能： 
  算法实现： 
  全局变量： 
  参    数： const s8* const szFileName
  返 回 值： BOOL  
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/8/31      1.0		    张 飞                   创建
======================================================================*/
BOOL  LoadDataFromCfgFile(const s8* const szFileName)
{
	if(NULL == szFileName)
	{
        msgprint("[umsConfig FileName Error]LoadDataFromCfgFile %s error ",
			szFileName);
		return FALSE;
	}

	FILE* pfFileName = fopen(szFileName,"r");
	if(NULL == pfFileName)
	{
		msgprint("[umsConfig Open File Error]LoadDataFromCfgFile %s error ",
			szFileName);
		return FALSE;
	}
    BOOL bResult = LoadDataFromCfgFile(pfFileName);
	fclose(pfFileName);
	return bResult;
}

/*====================================================================
  函 数 名： LoadDataFromCfgFile
  功    能： 
  算法实现： 
  全局变量： 
  参    数： FILE* pfFileName
  返 回 值： BOOL  
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/8/31      1.0		    张 飞                   创建
======================================================================*/
BOOL  LoadDataFromCfgFile(FILE* pfFileName)
{
	if(NULL == pfFileName)
	{
		return FALSE;
	}
	s_pfCfgFile = pfFileName;
   
	ReadLocalUmsInfoFromFile(g_tALLConfigData.m_tLocalCnsInfo);
	ReadSipRegCfgFromFile(g_tALLConfigData.m_tTPSipRegistrarCfg);
	ReadGKRegCfgFromFile(g_tALLConfigData.m_tGKRegCfg);
	ReadSipCallCfgFromFile(g_tALLConfigData.m_tSipStackCallCfg);

	ReadBoardInfoFromFile();
	ReadHduInfoFromFile();
	ReadHduStyleInfoFromFile();

	//读取QT配置信息
	ReadQTEncryptInfo( g_tALLConfigData.m_tTPQTEncryptInfo );
	
	ReadPwdCycleInfo (g_tALLConfigData.m_tPwdCycleInfo);

	ReadNtpdInfo(g_tALLConfigData.m_tNtpdInfo);
	s_pfCfgFile = NULL;
	return TRUE;
}


BOOL  SaveDataToCfgFile(const s8 szFileName[wFileNameLen],const TALLConfigData& tAllConfigData)
{
	if(NULL == szFileName)
	{
		msgprint("[umsConfig FileName Error]%s SaveDataToCfgFile %s error ",
			__FILE__,szFileName);
		return FALSE;
	}
	CFileAttrib file(szFileName);
	FILE* pfFileName = fopen(szFileName,"w");
	if(NULL == pfFileName)
	{
		msgprint("[umsConfig Open File Error]%s SaveDataToCfgFile %s error ",
			__FILE__,szFileName);
		return FALSE;
	}
	BOOL bResult = SaveDataToCfgFile(pfFileName,tAllConfigData);
	fclose(pfFileName);
	return bResult;
}
/*====================================================================
  函 数 名： SaveDataToCfgFile
  功    能： 
  算法实现： 
  全局变量： 
  参    数： FILE* pfFileName
  返 回 值： BOOL  
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/8/31      1.0		    张 飞                   创建
======================================================================*/
BOOL  SaveDataToCfgFile(FILE* pfFileName,const TALLConfigData& tAllConfigData)
{
	if(NULL == pfFileName)
	{
		return FALSE;
	}
	
	s_pfCfgFile = pfFileName;
    SetConfigVersionNumber(mtConfigFileVersion);

	SaveLocalUmsInfoToFile(tAllConfigData.m_tLocalCnsInfo);
	SaveSipRegCfgToFile(tAllConfigData.m_tTPSipRegistrarCfg);
	SaveGKRegCfgToFile(tAllConfigData.m_tGKRegCfg);
	SaveSipCallCfgToFile(g_tALLConfigData.m_tSipStackCallCfg);

	SaveBoardInfoToFile();
	SaveHduInfoToFile();
	SaveHduStyleCfg();

	SaveQTEncryptInfo(g_tALLConfigData.m_tTPQTEncryptInfo);
	SavePwdCycleInfo(g_tALLConfigData.m_tPwdCycleInfo);
	SaveNtpdInfo(g_tALLConfigData.m_tNtpdInfo);
	
	s_pfCfgFile = NULL;
	return TRUE;
}

#undef WriteStringVal
#undef WriteSimpleVal
#undef GetIPStr
#undef WriteIpVal