#include "netbufeqp.h"
#include "eventoutumseqp.h"
#include "innereventumscall.h"
#include "umsconfig.h"

CNbEqp::CNbEqp(CUmsEqpInst* pInst)
:CEqpBase(pInst)
{
}

CNbEqp::~CNbEqp()
{
	
}

void CNbEqp::Handle(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();

	switch(wEvent)
	{
	case ev_Netbuf_Req:
		OnEqpReg(ptMsg);
		break;
	case ev_NetbufInitSuccess_Ind:
		OnNbInitSuccess(ptMsg);
		break;
	default:
		MdlError(Ums_Mdl_Eqp, ("CNbEqp::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}
}


void CNbEqp::OnEqpReg(CTpMsg *const ptMsg)
{
	TModelProp tMdlProp;
	TP_SAFE_CAST( tMdlProp, ptMsg->GetBody());

	u32 wSrcNode = ptMsg->GetSrcNode();
	u32 wSrcInst = ptMsg->GetSrcIId();
	
	if (!m_tNb.IsIdle())
	{
		NotifyMsgToEqp(wSrcNode, wSrcInst, ev_Netbuf_NACK, NULL, 0);
		MdlError(Ums_Mdl_Eqp, ("CNbEqp::OnEqpReg No idle location! RegIP:"TPIPFORMAT"\n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));	
		return;
	}

	MdlHint(Ums_Mdl_Eqp, ("CNbEqp::OnEqpReg! RegIP:"TPIPFORMAT" \n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));	
		
	CHECK_EQP_SEM;

	m_tNb.m_dwUserNode = wSrcNode;
	m_tNb.m_dwUserInst = wSrcInst;
	memcpy(&m_tNb.m_tRegInfo, &tMdlProp, sizeof(m_tNb.m_tRegInfo));

	OspNodeDiscCBReg(m_tNb.m_dwUserNode, AID_UMSEQP_APP, EQP_SERVER_INST);
 
	TUmsNetbufCfg tCfg;
	tCfg.m_dwUmsNode = wSrcNode;
	NotifyMsgToEqp(wSrcNode, wSrcInst, ev_Netbuf_ACK, &tCfg, sizeof(tCfg));
}

void CNbEqp::OnNbInitSuccess(CTpMsg *const ptMsg)
{
	u16 wEqpIndex;
	TP_SAFE_CAST( wEqpIndex, ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("OnNbInitSuccess! index:%d, RegIP:"TPIPFORMAT" \n", wEqpIndex, Tpu32ToIP(m_tNb.m_tRegInfo.m_dwEqpIP)));	

	CHECK_EQP_SEM;
	if (m_tNb.m_bRegsited)
	{
		return;
	}
	m_tNb.m_bRegsited = TRUE;
	
	TEqpRes tEqp;
	tEqp.m_dwEqpInst = m_tNb.m_dwUserInst;
	tEqp.m_dwEqpNode = m_tNb.m_dwUserNode;
	tEqp.m_dwEqpIp = m_tNb.m_tRegInfo.m_dwEqpIP;
	tEqp.m_wEqpIndex = wEqpIndex;
	
// 	//通知call注册
// 	CTpMsg cMsg;
// 	cMsg.SetEvent(evtp_UmsMediaReg_Notify);
// 	cMsg.SetBody(&tEqp, sizeof(tEqp));
// 	
// 	cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
}


BOOL32 CNbEqp::AssignEqpEx(TEqpParam* ptEqpParam)
{
	CHECK_EQP_SEM;
	
	if (m_tNb.IsIdle() || !m_tNb.m_bRegsited)
	{
		return FALSE;
	}

	m_tNb.m_dwUsed += ptEqpParam->m_dwCapCount;

	ptEqpParam->m_ptEqpRes->m_dwEqpNode = m_tNb.m_dwUserNode;
	ptEqpParam->m_ptEqpRes->m_dwEqpInst = m_tNb.m_dwUserInst;
	ptEqpParam->m_ptEqpRes->m_dwEqpIp = m_tNb.m_tRegInfo.m_dwEqpIP;

	return TRUE;
}



BOOL32 CNbEqp::ReleaseEqpEx(TEqpParam* ptEqpParam)
{
	CHECK_EQP_SEM;

	u32 dwCapCount = ptEqpParam->m_dwCapCount;

	if (m_tNb.IsIdle())
	{
		return FALSE;
	}
	
	if (dwCapCount > m_tNb.m_dwUsed)
	{
		MdlError(Ums_Mdl_Eqp, ("CNbEqp::ReleaseEqp cap failed! Free Count:%d, Assigned Count:%d\n", dwCapCount, m_tNb.m_dwUsed));
		return FALSE;
	}
	
	m_tNb.m_dwUsed -= dwCapCount;
	return TRUE;
}


BOOL32 CNbEqp::OnDisConnect(u32 dwNode)
{
	u32 dwRegIP;
	TEqpRes tEqp;

	CHECK_EQP_SEM;

	if (m_tNb.m_dwUserNode != dwNode)
	{
		return FALSE;
	}
	
	tEqp.m_dwEqpInst = m_tNb.m_dwUserInst;
	tEqp.m_dwEqpNode = m_tNb.m_dwUserNode;
	dwRegIP = m_tNb.m_tRegInfo.m_dwEqpIP;

	m_tNb.Clear();	

	MdlHint(Ums_Mdl_Eqp, ("CNbEqp::RegOut , RegIP:"TPIPFORMAT" \n", Tpu32ToIP(dwRegIP)));	

	//通知call注册
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UmsMediaUnReg_Notify);
	cMsg.SetBody(&tEqp, sizeof(tEqp));
	
	cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);

	return TRUE;
}


void CNbEqp::Show()
{
	msgprintnotime("NetBufInfo:\n");

	if (m_tNb.m_bRegsited)
	{
		msgprintnotime("  Netbuf cap:%d, Node:%d, Reged:%d, use:%d, Ip:"TPIPFORMAT"\n"
			, m_tNb.m_tRegInfo.m_dwCapSet, m_tNb.m_dwUserNode, m_tNb.m_bRegsited, m_tNb.m_dwUsed, Tpu32ToIP(m_tNb.m_tRegInfo.m_dwEqpIP));
	}
}