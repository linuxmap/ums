#include "hduhandler.h"
#include "osp.h"
#include "umsobject.h"
#include "tplog.h"
#include "hdudef.h"
#include "mcuinstdef.h"
#include "innereventumshdu.h"
#include "mcuboardmgr.h"
#include "umsconfigex.h"

CHduHandler::CHduHandler()
{

}

CHduHandler::~CHduHandler()
{

}

BOOL32 CHduHandler::MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u16 wEvent = ptMsg->event;
	
	if (NULL == pInst)
	{
		MdlError(Ums_Mdl_Eqp, ("CHduHandler::MsgFromServiceHandler Instance is NULL.\n"));
		return FALSE;
	}

	BOOL32 bProc = TRUE;
	switch (wEvent)
	{
	case OSP_DISCONNECT:
		{
			EventDisconnect(ptMsg, pInst);
		}
		break;

	case UMS_HDU_REG_REQ:				
		{
			EventReg(ptMsg, pInst);
		}
		break;
			
	case UMS_HDU_PLAY_ACK:				
		{
			EventPlayAck(ptMsg, pInst);
		}
		break;
		
	case UMS_HDU_PLAY_NACK:				
		{
			EventPlayNack(ptMsg, pInst);
		}
		break;
		
	case UMS_HDU_STOP_PLAY_ACK:			
		{
			EventStopPlayAck(ptMsg, pInst);
		}
		break;
		
	case UMS_HDU_STOP_PLAY_NACK:		
		{
			EventStopPlayNack(ptMsg, pInst);
		}
		break;
		
	case HDU_UMS_CHNNLSTATUS_NOTIF:
		{
			EventUpdateChanStatus(ptMsg, pInst);
		}
		break;

	case HDU_UMS_NEEDIFRAME_CMD:
		{
			EventReqIFrame(ptMsg, pInst);
		}
		break;
		
	case UMS_BOARD_MPC_UPDATE_NOTIFY:	
		{
			EventUpdateNotify(ptMsg, pInst);
		}
		break;
		
	case HDU_UMS_STATUS_NOTIF:
		{
			EventUpdateStatus(ptMsg, pInst);
		}
		break;
	case HDU_UMS_CHGHDUVMPMODE_ACK:
		{
			EventChangeHduChanModeAck(ptMsg, pInst);
		}
		break;
	case HDU_UMS_CHGHDUVMPMODE_NACK:
		{
			EventChangeHduChanModeNack(ptMsg, pInst);
		}
		break;
	default:
		{
			MdlHint(Ums_Mdl_Eqp, ("CHduHandler::MsgFromServiceHandler Unknow event. EventID:%d, InsID:%d.\n",
								   wEvent, pInst->GetInsID()));
			bProc = FALSE;
		}
		break;
	}

	return bProc;

}

void CHduHandler::EventDisconnect(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventDisconnect InsID:%d.\n", pInst->GetInsID()));

	//SendMsgToEqp(ev_hdu_disconnect, 0, NULL, pInst->GetInsID(), pInst->GetBrdNode());
	SendMsgToEqp(ev_hdu_disconnect, NULL, 0, pInst->GetInsID(), pInst->GetBrdNode());
}

void CHduHandler::EventReg(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{	
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpRegReq tEqpReg;
	const u16 wMsgBodyLen = cServMsg.GetMsgBodyLen();
    memcpy(&tEqpReg, cServMsg.GetMsgBody(), min(sizeof(TPeriEqpRegReq), wMsgBodyLen));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventReg. Hdu Reg! EqpID:%d, InsID:%d, EqpType:%d, EqpIP:"TPIPFORMAT", RcvStartPort:%d, Ver:%d\n", 
							  tEqpReg.GetEqpId(), pInst->GetInsID(), tEqpReg.GetEqpType(), Tpu32ToIP(tEqpReg.GetPeriEqpIpAddr()), 
							  tEqpReg.GetStartPort(), tEqpReg.GetVersion()));
	
	if (tEqpReg.GetEqpId() != pInst->GetInsID())// || tEqpReg.GetEqpType() != EQP_TYPE_HDU2)
	{
		MdlError(Ums_Mdl_Eqp, ("CHduHandler::EventReg. EqpID is Invalid!\n"));

		OspPost(ptMsg->srcid, UMS_HDU_REG_NACK, NULL, 0, ptMsg->srcnode);
        ::OspDisconnectTcpNode(ptMsg->srcnode);

		return ;
	}

	pInst->SetBrdNode(ptMsg->srcnode);
	pInst->SetBrdIID(ptMsg->srcid);

	THduRegInfo tHduRegInfo;
	tHduRegInfo.m_byLayer = Layer(pInst);
	tHduRegInfo.m_bySlot = Slot(pInst);
	memcpy(tHduRegInfo.m_achAlias, tEqpReg.GetEqpAlias(), TP_MAXLEN_EQP_ALIAS);
	tHduRegInfo.m_bHDEqp = tEqpReg.IsHDEqp();
	tHduRegInfo.m_byChannlNum = tEqpReg.GetChnnlNum();
	tHduRegInfo.m_dwIpAddr = tEqpReg.GetPeriEqpIpAddr();
	tHduRegInfo.m_wStartPort = tEqpReg.GetStartPort();
	tHduRegInfo.m_wVersion = tEqpReg.GetVersion();
	
	SendMsgToEqp(ev_hdu_reg_req, (u8*)&tHduRegInfo, sizeof(THduRegInfo), pInst->GetInsID(), pInst->GetBrdNode());

	OspSetHBParam(ptMsg->srcnode, 2, 3);
	OspNodeDiscCBRegQ(ptMsg->srcnode, pInst->GetAppID(), pInst->GetInsID());
}

void CHduHandler::EventPlayAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventPlayAck Layer:%d, Slot:%d, ChanIndex:%d.\n",
							  Layer(pInst), Slot(pInst), cServMsg.GetChnIndex()));
	
	THduPlayInfo tInfo;
	tInfo.m_byLayer = Layer(pInst);
	tInfo.m_bySlot  = Slot(pInst);
	tInfo.m_byChanIndex = cServMsg.GetChnIndex();

	u8 byVmpMode = HDUCHN_MODE_ONE;
	u16 wIndex = sizeof(THduStartPlay)+sizeof(TDoublePayload)+sizeof(TDoublePayload)+sizeof(THDUExCfgInfo)+sizeof(TTransportAddr)+sizeof(u8);
	if (cServMsg.GetMsgBodyLen() > wIndex)
	{
		tInfo.m_bySubChan = *(u8 *)(cServMsg.GetMsgBody() + wIndex);
	}
	
	SendMsgToEqp(ev_hdu_play_ack, (u8*)&tInfo, sizeof(THduPlayInfo), pInst->GetInsID(), pInst->GetBrdNode());
	
}

void CHduHandler::EventPlayNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventPlayNack Layer:%d, Slot:%d, ChanIndex:%d.\n",
								Layer(pInst), Slot(pInst), cServMsg.GetChnIndex()));
	
	THduPlayInfo tInfo;
	tInfo.m_byLayer = Layer(pInst);
	tInfo.m_bySlot  = Slot(pInst);
	tInfo.m_byChanIndex = cServMsg.GetChnIndex();

	u8 byVmpMode = HDUCHN_MODE_ONE;
	u16 wIndex = sizeof(THduStartPlay)+sizeof(TDoublePayload)+sizeof(TDoublePayload)+sizeof(THDUExCfgInfo)+sizeof(TTransportAddr)+sizeof(u8);
	if (cServMsg.GetMsgBodyLen() > wIndex)
	{
		tInfo.m_bySubChan = *(u8 *)(cServMsg.GetMsgBody() + wIndex);
	}
	
	SendMsgToEqp(ev_hdu_play_nack, (u8*)&tInfo, sizeof(THduPlayInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CHduHandler::EventStopPlayAck(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	THduPlayInfo tPlayInfo;
	tPlayInfo.m_byLayer = Layer(pInst);
	tPlayInfo.m_bySlot  = Slot(pInst);
	tPlayInfo.m_byChanIndex = cServMsg.GetChnIndex();

	if (cServMsg.GetMsgBodyLen() == sizeof(TEqp) + sizeof(u8) + sizeof(u8))
	{
		tPlayInfo.m_bySubChan = *(u8 *)(cServMsg.GetMsgBody() + sizeof(TEqp));
	}
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventStopPlayAck Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d.\n",
							  tPlayInfo.m_byLayer, tPlayInfo.m_bySlot,
							  tPlayInfo.m_byChanIndex, tPlayInfo.m_bySubChan));
	
	SendMsgToEqp(ev_hdu_stop_play_ack, (u8*)&tPlayInfo, sizeof(THduPlayInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CHduHandler::EventStopPlayNack(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	THduPlayInfo tPlayInfo;
	tPlayInfo.m_byLayer = Layer(pInst);
	tPlayInfo.m_bySlot  = Slot(pInst);
	tPlayInfo.m_byChanIndex = cServMsg.GetChnIndex();

	if (cServMsg.GetMsgBodyLen() == sizeof(TEqp) + sizeof(u8) + sizeof(u8))
	{
		tPlayInfo.m_bySubChan = *(u8 *)(cServMsg.GetMsgBody() + sizeof(TEqp));
	}
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventStopPlayNack Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d.\n",
							  tPlayInfo.m_byLayer, tPlayInfo.m_bySlot,
							  tPlayInfo.m_byChanIndex, tPlayInfo.m_bySubChan));
	
	SendMsgToEqp(ev_hdu_stop_play_nack, (u8*)&tPlayInfo, sizeof(THduPlayInfo), pInst->GetInsID(), pInst->GetBrdNode());	
}

void CHduHandler::EventUpdateChanStatus(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	THduChnStatus tChanStatus;
	u8            bFirstNotifTmp;
	u8            byHduSubChnId;
	TP_SAFE_CAST(tChanStatus, cServMsg.GetMsgBody());
	TP_SAFE_CAST(bFirstNotifTmp, cServMsg.GetMsgBody()+sizeof(THduChnStatus)); // 暂时没用到
	TP_SAFE_CAST(byHduSubChnId, cServMsg.GetMsgBody()+sizeof(THduChnStatus)+sizeof(u8)); 

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventUpdateChanStatus InsID:%d, ChanIndex:%d, status:%d, byVol:%d, bMute:%d.\n",
							  pInst->GetInsID(), tChanStatus.GetChnIdx(), tChanStatus.GetStatus(), 
							  tChanStatus.GetVolume(), tChanStatus.GetIsMute()));

	THduChanStatus tInfo;
	tInfo.m_byStatus = tChanStatus.GetStatus();
	tInfo.m_byChanIndex = tChanStatus.GetChnIdx();
	tInfo.m_wEqpID = pInst->GetInsID();
	tInfo.m_bySubChan = byHduSubChnId;
	tInfo.m_tChanVol.m_byVol = tChanStatus.GetVolume();
	tInfo.m_tChanVol.m_bMute = tChanStatus.GetIsMute();

	SendMsgToEqp(ev_hdu_update_chan_status, (u8*)(&tInfo), sizeof(THduChanStatus), pInst->GetInsID(), pInst->GetBrdNode());

	return;
}

void CHduHandler::EventReqIFrame(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	MdlLowDtl(Ums_Mdl_Eqp, ("CHduHandler::EventReqIFrame InsID:%d, ChanIndex:%d.\n",
							  pInst->GetInsID(), cServMsg.GetChnIndex()));

	THduIFrameInfo tInfo;
	tInfo.m_wEqpID = pInst->GetInsID();
	tInfo.m_byChanIndex = cServMsg.GetChnIndex();
	if (cServMsg.GetMsgBodyLen() >= sizeof(u8))
	{
		tInfo.m_bySubChan = *((u8*)cServMsg.GetMsgBody());
	}

	SendMsgToEqp(ev_hdu_req_iframe, (u8*)(&tInfo), sizeof(THduIFrameInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CHduHandler::EventUpdateNotify(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	THduUpdateRes tRes;
	
	u8 byPos = 0;
	memcpy(&byPos, cServMsg.GetMsgBody(), sizeof(u8));
	tRes.m_byLayer = byPos / HDU_MAX_SLOT;
	tRes.m_bySlot  = byPos & HDU_MAX_SLOT;
	
	if (tRes.m_byLayer != Layer(pInst) ||
		tRes.m_bySlot  != Slot(pInst))
	{
		MdlError(Ums_Mdl_Eqp, ("CHduHandler::EventUpdateNotify invalid index. InsLayer:%d, InsSlot:%d, Layer:%d, Slot:%d.\n",
								Layer(pInst), Slot(pInst), tRes.m_byLayer, tRes.m_bySlot));
		return ;
	}
	
	memcpy(&(tRes.m_byFileNum), cServMsg.GetMsgBody()+sizeof(u8), sizeof(u8));
	
	for (u8 byIndex = 0; byIndex < tRes.m_byFileNum; ++byIndex)
	{
		memcpy(&(tRes.m_abyRes[byIndex]), cServMsg.GetMsgBody()+sizeof(u8)*(2+byIndex), sizeof(u8));
	}
	
	s8* pFileMsg = (s8*)(cServMsg.GetMsgBody()+sizeof(u8)*(2+tRes.m_byFileNum));
	u8 byFileLen = 0;
	u16 wOffSet = 0;
	for (u8 byTempNum = 0; byTempNum < tRes.m_byFileNum; ++byTempNum)
	{
		byFileLen = *pFileMsg;
		if (byFileLen+wOffSet > cServMsg.GetMsgBodyLen()-2)
		{
			MdlError(Ums_Mdl_Eqp, ("[OnHduUpdateNotify] Invalid Msgbody.\n"));
			break;
		}
		
		tRes.m_atFileInfo[byTempNum].m_byFileLength = byFileLen;
		memcpy(tRes.m_atFileInfo[byTempNum].m_achFileName, pFileMsg+sizeof(u8), byFileLen);
		wOffSet += sizeof(u8)+byFileLen;
		pFileMsg += wOffSet;
	}
	
	SendMsgToEqp(ev_hdu_update_res, (u8*)&tRes, sizeof(THduUpdateRes), pInst->GetInsID(), pInst->GetBrdNode());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventUpdateNotify Layer:%d, Slot:%d, FileNum:%d.\n",
						      tRes.m_byLayer, tRes.m_bySlot, tRes.m_byFileNum));
}

void CHduHandler::EventUpdateStatus(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	TPeriEqpStatus tStatus;
	TP_SAFE_CAST(tStatus, cServMsg.GetMsgBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventUpdateStatus InsID:%d, OnLine:%d.\n",
							  pInst->GetInsID(), tStatus.m_byOnline));

	THduUpdateInfo tInfo;
	tInfo.m_bOnLine = tStatus.m_byOnline;
	tInfo.m_wEqpID = pInst->GetInsID();
	tInfo.m_tName.SetAlias(tStatus.GetAlias());

	SendMsgToEqp(ev_hdu_updata_status, (u8*)&tInfo, sizeof(THduUpdateInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

BOOL32 CHduHandler::MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u16 wEvent = ptMsg->GetEvent();

	if (NULL == pInst)
	{
		MdlError(Ums_Mdl_Eqp, ("CHduHandler::MsgFromEqpHandler Instance is NULL.\n"));
		return FALSE;
	}
	
	BOOL32 bProc = TRUE;
	switch (wEvent)
	{
	case ev_hdu_req_ack:		
		{
			EventRegAck(ptMsg, pInst);
		}
		break;

	case ev_hdu_req_nack:		
		{
			EventRegNack(ptMsg, pInst);
		}
		break;

	case ev_hdu_play_req:		
		{
			EventPlayReq(ptMsg, pInst);
		}
		break;

	case ev_hdu_stop_play_req:	
		{
			EventStopPlayReq(ptMsg, pInst);
		}
		break;
		
	case ev_hdu_update_req:		
		{
			EventUpdateBrd(ptMsg, pInst);
		}
		break;
		
	case ev_hdu_notify_channel:	
		{
			EventNotifyChan(ptMsg, pInst);
		}
		break;
		
	case ev_hdu_del:
		{
			EventDelBrd(ptMsg, pInst);
		}
		break;

	case ev_hdu_chan_del:
		{
			EventDelChan(ptMsg, pInst);
		}
		break;

	case ev_hdu_set_vol:
		{
			EventSetVol(ptMsg, pInst);
		}
		break;
	case ev_hdu_change_chan_mode:
		{
			EventChangeHduChanMode(ptMsg, pInst);
		}
		break;

	case ev_hdu_media_key_nty:
		{
			EventMediaKeyNty(ptMsg, pInst);
		}
		break;

	default:
		{
			bProc = FALSE;
		}
		break;
	}

	return bProc;
	
}

void CHduHandler::EventRegAck(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	TUmsRSParam		tUmsRsParam;
	THduRegCfgAck	tRegCfg;
	TP_SAFE_CAST(tUmsRsParam, ptMsg->GetBody());
	TP_SAFE_CAST(tRegCfg, ptMsg->GetBody()+sizeof(TUmsRSParam));

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventRegAck InsID:%d, StartPort:%d.\n",
							  pInst->GetInsID(), tRegCfg.m_wStartPort));
	
	TPrsTimeSpan tTimeSpan;
	TPeriEqpRegAck tRegAck;
	TEqpHduCfgInfo tHduCfg;
	
	//转换为网络序传输
	tTimeSpan.m_wFirstTimeSpan	= htons(tUmsRsParam.m_wFirstTimeSpan);
	tTimeSpan.m_wSecondTimeSpan = htons(tUmsRsParam.m_wSecondTimeSpan);
	tTimeSpan.m_wThirdTimeSpan	= htons(tUmsRsParam.m_wThirdTimeSpan);
	tTimeSpan.m_wRejectTimeSpan = htons(tUmsRsParam.m_wRejectTimeSpan);
	
	
	tHduCfg.SetEqpStartPort(tRegCfg.m_wStartPort);
	tHduCfg.SetAlias(tRegCfg.m_szAlias);
	
	THduChnlModePort tHduChnModePort;
	for (u8 byIndex = 0; byIndex < MAXNUM_HDU_CHANNEL; ++byIndex)
	{
		tHduChnModePort.SetZoomRate(tRegCfg.m_atChanInfo[byIndex].GetZoomRate());
		tHduChnModePort.SetOutPortType(tRegCfg.m_atChanInfo[byIndex].GetOutType());
		tHduChnModePort.SetOutModeType(tRegCfg.m_atChanInfo[byIndex].GetOutMode());
		tHduChnModePort.SetScalingMode(tRegCfg.m_atChanInfo[byIndex].GetShowMode());
		
		tHduCfg.SetHduChnlModePort(byIndex, tHduChnModePort);

		MdlLowHint(Ums_Mdl_Eqp, ("EventRegAck PortType:%d, OutMode:%d, ShowMode:%d, ZoomRate:%d.\n",
								  tHduChnModePort.GetOutPortType(), tHduChnModePort.GetOutModeType(),
								  tHduChnModePort.GetScalingMode(), tHduChnModePort.GetZoomRate()));
	}
	
	CServMsg cMsg;
	cMsg.SetMsgBody((u8*)(&tRegAck), sizeof(TPeriEqpRegAck));
	cMsg.CatMsgBody((u8*)(&tTimeSpan), sizeof(TPrsTimeSpan));
	cMsg.CatMsgBody((u8*)(&tHduCfg), sizeof(TEqpHduCfgInfo));
	
	OspPost(pInst->GetBrdIID(), UMS_HDU_REG_ACK, cMsg.GetServMsg(), cMsg.GetServMsgLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));

	u8 byPlayPolicy = (u8)CUmsConfigEx::GetInstance()->GetTvWallLastPic();

	OspPost(pInst->GetBrdIID(), UMS_HDU_CHANGEPLAYPOLICY_NOTIF, &byPlayPolicy, sizeof(u8), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CHduHandler::EventRegNack(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventRegNack InsID:%d.\n",
							  pInst->GetInsID()));

	OspPost(pInst->GetBrdIID(), UMS_HDU_REG_NACK, ptMsg->GetBody(), ptMsg->GetBodyLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));

	OspDisconnectTcpNode(pInst->GetBrdNode());
}

void CHduHandler::EventPlayReq(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	THduPlayInfo tinfo;
	TAddTvMonitorAck tAck;
	TP_SAFE_CAST(tinfo, ptMsg->GetBody());
	TP_SAFE_CAST(tAck, ptMsg->GetBody()+sizeof(THduPlayInfo));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventPlayReq Layer:%d, Slot:%d, ChanIndex:%d, SubChan:%d, Vmp:%d.\n", 
						      tinfo.m_byLayer, tinfo.m_bySlot, tinfo.m_byChanIndex, tinfo.m_bySubChan, tinfo.m_bVmp));
	
	THduStartPlay thduStartPly;
	TDoublePayload tVidPayLoad;
	TDoublePayload tAudPayLoad;
	THDUExCfgInfo  tHduCfg;
	TTransportAddr	tAudTransPort;
	u8 byAudChanNum = 0;
	thduStartPly.SetMode(HDU_OUTPUTMODE_BOTH);
	thduStartPly.SetVidRtcpBackAddr(ntohl(tAck.m_tVidAddr.m_tBackRtcpAddr.m_dwIP), tAck.m_tVidAddr.m_tBackRtcpAddr.m_wPort);

	thduStartPly.SetIsNeedByPrs(TRUE);

	TMediaEncrypt tEncrypt;
	if (emTPEncryptTypeAES == tAck.m_tEncrypt.m_emEncryptModel)
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_AES);
		tEncrypt.SetEncryptKey((u8*)tAck.m_tEncrypt.m_achEncKey, (s32)tAck.m_tEncrypt.m_byKeyLen);
	}
	else if (emTPEncryptTypeDES == tAck.m_tEncrypt.m_emEncryptModel)
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_DES);
		tEncrypt.SetEncryptKey((u8*)tAck.m_tEncrypt.m_achEncKey, (s32)tAck.m_tEncrypt.m_byKeyLen);
	}else if (tAck.m_tEncrypt.IsQt())
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_QT);
		tEncrypt.SetEncryptKey(NULL, 0);
	}
	else
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_NONE);
		tEncrypt.SetEncryptKey(NULL, 0);
	}
	thduStartPly.SetVideoEncrypt(tEncrypt);

	tAudTransPort.SetNetSeqIpAddr(tAck.m_tAudAddr.m_tBackRtcpAddr.m_dwIP);
	tAudTransPort.SetPort(tAck.m_tAudAddr.m_tBackRtcpAddr.m_wPort);
	
	tVidPayLoad.SetActivePayload(tAck.m_byVidPayload);
	tVidPayLoad.SetRealPayLoad(tAck.m_byVidPayload);
	
	tAudPayLoad.SetActivePayload(tAck.m_byAudPayload);
	tAudPayLoad.SetRealPayLoad(tAck.m_byAudPayload);
	tHduCfg.m_byIdleChlShowMode = (u8)CUmsConfigEx::GetInstance()->GetTvWallLastPic();

	u8 byVmpMode = 0;
	if (tinfo.m_bVmp)
	{
		byVmpMode = HDUCHN_MODE_FOUR;
		byAudChanNum = 0;
	}
	else
	{
		byVmpMode = HDUCHN_MODE_ONE;
		byAudChanNum = 1;
	}
	
	CServMsg cServMsg;
	cServMsg.SetChnIndex(tinfo.m_byChanIndex);
	cServMsg.SetMsgBody( (u8*)&thduStartPly, sizeof(THduStartPlay) );
	cServMsg.CatMsgBody( (u8*)&tVidPayLoad, sizeof(TDoublePayload) );
	cServMsg.CatMsgBody( (u8*)&tAudPayLoad, sizeof(TDoublePayload) );
	cServMsg.CatMsgBody( (u8*)&tHduCfg, sizeof(THDUExCfgInfo) );
	cServMsg.CatMsgBody( (u8*)&tAudTransPort, sizeof(TTransportAddr) );
	cServMsg.CatMsgBody( (u8*)&byAudChanNum, sizeof(u8));
	cServMsg.CatMsgBody( (u8*)&(tinfo.m_bySubChan), sizeof(u8));
	cServMsg.CatMsgBody( (u8*)&byVmpMode, sizeof(u8));
	
	OspPost(pInst->GetBrdIID(), UMS_HDU_START_PLAY_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CHduHandler::EventStopPlayReq(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	THduPlayInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventStopPlayReq Layer:%d, Slot:%d, ChanIndex:%d.\n", 
						      tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex));
	CServMsg cServMsg;
	if (tInfo.m_bVmp)
	{
		TEqp tEqp;
		u8 byMode = HDUCHN_MODE_FOUR;
		cServMsg.SetMsgBody((u8*)(&tEqp), sizeof(TEqp));
		cServMsg.CatMsgBody(&(tInfo.m_bySubChan), sizeof(u8));
		cServMsg.CatMsgBody(&byMode, sizeof(u8));
	}
	cServMsg.SetChnIndex(tInfo.m_byChanIndex);
	
	OspPost(pInst->GetBrdIID(), UMS_HDU_STOP_PLAY_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CHduHandler::EventUpdateBrd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	TTPBrdUpGrade tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventUpdateBrd Layer:%d, Slot:%d, FileName:%s.\n",
							  tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_szFileName));

	u8 byIndex = tInfo.m_byLayer*HDU_MAX_SLOT+tInfo.m_bySlot;
	u8 byFileNum = 1;

	s8 szFile[256] = {0};
	memcpy(szFile, "/ramdisk/", sizeof("/ramdisk/"));
	strcat(szFile, tInfo.m_szFileName);
	u8 byFileLen = strlen(szFile);

	CServMsg cMsg;
	cMsg.SetMsgBody((u8*)(&byIndex), sizeof(u8));
	cMsg.CatMsgBody((u8*)(&byFileNum), sizeof(u8));
	cMsg.CatMsgBody((u8*)(&byFileLen), sizeof(u8));
	cMsg.CatMsgBody((u8*)szFile, TP_UPGRADE_FILENAME_LENGTH);

	OspPost(pInst->GetBrdIID(), UMS_MPC_BOARD_UPDATE_SOFTWARE_CMD, cMsg.GetServMsg(), cMsg.GetServMsgLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CHduHandler::EventNotifyChan(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	THduInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventNotifyChan InsID:%d.\n",
							  pInst->GetInsID()));

	CServMsg cMsg;
	THduChnlModePort tHduChanA, tHduChanB;
	THduChanInfo* ptChanInfo = NULL;

	ptChanInfo = &(tInfo.m_atChanInfo[0]);
	tHduChanA.SetOutPortType(ptChanInfo->GetOutType());
	tHduChanA.SetOutModeType(ptChanInfo->GetOutMode());
	tHduChanA.SetZoomRate(ptChanInfo->GetZoomRate());
	tHduChanA.SetScalingMode(ptChanInfo->GetShowMode());
	cMsg.SetMsgBody((u8*)(&tHduChanA), sizeof(THduChnlModePort));

	 
// 	 	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventNotifyChan ChanIndex:%d, PortType:%d, ModeType:%d, ZoomRate:%d, ScalingMode:%d.\n",
// 	 							  0, tHduChan.GetOutPortType(), tHduChan.GetOutModeType(),
// 							  tHduChan.GetZoomRate(), tHduChan.GetScalingMode()));

	ptChanInfo = &(tInfo.m_atChanInfo[1]);
	tHduChanB.SetOutPortType(ptChanInfo->GetOutType());
	tHduChanB.SetOutModeType(ptChanInfo->GetOutMode());
	tHduChanB.SetZoomRate(ptChanInfo->GetZoomRate());
	tHduChanB.SetScalingMode(ptChanInfo->GetShowMode());
	cMsg.CatMsgBody((u8*)(&tHduChanB), sizeof(THduChnlModePort));

// 	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventNotifyChan ChanIndex:%d, PortType:%d, ModeType:%d, ZoomRate:%d, ScalingMode:%d.\n",
// 		1, tHduChan.GetOutPortType(), tHduChan.GetOutModeType(),
// 							  tHduChan.GetZoomRate(), tHduChan.GetScalingMode()));


	
	OspPost(pInst->GetBrdIID(), UMS_HDU_CHANGEMODEPORT_NOTIF, cMsg.GetMsgBody(), cMsg.GetMsgBodyLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CHduHandler::EventDelBrd(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u8 byLayer = 0;
	u8 bySlot  = 0;
	TP_SAFE_CAST(byLayer, ptMsg->GetBody());
	TP_SAFE_CAST(bySlot, ptMsg->GetBody()+sizeof(u8));

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventDelBrd Layer:%d, Slot:%d.\n",
							  byLayer, bySlot));

	OspDisconnectTcpNode(pInst->GetBrdNode());
}

void CHduHandler::EventDelChan(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	TTPBrdPos tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventDelChan Layer:%d, Slot:%d.\n",
							  tInfo.m_byBrdLayer, tInfo.m_byBrdSlot));

	OspDisconnectTcpNode(pInst->GetBrdNode());
}

void CHduHandler::EventSetVol(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	THduVolInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventSetVol Layer:%d, Slot:%d, Chan:%d, Vol:%d, Mute:%d.\n",
							  tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanlIdx, tInfo.m_byVolume, tInfo.m_byIsMute));
	THduVolumeInfo tVolInfo;
	tVolInfo.SetChnlIdx(tInfo.m_byChanlIdx);
	tVolInfo.SetVolume(tInfo.m_byVolume);
//	tVolInfo.SetIsMute(1);
	tVolInfo.SetIsMute(tInfo.m_byIsMute);

	CServMsg cServMsg;
	cServMsg.SetChnIndex(tInfo.m_byChanlIdx);
	cServMsg.SetMsgBody((u8*)&tVolInfo, sizeof(tVolInfo));

	OspPost(pInst->GetBrdIID(), UMS_HDU_CHANGEVOLUME_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

u8 CHduHandler::Layer(CTPMcuBrdSsn* pInst)
{
	return (pInst->GetInsID() - EQP_ID_HDU_BEG) / HDU_MAX_SLOT;
}

u8 CHduHandler::Slot(CTPMcuBrdSsn* pInst)
{
	return (pInst->GetInsID() - EQP_ID_HDU_BEG) % HDU_MAX_SLOT;
}

void CHduHandler::EventChangeHduChanMode( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	THduChanModeInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventChangeHduVmpMode Layer:%d, Slot:%d, ChanIndex:%d, ChanMode:%d.\n", 
		tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_byChanIndex, tInfo.m_byChanMode));
	
	CServMsg cServMsg;
	cServMsg.SetMsgBody(&tInfo.m_byChanMode, sizeof(u8));
	cServMsg.SetChnIndex(tInfo.m_byChanIndex);
	
	OspPost(pInst->GetBrdIID(), UMS_HDU_CHGHDUVMPMODE_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
			pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));

	return;
}

void CHduHandler::EventChangeHduChanModeAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	THduChanModeInfo tVmpModeInfo;
	tVmpModeInfo.m_byLayer = Layer(pInst);
	tVmpModeInfo.m_bySlot  = Slot(pInst);
	tVmpModeInfo.m_byChanIndex = cServMsg.GetChnIndex();
	tVmpModeInfo.m_byChanMode = *(u8*)(cServMsg.GetMsgBody());

	EmTpHduChangeChanModeRes emRes = em_hdu_change_mode_success;

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventChangeHduVmpModeAck Layer:%d, Slot:%d, ChanIndex:%d, byAckChanMode:%d, emRes:%d.\n",
		tVmpModeInfo.m_byLayer, tVmpModeInfo.m_bySlot,
		tVmpModeInfo.m_byChanIndex, tVmpModeInfo.m_byChanMode, emRes));

	u8 abySndBuf[sizeof(THduChanModeInfo)+sizeof(EmTpHduChangeChanModeRes)];
	memcpy(abySndBuf, &tVmpModeInfo, sizeof(THduChanModeInfo));
	memcpy(abySndBuf+sizeof(THduChanModeInfo), &emRes, sizeof(emRes));


	SendMsgToEqp(ev_hdu_change_chan_mode_res, abySndBuf, sizeof(abySndBuf), pInst->GetInsID(), pInst->GetBrdNode());

	return;
}

void CHduHandler::EventChangeHduChanModeNack( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	THduChanModeInfo tVmpModeInfo;
	tVmpModeInfo.m_byLayer = Layer(pInst);
	tVmpModeInfo.m_bySlot  = Slot(pInst);
	tVmpModeInfo.m_byChanIndex = cServMsg.GetChnIndex();
	tVmpModeInfo.m_byChanMode = *(u8*)(cServMsg.GetMsgBody());

	EmTpHduChangeChanModeRes emRes = em_hdu_change_mode_error_fromhdu;

	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventChangeHduVmpModeNack Layer:%d, Slot:%d, ChanIndex:%d, byChanVmpMode:%d, emRes:%d.\n",
		tVmpModeInfo.m_byLayer, tVmpModeInfo.m_bySlot,
		tVmpModeInfo.m_byChanIndex, tVmpModeInfo.m_byChanMode, emRes));

	u8 abySndBuf[sizeof(THduChanModeInfo)+sizeof(EmTpHduChangeChanModeRes)];
	memcpy(abySndBuf, &tVmpModeInfo, sizeof(THduChanModeInfo));
	memcpy(abySndBuf+sizeof(THduChanModeInfo), &emRes, sizeof(emRes));	
	
	SendMsgToEqp(ev_hdu_change_chan_mode_res, abySndBuf, sizeof(abySndBuf), pInst->GetInsID(), pInst->GetBrdNode());
	
	return;	
}


void CHduHandler::EventMediaKeyNty(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	THduPlayInfo tHduInfo;
	TTPQTMediaKeyInfo tKeyInfo;
	memcpy(&tHduInfo, ptMsg->GetBody(), sizeof(tHduInfo));
	memcpy(&tKeyInfo, ptMsg->GetBody() + sizeof(tHduInfo), sizeof(tKeyInfo));
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler:: EventMediaKeyNty dwHandle->%d, index->%d, flag->%d, keylen->%d, emKeyFrequency->%d\n",
		tKeyInfo.m_dwHandle, tKeyInfo.m_wIndex, tKeyInfo.m_dwQtFlag, tKeyInfo.m_dwKeyLen, tKeyInfo.m_emKeyFrequency));
	
	TQTMediaKeyInfo tQTKeyInfo;
	tQTKeyInfo.SetChnlNo(tHduInfo.m_byChanIndex);
	tQTKeyInfo.SetHandle(tKeyInfo.m_dwHandle);
	tQTKeyInfo.SetIndex(tKeyInfo.m_wIndex);
	tQTKeyInfo.SetKeyFrequency(tKeyInfo.m_emKeyFrequency);
	tQTKeyInfo.SetKeyLen(tKeyInfo.m_dwKeyLen);
	tQTKeyInfo.SetQtFlag(tKeyInfo.m_dwQtFlag);
	
	memcpy(tQTKeyInfo.m_szAlias, tKeyInfo.m_szAlias, TP_MAX_ALIAS_LEN);
	
	memcpy(tQTKeyInfo.m_szMediaKey1, tKeyInfo.m_szMediaKey, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey2, tKeyInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey3, tKeyInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey4, tKeyInfo.m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	
	CServMsg cMsg;
	cMsg.SetMsgBody( (u8*)&tQTKeyInfo, sizeof(tQTKeyInfo) );
	OspPost(pInst->GetBrdIID(), UMS_HDU_MEDIAKEY_NTY, cMsg.GetServMsg(), cMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CHduHandler::EventMediaKeyNty BrdID:%d, MsgLen:%d.\n",
		pInst->GetBrdIID(), cMsg.GetMsgBodyLen()));
}
