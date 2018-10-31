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

#ifndef _CFGDATAMAN_HEADER_
#define _CFGDATAMAN_HEADER_

#include "osp.h"
#include "kdvsys.h"
#include "cfgdata.h"
class CPersistCfg : public CInstance
{
public:
	CPersistCfg();
	virtual ~CPersistCfg();
	
	virtual void InstanceEntry( CMessage* const pcMsg );
	void InstanceDump( u32 param ){};
	void InstanceExit(){};
protected:
	void OnInitPersist(u8* buf,u16 wLen);
	void OnUpdateData(u8* buf ,u16 wLen);
	void OnSaveFileData(u8* buf,u16 wLen);
	void OnSaveFileImmediately(u8* buf,u16 wLen);
    void OnSaveMtbFileData(u8* buf, u16 wlen); // add by wangliang for batchcfg 2007/01/09
protected:
	BOOL PersistFileData();
	BOOL WriteFileToRawDisk();
private:
	u8*  m_pbySaveData;
    u32  m_dwDataSize;
	BOOL m_bNeedSaveCfgData;
	s8   m_achFileName[256];
	TALLConfigData m_tALLConfigDataBak;
};

typedef zTemplate<CPersistCfg> CCfgDataApp;

#endif


