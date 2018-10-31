/*****************************************************************************
   模块名      : 升级服务器 
   文件名      : updatemgrhandle.cpp
   相关文件    : updatemgrhandle.h
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
#include "umsobject.h"
#include "tpsys.h"
#include "tphandle.h"
#include "devmgrserviceinst.h"
#include "updatemgrhandle.h"
#include "devmgrinfo.h"
#include "umsxmltype.h"
#include "eventoutupdateservice.h"

extern TDevMgrCfg g_tDevMgrCfg;

extern void ReadUpdateInfoCfg();

CUpdateMgr::CUpdateMgr( CTpDevMgrService* pcInst )
:CTpHandler(pcInst)
{
	Clear();
}

CUpdateMgr::~CUpdateMgr()
{
	
}

void CUpdateMgr::Clear()
{
	
}

BOOL32 CUpdateMgr::Handler( CTpMsg *const ptMsg )
{
	switch(ptMsg->GetEvent())
	{
	case ev_CnLogin_UpdateSer_Req:
		OnDevLoginReq(ptMsg);
		break;
	case ev_UpdateSystem_Req:
		OnDevUpdateReq(ptMsg);
		break;
	case ev_ReloadCfg_Req:
		ReloadLocalCfg();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void CUpdateMgr::OnDisConnect( CMessage *const ptMsg )
{
	//
}

void CUpdateMgr::ReloadLocalCfg()
{
	MdlHint(Ums_Mdl_UpdateSer, ("CUpdateMgr::OnReloadLocalCfg! CurrentDevNum:%d\n", Inst()->GetDevMgr()->GetDevInfoNum()));

	ReadUpdateInfoCfg();
	
	TTPDevVerInfo tVerInfo;

	for (CDevListItor Itor = Inst()->GetDevMgr()->GetDevList()->Head(); Itor != NULL
		;Itor = Inst()->GetDevMgr()->GetDevList()->Next(Itor))
	{
		if ( 0 == Itor->m_dwNode )
		{
			continue;
		}
		
		memset(&tVerInfo, 0, sizeof(tVerInfo));

		BOOL32 bIsExist = FALSE;
		u16 wDevIndx = 0;
		for ( u16 wIndex = 0; wIndex < MAX_DEVICE_NUM; wIndex ++ )
		{
			bIsExist = FALSE;
			if ( Itor->m_atLocalVerInfo[wIndex].m_emDevRegUpdateSer == emDevInvalid )
			{
				continue;
			}

			for ( u16 wI = 0; wI <= wDevIndx; wI ++ )
			{
				if ( tVerInfo.m_atDev[wI].m_emDevRegUpdateSer == Itor->m_atLocalVerInfo[wIndex].m_emDevRegUpdateSer )
				{
					bIsExist = TRUE;
					break;
				}
			}

			if( !bIsExist && wDevIndx < MAX_REG_DEVICE_NUM )
			{
				SetDevVerInfo(tVerInfo.m_atDev[wDevIndx++], Itor->m_atLocalVerInfo[wIndex].m_emDevRegUpdateSer);
			}
		}
		
		Inst()->NotifyMsgToDev(Itor->m_dwNode, Itor->m_dwInstIID, ev_UpdateSystem_Nty, &tVerInfo, sizeof(tVerInfo));

		MdlHint(Ums_Mdl_UpdateSer, ("CUpdateMgr::ReloadLocalCfg. Node:%d, DevNum:%d\n", Itor->m_dwNode, wDevIndx));
	}
	return ;
}

void CUpdateMgr::OnDevLoginReq( CTpMsg *const ptMsg )
{
	TTPLocalDevVerInfo tLocalInfo;
	TP_SAFE_CAST(tLocalInfo, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_UpdateSer, ("CUpdateMgr::OnDevLoginReq. IP:"TPIPFORMAT", DevType:(%d->%s)\n", 
		Tpu32ToIP(OspNodeIpGet(ptMsg->GetSrcNode())), TpEnumIdString(EmTPDevRegUpdateSer, tLocalInfo.m_emDevRegUpdateSer)));
	
	TDevInfo tDevInfo;
	tDevInfo.m_dwNode = ptMsg->GetSrcNode();
	tDevInfo.m_dwInstIID = ptMsg->GetSrcIId();
	tDevInfo.m_emDevType = tLocalInfo.m_emDevRegUpdateSer;
	memcpy(tDevInfo.m_atLocalVerInfo, tLocalInfo.m_atLocalVerInfo, sizeof(tDevInfo.m_atLocalVerInfo));
	
	BOOL32 bRet = Inst()->GetDevMgr()->InsertDev(tDevInfo);
	
	EmTPCnLoginUpdateRet emRet = emTPCnLoginUpdateSuccess;
	if ( !bRet )
	{
		emRet = emTPCnLoginUpdateFail;
	}
	else
	{
		//断链检测
		OspNodeDiscCBReg(ptMsg->GetSrcNode(), Inst()->GetAppID(), Inst()->GetInsID());
	}
	
	Inst()->NotifyMsgToDev(ptMsg->GetSrcNode(), ptMsg->GetSrcIId(), ev_CnLogin_UpdateSer_Rsp, &emRet, sizeof(emRet));
	
	return ;
}

void CUpdateMgr::OnDevUpdateReq( CTpMsg *const ptMsg )
{
	TTPLocalDevVerInfo tLocalInfo;
	TP_SAFE_CAST(tLocalInfo, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_UpdateSer, ("CUpdateMgr::OnDevUpdateReq. IP:"TPIPFORMAT", DevType:(%d->%s)\n", 
			Tpu32ToIP(OspNodeIpGet(ptMsg->GetSrcNode())), TpEnumIdString(EmTPDevRegUpdateSer, tLocalInfo.m_emDevRegUpdateSer)));
	
	TTPDevVerInfo tVerInfo;
	memset(&tVerInfo, 0, sizeof(tVerInfo));

	u16 wDevIndx = 0;
	for ( u16 wIndex = 0; wIndex < MAX_DEVICE_NUM; wIndex ++ )
	{
		if ( tLocalInfo.m_atLocalVerInfo[wIndex].m_emDevRegUpdateSer == emDevInvalid )
		{
			continue;
		}

		if( wDevIndx < MAX_REG_DEVICE_NUM )
		{
			SetDevVerInfo(tVerInfo.m_atDev[wDevIndx++], tLocalInfo.m_atLocalVerInfo[wIndex].m_emDevRegUpdateSer);
		}
	}
	
	Inst()->NotifyMsgToDev(ptMsg->GetSrcNode(), ptMsg->GetSrcIId(), ev_UpdateSystem_Rsp, &tVerInfo, sizeof(tVerInfo));
	
	return ;
}

void CUpdateMgr::SetDevVerInfo( TTPDev& tDev, EmTPDevRegUpdateSer emDevType )
{
	//根据类型 设置升级信息
	u16 wIndex = 0;
	for( wIndex = 0; wIndex < g_tDevMgrCfg.m_tUpdateCfg.m_wDevCfgNum; wIndex ++ )
	{
		if ( !g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_bUsed )
		{
			continue;
		}

		if ( g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_emDevType == emDevType )
		{
			strncpy(&tDev.m_achDevVersion[0], 
				&g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_acDevVer[0], sizeof(s8)*MAX_DEVICEVER_LEN);
			tDev.m_achDevVersion[MAX_DEVICEVER_LEN-1] = '\0';

			tDev.m_emTPUpdateType = g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_emTPUpdateType;
			
			strncpy(&tDev.m_tDevVerFileInfo.achFilePath[0], 
				&g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_achFileName[0], sizeof(s8)*TP_MAX_FILESRV_FILENAME_LEN);
			tDev.m_tDevVerFileInfo.achFilePath[TP_MAX_FILESRV_FILENAME_LEN-1] = '\0';

			tDev.m_tDevVerFileInfo.byFilePathLen = strlen(g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_achFileName);
			
			SetFtpSerInfo(tDev.m_tDevVerFileInfo);

			tDev.m_emDevRegUpdateSer = emDevType;

			break;
		}
	}

	if ( wIndex == g_tDevMgrCfg.m_tUpdateCfg.m_wDevCfgNum )
	{
		MdlHint(Ums_Mdl_UpdateSer, ("CUpdateMgr::SetDevVerInfo! not config! DevType:%d\n", emDevType));
	}
	
	return ;
}

void CUpdateMgr::SetFtpSerInfo( TTPFTPFileInfo& tFtpInfo )
{//设置ftp所需信息
	tFtpInfo.dwSerIP = g_tDevMgrCfg.m_dwLocalSerIP;
	tFtpInfo.wSerPort = 21;
	memcpy(&tFtpInfo.achUserName[0], UMS_UserName_New, strlen(UMS_UserName_New)*sizeof(s8));
	tFtpInfo.byUserNameLen = strlen(UMS_UserName_New)*sizeof(s8);
	memcpy(&tFtpInfo.achPassword[0], UMS_PassWord_New, strlen(UMS_PassWord_New)*sizeof(s8));
	tFtpInfo.byPasswordLen = strlen(UMS_PassWord_New)*sizeof(s8);
}
