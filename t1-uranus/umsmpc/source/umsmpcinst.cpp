#include "umsmpcinst.h"
#include "tpsys.h"
#include "umsobject.h"
#include "mpccfg.h"
#include "umscommonstruct.h"
#include "eventoutumseqp.h"
#include "innereventumsmpc.h"
#include "umsmpcmain.h"
#include "eventtpsys.h"
#include "umsapi.h"
#include "eventoutumscommonbrd.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif

extern TTPTime g_tSetTime;
CTpUmsMpcApp g_cTPUmsMpcApp;
extern u32 g_dwUmsNode;
extern BOOL32 g_bCreatApp;

BOOL StartMpcServer()
{
	msgprint("StartMpcServer g_bCreateApp:%d\n", g_bCreatApp);
	if (g_bCreatApp)
	{
		g_cTPUmsMpcApp.CreateApp("MpcApp",AID_UMSMPC_APP, 100);
		g_bCreatApp = FALSE;
	}

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( UMS_MPC_APP_INST );

	return TRUE;
}


void StopMpcServer()
{
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( UMS_MPC_APP_INST );

	return ;
}


CTpMpcInst::CTpMpcInst()
{
	m_wLogModuleId = Ums_Mdl_Mpc;
	m_bMaster = FALSE;
	m_bRegRtn = FALSE;
}

CTpMpcInst::~CTpMpcInst()
{

}

BOOL32 CTpMpcInst::ObjectInit( u32 wParam, u32 lParam )
{
	m_wMdlIndex = TP_INVALID_INDEX;

	msgprint("CTpMpcInst::ObjectInit\n");
	SetLogTitle("CTpMpcInst");
	
	m_bInit = TRUE;
	m_dwUmsNode = g_dwUmsNode;
	
	OnConnectToUms();

	return TRUE;
}

void CTpMpcInst::ObjectExit()
{
	if (INVALID_NODE != m_dwUmsNode)
	{
		OspDisconnectTcpNode(m_dwUmsNode);
	}

	m_wMdlIndex = TP_INVALID_INDEX;

	CUmsObject::ObjectExit();
	return ;
}


void CTpMpcInst::MessageProc( CTpMsg *const ptMsg )
{
	ObjHint(("CTpMpcInst::MessageProc ConfID:%d, event:%d->%s\n", GetInsID(), ptMsg->GetEvent(), 
		GetEventNamebyID(ptMsg->GetEvent())));

	switch(ptMsg->GetEvent())
	{
	case ev_MpcConnectToUms_Time:
		OnConnectToUms();
		break;
	case EVTP_TIMER_WatchdogNotify:
		{
			KillTimer( EVTP_TIMER_WatchdogNotify );				
			SetTimer( EVTP_TIMER_WatchdogNotify, m_dwWdGuardTime );
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
			SysNoticeWdGuard();
#endif
		}
        break;
	case ev_MpcInitCfg_ACK:
		OnRegSuccess(ptMsg);
		break;
	case ev_MpcInitCfg_NACK:
		{
			OspDisconnectTcpNode(m_dwUmsNode);
			m_dwUmsNode = INVALID_NODE;
			KillTimer(ev_MpcConnectToUms_Time);
			SetTimer(ev_MpcConnectToUms_Time, TP_INTERVAL_TIME_ONE_SECOND);
		}
		break;
	case ev_MpcSetTime_Cmd:
		{
			OnSetMpcTime(ptMsg);
		}
		break;
	case ev_MpcIsMaster_Ntf:
		{
			OnIsMasterMpc(ptMsg);
		}
		break;
	case OSP_DISCONNECT:
		{
			OnDisConnect(ptMsg);
		}
		break;
	case ev_TPBrdReboot_Cmd:
		{
			OnReboot(ptMsg);
		}
		break;
	default:
		{
			MdlHint(Ums_Mdl_Mpc, ("CTpMpcInst::MessageProc, >>:%d, unfind this Event!\n", ptMsg->GetEvent()));
		}
		break;
	}
}


API void reboot();
void CTpMpcInst::OnDisConnect( CTpMsg *const ptMsg )
{
	reboot();
	return;

	m_wMdlIndex = TP_INVALID_INDEX;
	m_bMaster = FALSE;
	m_bRegRtn = FALSE;
	g_dwUmsNode = INVALID_NODE;
//点M/S灯
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	u8 byState = BrdMPCQueryLocalMSState();
	MdlHint(Ums_Mdl_Mpc, ("[OnDisConnect] m_bMaster:%d, BrdMPCQueryLocalMSState:%d.\n", m_bMaster, byState));
	if (!m_bMaster)
	{
		if (byState == BRD_MPC_RUN_MASTER)
		{//当前状态为主板,设置成为备板
			if (OK == BrdMPCSetLocalMSState(BRD_MPC_RUN_SLAVE))
			{
				MdlHint(Ums_Mdl_Mpc, ("OnDisConnect set local MS state BRD_MPC_RUN_SLAVE success.\n"));
			}
			else
			{
				MdlHint(Ums_Mdl_Mpc, ("OnDisConnect set local MS state BRD_MPC_RUN_SLAVE error.\n"));
			}
		}
	}
#endif
	StopMpcServer();
}

void CTpMpcInst::OnRegSuccess( CTpMsg *const ptMsg)
{
	BOOL32 bRet = FALSE;
	TModelProp tMdl;
	TP_SAFE_CAST(tMdl, ptMsg->GetBody());
	m_wMdlIndex = tMdl.m_wEqpType;
	m_bRegRtn = TRUE;

	MdlHint(Ums_Mdl_Mpc, ("CTpMpcInst::OnRegSuccess, bRet:%d, MdlIndx:%d \n", bRet, m_wMdlIndex));

	return ;
}


void CTpMpcInst::OnConnectToUms()
{
	MdlHint(Ums_Mdl_Mpc, ("ConnectToUms retry!\n"));
	
	KillTimer(ev_MpcConnectToUms_Time);
	if (INVALID_NODE != m_dwUmsNode)
	{
		return;
	}
	
	m_dwUmsNode = ::OspConnectTcpNode(GetUmsListenIp(), GetUmsListenPort());

	g_dwUmsNode = m_dwUmsNode;
	
	if (INVALID_NODE == m_dwUmsNode)
	{
		SetTimer(ev_MpcConnectToUms_Time, TP_INTERVAL_TIME_ONE_SECOND);
	}
	else
	{
		::OspNodeDiscCBRegQ(g_dwUmsNode, GetAppID(), GetInsID());
		
		TModelProp tMdl;
		tMdl.m_dwEqpIP = GetLocalIP();
		tMdl.m_wEqpType = em_mpc_mdl;
		strncpy(tMdl.m_achAlias, GetMpcAlias(),sizeof(tMdl.m_achAlias));
		tMdl.m_wVersion = GetMpcVersion();
		
		TTPTime tSysTime;
		TPGetSysTime(tSysTime);

		OspPrintf(TRUE, FALSE, "ConnectToUms. IP:%d!\n", tMdl.m_dwEqpIP);

		u8 abyBuf[sizeof(TModelProp)+2*sizeof(TTPTime)];
		memcpy(abyBuf, &tMdl, sizeof(tMdl));
		memcpy(abyBuf+sizeof(tMdl), &g_tSetTime, sizeof(g_tSetTime));
		memcpy(abyBuf+sizeof(tMdl)+sizeof(TTPTime), &tSysTime, sizeof(tSysTime));

		CTpMsg cMsg;
		cMsg.SetEvent(ev_MpcInitCfg_Req);
		cMsg.SetBody(abyBuf, sizeof(TModelProp)+2*sizeof(TTPTime));
		cMsg.Post( UMS_EQP_APP_INST, g_dwUmsNode, UMS_MPC_APP_INST);
	}
}

void CTpMpcInst::OnSetMpcTime(CTpMsg *const ptMsg)
{
	TTPTime tSetTime;
	TTPTime tSysTime;

	TP_SAFE_CAST(tSetTime, ptMsg->GetBody());
	TP_SAFE_CAST(tSysTime, ptMsg->GetBody() + sizeof(TTPTime));

	MdlHint(Ums_Mdl_Mpc, ("[OnSetMpcTime] SetTime %d-%d-%d %d:%d:%d SysTime %d-%d-%d %d:%d:%d\n"
		, tSetTime.m_wYear, tSetTime.m_byMonth, tSetTime.m_byMDay, tSetTime.m_byHour, tSetTime.m_byMinute, tSetTime.m_bySecond
		, tSysTime.m_wYear, tSysTime.m_byMonth, tSysTime.m_byMDay, tSysTime.m_byHour, tSysTime.m_byMinute, tSysTime.m_bySecond));

	g_tSetTime = tSetTime;

	WriteSetTime();

	TPSetSysTime(tSysTime);
}

void CTpMpcInst::OnIsMasterMpc(CTpMsg *const ptMsg)
{
	TP_SAFE_CAST(m_bMaster, ptMsg->GetBody());
	
	msgprint("[OnIsMasterMpc] g_bMaster %d\n", m_bMaster);

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	u8 byState = BrdMPCQueryLocalMSState();
	msgprint("[OnIsMasterMpc] m_bMaster:%d, BrdMPCQueryLocalMSState:%d.\n", m_bMaster, byState);
	if (m_bMaster)
	{
		if (BRD_MPC_RUN_SLAVE == byState)
		{//查询当前为备板,设置成为主板
			if (OK == BrdMPCSetLocalMSState(BRD_MPC_RUN_MASTER))
			{
				MdlHint(Ums_Mdl_Mpc, ("BrdMPCSetLocalMSState BRD_MPC_RUN_MASTER success.\n"));
			}
			else
			{
				MdlHint(Ums_Mdl_Mpc, ("BrdMPCSetLocalMSState BRD_MPC_RUN_MASTER error.\n"));
			}
		}	
	}
	else
	{
		if (BRD_MPC_RUN_MASTER == byState)
		{//查询当前为主板 设置为备板
			if (OK == BrdMPCSetLocalMSState(BRD_MPC_RUN_SLAVE))
			{
				MdlHint(Ums_Mdl_Mpc, ("BrdMPCSetLocalMSState BRD_MPC_RUN_SLAVE success.\n"));
			}
			else
			{
				MdlHint(Ums_Mdl_Mpc, ("BrdMPCSetLocalMSState BRD_MPC_RUN_SLAVE error.\n"))
			}
		}
	}
#endif
}

void CTpMpcInst::OnReboot(CTpMsg *const ptMsg)
{
	system("reboot");
}

enum tp_ums_mpc_dump
{
	dump_show_mpc
};


API void showmpc(  )
{
	OspInstDump(AID_UMSMPC_APP, 1, dump_show_mpc);
}
API void showms()
{
	u8 byState = 0;//win默认为主板
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	 byState= BrdMPCQueryLocalMSState();
#endif
	msgprintnotime("0:BRD_MPC_RUN_MASTER(主板)\n1:BRD_MPC_RUN_SLAVE(备板)\nCurrent M/S State:%d.\n", byState);
}

void CTpMpcInst::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_mpc:
		ShowMpc();
		break;
	default:
		break;
	}
	return ;
}

void CTpMpcInst::ShowMpc()
{
	//打印所有混音信息
	msgprint("****Mpc INFO****\n");
	msgprint("Regist Result:%d\n", m_bRegRtn);
	msgprint("Index:%d, Master:%d\n", m_wMdlIndex, m_bMaster);
	msgprint("****End****\n");
	
	return ;
}


