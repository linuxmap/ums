#include "umsvmp.h"
#include "callnodemgr.h"
#include "innereventumscall.h"
#include "umsapi.h"
#include "umsnetportmgr.h"
#include "innereventumsmpu2.h"
#include "eventoutsipadapter.h"
#include "umsstackinterface.h"
#include "umsconfigex.h"
#include "callmgr.h"
#include "getvidaud.h"
#include "nodefsm.h"
#include "umsbas.h"
#include "eventoutumsbrdvmp.h"
#include "putaud.h"
#include "eventoutumsconftemplate.h"
#include "dualmgr.h"
#include "innereventumsvmp.h"
#include "tperrno.h"
#include "innereventxmpuvmp.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpubas.h"
#endif

const s8* GetUmsVmpStatBuf( CUmsVmp::EmVmpStat emStat )
{
	switch(emStat)
	{
	case CUmsVmp::VmpStat_Idle:
		return "Idle";
		break;
	case CUmsVmp::VmpStat_Running:
		return "Running";
		break;
	case CUmsVmp::VmpStat_Full:
		return "Full";
		break;
	case CUmsVmp::VmpStat_Error:
		return "Error";
		break;
	default:
		return "InvalidStat";
		break;
	}
	
	return NULL;
}

TBrdVmpRes CUmsVmp::m_atBrdVmp[XMPU_MAX_VMP_NUM];

CUmsVmp::CUmsVmp( CUmsConfInst* pcInst )
:CTpHandler(pcInst)
,CNodeBase(em_Node_Vmp)
{
	InstClear();
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		m_atBrdVmp[wIndex].Clear();
	}
}

CUmsVmp::~CUmsVmp()
{
	InstClear();
}

void CUmsVmp::InstClear()
{
	m_wVmpEpID = TP_INVALID_INDEX;
	m_emVmpType = em_Vmp_Invalid;
	m_bSpeakerVmpCfg = FALSE;

	m_tVmpCfg.Clear();
	m_tSaveMgr.Clear();

	m_pcSpeakerVmp = NULL;

	m_ptConfBrdVmp = NULL;
	
	m_bBrdVmp = FALSE;
	memset(m_szBrdVmpAlias, 0, sizeof(m_szBrdVmpAlias));
}

TCallNode* CUmsVmp::GetVmpEp()
{
	CUmsConfInst* pInst = Inst();
	
	m_emVmpType = em_Vmp_Invalid;

	TCallNode* ptVmpNode = NULL;
	TCallNode* ptSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->curSpeakerID());
	
	TCallNode* ptChair = pInst->m_pcNodeMgr->GetNode(pInst->chairID());
	if (pInst->GetRollCallMgr()->IsRollCallModle()/* && pInst->IsChairConf()*/)
	{   // ����ģʽ���������ˡ��൱����ϯ
        ptChair = pInst->m_pcNodeMgr->GetNode(pInst->GetRollCallMgr()->GetRollCallerEpId());
	}

	if ( NULL == ptSpeaker )
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::GetVmpEp.  ptSpeaker is NULL! ConfID:%d, VmpEpID:%d, Speaker:%d\n", 
			pInst->GetInsID(), m_wVmpEpID,  ptSpeaker));
		return NULL;
	}

    if (NULL == ptChair)
	{   //����ģʽptChair Ϊ ������ �¼��п���ȡ����
        if(!(pInst->GetRollCallMgr()->IsRollCallModle() && !pInst->IsChairConf()))
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::GetVmpEp. ptChair  is NULL! ConfID:%d, VmpEpID:%d, Chair:%d\n", 
				pInst->GetInsID(), m_wVmpEpID, ptChair));
			
		    return NULL;
		} 
	}

	if ( ptSpeaker->IsThreeVidSnd() )
	{//���������� ��Ҫ�ϳ�
		if ( ptSpeaker->IsChanOn() && ptSpeaker->IsSmallVidSnd() )
		{
			ptVmpNode = ptSpeaker;
			m_emVmpType = em_Speaker_In_Vmp;
		}
	}
	else
	{//�����˵���
		if( ptSpeaker != ptChair )
		{//��ϯ�ͷ����˲�ͬ
			
			if(pInst->GetRollCallMgr()->IsRollCallModle())
			{
				if (ptChair->IsThreeVidSnd() &&  ptChair->IsSmallVidSnd())
				{
                    ptVmpNode = ptChair;
                    m_emVmpType = em_Chair_In_Vmp;
				}  
			}
			else if ( pInst->GetChairCap().IsChairThreeVidSnd() && ptChair->IsSmallVidSnd() )
			{//��ϯ���� ��Ҫ�ϳ�
				if ( ptChair->IsChanOn() )
				{
					ptVmpNode = ptChair;
					m_emVmpType = em_Chair_In_Vmp;
				}
			}
		}
	}
	
	return ptVmpNode;
}

void CUmsVmp::GetSpeakerVmpInAddr( TTPDsFrom& tAddr, u16 wChnlIndx )
{
	TServiceAddr tSerAddr;
	CUmsConfInst::GetVmpServiceHandle()->GetRcvChanAddr(tSerAddr, m_pcSpeakerVmp, wChnlIndx);
	tAddr.m_tRtpAddr = tSerAddr.m_tAddr.m_tRtpAddr;
	tAddr.m_tBackRtcpAddr = tSerAddr.m_tAddr.m_tBackRtcpAddr;
	tAddr.m_dwEqpNode = tSerAddr.m_dwMediaNode;
}

void CUmsVmp::GetSpeakerVmpOutAddr(TTPDsFrom& tAddr)
{
	if ( Inst()->IsChairConf() )
	{//�ϼ� ֱ��ȥ�ϳɺ�����
		TServiceAddr tSerAddr;
		CUmsConfInst::GetVmpServiceHandle()->GetSndChanAddr(tSerAddr, m_pcSpeakerVmp);
		tAddr.m_tRtpAddr = tSerAddr.m_tAddr.m_tRtpAddr;
		tAddr.m_tBackRtcpAddr = tSerAddr.m_tAddr.m_tBackRtcpAddr;
		tAddr.m_dwEqpNode = tSerAddr.m_dwMediaNode;
	}
	else
	{//�¼� ȡcaller�ڵ�ķ����˺ϳ�
		TCapNode* ptChair = Inst()->GetNodeMgr()->GetCaller();
		if ( NULL != ptChair && ptChair->m_ptCasCadeChairAddr != NULL)
		{
			tAddr.m_tRtpAddr = ptChair->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtpAddr;
			tAddr.m_tBackRtcpAddr = ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tBackRtcpAddr; 
			tAddr.m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
		}
	}
	return ;
}

BOOL32 CUmsVmp::AskFrameToSpeakerVmp(const TUmsVidFormat& tFormat)
{
	CUmsConfInst::GetVmpServiceHandle()->AskFrameToBaseService(m_pcSpeakerVmp);	
	return TRUE;
}

//������᳡��ϳ�������ؼ�֡
BOOL32 CUmsVmp::AskFrameToSpeakerVmp( u16 wSrcEpID )
{
	CUmsConfInst* pInst = Inst();
	
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wSrcEpID);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if ( NULL == ptNode || NULL == ptFatherNode 
		|| !ptNode->IsChanOn() || !ptFatherNode->IsChanOn())
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::AskFrameToVmp. ptNode is NULL! ConfID:%d, emVmpType:%d VmpEpID:%d, SrcEpID:%d\n", 
												pInst->GetInsID(), m_emVmpType, m_wVmpEpID, wSrcEpID));
		return FALSE;
	}

	return AskFrameToSpeakerVmp(ptFatherNode->m_tVidRcvFormat.m_tFormat);
}

BOOL32 CUmsVmp::Handler( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case ev_TPVmp_FastUpdate_Req:
		OnVmpAskFrameToEp(ptMsg);
		break;
	case ev_UMC_UMS_RervesBrdVmp_Req:
		OnUmcRerveseBrdVmpReq(ptMsg);
		break;
	case ev_UMC_UMS_SetBrdVmp_Req:
		OnUmcSetBrdVmpReq(ptMsg);
		break;
	case ev_UMC_UMS_BrdVmp_Req:
		OnUmcBrdVmpReq(ptMsg);
		break;
	case ev_UMC_UMS_SaveVmpCfg_Cmd:
		OnUmcVmpMemberCfgCmd(ptMsg);
		break;
	case ev_Save_VmpCfg_Ack:
		OnSaveVmpPlanAck(ptMsg);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}


BOOL32 CUmsVmp::HandlerFromStack( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case ev_CNC_UMS_RervesBrdVmp_Req:
		OnCncRerveseBrdVmpReq(ptMsg);
		break;
	case ev_CNC_UMS_SetBrdVmp_Req:
		OnCncSetBrdVmpReq(ptMsg);
		break;
	case ev_CNC_UMS_BrdVmp_Req:
		OnCncBrdVmpReq(ptMsg);
		break;
	case ev_UMS_UMS_VmpCasecade_Ntfy:
		OnCasecadeVmpNtfy(ptMsg);
		break;
	case ev_CNC_UMS_SaveVmpCfg_Cmd:
		OnCncVmpMemberCfgCmd(ptMsg);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

extern CUmsCallMgrApp g_cUmsCallMgrApp;
//����ϳ�ʧ��
void CUmsVmp::OnVmpNAck( CTpMsg *const ptMsg )
{
	TEqpInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	TBrdVmpRes* ptVmp = FindBrdVmpByEqp(tInfo.m_byEqpID);
	if ( NULL == ptVmp )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnVmpNAck. ptVmp is NULL! EqpID:%s\n", tInfo.m_byEqpID));
		return ;
	}

	//����󣬸��µ�����
	ptVmp->m_emStat = EmBrdVmpStat_Error;

	NotifyBrdVmpToAllConf(ptVmp, tp_OprType_Update);
	
	return ;
}

void CUmsVmp::OnVmpConnect( CTpMsg *const ptMsg )
{
#ifdef _USE_XMPUEQP_
	return;
#endif
 	TEqpInfo tInfo;
 	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	TBrdVmpRes* ptVmp  = FindBrdVmpByEqp(tInfo.m_byEqpID);
	if ( NULL != ptVmp )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnVmpConnect. ptVmp is already exit. EqpID:%d\n", tInfo.m_byEqpID));
		return ;
	}
	else
	{
		ptVmp = FindIdleBrdVmp();
		if (NULL == ptVmp)
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::OnVmpConnect. ptVmp is NULL, no idle. EqpID:%d\n", tInfo.m_byEqpID));
			return;
		}
	}

 	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnVmpConnect. EqpID:%d, EqpAlias:%s\n", tInfo.m_byEqpID, tInfo.m_szEqpAlias));

 	memcpy(&ptVmp->m_tEqpInfo, &tInfo, sizeof(tInfo));
 	ptVmp->m_emStat = EmBrdVmpStat_Idle;
 	ptVmp->m_tEqpRes.m_byEqpID = tInfo.m_byEqpID;

	NotifyBrdVmpToAllConf(ptVmp, tp_OprType_Add);

	return ;
}

void CUmsVmp::OnVmpDisConnect( CTpMsg *const ptMsg )
{
	TEqpInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	TBrdVmpRes* ptVmp = FindBrdVmpByEqp(tInfo.m_byEqpID);
	if ( NULL == ptVmp )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnVmpDisConnect. ptVmp is NULL! EqpID:%d\n", tInfo.m_byEqpID));
		return ;
	}

	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(ptVmp->m_wConfID));
	if ( pInst != NULL )
	{
		if( ptVmp->m_emStat == EmBrdVmpStat_Brd )
		{//��ѡ�������ڹ㲥 ��Ҫֹͣ
			TBrdVmpReq tReq;
			tReq.m_wConfID = pInst->GetInsID();
			tReq.m_bBrd = FALSE;
			memcpy(&tReq.m_tEqp, &ptVmp->m_tEqpInfo, sizeof(tReq.m_tEqp));

			pInst->GetVmp()->BrdVmp(tReq);	
		}

		if( ptVmp->m_emStat == EmBrdVmpStat_Normal )
		{
			pInst->GetVmp()->ReleaseBrdVmpParam(ptVmp);
		}
	}

    EmBrdVmpCBOprType emOpr = EmBrdVmpCBOprType_DisConnect;
	if( NULL != ptVmp->m_pfSelViewCB )
	{
		ptVmp->m_pfSelViewCB(ptVmp->m_pSelViewParam, ptVmp, &emOpr);
	}

	if( NULL != ptVmp->m_pfTvWallCB )
	{
		ptVmp->m_pfTvWallCB(ptVmp->m_pTvWallParam, ptVmp, &emOpr);
	}

	if( NULL != ptVmp->m_pfGetVmpCB )
	{
		ptVmp->m_pfGetVmpCB(ptVmp->m_pGetVmpParam, ptVmp, &emOpr);
	}

	NotifyBrdVmpToAllConf(ptVmp, tp_OprType_Del);

	ptVmp->Clear();
	
	return ;
}

//�ϳ�����ǰ����᳡����ؼ�֡
void CUmsVmp::OnVmpAskFrameToEp( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TTPVmpAskFrame tAskFrame;
	TP_SAFE_CAST(tAskFrame, ptMsg->GetBody());

	TBrdVmpRes* ptVmp = FindBrdVmpByEqp(tAskFrame.m_byEqpID);
	if ( NULL == ptVmp || tAskFrame.m_byChanIndx >= TP_VMP_MAX_IN_CHN_NUM )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::OnVmpAskFrameToEp. no need Vmp! ConfID:%d, EqpID:%d, ChanIndx:%d\n", 
				pInst->GetInsID(), tAskFrame.m_byEqpID, tAskFrame.m_byChanIndx));
		return ;
	}
	
	MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::OnVmpAskFrameToEp. ConfID:%d, EpID:%d, EqpID:%d ChanIndx:%d\n", 
												pInst->GetInsID(), m_wVmpEpID, tAskFrame.m_byEqpID, tAskFrame.m_byChanIndx));

	TUmsVidFormat tVidFormat;
	for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++)
	{
		if(ptVmp->m_atMember[wIndex].IsVidGet())
		{
			CUmsConfInst::m_pcGetVidEx->AskKeyFrame(ptVmp->m_atMember[wIndex].m_wGetIndex, TRUE);
		}
		else if (ptVmp->m_tVmpStyle.m_wDualIndx == wIndex)
		{
			pInst->GetDualMgr()->AskFrameForSeeDual(tVidFormat, FALSE, TRUE);
		}
		else
		{

		}
	}

	return ;
}


// ѭ������
#define UmsVmpOprCycle(wIII, wIIIEnd, OprFun)\
	for (wIII = 0; wIII < wIIIEnd; wIII++)\
{\
	    OprFun;}\

// TTPMediaTransAddr
#define UmsVmpPrintAddr(Index, Addr) if (1){\
	msgprintnotime("  Index:%d, Rtp("ADDRPORT_FORMAT"), BackRtcp("ADDRPORT_FORMAT")\n"\
	, Index, ADDRNET(Addr.m_tRtpAddr), ADDRNET(Addr.m_tBackRtcpAddr));}


void CUmsVmp::Show()
{
	CUmsConfInst* pInst = Inst();
	
	msgprintnotime("\n --------umsvmp-------- \n");

	if ( CUmsConfInst::inst_idle != pInst->CurState() )
	{
		msgprintnotime("\n");
		msgprintnotime("\SpeakerVmp Info\n");

		msgprintnotime(" ConfID:%d, SpeakerVmpCfg:%d, emType:%d (0:none,1:chair,2:speaker), VmpEpID:%d.\n"
			,pInst->GetInsID(), m_bSpeakerVmpCfg, m_emVmpType, m_wVmpEpID);
		
		if ( m_pcSpeakerVmp )
		{
			CUmsConfInst::GetVmpServiceHandle()->Show(m_pcSpeakerVmp);

			TTPDsFrom tAddr0;
			TTPDsFrom tAddr1;
			TTPDsFrom tAddr2;
			TTPDsFrom tAddr3;
			GetSpeakerVmpInAddr(tAddr0, 0);
			GetSpeakerVmpInAddr(tAddr1, 1);
			GetSpeakerVmpInAddr(tAddr2, 2);
			GetSpeakerVmpInAddr(tAddr3, 3);
			
			msgprintnotime("  VmpID:%d, BigScreen(Rtp:%d, Rtcp:%d), Screen0(Rtp:%d,Rtcp:%d), Screen1(Rtp:%d,Rtcp:%d), Screen2(Rtp:%d,Rtcp:%d)\n",
				m_pcSpeakerVmp == NULL ? 0 : m_pcSpeakerVmp->GetServiceID(),
				tAddr0.m_tRtpAddr.GetPort(), tAddr0.m_tBackRtcpAddr.GetPort(), 
				tAddr1.m_tRtpAddr.GetPort(), tAddr1.m_tBackRtcpAddr.GetPort(),
				tAddr2.m_tRtpAddr.GetPort(), tAddr2.m_tBackRtcpAddr.GetPort(),
				tAddr3.m_tRtpAddr.GetPort(), tAddr3.m_tBackRtcpAddr.GetPort());
			
			GetSpeakerVmpOutAddr(tAddr0);
			msgprintnotime("  SpeakerVmpOut(Rtp:%d, Rtcp:%d)\n",
				tAddr0.m_tRtpAddr.GetPort(), tAddr0.m_tBackRtcpAddr.GetPort());
		}

		msgprintnotime("\n");
		msgprintnotime("\nVmpCfg Info\n");

		msgprintnotime(" Style:%d, EpNum:%d, SpeakIndex:%d, DualIndex:%d.\n", 
			m_tVmpCfg.m_emStyle, m_tVmpCfg.m_wEpNum,
			m_tVmpCfg.m_wSpeakerIndx, m_tVmpCfg.m_wDualIndx);
		for(u16 wLoop = 0; wLoop < m_tVmpCfg.m_wEpNum; wLoop++)
		{
			msgprintnotime("  wLoop:%d, EpAlias:%s, EpScreenIndex:%d.\n", 
				wLoop, m_tVmpCfg.m_atEpList[wLoop].m_tEpAlias.m_abyAlias, m_tVmpCfg.m_atEpList[wLoop].m_wScrIndx); 
		}
	}

	msgprintnotime("\n");
	msgprintnotime("\nBrdVmp Info\n");
	TBrdVmpRes* ptVmp = NULL;
	TBrdVmpMember* ptMember = NULL;
	TTPMediaTransAddr tAddr;
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( 0 == m_atBrdVmp[wIndex].m_tEqpRes.m_byEqpID)
		{
			continue;
		}

		ptVmp = &m_atBrdVmp[wIndex];

		msgprintnotime(" ConfID:%d, EqpInfo: EqpID:%d, Name:%s, UmsStartPort:%d, EqpStartPort:%d, EqpMdlType:%d\n", ptVmp->m_wConfID,
			ptVmp->m_tEqpRes.m_byEqpID, ptVmp->m_tEqpInfo.m_szEqpAlias, ptVmp->m_tEqpRes.m_wUmsStartPort, ptVmp->m_tEqpRes.m_wEqpStartPort, ptVmp->m_tEqpRes.m_emMdlType);

		msgprintnotime("   MemberNum:%d, Stat:%d(0:invalid;1:idle;2:normal;3:brd;4:error), VmpAuto:%d, NeedAdjVip:%d, VipNum:%d, CurVipNum:%d\n", 
			ptVmp->m_wMemberNum, ptVmp->m_emStat, ptVmp->m_bVmpAuto, ptVmp->m_bNeedAdjVip, ptVmp->m_wVipNum, ptVmp->m_wCurVipNum);

		msgprintnotime("   UIInfo MemberNum:%d, SpeakerIndx:%d, DualIndx:%d, VmpStyle:%d\n", 
			ptVmp->m_wMemberNum, ptVmp->m_tVmpStyle.m_wSpeakerIndx, ptVmp->m_tVmpStyle.m_wDualIndx, ptVmp->m_tVmpStyle.m_emVmpStyle);

		for ( u16 wMemberIndx = 0; wMemberIndx < ptVmp->m_wMemberNum; wMemberIndx ++ )
		{
			ptMember = &ptVmp->m_atMember[wMemberIndx];
			msgprintnotime("   Member%d,  EpID:%d,  ScrIndx:%d,  stat:%d,  Vip:%d,  Ds:%d,  SmallVid:%d,  AdjustRes:%d,  GetIndex:%d\n", 
				wMemberIndx, ptMember->m_tVmpMember.m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_tVmpMember.m_byStat, 
				ptMember->m_byVip, ptMember->m_byDs, ptMember->m_bySmallVid, ptMember->m_byAdjustRes, ptMember->m_wGetIndex);
			
			if (ptMember->IsDs() && (ptMember->m_wGetIndex < TP_UMS_MAX_CALLNUM))
			{
				//UmsVmpOprCycle(wLoop, TP_MAX_STREAMNUM, UmsVmpPrintAddr(wLoop, ptMember->m_tGetAddr.m_atVidAddr[wLoop]));
				msgprintnotime("   [Local]");
				if (ptMember->IsSmallVid())
				{
					UmsVmpPrintAddr(ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_tGetAddr.m_atSmallAddr[MIDSCREENINDEX]);
				}
				else
				{
					UmsVmpPrintAddr(ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_tGetAddr.m_atVidAddr[MIDSCREENINDEX]);
				}
				GetBrdVmpInAddr(ptVmp, tAddr, wMemberIndx);
				msgprintnotime("   [In]   ");
				UmsVmpPrintAddr(ptMember->m_tVmpMember.m_wScreenIndx, tAddr);
			}
		}
		msgprintnotime("\n");
	}

	msgprintnotime("\n --------umsvmp end-------- \n");

	return ;
}

EmBrdVmpRet CUmsVmp::SetBrdVmp( TSetVmpInfoReq& tBrdReq )
{
	if (Inst()->CurState() == CUmsConfInst::inst_idle)
	{
		return EmBrdVmpRet_Fail;
	}

	TBrdVmpRes* ptVmpRes = FindBrdVmpByEqp(tBrdReq.m_tEqp.m_byEqpID);
	if ( NULL == ptVmpRes || !ptVmpRes->IsRersves())
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::SetBrdVmp. ptVmpRes is NULL! ConfID:%d, EqpID:%d, bRersvesConId:%d\n", 
			Inst()->GetInsID(), tBrdReq.m_tEqp.m_byEqpID, ptVmpRes == NULL ? 0 : ptVmpRes->m_wConfID));
		return EmBrdVmpRet_NoExist;
	}
	
	//
	u16 wChanNum = localmin(CTpTypeAdpt::GetVmpMemberNumByStyle(tBrdReq.m_tStyle.m_emVmpStyle), tBrdReq.m_tStyle.m_wChnlNum);
	tBrdReq.m_tStyle.m_wChnlNum = wChanNum;
	tBrdReq.m_tStyle.ClearChnl(wChanNum);

	ptVmpRes->SetUIInfo(tBrdReq);
	
	UpdateBrdVmpParam(ptVmpRes);

	if (EmBrdVmpStat_Idle == ptVmpRes->m_emStat)
	{
		ptVmpRes->m_emStat = EmBrdVmpStat_Normal;
	}
	
	return EmBrdVmpRet_Succes;
}

EmRervesVmpRet CUmsVmp::RerveseBrdVmp( TRersvesEqpReq& tReq )
{
	if (Inst()->CurState() == CUmsConfInst::inst_idle)
	{
		return EmRervesVmpRet_unKnow;
	}

	TBrdVmpRes* ptVmpRes = NULL;
	TVmpParam tVmpParam;

	ptVmpRes = FindBrdVmpByEqp(tReq.m_tEqp.m_byEqpID);
	if ( NULL == ptVmpRes )
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseBrdVmp. ptVmpRes is NULL! ConfID:%d, EqpID:%d\n", 
			Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID));
		return EmRervesVmpRet_NoExist;
	}

	if ( tReq.m_bRersves )
	{//ռ��

		if( ptVmpRes->IsRersves())
		{
			if (ptVmpRes->m_wConfID == Inst()->GetInsID())
			{
				MdlHint(Ums_Mdl_Call, ("CUmsVmp::RerveseBrdVmp. repeat rervese! rsp is ok! ConfID:%d, RerConfID:%d, EqpID:%d\n", 
				Inst()->GetInsID(), ptVmpRes->m_wConfID, tReq.m_tEqp.m_byEqpID));
				return EmRervesVmpRet_Success;
			}
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseBrdVmp. busy! ConfID:%d, RerConfID:%d, EqpID:%d\n", 
				Inst()->GetInsID(), ptVmpRes->m_wConfID, tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_Busy;
		}

		//���� �� �����ϳ� 
		u8 byOutNum = 0;
		TUmsVidFormat atVidFormat[TP_VMP_MAX_OUT_CHN_NUM];

		// ��ģ�������и�ʽ��
		for (u16 wIndex = 0; wIndex < localmin(Inst()->m_tConfBaseInfo.m_wMainNum, TP_VMP_MAX_OUT_CHN_NUM-1); wIndex++)
		{
			atVidFormat[byOutNum] = Inst()->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex];
			byOutNum++;
		}

		tVmpParam.SetParam(Inst()->GetInsID(), byOutNum, atVidFormat, &ptVmpRes->m_tEqpRes);
		if ( !AssignEqpEx(&tVmpParam) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseBrdVmp. AssignEqpEx Failed! ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_unKnow;
		}

		ptVmpRes->m_wConfID = Inst()->GetInsID();
	}
	else
	{//ȡ��ռ��

		if(!ptVmpRes->IsRersves() || ptVmpRes->m_wConfID != Inst()->GetInsID())
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseBrdVmp. NoExist! ConfID:%d, RerConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_wConfID, tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_NoExist;
		}

		if ( ptVmpRes == m_ptConfBrdVmp )
		{//ȡ�����ǵ�ǰ�㲥�����裬����Ҫ��ֹͣ
			TBrdVmpReq tReq;
			tReq.m_wConfID = Inst()->GetInsID();
			tReq.m_bBrd = FALSE;
			memcpy(&tReq.m_tEqp, &ptVmpRes->m_tEqpInfo, sizeof(tReq.m_tEqp));		
			BrdVmp(tReq);
		}

		if (ptVmpRes->m_emStat == EmBrdVmpStat_Normal)
		{
			ReleaseBrdVmpParam(ptVmpRes);
		}

		tVmpParam.m_ptEqpRes = &ptVmpRes->m_tEqpRes;
		if ( !ReleaseEqpEx(&tVmpParam) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseBrdVmp. ReleaseEqpEx Failed! ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_tEqpRes.m_byEqpID));
			ptVmpRes->m_emStat = EmBrdVmpStat_Error;
			return EmRervesVmpRet_unKnow;
		}

        EmBrdVmpCBOprType emOpr = EmBrdVmpCBOprType_Stop;

		if( NULL != ptVmpRes->m_pfSelViewCB )
		{
			ptVmpRes->m_pfSelViewCB(ptVmpRes->m_pSelViewParam, ptVmpRes, &emOpr);
		}

		if( NULL != ptVmpRes->m_pfTvWallCB )
		{
			ptVmpRes->m_pfTvWallCB(ptVmpRes->m_pTvWallParam, ptVmpRes, &emOpr);
		}
		
		if( NULL != ptVmpRes->m_pfGetVmpCB )
		{
			ptVmpRes->m_pfGetVmpCB(ptVmpRes->m_pGetVmpParam, ptVmpRes, &emOpr);
		}

		ptVmpRes->m_emStat = EmBrdVmpStat_Idle;
		ptVmpRes->m_wConfID = TP_INVALID_INDEX;
	}

	return EmRervesVmpRet_Success;
}

void CUmsVmp::StartBrdVmpReq(TBrdVmpRes* ptVmpRes)
{
	//�����ϳ�
	CTpMsg cMsg;
	
	//���ϳɰ� ���ص� ����ת����
	TBasSndAddr tSndAddr;
	tSndAddr.m_byEqpID = ptVmpRes->m_tEqpRes.m_byEqpID;
	tSndAddr.m_dwNewDsIP = Inst()->m_tEqpConfDs.m_dwEqpIp;
	
	cMsg.SetEvent(ev_TPEqp_ChangeSndAddr_Req);
	cMsg.SetBody(&tSndAddr, sizeof(tSndAddr));
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	
	// �����ϳ�
	TTVmpStartParam tVmpParam;
	tVmpParam.m_emVmpStyle = ptVmpRes->m_tVmpStyle.m_emVmpStyle;
	tVmpParam.m_byVMPMemberNum = (u8)ptVmpRes->m_wMemberNum;
	for (u16 wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex++)
	{
		tVmpParam.m_atVMPMember[wIndex] = ptVmpRes->m_atMember[wIndex].m_tVmpMember;
	}
	cMsg.SetEvent(evtp_StartVmp_Req);
	cMsg.SetBody(&ptVmpRes->m_tEqpRes.m_byEqpID, sizeof(u8));
	cMsg.CatBody(&tVmpParam, sizeof(TTVmpStartParam));
	cMsg.Post(ptVmpRes->m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	CUmsConfInst* pInst = Inst();
	for (u8 byIndx = 0; byIndx < TP_MAX_OLD_KEY_NUM; byIndx++)
	{
		if (0 == pInst->m_atMediaKey[byIndx].m_dwQtFlag)
		{
			continue;
		}
		
		SetQtMediaKey(Inst()->m_atMediaKey[byIndx], pInst->GetInsID());
	}

	return ;
}

EmBrdVmpRet CUmsVmp::BrdVmp( TBrdVmpReq& tReq )
{
	if ( !Inst()->IsChairConf())
	{// �ϼ��Ź㲥
		return EmBrdVmpRet_DownUmsFail;
	}

	if (Inst()->CurState() == CUmsConfInst::inst_idle)
	{
		return EmBrdVmpRet_Fail;
	}

	if ( !tReq.m_bBrd )
	{
		if ( NULL == m_ptConfBrdVmp )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::BrdVmp. m_ptConfBrdVmp is NULL! ConfID:%d, EqpID:%d\n", 
				Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID));
			return EmBrdVmpRet_NoExist;
		}

		if ( m_ptConfBrdVmp->m_tEqpRes.m_byEqpID != tReq.m_tEqp.m_byEqpID )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::BrdVmp. ReqEqp is no Brd! ConfID:%d, ReqEqpID:%d, CurEqpID:%d\n", 
				Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID, m_ptConfBrdVmp->m_tEqpRes.m_byEqpID));
			return EmBrdVmpRet_Fail;
		}

		memset(m_szBrdVmpAlias, 0, sizeof(m_szBrdVmpAlias));

		AdjustNodeObjToBrdVmp(tReq.m_bBrd);

		m_ptConfBrdVmp->m_emStat = EmBrdVmpStat_Normal;

		m_ptConfBrdVmp = NULL;
	}
	else
	{
		TBrdVmpRes*	ptVmpRes = FindBrdVmpByEqp(tReq.m_tEqp.m_byEqpID);
		if ( NULL == ptVmpRes || ptVmpRes->m_wConfID != Inst()->GetInsID() )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::BrdVmp. ptVmpRes is NULL! ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID));
			return EmBrdVmpRet_NoExist;
		}

		if ( ptVmpRes == m_ptConfBrdVmp )
		{
			return EmBrdVmpRet_Busy;
		}

		if (ptVmpRes->m_emStat != EmBrdVmpStat_Normal)
		{
			return EmBrdVmpRet_Fail;
		}

		// ��Ŀ��ǰ����Ҫ��Ŀ�����ָ�ֵ
		strncpy(m_szBrdVmpAlias, ptVmpRes->m_tEqpInfo.m_szEqpAlias, TP_MAXLEN_EQP_ALIAS);
		m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';

		if ( NULL == m_ptConfBrdVmp )
		{
			AdjustNodeObjToBrdVmp(tReq.m_bBrd);
		}
		else
		{// ����ǰ�Ĺ㲥�ϳ�����Ϊnormal״̬
			m_ptConfBrdVmp->m_emStat = EmBrdVmpStat_Normal;
			NotifyBrdVmpToAllConf(m_ptConfBrdVmp->m_tEqpRes.m_byEqpID, tp_OprType_Update);
		}

		//ͬһʱ��ֻ��һ���㲥
		m_ptConfBrdVmp = ptVmpRes;
		ptVmpRes->m_emStat = EmBrdVmpStat_Brd;
	}

	m_bBrdVmp = tReq.m_bBrd;

	//���������ⷢ���˵Ľ���
	CNetPortMgr::CreateSpeakerToVirSpeaker(Inst());
	
	return EmBrdVmpRet_Succes;
}

void CUmsVmp::GetBrdVmpOutAddr(TBrdVmpRes* ptVmpRes, TTPDsFrom& tAddr, TUmsVidFormat& tVidFmt, BOOL32 bIsToVirSpeaker /* = FALSE */)
{
	CUmsConfInst* pInst = Inst();

	if (NULL != ptVmpRes)
	{// �¼�Ҳ���Լ��ĺϳ������¼��޹㲥�ϳ�
		u16 wOutIndx = TP_INVALID_INDEX;
		if (bIsToVirSpeaker)
		{
			wOutIndx = CTpTypeAdpt::GetRcvFormatForSnd(tVidFmt, pInst->m_tConfBaseInfo);
		}
		else
		{
			wOutIndx = CTpTypeAdpt::GetRcvFormat(tVidFmt, pInst->m_tConfBaseInfo.m_atTpMainVideoRes, pInst->m_tConfBaseInfo.m_wMainNum);
		}

		if( !TP_VALID_HANDLE(wOutIndx) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::GetBrdVmpOutAddr. Invaild ChnIndx ! ConfID:%d, EqpID:%d, bIsFromVirSpeaker:%d, Res:%d.\n",
			pInst->GetInsID(), ptVmpRes->m_tEqpRes.m_byEqpID, bIsToVirSpeaker, tVidFmt.m_emRes));
			return ;
		}
		
#ifdef _USE_XMPUEQP_
		tAddr.m_tRtpAddr.SetAddr(ptVmpRes->m_atEncRtpAddr[wOutIndx].m_dwIP, ptVmpRes->m_atEncRtpAddr[wOutIndx].m_wPort);
		tAddr.m_tBackRtcpAddr.SetAddr(ptVmpRes->m_atEncMiddleRtcpAddr[wOutIndx].m_dwIP, ptVmpRes->m_atEncMiddleRtcpAddr[wOutIndx].m_wPort);
		tAddr.m_dwEqpNode = Inst()->m_tEqpConfDs.m_dwEqpNode;
#else
		tAddr.m_tRtpAddr.SetAddr(Inst()->m_tEqpConfDs.m_dwEqpIp, ptVmpRes->m_tEqpRes.m_wUmsStartPort + wOutIndx*UMS_MCU_PORT_PORTSPAN);
		tAddr.m_tBackRtcpAddr.SetAddr(ptVmpRes->m_tEqpRes.m_dwEqpIp, ptVmpRes->m_tEqpRes.m_wUmsStartPort + wOutIndx*UMS_MCU_PORT_PORTSPAN +1 );
		tAddr.m_dwEqpNode = Inst()->m_tEqpConfDs.m_dwEqpNode;
#endif
	}
	else
	{// �¼��Ĺ㲥�ϳɣ����ϼ��´�
		TCapNode* ptCaller = pInst->GetNodeMgr()->GetCaller();
		if ( NULL != ptCaller && ptCaller->IsChanOn())
		{

			if (pInst->curSpeakerID() == ptCaller->m_wEpID)
			{// ���������ϼ����㲥�ϳ��ڷ�����ͨ�����м�·
				tAddr.m_tRtpAddr = ptCaller->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtpAddr;
				tAddr.m_tBackRtcpAddr = ptCaller->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				tAddr.m_dwEqpNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
			}
			else
			{// �����˲����ϼ����㲥�ϳ�����ϯͨ�����м�·
				if (NULL != ptCaller->m_ptCasCadeChairAddr)
				{
					tAddr.m_tRtpAddr = ptCaller->m_ptCasCadeChairAddr->m_atVid[MIDSCREENINDEX].m_tRtpAddr;
					tAddr.m_tBackRtcpAddr = ptCaller->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr;
					tAddr.m_dwEqpNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
				}
			}
		}
	}

	return ;
}

void CUmsVmp::GetBrdVmpInAddr( TBrdVmpRes* ptVmpRes, TTPMediaTransAddr& tAddr, u16 wChnIndx )
{
#ifdef _USE_XMPUEQP_
	tAddr.m_tRtpAddr.SetAddr(ptVmpRes->m_atDecMiddleRtpAddr[wChnIndx].m_dwIP, ptVmpRes->m_atDecMiddleRtpAddr[wChnIndx].m_wPort);
	tAddr.m_tBackRtcpAddr.SetAddr(ptVmpRes->m_atDecRtcpAddr[wChnIndx].m_dwIP, ptVmpRes->m_atDecRtcpAddr[wChnIndx].m_wPort);
	return;
#endif
	tAddr.m_tRtpAddr.SetAddr(ptVmpRes->m_tEqpRes.m_dwEqpIp, ptVmpRes->m_tEqpRes.m_wEqpStartPort + wChnIndx*UMS_MCU_PORT_PORTSPAN );
	u16 wRtcpBackPort = ptVmpRes->m_tEqpRes.m_wUmsStartPort;
	if (wChnIndx >= 24)
	{
		wRtcpBackPort += (8+wChnIndx); // 32
	}
	else if (wChnIndx >= 16)
	{
		wRtcpBackPort += (6+wChnIndx); // 22~29
	}
	else if (wChnIndx >= 8)
	{
		wRtcpBackPort += (4+wChnIndx); // 12~19
	}
	else
	{
		wRtcpBackPort += (2+wChnIndx);// 2~9
	}
	tAddr.m_tBackRtcpAddr.SetAddr(Inst()->m_tEqpConfDs.m_dwEqpIp, wRtcpBackPort );
	return ;
}

void CUmsVmp::AdjustNodeObjToBrdVmp( BOOL32 bStart )
{
	TVmpCasecadeNtfy tNtfy;
	tNtfy.m_bBrdVmp = bStart;
	tNtfy.m_emSpeakerVmpType = m_emVmpType;
	strncpy(tNtfy.m_szBrdVmpAlias, m_szBrdVmpAlias, TP_MAXLEN_EQP_ALIAS);
	tNtfy.m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';

	TUmsHandle tHandle;
	//�����㲥 �������ⷢ�����м�ڵ� ������ÿ���ڵ�Ĺ㲥Ŀ��
	for (TCapNode* ptNode = Inst()->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = Inst()->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if ( !ptNode->IsChanOn() )
		{
			continue;
		}

		if ( ptNode->IsUms() )
		{//UMS��Ҫ�Ǳ�����֪ͨ���������ϳ�
			Inst()->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			UmsSendConfCtrl(tHandle, ev_UMS_UMS_VmpCasecade_Ntfy, &tNtfy, sizeof(tNtfy));
		}

		if ( bStart )
		{
			Inst()->GetNodeFsm()->StartVmpBrd(ptNode);
		}
		else
		{
			Inst()->GetNodeFsm()->StopVmpBrd(ptNode);
		}
	}

	return ;
}

TBrdVmpRes* CUmsVmp::FindIdleBrdVmp()
{
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].IsRersves() )
		{
			continue;
		}

		if ( 0 != m_atBrdVmp[wIndex].m_tEqpRes.m_byEqpID)
		{
			continue;
		}

		return &m_atBrdVmp[wIndex];
	}

	return NULL;
}

TBrdVmpRes* CUmsVmp::FindBrdVmpByEqp( u16 wEqpID )
{
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_tEqpRes.m_byEqpID == wEqpID )
		{
			return &m_atBrdVmp[wIndex];
		}
	}

	return NULL;
}

void CUmsVmp::OnCasecadeVmpNtfy( CTpMsg *const ptMsg )
{

	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TVmpCasecadeNtfy tNtfy;
	TP_SAFE_CAST(tNtfy, ptMsg->GetBody() + sizeof(TUmsHandle));

	CUmsConfInst* pInst = Inst();
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnCasecadeVmpNtfy. ConfID:%d, BrdVmp:%d, emSpeakerVmp:%d, Alias:%s\n", 
							pInst->GetInsID(), tNtfy.m_bBrdVmp, tNtfy.m_emSpeakerVmpType, tNtfy.m_szBrdVmpAlias));

	do 
	{
		if (em_Vmp_Invalid != tNtfy.m_emSpeakerVmpType)
		{// �ϼ�֪ͨ���¼����뷢���˺ϳɣ��¼���������㲥��������ͨ��
			if ( em_Vmp_Invalid == m_emVmpType )
			{
				if (pInst->TryAssignVirSingleBas())
				{
					m_emVmpType = tNtfy.m_emSpeakerVmpType;
				}
			}
			else
			{
				pInst->TryAdjustVirSingleBas();
				m_emVmpType = tNtfy.m_emSpeakerVmpType;
			}
		}
		else if (em_Vmp_Invalid == tNtfy.m_emSpeakerVmpType && em_Vmp_Invalid != m_emVmpType)
		{// �ϼ�֪ͨ, �¼��˳������˺ϳɣ��¼������ͷŹ㲥��������ͨ��
			m_emVmpType = tNtfy.m_emSpeakerVmpType;
			pInst->TryReleaseVirSingleBas();
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnCasecadeVmpNtfy. speakervmp not changed! ConfID:%d, emSpeakerVmp:%d, m_emVmpType:%d\n", 
												pInst->GetInsID(), tNtfy.m_emSpeakerVmpType, m_emVmpType));
		}

	} while (0);

	// 
	pInst->GetBas()->AdjustSpeakerBasForBrdVmp(tNtfy.m_bBrdVmp);

	//���������ⷢ���˵Ľ���
	CNetPortMgr::CreateSpeakerToVirSpeaker(pInst);

	if ( m_bBrdVmp != tNtfy.m_bBrdVmp || 0 != strcmp(m_szBrdVmpAlias, tNtfy.m_szBrdVmpAlias) )
	{
		strncpy(m_szBrdVmpAlias, tNtfy.m_szBrdVmpAlias, TP_MAXLEN_EQP_ALIAS);
		m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';

		m_bBrdVmp = tNtfy.m_bBrdVmp;
		AdjustNodeObjToBrdVmp(tNtfy.m_bBrdVmp);
	}

	return ;
}

void CUmsVmp::NotifyAllBrdVmpToCNC( u16 wEpID )
{
	TBrdVmpResArray tArray;
	
	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, wEpID);
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Invalid )
		{
			continue;
		}
		
		m_atBrdVmp[wIndex].GetUIInfo(tArray.m_atVmpNtfy[tArray.m_wNum]);
		tArray.m_atVmpNtfy[tArray.m_wNum].m_emOpr = tp_OprType_Add;
		tArray.m_atVmpNtfy[tArray.m_wNum].m_bVmpAuto = m_atBrdVmp[wIndex].m_bVmpAuto;
		tArray.m_wNum ++;
		
		if( tArray.m_wNum == TP_REFRESH_LIST_THREE )
		{
			UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_BrdVmp_Ntfy, &tArray, sizeof(tArray));
			tArray.Clear();
		}
	}
	
	if( tArray.m_wNum > 0 )
	{
		UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_BrdVmp_Ntfy, &tArray, sizeof(tArray));
	}
	
	if( wEpID == Inst()->chairID() )
	{
		NotifyBrdVmpCfgToUI(TRUE, FALSE, NULL);
	}
}

void CUmsVmp::NotifyAllBrdVmpToUMC( TLogUser* ptUser )
{
	TBrdVmpResArray tArray;
	
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Invalid )
		{
			continue;
		}

		m_atBrdVmp[wIndex].GetUIInfo(tArray.m_atVmpNtfy[tArray.m_wNum]);
		tArray.m_atVmpNtfy[tArray.m_wNum].m_emOpr = tp_OprType_Add;
		tArray.m_atVmpNtfy[tArray.m_wNum].m_bVmpAuto = m_atBrdVmp[wIndex].m_bVmpAuto;
		tArray.m_wNum ++;

		if( tArray.m_wNum == TP_REFRESH_LIST_THREE )
		{
			Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_BrdVmp_Ntfy, &tArray, sizeof(tArray), ptUser);
			tArray.Clear();
		}
	}
	
	if( tArray.m_wNum > 0 )
	{
		Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_BrdVmp_Ntfy, &tArray, sizeof(tArray), ptUser);
	}

	NotifyBrdVmpCfgToUI(FALSE, TRUE, ptUser);
}

void CUmsVmp::NotifyBrdVmpToAllConf( TBrdVmpRes* ptVmpRes, EmTpOprType emOpr )
{
	CUmsConfInst* pInst = NULL;
	//�������л���
	for ( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex ++ )
	{
		pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wIndex));
		if ( pInst == NULL )
		{
			continue;
		}
		
		if ( pInst->CurState() == CUmsConfInst::inst_idle
			|| pInst->m_bIsQuiting )
		{
			continue;
		}
		
		pInst->GetVmp()->NotifyBrdVmpToCNC(ptVmpRes, emOpr);
	}

	NotifyBrdVmpToUMC(ptVmpRes, emOpr);

	return;
}

void CUmsVmp::NotifyBrdVmpToAllConf( u8 byEqpID, EmTpOprType emOpr )
{
	TBrdVmpRes*	ptVmpRes = FindBrdVmpByEqp(byEqpID);
	if ( NULL == ptVmpRes )
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::NotifyBrdVmpToAllConf. ptVmpRes is NULL! EqpID:%d\n", byEqpID));
		return ;
	}

	NotifyBrdVmpToAllConf(ptVmpRes, emOpr);
}

void CUmsVmp::NotifyBrdVmpToCNC( TBrdVmpRes* ptVmpRes, EmTpOprType emOpr )
{

	TBrdVmpResArray tArray;
	tArray.m_wNum = 1;
	ptVmpRes->GetUIInfo(tArray.m_atVmpNtfy[0]);
	tArray.m_atVmpNtfy[0].m_emOpr = emOpr;
	tArray.m_atVmpNtfy[0].m_bVmpAuto = ptVmpRes->m_bVmpAuto;

	// ֻ֪ͨ��ϯ
	TUmsHandle tOutHandle;

	for (TCapNode* ptNode = Inst()->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = Inst()->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if ( !ptNode->IsChanOn() )
		{
			continue;
		}
		
		if ( ptNode->IsB3CNS() || ptNode->Is323Ep() )
		{
			continue;
		}

		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_BrdVmp_Ntfy, &tArray, sizeof(tArray));
	}
}

void CUmsVmp::UpdateBrdVmpParam( TBrdVmpRes* ptVmpRes )
{
	if ( ptVmpRes->m_bVmpAuto )
	{
		AdjustAutoVmpStyle(ptVmpRes);
	}

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::UpdateBrdVmpParam. ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_tEqpInfo.m_byEqpID));

	//����+���
	BackupBrdVmpParam(ptVmpRes);
	ptVmpRes->ReSetMember();

	CUmsConfInst* pInst = Inst();
	u16 wIndex = 0;
	TCallNode* ptNodeTmp = NULL;
	// ��������
	TTPEncrypt tEncrypt = pInst->GetConfEncryptInfo();

	for ( wIndex = 0; wIndex < ptVmpRes->m_tVmpStyle.m_wChnlNum; ++wIndex)
	{//�ֶ� �����uiֵ��ϳɣ��������Чֵ����λ�ÿճ�

		if (wIndex == ptVmpRes->m_tVmpStyle.m_wSpeakerIndx || wIndex == ptVmpRes->m_tVmpStyle.m_wDualIndx)
		{// �ճ������λ��
			ptVmpRes->m_wMemberNum++;
			continue;
		}

		if ( !ptVmpRes->m_tVmpStyle.m_atVmpChnl[wIndex].IsValid() )
		{
			ptVmpRes->m_wMemberNum++;
			continue;
		}
		
		ptNodeTmp = pInst->m_pcNodeMgr->GetNode(ptVmpRes->m_tVmpStyle.m_atVmpChnl[wIndex].m_wEpID);
		if ( NULL == ptNodeTmp )
		{
			ptVmpRes->m_wMemberNum++;
			continue;
		}
		
		ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wEpID = ptNodeTmp->m_wEpID;
		ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wScreenIndx = ptVmpRes->m_tVmpStyle.m_atVmpChnl[wIndex].m_wScrIndx;
		
		if( ptNodeTmp->IsChanOn() && ptNodeTmp->IsVidSndValid() )
		{
			ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wStaticPayload = ptNodeTmp->m_tVidSndFormat.m_wStaticPayload;
			ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wDynamicPayload = ptNodeTmp->m_tVidSndFormat.m_wDynamicPayload;
		}
		ptVmpRes->m_wMemberNum ++;
	}

    u16 wMiniMem = localmin(ptVmpRes->m_wMemberNum, TP_VMP_MAX_IN_CHN_NUM);
	for(u16 wIndexct = 0; wIndexct < wMiniMem; wIndexct++)
	{
        ptVmpRes->m_atMember[wIndexct].m_tVmpMember.m_tEncrypt = tEncrypt;
	}

	//�����������ˡ�˫������
	AdjustSpeakerFollow(ptVmpRes);

	//������Ա����
	AdjustBrdVmpMember(ptVmpRes);

	StartBrdVmpReq(ptVmpRes);

	//��������
	CNetPortMgr::CreateAllMemberToBrdVmp(Inst(), ptVmpRes);

	return ;
}

// ѭ������ 0 1 2 ���� 1
#define UmsVmpAutoOpr(wIII, wIIIEnd, OprFun)\
	for (wIII = 0; wIII < wIIIEnd; wIII++)\
{\
	if (1 == wIIIEnd) wIII = wIIIEnd;\
	    OprFun;}\

void CUmsVmp::AdjustAutoVmpStyle(TBrdVmpRes* ptVmpRes)
{
	if (!ptVmpRes->m_bVmpAuto)
	{
		return;
	}
	
	CUmsConfInst* pInst = Inst();

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::AdjustAutoVmpStyle. ConfID:%d, EqpID:%d\n", pInst->GetInsID(), ptVmpRes->m_tEqpInfo.m_byEqpID));	
	
	u16 awAllEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpAllNum = pInst->m_pcNodeMgr->GetAllNode(awAllEpID, TP_CONF_MAX_CNSNUM);

	u16 wIndex = 0;
	u16 wLoop = 0;
	TCallNode* ptNodeTmp = NULL;
	TBrdVmpStyleOpr tVmpStyleOpr;
	for (wIndex = 0; wIndex < wEpAllNum; wIndex++)
	{// �Զ�����ϳɽ�ͨ�������ȼ������Ի᳡����ϯ�᳡�նˡ������նˡ�H.323�նˡ����նˣ������绰�նˣ����⳧���ն�/����ն�/vrs
		ptNodeTmp = pInst->GetNode(awAllEpID[wIndex]);
		if (NULL == ptNodeTmp || !ptNodeTmp->IsChanOn() || !ptNodeTmp->IsVidSndValid())
		{
			continue;
		}

		if ( ptNodeTmp->IsUms() )
		{
			continue;
		}

		if (ptNodeTmp->m_wEpID == pInst->curSpeakerID())
		{// ���Ի᳡
			UmsVmpAutoOpr(wLoop, ptNodeTmp->m_wVidSndNum,
					tVmpStyleOpr.AddVmpChnl(ptNodeTmp->m_wEpID, wLoop, 1000));
		}
		else if (ptNodeTmp->m_wEpID == pInst->chairID())
		{// ���᳡
			UmsVmpAutoOpr(wLoop, ptNodeTmp->m_wVidSndNum,
				tVmpStyleOpr.AddVmpChnl(ptNodeTmp->m_wEpID, wLoop, 800));
		}
		else if (ptNodeTmp->IsCns())
		{// �����ն�
			UmsVmpAutoOpr(wLoop, ptNodeTmp->m_wVidSndNum, 
				tVmpStyleOpr.AddVmpChnl(ptNodeTmp->m_wEpID, wLoop, 500));
		}
		else if (ptNodeTmp->Is323Ep() && !ptNodeTmp->IsG400() && !ptNodeTmp->IsVRS())
		{// h323�նˣ�����������ն�, vrs��
			UmsVmpAutoOpr(wLoop, ptNodeTmp->m_wVidSndNum, 
				tVmpStyleOpr.AddVmpChnl(ptNodeTmp->m_wEpID, wLoop, 200));
		}
		else
		{// ����
			UmsVmpAutoOpr(wLoop, ptNodeTmp->m_wVidSndNum, 
				tVmpStyleOpr.AddVmpChnl(ptNodeTmp->m_wEpID, wLoop, 50));
		}
	}

	EMVmpStyle emVmpStyle = FindStyleByMTNum(tVmpStyleOpr.m_wChnlNum);

	ptVmpRes->m_tVmpStyle.Clear();
	// ȷ�����ʵĺϳɷ��
	ptVmpRes->m_tVmpStyle.m_emVmpStyle = emVmpStyle;
	ptVmpRes->m_tVmpStyle.m_wChnlNum = tVmpStyleOpr.m_wChnlNum;
	memcpy(ptVmpRes->m_tVmpStyle.m_atVmpChnl, tVmpStyleOpr.m_atVmpChnl, sizeof(tVmpStyleOpr.m_atVmpChnl));
	
	return;
}

void CUmsVmp::AdjustSpeakerFollow(TBrdVmpRes* ptVmpRes)
{
	TCallNode* ptNodeTmp = NULL;
	u16 wEpId = 0;

	CUmsConfInst* pInst = Inst();
	TTPEncrypt tEncrypt = pInst->GetConfEncryptInfo();
	if ( TP_VALID_HANDLE(ptVmpRes->m_tVmpStyle.m_wSpeakerIndx) )
	{
		wEpId = pInst->curSpeakerID();
		ptNodeTmp = pInst->m_pcNodeMgr->GetNode(wEpId);
		if( NULL != ptNodeTmp && ptNodeTmp->IsChanOn() )
		{
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wSpeakerIndx].m_tVmpMember.m_wEpID = ptNodeTmp->m_wEpID;
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wSpeakerIndx].m_tVmpMember.m_wScreenIndx = ptNodeTmp->GetSpeaker();
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wSpeakerIndx].m_tVmpMember.m_wStaticPayload = ptNodeTmp->m_tVidSndFormat.m_wStaticPayload;
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wSpeakerIndx].m_tVmpMember.m_wDynamicPayload = ptNodeTmp->m_tVidSndFormat.m_wDynamicPayload;
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wSpeakerIndx].m_tVmpMember.m_tEncrypt = tEncrypt;
		}
		else
		{
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wSpeakerIndx].Clear();
		}
	}
	if ( TP_VALID_HANDLE(ptVmpRes->m_tVmpStyle.m_wDualIndx) )
	{
		wEpId = pInst->GetDualMgr()->GetDualID();
		ptNodeTmp = pInst->m_pcNodeMgr->GetNode(wEpId);
		if( NULL != ptNodeTmp && ptNodeTmp->IsChanOn())
		{
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wDualIndx].m_tVmpMember.m_byStat = 1;
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wDualIndx].m_tVmpMember.m_wEpID = ptNodeTmp->m_wEpID;
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wDualIndx].m_tVmpMember.m_wScreenIndx = ptNodeTmp->GetSpeaker();
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wDualIndx].m_tVmpMember.m_wStaticPayload = ptNodeTmp->m_tDualVidSndFormat.m_wStaticPayload;
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wDualIndx].m_tVmpMember.m_wDynamicPayload = ptNodeTmp->m_tDualVidSndFormat.m_wDynamicPayload;
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wDualIndx].m_tVmpMember.m_tEncrypt = tEncrypt;
		}
		else
		{
			ptVmpRes->m_atMember[ptVmpRes->m_tVmpStyle.m_wDualIndx].Clear();
		}
	}

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::AdjustSpeakerFollow. ConfID:%d, SpeakerIndx:%d, DualIndx:%d\n", 
			Inst()->GetInsID(), ptVmpRes->m_tVmpStyle.m_wSpeakerIndx, ptVmpRes->m_tVmpStyle.m_wDualIndx));

	return ;
}

void CUmsVmp::AdjustBrdVmpMember( TBrdVmpRes* ptVmpRes)
{
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdVmpMember. ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_tEqpInfo.m_byEqpID));

	//���Vip
	ptVmpRes->m_wCurVipNum = 0;

	CalcBrdVmpVipNum(ptVmpRes);

	TBrdVmpMember* ptMember = NULL;
	TVmpMemberPool tVmpMemberPool;  // �洢�Ѿ�ռ����vip��member

	TCallNode* ptNodeTmp = NULL;

	BOOL32	bAdjRes = TRUE;

	TCallVidFormat tVidFmt;
	EmGetVidRes emRes;
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex ++ )
	{// 
		ptMember = &ptVmpRes->m_atMember[wIndex];
		if ( !TP_VALID_HANDLE(ptMember->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		ptMember->m_emRes = CTpTypeAdpt::GetVmpMemberResByChnlIndx(ptVmpRes->m_tVmpStyle.m_emVmpStyle, wIndex);

		// ���vip�����Ϣ
		ptMember->ClearVip();
		ptMember->ClearDs();
		ptMember->ClearSmallVid();
		ptMember->ClearAdjustRes();

		ptNodeTmp = Inst()->m_pcNodeMgr->GetNode(ptMember->m_tVmpMember.m_wEpID);
		if ( NULL == ptNodeTmp || !ptNodeTmp->IsChanOn() || !ptNodeTmp->IsVidSndValid() )
		{
			continue;
		}

		if ( !ptVmpRes->m_bNeedAdjVip )
		{
			ptMember->SetVip();
			ptMember->SetDs();
		}
		else
		{
			if ( wIndex == 0 )
			{//0ͨ��������� Ĭ��VIP��ֱ�ӽ��ϳɣ��Ҳ�ռ��VIP��Դ
				ptMember->SetVip();
				ptMember->SetDs();
			}
			else
			{
				AdjustVipForMember(ptVmpRes, ptMember, &tVmpMemberPool);
			}
		}
	}

	BOOL32 bAdjustRet;
	for ( wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex ++ )
	{
		ptMember = &ptVmpRes->m_atMember[wIndex];
		
		if ( !TP_VALID_HANDLE(ptMember->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		ptMember->ClearGetVid(); // ��������������Ҳ��գ���Ӱ���ͷţ���Ϊǰ���Ѿ�����

		if (ptMember->m_tVmpMember.IsDual())
		{
			continue;
		}

		// �������ݶԱ�
		bAdjustRet = AdjustMemberResByOld(ptMember);

		if (!ptMember->IsVip() && ptMember->IsAdjustRes() && bAdjustRet && emTPVResEnd != ptMember->m_emRes)
		{// ���ֱ��ʽ��ϳ�
			Inst()->GetNodeMgr()->AdjustNodeRes( ptMember->m_tVmpMember.m_wEpID, 
						ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_emRes);
		}
	}

	//�ͷű������ݣ���������AdjustMemberResByOld�Ĵ��������������Ѿ�ֻʣ����Ҫ�ͷŵ���
	ReleaseBrdVmpParam(&m_tBrdVmpOld);
	//�����������
	BackupBrdVmpParam(NULL);

	// ѭ��һ�������������Ҫ���������Ĳŵ���
	for ( wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex ++ )
	{
		ptMember = &ptVmpRes->m_atMember[wIndex];		
		if ( !TP_VALID_HANDLE(ptMember->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		if (ptMember->m_tVmpMember.IsDual())
		{// ˫������������
			MdlLowHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdVmpMember. This Chan is Dual. Index:%d, EpId:%d, Vip:%d, Ds:%d.\n", wIndex, 
				ptMember->m_tVmpMember.m_wEpID, ptMember->IsVip(), ptMember->IsDs()));
			continue;
		}

		if (!ptMember->IsDs())
		{// ������������ͨ����Ҳ����������
			MdlLowHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdVmpMember. This Chan is no Ds. Index:%d, EpId:%d, Screen:%d, Stat:%d.\n", wIndex, 
				ptMember->m_tVmpMember.m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_tVmpMember.m_byStat));
			continue;
		}

		if (ptMember->IsVidGet())
		{// �Ѿ����ȹ������ģ����ظ�����
			MdlLowHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdVmpMember. This Chan is Get Vid. Index:%d, EpId:%d, Screen:%d.\n", wIndex, 
				ptMember->m_tVmpMember.m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx));
			continue;
		}

		ptNodeTmp = Inst()->m_pcNodeMgr->GetNode(ptMember->m_tVmpMember.m_wEpID);
		if ( NULL == ptNodeTmp || !ptNodeTmp->IsChanOn() || !ptNodeTmp->IsVidSndValid() )
		{
			continue;
		}

		// ������������
		emRes = CUmsConfInst::GetVidAudEx()->AssignByScreen(Inst(), ptNodeTmp->m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx, 
				em_GetVid_Vmp, tVidFmt, ptNodeTmp->IsSmallVidSnd(), ptMember->m_tGetAddr, ptMember->m_wGetIndex);
		if ( em_GetVid_Success != emRes )
		{
			// ��ʾ���棬��������ʧ�ܣ�����ϳ�ͨ��ʧ��
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_VMP_GetVidFail, Inst()->chairID(), (u32)ptMember->m_tVmpMember.m_wEpID,
					(u32)ptVmpRes->m_tEqpInfo.m_byEqpID);

			if (ptMember->IsAdjustRes() && emTPVResEnd != ptMember->m_emRes)
			{
				//������ʧ���ˣ��ָ��ն˷ֱ���
				Inst()->GetNodeMgr()->AdjustNodeRes( ptMember->m_tVmpMember.m_wEpID, 
						ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_emRes, TRUE);
				ptMember->m_emRes = emTPVResEnd;
			}
			continue;
		}
	}	

	return ;
}

BOOL32 CUmsVmp::AdjustMemberResByOld(TBrdVmpMember* ptMember)
{
	if ( m_tBrdVmpOld.m_wConfID != Inst()->GetInsID() )
	{
		return TRUE;
	}

	BOOL32 bRet = TRUE;
	u8	byAdjustPath = 0;
	u16 byGetPath = 0;

	TBrdVmpMember* ptMemberOld = NULL;
	for (u16 wIndex = 0; wIndex < m_tBrdVmpOld.m_wMemberNum; wIndex ++ )
	{
		ptMemberOld = &m_tBrdVmpOld.m_atMember[wIndex];
		
		if ( !TP_VALID_HANDLE(ptMemberOld->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		if ( ptMemberOld->m_tVmpMember.m_wEpID != ptMember->m_tVmpMember.m_wEpID
			|| ptMemberOld->m_tVmpMember.m_wScreenIndx != ptMember->m_tVmpMember.m_wScreenIndx )
		{
			continue;
		}

		// ������Ҳ������������

		// �������Ѿ������������������ݿɽ���������ֱ�ӿ������������У������ظ�����
		if (ptMemberOld->IsVidGet() && ptMember->IsDs())
		{
			ptMember->m_wGetIndex = ptMemberOld->m_wGetIndex;
			ptMember->m_tGetAddr = ptMemberOld->m_tGetAddr;

			ptMemberOld->ClearGetVid(); // ֱ����������ݵ�����������Ϣ

			byGetPath = 1;
		}
		else if (ptMemberOld->IsVidGet())
		{// �����ݵ��������������ݲ���Ҫ�������ͷ�֮ǰ���ȵ�����

			CUmsConfInst::GetVidAudEx()->Release(Inst(), ptMemberOld->m_wGetIndex);

			ptMemberOld->ClearGetVid();

			byGetPath = 2;
		}
		else
		{// ������û�е��������������ݿ�����Ҫ�������������洦��
			byGetPath = 3;
		}

		if (ptMember->IsAdjustRes() && emTPVResEnd != ptMember->m_emRes)
		{// ��������Ҫ��

			if (!ptMemberOld->IsAdjustRes())
			{// ����ϵ�û�н�����ֱ�ӽ�
				Inst()->GetNodeMgr()->AdjustNodeRes( ptMember->m_tVmpMember.m_wEpID, 
					ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_emRes);

				byAdjustPath = 1;
				bRet = FALSE;
			}
			else if (ptMemberOld->m_emRes != ptMember->m_emRes)
			{// ����ϵĽ��ˣ����ǽ��ķֱ��ʲ�һ�£�����µģ� ɾ���ϵģ�
				Inst()->GetNodeMgr()->AdjustNodeRes( ptMember->m_tVmpMember.m_wEpID, 
					ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_emRes);

				Inst()->GetNodeMgr()->AdjustNodeRes( ptMemberOld->m_tVmpMember.m_wEpID, 
				ptMemberOld->m_tVmpMember.m_wScreenIndx, ptMemberOld->m_emRes, TRUE);
				
				byAdjustPath = 2;
				bRet = FALSE;
			}
			else
			{// ���Ͻ���һ�£��������
				byAdjustPath = 3;
				bRet = FALSE;
			}
		}
		else if ( ptMemberOld->IsAdjustRes() && emTPVResEnd != ptMemberOld->m_emRes)
		{// �����ݲ���Ҫ������������ݽ��˷ֱ��ʣ���ָ�
			Inst()->GetNodeMgr()->AdjustNodeRes( ptMemberOld->m_tVmpMember.m_wEpID, 
				ptMemberOld->m_tVmpMember.m_wScreenIndx, ptMemberOld->m_emRes, TRUE);
			byAdjustPath = 4;
			bRet = FALSE;
		}
		else
		{// �������ݶ�����Ҫ��
			byAdjustPath = 5;
			bRet = FALSE;
		}

		//�ͷ�������ʱ���ڴ���
		ptMemberOld->m_tVmpMember.m_wEpID = TP_INVALID_INDEX;

		break;
	}

	MdlLowHint(Ums_Mdl_Call, ("CUmsVmp::AdjustMemberResByOld. ConfID:%d, EpID:%d, ScrIndx:%d, Ret:%d, AdjustPath:%d, GetPath:%d\n", 
					Inst()->GetInsID(), ptMember->m_tVmpMember.m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx, bRet, byAdjustPath, byGetPath));

	//��������û�ҵ� �������� ��Ҫ����
	return bRet;
}

void CUmsVmp::InitBrdVmpCfg(TSaveVmpCfg* ptCfg)
{
	if ( NULL == ptCfg )
	{
		return ;
	}

	memcpy(&m_tVmpCfg, ptCfg, sizeof(m_tVmpCfg));
	return;
}

void CUmsVmp::OnChanConnect( TCallNode* ptNode )
{
	//�᳡���� �������и��᳡
	if ( !ptNode->Is323Ep() && !ptNode->IsB3CNS() )
	{
		NotifyAllBrdVmpToCNC(ptNode->m_wEpID);
	}

	if ( Inst()->IsChairConf() && ptNode->IsUms())
	{//ums ���� ֪ͨ�䷢���˺ϳ� �� �㲥�ϳ�״̬
		TVmpCasecadeNtfy tNtfy;
		tNtfy.m_bBrdVmp = m_ptConfBrdVmp == NULL ? FALSE : TRUE;
		tNtfy.m_emSpeakerVmpType = m_emVmpType;
		strncpy(tNtfy.m_szBrdVmpAlias, m_szBrdVmpAlias, TP_MAXLEN_EQP_ALIAS);
		tNtfy.m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';
		
		TUmsHandle tHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tHandle, ev_UMS_UMS_VmpCasecade_Ntfy, &tNtfy, sizeof(tNtfy));
	}

	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}

		if( m_atBrdVmp[wIndex].m_bVmpAuto )
		{//�Զ�����ϳ� ��Ҫ����ˢ�³�Ա
			
#ifdef _USE_XMPUEQP_
			UpdateBrdXmpuVmpParam(&m_atBrdVmp[wIndex]);
#else
			UpdateBrdVmpParam(&m_atBrdVmp[wIndex]);
#endif
			
			Inst()->GetVmp()->NotifyBrdVmpToCNC(&m_atBrdVmp[wIndex], tp_OprType_Update);
			NotifyBrdVmpToUMC(&m_atBrdVmp[wIndex], tp_OprType_Update);
		}
		else if (m_atBrdVmp[wIndex].IsEpInVmp(ptNode->m_wEpID))
		{
			//����һ��
			BackupBrdVmpParam(&m_atBrdVmp[wIndex]);
#ifdef _USE_XMPUEQP_
				AdjustBrdXmpuVmpMember(&m_atBrdVmp[wIndex]);
#else
			//���ߣ�����Vip�Լ���������
			AdjustBrdVmpMember(&m_atBrdVmp[wIndex]);
#endif
			CNetPortMgr::CreateAllMemberToBrdVmp(Inst(), &m_atBrdVmp[wIndex]);
		}
		else
		{
			continue;
		}
	}
}

void CUmsVmp::OnHungUp(TCallNode* ptNode, EmCnsCallReason emReason /* = EmCnsCallReason_success */)
{
	if ( Inst()->m_bIsQuiting )
	{
		return ;
	}

	ptNode->m_bChannelOpen = FALSE;
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}

		if ( !m_atBrdVmp[wIndex].IsEpInVmp(ptNode->m_wEpID) )
		{
			continue;
		}

		if( m_atBrdVmp[wIndex].m_bVmpAuto || emReason == EmCnsCallReason_hungup || emReason == EmCnsCallReason_peerhungup)
		{//�Զ�����ϳ� ��Ҫ����ˢ�³�Ա

			if (!m_atBrdVmp[wIndex].m_bVmpAuto)
			{
				m_atBrdVmp[wIndex].m_tVmpStyle.DelChnl(ptNode->m_wEpID); // �ӷ����ɾ���˳�Ա�����ָ�����һ��
			}

#ifdef _USE_XMPUEQP_
			UpdateBrdXmpuVmpParam(&m_atBrdVmp[wIndex]);
#else
			UpdateBrdVmpParam(&m_atBrdVmp[wIndex]);
#endif

			Inst()->GetVmp()->NotifyBrdVmpToCNC(&m_atBrdVmp[wIndex], tp_OprType_Update);
			NotifyBrdVmpToUMC(&m_atBrdVmp[wIndex], tp_OprType_Update);
		}
		else
		{//�ֶ����� �����������Լ�VIP
			//����һ��
			BackupBrdVmpParam(&m_atBrdVmp[wIndex]);
			
#ifdef _USE_XMPUEQP_
			//���ߣ�����Vip�Լ���������
			AdjustBrdXmpuVmpMember(&m_atBrdVmp[wIndex]);
#else
			//���ߣ�����Vip�Լ���������
			AdjustBrdVmpMember(&m_atBrdVmp[wIndex]);
#endif
			CNetPortMgr::CreateAllMemberToBrdVmp(Inst(), &m_atBrdVmp[wIndex]);
		}
	}
	ptNode->m_bChannelOpen = TRUE;
}

void CUmsVmp::OnStopConf()
{
	TVmpParam tVmpParam;
	TXmpuVmpParam tXmpuVmpParam;
	TXmpuEqpRes tRes;
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}
		
		ReleaseBrdVmpParam(&m_atBrdVmp[wIndex]);
		m_atBrdVmp[wIndex].ResetUIInfo();

#ifdef _USE_XMPUEQP_
		TXmpuEqpRes tRes;
		tRes.m_dwEqpID = m_atBrdVmp[wIndex].m_tEqpRes.m_byEqpID;
		tXmpuVmpParam.m_ptEqp = &tRes;
		tXmpuVmpParam.m_emEqpType = em_XmpuVmp_Eqp;
		if ( !ReleaseXmpuEqp(&tXmpuVmpParam) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::OnStopConf. ReleaseEqp Failed! ConfID:%d, EqpID:%d\n", 
				Inst()->GetInsID(), m_atBrdVmp[wIndex].m_tEqpRes.m_byEqpID));
		}
		m_atBrdVmp[wIndex].m_bOnLine = FALSE;
		// �ͷ�vmp ֪ͨmpu2-tpģ��ˢ�ºϳ���
		CUmsConfInst::m_tXmpuVmpManger.ReleaseVmp(tRes.m_dwEqpID);
		CEqpService::Instance().FlushXmpuMpu2();

		if (m_atBrdVmp[wIndex].m_cToVmpDsInfo.GetElementNum() != 0)
		{
			CNetPortMgr::FreeMediaTrans(Inst(), m_atBrdVmp[wIndex].m_cToVmpDsInfo);
		}
#else
		tVmpParam.m_ptEqpRes = &m_atBrdVmp[wIndex].m_tEqpRes;
		if ( !ReleaseEqpEx(&tVmpParam) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::OnStopConf. ReleaseEqp Failed! ConfID:%d, EqpID:%d\n", 
				Inst()->GetInsID(), m_atBrdVmp[wIndex].m_tEqpRes.m_byEqpID));
		}
#endif
		
		m_atBrdVmp[wIndex].m_wConfID = TP_INVALID_INDEX;
		m_atBrdVmp[wIndex].m_emStat = EmBrdVmpStat_Idle;
		NotifyBrdVmpToAllConf(&m_atBrdVmp[wIndex], tp_OprType_Update);
	}

	StopSpeakerVmp();

	InstClear();

	return ;
}

void CUmsVmp::ChangSpeaker()
{
	if ( Inst()->m_bIsQuiting )
	{
		return ;
	}

	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}

		if ( m_atBrdVmp[wIndex].m_bVmpAuto )
		{
#ifdef _USE_XMPUEQP_
			UpdateBrdXmpuVmpParam(&m_atBrdVmp[wIndex]);
#else
			UpdateBrdVmpParam(&m_atBrdVmp[wIndex]);
#endif	
		}
		else
		{
			//����һ��
			BackupBrdVmpParam(&m_atBrdVmp[wIndex]);
			
			//���������˸���
			AdjustSpeakerFollow(&m_atBrdVmp[wIndex]);
			
#ifdef _USE_XMPUEQP_
			//�з����ˣ�����Vip�Լ���������
			AdjustBrdXmpuVmpMember(&m_atBrdVmp[wIndex]);
#else
			//�з����ˣ�����Vip�Լ���������
			AdjustBrdVmpMember(&m_atBrdVmp[wIndex]);
#endif
			CNetPortMgr::CreateAllMemberToBrdVmp(Inst(), &m_atBrdVmp[wIndex]);
		}

		Inst()->GetVmp()->NotifyBrdVmpToCNC(&m_atBrdVmp[wIndex], tp_OprType_Update);
		NotifyBrdVmpToUMC(&m_atBrdVmp[wIndex], tp_OprType_Update);
	}
}


void CUmsVmp::AdjustDual()
{
	if ( Inst()->m_bIsQuiting )
	{
		return ;
	}
	
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}
		
		if ( m_atBrdVmp[wIndex].m_bVmpAuto )
		{// �Զ�û��˫������
			continue;
		}
		else
		{
			if ( !TP_VALID_HANDLE(m_atBrdVmp[wIndex].m_tVmpStyle.m_wDualIndx) )
			{
				continue;
			}
#ifdef _USE_XMPUEQP_
			UpdateBrdXmpuVmpParam(&m_atBrdVmp[wIndex]);
#else
			UpdateBrdVmpParam(&m_atBrdVmp[wIndex]);
#endif

			Inst()->GetVmp()->NotifyBrdVmpToCNC(&m_atBrdVmp[wIndex], tp_OprType_Update);
			NotifyBrdVmpToUMC(&m_atBrdVmp[wIndex], tp_OprType_Update);
		}
	}

	return;
}


EMVmpStyle CUmsVmp::FindStyleByMTNum( u16 wMtNum )
{
	EMVmpStyle emStyleTmp = tp_VmpStyle_ONE;
	switch(wMtNum)
	{
	case 0:
		emStyleTmp = tp_VmpStyle_DYNAMIC;
		break;
	case 1:
		emStyleTmp = tp_VmpStyle_ONE;
		break;
	case 2:
		emStyleTmp = tp_VmpStyle_VTWO;
		break;
	// 	case 3:
	// 		emStyleTmp = tp_VmpStyle_HTWO;
	// 		break;
	case 3:
		emStyleTmp = tp_VmpStyle_THREE;
		break;
	case 4:
		emStyleTmp = tp_VmpStyle_FOUR;
		break;
		// 	case 6:
		// 		emStyleTmp = tp_VmpStyle_SPECFOUR;
		// 		break;
	case 5:
	case 6:
		emStyleTmp = tp_VmpStyle_SIX;
		break;
	case 7:
		emStyleTmp = tp_VmpStyle_SEVEN;
		break;
	case 8:
		emStyleTmp = tp_VmpStyle_EIGHT;
		break;
	case 9:
		emStyleTmp = tp_VmpStyle_NINE;
		break;
	case 10:
		emStyleTmp = tp_VmpStyle_TEN_M;
		break;
	case 11:
	case 12:
	case 13:
		emStyleTmp = tp_VmpStyle_THIRTEEN_M;
		break;
	case 14:
	case 15:
	case 16:
		emStyleTmp = tp_VmpStyle_SIXTEEN;
		break;
	case 17:
	case 18:
	case 19:
	case 20:
		emStyleTmp = tp_VmpStyle_TWENTY;
		break;
	default:
		emStyleTmp = tp_VmpStyle_TWENTYFIVE;
		break;
	}

	return emStyleTmp;
}

#ifdef _USE_XMPUEQP_
void CUmsVmp::XmpuBasCB(u32 dwType, CScreenBasRes* pBasRes, void *pData)
{
	CUmsConfInst *pInst = Inst();
	BOOL32 bError = FALSE;
	if ( pInst->GetSpeaker().m_pcSingleBas != pBasRes )
	{
		return;
	}
	
	if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		TXmpuStartBasNty tStartBastNty;
		memcpy(&tStartBastNty, pData, sizeof(tStartBastNty));  
		if (!tStartBastNty.m_bSuccess)
		{
			bError = TRUE;
			MdlError(Ums_Mdl_Call, ("CUmsVmp::XmpuBasCB. Startbas Fail! StopSpeakerVmp! ConfID:%d, EqpID:%d, bSuccess:%d\n", 
				pInst->GetInsID(), pBasRes->GetBasEqpId(), tStartBastNty.m_bSuccess));
		}else
		{
			pBasRes->m_tXmpuBas.m_emStat = EmXmpuResStatInfo_Running;
			pInst->GetBas()->SetXmpuVidBasAssignAddr(&pBasRes->m_tXmpuBas, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);
		    CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, &pBasRes->m_tXmpuBas);
			pInst->TryAdjustVirSingleBas();
		}
		
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		// CNetPortMgr::CreateVirSpeakerToBas(pInst);

	} else if (dwType == evXmpu_AskBasKey_Req)
	{   
		u16 wAskEp = 0;
		if ( Inst()->IsChairConf() )
		{
			if (Inst()->GetVmp()->IsChairInVmp())
			{
				wAskEp = Inst()->chairID();
				if (Inst()->GetRollCallMgr()->IsRollCallModle())
				{
                    wAskEp = Inst()->GetRollCallMgr()->GetRollCallerEpId();
				}
				
			}else 
			{
                wAskEp = Inst()->curSpeakerID();
			}
			
			AskFrameToSpeakerVmp(wAskEp);
		}
		else
		{
			Inst()->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeySpeakerVmp);
		}
		
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
		bError = TRUE;
		MdlError(Ums_Mdl_Call, ("CUmsVmp::XmpuBasCB. BasDisConnect! StopSpeakerVmp! ConfID:%d, EqpID:%d\n", 
				pInst->GetInsID(), pBasRes->GetBasEqpId()));
	}

	if (bError)
	{
        StopSpeakerVmp();
	}
}
	
#else

void CUmsVmp::BasCB( CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes )
{
	if ( Inst()->GetSpeaker().m_pcSingleBas != ptBasRes )
	{
		return;
	}

	u16 wAskEp = 0;

	MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::BasCB. ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, CBType:%d\n", 
		Inst()->GetInsID(), ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, emType));
	
	if ( emType == CScreenBasRes::VidBasCB_DisConnect
		|| emType == CScreenBasRes::VidBasCB_NAck )
	{
		StopSpeakerVmp();//�ϼ�ֹͣ�ϳɲ��н�������ϯ  �¼���ֱ���н�������ϯ
	}
	else if ( emType == CScreenBasRes::VidBasCB_AskKey )
	{
		if ( Inst()->IsChairConf() )
		{
			if (Inst()->GetVmp()->IsChairInVmp())
			{
				wAskEp = Inst()->chairID();
				if (Inst()->GetRollCallMgr()->IsRollCallModle())
				{
                    wAskEp = Inst()->GetRollCallMgr()->GetRollCallerEpId();
				}

			}else 
			{
                wAskEp = Inst()->curSpeakerID();
			}

			AskFrameToSpeakerVmp(wAskEp);
		}
		else
		{
			Inst()->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeySpeakerVmp);
		}
	}
}
#endif

void CUmsVmp::VmpCB( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wMemberIndx )
{
	if ( emRes == em_Service_No_Reg
		|| emRes == em_Start_Failed
		|| emRes == em_Stop_Failed
		|| emRes == em_Mdy_Failed
		|| emRes == em_Invalid_Param
		|| emRes == em_Set_Param_Failed)
	{
		MdlHint(Ums_Mdl_Call, ("CUmsVmp::VmpCB. ConfID:%d, ServiceID:%d, CBType:%d, emRes:%d\n", 
									Inst()->GetInsID(), pcService->GetServiceID(), emOpType, emRes));

		Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_SpeakerVmpError, Inst()->chairID());

		StopSpeakerVmp();
	}
	else if ( emRes == em_Res_Success )
	{
		if ( emOpType == em_Frame_Service )
		{
			Inst()->AskKeyByEpID(m_wVmpEpID, EmAskKeySpeaker, 0, 0, FALSE);
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("CUmsVmp::VmpCB. ConfID:%d, ServiceID:%d, CBType:%d, emRes:%d\n", 
									Inst()->GetInsID(), pcService->GetServiceID(), emOpType, emRes));
		}
	}
	return ;
}

void CUmsVmp::StartSpeakerVmp()
{
	if ( !Inst()->IsChairConf() )
	{//ֻ���ϼ��ϳ�
		return ;
	}

	m_b108060 = FALSE;
	for ( u16 wIndex = 0; wIndex < Inst()->m_tConfBaseInfo.m_wMainNum; wIndex ++ )
	{
		if ( Inst()->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex].m_emRes == emTPVHD1080p1920x1080
			&& Inst()->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex].m_wFrameRate == VID_FRAME_RATE_60 )
		{
			m_b108060 = TRUE;
			break;
		}
	}

	//ȡ��������������
	m_bSpeakerVmpCfg = CUmsConfigEx::GetInstance()->GetVmpUsed();
	if ( (!m_bSpeakerVmpCfg))
	{
		return ;
 	}

	if (NULL == Inst()->GetSpeaker().m_pcSingleVmp)
	{
		Inst()->GetSpeaker().m_pcSingleVmp = Inst()->GetVmpServiceHandle()->Assign(VirSingleVmpCB, Inst());	
		if (NULL == Inst()->GetSpeaker().m_pcSingleVmp)
		{
			return;
		}
		
		m_pcSpeakerVmp = Inst()->GetSpeaker().m_pcSingleVmp;
	}
	m_pcSpeakerVmp = Inst()->GetSpeaker().m_pcSingleVmp;

	if(!Inst()->TryAssignVirSingleBas())
	{
		if (NULL != m_pcSpeakerVmp)
		{
			Inst()->GetVmpServiceHandle()->Release(m_pcSpeakerVmp);
		}
		Inst()->GetSpeaker().m_pcSingleVmp = NULL;
		m_pcSpeakerVmp = NULL;
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::StartSpeakerVmp. ConfID:%d, speakerVmp:%d, speakerBas:%d\n", 
									Inst()->GetInsID(), m_pcSpeakerVmp, Inst()->GetSpeaker().m_pcSingleBas));

	AdjustSpeakerVmp();

	return ;
}

void CUmsVmp::AdjustSpeakerVmp(BOOL32 bFromDiscuss /* = FALSE */, BOOL32 bChangeSpeaker /* = TRUE */)
{

	if (bChangeSpeaker)
	{
		ChangSpeaker();
	}

	if (NULL == m_pcSpeakerVmp || !m_bSpeakerVmpCfg || !Inst()->IsChairConf())
	{
		return ;
	}
	
	if (Inst()->GetUmsDiscuss()->IsDiscussModle())
	{// ����ģʽ�£��޷����˺ϳ�
		return;
	} 

	TCallNode* ptVmpNode = GetVmpEp();
	TCapNode* ptVmpFar = Inst()->GetNodeMgr()->GetForeFatherNode(ptVmpNode);

	TCapNode* ptSpeakerNode = Inst()->GetNodeMgr()->GetForeFatherNode(Inst()->curSpeakerID());

	if (NULL == ptSpeakerNode)
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::AdjustSpeakerVmp speaker is NLLL. ConfID:%d.\n", Inst()->GetInsID()));
		return;
	}
	
	if( NULL != ptVmpFar)
	{
		
		if (TRUE)
		{
			TVmpStyleInfo	tStyleInfo;
			TVmpEncParam	tEncParam;
			
			tStyleInfo.m_emVmpStyle = em_ums_vmp_four_pic;
			tStyleInfo.m_emShowMode = ums_vmp_lastframe_mode;
			tStyleInfo.m_byMemberNum = TP_MAX_STREAMNUM+1;
			
			TCallVidFormat tVidFormat;

			if (em_Speaker_In_Vmp == m_emVmpType)
			{// ��������vmp,vmp�������˷��͸�ʽ��
				tVidFormat = ptSpeakerNode->m_tVidSndFormat;
			}
			else if (em_Chair_In_Vmp == m_emVmpType)
			{// ��ϯ��vmp,vmp�������˽��ո�ʽ��
				tVidFormat = ptSpeakerNode->m_tVidRcvFormat;
			}
			else
			{
				MdlError(Ums_Mdl_Call, ("CUmsVmp::AdjustSpeakerVmp invaild type. ConfID:%d, type:%d.\n", Inst()->GetInsID(), m_emVmpType));
				return;
			}

			tStyleInfo.m_atMemberInfo[0].m_bMerged = FALSE;
			tStyleInfo.m_atMemberInfo[0].m_dwHandle = ptVmpNode->m_wEpID;
			tStyleInfo.m_atDoublePayload[0].m_byActivePayload = tVidFormat.m_wDynamicPayload;
			tStyleInfo.m_atDoublePayload[0].m_byRealPayload = tVidFormat.m_wStaticPayload;
			
			for (u8 wIndx = 0; wIndx < TP_MAX_STREAMNUM; wIndx ++ )
			{
				tStyleInfo.m_atMemberInfo[wIndx+1].m_bMerged = TRUE;
				tStyleInfo.m_atMemberInfo[wIndx+1].m_dwHandle = ptVmpNode->m_wEpID;
				tStyleInfo.m_atDoublePayload[wIndx+1].m_byActivePayload = tVidFormat.m_wDynamicPayload;
				tStyleInfo.m_atDoublePayload[wIndx+1].m_byRealPayload = tVidFormat.m_wStaticPayload;
			}
			
			tEncParam.m_byEncType = CTpTypeAdpt::GetVidPayloadValue(tVidFormat.m_tFormat.m_emFormat);
			tEncParam.m_byFrameRate = tVidFormat.m_tFormat.m_wFrameRate;
			if ( tVidFormat.m_tFormat.m_emQualityLvl == emTPH264HP )
			{
				tEncParam.m_byProfileType = 1;
			}
			else if( tVidFormat.m_tFormat.m_emQualityLvl == emTPH264BP )
			{
				tEncParam.m_byProfileType = 0;
			}
			tEncParam.m_wBitRate = tVidFormat.m_tFormat.m_wBitrate;
			CTpTypeAdpt::GetWHByVidResolution(tVidFormat.m_tFormat.m_emRes,
				tEncParam.m_wVideoWidth, tEncParam.m_wVideoHeight);
			
			
			TVmpUseParam tVmpParam;
			TTPEncrypt tEncrypt = Inst()->GetConfEncryptInfo();
			memcpy(&tVmpParam.m_tEncrypt, &tEncrypt, sizeof(TTPEncrypt));
			memcpy(&tVmpParam.m_tEncParam, &tEncParam, sizeof(tEncParam));
			memcpy(&tVmpParam.m_tStyleInfo, &tStyleInfo, sizeof(tStyleInfo));
			if ( !Inst()->GetSpeaker().m_bSingleVmpStart)
			{
				
				Inst()->GetVmpServiceHandle()->Start(m_pcSpeakerVmp, &tVmpParam);
				Inst()->GetSpeaker().m_bSingleVmpStart = TRUE;
			}
			else
			{
				Inst()->GetVmpServiceHandle()->ChangeMode(m_pcSpeakerVmp, &tVmpParam);
			}
		}
		
		if( Inst()->IsPriNeedBas() )
		{
			//��������
			Inst()->GetBas()->AdjustScreenBas(Inst()->GetSpeaker().m_pcSingleBas, ptVmpNode->m_wEpID, ptVmpNode->GetSpeaker());
		}

		m_wVmpEpID = ptVmpNode->m_wEpID;
	}
	else
	{
		m_wVmpEpID = TP_INVALID_INDEX;
	}

	//�������� �᳡���ϳ�
	CNetPortMgr::CreatVidToSingleVmpTp(Inst());

	// ֪ͨ�¼�Ums
	NotifySpeakerVmpToDownUms();

	return ;
}

void CUmsVmp::ReleaseBrdVmpParam( TBrdVmpRes* ptVmpRes )
{
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::ReleaseBrdVmpParam. ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_tEqpInfo.m_byEqpID));
	for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++)
	{

		if ( !TP_VALID_HANDLE(ptVmpRes->m_atMember[wIndex].m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		//�ͷ���������
		if ( ptVmpRes->m_atMember[wIndex].IsVidGet() )
		{
			CUmsConfInst::GetVidAudEx()->Release(Inst(), ptVmpRes->m_atMember[wIndex].m_wGetIndex);
		}
		
		if( ptVmpRes->m_atMember[wIndex].IsAdjustRes() && emTPVResEnd != ptVmpRes->m_atMember[wIndex].m_emRes)
		{
			//�ָ��ն˷ֱ���
			Inst()->GetNodeMgr()->AdjustNodeRes( ptVmpRes->m_atMember[wIndex].m_tVmpMember.m_wEpID, 
						ptVmpRes->m_atMember[wIndex].m_tVmpMember.m_wScreenIndx, ptVmpRes->m_atMember[wIndex].m_emRes, TRUE);
		}
	}

	if( ptVmpRes->m_tDsToVmp.GetElementNum() != 0 )
	{
		//�������
		CNetPortMgr::FreeMediaTrans(Inst(), ptVmpRes->m_tDsToVmp);
	}

	ptVmpRes->ReSetMember();
}

void CUmsVmp::OnUmcRerveseBrdVmpReq( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	TRersvesEqpReq tReq;
	TP_SAFE_CAST(tReq, ptMsg->GetBody() + sizeof(TLogUser));

#ifdef _USE_XMPUEQP_
	EmRervesVmpRet emRet = RerveseXmpuVmp(tReq);
#else
	EmRervesVmpRet emRet = RerveseBrdVmp(tReq);
#endif
	if ( EmRervesVmpRet_Success == emRet )
	{
		NotifyBrdVmpToAllConf(tReq.m_tEqp.m_byEqpID, tp_OprType_Update);
	}

	TRersvesEqpRsp tRsp;
	tRsp.m_wConfID = Inst()->GetInsID();
	tRsp.m_emRet = emRet;
	memcpy(&tRsp.m_tRersvesReq, &tReq, sizeof(tReq));
	
	//�ظ�UMC
	Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_RervesBrdVmp_Ind, &tRsp, sizeof(tRsp), &tUsr);

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnUmcRerveseBrdVmpReq. ConfID:%d, EqpID:%d, Rersve:%d, Ret:%d\n", 
		Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID, tReq.m_bRersves, emRet));

	return ;
}

void CUmsVmp::OnCncRerveseBrdVmpReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TRersvesEqpReq tReq;
	TP_SAFE_CAST(tReq, ptMsg->GetBody() + sizeof(TUmsHandle));

	if ( tHandle.GetEpID() != Inst()->chairID() )
	{//��ϯ����
		return ;
	}

#ifdef _USE_XMPUEQP_
	EmRervesVmpRet emRet = RerveseXmpuVmp(tReq);
#else
	EmRervesVmpRet emRet = RerveseBrdVmp(tReq);
#endif
	if ( EmRervesVmpRet_Success == emRet )
	{
		NotifyBrdVmpToAllConf(tReq.m_tEqp.m_byEqpID, tp_OprType_Update);
	}

	TRersvesEqpRsp tRsp;
	tRsp.m_emRet = emRet;
	memcpy(&tRsp.m_tRersvesReq, &tReq, sizeof(tReq));
	
	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_RervesBrdVmp_Ind, &tRsp, sizeof(tRsp));
			
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnCncRerveseBrdVmpReq. ConfID:%d, EqpID:%d, Rersve:%d, Ret:%d\n", 
		Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID, tReq.m_bRersves, emRet));
	
	return ;
}

void CUmsVmp::OnUmcSetBrdVmpReq( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	TSetVmpInfoReq tReq;
	TP_SAFE_CAST(tReq, ptMsg->GetBody() + sizeof(TLogUser));
	
#ifdef _USE_XMPUEQP_
	EmBrdVmpRet emRet = SetBrdXmpuVmp(tReq);
#else
	EmBrdVmpRet emRet = SetBrdVmp(tReq);
#endif
	if ( EmBrdVmpRet_Succes == emRet )
	{
		NotifyBrdVmpToAllConf(tReq.m_tEqp.m_byEqpID, tp_OprType_Update);
	}

	TSetVmpInfoRsp tRsp;
	tRsp.m_wConfID = Inst()->GetInsID();
	tRsp.m_emRet = emRet;
	memcpy(&tRsp.m_tReq, &tReq, sizeof(tReq));
	
	//UMC ����Ind
	Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SetBrdVmp_Ind, &tRsp, sizeof(tRsp), &tUsr);
	
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnUmcSetBrdVmpReq. ConfID:%d, EqpID:%d, Ret:%d\n", Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID, emRet));
	
	return ;
}

void CUmsVmp::OnCncSetBrdVmpReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TSetVmpInfoReq tReq;
	TP_SAFE_CAST(tReq, ptMsg->GetBody() + sizeof(TUmsHandle));
	
	if ( tHandle.GetEpID() != Inst()->chairID() )
	{//��ϯ����
		return ;
	}

#ifdef _USE_XMPUEQP_
	EmBrdVmpRet emRet = SetBrdXmpuVmp(tReq);
#else
	EmBrdVmpRet emRet = SetBrdVmp(tReq);
#endif
	if ( EmBrdVmpRet_Succes == emRet )
	{
		NotifyBrdVmpToAllConf(tReq.m_tEqp.m_byEqpID, tp_OprType_Update);
	}

	TSetVmpInfoRsp tRsp;
	tRsp.m_emRet = emRet;
	memcpy(&tRsp.m_tReq, &tReq, sizeof(tReq));
		
	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SetBrdVmp_Ind, &tRsp, sizeof(tRsp));
	
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnCncSetBrdVmpReq. ConfID:%d, EqpID:%d, Ret:%d\n", Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID, emRet));
	
	return ;
}

void CUmsVmp::OnUmcBrdVmpReq( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	TBrdVmpReq tReq;
	TP_SAFE_CAST(tReq, ptMsg->GetBody() + sizeof(TLogUser));
	
	EmBrdVmpRet emRet = BrdVmp(tReq);
	if ( EmBrdVmpRet_Succes == emRet )
	{
		NotifyBrdVmpToAllConf(tReq.m_tEqp.m_byEqpID, tp_OprType_Update);
	}

	TBrdVmpRsp tRsp;
	tRsp.m_wConfID = Inst()->GetInsID();
	tRsp.m_emRet = emRet;
	memcpy(&tRsp.m_tReq, &tReq, sizeof(tReq));
	
	//UMC ����Ind
	Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_BrdVmp_Ind, &tRsp, sizeof(tRsp), &tUsr);

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnUmcBrdVmpReq. ConfID:%d, EqpID:%d, bBrd:%d, Ret:%d\n", 
		Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID, tReq.m_bBrd, emRet));
	
	return ;
}

void CUmsVmp::OnCncBrdVmpReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TBrdVmpReq tReq;
	TP_SAFE_CAST(tReq, ptMsg->GetBody() + sizeof(TUmsHandle));
	
	if ( tHandle.GetEpID() != Inst()->chairID() )
	{//��ϯ����
		return ;
	}
	
	EmBrdVmpRet emRet = BrdVmp(tReq);
	if ( EmBrdVmpRet_Succes == emRet )
	{
		NotifyBrdVmpToAllConf(tReq.m_tEqp.m_byEqpID, tp_OprType_Update);
	}

	TBrdVmpRsp tRsp;
	tRsp.m_emRet = emRet;
	memcpy(&tRsp.m_tReq, &tReq, sizeof(tReq));
		
	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_BrdVmp_Ind, &tRsp, sizeof(tRsp));
	
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnCncBrdVmpReq. ConfID:%d, EqpID:%d, bBrd:%d, Ret:%d\n", 
		Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID, tReq.m_bBrd, emRet));	
	return ;
}

void CUmsVmp::BackupBrdVmpParam( TBrdVmpRes* ptVmpRes )
{
	if( NULL == ptVmpRes )
	{
		m_tBrdVmpOld.Clear();
	}
	else
	{
		memcpy(&m_tBrdVmpOld, ptVmpRes, sizeof(TBrdVmpRes));
		m_tBrdVmpOld.m_tDsToVmp.Clear();
	}
}

TBrdVmpRes* CUmsVmp::SelViewVmp( u16 wEqpID, BrdVmpCB	pfCB, void* pParam )
{
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}

		if ( wEqpID != m_atBrdVmp[wIndex].m_tEqpInfo.m_byEqpID )
		{
			continue;
		}

		if ( m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Error
			|| m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Idle
			|| m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Invalid)
		{
			continue;
		}

		m_atBrdVmp[wIndex].m_pSelViewParam = pParam;
		m_atBrdVmp[wIndex].m_pfSelViewCB = pfCB;

		return &m_atBrdVmp[wIndex];
	}

	return NULL;
}

TBrdVmpRes* CUmsVmp::VmpToTvWall( u16 wEqpID, BrdVmpCB pfCB, void* pParam )
{
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}
		
		if ( wEqpID != m_atBrdVmp[wIndex].m_tEqpInfo.m_byEqpID )
		{
			continue;
		}
		
		if ( m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Error
			|| m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Idle
			|| m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Invalid)
		{
			continue;
		}
		
		m_atBrdVmp[wIndex].m_pTvWallParam = pParam;
		m_atBrdVmp[wIndex].m_pfTvWallCB = pfCB;
		
		return &m_atBrdVmp[wIndex];
	}
	
	return NULL;
}

TBrdVmpRes* CUmsVmp::GetVmpOutConf( u16 wEqpID, BrdVmpCB pfCB, void* pParam )
{
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}
		
		if ( wEqpID != m_atBrdVmp[wIndex].m_tEqpInfo.m_byEqpID )
		{
			continue;
		}
		
		if ( m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Error
			|| m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Idle
			|| m_atBrdVmp[wIndex].m_emStat == EmBrdVmpStat_Invalid)
		{
			continue;
		}
		
		m_atBrdVmp[wIndex].m_pGetVmpParam = pParam;
		m_atBrdVmp[wIndex].m_pfGetVmpCB = pfCB;
		
		return &m_atBrdVmp[wIndex];
	}
	
	return NULL;
};

BOOL32 CUmsVmp::AskFrameToBrdVmp( TBrdVmpRes* ptVmpRes, const TUmsVidFormat& tFormat, BOOL32 bIsFromVirSpeaker )
{
	if ( NULL == ptVmpRes )
	{
		return FALSE;
	}

	if ( ptVmpRes->m_emStat == EmBrdVmpStat_Error
		|| ptVmpRes->m_emStat == EmBrdVmpStat_Idle
		|| ptVmpRes->m_emStat == EmBrdVmpStat_Invalid)
	{
		return FALSE;
	}

	u16 wOutIndx = TP_INVALID_INDEX;
	if (bIsFromVirSpeaker)
	{
		wOutIndx = CTpTypeAdpt::GetRcvFormatForSnd(tFormat, Inst()->m_tConfBaseInfo);
	}
	else
	{
		wOutIndx = CTpTypeAdpt::GetRcvFormat(tFormat, Inst()->m_tConfBaseInfo.m_atTpMainVideoRes, Inst()->m_tConfBaseInfo.m_wMainNum);
	}

	if (!TP_VALID_HANDLE(wOutIndx))
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::AskFrameToBrdVmp. Invaild ChnIndx ! ConfID:%d, EqpID:%d, bIsFromVirSpeaker:%d, Res:%d.\n",
			Inst()->GetInsID(), ptVmpRes->m_tEqpRes.m_byEqpID, bIsFromVirSpeaker, tFormat.m_emRes));
		return FALSE;
	}

 	TTPVmpAskFrame tAskFrame;
 	tAskFrame.m_byEqpID = ptVmpRes->m_tEqpRes.m_byEqpID;
 	tAskFrame.m_byChanIndx = (u8)wOutIndx;
 	
 	CTpMsg cMsg;
#ifdef _USE_XMPUEQP_ 
	cMsg.SetEvent(evUms_XmpuAskVmpKey_Req);
	cMsg.SetBody(&tAskFrame, sizeof(tAskFrame));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

#else
	cMsg.SetEvent(ev_TPVmp_FastUpdate_Req);
	cMsg.SetBody(&tAskFrame, sizeof(tAskFrame));
	cMsg.Post(ptVmpRes->m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
#endif
	
 	MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::AskFrameToBrdVmp. ConfID:%d, EqpID:%d, ChnIndx:%d\n", 
									Inst()->GetInsID(), ptVmpRes->m_tEqpRes.m_byEqpID, wOutIndx));

	return TRUE;
}

BOOL32 CUmsVmp::AskFrameToBrdVmp( TBrdVmpRes* ptVmpRes, u16 wSrcEpID, BOOL32 bIsFromVirSpeaker )
{
	CUmsConfInst* pInst = Inst();
	
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetCapsetNode(wSrcEpID);
	if ( NULL == ptNode || !ptNode->IsChanOn() )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::AskFrameToBrdVmp. ptNode is NULL! ConfID:%d, SrcEpID:%d\n", pInst->GetInsID(), wSrcEpID));
		return FALSE;
	}

	BOOL32 bRet = FALSE;
	if (bIsFromVirSpeaker)
	{
		bRet = AskFrameToBrdVmp(ptVmpRes, ptNode->m_tVidSndFormat.m_tFormat, bIsFromVirSpeaker);
	}
	else
	{
		bRet = AskFrameToBrdVmp( ptVmpRes, ptNode->m_tVidRcvFormat.m_tFormat, bIsFromVirSpeaker);
	}

	return bRet;
}

void CUmsVmp::StopSpeakerVmp()
{
	BOOL32 bDis = Inst()->GetUmsDiscuss()->IsUIDiscussOn();
	if (NULL != m_pcSpeakerVmp && !bDis)
	{
		Inst()->GetVmpServiceHandle()->Release(m_pcSpeakerVmp);
		m_pcSpeakerVmp = NULL;
		Inst()->GetSpeaker().m_pcSingleVmp = NULL;
		Inst()->GetSpeaker().m_bSingleVmpStart = FALSE;
		CNetPortMgr::FreeMediaTrans(Inst(), Inst()->GetSpeaker().m_tToVmpDs);
	}

	m_bSpeakerVmpCfg = FALSE;
	m_emVmpType = em_Vmp_Invalid;
	m_wVmpEpID = TP_INVALID_INDEX;

	Inst()->TryReleaseVirSingleBas();

	if (!Inst()->m_bIsQuiting)
	{
		CNetPortMgr::CreateSpeakerToVirSpeaker(Inst());

		// ���������� ��������ϯ �ϳ�������
		Inst()->AdjustNewSpeakerToAllNode(Inst()->curSpeakerID(), TRUE);
	}

	NotifySpeakerVmpToDownUms();

	return;
}

u16 CUmsVmp::CalcVipNum(EMVmpStyle tStyle, EMEqpModleType tType)
{//����vip��Ϊ108060�£�����ǰ����·�� ����� 4 2 8 19 ������չ��

	u16 wMaxMemberNum = CTpTypeAdpt::GetVmpMemberNumByStyle(tStyle);
	u16 wVipNum = 0;
	if (tType == em_vmp_basic_eqp_mdl )
	{
		if ( wMaxMemberNum <=  4 )
		{
			wVipNum = 4;
		}
		else
		{
			if ( m_b108060 )
			{
				wVipNum = 1;
			}
			else
			{
				wVipNum = 2;
			}
		}
	}
	else if ( tType == em_vmp_enhanced_eqp_mdl )
	{
		if ( m_b108060 )
		{
			wVipNum = 8;
		}
		else
		{
			wVipNum = 19;
		}
	}

	return wVipNum;
}

void CUmsVmp::CalcBrdVmpVipNum( TBrdVmpRes* ptVmpRes )
{
	// �����������ͺͺϳɷ�����VipNum
	ptVmpRes->m_wVipNum = CalcVipNum(ptVmpRes->m_tVmpStyle.m_emVmpStyle, ptVmpRes->m_tEqpRes.m_emMdlType);

	if(ptVmpRes->m_wMemberNum <= ptVmpRes->m_wVipNum )
	{//��Ա��С��vip����������Ҫ��vipУ�� ֱ�ӽ�����
		ptVmpRes->m_bNeedAdjVip = FALSE;
	}
	else
	{
		ptVmpRes->m_bNeedAdjVip = TRUE;
	}

	return;
}

void CUmsVmp::OnUmcVmpMemberCfgCmd( CTpMsg *const ptMsg )
{
	TLogUser tUsr;
	TP_SAFE_CAST(tUsr, ptMsg->GetBody());
	TTpVmpMemberCfg tCfg;
	TP_SAFE_CAST(tCfg, ptMsg->GetBody() + sizeof(TLogUser));

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnUmcVmpMemberCfgCmd. ConfID:%d, Flag:%d, Style:%d, Total:%d, CurNum:%d \n", 
		Inst()->GetInsID(), tCfg.m_wFlag, tCfg.m_emStyle, tCfg.m_wTotalNum, tCfg.m_wEpNum));

	TTpVmpMemberCfgInd tInd;
	tInd.m_wConfID = Inst()->GetInsID();

	TSaveCfgMgr* ptMgr = NULL;
	do 
	{
		ptMgr = m_tSaveMgr.FindCfgMgr(tCfg.m_wFlag);
		if ( NULL == ptMgr )
		{
			tInd.m_bRet = FALSE;
			break ;
		}

		if (0 == Inst()->m_wConfTemplateID)
		{
			tInd.m_bRet = FALSE;
			break;
		}
		
		ptMgr->m_emUi = EmUI_UMC;
		ptMgr->m_tUser = tUsr;
		ptMgr->m_bUsed = TRUE;

		ptMgr->m_tVmpCfg.m_emStyle = tCfg.m_emStyle;
		memcpy(&ptMgr->m_tVmpCfg.m_atEpList[ptMgr->m_tVmpCfg.m_wEpNum], tCfg.m_atEpList, sizeof(TTpVmpCfgChnl)*tCfg.m_wEpNum);
		ptMgr->m_tVmpCfg.m_wSpeakerIndx = tCfg.m_wSpeakerIndx;
		ptMgr->m_tVmpCfg.m_wDualIndx = tCfg.m_wDualIndx;
		u16 wOldCurNum = ptMgr->m_tVmpCfg.m_wEpNum;
		ptMgr->m_tVmpCfg.m_wEpNum += tCfg.m_wEpNum;
		
		tInd.m_wFlag = ptMgr->m_wIndex;

		if ( wOldCurNum == 0  && ptMgr->m_tVmpCfg.m_wEpNum < tCfg.m_wTotalNum )
		{
			//UMC ����Ind
			Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SaveVmpCfg_Ind, &tInd, sizeof(tInd), &tUsr);
			return ;
		}
		
		if ( ptMgr->m_tVmpCfg.m_wEpNum < tCfg.m_wTotalNum )
		{//��ʱ�������ȴ�
			return ;
		}

	} while (0);

	if ( !tInd.m_bRet )
	{
		//UMC ����Ind
		Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SaveVmpCfg_Ind, &tInd, sizeof(tInd), &tUsr);
		return ;
	}

	//֪ͨumsserver,����Ԥ��
	TSaveVmpPlanInfo tVmpPlanInfo;
	tVmpPlanInfo.m_wConfID = tCfg.m_wConfID;
	tVmpPlanInfo.m_tCfg = ptMgr->m_tVmpCfg;
	tVmpPlanInfo.m_wCfgIndex = ptMgr->m_wIndex;
	strncpy(tVmpPlanInfo.m_achConfname,Inst()->m_tConfBaseInfo.m_achConfName,TP_MAX_ALIAS_LEN);

	s8 abBuf[sizeof(TLogUser) + sizeof(TSaveVmpPlanInfo)] = {0} ;
	memcpy(abBuf ,&tUsr , sizeof(TLogUser));
	memcpy(abBuf + sizeof(TLogUser),&tVmpPlanInfo,sizeof(TSaveVmpPlanInfo));
	Inst()->NotifyMsgToService(ev_save_vmpcfg_req, &abBuf, sizeof(abBuf));

}

void CUmsVmp::OnCncVmpMemberCfgCmd( CTpMsg *const ptMsg )
{
//	return;

	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TTpVmpMemberCfg tCfg;
	TP_SAFE_CAST(tCfg, ptMsg->GetBody()+sizeof(TUmsHandle));

	if ( tHandle.GetEpID() != Inst()->chairID() )
	{
		return ;
	}
	
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnCncVmpMemberCfgCmd. ConfID:%d, Flag:%d, Style:%d, Total:%d, Num:%d\n",
		tCfg.m_wConfID, tCfg.m_wFlag, tCfg.m_emStyle, tCfg.m_wTotalNum, tCfg.m_wEpNum));
	
	TTpVmpMemberCfgInd tInd;
	tInd.m_wConfID = Inst()->GetInsID();
	
	TSaveCfgMgr* ptMgr = NULL;
	do 
	{
		ptMgr = m_tSaveMgr.FindCfgMgr(tCfg.m_wFlag);
		if ( NULL == ptMgr )
		{
			tInd.m_bRet = FALSE;
			break ;
		}

		if (0 == Inst()->m_wConfTemplateID)
		{
			tInd.m_bRet = FALSE;
			break;
		}

		if (ptMgr->m_tVmpCfg.m_wEpNum + tCfg.m_wEpNum > TP_VMP_MAX_IN_CHN_NUM)
		{
			tInd.m_bRet = FALSE;
			break;
		}
		
		ptMgr->m_emUi = EmUI_CNC;
		ptMgr->m_bUsed = TRUE;
		
		ptMgr->m_tVmpCfg.m_emStyle = tCfg.m_emStyle;
		memcpy(&ptMgr->m_tVmpCfg.m_atEpList[ptMgr->m_tVmpCfg.m_wEpNum], tCfg.m_atEpList, sizeof(TTpVmpCfgChnl)*tCfg.m_wEpNum);
		ptMgr->m_tVmpCfg.m_wSpeakerIndx = tCfg.m_wSpeakerIndx;
		ptMgr->m_tVmpCfg.m_wDualIndx = tCfg.m_wDualIndx;
		u16 wOldCurNum = ptMgr->m_tVmpCfg.m_wEpNum;
		ptMgr->m_tVmpCfg.m_wEpNum += tCfg.m_wEpNum;

		tInd.m_wFlag = ptMgr->m_wIndex;
		
		if ( wOldCurNum == 0  && ptMgr->m_tVmpCfg.m_wEpNum < tCfg.m_wTotalNum )
		{//��һ����Ҫ��Ӧ
			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
			UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SaveVmpCfg_Ind, &tInd, sizeof(tInd));
			return ;
		}
		
		if ( ptMgr->m_tVmpCfg.m_wEpNum < tCfg.m_wTotalNum )
		{//��ʱ�������ȴ�
			return ;
		}
		
	} while (0);
	
	if ( !tInd.m_bRet )
	{
		TUmsHandle tOutHandle;
		Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
		UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SaveVmpCfg_Ind, &tInd, sizeof(tInd));
		return ;
	}

	//֪ͨumsserver,����Ԥ��
	TLogUser tusr;
	TSaveVmpPlanInfo tVmpPlanInfo;
	tVmpPlanInfo.m_wConfID = tCfg.m_wConfID;
	tVmpPlanInfo.m_tCfg = ptMgr->m_tVmpCfg;
	tVmpPlanInfo.m_wCfgIndex = ptMgr->m_wIndex;
	strncpy(tVmpPlanInfo.m_achConfname,Inst()->m_tConfBaseInfo.m_achConfName,TP_MAX_ALIAS_LEN);

	s8 abBuf[sizeof(TLogUser) + sizeof(TSaveVmpPlanInfo)] = {0} ;
	memcpy(abBuf ,&tusr , sizeof(TLogUser));
	memcpy(abBuf + sizeof(TLogUser), &tVmpPlanInfo , sizeof(TSaveVmpPlanInfo));
	Inst()->NotifyMsgToService(ev_save_vmpcfg_req, &abBuf, sizeof(abBuf));
	
}

//Ԥ������Ļ�Ӧ
void CUmsVmp::OnSaveVmpPlanAck(CTpMsg *const ptMsg)
{
	u16 wCfgIndex = TP_INVALID_INDEX;
	BOOL32 bRefresh = FALSE;

	TP_SAFE_CAST(wCfgIndex,ptMsg->GetBody());
	TP_SAFE_CAST(bRefresh, ptMsg->GetBody() + sizeof(u16));

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnSaveVmpPlanAck. ConfID:%d,wCfgIndex%d, bRefresh:%d\n", Inst()->GetInsID(),wCfgIndex,bRefresh));
	
	TTpVmpMemberCfgInd tInd;
	tInd.m_wConfID = Inst()->GetInsID();
	if (!bRefresh)		//����ʧ��
	{
		tInd.m_bRet = FALSE	;
	}
	else
	{//����ɹ��򸲸�
		memcpy(&m_tVmpCfg, &m_tSaveMgr.m_atCfgMgr[wCfgIndex].m_tVmpCfg, sizeof(m_tVmpCfg));
	}

	EmUIType emUi = m_tSaveMgr.m_atCfgMgr[wCfgIndex].m_emUi;
	switch (emUi)
	{
	case EmUI_UMC:
		{
			TLogUser ptUser;
			ptUser = m_tSaveMgr.m_atCfgMgr[wCfgIndex].m_tUser;
			//UMC ����Ind
			Inst()->NotifyMsgToServiceForUI(ev_UMS_UMC_SaveVmpCfg_Ind, &tInd, sizeof(tInd), &ptUser);	
		}
		break;
	case EmUI_CNC:
		{
			//CNC ����Ind
			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, Inst()->chairID());
			UmsSendConfCtrl(tOutHandle, ev_UMS_CNC_SaveVmpCfg_Ind, &tInd, sizeof(tInd));	
		}
		break;
	default:
		{
			MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnSaveVmpPlanAck error. ConfID:%d,wCfgIndex%d, bRefresh:%d\n",Inst()->GetInsID(),wCfgIndex,bRefresh));
		}
		break;	
	}

	if ( bRefresh )
	{
		NotifyBrdVmpCfgToUI(TRUE,TRUE,NULL);
	}

	m_tSaveMgr.m_atCfgMgr[wCfgIndex].Clear();

}

void CUmsVmp::NotifyBrdVmpCfgToUI( BOOL32 bCNC /*= TRUE*/, BOOL32 bUmc /*= TRUE*/, TLogUser* ptUser /*= NULL*/)
{
	time_t CurTime;
	time(&CurTime);

	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, Inst()->chairID());
	
	TTpVmpMemberCfg tCfg;
	tCfg.m_wConfID = Inst()->GetInsID();
	tCfg.m_wTotalNum = TP_VMP_MAX_IN_CHN_NUM;
	tCfg.m_emStyle = m_tVmpCfg.m_emStyle;
	tCfg.m_wSpeakerIndx = m_tVmpCfg.m_wSpeakerIndx;
	tCfg.m_wDualIndx = m_tVmpCfg.m_wDualIndx;
	tCfg.m_wFlag = CurTime/TP_INVALID_INDEX;

	for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++  )
	{
		if ( tCfg.m_wEpNum == TP_REFRESH_LIST_EIGHT )
		{
			if( bUmc )
			{
				//֪ͨ����UMC
				if (wIndex == TP_REFRESH_LIST_EIGHT)
				{
					tCfg.m_bFirst = TRUE;  
				}
				Inst()->NotifyMsgToServiceForUI(ev_UMC_UMS_SaveVmpCfg_Cmd, &tCfg, sizeof(tCfg), ptUser);
			}
			if ( Inst()->IsChairConf() && bCNC )
			{
				if (wIndex == TP_REFRESH_LIST_EIGHT)
				{
					tCfg.m_bFirst = TRUE;
				}
				UmsSendConfCtrl(tOutHandle, ev_CNC_UMS_SaveVmpCfg_Cmd, &tCfg, sizeof(tCfg));
			}
			tCfg.m_wEpNum = 0;
			tCfg.m_bFirst = FALSE;
		}
		tCfg.m_atEpList[tCfg.m_wEpNum++] = m_tVmpCfg.m_atEpList[wIndex];
	}

	if ( tCfg.m_wEpNum > 0 )
	{
		if( bUmc )
		{
			//֪ͨ����UMC
			Inst()->NotifyMsgToServiceForUI(ev_UMC_UMS_SaveVmpCfg_Cmd, &tCfg, sizeof(tCfg), ptUser);
		}
		if ( Inst()->IsChairConf() && bCNC )
		{
			TUmsHandle tOutHandle;
			Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, Inst()->chairID());
			UmsSendConfCtrl(tOutHandle, ev_CNC_UMS_SaveVmpCfg_Cmd, &tCfg, sizeof(tCfg));
		}
	}
	return ;
}

BOOL32 CUmsVmp::AdjustGetVidFailed(CUmsConfInst* pcInst, u16 wGetIndex )
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex++)
	{
		if (m_atBrdVmp[wIndex].m_wConfID != pcInst->GetInsID())
		{
			continue;
		}

		for (u16 wLoop = 0; wLoop < TP_VMP_MAX_IN_CHN_NUM; wLoop++)
		{
			if (m_atBrdVmp[wIndex].m_atMember[wLoop].m_wGetIndex != wGetIndex)
			{
				continue;
			}

			CUmsConfInst::GetVidAudEx()->Release(pcInst, m_atBrdVmp[wIndex].m_atMember[wLoop].m_wGetIndex);
			
			m_atBrdVmp[wIndex].m_atMember[wLoop].ClearGetVid();
			
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_VMP_GetVidFail, Inst()->chairID(), 
				m_atBrdVmp[wIndex].m_atMember[wLoop].m_tVmpMember.m_wEpID, m_atBrdVmp->m_tEqpRes.m_byEqpID);

			if (m_atBrdVmp[wIndex].m_atMember[wLoop].IsAdjustRes() && emTPVResEnd != m_atBrdVmp[wIndex].m_atMember[wLoop].m_emRes)
			{
				//������ʧ���ˣ��ָ��ն˷ֱ���
				Inst()->GetNodeMgr()->AdjustNodeRes( m_atBrdVmp[wIndex].m_atMember[wLoop].m_tVmpMember.m_wEpID, 
					m_atBrdVmp[wIndex].m_atMember[wLoop].m_tVmpMember.m_wScreenIndx, m_atBrdVmp[wIndex].m_atMember[wLoop].m_emRes, TRUE);
				m_atBrdVmp[wIndex].m_atMember[wLoop].m_emRes = emTPVResEnd;
			}

			CNetPortMgr::CreateAllMemberToBrdVmp(pcInst, &m_atBrdVmp[wIndex]);

			return TRUE;
		}
	}

	return FALSE;
}

void CUmsVmp::AdjustVipForMember(TBrdVmpRes* ptVmpRes, TBrdVmpMember* ptMember, TVmpMemberPool* ptMemberPool)
{
	if (NULL == ptVmpRes || NULL == ptMember || NULL == ptMemberPool)
	{
		return;
	}

	TCallNode*	ptNode = Inst()->m_pcNodeMgr->GetNode(ptMember->m_tVmpMember.m_wEpID);
	if ( NULL == ptNode || !ptNode->IsChanOn() || !ptNode->IsVidSndValid() )
	{
		return;
	}

	if (ptMember->m_wIndx == ptVmpRes->m_tVmpStyle.m_wDualIndx)
	{// ˫���ֱ���С�ںϳ������Ʒֱ��� ��������ռvip��ֱ�ӽ��ϳ�
		if (CTpTypeAdpt::ResolutionMaxOpr(ptMember->m_emRes, ptNode->m_tDualVidSndFormat.m_tFormat.m_emRes) )
		{
			ptMember->SetDs();
			return;
		}
	}
	else
	{// �᳡�ֱ���С�ںϳ������Ʒֱ��� ��������ռvip��ֱ�ӽ��ϳ�
		if (CTpTypeAdpt::ResolutionMaxOpr(ptMember->m_emRes, ptNode->m_tVidSndFormat.m_tFormat.m_emRes))
		{
			ptMember->SetDs();
			return;
		}
	}

	// ��ռ���ȼ�  
	// ˫������ > ���Ի᳡���� > ������ͨ�� > ���ܽ��ֱ����ն� > ��ϯ�᳡ > ��ѡ���᳡ > �ܽ��ֱ����ն� > vrs����

	// ���ݳ�Ա��ݣ�ȷ��ռ��vip�����ȼ�
	u16 wLevel = 0;
	if (ptMember->m_wIndx == ptVmpRes->m_tVmpStyle.m_wDualIndx)
	{// ˫������
		wLevel = 2000;
	}
	else if (ptMember->m_wIndx == ptVmpRes->m_tVmpStyle.m_wSpeakerIndx)
	{// ���Ի᳡����
		wLevel = 1500;
	}
	else if (ptNode->m_wEpID == Inst()->curSpeakerID())
	{// ���Ի᳡ͨ��
		wLevel = 1000;
	}
	else if (!ptNode->IsCanAdjustRes() && !ptNode->IsVRS())
	{// ���ܽ��ֱ����ն�(������vrs)
		wLevel = 800;
	}
	else if (ptNode->m_wEpID == Inst()->chairID())
	{// ���᳡ͨ��
		wLevel = 500;
	}
	else if (ptNode->bIsSel())
	{// ��ѡ���᳡
		wLevel = 300;
	}
	else if (!ptNode->IsVRS())
	{// �ܽ��ֱ��ʵ��ն�
		wLevel = 200;
	}
	else
	{// vrs
		wLevel = 100;
	}

	// ��Ҫ��ռvip
	// ��ռvip��Ϊ���֣�1. ���е�vip  2. �ѱ�ռ�õ�vip

	if (ptVmpRes->m_wCurVipNum < ptVmpRes->m_wVipNum)
	{//  ��ռ���е�vip
		ptMember->SetVip();
		ptMember->SetDs();
		ptVmpRes->m_wCurVipNum++;
	}
	else
	{
		TCallNode* ptNodeTemp = NULL;
		TBrdVmpMember* ptMemberTemp = NULL; 
		u16 wIndex = TP_INVALID_INDEX;
		ptMemberTemp = ptMemberPool->GetMember(wIndex, wLevel);
		if (NULL == ptMemberTemp || wIndex >= TP_VMP_MAX_IN_CHN_NUM || !ptMemberTemp->IsVip())
		{//�ó�Աlevel̫�ͣ�ռ����vip

			ptNodeTemp = Inst()->GetNode(ptMember->m_tVmpMember.m_wEpID);

			ptMemberTemp = ptMember;

		}
		else
		{//�ó�Ա�Ѿ�ռ��vip
			ptNodeTemp = Inst()->GetNode(ptMemberTemp->m_tVmpMember.m_wEpID);

			// ����ռ�ĳ�Ա������vip
			ptMemberTemp->ClearVip();
			ptMemberPool->DelMember(wIndex); // ��vip�����޳�

			ptMember->SetVip(); // ��ռ�ɹ�
			ptMember->SetDs();

		}

		//����VIP�ĳ�Ա���ٴ�ȷ�ϣ��Ƿ񴴽�����

		if (ptMemberTemp->m_tVmpMember.IsDual())
		{// ˫��������vip��ֱ�Ӳ��������������������֣�
			ptMemberTemp->ClearDs();

			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_VMP_Dual_ChanNoVid, Inst()->chairID(), (u32)ptMemberTemp->m_tVmpMember.m_wEpID,
					(u32)ptVmpRes->m_tEqpInfo.m_byEqpID);

		}
		else if (NULL != ptNodeTemp && ptNodeTemp->IsChanOn() && ptNodeTemp->IsVidSndValid())
		{
			if (ptNodeTemp->IsSmallVidSnd())
			{// С�������ϳ�
				ptMemberTemp->SetDs();
				ptMemberTemp->SetSmallVid();
			}
			else if (ptMemberTemp->m_tVmpMember.m_wEpID == Inst()->curSpeakerID())
			{// ������������vip��ֱ�Ӳ��������������������֣�
				ptMemberTemp->ClearDs();
				
				Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_VMP_Speaker_ChanNoVid, Inst()->chairID(), (u32)ptMemberTemp->m_tVmpMember.m_wEpID,
					(u32)ptVmpRes->m_tEqpInfo.m_byEqpID);

			}
			else if (ptNodeTemp->IsCanAdjustRes())
			{
				// ���Խ��ֱ��ʽ��ϳɣ����˴��������������ݶԱȣ�ͳһ����
				ptMemberTemp->SetDs();
				ptMemberTemp->SetAdjustRes();

			}
			else
			{// ����������
				ptMemberTemp->ClearDs();

				Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_VMP_Audience_ChanNoVid, Inst()->chairID(), (u32)ptMemberTemp->m_tVmpMember.m_wEpID,
					(u32)ptVmpRes->m_tEqpInfo.m_byEqpID);

			}
		}
	}

	if (ptMember->IsVip())
	{// ����vip��		
	 // vip���У�levelԽ�ͣ�Խ���ױ���ռ
		ptMemberPool->AddMember(ptMember, wLevel);
	}

	return;
}

u16 CUmsVmp::CalcBrdVmpCanDsEpNum( TBrdVmpRes* ptVmpRes )
{//������Դ������������� ������������ĺ�����ɾ��
	TBrdVmpMember* ptMember = NULL;
	u16 wChanNum = 0;
	for (u16 wIndex = ptVmpRes->m_wMemberNum-1; wIndex >=0; wIndex -- )
	{
		ptMember = &ptVmpRes->m_atMember[wIndex];

		if ( !TP_VALID_HANDLE(ptMember->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		if ( !ptMember->IsDs() )
		{
			wChanNum ++;
		}
	}
	return ptVmpRes->m_wMemberNum - wChanNum;
}

void CUmsVmp::NotifySpeakerVmpToDownUms()
{
	TVmpCasecadeNtfy tNtfy;
	tNtfy.m_bBrdVmp = m_ptConfBrdVmp == NULL ? FALSE : TRUE;
	tNtfy.m_emSpeakerVmpType = m_emVmpType;
	strncpy(tNtfy.m_szBrdVmpAlias, m_szBrdVmpAlias, TP_MAXLEN_EQP_ALIAS);
	tNtfy.m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';
	
	TUmsHandle tHandle;
	//�����㲥 �������ⷢ�����м�ڵ� ������ÿ���ڵ�Ĺ㲥Ŀ��
	for (TCapNode* ptNode = Inst()->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = Inst()->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if ( !ptNode->IsChanOn() || !ptNode->IsUms())
		{
			continue;
		}
		
		Inst()->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tHandle, ev_UMS_UMS_VmpCasecade_Ntfy, &tNtfy, sizeof(tNtfy));
	}
	return;
}

void CUmsVmp::AdjustCnsSpeaker(TCallNode* ptNode)
{
	if (NULL == ptNode || !ptNode->IsChanOn() || !ptNode->IsVidSndValid())
	{
		return;
	}

	if ( Inst()->m_bIsQuiting )
	{
		return ;
	}

	if (!Inst()->GetUmsDiscuss()->IsDiscussModle() && ptNode->m_wEpID == m_wVmpEpID)
	{// ������ģʽ�£������˺ϳ�

		//�������� �᳡���ϳ�
		CNetPortMgr::CreatVidToSingleVmpTp(Inst());

	}

	if (ptNode->m_wEpID != Inst()->curSpeakerID())
	{
		return;
	}

	// ���Ի᳡�ķ�����ϯ�ı䣬���ڰ������Ը���ĺϳ�����Ҫ����
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( m_atBrdVmp[wIndex].m_wConfID != Inst()->GetInsID() )
		{
			continue;
		}
		
		if ( m_atBrdVmp[wIndex].m_bVmpAuto )
		{
			continue;
		}

		if ( !TP_VALID_HANDLE(m_atBrdVmp[wIndex].m_tVmpStyle.m_wSpeakerIndx) )
		{
			continue;
		}
		
		//����һ��
		BackupBrdVmpParam(&m_atBrdVmp[wIndex]);
		
		//���������˸���
		AdjustSpeakerFollow(&m_atBrdVmp[wIndex]);
		
#ifdef _USE_XMPUEQP_
		//�з����ˣ�����Vip�Լ���������
		AdjustBrdXmpuVmpMember(&m_atBrdVmp[wIndex]);
#else
		//�з����ˣ�����Vip�Լ���������
		AdjustBrdVmpMember(&m_atBrdVmp[wIndex]);
#endif
			
	}


	return;
}

void CUmsVmp::NotifyBrdVmpToUMC( TBrdVmpRes* ptVmpRes, EmTpOprType emOpr )
{
	TBrdVmpResArray tArray;
	tArray.m_wNum = 1;
	ptVmpRes->GetUIInfo(tArray.m_atVmpNtfy[0]);
	tArray.m_atVmpNtfy[0].m_bVmpAuto = ptVmpRes->m_bVmpAuto;
	tArray.m_atVmpNtfy[0].m_emOpr = emOpr;
	
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(1));
	//֪ͨ����UMC
	pInst->NotifyMsgToServiceForUI(ev_UMS_UMC_BrdVmp_Ntfy, &tArray, sizeof(tArray));
}

void CUmsVmp::SetQtMediaKey( const TTPQTMediaKeyInfo& tInfo, u16 wConfId)
{
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ( !m_atBrdVmp[wIndex].IsRersves() || wConfId != m_atBrdVmp[wIndex].GetConfId())
		{
			continue;
		}

		//�����ϳ�
		CTpMsg cMsg;
		cMsg.SetEvent(ev_TPVmp_SetMediaKey_Req);
		cMsg.SetBody(&m_atBrdVmp[wIndex].m_tEqpRes.m_byEqpID, sizeof(u8));
		cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
		cMsg.Post(m_atBrdVmp[wIndex].m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}
}

void CUmsVmp::FlushXmpuVmp()
{
	TXmpuVmpManger* ptManger = &CUmsConfInst::m_tXmpuVmpManger;

	for (u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; ++wIndex)
	{
		if (ptManger->m_adwVmpID[wIndex] == 0)
		{
			continue;
		}

		TBrdVmpRes* ptVmp  = FindBrdVmpByEqp(ptManger->m_adwVmpID[wIndex]);
		if ( NULL != ptVmp )
		{
			// vmp ����
			if (ptManger->m_aemStat[wIndex] == VmpManger_Mpu2tp ||
				((ptManger->m_aemStat[wIndex] == VmpManger_Normal)&& ptVmp->IsStatNormal()))
			{
				// ����֪ͨ���еĻ���
				for (u16 wConfIndex = 1; wConfIndex <= TP_UMS_MAX_CONFNUM; ++wConfIndex)
				{
					CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfIndex));
					if (pInst->CurState() == CUmsConfInst::inst_idle)
					{
						continue;
					}
					pInst->GetVmp()->OnXmpuVmpDisConnect(ptManger->m_adwVmpID[wIndex]);
				}
			}
			else
			{
				MdlHint(Ums_Mdl_Call, ("CUmsVmp::FlushXmpuVmp. ptVmp is already exit. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
			}
			
			continue ;
		}

		// ��ǰvmp������
		if (ptManger->m_aemStat[wIndex]  != VmpManger_Normal)
		{
			continue ;
		}

		ptVmp = FindIdleBrdVmp();
		if (NULL == ptVmp)
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::FlushXmpuVmp. ptVmp is NULL, no idle. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
			return;
		}
		MdlHint(Ums_Mdl_Call, ("CUmsVmp::FlushXmpuVmp. wIndex:%d, EqpID%d\n", wIndex, ptManger->m_adwVmpID[wIndex]));

		ptVmp->m_tEqpInfo.m_byEqpID = ptManger->m_adwVmpID[wIndex];
		ptVmp->m_tEqpInfo.m_emEqpType = em_vmp_mdl;
		ptVmp->m_emStat = EmBrdVmpStat_Idle;
		ptVmp->m_tEqpRes.m_byEqpID = ptManger->m_adwVmpID[wIndex];
		strncpy(ptVmp->m_tEqpInfo.m_szEqpAlias,ptManger->m_aachEqpAlias[wIndex], TP_MAXLEN_EQP_ALIAS);
		ptVmp->m_tEqpInfo.m_szEqpAlias[TP_MAXLEN_EQP_ALIAS - 1] = '\0';
		NotifyBrdVmpToAllConf(ptVmp, tp_OprType_Add);
	}
	
	return ;
}

void CUmsVmp::OnXmpuVmpDisConnect(u32	dwEqpID)
{
	
	TBrdVmpRes* ptVmp = FindBrdVmpByEqp(dwEqpID);
	if ( NULL == ptVmp )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnXmpuVmpDisConnect. ptVmp is NULL! EqpID:%d\n", dwEqpID));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnXmpuVmpDisConnect. confID:%d, EqpID:%d\n", ptVmp->m_wConfID, dwEqpID));

	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(ptVmp->m_wConfID));
	if ( pInst != NULL )
	{
		if( ptVmp->m_emStat == EmBrdVmpStat_Brd )
		{//��ѡ�������ڹ㲥 ��Ҫֹͣ
			TBrdVmpReq tReq;
			tReq.m_wConfID = pInst->GetInsID();
			tReq.m_bBrd = FALSE;
			memcpy(&tReq.m_tEqp, &ptVmp->m_tEqpInfo, sizeof(tReq.m_tEqp));

			pInst->GetVmp()->BrdVmp(tReq);	
		}

		if( ptVmp->m_emStat == EmBrdVmpStat_Normal )
		{
			pInst->GetVmp()->ReleaseBrdVmpParam(ptVmp);
		}
	}

	EmBrdVmpCBOprType emOpr = EmBrdVmpCBOprType_DisConnect;
	if( NULL != ptVmp->m_pfSelViewCB )
	{
		ptVmp->m_pfSelViewCB(ptVmp->m_pSelViewParam, ptVmp, &emOpr);
	}

	if( NULL != ptVmp->m_pfTvWallCB )
	{
		ptVmp->m_pfTvWallCB(ptVmp->m_pTvWallParam, ptVmp, &emOpr);
	}

	if( NULL != ptVmp->m_pfGetVmpCB )
	{
		ptVmp->m_pfGetVmpCB(ptVmp->m_pGetVmpParam, ptVmp, &emOpr);
	}
	NotifyBrdVmpToAllConf(ptVmp, tp_OprType_Del);

	if (ptVmp->m_cToVmpDsInfo.GetElementNum() != 0)
	{
		CNetPortMgr::FreeMediaTrans(Inst(), ptVmp->m_cToVmpDsInfo);
	}
	ptVmp->Clear();

	return ;
}

EmRervesVmpRet CUmsVmp::RerveseXmpuVmp( TRersvesEqpReq& tReq )
{
	if (Inst()->CurState() == CUmsConfInst::inst_idle)
	{
		return EmRervesVmpRet_unKnow;
	}

	TBrdVmpRes* ptVmpRes = NULL;
	TXmpuVmpParam tVmpParam;
	TXmpuEqpRes tRes;
	tRes.m_dwEqpID = tReq.m_tEqp.m_byEqpID;

	ptVmpRes = FindBrdVmpByEqp(tReq.m_tEqp.m_byEqpID);
	if ( NULL == ptVmpRes )
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. ptVmpRes is NULL! ConfID:%d, EqpID:%d\n", 
			Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID));
		return EmRervesVmpRet_NoExist;
	}

	if ( tReq.m_bRersves )
	{//ռ��

		if( ptVmpRes->IsRersves())
		{
			if (ptVmpRes->m_wConfID == Inst()->GetInsID())
			{
				MdlHint(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. repeat rervese! rsp is ok! ConfID:%d, RerConfID:%d, EqpID:%d\n", 
					Inst()->GetInsID(), ptVmpRes->m_wConfID, tReq.m_tEqp.m_byEqpID));
				return EmRervesVmpRet_Success;
			}
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. busy! ConfID:%d, RerConfID:%d, EqpID:%d\n", 
				Inst()->GetInsID(), ptVmpRes->m_wConfID, tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_Busy;
		}

		if (!CUmsConfInst::m_tXmpuVmpManger.CanTask(tReq.m_tEqp.m_byEqpID))
		{
			MdlHint(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. this eqpid can not task! ConfID:%d, RerConfID:%d, EqpID:%d\n", 
				Inst()->GetInsID(), ptVmpRes->m_wConfID, tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_unKnow;
		}

		//���� �� �����ϳ� 
		u8 byOutNum = 0;
		TUmsVidFormat atVidFormat[TP_VMP_MAX_OUT_CHN_NUM];

		// ��ģ�������и�ʽ��
		for (u16 wIndex = 0; wIndex < localmin(Inst()->m_tConfBaseInfo.m_wMainNum, TP_VMP_MAX_OUT_CHN_NUM-1); wIndex++)
		{
			atVidFormat[byOutNum] = Inst()->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex];
			byOutNum++;
		}

		tVmpParam.m_ptEqp = &tRes;
		tVmpParam.m_emEqpType = em_XmpuVmp_Eqp;
		tVmpParam.m_wConfID = Inst()->GetInsID();
		tVmpParam.m_dwMediaIp =  Inst()->m_tEqpConfDs.m_dwEqpIp;
		tVmpParam.m_emVmpStyle = tp_VmpStyle_TWENTYFIVE;//Ĭ��ʹ��25���
		tVmpParam.m_byVMPMemberNum = ptVmpRes->m_wMemberNum;
		memcpy(tVmpParam.m_atVMPMember, ptVmpRes->m_atMember, sizeof(tVmpParam.m_atVMPMember));
		tVmpParam.m_byOutMemBerNum = byOutNum;
		memcpy(tVmpParam.m_atVMPOutMember,atVidFormat, sizeof(tVmpParam.m_atVMPOutMember));
		tVmpParam.m_atVMPMember[0].m_tEncrypt = Inst()->GetConfBase().m_tEncrypt;
#ifdef _USE_XMPUEQP_
		//�ж��Ƿ��п��õ�ý����Դ
		if (!CheckIdleMediaSource(SINGLE_NUMBER,0, 0))
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. No Vmp Source! ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_ResFull;
		}
		if ( !AssignXmpuEqp(&tVmpParam) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. AssignEqpEx Failed! ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_unKnow;
		}

		memcpy(ptVmpRes->m_atDecMiddleRtpAddr, tVmpParam.m_atDecMiddleRtpAddr, sizeof(ptVmpRes->m_atDecMiddleRtpAddr));
		memcpy(ptVmpRes->m_atDecRtcpAddr, tVmpParam.m_atDecRtcpAddr, sizeof(ptVmpRes->m_atDecRtcpAddr));
		memcpy(ptVmpRes->m_atEncRtpAddr, tVmpParam.m_atEncRtpAddr, sizeof(ptVmpRes->m_atEncRtpAddr));
		memcpy(ptVmpRes->m_atEncMiddleRtcpAddr, tVmpParam.m_atEncMiddleRtcpAddr, sizeof(ptVmpRes->m_atEncMiddleRtcpAddr));
		ptVmpRes->m_byVipMaxStyle = tVmpParam.m_byVipMaxStyle;
		ptVmpRes->m_byVipNum = tVmpParam.m_byVipNum;
		// ռ��vmp ֪ͨmpu2-tpģ��ˢ�ºϳ���
		CUmsConfInst::m_tXmpuVmpManger.TaskVmp(tRes.m_dwEqpID, TRUE);
		CEqpService::Instance().FlushXmpuMpu2();
#else
		return EmRervesVmpRet_unKnow;
#endif

		ptVmpRes->m_wConfID = Inst()->GetInsID();
	}
	else
	{//ȡ��ռ��

		if(!ptVmpRes->IsRersves() || ptVmpRes->m_wConfID != Inst()->GetInsID())
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. NoExist! ConfID:%d, RerConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_wConfID, tReq.m_tEqp.m_byEqpID));
			return EmRervesVmpRet_NoExist;
		}

		if ( ptVmpRes == m_ptConfBrdVmp )
		{//ȡ�����ǵ�ǰ�㲥�����裬����Ҫ��ֹͣ
			TBrdVmpReq tReq;
			tReq.m_wConfID = Inst()->GetInsID();
			tReq.m_bBrd = FALSE;
			memcpy(&tReq.m_tEqp, &ptVmpRes->m_tEqpInfo, sizeof(tReq.m_tEqp));		
			BrdVmp(tReq);
		}

		if (ptVmpRes->m_emStat == EmBrdVmpStat_Normal)
		{
			ReleaseBrdVmpParam(ptVmpRes);
		}

		tVmpParam.m_ptEqp = &tRes;
		tVmpParam.m_emEqpType = em_XmpuVmp_Eqp;
#ifdef _USE_XMPUEQP_
		if ( !ReleaseXmpuEqp(&tVmpParam) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsVmp::RerveseXmpuVmp. ReleaseEqpEx Failed! ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_tEqpRes.m_byEqpID));
			ptVmpRes->m_emStat = EmBrdVmpStat_Error;
		}
		// �ͷ�vmp ֪ͨmpu2-tpģ��ˢ�ºϳ���
		CUmsConfInst::m_tXmpuVmpManger.ReleaseVmp(tRes.m_dwEqpID);
		CEqpService::Instance().FlushXmpuMpu2();
#else
		return EmRervesVmpRet_unKnow;
#endif		

		EmBrdVmpCBOprType emOpr = EmBrdVmpCBOprType_Stop;

		if( NULL != ptVmpRes->m_pfSelViewCB )
		{
			ptVmpRes->m_pfSelViewCB(ptVmpRes->m_pSelViewParam, ptVmpRes, &emOpr);
		}

		if( NULL != ptVmpRes->m_pfTvWallCB )
		{
			ptVmpRes->m_pfTvWallCB(ptVmpRes->m_pTvWallParam, ptVmpRes, &emOpr);
		}

		if( NULL != ptVmpRes->m_pfGetVmpCB )
		{
			ptVmpRes->m_pfGetVmpCB(ptVmpRes->m_pGetVmpParam, ptVmpRes, &emOpr);
		}

		ptVmpRes->m_emStat = EmBrdVmpStat_Idle;
		ptVmpRes->m_wConfID = TP_INVALID_INDEX;
		ptVmpRes->m_bOnLine = FALSE;

		if (ptVmpRes->m_cToVmpDsInfo.GetElementNum() != 0)
		{
			CNetPortMgr::FreeMediaTrans(Inst(), ptVmpRes->m_cToVmpDsInfo);
		}
	}

	return EmRervesVmpRet_Success;
}

void CUmsVmp::OnXmpuVmpMdyNty( TXmpuVmpMdyInfo tInfo )
{
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnXmpuVmpMdyNty. EqpID:%d, bSucc:%d\n", tInfo.m_dwEqpID, tInfo.m_bSuccess));
	CUmsConfInst* pInst = Inst();
	TBrdVmpRes* ptVmp = FindBrdVmpByEqp(tInfo.m_dwEqpID);
	if ( NULL == ptVmp )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsVmp::OnXmpuVmpMdyNty. ptVmp is NULL! EqpID:%d\n", tInfo.m_dwEqpID));
		return ;
	}

	// ʧ�� ��disconnect����
	if (!tInfo.m_bSuccess)
	{
		OnXmpuVmpDisConnect(tInfo.m_dwEqpID);
		//ˢ��ʧ�ܺϳ���������ʼ��
		CUmsConfInst::m_tXmpuVmpManger.ReleaseVmp(tInfo.m_dwEqpID);
		FlushXmpuVmp();
		CEqpService::Instance().FlushXmpuMpu2();
		pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_AssignVmpFail, pInst->chairID());
		return;
	}
	ptVmp->m_bOnLine = TRUE;
	ChangeBrdXmpuVmpParam(ptVmp);

	memcpy(ptVmp->m_atDecRtpAddr,  tInfo.m_atDecRtpAddr, sizeof(ptVmp->m_atDecRtpAddr));
	memcpy(ptVmp->m_atEncRtcpAddr,  tInfo.m_atEncRtcpAddr, sizeof(ptVmp->m_atEncRtcpAddr));

	CNetPortMgr::AdjustXmpuMiddleAddrToVmp(Inst(), ptVmp);

}

EmBrdVmpRet CUmsVmp::SetBrdXmpuVmp( TSetVmpInfoReq& tBrdReq )
{
	if (Inst()->CurState() == CUmsConfInst::inst_idle)
	{
		return EmBrdVmpRet_Fail;
	}

	TBrdVmpRes* ptVmpRes = FindBrdVmpByEqp(tBrdReq.m_tEqp.m_byEqpID);
	if ( NULL == ptVmpRes || !ptVmpRes->IsRersves())
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::SetBrdVmp. ptVmpRes is NULL! ConfID:%d, EqpID:%d, bRersvesConId:%d\n", 
			Inst()->GetInsID(), tBrdReq.m_tEqp.m_byEqpID, ptVmpRes == NULL ? 0 : ptVmpRes->m_wConfID));
		return EmBrdVmpRet_NoExist;
	}

	//
	u16 wChanNum = localmin(CTpTypeAdpt::GetVmpMemberNumByStyle(tBrdReq.m_tStyle.m_emVmpStyle), tBrdReq.m_tStyle.m_wChnlNum);
	tBrdReq.m_tStyle.m_wChnlNum = wChanNum;
	tBrdReq.m_tStyle.ClearChnl(wChanNum);

	ptVmpRes->SetUIInfo(tBrdReq);

	UpdateBrdXmpuVmpParam(ptVmpRes);

	if (EmBrdVmpStat_Idle == ptVmpRes->m_emStat)
	{
		ptVmpRes->m_emStat = EmBrdVmpStat_Normal;
	}

	return EmBrdVmpRet_Succes;
}

void CUmsVmp::UpdateBrdXmpuVmpParam( TBrdVmpRes* ptVmpRes )
{
	if ( ptVmpRes->m_bVmpAuto )
	{
		AdjustAutoVmpStyle(ptVmpRes);
	}

	MdlHint(Ums_Mdl_Call, ("CUmsVmp::UpdateBrdXmpuVmpParam. ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_tEqpInfo.m_byEqpID));

	//����+���
	BackupBrdVmpParam(ptVmpRes);
	ptVmpRes->ReSetMember();

	CUmsConfInst* pInst = Inst();
	u16 wIndex = 0;
	TCallNode* ptNodeTmp = NULL;
	// ��������
	TTPEncrypt tEncrypt = pInst->GetConfEncryptInfo();

	for ( wIndex = 0; wIndex < ptVmpRes->m_tVmpStyle.m_wChnlNum; ++wIndex)
	{//�ֶ� �����uiֵ��ϳɣ��������Чֵ����λ�ÿճ�

		if (wIndex == ptVmpRes->m_tVmpStyle.m_wSpeakerIndx || wIndex == ptVmpRes->m_tVmpStyle.m_wDualIndx)
		{// �ճ������λ��
			ptVmpRes->m_wMemberNum++;
			continue;
		}

		if ( !ptVmpRes->m_tVmpStyle.m_atVmpChnl[wIndex].IsValid() )
		{
			ptVmpRes->m_wMemberNum++;
			continue;
		}

		ptNodeTmp = pInst->m_pcNodeMgr->GetNode(ptVmpRes->m_tVmpStyle.m_atVmpChnl[wIndex].m_wEpID);
		if ( NULL == ptNodeTmp )
		{
			ptVmpRes->m_wMemberNum++;
			continue;
		}

		ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wEpID = ptNodeTmp->m_wEpID;
		ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wScreenIndx = ptVmpRes->m_tVmpStyle.m_atVmpChnl[wIndex].m_wScrIndx;

		if( ptNodeTmp->IsChanOn() && ptNodeTmp->IsVidSndValid() )
		{
			ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wStaticPayload = ptNodeTmp->m_tVidSndFormat.m_wStaticPayload;
			ptVmpRes->m_atMember[ptVmpRes->m_wMemberNum].m_tVmpMember.m_wDynamicPayload = ptNodeTmp->m_tVidSndFormat.m_wDynamicPayload;
		}
		ptVmpRes->m_wMemberNum ++;
	}

	u16 wMiniMem = localmin(ptVmpRes->m_wMemberNum, TP_VMP_MAX_IN_CHN_NUM);
	for(u16 wIndexct = 0; wIndexct < wMiniMem; wIndexct++)
	{
		ptVmpRes->m_atMember[wIndexct].m_tVmpMember.m_tEncrypt = tEncrypt;
	}

	//�����������ˡ�˫������
	AdjustSpeakerFollow(ptVmpRes);

	//������Ա����
	AdjustBrdXmpuVmpMember(ptVmpRes);

	ChangeBrdXmpuVmpParam(ptVmpRes);

	// ������ת������ʵ�ʽ���
	if (ptVmpRes->m_bOnLine)
	{
		CNetPortMgr::AdjustXmpuMiddleAddrToVmp(Inst(), ptVmpRes);
	}
	//��������
	CNetPortMgr::CreateAllMemberToBrdVmp(Inst(), ptVmpRes);

}

void CUmsVmp::AdjustBrdXmpuVmpMember( TBrdVmpRes* ptVmpRes )
{
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdXmpuVmpMember. ConfID:%d, EqpID:%d\n", Inst()->GetInsID(), ptVmpRes->m_tEqpInfo.m_byEqpID));

	//���Vip
	ptVmpRes->m_wCurVipNum = 0;

	CalcXmpuVmpVipNum(ptVmpRes);

	TBrdVmpMember* ptMember = NULL;
	TVmpMemberPool tVmpMemberPool;  // �洢�Ѿ�ռ����vip��member

	TCallNode* ptNodeTmp = NULL;

	BOOL32	bAdjRes = TRUE;

	TCallVidFormat tVidFmt;
	EmGetVidRes emRes;
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex ++ )
	{// 
		ptMember = &ptVmpRes->m_atMember[wIndex];
		if ( !TP_VALID_HANDLE(ptMember->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		ptMember->m_emRes = CTpTypeAdpt::GetVmpMemberResByChnlIndx(ptVmpRes->m_tVmpStyle.m_emVmpStyle, wIndex);

		// ���vip�����Ϣ
		ptMember->ClearVip();
		ptMember->ClearDs();
		ptMember->ClearSmallVid();
		ptMember->ClearAdjustRes();

		ptNodeTmp = Inst()->m_pcNodeMgr->GetNode(ptMember->m_tVmpMember.m_wEpID);
		if ( NULL == ptNodeTmp || !ptNodeTmp->IsChanOn() || !ptNodeTmp->IsVidSndValid() )
		{
			continue;
		}

		if ( !ptVmpRes->m_bNeedAdjVip )
		{
			ptMember->SetVip();
			ptMember->SetDs();
		}
		else
		{
			if ( wIndex == 0 )
			{//0ͨ��������� Ĭ��VIP��ֱ�ӽ��ϳɣ��Ҳ�ռ��VIP��Դ
				ptMember->SetVip();
				ptMember->SetDs();
			}
			else
			{
				AdjustVipForMember(ptVmpRes, ptMember, &tVmpMemberPool);
			}
		}
	}

	BOOL32 bAdjustRet;
	for ( wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex ++ )
	{
		ptMember = &ptVmpRes->m_atMember[wIndex];

		if ( !TP_VALID_HANDLE(ptMember->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		ptMember->ClearGetVid(); // ��������������Ҳ��գ���Ӱ���ͷţ���Ϊǰ���Ѿ�����

		if (ptMember->m_tVmpMember.IsDual())
		{
			continue;
		}

		// �������ݶԱ�
		bAdjustRet = AdjustMemberResByOld(ptMember);

		if (!ptMember->IsVip() && ptMember->IsAdjustRes() && bAdjustRet && emTPVResEnd != ptMember->m_emRes)
		{// ���ֱ��ʽ��ϳ�
			Inst()->GetNodeMgr()->AdjustNodeRes( ptMember->m_tVmpMember.m_wEpID, 
				ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_emRes);
		}
	}

	//�ͷű������ݣ���������AdjustMemberResByOld�Ĵ��������������Ѿ�ֻʣ����Ҫ�ͷŵ���
	ReleaseBrdVmpParam(&m_tBrdVmpOld);
	//�����������
	BackupBrdVmpParam(NULL);

	// ѭ��һ�������������Ҫ���������Ĳŵ���
	for ( wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex ++ )
	{
		ptMember = &ptVmpRes->m_atMember[wIndex];		
		if ( !TP_VALID_HANDLE(ptMember->m_tVmpMember.m_wEpID) )
		{
			continue;
		}

		if (ptMember->m_tVmpMember.IsDual())
		{// ˫������������
			MdlLowHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdVmpMember. This Chan is Dual. Index:%d, EpId:%d, Vip:%d, Ds:%d.\n", wIndex, 
				ptMember->m_tVmpMember.m_wEpID, ptMember->IsVip(), ptMember->IsDs()));
			continue;
		}

		if (!ptMember->IsDs())
		{// ������������ͨ����Ҳ����������
			MdlLowHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdVmpMember. This Chan is no Ds. Index:%d, EpId:%d, Screen:%d, Stat:%d.\n", wIndex, 
				ptMember->m_tVmpMember.m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_tVmpMember.m_byStat));
			continue;
		}

		if (ptMember->IsVidGet())
		{// �Ѿ����ȹ������ģ����ظ�����
			MdlLowHint(Ums_Mdl_Call, ("CUmsVmp::AdjustBrdVmpMember. This Chan is Get Vid. Index:%d, EpId:%d, Screen:%d.\n", wIndex, 
				ptMember->m_tVmpMember.m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx));
			continue;
		}

		ptNodeTmp = Inst()->m_pcNodeMgr->GetNode(ptMember->m_tVmpMember.m_wEpID);
		if ( NULL == ptNodeTmp || !ptNodeTmp->IsChanOn() || !ptNodeTmp->IsVidSndValid() )
		{
			continue;
		}

		// ������������
		emRes = CUmsConfInst::GetVidAudEx()->AssignByScreen(Inst(), ptNodeTmp->m_wEpID, ptMember->m_tVmpMember.m_wScreenIndx, 
			em_GetVid_Vmp, tVidFmt, ptNodeTmp->IsSmallVidSnd(), ptMember->m_tGetAddr, ptMember->m_wGetIndex);
		if ( em_GetVid_Success != emRes )
		{
			// ��ʾ���棬��������ʧ�ܣ�����ϳ�ͨ��ʧ��
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_VMP_GetVidFail, Inst()->chairID(), (u32)ptMember->m_tVmpMember.m_wEpID,
				(u32)ptVmpRes->m_tEqpInfo.m_byEqpID);

			if (ptMember->IsAdjustRes() && emTPVResEnd != ptMember->m_emRes)
			{
				//������ʧ���ˣ��ָ��ն˷ֱ���
				Inst()->GetNodeMgr()->AdjustNodeRes( ptMember->m_tVmpMember.m_wEpID, 
					ptMember->m_tVmpMember.m_wScreenIndx, ptMember->m_emRes, TRUE);
				ptMember->m_emRes = emTPVResEnd;
			}
			continue;
		}
	}	

	return ;
}

void CUmsVmp::ChangeBrdXmpuVmpParam( TBrdVmpRes* ptVmpRes )
{
	if (!ptVmpRes->m_bOnLine)
	{
		return;
	}

	// �����ϳ�
	TTVmpStartParam tVmpParam;
	tVmpParam.m_emVmpStyle = ptVmpRes->m_tVmpStyle.m_emVmpStyle;
	tVmpParam.m_byVMPMemberNum = (u8)ptVmpRes->m_wMemberNum;
	for (u16 wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex++)
	{
		tVmpParam.m_atVMPMember[wIndex] = ptVmpRes->m_atMember[wIndex].m_tVmpMember;
	}
	u32 dwEqpID = ptVmpRes->m_tEqpRes.m_byEqpID;
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_ChangeVmp_Req);
	cMsg.SetBody(&dwEqpID, sizeof(u32));
	cMsg.CatBody(&tVmpParam, sizeof(TTVmpStartParam));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

}

u16 CUmsVmp::CalcXmpuVipNum( TBrdVmpRes* ptVmpRes )
{
	u16 wMaxMemberNum = CTpTypeAdpt::GetVmpMemberNumByStyle(ptVmpRes->m_tVmpStyle.m_emVmpStyle);
	u16 wVipNum = 0;
	if ( wMaxMemberNum <=  ptVmpRes->m_byVipMaxStyle )
	{
		wVipNum = ptVmpRes->m_byVipMaxStyle;
	}
	else
	{
		wVipNum = ptVmpRes->m_byVipNum;
	}
	return wVipNum;
}

void CUmsVmp::CalcXmpuVmpVipNum( TBrdVmpRes* ptVmpRes )
{
	// �����������ͺͺϳɷ�����VipNum
	ptVmpRes->m_wVipNum = CalcXmpuVipNum(ptVmpRes);

	if(ptVmpRes->m_wMemberNum <= ptVmpRes->m_wVipNum )
	{//��Ա��С��vip����������Ҫ��vipУ�� ֱ�ӽ�����
		ptVmpRes->m_bNeedAdjVip = FALSE;
	}
	else
	{
		ptVmpRes->m_bNeedAdjVip = TRUE;
	}

	return;
}

void CUmsVmp::UpdateXmpuUIVmp()
{
	TXmpuVmpManger* ptManger = &CUmsConfInst::m_tXmpuVmpManger;

	for (u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; ++wIndex)
	{
		if ((ptManger->m_adwVmpID[wIndex] == 0) || (ptManger->m_aemStat[wIndex]  != VmpManger_Normal))
		{
			continue;
		}
		TBrdVmpRes* ptVmp  = FindBrdVmpByEqp(ptManger->m_adwVmpID[wIndex]);
		if(NULL == ptVmp)
		{
			ptVmp = FindIdleBrdVmp();
			if (NULL == ptVmp)
			{
				MdlError(Ums_Mdl_Call, ("CUmsVmp::UpdateXmpuUIVmp. ptVmp is NULL, no idle. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
				return;
			}

			MdlHint(Ums_Mdl_Call, ("CUmsVmp::UpdateXmpuUIVmp. wIndex:%d, EqpID%d\n", wIndex, ptManger->m_adwVmpID[wIndex]));
			ptVmp->m_tEqpInfo.m_byEqpID = ptManger->m_adwVmpID[wIndex];
			ptVmp->m_tEqpInfo.m_emEqpType = em_vmp_mdl;
			ptVmp->m_emStat = EmBrdVmpStat_Idle;
			ptVmp->m_tEqpRes.m_byEqpID = ptManger->m_adwVmpID[wIndex];
			strncpy(ptVmp->m_tEqpInfo.m_szEqpAlias,ptManger->m_aachEqpAlias[wIndex], TP_MAXLEN_EQP_ALIAS);
			ptVmp->m_tEqpInfo.m_szEqpAlias[TP_MAXLEN_EQP_ALIAS - 1] = '\0';
			NotifyBrdVmpToAllConf(ptVmp, tp_OprType_Add);
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("CEqpService::UpdateXmpuUIVmp. ptVmp is already exist. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
		}

	}	
	return ;
}

void CUmsVmp::DisConnectXmpuVmp(u32	dwEqpID)
{
	MdlHint(Ums_Mdl_Call, ("CUmsVmp::DisConnectXmpuVmp. Disconnect EqpID:%d\n",dwEqpID));
	TXmpuVmpManger* ptManger = &CUmsConfInst::m_tXmpuVmpManger;
	for (u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; ++wIndex)
	{
		if ((ptManger->m_aemStat[wIndex]  != VmpManger_Normal) && (ptManger->m_aemStat[wIndex] != VmpManger_Vmp))
		{
			continue ;
		}
		// ���Ҷ���VMP
		if (ptManger->m_adwVmpID[wIndex] == dwEqpID)
		{
			TBrdVmpRes* ptVmp  = FindBrdVmpByEqp(dwEqpID);
			if ( NULL != ptVmp )
			{
				// vmp ����
				if (ptManger->m_aemStat[wIndex] == VmpManger_Vmp ||
					((ptManger->m_aemStat[wIndex] == VmpManger_Normal)&& ptVmp->IsStatNormal()))
				{
					MdlHint(Ums_Mdl_Call, ("CUmsVmp::DisConnectXmpuVmp. Disconnect EqpID:%d,  state:%d\n", ptManger->m_adwVmpID[wIndex], ptManger->m_aemStat[wIndex]));
					// ����֪ͨ���еĻ���
					for (u16 wConfIndex = 1; wConfIndex <= TP_UMS_MAX_CONFNUM; ++wConfIndex)
					{
						CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfIndex));
						if (pInst->CurState() == CUmsConfInst::inst_idle)
						{
							continue;
						}
						pInst->GetVmp()->OnXmpuVmpDisConnect(ptManger->m_adwVmpID[wIndex]);
					}
				}
				break;			
			}
			else
			{
				MdlHint(Ums_Mdl_Call, ("CUmsVmp::DisConnectXmpuVmp. ptVmp is already exit. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
			}
		}
	
		continue;
	}
	return;

}

void CUmsVmp::RefreashXmpuUIVmp(u16 wVmpNum)
{	
	u16 wVmpIdleNum = CountIdleVmpNum();
	MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::RefreashXmpuUIVmp. Vmp Number:%d, Idle Number:%d\n",wVmpNum,wVmpIdleNum ));
	if (wVmpNum == wVmpIdleNum)
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsVmp::RefreashXmpuUIVmp. Vmp Number not Decrease\n"));
		return;
	}
	else if (wVmpNum < wVmpIdleNum) //����
	{
		u16 wNum = wVmpIdleNum - wVmpNum;
		for (s16 swIndex = XMPU_MAX_VMP_NUM-1; swIndex >= 0; swIndex-- )
		{
			if ((EmBrdVmpStat_Idle ==  m_atBrdVmp[swIndex].m_emStat) && (wNum))
			{
				MdlHint(Ums_Mdl_Call, ("CUmsVmp::RefreashXmpuUIVmp. index:%d, Number:%d\n",swIndex,wNum ));
				m_atBrdVmp[swIndex].m_emStat = EmBrdVmpStat_Error;
				NotifyBrdVmpToAllConf(&m_atBrdVmp[swIndex], tp_OprType_Update);
				--wNum;
			}
		}
	}
	else //����
	{
		u16 wNum = wVmpNum - wVmpIdleNum;
		for (u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex++ )
		{
			if ((EmBrdVmpStat_Error ==  m_atBrdVmp[wIndex].m_emStat) && (wNum))
			{				
				MdlHint(Ums_Mdl_Call, ("CUmsVmp::RefreashXmpuUIVmp. index:%d, Number:%d\n",wIndex,wNum ));
				m_atBrdVmp[wIndex].m_emStat = EmBrdVmpStat_Idle;
				NotifyBrdVmpToAllConf(&m_atBrdVmp[wIndex], tp_OprType_Update);
				--wNum;
			}
		}

	}
	return;
}

u16 CUmsVmp::CountIdleVmpNum()
{
	u16 wCount = 0;
	for ( u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex ++ )
	{
		if ((EmBrdVmpStat_Idle ==  m_atBrdVmp[wIndex].m_emStat))
		{
			++wCount;
		}
	}
	return wCount;
}