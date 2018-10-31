/*****************************************************************************
   ģ����      : ���������� 
   �ļ���      : devmgrserviceinst.h
   ����ļ�    : devmgrserviceinst.cpp
   �ļ�ʵ�ֹ���: �����豸��Ϣ����
   ����        : ����
   �汾        : V1.0  Copyright(C) 2012-2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2013/3/22   1.0         ����        ����
******************************************************************************/

#ifndef _h_devmgrserviceinst_h__
#define _h_devmgrserviceinst_h__

#include "osp.h"
#include "kdvdef.h"
#include "tplog.h"
#include "tpobject.h"
#include "tpsys.h"
#include "devmgrinfo.h"
#include "updatemgrhandle.h"

BOOL32 StartDevMgrService();
void StopDevMgrService();

enum tp_update_service_dump
{
	devmgr_service_dump_reload,
	devmgr_service_dump_show_devlist,
	devmgr_service_dump_show_localinfo,
};

typedef struct tagTTDevCfg
{
	u32					m_dwLocalSerIP;
	TDevUpdateCfgArray	m_tUpdateCfg;
	
	tagTTDevCfg()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTDevCfg));
	}
}TDevMgrCfg;


class CTpDevMgrService :  public CTpObject
{
public:
    CTpDevMgrService();
	~CTpDevMgrService();

protected:
	BOOL PreMessageProc ( CMessage *const ptMsg );
	void MessageProc(CTpMsg *const ptMsg);

	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit();
	void InstanceDump(u32 wParam);
	
	void OnDisConnect(CMessage *const ptMsg);

	void ShowCfg();
public:
	CDevInfoMgr* GetDevMgr() { return m_pcDevInfoMgr; }

	void NotifyMsgToDev(u32 dwNode, u32 dwInstIID, u16 wEvent, void* pBuf = NULL, u16 wSize = 0);
private:
	u32				m_dwListenNode;
	CDevInfoMgr*	m_pcDevInfoMgr;

	CUpdateMgr*		m__pcUpdateMgr;
};

typedef zTemplate<CTpDevMgrService, 1> CTpDevMgrServiceApp;

#endif // _h_devmgrserviceinst_h__

