#include "handlecallservice.h"
#include "umscommonstruct.h"
#include "umsobject.h"
#include "umsserver.h"
#include "handleconftemplateservice.h"
#include "handletoolservice.h"
#include "umsxmltype.h"
#include "tpstruct.h"
#include "handleregservice.h"

#include "innereventumsserver.h"
#include "innereventumscall.h"
#include "eventoutumsconftemplate.h"

// 外部消息
#include "eventoutumscall.h"
#include "eventoutsipadapter.h"
#include "eventoutumsselview.h"
#include "eventoutumsbrdvmp.h"


using namespace UmsTpmsg;


#define VALID_CONF_ID(ID)  (ID <= TP_UMS_MAX_CONFNUM && ID >= 1)
#define MsgFrom(wAppID) AID_UMSUE_APP == wAppID ? "UE" : "CallMgr"

CUmsCallHandleService::CUmsCallHandleService(CTpObject* pcObjec)
:CTpHandler(pcObjec)
{
	
}


CUmsCallHandleService::~CUmsCallHandleService()
{
	
}


BOOL32 CUmsCallHandleService::Handler( CTpMsg *const ptMsg )
{
	u16 wEvent = ptMsg->GetEvent();
	u8* pData = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();
	
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());


	switch( wEvent ) 
	{
		//从呼叫过来的消息
	case evtp_UmsConfDisConnect:
		EventStartConfTemplateFailed(pData, wDataSize);
		break;
	case evtp_StartConfTemplate_Ret:
		EventStartConfRet(pData,wDataSize);
		break;
	case evtp_UmsConfIncoming:
		EventCallIncoming(pData, wDataSize);
		break;
	case evtp_UmsConfCreateMeetingMsg:
		EventCallCreateMeeting(pData, wDataSize);
		break;
	case evtp_UpdateConfTurnlist_Notify:	
		EventUpdateConfTurnList(wEvent, pData, wDataSize);
		break;
	case evtp_DelConflist_Notify:
		EventDelConfNotify(ptMsg);
		break;
	case evtp_AuxMixInfo_Notify:
		EventAuxMixInfoNotify(wEvent, pData, wDataSize);
		break;
	case evtp_CallEP_result:
		EventCallEpResult(wEvent, pData, wDataSize);
		break;
	case evtp_ApplySpeaker_result:
		EventApplySpeakerResult(wEvent, pData, wDataSize);
		break;
	case evtp_StartDual_Ind:
		EventStartDualInd(wEvent, pData, wDataSize);
		break;
	case evtp_ChairConfInfo_Notify:
		EventChairConfInfoNotify(wEvent, pData, wDataSize);
		break;

	case evtp_UpdateConfCnsList_Notify:
		EventUpdateConfCnsListNotify(wEvent, pData, wDataSize);
		break;
	case evtp_VidFeccMsg_Nty:
		EventFeccVidListNotify(wEvent, pData, wDataSize);
		break;
	case evtp_AddConfList_Notify:
		EventAddConfListNotify(wEvent, pData, wDataSize);
		break;
	case evtp_DualEp_Notify:
		EventDualEpNotify(wEvent, pData, wDataSize);
		break;
	case evtp_SpeakerChange_Notify:
		EventSpeakerChangeNotify(wEvent, pData, wDataSize);
		break;
	case evtp_MuteEp_Ind:
		EventMuteEpInd(wEvent, pData, wDataSize);
		break;
	case evtp_QuietEp_Ind:
		EventQuietEpInd(wEvent, pData, wDataSize);
		break;
	case evtp_ConfAllEpQuietMuteStatus_Nty:
		EventAllEpQuietMuteStatusNotify(wEvent, pData, wDataSize);
		break;
	case evtp_HungUp_Conf_Reason:
		EventHungUpConfReasonToUI(wEvent, pData, wDataSize);
		break;
	case evtp_UmsCommonReasonToUI_Ind:
		EventCommReasonUIInd(wEvent, pData, wDataSize);
		break;
	case evtp_DropEp_Ind:
		EventDropEpInd(wEvent, pData, wDataSize);
		break;
	case evtp_CallExistEP_result:
		EventCallExistEpInd(wEvent, pData, wDataSize);
		break;
	case evtp_StartTurn_ind:
		EventStartPollInd(wEvent, pData, wDataSize);
		break;
	case evtp_SuspendTurn_ind:
		EventSuspendPollInd(wEvent, pData, wDataSize);
		break;
	case evtp_StopTurn_ind:
		EventStopPollInd(wEvent, pData, wDataSize);
		break;
	case evtp_TurnStat_ntfy:
		EventPollStatNtfy(wEvent, pData, wDataSize);
		break;
	case evtp_UpdateTurn_ind:
		EventSetTurnListInd(wEvent, pData, wDataSize);
		break;
	case evtp_StopDual_Ind:
		EventStopDualInd(wEvent, pData, wDataSize);
		break;
	case evtp_UpdateAudMixInfo_Ind:
		EventOprDiscussEpInd(wEvent, pData, wDataSize);
		break;
	case ev_AuxMixVacSwitchInd:
		EventAudMixVacInd(wEvent, pData, wDataSize);
		break;
	case evtp_StartAuxMix_ind:
		EventUptateDiscussInd(wEvent, pData, wDataSize);
		break;
	case evtp_ViewObj_ind:
		EventViewObjInd(wEvent, pData, wDataSize);
		break;
	case evtp_UndoViewObj_ind:
		EventUnViewObjInd(wEvent, pData, wDataSize);
		break;
	case evtp_ChairStreenStatus_Notify:
		EventChairStreenInfoNotify(wEvent, pData, wDataSize);
		break;
	case ev_UMS_UMC_SelView_Ind:
		EventSelViewInd(wEvent, pData, wDataSize);
		break;
	case ev_UMS_UMC_SelView_Ntfy:
		EventSelViewNtfy(wEvent, pData, wDataSize);
		break;
	case ev_UMS_UMC_BrdVmp_Ind:
		EventBrdVmpInd(wEvent, pData, wDataSize);
		break;
	case ev_UMS_UMC_SetBrdVmp_Ind:
		EventSetBrdVmpInd(wEvent, pData, wDataSize);
		break;
	case ev_UMS_UMC_RervesBrdVmp_Ind:
		EventRervesBrdVmpInd(wEvent, pData, wDataSize);
		break;
	case ev_UMS_UMC_BrdVmp_Ntfy:
		EventBrdVmpNtfy(wEvent, pData, wDataSize);
		break;
	case ev_UMS_UMC_SaveVmpCfg_Ind:
		EventSaveBrdVmpCfgInd(wEvent, pData, wDataSize);
		break;
	case evtp_UmsJoinConf_Req:
		EventUmsJoinConfReq(wEvent, pData, wDataSize);
		break;
	case evtp_UmsJoinConf_Notify:
		EventUmsJoinConfNtfy(wEvent, pData,wDataSize);
		break;
		//从UI过来的消息
	case ev_SysCmsLoginInd:
		EventLogin(ptMsg);
		break;
	case evtp_StartConfTemplate_Req:
		EventStartConfReq(ptMsg);
		break;
	case evtp_StartInterimMeeting_Req:
		EventStartMeetingReq(ptMsg);
		break;
	case evtp_HungUpConf_cmd:
		EventHungUpConf(ptMsg);
		break;
	case evtp_CallEP_cmd:
		EventCallEp(ptMsg);
		break;
	case evtp_CallExistEP_cmd:
		EventCallExistEp(ptMsg);
		break;
	case evtp_DropEp_cmd:
		EventDropEp(ptMsg);
		break;

	case evtp_ApplySpeaker_cmd:
		EventChangeSpeaker(ptMsg);
		break;
	case evtp_MuteEp_cmd:
		EventMuteEp(ptMsg);
		break;
	case evtp_QuietEp_cmd:
		EventQuietEp(ptMsg);
		break;
	case evtp_UpdateTurn_cmd:
		EventSetTurnList(ptMsg);
		break;		
	case evtp_UpdateAudMixInfo_cmd:
		EventOprDiscussEpCmd(ptMsg);
		break;
	case ev_AuxMixVacSwitch:
		EventAudMixVacCmd(ptMsg);
		break;
	case evtp_StartAuxMix_cmd:
		EventUptateDiscussCmd(ptMsg);
		break;
	case evtp_StartDual_Cmd:
		EventStartDual(ptMsg);
		break;
	case evtp_StopDual_Cmd:
		EventStopDual(ptMsg);
		break;
	case evtp_StartTurn_cmd:
		EventStartPoll(ptMsg);
		break;
	case evtp_StopTurn_cmd:
		EventStopPoll(ptMsg);
		break;
	case evtp_SuspendTurn_cmd:
		EventSupendPoll(ptMsg);
		break;
	case evtp_ViewObj_cmd:
		EventViewObj(ptMsg);
		break;
	case evtp_UndoViewObj_cmd:
		EventUnViewObj(ptMsg);
		break;
	case ev_UMC_UMS_SelView_Req:
		EventSelViewReq(ptMsg);
		break;
	case ev_UMC_UMS_RervesBrdVmp_Req:
		EventRervesBrdVmpReq(ptMsg);
		break;
	case ev_UMC_UMS_SetBrdVmp_Req:
		EventSetBrdVmpReq(ptMsg);
		break;
	case ev_UMC_UMS_BrdVmp_Req:
		EventBrdVmpReq(ptMsg);
		break;
	case ev_UMC_UMS_SaveVmpCfg_Cmd:
		EventSaveBrdVmpCfg(ptMsg);
		break;
	case evtp_UmsJoinConf_Ack:
		EventUmsJoinConfAck(ptMsg);
        break;
	case evtp_FeccCamera_Req:
		EventFeccCameraReq(ptMsg);
		break;
	case evtp_FeccPrePos_Req:
		EventFeccPrePosReq(ptMsg);
		break;
	case evtp_FeccSelVid_Req:
		EventFeccSelVidReq(ptMsg);
		break;


    /////////////////点名/////////////////////
	case evtp_StartRollCall_cmd:
		EventUptateRollCallCmd(ptMsg);
		break;
	case evtp_StartRollCall_Ind:
        EventUptateRollCallInd(wEvent, pData, wDataSize);
		break;
	case evtp_RollCallNext_cmd:
        EventUptateRollCallNextEpCmd(ptMsg);
		break;
	case evtp_RollCallNext_Ind:
        EventUptateRollCallNextEpInd(wEvent, pData, wDataSize);
		break;
	case evtp_RollCallUpdateList_cmd:
        EventUptateRollCallListCmd(ptMsg);
		break;
	case evtp_RollCallUpdateList_Ind:
        EventUptateRollCallListInd(wEvent, pData, wDataSize);
		break;
	case evtp_RollCall_PresentState:
        EventRollCallPresentStateCmd(ptMsg);
		break;
	case evtp_RollCall_PresentState_Notify:
        EventRollCallPresentStateNotify(wEvent, pData, wDataSize);
		break;
	case evtp_RollCallState_Notify:
		EventRollCallInfoNotify(wEvent, pData, wDataSize);
		break;

    /////////////////会议混音///////////////////////

	case evtp_ConfAudMixMode_cmd:
		EventAudMixModeCmd(ptMsg);
		break;
	case evtp_ConfAudMixMode_ind:
        EventAudMixModeInd(wEvent, pData, wDataSize);
		break;
	case evtp_ConfAudMixList_cmd:
		EventAudMixListCmd(ptMsg);
		break;
	case evtp_ConfAudMixList_ind:
        EventAudMixListInd(wEvent, pData, wDataSize);
		break;
	case evtp_ConfAudMixMode_Notify:
        EventAudMixNotify(wEvent, pData, wDataSize);
		break;


	////////////getconfvidaud/////////////
	case evtp_GetConfBrdVidAud_cmd:
		EventGetConfBrdVidAudCmd(ptMsg);
		break;
	case evtp_GetConfBrdVidAud_ind:
        EventGetConfBrdVidAudInd(wEvent, pData, wDataSize);
		break;
	case evtp_ReleasConfBrdVidAud_cmd:
        EventReleaseGetConfBrdVidAudCmd(ptMsg);
		break;
	case evtp_ReleasConfBrdVidAud_ind:
        EventReleaseGetConfBrdVidAudInd(wEvent, pData, wDataSize);

	case evtp_GetConfBrdVidAudAskKey:
		EventGetConfBrdVidAudaskKey(ptMsg);
		break;
	///////////////不入会请求画面合成码流/////////////////
	case evtp_GetConfVmpVid_cmd:
		EventGetConfVmpVidCmd(ptMsg);
		break;
	case evtp_GetConfVmpVid_ind:
		EventGetConfVmpVidInd(wEvent, pData, wDataSize);
		break;
	case evtp_ReleaseConfVmpVid_cmd:
		EventReleaseConfVmpVidCmd(ptMsg);
		break;
	case evtp_ReleaseConfVmpVid_ind:
		EventReleaseConfVmpVidInd(wEvent, pData, wDataSize);
		break;
	case evtp_GetConfVmpVidAskKey_cmd:
		EventGetConfVmpVidAskKey(ptMsg);
		break;
	case evtp_ConfVmpVid_nty:
		EventConfVmpVidNotify(wEvent, pData, wDataSize);
		break;

	case evtp_GetEpSreenStream_cmd:
		EventGetEpScreenInfoCmd(ptMsg);
		break;
	case evtp_GetEpSreenStream_Ind:
		EventGetEpScreenInfoInd(wEvent, pData, wDataSize);
		break;
	case evtp_ReleaseEpSreenStream_cmd:
		EventReleaseEpScreenInfoCmd(ptMsg);
		break;
	case evtp_ReleaseEpSreenStream_Ind:
		EventReleaseEpScreenInfoInd(wEvent, pData, wDataSize);
		break;
	case evtp_GetEpSreenAskKey_cmd:
		EventGetConfEpScreenAskKey(ptMsg);
		break;

	// 更新临时会议名到server
	case evtp_Update_TempConf_To_Server:
		EventUpdateTempConfName( ptMsg );
		break;

	default:
		return FALSE;
		break;
	}
	return TRUE;
}

u16 CUmsCallHandleService::GetIdleConf(TTPConfTemplate* tTemplate, TLogUser* ptUmcUsr /*= NULL*/)
{
	//获取当前时间
	time_t curTime;
	time(&curTime);

	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex )
	{
		if (!m_atCall[wIndex].m_bIsRunning && (curTime > (m_atCall[wIndex].m_tEndConfTime + 30)))
		{
			m_atCall[wIndex].m_bIsRunning  = TRUE;
			strncpy(m_atCall[wIndex].m_achConfName, tTemplate->m_achConfName, TP_MAX_ALIAS_LEN);
			strncpy(m_atCall[wIndex].m_achConfE164, tTemplate->m_achConfE164, TP_MAX_ALIAS_LEN);
			
			if( NULL != ptUmcUsr )
			{
				memcpy(&m_atCall[wIndex].m_tUmcUser, ptUmcUsr, sizeof(TLogUser));
			}
			
			return wIndex;
		}
	}
	return TP_INVALID_INDEX;
}

TCallMgr* CUmsCallHandleService::GetCallMgr(u16 wIndex)
{
	if (wIndex <= 0 || wIndex > TP_UMS_MAX_CONFNUM)
	{
		return NULL;
	}
	else
	{
		return &(m_atCall[wIndex]);
	}
}

u32 CUmsCallHandleService::GetRunningConf()
{
	u32 dwCount = 0;

	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex )
	{
		if (m_atCall[wIndex].m_bIsRunning)
		{
			++dwCount;
		}
	}
	return dwCount;
}

u16 CUmsCallHandleService::GetConf(TTPConfTemplate* tTemplate)
{
	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex )
	{
		if (m_atCall[wIndex].m_bIsRunning && (strcmp(m_atCall[wIndex].m_achConfName, tTemplate->m_achConfName) == 0 
			                              &&  strcmp(m_atCall[wIndex].m_achConfE164, tTemplate->m_achConfE164) == 0))
		{
			return wIndex;	
		}
	}
	return TP_INVALID_INDEX;
}

u16	 CUmsCallHandleService::GetConfByDstAddr(TTpCallAddr* pCallDstAddr)
{
	u16 wIndex = 0;
	if (!pCallDstAddr)
	{
    	return TP_INVALID_INDEX;
	}

	for (wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex )
	{
        if (m_atCall[wIndex].m_bIsRunning && (strcmp(m_atCall[wIndex].m_achConfName, pCallDstAddr->m_tAlias.m_abyAlias) == 0))
		{
            return wIndex;
		}
	}

	return TP_INVALID_INDEX;
}


BOOL32 CUmsCallHandleService::IsConfIdle()
{
	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex )
	{
		if (m_atCall[wIndex].m_bIsRunning)
		{
			return FALSE;
		}
	}
	return TRUE;
}
/*==============================================================================
函数名    :  EventCallIncoming
功能      :  UMS被叫作为被叫：
			  1. 会议未召开
			     a. 主叫是CNS，则直接拒绝
				 b. 主叫是UMS，召开会议，并答复主叫
			  2. 已经召开会议
			     a. 主叫是CNS，成功(在呼叫模块进行其它验证)
				 b. 主叫是UMS，成功(在呼叫模块进行其它验证)
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-4               zhaixiaogang
==============================================================================*/
void CUmsCallHandleService::EventCallIncoming(u8* pDataBuf, u16 wDataSize)
{
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	CUmsConfTemplateHandleService* pConfService = (CUmsConfTemplateHandleService*)pServer->GetService(CTpUmsServer::_CUmsConfTemplateHandleService);

	TUmsHandle tHandle;
	TUmsCallInfo tCaller;
	TP_SAFE_CAST(tHandle, pDataBuf);
	TP_SAFE_CAST(tCaller, pDataBuf + sizeof(TUmsHandle));
	TConfTemplateLocal* ptConfTemp = pConfService->GetConfTemplate(tCaller.m_tDestAddr);

	TConfTemplateLocal* ptSrcTemp = pConfService->GetConfTemplate(tCaller.m_tSrcAddr);

	TConfTemplateLocal  tConfUnUsedTemp;
    BOOL32 bTempConf = FALSE;

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UmsConfIncomingAck);
	cMsg.SetBody(pDataBuf, wDataSize);

	EmCnsCallReason tRet = EmCnsCallReason_hungup;

	u16 wTempID = TP_INVALID_INDEX;
	u16 wConfID = TP_INVALID_INDEX;
	BOOL32 bConfStart = FALSE;
	do 
	{
		if (NULL == ptConfTemp)
		{
			wTempID = 0;
			bTempConf = TRUE;
			ptConfTemp = &tConfUnUsedTemp;
		} 
        else
		{
             wTempID = ptConfTemp->m_wID;
		}
		
		//禁止CNS以323协议来呼叫UMS
		if ( ( emTPEndpointTypeCNS == tCaller.m_emSrcEpType || emTPEndpointTypeUMS == tCaller.m_emSrcEpType ) 
			&& emTpH323 == tCaller.m_emTpProtocol) 
		{
			tRet = EmCnsCallReason_Unreachable;
			break;
		}
		//禁止323终端以sip协议来呼叫UMS
		if ( ( emTPEndpointH323MT == tCaller.m_emSrcEpType || emTPEndpointH323SingleMCU == tCaller.m_emSrcEpType ) 
			&& emTpSIP == tCaller.m_emTpProtocol) 
		{
			tRet = EmCnsCallReason_Unreachable;
			break;
		}

		//禁止同一个UMS上的会议进行级联
		if (NULL != ptSrcTemp)
		{
			MdlError(Ums_Mdl_Service, ("[EventCallIncoming] Src Alias:%s,E164:%s,IP:"TPIPFORMAT", Dest  Alias:%s,E164:%s,IP:"TPIPFORMAT"  in same ums.\n", 
									  tCaller.m_tSrcAddr.m_tAlias.m_abyAlias,tCaller.m_tSrcAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCaller.m_tSrcAddr.m_dwIP),
									  tCaller.m_tDestAddr.m_tAlias.m_abyAlias,tCaller.m_tDestAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCaller.m_tDestAddr.m_dwIP)));
			tRet = EmCnsCallReason_Rejected;
			break;
		}


        if (!bTempConf && emTpSIP == tCaller.m_emTpProtocol &&
		    (tCaller.m_tEncrypt.m_emEncryptModel == emTPEncryptTypeQtEverySecond ||
			tCaller.m_tEncrypt.m_emEncryptModel == emTPEncryptTypeQtEveryMinute ||
			tCaller.m_tEncrypt.m_emEncryptModel == emTPEncryptTypeQtEveryConf))
		{
   	            if (ptConfTemp->m_tEncrypt.m_emEncryptModel != emTPEncryptTypeQtEverySecond &&
					ptConfTemp->m_tEncrypt.m_emEncryptModel != emTPEncryptTypeQtEveryMinute &&
					ptConfTemp->m_tEncrypt.m_emEncryptModel != emTPEncryptTypeQtEveryConf )
				{
					MdlError(Ums_Mdl_Service, ("[EventCallIncoming]  Encrypt not equal! caller enc:%d; conftemplate enc:%d. \n", 
						tCaller.m_tEncrypt.m_emEncryptModel,ptConfTemp->m_tEncrypt.m_emEncryptModel) );
					
					tRet = EmCnsCallReason_Rejected;
			        break;;
				}
		}

        if (!bTempConf)
		{
		    wConfID = GetConf((TTPConfTemplate*)ptConfTemp);
		} 
		else 
		{
            wConfID = GetConfByDstAddr(&tCaller.m_tDestAddr);
			if (!TP_VALID_HANDLE(wConfID))
			{

			    MdlError(Ums_Mdl_Service, ("[EventCallIncoming] Call TempConf dst not found! Src Alias:%s,E164:%s,IP:"TPIPFORMAT", Dest  Alias:%s,E164:%s,IP:"TPIPFORMAT".\n", 
									  tCaller.m_tSrcAddr.m_tAlias.m_abyAlias,tCaller.m_tSrcAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCaller.m_tSrcAddr.m_dwIP),
									  tCaller.m_tDestAddr.m_tAlias.m_abyAlias,tCaller.m_tDestAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCaller.m_tDestAddr.m_dwIP)));
				tRet = EmCnsCallReason_dstnotfind;
			    break;
			}
			else
			{
				bConfStart = TRUE;
				tRet = EmCnsCallReason_success;
				break;
			}
		}

		
		if (!TP_VALID_HANDLE(wConfID))
		{//会议未召开
			if (emTPEndpointTypeUMS == tCaller.m_emSrcEpType || emTPEndpointTypeCNS == tCaller.m_emSrcEpType
				||emTPEndpointH323MT == tCaller.m_emSrcEpType || emTPEndpointH323SingleMCU == tCaller.m_emSrcEpType)
			{//UMS，开启会议
				wConfID = GetIdleConf((TTPConfTemplate*)ptConfTemp);
				if (!TP_VALID_HANDLE(wConfID))
				{
					tRet = EmCnsCallReason_resourcefull;
					break;
				}
	
				UpdateRunningConfCount();
			}
			else
			{//未知类型，直接挂断
				tRet = EmCnsCallReason_hungup;
				break;
			}			
		}
		else
		{			
			//会议已经存在，转到会议模块
			bConfStart = TRUE;
		}

		pConfService->UpDateOnTimeConfOnStart(ptConfTemp->m_wID);

		tRet = EmCnsCallReason_success;
		
	} while (0);

	MdlHint(Ums_Mdl_Service, ("[EventCallIncoming] CallingAddr Alias:%s,E164:%s,IP:"TPIPFORMAT", CalledAddr Alias:%s,E164:%s,IP:"TPIPFORMAT", ConfTempID:%d, ConfID:%d, CallResult:(%d->%s), bConfStart:%d, bTempConf:%d.\n", 
			tCaller.m_tSrcAddr.m_tAlias.m_abyAlias,tCaller.m_tSrcAddr.m_tE164.m_abyAlias, Tpu32ToIP(tCaller.m_tSrcAddr.m_dwIP),
			tCaller.m_tDestAddr.m_tAlias.m_abyAlias, tCaller.m_tDestAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCaller.m_tDestAddr.m_dwIP),
			wTempID, wConfID, TpEnumIdString(EmCnsCallReason, tRet), bConfStart, bTempConf) );

	cMsg.CatBody(&tRet, sizeof(tRet));

	if (EmCnsCallReason_success == tRet)
	{
		cMsg.CatBody(&wConfID, sizeof(wConfID));
		cMsg.CatBody(ptConfTemp, sizeof(TConfTemplateLocal));
		cMsg.CatBody(&bConfStart, sizeof(bConfStart));
	}
	
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));
}

/*==============================================================================
函数名    :  EventCallCreateMeeting
功能      :  只允许CNS创建会议
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-4               zhaixiaogang
==============================================================================*/
void CUmsCallHandleService::EventCallCreateMeeting(u8* pDataBuf, u16 wDataSize)
{
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	CUmsConfTemplateHandleService* pConfService = (CUmsConfTemplateHandleService*)pServer->GetService(CTpUmsServer::_CUmsConfTemplateHandleService);
	TUmsHandle tHandle;
	TUmsCallInfo tCaller;
	TConfTemplateLocal tConfTemp;
	TP_SAFE_CAST(tHandle, pDataBuf);
	TP_SAFE_CAST(tCaller, pDataBuf + sizeof(TUmsHandle));
	TP_SAFE_CAST(tConfTemp, pDataBuf + sizeof(TUmsHandle) + sizeof(TUmsCallInfo));

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UmsConfIncomingAck);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tCaller, sizeof(tCaller));
	
	EmCnsCallReason tRet = EmCnsCallReason_hungup;

	u16 wConfID = TP_INVALID_INDEX;
	BOOL32 bConfStart = FALSE;
	do 
	{
		//只允许CNS以SIP协议呼叫
		if ( emTPEndpointTypeCNS != tCaller.m_emSrcEpType || emTpH323 == tCaller.m_emTpProtocol) 
		{
			tRet = EmCnsCallReason_Unreachable;
			break;
		}
						
		wConfID = GetIdleConf((TTPConfTemplate*)&tConfTemp);
		if (!TP_VALID_HANDLE(wConfID))
		{
			tRet = EmCnsCallReason_resourcefull;
			break;
		}

		UpdateRunningConfCount();

		tRet = EmCnsCallReason_success;

	} while (0);

	MdlHint(Ums_Mdl_Service, ("[EventCallCreateMeeting] CallingAddr Alias:%s,E164:%s,IP:"TPIPFORMAT", CalledAddr Alias:%s,E164:%s,IP:"TPIPFORMAT", ConfID:%d, CallResult:(%d->%s), bConfStart:%d\n", 
			tCaller.m_tSrcAddr.m_tAlias.m_abyAlias,tCaller.m_tSrcAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCaller.m_tSrcAddr.m_dwIP),
			tCaller.m_tDestAddr.m_tAlias.m_abyAlias,tCaller.m_tDestAddr.m_tE164.m_abyAlias,Tpu32ToIP(tCaller.m_tDestAddr.m_dwIP), 
			wConfID, TpEnumIdString(EmCnsCallReason, tRet), bConfStart) );

	cMsg.CatBody(&tRet, sizeof(tRet));

	if (EmCnsCallReason_success == tRet)
	{
		cMsg.CatBody(&wConfID, sizeof(wConfID));
		cMsg.CatBody(&tConfTemp, sizeof(TConfTemplateLocal));
		cMsg.CatBody(&bConfStart, sizeof(bConfStart));
	}
	
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));
}

void CUmsCallHandleService::EventStartConfTemplateFailed(u8* pDataBuf, u16 wDataSize)
{
	u16 wConfID;
	TP_SAFE_CAST(wConfID, pDataBuf);

	if (!VALID_CONF_ID(wConfID))
	{
		MdlError(Ums_Mdl_Service, ("EventStartConfTemplateFailed ConfID error:%d\n", wConfID));
		return;
	}

	MdlHint(Ums_Mdl_Service, ("EventStartConfTemplateFailed Start ConfFailed. ConfTempName:%s, ConfID:%d\n", m_atCall[wConfID].m_achConfName, wConfID));

	m_atCall[wConfID].HungUp();

	UpdateRunningConfCount();
}

void CUmsCallHandleService::EventStartConfRet(u8* pDataBuf, u16 wDataSize)
{
	TStartConfResult tStartRet = *(TStartConfResult*)pDataBuf;

	if ( !VALID_CONF_ID(tStartRet.m_wConfID) )
	{
		MdlError(Ums_Mdl_Service, ("EventStartConfRet ConfID error:%d\n", tStartRet.m_wConfID));
		return;
	}

	MdlHint(Ums_Mdl_Service, ("EventStartConfRet. ConfTempName:%s, ConfID:%d, TemplateId:%d, Ret:%d\n", 
												m_atCall[tStartRet.m_wConfID].m_achConfName, tStartRet.m_wConfID, tStartRet.m_wConfTemplateID, tStartRet.m_emReason));

	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	CUmsConfTemplateHandleService* pTemplateService = (CUmsConfTemplateHandleService*)pServer->GetService(CTpUmsServer::_CUmsConfTemplateHandleService);
	TTpCallAddr tCallAddr;
	strncpy(tCallAddr.m_tAlias.m_abyAlias, m_atCall[tStartRet.m_wConfID].m_achConfName, sizeof(u8)*TP_MAX_ALIAS_LEN);
	tCallAddr.m_tAlias.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	
	if (tStartRet.m_wConfTemplateID > 0 && tStartRet.m_wConfTemplateID < TP_CONFTEMPLATE_MAXNUM)
	{
		TConfTemplateLocal* ptTemplate = pTemplateService->GetConfTemplate(tCallAddr);
		if ( ptTemplate )
		{
			tStartRet.m_wConfTemplateID = ptTemplate->m_wID;
		}
	}


	if( !m_atCall[tStartRet.m_wConfID].m_tUmcUser.Invalid() )
	{
		//提示给umc
		TpNotifyMsgToUeFromService(evtp_StartConfTemplate_Ret, &tStartRet, sizeof(TStartConfResult), m_atCall[tStartRet.m_wConfID].m_tUmcUser);
	}

	if (m_atCall[tStartRet.m_wConfID].m_bCallByTimer)
	{
		m_atCall[tStartRet.m_wConfID].m_bCallByTimer = FALSE;
		TLogUser tUserTmp;
		TpNotifyMsgToUeFromService(evtp_StartConfTemplate_Ret, &tStartRet, sizeof(tStartRet), tUserTmp);
	}

	return ;
}

void CUmsCallHandleService::EventLogin(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	TLogUser* ptUserTmp = (TLogUser*)pData;
	
	MdlHint(Ums_Mdl_Service, ("EventLogin, LogUsr-> ID:%d, Name:%s, IP:"TPIPFORMAT"\n", ptUserTmp->m_dwUserID, ptUserTmp->m_achName, Tpu32ToIP(ptUserTmp->m_dwUserIP)));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_SysCmsLoginInd);
	cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		if (m_atCall[wIndex].m_bIsRunning)
		{
			cMsg.Post(MAKEIID(AID_UMSCONFMGR, wIndex));	
		}
	}
	return;
}


void CUmsCallHandleService::EventStartConfReq(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	
	TLogUser* ptUserTmp = (TLogUser*)pData;
	u16 wConfTemplateID	= *(u16*)(pData+sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("EventStartConfReq, wConfTemplateID:%d\n", wConfTemplateID));

	u32 dwIndex = 0;
	u16 wConfID = TP_INVALID_INDEX;
	TStartConfResult tStartRet;
	tStartRet.m_emReason = TP_StartConf_Success;
	tStartRet.m_wConfTemplateID = wConfTemplateID;

	do 
	{
		CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
		CUmsConfTemplateHandleService* pTemplateService = (CUmsConfTemplateHandleService*)pServer->GetService(CTpUmsServer::_CUmsConfTemplateHandleService);
		CUmsRegHandleService* pRegService = (CUmsRegHandleService*)pServer->GetService(CTpUmsServer::_CUmsRegHandleService);

		TConfTemplateLocal* tTemplate = pTemplateService->GetConfTemplate(wConfTemplateID);
		
		if (NULL == tTemplate)
		{
			tStartRet.m_emReason = TP_StartConf_ConfTemplateUnExist;
			break;
		}

// 		if (!pRegService->IsRegOneGroup(em_Sip_reg_type))
// 		{
// 			tStartRet.m_emReason = TP_StartConf_SipUnReg;
// 			break;
// 		}


		//0号模版不判断
		if( 0 != wConfTemplateID)
		{
			wConfID = GetConf((TTPConfTemplate*)tTemplate);
			if (TP_VALID_HANDLE(wConfID))
			{
				tStartRet.m_emReason = TP_StartConf_ConfExist;
				break;
			}
		}

		wConfID = GetIdleConf((TTPConfTemplate*)tTemplate, ptUserTmp);
		if (!TP_VALID_HANDLE(wConfID))
		{
			tStartRet.m_emReason = TP_StartConf_ConfFull;
			break;
		}

		pTemplateService->UpDateOnTimeConfOnStart(wConfTemplateID);

		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsMakeConf);
		cMsg.SetBody(tTemplate, sizeof(TConfTemplateLocal));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID));

		UpdateRunningConfCount();

	} while (0);
	
	MdlHint(Ums_Mdl_Service, ("EventStartConfReq ConfTempID:%d, ConfID:%d, ret:(%d->%s)\n"
		, wConfTemplateID, wConfID, TpEnumIdString(EmTpStartConfRet, tStartRet.m_emReason)));

	//若成功 则仍需要umscall侧验证后才回应
	if( tStartRet.m_emReason != TP_StartConf_Success )
	{
		tStartRet.m_wConfID = wConfID;
		TpNotifyMsgToUeFromService(evtp_StartConfTemplate_Ret, &tStartRet, sizeof(tStartRet), *ptUserTmp);
	}
	return ;
}

void CUmsCallHandleService::EventStartMeetingReq(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TTPConfMeet *tMeet = (TTPConfMeet*)(pData+sizeof(TLogUser));
	TConfTemplateLocal tTemplate;
	GetValue(tTemplate,*tMeet);

	u16 wtempID = tTemplate.m_wID;


	
	u16 wConfID = TP_INVALID_INDEX;
	TStartConfResult tStartRet;
	tStartRet.m_emReason = TP_StartConf_Success;
	tStartRet.m_wConfTemplateID = wtempID;
	do 
	{
		
		if (wtempID < TP_CONFTEMPLATE_MAXNUM && wtempID > 0 )
		{//1~TP_CONFTEMPLATE_MAXNUM（128）- 1为模板会议
			tStartRet.m_emReason = TP_StartConf_ConfTemplateUnExist;
			break;
		}
		wConfID = GetIdleConf((TTPConfTemplate*)&tTemplate, ptUserTmp);
		if (!TP_VALID_HANDLE(wConfID))
		{
			tStartRet.m_emReason = TP_StartConf_ConfFull;
			break;
		}
		
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsMakeConf);
		cMsg.SetBody(&tTemplate, sizeof(TConfTemplateLocal));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR,wConfID ));
		
		UpdateRunningConfCount();
		
	} while (0);

	MdlHint(Ums_Mdl_Service, ("EventStartMeetingReq  ConfID:%d, ret:(%d->%s)\n"
		, wConfID, TpEnumIdString(EmTpStartConfRet, tStartRet.m_emReason)));
	//若成功 则仍需要umscall侧验证后才回应
	if( tStartRet.m_emReason != TP_StartConf_Success )
	{
		tStartRet.m_wConfID = wConfID;
		TpNotifyMsgToUeFromService(evtp_StartConfTemplate_Ret, &tStartRet, sizeof(tStartRet), *ptUserTmp);
	}
	return ;
	
}

/*==============================================================================
函数名    :  EventHungUpConf
功能      :  
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-7               zhaixiaogang
==============================================================================*/
void CUmsCallHandleService::EventHungUpConf(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	
	TLogUser* ptUserTmp = (TLogUser*)pData;
	u16 wConfID	= *(u16*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventHunUpConf, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));

	if (AID_UMSUE_APP == wAppID)
	{
		EmTpDropConfRet emRet = TP_DropConf_ConfUnExit;
		
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			emRet = TP_DropConf_Success;
			
			cMsg.SetEvent(evtp_HungUpConf_cmd);
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
			
			m_atCall[wConfID].HungUp();

			TDelConfList tConfList;
			tConfList.m_wRefreshNum = 1;
			tConfList.m_awConfIDList[0] = wConfID;
			TPBroadMsgToUi(evtp_DelConflist_Notify, (u8*)&tConfList, sizeof(tConfList));		
			UpdateRunningConfCount();

		}
		
		cMsg.SetEvent(evtp_HungUpConf_result);
		cMsg.SetBody(pData, ptMsg->GetBodyLen());
		cMsg.CatBody(&emRet, sizeof(emRet));
		cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);		
	}
	else if (AID_UMSCONFMGR == wAppID)
	{
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			m_atCall[wConfID].HungUp();

			TDelConfList tConfList;
			tConfList.m_wRefreshNum = 1;
			tConfList.m_awConfIDList[0] = wConfID;
			TPBroadMsgToUi(evtp_DelConflist_Notify, (u8*)&tConfList, sizeof(tConfList));
			UpdateRunningConfCount();
		}
	}
	else
	{
		MdlError(Ums_Mdl_Service, ("EventHunUpConf. AppId error. ConfId:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	}

	return;
}

void CUmsCallHandleService::EventHungUpConfResult(CTpMsg *const ptMsg)
{
	TLogUser* ptUser = (TLogUser*)ptMsg->GetBody();
	u16 wConfID = *(u16*)(ptMsg->GetBody() + sizeof(TLogUser));
	EmTpDropConfRet emRet = *(EmTpDropConfRet*)(ptMsg->GetBody() + sizeof(TLogUser) + sizeof(u16));
	
	MdlHint(Ums_Mdl_Service, ("EventHungUpConfResult , wConfID:%d, emRet:(%d->%s)\n", wConfID, TpEnumIdString(EmTpDropConfRet, emRet)));

	TPTransMsgToUi(ptMsg->GetEvent(), ptMsg->GetBody(), ptMsg->GetBodyLen());
}

void CUmsCallHandleService::EventDelConfNotify(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	u8* pData = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();	
    u16 wConfID = 0;
	
	TDelConfList* ptList = (TDelConfList*)pData;

	MdlHint(Ums_Mdl_Service, (" EventDelConfNotify TotalConf:%d, Begin:\n", ptList->m_wRefreshNum));
	
	BOOL32 bHungUp = FALSE;
	for (u16 wInde = 0; wInde < ptList->m_wRefreshNum; ++wInde)
	{
		wConfID = ptList->m_awConfIDList[wInde];
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
		//	m_atCall[wConfID].Clear();
			m_atCall[wConfID].HungUp();
			bHungUp = TRUE;
// 			m_atCall[wConfID].m_bIsRunning = FALSE;
// 			m_atCall[wConfID].m_wConfTempID = TP_INVALID_INDEX;
		}

		MdlHint(Ums_Mdl_Service, ("  >>ListIndex:%d, confID:%d\n", wInde,wConfID));
	}

	MdlHint(Ums_Mdl_Service, (" EventDelConfNotify End. Confid:%d, ToHungUP:%d\n", wConfID, bHungUp ));

	if (bHungUp)
	{
		TPBroadMsgToUi(wEvent, pData, wDataSize);
		UpdateRunningConfCount();
	}
	return;
}

/*==============================================================================
函数名    :  EventCallEp
功能      :  呼叫某个会场，暂时只考虑UE过来的命令
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-7               zhaixiaogang
==============================================================================*/
void CUmsCallHandleService::EventCallEp(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfCallEpAddr* ptConfCalled	= (TConfCallEpAddr*)(pData+sizeof(TLogUser));

	u16 wConfID = ptConfCalled->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventCallEp, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;

		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{			
			cMsg.SetEvent(evtp_CallEP_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmCnsCallReason emRet = EmCnsCallReason_NoConf;
			cMsg.SetEvent(evtp_CallEP_result);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(EmCnsCallReason));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventCallExistEp(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* ptCalled	= (TConfEpID*)(pData+sizeof(TLogUser));
	
	u16 wConfID = ptCalled->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventCallExistEp, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_CallExistEP_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmCnsCallReason emRet = EmCnsCallReason_NoConf;
			cMsg.SetEvent(evtp_CallExistEP_result);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(EmCnsCallReason));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}
void CUmsCallHandleService::EventDropEp(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* ptConfEp	= (TConfEpID*)(pData+sizeof(TLogUser));
	
	u16 wConfID = ptConfEp->m_wConfID;

	MdlHint(Ums_Mdl_Service, ("EventDropEp, confID:%d, epID:%d, From:%s\n", wConfID, ptConfEp->m_wEpID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;

		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_DropEp_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);				
		}
		else
		{
			EmCnsCallReason emRet = EmCnsCallReason_NoConf;
			cMsg.SetEvent(evtp_DropEp_Ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(EmCnsCallReason));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

// void CUmsCallHandleService::EventDeleteEp(CTpMsg *const ptMsg)
// {
// 	u8* pData = ptMsg->GetBody();
// 	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
// 	TLogUser* ptUserTmp = (TLogUser*)pData;
// 	TConfEpID* ptConfEp	= (TConfEpID*)(pData+sizeof(TLogUser));
// 	
// 	u16 wConfID = ptConfEp->m_wConfID;
// 
// 	
// 	MdlHint(Ums_Mdl_Service, ("EventDeleteEp, confID:%d, epID;%d, From:%s\n", wConfID, ptConfEp->m_wEpID, MsgFrom(wAppID) ));
// 	
// 	if (AID_UMSUE_APP == wAppID)
// 	{			
// 		CTpMsg cMsg;
// 		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
// 		{
// 			cMsg.SetEvent(evtp_DeleteEp_cmd);
// 			cMsg.SetBody(pData, ptMsg->GetBodyLen());
// 			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
// 		}
// 	}
// 	
// 	if (AID_UMSCONFMGR == wAppID)
// 	{
// 		
// 	}
// 
// }


void CUmsCallHandleService::EventChangeSpeaker(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* ptConfEp	= (TConfEpID*)(pData+sizeof(TLogUser));
	
	u16 wConfID = ptConfEp->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventChangeSpeaker, confID:%d, epID:%d, From:%s\n", wConfID, ptConfEp->m_wEpID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_ApplySpeaker_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmTpApplySpeakerRet emRet = TP_ApplySpeaker_ConfUnExist;			
			cMsg.SetEvent(evtp_ApplySpeaker_result);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(emRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventMuteEp(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* ptConfEp	= (TConfEpID*)(pData+sizeof(TLogUser));
	BOOL32 bIsMute	= *(BOOL32*)(pData+sizeof(TLogUser)+sizeof(TConfEpID));	
	u16 wConfID = ptConfEp->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventMuteEp, confID:%d, epID:%d, From:%s, bIsMute:%d\n"
		, wConfID, ptConfEp->m_wEpID, MsgFrom(wAppID) , bIsMute));
	
	if (AID_UMSUE_APP == wAppID)
	{					
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			CTpMsg cMsg;
			cMsg.SetEvent(evtp_MuteEp_cmd);
			cMsg.SetBody(ptConfEp, sizeof(TConfEpID));
			cMsg.CatBody(&bIsMute, sizeof(BOOL32));
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			MdlError(Ums_Mdl_Service, ("EventMuteEp error, Conf is not Running, ConfId: %d, bIsRunning: %d\n", wConfID, m_atCall[wConfID].m_bIsRunning));
		}
	}
}

void CUmsCallHandleService::EventQuietEp(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* ptConfEp	= (TConfEpID*)(pData+sizeof(TLogUser));
	BOOL32 bIsQuiet	= *(BOOL32*)(pData+sizeof(TLogUser)+sizeof(TConfEpID));	
	u16 wConfID = ptConfEp->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventQuietEp, confID:%d, epID:%d, From:%s, bIsQuiet:%d\n"
		, wConfID, ptConfEp->m_wEpID, MsgFrom(wAppID) , bIsQuiet));
	
	if (AID_UMSUE_APP == wAppID)
	{					
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			CTpMsg cMsg;
			cMsg.SetEvent(evtp_QuietEp_cmd);
			cMsg.SetBody(ptConfEp, sizeof(TConfEpID));
			cMsg.CatBody(&bIsQuiet, sizeof(BOOL32));
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			MdlError(Ums_Mdl_Service, ("EventQuietEp error, Conf is not Running, ConfId: %d, bIsRunning: %d\n", wConfID, m_atCall[wConfID].m_bIsRunning));
		}
	}
}

void CUmsCallHandleService::EventStartPoll( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());

	TLogUser* ptUserTmp = (TLogUser*)pData;
	u16 wConfID = *(u16*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventStartPoll, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID)));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;

		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{			
			cMsg.SetEvent(evtp_StartTurn_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmTPPollResult emRet = emPollFailUnKown;			
			cMsg.SetEvent(evtp_StartTurn_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(emRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventStopPoll( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	
	TLogUser* ptUserTmp = (TLogUser*)pData;
	u16 wConfID = *(u16*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventStopPoll, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID)));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{			
			cMsg.SetEvent(evtp_StopTurn_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			u32 dwRet = TP_RET_ERROR;			
			cMsg.SetEvent(evtp_StopTurn_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&dwRet, sizeof(dwRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}


void CUmsCallHandleService::EventSupendPoll( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	
	TLogUser* ptUserTmp = (TLogUser*)pData;
	u16 wConfID = *(u16*)(pData+sizeof(TLogUser));
	BOOL32 bSupend = *(BOOL32*)(pData+sizeof(TLogUser)+sizeof(u16));
	
	MdlHint(Ums_Mdl_Service, ("EventSupendPoll, confID:%d, bSupend:%d, From:%s\n", wConfID, bSupend, MsgFrom(wAppID)));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{			
			cMsg.SetEvent(evtp_SuspendTurn_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmTPPollResult emRet = emPollFailUnKown;			
			cMsg.SetEvent(evtp_SuspendTurn_ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&wConfID, sizeof(u16));
			cMsg.CatBody(&emRet, sizeof(EmTPPollResult));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}


void CUmsCallHandleService::EventViewObj(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* tConfEpId = (TConfEpID*)(pData+sizeof(TLogUser));

	u16 wStreenIndex = *(u16*)(pData+sizeof(TLogUser)+sizeof(TConfEpID));
	
	MdlHint(Ums_Mdl_Service, ("EventViewObj, confID:%d, From:%s\n", tConfEpId->m_wConfID, MsgFrom(wAppID)));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		
		if (VALID_CONF_ID(tConfEpId->m_wConfID) && m_atCall[tConfEpId->m_wConfID].m_bIsRunning)
		{			
			cMsg.SetEvent(evtp_ViewObj_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(tConfEpId->m_wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmTPViewResult emRet = emViewFailUnKown;			
			cMsg.SetEvent(evtp_ViewObj_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(emRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventUnViewObj(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	
	TLogUser* ptUserTmp = (TLogUser*)pData;
	u16 wConfID = *(u16*)(pData+sizeof(TLogUser));
	
	u16 wStreenIndex = *(u16*)(pData+sizeof(TLogUser)+sizeof(u16));
	
	MdlHint(Ums_Mdl_Service, ("EventUnViewObj, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID)));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{			
			cMsg.SetEvent(evtp_UndoViewObj_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmTPViewResult emRet = emViewFailUnKown;			
			cMsg.SetEvent(evtp_UndoViewObj_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(emRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}


void CUmsCallHandleService::EventSetTurnList(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TTpPollListNtfy* ptConfTurn	= (TTpPollListNtfy*)(pData+sizeof(TLogUser));
	
	u16 wConfID = ptConfTurn->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventSetTurnList, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_UpdateTurn_cmd);
			cMsg.SetBody(ptMsg->GetBody(), ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			TTpPollListInd tInd;
			tInd.m_wConfID = wConfID;
			tInd.m_wRet = TP_RET_ERROR;
			cMsg.SetEvent(evtp_UpdateTurn_ind);
			cMsg.SetBody(&tInd, sizeof(tInd));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventOprDiscussEpCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TDiscussListOpr* ptDisList	= (TDiscussListOpr*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptDisList->m_wConfId;
	
	MdlHint(Ums_Mdl_Service, ("EventOrpDiscussEpCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_UpdateAudMixInfo_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			ptDisList->ResetOprRes();
			cMsg.SetEvent(evtp_UpdateAudMixInfo_Ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(ptDisList, sizeof(TDiscussListOpr));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventUptateDiscussCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfAuxMixInfo* ptAudMix	= (TConfAuxMixInfo*)(pData+sizeof(TLogUser));
	u16 wConfID = ptAudMix->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventUptateDiscussCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_StartAuxMix_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			cMsg.SetEvent(evtp_StartAuxMix_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventStartDual(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* ptConfEp	= (TConfEpID*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventStartDual, confID:%d, EpID:%d, From:%s\n", ptConfEp->m_wConfID, ptConfEp->m_wEpID, MsgFrom(wAppID) ));
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(ptConfEp->m_wConfID) && m_atCall[ptConfEp->m_wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_StartDual_Cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(ptConfEp->m_wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmTPDualReason emRet = emTpDualNoVideo;
			cMsg.SetEvent(evtp_StartDual_Ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(emRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventStopDual(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID* ptConfEp	= (TConfEpID*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventStopDual, confID:%d, EpID:%d, From:%s\n", ptConfEp->m_wConfID, ptConfEp->m_wEpID, MsgFrom(wAppID) ));
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(ptConfEp->m_wConfID) && m_atCall[ptConfEp->m_wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_StopDual_Cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(ptConfEp->m_wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			EmTPDualReason emRet = emTpDualNoVideo;
			cMsg.SetEvent(evtp_StopDual_Ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.CatBody(&emRet, sizeof(emRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventUpdateConfTurnList( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TTpPollListNtfy* ptConfTurnInfo = (TTpPollListNtfy*)( pDataBuf + sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("EventUpdateConfTurnList, confID:%d, TurnTimeInterval:%d, Total:%d, CurNum:%d\n", 
				ptConfTurnInfo->m_wConfID, ptConfTurnInfo->m_wInterval, ptConfTurnInfo->m_wTotalNum, ptConfTurnInfo->m_wCurNum));

	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);

	return ;
}

void CUmsCallHandleService::EventAuxMixInfoNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfAuxMixInfo* ptMixInfo = (TConfAuxMixInfo*)( pDataBuf + sizeof(TLogUser) );

	MdlHint(Ums_Mdl_Service, ("EventAuxMixInfoNotify, confID:%d, IsStart:%d, bVac:%d\n", ptMixInfo->m_wConfID, ptMixInfo->m_bStart , ptMixInfo->m_bVacOn));

	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);

	return ;
}

void CUmsCallHandleService::EventCallEpResult( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfCallEpAddr* ptConfCallEpAddr = (TConfCallEpAddr*) ( pDataBuf + sizeof(TLogUser) );
	EmCnsCallReason  emRet = *(EmCnsCallReason*)( pDataBuf + sizeof(TLogUser) + sizeof(TConfCallEpAddr) );
	MdlHint(Ums_Mdl_Service, ("EventCallEpResult, confID:%d, CalledAddr Alias:%s,E164:%s,IP:"TPIPFORMAT", RetReason:(%d->%s)\n", 
		ptConfCallEpAddr->m_wConfID, ptConfCallEpAddr->m_tCallAddr.m_tAlias.m_abyAlias,ptConfCallEpAddr->m_tCallAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptConfCallEpAddr->m_tCallAddr.m_dwIP), 
		TpEnumIdString(EmCnsCallReason, emRet)));

	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventApplySpeakerResult( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID*			ptConfEp = (TConfEpID*)(pDataBuf+sizeof(TLogUser));
	EmTpApplySpeakerRet emRet = *(EmTpApplySpeakerRet*)(pDataBuf+sizeof(TLogUser) + sizeof(TConfEpID) );
	
	MdlHint(Ums_Mdl_Service, ("EventApplySpeakerResult, confID:%d, EpId:%d, Ret:(%d->%s)\n", 
		ptConfEp->m_wConfID, ptConfEp->m_wEpID, TpEnumIdString(EmTpApplySpeakerRet, emRet) ));

	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventStartDualInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID*			ptConfEp = (TConfEpID*)(pDataBuf+sizeof(TLogUser));
	EmTPDualReason		emRet = *(EmTPDualReason*)(pDataBuf+sizeof(TLogUser) + sizeof(TConfEpID) );

	MdlHint(Ums_Mdl_Service, ("EventStartDualInd, confID:%d, EpId:%d, Ret:(%d->%s)\n", 
		ptConfEp->m_wConfID, ptConfEp->m_wEpID, TpEnumIdString(EmTPDualReason, emRet) ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventChairConfInfoNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TChairConfInfo* ptChair = (TChairConfInfo*)( pDataBuf + sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventChairConfInfoNotify, confID:%d, ConfChairName:%s, ConfName:%s\n", 
		ptChair->m_wConfID, ptChair->m_tChairName.m_abyAlias, ptChair->m_tConfName.m_abyAlias ) );

	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventUpdateConfCnsListNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfCnsInfo* ptCnsInfo = (TConfCnsInfo*)( pDataBuf + sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventUpdateConfCnsListNotify, confID:%d, EpNum:%d, 1:(%d:%d:%d) 2:(%d:%d:%d) 3:(%d:%d:%d)\n", 
		ptCnsInfo->m_wConfID, ptCnsInfo->m_wNum , ptCnsInfo->m_tConfCnsList[0].m_wEpID, ptCnsInfo->m_tConfCnsList[0].m_wSpeakerNum, ptCnsInfo->m_tConfCnsList[0].m_bOnline,
		ptCnsInfo->m_tConfCnsList[1].m_wEpID, ptCnsInfo->m_tConfCnsList[1].m_wSpeakerNum, ptCnsInfo->m_tConfCnsList[1].m_bOnline,
		ptCnsInfo->m_tConfCnsList[2].m_wEpID, ptCnsInfo->m_tConfCnsList[2].m_wSpeakerNum,ptCnsInfo->m_tConfCnsList[2].m_bOnline) );
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventFeccVidListNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfVidFeccInfo* ptInfo = (TConfVidFeccInfo*)( pDataBuf + sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventFeccVidListNotify, confID:%d, EpNum:%d, 1:(%d|%d|%d) 2:(%d|%d|%d) 3:(%d|%d|%d)\n", 
		ptInfo->m_wConfID, ptInfo->m_wNum , 
		ptInfo->m_atVidFeccList[0].m_wEpID, ptInfo->m_atVidFeccList[0].m_bAllowFecc, ptInfo->m_atVidFeccList[0].m_byVidno,
		ptInfo->m_atVidFeccList[1].m_wEpID, ptInfo->m_atVidFeccList[1].m_bAllowFecc, ptInfo->m_atVidFeccList[1].m_byVidno,
		ptInfo->m_atVidFeccList[2].m_wEpID, ptInfo->m_atVidFeccList[2].m_bAllowFecc, ptInfo->m_atVidFeccList[2].m_byVidno) );
	
	TVidFeccInfo* ptFeccInfo = NULL;
	TVidSourceInfo* ptVidInfo = NULL;
	for (u16 wIndex = 0; wIndex < ptInfo->m_wNum; ++wIndex)
	{
		ptFeccInfo = &ptInfo->m_atVidFeccList[wIndex];
		ptVidInfo  = &ptInfo->m_atVidFeccList[wIndex].m_tVidSourceInfo;
		MdlLowHint(Ums_Mdl_Service, (">>>> EventFeccVidListNotify wEpId:%d, bAllowFecc:%d, byVidNo:%d, byVidNum:%d\n", 
			ptFeccInfo->m_wEpID, ptFeccInfo->m_bAllowFecc, ptFeccInfo->m_byVidno, ptVidInfo->m_byNum));
		
		for (u16 wVidIndex = 0; wVidIndex < ptVidInfo->m_byNum; ++wVidIndex)
		{
			MdlLowHint(Ums_Mdl_Service, ("byVidIndex:%d, byVidAlias:%s\n", 
				ptVidInfo->m_atVidInfo[wVidIndex].m_byIndex, ptVidInfo->m_atVidInfo[wVidIndex].m_abyAlias));
		}
		
	}


	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventAddConfListNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TAddConfList* ptAddConfList = (TAddConfList*)( pDataBuf + sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventAddConfListNotify AddConfList TotalNum:%d Begin : \n", ptAddConfList->m_wRefreshNum) );

	for ( u16 wIndex = 0; wIndex < ptAddConfList->m_wRefreshNum; wIndex++ )
	{
		MdlHint(Ums_Mdl_Service, ("		>>Index:%d, ConfID:%d, DualID:%d, SpeakerID:%d\n",
			wIndex,
			ptAddConfList->m_atTmpList[wIndex].m_wConfID,
			ptAddConfList->m_atTmpList[wIndex].m_wDual,
			ptAddConfList->m_atTmpList[wIndex].m_wSpeaker
			) );
	}
	
	MdlHint(Ums_Mdl_Service, ("EventAddConfListNotify AddConfList End. \n") );

	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;	
}

void CUmsCallHandleService::EventDualEpNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID* ptConfEp = (TConfEpID*)(pDataBuf);
	
	MdlHint(Ums_Mdl_Service, ("EventDualEpNotify, confID:%d, EpID;%d\n", ptConfEp->m_wConfID, ptConfEp->m_wEpID ) );
	
	TPBroadMsgToUi(wEvent, pDataBuf, wDataSize);

	return ;
}

void CUmsCallHandleService::EventSpeakerChangeNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID* ptConfEp = (TConfEpID*)(pDataBuf);
	
	MdlHint(Ums_Mdl_Service, ("EventSpeakerChangeNotify, confID:%d, EpID;%d\n", ptConfEp->m_wConfID, ptConfEp->m_wEpID ) );
	
	TPBroadMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;	
}

void CUmsCallHandleService::EventMuteEpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID* ptConfEp = (TConfEpID*)(pDataBuf);
	BOOL32	   bBool = *(BOOL32*)(pDataBuf + sizeof(TConfEpID));
	
	MdlHint(Ums_Mdl_Service, ("EventMuteEpInd, confID:%d, EpID;%d, MuteBool:%d\n", ptConfEp->m_wConfID, ptConfEp->m_wEpID, bBool ) );
	
	TPBroadMsgToUi(wEvent, pDataBuf, wDataSize);

	return ;
}

void CUmsCallHandleService::EventQuietEpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID* ptConfEp = (TConfEpID*)(pDataBuf);
	BOOL32	   bBool = *(BOOL32*)(pDataBuf + sizeof(TConfEpID));
	
	MdlHint(Ums_Mdl_Service, ("EventQuietEpInd, confID:%d, EpID:%d, QuietBool:%d\n", ptConfEp->m_wConfID, ptConfEp->m_wEpID, bBool ) );
	
	TPBroadMsgToUi(wEvent, pDataBuf, wDataSize);

	return ;
}
void CUmsCallHandleService::EventAllEpQuietMuteStatusNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
    u16 wconfID = *(u16*)(pDataBuf);
	BOOL32	   bAllQuietBool = *(BOOL32*)(pDataBuf + sizeof(u16));
	BOOL32	   bAllMuteBool = *(BOOL32*)(pDataBuf + sizeof(u16)+sizeof(BOOL32));
	MdlHint(Ums_Mdl_Service, ("EventAllEpQuietMuteStatusNotify, confID:%d, QuietBool:%d, MuteBool:%d\n", wconfID, bAllQuietBool, bAllMuteBool ) );
	
	TPBroadMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
	
}
void CUmsCallHandleService::EventAudMixStatNotify( u16 wEvent, u8* pData, u16 wDataSize )
{
	TAudMixStat* ptAudMixStat = (TAudMixStat*)( pData + sizeof(TLogUser) );

	MdlHint(Ums_Mdl_Service, ("EventAudMixStatNotify, confID:%d, MixStart:%d, EmTpMixStatus:%d\n", ptAudMixStat->m_wConfID, ptAudMixStat->m_bIsStart, ptAudMixStat->m_emMixStatus ) );

	TPTransMsgToUi(wEvent, pData, wDataSize);

	return ;
}

void CUmsCallHandleService::EventHungUpConfReasonToUI(u16 wEvent, u8* pData, u16 wDataSize)
{
	u16 wConfID = *((u16*)(pData+sizeof(TLogUser)));
	u32 dwReason = *((u32*)(pData+sizeof(TLogUser)+sizeof(u16)));
	MdlHint(Ums_Mdl_Service, ("EventHungUpConfReasonToUI ConfID:%d, Reason:%d\n", wConfID, dwReason));

	TPTransMsgToUi(wEvent, pData, wDataSize);
}

void CUmsCallHandleService::UpdateRunningConfCount()
{
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	if (NULL != pServer)
	{
		CUmsToolHandleService* pToolService = (CUmsToolHandleService*)pServer->GetService(CTpUmsServer::_CUmsToolHandleService);
		if (NULL != pToolService)
		{
			pToolService->UpdateConfCount();
		}
	}
}

void CUmsCallHandleService::EventCommReasonUIInd( u16 wEvent, u8* pData, u16 wDataSize )
{
	TTPUmsReasonInd tInd;
	TP_SAFE_CAST(tInd, pData+sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("EventCommReasonUIInd ConfID:%d, Reason:%d, R1:%d,R2:%d,R3:%d\n", 
					tInd.m_wConfID, tInd.m_dwReason, tInd.m_dwReserve1, tInd.m_dwReserve2, tInd.m_dwReserve3));

	TPTransMsgToUi(wEvent, pData, wDataSize);

	return ;
}

void CUmsCallHandleService::EventDropEpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID* ptConfEpId = (TConfEpID*) ( pDataBuf + sizeof(TLogUser) );
	EmCnsCallReason  emRet = *(EmCnsCallReason*)( pDataBuf + sizeof(TLogUser) + sizeof(TConfEpID) );
	
	MdlHint(Ums_Mdl_Service, ("EventDropEpInd, confID:%d, epID:%d, RetReason:(%d->%s)\n", 
		ptConfEpId->m_wConfID, ptConfEpId->m_wEpID, TpEnumIdString(EmCnsCallReason, emRet) ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventCallExistEpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID* ptConfEpId = (TConfEpID*) ( pDataBuf + sizeof(TLogUser) );
	EmCnsCallReason  emRet = *(EmCnsCallReason*)( pDataBuf + sizeof(TLogUser) + sizeof(TConfEpID) );
	
	MdlHint(Ums_Mdl_Service, ("EventCallExistEpInd, confID:%d, epID:%d, RetReason:(%d->%s)\n", 
		ptConfEpId->m_wConfID, ptConfEpId->m_wEpID, TpEnumIdString(EmCnsCallReason, emRet) ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventStartPollInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	u16 wConfId = *(u16*) ( pDataBuf + sizeof(TLogUser) );
	EmTPPollResult  emRet = *(EmTPPollResult*)( pDataBuf + sizeof(TLogUser) + sizeof(u16) );
	
	MdlHint(Ums_Mdl_Service, ("EventStartPollInd, confID:%d, EmTPPollResult:(%d->%s)\n", 
		wConfId, TpEnumIdString(EmTPPollResult, emRet) ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventStopPollInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{	
	u16 wConfId = *(u16*) ( pDataBuf + sizeof(TLogUser) );
	EmTPPollResult  emRet = *(EmTPPollResult*)( pDataBuf + sizeof(TLogUser) + sizeof(u16) );
	
	MdlHint(Ums_Mdl_Service, ("EventStopPollInd, confID:%d, EmTPPollResult:(%d->%s)\n", 
		wConfId, TpEnumIdString(EmTPPollResult, emRet) ));

	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventSetTurnListInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TTpPollListInd* ptConfList = (TTpPollListInd*) ( pDataBuf + sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("EventSetTurnListInd, confID:%d, wRet:%d, RcvNum:%d, flag:%d\n", ptConfList->m_wConfID, ptConfList->m_wRet, ptConfList->m_wCurRcvNum, ptConfList->m_nFlag));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventStopDualInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID*			ptConfEp = (TConfEpID*)(pDataBuf+sizeof(TLogUser));
	EmTPDualReason		emRet = *(EmTPDualReason*)(pDataBuf+sizeof(TLogUser) + sizeof(TConfEpID) );
	
	MdlHint(Ums_Mdl_Service, ("EventStopDualInd, confID:%d, EpId:%d, Ret:(%d->%s)\n", 
		ptConfEp->m_wConfID, ptConfEp->m_wEpID, TpEnumIdString(EmTPDualReason, emRet) ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventOprDiscussEpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TDiscussListOpr* ptDisList	= (TDiscussListOpr*)(pDataBuf+sizeof(TLogUser));	

	MdlHint(Ums_Mdl_Service, ("EventOrpDiscussEpInd, confID:%d, OprType:(%d->%s), OprNum:%d)\n", 
		ptDisList->m_wConfId, TpEnumIdString(EmDisListOprType, ptDisList->m_emOprType), ptDisList->m_wNum ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventUptateDiscussInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfAuxMixInfo* ptAuxMixInfo = (TConfAuxMixInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventUptateDiscussInd, confID:%d, bStart:%d, m_bAudMixOn: %d, m_emRet:%d\n", 
		ptAuxMixInfo->m_wConfID, ptAuxMixInfo->m_bStart, ptAuxMixInfo->m_atAuxMixList.m_bAudMixOn, ptAuxMixInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventViewObjInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfEpID* ptConf = (TConfEpID*) ( pDataBuf + sizeof(TLogUser) );
	u16  wChanID = *(u16*)(pDataBuf + sizeof(TLogUser) + sizeof(TConfEpID));

	TChanViewRes tChanViewRes = *(TChanViewRes*)(pDataBuf+sizeof(TLogUser)+sizeof(TConfEpID)+sizeof(u16));
	
	MdlHint(Ums_Mdl_Service, ("EventViewObjInd, confID:%d, dstEpId:%d, ChanID:%d, emRet:%d, Alias:%s\n", ptConf->m_wConfID, ptConf->m_wEpID, wChanID, tChanViewRes.m_emRes, tChanViewRes.m_tAlias.m_abyAlias));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventUnViewObjInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	u16  wConfID = *(u16*) ( pDataBuf + sizeof(TLogUser) );
	u16  wChanID = *(u16*)(pDataBuf + sizeof(TLogUser) + sizeof(TConfEpID));
	
	EmTPViewResult emRet = *(EmTPViewResult*)(pDataBuf+sizeof(TLogUser)+sizeof(TConfEpID)+sizeof(u16));
	
	MdlHint(Ums_Mdl_Service, ("EventUnViewObjInd, confID:%d, ChanID:%d, emRet:%d\n", wConfID, wChanID, emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventChairStreenInfoNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TChairStreenInfo*  tChairInfo = (TChairStreenInfo*) ( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventChairStreenInfoNotify, confID:%d, epId:%d, StreenNum:%d, Info:(L:%d->%s M:%d->%s R:%d->%s)\n", tChairInfo->tConfID.m_wConfID, tChairInfo->tConfID.m_wEpID, 
		tChairInfo->wStreenNum, TpEnumIdString(EMScreenLooked, tChairInfo->tChairStreenInfo[0].emScreenInfo), TpEnumIdString(EMScreenLooked, tChairInfo->tChairStreenInfo[1].emScreenInfo), 
		TpEnumIdString(EMScreenLooked, tChairInfo->tChairStreenInfo[2].emScreenInfo)));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventSelViewReq( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TTPSelViewReq* tViewReq	= (TTPSelViewReq*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventSelViewReq, confID:%d, epId:%d, scrIndx:%d, DstID:%d, DstScrIndx:%d, type:%d, sel:%d\n", 
		tViewReq->m_wConfID, tViewReq->m_wEpID, 
		tViewReq->m_wScreenIndx, tViewReq->m_wDstID, tViewReq->m_wDstScrIndx, tViewReq->m_emType, tViewReq->m_bSel));

	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		cMsg.SetEvent(ev_UMC_UMS_SelView_Req);
		cMsg.SetBody(pData, ptMsg->GetBodyLen());
		cMsg.Post(UMS_CALL_APP_INST(tViewReq->m_wConfID), 0, UMS_SERVICE_APP_INST);	
	}
}

void CUmsCallHandleService::EventSelViewInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TTPSelViewInd*  tViewInd = (TTPSelViewInd*) ( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventSelViewInd, confID:%d, epId:%d, scrIndx:%d, DstID:%d, type:%d, sel:%d\n", 
		tViewInd->m_tSelView.m_wConfID, tViewInd->m_tSelView.m_wEpID, 
		tViewInd->m_tSelView.m_wScreenIndx, tViewInd->m_tSelView.m_wDstID, tViewInd->m_tSelView.m_emType, tViewInd->m_tSelView.m_bSel));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventSelViewNtfy( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TTPSelViewNtfy*  tViewNtfy = (TTPSelViewNtfy*) ( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventSelViewNtfy, confID:%d, epId:%d, (%d,%d; %d,%d; %d,%d;)\n", 
		tViewNtfy->m_wConfID, tViewNtfy->m_wEpID, 
		tViewNtfy->m_atSelView[0].m_wDstID, tViewNtfy->m_atSelView[0].m_emType,
		tViewNtfy->m_atSelView[1].m_wDstID, tViewNtfy->m_atSelView[1].m_emType,
		tViewNtfy->m_atSelView[2].m_wDstID, tViewNtfy->m_atSelView[2].m_emType));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventRervesBrdVmpReq( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TRersvesEqpReq* ptRerVmpReq	= (TRersvesEqpReq*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventRervesBrdVmpReq, confID:%d, Rersves:%d, EqpID:%d\n", 
				ptRerVmpReq->m_wConfID, ptRerVmpReq->m_bRersves, ptRerVmpReq->m_tEqp.m_byEqpID));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		if (VALID_CONF_ID(ptRerVmpReq->m_wConfID) && m_atCall[ptRerVmpReq->m_wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(ev_UMC_UMS_RervesBrdVmp_Req);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(ptRerVmpReq->m_wConfID), 0, UMS_SERVICE_APP_INST);
		}
		else
		{
			TRersvesEqpRsp tRsp;
			tRsp.m_wConfID = ptRerVmpReq->m_wConfID;
			tRsp.m_emRet = EmRervesVmpRet_unKnow;
			memcpy(&tRsp.m_tRersvesReq, ptRerVmpReq, sizeof(TRersvesEqpReq));
			cMsg.SetEvent(ev_UMS_UMC_RervesBrdVmp_Ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&tRsp, sizeof(TRersvesEqpRsp));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}	
	}
}

void CUmsCallHandleService::EventSetBrdVmpReq( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TSetVmpInfoReq* ptVmpReq	= (TSetVmpInfoReq*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventSetBrdVmpReq, confID:%d, Style:%d, chnnum:%d, speakerindx:%d, dualindx:%d, EqpID:%d\n", 
		ptVmpReq->m_wConfID, ptVmpReq->m_tStyle.m_emVmpStyle, ptVmpReq->m_tStyle.m_wChnlNum, 
		ptVmpReq->m_tStyle.m_wSpeakerIndx, ptVmpReq->m_tStyle.m_wDualIndx, ptVmpReq->m_tEqp.m_byEqpID));
	
	if (AID_UMSUE_APP == wAppID)
	{		
		CTpMsg cMsg;
		if (VALID_CONF_ID(ptVmpReq->m_wConfID) && m_atCall[ptVmpReq->m_wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(ev_UMC_UMS_SetBrdVmp_Req);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(ptVmpReq->m_wConfID), 0, UMS_SERVICE_APP_INST);
		}
		else
		{
			TSetVmpInfoRsp tRsp;
			tRsp.m_wConfID = ptVmpReq->m_wConfID;
			tRsp.m_emRet = EmBrdVmpRet_Fail;
			memcpy(&tRsp.m_tReq, ptVmpReq, sizeof(TSetVmpInfoRsp));
			cMsg.SetEvent(ev_UMS_UMC_SetBrdVmp_Ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&tRsp, sizeof(TSetVmpInfoRsp));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventBrdVmpReq( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TBrdVmpReq* ptVmpReq	= (TBrdVmpReq*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventBrdVmpReq, confID:%d, brd:%d, EqpID:%d\n", 
		ptVmpReq->m_wConfID, ptVmpReq->m_bBrd, ptVmpReq->m_tEqp.m_byEqpID));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		if (VALID_CONF_ID(ptVmpReq->m_wConfID) && m_atCall[ptVmpReq->m_wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(ev_UMC_UMS_BrdVmp_Req);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(ptVmpReq->m_wConfID), 0, UMS_SERVICE_APP_INST);
		}
		else
		{
			TBrdVmpRsp tRsp;
			tRsp.m_wConfID = ptVmpReq->m_wConfID;
			tRsp.m_emRet = EmBrdVmpRet_Fail;
			memcpy(&tRsp.m_tReq, ptVmpReq, sizeof(TBrdVmpReq));
			cMsg.SetEvent(ev_UMS_UMC_BrdVmp_Ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&tRsp, sizeof(TBrdVmpReq));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
}

void CUmsCallHandleService::EventRervesBrdVmpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TRersvesEqpRsp*  tInd = (TRersvesEqpRsp*) ( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventRervesBrdVmpInd, confID:%d, EqpID:%d, Ret:%d\n", 
							tInd->m_wConfID, tInd->m_tRersvesReq.m_tEqp.m_byEqpID, tInd->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventSetBrdVmpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TSetVmpInfoRsp*  tInd = (TSetVmpInfoRsp*) ( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventSetBrdVmpInd, confID:%d, EqpID:%d, Ret:%d\n", 
		tInd->m_wConfID, tInd->m_tReq.m_tEqp.m_byEqpID, tInd->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventBrdVmpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TBrdVmpRsp*  tInd = (TBrdVmpRsp*) ( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventBrdVmpInd, confID:%d, EqpID:%d, Ret:%d\n", 
		tInd->m_wConfID, tInd->m_tReq.m_tEqp.m_byEqpID, tInd->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventBrdVmpNtfy( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TBrdVmpResArray tArray = *(TBrdVmpResArray*)(pDataBuf + sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventBrdVmpNtfy. dtl info tplogdtl. vmpNum:%d\n", tArray.m_wNum));
	TBrdVmpResNtfy* tInd;
	for ( u16 wIndex = 0; wIndex < tArray.m_wNum; wIndex ++ )
	{
		tInd = &tArray.m_atVmpNtfy[wIndex];
		MdlLowHint(Ums_Mdl_Service, (" oprtype:%d, auto:%d, stat:%d, eqpID:%d, style:%d, channum:%d, speakerindx:%d, chairindx:%d, %s\n", 
			tInd->m_emOpr, tInd->m_bVmpAuto, tInd->m_emStat, tInd->m_tEqpInfo.m_byEqpID, tInd->m_tVmpStyle.m_emVmpStyle, tInd->m_tVmpStyle.m_wChnlNum,
			tInd->m_tVmpStyle.m_wSpeakerIndx, tInd->m_tVmpStyle.m_wDualIndx, tInd->m_tEqpInfo.m_szEqpAlias));
	}
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventSuspendPollInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	u16 wConfId = *(u16*) ( pDataBuf + sizeof(TLogUser) );
	EmTPPollResult  emRet = *(EmTPPollResult*)( pDataBuf + sizeof(TLogUser) + sizeof(u16) );
	
	MdlHint(Ums_Mdl_Service, ("EventSuspendPollInd, confID:%d, EmTPPollResult:(%d->%s)\n", 
		wConfId, TpEnumIdString(EmTPPollResult, emRet) ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventPollStatNtfy( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TTpPollStat tStat = *(TTpPollStat*) ( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventPollStatNtfy, confID:%d, Stat:(%d->%s)\n", tStat.m_wConfID, TpEnumIdString(EmPollStat, tStat.m_emStat) ));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventAudMixVacCmd( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfAuxMixVacOpr* ptVac	= (TConfAuxMixVacOpr*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptVac->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventAudMixVacCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(ev_AuxMixVacSwitch);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			ptVac->m_wOprRet = TP_RET_ERROR;
			cMsg.SetEvent(ev_AuxMixVacSwitchInd);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(ptVac, sizeof(TConfAuxMixVacOpr));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventAudMixVacInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfAuxMixVacOpr* ptVac	= (TConfAuxMixVacOpr*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventAudMixVacInd, confID:%d, bVacOn:%d, bRet:%d\n", ptVac->m_wConfID, ptVac->m_bVacOn,
		ptVac->m_wOprRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventSaveBrdVmpCfg( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TTpVmpMemberCfg* ptCfg	= (TTpVmpMemberCfg*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCfg->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventSaveBrdVmpCfg, confID:%d, From:%s, Style:%d, Num:%d\n", wConfID, MsgFrom(wAppID),
		ptCfg->m_emStyle, ptCfg->m_wEpNum));
	
	CTpMsg cMsg;
	if (AID_UMSUE_APP == wAppID)
	{
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(ev_UMC_UMS_SaveVmpCfg_Cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			BOOL32 bRet = FALSE;
			cMsg.SetEvent(ev_UMS_UMC_SaveVmpCfg_Ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&bRet, sizeof(bRet));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	else if( AID_UMSCONFMGR == wAppID )
	{//通知界面
		cMsg.SetEvent(ev_UMC_UMS_SaveVmpCfg_Cmd);
		cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
		cMsg.CatBody(ptCfg, sizeof(TTpVmpMemberCfg));
		cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
	}
	return;
}

void CUmsCallHandleService::EventSaveBrdVmpCfgInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TTpVmpMemberCfgInd* ptInd = (TTpVmpMemberCfgInd*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventSaveBrdVmpCfgInd, confID:%d, bRet:%d\n", ptInd->m_wConfID, ptInd->m_bRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventUmsJoinConfReq( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{

	TTPConfEpInfo* ptInfo = (TTPConfEpInfo*)(pDataBuf+sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("EventUmsJoinConfReq, confID:%d,CallAddr:%s\n",ptInfo->m_wConfID,ptInfo->m_tCallAddr.GetValidAlias().m_abyAlias));

	TPBroadMsgToUi(wEvent, pDataBuf , wDataSize);

}
void CUmsCallHandleService::EventUmsJoinConfNtfy(u16 wEvent,u8* pData,u16 wDataSize)
{
	u16 wConfID = *(u16*) (pData + sizeof(TLogUser) );
	TTpCallAddr* tAddr = (TTpCallAddr*)(pData + sizeof(TLogUser) + sizeof(TTpCallAddr) );

	MdlHint(Ums_Mdl_Service,("EventUmsJoinConfNtfy,confID:%d,ConfName:%s\n",wConfID,tAddr->GetValidAlias().m_abyAlias));

	TPBroadMsgToUi(wEvent, pData , wDataSize);
	
}
void CUmsCallHandleService::EventUmsJoinConfAck( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TTPConfEpInfo* tInfo = (TTPConfEpInfo*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventUmsJoinConfAck,confID:%d,CallAddr:%s,bPermit:%d\n",tInfo->m_wConfID,tInfo->m_tCallAddr.GetValidAlias(),tInfo->m_bPermit));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsJoinConf_Ack);
		cMsg.SetBody(pData, ptMsg->GetBodyLen());
		cMsg.Post(UMS_CALL_APP_INST(tInfo->m_wConfID), 0, UMS_SERVICE_APP_INST);	
	}

	return ;
}
void CUmsCallHandleService::EventFeccCameraReq( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser*  ptUser = (TLogUser*)pData;
	TCamReq*   ptInfo = (TCamReq*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventFeccCameraReq,confID:%d, dstId:%d, FeccAct:%d, CamReq:%d\n",
					ptInfo->m_wConfID, ptInfo->m_wEpID,
					ptInfo->m_emCamAct, ptInfo->m_emCamReq));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_FeccCamera_Req);
		cMsg.SetBody(pData, ptMsg->GetBodyLen());
		cMsg.Post(UMS_CALL_APP_INST(ptInfo->m_wConfID), 0, UMS_SERVICE_APP_INST);	
	}
	
	return ;
}

void CUmsCallHandleService::EventFeccPrePosReq( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser*  ptUser = (TLogUser*)pData;
	TPrePos* ptInfo = (TPrePos*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventFeccPrePosReq,confID:%d, dstId:%d, PrePos:%d, SaveNo:%d\n",
		ptInfo->m_wConfID, ptInfo->m_wEpID,
		ptInfo->m_emPosAct, ptInfo->m_dwSaveNo));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_FeccPrePos_Req);
		cMsg.SetBody(pData, ptMsg->GetBodyLen());
		cMsg.Post(UMS_CALL_APP_INST(ptInfo->m_wConfID), 0, UMS_SERVICE_APP_INST);	
	}
	
	return ;
}

void CUmsCallHandleService::EventFeccSelVidReq( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser*  ptUser = (TLogUser*)pData;
	TSelVid* ptInfo = (TSelVid*)(pData+sizeof(TLogUser));
	
	MdlHint(Ums_Mdl_Service, ("EventFeccSelVidReq,confID:%d, dstId:%d, SelAct:%d, VidNo:%d\n",
		ptInfo->m_wConfID, ptInfo->m_wEpID,
		ptInfo->m_emVidAct, ptInfo->m_dwVidNo));
	
	if (AID_UMSUE_APP == wAppID)
	{
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_FeccSelVid_Req);
		cMsg.SetBody(pData, ptMsg->GetBodyLen());
		cMsg.Post(UMS_CALL_APP_INST(ptInfo->m_wConfID), 0, UMS_SERVICE_APP_INST);	
	}
	
	return ;
}

namespace UmsTpmsg {
    void tplocaltime(struct tm& t, const time_t& ti);
} //namespace UmsTpmsg

void CUmsCallHandleService::ShowAllConf()
{
	msgprintnotime("UmsCallHandleService. All Conf info:\n");
	TCallMgr* ptCall = NULL;
	struct tm t;
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM+1; wIndex++)
	{
		ptCall = &m_atCall[wIndex];
		if (NULL == ptCall || (!ptCall->m_bIsRunning && 0 == ptCall->m_tEndConfTime))
		{
			continue;
		}

		tplocaltime(t, ptCall->m_tEndConfTime);

		msgprintnotime("Index:%d, bIsRunning:%d, User:%s, ConfName:%s, e164:%s, bCallByTimer:%d, EndTime:%2.2u-%2.2u %2.2u:%2.2u:%2.2u\n", 
			wIndex, ptCall->m_bIsRunning, ptCall->m_tUmcUser.m_achName, 
			ptCall->m_achConfName, ptCall->m_achConfE164, ptCall->m_bCallByTimer, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	}
	return;
}




void CUmsCallHandleService::EventUptateRollCallCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfRollCallInfo* ptRollCallInfo	= (TConfRollCallInfo*)(pData+sizeof(TLogUser));
	u16 wConfID = ptRollCallInfo->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventUptateRollCallCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_StartRollCall_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			cMsg.SetEvent(evtp_StartRollCall_Ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}


void CUmsCallHandleService::EventUptateRollCallInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TConfRollCallInfo* pCallInfo = (TConfRollCallInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventUptateRollCallInd, confID:%d, bStart:%d,  m_emRet:%d\n", 
		pCallInfo->m_wConfID, pCallInfo->m_bStart, pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}


void CUmsCallHandleService::EventUptateRollCallNextEpCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TRollCallNextEpInfo* ptRollCallInfo	= (TRollCallNextEpInfo*)(pData+sizeof(TLogUser));
	u16 wConfID = ptRollCallInfo->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventUptateRollCallNextEpCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_RollCallNext_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			cMsg.SetEvent(evtp_RollCallNext_Ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}


void CUmsCallHandleService::EventUptateRollCallNextEpInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TRollCallNextEpInfo* pCallInfo = (TRollCallNextEpInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventUptateRollCallNextEpInd, confID:%d,  m_emRet:%d\n", 
		pCallInfo->m_wConfID,  pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}


void CUmsCallHandleService::EventUptateRollCallListCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TUpdataRollCallList* ptListInfo	= (TUpdataRollCallList*)(pData+sizeof(TLogUser));
	u16 wConfID = ptListInfo->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventUptateRollCallListCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_RollCallUpdateList_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			cMsg.SetEvent(evtp_RollCallUpdateList_Ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}



void CUmsCallHandleService::EventUptateRollCallListInd(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TUpdataRollCallListRes* pCallInfo = (TUpdataRollCallListRes*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventUptateRollCallListInd, confID:%d\n", 
		pCallInfo->m_wConfID));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}



void CUmsCallHandleService::EventRollCallPresentStateCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TRollCallPresentStateMsg* ptInfo	= (TRollCallPresentStateMsg*)(pData+sizeof(TLogUser));
	u16 wConfID = ptInfo->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventRollCallPresentStateCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_RollCall_PresentState);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		
	}
	return;
}

void CUmsCallHandleService::EventRollCallPresentStateNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TRollCallPresentStateMsg* pCallInfo = (TRollCallPresentStateMsg*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventRollCallPresentStateNotify, confID:%d\n", 
		pCallInfo->m_wConfID));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}






void CUmsCallHandleService::EventRollCallInfoNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TConfRollCallInfo* pInfo = (TConfRollCallInfo*)( pDataBuf + sizeof(TLogUser) );
	
	MdlHint(Ums_Mdl_Service, ("EventRollCallInfoNotify, confID:%d, IsStart:%d, \n", pInfo->m_wConfID, pInfo->m_bStart));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}

void CUmsCallHandleService::EventAudMixListCmd( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TUmsAudMixListCmd* ptCmd	= (TUmsAudMixListCmd*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfId;
	
	MdlHint(Ums_Mdl_Service, ("EventAudMixListCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_ConfAudMixList_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			TUmsAudMixListCmdRes tRes;
			tRes.m_wConfId = wConfID;
			tRes.m_tList = ptCmd->m_tList;
			cMsg.SetEvent(evtp_ConfAudMixList_ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&tRes, sizeof(TUmsAudMixListCmdRes));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}


void CUmsCallHandleService::EventAudMixListInd(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TUmsAudMixListCmdRes* pCallInfo = (TUmsAudMixListCmdRes*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventAudMixListInd, confID:%d\n", 
		pCallInfo->m_wConfId));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}



void CUmsCallHandleService::EventAudMixModeCmd( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TUmsAudMixInfo* ptCmd	= (TUmsAudMixInfo*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfId;
	
	MdlHint(Ums_Mdl_Service, ("EventAudMixModeCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_ConfAudMixMode_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			TUmsAudMixModeCmdRes tRes;
			tRes.m_wConfId = wConfID;
			tRes.m_emRes = em_umsaudmixres_unkown;

			cMsg.SetEvent(evtp_ConfAudMixMode_ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&tRes, sizeof(TUmsAudMixModeCmdRes));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}



void CUmsCallHandleService::EventAudMixModeInd(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TUmsAudMixModeCmdRes* pCallInfo = (TUmsAudMixModeCmdRes*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventAudMixModeInd, confID:%d, Mod:%d,  m_emRet:%d\n", 
		pCallInfo->m_wConfId, pCallInfo->m_emCmdMode, pCallInfo->m_emRes));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}



void CUmsCallHandleService::EventAudMixNotify(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TUmsAudMixInfo* pCallInfo = (TUmsAudMixInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventAudMixNotify, confID:%d, Mod:%d\n", 
		pCallInfo->m_wConfId, pCallInfo->m_emMode));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
	
	return ;
}



void CUmsCallHandleService::EventGetConfBrdVidAudCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;

	TUmsGetConfBrdVidAudInfo* ptCmd	= (TUmsGetConfBrdVidAudInfo*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventGetConfBrdVidAudCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_GetConfBrdVidAud_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			ptCmd->m_emRet = em_GetConfBrdVidAudRet_idleconf;
			cMsg.SetEvent(evtp_GetConfBrdVidAud_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventGetConfBrdVidAudInd(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TUmsGetConfBrdVidAudInfo* pCallInfo = (TUmsGetConfBrdVidAudInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventGetConfBrdVidAudInd, confID:%d, userindex:%d  ret:%d\n", 
		pCallInfo->m_wConfID, pCallInfo->m_wUserIndex, pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventReleaseGetConfBrdVidAudCmd(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TUmsReleaseConfBrdVidAudInfo* ptCmd	= (TUmsReleaseConfBrdVidAudInfo*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventReleaseGetConfBrdVidAudCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_ReleasConfBrdVidAud_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			ptCmd->m_emRet = em_ReleaseConfBrdVidAudRet_idleconf;
			cMsg.SetEvent(evtp_ReleasConfBrdVidAud_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventReleaseGetConfBrdVidAudInd(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TUmsReleaseConfBrdVidAudInfo* pCallInfo = (TUmsReleaseConfBrdVidAudInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventReleaseGetConfBrdVidAudInd, confID:%d, ret:%d\n", 
		pCallInfo->m_wConfID, pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}



void CUmsCallHandleService::EventGetConfBrdVidAudaskKey(CTpMsg* const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	
	TUmsGetConfBrdVidAudAskKey* ptCmd	= (TUmsGetConfBrdVidAudAskKey*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfId;
	
	MdlLowDtl(Ums_Mdl_Service, ("EventGetConfBrdVidAudaskKey, confID:%d, From:%s user:%d  askscreen[0~4]:%d\n",
		   wConfID, 
		   MsgFrom(wAppID),
		   ptCmd->m_wUserIndex,
		   ptCmd->m_wScreenIndex));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_GetConfBrdVidAudAskKey);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		
	}
	return;
}

void CUmsCallHandleService::EventGetConfVmpVidCmd( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	
	TUmsGetVmpVidInfo* ptCmd	= (TUmsGetVmpVidInfo*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventGetConfVmpVidCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_GetConfVmpVid_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			ptCmd->m_emRet = em_GetVmpVidRet_idleconf;
			cMsg.SetEvent(evtp_GetConfVmpVid_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventGetConfVmpVidInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TUmsGetVmpVidInfo* pCallInfo = (TUmsGetVmpVidInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventGetConfVmpVidInd, confID:%d, userindex:%d  ret:%d\n", 
		pCallInfo->m_wConfID, pCallInfo->m_wVmpInfoIndex, pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventReleaseConfVmpVidCmd( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TUmsReleaseVmpVidInfo* ptCmd	= (TUmsReleaseVmpVidInfo*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventReleaseConfVmpVidCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_ReleaseConfVmpVid_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			ptCmd->m_emRet = em_ReleaseVmpVidRet_idleconf;
			cMsg.SetEvent(evtp_ReleaseConfVmpVid_ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventReleaseConfVmpVidInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TUmsReleaseVmpVidInfo* pCallInfo = (TUmsReleaseVmpVidInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventReleaseConfVmpVidInd, confID:%d, ret:%d\n", 
		pCallInfo->m_wConfID, pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventGetConfVmpVidAskKey( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	
	TUmsGetVmpVidAskKey* ptCmd	= (TUmsGetVmpVidAskKey*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfId;
	
	MdlLowDtl(Ums_Mdl_Service, ("EventGetConfVmpVidAskKey, confID:%d, From:%s user:%d\n",
		wConfID, MsgFrom(wAppID), ptCmd->m_wVmpInfoIndex));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_GetConfVmpVidAskKey_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		
	}
	return;
}

void CUmsCallHandleService::EventConfVmpVidNotify( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TUmsVmpVidData* pCallInfo = (TUmsVmpVidData*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventConfVmpVidNotify, confID:%d, userindex:%d  ret:%d\n", 
		pCallInfo->m_wConfID, pCallInfo->m_wVmpInfoIndex, pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}


void CUmsCallHandleService::GetValue(TConfTemplateLocal&tRhs,const TTPConfMeet&tRes)
{

	tRhs.m_wID = ntohs(tRes.m_wID);
	
	u16 wIndex = 0;
	
	memcpy(tRhs.m_achConfName, tRes.m_achConfName, TP_MAX_ALIAS_LEN+1);
	memcpy(tRhs.m_achConfE164, tRes.m_achConfE164, TP_MAX_ALIAS_LEN+1);
	
	tRhs.m_wConfBitRate = ntohs(tRes.m_wConfBitRate);

	tRhs.m_wHpDualBitRate = ntohs(tRes.m_wHpDualBitRate);

	
	tRhs.m_tEncrypt = tRes.m_tEncrypt;
	tRhs.m_tEncrypt.m_emEncryptModel = (EmTPEncryptType)ntohl(tRes.m_tEncrypt.m_emEncryptModel);
	tRhs.m_bDefaultEncrypt = (BOOL32)ntohl(tRes.m_bDefaultEncrypt);

	
	tRhs.m_wMainNum = ntohs(tRes.m_wMainNum);
	tRhs.m_wMinorNum = ntohs(tRes.m_wMinorNum);
	
	for ( wIndex = 0; wIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; wIndex ++ )
	{
		tRhs.m_atTpMainVideoRes[wIndex].m_emFormat = (EmTpVideoFormat)ntohl(tRes.m_atTpMainVideoRes[wIndex].m_emFormat);
		tRhs.m_atTpMainVideoRes[wIndex].m_emQualityLvl = (EmTpVideoQualityLevel)ntohl(tRes.m_atTpMainVideoRes[wIndex].m_emQualityLvl);
		tRhs.m_atTpMainVideoRes[wIndex].m_emRes = (EmTpVideoResolution)ntohl(tRes.m_atTpMainVideoRes[wIndex].m_emRes);
		tRhs.m_atTpMainVideoRes[wIndex].m_wBitrate = ntohs(tRes.m_atTpMainVideoRes[wIndex].m_wBitrate);
		tRhs.m_atTpMainVideoRes[wIndex].m_wFrameRate = ntohs(tRes.m_atTpMainVideoRes[wIndex].m_wFrameRate);
	}
	
	for ( wIndex = 0; wIndex < TP_CONF_MAX_MINOR_VIDEO_RES_NUM; wIndex ++ )
	{
		tRhs.m_atTpMinorVideoRes[wIndex].m_emFormat = (EmTpVideoFormat)ntohl(tRes.m_atTpMinorVideoRes[wIndex].m_emFormat);
		tRhs.m_atTpMinorVideoRes[wIndex].m_emQualityLvl = (EmTpVideoQualityLevel)ntohl(tRes.m_atTpMinorVideoRes[wIndex].m_emQualityLvl);
		tRhs.m_atTpMinorVideoRes[wIndex].m_emRes = (EmTpVideoResolution)ntohl(tRes.m_atTpMinorVideoRes[wIndex].m_emRes);
		tRhs.m_atTpMinorVideoRes[wIndex].m_wBitrate = ntohs(tRes.m_atTpMinorVideoRes[wIndex].m_wBitrate);
		tRhs.m_atTpMinorVideoRes[wIndex].m_wFrameRate = ntohs(tRes.m_atTpMinorVideoRes[wIndex].m_wFrameRate);
	}
	
	tRhs.m_wAudFmtNum = ntohs(tRes.m_wAudFmtNum);
	for ( wIndex = 0; wIndex < TP_CONF_MAX_AUD_FMT_NUM; wIndex ++ )
	{
		tRhs.m_atAudFmt[wIndex].m_emFormat = (EmTpAudioFormat)ntohl(tRes.m_atAudFmt[wIndex].m_emFormat);
		tRhs.m_atAudFmt[wIndex].m_emSampleFreq = (EmTPAACSampleFreq)ntohl(tRes.m_atAudFmt[wIndex].m_emSampleFreq);
		tRhs.m_atAudFmt[wIndex].m_emChnlCfg = (EmTPAACChnlCfg)ntohl(tRes.m_atAudFmt[wIndex].m_emChnlCfg);
		tRhs.m_atAudFmt[wIndex].m_byReserve1 = tRes.m_atAudFmt[wIndex].m_byReserve1;
		tRhs.m_atAudFmt[wIndex].m_byReserve2 = tRes.m_atAudFmt[wIndex].m_byReserve2;
	}
	
	tRhs.m_wUpBandWid = ntohl(tRes.m_wUpBandWid);
	tRhs.m_wDownBandWid = ntohl(tRes.m_wDownBandWid);
	
	tRhs.m_atEpList.m_wNum = ntohs(tRes.m_atEpList.m_wNum);
	for ( wIndex = 0; wIndex < TP_CONF_MAX_EPNUM; wIndex ++ )
	{
		tRhs.m_atEpList.m_tCnsList[wIndex].m_wEpID = ntohs(tRes.m_atEpList.m_tCnsList[wIndex].m_wEpID);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_bAliasIP = ntohl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_bAliasIP);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_byCallType = (EmTpAliasType)ntohl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_byCallType);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP = tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP;
		
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_byType = (EmTpAliasType)ntohl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_byType);
		strncpy(tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias, tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
		
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_byType = (EmTpAliasType)ntohl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_byType);
		strncpy(tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias, tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
		}

}

void CUmsCallHandleService::EventGetEpScreenInfoCmd( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	
	TGetEpScreenInfo* ptCmd	= (TGetEpScreenInfo*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventGetEpScreenInfoCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_GetEpSreenStream_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			TGetEpScreenInd tInd;
			tInd.m_wConfID	= ptCmd->m_wConfID;
			tInd.m_wEpID	= ptCmd->m_wEpID;
			tInd.m_wScreenID = ptCmd->m_wScreenID;
			tInd.m_emRet	= em_GetEpSreenStreamRet_idleconf;

			cMsg.SetEvent(evtp_GetEpSreenStream_Ind);
			cMsg.SetBody(ptUserTmp, sizeof(TLogUser));
			cMsg.CatBody(&tInd, sizeof(tInd));
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventGetEpScreenInfoInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TGetEpScreenInd* ptCallInfo = (TGetEpScreenInd*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventGetEpScreenInfoInd, confID:%d, epId:%d  ScreenId:%d, UserIndex:%d, emRet:%d\n", 
		ptCallInfo->m_wConfID, ptCallInfo->m_wEpID, ptCallInfo->m_wScreenID,
		ptCallInfo->m_wUserIndex, ptCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);
}

void CUmsCallHandleService::EventReleaseEpScreenInfoCmd( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TReleaseEpScreenInfo* ptCmd	= (TReleaseEpScreenInfo*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfID;
	
	MdlHint(Ums_Mdl_Service, ("EventReleaseEpScreenInfoCmd, confID:%d, From:%s\n", wConfID, MsgFrom(wAppID) ));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_ReleaseEpSreenStream_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		else
		{
			ptCmd->m_emRet = em_ReleaseEpSreenStreamRet_idleconf;
			cMsg.SetEvent(evtp_ReleaseEpSreenStream_Ind);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_UE_APP_INST, 0, UMS_SERVICE_APP_INST);
		}
	}
	return;
}

void CUmsCallHandleService::EventReleaseEpScreenInfoInd( u16 wEvent, u8* pDataBuf, u16 wDataSize )
{
	TReleaseEpScreenInfo* pCallInfo = (TReleaseEpScreenInfo*)(pDataBuf+sizeof(TLogUser));	
	
	MdlHint(Ums_Mdl_Service, ("EventReleaseEpScreenInfoInd, confID:%d, wUserIndex:%d, ret:%d\n", 
		pCallInfo->m_wConfID, pCallInfo->m_wUserIndex, pCallInfo->m_emRet));
	
	TPTransMsgToUi(wEvent, pDataBuf, wDataSize);	
}

void CUmsCallHandleService::EventGetConfEpScreenAskKey( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	
	TGetEpScreenAskKey* ptCmd	= (TGetEpScreenAskKey*)(pData+sizeof(TLogUser));	
	u16 wConfID = ptCmd->m_wConfId;
	
	MdlLowDtl(Ums_Mdl_Service, ("EventGetConfEpScreenAskKey, confID:%d, From:%s user:%d\n",
		wConfID, MsgFrom(wAppID), ptCmd->m_wUserIndex));
	
	if (AID_UMSUE_APP == wAppID)
	{	
		CTpMsg cMsg;
		if (VALID_CONF_ID(wConfID) && m_atCall[wConfID].m_bIsRunning)
		{
			cMsg.SetEvent(evtp_GetEpSreenAskKey_cmd);
			cMsg.SetBody(pData, ptMsg->GetBodyLen());
			cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
		}
		
	}
}


void CUmsCallHandleService::EventUpdateTempConfName( CTpMsg* const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());

	u16 wConfID = *(u16*)pData;
	TTPAlias *ptConfNameAlias = (TTPAlias *)(pData + sizeof(u16));

	u32 dwConfNameLen = strlen(ptConfNameAlias->m_abyAlias);

	MdlHint(Ums_Mdl_Service, ("EventUpdateTempConfName, confID:%d, From:%s UpdateConfName:%s\n",
		wConfID, MsgFrom(wAppID), ptConfNameAlias->m_abyAlias));

    if (wConfID == 0 || 
		wConfID > TP_UMS_MAX_CONFNUM ||
		!m_atCall[wConfID].m_bIsRunning ||
		dwConfNameLen > TP_MAX_ALIAS_LEN ||
		dwConfNameLen == 0)
	{	
		MdlError(Ums_Mdl_Service, ("EventUpdateTempConfName update error! confID:%d, UpdateConfName:%s, dwConfNameLen:%d\n",
		                           wConfID, ptConfNameAlias->m_abyAlias, dwConfNameLen));
		return;
	}

    strcpy(m_atCall[wConfID].m_achConfName, ptConfNameAlias->m_abyAlias);

	return;
}