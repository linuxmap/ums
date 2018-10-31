#include "audmixeqp.h"
#include "innereventxmpumix.h"
#include "umsxmpuinst.h"
#include "xmpuinterface.h"
#include <map>

#define XMPU_MIX_MAX_PORT_SPAN		150		//每个混音器使用150个端口
#define XMPU_N_PORT_SPAN		10					//N出通道使用10个端口
#define XMPU_N1_DEC_PORT_SPAN		70		//N1编解码间隔70个端口
#define XMPU_MIX_MAX_CHANNEL 8       //Max Channel小于8时，使用8方混音器；大于8使用192方混音器
extern std::map<u32,u32> g_mapMix; 
CAudioMixEqpHandle::CAudioMixEqpHandle( CUmsXmpuInst* pInst )
	:CEqpBaseHandle(pInst)
{

}

CAudioMixEqpHandle::~CAudioMixEqpHandle()
{

}

u32 GetMixEqpID(u32 dwHandle);

void CAudioMixEqpHandle::Init()
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < XMPU_MAX_AUDMIX_NUM; ++wIndex)
	{
		m_atMixModle[wIndex].Clear();
		m_atMixModle[wIndex].m_dwEqpID = XMPU_EQP_ID_AUD_MIX_BEG + wIndex;
	}
	m_wMixUsedNum = 0;
	m_wMix8UsedNum = 0;
}

BOOL32 CAudioMixEqpHandle::Handle( CTpMsg *const ptMsg )
{
	BOOL32 bRes = TRUE;
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();

	switch(wEvent)
	{
	case evXmpu_UmsStartMix_Rsp:
		{
			OnStartMixRsp(ptMsg);
			break;
		}
	case evUms_XmpuAddMixMember_Req:
		{
			OnAddMixMemberReq(ptMsg);
			break;
		}
	case evUms_XmpuAddMixMember_Rsp:
		{
			OnAddMixMemberRsp(ptMsg);
			break;
		}
	case evUms_XmpuDelMixMember_Req:
		{
			OnDelMixMemberReq(ptMsg);
			break;
		}
	case evXmpu_StartVac_Req:
		{
			OnStartVacReq(ptMsg);
			break;
		}
	case evXmpu_StopVar_Req:
		{
			OnStopVacReq(ptMsg);
			break;
		}
	case evXmpu_SetMixSync_Req:
		{
			OnSetSynReq(ptMsg);
			break;
		}
	case evXmpu_SetKeepTime_Req:
		{
			OnSetKeepTimeReq(ptMsg);
			break;
		}
	case evXmpu_ForceActive_Req:
		{
			OnForceActiveReq(ptMsg);
			break;
		}
	case evXmpu_VacActive_Ntf:
		{
			OnVacActiveNty(ptMsg);
			break;
		}
	case evXmpu_MixVoiceDetection_Ntf:
		{
			OnVoiceDetection(ptMsg);
			break;
		}
	case evXmpu_MixDisConnect_Nty:
		{
			OnMixDisConnect(ptMsg);
			break;
		}
	default:
		{
			bRes = FALSE;
			MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		}
		break;
	}
	return bRes;
}

BOOL32 CAudioMixEqpHandle::AssignEqpEx( TXmpuEqpParam* ptEqpParam )
{
	CHECK_XMPU_SEM;

	TXmpuMixModle* ptModle = FindIdleMixModle();
	if (ptModle == NULL)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::AssignEqpEx.mix is full!\n"));
		return FALSE;
	}

	TXmpuMixParam* ptInfo = (TXmpuMixParam*)ptEqpParam;
	//
	ptModle->m_wConfID = ptInfo->m_wConfID;
	ptModle->m_dwMediaIP = ptInfo->m_dwMediaIp;
	ptModle->m_emStat = XmpuEqpStat_Starting;
	ptModle->m_byNNum = ptInfo->m_byNNum;
	ptModle->m_byMaxChanNum = ptInfo->m_byChanNum;
	// 30000~35000 每个混音器150个，32个混音器 共占用34800 到 34800
	ptModle->m_wUmsRcvStartPort = XMPU_AUD_MIX_BEGIN_PORT + 
					(ptModle->m_dwEqpID - XMPU_EQP_ID_AUD_MIX_BEG)*XMPU_MIX_MAX_PORT_SPAN;
	AdjustAddr(ptModle);
	//出参
	ptInfo->m_ptEqp->m_dwEqpID = ptModle->m_dwEqpID;
	memcpy(ptInfo->m_atNEncRtpAddr, ptModle->m_atNEncRtpAddr, sizeof(ptModle->m_atNEncRtpAddr));
	memcpy(ptInfo->m_atNEncMiddleRtcpAddr, ptModle->m_atNEncMiddleRtcpAddr, sizeof(ptModle->m_atNEncMiddleRtcpAddr));
	memcpy(ptInfo->m_atDecMiddleRtpAddr, ptModle->m_atN1DecMiddleRtpAddr, sizeof(ptModle->m_atN1DecMiddleRtpAddr));
	memcpy(ptInfo->m_atEncMiddleRtcpAddr, ptModle->m_atN1EncMiddleRtcpAddr, sizeof(ptModle->m_atN1EncMiddleRtcpAddr));

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::AssignEqpEx. wEqpID:%d, MaxChanNum:%d, VmpStat:%s.\n", 
		ptModle->m_dwEqpID, ptModle->m_byMaxChanNum, GetXmpuEqpStatBuf(ptModle->m_emStat)));

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::AssignEqpEx. byNNum:%d, EncryptInfo(%d,%d,%s)\n", 
		ptInfo->m_byNNum,
		ptInfo->m_tEncrypt.m_emEncryptModel,
		ptInfo->m_tEncrypt.m_byKeyLen,
		ptInfo->m_tEncrypt.m_achEncKey));

	// start Mix
	if (!MediaStartMix(ptModle->m_dwHandle, ptModle->m_dwEqpID, *ptInfo))
	{
		ptModle->Clear();
		return FALSE;
	}
	if (ptModle->m_byMaxChanNum > XMPU_MIX_MAX_CHANNEL)
	{
		++m_wMixUsedNum;
	}
	else
	{
		++m_wMix8UsedNum;
	}
	
	return TRUE;
}

BOOL32 CAudioMixEqpHandle::ReleaseEqpEx( TXmpuEqpParam* ptEqpParam )
{
	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixMdl = FindMixModle(ptEqpParam->m_ptEqp->m_dwEqpID);
	if ( NULL == ptMixMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::ReleaseEqpEx. ptMixMdl Is NULL! wEqpID:%d\n", ptEqpParam->m_ptEqp->m_dwEqpID));
		return FALSE;
	}

	//状态检测
	if ( ptMixMdl->m_emStat != XmpuEqpStat_Starting && ptMixMdl->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::ReleaseEqpEx. Mix state error m_byEqpID:%d CurrStat:%s\n", 
			ptMixMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixMdl->m_emStat)));	
		return FALSE;
	}
	MediaReleaseMix(ptMixMdl->m_dwHandle);

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::ReleaseEqpEx. ConfID:%d, wEqpID:%d, MixStat:%s,\n", 
		ptMixMdl->m_wConfID, ptMixMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixMdl->m_emStat)));

	if ((ptMixMdl->m_byMaxChanNum > XMPU_MIX_MAX_CHANNEL) && (m_wMixUsedNum))
	{
		--m_wMixUsedNum;
	}
	else if((ptMixMdl->m_byMaxChanNum < XMPU_MIX_MAX_CHANNEL) && (m_wMix8UsedNum))
	{
		--m_wMix8UsedNum;
	}
	ptMixMdl->Clear();
	return TRUE;
}

void CAudioMixEqpHandle::OnStartMixRsp( CTpMsg *const ptMsg )
{
	TXmpuStartMixRsp	tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	tRes.m_dwEqpID = GetMixEqpID(tRes.m_dwHandle);
	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartMixRsp. EqpID:%d, dwHandle:%d, emRes:%d\n", 
		tRes.m_dwEqpID, tRes.m_dwHandle, tRes.m_emRes));	

	BOOL32 bRes = TRUE;
	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixMdl = FindMixModle(tRes.m_dwEqpID);

	if ( NULL == ptMixMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartMixRsp. ptMixMdl Is NULL! wEqpID:%d\n", tRes.m_dwEqpID));	
		return;
	}
	do 
	{
		if (ptMixMdl->m_emStat != XmpuEqpStat_Starting && ptMixMdl->m_emStat != XmpuEqpStat_Running)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartMixRsp. Mix state error! wEqpID:%d, Stat:%s\n", 
														ptMixMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixMdl->m_emStat)));
			bRes = FALSE;
			break;
		}

		if (tRes.m_emRes !=  StartMixRsp_Success)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartMixRsp. Mix state error! emRes:%d,wEqpID:%d\n", tRes.m_emRes, ptMixMdl->m_dwEqpID));
			bRes = FALSE;
			break;
		}

		if (!MediaGetMixNChnID(ptMixMdl->m_dwHandle, ptMixMdl->m_byNNum, ptMixMdl->m_abyNChnID))
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartMixRsp. MediaGetMixNChnID error wEqpID:%d!\n", ptMixMdl->m_dwEqpID));
			bRes = FALSE;
			break;
		}

		for (u16 wIndex = 0; wIndex < ptMixMdl->m_byNNum; ++wIndex)
		{
			if (!MediaGetMixEncAddr(ptMixMdl->m_dwHandle, ptMixMdl->m_abyNChnID[wIndex],
				ptMixMdl->m_atNEncRtcpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartMixRsp. MediaGetMixOutAddr error wEqpID:%d!\n", ptMixMdl->m_dwEqpID));
				bRes = FALSE;
				break;
			}
		}
		ptMixMdl->m_emStat = XmpuEqpStat_Running;

	} while (0);

	TXmpuStartMixNty tNty;
	tNty.m_dwEqpID = ptMixMdl->m_dwEqpID;
	tNty.m_bSuccess = bRes;
	tNty.m_byNum = ptMixMdl->m_byNNum;
	memcpy(tNty.m_atNEncRtcpAddr, ptMixMdl->m_atNEncRtcpAddr, sizeof(tNty.m_atNEncRtcpAddr));

	SendMsgToCall(ptMixMdl->m_wConfID, evXmpu_UmsStartMix_Nty, &tNty, sizeof(tNty));

	if (!bRes)
	{
		MediaReleaseMix(ptMixMdl->m_dwHandle);
		if ((ptMixMdl->m_byMaxChanNum > XMPU_MIX_MAX_CHANNEL) && (m_wMixUsedNum))
		{
			--m_wMixUsedNum;
		}
		else if((ptMixMdl->m_byMaxChanNum < XMPU_MIX_MAX_CHANNEL) && (m_wMix8UsedNum))
		{
			--m_wMix8UsedNum;
		}
		ptMixMdl->Clear();
	}

}

void CAudioMixEqpHandle::OnAddMixMemberReq( CTpMsg *const ptMsg )
{
	TXmpuMixMember tMember;
	TP_SAFE_CAST(tMember, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixerMdl = FindMixModle(tMember.m_dwEqpID);
	if (NULL == ptMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberReq Mdl no Exist! EqpID:%d-%d.\n", tMember.m_wEpID, tMember.m_wScreenIndex));	
		return ;
	}

	if ( ptMixerMdl->m_emStat != XmpuEqpStat_Starting
		&& ptMixerMdl->m_emStat != XmpuEqpStat_Running )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberReq Stat Invalid! EqpID:%d, Stat:%s, EpID:%d-%d, chanIndex:%d\n", 
			ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat), tMember.m_wEpID, tMember.m_wScreenIndex, tMember.m_byIndex));
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberReq. ConfID:%d, EqpID:%d, EPID:%d-%d, chanIndex:%d, stat:%s\n", 
		ptMixerMdl->m_wConfID, ptMixerMdl->m_dwEqpID, tMember.m_wEpID, tMember.m_wScreenIndex, tMember.m_byIndex, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));	

	MediaAddMixMember(ptMixerMdl->m_dwHandle, tMember);
	ptMixerMdl->m_byN1Num++;
	return ;
}

void CAudioMixEqpHandle::OnAddMixMemberRsp( CTpMsg *const ptMsg )
{
	HMEDIARES dwHandle;
	TXmpuAddMixMemRsp tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());
	TP_SAFE_CAST(dwHandle, ptMsg->GetBody()+ sizeof(TXmpuAddMixMemRsp));
	tRes.m_dwEqpID = GetMixEqpID(dwHandle);

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixerMdl = FindMixModle(tRes.m_dwEqpID);
	if (NULL == ptMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMember Mdl no Exist! EqpID:%d\n", tRes.m_dwEqpID));	
		return ;
	}
	BOOL32 bRes = TRUE;
	do 
	{
		if ( ptMixerMdl->m_emStat != XmpuEqpStat_Starting
			&& ptMixerMdl->m_emStat != XmpuEqpStat_Running )
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberRsp Stat Invalid! EqpID:%d, Stat:%s\n", 
				ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));
			bRes = FALSE;
			break;
		}

		if (tRes.m_emRes !=  AddMixMemRsp_Success)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberRsp. Mix state error! emRes:%d, EqpID:%d\n", 
				tRes.m_emRes, ptMixerMdl->m_dwEqpID));
			bRes = FALSE;
			break;
		}

	} while (0);

	
	
	u8 byChnID = 0;
	for (u16 wIndex = 0; wIndex < tRes.m_byNum; ++wIndex)
	{
		byChnID =  tRes.m_abyChnID[wIndex];
		do 
		{
			if (!bRes)
			{
				break;
			}

			if (byChnID>= XMPU_AUDMIX_N1_NUM)
			{
				MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberRsp. byChnID Error! byChnID:%d EqpID:%d\n", 
					byChnID, ptMixerMdl->m_dwEqpID));
				bRes = FALSE;
				break;
			}

			if (!MediaGetMixEncAddr(ptMixerMdl->m_dwHandle, byChnID,
				ptMixerMdl->m_atN1EncRtcpAddr[byChnID]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberRsp. MediaGetMixEncAddr error!EqpID:%d\n", ptMixerMdl->m_dwEqpID));
				bRes = FALSE;
				break;
			}

			if (!MediaGetMixDecAddr(ptMixerMdl->m_dwHandle, byChnID,
				ptMixerMdl->m_atN1DecRtpAddr[byChnID]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberRsp. MediaGetMixDecAddr error!EqpID:%d\n", ptMixerMdl->m_dwEqpID));
				bRes = FALSE;
				break;
			}
		} while (0);

		MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnAddMixMemberRsp. wIndex:%d, ConfID:%d, EqpID:%d,chanID:%d, stat:%s\n", 
			wIndex, ptMixerMdl->m_wConfID, ptMixerMdl->m_dwEqpID,  byChnID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));	

		TXmpuAddMixMemNty tNty;
		tNty.m_dwEqpID = tRes.m_dwEqpID;
		tNty.m_byChnID = byChnID;
		tNty.m_bSuccess = bRes;
		if (bRes)
		{
			memcpy(&tNty.m_tN1DecRtpAddr, &ptMixerMdl->m_atN1DecRtpAddr[byChnID], sizeof(tNty.m_tN1DecRtpAddr));
			memcpy(&tNty.m_tN1EncRtcpAddr, &ptMixerMdl->m_atN1EncRtcpAddr[byChnID], sizeof(tNty.m_tN1EncRtcpAddr));
		}
		else
		{
			ptMixerMdl->m_byN1Num--;
			ptMixerMdl->m_atN1DecRtpAddr[byChnID].Clear();
			ptMixerMdl->m_atN1EncRtcpAddr[byChnID].Clear();
		}

		SendMsgToCall(ptMixerMdl->m_wConfID, evUms_XmpuAddMixMember_Nty, &tNty, sizeof(tNty));
	}
	
}

void CAudioMixEqpHandle::OnDelMixMemberReq( CTpMsg *const ptMsg )
{
	u32 dwEqpID = 0;
	u8  byChnID = 0;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(byChnID, ptMsg->GetBody()+sizeof(u32));

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptModle = FindMixModle(dwEqpID);
	if ( NULL == ptModle )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnDelMixMemberReq. ptMixMdl Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if (byChnID >= XMPU_AUDMIX_N1_NUM)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnDelMixMemberReq. chnID is InValid! wEqpID:%d, chnID;%d\n", 
			ptModle->m_dwEqpID, byChnID));
		return ; 
	}

	if (ptModle->m_dwHandle == 0)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnDelMixMemberReq. dwHandle is InValid! wEqpID:%d, chnID;%d, dwHandle:%d\n", 
			ptModle->m_dwEqpID, byChnID, ptModle->m_dwHandle ));
		return ; 
	}

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnDelMixMemberReq. FastUpdate To Eqp! wConfID:%d, EqpID:%d,chnID;%d,dwHandle:%d\n", 
		ptModle->m_wConfID, ptModle->m_dwEqpID, byChnID, ptModle->m_dwHandle));

	MediaDelMixMember(ptModle->m_dwHandle, byChnID);

	ptModle->m_byN1Num--;
	ptModle->m_atN1DecRtpAddr[byChnID].Clear();
	ptModle->m_atN1EncRtcpAddr[byChnID].Clear();

}

void CAudioMixEqpHandle::OnStartVacReq( CTpMsg *const ptMsg )
{
	u32 dwEqpID = 0;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixerMdl = FindMixModle(dwEqpID);
	if (NULL == ptMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartVarReq Mdl no Exist! EqpID:%d\n", dwEqpID));	
		return ;
	}

	if ( ptMixerMdl->m_emStat != XmpuEqpStat_Starting
		&& ptMixerMdl->m_emStat != XmpuEqpStat_Running )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartVarReq Stat Invalid! EqpID:%d, Stat:%s\n", 
			ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStartVarReq. ConfID:%d, EqpID:%d, stat:%s\n", 
		ptMixerMdl->m_wConfID, ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));	

	MediaStartVac(ptMixerMdl->m_dwHandle);
}

void CAudioMixEqpHandle::OnStopVacReq( CTpMsg *const ptMsg )
{
	u32 dwEqpID = 0;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixerMdl = FindMixModle(dwEqpID);
	if (NULL == ptMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStopVacReq Mdl no Exist! EqpID:%d\n", dwEqpID));	
		return ;
	}

	if ( ptMixerMdl->m_emStat != XmpuEqpStat_Starting
		&& ptMixerMdl->m_emStat != XmpuEqpStat_Running )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStopVacReq Stat Invalid! EqpID:%d, Stat:%s\n", 
			ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnStopVacReq. ConfID:%d, EqpID:%d, stat:%s\n", 
		ptMixerMdl->m_wConfID, ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));	

	MediaStopVac(ptMixerMdl->m_dwHandle);
}

void CAudioMixEqpHandle::OnSetSynReq( CTpMsg *const ptMsg )
{
	TXmpuMixSynInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnSetAudMixSynReq.  emSynType:%d bySyn0(%d|%d), bySyn1(%d|%d), bySyn2(%d|%d)\n",
		tInfo.m_emSynType, tInfo.m_adwEqpID[0], tInfo.m_abyChanId[0],
		tInfo.m_adwEqpID[1],  tInfo.m_abyChanId[1], tInfo.m_adwEqpID[2],  tInfo.m_abyChanId[2]));	

	if (tInfo.m_emSynType >= em_Xmpu_SynIndex_End)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnSetAudMixSynReq. synIndexType error:%d\n", tInfo.m_emSynType));	
		return;
	}

	TXmpuMixModle* ptModle = NULL;
	TXmpuSynChn		atSynChn[TP_MAX_STREAMNUM];
	u16						wConfID = 0;
	CHECK_XMPU_SEM;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM;++wIndex)
	{
		ptModle = FindMixModle(tInfo.m_adwEqpID[wIndex]);
		if (NULL == ptModle)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnSetAudMixSynReq. ptMixMdl Is NULL! wIndex:%d\n", wIndex));	
			continue;
		}
		atSynChn[wIndex].m_dwEqpID = ptModle->m_dwEqpID;
		atSynChn[wIndex].m_dwHandle = ptModle->m_dwHandle;
		atSynChn[wIndex].m_bySynChn = tInfo.m_abyChanId[wIndex];
		wConfID = ptModle->m_wConfID;
	}
	
	m_pcInst->SetSynID(wConfID, tInfo.m_emSynType, atSynChn);

	return;
}

void CAudioMixEqpHandle::OnSetKeepTimeReq( CTpMsg *const ptMsg )
{
	u32 dwEqpID = 0;
	u32 dwKeepTime = 0;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(dwKeepTime, ptMsg->GetBody()+sizeof(u32));

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixerMdl = FindMixModle(dwEqpID);
	if (NULL == ptMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnSetKeepTimeReq Mdl no Exist! EqpID:%d\n", dwEqpID));	
		return ;
	}

	if ( ptMixerMdl->m_emStat != XmpuEqpStat_Starting
		&& ptMixerMdl->m_emStat != XmpuEqpStat_Running )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnSetKeepTimeReq Stat Invalid! EqpID:%d, Stat:%s\n", 
			ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnSetKeepTimeReq. ConfID:%d, EqpID:%d, dwKeepTime:%d, stat:%s\n", 
		ptMixerMdl->m_wConfID, ptMixerMdl->m_dwEqpID, dwKeepTime, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));	

	MediaSetKeepTime(ptMixerMdl->m_dwHandle, dwKeepTime);
}

void CAudioMixEqpHandle::OnForceActiveReq( CTpMsg *const ptMsg )
{
	TForceActiveInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptMixerMdl = FindMixModle(tInfo.m_dwEqpID);
	if (NULL == ptMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnForceActiveReq Mdl no Exist! EqpID:%d\n", tInfo.m_dwEqpID));	
		return ;
	}

	if ( ptMixerMdl->m_emStat != XmpuEqpStat_Starting
		&& ptMixerMdl->m_emStat != XmpuEqpStat_Running )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnForceActiveReq Stat Invalid! EqpID:%d, Stat:%s\n", 
			ptMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnForceActiveReq. ConfID:%d, EqpID:%d, byChnDI:%d, bStart:%d, stat:%s\n", 
		ptMixerMdl->m_wConfID, ptMixerMdl->m_dwEqpID, tInfo.m_byChnID, tInfo.m_bStart, GetXmpuEqpStatBuf(ptMixerMdl->m_emStat)));	

	MediaSetForceMix(ptMixerMdl->m_dwHandle, tInfo.m_byChnID, tInfo.m_bStart);
}

void CAudioMixEqpHandle::OnVacActiveNty( CTpMsg *const ptMsg )
{
	TXmpuVacActiveNty tNty;
	HMEDIARES dwHandle;
	TP_SAFE_CAST(tNty, ptMsg->GetBody());
	TP_SAFE_CAST(dwHandle, ptMsg->GetBody()+ sizeof(TXmpuVacActiveNty));
	tNty.m_dwEqpID = GetMixEqpID(dwHandle);

	CHECK_XMPU_SEM;
	TXmpuMixModle* pcMixerMdl = FindMixModle(tNty.m_dwEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnVacActiveNty Mdl no Exist! EqpID:%d\n", tNty.m_dwEqpID));	
		return ;
	}

	if ( pcMixerMdl->m_emStat != XmpuEqpStat_Starting
		&& pcMixerMdl->m_emStat != XmpuEqpStat_Running )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnVacActiveNty Stat Invalid! EqpID:%d, Stat:%s\n", 
			pcMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(pcMixerMdl->m_emStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnVacActiveNty.EqpID:%d bychnID:%d, wConfID:%d \n", 
		pcMixerMdl->m_dwEqpID, tNty.m_byChnID, pcMixerMdl->m_wConfID));

	SendMsgToCall(pcMixerMdl->m_wConfID, evXmpu_VacActive_Ntf, &tNty, sizeof(tNty));
}

void CAudioMixEqpHandle::OnVoiceDetection( CTpMsg *const ptMsg )
{
	TVoiceDetectionNty tNty;
	TP_SAFE_CAST(tNty, ptMsg->GetBody());

	HMEDIARES dwHandle;
	TP_SAFE_CAST(dwHandle, ptMsg->GetBody()+ sizeof(TVoiceDetectionNty));
	tNty.m_dwEqpID = GetMixEqpID(dwHandle);

	MdlHint(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnVoiceDetection.EqpID:%d byNum:%d,bychnID:(%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|) \n", 
		tNty.m_dwEqpID, tNty.m_byNum, tNty.m_abyChanId[0],tNty.m_abyChanId[1], tNty.m_abyChanId[2], tNty.m_abyChanId[3],
		tNty.m_abyChanId[4], tNty.m_abyChanId[5], tNty.m_abyChanId[6], tNty.m_abyChanId[7], tNty.m_abyChanId[8],
		tNty.m_abyChanId[9]));

	CHECK_XMPU_SEM;
	TXmpuMixModle* pcMixerMdl = FindMixModle(tNty.m_dwEqpID);
	if (NULL == pcMixerMdl)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnVoiceDetection Mdl no Exist! EqpID:%d\n", tNty.m_dwEqpID));	
		return ;
	}

	if ( pcMixerMdl->m_emStat != XmpuEqpStat_Starting
		&& pcMixerMdl->m_emStat != XmpuEqpStat_Running )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnVoiceDetection Stat Invalid! EqpID:%d, Stat:%s\n", 
			pcMixerMdl->m_dwEqpID, GetXmpuEqpStatBuf(pcMixerMdl->m_emStat)));
		return ;
	}

	SendMsgToCall(pcMixerMdl->m_wConfID, evXmpu_MixVoiceDetection_Ntf, &tNty, sizeof(tNty));
}

// 每个混音器150个 N出 0~9  N-1路: 10~149
void CAudioMixEqpHandle::AdjustAddr( TXmpuMixModle* ptModle )
{
	u16 wIndex = 0;
	u16 wPort = 0;
	for(wIndex = 0; wIndex < UMS_AUDMIX_N_OUT_NUM; ++wIndex)
	{// 0-4 N出rtp 5~9:N出中转rtcp
		wPort = ptModle->m_wUmsRcvStartPort + wIndex;
		ptModle->m_atNEncRtpAddr[wIndex].SetAddr(ptModle->m_dwMediaIP, wPort);
		wPort = ptModle->m_wUmsRcvStartPort + wIndex + 5;
		ptModle->m_atNEncMiddleRtcpAddr[wIndex].SetAddr(ptModle->m_dwMediaIP, wPort);
	}

	for(wIndex = 0; wIndex < XMPU_AUDMIX_N1_NUM; ++wIndex)
	{
		wPort = ptModle->m_wUmsRcvStartPort + wIndex + XMPU_N_PORT_SPAN;
		ptModle->m_atN1DecMiddleRtpAddr[wIndex].SetAddr(ptModle->m_dwMediaIP, wPort);

		wPort = ptModle->m_wUmsRcvStartPort + wIndex + XMPU_N_PORT_SPAN + XMPU_N1_DEC_PORT_SPAN;
		ptModle->m_atN1EncMiddleRtcpAddr[wIndex].SetAddr(ptModle->m_dwMediaIP, wPort);
	}
}

void CAudioMixEqpHandle::OnMixDisConnect( CTpMsg *const ptMsg )
{
	HMEDIARES dwHandle = 0;
	TP_SAFE_CAST(dwHandle, ptMsg->GetBody());
	u32	dwEqpID = GetMixEqpID(dwHandle);

	CHECK_XMPU_SEM;
	TXmpuMixModle* ptModle = FindMixModle(dwEqpID);
	if ( NULL == ptModle )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioMixEqpHandle::OnMixDisConnect, ptMixChn Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if (ptModle->m_emStat == XmpuEqpStat_Starting || ptModle->m_emStat == XmpuEqpStat_Running)
	{
		SendMsgToCall(ptModle->m_wConfID, evXmpu_MixDisConnect_Nty, &dwEqpID, sizeof(dwEqpID));
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioMixEqpHandle::OnMixDisConnect. FastUpdate To Eqp! wConfID:%d, EqpID:%d\n", 
		ptModle->m_wConfID, ptModle->m_dwEqpID));

	g_mapMix.erase(dwHandle);
	if ((ptModle->m_byMaxChanNum > XMPU_MIX_MAX_CHANNEL) && (m_wMixUsedNum))
	{
		--m_wMixUsedNum;
	}
	else if((ptModle->m_byMaxChanNum < XMPU_MIX_MAX_CHANNEL) && (m_wMix8UsedNum))
	{
		--m_wMix8UsedNum;
	}
	ptModle->Clear();

}

TXmpuMixModle* CAudioMixEqpHandle::FindIdleMixModle()
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < XMPU_MAX_AUDMIX_NUM; ++wIndex)
	{
		if (m_atMixModle[wIndex].m_emStat == XmpuEqpStat_Idle)
		{
			return &m_atMixModle[wIndex];
		}
	}

	return NULL;
}

TXmpuMixModle* CAudioMixEqpHandle::FindMixModle( u32 dwEqpID )
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < XMPU_MAX_AUDMIX_NUM; ++wIndex)
	{
		if (m_atMixModle[wIndex].m_dwEqpID == dwEqpID)
		{
			return &m_atMixModle[wIndex];
		}
	}

	return NULL;
}

BOOL32 CAudioMixEqpHandle::StopConf( u16 wConfID )
{
	for(u16 wIndex = 0; wIndex < XMPU_MAX_AUDMIX_NUM; ++wIndex)
	{
		if (m_atMixModle[wIndex].m_wConfID == wConfID)
		{
			if (!m_atMixModle[wIndex].m_dwHandle)
			{
				MediaReleaseMix(m_atMixModle[wIndex].m_dwHandle);
			}

			m_atMixModle[wIndex].Clear();
		}
	}
	return TRUE;
}

void CAudioMixEqpHandle::SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen )
{
	if ( wConfID == TP_INVALID_INDEX )
	{
		return ;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post( MAKEIID( AID_UMSCONFMGR, wConfID) );
}

void CAudioMixEqpHandle::Show()
{

	msgprintnotime("AudMixEqp Info : \n");
	TXmpuMixModle* ptMdl = NULL;

	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_AUDMIX_NUM; ++wMdlIndex)
	{
		ptMdl = &m_atMixModle[wMdlIndex];
		if (ptMdl->m_emStat == XmpuEqpStat_Idle)
		{
			continue;
		}

		msgprintnotime("	Index:%d, EqpID:%d, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", UmsStartPort:%d, Stat:%s, MaxChanNum:%d, byN1Num:%d, byNNum:%d\n",
			wMdlIndex, ptMdl->m_dwEqpID, ptMdl->m_dwHandle, ptMdl->m_wConfID,Tpu32ToIP(ptMdl->m_dwMediaIP), 
			ptMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptMdl->m_emStat), ptMdl->m_byMaxChanNum, ptMdl->m_byN1Num, ptMdl->m_byNNum);

		u16 wIndex = 0;
		for(wIndex = 0; wIndex < ptMdl->m_byN1Num; ++wIndex)
		{
			msgprintnotime("		N_1 Addr:  wIndex:%d, DecMiddleRtp (IP:"TPIPFORMAT", Port:%d), DecRtp (IP:"TPIPFORMAT", Port:%d), EncMiddleRtcp(IP:"TPIPFORMAT", Port:%d), EncRtcp(IP:"TPIPFORMAT", Port:%d)\n",
				wIndex, Tpu32ToIP( ptMdl->m_atN1DecMiddleRtpAddr[wIndex].GetIP()), ptMdl->m_atN1DecMiddleRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP( ptMdl->m_atN1DecRtpAddr[wIndex].GetIP()), ptMdl->m_atN1DecRtpAddr[wIndex].GetPort(),
				Tpu32ToIP( ptMdl->m_atN1EncMiddleRtcpAddr[wIndex].GetIP()), ptMdl->m_atN1EncMiddleRtcpAddr[wIndex].GetPort(), 
				Tpu32ToIP( ptMdl->m_atN1EncRtcpAddr[wIndex].GetIP()), ptMdl->m_atN1EncRtcpAddr[wIndex].GetPort());
		}

		for(wIndex = 0; wIndex < ptMdl->m_byNNum; ++wIndex)
		{
			msgprintnotime("		N Addr:windex:%d, byNChnID:%d, EncRtp(IP:"TPIPFORMAT", Port:%d), EncMiddleRtcp (IP:"TPIPFORMAT", Port:%d), EncRtcp(IP:"TPIPFORMAT", Port:%d)\n",
				wIndex, ptMdl->m_abyNChnID[wIndex], 
				Tpu32ToIP( ptMdl->m_atNEncRtpAddr[wIndex].GetIP()), ptMdl->m_atNEncRtpAddr[wIndex].GetPort(),
				Tpu32ToIP( ptMdl->m_atNEncMiddleRtcpAddr[wIndex].GetIP()), ptMdl->m_atNEncMiddleRtcpAddr[wIndex].GetPort(), 
				Tpu32ToIP( ptMdl->m_atNEncRtcpAddr[wIndex].GetIP()), ptMdl->m_atNEncRtcpAddr[wIndex].GetPort());
		}
	}

}

void CAudioMixEqpHandle::ShowAll()
{

	msgprintnotime("AudMixEqp Info : \n");
	TXmpuMixModle* ptMdl = NULL;

	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_AUDMIX_NUM; ++wMdlIndex)
	{
		ptMdl = &m_atMixModle[wMdlIndex];
		msgprintnotime("	Index:%d, EqpID:%d, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", UmsStartPort:%d, Stat:%s, MaxChanNum:%d, byN1Num:%d, byNNum:%d\n",
			wMdlIndex, ptMdl->m_dwEqpID, ptMdl->m_dwHandle, ptMdl->m_wConfID,Tpu32ToIP(ptMdl->m_dwMediaIP), 
			ptMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptMdl->m_emStat), ptMdl->m_byMaxChanNum, ptMdl->m_byN1Num, ptMdl->m_byNNum);

		u16 wIndex = 0;
		for(wIndex = 0; wIndex < ptMdl->m_byN1Num; ++wIndex)
		{
			msgprintnotime("		N_1 Addr:  wIndex:%d, DecMiddleRtp (IP:"TPIPFORMAT", Port:%d), DecRtp (IP:"TPIPFORMAT", Port:%d), EncMiddleRtcp(IP:"TPIPFORMAT", Port:%d), EncRtcp(IP:"TPIPFORMAT", Port:%d)\n",
				wIndex, Tpu32ToIP( ptMdl->m_atN1DecMiddleRtpAddr[wIndex].GetIP()), ptMdl->m_atN1DecMiddleRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP( ptMdl->m_atN1DecRtpAddr[wIndex].GetIP()), ptMdl->m_atN1DecRtpAddr[wIndex].GetPort(),
				Tpu32ToIP( ptMdl->m_atN1EncMiddleRtcpAddr[wIndex].GetIP()), ptMdl->m_atN1EncMiddleRtcpAddr[wIndex].GetPort(), 
				Tpu32ToIP( ptMdl->m_atN1EncRtcpAddr[wIndex].GetIP()), ptMdl->m_atN1EncRtcpAddr[wIndex].GetPort());
		}

		for(wIndex = 0; wIndex < ptMdl->m_byNNum; ++wIndex)
		{
			msgprintnotime("		N Addr:windex:%d, byNChnID:%d, EncRtp(IP:"TPIPFORMAT", Port:%d), EncMiddleRtcp (IP:"TPIPFORMAT", Port:%d), EncRtcp(IP:"TPIPFORMAT", Port:%d)\n",
				wIndex, ptMdl->m_abyNChnID[wIndex], 
				Tpu32ToIP( ptMdl->m_atNEncRtpAddr[wIndex].GetIP()), ptMdl->m_atNEncRtpAddr[wIndex].GetPort(),
				Tpu32ToIP( ptMdl->m_atNEncMiddleRtcpAddr[wIndex].GetIP()), ptMdl->m_atNEncMiddleRtcpAddr[wIndex].GetPort(), 
				Tpu32ToIP( ptMdl->m_atNEncRtcpAddr[wIndex].GetIP()), ptMdl->m_atNEncRtcpAddr[wIndex].GetPort());
		}
	}

}
