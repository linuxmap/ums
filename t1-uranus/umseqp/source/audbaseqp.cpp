#include "audbaseqp.h"
#include "innereventumscall.h"
#include "eqpinterface.h"
#include "eqpinst.h"
#include "umsconfigex.h"
#include "eqpmgr.h"
#include "mediatranseqp.h"
#include "innereventumsmpu2.h"
#include "innereventumsaudbas.h"

#define UMS_APU2_BAS_START_PORT 40000 //外部端口 apu2 bas的码流接收端口， 目前apu2上有mix和bas，注意不能重复，与本地的接收端口也不能重复

s8* GetBasStatBuf( CAudBasModle::EmEqpStat emStat )
{
	switch(emStat)
	{
	case CAudBasModle::EpqStat_OffLine:
		return "OffLine";
		break;
	case CAudBasModle::EqpStat_Idle:
		return "Idle";
		break;
	case CAudBasModle::EqpStat_Normal:
		return "Normal";
		break;
	default:
		return "InvalidStat";
		break;
	}
	
	return NULL;
}

s8* GetChanStatBuf( tagTAudBasChn::EmChnStat emStat )
{
	switch(emStat)
	{
	case tagTAudBasChn::Stat_BasChn_Idle:
		return "Idle";
		break;
	case tagTAudBasChn::Stat_BasChn_Normal:
		return "Normal";
		break;
	case tagTAudBasChn::Stat_BasChn_Reserve:
		return "Reserve";
		break;
	case tagTAudBasChn::Stat_BasChn_Starting:
		return "Starting";
		break;
	case tagTAudBasChn::Stat_BasChn_Running:
		return "Running";
		break;
	case tagTAudBasChn::Stat_BasChn_Stoping:
		return "Stoping";
		break;
	case tagTAudBasChn::Stat_BasChn_Error:
		return "Error";
		break;
	default:
		return "InvalidStat";
		break;
	}
	
	return NULL;
}

u16 GetAudBasOutChnIndx( u8 byChnID)
{
	u16 wOutChnIndx = 0;
	for ( u8 byIndx = 0; byIndx < AUD_BAS_MAX_CHNL_NUM; byIndx ++ )
	{
		if ( byIndx == 0 )
		{
			wOutChnIndx += 0;
		}
		else
		{
			wOutChnIndx += AUD_BAS_MAX_OUT_CHNL_NUM;
		}
			
		if ( byChnID == byIndx )
		{
			break;
		}
	}
	
	return wOutChnIndx;
}

CAudBasEqp::CAudBasEqp( CUmsEqpInst* pInst )
: CEqpBase(pInst)
{
	
}

CAudBasEqp::~CAudBasEqp()
{
	
}


void CAudBasEqp::Init()
{
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < TP_UMS_MAX_AUD_BAS_NUM; wIndex ++ )
	{
		m_atBasMdl[wIndex].Clear();
		m_atBasMdl[wIndex].m_byIndx = (u8)wIndex;
	}

	for ( wIndex = 0; wIndex < AUD_BAS_MAX_CHNL_NUM*TP_UMS_MAX_AUD_BAS_NUM; wIndex ++ )
	{
		m_atBasChn[wIndex].Clear();
	}

	return ;
}

void CAudBasEqp::Show()
{
	msgprintnotime("AudBasEqp Info : \n");
	CAudBasModle* pcBasMdl = NULL;
	TAudBasChn* ptBasChn = NULL;
	
	CHECK_EQP_SEM;

	for (u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_AUD_BAS_NUM; ++wMdlIndex)
	{
		pcBasMdl = &m_atBasMdl[wMdlIndex];
		if (pcBasMdl->m_emStat != CAudBasModle::EpqStat_OffLine)
		{
			msgprintnotime("  Index:%d, EqpID:%d, EqpIP:"TPIPFORMAT", EqpType:%d, StartPort(Eqp:%d, Ums:%d), DsEqpIP:"TPIPFORMAT", Stat:%s\n",
							wMdlIndex, pcBasMdl->m_byEqpID, Tpu32ToIP(pcBasMdl->m_tRegInfo.m_dwEqpIP),
							pcBasMdl->m_emMdlType, pcBasMdl->m_wEqpRcvStartPort, pcBasMdl->m_wUmsRcvStartPort,
							Tpu32ToIP(pcBasMdl->m_dwMediaIP), GetBasStatBuf(pcBasMdl->m_emStat));
			
			if ( pcBasMdl->m_emStat == CAudBasModle::EpqStat_OffLine || pcBasMdl->m_emStat == CAudBasModle::EqpStat_Idle )
			{
				continue;
			}
			
			for ( u16 wChnIndx = pcBasMdl->m_byIndx*AUD_BAS_MAX_CHNL_NUM ; 
			wChnIndx < pcBasMdl->m_byIndx*AUD_BAS_MAX_CHNL_NUM + AUD_BAS_MAX_CHNL_NUM; wChnIndx ++ )
			{
				ptBasChn = &m_atBasChn[wChnIndx];
				
				msgprintnotime("     ChnIndx:%d, ChnID:%d, EqpID:%d, ConfID:%d, Stat:%s\n", 
								wChnIndx, ptBasChn->m_byChnID, ptBasChn->m_byEqpID,
								ptBasChn->m_wConfID, GetChanStatBuf(ptBasChn->m_emChnStat));
			}
		}
	}
}

BOOL32 CAudBasEqp::AssignEqpEx( TEqpParam* ptEqpParam )
{
	if ( NULL == ptEqpParam )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::AssignEqpEx. ptEqpParam is NULL\n"));
		return FALSE;
	}

	CHECK_EQP_SEM;

	TAudBasParam*	ptBasParam = (TAudBasParam*)ptEqpParam;
	TAudBasChn* ptBasChn = NULL;

	if (ptBasParam->m_wReqNum != 0)
	{// 
		ptBasChn = FindSuitableBasChn(ptBasParam);
	}
	else
	{
		ptBasChn = FindSuitableBasChn();
	}

	if ( NULL == ptBasChn )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::AssignEqpEx BasChan no idle! ConfID:%d, Node:%d, ReqNum:%d\n", 
			ptBasParam->m_wConfID, ptBasParam->m_dwNode, ptBasParam->m_wReqNum));
		return FALSE;
	}

	if ( NULL != ptBasChn->m_pcBasMdl )
	{
		ptBasChn->m_pcBasMdl->m_dwUsed++;
		//更新使用率
		TTPBrdUsedInfo tUsed;
		CalcEqpUsedStat(tUsed);
		m_pcInst->GetEqpMgr()->UpdateBrdUsedState(tUsed);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::AssignEqpEx. ptBasChn->m_pcBasMdl is NULL! ConfID:%d, ChnIndx:%d\n", 
													ptBasParam->m_wConfID, ptBasChn->m_byChnID));
		return FALSE;
	}

	ptBasChn->m_emChnStat = tagTAudBasChn::Stat_BasChn_Reserve;
	ptBasChn->m_wConfID = ptBasParam->m_wConfID;

	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_byEqpID = ptBasChn->m_pcBasMdl->m_byEqpID;
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx = ptBasChn->m_pcBasMdl->GetMdlChnBeginIndx() + ptBasChn->m_byChnID;

	//起始端口
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wUmsStartPort = 
							ptBasChn->m_pcBasMdl->m_wUmsRcvStartPort + GetAudBasOutChnIndx(ptBasChn->m_byChnID)*UMS_MCU_PORT_PORTSPAN;
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wEqpStartPort = 
							ptBasChn->m_pcBasMdl->m_wEqpRcvStartPort + GetAudBasOutChnIndx(ptBasChn->m_byChnID)*UMS_MCU_PORT_PORTSPAN;
	
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_dwEqpNode = ptBasChn->m_pcBasMdl->m_dwUserNode;
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_dwEqpInst = MAKEIID(AID_UMSEQP_APP, 1);
	((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_dwEqpIp = ptBasChn->m_pcBasMdl->m_tRegInfo.m_dwEqpIP;

	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::AssignEqpEx. ConfID:%d, EqpID;%d, ChanIndx:%d\n", 
										ptBasParam->m_wConfID, ptBasChn->m_pcBasMdl->m_byEqpID, ptBasChn->m_pcBasMdl->GetMdlChnBeginIndx() + ptBasChn->m_byChnID));

	return TRUE;
}

BOOL32 CAudBasEqp::ReleaseEqpEx( TEqpParam* ptEqpParam )
{
	if ( NULL == ptEqpParam )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::ReleaseEqpEx. ptEqpParam is NULL\n"));
		return FALSE;
	}
	
	TAudBasParam*	ptBasParam = (TAudBasParam*)ptEqpParam;
	
	if ( NULL == ptEqpParam->m_ptEqpRes )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::ReleaseEqpEx. ptEqpParam->m_ptEqpRes is NULL! ConfID:%d\n", ptBasParam->m_wConfID));
		return FALSE;
	}

	CHECK_EQP_SEM;
	
	TAudBasChn* ptBasChn = &m_atBasChn[((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx];

	if ( ptBasChn->m_emChnStat == tagTAudBasChn::Stat_BasChn_Idle || ptBasChn->m_emChnStat == tagTAudBasChn::Stat_BasChn_Normal )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::ReleaseEqpEx. Stat Invalid! ConfID:%d, wEqpID:%d, ChanIndx:%d, Stat:%s\n",
									ptBasChn->m_wConfID,
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_byEqpID, 
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx,
									GetChanStatBuf(ptBasChn->m_emChnStat)));
		return FALSE;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::ReleaseEqpEx. ConfID:%d, wEqpID:%d, ChanIndx:%d, Stat:%s\n", 
									ptBasChn->m_wConfID,
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_byEqpID, 
									((TBasEqpRes*)ptBasParam->m_ptEqpRes)->m_tBasChnInfo.m_wChnIndx,
									GetChanStatBuf(ptBasChn->m_emChnStat)));

	if ( NULL != ptBasChn->m_pcBasMdl )
	{
		--ptBasChn->m_pcBasMdl->m_dwUsed;
		//更新使用率
		TTPBrdUsedInfo tUsed;
		CalcEqpUsedStat(tUsed);
		m_pcInst->GetEqpMgr()->UpdateBrdUsedState(tUsed);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::ReleaseEqpEx. ptBasChn->m_pcBasMdl is NULL! ConfID:%d, ChnIndx:%d\n", 
														ptBasParam->m_wConfID, ptBasChn->m_byChnID));
		return FALSE;
	}

	if ( ptBasChn->m_emChnStat == tagTAudBasChn::Stat_BasChn_Reserve )
	{//占用则直接置状态
		ptBasChn->m_emChnStat = tagTAudBasChn::Stat_BasChn_Normal;
		ptBasChn->m_wConfID = TP_INVALID_INDEX;
	}
	else
	{//使用状态 则请求板子停止适配
		ptBasChn->m_emChnStat = tagTAudBasChn::Stat_BasChn_Stoping;

		StopAdatper(ptBasChn);
	}

	return TRUE;
}

BOOL32 CAudBasEqp::OnDisConnect( u32 dwNode )
{
	CHECK_EQP_SEM;

	CAudBasModle* ptEqpMdl = FindBasMdl(dwNode);
	if ( NULL ==  ptEqpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnDisConnect. ptEqpMdl is noExist!\n"));
		return FALSE;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnDisConnect EqpID:%d, RegIP:"TPIPFORMAT" \n", ptEqpMdl->m_byEqpID, Tpu32ToIP(ptEqpMdl->m_tRegInfo.m_dwEqpIP)));
	
	TAudBasChn* ptBasChn = NULL;
	for ( u16 wChnIndx = ptEqpMdl->m_byIndx*AUD_BAS_MAX_CHNL_NUM ; 
							wChnIndx < ptEqpMdl->m_byIndx*AUD_BAS_MAX_CHNL_NUM + AUD_BAS_MAX_CHNL_NUM; wChnIndx ++ )
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

void CAudBasEqp::SendMsgToEqpSsn( u32 dwSrcIID, u16 wEvent, u8 * const pbyMsg /*= NULL*/, u16 wLen /*= 0 */ )
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

void CAudBasEqp::SendMsgToCall( u16 wConfID, u16 wEvent, u8 * const pbyMsg /*= NULL*/, u16 wLen /*= 0 */ )
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

CAudBasModle* CAudBasEqp::FindBasMdl( u8 byEqpID )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_AUD_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].m_byEqpID == byEqpID )
		{
			return &m_atBasMdl[wMdlIndex];
		}
	}

	return NULL;	
}

CAudBasModle* CAudBasEqp::FindBasMdl( u32 dwNode )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_AUD_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].m_dwUserNode == dwNode )
		{
			return &m_atBasMdl[wMdlIndex];
		}
	}
	
	return NULL;
}

TAudBasChn* CAudBasEqp::FindSuitableBasChn()
{
	TAudBasChn* ptBasChn = NULL;
	
	for ( u16 wIndx = 0 ; wIndx < AUD_BAS_MAX_CHNL_NUM*TP_UMS_MAX_AUD_BAS_NUM; wIndx ++ )
	{
		ptBasChn = &m_atBasChn[wIndx];

		if ( ptBasChn->m_emChnStat != tagTAudBasChn::Stat_BasChn_Normal )
		{
			continue;
		}

		if ( NULL == ptBasChn->m_pcBasMdl )
		{
			continue;
		}

		if ( ptBasChn->m_pcBasMdl->m_emStat != CAudBasModle::EqpStat_Normal )
		{
			continue;
		}

		return ptBasChn;
	}

	return NULL;
}

TAudBasChn* CAudBasEqp::FindSuitableBasChn( TAudBasParam* ptBasParam )
{
	TAudBasChn* ptBasChn = NULL;
	u8  byIndex = 0;
	u8  byLoop = 0;
	u8  byChanIndex =0;
	u16 wIdelNum = 0;
	u16 wTempNum = TP_INVALID_INDEX;

	if (0 == ptBasParam->m_dwNode)
	{// 第一次来申请，找到最合适的一个适配器外设
		for (byIndex = 0; byIndex < TP_UMS_MAX_AUD_BAS_NUM; byIndex++)
		{
			if (m_atBasMdl[byIndex].m_emStat != CAudBasModle::EqpStat_Normal)
			{
				continue;
			}
			
			for (byLoop = 0; byLoop < AUD_BAS_MAX_CHNL_NUM; byLoop++)
			{
				byChanIndex = byIndex*AUD_BAS_MAX_CHNL_NUM+byLoop;
				
				if (m_atBasChn[byChanIndex].m_emChnStat == tagTAudBasChn::Stat_BasChn_Normal)
				{
					wIdelNum++;
				}
			}
			
			if (wIdelNum >= ptBasParam->m_wReqNum && wIdelNum < wTempNum)
			{
				ptBasParam->m_dwNode = m_atBasMdl[byIndex].m_dwUserNode;
				wTempNum = wIdelNum;
			}
			wIdelNum = 0;
		}
	}
	
	if (0 != ptBasParam->m_dwNode)
	{
		CAudBasModle* pBasModle = FindBasMdl(ptBasParam->m_dwNode);
		if (NULL != pBasModle)
		{
			for (byLoop = 0; byLoop < AUD_BAS_MAX_CHNL_NUM; byLoop++)
			{
				byChanIndex = pBasModle->GetMdlChnBeginIndx()+byLoop;
				if (m_atBasChn[byChanIndex].m_emChnStat == tagTAudBasChn::Stat_BasChn_Normal)
				{
					ptBasChn = &m_atBasChn[byChanIndex];
					break;
				}
			}
		}
	}
	return ptBasChn;
}

CAudBasModle* CAudBasEqp::InsertBas(TTPEqpCfg& tCfg, u32 dwNode)
{
	CHECK_EQP_SEM;

	CAudBasModle* ptMdl = FindBasMdl(tCfg.m_byEqpID);
	if ( NULL != ptMdl )
	{//已经存在 则拒绝
		return NULL;
	}

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_AUD_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].IsIdle() && m_atBasMdl[wMdlIndex].m_emStat == CAudBasModle::EpqStat_OffLine )
		{
			//初始化端口 每个适配器210个端口 总的起始端口为18300
			m_atBasMdl[wMdlIndex].m_wEqpRcvStartPort = UMS_APU2_BAS_START_PORT + (tCfg.m_byEqpID - EQP_ID_AUD_BAS_BEG )*AUD_BAS_MAX_PORT_SPAN;
			m_atBasMdl[wMdlIndex].m_wUmsRcvStartPort = UMS_AUD_BAS_BEGIN_PORT + (tCfg.m_byEqpID - EQP_ID_AUD_BAS_BEG )*AUD_BAS_MAX_PORT_SPAN;

			m_atBasMdl[wMdlIndex].m_emMdlType = tCfg.m_emEqpMdlType;
			m_atBasMdl[wMdlIndex].m_emStat = CAudBasModle::EqpStat_Idle;
			m_atBasMdl[wMdlIndex].m_byEqpID = tCfg.m_byEqpID;

			m_atBasMdl[wMdlIndex].m_dwUserNode = dwNode;
			
			return &m_atBasMdl[wMdlIndex];
		}
	}
	
	return NULL;
}

void CAudBasEqp::DeleteBas( u8 byEqpID )
{
	CHECK_EQP_SEM;

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_AUD_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].m_byEqpID == byEqpID )
		{
			m_atBasMdl[wMdlIndex].m_emMdlType = em_unknow_eqp_mdl;
			m_atBasMdl[wMdlIndex].m_emStat = CAudBasModle::EpqStat_OffLine;
			m_atBasMdl[wMdlIndex].m_byEqpID = 0;
		}
	}
	return ;
}

void CAudBasEqp::CalcEqpUsedStat(TTPBrdUsedInfo& tUsed)
{
	tUsed.m_emType = em_audbas_mdl;

	for ( u16 wMdlIndex = 0; wMdlIndex < TP_UMS_MAX_AUD_BAS_NUM; wMdlIndex ++ )
	{
		if ( m_atBasMdl[wMdlIndex].m_emStat != CAudBasModle::EqpStat_Normal )
		{
			continue;
		}

		tUsed.m_wUsedNum += (u16)m_atBasMdl[wMdlIndex].m_dwUsed;
		tUsed.m_wRegNum ++;
	}
	tUsed.m_wRegNum *= AUD_BAS_MAX_CHNL_NUM;

	return ;
}

void CAudBasEqp::Handle( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	switch(wEvent)
	{
	case ev_AudBasEqpReg_Req:
		OnBasReg(ptMsg);
		break;
	case ev_AudBasEqpStat_Ntfy:
		OnBasStatNtfy(ptMsg);
		break;
	case ev_AudBasChnlStat_Ntfy:
		OnBasChnStatNtfy(ptMsg);
		break;
	case ev_AudBasStartAdapter_Req:
		OnStartAdapter(ptMsg);
		break;
	case ev_AudBasStartAdapter_Ack:
		OnStartAdapterAck(ptMsg);
		break;
	case ev_AudBasStartAdapter_NAck:
		OnStartAdapterNAck(ptMsg);
		break;
	case ev_AudBasStopAdapter_Ack:
		OnStopAdapterAck(ptMsg);
		break;
	case ev_AudBasStopAdapter_NAck:
		OnStopAdapterNAck(ptMsg);
		break;
	case ev_AudBasSetSync_Req:
		OnSetSyncChnl(ptMsg);
		break;

	case ev_AudBas_set_mediakey_ntfy:
		OnSetMediaKey(ptMsg);
		break;

	default:
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		break;
	}	
}

void CAudBasEqp::OnBasReg( CTpMsg *const ptMsg )
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
	CAudBasModle* ptEqpMdl = FindBasMdl(tBasReg.m_byEqpID);
	if ( NULL ==  ptEqpMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasReg. EqpModle is noExist!\n"));
		
		wErrCode = ERR_MCU_NOIDLEEQPSSN;
		SendMsgToEqpSsn( ptMsg->GetSrcIId(), ev_TPBas_Reg_NAck, (u8*)&wErrCode, sizeof(wErrCode));
		return ;
	}
	
	if ( ptEqpMdl->m_emStat != CAudBasModle::EqpStat_Idle )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasReg. BasEntry Stat Invalid! Stat:%s\n", GetBasStatBuf(ptEqpMdl->m_emStat)));
		
		if ( ptEqpMdl->m_emStat == CAudBasModle::EpqStat_OffLine )
		{//外设不在线
			wErrCode = ERR_MCU_EQPOFFLINE;
		}
		else if ( ptEqpMdl->m_emStat == CAudBasModle::EqpStat_Normal )
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

	if ( tBasReg.m_emEqpMdlType != ptEqpMdl->m_emMdlType )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasReg. BasEntry MdlType Invalid! LocalType:%d, RegType:%d\n", 
											ptEqpMdl->m_emMdlType, tBasReg.m_emEqpMdlType));
		wErrCode = ERR_MCU_WRONGEQP;
		SendMsgToEqpSsn( ptMsg->GetSrcIId(), ev_TPBas_Reg_NAck, (u8*)&wErrCode, sizeof(wErrCode));
		return ;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasReg. Bas Reg! EqpID:%d, EqpType:%d, EqpIP:"TPIPFORMAT", RcvStartPort:%d, Ver:%d\n", 
		tBasReg.m_byEqpID, tBasReg.m_emEqpMdlType, Tpu32ToIP(tBasReg.m_dwEqpIPAddr), 
					tBasReg.m_dwEqpPort, tBasReg.m_dwEqpVer));

	ptEqpMdl->m_dwUserNode = wSrcNode;
	ptEqpMdl->m_dwUserInst = wSrcInst;
	
	ptEqpMdl->m_tRegInfo.m_dwEqpIP = tBasReg.m_dwEqpIPAddr;
	ptEqpMdl->m_tRegInfo.m_wVersion = (u16)tBasReg.m_dwEqpVer;
	ptEqpMdl->m_bRegsited = TRUE;
	ptEqpMdl->m_emStat = CAudBasModle::EqpStat_Normal;

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
		tAck.SetAlias("umsaudbas");
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
	
	SendMsgToEqpSsn( wSrcInst, ev_AudBasEqpReg_Ack, abySndBuf, sizeof(abySndBuf));

	return ;
}

void CAudBasEqp::OnBasStatNtfy( CTpMsg *const ptMsg )
{
	TTPBasStatNtfy tStatNtfy;
	TP_SAFE_CAST( tStatNtfy, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasStatNtfy. BasStat Change! EqpID:%d, EqpAlias:%s\n", tStatNtfy.m_byEqpID, tStatNtfy.m_szAlias));
	
	CHECK_EQP_SEM;
	
	CAudBasModle* ptBasMdl = FindBasMdl(tStatNtfy.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasStatNtfy. Eqp:%d no exist!\n", tStatNtfy.m_byEqpID));
		return ;
	}

	ptBasMdl->m_emStat = CAudBasModle::EqpStat_Normal;

	return ;
}

void CAudBasEqp::OnBasChnStatNtfy( CTpMsg *const ptMsg )
{
	TTPBasChnStatNtfy tStatNtfy;
	TP_SAFE_CAST( tStatNtfy, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudBasModle* ptBasMdl = FindBasMdl(tStatNtfy.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasChnStatNtfy. Eqp:%d no exist!\n", tStatNtfy.m_byEqpID));
		return ;
	}

	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tStatNtfy.m_byChnIndx;

	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasChnStatNtfy. BasChnStat Change! ConfID:%d, EqpID:%d, ChnID:%d, NtfyStat:%d (0-idle,1-ready,2-run)\n", 
										m_atBasChn[wChnIndx].m_wConfID, tStatNtfy.m_byEqpID, tStatNtfy.m_byChnIndx, tStatNtfy.m_byStat));


	m_atBasChn[wChnIndx].m_byEqpID = ptBasMdl->m_byEqpID;
	m_atBasChn[wChnIndx].m_byChnID = tStatNtfy.m_byChnIndx;
	m_atBasChn[wChnIndx].m_pcBasMdl = ptBasMdl;

	//更新外设注册状态
	m_pcInst->GetEqpMgr()->UpdateEqpRegState(ptBasMdl->m_dwUserNode, ptBasMdl->m_byEqpID, TRUE);

	//更新板子最新状态
	if ( tStatNtfy.m_byStat == 0 )
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTAudBasChn::Stat_BasChn_Idle;
	}
	else if ( tStatNtfy.m_byStat == 1 )
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTAudBasChn::Stat_BasChn_Normal;
	}
	else if ( tStatNtfy.m_byStat == 2 )
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTAudBasChn::Stat_BasChn_Running;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnBasChnStatNtfy. NtfyStat Invalid! Eqp:%d, ChnIdx:%d, NtfyStat:%d (0-idle,1-ready,2-run)\n", 
									tStatNtfy.m_byEqpID, tStatNtfy.m_byChnIndx, tStatNtfy.m_byStat));
	}

	return ;
}


void CAudBasEqp::OnStartAdapter(CTpMsg *const ptMsg)
{
	TStartAudAdapter tTPStart;
	TP_SAFE_CAST(tTPStart, ptMsg->GetBody());

	if ( tTPStart.m_byChnlIndx >= AUD_BAS_MAX_CHNL_NUM*TP_UMS_MAX_AUD_BAS_NUM )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapter. ChnIndx Invalid! ChnIndx:%d\n", tTPStart.m_byChnlIndx));
		return ;
	}

	CHECK_EQP_SEM;

	TAudBasChn* ptBasChn = &m_atBasChn[tTPStart.m_byChnlIndx];

	TTPBasNAck tNAck;
	tNAck.m_byEqpID = ptBasChn->m_byEqpID;
	tNAck.m_wChnIndx = tTPStart.m_byChnlIndx;

	if ( ptBasChn->m_emChnStat == tagTAudBasChn::Stat_BasChn_Idle ||
		ptBasChn->m_emChnStat == tagTAudBasChn::Stat_BasChn_Normal ||
		 ptBasChn->m_emChnStat == tagTAudBasChn::Stat_BasChn_Error )
	{
		//开启失败 通知call
		SendMsgToCall(GETINS(ptMsg->GetSrcIId()), evtp_UmsBasStart_NAck, (u8*)&tNAck, sizeof(tNAck));

		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapter. BasStat Invalid! ConfID:%d, ChnID:%d, Stat:%s\n", 
													ptBasChn->m_wConfID, ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat)));
		return ;
	}

	if ( NULL == ptBasChn->m_pcBasMdl )
	{
		//开启失败 通知call
		SendMsgToCall(GETINS(ptMsg->GetSrcIId()), evtp_UmsBasStart_NAck, (u8*)&tNAck, sizeof(tNAck));

		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapter. ptBasChn->m_pcBasMdl is NULL! ConfID:%d, ChnID:%d, Stat:%s\n", 
											ptBasChn->m_wConfID, ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat)));
		return ;
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapter. ConfID:%d, ChnIndx:%d, ChnID:%d, Stat:%s, EqpID:%d\n", 
															ptBasChn->m_wConfID, tTPStart.m_byChnlIndx, 
															ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat), 
															ptBasChn->m_pcBasMdl->m_byEqpID));

	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapter. EncryptInfo(%d,%s,%d)\n", tTPStart.m_tEncrypt.m_emEncryptModel, 
		tTPStart.m_tEncrypt.m_achEncKey, tTPStart.m_tEncrypt.m_byKeyLen));

	tTPStart.m_byChnlIndx = ptBasChn->m_byChnID;
	if ( ptBasChn->m_emChnStat == tagTAudBasChn::Stat_BasChn_Reserve )
	{
		ptBasChn->m_emChnStat = tagTAudBasChn::Stat_BasChn_Starting;

		SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_AudBasStartAdapter_Req, (u8*)&tTPStart, sizeof(tTPStart));
	}
	else
	{
		SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_AudBasChangeAdapter_Req, (u8*)&tTPStart, sizeof(tTPStart));
	}

	return ;
}

void CAudBasEqp::OnStartAdapterAck( CTpMsg *const ptMsg )
{
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CAudBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterAck. Eqp:%d no exist!\n", tRetInfo.m_byEqpID));
		return ;
	}

	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}

	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
											m_atBasChn[wChnIndx].m_wConfID,
											tRetInfo.m_byEqpID, wChnIndx, tRetInfo.m_byChnID, 
											GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));

	if(m_atBasChn[wChnIndx].m_emChnStat == tagTAudBasChn::Stat_BasChn_Starting)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTAudBasChn::Stat_BasChn_Running;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterAck. Stat Invalid! ConfID:%d,  wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
											m_atBasChn[wChnIndx].m_wConfID,
											tRetInfo.m_byEqpID, wChnIndx, tRetInfo.m_byChnID, 
											GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}

}

void CAudBasEqp::OnStartAdapterNAck( CTpMsg *const ptMsg )
{// 包括调整适配的回应
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CAudBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterNAck. Eqp:%d no exist!\n", tRetInfo.m_byEqpID));
		return ;
	}
	
	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterNAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}

	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterNAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
								m_atBasChn[wChnIndx].m_wConfID,
								tRetInfo.m_byEqpID, wChnIndx, tRetInfo.m_byChnID, 
								GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	
	if(m_atBasChn[wChnIndx].m_emChnStat == tagTAudBasChn::Stat_BasChn_Starting
		|| m_atBasChn[wChnIndx].m_emChnStat == tagTAudBasChn::Stat_BasChn_Running)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTAudBasChn::Stat_BasChn_Error;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStartAdapterNAck. Stat Invalid! ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n",
										m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, 
										wChnIndx, tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}

	TTPBasNAck tNAck;
	tNAck.m_byEqpID = m_atBasChn[wChnIndx].m_byEqpID;
	tNAck.m_wChnIndx = wChnIndx;
	//开启失败 通知call
	SendMsgToCall( m_atBasChn[wChnIndx].m_wConfID, evtp_UmsBasStart_NAck, (u8*)&tNAck, sizeof(tNAck));
}

void CAudBasEqp::OnStopAdapterAck( CTpMsg *const ptMsg )
{
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CAudBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterAck. Eqp:%d no exist!\n", tRetInfo.m_byEqpID));
		return ;
	}

	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}
	
	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n",
						m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
						tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	
	if(m_atBasChn[wChnIndx].m_emChnStat == tagTAudBasChn::Stat_BasChn_Stoping)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTAudBasChn::Stat_BasChn_Normal;

		m_atBasChn[wChnIndx].m_wConfID = TP_INVALID_INDEX;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterAck. Stat Invalid! ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
							m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
							tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}
}

void CAudBasEqp::OnStopAdapterNAck( CTpMsg *const ptMsg )
{
	TTPBasRetInfo tRetInfo;
	TP_SAFE_CAST( tRetInfo, ptMsg->GetBody());
	
	CHECK_EQP_SEM;

	CAudBasModle* ptBasMdl = FindBasMdl(tRetInfo.m_byEqpID);
	if ( NULL ==  ptBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterNAck. Eqp:%d no exist! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}

	if ( tRetInfo.m_byChnID >= BAS_CHN_MAX_NUM_EHANCED )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterNAck. m_byChnID Invalid! ChnID:%d\n", tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
		return ;
	}
	
	u16	wChnIndx = ptBasMdl->GetMdlChnBeginIndx() + tRetInfo.m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterNAck. ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n", 
					m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
					tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	
	if(m_atBasChn[wChnIndx].m_emChnStat == tagTAudBasChn::Stat_BasChn_Stoping)
	{
		m_atBasChn[wChnIndx].m_emChnStat = tagTAudBasChn::Stat_BasChn_Error;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnStopAdapterNAck. Stat Invalid! ConfID:%d, wEqpID:%d, ChnIndx:%d, ChnID:%d, Stat:%s\n",
						m_atBasChn[wChnIndx].m_wConfID, tRetInfo.m_byEqpID, wChnIndx, 
						tRetInfo.m_byChnID, GetChanStatBuf(m_atBasChn[wChnIndx].m_emChnStat)));
	}	
}

void CAudBasEqp::StopAdatper( TAudBasChn* ptBasChn )
{
	if ( NULL == ptBasChn->m_pcBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::StopAdatper. m_pcBasMdl is NULL! wEqpID:%d, ChnID:%d, Stat:%s\n", 
									ptBasChn->m_byEqpID, ptBasChn->m_byChnID, GetChanStatBuf(ptBasChn->m_emChnStat)));
		return ;
	}

	SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_AudBasStopAdapter_Req, &ptBasChn->m_byChnID, sizeof(ptBasChn->m_byChnID));
}


void CAudBasEqp::ChangeBasMeidaDsIp(TBasSndAddr& tSndAddr)
{
	CAudBasModle* ptModle = FindBasMdl(tSndAddr.m_byEqpID);
	
	MdlLowHint(Ums_Mdl_Eqp, ("CAudBasEqp::ChangeBasMeidaDsIp. EqpID:%d, NewIp:"TPIPFORMAT", CurIP:"TPIPFORMAT"\n", 
		tSndAddr.m_byEqpID, Tpu32ToIP(tSndAddr.m_dwNewDsIP), Tpu32ToIP(ptModle->m_dwMediaIP)));
	
	if(0 == tSndAddr.m_dwNewDsIP || ptModle->m_dwMediaIP == tSndAddr.m_dwNewDsIP)
	{// 转发板ip无效或者新旧ip相同 不需要变更
		return;
	}
	
	ptModle->m_dwMediaIP = tSndAddr.m_dwNewDsIP;
	SendMsgToEqpSsn(ptModle->m_dwUserInst, ev_TPEqp_ChangeSndAddr_Req, (u8*)&tSndAddr, sizeof(tSndAddr));
}

void CAudBasEqp::OnSetSyncChnl( CTpMsg *const ptMsg )
{
	TAudBasSyncChnl tSync;
	TP_SAFE_CAST(tSync, ptMsg->GetBody());
	
	CHECK_EQP_SEM;
	
	CAudBasModle* pcBasMdl = FindBasMdl(tSync.m_byEqpID);
	if ( NULL == pcBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnSetSyncChnl. ptBasChn is NULL! ChnID:%d\n", tSync.m_byEqpID));
		return ;
	}
	
	//转成chnlid
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		if ( tSync.m_abyChanId[wIndex] == 0xFF )
		{
			continue;
		}
		tSync.m_abyChanId[wIndex] = m_atBasChn[tSync.m_abyChanId[wIndex]].m_byChnID;
	}
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnSetSyncChnl. EqpID:%d, Chnl(%d, %d, %d)\n", 
		pcBasMdl->m_byEqpID, 
		tSync.m_abyChanId[0], tSync.m_abyChanId[1], tSync.m_abyChanId[2]));

	SendMsgToEqpSsn(pcBasMdl->m_dwUserInst, ev_AudBasSetSync_Req, (u8*)&tSync, sizeof(tSync));

	return ;
}


void CAudBasEqp::OnSetMediaKey( CTpMsg *const ptMsg )
{
	u8 byEqpID;
	u16 wChnlID;
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(wChnlID, ptMsg->GetBody()+sizeof(u8));
	TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(byEqpID)+sizeof(wChnlID));
	
	CAudBasModle* pcBasMdl = FindBasMdl(byEqpID);
	if ( NULL == pcBasMdl )
	{
		MdlError(Ums_Mdl_Eqp, ("CAudBasEqp::OnSetMediaKey. ptBasChn is NULL! ChnID:%d\n", byEqpID));
		return ;
	}
	
	TAudBasChn* ptBasChn = &m_atBasChn[wChnlID];
	
	//handle 用来携带chnlid
	tInfo.m_dwHandle = ptBasChn->m_byChnID;
	
	MdlHint(Ums_Mdl_Eqp, ("CAudBasEqp::OnSetMediaKey. EqpID:%d, ChnIndx:%d\n", byEqpID, wChnlID));
	
	SendMsgToEqpSsn(ptBasChn->m_pcBasMdl->m_dwUserInst, ev_AudBas_set_mediakey_ntfy, (u8*)&tInfo, sizeof(tInfo));
}



