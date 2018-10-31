#include "audiomixeqp.h"
#include "eventoutumseqp.h"
#include "innereventumsaudiomix.h"
#include "innereventumscall.h"
#include "eqpinterface.h"
#include "umsconfigex.h"
#include "eqpinst.h"
#include "mcuinstdef.h"
#include "mediatranseqp.h"
#include "umsconfig.h"
#include "eventoutumscommonbrd.h"

u32 g_dwCapSet = TP_APU2_MAX_CHAN_NUM; //混音板的最大能力，该值可以设置的较小，用来测试, 资源不足情况

//此处是外部地址 和本地端口可重复
#define UMS_APU2_EQP_RCV_PORT 20000 //apu2的码流接收地址
#define UMS_APU2_EQP_SND_PORT 10000 //apu2的码流发送地址

s8* GetStartDes(CAudioMixModle::EmAudMixStat em)
{
	s8* pcStat = NULL;

	switch(em)
	{
	case CAudioMixModle::EmAudMix_Normal:
		pcStat = "Normal";
		break;
	case CAudioMixModle::EmAudMix_Idle:
		pcStat = "Idle";
		break;
	case CAudioMixModle::EmAudMix_InitIng:
		pcStat = "InitIng";
		break;
	case CAudioMixModle::EmAudMix_Reserve:
		pcStat = "Reserve";
		break;
	case CAudioMixModle::EmAudMix_StartIng:
		pcStat = "StartIng";
		break;
	case CAudioMixModle::EmAudMix_Running:
		pcStat = "Running";
		break;
	case CAudioMixModle::EmAudMix_StopIng:
		pcStat = "StopIng";
		break;
	case CAudioMixModle::EmAudMix_Error:
		pcStat = "Error";
		break;
	default:
		pcStat = "default";
		break;
	}

	return pcStat;
}

CAudioMixEqp::CAudioMixEqp( CUmsEqpInst* pInst )
: CEqpBase(pInst)
{
// 	for ( u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; wMdlIndex ++ )
// 	{
// 		CAudioMixModle* ptModle = &m_atAudioMix[wMdlIndex];
// 		if (wMdlIndex < 4)
// 		{
// 			ptModle->m_bRegsited = TRUE;
// 			ptModle->m_emStat = CAudioMixModle::EmAudMix_Normal;
// 			ptModle->m_wChanNum = wMdlIndex%4 == 0 ? 34: 10;
// 			ptModle->m_byEqpID = 100+wMdlIndex;
// 			ptModle->m_dwUserNode = 1;
// 		}
// 		else if (wMdlIndex < 8)
// 		{
// 			ptModle->m_bRegsited = TRUE;
// 			ptModle->m_emStat = CAudioMixModle::EmAudMix_Normal;
// 			ptModle->m_wChanNum = wMdlIndex%4 == 0 ? 34: 10;
// 			ptModle->m_byEqpID = 100+wMdlIndex;
// 			ptModle->m_dwUserNode = 2;
// 		}
// 	}
}

CAudioMixEqp::~CAudioMixEqp()
{
	
}

CAudioMixModle* CAudioMixEqp::FindMixMdl( u8 byEqpID )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; wMdlIndex ++ )
	{
		if ( m_atAudioMix[wMdlIndex].m_byEqpID == byEqpID )
		{
			return &m_atAudioMix[wMdlIndex];
		}
	}

	return NULL;
}

void CAudioMixEqp::Handle( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	switch(wEvent)
	{
	case ev_mixer_reg:
		OnEqpReg(ptMsg);
		break;
	case ev_mixer_stat_ntfy:
		OnMixerStatNtfy(ptMsg);
		break;
	case ev_mixer_start_mix_nack:
		OnStartMixNAck(ptMsg);
		break;
	case ev_mixer_start_mix_ack:
		OnStartMixAck(ptMsg);
		break;
	case ev_mixer_stop_mix_nack:
		OnStopMixNAck(ptMsg);
		break;
	case ev_mixer_stop_mix_ack:
		OnStopMixAck(ptMsg);
		break;
	case ev_mixer_add_mixmember_nack:
		OnAddMixMemberNAck(ptMsg);
		break;
	case ev_mixer_add_mixmember_ack:
		OnAddMixMemberAck(ptMsg);
		break;
	case ev_mixer_del_mixmember_nack:
		OnDelMixMemberNAck(ptMsg);
		break;
	case ev_mixer_del_mixmember_ack:
		OnDelMixMemberAck(ptMsg);
		break;
	case ev_mixer_start_mix:
		OnStartMix(ptMsg);
		break;
	case ev_mixer_stop_mix:
		OnStopMix(ptMsg);
		break;
	case ev_mixer_start_vac:
		OnStartVAC(ptMsg);
		break;
	case ev_mixer_stop_vac:
		OnStopVAC(ptMsg);
		break;
	case ev_mixer_set_vac_keeptime:
		OnSetVacKeepTime(ptMsg);
		break;
	case ev_mixer_vac_result_ntfy:
		OnVacResultNtfy(ptMsg);
		break;
	case ev_mixer_add_mixmember:
		OnAddMixMember(ptMsg);
		break;
	case ev_mixer_del_mixmember:
		OnDelMixMember(ptMsg);
		break;
	case ev_mixer_if_snd_ntfy:
		OnifSndNtfy(ptMsg);
		break;
	case ev_mixer_ForceActive_Cmd:
		OnForceActive(ptMsg);
		break;
	case ev_mixer_CancelForceActive_Cmd:
		OnCancelForceActive(ptMsg);
		break;
	case ev_mixer_SyncChnl_Cmd:
		OnSyncChnlCmd(ptMsg);
		break;
	case ev_mixer_set_mediakey_ntfy:
		OnSetMediaKeyNtfy(ptMsg);
		break;

	default:
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::Handle Unknow event:%d->%s\n", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}
}

void CAudioMixEqp::Show()
{
	CHECK_EQP_SEM;

	msgprintnotime("AudioMixEqp Info : \n");
	CAudioMixModle* pcMixerMdl = NULL;
	for (u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; ++wMdlIndex)
	{
		pcMixerMdl = &m_atAudioMix[wMdlIndex];
		if (pcMixerMdl->m_bRegsited)
		{
			msgprintnotime("  Indx:%d, EqpID:%d, IP:"TPIPFORMAT",  ChanStat:%s, ChanNum:%d, OffSet:%d, EqpRtpStartPort:%d, EqpRtcpStartPort:%d, UmsStartPort:%d\n",
							wMdlIndex, 
							pcMixerMdl->m_byEqpID, 
							Tpu32ToIP(pcMixerMdl->m_tRegInfo.m_dwEqpIP), 
							GetStartDes(pcMixerMdl->m_emStat),
							pcMixerMdl->m_wChanNum, 
							pcMixerMdl->m_wOffSet, 
							pcMixerMdl->m_wEqpRcvStartPort,
							pcMixerMdl->m_wEqpRcvRtcpStartPort,
							pcMixerMdl->m_wUmsRcvStartPort);
		}
	}

	return ;
}

BOOL32 CAudioMixEqp::OnDisConnect( u32 dwNode )
{
	u32 dwRegIP = 0;
	u16	wConfID = TP_INVALID_INDEX;
	u16 wMdlIndex = 0;
	
	CHECK_EQP_SEM;

	CAudioMixModle* ptEqp = NULL;
	for (wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; ++wMdlIndex)
	{
		if (m_atAudioMix[wMdlIndex].m_dwUserNode != dwNode)
		{
			continue;
		}

		ptEqp = &m_atAudioMix[wMdlIndex];
		
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsAudioMixUnReg_Notify);
		cMsg.CatBody(&ptEqp->m_byEqpID, sizeof(u8));
		cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
		
		//更新外设状态到eqpmgr
		m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptEqp->m_dwUserNode, ptEqp->m_byEqpID, FALSE);

		dwRegIP = ptEqp->m_tRegInfo.m_dwEqpIP;
		wConfID = ptEqp->m_wConfID;
		
		ptEqp->Clear();
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDisConnect. ConfID:%d, dwNode:%d, index:%d, RegIP:"TPIPFORMAT" \n", wConfID, dwNode, wMdlIndex, Tpu32ToIP(dwRegIP)));	
	return TRUE;
}

void CAudioMixEqp::OnEqpReg( CTpMsg *const ptMsg )
{
	TMixerRegInfo tReg;
	TP_SAFE_CAST( tReg, ptMsg->GetBody());

	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tReg.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_mixer_reg_nack, NULL, 0);
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnEqpReg No idle location! RegIP:"TPIPFORMAT", EqpID:%d\n", Tpu32ToIP(tReg.m_dwEqpIP), tReg.m_byEqpID));	
		return;
	}

	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_InitIng )
	{
		SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_mixer_reg_nack, NULL, 0);
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnEqpReg state Invalid! EmStat:%s, EqpID:%d\n", GetStartDes(pcMixerMdl->m_emStat), tReg.m_byEqpID));	
		return;
	}
	
	pcMixerMdl->m_bRegsited = TRUE;
	pcMixerMdl->m_dwUserInst = ptMsg->GetSrcIId();
	pcMixerMdl->m_dwUserNode = ptMsg->GetSrcNode();
	pcMixerMdl->m_tRegInfo.m_dwEqpIP = tReg.m_dwEqpIP;

	TMixRegAck tAck;
	if (CUmsConfigEx::GetInstance()->GetRsFirstTime() != 0 && CUmsConfigEx::GetInstance()->GetRsRejectTime() != 0)
	{
		tAck.m_tRsParam.m_wFirstTimeSpan	= CUmsConfigEx::GetInstance()->GetRsFirstTime();
		tAck.m_tRsParam.m_wSecondTimeSpan	= CUmsConfigEx::GetInstance()->GetRsSecondTime();
		tAck.m_tRsParam.m_wThirdTimeSpan	= CUmsConfigEx::GetInstance()->GetRsThirdTime();
		tAck.m_tRsParam.m_wRejectTimeSpan	= CUmsConfigEx::GetInstance()->GetRsRejectTime();
	}
	umsGetLocalUmsIP(tAck.m_dwIpAddr);//会议转发板ip N模式使用
	tAck.m_wStartPort = pcMixerMdl->m_wUmsRcvStartPort  - pcMixerMdl->m_wChanNum*UMS_MCU_PORT_PORTSPAN;

	SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_mixer_reg_ack, (u8*)&tAck, sizeof(tAck));

	//更新外设注册状态到eqpmgr
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptMsg->GetSrcNode(), pcMixerMdl->m_byEqpID, TRUE);

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnEqpReg Success! MdlIP:"TPIPFORMAT", EqpID:%d\n", Tpu32ToIP(tReg.m_dwEqpIP), tReg.m_byEqpID));

	return ;
}

void CAudioMixEqp::OnMixerStatNtfy( CTpMsg *const ptMsg )
{
	TMixerStatNtfy	tNtfy;
	TP_SAFE_CAST( tNtfy, ptMsg->GetBody());

	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tNtfy.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnMixerStatNtfy Mdl no Exist! EqpID:%d\n", tNtfy.m_byEqpID));	
		return;
	}

	if (tNtfy.m_byMixChanNum != pcMixerMdl->m_wChanNum)
	{// APU2板上混音器通道数和平台侧保留的不一致，则通知APU2板重启
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnMixerStatNtfy ChanNum is not equal, Nofity apu2 reboot! apu2 channum = %d, local channum = %d\n", 
			tNtfy.m_byMixChanNum, pcMixerMdl->m_wChanNum));

		// 从eqpmgr中获取对应AP2板子的inst号
		u16 wIndex = m_pcInst->GetEqpMgr()->GetBrdIndex(ptMsg->GetSrcNode());
		u32 dwInst = m_pcInst->GetEqpMgr()->GetBrdInst(wIndex);
		
		// APU2板子重启
		m_pcInst->SendToBrd(em_apu2_tp_brd, ev_TPBrdReboot_Cmd, dwInst, 0);		
		return;
	}

	MdlHint(Ums_Mdl_Eqp, ("OnMixerStatNtfy! EqpID:%d, Alis:%s RegIP:"TPIPFORMAT", stat:%d (1: success), OnLine:%d, chanNum:%d\n", 
			pcMixerMdl->m_byEqpID, tNtfy.m_szAlias, Tpu32ToIP(pcMixerMdl->m_tRegInfo.m_dwEqpIP), tNtfy.m_byStat, tNtfy.m_bOnLine, tNtfy.m_byMixChanNum));

	if ( tNtfy.m_byStat == 1 )
	{
		pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_Normal;

		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsAudioMixReg_Notify);

		TEqpRes tRes;
		tRes.m_dwEqpIp = pcMixerMdl->m_tRegInfo.m_dwEqpIP;
		tRes.m_dwEqpNode = pcMixerMdl->m_dwUserNode;

		cMsg.SetBody(&tRes, sizeof(tRes));
		cMsg.Post(UMS_CALL_APP_INST(CInstance::DAEMON), 0, UMS_EQP_APP_INST);
	}
	else
	{//其他出错

	}

	return ;
}

BOOL32 CAudioMixEqp::AssignEqpEx( TEqpParam* ptEqpParam )
{
	TMixerParam*	ptMixerParam = (TMixerParam*)ptEqpParam;

	CHECK_EQP_SEM;	

	u16 wSurperIndx = TP_INVALID_INDEX;

	if (ptMixerParam->m_wReqNum > 1)
	{
		u32 dwNode = ptMixerParam->m_dwNode;
		if (0 == dwNode)
		{// 找一个合适的apu2板卡分配
			dwNode = FindSuitableApu2(ptMixerParam->m_wChanLimit, ptMixerParam->m_wReqNum);
		}

		if (0 == dwNode)
		{// 找不到，分配失败
			MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::AssignEqpEx no suitable apu2! ConfID:%d, ReqNum:%d, LimitChan:%d, FindNode:%d.\n", 
				ptMixerParam->m_wConfID, ptMixerParam->m_wReqNum, ptMixerParam->m_wChanLimit, dwNode));	
			return FALSE;
		}
		wSurperIndx = FindSuitableMixMdl(ptMixerParam->m_wChanLimit, dwNode);
	}
	else
	{
		wSurperIndx = FindSuitableMixMdl(ptMixerParam->m_wChanLimit);
	}

	if ( !TP_VALID_HANDLE(wSurperIndx) )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::AssignEqpEx no suitable mdl! ConfID:%d, ReqNum:%d, LimitChan:%d, Node:%d.\n", 
			ptMixerParam->m_wConfID, ptMixerParam->m_wReqNum, ptMixerParam->m_wChanLimit, ptMixerParam->m_dwNode));		
		return FALSE;
	}

	m_atAudioMix[wSurperIndx].m_emStat = CAudioMixModle::EmAudMix_Reserve;
	m_atAudioMix[wSurperIndx].m_wConfID = ptMixerParam->m_wConfID;

	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_byEqpID = m_atAudioMix[wSurperIndx].m_byEqpID;
	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_wChanNum = m_atAudioMix[wSurperIndx].m_wChanNum;

	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_wEqpStartPort = m_atAudioMix[wSurperIndx].m_wEqpRcvStartPort;
	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_wEqpRtcpStartPort = m_atAudioMix[wSurperIndx].m_wEqpRcvRtcpStartPort;
	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_wUmsStartPort = m_atAudioMix[wSurperIndx].m_wUmsRcvStartPort;

	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_dwEqpIp = m_atAudioMix[wSurperIndx].m_tRegInfo.m_dwEqpIP;
	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_dwEqpNode = m_atAudioMix[wSurperIndx].m_dwUserNode;
	((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_dwEqpInst = MAKEIID(AID_UMSEQP_APP, 1);//本地的eqp inst

	
	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::AssignEqpEx! ConfID:%d, EqpID:%d, RegIP:"TPIPFORMAT", stat:%d\n", 
						ptMixerParam->m_wConfID, 
						m_atAudioMix[wSurperIndx].m_byEqpID, 
						Tpu32ToIP(m_atAudioMix[wSurperIndx].m_tRegInfo.m_dwEqpIP), 
						m_atAudioMix[wSurperIndx].m_emStat
						));

	return TRUE;
}

BOOL32 CAudioMixEqp::ReleaseEqpEx( TEqpParam* ptEqpParam )
{
	TMixerParam*	ptMixerParam = (TMixerParam*)ptEqpParam;

	CHECK_EQP_SEM;

	CAudioMixModle* pcMixerMdl = FindMixMdl(((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::ReleaseEqpEx Mdl no Exist! EqpID:%d\n", ((TMixEqpRes*)ptMixerParam->m_ptEqpRes)->m_byEqpID));	
		return FALSE;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::ReleaseEqpEx! ConfID:%d, EqpID:%d, RegIP:"TPIPFORMAT", stat:%s\n", 
						pcMixerMdl->m_wConfID, pcMixerMdl->m_byEqpID, Tpu32ToIP(pcMixerMdl->m_tRegInfo.m_dwEqpIP), GetStartDes(pcMixerMdl->m_emStat)));

	CTpMsg cMsg;
	if ( pcMixerMdl->m_emStat == CAudioMixModle::EmAudMix_Reserve )
	{//直接置状态即可
		pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_Normal;
		pcMixerMdl->m_wConfID = TP_INVALID_INDEX;
	}
	else if ( pcMixerMdl->m_emStat == CAudioMixModle::EmAudMix_Running
		|| pcMixerMdl->m_emStat == CAudioMixModle::EmAudMix_StartIng )
	{
		//先停止语音激励
		cMsg.SetEvent(ev_mixer_stop_vac);
		cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
		//再停止混音
		cMsg.SetEvent(ev_mixer_stop_mix);
		cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);

		pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_StopIng;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::ReleaseEqpEx. Error! ConfID:%d, EqpID:%d, RegIP:"TPIPFORMAT", stat:%s\n", 
						pcMixerMdl->m_wConfID, pcMixerMdl->m_byEqpID, Tpu32ToIP(pcMixerMdl->m_tRegInfo.m_dwEqpIP), GetStartDes(pcMixerMdl->m_emStat)));
	}
	return TRUE;
}

void CAudioMixEqp::CalcEqpUsedStat(TTPBrdUsedInfo& tUsed)
{
	tUsed.m_emType = em_audmix_mdl;
	for ( u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; wMdlIndex ++ )
	{
		if ( !m_atAudioMix[wMdlIndex].m_bRegsited )
		{
			continue;
		}

		if ( m_atAudioMix[wMdlIndex].m_emStat == CAudioMixModle::EmAudMix_Idle
			|| m_atAudioMix[wMdlIndex].m_emStat == CAudioMixModle::EmAudMix_InitIng
			|| m_atAudioMix[wMdlIndex].m_emStat == CAudioMixModle::EmAudMix_Error)
		{
			continue;
		}
		
		tUsed.m_wRegNum ++;

		if ( m_atAudioMix[wMdlIndex].m_emStat == CAudioMixModle::EmAudMix_Normal )
		{
			continue;
		}

		tUsed.m_wUsedNum ++;
	}

	return ;
}

void CAudioMixEqp::OnStartMix( CTpMsg *const ptMsg )
{
	TStartMix tTPStart;
	TP_SAFE_CAST(tTPStart, ptMsg->GetBody());

	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTPStart.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMix Mdl no Exist! EqpID:%d\n", tTPStart.m_byEqpID));	
		return ;
	}

	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Reserve)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMix Stat Invalid! EqpID:%d, Stat:%s\n", tTPStart.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMix! ConfID:%d, EqpID:%d, N num:%d, AudFormat:(%d,%d,%d,%d), stat:%s\n", 
							pcMixerMdl->m_wConfID, pcMixerMdl->m_byEqpID, 
							tTPStart.m_byNNum, tTPStart.m_atAudFmt[0].m_emFormat, tTPStart.m_atAudFmt[1].m_emFormat, 
							tTPStart.m_atAudFmt[2].m_emFormat, tTPStart.m_atAudFmt[3].m_emFormat, 
							GetStartDes(pcMixerMdl->m_emStat)));

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMix! EncryptInfo(%d,%s,%d)\n", tTPStart.m_tEncrypt.m_emEncryptModel, 
		tTPStart.m_tEncrypt.m_achEncKey, tTPStart.m_tEncrypt.m_byKeyLen));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_start_mix);
	cMsg.SetBody(&tTPStart, sizeof(tTPStart));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);

	//设置深度
	TTPMixDepth tDepth;
	tDepth.m_byEqpID = pcMixerMdl->m_byEqpID;
	tDepth.m_byDepth = 8;

	cMsg.SetEvent(ev_mixer_set_depth);
	cMsg.SetBody(&tDepth, sizeof(tDepth));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);

	pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_StartIng;

	return ;
}

void CAudioMixEqp::OnStartMixAck( CTpMsg *const ptMsg )
{
	u8 byEqpID = *(u8*)ptMsg->GetBody();

	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMixAck Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMixAck! ConfID:%d, EqpID:%d, stat:%s\n", 
							pcMixerMdl->m_wConfID, pcMixerMdl->m_byEqpID, GetStartDes(pcMixerMdl->m_emStat)));

	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{// 已经释放了，直接返回
		return;
	}

	pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_Running;

	return ;
}

void CAudioMixEqp::OnStartMixNAck( CTpMsg *const ptMsg )
{
	u8 byEqpID = *(u8*)ptMsg->GetBody();
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMixNAck Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}

	MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartMixNAck. ConfID:%d, EqpID:%d, stat:%s\n", pcMixerMdl->m_wConfID, byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
	
	if (pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng)
	{
		return;
	}

	pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_Error;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_start_mix_nack);
	cMsg.SetBody(&byEqpID, sizeof(u8));
	cMsg.Post(UMS_CALL_APP_INST(pcMixerMdl->m_wConfID), 0, UMS_EQP_APP_INST);
	
	return ;
}

void CAudioMixEqp::OnStopMix( CTpMsg *const ptMsg )
{
	u8 byEqpID = *(u8*)ptMsg->GetBody();

	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopMix Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running || 
		pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopMix Stat Invalid! EqpID:%d, Stat:%s\n", byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopMix. ConfID:%d, EqpID:%d, stat:%s\n", pcMixerMdl->m_wConfID, byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_stop_mix);
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);

	pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_StopIng;

	return ;
}

void CAudioMixEqp::OnStopMixAck( CTpMsg *const ptMsg )
{
	u8 byEqpID = *(u8*)ptMsg->GetBody();
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopMixAck Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopMixAck. ConfID:%d, EqpID:%d, stat:%s\n", pcMixerMdl->m_wConfID, byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
	
	pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_Normal;
	pcMixerMdl->m_wConfID = TP_INVALID_INDEX;

	return ;
}

void CAudioMixEqp::OnStopMixNAck( CTpMsg *const ptMsg )
{
	u8 byEqpID = *(u8*)ptMsg->GetBody();
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopMixNAck Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}

	MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopMixNAck. ConfID:%d, EqpID:%d, stat:%s\n", pcMixerMdl->m_wConfID, byEqpID, GetStartDes(pcMixerMdl->m_emStat)));

	if (pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StopIng)
	{
		return;
	}

	pcMixerMdl->m_emStat = CAudioMixModle::EmAudMix_Error;
	
	return ;
}

void CAudioMixEqp::OnStartVAC( CTpMsg *const ptMsg )
{
	TStartMix tTPStart;
	TP_SAFE_CAST(tTPStart, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTPStart.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartVAC Mdl no Exist! EqpID:%d\n", tTPStart.m_byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng &&
		pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running && 
		pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Reserve )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartVAC Stat Invalid! EqpID:%d, Stat:%s\n", tTPStart.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStartVAC! ConfID:%d, EqpID:%d, N num:%d, AudFormat:(%d,%d,%d,%d), stat:%s\n", 
		pcMixerMdl->m_wConfID, pcMixerMdl->m_byEqpID, 
		tTPStart.m_byNNum, tTPStart.m_atAudFmt[0].m_emFormat, tTPStart.m_atAudFmt[1].m_emFormat, 
		tTPStart.m_atAudFmt[2].m_emFormat, tTPStart.m_atAudFmt[3].m_emFormat, 
							GetStartDes(pcMixerMdl->m_emStat)));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_start_vac);
	cMsg.SetBody(&tTPStart, sizeof(tTPStart));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
}

void CAudioMixEqp::OnStopVAC( CTpMsg *const ptMsg )
{//
	u8 byEqpID = *(u8*)ptMsg->GetBody();
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopVAC Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StopIng &&
		pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopVAC Stat Invalid! EqpID:%d, Stat:%s\n", byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnStopVAC. ConfID:%d, EqpID:%d, stat:%s\n", pcMixerMdl->m_wConfID, byEqpID, GetStartDes(pcMixerMdl->m_emStat)));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_stop_vac);
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
}

void CAudioMixEqp::OnAddMixMember( CTpMsg *const ptMsg )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());

	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTpMember.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMember Mdl no Exist! EqpID:%d\n", tTpMember.m_byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running
		&& pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMember Stat Invalid! EqpID:%d, Stat:%s, EpID:%d, chanIndex:%d\n", 
									tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_wEpID, tTpMember.m_byIndex));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMember. ConfID:%d, EqpID:%d, EPID:%d, chanIndex:%d, stat:%s\n", 
						pcMixerMdl->m_wConfID, tTpMember.m_byEqpID, tTpMember.m_wEpID, tTpMember.m_byIndex, GetStartDes(pcMixerMdl->m_emStat)));	

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_add_mixmember);
	cMsg.SetBody(&tTpMember, sizeof(tTpMember));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);

	return ;
}

void CAudioMixEqp::OnAddMixMemberAck( CTpMsg *const ptMsg )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTpMember.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMemberAck Mdl no Exist! EqpID:%d\n", tTpMember.m_byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running 
		&& pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMemberAck Stat Invalid! EqpID:%d, Stat:%s, chanIndex:%d\n", 
									tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_byIndex));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMemberAck. ConfID:%d, EqpID:%d, chanIndex:%d, stat:%s\n", 
								pcMixerMdl->m_wConfID, tTpMember.m_byEqpID, tTpMember.m_byIndex, GetStartDes(pcMixerMdl->m_emStat)));	

	return ;
}

void CAudioMixEqp::OnAddMixMemberNAck( CTpMsg *const ptMsg )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTpMember.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMemberNAck Mdl no Exist! EqpID:%d\n", tTpMember.m_byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running
		&& pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMemberNAck Stat Invalid! EqpID:%d, Stat:%s, chanIndex:%d\n", 
										tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_byIndex));
		return ;
	}

	MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnAddMixMemberNAck. ConfID:%d, EqpID:%d, Stat:%s, chanIndex:%d\n", 
								pcMixerMdl->m_wConfID, tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_byIndex));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_add_mixmember_nack);
	cMsg.SetBody(&tTpMember, sizeof(tTpMember));
	cMsg.Post(UMS_CALL_APP_INST(pcMixerMdl->m_wConfID), 0, UMS_EQP_APP_INST);

	return ;
}

void CAudioMixEqp::OnDelMixMember( CTpMsg *const ptMsg )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTpMember.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMember Mdl no Exist! EqpID:%d\n", tTpMember.m_byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running
	  && pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMember Stat Invalid! EqpID:%d, Stat:%s, EpID:%d\n", 
								tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_wEpID));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMember. ConfID:%d, EqpID:%d, EPID:%d, chanIndex:%d, stat:%s\n", 
					pcMixerMdl->m_wConfID, tTpMember.m_byEqpID, tTpMember.m_wEpID, tTpMember.m_byIndex, GetStartDes(pcMixerMdl->m_emStat)));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_del_mixmember);
	cMsg.SetBody(&tTpMember, sizeof(tTpMember));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
}

void CAudioMixEqp::OnDelMixMemberAck( CTpMsg *const ptMsg )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTpMember.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMemberAck Mdl no Exist! EqpID:%d, chanIndex:%d\n", tTpMember.m_byEqpID, tTpMember.m_byIndex));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running
		&& pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMemberAck Stat Invalid! EqpID:%d, Stat:%s, chanIndex:%d\n", 
												tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_byIndex));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMemberAck. ConfID:%d, EqpID:%d, chanIndex:%d, stat:%s\n", 
					pcMixerMdl->m_wConfID, tTpMember.m_byEqpID, tTpMember.m_byIndex, GetStartDes(pcMixerMdl->m_emStat)));
	
	return ;
}

void CAudioMixEqp::OnDelMixMemberNAck( CTpMsg *const ptMsg )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tTpMember.m_byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMemberNAck Mdl no Exist! EqpID:%d\n", tTpMember.m_byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running
		&& pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMemberNAck Stat Invalid! EqpID:%d, Stat:%s, chanIndex:%d\n", 
											tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_byIndex));
		return ;
	}

	MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnDelMixMemberNAck. ConfID:%d, EqpID:%d, Stat:%s, chanIndex:%d\n", 
									pcMixerMdl->m_wConfID, tTpMember.m_byEqpID, GetStartDes(pcMixerMdl->m_emStat), tTpMember.m_byIndex));
	
// 	CTpMsg cMsg;
// 	cMsg.SetEvent(ev_mixer_del_mixmember_nack);
// 	cMsg.SetBody(&tTpMember, sizeof(tTpMember));
// 	cMsg.Post(UMS_CALL_APP_INST(pcMixerMdl->m_wConfID), 0, UMS_EQP_APP_INST);
	
	return ;
}

void CAudioMixEqp::OnSetVacKeepTime( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	u32 dwVacKeepTimeS;
	TP_SAFE_CAST(dwVacKeepTimeS, ptMsg->GetBody()+sizeof(u8));

	CHECK_EQP_SEM;
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnSetVacKeepTime Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running &&
		pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_StartIng )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnSetVacKeepTime Stat Invalid! EqpID:%d, Stat:%s\n", byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnSetVacKeepTime. ConfID:%d, EqpID:%d, TimeS:%d, stat:%s\n", 
					pcMixerMdl->m_wConfID, byEqpID, dwVacKeepTimeS, GetStartDes(pcMixerMdl->m_emStat)));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_set_vac_keeptime);
	cMsg.SetBody(&byEqpID, sizeof(byEqpID));
	cMsg.CatBody(&dwVacKeepTimeS, sizeof(dwVacKeepTimeS));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);

	return ;
}

CAudioMixModle* CAudioMixEqp::InsertMix( TTPEqpCfg& tCfg, u32 dwNode, u16 wOffSet )
{
	CHECK_EQP_SEM;
	
	CAudioMixModle* ptMdl = FindMixMdl(tCfg.m_byEqpID);
	if ( NULL != ptMdl )
	{//已经存在 则拒绝
		return NULL;
	}

	static u16 wNModlOffSet = 0;
	if ( wOffSet == 0 )
	{
		wNModlOffSet = 0;
	}
	
	for ( u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; wMdlIndex ++ )
	{
		ptMdl = &m_atAudioMix[wMdlIndex];

		if ( !ptMdl->IsIdle() || !ptMdl->m_emStat == CAudioMixModle::EmAudMix_Idle )
		{
			continue;
		}

		ptMdl->m_wChanNum = tCfg.m_byAudmixNum;

		//初始化端口 每个板子接收都从20000 开始接收rtp  10000开始接收rtcp 配置了两个混音器的，根据offset进行偏移
		ptMdl->m_wEqpRcvStartPort = UMS_APU2_EQP_RCV_PORT + wOffSet*UMS_MCU_PORT_PORTSPAN;
		
		//wOffSet加4 是为了空出最大4个N模式混音
		ptMdl->m_wEqpRcvRtcpStartPort = UMS_APU2_EQP_SND_PORT + (wOffSet == 0 ? wOffSet : wOffSet+4*(++wNModlOffSet))*UMS_MCU_PORT_PORTSPAN;

		//Ums侧接收 N模式混音的地址
		ptMdl->m_wUmsRcvStartPort = ( UMS_AUD_MIX_BEGIN_PORT + 4*wMdlIndex*UMS_MCU_PORT_PORTSPAN);
		
		ptMdl->m_emStat = CAudioMixModle::EmAudMix_InitIng;
		ptMdl->m_byEqpID = tCfg.m_byEqpID;
		ptMdl->m_dwUserNode = dwNode;
		ptMdl->m_wOffSet = wOffSet;
		
		return ptMdl;
	}
	
	return NULL;
}

void CAudioMixEqp::DeleteMix( u8 byEqpID )
{
	CHECK_EQP_SEM;

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{
		if ( m_atAudioMix[wMdlIndex].m_byEqpID == byEqpID )
		{
			m_atAudioMix[wMdlIndex].m_emStat = CAudioMixModle::EmAudMix_Idle;
			m_atAudioMix[wMdlIndex].m_byEqpID = 0;
		}
	}
	return ;
}

void CAudioMixEqp::OnVacResultNtfy( CTpMsg *const ptMsg )
{	
	TMixVacResInfo tVacInfo;
	TP_SAFE_CAST(tVacInfo, ptMsg->GetBody());
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tVacInfo.m_byEqpId);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnVacResultNtfy Mdl no Exist! EqpID:%d\n", tVacInfo.m_byEqpId));	
		return ;
	}
	
	if ( pcMixerMdl->m_emStat != CAudioMixModle::EmAudMix_Running )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnVacResultNtfy Stat Invalid! EqpID:%d, Stat:%s\n", tVacInfo.m_byEqpId, GetStartDes(pcMixerMdl->m_emStat)));
		return ;
	}

	MdlLowDtl(Ums_Mdl_Eqp, ("CAudioMixEqp::OnVacResultNtfy. ConfID:%d, EqpID:%d, VacChanId:%d, stat:%s\n", 
						pcMixerMdl->m_wConfID, tVacInfo.m_byEqpId, tVacInfo.m_byVacChanId, GetStartDes(pcMixerMdl->m_emStat)));

 	CTpMsg cMsg;
 	cMsg.SetEvent(ev_mixer_vac_result_ntfy);
	cMsg.SetBody(&tVacInfo, sizeof(tVacInfo));
 	cMsg.Post(UMS_CALL_APP_INST(pcMixerMdl->m_wConfID), 0, UMS_EQP_APP_INST);

	return ;
}

void CAudioMixEqp::OnifSndNtfy( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	BOOL32 bSnd;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(bSnd, ptMsg->GetBody()+sizeof(byEqpID));
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnifSndNtfy Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnifSndNtfy. EqpID:%d, bSnd:%d, stat:%s\n", byEqpID, bSnd, GetStartDes(pcMixerMdl->m_emStat)));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_if_snd_ntfy);
	cMsg.SetBody(&bSnd, sizeof(bSnd));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);

	return ;
}

void CAudioMixEqp::OnForceActive( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	u8 byChnlIndx;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(byChnlIndx, ptMsg->GetBody()+sizeof(byEqpID));

	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnForceActive Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnForceActive. EqpID:%d, ChnlIndx:%d, stat:%s\n", byEqpID, byChnlIndx, GetStartDes(pcMixerMdl->m_emStat)));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_ForceActive_Cmd);
	cMsg.SetBody(&byChnlIndx, sizeof(byChnlIndx));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
	
	return ;
}

void CAudioMixEqp::OnCancelForceActive( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());

	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnForceActive Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnForceActive. EqpID:%d, stat:%s\n", byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_CancelForceActive_Cmd);
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
}

u16 CAudioMixEqp::FindSuitableMixMdl(u16 wChanLimit, u32 dwNode)
{// 在对应的apu2板卡上分配混音器
	u16 wSurperIndx = TP_INVALID_INDEX;
	u16	wMinCap = TP_APU2_MAX_CHAN_NUM;

	for (u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; wMdlIndex ++ )
	{
		if (0 != wChanLimit)
		{//取最合适的（符合通道数要求且最少）
			if ( m_atAudioMix[wMdlIndex].IsUsable() && m_atAudioMix[wMdlIndex].m_dwUserNode == dwNode)
			{
				if ( m_atAudioMix[wMdlIndex].m_wChanNum >= wChanLimit
					&& ( wMinCap > m_atAudioMix[wMdlIndex].m_wChanNum - wChanLimit ) )
				{
					wMinCap = m_atAudioMix[wMdlIndex].m_wChanNum - wChanLimit;
					wSurperIndx = wMdlIndex;
				}
			}
		}
		else
		{//取最大的（通道数最多）
			if ( m_atAudioMix[wMdlIndex].IsUsable() && m_atAudioMix[wMdlIndex].m_dwUserNode == dwNode)
			{
				if ( wMinCap == TP_APU2_MAX_CHAN_NUM )
				{
					wMinCap = m_atAudioMix[wMdlIndex].m_wChanNum;
					wSurperIndx = wMdlIndex;
				}
				
				if ( m_atAudioMix[wMdlIndex].m_wChanNum > wMinCap )
				{
					wMinCap = m_atAudioMix[wMdlIndex].m_wChanNum;
					wSurperIndx = wMdlIndex;
				}
			}
		}
	}
	
	return wSurperIndx;
}

u16 CAudioMixEqp::FindSuitableMixMdl( u16 wChanLimit )
{ // 在所有的apu2板卡上分配混音器
	u16 wSurperIndx = TP_INVALID_INDEX;
	u16	wMinCap = TP_APU2_MAX_CHAN_NUM;
	
	for (u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; wMdlIndex ++ )
	{
		if (0 != wChanLimit)
		{//取最合适的（符合通道数要求且最少）
			if ( m_atAudioMix[wMdlIndex].IsUsable())
			{
				if ( m_atAudioMix[wMdlIndex].m_wChanNum >= wChanLimit
					&& ( wMinCap > m_atAudioMix[wMdlIndex].m_wChanNum - wChanLimit ) )
				{
					wMinCap = m_atAudioMix[wMdlIndex].m_wChanNum - wChanLimit;
					wSurperIndx = wMdlIndex;
				}
			}
		}
		else
		{//取最大的（通道数最多）
			if ( m_atAudioMix[wMdlIndex].IsUsable())
			{
				if ( wMinCap == TP_APU2_MAX_CHAN_NUM )
				{
					wMinCap = m_atAudioMix[wMdlIndex].m_wChanNum;
					wSurperIndx = wMdlIndex;
				}
				
				if ( m_atAudioMix[wMdlIndex].m_wChanNum > wMinCap )
				{
					wMinCap = m_atAudioMix[wMdlIndex].m_wChanNum;
					wSurperIndx = wMdlIndex;
				}
			}
		}
	}
	
	return wSurperIndx;
}

u32 CAudioMixEqp::FindSuitableApu2(u16 wChanLimit, u16 wReqNum)
{// 寻找apu2上符合通道数量需求的混音器，哪个apu2上这样的混音器数量多且大于等于wReqNum，就选哪个apu2，并返回对应node 
	u32 dwNodeTemp = 0;
	u32 dwNode = 0;
	u16 wNumTemp = 0;
	u16 wNum = 0;

	CAudioMixModle* pMdl = NULL;
	for (u16 wMdlIndex = 0; wMdlIndex < MAX_AUDMIX_MDL_NUM; wMdlIndex ++ )
	{
		pMdl = &m_atAudioMix[wMdlIndex];
		if (pMdl->IsUsable() && pMdl->m_wChanNum >= wChanLimit)
		{
			wNum++;
		}

		if (pMdl->m_dwUserNode == m_atAudioMix[wMdlIndex+1].m_dwUserNode)
		{
			continue;
		}

		if (wNum >= wReqNum && wNum > wNumTemp)
		{
			dwNode = pMdl->m_dwUserNode;
			wNumTemp = wNum;
		}
		wNum = 0;
	}

	return dwNode;
}

void CAudioMixEqp::OnSyncChnlCmd( CTpMsg *const ptMsg )
{
	TMixSyncChnl tSync;
	TP_SAFE_CAST(tSync, ptMsg->GetBody());
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(tSync.m_abyEqpId[0]);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnSyncChnlCmd Mdl no Exist! EqpID:%d\n", tSync.m_abyEqpId[0]));	
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnSyncChnlCmd. EqpID-Chnl %d-%d, %d-%d, %d-%d\n", 
		tSync.m_abyEqpId[0], tSync.m_abyChanId[0], 
		tSync.m_abyEqpId[1], tSync.m_abyChanId[1],
		tSync.m_abyEqpId[2], tSync.m_abyChanId[2]));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_SyncChnl_Cmd);
	cMsg.SetBody(&tSync, sizeof(tSync));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
}



void CAudioMixEqp::OnSetMediaKeyNtfy( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(byEqpID));
	
	CAudioMixModle* pcMixerMdl = FindMixMdl(byEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudioMixEqp::OnSetMediaKeyNtfy Mdl no Exist! EqpID:%d\n", byEqpID));	
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqp::OnSetMediaKeyNtfy. EqpID:%d, stat:%s\n", byEqpID, GetStartDes(pcMixerMdl->m_emStat)));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_set_mediakey_ntfy);
	cMsg.SetBody(&tInfo, sizeof(tInfo));
	cMsg.Post(pcMixerMdl->m_dwUserInst, 0, UMS_EQP_APP_INST);
}



