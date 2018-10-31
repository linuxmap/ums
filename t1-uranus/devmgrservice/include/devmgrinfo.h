/*****************************************************************************
   模块名      : 升级服务器 
   文件名      : devmgrinfo.h
   相关文件    : devmgrinfo.cpp
   文件实现功能: 升级设备信息管理
   作者        : 刁磊
   版本        : V1.0  Copyright(C) 2012-2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2013/3/25   1.0         刁磊        创建
******************************************************************************/

#ifndef _h_devmgrinfo_h__
#define _h_devmgrinfo_h__

#include "tpsys.h"
#include "tptype.h"
#include "tpstruct.h"
#include "tplist.h"

#define MAX_DEV_LOGIN_NUM 65535

#define  CDevList CTpList<TDevInfo>
#define  CDevListItor TDevInfo*

#define CURRENT_DEV_NUM(cDevList) cDevList.GetTotalNum() - cDevList.GetFreeBlocks()

typedef struct tagTTDevInfo
{
	u32					m_dwNode;
	u32					m_dwInstIID;
	EmTPDevRegUpdateSer m_emDevType;
	TTPLocalVerInfo     m_atLocalVerInfo[MAX_DEVICE_NUM];

	tagTTDevInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTDevInfo));

		m_emDevType = emDevInvalid;
		for ( u16 wIndex = 0; wIndex < MAX_DEVICE_NUM; wIndex ++ )
		{
			m_atLocalVerInfo[wIndex].m_emDevRegUpdateSer = emDevInvalid;
		}
	}
}TDevInfo;

class CDevInfoMgr
{
public:
	CDevInfoMgr();
	~CDevInfoMgr();
public:
	void Create(u32 dwListNum) { m_cDevList.Create(dwListNum); }
	void Destroy() { m_cDevList.Destroy(); }

	BOOL32 InsertDev(TDevInfo& tDev);
	void DeleteDev(u32 dwNode);

	CDevListItor FindDevByNode(u32 dwNode);

	void ShowDevInfo();

	u32 GetDevInfoNum() { return CURRENT_DEV_NUM(m_cDevList); }
	CDevList* GetDevList() { return &m_cDevList; }
private:
	CDevList m_cDevList;
};

#endif //_h_devmgrinfo_h__