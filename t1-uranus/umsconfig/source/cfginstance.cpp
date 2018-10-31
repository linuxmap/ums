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


#include "cfginstance.h"
#include "rwnewcfgfile.h"
#include "syscfgcom.h"
#include "persistfile.h"

#ifdef _VXWORKS_
#include "fpdrvlib.h"
#endif

#ifdef _LINUX_
#include "brdwrapper.h"
#include "nipwrapper.h"
#endif
extern CCfgDataManager g_cUmsCfgDataMan;
extern BOOL g_bUmsShowConfig_info;
extern SEMHANDLE s_semUmsQuitCfg;


CPersistCfg::CPersistCfg()
{
	m_pbySaveData = NULL;
    m_dwDataSize  = 0;
	m_bNeedSaveCfgData = FALSE;
	memset(m_achFileName,0,sizeof(m_achFileName));
	memset(&m_tALLConfigDataBak,0,sizeof(m_tALLConfigDataBak));
	
#if defined(_LINUX_) && defined(_d6446_)
	::nice(19);
#endif
	
#ifdef WIN32
	//重置捕获优先级为 THREAD_PRIORITY_LOWEST
	HANDLE hCfg = GetCurrentThread();
	s32 nPrePriority = GetThreadPriority( hCfg );
	if( THREAD_PRIORITY_LOWEST != nPrePriority )
	{
		BOOL32 bRet = SetThreadPriority( hCfg , THREAD_PRIORITY_LOWEST );
		s32    nRealPriority = GetThreadPriority(hCfg);
		msgprint("[SetThreadPriority] VidCap bRet=%d, nPrePriority=%d, nRealPriority=%d", 
			              bRet, nPrePriority, nRealPriority );
	}

#endif

}

CPersistCfg::~CPersistCfg()
{
	if ( m_pbySaveData )
		free( m_pbySaveData );
	m_pbySaveData = NULL;
}
	
void CPersistCfg::InstanceEntry( CMessage* const pcMsg )
{
	u16 wEvent = pcMsg->event;
	u8* buf = pcMsg->content;
	u16 wLen = pcMsg->length;
    switch( pcMsg->event )
	{
	case EV_SYSCFG_INIT_CMD:
		{
			OnInitPersist(buf,wLen);
			break;
		}

	case EV_MTA_MTAC_SAVE_CMD:
		{
			OnSaveFileData(buf,wLen);
			break;
		}
	case EV_MTA_MTAC_UPDATE_CMD:
		{
			OnUpdateData(buf,wLen);
			break;
		}
	case TIMER_SAVE_CFGDATA:
		{
			OnSaveFileImmediately(buf,wLen);
			break;
		}
    default:
		break;
	}
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
void CPersistCfg::OnInitPersist(u8* buf,u16 wLen)
{
	u16 wBufLen = sizeof(m_achFileName)-1;
	u16 wStrLen = wBufLen > wLen ? wLen : wBufLen;
	strncpy(m_achFileName,(s8*)buf,wStrLen);
	if(strlen(m_achFileName) == 0)
	{
        msgprint("[MtConfig]the config file name get error %s\n",m_achFileName);
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
void CPersistCfg::OnSaveFileData(u8* buf ,u16 wLen)
{
    
    if(!m_bNeedSaveCfgData) 
    {
        msgprint( "OnSaveFileData quit succed, no need save! \n" );
        OspSemGive( s_semUmsQuitCfg );
        return ;
    }
    KillTimer( TIMER_SAVE_CFGDATA );
    if(!PersistFileData()) 
    {
        msgprint( "OnSaveFileData quit succed, but persist failed! \n" );
        OspSemGive( s_semUmsQuitCfg );
        return;
    }
    m_bNeedSaveCfgData = FALSE;
    msgprint( "OnSaveFileData quit succed! \n" );
    OspSemGive( s_semUmsQuitCfg );
}
/*====================================================================
  函 数 名： OnSaveMtbFileData
  功    能： 
  算法实现： 
  全局变量： 
  参    数： u8* buf
             u16 wLen
  返 回 值： void 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2007/01/09      1.0		    wangliang             创建
======================================================================*/
void CPersistCfg::OnSaveMtbFileData(u8* buf ,u16 wLen)
{
	if(!m_bNeedSaveCfgData) return ;
	KillTimer( TIMER_SAVE_CFGDATA );
    memcpy(&m_tALLConfigDataBak, &g_tALLConfigData, sizeof(g_tALLConfigData));
	if(!PersistFileData()) return;
	m_bNeedSaveCfgData = FALSE;
}

void CPersistCfg::OnUpdateData(u8* buf,u16 wLen)
{
	memcpy(&m_tALLConfigDataBak, buf, wLen);
	m_bNeedSaveCfgData = TRUE;

	KillTimer( TIMER_SAVE_CFGDATA );
	SetTimer( TIMER_SAVE_CFGDATA, SAVE_TIME_OUT );
	if(g_bUmsShowConfig_info)
		msgprint("Recv the save data message ...\n");
}

void CPersistCfg::OnSaveFileImmediately(u8* buf,u16 wLen)
{
	if ( !m_bNeedSaveCfgData ) return;

	if(g_bUmsShowConfig_info)	msgprint("saving the data ...\n");
	if(!PersistFileData())	return;
	if(g_bUmsShowConfig_info)	msgprint("saved the data \n");
	m_bNeedSaveCfgData = FALSE;
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

BOOL CPersistCfg::PersistFileData()
{
	if(strlen(m_achFileName) == 0)
	{
		msgprint("[MtConfig]the saved config file is %s\n",m_achFileName);
		return FALSE;
	}
	
	if(g_bUmsShowConfig_info)
		msgprint("Beginning save data to file ...\n");

	SaveDataToCfgFile(m_achFileName,m_tALLConfigDataBak);

	if(g_bUmsShowConfig_info)
		msgprint("the data is saved to file \n");

#ifndef _LINUX_
	return TRUE;
#endif

#ifdef _LINUX_CONFIG_DEBUG_
	return TRUE;
#endif
	{
		return WriteFileToRawDisk();
 	}
	return TRUE;
}

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
BOOL CPersistCfg::WriteFileToRawDisk()
{
	FILE* pfFile = fopen(m_achFileName,"rb");
	if(NULL == pfFile)
	{
		msgprint("[MtConfig] open cfg file %s error",m_achFileName);
		return FALSE;
	}
	fseek(pfFile, 0L, SEEK_END);
	u32  dwLen = ftell(pfFile);
	if(dwLen > m_dwDataSize)
	{
		m_pbySaveData = (u8*)realloc(m_pbySaveData,dwLen*sizeof(char));
		if(NULL == m_pbySaveData)
		{
			msgprint("[MtConfig]realloc mem faill\n");
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
		msgprint("[MtConfig]read config file faill\n");
		return FALSE;
	}
	fclose(pfFile);

	//将数据保存到USER0/USER1的分区里面
	//在T2终端里面，由于os的分区不再单独由USER0/USER1,
	//故实际上终端用了两个配置文件0mtcfg.ini和1mtcfg.ini来替换了
	if(!g_cUmsCfgDataMan.SaveData(m_pbySaveData,dwLen))
	{
		msgprint("[MtConfig]save data to rawdisk error\n");
		return FALSE;
	}
    return TRUE;	
}
