#include "tpinfo.h"
#include "tpconfig.h"
#include "umsconfig.h"
#include "kdvsys.h"
#include "tprwnewcfgfile.h"
#include "systpcom.h"
#include "tpconfig.h"

s8 CTemplateInfo::s_validTpNum[]	= "validTpNum";
s8 CTemplateInfo::s_validTpNumKey[]	= "validTpNumKey";
s8 CTemplateInfo::s_validSeq_[]		= "validSeq_";

s8 CTemplateInfo::s_tpMeetingName[] = "tpMeetingName";
s8 CTemplateInfo::s_tpE164[] = "tpE164";

s8 CTemplateInfo::s_tpStartTime[] = "tpStartTime";

s8 CTemplateInfo::s_tpEpAddrNum[] = "tpEpAddrNum";
s8 CTemplateInfo::s_tpEpAddrID_[] = "tpEpAddrID_";
s8 CTemplateInfo::s_tpIsAliasIP[] = "tpIsAliasIP_";


s8 CTemplateInfo::s_tpEpAddrAlias_[] = "tpEpAddrAlias_";
s8 CTemplateInfo::s_tpEpAddrAliasType_[] = "tpEpAddrAliasType_";
s8 CTemplateInfo::s_tpEpAddrE164_[] = "tpEpAddrE164_";
s8 CTemplateInfo::s_tpEpAddrE164Type_[] = "tpEpAddrE164Type_";
s8 CTemplateInfo::s_tpEpAddrCallType_[] = "tpEpAddrCallType_";
s8 CTemplateInfo::s_tpEpAddrIP_[] = "tpEpAddrIP_";
s8 CTemplateInfo::s_tpEpAddrIPType_[] = "tpEpAddrIPType_";

s8 CTemplateInfo::s_tpTurnInterval[] = "tpTurnInterval";
s8 CTemplateInfo::s_tpTurnOn[] = "tpTurnOn";
s8 CTemplateInfo::s_tpTurnNum[] = "tpTurnNum";
s8 CTemplateInfo::s_tpTurnID_[] = "tpTurnID_";

s8 CTemplateInfo::s_tpDiscussOn[] = "tpDiscussOn";
s8 CTemplateInfo::s_tpDiscussVacOn[] = "tpDiscussVacOn";
s8 CTemplateInfo::s_tpAuxMixID_[] = "tpAudMixID_";

s8 CTemplateInfo::s_tpMainVidNum[] = "tpMainVidNum";
s8 CTemplateInfo::s_tpMinorVidNum[] = "tpMinorVidNum";
s8 CTemplateInfo::s_tpMainVideoRes_[] = "tpMainVideoRes_";
s8 CTemplateInfo::s_tpMinorVideoRes_[] = "tpMinorVideoRes_";
s8 CTemplateInfo::s_tpMainVideoLvl_[] = "tpMainVideoLvl_";
s8 CTemplateInfo::s_tpMinorVideoLvl_[] = "tpMinorVideoLvl_";
s8 CTemplateInfo::s_tpMainVideoFrame_[] = "tpMainVideoFrame_";
s8 CTemplateInfo::s_tpMinorVideoFrame_[] = "tpMinorVideoFrame_";
s8 CTemplateInfo::s_tpAudioNum[] = "tpAudioNum";
s8 CTemplateInfo::s_tpAudioFormat_[] = "tpAudioFormat_";
s8 CTemplateInfo::s_tpAudioFreq_[] = "tpAudioFreq_";
s8 CTemplateInfo::s_tpAudioReservel_[] = "tpAudioReservel_";
s8 CTemplateInfo::s_tpEncryptKey[] = "tpEncryptKey";
s8 CTemplateInfo::s_tpEncryptType[] = "tpEncryptType";
s8 CTemplateInfo::s_tpEncryptFreq[] = "tpEncryptFreq";
s8 CTemplateInfo::s_tpDefaultEncrypt[] = "tpDefaultEncrypt";
s8 CTemplateInfo::s_tpHpConfBitRate[] = "tpConfBitRate";
s8 CTemplateInfo::s_tpConfDualBitRate[] = "tpConfDualBitRate";
s8 CTemplateInfo::s_tpConfUpBandWid[] = "tpConfUpBandWid";
s8 CTemplateInfo::s_tpConfDownBandWid[] = "tpConfDownBandWid";
s8 CTemplateInfo::s_tpVmpPlanStyle[] = "tpVmpPlanStyle";
s8 CTemplateInfo::s_tpVmpPlanEpNum[] = "tpVmpPlanEpNum";
s8 CTemplateInfo::s_tpVmpPlanEpAlias_[] = "tpVmpPlanEpAlias_";
s8 CTemplateInfo::s_tpVmpPlanScrIndex_[] = "tpVmpPlanScrIndex_";
s8 CTemplateInfo::s_tpVmpPlanSpeakIndex[] = "tpVmpPlanSpeakIndex";
s8 CTemplateInfo::s_tpVmpPlanDualIndex[] = "tpVmpPlanDualIndex";

s8 CTemplateInfo::s_tpEpCallProtocol_[] = "tpEpCallProtocol_";
CTemplateInfo::CTemplateInfo()
{
	m_tControlData.m_wValidNum = 0;

	for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		m_tControlData.m_abValidSeq[wIndex] = FALSE;
	}
	memset(m_szControlFile, 0, sizeof(m_szControlFile));
	memset(m_szTpFileName, 0, sizeof(m_szTpFileName));
	memset(m_szTpFolder, 0, sizeof(m_szTpFolder));
	m_semConfLock = NULL;
}

CTemplateInfo::~CTemplateInfo()
{

}

CTemplateInfo& CTemplateInfo::Instance()
{
	static CTemplateInfo tInfo;
	return tInfo;
}

BOOL32 CTemplateInfo::Init()
{
	//创建读写信号量
	if( !OspSemBCreate(&m_semConfLock) )
	{
        MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::Init] create SEMHANDLE failed!\n" ));
		return FALSE;
	}

	strncpy(m_szControlFile, UmsGetFileName(emUmsTpControlFile), sizeof(m_szControlFile) - 1);
	strncpy(m_szTpFileName, UmsGetFileName(emUmsTpFile), sizeof(m_szTpFileName)-1);
	strncpy(m_szTpFolder, UmsGetFileName(emUmsTpFolder), sizeof(m_szTpFolder)-1);

	TemplateMakeDir(m_szTpFileName);

	if (!LoadControlFile())
	{
		return FALSE;
	}

	if (!LoadTpFile())
	{
		return FALSE;
	}
	return TRUE;
}

BOOL32 CTemplateInfo::UpLoadTempFromFile(s8* szFileName)
{
	s8 achCommandBuf[256] = {0};
	memcpy(achCommandBuf, "tar xvf ", sizeof("tar xvf "));
	strcat(achCommandBuf, UmsGetFileName(emUmsTpDownLoadFile));
	strcat(achCommandBuf, " -C "); //将文件解压
	strcat(achCommandBuf, UmsGetFileName(emUmsTpFolder));
	msgprint("[UpLoadTempFromFile] achCommandBuf->%s .\n", achCommandBuf);
	s16  wStatus = 0;
#if defined(_LINUX_)
	msgprint("[UpLoadTempFromFile] execute command ->%s .\n", achCommandBuf);
	wStatus = system(achCommandBuf);
	if (-1 == wStatus || 127 == wStatus)
	{
		msgprint("[UpLoadTempFromFile] system error!\n");
		return FALSE;
	}
#endif

	TConfTemplateLocal tTemp;
	s8 achTempFileName[TP_FILENAME_LENGTH +1 ] = {0};
	BOOL32 bAddFlag = FALSE;
	tTemp.Clear();
	tTemp.m_wID = 0;

	if( !OspSemTakeByTime(m_semConfLock, WAIT_SEM_TIMEOUT ))
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::UpLoadTempFromFile]OspSemTakeByTime excute failed s_semGetSetTP value is %d\n", m_semConfLock));
		return FALSE ;
	} 
	for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		bAddFlag = FALSE;
		sprintf(achTempFileName,"%s%s%d.ini",UmsGetFileName(emUmsTpFolder),UmsGetFileName(emUmsTpDownTemplateFile)+1,wIndex+1);
		FILE* pfFile = fopen(achTempFileName,"r");
		if (NULL == pfFile)
		{
			continue;
		}

		s8 achSectionBuf[64] = "";	
		sprintf(achSectionBuf, "%s%d", "template_", wIndex+1);

		if (!LoadTemplate(pfFile,tTemp,achSectionBuf))
		{
			MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::UpLoadTempFromFile]LoadTemplate %s failed \n",achTempFileName));
			continue;
		}

		tTemp.m_wID = wIndex + 1;
		
		//判断是否存在重名的模板
		u16 wValidCount = 0;
		for (u16 wValidConf = 0; wValidConf < TP_CONFTEMPLATE_MAXNUM; ++wValidConf)
		{
			if (wValidCount == m_tControlData.m_wValidNum)
			{
				break;
			}
			
			if (!m_tControlData.m_abValidSeq[wValidConf])
			{
				continue;
			}
			
			++wValidCount;
			
			if (('\0' != tTemp.m_achConfName[0] && 0 == strcmp(tTemp.m_achConfName, m_atConfTemplate[wValidConf].m_achConfName)) ||
				('\0' != tTemp.m_achConfE164[0] && 0 == strcmp(tTemp.m_achConfE164, m_atConfTemplate[wValidConf].m_achConfE164)))
			{//重名
				if (m_atConfTemplate[wValidConf].m_wID == tTemp.m_wID)
				{//覆盖
					memcpy(&(m_atConfTemplate[wValidConf]), &tTemp, sizeof(TConfTemplateLocal));
				}
				else
				{
					m_tControlData.m_abValidSeq[m_atConfTemplate[wValidConf].m_wID-1] = FALSE;
					m_atConfTemplate[wValidConf].Clear();
					if (!m_tControlData.m_abValidSeq[tTemp.m_wID - 1])
					{
						memcpy(&(m_atConfTemplate[tTemp.m_wID - 1]), &tTemp, sizeof(TConfTemplateLocal));
						m_tControlData.m_abValidSeq[tTemp.m_wID - 1] = TRUE;
					}
					else
					{
						//重新找个位置
						for (u16 wPos = 0; wPos < TP_CONFTEMPLATE_MAXNUM; ++wPos)
						{
							if (!m_tControlData.m_abValidSeq[wPos])
							{
								tTemp.m_wID = wPos + 1;
								memcpy(&(m_atConfTemplate[wPos]), &tTemp, sizeof(TConfTemplateLocal));
								m_tControlData.m_abValidSeq[wPos] = TRUE;
								break;
							}
						}
					}
				}
				
				bAddFlag = TRUE;
				break;
			}
		}
		
		if (!bAddFlag)
		{
			//对应的模板ID是否已经存在,存在找一个空闲的ID
			if (m_tControlData.m_abValidSeq[tTemp.m_wID - 1])
			{//存在，重新分配
				BOOL32 bRes = FALSE;
				for (u16 wPos = 0; wPos < TP_CONFTEMPLATE_MAXNUM; ++wPos)
				{
					if (!m_tControlData.m_abValidSeq[wPos])
					{
						tTemp.m_wID = wPos + 1;
						memcpy(&(m_atConfTemplate[wPos]), &tTemp, sizeof(TConfTemplateLocal));
						m_tControlData.m_abValidSeq[wPos] = TRUE;
						++m_tControlData.m_wValidNum;
						bRes = TRUE;
						break;
					}
				}
			}
			else
			{
				memcpy(&(m_atConfTemplate[tTemp.m_wID - 1]), &tTemp, sizeof(TConfTemplateLocal));
				m_tControlData.m_abValidSeq[tTemp.m_wID - 1] = TRUE;
				++m_tControlData.m_wValidNum;
			}
		}
		
		tTemp.Clear();
		tTemp.m_wID = 0;


		if(NULL != pfFile)
		{
			fclose(pfFile);
		}
	}

	memset(achCommandBuf,0,sizeof(achCommandBuf));
	memcpy(achCommandBuf,"rm -rf ",sizeof("rm -rf "));
	#ifdef _LINUX_ 
	#if defined(_PPC_82XX_) || defined(_PPC_85XX_)	
	strcat(achCommandBuf,"/ramdisk/ramdisk");
	#else 
	strcat(achCommandBuf,"/usr/usr");
	#endif
	#endif
	msgprint("[UpLoadTempFromFile] achCommandBuf->%s .\n", achCommandBuf);

#if defined(_LINUX_)
	msgprint("[UpLoadTempFromFile] execute command ->%s .\n", achCommandBuf);
	wStatus = system(achCommandBuf);
	if (-1 == wStatus || 127 == wStatus)
	{
		msgprint("[UpLoadTempFromFile] system error!\n");
		return FALSE;
	}
#endif	

	OspSemGive(m_semConfLock);
	return TRUE;
}


BOOL32 CTemplateInfo::LoadTpFile()
{
	
	s8 szFullFileName[TP_FILE_NAME_LEN+1] = {0};
	FILE *pFile = NULL;
	s8 achSectionBuf[64] = "";

	for( u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex )
	{
		memset(szFullFileName, 0, TP_FILE_NAME_LEN+1);
		sprintf(szFullFileName,"%s%d.ini", m_szTpFileName, wIndex+1);
		pFile = fopen(szFullFileName, "rb");
		
		if(NULL == pFile)
		{
			pFile = fopen(szFullFileName,"w");
			if(NULL != pFile)	
			{
				fclose(pFile);
			}

			continue;
		}
		
		if (!m_tControlData.m_abValidSeq[wIndex])
		{
			fclose(pFile);
			continue;
		}

		sprintf(achSectionBuf, "%s%d", "template_", wIndex+1);
		
		LoadTemplate(pFile, m_atConfTemplate[wIndex], achSectionBuf);
		m_atConfTemplate[wIndex].m_wID = wIndex + 1;

		m_atConfTemplate[wIndex].m_tTempCfgEx.m_wTempID = wIndex + 1;
		fclose(pFile);
		
	}
	return TRUE;
}

BOOL32 CTemplateInfo::LoadControlFile()
{
	FILE *pFile = fopen(m_szControlFile,"rb");

	//文件不存在创建文件
	if(NULL == pFile)
	{
		pFile = fopen(m_szControlFile,"w");
		if (NULL != pFile)
		{
			fclose(pFile);
			m_tControlData.m_wValidNum = 0;
			return TRUE;
		}
		else
		{
			MdlError(Ums_Mdl_Cfg, ("[CTemplateInfo::LoadControlFile] Create control file failed..\n"));
			return FALSE;
		}
	}

	fseek(pFile, 0L, SEEK_END);
	u32 dwFileLen = ftell(pFile);
	if (0 == dwFileLen)
	{
		msgprint("[CTemplateInfo::LoadControlFile] control file is empty.\n");
		fclose(pFile);
		m_tControlData.m_wValidNum = 0;
		return TRUE;
	}
	fseek(pFile, 0L, SEEK_SET);

	s8 szBuf[40] = {0};
	BOOL32 bResult = GetRegKeyString2(pFile, s_validTpNum, s_validTpNumKey, "", szBuf, sizeof(szBuf));
	if(!bResult || 0 == strlen(szBuf)) 
	{
		fclose(pFile);
		MdlError(Ums_Mdl_Cfg, ("[CTemplateInfo::LoadControlFile] Get Key:%s failed.\n", validTpNumKey));
		return FALSE;
	}
	else
	{
		m_tControlData.m_wValidNum = (u16)atol(szBuf);
	}

	s8 szSectionName[256]={0};
	u16 wSeqNum;
	
	for(u16 wIndex = 0; wIndex < m_tControlData.m_wValidNum; ++wIndex)
	{
		memset(szBuf, 0, sizeof(szBuf));
		memset(szSectionName, 0, sizeof(szSectionName));
		sprintf(szSectionName, "%s%d", s_validSeq_ , wIndex+1);
		bResult = GetRegKeyString2(pFile, s_validTpNum, szSectionName, "", szBuf, sizeof(szBuf));
		
		if(!bResult || 0 == strlen(szBuf) ) 
		{
			fclose(pFile);
			MdlError(Ums_Mdl_Cfg, ("[CTemplateInfo::LoadControlFile]Get Key:%s failed.\n", szSectionName));
			return FALSE;
		}
		else
		{
			wSeqNum = (u16)atol(szBuf);
			m_tControlData.m_abValidSeq[wSeqNum - 1] = TRUE;
		}
	}
	
	fclose(pFile);
	return TRUE;
}

BOOL32 CTemplateInfo::LoadTemplate(FILE *pFile, TConfTemplateLocal& tConfTemp, s8* szSectionBuf)
{
	if (NULL == pFile || NULL == szSectionBuf)
	{
		return FALSE;
	}

	u32 dwTemp = 0;
	ReadStringValue(pFile, szSectionBuf, s_tpMeetingName, tConfTemp.m_achConfName, TP_MAX_ALIAS_LEN);
	ReadStringValue(pFile, szSectionBuf, s_tpE164, tConfTemp.m_achConfE164, TP_MAX_ALIAS_LEN);

	if ( '\0' == tConfTemp.m_achConfName[0] && '\0' == tConfTemp.m_achConfE164[0] )
	{
		return FALSE;
	}

	ReadIntegerValue(pFile, szSectionBuf, s_tpStartTime, dwTemp);
	tConfTemp.m_tStartTime = (time_t)dwTemp;

	dwTemp = 0;
	ReadIntegerValue(pFile, szSectionBuf, s_tpEpAddrNum, dwTemp);
	tConfTemp.m_atEpList.m_wNum = (u16)dwTemp;
	ReadEpList(pFile, szSectionBuf, tConfTemp.m_atEpList);

	dwTemp = 20;//轮询时间默认值
	ReadIntegerValue(pFile, szSectionBuf, s_tpTurnInterval, dwTemp);
	tConfTemp.m_tTurnList.m_wInterval = (u16)dwTemp;

	dwTemp = TRUE;
	ReadIntegerValue(pFile, szSectionBuf, s_tpTurnOn, dwTemp);
	tConfTemp.m_tTurnList.m_bPollOn = (BOOL32)dwTemp;

	dwTemp = 0;
	ReadIntegerValue(pFile, szSectionBuf, s_tpTurnNum, dwTemp);
	tConfTemp.m_tTurnList.m_wNum = (u16)dwTemp;
	ReadTurnList(pFile, szSectionBuf, tConfTemp.m_tTurnList);

	dwTemp = FALSE;
	ReadIntegerValue(pFile, szSectionBuf, s_tpDiscussOn, dwTemp);
	tConfTemp.m_atAuxMixList.m_bAudMixOn = (BOOL32)dwTemp;

	dwTemp = FALSE;
	ReadIntegerValue(pFile,szSectionBuf,s_tpDiscussVacOn,dwTemp);
	tConfTemp.m_atAuxMixList.m_bVacOn = (BOOL32)dwTemp;


	ReadAudMixList(pFile, szSectionBuf, tConfTemp.m_atAuxMixList);

	//读取音频格式 by ywd
	dwTemp = 1;
	ReadIntegerValue(pFile, szSectionBuf, s_tpAudioNum, dwTemp);
	tConfTemp.m_wAudFmtNum = (u16)dwTemp;
	ReadAudioRes(pFile,szSectionBuf,tConfTemp.m_atAudFmt,tConfTemp.m_wAudFmtNum);
	//读取加密信息
	ReadEncryptInfo(pFile,szSectionBuf,tConfTemp.m_tEncrypt);
	dwTemp = 0;
	ReadIntegerValue(pFile,szSectionBuf,s_tpDefaultEncrypt,dwTemp);
	tConfTemp.m_bDefaultEncrypt = (BOOL32)dwTemp;

	dwTemp = 1;
	ReadIntegerValue(pFile, szSectionBuf, s_tpMainVidNum, dwTemp);
	tConfTemp.m_wMainNum = (u16)dwTemp;
	//读取主辅视频分辨率
	ReadMainVideoRes(pFile, szSectionBuf, tConfTemp.m_atTpMainVideoRes, tConfTemp.m_wMainNum);

	dwTemp = 1;
	ReadIntegerValue(pFile, szSectionBuf, s_tpMinorVidNum, dwTemp);
	tConfTemp.m_wMinorNum = (u16)dwTemp;
	ReadMinorVideoRes(pFile, szSectionBuf, tConfTemp.m_atTpMinorVideoRes, tConfTemp.m_wMinorNum);

	dwTemp = 2048;
	ReadIntegerValue(pFile, szSectionBuf, s_tpHpConfBitRate, dwTemp);	
	tConfTemp.m_wConfBitRate = (u16)dwTemp;
	tConfTemp.m_wBpConfBitRate = tConfTemp.m_wConfBitRate;


	dwTemp = 2048;
	ReadIntegerValue(pFile, szSectionBuf, s_tpConfDualBitRate, dwTemp);
	tConfTemp.m_wHpDualBitRate = (u16)dwTemp;
	tConfTemp.m_wBpDualBitRate = tConfTemp.m_wHpDualBitRate;

	dwTemp = 0;
	ReadIntegerValue(pFile, szSectionBuf, s_tpConfUpBandWid, dwTemp);
	tConfTemp.m_wUpBandWid = (u32)dwTemp;

	dwTemp = 0;
	ReadIntegerValue(pFile, szSectionBuf, s_tpConfDownBandWid, dwTemp);
	tConfTemp.m_wDownBandWid = (u32)dwTemp;
	
	ReadVmpMemberCfg(pFile, szSectionBuf,tConfTemp.m_tVmpCfg);
    
	tConfTemp.m_tTempCfgEx.m_wNum = tConfTemp.m_atEpList.m_wNum;
	ReadEpCallProcotol(pFile,szSectionBuf,tConfTemp.m_tTempCfgEx,tConfTemp.m_atEpList);

	return TRUE;
}


BOOL32 CTemplateInfo::ReadIntegerValue(FILE* pFile, const s8 *const  pchSection, const s8 *const  pchKey, u32& dwVal)
{
	s8 achBuf[32] = "";
	BOOL32 bRes = GetRegKeyString2(pFile, pchSection, pchKey, "", achBuf, sizeof(achBuf));
	if (!bRes || 0 == strlen(achBuf))
	{
		return FALSE;
	}
	
	dwVal = atol(achBuf);

	return TRUE;
}

BOOL32 CTemplateInfo::ReadStringValue(FILE* pFile, const s8 *const pchSection, const s8 *const pchKey, 
									  s8* pchBuf, u16 wLen)
{
	s8 achTemp[256] = {0};
	BOOL bResult = GetRegKeyString2(pFile, pchSection, pchKey, "", achTemp, sizeof(achTemp));
	if(!bResult || 0 == strlen(achTemp))
	{
		return FALSE;
	}
	
	strncpy(pchBuf,achTemp,wLen);
	return TRUE;
}

BOOL32 CTemplateInfo::ReadEpList(FILE* pFile, const s8* const pchSection, TEpAddrList& tEpList)
{
	s8 achBufID[64] = "";
	s8 achbufIsAliasIP[64] = "";
	s8 achBufType[64] = "";
	s8 achBufAlias[64] = "";
	s8 achBufE164Type[64] = "";
	s8 achBufCallType[64] ="";
	s8 achBufE164[64] = "";
	s8 achBufIPType[64] = "";
	s8 achBufIP[64] = "";
	
	if( 0 == tEpList.m_wNum )
	{
		return TRUE;
	}
	
	for (u16 wListIndex = 0; wListIndex < tEpList.m_wNum; ++wListIndex )
	{
		memset( achBufID, 0, sizeof( achBufID ) );
		memset( achbufIsAliasIP, 0 , sizeof(achbufIsAliasIP ));
		memset( achBufType, 0, sizeof( achBufType ) );
		memset( achBufAlias, 0, sizeof( achBufAlias ) );
		memset( achBufE164Type, 0, sizeof( achBufE164Type ) );
		memset( achBufCallType,0,sizeof(achBufCallType ));
		memset( achBufE164, 0, sizeof( achBufE164 ) );
		memset( achBufIPType, 0, sizeof( achBufIPType ) );
		memset( achBufIP, 0, sizeof( achBufIP ) );
		
		sprintf( achBufID, "%s%d", s_tpEpAddrID_, wListIndex+1 );
		sprintf( achbufIsAliasIP, "%s%d", s_tpIsAliasIP, wListIndex+1 );
		sprintf( achBufType, "%s%d", s_tpEpAddrAliasType_, wListIndex+1 );
		sprintf( achBufAlias, "%s%d", s_tpEpAddrAlias_, wListIndex+1 );
		sprintf( achBufE164Type, "%s%d", s_tpEpAddrE164Type_, wListIndex+1 );
		sprintf( achBufCallType, "%s%d", s_tpEpAddrCallType_, wListIndex+1 );
		sprintf( achBufE164, "%s%d", s_tpEpAddrE164_, wListIndex+1 );
		sprintf( achBufIPType, "%s%d", s_tpEpAddrIPType_, wListIndex+1 );
		sprintf( achBufIP, "%s%d", s_tpEpAddrIP_, wListIndex+1 );
		
		u32 dwTemp;
		ReadIntegerValue(pFile, pchSection, achBufID, dwTemp);
		tEpList.m_tCnsList[wListIndex].m_wEpID = (u16)dwTemp;
		dwTemp = 0;
		ReadIntegerValue(pFile,pchSection,achbufIsAliasIP,dwTemp);
		tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_bAliasIP = (BOOL32)dwTemp;

		dwTemp = 0;
		ReadIntegerValue(pFile, pchSection, achBufType, dwTemp);
		tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_tAlias.m_byType = (EmTpAliasType)dwTemp;
		ReadStringValue(pFile, pchSection, achBufAlias, tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN);

		dwTemp = 0;
		ReadIntegerValue(pFile, pchSection, achBufE164Type, dwTemp);
		tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_tE164.m_byType = (EmTpAliasType)dwTemp;
		ReadStringValue(pFile, pchSection, achBufE164, tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);
		
		dwTemp = 0;
		ReadIntegerValue(pFile, pchSection, achBufCallType, dwTemp);
		tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_byCallType = (EmTpAliasType)dwTemp;

		dwTemp = 0;
		s8	abyIP[TP_MAX_ALIAS_LEN + 1] = {0};
		if (ReadStringValue(pFile, pchSection, achBufIP, abyIP, TP_MAX_ALIAS_LEN))
		{
			tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_dwIP = inet_addr(abyIP);
		}
		else
		{
			tEpList.m_tCnsList[wListIndex].m_tEpAddr.m_dwIP = 0;
		}
	}
	
	return TRUE;
}

BOOL32 CTemplateInfo::ReadTurnList(FILE* pFile, const s8* const pchSection, TConfTurnList& tTurnList)
{
	s8 achBuf[64] = "";
	
	if(0 == tTurnList.m_wNum)
	{
		return TRUE;
	}

	u32 dwTemp;
	for (u16 wListIndex = 0; wListIndex < tTurnList.m_wNum; ++wListIndex)
	{
		memset(achBuf, 0, sizeof(achBuf));
		sprintf(achBuf, "%s%d", s_tpTurnID_, wListIndex+1);
		dwTemp = TP_INVALID_INDEX;//默认值
		ReadIntegerValue(pFile, pchSection, achBuf, dwTemp);
		tTurnList.m_awList[wListIndex] = (u16)dwTemp;
	}
	
	return TRUE;
}

//读取会议讨论信息
BOOL32 CTemplateInfo::ReadAudMixList(FILE* pFile, const s8* const pchSection, TAuxMixList& tAudMixInfo)
{
	s8 achBuf[64] = "";
	
	u32 dwTemp;
	for (u16 wListIndex = 0; wListIndex < TP_CONF_MAX_AUDMIXNUM; ++wListIndex)
	{
		memset(achBuf, 0, sizeof(achBuf));
		sprintf(achBuf, "%s%d", s_tpAuxMixID_, wListIndex+1);
		dwTemp = TP_INVALID_INDEX;
		ReadIntegerValue(pFile, pchSection, achBuf, dwTemp);
		tAudMixInfo.m_awList[wListIndex] = (u16)dwTemp;
	}
	
	return TRUE;
}

//读取画面合成预案
BOOL32 CTemplateInfo::ReadVmpMemberCfg(FILE* pFile, const s8* const pchSection, TSaveVmpCfg& tVmpMemberCfg)
{
	s8 achVmpEpList[64] = {0};
	u16 wVmpIndex = 0;
	u16 wEpIndex = 0;
	u32 dwTemp;

	dwTemp = (u32)emVMPDynamic;
	ReadIntegerValue(pFile, pchSection, s_tpVmpPlanStyle, dwTemp);
	tVmpMemberCfg.m_emStyle = (EMVmpStyle)dwTemp;
	
	dwTemp = 0;
	ReadIntegerValue(pFile,pchSection,s_tpVmpPlanEpNum,dwTemp);
	tVmpMemberCfg.m_wEpNum = (u16)dwTemp;
	
	dwTemp = 0;
	ReadIntegerValue(pFile,pchSection,s_tpVmpPlanSpeakIndex,dwTemp);
	tVmpMemberCfg.m_wSpeakerIndx = (u16)dwTemp;

	dwTemp = 0;
	ReadIntegerValue(pFile,pchSection,s_tpVmpPlanDualIndex,dwTemp);
	tVmpMemberCfg.m_wDualIndx = (u16)dwTemp;

	for(wEpIndex = 0; wEpIndex < TP_VMP_MAX_IN_CHN_NUM ; ++wEpIndex)
	{
		if (0 == tVmpMemberCfg.m_atEpList[wEpIndex].m_tEpAlias.m_abyAlias)
		{
			continue;
		}
		memset( achVmpEpList , 0 , sizeof( achVmpEpList ) );
		sprintf( achVmpEpList , "%s%d" , s_tpVmpPlanEpAlias_ , wEpIndex+1 );
		ReadStringValue(pFile, pchSection, achVmpEpList, tVmpMemberCfg.m_atEpList[wEpIndex].m_tEpAlias.m_abyAlias ,TP_MAX_ALIAS_LEN);

		memset( achVmpEpList, 0 ,sizeof( achVmpEpList ));
		sprintf( achVmpEpList, "%s%d", s_tpVmpPlanScrIndex_, wEpIndex+1 );
		dwTemp = (u16)0;
		ReadIntegerValue(pFile, pchSection, achVmpEpList, dwTemp);
		tVmpMemberCfg.m_atEpList[wEpIndex].m_wScrIndx = dwTemp;
	}
	
	return TRUE;
}
//读取会场呼叫信息
BOOL32 CTemplateInfo::ReadEpCallProcotol(FILE* pFile, const s8* const pchSection, TTemplateConfEx& tTempex,TEpAddrList& tEpList)
{
	s8 achBufCallPro[64] = "";
	s8 achCallPro[64] = "";

	
	if( 0 == tTempex.m_wNum )
	{
		return TRUE;
	}
	
	for (u16 wListIndex = 0; wListIndex < tTempex.m_wNum; ++wListIndex )
	{
		
		tTempex.m_awEpID[wListIndex] = tEpList.m_tCnsList[wListIndex].m_wEpID;
		memset( achBufCallPro, 0, sizeof( achBufCallPro ) );
		memset( achCallPro, 0, sizeof( achCallPro ) );
		sprintf( achBufCallPro, "%s%d", s_tpEpCallProtocol_, wListIndex+1 );

		ReadStringValue(pFile, pchSection, achBufCallPro, achCallPro, TP_MAX_ALIAS_LEN);
		if (0 == strcmp(achCallPro,"emTpSIP"))
		{
			tTempex.m_aemCallProtocol[wListIndex] = emTpSIP;

		}
		else if (0 == strcmp(achCallPro,"emTpH323"))
		{
			tTempex.m_aemCallProtocol[wListIndex] = emTpH323;
		}
	}
	return TRUE;

}
//读取会议加密信息
BOOL32 CTemplateInfo::ReadEncryptInfo(FILE* pFile, const s8* const pchSection, TTPEncrypt& tEncryptInfo)
{
	u32 dwTemp;
	dwTemp = (u32)emTPEncryptTypeNone;

	ReadIntegerValue(pFile, pchSection, s_tpEncryptType, dwTemp);
	tEncryptInfo.m_emEncryptModel = (EmTPEncryptType)dwTemp;


	ReadStringValue(pFile, pchSection, s_tpEncryptKey, tEncryptInfo.m_achEncKey, TP_ENCRYPT_KEY_LEN);
	tEncryptInfo.m_byKeyLen = strlen(tEncryptInfo.m_achEncKey);
	if (tEncryptInfo.m_byKeyLen > TP_ENCRYPT_KEY_LEN)
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::ReadEncryptInfo]Encryp length is out of range!\n"));
		return FALSE;
	}
	return TRUE;
}

//读取音频格式 
BOOL32 CTemplateInfo::ReadAudioRes(FILE* pFile, const s8* const pchSection, TUmsAudFormat tRes[], u16 wAudioResNum)
{ 
	s8 achAudioFormat[64] = {0};   
	s8 achAudioFreq[64] = {0};  
	s8 achAudioReserve[64] = {0};
	u16 wResIndex = 0;
	  
	if (0 == wAudioResNum)
	{
		return TRUE;
	}
	
	u32 dwTemp;
	for (wResIndex = 0; wResIndex < TP_CONF_MAX_AUD_FMT_NUM; ++wResIndex)
	{	
		memset( achAudioFormat, 0, sizeof( achAudioFormat ) );
		memset( achAudioFreq, 0, sizeof( achAudioFreq ) );
		memset( achAudioReserve, 0, sizeof( achAudioReserve ) );
 
		sprintf( achAudioFormat, "%s%d", s_tpAudioFormat_, wResIndex + 1 );
		sprintf( achAudioFreq, "%s%d", s_tpAudioFreq_, wResIndex + 1 );
		sprintf( achAudioReserve, "%s%d", s_tpAudioReservel_, wResIndex + 1 );

		dwTemp = (u32)emTPAMpegAACLD;
		ReadIntegerValue(pFile, pchSection, achAudioFormat, dwTemp);
		tRes[wResIndex].m_emFormat = (EmTpAudioFormat)dwTemp;

		dwTemp = (u32)emTPFs32000;
		ReadIntegerValue(pFile, pchSection, achAudioFreq, dwTemp);
		tRes[wResIndex].m_emSampleFreq = (EmTPAACSampleFreq)dwTemp;
		
		dwTemp = 0;
		ReadIntegerValue(pFile, pchSection, achAudioReserve, dwTemp);
		tRes[wResIndex].m_byReserve1 = (u8)dwTemp;

	}

	return TRUE;
}

//读取主视频格式
BOOL32 CTemplateInfo::ReadMainVideoRes(FILE* pFile, const s8* const pchSection, TUmsVidFormat tRes[], u16 wMainResNum)
{
	s8 achVideoLvl[64] = {0};
	s8 achVideoRes[64] = {0};
	s8 achVideoFrame[64] = {0};

	u16 wResIndex = 0;
	
	if (0 == wMainResNum)
	{
		return TRUE;
	}
	
	u32 dwTemp;
	for (wResIndex = 0; wResIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; ++wResIndex)
	{
		memset( achVideoLvl, 0, sizeof( achVideoLvl ) );
		memset( achVideoRes, 0, sizeof( achVideoRes ) );
		memset( achVideoFrame, 0, sizeof( achVideoFrame ));
		
		sprintf( achVideoLvl, "%s%d", s_tpMainVideoLvl_, wResIndex + 1 );
		sprintf( achVideoRes, "%s%d", s_tpMainVideoRes_, wResIndex + 1 );
		sprintf( achVideoFrame, "%s%d", s_tpMainVideoFrame_, wResIndex + 1);

		dwTemp = (u32)emTPH264HP;
		ReadIntegerValue(pFile, pchSection, achVideoLvl, dwTemp);
		tRes[wResIndex].m_emQualityLvl = (EmTpVideoQualityLevel)dwTemp;

		dwTemp = (u32)emTPVHD1080p1920x1080;
		ReadIntegerValue(pFile, pchSection, achVideoRes, dwTemp);
		tRes[wResIndex].m_emRes = (EmTpVideoResolution)dwTemp;

		dwTemp = 60;
		ReadIntegerValue(pFile, pchSection, achVideoFrame, dwTemp);
		tRes[wResIndex].m_wFrameRate = (u16)dwTemp;
	}

	return TRUE;
}

//读取辅视频格式
BOOL32 CTemplateInfo::ReadMinorVideoRes(FILE* pFile, const s8* const pchSection, TUmsVidFormat tRes[], u16 wMinorResNum)
{
	s8 achVideoLvl[64] = {0};
	s8 achVideoRes[64] = {0};
	s8 achVideoFrame[64] = {0};

	u16 wResIndex = 0;
	
	if (0 == wMinorResNum)
	{
		return TRUE;
	}
	
	u32 dwTemp;
	for (wResIndex = 0; wResIndex < wMinorResNum; ++wResIndex)
	{
		memset( achVideoLvl, 0, sizeof( achVideoLvl ) );
		memset( achVideoRes, 0, sizeof( achVideoRes ) );
		memset( achVideoFrame, 0, sizeof( achVideoFrame ));

		sprintf( achVideoLvl, "%s%d", s_tpMinorVideoLvl_, wResIndex + 1 );
		sprintf( achVideoRes, "%s%d", s_tpMinorVideoRes_, wResIndex + 1 );
		sprintf( achVideoFrame, "%s%d", s_tpMinorVideoFrame_, wResIndex + 1);

		dwTemp = (u32)emTPH264HP;
		ReadIntegerValue(pFile, pchSection, achVideoLvl, dwTemp);
		tRes[wResIndex].m_emQualityLvl = (EmTpVideoQualityLevel)dwTemp;

		dwTemp = (u32)emTPVHD1080p1920x1080;
		ReadIntegerValue(pFile, pchSection, achVideoRes, dwTemp);
		tRes[wResIndex].m_emRes = (EmTpVideoResolution)dwTemp;

		dwTemp = 60;
		ReadIntegerValue(pFile, pchSection, achVideoFrame, dwTemp);
		tRes[wResIndex].m_wFrameRate = (u16)dwTemp;
	}

	return TRUE;
}


BOOL32 CTemplateInfo::GetConfTempInfo(TConfTemplateLocal &tTpConfTemplate, u16 wIndex)
{
	if( ( wIndex<0 ) || ( wIndex >= TP_CONFTEMPLATE_MAXNUM ) )
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::GetConfTempInfo]The Index is out of range!\n"));
		return FALSE;
	}
	
	if( !OspSemTakeByTime(m_semConfLock, WAIT_SEM_TIMEOUT))
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::GetConfTempInfo]OspSemTakeByTime excute failed SemLock value is %d\n", m_semConfLock));
        return FALSE;
	} 

	if (!m_tControlData.m_abValidSeq[wIndex])
	{
		OspSemGive(m_semConfLock);
		return FALSE;
	}

	memcpy(&tTpConfTemplate, &m_atConfTemplate[wIndex], sizeof(TConfTemplateLocal));

	OspSemGive(m_semConfLock);

	return TRUE;
}

BOOL32 CTemplateInfo::SetConfTempInfo(TConfTemplateLocal& tTpConfTemplate, u16 wIndex)
{
	if( ( wIndex<0 ) || ( wIndex >= TP_CONFTEMPLATE_MAXNUM ) )
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::SetConfTempInfo]The Index is out of range!\n"));
		return FALSE;
	}
	
	if( !OspSemTakeByTime(m_semConfLock, WAIT_SEM_TIMEOUT))
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::SetConfTempInfo]OspSemTakeByTime excute failed sem value is %d\n", m_semConfLock));
        return FALSE ;
	} 
	
	memcpy(&(m_atConfTemplate[wIndex]), &tTpConfTemplate, sizeof(TConfTemplateLocal));
	if (!m_tControlData.m_abValidSeq[wIndex])
	{
		++m_tControlData.m_wValidNum;
	}
	m_tControlData.m_abValidSeq[wIndex] = TRUE;
	
	TIndexALLTpConfigData tIndexALLTpConfigData;
	memset(&tIndexALLTpConfigData,0,sizeof(tIndexALLTpConfigData));
	
	memcpy(&(tIndexALLTpConfigData.m_tALLTpConfigData), &(m_atConfTemplate[wIndex]), sizeof(TALLTpConfigData));
	tIndexALLTpConfigData.m_wIndex = wIndex;
	
	::OspPost(MAKEIID(AID_TP_CFGDATA), EV_TP_UPDATE_CMD,
			  &tIndexALLTpConfigData, sizeof( TIndexALLTpConfigData));

	::OspPost(MAKEIID(AID_TP_CFGDATA), EV_TP_VALID_CMD,
			  &m_tControlData, sizeof(TControlData));
	
	OspSemGive(m_semConfLock);

	return TRUE;
}

BOOL32 CTemplateInfo::DelConfTempInfo(u16 wIndex)
{
	if( ( wIndex<0 ) || ( wIndex >= TP_CONFTEMPLATE_MAXNUM ) )
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::DelConfTempInfo]The Index is out of range!\n"));
		return FALSE;
	}
	
	if( !OspSemTakeByTime(m_semConfLock, WAIT_SEM_TIMEOUT))
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::DelConfTempInfo]OspSemTakeByTime excute failed sem value is %d\n", m_semConfLock));
        return FALSE ;
	}

	if (m_tControlData.m_abValidSeq[wIndex])
	{
		m_tControlData.m_abValidSeq[wIndex] = FALSE;
		--m_tControlData.m_wValidNum;
	}

	m_atConfTemplate[wIndex].m_wID = TP_INVALID_INDEX;
	m_atConfTemplate[wIndex].Clear();

	TIndexALLTpConfigData tIndexALLTpConfigData;
	memset(&tIndexALLTpConfigData,0,sizeof(tIndexALLTpConfigData));
	
	memcpy(&(tIndexALLTpConfigData.m_tALLTpConfigData), &(m_atConfTemplate[wIndex]), sizeof(TALLTpConfigData));
	tIndexALLTpConfigData.m_wIndex = wIndex;
	
	::OspPost(MAKEIID(AID_TP_CFGDATA), EV_TP_UPDATE_CMD,
		&tIndexALLTpConfigData, sizeof( TIndexALLTpConfigData));
	
	::OspPost(MAKEIID(AID_TP_CFGDATA), EV_TP_VALID_CMD,
			  &m_tControlData, sizeof(TControlData));

	OspSemGive(m_semConfLock);
	return TRUE;
}

void CTemplateInfo::GetAllConfTemp(TConfTemplateLocal atConfTemplate[TP_CONFTEMPLATE_MAXNUM])
{
	if( !OspSemTakeByTime(m_semConfLock, WAIT_SEM_TIMEOUT))
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::GetAllConfTemp]OspSemTakeByTime excute failed sem value is %d\n", m_semConfLock));
        return  ;
	} 

	memcpy(atConfTemplate, m_atConfTemplate, sizeof(m_atConfTemplate));

	OspSemGive(m_semConfLock);
}

void CTemplateInfo::GetControlData(TControlData& tControlData)
{
	if( !OspSemTakeByTime(m_semConfLock, WAIT_SEM_TIMEOUT))
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::GetControlData]OspSemTakeByTime excute failed sem value is %d\n", m_semConfLock));
        return  ;
	} 

	memcpy(&tControlData, &m_tControlData, sizeof(TControlData));
	
	OspSemGive(m_semConfLock);
}

BOOL32 CTemplateInfo::IsValid(u16 wIndex)
{
	if (wIndex < 0 || wIndex >= TP_CONFTEMPLATE_MAXNUM)
	{
		return FALSE;
	}
	
	if( !OspSemTakeByTime(m_semConfLock, WAIT_SEM_TIMEOUT))
	{
		MdlError(Ums_Mdl_Cfg,("[CTemplateInfo::IsValid]OspSemTakeByTime excute failed sem value is %d\n", m_semConfLock));
        return  FALSE;
	} 

	BOOL32 bRes = m_tControlData.m_abValidSeq[wIndex];

	OspSemGive(m_semConfLock);

	return bRes;
}