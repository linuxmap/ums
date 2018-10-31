#include "mediatranseqp.h"
#include "eventoutumseqp.h"
#include "innereventumscall.h"
#include "umsconfig.h"
#include "eqpinst.h"
#include "baseqp.h"
#include "mpu2tpeqp.h"
#include "umsconfigex.h"
#include "eventoutumsmediatrans.h"
#include "eventoutumseqp.h"
#include "umsapi.h"
#include "eqpmgr.h"
#include "umsconfig.h"

CMediaTransEqp::CMediaTransEqp(CUmsEqpInst* pInst)
:CEqpBase(pInst)
{
}

CMediaTransEqp::~CMediaTransEqp()
{
	
}

void CMediaTransEqp::Handle(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();

	switch(wEvent)
	{
	case ev_MediaTrans_Req:
		OnEqpReg(ptMsg);
		break;
	case ev_MediatransInitSuccess_Ind:
		OnMediatransInitSuccess(ptMsg);
		break;
	case ev_media_switchtelnetftp_req:
		OnMediatransSshSwitch(ptMsg);
		break;
	default:
		MdlError(Ums_Mdl_Eqp, ("CMediaTransEqp::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}
}


void CMediaTransEqp::OnEqpReg(CTpMsg *const ptMsg)
{
	TModelProp tMdlProp;
	TP_SAFE_CAST( tMdlProp, ptMsg->GetBody());
	TIpmaskinfo tIpmask;
	TP_SAFE_CAST( tIpmask, ptMsg->GetBody()+sizeof(tMdlProp));

	u32 wSrcNode = ptMsg->GetSrcNode();
	u32 wSrcInst = ptMsg->GetSrcIId();
	
	u16 wMdlIndex = TP_INVALID_INDEX;
	CMediaTransModle* ptModle = FindIdle(wMdlIndex);

	if (NULL == ptModle)
	{
		NotifyMsgToEqp(wSrcNode, wSrcInst, ev_MediaTrans_NACK, NULL, 0);
		MdlError(Ums_Mdl_Eqp, ("CMediaTransEqp::OnEqpReg No idle location! RegIP:"TPIPFORMAT"\n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));	
		return;
	}

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	if (NULL == m_pcInst->GetEqpMgr()->GetBrdCfg(tMdlProp.m_dwEqpIP) 
		&& Ums_Run_On_Mpc2 == CUmsConfigEx::GetInstance()->GetUmsRunType() )
	{//验证下ip
		NotifyMsgToEqp(wSrcNode, wSrcInst, ev_MediaTrans_NACK, NULL, 0);
		MdlError(Ums_Mdl_Eqp, ("CMediaTransEqp::OnEqpReg ip error! RegIP:"TPIPFORMAT" \n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));
		return;
	}
#endif

	MdlHint(Ums_Mdl_Eqp, ("CMediaTransEqp::OnEqpReg! RegIP:"TPIPFORMAT" \n", Tpu32ToIP(tMdlProp.m_dwEqpIP)));

// 	MdlHint(Ums_Mdl_Eqp, ("CMediaTransEqp::OnEqpReg. Ipa:"TPIPFORMAT", maska:"TPIPFORMAT", ipb:"TPIPFORMAT", maskb:"TPIPFORMAT".\n", 
// 		Tpu32ToIP(tIpmask.m_dwIpa), Tpu32ToIP(tIpmask.m_dwMaska), Tpu32ToIP(tIpmask.m_dwIpb), Tpu32ToIP(tIpmask.m_dwMaskb)));
		
	CHECK_EQP_SEM;

	ptModle->m_dwUserNode = wSrcNode;
	ptModle->m_dwUserInst = wSrcInst;
	memcpy(&ptModle->m_tRegInfo, &tMdlProp, sizeof(ptModle->m_tRegInfo));
	memcpy(&ptModle->m_tIpMask, &tIpmask, sizeof(tIpmask));
    
	ptModle->m_bIsLocal = IsLocalUmsIP(tMdlProp.m_dwEqpIP);
	OspNodeDiscCBReg(ptModle->m_dwUserNode, AID_UMSEQP_APP, EQP_SERVER_INST);

	//更新外设注册状态到eqpmgr
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(wSrcNode, 0, TRUE);

	TUmsMediatransCfg tCfg;
	tCfg.m_wUmsIndex = wMdlIndex;
	tCfg.m_dwUmsNode = wSrcNode;
	NotifyMsgToEqp(wSrcNode, wSrcInst, ev_MediaTrans_ACK, &tCfg, sizeof(tCfg));

	TPBoardSwitch tSshInfo;
	tSshInfo.m_bSwitch = FALSE;
	if (!ptModle->m_bIsLocal)
	{
		TPBoardSwitch tSshInfo;
		tSshInfo.m_bSwitch = FALSE;
		NotifyMsgToEqp(wSrcNode, wSrcInst, ev_media_switchtelnetftp_req, &tSshInfo, sizeof(tSshInfo));
	}
}

void CMediaTransEqp::OnMediatransInitSuccess(CTpMsg *const ptMsg)
{
	u16 wEqpIndex = TP_INVALID_INDEX;
	TP_SAFE_CAST( wEqpIndex, ptMsg->GetBody());
		
	if (wEqpIndex >= MAX_DATASWITCH_MDL_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("OnMediatransInitSuccess Index invalid! :%d\n", wEqpIndex));	
		return;
	}
	MdlHint(Ums_Mdl_Eqp, ("OnMediatransInitSuccess! index:%d, RegIP:"TPIPFORMAT" \n", wEqpIndex, Tpu32ToIP(m_atMediaTrans[wEqpIndex].m_tRegInfo.m_dwEqpIP)));	
	

	CHECK_EQP_SEM;
	if (m_atMediaTrans[wEqpIndex].m_bRegsited)
	{
		return;
	}
	m_atMediaTrans[wEqpIndex].m_bRegsited = TRUE;



#ifndef WIN32

	if (Ums_Run_On_Mpc2 == CUmsConfigEx::GetInstance()->GetUmsRunType())
	{
		TBrdEntry* pBrd = m_pcInst->GetEqpMgr()->GetBrdCfg(m_atMediaTrans[wEqpIndex].m_tRegInfo.m_dwEqpIP);
		if (NULL == pBrd)
		{
			MdlError(Ums_Mdl_Eqp, ("CMediaTransEqp::OnMediatransInitSuccess ip error! RegIP:"TPIPFORMAT" \n", 
				Tpu32ToIP(m_atMediaTrans[wEqpIndex].m_tRegInfo.m_dwEqpIP)));
			OnDisConnect(m_atMediaTrans[wEqpIndex].m_dwUserNode);
			return;
		}
		m_atMediaTrans[wEqpIndex].m_bIS22 = 
		(m_pcInst->GetEqpMgr()->GetBrdCfg(m_atMediaTrans[wEqpIndex].m_tRegInfo.m_dwEqpIP)->m_tBrdCfg.m_tBrdPos.m_emBrdType == em_is22_brd);
	}
	else
	{
		m_atMediaTrans[wEqpIndex].m_bIS22 = FALSE;
	}

#endif

	TEqpRes tEqp;
	tEqp.m_dwEqpInst = m_atMediaTrans[wEqpIndex].m_dwUserInst;
	tEqp.m_dwEqpNode = m_atMediaTrans[wEqpIndex].m_dwUserNode;
	tEqp.m_wEqpIndex = wEqpIndex;
	tEqp.m_dwEqpIp = m_atMediaTrans[wEqpIndex].m_tRegInfo.m_dwEqpIP;
	
	TIpmaskinfo tIpMask;
	memcpy(&tIpMask, &m_atMediaTrans[wEqpIndex].m_tIpMask, sizeof(tIpMask));

	//通知call注册
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UmsMediaReg_Notify);
	cMsg.SetBody(&tEqp, sizeof(tEqp));
	cMsg.CatBody(&tIpMask, sizeof(tIpMask));
	cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
}

CMediaTransModle* CMediaTransEqp::FindIdle(u16& wEqpIndex)
{
	CHECK_EQP_SEM;

	for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
	{
		if (m_atMediaTrans[wIndex].IsIdle())
		{
			wEqpIndex = wIndex;
			return &m_atMediaTrans[wIndex];
		}
	}
	return NULL;
}

void CMediaTransEqp::OnMediatransSshSwitch(CTpMsg *const ptMsg)
{
	TPBoardSwitch tSshSwithInfo;
	TP_SAFE_CAST( tSshSwithInfo, ptMsg->GetBody());
	for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
	{
	//	MdlHint(Ums_Mdl_Eqp, ("bLocal:%d,bsshonoff:%d,RegIP:"TPIPFORMAT" \n",m_atMediaTrans[wIndex].m_bIsLocal,tSshSwithInfo.m_bSwitch, Tpu32ToIP(m_atMediaTrans[wIndex].m_tRegInfo.m_dwEqpIP)));
		if (m_atMediaTrans[wIndex].m_bIsLocal)
		{
			MdlHint(Ums_Mdl_Eqp, ("OnMediatransSshSwitch! index:%d, RegIP:"TPIPFORMAT"  \n", wIndex, Tpu32ToIP(m_atMediaTrans[wIndex].m_tRegInfo.m_dwEqpIP)));
			continue;
		}
		if (!m_atMediaTrans[wIndex].m_bRegsited)
		{
			continue;
		}
		NotifyMsgToEqp(m_atMediaTrans[wIndex].m_dwUserNode, m_atMediaTrans[wIndex].m_dwUserInst, ev_media_switchtelnetftp_req, &tSshSwithInfo, sizeof(tSshSwithInfo));
	}
}

void CMediaTransEqp::CalcEqpUsedStat(TTPBrdUsedInfo& tUsed)
{
	tUsed.m_emType = em_dataswitch_mdl;

	u32 dwCount = 0;

	for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
	{
		if (m_atMediaTrans[wIndex].m_bRegsited)
		{
			tUsed.m_wRegNum ++;
		}
	}
	MdlHint(Ums_Mdl_Eqp, ("GetMediaCount! mediacount:%d \n", tUsed.m_wRegNum));
	return;

}


BOOL32 CMediaTransEqp::AssignEqpEx(TEqpParam* ptEqpParam)
{
	return FALSE;
}

BOOL32 CMediaTransEqp::AssignEqpByEqpEx(TEqpParam* ptEqpParam)
{
	CHECK_EQP_SEM;
	
	TMediaParam* pParam = (TMediaParam*)(ptEqpParam);
	BOOL32 bRet = FALSE;
	u16 wIndex = 0;
	
	
	u16 wMinIndex = TP_INVALID_INDEX;	
	//遍历此会议所有的转发板，如果存在空缺，则分配一个转发板
	for (wIndex = 0; wIndex < UMS_CONF_MAX_DS_NUM; ++wIndex)
	{
		if (!pParam->m_atEqp[wIndex].IsValid())
		{//未分配，则需要重新分配一个转发板
			wMinIndex = wIndex;
			break;
		}
	}

	if (wMinIndex < UMS_CONF_MAX_DS_NUM)
	{//存在空缺，分配一个新的转发板
		bRet = Assign(pParam);
		if (bRet)
		{
			return TRUE;
		}
	}
	
	CMediaTransModle* ptEqp = NULL;
	u16 wEqpIndexTmp = 0;
	u16 wEqpIndex = 0;
	u32 dwUsedOne = 0;
	u32 dwUsedTwo = 0;

	//在已有的转发板中分配
	for (wIndex = 0; wIndex < UMS_CONF_MAX_DS_NUM; ++wIndex)
	{
		if (!pParam->m_atEqp[wIndex].IsValid())
		{
			continue;
		}

		wEqpIndexTmp = pParam->m_atEqp[wIndex].m_wEqpIndex;
		
		if (m_atMediaTrans[wEqpIndexTmp].IsIdle() || !m_atMediaTrans[wEqpIndexTmp].m_bRegsited)
		{
			continue;
		}
		 
		if (NULL == ptEqp)
		{
			ptEqp = &m_atMediaTrans[wEqpIndexTmp];
			wEqpIndex = wEqpIndexTmp;
		}
		else
		{
			// 保证会议中60%的转发能力来源于IS2.2上的转发板，采取的方法是减少IS2.2板上已使用能力数的权重
			if (ptEqp->m_bIS22)
			{// 运行在IS2.2上的转发板
				dwUsedOne = ptEqp->m_dwUsed;
			}
			else
			{
				dwUsedOne = ptEqp->m_dwUsed*3;
			}

			if (m_atMediaTrans[wEqpIndexTmp].m_bIS22)
			{// 运行在IS2.2上的转发板
				dwUsedTwo = m_atMediaTrans[wEqpIndexTmp].m_dwUsed;
			}
			else
			{
				dwUsedTwo = (m_atMediaTrans[wEqpIndexTmp].m_dwUsed)*3;
			}

			if (dwUsedOne > dwUsedTwo)
			{
				ptEqp = &m_atMediaTrans[wEqpIndexTmp];
				wEqpIndex = wEqpIndexTmp;
			}
		}

	}

	if (NULL == ptEqp)
	{
		return FALSE;
	}
	
	ptEqp->AddUse(pParam->m_dwCapCount);
	pParam->m_ptEqpRes->m_dwEqpNode = ptEqp->m_dwUserNode;
	pParam->m_ptEqpRes->m_dwEqpInst = ptEqp->m_dwUserInst;
	pParam->m_ptEqpRes->m_dwEqpIp = ptEqp->m_tRegInfo.m_dwEqpIP;
	pParam->m_ptEqpRes->m_wEqpIndex = wEqpIndex;
	return TRUE;
}


BOOL32 CMediaTransEqp::Assign(TMediaParam* pParam)
{
	CMediaTransModle* ptEqp = NULL;
	u16 wEqpIndex = TP_INVALID_INDEX;

	do 
	{
		//如果是会议，则优先分配IS2.2为其转发板
		if (pParam->m_emAssignType == TMediaParam::emAssignConf)
		{
			for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
			{
				if (m_atMediaTrans[wIndex].IsIdle() || !m_atMediaTrans[wIndex].m_bRegsited)
				{
					continue;
				}

				if (!m_atMediaTrans[wIndex].m_bIS22)
				{//优先分配IS22
					continue;
				}

				ptEqp = &m_atMediaTrans[wIndex];
				wEqpIndex = wIndex;
				
				for (u16 wMediaIndex = 0; wMediaIndex < UMS_CONF_MAX_DS_NUM; ++wMediaIndex)
				{
					if (m_atMediaTrans[wIndex].m_dwUserNode == pParam->m_atEqp[wMediaIndex].m_dwEqpNode)
					{
						ptEqp->AddUse(pParam->m_dwCapCount);
						pParam->m_ptEqpRes->m_dwEqpNode = ptEqp->m_dwUserNode;
						pParam->m_ptEqpRes->m_dwEqpInst = ptEqp->m_dwUserInst;
						pParam->m_ptEqpRes->m_dwEqpIp = ptEqp->m_tRegInfo.m_dwEqpIP;
						pParam->m_ptEqpRes->m_wEqpIndex = wEqpIndex;
						return TRUE;
					}
				}
				break;
			}	

			if (NULL != ptEqp)
			{
				break;
			}
			else if (Ums_Run_On_Mpc2 == CUmsConfigEx::GetInstance()->GetUmsRunType())
			{
				return FALSE;
			}
		}

		//取得使用最少的那个转发板
		for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
		{
			if (m_atMediaTrans[wIndex].IsIdle() || !m_atMediaTrans[wIndex].m_bRegsited)
			{
				continue;
			}
			
			BOOL32 bAssign = FALSE;
			for (u16 wI = 0; wI < UMS_CONF_MAX_DS_NUM; ++wI)
			{
				if (m_atMediaTrans[wIndex].m_dwUserNode == pParam->m_atEqp[wI].m_dwEqpNode)
				{
					bAssign = TRUE;
				}
			}
			
			if (bAssign)
			{
				continue;
			}
			
			if (m_atMediaTrans[wIndex].m_tIpMask.IsValid())
			{
				if (pParam->m_dwNodeIp && !m_atMediaTrans[wIndex].m_tIpMask.GetSameNetWork(pParam->m_dwNodeIp))
				{//只能使用同网段转发板
					continue;
				}
			}


			if (NULL == ptEqp)
			{
				ptEqp = &m_atMediaTrans[wIndex];
				wEqpIndex = wIndex;
			}
			else
			{
				if (ptEqp->m_dwUsed > m_atMediaTrans[wIndex].m_dwUsed)
				{
					ptEqp = &m_atMediaTrans[wIndex];
					wEqpIndex = wIndex;
				}
			}
		}
	} while (0);
	

	if (NULL == ptEqp)
	{
		return FALSE;
	}
	
	ptEqp->AddUse(pParam->m_dwCapCount);
	pParam->m_ptEqpRes->m_dwEqpNode = ptEqp->m_dwUserNode;
	pParam->m_ptEqpRes->m_dwEqpInst = ptEqp->m_dwUserInst;
	pParam->m_ptEqpRes->m_dwEqpIp = ptEqp->m_tRegInfo.m_dwEqpIP;
	pParam->m_ptEqpRes->m_wEqpIndex = wEqpIndex;
	return TRUE;
}

BOOL32 CMediaTransEqp::AssignDsForBas( TEqpRes* ptEqp, u32 dwCapCount )
{
	CMediaTransModle* ptEqpTmp = NULL;
	u32 dwMaxCap = TP_INVALID_INDEX;

	u16 wEqpIndex = TP_INVALID_INDEX;
	for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
	{
		if (m_atMediaTrans[wIndex].IsIdle() || !m_atMediaTrans[wIndex].m_bRegsited)
		{
			continue;
		}

		if ( m_atMediaTrans[wIndex].m_dwUsed < dwMaxCap )
		{//查找使用量最小的
			dwMaxCap = m_atMediaTrans[wIndex].m_dwUsed;
			ptEqpTmp = &m_atMediaTrans[wIndex];
			wEqpIndex = wIndex;
		}
	}

	if ( NULL == ptEqpTmp )
	{
		return FALSE;
	}

	ptEqpTmp->AddUse(dwCapCount);

	ptEqp->m_dwEqpNode = ptEqpTmp->m_dwUserNode;
	ptEqp->m_dwEqpInst = ptEqpTmp->m_dwUserInst;
	ptEqp->m_dwEqpIp = ptEqpTmp->m_tRegInfo.m_dwEqpIP;
	ptEqp->m_wEqpIndex = wEqpIndex;

	return TRUE;
}

BOOL32 CMediaTransEqp::ReleaseDsForBas( u32 dwIP, u32 dwCapCount )
{

	for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
	{
		if (m_atMediaTrans[wIndex].IsIdle() || !m_atMediaTrans[wIndex].m_bRegsited)
		{
			continue;
		}
		
		if ( m_atMediaTrans[wIndex].m_tRegInfo.m_dwEqpIP == dwIP )
		{
			m_atMediaTrans[wIndex].DelUse(dwCapCount);;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL32 CMediaTransEqp::ReleaseEqpEx(TEqpParam* ptEqpParam)
{
	CHECK_EQP_SEM;

	u16 wEqpIndex = ptEqpParam->m_ptEqpRes->m_wEqpIndex;
	u32 dwCapCount = ptEqpParam->m_dwCapCount;

	if (wEqpIndex >= MAX_DATASWITCH_MDL_NUM || m_atMediaTrans[wEqpIndex].IsIdle())
	{
		return FALSE;
	}
	
	if (dwCapCount > m_atMediaTrans[wEqpIndex].m_dwUsed)
	{
		MdlError(Ums_Mdl_Eqp, ("CMediaTransEqp::ReleaseEqp cap failed! Free Count:%d, Assigned Count:%d\n", dwCapCount, m_atMediaTrans[wEqpIndex].m_dwUsed));
	}
	
	m_atMediaTrans[wEqpIndex].DelUse(dwCapCount);
	return TRUE;
}


BOOL32 CMediaTransEqp::OnDisConnect(u32 dwNode)
{
	u16 wIndex;
	u32 dwRegIP;
	TEqpRes tEqp;

	CHECK_EQP_SEM;

	CEqpModle* ptEqp = NULL;	
	for (wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
	{
		if (m_atMediaTrans[wIndex].m_dwUserNode == dwNode)
		{
			ptEqp = &m_atMediaTrans[wIndex];
			break;
		}
	}
	
	if (NULL == ptEqp)
	{
		return FALSE;
	}
	
	tEqp.m_dwEqpInst = ptEqp->m_dwUserInst;
	tEqp.m_dwEqpNode = ptEqp->m_dwUserNode;
	tEqp.m_wEqpIndex = wIndex;
	dwRegIP = ptEqp->m_tRegInfo.m_dwEqpIP;

	//更新外设状态到eqpmgr
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptEqp->m_dwUserNode, 0, FALSE);

	ptEqp->Clear();	
	//更新使用率
	TTPBrdUsedInfo tUsed;
	CalcEqpUsedStat(tUsed);
	m_pcInst->GetEqpMgr()->UpdateBrdUsedState(tUsed);
	MdlHint(Ums_Mdl_Eqp, ("CMediaTransEqp::RegOut index:%d, RegIP:"TPIPFORMAT" \n", wIndex, Tpu32ToIP(dwRegIP)));	

	//通知call注册
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UmsMediaUnReg_Notify);
	cMsg.SetBody(&tEqp, sizeof(tEqp));
	
	cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
	
	return TRUE;
}


void CMediaTransEqp::Show()
{
	msgprintnotime("Mediatrans :\n");
	CMediaTransModle*	ptEqp;
	for (u16 wIndex = 0; wIndex < MAX_DATASWITCH_MDL_NUM; ++wIndex)
	{
		ptEqp = &m_atMediaTrans[wIndex];
		if (ptEqp->m_bRegsited)
		{
			msgprintnotime("  Index:%d, cap:%d, Node:%d, Reged:%d, use:%d, Ip:"TPIPFORMAT".\n"
			, wIndex, ptEqp->m_tRegInfo.m_dwCapSet, ptEqp->m_dwUserNode, ptEqp->m_bRegsited, ptEqp->m_dwUsed, Tpu32ToIP(ptEqp->m_tRegInfo.m_dwEqpIP));

			msgprintnotime("  IS22:%d, Ipa:"TPIPFORMAT", maska:"TPIPFORMAT", ipb:"TPIPFORMAT", maskb:"TPIPFORMAT", LocalOutIp:"TPIPFORMAT".\n", 
				ptEqp->m_bIS22, Tpu32ToIP(ptEqp->m_tIpMask.m_dwIpa), Tpu32ToIP(ptEqp->m_tIpMask.m_dwMaska), Tpu32ToIP(ptEqp->m_tIpMask.m_dwIpb), Tpu32ToIP(ptEqp->m_tIpMask.m_dwMaskb), Tpu32ToIP(ptEqp->m_tIpMask.m_dwOutIp));
		}
	}
}

