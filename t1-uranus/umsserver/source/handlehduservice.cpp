#include "handlehduservice.h"
#include "umsobject.h"
#include "tphdu2.h"
#include "umsconfig.h"

#include "innereventumshdu.h"
#include "innereventumsserver.h"
#include "innereventtvwall.h"

// 外部消息
#include "eventoutumshdu2.h"
#include "eventoutsipadapter.h"

CUmsHduHandleService::CUmsHduHandleService(CTpObject* pcObjec)
										  : CTpHandler(pcObjec)
{
	LoadHduInfo();
}

CUmsHduHandleService::~CUmsHduHandleService()
{
	SaveHduBrdInfo();
	SaveHduPlanInfo();
}

void CUmsHduHandleService::LoadHduInfo()
{
	THduCfgInfo tInfo;
	for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; ++wIndex)
	{
		tInfo.Clear();
		if (umsGetHduCfg(wIndex, tInfo) && 0 != tInfo.m_dwIP)
		{
			m_acHdu[wIndex].Init(tInfo);
			UmsNotifyMsgToEqp(ev_hdu_cfg_info, &tInfo, sizeof(THduCfgInfo));
		}
	}

	THduStyleCfgInfo tHduStyle;
	if (umsGetHduStyle(tHduStyle))
	{
		THduPlayUnit atUnit[HDU_STYLE_MAX_NUM];
		CHduEx* pcHdu = NULL;
		CHduChannelEx* pcChannel = NULL;
		for (u16 wIndex = 0; wIndex < tHduStyle.m_byRow * tHduStyle.m_byCol; ++wIndex)
		{
			u16 wHduIndex = GetHduIndex(tHduStyle.m_atHduStyle[wIndex].m_byLayer, tHduStyle.m_atHduStyle[wIndex].m_bySlot);
			if (HDU_MAX_NUM == wHduIndex)
			{
				continue;
			}
			else
			{
				pcHdu = &(m_acHdu[wHduIndex]);
				pcChannel = m_acHdu[wHduIndex].GetChannel(tHduStyle.m_atHduStyle[wIndex].m_byChanIndex);

			}

			if (NULL != pcHdu && NULL != pcChannel)
			{
				atUnit[wIndex].m_pcHdu = pcHdu;
				atUnit[wIndex].m_pcChannel = pcChannel;
			}
			atUnit[wIndex].m_tName.SetAlias(m_acHdu[wHduIndex].GetHduName());
			
		}

		m_cHduPlanEx.Init(tHduStyle.m_byRow, tHduStyle.m_byCol, atUnit);
	}
}

BOOL32 CUmsHduHandleService::Handler(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	u8* pData  = ptMsg->GetBody();
	u16 wSize  = ptMsg->GetBodyLen();
 
	switch (wEvent)
	{
	case ev_SysCmsLoginInd:			
		{
			EventHduUserLogin(pData, wSize);
		}
		break;

	case ev_hdu_brd_reg_res:		
		{
			EventBrdRegRes(pData, wSize);
		}
		break;

	case ev_hdu_service_reg_res:	
		{
			EventServiceRegRes(pData, wSize);
		}
		break;

	case ev_hduBrdModify_req:		
		{
			EventHduBrdModify(pData, wSize);
		}
		break;
									
	case ev_hduBrdAdd_req:			
		{
			EventHduBrdAdd(pData, wSize);
		}
		break;
									
	case ev_hduUpdate_req:			
		{
			EventHduUpdate(pData, wSize);
		}
		break;
									
	case ev_hdu_update_nty:			
		{
			EventHduUpdateNty(pData, wSize);
		}
		break;

	case ev_hduReboot_req:			
		{
			EventHduReboot(pData, wSize);
		}
		break;

	case ev_hduChanModify_req:		
		{
			EventHduChanModify(pData, wSize);
		}
		break;

	case ev_hduChanDel_req:			
		{
			EventHduDelChan(pData, wSize);
		}
		break;

	case ev_hduDel_req:				
		{
			EventHduDel(pData, wSize);
		}
		break;

	case ev_hduStyle_Add:			
		{
			EventHduStyleAdd(pData, wSize);
		}
		break;
	case ev_hduStyle_Del_Req:
		{
			EventHduStyleDel(pData, wSize);
		}	
		break;
	case ev_hduStyle_update_Req:
		{
			EventHduStyleUpdate(pData, wSize);
		}
		break;
	case ev_HduPlay_Req:			
		{
			EventHduPlayReq(pData, wSize);
		}
		break;

	case ev_Hdu_SetVol:
		{
			EventSetVolInfo(pData, wSize);
		}
		break;

	case ev_HduStopPlay_Req:		
		{
			EventHduStopPlay(pData, wSize);
		}
		break;

	case ev_HduAllStopPlay_Req:		
		{
			HduStopAllReqStateFromUmcCns(pData, wSize);
		}
		break;

	case ev_hdu_stop_play_ack:		
		{
			EventHduStopAckFromEqp(pData, wSize);
		}
		break;

	case ev_hdu_stop_play_nack:		
		{
			EventHduStopNackFromEqp(pData, wSize);
		}
		break;

	case ev_AddTvMonitor_ack:		
		{
			EventHduPlayAckFromCall(pData, wSize);
		}
		break;

	case ev_hdu_play_ack:			
		{
			EventHduPlayAckFromEqp(pData, wSize);
		}
		break;

	case ev_hdu_play_nack:			
		{
			EventHduPlayNackFromEqp(pData, wSize);
		}
		break;

	case ev_DelTvMonitor_ack:		
		{
			EventHduDelMonitorFromCall(pData, wSize);
		}
		break;

	case ev_HungUpHdu_cmd:
		{
			EventHungUpHdu(pData, wSize);
		}
		break;

	case ev_HungUpConf_Hdu_cmd:
		{
			EventHungUpConfHdu(pData, wSize);
		}
		break;
		
	case ev_hdu_update_chan_status:
		{
			EventUpdateChanStatus(pData, wSize);
		}
		break;
		
	case ev_hdu_updata_status:
		{
			EventUpdateStatus(pData, wSize);
		}
		break;

	case ev_hdu_req_iframe:
		{
			EventReqIFrame(pData, wSize);
		}
		break;

	case ev_hdu_set_vol_res:
		{
			EventSetVolRes(pData, wSize);
		}
		break;

	case ev_Hdu_ChangeChanMode_Req:
		{// from ue to eqp
			EventChangeChanModeReq(pData, wSize);
		}
		break;

	case ev_hdu_change_chan_mode_res:
		{// from eqp to ue
			EventChangeChanModeRsp(pData, wSize);
		}
		break;
	case ev_HduPlanInfo_Req:
		{
			u16 wConfID = 0;
			u16 wEpID   = 0;
			TP_SAFE_CAST(wConfID, pData);
			TP_SAFE_CAST(wEpID, pData+sizeof(u16));
			SendToCnsHduPlanInfo(wConfID, wEpID);
		}
		break;
	/////////////////////////////////////////////////////////
	////  终端操作电视墙相关
	case evTPCNS_UMS_HduPlay_Req:
		{
			EventFromCnsHduPlayReq(pData, wSize);
		}
		break;
	case evTPCNS_UMS_HduStopPlay_Req:
		{
			EventFromCnsHduStopPlay(pData, wSize);
		}
		break;
	case evTPCNS_UMS_HduStopAllPlay_Req:
		{
			HduStopAllReqStateFromUmcCns(pData, wSize);
			//EventFromCnsHduAllStopPlay(pData, wSize);
		}
		break;
	case evTPCNS_UMS_HduSetVol_Req:
		{
			EventFromCnsSetVolInfo(pData, wSize);
		}
		break;
	case evTPCNS_UMS_HduChangeChanMode_Req:
		{
			EventFromCnsChangeChanModeReq(pData, wSize);
		}
		break;

	case ev_TvMonitor_MediaKey_Nty:
		{
            EventMediaKeyNty(pData, wSize);
		}
        break;

	default:						
		{
			MdlError(Ums_Mdl_Service, ("[CUmsHduHandleService::Handler] Unknow event ID:%d.\n", wEvent));
		}
		return FALSE;

	}

	return TRUE;
}

void CUmsHduHandleService::EventHduUserLogin(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pData);
	MdlHint(Ums_Mdl_Service, ("EventHduUserLogin User login. AppID:%d.\n", GETAPP(tUser.m_dwUserInst)));
	
	if (IsToolUser(tUser))
	{
		for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; ++wIndex)
		{
			if (m_acHdu[wIndex].ValidBrd())
			{
				THduCfg tCfgInfo;
				m_acHdu[wIndex].GetCfgInfo(tCfgInfo);
				
				TLogUser tUser;
				tUser.m_dwUserInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);
				TpNotifyMsgToUeFromService(ev_hduInfo_Nty, &tCfgInfo, sizeof(THduCfg), tUser);
			}
		}
		
		THduStyleData tData;
		tData.m_byRow = m_cHduPlanEx.RowNum();
		tData.m_byCol = m_cHduPlanEx.ColNum();

		THduPlayUnit* ptInfo = NULL;
		for (u16 wUnitIndex = 0; wUnitIndex < tData.m_byRow * tData.m_byCol; ++wUnitIndex)
		{
			ptInfo = m_cHduPlanEx.GetChannel(wUnitIndex);
			if (NULL != ptInfo)
			{
				tData.m_atUnits[wUnitIndex].m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
				tData.m_atUnits[wUnitIndex].m_byLayer = ptInfo->m_pcHdu->Layer();
				tData.m_atUnits[wUnitIndex].m_bySlot = ptInfo->m_pcHdu->Slot();
				tData.m_atUnits[wUnitIndex].m_tName.SetAlias(ptInfo->m_tName.m_abyAlias);
			}
		}

		TpNotifyMsgToUeFromService(ev_hduStyle_Nty, &tData, sizeof(THduStyleData), tUser);
	}
	else
	{
		SendHduPlanInfo(TRUE, FALSE);
	}
}

void CUmsHduHandleService::EventBrdRegRes(u8* pData, u16 wDataSize)
{
	THduRegStatus tInfo;
	TP_SAFE_CAST(tInfo, pData);
	
	MdlHint(Ums_Mdl_Service, ("EventBrdRegRes Layer:%d, Slot:%d, Reg:%d.\n", 
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_bRegRes));
	
	u16 wIndex = GetHduIndex(tInfo.m_byLayer, tInfo.m_bySlot);
	if (HDU_MAX_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Service, ("EventBrdRegRes Invalid position.\n"));
		return ;
	}
	
	if (tInfo.m_bRegRes != m_acHdu[wIndex].BrdRegState())
	{
		m_acHdu[wIndex].UpdateBrdState(tInfo.m_bRegRes);
		THduCfg tCfgInfo;
		m_acHdu[wIndex].GetCfgInfo(tCfgInfo);
		
		TLogUser tUser;
		tUser.m_dwUserInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);
		TpNotifyMsgToUeFromService(ev_hduInfo_Nty, &tCfgInfo, sizeof(THduCfg), tUser);
	}
}

void CUmsHduHandleService::EventServiceRegRes(u8* pData, u16 wDataSize)
{
	THduRegStatus tInfo;
	u16	wStartPort;
	TP_SAFE_CAST(tInfo, pData);
	TP_SAFE_CAST(wStartPort, pData+sizeof(THduRegStatus));
	
	MdlHint(Ums_Mdl_Service, ("EventServiceRegRes Layer:%d, Slot:%d, Reg:%d, StartPort:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_bRegRes, wStartPort));
	
	u32 dwIP = 0;
	u16 wIndex = GetHduIndex(tInfo.m_byLayer, tInfo.m_bySlot);
	if (HDU_MAX_NUM == wIndex)
	{
		MdlHint(Ums_Mdl_Service, ("EventServiceRegRes Invalid position.\n"));
	}
	else
	{
		if (tInfo.m_bRegRes != m_acHdu[wIndex].ServiceRegState())
		{
			m_acHdu[wIndex].UpdateServiceState(tInfo.m_bRegRes);
			m_acHdu[wIndex].SetStartPort(wStartPort);

			THduCfg tCfgInfo;
			m_acHdu[wIndex].GetCfgInfo(tCfgInfo);

			TLogUser tUser;
			tUser.m_dwUserInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);
			TpNotifyMsgToUeFromService(ev_hduInfo_Nty, &tCfgInfo, sizeof(THduCfg), tUser);
		}
	}

	THduPlayUnit* ptInfo = NULL;
	u8 bySubChan = 0;
	EmHduChanStatus emStatus;
	for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
	{
		ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, byIndex);
		if (NULL != ptInfo)
		{// 通道掉线了，需要stop
			if (ptInfo->m_pcChannel->IsVmpChan())
			{
				for (bySubChan = 0; bySubChan < HDU_MAX_VMP_SUBCHAN; bySubChan++)
				{
					emStatus = ptInfo->m_pcChannel->GetChanStatus(bySubChan);
					if (!tInfo.m_bRegRes && (em_hdu_chan_idle != emStatus))
					{
						StopHduToCall(ptInfo, bySubChan);
						ptInfo->m_pcChannel->ClearPlayInfo(bySubChan);
					}
				}
			}
			else
			{
				bySubChan = 0;
				emStatus = ptInfo->m_pcChannel->GetChanStatus(bySubChan);
				if (!tInfo.m_bRegRes && (em_hdu_chan_idle != emStatus))
				{
					StopHduToCall(ptInfo, bySubChan);
					ptInfo->m_pcChannel->ClearPlayInfo(bySubChan);
				}
			}
			ptInfo->m_pcChannel->SetVmpMode(0);  // 通道上线和下线，模式都变为一画面
		}
	}

	SendHduPlanInfo();

	return;
}

void CUmsHduHandleService::EventHduBrdModify(u8* pData, u16 wDataSize)
{
	TLogUser  tUser;
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tBrdPos, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduBrdModify Layer:%d, Slot:%d, m_emBrdType:%d IP:"TPIPFORMAT".\n",
							   tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, tBrdPos.m_emBrdType, Tpu32ToIP(tBrdPos.m_dwBrdIP)));
	
	EmModifyHduRet emRet = em_hdu_modify_success;
	u16 wIndex = GetHduIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);
	if (HDU_MAX_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Service, ("EventHduBrdModify Invalid position.\n"));
		emRet = em_hdu_brd_no_cfg;
	}
	else
	{
		tBrdPos.m_emBrdType = m_acHdu[wIndex].BrdType();
		m_acHdu[wIndex].SetBrdInfo(tBrdPos);

		SaveHduBrdInfo(wIndex);
		UmsNotifyMsgToEqp(ev_hdu_brd_modify, &tBrdPos, sizeof(TTPBrdPos));
	}
	
	u8 abBuf[sizeof(EmModifyHduRet) +sizeof(TTPBrdPos)] = {0};
	memcpy(abBuf, &emRet, sizeof(EmModifyHduRet));
	memcpy(abBuf+sizeof(EmModifyHduRet), &tBrdPos, sizeof(TTPBrdPos));
	TpNotifyMsgToUeFromService(ev_hduBrdModify_rsp, abBuf, sizeof(abBuf), tUser);
}

void CUmsHduHandleService::EventHduBrdAdd(u8* pData, u16 wDataSize)
{
	TLogUser  tUser;
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tBrdPos, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduBrdAdd Layer:%d, Slot:%d, m_emBrdType:%d, IP:"TPIPFORMAT".\n",
							   tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, tBrdPos.m_emBrdType, Tpu32ToIP(tBrdPos.m_dwBrdIP)));
	
	EmModifyHduRet emRet = em_hdu_modify_success;
	u16 wIndex = GetHduIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);
	if (HDU_MAX_NUM != wIndex)
	{
		MdlError(Ums_Mdl_Service, ("EventHduBrdAdd position already.\n"));
		emRet = em_hdu_brd_already_cfg;
	}

	if (tBrdPos.m_byBrdLayer >= HDU_MAX_LAYER || tBrdPos.m_byBrdSlot >= HDU_MAX_SLOT)
	{
		MdlError(Ums_Mdl_Service, ("EventHduBrdAdd Invalid layer or slot.\n"));
		emRet = em_hdu_invalid_index;
	}
	
	// 兼容旧版本电视墙
	if (tBrdPos.m_emBrdType != em_hdu2_qt_brd)
	{
		tBrdPos.m_emBrdType = em_hdu2_brd;
	}
	
	if (em_hdu_modify_success == emRet)
	{
		u16 wIndex = GetIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);

		m_acHdu[wIndex].SetBrdInfo(tBrdPos);

		SaveHduBrdInfo(wIndex);
		
		UmsNotifyMsgToEqp(ev_hdu_brd_modify, &tBrdPos, sizeof(TTPBrdPos));
	}
	

	u8 abBuf[sizeof(EmModifyHduRet) +sizeof(TTPBrdPos)] = {0};
	memcpy(abBuf, &emRet, sizeof(EmModifyHduRet));
	memcpy(abBuf+sizeof(EmModifyHduRet), &tBrdPos, sizeof(TTPBrdPos));
	TpNotifyMsgToUeFromService(ev_hduBrdAdd_rsp, abBuf, sizeof(abBuf), tUser);
}

void CUmsHduHandleService::EventHduUpdate(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	TTPBrdUpGrade tInfo;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tInfo, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduUpdate Layer:%d, Slot:%d, FileName:%s.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_szFileName));
	
	EmUpdateHduRet emRet = em_hdu_update_success;
	u16 wIndex = GetHduIndex(tInfo.m_byLayer, tInfo.m_bySlot);
	do 
	{
		if (HDU_MAX_NUM == wIndex)
		{
			MdlError(Ums_Mdl_Service, ("EventHduUpdate Invalid position.\n"));
			emRet = em_hdu_update_unknow;
			break;
		}
		
		if (!m_acHdu[wIndex].ServiceRegState())
		{
			MdlError(Ums_Mdl_Service, ("EventHduUpdate Service is not registed.\n"));
			emRet = em_hdu_update_unreg;
			break;
		}
		
	} while (FALSE);
	
	if (em_hdu_update_success == emRet)
	{
		UmsNotifyMsgToEqp(ev_hdu_update_req, &tInfo, sizeof(TTPBrdUpGrade));
	}
	else
	{
		u8 abBuf[sizeof(TTPBrdUpGrade)+sizeof(EmUpdateHduRet)] = {0};
		memcpy(abBuf, &tInfo, sizeof(TTPBrdUpGrade));
		memcpy(abBuf+sizeof(TTPBrdUpGrade), &emRet, sizeof(EmUpdateHduRet));
		TpNotifyMsgToToolUserFromService(ev_hduUpdate_rsp, abBuf, sizeof(abBuf));
	}
}

void CUmsHduHandleService::EventHduUpdateNty(u8* pData, u16 wDataSize)
{
	TTPBrdUpGrade tInfo;
	EmUpdateHduRet emRet;
	TP_SAFE_CAST(tInfo, pData);
	TP_SAFE_CAST(emRet, pData+sizeof(TTPBrdUpGrade));
	
	MdlHint(Ums_Mdl_Service, ("EventHduUpdateNty Layer:%d, Slot:%d, FileName:%s, Res:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_szFileName, emRet));
	
	TpNotifyMsgToToolUserFromService(ev_hduUpdate_rsp, pData, wDataSize);
}

void CUmsHduHandleService::EventHduReboot(u8* pData, u16 wDataSize)
{
	TLogUser  tUser;
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tBrdPos, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduReboot Layer:%d, Slot:%d, brdtype:%d, IP:"TPIPFORMAT".\n",
							   tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, tBrdPos.m_emBrdType, Tpu32ToIP(tBrdPos.m_dwBrdIP)));
	
	EmModifyHduRet emRet = em_hdu_modify_success;
	u16 wIndex = HDU_MAX_NUM;
	do 
	{
		wIndex = GetHduIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);
		if (HDU_MAX_NUM == wIndex)
		{
			MdlError(Ums_Mdl_Service, ("EventHduReboot Invalid position.\n"));
			emRet = em_hdu_invalid_index;
			break;
		}

		if (!m_acHdu[wIndex].ServiceRegState())
		{
			MdlError(Ums_Mdl_Service, ("Board is not reged.\n"));
			emRet = em_hdu_invalid_index;
			break;
		}

	} while (FALSE);

	if (em_hdu_modify_success == emRet)
	{
		UmsNotifyMsgToEqp(ev_hdu_reboot, &tBrdPos, sizeof(TTPBrdPos));

		THduRegStatus tInfo;
		tInfo.m_byLayer = tBrdPos.m_byBrdLayer;
		tInfo.m_bySlot = tBrdPos.m_byBrdSlot;
		tInfo.m_bRegRes = FALSE;
		u16	wStartPort = 0;

		u8 abInfo[sizeof(THduRegStatus)+sizeof(u16)] = {0};
		memcpy(abInfo, &tInfo, sizeof(THduRegStatus));
		memcpy(abInfo+sizeof(THduRegStatus), &wStartPort, sizeof(u16));

		EventServiceRegRes(abInfo, sizeof(abInfo));
	}
	
	u8 abBuf[sizeof(EmModifyHduRet) +sizeof(TTPBrdPos)] = {0};
	memcpy(abBuf, &emRet, sizeof(EmModifyHduRet));
	memcpy(abBuf+sizeof(EmModifyHduRet), &tBrdPos, sizeof(TTPBrdPos));
	TpNotifyMsgToUeFromService(ev_hduReboot_rsp, abBuf, sizeof(abBuf), tUser);
}

void CUmsHduHandleService::EventHduChanModify(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	THduInfo tInfo;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tInfo, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduChanModify Layer:%d, Slot:%d, brdType:%d.\n", 
								tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_emBrdType));
	
	EmModifyHduRet emRet = em_hdu_modify_success;
	u16 wIndex = HDU_MAX_NUM;
	do 
	{
		wIndex = GetHduIndex(tInfo.m_byLayer, tInfo.m_bySlot);
		if (HDU_MAX_NUM == wIndex)
		{
			emRet = em_hdu_invalid_index;
			MdlError(Ums_Mdl_Service, ("EventHduChanModify Invalid position.\n"));
			break;
		}
		
	} while (FALSE);
	
	if (em_hdu_modify_success == emRet)
	{
		m_acHdu[wIndex].SetServiceInfo(tInfo.m_atChanInfo, tInfo.m_tName);

		SaveHduBrdInfo(wIndex);
		UmsNotifyMsgToEqp(ev_hdu_chan_modify, &tInfo, sizeof(THduInfo));

		SendHduPlanInfo();
	}
	
	u8 abBuf[sizeof(EmModifyHduRet) +sizeof(THduInfo)] = {0};
	memcpy(abBuf, &emRet, sizeof(EmModifyHduRet));
	memcpy(abBuf+sizeof(EmModifyHduRet), &tInfo, sizeof(THduInfo));
	TpNotifyMsgToUeFromService(ev_hduChanModify_rsp, abBuf, sizeof(EmModifyHduRet) +sizeof(THduInfo), tUser);
}

void CUmsHduHandleService::EventHduDelChan(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tBrdPos, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduDelChan Layer:%d, Slot:%d, brdtype:%d.\n",
						tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, tBrdPos.m_emBrdType));
	
	EmModifyHduRet emRet = em_hdu_modify_success;
	u16 wIndex = HDU_MAX_NUM;
	do 
	{
		wIndex = GetHduIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);
		if (HDU_MAX_NUM == wIndex)
		{
			MdlError(Ums_Mdl_Service, ("EventHduDelChan Invalid position.\n"));
			emRet = em_hdu_invalid_index;
			break;
		}

	} while (FALSE);
	
	if (em_hdu_modify_success == emRet)
	{
		m_acHdu[wIndex].ClearServiceInfo();
		SaveHduBrdInfo(wIndex);
		
		THduInfo tInfo;
		tInfo.m_byLayer = tBrdPos.m_byBrdLayer;
		tInfo.m_bySlot = tBrdPos.m_byBrdSlot;
		
		UmsNotifyMsgToEqp(ev_hdu_chan_modify, &tInfo, sizeof(THduInfo));
	}
	
	u8 abBuf[sizeof(EmModifyHduRet)+sizeof(TTPBrdPos)] = {0};
	memcpy(abBuf, &emRet, sizeof(EmModifyHduRet));
	memcpy(abBuf+sizeof(EmModifyHduRet), &tBrdPos, sizeof(TTPBrdPos));
	TpNotifyMsgToUeFromService(ev_hduChanDel_rsp, abBuf, sizeof(abBuf), tUser);
}

void CUmsHduHandleService::EventHduDel(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tBrdPos, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduDel Info: Layer:%d, Slot:%d, brdtype:%d.\n", tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, tBrdPos.m_emBrdType));
	
	EmModifyHduRet emRet = em_hdu_modify_success;
	u16 wIndex = GetHduIndex(tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot);
	if (HDU_MAX_NUM == wIndex)
	{
		emRet = em_hdu_invalid_index;
		MdlError(Ums_Mdl_Service, ("EventHduDel Invalid position.\n"));
	}
	
	
	if (em_hdu_modify_success == emRet)
	{
		u8 abBuf[sizeof(u8)*2] = {0};
		memcpy(abBuf, &(tBrdPos.m_byBrdLayer), sizeof(u8));
		memcpy(abBuf+sizeof(u8), &(tBrdPos.m_byBrdSlot), sizeof(u8));
		UmsNotifyMsgToEqp(ev_hdu_del, abBuf, sizeof(abBuf));
		
		m_acHdu[wIndex].ClearBrdInfo();

		THduCfgInfo tCfg;
		umsSetHduCfg(wIndex, tCfg);
	}

	u8 abRspBuf[sizeof(EmModifyHduRet) + sizeof(TTPBrdPos)] = {0};
	memcpy(abRspBuf, &emRet, sizeof(EmModifyHduRet));
	memcpy(abRspBuf+sizeof(EmModifyHduRet), &tBrdPos, sizeof(TTPBrdPos));
		
	TpNotifyMsgToUeFromService(ev_hduDel_rsp, abRspBuf, sizeof(abRspBuf), tUser);
}

void CUmsHduHandleService::EventHduStyleAdd(u8* pData, u16 wDataSize)
 {
	TLogUser tUser;
	THduStyleData tData;
	
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tData, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduStyleAdd Add Hdu Style: Row:%d, Column:%d.\n",
							   tData.m_byRow, tData.m_byCol));

	u16 wTotal = m_cHduPlanEx.TotalChannel();
	u16 wIndex = 0;
	u8 byChanID = 0;
	THduPlayUnit* ptInfo = NULL;
	for (wIndex = 0; wIndex < wTotal; ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			if (ptInfo->m_pcChannel->IsVmpChan())
			{
				for (byChanID = 0; byChanID < HDU_MAX_VMP_SUBCHAN; byChanID++)
				{
					StopHduPlay(ptInfo, byChanID);
				}
			}
			else
			{
				byChanID = 0;
				StopHduPlay(ptInfo, byChanID);
			}
		}
	}

	m_cHduPlanEx.Clear();
	THduPlayUnit atInfo[HDU_STYLE_MAX_NUM];
	CHduEx* pcHdu = NULL;
	CHduChannelEx* pcChannel = NULL;
	for (wIndex = 0; wIndex < tData.m_byRow * tData.m_byCol; ++wIndex)
	{
		u16 wHduIndex = GetHduIndex(tData.m_atUnits[wIndex].m_byLayer, tData.m_atUnits[wIndex].m_bySlot);
		if (HDU_MAX_NUM == wHduIndex)
		{
			continue;
		}
		else
		{
			pcHdu = &(m_acHdu[wHduIndex]);
			pcChannel = m_acHdu[wHduIndex].GetChannel(tData.m_atUnits[wIndex].m_byChanIndex);
		}
		
		if (NULL != pcHdu && NULL != pcChannel)
		{
			atInfo[wIndex].m_pcChannel = pcChannel;
			atInfo[wIndex].m_pcHdu = pcHdu;
			atInfo[wIndex].m_tName.SetAlias(tData.m_atUnits[wIndex].m_tName.m_abyAlias);
		}
	}

	m_cHduPlanEx.Init(tData.m_byRow, tData.m_byCol, atInfo);

	SendHduPlanInfo();
	SaveHduPlanInfo();

	EmModifyHduRet emRet = em_hdu_modify_success;
	u8 abBuf[sizeof(EmModifyHduRet)+sizeof(THduStyleData)] = {0};
	memcpy(abBuf, &emRet, sizeof(EmModifyHduRet));
	memcpy(abBuf+sizeof(EmModifyHduRet), &tData, sizeof(THduStyleData));

	TpNotifyMsgToUeFromService(ev_hduStyle_Add_Rsp, abBuf, sizeof(abBuf), tUser);
}

void CUmsHduHandleService::EventHduStyleDel(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pData);
	
	MdlHint(Ums_Mdl_Service, ("EventHduStyleDel Del Hdu Style.\n"));

	THduPlayUnit* ptInfo = NULL;
	u8 byChanID = 0;
	u16 wTotal = m_cHduPlanEx.TotalChannel();
	for (u16 wIndex = 0; wIndex < wTotal; ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			if (ptInfo->m_pcChannel->IsVmpChan())
			{
				for (byChanID = 0; byChanID < HDU_MAX_VMP_SUBCHAN; byChanID++)
				{
					StopHduPlay(ptInfo, byChanID);
				}
			}
			else
			{
				byChanID = 0;
				StopHduPlay(ptInfo, byChanID);
			}
		}
	}
	
	m_cHduPlanEx.Clear();
	SendHduPlanInfo();

	EmModifyHduRet emRet = em_hdu_modify_success;
	TpNotifyMsgToUeFromService(ev_hduStyle_Del_Rsp, &emRet, sizeof(EmModifyHduRet), tUser);
}


void CUmsHduHandleService::EventHduStyleUpdate(u8* pData, u16 wDataSize)
{
	TLogUser tUser;	
	TP_SAFE_CAST(tUser, pData);

	THduStyleData tUpdate;
	TP_SAFE_CAST(tUpdate, pData + sizeof(TLogUser));
	MdlHint(Ums_Mdl_Service, ("EventHduStyleUpdate Hdu Style: Row:%d, Col:%d.\n",
							   tUpdate.m_byRow, tUpdate.m_byCol));

	u16 wNum = tUpdate.m_byRow * tUpdate.m_byCol;

	EmModifyHduRet emRetReason = em_hdu_modify_fail;
	u8 abBuf[sizeof(EmModifyHduRet)+sizeof(THduStyleData)] = {0};

	if (wNum != m_cHduPlanEx.TotalChannel())
	{
		MdlError(Ums_Mdl_Service, ("EventHduStyleUpdate Channel-num is changed.\n"));
		emRetReason = em_hdu_invalid_index;
	}
	else
	{
		u16 wTotal = m_cHduPlanEx.TotalChannel();
		THduPlayUnit* ptInfo = NULL;
		
		for (u16 wIndex = 0; wIndex < wTotal; wIndex++)
		{
			ptInfo = m_cHduPlanEx.GetChannel(wIndex);
			if (NULL == ptInfo)
			{
				continue;
			}
			
			if (ptInfo->m_pcHdu->Layer() != tUpdate.m_atUnits[wIndex].m_byLayer 
				|| ptInfo->m_pcHdu->Slot() != tUpdate.m_atUnits[wIndex].m_bySlot
				|| ptInfo->m_pcChannel->GetChanID() != tUpdate.m_atUnits[wIndex].m_byChanIndex)
			{
				continue;
			}
			if (NULL == tUpdate.m_atUnits[wIndex].m_tName.m_abyAlias)
			{
				continue;
			}
			if (0 == strcmp(m_cHduPlanEx.GetHduName(wIndex) , tUpdate.m_atUnits[wIndex].m_tName.m_abyAlias))
			{
				continue;
			}
			
			emRetReason = em_hdu_modify_success;
			ptInfo->m_tName.SetAlias(tUpdate.m_atUnits[wIndex].m_tName.m_abyAlias);
			m_cHduPlanEx.SetHduName(wIndex,tUpdate.m_atUnits[wIndex].m_tName.m_abyAlias);
		}
	}

	if (em_hdu_modify_success == emRetReason)
	{
		SendHduPlanInfo();
		SaveHduPlanInfo();
	}
	
	memcpy(abBuf, &emRetReason, sizeof(EmModifyHduRet));
	memcpy(abBuf+sizeof(EmModifyHduRet), &tUpdate, sizeof(THduStyleData));	
	TpNotifyMsgToUeFromService(ev_hduStyle_update_Rsp, abBuf, sizeof(abBuf), tUser);

	return;
}

void CUmsHduHandleService::EventSetVolRes(u8* pData, u16 wDataSize)
{// 设置音量结果返回后，根据ev_hdu_update_chan_status消息更新音量信息
	THduVolInfo tInfo;
	EmTpHduSetVolRes emRes;
	TP_SAFE_CAST(tInfo, pData);
	TP_SAFE_CAST(emRes, pData+sizeof(THduVolInfo));
	
	MdlHint(Ums_Mdl_Service, ("EventSetVolRes Layer:%d, Slot:%d, Chan:%d, Res:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanlIdx, emRes));

	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanlIdx);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventSetVolRes Invalid position.\n"));
		return ;
	}

	TLogUser tUser;
	THduSetVolInfo tVolInfo;
	tVolInfo.m_tInfo.m_wIndex = ptInfo->m_wIndex;
	tVolInfo.m_byVol = tInfo.m_byVolume;
	tVolInfo.m_bMute = tInfo.m_byIsMute;
	

	u8 szRes[sizeof(THduSetVolInfo)+sizeof(EmTpHduSetVolRes)] = {0};
	memcpy(szRes, &tVolInfo, sizeof(THduSetVolInfo));
	memcpy(szRes+sizeof(THduSetVolInfo), &emRes, sizeof(EmTpHduSetVolRes));
	TpNotifyMsgToUeFromService(ev_Hdu_SetVol_Res, szRes, sizeof(szRes), tUser);
	
	TUmsHandle tHandle;
	u8 abBuf[sizeof(tHandle)+sizeof(tVolInfo)+sizeof(emRes)] = {0};
	memcpy(abBuf, &(tHandle), sizeof(tHandle));
	memcpy(abBuf+sizeof(tHandle), &tVolInfo, sizeof(tVolInfo));
	memcpy(abBuf+sizeof(tHandle)+sizeof(tVolInfo), &emRes, sizeof(emRes));
	
	NotifyCall(evTPUMS_CNS_HduSetVol_Ind, abBuf, sizeof(abBuf));

	return;
}

void CUmsHduHandleService::EventSetVolInfo(u8* pData, u16 wDataSize)
{
	TLogUser tUser;	
	THduSetVolInfo tInfo;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tInfo, pData+sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("EventSetVolInfo Index:%d, Vol:%d, Mute:%d.\n",
							   tInfo.m_tInfo.m_wIndex, tInfo.m_byVol, tInfo.m_bMute));

	EmTpHduSetVolRes emRes = em_hdu_SetVol_Success;
	THduPlayUnit* ptInfo = m_cHduPlanEx.GetChannel(tInfo.m_tInfo.m_wIndex);
	
	// 修改电视墙音量状态校验
	HduSetVolReqStateFromUmcCns(ptInfo, emRes);

	if (em_hdu_SetVol_Success != emRes)
	{
		u8 szRes[sizeof(THduSetVolInfo)+sizeof(EmTpHduSetVolRes)] = {0};
		memcpy(szRes, &tInfo, sizeof(THduSetVolInfo));
		memcpy(szRes+sizeof(THduSetVolInfo), &emRes, sizeof(EmTpHduSetVolRes));
		TpNotifyMsgToUeFromService(ev_Hdu_SetVol_Res, szRes, sizeof(szRes), tUser);
	}
	else
	{
		THduVolInfo tVolInfo;
		tVolInfo.m_byLayer = ptInfo->m_pcHdu->Layer();
		tVolInfo.m_byChanlIdx = ptInfo->m_pcChannel->GetChanID();
		tVolInfo.m_byIsMute = tInfo.m_bMute;
		tVolInfo.m_bySlot = ptInfo->m_pcHdu->Slot();
		tVolInfo.m_byVolume = tInfo.m_byVol;
		UmsNotifyMsgToEqp(ev_hdu_set_vol, &tVolInfo, sizeof(tVolInfo));
	}
}

void CUmsHduHandleService::EventHduPlayReq(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	TTPHduPlayReq tReq;
	
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tReq, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduPlayReq Type:%d, ConfID:%d, DstID:%d, Screen;%d, Name:%s, Index:%d, SunIndex:%d.\n",
							   tReq.m_emType, tReq.m_wConfID, tReq.m_wDstID, tReq.m_wScreenNum, tReq.m_achAlias, tReq.m_wIndex, tReq.m_bySubIndex));
	
	EmTpHduPlayNackReason emReason = em_hdu_play_success;
	
	// 请求消息状态判断
	HduPlayReqStateFromUmcCns(tReq, emReason);

	if (em_hdu_play_success == emReason )
	{
		u8 abData[sizeof(u16)+sizeof(u8)] = {0};
		memcpy(abData, &tReq.m_wIndex, sizeof(u16));
		memcpy(abData+sizeof(u16), &tReq.m_bySubIndex, sizeof(u8));
		TpNotifyMsgToUeFromService(ev_HduPlay_Ack, abData, sizeof(abData), tUser);
	}
	else
	{
		u8 abBuf[sizeof(u16)+sizeof(EmTpHduPlayNackReason)+sizeof(u8)] = {0};
		memcpy(abBuf, &(tReq.m_wIndex), sizeof(u16));
		memcpy(abBuf+sizeof(u16), &emReason, sizeof(EmTpHduPlayNackReason));
		memcpy(abBuf+sizeof(u16)+sizeof(EmTpHduPlayNackReason), &tReq.m_bySubIndex, sizeof(u8));
		TpNotifyMsgToUeFromService(ev_HduPlay_NAck, abBuf, sizeof(abBuf), tUser);
	}

	return;
}

void CUmsHduHandleService::EventHduStopPlay(u8* pData, u16 wDataSize)
{
	TLogUser tUser;
	TTPHduPlayReq tReq;
	
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tReq, pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHduStopPlay Type:%d, ConfID:%d, DstID:%d, ScreenNum:%d, Index%d, SubIndex:%d.\n",
							   tReq.m_emType, tReq.m_wConfID, tReq.m_wDstID, tReq.m_wScreenNum, tReq.m_wIndex, tReq.m_bySubIndex));
	
	BOOL32 bRes = TRUE;

	// 停止播放电视墙某个通道状态判断
	HduStopReqStateFromUmcCns(tReq, bRes);	

	TPHduBaseInfo tBaseInfo;
	tBaseInfo.m_wIndex = tReq.m_wIndex;
	tBaseInfo.m_bySubIndex = tReq.m_bySubIndex;
	if (bRes)
	{
		TpNotifyMsgToUeFromService(ev_HduStopPlay_Ack, &tBaseInfo, sizeof(tBaseInfo), tUser);
	}
	else
	{
		TpNotifyMsgToUeFromService(ev_HduStopPlay_NAck, &tBaseInfo, sizeof(tBaseInfo), tUser);
	}

	return;
}

void CUmsHduHandleService::EventHduAllStopPlay(u8* pData, u16 wDataSize)
{
	MdlHint(Ums_Mdl_Service, ("EventHduAllStopPlay Stop all hdu.\n"));
	
	u16 wTotal = m_cHduPlanEx.TotalChannel();
	THduPlayUnit* ptInfo = NULL;
	u8 bySubIndex = 0;
	for (u16 wIndex = 0; wIndex < wTotal; ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			if (ptInfo->m_pcChannel->IsVmpChan())
			{
				for (bySubIndex = 0; bySubIndex < HDU_MAX_VMP_SUBCHAN; ++bySubIndex)
				{
					if (em_hdu_chan_idle != ptInfo->m_pcChannel->GetChanStatus(bySubIndex))
					{
						StopHduPlay(ptInfo, bySubIndex);
						ptInfo->m_pcChannel->ClearPlayInfo(bySubIndex);
					}
				}
			}
			else
			{
				bySubIndex = 0;
				if (em_hdu_chan_idle != ptInfo->m_pcChannel->GetChanStatus(bySubIndex))
				{
					StopHduPlay(ptInfo, bySubIndex);
					ptInfo->m_pcChannel->ClearPlayInfo(bySubIndex);
				}
			}
		}
	}

	SendHduPlanInfo();
}

void CUmsHduHandleService::EventHduStopAckFromEqp(u8* pData, u16 wDataSize)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, pData);
	
	MdlHint(Ums_Mdl_Service, ("EventHduStopAckFromEqp Layer:%d, Slot:%d, ChanIndex:%d, SubChannel:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_bySubChan));
	
	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventHduStopAckFromEqp Invalid position.\n"));
		return ;
	}
	
// 	if (em_hdu_chan_idle == ptInfo->m_pcChannel->GetChanStatus(tInfo.m_bySubChan)&& 
// 		ptInfo->m_pcChannel->ValidPlayInfo(tInfo.m_bySubChan))
// 	{// 如果是会场掉线引起的电视墙停止播放，播放信息没有清，通知call待会场上线后重新上墙
// 		InitHduToCall(ptInfo, tInfo.m_byChanIndex);
// 	}

//	SendHduPlanInfo();

	return;
}

void CUmsHduHandleService::EventHduStopNackFromEqp(u8* pData, u16 wDataSize)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, pData);
	
	MdlError(Ums_Mdl_Service, ("EventHduStopNackFromEqp Layer:%d, Slot:%d, ChanIndex:%d, SubChannel:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_bySubChan));
	
	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventHduStopNackFromEqp Invalid position.\n"));
		return ;
	}

	return;
}

void CUmsHduHandleService::EventHduPlayAckFromCall(u8* pData, u16 wDataSize)
{
	TAddTvMonitorAck tAck;
	BOOL32 bChangeMode = FALSE;
	TP_SAFE_CAST(tAck, pData);
	TP_SAFE_CAST(bChangeMode, pData + sizeof(TAddTvMonitorAck));

	MdlHint(Ums_Mdl_Service, ("EventHduPlayAckFromCall Type:%d, ConfID:%d, DstID:%d, Index:%d, SubIndex:%d,ScreenNum:%d, Accept:%d.\n",
							   tAck.m_tReq.m_emType, tAck.m_tReq.m_wConfID, tAck.m_tReq.m_wDstID, tAck.m_tReq.m_wIndex,
							   tAck.m_tReq.m_bySubIndex, tAck.m_tReq.m_wScreenNum, tAck.m_bAccept));
	
	u16 wIndex = tAck.m_tReq.m_wIndex;
	
	THduPlayUnit* ptInfo = m_cHduPlanEx.GetChannel(tAck.m_tReq.m_wIndex);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventHduPlayAckFromCall Invalid channel info.\n"));
		return ;
	}

	if (em_hdu_chan_to_call != ptInfo->m_pcChannel->GetChanStatus(tAck.m_tReq.m_bySubIndex))
	{
		MdlError(Ums_Mdl_Service, ("EventHduPlayAckFromCall Channel status invalid. Status:%d.\n", 
									ptInfo->m_pcChannel->GetChanStatus(tAck.m_tReq.m_bySubIndex)))
		return ;
	}
	
	if (tAck.m_bAccept)
	{	
		if (ptInfo->m_pcHdu->ServiceRegState())
		{
			u8 abBuf[sizeof(THduPlayInfo)+sizeof(TAddTvMonitorAck)] = {0};
			THduPlayInfo tInfo;
			tInfo.m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
			tInfo.m_byLayer = ptInfo->m_pcHdu->Layer();
			tInfo.m_bySlot = ptInfo->m_pcHdu->Slot();
			tInfo.m_bySubChan = tAck.m_tReq.m_bySubIndex;
			tInfo.m_bVmp = ptInfo->m_pcChannel->IsVmpChan();
			
			memcpy(abBuf, &tInfo, sizeof(THduPlayInfo));
			memcpy(abBuf+sizeof(THduPlayInfo), &tAck, sizeof(TAddTvMonitorAck));
			UmsNotifyMsgToEqp(ev_hdu_play_req, abBuf, sizeof(abBuf));
			
			ptInfo->m_pcChannel->SetChanStatus(tAck.m_tReq.m_bySubIndex, em_hdu_chan_to_hdu);
			
		}
	}
	else
	{ // 清除播放信息
		ptInfo->m_pcChannel->ClearPlayInfo(tAck.m_tReq.m_bySubIndex);

		if (bChangeMode)
		{
			THduChanModeInfo tChanInfo;
			tChanInfo.m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
			tChanInfo.m_byLayer = ptInfo->m_pcHdu->Layer();
			tChanInfo.m_bySlot = ptInfo->m_pcHdu->Slot();
			tChanInfo.m_byChanMode = ptInfo->m_pcChannel->IsVmpChan();
			
			UmsNotifyMsgToEqp(ev_hdu_change_chan_mode, &tChanInfo, sizeof(tChanInfo));
		}
		else
		{
			SendHduPlanInfo();
		}
	
	}


}

void CUmsHduHandleService::EventHduPlayAckFromEqp(u8* pData, u16 wDataSize)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, pData);
	
	MdlHint(Ums_Mdl_Service, ("EventHduPlayAckFromEqp Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_bySubChan));

	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex);	
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventHduPlayAckFromEqp Invalid index.\n"));
		return ;
	}
	
	if (em_hdu_chan_to_hdu != ptInfo->m_pcChannel->GetChanStatus(tInfo.m_bySubChan))
	{
		MdlError(Ums_Mdl_Service, ("EventHduPlayAckFromEqp Invalid status. Status:%d.\n",
									ptInfo->m_pcChannel->GetChanStatus(tInfo.m_bySubChan)));
		return ;
	}
	
	ptInfo->m_pcChannel->SetChanStatus(tInfo.m_bySubChan, em_hdu_chan_working);

	SendHduPlanInfo();
}

void CUmsHduHandleService::EventHduPlayNackFromEqp(u8* pData, u16 wDataSize)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, pData);
	
	MdlHint(Ums_Mdl_Service, ("EventHduPlayNackFromEqp Layer:%d, Slot:%d, ChanIndex:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex));

	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventHduPlayAckFromEqp Invalid channel.\n"));
		return ;
	}
	
	if (em_hdu_chan_to_hdu != ptInfo->m_pcChannel->GetChanStatus(tInfo.m_bySubChan))
	{
		MdlError(Ums_Mdl_Service, ("EventHduPlayAckFromEqp Invalid status. Status:%d.\n",
									ptInfo->m_pcChannel->GetChanStatus(tInfo.m_bySubChan)));
		return ;
	}
	
	StopHduToCall(ptInfo, tInfo.m_bySubChan);

	SendHduPlanInfo();

	return;
}

void CUmsHduHandleService::EventHduDelMonitorFromCall(u8* pData, u16 wDataSize)
{
	TTPHduPlayReq tReq;
	TP_SAFE_CAST(tReq, pData);
	
	MdlHint(Ums_Mdl_Service, ("EventHduDelMonitorFromCall Index:%d, ScreenNum:%d.\n",
							   tReq.m_wIndex, tReq.m_wScreenNum));
}

void CUmsHduHandleService::EventHungUpConfHdu(u8* pData, u16 wDataSize)
{
	u16 wConfID = 0;
	TP_SAFE_CAST(wConfID, pData);

	MdlHint(Ums_Mdl_Service, ("EventHungUpConfHdu ConfID:%d.\n", wConfID));

	u16 wTotalChannel = m_cHduPlanEx.TotalChannel();
	TPlayInfo tPlayInfo;
	THduPlayUnit* ptInfo = NULL;
	u8 bySubChan = 0;
	for (u16 wIndex = 0; wIndex < wTotalChannel; ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			if (ptInfo->m_pcChannel->IsVmpChan())
			{
				for (bySubChan = 0; bySubChan < HDU_MAX_VMP_SUBCHAN; ++bySubChan)
				{
					tPlayInfo = ptInfo->m_pcChannel->GetPlayInfo(bySubChan);
					if (wConfID == tPlayInfo.m_wConfID)
					{
						StopHduPlay(ptInfo, bySubChan);
					}
				}
			}
			else
			{
				bySubChan = 0;
				tPlayInfo = ptInfo->m_pcChannel->GetPlayInfo(bySubChan);
				if (wConfID == tPlayInfo.m_wConfID)
				{
					StopHduPlay(ptInfo, bySubChan);
				}
			}
		}
	}

	SendHduPlanInfo();
}

void CUmsHduHandleService::EventHungUpHdu(u8* pData, u16 wDataSize)
{
	u16 wIndex = 0;
	u8 bySubChan = 0;
	EmCnsCallReason emRes;
	TP_SAFE_CAST(wIndex, pData);
	TP_SAFE_CAST(bySubChan, pData+sizeof(u16));
	TP_SAFE_CAST(emRes, pData+sizeof(u16)+sizeof(u8));
	
	MdlHint(Ums_Mdl_Service, ("EventHungUpHdu Index:%d, Chan:%d, Res:%d.\n", wIndex, bySubChan, emRes));

	THduPlayUnit* ptInfo = m_cHduPlanEx.GetChannel(wIndex);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventHungUpHdu Invalid channel.\n"));
		return ;
	}

	EmHduChanStatus emStatus = ptInfo->m_pcChannel->GetChanStatus(bySubChan);
	if (em_hdu_chan_working == emStatus || em_hdu_chan_to_hdu == emStatus)
	{
		THduPlayInfo tHduInfo;
		tHduInfo.m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
		tHduInfo.m_byLayer = ptInfo->m_pcHdu->Layer();
		tHduInfo.m_bySlot = ptInfo->m_pcHdu->Slot();
		tHduInfo.m_bySubChan = bySubChan;
		tHduInfo.m_bVmp = ptInfo->m_pcChannel->IsVmpChan();
		UmsNotifyMsgToEqp(ev_hdu_stop_play_req, &tHduInfo, sizeof(THduPlayInfo));
	}

	if (emRes == EmCnsCallReason_hungup || emRes == EmCnsCallReason_peerhungup)
	{
		ptInfo->m_pcChannel->ClearPlayInfo(bySubChan);
	}
	else
	{// 非主动挂断，等待会场上线，再次进入，状态置为em_hdu_chan_to_call
		ptInfo->m_pcChannel->SetChanStatus(bySubChan, em_hdu_chan_to_call);
	}

	SendHduPlanInfo();
}

void CUmsHduHandleService::EventUpdateChanStatus(u8* pData, u16 wDataSize)
{
	THduChanStatus tStatus;
	TP_SAFE_CAST(tStatus, pData);
	
	MdlHint(Ums_Mdl_Service, ("EventUpdateChanStatus Layer:%d, Slot:%d, ChanIndex:%d, subChan:%d, status:%d, byVol:%d, bMute:%d.\n",
							   tStatus.m_byLayer, tStatus.m_bySlot, 
							   tStatus.m_byChanIndex, tStatus.m_bySubChan, tStatus.m_byStatus, tStatus.m_tChanVol.m_byVol, tStatus.m_tChanVol.m_bMute));

	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tStatus.m_byLayer, tStatus.m_bySlot, tStatus.m_byChanIndex);
	if (NULL != ptInfo)
	{
		u8 byChanID = tStatus.m_bySubChan;

		if (tStatus.IsVaildStatus() && ptInfo->m_pcChannel->ValidPlayInfo(byChanID) && 
			em_hdu_chan_idle == ptInfo->m_pcChannel->GetChanStatus(byChanID))
		{
			InitHduToCall(ptInfo, byChanID);
		}
		
		if (!tStatus.IsVaildStatus() && em_hdu_chan_idle != ptInfo->m_pcChannel->GetChanStatus(byChanID))
		{
			StopHduPlay(ptInfo, byChanID);
		}
		
		// 改变音量或静音状态更新数据
		if (tStatus.m_tChanVol.m_byVol != ptInfo->m_pcChannel->GetVol() ||
			tStatus.m_tChanVol.m_bMute != ptInfo->m_pcChannel->IsMute())
		{
			ptInfo->m_pcChannel->SetVol(tStatus.m_tChanVol.m_byVol);
			ptInfo->m_pcChannel->SetMute(tStatus.m_tChanVol.m_bMute);
			SendHduPlanInfo();	
		}
	
	}

	return;
}

void CUmsHduHandleService::EventUpdateStatus(u8* pData, u16 wDataSize)
{
	THduUpdateInfo tInfo;
	TP_SAFE_CAST(tInfo, pData);
	MdlHint(Ums_Mdl_Service, ("EventUpdateStatus Layer:%d, Slot:%d, OnLine:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_bOnLine));
}

void CUmsHduHandleService::EventReqIFrame(u8* pData, u16 wDataSize)
{
	THduIFrameInfo tInfo;
	TP_SAFE_CAST(tInfo, pData);

	MdlLowDtl(Ums_Mdl_Service, ("EventReqIFrame Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d.\n",
							   tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_bySubChan));

	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventReqIFrame Invalid position.\n"));
		return ;
	}

	if (em_hdu_chan_working != ptInfo->m_pcChannel->GetChanStatus(tInfo.m_bySubChan))
	{
		MdlError(Ums_Mdl_Service, ("EventReqIFrame Channel is not in working.\n"));
		return ;
	}

	TPlayInfo tPlayInfo = ptInfo->m_pcChannel->GetPlayInfo(tInfo.m_bySubChan);

	TTPHduPlayReq tKeyInfo;
	tKeyInfo.m_bySubIndex = tInfo.m_bySubChan;
	tKeyInfo.m_emType = tPlayInfo.m_emType;
	tKeyInfo.m_wConfID = tPlayInfo.m_wConfID;
	tKeyInfo.m_wDstID = tPlayInfo.m_wDstID;
	tKeyInfo.m_wIndex = ptInfo->m_wIndex;
	tKeyInfo.m_wScreenNum = tPlayInfo.m_wScreenNum;

	NotifyCall(ev_TvMonitor_AskKey, &tKeyInfo, sizeof(TTPHduPlayReq));
}

void CUmsHduHandleService::GetHduUesInfo(TTPBrdUsedInfo& tUseInfo)
{
	tUseInfo.m_wRegNum = 0;
	tUseInfo.m_wUsedNum = 0;

	for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; ++wIndex)
	{
		if (m_acHdu[wIndex].ValidBrd() && m_acHdu[wIndex].BrdRegState())
		{
			++(tUseInfo.m_wRegNum);
		}
	}

	tUseInfo.m_wRegNum *= HDU_MAX_CHANNEL_NUM;
	tUseInfo.m_wUsedNum = m_cHduPlanEx.GetValidNum();
}


BOOL32 CUmsHduHandleService::IsToolUser(const TLogUser& ptUser)
{
	return GETAPP(ptUser.m_dwUserInst) == AID_UMSTOOL2UMS_APP;
}

u16 CUmsHduHandleService::GetHduIndex(u8 byLayer, u8 bySlot)
{
	if (byLayer < HDU_MAX_LAYER && bySlot < HDU_MAX_SLOT)
	{
		for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; ++wIndex)
		{			
			if (byLayer == m_acHdu[wIndex].Layer() && bySlot == m_acHdu[wIndex].Slot())
			{
				return wIndex;
			}
		}
	}

	return HDU_MAX_NUM;
}

void CUmsHduHandleService::InitHduToCall(THduPlayUnit* ptInfo, u8 bySubChanID, BOOL32 bChangeMode)
{
	BOOL32 bHduOnline = ptInfo->m_pcHdu->BrdRegState();	
	if (!bHduOnline)
	{
		MdlHint(Ums_Mdl_Service, ("[InitHduToCall] hdu is not online! wait to call...\n"));
		return;
	}

	TPlayInfo tPlayInfo = ptInfo->m_pcChannel->GetPlayInfo(bySubChanID);
	u32 dwIP = ptInfo->m_pcHdu->BrdIP();
	u16 wPort = ptInfo->m_pcHdu->GetStartPort();
	u8 byChanID = ptInfo->m_pcChannel->GetChanID();

	u8 abyBuf[sizeof(TAddTvMonitor) + sizeof(BOOL32) + sizeof(BOOL32)] = {0};
	TAddTvMonitor tInfo;
	tInfo.m_tReq.m_wIndex = ptInfo->m_wIndex;
	tInfo.m_tReq.m_bySubIndex = bySubChanID;

	//
	tInfo.m_tVidAddr.m_tRtpAddr.SetAddr(dwIP, wPort + (byChanID*HDU_VMP_PORT_SPAN+bySubChanID)*HDU_PORT_SPAN);
	tInfo.m_tVidAddr.m_tBackRtcpAddr.SetAddr(dwIP, wPort + (byChanID*HDU_VMP_PORT_SPAN+bySubChanID)*HDU_PORT_SPAN+1);
	tInfo.m_tAudAddr.m_tRtpAddr.SetAddr(dwIP, wPort + (byChanID*HDU_VMP_PORT_SPAN+bySubChanID)*HDU_PORT_SPAN+2);
	tInfo.m_tAudAddr.m_tBackRtcpAddr.SetAddr(dwIP, wPort + (byChanID*HDU_VMP_PORT_SPAN+bySubChanID)*HDU_PORT_SPAN+3);

	tInfo.m_tReq.m_emType = tPlayInfo.m_emType;
	tInfo.m_tReq.m_wConfID = tPlayInfo.m_wConfID;
	tInfo.m_tReq.m_wDstID = tPlayInfo.m_wDstID;
	tInfo.m_tReq.m_wScreenNum = tPlayInfo.m_wScreenNum;
	tInfo.m_tReq.m_bVmp = ptInfo->m_pcChannel->IsVmpChan();
		
	memcpy(abyBuf, &tInfo, sizeof(TAddTvMonitor));
	memcpy(abyBuf + sizeof(TAddTvMonitor), &bHduOnline, sizeof(BOOL32));
	memcpy(abyBuf + sizeof(TAddTvMonitor) + sizeof(BOOL32), &bChangeMode, sizeof(BOOL32));
	NotifyCall(ev_AddTvMonitor_req, abyBuf, sizeof(abyBuf));
	
	ptInfo->m_pcChannel->SetChanStatus(bySubChanID, em_hdu_chan_to_call);
}

void CUmsHduHandleService::UptateHduToCall(THduPlayUnit* ptInfo, u8 bySubChanID)
{
	BOOL32 bHduOnline = ptInfo->m_pcHdu->BrdRegState();	
	if (!bHduOnline)
	{
		MdlHint(Ums_Mdl_Service, ("[InitHduToCall] hdu is not online! wait to call...\n"));
		return;
	}
	
	TPlayInfo tPlayInfo = ptInfo->m_pcChannel->GetPlayInfo(bySubChanID);
	u32 dwIP = ptInfo->m_pcHdu->BrdIP();
	u16 wPort = ptInfo->m_pcHdu->GetStartPort();
	u8 byChanID = ptInfo->m_pcChannel->GetChanID();
	
	u8 abyBuf[sizeof(TAddTvMonitor) + sizeof(BOOL32)] = {0};
	TAddTvMonitor tInfo;
	tInfo.m_tReq.m_wIndex = ptInfo->m_wIndex;
	tInfo.m_tReq.m_bySubIndex = bySubChanID;
	
	//
	tInfo.m_tVidAddr.m_tRtpAddr.SetAddr(dwIP, wPort + (byChanID*HDU_VMP_PORT_SPAN+bySubChanID)*HDU_PORT_SPAN);
	tInfo.m_tAudAddr.m_tRtpAddr.SetAddr(dwIP, wPort + (byChanID*HDU_VMP_PORT_SPAN+bySubChanID)*HDU_PORT_SPAN+2);
	
	tInfo.m_tReq.m_emType = tPlayInfo.m_emType;
	tInfo.m_tReq.m_wConfID = tPlayInfo.m_wConfID;
	tInfo.m_tReq.m_wDstID = tPlayInfo.m_wDstID;
	tInfo.m_tReq.m_wScreenNum = tPlayInfo.m_wScreenNum;
	tInfo.m_tReq.m_bVmp = ptInfo->m_pcChannel->IsVmpChan();
	
	memcpy(abyBuf, &tInfo, sizeof(TAddTvMonitor));
	memcpy(abyBuf + sizeof(TAddTvMonitor), &bHduOnline, sizeof(BOOL32));	
	NotifyCall(ev_RestartTvMonitor_cmd, abyBuf, sizeof(abyBuf));

	return;
}

void CUmsHduHandleService::StopHduToCall(THduPlayUnit* ptInfo, u8 bySubChanID)
{
	TPlayInfo tPlayInfo = ptInfo->m_pcChannel->GetPlayInfo(bySubChanID);
	TTPHduPlayReq tInfo;
	tInfo.m_emType = tPlayInfo.m_emType;
	tInfo.m_wConfID = tPlayInfo.m_wConfID;
	tInfo.m_wDstID = tPlayInfo.m_wDstID;
	tInfo.m_wIndex = ptInfo->m_wIndex;
	tInfo.m_wScreenNum = tPlayInfo.m_wScreenNum;
	tInfo.m_bySubIndex = bySubChanID;

	NotifyCall(ev_DelTvMonitor_req, &tInfo, sizeof(TTPHduPlayReq));
	
	ptInfo->m_pcChannel->SetChanStatus(bySubChanID, em_hdu_chan_idle);
}

void CUmsHduHandleService::StopHduPlay(THduPlayUnit* ptInfo, u8 bySubChanID)
{
	EmHduChanStatus emStatus = ptInfo->m_pcChannel->GetChanStatus(bySubChanID);
	if (em_hdu_chan_working == emStatus || em_hdu_chan_to_hdu == emStatus ||
		em_hdu_chan_to_call == emStatus)
	{
		StopHduToCall(ptInfo, bySubChanID);
	}
	
	if (em_hdu_chan_working == emStatus || em_hdu_chan_to_hdu == emStatus)
	{
		THduPlayInfo tHduInfo;
		tHduInfo.m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
		tHduInfo.m_byLayer = ptInfo->m_pcHdu->Layer();
		tHduInfo.m_bySlot = ptInfo->m_pcHdu->Slot();
		tHduInfo.m_bySubChan = bySubChanID;
		tHduInfo.m_bVmp = ptInfo->m_pcChannel->IsVmpChan();
		UmsNotifyMsgToEqp(ev_hdu_stop_play_req, &tHduInfo, sizeof(THduPlayInfo));
	}

	ptInfo->m_pcChannel->ClearPlayInfo(bySubChanID);
}

void CUmsHduHandleService::SaveHduBrdInfo()
{
	for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; ++wIndex)
	{
		SaveHduBrdInfo(wIndex);
	}
}

void CUmsHduHandleService::SaveHduBrdInfo(u16 wIndex)
{
	THduCfgInfo tInfo;
	if (m_acHdu[wIndex].ValidBrd())
	{
		m_acHdu[wIndex].GetCfgInfo(tInfo);
		umsSetHduCfg(wIndex, tInfo);
	}
}

void CUmsHduHandleService::SaveHduPlanInfo()
{
	THduStyleCfgInfo tInfo;
	tInfo.m_byRow = m_cHduPlanEx.RowNum();
	tInfo.m_byCol = m_cHduPlanEx.ColNum();

	THduPlayUnit* ptInfo = NULL;
	for (u16 wIndex = 0; wIndex < m_cHduPlanEx.TotalChannel(); ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			tInfo.m_atHduStyle[wIndex].m_bVmp = ptInfo->m_pcChannel->IsVmpChan();
			tInfo.m_atHduStyle[wIndex].m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
			tInfo.m_atHduStyle[wIndex].m_byLayer = ptInfo->m_pcHdu->Layer();
			tInfo.m_atHduStyle[wIndex].m_bySlot = ptInfo->m_pcHdu->Slot();
			tInfo.m_atHduStyle[wIndex].m_tName.SetAlias(ptInfo->m_tName.m_abyAlias);
		}
	}

	umsSetHduStyle(tInfo);
}

void CUmsHduHandleService::SendHduPlanInfo(BOOL32 bUmcReq,  BOOL32 bCnsReq)
{
	THduPlanData tData;
	GetALLHduPalnInfo(tData);
	// 转成网络序
	THduPlanData tNetData;
	tNetData.SetValue(tData);
	
	// 需要发送给umc
	if (bUmcReq)
	{
		TLogUser tUser;
		TpNotifyMsgToUeFromService(ev_hduPlan_Nty, &tNetData, sizeof(THduPlanData), tUser);	
	}
	
	// 需要发送给cns
	if (bCnsReq)
	{
		// 通知cns
		SendToCnsHduPlanInfo();
	}
}

void CUmsHduHandleService::ShowHdu()
{
	for (u16 wIndex = 0; wIndex < HDU_MAX_NUM; ++wIndex)
	{
		if (m_acHdu[wIndex].ValidBrd())
		{
			m_acHdu[wIndex].Dump();
		}
	}
}

void CUmsHduHandleService::ShowHduStyle()
{
	m_cHduPlanEx.Dump();
}

void CUmsHduHandleService::EventChangeChanModeReq( u8* pData, u16 wDataSize )
{
	TLogUser tUser;	
	THduChanModeSetInfo tInfo;
	TP_SAFE_CAST(tUser, pData);
	TP_SAFE_CAST(tInfo, pData+sizeof(TLogUser));


	MdlHint(Ums_Mdl_Service, ("EventChangeChanModeReq Index:%d, Mode:%d.\n",
		tInfo.m_wIndex, tInfo.m_byMode));
	
	EmTpHduChangeChanModeRes emRes = em_hdu_change_mode_success;
	
	// 修改通道状态参数校验
	HduChangeChanModeStateFromUmcCns(tInfo, emRes);

	if (emRes != em_hdu_change_mode_success)
	{
		u8 szRes[sizeof(THduChanModeSetInfo)+sizeof(EmTpHduChangeChanModeRes)] = {0};
		memcpy(szRes, &tInfo, sizeof(THduChanModeSetInfo));
		memcpy(szRes+sizeof(THduChanModeSetInfo), &emRes, sizeof(EmTpHduChangeChanModeRes));
		TpNotifyMsgToUeFromService(ev_Hdu_ChangeChanMode_Rsp, szRes, sizeof(szRes), tUser);
	}

	return;
}

void CUmsHduHandleService::EventChangeChanModeRsp( u8* pData, u16 wDataSize )
{
	THduChanModeInfo tInfo;
	EmTpHduChangeChanModeRes emRes;
	TP_SAFE_CAST(tInfo, pData);
	TP_SAFE_CAST(emRes, pData+sizeof(THduChanModeInfo));


	MdlHint(Ums_Mdl_Service, ("EventChangeChanModeRsp Layer:%d, Slot:%d, Chan:%d, Mode:%d, Res:%d.\n",
		tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_byChanMode, emRes));
	
	THduPlayUnit* ptInfo = m_cHduPlanEx.FindChannel(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex);
	if (NULL == ptInfo)
	{
		MdlError(Ums_Mdl_Service, ("EventChangeChanModeRsp Invalid position.\n"));
		return ;
	}
	
	if (em_hdu_change_mode_success != emRes)
	{
		MdlError(Ums_Mdl_Service, ("EventChangeChanModeRsp Error! Layer:%d, Slot:%d, Chan:%d, Mode:%d, Res:%d.\n",
			tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_byChanMode, emRes));

		for (u8 byIndex = 0; byIndex < HDU_MAX_VMP_SUBCHAN; ++byIndex)
		{
			StopHduPlay(ptInfo, byIndex);
		}

		
	}

	TLogUser tUser;
	THduChanModeSetInfo tRspInfo;
	tRspInfo.m_wIndex = ptInfo->m_wIndex;
	tRspInfo.m_byMode = tInfo.m_byChanMode;
	
	u8 szRes[sizeof(THduChanModeSetInfo)+sizeof(EmTpHduChangeChanModeRes)] = {0};
	memcpy(szRes, &tRspInfo, sizeof(THduChanModeSetInfo));
	memcpy(szRes+sizeof(THduChanModeSetInfo), &emRes, sizeof(EmTpHduChangeChanModeRes));
	TpNotifyMsgToUeFromService(ev_Hdu_ChangeChanMode_Rsp, szRes, sizeof(szRes), tUser);
	

	TUmsHandle tHandle;
	u8 abBuf[sizeof(tHandle)+sizeof(THduChanModeSetInfo)+sizeof(EmTpHduChangeChanModeRes)] = {0};
	memcpy(abBuf, &(tHandle), sizeof(tHandle));
	memcpy(abBuf+sizeof(tHandle), &tRspInfo, sizeof(tRspInfo));
	memcpy(abBuf+sizeof(tHandle)+sizeof(tRspInfo), &emRes, sizeof(emRes));
	NotifyCall(evTPUMS_CNS_HduChangeChanMode_Ind, abBuf, sizeof(abBuf));

	SendHduPlanInfo();

	return;
}

////////////////////////////////
///终端操作电视墙相关

void CUmsHduHandleService::EventFromCnsHduPlayReq(u8* pData, u16 wDataSize)
{
	TUmsHandle tHandle;
	TTPHduPlayReq tReq;
	
	TP_SAFE_CAST(tHandle, pData);
	TP_SAFE_CAST(tReq, pData+sizeof(tHandle));
	
	MdlHint(Ums_Mdl_Service, ("EventFromCnsHduPlayReq Type:%d, ConfID:%d, DstID:%d, Screen;%d, Name:%s, Index:%d, SunIndex:%d.\n",
							   tReq.m_emType, tReq.m_wConfID, tReq.m_wDstID, tReq.m_wScreenNum, tReq.m_achAlias, tReq.m_wIndex, tReq.m_bySubIndex));
	
	EmTpHduPlayNackReason emReason = em_hdu_play_success;

	// 请求消息状态判断
	HduPlayReqStateFromUmcCns(tReq, emReason);
	
	TPHduBaseInfo tBaseInfo;
	tBaseInfo.m_wIndex     = tReq.m_wIndex;
	tBaseInfo.m_bySubIndex = tReq.m_bySubIndex;

	u8 abBuf[sizeof(tHandle)+sizeof(tBaseInfo)+sizeof(emReason)] = {0};
	memcpy(abBuf, &(tHandle), sizeof(tHandle));
	memcpy(abBuf+sizeof(tHandle), &tBaseInfo, sizeof(tBaseInfo));
	memcpy(abBuf+sizeof(tHandle)+sizeof(tBaseInfo), &emReason, sizeof(emReason));
	

	NotifyCall(evTPUMS_CNS_HduPlay_Ind, abBuf, sizeof(abBuf));	

	return;
}

void CUmsHduHandleService::EventFromCnsHduStopPlay(u8* pData, u16 wDataSize)
{
	TUmsHandle tHandle;
	TTPHduPlayReq tReq;
	
	TP_SAFE_CAST(tHandle, pData);
	TP_SAFE_CAST(tReq, pData+sizeof(tHandle));
	
	MdlHint(Ums_Mdl_Service, ("EventFromCnsHduStopPlay Type:%d, ConfID:%d, DstID:%d, ScreenNum:%d, Index%d, SubIndex:%d.\n",
		tReq.m_emType, tReq.m_wConfID, tReq.m_wDstID, tReq.m_wScreenNum, tReq.m_wIndex, tReq.m_bySubIndex));
	
	BOOL32 bRes = TRUE;
	
	// 停止播放电视墙某个通道状态判断
	HduStopReqStateFromUmcCns(tReq, bRes);
	
	TPHduBaseInfo tBaseInfo;
	u16 wIsSuccess = 0;
	tBaseInfo.m_wIndex     = tReq.m_wIndex;
	tBaseInfo.m_bySubIndex = tReq.m_bySubIndex;
	if (bRes)
	{
		// 0 停止播放成功
		wIsSuccess = 0;   
	}
	else
	{
		// 非0 停止播放错误
		wIsSuccess = 1;
	}
	
	u8 abBuf[sizeof(tHandle)+sizeof(tBaseInfo)+sizeof(u16)] = {0};
	memcpy(abBuf, &(tHandle), sizeof(tHandle));
	memcpy(abBuf+sizeof(tHandle), &tBaseInfo, sizeof(tBaseInfo));
	memcpy(abBuf+sizeof(tHandle)+sizeof(tBaseInfo), &wIsSuccess, sizeof(wIsSuccess));
		
	NotifyCall(evTPUMS_CNS_HduStopPlay_Ind, abBuf, sizeof(abBuf));

	return;
}

void CUmsHduHandleService::EventFromCnsHduAllStopPlay(u8* pData, u16 wDataSize)
{
	MdlHint(Ums_Mdl_Service, ("EventFromCnsHduAllStopPlay Stop all hdu.\n"));
	
	u16 wTotal = m_cHduPlanEx.TotalChannel();
	THduPlayUnit* ptInfo = NULL;
	u8 bySubIndex = 0;
	for (u16 wIndex = 0; wIndex < wTotal; ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			if (ptInfo->m_pcChannel->IsVmpChan())
			{
				for (bySubIndex = 0; bySubIndex < HDU_MAX_VMP_SUBCHAN; ++bySubIndex)
				{
					if (em_hdu_chan_idle != ptInfo->m_pcChannel->GetChanStatus(bySubIndex))
					{
						StopHduPlay(ptInfo, bySubIndex);
						ptInfo->m_pcChannel->ClearPlayInfo(bySubIndex);
					}
				}
			}
			else
			{
				bySubIndex = 0;
				if (em_hdu_chan_idle != ptInfo->m_pcChannel->GetChanStatus(bySubIndex))
				{
					StopHduPlay(ptInfo, bySubIndex);
					ptInfo->m_pcChannel->ClearPlayInfo(bySubIndex);
				}
			}
		}
	}
	
	// 更新所有通道状态
	SendHduPlanInfo();	
}

void CUmsHduHandleService::EventFromCnsSetVolInfo(u8* pData, u16 wDataSize)
{
	TUmsHandle tHandle;	
	THduSetVolInfo tInfo;
	TP_SAFE_CAST(tHandle, pData);
	TP_SAFE_CAST(tInfo, pData+sizeof(tHandle));
	
	MdlHint(Ums_Mdl_Service, ("EventFromCnsSetVolInfo Index:%d, Vol:%d, Mute:%d.\n",
		tInfo.m_tInfo.m_wIndex, tInfo.m_byVol, tInfo.m_bMute));
	
	EmTpHduSetVolRes emRes = em_hdu_SetVol_Success;
	THduPlayUnit* ptInfo = m_cHduPlanEx.GetChannel(tInfo.m_tInfo.m_wIndex);
	
	// 修改电视墙音量状态校验
	HduSetVolReqStateFromUmcCns(ptInfo, emRes);
	
	if (em_hdu_SetVol_Success != emRes)
	{
		u8 abBuf[sizeof(tHandle)+sizeof(tInfo)+sizeof(emRes)] = {0};
		memcpy(abBuf, &(tHandle), sizeof(tHandle));
		memcpy(abBuf+sizeof(tHandle), &tInfo, sizeof(tInfo));
		memcpy(abBuf+sizeof(tHandle)+sizeof(tInfo), &emRes, sizeof(emRes));
		
		NotifyCall(evTPUMS_CNS_HduSetVol_Ind, abBuf, sizeof(abBuf));
	}
	else
	{
		THduVolInfo tVolInfo;
		tVolInfo.m_byLayer = ptInfo->m_pcHdu->Layer();
		tVolInfo.m_byChanlIdx = ptInfo->m_pcChannel->GetChanID();
		tVolInfo.m_byIsMute = tInfo.m_bMute;
		tVolInfo.m_bySlot = ptInfo->m_pcHdu->Slot();
		tVolInfo.m_byVolume = tInfo.m_byVol;
		UmsNotifyMsgToEqp(ev_hdu_set_vol, &tVolInfo, sizeof(tVolInfo));
	}	
}

void CUmsHduHandleService::EventFromCnsChangeChanModeReq(u8* pData, u16 wDataSize)
{
	TUmsHandle tHandle;	
	THduChanModeSetInfo tInfo;
	TP_SAFE_CAST(tHandle, pData);
	TP_SAFE_CAST(tInfo, pData+sizeof(tHandle));


	MdlHint(Ums_Mdl_Service, ("EventFromCnsChangeChanModeReq Index:%d, Mode:%d.\n",
		tInfo.m_wIndex, tInfo.m_byMode));
	
	EmTpHduChangeChanModeRes emRes = em_hdu_change_mode_success;

	HduChangeChanModeStateFromUmcCns(tInfo, emRes);

	
	if (emRes != em_hdu_change_mode_success)
	{
		u8 abBuf[sizeof(tHandle)+sizeof(tInfo)+sizeof(emRes)] = {0};
		memcpy(abBuf, &(tHandle), sizeof(tHandle));
		memcpy(abBuf+sizeof(tHandle), &tInfo, sizeof(tInfo));
		memcpy(abBuf+sizeof(tHandle)+sizeof(tInfo), &emRes, sizeof(emRes));
		
		NotifyCall(evTPUMS_CNS_HduChangeChanMode_Ind, abBuf, sizeof(abBuf));
	}

	return;
}

void CUmsHduHandleService::SendToCnsHduPlanInfo(u16 wConfID, u16 wEpID)
{
	THduPlanData tData;
	THduPlanPackData tPlanPackData;

	GetALLHduPalnInfo(tData);

	tPlanPackData.Clear();
	tPlanPackData.m_byCol = tData.m_byCol;
	tPlanPackData.m_byRow = tData.m_byRow;
	tPlanPackData.m_wNum  = tData.m_wNum;

	TUmsHandle tHandle;	
	tHandle.MakeAppHandle(wConfID, wEpID);
	u8 abBuf[sizeof(tHandle)+sizeof(tPlanPackData)] = {0};
	memcpy(abBuf, &(tHandle), sizeof(tHandle));

	MdlHint(Ums_Mdl_Service, ("SendToCnsHduPlanInfo Col:%d, Row:%d AllNum:%d .\n",
		tPlanPackData.m_byCol, tPlanPackData.m_byRow, tPlanPackData.m_wNum));

	u16 wIndex = 0;
	// 完整包数据添加
	for (; wIndex < tData.m_wNum/TP_STYLE_DATA_PACK_NUM; ++wIndex)
	{
		tPlanPackData.m_CurentNum = TP_STYLE_DATA_PACK_NUM;
		if (0 == wIndex)
		{
			tPlanPackData.m_byFirst = 1;
		}
		else
		{
			tPlanPackData.m_byFirst = 0;
		}
		
		memcpy(tPlanPackData.m_atUnits, tData.m_atUnits+wIndex*TP_STYLE_DATA_PACK_NUM, sizeof(tPlanPackData.m_atUnits));
		
		// 发送数据包
		memcpy(abBuf+sizeof(tHandle), &(tPlanPackData), sizeof(tPlanPackData));

		MdlHint(Ums_Mdl_Service, ("[%d] SendToCnsHduPlanInfo[loop] Col:%d, Row:%d AllNum:%d m_CurentNum:%d first:%d.\n",
		wIndex, tPlanPackData.m_byCol, tPlanPackData.m_byRow, tPlanPackData.m_wNum,
		tPlanPackData.m_CurentNum, tPlanPackData.m_byFirst));

		NotifyCall(evTPUMS_CNS_hduPlan_Nty, abBuf, sizeof(abBuf));

	}
	tPlanPackData.m_CurentNum = tData.m_wNum - TP_STYLE_DATA_PACK_NUM*wIndex;
	if (0 == tPlanPackData.m_CurentNum)
	{
		MdlHint(Ums_Mdl_Service, ("SendToCnsHduPlanInfo all is send....\n"));
		return;
	}
	if (0 == wIndex)
	{
		tPlanPackData.m_byFirst = 1;
	}
	else
	{
		tPlanPackData.m_byFirst = 0;
	}
	memset(tPlanPackData.m_atUnits, 0, sizeof(tPlanPackData.m_atUnits));
	// 最后一包数据的添加
	memcpy(tPlanPackData.m_atUnits, tData.m_atUnits+wIndex*TP_STYLE_DATA_PACK_NUM, sizeof(THduPlanUnit)*tPlanPackData.m_CurentNum);
	
	MdlHint(Ums_Mdl_Service, ("[%d]SendToCnsHduPlanInfo Col:%d, Row:%d AllNum:%d m_CurentNum:%d first:%d.\n",
		wIndex, tPlanPackData.m_byCol, tPlanPackData.m_byRow, tPlanPackData.m_wNum,
		tPlanPackData.m_CurentNum, tPlanPackData.m_byFirst));

	memcpy(abBuf+sizeof(tHandle), &(tPlanPackData), sizeof(tPlanPackData));
	NotifyCall(evTPUMS_CNS_hduPlan_Nty, abBuf, sizeof(abBuf));
}


void CUmsHduHandleService::HduPlayReqStateFromUmcCns(TTPHduPlayReq& tReq, EmTpHduPlayNackReason& emReason)
{
	THduPlayUnit* ptInfo = NULL;
	do 
	{
		ptInfo = m_cHduPlanEx.GetChannel(tReq.m_wIndex);
		if (NULL == ptInfo)
		{
			emReason = em_Hdu_Invalid_Index;
			MdlError(Ums_Mdl_Service, ("HduPlayReqStateFromUmcCns Invalid index.\n"));
			break;
		}
		
		if (tReq.m_bVmp != ptInfo->m_pcChannel->IsVmpChan())
		{
			emReason = em_Hdu_Invalid_Index;
			MdlError(Ums_Mdl_Service, ("HduPlayReqStateFromUmcCns Invalid Vmp param.\n"));
			break;
		}
		
		if (!tReq.m_bVmp)
		{// 非合成通道，子索引固定为0
			tReq.m_bySubIndex = 0;
		}
		else
		{ // 合成通道，子索引0 1 2 3
			if (HDU_MAX_VMP_SUBCHAN <= tReq.m_bySubIndex)
			{
				emReason = em_Hdu_Invalid_Index;
				MdlError(Ums_Mdl_Service, ("HduPlayReqStateFromUmcCns Invalid subindex param.\n"));
				break;
			}
			
			if (tReq.m_emType == EmEpType_Eqp)
			{
				emReason = em_unknown;
				MdlError(Ums_Mdl_Service, ("HduPlayReqStateFromUmcCns Dst is Eqp, Now is Vmp Mode!."));
				break;
			}
		}
		
		EmHduChanStatus emStatus = ptInfo->m_pcChannel->GetChanStatus(tReq.m_bySubIndex);
		if (em_hdu_chan_invalid == emStatus)
		{
			emReason = em_unknown;
			MdlError(Ums_Mdl_Service, ("HduPlayReqStateFromUmcCns Invalid emStatus.\n"));
			break;
		}
		
		if (em_hdu_chan_idle != emStatus)
		{
			TPlayInfo tPlayInfo = ptInfo->m_pcChannel->GetPlayInfo(tReq.m_bySubIndex);
			if (tPlayInfo.m_wConfID == tReq.m_wConfID && tPlayInfo.m_wDstID == tReq.m_wDstID &&
				tPlayInfo.m_emType == tReq.m_emType && tPlayInfo.m_wScreenNum == tReq.m_wScreenNum)
			{
				emReason = em_Same_Info;
				MdlError(Ums_Mdl_Service, ("HduPlayReqStateFromUmcCns same play info.\n"));
				break;
			}
			else
			{
				StopHduPlay(ptInfo, tReq.m_bySubIndex);
			}
		}
		
		TPlayInfo tPlayInfo;
		tPlayInfo.m_emType = tReq.m_emType;
		tPlayInfo.m_wConfID = tReq.m_wConfID;
		tPlayInfo.m_wDstID = tReq.m_wDstID;
		tPlayInfo.SetAlias(tReq.m_achAlias);
		tPlayInfo.m_wScreenNum = tReq.m_wScreenNum;
		// 设置播放信息
		ptInfo->m_pcChannel->SetPlayInfo(tReq.m_bySubIndex, tPlayInfo);
		
	} while (FALSE);
	
	if (em_hdu_play_success == emReason )
	{
		InitHduToCall(ptInfo, tReq.m_bySubIndex);
	}
	else
	{
		// 更新通道状态
		SendHduPlanInfo();
	}	
}

void CUmsHduHandleService::HduStopReqStateFromUmcCns( TTPHduPlayReq& tReq, BOOL32& bRes )
{
	THduPlayUnit* ptInfo = NULL;
	do 
	{
		ptInfo = m_cHduPlanEx.GetChannel(tReq.m_wIndex);
		if (NULL == ptInfo)
		{
			MdlError(Ums_Mdl_Service, ("HduStopReqStateFromUmcCns Invalid position.\n"));
			bRes = FALSE;
			break;
		}
		
		EmHduChanStatus emChanStatus = ptInfo->m_pcChannel->GetChanStatus(tReq.m_bySubIndex);
		if (em_hdu_chan_invalid == emChanStatus)
		{
			MdlError(Ums_Mdl_Service, ("HduStopReqStateFromUmcCns Invalid status, current Status: %d.\n", emChanStatus));
			bRes = FALSE;
			break;
		}
		
		StopHduPlay(ptInfo, tReq.m_bySubIndex);
		
	} while (FALSE);
	
	SendHduPlanInfo();	
	
}

void CUmsHduHandleService::HduStopAllReqStateFromUmcCns(u8* pData, u16 wDataSize)
{
	MdlHint(Ums_Mdl_Service, ("HduStopAllReqStateFromUmcCns Stop all hdu.\n"));
	
	u16 wTotal = m_cHduPlanEx.TotalChannel();
	THduPlayUnit* ptInfo = NULL;
	u8 bySubIndex = 0;
	for (u16 wIndex = 0; wIndex < wTotal; ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			if (ptInfo->m_pcChannel->IsVmpChan())
			{
				for (bySubIndex = 0; bySubIndex < HDU_MAX_VMP_SUBCHAN; ++bySubIndex)
				{
					if (em_hdu_chan_idle != ptInfo->m_pcChannel->GetChanStatus(bySubIndex))
					{
						StopHduPlay(ptInfo, bySubIndex);
						ptInfo->m_pcChannel->ClearPlayInfo(bySubIndex);
					}
				}
			}
			else
			{
				bySubIndex = 0;
				if (em_hdu_chan_idle != ptInfo->m_pcChannel->GetChanStatus(bySubIndex))
				{
					StopHduPlay(ptInfo, bySubIndex);
					ptInfo->m_pcChannel->ClearPlayInfo(bySubIndex);
				}
			}
		}
	}
	
	SendHduPlanInfo();
}

void CUmsHduHandleService::HduSetVolReqStateFromUmcCns( THduPlayUnit* ptInfo, EmTpHduSetVolRes& emRes)
{	
	do 
	{
		if (NULL == ptInfo)
		{
			MdlError(Ums_Mdl_Service, ("HduSetVolReqStateFromUmcCns Invalid index.\n"));
			emRes = em_hdu_SetVol_Invalid_Index;
			break;
		}
		
		if (!ptInfo->m_pcHdu->ServiceRegState())
		{
			MdlError(Ums_Mdl_Service, ("HduSetVolReqStateFromUmcCns Service Unreg.\n"));
			emRes = em_hdu_SetVol_UnReg;
			break;
		}
		
		if (ptInfo->m_pcChannel->IsVmpChan())
		{
			MdlError(Ums_Mdl_Service, ("HduSetVolReqStateFromUmcCns VmpChan.\n"));
			emRes = em_hdu_SetVol_VmpChan;
			break;
		}
		
	} while (FALSE);
}

void CUmsHduHandleService::HduChangeChanModeStateFromUmcCns( THduChanModeSetInfo& tInfo, EmTpHduChangeChanModeRes& emRes)
{
	THduPlayUnit* ptInfo = m_cHduPlanEx.GetChannel(tInfo.m_wIndex);

	do 
	{
		if (!tInfo.IsValidMode())
		{
			MdlError(Ums_Mdl_Service, ("HduChangeChanModeStateFromUmcCns Invalid mode.\n"));
			emRes = em_hdu_change_mode_error_param;
			break;
		}

		if (NULL == ptInfo)
		{
			MdlError(Ums_Mdl_Service, ("HduChangeChanModeStateFromUmcCns Invalid index.\n"));
			emRes = em_hdu_change_mode_error_index;
			break;
		}
		
		if (!ptInfo->m_pcHdu->ServiceRegState())
		{
			MdlError(Ums_Mdl_Service, ("HduChangeChanModeStateFromUmcCns Service Unreg.\n"));
			emRes = em_hdu_change_mode_error_regstate;
			break;
		}

		if (ptInfo->m_pcChannel->IsSameMode(tInfo.m_byMode))
		{
			MdlError(Ums_Mdl_Service, ("HduChangeChanModeStateFromUmcCns Mode is not changed.\n"));
			emRes = em_hdu_change_mode_error_param;
			break;
		}

		if (ptInfo->m_pcHdu->IsHaveVmpChan() && tInfo.m_byMode)
		{
			MdlError(Ums_Mdl_Service, ("HduChangeChanModeStateFromUmcCns Only one VmpChan.\n"));
			emRes = em_hdu_change_mode_error_onlyoneVmp;
			break;
		}

		EmHduChanStatus emStatus = ptInfo->m_pcChannel->GetChanStatus(0);
		if (em_hdu_chan_idle != emStatus && em_hdu_chan_working != emStatus)
		{
			MdlError(Ums_Mdl_Service, ("HduChangeChanModeStateFromUmcCns error state:%d.\n", emStatus));
			emRes = em_hdu_change_mode_error_workingstate;
			break;
		}

		
	} while (FALSE);

	if (em_hdu_change_mode_success == emRes)
	{
		TPlayInfo tInfoBk; // 0号子通道的播放信息先备份下，多画面切换过程中，0号子通道的播放信息不能变
		tInfoBk = ptInfo->m_pcChannel->GetPlayInfo(0);

		// 所有子通道先stop，防止出现闪现
		for (u8 byIndex = 0; byIndex < HDU_MAX_VMP_SUBCHAN; ++byIndex)
		{
			StopHduPlay(ptInfo, byIndex);
		}

		// 先切成新模式
		ptInfo->m_pcChannel->SetVmpMode(tInfo.m_byMode);

		do 
		{
			if (tInfoBk.m_emStatus == em_hdu_chan_working)
			{			
				tInfoBk.m_emStatus = em_hdu_chan_idle;
				ptInfo->m_pcChannel->SetPlayInfo(0, tInfoBk);
				InitHduToCall(ptInfo, 0, TRUE);
				break;
			}
			
			THduChanModeInfo tChanInfo;
			tChanInfo.m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
			tChanInfo.m_byLayer = ptInfo->m_pcHdu->Layer();
			tChanInfo.m_bySlot = ptInfo->m_pcHdu->Slot();
			tChanInfo.m_byChanMode = tInfo.m_byMode;
			
			UmsNotifyMsgToEqp(ev_hdu_change_chan_mode, &tChanInfo, sizeof(tChanInfo));

		} while (0);
		
//		SendHduPlanInfo();
	}
}

void CUmsHduHandleService::GetALLHduPalnInfo(THduPlanData& tData)
{
	tData.m_byRow = m_cHduPlanEx.RowNum();
	tData.m_byCol = m_cHduPlanEx.ColNum();
	
	THduPlayUnit* ptInfo = NULL;
	u8  byChanID = 0;
	TPlayInfo tInfo;
	for(u16 wIndex = 0; wIndex < tData.m_byRow * tData.m_byCol; ++wIndex)
	{
		ptInfo = m_cHduPlanEx.GetChannel(wIndex);
		if (NULL != ptInfo)
		{
			tData.m_atUnits[tData.m_wNum].m_byReged = ptInfo->m_pcHdu->ServiceRegState()?1:0;
			tData.m_atUnits[tData.m_wNum].m_byVmp = ptInfo->m_pcChannel->IsVmpChan()?1:0;
			tData.m_atUnits[tData.m_wNum].m_tHduName.SetAlias(ptInfo->m_tName.m_abyAlias);
			tData.m_atUnits[tData.m_wNum].m_byValid = 1;
			tData.m_atUnits[tData.m_wNum].m_wIndex = wIndex;
			tData.m_atUnits[tData.m_wNum].m_byMute = ptInfo->m_pcChannel->IsMute()?1:0;
			tData.m_atUnits[tData.m_wNum].m_byVol = ptInfo->m_pcChannel->GetVol();
			tData.m_atUnits[tData.m_wNum].m_byChanIndex = ptInfo->m_pcChannel->GetChanID();
			
			for (byChanID = 0; byChanID < HDU_MAX_VMP_SUBCHAN; byChanID++)
			{
				tInfo = ptInfo->m_pcChannel->GetPlayInfo(byChanID);
				tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_wConfID = tInfo.m_wConfID;
				tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_wDstID = tInfo.m_wDstID;
				tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_wScreenNum = tInfo.m_wScreenNum;
				tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_emType = tInfo.m_emType;
				tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].SetAlias(tInfo.m_achAlias);
				switch (tInfo.m_emStatus)
				{
				case em_hdu_chan_invalid:
					{
						tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_emStatus = emTPHduUnknow;
					}
					break;
				case em_hdu_chan_idle:
					{
						tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_emStatus = emTPHduIdle;
					}
					break;
					
				case em_hdu_chan_to_call:
				case em_hdu_chan_to_hdu:
					{
						tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_emStatus = emTPHduWaiting;
					}
					break;
					
				case em_hdu_chan_working:
					{
						tData.m_atUnits[tData.m_wNum].m_atPlayInfo[byChanID].m_emStatus = emTPHduPlaying;
					}
					break;
				default:
					{
						MdlError(Ums_Mdl_Service, ("GetALLHduPalnInfo Invalid emStatus.\n"));
						break;
					}
				}
			}
		}
		else
		{
			tData.m_atUnits[tData.m_wNum].m_byValid = 0;
			tData.m_atUnits[tData.m_wNum].m_wIndex = wIndex;
		}
		
		++tData.m_wNum;
	}
}


void CUmsHduHandleService::EventMediaKeyNty(u8* pData, u16 wDataSize)
{
	u16 wChanIndex = 0;
	u8 bySubChan = 0;
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(wChanIndex, pData);
	TP_SAFE_CAST(bySubChan, pData+sizeof(u16));
	TP_SAFE_CAST(tInfo, pData+sizeof(u16)+sizeof(u8));
	
	MdlHint(Ums_Mdl_Service, ("EventMediaKeyNty ChanIndex:%d, subChnl:%d, Handle:%d, Index:%d, Key:%s.\n",
								wChanIndex, bySubChan, tInfo.m_dwHandle, tInfo.m_wIndex, tInfo.m_szMediaKey));
	
	do 
	{
		THduPlayUnit* ptUnit = m_cHduPlanEx.GetChannel(wChanIndex);
		if (NULL==ptUnit)
		{
			MdlError(Ums_Mdl_Service, ("EventMediaKeyNty Invalid index.\n"));
			break;
		}
		
		THduPlayInfo tHduInfo;
		tHduInfo.m_byChanIndex = ptUnit->m_pcChannel->GetChanID();
		tHduInfo.m_byLayer = ptUnit->m_pcHdu->Layer();
		tHduInfo.m_bySlot = ptUnit->m_pcHdu->Slot();
		tHduInfo.m_bySubChan = bySubChan;
		tHduInfo.m_bVmp = ptUnit->m_pcChannel->IsVmpChan();
		
		u8 abBuf[sizeof(THduPlayInfo)+sizeof(TTPQTMediaKeyInfo)] = {0};
		memcpy(abBuf, &tHduInfo, sizeof(THduPlayInfo));
		memcpy(abBuf+sizeof(THduPlayInfo), &tInfo, sizeof(tInfo));
		UmsNotifyMsgToEqp(ev_hdu_media_key_nty, abBuf, sizeof(abBuf));
		
	} while (FALSE);
}
