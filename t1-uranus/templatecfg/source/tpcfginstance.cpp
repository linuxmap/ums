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
	//	���forkʧ���ˣ�����waitpid���س���EINTR֮��Ĵ���system���� -1��
	// execlִ��ʧ�ܣ��䷵��ֵ��ͬshellִ����"exit(127)" һ����
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
	strcat(achCommandBuf, UmsGetFileName(emUmsTpDownLoadFile)); //���ļ����
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
	{//С��12s �򷵻ط�����æ
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
  �� �� ���� OnSaveFileData
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
  �� �� ���� OnSaveFileImmediately
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
			{//����ģ����Ҫ����ʱ�����̱߳�ռ�úܾã���������Ӧ
				//�˴����� һ��ֻ����10��ģ�� ���ռ��2s Ȼ�����2s���������
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

	//�����ݱ��浽USER0/USER1�ķ�������
	//��T2�ն����棬����os�ķ������ٵ�����USER0/USER1,
	//��ʵ�����ն��������������ļ�0mtcfg.ini��1mtcfg.ini���滻��


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
		//LINUX��д��������
		return WriteFileToRawDisk(TP_INVALID_INDEX);
	}

}
