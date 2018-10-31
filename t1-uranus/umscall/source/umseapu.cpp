#include "umseapu.h"
#include "umsconfinst.h"
#include "callnodemgr.h"
#include "umsstackinterface.h"
#include "eventoutumscall.h"
#include "eventoutsipadapter.h"
#include "innereventumsconf.h"
#include "umsapi.h"
#include "eqpinterface.h"
#include "umsnetportmgr.h"
#include "innereventumscall.h"
#include "umsconfigex.h"
#include "callmgr.h"
#include "tperrno.h"
#include "innereventumsaudiomix.h"
#include "dualmgr.h"
#include "innereventumsmpu2.h"
#include "umsxmpinterface.h"
#include "innereventxmpumix.h"

CUmsEapu::CUmsEapu(CUmsConfInst* pcInst)
:CTpHandler(pcInst)
{
	
	EapuClear();
}


CUmsEapu::~CUmsEapu()
{

}

//rtp 外设接收地址 rtcp为混音器过来的rtcp
void CUmsEapu::GetMixerChnInAddr(TAudMixInfo* ptInfo, TTPMediaTransAddr& tAddr, u16 wEpID, u16 wScrIndx)
{
	CUmsConfInst* pInst = Inst();
	tAddr.Clear();

	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnInAddr. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
#ifdef _USE_XMPUEQP_
	if (!ptInfo->m_tEqpRes.m_byEqpID)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnOutAddr. ptInfo is Invalid! ConfID:%d, dwEqpID:%d\n", pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}
#else
	if ( !ptInfo->m_tEqpRes.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnOutAddr. ptInfo is Invalid! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
#endif

	u16 wChnlIndx = ptInfo->GetIndx(wEpID, wScrIndx);

	if (TP_INVALID_INDEX == wChnlIndx)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnInAddr. wChnlIndex Invalid! ConfID:%d\n", pInst->GetInsID()));
		return;
	}
	tAddr.m_tRtpAddr = ptInfo->m_atChnl[wChnlIndx].m_tMixAddr.m_tRtpAddr;
	tAddr.m_tBackRtcpAddr = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr->m_tBackRtcpAddr;

	return ;
}

//rtp UMS接收地址 rtcp为混音器接收
void CUmsEapu::GetMixerChnOutAddr(TAudMixInfo* ptInfo, TServiceAddr& tAddr, u16 wEpID, u16 wScrIndx)
{
	CUmsConfInst* pInst = Inst();
	tAddr.Clear();
	
	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnOutAddr. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

#ifdef _USE_XMPUEQP_
	if (!ptInfo->m_tEqpRes.m_byEqpID)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnOutAddr. ptInfo is Invalid! ConfID:%d, dwEqpID:%d\n", pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}
#else
	if ( !ptInfo->m_tEqpRes.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnOutAddr. ptInfo is Invalid! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
#endif
	
	
	u16 wChnlIndx = ptInfo->GetIndx(wEpID, wScrIndx);
	
	if (TP_INVALID_INDEX == wChnlIndx)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnOutAddr. wChnlIndex Invalid! ConfID:%d\n", pInst->GetInsID()));
		return;
	}

	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEpID);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	
	if (NULL == ptNode || NULL == ptFatherNode || !ptFatherNode->IsChanOn())
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetMixerChnOutAddr. ptNode or ptFatherNode is Invalid! ConfID:%d\n", pInst->GetInsID()));
	}

	tAddr.m_tAddr.m_tRtpAddr = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr->m_tRtpAddr;
	tAddr.m_tAddr.m_tBackRtcpAddr = ptInfo->m_atChnl[wChnlIndx].m_tMixAddr.m_tBackRtcpAddr;
	tAddr.m_dwMediaNode = ptFatherNode->m_tMediaEqp.m_dwEqpNode;
	
	return ;
}

void CUmsEapu::EapuClear()
{
	
}

void CUmsEapu::Show()
{
	CUmsConfInst* pInst = Inst();

	msgprintnotime("-----------------Apu2Beg---------------, ConfID:%d\n\n", pInst->GetInsID());

	TTPMediaTransAddr* ptMediaAddr = NULL;
	TAudMixInfo* ptInfo = NULL;
	u16 wChnIndx = 0;
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( !m_atAudMix[wIndex].m_tEqpRes.m_byEqpID )
		{
			continue;
		}

		ptInfo = &m_atAudMix[wIndex];

		msgprintnotime("Apu2(%d): \n", wIndex);

#ifdef _USE_XMPUEQP_
		msgprintnotime("EqpID:%d, ChanNum:%d, UsedChanNum:%d, bVacOn:%d, bForceActiveChan:%d, bSyncChnl:%d, bDelChnlId:%d.\n\n",
			ptInfo->m_tEqpRes.m_byEqpID,
			ptInfo->m_tEqpRes.m_wChanNum, ptInfo->m_wUsdChnNum, ptInfo->m_bMixMotive, 
			ptInfo->m_byForceActiveChan, ptInfo->m_bySyncChnl,
			ptInfo->m_byDelChnld);

		for( wChnIndx = 0; wChnIndx < pInst->m_tConfBaseInfo.m_wAudFmtNum; wChnIndx++ )
		{
			if (wChnIndx >= UMS_AUDMIX_N_OUT_NUM || !ptInfo->m_atNEncRtpAddr[wChnIndx].GetPort() )
			{
                continue;
			}
			
			msgprintnotime("  Out(N) Chn%d: AudFmt:%s, EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n", 
				wChnIndx,  UmsAudFormatPrint(pInst->m_tConfBaseInfo.m_atAudFmt[wChnIndx].m_emFormat),
				Tpu32ToIP(ptInfo->m_atNEncRtpAddr[wChnIndx].GetIP()), ptInfo->m_atNEncRtpAddr[wChnIndx].GetPort(), 
				Tpu32ToIP(ptInfo->m_atNEncMiddleRtcpAddr[wChnIndx].GetIP()), ptInfo->m_atNEncMiddleRtcpAddr[wChnIndx].GetPort(), 
				Tpu32ToIP(ptInfo->m_atNEncRtcpAddr[wChnIndx].GetIP()), ptInfo->m_atNEncRtcpAddr[wChnIndx].GetPort());
		}

        for( wChnIndx = 0; wChnIndx < TP_APU2_MAX_CHAN_NUM; wChnIndx++ )
		{
			if ( !ptInfo->m_atChnl[wChnIndx].IsExist() )
			{
				continue;
			}

			if(!ptInfo->m_atChnl[wChnIndx].m_ptMixChnAddr)
			{
                continue;
			}

			msgprintnotime(" ChnIndx:%d, EpID:%d, ScrIndx:%d\n", wChnIndx, ptInfo->m_atChnl[wChnIndx].m_wEpID, ptInfo->m_atChnl[wChnIndx].m_wScrIndx);
			msgprintnotime("    In DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",  
				Tpu32ToIP(ptInfo->m_atChnl[wChnIndx].m_tMixAddr.m_tRtpAddr.GetIP()), ptInfo->m_atChnl[wChnIndx].m_tMixAddr.m_tRtpAddr.GetPort(), 
				Tpu32ToIP(ptInfo->m_atChnl[wChnIndx].m_ptMixChnAddr->m_tBackRtcpAddr.GetIP()), ptInfo->m_atChnl[wChnIndx].m_ptMixChnAddr->m_tBackRtcpAddr.GetPort(), 
				Tpu32ToIP(ptInfo->m_atN1DecRtpAddr[wChnIndx].GetIP()), ptInfo->m_atN1DecRtpAddr[wChnIndx].GetPort());
			
			msgprintnotime("    Out(N-1) EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n", 
				Tpu32ToIP(ptInfo->m_atChnl[wChnIndx].m_ptMixChnAddr->m_tRtpAddr.GetIP()), ptInfo->m_atChnl[wChnIndx].m_ptMixChnAddr->m_tRtpAddr.GetPort(), 
				Tpu32ToIP(ptInfo->m_atChnl[wChnIndx].m_tMixAddr.m_tBackRtcpAddr.GetIP()), ptInfo->m_atChnl[wChnIndx].m_tMixAddr.m_tBackRtcpAddr.GetPort(), 
				Tpu32ToIP(ptInfo->m_atN1EncRtcpAddr[wChnIndx].GetIP()), ptInfo->m_atN1EncRtcpAddr[wChnIndx].GetPort());
			
		}

		msgprintnotime("\n");

#else
		msgprintnotime("EqpID:%d, IP:"TPIPFORMAT", ChanNum:%d, UsedChanNum:%d, EqpRtpStartPort:%d, EqpRtcpstartPort:%d, bVacOn:%d, bForceActiveChan:%d, bSyncChnl:%d, bDelChnlId:%d.\n\n",
			ptInfo->m_tEqpRes.m_byEqpID, Tpu32ToIP(ptInfo->m_tEqpRes.m_dwEqpIp), 
			ptInfo->m_tEqpRes.m_wChanNum, ptInfo->m_wUsdChnNum,  
			ptInfo->m_tEqpRes.m_wEqpStartPort, ptInfo->m_tEqpRes.m_wEqpRtcpStartPort, ptInfo->m_bMixMotive, 
			ptInfo->m_byForceActiveChan, ptInfo->m_bySyncChnl,
			ptInfo->m_byDelChnld);

		TServiceAddr tAddr;
		msgprintnotime("N Mode AudMix--> AudFmtNum:%d", pInst->m_tConfBaseInfo.m_wAudFmtNum);
		for ( wChnIndx = 0; wChnIndx < pInst->m_tConfBaseInfo.m_wAudFmtNum; wChnIndx ++ )
		{
			GetNModeAudRcvAddr(ptInfo, tAddr, pInst->m_tConfBaseInfo.m_atAudFmt[wChnIndx]);
			msgprintnotime("	AudFmt:%s, UmsRcv: Rtp:"ADDRPORT_FORMAT",Rtcp:"ADDRPORT_FORMAT"\n", 
							UmsAudFormatPrint(pInst->m_tConfBaseInfo.m_atAudFmt[wChnIndx].m_emFormat),
							ADDRNET(tAddr.m_tAddr.m_tRtpAddr), ADDRNET(tAddr.m_tAddr.m_tBackRtcpAddr));
		}

		msgprintnotime("\n");
		for ( wChnIndx = 0; wChnIndx < TP_APU2_MAX_CHAN_NUM; wChnIndx ++ )
		{
			if ( !ptInfo->m_atChnl[wChnIndx].IsExist() )
			{
				continue;
			}
			
			msgprintnotime(" ChnIndx:%d, EpID:%d, ScrIndx:%d\n", wChnIndx, ptInfo->m_atChnl[wChnIndx].m_wEpID, ptInfo->m_atChnl[wChnIndx].m_wScrIndx);

			ptMediaAddr = ptInfo->m_atChnl[wChnIndx].m_ptMixChnAddr;
			if( ptMediaAddr )
			{
				msgprintnotime("  UMSRcv(MixOut N-1) MixRtp:"ADDRPORT_FORMAT" SndChnlBackRtcp:"ADDRPORT_FORMAT"\n", 
					ADDRNET(ptMediaAddr->m_tRtpAddr), ADDRNET(ptMediaAddr->m_tBackRtcpAddr));
			}

			ptMediaAddr = &ptInfo->m_atChnl[wChnIndx].m_tMixAddr;
			msgprintnotime("  MixerRcv RcvChnlRtp:"ADDRPORT_FORMAT" SndChnlBackRtcp(N-1):"ADDRPORT_FORMAT"\n", 
				ADDRNET(ptMediaAddr->m_tRtpAddr), ADDRNET(ptMediaAddr->m_tBackRtcpAddr));
		}
#endif

	}

	msgprintnotime("\n\n-----------------Apu2end---------------, ConfID:%d\n\n", pInst->GetInsID());

	return ;
}

BOOL32 CUmsEapu::HandlerFromStack( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	switch (ptMsg->GetEvent())
	{
	case evtp_UmsCnsSpeakerIndxAdjust_Notify:
		pInst->OnAdjustCnsSpeakerIndx(ptMsg);
		break;
	case ev_UmsAudMixStatus_Nty:
		pInst->OnBrdCastMsg(ptMsg);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL32 CUmsEapu::Handler( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case ev_mixer_start_mix_nack:
		OnStartMixNAck(ptMsg);
		break;
	case ev_mixer_add_mixmember_nack:
		OnAddMemberNAck(ptMsg);
		break;
	case ev_mixer_vac_result_ntfy:
		OnAudMixExciteInd(ptMsg);
		break;
	case evtp_UmsAudioMixUnReg_Notify:
		OnAudMixDisConnect(ptMsg);
		break;
	case evtp_UmsAudioMixReg_Notify:
		OnAudMixConnect(ptMsg);
		break;
	// xmpu event

#ifdef _USE_XMPUEQP_
	case evXmpu_MixDisConnect_Nty:
	case evXmpu_UmsStartMix_Nty:
	case evUms_XmpuAddMixMember_Nty:
	case evXmpu_VacActive_Ntf:
	case evXmpu_MixVoiceDetection_Ntf:
		ProcMixCb(ptMsg);
		break;
#endif

	default:
		return FALSE;
	}
	return TRUE;
}

TAudMixInfo* CUmsEapu::AssignMixer(AudMixerCB pCB, CUmsConfInst* ptUsrParam, u16 wChnlLimit /* = 0 */, u16 wReqNum /* = 1 */, u32 dwNode /* = 0 */)
{
#ifdef _USE_XMPUEQP_
	return AssignXmpuMixer(pCB, ptUsrParam, wChnlLimit);
#endif

	CUmsConfInst* pInst = Inst();

	TAudMixInfo* ptInfo = FindIdle();
	if (  NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AssignMixer. TAudMixInfo is Full! ConfID:%d\n", pInst->GetInsID()));
		return NULL;
	}

	TMixerParam tParam;
	tParam.Init(&ptInfo->m_tEqpRes, pInst->GetInsID(), wChnlLimit, wReqNum, dwNode);
	
	if(!AssignEqpEx(&tParam))
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AssignMixer. AssignApu Fail! ConfID:%d, wChnlLimit:%d\n", pInst->GetInsID(), wChnlLimit));
		ptInfo->Clear();
		return NULL;
	}

	ptInfo->m_pcCB = pCB;
	ptInfo->m_ptUsrParam = ptUsrParam;

	//分配即开启语音激励
	TStartMix tMix;
	tMix.m_byEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	tMix.m_byMixDepth = 8;
	
	tMix.m_byNNum = pInst->m_tConfBaseInfo.m_wAudFmtNum;
	memcpy(tMix.m_atAudFmt, pInst->m_tConfBaseInfo.m_atAudFmt, tMix.m_byNNum*sizeof(TUmsAudFormat));
	
	tMix.m_tEncrypt = pInst->GetConfEncryptInfo();

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_start_mix);
	cMsg.SetBody(&tMix, sizeof(tMix));	
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));

	for (u8 byIndx = 0; byIndx < TP_MAX_OLD_KEY_NUM; byIndx++)
	{
		if (0 == pInst->m_atMediaKey[byIndx].m_dwQtFlag)
		{
			continue;
		}
		
		SetMediaKey(Inst()->m_atMediaKey[byIndx], ptInfo);
	}

	//N模式 要挂载到 会议转发板
	TBasSndAddr tSndAddr;
	tSndAddr.m_byEqpID = tMix.m_byEqpID;
	tSndAddr.m_dwNewDsIP = Inst()->m_tEqpConfDs.m_dwEqpIp;
	
	cMsg.SetEvent(ev_TPEqp_ChangeSndAddr_Req);
	cMsg.SetBody(&tSndAddr, sizeof(tSndAddr));
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	return ptInfo;
}

void CUmsEapu::ReleaseMixer(TAudMixInfo* ptInfo)
{
#ifdef _USE_XMPUEQP_
	ReleaseXmpuMixer(ptInfo);
	return;
#endif
	CUmsConfInst* pInst = Inst();

	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::ReleaseMixer. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	if ( !ptInfo->m_tEqpRes.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::ReleaseMixer. ptInfo is Invalid! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	TMixerParam tParam;
	tParam.Init(&ptInfo->m_tEqpRes, pInst->GetInsID());
	
	if(!ReleaseEqpEx(&tParam))
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::ReleaseMixer. ReleaseApu Fail! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}

	for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex ++ )
	{
		if ( NULL == ptInfo->m_atChnl[wIndex].m_ptMixChnAddr )
		{
			continue;
		}
		CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[wIndex].m_ptMixChnAddr);
	}

	ptInfo->Clear();

	return ;
}

void CUmsEapu::OnAudMixExciteInd( CTpMsg *const ptMsg )
{
	CUmsConfInst*	pInst = Inst();

	TMixVacResInfo tVacResInfo;
	TP_SAFE_CAST( tVacResInfo, ptMsg->GetBody());

	if ( pInst->m_bIsQuiting || CUmsConfInst::inst_idle == pInst->CurState() )
	{//正在退出会议不处理
		return ;
	}

	TAudMixInfo* ptInfo = FindByEqpID(tVacResInfo.m_byEqpId);
	if ( NULL == ptInfo )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::OnAudMixExciteInd. AudMixer no exist! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), tVacResInfo.m_byEqpId));
		return ;
	}

	MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::OnAudMixExciteInd. ConfID:%d, EqpID:%d, VacChanId:%d.(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", 
		pInst->GetInsID(), tVacResInfo.m_byEqpId, tVacResInfo.m_byVacChanId, tVacResInfo.m_abyChanId[0], 
		tVacResInfo.m_abyChanId[1], tVacResInfo.m_abyChanId[2], tVacResInfo.m_abyChanId[3], tVacResInfo.m_abyChanId[4], tVacResInfo.m_abyChanId[5],
		tVacResInfo.m_abyChanId[6], tVacResInfo.m_abyChanId[7], tVacResInfo.m_abyChanId[8], tVacResInfo.m_abyChanId[9]));
	
	if (ptInfo->m_bMixMotive && tVacResInfo.m_byVacChanId < TP_APU2_MAX_CHAN_NUM)
	{// 开启语音激励的混音器，处理语音激励结果
		AudMixExciteSpeakerEp(ptInfo, tVacResInfo.m_byVacChanId);
	}

	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		pInst->GetUmsDiscuss()->UpdateMixDepthChanID(ptInfo, tVacResInfo.m_abyChanId, MAXNUM_MIXER_DEPTH);
	}
	
	return ;
}

void CUmsEapu::OnAudMixDisConnect( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	
	TAudMixInfo* ptInfo = FindByEqpID(byEqpID);
	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::OnAudMixDisConnect. AudMixer no exist! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), byEqpID));
		return ;
	}
	
	MdlHint(Ums_Mdl_Call, ("CUmsEapu::OnAudMixDisConnect disconnect! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), byEqpID));
	
	ptInfo->m_pcCB(TAudMixInfo::EmCBOprType_DisConnect, ptInfo, ptInfo->m_ptUsrParam);
	
	for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex ++ )
	{
		if ( NULL == ptInfo->m_atChnl[wIndex].m_ptMixChnAddr )
		{
			continue;
		}
		CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[wIndex].m_ptMixChnAddr);
	}

	ptInfo->Clear();
	
	return ;
}

void CUmsEapu::OnAudMixConnect( CTpMsg *const ptMsg )
{
	return ;
}

void CUmsEapu::OnAddMemberNAck( CTpMsg *const ptMsg )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());
	
	CUmsConfInst* pInst = Inst();
	
	TAudMixInfo* ptInfo = FindByEqpID(tTpMember.m_byEqpID);
	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::OnAddMemberNAck. AudMixer no exist! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), tTpMember.m_byEqpID));
		return ;
	}
	
	MdlError(Ums_Mdl_Call, ("CUmsEapu::OnAddMemberNAck. wConfID:%d, EqpID:%d, chanIndex:%d\n", pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID, tTpMember.m_byIndex));
	
	ptInfo->m_pcCB(TAudMixInfo::EmCBOprType_AddMemberFail, ptInfo, ptInfo->m_ptUsrParam);
	
	return ;
}

void CUmsEapu::OnStartMixNAck( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	
	CUmsConfInst* pInst = Inst();
	
	TAudMixInfo* ptInfo = FindByEqpID(byEqpID);
	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::OnStartMixNAck. AudMixer no exist! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), byEqpID));
		return ;
	}
	
	MdlError(Ums_Mdl_Call, ("CUmsEapu::OnStartMixNAck. wConfID:%d, EqpID:%d\n", pInst->GetInsID(), byEqpID));
	
	ptInfo->m_pcCB(TAudMixInfo::EmCBOprType_StartFail, ptInfo, ptInfo->m_ptUsrParam);

	return ;
}

void CUmsEapu::AddMember(TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx, u16 wChnlIndx /* = TP_INVALID_INDEX */)
{
#ifdef _USE_XMPUEQP_
	AddXmpuMember(ptInfo, wEpID, wScrIndx, wChnlIndx);
	return;
#endif
	CUmsConfInst* pInst = Inst();
	
	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddMember. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
	if ( !ptInfo->m_tEqpRes.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddMember. ptInfo is Invalid! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	TCallNode* ptNode = Inst()->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFatherNode = Inst()->m_pcNodeMgr->GetForeFatherNode(wEpID);
	if ( NULL == ptNode || NULL == ptFatherNode || !ptNode->IsAudSndValid() || !ptFatherNode->IsAudSndValid())
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddMember. node or fathernode Invalid! ConfID:%d, EpID:%d\n", Inst()->GetInsID(), wEpID));
		return ;
	}

	if (!TP_VALID_HANDLE(wChnlIndx))
	{
		wChnlIndx = ptInfo->AddMember();
		if ( !TP_VALID_HANDLE(wChnlIndx) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsEapu::AddMember. wChnlIndx is Invalid! ConfID:%d, wChnlIndx:%d\n", pInst->GetInsID(), wChnlIndx));
			return ;
		}
	}

	//计算混音器的接收地址 存起来
	//rtcp BRD_APU2_SNDPORT + (m_pcMixerCfg->m_bySndOff + byChnIdx)* PORTSPAN + 2 + 1;
	//rtp  m_pcMixerCfg->wRcvStartPort + byIdleIdx * PORTSPAN + 2;
	ptInfo->m_atChnl[wChnlIndx].m_tMixAddr.m_tRtpAddr.SetAddr(ptInfo->m_tEqpRes.m_dwEqpIp, 
		ptInfo->m_tEqpRes.m_wEqpStartPort + wChnlIndx*UMS_MCU_PORT_PORTSPAN + 2);
	ptInfo->m_atChnl[wChnlIndx].m_tMixAddr.m_tBackRtcpAddr.SetAddr(ptInfo->m_tEqpRes.m_dwEqpIp, 
		ptInfo->m_tEqpRes.m_wEqpRtcpStartPort + wChnlIndx*UMS_MCU_PORT_PORTSPAN + 2 + 1);
	
	CMixerChnAddrListItor pItor = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr;
	if (NULL == pItor)
	{
		pItor = CUmsConfInst::GetEapuAddrList()->AllocNode();
	}

	if ( NULL == pItor )
	{
		ptInfo->DecrementChan();
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddMember. GetMixerChnAddr Fail! ConfID:%d, wChnlIndx:%d\n", pInst->GetInsID(), wChnlIndx));
		return ;
	}
	

	ptInfo->m_atChnl[wChnlIndx].m_wEpID = wEpID;
	ptInfo->m_atChnl[wChnlIndx].m_wScrIndx = wScrIndx;
	ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr = pItor;
	
	BOOL32 bDual = wScrIndx<=TP_MAX_STREAMNUM ? FALSE : TRUE;

	//放在结点所在的转发板
	pItor->SetIP(ptFatherNode->m_tMediaEqp.m_dwEqpIp);

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::AddMember. ConfID:%d, EpID:%d, wScrIndex:%d, EqpID:%d, ChnlIndx:%d, bDual:%d\n", 
										pInst->GetInsID(), wEpID, wScrIndx, ptInfo->m_tEqpRes.m_byEqpID, wChnlIndx, bDual));
	
	TTPMixMember tMember;
	tMember.m_byEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	tMember.m_wEpID = wEpID;

	if( bDual )
	{
		tMember.m_emAudFormat = ptNode->m_tDualAudSndFormat.m_tFormat.m_emFormat;
		tMember.m_emPAChnlCfg = ptNode->m_tDualAudSndFormat.m_tFormat.m_emChnlCfg;
		tMember.m_emPASampleFreq = ptNode->m_tDualAudSndFormat.m_tFormat.m_emSampleFreq;
		tMember.m_wDynamicPayload = ptNode->m_tDualAudSndFormat.m_wDynamicPayload;
		tMember.m_wStaticPayload = ptNode->m_tDualAudSndFormat.m_wStaticPayload;

		tMember.m_emOutAudFormat = tMember.m_emAudFormat;
		tMember.m_emOutPAChnlCfg = tMember.m_emPAChnlCfg;
		tMember.m_emOutPASampleFreq = tMember.m_emPASampleFreq;
		tMember.m_wOutDynamicPayload = tMember.m_wDynamicPayload;
		tMember.m_wOutStaticPayload = tMember.m_wStaticPayload;
	}
	else
	{
		tMember.m_emAudFormat = ptNode->m_tAudSndFormat.m_tFormat.m_emFormat;
		tMember.m_emPAChnlCfg = ptNode->m_tAudSndFormat.m_tFormat.m_emChnlCfg;
		tMember.m_emPASampleFreq = ptNode->m_tAudSndFormat.m_tFormat.m_emSampleFreq;
		tMember.m_wDynamicPayload = ptNode->m_tAudSndFormat.m_wDynamicPayload;
		tMember.m_wStaticPayload = ptNode->m_tAudSndFormat.m_wStaticPayload;

		tMember.m_emOutAudFormat = ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat;
		tMember.m_emOutPAChnlCfg = ptNode->m_tAudRcvFormat.m_tFormat.m_emChnlCfg;
		tMember.m_emOutPASampleFreq = ptNode->m_tAudRcvFormat.m_tFormat.m_emSampleFreq;
		tMember.m_wOutDynamicPayload = ptNode->m_tAudRcvFormat.m_wDynamicPayload;
		tMember.m_wOutStaticPayload = ptNode->m_tAudRcvFormat.m_wStaticPayload;
	}


	tMember.m_tLocalRtpRcv = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr->m_tRtpAddr;
	tMember.m_tLocalRtcpRcv = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr->m_tBackRtcpAddr;
	
	tMember.m_byIndex = wChnlIndx;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_add_mixmember);
	cMsg.SetBody(&tMember, sizeof(tMember));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
	
	return ;
}

void CUmsEapu::DelMember(TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx)
{
#ifdef _USE_XMPUEQP_
	DelXmpuMember(ptInfo, wEpID, wScrIndx);
	return;
#endif
	CUmsConfInst* pInst = Inst();
	
	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::DelMember. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
	if ( !ptInfo->m_tEqpRes.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::DelMember. ptInfo is Invalid! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	u16 wChnlIndx = ptInfo->GetIndx(wEpID, wScrIndx);
	if ( !TP_VALID_HANDLE(wChnlIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::DelMember. wChnlIndx is Invalid! ConfID:%d, wChnlIndx:%d\n", pInst->GetInsID(), wChnlIndx));
		return ;
	}

	TTPMixMember tMember;
	tMember.m_byEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	tMember.m_byIndex = wChnlIndx;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_del_mixmember);
	cMsg.SetBody(&tMember, sizeof(tMember));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));


	if( ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr )
	{
		CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr);
		ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr = NULL;
	}

	ptInfo->DelMember(wEpID, wScrIndx);

	return;
}

void CUmsEapu::GetNModeAudRcvAddr( TAudMixInfo* ptInfo, TServiceAddr& tAddr, TUmsAudFormat& tAudFmt )
{
	tAddr.Clear();

	if ( NULL == ptInfo )
	{
		return ;
	}
	
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < TP_CONF_MAX_AUD_FMT_NUM; wIndex ++ )
	{
		if ( Inst()->m_tConfBaseInfo.m_atAudFmt[wIndex].m_emFormat == tAudFmt.m_emFormat )
		{
			break;
		}
	}
	
	if ( wIndex >= TP_CONF_MAX_AUD_FMT_NUM )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::GetNModeAudRcvAddr. AudFmt no Exist! ConfID:%d, AudFmt:%s\n", Inst()->GetInsID(), UmsAudFormatPrint(tAudFmt.m_emFormat)));
		return ;
	}
#ifdef _USE_XMPUEQP_
	//N 模式
	tAddr.m_tAddr.m_tRtpAddr.SetAddr( ptInfo->m_atNEncRtpAddr[wIndex].GetIP(), ptInfo->m_atNEncRtpAddr[wIndex].GetPort());
	tAddr.m_tAddr.m_tBackRtcpAddr.SetAddr(ptInfo->m_atNEncMiddleRtcpAddr[wIndex].GetIP(), ptInfo->m_atNEncMiddleRtcpAddr[wIndex].GetPort());
	tAddr.m_dwMediaNode = Inst()->GetConfEqpDs().m_dwEqpNode;

#else
	//N 模式依次推移
	tAddr.m_tAddr.m_tRtpAddr.SetAddr( Inst()->GetConfEqpDs().m_dwEqpIp, ptInfo->m_tEqpRes.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2);
	tAddr.m_tAddr.m_tBackRtcpAddr.SetAddr(ptInfo->m_tEqpRes.m_dwEqpIp, 
		ptInfo->m_tEqpRes.m_wEqpRtcpStartPort + (ptInfo->m_tEqpRes.m_wChanNum + wIndex)*UMS_MCU_PORT_PORTSPAN + 2 + 1);
	tAddr.m_dwMediaNode = Inst()->GetConfEqpDs().m_dwEqpNode;

#endif
	
	return ;
}

TAudMixInfo* CUmsEapu::FindByEqpID( u16 wEqpID )
{
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( m_atAudMix[wIndex].m_tEqpRes.m_byEqpID == wEqpID )
		{
			return &m_atAudMix[wIndex];
		}
	}
	return NULL;
}
#ifdef _USE_XMPUEQP_
TAudMixInfo* CUmsEapu::FindIdle()
{
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( m_atAudMix[wIndex].m_tEqpRes.m_byEqpID == 0 )
		{
			return &m_atAudMix[wIndex];
		}
	}
	return NULL;
}
#else
TAudMixInfo* CUmsEapu::FindIdle()
{
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( !m_atAudMix[wIndex].m_tEqpRes.IsValid() )
		{
			return &m_atAudMix[wIndex];
		}
	}
	return NULL;
}
#endif

void CUmsEapu::StartVac( TAudMixInfo* ptInfo )
{
#ifdef _USE_XMPUEQP_
	OnXmpuStartVacReq(ptInfo);
	return;
#endif
	CUmsConfInst* pInst = Inst();
	TStartMix tMix;
	tMix.m_byEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	tMix.m_byMixDepth = 8;
	
	tMix.m_byNNum = pInst->m_tConfBaseInfo.m_wAudFmtNum;
	memcpy(tMix.m_atAudFmt, pInst->m_tConfBaseInfo.m_atAudFmt, tMix.m_byNNum*sizeof(TUmsAudFormat));
	
	ptInfo->m_bMixMotive = TRUE;
	
	CTpMsg cMsg;
	
	if (ptInfo->IsForceActive())
	{
		ptInfo->ClearForceActve();
		cMsg.SetEvent(ev_mixer_CancelForceActive_Cmd);
		cMsg.SetBody(&ptInfo->m_tEqpRes.m_byEqpID, sizeof(u8));
		cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
	}

	cMsg.SetBody(&tMix, sizeof(tMix));
	cMsg.SetEvent(ev_mixer_start_vac);
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
	
	//语音激励敏感度范围1-255秒，默认4秒
	s32 dwVal = CUmsConfigEx::GetInstance()->GetMixProtectedTime();
	
	cMsg.SetEvent(ev_mixer_set_vac_keeptime);
	cMsg.SetBody(&ptInfo->m_tEqpRes.m_byEqpID, sizeof(u8));
	cMsg.CatBody(&dwVal, sizeof(u32));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
}

void CUmsEapu::StopVac( TAudMixInfo* ptInfo )
{
#ifdef _USE_XMPUEQP_
	OnXmpuStopVac(ptInfo);
	return;
#endif
	CUmsConfInst* pInst = Inst();

	u8 byEqpId = ptInfo->m_tEqpRes.m_byEqpID;

	ptInfo->m_bMixMotive = FALSE;

	CTpMsg cMsg;
	cMsg.SetBody(&byEqpId, sizeof(u8));
	cMsg.SetEvent(ev_mixer_stop_vac);
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
}

void CUmsEapu::AdjustAudMixMember(TAudMixInfo* ptMixRes, TAudMixMemberInfo* ptMixNewMember, u16 wSyncEp /* = TP_INVALID_INDEX */, u16 wScreeIndex /* = TP_INVALID_INDEX */)
{
	if (NULL == ptMixRes || NULL == ptMixNewMember)
	{
		return;
	} 

	u16 wIndex = 0;
	u16 wOprEp = 0;
	u16 wScrIndex = 0;


	MdlHint(Ums_Mdl_Call, ("AdjustAudMixMember Before! EqpId:%d, SyncChnl:%d, DelChnl:%d.\n", ptMixRes->m_tEqpRes.m_byEqpID,
		ptMixRes->m_bySyncChnl, ptMixRes->m_byDelChnld));
	for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (ptMixRes->m_atChnl[wIndex].IsExist())
		{
			MdlHint(Ums_Mdl_Call, ("  [%d] old Member:(%d,%d)\n", wIndex, ptMixRes->m_atChnl[wIndex].m_wEpID, 
				ptMixRes->m_atChnl[wIndex].m_wScrIndx));
		}
	}
	MdlHint(Ums_Mdl_Call, ("\n"));
	for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 != ptMixNewMember->m_awEpId[wIndex])
		{
			MdlHint(Ums_Mdl_Call, ("  [%d] Adjust Member:(%d,%d)\n", wIndex, ptMixNewMember->m_awEpId[wIndex], 
				ptMixNewMember->m_awScrIndx[wIndex]));
		}
	}

	// 一个混音器通道中，最多只有一个三屏会场的某屏
	if (TP_VALID_HANDLE(wSyncEp) && wScreeIndex < TP_MAX_STREAMNUM)
	{// 新目标有同步
		if (ptMixRes->IsSyncChnl() && !TP_VALID_HANDLE(ptMixRes->GetIndx(wSyncEp, wScreeIndex)))
		{// 新老同步不一样
			if (ptMixRes->IsSyncChnl())
			{
				AddMember(ptMixRes, wSyncEp, wScreeIndex, ptMixRes->m_bySyncChnl);
			}
		}
	}
	else if (wScreeIndex < TP_MAX_STREAMNUM)
	{// 新目标没有同步
		if (ptMixRes->IsSyncChnl())
		{
			// 老的有同步，则这个通道最后肯定会删除，需要设置完sync之后发delmeber
			// 把通道保存下来，通道成员信息先删除
			ptMixRes->m_byDelChnld = ptMixRes->m_bySyncChnl;
			ptMixRes->DelMember(ptMixRes->m_byDelChnld); //
		}
	}
	else
	{
	}

	for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{// 遍历混音器中老成员，如果不属于新的成员，则删除
		if (ptMixRes->m_atChnl[wIndex].IsExist())
		{
			wOprEp = ptMixRes->m_atChnl[wIndex].m_wEpID;
			wScrIndex = ptMixRes->m_atChnl[wIndex].m_wScrIndx;
			if (!ptMixNewMember->IsMixMember(wOprEp, wScrIndex))
			{
				DelMember(ptMixRes, wOprEp, wScrIndex);
			}
		}
	}
	
	for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{// 遍历新成员，如果不在混音器中，则添加
		wOprEp = ptMixNewMember->m_awEpId[wIndex];
		wScrIndex = ptMixNewMember->m_awScrIndx[wIndex];
		if (0 == wOprEp)
		{
			continue;
		}
		
		if (!TP_VALID_HANDLE(ptMixRes->GetIndx(wOprEp, wScrIndex)))
		{
			AddMember(ptMixRes, wOprEp, wScrIndex);
		}
	}

	
	MdlHint(Ums_Mdl_Call, ("AdjustAudMixMember After! EqpId:%d, SyncChnl:%d, DelChnl:%d.\n", ptMixRes->m_tEqpRes.m_byEqpID,
		ptMixRes->m_bySyncChnl, ptMixRes->m_byDelChnld));

	for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (ptMixRes->m_atChnl[wIndex].IsExist())
		{
			MdlHint(Ums_Mdl_Call, ("  [%d] New Member:(%d,%d)\n", wIndex, ptMixRes->m_atChnl[wIndex].m_wEpID, 
				ptMixRes->m_atChnl[wIndex].m_wScrIndx));
		}
	}
	
	return;
}

void CUmsEapu::AdjustForceActive(TAudMixInfo* ptInfo, u16 wForceActiveEpID)
{
#ifdef _USE_XMPUEQP_
	AdjustXmpuForceActive(ptInfo, wForceActiveEpID);
	return;
#endif
	CUmsConfInst* pInst = Inst();
	
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AdjustForceActive. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
	if ( !ptInfo->m_tEqpRes.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AdjustForceActive. ptInfo is Invalid! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	u8 byChanIndex = TP_VALID_HANDLE(wForceActiveEpID) ? ptInfo->GetIndxByEpId(wForceActiveEpID) : TP_APU2_MAX_CHAN_NUM; // 找到需要强制混音的索引;
	
	MdlHint(Ums_Mdl_Call, ("CUmsEapu::AdjustForceActive. ConfID:%d, ForceActiveEpID:%d, EqpID:%d, OldChanIndex:%d, NewChanIndex:%d.\n", 
										pInst->GetInsID(), wForceActiveEpID, ptInfo->m_tEqpRes.m_byEqpID, ptInfo->m_byForceActiveChan,
										byChanIndex));

	CTpMsg cMsg;
	if (byChanIndex < TP_APU2_MAX_CHAN_NUM)
	{// 强制混音
		if ( ptInfo->m_byForceActiveChan != byChanIndex)
		{// 强制混音通道变化了，再发一次
			ptInfo->SetForceActive(byChanIndex);
			
			cMsg.SetEvent(ev_mixer_ForceActive_Cmd);
			cMsg.SetBody(&ptInfo->m_tEqpRes.m_byEqpID, sizeof(u8));
			cMsg.CatBody(&byChanIndex, sizeof(u8));
			cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
		}
	}
	else if (ptInfo->IsForceActive())
	{
		ptInfo->ClearForceActve();

		cMsg.SetEvent(ev_mixer_CancelForceActive_Cmd);
		cMsg.SetBody(&ptInfo->m_tEqpRes.m_byEqpID, sizeof(u8));
		cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
	}
	else
	{
		// 不需要处理
	}

	return ;
}

void CUmsEapu::AudMixExciteSpeakerEp(TAudMixInfo* ptInfo, u8 byChanId)
{
	CUmsConfInst* pInst = Inst();
	
	if (NULL == ptInfo || byChanId >= TP_APU2_MAX_CHAN_NUM || !ptInfo->m_atChnl[byChanId].IsExist())
	{
		MdlHint(Ums_Mdl_Call, ("CUmsEapu::AudMixExciteSpeakerEp. not process! ConfID:%d, byChanId:%d\n", pInst->GetInsID(), byChanId));
		return;
	}
	
	if (ptInfo->m_atChnl[byChanId].m_wScrIndx > TP_MAX_STREAMNUM)
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::AudMixExciteSpeakerEp. AudMixer chanId is Dual, return! ConfID:%d, EqpID:%d, chanIndex:%d, epId:%d, wScrIndex:%d\n", 
			pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID, byChanId, ptInfo->m_atChnl[byChanId].m_wEpID, ptInfo->m_atChnl[byChanId].m_wScrIndx));
		return;
	}
	
	u16 wEpID = ptInfo->m_atChnl[byChanId].m_wEpID;
	
	//当前发言人
	TCallNode* ptOldSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->curSpeakerID());
	if ( NULL == ptOldSpeaker )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AudMixExciteSpeakerEp. ptOldSpeaker is NULL. ConfID:%d, wEpID:%d\n", pInst->GetInsID(), wEpID));
		return ;
	}
	
	//和当前相同 不处理
	if( pInst->curSpeakerID() == wEpID)
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::AudMixExciteSpeakerEp. ep not change! ConfID:%d, New wEpID:%d, OldSpeaker:%d.\n", 
			pInst->GetInsID(), wEpID, pInst->curSpeakerID()));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::AudMixExciteSpeakerEp. ConfID:%d, New wEpID:%d, OldSpeaker:%d.\n", 
			pInst->GetInsID(), wEpID, pInst->curSpeakerID()));

	TCallNode* ptNewSpeakerNode = pInst->m_pcNodeMgr->GetNode(wEpID);
	if ( ptNewSpeakerNode == NULL || !ptNewSpeakerNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("AudMixExciteSpeakerEp Error, no EpID or chan is off. ConfID:%d, wEpID:%d, ptNode:%d, ChanOn:%d\n", 
			pInst->GetInsID(), wEpID, ptNewSpeakerNode, ptNewSpeakerNode != NULL ? ptNewSpeakerNode->IsChanOn() : FALSE));
		return ;
	}
	
	if (pInst->GetUmsDiscuss()->IsUIDiscussOn())
	{
		TDiscussEpInfo* ptEpInfo = pInst->GetUmsDiscuss()->GetDiscussEpInfoById(wEpID);
		if (NULL == ptEpInfo || !ptEpInfo->IsValid())
		{
			MdlError(Ums_Mdl_Call, ("AudMixExciteSpeakerEp Error, ep is not vaild In discuss. ConfId:%d, epId:%d\n", pInst->GetInsID(), wEpID));
			return;
		}
		
		pInst->GetUmsDiscuss()->OnChangerSpeaker(ptNewSpeakerNode);
	}
	else
	{
		pInst->ChangeSpeaker(wEpID, NULL);
		pInst->AdjustNewSpeakerToAllNode();
		pInst->NotifyApplySpeakerToUI();
	}
	
	return;
}

//一个板子只发一次
void CUmsEapu::SetMixerSyncChnl( TMixSync& tSync )
{
#ifdef _USE_XMPUEQP_
	SetXmpuMixerSyncChnl(tSync);
	return;
#endif

	CUmsConfInst* pInst = Inst();

	TMixSyncChnl tSyncChnl;
	
	TAudMixInfo* ptInfo = NULL;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ptInfo = tSync.m_aptMixer[wIndex];
		if ( NULL == ptInfo )
		{
			continue ;
		}

		if ( !ptInfo->m_tEqpRes.IsValid() )
		{
			continue ;
		}

		tSyncChnl.m_abyEqpId[wIndex] = ptInfo->m_tEqpRes.m_byEqpID;
		tSyncChnl.m_abyChanId[wIndex] = tSync.m_abyChanId[wIndex];
	}

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::SetMixerSyncChnl. ConfID:%d, EqpId:(%d,%d,%d), SyncChnl:(%d,%d,%d).\n", 
		pInst->GetInsID(), tSyncChnl.m_abyEqpId[0], tSyncChnl.m_abyEqpId[1], tSyncChnl.m_abyEqpId[2],
		tSyncChnl.m_abyChanId[0], tSyncChnl.m_abyChanId[1], tSyncChnl.m_abyChanId[2]));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_SyncChnl_Cmd);
	cMsg.SetBody(&tSyncChnl, sizeof(tSyncChnl));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
}

void CUmsEapu::CheckDelMember( TAudMixInfo* ptInfo )
{
#ifdef _USE_XMPUEQP_
	CheckDelXmpuMember(ptInfo);
	return;
#endif
	if (NULL == ptInfo)
	{
		return;
	}

	if ( !ptInfo->m_tEqpRes.IsValid() )
	{
		return ;
	}

	u8 byChanID = ptInfo->m_byDelChnld;

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::CheckDelMember. ConfID:%d, EqpId:%d, DelChanId:%d.\n", 
		Inst()->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID, byChanID));

	if (0xFF != byChanID)
	{
		if (!ptInfo->m_atChnl[byChanID].IsExist())
		{// 没有被其他占用了，发delmember

			TTPMixMember tMember;
			tMember.m_byEqpID = ptInfo->m_tEqpRes.m_byEqpID;
			tMember.m_byIndex = byChanID;
			
			CTpMsg cMsg;
			cMsg.SetEvent(ev_mixer_del_mixmember);
			cMsg.SetBody(&tMember, sizeof(tMember));
			cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(Inst()->GetInsID()));
			
			
			if( ptInfo->m_atChnl[byChanID].m_ptMixChnAddr )
			{
				CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[byChanID].m_ptMixChnAddr);
				ptInfo->m_atChnl[byChanID].m_ptMixChnAddr = NULL;
			}
		}
	}

	ptInfo->m_byDelChnld = 0xFF;

	return;
}

void CUmsEapu::ShowMixInfo( TAudMixInfo* ptInfo )
{
	CUmsConfInst* pInst = Inst();
	
	msgprintnotime("-----------------MixInfo---------------, ConfID:%d\n\n", pInst->GetInsID());

	if (NULL == ptInfo)
	{
		return;
	}
	TTPMediaTransAddr* ptMediaAddr = NULL;
	u16 wChnIndx = 0;
	TServiceAddr tAddr;

#ifdef _USE_XMPUEQP_
	msgprintnotime("EqpID:%d, ChanNum:%d, UsedChanNum:%d, bVacOn:%d, bForceActiveChan:%d, bSyncChnl:%d, bDelChnlId:%d.\n\n",
		ptInfo->m_tEqpRes.m_byEqpID, 
		ptInfo->m_tEqpRes.m_wChanNum, ptInfo->m_wUsdChnNum,  ptInfo->m_bMixMotive, 
		ptInfo->m_byForceActiveChan, ptInfo->m_bySyncChnl,
		ptInfo->m_byDelChnld);
#else
	msgprintnotime("EqpID:%d, IP:"TPIPFORMAT", ChanNum:%d, UsedChanNum:%d, EqpRtpStartPort:%d, EqpRtcpstartPort:%d, bVacOn:%d, bForceActiveChan:%d, bSyncChnl:%d, bDelChnlId:%d.\n\n",
		ptInfo->m_tEqpRes.m_byEqpID, Tpu32ToIP(ptInfo->m_tEqpRes.m_dwEqpIp), 
		ptInfo->m_tEqpRes.m_wChanNum, ptInfo->m_wUsdChnNum,  
		ptInfo->m_tEqpRes.m_wEqpStartPort, ptInfo->m_tEqpRes.m_wEqpRtcpStartPort, ptInfo->m_bMixMotive, 
		ptInfo->m_byForceActiveChan, ptInfo->m_bySyncChnl,
		ptInfo->m_byDelChnld);
#endif

	msgprintnotime("N Mode AudMix--> AudFmtNum:%d", pInst->m_tConfBaseInfo.m_wAudFmtNum);
	for ( wChnIndx = 0; wChnIndx < pInst->m_tConfBaseInfo.m_wAudFmtNum; wChnIndx ++ )
	{
		GetNModeAudRcvAddr(ptInfo, tAddr, pInst->m_tConfBaseInfo.m_atAudFmt[wChnIndx]);
		msgprintnotime("	AudFmt:%s, UmsRcv: Rtp:"ADDRPORT_FORMAT",Rtcp:"ADDRPORT_FORMAT"\n", 
			UmsAudFormatPrint(pInst->m_tConfBaseInfo.m_atAudFmt[wChnIndx].m_emFormat),
			ADDRNET(tAddr.m_tAddr.m_tRtpAddr), ADDRNET(tAddr.m_tAddr.m_tBackRtcpAddr));
	}
	msgprintnotime("\n");
	for ( wChnIndx = 0; wChnIndx < TP_APU2_MAX_CHAN_NUM; wChnIndx ++ )
	{
		if ( !ptInfo->m_atChnl[wChnIndx].IsExist() )
		{
			continue;
		}
		
		msgprintnotime(" ChnIndx:%d, EpID:%d, ScrIndx:%d\n", wChnIndx, ptInfo->m_atChnl[wChnIndx].m_wEpID, ptInfo->m_atChnl[wChnIndx].m_wScrIndx);
		
		ptMediaAddr = ptInfo->m_atChnl[wChnIndx].m_ptMixChnAddr;
		if( ptMediaAddr )
		{
			msgprintnotime("  UMSRcv(MixOut N-1) MixRtp:"ADDRPORT_FORMAT" SndChnlBackRtcp:"ADDRPORT_FORMAT"\n", 
				ADDRNET(ptMediaAddr->m_tRtpAddr), ADDRNET(ptMediaAddr->m_tBackRtcpAddr));
		}
		
		ptMediaAddr = &ptInfo->m_atChnl[wChnIndx].m_tMixAddr;
		msgprintnotime("  MixerRcv RcvChnlRtp:"ADDRPORT_FORMAT" SndChnlBackRtcp(N-1):"ADDRPORT_FORMAT"\n", 
			ADDRNET(ptMediaAddr->m_tRtpAddr), ADDRNET(ptMediaAddr->m_tBackRtcpAddr));
	}

	msgprintnotime("\n\n-----------------MixInfoEnd---------------, ConfID:%d\n\n", pInst->GetInsID());
}



void CUmsEapu::SetMediaKey( const TTPQTMediaKeyInfo& tInfo, TAudMixInfo* ptInfo)
{
	CUmsConfInst* pInst = Inst();
	
	CTpMsg cMsg;
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( !m_atAudMix[wIndex].m_tEqpRes.IsValid() )
		{
			continue;
		}
		
		if ( ptInfo != NULL && ptInfo != &m_atAudMix[wIndex])
		{
			continue;
		}

		
		cMsg.SetBody(&(m_atAudMix[wIndex].m_tEqpRes.m_byEqpID), sizeof(u8));
		cMsg.CatBody(&tInfo, sizeof(tInfo));
		
		cMsg.SetEvent(ev_mixer_set_mediakey_ntfy);
		cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
	}
}

#ifdef _USE_XMPUEQP_
/*xmpu外设接口*/
TAudMixInfo* CUmsEapu::AssignXmpuMixer( AudMixerCB pCB, CUmsConfInst* ptUsrParam, u16 wChnlLimit /*= 0*/)
{
	CUmsConfInst* pInst = Inst();

	TAudMixInfo* ptInfo = FindIdle();
	if (  NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AssignXmpuMixer. TAudMixInfo is Full! ConfID:%d\n", pInst->GetInsID()));
		return NULL;
	}

	TXmpuMixParam tParam;
	TXmpuEqpRes tRes;
	tParam.m_ptEqp = &tRes;
	tParam.m_emEqpType = em_XmpuMix_Eqp;
	tParam.m_wConfID = Inst()->GetInsID();
	tParam.m_dwMediaIp = Inst()->m_tEqpConfDs.m_dwEqpIp;
	tParam.m_byChanNum = (wChnlLimit==0?MAX_AUDMIX_MDL_NUM:wChnlLimit); // 占用64能力混音器
	tParam.m_byMixDepth = 8;
	tParam.m_byNNum = pInst->m_tConfBaseInfo.m_wAudFmtNum;
	memcpy(tParam.m_atAudFmt, pInst->m_tConfBaseInfo.m_atAudFmt, sizeof(tParam.m_atAudFmt));
	tParam.m_tEncrypt = pInst->GetConfEncryptInfo();

	if(!AssignXmpuEqp(&tParam))
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AssignXmpuMixer. AssignApu Fail! ConfID:%d, wChnlLimit:%d\n", pInst->GetInsID(), wChnlLimit));
		return NULL;
	}

	memcpy(ptInfo->m_atNEncRtpAddr, tParam.m_atNEncRtpAddr, sizeof(ptInfo->m_atNEncRtpAddr));
	memcpy(ptInfo->m_atNEncMiddleRtcpAddr, tParam.m_atNEncMiddleRtcpAddr, sizeof(ptInfo->m_atNEncMiddleRtcpAddr));
	memcpy(ptInfo->m_atN1DecMiddleRtpAddr, tParam.m_atDecMiddleRtpAddr, sizeof(ptInfo->m_atN1DecMiddleRtpAddr));
	memcpy(ptInfo->m_atN1EncMiddleRtcpAddr, tParam.m_atEncMiddleRtcpAddr, sizeof(ptInfo->m_atN1EncMiddleRtcpAddr));
	ptInfo->m_tEqpRes.m_byEqpID = tRes.m_dwEqpID;
	ptInfo->m_tEqpRes.m_wChanNum = MAX_AUDMIX_MDL_NUM;
	ptInfo->m_pcCB = pCB;
	ptInfo->m_ptUsrParam = ptUsrParam;

	return ptInfo;
}

void CUmsEapu::ReleaseXmpuMixer( TAudMixInfo* ptInfo )
{
	CUmsConfInst* pInst = Inst();

	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::ReleaseXmpuMixer. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	if (!ptInfo->m_tEqpRes.m_byEqpID)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::ReleaseXmpuMixer. ptInfo is Invalid! ConfID:%d, dwEqpID:%d\n", 
							pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}

	TXmpuMixParam tParam;
	TXmpuEqpRes tRes;
	tRes.m_dwEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	tParam.m_ptEqp = &tRes;
	tParam.m_emEqpType = em_XmpuMix_Eqp;

	if(!ReleaseXmpuEqp(&tParam))
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::ReleaseXmpuMixer. ReleaseApu Fail! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID));
	}
	
	for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex ++ )
	{
		if ( NULL == ptInfo->m_atChnl[wIndex].m_ptMixChnAddr )
		{
			continue;
		}
		CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[wIndex].m_ptMixChnAddr);
	}
	if (ptInfo->m_cToMixDsInfo.GetElementNum() != 0)
	{
		CNetPortMgr::FreeMediaTrans(Inst(), ptInfo->m_cToMixDsInfo);
	}

	ptInfo->Clear();

	return ;
}

void CUmsEapu::OnXmpuAudMixDisConnect( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	u32 dwEqpID;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());

	TAudMixInfo* ptInfo = FindByEqpID(dwEqpID);
	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::OnXmpuAudMixDisConnect. AudMixer no exist! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), dwEqpID));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::OnXmpuAudMixDisConnect disconnect! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), dwEqpID));

	ptInfo->m_pcCB(TAudMixInfo::EmCBOprType_DisConnect, ptInfo, ptInfo->m_ptUsrParam);

	for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex ++ )
	{
		if ( NULL == ptInfo->m_atChnl[wIndex].m_ptMixChnAddr )
		{
			continue;
		}
		CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[wIndex].m_ptMixChnAddr);
	}

	if (ptInfo->m_cToMixDsInfo.GetElementNum() != 0)
	{
		CNetPortMgr::FreeMediaTrans(Inst(), ptInfo->m_cToMixDsInfo);
	}

	ptInfo->Clear();

	return ;
}

void CUmsEapu::AddXmpuMember( TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx, u16 wChnlIndx /*= TP_INVALID_INDEX*/ )
{
	CUmsConfInst* pInst = Inst();

	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddXmpuMember. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	if (!ptInfo->m_tEqpRes.m_byEqpID)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddXmpuMember. ptInfo is Invalid! ConfID:%d, dwEqpID:%d\n", pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}

	TCallNode* ptNode = Inst()->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFatherNode = Inst()->m_pcNodeMgr->GetForeFatherNode(wEpID);
	if ( NULL == ptNode || NULL == ptFatherNode || !ptNode->IsAudSndValid() || !ptFatherNode->IsAudSndValid())
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddXmpuMember. node or fathernode Invalid! ConfID:%d, EpID:%d\n", Inst()->GetInsID(), wEpID));
		return ;
	}

	if (!TP_VALID_HANDLE(wChnlIndx))
	{
		wChnlIndx = ptInfo->AddMember();
		if ( !TP_VALID_HANDLE(wChnlIndx) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsEapu::AddXmpuMember. wChnlIndx is Invalid! ConfID:%d, wChnlIndx:%d\n", pInst->GetInsID(), wChnlIndx));
			return ;
		}
	}

	//计算混音器的接收地址 存起来
	//xmpu audmix 多申请了一组中转地址，对外统一使用中转地址，内部创建实际地址到中转地址的交换
	ptInfo->m_atChnl[wChnlIndx].m_tMixAddr.m_tRtpAddr.SetAddr(ptInfo->m_atN1DecMiddleRtpAddr[wChnlIndx].GetIP(),
				ptInfo->m_atN1DecMiddleRtpAddr[wChnlIndx].GetPort());
	ptInfo->m_atChnl[wChnlIndx].m_tMixAddr.m_tBackRtcpAddr.SetAddr(ptInfo->m_atN1EncMiddleRtcpAddr[wChnlIndx].GetIP(),
		ptInfo->m_atN1EncMiddleRtcpAddr[wChnlIndx].GetPort());

	CMixerChnAddrListItor pItor = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr;
	if (NULL == pItor)
	{
		pItor = CUmsConfInst::GetEapuAddrList()->AllocNode();
	}

	if ( NULL == pItor )
	{
		ptInfo->DecrementChan();
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AddXmpuMember. GetMixerChnAddr Fail! ConfID:%d, wChnlIndx:%d\n", pInst->GetInsID(), wChnlIndx));
		return ;
	}


	ptInfo->m_atChnl[wChnlIndx].m_wEpID = wEpID;
	ptInfo->m_atChnl[wChnlIndx].m_wScrIndx = wScrIndx;
	ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr = pItor;

	BOOL32 bDual = wScrIndx<=TP_MAX_STREAMNUM ? FALSE : TRUE;

	//放在结点所在的转发板
	pItor->SetIP(ptFatherNode->m_tMediaEqp.m_dwEqpIp);

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::AddXmpuMember. ConfID:%d, EpID:%d, wScrIndex:%d, EqpID:%d, ChnlIndx:%d, bDual:%d\n", 
		pInst->GetInsID(), wEpID, wScrIndx, ptInfo->m_tEqpRes.m_byEqpID, wChnlIndx, bDual));

	TXmpuMixMember tMember;
	tMember.m_dwEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	tMember.m_wEpID = wEpID;
	tMember.m_wScreenIndex = wScrIndx;
	tMember.m_byIndex = wChnlIndx;
	tMember.m_tLocalRtpRcv = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr->m_tRtpAddr;
	tMember.m_tLocalRtcpRcv = ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr->m_tBackRtcpAddr;
	tMember.m_tEncrypt = Inst()->m_tConfBaseInfo.m_tEncrypt;
	if( bDual )
	{
		tMember.m_emAudFormat = ptNode->m_tDualAudSndFormat.m_tFormat.m_emFormat;
		tMember.m_emOutAudFormat = tMember.m_emAudFormat;
	}
	else
	{
		tMember.m_emAudFormat = ptNode->m_tAudSndFormat.m_tFormat.m_emFormat;

		tMember.m_emOutAudFormat = ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(evUms_XmpuAddMixMember_Req);
	cMsg.SetBody(&tMember, sizeof(tMember));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	return ;
}

void CUmsEapu::DelXmpuMember( TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx )
{
	CUmsConfInst* pInst = Inst();

	if ( NULL == ptInfo )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::DelXmpuMember. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	if (!ptInfo->m_tEqpRes.m_byEqpID)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::DelXmpuMember. ptInfo is Invalid! ConfID:%d, dwEqpID:%d\n", pInst->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}

	u16 wChnlIndx = ptInfo->GetIndx(wEpID, wScrIndx);
	if ( !TP_VALID_HANDLE(wChnlIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::DelXmpuMember. wChnlIndx is Invalid! ConfID:%d, wChnlIndx:%d\n", pInst->GetInsID(), wChnlIndx));
		return ;
	}

	u32 dwEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	u8  byChnID = wChnlIndx;
	CTpMsg cMsg;
	cMsg.SetEvent(evUms_XmpuDelMixMember_Req);
	cMsg.SetBody(&dwEqpID, sizeof(dwEqpID));
	cMsg.CatBody(&byChnID, sizeof(byChnID));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));


	if( ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr )
	{
		CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr);
		ptInfo->m_atChnl[wChnlIndx].m_ptMixChnAddr = NULL;
	}

	ptInfo->DelMember(wEpID, wScrIndx);

	// 删除成员刷新下交换
	CNetPortMgr::AdjustXmpuMiddleAddrToMix(Inst(), ptInfo);

	return;
}

void CUmsEapu::CheckDelXmpuMember( TAudMixInfo* ptInfo )
{
	if (NULL == ptInfo)
	{
		return;
	}

	if (!ptInfo->m_tEqpRes.m_byEqpID)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::CheckDelXmpuMember. ptInfo is Invalid! dwEqpID:%d\n", ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}

	u8 byChanID = ptInfo->m_byDelChnld;

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::CheckDelXmpuMember. ConfID:%d, EqpId:%d, DelChanId:%d.\n", 
		Inst()->GetInsID(), ptInfo->m_tEqpRes.m_byEqpID, byChanID));

	if (0xFF != byChanID)
	{
		if (!ptInfo->m_atChnl[byChanID].IsExist())
		{// 没有被其他占用了，发delmember

			u32 dwEqpID = ptInfo->m_tEqpRes.m_byEqpID;
			u8  byChnID = byChanID;
			CTpMsg cMsg;
			cMsg.SetEvent(evUms_XmpuDelMixMember_Req);
			cMsg.SetBody(&dwEqpID, sizeof(dwEqpID));
			cMsg.CatBody(&byChnID, sizeof(byChnID));
			cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));


			if( ptInfo->m_atChnl[byChanID].m_ptMixChnAddr )
			{
				CUmsConfInst::GetEapuAddrList()->FreeBuff(ptInfo->m_atChnl[byChanID].m_ptMixChnAddr);
				ptInfo->m_atChnl[byChanID].m_ptMixChnAddr = NULL;
			}
			// 删除成员刷新下交换
			CNetPortMgr::AdjustXmpuMiddleAddrToMix(Inst(), ptInfo);
		}
	}

	ptInfo->m_byDelChnld = 0xFF;
	return;
}

void CUmsEapu::OnXmpuStartMixRsp( CTpMsg *const ptMsg )
{
	TXmpuStartMixNty tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	TAudMixInfo* ptInfo = FindByEqpID(tInfo.m_dwEqpID);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::OnXmpuStartMixRsp. ptInfo is Invalid!, dwEqpID:%d\n", tInfo.m_dwEqpID));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::OnXmpuStartMixRsp. wConfID:%d, EqpID:%d, chanIndex:%d\n", 
				Inst()->GetInsID(), tInfo.m_dwEqpID, tInfo.m_bSuccess));

	if (tInfo.m_bSuccess)
	{
		ptInfo->m_byNNum = tInfo.m_byNum;
		memcpy(ptInfo->m_atNEncRtcpAddr, tInfo.m_atNEncRtcpAddr, sizeof(tInfo.m_atNEncRtcpAddr));
		// 刷新交换
		CNetPortMgr::AdjustXmpuMiddleAddrToMix(Inst(), ptInfo);
	}
}

void CUmsEapu::OnXmpuAddMemberRsp( CTpMsg *const ptMsg )
{
	TXmpuAddMixMemNty tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	TAudMixInfo* ptInfo = FindByEqpID(tInfo.m_dwEqpID);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::OnXmpuAddMemberRsp. ptInfo is Invalid! dwEqpID:%d\n", tInfo.m_dwEqpID));
		return ;
	}

	if (tInfo.m_bSuccess)
	{
	    memcpy(&ptInfo->m_atN1DecRtpAddr[tInfo.m_byChnID], &tInfo.m_tN1DecRtpAddr, sizeof(tInfo.m_tN1DecRtpAddr));
	    memcpy(&ptInfo->m_atN1EncRtcpAddr[tInfo.m_byChnID], &tInfo.m_tN1EncRtcpAddr, sizeof(tInfo.m_tN1EncRtcpAddr));
	    // 刷新交换
	    CNetPortMgr::AdjustXmpuMiddleAddrToMix(Inst(), ptInfo);
	}
}

void CUmsEapu::SetXmpuMixerSyncChnl( TMixSync& tSync )
{
	CUmsConfInst* pInst = Inst();

	TXmpuMixSynInfo tInfo;
	TAudMixInfo* ptInfo = NULL;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ptInfo = tSync.m_aptMixer[wIndex];
		if ( NULL == ptInfo )
		{
			continue ;
		}

		if ( !ptInfo->m_tEqpRes.m_byEqpID )
		{
			continue ;
		}

		tInfo.m_adwEqpID[wIndex] = ptInfo->m_tEqpRes.m_byEqpID;
		tInfo.m_abyChanId[wIndex] = tSync.m_abyChanId[wIndex];
	}
	if (tSync.m_bSpeakerObject)
	{
		tInfo.m_emSynType = em_Xmpu_Mix_SpeakerEp;
	}
	else
	{
		tInfo.m_emSynType = em_Xmpu_Mix_OtherThreeEp;
	}

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::SetXmpuMixerSyncChnl. ConfID:%d, EqpId:(%d,%d,%d), SyncChnl:(%d,%d,%d).\n", 
		pInst->GetInsID(), tInfo.m_adwEqpID[0], tInfo.m_adwEqpID[1], tInfo.m_adwEqpID[2],
		tInfo.m_abyChanId[0], tInfo.m_abyChanId[1], tInfo.m_abyChanId[2]));

	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetMixSync_Req);
	cMsg.SetBody(&tInfo, sizeof(tInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
}

void CUmsEapu::AdjustXmpuForceActive( TAudMixInfo* ptInfo, u16 wForceActiveEpID /*= TP_INVALID_INDEX*/ )
{
	CUmsConfInst* pInst = Inst();

	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AdjustXmpuForceActive. ptInfo is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	if (!ptInfo->m_tEqpRes.m_byEqpID)
	{
		MdlError(Ums_Mdl_Call, ("CUmsEapu::AdjustXmpuForceActive. ptInfo is Invalid! dwEqpID:%d\n", ptInfo->m_tEqpRes.m_byEqpID));
		return ;
	}

	u8 byChanIndex = TP_VALID_HANDLE(wForceActiveEpID) ? ptInfo->GetIndxByEpId(wForceActiveEpID) : TP_APU2_MAX_CHAN_NUM; // 找到需要强制混音的索引;

	MdlHint(Ums_Mdl_Call, ("CUmsEapu::AdjustXmpuForceActive. ConfID:%d, ForceActiveEpID:%d, EqpID:%d, OldChanIndex:%d, NewChanIndex:%d.\n", 
		pInst->GetInsID(), wForceActiveEpID, ptInfo->m_tEqpRes.m_byEqpID, ptInfo->m_byForceActiveChan,
		byChanIndex));

	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_ForceActive_Req);
	TForceActiveInfo tInfo;
	tInfo.m_dwEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	if (byChanIndex < TP_APU2_MAX_CHAN_NUM)
	{// 修改强制混音
		if ( ptInfo->m_byForceActiveChan != byChanIndex)
		{// 强制混音通道变化了，再发一次
			ptInfo->SetForceActive(byChanIndex);
			tInfo.m_byChnID = byChanIndex;
			tInfo.m_bStart = TRUE;
			cMsg.SetBody(&tInfo, sizeof(tInfo));
			cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		}
	}
	else if (ptInfo->IsForceActive())
	{
		tInfo.m_byChnID = ptInfo->m_byForceActiveChan;
		tInfo.m_bStart = FALSE;
		cMsg.SetBody(&tInfo, sizeof(tInfo));
		cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

		ptInfo->ClearForceActve();
	}
	else
	{
		// 不需要处理
	}

	return ;
}

void CUmsEapu::OnXmpuStartVacReq( TAudMixInfo* ptInfo )
{
	CUmsConfInst* pInst = Inst();

	CTpMsg cMsg;

	if (ptInfo->IsForceActive())
	{
		cMsg.SetEvent(evXmpu_ForceActive_Req);
		TForceActiveInfo tInfo;
		tInfo.m_dwEqpID = ptInfo->m_tEqpRes.m_byEqpID;
		tInfo.m_byChnID = ptInfo->m_byForceActiveChan;
		tInfo.m_bStart = FALSE;
		cMsg.SetBody(&tInfo, sizeof(tInfo));
		cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		ptInfo->ClearForceActve();
	}

	u32 dwEqpID = ptInfo->m_tEqpRes.m_byEqpID;
	cMsg.SetBody(&dwEqpID, sizeof(dwEqpID));
	cMsg.SetEvent(evXmpu_StartVac_Req);
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	ptInfo->m_bMixMotive = TRUE;

	//语音激励敏感度范围1-255秒，默认4秒
	s32 dwVal = CUmsConfigEx::GetInstance()->GetMixProtectedTime();

	cMsg.SetEvent(evXmpu_SetKeepTime_Req);
	cMsg.SetBody(&dwEqpID, sizeof(dwEqpID));
	cMsg.CatBody(&dwVal, sizeof(u32));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

}

void CUmsEapu::OnXmpuAudMixExciteInd( CTpMsg *const ptMsg )
{
	CUmsConfInst*	pInst = Inst();

	TXmpuVacActiveNty tVacResInfo;
	TP_SAFE_CAST( tVacResInfo, ptMsg->GetBody());

	if ( pInst->m_bIsQuiting || CUmsConfInst::inst_idle == pInst->CurState() )
	{//正在退出会议不处理
		return ;
	}

	TAudMixInfo* ptInfo = FindByEqpID(tVacResInfo.m_dwEqpID);
	if ( NULL == ptInfo )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::OnXmpuAudMixExciteInd. AudMixer no exist! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), tVacResInfo.m_dwEqpID));
		return ;
	}

	MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::OnXmpuAudMixExciteInd. ConfID:%d, EqpID:%d, VacChanId:%d.\n", 
		pInst->GetInsID(), tVacResInfo.m_dwEqpID, tVacResInfo.m_byChnID));
	if (ptInfo->m_bMixMotive && tVacResInfo.m_byChnID < TP_APU2_MAX_CHAN_NUM)
	{// 开启语音激励的混音器，处理语音激励结果
		AudMixExciteSpeakerEp(ptInfo, tVacResInfo.m_byChnID);
	}

}

void CUmsEapu::OnXmpuStopVac( TAudMixInfo* ptInfo )
{
	CUmsConfInst* pInst = Inst();

	u32 dwEqpId = ptInfo->m_tEqpRes.m_byEqpID;

	ptInfo->m_bMixMotive = FALSE;

	CTpMsg cMsg;
	cMsg.SetBody(&dwEqpId, sizeof(u32));
	cMsg.SetEvent(evXmpu_StopVar_Req);
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_CALL_APP_INST(pInst->GetInsID()));
}

void CUmsEapu::OnXmpuVoiceDetectionNty( CTpMsg *const ptMsg )
{
	CUmsConfInst*	pInst = Inst();

	TVoiceDetectionNty tVoiceInfo;
	TP_SAFE_CAST( tVoiceInfo, ptMsg->GetBody());

	if ( pInst->m_bIsQuiting || CUmsConfInst::inst_idle == pInst->CurState() )
	{//正在退出会议不处理
		return ;
	}

	TAudMixInfo* ptInfo = FindByEqpID(tVoiceInfo.m_dwEqpID);
	if ( NULL == ptInfo )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::onXmpuVoiceDetectionNty. AudMixer no exist! ConfID:%d, EqpID:%d\n", pInst->GetInsID(), tVoiceInfo.m_dwEqpID));
		return ;
	}

	MdlLowDtl(Ums_Mdl_Call, ("CUmsEapu::onXmpuVoiceDetectionNty. ConfID:%d, EqpID:%d.(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", 
		pInst->GetInsID(), tVoiceInfo.m_dwEqpID, tVoiceInfo.m_abyChanId[0], 
		tVoiceInfo.m_abyChanId[1], tVoiceInfo.m_abyChanId[2], tVoiceInfo.m_abyChanId[3], tVoiceInfo.m_abyChanId[4], tVoiceInfo.m_abyChanId[5],
		tVoiceInfo.m_abyChanId[6], tVoiceInfo.m_abyChanId[7], tVoiceInfo.m_abyChanId[8], tVoiceInfo.m_abyChanId[9]));

	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		pInst->GetUmsDiscuss()->UpdateMixDepthChanID(ptInfo, tVoiceInfo.m_abyChanId, MAXNUM_MIXER_DEPTH);
	}

	return ;
}


void CUmsEapu::ProcMixCb(CTpMsg *const ptMsg)
{
    TXmpuStartMixNty  tStartInfo;
    TXmpuAddMixMemNty tAddMemInfo;
    TXmpuVacActiveNty tVacActiveInfo;
    TVoiceDetectionNty tVoiceDelInfo;
    u32 wEqpId = 0;

    u32 dwEvent = ptMsg->GetEvent();
	
    switch (dwEvent)
	{
    case evXmpu_UmsStartMix_Nty:
	    memcpy(&tStartInfo, ptMsg->GetBody(), sizeof(tStartInfo));
	    wEqpId = tStartInfo.m_dwEqpID;
		OnXmpuStartMixRsp( ptMsg );
	    break;
    case evUms_XmpuAddMixMember_Nty:
	    memcpy(&tAddMemInfo, ptMsg->GetBody(), sizeof(tAddMemInfo));
	    wEqpId = tAddMemInfo.m_dwEqpID;
		OnXmpuAddMemberRsp(ptMsg);
	    break;
    case evXmpu_VacActive_Ntf:
	    memcpy(&tVacActiveInfo, ptMsg->GetBody(), sizeof(tVacActiveInfo));
		wEqpId = tVacActiveInfo.m_dwEqpID;
		OnXmpuAudMixExciteInd(ptMsg);
	    break;
    case evXmpu_MixVoiceDetection_Ntf:
        memcpy(&tVoiceDelInfo, ptMsg->GetBody(), sizeof(tVoiceDelInfo));
	    wEqpId = tVoiceDelInfo.m_dwEqpID;
		OnXmpuVoiceDetectionNty(ptMsg);
	    break;
    case evXmpu_MixDisConnect_Nty:
	    memcpy(&wEqpId, ptMsg->GetBody(), sizeof(wEqpId));
	    break;
    default:
	    return;
	}

    if (wEqpId == 0 )
	{
		return;
	}
   
    TAudMixInfo* ptMix = FindByEqpID( wEqpId );
	if (!ptMix)
	{
        return;
	}
	
	if (ptMix->m_pcCB)
	{
		tXmpuMixCbData tCbData;
		tCbData.pService = Inst();
		tCbData.pRes     = ptMix;
		tCbData.pData    = ptMsg->GetBody();

		ptMix->m_pcCB(dwEvent, &tCbData, NULL);
	}

}
#endif