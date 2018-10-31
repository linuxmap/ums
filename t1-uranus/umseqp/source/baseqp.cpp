#include "baseqp.h"
#include "innereventumscall.h"
#include "eqpinterface.h"
#include "eqpinst.h"
#include "umsconfigex.h"
#include "eqpmgr.h"
#include "mediatranseqp.h"
#include "innereventumsmpu2.h"

s8* GetBasStatBuf( CBasModle::EmEqpStat emStat )
{
	switch(emStat)
	{
	case CBasModle::EpqStat_OffLine:
		return "OffLine";
		break;
	case CBasModle::EqpStat_Idle:
		return "Idle";
		break;
	case CBasModle::EqpStat_Normal:
		return "Normal";
		break;
	default:
		return "InvalidStat";
		break;
	}
	
	return NULL;
}

s8* GetChanStatBuf( tagTBasChn::EmChnStat emStat )
{
	switch(emStat)
	{
	case tagTBasChn::Stat_BasChn_Idle:
		return "Idle";
		break;
	case tagTBasChn::Stat_BasChn_Normal:
		return "Normal";
		break;
	case tagTBasChn::Stat_BasChn_Reserve:
		return "Reserve";
		break;
	case tagTBasChn::Stat_BasChn_Starting:
		return "Starting";
		break;
	case tagTBasChn::Stat_BasChn_Running:
		return "Running";
		break;
	case tagTBasChn::Stat_BasChn_Stoping:
		return "Stoping";
		break;
	case tagTBasChn::Stat_BasChn_Error:
		return "Error";
		break;
	default:
		return "InvalidStat";
		break;
	}
	
	return NULL;
}

u16 GetOutChnIndx( u8 byChnID, EMEqpModleType emtype)
{
	u16 wOutChnIndx = 0;
	u8 byIndx = 0;
	if (em_bas_enhanced_eqp_mdl == emtype)
	{
		for ( byIndx = 0; byIndx < BAS_CHN_MAX_NUM_EHANCED; byIndx ++ )
		{
			if ( byIndx == 0 )
			{
				wOutChnIndx += 0;
			}
			else if ( byIndx == 1 )
			{
				wOutChnIndx += BAS_ENHACNED_OUT_CHN_MAX_NUM_1;
			}
			else if( byIndx == 2 )  
			{
				wOutChnIndx += BAS_ENHACNED_OUT_CHN_MAX_NUM_2;
			}
			else
			{
				wOutChnIndx += BAS_ENHACNED_OUT_CHN_MAX_NUM_OTHER;
			}
			
			if ( byChnID == byIndx )
			{
				break;
			}
		}
	}
	else if (em_bas_basic_eqp_mdl == emtype)
	{
		for ( byIndx = 0; byIndx < BAS_CHN_MAX_NUM_EHANCED; byIndx ++ )
		{
			if ( byIndx == 0 )
			{
				wOutChnIndx += 0;
			}
			else if ( byIndx == 1 )
			{
				wOutChnIndx += BAS_BASIC_OUT_CHN_MAX_NUM_1;
			}
			else if( byIndx == 2 )  
			{
				wOutChnIndx += BAS_BASIC_OUT_CHN_MAX_NUM_2;
			}
			else
			{
				wOutChnIndx += BAS_BASIC_OUT_CHN_MAX_NUM_OTHER;
			}
			
			if ( byChnID == byIndx )
			{
				break;
			}
		}
	}
	
	return wOutChnIndx;
}

CBasEqp::CBasEqp( CUmsEqpInst* pInst )
: CEqpBase(pInst)
{
	
}

CBasEqp::~CBasEqp()
{
	
}


void CBasEqp::Init()
{
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < TP_UMS_MAX_BAS_NUM; wIndex ++ )
	{
		m_atBasMdl[wIndex].Clear();
		m_atBasMdl[wIndex].m_byIndx = (u8)wIndex;
	}

	for ( wIndex = 0; wIndex < BAS_CHN_MAX_NUM_EHANCED*TP_UMS_MAX_BAS_NUM; wIndex ++ )
	{
		m_atBasChn[wIndex].Clear();
	}

	return ;
}

void CBasEqp::Show()
{
	msgprintnotime("BasEqp Info : \n");
	CBasModle* pcBasMdl = NULL;
	TBasChn* ptBasChn = NULL;
	
	CHECK_EQP_SEM;

	for (u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_BAS_NUM; ++wMdlIndex)
	{
		pcBasMdl = &m_atBasMdl[wMdlIndex];
		if (pcBasMdl->m_emStat != CBasModle::EpqStat_OffLine)
		{
			msgprintnotime("  Index:%d, EqpID:%d, EqpIP:"TPIPFORMAT", DsIP:"TPIPFORMAT", EqpType:%d, StartPort(Eqp:%d, Ums:%d), Stat:%s\n",
							wMdlIndex, pcBasMdl->m_byEqpID, Tpu32ToIP(pcBasMdl->m_tRegInfo.m_dwEqpIP),
							Tpu32ToIP(pcBasMdl->m_dwMediaIP),pcBasMdl->m_emMdlType, pcBasMdl->m_wEqpRcvStartPort,
							pcBasMdl->m_wUmsRcvStartPort, GetBasStatBuf(pcBasMdl->m_emStat));
			
			if ( pcBasMdl->m_emStat == CBasModle::EpqStat_OffLine || pcBasMdl->m_emStat == CBasModle::EqpStat_Idle )
			{
				continue;
			}
			
			for ( u16 wChnIndx = pcBasMdl->m_byIndx*BAS_CHN_MAX_NUM_EHANCED ; 
			wChnIndx < pcBasMdl->m_byIndx*BAS_CHN_MAX_NUM_EHANCED + BAS_CHN_MAX_NUM_EHANCED; wChnIndx ++ )
			{
				ptBasChn = &m_atBasChn[wChnIndx];
				
				msgprintnotime("     ChnIndx:%d, ChnID:%d, EqpID:%d, EncAbility:%d, OutChanNum:%d, ConfID:%d, Stat:%s\n", 
								wChnIndx, ptBasChn->m_byChnID, ptBasChn->m_byEqpID, ptBasChn->m_wEncAbility, ptBasChn->m_byOutChnNum,
								ptBasChn->m_wConfID, GetChanStatBuf(ptBasChn->m_emChnStat));
			}
		}
	}
}

BOOL32 CBasEqp::AssignEqpEx( TEqpParam* ptEqpParam )
{
	if ( NULL == ptEqpParam )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::AssignEqpEx. ptEqpParam is NULL\n"));
		return FALSE;
	}

	TBasParam*	ptBasParam = (TBasParam*)ptEqpParam;

	CHECK_EQP_SEM;

	u16 wChnIndx = 0;
	TBasChn* ptBasChn = FindSuitableBasChn( ptBasParam->m_emAssignType, ptBasParam->m_byOutMemBerNum, wChnIndx);
	if ( NULL == ptBasChn )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::AssignEqpEx BasChan no idle! ConfID:%d, OutMemberNum:%d\n", ptBasParam->m_wConfID, ptBasParam->m_byOutMemBerNum));
		return FALSE;
	}

	if ( NULL != ptBasChn->m_pcBasMdl )
	{
		ptBasChn->m_pcBasMdl->m_dwUsed ++;
		//更新使用率
		TTPBrdUsedInfo tUsed;
		CalcEqpUsedStat(tUsed);
		m_pcInst->GetEqpMgr()->UpdateBrdUsedState(tUsed);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::AssignEqpEx. ptBasChn->m_pcBasMdl is NULL! ConfID:%d, OutMemberNum:%d, ChnIndx:%d\n", 
													ptBasParam->m_wConfID, ptBasParam->m_byOutMemBerNum, ptBasChn->m_byChnID));
		return FALSE;
	}

	ptBasChn->m_emChnStat = tagTBasChn::Stat_BasChn_Reserve;
	ptBasChn->m_wConfID = ptBasParam->m_wConfID;

	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_byEqpID = ptBasChn->m_pcBasMdl->m_byEqpID;
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx = wChnIndx;

	//起始端口
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wUmsStartPort = 
							ptBasChn->m_pcBasMdl->m_wUmsRcvStartPort + GetOutChnIndx(ptBasChn->m_byChnID, ptBasChn->m_pcBasMdl->m_emMdlType)*UMS_MCU_PORT_PORTSPAN;
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wEqpStartPort = 
							ptBasChn->m_pcBasMdl->m_wEqpRcvStartPort + GetOutChnIndx(ptBasChn->m_byChnID, ptBasChn->m_pcBasMdl->m_emMdlType)*UMS_MCU_PORT_PORTSPAN;
	
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_dwEqpNode = ptBasChn->m_pcBasMdl->m_dwUserNode;
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_dwEqpInst = MAKEIID(AID_UMSEQP_APP, 1);
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_dwEqpIp = ptBasChn->m_pcBasMdl->m_tRegInfo.m_dwEqpIP;

	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::AssignEqpEx. ConfID:%d, EqpID;%d, ChanIndx:%d, OutMemberNum:%d\n", 
										ptBasParam->m_wConfID, ptBasChn->m_pcBasMdl->m_byEqpID, wChnIndx, ptBasParam->m_byOutMemBerNum));

	return TRUE;
}

BOOL32 CBasEqp::ReleaseEqpEx( TEqpParam* ptEqpParam )
{
	if ( NULL == ptEqpParam )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::ReleaseEqpEx. ptEqpParam is NULL\n"));
		return FALSE;
	}
	
	TBasParam*	ptBasParam = (TBasParam*)ptEqpParam;
	
	if ( NULL == ptEqpParam->m_ptEqpRes )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::ReleaseEqpEx. ptEqpParam->m_ptEqpRes is NULL! ConfID:%d\n", ptBasParam->m_wConfID));
		return FALSE;
	}

	CHECK_EQP_SEM;
	
	TBasChn* ptBasChn = &m_atBasChn[((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx];

	if ( ptBasChn->m_emChnStat == tagTBasChn::Stat_BasChn_Idle || ptBasChn->m_emChnStat == tagTBasChn::Stat_BasChn_Normal )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::ReleaseEqpEx. Stat Invalid! ConfID:%d, wEqpID:%d, ChanIndx:%d, Stat:%s\n",
									ptBasChn->m_wConfID,
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_byEqpID, 
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx,
									GetChanStatBuf(ptBasChn->m_emChnStat)));
		return FALSE;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::ReleaseEqpEx. ConfID:%d, wEqpID:%d, ChanIndx:%d, Stat:%s\n", 
									ptBasChn->m_wConfID,
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_byEqpID, 
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx,
									GetChanStatBuf(ptBasChn->m_emChnStat)));

	if ( NULL != ptBasChn->m_pcBasMdl )
	{
		if ( 0 == -- ptBasChn->m_pcBasMdl->m_dwUsed )
		{
// 			//分配转发板
// 			BOOL32 bRet = ((CMediaTransEqp*)m_pcInst->GetEqp(CUmsEqpInst::_CMediaTransEqp))->ReleaseDsForBas(
// 																					ptBasChn->m_pcBasMdl->m_tMediaEqp.m_dwEqpIp, 
// 																					BAS_CHN_MAX_NUM_EHANCED);
// 			if ( !bRet )
// 			{
// 				MdlError(Ums_Mdl_Eqp, ("CBasEqp::ReleaseEqpEx. AssignDsEqp Fail! ConfID:%d, ChnNum:%d, ChnIndx:%d\n", 
// 													ptBasParam->m_wConfID, ptBasParam->m_byOutMemBerNum, ptBasChn->m_byChnID));
// 			}
// 
// 			ptBasChn->m_pcBasMdl->m_tMediaEqp.Clear();

		}

		//更新使用率
		TTPBrdUsedInfo tUsed;
		CalcEqpUsedStat(tUsed);
		m_pcInst->GetEqpMgr()->UpdateBrdUsedState(tUsed);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::ReleaseEqpEx. ptBasChn->m_pcBasMdl is NULL! ConfID:%d, ChnNum:%d, ChnIndx:%d\n", 
														ptBasParam->m_wConfID, ptBasParam->m_byOutMemBerNum, ptBasChn->m_byChnID));
		return FALSE;
	}

	if ( ptBasChn->m_emChnStat == tagTBasChn::Stat_BasChn_Reserve )
	{//占用则直接置状态
		ptBasChn->m_emChnStat = tagTBasChn::Stat_BasChn_Normal;
		ptBasChn->m_wConfID = TP_INVALID_INDEX;
	}
	else
	{//使用状态 则请求板子停止适配
		ptBasChn->m_emChnStat = tagTBasChn::Stat_BasChn_Stoping;

		StopAdatper(ptBasChn);
	}

	return TRUE;
}

BOOL32 CBasEqp::OnDisConnect( u32 dwNode )
{
	CHECK_EQP_SEM;

	CBasModle* ptEqpMdl = FindBasMdl(dwNode);
	if ( NULL ==  ptEqpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnDisConnect. ptEqpMdl is noExist!\n"));
		return FALSE;
	}

	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnDisConnect EqpID:%d, RegIP:"TPIPFORMAT" \n", ptEqpMdl->m_byEqpID, Tpu32ToIP(ptEqpMdl->m_tRegInfo.m_dwEqpIP)));
	
	TBasChn* ptBasChn = NULL;
	for ( u16 wChnIndx = ptEqpMdl->m_byIndx*BAS_CHN_MAX_NUM_EHANCED ; 
							wChnIndx < ptEqpMdl->m_byIndx*BAS_CHN_MAX_NUM_EHANCED + BAS_CHN_MAX_NUM_EHANCED; wChnIndx ++ )
	{
		ptBasChn = &m_atBasChn[wChnIndx];
		ptBasChn->Clear();
	}

	u8 byEqpID = ptEqpMdl->m_byEqpID;

	//更新外设注册状态
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptEqpMdl->m_dwUserNode, byEqpID, FALSE);

	ptEqpMdl->Clear();

	//更新使用率
	TTPBrdUsedInfo tUsed;
	CalcEqpUsedStat(tUsed);
	m_pcInst->GetEqpMgr()->UpdateBrdUsedState(tUsed);

	//通知call 适配器掉线
	SendMsgToCall(CInstance::DAEMON, evtp_UmsBasUnReg_Notify, &byEqpID, sizeof(u8));

	return TRUE;
}

void CBasEqp::SendMsgToEqpSsn( u32 dwSrcIID, u16 wEvent, u8 * const pbyMsg /*= NULL*/, u16 wLen /*= 0 */ )
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

void CBasEqp::SendMsgToCall( u16 wConfID, u16 wEvent, u8 * const pbyMsg /*= NULL*/, u16 wLen /*= 0 */ )
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

CBasModle* CBasEqp::FindBasMdl( u8 byEqpID )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].m_byEqpID == byEqpID )
		{
			return &m_atBasMdl[wMdlIndex];
		}
	}

	return NULL;	
}

CBasModle* CBasEqp::FindBasMdl( u32 dwNode )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].m_dwUserNode == dwNode )
		{
			return &m_atBasMdl[wMdlIndex];
		}
	}
	
	return NULL;
}

TBasChn* CBasEqp::FindSuitableBasChn( TBasParam::EmAssignType emType, u8 byOutChanNum, u16& wChnIndx)
{
	u16 wChnIndxTmp = 0;
	TBasChn* ptBasChnTmp = NULL;
	TBasChn* ptBasChn = NULL;
	
	for ( u16 wIndx = 0 ; wIndx < BAS_CHN_MAX_NUM_EHANCED*TP_UMS_MAX_BAS_NUM; wIndx ++ )
	{
		ptBasChn = &m_atBasChn[wIndx];

		if ( ptBasChn->m_emChnStat != tagTBasChn::Stat_BasChn_Normal )
		{
			continue;
		}

		if ( NULL == ptBasChn->m_pcBasMdl )
		{
			continue;
		}

		if ( ptBasChn->m_pcBasMdl->m_emStat != CBasModle::EqpStat_Normal )
		{
			continue;
		}

		if ( !ptBasChn->CheckAbility(byOutChanNum) )
		{
			continue;
		}

		if ( NULL == ptBasChnTmp )
		{
			wChnIndxTmp = wIndx;
			ptBasChnTmp = ptBasChn;
		}

		if ( emType == TBasParam::em_AssignType_Brd )
		{
			if (ptBasChn->m_wEncAbility != BAS_ENCRES_3000)
			{
				continue;
			}

			if ( ptBasChn->m_byChnID == 0 || ptBasChn->m_byChnID == 1 )
			{
				wChnIndx = wIndx;
				return ptBasChn;
			}
		}
		else
		{
			if ( ptBasChn->m_byChnID != 0 && ptBasChn->m_byChnID != 1 )
			{
				wChnIndx = wIndx;
				return ptBasChn;
			}
		}
	}

	if( emType == TBasParam::em_AssignType_Brd )
	{
		return NULL;
	}
	else
	{
		wChnIndx = wChnIndxTmp;
		return ptBasChnTmp;
	}

	return NULL;
}

CBasModle* CBasEqp::InsertBas(TTPEqpCfg& tCfg, u32 dwNode)
{
	CHECK_EQP_SEM;

	CBasModle* ptMdl = FindBasMdl(tCfg.m_byEqpID);
	if ( NULL != ptMdl )
	{//已经存在 则拒绝
		return NULL;
	}

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_BAS_NUM; wMdlIndex ++ )
	{	
		if ( m_atBasMdl[wMdlIndex].IsIdle() && m_atBasMdl[wMdlIndex].m_emStat == CBasModle::EpqStat_OffLine )
		{
			//初始化端口 每个适配器1000个端口 总的起始端口为24000
			//解码和编码不能重复 间隔500
			m_atBasMdl[wMdlIndex].m_wEqpRcvStartPort = UMS_BAS_BEGIN_PORT + (tCfg.m_byEqpID - EQP_ID_BAS_BEG )*BAS_MAX_PORT_SPAN;
			m_atBasMdl[wMdlIndex].m_wUmsRcvStartPort = UMS_BAS_BEGIN_PORT + (tCfg.m_byEqpID - EQP_ID_BAS_BEG )*BAS_MAX_PORT_SPAN + BAS_MAX_DEC_PORT_SPAN;

			m_atBasMdl[wMdlIndex].m_emMdlType = tCfg.m_emEqpMdlType;
			m_atBasMdl[wMdlIndex].m_emStat = CBasModle::EqpStat_Idle;
			m_atBasMdl[wMdlIndex].m_byEqpID = tCfg.m_byEqpID;

			m_atBasMdl[wMdlIndex].m_dwUserNode = dwNode;
			
			return &m_atBasMdl[wMdlIndex];
		}
	}
	
	return NULL;
}

void CBasEqp::DeleteBas( u8 byEqpID )
{
	CHECK_EQP_SEM;

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_BAS_NUM; wMdlIndex ++ )
	{	
		if ( m_atBasMdl[wMdlIndex].m_byEqpID == byEqpID )
		{
			m_atBasMdl[wMdlIndex].m_emMdlType = em_unknow_eqp_mdl;
			m_atBasMdl[wMdlIndex].m_emStat = CBasModle::EpqStat_OffLine;
			m_atBasMdl[wMdlIndex].m_byEqpID = 0;
		}
	}
	return ;
}

void CBasEqp::CalcEqpUsedStat(TTPBrdUsedInfo& tUsed)
{
	tUsed.m_emType = em_bas_mdl;

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].m_emStat != CBasModle::EqpStat_Normal )
		{
			continue;
		}

		tUsed.m_wUsedNum += (u16)m_atBasMdl[wMdlIndex].m_dwUsed;
		if (m_atBasMdl[wMdlIndex].m_emMdlType == em_bas_enhanced_eqp_mdl)
		{
			tUsed.m_wRegNum += BAS_CHN_MAX_NUM_EHANCED;
		}
		else if (m_atBasMdl[wMdlIndex].m_emMdlType == em_bas_basic_eqp_mdl)
		{
			tUsed.m_wRegNum += BAS_CHN_MAX_NUM_BASIC;
		}
		else
		{

		}
	}

	return ;
}

void CBasEqp::Handle( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	switch(wEvent)
	{
	case ev_TPBas_Reg_Req:
		OnBasReg(ptMsg);
		break;
	case ev_TPBas_State_Nty:
		OnBasStatNtfy(ptMsg);
		break;
	case ev_TPBas_ChnState_Nty:
		OnBasChnStatNtfy(ptMsg);
		break;
	case ev_TPBas_StartAdapter_Req:
		OnStartAdapter(ptMsg);
		break;
	case ev_TPBas_StartAdapter_Ack:
		OnStartAdapterAck(ptMsg);
		break;
	case ev_TPBas_StartAdapter_NAck:
		OnStartAdapterNAck(ptMsg);
		break;
	case ev_TPBas_StopAdapter_Ack:
		OnStopAdapterAck(ptMsg);
		break;
	case ev_TPBas_StopAdapter_NAck:
		OnStopAdapterNAck(ptMsg);
		break;
	case ev_TPBas_FastUpdate_Req:
		OnAskFrameToCall(ptMsg);
		break;
	case evtp_UmsBasAskFrame_Req:
		OnAskFrameToEqp(ptMsg);
		break;

	case ev_TPBas_SetMediaKey_Req:
		OnQtSetMediaKey(ptMsg);
		break;

	default:
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}	
}

void CBasEqp::OnBasReg( CTpMsg *const ptMsg )
{
	TTPBasReg tBasReg;
	TP_SAFE_CAST( tBasReg, ptMsg->GetBody());
	
	u32 wSrcNode = ptMsg->GetSrcNode();
	u32 wSrcInst = ptMsg->GetSrcIId();
	
	if ( !tBasReg.m_dwEqpVer )
	{//验证版本
		return ;
	}
	
	CHECK_EQP_SEM;
	
	u16 wErrCode = 0;
	CBasModle* ptEqpMdl = FindBasMdl(tBasReg.m_byEqpID);
	if ( NULL ==  ptEqpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnBasReg. EqpModle is noExist!\n"));
		
		wErrCode = ERR_MCU_NOIDLEEQPSSN;
		SendMsgToEqpSsn( ptMsg->GetSrcIId(), ev_TPBas_Reg_NAck, (u8*)&wErrCode, sizeof(wErrCode));
		return ;
	}
	
	if ( ptEqpMdl->m_emStat != CBasModle::EqpStat_Idle )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnBasReg. BasEntry Stat Invalid! Stat:%s\n", GetBasStatBuf(ptEqpMdl->m_emStat)));
		
		if ( ptEqpMdl->m_emStat == CBasModle::EpqStat_OffLine )
		{//外设不在线
			wErrCode = ERR_MCU_EQPOFFLINE;
		}
		else if ( ptEqpMdl->m_emStat == CBasModle::EqpStat_Normal )
		{//外设已经在线
			wErrCode = ERR_MCU_PERIEQP_REGISTERED;
		}
		else
		{
			wErrCode = ERR_MCU_REGEQP_INVALID;
		}
		
		SendMsgToEqpSsn( ptMsg->GetSrcIId(), ev_TPBas_Reg_NAck, (u8*)&wErrCode, sizeof(wErrCode));
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnBasReg. Bas Reg! EqpID:%d, EqpType:%d, EqpIP:"TPIPFORMAT", RcvStartPort:%d, Ver:%d\n", 
		tBasReg.m_byEqpID, tBasReg.m_emEqpMdlType, Tpu32ToIP(tBasReg.m_dwEqpIPAddr), 
					tBasReg.m_dwEqpPort, tBasReg.m_dwEqpVer));

	ptEqpMdl->m_dwUserNode = wSrcNode;
	ptEqpMdl->m_dwUserInst = wSrcInst;
	
	ptEqpMdl->m_tRegInfo.m_dwEqpIP = tBasReg.m_dwEqpIPAddr;
	ptEqpMdl->m_tRegInfo.m_wVersion = (u16)tBasReg.m_dwEqpVer;
	ptEqpMdl->m_bRegsited = TRUE;
	ptEqpMdl->m_emStat = CBasModle::EqpStat_Normal;

	//更新使用率
	TTPBrdUsedInfo tUsed;
	CalcEqpUsedStat(tUsed);
	m_pcInst->GetEqpMgr()->UpdateBrdUsedState(tUsed);

	//Ack
	TTPBasRegAck tAck;
	tAck.m_dwIpAddr = GetLocalIP();
	tAck.m_wStartPort = ptEqpMdl->m_wUmsRcvStartPort;
	tAck.m_wEqpStartPort = ptEqpMdl->m_wEqpRcvStartPort;
	tAck.m_byEqpId = ptEqpMdl->m_byEqpID;
	
	//取配置的外设名称
	TTPEqpCfg* ptEqpCfg = m_pcInst->GetEqpMgr()->GetEqpCfgByEqpID(ptEqpMdl->m_byEqpID);
	if( NULL != ptEqpCfg)
	{
		tAck.SetAlias(ptEqpCfg->m_szEqpAlias);
	}
	else
	{
		tAck.SetAlias("umsbas");
	}
	
	//将码流重传参数，发送给混音器
	TUmsRSParam tRsParam;
	if (CUmsConfigEx::GetInstance()->GetRsFirstTime() != 0 && CUmsConfigEx::GetInstance()->GetRsRejectTime() != 0)
	{
		tRsParam.m_wFirstTimeSpan	= CUmsConfigEx::GetInstance()->GetRsFirstTime();
		tRsParam.m_wSecondTimeSpan	= CUmsConfigEx::GetInstance()->GetRsSecondTime();
		tRsParam.m_wThirdTimeSpan	= CUmsConfigEx::GetInstance()->GetRsThirdTime();
		tRsParam.m_wRejectTimeSpan	= CUmsConfigEx::GetInstance()->GetRsRejectTime();
	}
	
	u8 abySndBuf[sizeof(TTPBasRegAck) + sizeof(TUmsRSParam)] = {0};
	memcpy(abySndBuf, &tAck, sizeof(TTPBasRegAck));
	memcpy(abySndBuf + sizeof(TTPBasRegAck), &tRsParam, sizeof(TUmsRSParam));
	
	SendMsgToEqpSsn( wSrcInst, ev_TPBas_Reg_Ack, abySndBuf, sizeof(abySndBuf));

	return ;
}

void CBasEqp::OnBasStatNtfy( CTpMsg *const ptMsg )
{
	TTPBasStatNtfy tStatNtfy;
	TP_SAFE_CAST( tStatNtfy, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnBasStatNtfy. BasStat Change! EqpID:%d, EqpAlias:%s\n", tStatNtfy.m_byEqpID, tStatNtfy.m_szAlias));
	
	CHECK_EQP_SEM;
	
	CBasModle* ptBasMdl = FindBasMdl(tStatNtfy.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnBasStatNtfy. Eqp:%d no exist!\n", tStatNtfy.m_byEqpID));
		return ;
	}

	ptBasMdl->m_emStat = CBasModle::EqpStat_Normal;

	return ;
}

void CBasEqp::OnBasChnStatNtfy( CTpMsg *const ptMsg )
{
	TTPBasChnStatNtfy tStatNtfy;
	TP_SAFE_CAST( tStatNtfy, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CBasModle* ptBasMdl = FindBasMdl(tStatNtfy.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnBasChnStatNtfy. Eqp:%d no exist!\n", tStatNtfy.m_byEqpID));
		return ;
	}

	//basic 和 ehance 都是 按照最大间距保存
	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tStatNtfy.m_byChnIndx;

	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnBasChnStatNtfy. BasChnStat Change! ConfID:%d, EqpID:%d, ChnID:%d, NtfyStat:%d (0-idle,1-ready,2-run)\n", 
										m_atBasChn[wChnIndx].m_wConfID, tStatNtfy.m_byEqpID, tStatNtfy.m_byChnIndx, tStatNtfy.m_byStat));

	//更新板子最大支持几路编码
	m_atBasChn[wChnIndx].SetOutChnNum(tStatNtfy.m_byChnIndx, ptBasMdl->m_emMdlType);
	m_atBasChn[wChnIndx].m_byEqpID = ptBasMdl->m_byEqpID;
	m_atBasChn[wChnIndx].m_byChnID = tStatNtfy.m_byChnIndx;
	m_atBasChn[wChnIndx].m_pcBasMdl = ptBasMdl;

	//更新外设注册状态
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptBasMdl->m_dwUserNode, ptBasMdl->m_byEqpID, TRUE);

	//更新板子最新状态
	if ( tStatNtfy.m_byStat == 0 )
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTBasChn::Stat_BasChn_Idle;
	}
	else if ( tStatNtfy.m_byStat == 1 )
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTBasChn::Stat_BasChn_Normal;
	}
	else if ( tStatNtfy.m_byStat == 2 )
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTBasChn::Stat_BasChn_Running;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnBasChnStatNtfy. NtfyStat Invalid! Eqp:%d, ChnIdx:%d, NtfyStat:%d (0-idle,1-ready,2-run)\n", 
									tStatNtfy.m_byEqpID, tStatNtfy.m_byChnIndx, tStatNtfy.m_byStat));
	}

	return ;
}


void CBasEqp::OnStartAdapter(CTpMsg *const ptMsg)
{

	TStartBasAdapter tTpStart;
	TP_SAFE_CAST(tTpStart, ptMsg->GetBody());

	u16 wChnIndx = tTpStart.m_byChnID;

	if ( wChnIndx >= BAS_CHN_MAX_NUM_EHANCED*TP_UMS_MAX_BAS_NUM )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapter. ChnIndx Invalid! ChnIndx:%d\n", wChnIndx));
		return ;
	}

	CHECK_EQP_SEM;

	TBasChn* ptBasChn = &m_atBasChn[wChnIndx];

	TTPBasNAck tNAck;
	tNAck.m_byEqpID = m_atBasChn[wChnIndx].m_byEqpID;
	tNAck.m_wChnIndx = wChnIndx;

	if ( ptBasChn->m_emChnStat == tagTBasChn::Stat_BasChn_Idle ||
		ptBasChn->m_emChnStat == tagTBasChn::Stat_BasChn_Normal ||
		 ptBasChn->m_emChnStat == tagTBasChn::Stat_BasChn_Error )
	{
		//开启失败 通知call
		SendMsgToCall(GETINS(ptMsg->GetSrcIId()), evtp_UmsBasStart_NAck, (u8*)&tNAck, sizeof(tNAck));

		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapter. BasStat Invalid! ConfID:%d, ChnID:%d, Stat:%s\n", 
													ptBasChn->m_wConfID, ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat)));
		return ;
	}

	if ( NULL == ptBasChn->m_pcBasMdl )
	{
		//开启失败 通知call
		SendMsgToCall(GETINS(ptMsg->GetSrcIId()), evtp_UmsBasStart_NAck, (u8*)&tNAck, sizeof(tNAck));

		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapter. ptBasChn->m_pcBasMdl is NULL! ConfID:%d, ChnID:%d, Stat:%s\n", 
											ptBasChn->m_wConfID, ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapter. ConfID:%d, ChnIndx:%d, ChnID:%d, Stat:%s, EqpID:%d\n", 
															ptBasChn->m_wConfID, wChnIndx, 
															ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat), 
															ptBasChn->m_pcBasMdl->m_byEqpID));

	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapter. EncryptInfo(%d,%s,%d)\n", tTpStart.m_tEncrypt.m_emEncryptModel, 
		tTpStart.m_tEncrypt.m_achEncKey, tTpStart.m_tEncrypt.m_byKeyLen));

	// 通知mpu2是通道ID
	tTpStart.m_byChnID = ptBasChn->m_byChnID;
	//此处将该值转换成 bas通道对应的最大编码路数
	tTpStart.m_tBasParam.m_byParamNum = ptBasChn->m_byOutChnNum;
	tTpStart.m_tMaxBasParam.m_byParamNum = ptBasChn->m_byOutChnNum;

	if ( ptBasChn->m_emChnStat == tagTBasChn::Stat_BasChn_Reserve )
	{
		ptBasChn->m_emChnStat = tagTBasChn::Stat_BasChn_Starting;

		SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_TPBas_StartAdapter_Req, (u8*)&tTpStart, sizeof(TStartBasAdapter));
	}
	else
	{
		SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_TPBas_SetAdapterParam_Req, (u8*)&tTpStart, sizeof(TStartBasAdapter));
	}

	return ;
}

void CBasEqp::OnStartAdapterAck( CTpMsg *const ptMsg )
{
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterAck. Eqp:%d no exist!\n", tRetInfo.m_byEqpID));
		return ;
	}

	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}

	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
											m_atBasChn[wChnIndx].m_wConfID,
											tRetInfo.m_byEqpID, wChnIndx, tRetInfo.m_byChnID, 
											GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));

	if(m_atBasChn[wChnIndx].m_emChnStat == tagTBasChn::Stat_BasChn_Starting)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTBasChn::Stat_BasChn_Running;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterAck. Stat Invalid! ConfID:%d,  wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
											m_atBasChn[wChnIndx].m_wConfID,
											tRetInfo.m_byEqpID, wChnIndx, tRetInfo.m_byChnID, 
											GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}

}

void CBasEqp::OnStartAdapterNAck( CTpMsg *const ptMsg )
{
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterNAck. Eqp:%d no exist!\n", tRetInfo.m_byEqpID));
		return ;
	}
	
	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterNAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}

	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterNAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
								m_atBasChn[wChnIndx].m_wConfID,
								tRetInfo.m_byEqpID, wChnIndx, tRetInfo.m_byChnID, 
								GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	
	if(m_atBasChn[wChnIndx].m_emChnStat == tagTBasChn::Stat_BasChn_Starting)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTBasChn::Stat_BasChn_Error;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStartAdapterNAck. Stat Invalid! ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n",
										m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, 
										wChnIndx, tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}

	TTPBasNAck tNAck;
	tNAck.m_byEqpID = m_atBasChn[wChnIndx].m_byEqpID;
	tNAck.m_wChnIndx = wChnIndx;
	//开启失败 通知call
	SendMsgToCall( m_atBasChn[wChnIndx].m_wConfID, evtp_UmsBasStart_NAck, (u8*)&tNAck, sizeof(tNAck));
}

void CBasEqp::OnStopAdapterAck( CTpMsg *const ptMsg )
{
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterAck. Eqp:%d no exist!\n", tRetInfo.m_byEqpID));
		return ;
	}

	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}
	
	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n",
						m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
						tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	
	if(m_atBasChn[wChnIndx].m_emChnStat == tagTBasChn::Stat_BasChn_Stoping)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTBasChn::Stat_BasChn_Normal;

		m_atBasChn[wChnIndx].m_wConfID = TP_INVALID_INDEX;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterAck. Stat Invalid! ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
							m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
							tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}
}

void CBasEqp::OnStopAdapterNAck( CTpMsg *const ptMsg )
{
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterNAck. Eqp:%d no exist! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}

	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterNAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}
	
	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterNAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
					m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
					tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	
	if(m_atBasChn[wChnIndx].m_emChnStat == tagTBasChn::Stat_BasChn_Stoping)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTBasChn::Stat_BasChn_Error;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::OnStopAdapterNAck. Stat Invalid! ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n",
						m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
						tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}	
}

void CBasEqp::StopAdatper( TBasChn* ptBasChn )
{
	if ( NULL == ptBasChn->m_pcBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CBasEqp::StopAdatper. m_pcBasMdl is NULL! wEqpID:%d, ChnID:%d, Stat:%s\n", 
									ptBasChn->m_byEqpID, ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat)));
		return ;
	}

	SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_TPBas_StopAdapter_Req, &ptBasChn->m_byChnID, sizeof(ptBasChn->m_byChnID));
}

void CBasEqp::OnAskFrameToEqp( CTpMsg *const ptMsg )
{
	u16 wChnIndx;
	TP_SAFE_CAST(wChnIndx, ptMsg->GetBody());
	
	if ( wChnIndx >= BAS_CHN_MAX_NUM_EHANCED*TP_UMS_MAX_BAS_NUM )
	{
		MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToEqp.  wChndIndx Invalid! ChnIndx:%d\n", wChnIndx));
		return ;
	}

	CHECK_EQP_SEM;

	if ( m_atBasChn[wChnIndx].m_emChnStat == tagTBasChn::Stat_BasChn_Running
		|| m_atBasChn[wChnIndx].m_emChnStat == tagTBasChn::Stat_BasChn_Starting )
	{
		if (!m_atBasChn[wChnIndx].m_tKeyFrameStatisToEqp.CheckFrameStatis())
		{
			MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToEqp Src req frequent! ConfID:%d, Eqp:%d ,ChnID:%d, ChnIndx:%d\n"
				, m_atBasChn[wChnIndx].m_wConfID, m_atBasChn[wChnIndx].m_byEqpID, m_atBasChn[wChnIndx].m_byChnID, wChnIndx));
			return;
		}

		MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToEqp. ConfID:%d, Eqp:%d ,ChnID:%d, ChnIndx:%d\n", 
								m_atBasChn[wChnIndx].m_wConfID,
								m_atBasChn[wChnIndx].m_byEqpID, m_atBasChn[wChnIndx].m_byChnID, wChnIndx));

		TTPBasAskFrame tAsk;
		tAsk.m_byEqpID = m_atBasChn[wChnIndx].m_byEqpID;
		tAsk.m_byChanID = m_atBasChn[wChnIndx].m_byChnID;
		SendMsgToEqpSsn(m_atBasChn[wChnIndx].m_pcBasMdl->m_dwUserInst, ev_TPBas_FastUpdate_Req, (u8*)&tAsk, sizeof(tAsk));
	}
	else
	{
		MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToEqp. BasChn Stat Invalid! ConfID:%d, Eqp:%d ,ChnID:%d, ChanStat:%s\n", 
								m_atBasChn[wChnIndx].m_wConfID, m_atBasChn[wChnIndx].m_byEqpID, m_atBasChn[wChnIndx].m_byChnID, 
								GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}

	return ;
}

void CBasEqp::OnAskFrameToCall( CTpMsg *const ptMsg )
{
	TTPBasAskFrame tAsk;
	TP_SAFE_CAST(tAsk, ptMsg->GetBody());

	CHECK_EQP_SEM;

	CBasModle* ptBasMdl = FindBasMdl(tAsk.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToCall. Eqp:%d no exist! ChnID:%d\n", tAsk.m_byEqpID, tAsk.m_byChanID));
		return ;
	}

	u16 wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tAsk.m_byChanID;

	if ( m_atBasChn[wChnIndx].m_emChnStat == tagTBasChn::Stat_BasChn_Running )
	{
		u8 abySndBuf[ sizeof(u8) + sizeof(u16) ] = {0};

		
		if (!m_atBasChn[wChnIndx].m_tKeyFrameStatis.CheckFrameStatis())
		{
			MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToCall Src req frequent! ConfID:%d, Eqp:%d ,ChnID:%d, ChnIndx:%d\n"
				, m_atBasChn[wChnIndx].m_wConfID, m_atBasChn[wChnIndx].m_byEqpID, m_atBasChn[wChnIndx].m_byChnID, wChnIndx));
			return;
		}

		memcpy(abySndBuf, &ptBasMdl->m_byEqpID, sizeof(u8));
		memcpy(abySndBuf + sizeof(u8), &wChnIndx, sizeof(u16));

		MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToCall. ConfID:%d, Eqp:%d ,ChnID:%d, ChnIndx:%d\n", 
								m_atBasChn[wChnIndx].m_wConfID,
								m_atBasChn[wChnIndx].m_byEqpID, m_atBasChn[wChnIndx].m_byChnID, wChnIndx));

		SendMsgToCall(m_atBasChn[wChnIndx].m_wConfID, evtp_UmsBasAskFrame_Req, abySndBuf, sizeof(abySndBuf));
	}
	else
	{
		MdlLowDtl(Ums_Mdl_Eqp, ("CBasEqp::OnAskFrameToCall. BasChn Stat Invalid! ConfID:%d, Eqp:%d ,ChnID:%d, ChanStat:%s\n", 
								m_atBasChn[wChnIndx].m_wConfID,
								tAsk.m_byEqpID, tAsk.m_byChanID, 
								GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}

	return ;
}

void CBasEqp::ChangeBasMeidaDsIp(TBasSndAddr& tSndAddr)
{
	CBasModle* ptModle = FindBasMdl(tSndAddr.m_byEqpID);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CBasEqp::ChangeBasMeidaDsIp. EqpID:%d, NewIp:"TPIPFORMAT", CurIP:"TPIPFORMAT"\n", 
		tSndAddr.m_byEqpID, Tpu32ToIP(tSndAddr.m_dwNewDsIP), Tpu32ToIP(ptModle->m_dwMediaIP)));
	
	if(0 == tSndAddr.m_dwNewDsIP || ptModle->m_dwMediaIP == tSndAddr.m_dwNewDsIP)
	{// 转发板ip无效或者新旧ip相同 不需要变更
		return;
	}
	
	ptModle->m_dwMediaIP = tSndAddr.m_dwNewDsIP;
	SendMsgToEqpSsn(ptModle->m_dwUserInst, ev_TPEqp_ChangeSndAddr_Req, (u8*)&tSndAddr, sizeof(tSndAddr));
}


void CBasEqp::OnQtSetMediaKey( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	u16 wChnlID;
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(wChnlID, ptMsg->GetBody()+sizeof(u8));
	TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(byEqpID)+sizeof(wChnlID));
	
	TBasChn* ptBasChn = &m_atBasChn[wChnlID];
	
	//handle携带chnlID过去
	tInfo.m_dwHandle = ptBasChn->m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CBasEqp::OnQtSetMediaKey. ConfID:%d, wEqpID:%d, KeyLen:%d, Flag:%u, Freq:%d\n", 
		ptBasChn->m_wConfID, byEqpID, tInfo.m_dwKeyLen, tInfo.m_dwQtFlag, tInfo.m_emKeyFrequency));
	
	SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_TPBas_SetMediaKey_Req, (u8*)&tInfo, sizeof(TTPQTMediaKeyInfo));
}

