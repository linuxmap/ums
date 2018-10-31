#include "adaptereqp.h"
#include "eventoutumseqp.h"
#include "innereventregsrv.h"
#include "innereventumscall.h"
#include "umsconfig.h"

extern BOOL32 g_bKedaManuOn;
CAdapterEqp::CAdapterEqp(CUmsEqpInst* pInst)
:CEqpBase(pInst)
{
}

CAdapterEqp::~CAdapterEqp()
{
	
}

void CAdapterEqp::Handle(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();

	switch(wEvent)
	{
	case ev_SipAdapterInitCfg_Req:
		OnEqpReg(ptMsg);
		break;
	case ev_SipAdapterInitSuccess_Ind:
		OnAdaptInitSuccess(ptMsg);
		break;
	default:
		MdlError(Ums_Mdl_Eqp, ("CAdapterEqp::Handle Unknow event:%d->%s\n", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}
}


void CAdapterEqp::OnEqpReg(CTpMsg *const ptMsg)
{
	TModelProp tMdlProp;
	TP_SAFE_CAST( tMdlProp, ptMsg->GetBody());
	EmTpConfProtocol emProtocol;
	TP_SAFE_CAST( emProtocol, ptMsg->GetBody()+sizeof(TModelProp));

	u32 wSrcNode = ptMsg->GetSrcNode();
	u32 wSrcInst = ptMsg->GetSrcIId();
	
	u16 wMdlIndex = TP_INVALID_INDEX;
	CAdapterModle* ptModle = FindIdle(wMdlIndex);

	if (NULL == ptModle)
	{
		NotifyMsgToEqp(wSrcNode, wSrcInst, ev_SipAdapterInitCfg_NACK, NULL, 0);
		MdlError(Ums_Mdl_Eqp, ("CAdapterEqp::OnEqpReg No idle location! RegIP:"TPIPFORMAT"\n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));	
		return;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAdapterEqp::OnEqpReg! RegIP:"TPIPFORMAT" \n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));	
		
	TUmsStackCallCfg tCfg;
	umsGetUmsStackCfg(tCfg);

	TTPSipRegistrarCfg tReg;
	umsGetSipRegCfg(tReg);

	tCfg.m_wMaxCallNum = tCfg.m_wMaxCallNum;
	tCfg.m_wCallingPort += wMdlIndex * 2;
	tCfg.m_wUmsIndex = wMdlIndex;
	tCfg.m_dwRegIP = tReg.dwRegIP;
	tCfg.m_wRegPort = tReg.wRegPort;
	tCfg.m_dwUmsNode = wSrcNode;
	
	tCfg.SetProductID(UMS_ProductID);
	tCfg.SetVerID(UMS_VerID);

	CHECK_EQP_SEM;

	ptModle->m_dwUserNode = wSrcNode;
	ptModle->m_dwUserInst = wSrcInst;
	ptModle->m_dwListenPort = tCfg.m_wCallingPort;
	memcpy(&ptModle->m_tRegInfo, &tMdlProp, sizeof(ptModle->m_tRegInfo));
	ptModle->m_emAdatperType = emProtocol;	

	OspNodeDiscCBReg(ptModle->m_dwUserNode, AID_UMSEQP_APP, EQP_SERVER_INST);

	TTPQTEncryptInfo tTPQTEncryptInfo;
	umsGetQTEncryptInfo(tTPQTEncryptInfo);
	u8 abyBuf[sizeof(TUmsStackCallCfg) + sizeof(TTPQTEncryptInfo) +sizeof(BOOL32)] = {0};
	memcpy(abyBuf, &tCfg, sizeof(tCfg));
	memcpy(abyBuf + sizeof(TUmsStackCallCfg), &tTPQTEncryptInfo, sizeof(tTPQTEncryptInfo));
	memcpy(abyBuf + sizeof(TUmsStackCallCfg) + sizeof(TTPQTEncryptInfo) ,&g_bKedaManuOn,sizeof(BOOL32));
	msgprint("OnRegSuccess, channel on is %d\n", g_bKedaManuOn);
	NotifyMsgToEqp(wSrcNode, wSrcInst, ev_SipAdapterInitCfg_ACK, abyBuf, sizeof(abyBuf));
}

void CAdapterEqp::OnAdaptInitSuccess(CTpMsg *const ptMsg)
{ 
	u16 wEqpIndex = TP_INVALID_INDEX;
	TP_SAFE_CAST( wEqpIndex, ptMsg->GetBody());
		
	if (wEqpIndex >= MAX_ADAPTER_MDL_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("OnAdaptInitSuccess Index invalid! :%d\n", wEqpIndex));	
		return;
	}
	MdlHint(Ums_Mdl_Eqp, ("OnAdaptInitSuccess! index:%d, RegIP:"TPIPFORMAT" \n", wEqpIndex, Tpu32ToIP(m_atAdapter[wEqpIndex].m_tRegInfo.m_dwEqpIP)));	
		
	CHECK_EQP_SEM;

	if (m_atAdapter[wEqpIndex].m_bRegsited)
	{
		return;
	}
	m_atAdapter[wEqpIndex].m_bRegsited = TRUE;

	TEqpRes tEqp;

	tEqp.m_dwEqpIp = m_atAdapter[wEqpIndex].m_tRegInfo.m_dwEqpIP;
	tEqp.m_dwEqpInst = m_atAdapter[wEqpIndex].m_dwUserInst;
	tEqp.m_dwEqpNode = m_atAdapter[wEqpIndex].m_dwUserNode;
	tEqp.m_wEqpIndex = wEqpIndex;
	
	
	TTPTransAddr tAdapterAddr;
	tAdapterAddr.m_dwIP = tEqp.m_dwEqpIp;
	tAdapterAddr.m_wPort = m_atAdapter[wEqpIndex].m_dwListenPort;
	
	//Í¨Öªcall×¢²á
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UmsAdapterReg_Notify);
	cMsg.SetBody(&tEqp, sizeof(tEqp));
	cMsg.CatBody(&tAdapterAddr, sizeof(tAdapterAddr));

	cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
}

CAdapterModle* CAdapterEqp::FindIdle(u16& wEqpIndex)
{
	CHECK_EQP_SEM;

	for (u16 wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM; ++wIndex)
	{
		if (m_atAdapter[wIndex].IsIdle())
		{
			wEqpIndex = wIndex;
			return &m_atAdapter[wIndex];
		}
	}
	return NULL;
}


BOOL32 CAdapterEqp::AssignEqpByEqpEx(TEqpParam* ptEqpParam)
{
	CHECK_EQP_SEM;

	CAdapterModle* ptEqp = NULL;
	u16 wIndex;	
	for (wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM; ++wIndex)
	{
		if (m_atAdapter[wIndex].IsIdle() || !m_atAdapter[wIndex].m_bRegsited)
		{
			continue;
		}
		if (ptEqpParam->m_ptEqpRes->m_dwEqpNode != m_atAdapter[wIndex].m_dwUserNode)
		{
			continue;
		}
		
		ptEqp = &m_atAdapter[wIndex];
		break;
	}
	
	if (NULL == ptEqp)
	{
		return FALSE;
	}
	
	ptEqp->m_dwUsed += ptEqpParam->m_dwCapCount;
	ptEqpParam->m_ptEqpRes->m_dwEqpNode = ptEqp->m_dwUserNode;
	ptEqpParam->m_ptEqpRes->m_dwEqpInst = ptEqp->m_dwUserInst;
	ptEqpParam->m_ptEqpRes->m_dwEqpIp = ptEqp->m_tRegInfo.m_dwEqpIP;
	ptEqpParam->m_ptEqpRes->m_wEqpIndex = wIndex;
	return TRUE;
}


BOOL32 CAdapterEqp::AssignEqpEx(TEqpParam* ptEqpParam)
{
	CHECK_EQP_SEM;

	CAdapterModle* ptEqp = NULL;
	u16 wIndex = 0;
	u16 wEqpIndex = TP_INVALID_INDEX;
	for (wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM; ++wIndex)
	{
		if (m_atAdapter[wIndex].IsIdle() || !m_atAdapter[wIndex].m_bRegsited)
		{
			continue;
		}
		if (NULL == ptEqp)
		{
			ptEqp = &m_atAdapter[wIndex];
			wEqpIndex = wIndex;
		}
		else
		{
			if (ptEqp->m_dwUsed > m_atAdapter[wIndex].m_dwUsed)
			{
				ptEqp = &m_atAdapter[wIndex];
				wEqpIndex = wIndex;
			}
		}
	}
	
	if (NULL == ptEqp)
	{
		return FALSE;
	}
	
	ptEqp->m_dwUsed += ptEqpParam->m_dwCapCount;
	ptEqpParam->m_ptEqpRes->m_dwEqpNode = ptEqp->m_dwUserNode;
	ptEqpParam->m_ptEqpRes->m_dwEqpInst = ptEqp->m_dwUserInst;
	ptEqpParam->m_ptEqpRes->m_dwEqpIp = ptEqp->m_tRegInfo.m_dwEqpIP;
	ptEqpParam->m_ptEqpRes->m_wEqpIndex = wEqpIndex;
	return TRUE;
}

BOOL32 CAdapterEqp::GetAllEqpRes( TEqpRes* pcEqpRes, u16 wEqpNum )
{
	BOOL32 bRet = FALSE;
	TEqpRes* pcEqpTemp = pcEqpRes;
	
	for ( u16 wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM && wIndex < wEqpNum; wIndex ++ )
	{
		if ( !m_atAdapter[wIndex].IsIdle() && m_atAdapter[wIndex].m_bRegsited )
		{
			pcEqpTemp->m_dwEqpNode = m_atAdapter[wIndex].m_dwUserNode;
			pcEqpTemp->m_wEqpIndex = wIndex;
			pcEqpTemp->m_dwEqpIp = m_atAdapter[wIndex].m_tRegInfo.m_dwEqpIP;
			pcEqpTemp ++;
			bRet = TRUE;
		}
	}
	
	return bRet;
}


BOOL32 CAdapterEqp::ReleaseEqpEx(TEqpParam* ptEqpParam)
{
	CHECK_EQP_SEM;

	u16 wEqpIndex = ptEqpParam->m_ptEqpRes->m_wEqpIndex;
	u32 dwCapCount = ptEqpParam->m_dwCapCount;
	if (wEqpIndex >= MAX_ADAPTER_MDL_NUM || m_atAdapter[wEqpIndex].IsIdle())
	{
		return FALSE;
	}
	
	if (dwCapCount > m_atAdapter[wEqpIndex].m_dwUsed)
	{
		MdlError(Ums_Mdl_Eqp, ("CAdapterEqp::ReleaseEqp cap failed! Free Count:%d, Assigned Count:%d\n", dwCapCount, m_atAdapter[wEqpIndex].m_dwUsed));
		return FALSE;
	}
	
	m_atAdapter[wEqpIndex].m_dwUsed -= dwCapCount;
	return TRUE;
}

BOOL32 CAdapterEqp::OnDisConnect(u32 dwNode)
{
	u16 wIndex;
	u32 dwRegIP;
	TEqpRes tEqp;
	CHECK_EQP_SEM;

	CEqpModle* ptEqp = NULL;	
	for (wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM; ++wIndex)
	{
		if (m_atAdapter[wIndex].m_dwUserNode == dwNode)
		{
			ptEqp = &m_atAdapter[wIndex];
			break;
		}
	}
	
	if (NULL == ptEqp)
	{
		return FALSE;
	}
	
	dwRegIP = ptEqp->m_tRegInfo.m_dwEqpIP;

	tEqp.m_dwEqpInst = ptEqp->m_dwUserInst;
	tEqp.m_dwEqpNode = ptEqp->m_dwUserNode;
	tEqp.m_wEqpIndex = wIndex;
	tEqp.m_dwEqpIp = dwRegIP;

	ptEqp->Clear();	


	MdlHint(Ums_Mdl_Eqp, ("CAdapterEqp::RegOut index:%d, RegIP:"TPIPFORMAT", LocIp:"TPIPFORMAT" \n", wIndex, Tpu32ToIP(dwRegIP)));	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UmsAdapterUnReg_Notify);
	cMsg.CatBody(&tEqp, sizeof(CEqpModle));
	cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);

	return TRUE;
}


void CAdapterEqp::Show()
{
	msgprintnotime("AdapterInfo:\n");
	CAdapterModle*	ptEqp;
	for (u16 wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM; ++wIndex)
	{
		ptEqp = &m_atAdapter[wIndex];
		if (ptEqp->m_bRegsited)
		{
			msgprintnotime("  Index:%d, cap:%d, Node:%d, Reged:%d, use:%d, Ip:"TPIPFORMAT", Port:%d\n"
							, wIndex, ptEqp->m_tRegInfo.m_dwCapSet, ptEqp->m_dwUserNode, ptEqp->m_bRegsited
							, ptEqp->m_dwUsed, Tpu32ToIP(ptEqp->m_tRegInfo.m_dwEqpIP), ptEqp->m_dwListenPort);
		}
	}
}