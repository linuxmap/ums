/*****************************************************************************
   模块名      : 升级服务器 
   文件名      : devmgrserviceinst.cpp
   相关文件    : devmgrserviceinst.h
   文件实现功能: 负责设备信息管理
   作者        : 刁磊
   版本        : V1.0  Copyright(C) 2012-2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2013/3/22   1.0         刁磊        创建
******************************************************************************/
#include "umsobject.h"
#include "umsxmltype.h"
#include "devmgrserviceinst.h"
#include "eventtpsys.h"
#include "eventoutupdateservice.h"
#include "devmgrinfo.h"
#include "updatemgrhandle.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif

CTpDevMgrServiceApp g_cTPDevMgrServiceApp;

u32	g_dwWdGuardTime = 0;
extern BOOL32 g_bQuitIng;
extern TDevMgrCfg g_tDevMgrCfg;

extern void ReadDevMgrServiceCfg();

BOOL32 StartDevMgrService()
{
	g_cTPDevMgrServiceApp.CreateApp("CTpDevMgrService",AID_UPDATESERVER_APP, 100);
	
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( MAKEIID( AID_UPDATESERVER_APP, 1 ) );
	
	return TRUE;
}

void StopDevMgrService()
{
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( MAKEIID( AID_UPDATESERVER_APP, 1 ) );
	
	return ;
}

CTpDevMgrService::CTpDevMgrService()
{
	m_wLogModuleId = Ums_Mdl_UpdateSer;
	m_dwListenNode = 0;
}

CTpDevMgrService::~CTpDevMgrService()
{
	m_wLogModuleId = 0;
	m_dwListenNode = 0;
}

BOOL32 CTpDevMgrService::ObjectInit( u32 wParam, u32 lParam )
{
	SetLogTitle("CTpDevMgrService");

//看门狗初始化
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	s8 byRet = BrdSetSysRunSuccess();
	BOOL32 bRet = FALSE;
	if ( OK == SysOpenWdGuard(UMS_OpenWdGuard_Param) )
	{
		bRet = TRUE;
		g_dwWdGuardTime = UMS_WdGuardNotice_TIME * 1000 / 2;
		if( g_dwWdGuardTime > 0 )
		{
			SetTimer( EVTP_TIMER_WatchdogNotify, g_dwWdGuardTime );
		}
	}
	else
	{
		g_dwWdGuardTime = 0;
	}	
	printf("[SysOpenWdGuard],bRet: %d,  dwNoticeTimeout: %d \n", bRet, UMS_WdGuardNotice_TIME );
#endif

//业务初始化

	m_pcDevInfoMgr = new CDevInfoMgr;
	if ( NULL == m_pcDevInfoMgr )
	{
		msgprint("m_pcDevInfoMgr new fail!\n");
		return FALSE;
	}
	m_pcDevInfoMgr->Create(MAX_DEV_LOGIN_NUM);

	m__pcUpdateMgr = new CUpdateMgr(this);
	if ( NULL == m__pcUpdateMgr )
	{
		msgprint("m__pcUpdateMgr new fail!\n");
		return FALSE;
	}

	ReadDevMgrServiceCfg();

	m_dwListenNode  = OspCreateTcpNode(0, (u16)UPDATE_SERVICE_LISTION);
	if (INVALID_SOCKET == m_dwListenNode)
	{
		msgprint("OspCreateTcpNode fail!\n");
		return FALSE;
	}

	m_bInit = TRUE;
	return TRUE;
}

void CTpDevMgrService::ObjectExit()
{
	if ( NULL != m_pcDevInfoMgr )
	{
		m_pcDevInfoMgr->Destroy();

		delete m_pcDevInfoMgr;
		m_pcDevInfoMgr = NULL;
	}

	if ( NULL != m__pcUpdateMgr )
	{
		delete m__pcUpdateMgr;
		m__pcUpdateMgr = NULL;
	}

	m_dwListenNode = 0;

	m_bInit = FALSE;
	CTpObject::ObjectExit();

	g_bQuitIng = FALSE;

	return ;
}

BOOL CTpDevMgrService::PreMessageProc ( CMessage *const ptMsg )
{
	if (ptMsg->event == OSP_DISCONNECT)
	{
		OnDisConnect(ptMsg);
		return TRUE;
	}
	return FALSE;
}

void CTpDevMgrService::MessageProc( CTpMsg *const ptMsg )
{
	if ( m__pcUpdateMgr->Handler(ptMsg) )
	{
		return ;
	}

	switch(ptMsg->GetEvent())
	{
	case EVTP_TIMER_WatchdogNotify:
		{
			KillTimer( EVTP_TIMER_WatchdogNotify );				
			SetTimer( EVTP_TIMER_WatchdogNotify, g_dwWdGuardTime );
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
			SysNoticeWdGuard();
#endif
		}
        break;
	default:
		{
			MdlError(Ums_Mdl_UpdateSer, ("CTpDevMgrService::MessageProc, >>:%d, unfind this Event!\n", ptMsg->GetEvent()));
		}
		break;
	}
}

void CTpDevMgrService::InstanceDump( u32 wParam )
{
	switch(wParam)
	{
	case devmgr_service_dump_reload:
		m__pcUpdateMgr->ReloadLocalCfg();
		break;
	case devmgr_service_dump_show_devlist:
		m_pcDevInfoMgr->ShowDevInfo();
		break;
	case devmgr_service_dump_show_localinfo:
		ShowCfg();
		break;
	default:
		break;
	}
	return ;
}

void CTpDevMgrService::OnDisConnect(CMessage *const ptMsg)
{
	u32 dwNode = *(u32*)ptMsg->content;

	//handle
	if( NULL != m__pcUpdateMgr )
	{
		m__pcUpdateMgr->OnDisConnect(ptMsg);
	}

	m_pcDevInfoMgr->DeleteDev(dwNode);

	return ;
}

void CTpDevMgrService::NotifyMsgToDev(u32 dwNode, u32 dwInstIID, u16 wEvent, void* pBuf, u16 wSize )
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if (NULL != pBuf)
	{
		cMsg.SetBody(pBuf, wSize);
	}
	cMsg.Post(dwInstIID, dwNode, MAKEIID(AID_UPDATESERVER_APP, 1));
}

void CTpDevMgrService::ShowCfg()
{
	msgprintnotime("DevMgrService Cfg --->FtpIp:"TPIPFORMAT" \n", Tpu32ToIP(g_tDevMgrCfg.m_dwLocalSerIP));

	msgprintnotime("UpdateCfg Num:%d\n", g_tDevMgrCfg.m_tUpdateCfg.m_wDevCfgNum);
	for ( u16 wIndex = 0; wIndex < g_tDevMgrCfg.m_tUpdateCfg.m_wDevCfgNum; wIndex ++ )
	{
		msgprintnotime(" Index:%d DevType:%d UpdateType:%d Ver:%s FileName:%s \n", 
						wIndex, 
						g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_emDevType, 
						g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_emTPUpdateType, 
						g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_acDevVer, 
						g_tDevMgrCfg.m_tUpdateCfg.m_atDevCfg[wIndex].m_achFileName);
	}

	return ;
}
