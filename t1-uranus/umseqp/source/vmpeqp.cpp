#include "vmpeqp.h"
#include "innereventumscall.h"
#include "eqpinterface.h"
#include "eqpinst.h"
#include "umsconfigex.h"
#include "innereventumsmpu2.h"

s8* GetVmpStatBuf( CVmpModle::EmEqpStat emStat )
{
	switch(emStat)
	{
	case CVmpModle::EqpStat_OffLine:
		return "OffLine";
		break;
	case CVmpModle::EqpStat_Idle:
		return "Idle";
		break;
	case CVmpModle::EqpStat_Normal:
		return "Normal";
		break;
	case CVmpModle::EqpStat_Assign:
		return "Assign";
		break;
	case CVmpModle::EqpStat_Starting:
		return "Starting";
		break;
	case CVmpModle::EqpStat_Running:
		return "Running";
		break;
	case CVmpModle::EqpStat_Stoping:
		return "Stoping";
		break;
	case CVmpModle::EqpStat_Error:
		return "Error";
		break;
	default:
		return "InvalidStat";
		break;
	}
	
	return NULL;
}

CVmpEqp::CVmpEqp( CUmsEqpInst* pInst )
: CEqpBase(pInst)
{

}

CVmpEqp::~CVmpEqp()
{

}

void CVmpEqp::Init()
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{
		m_atVmpMdl[wMdlIndex].Clear();
	}
	
	return ;
}

CVmpModle* CVmpEqp::FindVmpMdl( u8	byEqpID)
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{
		if ( m_atVmpMdl[wMdlIndex].m_byEqpID == byEqpID )
		{
			return &m_atVmpMdl[wMdlIndex];
		}
	}
	
	return NULL;	
}

CVmpModle* CVmpEqp::FindVmpMdl( u32 dwNode )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{
		if ( m_atVmpMdl[wMdlIndex].m_dwUserNode == dwNode )
		{
			return &m_atVmpMdl[wMdlIndex];
		}
	}
	
	return NULL;	
}

CVmpModle* CVmpEqp::AssignVmpMdl( u8 byMemberNum, u8 byOutMemberNum )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{		
		if ( m_atVmpMdl[wMdlIndex].m_emStat == CVmpModle::EqpStat_Normal
			&& m_atVmpMdl[wMdlIndex].m_wConfID == TP_INVALID_INDEX )
		{
			//判断该合成器的能力
			if ( m_atVmpMdl[wMdlIndex].m_tTpVmpParam.m_byDecodeNum >= byMemberNum 
				|| m_atVmpMdl[wMdlIndex].m_tTpVmpParam.m_byEncodeNum >= byOutMemberNum )
			{
				return &m_atVmpMdl[wMdlIndex];
			}
		}
	}
	
	return NULL;
}

void CVmpEqp::SendMsgToEqpSsn( u32 dwSrcIID, u16 wEvent, u8 * const pbyMsg, u16 wLen )
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post( dwSrcIID, 0, UMS_EQP_APP_INST );
	return ;
}

void CVmpEqp::SendMsgToCall( u16 wConfID, u16 wEvent, u8 * const pbyMsg, u16 wLen )
{
	if ( wConfID == TP_INVALID_INDEX )
	{
		return ;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post( MAKEIID( AID_UMSCONFMGR, wConfID) );
	return ;
}

void CVmpEqp::Handle( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	switch(wEvent)
	{
	case ev_TPVmp_Reg_Req:
		OnVmpReg(ptMsg);
		break;
	case ev_TPVmp_State_Nty:
		OnVmpStatNtfy(ptMsg);
		break;
	case ev_TPVmp_StartMix_NAck:
		OnStartVmpNAck(ptMsg);
		break;
	case ev_TPVmp_StartMix_Ack:
		OnStartVmpAck(ptMsg);
		break;
	case ev_TPVmp_StartMix_Ntfy:
		OnStartVmpNtfy(ptMsg);
		break;
	case ev_TPVmp_StopMix_NAck:
		OnStopVmpNAck(ptMsg);
		break;
	case ev_TPVmp_StopMix_Ack:
		OnStopVmpAck(ptMsg);
		break;
	case ev_TPVmp_StopMix_Ntfy:
		OnStopVmpNtfy(ptMsg);
		break;
	case ev_TPVmp_ChangeMixParam_NAck:
		OnChangeVmpNAck(ptMsg);
		break;
	case ev_TPVmp_ChangeMixParam_Ack:
		OnChangeVmpAck(ptMsg);
		break;
	case ev_TPVmp_ChangeMixParam_Ntfy:
		OnChangeVmpNtfy(ptMsg);
		break;
	case ev_TPVmp_StartStopChn_Req:
		OnStartStopChnReq(ptMsg);
		break;
	case evtp_StartVmp_Req:
		OnStartVmp(ptMsg);
		break;
	case evtp_AdjustVmp_Req:
		OnAdjustVmp(ptMsg);
		break;
	case ev_TPVmp_FastUpdate_Req:
		{//收到请求关键帧
			TTPVmpAskFrame tAskFrame;
			TP_SAFE_CAST(tAskFrame, ptMsg->GetBody());
			if( GETAPP(ptMsg->GetSrcIId()) == AID_UMSCONFMGR )
			{
				AskFrameReq(TRUE, tAskFrame);
			}
			else
			{
				AskFrameReq(FALSE, tAskFrame);
			}
		}
		break;


	case ev_TPVmp_SetMediaKey_Req:
		OnQtSetMediaKey(ptMsg);
		break;

	default:
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}
}

void CVmpEqp::Show()
{
	msgprintnotime("VmpEqp Info : \n");
	CVmpModle* pcVmpMdl = NULL;

	for (u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; ++wMdlIndex)
	{
		pcVmpMdl = &m_atVmpMdl[wMdlIndex];
		if (pcVmpMdl->m_emStat != CVmpModle::EqpStat_OffLine)
		{
			msgprintnotime("  Index:%d, EqpID:%d, EqpIP:"TPIPFORMAT", Name:%s, EqpType:%d, Port(Eqp:%d, Ums:%d), Stat:%s, Node:%d, ConfID:%d\n",
							wMdlIndex, pcVmpMdl->m_byEqpID, Tpu32ToIP(pcVmpMdl->m_tRegInfo.m_dwEqpIP), pcVmpMdl->m_tRegInfo.m_achAlias,
							pcVmpMdl->m_emMdlType, pcVmpMdl->m_wEqpRcvStartPort, pcVmpMdl->m_wUmsRcvStartPort,
							GetVmpStatBuf(pcVmpMdl->m_emStat), pcVmpMdl->m_dwUserNode, pcVmpMdl->m_wConfID);
		}
	}
	return ;
}

BOOL32 CVmpEqp::OnDisConnect( u32 dwNode )
{	
	CVmpModle* ptEqpMdl = FindVmpMdl(dwNode);
	if ( NULL ==  ptEqpMdl )
	{
		return FALSE;
	}
	
 	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnDisConnect EqpID:%d, RegIP:"TPIPFORMAT" \n", ptEqpMdl->m_byEqpID, Tpu32ToIP(ptEqpMdl->m_tRegInfo.m_dwEqpIP)));

	TEqpInfo tInfo;
	tInfo.m_emEqpType = em_vmp_mdl;
	tInfo.m_byEqpID = ptEqpMdl->m_byEqpID;

	//通知call 合成器掉线
	SendMsgToCall(CInstance::DAEMON, evtp_UmsVmpUnReg_Notify, (u8*)&tInfo, sizeof(tInfo));

	//更新外设状态到eqpmgr
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptEqpMdl->m_dwUserNode, ptEqpMdl->m_byEqpID, FALSE);

	ptEqpMdl->Clear();

	return TRUE;
}

//板子上线后，给预先配置的外设 分配一个位置
CVmpModle* CVmpEqp::InsertVmp( TTPEqpCfg& tCfg, u32 dwNode )
{
	CHECK_EQP_SEM;

	CVmpModle* ptMdl = FindVmpMdl(tCfg.m_byEqpID);
	if ( NULL != ptMdl )
	{//已经存在 则拒绝
		return NULL;
	}

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{	
		if ( m_atVmpMdl[wMdlIndex].IsIdle() && m_atVmpMdl[wMdlIndex].m_emStat == CVmpModle::EqpStat_OffLine )
		{
			//初始化端口 每个合成器400个端口 总的起始端口为10000
			m_atVmpMdl[wMdlIndex].m_wEqpRcvStartPort = UMS_VMP_BEGIN_PORT + (tCfg.m_byEqpID - EQP_ID_VMP_BEG)*VMP_MAX_PORT_SPAN;
			m_atVmpMdl[wMdlIndex].m_wUmsRcvStartPort = UMS_VMP_BEGIN_PORT + (tCfg.m_byEqpID - EQP_ID_VMP_BEG)*VMP_MAX_PORT_SPAN + VMP_MAX_DEC_PORT_SPAN;

			m_atVmpMdl[wMdlIndex].m_emMdlType = tCfg.m_emEqpMdlType;
			m_atVmpMdl[wMdlIndex].m_emStat = CVmpModle::EqpStat_Idle;
			m_atVmpMdl[wMdlIndex].m_byEqpID = tCfg.m_byEqpID;
			m_atVmpMdl[wMdlIndex].m_dwUserNode = dwNode;

			return &m_atVmpMdl[wMdlIndex];
		}
	}

	return NULL;
}
//释放分配的位置
void CVmpEqp::DeleteVmp( u8 byEqpID )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{	
		if ( m_atVmpMdl[wMdlIndex].m_byEqpID == byEqpID )
		{
			m_atVmpMdl[wMdlIndex].m_emMdlType = em_unknow_eqp_mdl;
			m_atVmpMdl[wMdlIndex].m_emStat = CVmpModle::EqpStat_OffLine;
			m_atVmpMdl[wMdlIndex].m_byEqpID = 0;
		}
	}
	return ;
}

void CVmpEqp::CalcEqpUsedStat(TTPBrdUsedInfo& tUsed)
{
	tUsed.m_emType = em_vmp_mdl;
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_VMP_NUM; wMdlIndex ++ )
	{
		if ( m_atVmpMdl[wMdlIndex].m_emStat == CVmpModle::EqpStat_OffLine
			|| m_atVmpMdl[wMdlIndex].m_emStat == CVmpModle::EqpStat_Idle )
		{
			continue;
		}
		
		if ( m_atVmpMdl[wMdlIndex].m_dwUsed != 0 )
		{
			tUsed.m_wUsedNum ++;
		}
		tUsed.m_wRegNum ++;
	}

	return ;
}

BOOL32 CVmpEqp::AssignEqpEx( TEqpParam* ptEqpParam )
{
	if ( NULL == ptEqpParam )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::AssignEqpEx. ptEqpParam is NULL\n"));
		return FALSE;
	}

	TVmpParam*	ptVmpParam = (TVmpParam*)ptEqpParam;
	
	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl( ((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_byEqpID );
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::FindVmpMdl. no VmpMdl! wConfID:%d\n", ptVmpParam->m_wConfID));
		return FALSE;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::AssignEqpEx. wConfID:%d, EqpID:%d, CurStat:%s.\n", ptVmpParam->m_wConfID, ptVmpMdl->m_byEqpID, 
		GetVmpStatBuf(ptVmpMdl->m_emStat)));

	if (ptVmpMdl->m_emStat != CVmpModle::EqpStat_Normal)
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::AssignEqpEx. no idle VmpMdl! wConfID:%d, EqpID:%d, CurStat:%s.\n", ptVmpParam->m_wConfID, ptVmpMdl->m_byEqpID, 
			GetVmpStatBuf(ptVmpMdl->m_emStat)));
		return FALSE;
	}

	ptVmpMdl->m_emStat = CVmpModle::EqpStat_Assign;
	ptVmpMdl->m_dwUsed ++;
	ptVmpMdl->m_wConfID = ptVmpParam->m_wConfID;
	ptVmpMdl->m_tTpVmpParam.m_emVmpStyle = ptVmpParam->m_emVmpStyle;
	ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum = min(TP_VMP_MAX_IN_CHN_NUM, ptVmpParam->m_byVMPMemberNum);
	ptVmpMdl->m_tTpVmpParam.m_byVmpOutMemberNum = min(TP_VMP_MAX_OUT_CHN_NUM, ptVmpParam->m_byOutMemBerNum);

	// 合成in参数
	memcpy(&ptVmpMdl->m_tTpVmpParam.m_atVMPMember[0], &ptVmpParam->m_atVMPMember[0], 
		sizeof(TTPVMPMember)*ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum);

	// 合成out参数
	memcpy(&ptVmpMdl->m_tTpVmpParam.m_atVMPOutMember[0], &ptVmpParam->m_atVMPOutMember[0], 
		sizeof(TUmsVidFormat)*ptVmpMdl->m_tTpVmpParam.m_byVmpOutMemberNum);

	((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_byEqpID = ptVmpMdl->m_byEqpID;
	((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_wUmsStartPort = ptVmpMdl->m_wUmsRcvStartPort;
	((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_wEqpStartPort = ptVmpMdl->m_wEqpRcvStartPort;

	((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_dwEqpNode = ptVmpMdl->m_dwUserNode;
	((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_dwEqpInst = MAKEIID(AID_UMSEQP_APP, 1);
	((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_dwEqpIp = ptVmpMdl->m_tRegInfo.m_dwEqpIP;

	((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_emMdlType = ptVmpMdl->m_emMdlType;
	
	return TRUE;
}

BOOL32 CVmpEqp::ReleaseEqpEx( TEqpParam* ptEqpParam )
{
	if ( NULL == ptEqpParam )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::ReleaseEqpEx. ptEqpParam is NULL\n"));
		return FALSE;
	}
	
	TVmpParam*	ptVmpParam = (TVmpParam*)ptEqpParam;
	
	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::ReleaseEqpEx Fail!. wConfID:%d, wEqpID:%d\n", ptVmpParam->m_wConfID, 
				((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_byEqpID));
		return FALSE;
	}

	if ( ptVmpMdl->IsIdle() )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::ReleaseEqpEx. VmpMdl is Idle!. wConfID:%d, wEqpID:%d, Stat:%s\n", ptVmpParam->m_wConfID, 
				((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_byEqpID, GetVmpStatBuf(ptVmpMdl->m_emStat)));
		return FALSE;
	}

	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Error )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::ReleaseEqpEx. Stat Invalid!. wConfID:%d, wEqpID:%d, Stat:%s\n", ptVmpParam->m_wConfID, 
				((TVmpEqpRes*)ptVmpParam->m_ptEqpRes)->m_byEqpID, GetVmpStatBuf(ptVmpMdl->m_emStat)));
		return FALSE;
	}

	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::ReleaseEqpEx. wConfID:%d, EqpID:%d, Stat:%s\n", 
											ptVmpParam->m_wConfID, ptVmpMdl->m_byEqpID,
											GetVmpStatBuf(ptVmpMdl->m_emStat)));

	ptVmpMdl->m_wConfID = TP_INVALID_INDEX;
	ptVmpMdl->m_tTpVmpParam.ClearInOutParam();

	if (ptVmpMdl->m_emStat == CVmpModle::EqpStat_Assign)
	{// 直接置状态
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Normal;
		ptVmpMdl->m_dwUsed --;
	}
	else
	{
		//停止
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Stoping;
		ptVmpMdl->m_dwUsed --;
		
		SendMsgToEqpSsn( ptVmpMdl->m_dwUserInst, ev_TPVmp_StopMix_Req);
	}

	return TRUE;
}

void CVmpEqp::AskFrameReq( BOOL32 bToEqp, TTPVmpAskFrame& tAskFrame )
{
	CHECK_EQP_SEM;
	
	CVmpModle* ptVmpMdl = FindVmpMdl(tAskFrame.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::AskFrameReq. ptVmpMdl Is NULL! wEqpID:%d\n", tAskFrame.m_byEqpID));
		return ;
	}
	
	if ( bToEqp )
	{
		if ( !ptVmpMdl->m_tKeyFrameStatisToEqp.CheckFrameStatis() )
		{
			return ;
		}

		MdlLowDtl(Ums_Mdl_Eqp, ("CVmpEqp::Handle. FastUpdate To Eqp! wConfID:%d, EqpID:%d, ChanIndx:%d\n", 
			ptVmpMdl->m_wConfID, ptVmpMdl->m_byEqpID, tAskFrame.m_byChanIndx));
		SendMsgToEqpSsn(ptVmpMdl->m_dwUserInst, ev_TPVmp_FastUpdate_Req, (u8*)&tAskFrame, sizeof(TTPVmpAskFrame));
	}
	else
	{
		if ( !ptVmpMdl->m_tKeyFrameStatis.CheckFrameStatis() )
		{
			return ;
		}

		MdlLowDtl(Ums_Mdl_Eqp, ("CVmpEqp::Handle. FastUpdate To Call! wConfID:%d,  EqpID:%d, ChanIndx:%d\n", 
			ptVmpMdl->m_wConfID, ptVmpMdl->m_byEqpID, tAskFrame.m_byChanIndx));
		SendMsgToCall(ptVmpMdl->m_wConfID, ev_TPVmp_FastUpdate_Req, (u8*)&tAskFrame, sizeof(TTPVmpAskFrame));
	}
	
	return ;
}

void CVmpEqp::OnVmpReg( CTpMsg *const ptMsg )
{
	TTPVmpReg tVmpReg;
	TP_SAFE_CAST( tVmpReg, ptMsg->GetBody());

	u32 wSrcNode = ptMsg->GetSrcNode();
	u32 wSrcInst = ptMsg->GetSrcIId();

	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnVmpReg. Vmp Reg! EqpID:%d, EqpType:%d, EqpIP:"TPIPFORMAT", RcvStartPort:%d, Ver:%d\n", 
		tVmpReg.m_byEqpID, tVmpReg.m_emEqpMdlType, Tpu32ToIP(tVmpReg.m_dwEqpIPAddr), tVmpReg.m_dwEqpPort, tVmpReg.m_dwEqpVer));

// 	if ( tVmpReg.m_dwEqpVer )
// 	{//验证版本
// 		return ;
// 	}

	CHECK_EQP_SEM;

	u16 wErrCode = 0;
	CVmpModle* ptEqpMdl = FindVmpMdl(tVmpReg.m_byEqpID);
	if ( NULL ==  ptEqpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnVmpReg. EqpModle is noExist!\n"));

		wErrCode = ERR_MCU_NOIDLEEQPSSN;
		SendMsgToEqpSsn( ptMsg->GetSrcIId(), ev_TPVmp_Reg_NAck, (u8*)&wErrCode, sizeof(wErrCode));
		return ;
	}

	if ( ptEqpMdl->m_emStat != CVmpModle::EqpStat_Idle )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnVmpReg. VmpEntry Stat Invalid! Stat:%s\n", GetVmpStatBuf(ptEqpMdl->m_emStat)));

		if ( ptEqpMdl->m_emStat == CVmpModle::EqpStat_OffLine )
		{//外设不在线
			wErrCode = ERR_MCU_EQPOFFLINE;
		}
		else if ( ptEqpMdl->m_emStat == CVmpModle::EqpStat_Normal ||
			ptEqpMdl->m_emStat == CVmpModle::EqpStat_Assign ||
			ptEqpMdl->m_emStat == CVmpModle::EqpStat_Starting || 
			ptEqpMdl->m_emStat == CVmpModle::EqpStat_Running ||
			ptEqpMdl->m_emStat == CVmpModle::EqpStat_Stoping )
		{//外设已经在线
			wErrCode = ERR_MCU_PERIEQP_REGISTERED;
		}
		else if ( ptEqpMdl->m_emStat == CVmpModle::EqpStat_Error )
		{
			wErrCode = ERR_MCU_REGEQP_INVALID;
		}
		else
		{
			wErrCode = ERR_MCU_WRONGEQP;
		}
		
		SendMsgToEqpSsn( ptMsg->GetSrcIId(), ev_TPVmp_Reg_NAck, (u8*)&wErrCode, sizeof(wErrCode));
		return ;
	}

// vmp 暂无需校验该值，以本地为主
// 	if ( tVmpReg.m_emEqpMdlType != ptEqpMdl->m_emMdlType )
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnVmpReg. VmpEntry MdlType Invalid! LocalType:%d, RegType:%d\n", 
// 								ptEqpMdl->m_emMdlType, tVmpReg.m_emEqpMdlType));
// 		wErrCode = ERR_MCU_WRONGEQP;
// 		SendMsgToEqpSsn( ptMsg->GetSrcIId(), ev_TPVmp_Reg_NAck, (u8*)&wErrCode, sizeof(wErrCode));
// 		return ;
// 	}

	ptEqpMdl->m_dwUserNode = wSrcNode;
	ptEqpMdl->m_dwUserInst = wSrcInst;

	ptEqpMdl->m_tRegInfo.m_dwEqpIP = tVmpReg.m_dwEqpIPAddr;
	ptEqpMdl->m_tRegInfo.m_wVersion = (u16)tVmpReg.m_dwEqpVer;
	ptEqpMdl->m_bRegsited = TRUE;
//	ptEqpMdl->m_emStat = CVmpModle::EqpStat_Normal; 在vmpstatsNtfy中更新

	//更新外设状态到eqpmgr
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptEqpMdl->m_dwUserNode, ptEqpMdl->m_byEqpID, TRUE);

	TTPVmpRegAck tAck;
	tAck.m_dwIpAddr = GetLocalIP();
	tAck.m_wStartPort = ptEqpMdl->m_wUmsRcvStartPort;

	//将码流重传参数，发送给混音器
	TUmsRSParam tRsParam;
	if (CUmsConfigEx::GetInstance()->GetRsFirstTime() != 0 && CUmsConfigEx::GetInstance()->GetRsRejectTime() != 0)
	{
		tRsParam.m_wFirstTimeSpan	= CUmsConfigEx::GetInstance()->GetRsFirstTime();
		tRsParam.m_wSecondTimeSpan	= CUmsConfigEx::GetInstance()->GetRsSecondTime();
		tRsParam.m_wThirdTimeSpan	= CUmsConfigEx::GetInstance()->GetRsThirdTime();
		tRsParam.m_wRejectTimeSpan	= CUmsConfigEx::GetInstance()->GetRsRejectTime();
	}
	
	u8 abySndBuf[sizeof(TTPVmpRegAck) + sizeof(TUmsRSParam)] = {0};
	memcpy(abySndBuf, &tAck, sizeof(TTPVmpRegAck));
	memcpy(abySndBuf + sizeof(TTPVmpRegAck), &tRsParam, sizeof(TUmsRSParam));

	SendMsgToEqpSsn( wSrcInst, ev_TPVmp_Reg_Ack, abySndBuf, sizeof(abySndBuf));

	return ;
}

void CVmpEqp::OnVmpStatNtfy( CTpMsg *const ptMsg )
{
	TTPVmpStatNtfy tStatNtfy;
	TP_SAFE_CAST( tStatNtfy, ptMsg->GetBody());

	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(tStatNtfy.m_byEqpID);
	if ( NULL ==  ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnVmpStatNtfy. Eqp:%d no exist!\n", tStatNtfy.m_byEqpID));
		return ;
	}

	//合成器状态有任何变更都会收到此消息
	//所以此处判断状态只是做检测用。 有异常则打印。不更新合成器的状态。以Ack和Ntfy为准
	//另：此消息还主要用在自动合成的场合，此时合成器将最新的合成相关参数更新到主控，从而通知界面。
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnVmpStatNtfy. VmpStat Change! EqpID:%d, DecNum:%d, EncNum:%d, Style:%d, byStat:%d(0-normal,3-running), VmpEmStat:%s\n", 
									tStatNtfy.m_byEqpID, tStatNtfy.m_byDecodeNum, tStatNtfy.m_byEncodeNum, 
									tStatNtfy.m_byVMPStyle, tStatNtfy.m_byStat, GetVmpStatBuf(ptVmpMdl->m_emStat)));

	if ( tStatNtfy.m_byStat == 0 && ptVmpMdl->m_emStat < CVmpModle::EqpStat_Normal)
	{
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Normal;
	}

	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Normal )
	{//如果该合成器为正常状态 则 通知call 看是否有会议要使用

		ptVmpMdl->m_tTpVmpParam.m_byDecodeNum = tStatNtfy.m_byDecodeNum;
		ptVmpMdl->m_tTpVmpParam.m_byEncodeNum = tStatNtfy.m_byEncodeNum;

		TTPEqpCfg* ptEqpCfg = m_pcInst->GetEqpMgr()->GetEqpCfgByEqpID(ptVmpMdl->m_byEqpID);

 		TEqpInfo tEqpInfo;
 		tEqpInfo.m_byEqpID = ptVmpMdl->m_byEqpID;
		tEqpInfo.m_emEqpType = em_vmp_mdl;
		strncpy(tEqpInfo.m_szEqpAlias, ptEqpCfg->m_szEqpAlias, TP_MAXLEN_EQP_ALIAS);
		tEqpInfo.m_szEqpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';

		strncpy(ptVmpMdl->m_tRegInfo.m_achAlias,ptEqpCfg->m_szEqpAlias, TP_MAXLEN_EQP_ALIAS);
		ptVmpMdl->m_tRegInfo.m_achAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0'; 

		SendMsgToCall(CInstance::DAEMON, evtp_UmsVmpReg_Notify, (u8*)&tEqpInfo, sizeof(tEqpInfo));
	}
	
	return ;
}

void CVmpEqp::OnStartVmpAck( CTpMsg *const ptMsg )
{//Ack不作处理，以Ntfy为准
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmpAck. wEqpID:%d, ErrCode:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));

	return ;
}

void CVmpEqp::OnStartVmpNAck( CTpMsg *const ptMsg )
{
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmpNAck. wEqpID:%d, ErrCode:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));

	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(tRetInfo.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmpNAck. not Find EqpID! wEqpID:%d\n", tRetInfo.m_byEqpID));
		return ;
	}

	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Starting )
	{
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Error;
		//需要通知Call 画面合成开启失败

		TEqpInfo tInfo;
		tInfo.m_emEqpType = em_vmp_mdl;
		tInfo.m_byEqpID = ptVmpMdl->m_byEqpID;

		SendMsgToCall( CInstance::DAEMON, evtp_VmpToCall_NAck, (u8*)&tInfo, sizeof(tInfo));
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmpNAck. Stat Invalid! wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
					tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	}

	return ;	
}

void CVmpEqp::OnStartVmpNtfy( CTpMsg *const ptMsg )
{
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(tRetInfo.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmpNtfy. not Find EqpID! wEqpID:%d\n", tRetInfo.m_byEqpID));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmpNtfy. ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
								ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));

	if ( 0 == tRetInfo.m_wErrCode )
	{
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Running;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmpNtfy. ErrorCode! ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
								ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	}

	return ;
}

void CVmpEqp::OnStopVmpAck( CTpMsg *const ptMsg )
{//Ack不作处理，以Ntfy为准
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnStopVmpAck. wEqpID:%d, ErrCode:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
	
	return ;
}

void CVmpEqp::OnStopVmpNAck( CTpMsg *const ptMsg )
{
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(tRetInfo.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStopVmpNAck. not Find EqpID! wEqpID:%d\n", tRetInfo.m_byEqpID));
		return ;
	}
	
	MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStopVmpNAck. ConfID:%d, wEqpID:%d, ErrCode:%d\n", ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));

	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Stoping )
	{
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Error;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStopVmpNAck. Stat Invalid! ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
			ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	}
	
	return ;
}

void CVmpEqp::OnStopVmpNtfy( CTpMsg *const ptMsg )
{
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(tRetInfo.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStopVmpNtfy. not Find EqpID! wEqpID:%d\n", tRetInfo.m_byEqpID));
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnStopVmpNtfy. ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
									ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	
	if (0 ==  tRetInfo.m_wErrCode )
	{
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Normal;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStopVmpNtfy. ErrorCode! ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
									ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	}
	
	return ;
}

void CVmpEqp::OnChangeVmpAck( CTpMsg *const ptMsg )
{//Ack不作处理，以Ntfy为准
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnChangeVmpAck. wEqpID:%d, ErrCode:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
	
	return ;
}

void CVmpEqp::OnChangeVmpNAck( CTpMsg *const ptMsg )
{
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(tRetInfo.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnChangeVmpNAck. not Find EqpID! wEqpID:%d\n", tRetInfo.m_byEqpID));
		return ;
	}
	
	MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnChangeVmpNAck. ConfID:%d, wEqpID:%d, ErrCode:%d\n", 
												ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));

	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Running )
	{
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Error;
		//需要通知Call 画面合成参数调整失败

		TEqpInfo tInfo;
		tInfo.m_emEqpType = em_vmp_mdl;
		tInfo.m_byEqpID = ptVmpMdl->m_byEqpID;

		SendMsgToCall( CInstance::DAEMON, evtp_VmpToCall_NAck, (u8*)&tInfo, sizeof(tInfo));
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnChangeVmpNAck. Stat Invalid! ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
									ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	}
	
	return ;
}

void CVmpEqp::OnChangeVmpNtfy( CTpMsg *const ptMsg )
{
	TTPVmpRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());

	CHECK_EQP_SEM;

	CVmpModle* ptVmpMdl = FindVmpMdl(tRetInfo.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnChangeVmpNtfy. not Find EqpID! wEqpID:%d\n", tRetInfo.m_byEqpID));
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnChangeVmpNtfy. ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
								ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	
	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Running )
	{
		//需要通知Call 画面合成参数调整成功
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnChangeVmpNtfy. Stat Invalid! ConfID:%d, wEqpID:%d, ErrCode:%d, CurrStat:%s\n", 
									ptVmpMdl->m_wConfID, tRetInfo.m_byEqpID, tRetInfo.m_wErrCode, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	}
	
	return ;
}

void CVmpEqp::OnStartStopChnReq( CTpMsg *const ptMsg )
{//call 请求 关闭或者打开某合成外设的某输出通道
	u8 byEqpID, byChnID, byAcitve;
	TP_SAFE_CAST( byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST( byChnID, ptMsg->GetBody() + sizeof(u8));
	TP_SAFE_CAST( byAcitve, ptMsg->GetBody() + sizeof(u8) + sizeof(u8));
	
	CHECK_EQP_SEM;
	
	CVmpModle* ptVmpMdl = FindVmpMdl(byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartStopChnReq. not Find EqpID! wEqpID:%d\n", byEqpID));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnStartStopChnReq. ConfID:%d, wEqpID:%d, ChnInx:%d, Active:%d, CurrStat:%s\n", 
										ptVmpMdl->m_wConfID, byEqpID, byChnID, byAcitve, GetVmpStatBuf(ptVmpMdl->m_emStat)));

	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Running )
	{
		u8 abySndBuf[3] = {0};
		abySndBuf[0] = byEqpID;
		abySndBuf[1] = byChnID;
		abySndBuf[2] = byAcitve;
		SendMsgToEqpSsn(ptVmpMdl->m_dwUserInst, ev_TPVmp_StartStopChn_Req, abySndBuf, sizeof(abySndBuf));
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartStopChnReq. Stat Invalid! ConfID:%d, wEqpID:%d, Stat:%s\n", 
																ptVmpMdl->m_wConfID, byEqpID, GetVmpStatBuf(ptVmpMdl->m_emStat)));
	}

	return ;
}

void CVmpEqp::OnStartVmp( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	TTVmpStartParam tVmpParam;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(tVmpParam, ptMsg->GetBody() + sizeof(u8));

	CVmpModle* ptVmpMdl = FindVmpMdl(byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmp. not Find EqpID! wEqpID:%d\n", byEqpID));
		return ;
	}

	//状态检测
	if ( ptVmpMdl->m_emStat != CVmpModle::EqpStat_Running && ptVmpMdl->m_emStat != CVmpModle::EqpStat_Assign 
		&& ptVmpMdl->m_emStat != CVmpModle::EqpStat_Starting)
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmp. ConfID:%d, wEqpID:%d, CurrStat:%s\n", 
											ptVmpMdl->m_wConfID, byEqpID, GetVmpStatBuf(ptVmpMdl->m_emStat)));	
//		SendMsgToCall( CInstance::DAEMON, evtp_VmpToCall_NAck);
		return ;
	}
	
	ptVmpMdl->m_tTpVmpParam.m_emVmpStyle = tVmpParam.m_emVmpStyle;
	ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum = min(TP_VMP_MAX_IN_CHN_NUM, tVmpParam.m_byVMPMemberNum);

	memcpy(ptVmpMdl->m_tTpVmpParam.m_atVMPMember, tVmpParam.m_atVMPMember,
		sizeof(TTPVMPMember)*ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum);
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmp. ConfID:%d, wEqpID:%d, VmpStat:%s, VmpStyle:%d, VmpMemberNum:%d\n", 
											ptVmpMdl->m_wConfID, ptVmpMdl->m_byEqpID, GetVmpStatBuf(ptVmpMdl->m_emStat),
											ptVmpMdl->m_tTpVmpParam.m_emVmpStyle, ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum));

	u8 abySndBuf[ sizeof(u8) + sizeof(TTPVMPParam)] = {0};
	memcpy(abySndBuf, &ptVmpMdl->m_byEqpID, sizeof(u8));
	memcpy(abySndBuf+ sizeof(u8), &ptVmpMdl->m_tTpVmpParam, sizeof(TTPVMPParam));
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnStartVmp. EncryptInfo(%d,%s,%d)\n", 
		ptVmpMdl->m_tTpVmpParam.m_atVMPMember[0].m_tEncrypt.m_emEncryptModel, 
		ptVmpMdl->m_tTpVmpParam.m_atVMPMember[0].m_tEncrypt.m_achEncKey, 
		ptVmpMdl->m_tTpVmpParam.m_atVMPMember[0].m_tEncrypt.m_byKeyLen));

	if ( ptVmpMdl->m_emStat == CVmpModle::EqpStat_Assign )
	{
		ptVmpMdl->m_emStat = CVmpModle::EqpStat_Starting;
		SendMsgToEqpSsn( ptVmpMdl->m_dwUserInst, ev_TPVmp_StartMix_Req, abySndBuf, sizeof(abySndBuf));
	}
	else
	{
		SendMsgToEqpSsn( ptVmpMdl->m_dwUserInst, ev_TPVmp_ChangeMixParam_Req, abySndBuf, sizeof(abySndBuf));
	}

	return ;
}

void CVmpEqp::OnAdjustVmp( CTpMsg *const ptMsg )
{
	return; // 传统vmp不支持动态调整out格式，目前就按模板格式out，之后不再改变

	u8 byEqpID;
	TUmsVidFormat tVidFormat;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(tVidFormat, ptMsg->GetBody() + sizeof(u8));
	
	CVmpModle* ptVmpMdl = FindVmpMdl(byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnAdjustVmp. not Find EqpID! wEqpID:%d\n", byEqpID));
		return ;
	}
	
	//状态检测
	if ( ptVmpMdl->m_emStat != CVmpModle::EqpStat_Running)
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnAdjustVmp. ConfID:%d, wEqpID:%d, CurrStat:%s\n", 
			ptVmpMdl->m_wConfID, byEqpID, GetVmpStatBuf(ptVmpMdl->m_emStat)));	
		return ;
	}

	// 动态调整第一路合成出格式，如果相同不调整
	if (tVidFormat == ptVmpMdl->m_tTpVmpParam.m_atVMPOutMember[0])
	{
		MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnAdjustVmp. Same VidFormat. ConfID:%d, wEqpID:%d, Profile:%d, Res:%d, FrameRate:%d, Bitrate:%d.\n", 
			ptVmpMdl->m_wConfID, byEqpID, tVidFormat.m_emQualityLvl, tVidFormat.m_emRes, tVidFormat.m_wFrameRate, tVidFormat.m_wBitrate));
		return;
	}

	ptVmpMdl->m_tTpVmpParam.m_atVMPOutMember[0] = tVidFormat;
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnAdjustVmp. ConfID:%d, wEqpID:%d, Profile:%d, Res:%d, FrameRate:%d, Bitrate:%d.\n", 
				ptVmpMdl->m_wConfID, byEqpID, tVidFormat.m_emQualityLvl, tVidFormat.m_emRes, tVidFormat.m_wFrameRate, tVidFormat.m_wBitrate));
	
	u8 abySndBuf[ sizeof(u8) + sizeof(TTPVMPParam)] = {0};
	memcpy(abySndBuf, &ptVmpMdl->m_byEqpID, sizeof(u8));
	memcpy(abySndBuf+ sizeof(u8), &ptVmpMdl->m_tTpVmpParam, sizeof(TTPVMPParam));

	SendMsgToEqpSsn( ptVmpMdl->m_dwUserInst, ev_TPVmp_ChangeMixParam_Req, abySndBuf, sizeof(abySndBuf));

	return;
}


void CVmpEqp::OnQtSetMediaKey( CTpMsg *const ptMsg )
{
	TTPQTMediaKeyInfo tInfo;
	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(tInfo, ptMsg->GetBody() + sizeof(u8));
	
	CVmpModle* ptVmpMdl = FindVmpMdl(byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CVmpEqp::OnQtSetMediaKey. not Find EqpID! wEqpID:%d\n", byEqpID));
		return ;
	}
	
	tInfo.m_dwHandle = byEqpID;
	
	MdlHint(Ums_Mdl_Eqp, ("CVmpEqp::OnQtSetMediaKey. ConfID:%d, wEqpID:%d, KeyLen:%d, Flag:%u, Freq:%d\n", 
		ptVmpMdl->m_wConfID, byEqpID, tInfo.m_dwKeyLen, tInfo.m_dwQtFlag, tInfo.m_emKeyFrequency));
	
	SendMsgToEqpSsn(ptVmpMdl->m_dwUserInst, ev_TPVmp_SetMediaKey_Req, (u8*)&tInfo, sizeof(TTPQTMediaKeyInfo));
}





