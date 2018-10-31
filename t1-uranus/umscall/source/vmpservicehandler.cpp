#include "tplog.h"
#include "tpsys.h"
#include "umsobject.h"
#include "vmpserviecehandler.h"
#include "innereventumsvmp.h"
#include "eventoutmpu2tp.h"
#include "callinnerstruct.h"
#include "umsconfinst.h"
#include "umsxmpinterface.h"
#include "innereventxmpuvmp.h"
#include "umsconfigex.h"

void CServiceHandler::PostMsgToEqpModule(u16 wEvent, void* param, u16 wLength) const
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(param, wLength);
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, 0));
}

void CServiceHandler::PostMsgToXmpuEqp(u16 wEvent, void* param, u16 wLength) const
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(param, wLength);
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, 0));
}

CVmpServiceHandler::CVmpServiceHandler()
{

}

CVmpServiceHandler::~CVmpServiceHandler()
{
	CEqpService::Instance().FlushXmpuMpu2();
}

const CBaseService* CVmpServiceHandler::Assign(ServiceCB cbFun, CUmsConfInst* pcInst) const
{
#ifdef _USE_XMPUEQP_
	if (!CUmsConfigEx::GetInstance()->GetXmpu5Used())
	{
		return NULL;
	}
	else
	{
		return AssignXmpuEqp(cbFun, pcInst);
	}

#endif

	if (NULL == cbFun || NULL == pcInst)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Assign Invalid call back function.\n"));
		return NULL;
	}

	const CBaseService* pcBaseService = CEqpService::Instance().Assign(em_mpu2tp_service, cbFun, pcInst);
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Assign serivice failed.\n"));
		return NULL;
	}

	TServiceBaseInfo tInfo;
	tInfo.m_emType = pcBaseService->GetType();
	tInfo.m_wServiceID = pcBaseService->GetServiceID();
	
	PostMsgToEqpModule(ev_vmp_Assgin_Req, &tInfo, sizeof(tInfo));



	
	//设置量子码流秘钥
	for ( u16 wIndex = 0; wIndex < TP_MAX_OLD_KEY_NUM; wIndex ++ )
	{
		if (0 == pcInst->MediaKey(wIndex).m_dwQtFlag)
		{
			continue;
		}
		SetMediaKey(pcBaseService, pcInst->MediaKey(wIndex), pcInst);
	}

	return pcBaseService;
}

void CVmpServiceHandler::Release(const CBaseService* pcService)
{
#ifdef _USE_XMPUEQP_
	ReleaseXmpuMpu2(pcService);
	return;
#endif
	Stop(pcService);
	if (NULL != pcService)
	{
		CEqpService::Instance().Release(pcService, em_mpu2tp_service);
	}
}


BOOL32 CVmpServiceHandler::Start( const CBaseService* pcBaseService, void* useParam )
{
	if (NULL == useParam)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Start Invalid param.\n"));
		return FALSE;
	}
	
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Start Invalid service.\n"));
		return FALSE;
	}
	
	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Start Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return FALSE;
	}

	const CServiceInfo* pcService = (const CServiceInfo*)pcBaseService;
	if (pcService->IdleStatus())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Start Service is Idle.\n"));
		return FALSE;
	}

	if (!CEqpService::Instance().SetWorking(em_mpu2tp_service, pcBaseService->GetServiceID()))
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Start Service is setworkding failed.\n"));
		return FALSE;
	}

	TVmpStartInfo tInfo;
	memcpy(&(tInfo.m_tVmpParam), useParam, sizeof(TVmpUseParam));
	tInfo.m_wServiceID = pcBaseService->GetServiceID();
#ifdef _USE_XMPUEQP_
	CServiceInfo* pcInfo = (CServiceInfo*)pcBaseService;
	if (pcInfo->IsOnline())
	{
		PostMsgToXmpuEqp(evXmpu_StartMpu2_Req, &tInfo, sizeof(tInfo));
	}
#else
	PostMsgToEqpModule(ev_vmp_Start_Req, &tInfo, sizeof(tInfo));
#endif
	

	// 把合成器out的风格和格式保存一下
	CEqpService::Instance().SaveInfo(em_mpu2tp_service, tInfo.m_wServiceID, tInfo.m_tVmpParam.m_tStyleInfo, tInfo.m_tVmpParam.m_tEncParam);
	CEqpService::Instance().FlushXmpuMiddleAddrToMpu2(pcBaseService);
	return TRUE;
}


BOOL32 CVmpServiceHandler::ChangeMode(const CBaseService* pcBaseService, void* useParam)
{
	if (NULL == useParam)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::ChangeMode Invalid param.\n"));
		return FALSE;
	}

	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::ChangeMode Invalid service.\n"));
		return FALSE;
	}

	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::ChangeMode Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return FALSE;
	}

	const CServiceInfo* pcService = (const CServiceInfo*)pcBaseService;
	if (!pcService->WorkStatus())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::ChangeMode Service is not in working.\n"));
		return FALSE;
	}

	TVmpUseParam* ptParam = (TVmpUseParam*)useParam;

	if (CEqpService::Instance().IsSameInfo(em_mpu2tp_service, pcService->GetServiceID(), ptParam->m_tStyleInfo, ptParam->m_tEncParam))
	{// 比较老风格和格式，如果一致无需ChangeMode，直接返回；不一致保存最新的，接下来ChangeMode
		MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::ChangeMode SameMode,  serviceId:%d not changeed.\n", pcService->GetServiceID()));
		return TRUE;
	}

	// 刷新xmpu临时地址到实际地址的交换
	CEqpService::Instance().FlushXmpuMiddleAddrToMpu2(pcBaseService);
	
#ifdef _USE_XMPUEQP_
	TVmpStartInfo tInfo;
	memcpy(&(tInfo.m_tVmpParam), useParam, sizeof(TVmpUseParam));
	tInfo.m_wServiceID = pcBaseService->GetServiceID();
	CServiceInfo* pcInfo = (CServiceInfo*)pcBaseService;
	if (pcInfo->IsOnline())
	{
		PostMsgToXmpuEqp(evXmpu_StartMpu2_Req, &tInfo, sizeof(tInfo));
	}
#else
	TVmpMdyInfo tInfo;
	memcpy(&(tInfo.m_tEncParam), &(ptParam->m_tEncParam), sizeof(TVmpEncParam));
	memcpy(&(tInfo.m_tStyleInfo), &(ptParam->m_tStyleInfo), sizeof(TVmpStyleInfo));
	tInfo.m_wServiceID = pcBaseService->GetServiceID();

	PostMsgToEqpModule(ev_vmp_Mdy_Style_Req, &tInfo, sizeof(tInfo));
#endif

	return TRUE;
}

void CVmpServiceHandler::Stop(const CBaseService* pcBaseService) const
{
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Stop Invalid service pointer.\n"));
		return ;
	}

	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::Stop Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return ;
	}

	const CServiceInfo* pcService = (const CServiceInfo*)pcBaseService;
	if (pcService->IdleStatus())
	{
		MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::Stop Service is already Idel.\n"));
		return ;
	}

	TServiceBaseInfo tInfo;
	tInfo.m_emType = pcBaseService->GetType();
	tInfo.m_wServiceID = pcBaseService->GetServiceID();

	PostMsgToEqpModule(ev_vmp_Stop_Req, &tInfo, sizeof(tInfo));
}

void CVmpServiceHandler::GetRcvChanAddr(TServiceAddr& tRes, const CBaseService* pcBaseService, u16 wChanIndex)
{
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::GetRcvChanAddr Invalid service pointer.\n"));
		return ;
	}

	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::GetRcvChanAddr Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return ;
	}

#ifdef _USE_XMPUEQP_
	((CServiceInfo*)pcBaseService)->GetDecAddr(tRes, wChanIndex);
#else
	//vmp的rtp接收
	tRes.m_tAddr.m_tRtpAddr.m_wPort = pcBaseService->GetEqpStartPort() + wChanIndex * UMS_VMP_PORT_SPAN;
	tRes.m_tAddr.m_tRtpAddr.m_dwIP = pcBaseService->GetEqpIP();

	//ums主控的rtcp接收
	tRes.m_tAddr.m_tBackRtcpAddr.m_wPort = pcBaseService->GetUmsStartPort() + wChanIndex + 2;
	tRes.m_tAddr.m_tBackRtcpAddr.m_dwIP = pcBaseService->GetMediaIP();

	tRes.m_dwMediaNode = pcBaseService->GetMediaNode();
#endif

	return ;
}

void CVmpServiceHandler::GetSndChanAddr(TServiceAddr& tRes, const CBaseService* pcBaseService)
{
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::GetSndChanAddr Invalid service pointer.\n"));
		return ;
	}
	
	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::GetSndChanAddr Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return ;
	}
#ifdef _USE_XMPUEQP_
	((CServiceInfo*)pcBaseService)->GetEncAddr(tRes);
#else
	tRes.m_dwMediaNode = pcBaseService->GetMediaNode();

	tRes.m_tAddr.m_tRtpAddr.m_wPort = pcBaseService->GetUmsStartPort();
	tRes.m_tAddr.m_tRtpAddr.m_dwIP = pcBaseService->GetMediaIP();

	tRes.m_tAddr.m_tBackRtcpAddr.m_wPort = pcBaseService->GetEqpStartPort() + 3 + 0 * UMS_VMP_PORT_SPAN;
	tRes.m_tAddr.m_tBackRtcpAddr.m_dwIP = pcBaseService->GetEqpIP();
#endif
	
	return ;
}

// xmpu外设接口暂缺
void CVmpServiceHandler::UpdateSpeakerSideLine( const CBaseService* pcBaseService, u8 byFlag[], u8 byNum )
{
#ifdef _USE_XMPUEQP_
//	UpdateXmpuSpeakerSideLine(pcBaseService, byFlag, byNum);
	return;
#endif
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::UpdateSpeakerSideLine Invalid service pointer.\n"));
		return ;
	}
	
	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::UpdateSpeakerSideLine Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return ;
	}
	
	const CServiceInfo* pcService = (const CServiceInfo*)pcBaseService;
	if (pcService->IdleStatus())
	{
		MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::UpdateSpeakerSideLine Service is already Idel.\n"));
		return ;
	}
	
	MdlLowDtl(Ums_Mdl_Call, ("[UpdateSpeakerSideLine] ServiceId:%d. (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", pcService->GetServiceID(),
		byFlag[0],byFlag[1],byFlag[2],byFlag[3],byFlag[4],byFlag[5],byFlag[6],byFlag[7],byFlag[8],byFlag[9]));

	TVmpSpeakerFlag tInfo;
	tInfo.m_wChanID = pcBaseService->GetServiceID();
	memcpy(tInfo.m_abyFlag, byFlag, sizeof(tInfo.m_abyFlag));
	
	PostMsgToEqpModule(ev_vmp_UpdateSpeakerSide_Req, &tInfo, sizeof(tInfo));
}

void CVmpServiceHandler::UpdateXmpuSpeakerSideLine( const CBaseService* pcBaseService, u8 byFlag[], u8 byNum )
{
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::UpdateXmpuSpeakerSideLine Invalid service pointer.\n"));
		return ;
	}

	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::UpdateXmpuSpeakerSideLine Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return ;
	}

	const CServiceInfo* pcService = (const CServiceInfo*)pcBaseService;
	if (pcService->IdleStatus())
	{
		MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::UpdateXmpuSpeakerSideLine Service is already Idel.\n"));
		return ;
	}

	MdlLowDtl(Ums_Mdl_Call, ("[UpdateXmpuSpeakerSideLine] ServiceId:%d. (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", pcService->GetServiceID(),
		byFlag[0],byFlag[1],byFlag[2],byFlag[3],byFlag[4],byFlag[5],byFlag[6],byFlag[7],byFlag[8],byFlag[9]));

	TVmpSpeakerFlag tInfo;
	tInfo.m_wChanID = pcBaseService->GetServiceID();
	memcpy(tInfo.m_abyFlag, byFlag, sizeof(tInfo.m_abyFlag));

	PostMsgToXmpuEqp(evXmpu_UpdateSpeakerSide_Req, &tInfo, sizeof(tInfo));
}

void CVmpServiceHandler::AskFrameToBaseService( const CBaseService* pcBaseService )
{
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::AskFrameToBaseService Invalid service pointer.\n"));
		return ;
	}
	
	if (em_mpu2tp_service != pcBaseService->GetType())
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::AskFrameToBaseService Invalid service type. Type:%d.\n", pcBaseService->GetType()));
		return ;
	}
#ifdef _USE_XMPUEQP_
	TTPVmpAskFrame tAskFrame;
	tAskFrame.m_byEqpID =  pcBaseService->GetServiceID();
	tAskFrame.m_byChanIndx = 0;

	PostMsgToXmpuEqp(evUms_XmpuAskVmpKey_Req, &tAskFrame, sizeof(tAskFrame));
#else
	TVmpAskFrame tInfo;
	tInfo.m_wChanID = pcBaseService->GetServiceID();
	tInfo.m_wMemberIndx = 0;

	PostMsgToEqpModule(ev_mpu2tp_AskFrame_Req, &tInfo, sizeof(tInfo));
#endif
	
}

void CVmpServiceHandler::SetMediaKey( const CBaseService* pcBaseService, const TTPQTMediaKeyInfo& tInfo, void* pcInst )
{
	CServiceInfo* pcServeice = NULL;
	for ( u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; wIndex ++ )
	{
		pcServeice = &CEqpService::Instance().ServeiceInfo(wIndex);
		
		if ( pcServeice->IdleStatus() || pcServeice->GetType() != em_mpu2tp_service )
		{
			continue;
		}
		
		if ( pcServeice->Param() != pcInst )
		{
			continue;
		}
		
		if ( pcBaseService != NULL && pcBaseService != pcServeice )
		{
			continue;
		}
		
		u16 wID = pcServeice->GetServiceID();
		
		u8 abyBuf[sizeof(u16) + sizeof(TTPQTMediaKeyInfo)] = {0};
		memcpy( abyBuf, &wID, sizeof(u16));
		memcpy( abyBuf + sizeof(u16), &tInfo, sizeof(TTPQTMediaKeyInfo));
		
		CTpMsg cMsg;
		cMsg.SetEvent(ev_vmp_SetMediaKey_Req);
		cMsg.SetBody(abyBuf, sizeof(abyBuf));
		cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, 0));
	}
}

void CVmpServiceHandler::Show(const CBaseService* pcBaseService )
{
	u32 dwRcvIP = pcBaseService->GetEqpIP();
	u32 dwLocalIP = pcBaseService->GetMediaIP();
 	msgprintnotime("ServiceID:%d, stat:%d(0:idle,1:assign,2:run,3:error), MediaNode:%d, Ds:"TPIPFORMAT" UmsStartPort:%d, Vmp:"TPIPFORMAT" VmpStartPort:%d\n", 
 		pcBaseService->GetServiceID(), ((CServiceInfo*)pcBaseService)->GetStatus(), pcBaseService->GetMediaNode(), u32ToIP(dwLocalIP), pcBaseService->GetUmsStartPort(), u32ToIP(dwRcvIP), pcBaseService->GetEqpStartPort());
}

BOOL32 CVmpServiceHandler::Handler(CTpMsg* const pcMsg)
{
	switch (pcMsg->GetEvent())
	{
	case ev_vmp_Start_Res:
		{
			EventStartRes(pcMsg);
		}
		break;

	case ev_vmp_Stop_Res:
		{
			EventStopRes(pcMsg);
		}
		break;

	case ev_vmp_Assgin_Res:
		{
			EventAssginRes(pcMsg);
		}
		break;

	case ev_vmp_Mdy_Style_Res:
		{
			EventMdyRes(pcMsg);
		}
		break;
	case ev_mpu2tp_AskFrame_Req:
		{
			EventAskFrame(pcMsg);
		}
		break;
	default:
		{
			return FALSE;
		}
		break;
	}

	return TRUE;
}

void CVmpServiceHandler::EventAssginRes( CTpMsg* const pcMsg )
{
	TVmpStartResult tInfo;
	TP_SAFE_CAST(tInfo, pcMsg->GetBody());
	
	MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::EventAssginRes ServiceID:%d, Res:%d.\n", 
		tInfo.m_tBaseInfo.m_wServiceID, tInfo.m_emRes));
	
	if (em_mpu2tp_service != tInfo.m_tBaseInfo.m_emType)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::EventAssginRes Invalid service.\n"));
		return ;
	}
	
	if (em_Res_Success != tInfo.m_emRes)
	{
		CEqpService::Instance().OperateRet(tInfo.m_tBaseInfo.m_emType, tInfo.m_tBaseInfo.m_wServiceID, em_Assgin_Service, tInfo.m_emRes);
	}
}

void CVmpServiceHandler::EventStartRes(CTpMsg* const pcMsg)
{
	TVmpStartResult tInfo;
	TP_SAFE_CAST(tInfo, pcMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::EventStartRes ServiceID:%d, Res:%d.\n", 
			tInfo.m_tBaseInfo.m_wServiceID, tInfo.m_emRes));

	if (em_mpu2tp_service != tInfo.m_tBaseInfo.m_emType)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::EventStartRes Invalid service.\n"));
		return ;
	}

	if (em_Res_Success != tInfo.m_emRes)
	{
		CEqpService::Instance().OperateRet(tInfo.m_tBaseInfo.m_emType, tInfo.m_tBaseInfo.m_wServiceID, em_Start_Service, tInfo.m_emRes);
	}
}

void CVmpServiceHandler::EventStopRes(CTpMsg* const pcMsg)
{
	TVmpStartResult tInfo;
	TP_SAFE_CAST(tInfo, pcMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::EventStopRes ServiceID:%d, Res:%d.\n", 
			tInfo.m_tBaseInfo.m_wServiceID, tInfo.m_emRes));

	if (em_mpu2tp_service != tInfo.m_tBaseInfo.m_emType)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::EventStopRes Invalid service.\n"));
		return ;
	}

	if (em_Res_Success != tInfo.m_emRes)
	{
//		CEqpService::Instance().SetError(em_mpu2tp_service, tInfo.m_tBaseInfo.m_wServiceID);
	}
}

void CVmpServiceHandler::EventMdyRes(CTpMsg* const pcMsg)
{
	TVmpMdyResult tInfo;
	TP_SAFE_CAST(tInfo, pcMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("CVmpServiceHandler::EventMdyRes ServiceID:%d, Res:%d.\n", 
			tInfo.m_tBaseInfo.m_wServiceID, tInfo.m_emRes));

	if (em_mpu2tp_service != tInfo.m_tBaseInfo.m_emType)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::EventMdyRes Invalid service.\n"));
		return ;
	}

	if (em_Res_Success != tInfo.m_emRes)
	{
		CEqpService::Instance().OperateRet(tInfo.m_tBaseInfo.m_emType, tInfo.m_tBaseInfo.m_wServiceID, em_Mdy_Service, tInfo.m_emRes);
	}
}

void CVmpServiceHandler::EventAskFrame( CTpMsg* const pcMsg )
{
	TVmpAskFrame tAsk;
	TP_SAFE_CAST(tAsk, pcMsg->GetBody());
	
	MdlLowDtl(Ums_Mdl_Call, ("CVmpServiceHandler::EventMdyRes ServiceID:%d, MemberIndx:%d.\n", tAsk.m_wChanID, tAsk.m_wMemberIndx));
	
	CEqpService::Instance().OperateRet(em_mpu2tp_service, tAsk.m_wChanID, em_Frame_Service, em_Res_Success, tAsk.m_wMemberIndx);	
}


const CBaseService* CVmpServiceHandler::AssignXmpuEqp( ServiceCB cbFun, CUmsConfInst* pcInst ) const
{
	if (NULL == cbFun || NULL == pcInst)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::AssignXmpuEqp Invalid call back function.\n"));
		return NULL;
	}

	const CBaseService* pcBaseService = CEqpService::Instance().AssignXmpuMpu2(em_mpu2tp_service, cbFun, pcInst);
	if (NULL == pcBaseService)
	{
		MdlError(Ums_Mdl_Call, ("CVmpServiceHandler::AssignXmpuEqp serivice failed.\n"));
		return NULL;
	}

	return pcBaseService;
}

void CVmpServiceHandler::ReleaseXmpuMpu2( const CBaseService* pcService )
{
	if (NULL != pcService)
	{
		CEqpService::Instance().ReleaseXmpuMpu2(pcService, em_mpu2tp_service);
	}
}

void CVmpServiceHandler::XmpuAskFrame( CTpMsg* const pcMsg )
{
	TTPVmpAskFrame tAsk;
	TP_SAFE_CAST(tAsk, pcMsg->GetBody());

	MdlLowDtl(Ums_Mdl_Call, ("CVmpServiceHandler::EventMdyRes ServiceID:%d, MemberIndx:%d.\n", tAsk.m_byEqpID, tAsk.m_byChanIndx));

	CEqpService::Instance().OperateRet(em_mpu2tp_service, tAsk.m_byEqpID, em_Frame_Service, em_Res_Success, tAsk.m_byChanIndx);	
}
