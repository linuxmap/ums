#include "tpsys.h"
#include "tpstruct.h"
#include "eqpinst.h"
#include "umsueinit.h"
#include "umsconfig.h"
#include "adaptereqp.h"
#include "audiomixeqp.h"
#include "mediatranseqp.h"
#include "netbufeqp.h"
#include "mpceqp.h"
#include "eventtpsys.h"
#include "eventoutumscfg.h"
#include "eventoutumseqp.h"
#include "mcuboardmgr.h"
#include "vmpeqp.h"
#include "hdueqp.h"
#include "audbaseqp.h"
#include "baseqp.h"
#include "umsapi.h"
#include "innereventumshdu.h"
#include "innereventumscall.h"
#include "innereventumsboard.h"
#include "innereventumsmpu2.h"
#include "innereventumsvmp.h"
#include "eventoutumscommonbrd.h"
#include "innereventumsaudiomix.h"
#include "mpu2tpeqp.h"
#include "innereventumsaudbas.h"
#include "mpu2tpeqp.h"
#include "eventoutmpu2tp.h"


CUmsEqpApp g_cUmsEqpApp;
SEMHANDLE g_SemEqpData = NULL;

extern CTPMcuBrdRegApp g_cBrdRegApp;
extern CTPMcuBrdSsnApp g_cBrdSsnApp;

void InitEqpLib()
{
	OspSemBCreate(&g_SemEqpData);
	if (NULL == g_SemEqpData)
	{
		msgprint("InitEqpLib Create m_DataSem failed!\n");
	}

	g_cBrdRegApp.CreateApp("TpMcuBrdRegApp", AID_UMSBRD_REG_APP, 100, 1024);
	g_cBrdSsnApp.CreateApp("TpMcuBrdSsnApp", AID_UMSBRD_SSN_APP, 100, 5120);

	g_cUmsEqpApp.CreateApp("UmsEqpApp",AID_UMSEQP_APP,100, 4096);
	

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );

	cMsg.Post(MAKEIID(AID_UMSBRD_REG_APP, CInstance::DAEMON));
	cMsg.Post(MAKEIID(AID_UMSBRD_SSN_APP, CInstance::DAEMON));
	
	//eqp inst
	cMsg.Post( UMS_EQP_APP_INST );
}

void QuitEqpLib()
{
	if (g_SemEqpData != NULL)
	{	
		OspSemTake(g_SemEqpData);
		OspSemDelete(g_SemEqpData);
		g_SemEqpData = NULL;
	}
}

u32 g_dwEqpSemCheck = 0;
s8* g_pszEqpSemCheckPos = NULL;
u32	g_dwFileLine = 0;
CEqpSem::CEqpSem(s8* pszPos, u32 dwLine)
{
	g_dwEqpSemCheck = 1;
	g_pszEqpSemCheckPos = pszPos;
	g_dwFileLine = dwLine;
	if (g_SemEqpData != NULL)
	{
		OspSemTake(g_SemEqpData);
	}
	else
	{
		msgprint("enter. CEqpSem::g_SemEqpData is null!\n");
	}
}
CEqpSem::~CEqpSem()
{
	g_dwEqpSemCheck = 0; 
	g_pszEqpSemCheckPos = NULL;
	g_dwFileLine = 0;
	if (g_SemEqpData != NULL)
	{
		OspSemGive(g_SemEqpData);
	}
	else
	{
		msgprint("quit. CEqpSem::g_SemEqpData is null!\n");
	}
}

#define _LoadEqp( classname, eqptype )\
	if( NULL == m_atEqpHandle[_##classname].m_pcEqp )\
{\
	m_atEqpHandle[_##classname].m_pcEqp = new classname(this);\
	if( NULL == m_atEqpHandle[_##classname].m_pcEqp )\
{\
	MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ObjectInit malloc %s Failed\n", #classname)); \
	return FALSE;\
}\
	m_atEqpHandle[_##classname].m_emEqpType = eqptype; \
	m_atEqpHandle[_##classname].m_pcEqp->Init(); \
}

CUmsEqpInst::CUmsEqpInst()
{
	for ( u16 wIndex = 0; wIndex < _EqpEnd; wIndex ++ )
	{
		m_atEqpHandle[wIndex].Clear();
	}
	m_wLogModuleId = Ums_Mdl_Eqp;
}

CUmsEqpInst::~CUmsEqpInst()
{
	ObjectExit();
}


BOOL CUmsEqpInst::PreMessageProc ( CMessage *const ptMsg )
{
	if (ptMsg->event == OSP_DISCONNECT)
	{
		OnDisconnect(ptMsg);
		return TRUE;
	}
	return FALSE;
}
void CUmsEqpInst::MessageProc( CTpMsg *const ptMsg)
{
	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();

	switch(wSrcAppID)
	{
	case AID_UMSSIPADAPTER_APP:
		m_atEqpHandle[_CAdapterEqp].m_pcEqp->Handle(ptMsg);
		break;
	case AID_UMSAUDIOMIX_APP:
		m_atEqpHandle[_CAudioMixEqp].m_pcEqp->Handle(ptMsg);
		break;
	case AID_UMSMEDIATRANS_APP:
		m_atEqpHandle[_CMediaTransEqp].m_pcEqp->Handle(ptMsg);
		break;
	case AID_UMSNETBUF_APP:
		m_atEqpHandle[_CNbEqp].m_pcEqp->Handle(ptMsg);
		break;
	case AID_UMSMPC_APP:
		m_atEqpHandle[_CMpcEqp].m_pcEqp->Handle(ptMsg);
		break;
	case AID_MPU2TP_APP:
		m_atEqpHandle[_CMpu2TpEqp].m_pcEqp->Handle(ptMsg);
		break;
	case AID_UMSBRD_SSN_APP:
		BrdSsnMessageProc(ptMsg);
		break;
	case AID_UMSCONFMGR:
		CallMgrMessageProc(ptMsg);
		break;
	case AID_UMSSERVER_APP:
		ServiceMessageProc(ptMsg);
		break;
	default:
		{
			switch(wEvent)
			{
			case ev_UmsSetSysTime_Cmd:
				m_atEqpHandle[_CMpcEqp].m_pcEqp->Handle(ptMsg);
				break;
			//所有板子的注册
			case ev_TPBrdReg_Req:
				OnBrdReg(ptMsg);
				break;
			case ev_TPBrdGetCfg_Req:
				OnBrdGetCfgReq(ptMsg);
				break;
			case ev_TPBrdHDVersion_Ack:
			case ev_TPBrdSoftWareUpdate_Ack:
				OnBrdUpdateAck(ptMsg);
				break;
			case ev_TPBrdSwitchTeltp_Ack:
				m_cEqpMgr.Handle(ptMsg);
				break;
			default:
				MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst MessageProc Unknow MsgSrc:%d, event:%d->%s\n", wSrcAppID, 
															ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
			}
		}
		break;
	}
}

BOOL CUmsEqpInst::ObjectInit(u32 wParam, u32 lParam)
{
	if (m_bInit)
	{
		return TRUE;
	}

	SetLogTitle("CUmsEqpInst");

	_LoadEqp(CAdapterEqp, em_adapter_mdl);
	_LoadEqp(CAudioMixEqp, em_audmix_mdl);
	_LoadEqp(CMediaTransEqp, em_dataswitch_mdl);
	_LoadEqp(CNbEqp, em_netbuf_mdl);
	_LoadEqp(CMpcEqp, em_mpc_mdl);
	_LoadEqp(CVmpEqp, em_vmp_mdl);
	_LoadEqp(CBasEqp, em_bas_mdl);
	_LoadEqp(CHduEqp, em_hdu_mdl);
	_LoadEqp(CAudBasEqp, em_audbas_mdl);
	_LoadEqp(CMpu2TpEqp, em_vmp_tp_mdl);

	m_cEqpMgr.Init(this);

	CTpMsg cMsg;
	cMsg.SetEvent( EVTP_RUNNING );
	cMsg.Post( UMS_SERVICE_APP_INST, 0, UMS_EQP_APP_INST);

	m_bInit = TRUE;	
	return TRUE;
}


void CUmsEqpInst::ObjectExit()
{
	for ( u16 wIndex = 0; wIndex < _EqpEnd; wIndex ++ )
	{
		if ( NULL != m_atEqpHandle[wIndex].m_pcEqp )
		{
			delete m_atEqpHandle[wIndex].m_pcEqp;
		}
		m_atEqpHandle[wIndex].Clear();
	}

	CUmsObject::ObjectExit();
}

CEqpBase* CUmsEqpInst::GetEqp( EMEqpType em )
{
	for ( u16 wIndex = 0; wIndex < _EqpEnd; wIndex ++ )
	{
		if ( m_atEqpHandle[wIndex].m_emEqpType == em )
		{
			return m_atEqpHandle[wIndex].m_pcEqp;
		}
	}

	return NULL;
}

void CUmsEqpInst::OnDisconnect(CMessage *const ptMsg)
{
	u32 dwNode = *(u32*)ptMsg->content;
	ObjHint(("[CUmsEqpInst],OnDisconnect, dwNode->%d \n", dwNode));

	do
	{
		//板子掉线
		EMEqpType emType = m_cEqpMgr.BrdDisConnect(dwNode);
		if(em_unknow_mdl != emType)
		{
			break;
		}

		//业务状态处理
		if (m_atEqpHandle[_CAdapterEqp].m_pcEqp->OnDisConnect(dwNode))
		{
			break;
		}
		if (m_atEqpHandle[_CMediaTransEqp].m_pcEqp->OnDisConnect(dwNode))
		{
			break;
		}
		if (m_atEqpHandle[_CNbEqp].m_pcEqp->OnDisConnect(dwNode))
		{
			break;
		}
		if (m_atEqpHandle[_CMpcEqp].m_pcEqp->OnDisConnect(dwNode))
		{
			break;
		}
		if (m_atEqpHandle[_CHduEqp].m_pcEqp->OnDisConnect(dwNode))
		{
			break;
		}

		ObjError(("[CUmsEqpInst],OnDisconnect error, dwNode->%d \n", dwNode));

	}while(0);
}


u16 CUmsEqpInst::NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	
	if (NULL != body)
	{
		cMsg.CatBody(body,bodyLen);
	}
	
	return cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

BOOL32 CUmsEqpInst::AssignEqpEx(  TEqpParam* ptEqpParam )
{
	BOOL32 bRet = FALSE;
	CEqpBase* ptEqp = GetEqp(ptEqpParam->m_emEqpType);
	if ( NULL != ptEqp )
	{
		bRet = ptEqp->AssignEqpEx(ptEqpParam);
	}

	return bRet;
}

BOOL32 CUmsEqpInst::AssignEqpByNodeEx( TEqpParam* ptEqpParam  )
{
	BOOL32 bRet = FALSE;
	CEqpBase* ptEqp = GetEqp(ptEqpParam->m_emEqpType);
	if ( NULL != ptEqp )
	{
		bRet = ptEqp->AssignEqpByEqpEx(ptEqpParam);
	}

	return bRet;
}

BOOL32 CUmsEqpInst::ReleaseEqpEx(  TEqpParam* ptEqpParam )
{
	BOOL32 bRet = FALSE;
	CEqpBase* ptEqp = GetEqp(ptEqpParam->m_emEqpType);
	if ( NULL != ptEqp )
	{
		bRet = ptEqp->ReleaseEqpEx(ptEqpParam);
	}

	return bRet;
}

BOOL32 CUmsEqpInst::GetAllEqpResEx(  TEqpRes* pcEqpRes, u16 wEqpNum,  EMEqpType emEqpType)
{
	BOOL32 bRet = FALSE;
	CEqpBase* ptEqp = GetEqp(emEqpType);
	if ( NULL != ptEqp )
	{
		bRet = ptEqp->GetAllEqpRes(pcEqpRes, wEqpNum);
	}
	
	return bRet;
}

void CUmsEqpInst::CallMgrMessageProc( CTpMsg *const ptMsg )
{
	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();
	
// 	if (wEvent > segment_begin(umsinnerrec) && wEvent < segment_end(umsinnerrec))
// 	{
// 		m_atEqpHandle[_CRecorderEqp].m_pcEqp->Handle(ptMsg);
// 		return ;
// 	}

	switch(wEvent)
	{
	case ev_TPEqp_ChangeSndAddr_Req:
		OnChangeEqpSndAddr(ptMsg);
		break;
	case ev_TPVmp_FastUpdate_Req:
	case ev_TPVmp_StartStopChn_Req:
	case evtp_StartVmp_Req:
	case evtp_AdjustVmp_Req:
	case ev_TPVmp_SetMediaKey_Req:
		m_atEqpHandle[_CVmpEqp].m_pcEqp->Handle(ptMsg);
		break;
	case ev_TPBas_StartAdapter_Req:
	case evtp_UmsBasAskFrame_Req:
    case ev_TPBas_SetMediaKey_Req:
		m_atEqpHandle[_CBasEqp].m_pcEqp->Handle(ptMsg);
		break;
	case ev_mpu2tp_AskFrame_Req:
		m_atEqpHandle[_CMpu2TpEqp].m_pcEqp->Handle(ptMsg);
		break;
	default:
		{
			if ( wEvent > segment_begin(innerumsaudiomix)  && wEvent < segment_end(innerumsaudiomix) )
			{
				m_atEqpHandle[_CAudioMixEqp].m_pcEqp->Handle(ptMsg);
			}
			else if ( wEvent > segment_begin(innerumsaudbas)  && wEvent < segment_end(innerumsaudbas) )
			{
				m_atEqpHandle[_CAudBasEqp].m_pcEqp->Handle(ptMsg);
			}
			else if (wEvent > segment_begin(umsinnervmp)  && wEvent < segment_end(umsinnervmp))
			{
				m_atEqpHandle[_CMpu2TpEqp].m_pcEqp->Handle(ptMsg);
			}
			else
			{
				MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::CallMgrMessageProc. unknow msg! SrcAppID:%d, event:%d->%s\n", 
					wSrcAppID, wEvent, GetEventNamebyID(wEvent)));
			}
		}
		break;
	}
	return ;	
}

void CUmsEqpInst::BrdSsnMessageProc( CTpMsg *const ptMsg )
{
	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();

	if (wEvent > segment_begin(umsinnerhdu) && wEvent < segment_end(umsinnerhdu))
	{
		m_atEqpHandle[_CHduEqp].m_pcEqp->Handle(ptMsg);
	}
	else if( wEvent > ev_TPVmp_Begin && wEvent < ev_TPVmp_End )
	{
		m_atEqpHandle[_CVmpEqp].m_pcEqp->Handle(ptMsg);
	}
	else if( wEvent > ev_TPBas_Begin && wEvent < ev_TPBas_End )
	{
		m_atEqpHandle[_CBasEqp].m_pcEqp->Handle(ptMsg);
	}
// 	else if (wEvent > segment_begin(umsinnerrec) && wEvent < segment_end(umsinnerrec))
// 	{
// 		m_atEqpHandle[_CRecorderEqp].m_pcEqp->Handle(ptMsg);
// 	}
	else if ( wEvent > segment_begin(innerumsaudiomix) && wEvent < segment_end(innerumsaudiomix) )
	{
		m_atEqpHandle[_CAudioMixEqp].m_pcEqp->Handle(ptMsg);
	}
	else if ( wEvent > segment_begin(innerumsaudbas) && wEvent < segment_end(innerumsaudbas) )
	{
		m_atEqpHandle[_CAudBasEqp].m_pcEqp->Handle(ptMsg);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::BrdSsnMessageProc. unknow msg! SrcAppID:%d, event:%d->%s\n", 
								wSrcAppID, wEvent, GetEventNamebyID(wEvent)));
	}

	return ;
}

void CUmsEqpInst::ServiceMessageProc(CTpMsg *const ptMsg)
{
	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();

	if (wEvent > segment_begin(umsinnerhdu) && wEvent < segment_end(umsinnerhdu))
	{
		m_atEqpHandle[_CHduEqp].m_pcEqp->Handle(ptMsg);
	}
	else if (wEvent > segment_begin(umsinnerboard) && wEvent < segment_end(umsinnerboard))
	{
		m_cEqpMgr.Handle(ptMsg);
	}
// 	else if (wEvent > segment_begin(umsinnerrec) && wEvent < segment_end(umsinnerrec))
// 	{
// 		m_atEqpHandle[_CRecorderEqp].m_pcEqp->Handle(ptMsg);
// 	}
	else if (wEvent == ev_UmsSetSysTime_Cmd)
	{
		m_atEqpHandle[_CMpcEqp].m_pcEqp->Handle(ptMsg);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ServiceMessageProc. unknow msg! SrcAppID:%d, event:%d->%s\n", 
								wSrcAppID, wEvent, GetEventNamebyID(wEvent)));
	}

	return ;
}

void CUmsEqpInst::OnBrdReg( CTpMsg *const ptMsg )
{
	TTPBrdRegInfo* ptBrdRegInfo = (TTPBrdRegInfo*)ptMsg->GetBody();

	//电视墙
	if (ptBrdRegInfo->m_tBrdPos.m_emBrdType == em_hdu2_brd)
	{
		CTpMsg cMsg;
		if (m_atEqpHandle[_CHduEqp].m_pcEqp != NULL)
		{
			if (((CHduEqp*)m_atEqpHandle[_CHduEqp].m_pcEqp)->CheckBrdInfo(*ptBrdRegInfo, ptMsg->GetSrcNode(), ptMsg->GetSrcIId()))
			{
				OspNodeDiscCBRegQ(ptMsg->GetSrcNode(), AID_UMSEQP_APP, EQP_SERVER_INST);

				cMsg.SetEvent(ev_TPBrdReg_Ack);
			}
			else
			{
				cMsg.SetEvent(ev_TPBrdReg_NAck);
			}
		}
		else
		{
			cMsg.SetEvent(ev_TPBrdReg_NAck);
			MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdReg. Hdu Eqp is NULL.\n"));
		}

		cMsg.Post(ptMsg->GetSrcIId(), 0, UMS_EQP_APP_INST);

		return ;
	}

	//其他板子
	if ( m_cEqpMgr.CheckBrdInfo(ptBrdRegInfo, ptMsg->GetSrcNode(), ptMsg->GetSrcIId()) )
	{
		::OspSetHBParam(ptMsg->GetSrcNode(), 3, 2);

		OspNodeDiscCBRegQ(ptMsg->GetSrcNode(), AID_UMSEQP_APP, EQP_SERVER_INST);

		SendToBrd(ptBrdRegInfo->m_tBrdPos.m_emBrdType, ev_TPBrdReg_Ack, ptMsg->GetSrcIId(), ptMsg->GetSrcNode());
		
		MdlHint(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdReg. Brd Check Success! Board<BrdType:%d,Layer:%d,Slot:%d>, Ip:"TPIPFORMAT"\n", 
							   ptBrdRegInfo->m_tBrdPos.m_emBrdType, ptBrdRegInfo->m_tBrdPos.m_byBrdLayer, ptBrdRegInfo->m_tBrdPos.m_byBrdSlot,
							   Tpu32ToIP(ptBrdRegInfo->m_tBrdPos.m_dwBrdIP)));

		//版本请求
		SendToBrd(ptBrdRegInfo->m_tBrdPos.m_emBrdType, ev_TPBrdHDVersion_Req, ptMsg->GetSrcIId(), ptMsg->GetSrcNode());
		
		if ( IsUmsBrd(ptBrdRegInfo->m_tBrdPos.m_emBrdType) )
		{//向板子更新时间
			if ( ptBrdRegInfo->m_tBrdPos.m_emBrdType != em_mpc_brd )
			{//mpc不更新
				TTPTime tTime;
				TPGetSysTime(tTime);
				SendToBrd(ptBrdRegInfo->m_tBrdPos.m_emBrdType, ev_TPBrdSetSysTime_Cmd, 
								ptMsg->GetSrcIId(), ptMsg->GetSrcNode(), &tTime, sizeof(tTime));
			}
		}
	}
	else
	{
		SendToBrd(ptBrdRegInfo->m_tBrdPos.m_emBrdType, ev_TPBrdReg_NAck, ptMsg->GetSrcIId(), ptMsg->GetSrcNode());

		MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdReg. Brd Check Error! Board<BrdType:%d,Layer:%d,Slot:%d>, Ip:"TPIPFORMAT"\n", 
			ptBrdRegInfo->m_tBrdPos.m_emBrdType, ptBrdRegInfo->m_tBrdPos.m_byBrdLayer, ptBrdRegInfo->m_tBrdPos.m_byBrdSlot,
				Tpu32ToIP(ptBrdRegInfo->m_tBrdPos.m_dwBrdIP)));
	}

	return ;
}

void CUmsEqpInst::OnBrdGetCfgReq( CTpMsg *const ptMsg )
{
	TTPBrdPos tBrdPos;
	TP_SAFE_CAST(tBrdPos, ptMsg->GetBody());

	//TODO 根据不同的板子获得不同的外设  可以重构
	do 
	{
		u8 abyBuffer[512] = {0};
		//电视墙处理
		if (tBrdPos.m_emBrdType == em_hdu2_brd)
		{
			u8 byHduVer = STARTMODE_HDU2_S;
			if (!((CHduEqp*)m_atEqpHandle[_CHduEqp].m_pcEqp)->GetHduVer(tBrdPos, byHduVer))
			{
				MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdGetCfgReq The brd is not find. Layer:%d, Slot:%d.\n",
										tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot));
			}
			else
			{
				//电视墙 从 1开始
				u8	byEqpID = EQP_ID_HDU_BEG;
				
				THduCfgAck tHduAck;
				tHduAck.SetStartMoe(byHduVer);
				tHduAck.m_byEqpID = byEqpID + (tBrdPos.m_byBrdLayer * HDU_MAX_SLOT + tBrdPos.m_byBrdSlot);
				
				memcpy(abyBuffer, &(tBrdPos.m_emBrdType), sizeof(EMBrdType));
				memcpy(abyBuffer+sizeof(EMBrdType), &tHduAck, sizeof(THduCfgAck));
				
				CTpMsg cMsg;
				cMsg.SetEvent(ev_TPMcuBrdGetCfg_Ack);
				cMsg.SetBody(abyBuffer, sizeof(abyBuffer));
				cMsg.Post(ptMsg->GetSrcIId(), 0, UMS_EQP_APP_INST);
				
				((CHduEqp*)m_atEqpHandle[_CHduEqp].m_pcEqp)->SetBrdEqpID(tBrdPos.m_byBrdLayer, 
																		 tBrdPos.m_byBrdSlot,
																		 tHduAck.m_byEqpID);

				MdlHint(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdGetCfgReq Hdu brd get cfg. Layer:%d, Slot:%d.\n",
									   tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot));
				return;
			}
			break;
		}

		//电视墙以外其他板子统一处理
		TBrdEntry* ptBrdEntry = m_cEqpMgr.GetBrdCfg(tBrdPos);

		if ( ptBrdEntry == NULL )
		{
			MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdGetCfgReq Brd no exist! Ip:"TPIPFORMAT"\n", Tpu32ToIP(tBrdPos.m_dwBrdIP)));
			break;
		}

		if ( !ptBrdEntry->m_bBrdState )
		{
			MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdGetCfgReq Brd offline! Ip:"TPIPFORMAT", BrdID:%d\n", 
								Tpu32ToIP(tBrdPos.m_dwBrdIP), 
								ptBrdEntry->m_tBrdCfg.m_byBrdID));
			break;
		}

		//外设未配置
		if ( 0 == ptBrdEntry->m_byEqpNum )
		{
			MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdGetCfgReq Eqp no exist! BrdID:%d, BrdUsed:%d, EqpNum:%d\n", 
								ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum));
			break ;
		}

		if ( ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType == em_mpu2ecard_brd
			|| ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType == em_mpu2basic_brd )
		{
			memcpy(abyBuffer, &ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType, sizeof(EMBrdType));
			
			if ( !ProcMpu2GetCfg(ptBrdEntry, abyBuffer) )
			{
				break;
			}
		}
		else if (em_mpc_brd == ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			memcpy(abyBuffer, &ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType, sizeof(EMBrdType));
			memcpy(abyBuffer + sizeof(EMBrdType), &ptBrdEntry->m_atEqpCfg[0].m_emEqpType, sizeof(EMEqpType));
		}
		else if (em_eapu_brd == ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType ||
				em_apu2_tp_brd == ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			memcpy(abyBuffer, &ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType, sizeof(EMBrdType));

			if ( !ProcApu2GetCfg(ptBrdEntry, abyBuffer) )
			{
				break;
			}
		}
		else if (em_cri2_brd == ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			memcpy(abyBuffer, &ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType, sizeof(EMBrdType));
			memcpy(abyBuffer + sizeof(EMBrdType), &ptBrdEntry->m_atEqpCfg[0].m_emEqpType, sizeof(EMEqpType));
		}
		else if (em_mpu2_tp_brd == ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			EMEqpType emType = em_vmp_tp_mdl;
			memcpy(abyBuffer, &ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType, sizeof(EMBrdType));
			memcpy(abyBuffer + sizeof(EMBrdType), &emType, sizeof(emType));;
		}
		else if (em_is22_brd == ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			memcpy(abyBuffer, &ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType, sizeof(EMBrdType));
			memcpy(abyBuffer + sizeof(EMBrdType), &ptBrdEntry->m_atEqpCfg[0].m_emEqpType, sizeof(EMEqpType));
		}
		else
		{
			MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdGetCfgReq Brd Type Invalid! BrdID:%d, BrdUsed:%d, EqpNum:%d\n", 
				ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum));
			break;
		}

		SendToBrd(ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType, 
					ev_TPMcuBrdGetCfg_Ack, ptMsg->GetSrcIId(), ptMsg->GetSrcNode(), abyBuffer, sizeof(abyBuffer));

		MdlHint(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdGetCfgReq. Ip:"TPIPFORMAT", BrdID:%d, Stat:%d(1-Online, 0-Offline), EqpID:(%d,%d)\n", 
												Tpu32ToIP(tBrdPos.m_dwBrdIP), ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bBrdState,
												ptBrdEntry->m_atEqpCfg[0].m_byEqpID, ptBrdEntry->m_atEqpCfg[1].m_byEqpID));

		return ;

	} while (0);

	SendToBrd(tBrdPos.m_emBrdType, ev_TPBrdGetCfg_NAck, ptMsg->GetSrcIId(), ptMsg->GetSrcNode());

	return ;
}

BOOL32 CUmsEqpInst::ProcApu2GetCfg( TBrdEntry* ptBrdEntry, u8* abyBuffer )
{
	TTPApu2CfgAck tApu2Cfg;
	tApu2Cfg.m_emType = ptBrdEntry->m_tBrdCfg.m_tBrdPos.m_emBrdType;
	
	u16 wOffSet = 0;
	CAudioMixModle* pcMixMdl = NULL;
	CAudBasModle* pcAudBasMdl = NULL;
	
	for ( u16 wIndx = 0; wIndx < ptBrdEntry->m_byEqpNum; wIndx ++ )
	{
		if(ptBrdEntry->m_atEqpCfg[wIndx].m_emEqpType == em_audmix_mdl )
		{
			if ( ptBrdEntry->m_atEqpCfg[wIndx].m_byAudmixNum <= 1 )
			{//此处要判断当前外设的通道数量 如果配置了0，则认为一个外设
				continue ;
			}
			pcMixMdl = ((CAudioMixEqp*)m_atEqpHandle[_CAudioMixEqp].m_pcEqp)->InsertMix( ptBrdEntry->m_atEqpCfg[wIndx], 
				ptBrdEntry->m_dwBrdNode, wOffSet );
			
			if ( NULL == pcMixMdl )
			{
				MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ProcApu2GetCfg MixEqp Full! BrdID:%d, BrdUsed:%d, EqpNum:%d, EqpType:%d\n", 
					ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum, ptBrdEntry->m_atEqpCfg[wIndx].m_emEqpType));
				break ;
			}
			
			tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_byEqpId = pcMixMdl->m_byEqpID;
			tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_wEqpRcvStartPort = pcMixMdl->m_wEqpRcvStartPort;
			//Apu2会偏移到通道的最后一个位置，为了节省端口，此处，先进行反方向偏移
			tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_wUmsRcvStartPort = pcMixMdl->m_wUmsRcvStartPort - pcMixMdl->m_wChanNum*UMS_MCU_PORT_PORTSPAN;
			tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_byChanNum = ptBrdEntry->m_atEqpCfg[wIndx].m_byAudmixNum;
		}
		else
		{
			pcAudBasMdl = ((CAudBasEqp*)m_atEqpHandle[_CAudBasEqp].m_pcEqp)->InsertBas( ptBrdEntry->m_atEqpCfg[wIndx], 
				ptBrdEntry->m_dwBrdNode );
			
			if ( NULL == pcAudBasMdl )
			{
				MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ProcApu2GetCfg AudBasEqp Full! BrdID:%d, BrdUsed:%d, EqpNum:%d, EqpType:%d\n", 
					ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum, ptBrdEntry->m_atEqpCfg[wIndx].m_emEqpType));
				break ;
			}
			
			tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_byEqpId = pcAudBasMdl->m_byEqpID;
			tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_wEqpRcvStartPort = pcAudBasMdl->m_wEqpRcvStartPort;
			tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_wUmsRcvStartPort = pcAudBasMdl->m_wUmsRcvStartPort;
		}
		
		tApu2Cfg.m_atInfo[tApu2Cfg.m_byEqpNum].m_emEqpType = ptBrdEntry->m_atEqpCfg[wIndx].m_emEqpType;
		
		tApu2Cfg.m_byEqpNum ++;
		wOffSet += ptBrdEntry->m_atEqpCfg[wIndx].m_byAudmixNum;
	}
	
	if( tApu2Cfg.m_byEqpNum < 1 )
	{
		return FALSE;
	}

	memcpy(abyBuffer + sizeof(EMBrdType), &tApu2Cfg, sizeof(tApu2Cfg));

	return TRUE;
}

BOOL32 CUmsEqpInst::ProcMpu2GetCfg( TBrdEntry* ptBrdEntry, u8* abyBuffer )
{
	TTPMpu2CfgAck tAck;
	tAck.m_byEqpMdlType = ptBrdEntry->m_atEqpCfg[0].m_emEqpMdlType;
	
	//合成器
	if ( ptBrdEntry->m_atEqpCfg[0].m_emEqpType == em_vmp_mdl)
	{
		//给配置的外设 分配位置和资源
		CVmpModle* pcVmpMdl = ((CVmpEqp*)m_atEqpHandle[_CVmpEqp].m_pcEqp)->InsertVmp( ptBrdEntry->m_atEqpCfg[0], ptBrdEntry->m_dwBrdNode );
		if ( NULL == pcVmpMdl )
		{
			MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ProcMpu2GetCfg Vmp Full! BrdID:%d, BrdUsed:%d, EqpNum:%d, EqpType:%d\n", 
				ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum, ptBrdEntry->m_atEqpCfg[0].m_emEqpType));
			return FALSE;
		}
		
		tAck.m_byEqpId = pcVmpMdl->m_byEqpID;
		tAck.m_wEqpRcvStartPort = pcVmpMdl->m_wEqpRcvStartPort;

		//多个外设
		if ( ptBrdEntry->m_byEqpNum > 1 )
		{
			CVmpModle* pcVmpMdl2 = ((CVmpEqp*)m_atEqpHandle[_CVmpEqp].m_pcEqp)->InsertVmp( ptBrdEntry->m_atEqpCfg[1], ptBrdEntry->m_dwBrdNode );
			if ( NULL == pcVmpMdl2 )
			{
				MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ProcMpu2GetCfg Vmp2 Full! BrdID:%d, BrdUsed:%d, EqpNum:%d, EqpType:%d\n", 
					ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum, ptBrdEntry->m_atEqpCfg[1].m_emEqpType));
				
				//释放第一个分配的
				((CVmpEqp*)m_atEqpHandle[_CVmpEqp].m_pcEqp)->DeleteVmp(pcVmpMdl->m_byEqpID);

				return FALSE;
			}

			tAck.m_byEqpId2 = pcVmpMdl2->m_byEqpID;
			tAck.m_wEqpRcvStartPort2 = pcVmpMdl2->m_wEqpRcvStartPort;
		}
	}
	else if ( ptBrdEntry->m_atEqpCfg[0].m_emEqpType == em_bas_mdl )
	{
		CBasModle* pcBasMdl = ((CBasEqp*)m_atEqpHandle[_CBasEqp].m_pcEqp)->InsertBas( ptBrdEntry->m_atEqpCfg[0], ptBrdEntry->m_dwBrdNode );
		if ( NULL == pcBasMdl )
		{
			MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ProcMpu2GetCfg Bas Full! BrdID:%d, BrdUsed:%d, EqpNum:%d, EqpType:%d\n", 
				ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum, ptBrdEntry->m_atEqpCfg[0].m_emEqpType));
			return FALSE;
		}

		tAck.m_byEqpId = pcBasMdl->m_byEqpID;
		tAck.m_wEqpRcvStartPort = pcBasMdl->m_wEqpRcvStartPort;

		//多个外设
		if ( ptBrdEntry->m_byEqpNum > 1 )
		{
			CBasModle* pcBasMdl2 = ((CBasEqp*)m_atEqpHandle[_CBasEqp].m_pcEqp)->InsertBas( ptBrdEntry->m_atEqpCfg[1], ptBrdEntry->m_dwBrdNode );
			if ( NULL == pcBasMdl2 )
			{
				MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ProcMpu2GetCfg Bas2 Full! BrdID:%d, BrdUsed:%d, EqpNum:%d, EqpType:%d\n", 
					ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum, ptBrdEntry->m_atEqpCfg[1].m_emEqpType));
				
				//释放第一个分配的
				((CBasEqp*)m_atEqpHandle[_CBasEqp].m_pcEqp)->DeleteBas(pcBasMdl->m_byEqpID);
				
				return FALSE;
			}
			
			tAck.m_byEqpId2 = pcBasMdl2->m_byEqpID;
			tAck.m_wEqpRcvStartPort2 = pcBasMdl2->m_wEqpRcvStartPort;
		}
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CUmsEqpInst::ProcMpu2GetCfg Eqp Type Invalid! BrdID:%d, BrdUsed:%d, EqpNum:%d, EqpType:%d\n", 
			ptBrdEntry->m_tBrdCfg.m_byBrdID, ptBrdEntry->m_bUsed, ptBrdEntry->m_byEqpNum, ptBrdEntry->m_atEqpCfg[0].m_emEqpType));
		return FALSE;
	}

	memcpy(abyBuffer+sizeof(EMBrdType), &tAck, sizeof(tAck));

	return TRUE;
}


void CUmsEqpInst::OnChangeEqpSndAddr( CTpMsg *const ptMsg )
{
	TBasSndAddr tSndAddr;
	TP_SAFE_CAST(tSndAddr, ptMsg->GetBody());

	TTPEqpCfg* ptEqp = m_cEqpMgr.GetEqpCfgByEqpID(tSndAddr.m_byEqpID);
	if (NULL != ptEqp && em_bas_mdl == ptEqp->m_emEqpType)
	{
		((CBasEqp*)(m_atEqpHandle[_CBasEqp].m_pcEqp))->ChangeBasMeidaDsIp(tSndAddr);
		return;
	}
	else if (NULL != ptEqp && em_audbas_mdl == ptEqp->m_emEqpType)
	{
		((CAudBasEqp*)(m_atEqpHandle[_CAudBasEqp].m_pcEqp))->ChangeBasMeidaDsIp(tSndAddr);
		return;
	}
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPEqp_ChangeSndAddr_Req);
	cMsg.SetBody(&tSndAddr, sizeof(tSndAddr));
	cMsg.Post(MAKEIID(AID_UMSBRD_SSN_APP, tSndAddr.m_byEqpID), 0, MAKEIID(AID_UMSEQP_APP, CInstance::DAEMON));

	return ;
}

void CUmsEqpInst::OnBrdUpdateAck(CTpMsg *const ptMsg)
{
	BOOL32 bRes;
	TP_SAFE_CAST(bRes, ptMsg->GetBody());

	u8 byInstId = (u8)ptMsg->GetSrcIId();
	MdlHint(Ums_Mdl_Eqp, ("CUmsEqpInst::OnBrdUpdateAck update res:%d, instId:%d\n", bRes, byInstId));

	u16 wTemp = AID_UMSBRD_REG_APP;
	u16 wTempb = GETAPP(ptMsg->GetSrcIId());

	if (AID_UMSBRD_REG_APP == GETAPP(ptMsg->GetSrcIId()) && byInstId > 0 && byInstId <= HDU_MAX_NUM)
	{//电视墙
		if (m_atEqpHandle[_CHduEqp].m_pcEqp != NULL)
		{
			((CHduEqp*)m_atEqpHandle[_CHduEqp].m_pcEqp)->Handle(ptMsg);	
		}
	}
	else
	{//其它板子
		m_cEqpMgr.Handle(ptMsg);
	}
	
}

void CUmsEqpInst::SendToBrd(EMBrdType emBrdType, u16 wEvent, u32 dwDstIID, u32 dwNode, void* pbyBody, u16 wLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if (NULL != pbyBody)
	{
		cMsg.SetBody(pbyBody, wLen);
	}

	if (!IsUmsBrd(emBrdType))
	{
		cMsg.Post(dwDstIID, 0, UMS_EQP_APP_INST);
	}
	else
	{
		cMsg.Post(dwDstIID, dwNode, UMS_EQP_APP_INST);
	}
}

BOOL32 CUmsEqpInst::IsUmsBrd(EMBrdType emBrdType)
{
	if ( em_mpu2ecard_brd == emBrdType || em_mpu2basic_brd == emBrdType || em_hdu2_brd == emBrdType ||
		 em_apu2_tp_brd == emBrdType || em_hdu2_qt_brd == emBrdType)
	{
		return FALSE;
	}
	return TRUE;
}

void CUmsEqpInst::InstanceDump(u32 wParam)
{
	if ( wParam == CUmsEqpInst::_EqpEnd )
	{
		ShowEqp();
		return ;
	}

	CEqpBase* ptEqp = GetEqp((CUmsEqpInst::EmEqpHandle)wParam);
	if ( NULL != ptEqp )
	{
		ptEqp->Show();
	}
	if (wParam == CUmsEqpInst::_EqpEnd + 1)
	{
		m_cEqpMgr.ShowBrdInfo();
	}
}

void CUmsEqpInst::ShowEqp()
{
	for ( u16 wIndex = 0; wIndex < _EqpEnd; wIndex ++ )
	{
		if ( m_atEqpHandle[wIndex].m_pcEqp == NULL )
		{
			continue;
		}

		m_atEqpHandle[wIndex].m_pcEqp->Show();
	}
}

API void showeqp()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_EqpEnd);
}

API void showbas()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CBasEqp);
}

API void showumsvmp()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CVmpEqp);
}

API void showeapu()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CAudioMixEqp);
}

API void showaudbas()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CAudBasEqp);
}

API void showsip()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CAdapterEqp);
}

API void showmedia()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CMediaTransEqp);
}

API void showhdu2()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CHduEqp);
}

API void shownb()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CNbEqp);
}

API void showmpc()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_CMpcEqp);
}

API void showbrd()
{
	OspInstDump(AID_UMSEQP_APP, 1, CUmsEqpInst::_EqpEnd + 1);
}

API void showeqpsem()
{
	msgprint("g_dwEqpSemCheck = %d\n", g_dwEqpSemCheck);
	msgprint("g_dwFileLine = %d\n", g_dwFileLine);
	if (NULL == g_pszEqpSemCheckPos)
	{
		msgprint("g_pszEqpSemCheckPos is null\n");
	}
	else
	{
		msgprint("g_pszEqpSemCheckPos is %s\n", g_pszEqpSemCheckPos);
	}
}

API void eqphelp()
{
	msgprintnotime("eqpver()                       --  eqpver\n");
	msgprintnotime("showeqp()                      --  显示外设注册请求信息\n");
	msgprintnotime("showeqpsem()                   --  显示保护锁的位置和状态\n");
	msgprintnotime("showbrd()                      --  显示eqp侧板子信息.\n");
	msgprintnotime("\n");
	msgprintnotime("showbas()                      --  显示适配外设信息\n");
	msgprintnotime("showumsvmp()                      --  显示合成外设信息\n");
	msgprintnotime("showeapu()                     --  显示混音器外设信息\n");
	msgprintnotime("showaudbas()                   --  显示音频适配外设信息\n");
	msgprintnotime("showsip()                      --  显示接入外设信息\n");
	msgprintnotime("showmedia()                    --  显示转发外设信息\n");
	msgprintnotime("shownb()                       --  显示重传外设信息\n");
	msgprintnotime("showmpc()                      --  显示主备外设信息\n");
	msgprintnotime("showhdu2()                     --  显示电视墙外设信息\n");
}

#define  VER_umseqp_ver UMS_VerID
API void eqpver()
{
	msgprint("eqpver ver: %s  compile time: %s:%s\n",
		VER_umseqp_ver, __DATE__,  __TIME__);
}

void regist_ums_eqp_commond()
{
#ifdef _LINUX_
	OspRegCommand("eqphelp", (void*)eqphelp, "eqphelp()");
	OspRegCommand("eqpver", (void*)eqpver, "eqpver(int)");
	OspRegCommand("showeqp", (void*)showeqp, "showeqp(int)");
	OspRegCommand("showeqpsem", (void*)showeqpsem, "showeqpsem(int)");
	OspRegCommand("showbrd", (void*)showbrd, "showbrd()");

	OspRegCommand("showbas", (void*)showbas, "showbas(int)");
	OspRegCommand("showumsvmp", (void*)showumsvmp, "showumsvmp(int)");
	OspRegCommand("showeapu", (void*)showeapu, "showeapu(int)");
	OspRegCommand("showaudbas", (void*)showaudbas, "showaudbas(int)");
	OspRegCommand("showsip", (void*)showsip, "showsip(int)");
	OspRegCommand("showmedia", (void*)showmedia, "showmedia(int)");
	OspRegCommand("shownb", (void*)shownb, "shownb(int)");
	OspRegCommand("showmpc", (void*)showmpc, "showmpc(int)");
	OspRegCommand("showhdu2", (void*)showhdu2, "showhdu2(int)");

#endif
}


 