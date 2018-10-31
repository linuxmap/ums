#include "audmixhandler.h"
#include "umsobject.h"
#include "tplog.h"
#include "mcudef.h"
#include "mcuinstdef.h"
#include "mcuboardmgr.h"
#include "innereventumsaudiomix.h"
#include "umsapi.h"
#include "codecwrapperdef_hd.h"
#include "hdudef.h"

CAudMixHandler::CAudMixHandler()
{

}

CAudMixHandler::~CAudMixHandler()
{

}

BOOL32 CAudMixHandler::MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u16 wEvent = ptMsg->event;
	BOOL32 bProc = TRUE;

	if (NULL == pInst)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudMixHandler::MsgFromServiceHandler Instance is NULL.\n"));
		return FALSE;
	}

	switch (wEvent)
	{
	case OSP_DISCONNECT:
		{
			EventDisconnect(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_REG_REQ:				
		{
			EventReg(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_MIXERSTATUS_NOTIF:				
		{
			EventMixerStatNtfy(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_STARTMIX_ACK:				
		{
			EventStartMixAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_STARTMIX_NACK:				
		{
			EventStartMixNAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_STOPMIX_ACK:				
		{
			EventStopMixAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_STOPMIX_NACK:				
		{
			EventStopMixNAck(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_ADDMEMBER_ACK:				
		{
			EventAddMixMemberAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_ADDMEMBER_NACK:				
		{
			EventAddMixMemberNAck(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_REMOVEMEMBER_ACK:				
		{
			EventDelMixMemberAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_REMOVEMEMBER_NACK:				
		{
			EventDelMixMemberNAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_SETMIXDEPTH_ACK:				
		{
			EventSetMixDepthAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_SETMIXDEPTH_NACK:				
		{
			EventSetMixDepthNAck(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_ACTIVEMMBCHANGE_NOTIF:
		{
			EventVacResultNtfy(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_FORCEACTIVE_ACK:
		{
			EventForceMemberMixAck(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_FORCEACTIVE_NACK:
		{
			EventForceMemberMixAck(ptMsg, pInst);
		}
		break;

	case UMS_MIXER_MCU_CANCELFORCEACTIVE_ACK:
		{
			EventCancelForceMemberMixAck(ptMsg, pInst);
		}
		break;
		
	case UMS_MIXER_MCU_CANCELFORCEACTIVE_NACK:
		{
			EventCancelForceMemberMixNAck(ptMsg, pInst);
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

void CAudMixHandler::EventDisconnect(CMessage* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u32 dwNode = pInst->GetBrdNode();

//	SendMsgToEqp(OSP_DISCONNECT, (u8*)&dwNode, sizeof(u32), pInst->GetInsID(), pInst->GetBrdNode());
}

BOOL32 CAudMixHandler::MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst)
{
	u16 wEvent = ptMsg->GetEvent();

	if (NULL == pInst)
	{
		MdlError(Ums_Mdl_Eqp, ("CAudMixHandler::MsgFromEqpHandler Instance is NULL.\n"));
		return FALSE;
	}

	BOOL32 bProc = TRUE;
	switch (wEvent)
	{
	case ev_mixer_reg_ack:		
		{
			EventRegAck(ptMsg, pInst);
		}
		break;

	case ev_mixer_reg_nack:		
		{
			EventRegNack(ptMsg, pInst);
		}
		break;

	case ev_mixer_start_mix:		
		{
			EventStartMix(ptMsg, pInst);
		}
		break;
		
	case ev_mixer_stop_mix:		
		{
			EventStopMix(ptMsg, pInst);
		}
		break;

	case ev_mixer_start_vac:		
		{
			EventStartVac(ptMsg, pInst);
		}
		break;

	case ev_mixer_stop_vac:		
		{
			EventStopVac(ptMsg, pInst);
		}
		break;

	case ev_mixer_add_mixmember:		
		{
			EventAddMixMember(ptMsg, pInst);
		}
		break;

	case ev_mixer_del_mixmember:		
		{
			EventDelMixMember(ptMsg, pInst);
		}
		break;

	case ev_mixer_set_depth:
		{
			EventSetMixDepth(ptMsg, pInst);
		}
		break;

	case ev_mixer_set_vac_keeptime:
		{
			EventSetVacKeepTime(ptMsg, pInst);
		}
		break;

	case ev_mixer_if_snd_ntfy:
		{
			EventSendAudNtfy(ptMsg, pInst);
		}
		break;

	case ev_mixer_ForceActive_Cmd:
		{
			EventForceMemberMix(ptMsg, pInst);
		}
		break;

	case ev_mixer_CancelForceActive_Cmd:
		{
			EventCancelForceMemberMix(ptMsg, pInst);
		}
		break;

	case ev_mixer_SyncChnl_Cmd:
		{
			EventSyncChnlCmd(ptMsg, pInst);
		}
		break;

	case ev_mixer_set_mediakey_ntfy:
		{
			EventSetMediaKeyNtfy(ptMsg, pInst);
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

void CAudMixHandler::EventReg( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpRegReq tEqpReg;
	TP_SAFE_CAST(tEqpReg, cServMsg.GetMsgBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CApu2Handler::OnReg instID:%d, EqpID:%d, IP:"TPIPFORMAT", StartPort:%d, ChanNum:%d, Alias:%s, Ver:%d, HD:%d.\n",
		pInst->GetInsID(), tEqpReg.GetEqpId(), Tpu32ToIP(tEqpReg.GetPeriEqpIpAddr()), tEqpReg.GetStartPort(),
		tEqpReg.GetChnnlNum(), tEqpReg.GetEqpAlias(), tEqpReg.GetVersion(), tEqpReg.IsHDEqp()));
	
	//预防修改配置后断链和注册请求冲突
	if (INVALID_NODE != pInst->GetBrdNode())
	{
		MdlError(Ums_Mdl_Eqp, ("CAudMixHandler::OnReg BrdNode is valid. Node:%d, Inst:%d, EqpID:%d\n", pInst->GetBrdNode(), pInst->GetInsID(), tEqpReg.GetEqpId()));
		OspPost(ptMsg->srcid, UMS_MCU_MIXER_REG_NACK, NULL, 0, ptMsg->srcnode);
        ::OspDisconnectTcpNode(ptMsg->srcnode);
		
		return ;
	}
	
	if (tEqpReg.GetEqpId() != pInst->GetInsID())
	{
		MdlError(Ums_Mdl_Eqp, ("CAudMixHandler::EventReg. EqpID is Invalid!\n"));
		
		OspPost(ptMsg->srcid, UMS_MCU_MIXER_REG_NACK, NULL, 0, ptMsg->srcnode);
        ::OspDisconnectTcpNode(ptMsg->srcnode);
		
		return ;
	}

	pInst->SetBrdNode(ptMsg->srcnode);
	pInst->SetBrdIID(ptMsg->srcid);

	OspNodeDiscCBRegQ(ptMsg->srcnode, pInst->GetAppID(), pInst->GetInsID());

	TMixerRegInfo tInfo;
	tInfo.m_dwEqpIP = tEqpReg.GetPeriEqpIpAddr();
	tInfo.m_byEqpID = tEqpReg.GetEqpId();
	tInfo.m_wStartPort = tEqpReg.GetStartPort();
	
	SendMsgToEqp(ev_mixer_reg, (u8*)(&tInfo), sizeof(TMixerRegInfo), pInst->GetInsID(), pInst->GetBrdNode());
	
}

void CAudMixHandler::EventRegAck( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TMixRegAck tAck;
	TP_SAFE_CAST(tAck, ptMsg->GetBody());
	
	TPrsTimeSpan tPrsTimeSpan;
	tPrsTimeSpan.m_wFirstTimeSpan = htons(tAck.m_tRsParam.m_wFirstTimeSpan);
	tPrsTimeSpan.m_wSecondTimeSpan = htons(tAck.m_tRsParam.m_wSecondTimeSpan);
	tPrsTimeSpan.m_wThirdTimeSpan = htons(tAck.m_tRsParam.m_wThirdTimeSpan);
	tPrsTimeSpan.m_wRejectTimeSpan = htons(tAck.m_tRsParam.m_wRejectTimeSpan);

	TPeriEqpRegAck tPeriAck;
	tPeriAck.SetMcuIpAddr(ntohl(tAck.m_dwIpAddr));
	tPeriAck.SetMcuStartPort(tAck.m_wStartPort);
	tPeriAck.SetAnotherMpcIp(0); // 没有主备
	
	u16 wMTUSize = htons(0);			//默认0，mpu2不使用
	u8	byIsSendRedundancy = 0;
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&tPeriAck, sizeof(tPeriAck));
	cServMsg.CatMsgBody((u8 *)&tPrsTimeSpan, sizeof(tPrsTimeSpan));
	cServMsg.CatMsgBody((u8 *)&wMTUSize, sizeof(u16));
	cServMsg.CatMsgBody((u8 *)&byIsSendRedundancy, sizeof(u8));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_REG_ACK, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventRegAck. InsID:%d, UmsIp:"TPIPFORMAT", UmsPort:%d, Pris(%d,%d,%d,%d)\n", 
		pInst->GetInsID(), Tpu32ToIP(tPeriAck.GetMcuIpAddr()), 
		tPeriAck.GetMcuStartPort(),
		tPrsTimeSpan.m_wFirstTimeSpan, tPrsTimeSpan.m_wSecondTimeSpan, 
		tPrsTimeSpan.m_wThirdTimeSpan, tPrsTimeSpan.m_wRejectTimeSpan));
}

void CAudMixHandler::EventRegNack( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventRegNack Instance ID:%d.\n", pInst->GetInsID()));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_REG_NACK, ptMsg->GetBody(), ptMsg->GetBodyLen(), 
				pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	OspDisconnectTcpNode(pInst->GetBrdNode());
	
	pInst->SetBrdNode(INVALID_NODE);
}

void CAudMixHandler::EventMixerStatNtfy( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpStatus tStatus;
	memset( &tStatus,0,sizeof(TPeriEqpStatus) );
	const u16 wMsgBodyLen = cServMsg.GetMsgBodyLen();
    memcpy(&tStatus, cServMsg.GetMsgBody(), min(sizeof(TPeriEqpStatus), wMsgBodyLen));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventMixerStatNtfy. EqpID:%d, InsID:%d, EqpAlias:%s, stat:%d, Online:%d\n", 
					tStatus.GetEqpId(), pInst->GetInsID(), tStatus.GetAlias(), tStatus.m_tStatus.tMixer.m_atGrpStatus[0].m_byGrpState, tStatus.m_byOnline));
	
	TMixerStatNtfy tStatNtfy;
	tStatNtfy.m_byEqpID = tStatus.GetEqpId();
	tStatNtfy.m_bOnLine = tStatus.m_byOnline;
	tStatNtfy.m_byStat = tStatus.m_tStatus.tMixer.m_atGrpStatus[0].m_byGrpState;
	tStatNtfy.m_byMixChanNum = tStatus.m_tStatus.tMixer.m_atGrpStatus[0].m_byMixGrpChnNum;
	tStatNtfy.SetAlias(tStatus.GetAlias());
	
	SendMsgToEqp(ev_mixer_stat_ntfy, (u8*)&tStatNtfy, sizeof(tStatNtfy), pInst->GetInsID(), pInst->GetBrdNode());
}

//TMixerStart+TDoublePayload+TCapSupportEx
void CAudMixHandler::EventStartMix( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TStartMix tTPStart;
	TP_SAFE_CAST(tTPStart, ptMsg->GetBody());

	TMixerStart tStart;
	TDoublePayload tPayLoad;
	TCapSupportEx tCapEx; //不填
	TMediaEncrypt tEncrypt;

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

	tStart.SetMixGroupId(0);
	tStart.SetMixDepth(tTPStart.m_byMixDepth);//讨论中最多27个会场
//	tStart.SetAudioMode(CTpTypeAdpt::GetAudPayloadValue(tTPStart.m_emAudFormat));
	tStart.SetIsAllMix(TRUE);
	tStart.SetIsNeedByPrs(TRUE);
	tStart.SetAudioEncrypt(tEncrypt);

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&tStart, sizeof(tStart));
	cServMsg.CatMsgBody((u8 *)&tPayLoad, sizeof(tPayLoad));
	cServMsg.CatMsgBody((u8 *)&tCapEx, sizeof(tCapEx));
	cServMsg.CatMsgBody((u8 *)&tTPStart.m_byNNum, sizeof(u8));

//未使用
//	tPayLoad.SetActivePayload((u8)tTPStart.m_wDynamicPayload);
//	tPayLoad.SetRealPayLoad((u8)tTPStart.m_wStaticPayload);

	TAudioCapInfo tCapInfo;//N模式音频格式
	for ( u8 byIndx = 0; byIndx < tTPStart.m_byNNum; byIndx ++ )
	{
		tCapInfo.SetAudioMediaType(CTpTypeAdpt::GetAudPayloadValue(tTPStart.m_atAudFmt[byIndx].m_emFormat));
		tCapInfo.SetAudioTrackNum(1);
		tCapInfo.SetActivePayLoad(CTpTypeAdpt::GetAudPayloadValue(tTPStart.m_atAudFmt[byIndx].m_emFormat));

		cServMsg.CatMsgBody((u8 *)&tCapInfo, sizeof(tCapInfo));
	}
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_STARTMIX_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStartMix. InsID:%d, EqpID:%d, Depth:%d, AudFormat:(%d,%d,%d,%d)\n", 
							pInst->GetInsID(), tTPStart.m_byEqpID, tTPStart.m_byMixDepth
							, tTPStart.m_atAudFmt[0].m_emFormat, tTPStart.m_atAudFmt[1].m_emFormat, tTPStart.m_atAudFmt[2].m_emFormat
							, tTPStart.m_atAudFmt[3].m_emFormat));

	return ;
}

void CAudMixHandler::EventStartMixAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStartMixAck. InsID:%d\n", pInst->GetInsID()));

	u8 byEqpID = (u8)pInst->GetInsID();

	SendMsgToEqp(ev_mixer_start_mix_ack, (u8*)&byEqpID, sizeof(u8), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventStartMixNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStartMixNAck. InsID:%d, ErrorCode:%d\n", pInst->GetInsID(), cServMsg.GetErrorCode()));
	
	u8 byEqpID = (u8)pInst->GetInsID();

	SendMsgToEqp(ev_mixer_start_mix_nack, (u8*)&byEqpID, sizeof(u8), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventStopMix( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	u8 byGrpID = 0;

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8*)&byGrpID, sizeof(u8));

	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_STOPMIX_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStopMix. EqpID:%d\n", pInst->GetInsID()));
}

void CAudMixHandler::EventStopMixAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byGrpID = *(u8*)cServMsg.GetMsgBody();
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStopMixAck. EqpID:%d, GrpID:%d\n", pInst->GetInsID(), byGrpID));
	
	u8 byEqpID = (u8)pInst->GetInsID();

	SendMsgToEqp(ev_mixer_stop_mix_ack, (u8*)&byEqpID, sizeof(u8), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventStopMixNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStopMixNAck. InsID:%d, ErrorCode:%d\n", pInst->GetInsID(), cServMsg.GetErrorCode()));
	
	u8 byEqpID = (u8)pInst->GetInsID();
	
	SendMsgToEqp(ev_mixer_stop_mix_nack, (u8*)&byEqpID, sizeof(u8), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventAddMixMember( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventAddMixMember. InsID:%d, EqpID:%d, EPID:%d, indx:%d, AudFormat:%d, SampleFreq:%d, TrackNum:%d , RtpRcv"TPIPFORMAT":%d, RtcpRcv"TPIPFORMAT":%d\n", 
										pInst->GetInsID(), tTpMember.m_byEqpID, tTpMember.m_wEpID, tTpMember.m_byIndex, tTpMember.m_emAudFormat, tTpMember.m_emPASampleFreq, tTpMember.m_emPAChnlCfg,
										Tpu32ToIP(tTpMember.m_tLocalRtpRcv.GetIP()),tTpMember.m_tLocalRtpRcv.GetPort(),
										Tpu32ToIP(tTpMember.m_tLocalRtcpRcv.GetIP()),tTpMember.m_tLocalRtcpRcv.GetPort()));

	u8 byGrpID = 0;
	TMixMember tMember;
	u8 byAudFormat = CTpTypeAdpt::GetAudPayloadValue(tTpMember.m_emAudFormat);
	u8 byOutAudFormat = CTpTypeAdpt::GetAudPayloadValue(tTpMember.m_emOutAudFormat);

	tMember.m_tMember.SetMtId((u8)tTpMember.m_byIndex+1); // 之前用的epid, 现在改用通道索引，混音器不支持mtID为0，因此加1
	tMember.m_byAudioType = byAudFormat;
	tMember.m_byVolume = MAXVALUE_APU2_VOLUME/2;

	tMember.m_tAddr.SetIpAddr(ntohl(tTpMember.m_tLocalRtpRcv.GetIP()));  //本地地址 ums用于接收混音码流
	tMember.m_tAddr.SetPort(tTpMember.m_tLocalRtpRcv.GetPort());
	tMember.m_tRtcpBackAddr.SetIpAddr(ntohl(tTpMember.m_tLocalRtcpRcv.GetIP()));  //本地地址  ums用于接收混音版的重传
	tMember.m_tRtcpBackAddr.SetPort(tTpMember.m_tLocalRtcpRcv.GetPort());

	TAudioCapInfo tCapInfo;
	tCapInfo.SetAudioMediaType(byAudFormat);
	tCapInfo.SetAudioTrackNum(1);//写死，单声道
	tCapInfo.SetActivePayLoad((u8)tTpMember.m_wDynamicPayload);

	TAudioCapInfo tOutCapInfo;
	tOutCapInfo.SetAudioMediaType(byOutAudFormat);
	tOutCapInfo.SetAudioTrackNum(1);//写死，单声道
	tOutCapInfo.SetActivePayLoad((u8)tTpMember.m_wOutDynamicPayload);


	u8 bySampleRate = AAC_SAMPLE_FRQ_32;//采样率

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetChnIndex(tTpMember.m_byIndex);//通道索引， 由ums来决定，便于计算端口
	cServMsg.SetMsgBody((u8 *)&byGrpID, sizeof(u8));
	cServMsg.CatMsgBody((u8 *)&tMember, sizeof(TMixMember));
	cServMsg.CatMsgBody((u8 *)&byAudFormat, sizeof(u8));
	cServMsg.CatMsgBody((u8 *)&bySampleRate, sizeof(u8));
	cServMsg.CatMsgBody((u8 *)&tCapInfo, sizeof(tCapInfo));
	cServMsg.CatMsgBody((u8 *)&tOutCapInfo, sizeof(tOutCapInfo));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_ADDMEMBER_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));

	return ;
}

void CAudMixHandler::EventAddMixMemberAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byGrpID = *(u8*)cServMsg.GetMsgBody();
	TMixMember* ptMember = (TMixMember*)(cServMsg.GetMsgBody() + sizeof(u8));

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventAddMixMemberAck. EqpID:%d, chanIndex:%d\n", pInst->GetInsID(), ptMember->m_tMember.GetMtId()));

	TTPMixMember tTpMember;
	tTpMember.m_byEqpID = (u8)pInst->GetInsID();
	tTpMember.m_byIndex = ptMember->m_tMember.GetMtId()-1;//收到的mtid统一减1变成索引

	SendMsgToEqp(ev_mixer_add_mixmember_ack, (u8*)&tTpMember, sizeof(tTpMember), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventAddMixMemberNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byGrpID = *(u8*)cServMsg.GetMsgBody();
	TMixMember* ptMember = (TMixMember*)(cServMsg.GetMsgBody() + sizeof(u8));

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventAddMixMemberNAck. EqpID:%d, chanIndex:%d, ErrorCode:%d\n", 
									pInst->GetInsID(), ptMember->m_tMember.GetMtId(), cServMsg.GetErrorCode()));
	
	TTPMixMember tTpMember;
	tTpMember.m_byEqpID = (u8)pInst->GetInsID();
	tTpMember.m_byIndex = ptMember->m_tMember.GetMtId()-1;//收到的mtid统一减1变成索引
	
	SendMsgToEqp(ev_mixer_add_mixmember_nack, (u8*)&tTpMember, sizeof(tTpMember), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventDelMixMember( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TTPMixMember tTpMember;
	TP_SAFE_CAST(tTpMember, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventDelMixMember. EqpID:%d, EpID:%d, chanIndex:%d\n", pInst->GetInsID(), tTpMember.m_wEpID, tTpMember.m_byIndex));

	u8 byGrpID = 0;
	TMixMember tMember;
	tMember.m_tMember.SetMtId((u8)tTpMember.m_byIndex+1);//之前用的epid, 现在改用通道索引 但要加1

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&byGrpID, sizeof(byGrpID));
	cServMsg.CatMsgBody((u8 *)&tMember, sizeof(tMember));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_REMOVEMEMBER_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CAudMixHandler::EventDelMixMemberAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byGrpID = *(u8*)cServMsg.GetMsgBody();
	TMixMember* ptMember = (TMixMember*)(cServMsg.GetMsgBody() + sizeof(u8));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventDelMixMemberAck. EqpID:%d, ChanIndex:%d\n", pInst->GetInsID(), ptMember->m_tMember.GetMtId()));
	
	TTPMixMember tTpMember;
	tTpMember.m_byEqpID = (u8)pInst->GetInsID();
	tTpMember.m_byIndex = ptMember->m_tMember.GetMtId()-1;//收到的mtid统一减1变成索引
	
	SendMsgToEqp(ev_mixer_del_mixmember_ack, (u8*)&tTpMember, sizeof(tTpMember), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventDelMixMemberNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byGrpID = *(u8*)cServMsg.GetMsgBody();
	TMixMember* ptMember = (TMixMember*)(cServMsg.GetMsgBody() + sizeof(u8));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventDelMixMemberNAck. EqpID:%d, ChanIndex:%d\n", pInst->GetInsID(), ptMember->m_tMember.GetMtId()));
	
	TTPMixMember tTpMember;
	tTpMember.m_byEqpID = (u8)pInst->GetInsID();
	tTpMember.m_byIndex = ptMember->m_tMember.GetMtId()-1;//收到的mtid统一减1变成索引
	
	SendMsgToEqp(ev_mixer_del_mixmember_nack, (u8*)&tTpMember, sizeof(tTpMember), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventSetMixDepth( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TTPMixDepth tDepth;
	TP_SAFE_CAST(tDepth, ptMsg->GetBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventSetMixDepth. EqpID:%d, Depth:%d\n", pInst->GetInsID(), tDepth.m_byDepth));

	u8 byGrpID = 0;

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&byGrpID, sizeof(byGrpID));
	cServMsg.CatMsgBody((u8 *)&tDepth.m_byDepth, sizeof(u8));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_SETMIXDEPTH_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CAudMixHandler::EventSetMixDepthAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byGrpID = *(u8*)cServMsg.GetMsgBody();
	u8 byDepth = *(u8*)cServMsg.GetMsgBody() + sizeof(u8);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventSetMixDepthAck. EqpID:%d, Depth:%d\n", pInst->GetInsID(), byDepth));

	u8 byEqpID = (u8)pInst->GetInsID();
	
	SendMsgToEqp(ev_mixer_set_depth_ack, (u8*)&byEqpID, sizeof(byEqpID), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventSetMixDepthNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 byGrpID = *(u8*)cServMsg.GetMsgBody();
	u8 byDepth = *(u8*)cServMsg.GetMsgBody() + sizeof(u8);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventSetMixDepthNAck. EqpID:%d, Depth:%d\n", pInst->GetInsID(), byDepth));
	
	u8 byEqpID = (u8)pInst->GetInsID();

	SendMsgToEqp(ev_mixer_set_depth_nack, (u8*)&byEqpID, sizeof(byEqpID), pInst->GetInsID(), pInst->GetBrdNode());
}

void CAudMixHandler::EventSendAudNtfy( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	BOOL32 bSend;
	TP_SAFE_CAST(bSend, ptMsg->GetBody());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventSendAudNtfy. EqpID:%d, Send:%d\n", pInst->GetInsID(), bSend));
	
	u8 byGrpID = 0;
	u8 bySend = bSend ? 1 : 0;
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&byGrpID, sizeof(byGrpID));
	cServMsg.CatMsgBody((u8 *)&bySend, sizeof(bySend));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_SEND_NOTIFY, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CAudMixHandler::EventSetVacKeepTime( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	u32 dwVacKeepTimeS;
	TP_SAFE_CAST(dwVacKeepTimeS, ptMsg->GetBody()+sizeof(u8));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventSetVacKeepTime. EqpID:%d, VacKeepTime:%d\n", pInst->GetInsID(), dwVacKeepTimeS));
	
	u8 byGrpID = 0;
	
	//网络序
	dwVacKeepTimeS = htonl(dwVacKeepTimeS);

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&byGrpID, sizeof(byGrpID));
	cServMsg.CatMsgBody((u8 *)&dwVacKeepTimeS, sizeof(dwVacKeepTimeS));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_VACKEEPTIME_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CAudMixHandler::EventStartVac( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TStartMix tTPStart;
	TP_SAFE_CAST(tTPStart, ptMsg->GetBody());
	
	TMixerStart tStart;
	TDoublePayload tPayLoad;
	TCapSupportEx tCapEx; //不填
	
	tStart.SetMixGroupId(0);
	tStart.SetMixDepth(tTPStart.m_byMixDepth);//讨论中最多27个会场
//	tStart.SetAudioMode(CTpTypeAdpt::GetAudPayloadValue(tTPStart.m_emAudFormat));
	tStart.SetIsAllMix(TRUE);
	tStart.SetIsNeedByPrs(TRUE);
	
//	tPayLoad.SetActivePayload((u8)tTPStart.m_wDynamicPayload);
//	tPayLoad.SetRealPayLoad((u8)tTPStart.m_wStaticPayload);
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&tStart, sizeof(tStart));
	cServMsg.CatMsgBody((u8 *)&tPayLoad, sizeof(tPayLoad));
	cServMsg.CatMsgBody((u8 *)&tCapEx, sizeof(tCapEx));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_STARTVAC_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStartVac. InsID:%d, EqpID:%d, Depth:%d, AudFormat:(%d,%d,%d,%d)\n", 
		pInst->GetInsID(), tTPStart.m_byEqpID, tTPStart.m_byMixDepth
		, tTPStart.m_atAudFmt[0].m_emFormat, tTPStart.m_atAudFmt[1].m_emFormat, tTPStart.m_atAudFmt[2].m_emFormat
							, tTPStart.m_atAudFmt[3].m_emFormat));
	
	return ;
}

void CAudMixHandler::EventStopVac( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{//停止语音激励
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_STOPVAC_CMD, NULL, 0, pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventStopVac. InsID:%d\n", pInst->GetInsID()));
	
	return ;
}

void CAudMixHandler::EventVacResultNtfy( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	TMixVacResInfo tVacInfo;
	tVacInfo.m_byEqpId = (u8)pInst->GetInsID();
	memcpy(tVacInfo.m_abyChanId, cServMsg.GetMsgBody(), sizeof(tVacInfo.m_abyChanId)); // chanid  不减1 ，无效为0xff
	tVacInfo.m_byVacChanId = *(u8*)(cServMsg.GetMsgBody() + sizeof(u8)*MAXNUM_MIXER_DEPTH); // 事实为mtid，需要减1，无效为0xff


	if (tVacInfo.m_byVacChanId != 0xFF)
	{// 不是无效值，说明激励出了有效的mtid，需要减1
		tVacInfo.m_byVacChanId--;
	}

	MdlLowDtl(Ums_Mdl_Eqp, ("CAudMixHandler::EventVacResultNtfy. EqpID:%d, vacchanid:%d, (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", pInst->GetInsID(), tVacInfo.m_byVacChanId,
		tVacInfo.m_abyChanId[0], tVacInfo.m_abyChanId[1], tVacInfo.m_abyChanId[2], tVacInfo.m_abyChanId[3], tVacInfo.m_abyChanId[4], tVacInfo.m_abyChanId[5],
		tVacInfo.m_abyChanId[6], tVacInfo.m_abyChanId[7], tVacInfo.m_abyChanId[8], tVacInfo.m_abyChanId[9]));
	
	SendMsgToEqp(ev_mixer_vac_result_ntfy, (u8*)&tVacInfo, sizeof(tVacInfo), pInst->GetInsID(), pInst->GetBrdNode());
	
	return ;
}

void CAudMixHandler::EventForceMemberMix( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	u8 byChnlIndx = 0;
	TP_SAFE_CAST(byChnlIndx, ptMsg->GetBody());

	TMixMember tMember;
	tMember.m_tMember.SetMtId(byChnlIndx+1);//UMS侧用索引

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventForceMemberMix. InsID:%d, chnl:%d\n", pInst->GetInsID(), byChnlIndx));

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&tMember, sizeof(tMember));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_FORCEACTIVE_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}

void CAudMixHandler::EventForceMemberMixAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventForceMemberMixAck. InsID:%d\n", pInst->GetInsID()));
	return ;
}

void CAudMixHandler::EventForceMemberMixNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	MdlError(Ums_Mdl_Eqp, ("CAudMixHandler::EventForceMemberMixNAck. InsID:%d, ErrorCode:%d\n", pInst->GetInsID(), cServMsg.GetErrorCode()));
	return ;
}

void CAudMixHandler::EventCancelForceMemberMix( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());

	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventCancelForceMemberMix. InsID:%d\n", pInst->GetInsID()));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_CANCELFORCEACTIVE_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));

	return ;
}

void CAudMixHandler::EventCancelForceMemberMixAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventCancelForceMemberMixAck. InsID:%d\n", pInst->GetInsID()));
	return ;
}

void CAudMixHandler::EventCancelForceMemberMixNAck( CMessage* const ptMsg, CTPMcuBrdSsn* pInst )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	MdlError(Ums_Mdl_Eqp, ("CAudMixHandler::EventCancelForceMemberMixNAck. InsID:%d, ErrorCode:%d\n", pInst->GetInsID(), cServMsg.GetErrorCode()));
	return ;
}

void CAudMixHandler::EventSyncChnlCmd( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
{
	TMixSyncChnl tSync;
	TP_SAFE_CAST(tSync, ptMsg->GetBody());

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventSyncChnlCmd. EqpID-Chnl %d-%d, %d-%d, %d-%d\n", 
		tSync.m_abyEqpId[0], tSync.m_abyChanId[0], 
		tSync.m_abyEqpId[1], tSync.m_abyChanId[1],
		tSync.m_abyEqpId[2], tSync.m_abyChanId[2]));

	u8 abBuf[6] = {0xFF};

	abBuf[0] = tSync.m_abyEqpId[0];
	abBuf[1] = tSync.m_abyChanId[0];

	abBuf[2] = tSync.m_abyEqpId[1];
	abBuf[3] = tSync.m_abyChanId[1];

	abBuf[4] = tSync.m_abyEqpId[2];
	abBuf[5] = tSync.m_abyChanId[2];

	cServMsg.SetMsgBody(abBuf, sizeof(abBuf));
	
	//发往daemon
	OspPost(MAKEIID(GETAPP(pInst->GetBrdIID()), CInstance::DAEMON), UMS_MCU_MIXER_SYNCCHNL_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
						pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
}


void CAudMixHandler::EventSetMediaKeyNtfy( CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst )
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
	cServMsg.SetSrcSsnId((u8)pInst->GetInsID());
	cServMsg.SetMsgBody((u8 *)&tQTKeyInfo, sizeof(tQTKeyInfo));
	
	OspPost(pInst->GetBrdIID(), UMS_MCU_MIXER_SETMEDIAKEY_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen(), 
		pInst->GetBrdNode(), MAKEIID(pInst->GetAppID(), pInst->GetInsID()));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudMixHandler::EventSetMediaKeyNtfy. InsID:%d MsgLen:%d\n", pInst->GetInsID(), cServMsg.GetServMsgLen()));
}