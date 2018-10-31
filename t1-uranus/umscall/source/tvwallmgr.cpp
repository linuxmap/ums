#include "tvwallmgr.h"
#include "umsconfinst.h"
#include "innereventtvwall.h"
#include "innereventumsconf.h"
#include "eventoutsipadapter.h"
#include "callnodemgr.h"
#include "umsnetportmgr.h"
#include "umsstackinterface.h"
#include "callmgr.h"
#include "umsapi.h"
#include "getvidaud.h"
#include "tperrno.h"
#include "tpcommonstruct.h"

void HduBrdVmpCB(void* param1, void* param2, void* param3)
{
	CTvWallMgr* ptTv= (CTvWallMgr*)param1;
	TBrdVmpRes* ptRes = (TBrdVmpRes*)param2;
	
	ptTv->BrdVmpCB(ptRes, *(EmBrdVmpCBOprType *)param3);
}


static u16 NotifyMsgToHdu(u16 wEvent, void* body, u16 bodyLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(body, bodyLen);
	
	return cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_CALL_APP_INST(CInstance::DAEMON));
}

CTvWallMgr::CTvWallMgr(CUmsConfInst* pcInst)
:m_pcConf(pcInst)
{
	memset(m_atInfo, 0, sizeof(m_atInfo));
}

CTvWallMgr::~CTvWallMgr()
{
}

BOOL32 CTvWallMgr::Handler(CTpMsg *const ptMsg, CApp* pcApp)
{
	switch(ptMsg->GetEvent())
	{
	case ev_AddTvMonitor_req:
		OnAddMonitor(ptMsg, pcApp);
		break;
	case ev_DelTvMonitor_req:
		OnDelMonitor(ptMsg, pcApp);
		break;
	case ev_RestartTvMonitor_cmd:
		OnUptateMonitor(ptMsg, pcApp);
		break;
	case ev_TvMonitor_AskKey:
		OnAskKey(ptMsg, pcApp);
		break;
	/////////////////////////////////////////////////
	//// 终端操作电视墙相关
	case evTPCNS_UMS_HduPlay_Req:
		{
			EventHduPlayReq(ptMsg, pcApp);
		}
		break;
	case evTPUMS_CNS_HduPlay_Ind:
		{
			EventHduPlayInd(ptMsg, pcApp);
		}
		break;
	case evTPCNS_UMS_HduStopPlay_Req:
		{
			EventHduStopReq(ptMsg, pcApp);
		}
		break;
	case evTPUMS_CNS_HduStopPlay_Ind:
		{
			EventHduStopInd(ptMsg, pcApp);
		}
		break;
	case evTPCNS_UMS_HduStopAllPlay_Req:
		{
			EventHduAllStopReq(ptMsg, pcApp);
		}
		break;
	case evTPCNS_UMS_HduSetVol_Req:
		{
			EventHduSetVolReq(ptMsg, pcApp);
		}
		break;
	case evTPUMS_CNS_HduSetVol_Ind:
		{
			EventHduSetVolInd(ptMsg, pcApp);	
		}
		break;
	case evTPCNS_UMS_HduChangeChanMode_Req:
		{
			EventHduChangeModeReq(ptMsg, pcApp);
		}
		break;
	case evTPUMS_CNS_HduChangeChanMode_Ind:
		{
			EventHduChangeModeInd(ptMsg, pcApp);
		}
		break;
	case evTPUMS_CNS_hduPlan_Nty:
		{
			SendHduPlanInfo(ptMsg, pcApp);
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void CTvWallMgr::AdjustGetVidFailed(CUmsConfInst* pcInst, u16 wGetVidIndex)
{
	EmCnsCallReason emRes = EmCnsCallReason_hungup;

	for(u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		if (m_atInfo[wIndex].m_wGetVidIndex == wGetVidIndex)
		{
			DestroyMediaTrans(pcInst, &(m_atInfo[wIndex]));
			
			if ( m_atInfo[wIndex].m_bAdjstRes )
			{// 恢复终端分辨率
				pcInst->GetNodeMgr()->AdjustNodeRes(m_atInfo[wIndex].m_tChanInfo.m_wEpID, m_atInfo[wIndex].m_tChanInfo.m_wScreenIndex, emTPVHD720p1280x720, TRUE);
			}

			pcInst->m_pcGetVidEx->Release(pcInst, wGetVidIndex);
			
			u8 byRes[sizeof(u16)+sizeof(u8)+sizeof(EmCnsCallReason)] = {0};
			memcpy(byRes, &m_atInfo[wIndex].m_tChanInfo.m_wChan, sizeof(u16));
			memcpy(byRes+sizeof(u16), &(m_atInfo[wIndex].m_tChanInfo.m_bySubChan), sizeof(u8));
			memcpy(byRes+sizeof(u16)+sizeof(u8), &emRes, sizeof(EmCnsCallReason));
			NotifyMsgToHdu(ev_HungUpHdu_cmd, byRes, sizeof(byRes));

			m_atInfo[wIndex].Clear();
			
			// 需要提示，会场从电视墙删除
			pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_BandError);

			return ;
		}
	}
}

BOOL32 CTvWallMgr::Create()
{
	for(u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		m_atInfo[wIndex].m_tChanInfo.m_bUsed = FALSE;
	}
	return TRUE;
}

u16 CTvWallMgr::InitPort(u16 wStartPort)
{
 	u16 wOffsetPort = wStartPort;
// 	u32 dwIP = GetLocalIP();
// 	
// 	TTvChanInfo* ptChan;
// 	for(u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
// 	{
// 		ptChan = &(m_atInfo[wIndex].m_tChanInfo);
// 		ptChan->m_tLocVidRcv.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
// 		ptChan->m_tLocVidRcv.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
// 		ptChan->m_tLocVidRcv.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+2);
// 		wOffsetPort += 3;
// 
// //		OspPrintf(TRUE,FALSE,"localvidrecv%d %d %d\n",ptChan->m_tLocVidRcv.m_tRtpAddr.m_wPort,ptChan->m_tLocVidRcv.m_tRtcpAddr.m_wPort,ptChan->m_tLocVidRcv.m_tBackRtcpAddr.m_wPort );
// 
// 		ptChan->m_tLocAudRcv.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
// 		ptChan->m_tLocAudRcv.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
// 		ptChan->m_tLocAudRcv.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+2);
// 		wOffsetPort += 3;
// 
// //		OspPrintf(TRUE,FALSE,"localaudrecv%d %d %d\n",ptChan->m_tLocAudRcv.m_tRtpAddr.m_wPort,ptChan->m_tLocAudRcv.m_tRtcpAddr.m_wPort,ptChan->m_tLocAudRcv.m_tBackRtcpAddr.m_wPort);
// 
// 		ptChan->m_tLocVidSnd.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
// 		ptChan->m_tLocVidSnd.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
// 		ptChan->m_tLocVidSnd.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+2);
// 		wOffsetPort += 3;
// 
// //		OspPrintf(TRUE,FALSE,"localvidsnd%d %d %d\n",ptChan->m_tLocVidSnd.m_tRtpAddr.m_wPort,ptChan->m_tLocVidSnd.m_tRtcpAddr.m_wPort,ptChan->m_tLocVidSnd.m_tBackRtcpAddr.m_wPort);
// 
// 		ptChan->m_tLocAudSnd.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
// 		ptChan->m_tLocAudSnd.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
// 		ptChan->m_tLocAudSnd.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+2);
// 		wOffsetPort += 3;
// //		OspPrintf(TRUE,FALSE,"localaudsnd%d %d %d\n",ptChan->m_tLocAudSnd.m_tRtpAddr.m_wPort,ptChan->m_tLocAudSnd.m_tRtcpAddr.m_wPort,ptChan->m_tLocAudSnd.m_tBackRtcpAddr.m_wPort);
// 
// 	}	
 	return wOffsetPort;
}


void CTvWallMgr::ResetMediaIp( const TEqpRes& tConfDs )
{
	return;
}

#define UmsTvWallPrintAddr(Index, Addr) if (1){\
	msgprintnotime("  Index:%d, Rtp("ADDRPORT_FORMAT"), BackRtcp("ADDRPORT_FORMAT")\n"\
	, Index, ADDRNET(Addr.m_tRtpAddr), ADDRNET(Addr.m_tBackRtcpAddr));}

void CTvWallMgr::Show()
{
	msgprintnotime("TvWall Info\n");
	TTvChanInfo* ptChan;
	for (u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; wIndex++)
	{
		ptChan = &(m_atInfo[wIndex].m_tChanInfo);
		
		if (!ptChan->m_bUsed)
		{
			continue;
		}

		msgprintnotime(" Wall :%d, Used:%d, ChanIndex:%d, SubChanIndex:%d, bVmp:%d\n", wIndex+1, ptChan->m_bUsed, ptChan->m_wChan, ptChan->m_bySubChan, ptChan->m_bVmp);
		msgprintnotime("   GetVidIndex:%d, AdjstRes:%d\n", m_atInfo[wIndex].m_wGetVidIndex, m_atInfo[wIndex].m_bAdjstRes);
		msgprintnotime("   ToServer:%d.\n", ptChan->m_bOpenToServer);
		msgprintnotime("   ToCall:%d, ConfID:%d, EpID:%d, wScreenIndex:%d\n", ptChan->m_bOpenToCall, ptChan->m_wConfID, ptChan->m_wEpID, ptChan->m_wScreenIndex);

		msgprintnotime("   [Local]\n");
		if (ptChan->m_emType == EmEpType_Ter)
		{
			msgprintnotime("  [Vid]");
			UmsTvWallPrintAddr(ptChan->m_wScreenIndex, m_atInfo[wIndex].m_tAddr.m_atVidAddr[MIDSCREENINDEX]);
			msgprintnotime("  [Aud]");
			UmsTvWallPrintAddr(ptChan->m_wScreenIndex, m_atInfo[wIndex].m_tAddr.m_atAudAddr[MIDSCREENINDEX]);
		}
		else
		{
			msgprintnotime("  VmpEpd ID: %d\n", ptChan->m_wEpID);
		}

		msgprintnotime("   TVVidRcv rtp("ADDRPORT_FORMAT"), backrtcp("ADDRPORT_FORMAT")\n"
		, ADDRNET(ptChan->m_tTvVidRcv.m_tRtpAddr), ADDRNET(ptChan->m_tTvVidRcv.m_tBackRtcpAddr));
		msgprintnotime("   TVAudRcv rtp("ADDRPORT_FORMAT"), backrtcp("ADDRPORT_FORMAT")\n"
		, ADDRNET(ptChan->m_tTvAudRcv.m_tRtpAddr), ADDRNET(ptChan->m_tTvAudRcv.m_tBackRtcpAddr));

	}
}

void CTvWallMgr::ShowPortRes()
{
}

void CTvWallMgr::OnAddMonitor(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TAddTvMonitor tReq;
	TP_SAFE_CAST(tReq, pData);
	BOOL32 bHduOnline;
	TP_SAFE_CAST(bHduOnline, pData + sizeof(TAddTvMonitor));
	BOOL32 bChangeMode;
	TP_SAFE_CAST(bChangeMode, pData + sizeof(TAddTvMonitor)+sizeof(BOOL32));
	MdlHint(Ums_Mdl_Call,("OnAddMonitor Type:%d, ConfID:%d, DstID:%d, ScreenNum:%d, Index:%d, bCreateMedia:%d, bChangeMode:%d.\n",
						   tReq.m_tReq.m_emType, tReq.m_tReq.m_wConfID, tReq.m_tReq.m_wDstID, tReq.m_tReq.m_wScreenNum,
						   tReq.m_tReq.m_wIndex, bHduOnline, bChangeMode));

	TAddTvMonitorAck tAck;
	tAck.m_bAccept = TRUE;
	tAck.m_tReq = tReq.m_tReq;

	u16 wScreenNum = tReq.m_tReq.m_wScreenNum;
	
	u8 abBuf[sizeof(TAddTvMonitorAck)+sizeof(BOOL32)] = {0};
	TVWallInfo* ptInfo = NULL;
	for (u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		if (!m_atInfo[wIndex].m_tChanInfo.m_bUsed)
		{

			ptInfo = &(m_atInfo[wIndex]);
			break;
		}
	}

	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("OnAddMonitor no idle resource! ConfID:%d, EpID:%d, Screen:%d\n", 
								 tReq.m_tReq.m_wConfID, tReq.m_tReq.m_wDstID, wScreenNum));
		tAck.m_bAccept = FALSE;
		memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
		memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));

		NotifyMsgToHdu(ev_AddTvMonitor_ack, abBuf, sizeof(abBuf));
		return;
	}
	ptInfo->Clear();
	
	ptInfo->m_tChanInfo.m_bUsed = TRUE;
	ptInfo->m_tChanInfo.m_wChan = tReq.m_tReq.m_wIndex;
	ptInfo->m_tChanInfo.m_bySubChan = tReq.m_tReq.m_bySubIndex;
	ptInfo->m_tChanInfo.m_bVmp = tReq.m_tReq.m_bVmp;
	ptInfo->m_tChanInfo.m_wConfID = tReq.m_tReq.m_wConfID;
	ptInfo->m_tChanInfo.m_wDstID = tReq.m_tReq.m_wDstID;
	ptInfo->m_tChanInfo.m_wEpID = tReq.m_tReq.m_wDstID;
	ptInfo->m_tChanInfo.m_emType = tReq.m_tReq.m_emType;
	ptInfo->m_tChanInfo.m_wScreenIndex = tReq.m_tReq.m_wScreenNum;    //加入屏号
	ptInfo->m_tChanInfo.m_tTvVidRcv = tReq.m_tVidAddr;
	ptInfo->m_tChanInfo.m_tTvAudRcv = tReq.m_tAudAddr;
	ptInfo->m_tChanInfo.m_bOpenToServer = TRUE;

	CUmsConfInst* pcInst = (CUmsConfInst*)(pcApp->GetInstance(tReq.m_tReq.m_wConfID));
	if (NULL != pcInst)
	{
		// 加密参数
		tAck.m_tEncrypt = pcInst->GetConfEncryptInfo();

		if (EmEpType_Ter == tReq.m_tReq.m_emType)
		{
			TCallNode* ptNode = pcInst->m_pcNodeMgr->GetNode(ptInfo->m_tChanInfo.m_wDstID);
			TCapNode* ptFarther = pcInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
			if (NULL == ptNode || NULL == ptFarther || !ptNode->IsVidSndValid() || !ptNode->IsMtEp()) 
			{
				MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Find Ep is invaild. ConfID:%d, epID:%d\n", 
										pcInst->GetInsID(), ptInfo->m_tChanInfo.m_wDstID));
				tAck.m_bAccept = FALSE;
				ptInfo->Clear();
				
				memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
				memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
				NotifyMsgToHdu(ev_AddTvMonitor_ack, abBuf, sizeof(abBuf));

				pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_InvalidMT);

				return;
			}

			if (!IsInSndRange(ptInfo->m_tChanInfo.m_wScreenIndex, ptNode->m_wVidSndNum))
			{
				MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Find Ep chan is invaild. ConfID:%d, epID:%d, ScreenIndex:%d\n", 
					pcInst->GetInsID(), ptInfo->m_tChanInfo.m_wDstID, ptInfo->m_tChanInfo.m_wScreenIndex));
				tAck.m_bAccept = FALSE;
				ptInfo->Clear();
				
				memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
				memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
				NotifyMsgToHdu(ev_AddTvMonitor_ack, abBuf, sizeof(abBuf));

				pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_InvalidMT);

				return;
			}

			if (tReq.m_tReq.m_bVmp && CTpTypeAdpt::ResolutionMaxOpr(ptNode->m_tVidSndFormat.m_tFormat.m_emRes, emTPVHD720p1280x720))
			{// 合成通道，只能支持720p解码，如果会场发送能力大于720且不支持降分辨率，则拒绝进
				if (!ptNode->IsCanAdjustRes())
				{
					MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Ep can not In Vmp. ConfID:%d, epID:%d.\n", 
						pcInst->GetInsID(), ptInfo->m_tChanInfo.m_wDstID));
					tAck.m_bAccept = FALSE;
					ptInfo->Clear();
					
					memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
					memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
					NotifyMsgToHdu(ev_AddTvMonitor_ack, abBuf, sizeof(abBuf));

					pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, Tp_UMS_TvWall_MTVmpFail);

					return;
				}
				ptInfo->m_bAdjstRes = TRUE; // 需要降分辨率
			}
			
			EmGetVidRes emRes = pcInst->GetVidAudEx()->AssignByScreen(pcInst, tReq.m_tReq.m_wDstID, tReq.m_tReq.m_wScreenNum, 
									em_GetVid_Hdu, TCallVidFormat(), TRUE, ptInfo->m_tAddr, ptInfo->m_wGetVidIndex);
			if (em_GetVid_Success == emRes)
			{
				tAck.m_byVidPayload = MEDIA_TYPE_H264;
				tAck.m_byAudPayload = CTpTypeAdpt::GetAudPayloadValue(ptNode->m_tAudSndFormat.m_tFormat.m_emFormat);

				if (!ptInfo->m_bAdjstRes)
				{
					//创建交换
					CreateMediaTrans(pcInst, ptInfo);

					pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);
				}
				else if (ptNode->m_wEpID != pcInst->curSpeakerID())
				{
					// 降分辨率
					pcInst->GetNodeMgr()->AdjustNodeRes(ptNode->m_wEpID, tReq.m_tReq.m_wScreenNum, emTPVHD720p1280x720);
					CreateMediaTrans(pcInst, ptInfo);

					pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);
				}
				else
				{
					//只能暂时黑屏。。。。
                    pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_VmpCapFail);
				}
			}
			else
			{
				MdlError(Ums_Mdl_Call, ("OnAddMonitor error! GetVid Fail. ConfID:%d, epID:%d, Ret:%d\n", 
											pcInst->GetInsID(), ptInfo->m_tChanInfo.m_wEpID, emRes));
				tAck.m_bAccept = FALSE;
				ptInfo->Clear();
				
				memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
				memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
				NotifyMsgToHdu(ev_AddTvMonitor_ack, &abBuf, sizeof(abBuf));

				pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_BandError);

				return;
			}
		}
		else
		{
			if (!tReq.m_tReq.m_bVmp)
			{
				ptInfo->m_ptVmp = pcInst->GetVmp()->VmpToTvWall(tReq.m_tReq.m_wDstID, HduBrdVmpCB, this);
				if (NULL == ptInfo->m_ptVmp)
				{
					MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Assign vmp failed.\n"));
					tAck.m_bAccept = FALSE;
					ptInfo->Clear();
					
					memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
					memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
					NotifyMsgToHdu(ev_AddTvMonitor_ack, &abBuf, sizeof(abBuf));

					pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_AssignVmpFail);

					return;
				}
				else
				{
					u16 wMaxHp = TP_INVALID_INDEX;
					u16 wMaxBp = TP_INVALID_INDEX;
					CTpTypeAdpt::GetConfBaseMaxCap(pcInst->GetConfBase(), wMaxHp, wMaxBp);
					if (TP_INVALID_INDEX == wMaxHp && TP_INVALID_INDEX == wMaxBp)
					{
						MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Not vaild format.\n"));
						tAck.m_bAccept = FALSE;
						ptInfo->Clear();
						
						memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
						memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
						NotifyMsgToHdu(ev_AddTvMonitor_ack, &abBuf, sizeof(abBuf));
						return;
					}

					if (TP_INVALID_INDEX != wMaxHp)
					{
						ptInfo->m_tFormat = pcInst->GetConfBase().m_atTpMainVideoRes[wMaxHp];
					}
					else
					{
						ptInfo->m_tFormat = pcInst->GetConfBase().m_atTpMainVideoRes[wMaxBp];
					}

					tAck.m_byVidPayload = MEDIA_TYPE_H264;
					tAck.m_byAudPayload = MEDIA_TYPE_H264;

					//创建交换
					CreateMediaTrans(pcInst, ptInfo);

					pcInst->GetVmp()->AskFrameToBrdVmp(ptInfo->m_ptVmp, ptInfo->m_tFormat);
				}
			}
			else
			{
				MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Vmp chan.\n"));
				tAck.m_bAccept = FALSE;
				ptInfo->Clear();
				
				memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
				memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
				NotifyMsgToHdu(ev_AddTvMonitor_ack, &abBuf, sizeof(abBuf));
				return;
			}
		}

		tAck.m_bAccept = TRUE;
		if (EmEpType_Ter == tReq.m_tReq.m_emType)
		{
			tAck.m_tVidAddr = ptInfo->m_tAddr.m_atVidAddr[MIDSCREENINDEX];
			tAck.m_tAudAddr = ptInfo->m_tAddr.m_atAudAddr[MIDSCREENINDEX];
		}
		else
		{
			TTPDsFrom tVmp;
			pcInst->GetVmp()->GetBrdVmpOutAddr(ptInfo->m_ptVmp, tVmp, ptInfo->m_tFormat);
			tAck.m_tVidAddr.m_tRtpAddr = tVmp.m_tRtpAddr;
			tAck.m_tVidAddr.m_tBackRtcpAddr = tVmp.m_tBackRtcpAddr;
		}

	//	u16 wConfID = pcInst->GetInsID();
		memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
		memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
		NotifyMsgToHdu(ev_AddTvMonitor_ack, abBuf, sizeof(abBuf));

		for (u8 byIndx = 0; byIndx < TP_MAX_OLD_KEY_NUM; byIndx++)
		{
			if (0 == pcInst->m_atMediaKey[byIndx].m_dwQtFlag)
			{
				continue;
			}
			
			SetMediaKey(pcInst, pcInst->m_atMediaKey[byIndx], ptInfo);
		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Not Find pcInst.\n"));
		tAck.m_bAccept = FALSE;
		ptInfo->Clear();

		memcpy(abBuf, &tAck, sizeof(TAddTvMonitorAck));
		memcpy(abBuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));
		NotifyMsgToHdu(ev_AddTvMonitor_ack, abBuf, sizeof(abBuf));
	}
	return;
}

void CTvWallMgr::OnDelMonitor(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();
	TTPHduPlayReq* ptReq = (TTPHduPlayReq*)(pData);
	NotifyMsgToHdu(ev_DelTvMonitor_ack, ptReq, sizeof(TTPHduPlayReq));

	u16 wScreenNum = ptReq->m_wScreenNum;
	
	TVWallInfo* ptInfo = NULL;
	for (u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		if (m_atInfo[wIndex].m_tChanInfo.m_bUsed && ptReq->m_wIndex == m_atInfo[wIndex].m_tChanInfo.m_wChan &&
			ptReq->m_emType == m_atInfo[wIndex].m_tChanInfo.m_emType && ptReq->m_wConfID == m_atInfo[wIndex].m_tChanInfo.m_wConfID &&
			ptReq->m_bySubIndex == m_atInfo[wIndex].m_tChanInfo.m_bySubChan && ptReq->m_wDstID == m_atInfo[wIndex].m_tChanInfo.m_wDstID && 
			ptReq->m_wScreenNum == m_atInfo[wIndex].m_tChanInfo.m_wScreenIndex)
		{
			ptInfo = &(m_atInfo[wIndex]);
			break;
		}
	}
	
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("OnDelMonitor Dst not exist! index:%d, Screen:%d\n", ptReq->m_wIndex, wScreenNum));
		return;
	}
	
	MdlHint(Ums_Mdl_Call, ("OnDelMonitor index:%d, Screen:%d\n", ptReq->m_wIndex, wScreenNum));	
	
	CUmsConfInst* pcInst = (CUmsConfInst*)(pcApp->GetInstance(ptInfo->m_tChanInfo.m_wConfID));

	DestroyMediaTrans(pcInst, ptInfo);

	if ( ptInfo->m_bAdjstRes )
	{
		pcInst->GetNodeMgr()->AdjustNodeRes(ptInfo->m_tChanInfo.m_wEpID, ptInfo->m_tChanInfo.m_wScreenIndex, emTPVHD720p1280x720, TRUE);
	}
		
	if ( ptInfo->m_wGetVidIndex < TP_UMS_MAX_CALLNUM )
	{
		pcInst->m_pcGetVidEx->Release(pcInst, ptInfo->m_wGetVidIndex);
	}

	ptInfo->Clear();

	return;
}


void CTvWallMgr::OnUptateMonitor( CTpMsg *const ptMsg, CApp* pcApp )
{// 用于电视墙通道模式切换
	u8* pData = ptMsg->GetBody();	
	TAddTvMonitor tReq;
	TP_SAFE_CAST(tReq, pData);

	TVWallInfo* ptInfo = NULL;
	for (u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		if (m_atInfo[wIndex].m_tChanInfo.m_bUsed && m_atInfo[wIndex].m_tChanInfo.m_bOpenToServer && 
			tReq.m_tReq.m_wConfID == m_atInfo[wIndex].m_tChanInfo.m_wConfID &&
			tReq.m_tReq.m_wIndex == m_atInfo[wIndex].m_tChanInfo.m_wChan &&
			tReq.m_tReq.m_bySubIndex == m_atInfo[wIndex].m_tChanInfo.m_bySubChan)
		{
			ptInfo = &(m_atInfo[wIndex]);
			break;
		}
	}

	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Call, ("OnUptateMonitor. Dst not exist! index:%d, subChan:%d\n", tReq.m_tReq.m_wIndex, tReq.m_tReq.m_bySubIndex));
		return;
	}

	if (tReq.m_tReq.m_emType != ptInfo->m_tChanInfo.m_emType || tReq.m_tReq.m_wDstID != ptInfo->m_tChanInfo.m_wDstID
		|| tReq.m_tReq.m_wScreenNum != ptInfo->m_tChanInfo.m_wScreenIndex)
	{
		MdlError(Ums_Mdl_Call, ("OnUptateMonitor. not Same ep info! index:%d, subChan:%d, Type:%d, EpId:%d, ScreenIndex:%d\n", 
			tReq.m_tReq.m_wIndex, tReq.m_tReq.m_bySubIndex, tReq.m_tReq.m_emType, tReq.m_tReq.m_wDstID, tReq.m_tReq.m_wScreenNum));
		return;
	}

	if (ptInfo->m_tChanInfo.m_bVmp == tReq.m_tReq.m_bVmp)
	{
		MdlError(Ums_Mdl_Call, ("OnUptateMonitor. Same Vmp info! index:%d, subChan:%d, bvmp:%d\n", 
			tReq.m_tReq.m_wIndex, tReq.m_tReq.m_bySubIndex, tReq.m_tReq.m_bVmp));
		return;
	}

	BOOL32 bRet = TRUE;
	TCallNode* ptNode = NULL;
	TCapNode* ptFarterNode = NULL;

	CUmsConfInst* pcInst = (CUmsConfInst*)(pcApp->GetInstance(ptInfo->m_tChanInfo.m_wConfID));

	do 
	{
		if (NULL == pcInst)
		{
			MdlError(Ums_Mdl_Call, ("OnUptateMonitor. Conf is Null! ConfiD:%d.\n", ptInfo->m_tChanInfo.m_wConfID));
			bRet = FALSE;
			break;
		}

		if (tReq.m_tReq.m_bVmp)
		{// 原先是非合成通道，现在是合成通道
			if (ptInfo->m_tChanInfo.m_emType == EmEpType_Eqp)
			{// 外设不能进合成通道，删除
				bRet = FALSE;
				break;
			}

			ptNode = pcInst->GetNodeMgr()->GetNode(ptInfo->m_tChanInfo.m_wDstID);
			ptFarterNode = pcInst->GetNodeMgr()->GetForeFatherNode(ptNode);
			if (NULL == ptNode || NULL == ptFarterNode)
			{
				bRet = FALSE;
				break;
			}

			if (CTpTypeAdpt::ResolutionMaxOpr(ptNode->m_tVidSndFormat.m_tFormat.m_emRes, emTPVHD720p1280x720))
			{
				if (!ptNode->IsCanAdjustRes())
				{
					bRet = FALSE;
					break;
				}
				ptInfo->m_bAdjstRes = TRUE; // need 降分辨率
			}

			bRet = TRUE;
			ptInfo->m_tChanInfo.m_bVmp = tReq.m_tReq.m_bVmp;
			ptInfo->m_tChanInfo.m_tTvVidRcv = tReq.m_tVidAddr;
			ptInfo->m_tChanInfo.m_tTvAudRcv = tReq.m_tAudAddr;

			if (!ptInfo->m_bAdjstRes)
			{
				CreateMediaTrans(pcInst, ptInfo);

				pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);
			}
			else if (ptNode->m_wEpID != pcInst->curSpeakerID())
			{
				pcInst->GetNodeMgr()->AdjustNodeRes(ptNode->m_wEpID, tReq.m_tReq.m_wScreenNum, emTPVHD720p1280x720);
				CreateMediaTrans(pcInst, ptInfo);

				pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);
			}
			else
			{// 拆掉交换，黑屏
				CNetPortMgr::FreeMediaTrans(pcInst, ptInfo->m_tChanInfo.m_tToHdu);
				pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_VmpCapFail);

			}

		}
		else
		{// 原先是合成通道，现在是非合成通道
			ptNode = pcInst->GetNodeMgr()->GetNode(ptInfo->m_tChanInfo.m_wDstID);
			ptFarterNode = pcInst->GetNodeMgr()->GetForeFatherNode(ptNode);
			if (NULL == ptNode || NULL == ptFarterNode)
			{
				bRet = FALSE;
				break;
			}

			bRet = TRUE;
			ptInfo->m_tChanInfo.m_bVmp = tReq.m_tReq.m_bVmp;
			ptInfo->m_tChanInfo.m_tTvVidRcv = tReq.m_tVidAddr;
			ptInfo->m_tChanInfo.m_tTvAudRcv = tReq.m_tAudAddr;

			// 重新刷交换
			CreateMediaTrans(pcInst, ptInfo);

			pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);

			if (ptInfo->m_bAdjstRes)
			{// 恢复分辨率
				pcInst->GetNodeMgr()->AdjustNodeRes(ptInfo->m_tChanInfo.m_wEpID, ptInfo->m_tChanInfo.m_wScreenIndex, emTPVHD720p1280x720, TRUE);
			}
		}

	} while (0);

	
	if (!bRet)
	{// 删除

		CNetPortMgr::FreeMediaTrans(pcInst, ptInfo->m_tChanInfo.m_tToHdu);
		
		if ( ptInfo->m_bAdjstRes )
		{// 恢复终端分辨率
			pcInst->GetNodeMgr()->AdjustNodeRes(ptInfo->m_tChanInfo.m_wEpID, ptInfo->m_tChanInfo.m_wScreenIndex, emTPVHD720p1280x720, TRUE);
		}
		
		if (ptInfo->m_wGetVidIndex < TP_UMS_MAX_CALLNUM)
		{
			pcInst->m_pcGetVidEx->Release(pcInst, ptInfo->m_wGetVidIndex);
		}
		
		EmCnsCallReason  emRes = EmCnsCallReason_hungup;

		u8 byRes[sizeof(u16)+sizeof(u8)+sizeof(EmCnsCallReason)] = {0};
		memcpy(byRes, &ptInfo->m_tChanInfo.m_wChan, sizeof(u16));
		memcpy(byRes+sizeof(u16), &ptInfo->m_tChanInfo.m_bySubChan, sizeof(u8));
		memcpy(byRes+sizeof(u16)+sizeof(u8), &emRes, sizeof(EmCnsCallReason));
		NotifyMsgToHdu(ev_HungUpHdu_cmd, byRes, sizeof(byRes));
		
		ptInfo->Clear();
		
		// 需要提示，会场从电视墙删除
		pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, Tp_UMS_TvWall_MTVmpFail);

	}
	
	return;
}


void CTvWallMgr::OnAskKey(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();
	TTPHduPlayReq* ptReq = (TTPHduPlayReq*)(pData);

	u16 wScreenNum = ptReq->m_wScreenNum;
	
	TVWallInfo* ptInfo = NULL;
	for (u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		if (m_atInfo[wIndex].m_tChanInfo.m_bUsed && ptReq->m_wIndex == m_atInfo[wIndex].m_tChanInfo.m_wChan &&
			ptReq->m_emType == m_atInfo[wIndex].m_tChanInfo.m_emType && ptReq->m_wConfID == m_atInfo[wIndex].m_tChanInfo.m_wConfID &&
			ptReq->m_bySubIndex == m_atInfo[wIndex].m_tChanInfo.m_bySubChan && ptReq->m_wDstID == m_atInfo[wIndex].m_tChanInfo.m_wDstID && 
			ptReq->m_wScreenNum == m_atInfo[wIndex].m_tChanInfo.m_wScreenIndex)
		{
			ptInfo = &(m_atInfo[wIndex]);
			break;
		}
	}
	
	if (NULL == ptInfo)
	{
		tpLowDtl(Ums_Mdl_Call, "CTvWallMgr::OnAskKey Dst not exist! Screen:%d\n",wScreenNum);
		return;
	}
	
	tpLowDtl(Ums_Mdl_Call, "OnAskKey Screen:%d\n",wScreenNum);	
	
	CUmsConfInst* pcInst = (CUmsConfInst*)(pcApp->GetInstance(ptInfo->m_tChanInfo.m_wConfID));
	if (ptInfo->m_tChanInfo.m_bOpenToCall)
	{
		if (EmEpType_Ter == ptInfo->m_tChanInfo.m_emType)
		{
			pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex);
		}
		else
		{
			pcInst->GetVmp()->AskFrameToBrdVmp(ptInfo->m_ptVmp, ptInfo->m_tFormat);
		}
	}
}


// CUmsConfInst* CTvWallMgr::GetCallInfo(CApp* pcApp, TTvChanInfo* ptChan)
// {
// 	CUmsConfInst* pcInst = (CUmsConfInst*)(pcApp->GetInstance(ptChan->m_wConfID));
// 
// 	if (NULL == pcInst)
// 	{
// 		MdlError(Ums_Mdl_Call, ("CTvWallMgr::GetCallInfo Invalid conf.\n"));
// 		return NULL;
// 	}
// 
// 	if(CUmsConfInst::inst_idle == pcInst->CurState())
// 	{
// 		MdlError(Ums_Mdl_Call, ("CTvWallMgr::GetCallInfo Invalid conf state.\n"));
// 		return NULL;
// 	}
// 
// 	TCallNode* ptNode = pcInst->m_pcNodeMgr->GetNode(ptChan->m_wDstID);
// 	if (NULL == ptNode)
// 	{
// 		MdlError(Ums_Mdl_Call, ("CTvWallMgr::GetCallInfo Invalid node.\n"));
// 		return pcInst;
// 	}
// 		
// 
// 	ptChan->m_wConfID = pcInst->GetInsID();
// 	ptChan->m_wEpID = ptNode->m_wEpID;
// 	ptChan->m_bOpenToCall = FALSE;
// 
// 	return pcInst;
// }

void CTvWallMgr::CreateMediaTrans(CUmsConfInst* pcInst, TVWallInfo* ptInfo)
{
	if (NULL != pcInst || NULL != ptInfo)
	{
		//根据屏号建交换
		CNetPortMgr::CreateTvWallTrans(pcInst, ptInfo);
	}
	ptInfo->m_tChanInfo.m_bOpenToCall = TRUE;
	return;
}

void CTvWallMgr::DestroyMediaTrans(CUmsConfInst* pcInst, TVWallInfo* ptInfo)
{
	if (NULL != pcInst && NULL != ptInfo)
	{
		CNetPortMgr::DestroyTvWallTrans(pcInst, ptInfo);
	}
	ptInfo->m_tChanInfo.m_bOpenToCall = FALSE;
	return;
}

void CTvWallMgr::ChannelConnect(CUmsConfInst* pcInst, TCallNode* ptNode)
{
	if (NULL == pcInst || NULL == ptNode)
	{
		return;
	}

	if (ptNode->m_wEpID == pcInst->chairID())
	{

		HduPlanInfoReq(pcInst->GetInsID(), ptNode->m_wEpID);
	}

	TVWallInfo* ptInfo = NULL;
	for(u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		if (m_atInfo[wIndex].m_tChanInfo.m_bUsed &&
			m_atInfo[wIndex].m_tChanInfo.m_wConfID == pcInst->GetInsID() &&
			m_atInfo[wIndex].m_tChanInfo.m_wDstID == ptNode->m_wEpID &&
			!m_atInfo[wIndex].m_tChanInfo.m_bOpenToCall)
		{
			ptInfo = &m_atInfo[wIndex];
			
			TCapNode* ptFarther = pcInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
			if (NULL == ptFarther)
			{
				continue;
			}
			
			MdlHint(Ums_Mdl_Call, ("CTvWallMgr::ChannelConnect! wConfID:%d, Index:%d\n", pcInst->GetInsID(), wIndex));
			
			TAddTvMonitorAck tAck;	
			tAck.m_bAccept = TRUE;
			tAck.m_tEncrypt = pcInst->GetConfEncryptInfo();
			tAck.m_tReq.m_wIndex = ptInfo->m_tChanInfo.m_wChan;
			tAck.m_tReq.m_bySubIndex = ptInfo->m_tChanInfo.m_bySubChan;
			tAck.m_tReq.m_bVmp = ptInfo->m_tChanInfo.m_bVmp;
			tAck.m_tReq.m_emType = ptInfo->m_tChanInfo.m_emType;
			tAck.m_tReq.m_wConfID = ptInfo->m_tChanInfo.m_wConfID;
			tAck.m_tReq.m_wDstID = ptInfo->m_tChanInfo.m_wDstID;
			tAck.m_tReq.m_wScreenNum = ptInfo->m_tChanInfo.m_wScreenIndex;
			
			ptInfo->m_tChanInfo.m_bOpenToServer = TRUE;

			EmGetVidRes emRes = pcInst->GetVidAudEx()->AssignByScreen(pcInst, ptInfo->m_tChanInfo.m_wDstID, ptInfo->m_tChanInfo.m_wScreenIndex, 
				em_GetVid_Hdu, TCallVidFormat(), TRUE, ptInfo->m_tAddr, ptInfo->m_wGetVidIndex);
			if (em_GetVid_Success == emRes)
			{	
				tAck.m_byVidPayload = MEDIA_TYPE_H264;//CTpTypeAdpt::GetVidPayloadValue(pcInst->m_tConfBaseInfo.m_emTpVideoFormat);
				tAck.m_byAudPayload = CTpTypeAdpt::GetAudPayloadValue(ptNode->m_tAudSndFormat.m_tFormat.m_emFormat);

				if (!ptInfo->m_bAdjstRes)
				{
					CreateMediaTrans(pcInst, ptInfo);

					pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);
				}
				else if (ptNode->m_wEpID != pcInst->curSpeakerID())
				{// 非发言人，需要降分辨率，则降分辨率
					pcInst->GetNodeMgr()->AdjustNodeRes(ptNode->m_wEpID, ptInfo->m_tChanInfo.m_wScreenIndex, emTPVHD720p1280x720);
					CreateMediaTrans(pcInst, ptInfo);

					pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);
				}
				else
				{
                    pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_VmpCapFail);
					//电视墙只能暂时黑屏。。。。。
				}
			}
			else
			{
				tAck.m_bAccept = FALSE;
				ptInfo->Clear();
				// 需要提示，会场从电视墙删除
			}

			if (tAck.m_bAccept)
			{
				tAck.m_tVidAddr = ptInfo->m_tAddr.m_atVidAddr[MIDSCREENINDEX];
				tAck.m_tAudAddr = ptInfo->m_tAddr.m_atAudAddr[MIDSCREENINDEX];
			}

			u8 aybuf[sizeof(TAddTvMonitorAck) + sizeof(BOOL32)] = {0};
			memcpy(aybuf, &tAck, sizeof(TAddTvMonitorAck));
			BOOL32 bChangeMode = FALSE;
			memcpy(aybuf + sizeof(TAddTvMonitorAck), &bChangeMode, sizeof(BOOL32));

			NotifyMsgToHdu(ev_AddTvMonitor_ack, aybuf, sizeof(aybuf));
		}
	}
	return;
}

void CTvWallMgr::HungUpConf(CUmsConfInst* pcInst)
{
	if (NULL == pcInst)
	{
		return ;
	}

	u16 wConfID = pcInst->GetInsID();
	NotifyMsgToHdu(ev_HungUpConf_Hdu_cmd, &wConfID, sizeof(u16));
}

void CTvWallMgr::HungUpNode(CUmsConfInst* pcInst, TCallNode* ptNode, EmCnsCallReason emRes)
{//主动挂断 则踢出 其他原因删除交换
	if (NULL == pcInst || NULL == ptNode)
	{
		return;
	}
	TVWallInfo* ptInfo = NULL;
	for(u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		if (m_atInfo[wIndex].m_tChanInfo.m_bUsed 
			&& m_atInfo[wIndex].m_tChanInfo.m_wEpID == ptNode->m_wEpID 
			&& m_atInfo[wIndex].m_tChanInfo.m_wConfID == pcInst->GetInsID())
		{
			ptInfo = &(m_atInfo[wIndex]);
			
			MdlHint(Ums_Mdl_Call, ("[CTvWallMgr] HungUpNode! wConfID:%d, Index:%d\n", pcInst->GetInsID(), wIndex));
			
			DestroyMediaTrans(pcInst, ptInfo);			
			ptInfo->m_tChanInfo.m_bOpenToServer = FALSE;

			u8 byRes[sizeof(u16)+sizeof(u8)+sizeof(EmCnsCallReason)] = {0};
			memcpy(byRes, &(ptInfo->m_tChanInfo.m_wChan), sizeof(u16));
			memcpy(byRes+sizeof(u16), &(ptInfo->m_tChanInfo.m_bySubChan), sizeof(u8));
			memcpy(byRes+sizeof(u16)+sizeof(u8), &emRes, sizeof(EmCnsCallReason));
			NotifyMsgToHdu(ev_HungUpHdu_cmd, byRes, sizeof(byRes));

			if (ptInfo->m_wGetVidIndex < TP_UMS_MAX_CALLNUM)
			{
				pcInst->m_pcGetVidEx->Release(pcInst, ptInfo->m_wGetVidIndex);
				ptInfo->m_wGetVidIndex = TP_UMS_MAX_CALLNUM;
			}

			if (EmCnsCallReason_hungup == emRes || EmCnsCallReason_peerhungup == emRes)
			{
				ptInfo->Clear();
			}
		}
	}
	return;
}

//新发言人 如果是需要降分辨率，则恢复并拆掉交换
//老发言人 如果是需要降分辨率，则降并创建交换
void CTvWallMgr::ChangeSpeaker( CUmsConfInst* pcInst )
{
	if (NULL == pcInst)
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[CTvWallMgr] ChangeSpeaker! wConfID:%d\n", pcInst->GetInsID()));

	TVWallInfo* ptInfo = NULL;
	for(u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		ptInfo = &(m_atInfo[wIndex]);

		if ( !ptInfo->m_tChanInfo.m_bUsed )
		{
			continue;
		}

		if ( ptInfo->m_tChanInfo.m_wConfID != pcInst->GetInsID() )
		{
			continue;
		}

		if ( m_atInfo[wIndex].m_tChanInfo.m_wEpID == pcInst->curSpeakerID() )
		{
			if ( m_atInfo[wIndex].m_bAdjstRes )
			{
				DestroyMediaTrans(pcInst, ptInfo);
				pcInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_VmpCapFail);
				pcInst->GetNodeMgr()->AdjustNodeRes(ptInfo->m_tChanInfo.m_wEpID, ptInfo->m_tChanInfo.m_wScreenIndex, emTPVHD720p1280x720, TRUE);
			}

			continue;
		}

		if ( m_atInfo[wIndex].m_tChanInfo.m_wEpID == pcInst->oldSpeakerID() )
		{
			if ( m_atInfo[wIndex].m_bAdjstRes )
			{
				TCallNode* ptNode = pcInst->m_pcNodeMgr->GetNode(pcInst->oldSpeakerID());
				TCapNode* ptFarther = pcInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
				if (NULL == ptNode || NULL == ptFarther)
				{
					return;
				}
				pcInst->GetNodeMgr()->AdjustNodeRes(ptInfo->m_tChanInfo.m_wEpID, ptInfo->m_tChanInfo.m_wScreenIndex, emTPVHD720p1280x720);
				CreateMediaTrans(pcInst, ptInfo);

				pcInst->GetVidAudEx()->AskKeyFrame(ptInfo->m_wGetVidIndex, TRUE);
			}
		}
	}
}

extern CUmsCallMgrApp g_cUmsCallMgrApp;
void CTvWallMgr::BrdVmpCB( TBrdVmpRes* ptRes, EmBrdVmpCBOprType emOpr)
{//合成器掉线或释放
	MdlHint(Ums_Mdl_Call, ("[CTvWallMgr] BrdVmpCB! VmpID:%d\n", ptRes->m_tEqpRes.m_byEqpID));
	
	EmCnsCallReason emRes = EmCnsCallReason_hungup;

	TVWallInfo* ptInfo = NULL;
	CUmsConfInst* pInst = NULL;
	for(u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		ptInfo = &(m_atInfo[wIndex]);
		
		if ( !ptInfo->m_tChanInfo.m_bUsed )
		{
			continue;
		}

		if ( ptInfo->m_ptVmp != ptRes )
		{
			continue;
		}

		pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(ptInfo->m_tChanInfo.m_wConfID));
		if (NULL == pInst)
		{
			continue;
		}

		CNetPortMgr::FreeMediaTrans(pInst, ptInfo->m_tChanInfo.m_tToHdu);
		
		u8 byRes[sizeof(u16)+sizeof(u8)+sizeof(EmCnsCallReason)] = {0};
		memcpy(byRes, &(ptInfo->m_tChanInfo.m_wChan), sizeof(u16));
		memcpy(byRes+sizeof(u16), &(ptInfo->m_tChanInfo.m_bySubChan), sizeof(u8));
		memcpy(byRes+sizeof(u16)+sizeof(u8), &emRes, sizeof(EmCnsCallReason));
		NotifyMsgToHdu(ev_HungUpHdu_cmd, byRes, sizeof(byRes));
		if (EmBrdVmpCBOprType_Stop == emOpr)
		{
			pInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_VmpStop);

		} else
		{
			pInst->NotifyReasonToUI(EmUI_UMC|EmUI_CNC, TP_UMS_TvWall_VmpError);

		}

		
		

		ptInfo->Clear();
	}
}

////////////////////////////////////////////////
/////// 终端操作电视墙相关

void CTvWallMgr::EventHduPlayReq(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	TTPHduPlayReq tInfo;
	TP_SAFE_CAST(tInfo, pData + sizeof(tHandle));


	MdlHint(Ums_Mdl_Call,("[call]EventHduPlayReq EpID:%d EmType:%d, ConfID:%d, DstID:%d, BrdAlias:%s, ScreenNum:%d, Index:%d, SubIndex:%d, IsVmp:%d.\n"
		, tHandle.GetEpID(), tInfo.m_emType, tInfo.m_wConfID, tInfo.m_wDstID, tInfo.m_achAlias, tInfo.m_wScreenNum
		, tInfo.m_wIndex, tInfo.m_bySubIndex, tInfo.m_bVmp));

	NotifyMsgToHdu(evTPCNS_UMS_HduPlay_Req, ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CTvWallMgr::EventHduPlayInd(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	TPHduBaseInfo tBaseInfo;
	TP_SAFE_CAST(tBaseInfo, pData + sizeof(tHandle));
	EmTpHduPlayNackReason emReason;
	TP_SAFE_CAST(emReason, pData+sizeof(tHandle)+sizeof(tBaseInfo));
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduPlayInd EpID:%d index:%d SubIndex:%d reason:%d \n"
		, tHandle.GetEpID(), tBaseInfo.m_wIndex, tBaseInfo.m_bySubIndex, emReason));

	void* pBuf = (void*)(ptMsg->GetBody()+sizeof(tHandle));
	u16 wSize  =  ptMsg->GetBodyLen() - sizeof(tHandle);
	NotifyMsgToCns(pcApp, evTPUMS_CNS_HduPlay_Ind, tHandle, pBuf, wSize);
}

void CTvWallMgr::EventHduStopReq(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	TTPHduPlayReq tInfo;
	TP_SAFE_CAST(tInfo, pData + sizeof(tHandle));
	
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduStopReq EpID:%d EmType:%d, ConfID:%d, DstID:%d, BrdAlias:%s, ScreenNum:%d, Index:%d, SubIndex:%d, IsVmp:%d.\n"
		, tHandle.GetEpID(), tInfo.m_emType, tInfo.m_wConfID, tInfo.m_wDstID, tInfo.m_achAlias, tInfo.m_wScreenNum
		, tInfo.m_wIndex, tInfo.m_bySubIndex, tInfo.m_bVmp));
	
	
	NotifyMsgToHdu(evTPCNS_UMS_HduStopPlay_Req, ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CTvWallMgr::EventHduStopInd(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	TPHduBaseInfo tBaseInfo;
	TP_SAFE_CAST(tBaseInfo, pData + sizeof(tHandle));
	u16 wErrReason;
	TP_SAFE_CAST(wErrReason, pData+sizeof(tHandle)+sizeof(tBaseInfo));
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduStopInd EpID:%d index:%d SubIndex:%d reason:%d \n"
		, tHandle.GetEpID(), tBaseInfo.m_wIndex, tBaseInfo.m_bySubIndex, wErrReason));
	
	void* pBuf = (void*)(ptMsg->GetBody()+sizeof(tHandle));
	u16 wSize  =  ptMsg->GetBodyLen() - sizeof(tHandle);
	NotifyMsgToCns(pcApp, evTPUMS_CNS_HduStopPlay_Ind, tHandle, pBuf, wSize);		
}

void CTvWallMgr::EventHduAllStopReq(CTpMsg *const ptMsg, CApp* pcApp)
{		
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduAllStopReq EpID:%d \n", tHandle.GetEpID()));

	NotifyMsgToHdu(evTPCNS_UMS_HduStopAllPlay_Req, ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CTvWallMgr::EventHduSetVolReq(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	THduSetVolInfo tInfo;
	TP_SAFE_CAST(tInfo, pData + sizeof(tHandle));
	
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduSetVolReq EpID:%d HduInfo.index: %d, HduInfo.SubIndex:%d, byVol:%d, IsMute:%d.\n"
		, tHandle.GetEpID(), tInfo.m_tInfo.m_wIndex, tInfo.m_tInfo.m_bySubIndex, tInfo.m_byVol, tInfo.m_bMute));
	
	
	NotifyMsgToHdu(evTPCNS_UMS_HduSetVol_Req, ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CTvWallMgr::EventHduSetVolInd(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	THduSetVolInfo tVolInfo;
	TP_SAFE_CAST(tVolInfo, pData + sizeof(tHandle));
	EmTpHduSetVolRes emReason;
	TP_SAFE_CAST(emReason, pData+sizeof(tHandle)+sizeof(tVolInfo));
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduSetVolInd EpID:%d VolInfo.Index:%d VolInfo.SubIndex:%d vol:%d, mute:%d VolRes:%d \n"
		, tHandle.GetEpID(), tVolInfo.m_tInfo.m_wIndex, tVolInfo.m_tInfo.m_bySubIndex
		, tVolInfo.m_byVol, tVolInfo.m_bMute, emReason));
			
	
	void* pBuf = (void*)(ptMsg->GetBody()+sizeof(tHandle));
	u16 wSize  =  ptMsg->GetBodyLen() - sizeof(tHandle);
	NotifyMsgToAllOnLineChair(pcApp, evTPUMS_CNS_HduSetVol_Ind, tHandle, pBuf, wSize);	
}

void CTvWallMgr::EventHduChangeModeReq(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	THduChanModeSetInfo tModeInfo;
	TP_SAFE_CAST(tModeInfo, pData + sizeof(tHandle));
	
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduChangeModeReq EpID:%d Index:%d, Mode:%d.\n"
		, tHandle.GetEpID(), tModeInfo.m_wIndex, tModeInfo.m_byMode));
	
	NotifyMsgToHdu(evTPCNS_UMS_HduChangeChanMode_Req, ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CTvWallMgr::EventHduChangeModeInd(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();	
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, pData);
	THduChanModeSetInfo tModeInfo;
	TP_SAFE_CAST(tModeInfo, pData + sizeof(tHandle));
	EmTpHduChangeChanModeRes emReason;
	TP_SAFE_CAST(emReason, pData+sizeof(tHandle)+sizeof(tModeInfo));
	
	MdlHint(Ums_Mdl_Call,("[call]EventHduChangeModeInd EpID:%d Index:%d mode:%d changeModeRes:%d \n"
				, tHandle.GetEpID(), tModeInfo.m_wIndex, tModeInfo.m_byMode, emReason));
	
	
	void* pBuf = (void*)(ptMsg->GetBody()+sizeof(tHandle));
	u16 wSize  =  ptMsg->GetBodyLen() - sizeof(tHandle);
	NotifyMsgToAllOnLineChair(pcApp, evTPUMS_CNS_HduChangeChanMode_Ind, tHandle, pBuf, wSize);
}

void CTvWallMgr::SendHduPlanInfo(CTpMsg *const ptMsg, CApp* pcApp)
{
	u8* pData = ptMsg->GetBody();
	TUmsHandle tHandle;
	THduPlanPackData tPlanPackData;
	TP_SAFE_CAST(tHandle, pData);
	TP_SAFE_CAST(tPlanPackData, pData + sizeof(tHandle));

	MdlHint(Ums_Mdl_Call,("[call]SendHduPlanInfo ConfId:%d EpId:%d Row:%d Col:%d AllNum:%d m_byFirst:%d m_CurentNum:%d \n"
		, tHandle.GetConfID(),tHandle.GetEpID(), tPlanPackData.m_byRow, tPlanPackData.m_byCol, tPlanPackData.m_wNum, tPlanPackData.m_byFirst
		, tPlanPackData.m_CurentNum));
	
	CUmsConfInst* pcInst = NULL;
	
	// 发送Hdu的变更消息给当前所有在线会议的主席
	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex)
	{		
		if (tHandle.GetConfID() != 0 && wIndex != tHandle.GetConfID())
		{
			continue;
		}
		
		pcInst = (CUmsConfInst*)(pcApp->GetInstance(wIndex));
		if (NULL == pcInst)
		{
			MdlError(Ums_Mdl_Call, ("SendHduPlanInfo error! conf %d inst is NULL! \n", wIndex));
			continue;
		}
		// 当前会议是否在运行中
		if (pcInst->CurState() == CUmsConfInst::inst_run)
		{
			CCallNodeMgr* cCallNodeMgr = pcInst->GetNodeMgr();	
			if (NULL == cCallNodeMgr)
			{
				MdlError(Ums_Mdl_Call, ("SendHduPlanInfo error! conf %d cCallNodeMgr is NULL! \n", wIndex));
				continue;
			}
			
			// 获取当前会议的主席
			u16 wChairIndex = pcInst->chairID();
			TUmsHandle tOutHandle;
			cCallNodeMgr->MakeCallerHandle(tOutHandle, wChairIndex);
			if (tOutHandle.m_dwAdapteID == 0)
			{
				MdlError(Ums_Mdl_Call, ("SendHduPlanInfo failed! event:%d->%s\n", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
				continue;
			}

			CTpMsg cMsg;	
			cMsg.SetEvent(evTPUMS_CNS_hduPlan_Nty);
			cMsg.SetBody(&tOutHandle, sizeof(tOutHandle));
			cMsg.CatBody(&tPlanPackData, sizeof(tPlanPackData));
			cMsg.Post(UMS_SIPADAPTER_APP_INST, tOutHandle.m_dwAdapteID, UMS_CALL_APP_INST(tOutHandle.GetConfID()));
		}
	}

}

void CTvWallMgr::NotifyMsgToCns(CApp* pcApp, u16 wEvent, const TUmsHandle& tHandle, const void* pBuf, u16 wSize)
{
	CUmsConfInst* pcInst = (CUmsConfInst*)(pcApp->GetInstance(tHandle.GetConfID()));
	if (NULL == pcInst)
	{
		MdlError(Ums_Mdl_Call, ("NotifyMsgToCns error! conf %d inst is NULL! \n", tHandle.GetConfID()));
		return;
	}

	CCallNodeMgr* cCallNodeMgr = pcInst->GetNodeMgr();
	if (NULL == cCallNodeMgr)
	{
		MdlError(Ums_Mdl_Call, ("NotifyMsgToCns error! conf %d cCallNodeMgr is NULL! \n", tHandle.GetConfID()));
		return;
	}

	TUmsHandle tOutHandle;
	cCallNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	if (tOutHandle.m_dwAdapteID == 0)
	{
		MdlError(Ums_Mdl_Call, ("[call]NotifyMsgToCns failed! event:%d->%s\n", wEvent, GetEventNamebyID(wEvent)));
		return;
	}
	
	CTpMsg cMsg;	
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tOutHandle, sizeof(tOutHandle));
	if (NULL != pBuf)
	{
		cMsg.CatBody(pBuf, wSize);
	}
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tOutHandle.m_dwAdapteID, UMS_CALL_APP_INST(tOutHandle.GetConfID()));
}

void CTvWallMgr::HduPlanInfoReq(u16 wConfID, u16 wEpID)
{
	u8 ayBuf[sizeof(u16)*2] = {0};
	memcpy(ayBuf, &wConfID, sizeof(u16));
	memcpy(ayBuf+sizeof(u16), &wEpID, sizeof(u16));

	NotifyMsgToHdu(ev_HduPlanInfo_Req, ayBuf, sizeof(ayBuf));
}


void CTvWallMgr::NotifyMsgToAllOnLineChair( CApp* pcApp, u16 wEvent, const TUmsHandle& tHandle, const void* pBuf, u16 wSize )
{
	CUmsConfInst* pcInst = NULL;
	
	// 发送Hdu的变更消息给当前所有在线会议的主席
	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex)
	{		
		if (tHandle.GetConfID() != 0 && wIndex != tHandle.GetConfID())
		{
			continue;
		}
		
		pcInst = (CUmsConfInst*)(pcApp->GetInstance(wIndex));
		if (NULL == pcInst)
		{
			MdlError(Ums_Mdl_Call, ("NotifyMsgToAllOnLineChair error! conf %d inst is NULL! \n", wIndex));
			continue;
		}
		// 当前会议是否在运行中
		if (pcInst->CurState() == CUmsConfInst::inst_run)
		{
			CCallNodeMgr* cCallNodeMgr = pcInst->GetNodeMgr();	
			if (NULL == cCallNodeMgr)
			{
				MdlError(Ums_Mdl_Call, ("NotifyMsgToAllOnLineChair error! conf %d cCallNodeMgr is NULL! \n", wIndex));
				continue;
			}
			
			// 获取当前会议的主席
			u16 wChairIndex = pcInst->chairID();
			TUmsHandle tOutHandle;
			cCallNodeMgr->MakeCallerHandle(tOutHandle, wChairIndex);
			if (tOutHandle.m_dwAdapteID == 0)
			{
				MdlError(Ums_Mdl_Call, ("NotifyMsgToAllOnLineChair failed! event:%d->%s\n", wEvent, GetEventNamebyID(wEvent)));
				continue;
			}
			
			CTpMsg cMsg;	
			cMsg.SetEvent(wEvent);
			cMsg.SetBody(&tOutHandle, sizeof(tOutHandle));
			cMsg.CatBody(pBuf, wSize);
			cMsg.Post(UMS_SIPADAPTER_APP_INST, tOutHandle.m_dwAdapteID, UMS_CALL_APP_INST(tOutHandle.GetConfID()));
		}
	}	
}


void CTvWallMgr::SetMediaKey(CUmsConfInst* pcInst, const TTPQTMediaKeyInfo& tInfo, TVWallInfo* ptInfo)
{
	TVWallInfo* ptInfoTmp = NULL;
	for (u16 wIndex = 0; wIndex < TV_WALL_MAX_CHAN; ++wIndex)
	{
		ptInfoTmp = &(m_atInfo[wIndex]);
		
		if ( !ptInfoTmp->m_tChanInfo.m_bUsed )
		{
			continue;
		}
		
		if ( ptInfo != NULL && ptInfo != ptInfoTmp )
		{
			continue;
		}
		
		if (ptInfoTmp->m_tChanInfo.m_bUsed && ptInfoTmp->m_tChanInfo.m_wConfID == pcInst->GetInsID())
		{
			u8 abBuf[sizeof(u16)+sizeof(u8)+sizeof(TTPQTMediaKeyInfo)] = {0};
			memcpy(abBuf, &(ptInfoTmp->m_tChanInfo.m_wChan), sizeof(u16));
			memcpy(abBuf+sizeof(u16), &(ptInfoTmp->m_tChanInfo.m_bySubChan), sizeof(u8));
			memcpy(abBuf+sizeof(u16)+sizeof(u8), &tInfo, sizeof(tInfo));
			NotifyMsgToHdu(ev_TvMonitor_MediaKey_Nty, abBuf, sizeof(abBuf));
		}
	}
}
