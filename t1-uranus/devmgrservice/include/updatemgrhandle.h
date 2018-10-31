/*****************************************************************************
   模块名      : 升级服务器 
   文件名      : updatemgrhandle.h
   相关文件    : updatemgrhandle.cpp
   文件实现功能: 负责升级服务器相关业务
   作者        : 刁磊
   版本        : V1.0  Copyright(C) 2012-2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2013/3/31   1.0         刁磊        创建
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

#define DEV_CFG_MAX_CFG 10    //可以配置的升级设备数目

typedef struct tagTTDevUpdateCfg
{
	BOOL32				m_bUsed;
	EmTPDevRegUpdateSer m_emDevType;//升级设备类型
	EmTPUpdateType		m_emTPUpdateType;//升级选项
	s8					m_acDevVer[MAX_DEVICEVER_LEN];
	s8					m_achFileName[TP_MAX_FILESRV_FILENAME_LEN];//文件名 包含路径
	
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
