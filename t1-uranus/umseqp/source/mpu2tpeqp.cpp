#include "mpu2tpeqp.h"
#include "eqpmgr.h"
#include "eqpinst.h"
#include "mediatranseqp.h"
#include "eventoutmpu2tp.h"
#include "innereventumsboard.h"
#include "innereventumsvmp.h"
#include "umsinnerstruct.h"
#include "tpcommonstruct.h"
#include "umsinnertype.h"
#include "innereventumscall.h"
#include "umsconfigex.h"

#define TP_MPU2TP_PORT_SPAN	15


CMpu2TpEqp::CMpu2TpEqp( CUmsEqpInst* ptInst ):CEqpBase(ptInst)
{

}

CMpu2TpEqp::~CMpu2TpEqp()
{

}

void CMpu2TpEqp::Init()
{
	for (u16 wIndex = 0; wIndex < TP_MAX_MPU2TP_NUM; ++wIndex)
	{
		m_atModule[wIndex].Clear();
		m_atModule[wIndex].m_wServiceID = wIndex + 1;
	}
}

void CMpu2TpEqp::Handle(CTpMsg *const ptMsg)
{
	switch (ptMsg->GetEvent())
	{
	case ev_mpu2tp_regist:
		{
			EventRegist(ptMsg);
		}
		break;

	case ev_mpu2tp_start_res:
		{
			EventStartRes(ptMsg);
		}
		break;

	case ev_npu2tp_mdy_param_res:
		{
			EventMdyRes(ptMsg);
		}
		break;

	case ev_mpu2tp_stop_res:
		{
			EventStopRes(ptMsg);
		}	
		break;

	case ev_mpu2tp_addchan_res:
		{
			EventAddChanRes(ptMsg);
		}
		break;

	case ev_mpu2tp_delchan_res:
		{
			EventDelChanRes(ptMsg);
		}
		break;

	case ev_vmp_Assgin_Req:
		{
			EventAssginReq(ptMsg);
		}
		break;

	case ev_vmp_Start_Req:
		{
			EventStartReq(ptMsg);
		}
		break;

	case ev_vmp_Stop_Req:
		{
			EventStopReq(ptMsg);
		}
		break;

	case ev_vmp_Mdy_Style_Req:
		{
			EventMdyStyleReq(ptMsg);
		}
		break;

	case ev_mpu2tp_AskFrame_Req:
		{
			EventAskFrameReq(ptMsg);
		}
		break;

	case ev_vmp_UpdateSpeakerSide_Req:
		{
			EventUpdateSpeakerFlag(ptMsg);
		}
		break;

	case ev_vmp_SetMediaKey_Req:
		{
			EventSetMediaKey(ptMsg);
		}
		break;
	case ev_vmp_ChangeDsIP_Req:
		{
			EventChangeDsIP(ptMsg);
		}
		break;
	default:
		break;
	}
}

void CMpu2TpEqp::EventRegist(CTpMsg* const ptMsg)
{
	TVmpRegistInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	BOOL32 bRes = FALSE;
	u16 wIndex = TP_MAX_MPU2TP_NUM;
	do 
	{
		TBrdEntry* ptBrd = m_pcInst->GetEqpMgr()->GetBrdCfg(tInfo.m_byLayer, tInfo.m_bySlot, em_mpu2_tp_brd);
		if (NULL == ptBrd)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventRegist Brd can not be found.\n"));
			break;
		}

		if (!ptBrd->m_bBrdState)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventRegist Brd is not registed.\n"));
			break;
		}

		wIndex = FindEqp(tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_wChanID);
		if (TP_MAX_MPU2TP_NUM != wIndex)
		{
			MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventRegist Alreadty registed.\n"));
			break;
		}
		else
		{
			wIndex = FindIdleEqp();
			if (TP_MAX_MPU2TP_NUM == wIndex)
			{
				MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventRegist Eqp is full.\n"));
				break;
			}
		}

	/*	TEqpRes tMediaRes;
		if (!((CMediaTransEqp*)m_pcInst->GetEqp(CUmsEqpInst::_CMediaTransEqp))->AssignDsForBas(&tMediaRes, MPU2TP_USE_MEDIA))
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventRegist Assign medis resource failed.\n"));
			break;
		}
		else
		{
		//	m_atModule[wIndex].m_dwMediaIndex = tMediaRes.m_wEqpIndex;
		//	m_atModule[wIndex].m_dwMediaNode = tMediaRes.m_dwEqpNode;
		//	m_atModule[wIndex].m_dwMediaIP = tMediaRes.m_dwEqpIp;
			
		}
	*/
		bRes = TRUE;
		m_atModule[wIndex].m_wUmsStartPort = UMS_MPU2TP_BEGIN_PORT + wIndex * TP_MPU2TP_PORT_SPAN;
		m_atModule[wIndex].m_bReg = TRUE;
		m_atModule[wIndex].m_byLayer = tInfo.m_byLayer;
		m_atModule[wIndex].m_bySlot = tInfo.m_bySlot;
		m_atModule[wIndex].m_wChanID = tInfo.m_wChanID;
		m_atModule[wIndex].m_wEqpStartPort = tInfo.m_dwStartPort;
		m_atModule[wIndex].m_wRcvChanNum = tInfo.m_wRcvChanNum;
		m_atModule[wIndex].m_wSndChanNum = tInfo.m_wSendChanNum;
		m_atModule[wIndex].m_dwSrcIID = ptMsg->GetSrcIId();
		m_atModule[wIndex].m_dwSrcNode = ptMsg->GetSrcNode();

	} while (FALSE);

	CTpMsg cMsg;
	if (bRes)
	{
		TVmpRegAck tAck;
	//	tAck.m_dwRcvIP = m_atModule[wIndex].m_dwMediaIP;
		tAck.m_wRcvPort = m_atModule[wIndex].m_wUmsStartPort;
		TVmpTimeSpan tSpan;
		if (CUmsConfigEx::GetInstance()->GetRsFirstTime() != 0 && CUmsConfigEx::GetInstance()->GetRsRejectTime() != 0)
		{
			tSpan.m_wFirstTimeSpan	= CUmsConfigEx::GetInstance()->GetRsFirstTime();
			tSpan.m_wSecondTimeSpan	= CUmsConfigEx::GetInstance()->GetRsSecondTime();
			tSpan.m_wThirdTimeSpan	= CUmsConfigEx::GetInstance()->GetRsThirdTime();
			tSpan.m_wRejectTimeSpan	= CUmsConfigEx::GetInstance()->GetRsRejectTime();
		}

		u32 dwMpu2NetBandMul = CUmsConfigEx::GetInstance()->GetMpu2tpNetBandMul();

		cMsg.SetEvent(ev_mpu2tp_regist_ack);
		cMsg.SetBody(&tAck, sizeof(tAck));
		cMsg.CatBody(&tSpan, sizeof(tSpan));
		cMsg.CatBody(&dwMpu2NetBandMul, sizeof(dwMpu2NetBandMul));

		//更新外设注册状态到eqpmgr
		m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptMsg->GetSrcNode(), 0, TRUE);

		TServiceReg tReg;
	//	tReg.m_dwLocalIP = m_atModule[wIndex].m_dwMediaIP;
		tReg.m_wUmsStartPort = m_atModule[wIndex].m_wUmsStartPort;
		tReg.m_dwEqpIP = OspNodeIpGet(m_atModule[wIndex].m_dwSrcNode);
		tReg.m_wEqpStartPort = m_atModule[wIndex].m_wEqpStartPort;
	//	tReg.m_dwMediaNode = m_atModule[wIndex].m_dwMediaNode;
		tReg.m_tBaseInfo.m_emType = em_mpu2tp_service;
		tReg.m_tBaseInfo.m_wServiceID = m_atModule[wIndex].m_wServiceID;

		SendMsgToCall(evtp_EqpService_Reg, &tReg, sizeof(tReg));
	}
	else
	{
		cMsg.SetEvent(ev_mpu2tp_regist_nack);
	}

	cMsg.Post(ptMsg->GetSrcIId(), ptMsg->GetSrcNode());

	MdlHint(Ums_Mdl_Eqp, ("EventRegist Layer:%d, Slot:%d, ChanID:%d, StartPort:%d, RcvNum:%d, SndNum:%d, bRet:%d\n",
		tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_wChanID, tInfo.m_dwStartPort, tInfo.m_wRcvChanNum, tInfo.m_wSendChanNum, bRes));

	return ;
}

void CMpu2TpEqp::EventStartRes(CTpMsg* const ptMsg)
{
	TVmpStartRes tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartRes ChanID:%d, EmRes:%d.\n", tRes.m_wChanID, tRes.m_emRes));

	u16 wIndex = FindEqpByChanID(tRes.m_wChanID, ptMsg->GetSrcNode());
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartRes Not find the channel.\n"));
		return ;
	}

	if (em_mpu2tp_working != m_atModule[wIndex].m_emState)
	{
		MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartRes No in working.\n"));
		return ;
	}

	TVmpStartResult tStartRes;
	tStartRes.m_tBaseInfo.m_emType = em_mpu2tp_service;
	tStartRes.m_tBaseInfo.m_wServiceID = wIndex;
	ConvertRes(tRes.m_emRes, tStartRes.m_emRes);
	SendMsgToCall(ev_vmp_Start_Res, &tStartRes, sizeof(tStartRes));
}

void CMpu2TpEqp::EventMdyRes(CTpMsg* const ptMsg)
{
	TVmpMdyRes tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventMdyRes ChanID:%d. Res:%d.\n", tRes.m_wChanID, tRes.m_emRes));

	u16 wIndex = FindEqpByChanID(tRes.m_wChanID, ptMsg->GetSrcNode());
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventMdyRes Not find the channel.\n"));
		return ;
	}

	if (em_mpu2tp_working != m_atModule[wIndex].m_emState)
	{
		MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartRes No in working.\n"));
		return ;
	}

	TVmpMdyResult tInfo;
	tInfo.m_tBaseInfo.m_emType = em_mpu2tp_service;
	tInfo.m_tBaseInfo.m_wServiceID = m_atModule[wIndex].m_wServiceID;
	ConvertRes(tRes.m_emRes, tInfo.m_emRes);

	SendMsgToCall(ev_vmp_Mdy_Style_Res, &tInfo, sizeof(tInfo));
}

void CMpu2TpEqp::EventStopRes(CTpMsg* const ptMsg)
{
	TVmpStopRes tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStopRes ChanID:%d, Res:%d.\n", tRes.m_wChanID, tRes.m_emRes));

	u16 wIndex = FindEqpByChanID(tRes.m_wChanID, ptMsg->GetSrcNode());
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStopRes Not find the channel.\n"));
		return ;
	}

	if (em_ums_vmp_success != tRes.m_emRes)
	{
// 		m_atModule[wIndex].m_emState = em_mpu2tp_error;
// 
// 		TVmpStartResult tInfo;
// 		tInfo.m_tBaseInfo.m_wServiceID = m_atModule[wIndex].m_wServiceID;
// 		tInfo.m_tBaseInfo.m_emType = em_mpu2tp_service;
// 		ConvertRes(tRes.m_emRes, tInfo.m_emRes);
// 		SendMsgToCall(ev_vmp_Stop_Res, &tInfo, sizeof(tInfo));
	}
}

void CMpu2TpEqp::EventAddChanRes(CTpMsg* const ptMsg)
{
	TVmpChanRes tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAddChanRes ChanID:%d, Res:%d.\n", tRes.m_wChanID, tRes.m_emRes));

	u16 wIndex = FindEqpByChanID(tRes.m_wChanID, ptMsg->GetSrcNode());
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAddChanRes Not find the channel.\n"));
		return ;
	}
	
	//TODO
}

void CMpu2TpEqp::EventDelChanRes(CTpMsg* const ptMsg)
{
	TVmpChanRes tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventDelChanRes ChanID:%d, Res:%d.\n", tRes.m_wChanID, tRes.m_emRes));
	
	u16 wIndex = FindEqpByChanID(tRes.m_wChanID, ptMsg->GetSrcNode());
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventDelChanRes Not find the channel.\n"));
		return ;
	}
	
	//TODO
}

void CMpu2TpEqp::EventStartReq(CTpMsg* const ptMsg)
{
	TVmpStartInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartReq ServiceID:%d, Style:%d.\n", 
							tInfo.m_wServiceID, tInfo.m_tVmpParam.m_tStyleInfo.m_emVmpStyle));

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartReq EncryptInfo(%d,%s,%d)\n", 
		tInfo.m_tVmpParam.m_tEncrypt.m_emEncryptModel,
		tInfo.m_tVmpParam.m_tEncrypt.m_achEncKey,
		tInfo.m_tVmpParam.m_tEncrypt.m_byKeyLen));

	EmServiceRes emRes = em_Res_Success;
	TMpu2TpModule* pcModule = NULL;
	do 
	{
		u16 wIndex = FindEqpByServiceID(tInfo.m_wServiceID);
		if (TP_MAX_MPU2TP_NUM == wIndex)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartReq Not find the channel.\n"));
			return ;
		}
		pcModule = &(m_atModule[wIndex]);

		if (!pcModule->m_bReg)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartReq Service is not registed.\n"));
			emRes = em_Service_No_Reg;
			break;
		}

		if (em_mpu2tp_Assgin != pcModule->m_emState)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStartReq Service is not assgin.\n"));
			emRes = em_Service_Working;
			break;
		}

	} while (FALSE);

	if (em_Res_Success == emRes)
	{
		TVmpStartParam tParam;
		tParam.m_tEncParam = tInfo.m_tVmpParam.m_tEncParam;
		tParam.m_tEncrypt = tInfo.m_tVmpParam.m_tEncrypt;
		tParam.m_tStyleInfo = tInfo.m_tVmpParam.m_tStyleInfo;
		tParam.m_wChanID = m_atModule[tInfo.m_wServiceID].m_wChanID;
		SendMsgToEqp(ev_mpu2tp_start_req, pcModule->m_dwSrcIID, pcModule->m_dwSrcNode, &tParam, sizeof(tParam));

		pcModule->m_emState = em_mpu2tp_working;
	}
	else
	{
		TVmpStartResult tRes;
		tRes.m_tBaseInfo.m_emType = em_mpu2tp_service;
		tRes.m_tBaseInfo.m_wServiceID = tInfo.m_wServiceID;
		tRes.m_emRes = emRes;
		SendMsgToCall(ev_vmp_Start_Res, &tRes, sizeof(tRes));
	}
}

void CMpu2TpEqp::EventStopReq(CTpMsg* const ptMsg)
{
	TServiceBaseInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStopReq SergviceID:%d, Type:%d.\n", tInfo.m_wServiceID, tInfo.m_emType));

	EmServiceRes emRes = em_Res_Success;
	TMpu2TpModule* pcModule = NULL;
	do 
	{	
		u16 wIndex = FindEqpByServiceID(tInfo.m_wServiceID);
		if (TP_MAX_MPU2TP_NUM == wIndex)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStopReq Not find the channel.\n"));
			return ;
		}
		pcModule = &(m_atModule[wIndex]);
		
		if (!pcModule->m_bReg)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStopReq Service is not registed.\n"));
			emRes = em_Service_No_Reg;
			break;
		}
		
		if (em_mpu2tp_working != pcModule->m_emState && em_mpu2tp_Assgin != pcModule->m_emState)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventStopReq Service is not in working.\n"));
			emRes = em_Service_No_Working;
			break;
		}

		if ( em_mpu2tp_Assgin == pcModule->m_emState )
		{//只置状态即可
			break;
		}

		SendMsgToEqp(ev_mpu2tp_stop_req, pcModule->m_dwSrcIID, pcModule->m_dwSrcNode, NULL, 0);
		
	} while (FALSE);

//	if (em_Res_Success == emRes)
	{
		pcModule->m_emState = em_mpu2tp_idle;
	}
//	else
	{
// 		pcModule->m_emState = em_mpu2tp_error;
// 
// 		TVmpStartResult tRes;
// 		tRes.m_tBaseInfo = tInfo;
// 		tRes.m_emRes = emRes;
// 		SendMsgToCall(ev_vmp_Stop_Res, &tRes, sizeof(tRes));
	}
}

void CMpu2TpEqp::EventMdyStyleReq(CTpMsg* const ptMsg)
{
	TVmpMdyInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventMdyStyleReq ServiceID:%d, NetStyle:%d.\n", tInfo.m_wServiceID, tInfo.m_tStyleInfo.m_emVmpStyle));

	TVmpMdyResult tRes;
	tRes.m_tBaseInfo.m_emType = em_mpu2tp_service;
	tRes.m_tBaseInfo.m_wServiceID = tInfo.m_wServiceID;
	tRes.m_emRes = em_Res_Success;
	TMpu2TpModule* pcModule = NULL;
	do 
	{
		u16 wIndex = FindEqpByServiceID(tInfo.m_wServiceID);
		if (TP_MAX_MPU2TP_NUM == wIndex)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventMdyStyleReq Not find the channel.\n"));
			return ;
		}
		pcModule = &(m_atModule[wIndex]);

		if (!pcModule->m_bReg)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventMdyStyleReq Service is not registed.\n"));
			tRes.m_emRes = em_Service_No_Reg;
			break;
		}
		
		if (em_mpu2tp_working != pcModule->m_emState)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventMdyStyleReq Service is not in working.\n"));
			tRes.m_emRes = em_Service_No_Working;
			break;
		}

	} while (FALSE);

	if (em_Res_Success == tRes.m_emRes)
	{
		SendMsgToEqp(ev_mpu2tp_mdy_param, pcModule->m_dwSrcIID, pcModule->m_dwSrcNode, &(tInfo), sizeof(TVmpMdyInfo));
	}
	else
	{
		SendMsgToCall(ev_vmp_Mdy_Style_Res, &tRes, sizeof(tRes));
	}
}

void CMpu2TpEqp::EventUpdateSpeakerFlag(  CTpMsg* const ptMsg )
{
	TVmpSpeakerFlag tFlag;
	TP_SAFE_CAST(tFlag, ptMsg->GetBody());
	
	u16 wIndex = FindEqpByServiceID(tFlag.m_wChanID);
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventUpdateSpeakerFlag Not find the channel.\n"));
		return ;
	}
	TMpu2TpModule* pcModule = &(m_atModule[wIndex]);
	if (!pcModule->m_bReg)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventUpdateSpeakerFlag Service is not registed.\n"));
		return ;
	}
	
	if (em_mpu2tp_working != pcModule->m_emState)
	{
		MdlLowDtl(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventUpdateSpeakerFlag Service is not in working.\n"));
		return ;
	}

	SendMsgToEqp(ev_mpu2tp_SpeakerFlag_Ntfy, pcModule->m_dwSrcIID, pcModule->m_dwSrcNode, &(tFlag), sizeof(TVmpSpeakerFlag));
	
	return ;
}


BOOL32 CMpu2TpEqp::OnDisConnect(u32 dwNode)
{
	MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::OnDisConnect dwNode:%d.\n", dwNode));

	TServiceBaseInfo tInfo;
	for (u16 wIndex = 0; wIndex < TP_MAX_MPU2TP_NUM; ++wIndex)
	{
		if ( !m_atModule[wIndex].m_bReg )
		{
			continue;
		}

		if ( m_atModule[wIndex].m_dwSrcNode != dwNode )
		{
			continue;
		}
		
		tInfo.m_emType = em_mpu2tp_service;
		tInfo.m_wServiceID = m_atModule[wIndex].m_wServiceID;
		SendMsgToCall(evtp_EqpService_UnReg, &tInfo, sizeof(tInfo));

		m_atModule[wIndex].Clear();
	}

	return TRUE;
}

u16 CMpu2TpEqp::FindEqp(const u8 byLayer, const u8 bySlot, const u16 wChanID) const
{
	for (u16 wIndex = 0; wIndex < TP_MAX_MPU2TP_NUM; ++wIndex)
	{
		if (m_atModule[wIndex].m_byLayer == byLayer &&
			m_atModule[wIndex].m_bySlot == bySlot &&
			m_atModule[wIndex].m_wChanID == wChanID)
		{
			return wIndex;
		}
	}

	return TP_MAX_MPU2TP_NUM;
}

u16 CMpu2TpEqp::FindEqpByServiceID(const u16 wServiceID) const
{
	for (u16 wIndex = 0; wIndex < TP_MAX_MPU2TP_NUM; ++wIndex)
	{
		if (m_atModule[wIndex].m_bReg && wServiceID == m_atModule[wIndex].m_wServiceID)
		{
			return wIndex;
		}
	}

	return TP_MAX_MPU2TP_NUM;
}

u16 CMpu2TpEqp::FindEqpByChanID(const u16 wChanID, const u32 dwNode) const
{
	for (u16 wIndex = 0; wIndex < TP_MAX_MPU2TP_NUM; ++wIndex)
	{
		if (m_atModule[wIndex].m_bReg 
			&& wChanID == m_atModule[wIndex].m_wChanID
			&& dwNode == m_atModule[wIndex].m_dwSrcNode )
		{
			return wIndex;
		}
	}
	
	return TP_MAX_MPU2TP_NUM;
}

u16 CMpu2TpEqp::FindIdleEqp() const
{
	for (u16 wIndex = 0; wIndex < TP_MAX_MPU2TP_NUM; ++wIndex)
	{
		if (!m_atModule[wIndex].m_bReg)
		{
			return wIndex;
		}
	}

	return TP_MAX_MPU2TP_NUM;
}

void CMpu2TpEqp::SendMsgToCall(u16 wEvent, void* const pbyMsg, u16 wLen)
{	
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post(MAKEIID( AID_UMSCONFMGR, CInstance::DAEMON));
	return ;
}

void CMpu2TpEqp::SendMsgToEqp(u16 wEvent, u32 dwDstIID, u32 dwNode, void* const pbyMsg /* = NULL */, u16 wLen /* = 0 */)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post(dwDstIID, dwNode);
	return ;
}

void CMpu2TpEqp::ConvertRes(EmVmpRes emVmpRes, EmServiceRes& emServiceRes)
{
	switch (emVmpRes)
	{
	case em_ums_vmp_success:
		{
			emServiceRes = em_Res_Success;
		}
		break;

	case em_ums_vmp_failed:
		{
			emServiceRes = em_Start_Failed;
		}
		break;

	case em_ums_vmp_invalid_chan:
		{
			emServiceRes = em_Invalid_ServiceID;
		}
		break;

	case em_ums_vmp_chan_working:
		{
			emServiceRes = em_Service_Working;
		}
		break;

	case em_ums_vmp_invalid_param:
		{
			emServiceRes = em_Invalid_Param;
		}
		break;

	case em_ums_vmp_set_param_failed:
		{
			emServiceRes = em_Set_Param_Failed;
		}
		break;

	default:
		{
			emServiceRes = em_Start_Failed;
		}
		break;
	}
}

void CMpu2TpEqp::Show()
{
	msgprintnotime("Mpu2Tp Info:\n");
	for (u16 wIndex = 0; wIndex < TP_MAX_MPU2TP_NUM; ++wIndex)
	{
		if ( !m_atModule[wIndex].m_bReg )
		{
			continue;
		}

		msgprintnotime("Index:%d, SerID:%d, EqpIP:"IPFORMAT", Stat:%d ( 0-idle, 1-Assgin, 2-work, 3-error )\n", 
			wIndex, m_atModule[wIndex].m_wServiceID, 
			u32ToIP(OspNodeIpGet(m_atModule[wIndex].m_dwSrcNode)),
			m_atModule[wIndex].m_emState
			);

		msgprintnotime("	ChnlNum(Rcv:%d, Snd:%d), UmsStartPort:%d, EqpStartPort:%d\n",  
			m_atModule[wIndex].m_wRcvChanNum, m_atModule[wIndex].m_wSndChanNum,
			m_atModule[wIndex].m_wUmsStartPort, m_atModule[wIndex].m_wEqpStartPort
			);

		msgprintnotime("\n");
	}

	return ;
}

void CMpu2TpEqp::EventAskFrameReq( CTpMsg* const ptMsg )
{
	TVmpAskFrame tFrame;
	TP_SAFE_CAST(tFrame, ptMsg->GetBody());

	MdlLowDtl(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAskFrameReq ServiceID:%d, MemberIndx:%d srcnode:%d.\n", 
		tFrame.m_wChanID, tFrame.m_wMemberIndx, ptMsg->GetSrcNode()));
	
	u16 wIndex = TP_MAX_MPU2TP_NUM;

	if( GETAPP(ptMsg->GetSrcIId()) == AID_MPU2TP_APP )
	{
		wIndex = FindEqpByChanID(tFrame.m_wChanID, ptMsg->GetSrcNode());
	}
	else
	{
		wIndex = FindEqpByServiceID(tFrame.m_wChanID);
	}
	
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAskFrameReq Not find the channel.\n"));
		return ;
	}

	TMpu2TpModule* pcModule = &(m_atModule[wIndex]);

	if( GETAPP(ptMsg->GetSrcIId()) != AID_MPU2TP_APP )
	{
		if(!pcModule->m_tKeyFrameStatisToEqp.CheckFrameStatis())
		{//2s内可以请求2次
			if ( pcModule->m_wFrameTimesToEqp >= 2 )
			{
				MdlLowDtl(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAskFrameReq. Src req frequent(to eqp)! ServiceID:%d, MemberIndx:%d srcnode:%d.\n", 
					tFrame.m_wChanID, tFrame.m_wMemberIndx, ptMsg->GetSrcNode()));
				return ;
			}
			pcModule->m_wFrameTimesToEqp++;
		}
		else
		{
			pcModule->m_wFrameTimesToEqp = 1;
		}
	} 
	else 
	{
         if (!pcModule->m_tKeyFrameStatis.CheckFrameStatis())
		 {
			 if ( pcModule->m_wFrameTimes >= 2 )
			 {
				 MdlLowDtl(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAskFrameReq. vmptp Src req frequent! ServiceID:%d, MemberIndx:%d srcnode:%d.\n", 
					 tFrame.m_wChanID, tFrame.m_wMemberIndx, ptMsg->GetSrcNode()));
				 return ;
			 }
			 pcModule->m_wFrameTimes++;
		 }
		 else 
		 {
             pcModule->m_wFrameTimes = 1;
		 }

	}
	
	if (!pcModule->m_bReg)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAskFrameReq Eqp is not registed.\n"));
		return ;
	}
	
	if (em_mpu2tp_working != pcModule->m_emState)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAskFrameReq Eqp is not working.\n"));
		return ;
	}
	
	TVmpAskFrame tAsk;
	tAsk.m_wChanID = pcModule->m_wServiceID;
	tAsk.m_wMemberIndx = tFrame.m_wMemberIndx;

	if( GETAPP(ptMsg->GetSrcIId()) == AID_MPU2TP_APP )
	{
		SendMsgToCall(ev_mpu2tp_AskFrame_Req, &tAsk, sizeof(tAsk));
	}
	else
	{
		SendMsgToEqp(ev_mpu2tp_AskFrame_Req, pcModule->m_dwSrcIID, pcModule->m_dwSrcNode, NULL, 0);
	}

	return ;
}

void CMpu2TpEqp::CalcEqpUsedStat( TTPBrdUsedInfo& tUsed )
{
	tUsed.Clear();
	tUsed.m_emType = em_vmp_tp_mdl;

	u16 wMdlIndex;
	for (wMdlIndex = 0; wMdlIndex < TP_MAX_MPU2TP_NUM; wMdlIndex++)
	{
		if (m_atModule[wMdlIndex].m_bReg)
		{
			tUsed.m_wRegNum++;
			if (em_mpu2tp_idle != m_atModule[wMdlIndex].m_emState)
			{
				tUsed.m_wUsedNum++;
			}
		}
	}
		
	return ;
}

/*void CMpu2TpEqp::MediaEqpDisConnect( u32 dwMediaIP )
{
	u16 wMdlIndex;
	for (wMdlIndex = 0; wMdlIndex < TP_MAX_MPU2TP_NUM; wMdlIndex++)
	{
		if (!m_atModule[wMdlIndex].m_bReg)
		{
			continue;
		}

		if( dwMediaIP == m_atModule[wMdlIndex].m_dwMediaIP )
		{
			TServiceBaseInfo tInfo;
			tInfo.m_emType = em_mpu2tp_service;
			tInfo.m_wServiceID = m_atModule[wMdlIndex].m_wServiceID;
			SendMsgToCall(evtp_EqpService_UnReg, &tInfo, sizeof(tInfo));

			m_atModule[wMdlIndex].m_dwMediaIndex = 0;
			m_atModule[wMdlIndex].m_dwMediaNode = 0;
			m_atModule[wMdlIndex].m_dwMediaIP = 0;

			TEqpRes tMediaRes;
			if (((CMediaTransEqp*)m_pcInst->GetEqp(CUmsEqpInst::_CMediaTransEqp))->AssignDsForBas(&tMediaRes, MPU2TP_USE_MEDIA))
			{
				m_atModule[wMdlIndex].m_dwMediaIndex = tMediaRes.m_wEqpIndex;
				m_atModule[wMdlIndex].m_dwMediaNode = tMediaRes.m_dwEqpNode;
				m_atModule[wMdlIndex].m_dwMediaIP = tMediaRes.m_dwEqpIp;

				TServiceReg tReg;
				tReg.m_dwLocalIP = m_atModule[wMdlIndex].m_dwMediaIP;
				tReg.m_wLocalPort = m_atModule[wMdlIndex].m_wStartPort;
				tReg.m_dwRcvIP = OspNodeIpGet(m_atModule[wMdlIndex].m_dwSrcNode);
				tReg.m_wRcvPort = m_atModule[wMdlIndex].m_wEqpStartPort;
				tReg.m_dwMediaNode = m_atModule[wMdlIndex].m_dwMediaNode;
				tReg.m_tBaseInfo.m_emType = em_mpu2tp_service;
				tReg.m_tBaseInfo.m_wServiceID = m_atModule[wMdlIndex].m_wServiceID;
				
				SendMsgToCall(evtp_EqpService_Reg, &tReg, sizeof(tReg));

				TVmpRegAck tAck;
				tAck.m_dwRcvIP = m_atModule[wMdlIndex].m_dwMediaIP;
				tAck.m_wRcvPort = m_atModule[wMdlIndex].m_wStartPort;
				
				CTpMsg cMsg;
				cMsg.SetEvent(ev_mpu2tp_ChangeUmsIP_Req);
				cMsg.SetBody(&tAck, sizeof(tAck));
				cMsg.Post(m_atModule[wMdlIndex].m_dwSrcIID, m_atModule[wMdlIndex].m_dwSrcNode);
			}
		}
	}
}

void CMpu2TpEqp::MediaEqpConnect()
{
	u16 wMdlIndex;
	for (wMdlIndex = 0; wMdlIndex < TP_MAX_MPU2TP_NUM; wMdlIndex++)
	{
		if (!m_atModule[wMdlIndex].m_bReg)
		{
			continue;
		}

		if( 0 != m_atModule[wMdlIndex].m_dwMediaNode )
		{
			continue;
		}

		TEqpRes tMediaRes;
		if (((CMediaTransEqp*)m_pcInst->GetEqp(CUmsEqpInst::_CMediaTransEqp))->AssignDsForBas(&tMediaRes, MPU2TP_USE_MEDIA))
		{
			m_atModule[wMdlIndex].m_dwMediaIndex = tMediaRes.m_wEqpIndex;
			m_atModule[wMdlIndex].m_dwMediaNode = tMediaRes.m_dwEqpNode;
			m_atModule[wMdlIndex].m_dwMediaIP = tMediaRes.m_dwEqpIp;
			
			TServiceReg tReg;
			tReg.m_dwLocalIP = m_atModule[wMdlIndex].m_dwMediaIP;
			tReg.m_wLocalPort = m_atModule[wMdlIndex].m_wStartPort;
			tReg.m_dwRcvIP = OspNodeIpGet(m_atModule[wMdlIndex].m_dwSrcNode);
			tReg.m_wRcvPort = m_atModule[wMdlIndex].m_wEqpStartPort;
			tReg.m_dwMediaNode = m_atModule[wMdlIndex].m_dwMediaNode;
			tReg.m_tBaseInfo.m_emType = em_mpu2tp_service;
			tReg.m_tBaseInfo.m_wServiceID = m_atModule[wMdlIndex].m_wServiceID;
			
			SendMsgToCall(evtp_EqpService_Reg, &tReg, sizeof(tReg));

			TVmpRegAck tAck;
			tAck.m_dwRcvIP = m_atModule[wMdlIndex].m_dwMediaIP;
			tAck.m_wRcvPort = m_atModule[wMdlIndex].m_wStartPort;

			CTpMsg cMsg;
			cMsg.SetEvent(ev_mpu2tp_ChangeUmsIP_Req);
			cMsg.SetBody(&tAck, sizeof(tAck));
			cMsg.Post(m_atModule[wMdlIndex].m_dwSrcIID, m_atModule[wMdlIndex].m_dwSrcNode);
		}
	}
}
*/
void CMpu2TpEqp::EventAssginReq( CTpMsg* const ptMsg )
{
	TServiceBaseInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAssginReq SergviceID:%d, Type:%d.\n", tInfo.m_wServiceID, tInfo.m_emType));
	
	EmServiceRes emRes = em_Res_Success;
	TMpu2TpModule* pcModule = NULL;
	do 
	{	
		u16 wIndex = FindEqpByServiceID(tInfo.m_wServiceID);
		if (TP_MAX_MPU2TP_NUM == wIndex)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAssginReq Not find the channel.\n"));
			return ;
		}
		pcModule = &(m_atModule[wIndex]);
		
		if (!pcModule->m_bReg)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAssginReq Service is not registed.\n"));
			emRes = em_Service_No_Reg;
			break;
		}
		
		if (em_mpu2tp_idle != pcModule->m_emState)
		{
			MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventAssginReq Service is not idle.\n"));
			emRes = em_Service_Working;
			break;
		}
		
	} while (FALSE);
	
	if (em_Res_Success != emRes)
	{
		TVmpStartResult tRes;
		tRes.m_tBaseInfo = tInfo;
		tRes.m_emRes = emRes;
		SendMsgToCall(ev_vmp_Assgin_Res, &tRes, sizeof(tRes));
	}
	else
	{
		pcModule->m_emState = em_mpu2tp_Assgin;
	}
	return;
}


void CMpu2TpEqp::EventSetMediaKey( CTpMsg* const ptMsg )
{
	u16 wServerID;
	TP_SAFE_CAST(wServerID, ptMsg->GetBody());
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(u16));
	
	u16 wIndex = FindEqpByServiceID(wServerID);
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventSetMediaKey Not find the channel.\n"));
		return ;
	}
	TMpu2TpModule* pcModule = &(m_atModule[wIndex]);
	if (!pcModule->m_bReg)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventSetMediaKey Service is not registed.\n"));
		return ;
	}
	
	if (em_mpu2tp_working != pcModule->m_emState)
	{
		MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventSetMediaKey Service is not in working.\n"));
		//return ;
	}

	TTPMediaKeyInfo tSndQ;
	tSndQ.m_dwHandle = pcModule->m_wChanID;//用来传递VmpchanID
	tSndQ.m_wIndex = tInfo.m_wIndex;
	tSndQ.m_dwKeyLen = tInfo.m_dwKeyLen;
	tSndQ.m_emKeyFrequency = tInfo.m_emKeyFrequency;
	tSndQ.m_dwQtFlag = tInfo.m_dwQtFlag;
	memcpy(tSndQ.m_szAlias, tInfo.m_szAlias, TP_MAX_ALIAS_LEN);
	tSndQ.m_szAlias[TP_MAX_ALIAS_LEN] = '\0';
	
	memcpy(tSndQ.m_szMediaKey1, tInfo.m_szMediaKey, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tSndQ.m_szMediaKey2, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tSndQ.m_szMediaKey3, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tSndQ.m_szMediaKey4, tInfo.m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	
	SendMsgToEqp(ev_mpu2tp_SetMediaKey_Req, pcModule->m_dwSrcIID, pcModule->m_dwSrcNode, &tSndQ, sizeof(tSndQ));
	
	return ;
}

void CMpu2TpEqp::EventChangeDsIP( CTpMsg* const ptMsg )
{
	TSndDsAddr tSndAddr;
	TP_SAFE_CAST(tSndAddr, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventChangeDsIP SergviceID:%d, DSIP:"IPFORMAT", StartPort:%d.\n", 
				tSndAddr.m_wServiceID, Tpu32ToIP(tSndAddr.m_dwMediaIP), tSndAddr.m_wStartPort));

	u16 wIndex = FindEqpByServiceID(tSndAddr.m_wServiceID);
	if (TP_MAX_MPU2TP_NUM == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventChangeDsIP Not find the channel.\n"));
		return ;
	}
	TMpu2TpModule* pcModule = &(m_atModule[wIndex]);
	if (!pcModule->m_bReg)
	{
		MdlError(Ums_Mdl_Eqp, ("CMpu2TpEqp::EventChangeDsIP Service is not registed.\n"));
		return ;
	}
		
	TVmpRegAck tAck;
	tAck.m_dwRcvIP = tSndAddr.m_dwMediaIP;
	tAck.m_wRcvPort = tSndAddr.m_wStartPort;
				
	CTpMsg cMsg;
	cMsg.SetEvent(ev_mpu2tp_ChangeUmsIP_Req);
	cMsg.SetBody(&tAck, sizeof(tAck));
	cMsg.Post(pcModule->m_dwSrcIID, pcModule->m_dwSrcNode);

	return ;
}

