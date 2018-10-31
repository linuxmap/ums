#include "umsstackinterface.h"
#include "innereventumscall.h"
#include "innereventumsconf.h"
#include "tpmsg.h"
#include "umsobject.h"
#include "eventoutsipadapter.h"
#include "innereventregsrv.h"
#include "umsxmltype.h"
#include "eventoutumsselview.h"
#include "eventoutumsbrdvmp.h"
#include "eventoutumsmcucasecade.h"

#include "umsapi.h"
#include "eventoutquantum.h"

TUmsStackCallCfg g_tUmsStackCfg;


static void NotifyMsgToAdapter(u16 wEvent, const TUmsHandle& tHandle, const void* pBuf, u16 wSize)
{
	if (tHandle.m_dwAdapteID == 0)
	{
		MdlError(Ums_Mdl_Call, ("NotifyMsgToAdapter failed! event:%d->%s\n", wEvent, GetEventNamebyID(wEvent)));
		return;
	}
	

	CTpMsg cMsg;	
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	if (NULL != pBuf)
	{
		cMsg.CatBody(pBuf, wSize);
	}
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));
}

static void NotifyMsgToCall(u16 wEvent, const TUmsHandle& tHandle, void* pBuf, u16 wSize)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	if (NULL != pBuf)
	{
		cMsg.CatBody(pBuf, wSize);
	}
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}


// out
u16 UmsMakeCall(const TUmsHandle& tHandle, const TMakeCallPara& tCallPara)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsMakeCall ConfID:%d, epID:%d, dst Alias:%s,E164:%s,IP:"TPIPFORMAT",bIPAlias:%d, type:%d->%s\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias
		, tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP),tCallPara.m_tCallInfo.m_tDestAddr.m_bAliasIP
		, TpEnumIdString(EmTpConfProtocol, tCallPara.m_tCallInfo.m_emTpProtocol)));
	
	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makecall, (u8*)&tCallPara, tHandle, OUTSIGN);

	NotifyMsgToAdapter(ev_MakeCall_Req, tHandle, (void*)&tCallPara, sizeof(tCallPara));
	return TP_RET_OK;
}

u16 UmsMakeChan(const TUmsHandle& tHandle, TUmsNodeCapset& tCallPara, BOOL32 bIsDual)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsMakeChan ConfID:%d, epID:%d, bDual:%d.\n", tHandle.GetConfID(), tHandle.GetEpID(), bIsDual));

	TMakeCallPara tSndPara;
	memcpy(&tSndPara.m_tCapSet, &tCallPara, sizeof(tSndPara.m_tCapSet));
	if (tSndPara.m_tCapSet.m_tVidSndCap.m_tHp.IsValid())
	{
		tSndPara.m_tCapSet.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
	}
	if (tSndPara.m_tCapSet.m_tVidRcvCap.m_tHp.IsValid())
	{
		tSndPara.m_tCapSet.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
	}
	tSndPara.m_tCapSet.m_wAudDecNum = 0;
	tSndPara.m_tCapSet.m_wAudEncNum = 0;

	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makechan, (u8*)&tCallPara, tHandle, OUTSIGN);

	CTpMsg cMsg;
	cMsg.SetEvent(ev_MakeChan_Req);
	cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
	cMsg.CatBody(&tSndPara.m_tCapSet, sizeof(TUmsNodeCapset));
	cMsg.CatBody(&bIsDual, sizeof(BOOL32));
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));
	return TP_RET_OK;
}

//add
u16 UmsCloseChan(const TUmsHandle& tHandle, const EmChanType emType, const TUmsNodeCapset& tNode)
{
	return 1;
	MdlHint(Ums_Mdl_Stack, (">> UmsCloseChan ConfID:%d, epID:%d, chanType:(%d->%s).\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), TpEnumIdString(EmChanType, emType)));

	//CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makecall, (u8*)&tCallPara, tHandle, OUTSIGN);

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Close_Chan_Req);
	cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
	cMsg.CatBody(&emType, sizeof(EmChanType));
	cMsg.CatBody(&tNode, sizeof(TUmsNodeCapset));
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));

	return TP_RET_OK;
}

void UmsAnwserCall( const TUmsHandle& tHandle, const BOOL32 bAnwser, const TMakeCallPara* ptCallPara, EmCnsCallReason emReason)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsAnwserCall ConfID:%d, epID:%d, bAnwser:%d, PACall:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), bAnwser, tHandle.handPaCall));

	TMakeCallPara tPara;
	if (NULL != ptCallPara)
	{		
		CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_channelconnect, (u8*)&ptCallPara->m_tCapSet, tHandle, OUTSIGN);
	}
	else
	{
		ptCallPara = &tPara;
	}

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_AnwserCall_IND);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&bAnwser, sizeof(bAnwser));
	cMsg.CatBody(&emReason, sizeof(EmCnsCallReason));
	cMsg.CatBody(ptCallPara, sizeof(TMakeCallPara));
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));
}

u16 UmsHangUp(const TUmsHandle& tHandle, EmCnsCallReason emReason)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsHangUp ConfID:%d, epID:%d, PACall:%d, emReason:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, emReason));
	
	NotifyMsgToAdapter(ev_HungUp_Req, tHandle, &emReason, sizeof(emReason));

	return TP_RET_OK;
}

u16 UmsClearConference(const TUmsHandle& tHandle)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsClearConference ConfID:%d\n", tHandle.GetConfID()));
	NotifyMsgToAdapter(evtp_Conf_Clear,  tHandle, NULL, 0);
	return TP_RET_OK;
}

u16 UmsMakeSendDual(const TUmsHandle& tHandle, TUmsNodeCapset& tCapSet)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsMakeSendDual ConfID:%d, epID:%d, nPaID:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
	
	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makesenddual, (u8*)&tCapSet, tHandle, OUTSIGN);

	
	NotifyMsgToAdapter(ev_OpenDualChan_Req, tHandle, (void*)&tCapSet, sizeof(tCapSet));
	return TP_RET_OK;
}

u16 UmsAnswerSendDual(const TUmsHandle& tHandle, TUmsNodeCapset& tCapSet, BOOL32 bRes)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsAnswerSendDual ConfID:%d, epID:%d\n", tHandle.GetConfID(), tHandle.GetEpID()));
	
	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makesenddual, (u8*)&tCapSet, tHandle, OUTSIGN);
	
	CTpMsg cMsg;	
	cMsg.SetEvent(ev_MakeSendDual_Answer);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&bRes, sizeof(BOOL32));
	cMsg.CatBody(&tCapSet, sizeof(TUmsNodeCapset));

	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));

	//NotifyMsgToAdapter(ev_MakeSendDual_Answer, tHandle, (void*)&tCapSet, sizeof(tCapSet));
	return TP_RET_OK;
}

u16 UmsStopDual(const TUmsHandle& tHandle, EmTPChannelReason emReason)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsStopDual ConfID:%d, epID:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID()));
	
	NotifyMsgToAdapter(ev_DualChan_DisConnect, tHandle, &emReason, sizeof(emReason));
	return TP_RET_OK;
}


u16 UmsSendChanCtrl( const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize )
{	
	switch(nMsgType)
	{
	case evtp_Conf_AskKeyFrame:
		{
			tpLowDtl(Ums_Mdl_Stack, ">> AskKeyFrame, ConfID:%d, EpID:%d, CallID:%d, ChanID:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, tHandle.handPaChan);

			//PA_SendChanCtrl( tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan, emPAConfFastUpdate, NULL, 0);
		}
		break;
	case evtp_Chan_FlowCtrol:
		{
			u16 wBand = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">> UmsFlowControl ConfID:%d, epID:%d, ChanID:%d band:%d\n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, wBand));
			//PA_SendChanCtrl( tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan, emPAConfFlowCtrl, (u8*)&wBand, sizeof(wBand));
		}
		break;
	case evtp_Conf_ViewObj_Ind:
		{
			TChanViewRes tRes = *(TChanViewRes*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">> ViewObjInd ConfID:%d, epID:%d, ChanID:%d wret:%d, Name:%s\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, tRes.m_emRes, tRes.m_tAlias.m_abyAlias));
			//PA_SendChanCtrl( tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan, emPAChanSelecteCascadRes, (u8*)&wRet, sizeof(wRet));
		}
		break;
	case evtp_Conf_UndoViewObj_Ind:
		{
			EmTPViewResult emViewResult = *(EmTPViewResult*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">> cancelViewObjInd ConfID:%d, epID:%d, ChanID:%d Reason:%d\n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, emViewResult));
			//PA_SendChanCtrl( tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan, emPAChanSelecteCascadCancelRes, (u8*)&wRet, sizeof(wRet));
		}
		break;
	case evtp_Conf_ChanSeeLocal_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">> evtp_Conf_ChanSeeLocal_Ind ConfID:%d, epID:%d, ChanID:%d \n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan));
			//PA_SendChanCtrl( tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan, emPAChanSeeLocal, NULL, 0);
		}
		break;
	case evtp_Conf_ChanSeeLocalCancel_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">> evtp_Conf_ChanSeeLocalCancel_Ind ConfID:%d, epID:%d, ChanID:%d \n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan));
			//PA_SendChanCtrl( tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan, emPAChanSeeLocalCancel, NULL, 0);
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, (">> UmsSendChanCtrl failed. unkonw msg type. ConfID:%d, epID:%d, ChanID:%d, event:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, nMsgType));
		}
		break;
	}

	NotifyMsgToAdapter(nMsgType, tHandle, pBuf, nSize);
	return TP_RET_OK;
}

static BOOL32 UmsSendDualConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();

	switch(nMsgType)
	{
	case evtp_Conf_RequestDualStream_cmd:
		{
			TEpKeyEx tEx = *(TEpKeyEx*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_RequestDualStream_cmd, ConfID:%d, EpID:%d, CallID:%d, epid:%d, key:%s\n", 
				wConfID, wEpID, nPaID, tEx.m_wEpID, tEx.m_achReserve));
// 			TDualRequestTr* ptUms = (TDualRequestTr*)pBuf;
// 			TDualRequest tPA;
// 			tPA.m_nEpId = ptUms->m_wEpID;
// 			strncpy(tPA.m_achCascade, ptUms->m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
// 			PA_SendConfCtrl(nAppID, nPaID, emPARequestDualStreamCmd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_RequestDualStream_Ind:
		{
			TDualRequestAckTr* ptAck = (TDualRequestAckTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_RequestDualStream_Ind, ConfID:%d, EpID:%d, CallID:%d, DualEpID:%d\n", wConfID, wEpID, nPaID, ptAck->m_tEpKey.m_wEpID));
// 			TDualRequestAckTr* ptUms = (TDualRequestAckTr*)pBuf;
// 			const u32 nSize = sizeof(BOOL32) + sizeof(EmDualReason) + sizeof(TDualRequest);
// 			u8 abyBuf[nSize];
// 			*(BOOL32*)abyBuf = ptUms->m_bAccept;
// 			*(EmDualReason*)(abyBuf+sizeof(BOOL32)) = (EmDualReason)ptUms->m_dwReason;
// 			TDualRequest* ptPA = (TDualRequest*)(abyBuf+sizeof(BOOL32)) + sizeof(EmDualReason);
// 			ptPA->m_nEpId = ptUms->m_wEpID;
// 			strncpy(ptPA->m_achCascade, ptUms->m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
// 			PA_SendConfCtrl(nAppID, nPaID, emPARequestDualStreamInd, abyBuf, nSize);
		}
		break;
	case evtp_cascade_OpenDualChan_Cmd:
		{
			TDualInfoTr* ptUms = (TDualInfoTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenDualChan_Cmd, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));			
// 			TDualInfo tPA;
// 			ConvertConfDualStreamFromUmsToStack(tPA, *ptUms);
// 			PA_SendConfCtrl(nAppID, nPaID, emPASendDualStream, (u8*)&tPA, sizeof(tPA));	
		}
		break;
	case evtp_cascade_OpenDualChan_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenDualChan_Ind, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
// 			TDualInfoAckTr* ptUms = (TDualInfoAckTr*)pBuf;
// 			TDualInfoAck tPA;
// 			tPA.m_bAccept = ptUms->m_bAccept;
// 			ConvertConfDualStreamFromUmsToStack(tPA.m_tDualInfo, ptUms->m_tDualInfo);
// 			PA_SendConfCtrl(nAppID, nPaID, emPASendDualStreamAck, (u8*)&tPA, sizeof(tPA));	
		}
		break;
	case evtp_Conf_StopRcvDual_Ind:
		{
			EmTPDualReason* ptUms = (EmTPDualReason*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopRcvDual_Ind, ConfID:%d, EpID:%d, CallID:%d, reason:%d\n", wConfID, wEpID, nPaID, *ptUms));
			
// 			EmDualReason tPA = CTpTypeAdpt::GetDualReason(*ptUms);		
// 			PA_SendConfCtrl(nAppID, nPaID, emPAStopRcvDualInd, (u8*)&tPA, sizeof(tPA));				
		}
		break;
	case evtp_Conf_DualFastUpdate_Ind:
		{
			BOOL32 tUms = *(BOOL32*)pBuf;
			tpLowDtl(Ums_Mdl_Stack, ">>>> evtp_Conf_DualFastUpdate_Ind, ConfID:%d, EpID:%d, CallID:%d, bSys:%d\n", wConfID, wEpID, nPaID, tUms);
//			PA_SendConfCtrl(nAppID, nPaID, emPADualStreamFastUpdate, NULL, 0);	
		}
		break;	
	case evtp_Conf_StartRcvDual_Ind:
		{
			TEpKeyEx tEx = *(TEpKeyEx*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartRcvDual_Ind, ConfID:%d, EpID:%d, CallID:%d, epid:%d, key:%s.\n", 
				wConfID, wEpID, nPaID, tEx.m_wEpID, tEx.m_achReserve));
//			PA_SendConfCtrl(nAppID, nPaID, emPAStartRcvDualInd, NULL, 0);
		}
		break;
	case evtp_Conf_SrcDualName_Ind:
		{			
			TTPAlias* ptUms = (TTPAlias*)pBuf;
			TEpKey* ptKey = (TEpKey*)((u8*)pBuf + sizeof(TTPAlias));
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_SrcDualName_Ind, ConfID:%d, EpID:%d, CallID:%d, Name:%s, dualID:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_abyAlias, ptKey->m_wEpID));
		
// 			TPAName tPA;
// 			tPA.SetAlias(ptUms->m_abyAlias);
// 			PA_SendConfCtrl(nAppID, nPaID, emPASrcDualNameInd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_StopSendDual_Ind:
		{
			TEpKey tUms = *(TEpKey*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopSendDual_Ind, ConfID:%d, EpID:%d, CallID:%d, epID:%d\n", wConfID, wEpID, nPaID, tUms.m_wEpID));			
// 			EmDualReason tPA = CTpTypeAdpt::GetDualReason(tUms);		
// 			PA_SendConfCtrl(nAppID, nPaID, emPAStopDualStream, (u8*)&tPA, sizeof(tPA));	
		}
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

static BOOL32 UmsSendPollConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	switch(nMsgType)
	{
	case evtp_Conf_StartPoll_cmd:
		{
			TPollCmdTr& tInfo = *(TPollCmdTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartPoll_cmd, ConfID:%d, EpID:%d, CallID:%d, Interval:%d\n"
				, wConfID, wEpID, nPaID, tInfo.m_wInterval));
			
// 			TPAPollCmd tPA;
// 			ConvertConfPollCmdFromUmsToStack(tPA, tInfo);			
// 			PA_SendConfCtrl(nAppID, nPaID, emPAConfStartPoll, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_StartPoll_ack:
		{
			TPollAckTr& tInfo = *(TPollAckTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartPoll_ack, ConfID:%d, EpID:%d, CallID:%d, ret:%d\n"
				, wConfID, wEpID, nPaID, tInfo.m_wReason));
			
// 			TPAPollAck tPA;
// 			ConvertConfPollAckFromUmsToStack(tPA, tInfo);	
// 			PA_SendConfCtrl(nAppID, nPaID, emPAConfStartPollAck, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_Poll_NodeChange:
		{
			TEpPathKey& tKey = *(TEpPathKey*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_Poll_NodeChange, ConfID:%d, EpID:%d, CallID:%d, NodeChange key:%s\n"
				, wConfID, wEpID, nPaID, tKey.m_szEpID));
			
// 			TPAPollNodeChange tPaPoll;
// 			strncpy(tPaPoll.m_achNodeInfo, tKey.m_szEpID, PA_NODECHANGEINFO);
// 			PA_SendConfCtrl(nAppID, nPaID, emPAConfPollNodeChange, (u8*)&tPaPoll, sizeof(tPaPoll));	
		}
		break;
	case evtp_Conf_Poll_End:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_Poll_End, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
//			PA_SendConfCtrl(nAppID, nPaID, emPAConfEndPoll, NULL, 0);	
		}
		break;
	case evtp_Conf_Poll_AskKeyFrame:
		{
			tpLowDtl(Ums_Mdl_Stack, ">>>> evtp_Conf_Poll_AskKeyFrame, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID);
//			PA_SendConfCtrl(nAppID, nPaID, emPAConfPollFastUpdate, NULL, 0);	
		}
		break;
	case evtp_Conf_PollDstName_Ind:
		{			
			TPollInfoNtf* ptUms = (TPollInfoNtf*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_PollDstName_Ind, ConfID:%d, EpID:%d, CallID:%d, Name:%s, vidSnd:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_tAlias.m_abyAlias, ptUms->m_nScreenNum));
		
// 			TPAName tPA;
// 			tPA.SetAlias(ptUms->m_abyAlias);
// 			PA_SendConfCtrl(nAppID, nPaID, emPAPollDstNameInd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_StartPoll_Ind:
		{
			EmTPPollResult tUms = *(EmTPPollResult*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartPoll_Ind, ConfID:%d, EpID:%d, ret:%d\n", wConfID, wEpID, tUms));
		}
		break;
	case evtp_Conf_StopPoll_Ind:
		{
			EmTPPollResult tUms = *(EmTPPollResult*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopPoll_Ind, ConfID:%d, EpID:%d, ret:%d\n", wConfID, wEpID, tUms));
		}
		break;
	case evtp_Conf_PollStatus_Notif:
		{
			TTpPollStat tUms = *(TTpPollStat*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_PollStatus_Notif, ConfID:%d, EpID:%d, Stat:%d\n", wConfID, wEpID, tUms.m_emStat));
		}
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

static BOOL32 UmsSendAudMixConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	switch(nMsgType)
	{
	case evtp_OpenAudChan_Cmd:
		{
			TAudChanCmd& tCmd = *(TAudChanCmd*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenAudChan_Cmd, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
		}
		break;
	case evtp_OpenAudChan_Ack:
		{
			TAudChanAck& tAck = *(TAudChanAck*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenAudChan_Ack, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
		}
		break;
	case evtp_OpenVidChan_Cmd:
		{
			TVidChanCmd& tCmd = *(TVidChanCmd*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenVidChan_Cmd, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
		}
		break;
	case evtp_OpenVidChan_Ack:
		{
			TVidChanAck& tAck = *(TVidChanAck*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenVidChan_Ack, ConfID:%d, EpID:%d, CallID:%d, m_wReason:%d\n"
				, wConfID, wEpID, nPaID, tAck.m_wReason));
		}
		break;
	case evtp_CloseVidChan_Cmd:
		{
			u16 wEpIDCmd = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_CloseVidChan_Cmd, ConfID:%d, EpID:%d, CallID:%d, wEpIDCmd:%d\n"
				, wConfID, wEpID, nPaID, wEpIDCmd));		
		}
		break;
	case evtp_UmsDiscussScreenStat_Notify:
		{
			TDiscussCasecadeNtfy* ptDisStat = (TDiscussCasecadeNtfy*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsDiscussScreenStat_Notify, ConfID:%d, EpID:%d, CallID:%d, bNtyDis:%d, obj(%d-%s,%d-%s,%d-%s), obj(%d-%s,%d-%s,%d-%s), obj(%d-%s,%d-%s,%d-%s)\n"
				, wConfID, wEpID, nPaID, ptDisStat->m_bIsDiscussModle, 
				ptDisStat->m_atDiscussObj[0].m_abIsVaild[0], ptDisStat->m_atDiscussObj[0].m_atEpAlias[0].m_abyAlias, 
				ptDisStat->m_atDiscussObj[0].m_abIsVaild[1], ptDisStat->m_atDiscussObj[0].m_atEpAlias[1].m_abyAlias,
				ptDisStat->m_atDiscussObj[0].m_abIsVaild[2], ptDisStat->m_atDiscussObj[0].m_atEpAlias[2].m_abyAlias,
				ptDisStat->m_atDiscussObj[1].m_abIsVaild[0], ptDisStat->m_atDiscussObj[1].m_atEpAlias[0].m_abyAlias,
				ptDisStat->m_atDiscussObj[1].m_abIsVaild[1], ptDisStat->m_atDiscussObj[1].m_atEpAlias[1].m_abyAlias,
				ptDisStat->m_atDiscussObj[1].m_abIsVaild[2], ptDisStat->m_atDiscussObj[1].m_atEpAlias[2].m_abyAlias,
				ptDisStat->m_atDiscussObj[2].m_abIsVaild[0], ptDisStat->m_atDiscussObj[2].m_atEpAlias[0].m_abyAlias,
				ptDisStat->m_atDiscussObj[2].m_abIsVaild[1], ptDisStat->m_atDiscussObj[2].m_atEpAlias[1].m_abyAlias,
				ptDisStat->m_atDiscussObj[2].m_abIsVaild[2], ptDisStat->m_atDiscussObj[2].m_atEpAlias[2].m_abyAlias));
			MdlHint(Ums_Mdl_Stack, ("  SpeacialEP:%d.\n", ptDisStat->m_atDiscussObj[emDiscussObjForSpeakerEp].m_wReserve));

			for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
			{	
				if (0 != ptDisStat->m_tEpAudInfo.m_awDiscussEpId[wIndex])
				{
					MdlHint(Ums_Mdl_Stack, ("  To Adapter... Ep:%d, (%d,%d,%d)\n", ptDisStat->m_tEpAudInfo.m_awDiscussEpId[wIndex],
						ptDisStat->m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][0], ptDisStat->m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][1],
						ptDisStat->m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][2]));
				}
			}
		}
		break;
	case evtp_UmsCnsSpeakerIndxAdjust_Notify:
		{
			TCnsSpeakerAdjust* ptUms = (TCnsSpeakerAdjust*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsCnsSpeakerIndxAdjust_Notify, ConfID:%d, EpID:%d, CallID:%d, childId:%d, Index:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_tKey.m_wEpID, ptUms->m_wSpeakerIndex));
		}
		break;
	case evtp_UmsDiscussFastUpdate_Req:
		{
			TDisAskKeyFrame* ptUms = (TDisAskKeyFrame*)pBuf;
			MdlLowDtl(Ums_Mdl_Stack, (">>>> evtp_UmsDiscussFastUpdate_Req, ConfID:%d, EpID:%d, CallID:%d, SrcEpID:%d, SrcScreenIndx:%d, bSys:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_wEpID, ptUms->m_wScreenNo, ptUms->m_bReqBySys));
		}
		break;
	default:
		return FALSE;	
	}
	return TRUE;
}

static BOOL32 UmsSendRollCallAndConfMixCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	switch(nMsgType)
	{

    ///////////////////点名////////////////////////
	case ev_UmsConfRollCallUpdate_Ind:
		{
			TConfRollCallInfo& tAck = *(TConfRollCallInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallUpdate_Ind, ConfID:%d, EpID:%d, CallID:%d ret:%d\n"
				, wConfID, wEpID, nPaID, tAck.m_emRet));
		}
		break;
	case ev_UmsConfRollCallNextEp_Ind:
		{
			TRollCallNextEpInfo& tAck = *(TRollCallNextEpInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallNextEp_Ind, ConfID:%d, EpID:%d, CallID:%d  Rcaller:%d Rtarget:%d ret:%d\n"
				, wConfID, wEpID, nPaID, tAck.m_wRollCaller, tAck.m_wCallTarget, tAck.m_emRet));
		}
		break;


	case ev_UmsConfRollCallUpdataList_Ind:
		{
			TUpdataRollCallListRes& tAck = *(TUpdataRollCallListRes*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallUpdataList_Ind, ConfID:%d, EpID:%d, CallID:%d \n"
				, wConfID, wEpID, nPaID));
		}
		break;

	case evtp_UmsRoll_PresentState_Notify:
		{
			TRollCallPresentStateMsg& tAck = *(TRollCallPresentStateMsg*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsRoll_PresentState_Notify, ConfID:%d, EpID:%d, CallID:%d  notifynum:%d\n"
				, wConfID, wEpID, nPaID, tAck.m_wValidNum));

		}
        break;

	case evtp_UmsRollCallScreenStat_Notify:
		{
			TRollCallCasecadeNtfy& tmsg = *(TRollCallCasecadeNtfy*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsRollCallScreenStat_Notify, ConfID:%d, EpID:%d, CallID:%d NotyType:%d mod:%d\n"
				, wConfID, wEpID, nPaID, tmsg.m_NotyType, tmsg.m_bIsRollCallModle));
		}
		break;
	case ev_UmsConfRollCallUpdate_Nty:
		{
			TConfRollCallInfo& tmsg = *(TConfRollCallInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallUpdate_Nty, ConfID:%d, EpID:%d, CallID:%d, ret:%d, curstate:%d, listnum:%d\n"
				, wConfID, wEpID, nPaID, tmsg.m_emRet,  tmsg.m_bStart,  tmsg.m_atRollCallMemList.m_wNum));
		}
		break;


	//////////////////////////会议混音////////////////////////////////

	case evtp_UMS_CNS_ConfAudMixMode_ind:
		{
			TUmsAudMixModeCmdRes& tAck = *(TUmsAudMixModeCmdRes*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_ConfAudMixMode_ind, ConfID:%d, EpID:%d, CallID:%d mod:%d ret:%d\n"
				, wConfID, wEpID, nPaID, tAck.m_emCmdMode, tAck.m_emRes));
		}
		break;

	case evtp_UMS_CNS_ConfAudMixList_ind:
		{
			TUmsAudMixListCmdRes& tAck = *(TUmsAudMixListCmdRes*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_ConfAudMixList_ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
		}
		break;

	case evtp_UMS_CNS_ConfAudMixMode_Notify:
		{
			TUmsAudMixInfo& tmsg = *(TUmsAudMixInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_ConfAudMixMode_Notify, ConfID:%d, EpID:%d, CallID:%d, mod:%d , oprnum:%d\n"
				, wConfID, wEpID, nPaID, tmsg.m_emMode, tmsg.m_tMixList.m_wNum));
		}
		break;

	case evtp_UMS_UMS_ConfAudMixMode_Notify:
		{
			TUmsAudMixCasecadeInfo& tmsg = *(TUmsAudMixCasecadeInfo*)pBuf;
			MdlLowDtl(Ums_Mdl_Stack, (">>>> evtp_UMS_UMS_ConfAudMixMode_Notify, ConfID:%d, EpID:%d, CallID:%d, mod:%d\n"
				, wConfID, wEpID, nPaID, tmsg.m_emMode));
		}
		break;

	case evtp_UMS_CNS_EpInAudMix_Notify:
		{
			BOOL32& bmsg = *(BOOL32*)pBuf;
			MdlLowDtl(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_EpInAudMix_Notify, ConfID:%d, EpID:%d, CallID:%d, epinaudmix:%d\n"
				, wConfID, wEpID, nPaID, bmsg));

		}
		break;

	default:
		return FALSE;
		
	}

	return TRUE;
}



u16 UmsSendCnsUIConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	switch(nMsgType)
	{
	case ev_UmsConfAMixUpdate_Ind:
		{
			TConfAuxMixInfo& tInd = *(TConfAuxMixInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfAMixUpdate_Ind, ConfID:%d, EpID:%d, CallID:%d, bStart:%d, emRet:%d\n"
				, wConfID, wEpID, nPaID, tInd.m_bStart, tInd.m_emRet));
		}
		break;
	case ev_UmsConfAMixUpdate_Nty:
		{
			TConfAuxMixInfo& tNty = *(TConfAuxMixInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfAMixUpdate_Nty, ConfID:%d, EpID:%d, CallID:%d, bStart:%d, bVacOn:%d\n"
				, wConfID, wEpID, nPaID, tNty.m_bStart, tNty.m_bVacOn));
		}
		break;
	case ev_UmsConfApplySpeaker_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			EmTpApplySpeakerRet& emRet = *(EmTpApplySpeakerRet*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfApplySpeaker_Ind, ConfID:%d, EpID:%d, CallID:%d, EmRet:%d\n"
				, wConfID, wEpID, nPaID, emRet));
		}
		break;
	case ev_UmsConfApplySpeaker_Nty:
		{
			TConfEpID& tAck = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfApplySpeaker_Nty, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
		}
		break;
	case ev_UmsConfMute_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfMute_Ind, ConfID:%d, EpID:%d, CallID:%d, bRet:%d\n"
				, wConfID, wEpID, nPaID, bRet));
		}
		break;
	case ev_UmsConfMute_Nty:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfMute_Nty, ConfID:%d, EpID:%d, CallID:%d, bRet:%d\n"
				, wConfID, wEpID, nPaID, bRet));
		}
		break;
	case ev_UmsConfQuiet_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfQuiet_Ind, ConfID:%d, EpID:%d, CallID:%d, bRet:%d\n"
				, wConfID, wEpID, nPaID, bRet));
		}
		break;
	case ev_UmsConfQuiet_Nty:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfQuiet_Nty, ConfID:%d, EpID:%d, CallID:%d, bRet:%d\n"
				, wConfID, wEpID, nPaID, bRet));
		}
		break;
	case ev_UmsInviteCnsByAlias_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TTpCallAddr& tInd = *(TTpCallAddr*)pBuf;
			EmCnsCallReason& emRet = *(EmCnsCallReason*)(pByBuf + sizeof(TTpCallAddr));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsInviteCnsByAlias_Ind, ConfID:%d, EpID:%d, alias:%s-%s CallID:%d, reason:%d\n"
				, wConfID, wEpID, tInd.m_tAlias.m_abyAlias, tInd.m_tE164.m_abyAlias, nPaID, emRet));
		}
		break;
	case ev_UmsHangupCns_Ind:
	case ev_UmsInviteCnsByEpId_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			u16& wInd = *(u16*)pBuf;
			EmCnsCallReason& emRet = *(EmCnsCallReason*)(pByBuf + sizeof(u16));
			
			if ( nMsgType ==  ev_UmsInviteCnsByEpId_Ind )
			{
				MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsInviteCnsByEpId_Ind, ConfID:%d, EpID:%d, CallID:%d, CnsCallReason:%d\n"
				, wConfID, wEpID, nPaID, emRet));
			}
			else
			{
				MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsHangupCns_Ind, ConfID:%d, EpID:%d, CallID:%d, CnsCallReason:%d\n"
				, wConfID, wEpID, nPaID, emRet));
			}
		}
		break;
	case ev_UmsUpdateConfTurnlist_Nty:
		{
			TTpPollListNtfy& tInd = *(TTpPollListNtfy*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsUpdateConfTurnlist_Nty, ConfID:%d, EpID:%d, CallID:%d, TimeInteval:%d, TotalNum:%d, CurNum:%d\n"
				, wConfID, wEpID, nPaID, tInd.m_wInterval, tInd.m_wTotalNum, tInd.m_wCurNum));
		}
		break;
	case ev_UmsChairConfInfo_Nty:
		{
			TChairConfInfo& tInd = *(TChairConfInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsChairConfInfo_Nty, ConfID:%d, EpID:%d, CallID:%d, BeginTime:%d, ChairName:%s, ConfName:%s\n"
				, wConfID, wEpID, nPaID, tInd.m_tBeginTime, tInd.m_tChairName.m_abyAlias, tInd.m_tConfName.m_abyAlias));
		}
		break;
	case ev_UmsAudMixStatus_Nty:
		{
			TAudMixStat& tInd = *(TAudMixStat*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsAudMixStatus_Nty, ConfID:%d, EpID:%d, CallID:%d, AudMixEp:%d, bStart:%d, MixStatus:%d\n"
				, wConfID, wEpID, nPaID, tInd.m_wEpID, tInd.m_bIsStart, tInd.m_emMixStatus));
		}
		break;
	case ev_UmsConfStartDual_Cmd:
		{
			TConfEpID& tUms = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfStartDual_Cmd, ConfID:%d, EpID:%d, CallID:%d, DualEp:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wEpID));
		}
		break;
	case ev_UmsConfStartDual_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			EmTPDualReason& eReason = *(EmTPDualReason*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfStartDual_Ind, ConfID:%d, EpID:%d, CallID:%d, DualEp:%d, Reason:%d\n"
				, wConfID, wEpID, nPaID, tInd.m_wEpID, eReason));
		}
		break;
	case ev_UmsConfStopDual_Cmd:
		{
			TConfEpID& tUms = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfStopDual_Cmd, ConfID:%d, EpID:%d, CallID:%d, DualEp:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wEpID));
		}
		break;
	case ev_UmsConfStopDual_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			EmTPDualReason& eReason = *(EmTPDualReason*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> emPATppConfStopDual_Ind, ConfID:%d, EpID:%d, CallID:%d, DualEp:%d, Reason:%d\n"
				, wConfID, wEpID, nPaID, tInd.m_wEpID, eReason));
		}
		break;
	case ev_UmsConfDualEp_Nty:
		{
			TConfEpID& tUms = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfDualEp_Nty, ConfID:%d, EpID:%d, CallID:%d, DualEp:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wEpID));
		}
		break;
	case ev_UmsAudMixDisListOpr_Ind:
		{
			TDiscussListOpr& tUms = *(TDiscussListOpr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsAudMixDisListOpr_Ind, ConfID:%d, EpID:%d, CallID:%d, wNum:%d, OprType:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wNum, tUms.m_emOprType));
		}
		break;
	case ev_UmsConfAMixVacSwitchInd:
		{
			TConfAuxMixVacOpr& tUms = *(TConfAuxMixVacOpr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfAMixVacSwitchInd, ConfID:%d, EpID:%d, CallID:%d, bVacOn:%d, wRet:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_bVacOn, tUms.m_wOprRet));
		}
		break;
	case ev_UmsCommonReasonToUI_Ind:
		{
			TTPUmsReasonInd& tUms = *(TTPUmsReasonInd*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsCommonReasonToUI_Ind, ConfID:%d, EpID:%d, CallID:%d, DstEPID:%d, Reason:%d, Reserve1:%d, Reserve2:%d, Reserve3:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wEpID, tUms.m_dwReason, tUms.m_dwReserve1, tUms.m_dwReserve2, tUms.m_dwReserve3));
		}
		break;
	case ev_UMS_CNC_RervesBrdVmp_Ind:
		{
			TRersvesEqpRsp& tUms = *(TRersvesEqpRsp*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_RervesBrdVmp_Ind, ConfID:%d, EpID:%d, CallID:%d, Ret:%d, EqpID:%d, Rerves:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_emRet, tUms.m_tRersvesReq.m_tEqp.m_byEqpID, tUms.m_tRersvesReq.m_bRersves));
		}
		break;
	case ev_UMS_CNC_BrdVmp_Ind:
		{
			TBrdVmpRsp& tUms = *(TBrdVmpRsp*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_BrdVmp_Ind, ConfID:%d, EpID:%d, CallID:%d, Ret:%d, EqpID:%d, bBrd:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_emRet, tUms.m_tReq.m_tEqp.m_byEqpID, tUms.m_tReq.m_bBrd));
		}
		break;
	case ev_UMS_CNC_SetBrdVmp_Ind:
		{
			TSetVmpInfoRsp& tUms = *(TSetVmpInfoRsp*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SetBrdVmp_Ind, ConfID:%d, EpID:%d, CallID:%d, Ret:%d, EqpID:%d, Style:%d, ChnNum:%d, speakerIndx:%d, dualIndx:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_emRet, tUms.m_tReq.m_tEqp.m_byEqpID, tUms.m_tReq.m_tStyle.m_emVmpStyle, tUms.m_tReq.m_tStyle.m_wChnlNum,
				tUms.m_tReq.m_tStyle.m_wSpeakerIndx, tUms.m_tReq.m_tStyle.m_wDualIndx));
		}
		break;
	case ev_UMS_CNC_BrdVmp_Ntfy:
		{
			TBrdVmpResArray tArray = *(TBrdVmpResArray*)(pBuf);

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_BrdVmp_Ntfy, ConfID:%d, EpID:%d, CallID:%d, vmpNum:%d\n", wConfID, wEpID, nPaID, tArray.m_wNum));

			TBrdVmpResNtfy* tInd;
			for ( u16 wIndex = 0; wIndex < tArray.m_wNum; wIndex ++ )
			{
				tInd = &tArray.m_atVmpNtfy[wIndex];
				MdlLowDtl(Ums_Mdl_Stack, ("	oprtype:%d, auto:%d, stat:%d, eqpID:%d, style:%d, channum:%d, speakerindx:%d, dualindx:%d\n", 
					tInd->m_emOpr, tInd->m_bVmpAuto, tInd->m_emStat, tInd->m_tEqpInfo.m_byEqpID, tInd->m_tVmpStyle.m_emVmpStyle, tInd->m_tVmpStyle.m_wChnlNum,
					tInd->m_tVmpStyle.m_wSpeakerIndx, tInd->m_tVmpStyle.m_wDualIndx));
			}
		}
		break;
	case ev_UMS_UMS_VmpCasecade_Ntfy:
		{
			TVmpCasecadeNtfy& tUms = *(TVmpCasecadeNtfy*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_UMS_VmpCasecade_Ntfy, ConfID:%d, EpID:%d, CallID:%d, bBrdVmp:%d, emSpeakerVmp:%d, Alias:%s\n"
				, wConfID, wEpID, nPaID, tUms.m_bBrdVmp, tUms.m_emSpeakerVmpType, tUms.m_szBrdVmpAlias));
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
s8* GetNodeObj(EMScreenObj emObj);
u16 UmsSendConfCtrl( const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize )
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;

	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();

// 	MdlHint(Ums_Mdl_Stack, (">>>> UmsSendConfCtrl event:%d->%s, ConfID:%d, EpID:%d, CallID:%d\n"
// 		, nMsgType, GetEventNamebyID(nMsgType), tHandle.GetConfID(), tHandle.GetEpID(), nPaID));

	if (UmsSendDualConfCtrl(tHandle, nMsgType, pBuf, nSize))
	{
		NotifyMsgToAdapter(nMsgType, tHandle, pBuf, nSize);
		return TP_RET_OK;
	}
	if (UmsSendPollConfCtrl(tHandle, nMsgType, pBuf, nSize))
	{
		NotifyMsgToAdapter(nMsgType, tHandle, pBuf, nSize);
		return TP_RET_OK;
	}
	if (UmsSendAudMixConfCtrl(tHandle, nMsgType, pBuf, nSize))
	{
		NotifyMsgToAdapter(nMsgType, tHandle, pBuf, nSize);
		return TP_RET_OK;
	}
	if ( UmsSendCnsUIConfCtrl(tHandle, nMsgType, pBuf, nSize) )
	{
		NotifyMsgToAdapter(nMsgType, tHandle, pBuf, nSize);
		return TP_RET_OK;
	}

	if (UmsSendRollCallAndConfMixCtrl(tHandle, nMsgType, pBuf, nSize))
	{
		NotifyMsgToAdapter(nMsgType, tHandle, pBuf, nSize);
		return TP_RET_OK;
	}

	switch(nMsgType)
	{
	case evtp_Conf_EpCallInfo_Update:
		{	
			TConfNodeCallUpdateTrList& tUms = *(TConfNodeCallUpdateTrList*)pBuf;
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpCallInfo, (u8*)&tUms, tHandle, OUTSIGN);
			//MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_EpInfo_Update, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
		}
		break;
	case evtp_Conf_EpVidFeccInfo_Update:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_EpVidFeccInfo_Update, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
		}
		break;
	case evtp_Conf_EpChanInfo_Update:
		{
			TConfNodeChanUpdateTrList& tUms = *(TConfNodeChanUpdateTrList*)pBuf;
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpChanInfo, (u8*)&tUms, tHandle, OUTSIGN);
			//MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_EpInfo_Update_B2NEW, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
		}
		break;
	case evtp_Conf_EpInfo_Del:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_EpInfo_Del, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
		}
		break;
	case evtp_Conf_YouAreSeeing_Ind:
		{
			TSpeakerCapTr& tCap = *(TSpeakerCapTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_YouAreSeeing_Ind, ConfID:%d, EpID:%d, CallID:%d,  vidSnd:%d, audSnd:%d, IsSpeaker:%d, SpeakerID:%d, SpeakerAlias:%s, SpeakerIndx:%d\n"
				, wConfID, wEpID, nPaID, tCap.m_wVidSnd, tCap.m_wAudSnd, tCap.m_bIsSpeaker, tCap.m_wSpeakerID
				, tCap.m_tEpAlias.m_abyAlias, tCap.m_wSpeakerIndex));
		}
		break;
	case evtp_Conf_YouAreSeeingEx_Ind:
		{
			TTpYouAreSeeing& tCap = *(TTpYouAreSeeing*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_YouAreSeeingEx_Ind, ConfID:%d, EpID:%d, CallID:%d, bSpeaker:%d, (%s,%d,%d,%s), (%s,%d,%d,%s), (%s,%d,%d,%s)\n"
				, wConfID, wEpID, nPaID, tCap.m_bSpeaker, GetNodeObj(tCap.m_atObj[0].m_emObj), tCap.m_atObj[0].m_wVidNum, tCap.m_atObj[0].m_wAudNum, tCap.m_atObj[0].m_tAlias.m_abyAlias,
				GetNodeObj(tCap.m_atObj[1].m_emObj), tCap.m_atObj[1].m_wVidNum, tCap.m_atObj[1].m_wAudNum, tCap.m_atObj[1].m_tAlias.m_abyAlias,
				GetNodeObj(tCap.m_atObj[2].m_emObj), tCap.m_atObj[2].m_wVidNum, tCap.m_atObj[2].m_wAudNum, tCap.m_atObj[2].m_tAlias.m_abyAlias));
		}
		break;
	case evtp_Conf_IsChair_Notify:
		{			
			BOOL32 bIsChair = *(BOOL32*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_IsChair_Notify, ConfID:%d, EpID:%d, CallID:%d, bIsChair:%d\n"
				, wConfID, wEpID, nPaID, bIsChair));
		}
		break;
	case evtp_Conf_StatusInfo_Notify:
		{			
			TTPConfInfoNtfy* ptConf = (TTPConfInfoNtfy*)(pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StatusInfo_Notify, ConfID:%d, EpID:%d, CallID:%d, MeetingID:%d, Conf:%s, Chair:%s, vidNum:%d, audNum:%d, MixMotive:%d, SpeakOnline:%d.\n"
				, wConfID, wEpID, nPaID, ptConf->m_wConfID, ptConf->m_tConf.m_abyAlias, ptConf->m_tChair.m_abyAlias, ptConf->m_wChairVidSndCap, ptConf->m_wChairAudSndCap, ptConf->m_bMixMotive, ptConf->m_bSpeakOnline));		
		}
		break;
	case evtp_Conf_CnsSpeakerCascad_Notify:
		{
			TCnsSpeakerAdjust& tAdjust = *(TCnsSpeakerAdjust*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CnsSpeakerCascad_Notify, ConfID:%d, EpID:%d, CallID:%d, childId:%d, Index:%d\n"
				, wConfID, wEpID, nPaID, tAdjust.m_tKey.m_wEpID, tAdjust.m_wSpeakerIndex));
		}
		break;
	case evtp_Conf_MuteRemoteEp_Cmd:
		{
			TMuteRmtEpCmd* ptRmtEp = (TMuteRmtEpCmd*)(pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_MuteRemoteEp_Cmd, ConfID:%d, EpID:%d, CallID:%d, bMute:%d, DstID:%d\n"
				, wConfID, wEpID, nPaID, ptRmtEp->m_bMute, ptRmtEp->m_wEpID));
		}
		break;
	case evtp_Conf_MuteRemoteEp_Ind:
		{
			TMuteRmtEpInd* ptRmtEp = (TMuteRmtEpInd*)(pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_MuteRemoteEp_Ind, ConfID:%d, EpID:%d, CallID:%d, bMute:%d, childId:%d\n"
				, wConfID, wEpID, nPaID, ptRmtEp->m_bMute, ptRmtEp->m_tKeyID.m_wEpID));

		}
		break;
	case evtp_Conf_QuietRemoteEp_Cmd:
		{
			TQuietRmtEpCmd* ptRmtEp = (TQuietRmtEpCmd*)(pBuf);		
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_QuietRemoteEp_Cmd, ConfID:%d, EpID:%d, CallID:%d, Quiet:%d, DstID:%d\n"
				, wConfID, wEpID, nPaID, ptRmtEp->m_bQuiet, ptRmtEp->m_wEpID));

		}
		break;
	case evtp_Conf_QuietRemoteEp_Ind:
		{
			TQuietRmtEpInd* ptRmtEp = (TQuietRmtEpInd*)(pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_QuietRemoteEp_Ind, ConfID:%d, EpID:%d, CallID:%d, Quiet:%d, childId:%d\n"
				, wConfID, wEpID, nPaID, ptRmtEp->m_bQuiet, ptRmtEp->m_tKeyID.m_wEpID));
		}
		break;
	case evtp_Conf_CallExistEPTr_cmd:
		{
			u16 wRmtEp = *(u16*)(pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CallExistEPTr_cmd, ConfID:%d, EpID:%d, CallID:%d, CallNode:%d\n"
				, wConfID, wEpID, nPaID, wRmtEp));		
			
//			PA_SendConfCtrl(nAppID, nPaID, emPAConfCallCascadingOff, (u8*)&wRmtEp, sizeof(u16));
		}
		break;
	case evtp_Conf_DropEPTr_cmd:
		{
			TDropEpCmd* ptCmd = (TDropEpCmd*)(pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_DropEPTr_cmd, ConfID:%d, EpID:%d, CallID:%d, DstID:%d, del:%d\n"
				, wConfID, wEpID, nPaID, ptCmd->m_wEpID, ptCmd->m_bDel));			
		}
		break;
	case evtp_Conf_TvMonitor_Cmd:
		{			
			TTvMonitorCmdTr* ptUms = (TTvMonitorCmdTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_TvMonitor_Cmd, ConfID:%d, EpID:%d, CallID:%d, index:%d, dst:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_wIndex, ptUms->m_wEpID));
// 			TPATvMonitorCmd tPa;
// 			ConvertAddTvMonitorFromUmsToStack(tPa, *ptUms);
// 			PA_SendConfCtrl(nAppID, nPaID, emPAAddTvMonitorCmd, (u8*)&tPa, sizeof(tPa));
		}		
		break;
	case evtp_Conf_TvMonitor_Ind:
		{			
			TTvMonitorIndTr* ptUms = (TTvMonitorIndTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_TvMonitor_Ind, ConfID:%d, EpID:%d, CallID:%d, Index:%d, wEpID:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_wIndex, ptUms->m_wEpID));
		}
		break;
	case evtp_Conf_TvMonitor_stop:
		{			
			u16* ptUms = (u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_TvMonitor_stop, ConfID:%d, EpID:%d, CallID:%d, wIndex:%d\n", wConfID, wEpID, nPaID, *ptUms));
//			PA_SendConfCtrl(nAppID, nPaID, emPAStopMonitorCmd, (u8*)ptUms, sizeof(u16));
		}
		break;
	case evtp_Conf_AskKeyByScreen :
		{
			TAskKeyByScreenTr* ptUms = (TAskKeyByScreenTr*)pBuf;
			MdlLowDtl(Ums_Mdl_Stack, (">>>> evtp_Conf_AskKeyByScreen, ConfID:%d, EpID:%d, CallID:%d, wDstEp:%d, Screen:%d, bSys:%d, Type:%d\n", 
					wConfID, wEpID, nPaID, ptUms->m_wEpID, ptUms->m_wScreenIndex, ptUms->m_bReqBySys, ptUms->m_dwAskType));
		}
		break;
	case evtp_Conf_ChairCap_Notify:
		{			
			TChairInfoTr* ptUms = (TChairInfoTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_ChairCap_Notify, ConfID:%d, EpID:%d, CallID:%d, index:%d\n", wConfID, wEpID, nPaID, ptUms->m_wSpeakerIndex));
		}
		break;

	case evtp_Conf_CnsList_Notify:
		{
			TConfCnsInfo* ptUms = (TConfCnsInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CnsList_Notify, ConfID:%d, EpID:%d, CallID:%d, Num:%d->( %d,%d,%d), type(%d,%d,%d), scrnum(%d,%d,%d)\n", 
				wConfID, wEpID, nPaID, ptUms->m_wNum, ptUms->m_tConfCnsList[0].m_wEpID, ptUms->m_tConfCnsList[1].m_wEpID, ptUms->m_tConfCnsList[2].m_wEpID
				, ptUms->m_tConfCnsList[0].m_emEpType, ptUms->m_tConfCnsList[1].m_emEpType, ptUms->m_tConfCnsList[2].m_emEpType, 
				ptUms->m_tConfCnsList[0].m_wSpeakerNum, ptUms->m_tConfCnsList[1].m_wSpeakerNum, ptUms->m_tConfCnsList[2].m_wSpeakerNum));
		}
		break;
	case evtp_UMS_CNS_VidFeccInfoNty:
		{
			TConfVidFeccInfo* ptList = (TConfVidFeccInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_VidFeccInfoNty, ConfID:%d, EpID:%d, CallID:%d, Num:%d, (%d|%d|%d), (%d|%d|%d), (%d|%d|%d)\n", 
				wConfID, wEpID, nPaID, ptList->m_wNum, 
				ptList->m_atVidFeccList[0].m_wEpID, ptList->m_atVidFeccList[0].m_bAllowFecc, ptList->m_atVidFeccList[0].m_byVidno,
				ptList->m_atVidFeccList[1].m_wEpID, ptList->m_atVidFeccList[1].m_bAllowFecc, ptList->m_atVidFeccList[1].m_byVidno,
				ptList->m_atVidFeccList[2].m_wEpID, ptList->m_atVidFeccList[2].m_bAllowFecc, ptList->m_atVidFeccList[2].m_byVidno));

		}
		break;
	case evtp_Conf_ViewLocal_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_ViewLocal_Cmd, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
//			PA_SendConfCtrl(nAppID, nPaID, emPAViewLocal, NULL, 0);
		}		
		break;
	case evtp_Conf_CancelViewLocal_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CancelViewLocal_Cmd, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
//			PA_SendConfCtrl(nAppID, nPaID, emPACancelViewlocal, NULL, 0);
		}		
		break;
	case evtp_cascade_GetVid_cmd:
		{			
			TViewCmdTr* ptUms = (TViewCmdTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_GetVid_cmd, ConfID:%d, EpID:%d, dst:%d, index:%d\n", wConfID, wEpID, ptUms->m_wEpID, ptUms->m_wIndex));
		}
		break;
	case evtp_cascade_GetVid_ack:
		{			
			TViewAckTr* ptUms = (TViewAckTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_GetVid_ack, ConfID:%d, EpID:%d, index:%d, ret:%d\n", wConfID, wEpID, ptUms->m_wIndex, ptUms->m_emRes));
		}
		break;
	case evtp_cascade_StopGetVid_cmd:
		{
			u16 tUms = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_StopGetVid_cmd, ConfID:%d, EpID:%d, chan:%d\n", wConfID, wEpID, tUms));
		}
		break;

	case evtp_Conf_AdjustFrameRate:
		{ 
			TAdjustFrameRate tUms = *(TAdjustFrameRate*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_AdjustFrameRate, ConfID:%d, EpID:%d, DstEp:%d, FrameRate:%d\n"
															, wConfID, wEpID, tUms.m_wEpID, tUms.m_wFrameRate));
		}
		break;
	case evtp_Conf_AdjustVidRes:
		{ 
			TAdjustVidRes tUms = *(TAdjustVidRes*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_AdjustVidRes, ConfID:%d, EpID:%d, DstEp:%d, VidRes:%d\n"
															, wConfID, wEpID, tUms.m_wEpID, tUms.m_dwVidRes));
		}
		break;
	case evtp_Conf_FlowCtrol:
		{ 
			TFlowControl tUms = *(TFlowControl*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_FlowCtrol, ConfID:%d, EpID:%d, DstEp:%d, Band:%d\n"
				, wConfID, wEpID, tUms.m_tEpKey.m_wEpID, tUms.m_wBand));
		}
		break;
	case evtpH323_Conf_MultipleConference_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtpH323_Conf_MultipleConference_Ind, ConfID:%d, EpID:%d\n", wConfID, wEpID));
		}
		break;
	case evtp_Conf_MultConf_Notify:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_MultConf_Notify, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
		}
		break;
	case evtp_Conf_CancelMultConf_Notify:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CancelMultConf_Notify, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));			
		}
		break;
	case evtp_Conf_JoinConf_Notify:
		{
			TConfEpIDInfo* ptUms = (TConfEpIDInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_JoinConf_Notify, ConfID:%d, EpID:%d, DstID:%d, name:%s\n"
				, wConfID, wEpID, ptUms->m_wEpID, ptUms->m_tAlias.m_abyAlias));
		}
		break;
	case evtp_Conf_LeftConf_Notify:
		{
			TConfEpIDInfo* ptUms = (TConfEpIDInfo*)pBuf;			
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_LeftConf_Notify, ConfID:%d, EpID:%d, DstID:%d, name:%s\n"
				, wConfID, wEpID, ptUms->m_wEpID, ptUms->m_tAlias.m_abyAlias));
		}
		break;
	case evtp_cascade_OpenChairChan_cmd:
		{
			TCascadeOpenChanCmd* ptUms = (TCascadeOpenChanCmd*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenChairChan_cmd, ConfID:%d, EpID:%d, dst:%d\n", wConfID, wEpID, ptUms->m_wEpID));
		}
		break;
	case evtp_cascade_OpenChairChan_ack:
		{
			TCascadeOpenChanAck* ptUms = (TCascadeOpenChanAck*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenChairChan_ack, ConfID:%d, EpID:%d, ret:%d\n", wConfID, wEpID, ptUms->m_wEpID));
		}
		break;
	case evtp_Conf_StopRecPlay_Req:
		{
			u32 dwParam = 0;
			TP_SAFE_CAST(dwParam, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopRecPlay_Req Param:%d.\n", dwParam));
		}
		break;
	case evtp_Conf_RecPlayState_Nty:
		{
			TUpRecPlayState tState;
			TP_SAFE_CAST(tState, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_RecPlayState_Nty IsPlaying:%d, DualPlaying:%d, FileName:%s.\n",
									tState.m_bIsPlayIng, tState.m_bIsDualPlayIng, tState.m_achFileName));
		}
		break;
	case ev_UMS_CNC_SelView_Ntfy:
		{
			TTPSelViewNtfy tNtfy;
			TP_SAFE_CAST(tNtfy, (u8*)pBuf);

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SelView_Ntfy confID:%d, epId:%d, (%d,%d; %d,%d; %d,%d;)\n", 
				tNtfy.m_wConfID, tNtfy.m_wEpID, 
				tNtfy.m_atSelView[0].m_wDstID, tNtfy.m_atSelView[0].m_emType,
				tNtfy.m_atSelView[1].m_wDstID, tNtfy.m_atSelView[1].m_emType,
				tNtfy.m_atSelView[2].m_wDstID, tNtfy.m_atSelView[2].m_emType));
		}
		break;
	case ev_UMS_CNC_SelView_Ind:
		{
			TTPSelViewInd tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SelView_Ind EpID:%d Ret:%d, SelEpID:%d, ScrIndx:%d, DstID:%d\n",
				tHandle.GetEpID(), tInd.m_emRet, tInd.m_tSelView.m_wEpID, tInd.m_tSelView.m_wScreenIndx, tInd.m_tSelView.m_wDstID));
		}
		break;
	case ev_CNC_UMS_SelView_Req:
		{
			TTPSelViewReq tReq;
			TP_SAFE_CAST(tReq, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_CNC_UMS_SelView_Req EpID:%d bSel:%d, SelEpID:%d, ScrIndx:%d, DstID:%d, Type:%d.\n",
				tHandle.GetEpID(), tReq.m_bSel, tReq.m_wEpID, tReq.m_wScreenIndx, tReq.m_wDstID, tReq.m_emType));
		}
		break;
	case evtp_Conf_SuspendPoll_Ind:
		{
			u32 dwRet;
			TP_SAFE_CAST(dwRet, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_SuspendPoll_Ind EpID:%d Ret:%d.\n", tHandle.GetEpID(), dwRet));
		}
		break;
	case evtp_Conf_CasecadePollEp_Req:
		{
			TCasecadePollEpReq tReq;
			TP_SAFE_CAST(tReq, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CasecadePollEp_Req EpID:%d bCreate:%d, EpID:%d, Rtp(%d, %d, %d).\n",
				tHandle.GetEpID(), tReq.m_bCreate, tReq.m_wEpID, tReq.m_atPollAddr[0].GetPort(), tReq.m_atPollAddr[1].GetPort(), tReq.m_atPollAddr[2].GetPort()));
		}
		break;
	case evtp_Conf_CasecadePollEp_Rsp:
		{
			TCasecadePollEpRsp tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CasecadePollEp_Rsp EpID:%d bCreate:%d, EpID:%d, Rtp(%d, %d, %d) Ret:%d.\n",
				tHandle.GetEpID(), tRsp.m_tReq.m_bCreate, tRsp.m_tReq.m_wEpID, 
				tRsp.m_tReq.m_atPollAddr[0].GetPort(), tRsp.m_tReq.m_atPollAddr[1].GetPort(), tRsp.m_tReq.m_atPollAddr[2].GetPort(), tRsp.m_emRes));
		}
		break;
	case ev_UmsUpdateConfTurnlist_Ind:
		{
			TTpPollListInd tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsUpdateConfTurnlist_Ind EpID:%d ConfID:%d, Flag:%d, Ret:%d.\n",
								tHandle.GetEpID(), tRsp.m_wConfID, tRsp.m_nFlag, tRsp.m_wRet));
		}
		break;

	case ev_CNC_UMS_SaveVmpCfg_Cmd:
		{
			TTpVmpMemberCfg tCfg;
			TP_SAFE_CAST(tCfg, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_CNC_UMS_SaveVmpCfg_Cmd EpID:%d ConfID:%d, Style:%d, Num:%d.\n",
				tHandle.GetEpID(), tCfg.m_wConfID, tCfg.m_emStyle, tCfg.m_wEpNum));
		}
		break;

	case ev_UMS_CNC_SaveVmpCfg_Ind:
		{
			TTpVmpMemberCfgInd tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SaveVmpCfg_Ind EpID:%d ConfID:%d, Ret:%d.\n",tHandle.GetEpID(), tInd.m_wConfID, tInd.m_bRet));
		}
		break;
	case ev_GetVid_Req:
		{
			TGetVidInfo tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Req EpID:%d GetVidIndx:%d\n",tHandle.GetEpID(), tInfo.m_tBaseInfo.m_wHandle));
		}
		break;
	case ev_GetVid_Res:
		{
			TGetVidInfoRes tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Res EpID:%d GetVidIndx:%d\n",tHandle.GetEpID(), tInfo.m_tInfo.m_tBaseInfo.m_wHandle));
		}
		break;
	case ev_GetVid_Stop_Req:
		{
			TGetVidBaseInfo tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Stop_Req EpID:%d GetVidIndx:%d\n",tHandle.GetEpID(), tInfo.m_wHandle));
		}
		break;
	case ev_GetVid_Stop_Res:
		{
			TStopGetVid tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Stop_Res EpID:%d GetVidIndx:%d\n",tHandle.GetEpID(), tInfo.m_tInfo.m_wHandle));
		}
		break;


	case evtp_QtQueryAlias_rsp:
		{
             MdlHint(Ums_Mdl_Stack, (">>>> evtp_QtQueryAlias_rsp \n"));
		}
		break;
	case evtp_UMS_CNS_SendFecc_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_SendFecc_Cmd \n"));
		}
		break;

	case evtp_MediaKey_Nty:
		{
			TTPMediaKeyInfo tTpInfo;
			TP_SAFE_CAST(tTpInfo,(u8*)pBuf);
			MdlHint(Ums_Mdl_Stack,(">>> evtp_MediaKey_Nty ConfID:%d, EpID:%d, dwhandle:%d,QtFlag:%u,Frequency:%d,wIndex:%d.\n", wConfID, wEpID
				, tTpInfo.m_dwHandle,tTpInfo.m_dwQtFlag,tTpInfo.m_emKeyFrequency, tTpInfo.m_wIndex));
		}
		break;

	case evtp_QtSetConfInfo_Cmd:
		{
			BOOL32 bChairConf;
			TP_SAFE_CAST( bChairConf, (u8*)pBuf );
			BOOL32 bReset;
			TP_SAFE_CAST( bReset, (u8*)pBuf + sizeof(BOOL32) );
			
			MdlHint( Ums_Mdl_Stack, (">>>>evtp_QtSetConfInfo_Cmd ConfID->%d, ChairConf->%d, Reset->%d\n",
				    tHandle.GetConfID(), bChairConf, bReset) );
		}
		break;

	default:
		{
			MdlError(Ums_Mdl_Stack, ("  >> UmsSendConfCtrl failed. unkonw msg type. ConfID:%d, epID:%d, event:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType));
		}
		break;
	}
	NotifyMsgToAdapter(nMsgType, tHandle, pBuf, nSize);
	return TP_RET_OK;
}

void UmsReqRegInfo(const TUmsHandle& tHandle, TUmsSipRegCfg& tRegCfg, const EmGetRegInfoType& emType, u32 dwSipHandle, u32 dwGkHandle)
{
	if (tHandle.m_dwAdapteID != 0)
	{
		CTpMsg cMsg;	
		cMsg.SetEvent(ev_UmsGetRegInfo_Req);
		cMsg.SetBody(&tHandle, sizeof(tHandle));
		cMsg.CatBody(&tRegCfg, sizeof(tRegCfg));
		cMsg.CatBody(&emType, sizeof(emType));
		cMsg.CatBody(&dwSipHandle, sizeof(u32));
		cMsg.CatBody(&dwGkHandle, sizeof(u32));
		cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));

		if (0 == dwSipHandle)
		{
			TRegPackInfoEx tPackInfo;
			tPackInfo.m_emEndpointType = emTPEndpointTypeUMS;
			tPackInfo.m_emType = emType;
			TUmsRegPackEx tInfo;
			tInfo.m_bIsEnd = TRUE;
			tInfo.m_wSize = 0;

			CTpMsg cMsg;
			cMsg.SetEvent(ev_UmsGetRegInfo_UmsRspEx);
			cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
			cMsg.CatBody(&tPackInfo, sizeof(TRegPackInfoEx));
			cMsg.CatBody(&tInfo, sizeof(TUmsRegPackEx));
			cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
		}

		if (0 == dwGkHandle)
		{
			TTPMtRegInfo tInfo;
			tInfo.m_wListNum = 0;
			tInfo.m_bIsEnd = TRUE;

			CTpMsg cMsg;
			cMsg.SetEvent(ev_UmsGetGkRegInfo_MtRsp);
			cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
			cMsg.CatBody(&emType, sizeof(EmGetRegInfoType));
			cMsg.CatBody(&tInfo, sizeof(TTPMtRegInfo));
			cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
		}	
	}
	else
	{
		TTPSipRegPackInfo tSipPack;
		TTPSipRegInfo tRegInfo;

		CTpMsg cMsg;	
		cMsg.SetEvent(ev_UmsGetRegInfo_Rsp);
		cMsg.SetBody(&tHandle, sizeof(tHandle));
		cMsg.CatBody(&tSipPack, sizeof(tSipPack));
		cMsg.CatBody(&emType, sizeof(emType));
		cMsg.CatBody(&tRegInfo, sizeof(tRegInfo));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
	}
}

//gk注册
void UmsGkRegister(const TUmsHandle& tHandle, TRegCfg& tRegCfg, u16 wAliasNum)
{
	if (tHandle.m_dwAdapteID == 0)
	{
		MdlError(Ums_Mdl_Stack, ("<< UmsGkRegister unknow adapter! nAppId:%d, pRegHandle:0x%x\n", tHandle.handAppCall, tHandle.handPaCall));
		TCnsRegRetResult tRetInfo;
		tRetInfo.m_emReson = tp_CnsRegRet_SysError;		
		NotifyMsgToCall(evtp_ums_323_unreg_ret, tHandle, &tRetInfo, sizeof(tRetInfo));
		return;
	}
	
	MdlHint(Ums_Mdl_Stack, ("UmsGkRegister PACall:0x%x, Used:%d, RegIp:"TPIPFORMAT", RegPort:%d, wExpire:%d, adapter:%d\n"
		, tHandle.handPaCall, tRegCfg.m_bUsed, Tpu32ToIP(tRegCfg.m_tGKAddress.m_dwIP), tRegCfg.m_tGKAddress.m_wPort, 
		tRegCfg.m_nTimeToLive, tHandle.m_dwAdapteID));

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_gk_Register_Req);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tRegCfg, sizeof(tRegCfg));
	cMsg.CatBody(&wAliasNum, sizeof(wAliasNum));
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));
}

//注册
void UmsRegister(const TUmsHandle& tHandle, TUmsSipRegCfg& tRegCfg, TTPAlias atAlias[], u16 wAliasNum)
{	
	if (tHandle.m_dwAdapteID == 0)
	{
		MdlError(Ums_Mdl_Stack, ("<< UmsRegister unknow adapter! nAppId:%d, pRegHandle:0x%x\n", tHandle.handAppCall, tHandle.handPaCall));
		TCnsRegRetResult tRetInfo;
		tRetInfo.m_emReson = tp_CnsRegRet_SysError;		
		NotifyMsgToCall(evtp_ums_reg_ret, tHandle, &tRetInfo, sizeof(tRetInfo));
		return;
	}

	MdlHint(Ums_Mdl_Stack, ("UmsRegister PACall:0x%x, Used:%d, QtID:%d, RegIp:"TPIPFORMAT", RegPort:%d, wExpire:%d, Hostaddr:"ADDRPORT_FORMAT", adapter:%d\n"
		, tHandle.handPaCall, tRegCfg.bUsed, tRegCfg.m_dwQTId, Tpu32ToIP(tRegCfg.dwRegIP), tRegCfg.wRegPort, tRegCfg.wExpire, ADDRNET(tRegCfg.m_atAdaptAddr[0]), tHandle.m_dwAdapteID));

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_Register_Req);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tRegCfg, sizeof(tRegCfg));
	cMsg.CatBody(&wAliasNum, sizeof(wAliasNum));
	for (u16 wIndex = 0; wIndex < wAliasNum; ++wIndex)
	{
		cMsg.CatBody(&atAlias[wIndex], sizeof(TTPAlias));
	}
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));

	//PA_Register(tHandle.handAppCall, &tPARegCfg, (void*)tHandle.handPaCall);
}


void UmsUnregister(const TUmsHandle& tHandle, EmRegType emRegType)
{
	EmTpRegType emType = em_sip_reg;
	switch (emRegType)
	{
	case em_Sip_reg_type:
		{
			emType = em_sip_reg;
			break;
		}

	case em_Gk_reg_type:
		{
			emType = em_323_reg;
			break;
		}
	}
	MdlHint(Ums_Mdl_Stack, ("UmsUnregister PACall:0x%x, RegType:%d\n", tHandle.handPaCall, emRegType));
	NotifyMsgToAdapter(ev_UnRegister_Req, tHandle, &emType, sizeof(EmTpRegType));
	//PA_UnRegister( tHandle.handAppCall, (void*)tHandle.handPaCall );
}

u16 UmsCallSendMcuCtrl( const TUmsHandle& tHandle, const TUmsMcuChan& tMcuChan, const s32 nMsgType, const void *pBuf, const s32 nSize )
{
	if (tHandle.m_dwAdapteID == 0)
	{
		MdlError(Ums_Mdl_Call, ("UmsCallSendMcuCtrl failed! event:%d->%s\n", nMsgType, GetEventNamebyID(nMsgType)));
		return TP_RET_ERROR;
	}

	s32 nAppCall = tHandle.handAppCall;
	s32 nPaCall = tHandle.handPaCall;
	
	s32 hChan = tMcuChan.m_hMcuChan;
	s32 hAppChan = tMcuChan.m_hMcuAppChan;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	tpLowHint(Ums_Mdl_Stack, ">>>> UmsCallSendMcuCtrl event(%d-%s), Conf:%d, Ep:%d, PaCall:%d, hChan:%d, hAppChan:%d.\n", 
		nMsgType, GetEventNamebyID(nMsgType), wConfID, wEpID, nPaCall, hChan, hAppChan);
	
// 	switch(nMsgType)
// 	{
// 	default:
// 		{
// 			tpError(Ums_Mdl_Stack, "  UmsCallSendMcuCtrl unkonw event! event(%d-%s), Conf:%d, Ep:%d, PaCall:%d, hChan:%d, hAppChan:%d.\n", 
// 				nMsgType, GetEventNamebyID(nMsgType), wConfID, wEpID, nPaCall, hChan, hAppChan);
// 		}
// 		break;
// 	}

	CTpMsg cMsg;	
	cMsg.SetEvent((u16)nMsgType);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tMcuChan, sizeof(tMcuChan));
	if (NULL != pBuf)
	{
		cMsg.CatBody(pBuf, (u16)nSize);
	}
	cMsg.Post(UMS_SIPADAPTER_APP_INST, tHandle.m_dwAdapteID, UMS_CALL_APP_INST(tHandle.GetConfID()));

	return TP_RET_OK;
}


void UmsSetQTEncryptInfo( u16 wEvent, const TUmsHandle& tHandle, const void* pBuf, u16 wSize )
{
	MdlHint( Ums_Mdl_Stack, ("UmsSetQTEncryptInfo\n") );
	NotifyMsgToAdapter( wEvent, tHandle, pBuf, wSize );
}
