 /*****************************************************************************
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
   
******************************************************************************/
#ifndef _TPCFGINSTANCE_
#define _TPCFGINSTANCE_

#include "osp.h"
#include "kdvsys.h"
#include "tpcfgdata.h"
class CTpPersistCfg : public CInstance
{
public:
	CTpPersistCfg();
	virtual ~CTpPersistCfg();
	
	virtual void InstanceEntry( CMessage* const pcMsg );
	void InstanceDump( u32 param ){};
	void InstanceExit(){};
protected:
	void OnInitPersist(u8* buf,u16 wLen);
	void OnUpdateData(u8* buf ,u16 wLen);
	void OnSaveFileData(u8* buf,u16 wLen);
	void OnSaveFileImmediately(u8* buf,u16 wLen);
	void OnSaveValidNum(u8* buf,u16 wLen);
	void OnUpLoadFile(u8* pBuf,u16 wLen);
	void OnDownLoadFile(u8* pBuf,u16 wLen);

protected:
	BOOL PersistFileData(u16 wIndex);
	BOOL WriteFileToRawDisk(u16 wIndex);

	BOOL PersistControlData();
private:
	u8*  m_pbySaveData;
    u32  m_dwDataSize;
	BOOL m_abNeedSaveCfgData[TP_CONFTEMPLATE_MAXNUM];
	BOOL m_bNeedSaveValidData;
	s8   m_achFileName[256];
	TConfTemplateLocal m_tALLTpConfigDataBak[TP_CONFTEMPLATE_MAXNUM];
	TIndexALLTpConfigData m_tIndexALLTpConfigData;
	TControlData m_tControlDataBak;

	time_t		m_dwTime;
};

typedef zTemplate<CTpPersistCfg> CTpCfgDataApp;

#endif


