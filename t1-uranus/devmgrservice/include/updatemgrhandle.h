/*****************************************************************************
   ģ����      : ���������� 
   �ļ���      : updatemgrhandle.h
   ����ļ�    : updatemgrhandle.cpp
   �ļ�ʵ�ֹ���: �����������������ҵ��
   ����        : ����
   �汾        : V1.0  Copyright(C) 2012-2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2013/3/31   1.0         ����        ����
******************************************************************************/
#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "tpobject.h"
#include "tpsys.h"
#include "tphandle.h"
#include "devmgrserviceinst.h"

#ifndef _h_updatemgrhandle_h__
#define _h_updatemgrhandle_h__

#define DEV_CFG_MAX_CFG 10    //�������õ������豸��Ŀ

typedef struct tagTTDevUpdateCfg
{
	BOOL32				m_bUsed;
	EmTPDevRegUpdateSer m_emDevType;//�����豸����
	EmTPUpdateType		m_emTPUpdateType;//����ѡ��
	s8					m_acDevVer[MAX_DEVICEVER_LEN];
	s8					m_achFileName[TP_MAX_FILESRV_FILENAME_LEN];//�ļ��� ����·��
	
	tagTTDevUpdateCfg()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTDevUpdateCfg));
		m_bUsed = FALSE;
	}
}TDevUpdateCfg;

typedef struct tagTTDevUpdateCfgArray
{
	u16			  m_wDevCfgNum;
	TDevUpdateCfg m_atDevCfg[DEV_CFG_MAX_CFG];

	tagTTDevUpdateCfgArray()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTDevUpdateCfgArray));
	}
}TDevUpdateCfgArray;

class CTpDevMgrService;
class CUpdateMgr  : public CTpHandler
{
public:
	CUpdateMgr(CTpDevMgrService* pcInst);
	~CUpdateMgr();
	
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	void Show();

	void OnDisConnect(CMessage *const ptMsg);

public:
	void OnDevLoginReq(CTpMsg *const ptMsg);
	void OnDevUpdateReq(CTpMsg *const ptMsg);
	
	void ReloadLocalCfg();
protected:
	void SetDevVerInfo(TTPDev& tDev, EmTPDevRegUpdateSer emDevType);
	void SetFtpSerInfo(TTPFTPFileInfo& tFtpInfo);

private:
	CTpDevMgrService* Inst()	{ return (CTpDevMgrService*)m_pcInstance; }
	void Clear();
};

#endif //_h_updatemgrhandle_h__
