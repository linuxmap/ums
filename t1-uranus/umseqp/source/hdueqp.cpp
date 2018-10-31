#include "hdueqp.h"
#include "mcudef.h"
#include "innereventumshdu.h"
#include "eventoutumstool.h"
#include "eventoutumseqp.h"
#include "eqpinst.h"
#include "eventoutumscommonbrd.h"
CHduEqp::CHduEqp(CUmsEqpInst* pInst)
				 : CEqpBase(pInst)
{
	
}

CHduEqp::~CHduEqp()
{
	
}


void CHduEqp::Init()
{
	
}

void CHduEqp::Handle(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();

	switch (wEvent)
	{
	case ev_hdu_disconnect:
		{
			EventDisconnect(ptMsg);
		}
		break;

	case ev_hdu_reg_req:		
		{
			EventRegReq(ptMsg);
		}
		break;
								
	case ev_hdu_reboot:			
		{
			EventReboot(ptMsg);
		}
		break;
		
	case ev_hdu_brd_modify:		
		{
			EventBrdModify(ptMsg);
		}
		break;
								
	case ev_hdu_update_req:		
		{
			EventUpdateBrd(ptMsg);
		}
		break;
	case ev_TPBrdSoftWareUpdate_Ack:
		{
			EventBrdUpdateAck(ptMsg);
		}
		break;
	case ev_hdu_chan_modify:	
		{
			EventChanModify(ptMsg);
		}
		break;

// 	case ev_hdu_chan_del:		
// 		{
// 			EventChanDel(ptMsg);
// 		}
// 		break;

	case ev_hdu_del:			
		{
			EventDel(ptMsg);
		}
		break;
		
	case ev_hdu_cfg_info:		
		{
			EventCfgInfo(ptMsg);
		}
		break;

	case ev_hdu_play_req:		
		{
			EventPlayReq(ptMsg);
		}
		break;

	case ev_hdu_play_ack:		
		{
			EventPlayAck(ptMsg);
		}
		break;

	case ev_hdu_play_nack:		
		{
			EventPlayNack(ptMsg);
		}
		break;

	case ev_hdu_stop_play_req:	
		{
			EventStopPlyaReg(ptMsg);
		}
		break;

	case ev_hdu_stop_play_ack:	
		{
			EventStopPlayAck(ptMsg);
		}
		break;

	case ev_hdu_stop_play_nack:	
		{
			EventStopPlayNack(ptMsg);
		}
		break;
		
	case ev_hdu_update_chan_status:
		{
			EventUpdateChanStatus(ptMsg);
		}
		break;
		
	case ev_hdu_updata_status:
		{
			EventUpdateStatus(ptMsg);
		}
		break;

	case ev_hdu_req_iframe:
		{
			EventReqIFrame(ptMsg);
		}
		break;

	case ev_hdu_set_vol:
		{
			EventSetVol(ptMsg);
		}
		break;
	case ev_hdu_change_chan_mode:
		{
			EventChangeHduChanMode(ptMsg);
		}
		break;
	case ev_hdu_change_chan_mode_res:
		{
			EventChangeHduChanModeRes(ptMsg);
		}
		break;

	case ev_hdu_media_key_nty:
		{
			EventMediaKeyNty(ptMsg);
		}
		break;

	default:					
		{
			MdlError(Ums_Mdl_Eqp, ("[CHduEqp::Handle] Unknow event ID:%d.\n", wEvent));
		}
		return ;
	}
}

void CHduEqp::EventChanModify(CTpMsg *const ptMsg)
{
	THduInfo tHduInfo;
	TP_SAFE_CAST(tHduInfo, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventChanModify]Channel Changed: Layer:%d, Slot:%d.\n", 
						   tHduInfo.m_byLayer, tHduInfo.m_bySlot));

	u16 wHudIndex = GetIndex(tHduInfo.m_byLayer, tHduInfo.m_bySlot);
	if (0 > wHudIndex || wHudIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventChanModify] Invalid Index. Index:%d.\n", wHudIndex));
		return ;
	}

	m_acHduModle[wHudIndex].SetChanInfo(tHduInfo);

 	if (m_acHduModle[wHudIndex].m_bServiceReged)
 	{
 		SendMsgToEqpSsn(m_acHduModle[wHudIndex].m_dwUserInst, ev_hdu_notify_channel, (u8*)(&tHduInfo), sizeof(THduInfo));
 	}
}

void CHduEqp::EventReboot(CTpMsg *const ptMsg)
{
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tBrdPos, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::EventReboot] Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n",
						   tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdPos.m_dwBrdIP)));

	u16 wIndex = GetIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);
	if (0 > wIndex || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventReboot] Invalid Index. Index:%d.\n", wIndex));
		return ;
	}

	m_acHduModle[wIndex].m_bRegsited = FALSE;
	m_acHduModle[wIndex].m_bServiceReged = FALSE;

	SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwBrdIns, ev_TPBrdReboot_Cmd, NULL, 0);
}

/*
void CHduEqp::EventUpdateBrdRes(CTpMsg *const ptMsg)
{
	THduUpdateRes tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventUpdateBrdNty] Layer:%d, Slot:%d, FileNum:%d.\n",
							  tRes.m_byLayer, tRes.m_bySlot, tRes.m_byFileNum));

	TTPBrdUpGrade tInfo;
	EmUpdateHduRet emRet = em_hdu_update_success;

	tInfo.m_byLayer = tRes.m_byLayer;
	tInfo.m_bySlot  = tRes.m_bySlot;
	for (u8 byIndex = 0; byIndex < tRes.m_byFileNum; ++byIndex)
	{
		memcpy(tInfo.m_szFileName, tRes.m_atFileInfo[byIndex].m_achFileName, tRes.m_atFileInfo[byIndex].m_byFileLength);
		if (1 != tRes.m_abyRes[byIndex])
		{
			emRet = em_hdu_update_unknow;
		}

		u8 abBuf[sizeof(TTPBrdUpGrade)+sizeof(EmUpdateHduRet)] = {0};
		memcpy(abBuf, &tInfo, sizeof(TTPBrdUpGrade));
		memcpy(abBuf+sizeof(TTPBrdUpGrade), &emRet, sizeof(EmUpdateHduRet));
		NotifyHduInfoToServer(ev_hdu_update_nty, abBuf, sizeof(abBuf));
	}
}
*/
void CHduEqp::EventBrdUpdateAck(CTpMsg *const ptMsg)
{
	BOOL32 bRes;
	TP_SAFE_CAST(bRes, ptMsg->GetBody());
	
	EmUpdateHduRet emRet = em_hdu_update_success;
	TTPBrdUpGrade tInfo;
	
	u8 byInstId = (u8)ptMsg->GetSrcIId();
	if (byInstId > HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdUpdateAck] hdu2 instId:%d error.\n", byInstId));
		emRet = em_hdu_update_unknow;
	}
	else
	{
		u8 byLayer = (byInstId - 1) / HDU_MAX_SLOT;
		u8 bySlot = (byInstId - 1) % HDU_MAX_SLOT;
		
		emRet = em_hdu_update_success;
		tInfo.m_byLayer = byLayer;
		tInfo.m_bySlot = bySlot;
	}
	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdUpdateAck] Layer:%d, Slot:%d, instId:%d, Res:%d\n", tInfo.m_byLayer, tInfo.m_bySlot, byInstId, bRes));
	
	u8 abBuf[sizeof(TTPBrdUpGrade)+sizeof(EmUpdateHduRet)] = {0};
	memcpy(abBuf, &tInfo, sizeof(TTPBrdUpGrade));
	memcpy(abBuf+sizeof(TTPBrdUpGrade), &emRet, sizeof(EmUpdateHduRet));
	NotifyHduInfoToServer(ev_hdu_update_nty, abBuf, sizeof(abBuf));
}

void CHduEqp::EventUpdateBrd(CTpMsg *const ptMsg)
{
	TTPBrdUpGrade tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventUpdateBrd] Layer:%d, Slot:%d, FileName:%s.\n",
							  tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_szFileName));

	EmUpdateHduRet emRet = em_hdu_update_success;
	u16 wIndex = 0;
	do 
	{
		wIndex = GetIndex(tInfo.m_byLayer, tInfo.m_bySlot);
		if (0 > wIndex || wIndex >= HDU_MAX_NUM)
		{
			MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdModify] Invalid Index. Index:%d.\n", wIndex));
			emRet = em_hdu_update_unknow;
			break;
		}

		if (!m_acHduModle[wIndex].m_bServiceReged)
		{
			MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdModify] The hdu not reged.\n"));
			emRet = em_hdu_update_unreg;
			break;
		}

	} while (FALSE);

	if (em_hdu_update_success == emRet)
	{
		TBrdUpInfo tUpdate;
		tUpdate.m_byIndex = (u8)wIndex;
		tUpdate.m_byNameLen = strlen(tInfo.m_szFileName);
		memcpy(&tUpdate.m_szFileName, &tInfo.m_szFileName, sizeof(tUpdate.m_szFileName));
		SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwBrdIns, ev_TPBrdSoftWareUpdate_Req, (u8*)(&tUpdate), sizeof(TBrdUpInfo));
	}
	else
	{
		u8 abBuf[sizeof(TTPBrdUpGrade)+sizeof(EmUpdateHduRet)] = {0};
		memcpy(abBuf, &tInfo, sizeof(TTPBrdUpGrade));
		memcpy(abBuf+sizeof(TTPBrdUpGrade), &emRet, sizeof(EmUpdateHduRet));
		NotifyHduInfoToServer(ev_hdu_update_nty, abBuf, sizeof(abBuf));
	}
}

void CHduEqp::EventBrdModify(CTpMsg *const ptMsg)
{
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tBrdPos, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdModify] brdType:%d Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n",
						   tBrdPos.m_emBrdType, tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdPos.m_dwBrdIP)));

	u16 wIndex = GetIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);
	if (0 > wIndex || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdModify] Invalid Index. Index:%d.\n", wIndex));
		return ;
	}
	
	if (m_acHduModle[wIndex].m_bRegsited && m_acHduModle[wIndex].m_tRegInfo.m_dwEqpIP != tBrdPos.m_dwBrdIP)
	{
		MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdModify] Ip Modify. Disconnect to Brd. OldIP:"TPIPFORMAT", NewIP:"TPIPFORMAT".\n",
							   Tpu32ToIP(m_acHduModle[wIndex].m_tRegInfo.m_dwEqpIP), Tpu32ToIP(tBrdPos.m_dwBrdIP)));

		OspDisconnectTcpNode(m_acHduModle[wIndex].m_dwUserNode);

		m_acHduModle[wIndex].m_bServiceReged = FALSE;
		m_acHduModle[wIndex].m_bRegsited = FALSE;
	}
	
	m_acHduModle[wIndex].SetBrdPos(tBrdPos);
}

void CHduEqp::EventStopPlayAck(CTpMsg* const ptMsg)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::EventStopPlayAck] Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d.\n",
						   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_bySubChan));

	NotifyHduInfoToServer(ptMsg->GetEvent(), ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CHduEqp::EventStopPlayNack(CTpMsg* const ptMsg)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::EventStopPlayNack] Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d.\n",
						   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_bySubChan));
	
	NotifyHduInfoToServer(ptMsg->GetEvent(), ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CHduEqp::EventReqIFrame(CTpMsg* const ptMsg)
{
	THduIFrameInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlLowDtl(Ums_Mdl_Eqp, ("CHduEqp::EventReqIFrame EqpID:%d, ChanIndex:%d, SubChan:%d.\n",
							  tInfo.m_wEqpID, tInfo.m_byChanIndex, tInfo.m_bySubChan));
	u8 byIndex = 0;
	CHduModle* pcModule = FindModule(tInfo.m_wEqpID, byIndex);
	if (NULL == pcModule)
	{
		MdlError(Ums_Mdl_Eqp, ("CHduEqp::EventReqIFrame Not find the hdu.\n"));
		return ;
	}

	if (!pcModule->m_bServiceReged)
	{
		MdlError(Ums_Mdl_Eqp, ("CHduEqp::EventReqIFrame The hdu service is not reged.\n"));
		return ;
	}

//	if ( !pcModule->m_atSubChanAskKey[tInfo.m_bySubChan].CheckFrame())
//	{
//		MdlLowDtl(Ums_Mdl_Eqp, ("CHduEqp::EventReqIFrame. Ask frequent!! EqpID:%d, ChanIndex:%d, SubChan:%d.\n",
//							  tInfo.m_wEqpID, tInfo.m_byChanIndex, tInfo.m_bySubChan));
//		return ;
//	}

	tInfo.m_byLayer = GetLayer(byIndex);
	tInfo.m_bySlot = GetSlot(byIndex);

	NotifyHduInfoToServer(ptMsg->GetEvent(), (u8*)(&tInfo), sizeof(THduIFrameInfo));
}

void CHduEqp::EventSetVol(CTpMsg* const ptMsg)
{
	THduVolInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventSetVol] Layer:%d, Slot:%d, Chan:%d, Vol:%d, Mute:%d.\n",
								tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanlIdx, tInfo.m_byVolume, tInfo.m_byIsMute));
	
	EmTpHduSetVolRes emRes = em_hdu_SetVol_Success;
	u16 wIndex = 0;
	do 
	{
		wIndex = GetIndex(tInfo.m_byLayer, tInfo.m_bySlot);
		if (0 > wIndex || wIndex >= HDU_MAX_NUM)
		{
			MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventSetVol] Invalid Index. Index:%d.\n", wIndex));
			emRes = em_hdu_SetVol_Invalid_Index;
			break;
		}
		
		if (!m_acHduModle[wIndex].m_bServiceReged)
		{
			MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventSetVol] The hdu not reged.\n"));
			emRes = em_hdu_SetVol_UnReg;
			break;
		}
		
	} while (FALSE);
	
	if (emRes == em_hdu_SetVol_Success)
	{
		SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwUserInst, ptMsg->GetEvent(), (u8*)(&tInfo), sizeof(THduVolInfo));
	}

	u8 szRes[sizeof(THduVolInfo)+sizeof(EmTpHduSetVolRes)] = {0};
	memcpy(szRes, &tInfo, sizeof(THduVolInfo));
	memcpy(szRes+sizeof(THduVolInfo), &emRes, sizeof(EmTpHduSetVolRes));
	NotifyHduInfoToServer(ev_hdu_set_vol_res, szRes, sizeof(szRes));
	
	return;
}

void CHduEqp::EventUpdateStatus(CTpMsg* const ptMsg)
{
	THduUpdateInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CHduEqp::EventUpdateStatus EqpID:%d, OnLine:%d.\n",
							  tInfo.m_wEqpID, tInfo.m_bOnLine));

	u8 byIndex = 0;
	CHduModle* pcModule = FindModule(tInfo.m_wEqpID, byIndex);
	if (NULL == pcModule)
	{
		MdlError(Ums_Mdl_Eqp, ("CHduEqp::EventUpdateStatus Not find the hdu.\n"));
		return ;
	}
	
	tInfo.m_byLayer = GetLayer(byIndex);
	tInfo.m_bySlot = GetSlot(byIndex);
	
	NotifyHduInfoToServer(ptMsg->GetEvent(), (u8*)(&tInfo), sizeof(THduUpdateInfo));
}

void CHduEqp::EventUpdateChanStatus(CTpMsg* const ptMsg)
{
	THduChanStatus tStatus;
	TP_SAFE_CAST(tStatus, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CHduEqp::EventUpdateChanStatus EqpID:%d, ChanIndex:%d, Status:%d.\n",
							  tStatus.m_wEqpID, tStatus.m_byChanIndex, tStatus.m_byStatus));

	u8 byIndex = 0;
	CHduModle* pcModule = FindModule(tStatus.m_wEqpID, byIndex);
	if (NULL == pcModule)
	{
		MdlError(Ums_Mdl_Eqp, ("CHduEqp::EventUpdateChanStatus Not find the hdu.\n"));
		return ;
	}

	tStatus.m_byLayer = GetLayer(byIndex);
	tStatus.m_bySlot = GetSlot(byIndex);

	NotifyHduInfoToServer(ptMsg->GetEvent(), (u8*)(&tStatus), sizeof(THduChanStatus));
}

void CHduEqp::EventStopPlyaReg(CTpMsg* const ptMsg)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	u16 wIndex = GetIndex(tInfo.m_byLayer, tInfo.m_bySlot);

	MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::EventStopPlyaReg] Layer:%d, Slot:%d, ChanIndex:%d.\n",
						   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex));

	SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwUserInst, ptMsg->GetEvent(), ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CHduEqp::EventPlayAck(CTpMsg* const ptMsg)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventPlayAck] Layer:%d, Slot:%d, ChanIndex:%d.\n",
							  tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex));

	u16 wIndex = GetIndex(tInfo.m_byLayer, tInfo.m_bySlot);

	NotifyHduInfoToServer(ev_hdu_play_ack, ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CHduEqp::EventPlayNack(CTpMsg* const ptMsg)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventPlayNack] Layer:%d, Slot:%d, ChanIndex:%d.\n",
							  tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex));
	
	NotifyHduInfoToServer(ev_hdu_play_nack, ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CHduEqp::EventPlayReq(CTpMsg* const ptMsg)
{
	THduPlayInfo tInfo;
 	TAddTvMonitorAck tAck;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	TP_SAFE_CAST(tAck, ptMsg->GetBody()+sizeof(THduPlayInfo));

	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventPlayReq] Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d.\n",
							  tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_bySubChan));

	u16 wIndex = GetIndex(tInfo.m_byLayer, tInfo.m_bySlot);
	if (0 > wIndex || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventPlayReq] Index is invalid. Index:%d.\n", wIndex));
		NotifyHduInfoToServer(ev_hdu_play_nack, (u8*)(&tInfo), sizeof(THduPlayInfo));
		return ;
	}

	if (!m_acHduModle[wIndex].m_bRegsited || !m_acHduModle[wIndex].m_bServiceReged)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventPlayReq] Brd or Service not reged. BrdReg:%d, ServiceReg;%d.\n",
								m_acHduModle[wIndex].m_bRegsited, m_acHduModle[wIndex].m_bServiceReged));
		NotifyHduInfoToServer(ev_hdu_play_nack, (u8*)(&tInfo), sizeof(THduPlayInfo));
		return ;
	}

	SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwUserInst, ptMsg->GetEvent(), ptMsg->GetBody(), ptMsg->GetBodyLen());
}
 
void CHduEqp::EventCfgInfo(CTpMsg* const ptMsg)
{
	THduCfgInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::EventCfgInfo] Layer:%d, Slot:%d, bQtHdu:%d, IP:"TPIPFORMAT", ChanNum:%d, StartMode:%d.\n",
						  tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_bQtHdu, Tpu32ToIP(tInfo.m_dwIP), tInfo.m_byChanNum, tInfo.m_byStartMode));

	u16 wIndex = GetIndex(tInfo.m_byLayer, tInfo.m_bySlot);
	if (0 > wIndex || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventCfgInfo] Invalid Index. Index:%d.\n", wIndex));
		return ;
	}
	
	m_acHduModle[wIndex].SetCfgInfo(tInfo);
}

void CHduEqp::EventDel(CTpMsg *const ptMsg)
{
	u8 byLayer, bySlot;
	TP_SAFE_CAST(byLayer, ptMsg->GetBody());
	TP_SAFE_CAST(bySlot, ptMsg->GetBody()+sizeof(u8));
	
	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventDel] Layer:%d, Slot:%d.\n", byLayer, bySlot));

	u16 wIndex = GetIndex(byLayer, bySlot);
	if (wIndex < 0 || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventDel] Index:%d, is invalid.\n", wIndex));
		return ;
	}

	if (m_acHduModle[wIndex].m_bRegsited)
	{
		SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwUserInst, ptMsg->GetEvent(), ptMsg->GetBody(), ptMsg->GetBodyLen());
		
		//更新业务的注册状态
		THduRegStatus tInfo;
		tInfo.m_bRegRes = FALSE;
		tInfo.m_byLayer = byLayer;
		tInfo.m_bySlot  = bySlot;
		
		u8 abBuf[sizeof(THduRegStatus)+sizeof(u16)] = {0};
		memcpy(abBuf, &tInfo, sizeof(THduRegStatus));
		
		NotifyHduInfoToServer(ev_hdu_brd_reg_res, (u8*)(&tInfo), sizeof(THduRegStatus));
		NotifyHduInfoToServer(ev_hdu_service_reg_res, abBuf, sizeof(abBuf));
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventDel] Hdu not registed.\n"));
	}

	m_acHduModle[wIndex].Clear();
}

void CHduEqp::EventDisconnect(CTpMsg* const ptMsg)
{
	u32 dwSrcInst  = ptMsg->GetSrcIId();

	MdlLowHint(Ums_Mdl_Eqp, ("CHduEqp::EventDisconnect InsID:%d.\n",
							  dwSrcInst));

	u8 byIndex = 0;
	CHduModle* pcModle = FindModleByIns(dwSrcInst, byIndex);
	if (NULL == pcModle)
	{
		MdlLowHint(Ums_Mdl_Eqp, ("CHduEqp::EventDisconnect Not find the modle. InsID:%d.\n",
								  dwSrcInst));
		return ;
	}

// 	if (!pcModle->m_bServiceReged)
// 	{
// 		MdlLowHint(Ums_Mdl_Eqp, ("CHduEqp::EventDisconnect The hdu service is not reged. InsID:%d\n",
// 								  dwSrcInst));
// 		return ;
// 	}

	pcModle->m_bRegsited = FALSE;
	pcModle->m_bServiceReged = FALSE;

	//更新业务的注册状态
	THduRegStatus tInfo;
	tInfo.m_bRegRes = FALSE;
	tInfo.m_byLayer = GetLayer(byIndex);
	tInfo.m_bySlot  = GetSlot(byIndex);
	
	u8 abBuf[sizeof(THduRegStatus)+sizeof(u16)] = {0};
	memcpy(abBuf, &tInfo, sizeof(THduRegStatus));
	
	NotifyHduInfoToServer(ev_hdu_brd_reg_res, (u8*)(&tInfo), sizeof(THduRegStatus));
	NotifyHduInfoToServer(ev_hdu_service_reg_res, abBuf, sizeof(abBuf));
}

void CHduEqp::EventRegReq(CTpMsg *const ptMsg)
{
	u8* pData	  = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();
	u32 wSrcNode  = ptMsg->GetSrcNode();
	u32 wSrcInst  = ptMsg->GetSrcIId();

	THduRegInfo tRegInfo;
	TP_SAFE_CAST(tRegInfo, pData);

	u16 wHduIndex = GetIndex(tRegInfo.m_byLayer, tRegInfo.m_bySlot);
	if (wHduIndex < 0 || wHduIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventRegReq] Index:%d, is invalid.\n", wHduIndex));
		SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_hdu_req_nack, NULL, 0);
		return ;
	}

	CHduModle* pcModle = &(m_acHduModle[wHduIndex]);

	if (!pcModle->m_bRegsited)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventRegReq] The brd is not registed. IP:"TPIPFORMAT" \n", Tpu32ToIP(tRegInfo.m_dwIpAddr)));
		SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_hdu_req_nack, NULL, 0);

		return ;
	}

	if ((pcModle->m_bQtVer && tRegInfo.m_wVersion != DEVVER_HDU2) ||
		(!pcModle->m_bQtVer && tRegInfo.m_wVersion != DEVVER_HDU2_S))
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventRegReq] hdu ver not match. bQtVer:%d, m_wVersion:%d \n",
						pcModle->m_bQtVer, tRegInfo.m_wVersion));

		// 电视墙的启动模式异常需要重新启动
		TTPBrdPos tBrdPos;
		tBrdPos.m_byBrdLayer = tRegInfo.m_byLayer;
		tBrdPos.m_byBrdSlot = tRegInfo.m_bySlot;
		CTpMsg cMsg;
		cMsg.SetBody(&tBrdPos, sizeof(TTPBrdPos));
		EventReboot(&cMsg);

		SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_hdu_req_nack, NULL, 0);

		return;
	}

// 	if (pcModle->m_bServiceReged)
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventRegReq] Serviced is reged. IP:"TPIPFORMAT" \n", Tpu32ToIP(tRegInfo.m_dwIpAddr)));
// 		SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_hdu_req_nack, NULL, 0);
// 		return ;
// 	}

// 	if (!pcModle->m_atChanInfo[0].IsValid() ||
// 		!pcModle->m_atChanInfo[1].IsValid())
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventRegReq] Chan info is invalid. IP:"TPIPFORMAT" \n", Tpu32ToIP(tRegInfo.m_dwIpAddr)));
// 		SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_hdu_req_nack, NULL, 0);
// 		
// 		return ;
// 	}


	MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::EventRegReq] New Reg.EqpIP:"TPIPFORMAT", Node:%d, RegVersion:%d, bQtVer:%d.\n",
							Tpu32ToIP(tRegInfo.m_dwIpAddr), wSrcNode, tRegInfo.m_wVersion, pcModle->m_bQtVer));

	pcModle->m_dwUserInst = wSrcInst;
	pcModle->m_dwUserNode = wSrcNode;
	pcModle->m_tRegInfo.m_wEqpType = em_hdu_mdl;
	pcModle->m_bServiceReged = TRUE;
	pcModle->m_wStartPort = tRegInfo.m_wStartPort;

	TUmsRSParam		tUmsRsParam;
	THduRegCfgAck	tRegCfg;
	
	strncpy(tRegCfg.m_szAlias, pcModle->m_tRegInfo.m_achAlias, TP_MAXLEN_EQP_ALIAS);
	for (u16 wIndex = 0; wIndex < HDU_MAX_CHANNEL_NUM; ++wIndex)
	{
		memcpy(&(tRegCfg.m_atChanInfo[wIndex]), &(pcModle->m_atChanInfo[wIndex]), sizeof(THduChanInfo));
	}
	tRegCfg.m_wStartPort = tRegInfo.m_wStartPort;
	
	u8 abRes[sizeof(TUmsRSParam)+sizeof(THduRegCfgAck)] = {0};
	memcpy(abRes, &tUmsRsParam, sizeof(TUmsRSParam));
	memcpy(abRes+sizeof(TUmsRSParam), &tRegCfg, sizeof(THduRegCfgAck));
	
	SendMsgToEqpSsn(ptMsg->GetSrcIId(), ev_hdu_req_ack, abRes, sizeof(abRes));

	//更新业务的注册状态
	THduRegStatus tInfo;
	tInfo.m_bRegRes = TRUE;
	tInfo.m_byLayer = tRegInfo.m_byLayer;
	tInfo.m_bySlot  = tRegInfo.m_bySlot;
	
	u8 abBuf[sizeof(THduRegStatus)+sizeof(u16)] = {0};
	memcpy(abBuf, &tInfo, sizeof(THduRegStatus));
	memcpy(abBuf+sizeof(THduRegStatus), &(tRegInfo.m_wStartPort), sizeof(u16));

	NotifyHduInfoToServer(ev_hdu_service_reg_res, abBuf, sizeof(abBuf));

	THduInfo tHduInfo;
	tHduInfo.m_byLayer = tRegInfo.m_byLayer;
	tHduInfo.m_bySlot = tRegInfo.m_bySlot;
	tHduInfo.m_atChanInfo[0] = pcModle->m_atChanInfo[0];
	tHduInfo.m_atChanInfo[1] = pcModle->m_atChanInfo[1];

	CTpMsg cMsg;
	cMsg.SetBody(&tHduInfo, sizeof(THduInfo));
	EventChanModify(&cMsg);
}

CHduModle* CHduEqp::FindModleByIns(u32 dwInsID, u8& byVal)
{
	for (u8 byIndex = 0; byIndex < HDU_MAX_NUM; ++byIndex)
	{
		if (m_acHduModle[byIndex].m_dwUserInst == dwInsID)
		{
			byVal = byIndex;
			return &(m_acHduModle[byIndex]);
		}
	}
	
	return NULL;
}

CHduModle* CHduEqp::FindModleByIP(u32 dwIP, u8& byVal)
{
	for (u8 byIndex = 0; byIndex < HDU_MAX_NUM; ++byIndex)
	{
		if (m_acHduModle[byIndex].m_tRegInfo.m_dwEqpIP == dwIP)
		{
			byVal = byIndex;
			return &(m_acHduModle[byIndex]);
		}
	}

	return NULL;
}

CHduModle* CHduEqp::FindModule(u16 wEqpID, u8& byVal)
{
	for (u8 byIndex = 0; byIndex < HDU_MAX_NUM; ++byIndex)
	{
		if (m_acHduModle[byIndex].m_wEqpID == wEqpID)
		{
			byVal = byIndex;
			return &(m_acHduModle[byIndex]);
		}
	}
	
	return NULL;
}

void CHduEqp::SetBrdEqpID(u8 byLayer, u8 bySlot, u16 wEqpID)
{
	u16 wIndex = GetIndex(byLayer, bySlot);
	m_acHduModle[wIndex].m_wEqpID = wEqpID;
}

BOOL32 CHduEqp::CheckBrdInfo(const TTPBrdRegInfo& tBrdInfo, u32 dwNode, u32 dwIns)
{
	if (em_hdu2_brd != tBrdInfo.m_tBrdPos.m_emBrdType)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::CheckBrdInfo] The brd type is not hdu2. BrdType:%d.\n",
								tBrdInfo.m_tBrdPos.m_emBrdType));
		return FALSE;
	}

	u16 wIndex = GetIndex(tBrdInfo.m_tBrdPos.m_byBrdLayer, tBrdInfo.m_tBrdPos.m_byBrdSlot);
	if (wIndex < 0 || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::CheckBrdInfo] Invalid. Layer:%d, Slot:%d.\n",
								tBrdInfo.m_tBrdPos.m_byBrdLayer,
								tBrdInfo.m_tBrdPos.m_byBrdSlot));
		return FALSE;
	}

	if (m_acHduModle[wIndex].m_tRegInfo.m_dwEqpIP != tBrdInfo.m_tBrdPos.m_dwBrdIP)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::CheckBrdInfo] IP no equal. Layer:%d, Slot:%d, CfgIP:"IPFORMAT", RegIP:"IPFORMAT"\n",
								tBrdInfo.m_tBrdPos.m_byBrdLayer,
								tBrdInfo.m_tBrdPos.m_byBrdSlot,
								Tpu32ToIP(m_acHduModle[wIndex].m_tRegInfo.m_dwEqpIP),
								Tpu32ToIP(tBrdInfo.m_tBrdPos.m_dwBrdIP)));
		return FALSE;
	}

	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::CheckBrdInfo] BrdInfo  Layer:%d, Slot:%d, IP:"TPIPFORMAT", Node:%d.\n",
							  tBrdInfo.m_tBrdPos.m_byBrdLayer, tBrdInfo.m_tBrdPos.m_byBrdSlot,
							  Tpu32ToIP(tBrdInfo.m_tBrdPos.m_dwBrdIP), dwNode));

	m_acHduModle[wIndex].m_bRegsited  = TRUE;
	m_acHduModle[wIndex].m_dwUserNode = dwNode;
	m_acHduModle[wIndex].m_dwBrdIns = dwIns;
	
	THduRegStatus tRegStatus;
	tRegStatus.m_byLayer = tBrdInfo.m_tBrdPos.m_byBrdLayer;
	tRegStatus.m_bySlot  = tBrdInfo.m_tBrdPos.m_byBrdSlot;
	tRegStatus.m_bRegRes = TRUE;
	
	NotifyHduInfoToServer(ev_hdu_brd_reg_res, (u8*)&tRegStatus, sizeof(THduRegStatus));
	
	return TRUE;
}

BOOL32 CHduEqp::FindRegBrd(const TTPBrdPos& tBrdInfo)
{
	if (em_hdu2_brd != tBrdInfo.m_emBrdType)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::FindRegBrd] The brd type is not hdu2.\n"));
		return FALSE;
	}

	u16 wIndex = GetIndex(tBrdInfo.m_byBrdLayer, tBrdInfo.m_byBrdSlot);
	if (wIndex < 0 || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::FindRegBrd] Invalid index:%d.\n", wIndex));
		return FALSE;
	}

	if (m_acHduModle[wIndex].m_tRegInfo.m_dwEqpIP != tBrdInfo.m_dwBrdIP)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::FindRegBrd] IP no equal.\n"));
		return FALSE;
	}

	return m_acHduModle[wIndex].m_bRegsited;
}

void CHduEqp::SendMsgToEqpSsn(u32 dwSrcIID, u16 wEvent, u8 * const pbyMsg, u16 wLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	
	if (NULL != pbyMsg)
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	
	cMsg.Post(dwSrcIID, 0, UMS_EQP_APP_INST);
}

void CHduEqp::NotifyHduInfoToServer(u16 wEvent, u8* pbyMsg, u16 wLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	
	if (NULL != pbyMsg)
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_EQP_APP_INST);
}

BOOL32 CHduEqp::AssignEqpEx(TEqpParam* ptEqpParam)
{
	return TRUE;
}

BOOL32 CHduEqp::ReleaseEqpEx(TEqpParam* ptEqpParam)
{
	return TRUE;
}

BOOL32 CHduEqp::OnDisConnect(u32 dwNode)
{
	for (u8 byIndex = 0; byIndex < HDU_MAX_NUM; ++byIndex)
	{
		if (m_acHduModle[byIndex].m_dwUserNode == dwNode)
		{
			THduRegStatus tBrdInfo;
			tBrdInfo.m_byLayer = GetLayer(byIndex);
			tBrdInfo.m_bySlot  = GetSlot(byIndex);
			tBrdInfo.m_bRegRes = FALSE;

			u8 abBuf[sizeof(THduRegStatus)+sizeof(u16)] = {0};
			memcpy(abBuf, &tBrdInfo, sizeof(THduRegStatus));
			memcpy(abBuf+sizeof(THduRegStatus), &(m_acHduModle[byIndex].m_wStartPort), sizeof(u16));
			NotifyHduInfoToServer(ev_hdu_service_reg_res, abBuf, sizeof(abBuf));
			
			NotifyHduInfoToServer(ev_hdu_brd_reg_res, (u8*)&tBrdInfo, sizeof(THduRegStatus));

			//通知mcubrdmgr清除实例状态
			::OspPost(MAKEIID( AID_UMSBRD_REG_APP, tBrdInfo.m_byLayer*HDU_MAX_SLOT + tBrdInfo.m_bySlot + 1), 
																		OSP_DISCONNECT, (void*)&dwNode, sizeof(u32));

			MdlHint(Ums_Mdl_Eqp, ("[CHduEqp::OnDisConnect] Layer:%d, Slot:%d, Node:%d.\n", 
								   GetLayer(byIndex), GetSlot(byIndex), dwNode));

			m_acHduModle[byIndex].m_dwUserNode = 0;
			m_acHduModle[byIndex].m_bRegsited = FALSE;
			m_acHduModle[byIndex].m_bServiceReged = FALSE;

			return TRUE;
		}
	}

	MdlError(Ums_Mdl_Eqp, ("[CHduEqp::OnDisConnect] Not find the Node:%d.\n", dwNode));
	return FALSE;
}

void CHduEqp::Show()
{
	msgprintnotime("Hdu Info: \n");
	for (u8 byIndex = 0; byIndex < HDU_MAX_NUM; ++byIndex)
	{
		if (0 != m_acHduModle[byIndex].m_tRegInfo.m_dwEqpIP)
		{
			if (m_acHduModle[byIndex].m_bServiceReged)
			{
				msgprintnotime("Layer:%d, Slot:%d, IP:"TPIPFORMAT", BrdReg:%d, ServiceReg:%d, Node:%d, bQtVer:%d.\n",
					GetLayer(byIndex), GetSlot(byIndex), Tpu32ToIP(m_acHduModle[byIndex].m_tRegInfo.m_dwEqpIP),
					m_acHduModle[byIndex].m_bRegsited, m_acHduModle[byIndex].m_bServiceReged,
					m_acHduModle[byIndex].m_dwUserNode, m_acHduModle[byIndex].m_bQtVer);
				
				for (u8 byChanIndex = 0; byChanIndex < HDU_MAX_CHANNEL_NUM; ++byChanIndex)
				{
					msgprintnotime("ChanIndex:%d, PortType:%d, OutMode;%d, ZoomRate:%d, ShowMode:%d.\n", byChanIndex,
											m_acHduModle[byIndex].m_atChanInfo[byChanIndex].GetOutType(),
											m_acHduModle[byIndex].m_atChanInfo[byChanIndex].GetOutMode(),
											m_acHduModle[byIndex].m_atChanInfo[byChanIndex].GetZoomRate(),
											m_acHduModle[byIndex].m_atChanInfo[byChanIndex].GetShowMode());
				}
			}
		}
	}
}

void CHduEqp::EventChangeHduChanMode( CTpMsg* const ptMsg )
{
	THduChanModeInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventChangeHduMode] Layer:%d, Slot:%d, Chan:%d, ChanMode:%d.\n",
								tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_byChanMode));
	
	EmTpHduChangeChanModeRes emRes = em_hdu_change_mode_success;
	u16 wIndex = 0;
	do 
	{
		wIndex = GetIndex(tInfo.m_byLayer, tInfo.m_bySlot);
		if (0 > wIndex || wIndex >= HDU_MAX_NUM)
		{
			MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventChangeHduMode] Invalid Index. Index:%d.\n", wIndex));
			emRes = em_hdu_change_mode_error_index;
			break;
		}
		
		if (!m_acHduModle[wIndex].m_bServiceReged)
		{
			MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventChangeHduMode] The hdu not reged.\n"));
			emRes = em_hdu_change_mode_error_regstate;
			break;
		}
		
	} while (FALSE);
	
	if (emRes == em_hdu_change_mode_success)
	{
		SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwUserInst, ptMsg->GetEvent(), (u8*)(&tInfo), sizeof(THduChanModeInfo));
	}
	else
	{
		u8 szRes[sizeof(THduChanModeInfo)+sizeof(EmTpHduChangeChanModeRes)] = {0};
		memcpy(szRes, &tInfo, sizeof(THduChanModeInfo));
		memcpy(szRes+sizeof(THduChanModeInfo), &emRes, sizeof(EmTpHduChangeChanModeRes));
		NotifyHduInfoToServer(ev_hdu_change_chan_mode_res, szRes, sizeof(szRes));
	}

	return;
}

void CHduEqp::EventChangeHduChanModeRes( CTpMsg* const ptMsg )
{
	THduChanModeInfo tInfo;
	EmTpHduChangeChanModeRes emRes;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	TP_SAFE_CAST(emRes, ptMsg->GetBody()+sizeof(tInfo));
		
	MdlLowHint(Ums_Mdl_Eqp, ("[CHduEqp::EventChangeHduChanModeRes] Layer:%d, Slot:%d, Chan:%d, ChanMode:%d, Res:%d.\n",
								tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_byChanMode, emRes));
	
	
	NotifyHduInfoToServer(ptMsg->GetEvent(), ptMsg->GetBody(), ptMsg->GetBodyLen());

	return;
}


void CHduEqp::EventMediaKeyNty(CTpMsg* const ptMsg)
{
	THduPlayInfo tHduInfo;
	TTPQTMediaKeyInfo tKeyInfo;
	TP_SAFE_CAST(tHduInfo, ptMsg->GetBody());
	TP_SAFE_CAST(tKeyInfo, ptMsg->GetBody()+sizeof(THduPlayInfo));
	
	MdlHint(Ums_Mdl_Eqp, ("EventMediaKeyNty Layer:%d, Slot:%d, ChanIndex:%d Subindx:%d, Handle:%d, Index:%d, Flag:%d, Keylen:%d.\n",
		tHduInfo.m_byLayer, tHduInfo.m_bySlot, tHduInfo.m_byChanIndex, tHduInfo.m_bySubChan,
		tKeyInfo.m_dwHandle, tKeyInfo.m_wIndex, tKeyInfo.m_dwQtFlag, tKeyInfo.m_dwKeyLen));
	
	u16 wIndex = GetIndex(tHduInfo.m_byLayer, tHduInfo.m_bySlot);
	if (0 > wIndex || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdModify] Invalid Index. Index:%d.\n", wIndex));
		return ;
	}
	
	if (!m_acHduModle[wIndex].m_bServiceReged)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::EventBrdModify] Service is not registed.\n"));
		return ;
	}
	
	
	//TODO
	u8 byBuf[sizeof(THduPlayInfo) + sizeof(TTPQTMediaKeyInfo)] = {0};
	memcpy( byBuf, &tHduInfo, sizeof(tHduInfo) );
	memcpy( byBuf + sizeof(tHduInfo), &tKeyInfo, sizeof(tKeyInfo) );
	SendMsgToEqpSsn(m_acHduModle[wIndex].m_dwUserInst, ev_hdu_media_key_nty, byBuf, sizeof(THduPlayInfo) + sizeof(TTPQTMediaKeyInfo));
}

BOOL32 CHduEqp::GetHduVer( const TTPBrdPos& tBrdInfo , u8& byHduVer)
{
	if (em_hdu2_brd != tBrdInfo.m_emBrdType && em_hdu2_qt_brd != tBrdInfo.m_emBrdType)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::GetHduVer] The brd type is not hdu2.\n"));
		return FALSE;
	}
	
	u16 wIndex = GetIndex(tBrdInfo.m_byBrdLayer, tBrdInfo.m_byBrdSlot);
	if (wIndex < 0 || wIndex >= HDU_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::GetHduVer] Invalid index:%d.\n", wIndex));
		return FALSE;
	}
	
	if (m_acHduModle[wIndex].m_tRegInfo.m_dwEqpIP != tBrdInfo.m_dwBrdIP)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::GetHduVer] IP no equal.\n"));
		return FALSE;
	}
	
	if (!m_acHduModle[wIndex].m_bRegsited)
	{
		MdlError(Ums_Mdl_Eqp, ("[CHduEqp::GetHduVer] this brd is not regsited.\n"));
		return FALSE;
	}
	
	// qt电视墙版本号 STARTMODE_HDU2
	if (m_acHduModle[wIndex].m_bQtVer)
	{
		byHduVer = STARTMODE_HDU2;
	}
	// 普通电视墙版本号 STARTMODE_HDU2_S
	else
	{
		byHduVer = STARTMODE_HDU2_S;
	}
	
	return TRUE;
}