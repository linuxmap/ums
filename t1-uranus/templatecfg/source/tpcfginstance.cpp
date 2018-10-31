/*******************************************************************************
  模块名      : KDVMT MtAgent
   文件名      : CCfgDataManager.h
   相关文件    : CCfgDataManager.cpp
   文件实现功能: KDVMT 代理基类头文件
   作者        : 
   版本        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2005/03/24  1.0         耿昌明       创建
   2005/07/21  4.0         张  飞       修改：为CCfgDataManager添加获取文件名称函数
                                        修改： CIMtCfg消息内容，修改InstanceEntry实现方式
										修改：移动InstanceDump到头文件中实现
										修改：移动InstanceExit到头文件中实现
*******************************************************************************/
#include "tpcfginstance.h"
#include "tprwnewcfgfile.h"
#include "systpcom.h"
#include "tppersistfile.h"
#include "tpconfig.h"
#include "umsconfig.h"
#include "tplog.h"
#include "umsobject.h"

#ifdef _VXWORKS_
#include "fpdrvlib.h"
#endif

#ifdef _LINUX_
#include "brdwrapper.h"
#include "nipwrapper.h"
#endif
#include "tplogmgr.h"
#include "tpinfo.h"
#include "eventoutumsconftemplate.h"

#define FILE_NAME_LEN 255

extern CTpCfgDataManager g_cTpCfgDataMan[TP_CONFTEMPLATE_MAXNUM];
extern CTpCfgDataManager g_cTpControlDataMan;
extern SEMHANDLE s_semQuitCfg;


CTpPersistCfg::CTpPersistCfg()
{
	m_pbySaveData = NULL;
    m_dwDataSize  = 0;

	m_dwTime = 0;
	
	for( u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		m_abNeedSaveCfgData[wIndex] = FALSE;
	}

	m_bNeedSaveValidData = FALSE;

	memset(m_achFileName,0,sizeof(m_achFileName));
	memset(&m_tALLTpConfigDataBak,0,sizeof(m_tALLTpConfigDataBak));
	memset(&m_tIndexALLTpConfigData,0,sizeof(m_tIndexALLTpConfigData));
	memset(&m_tControlDataBak,0,sizeof(m_tControlDataBak));


}

CTpPersistCfg::~CTpPersistCfg()
{
	if ( m_pbySaveData )
		free( m_pbySaveData );
	m_pbySaveData = NULL;
}
	
void CTpPersistCfg::InstanceEntry( CMessage* const pcMsg )
{
	u16 wEvent = pcMsg->event;
	u8* buf = pcMsg->content;
	u16 wLen = pcMsg->length;
    switch( pcMsg->event )
	{
	case EV_TPCFG_INIT_CMD:
		{
			OnInitPersist(buf,wLen);
			break;
		}

	case EV_TP_SAVE_CMD:
		{
			OnSaveFileData(buf,wLen);
			break;
		}
	case EV_TP_UPDATE_CMD:
		{
			OnUpdateData(buf,wLen);
			break;
		}
	case TIMER_SAVE_TP_CFGDATA:
		{
			OnSaveFileImmediately(buf,wLen);
			break;
		}

	case EV_TP_VALID_CMD:
		{
			OnSaveValidNum(buf,wLen);
			break;
		}

	case EV_TP_UPLOAD_FILE:
		{
			OnUpLoadFile(buf, wLen);
			break;
		}

	case EV_TP_DOWNLOAD_FILE:
		{
			OnDownLoadFile(buf, wLen);
			break;
		}

    default:
		break;
	}
}

void CTpPersistCfg::OnDownLoadFile(u8* pBuf,u16 wLen)
{
s16  wStatus = 0 ;
#ifdef _LINUX_ 
    #if defined(_PPC_82XX_) || defined(_PPC_85XX_)	
	wStatus = system("mkdir /ramdisk/template_down");
	#else
	wStatus = system("mkdir /usr/template_down");
	#endif
	//	如果fork失败了，或者waitpid返回除了EINTR之外的错误，system返回 -1；
	// execl执行失败，其返回值如同shell执行了"exit(127)" 一样。
	if (-1 == wStatus || 127 == wStatus)
	{
		msgprint("[OnDownLoadFile] system error!\n");
		return;
	}
	
#endif
	u16 wValidCount = 0;
	for(u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++ wIndex)
	{
		if (wValidCount == m_tControlDataBak.m_wValidNum)
		{
			break;
		}
		
		if (!m_tControlDataBak.m_abValidSeq[wIndex])
		{
			continue;
		}
   
		s8 szFileName[TP_FILE_NAME_LEN+1] = {0};
		sprintf(szFileName, "%s%d.ini", UmsGetFileName(emUmsTpDownTemplateFile), wIndex+1);
		FILE *pFile = fopen(szFileName,"w");
		BOOL32 bSuc = TRUE;
		if(NULL == pFile)
		{
			MdlError(Ums_Mdl_Cfg,("[OnDownLoadFile]Open file:%s failed.!\n", szFileName));
			continue;
		}

		++wValidCount; 
		SaveDataToTpFile(pFile, m_tALLTpConfigDataBak, wIndex, szFileName);

		fclose(pFile);
	}

	s8 achCommandBuf[256] = {0};
	memcpy(achCommandBuf, "tar cvf ", sizeof("tar cvf "));
	strcat(achCommandBuf, UmsGetFileName(emUmsTpDownLoadFile)); //将文件打包
	#ifdef _LINUX_ 
	#if defined(_PPC_82XX_) || defined(_PPC_85XX_)	
	strcat(achCommandBuf," /ramdisk/template_down");
	#else
	strcat(achCommandBuf," /usr/template_down");
    #endif
	#endif
	msgprint("[OnDownLoadFile] achCommandBuf->%s .\n", achCommandBuf);

#if defined(_LINUX_)
	msgprint("[OnDownLoadFile] execute command ->%s .\n", achCommandBuf);
	wStatus = system(achCommandBuf);
	if (-1 == wStatus || 127 == wStatus)
	{
		msgprint("[OnDownLoadFile] system error!\n");
		return;
	}
#endif	
	
	s8 szDownFullName[TP_FILE_NAME_LEN+1] = {0};
	sprintf(szDownFullName,"%s",UmsGetFileName(emUmsTpDownLoadFile));
	TLogUser tLogUser;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_downloadConftemp_rsq);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(szDownFullName, sizeof(szDownFullName));
	cMsg.Post(UMS_SERVICE_APP_INST);

	memset(achCommandBuf,0,sizeof(achCommandBuf));
	memcpy(achCommandBuf,"rm -rf ",sizeof("rm -rf "));
	#if defined(_LINUX_)
	#if defined(_PPC_82XX_) || defined(_PPC_85XX_)	
	strcat(achCommandBuf," /ramdisk/template_down");
	#else
	strcat(achCommandBuf," /usr/template_down");
    #endif
	#endif
	msgprint("[OnDownLoadFile] achCommandBuf->%s .\n", achCommandBuf);
#if defined(_LINUX_)
	msgprint("[OnDownLoadFile] execute command ->%s .\n", achCommandBuf);
	wStatus = system(achCommandBuf);
	if (-1 == wStatus || 127 == wStatus)
	{
		msgprint("[OnDownLoadFile] system error!\n");
		return;
	}
#endif	
	return ;
}

void CTpPersistCfg::OnUpLoadFile(u8* pBuf,u16 wLen)
{
	s8 szFileName[TP_UPLOAD_FILE_NAME_LENGTH + 1] = {0};
	memcpy(szFileName, pBuf, wLen);

	TLogUser tLogUser;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_uploadConftemp_rsq);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));

	BOOL32 bRet = TRUE;

	time_t CurTime;
	time(&CurTime);

	if(CurTime-m_dwTime<12)
	{//小于12s 则返回服务器忙
		bRet = FALSE;
		MdlError(Ums_Mdl_Cfg,("CTpPersistCfg::OnUpLoadFile Server Busy! curtime:%d, dwTime:%d\n", CurTime, m_dwTime));
		cMsg.CatBody(&bRet, sizeof(BOOL32));
		cMsg.Post(UMS_SERVICE_APP_INST);
		return ;
	}

	m_dwTime = CurTime;

	CTemplateInfo::Instance().UpLoadTempFromFile(szFileName);
	CTemplateInfo::Instance().GetAllConfTemp(m_tALLTpConfigDataBak);
	CTemplateInfo::Instance().GetControlData(m_tControlDataBak);

	u16 wValidCount = 0;
	for (u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		if (wValidCount == m_tControlDataBak.m_wValidNum)
		{
			break;
		}
		else
		{
			if (m_tControlDataBak.m_abValidSeq[wIndex])
			{
				m_abNeedSaveCfgData[wIndex] = TRUE;
				++wValidCount;
			}
		}
	}

	m_bNeedSaveValidData = TRUE;
	
	KillTimer( TIMER_SAVE_TP_CFGDATA );
	SetTimer( TIMER_SAVE_TP_CFGDATA, SAVE_TIME_OUT );

	cMsg.CatBody(&bRet, sizeof(BOOL32));
	cMsg.Post(UMS_SERVICE_APP_INST);

	return ;
}

/*====================================================================
  函 数 名： OnInitPersist
  功    能： 
  算法实现： 
  全局变量： 
  参    数： u8* buf
             u16 wLen
  返 回 值： void 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/4/14      1.0		    张 飞                   创建
======================================================================*/
void CTpPersistCfg::OnInitPersist(u8* buf,u16 wLen)
{
	u16 wBufLen = sizeof(m_achFileName)-1;

	strncpy(m_achFileName, UmsGetFileName(emUmsTpFile), wBufLen);
	CTemplateInfo::Instance().GetAllConfTemp(m_tALLTpConfigDataBak);
	CTemplateInfo::Instance().GetControlData(m_tControlDataBak);

	if(strlen(m_achFileName) == 0)
	{
        MdlError(Ums_Mdl_Cfg,("[OnInitPersist]the config file name get error %s\n",m_achFileName));
		return ;
	}


	m_pbySaveData = NULL;
	m_dwDataSize = 0;
}
/*====================================================================
  函 数 名： OnUpdateData
  功    能： 
  算法实现： 
  全局变量： 
  参    数： u8* buf
             u16 wLen
  返 回 值： void 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/4/14      1.0		    张 飞                   创建
  2007/11/20     4.0            fangtao             添加同步信号量保护
======================================================================*/
void CTpPersistCfg::OnSaveFileData(u8* buf ,u16 wLen)
{

	if(m_bNeedSaveValidData)
	{
		if(!PersistControlData())
		{
			MdlError(Ums_Mdl_Cfg,("save the control fail\n"));
		}
		else
		{
			tpHintNoFile(Ums_Mdl_Cfg,"save the control success\n");
			m_bNeedSaveValidData = FALSE;
		}
		
		
	}


	for (u16 wIndex = 0; wIndex <= TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		if( !CTemplateInfo::Instance().IsValid(wIndex) || !m_abNeedSaveCfgData[wIndex])
		{
			continue;
		}

		else
		{
			PersistFileData(wIndex);
			m_abNeedSaveCfgData[wIndex] = FALSE;
		}
	}


    KillTimer( TIMER_SAVE_TP_CFGDATA );

    tpHintNoFile(Ums_Mdl_Cfg, "OnSaveFileData quit succed! \n");
    OspSemGive( s_semQuitCfg );
}




/*====================================================================
  函 数 名： OnSaveFileData
  功    能： 
  算法实现： 
  全局变量： 
  参    数： u8* buf
             u16 wLen
  返 回 值： void 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/4/14      1.0		    张 飞                   创建
======================================================================*/
void CTpPersistCfg::OnUpdateData(u8* buf,u16 wLen)
{


	memcpy( &m_tIndexALLTpConfigData, buf, sizeof(TIndexALLTpConfigData));

	u16 wIndex = m_tIndexALLTpConfigData.m_wIndex;
	
	if( ( wIndex<0 ) || ( wIndex >= TP_CONFTEMPLATE_MAXNUM ) )
	{
		MdlError(Ums_Mdl_Cfg,("[OnUpdateData]The Index is out of range!\n"));
		return;
	}

	
	memcpy( &m_tALLTpConfigDataBak[wIndex], &( m_tIndexALLTpConfigData.m_tALLTpConfigData ), sizeof( TALLTpConfigData ) );

	m_abNeedSaveCfgData[wIndex] = TRUE;

	KillTimer( TIMER_SAVE_TP_CFGDATA );
	SetTimer( TIMER_SAVE_TP_CFGDATA, SAVE_TIME_OUT );


	tpHintNoFile(Ums_Mdl_Cfg,"Recv the save data message ...\n");
}
/*====================================================================
  函 数 名： OnSaveFileImmediately
  功    能： 
  算法实现： 
  全局变量： 
  参    数： u8* buf
             u16 wLen
  返 回 值： void 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/4/14      1.0		    张 飞                   创建
======================================================================*/
void CTpPersistCfg::OnSaveFileImmediately(u8* buf,u16 wLen)
{
	if(m_bNeedSaveValidData)
	{
		if(!PersistControlData())
		{
			MdlError(Ums_Mdl_Cfg,("save the control fail\n"));
		}
		else
		{
			tpHintNoFile(Ums_Mdl_Cfg,"save the control success\n");
			m_bNeedSaveValidData = FALSE;
		}
	}

	u16 wSaveNum = 0;
	for( u16 wIndex = 0; wIndex < TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		if ( !m_abNeedSaveCfgData[wIndex] ) 
		{
			continue;
		}
		else
		{
			if ( wSaveNum > 10 )
			{//大量模板需要保存时，该线程被占用很久，导致无响应
				//此处限制 一次只保存10个模板 大概占用2s 然后空闲2s后继续保存
				KillTimer( TIMER_SAVE_TP_CFGDATA );
				SetTimer( TIMER_SAVE_TP_CFGDATA, 1000 );
				break;
			}
			tpHintNoFile(Ums_Mdl_Cfg,"saving the data ...\n");
			if( !PersistFileData(wIndex) )
			{
				MdlError(Ums_Mdl_Cfg,("save the data fail %d\n",wIndex+1));
			}
			else
			{
				tpHintNoFile(Ums_Mdl_Cfg,"saved the data success %d\n",wIndex+1);
				m_abNeedSaveCfgData[wIndex] = FALSE;
				wSaveNum ++;
			}
		}
	}
	return;
}


void CTpPersistCfg::OnSaveValidNum(u8 *buf, u16 wLen)
{
	m_bNeedSaveValidData = TRUE;
	memcpy(&m_tControlDataBak,buf,sizeof(m_tControlDataBak));

	KillTimer( TIMER_SAVE_TP_CFGDATA );
	SetTimer( TIMER_SAVE_TP_CFGDATA, SAVE_TIME_OUT );
	
	
	tpHintNoFile(Ums_Mdl_Cfg,"Recv the save control message ...\n");

}
/*====================================================================
  函 数 名： PersistFileData
  功    能： 同步文件，并进行文件持久化工作
  算法实现： 
  全局变量： 
  参    数： 无
  返 回 值： TRUE 保存成功 FALSE保存失败
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/7/21      1.0		    张 飞                   创建
======================================================================*/

BOOL CTpPersistCfg::PersistFileData(u16 wIndex)
{
	if(strlen(m_achFileName) == 0)
	{
		MdlError(Ums_Mdl_Cfg,("[PersistFileData]the saved config file is %s\n",m_achFileName));
		return FALSE;
	}
	
	tpHintNoFile(Ums_Mdl_Cfg,"Beginning save data to file ...\n");

	if(!SaveDataToTpFile(m_achFileName,m_tALLTpConfigDataBak, wIndex))
	{
		MdlError(Ums_Mdl_Cfg,("[PersistFileData]SaveDataToTpFile Fail in %d file\n",wIndex+1));
		return FALSE;
	}


	tpHintNoFile(Ums_Mdl_Cfg,"the data is saved to file \n");

#ifndef _LINUX_
	return TRUE;
#endif


	return WriteFileToRawDisk(wIndex);


}

#ifndef FILE_TPCTL_INI
#define FILE_TPCTL_INI (s8*)"control.ini"
#endif

/*====================================================================
  函 数 名： WriteFileToRawDisk
  功    能： 把文件内容写到rawdisk中去, 实际为将数据保存到分区里面
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/8/26      1.0		    张 飞                   创建
======================================================================*/
BOOL CTpPersistCfg::WriteFileToRawDisk(u16 wIndex)
{

	s8 achFullFileName[TP_FILENAME_LENGTH] = {0};

	if(TP_INVALID_INDEX == wIndex)
	{
		strncpy(achFullFileName, UmsGetFileName(emUmsTpControlFile), sizeof(achFullFileName));
	}

	else
	{
		sprintf(achFullFileName,"%s%d.ini",m_achFileName,wIndex+1);
	}

	FILE* pfFile = fopen(achFullFileName,"rb");
	if(NULL == pfFile)
	{
		MdlError(Ums_Mdl_Cfg,("[WriteFileToRawDisk] open cfg file %s error",m_achFileName));
		return FALSE;
	}
	fseek(pfFile, 0L, SEEK_END);
	u32  dwLen = ftell(pfFile);
	if(dwLen > m_dwDataSize)
	{
		m_pbySaveData = (u8*)realloc(m_pbySaveData,dwLen*sizeof(char));
		if(NULL == m_pbySaveData)
		{
			MdlError(Ums_Mdl_Cfg,("[WriteFileToRawDisk]realloc mem fail\n"));
			fclose(pfFile);
			return FALSE;
		}
		m_dwDataSize = dwLen;
	}
	memset(m_pbySaveData,0,m_dwDataSize);
	fseek(pfFile,0L,SEEK_SET);
	u32 dwReadLen = fread(m_pbySaveData,sizeof(char),
		m_dwDataSize*sizeof(char),pfFile);
	if(dwReadLen != dwLen)
	{
		MdlError(Ums_Mdl_Cfg,("[WriteFileToRawDisk]read config file fail\n"));
		fclose(pfFile);
		return FALSE;
	}
	fclose(pfFile);

	//将数据保存到USER0/USER1的分区里面
	//在T2终端里面，由于os的分区不再单独由USER0/USER1,
	//故实际上终端用了两个配置文件0mtcfg.ini和1mtcfg.ini来替换了


	if(TP_INVALID_INDEX == wIndex)
	{
		if(!g_cTpControlDataMan.SaveData(m_pbySaveData, dwLen))
		{
			MdlError(Ums_Mdl_Cfg,("[WriteFileToRawDisk]save control to rawdisk error\n"));
			return FALSE;
		}

		return TRUE;
	}

	if(!g_cTpCfgDataMan[wIndex].SaveData(m_pbySaveData, dwLen))
	{
		MdlError(Ums_Mdl_Cfg,("[WriteFileToRawDisk]save data to rawdisk error\n"));
		return FALSE;
	}
    return TRUE;	
}

BOOL CTpPersistCfg::PersistControlData()
{
	
	tpHintNoFile(Ums_Mdl_Cfg,"Beginning save control to file ...\n");
	
	if (!SaveDataToControlFile(UmsGetFileName(emUmsTpControlFile), m_tControlDataBak))
	{
		MdlError(Ums_Mdl_Cfg,("the control is not saved to file \n"));
		return FALSE;
	}
	else
	{
		tpHintNoFile(Ums_Mdl_Cfg,"the data is saved to file \n");

#ifndef _LINUX_
		return TRUE;
#endif
		//LINUX下写控制数据
		return WriteFileToRawDisk(TP_INVALID_INDEX);
	}

}
