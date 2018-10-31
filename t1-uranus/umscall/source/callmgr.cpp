#include "callmgr.h"
#include "umsconfinst.h"
#include "callnodemgr.h"
#include "umsstackinterface.h"
#include "innereventumsconf.h"
#include "innereventumscall.h"
#include "eventoutumscall.h"
#include "eventoutsipadapter.h"
#include "tvwallmgr.h"
#include "umsdiscussnew.h"
#include "umsrollcall.h"
#include "umseapu.h"
#include "umsconfigex.h"
#include "umsapi.h"
#include "umsreg.h"
#include "nodefsm.h"
#include "pollmgr.h"
#include "umsaudmix.h"
#include "eventoutumsmcucasecade.h"

CCallMgr::CCallMgr(CUmsConfInst* pcConf)
:CTpHandler(pcConf)
,m_pcConf(pcConf)
,m_bIsChair(TRUE)
{
	
}

CCallMgr::~CCallMgr()
{
	
}

void CCallMgr::StopConf()
{
	m_bIsChair = TRUE;
}

BOOL32 CCallMgr::Handler( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	return FALSE;
}

BOOL32 CCallMgr::HandlerFromStack(TUmsHandle& tHandle, u16 wEvent, u8* pData)
{
	switch ( wEvent )
	{
	case ev_UmsInviteCnsByAlias_Cmd:
		OnCallEp(tHandle, pData);
		break;
	case ev_UmsInviteCnsByEpId_Cmd:
		OnCallExistEpFromCns(tHandle, pData);
		break;
	case evtp_Conf_CallExistEPTr_cmd:
		OnCallExistEpFromCascade(tHandle, pData);
		break;
	case ev_UmsHangupCns_Cmd:
		OnConfDropEpFromCns(tHandle, pData);
		break;
	case evtp_Conf_DropEPTr_cmd:
		OnConfDropEpFromCascade(tHandle, pData);
		break;
	case evtp_Conf_EpCallInfo_Update:
		OnUpdateEpCallInfo(tHandle, *(TConfNodeCallUpdateTrList*)pData);
		break;
	case evtp_Conf_EpChanInfo_Update:
		OnUpdateEpChanInfo(tHandle, *(TConfNodeChanUpdateTrList*)pData);
		break;
	case evtp_Conf_EpInfo_Del:		
		OnDelEpNode(tHandle, pData);
		break;
	case evtp_CnsJoinConf_Ack:
		OnCnsJoinConf(tHandle,pData);
		break;
	// 切源 远遥通知
	case evtp_Conf_EpVidFeccInfo_Update:
		OnUpdateEpVidFeccInfo(tHandle, *(TConfEpVidFeccList*)pData);
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

BOOL32 CCallMgr::HandlerFromUmc(CTpMsg *const ptMsg)
{
	switch (ptMsg->GetEvent())
	{
	case evtp_DropEp_cmd:
		{
			OnConfDropEpFromUmc(ptMsg);
		}
		break;
	case evtp_CallExistEP_cmd:
		{
			OnConfCallEpFromUmc(ptMsg);
		}
		break;
	case evtp_CallEP_cmd:
		{
			OnConfInviteEpFromUmc(ptMsg);
		}
		break;
	case evtp_UmsJoinConf_Ack:
		{
			OnConfJoinEpFromUmc(ptMsg);
		}
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

static u32 GetLocalOutDsIp(TIpmaskinfo* ptInfo, u32 dwDstIp)
{
	if (NULL == ptInfo)
	{
		return 0;
	}

	u32 dwRetIp = 0;
	if (ptInfo->IsValid())
	{
		if (dwDstIp)
		{
			dwRetIp = ptInfo->GetSameNetWork(dwDstIp);
			if (dwRetIp)
			{
				return dwRetIp;
			}
		}

		if (ptInfo->m_dwOutIp)
		{
			return ptInfo->m_dwOutIp;
		}
	}
	return 0;
}


BOOL32 CCallMgr::MakeCallInfo(TMakeCallPara& tCallPara, TCapNode& tRmtNode, BOOL32 bIsAnswerCall)
{
	tCallPara.m_tCallInfo.m_emTpProtocol = tRmtNode.m_emCallProtocol;
	
	// 将本地的码流密钥带下去协商
	tCallPara.m_tCallInfo.m_tEncrypt = m_pcConf->GetConfEncryptInfo();

	//会议码率，第一路和第二路之合

	u16 wMainBitRate = localmax(m_pcConf->m_tConfBaseInfo.m_wConfBitRate, m_pcConf->m_tConfBaseInfo.m_wBpConfBitRate);
	u16 wMinorBitRate = localmax(m_pcConf->m_tConfBaseInfo.m_wHpDualBitRate, m_pcConf->m_tConfBaseInfo.m_wBpDualBitRate);
	tCallPara.m_tCallInfo.m_wBitRate = wMainBitRate * TP_MAX_STREAMNUM + wMinorBitRate; 
	
	if (bIsAnswerCall)
	{
		tCallPara.m_tCallInfo.m_tSrcAddr = tRmtNode.m_tCalledAddr;
		tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.SetAlias(m_pcConf->m_tConfBaseInfo.m_achConfName);
		tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.SetAlias(m_pcConf->m_tConfBaseInfo.m_achConfE164);
		tCallPara.m_tCallInfo.m_tDestAddr.m_byCallType = tRmtNode.m_tCalledAddr.m_byCallType;
		// 区分是回应平台过来的呼叫还是终端过来的呼叫
		tCallPara.m_tCallInfo.m_emTpCallType = tRmtNode.m_wEpID == CALLER_EP_INDEX ? emTpAnswerUms: emTpAnswerCns;
	}
	else
	{
	 	tCallPara.m_tCallInfo.m_tSrcAddr.m_tAlias.SetAlias(m_pcConf->m_tConfBaseInfo.m_achConfName);
		tCallPara.m_tCallInfo.m_tSrcAddr.m_tE164.SetAlias(m_pcConf->m_tConfBaseInfo.m_achConfE164);
		tCallPara.m_tCallInfo.m_tSrcAddr.m_byCallType = tRmtNode.m_tCalledAddr.m_byCallType;
  		tCallPara.m_tCallInfo.m_tDestAddr = tRmtNode.m_tCalledAddr;
		tCallPara.m_tCallInfo.m_emTpCallType = emTpInvite;
		tCallPara.m_tCallInfo.m_bIsCasecadeMcuOn = CUmsConfigEx::GetInstance()->IsCasecadeMcuOn();
	}
	TUmsNodeCapset* ptCap = &tCallPara.m_tCapSet;
	
	ptCap->m_wVidEncNum = TP_MAX_STREAMNUM;
	ptCap->m_wVidDecNum = TP_MAX_STREAMNUM;
	ptCap->m_wAudEncNum = TP_MAX_STREAMNUM;
	ptCap->m_wAudDecNum = TP_MAX_STREAMNUM;

	u16 wIndex = 0;
	for (wIndex = 0; wIndex < m_pcConf->m_tConfBaseInfo.m_wMainNum; ++wIndex)
	{
		TUmsVidFormat& tFormat = m_pcConf->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex];
		if (emTPVResEnd == tFormat.m_emRes)
		{
			break;
		}

		TUmsVidFormat* ptVidCap = NULL;
		if (emTPH264HP == tFormat.m_emQualityLvl)
		{
			ptVidCap = &ptCap->m_tVidRcvCap.m_tHp;
		}
		else
		{
			ptVidCap = &ptCap->m_tVidRcvCap.m_tBp;
		}

		if (CTpTypeAdpt::ResolutionMaxOpr(tFormat.m_emRes,  ptVidCap->m_emRes))
		{
			ptVidCap->m_emRes = tFormat.m_emRes;
			ptVidCap->m_wFrameRate = tFormat.m_wFrameRate;
			ptVidCap->m_wBitrate = tFormat.m_wBitrate;
		}
		else if (CTpTypeAdpt::ResolutionEqualOpr(tFormat.m_emRes,  ptVidCap->m_emRes))
		{
			if (tFormat.m_wFrameRate > ptVidCap->m_wFrameRate)
			{
				ptVidCap->m_wFrameRate = tFormat.m_wFrameRate;
				ptVidCap->m_wBitrate = tFormat.m_wBitrate;
			}
		}
		ptCap->m_tVidRcvCap.m_tHp.m_wBitrate = m_pcConf->m_tConfBaseInfo.m_wConfBitRate;
		ptCap->m_tVidRcvCap.m_tBp.m_wBitrate = m_pcConf->m_tConfBaseInfo.m_wBpConfBitRate;

		memcpy(&ptCap->m_tVidSndCap.m_tHp, &ptCap->m_tVidRcvCap.m_tHp, sizeof(TUmsVidFormat));
		memcpy(&ptCap->m_tVidSndCap.m_tBp, &ptCap->m_tVidRcvCap.m_tBp, sizeof(TUmsVidFormat));
	}
	MakeAudCap(ptCap->m_tAudSndCap);
	MakeAudCap(ptCap->m_tAudRcvCap);
	
	CLocalChanAddrListItor ptChanAddr;

	TIpmaskinfo* ptInfo = CUmsConfInst::m_tMediaNetWorkManger.Get(tRmtNode.m_tMediaEqp.m_dwEqpNode);
	u32 dwMediaIp = 0;
	BOOL32 bResetIp = FALSE;
	u32 dwDstIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
	if (NULL != ptInfo)
	{
		dwMediaIp = GetLocalOutDsIp(ptInfo, dwDstIp);
		if (dwMediaIp)
		{
			bResetIp = TRUE;
		}
		tpHint(Ums_Mdl_Call, "[MakeCallInfo] call ep GetLocalOutDsIp, dwMediaIp:"TPIPFORMAT".\n", u32ToIP(dwMediaIp));
	}

	if (0 == dwMediaIp)
	{
		dwMediaIp = tRmtNode.m_tMediaEqp.m_dwEqpIp;
	}

	if (bResetIp)
	{
		tRmtNode.ResetIpForRes(dwMediaIp);
	}

	tpHint(Ums_Mdl_Call, "[MakeCallInfo] tRmtNode m_byCallType:%d, dwIp:"TPIPFORMAT", dwMediaIp:"TPIPFORMAT".\n", 
		tCallPara.m_tCallInfo.m_tDestAddr.m_byCallType, u32ToIP(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP), u32ToIP(dwMediaIp));


	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{//调整部分特定端口
		
		ptChanAddr = tRmtNode.m_aptChanAddr[wIndex];

		ptCap->m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tVid.m_tRtpAddr.m_wPort);
		ptCap->m_atVidDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tVid.m_tRtcpForRcv.m_wPort);
		ptCap->m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tVid.m_tRtcpForRcv.m_wPort);
		tRmtNode.m_tRmtChan.m_atVidDec[wIndex].m_emChanState = EmChanMaking;
		
		ptCap->m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tAud.m_tRtpAddr.m_wPort);
		ptCap->m_atAudDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tAud.m_tRtcpForRcv.m_wPort);
		ptCap->m_atAudDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tAud.m_tRtcpForRcv.m_wPort);
		tRmtNode.m_tRmtChan.m_atAudDec[wIndex].m_emChanState = EmChanMaking;
		
		ptCap->m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tVid.m_tRtcpForSnd.m_wPort);
		tRmtNode.m_tRmtChan.m_atVidEnc[wIndex].m_emChanState = EmChanMaking;

		ptCap->m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, ptChanAddr->m_tAud.m_tRtcpForSnd.m_wPort);
		tRmtNode.m_tRmtChan.m_atAudEnc[wIndex].m_emChanState = EmChanMaking;
		
		//小码流
		ptCap->m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwMediaIp, tRmtNode.m_aptSmallChanAddr[wIndex]->m_tRtpAddr.m_wPort);
		ptCap->m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwMediaIp, tRmtNode.m_aptSmallChanAddr[wIndex]->m_tRtcpForRcv.m_wPort);
	 	ptCap->m_atSmallVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, tRmtNode.m_aptSmallChanAddr[wIndex]->m_tRtcpForRcv.m_wPort);
		
		ptCap->m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, tRmtNode.m_aptSmallChanAddr[wIndex]->m_tRtcpForSnd.m_wPort);
	}
	
	//混音
	ptCap->m_tAudMixDec.m_tChanAddr.m_tRtpAddr.SetAddr(dwMediaIp, tRmtNode.m_ptMixAddr->m_tRtpAddr.m_wPort);
	ptCap->m_tAudMixDec.m_tChanAddr.m_tRtcpAddr.SetAddr(dwMediaIp, tRmtNode.m_ptMixAddr->m_tRtcpForRcv.m_wPort);
 	ptCap->m_tAudMixDec.m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, tRmtNode.m_ptMixAddr->m_tRtcpForRcv.m_wPort);
	ptCap->m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwMediaIp, tRmtNode.m_ptMixAddr->m_tRtcpForSnd.m_wPort);
	

	m_pcConf->m_tConfBaseInfo.m_atTpMinorVideoRes[wIndex];

	//双流能力
	u16 wMaxBitRate = localmax(m_pcConf->m_tConfBaseInfo.m_wHpDualBitRate, m_pcConf->m_tConfBaseInfo.m_wBpDualBitRate);
	TUmsDualCapsetMc* ptDualCap = &tCallPara.m_tDualCapSet;
	ptDualCap->m_wMaxBitRate = wMaxBitRate;
	
	MakeSecVidCap(ptDualCap->m_tVidRcvCap, ptDualCap->m_tVidSndCap);
	MakeAudCap(ptDualCap->m_tAudCap);
	
	//视频接收
	ptDualCap->m_tVidDec.m_tChanAddr.m_tRtpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tVid.m_tRtpAddr.m_wPort);
	ptDualCap->m_tVidDec.m_tChanAddr.m_tRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tVid.m_tRtcpForRcv.m_wPort);
	ptDualCap->m_tVidDec.m_tChanAddr.m_tBackRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tVid.m_tRtcpForRcv.m_wPort);
	
	//音频接收
	ptDualCap->m_tAudDec.m_tChanAddr.m_tRtpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tAud.m_tRtpAddr.m_wPort);
	ptDualCap->m_tAudDec.m_tChanAddr.m_tRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tAud.m_tRtcpForRcv.m_wPort);
	ptDualCap->m_tAudDec.m_tChanAddr.m_tBackRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tAud.m_tRtcpForRcv.m_wPort);
	
	//发送
	ptDualCap->m_tVidEnc.m_tChanAddr.m_tRtpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tVid.m_tRtpAddr.m_wPort);
	ptDualCap->m_tVidEnc.m_tChanAddr.m_tRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tVid.m_tRtcpForSnd.m_wPort);
	ptDualCap->m_tVidEnc.m_tChanAddr.m_tBackRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tVid.m_tRtcpForSnd.m_wPort);
	
	ptDualCap->m_tAudEnc.m_tChanAddr.m_tRtpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tAud.m_tRtpAddr.m_wPort);
	ptDualCap->m_tAudEnc.m_tChanAddr.m_tRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tAud.m_tRtcpForSnd.m_wPort);
	ptDualCap->m_tAudEnc.m_tChanAddr.m_tBackRtcpAddr.SetAddr( dwMediaIp, tRmtNode.m_ptDualAddr->m_tAud.m_tRtcpForSnd.m_wPort);
	
	return TRUE;
}
 
void CCallMgr::MakeSecVidCap(TUmsVidCapParam& tRcv, TUmsVidCapParam& tSnd)
{
	TUmsVidFormat* ptHp = NULL;
	TUmsVidFormat* ptBp = NULL;
	for (u16 wIndex = 0; wIndex < m_pcConf->m_tConfBaseInfo.m_wMinorNum; ++wIndex)
	{//找出会议模板中双流能力最高的HP和BP,发送和接收能力一致
		TUmsVidFormat& tFormat = m_pcConf->m_tConfBaseInfo.m_atTpMinorVideoRes[wIndex];
		if (emTPVResEnd == tFormat.m_emRes)
		{
			break;
		}
		
		if (emTPH264HP == tFormat.m_emQualityLvl)
		{
			if (NULL == ptHp)
			{
				ptHp = &tFormat;
			}
			else
			{
				if (tFormat.m_emRes == ptHp->m_emRes)
				{
					if (tFormat.m_wFrameRate >= ptHp->m_wFrameRate)
					{
						ptHp = &tFormat;
					}
				}
				if (CTpTypeAdpt::CapMaxOpr(&tFormat, ptHp))
				{
					ptHp = &tFormat;
				}
			}
		}
		else
		{
			if (NULL == ptBp)
			{
				ptBp = &tFormat;
			}
			else
			{
				if (tFormat.m_emRes == ptBp->m_emRes)
				{
					if (tFormat.m_wFrameRate >= ptBp->m_wFrameRate)
					{
						ptBp = &tFormat;
					}
				}
				if (CTpTypeAdpt::CapMaxOpr(&tFormat, ptBp))
				{
					ptBp = &tFormat;
				}
			}
		}
	}
	if (NULL != ptHp)
	{
		memcpy(&tSnd.m_tHp, ptHp, sizeof(TUmsVidFormat));
		if (NULL != ptBp)
		{
			memcpy(&tSnd.m_tBp, ptBp, sizeof(TUmsVidFormat));
		}
		else
		{
			tSnd.m_tBp.m_emRes = emTPVResEnd;
		}
	}
	else
	{
		tSnd.m_tHp.m_emRes = emTPVResEnd;
		if (NULL != ptBp)
		{
			memcpy(&tSnd.m_tBp, ptBp, sizeof(TUmsVidFormat));
		}
		else
		{
			tSnd.m_tBp.m_emRes = emTPVResEnd;
		}
	}
	tSnd.m_tHp.m_wBitrate = m_pcConf->m_tConfBaseInfo.m_wHpDualBitRate;
	tSnd.m_tBp.m_wBitrate = m_pcConf->m_tConfBaseInfo.m_wBpDualBitRate;
	//发送
	memcpy(&tRcv, &tSnd, sizeof(TUmsVidCapParam));
}

void CCallMgr::MakeAudCap(TUmsAudCap& tCap)
{
	memcpy(tCap.m_atAudFmt, m_pcConf->m_tConfBaseInfo.m_atAudFmt, sizeof(TUmsAudFormat)*m_pcConf->m_tConfBaseInfo.m_wAudFmtNum);
	tCap.m_wAudFmtNum = m_pcConf->m_tConfBaseInfo.m_wAudFmtNum;

	for( u16 wIndex = 0; wIndex < m_pcConf->m_tConfBaseInfo.m_wAudFmtNum; wIndex ++ )
	{
		tCap.m_atAudFmt[wIndex].m_byReserve1 = CTpTypeAdpt::GetAudPayloadValue(tCap.m_atAudFmt[wIndex].m_emFormat);
	}
}
BOOL32 CCallMgr::MakeCascadeChair(TCapNode& tRmtNode)
{
	tRmtNode.m_ptCasCadeChairAddr = CUmsConfInst::m_cCascadeChairAddrMgr.AllocNode();
	if (tRmtNode.m_ptCasCadeChairAddr == NULL)
	{
		MdlError(Ums_Mdl_Call, ("MakeCascadeChair. Assign CascadeChair Failed, ConfID:%d, wEpID:%d\n", m_pcConf->GetInsID(), tRmtNode.m_wEpID));
		return FALSE;
	}

	TChanRcvAddr* ptVirLocalNode;
	u16 wChanIndex = 0;
	
	u32 dwEqpIP = tRmtNode.m_tMediaEqp.m_dwEqpIp;
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptVirLocalNode = &tRmtNode.m_ptCasCadeChairAddr->m_atVid[wChanIndex];
		ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);
	}
	
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptVirLocalNode = &tRmtNode.m_ptCasCadeChairAddr->m_atAud[wChanIndex];	
		ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);		
		
	}
	//混音
	ptVirLocalNode = &tRmtNode.m_ptCasCadeChairAddr->m_tMixAud;
	ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);

	//讨论内单屏广播 - vid
	ptVirLocalNode = &tRmtNode.m_ptCasCadeChairAddr->m_tDisSingleVid;
	ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);

	//讨论内单屏广播 - aud
	ptVirLocalNode = &tRmtNode.m_ptCasCadeChairAddr->m_tDisSingleAud;
	ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);

	TCascadeOpenChanCmd tViewCmd;

	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		tViewCmd.m_atVidAddr[wIndex].m_tRtpAddr      = tRmtNode.m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtpAddr;
		tViewCmd.m_atVidAddr[wIndex].m_tBackRtcpAddr = tRmtNode.m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtcpForSnd;

		tViewCmd.m_atAudAddr[wIndex].m_tBackRtcpAddr = tRmtNode.m_ptCasCadeChairAddr->m_atAud[wIndex].m_tRtcpForSnd;

		tViewCmd.m_abVidOpen[wIndex] = TRUE;
		tViewCmd.m_abAudOpen[wIndex] = TRUE;
	}
	//主席三屏混音固定打开
	tViewCmd.m_bMixAudOpen = TRUE;
	tViewCmd.m_tMixAudAddr.m_tBackRtcpAddr = tRmtNode.m_ptCasCadeChairAddr->m_tMixAud.m_tRtcpForSnd;

	//讨论内单屏广播 - vid  固定打开
	tViewCmd.m_bDisSingleVid = TRUE;
	tViewCmd.m_tDisSingleVid.m_tBackRtcpAddr = tRmtNode.m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtcpForSnd;
	//讨论内单屏广播 - aud  固定打开
	tViewCmd.m_bDisSingleAud = TRUE;
	tViewCmd.m_tDisSingleAud.m_tBackRtcpAddr = tRmtNode.m_ptCasCadeChairAddr->m_tDisSingleAud.m_tRtcpForSnd;

	TUmsHandle tOutHandle;
	m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tRmtNode.m_wEpID);
	UmsSendConfCtrl(tOutHandle, evtp_cascade_OpenChairChan_cmd, &tViewCmd, sizeof(tViewCmd));
	return TRUE;
}

BOOL32 CCallMgr::AnswerCascadeChair(TCascadeOpenChanCmd* ptCmd)
{
	TCapNode* ptChair = m_pcConf->m_pcNodeMgr->GetCaller();
	TCascadeOpenChanAck tViewAck;
	TUmsHandle tOutHandle;
	m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptChair->m_wEpID);
	
	//如果已经打开，则返回失败
	if (ptChair->m_ptCasCadeChairAddr != NULL)
	{		
		MdlError(Ums_Mdl_Call, ("AnswerCascadeChair. Assign CascadeChair Failed, ConfID:%d\n", m_pcConf->GetInsID()));
		UmsSendConfCtrl(tOutHandle, evtp_cascade_OpenChairChan_ack, &tViewAck, sizeof(tViewAck));
		return FALSE;
	}

	//如果分配失败，则返回失败
	ptChair->m_ptCasCadeChairAddr = CUmsConfInst::m_cCascadeChairAddrMgr.AllocNode();
	if (ptChair->m_ptCasCadeChairAddr == NULL)
	{		
		MdlError(Ums_Mdl_Call, ("AnswerCascadeChair. Assign CascadeChair Failed, ConfID:%d\n", m_pcConf->GetInsID()));
		UmsSendConfCtrl(tOutHandle, evtp_cascade_OpenChairChan_ack, &tViewAck, sizeof(tViewAck));
		return FALSE;
	}
	
	TChanRcvAddr* ptVirLocalNode;
	u16 wChanIndex = 0;
	
	u32 dwEqpIP = ptChair->m_tMediaEqp.m_dwEqpIp;
	//接收视频地址
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptVirLocalNode = &ptChair->m_ptCasCadeChairAddr->m_atVid[wChanIndex];
		ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);
	}
	
	//接收视频地址
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptVirLocalNode = &ptChair->m_ptCasCadeChairAddr->m_atAud[wChanIndex];	
		ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);		
		
	}
	//混音
	ptVirLocalNode = &ptChair->m_ptCasCadeChairAddr->m_tMixAud;
	ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);

	//讨论内单屏广播 -vid
	ptVirLocalNode = &ptChair->m_ptCasCadeChairAddr->m_tDisSingleVid;
	ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);

	//讨论内三屏广播 -aud
	ptVirLocalNode = &ptChair->m_ptCasCadeChairAddr->m_tDisSingleAud;
	ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
	ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);
	
	u16 wIndex = 0;

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{   tViewAck.m_atVidAddr[wIndex].m_tRtpAddr      = ptChair->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtpAddr;
		tViewAck.m_atVidAddr[wIndex].m_tBackRtcpAddr = ptChair->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtcpForSnd;

		tViewAck.m_atAudAddr[wIndex].m_tRtpAddr = ptChair->m_ptCasCadeChairAddr->m_atAud[wIndex].m_tRtpAddr;

		tViewAck.m_abVidOpen[wIndex] = ptCmd->m_abVidOpen[wIndex];
		tViewAck.m_abAudOpen[wIndex] = ptCmd->m_abAudOpen[wIndex];
	
		
		ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].m_tChanAddr = ptCmd->m_atVidAddr[wIndex];
		ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].SetOpen(ptCmd->m_abVidOpen[wIndex]);
		
		ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].m_tChanAddr = ptCmd->m_atAudAddr[wIndex];
		ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].SetOpen(ptCmd->m_abAudOpen[wIndex]);
	}
	
	//主席三屏混音
	tViewAck.m_tMixAudAddr.m_tRtpAddr = ptChair->m_ptCasCadeChairAddr->m_tMixAud.m_tRtpAddr;
	tViewAck.m_bMixAudOpen = ptCmd->m_bMixAudOpen;
	ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr = ptCmd->m_tMixAudAddr;


	//讨论内单屏广播 -vid
	tViewAck.m_tDisSingleVid.m_tRtpAddr = ptChair->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtpAddr;
	tViewAck.m_bDisSingleVid = ptCmd->m_bDisSingleVid;
	ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr = ptCmd->m_tDisSingleVid;

	//讨论内单屏广播 -aud
	tViewAck.m_tDisSingleAud.m_tRtpAddr = ptChair->m_ptCasCadeChairAddr->m_tDisSingleAud.m_tRtpAddr;
	tViewAck.m_bDisSingleAud = ptCmd->m_bDisSingleAud;
	ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleAud.m_tChanAddr = ptCmd->m_tDisSingleAud;
	
	UmsSendConfCtrl(tOutHandle, evtp_cascade_OpenChairChan_ack, &tViewAck, sizeof(tViewAck));
	
	return TRUE;
}

BOOL32 CCallMgr::OnCascadeChairAck(TCapNode* ptRmt, TCascadeOpenChanAck* ptAck)
{
	if (ptRmt->m_ptCasCadeChairAddr == NULL)
	{
		MdlError(Ums_Mdl_Call, ("OnCascadeChairAck. CascadeChair Failed, ConfID:%d, wEpID:%d\n", m_pcConf->GetInsID(), ptRmt->m_wEpID));
		return FALSE;
	}

	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].m_tChanAddr = ptAck->m_atVidAddr[wIndex];
		ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].SetOpen(ptAck->m_abVidOpen[wIndex]);
		
		ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].m_tChanAddr = ptAck->m_atAudAddr[wIndex];
		ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].SetOpen(ptAck->m_abAudOpen[wIndex]);
		
	}
	//主席三屏混音
	ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr = ptAck->m_tMixAudAddr;
	ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.SetOpen(ptAck->m_bMixAudOpen);

	//讨论内单屏广播 -vid
	ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr = ptAck->m_tDisSingleVid;
	ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.SetOpen(ptAck->m_bDisSingleVid);

	//讨论内单屏广播 -aud
	ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleAud.m_tChanAddr = ptAck->m_tDisSingleAud;
	ptRmt->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleAud.SetOpen(ptAck->m_bDisSingleAud);

	Inst()->GetNodeFsm()->ChangeSpeaker(ptRmt);
	return TRUE;
}

//收到下级更新结点信息
void CCallMgr::OnUpdateEpCallInfo(const TUmsHandle& tHandle, TConfNodeCallUpdateTrList& tNodeList)
{
	TCallNode* ptRootNode = m_pcConf->m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (0 == tNodeList.m_wNum || NULL == ptRootNode)
	{
		MdlError(Ums_Mdl_Call, ("OnUpdateEpCallInfo msg error. ConfID:%d, listnum:%d, EpID:%d\n"
			, m_pcConf->GetInsID(), tNodeList.m_wNum, tHandle.GetEpID()));
		return;
	}
	if (!ptRootNode->IsCallOn())
	{
		MdlError(Ums_Mdl_Call, ("OnUpdateEpCallInfo Node state error. ConfID:%d, EpID:%d, state:%d\n"
			, m_pcConf->GetInsID(), tHandle.GetEpID(), ptRootNode->m_emCallState));
		return;
	}
	
	TEpPathKey* pTKeyID;
	TCallNode* ptAddNode = NULL;
	TCallNode* ptParentNode = NULL;

	u16 wEpLevelNum = 0;
	u16 awLowerEpID[TP_MAX_CASECADE_NUM];
	for (u16 wIndex = 0; wIndex < tNodeList.m_wNum; ++wIndex)
	{
		pTKeyID = &tNodeList.m_atList[wIndex].m_tID;
		if (!pTKeyID->GetKeyPath(awLowerEpID, TP_MAX_CASECADE_NUM, wEpLevelNum))
		{
			MdlError(Ums_Mdl_Call, ("OnUpdateEpCallInfo Node KeyID error. confid:%d, epid:%d\n", m_pcConf->GetInsID(), tHandle.GetEpID()));
			continue;
		}

		ptParentNode = NULL;
		ptAddNode = m_pcConf->m_pcNodeMgr->GetNodeByChildIDList(ptRootNode, awLowerEpID, wEpLevelNum, &ptParentNode);
		if (NULL != ptAddNode)
		{//下级结点已经存在，则更改其状态
			if ((ums_UmsConfNodeState_calling == tNodeList.m_atList[wIndex].m_emCallState)
				|| (ums_UmsConfNodeState_online == tNodeList.m_atList[wIndex].m_emCallState))
			{
				ptAddNode->SetNodeCallInfo(tNodeList.m_atList[wIndex]);
			}
			else
			{
				if (ptAddNode->IsCallOn())
				{
					m_pcConf->HungUpFromLow(ptAddNode, tNodeList.m_atList[wIndex].m_emCallReason);
				}
				else
				{//始终没有呼叫上来的下级会场失败状态，也要更新
					ptAddNode->SetNodeCallInfo(tNodeList.m_atList[wIndex]);
				}
				m_pcConf->UpdateNodeInfo(tp_OprType_Update, ptAddNode->m_wEpID);
			}
		}
		else
		{
			if (NULL == ptParentNode)
			{
				MdlError(Ums_Mdl_Call, ("OnUpdateEpCallInfo Node Key List error. confid:%d, epid:%d, keyID:%s\n"
					, m_pcConf->GetInsID(), tHandle.GetEpID(), pTKeyID->m_szEpID));
				continue;
			}
		
			//下级结点第一次上报上来，在本级分配一个结点存储
			ptAddNode = m_pcConf->m_pcNodeMgr->AddChildNode(ptParentNode->m_wEpID, tNodeList.m_atList[wIndex]);		
			if (NULL == ptAddNode)
			{
				MdlError(Ums_Mdl_Call, ("OnUpdateEpCallInfo assign node error. confid:%d, epid:%d, keyID:%s\n"
					, m_pcConf->GetInsID(), tHandle.GetEpID(), pTKeyID->m_szEpID));
				continue;
			}

			m_pcConf->UpdateNodeInfo(tp_OprType_Add, ptAddNode->m_wEpID);
			if (!m_pcConf->GetPollMgr()->IsDefaultPoll())
			{   
                m_pcConf->GetPollMgr()->AddLowInviteEp(ptAddNode);
			}
		}

		if (NULL != ptAddNode && ptAddNode->m_bCallByCMC)
		{
			if (ums_UmsConfNodeState_calling != ptAddNode->m_emCallState
				&& ums_UmsConfNodeState_online != ptAddNode->m_emCallState)
			{

				TLogUser tUser;
				CTpMsg cMsg;	
				cMsg.SetEvent(evtp_CallEP_result);
				
				TConfCallEpAddr tEpAddr;
				tEpAddr.m_wConfID = m_pcConf->GetInsID();
				tEpAddr.m_tCallAddr = ptAddNode->m_tCalledAddr;	
				
				cMsg.SetBody(&tUser, sizeof(tUser));
				cMsg.CatBody(&tEpAddr, sizeof(tEpAddr));
				cMsg.CatBody(&ptAddNode->m_emCallReason, sizeof(ptAddNode->m_emCallReason));
				cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, m_pcConf->GetInsID()));
				
				u8 byBuf[sizeof(TTpCallAddr) + sizeof(EmCnsCallReason)] = {0};
				memcpy(byBuf, &ptAddNode->m_tCalledAddr, sizeof(TTpCallAddr));
				memcpy(byBuf + sizeof(TTpCallAddr), &ptAddNode->m_emCallReason, sizeof(EmCnsCallReason));
 				
 				//回应CNS
 				m_pcConf->NotifyConfCtrlMsgToCns(ev_UmsInviteCnsByAlias_Ind, m_pcConf->chairID(),  byBuf, sizeof(byBuf));
			}
			//calling不修改界面提示的状态
			if (ums_UmsConfNodeState_calling != ptAddNode->m_emCallState)
			{
				ptAddNode->m_bCallByCMC = FALSE;
			}
		}
	}
}

void CCallMgr::OnUpdateEpVidFeccInfo( const TUmsHandle& tHandle, TConfEpVidFeccList& tNodeList )
{
	TCallNode* ptRootNode = m_pcConf->m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (0 == tNodeList.m_wNum || NULL == ptRootNode)
	{
		MdlError(Ums_Mdl_Call, ("OnUpdateEpVidFeccInfo msg error. ConfID:%d, listnum:%d, EpID:%d\n"
			, m_pcConf->GetInsID(), tNodeList.m_wNum, tHandle.GetEpID()));
		return;
	}
	if (!ptRootNode->IsCallOn())
	{
		MdlError(Ums_Mdl_Call, ("OnUpdateEpVidFeccInfo Node state error. ConfID:%d, EpID:%d, state:%d\n"
			, m_pcConf->GetInsID(), tHandle.GetEpID(), ptRootNode->m_emCallState));
		return;
	}
	
	TEpPathKey* pTKeyID;
	TCallNode* ptAddNode = NULL;
	TCallNode* ptParentNode = NULL;

	u16 wEpLevelNum = 0;
	u16 awLowerEpID[TP_MAX_CASECADE_NUM];
	for (u16 wIndex = 0; wIndex < tNodeList.m_wNum; ++wIndex)
	{
		pTKeyID = &tNodeList.m_atList[wIndex].m_tID;
		if (!pTKeyID->GetKeyPath(awLowerEpID, TP_MAX_CASECADE_NUM, wEpLevelNum))
		{
			MdlError(Ums_Mdl_Call, ("OnUpdateEpVidFeccInfo Node KeyID error. confid:%d, epid:%d\n", m_pcConf->GetInsID(), tHandle.GetEpID()));
			continue;
		}

		ptParentNode = NULL;
		ptAddNode = m_pcConf->m_pcNodeMgr->GetNodeByChildIDList(ptRootNode, awLowerEpID, wEpLevelNum, &ptParentNode);
		if (NULL != ptAddNode)
		{// 找到对应的下级节点，更新其状态
			ptAddNode->SetVidFeccInfo(tNodeList.m_atList[wIndex].m_tVidFeccInfo);
			m_pcConf->NotifyVidFeccInfoToUI(ptAddNode->m_wEpID);
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("OnUpdateEpVidFeccInfo Node Key List error. confid:%d, epid:%d, keyID:%s\n"
				, m_pcConf->GetInsID(), tHandle.GetEpID(), pTKeyID->m_szEpID));
			continue;
		}
	}		
}

void CCallMgr::OnUpdateEpChanInfo(const TUmsHandle& tHandle, TConfNodeChanUpdateTrList& tNodeList)
{
	TCallNode* ptRootNode = m_pcConf->m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (0 == tNodeList.m_wNum || NULL == ptRootNode)
	{
		MdlError(Ums_Mdl_Call, ("OnUpdateEpChanInfo msg error. ConfID:%d, listnum:%d, EpID:%d\n"
			, m_pcConf->GetInsID(), tNodeList.m_wNum, tHandle.GetEpID()));
		return;
	}

	if (!ptRootNode->IsCallOn())
	{
		MdlError(Ums_Mdl_Call, ("OnUpdateEpChanInfo Node state error. ConfID:%d, EpID:%d, state:%d\n"
			, m_pcConf->GetInsID(), tHandle.GetEpID(), ptRootNode->m_emCallState));
		return;
	}

	TCallNode* ptAddNode = NULL;
	for (u16 wIndex = 0; wIndex < tNodeList.m_wNum; ++wIndex)
	{
		ptAddNode = m_pcConf->m_pcNodeMgr->GetNodeByChildEpID(ptRootNode, tNodeList.m_atList[wIndex].tID.m_wEpID);
		if (NULL == ptAddNode)
		{
			MdlError(Ums_Mdl_Call, ("OnUpdateEpChanInfo Node Key List error. confid:%d, epid:%d, childId:%d, keyID:%d\n"
						, m_pcConf->GetInsID(), tHandle.GetEpID(), tNodeList.m_atList[wIndex].tID.m_wEpID
						, tNodeList.m_atList[wIndex].tID.m_wEpID));
			continue;
		}
		BOOL32 bOldChan = ptAddNode->m_bChannelOpen;
		if (!bOldChan && tNodeList.m_atList[wIndex].bChanOpen)
		{//通道第一次上线
			if (ptAddNode->IsCallOn())
			{
				ptAddNode->SetNodeChanInfo(tNodeList.m_atList[wIndex]);		
				m_pcConf->m_pcPollMgr->OnChanConnect(ptAddNode);
				m_pcConf->GetUmsDiscuss()->OnChanConnect(ptAddNode);
				m_pcConf->GetAudMix()->OnChanConnect(ptAddNode);
				m_pcConf->m_pcTvWallMgr->ChannelConnect(m_pcConf, ptAddNode);
				m_pcConf->GetVmp()->OnChanConnect(ptAddNode);
				m_pcConf->GetRollCallMgr()->OnChanConnect(ptAddNode);

				m_pcConf->UpdateNodeInfo(tp_OprType_Update, ptAddNode->m_wEpID);
			}
			else
			{
				MdlHint(Ums_Mdl_Call, ("OnUpdateEpChanInfo ep not online, unneed proc. confid:%d, epid:%d, childId:%d, CallState:%d, ChanOn:%d\n"
				, m_pcConf->GetInsID(), tHandle.GetEpID(), tNodeList.m_atList[wIndex].tID.m_wEpID, ptAddNode->m_emCallState, ptAddNode->IsChanOn()));
			}
		}
		else
		{
			//通道已经上线了,不去更新
		}
	}

	return ;
}
void CCallMgr::OnDelEpNode(const TUmsHandle& tHandle, u8* pData)
{
	TConfNodeDelTrList tList;
	TP_SAFE_CAST(tList, pData);

	TCallNode* ptDelNode = NULL;
		
	u16 wEpChildNum = 0;
	u16 awChildEpID[TP_CONF_MAX_CNSNUM];
	for (u16 wIndex = 0; wIndex < tList.m_wNum; ++wIndex)
	{
		ptDelNode = m_pcConf->GetSonNode(tHandle, tList.m_atList[wIndex]);
		if (NULL != ptDelNode)
		{
			wEpChildNum = m_pcConf->m_pcNodeMgr->GetAllNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, ptDelNode);
			for (u16 wI = 0; wI < wEpChildNum; ++wI)
			{
				m_pcConf->UpdateNodeInfo(tp_OprType_Del, awChildEpID[wEpChildNum]);
			}
			m_pcConf->m_pcNodeMgr->DeleteNode(ptDelNode);
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("DelEpNode Node Key List error. confid:%d, epid:%d, keyID:%d\n"
				, m_pcConf->GetInsID(), tHandle.GetEpID(), tList.m_atList[wIndex].m_wEpID));
		}
	}
}
void CCallMgr::OnCnsJoinConf(const TUmsHandle& tHandle, u8* pData)
{
	TTPConfEpInfo tInfo;
	TP_SAFE_CAST(tInfo,pData);


	if (tInfo.m_Index >= TP_CONF_MAX_EPNUM)	//索引无效
	{
		MdlError(Ums_Mdl_Call, ("OnConfJoinEpFromUmc Index invalid. wConfID:%d, Name:%s, Index:%d.\n"
			, tInfo.m_wConfID, tInfo.m_tCallAddr.GetValidAlias().m_abyAlias, tInfo.m_Index));
		return;
	}

	TTPConfEpParam* ptEpParam = &(Inst()->m_tConfEpInfoMrg.m_ConfEpParam[tInfo.m_Index]);

	MdlHint(Ums_Mdl_Call, ("CCallMgr::OnCnsJoinConf Confid:%d, bPermit:%d, Index:%d, Name:%s.\n", tInfo.m_wConfID, tInfo.m_bPermit, 
		tInfo.m_Index, tInfo.m_tCallAddr.GetValidAlias().m_abyAlias));

	//删除定时器
	TTpTimer* ptTimer = (TTpTimer*)ptEpParam->m_dwTimerID;
	if (NULL != ptTimer)
	{
		Inst()->m_pcTimerMgr->DeleteTimer(ptTimer);
		ptEpParam->m_dwTimerID = 0 ;
	}

	if (!ptEpParam->IsUsed())
	{
		return;
	}

	if (!(tInfo.m_bPermit))
	{
		MdlHint(Ums_Mdl_Call,("OnCnsJoinConf Don't be allowed to join the meeting. wConfID:%d,bPermit:%d\n",tInfo.m_wConfID,tInfo.m_bPermit));
		EmCnsCallReason emCallRet = EmCnsCallReason_Rejected;
  		UmsAnwserCall(ptEpParam->m_tHandle, FALSE, NULL, emCallRet);
		ptEpParam->Clear();
		return;
	}

	EmCnsCallReason emCallRet = EmCnsCallReason_success;
	emCallRet = Inst()->OnCnsCallExistConf(ptEpParam->m_tHandle, ptEpParam->m_tCallInfo);
	if (EmCnsCallReason_success != emCallRet)
	{
		MdlHint(Ums_Mdl_Call,("OnCnsJoinConf. wConfID:%d,bPermit:%d,CallReason:%d\n",tInfo.m_wConfID,tInfo.m_bPermit,emCallRet));
		UmsAnwserCall(ptEpParam->m_tHandle, FALSE, NULL, emCallRet);
		ptEpParam->Clear();
		return;
	}
	ptEpParam->Clear();	
	//通知umc和cnc，会场已经入会	
	TLogUser tUserTmp;
	u8 byBuf[ sizeof(u16) + sizeof(TTpCallAddr)] ={0} ;
	memcpy(byBuf,&tInfo.m_wConfID,sizeof(u16));
	memcpy(byBuf + sizeof(u16),&tInfo.m_tCallAddr,sizeof(TTpCallAddr));
	Inst()->NotifyMsgToServiceForUI(evtp_UmsJoinConf_Notify,byBuf,sizeof(TTPConfEpInfo),&tUserTmp);
	Inst()->NotifyConfCtrlMsgToCns(evtp_CnsJoinConf_Notify,Inst()->chairID(),byBuf,sizeof(TTPConfEpInfo));

	return;
}
void CCallMgr::FlowControl(u16 wEpID, u16 wScreeNo, u16 wBitRate)
{
	TCallNode* ptNode = m_pcConf->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptForeFather = m_pcConf->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptForeFather || !ptNode->IsMtEp())
	{
		return;
	}
	u16 wBitrateTemp = 0;

	TFlowControl tFlowInfo;
	tFlowInfo.m_wBand = wBitRate;
	tFlowInfo.m_wEncNo = wScreeNo;
	tFlowInfo.m_tEpKey.m_wEpID = ptNode->m_wLowChildEpID;	

	TUmsHandle tOutHandle;
	m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptForeFather->m_wEpID);

	TVidChanPara* ptDstChan;
	if (FLOW_CTROL_ALL_ENC == wScreeNo)
	{
		if (ptNode == ptForeFather)
		{
			for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				ptDstChan = m_pcConf->m_pcNodeMgr->GetVidChanByIndex(wEpID, ums_CodecType_vid_enc, wIndex);
				if (NULL != ptDstChan && TP_VALID_HANDLE(ptDstChan->m_tPAHandle))
				{
					if ( 0 == wBitRate  )
					{
						if ( ptDstChan->m_tFlowCtrl.IsNoneFlow() )
						{//本来就是0 ，暂不要减，做个保护 宁可多码流，也不可无码流
							MdlHint(Ums_Mdl_Call, ("FlowControl dst chan is 0! ConfID:%d, EpID:%d, ChanID:%d, index:%d, Flowctrl:%d\n"
								, m_pcConf->GetInsID(), wEpID, ptDstChan->m_tPAHandle, ptDstChan->m_wIndex, ptDstChan->m_tFlowCtrl.m_dwState));
							continue;
						}
						ptDstChan->m_tFlowCtrl.Dec();
						if (!ptDstChan->m_tFlowCtrl.IsNoneFlow())
						{
							MdlHint(Ums_Mdl_Call, ("FlowControl dst chan Unneeded! ConfID:%d, EpID:%d, ChanID:%d, index:%d, Flowctrl:%d\n"
								, m_pcConf->GetInsID(), wEpID, ptDstChan->m_tPAHandle, ptDstChan->m_wIndex, ptDstChan->m_tFlowCtrl.m_dwState));
							continue;
						}
						wBitrateTemp = wBitRate;
					}
					else
					{
						ptDstChan->m_tFlowCtrl.Inc();
						wBitrateTemp = ptNode->m_tVidSndFormat.m_tFormat.m_wBitrate;
					}
					tOutHandle.handPaChan = ptDstChan->m_tPAHandle;
					UmsSendChanCtrl(tOutHandle, evtp_Chan_FlowCtrol, &wBitrateTemp, sizeof(wBitrateTemp));					
				}
			}
		}
		else
		{
			UmsSendConfCtrl(tOutHandle, evtp_Conf_FlowCtrol, &tFlowInfo, sizeof(tFlowInfo));
		}
	}
	else
	{
		if (ptNode == ptForeFather)
		{
			ptDstChan = m_pcConf->m_pcNodeMgr->GetVidChanByIndex(wEpID, ums_CodecType_vid_enc, wScreeNo);
			if (NULL != ptDstChan && TP_VALID_HANDLE(ptDstChan->m_tPAHandle))
			{
				if (0 == wBitRate)
				{
					if ( ptDstChan->m_tFlowCtrl.IsNoneFlow() )
					{//本来就是0 ，暂不要减，做个保护 宁可多码流，也不可无码流
						MdlHint(Ums_Mdl_Call, ("FlowControl dst chan is 0! ConfID:%d, EpID:%d, ChanID:%d, index:%d, Flowctrl:%d\n"
							, m_pcConf->GetInsID(), wEpID, ptDstChan->m_tPAHandle, ptDstChan->m_wIndex, ptDstChan->m_tFlowCtrl.m_dwState));
						return ;
					}

					ptDstChan->m_tFlowCtrl.Dec();
					if (!ptDstChan->m_tFlowCtrl.IsNoneFlow())
					{
						MdlHint(Ums_Mdl_Call, ("FlowControl dst chan Unneeded! ConfID:%d, EpID:%d, ChanID:%d, index:%d, Flowctrl:%d\n"
								, m_pcConf->GetInsID(), wEpID, ptDstChan->m_tPAHandle, ptDstChan->m_wIndex, ptDstChan->m_tFlowCtrl.m_dwState));
						return;
					}
					wBitrateTemp = wBitRate;
				}
				else
				{
					ptDstChan->m_tFlowCtrl.Inc();
					wBitrateTemp = ptNode->m_tVidSndFormat.m_tFormat.m_wBitrate;
				}
				tOutHandle.handPaChan = ptDstChan->m_tPAHandle;
				UmsSendChanCtrl(tOutHandle, evtp_Chan_FlowCtrol, &wBitrateTemp, sizeof(wBitrateTemp));
			}
		}
		else
		{
			UmsSendConfCtrl(tOutHandle, evtp_Conf_FlowCtrol, &tFlowInfo, sizeof(tFlowInfo));
		}
	}			
}

void CCallMgr::AskKeyFrame(u16 wEpID, u16 wScreeNo)
{
	TCallNode* ptNode = m_pcConf->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptForeFather = m_pcConf->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptForeFather || !ptNode->IsMtEp())
	{
		return;
	}
		
	TUmsHandle tOutHandle;
	m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptForeFather->m_wEpID);
	
	TChanPara* ptDstChan;
	if (FLOW_CTROL_ALL_ENC == wScreeNo)
	{
		if (ptNode == ptForeFather)
		{
			for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				ptDstChan = m_pcConf->m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_vid_enc, wIndex);
				if (NULL != ptDstChan && TP_VALID_HANDLE(ptDstChan->m_tPAHandle))
				{
					tOutHandle.handPaChan = ptDstChan->m_tPAHandle;									
					UmsSendChanCtrl(tOutHandle, evtp_Conf_AskKeyFrame, NULL, 0);
				}
			}
		}
		else
		{
			u16 wMidIndex = MIDSCREENINDEX;
			s32 symbolflag = 1; 
			u16 wChanIndex;
			
			symbolflag = 1; 
			for (u16 wIndex = 1; wIndex <= ptNode->m_wVidSndNum; ++wIndex, symbolflag *= -1)
			{
				wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

				TAskKeyByScreenTr tAskKey;
				tAskKey.m_wEpID = ptNode->m_wLowChildEpID;
				tAskKey.m_wScreenIndex = wChanIndex;
				tAskKey.m_bReqBySys = TRUE;
				UmsSendConfCtrl(tOutHandle, evtp_Conf_AskKeyByScreen, &tAskKey, sizeof(tAskKey));

			}	
		}
	}
	else
	{
		if (ptNode == ptForeFather)
		{
			ptDstChan = m_pcConf->m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_vid_enc, wScreeNo);
			if (NULL != ptDstChan && TP_VALID_HANDLE(ptDstChan->m_tPAHandle))
			{
				
				tOutHandle.handPaChan = ptDstChan->m_tPAHandle;						
				UmsSendChanCtrl(tOutHandle, evtp_Conf_AskKeyFrame, NULL, 0);
			}
		}
		else
		{
			TAskKeyByScreenTr tAskKey;
			tAskKey.m_wEpID = ptNode->m_wLowChildEpID;
			tAskKey.m_wScreenIndex = wScreeNo;
			tAskKey.m_bReqBySys = TRUE;
			UmsSendConfCtrl(tOutHandle, evtp_Conf_AskKeyByScreen, &tAskKey, sizeof(tAskKey));			
		}
	}
}

void CCallMgr::CallerConnect()
{
	//通知上级结点
	TUmsHandle tOutHandle;
	m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
	
	TConfNodeChanUpdateTrList tUpdateListB2;
	TConfNodeCallUpdateTrList tUpdateList;	
	// 切源远遥消息列表
	TConfEpVidFeccList tVidFeccList;
	TEpPathKey tKeyID;
	TCallNode* ptNode;
	
	u16 atUsedNode[TP_CONF_MAX_CNSNUM];
	u16 wNum = m_pcConf->m_pcNodeMgr->GetAllNode(atUsedNode, TP_CONF_MAX_CNSNUM);
	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
		ptNode = m_pcConf->m_pcNodeMgr->GetNode(atUsedNode[wIndex]);
		if (NULL == ptNode || !ptNode->m_bUsed)
		{
			continue;
		}
		m_pcConf->m_pcNodeMgr->GetPathKey(tUpdateList.m_atList[tUpdateList.m_wNum].m_tID, ptNode->m_wEpID);
		ptNode->GetNodeCallInfo(tUpdateList.m_atList[tUpdateList.m_wNum]);
		++tUpdateList.m_wNum;

		m_pcConf->m_pcNodeMgr->GetPathKey(tVidFeccList.m_atList[tVidFeccList.m_wNum].m_tID, ptNode->m_wEpID);
		ptNode->GetVidFeccInfo(tVidFeccList.m_atList[tVidFeccList.m_wNum].m_tVidFeccInfo);
		++tVidFeccList.m_wNum;

		if ((ums_UmsConfNodeState_calling == ptNode->m_emCallState) || (ums_UmsConfNodeState_online == ptNode->m_emCallState))
		{
			tUpdateListB2.m_atList[tUpdateListB2.m_wNum].tID.m_wEpID = ptNode->m_wEpID;
			ptNode->GetNodeChanInfo(tUpdateListB2.m_atList[tUpdateListB2.m_wNum]);
			++tUpdateListB2.m_wNum;
		}

		if (tUpdateList.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			UmsSendConfCtrl(tOutHandle, evtp_Conf_EpCallInfo_Update, &tUpdateList, sizeof(tUpdateList));
			tUpdateList.m_wNum = 0;
		}
		if (tVidFeccList.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			UmsSendConfCtrl(tOutHandle, evtp_Conf_EpVidFeccInfo_Update, &tVidFeccList, sizeof(tVidFeccList));
			tVidFeccList.m_wNum = 0;
		}
		if (tUpdateListB2.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			UmsSendConfCtrl(tOutHandle, evtp_Conf_EpChanInfo_Update, &tUpdateListB2, sizeof(tUpdateListB2));
			tUpdateListB2.m_wNum = 0;
		}
	}

	if (tUpdateList.m_wNum > 0)
	{
		UmsSendConfCtrl(tOutHandle, evtp_Conf_EpCallInfo_Update, &tUpdateList, sizeof(tUpdateList));
		tUpdateList.m_wNum = 0;
	}

	if (tVidFeccList.m_wNum >= 0)
	{
		UmsSendConfCtrl(tOutHandle, evtp_Conf_EpVidFeccInfo_Update, &tVidFeccList, sizeof(tVidFeccList));
		tVidFeccList.m_wNum = 0;
	}

	if (tUpdateListB2.m_wNum > 0)
	{		
		UmsSendConfCtrl(tOutHandle, evtp_Conf_EpChanInfo_Update, &tUpdateListB2, sizeof(tUpdateListB2));
		tUpdateListB2.m_wNum = 0;
	}
}

void CCallMgr::NotifyToHigherUpdateEp(TRefrenUiNodeList& tList)
{
	if (IsChair() || !m_pcConf->m_pcNodeMgr->GetCaller()->IsChanOn())
	{
		return;
	}
	
	TUmsHandle tOutHandle;
	m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);

	TConfNodeChanUpdateTrList tUpdateListB2;
	TConfNodeCallUpdateTrList tUpdateList;
	TConfNodeDelTrList tDelList;
	
	TEpPathKey tKeyID;
	TCallNode* ptNode;
	TUmsUpdateNode* ptCurInfo = NULL;
	for (u16 wIndex = 0; wIndex < tList.m_wNum; ++wIndex)
	{
		ptCurInfo = &tList.m_atNode[wIndex];
		ptNode = m_pcConf->m_pcNodeMgr->GetNode(ptCurInfo->m_wEpID);
		if (NULL == ptNode || Is_Caller_Node(ptNode->m_wEpID))
		{//上级信息不往上报
			continue;
		}
		
		if (!m_pcConf->m_pcNodeMgr->GetPathKey(tKeyID, ptNode->m_wEpID))
		{
			MdlError(Ums_Mdl_Call, ("NotifyToHigherUpdateEp GetPathKey failed. wConfID:%d, wEpID:%d\n", m_pcConf->GetInsID(), ptNode->m_wEpID));
			continue;
		}
		
		if (tp_OprType_Update == ptCurInfo->m_emOpr || tp_OprType_Add == ptCurInfo->m_emOpr)
		{
			tUpdateList.m_atList[tUpdateList.m_wNum].m_tID = tKeyID;
			ptNode->GetNodeCallInfo(tUpdateList.m_atList[tUpdateList.m_wNum]);
			++tUpdateList.m_wNum;

			if ((ums_UmsConfNodeState_calling == ptNode->m_emCallState) || (ums_UmsConfNodeState_online == ptNode->m_emCallState))
			{
				tUpdateListB2.m_atList[tUpdateListB2.m_wNum].tID.m_wEpID = ptNode->m_wEpID;
				ptNode->GetNodeChanInfo(tUpdateListB2.m_atList[tUpdateListB2.m_wNum]);
				++tUpdateListB2.m_wNum;
			}
			
		}
		else if (tp_OprType_Del == ptCurInfo->m_emOpr)
		{
			tDelList.m_atList[tDelList.m_wNum].m_wEpID = ptNode->m_wEpID;
			++tDelList.m_wNum;
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("NotifyToHigherUpdateEp opr failed. wConfID:%d, wEpID:%d\n", m_pcConf->GetInsID(), ptNode->m_wEpID));
			continue;
		}
	}
	
	if (tUpdateList.m_wNum > 0)
	{
		UmsSendConfCtrl(tOutHandle, evtp_Conf_EpCallInfo_Update, &tUpdateList, sizeof(tUpdateList));
		tUpdateList.m_wNum = 0;
	}
	if (tUpdateListB2.m_wNum > 0)
	{
		UmsSendConfCtrl(tOutHandle, evtp_Conf_EpChanInfo_Update, &tUpdateListB2, sizeof(tUpdateListB2));
		tUpdateListB2.m_wNum = 0;
	}
	if (tDelList.m_wNum > 0)
	{
		UmsSendConfCtrl(tOutHandle, evtp_Conf_EpInfo_Del, &tDelList, sizeof(tDelList));
		tDelList.m_wNum = 0;
	}
}

void CCallMgr::NotifyToHigherVidFeccInfo( u16 wEpId )
{
	if (IsChair() || !m_pcConf->m_pcNodeMgr->GetCaller()->IsChanOn())
	{
		return;
	}

	TCallNode* ptNode = m_pcConf->m_pcNodeMgr->GetNode(wEpId);
	if (NULL == ptNode || !ptNode->m_bUsed)
	{
		return;
	}
	//通知上级结点
	TUmsHandle tOutHandle;
	m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
	// 切源远遥消息列表
	TConfEpVidFeccList tVidFeccList;
	m_pcConf->m_pcNodeMgr->GetPathKey(tVidFeccList.m_atList[tVidFeccList.m_wNum].m_tID, ptNode->m_wEpID);
	ptNode->GetVidFeccInfo(tVidFeccList.m_atList[tVidFeccList.m_wNum].m_tVidFeccInfo);
	++tVidFeccList.m_wNum;
	
	UmsSendConfCtrl(tOutHandle, evtp_Conf_EpVidFeccInfo_Update, &tVidFeccList, sizeof(tVidFeccList));
	
}

void CCallMgr::OnCallEp(const TUmsHandle& tHandle, u8* pData)
{
	CUmsConfInst* pInst = Inst();
	CCallNodeMgr* pNodeMgr = pInst->m_pcNodeMgr;
	TTpCallAddr* ptCallAddr	= (TTpCallAddr*)pData;

	MdlHint(Ums_Mdl_Call, ("OnCallEp ConfID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n", pInst->GetInsID(), ptCallAddr->m_tAlias.m_abyAlias,ptCallAddr->m_tE164.m_abyAlias,Tpu32ToIP(ptCallAddr->m_dwIP)));

	EmCnsCallReason emRet = OnConfInviteEp(ptCallAddr);
	
	u8 byBuf[sizeof(TTpCallAddr) + sizeof(EmCnsCallReason)] = {0};
	memcpy(byBuf, ptCallAddr, sizeof(TTpCallAddr));
	memcpy(byBuf + sizeof(TTpCallAddr), &emRet, sizeof(EmCnsCallReason));
	
	//回应CNS
	pInst->NotifyConfCtrlMsgToCns(ev_UmsInviteCnsByAlias_Ind, tHandle.GetEpID(), byBuf, sizeof(byBuf));

	if (emRet != EmCnsCallReason_success)
	{
		KillTimer(evtp_CallNode_time);
 		SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
	}
}

void CCallMgr::OnCallExistEpFromCns(const TUmsHandle& tHandle, u8* pData)
{	
	u16 wEpID;
	TP_SAFE_CAST(wEpID, pData);

	CUmsConfInst* pInst = Inst();		

	MdlHint(Ums_Mdl_Call, ("OnCallExistEpFromCns, confID:%d, epID:%d\n", pInst->GetInsID(), wEpID));

	EmCnsCallReason emRet = OnConfCallEp(wEpID);

	u8 byBuf[sizeof(u16) + sizeof(EmCnsCallReason)] = {0};
	memcpy(byBuf, &wEpID, sizeof(u16));
	memcpy(byBuf + sizeof(u16), &emRet, sizeof(EmCnsCallReason));
	
	//回应CNS
	pInst->NotifyConfCtrlMsgToCns(ev_UmsInviteCnsByEpId_Ind, tHandle.GetEpID(), byBuf, sizeof(byBuf));

	if (emRet != EmCnsCallReason_success)
	{
		pInst->KillTimer(evtp_CallNode_time);
 		pInst->SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
	}
}
void CCallMgr::OnCallExistEpFromCascade(const TUmsHandle& tHandle, u8* pData)
{
	u16 wEpID;
	TTPAlias tAlias;
	TP_SAFE_CAST(wEpID, pData);
	TP_SAFE_CAST(tAlias, pData+sizeof(u16));
	
	CUmsConfInst* pInst = Inst();
	MdlHint(Ums_Mdl_Call, ("OnCallExistEpFromCascade ConfID:%d, dstID:%d, alias:%s\n", pInst->GetInsID(), wEpID, tAlias.m_abyAlias));
	
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (ptNode && ptFartherNode && ptNode->m_bUsed)
	{
		EmCnsCallReason emRet = EmCnsCallReason_success;
		do 
		{
			if (ums_UmsConfNodeState_uncall == ptFartherNode->m_emCallState && pInst->m_bIsNeedDelayCallNode)
			{
				MdlError(Ums_Mdl_Call, ("OnCallExistEpFromCascade m_bIsNeedDelayCallNode:%d. ConfID:%d, EpID:%d, FatherEp:%d.\n"
					, pInst->m_bIsNeedDelayCallNode, pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID));
				emRet = EmCnsCallReason_Busy;
				break;
			}

			if (ums_UmsConfNodeState_online == ptNode->m_emCallState)
			{
				MdlError(Ums_Mdl_Call, ("OnCallExistEpFromCascade ep is online! ConfID:%d, EpID:%d, FatherEp:%d.\n",
					pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID));
				emRet = EmCnsCallReason_ConfExist;
				break;
			}

			if (ptNode != ptFartherNode && ptFartherNode->m_emCallState == ums_UmsConfNodeState_calling)
			{// 下级结点，父节点正在呼叫中，不用再呼叫
				emRet = EmCnsCallReason_Busy;
				MdlError(Ums_Mdl_Call, ("OnCallExistEpFromCascade father ep is Calling. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}
			
			if (ptNode == ptFartherNode && 
				ums_UmsConfNodeState_calling == ptNode->m_emCallState)
			{// 本级结点，正在呼叫中，不用再呼叫
				emRet = EmCnsCallReason_Busy;
				MdlError(Ums_Mdl_Call, ("OnCallExistEpFromCascade local ep is Calling. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}
			
			if (ptNode == ptFartherNode && !ptFartherNode->IsResReady())
			{			
				BOOL32 bAdapterRet = pInst->m_pcNodeMgr->AssignNodeRes(ptFartherNode, NULL);
				if (!bAdapterRet)
				{
					MdlError(Ums_Mdl_Call, ("OnCallExistEpFromCascade assign Failed. ConfID:%d, EpID:%d\n"
						, pInst->GetInsID(), ptFartherNode->m_wEpID));
					emRet = EmCnsCallReason_Local;
					break;
				}
				
				MdlHint(Ums_Mdl_Call, ("OnCallExistEpFromCascade assign suc. ConfID:%d, EpID:%d, Node:%d\n"
					, pInst->GetInsID(), ptFartherNode->m_wEpID));
			}

		} while (0);
		
		if (EmCnsCallReason_success == emRet)
		{
			TUmsHandle tOutHandle;
			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
			
			if (ptNode == ptFartherNode || !ptFartherNode->IsCallOn())
			{
				ptNode->m_emCallState = ums_UmsConfNodeState_calling;
				TMakeCallPara tCallPara;
				MakeCallInfo(tCallPara, *ptFartherNode, FALSE);
				UmsMakeCall(tOutHandle, tCallPara);
			}
			else
			{
				u8 abBuf[sizeof(u16) + sizeof(TTPAlias)] = {0};
				memcpy(abBuf, &(ptNode->m_wLowChildEpID), sizeof(u16));
				memcpy(abBuf+sizeof(u16), &(ptNode->m_tConfName), sizeof(TTPAlias));
				UmsSendConfCtrl(tOutHandle, evtp_Conf_CallExistEPTr_cmd, abBuf, sizeof(u16)+sizeof(TTPAlias));
			}
		}
		else
		{
			ptNode->m_emCallReason = emRet==EmCnsCallReason_ConfExist?EmCnsCallReason_success:emRet;
			pInst->UpdateNodeInfo(tp_OprType_Update, ptNode->m_wEpID);
			
			pInst->KillTimer(evtp_CallNode_time);
			pInst->SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
		}
		
	}
	else
	{
		MdlHint(Ums_Mdl_Call, ("OnCallExistEpFromCascade call by alias. ConfID:%d, EpID:%d, Alias:%s\n", pInst->GetInsID(), wEpID, tAlias.m_abyAlias));
				
		OnCallEp(tHandle, (u8*)&tAlias);
	}
}

void CCallMgr::OnConfDropEpFromCns(const TUmsHandle& tHandle, u8* pData)
{
	CUmsConfInst* pInst = Inst();
	u16 wEpID;
	TP_SAFE_CAST(wEpID, pData);
	
	MdlHint(Ums_Mdl_Call, ("OnConfDropEpFromCns, confID:%d, epID:%d\n", pInst->GetInsID(), wEpID));
	
	if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) )
	{
		return ;
	}
	
	EmCnsCallReason emReason = OnConfDropEp(wEpID);

	//回应cnc
	u8 byBuf[sizeof(u16) + sizeof(EmCnsCallReason)] = {0};
	memcpy(byBuf, &wEpID, sizeof(u16));
	memcpy(byBuf + sizeof(u16), &emReason, sizeof(EmCnsCallReason));		
	pInst->NotifyConfCtrlMsgToCns(ev_UmsHangupCns_Ind, tHandle.GetEpID(), byBuf, sizeof(byBuf));

}

void CCallMgr::OnConfDropEpFromCascade(const TUmsHandle& tHandle, u8* pData)
{
	CUmsConfInst* pInst = Inst();

	TDropEpCmd tCmd;
	TP_SAFE_CAST(tCmd, pData);

	MdlHint(Ums_Mdl_Call, ("OnConfDropEpFromCascade ConfID:%d, EpID:%d, dstID:%d\n", pInst->GetInsID(), tHandle.GetEpID(), tCmd.m_wEpID));
	
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(tCmd.m_wEpID);
	TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (ptNode && ptFartherNode && ptNode->m_bUsed)
	{
		if (ptNode == ptFartherNode)
		{
			if (tCmd.m_bDel)
			{
				pInst->HungUp(tCmd.m_wEpID, TRUE, TRUE, EmCnsCallReason_hungup);		
			}
			else
			{
				if (ums_UmsConfNodeState_online != ptNode->m_emCallState
					&& ums_UmsConfNodeState_calling != ptNode->m_emCallState)
				{
					return;
				}
				pInst->HungUp(tCmd.m_wEpID, FALSE, TRUE, EmCnsCallReason_hungup);
			}	
			pInst->AjustSpeakerOnNodeDisConn(ptNode);
		}
		else
		{			
			TUmsHandle tOutHandle;
			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
			
			TDropEpCmd tCmd;
			tCmd.m_bDel = tCmd.m_bDel;
			tCmd.m_wEpID = ptNode->m_wLowChildEpID;
			UmsSendConfCtrl(tOutHandle, evtp_Conf_DropEPTr_cmd, &tCmd, sizeof(tCmd));
		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("OnConfDropEpFromCascade ep unexist. ConfID:%d, EpID:%d\n", pInst->GetInsID(), tCmd.m_wEpID));
	}
}

void CCallMgr::OnConfDropEpFromUmc( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TLogUser* ptUserTmp = (TLogUser*)(ptMsg->GetBody());
	TConfEpID* tConfEpId = (TConfEpID*)(ptMsg->GetBody() + sizeof(TLogUser));

	MdlHint(Ums_Mdl_Call, ("OnConfDropEpFromUmc, confID:%d, epID:%d\n", tConfEpId->m_wConfID, tConfEpId->m_wEpID));

	if (pInst->GetInsID() != tConfEpId->m_wConfID)
	{
		MdlError(Ums_Mdl_Call, ("OnConfDropEpFromUmc ConfID error!!. ConfID:%d, tConfEpId.m_wConfID:%d\n", pInst->GetInsID(), tConfEpId->m_wConfID));
		return;
	}

	EmCnsCallReason emReason = OnConfDropEp(tConfEpId->m_wEpID);

	// 回应umc
	u8 byBuf[sizeof(TLogUser) + sizeof(TConfEpID) + sizeof(EmCnsCallReason)] = {0};
	memcpy(byBuf, ptUserTmp, sizeof(TLogUser));
	memcpy(byBuf + sizeof(TLogUser), tConfEpId, sizeof(TConfEpID));
	memcpy(byBuf + sizeof(TLogUser) + sizeof(TConfEpID), &emReason, sizeof(EmCnsCallReason));		
	pInst->NotifyMsgToService(evtp_DropEp_Ind, byBuf, sizeof(byBuf));
}

void CCallMgr::OnConfCallEpFromUmc( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser* ptUserTmp = (TLogUser*)(ptMsg->GetBody());
	TConfEpID* tConfEpId = (TConfEpID*)(ptMsg->GetBody() + sizeof(TLogUser));		

	MdlHint(Ums_Mdl_Call, ("OnConfCallEpFromUmc, confID:%d, epID:%d\n", pInst->GetInsID(), tConfEpId->m_wEpID));

	EmCnsCallReason emRet = OnConfCallEp(tConfEpId->m_wEpID);
	
	if (emRet != EmCnsCallReason_success)
	{
		u8 byBuf[sizeof(TLogUser) + sizeof(TConfEpID) + sizeof(EmCnsCallReason)] = {0};
		memcpy(byBuf, ptUserTmp, sizeof(TLogUser));
		memcpy(byBuf + sizeof(TLogUser), tConfEpId, sizeof(TConfEpID));
		memcpy(byBuf + sizeof(TLogUser) + sizeof(TConfEpID), &emRet, sizeof(EmCnsCallReason));
		
		// 回应umc
		pInst->NotifyMsgToService(evtp_CallExistEP_result, byBuf, sizeof(byBuf));

		pInst->KillTimer(evtp_CallNode_time);
 		pInst->SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
	}
}

void CCallMgr::OnConfInviteEpFromUmc( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser* ptUserTmp = (TLogUser*)(ptMsg->GetBody());
	TConfCallEpAddr* ptConfCalled	= (TConfCallEpAddr*)(ptMsg->GetBody() + sizeof(TLogUser));

	TTpCallAddr* ptCallAddr	= &(ptConfCalled->m_tCallAddr);
	MdlHint(Ums_Mdl_Call, ("OnConfInviteEpFromUmc, ConfID:%d, alias:%s,e164:%s,IP:"TPIPFORMAT",m_bAliasIP:%d\n", 
		   pInst->GetInsID(),
		   ptCallAddr->m_tAlias.m_abyAlias,
		   ptCallAddr->m_tE164.m_abyAlias,
		   Tpu32ToIP(ptCallAddr->m_dwIP), 
		   ptCallAddr->m_bAliasIP));

	EmCnsCallReason emRet = OnConfInviteEp(ptCallAddr);

	if (emRet != EmCnsCallReason_success)
	{

		u8 byBuf[sizeof(TLogUser) + sizeof(TConfCallEpAddr) + sizeof(EmCnsCallReason)] = {0};
		memcpy(byBuf, ptUserTmp, sizeof(TLogUser));
		memcpy(byBuf + sizeof(TLogUser), ptConfCalled, sizeof(TConfCallEpAddr));
		memcpy(byBuf + sizeof(TLogUser) + sizeof(TConfCallEpAddr), &emRet, sizeof(EmCnsCallReason));
		
		// 不成功，回应umc
		pInst->NotifyMsgToService(evtp_CallEP_result, byBuf, sizeof(byBuf));

		KillTimer(evtp_CallNode_time);
 		SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
	}
}

EmCnsCallReason CCallMgr::OnConfDropEp( u16 wEpID )
{
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	
	if (ptNode && ptFartherNode && ptFartherNode != ptNode && ptFartherNode->IsMcu())
	{
		EmCnsCallReason emReason = OnConfDropMcuEp(wEpID);
		return emReason;
	}


	if (ptNode && ptFartherNode && ptNode->m_bUsed)
	{
		do
		{
			if (ums_UmsConfNodeState_uncall == ptNode->m_emCallState
				|| ums_UmsConfNodeState_callfailed == ptNode->m_emCallState)
			{//处于呼叫状态，停止呼叫
				
				if( ptNode == ptFartherNode )
				{
					pInst->m_pcNodeMgr->ReleaseNodeRes(ptFartherNode);
				}
				ptNode->HungUp();
				break;
			}
			
			if (ums_UmsConfNodeState_online != ptNode->m_emCallState
				&& ums_UmsConfNodeState_calling != ptNode->m_emCallState)
			{
				if( ptNode == ptFartherNode )
				{
					pInst->m_pcNodeMgr->ReleaseNodeRes(ptFartherNode);
				}
				ptNode->HungUp();
				break;
			}
			
			if (ptNode == ptFartherNode)
			{
				pInst->HungUp(wEpID, FALSE, TRUE, EmCnsCallReason_hungup);
				pInst->AjustSpeakerOnNodeDisConn(ptNode);
			}
			else
			{			
				TUmsHandle tOutHandle;
				pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
				
				TDropEpCmd tCmd;
				tCmd.m_bDel = FALSE;
				tCmd.m_wEpID = ptNode->m_wLowChildEpID;
				UmsSendConfCtrl(tOutHandle, evtp_Conf_DropEPTr_cmd, &tCmd, sizeof(tCmd));
			}
		}while(0);
		return EmCnsCallReason_hungup;
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("OnConfDropEp ep unexist. ConfID:%d, EpID:%d\n", pInst->GetInsID(), wEpID));
		return EmCnsCallReason_dstnotfind;
	}
}

EmCnsCallReason CCallMgr::OnConfCallEp( u16 wEpID )
{

	CUmsConfInst* pInst = Inst();
	
	EmCnsCallReason emRet = EmCnsCallReason_success;	

	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	
	if (ptNode && ptFartherNode && ptNode != ptFartherNode && ptFartherNode->IsMcu())
	{
		EmCnsCallReason emReason = OnConfCallMcuEp(wEpID);
		return emReason;
	}

	do 
	{
		if (ptNode && ptFartherNode && ptNode->m_bUsed)
		{
			if (ums_UmsConfNodeState_uncall == ptFartherNode->m_emCallState && pInst->m_bIsNeedDelayCallNode)
			{
				MdlError(Ums_Mdl_Call, ("OnConfCallEp m_bIsNeedDelayCallNode:%d. ConfID:%d, EpID:%d, FartherEp:%d\n"
					, pInst->m_bIsNeedDelayCallNode, pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID));
				emRet = EmCnsCallReason_Busy;
				break;
			}

			if (ums_UmsConfNodeState_online == ptNode->m_emCallState &&  ptNode == ptFartherNode )
			{// 本级结点，online状态，不再去呼叫
				emRet = EmCnsCallReason_success;
				MdlError(Ums_Mdl_Call, ("OnConfCallEp ep is online. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}

			if (ums_UmsConfNodeState_online == ptNode->m_emCallState && ptNode != ptFartherNode && ptNode->IsChanOn())
			{// 下级结点，online状态且通道也上线了，才不去呼叫
				emRet = EmCnsCallReason_success;
				MdlError(Ums_Mdl_Call, ("OnConfCallEp ep is online and chanon. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}


			if (ptNode != ptFartherNode && ptFartherNode->m_emCallState == ums_UmsConfNodeState_calling)
			{// 下级结点，父节点正在呼叫中，不用再呼叫
				emRet = EmCnsCallReason_Busy;
				MdlError(Ums_Mdl_Call, ("OnConfCallEp father ep is Calling. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}

			if (ptNode == ptFartherNode && 
				ums_UmsConfNodeState_calling == ptNode->m_emCallState)
			{// 本级结点，正在呼叫中，不用再呼叫
				emRet = EmCnsCallReason_Busy;
				MdlError(Ums_Mdl_Call, ("OnConfCallEp local ep is Calling. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}

			TUmsHandle tOutHandle;
			
			if (ptNode == ptFartherNode)
			{
				//本级中
				if (!ptFartherNode->IsResReady())
				{
					BOOL32 bAdapterRet = pInst->m_pcNodeMgr->AssignNodeRes(ptFartherNode, NULL);
					if (!bAdapterRet)
					{
						MdlError(Ums_Mdl_Call, ("OnConfCallEp assign res Failed. ConfID:%d, EpID:%d\n"
							, pInst->GetInsID(), ptFartherNode->m_wEpID));
						emRet = EmCnsCallReason_Local;
						
						ptNode->m_emCallState = ums_UmsConfNodeState_callfailed;
					}
					else
					{
						MdlHint(Ums_Mdl_Call, ("OnConfCallEp ConfID:%d, EpID:%d, Adapter:%d\n"
							, pInst->GetInsID(), ptFartherNode->m_wEpID,  ptFartherNode->m_tAdapterEqp.m_dwEqpNode));
					}
				}
				
				if (EmCnsCallReason_success == emRet)
				{
					ptNode->m_bCallByCMC = TRUE;
					ptNode->m_emCallState = ums_UmsConfNodeState_calling;
					
					pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
					TMakeCallPara tCallPara;
					MakeCallInfo(tCallPara, *ptFartherNode, FALSE);
					UmsMakeCall(tOutHandle, tCallPara);
				}
			}
			else
			{
				if (ptFartherNode->IsCallOn())
				{
					ptNode->m_bCallByCMC = TRUE;
					if (ptNode->m_emCallState != ums_UmsConfNodeState_online)
					{// 下级的结点如果没有online，才置为calling；
					// 有种情形：下级的结点online状态，但是chan状态没有更新上来，通过此次呼叫更新上来
						ptNode->m_emCallState = ums_UmsConfNodeState_calling;
					}
					
					pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
					
					u8 abBuf[sizeof(u16) + sizeof(TTPAlias)] = {0};
					memcpy(abBuf, &(ptNode->m_wLowChildEpID), sizeof(u16));
					memcpy(abBuf+sizeof(u16), &(ptNode->m_tConfName), sizeof(TTPAlias));
					UmsSendConfCtrl(tOutHandle, evtp_Conf_CallExistEPTr_cmd, abBuf, sizeof(u16)+sizeof(TTPAlias));
				}
				else
				{
					if (!ptFartherNode->IsResReady())
					{			
						BOOL32 bAdapterRet = pInst->m_pcNodeMgr->AssignNodeRes(ptFartherNode, NULL);
						if (!bAdapterRet)
						{
							MdlError(Ums_Mdl_Call, ("OnConfCallEp farther assign Failed. ConfID:%d, EpID:%d, FartherEp:%d\n"
								, pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID));
							emRet = EmCnsCallReason_Local;
						}
						else
						{
							MdlHint(Ums_Mdl_Call, ("OnConfCallEp ConfID:%d, EpID:%d, FartherEp:%d, adapter:%d\n"
								, pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID, ptFartherNode->m_tAdapterEqp.m_dwEqpNode));
						}
					}
					
					if (EmCnsCallReason_success == emRet)
					{
						ptNode->m_bCallByCMC = TRUE;
						
						ptFartherNode->m_emCallState = ums_UmsConfNodeState_calling;
						ptFartherNode->m_bCallByCMC  = TRUE;
						
						pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
						TMakeCallPara tCallPara;
						MakeCallInfo(tCallPara, *ptFartherNode, FALSE);
						UmsMakeCall(tOutHandle, tCallPara);
					}
				}			
			}	

		}
		else
		{
			emRet = EmCnsCallReason_dstnotfind;
			MdlError(Ums_Mdl_Call, ("OnConfCallEp ep unexist. ConfID:%d, EpID:%d\n", pInst->GetInsID(), wEpID));
		}

	} while (0);

	return emRet;
}

// 呼叫mcu的下级会场
EmCnsCallReason CCallMgr::OnConfCallMcuEp( u16 wEpID )
{
	CUmsConfInst* pInst = Inst();
	
	EmCnsCallReason emRet = EmCnsCallReason_success;	

	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	
	if (!ptNode || !ptFartherNode || ptFartherNode == ptNode || !ptFartherNode->IsMcu())
	{// 非mcu的下级会场
		MdlError(Ums_Mdl_Call, ("OnConfCallMcuEp ep is not mcu low ep. ConfID:%d, EpID:%d\n", pInst->GetInsID(), wEpID));
		return EmCnsCallReason_dstnotfind;
	}

	do 
	{
		if (ptNode && ptFartherNode && ptNode->m_bUsed)
		{
			if (ums_UmsConfNodeState_uncall == ptFartherNode->m_emCallState && pInst->m_bIsNeedDelayCallNode)
			{
				MdlError(Ums_Mdl_Call, ("OnConfCallMcuEp m_bIsNeedDelayCallNode:%d. ConfID:%d, EpID:%d, FartherEp:%d\n"
					, pInst->m_bIsNeedDelayCallNode, pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID));
				emRet = EmCnsCallReason_Busy;
				break;
			}
	
			if (ums_UmsConfNodeState_online == ptNode->m_emCallState && ptNode != ptFartherNode && ptNode->IsChanOn())
			{// 下级结点，online状态且通道也上线了，才不去呼叫
				emRet = EmCnsCallReason_success;
				MdlError(Ums_Mdl_Call, ("OnConfCallMcuEp ep is online and chanon. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}

			if (ptNode != ptFartherNode && ptFartherNode->m_emCallState == ums_UmsConfNodeState_calling)
			{// 下级结点，父节点正在呼叫中，不用再呼叫
				emRet = EmCnsCallReason_Busy;
				MdlError(Ums_Mdl_Call, ("OnConfCallMcuEp father ep is Calling. ConfID:%d, EpID:%d.\n", pInst->GetInsID(), wEpID));
				break;
			}

			TUmsHandle tOutHandle;
			if (ptNode != ptFartherNode)
			{
				if (ptFartherNode->IsCallOn())
				{
					ptNode->m_bCallByCMC = TRUE;
					
					TUmsMcuChan tOutChan;
					pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
					tOutChan.m_hMcuChan = ptFartherNode->m_hMcuChan;
					tOutChan.m_hMcuAppChan = ptFartherNode->m_hMcuAppChan;
					
					TMcuEpCmd	tCmd;
					tCmd.m_bCall	= TRUE;
					tCmd.m_dwPID	= MAKEIID(UMS_MCU_PART_MAX_NUM, ptNode->m_wLowChildEpID); // 192 本mcu mcuid + mtId
					UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_CallDropPartReq, &tCmd, sizeof(TMcuEpCmd));
				}
				else
				{
					if (!ptFartherNode->IsResReady())
					{			
						BOOL32 bAdapterRet = pInst->m_pcNodeMgr->AssignNodeRes(ptFartherNode, NULL);
						if (!bAdapterRet)
						{
							MdlError(Ums_Mdl_Call, ("OnConfCallMcuEp farther assign Failed. ConfID:%d, EpID:%d, FartherEp:%d\n"
								, pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID));
							emRet = EmCnsCallReason_Local;
						}
						else
						{
							MdlHint(Ums_Mdl_Call, ("OnConfCallMcuEp ConfID:%d, EpID:%d, FartherEp:%d, adapter:%d\n"
								, pInst->GetInsID(), ptNode->m_wEpID, ptFartherNode->m_wEpID, ptFartherNode->m_tAdapterEqp.m_dwEqpNode));
						}
					}
					
					if (EmCnsCallReason_success == emRet)
					{
						ptNode->m_bCallByCMC = TRUE;
						
						ptFartherNode->m_emCallState = ums_UmsConfNodeState_calling;
						ptFartherNode->m_bCallByCMC  = TRUE;
						
						pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
						TMakeCallPara tCallPara;
						MakeCallInfo(tCallPara, *ptFartherNode, FALSE);
						UmsMakeCall(tOutHandle, tCallPara);
					}
				}	
			}
		}
		else
		{
			emRet = EmCnsCallReason_dstnotfind;
			MdlError(Ums_Mdl_Call, ("OnConfCallMcuEp ep unexist. ConfID:%d, EpID:%d\n", pInst->GetInsID(), wEpID));
		}

	} while (0);

	return emRet;
}

// 挂断mcu的下级会场
EmCnsCallReason CCallMgr::OnConfDropMcuEp( u16 wEpID )
{
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (!ptNode || !ptFartherNode || ptFartherNode == ptNode || !ptFartherNode->IsMcu())
	{// 非mcu的下级会场
		MdlError(Ums_Mdl_Call, ("OnConfDropMcuEp ep is not mcu low ep. ConfID:%d, EpID:%d\n", pInst->GetInsID(), wEpID));
		return EmCnsCallReason_dstnotfind;
	}

	if (ptNode && ptFartherNode && ptNode->m_bUsed)
	{
		do
		{
			if (ums_UmsConfNodeState_uncall == ptNode->m_emCallState
				|| ums_UmsConfNodeState_callfailed == ptNode->m_emCallState)
			{//处于呼叫状态，停止呼叫
				ptNode->HungUp();
				break;
			}
			
			if (ums_UmsConfNodeState_online != ptNode->m_emCallState
				&& ums_UmsConfNodeState_calling != ptNode->m_emCallState)
			{
				ptNode->HungUp();
				break;
			}
			
			if (ptNode != ptFartherNode)
			{
				
				TUmsHandle tOutHandle;
				TUmsMcuChan tOutChan;
				pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
				tOutChan.m_hMcuChan = ptFartherNode->m_hMcuChan;
				tOutChan.m_hMcuAppChan = ptFartherNode->m_hMcuAppChan;
				u16 wLowEpId = ptNode->m_wLowChildEpID;
				
				TMcuEpCmd	tCmd;
				tCmd.m_bCall	= FALSE;
				tCmd.m_dwPID	= MAKEIID(UMS_MCU_PART_MAX_NUM, ptNode->m_wLowChildEpID); // 192 本mcu mcuid + mtId
				UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_CallDropPartReq, &tCmd, sizeof(TMcuEpCmd));

			}
		}while(0);
		return EmCnsCallReason_hungup;
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("OnConfDropMcuEp ep unexist. ConfID:%d, EpID:%d bUsed:%d\n", pInst->GetInsID(), wEpID, ptNode->m_bUsed));
		return EmCnsCallReason_dstnotfind;
	}
}

EmCnsCallReason CCallMgr::OnConfInviteEp( TTpCallAddr* ptCallAddr )
{
	CUmsConfInst* pInst = Inst();
	CCallNodeMgr* pNodeMgr = pInst->m_pcNodeMgr;

	pNodeMgr->GetValidCallType(*ptCallAddr);
	EmCnsCallReason emRet = EmCnsCallReason_success;
	BOOL32 bExist = FALSE;
	TCapNode* ptNode = pNodeMgr->AddNewCall(*ptCallAddr, bExist);
	do 
	{
		if (NULL == ptNode)
		{
			emRet = EmCnsCallReason_resourcefull;
			break;
		}
		
		if (ums_UmsConfNodeState_uncall == ptNode->m_emCallState && pInst->m_bIsNeedDelayCallNode)
		{
			MdlError(Ums_Mdl_Call, ("OnConfInviteEp m_bIsNeedDelayCallNode:%d. ConfID:%d, EpID:%d.\n"
				, pInst->m_bIsNeedDelayCallNode, pInst->GetInsID(), ptNode->m_wEpID));
			emRet = EmCnsCallReason_Busy;
			break;
		}
		
		if (!bExist)
		{//新建节点
			if (!pNodeMgr->AssignNodeRes(ptNode, NULL))
			{
				emRet = EmCnsCallReason_resourcefull;
				break;
			}
			
			emRet = EmCnsCallReason_success;
			
			//加入呼叫队列
			ptNode->m_bUsed = TRUE;
			ptNode->m_tCalledAddr = *ptCallAddr;
			ptNode->m_tConfName = ptNode->m_tCalledAddr.GetValidAlias();
			ptNode->m_emCallState = ums_UmsConfNodeState_calling;
			ptNode->m_bCallByCMC = TRUE;
			
			TUmsHandle	tHandle;
			pNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			
			TMakeCallPara tCallPara;
			MakeCallInfo(tCallPara, *ptNode, FALSE);
			UmsMakeCall(tHandle, tCallPara);
			
			pInst->UpdateNodeInfo(tp_OprType_Add, ptNode->m_wEpID);
			
			if (!pInst->GetPollMgr()->IsDefaultPoll())
			{
				pInst->GetPollMgr()->AddNode(ptNode);
			}
			
		}
		else
		{//已存在节点
			BOOL32 bRet = TRUE;
			if (!ptNode->IsResReady())
			{			
				bRet = pNodeMgr->AssignNodeRes(ptNode, NULL);
			}
			
			if (!bRet)
			{
				emRet = EmCnsCallReason_resourcefull;
				break;
			}
			
			//此状态，重新呼叫
			if (ums_UmsConfNodeState_stopcall == ptNode->m_emCallState)
			{
				
				ptNode->m_emCallState = ums_UmsConfNodeState_calling;
				ptNode->m_bCallByCMC = TRUE;
				
				TUmsHandle	tHandle;
				pNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);	
				
				TMakeCallPara tCallPara;
				MakeCallInfo(tCallPara, *ptNode, FALSE);
				UmsMakeCall(tHandle, tCallPara);
				
				emRet = EmCnsCallReason_success;
			}
			else
			{
				emRet = EmCnsCallReason_Exist;
			}
		}
	} while (0);

	return emRet;
}

void CCallMgr::OnConfJoinEpFromUmc(CTpMsg *const ptMsg)
{
 	
	CUmsConfInst* pInst = Inst();
	TLogUser* ptUserTmp = (TLogUser*)(ptMsg->GetBody());
	TTPConfEpInfo* ptInfo = (TTPConfEpInfo*)(ptMsg->GetBody() + sizeof(TLogUser));

	if (ptInfo->m_Index >= TP_CONF_MAX_EPNUM)	//索引无效
	{
		MdlError(Ums_Mdl_Call, ("OnConfJoinEpFromUmc Index invalid. wConfID:%d, Name:%s, Index:%d.\n"
						, ptInfo->m_wConfID, ptInfo->m_tCallAddr.GetValidAlias().m_abyAlias, ptInfo->m_Index));
		return;
	}

	MdlHint(Ums_Mdl_Call, ("CCallMgr::OnConfJoinEpFromUmc Confid:%d, bPermit:%d, Index:%d, Name:%s.\n", ptInfo->m_wConfID, ptInfo->m_bPermit, 
		ptInfo->m_Index, ptInfo->m_tCallAddr.GetValidAlias().m_abyAlias));

 	TTPConfEpParam* ptEpParam = &(pInst->m_tConfEpInfoMrg.m_ConfEpParam[ptInfo->m_Index]);	
	if (NULL == ptEpParam)
	{
		MdlError(Ums_Mdl_Call,("OnConfJoinEpFromUmc EpParam is null.wConfID:%d, Name:%s\n"
						, ptInfo->m_wConfID, ptInfo->m_tCallAddr.GetValidAlias().m_abyAlias));
		return;
	}
	TTpTimer* ptTimer = (TTpTimer*)ptEpParam->m_dwTimerID;
	if (NULL != ptTimer)
	{
		pInst->m_pcTimerMgr->DeleteTimer(ptTimer);
	}

	if (!ptEpParam->IsUsed())
	{
		return;
	}

	if (!(ptInfo->m_bPermit))
	{
		EmCnsCallReason emCallRet = EmCnsCallReason_Rejected;
 		UmsAnwserCall(ptEpParam->m_tHandle, FALSE, NULL, emCallRet);
		MdlHint(Ums_Mdl_Call,("OnConfJoinEpFromUmc Don't be allowed to join the meeting. ConfID:%d,Permit:%d\n",ptInfo->m_wConfID,ptInfo->m_bPermit));
		ptEpParam->Clear();
		return;
	}

	EmCnsCallReason emCallRet = EmCnsCallReason_success;
	emCallRet = pInst->OnCnsCallExistConf(ptEpParam->m_tHandle, ptEpParam->m_tCallInfo);
	
	if (EmCnsCallReason_success != emCallRet)
	{
		MdlHint(Ums_Mdl_Call,("OnConfJoinEpFromUmc. ConfID:%d,bPermit:%d,CallReason:%d\n",ptInfo->m_wConfID,ptInfo->m_bPermit,emCallRet));
		UmsAnwserCall(ptEpParam->m_tHandle, FALSE, NULL, emCallRet);
		ptEpParam->Clear();
		return;
	}	
	ptEpParam->Clear();

	//通知umc和cnc，会场已经入会	
	u8 byBuf[ sizeof(u16) + sizeof(TTpCallAddr)] ={0} ;
	TLogUser tUserTmp;
	memcpy(byBuf,&(ptInfo->m_wConfID),sizeof(u16));
	memcpy(byBuf + sizeof(u16),&(ptInfo->m_tCallAddr),sizeof(TTpCallAddr));
	Inst()->NotifyMsgToServiceForUI(evtp_UmsJoinConf_Notify,byBuf,sizeof(TTPConfEpInfo),&tUserTmp);
	Inst()->NotifyConfCtrlMsgToCns(evtp_CnsJoinConf_Notify,Inst()->chairID(),byBuf,sizeof(TTPConfEpInfo));

	return;
}

