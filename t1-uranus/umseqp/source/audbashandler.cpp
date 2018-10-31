#include "audbashandler.h"
#include "umsobject.h"
#include "tplog.h"
#include "mcudef.h"
#include "mcuinstdef.h"
#include "mcuboardmgr.h"
#include "innereventumsaudbas.h"
#include "umsapi.h"
#include "codecwrapperdef_hd.h"
#include "hdudef.h"

CAudBasHandler::CAudBasHandler()
{

}

CAudBasHandler::~CAudBasHandler()
{

}

BOOL32 CAudBasHandler::MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u16 wEvent = ptMsg->event;
	BOOL32 bProc = TRUE;

	if (NULL == pInst)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasHandler::MsgFromServiceHandler Instance is NULL.\n"));
		return FALSE;
	}

	switch (wEvent)
	{
	case OSP_DISCONNECT:
		{
			EventDisconnect(ptMsg, pInst);
		}
		break;

	case UMS_BAS_MCU_REG_REQ:				
		{
			EventReg(ptMsg, pInst);
		}
		break;

	case UMS_BAS_MCU_BASSTATUS_NOTIF:				
		{
			EventEqpStatNtfy(ptMsg, pInst);
		}
		break;

	case UMS_AUDBAS_MCU_CHNNLSTATUS_NOTIF:				
		{
			EventChnlStatNtfy(ptMsg, pInst);
		}
		break;	

	case UMS_BAS_MCU_STARTADAPT_ACK:				
		{
			EventStartAdapterAck(ptMsg, pInst);
		}
		break;
		
	case UMS_BAS_MCU_STARTADAPT_NACK:				
		{
			EventStartAdapterNAck(ptMsg, pInst);
		}
		break;

	case UMS_BAS_MCU_CHANGEAUDPARAM_ACK:				
		{
			EventChangeAdapterAck(ptMsg, pInst);
		}
		break;
		
	case UMS_BAS_MCU_CHANGEAUDPARAM_NACK:				
		{
			EventChangeAdapterNAck(ptMsg, pInst);
		}
		break;

	case UMS_BAS_MCU_STOPADAPT_ACK:				
		{
			EventStopAdapterAck(ptMsg, pInst);
		}
		break;

	case UMS_BAS_MCU_STOPADAPT_NACK:				
		{
			EventStopAdapterNAck(ptMsg, pInst);
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

void CAudBasHandler::EventDisconnect(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u32 dwNode = pInst->GetBrdNode();

//	SendMsgToEqp(OSP_DISCONNECT, (u8*)&dwNode, sizeof(u32), pInst->GetInsID(), pInst->GetBrdNode());
}

BOOL32 CAudBasHandler::MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u16 wEvent = ptMsg->GetEvent();

	if (NULL == pInst)
	{
		MdlError(Ums_Mdl_Eqp, ("CApu2Handler::MsgFromEqpHandler Instance is NULL.\n"));
		return FALSE;
	}

	BOOL32 bProc = TRUE;
	switch (wEvent)
	{
	case ev_AudBasEqpReg_Ack:		
		{
			EventRegAck(ptMsg, pInst);
		}
		break;

	case ev_AudBasEqpReg_NAck:		
		{
			EventRegNack(ptMsg, pInst);
		}
		break;

	case ev_AudBasChangeAdapter_Req:
	case ev_AudBasStartAdapter_Req:		
		{
			EventStartAdapter(ptMsg, pInst);
		}
		break;

	case ev_AudBasStopAdapter_Req:		
		{
			EventStopAdapter(ptMsg, pInst);
		}
		break;

	case ev_AudBasSetSync_Req:
		{
			EventSetSync(ptMsg, pInst);
		}
		break;

	case ev_AudBas_set_mediakey_ntfy:
		{
			EventSetMediaKey(ptMsg, pInst);
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

void CAudBasHandler::EventReg( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpRegReq tEqpReg;
	TP_SAFE_CAST(tEqpReg, cServMsg.GetMsgBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventReg instID:%d, EqpID:%d, IP:"TPIPFORMAT", StartPort:%d, ChanNum:%d, Alias:%s, Ver:%d, HD:%d.\n",
		pInst->GetInsID(), tEqpReg.GetEqpId(), Tpu32ToIP(tEqpReg.GetPeriEqpIpAddr()), tEqpReg.GetStartPort(),
		tEqpReg.GetChnnlNum(), tEqpReg.GetEqpAlias(), tEqpReg.GetVersion(), tEqpReg.IsHDEqp()));
	
// 	//预防修改配置后断链和注册请求冲突
// 	if (INVALID_NODE != pInst->GetBrdNode())
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("CAudBasHandler::EventReg BrdNode is valid. Node:%d, Inst:%d, EqpID:%d\n", pInst->GetBrdNode(), pInst->GetInsID(), tEqpReg.GetEqpId()));
// 		OspPost(ptMsg->srcid, UMS_MCU_BAS_REG_NACK, NULL, 0, ptMsg->srcnode);
//         ::OspDisconnectTcpNode(ptMsg->srcnode);
// 		
// 		return ;
// 	}
	
	if (tEqpReg.GetEqpId() != pInst->GetInsID())
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasHandler::EventReg. EqpID is Invalid!\n"));
		
		OspPost(ptMsg->srcid, UMS_MCU_BAS_REG_NACK, NULL, 0, ptMsg->srcnode);
        ::OspDisconnectTcpNode(ptMsg->srcnode);
		
		return ;
	}

	pInst->SetBrdNode(ptMsg->srcnode);
	pInst->SetBrdIID(ptMsg->srcid);

	OspNodeDiscCBRegQ(ptMsg->srcnode, pInst->GetAppID(), pInst->GetInsID());

	TTPBasReg tInfo;
	tInfo.m_dwEqpIPAddr = tEqpReg.GetPeriEqpIpAddr();
	tInfo.m_byEqpID = tEqpReg.GetEqpId();
	tInfo.m_dwEqpPort = tEqpReg.GetStartPort();
	tInfo.m_dwEqpVer = tEqpReg.GetVersion();
	
	SendMsgToEqp(ev_AudBasEqpReg_Req, (u8*)(&tInfo), sizeof(TTPBasReg), pInst->GetInsID(), pInst->GetBrdNode());
	
}

void CAudBasHandler::EventRegAck( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TTPBasRegAck tAck;
	TP_SAFE_CAST(tAck, ptMsg->GetBody());
	TUmsRSParam tRsParam;
	TP_SAFE_CAST(tRsParam, ptMsg->GetBody() + sizeof(tAck));

	TPrsTimeSpan tPrsTimeSpan;
	tPrsTimeSpan.m_wFirstTimeSpan = htons(tRsParam.m_wFirstTimeSpan);
	tPrsTimeSpan.m_wSecondTimeSpan = htons(tRsParam.m_wSecondTimeSpan);
	tPrsTimeSpan.m_wThirdTimeSpan = htons(tRsParam.m_wThirdTimeSpan);
	tPrsTimeSpan.m_wRejectTimeSpan = htons(tRsParam.m_wRejectTimeSpan);

	TPeriEqpRegAck tPeriAck;
	tPeriAck.SetMcuIpAddr(ntohl(tAck.m_dwIpAddr));
	tPeriAck.SetMcuStartPort(tAck.m_wStartPort);
	tPeriAck.SetAnotherMpcIp(0);
	
	u16 wMTUSize = htons(0);			//默认0，mpu2不使用

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&tPeriAck, sizeof(tPeriAck));
	cServMsg.CatMsgBody((u8 *)&tPrsTimeSpan, sizeof(tPrsTimeSpan));
	cServMsg.CatMsgBody((u8 *)&wMTUSize, sizeof(u16));

	OspPost(pInst->GetBrdIID(), UMS_MCU_BAS_REG_ACK, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventRegAck. InsID:%d, UmsIp:"TPIPFORMAT", UmsPort:%d\n", 
		pInst->GetInsID(), Tpu32ToIP(tPeriAck.GetMcuIpAddr()), 
		tPeriAck.GetMcuStartPort()));
}

void CAudBasHandler::EventRegNack( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventRegNack Instance ID:%d.\n", pInst->GetInsID()));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_BAS_REG_NACK, ptMsg->GetBody(), ptMsg->GetBodyLen(), 
				pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	OspDisconnectTcpNode(pInst->GetBrdNode());
	
	pInst->SetBrdNode(INVALID_NODE);
}

void CAudBasHandler::EventEqpStatNtfy( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpStatus tStatus;
	memset( &tStatus,0,sizeof(TPeriEqpStatus) );
	const u16 wMsgBodyLen = cServMsg.GetMsgBodyLen();
    memcpy(&tStatus, cServMsg.GetMsgBody(), min(sizeof(TPeriEqpStatus), wMsgBodyLen));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventEqpStatNtfy. EqpID:%d, InsID:%d, EqpAlias:%s, EqpType:%d, Online:%d\n", 
		tStatus.GetEqpId(), pInst->GetInsID(), tStatus.GetAlias(), tStatus.m_tStatus.tAudBas.GetEqpType(), tStatus.m_byOnline));
	
	TTPBasStatNtfy tStatNtfy;
	tStatNtfy.m_byEqpID = tStatus.GetEqpId();
	tStatNtfy.SetAlias(tStatus.GetAlias());
	
	SendMsgToEqp(ev_AudBasEqpStat_Ntfy, (u8*)&tStatNtfy, sizeof(tStatNtfy), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventChnlStatNtfy( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byEqpType;
	TP_SAFE_CAST(byEqpType, cServMsg.GetMsgBody());
	TAudBasChnStatus tStatus;
	TP_SAFE_CAST(tStatus, cServMsg.GetMsgBody() + sizeof(u8));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventEqpStatNtfy. EqpID:%d, InsID:%d, EqpType:%d, ChnIdx:%d, Stat:%d(0:idle 1:ready 2:run)\n", 
		tStatus.GetEqpId(), pInst->GetInsID(), tStatus.GetEqp().GetEqpType(), tStatus.GetChnIdx(), tStatus.GetStatus()));
	
	TTPBasChnStatNtfy tStatNtfy;
	tStatNtfy.m_byEqpID = tStatus.GetEqpId();
	tStatNtfy.m_byChnIndx = tStatus.GetChnIdx();
	tStatNtfy.m_byStat = tStatus.GetStatus();
	
	SendMsgToEqp(ev_AudBasChnlStat_Ntfy, (u8*)&tStatNtfy, sizeof(tStatNtfy), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventStartAdapter( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TStartAudAdapter tTPStart;
	TP_SAFE_CAST(tTPStart, ptMsg->GetBody());

	TAudAdaptParam atEncParam[AUD_BAS_MAX_OUT_CHNL_NUM];
	TMediaEncrypt tEncrypt;
	TAudioCapInfo tDecParam;
	u8	byDecSampleRate;

	// 加密参数
	if (emTPEncryptTypeAES == tTPStart.m_tEncrypt.m_emEncryptModel)
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_AES);
		tEncrypt.SetEncryptKey((u8*)tTPStart.m_tEncrypt.m_achEncKey, (s32)tTPStart.m_tEncrypt.m_byKeyLen);
	}
	else if (emTPEncryptTypeDES == tTPStart.m_tEncrypt.m_emEncryptModel)
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_DES);
		tEncrypt.SetEncryptKey((u8*)tTPStart.m_tEncrypt.m_achEncKey, (s32)tTPStart.m_tEncrypt.m_byKeyLen);
	}
	else if ( tTPStart.m_tEncrypt.IsQt() )
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_QT);
		tEncrypt.SetEncryptKey(NULL, 0);
	}
	else
	{
		tEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_NONE);
		tEncrypt.SetEncryptKey(NULL, 0);
	}

	for( u16 wIndex = 0; wIndex < AUD_BAS_MAX_OUT_CHNL_NUM; wIndex ++ )
	{
		atEncParam[wIndex].Clear();
		if( tTPStart.m_atAudEnc[wIndex].m_emFormat == emTPAEnd )
		{
			continue;
		}
		atEncParam[wIndex].SetAudCodeType(CTpTypeAdpt::GetAudPayloadValue(tTPStart.m_atAudEnc[wIndex].m_emFormat));
		atEncParam[wIndex].SetAudActiveType(CTpTypeAdpt::GetAudPayloadValue(tTPStart.m_atAudEnc[wIndex].m_emFormat));
		atEncParam[wIndex].SetIsNeedByPrs(TRUE);
		atEncParam[wIndex].SetTrackNum(1);//单声道
	}

	tDecParam.SetAudioMediaType(CTpTypeAdpt::GetAudPayloadValue(tTPStart.m_tAudDec.m_emFormat));
	tDecParam.SetActivePayLoad(tTPStart.m_tAudDec.m_byReserve1);
	tDecParam.SetAudioTrackNum(1);//单声道

	byDecSampleRate = AAC_SAMPLE_FRQ_32; //tTPStart.m_tAudDec.m_emPASampleFreq;

	CServMsg cServMsg;

	cServMsg.SetChnIndex(tTPStart.m_byChnlIndx);

	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)atEncParam, sizeof(atEncParam));
	cServMsg.CatMsgBody((u8 *)&tEncrypt, sizeof(tEncrypt));
	cServMsg.CatMsgBody((u8 *)&tDecParam, sizeof(tDecParam));
	cServMsg.CatMsgBody((u8 *)&byDecSampleRate, sizeof(byDecSampleRate));

	u16 wEventID = UMS_MCU_BAS_STARTADAPT_REQ;
	if ( ptMsg->GetEvent() == ev_AudBasChangeAdapter_Req )
	{
		wEventID = UMS_MCU_BAS_CHANGEAUDPARAM_REQ;
	}
	
	OspPost(pInst->GetBrdIID(), wEventID, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventStartAdapter. InsID:%d, EqpID:%d, chnlindx:%d\n", 
							pInst->GetInsID(), tTPStart.m_byEqpID, tTPStart.m_byChnlIndx));

	return ;
}

void CAudBasHandler::EventStartAdapterAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventStartAdapterAck. InsID:%d, chnlindx:%d\n", pInst->GetInsID(), cServMsg.GetChnIndex()));

	TTPBasRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)pInst->GetInsID();
	tRetInfo.m_byChnID = cServMsg.GetChnIndex();

	SendMsgToEqp(ev_AudBasStartAdapter_Ack, (u8*)&tRetInfo, sizeof(tRetInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventStartAdapterNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventStartAdapterNAck. InsID:%d, chnlindx:%d, ErrorCode:%d\n", pInst->GetInsID(), cServMsg.GetChnIndex(), cServMsg.GetErrorCode()));

	TTPBasRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)pInst->GetInsID();
	tRetInfo.m_byChnID = cServMsg.GetChnIndex();
	
	SendMsgToEqp(ev_AudBasStartAdapter_NAck, (u8*)&tRetInfo, sizeof(tRetInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventStopAdapter( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	u8 byIndex;
	TP_SAFE_CAST(byIndex, ptMsg->GetBody());

	CServMsg cServMsg;
	
	cServMsg.SetChnIndex(byIndex);

	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());

	OspPost(pInst->GetBrdIID(), UMS_MCU_BAS_STOPADAPT_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventStopAdapter. EqpID:%d, ChnlIndx:%d\n", pInst->GetInsID(), byIndex));
}

void CAudBasHandler::EventStopAdapterAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventStopAdapterAck. EqpID:%d, ChnlIndx:%d\n", pInst->GetInsID(), cServMsg.GetChnIndex()));
	
	TTPBasRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)pInst->GetInsID();
	tRetInfo.m_byChnID = cServMsg.GetChnIndex();

	SendMsgToEqp(ev_AudBasStopAdapter_Ack, (u8*)&tRetInfo, sizeof(tRetInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventStopAdapterNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventStopAdapterNAck. EqpID:%d, ChnlIndx:%d, ErrorCode:%d\n", pInst->GetInsID(), cServMsg.GetChnIndex(), cServMsg.GetErrorCode()));
	
	TTPBasRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)pInst->GetInsID();
	tRetInfo.m_byChnID = cServMsg.GetChnIndex();
	
	SendMsgToEqp(ev_AudBasStopAdapter_NAck, (u8*)&tRetInfo, sizeof(tRetInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventChangeAdapterAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventChangeAdapterAck. EqpID:%d, ChnlIndx:%d\n", pInst->GetInsID(), cServMsg.GetChnIndex()));
	
	TTPBasRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)pInst->GetInsID();
	tRetInfo.m_byChnID = cServMsg.GetChnIndex();
// 调整适配成功回应不需要处理	
//	SendMsgToEqp(ev_AudBasStartAdapter_Ack, (u8*)&tRetInfo, sizeof(tRetInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventChangeAdapterNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventChangeAdapterNAck. EqpID:%d, ChnlIndx:%d\n", pInst->GetInsID(), cServMsg.GetChnIndex()));
	
	TTPBasRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)pInst->GetInsID();
	tRetInfo.m_byChnID = cServMsg.GetChnIndex();
	
	SendMsgToEqp(ev_AudBasStartAdapter_NAck, (u8*)&tRetInfo, sizeof(tRetInfo), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudBasHandler::EventSetSync( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TAudBasSyncChnl tSync;
	TP_SAFE_CAST(tSync, ptMsg->GetBody());
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventSetSync. EqpID:%d, Set:%d, Chnl %d, %d, %d\n", 
		tSync.m_byEqpID, tSync.m_bSet, tSync.m_abyChanId[0], tSync.m_abyChanId[1], tSync.m_abyChanId[2]));
	
	u8 abBuf[4] = {0xFF};
	
	abBuf[0] = (u8)tSync.m_bSet;
	abBuf[1] = tSync.m_abyChanId[0];
	abBuf[2] = tSync.m_abyChanId[1];
	abBuf[3] = tSync.m_abyChanId[2];
	
	cServMsg.SetMsgBody(abBuf, sizeof(abBuf));

	OspPost(pInst->GetBrdIID(), UMS_BAS_AUD_SET_SYNC_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CAudBasHandler::EventSetMediaKey( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	TQTMediaKeyInfo tQTKeyInfo;
	tQTKeyInfo.SetHandle(tInfo.m_dwHandle);
	tQTKeyInfo.SetIndex(tInfo.m_wIndex);
	tQTKeyInfo.SetKeyFrequency(tInfo.m_emKeyFrequency);
	tQTKeyInfo.SetKeyLen(tInfo.m_dwKeyLen);
	tQTKeyInfo.SetQtFlag(tInfo.m_dwQtFlag);
	
	memcpy(tQTKeyInfo.m_szAlias, tInfo.m_szAlias, TP_MAX_ALIAS_LEN);
	
	memcpy(tQTKeyInfo.m_szMediaKey1, tInfo.m_szMediaKey, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey2, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey3, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey4, tInfo.m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	
	CServMsg cServMsg;
	cServMsg.SetChnIndex(tInfo.m_dwHandle);
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&tQTKeyInfo, sizeof(tQTKeyInfo));
	
	OspPost(pInst->GetBrdIID(), UMS_BAS_AUD_SET_MEDIA_KEY_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasHandler::EventSetMediaKey. tInfo.m_dwHandle:%d InsID:%d MsgLen:%d\n", tInfo.m_dwHandle, pInst->GetInsID(), cServMsg.GetServMsgLen()));
}
