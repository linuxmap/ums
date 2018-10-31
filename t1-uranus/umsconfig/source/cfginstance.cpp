/*******************************************************************************
  ģ����      : KDVMT MtAgent
   �ļ���      : CCfgDataManager.h
   ����ļ�    : CCfgDataManager.cpp
   �ļ�ʵ�ֹ���: KDVMT �������ͷ�ļ�
   ����        : 
   �汾        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2005/03/24  1.0         ������       ����
   2005/07/21  4.0         ��  ��       �޸ģ�ΪCCfgDataManager��ӻ�ȡ�ļ����ƺ���
                                        �޸ģ� CIMtCfg��Ϣ���ݣ��޸�InstanceEntryʵ�ַ�ʽ
										�޸ģ��ƶ�InstanceDump��ͷ�ļ���ʵ��
										�޸ģ��ƶ�InstanceExit��ͷ�ļ���ʵ��
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
	//���ò������ȼ�Ϊ THREAD_PRIORITY_LOWEST
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
  �� �� ���� OnInitPersist
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u8* buf
             u16 wLen
  �� �� ֵ�� void 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2006/4/14      1.0		    �� ��                   ����
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
  �� �� ���� OnUpdateData
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u8* buf
             u16 wLen
  �� �� ֵ�� void 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2006/4/14      1.0		    �� ��                   ����
  2007/11/20     4.0            fangtao             ���ͬ���ź�������
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
  �� �� ���� OnSaveMtbFileData
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u8* buf
             u16 wLen
  �� �� ֵ�� void 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2007/01/09      1.0		    wangliang             ����
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
  �� �� ���� PersistFileData
  ��    �ܣ� ͬ���ļ����������ļ��־û�����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� ��
  �� �� ֵ�� TRUE ����ɹ� FALSE����ʧ��
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2005/7/21      1.0		    �� ��                   ����
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
  �� �� ���� WriteFileToRawDisk
  ��    �ܣ� ���ļ�����д��rawdisk��ȥ, ʵ��Ϊ�����ݱ��浽��������
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2005/8/26      1.0		    �� ��                   ����
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

	//�����ݱ��浽USER0/USER1�ķ�������
	//��T2�ն����棬����os�ķ������ٵ�����USER0/USER1,
	//��ʵ�����ն��������������ļ�0mtcfg.ini��1mtcfg.ini���滻��
	if(!g_cUmsCfgDataMan.SaveData(m_pbySaveData,dwLen))
	{
		msgprint("[MtConfig]save data to rawdisk error\n");
		return FALSE;
	}
    return TRUE;	
}
