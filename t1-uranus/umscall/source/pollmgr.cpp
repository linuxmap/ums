#include "umsconfinst.h"
#include "umsstackinterface.h"
#include "pollmgr.h"
#include "eventoutsipadapter.h"
#include "eventoutumscall.h"
#include "innereventumscall.h"
#include "umsnetportmgr.h"
#include "umsbas.h"
#include "umsapi.h"
#include "tpcommonstruct.h"
#include "eventoutumsmediatrans.h"
#include "nodefsm.h"
#include "callmgr.h"
#include "tperrno.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpubas.h"
#endif

s8* GetStatPrint(EmPollStat emStat)
{
	switch(emStat)
	{
	case EmPollStat_Error: return "Error";
	case EmPollStat_Stop: return "Stop";
	case EmPollStat_Start: return "Start";
	case EmPollStat_Suspend: return "Suspend";
	default:
		return "unknow";
	}
}

void PollVmpCB( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, void* param, u16 wTmp1 )
{
	CUmsConfInst* pInst = (CUmsConfInst*)param;
	pInst->GetPollMgr()->VmpCB(pcService, emOpType, emRes);
	return;
}

void PollBasCB(u32 dwType, void* param1, void* param2)
{
#ifdef _USE_XMPUEQP_
    tXmpuBasCbData* pBasCbData =  (tXmpuBasCbData* )param1;
    CUmsConfInst* pInst = (CUmsConfInst*)pBasCbData->pService;
	CPollMgr* ptPollMgr = pInst->GetPollMgr();
	ptPollMgr->XmpuBasCB(dwType, (CScreenBasRes *)pBasCbData->pRes, pBasCbData->pData );

#else
	CScreenBasRes::VidBasCBType emType = (CScreenBasRes::VidBasCBType)dwType;
	CPollMgr* ptPollMgr = (CPollMgr*)param1;
	CScreenBasRes* ptBasRes = (CScreenBasRes*)param2;
	
	ptPollMgr->BasCB(emType, ptBasRes);
#endif

	return;
}

CPollMgr::CPollMgr( CUmsConfInst* pcInst )
:CTpHandler(pcInst)
{
	m_ptCurAddr = NULL;
	m_ptOldAddr = NULL;

	memset(m_apcBasRes, NULL, sizeof(m_apcBasRes));
	m_pcPollVmp = NULL;
	memset(m_aptLocalChair, NULL, sizeof(m_aptLocalChair));

	StopConf();
}

CPollMgr::~CPollMgr()
{
	StopConf();
}

BOOL32 CPollMgr::Handler( CTpMsg *const ptMsg )
{
	BOOL32 bProc = TRUE;
	switch(ptMsg->GetEvent())
	{
	case evtp_StartTurn_cmd:
		OnUmcStartPollReq(ptMsg);
		break;
	case evtp_StopTurn_cmd:
		OnUmcStopPollReq(ptMsg);
		break;
	case evtp_SuspendTurn_cmd:
		OnUmcSuspendPollReq(ptMsg);
		break;
	case evtp_ExeTurnList_time:
		OnPollTimer(ptMsg);
		break;
	case ev_media_ds_iframe_TwoRcvPort_Ind:
		OnIframeBySrcNty(ptMsg);
		break;
	case evtp_UpdateTurn_cmd:
		OnUpdatePollListFromUmc(ptMsg);
		break;
	default:
		bProc = FALSE;
		break;
	}

	return bProc;
}

BOOL32 CPollMgr::HandlerFromStack( CTpMsg *const ptMsg )
{
	BOOL32 bProc = TRUE;
	switch(ptMsg->GetEvent())
	{
	case evtp_Conf_StartPoll_Req:
		OnCncStartPollReq(ptMsg);
		break;
	case evtp_Conf_StopPoll_Req:
		OnCncStopPollReq(ptMsg);
		break;
	case evtp_Conf_SuspendPoll_Req:
		OnCncSuspendPollReq(ptMsg);
		break;
	case evtp_Conf_CasecadePollEp_Req:
		OnCasecadePollEpReq(ptMsg);
		break;
	case evtp_Conf_CasecadePollEp_Rsp:
		OnCasecadePollEpRsp(ptMsg);
		break;
	case ev_UmsUpdateConfTurnlist_Nty:
		OnUpdatePollListFromCnc(ptMsg);
		break;
	default:
		bProc = FALSE;
		break;
	}
	
	return bProc;
}

void CPollMgr::Show()
{
	msgprintnotime("\n");
	msgprintnotime(" ===PollMgr ConfID:%d  Beg===\n\n", Inst()->GetInsID());

	msgprintnotime(" UiOn:%s, Stat:%s, bBas:%d\n", GetStatPrint(m_emUiStat), GetStatPrint(m_emStat), m_bBas);

	msgprintnotime("\n");

	msgprintnotime(" RmtRtp0:"ADDRPORT_FORMAT" RmtRtp1:"ADDRPORT_FORMAT" RmtRtp2:"ADDRPORT_FORMAT"\n\n", 
						ADDRNET(m_atRmtRtp[0]), ADDRNET(m_atRmtRtp[1]), ADDRNET(m_atRmtRtp[2]));

	msgprintnotime(" SamllRmtRtp0:"ADDRPORT_FORMAT" SamllRmtRtp1:"ADDRPORT_FORMAT" SamllRmtRtp2:"ADDRPORT_FORMAT"\n\n", 
		ADDRNET(m_atSmallRmtRtp[0]), ADDRNET(m_atSmallRmtRtp[1]), ADDRNET(m_atSmallRmtRtp[2]));

	msgprintnotime(" CurInfo  EpID:%d, PollIndx:%d\n", m_ptCurAddr->m_wPollEpID, m_ptCurAddr->m_wPollIndx);

	u16 wIndex = 0;
	u16 byInnerIndex = 0;

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_ptCurAddr->m_aptLocalAddr[wIndex] )
		{
			continue;
		}
		msgprintnotime("   LocalAddr(Rtp:"ADDRPORT_FORMAT", Rtcp:"ADDRPORT_FORMAT"), RmtRtcp"ADDRPORT_FORMAT")\n", 
			ADDRNET(m_ptCurAddr->m_aptLocalAddr[wIndex]->m_tRtpAddr), ADDRNET(m_ptCurAddr->m_aptLocalAddr[wIndex]->m_tBackRtcpAddr),
			ADDRNET(m_ptCurAddr->m_atRmtRtcp[wIndex]));

		if ( NULL == m_ptCurAddr->m_aptSmallAddr[wIndex] )
		{
			continue;
		}
		msgprintnotime("   SmallAddr(Rtp:"ADDRPORT_FORMAT", Rtcp:"ADDRPORT_FORMAT"), RmtRtcp"ADDRPORT_FORMAT")\n", 
			ADDRNET(m_ptCurAddr->m_aptSmallAddr[wIndex]->m_tRtpAddr), ADDRNET(m_ptCurAddr->m_aptSmallAddr[wIndex]->m_tBackRtcpAddr),
			ADDRNET(m_ptCurAddr->m_atSmallRmtRtcp[wIndex]));
	}

	msgprintnotime("\n");

	msgprintnotime(" OldInfo  EpID:%d, PollIndx:%d\n", m_ptOldAddr->m_wPollEpID, m_ptOldAddr->m_wPollIndx);
	
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_ptOldAddr->m_aptLocalAddr[wIndex] )
		{
			continue;
		}
		msgprintnotime("   LocalAddr(Rtp:"ADDRPORT_FORMAT", Rtcp:"ADDRPORT_FORMAT"), RmtRtcp"ADDRPORT_FORMAT")\n", 
			ADDRNET(m_ptOldAddr->m_aptLocalAddr[wIndex]->m_tRtpAddr), ADDRNET(m_ptOldAddr->m_aptLocalAddr[wIndex]->m_tBackRtcpAddr),
			ADDRNET(m_ptOldAddr->m_atRmtRtcp[wIndex]));

		if ( NULL == m_ptOldAddr->m_aptSmallAddr[wIndex] )
		{
			continue;
		}
		msgprintnotime("   SmallAddr(Rtp:"ADDRPORT_FORMAT", Rtcp:"ADDRPORT_FORMAT"), RmtRtcp"ADDRPORT_FORMAT")\n", 
			ADDRNET(m_ptOldAddr->m_aptSmallAddr[wIndex]->m_tRtpAddr), ADDRNET(m_ptOldAddr->m_aptSmallAddr[wIndex]->m_tBackRtcpAddr),
			ADDRNET(m_ptOldAddr->m_atSmallRmtRtcp[wIndex]));
	}


	msgprintnotime("\n");

	if ( NULL != m_pcPollVmp )
	{
		CUmsConfInst::GetVmpServiceHandle()->Show(m_pcPollVmp);
		msgprintnotime("\n");
	}

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_aptLocalChair[wIndex] )
		{
			continue;
		}
		msgprintnotime("  Smooth PollAddr%d Rtp:"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT"\n",
			wIndex, ADDRNET(m_aptLocalChair[wIndex]->m_tRtpAddr),ADDRNET(m_aptLocalChair[wIndex]->m_tBackRtcpAddr)
			);
	}

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_apcBasRes[wIndex] )
		{
			continue;
		}

#ifdef _USE_XMPUEQP_

		msgprintnotime("Bas%d, EqpID:%d, State:%d(0:idle;1:start;2:run)\n",
			wIndex, m_apcBasRes[wIndex]->GetBasEqpId(), m_apcBasRes[wIndex]->m_tXmpuBas.m_emStat);

	    if (m_apcBasRes[wIndex]->m_tXmpuBas.m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("  InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_apcBasRes[wIndex]->m_tXmpuBas.m_tDecMiddleRtpAddr.GetIP()),
				m_apcBasRes[wIndex]->m_tXmpuBas.m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_apcBasRes[wIndex]->m_tXmpuBas.m_tDecRtcpAddr.GetIP()),
				m_apcBasRes[wIndex]->m_tXmpuBas.m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_apcBasRes[wIndex]->m_tXmpuBas.m_tDecRtpAddr.GetIP()),
				m_apcBasRes[wIndex]->m_tXmpuBas.m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < 1; byInnerIndex++)
			{
				msgprintnotime("  OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(m_apcBasRes[wIndex]->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetIP()), m_apcBasRes[wIndex]->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_apcBasRes[wIndex]->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), m_apcBasRes[wIndex]->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_apcBasRes[wIndex]->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetIP()), m_apcBasRes[wIndex]->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
			}
		}
        
#else
		msgprintnotime("Bas%d, EqpID:%d, ChnlIndx:%d, Ds:"TPIPFORMAT" UmsStartPort:%d, EqpStartPort:%d\n",
			 wIndex, m_apcBasRes[wIndex]->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
			 m_apcBasRes[wIndex]->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx,
			u32ToIP(m_apcBasRes[wIndex]->m_tBasEqpRes.m_tBasChnInfo.m_dwMediaIP), 
			m_apcBasRes[wIndex]->m_tBasEqpRes.m_tBasChnInfo.m_wUmsStartPort,
			m_apcBasRes[wIndex]->m_tBasEqpRes.m_tBasChnInfo.m_wEqpStartPort
			);
#endif
	}

	msgprintnotime("\n");

	msgprintnotime(" PollList Num:%d, TimeInterval:%d\n\n", m_tCfg.m_wNum, m_tCfg.m_wInterval);
	u16 wPrintNum = 0;
	for ( wIndex = 0; wIndex < TP_CONF_MAX_CNSNUM; wIndex ++ )
	{
		if ( NULL == m_tCfg.m_apcNode[wIndex] )
		{
			continue;
		}
		
		msgprintnotime(" EpID:%d ", m_tCfg.m_apcNode[wIndex]->m_wEpID);

		wPrintNum ++;
		
		if ( wPrintNum%10 != 0 )
		{
			msgprintnotime("\n");
		}
	}

	if ( m_bPrint )
	{
		m_bPrint = FALSE;
	}
	else
	{
		m_bPrint = TRUE;
	}

	msgprintnotime("\n\n ===PollMgr ConfID:%d End ===\n\n", Inst()->GetInsID());
	
	return ;
}

void CPollMgr::ResetMediaIp()
{
	CUmsConfInst* pInst = Inst();
	
	u32 dwEqpIP = pInst->GetConfEqpDs().m_dwEqpIp;
	
	u16 wIndex;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		m_tAddrOne.m_aptLocalAddr[wIndex]->SetIP(dwEqpIP);
		m_tAddrTwo.m_aptLocalAddr[wIndex]->SetIP(dwEqpIP);
		m_tAddrOne.m_aptSmallAddr[wIndex]->SetIP(dwEqpIP);
		m_tAddrTwo.m_aptSmallAddr[wIndex]->SetIP(dwEqpIP);
	}
}

void CPollMgr::InitPollList( const TConfTurnList* ptList )
{
	if ( m_emStat != EmPollStat_Stop )
	{
		return;
	}

	CUmsConfInst* pInst = Inst();
	
	u16 wIndex = 0;
	u16 wEpID = TP_INVALID_INDEX;
	TCallNode* ptNode;
	CCallNodeMgr* pcNodeMgr = pInst->m_pcNodeMgr;
	
	m_tCfg.Clear();

	if (NULL != ptList && ptList->m_wNum > 0)
	{
		m_bIsDefaultPoll = TRUE;

		for (wIndex = 0; wIndex < ptList->m_wNum; ++wIndex)
		{
			wEpID = ptList->m_awList[wIndex] + 1;
			ptNode = pcNodeMgr->GetNode(wEpID);
			if (NULL != ptNode && ptNode->m_wEpID != pInst->chairID())
			{
				if ( ptNode->IsVRS() )
				{
					continue;
				}
				ptNode->m_bInPoll = TRUE;
				m_tCfg.m_apcNode[m_tCfg.m_wNum] = ptNode;
				m_tCfg.m_wNum++;
			}
		}
	}
	else
	{
		u16 awAllEpID[TP_CONF_MAX_CNSNUM] = {0};
		u16 wEpAllNum = pcNodeMgr->GetAllNode(awAllEpID, TP_CONF_MAX_CNSNUM );
		for (wIndex = 0; wIndex < wEpAllNum; ++wIndex)
		{
			TCallNode* ptNode = pcNodeMgr->GetNode(awAllEpID[wIndex]);
			if(!ptNode->m_bUsed || ptNode->m_wEpID == pInst->chairID())
			{
				continue;
			}
			
			if ( ptNode->IsVRS() )
			{
				continue;
			}
			
			ptNode->m_bInPoll = TRUE;
			m_tCfg.m_apcNode[m_tCfg.m_wNum] = ptNode;
			m_tCfg.m_wNum++;
		}
	}

	m_tCfg.SetInterval(ptList->m_wInterval);
	
	m_emUiStat = ptList->m_bPollOn ? EmPollStat_Start : EmPollStat_Stop;

	BOOL32 bError = FALSE;
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		m_tAddrOne.m_aptLocalAddr[wIndex] = Inst()->GetPollAddrList()->AllocNode();
		if ( NULL == m_tAddrOne.m_aptLocalAddr[wIndex] )
		{
			bError = TRUE;
			break;
		}
// 		else
// 		{
// 			m_tAddrOne.m_aptLocalAddr[wIndex]->SetIP(Inst()->GetConfEqpDs().m_dwEqpIp);
// 		}
		m_tAddrTwo.m_aptLocalAddr[wIndex] = Inst()->GetPollAddrList()->AllocNode();
		if ( NULL == m_tAddrTwo.m_aptLocalAddr[wIndex] )
		{
			bError = TRUE;
			break;
		}
// 		else
// 		{
// 			m_tAddrTwo.m_aptLocalAddr[wIndex]->SetIP(Inst()->GetConfEqpDs().m_dwEqpIp);
// 		}

		m_tAddrOne.m_aptSmallAddr[wIndex] = Inst()->GetPollAddrList()->AllocNode();
		if ( NULL == m_tAddrOne.m_aptSmallAddr[wIndex] )
		{
			bError = TRUE;
			break;
		}
// 		else
// 		{
// 			m_tAddrOne.m_aptSmallAddr[wIndex]->SetIP(Inst()->GetConfEqpDs().m_dwEqpIp);
// 		}
		m_tAddrTwo.m_aptSmallAddr[wIndex] = Inst()->GetPollAddrList()->AllocNode();
		if ( NULL == m_tAddrTwo.m_aptSmallAddr[wIndex] )
		{
			bError = TRUE;
			break;
		}
// 		else
// 		{
// 			m_tAddrTwo.m_aptSmallAddr[wIndex]->SetIP(Inst()->GetConfEqpDs().m_dwEqpIp);
// 		}
	}

	if ( bError )
	{
		StopConf();
		m_emStat = EmPollStat_Error;
		MdlError(Ums_Mdl_Call, ("InitPollList. Aloc Addr Fail! ConfID:%d\n", Inst()->GetInsID()));
		return ;
	}

	m_bPrint = FALSE;

	ResetMediaIp();
}

void CPollMgr::InitPollList()
{
	if ( m_emStat != EmPollStat_Stop )
	{
		return;
	}
	
	CUmsConfInst* pInst = Inst();
	
	TCallNode* ptNode = NULL;
	TCapNode* ptFartherNode = NULL;
	CCallNodeMgr* pcNodeMgr = pInst->m_pcNodeMgr;
	
	m_tCfg.Clear();
	
	for (u16 wIndex = 0; wIndex < m_tUiListTemp.m_wTotalNum; ++wIndex)
	{
		ptNode = pcNodeMgr->GetNode(m_tUiListTemp.m_awList[wIndex]);
		ptFartherNode = pcNodeMgr->GetForeFatherNode(ptNode);
		if (NULL != ptNode && ptNode->m_wEpID != pInst->chairID()
			&& ptNode->m_bUsed && NULL != ptFartherNode && ptFartherNode->m_bUsed)
		{
			if ( ptNode->IsVRS() || (ptFartherNode->IsMcu() && ptNode!=ptFartherNode))
			{// vrs不加人轮询
			 // （mcu合并级联）mcu可以加入轮询，mcu下级的会场不加入轮询
				continue;
			}
			ptNode->m_bInPoll = TRUE;
			m_tCfg.m_apcNode[m_tCfg.m_wNum] = ptNode;
			m_tCfg.m_wNum++;
		}
	}
	m_tCfg.SetInterval(m_tUiListTemp.m_wInterval);
}

void CPollMgr::OnChanConnect( TCallNode* ptNode )
{
	if ( !Inst()->IsChairConf() )
	{
		return ;
	}

	if ( m_emStat == EmPollStat_Error )
	{
		return ;
	}

	if ( NULL == ptNode )
	{
		return ;
	}

	if ( ptNode->m_wEpID != Inst()->chairID() )
	{//非主席上线

		if(!Inst()->IsChairConf())
		{
			return ;
		}

		if ( ptNode->IsVRS() )
		{
			m_tCfg.RemoveOneEp(ptNode->m_wEpID);

			NotifyPollListToUI();
			return;
		}

		if ( m_emStat == EmPollStat_Suspend
			&& m_emUiStat == EmPollStat_Start )
		{
			PollNextEp();
		}
	}
	else
	{
		m_tChairFmt.Clear();

		BOOL32 bNeed = FALSE;
		for (u16 wIndex = 0 ; wIndex < Inst()->m_tConfBaseInfo.m_wMainNum; wIndex ++ )
		{
			if(CTpTypeAdpt::IsVidTransNeedBas( Inst()->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex], ptNode->m_tVidRcvFormat.m_tFormat))
			{//到主席 有需要适配的 则需要申请适配资源
				bNeed = TRUE;
				break;
			}
		}
		
		m_bBas = bNeed;
		m_tChairFmt = ptNode->m_tVidRcvFormat;

		if ( m_emUiStat == EmPollStat_Start )
		{
			do 
			{
				EmTPPollResult emRet = StartPoll();
				if (emPollSucceed == emRet)
				{
					break;
				}

				if (emPollInvalidEp == emRet)
				{// 主席上线，轮询没有开启成功，原因是无有效轮询会场，则状态置为暂停，等待其他会场上线，开启轮询
					m_emStat = EmPollStat_Suspend;
					break;
				}

				// 开启失败，界面状态也更新为停止
				m_emUiStat = EmPollStat_Stop;

				// 提示
				TUmsHandle tOutHandle;
				Inst()->m_pcNodeMgr->MakeCallerHandle(tOutHandle, Inst()->chairID());
				UmsSendConfCtrl(tOutHandle, evtp_Conf_StartPoll_Ind, &emRet, sizeof(emRet));

			} while (0);
		}
		
		NotifyPollStatToUI();
		NotifyPollListToUI();
	}
	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnChanConnect. ConfID:%d, stat:%s, EpID:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), ptNode->m_wEpID));

	return ;
}

void CPollMgr::OnHungup( TCallNode* ptNode )
{
	if ( !Inst()->IsChairConf() )
	{
		return ;
	}

	if ( m_emStat == EmPollStat_Error )
	{
		return ;
	}

	if ( NULL == ptNode )
	{
		return ;
	}

	if ( m_emStat == EmPollStat_Stop )
	{
		return ;
	}

	if ( ptNode->m_wEpID == Inst()->chairID() )
	{//主席掉线 清掉
		m_bBas = FALSE;
		m_tChairFmt.Clear();
		StopPoll();
	}
	else
	{
		if ( m_ptCurAddr->m_wPollEpID == ptNode->m_wEpID )
		{//当前轮询结点掉线 找下一个
			KillTimer(evtp_ExeTurnList_time);

			if ( m_emStat == EmPollStat_Start )
			{
				//置为无效，不用做平滑
				m_ptCurAddr->m_wPollEpID = TP_INVALID_INDEX;

				BOOL32 bTempOpen = ptNode->m_bChannelOpen;
				ptNode->m_bChannelOpen = FALSE;
				
				PollNextEp();	
					
				ptNode->m_bChannelOpen = bTempOpen;
			}
		}
	}

	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnHungup. ConfID:%d, stat:%s, EpID:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), ptNode->m_wEpID));

	return ;
}

void CPollMgr::OnCncStartPollReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());

	EmTPPollResult emRet = emPollSucceed;
	do
	{
		if ( tHandle.GetEpID() != Inst()->chairID() )
		{
			emRet = emPollNoChair;
			break ;
		}

		emRet = StartPoll();

		if ( emRet == emPollSucceed )
		{
			m_emUiStat = EmPollStat_Start;
		}
		NotifyPollStatToUI();
		NotifyPollListToUI();

	}while(0);

	TUmsHandle tOutHandle;
	Inst()->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, evtp_Conf_StartPoll_Ind, &emRet, sizeof(emRet));
	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnCncStartPollReq. ConfID:%d, stat:%s, ret:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), emRet));

	return ;
}

void CPollMgr::OnUmcStartPollReq( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	TTpPollInterval tInterval;
	TP_SAFE_CAST(tInterval, ptMsg->GetBody() + sizeof(tUsr));

	m_tCfg.SetInterval(tInterval.m_wInterval);
	EmTPPollResult emRet = StartPoll();
	if ( emRet == emPollSucceed )
	{
		m_emUiStat = EmPollStat_Start;
	}
	NotifyPollStatToUI();
	NotifyPollListToUI();

	u8 byBuf[sizeof(TLogUser) + sizeof(u16) + sizeof(EmTPPollResult)] = {0};
	memcpy(byBuf, &tUsr, sizeof(TLogUser));
	memcpy(byBuf + sizeof(TLogUser), &(tInterval.m_wConfID), sizeof(u16));
	memcpy(byBuf + sizeof(TLogUser) + sizeof(u16), &emRet, sizeof(EmTPPollResult));
	
	Inst()->NotifyMsgToService(evtp_StartTurn_ind, byBuf, sizeof(byBuf));
	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnUmcStartPollReq. ConfID:%d, stat:%s, ret:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), emRet));
}

void CPollMgr::OnCncSuspendPollReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	BOOL32	bSuspend;
	TP_SAFE_CAST(bSuspend, ptMsg->GetBody() + sizeof(tHandle));
	
	EmTPPollResult emRet = emPollSucceed;
	do
	{
		if ( tHandle.GetEpID() != Inst()->chairID() )
		{
			emRet = emPollNoChair;
			break ;
		}
		
		emRet = SuspendPoll(bSuspend);

		if ( emRet == emPollSucceed )
		{
			m_emUiStat = bSuspend ? EmPollStat_Suspend : EmPollStat_Start;
		}
		
		NotifyPollStatToUI();
		
	}while(0);
	
	TUmsHandle tOutHandle;
	Inst()->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, evtp_Conf_SuspendPoll_Ind, &emRet, sizeof(emRet));
	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnCncSuspendPollReq. ConfID:%d, stat:%s, ret:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), emRet));
}

void CPollMgr::OnUmcSuspendPollReq( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	u16 wConfID;
	TP_SAFE_CAST(wConfID, ptMsg->GetBody() + sizeof(tUsr));
	BOOL32	bSuspend;
	TP_SAFE_CAST(bSuspend, ptMsg->GetBody() + sizeof(wConfID) + sizeof(tUsr));
	
	EmTPPollResult emRet = SuspendPoll(bSuspend);
	if ( emRet == emPollSucceed )
	{
		m_emUiStat = bSuspend ? EmPollStat_Suspend : EmPollStat_Start;
	}
	NotifyPollStatToUI();
	
	u8 byBuf[sizeof(TLogUser) + sizeof(u16) + sizeof(EmTPPollResult)] = {0};
	memcpy(byBuf, &tUsr, sizeof(TLogUser));
	memcpy(byBuf + sizeof(TLogUser), &wConfID, sizeof(u16));
	memcpy(byBuf + sizeof(TLogUser) + sizeof(u16), &emRet, sizeof(EmTPPollResult));
	
	Inst()->NotifyMsgToService(evtp_SuspendTurn_ind, byBuf, sizeof(byBuf));
	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnUmcSuspendPollReq. ConfID:%d, stat:%s, ret:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), emRet));
}

void CPollMgr::OnUmcStopPollReq( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	u16 wConfID;
	TP_SAFE_CAST(wConfID, ptMsg->GetBody() + sizeof(tUsr));
	
	EmTPPollResult emRet = StopPoll();
	if ( emRet == emPollSucceed )
	{
		m_emUiStat = EmPollStat_Stop;
	}
	NotifyPollStatToUI();

	u8 byBuf[sizeof(TLogUser) + sizeof(u16) + sizeof(EmTPPollResult)] = {0};
	memcpy(byBuf, &tUsr, sizeof(TLogUser));
	memcpy(byBuf + sizeof(TLogUser), &wConfID, sizeof(u16));
	memcpy(byBuf + sizeof(TLogUser) + sizeof(u16), &emRet, sizeof(EmTPPollResult));
	
	Inst()->NotifyMsgToService(evtp_StopTurn_ind, byBuf, sizeof(byBuf));
	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnUmcStopPollReq. ConfID:%d, stat:%s, ret:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), emRet));
}

void CPollMgr::OnCncStopPollReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	
	EmTPPollResult emRet = emPollSucceed;
	do
	{
		if ( tHandle.GetEpID() != Inst()->chairID() )
		{
			emRet = emPollNoChair;
			break ;
		}
		
		emRet = StopPoll();
		if ( emRet == emPollSucceed )
		{
			m_emUiStat = EmPollStat_Stop;
		}
		NotifyPollStatToUI();
		
	}while(0);
	
	TUmsHandle tOutHandle;
	Inst()->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, evtp_Conf_StopPoll_Ind, &emRet, sizeof(emRet));
	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnCncStopPollReq. ConfID:%d, stat:%s, ret:%d\n", Inst()->GetInsID(), GetStatPrint(m_emStat), emRet));
}

void CPollMgr::OnUpdatePollListFromUmc( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());

	TTpPollListNtfy tList;
	TP_SAFE_CAST(tList, ptMsg->GetBody()+ sizeof(TLogUser));

	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnUpdatePollListFromUmc. ConfID:%d, flag:%d, totalnum:%d, curnum:%d,Interval:%d\n", 
										Inst()->GetInsID(), tList.m_nFlag, tList.m_wTotalNum, tList.m_wCurNum,tList.m_wInterval));

	TTpPollListInd tInd;
	if ( !Inst()->IsChairConf() )
	{//下级 不能编辑
		tInd.m_wConfID = Inst()->GetInsID();
		tInd.m_wRet = TP_RET_ERROR;
	//	Inst()->NotifyMsgToService(evtp_UpdateTurn_ind, &tInd, sizeof(tInd));
		Inst()->NotifyMsgToServiceForUI(evtp_UpdateTurn_ind, &tInd, sizeof(tInd),&tUsr);
		return ;
	}

	BOOL32 bNtfy = UpdatePollList(tList, tInd);

	Inst()->NotifyMsgToServiceForUI(evtp_UpdateTurn_ind, &tInd, sizeof(tInd),&tUsr);

	if ( bNtfy )
	{
		NotifyPollListToUI();
	}

	return ;
}

void CPollMgr::OnUpdatePollListFromCnc( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TTpPollListNtfy tList;
	TP_SAFE_CAST(tList, ptMsg->GetBody() + sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnUpdatePollListFromCnc. ConfID:%d, EpID:%d, flag:%d, totalnum:%d, curnum:%d\n", 
										Inst()->GetInsID(), tHandle.GetEpID(), tList.m_nFlag, tList.m_wTotalNum, tList.m_wCurNum));

	TUmsHandle tOutHandle;
	Inst()->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());

	TTpPollListInd tInd;
	if ( !Inst()->IsChairConf() )
	{//下级 不能编辑
		tInd.m_wConfID = Inst()->GetInsID();
		tInd.m_wRet = TP_RET_ERROR;
		UmsSendConfCtrl(tOutHandle, ev_UmsUpdateConfTurnlist_Ind, &tInd, sizeof(tInd));
		return ;
	}

	if ( tHandle.GetEpID() == Inst()->chairID() )
	{//主席来更新

		BOOL32 bNtfy = UpdatePollList(tList, tInd);
		
		UmsSendConfCtrl(tOutHandle, ev_UmsUpdateConfTurnlist_Ind, &tInd, sizeof(tInd));
		
		if ( bNtfy )
		{
			NotifyPollListToUI();
		}
	}
	else
	{//下级来更新
		TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(tHandle.GetEpID());
		if ( NULL == ptNode )
		{
			MdlError(Ums_Mdl_Call, ("OnUpdatePollListFromCnc tHandle.GetEpID() Invalid ! ConfID:%d, EpID:%d\n", Inst()->GetInsID(), tHandle.GetEpID()));
			return;
		}

		if ( ptNode->IsUms() )
		{//上级收到下级轮询信息
			u16 wPollIndex = m_tCfg.FindIndexByEp(ptNode->m_wEpID);
			if ( !TP_VALID_HANDLE(wPollIndex) )
			{
				return ;
			}

			u16	wPollNum = 0;
			TCallNode* aptCallNode[TP_CONF_MAX_CNSNUM] = { NULL };
			//该下级存在 则将子结点插入
			for (u16 wIndex = 0; wIndex < tList.m_wCurNum; ++wIndex)
			{
				TCallNode* pTempNode = Inst()->m_pcNodeMgr->GetNodeByChildEpID( ptNode, tList.m_awList[wIndex]);
				if (NULL != pTempNode && pTempNode->m_wEpID != Inst()->chairID())
				{
					if ( pTempNode->IsVRS() )
					{
						continue;
					}



					aptCallNode[wPollNum] = pTempNode;
					wPollNum++;
				}
			}

			if ( wPollNum + m_tCfg.m_wNum > TP_CONF_MAX_CNSNUM )
			{
				return ;
			}

			MdlHint(Ums_Mdl_Call, ("CPollMgr::OnUpdatePollListFromCnc. PollNum:%d, PollEpID:%d\n", 
										wPollNum, tHandle.GetEpID(), tList.m_awList[0]));

			if ( wPollNum < 1 )
			{

				return ;
			}

			m_tCfg.m_wNum--;//把下级UMS给删除
			m_tCfg.m_wNum += wPollNum;
			memmove(&(m_tCfg.m_apcNode[wPollIndex+wPollNum]), &(m_tCfg.m_apcNode[wPollIndex+1]), sizeof(m_tCfg.m_apcNode[0])*(m_tCfg.m_wNum - wPollIndex - 1));
			memcpy(&(m_tCfg.m_apcNode[wPollIndex]), aptCallNode, sizeof(aptCallNode[0])*wPollNum);

			NotifyPollListToUI();
		}
	}

	return ;
}


BOOL32 CPollMgr::IsAddEpInPollList(TCallNode* ptNodeAdd)
{
	if (NULL == ptNodeAdd)
	{
        return FALSE;
	}

	u16 wIndex = 0;
	for (wIndex = 0; wIndex < m_tCfg.m_wNum; wIndex++)
	{
		if (NULL != m_tCfg.m_apcNode[wIndex] && ptNodeAdd->m_wEpID == m_tCfg.m_apcNode[wIndex]->m_wEpID)
		{
            return  TRUE;
		}
	}


	return FALSE;
}

void CPollMgr::AddLowInviteEp(TCallNode* ptNodeAdd)
{
	if (NULL == ptNodeAdd)
	{
        return;
	}

	if ( !Inst()->IsChairConf() )
	{
		return;
	}

	u16 wIndex = 0;

	if ( 1 + m_tCfg.m_wNum > TP_CONF_MAX_CNSNUM )
	{   //列表已满
		return ;
	}


    TCapNode* tAddEpFarther = Inst()->m_pcNodeMgr->GetForeFatherNode(ptNodeAdd);
	if (NULL == tAddEpFarther)
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::AddLowInviteEp. ConfID:%d, ep:%d  farther is NULL\n", Inst()->GetInsID(), ptNodeAdd->m_wEpID));
        return ;
	}


	TCapNode* tTempFarther = NULL;
    u16 wInsertIndex = TP_INVALID_INDEX;
    for (wIndex = 0; wIndex < m_tCfg.m_wNum; wIndex++)
	{

		if (NULL != m_tCfg.m_apcNode[wIndex])
		{
			if (m_tCfg.m_apcNode[wIndex]->m_wEpID == tAddEpFarther->m_wEpID  ||
				m_tCfg.m_apcNode[wIndex]->m_wEpID == ptNodeAdd->m_wEpID)
			{  //（1）下级UMS 还在上级轮询列表中,下级轮询列表的noty 消息还没有来，本会场将通过轮询notify来通知
			   //（2）会场已经在列表中
			   return;	
			}		
		} 
		else 
		{
			continue;
		}

		
        tTempFarther = Inst()->m_pcNodeMgr->GetForeFatherNode(m_tCfg.m_apcNode[wIndex]);
        if (tTempFarther == tAddEpFarther)
		{
            wInsertIndex = wIndex;  //后插
		}

	}


    if (TP_INVALID_INDEX == wInsertIndex)
	{   //没有找到同一级的会场, 加到后面
        wInsertIndex = m_tCfg.m_wNum;
		MdlHint(Ums_Mdl_Call, ("CPollMgr::AddLowInviteEp back. ConfID:%d, ep:%d  Inserindex:%d  PollCfgNum:%d\n", 
			                   Inst()->GetInsID(), ptNodeAdd->m_wEpID, wInsertIndex, m_tCfg.m_wNum));

        m_tCfg.m_apcNode[wInsertIndex] = ptNodeAdd;
        m_tCfg.m_wNum++;
		NotifyPollListToUI();
		return; 
	} 

    wInsertIndex++;   //后插	
	MdlHint(Ums_Mdl_Call, ("CPollMgr::AddLowInviteEp  ConfID:%d, ep:%d  Inserindex:%d  PollCfgNum:%d\n", Inst()->GetInsID(), ptNodeAdd->m_wEpID, wInsertIndex, m_tCfg.m_wNum));
	u16 wMoveCt = m_tCfg.m_wNum - wInsertIndex;
	if (wMoveCt)
	{
		memmove(&(m_tCfg.m_apcNode[wInsertIndex + 1]), &(m_tCfg.m_apcNode[wInsertIndex]), sizeof(m_tCfg.m_apcNode[0]) * wMoveCt);
	}
    m_tCfg.m_apcNode[wInsertIndex] = ptNodeAdd;
	m_tCfg.m_wNum++;

    NotifyPollListToUI();
    return;
}



BOOL32 CPollMgr::UpdatePollList( TTpPollListNtfy& tList, TTpPollListInd& tInd )
{
	tInd.m_wConfID = Inst()->GetInsID();
	tInd.m_wRet = TP_RET_OK;
	
	if (IsPollStart())
	{// 轮询中不能更新轮询列表
		tInd.m_wRet = TP_RET_ERROR;
		m_tUiListTemp.Clear();
		return FALSE;
	}
	
	BOOL32 bNtfy = FALSE;
	if ( !m_tUiListTemp.m_wUpdate )
	{
		time_t CurTime;
		time(&CurTime);
		tInd.m_nFlag = CurTime;
		m_tUiListTemp.m_dwFlag = tInd.m_nFlag;
		m_tUiListTemp.m_wUpdate = TRUE;
	}
	else
	{
		tInd.m_nFlag = tList.m_nFlag;
	}

	if ( tInd.m_nFlag == m_tUiListTemp.m_dwFlag )
	{
		bNtfy = UpdatePollTempList(tList);
	}
	else
	{
		time_t CurTime;
		time(&CurTime);
		if ( CurTime - m_tUiListTemp.m_dwFlag > 5 )
		{//上一次 超时，清除掉，重新接收
			m_tUiListTemp.Clear();

			m_tUiListTemp.m_dwFlag = tInd.m_nFlag;
			m_tUiListTemp.m_wUpdate = TRUE;
			tInd.m_nFlag = CurTime;
			bNtfy = UpdatePollTempList(tList);
		}
		else
		{
			tInd.m_wRet = TP_RET_ERROR;
		}
	}

	if (bNtfy)
	{// 已经接收完成了
		tInd.m_wCurRcvNum = tList.m_wTotalNum;
	}
	else
	{
		tInd.m_wCurRcvNum = m_tUiListTemp.m_wCurNum;
	}

	return bNtfy;
}

void CPollMgr::OnCasecadePollEpReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TCasecadePollEpReq tReq;
	TP_SAFE_CAST(tReq, ptMsg->GetBody() + sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnCasecadePollEpReq. ConfID:%d, Req EpID:%d, Create:%d\n", Inst()->GetInsID(), tReq.m_wEpID, tReq.m_bCreate));
	MdlHint(Ums_Mdl_Call, (" Rtp0:"ADDRPORT_FORMAT", Rtp1:"ADDRPORT_FORMAT", Rtp2:"ADDRPORT_FORMAT"\n", 
							ADDRNET(tReq.m_atPollAddr[0]), ADDRNET(tReq.m_atPollAddr[1]), ADDRNET(tReq.m_atPollAddr[2]) ));

	TCasecadePollEpRsp tRsp;
	memcpy(&tRsp.m_tReq, &tReq, sizeof(tReq));

	tRsp.m_emRes = emPollSucceed;
	do 
	{
		TCallNode* ptPoll = Inst()->GetNodeMgr()->GetNode(tReq.m_wEpID);
		TCapNode* ptPollCap = Inst()->GetNodeMgr()->GetForeFatherNode(tReq.m_wEpID);
		if( NULL == ptPoll || NULL == ptPollCap )
		{
			tRsp.m_emRes = emPollInvalidEp;
			break ;
		}

		if ( tReq.m_bCreate )
		{
			if( !ptPoll->IsChanOn() )
			{
				tRsp.m_emRes = emPollInvalidEp;
				break ;
			}

			u32 dwCurBw = 0;
			if( ptPoll->GetSndBW() > m_dwBw )
			{//新会场需要额外占用带宽
				dwCurBw = ptPoll->GetSndBW() - m_dwBw;
				if ( !Inst()->GetBandWidth().AssigneUpBW(dwCurBw, em_View_Poll) )
				{//为新会场申请增加的部分
					tRsp.m_emRes = emPollResFull_Bw;
					MdlError(Ums_Mdl_Call, ("OnCasecadePollEpReq no UpBw! ConfID:%d, AssignBw:%d, CurBw:%d\n", 
						Inst()->GetInsID(), dwCurBw, Inst()->GetBandWidth().CurUpBw()));
					break;
				}
			}
			else
			{//需要释放一部分
				Inst()->GetBandWidth().ReleaseUpBW(m_dwBw - ptPoll->GetSndBW(), em_View_Poll);
			}

			m_dwBw = ptPoll->GetSndBW();

			if( ptPoll != ptPollCap )
			{//下下级 需要申请下行带宽
				if ( !Inst()->GetBandWidth().AssigneDownBW(ptPoll->GetSndBW(), em_View_Poll) )
				{
					MdlError(Ums_Mdl_Call, ("OnCasecadePollEpReq no DownBw! ConfID:%d, AssignBw:%d, CurBw:%d\n", 
									Inst()->GetInsID(), ptPoll->GetSndBW(), Inst()->GetBandWidth().CurDownBw()));

					Inst()->GetBandWidth().ReleaseUpBW(m_dwBw, em_View_Poll);
					m_dwBw = 0;
					tRsp.m_emRes = emPollResFull_Bw;
					break;
				}
			}

			TCapNode* ptCaller = Inst()->GetNodeMgr()->GetCaller();
			if ( NULL == ptCaller || !ptCaller->IsChanOn() )
			{
				if( ptPoll != ptPollCap )
				{
					Inst()->GetBandWidth().ReleaseDownBW(ptPoll->GetSndBW(), em_View_Poll);
				}
				Inst()->GetBandWidth().ReleaseUpBW(m_dwBw, em_View_Poll);
				m_dwBw = 0;
				tRsp.m_emRes = emPollChairNoLine;
				break;
			}

			if ( CTpTypeAdpt::IsVidTransNeedBas(ptPollCap->m_tVidSndFormat.m_tFormat, ptCaller->m_tVidRcvFormat.m_tFormat) )
			{//需要适配
				CScreenBasRes*	apcBasRes[TP_MAX_STREAMNUM] = {NULL};
				
				BOOL32 bError = FALSE;
				ForEachChanList(ptPoll->m_wVidRcvNum,
					if ( NULL != m_apcBasRes[ewIndex] )
					{
						continue;
					}
					if(!Inst()->GetBas()->AssignScreenBas(apcBasRes[ewIndex]))
					{
						bError = TRUE;
						break;
					}
					Inst()->GetBas()->AdjustScreenBas(apcBasRes[ewIndex], ptPoll->m_wEpID, ewIndex, 1, 
																	&ptCaller->m_tVidRcvFormat.m_tFormat);
					apcBasRes[ewIndex]->SetCB(PollBasCB, this);
					);

				if( bError )
				{
					ForEachChanList(TP_MAX_STREAMNUM,
						if ( NULL == apcBasRes[ewIndex] )
						{
							continue;
						}
						Inst()->GetBas()->ReleaseScreenBas(apcBasRes[ewIndex]);
						apcBasRes[ewIndex] = NULL);
					
					if( ptPoll != ptPollCap )
					{
						Inst()->GetBandWidth().ReleaseDownBW(ptPoll->GetSndBW(), em_View_Poll);
					}
					Inst()->GetBandWidth().ReleaseUpBW(m_dwBw, em_View_Poll);
					m_dwBw = 0;
					
					MdlError(Ums_Mdl_Call, ("OnCasecadePollEpReq no BasEqp! ConfID:%d\n", Inst()->GetInsID()));
					tRsp.m_emRes = emPollResFull_Bas;
					break ;
				}

				//新老数据合并 等待平滑结束 再尝试释放不需要的适配通道
				ForEachChanList(TP_MAX_STREAMNUM,
						if( NULL != apcBasRes[ewIndex] )
						{
							m_apcBasRes[ewIndex] = apcBasRes[ewIndex];
						}
						);
			}
			else
			{
				ForEachChanList(TP_MAX_STREAMNUM,
					if ( NULL == m_apcBasRes[ewIndex] )
					{
						continue;
					}
					Inst()->GetBas()->ReleaseScreenBas(m_apcBasRes[ewIndex]);
					m_apcBasRes[ewIndex] = NULL);
			}

			u16 wIndex = 0;
			for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			{//保存上级Rtp
				m_atRmtRtp[wIndex] = tReq.m_atPollAddr[wIndex];
				m_atSmallRmtRtp[wIndex] = tReq.m_atSmallAddr[wIndex];
			}

			CreatePollEpMedia(tReq.m_wEpID, TP_INVALID_INDEX);

			if ( ptPoll == ptPollCap )
			{//本级 开始上报
				for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
				{//取最新的当前rtcp 给上级
					tRsp.m_tReq.m_atPollAddr[wIndex] = m_ptCurAddr->m_aptLocalAddr[wIndex]->m_tBackRtcpAddr;
					tRsp.m_tReq.m_atSmallAddr[wIndex] = m_ptCurAddr->m_aptSmallAddr[wIndex]->m_tBackRtcpAddr;
				}
				TUmsHandle tOutHandle;
				Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Rsp, &tRsp, sizeof(tRsp));
			}
		}
		else
		{
			if ( m_ptCurAddr->m_wPollEpID == tReq.m_wEpID )
			{
				m_ptCurAddr->m_wPollEpID = TP_INVALID_INDEX;
			}
			else if ( m_ptOldAddr->m_wPollEpID == tReq.m_wEpID )
			{
				m_ptOldAddr->m_wPollEpID = TP_INVALID_INDEX;
			}
			else
			{
				return ;
			}

			Inst()->GetBandWidth().ReleaseUpBW(m_dwBw, em_View_Poll);
			m_dwBw = 0;

			ForEachChanList(TP_MAX_STREAMNUM, 
				if( NULL != m_apcBasRes[ewIndex] )\
				{Inst()->GetBas()->ReleaseScreenBas(m_apcBasRes[ewIndex]);}
				);
				
			for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			{
				m_atRmtRtp[wIndex].Clear();
				m_atSmallRmtRtp[wIndex].Clear();
			}

			if ( ptPoll != ptPollCap )
			{
				Inst()->GetBandWidth().ReleaseDownBW(ptPoll->GetSndBW(), em_View_Poll);

				//向下级请求拆除
				TCasecadePollEpReq tReq;
				tReq.m_wEpID = ptPoll->m_wLowChildEpID;
				tReq.m_bCreate = FALSE;
				
				TUmsHandle tOutHandle;
				Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptPollCap->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));
			}
			else
			{
				Inst()->m_pcCallMgr->FlowControl(ptPoll->m_wEpID, FLOW_CTROL_ALL_ENC, 0);
			}

			CreatePollEpMedia(m_ptCurAddr->m_wPollEpID, TP_INVALID_INDEX);
		}

	} while (0);

	if ( tRsp.m_emRes != emPollSucceed )
	{
		TUmsHandle tOutHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Rsp, &tRsp, sizeof(tRsp));
	}

	return ;
}

void CPollMgr::OnCasecadePollEpRsp( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TCasecadePollEpRsp tRsp;
	TP_SAFE_CAST(tRsp, ptMsg->GetBody() + sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("CPollMgr::OnCasecadePollEpRsp. ConfID:%d, Rsp EpID:%d, Ret:%d\n", Inst()->GetInsID(), tRsp.m_tReq.m_wEpID, tRsp.m_emRes));
	MdlHint(Ums_Mdl_Call, (" Rtcp0:"ADDRPORT_FORMAT", Rtcp1:"ADDRPORT_FORMAT", Rtcp2:"ADDRPORT_FORMAT"\n", 
							ADDRNET(tRsp.m_tReq.m_atPollAddr[0]), ADDRNET(tRsp.m_tReq.m_atPollAddr[1]), ADDRNET(tRsp.m_tReq.m_atPollAddr[2]) ));

	TCapNode* ptForeNode = Inst()->GetNodeMgr()->GetCapsetNode(tHandle.GetEpID());
	if ( NULL == ptForeNode )
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::OnCasecadePollEpRsp ptSrcCapNode is NULL . ConfID:%d, EpID:%d, handleEpID:%d\n", Inst()->GetInsID(), tRsp.m_tReq.m_wEpID, tHandle.GetEpID()));
		return ;
	}
	
	TCallNode* ptNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tRsp.m_tReq.m_wEpID);
	if ( NULL == ptNode || !ptNode->m_bUsed )
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::OnCasecadePollEpRsp ptNode is NULL . ConfID:%d, EpID:%d\n", Inst()->GetInsID(), tRsp.m_tReq.m_wEpID));
		return ;
	}
	tRsp.m_tReq.m_wEpID = ptNode->m_wEpID;
	
	if ( tRsp.m_emRes == emPollSucceed )
	{//成功才处理
		//向下级请求拆除
		TCasecadePollEpReq tReq;
		tReq.m_wEpID = ptNode->m_wLowChildEpID;
		tReq.m_bCreate = FALSE;

		TUmsHandle tOutHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptForeNode->m_wEpID);
		if ( m_emStat != EmPollStat_Start
			&& m_emUiStat != EmPollStat_Start )
		{
			MdlError(Ums_Mdl_Call, ("CPollMgr::OnCasecadePollEpRsp Poll no Start! ConfID:%d, Stat:%d, UiStat:%d, Ep:%d\n", 
				Inst()->GetInsID(), m_emStat, m_emUiStat, tRsp.m_tReq.m_wEpID));
			
			//上级状态有变 通知下级释放 防止下级泄露
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));

			return ;
		}
		if ( m_ptOldAddr->m_wPollEpID != tRsp.m_tReq.m_wEpID )
		{
			MdlError(Ums_Mdl_Call, ("CPollMgr::OnCasecadePollEpRsp PollEp no Exist! ConfID:%d, EpID:%d, CurEp:%d, OldEp:%d\n", 
				Inst()->GetInsID(), tRsp.m_tReq.m_wEpID, m_ptCurAddr->m_wPollEpID, m_ptOldAddr->m_wPollEpID));

			//上级状态有变 通知下级释放 防止下级泄露
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));

			return ;
		}

		TCallNode* ptCurPoll = Inst()->GetNodeMgr()->GetNode(m_ptCurAddr->m_wPollEpID);
		TCapNode* ptCurPollCap = Inst()->GetNodeMgr()->GetForeFatherNode(m_ptCurAddr->m_wPollEpID);
		if ( NULL == ptCurPoll || NULL == ptCurPollCap )
		{
			MdlError(Ums_Mdl_Call, ("CPollMgr::OnCasecadePollEpRsp curPoll Invalid! ConfID:%d, EpID:%d, CurEp:%d, OldEp:%d\n", 
				Inst()->GetInsID(), tRsp.m_tReq.m_wEpID, m_ptCurAddr->m_wPollEpID, m_ptOldAddr->m_wPollEpID));
		}
		
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{//保存下级rtcp 上报本级rtcp
			if ( ptForeNode != ptCurPollCap && ptCurPollCap != NULL )
			{//不在同一个下级，上级需要平滑，CreatePollEpMedia会切换addr
				m_ptOldAddr->m_atRmtRtcp[wIndex] = tRsp.m_tReq.m_atPollAddr[wIndex];
				tRsp.m_tReq.m_atPollAddr[wIndex] = m_ptOldAddr->m_aptLocalAddr[wIndex]->m_tBackRtcpAddr;
			}
			else
			{//再同一个下级 上级始终使用cur  CreatePollEpMedia里面也不会切换addr
				m_ptCurAddr->m_atRmtRtcp[wIndex] = tRsp.m_tReq.m_atPollAddr[wIndex];
				tRsp.m_tReq.m_atPollAddr[wIndex] = m_ptCurAddr->m_aptLocalAddr[wIndex]->m_tBackRtcpAddr;
			}
		}

		CreatePollEpMedia(m_ptOldAddr->m_wPollEpID, m_ptOldAddr->m_wPollIndx, TRUE);
	}

	if ( !Inst()->IsChairConf() )
	{//非上级，继续上报
		
		TUmsHandle tOutHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Rsp, &tRsp, sizeof(tRsp));
	}
	else
	{//上级收到发现处理失败 则进行下一个
		if ( tRsp.m_emRes != emPollSucceed )
		{
			u32 wReason = TP_UMS_Poll_EpNextBas;
			if ( tRsp.m_emRes == emPollResFull_Bw )
			{
				wReason = TP_UMS_Poll_EpNextBW;
			}
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, wReason, Inst()->chairID(), ptNode->m_wEpID);
		}

		if ( tRsp.m_emRes != emPollSucceed 
			&& m_emStat == EmPollStat_Start
			&& m_emUiStat == EmPollStat_Start )
		{
			m_tFailEpID.SetValue(ptForeNode->m_wEpID, ptNode->m_wVidSndNum);
			PollNextEp(m_ptOldAddr->m_wPollIndx);
		}
		else
		{
			m_ptOldAddr->m_wPollEpID = TP_INVALID_INDEX;
			m_ptOldAddr->m_wPollIndx = TP_INVALID_INDEX;
		}
	}
	
	return;
}

void CPollMgr::OnPollTimer( CTpMsg *const ptMsg )
{

	MdlLowHint(Ums_Mdl_Call, ("OnPollTimer to next pollEp, ConfId:%d, UiStat:%d, Stat:%d.\n", Inst()->GetInsID(), m_emUiStat, m_emStat));

	if (EmPollStat_Start != m_emStat)
	{
		return;
	}
	
	PollNextEp();
	
	return ;
}

EmTPPollResult CPollMgr::StartPoll()
{
	if ( !Inst()->IsChairConf() )
	{
		return emPollNoChair;
	}
	if ( m_emStat == EmPollStat_Error )
	{
		return emPollFailUnKown;
	}

	if ( m_emStat == EmPollStat_Start )
	{
		return emPollSucceed;
	}

	if ( m_tUiListTemp.m_wUpdate )
	{
		return emPollServerBusy;
	}

	TCapNode* ptChair = Inst()->m_pcNodeMgr->GetCapsetNode(Inst()->chairID());
	if (NULL == ptChair || !ptChair->IsChanOn() || !ptChair->IsVidRcvValid() )
	{
		MdlError(Ums_Mdl_Call, ("StartPoll chair failed ConfID:%d, chair:%d\n", Inst()->GetInsID(), Inst()->chairID()));
		return emPollChairNoLine;
	}

// 	if ( !HavePollEp() )
// 	{
// 		MdlError(Ums_Mdl_Call, ("StartPoll not Valid EP! ConfID:%d\n", Inst()->GetInsID()));
// 		return emPollInvalidEp;
// 	}

	if ( ptChair->IsSingleVidRcv() && NULL == m_pcPollVmp)
	{//单屏 占用合成器
		m_pcPollVmp = CUmsConfInst::GetVmpServiceHandle()->Assign(PollVmpCB, Inst());
		if ( NULL == m_pcPollVmp )
		{
			MdlError(Ums_Mdl_Call, ("StartPoll no VmpEqp! ConfID:%d\n", Inst()->GetInsID()));
		}
		m_bVmpStart = FALSE;
	}

	if ( m_bBas && NULL == m_pcPollVmp )
	{
		BOOL32 bError = FALSE;
		ForEachChanList(ptChair->m_wVidRcvNum,
			if(!Inst()->GetBas()->AssignScreenBas(m_apcBasRes[ewIndex]))
			{
				bError = TRUE;
				break;
			}
			Inst()->GetBas()->AdjustScreenBas(m_apcBasRes[ewIndex], ptChair->m_wEpID, ewIndex, 1, 
												&ptChair->m_tVidRcvFormat.m_tFormat);
			m_apcBasRes[ewIndex]->SetCB(PollBasCB, this);
			);
			
		if( bError )
		{
			ForEachChanList(ptChair->m_wVidRcvNum,Inst()->GetBas()->ReleaseScreenBas(m_apcBasRes[ewIndex]));
			MdlError(Ums_Mdl_Call, ("StartPoll no BasEqp! ConfID:%d\n", Inst()->GetInsID()));
			return emPollResFull_Bas;
		}
	}

	if ( !m_bBas && NULL == m_pcPollVmp )
	{
		ForEachChanList(ptChair->m_wVidRcvNum,
			m_aptLocalChair[ewIndex] = Inst()->GetPollAddrList()->AllocNode();
			m_aptLocalChair[ewIndex]->SetIP(Inst()->GetConfEqpDs().m_dwEqpIp);
		);
	}

	InitVirNode();

	EmTPPollResult emRet = PollNextEp();
		
	return emRet;
}

EmTPPollResult CPollMgr::SuspendPoll(BOOL32 bSuspend, BOOL32 bTimer)
{
	if ( !Inst()->IsChairConf() )
	{
		return emPollNoChair;
	}

	EmTPPollResult emRet = emPollFailUnKown;

	do 
	{
		if ( bSuspend )
		{//暂停

			if ( m_emUiStat == EmPollStat_Stop
				|| m_emUiStat == EmPollStat_Suspend )
			{
				KillTimer(evtp_ExeTurnList_time);
				MdlError(Ums_Mdl_Call, ("SuspendPoll Stat Invalid! ConfID:%d, stat:%s, uiStat:%s\n", 
					Inst()->GetInsID(), GetStatPrint(m_emStat), GetStatPrint(m_emUiStat)));
				break;
			}

			if ( m_emStat != EmPollStat_Start  )
			{//后台不是开启状态 后台无需处理
				emRet = emPollSucceed;
				break;
			}

			if ( !bTimer )
			{
				KillTimer(evtp_ExeTurnList_time);
			}
			
			m_emStat = EmPollStat_Suspend;

			emRet = emPollSucceed;
			
			TCapNode* ptChair = Inst()->m_pcNodeMgr->GetCapsetNode(Inst()->chairID());
			if (NULL != ptChair && ptChair->IsChanOn())
			{
				Inst()->GetNodeFsm()->StopPoll(ptChair);
			}
		}
		else
		{//恢复
			if ( m_emUiStat != EmPollStat_Suspend )
			{
				MdlError(Ums_Mdl_Call, ("SuspendPoll Stat Invalid! ConfID:%d, stat:%s, uiStat:%s\n", 
					Inst()->GetInsID(), GetStatPrint(m_emStat), GetStatPrint(m_emUiStat)));
				break;
			}

			if ( m_emStat != EmPollStat_Suspend  )
			{//后台不是暂停状态 后台无需处理
				emRet = emPollSucceed;
				if ( m_emStat == EmPollStat_Stop )
				{
					emRet = StartPoll();
				}
				break;
			}
			else
			{
				emRet = PollNextEp();
			}
		}

	} while (0);

	return emRet;
}

EmTPPollResult CPollMgr::StopPoll()
{
	if ( !Inst()->IsChairConf() )
	{
		return emPollNoChair;
	}

	if ( m_emStat == EmPollStat_Stop )
	{
		MdlError(Ums_Mdl_Call, ("StopPoll Stat Invalid! ConfID:%d, stat:%s\n", Inst()->GetInsID(), GetStatPrint(m_emStat)));
		return emPollSucceed;
	}

	//向下级请求拆除
	TCasecadePollEpReq tReq;
	tReq.m_bCreate = FALSE;

	TUmsHandle tOutHandle;

	TCallNode* ptPoll = NULL;
	TCapNode* ptPollCap = NULL;
	if ( TP_VALID_HANDLE(m_tAddrOne.m_wPollEpID) )
	{
		ptPoll = Inst()->GetNodeMgr()->GetNode(m_tAddrOne.m_wPollEpID);
		ptPollCap = Inst()->GetNodeMgr()->GetForeFatherNode(ptPoll);
		if ( ptPoll != NULL && ptPollCap != NULL )
		{
			if ( ptPoll == ptPollCap )
			{
				Inst()->m_pcCallMgr->FlowControl(m_tAddrOne.m_wPollEpID, FLOW_CTROL_ALL_ENC, 0);
			}
			else
			{
				tReq.m_wEpID = ptPoll->m_wLowChildEpID;
				Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptPollCap->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));
			}
		}
	}
	
	if ( TP_VALID_HANDLE(m_tAddrTwo.m_wPollEpID) )
	{
		ptPoll = Inst()->GetNodeMgr()->GetNode(m_tAddrTwo.m_wPollEpID);
		ptPollCap = Inst()->GetNodeMgr()->GetForeFatherNode(ptPoll);
		if ( ptPoll != NULL && ptPollCap != NULL )
		{
			if ( ptPoll == ptPollCap )
			{
				Inst()->m_pcCallMgr->FlowControl(m_tAddrTwo.m_wPollEpID, FLOW_CTROL_ALL_ENC, 0);
			}
			else
			{
				tReq.m_wEpID = ptPoll->m_wLowChildEpID;
				Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptPollCap->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));
			}
		}
	}

	Inst()->GetBandWidth().ReleaseDownBW(m_dwBw, em_View_Poll);
	m_dwBw = 0;
			
	m_tAddrOne.m_wPollEpID = TP_INVALID_INDEX;
	m_tAddrOne.m_wPollIndx = TP_INVALID_INDEX;

	m_tAddrTwo.m_wPollEpID = TP_INVALID_INDEX;
	m_tAddrTwo.m_wPollIndx = TP_INVALID_INDEX;

	PollClear();
		
	//停止
	KillTimer(evtp_ExeTurnList_time);

	TCapNode* ptChair = Inst()->m_pcNodeMgr->GetCapsetNode(Inst()->chairID());
	if (NULL != ptChair && ptChair->IsChanOn())
	{
		Inst()->GetNodeFsm()->StopPoll(ptChair);
	}
	
	m_emStat = EmPollStat_Stop;

	ReleaseVirNode();
	
	return emPollSucceed;
}

EmTPPollResult CPollMgr::PollNextEp(u16 wPollIndx)
{
	KillTimer(evtp_ExeTurnList_time);
	SetTimer(evtp_ExeTurnList_time, m_tCfg.m_wInterval * 1000);

	if (!TP_VALID_HANDLE(wPollIndx))
	{
		wPollIndx = m_ptCurAddr->m_wPollIndx;
	}

	u16 wNextPollIndx = GetNextPollEp(wPollIndx);
	if ( !TP_VALID_HANDLE(wNextPollIndx) )
	{
		MdlError(Ums_Mdl_Call, ("PollNextEp nextPoll InValid EP! ConfID:%d\n", Inst()->GetInsID()));
		SuspendPoll(TRUE, TRUE);
		return emPollInvalidEp;
	}
	
	m_emStat = EmPollStat_Start;
	
	//开启
	CreatePollEpMedia( m_tCfg.m_apcNode[wNextPollIndx]->m_wEpID, wNextPollIndx);

	return emPollSucceed;
}

void CPollMgr::CreatePollEpMedia(u16 wCurPollEp, u16 wPollIndx, BOOL32 bDownUmsRsp)
{
	TCallNode* ptNewPoll = Inst()->GetNodeMgr()->GetNode(wCurPollEp);
	TCapNode* ptNewPollCap = Inst()->GetNodeMgr()->GetForeFatherNode(wCurPollEp);
	TCallNode* ptOldPoll = Inst()->GetNodeMgr()->GetNode(m_ptCurAddr->m_wPollEpID);
	TCapNode* ptOldPollCap = Inst()->GetNodeMgr()->GetForeFatherNode(m_ptCurAddr->m_wPollEpID);
	if ( NULL != ptNewPoll && NULL != ptNewPollCap )
	{//根结点相等 则不需要平滑
		
		if ( ptNewPoll != ptNewPollCap && !bDownUmsRsp )
		{//下级会场，先去请求，返回成功后再切目标
			TCasecadePollEpReq tReq;
			tReq.m_wEpID = ptNewPoll->m_wLowChildEpID;
			tReq.m_bCreate = TRUE;
			for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			{
				if ( ptNewPollCap != ptOldPollCap && NULL != ptOldPollCap )
				{//不在同一个下级 用下一个当前地址 即现在的old地址
					tReq.m_atPollAddr[wIndex] = m_ptOldAddr->m_aptLocalAddr[wIndex]->m_tRtpAddr;
					tReq.m_atSmallAddr[wIndex] = m_ptOldAddr->m_aptSmallAddr[wIndex]->m_tRtpAddr;
				}
				else
				{//再同一个下级 下级做平滑 用当前地址
					tReq.m_atPollAddr[wIndex] = m_ptCurAddr->m_aptLocalAddr[wIndex]->m_tRtpAddr;
					tReq.m_atSmallAddr[wIndex] = m_ptCurAddr->m_aptSmallAddr[wIndex]->m_tRtpAddr;
				}
			}
			
			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNewPollCap->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));

			m_ptOldAddr->m_wPollIndx = wPollIndx;
			m_ptOldAddr->m_wPollEpID = wCurPollEp;

			return ;
		}
		else if( ptNewPoll == ptNewPollCap )
		{
			Inst()->m_pcCallMgr->FlowControl(ptNewPoll->m_wEpID, FLOW_CTROL_ALL_ENC, ptNewPoll->m_tVidSndFormat.m_tFormat.m_wBitrate);
		}

		if ( ptNewPollCap != ptOldPollCap && NULL != ptOldPollCap )
		{
			NextAddr();
			m_ptCurAddr->m_wPollIndx = wPollIndx;
			m_ptCurAddr->m_wPollEpID = wCurPollEp;

			//创建平滑
			SetIFrameCheck();
		}
		else
		{
			m_ptCurAddr->m_wPollIndx = wPollIndx;
			m_ptCurAddr->m_wPollEpID = wCurPollEp;

			if ( NULL != ptOldPoll && ptOldPoll == ptOldPollCap )
			{
				Inst()->m_pcCallMgr->FlowControl(ptOldPoll->m_wEpID, FLOW_CTROL_ALL_ENC, 0);
			}
		}

		if( NULL != m_pcPollVmp )
		{
			TVmpStyleInfo	tStyleInfo;
			TVmpEncParam	tEncParam;
			tStyleInfo.m_emShowMode = ums_vmp_lastframe_mode;
			tStyleInfo.m_byMemberNum = 1;
			
			tStyleInfo.m_atMemberInfo[0].m_bMerged = FALSE;
			tStyleInfo.m_atMemberInfo[0].m_dwHandle = ptNewPoll->m_wEpID;
			tStyleInfo.m_atDoublePayload[0].m_byActivePayload = ptNewPoll->m_tVidSndFormat.m_wDynamicPayload;
			tStyleInfo.m_atDoublePayload[0].m_byRealPayload = ptNewPoll->m_tVidSndFormat.m_wStaticPayload;
			
			if ( ptNewPoll->IsThreeVidSnd() && ptNewPoll->IsSmallVidSnd() )
			{
				tStyleInfo.m_byMemberNum += TP_MAX_STREAMNUM;
				for (u8 wIndx = 0; wIndx < TP_MAX_STREAMNUM; wIndx ++ )
				{
					tStyleInfo.m_atMemberInfo[wIndx+1].m_bMerged = TRUE;
					tStyleInfo.m_atMemberInfo[wIndx+1].m_dwHandle = ptNewPoll->m_wEpID;
					tStyleInfo.m_atDoublePayload[wIndx+1].m_byActivePayload = ptNewPoll->m_tVidSndFormat.m_wDynamicPayload;
					tStyleInfo.m_atDoublePayload[wIndx+1].m_byRealPayload = ptNewPoll->m_tVidSndFormat.m_wStaticPayload;
				}
			}

			tStyleInfo.m_emVmpStyle = (1 == tStyleInfo.m_byMemberNum)?em_ums_vmp_one:em_ums_vmp_four_pic;
			
			tEncParam.m_byEncType = CTpTypeAdpt::GetVidPayloadValue(m_tChairFmt.m_tFormat.m_emFormat);
			tEncParam.m_byFrameRate = m_tChairFmt.m_tFormat.m_wFrameRate;
			if ( m_tChairFmt.m_tFormat.m_emQualityLvl == emTPH264HP )
			{
				tEncParam.m_byProfileType = 1;
			}
			else if( m_tChairFmt.m_tFormat.m_emQualityLvl == emTPH264BP )
			{
				tEncParam.m_byProfileType = 0;
			}
			tEncParam.m_wBitRate = m_tChairFmt.m_tFormat.m_wBitrate;
			CTpTypeAdpt::GetWHByVidResolution(m_tChairFmt.m_tFormat.m_emRes,
								tEncParam.m_wVideoWidth, tEncParam.m_wVideoHeight);
			
			
			TVmpUseParam tVmpParam;
			TTPEncrypt tEncrypt = Inst()->GetConfEncryptInfo();
			memcpy(&tVmpParam.m_tEncrypt, &tEncrypt, sizeof(TTPEncrypt));
			memcpy(&tVmpParam.m_tEncParam, &tEncParam, sizeof(tEncParam));
			memcpy(&tVmpParam.m_tStyleInfo, &tStyleInfo, sizeof(tStyleInfo));
			if ( !m_bVmpStart)
			{
				Inst()->GetVmpServiceHandle()->Start(m_pcPollVmp, &tVmpParam);
				m_bVmpStart = TRUE;
			}
			else
			{
				Inst()->GetVmpServiceHandle()->ChangeMode(m_pcPollVmp, &tVmpParam);
			}
		}
	}

	if( m_bPrint )
	{
		MdlHint(Ums_Mdl_Call, ("CreatePollEpMedia. ConfID:%d, stat:%d, CurEpID:%d, OldEpID:%d\n", 
			Inst()->GetInsID(), m_emStat, m_ptCurAddr->m_wPollEpID, m_ptOldAddr->m_wPollEpID));
	}
	

	//创建到本地的交换
	CNetPortMgr::AdjustPollTransToUms(Inst());

	TCapNode* ptChair = Inst()->m_pcNodeMgr->GetCapsetNode(Inst()->chairID());
	if (NULL != ptChair && ptChair->IsChanOn())
	{
		Inst()->GetNodeFsm()->StartPoll(ptChair);
	}

	if ( NULL != ptNewPoll && NULL != ptNewPollCap )
	{
		ptNewPollCap->m_tRmtChan.ResetFastStatis();
		ForEachChanList(ptNewPoll->m_wVidSndNum, AskKeyFrame(ewIndex, TRUE););
	}

	return ;
}

void CPollMgr::StopConf()
{
	ReleaseVirNode();

	m_emUiStat = EmPollStat_Stop;
	m_emStat = EmPollStat_Stop;
	
	m_ptCurAddr = &m_tAddrOne;
	m_ptOldAddr = &m_tAddrTwo;
	
	m_bIsDefaultPoll = FALSE;

	KillTimer(evtp_ExeTurnList_time);
	
	m_bBas = FALSE;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL != m_tAddrOne.m_aptLocalAddr[wIndex] )
		{
			Inst()->GetPollAddrList()->FreeBuff(m_tAddrOne.m_aptLocalAddr[wIndex]);
			m_tAddrOne.m_aptLocalAddr[wIndex] = NULL;
		}
		
		if ( NULL != m_tAddrTwo.m_aptLocalAddr[wIndex] )
		{
			Inst()->GetPollAddrList()->FreeBuff(m_tAddrTwo.m_aptLocalAddr[wIndex]);
			m_tAddrTwo.m_aptLocalAddr[wIndex] = NULL;
		}

		if ( NULL != m_tAddrOne.m_aptSmallAddr[wIndex] )
		{
			Inst()->GetPollAddrList()->FreeBuff(m_tAddrOne.m_aptSmallAddr[wIndex]);
			m_tAddrOne.m_aptSmallAddr[wIndex] = NULL;
		}
		
		if ( NULL != m_tAddrTwo.m_aptSmallAddr[wIndex] )
		{
			Inst()->GetPollAddrList()->FreeBuff(m_tAddrTwo.m_aptSmallAddr[wIndex]);
			m_tAddrTwo.m_aptSmallAddr[wIndex] = NULL;
		}
	}

	PollClear();
}

void CPollMgr::PollClear()
{
	m_tFailEpID.Clear();

	m_tUiListTemp.Clear();

	if (0 != m_tToPollDs.GetElementNum())
	{
		CNetPortMgr::FreeMediaTrans(Inst(), m_tToPollDs);
		m_tToPollDs.Clear();
	}

	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if( NULL != m_apcBasRes[wIndex] )
		{
			Inst()->GetBas()->ReleaseScreenBas(m_apcBasRes[wIndex]);
			m_apcBasRes[wIndex] = NULL;
		}

		if ( NULL != m_aptLocalChair[wIndex] )
		{
			Inst()->GetPollAddrList()->FreeBuff(m_aptLocalChair[wIndex]);
			m_aptLocalChair[wIndex] = NULL;
		}

		m_atRmtRtp[wIndex].Clear();
		m_atSmallRmtRtp[wIndex].Clear();
	}

	if ( NULL != m_pcPollVmp )
	{
		CUmsConfInst::GetVmpServiceHandle()->Release(m_pcPollVmp);
		m_pcPollVmp = NULL;
	}

	m_dwBw = 0;

	DestroyIframeCheck();

//	m_tIframeCheck.Clear();
}

BOOL32 CPollMgr::HavePollEp()
{
	BOOL32		bValid = FALSE;
	TCallNode*	ptNode = NULL;
	for (u16 wIndex = 0; wIndex < m_tCfg.m_wNum; ++wIndex)
	{
		ptNode = m_tCfg.m_apcNode[wIndex];
		if (NULL == ptNode)
		{
			continue;
		}
		else
		{
			if ( ptNode->m_wEpID == Inst()->chairID() )
			{
				continue;
			}
			
			if (ptNode->IsChanOn() && ptNode->IsVidSndValid())
			{
				bValid = TRUE;
				break;
			}
		}
	}

	return bValid;
}

void CPollMgr::NextAddr()
{
	if ( m_ptCurAddr == NULL )
	{
		m_ptCurAddr = &m_tAddrOne;
	}
	else
	{
		if ( m_ptCurAddr == &m_tAddrOne )
		{
			m_ptCurAddr = &m_tAddrTwo;
			m_ptOldAddr = &m_tAddrOne;
		}
		else if ( m_ptCurAddr == &m_tAddrTwo )
		{
			m_ptCurAddr = &m_tAddrOne;
			m_ptOldAddr = &m_tAddrTwo;
		}
	}
}

u16 CPollMgr::GetNextPollEp(u16 wCurIndx)
{
	u16 wIndex = 0;
	if ( wCurIndx + 1 >= m_tCfg.m_wNum )
	{
		wIndex = 0;
		m_tFailEpID.Clear();
	}
	else
	{
		wIndex = wCurIndx + 1;
	}

	u16	wForNum = 0;//避免死循环
	TCallNode*	ptNode = NULL;
	TCapNode* ptCapNode = NULL;
	for ( ; wIndex <= m_tCfg.m_wNum; ++wIndex)
	{
		if ( wIndex == m_tCfg.m_wNum  )
		{//再找一遍
			wIndex = 0;
			wForNum ++;
		}

		if ( wForNum > 2 )
		{
			break;
		}

		ptNode = m_tCfg.m_apcNode[wIndex];
		if (NULL == ptNode)
		{
			continue;
		}

		if ( ptNode->m_wEpID == m_wVirEpID )
		{
			continue;
		}

		if ( ptNode->IsUms() )
		{
			continue;
		}

		if ( ptNode->IsVRS() )
		{
			continue;
		}

		if ( !ptNode->IsChanOn() || !ptNode->IsVidSndValid())
		{
			continue;
		}

		ptCapNode = Inst()->GetNodeMgr()->GetForeFatherNode(ptNode);
		if (  NULL == ptCapNode || !ptCapNode->IsChanOn() )
		{ 
			continue;
		}

		if ( ptNode != ptCapNode )
		{//下级申请下行带宽 无则不轮询

			if ( !m_tFailEpID.Check(ptCapNode->m_wEpID, ptNode->m_wVidSndNum) )
			{
				continue;
			}

			if ( m_dwBw < ptNode->GetSndBW() )
			{
				if(!Inst()->GetBandWidth().AssigneDownBW(ptNode->GetSndBW() - m_dwBw, em_View_Poll))
				{
					Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Poll_EpNextBW, Inst()->chairID(), ptNode->m_wEpID);
					continue;
				}

				m_dwBw = ptNode->GetSndBW();
			}
			else if( m_dwBw > ptNode->GetSndBW() )
			{
				Inst()->GetBandWidth().ReleaseDownBW(m_dwBw - ptNode->GetSndBW(), em_View_Poll);

				m_dwBw = ptNode->GetSndBW();
			}
		}
		else
		{
			Inst()->GetBandWidth().ReleaseDownBW(m_dwBw, em_View_Poll);
			m_dwBw = 0;
		}
		
		return wIndex;
	}
	
	if (wCurIndx < TP_CONF_MAX_CNSNUM)
	{
		TCallNode* ptCurPoll = m_tCfg.m_apcNode[wCurIndx];
		TCapNode* ptCurollCap = Inst()->GetNodeMgr()->GetForeFatherNode(ptCurPoll);;
		// 未找到下一个有效的会场，且最后一个会场是下级会场
		if (ptCurPoll != ptCurollCap && NULL != ptCurPoll && NULL != ptCurollCap && ptCurollCap->IsUms())
		{
			// 清除当前下行宽带
			Inst()->GetBandWidth().ReleaseDownBW(m_dwBw, em_View_Poll);
			m_dwBw = 0;
			
			// 通知下级UMS清除上行宽带
			TCasecadePollEpReq tReq;
			tReq.m_bCreate = FALSE;
			tReq.m_wEpID   = ptCurPoll->m_wLowChildEpID;
			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptCurollCap->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));
		}
	}


	return TP_INVALID_INDEX;
}

void CPollMgr::SetIFrameCheck()
{
	CUmsConfInst* pInst = Inst();
	DestroyIframeCheck();

	TCallNode* ptNewPoll = pInst->GetNodeMgr()->GetNode(m_ptCurAddr->m_wPollEpID);
	TCallNode* ptOldPoll = pInst->GetNodeMgr()->GetNode(m_ptOldAddr->m_wPollEpID);	
	if (NULL != ptNewPoll && NULL != ptOldPoll)
	{
		if (ptNewPoll->m_wVidSndNum > 0 && ptNewPoll != ptOldPoll)
		{
			TCapNode* ptChair = pInst->m_pcNodeMgr->GetCapsetNode(pInst->chairID());
			if (NULL == ptChair || !ptChair->IsChanOn())
			{
				MdlError(Ums_Mdl_Call, ("SetIFrameCheck failed. ConfID:%d\n", pInst->GetInsID()));
				return;
			}
			
			s32 symbolflag = 1; 
			u16 wTempNum = 0;
			u16 wChanIndex = 0;
			u16 wMidIndex = MIDSCREENINDEX;
			
			if (ptChair->IsSingleScreen())
			{
				u16 wOldSpeakerIndex = ptOldPoll->GetSpeaker();
				u16 wNewSpeakerIndex = ptNewPoll->GetSpeaker();
				
				if (CNetPortMgr::CreatePollForIframeCheck(pInst, &m_ptCurAddr->m_aptLocalAddr[wNewSpeakerIndex]->m_tRtpAddr
					, &m_ptOldAddr->m_aptLocalAddr[wOldSpeakerIndex]->m_tRtpAddr, wMidIndex, ptNewPoll->m_wEpID))
				{
					m_tIframeCheck.m_abInCheck[wMidIndex] = TRUE;
					m_tIframeCheck.m_abNeedClear[wMidIndex] = TRUE;
					m_tIframeCheck.m_tCurAddr[wMidIndex] = m_ptCurAddr->m_aptLocalAddr[wNewSpeakerIndex]->m_tRtpAddr;
					m_tIframeCheck.m_tOldAddr[wMidIndex] = m_ptOldAddr->m_aptLocalAddr[wOldSpeakerIndex]->m_tRtpAddr;
				}	
			}
			else
			{
				for (u16 wIndex = 1; wIndex <= TP_MAX_STREAMNUM; ++wIndex, symbolflag *= -1)
				{		
					wChanIndex = wMidIndex + wIndex / 2 * symbolflag;
					
					wTempNum++;
					if (ptNewPoll->m_wVidSndNum >= wTempNum && ptOldPoll->m_wVidSndNum >= wTempNum)
					{
						if (CNetPortMgr::CreatePollForIframeCheck(pInst, &m_ptCurAddr->m_aptLocalAddr[wChanIndex]->m_tRtpAddr
							, &m_ptOldAddr->m_aptLocalAddr[wChanIndex]->m_tRtpAddr, wChanIndex, ptNewPoll->m_wEpID))
						{
							m_tIframeCheck.m_abInCheck[wChanIndex] = TRUE;
							m_tIframeCheck.m_abNeedClear[wChanIndex] = TRUE;
							m_tIframeCheck.m_tCurAddr[wChanIndex] = m_ptCurAddr->m_aptLocalAddr[wChanIndex]->m_tRtpAddr;
							m_tIframeCheck.m_tOldAddr[wChanIndex] = m_ptOldAddr->m_aptLocalAddr[wChanIndex]->m_tRtpAddr;
						}			
					}					
				}
			}
		}
	}
	
	if( m_bPrint )
	{
		MdlHint(Ums_Mdl_Call, ("SetIFrameCheck:[%d,%d,%d], New:%x, old:%x\n"
			, m_tIframeCheck.m_abInCheck[0], m_tIframeCheck.m_abInCheck[1], m_tIframeCheck.m_abInCheck[2], ptNewPoll, ptOldPoll));
	}
}

void CPollMgr::DestroyIframeCheck()
{
	CUmsConfInst* pInst = Inst();
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (m_tIframeCheck.m_abNeedClear[wIndex])
		{
			CNetPortMgr::DestroyPollForIframeCheck(pInst, &m_tIframeCheck.m_tCurAddr[wIndex], &m_tIframeCheck.m_tOldAddr[wIndex]);
		}
	}
	m_tIframeCheck.Clear();
}

void CPollMgr::OnIframeBySrcNty( CTpMsg *const ptMsg )
{
	TCheckIFrameBase tBase;
	TIFrameTwoRcvPort tTwoRcv;
	tTwoRcv.Clear();
	TP_SAFE_CAST(tBase, ptMsg->GetBody());
	TP_SAFE_CAST(tTwoRcv, ptMsg->GetBody() + sizeof(tBase));
	
	CUmsConfInst* pInst = Inst();
	u16 wNewPollID = tTwoRcv.m_wPollEp;
	if (wNewPollID != m_ptCurAddr->m_wPollEpID)
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::OnIframeBySrcNty epid failed! ConfID:%d, CurPollEp:%d, IEp:%d\n", 
			pInst->GetInsID(), m_ptCurAddr->m_wPollEpID, wNewPollID));
		return;
	}
	
	u16 wChanIndex = tTwoRcv.m_wChanIndex;
	if (wChanIndex >= TP_MAX_STREAMNUM)
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::OnIframeBySrcNty chan failed! wConfID:%d, CurPollEp:%d, IEp:%d, chan:%d\n", 
			pInst->GetInsID(), m_ptCurAddr->m_wPollEpID, wNewPollID, wChanIndex));
		return;
	}
	
	if (!m_tIframeCheck.m_abInCheck[wChanIndex])
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::OnIframeBySrcNty chan status failed! wConfID:%d, CurPollEp:%d, IEp:%d, chan:%d\n", 
			pInst->GetInsID(), m_ptCurAddr->m_wPollEpID, wNewPollID, wChanIndex));
		return;
	}
	
	m_tIframeCheck.m_abInCheck[wChanIndex] = FALSE;
	
	MdlLowHint(Ums_Mdl_Call, ("CPollMgr::OnIframeBySrcNty wConfID:%d, CurPollEp:%d, IEp:%d, chan:%d\n", 
									pInst->GetInsID(), m_ptCurAddr->m_wPollEpID, wNewPollID, wChanIndex));
	
	BOOL32 bChanged = TRUE;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (m_tIframeCheck.m_abInCheck[wIndex])
		{
			bChanged = FALSE;
		}
	}
	
	if (bChanged)
	{
		if( m_bPrint )
		{
			MdlHint(Ums_Mdl_Call, ("CPollMgr::OnIframeBySrcNty pollchanger final! wConfID:%d, CurPollEp:%d\n", 
				pInst->GetInsID(), m_ptCurAddr->m_wPollEpID));
		}

		TCallNode* ptOldPoll = Inst()->GetNodeMgr()->GetNode(m_ptOldAddr->m_wPollEpID);
		TCapNode* ptOldPollCap = Inst()->GetNodeMgr()->GetForeFatherNode(m_ptOldAddr->m_wPollEpID);
		if ( NULL != ptOldPoll && NULL != ptOldPollCap  )
		{
			if( ptOldPoll != ptOldPollCap )
			{
				//向下级请求拆除
				TCasecadePollEpReq tReq;
				tReq.m_wEpID = ptOldPoll->m_wLowChildEpID;
				tReq.m_bCreate = FALSE;
				
				TUmsHandle tOutHandle;
				Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptOldPollCap->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Req, &tReq, sizeof(tReq));
			}
			else
			{
				Inst()->m_pcCallMgr->FlowControl(ptOldPoll->m_wEpID, FLOW_CTROL_ALL_ENC, 0);
			}
		}

		m_ptOldAddr->m_wPollEpID = TP_INVALID_INDEX;
		m_ptOldAddr->m_wPollIndx = TP_INVALID_INDEX;

		if ( !pInst->IsChairConf() )
		{//尝试释放适配通道
			TCallNode* ptNewPoll = Inst()->GetNodeMgr()->GetNode(m_ptCurAddr->m_wPollEpID);
			if ( NULL != ptNewPoll && ptNewPoll->IsChanOn() && ptNewPoll->m_wVidSndNum < ptOldPoll->m_wVidSndNum )
			{
				Inst()->GetBas()->ReleaseScreenBas(m_apcBasRes[0]);
				Inst()->GetBas()->ReleaseScreenBas(m_apcBasRes[2]);
			}
		}
		
		DestroyIframeCheck();

		CNetPortMgr::AdjustPollTransToUms(pInst);

		if( pInst->IsChairConf() )
		{
			pInst->GetNodeFsm()->UpdateMediaTrans(pInst->chairID());
		}
	}

	return ;
}

void CPollMgr::NotifyPollListToUI(BOOL32 bCNC, BOOL32 bUmc, TLogUser* ptUser)
{
	//通知轮询列表
	u16 wDstEp = 0;
	if ( Inst()->IsChairConf() )
	{
		wDstEp = Inst()->chairID();
	}
	else
	{
		wDstEp = CALLER_EP_INDEX;
	}
	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, wDstEp);

	TTpPollListNtfy tPollList;
	tPollList.m_wConfID = Inst()->GetInsID();
	tPollList.m_wInterval = m_tCfg.m_wInterval;
	tPollList.m_wTotalNum = m_tCfg.m_wNum;
 
	time_t CurTime;
	time(&CurTime);
	tPollList.m_nFlag = CurTime;

	for (u16 wIndex = 0; wIndex < m_tCfg.m_wNum; ++wIndex)
	{
		if ( NULL == m_tCfg.m_apcNode[wIndex] )
		{
			continue;
		}
		
		if ( tPollList.m_wCurNum == TP_CONF_MAX_TURNNUM )
		{
			if ( bCNC )
			{
				UmsSendConfCtrl(tOutHandle, ev_UmsUpdateConfTurnlist_Nty, &tPollList, sizeof(TTpPollListNtfy));
			}
			if ( bUmc )
			{
				Inst()->NotifyMsgToServiceForUI(evtp_UpdateConfTurnlist_Notify, &tPollList, sizeof(TTpPollListNtfy), ptUser);
			}

			tPollList.m_wCurNum = 0;
			memset(tPollList.m_awList, 0, sizeof(tPollList.m_awList));
		//	continue;
		}
		
		tPollList.m_awList[tPollList.m_wCurNum ++] = m_tCfg.m_apcNode[wIndex]->m_wEpID;
	}

	if ( tPollList.m_wCurNum > 0 || m_tCfg.m_wNum == 0 )
	{//轮询列表为0 ，也更新一次间隔时间
		if ( bCNC )
		{
			UmsSendConfCtrl(tOutHandle, ev_UmsUpdateConfTurnlist_Nty, &tPollList, sizeof(TTpPollListNtfy));
		}
		if ( bUmc )
		{
			Inst()->NotifyMsgToServiceForUI(evtp_UpdateConfTurnlist_Notify, &tPollList, sizeof(TTpPollListNtfy), ptUser);
		}
	}

	return ;
}

BOOL32 CPollMgr::UpdatePollTempList(TTpPollListNtfy& tList)
{
	m_tUiListTemp.m_wInterval = tList.m_wInterval;
	m_tUiListTemp.m_wTotalNum = tList.m_wTotalNum;

	memcpy(&m_tUiListTemp.m_awList[m_tUiListTemp.m_wCurNum], tList.m_awList, sizeof(u16)*tList.m_wCurNum);
	m_tUiListTemp.m_wCurNum += tList.m_wCurNum;
	
	if ( m_tUiListTemp.m_wCurNum >= m_tUiListTemp.m_wTotalNum)
	{//此时结束接收
		m_tUiListTemp.m_wUpdate = FALSE;
		m_tUiListTemp.m_dwFlag = 0;
		
		InitPollList();

		m_tUiListTemp.Clear();

		return TRUE;
	}

	return FALSE;
}

void CPollMgr::NotifyPollStatToUI(TLogUser* ptUser)
{
	TTpPollStat tStat;
	tStat.m_emStat = m_emUiStat;
	tStat.m_wConfID = Inst()->GetInsID();

	if ( !Inst()->IsChairConf() )
	{//下级，轮询固定停止
		tStat.m_emStat = EmPollStat_Stop;
		Inst()->NotifyMsgToServiceForUI(evtp_TurnStat_ntfy, &tStat, sizeof(tStat), ptUser);
		return ;
	}
	
	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, Inst()->chairID());

	Inst()->NotifyMsgToServiceForUI(evtp_TurnStat_ntfy, &tStat, sizeof(tStat), ptUser);
	UmsSendConfCtrl(tOutHandle, evtp_Conf_PollStatus_Notif, &tStat, sizeof(tStat));

	return ;
}

#ifdef _USE_XMPUEQP_

void CPollMgr::XmpuBasCB( u32 dwType, CScreenBasRes* ptBasRes, void *pData)
{
	TXmpuStartBasNty tStartBastNty;
    CUmsConfInst* pInst = Inst();
	BOOL32 bError = FALSE;

    if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		memcpy(&tStartBastNty, pData, sizeof(tStartBastNty));  
		if (!tStartBastNty.m_bSuccess)
		{
			bError = TRUE;
			MdlHint(Ums_Mdl_Call, ("CPollMgr::XmpuBasCB,StartBasFail. ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, AssignBas fail!\n", 
				Inst()->GetInsID(), ptBasRes->GetBasEqpId(), ptBasRes->GetBasChnIndex()));

		} else 
		{
			ptBasRes->m_tXmpuBas.m_emStat = EmXmpuResStatInfo_Running;
			pInst->GetBas()->SetXmpuVidBasAssignAddr(&ptBasRes->m_tXmpuBas, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);
			CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, &ptBasRes->m_tXmpuBas);

			TCapNode* ptCaller = Inst()->GetNodeMgr()->GetCaller();
			if ( NULL == ptCaller || !ptCaller->IsChanOn() )
			{
			    Inst()->GetBas()->AdjustScreenBas(ptBasRes, ptBasRes->m_wSrcEp, ptBasRes->m_wSrcScreenIndx, 1, 
																	&ptCaller->m_tVidRcvFormat.m_tFormat);	
			}
		}

		
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		// 	CNetPortMgr::AdjustPollTransToUms(Inst());
		
	} else if (dwType == evXmpu_AskBasKey_Req)
	{
		MdlLowDtl(Ums_Mdl_Call, ("CPollMgr::XmpuBasCB. ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, AskBasKey\n", 
			Inst()->GetInsID(), ptBasRes->GetBasEqpId(), ptBasRes->GetBasChnIndex()));
		
		u16 wIndex = 0;
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if ( m_apcBasRes[wIndex] == ptBasRes )
			{
				break;
			}
		}
		Inst()->AskKeyByScreen(m_ptCurAddr->m_wPollEpID, wIndex, EmAskKeyPoll, wIndex);
		
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
        bError = TRUE;
		MdlHint(Ums_Mdl_Call, ("CPollMgr::XmpuBasCB. ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, BasDisConnect\n", 
			    Inst()->GetInsID(), ptBasRes->GetBasEqpId(), ptBasRes->GetBasChnIndex()));
	}

	if ( bError )
	{
		if( Inst()->IsChairConf() )
		{
			StopPoll();
			m_emUiStat = EmPollStat_Stop;
			NotifyPollStatToUI();
			//加提示
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Poll_BasDisCnnt, Inst()->chairID());
		}
		else
		{//通知上级切换轮询  本级取消
			TCasecadePollEpReq tReq;
			tReq.m_bCreate = FALSE;
			tReq.m_wEpID = m_ptCurAddr->m_wPollEpID;
			
			TCasecadePollEpRsp tRsp;
			tRsp.m_emRes = emPollResFull_Bas;
			tRsp.m_tReq.m_bCreate = FALSE;
			tRsp.m_tReq.m_wEpID = m_ptCurAddr->m_wPollEpID;
			
			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Rsp, &tRsp, sizeof(tRsp));
			
			CTpMsg cMsg;
			cMsg.SetBody(&tOutHandle, sizeof(tOutHandle));
			cMsg.CatBody(&tReq, sizeof(tReq));
			OnCasecadePollEpReq(&cMsg);
		}
	}
}

#else

void CPollMgr::BasCB( CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes )
{	
	if ( emType == CScreenBasRes::VidBasCB_DisConnect
		|| emType == CScreenBasRes::VidBasCB_NAck )
	{
		MdlHint(Ums_Mdl_Call, ("CPollMgr::BasCB. ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, CBType:%d\n", 
			Inst()->GetInsID(), ptBasRes->GetBasEqpId(), ptBasRes->GetBasChnIndex(), emType));

		if( Inst()->IsChairConf() )
		{
			StopPoll();
			m_emUiStat = EmPollStat_Stop;
			NotifyPollStatToUI();
			//加提示
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Poll_BasDisCnnt, Inst()->chairID());
		}
		else
		{//通知上级切换轮询  本级取消
			TCasecadePollEpReq tReq;
			tReq.m_bCreate = FALSE;
			tReq.m_wEpID = m_ptCurAddr->m_wPollEpID;

			TCasecadePollEpRsp tRsp;
			tRsp.m_emRes = emPollResFull_Bas;
			tRsp.m_tReq.m_bCreate = FALSE;
			tRsp.m_tReq.m_wEpID = m_ptCurAddr->m_wPollEpID;

			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CasecadePollEp_Rsp, &tRsp, sizeof(tRsp));

			CTpMsg cMsg;
			cMsg.SetBody(&tOutHandle, sizeof(tOutHandle));
			cMsg.CatBody(&tReq, sizeof(tReq));
			OnCasecadePollEpReq(&cMsg);
		}
	}
	else if ( emType == CScreenBasRes::VidBasCB_AskKey )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CPollMgr::BasCB. ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, CBType:%d\n", 
			Inst()->GetInsID(), ptBasRes->GetBasEqpId(), ptBasRes->GetBasChnIndex(), emType));

		u16 wIndex = 0;
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if ( m_apcBasRes[wIndex] == ptBasRes )
			{
				break;
			}
		}
		Inst()->AskKeyByScreen(m_ptCurAddr->m_wPollEpID, wIndex, EmAskKeyPoll, wIndex);
	}
}
#endif

void CPollMgr::VmpCB( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes )
{
	if ( emRes == em_Service_No_Reg
		|| emRes == em_Start_Failed
		|| emRes == em_Stop_Failed
		|| emRes == em_Mdy_Failed
		|| emRes == em_Invalid_Param
		|| emRes == em_Set_Param_Failed)
	{
		MdlHint(Ums_Mdl_Call, ("CPollMgr::VmpCB. ConfID:%d, ServiceID:%d, CBType:%d, emRes:%d\n", 
			Inst()->GetInsID(), pcService->GetServiceID(), emOpType, emRes));
		StopPoll();
		m_emUiStat = EmPollStat_Stop;
		NotifyPollStatToUI();
		//提示
		Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Poll_VmpDisCnnt, Inst()->chairID());
	}
	else if ( emRes == em_Res_Success )
	{
		if ( emOpType == em_Frame_Service )
		{
			Inst()->AskKeyByEpID(m_ptCurAddr->m_wPollEpID, EmAskKeySpeaker);
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("CPollMgr::VmpCB. ConfID:%d, ServiceID:%d, CBType:%d, emRes:%d\n", 
				Inst()->GetInsID(), pcService->GetServiceID(), emOpType, emRes));
		}
	}
	return ;
}

void CPollMgr::AskKeyFrame( u16 wScreenIndx, BOOL32 bBySys )
{
	if ( NULL != m_pcPollVmp )
	{
		CUmsConfInst::GetVmpServiceHandle()->AskFrameToBaseService(m_pcPollVmp);
	}
	else if( m_bBas && NULL != m_apcBasRes[MIDSCREENINDEX] )
	{
		Inst()->GetBas()->AskFrameToScreenBas(m_apcBasRes[wScreenIndx]);
	}
	else
	{
		Inst()->AskKeyByScreen(m_ptCurAddr->m_wPollEpID, wScreenIndx, EmAskKeyPoll, wScreenIndx, bBySys);
	}
	return ;
}

void CPollMgr::AddNode(TCapNode* ptNode)
{
	CUmsConfInst* pInst = Inst();
	if (NULL == ptNode)
	{
		return;
	}
	
	u16 wIndex = m_tCfg.FindIndexByEp(ptNode->m_wEpID);
	if (m_tCfg.IsValid(wIndex))
	{
		return;
	}
	
	if (m_tCfg.m_wNum < TP_CONF_MAX_TURNNUM && ptNode->m_wEpID != pInst->chairID())
	{	
		m_tCfg.m_apcNode[m_tCfg.m_wNum] = ptNode;
		m_tCfg.m_wNum++;

		NotifyPollListToUI(); // 新会场加入轮询列表，更新到界面
	}
	else
	{
		MdlHint(Ums_Mdl_Call, ("CPollMgr::AddNode Failed. Poll List Full. ConfID:%d, NodeName:%s\n", pInst->GetInsID(), ptNode->m_tConfName.m_abyAlias));
	}
}

BOOL32 CPollMgr::GetLocalPollInAddr( TTPMediaTransAddr& tAddr, u32& dwEqpNode, u16 wScreenIndx , u16 wPollEpSpeakerIndex)
{
// 	if ( NULL != m_pcPollVmp )
// 	{
// 		TServiceAddr tSerAddr;// wScreenIndx + 1 是为了让合成器的小图像索引和屏索引对应
// 		CUmsConfInst::GetVmpServiceHandle()->GetRcvChanAddr(tSerAddr, m_pcPollVmp, wScreenIndx+1);
// 
// 		tAddr = tSerAddr.m_tAddr;
// 		dwEqpNode = tSerAddr.m_dwMediaNode;
// 	}
// 	else 


	TCallNode *ptNodeChair = Inst()->GetNodeMgr()->GetNode(Inst()->chairID());
	if (ptNodeChair && ptNodeChair->IsSingleVidRcv() )
	{
        
		if (wScreenIndx !=  wPollEpSpeakerIndex)
		{
            return FALSE;
		}else 
		{
            wScreenIndx = MIDSCREENINDEX;
		}
	}


	if( NULL != m_apcBasRes[MIDSCREENINDEX] )
	{
		if ( NULL == m_apcBasRes[wScreenIndx] )
		{
			return FALSE;
		}
		Inst()->GetBas()->GetInChnVidAddr(tAddr, m_apcBasRes[wScreenIndx]);
		dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
	}
	else
	{
		if ( NULL == m_aptLocalChair[wScreenIndx] )
		{
			return FALSE;
		}
		tAddr = *m_aptLocalChair[wScreenIndx];
		dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
	}
	return TRUE;
}

BOOL32 CPollMgr::GetLocalPollOutAddr( TTPMediaTransAddr& tAddr, u32& dwEqpNode, u16 wScreenIndx )
{
	if ( NULL != m_pcPollVmp )
	{//只有中间屏
		if ( wScreenIndx != MIDSCREENINDEX )
		{
			return FALSE;
		}
		TServiceAddr tSerAddr;
		CUmsConfInst::GetVmpServiceHandle()->GetSndChanAddr(tSerAddr, m_pcPollVmp);
		
		tAddr = tSerAddr.m_tAddr;
		dwEqpNode = tSerAddr.m_dwMediaNode;
	}
	else if( NULL != m_apcBasRes[MIDSCREENINDEX] )
	{
		if ( NULL == m_apcBasRes[wScreenIndx] )
		{
			return FALSE;
		}
		TUmsVidFormat tFmt;
		Inst()->GetBas()->GetOutChnVidAddr(tAddr, m_apcBasRes[wScreenIndx], tFmt);
		dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
	}
	else
	{
		if ( NULL == m_aptLocalChair[wScreenIndx] )
		{
			return FALSE;
		}
		tAddr = *m_aptLocalChair[wScreenIndx];
		dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
	}
	return TRUE;
}

void CPollMgr::InitVirNode()
{//模拟上线一个会场上线 作为轮询的虚拟结点

	if ( !CUmsConfigEx::GetInstance()->GetVirPoll() )
	{
		return ;
	}

	if ( !Inst()->IsChairConf() )
	{
		 return ;
	}

	if ( m_wVirEpID != 0 )
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::InitVirNode. allready vir! ConfID:%d, epid:%d\n", Inst()->GetInsID(), m_wVirEpID));
		return;
	}

	m_tVirDs.Clear();
	m_wVirEpID = 0;

	TCapNode* ptChair = Inst()->m_pcNodeMgr->GetCapsetNode(Inst()->chairID());
	if (NULL == ptChair || !ptChair->IsChanOn())
	{
		return ;
	}

	TTpCallAddr tCaller;
	tCaller.m_tAlias.SetAlias(tp_Alias_h323, "VirPoll");

	BOOL32 bExist = FALSE;
	TCapNode* ptNode = Inst()->GetNodeMgr()->AddNewCall(tCaller, bExist);
	
	//没有空闲的实例
	if ( NULL == ptNode )
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::InitVirNode. node full! ConfID:%d, NodeName:%s\n", Inst()->GetInsID(), tCaller.m_tAlias.m_abyAlias));
		return ;
	}
	
	if (bExist)
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::InitVirNode. node exist! ConfID:%d, NodeName:%s\n", Inst()->GetInsID(), tCaller.m_tAlias.m_abyAlias));
		return  ;
	}
	
	if (!Inst()->GetNodeMgr()->AssignNodeRes(ptNode, NULL))
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::InitVirNode. node res full! ConfID:%d, NodeName:%s\n", Inst()->GetInsID(), tCaller.m_tAlias.m_abyAlias));
		return ;
	}
	
	ptNode->m_bUsed = TRUE;
	ptNode->m_tCalledAddr = tCaller;
	ptNode->m_tConfName = ptNode->m_tCalledAddr.GetValidAlias();
	ptNode->m_tMediaEqp = Inst()->GetConfEqpDs();
	ptNode->m_emCallState = ums_UmsConfNodeState_online;
	ptNode->m_bIsCaller = FALSE;
	ptNode->CallOn();
	ptNode->m_bChannelOpen = TRUE;
	ptNode->m_emEpType = emTPEndpointTypeCNS;
	ptNode->m_emCallReason = EmCnsCallReason_success;

	m_wVirEpID = ptNode->m_wEpID;

	TTPMediaTransAddr tAddr;
	u32	dwNode;

	TUmsNodeCapset tCapSet;
	tCapSet.m_wVidEncNum = ptChair->m_wVidRcvNum;

	ForEachChanList(tCapSet.m_wVidEncNum, 
		GetLocalPollOutAddr(tAddr, dwNode, ewIndex);\
		tCapSet.m_atVidEnc[ewIndex].m_bIsChanOn = TRUE;\
		tCapSet.m_atVidEnc[ewIndex].m_tChanAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
		);

	if ( ptChair->m_tVidSndFormat.m_tFormat.m_emQualityLvl == emTPH264HP )
	{
		tCapSet.m_tVidSndCap.m_tHp = ptChair->m_tVidSndFormat.m_tFormat;
	}
	else
	{
		tCapSet.m_tVidSndCap.m_tBp = ptChair->m_tVidSndFormat.m_tFormat;
	}

	Inst()->GetNodeMgr()->SetNodeCapSet(ptNode, tCapSet);

	Inst()->GetNodeMgr()->AdjustResOnChanConnect(ptNode);

	Inst()->UpdateNodeInfo(tp_OprType_Add, m_wVirEpID);

	AdjustDsToVirNode();
	return;
}

void CPollMgr::ReleaseVirNode()
{
	if ( !CUmsConfigEx::GetInstance()->GetVirPoll() )
	{
		return ;
	}

	if ( !Inst()->IsChairConf() )
	{
		return ;
	}

	if ( m_wVirEpID != 0 )
	{
		return ;
	}

	TCapNode* ptNode = Inst()->m_pcNodeMgr->GetCapsetNode(m_wVirEpID);
	if (NULL != ptNode)
	{
		Inst()->AjustSpeakerOnNodeDisConn(ptNode);

		Inst()->StopMediaTrans(ptNode, TRUE, EmCnsCallReason_hungup);

		Inst()->UpdateNodeInfo(tp_OprType_Del, m_wVirEpID);

		Inst()->GetNodeMgr()->DeleteNode(ptNode);
	}

	if (0 != m_tVirDs.GetElementNum())
	{
		CNetPortMgr::FreeMediaTrans(Inst(), m_tVirDs);
		m_tVirDs.Clear();
	}
	m_wVirEpID = 0;
	return;
}

void CPollMgr::AdjustDsToVirNode()
{
	if ( !Inst()->IsChairConf() )
	{
		return ;
	}

	TCapNode* ptNode = Inst()->m_pcNodeMgr->GetCapsetNode(m_wVirEpID);
	if (NULL == ptNode || !ptNode->IsChanOn())
	{
		MdlError(Ums_Mdl_Call, ("CPollMgr::AdjustDsToVirNode. node offline! ConfID:%d, epID:%d\n", Inst()->GetInsID(), m_wVirEpID));
		return ;
	}

	//轮询 到 虚拟结点的交换
	TTPMediaTransAddr tAddr;
	u32	dwNode;

	u16 wDsNum = 0;
	TUmsDsData atDsData[10];

	ForEachChanList(ptNode->m_wVidSndNum, 
		GetLocalPollOutAddr(tAddr, dwNode, ewIndex);\
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;\
		atDsData[wDsNum].m_tSndToAddr = ptNode->m_aptChanAddr[ewIndex]->m_tVid.m_tRtpAddr;\
		atDsData[wDsNum].m_dwEqpNode = dwNode;\
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		wDsNum++;
		);

	CNetPortMgr::MergerDsList(Inst(), m_tVirDs, atDsData, wDsNum, "CPollMgr::AdjustDsToVirNode");
	return;
}

void CPollMgr::AdjustCnsSpeaker( TCallNode* ptNode )
{
	if ( !Inst()->IsChairConf() )
	{
		return ;
	}

	if ( m_ptCurAddr->m_wPollEpID != ptNode->m_wEpID )
	{
		return ;
	}

	CNetPortMgr::AdjustPollTransToUms(Inst());

	return ;
}

