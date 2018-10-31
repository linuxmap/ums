/*****************************************************************************
   模块名      : 升级服务器 
   文件名      : devmgrinfo.cpp
   相关文件    : devmgrinfo.h
   文件实现功能: 负责升级服务器相关业务
   作者        : 刁磊
   版本        : V1.0  Copyright(C) 2012-2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2013/3/25   1.0         刁磊        创建
******************************************************************************/
#include "devmgrinfo.h"
#include "tplog.h"
#include "osp.h"
#include "umsobject.h"
#include "umsxmltype.h"

CDevInfoMgr::CDevInfoMgr()
{
	
}

CDevInfoMgr::~CDevInfoMgr()
{
	
}

void CDevInfoMgr::ShowDevInfo()
{
	msgprintnotime("DevInfo:  devNum:%d\n", CURRENT_DEV_NUM(m_cDevList));

	for (CDevListItor Itor = m_cDevList.Head(); Itor != NULL; Itor = m_cDevList.Next(Itor))
	{
		if ( 0 == Itor->m_dwNode )
		{
			continue;
		}

		if ( Itor->m_emDevType == emDevInvalid )
		{
			continue;
		}

		msgprintnotime("LoginIp:"TPIPFORMAT" DevType:%d->%s\n", 
			Tpu32ToIP(OspNodeIpGet(Itor->m_dwNode)), TpEnumIdString(EmTPDevRegUpdateSer, Itor->m_emDevType));

		for ( u16 wDevIndx = 0; wDevIndx < MAX_DEVICE_NUM; wDevIndx ++ )
		{
			if ( Itor->m_atLocalVerInfo[wDevIndx].m_emDevRegUpdateSer == emDevInvalid )
			{
				continue;
			}

			msgprintnotime("	DevType:%d->%s, Ver:%s\n", 
				TpEnumIdString(EmTPDevRegUpdateSer, Itor->m_atLocalVerInfo[wDevIndx].m_emDevRegUpdateSer), 
				Itor->m_atLocalVerInfo[wDevIndx].m_achDevVersion);
		}
	}
}

BOOL32 CDevInfoMgr::InsertDev( TDevInfo& tDev )
{
	CDevListItor itDevList = FindDevByNode( tDev.m_dwNode );
	if ( NULL == itDevList )
	{
		itDevList = m_cDevList.AllocNode();

		if ( NULL == itDevList )
		{
			MdlError(Ums_Mdl_UpdateSer, ("CDevInfoMgr::InsertDev. AllocNode Fail!\n"));
			return FALSE;
		}
	}

	itDevList->m_dwNode = tDev.m_dwNode;
	itDevList->m_dwInstIID = tDev.m_dwInstIID;
	itDevList->m_emDevType = tDev.m_emDevType;
	memcpy(itDevList->m_atLocalVerInfo, tDev.m_atLocalVerInfo, sizeof(tDev.m_atLocalVerInfo));

	return TRUE;
}

void CDevInfoMgr::DeleteDev( u32 dwNode )
{
	CDevListItor Itor = NULL;
	for (Itor = m_cDevList.Head(); Itor != NULL; Itor = m_cDevList.Next(Itor))
	{
		if ( Itor->m_dwNode == dwNode )
		{
			m_cDevList.FreeBuff(Itor);
			break;
		}
	}

	MdlHint(Ums_Mdl_UpdateSer, ("CDevInfoMgr::DeleteDev. DelSuccess:%d, Node:%d, TotalNum:%d\n", 
									Itor != NULL ? 1 : 0, dwNode, CURRENT_DEV_NUM(m_cDevList)));

	return ;
}

CDevListItor CDevInfoMgr::FindDevByNode( u32 dwNode )
{
	CDevListItor Itor = NULL;
	for (Itor = m_cDevList.Head(); Itor != NULL; Itor = m_cDevList.Next(Itor))
	{
		if ( Itor->m_dwNode == dwNode )
		{
			return Itor;
		}
	}
	return NULL;
}

