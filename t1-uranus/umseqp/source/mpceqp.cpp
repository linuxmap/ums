#include "mpceqp.h"
#include "eventoutumseqp.h"
#include "eventoutumscfg.h"
#include "innereventumscall.h"
#include "innereventumsserver.h"
#include "innereventumsmpc.h"
#include "eqpinterface.h"
#include "umsconfigex.h"
#include "umsapi.h"
#include "eqpinst.h"

CMpcEqp::CMpcEqp( CUmsEqpInst* pInst )
: CEqpBase(pInst)
{
	m_emUsedMpc = MPC_INVALID;
}

CMpcEqp::~CMpcEqp()
{
	
}

void CMpcEqp::Handle( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	switch(wEvent)
	{
	case ev_MpcInitCfg_Req:
		OnEqpReg(ptMsg);
		break;
	case ev_UmsSetSysTime_Cmd:
		OnEqpSetTime(ptMsg);
		break;
	default:
		MdlError(Ums_Mdl_Eqp, ("CMpcEqp::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}
}

void CMpcEqp::Show()
{
	msgprintnotime("CMpcEqp Info : \n");

	msgprintnotime("  m_emUsedMpc:%d, m_tSetTime year:%d, month:%u, day:%u, hour:%u, minute:%u, second:%u.\n",
		m_emUsedMpc, m_tSetTime.m_wYear, m_tSetTime.m_byMonth, m_tSetTime.m_byMDay, 
		m_tSetTime.m_byHour, m_tSetTime.m_byMinute, m_tSetTime.m_bySecond);

	if (m_tMpc1.m_bRegsited)
	{
		msgprintnotime("  ModleIndex:0, cap:%d, Node:%d, Reged:%d, use:%d, Master:%d,  Ip:"TPIPFORMAT"\n",
			m_tMpc1.m_tRegInfo.m_dwCapSet, m_tMpc1.m_dwUserNode, 
			m_tMpc1.m_bRegsited, m_tMpc1.m_dwUsed, m_tMpc1.m_bMaster, Tpu32ToIP(m_tMpc1.m_tRegInfo.m_dwEqpIP));
	}
	
	if (m_tMpc2.m_bRegsited)
	{
		msgprintnotime("  ModleIndex:1, cap:%d, Node:%d, Reged:%d, use:%d, Master:%d,  Ip:"TPIPFORMAT"\n",
			m_tMpc2.m_tRegInfo.m_dwCapSet, m_tMpc2.m_dwUserNode, 
			m_tMpc2.m_bRegsited, m_tMpc2.m_dwUsed, m_tMpc2.m_bMaster, Tpu32ToIP(m_tMpc2.m_tRegInfo.m_dwEqpIP));
	}
	return ;
}

CMpcModle* CMpcEqp::AnotherMpc(EMMpcNum emMpc)
{
	if (MPC_ONE == emMpc)
	{
		return &m_tMpc2;
	}
	return &m_tMpc1;
}


BOOL32 CMpcEqp::OnDisConnect( u32 dwNode )
{
	EMMpcNum wMdlIndex = MPC_INVALID;
	u32 dwRegIP;
	TEqpRes tEqp;
	CHECK_EQP_SEM;

	CMpcModle* ptEqp = NULL;
	if (m_tMpc1.m_dwUserNode == dwNode && m_emUsedMpc != MPC_INVALID)
	{
		ptEqp = &m_tMpc1;
		wMdlIndex = MPC_ONE;
		if (m_tMpc2.IsIdle())
		{
			m_emUsedMpc = MPC_INVALID;
		}
		else
		{
			m_emUsedMpc = MPC_TWO;
		}
	}
	if (m_tMpc2.m_dwUserNode == dwNode && m_emUsedMpc != MPC_INVALID)
	{
		ptEqp = &m_tMpc2;
		wMdlIndex = MPC_TWO;
		if (m_tMpc1.IsIdle())
		{
			m_emUsedMpc = MPC_INVALID;
		}
		else
		{
			m_emUsedMpc = MPC_ONE;
		}
	}
	
	if (NULL == ptEqp)
	{
		return FALSE;
	}
	
	//更新外设注册状态到eqpmgr
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptEqp->m_dwUserNode, 0, FALSE);

	CMpcModle* pAnother = AnotherMpc(wMdlIndex);
	if (NULL != pAnother && !pAnother->IsIdle())
	{
		BOOL32 bIsMaster = TRUE;

		pAnother->m_bMaster = bIsMaster;
		NotifyMsgToEqp(pAnother->m_dwUserNode, pAnother->m_dwUserInst, ev_MpcIsMaster_Ntf, &bIsMaster, sizeof(bIsMaster));
	}
	else
	{//没有MPC板，要挂断会议

		BOOL32 bMpc = FALSE;
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsMpcReged_Notify);
		cMsg.SetBody(&bMpc, sizeof(bMpc));
		cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);

		//通知call,授权数清零
		u32 dwAccessNum = 0;
		cMsg.SetEvent(evtp_UmsAccessNum_Notify);
		cMsg.SetBody(&dwAccessNum, sizeof(dwAccessNum));
		cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
	}

	dwRegIP = ptEqp->m_tRegInfo.m_dwEqpIP;
	ptEqp->m_bMaster = FALSE;
	ptEqp->Clear();

	MdlHint(Ums_Mdl_Eqp, ("CMpcEqp::OnDisConnect index:%d, RegIP:"TPIPFORMAT" \n", wMdlIndex, Tpu32ToIP(dwRegIP)));	
	return TRUE;
}

void CMpcEqp::OnEqpReg( CTpMsg *const ptMsg )
{
	TModelProp tMdlProp;
	TTPTime tSetTime;
	TTPTime tSysTime;
	TP_SAFE_CAST( tMdlProp, ptMsg->GetBody());
	TP_SAFE_CAST( tSetTime, ptMsg->GetBody()+sizeof(TModelProp));
	TP_SAFE_CAST( tSysTime, ptMsg->GetBody()+sizeof(TModelProp)+sizeof(TTPTime));
	
	u32 wSrcNode = ptMsg->GetSrcNode();
	u32 wSrcInst = ptMsg->GetSrcIId();

	EMMpcNum wCurIndex = MPC_INVALID;
	CMpcModle* pcModle = NULL;
	if (m_tMpc1.IsIdle())
	{
		pcModle = &m_tMpc1;
		wCurIndex = MPC_ONE;
	}
	if (NULL == pcModle && m_tMpc2.IsIdle())
	{
		pcModle = &m_tMpc2;
		wCurIndex = MPC_TWO;
	}

	if (NULL == pcModle)
	{
		NotifyMsgToEqp(wSrcNode, wSrcInst, ev_MpcInitCfg_NACK, NULL, 0);
		MdlError(Ums_Mdl_Eqp, ("CMpcEqp::OnEqpReg No idle location! RegIP:"TPIPFORMAT"\n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));	
		return;
	}

	CHECK_EQP_SEM;

	pcModle->m_dwUserNode = wSrcNode;
	pcModle->m_dwUserInst = wSrcInst;
	pcModle->m_bRegsited = TRUE;
	memcpy(&pcModle->m_tRegInfo, &tMdlProp, sizeof(pcModle->m_tRegInfo));
	
	//对该结点注册断链检测
	OspNodeDiscCBReg( wSrcNode, AID_UMSEQP_APP, EQP_SERVER_INST);

	NotifyMsgToEqp(wSrcNode, wSrcInst, ev_MpcInitCfg_ACK, &tMdlProp, sizeof(tMdlProp));

	//更新外设注册状态到epqmgr
	u8 byEqpId = 0; //普通板子的eqpid都设置为0
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(wSrcNode, byEqpId, TRUE);

	if (tSetTime.IsValid() && m_tSetTime < tSetTime)
	{//取当前MPC板时间
		m_tSetTime = tSetTime;
		if (Ums_Run_On_Cri2 == CUmsConfigEx::GetInstance()->GetUmsRunType() && tSysTime < tSetTime)
		{// cri2重启后，时间会重置，所以这里tSysTime是一个默认时间，这里取SetTime（保存在配置文件的一个时间）同步
			NotifyMsgToService(ev_UmsSetSysTime_Cmd, &tSetTime, sizeof(TTPTime));
		}
		else
		{
			NotifyMsgToService(ev_UmsSetSysTime_Cmd, &tSysTime, sizeof(TTPTime));
		}
		//时间变动后更新到所有板子
		m_pcInst->GetEqpMgr()->UpdateSysTimeToAllBrd();
	}	
	else
	{
		//如果MPC时间和ums时间都是非法的，则取MPC系统时间同步ums
		if ( !tSetTime.IsValid() && !m_tSetTime.IsValid() )
		{
			NotifyMsgToService(ev_UmsSetSysTime_Cmd, &tSysTime, sizeof(TTPTime));
			//时间变动后更新到所有板子
			m_pcInst->GetEqpMgr()->UpdateSysTimeToAllBrd();
		} 
		else
		{
			//设置当前MPC板时间
			TPGetSysTime(tSysTime);
			
			u8 abyBuf[sizeof(TTPTime) *2];
			memcpy(abyBuf, &m_tSetTime, sizeof(TTPTime));
			memcpy(abyBuf+sizeof(TTPTime), &tSysTime, sizeof(TTPTime));
			
		    NotifyMsgToEqp(wSrcNode, wSrcInst, ev_MpcSetTime_Cmd, abyBuf, sizeof(abyBuf));	
		}
	}

	BOOL32 bIsMaster = FALSE;
	if (MPC_INVALID == m_emUsedMpc)
	{
		m_emUsedMpc = wCurIndex;
		bIsMaster = TRUE;

		BOOL32 bMpc = TRUE;
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsMpcReged_Notify);
		cMsg.SetBody(&bMpc, sizeof(bMpc));
		cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
	}
	
	pcModle->m_bMaster = bIsMaster;

	NotifyMsgToEqp(wSrcNode, wSrcInst, ev_MpcIsMaster_Ntf, &bIsMaster, sizeof(bIsMaster));
	if (bIsMaster)
	{
		NotifyMsgToService(ev_MpcIsMaster_Ntf, &bIsMaster, sizeof(bIsMaster));
	}

	MdlHint(Ums_Mdl_Eqp, ("CMpcEqp::OnEqpReg Success! MdlIP:"TPIPFORMAT", AppID:%d, InsID:%d\n"
		, Tpu32ToIP(tMdlProp.m_dwEqpIP), GETAPP(wSrcInst), GETINS(wSrcInst)));
}

void CMpcEqp::NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen)
{
	TLogUser tUser;
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tUser, sizeof(TLogUser));
	if (NULL != body)
	{
		cMsg.CatBody(body, bodyLen);
	}

	cMsg.Post(UMS_SERVICE_APP_INST);
}

void CMpcEqp::OnEqpSetTime(CTpMsg* const ptMsg)
{
	TTPTime tSetTime;
	TP_SAFE_CAST( tSetTime, ptMsg->GetBody());

	m_tSetTime = tSetTime;
	
	TTPTime tSysTime;
	TPGetSysTime(tSysTime);

	u8 abyBuf[sizeof(TTPTime) *2];
	memcpy(abyBuf, &m_tSetTime, sizeof(TTPTime));
	memcpy(abyBuf+sizeof(TTPTime), &tSysTime, sizeof(TTPTime));

	if (!m_tMpc1.IsIdle())
	{
		NotifyMsgToEqp(m_tMpc1.m_dwUserNode, m_tMpc1.m_dwUserInst, ev_MpcSetTime_Cmd, &abyBuf, sizeof(abyBuf));
	}
	if (!m_tMpc2.IsIdle())
	{
		NotifyMsgToEqp(m_tMpc2.m_dwUserNode, m_tMpc2.m_dwUserInst, ev_MpcSetTime_Cmd, &abyBuf, sizeof(abyBuf));
	}

	//时间变动后更新到所有板子
	m_pcInst->GetEqpMgr()->UpdateSysTimeToAllBrd();
}

BOOL32 CMpcEqp::AssignEqpEx( TEqpParam* ptEqpParam )
{
	if (m_tMpc1.IsIdle() && m_tMpc2.IsIdle())
	{
		return FALSE;
	}
	return TRUE;
}

BOOL32 CMpcEqp::ReleaseEqpEx( TEqpParam* ptEqpParam )
{
	return FALSE;
}
