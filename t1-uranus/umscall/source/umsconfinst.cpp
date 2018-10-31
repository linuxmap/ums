
#include "umsconfinst.h"
#include "eventtpsys.h"
#include "innereventregsrv.h"
#include "innereventumscall.h"
#include "innereventumsconf.h"
#include "innereventumsserver.h"
#include "innereventtvwall.h"
#include "innereventumshdu.h"
#include "eventoutumscall.h"
#include "eventoutumscfg.h"
#include "eventoutsipadapter.h"
#include "eventoutumsmediatrans.h"
#include "eventoutumstool.h"
#include "eventoutumsmcucasecade.h"
#include "umsstackinterface.h"
#include "umscallinit.h"
#include "umsnetportmgr.h"
#include "callnodemgr.h"
#include "umseapu.h"
#include "umsvmp.h"
#include "umsbas.h"
#include "umsreg.h"
#include "tvwallmgr.h"
#include "umsconfig.h"
#include "umsconfigex.h"
#include "callmgr.h"
#include "dualmgr.h"
#include "eqpinterface.h"
#include "getvidaud.h"
#include "tperrno.h"
#include "umsapi.h"
#include "nodefsm.h"
#include "umsdiscussnew.h"
#include "vmpserviecehandler.h"
#include "selviewmgr.h"
#include "pollmgr.h"
#include "eventoutumsbrdvmp.h"
#include "dataconfhandler.h"
#include "umsaudmix.h"
#include "umsgetconfvidaud.h"
#include "umsmcumgr.h"

#include "eventoutquantum.h"
#include "tpcommonstruct.h"
#include "innereventxmpuvmp.h"
#include "jdconfig.h"

#define MAX_POLL_CHANNEL_NUM (5 * TP_MAX_STREAMNUM)
#define MAX_ROLL_CHANNEL_NUM (3* TP_MAX_STREAMNUM + 1)
#define MAX_PUTAUD_CHANNEL_NUM (TP_MAX_STREAMNUM * MAX_AUDMIX_MDL_NUM)
#define MAX_323_CALL_NUM 5

CLocalAudMixAddrList	CUmsConfInst::m_clocMixAddrMgr;
CLocalDualAddrList	CUmsConfInst::m_clocDualAddrMgr;
CLocalChanAddrList	CUmsConfInst::m_cLocChanAddrMgr;
CLocalSmallChanAddrList	CUmsConfInst::m_cLocSmallChanAddrMgr;
CCascadeChairAddrList CUmsConfInst::m_cCascadeChairAddrMgr;

CLocalPollChanAddrList CUmsConfInst::m_cLocPollAddrMgr; 
CLocalRollChanAddrList CUmsConfInst::m_cLocRollAddrMgr;

CPutAudChanAddrList  CUmsConfInst::m_cPutAudAddrMgr;
CEapuChanAddrList    CUmsConfInst::m_cEapuAddrMgr;

CAddrList	CUmsConfInst::m_cAddrList;

CTvWallMgr*	CUmsConfInst::m_pcTvWallMgr = NULL;
CUmsRegMgr*	CUmsConfInst::m_pcRegMgr = NULL;
CVmpServiceHandler* CUmsConfInst::m_pcVmpTpHandle = NULL;
CDsList*	CUmsConfInst::m_pcCallDs = NULL;
CGetVidAudEx* CUmsConfInst::m_pcGetVidEx = NULL;
TUmsCallCfg CUmsConfInst::m_tCallCfg;
TTPConfEpParamArray CUmsConfInst::m_tConfEpInfoMrg;
TMediaNetWorkManger CUmsConfInst::m_tMediaNetWorkManger;
TXmpuVmpManger  CUmsConfInst::m_tXmpuVmpManger; 
BOOL32 CUmsConfInst::m_bMpcReged = FALSE;
u32	CUmsConfInst::m_dwOnlineChanNum = 0;
CTpTimerMgr* CUmsConfInst::m_pcTimerMgr = NULL;
CQueryAliasMgr  CUmsConfInst::m_QueryAliasMgr;
u32 CUmsConfInst::m_dwLicenseChanNum = 0;
u32 CUmsConfInst::m_dwDelayTime = 1500;
extern BOOL32 g_bKedaManuOn;

typedef struct tagTempConfLabel
{
	BOOL32	m_bUsed;
	u16		m_wConfId;
	
	tagTempConfLabel()
	{
		Clear();
	}
	void Clear()
	{
		m_bUsed = FALSE;
		m_wConfId = TP_INVALID_INDEX;
	}
}TempConfLabel;

/*const u8 g_abyTempConfName[] = "临时会议";*/
static TempConfLabel g_atTempConf[TP_UMS_MAX_CONFNUM]; 
u16 GetIdleTempConfID()
{
	for(u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		if (!g_atTempConf[wIndex].m_bUsed)
		{
			return wIndex;
		}
	}
	return TP_INVALID_INDEX;
}

void ClearTempConfSeq(u16 wConfId)
{
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		if (wConfId == g_atTempConf[wIndex].m_wConfId)
		{
			g_atTempConf[wIndex].m_bUsed = FALSE;
		}
	}
}

#ifdef _USE_XMPUEQP_
typedef struct tagTXmpuInitMeetingConfInfo
{
	BOOL32				m_bInitXmpuMeeting; // 有效的标识

	TConfTemplateLocal  m_tXmpuConfTempInfo;
	TCapNode			m_tXmpuCallerNode;
	BOOL32				m_bXmpuNeedDelayCall;

	tagTXmpuInitMeetingConfInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_bInitXmpuMeeting = FALSE;
		m_tXmpuConfTempInfo.Clear();
		m_tXmpuCallerNode.Clear();
		m_bXmpuNeedDelayCall = FALSE;
	}

}TXmpuInitMeetingConfInfo;

static TXmpuInitMeetingConfInfo g_atXmpuInitMeeting[TP_UMS_MAX_CONFNUM];

#endif //#ifdef _USE_XMPUEQP_

SEMHANDLE g_confInstDaemonQuitSem = NULL;
SEMHANDLE g_confInstQuitSem = NULL;
u32		g_wconfInstQuitCount = 0;

CUmsCallMgrApp g_cUmsCallMgrApp;
void InitUmsConfMgr(TUmsCallCfg& tCfg)
{
	OspSemBCreate(&g_confInstDaemonQuitSem);
	if (NULL == g_confInstDaemonQuitSem)
	{
		msgprint("InitUmsConfMgr Create daemon quit sem failed!\n");
		return;
	}
	
	OspSemBCreate(&g_confInstQuitSem);
	if (NULL == g_confInstQuitSem)
	{
		msgprint("InitUmsConfMgr Create quite sem failed!\n");
		return;
	}
	g_wconfInstQuitCount = 0;

	u32 dwDelayTime = CUmsConfigEx::GetInstance()->GetDelayTime();
	CUmsConfInst::SetDelayTime(dwDelayTime);

	g_cUmsCallMgrApp.CreateApp("CUmsCallMgrApp",AID_UMSCONFMGR,100, 4096);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	for (u16 dwIndex = 0; dwIndex < TP_UMS_MAX_CONFNUM; ++dwIndex)
	{
		cMsg.Post( MAKEIID(AID_UMSCONFMGR,dwIndex+1) );
	}
	cMsg.Post( MAKEIID(AID_UMSCONFMGR,CInstance::DAEMON) );

	cMsg.SetEvent(evtp_sys_init);
	cMsg.SetBody(&tCfg, sizeof(tCfg));
	cMsg.Post( MAKEIID(AID_UMSCONFMGR,CInstance::DAEMON) );
}

void QuitUmsConfMgr()
{
	CTpMsg cMsg;
	cMsg.SetEvent(ev_kdvmsg_sys_exit);
	for (u16 dwIndex = 0; dwIndex < TP_UMS_MAX_CONFNUM; ++dwIndex)
	{
		cMsg.Post( MAKEIID(AID_UMSCONFMGR,dwIndex+1) );
	}
	if (g_confInstQuitSem != NULL)
	{
		while (g_wconfInstQuitCount != 0)
		{
			msgprint( "QuitUmsConfMgr wait for g_wconfInstQuitCount =%d!\n", g_wconfInstQuitCount);	
			OspSemTake(g_confInstQuitSem);
			msgprint( "QuitUmsConfMgr wait g_wconfInstQuitCount =%d!\n", g_wconfInstQuitCount);	
			OspSemGive(g_confInstQuitSem);
			OspDelay( 30 );
		}
		OspSemDelete(g_confInstQuitSem);
		g_confInstQuitSem = NULL;
	}


	cMsg.Post( MAKEIID(AID_UMSCONFMGR,CInstance::DAEMON) );
	if (g_confInstDaemonQuitSem != NULL)
	{	
		msgprint( "QuitUmsConfMgr wait for g_confInstDaemonQuitSem.\n");	
		OspSemTake(g_confInstDaemonQuitSem);
		OspSemDelete(g_confInstDaemonQuitSem);
		g_confInstDaemonQuitSem = NULL;
	}
}

void VirSingleVmpCB(const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, void* param, u16 wTmp1)
{
	CUmsConfInst* pInst = (CUmsConfInst*)param;
	
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		pInst->GetUmsDiscuss()->VmpCBForSingle(pcService, emOpType, emRes, wTmp1);
	}
	else
	{
		pInst->GetVmp()->VmpCB(pcService, emOpType, emRes, wTmp1);
	}
	return;
}

void VirSingleBasCB(u32 dwType, void* param1, void* param2)
{
#ifdef _USE_XMPUEQP_
    tXmpuBasCbData *pBasCbData = (tXmpuBasCbData *)param1;
	CUmsConfInst* pInst = (CUmsConfInst* )pBasCbData->pService;
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		pInst->GetUmsDiscuss()->XmpuBasCBForSingle(dwType, (CScreenBasRes *)pBasCbData->pRes, pBasCbData->pData);
	}
	else
	{
		pInst->GetVmp()->XmpuBasCB(dwType, (CScreenBasRes *)pBasCbData->pRes, pBasCbData->pData );
	}
#else
	CScreenBasRes::VidBasCBType emType = (CScreenBasRes::VidBasCBType)dwType;
	CUmsConfInst* pInst = (CUmsConfInst*)param1;
	CScreenBasRes* ptBasRes = (CScreenBasRes*)param2;
	
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		pInst->GetUmsDiscuss()->BasCBForSingle(emType, ptBasRes);
	}
	else
	{
		pInst->GetVmp()->BasCB(emType, ptBasRes);
	}

#endif

	return;
}

void VirSingleMixCB(u32 dwType, void* param1, void* param2)
{

#ifdef _USE_XMPUEQP_
	tXmpuMixCbData* ptCbData = (tXmpuMixCbData* )param1;
    CUmsConfInst*	pInst = (CUmsConfInst*)ptCbData->pService;
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
        pInst->GetUmsDiscuss()->XmpuMixCBForSingle(dwType, (TAudMixInfo*)ptCbData->pRes, ptCbData->pData);
	} 
	else 
	{
        pInst->GetDualMgr()->DualXmpuAudMixCB(dwType, (TAudMixInfo*)ptCbData->pRes, ptCbData->pData);
	}

#else
	TAudMixInfo::EmCBOprType emType = (TAudMixInfo::EmCBOprType)dwType;
	TAudMixInfo* ptMixInfo = (TAudMixInfo*)param1;
	CUmsConfInst* pInst = (CUmsConfInst*)param2;
	
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		pInst->GetUmsDiscuss()->MixCBForSingle(emType, ptMixInfo);
	}
	else
	{
		pInst->GetDualMgr()->DualAudMixCB(emType, ptMixInfo);
	}
#endif
	return;
}

CUmsConfInst::CUmsConfInst()
:m_pcNodeMgr(NULL)
,m_pcDual(NULL)
,m_pcCallMgr(NULL)
,m_pcUmsDiscuss(NULL)
,m_pcSelView(NULL)
,m_pcPollMgr(NULL)
,m_pcRollCallMgr(NULL)
,m_pcPutAudMgr(NULL)
,m_pcAudMix(NULL)
,m_tGetConfVidAudMgr(NULL)
,m_pcMcuMgr(NULL)
{
	m_wLogModuleId = Ums_Mdl_Call;
	
	m_bIsQuiting = FALSE;
	m_wConfTemplateID = TP_INVALID_INDEX;
	m_bIsNeedKeyProtectOnStart = FALSE;

	m_tConfBaseInfo.Clear();
	m_tSuperChairCap.Clear();
	m_tSuperInfo.Clear();
	m_tUpdateNodeList.Clear();

	m_bIsNeedDelayCallNode = FALSE;
	m_bIsAllEpMute = FALSE;
	m_bIsAllEpQuiet = FALSE;
	m_bEpNodeCheck = FALSE;
	SetCurSpeaker(NULL);
	SetOldSpeaker(NULL);
	SetChairID(NULL);
	
	u16 wIndex;

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		m_abOnIFrameCheck[wIndex] = FALSE;
	}
	m_bOnSingleIframeCheck = FALSE;


	for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		m_atMediaKey[wIndex].clear();
	}
	m_wMediaKeyIndx = 0;
	m_bSetMediaKey = FALSE;
}

CUmsConfInst::~CUmsConfInst()
{
	ObjectExit();
}

void CUmsConfInst::DaemonMessageProc(CTpMsg *const ptMsg, CApp* pcApp)
{
	u16 wEvent = ptMsg->GetEvent();

	if ( wEvent == evtp_TimerMgrTimer_Tick )
	{
		if (NULL != m_pcTimerMgr)
		{
			m_pcTimerMgr->Check();
		}
		
		SetTimer(evtp_TimerMgrTimer_Tick, TP_INTERVAL_TIME_ONE_SECOND);
		return ;
	}

	if (wEvent > segment_begin(innerregsrv) && wEvent < segment_end(innerregsrv))
	{
		m_pcRegMgr->Handler(ptMsg);
		return;
	}
	
	if ((wEvent > segment_begin(umsinnertvwall) && wEvent < segment_end(umsinnertvwall))
		|| (wEvent >=  evTPUMS_CNS_hduPlan_Nty && wEvent <= evTPUMS_CNS_HduChangeChanMode_Ind))
	{
		m_pcTvWallMgr->Handler(ptMsg, pcApp);
		return;
	}

	if (wEvent > segment_begin(outerumsquantum) && wEvent < segment_end(outerumsquantum))
	{
        DaemonProQtMsg(ptMsg,  pcApp);
		return;
	}

	if( CEqpService::Instance().Handler(ptMsg) )
	{
		return ;
	}

	if ( GetVmpServiceHandle()->Handler(ptMsg) )
	{
		return ;
	}


	switch(wEvent)
	{
	case evtp_sys_init:
		DaemonInitCfg(ptMsg, pcApp);
		break;
	case ev_UmsIPCfg:
		DaemonInitPort(pcApp);
		break;
	case evtp_UmsConfIncoming:
		NotifyMsgToService(evtp_UmsConfIncoming, ptMsg->GetBody(), ptMsg->GetBodyLen());
		break;
	case evtp_UmsConfCreateMeeting:
		{
			memcpy(&m_tTemp.m_tCallInfo, ptMsg->GetBody()+sizeof(TUmsHandle), sizeof(TUmsCallInfo));
			memcpy(&m_tTemp.m_tTemp.m_tTemplate1, ptMsg->GetBody()+sizeof(TUmsHandle)+sizeof(TUmsCallInfo), sizeof(TTPConfTemplateBuf1));
		}
		break;
	case evtp_UmsConfCreateMeeting1:
		{
			memcpy(&m_tTemp.m_tTemp.m_tTemplate2, ptMsg->GetBody()+sizeof(TUmsHandle), sizeof(TTPConfTemplateBuf2));
			
			TConfTemplateLocal tConfTemp;
			m_tTemp.m_tTemp.GetValueForCall((TTPConfTemplate*)&tConfTemp);

			u8 abyBuf[sizeof(TUmsHandle) + sizeof(TUmsCallInfo) + sizeof(TConfTemplateLocal)];
			memcpy(abyBuf, ptMsg->GetBody(), sizeof(TUmsHandle));
			memcpy(abyBuf+sizeof(TUmsHandle), &m_tTemp.m_tCallInfo, sizeof(TUmsCallInfo));
			memcpy(abyBuf+sizeof(TUmsHandle)+sizeof(TUmsCallInfo), &tConfTemp, sizeof(TConfTemplateLocal));
			NotifyMsgToService(evtp_UmsConfCreateMeetingMsg, abyBuf, sizeof(abyBuf));
		}
		break;
	case evtp_UmsConfIncomingAck:
		DaemonConfIncomingFromService(ptMsg, pcApp);
		break;

	case evtp_UmsAdapterReg_Notify:
		DaemonConfAdapterReg(ptMsg, pcApp);
		break;
	case evtp_UmsAdapterUnReg_Notify:
		DaemonConfAdapterUnReg(ptMsg, pcApp);
		break;
	case evtp_UmsAudioMixUnReg_Notify:
		DaemonConfAudMixUnReg(ptMsg, pcApp);
		break;
	case evtp_UmsAudioMixReg_Notify:
		DaemonConfAudMixReg(ptMsg, pcApp);
		break;
	case evtp_UmsMediaReg_Notify:
		DaemonConfMediaReg(ptMsg, pcApp);
		break;
	case evtp_UmsMediaUnReg_Notify:
		DaemonConfMediaUnReg(ptMsg, pcApp);
		break;
	case evtp_UmsVmpReg_Notify:
	case evtp_UmsVmpUnReg_Notify:
	case evtp_VmpToCall_NAck:
		DaemonConfVmpProc(ptMsg, pcApp);
		break;
	case evtp_UmsBasUnReg_Notify:
	case evtp_UmsBasStart_NAck:
	case evtp_UmsBasChangeDsIP_Req:
		DaemonConfBasMsgProc(ptMsg, pcApp);
		break;
	case evtp_UmsMpcReged_Notify:
		break;
	case evtp_ums_reg_ret:
		m_pcRegMgr->Handler(ptMsg);
		break;
	case ev_UmsGetRegInfo_Rsp:
	case ev_UmsGetRegInfo_UmsRspEx:
	case ev_UmsGetRegInfo_CnsRspEx:
	case ev_UmsGetGkRegInfo_MtRsp:
	case ev_UmsGetGkRegInfo_McuRsp:
	case evtp_ums_unreg_ret:
	case evtp_ums_323_unreg_ret:
	case ev_register_handle_info:
		{
			m_pcRegMgr->Handler(ptMsg);
		}
		break; 
	case evtp_UmsAccessNum_Notify:
		{
			u32 wTmp = m_dwLicenseChanNum;
			TP_SAFE_CAST(m_dwLicenseChanNum, ptMsg->GetBody());
			msgprint("LicenseChanNum from %d To %d\n", wTmp, m_dwLicenseChanNum);	
			
			u8 abBuf[sizeof(u32)*2] = {0};			
			TLogUser tUserTmp;
			tUserTmp.m_dwUserInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);
			memcpy(abBuf, &m_dwLicenseChanNum, sizeof(u32));
			memcpy(abBuf + sizeof(u32), &m_dwOnlineChanNum, sizeof(u32));
			
			NotifyMsgToServiceForUI(ev_authCount_Nty, abBuf, sizeof(abBuf), &tUserTmp);
			MdlHint(Ums_Mdl_Call, ("LicenseNum:%d, OnlineNum:%d.\n", m_dwLicenseChanNum, m_dwOnlineChanNum));
		}		
		break;
	case ev_authCount_req:
		{
			u8 abBuf[sizeof(u32)*2] = {0};			
			TLogUser* ptUserTmp = (TLogUser*)ptMsg->GetBody();
			memcpy(abBuf, &m_dwLicenseChanNum, sizeof(u32));
			memcpy(abBuf + sizeof(u32), &m_dwOnlineChanNum, sizeof(u32));
			
			NotifyMsgToServiceForUI(ev_authCount_Nty, abBuf, sizeof(abBuf), ptUserTmp);
			MdlHint(Ums_Mdl_Call, ("LicenseNum:%d, OnlineNum:%d.\n", m_dwLicenseChanNum, m_dwOnlineChanNum));
		}
		break;
	case evXmpu_VmpConnect_Nty:
		{
			OnXmpuVmpConnect(ptMsg);
		}
		break;
	case evXmpu_VmpRefresh_Nty:
		{
			OnXmpuRefreshVmp(ptMsg);
		}
		break;
	default:
		{
			u32 dwAppID = GETAPP(ptMsg->GetSrcIId());
			if (dwAppID == AID_UMSSIPADAPTER_APP)
			{
				TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
				u8* pData = ptMsg->GetBody()+sizeof(TUmsHandle);

				if ( ptHandle->GetConfID() == 0 )
				{//APP Handle 为空 根据PaHandle处理
					ObjError(("DaemonMessageProc. App Handel Invalid!! ConfID:%d, EpID:%d, PaHandle:%d, event:%d->%s\n"
						, ptHandle->GetConfID(), ptHandle->GetEpID(), ptHandle->handPaCall, ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
					DaemonConfInvalidAppHandleProc(ptMsg, pcApp);
					return ;
				}
				
				CUmsConfInst* pcInst =  (CUmsConfInst*)pcApp->GetInstance(ptHandle->GetConfID());
				if (NULL == pcInst || inst_idle == pcInst->CurState())
				{
					ObjError(("DaemonMessageProc inst error. ConfID:%d, EpID:%d, event:%d->%s\n"
						, ptHandle->GetConfID(), ptHandle->GetEpID(), ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
					return;
				}
				
				if( wEvent == evtp_Conf_AskKeyFrame ||
					wEvent == evtp_Conf_AskKeyByScreen ||
					wEvent == evtp_UmsDiscussFastUpdate_Req)
				{
					MdlLowDtl(Ums_Mdl_Call, ("DaemonProc ConfID:%d, epID:%d, PaCall:%d, Chan:%d, Ev:%d->%s\n"
						, ptHandle->GetConfID(), ptHandle->GetEpID(), ptHandle->handPaCall, ptHandle->handPaChan,
							ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
				}
				else
				{
					ObjHint(("DaemonProc ConfID:%d, epID:%d, PaCall:%d, Chan:%d, Ev:%d->%s\n"
						, ptHandle->GetConfID(), ptHandle->GetEpID(), ptHandle->handPaCall, ptHandle->handPaChan,
						ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
				}
				
				pcInst->MessageProc(ptMsg);
			}
			else
			{
				ObjError(("DaemonMessageProc unknow src! SrcApp:%d, event:%d->%s\n"
					, dwAppID, ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
			}
		}
		break;
	}
}

void CUmsConfInst::MessageProc(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	u32 dwAppID = GETAPP(ptMsg->GetSrcIId());
	BOOL32 bProccessed = FALSE;
	
	if (dwAppID == AID_UMSSIPADAPTER_APP)
	{
		u16 wEvent = ptMsg->GetEvent();
		
		TUmsHandle tHandle;
		u8* pMsgBuf = ptMsg->GetBody();
		TP_SAFE_CAST(tHandle, pMsgBuf);
		u8* pDataBuf = pMsgBuf + sizeof(TUmsHandle);


		if (wEvent > ev_SipAdapter_DualBegin && wEvent < ev_SipAdapter_PollBegin)
		{
			bProccessed = m_pcDual->Handler(ptMsg);
		}
		else if (wEvent > ev_SipAdapter_PollBegin && wEvent < ev_SipAdapter_UmsDiscussBegin)
		{
			if ( m_pcPollMgr->HandlerFromStack(ptMsg) )
			{
				return;
			}
		}
		else if (wEvent > ev_SipAdapter_GetVid_Begin && wEvent < ev_SipAdapter_OtherConfBegin)
		{		
		}
		else if (wEvent >= evtp_OpenVidChan_Cmd && wEvent <= evtp_CloseVidChan_Cmd)
		{
			 bProccessed = m_pcPutAudMgr->Handler(ptMsg);
             
		}
		else if (wEvent > ev_SipAdapter_UmsDiscussBegin && wEvent < ev_SipAdapter_UmsEapuBegin)
		{
			bProccessed = m_pcUmsDiscuss->HandlerFromStack(ptMsg);
		}
		else if (wEvent > ev_SipAdapter_UmsEapuBegin && wEvent < ev_SipAdapter_CnsConfStatBegin)
		{
			bProccessed = m_pcEapu->HandlerFromStack(ptMsg);
		}
		else if (wEvent >= ev_UmsConfRollCallUpdate_Cmd && wEvent <= ev_UmsConfRollCallUpdate_Nty)
		{
            bProccessed = m_pcRollCallMgr->HandlerFromStack(ptMsg);

		} else if (wEvent >= evtp_CNS_UMS_ConfAudMixMode_cmd && wEvent <= evtp_UMS_UMS_ConfAudMixMode_Notify)
		{
            bProccessed = m_pcAudMix->HandlerFromStack(ptMsg);

		} else if (wEvent >= evtp_QuantumEvent_Begin && wEvent <= evtp_QuantumEvent_End)
		{
            bProccessed = ProQtMsg(ptMsg);
		}
		else
		{
			if ( m_pcGetVidEx->Handler(this, ptMsg) )
			{
				return ;
			}
			if ( m_pcSelView->HandlerFromStack(ptMsg) )
			{
				return;
			}

			if ( m_pcVmp->HandlerFromStack(ptMsg) )
			{
				return;
			}

			if (m_pcCallMgr->HandlerFromStack(tHandle, wEvent, pDataBuf))
			{
				return;
			}

			bProccessed = TRUE;

			switch(wEvent)
			{
			//从协议栈来的消息
			case evtp_Conf_UmsCallConnect:
				OnCallConnect(ptMsg);
				break;
			case evtp_Conf_UmsCallDisConnect:
				OnCallDisConnect(ptMsg, TRUE);
				break;
			case evtp_Conf_UmsChannelConnect:
				OnChanConnect(ptMsg);
				break;
			case evtp_Conf_UmsChannelDisConnect:
				OnChanDisConnect(ptMsg);
				break;
			case evtp_cascade_OpenChairChan_cmd:
				OnOpenCascadeChairChan(ptMsg);
				break;
			case evtp_cascade_OpenChairChan_ack:
				OnOpenCascadeChairChanAck(ptMsg);
				break;
			case evtp_Conf_YouAreSeeing_Ind:
				OnConfYouAreSeeing(ptMsg);
				break;
			case evtp_Conf_AskKeyFrame:
				OnConfAskKeyFrame(ptMsg);
				break;
			case evtp_Conf_CnsSpeaker_Notify:
				OnAdjustInnerSpeakFromCns(ptMsg);
				break;
			case evtp_Conf_CnsSpeakerCascad_Notify:
				OnConfCnsSpeakerCascadNotify(ptMsg);
				break;
			case evtp_Conf_MuteRemoteEp_Cmd:
				OnConfMuteRemoteEpCmd(ptMsg);
				break;
			case evtp_Conf_MuteRemoteEp_Ind:
				OnConfMuteRemoteEpInd(ptMsg);
				break;
			case evtp_Conf_QuietRemoteEp_Cmd:
				OnConfQuietRemoteEpCmd(ptMsg);
				break;
			case evtp_Conf_QuietRemoteEp_Ind:
				OnConfQuietRemoteEpInd(ptMsg);
				break;
			case evtp_Conf_StatusInfo_Notify:
				OnConfChairInfo(ptMsg);
				break;
			case evtp_Conf_TvMonitor_Cmd:
				OnConfTvMonitorCmd(ptMsg);
				break;
			case evtp_Conf_TvMonitor_Ind:
				OnConfTvMonitorInd(ptMsg);
				break;
			case evtp_Conf_TvMonitor_stop:
				OnConfTvMonitorStop(ptMsg);
				break;
			case evtp_Conf_AskKeyByScreen:
				OnConfAskKeyToScreen(ptMsg);
				break;
			case evtp_Conf_ChairCap_Notify:
				OnConfChairCapNotify(ptMsg);
				break;
			case evtp_Conf_FlowCtrol:
				OnConfFlowCtrl(ptMsg);
				break;
			case evtp_Conf_AdjustFrameRate:
				OnConfAdjustFrameRate(ptMsg);
				break;
			case evtp_Conf_AdjustVidRes:
				OnConfAdjustVidRes(ptMsg);
				break;
			case evtp_Conf_ResetFastUpdate:
				OnResetFastUpdate(ptMsg);
				break;
		//从Sip过来的多点信令
			case ev_UmsConfApplySpeaker_Cmd:
				OnChangeSpeaker(ptMsg);
				break;
			case ev_UmsConfMute_Cmd:  // form cnc
				OnMuteEp(ptMsg);
				break;
			case ev_UmsConfQuiet_Cmd:
				OnQuietEp(ptMsg);
				break;
			case ev_UmsHangupConf_Cmd:
				OnHungConf(ptMsg);
				break;

			case ev_UmsCommonReasonToUI_Ind:
				{
					TTPUmsReasonInd& tInd = *(TTPUmsReasonInd*)(ptMsg->GetBody() + sizeof(TUmsHandle));
					NotifyReasonToUI( EmUI_CNC, tInd.m_dwReason, tInd.m_wEpID, tInd.m_dwReserve1, tInd.m_dwReserve2, tInd.m_dwReserve3);
				}
				break;
			//广播类消息
			case ev_UmsConfApplySpeaker_Nty:
			case ev_UmsConfMute_Nty:
			case ev_UmsConfQuiet_Nty:
				OnBrdCastMsg(ptMsg);
				break;
			//323类型消息
			case evtpH323_Conf_TerminalListRequest:
				OnTerListReq(ptMsg);
				break;

			//mcu级联消息
			case evtp_MCU_UMS_CasecadeChanConnected:
				OnMcuCasecadeChanConnected(ptMsg);
				break;
			case evtp_MCU_UMS_RegUnRegReq:
				OnMcuCasecadeRegUnRegReq(ptMsg);
				break;
			case evtp_MCU_UMS_RegUnRegRsp:
				OnMcuCasecadeRegUnRegRsp(ptMsg);
				break;
			case evtp_MCU_UMS_RosterNotify:
				OnMcuCasecadeRosterNotify(ptMsg);
				break;
			case evtp_MCU_UMS_PartListRsp:
				OnMcuCasecadePartListReqRsp(ptMsg);
				break;
			case evtp_MCU_UMS_PartStateNty:
				OnMcuCasecadePartStateNty(ptMsg);
				break;
			case evtp_MCU_UMS_DelPartNty:
				OnMcuCasecadeDelPartNty(ptMsg);
				break;
			case evtp_MCU_UMS_SpyBWNty:
				OnMcuCasecadeSpyBWNty(ptMsg);
				break;
			// 远遥通道上线
			case evtp_CNS_UMS_FeccChanConnected:
				OnFeccChannedConnnected(ptMsg);
				break;
			// cnc请求远遥会场
			case evtp_CNS_UMS_FeccReq:
				OnFeccReqFromCns(ptMsg);
				break;
			// 会场视频源通知
			case evtp_CNS_UMS_VidInfoNty:
				OnVidSourceInfoFromCns(ptMsg);
				break;
			// 323会场当前源通知
			case evtp_CNS_UMS_EpStatusNty:
				OnEpStatusNty(ptMsg);
				break;
				//白板消息
			case evtp_JoinWBConf_Cmd:
			case evtp_JoinWBConf_Ind:
			case evtp_HungUpWBConf_Cmd:
				{
					m_pcDataConf->Handler(ptMsg);
				}
				break;
			// 渠道消息通知
			case evtp_KedaManuProduct_Notify:
				{
					OnEpKedaManuProduckNotify(ptMsg);
				}
				break;
			default:
				{
					bProccessed = FALSE;					
				}
				break;
			}//switch
		}

		if (!bProccessed)
		{
			ObjError(("MessageProc unknow msg From stack! event:%d->%s\n", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		}
	}
	else
	{
		if ( m_pcPollMgr->Handler(ptMsg) )
		{
			return;
		}

		if (m_pcEapu->Handler(ptMsg))
		{
			return;
		}

		if ( m_pcVmp->Handler(ptMsg) )
		{
			return;
		}

		if ( m_pcBas->Handler(ptMsg) )
		{
			return;
		}

		if ( m_pcSelView->Handler(ptMsg) )
		{
			return;
		}

		// add by gaoyong
		// umc会控消息：邀请，挂断，呼叫   
		if ( m_pcCallMgr->HandlerFromUmc(ptMsg))
		{
			return;
		}
		// 双流操作
		if ( m_pcDual->HandlerFromUmc(ptMsg))
		{
			return;
		}

		if (m_pcUmsDiscuss->HandlerFromUmc(ptMsg))
		{
			return;
		}

		if (m_pcAudMix->HandlerFromUmc(ptMsg))
		{
			return;
		}

		if(m_pcRollCallMgr->HandlerFromUmc(ptMsg))
		{
            return;
		}

		if (m_tGetConfVidAudMgr->HandlerFromUmc(ptMsg))
		{
		    return;
		}

		if (m_pcMcuMgr->HandlerFromCns(ptMsg))
		{
			return;
		}

		bProccessed = TRUE;
		switch (ptMsg->GetEvent())
		{
		case ev_SysCmsLoginInd:
			EventUserLogin(ptMsg);
			break;
		case evtp_UmsMakeConf:
			{
				EmCnsCallReason emCallRet = EventStartConf(ptMsg->GetBody(), ptMsg->GetBodyLen(), NULL, FALSE);
				
				TStartConfResult tRet;
				TConfTemplateLocal* pConfTmp = (TConfTemplateLocal*)(ptMsg->GetBody());
				tRet.m_wConfID = GetInsID();
                tRet.m_wConfTemplateID = pConfTmp->m_wID;
				tRet.m_emReason = CTpTypeAdpt::GetConfRetByCallReason(emCallRet);
				NotifyMsgToService(evtp_StartConfTemplate_Ret, &tRet, sizeof(tRet));

				if ( EmCnsCallReason_success != emCallRet )
				{
					u16 wConfID = GetInsID();
					NotifyMsgToService(evtp_UmsConfDisConnect, &wConfID, sizeof(wConfID));
					ObjError(("evtp_UmsMakeConf. start failed. wConfID:%d\n", wConfID));
				}
			}		
			break;
		case evtp_MuteEp_cmd:   // add begin form umc 
			{
				OnMuteEpFromUmc(ptMsg);
			}
			break;
		case evtp_QuietEp_cmd:
			{
				OnQuietEpFromUmc(ptMsg);
			}
			break;
		case evtp_ApplySpeaker_cmd:
			{
				OnChangeSpeakerFromUmc(ptMsg);
			}
			break;
		case evtp_CallNode_time:
			EventOnCallTime();
			break;
		case evtp_AskFrameToBas_time:
			m_pcBas->OnAskFrameTime();
			break;
		case evtp_UpdateConfNode_time:
			NotifyUpdateNodeToUi();
			break;
		case evtp_KeyProtectOnStart_time:
			EventOnProtectTime();		
			break;
		case evtp_HungUpConf_cmd:
			EventHungConf(ptMsg);
			break;
		
		case ev_media_ds_iframe_bySrc_Ind:
			OnIframeBySrcNty(ptMsg);
			break;
		// 会场远遥
		// Umc 摄像机控制请求
		case evtp_FeccCamera_Req:
			OnFeccCamControlFromUmc(ptMsg);
			break;
		// Umc 预置位保存 加载请求
		case evtp_FeccPrePos_Req:
			OnFeccPrePosReqFromUmc(ptMsg);
			break;
		// Umc 切视频源请求
		case evtp_FeccSelVid_Req:
			OnFeccSelVidFromUmc(ptMsg);
			break;

		case ev_media_ds_iframe_byDis_Ind:
			//重新刷交换
			// to do...
			break;
		// 渠道检测计时器
		case evtp_EpNodeTimer_Check:
			{
				EventEpNodeTimerCheck();
			}
			break;
		case evXmpu_InitMettingFaild_Nty:
			{
				OnXmpuInitMeetingNty(ptMsg);
			}
			break;
		// Xmpu msg
		case evXmpu_VmpMdy_Nty:
			{
				OnXmpuVmpMdyNty(ptMsg);
			}
			break;
		case evXmpu_AskVmpKey_Req:
			{
				OnXmpuAskKeyReq(ptMsg);
			}
			break;
		case evXmpu_VmpDisConnect_Nty:
			{
				OnXmpuVmpDisConnect(ptMsg);
			}
			break;
		default:
			{
				bProccessed = FALSE;				
			}
			break;
		}

		if (!bProccessed)
		{
			ObjError(("MessageProc unknow msg From Server! event:%d->%s\n", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		}
	}
	
}

BOOL CUmsConfInst::ObjectInit(u32 wParam, u32 lParam)
{
	if (m_bInit)
	{
		return TRUE;
	}	
	SetLogTitle("[CUmsConfInst]");

	m_pcNodeMgr = new CCallNodeMgr(this);
	if (NULL == m_pcNodeMgr || !m_pcNodeMgr->Create())
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CCallNodeMgr failed\n"));
		return FALSE;
	}
	

	m_pcDual = new CDualMgr(this);
	if (NULL == m_pcDual)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CDualMgr failed\n"));
		return FALSE;
	}

	m_pcCallMgr = new CCallMgr(this);
	if (NULL == m_pcCallMgr)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc callmgr failed\n"));
		return FALSE;
	}
	
	m_pcVmp = new CUmsVmp(this);
	if (NULL == m_pcVmp)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CUmsVmp failed\n"));
		return FALSE;
	}
	m_pcVmp->Create();

	m_pcBas = new CUmsBas(this);
	if (NULL == m_pcBas)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CUmsBas failed\n"));
		return FALSE;
	}
	
	m_pcEapu = new CUmsEapu(this);
	if (NULL == m_pcEapu)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CUmsEapu failed\n"));
		return FALSE;
	}

	m_pcNodeFsm = new CNodeFsmMgr(this);
	if (NULL == m_pcNodeFsm)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CNodeFsmMgr failed\n"));
		return FALSE;
	}
	m_pcNodeFsm->Init();

	m_pcUmsDiscuss = new CUmsDiscussMgr(this);
	if (NULL == m_pcUmsDiscuss)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CUmsDisMgr failed\n"));
		return FALSE;
	}
	m_pcUmsDiscuss->Enter();

	m_pcSelView = new CSelView(this);

	if (NULL == m_pcSelView)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CSelView failed\n"));
		return FALSE;
	}

	m_pcPollMgr = new CPollMgr(this);
	if (NULL == m_pcPollMgr)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CPollMgr failed\n"));
		return FALSE;
	}
	
	m_pcDataConf = new CDataConfHandler(this);
	if (NULL == m_pcDataConf)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CDataConfHandler failed\n"));
		return FALSE;
	}

	m_pcPutAudMgr = new CPutAud(this); 
	if (NULL == m_pcPutAudMgr)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc PutAudMgr failed\n"));
		return FALSE;
	}

	m_pcRollCallMgr = new CUmsRollCallMgr(this);
	if (NULL == m_pcRollCallMgr)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc RollCallMgr failed\n"));
		return FALSE;
	}
	m_pcRollCallMgr->Enter();

	m_pcAudMix = new CUmsAudMixMgr(this);
	if (NULL == m_pcAudMix)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CUmsAudMixMgr failed\n"));
		return FALSE;
	}
	m_pcAudMix->Enter();


	m_tGetConfVidAudMgr = new CGetConfVidAudMgr(this);
	if (NULL == m_tGetConfVidAudMgr)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CGetConfVidAudMgr failed\n"));
		return FALSE;
	}
	m_tGetConfVidAudMgr->Enter();

	m_pcMcuMgr = new CUmsMcuMgr(this);
	if (NULL == m_pcMcuMgr)
	{
		ObjectExit();
		ObjError(("ObjectInit malloc CUmsMcuMgr failed\n"));
		return FALSE;
	}
	m_pcMcuMgr->Enter();

	m_cSpeaker.m_pcSingleVmp = NULL;

	m_tSpeakerMediaFmt.Clear();

	NextState(inst_idle);

	OspSemTake(g_confInstQuitSem);
	g_wconfInstQuitCount++;
	OspSemGive(g_confInstQuitSem);

	return TRUE;
}

void CUmsConfInst::ObjectExit(void)
{
	StopConf();

	if( NULL != m_pcPutAudMgr )
	{
         m_pcPutAudMgr->ReleaseAll(em_putauduser_none);
	}
    TP_SAFE_DEL(m_pcPutAudMgr);
	
	TP_SAFE_DEL(m_pcNodeMgr);
	TP_SAFE_DEL(m_pcCallMgr);
	TP_SAFE_DEL(m_pcDual);
	TP_SAFE_DEL(m_pcVmp);
	TP_SAFE_DEL(m_pcBas);
	TP_SAFE_DEL(m_pcEapu);

	if( NULL != m_pcNodeFsm )
	{
		m_pcNodeFsm->Quit();
	}

	TP_SAFE_DEL(m_pcNodeFsm);

	if( NULL != m_pcUmsDiscuss )
	{
		m_pcUmsDiscuss->Exit();
	}
	TP_SAFE_DEL(m_pcUmsDiscuss);
	TP_SAFE_DEL(m_pcSelView);
	TP_SAFE_DEL(m_pcPollMgr);

    if (NULL != m_pcRollCallMgr)
	{
		m_pcRollCallMgr->Exit();
	}
	TP_SAFE_DEL(m_pcRollCallMgr);

	if (NULL != m_pcAudMix)
	{
		m_pcAudMix->Exit();
	}
	TP_SAFE_DEL(m_pcAudMix);

	if (NULL != m_tGetConfVidAudMgr)
	{
        m_tGetConfVidAudMgr->Exit();
	}
	TP_SAFE_DEL(m_tGetConfVidAudMgr);

	if (NULL != m_pcMcuMgr)
	{
        m_pcMcuMgr->Exit();
	}
	TP_SAFE_DEL(m_pcMcuMgr);

	m_pcCallMgr = NULL;

	CUmsObject::ObjectExit();

	OspSemTake(g_confInstQuitSem);
	g_wconfInstQuitCount--;
	OspSemGive(g_confInstQuitSem);
}

u16 CUmsConfInst::InitPort(u16 wStartPort)
{
	u16 wOffsetPort = wStartPort;
	u16 wCnsIndex = 0;
	u16 wChanIndex = 0;
	u32 dwIP = GetLocalIP();

	TUmsNetBuf* pNetbufChan;
	
	//分配虚拟发言人码流的本地接收端口，UMS将发言会场的码流转到此，相当于解码器接收
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		m_cSpeaker.m_atVidDec[wChanIndex].m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		m_cSpeaker.m_atVidDec[wChanIndex].m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
		m_cSpeaker.m_atVidDec[wChanIndex].m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
		wOffsetPort += 4;
	}

	m_cSpeaker.m_tSingleVidDec.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
	m_cSpeaker.m_tSingleVidDec.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
	m_cSpeaker.m_tSingleVidDec.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
	wOffsetPort += 4;

	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{		
		m_cSpeaker.m_atAudDec[wChanIndex].m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		m_cSpeaker.m_atAudDec[wChanIndex].m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
		m_cSpeaker.m_atAudDec[wChanIndex].m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
		wOffsetPort += 4;
	}

	m_cSpeaker.m_tAudMixDec.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
	m_cSpeaker.m_tAudMixDec.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
	m_cSpeaker.m_tAudMixDec.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
	wOffsetPort += 4;

	//发言人NetBuf地址
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		pNetbufChan = &m_cSpeaker.m_atVidBuf[wChanIndex];
		
		pNetbufChan->m_tRcvRtpAddr.SetAddr(dwIP, wOffsetPort);	
		pNetbufChan->m_wSndAddr.SetAddr(dwIP, wOffsetPort+2);	
		pNetbufChan->m_tRcvRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
		pNetbufChan->m_tRmtRtcpAddr = m_cSpeaker.m_atVidDec[wChanIndex].m_tBackRtcpAddr;
		wOffsetPort += 4;
	}

	pNetbufChan = &m_cSpeaker.m_tSingleVidBuf;
	
	pNetbufChan->m_tRcvRtpAddr.SetAddr(dwIP, wOffsetPort);	
	pNetbufChan->m_wSndAddr.SetAddr(dwIP, wOffsetPort+2);	
	pNetbufChan->m_tRcvRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
	pNetbufChan->m_tRmtRtcpAddr = m_cSpeaker.m_tSingleVidDec.m_tBackRtcpAddr;
	wOffsetPort += 4;

	//主席地址
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		m_cChair.m_atVidDec[wChanIndex].SetAddr(dwIP, wOffsetPort);
		wOffsetPort += 4;
	}
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{		
		m_cChair.m_atAudDec[wChanIndex].SetAddr(dwIP, wOffsetPort);
		wOffsetPort += 4;
	}

	wOffsetPort = m_pcDual->InitPort(wOffsetPort);

	printf("InitPort ConfId:%d LocalAddr(VirSpeaker VirChair Dual) begin:%d, end:%d.\n", 
		GetInsID(), wStartPort, wOffsetPort);

	return wOffsetPort;
}

//根据转发板IP，充置会议IP
void CUmsConfInst::ResetMediaIp(const TEqpRes& tConfDs)
{
	if (!tConfDs.IsValid())
	{
		ObjError(("ResetMediaIp media ds invalid. wConfID:%d\n", GetInsID()));
		return;
	}

	u32 dwEqpIP = tConfDs.m_dwEqpIp;
	u16 wChanIndex = 0;

	//分配虚拟发言人码流的本地接收端口，UMS将发言会场的码流转到此，相当于解码器接收
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		m_cSpeaker.m_atVidDec[wChanIndex].m_tRtpAddr.SetIP(dwEqpIP);
		m_cSpeaker.m_atVidDec[wChanIndex].m_tRtcpAddr.SetIP(dwEqpIP);
		m_cSpeaker.m_atVidDec[wChanIndex].m_tBackRtcpAddr.SetIP(dwEqpIP);
	}
	m_cSpeaker.m_tSingleVidDec.m_tRtpAddr.SetIP(dwEqpIP);
	m_cSpeaker.m_tSingleVidDec.m_tRtcpAddr.SetIP(dwEqpIP);
	m_cSpeaker.m_tSingleVidDec.m_tBackRtcpAddr.SetIP(dwEqpIP);

	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{		
		m_cSpeaker.m_atAudDec[wChanIndex].m_tRtpAddr.SetIP(dwEqpIP);
		m_cSpeaker.m_atAudDec[wChanIndex].m_tRtcpAddr.SetIP(dwEqpIP);
		m_cSpeaker.m_atAudDec[wChanIndex].m_tBackRtcpAddr.SetIP(dwEqpIP);
	}
	

	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		m_cChair.m_atVidDec[wChanIndex].SetIP(dwEqpIP);
	}
	
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{		
		m_cChair.m_atAudDec[wChanIndex].SetIP(dwEqpIP);
	}

	m_cSpeaker.m_tAudMixDec.m_tRtpAddr.SetIP(dwEqpIP);
	m_cSpeaker.m_tAudMixDec.m_tRtcpAddr.SetIP(dwEqpIP);
	m_cSpeaker.m_tAudMixDec.m_tBackRtcpAddr.SetIP(dwEqpIP);
	
	m_pcDual->ResetMediaIp(tConfDs);

	return ;
}

void CUmsConfInst::ResetNbIp(const TEqpRes& tConfNb)
{
	u32 wEqpIP = tConfNb.m_dwEqpIp;
	u16 wIndex;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{	
		m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtpAddr.SetIP(wEqpIP);
		m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtcpAddr.SetIP(wEqpIP);
		m_cSpeaker.m_atVidBuf[wIndex].m_wSndAddr.SetIP(wEqpIP);
		m_cSpeaker.m_atVidBuf[wIndex].m_tRmtRtcpAddr = m_cSpeaker.m_atVidDec[wIndex].m_tBackRtcpAddr;
	}

	m_cSpeaker.m_tSingleVidBuf.m_tRcvRtpAddr.SetIP(wEqpIP);
	m_cSpeaker.m_tSingleVidBuf.m_tRcvRtcpAddr.SetIP(wEqpIP);
	m_cSpeaker.m_tSingleVidBuf.m_wSndAddr.SetIP(wEqpIP);
	m_cSpeaker.m_tSingleVidBuf.m_tRmtRtcpAddr = m_cSpeaker.m_tSingleVidDec.m_tBackRtcpAddr;

	m_pcDual->ResetNbIp(tConfNb);
}

BOOL32 CUmsConfInst::DaemonObjectInit(u32 wParam, u32 lParam)
{
	if (m_bInit)
	{
		return TRUE;
	}
	
	SetLogTitle("[CUmsConfInst]");

	OspSemTake(g_confInstDaemonQuitSem);
	
	m_pcRegMgr = new CUmsRegMgr(this);
	if (NULL == m_pcRegMgr)
	{
		ObjError(("DaemonInit malloc CUmsRegMgr failed\n"));
		return FALSE;
	}
	
	m_pcVmpTpHandle = new CVmpServiceHandler;
	if (NULL == m_pcVmpTpHandle)
	{
		ObjError(("DaemonInitmalloc CVmpServiceHangdle failed\n"));
		return FALSE;
	}

	m_pcTvWallMgr = new CTvWallMgr(this);
	if (NULL == m_pcTvWallMgr)
	{
		ObjError(("DaemonInit malloc CTvWallMgr failed\n"));
		DaemonObjectExit();
		return FALSE;
	}
	m_pcTvWallMgr->Create();

//////////////////////////////////////////////////////////////////////////
//以下为针对本级会场的接收地址，按照UMS最大的屏接入数192制定
	//级联间消息：主席下传码流、广播类码流
	m_cCascadeChairAddrMgr.Create(TP_UMS_MAX_CASCADECHANNUM / TP_MAX_STREAMNUM);

	//所有本级会场的接收地址：主流、小码流、双流、混音
	m_cLocChanAddrMgr.Create(TP_UMS_MAX_CHANNUM);
	m_cLocSmallChanAddrMgr.Create(TP_UMS_MAX_CHANNUM);
	m_clocDualAddrMgr.Create(TP_UMS_MAX_CHANNUM);
	m_clocMixAddrMgr.Create(TP_UMS_MAX_CHANNUM/TP_MAX_STREAMNUM);
    //轮询
	m_cLocPollAddrMgr.Create(TP_UMS_MAX_CONFNUM * MAX_POLL_CHANNEL_NUM);
	//点名
	m_cLocRollAddrMgr.Create(TP_UMS_MAX_CONFNUM * MAX_ROLL_CHANNEL_NUM);	

	m_cPutAudAddrMgr.Create(TP_UMS_MAX_CONFNUM * MAX_PUTAUD_CHANNEL_NUM);
	m_cEapuAddrMgr.Create(TP_UMS_MAX_CONFNUM * TP_APU2_MAX_CHAN_NUM);

	m_pcCallDs = new CDsList();
	if (NULL == m_pcCallDs)
	{
		ObjError(("DaemonInit malloc CCallDsNodeBuf failed\n"));
		return FALSE;
	}
	m_pcCallDs->Create(50000);

	m_pcGetVidEx = new CGetVidAudEx;
	if (NULL == m_pcGetVidEx)
	{
		ObjError(("DaemonInit malloc CGetVidAudEx failed\n"));
		return FALSE;
	}
	
	m_pcTimerMgr = new CTpTimerMgr;
	if (NULL == m_pcTimerMgr)
	{
		ObjError(("DeamonInit malloc CTpTimerMgr failed\n"));
		return FALSE;
	}
	m_pcTimerMgr->Create(100);
	SetTimer(evtp_TimerMgrTimer_Tick, TP_INTERVAL_TIME_ONE_SECOND);

	return CTpObject::DaemonObjectInit(wParam, lParam);
}

void CUmsConfInst::DaemonObjectExit(void)
{
	if (NULL != m_pcRegMgr)
	{
		delete m_pcRegMgr;
		m_pcRegMgr = NULL;
	}

	if (NULL != m_pcVmpTpHandle)
	{
		delete m_pcVmpTpHandle;
		m_pcVmpTpHandle = NULL;
	}

	if (NULL != m_pcTvWallMgr)
	{
		delete m_pcTvWallMgr;
		m_pcTvWallMgr = NULL;
	}

	KillTimer(evtp_TimerMgrTimer_Tick);
	if (NULL != m_pcTimerMgr)
	{
		delete m_pcTimerMgr;
		m_pcTimerMgr = NULL;
	}

	m_clocDualAddrMgr.Destroy();
	m_clocMixAddrMgr.Destroy();
	m_cLocChanAddrMgr.Destroy();
	m_cLocSmallChanAddrMgr.Destroy();
	m_cCascadeChairAddrMgr.Destroy();
	m_cLocPollAddrMgr.Destroy();
	m_cLocRollAddrMgr.Destroy();
	m_cPutAudAddrMgr.Destroy();
	m_cEapuAddrMgr.Destroy();
	m_cAddrList.Destroy();

	if (NULL != m_pcCallDs)
	{
		delete m_pcCallDs;
		m_pcCallDs = NULL;
	}


	if (NULL != m_pcGetVidEx)
	{
		delete m_pcGetVidEx;
		m_pcGetVidEx = NULL;
	}

	CTpObject::DaemonObjectExit();

	OspSemGive(g_confInstDaemonQuitSem);
}

void CUmsConfInst::DaemonInitCfg(CTpMsg *const ptMsg,CApp* pcApp)
{
	TUmsCallCfg& tCfg = *(TUmsCallCfg*)ptMsg->GetBody();

	m_tCallCfg.m_wMaxOnceCall = tCfg.m_wMaxOnceCall;
	m_tCallCfg.m_wStartPort = tCfg.m_wStartPort;

	DaemonInitPort(pcApp);
	
	CTpMsg cMsg;
	cMsg.SetEvent( EVTP_RUNNING );
	cMsg.Post( UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR,CInstance::DAEMON) );
}

void CUmsConfInst::DaemonInitPort(CApp* pcApp)
{
	u16 wStartPort = m_tCallCfg.m_wStartPort;

	wStartPort = DaemonInitLocalAddr(wStartPort);
	wStartPort = DaemonInitCascadeChairAddr(wStartPort);

	CInstance* pcInst;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = pcApp->GetInstance(wIndex);
		wStartPort = ((CUmsConfInst*)pcInst)->InitPort(wStartPort);
	}

	wStartPort = DaemonInitPollAddr(wStartPort);
	wStartPort = DaemonInitRollAddr(wStartPort);
	wStartPort = DaemonInitPutAudAddr(wStartPort);
	wStartPort = DaemonInitEapuAddr(wStartPort);

	u16 wAddrListBeginPort = wStartPort;
	const u16 wMAXPORT = UMS_EP_TRANS_END_PORT;
	if ( wStartPort < wMAXPORT - 2 )
	{//此处分配最大量的动态端口
		m_cAddrList.Create((wMAXPORT-wStartPort)/2-1);
		
		TTPMediaTransAddr* ptChan = NULL;
		//接收视频地址
		for (u16 wIndex = 0; wIndex < m_cAddrList.GetTotalNum(); ++wIndex)
		{
			ptChan = m_cAddrList.GetDataByIndex(wIndex);
			ptChan->m_tRtpAddr.SetAddr(GetLocalIP(), wStartPort);
			ptChan->m_tBackRtcpAddr.SetAddr(GetLocalIP(), wStartPort+1);
			wStartPort += 2;
		}
	}
	else
	{
		printf("DaemonInitPort no space port for m_cAddrList!!! wAddrListBeginPort:%d, wMAXPORT:%d.\n", wAddrListBeginPort, wMAXPORT);
	}
	
	printf("DaemonInitPort ums start port:%d! AddrList Begin:%d, End:%d, AddrlistNum:%d.\n", 
		m_tCallCfg.m_wStartPort, wAddrListBeginPort, wStartPort, m_cAddrList.GetTotalNum());
}
 
u16 CUmsConfInst::DaemonInitLocalAddr(u16 wStartPort)
{
	u32 dwIndex = 0;

	u16 wOffsetPort = wStartPort;	
	u16 wChanIndex = 0;
	u32 dwIP = GetLocalIP();
	
	TChanRcvAddr* ptVirLocalNode = NULL;
	TLocalChanAddr* ptChan;
	u32 dwTotalLocalChan = m_cLocChanAddrMgr.GetTotalNum();

	//主流视频和音频
    for (dwIndex = 0; dwIndex < dwTotalLocalChan; ++dwIndex)
    {
		ptChan = m_cLocChanAddrMgr.GetDataByIndex(dwIndex);

		ptVirLocalNode = &ptChan->m_tVid;
		ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);
		wOffsetPort += 4;

		ptVirLocalNode = &ptChan->m_tAud;
		ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);		
		wOffsetPort += 4;
    }

	printf("DaemonInitLocalAddr LocalEpVidAudAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);
	wStartPort = wOffsetPort;

	TSingleScreenAddr* ptDual;
	
	dwTotalLocalChan = m_clocDualAddrMgr.GetTotalNum();

	//双流视频和音频
	for (dwIndex = 0; dwIndex <dwTotalLocalChan;  ++dwIndex)
    {		
		ptDual = m_clocDualAddrMgr.GetDataByIndex(dwIndex);

		ptDual->m_tVid.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptDual->m_tVid.m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptDual->m_tVid.m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);
		wOffsetPort += 4;

		ptDual->m_tAud.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptDual->m_tAud.m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptDual->m_tAud.m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);
		wOffsetPort += 4;
    }

	printf("DaemonInitLocalAddr LocalEpDualVidAudAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);
	wStartPort = wOffsetPort;

	dwTotalLocalChan = m_cLocSmallChanAddrMgr.GetTotalNum();
	//接收小码流视频地址
	for (dwIndex = 0; dwIndex < dwTotalLocalChan; ++dwIndex)
	{		
		ptVirLocalNode = m_cLocSmallChanAddrMgr.GetDataByIndex(dwIndex);

		ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);
		wOffsetPort += 4;
	}

	printf("DaemonInitLocalAddr LocalEpSmallVidAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);
	wStartPort = wOffsetPort;

	TChanRcvAddr* ptMixRcv;
	//混音码流接收地址
	for (dwIndex = 0; dwIndex < m_clocMixAddrMgr.GetTotalNum(); ++dwIndex)
	{		
		ptMixRcv = m_clocMixAddrMgr.GetDataByIndex(dwIndex);				
		ptMixRcv->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptMixRcv->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptMixRcv->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);
		wOffsetPort += 4;
	}

	printf("DaemonInitLocalAddr LocalEpMixAudAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);

	return wOffsetPort;
}

u16 CUmsConfInst::DaemonInitCascadeChairAddr(u16 wStartPort)
{
	u32 dwTotalNum = m_cCascadeChairAddrMgr.GetTotalNum();
	u32 dwFreeBlockNum = m_cCascadeChairAddrMgr.GetFreeBlocks();
	u32 dwIndex = 0;
	
	if (dwTotalNum != dwFreeBlockNum)
	{
		msgprint("DaemonInitCascadeChairAddr::InitPort error!\n");
		return wStartPort;
	}
	
	u16 wOffsetPort = wStartPort;	
	u16 wChanIndex = 0;
	u32 dwIP = GetLocalIP();
	
	TChanRcvAddr* ptVirLocalNode = NULL;
	TCascadeChairAddr* itor;
		
	//级联主席通道接收地址
	for (dwIndex = 0; dwIndex < dwTotalNum; ++dwIndex)
    {	

		itor = m_cCascadeChairAddrMgr.GetDataByIndex(dwIndex);
		for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
		{
			ptVirLocalNode = &itor->m_atVid[wChanIndex];
			ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
			ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
			ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);
			wOffsetPort += 4;
		}

		itor = m_cCascadeChairAddrMgr.GetDataByIndex(dwIndex);		
		for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
		{
			ptVirLocalNode = &itor->m_atAud[wChanIndex];
			ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
			ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
			ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);		
			wOffsetPort += 4;
		}
		
		//混音
		ptVirLocalNode = &itor->m_tMixAud;
		ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);		
		wOffsetPort += 4;

		//讨论内单屏广播 vid
		ptVirLocalNode = &itor->m_tDisSingleVid;
		ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);		
		wOffsetPort += 4;

		//讨论内单屏广播 aud
		ptVirLocalNode = &itor->m_tDisSingleAud;
		ptVirLocalNode->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptVirLocalNode->m_tRtcpForRcv.SetAddr(dwIP, wOffsetPort+1);
		ptVirLocalNode->m_tRtcpForSnd.SetAddr(dwIP, wOffsetPort+3);		
		wOffsetPort += 4;
    }

	printf("DaemonInitCascadeChairAddr LocalCascadeChairAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);

	return wOffsetPort;
}


u16 CUmsConfInst::DaemonInitPollAddr(u16 wStartPort)
{
	u32 dwTotalNum = m_cLocPollAddrMgr.GetTotalNum();
	u32 dwIP = GetLocalIP();
	u16 wOffsetPort = wStartPort;
	TTPMediaTransAddr* ptPollChan = NULL;
	//轮询地址
	for (u16 wIndex = 0; wIndex < dwTotalNum; ++wIndex)
	{
		ptPollChan = m_cLocPollAddrMgr.GetDataByIndex(wIndex);
		ptPollChan->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptPollChan->m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
		wOffsetPort += 2;
	}

	printf("DaemonInitPollAddr LocalPollAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);
	
	return wOffsetPort;
}


u16 CUmsConfInst::DaemonInitRollAddr(u16 wStartPort)
{
	u32 dwTotalNum = m_cLocRollAddrMgr.GetTotalNum();
	u32 dwIP = GetLocalIP();
	u16 wOffsetPort = wStartPort;
	TTPMediaTransAddr* ptRollChan = NULL;
	//点名地址
	for (u16 wIndex = 0; wIndex < dwTotalNum; ++wIndex)
	{
		ptRollChan = m_cLocRollAddrMgr.GetDataByIndex(wIndex);
		ptRollChan->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptRollChan->m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
		wOffsetPort += 2;
	}
	
	printf("DaemonInitRollAddr LocalRollAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);
	
	return wOffsetPort;
}


u16 CUmsConfInst::DaemonInitPutAudAddr(u16 wStartPort)
{
	u32 dwTotalNum = m_cPutAudAddrMgr.GetTotalNum();
	u32 dwIP = GetLocalIP();
	u16 wOffsetPort = wStartPort;
	TTPMediaTransAddr* ptPutAudChan = NULL;

	for (u16 wIndex = 0; wIndex < dwTotalNum; ++wIndex)
	{
		ptPutAudChan = m_cPutAudAddrMgr.GetDataByIndex(wIndex);
		ptPutAudChan->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptPutAudChan->m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
		wOffsetPort += 2;
	}
	
	printf("DaemonInitPutAudAddr PutAudAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);
	
	return wOffsetPort;
}

u16 CUmsConfInst::DaemonInitEapuAddr(u16 wStartPort)
{
	u32 dwTotalNum = m_cEapuAddrMgr.GetTotalNum();
	u32 dwIP = GetLocalIP();
	u16 wOffsetPort = wStartPort;
	TTPMediaTransAddr* ptEapuChan = NULL;

	for (u16 wIndex = 0; wIndex < dwTotalNum; ++wIndex)
	{
		ptEapuChan = m_cEapuAddrMgr.GetDataByIndex(wIndex);
		ptEapuChan->m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
		ptEapuChan->m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
		wOffsetPort += 2;
	}
	
	printf("DaemonInitEapuAddr EapuAddr begin:%d, end:%d.\n", wStartPort, wOffsetPort);
	
	return wOffsetPort;
}





s32 PreOutTimeCB(u32 dwTimerId, void* param)
{
	CUmsConfInst* pcRunTimerDB = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(1));
	u32 dwIndex = (u32)param;
	pcRunTimerDB->SndTimeOut((u16)dwIndex);
	return TP_RET_OK;
}
void CUmsConfInst::SndTimeOut(u16 wIndex)
{		
	TTPConfEpParam* ptEpParam = &(m_tConfEpInfoMrg.m_ConfEpParam[wIndex]);
	if (NULL == ptEpParam)
	{
		ObjError(("SndTimeOut EpParam is null\n"));
		return;
	}
	ObjHint(("SndTimeOut ConfID:%d, Index:%d, name:%s.\n",ptEpParam->m_wConfID,ptEpParam->m_wIndex,
		ptEpParam->m_tCallInfo.m_tSrcAddr.GetValidAlias().m_abyAlias));

	TTpTimer* ptTimer = (TTpTimer*)ptEpParam->m_dwTimerID;
	if (NULL != ptTimer)
	{
		m_pcTimerMgr->DeleteTimer(ptTimer);
		ptEpParam->m_dwTimerID = 0;
	}

	if (ptEpParam->IsUsed())
	{
		EmCnsCallReason emCallRet = EmCnsCallReason_Rejected;
		UmsAnwserCall(ptEpParam->m_tHandle, FALSE, NULL, emCallRet);
		ptEpParam->Clear();	
	}
}
/*==============================================================================
函数名    :  DaemonConfIncomingACK
功能      :  service过来的被叫
算法实现  :  1. 未呼叫
				a. 如果主叫是UMS，启动呼叫
				b. 如果主叫是CNS，拒绝呼叫
			 2. 已经呼叫
				a. 如果主叫是UMS，则判断是否有原主叫，有则拒绝
				b. 如果主叫是CNS，判断CNS是否在呼叫列表，有则无操作，没有则加入呼叫列表
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-4               zhaixiaogang
==============================================================================*/
void CUmsConfInst::DaemonConfIncomingFromService(CTpMsg *const ptMsg,CApp* pcApp)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsCallInfo& tCaller = *(TUmsCallInfo*)((u8*)ptMsg->GetBody() + sizeof(TUmsHandle));
	EmCnsCallReason& tRet = *(EmCnsCallReason*)((u8*)ptMsg->GetBody() + sizeof(TUmsHandle) + sizeof(TUmsCallInfo));

	ObjHint(("DaemonConfIncomingFromService ret(%d->%s), caller type(%d->%s), incoming CallBitRate = %d\n"
		, TpEnumIdString(EmCnsCallReason, tRet), TpEnumIdString(EmTPEndpointType, tCaller.m_emSrcEpType), tCaller.m_wBitRate));

	if (EmCnsCallReason_success != tRet)
	{
		UmsAnwserCall(tHandle, FALSE, NULL, tRet);
		return;
	}

	u8* pDataBuf = (u8*)ptMsg->GetBody() + sizeof(TUmsHandle) + sizeof(TUmsCallInfo) + sizeof(EmCnsCallReason);
	u16 wConfID = *(u16*)pDataBuf;
	TConfTemplateLocal& tConfTemp = *(TConfTemplateLocal*)(pDataBuf + sizeof(wConfID));
	CUmsConfInst* pcInst =  (CUmsConfInst*)pcApp->GetInstance(wConfID);
	if (NULL == pcInst)
	{
		UmsAnwserCall(tHandle, FALSE, NULL, EmCnsCallReason_Local);
		NotifyMsgToService(evtp_UmsConfDisConnect, &wConfID, sizeof(wConfID));
		ObjError(("DaemonConfIncomingFromService inst error. ConfID:%d\n", tHandle.GetConfID()));
		return;
	}

	BOOL32 bConfStart = *(BOOL32*)(pDataBuf + sizeof(wConfID) + sizeof(TConfTemplateLocal));
    if (bConfStart && inst_idle == pcInst->CurState())
	{//会议刚结束，call（已结束） 与server 还没有结束）关于会议的状态还没有来得及同步
		UmsAnwserCall(tHandle, FALSE, NULL, EmCnsCallReason_Busy);
		ObjError(("DaemonConfIncomingFromService, ConfID:%d Is Idle\n", wConfID));
        return;
	}

	EmCnsCallReason emCallRet = EmCnsCallReason_success;
	if (inst_idle == pcInst->CurState())
	{
		if (emTPEndpointTypeCNS == tCaller.m_emSrcEpType||emTPEndpointH323MT == tCaller.m_emSrcEpType || emTPEndpointH323SingleMCU == tCaller.m_emSrcEpType)
		{
			emCallRet = pcInst->OnConfCnsCall(tHandle, tCaller, &tConfTemp);
		}
		else if (emTPEndpointTypeUMS == tCaller.m_emSrcEpType)
		{
			emCallRet = pcInst->OnConfUmsCall(tHandle, tCaller, tConfTemp);
		}
		else
		{
			ObjError(("DaemonConfIncomingFromService inst Idle. reject call. unknow caller ConfID:%d, caller type:%d\n", tHandle.GetConfID(), tCaller.m_emSrcEpType));
			emCallRet = EmCnsCallReason_hungup;
		}

		if (EmCnsCallReason_success != emCallRet)
		{
			MdlError(Ums_Mdl_Call, ("DaemonConfIncomingFromService failed! wConfID:%d, ConfTemp:%s, CallRet:%d\n", 
																				GetInsID(), tConfTemp.m_achConfName, emCallRet));
			UmsAnwserCall(tHandle, FALSE, NULL, emCallRet);
			NotifyMsgToService(evtp_UmsConfDisConnect, &wConfID, sizeof(wConfID));
		}
	}
	else
	{
		do 
		{

			if ( strcmp(tCaller.m_tSrcAddr.m_tAlias.m_abyAlias, pcInst->m_tConfBaseInfo.m_achConfName) == 0)
			{
				emCallRet = EmCnsCallReason_Busy;
				break;
			}

			if (emTpSIP == tCaller.m_emTpProtocol &&
				(tCaller.m_tEncrypt.m_emEncryptModel == emTPEncryptTypeQtEverySecond ||
				tCaller.m_tEncrypt.m_emEncryptModel == emTPEncryptTypeQtEveryMinute ||
				tCaller.m_tEncrypt.m_emEncryptModel == emTPEncryptTypeQtEveryConf))
			{
   	            if (pcInst->m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel != emTPEncryptTypeQtEverySecond &&
					pcInst->m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel != emTPEncryptTypeQtEveryMinute &&
					pcInst->m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel != emTPEncryptTypeQtEveryConf )
				{
					MdlError(Ums_Mdl_Service, ("[DaemonConfIncomingFromService]  Encrypt not equal! caller enc:%d; conftemplate enc:%d. \n", 
						tCaller.m_tEncrypt.m_emEncryptModel, pcInst->m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel) );
					
					tRet = EmCnsCallReason_Rejected;
					break;;
				}
			}

			//判断会场是否在列表中
			u16  wCallerEpID = TP_CONF_MAX_CNSNUM;
			BOOL32 bExist = FALSE;
			for (TCallNode* ptNode = pcInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pcInst->m_pcNodeMgr->NextLoalNode(ptNode))
			{
				if (tCaller.m_tSrcAddr.m_bAliasIP)
				{
					if (ptNode->m_tCalledAddr.m_dwIP == tCaller.m_tSrcAddr.m_dwIP 
						&& (ptNode->m_tCalledAddr.m_tAlias == tCaller.m_tSrcAddr.m_tAlias || 
						    ptNode->m_tCalledAddr.m_tE164 == tCaller.m_tSrcAddr.m_tE164))
					{
						wCallerEpID = ptNode->m_wEpID;
						bExist = TRUE;
						break;
					}
				}
				else
				{
					if (!tCaller.m_tSrcAddr.m_tAlias.IsInValid())
					{
						if (ptNode->m_tCalledAddr.m_tAlias == tCaller.m_tSrcAddr.m_tAlias )
						{
							wCallerEpID = ptNode->m_wEpID;
							bExist = TRUE;
							break;
						}
					}
					if (!tCaller.m_tSrcAddr.m_tE164.IsInValid())
					{
						if (ptNode->m_tCalledAddr.m_tE164 == tCaller.m_tSrcAddr.m_tE164)
						{
							wCallerEpID = ptNode->m_wEpID;
							bExist = TRUE;
							break;
						}
					}
					if (0 != tCaller.m_tSrcAddr.m_dwIP)
					{
						if (ptNode->m_tCalledAddr.m_dwIP == tCaller.m_tSrcAddr.m_dwIP)
						{
							wCallerEpID = ptNode->m_wEpID;
							bExist = TRUE;
							break;
						}
					}
				}
			}


            if (pcInst->m_bIsNeedDelayCallNode)
			{
				if (!(bExist && wCallerEpID == pcInst->chairID()))
				{
					emCallRet = EmCnsCallReason_Busy;
				    break;
				} 
			}

			if (!bExist && tCaller.m_emSrcEpType != emTPEndpointTypeUMS && emTPEndpointH323SingleMCU != tCaller.m_emSrcEpType ) 
			{
				//查找空闲位置保存Ep参数
				static u16 wEpIndex = 0;

				u16 wForNum = 0;
				u16 wIndex = wEpIndex;
				do 
				{
					if ( wForNum >= 2 )
					{
						break ;
					}
					//依次往下找
					if ( wIndex >= TP_UMS_MAX_CALLNUM )
					{
						wForNum ++;
						wIndex = 0;
					}
					
					if (!m_tConfEpInfoMrg.m_ConfEpParam[wIndex].IsUsed())
					{
						wEpIndex = wIndex + 1;
						break;
					}
					
					wIndex ++;
					
				} while (TRUE);

				if ( wForNum >= 2 )
				{
					emCallRet = EmCnsCallReason_Local ;
					MdlError(Ums_Mdl_Call,("DaemonConfIncomingFromService. EpParam Full ConfID:%d,CallAddr:%s,CallReason:%d\n",
						wConfID,tCaller.m_tSrcAddr.GetValidAlias().m_abyAlias,emCallRet));
					break;
				}

				TTPConfEpParam* ptEpParam = &(m_tConfEpInfoMrg.m_ConfEpParam[wIndex]);
				if (NULL == ptEpParam )
				{
					emCallRet = EmCnsCallReason_Local ;
					MdlError(Ums_Mdl_Call,("DaemonConfIncomingFromService. EpParam Error ConfID:%d,CallAddr:%s,CallReason:%d\n",
									wConfID,tCaller.m_tSrcAddr.GetValidAlias().m_abyAlias,emCallRet));
					break;
				}
				ptEpParam->m_bUsed = TRUE;
				ptEpParam->m_wConfID = wConfID;
				memcpy(&ptEpParam->m_tHandle, &tHandle, sizeof(tHandle));
				memcpy(&ptEpParam->m_tCallInfo, &tCaller, sizeof(tCaller));

				TTpTimer* ptTimer = m_pcTimerMgr->AddTimer(TP_JOINCONF_TIME , PreOutTimeCB , (void *)(ptEpParam->m_wIndex));
				if (NULL == ptTimer)
				{
					emCallRet = EmCnsCallReason_Local ;
					MdlError(Ums_Mdl_Call, ("DaemonConfIncomingFromService. AddTimer Failed. ConfID:%d, ConfName:%s, CallReason:%d\n",
						wConfID,tCaller.m_tSrcAddr.GetValidAlias().m_abyAlias, emCallRet));
					break;
				}
				ptEpParam->m_dwTimerID = (u32)ptTimer;

				MdlHint(Ums_Mdl_Call, ("DaemonConfIncomingFromService Ep want to join conf... ConfID:%d, Index:%d, Name:%s.\n",
					wConfID, ptEpParam->m_wIndex, tCaller.m_tSrcAddr.GetValidAlias().m_abyAlias));

				TTPConfEpInfo tInfo;
				tInfo.m_wConfID = wConfID;
				tInfo.m_Index = ptEpParam->m_wIndex;
				tInfo.m_bPermit = FALSE;
				memcpy(&tInfo.m_tCallAddr, &tCaller.m_tSrcAddr, sizeof(tCaller.m_tSrcAddr));

				//  通知 cnc  umc有会场请求入会
				pcInst->NotifyConfCtrlMsgToCns(evtp_CnsJoinConf_Req, pcInst->chairID(), &tInfo, sizeof(tInfo));
				TLogUser tUserTmp;		
				pcInst->NotifyMsgToServiceForUI(evtp_UmsJoinConf_Req,&tInfo,sizeof(tInfo),&tUserTmp);
				return;
			}
			else				
			{
				emCallRet = pcInst->OnCnsCallExistConf(tHandle, tCaller);
			}

		} while (0);

		if (EmCnsCallReason_success != emCallRet)
		{
			UmsAnwserCall(tHandle, FALSE, NULL, emCallRet);
			MdlError(Ums_Mdl_Call,("DaemonConfIncomingFromService.Call Conf fail.ConfID:%d,ConfName:%s,CallReason:%d\n",
							wConfID,tCaller.m_tSrcAddr.GetValidAlias().m_abyAlias,emCallRet));
		}
	}
}


void CUmsConfInst::AdapterReg()
{
	m_pcNodeMgr->SetLastCallNode(NULL);
	CallAllLocalNode();
}

void CUmsConfInst::AdapterQuit(TEqpRes& tEqp)
{	
	u16 wConfID = GetInsID();
	MdlHint(Ums_Mdl_Call, ("AdapterQuit ConfID:%d, node:%d\n", wConfID, tEqp.m_dwEqpNode));

	u32 dwAdapterID = tEqp.m_dwEqpNode;
	TCapNode* ptCallerNode = m_pcNodeMgr->GetCaller();
	if (ptCallerNode->m_bUsed && dwAdapterID == ptCallerNode->m_tAdapterEqp.m_dwEqpNode)
	{
		MdlHint(Ums_Mdl_Call, ("AdapterQuit Caller disconnect ,hungup conf! ConfID:%d, node:%d\n", wConfID, tEqp.m_dwEqpNode));	
		
		SelfHungupImmediately(TP_UMS_AdapterQuit);
		return;
	}
	
	EmCnsCallReason emAppReason = EmCnsCallReason_Rejected;
	TUmsHandle tHandle;
	
	CTpMsg cMsg;	
	cMsg.SetEvent(evtp_Conf_UmsCallDisConnect);	
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->m_bUsed || dwAdapterID != ptNode->m_tAdapterEqp.m_dwEqpNode)
		{
			continue;	
		}		

		TAdaptEqpParam tAdapterEqp;
		tAdapterEqp.m_ptEqpRes = &ptNode->m_tAdapterEqp;
		ReleaseEqpEx(&tAdapterEqp);
		ptNode->m_tAdapterEqp.Clear();

		MdlHint(Ums_Mdl_Call, ("AdapterQuit node disconnect, ConfID:%d, wEpID:%d\n", wConfID, ptNode->m_wEpID));
		m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
		
		cMsg.SetBody(&tHandle, sizeof(tHandle));
		cMsg.CatBody(&emAppReason, sizeof(emAppReason));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, UMS_SIPADAPTER_APP_INST);
	}
}

void CUmsConfInst::MediaReg(TEqpRes& tEqp)
{
	MdlHint(Ums_Mdl_Call, ("MediaReg ConfStart, ConfID:%d, CurSwitch:%d, NewSwitch:%d\n"
		, GetInsID(), m_tEqpConfDs.m_wEqpIndex, tEqp.m_wEqpIndex));

	if (!m_tEqpConfDs.IsValid() && m_pcNodeMgr->AssignDsRes(FALSE, &m_tEqpConfDs))
	{//此处会议转发板掉线 需要重新分配并恢复 未完成
		ResetMediaIp(m_tEqpConfDs);
		CNetPortMgr::CreateVirSpeakerTrans(this);
	}	
	CNetPortMgr::CreateSpeakerToVirSpeaker(this);
}

void CUmsConfInst::MediaUnReg(TEqpRes& tEqp)
{
	EmCnsCallReason emAppReason = EmCnsCallReason_Unreachable;
	TUmsHandle tHandle;
	
	if (m_tEqpConfDs.m_wEqpIndex == tEqp.m_wEqpIndex)
	{//此处会议转发板掉线 需要重新分配并恢复 未完成
		
		SelfHungupImmediately(TP_UMS_MediaTransQuit);
		
		MdlHint(Ums_Mdl_Call, ("MediaUnReg node disconnect, hungup conf! ConfID:%d,\n", GetInsID()));
		return;
	}
	else
	{
		CTpMsg cMsg;	
		cMsg.SetEvent(evtp_Conf_UmsCallDisConnect);	
		for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
		{
			if(!ptNode->m_bUsed || ptNode->m_tMediaEqp.m_wEqpIndex != tEqp.m_wEqpIndex)
			{
				continue;	
			}
			
			MdlHint(Ums_Mdl_Call, ("MediaUnReg node disconnect, ConfID:%d, wEpID:%d\n", GetInsID(), ptNode->m_wEpID));
			m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			
			cMsg.SetBody(&tHandle, sizeof(tHandle));
			cMsg.CatBody(&emAppReason, sizeof(emAppReason));
			
			OnCallDisConnect(&cMsg, FALSE); 
			
			ptNode->m_emCallReason = EmCnsCallReason_Abnormal;
		}	
	}

	for (u16 wIndex = 0; wIndex < UMS_CONF_MAX_DS_NUM; ++wIndex)
	{
		if (m_atDsEqp[wIndex].m_wEqpIndex == tEqp.m_wEqpIndex)
		{
			m_atDsEqp[wIndex].Clear();
		}
	}	
	
	KillTimer(evtp_CallNode_time);
	SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
}

u32  CUmsConfInst::GetNodeFromMediaIp(const u32 dwIp)
{
	u32 dwNode = 0;
	for (u16 wIndex = 0; wIndex < UMS_CONF_MAX_DS_NUM; ++wIndex)
	{
		TIpmaskinfo* ptInfo = CUmsConfInst::m_tMediaNetWorkManger.Get(m_atDsEqp[wIndex].m_dwEqpNode);
		if (NULL != ptInfo)
		{
			// 双网段 ip判断
			if (dwIp == ptInfo->m_dwIpa || dwIp == ptInfo->m_dwIpb)
			{
				dwNode = m_atDsEqp[wIndex].m_dwEqpNode;
				break;
			}
		}
		else
		{	
			if (dwIp == m_atDsEqp[wIndex].m_dwEqpIp)
			{
				dwNode = m_atDsEqp[wIndex].m_dwEqpNode;
				break;
			}
		}
	}
	return dwNode;
}

void CUmsConfInst::DaemonConfInvalidAppHandleProc(CTpMsg *const ptMsg,CApp* pcApp)
{
	CUmsConfInst* pcInst;
	CTpMsg cMsg;
	memcpy(&cMsg, ptMsg, sizeof(CTpMsg));
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		if( pcInst->ConfInvalidAppHandleProc(&cMsg) )
		{
			return;
		}
	}
}

BOOL32 CUmsConfInst::ConfInvalidAppHandleProc(CTpMsg *ptMsg)
{
	TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();

	TCapNode* ptNode = NULL;
	for (ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->m_bUsed)
		{
			continue;
		}

		if ( ptNode->m_dwStackHandle == ptHandle->handPaCall )
		{
			ptHandle->MakeAppHandle(GetInsID(), ptNode->m_wEpID);

			MdlHint(Ums_Mdl_Call, ("ConfInvalidAppHandleProc. ConfID:%d, EpID:%d, PaHandle:%d, UmsHandle(ConfID:%d,EpID:%d, PaHandle:%d)\n", 
							GetInsID(), ptNode->m_wEpID, ptNode->m_dwStackHandle, ptHandle->GetConfID(), ptHandle->GetEpID(), ptHandle->handPaCall));

			MessageProc(ptMsg);

			return TRUE;
		}
	}

	return FALSE;
}

void CUmsConfInst::DaemonConfAdapterReg(CTpMsg *const ptMsg,CApp* pcApp)
{
	MdlHint(Ums_Mdl_Call, ("DaemonConfAdapterReg \n"));
	m_pcRegMgr->Handler(ptMsg);

	CUmsConfInst* pcInst;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		pcInst->AdapterReg();
	}
}

void CUmsConfInst::DaemonConfAdapterUnReg(CTpMsg *const ptMsg,CApp* pcApp)
{
	TEqpRes tEqp;
	TP_SAFE_CAST(tEqp, ptMsg->GetBody());
	MdlHint(Ums_Mdl_Call, ("DaemonConfAdapterUnReg disconnect node:%d\n", tEqp.m_dwEqpNode));

	m_pcRegMgr->Handler(ptMsg);

	CUmsConfInst* pcInst;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		pcInst->AdapterQuit(tEqp);
	}
}

void CUmsConfInst::DaemonConfMediaReg(CTpMsg *const ptMsg,CApp* pcApp)
{
	TEqpRes tEqp;
	TP_SAFE_CAST(tEqp, ptMsg->GetBody());
	TIpmaskinfo tIpmask;
	TP_SAFE_CAST(tIpmask, ptMsg->GetBody()+sizeof(tEqp));

	MdlHint(Ums_Mdl_Call, ("DaemonConfMediaReg node:%d, Index:%d\n", tEqp.m_dwEqpNode, tEqp.m_wEqpIndex));

	MdlHint(Ums_Mdl_Call, ("DaemonConfMediaReg. Ipa:"TPIPFORMAT", maska:"TPIPFORMAT", ipb:"TPIPFORMAT", maskb:"TPIPFORMAT", LocalOutIp:"TPIPFORMAT",IsSame:%d.\n", 
		Tpu32ToIP(tIpmask.m_dwIpa), Tpu32ToIP(tIpmask.m_dwMaska), Tpu32ToIP(tIpmask.m_dwIpb), Tpu32ToIP(tIpmask.m_dwMaskb), Tpu32ToIP(tIpmask.m_dwOutIp),tIpmask.IsSameNetwork()));


	if (!tIpmask.IsSameNetwork())
	{
		m_tMediaNetWorkManger.Add(&tIpmask, tEqp.m_dwEqpNode);
	}

	u16 wEqpIndex = tEqp.m_wEqpIndex;
	if (!TP_VALID_HANDLE(wEqpIndex))
	{
		MdlError(Ums_Mdl_Call, ("DaemonConfMediaReg eqpindex error!node:%d, Index:%d, "TPIPFORMAT"!", 
			tEqp.m_dwEqpNode, tEqp.m_wEqpIndex, Tpu32ToIP(tEqp.m_dwEqpIp)));
		return;
	}

	CUmsConfInst* pcInst;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		pcInst->MediaReg(tEqp);
	}
}

void CUmsConfInst::DaemonConfMediaUnReg(CTpMsg *const ptMsg,CApp* pcApp)
{
	TEqpRes tEqp;
	TP_SAFE_CAST(tEqp, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Call, ("DaemonConfMediaReg node:%d, Index:%d\n", tEqp.m_dwEqpNode, tEqp.m_wEqpIndex));
	
	u16 wEqpIndex = tEqp.m_wEqpIndex;
	if (!TP_VALID_HANDLE(wEqpIndex))
	{
		MdlError(Ums_Mdl_Call, ("DaemonConfMediaUnReg eqpindex error!node:%d, Index:%d, "TPIPFORMAT".\n", 
			tEqp.m_dwEqpNode, tEqp.m_wEqpIndex, Tpu32ToIP(tEqp.m_dwEqpIp)));
		return;
	}
	
	m_tMediaNetWorkManger.Del(tEqp.m_dwEqpNode);

	CUmsConfInst* pcInst;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		pcInst->MediaUnReg(tEqp);
	}
}

void CUmsConfInst::DaemonConfAudMixReg( CTpMsg *const ptMsg, CApp* pcApp )
{
	TEqpRes tEqp;
	TP_SAFE_CAST(tEqp, ptMsg->GetBody());
	
	MdlHint(Ums_Mdl_Call, ("DaemonConfAudMixReg Connect node:%d\n", tEqp.m_dwEqpNode));
	
	CUmsConfInst* pcInst;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		pcInst->m_pcEapu->Handler(ptMsg);
	}

	return ;
}

void CUmsConfInst::DaemonConfMpcInfo( CTpMsg *const ptMsg, CApp* pcApp )
{
	TP_SAFE_CAST(m_bMpcReged, ptMsg->GetBody());
	if (!m_bMpcReged)
	{
	}
}

void CUmsConfInst::DaemonConfAudMixUnReg( CTpMsg *const ptMsg, CApp* pcApp )
{
	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("DaemonConfAudMixUnReg disconnect EqpID:%d\n", byEqpID));

	CUmsConfInst* pcInst;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		pcInst->m_pcEapu->Handler(ptMsg);
	}

	return ;
}

void CUmsConfInst::DaemonConfVmpProc( CTpMsg *const ptMsg, CApp* pcApp )
{
	u16 wEvent = ptMsg->GetEvent();
	if ( wEvent == evtp_UmsVmpReg_Notify )
	{
		CUmsVmp::OnVmpConnect(ptMsg);
	}
	else if ( wEvent == evtp_UmsVmpUnReg_Notify )
	{
		CUmsVmp::OnVmpDisConnect(ptMsg);
	}
	else if ( wEvent == evtp_VmpToCall_NAck )
	{
		CUmsVmp::OnVmpNAck(ptMsg);
	}

	return ;
}

void CUmsConfInst::DaemonConfBasMsgProc( CTpMsg *const ptMsg, CApp* pcApp )
{
	MdlHint(Ums_Mdl_Call, ("DaemonConfBasMsgProc event:%d\n", ptMsg->GetEvent()));
	
	CUmsConfInst* pcInst = NULL;
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		pcInst = (CUmsConfInst*)pcApp->GetInstance(wIndex);
		if (inst_idle == pcInst->CurState())
		{
			continue;
		}
		
		pcInst->m_pcBas->Handler(ptMsg);
	}
	return ;	
}


void CUmsConfInst::EventUserLogin(CTpMsg *const ptMsg)
{
	TLogUser* ptUserTmp = (TLogUser*)ptMsg->GetBody();

	if ( CurState() == CUmsConfInst::inst_idle || m_bIsQuiting )
	{
		return ;
	}

	TAddConfList tAddList;
	tAddList.m_wRefreshNum = 1;
	tAddList.m_atTmpList[0].SetBaseInfo(&m_tConfBaseInfo);
	tAddList.m_atTmpList[0].m_wConfID = GetInsID();
	tAddList.m_atTmpList[0].m_wSpeaker = curSpeakerID();
	tAddList.m_atTmpList[0].m_wDual = m_pcDual->GetDualID();
	tAddList.m_atTmpList[0].m_bIsChairUms = IsChairConf();
	
	NotifyMsgToServiceForUI(evtp_AddConfList_Notify, &tAddList, sizeof(tAddList), ptUserTmp);

	//上报会议中的结点
	TConfCnsInfo tCnsList;
	tCnsList.m_wConfID = GetInsID();
	tCnsList.m_emOpr = tp_OprType_Add;
	//上报切源远遥消息
	TConfVidFeccInfo tVidFeccList;
	tVidFeccList.m_wConfID	= GetInsID();
	tVidFeccList.m_emOpr	= tp_OprType_Add;
	
	TCallNode* ptNode = NULL;
	u16 awAllEpID[TP_CONF_MAX_CNSNUM];
	u16 wEpAllNum = m_pcNodeMgr->GetAllNode( awAllEpID, TP_CONF_MAX_CNSNUM );

	for (u16 wI = 0; wI < wEpAllNum; ++wI)
	{
		ptNode = m_pcNodeMgr->GetNode(awAllEpID[wI]);
		if(NULL == ptNode || !ptNode->m_bUsed)
		{
			continue;	
		}		

		if (tCnsList.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			NotifyMsgToServiceForUI(evtp_UpdateConfCnsList_Notify, &tCnsList, sizeof(tCnsList), ptUserTmp);
			tCnsList.m_wNum = 0;
		}

		if (tVidFeccList.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			NotifyMsgToServiceForUI(evtp_VidFeccMsg_Nty, &tVidFeccList, sizeof(tVidFeccList), ptUserTmp);
			tVidFeccList.m_wNum = 0;
		}

		ptNode->GetCnsInfo(tCnsList.m_tConfCnsList[tCnsList.m_wNum]);
		tCnsList.m_wNum++;
		ptNode->GetVidFeccInfo(tVidFeccList.m_atVidFeccList[tVidFeccList.m_wNum]);
		tVidFeccList.m_wNum++;
	}

	if (tCnsList.m_wNum > 0)
	{
		NotifyMsgToServiceForUI(evtp_UpdateConfCnsList_Notify, &tCnsList, sizeof(tCnsList), ptUserTmp);
	}
	if (tVidFeccList.m_wNum > 0)
	{
		NotifyMsgToServiceForUI(evtp_VidFeccMsg_Nty, &tVidFeccList, sizeof(tVidFeccList), ptUserTmp);
	}

	//通知轮询列表
	m_pcPollMgr->NotifyPollListToUI(FALSE, TRUE, ptUserTmp);
	m_pcPollMgr->NotifyPollStatToUI(ptUserTmp);

	//通知讨论
	TConfAuxMixInfo tMixInfo;
	m_pcUmsDiscuss->GetDiscussStateInfo(tMixInfo);
	NotifyMsgToServiceForUI(evtp_AuxMixInfo_Notify, &tMixInfo, sizeof(tMixInfo), ptUserTmp);

	//通知点名状态
	TConfRollCallInfo tRollCallInfo;
	m_pcRollCallMgr->GetRollCallStateInfo(tRollCallInfo);
	NotifyMsgToServiceForUI(evtp_RollCallState_Notify, &tRollCallInfo, sizeof(TConfRollCallInfo));
	//通知点名于会状态
    TRollCallPresentStateMsg tPresentState;
	m_pcRollCallMgr->GetAllRollCallPresentStateInfo(tPresentState);
	NotifyMsgToServiceForUI(evtp_RollCall_PresentState_Notify, &tPresentState, sizeof(TRollCallPresentStateMsg));

	//通知会议混音状态
	TUmsAudMixInfo tConfMixInfo;
	m_pcAudMix->GetConfAudMixStateInfo(tConfMixInfo);
	NotifyMsgToServiceForUI(evtp_ConfAudMixMode_Notify, &tConfMixInfo, sizeof(tConfMixInfo));


	//通知选看状态
	m_pcSelView->NtfyAllSelInfoToUI(tp_OprType_Add, ptUserTmp);

	// 合成
	m_pcVmp->NotifyAllBrdVmpToUMC( ptUserTmp);

	u16 wConfID = GetInsID();
	// 通知umc全场静音哑音状态
	s8 szBuf[sizeof(u16) + sizeof(BOOL32) +sizeof(BOOL32)] = {0};
	memcpy(szBuf, &wConfID, sizeof(u16));
	memcpy(szBuf+sizeof(u16), &m_bIsAllEpQuiet, sizeof(BOOL32));
	memcpy(szBuf+sizeof(u16)+sizeof(BOOL32), &m_bIsAllEpMute, sizeof(BOOL32));
	NotifyMsgToService(evtp_ConfAllEpQuietMuteStatus_Nty, szBuf, sizeof(u16) + sizeof(BOOL32)+sizeof(BOOL32));
	if (!IsChairConf())
	{
		//通知主席
		TChairConfInfo tChair;
		tChair.m_wConfID = GetInsID();
		tChair.m_tBeginTime = time(NULL) - m_tConfBaseInfo.m_tStartTime;
		tChair.m_tChairName.SetAlias(m_tSuperInfo.m_tChair.m_abyAlias);
		tChair.m_tConfName.SetAlias(m_tSuperInfo.m_tConf.m_abyAlias);
		NotifyMsgToServiceForUI(evtp_ChairConfInfo_Notify, &tChair, sizeof(tChair), ptUserTmp);
	}
	return;
}

/*==============================================================================
函数名    :  EventStartConf
功能      :  根据会议模板呼叫各会场
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-4-27               zhaixiaogang
==============================================================================*/
EmCnsCallReason CUmsConfInst::EventStartConf(u8* pDataBuf, u16 wDataSize, TCapNode* ptCaller, BOOL32 bIsNeedDelayCall)
{
	TConfTemplateLocal* pConfTmp = (TConfTemplateLocal*)pDataBuf;

	ObjHint(("EventStartConf curState:%d, confTempID:%d, ConfID:%d, EncrptyMdl:%d\n", CurState(), pConfTmp->m_wID, GetInsID(), pConfTmp->m_tEncrypt.m_emEncryptModel));
	static u32 dwConfTemplateId = 1;
	if (CurState() != inst_idle)
	{
		u16 wConfID = GetInsID();
		ObjError(("EventStartConf Failed. inst is busy. wConfID:%d,state:%d, Template:%s\n", wConfID, CurState(), pConfTmp->m_achConfName));
		return EmCnsCallReason_Busy;
	}

	if ( localmax(GetConfBase().m_wConfBitRate, GetConfBase().m_wBpConfBitRate) == 0 )//会议码率为0
	{
		ObjError(("CUmsConfInst::EventStartConf. BitRate is Zero. wConfID:%d, state:%d, Template:%s\n",
			GetInsID(), CurState(), pConfTmp->m_achConfName));
       
		if (ptCaller == NULL)
		{//表示从UMC过来的呼叫，原因设置成资源不足
			return EmCnsCallReason_resourcefull;
		}

        //从协议栈过来的呼叫，原因设置成拒绝
		return EmCnsCallReason_Rejected;
	}


	//add
	if (m_dwOnlineChanNum >= m_dwLicenseChanNum)
	{
		u16 wConfID = GetInsID();
		ObjError(("EventStartConf Failed. m_dwOnlineChanNum:%d more than m_dwLicenseChanNum:%d. wConfID:%d,state:%d, Template:%s\n"
				, m_dwOnlineChanNum, m_dwLicenseChanNum, wConfID, CurState(), pConfTmp->m_achConfName));

		if (ptCaller == NULL)
		{//表示从UMC过来的呼叫，原因设置成资源不足
			return EmCnsCallReason_resourcefull;
		}

		//从协议栈过来的呼叫，原因设置成拒绝
		return EmCnsCallReason_Rejected;
	}
	//end
	m_tConfBaseInfo = *(TUmsConfBase*)(pConfTmp);
	m_tConfBaseInfo.m_tStartTime = time(NULL);

	if (emTPEncryptTypeAES == m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel)
	{//长度固定为16位
		if (m_tConfBaseInfo.m_bDefaultEncrypt)
		{
			static const s8 achkeysrc[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			srand(time(0));
			
			for (u16 wCount = 0; wCount < TP_ENCRYPT_KEY_LEN; wCount++)
			{
				m_tConfBaseInfo.m_tEncrypt.m_achEncKey[wCount] = (s8)achkeysrc[rand()%strlen(achkeysrc)] ;			
			}
			m_tConfBaseInfo.m_tEncrypt.m_achEncKey[TP_ENCRYPT_KEY_LEN] = '\0'; 
		}

		m_tConfBaseInfo.m_tEncrypt.m_byKeyLen = 16;
	}
	else if ( m_tConfBaseInfo.m_tEncrypt.IsQt() )
	{
		EmTPEncryptType emEncry = m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel;
		m_tConfBaseInfo.m_tEncrypt.Clear();
		m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel = emEncry;

		TTPQTEncryptInfo tTPQTEncryptInfo;
	    umsGetQTEncryptInfo(tTPQTEncryptInfo);

		if (!tTPQTEncryptInfo.m_bIsEncQT)
		{ //QTID, QTIP开关没有打开
			if (ptCaller == NULL)
			{//表示从UMC过来的呼叫，原因设置成资源不足
				return EmCnsCallReason_resourcefull;
			}
			//从协议栈过来的呼叫，原因设置成拒绝
		    return EmCnsCallReason_Rejected;
		}
	}

	//会议模板和会议的ID不一致
	m_tConfBaseInfo.m_wDefaultChairMan = m_tConfBaseInfo.m_wDefaultChairMan + 1;

	//给每个格式赋值码率
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < m_tConfBaseInfo.m_wMainNum; wIndex ++ )
	{
		if ( m_tConfBaseInfo.m_atTpMainVideoRes[wIndex].m_emQualityLvl == emTPH264HP )
		{
			m_tConfBaseInfo.m_atTpMainVideoRes[wIndex].m_wBitrate = m_tConfBaseInfo.m_wConfBitRate;//会议码率 hp
		}
		else
		{
			m_tConfBaseInfo.m_atTpMainVideoRes[wIndex].m_wBitrate = m_tConfBaseInfo.m_wBpConfBitRate;
		}
	}
	
	for ( wIndex = 0; wIndex < m_tConfBaseInfo.m_wMinorNum; wIndex ++ )
	{
		if ( m_tConfBaseInfo.m_atTpMinorVideoRes[wIndex].m_emQualityLvl == emTPH264HP )
		{
			m_tConfBaseInfo.m_atTpMinorVideoRes[wIndex].m_wBitrate = m_tConfBaseInfo.m_wHpDualBitRate;//双流码率 hp
		}
		else
		{
			m_tConfBaseInfo.m_atTpMinorVideoRes[wIndex].m_wBitrate = m_tConfBaseInfo.m_wBpDualBitRate;
		}
	}

#ifdef _USE_XMPUEQP_
	TXmpuMettingInfo tInfo;
	u16 wMaxHp = 0;
	u16 wMaxBp = 0;
	tInfo.m_wConfID = GetInsID();
	memcpy(tInfo.m_achConfE164, m_tConfBaseInfo.m_achConfE164, strlen(m_tConfBaseInfo.m_achConfE164));
	memcpy(tInfo.m_achConfName, m_tConfBaseInfo.m_achConfName, strlen(m_tConfBaseInfo.m_achConfName));
	CTpTypeAdpt::GetConfBaseMaxCap(m_tConfBaseInfo, wMaxHp, wMaxBp);
	if (TP_INVALID_INDEX != wMaxHp)
	{
		tInfo.m_tFormat = m_tConfBaseInfo.m_atTpMainVideoRes[wMaxHp];
	}
	else
	{
		tInfo.m_tFormat  = m_tConfBaseInfo.m_atTpMainVideoRes[wMaxBp];
	}
	tInfo.m_dwMaxMtNum = TP_UMS_MAX_CHANNUM;
	tInfo.m_bNeedVidBas = IsVidNeedBas(); 
	tInfo.m_bNeedAudBas = IsAudNeedBas(); 

	TJDInfo tJdInfo;
	CJDConfig::GetInstance()->GetFromConfigFile(tJdInfo); 
	memcpy(tInfo.m_abyMqUrl, tJdInfo.m_abyMqUrl, sizeof(tJdInfo.m_abyMqUrl));
	memcpy(tInfo.m_abyMoid, tJdInfo.m_abyMachineMoid, sizeof(tJdInfo.m_abyMachineMoid));

	BOOL32 bInitRet = InitXmpuMeeting(tInfo);
	ObjHint(("EventStartConf. Init Xmpu Metting Ret:%d. wConfID:%d.\n", 
		bInitRet, GetInsID()));

	if (!bInitRet && (tInfo.m_bNeedAudBas || tInfo.m_bNeedVidBas))
	{
		ObjHint(("EventStartConf. Init Xmpu Metting Error!. wConfID:%d, audbas:%d, vidbas:%d.\n", 
			GetInsID(), tInfo.m_bNeedAudBas, tInfo.m_bNeedVidBas));
		return EmCnsCallReason_resourcefull;
	}

	if (bInitRet)
	{
		g_atXmpuInitMeeting[GetInsID()-1].m_bInitXmpuMeeting = TRUE;
		memcpy(&g_atXmpuInitMeeting[GetInsID()-1].m_tXmpuConfTempInfo, pConfTmp, sizeof(TConfTemplateLocal));
		if (NULL != ptCaller)
		{
			memcpy(&g_atXmpuInitMeeting[GetInsID()-1].m_tXmpuCallerNode, ptCaller, sizeof(TCapNode));
		}
		g_atXmpuInitMeeting[GetInsID()-1].m_bXmpuNeedDelayCall = bIsNeedDelayCall;

		return EmCnsCallReason_success;
	}
#endif//#ifdef _USE_XMPUEQP_
	return EventStartConfFromXeqp(pConfTmp, ptCaller, bIsNeedDelayCall);
}

EmCnsCallReason CUmsConfInst::EventStartConfFromXeqp(TConfTemplateLocal* pConfTmp, TCapNode* ptCaller,  BOOL32 bIsNeedDelayCall)
{
	if ((pConfTmp->m_wID == 0 || pConfTmp->m_wID >= TP_CONFTEMPLATE_MAXNUM) && m_tConfBaseInfo.m_tEncrypt.IsQt() )
	{//临时会议, 
		m_QueryAliasMgr.UpdateTempConfInfo(m_tConfBaseInfo.m_achConfName, sizeof(m_tConfBaseInfo.m_achConfName), GetInsID(), &m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel);
	}

	BOOL32 bRet = FALSE;
	bRet = m_pcNodeMgr->AssignDsRes(FALSE, &m_tEqpConfDs);	
	if (bRet)
	{
		ResetMediaIp(m_tEqpConfDs);
	}
	else
	{
		ObjError(("EventStartConf. assign media failed. wConfID:%d, Template:%s\n", GetInsID(), pConfTmp->m_achConfName));
		return EmCnsCallReason_resourcefull;
	}

	if (!m_pcBas->StartBas())
	{
		m_pcBas->StopBas();
		m_tConfBaseInfo.Clear();

		ObjError(("EventStartConf Failed. assign BasRes failed. wConfID:%d,state:%d, Template:%s\n", GetInsID(), CurState(), pConfTmp->m_achConfName));

		if (ptCaller == NULL)
		{//表示从UMC过来的呼叫，原因设置成资源不足
			return EmCnsCallReason_resourcefull;
		}

		return EmCnsCallReason_Rejected;
	}

	NextState(inst_run);

	m_wConfTemplateID = pConfTmp->m_wID;
	if( m_wConfTemplateID == 0 || m_wConfTemplateID >= TP_CONFTEMPLATE_MAXNUM)//临时会议 cky
	{
		u16 wTempConfID = GetIdleTempConfID();
		if (wTempConfID < TP_UMS_MAX_CONFNUM)
		{
			g_atTempConf[wTempConfID].m_bUsed = TRUE;
			g_atTempConf[wTempConfID].m_wConfId = GetInsID();
		}

		if (!m_tConfBaseInfo.m_tEncrypt.IsQt())
		{
			snprintf( m_tConfBaseInfo.m_achConfName, TP_MAX_ALIAS_LEN, "%s%d", pConfTmp->m_achConfName, wTempConfID + 1);
			m_tConfBaseInfo.m_achConfName[TP_MAX_ALIAS_LEN] = '\0';
		}

		ObjHint(("EventStartConf InstantConfName:%s\n", m_tConfBaseInfo.m_achConfName));
		m_pcRegMgr->StartTempReg(m_tConfBaseInfo, GetInsID());


		u16 wUpdateConf = GetInsID();
		s8 abyTmpConfName[ sizeof(u16) + sizeof(TTPAlias)] = {0};
		memcpy(abyTmpConfName, &wUpdateConf, sizeof(u16));
		TTPAlias *palias = (TTPAlias *)(abyTmpConfName + sizeof(u16));
		palias->SetAlias( m_tConfBaseInfo.m_achConfName);

		NotifyMsgToService(evtp_Update_TempConf_To_Server, abyTmpConfName, sizeof(abyTmpConfName));
	}	

	TNbParam tEqpNb;
	tEqpNb.m_ptEqpRes = &m_tEqpConfNb;
	bRet = AssignEqpEx(&tEqpNb);

	if (bRet)
	{
		ResetNbIp(m_tEqpConfNb);
	}
	else
	{
		ObjError(("EventStartConf. assign nb failed. wConfID:%d, Template:%s\n", GetInsID(), pConfTmp->m_achConfName));
	}
	for (u16 wI = 0;wI < pConfTmp->m_atEpList.m_wNum; wI++)
	{
		ObjHint(("EventStartConf epIP:"TPIPFORMAT",EpName:%s,Epe164:%s\n", 
			u32ToIP(pConfTmp->m_atEpList.m_tCnsList[wI].m_tEpAddr.m_dwIP),
			pConfTmp->m_atEpList.m_tCnsList[wI].m_tEpAddr.m_tAlias.m_abyAlias,
			pConfTmp->m_atEpList.m_tCnsList[wI].m_tEpAddr.m_tE164.m_abyAlias));
	}
	//创建结点
	m_pcNodeMgr->InitCallNode(pConfTmp->m_atEpList,pConfTmp->m_tTempCfgEx);
	if (NULL == ptCaller)
	{
		SetChairID(GetNode(m_tConfBaseInfo.m_wDefaultChairMan));//设定主席
		SetCurSpeaker(m_cChair.GetSrc());                       //暂定主席为发言人
	}
	else
	{
		TCapNode* ptTmpNode = NULL;
		if (ptCaller->m_wEpID != CALLER_EP_INDEX)//CNS过来的呼叫
		{
			TCapNode* ptSrcNode = m_pcNodeMgr->GetLocalNode(ptCaller->m_tCalledAddr);
			if (NULL == ptSrcNode)
			{
				ObjError(("EventStartConf. set caller failed. wConfID:%d, CallerID:%d, Template:%s\n", GetInsID(), ptCaller->m_wEpID, pConfTmp->m_achConfName));
				m_pcNodeMgr->StopConf();
				return EmCnsCallReason_dstnotfind;
			}
			m_pcNodeMgr->ReleaseNodeRes(ptSrcNode);

			//使用前面分配的节点
			for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				ptSrcNode->m_aptChanAddr[wIndex] = ptCaller->m_aptChanAddr[wIndex];
				ptSrcNode->m_aptSmallChanAddr[wIndex] = ptCaller->m_aptSmallChanAddr[wIndex];
			}
			ptSrcNode->m_ptMixAddr = ptCaller->m_ptMixAddr;
			ptSrcNode->m_ptDualAddr = ptCaller->m_ptDualAddr;
			ptSrcNode->m_tAdapterEqp = ptCaller->m_tAdapterEqp;
			ptSrcNode->m_tMediaEqp = ptCaller->m_tMediaEqp;
			ptSrcNode->m_emCallState = ums_UmsConfNodeState_calling;
			ptSrcNode->m_dwStackHandle = ptCaller->m_dwStackHandle;
			ptSrcNode->m_bIsCaller = FALSE;
			ptSrcNode->m_emCallProtocol = ptCaller->m_emCallProtocol;

			ptTmpNode = ptSrcNode;
		}
		else
		{
			ptCaller->m_emCallState = ums_UmsConfNodeState_calling;
			ptCaller->m_bIsCaller = FALSE;

			ptTmpNode = ptCaller;
		}

		SetCurSpeaker(ptTmpNode);
		SetChairID(m_cSpeaker.GetCur());

		TUmsHandle tAckHandle;
		m_pcNodeMgr->MakeCallerHandle(tAckHandle, ptTmpNode->m_wEpID);

		TMakeCallPara tCallPara;
		m_pcCallMgr->MakeCallInfo(tCallPara, *ptTmpNode, TRUE);
		UmsAnwserCall(tAckHandle, TRUE, &tCallPara, EmCnsCallReason_success);

	}

	TUmsHandle tHandle;
	m_pcNodeMgr->MakeCallerHandle(tHandle, curSpeakerID());
	u8 uSndBuf[sizeof(BOOL32)*2] = {0};
	BOOL32 bChairConf = IsChairConf();
	BOOL32 bReset = FALSE;
	memcpy(uSndBuf, &bChairConf, sizeof(BOOL32));
	memcpy(uSndBuf+sizeof(BOOL32), &bReset, sizeof(BOOL32));
	UmsSendConfCtrl(tHandle, evtp_QtSetConfInfo_Cmd, uSndBuf, sizeof(uSndBuf));

	if (CUmsConfigEx::GetInstance()->GetRsFirstTime() != 0 && CUmsConfigEx::GetInstance()->GetRsRejectTime() != 0)
	{
		m_tConfBaseInfo.m_tRsParam.m_wFirstTimeSpan	= CUmsConfigEx::GetInstance()->GetRsFirstTime();
		m_tConfBaseInfo.m_tRsParam.m_wSecondTimeSpan	= CUmsConfigEx::GetInstance()->GetRsSecondTime();
		m_tConfBaseInfo.m_tRsParam.m_wThirdTimeSpan	= CUmsConfigEx::GetInstance()->GetRsThirdTime();
		m_tConfBaseInfo.m_tRsParam.m_wRejectTimeSpan	= CUmsConfigEx::GetInstance()->GetRsRejectTime();

		ObjHint(("EventStartConf ConfID:%d, rs: %d - %d - %d - %d\n"
			, GetInsID(), m_tConfBaseInfo.m_tRsParam.m_wFirstTimeSpan, m_tConfBaseInfo.m_tRsParam.m_wSecondTimeSpan
			, m_tConfBaseInfo.m_tRsParam.m_wThirdTimeSpan, m_tConfBaseInfo.m_tRsParam.m_wRejectTimeSpan));
	}

	m_cBw.StartConf(m_tConfBaseInfo.m_wUpBandWid, m_tConfBaseInfo.m_wDownBandWid);//获取带宽信息

	m_pcVmp->StartSpeakerVmp();

	//初始化轮询结点
	m_pcPollMgr->InitPollList(&pConfTmp->m_tTurnList);
	// 讨论预置开启，暂停上面的轮询
	m_pcUmsDiscuss->InitDiscuss(pConfTmp->m_atAuxMixList);

	//初始化合成预案
	m_pcVmp->InitBrdVmpCfg(&pConfTmp->m_tVmpCfg);

	//创建netbuf
	CNetPortMgr::CreateNetBuf(this);

	if (m_tEqpConfDs.IsValid())
	{
		//创建虚拟发言人的交换
		CNetPortMgr::CreateVirSpeakerTrans(this);
	}

	if (!bIsNeedDelayCall)
	{
		// 呼叫结点
		m_bIsNeedDelayCallNode = FALSE;
		CallAllLocalNode();
	}
	else
	{
		// cns呼叫ums会议模板时，等待主会场的主流和双流通道协商结果上来后，再呼叫其他节点
		m_bIsNeedDelayCallNode = TRUE;
		ObjHint(("EventStartConf ConfID:%d, bIsNeedDelayCall:%d, m_bIsNeedCallNode:%d, CallAllLocalNode is delay!\n", 
			GetInsID(), bIsNeedDelayCall, m_bIsNeedDelayCallNode));
	}

	//上报会议信息
	TAddConfList tAddList;
	tAddList.m_wRefreshNum = 1;
	tAddList.m_atTmpList[0].m_wConfID = GetInsID();
	tAddList.m_atTmpList[0].SetBaseInfo(&m_tConfBaseInfo);
	tAddList.m_atTmpList[0].m_wSpeaker = curSpeakerID();
	tAddList.m_atTmpList[0].m_wDual = m_pcDual->GetDualID();
	tAddList.m_atTmpList[0].m_bIsChairUms = IsChairConf();
	NotifyMsgToServiceForUI(evtp_AddConfList_Notify, &tAddList, sizeof(tAddList));

	//上报会议中的结点
	TConfCnsInfo tCnsList;
	tCnsList.m_wConfID = GetInsID();
	tCnsList.m_emOpr = tp_OprType_Add;
	//上报会议中的视频源 远遥信息
	TConfVidFeccInfo tVidFeccList;
	tVidFeccList.m_wConfID	= GetInsID();
	tVidFeccList.m_emOpr	= tp_OprType_Add;

	for (TCallNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->m_bUsed)
		{
			continue;	
		}		
		if (tCnsList.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			NotifyMsgToServiceForUI(evtp_UpdateConfCnsList_Notify, &tCnsList, sizeof(tCnsList));
			tCnsList.m_wNum = 0;
		}
		if (tVidFeccList.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			NotifyMsgToServiceForUI(evtp_VidFeccMsg_Nty, &tVidFeccList, sizeof(tVidFeccList));
			tVidFeccList.m_wNum = 0;
		}

		ptNode->GetCnsInfo(tCnsList.m_tConfCnsList[tCnsList.m_wNum]);
		tCnsList.m_wNum++;

		ptNode->GetVidFeccInfo(tVidFeccList.m_atVidFeccList[tVidFeccList.m_wNum]);
		tVidFeccList.m_wNum++;
	}

	if (tCnsList.m_wNum > 0)
	{
		NotifyMsgToServiceForUI(evtp_UpdateConfCnsList_Notify, &tCnsList, sizeof(tCnsList));
	}
	if (tVidFeccList.m_wNum > 0)
	{
		NotifyMsgToServiceForUI(evtp_VidFeccMsg_Nty, &tVidFeccList, sizeof(tVidFeccList));
	}
	// 通知轮询列表
	if (IsChairConf())
	{
		m_pcPollMgr->NotifyPollListToUI();
		m_pcPollMgr->NotifyPollStatToUI();
	}

	// 通知合成状态
	m_pcVmp->NotifyAllBrdVmpToUMC();

	// 通知讨论
	TConfAuxMixInfo tMixInfo;
	m_pcUmsDiscuss->GetDiscussStateInfo(tMixInfo);
	NotifyMsgToServiceForUI(evtp_AuxMixInfo_Notify, &tMixInfo, sizeof(tMixInfo));

	u16 wConfID = GetInsID();
	// 通知umc全场静音哑音状态
	s8 szBuf[sizeof(u16) + sizeof(BOOL32) +sizeof(BOOL32)] = {0};
	memcpy(szBuf, &wConfID, sizeof(u16));
	memcpy(szBuf+sizeof(u16), &m_bIsAllEpQuiet, sizeof(BOOL32));
	memcpy(szBuf+sizeof(u16)+sizeof(BOOL32), &m_bIsAllEpMute, sizeof(BOOL32));
	NotifyMsgToService(evtp_ConfAllEpQuietMuteStatus_Nty, szBuf, sizeof(u16) + sizeof(BOOL32)+sizeof(BOOL32));

	u32 wBeginTime = CUmsConfigEx::GetInstance()->GetBeginFastUpdateInterval();
	if ( wBeginTime > 0)
	{
		m_bIsNeedKeyProtectOnStart = TRUE;
		SetTimer(evtp_KeyProtectOnStart_time, wBeginTime * 1000);
	}

	m_pcDual->StartConf();

	return EmCnsCallReason_success;
}

void CUmsConfInst::EventOnProtectTime()
{
	m_bIsNeedKeyProtectOnStart = FALSE;
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}

		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			ptNode->m_tRmtChan.m_atVidEnc[wIndex].m_tKeyFrameStatis.Clear();			
			ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tKeyFrameStatis.Clear();			
		}
	}
}


void CUmsConfInst::EventOnCallTime()
{
	CallAllLocalNode();
}


void CUmsConfInst::EventHungConf(CTpMsg *const ptMsg)
{
	ObjHint(("EventHungConf confID:%d, state:%d\n", GetInsID(), CurState()));

	m_bIsQuiting = TRUE;
	StopConf();

	TDelConfList tList;
	tList.m_wRefreshNum = 1;
	tList.m_awConfIDList[0] = GetInsID();
		
	CTpMsg cMsg;	
	cMsg.SetEvent(evtp_DelConflist_Notify);
	cMsg.SetBody(&tList, sizeof(tList));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
	
}

void CUmsConfInst::OnChangeSpeaker( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TConfEpID* ptConfEp	= (TConfEpID*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	u16 wEpID = ptConfEp->m_wEpID;
	
	if ( !CheckMsgFromChair(this, tHandle.GetEpID()) )
	{
		return ;
	}

	TCallNode* ptNode = m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = m_pcNodeMgr->GetForeFatherNode(ptNode);
	
	if (ptNode && ptFartherNode && ptFartherNode != ptNode && ptFartherNode->IsMcu())
	{
		OnChangeMcuEpSpeakerFromCns(tHandle, ptConfEp);
		return ;
	}

	EmTpApplySpeakerRet emRet = TP_ApplySpeaker_Success;
	do 
	{
		if (NULL == ptNode)
		{
			ObjError(("OnChangeSpeaker ep Index error.wConfID:%d, EpID:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}
		
		if (!ptNode->IsMtEp() || !ptNode->IsCallOn() || !ptNode->IsChanOn() || !ptNode->IsVidSndValid())
		{
			ObjError(("OnChangeSpeaker ep state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), wEpID, UmsNodeConfType(ptNode->m_emCallState), ptNode->m_bChannelOpen));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}

		if (ptNode->IsMcu())
		{ // 指定MCU 为发言人(应指定MCU下某一个会场为发言人,简单级联mcu 的类型是emTPEndpointH323SingleMCU)
			ObjError(("OnChangeSpeaker ep error,  speaker is mcu! .wConfID:%d, EpID:%d\n", GetInsID(), wEpID));
            emRet = TP_ApplySpeaker_EpStateError;
			break;
		}

		if (0 == ptNode->m_wVidSndNum && 0 == ptNode->m_wAudSndNum)
		{
			ObjError(("OnChangeSpeaker ep Snd Num error. ConfID:%d, epID:%d, VidSndNum:%d, AudSndNum:%d\n", GetInsID(), wEpID, ptNode->m_wVidSndNum, ptNode->m_wAudSndNum));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}

		if (wEpID == curSpeakerID())
		{
			ObjError(("OnChangeSpeaker ep not changer.wConfID:%d, EpID:%d, curspeaker:%d\n", GetInsID(), wEpID, curSpeakerID()));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}


		if (m_pcUmsDiscuss->IsUIDiscussOn())
		{
			TDiscussEpInfo* ptEpInfo = m_pcUmsDiscuss->GetDiscussEpInfoById(wEpID);
			if (NULL == ptEpInfo || !ptEpInfo->IsValid())
			{
				ObjError(("OnChangeSpeaker Now it is Dicuss modle, ep is not vaild In discuss. ConfId:%d, epId:%d\n", GetInsID(), wEpID));
				emRet = TP_ApplySpeaker_EpIDError;
				break;
			}
		}


		if (GetRollCallMgr()->IsUIRollCallOn())
		{   //点名模式，不支持切换发言人
			ObjError(("OnChangeSpeaker Now it is rollcallmode modle, ConfId:%d, epId:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}	

	} while (0);
	
	ObjHint(("OnChangeSpeaker ConfID:%d, old Speaker:%d, new Speaker:%d, ret:%d\n", GetInsID(), curSpeakerID(), wEpID, emRet));
	
	//回应CNS
	u8 uSndBuf[sizeof(TConfEpID) + sizeof(EmTpApplySpeakerRet)] = { 0 };
	memcpy(uSndBuf, ptConfEp, sizeof(TConfEpID));
	memcpy(uSndBuf + sizeof(TConfEpID), &emRet, sizeof(EmTpApplySpeakerRet));
	NotifyConfCtrlMsgToCns(ev_UmsConfApplySpeaker_Ind, tHandle.GetEpID(), uSndBuf, sizeof(uSndBuf));

	if (TP_ApplySpeaker_Success == emRet)
	{
		if (m_pcUmsDiscuss->IsUIDiscussOn())
		{// 里面会调changspeaker
			m_pcUmsDiscuss->OnChangerSpeaker(ptNode);
		}
		else
		{
			ChangeSpeaker(wEpID, NULL);
			AdjustNewSpeakerToAllNode();
			AdjustNewSpeakerToAllMcuNode();
			NotifyApplySpeakerToUI();
		}
	}

	return;
}

void CUmsConfInst::OnMuteEp(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TConfEpID* ptConfEp	= (TConfEpID*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	BOOL32 bIsMute	= *(BOOL32*)(ptMsg->GetBody()+sizeof(TUmsHandle)+sizeof(TConfEpID));

	if ( !CheckMsgFromChair(this, tHandle.GetEpID()) )
	{
		return;
	}

	ObjHint(("OnMuteEp ConfID:%d, EpID:%d, bIsMute:%d\n", GetInsID(), ptConfEp->m_wEpID, bIsMute));
	
	if (ptConfEp->m_wEpID == TP_ALLEP_INDEX)
	{
		if (IsChairConf())
		{
			OnAllMuteEpForUmcCnc(ptConfEp, bIsMute);
		}
	}
	else
	{
		OnMuteEpForUmcCnc(ptConfEp, bIsMute);
	}
}

void CUmsConfInst::OnQuietEp(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TConfEpID* ptConfEp	= (TConfEpID*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	BOOL32 bIsQuiet	= *(BOOL32*)(ptMsg->GetBody()+sizeof(TUmsHandle)+sizeof(TConfEpID));
		
	if ( !CheckMsgFromChair(this, tHandle.GetEpID()) )
	{
		return;
	}

	ObjHint(("OnQuietEp ConfID:%d, EpID:%d, bIsQuiet:%d\n", GetInsID(), ptConfEp->m_wEpID, bIsQuiet));
	//给cnc回应
	if (ptConfEp->m_wEpID == TP_ALLEP_INDEX)
	{
		if (IsChairConf())
		{
			OnAllQuietEpForUmcCnc(ptConfEp, bIsQuiet);
		}
	}
	else
	{
		OnQuietEpForUmcCnc(ptConfEp, bIsQuiet);
	}
}


void CUmsConfInst::OnHungConf( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();

	if ( !CheckMsgFromChair(this, tHandle.GetEpID()) )
	{
		return ;
	}

	ObjHint(("OnHungConf confID:%d, state:%d\n", GetInsID(), CurState()));
	
	m_bIsQuiting = TRUE;
	StopConf();

	TDelConfList tList;
	tList.m_wRefreshNum = 1;
	tList.m_awConfIDList[0] = GetInsID();
	
	CTpMsg cMsg;	
	cMsg.SetEvent(evtp_DelConflist_Notify);
	cMsg.SetBody(&tList, sizeof(tList));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));

	return ;
}

/*==============================================================================
函数名    :  OnConfIncoming
功能      :  被动呼入
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-4               zhaixiaogang
==============================================================================*/
EmCnsCallReason CUmsConfInst::OnConfUmsCall(const TUmsHandle& tHandle, TUmsCallInfo& tCaller, TConfTemplateLocal& tConfTemp)
{	
	TCapNode* ptCallerNode = m_pcNodeMgr->GetCaller();

	TEqpRes tAdapter;
	TAdaptEqpParam tAdapterEqp;
	tAdapterEqp.m_ptEqpRes = &tAdapter;
	tAdapterEqp.m_ptEqpRes->m_dwEqpNode = tHandle.m_dwAdapteID;
	BOOL32 bRet = AssignEqpByNodeEx(&tAdapterEqp);

	if (!bRet)
	{//接入分配失败		
		MdlError(Ums_Mdl_Call, ("OnConfUmsCall alloc new adapter failed! wConfID:%d, ConfTemp:%s\n", GetInsID(), tConfTemp.m_achConfName));
		return EmCnsCallReason_resourcefull;
	}

	if (!m_pcNodeMgr->AssignNodeRes(ptCallerNode, &tAdapter))
	{
		ReleaseEqpEx(&tAdapterEqp);
		MdlError(Ums_Mdl_Call, ("OnConfUmsCall AssignNodeRes failed! wConfID:%d, ConfTemp:%s\n", GetInsID(), tConfTemp.m_achConfName));		
		return EmCnsCallReason_resourcefull;
	}

	ptCallerNode->m_bUsed = TRUE;
	ptCallerNode->m_dwStackHandle = tHandle.handPaCall;
	ptCallerNode->m_emEpType = tCaller.m_emSrcEpType;
	ptCallerNode->m_tAdapterEqp = tAdapter;

	ptCallerNode->m_tConfName = tCaller.m_tSrcAddr.GetValidAlias();	
	ptCallerNode->m_tCalledAddr = tCaller.m_tSrcAddr;
	ptCallerNode->m_emCallProtocol = tCaller.m_emTpProtocol;

	//设置为非上级
	m_pcCallMgr->SetChair(FALSE);

	//开启会议
	EmCnsCallReason emCallRet = EventStartConf((u8*)&tConfTemp, sizeof(tConfTemp), ptCallerNode, TRUE);
	if ( EmCnsCallReason_success != emCallRet )
	{
		m_pcNodeMgr->ReleaseNodeRes(ptCallerNode);
		ptCallerNode->Clear();
		StopConf();

		MdlError(Ums_Mdl_Call, ("OnConfUmsCall EventStartConf failed! wConfID:%d, ConfTemp:%s, CallRet:%d\n", 
																			GetInsID(), tConfTemp.m_achConfName, emCallRet));
		return emCallRet;
	}

	return EmCnsCallReason_success;
}


EmCnsCallReason CUmsConfInst::OnConfCnsCall(const TUmsHandle& tHandle, TUmsCallInfo& tCaller, TConfTemplateLocal* ptConfTemp)
{
	TConfTemplateLocal tConfTemp = *ptConfTemp;
	TEpAddr* ptEpAddr = tConfTemp.m_atEpList.FindEp(tCaller.m_tSrcAddr);

	u16 wDelFromPoll = TP_INVALID_INDEX;
	if (NULL == ptEpAddr)
	{
		MdlHint(Ums_Mdl_Call, ("OnConfCnsCall SrcAddr not find in ConfTemp! wConfID:%d, ConfTemp:%s, EpNum:%d, SrcAddr:%s-%s-"TPIPFORMAT",SrcType:%d\n", 
				GetInsID(), tConfTemp.m_achConfName, tConfTemp.m_atEpList.m_wNum, tCaller.m_tSrcAddr.m_tAlias.m_abyAlias, 
				tCaller.m_tSrcAddr.m_tE164.m_abyAlias, u32ToIP(tCaller.m_tSrcAddr.m_dwIP),tCaller.m_emSrcEpType));
		
		tConfTemp.m_atEpList.Add(tCaller.m_tSrcAddr);
		ptEpAddr = tConfTemp.m_atEpList.FindEp(tCaller.m_tSrcAddr);
		if (NULL == ptEpAddr)
		{
			MdlError(Ums_Mdl_Call, ("OnConfCnsCall ConfTemp is full! wConfID:%d, ConfTemp:%s\n", GetInsID(), tConfTemp.m_achConfName));
			return EmCnsCallReason_Rejected;
		}
	}

	if (ptEpAddr->m_wEpID != tConfTemp.m_wDefaultChairMan)
	{
		tConfTemp.m_wDefaultChairMan = ptEpAddr->m_wEpID;

		//将此节点从轮询列表中删除
		for (u16 wIndex = 0; wIndex < tConfTemp.m_tTurnList.m_wNum; ++wIndex)
		{
			if (ptEpAddr->m_wEpID == tConfTemp.m_tTurnList.m_awList[wIndex])
			{
				if (wIndex != tConfTemp.m_tTurnList.m_wNum - 1)
				{
					memcpy(&tConfTemp.m_tTurnList.m_awList[wIndex], &tConfTemp.m_tTurnList.m_awList[wIndex+1]
						, (tConfTemp.m_tTurnList.m_wNum - wIndex - 1) * sizeof(tConfTemp.m_tTurnList.m_awList[0]) );
				}
				
				tConfTemp.m_tTurnList.m_wNum -= 1;
				break;
			}
		}
	}

	TCapNode tCallNode;
	tCallNode.m_wEpID = 0;
	tCallNode.m_emEpType = emTPEndpointTypeCNS;

	TEqpRes tAdapter;
	TAdaptEqpParam tAdapterEqp;
	tAdapterEqp.m_ptEqpRes = &tAdapter;
	tAdapterEqp.m_ptEqpRes->m_dwEqpNode = tHandle.m_dwAdapteID;
	BOOL32 bRet = AssignEqpByNodeEx(&tAdapterEqp);
	
	if (!bRet)
	{//接入分配失败		
		MdlError(Ums_Mdl_Call, ("OnConfCnsCall alloc new adapter failed! wConfID:%d, ConfTemp:%s\n", GetInsID(), tConfTemp.m_achConfName));
		return EmCnsCallReason_resourcefull;
	}
	
	if (!m_pcNodeMgr->AssignNodeRes(&tCallNode, &tAdapter))
	{
		MdlError(Ums_Mdl_Call, ("OnConfCnsCall AssignNodeRes failed! wConfID:%d, ConfTemp:%s\n", GetInsID(), tConfTemp.m_achConfName));		
		return EmCnsCallReason_resourcefull;
	}

	tCallNode.m_tAdapterEqp = tAdapter;

	tCallNode.m_dwStackHandle = tHandle.handPaCall;
	tCallNode.m_emEpType = tCaller.m_emSrcEpType;

	tCallNode.m_tConfName = tCaller.m_tSrcAddr.GetValidAlias();
	tCallNode.m_tCalledAddr = tCaller.m_tSrcAddr;
    tCallNode.m_emCallProtocol = tCaller.m_emTpProtocol;
	
	u16 wEpIndex = tConfTemp.m_atEpList.FindEpIndex(ptEpAddr->m_wEpID);
	if (TP_INVALID_INDEX == wEpIndex)
	{
		MdlError(Ums_Mdl_Call, ("OnConfCnsCall can not find ep in list! wConfID:%d, ConfTemp:%s EPID:%d\n",
			                     GetInsID(), tConfTemp.m_achConfName,ptEpAddr->m_wEpID));
		return EmCnsCallReason_Rejected;
	}
	else
	{
		tConfTemp.m_tTempCfgEx.m_awEpID[wEpIndex] = ptEpAddr->m_wEpID;
		tConfTemp.m_tTempCfgEx.m_aemCallProtocol[wEpIndex] = tCallNode.m_emCallProtocol;
	}

	//开启会议
	EmCnsCallReason emCallRet = EmCnsCallReason_unknown;

	if (tCaller.m_bIsCreatConf)
	{// 临时多点		
		emCallRet = EventStartConf((u8*)&tConfTemp, sizeof(tConfTemp), &tCallNode, FALSE);
	}
	else
	{// 323呼叫模板,不延时
		if (emTPEndpointH323MT == tCaller.m_emSrcEpType || emTPEndpointH323SingleMCU == tCaller.m_emSrcEpType)
		{
			emCallRet = EventStartConf((u8*)&tConfTemp, sizeof(tConfTemp), &tCallNode, FALSE);
		}
		// CNS呼叫模板
		else
		{
			emCallRet = EventStartConf((u8*)&tConfTemp, sizeof(tConfTemp), &tCallNode, TRUE);
		}
		
	}

	if (EmCnsCallReason_success != emCallRet)
	{
		m_pcNodeMgr->ReleaseNodeRes(&tCallNode);
		tCallNode.Clear();

		StopConf();
		
		MdlError(Ums_Mdl_Call, ("OnConfCnsCall EventStartConf failed! wConfID:%d, ConfTemp:%s, CallRet:%d\n", 
																			GetInsID(), tConfTemp.m_achConfName, emCallRet));	
		return emCallRet;
	}
		
	return EmCnsCallReason_success;
}

/*==============================================================================
函数名    :  OnCnsCallExistConf
功能      :  请求加入会议
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-4               zhaixiaogang
==============================================================================*/
EmCnsCallReason CUmsConfInst::OnCnsCallExistConf(const TUmsHandle& tInHandle, TUmsCallInfo& tCaller)
{
	TUmsHandle tOutHandle;
	tOutHandle.m_dwAdapteID = tInHandle.m_dwAdapteID;
	tOutHandle.handPaCall = tInHandle.handPaCall;

	if (emTPEndpointTypeUMS == tCaller.m_emSrcEpType)
	{
		return EmCnsCallReason_Busy;

		TCapNode* ptCallNode = m_pcNodeMgr->GetCaller();
		//一个会议只能被一个UMS呼入
		if (ptCallNode->m_bUsed)
		{
			ObjHint(("OnCnsCallExistConf reject call. m_tCaller is used. instID:%d, caller:%s\n", GetInsID(), tCaller.m_tSrcAddr.m_tAlias.m_abyAlias));
			return EmCnsCallReason_Busy;
		}

		TCallNode* ptTmpNode = m_pcNodeMgr->GetNodeByName(tCaller.m_tSrcAddr.m_tAlias, NULL);
		if (NULL != ptTmpNode)
		{
			ObjHint(("OnCnsCallExistConf reject ums call. Caller is in conf. instID:%d, caller:%s\n", GetInsID(), tCaller.m_tSrcAddr.m_tAlias.m_abyAlias));
			return EmCnsCallReason_Busy;
		}
		
		TEqpRes tAdapter;
		TAdaptEqpParam tAdapterEqp;
		tAdapterEqp.m_ptEqpRes = &tAdapter;
		tAdapterEqp.m_ptEqpRes->m_dwEqpNode = tInHandle.m_dwAdapteID;
		BOOL32 bRet = AssignEqpByNodeEx(&tAdapterEqp);
		if (!bRet)
		{//接入分配失败
			MdlError(Ums_Mdl_Call, ("OnCnsCallExistConf ums OnCallAddConf  alloc new adapter failed!\n"));
			return EmCnsCallReason_hungup;
		}

		if (!m_pcNodeMgr->AssignNodeRes(ptCallNode, &tAdapter))
		{
			MdlError(Ums_Mdl_Call, ("OnCnsCallExistConf ums OnCallAddConf  alloc new res failed!\n"));
			return EmCnsCallReason_hungup;
		}

		//被上级呼入后下级要改变主席为上级时，先通知主席CNS取消它的主席地位
		TCallNode* ptNode = m_pcNodeMgr->GetLocalNode(chairID());
		if (NULL != ptNode && ptNode->IsCallOn() && ptNode->IsCns())
		{
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);

			BOOL32 isChair = FALSE;		
			UmsSendConfCtrl(tOutHandle, evtp_Conf_IsChair_Notify, &isChair, sizeof(isChair));		
		}

		DestroyMediaOnCallerOnline();
		SetCurSpeaker(m_pcNodeMgr->GetCaller());
		SetChairID(m_cSpeaker.GetCur());

		ptCallNode->m_bUsed = TRUE;
		ptCallNode->m_tCalledAddr = tCaller.m_tSrcAddr;
		ptCallNode->m_emCallState = ums_UmsConfNodeState_calling;
		ptCallNode->m_tAdapterEqp = tAdapter;
		ptCallNode->m_bIsCaller = FALSE;
        ptCallNode->m_emCallProtocol = tCaller.m_emTpProtocol;

		//设置为非上级
		m_pcCallMgr->SetChair(FALSE);
		
		TMakeCallPara tCallPara;
		m_pcCallMgr->MakeCallInfo(tCallPara, *ptCallNode, TRUE);	
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptCallNode->m_wEpID);
		tOutHandle.handPaCall = tInHandle.handPaCall;
		UmsAnwserCall(tOutHandle, TRUE, &tCallPara, EmCnsCallReason_success);

		NotifyApplySpeakerToUI();
	}
	else
	{
		BOOL32 bExist(FALSE);
		TCapNode* ptNode = m_pcNodeMgr->AddNewCall(tCaller.m_tSrcAddr, bExist);
		
		//没有空闲的实例
		if ( NULL == ptNode )
		{
			ObjError(("OnCnsCallExistConf reject call. conf is full. instID:%d, caller:%s\n", GetInsID(), tCaller.m_tSrcAddr.m_tAlias.m_abyAlias));
			return EmCnsCallReason_Local;
		}
		
		if (bExist && ptNode->m_emCallState == ums_UmsConfNodeState_calling)
		{
			ObjError(("OnCnsCallExistConf reject cns call. caller is in conf. instID:%d, caller:%s\n", GetInsID(), tCaller.m_tSrcAddr.m_tAlias.m_abyAlias));
			return  EmCnsCallReason_hungup;
		}

		TEqpRes tAdapter;	
		
		TAdaptEqpParam tAdapterEqp;
		tAdapterEqp.m_ptEqpRes = &tAdapter;
		tAdapterEqp.m_ptEqpRes->m_dwEqpNode = tInHandle.m_dwAdapteID;
		BOOL32 bRet = AssignEqpByNodeEx(&tAdapterEqp);
		if (!bRet)
		{		
			MdlError(Ums_Mdl_Call, ("OnCnsCallExistConf alloc new adapter failed!\n"));
			return  EmCnsCallReason_hungup;
		}
		
		if ( !ptNode->IsResReady() )
		{
			if (!m_pcNodeMgr->AssignNodeRes(ptNode, &tAdapter))
			{
				MdlError(Ums_Mdl_Call, ("OnCnsCallExistConf alloc new res failed!\n"));
				return  EmCnsCallReason_hungup;
			}
		}

		TUmsHandle tHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		tOutHandle.handPaCall = tInHandle.handPaCall;
		
		EmTpOprType emType = tp_OprType_Update;

		if( !bExist )
		{		
			//加入呼叫队列
			ptNode->m_bUsed = TRUE;
			ptNode->m_tCalledAddr = tCaller.m_tSrcAddr;
			ptNode->m_tConfName = ptNode->m_tCalledAddr.GetValidAlias();
		    ptNode->m_tAdapterEqp = tAdapter;

			emType = tp_OprType_Add;
		}
		ptNode->m_emCallState = ums_UmsConfNodeState_calling;
		ptNode->m_bIsCaller = FALSE;
		ptNode->m_emCallProtocol = tCaller.m_emTpProtocol;

		TMakeCallPara tCallPara;
		m_pcCallMgr->MakeCallInfo(tCallPara, *ptNode, TRUE);	
		
		UmsAnwserCall(tOutHandle, TRUE, &tCallPara, EmCnsCallReason_success);
		
		UpdateNodeInfo(emType, ptNode->m_wEpID);
	}

	MdlHint(Ums_Mdl_Call, ("OnCnsCallExistConf success. ConfID:%d Caller:%s\n", GetInsID(), tCaller.m_tSrcAddr.m_tAlias.m_abyAlias));

	return EmCnsCallReason_success;
}

void CUmsConfInst::OnCallConnect(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsCallInfo& tCallInfo = *(TUmsCallInfo*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	if (inst_idle == CurState())
	{
		UmsHangUp(tHandle);
		ObjError(("OnCallConnect state error. ConfID:%d\n", GetInsID()));
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->m_bUsed)
	{
		UmsHangUp(tHandle);
		ObjError(("OnCallConnect epid error. wConfID:%d, epid:%d\n", GetInsID(), wEpID));
		return;
	}

	if(!ptNode->IsResReady())
	{
		UmsHangUp(tHandle);
		ObjError(("OnCallConnect ep res error. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
		return;
	}

	if (ptNode->IsCallOn())
	{
		ObjError(("OnCallConnect Is Connect! conID:%d, epID:%d\n", GetInsID(), wEpID));
		return;
	}
	
	// 会场类型
	ptNode->m_emEpType = tCallInfo.m_emSrcEpType;
	//厂商ID 和 版本ID
	ptNode->m_emVendorID = tCallInfo.m_emVendorID;
	ptNode->m_byVer = tCallInfo.m_byVer;
	// 会场产品id
	strncpy(ptNode->m_abyPrdutID, tCallInfo.m_acPrdutID, sizeof(tCallInfo.m_acPrdutID));

	if (emTpSIP == tCallInfo.m_emTpProtocol && !ptNode->IsCns() && !ptNode->IsUms() && !ptNode->IsVRS())
	{// 以sip协议呼叫非cns ums且非vrs终端，挂掉，等待disconnect上来后，换h323协议重新呼叫
		UmsHangUp(tHandle);
		ptNode->SetNeedCallType(NodeNeedH323Call);
		ObjError(("OnCallConnect call MT by sip, need recall by h323! wConfID:%d, epid:%d\n", GetInsID(), wEpID));
		return;
	}

	//以323协议呼叫CNS或UMS挂掉，换sip呼
	if ((ptNode->IsCns() || ptNode->IsUms()) && emTpH323 == tCallInfo.m_emTpProtocol)
	{
		UmsHangUp(tHandle);
		ptNode->SetNeedCallType(NodeNeedSipCall);
		ObjError(("OnCallConnect call cns by h323, need recall by sip! wConfID:%d, epid:%d\n", GetInsID(), wEpID));
		return ;
	}

	if (m_tConfBaseInfo.m_tEncrypt.IsQt()&& !tCallInfo.m_tEncrypt.IsQt()) 
	{//量子加密时判断 加密模式不同 则挂断
		UmsHangUp(tHandle, EmCnsCallReason_StreamEncryptTypeNotEqual);
		ObjError(("OnCallConnect call Encry is not same. wConfID:%d, epid:%d, LocalMdl:%d, tCallInfo.Mdl:%d\n", 
			GetInsID(), wEpID, m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel, tCallInfo.m_tEncrypt.m_emEncryptModel));
		return ;
	}

	ptNode->m_dwStackHandle = tHandle.handPaCall;
	ptNode->m_emLevel = tCallInfo.m_emLevel;
	ptNode->m_emCallReason = EmCnsCallReason_success;
	
	ptNode->ResetNeedCall();	
	ptNode->CallOn();

	if (!ptNode->m_bIsCaller)//本地为被叫
	{
		ptNode->m_tConfName = tCallInfo.m_tSrcAddr.GetValidAlias();
		ObjHint(("OnCallConnect ptNode Name:%s. bIsCaller:%d, bCallByUI:%d, wConfID:%d, epid:%d, Protocol:%d, PrdutID:%s,%s, VendorID:%d, Ver:%u.\n", 
			ptNode->m_tConfName.m_abyAlias, ptNode->m_bIsCaller, ptNode->m_bCallByCMC, GetInsID(), wEpID, ptNode->m_emCallProtocol,
			ptNode->m_abyPrdutID, UmsNodeType(ptNode->m_emEpType), ptNode->m_emVendorID, ptNode->m_byVer));
	}
	else
	{
		ptNode->m_tConfName = tCallInfo.m_tDestAddr.GetValidAlias();
		ObjHint(("OnCallConnect ptNode Name:%s, bIsCaller:%d, bCallByUI:%d, wConfID:%d, epid:%d, Protocol:%d, PrdutID:%s,%s, VendorID:%d, Ver:%u.\n", 
			ptNode->m_tConfName.m_abyAlias, ptNode->m_bIsCaller, ptNode->m_bCallByCMC, GetInsID(), wEpID, ptNode->m_emCallProtocol,
			ptNode->m_abyPrdutID, UmsNodeType(ptNode->m_emEpType), ptNode->m_emVendorID, ptNode->m_byVer));
	}

	// 标识是否是渠道终端
	if (g_bKedaManuOn)
	{
		if (ptNode->m_emCallProtocol == emTpSIP)
		{
			ptNode->m_bIsKedaManu = TRUE;
		}
		else
		{
			ptNode->m_bIsKedaManu = FALSE;
			ptNode->m_bKedaManuCheckNum = 0;
// 			if (!m_bEpNodeCheck)
// 			{
// 				SetTimer(evtp_EpNodeTimer_Check, TP_INTERVAL_TIME_TWO_SECOND);
// 				m_bEpNodeCheck = TRUE;
// 			}
		}
	}

	if (ptNode->m_wEpID != chairID() && ptNode->m_bCallByCMC)
	{
		TConfEpIDInfo tConfID;
		tConfID.m_wConfID = GetInsID();
		tConfID.m_wEpID = ptNode->m_wEpID;
		tConfID.m_tAlias = ptNode->m_tConfName;
		NotifyConfCtrlMsgToCns(evtp_Conf_JoinConf_Notify, chairID(), &tConfID, sizeof(tConfID));
	}

	//主席身份判断
	if (chairID() == wEpID)
	{
		if (ptNode->IsCns())
		{
			BOOL32 isChair = TRUE;
			TUmsHandle tOutHandle;
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
			UmsSendConfCtrl(tOutHandle, evtp_Conf_IsChair_Notify, &isChair, sizeof(isChair));		
		}
		else if (ptNode->IsUms()) //上级的主席不能是UMS
		{			
			if (IsChairConf())
			{
				ObjHint(("OnCallConnect Chair is ums Ep. ConfID:%d\n", GetInsID()));
				SelfHungupImmediately(TP_UMS_ChairIsUMS);
				return;
			}
		}
		else
		{//主席可以是323终端
		}
	}

	if (ptNode->m_wEpID != CALLER_EP_INDEX && ptNode->m_bSetMediaKeyMT)
	{//量子秘钥 1、只发给下级 2、平台ums和此终端直接协商的不在发
		TUmsHandle tHandle;
		m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
		
		TTPMediaKeyInfo tInfo;
		for (u8 byIndx = 0; byIndx < TP_MAX_OLD_KEY_NUM; byIndx++)
		{
			if (0 == m_atMediaKey[byIndx].m_dwQtFlag)
			{
				continue;
			}
			tInfo.m_dwHandle = m_atMediaKey[byIndx].m_dwHandle;
			memcpy(tInfo.m_szAlias, m_atMediaKey[byIndx].m_szAlias, TP_MAX_ALIAS_LEN);
			tInfo.m_szAlias[TP_MAX_ALIAS_LEN] = '\0';
			tInfo.m_wIndex = m_atMediaKey[byIndx].m_wIndex;
			memcpy(tInfo.m_szMediaKey1, m_atMediaKey[byIndx].m_szMediaKey, TP_MAX_MEDIAKEY_LEN/4);
			memcpy(tInfo.m_szMediaKey2, m_atMediaKey[byIndx].m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
			memcpy(tInfo.m_szMediaKey3, m_atMediaKey[byIndx].m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
			memcpy(tInfo.m_szMediaKey4, m_atMediaKey[byIndx].m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
			
			tInfo.m_dwKeyLen = m_atMediaKey[byIndx].m_dwKeyLen;
			tInfo.m_emKeyFrequency = m_atMediaKey[byIndx].m_emKeyFrequency;
			tInfo.m_dwQtFlag = m_atMediaKey[byIndx].m_dwQtFlag;
			
			UmsSendConfCtrl(tHandle, evtp_MediaKey_Nty, &tInfo, sizeof(tInfo));
			ObjHint(("OnCallConnect wIndex:%d,wHandle:%d,keyFreq:%d,wQtFlag:%d.\n",
				tInfo.m_wIndex,tInfo.m_dwHandle,tInfo.m_emKeyFrequency,tInfo.m_dwQtFlag));
		}
	}

	return;
}

void CUmsConfInst::NotifySelfHungup(u32 dwReason)
{
	if ( m_bIsQuiting )
	{//已经正在退出会议了 则不再 再次结会
		return ;
	}

	ObjError(("NotifySelfHungup. wConfID:%d, Reason:%d\n", GetInsID(), dwReason));

	u16 wConfID = GetInsID();
	TLogUser tUser;
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_HungUpConf_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&wConfID, sizeof(wConfID));
	cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
	
	if (0 != dwReason)
	{
		TTPUmsReasonInd tInd;
		tInd.m_wConfID = wConfID;
		tInd.m_dwReason = dwReason;
		
		NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd));
	}

    m_bIsQuiting = TRUE;

	return;
}

void CUmsConfInst::SelfHungupImmediately(u32 dwReason)
{
	if ( m_bIsQuiting )
	{//已经正在退出会议了 则不再 再次结会
		return ;
	}
	
	u16 wConfId = GetInsID();
	ObjError(("SelfHungupImmediately. wConfID:%d, Reason:%d\n", wConfId, dwReason));
	
	if (0 != dwReason)
	{
		TTPUmsReasonInd tInd;
		tInd.m_wConfID = wConfId;
		tInd.m_dwReason = dwReason;
		
		NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd));
	}
	
	EventHungConf(NULL);
	
	return;
}

void CUmsConfInst::NotifyReasonToUI(u32 dwType, u32 dwReason, u16 wDstEpID, 
									u32 dwReserve1, u32 dwReserve2, u32 dwReserve3)
{
	TTPUmsReasonInd tInd;
	tInd.m_wConfID = GetInsID();
	tInd.m_wEpID = wDstEpID;
	tInd.m_dwReason = dwReason;
	tInd.m_dwReserve1 = dwReserve1;
	tInd.m_dwReserve2 = dwReserve2;
	tInd.m_dwReserve3 = dwReserve3;

	if ( dwType & EmUI_UMC )
	{
		NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd));
	}

	if( dwType & EmUI_CNC )
	{
		if ( wDstEpID == TP_INVALID_INDEX )
		{//群发
			for (TCapNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
			{
				if (!ptItor->IsCallOn())
				{
					continue;
				}

				if ( !ptItor->IsUms() )
				{
					tInd.m_wEpID = ptItor->m_wEpID;
				}

				NotifyConfCtrlMsgToCns(ev_UmsCommonReasonToUI_Ind, ptItor->m_wEpID, &tInd, sizeof(tInd));
			}
		}
		else
		{
			TCallNode* ptNode = m_pcNodeMgr->GetNode(tInd.m_wEpID);
			TCapNode* ptFather = m_pcNodeMgr->GetForeFatherNode(ptNode);
			if ( NULL == ptNode || NULL == ptFather || !ptNode->IsChanOn() )
			{
				return ;
			}

			if ( ptNode != ptFather )
			{
				tInd.m_wEpID = ptNode->m_wLowChildEpID;
			}

			NotifyConfCtrlMsgToCns(ev_UmsCommonReasonToUI_Ind, ptFather->m_wEpID, &tInd, sizeof(tInd));
		}
	}
	return ;
}

void CUmsConfInst::OnCallDisConnect(CTpMsg *const ptMsg, BOOL32 bFromStack)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	EmCnsCallReason emReason = *(EmCnsCallReason*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	if (inst_idle == CurState()) 
	{
		ObjHint(("OnCallDisConnect state error. instID:%d\n", GetInsID()));
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode)
	{
		ObjError(("OnCallDisConnect ep Index error. EpID:%d\n", wEpID));
		return;
	}

	BOOL32 bNeedReCallBy323 = ptNode->m_bNeedReCallBy323;
	m_pcNodeMgr->delepip(ptNode->m_wEpID);

	ObjHint(("OnCallDisConnect ConfID:%d, wEpID:%d, Name:%s, IsCaller:%d, bCallByUI:%d, CallOn:%d, Reason:(%d->%s), CallProtocol:%d, NeedCallType:%d.\n"
		,GetInsID(), wEpID, ptNode->m_tConfName.m_abyAlias, ptNode->m_bIsCaller, ptNode->m_bCallByCMC,
		ptNode->IsCallOn(), TpEnumIdString(EmCnsCallReason, emReason), ptNode->m_emCallProtocol, ptNode->m_byNeedCallType));
	
	if (ptNode->IsNeedCall())
	{// 需要重新呼叫
		if (!ptNode->IsResReady())
		{
			if (!m_pcNodeMgr->AssignNodeRes(ptNode, NULL))
			{
				ObjError(("OnCallDisConnect ep AssignNodeRes error. EpID:%d\n", wEpID));
				return;
			}
		}

		ptNode->m_emCallProtocol = ptNode->IsNeedH323Call()?emTpH323:emTpSIP;
		ptNode->m_emCallState = ums_UmsConfNodeState_calling;
		TMakeCallPara tCall;
		m_pcCallMgr->MakeCallInfo(tCall, *ptNode, FALSE);		
		UmsMakeCall(tHandle, tCall);
		ptNode->ResetNeedCall();
		if (ptNode->m_emCallProtocol == emTpH323)
		{
			ptNode->m_bNeedReCallBy323 = TRUE;
		}

		return;
	}
	else
	{
		// 按照下面业务处理
	}

	if (!( Is_Caller_Node(wEpID) ||  ptNode->IsCallOn() || EmCnsCallReason_Busy == emReason || EmCnsCallReason_Rejected == emReason
		|| EmCnsCallReason_PeerAbnormal == emReason || EmCnsCallReason_peerhungup == emReason 
		|| EmCnsCallReason_Exist == emReason || EmCnsCallReason_resourcefull == emReason
		|| EmCnsCallReason_NoConf == emReason || EmCnsCallReason_Abnormal == emReason) )
	{//1. Caller结点挂断，不再重呼
	 //2. 如果是已经链接的会场呼叫，等待下一个间隔再呼叫
	 //3. 对端忙、对端拒绝、对端挂断、对端掉线挂断等不改变重呼类型
	 //4. 会议存在、资源满、无此会议、本地掉线挂断等不改变重呼类型
		TMakeCallPara tCallPara;
		//切换下一次的呼叫类型
		switch (ptNode->m_emCallProtocol)
		{
		case emTpSIP:
			{
				if (emReason != EmCnsCallReason_Rejected && emReason != EmCnsCallReason_hungup 
					&& emReason != EmCnsCallReason_peerhungup && emReason != EmCnsCallReason_ConfOver 
					&& ptNode->IsResReady())
				{					
					ptNode->m_emCallProtocol = emTpH323;
					ptNode->m_emCallState = ums_UmsConfNodeState_calling;
					m_pcCallMgr->MakeCallInfo(tCallPara, *ptNode, FALSE);		
					UmsMakeCall(tHandle, tCallPara);
					return;
				}
			}
			break;

		case emTpH323:
			{
				ptNode->m_emCallProtocol = emTpSIP;
				break;
			}
		default:	
			return ;
		}
	}

	if ( !ptNode->m_bIsCaller 
		&& ptNode->m_emCallState == ums_UmsConfNodeState_calling
		&& ptNode->m_wEpID == chairID() )
	{//被动呼叫且主席 如果协商失败 则结会
		ObjHint(("OnCallDisConnect Called Disconnect! hungup! ConfID:%d, EpID:%d\n",GetInsID(), ptNode->m_wEpID));
		SelfHungupImmediately(TP_UMS_ChairIsFailed);
		return ;
	}

	EmUmsConfNodeState emOldCallState = ptNode->m_emCallState;
	EmCnsCallReason	emOldCallReason = ptNode->m_emCallReason;
	//EmTpConfProtocol emOldCallProtocol = ptNode->m_emCallProtocol;
	if ( ptNode->IsCallOn() || ptNode->m_emCallState == ums_UmsConfNodeState_calling )
	{
		HungUp(ptNode->m_wEpID, FALSE, !bFromStack, emReason);//里面会调用ptNode->HungUp()
		//上级断线，则挂断会议
		if (!IsChairConf() && Is_Caller_Node(ptNode->m_wEpID))
		{
			ObjHint(("OnCallDisConnect This is Low conf, hungup by up! ConfID:%d.\n", GetInsID()));

			if (EmCnsCallReason_peerhungup == emReason)
			{
				SelfHungupImmediately();
			}
			else
			{
				SelfHungupImmediately(TP_UMS_SuperDropped);
			}
			return;
		}
		else
		{
			AjustSpeakerOnNodeDisConn(ptNode);
		}
	}
	
	//在这之前已经挂断，则不更新呼叫状态
	if (EmCnsCallReason_hungup == emReason || EmCnsCallReason_peerhungup == emReason ||
		EmCnsCallReason_ConfOver == emReason || EmCnsCallReason_Rejected == emReason ||
		emOldCallState == ums_UmsConfNodeState_stopcall)
	{
		ptNode->m_emCallState = ums_UmsConfNodeState_stopcall;
	}
	else
	{
		ptNode->m_emCallState = ums_UmsConfNodeState_callfailed;		
	}

	//在这之前已经挂断，则不更新呼叫原因
	if( !(emOldCallReason == EmCnsCallReason_hungup && emOldCallState == ums_UmsConfNodeState_stopcall))
	{
		ptNode->m_emCallReason = emReason;
	}	

	if (emOldCallReason == EmCnsCallReason_Abnormal)
	{
		ptNode->m_emCallReason = EmCnsCallReason_Abnormal;
		ptNode->m_emCallState = ums_UmsConfNodeState_callfailed;
	}

	//因UMS资源满掉线 则停止呼叫
	if (emOldCallReason == EmCnsCallReason_resourcefull)
	{
		ptNode->m_emCallReason = EmCnsCallReason_resourcefull;
		ptNode->m_emCallState = ums_UmsConfNodeState_stopcall;
	}

	if( emOldCallState == ums_UmsConfNodeState_online )
	{//原先在线，才更新
		UpdateNodeInfo(tp_OprType_Update, ptNode->m_wEpID);
	}
	
	//立即更新
	if (ptNode->IsUms() && !Is_Caller_Node(ptNode->m_wEpID) && (EmCnsCallReason_peerhungup == emReason))
	{
		if (!VALID_ALL_EPID(ptNode->m_wChildEpID))
		{
			ptNode->m_emEpType = emTPEndpointTypeCNS;
		}
		NotifyUpdateNodeToUi();
	}

	//假如对端会场掉线和对端不可达，必须重呼
	if ((ptNode->m_emCallReason != EmCnsCallReason_hungup && ptNode->m_emCallReason != EmCnsCallReason_peerhungup &&
		ptNode->m_emCallReason != EmCnsCallReason_ConfOver && ptNode->m_emCallReason != EmCnsCallReason_Rejected)
		|| ptNode->m_emCallReason == EmCnsCallReason_PeerAbnormal || ptNode->m_emCallReason == EmCnsCallReason_Unreachable  )
	{
		//定时呼叫未上线会场
		
		MdlHint(Ums_Mdl_Call,("[OnCallDisConnect] ConfID:%d, Recall Timely Node is %s\n", GetInsID(), ptNode->m_tConfName.m_abyAlias));
		KillTimer(evtp_CallNode_time);
		
		if (bNeedReCallBy323)
		{
			ptNode->m_emCallProtocol = emTpH323;
			if (m_pcNodeMgr->AssignNodeRes(ptNode, NULL))
			{
					ptNode->m_emCallState = ums_UmsConfNodeState_calling;
					TMakeCallPara tCall;
					m_pcCallMgr->MakeCallInfo(tCall, *ptNode, FALSE);		
					UmsMakeCall(tHandle, tCall);
					++ptNode->m_wCallBy323Num;
					if (MAX_323_CALL_NUM == ptNode->m_wCallBy323Num)
					{
						ptNode->m_bNeedReCallBy323 = FALSE;
						ptNode->m_wCallBy323Num = 0;
					}
					return;
			}
		}

		if (m_pcNodeMgr->FirstNode() == m_pcNodeMgr->FirstNeedCallNode())
		{
			SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
		}
		else
		{//批量呼叫未完成，仍然快速呼叫
			SetTimer(evtp_CallNode_time, TP_INTERVAL_TIME_THREE_SECOND);
		}
		if (ptNode->m_emEpType == emTPEndpointTypeUMS)
		{
			u16 awChildEpID[TP_CONF_MAX_CNSNUM];
			u16 wEpChildNum = m_pcNodeMgr->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, ptNode);
			for (u16 wI = 0; wI < wEpChildNum; ++wI)
			{
				TCallNode* pTempNode = m_pcNodeMgr->GetNode(awChildEpID[wI]);
				if (NULL != pTempNode && pTempNode->m_bCallByCMC)
				{
					pTempNode->m_emCallReason = ptNode->m_emCallReason;
					u8 byBuf[sizeof(TTpCallAddr) + sizeof(EmCnsCallReason)] = {0};
					memcpy(byBuf, &pTempNode->m_tCalledAddr, sizeof(TTpCallAddr));
					memcpy(byBuf + sizeof(TTPAlias), &pTempNode->m_emCallReason, sizeof(EmCnsCallReason));
					
					NotifyConfCtrlMsgToCns(ev_UmsInviteCnsByAlias_Ind, chairID(), byBuf, sizeof(byBuf));
				}
				pTempNode->m_bCallByCMC = FALSE;
			}
		}
	}

	//判断此时是否还有: 未主动挂断的会场
	if (!m_bIsQuiting && IsChairConf())
	{
		BOOL32 bHaveActivNode = FALSE;
		u16 awAllEpID[TP_CONF_MAX_CNSNUM] = {0};
		u16 wEpAllNum = m_pcNodeMgr->GetAllNode(awAllEpID, TP_CONF_MAX_CNSNUM );
		for (u16 wIndex = 0; wIndex < wEpAllNum; ++wIndex)
		{
			TCallNode* ptNodeTmp = m_pcNodeMgr->GetNode(awAllEpID[wIndex]);
			if ( ptNodeTmp->m_emCallState != ums_UmsConfNodeState_stopcall && ptNodeTmp->IsMtEp() && 
				ptNodeTmp->m_emEpType != emTPEndpointH323SingleMCU )
			{//当会议中的所有终端或者cns都主动挂断后，需要自动结会。
				bHaveActivNode = TRUE;
				break;
			}
		}
		
		if (!bHaveActivNode)
		{
			SelfHungupImmediately(TP_UMS_AllEpHungUp);
			return;
		}	
	}
	
	if (EmCnsCallReason_success != ptNode->m_emCallReason && ptNode->m_bCallByCMC)
	{
		TLogUser tUser;

		TConfCallEpAddr tEpAddr;
		tEpAddr.m_wConfID = GetInsID();
		tEpAddr.m_tCallAddr = ptNode->m_tCalledAddr;
		
		CTpMsg cMsg;	
		cMsg.SetEvent(evtp_CallEP_result);
		cMsg.SetBody(&tUser, sizeof(tUser));
		cMsg.CatBody(&tEpAddr, sizeof(tEpAddr));
		cMsg.CatBody(&ptNode->m_emCallReason, sizeof(ptNode->m_emCallReason));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));

		u8 byBuf[sizeof(TTpCallAddr) + sizeof(EmCnsCallReason)] = {0};
		memcpy(byBuf, &tEpAddr.m_tCallAddr, sizeof(TTpCallAddr));   
		memcpy(byBuf + sizeof(TTpCallAddr), &ptNode->m_emCallReason, sizeof(EmCnsCallReason));
		
		//回应CNS
		NotifyConfCtrlMsgToCns(ev_UmsInviteCnsByAlias_Ind, chairID(), byBuf, sizeof(byBuf));
	}

	ptNode->m_bCallByCMC = FALSE;

	return;
}

void CUmsConfInst::OnChanConnect(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsNodeCapset& tNodeCap = *(TUmsNodeCapset*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	u16 wEpID = tHandle.GetEpID();
	ObjHint(("OnChanConnect confid:%d, epid:%d, audsnd:%d, audrcv:%d, vidsnd:%d, vidrcv:%d.\n",
		GetInsID(), wEpID,
		tNodeCap.m_wAudEncNum, tNodeCap.m_wAudDecNum, tNodeCap.m_wVidEncNum, tNodeCap.m_wVidDecNum));

	if (inst_idle == CurState())
	{
		UmsHangUp(tHandle);
		ObjError(("OnChanConnect state error. ConfID:%d\n", GetInsID()));
		return;
	}

	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode)
	{
		UmsHangUp(tHandle);
		ObjError(("OnChanConnect ep Index error. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
		return;
	}
	
	if (!ptNode->IsCallOn())
	{
		ObjError(("OnChanConnect ep state error. ConfID:%d, EpID:%d, state:%s\n", GetInsID(), wEpID, UmsNodeConfType(ptNode->m_emCallState)));
		return;
	}

	if (ptNode->IsChanOn())
	{// 二代高清，可能存在多次协商，回调多次chanconnect的情形（非必现），这种情况，业务直接挂断，重新呼叫。
		u8 byCallType = ptNode->m_emCallProtocol == emTpSIP?NodeNeedSipCall:NodeNeedH323Call;
		HungUp(wEpID, FALSE, TRUE, EmCnsCallReason_hungup); // 先挂断，包括业务
		ptNode->SetNeedCallType(byCallType);
		ObjError(("OnChanConnect ep chan has opend, need recall! ConfID:%d, EpID:%d, CallType:%d.\n", GetInsID(), wEpID, byCallType));
		return;
	}

	if(!ptNode->IsResReady())
	{
		UmsHangUp(tHandle);
		ObjError(("OnChanConnect ep res error. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
		return;
	}

	// 协商上来的码流密钥和本地密钥比对，不一致则挂断
	if (!(m_tConfBaseInfo.m_tEncrypt == tNodeCap.m_tEncrypt) && !m_tConfBaseInfo.m_tEncrypt.IsQt())
	{
		UmsHangUp(tHandle);
		ObjError(("OnChanConnect ep Encrypt not equal! ConfID:%d, EpID:%d, local(%d(0:none;1:des;2:aes;4:qt_every_s;5:qt_every_m;6:qt_every_c ) %d, %s), from ChanConnect(%d(0:none;1:des;2:aes;4:qt_every_s;5:qt_every_m;6:qt_every_c), %d, %s)\n", 
			GetInsID(), wEpID, m_tConfBaseInfo.m_tEncrypt.m_emEncryptModel,
			m_tConfBaseInfo.m_tEncrypt.m_byKeyLen, 
			m_tConfBaseInfo.m_tEncrypt.m_achEncKey,
			tNodeCap.m_tEncrypt.m_byKeyLen,
			tNodeCap.m_tEncrypt.m_achEncKey));
		return;
	}

	// 如果协商出来的通道只有1路并且不是中间路，那业务将这路通道挪到中间路
	CheckMidChanInfo(ptNode, tNodeCap);

 	if (ptNode->IsMtEp())
	{		
 		TUmsHandle tOutHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
 		UmsSendConfCtrl(tOutHandle, evtp_Conf_MultConf_Notify, NULL, 0);			
	}

	if ((0 == tNodeCap.m_wVidDecNum) && (0 == tNodeCap.m_wVidEncNum))
	{
		ObjError(("OnChanConnect capset vid snd and rcv chan num error.ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
		
		if (ptNode->IsUms())
		{
			if (Is_Caller_Node(ptNode->m_wEpID))
			{//下级
				StopConf();

				TDelConfList tList;
				tList.m_wRefreshNum = 1;
				tList.m_awConfIDList[0] = GetInsID();
				
				CTpMsg cMsg;	
				cMsg.SetEvent(evtp_DelConflist_Notify);
				cMsg.SetBody(&tList, sizeof(tList));
				cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
				return;
			}
			//上级
			UmsHangUp(tHandle);
			return;
		}
	}

	
	// add by gaoyong
	TUmsConfBase tConfBaseInfoBk;
	memcpy(&tConfBaseInfoBk, &m_tConfBaseInfo, sizeof(TUmsConfBase));

	BOOL32 bIsAdjustConfBit = FALSE; // 是否已经调整会议码率

	//add
	u16 wIndex = 0;
	u16 wLoop = 0;
	if (tNodeCap.m_wVidDecNum > 0)
	{
		//视频rcv能力不合法，关闭所有视频rcv通道
		MdlHint(Ums_Mdl_Call, ("Before Check vidrcv cap:(%s,%s,%d,%d)(%s,%s,%d,%d)\n", UmsVidProfilePrint(tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl)
			, UmsVidResPrint(tNodeCap.m_tVidRcvCap.m_tHp.m_emRes), tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate, tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate
			, UmsVidProfilePrint(tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl), UmsVidResPrint(tNodeCap.m_tVidRcvCap.m_tBp.m_emRes)
			, tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate, tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate));

		// add by gaoyong
		if (m_bIsNeedDelayCallNode && !bIsAdjustConfBit)
		{// cns呼ums会议模板时，需要调整会议码率
			tConfBaseInfoBk.m_wConfBitRate = tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate;
			tConfBaseInfoBk.m_wBpConfBitRate = tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate;
		}

		if (!CTpTypeAdpt::IsValidPriFormat(tNodeCap.m_tVidRcvCap.m_tHp, tConfBaseInfoBk, ptNode->IsMtEp(), FALSE))
		{//接收HP无效
			tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = emTPVResEnd;
			if (!CTpTypeAdpt::IsValidPriFormat(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk, ptNode->IsMtEp(), FALSE))
			{
				MdlHint(Ums_Mdl_Call, ("OnChanConnect vid rcv hp and bp invalid.\n"));
				tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
				UmsCloseChan(tHandle, emChanRecvPrimoVideo, tNodeCap);
			}
			else
			{
				if (!ptNode->IsMtEp())
				{//UMS要在会议模板中选择合适的
					if (!CTpTypeAdpt::IsEqualConfBaseCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk))
					{
						u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk);
						if (TP_INVALID_INDEX == wLoc)
						{
							MdlHint(Ums_Mdl_Call, ("OnChanConnect GetSuitCap vid rcv bp cap wrong.\n"));
							tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
							UmsCloseChan(tHandle, emChanRecvPrimoVideo, tNodeCap);
						}
						else
						{
							memcpy(&tNodeCap.m_tVidRcvCap.m_tBp, &tConfBaseInfoBk.m_atTpMainVideoRes[wLoc], sizeof(TUmsVidFormat));
						}
					}
				}

				if (m_bIsNeedDelayCallNode && !bIsAdjustConfBit)
				{
					m_tConfBaseInfo.m_wConfBitRate = tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate;
					m_tConfBaseInfo.m_wBpConfBitRate = m_tConfBaseInfo.m_wConfBitRate;				
					bIsAdjustConfBit = TRUE;

					for (wLoop = 0; wLoop < m_tConfBaseInfo.m_wMainNum; wLoop++)
					{
						m_tConfBaseInfo.m_atTpMainVideoRes[wLoop].m_wBitrate = m_tConfBaseInfo.m_wConfBitRate;
					}

					// for bas
					m_pcBas->AdjustConfBitrateForBas(m_tConfBaseInfo.m_wConfBitRate);

					MdlHint(Ums_Mdl_Call, ("OnChanConnect  rcv hp is invalid, bp is valid, set to ConfBitRate, m_wConfBitRate:%d.\n"
						, m_tConfBaseInfo.m_wConfBitRate));
				}

			}
		}
		else
		{//接收HP有效
			if (!ptNode->IsMtEp())
			{
				if (!CTpTypeAdpt::IsEqualConfBaseCap(tNodeCap.m_tVidRcvCap.m_tHp, tConfBaseInfoBk))
				{
					u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidRcvCap.m_tHp, tConfBaseInfoBk);
					if (TP_INVALID_INDEX == wLoc)
					{
						MdlHint(Ums_Mdl_Call, ("OnChanConnect GetSuitCap vid rcv hp cap wrong.\n"));
						tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = emTPVResEnd;
					}
					else
					{
						memcpy(&tNodeCap.m_tVidRcvCap.m_tHp, &tConfBaseInfoBk.m_atTpMainVideoRes[wLoc], sizeof(TUmsVidFormat));
					}
				}
				else
				{
					tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
				}
				
				if (emTPVResEnd == tNodeCap.m_tVidRcvCap.m_tHp.m_emRes)
				{
					if (!CTpTypeAdpt::IsValidPriFormat(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk, ptNode->IsMtEp(), TRUE))
					{
						MdlHint(Ums_Mdl_Call, ("OnChanConnect unfind suit rcv hp cap and snd bp cap is invalid.\n"));
						tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
						UmsCloseChan(tHandle, emChanRecvPrimoVideo, tNodeCap);
					}
					else
					{
						if (!CTpTypeAdpt::IsEqualConfBaseCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk))
						{
							u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk);
							if (TP_INVALID_INDEX == wLoc)
							{
								MdlHint(Ums_Mdl_Call, ("OnChanConnect unfind suit rcv hp cap and get suit bp cap wrong.\n"));
								tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
								UmsCloseChan(tHandle, emChanRecvPrimoVideo, tNodeCap);
							}
							memcpy(&tNodeCap.m_tVidRcvCap.m_tHp, &tConfBaseInfoBk.m_atTpMainVideoRes[wLoc], sizeof(TUmsVidFormat));
						}
					}
				}
			}
			else
			{
				MdlHint(Ums_Mdl_Call, ("OnChanConnect cns vid rcv hp is valid, set vid rcv bp invalid.\n"));
				tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
			}

			if (m_bIsNeedDelayCallNode && !bIsAdjustConfBit)
			{
				m_tConfBaseInfo.m_wConfBitRate = tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate;
				m_tConfBaseInfo.m_wBpConfBitRate = m_tConfBaseInfo.m_wConfBitRate;				
				bIsAdjustConfBit = TRUE;

				for (wLoop = 0; wLoop < m_tConfBaseInfo.m_wMainNum; wLoop++)
				{
					m_tConfBaseInfo.m_atTpMainVideoRes[wLoop].m_wBitrate = m_tConfBaseInfo.m_wConfBitRate;
				}

				// for bas
				m_pcBas->AdjustConfBitrateForBas(m_tConfBaseInfo.m_wConfBitRate);

				MdlHint(Ums_Mdl_Call, ("OnChanConnect  rcv hp is valid, set to ConfBitRate, m_wConfBitRate:%d.\n"
					, m_tConfBaseInfo.m_wConfBitRate));
			}
		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("OnChanConnect rcvnum error. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
	}

	if (tNodeCap.m_wVidEncNum > 0)
	{
		//snd能力不合法，通知协议栈关闭所有视频snd通道
		MdlHint(Ums_Mdl_Call, ("Before Check vidsnd cap:(%s,%s,%d,%d)(%s,%s,%d,%d)\n", UmsVidProfilePrint(tNodeCap.m_tVidSndCap.m_tHp.m_emQualityLvl)
			, UmsVidResPrint(tNodeCap.m_tVidSndCap.m_tHp.m_emRes), tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate, tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate
			, UmsVidProfilePrint(tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl), UmsVidResPrint(tNodeCap.m_tVidSndCap.m_tBp.m_emRes)
			, tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate, tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate));
		
		if (m_bIsNeedDelayCallNode && !bIsAdjustConfBit)
		{// cns呼叫会议码率，需要调整会议码率，如果之前已经根据接收通道调整过，则不用再次调整
			tConfBaseInfoBk.m_wConfBitRate = tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate;
			tConfBaseInfoBk.m_wBpConfBitRate = tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate;
		}

		if (!CTpTypeAdpt::IsValidPriFormat(tNodeCap.m_tVidSndCap.m_tHp, tConfBaseInfoBk, ptNode->IsMtEp(), TRUE))
		{
			tNodeCap.m_tVidSndCap.m_tHp.m_emRes = emTPVResEnd;
			if (!CTpTypeAdpt::IsValidPriFormat(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk, ptNode->IsMtEp(), TRUE))
			{
				MdlHint(Ums_Mdl_Call, ("OnChanConnect vid snd hp and bp invalid.\n"));
				tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
				UmsCloseChan(tHandle, emChanSendPrimoVideo, tNodeCap);
			}
			else
			{
				if (!ptNode->IsMtEp())
				{
					if (!CTpTypeAdpt::IsEqualConfBaseCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk))
					{
						//取出最接近的会议模板中的能力
						u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk);
						if (TP_INVALID_INDEX == wLoc)
						{
							MdlHint(Ums_Mdl_Call, ("OnChanConnect GetSuitCap vid snd bp cap wrong.\n"));
							tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
							UmsCloseChan(tHandle, emChanSendPrimoVideo, tNodeCap);
						}
						else
						{
							MdlHint(Ums_Mdl_Call, ("OnChanConnect vid snd hp cap is invalid and get vid snd bp cap wrong.\n"));
							memcpy(&tNodeCap.m_tVidSndCap.m_tBp, &tConfBaseInfoBk.m_atTpMainVideoRes[wLoc], sizeof(TUmsVidFormat));
						}
					}
				}

				if (m_bIsNeedDelayCallNode && !bIsAdjustConfBit)
				{
					m_tConfBaseInfo.m_wConfBitRate = tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate;
					m_tConfBaseInfo.m_wBpConfBitRate = m_tConfBaseInfo.m_wConfBitRate;
					bIsAdjustConfBit = TRUE;

					for (wLoop = 0; wLoop < m_tConfBaseInfo.m_wMainNum; wLoop++)
					{
						m_tConfBaseInfo.m_atTpMainVideoRes[wLoop].m_wBitrate = m_tConfBaseInfo.m_wConfBitRate;
					}

					// for bas
					m_pcBas->AdjustConfBitrateForBas(m_tConfBaseInfo.m_wConfBitRate);

					MdlHint(Ums_Mdl_Call, ("OnChanConnect  snd hp is invalid, bp is valid, set to ConfBitRate, m_wConfBitRate:%d.\n"
						, m_tConfBaseInfo.m_wConfBitRate));
				}
			}
		}
		else
		{
			if (!ptNode->IsMtEp())
			{
				if (!CTpTypeAdpt::IsEqualConfBaseCap(tNodeCap.m_tVidSndCap.m_tHp, tConfBaseInfoBk))
				{
					//会议模板中取出最接近的
					u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidSndCap.m_tHp, tConfBaseInfoBk);
					if (TP_INVALID_INDEX == wLoc)
					{
						MdlHint(Ums_Mdl_Call, ("OnChanConnect GetSuitCap vid snd hp cap wrong.\n"));
						tNodeCap.m_tVidSndCap.m_tHp.m_emRes = emTPVResEnd;
					}
					memcpy(&tNodeCap.m_tVidSndCap.m_tHp, &tConfBaseInfoBk.m_atTpMainVideoRes[wLoc], sizeof(TUmsVidFormat));
				}
				else
				{
					tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
				}
				
				if (emTPVResEnd == tNodeCap.m_tVidSndCap.m_tHp.m_emRes)
				{
					if (!CTpTypeAdpt::IsValidPriFormat(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk, ptNode->IsMtEp(), TRUE))
					{
						MdlHint(Ums_Mdl_Call, ("OnChanConnect unfind suit snd hp cap and snd bp cap is invalid.\n"));
						tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
						UmsCloseChan(tHandle, emChanSendPrimoVideo, tNodeCap);
					}
					else
					{
						if (!CTpTypeAdpt::IsEqualConfBaseCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk))
						{
							u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk);
							if (TP_INVALID_INDEX == wLoc)
							{
								MdlHint(Ums_Mdl_Call, ("OnChanConnect unfind suit snd hp cap and get suit bp cap wrong.\n"));
								tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
								UmsCloseChan(tHandle, emChanSendPrimoVideo, tNodeCap);
							}
							memcpy(&tNodeCap.m_tVidSndCap.m_tBp, &tConfBaseInfoBk.m_atTpMainVideoRes[wLoc], sizeof(TUmsVidFormat));
						}
					}
				}
				
			}
			else
			{
				MdlHint(Ums_Mdl_Call, ("OnChanConnect cns vid snd hp valid, set vid snd bp invalid.\n"));
				tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
			}

			if (m_bIsNeedDelayCallNode && !bIsAdjustConfBit)
			{
				m_tConfBaseInfo.m_wConfBitRate = tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate;
				m_tConfBaseInfo.m_wBpConfBitRate = m_tConfBaseInfo.m_wConfBitRate;	
				bIsAdjustConfBit = TRUE;

				for (wLoop = 0; wLoop < m_tConfBaseInfo.m_wMainNum; wLoop++)
				{
					m_tConfBaseInfo.m_atTpMainVideoRes[wLoop].m_wBitrate = m_tConfBaseInfo.m_wConfBitRate;
				}

				// for bas
				m_pcBas->AdjustConfBitrateForBas(m_tConfBaseInfo.m_wConfBitRate);

				MdlHint(Ums_Mdl_Call, ("OnChanConnect  snd hp is valid, set to ConfBitRate, m_wConfBitRate:%d.\n"
					, m_tConfBaseInfo.m_wConfBitRate));
			}

		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("OnChanConnect vid sndnum error. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
	}

	if (!tNodeCap.m_tVidRcvCap.IsValidCap() && !tNodeCap.m_tVidSndCap.IsValidCap())
	{
		if (ptNode->IsUms())
		{
			// 级联会议通道没协商成功，要挂掉下级ums
			if (Is_Caller_Node(ptNode->m_wEpID))
			{//下级

				ObjError(("OnChanConnect fail, LowUms StopConf. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
				
				StopConf();				
				TDelConfList tList;
				tList.m_wRefreshNum = 1;
				tList.m_awConfIDList[0] = GetInsID();
				
				CTpMsg cMsg;	
				cMsg.SetEvent(evtp_DelConflist_Notify);
				cMsg.SetBody(&tList, sizeof(tList));
				cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
				return;
			}
			//上级

			ObjError(("OnChanConnect fail, UpUms UmsHangUp. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
			UmsHangUp(tHandle);
			return;
		}

		//视频通道未打开且音频通道也未打开 才挂断会议
		BOOL32 bDecRet = FALSE;
		BOOL32 bEncRet = FALSE;
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (tNodeCap.m_atAudDec[wIndex].m_bIsChanOn)
			{
				bDecRet = TRUE;
				break;
			}
		}
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (tNodeCap.m_atAudEnc[wIndex].m_bIsChanOn)
			{
				bEncRet = TRUE;
				break;
			}
		}
		if (!bDecRet && !bEncRet)
		{
			UmsHangUp(tHandle, EmCnsCallReason_Rejected);
			MdlError(Ums_Mdl_Call, ("OnChanConnect vid and aud chan not open, hung up conf. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
			return;
		}
	}


	//增加接入点数判断
	u16 wLiceNum = 0;
	if ( (tNodeCap.m_wVidEncNum > 0 && tNodeCap.m_tVidSndCap.IsValidCap())
		|| (tNodeCap.m_wVidDecNum > 0 && tNodeCap.m_tVidRcvCap.IsValidCap()) )
	{
		wLiceNum = tNodeCap.m_wVidEncNum > tNodeCap.m_wVidDecNum ? tNodeCap.m_wVidEncNum : tNodeCap.m_wVidDecNum;
	}

	u32 dwTmp = m_dwOnlineChanNum + wLiceNum;
	if (dwTmp > m_dwLicenseChanNum)
	{
		if (wEpID == chairID())
		{

			ObjError(("OnChanConnect assigned licenum to chair failed. ConfID:%d, EpID:%d, ChairID:%d, channum:%d, licenum:%d\n"
				, GetInsID(), wEpID, chairID(), m_dwOnlineChanNum, m_dwLicenseChanNum));
			StopConf();
			
			TDelConfList tList;
			tList.m_wRefreshNum = 1;
			tList.m_awConfIDList[0] = GetInsID();
			
			CTpMsg cMsg;	
			cMsg.SetEvent(evtp_DelConflist_Notify);
			cMsg.SetBody(&tList, sizeof(tList));
			cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
			return;
		}

		ptNode->m_emCallReason = EmCnsCallReason_resourcefull;
		
		if (ptNode->m_bCallByCMC)
		{
			u8 byBuf[sizeof(TTpCallAddr) + sizeof(EmCnsCallReason)] = {0};
			memcpy(byBuf, &ptNode->m_tCalledAddr, sizeof(TTpCallAddr));
			memcpy(byBuf + sizeof(TTpCallAddr), &ptNode->m_emCallReason, sizeof(EmCnsCallReason));
			NotifyConfCtrlMsgToCns(ev_UmsInviteCnsByAlias_Ind, chairID(),  byBuf, sizeof(byBuf));
			
			TLogUser tUser;
			CTpMsg cMsg;	
			cMsg.SetEvent(evtp_CallEP_result);
			
			TConfCallEpAddr tEpAddr;
			tEpAddr.m_wConfID =GetInsID();
			tEpAddr.m_tCallAddr = ptNode->m_tCalledAddr;	
			
			cMsg.SetBody(&tUser, sizeof(tUser));
			cMsg.CatBody(&tEpAddr, sizeof(tEpAddr));
			
			cMsg.CatBody(&ptNode->m_emCallReason, sizeof(ptNode->m_emCallReason));
			cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
			
		}
		ptNode->m_bCallByCMC = FALSE;
		
		UmsHangUp(tHandle, EmCnsCallReason_resourcefull);
		ObjError(("OnChanConnect m_dwOnlineChanNum:%d more than m_dwLicenseChanNum:%d ConfID:%d, EpID:%d\n"
			, m_dwOnlineChanNum, m_dwLicenseChanNum, GetInsID(), wEpID));
		return;
	}
	m_dwOnlineChanNum += wLiceNum;

	//////////////////////////////////////////////////////////////////////////
	m_pcNodeMgr->SetNodeCapSet(ptNode, tNodeCap);

	u32 dwEpRemoteIp = ptNode->m_tRmtChan.getvalidepip();

	if (ptNode->m_wVidSndNum > 0 
		|| ptNode->m_wVidRcvNum > 0
		|| ptNode->m_wAudSndNum > 0 
		|| ptNode->m_wAudRcvNum > 0 )
	{
		if (dwEpRemoteIp)
		{
			m_pcNodeMgr->addepip(ptNode->m_wEpID, dwEpRemoteIp);
		}
		ptNode->m_bAdjustChanOn = TRUE;
		AdjustNodeChanOn(ptNode);
	}
	else
	{
		UmsHangUp(tHandle, EmCnsCallReason_Rejected);//给对端拒绝提示
		MdlError(Ums_Mdl_Call, ("OnChanConnect no chan open. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
	}

}

void  CUmsConfInst::AdjustCapOnChanOn(TUmsHandle& tHandle, TCapNode* ptNode)
{
	TCallNode* ptChair = m_pcNodeMgr->GetCapsetNode(chairID());
	u16 wEpID = ptNode->m_wEpID;

	if (Is_Caller_Node(ptNode->m_wEpID))
	{
		m_pcCallMgr->CallerConnect();
		m_pcPollMgr->NotifyPollListToUI();
	}

	m_pcNodeMgr->AdjustResOnChanConnect(ptNode);
	if (ptNode->IsUms() && !Is_Caller_Node(ptNode->m_wEpID))
	{
		if (!m_pcCallMgr->MakeCascadeChair(*ptNode))
		{
			UmsHangUp(tHandle);
			ObjError(("OnChanConnect open casecade error. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
			return;
		}
	}

	MdlHint(Ums_Mdl_Call, ("AdjustCapOnChanOn. ConfID:%d, wEpID:%d, type:%d, m_dwOnlineChanNum:%d, Snd:%d(%s,%s,%d), Rcv:%d(%s,%s,%d)\n"
		, GetInsID(), ptNode->m_wEpID, ptNode->m_emEpType, m_dwOnlineChanNum, ptNode->m_wVidSndNum,
		UmsVidProfilePrint(ptNode->m_tVidSndFormat.m_tFormat.m_emQualityLvl),
		UmsVidResPrint(ptNode->m_tVidSndFormat.m_tFormat.m_emRes),
		ptNode->m_tVidSndFormat.m_tFormat.m_wFrameRate, ptNode->m_wVidRcvNum,
		UmsVidProfilePrint(ptNode->m_tVidRcvFormat.m_tFormat.m_emQualityLvl),
		UmsVidResPrint(ptNode->m_tVidRcvFormat.m_tFormat.m_emRes),
		ptNode->m_tVidRcvFormat.m_tFormat.m_wFrameRate));

	if (ptNode->m_bCallByCMC)
	{// 成功了，也提示下umc
		TLogUser tUser;
		CTpMsg cMsg;	
		cMsg.SetEvent(evtp_CallEP_result);
		
		TConfCallEpAddr tEpAddr;
		tEpAddr.m_wConfID =GetInsID();
		tEpAddr.m_tCallAddr = ptNode->m_tCalledAddr ;	
		
		cMsg.SetBody(&tUser, sizeof(tUser));
		cMsg.CatBody(&tEpAddr, sizeof(tEpAddr));
		
		cMsg.CatBody(&ptNode->m_emCallReason, sizeof(ptNode->m_emCallReason));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
	}

	ptNode->m_bCallByCMC = FALSE;//通道打开 认为上线 防止“通道协商失败后掉线”这种假上线现象
	ptNode->m_bChannelOpen = TRUE;

	if (wEpID == curSpeakerID())
	{
		m_pcCallMgr->FlowControl(wEpID, FLOW_CTROL_ALL_ENC, ptNode->m_tVidSndFormat.m_tFormat.m_wBitrate);
		if (wEpID == chairID())
		{
			m_pcCallMgr->FlowControl(wEpID, FLOW_CTROL_ALL_ENC, ptNode->m_tVidSndFormat.m_tFormat.m_wBitrate);
		}

		AskKeyByEpID(wEpID, EmAskKeySpeaker);
	}
	else if(wEpID == chairID())
	{
		m_pcCallMgr->FlowControl(wEpID, FLOW_CTROL_ALL_ENC, ptNode->m_tVidSndFormat.m_tFormat.m_wBitrate);
		AskKeyByEpID(wEpID, EmAskKeyChair);
	}
	else
	{
		m_pcCallMgr->FlowControl(wEpID, FLOW_CTROL_ALL_ENC, 0);
	}

	TUmsHandle tOutHandle;

	//通知对端会议信息
	TTPConfInfoNtfy tInfo;
	TChairConfInfo tChair;

	GetConfNtfyInfo(tInfo, tChair);
	
	if (!Is_Caller_Node(ptNode->m_wEpID))
	{
		tInfo.m_wConfID = GetInsID();
		tInfo.m_wEpID = ptNode->m_wEpID;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_StatusInfo_Notify, &tInfo, sizeof(tInfo));
	}

	if (IsChairConf() && (chairID() == wEpID || curSpeakerID() == wEpID)) //上级，通知下级UMS主席信息
	{
		for (TCallNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
		{		
			if (ptItor->IsCallOn() && ptItor->IsUms())
			{				
				m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptItor->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_StatusInfo_Notify, &tInfo, sizeof(tInfo));
			}
			//CNS通知主席信息
			if (ptItor->IsCallOn() && ptItor->IsCns() )
			{
				NotifyConfCtrlMsgToCns(ev_UmsChairConfInfo_Nty, ptItor->m_wEpID, &tChair, sizeof(TChairConfInfo));
			}
		}
	}

	if (chairID() == wEpID) 
	{
		NotifyChairCapToLowUms();
	}
	else
	{
		NotifyChairCapToLowUms(ptNode->m_wEpID);
	}

	//通知该会场会场列表
	NotifyAllCnsListToCns(ptNode);

	TConfEpID tConfId;
	tConfId.m_wConfID = GetInsID();
	tConfId.m_wEpID = ptNode->m_wEpID;
	
	if (m_bIsAllEpMute)
	{
		OnMuteEpForUmcCnc(&tConfId, m_bIsAllEpMute);
	}
	if (m_bIsAllEpQuiet)
	{
		OnQuietEpForUmcCnc(&tConfId, m_bIsAllEpQuiet);
	}

	m_pcNodeFsm->ChanConnect(ptNode);
	m_pcTvWallMgr->ChannelConnect(this, ptNode);
	m_pcPollMgr->OnChanConnect(ptNode);
	m_pcUmsDiscuss->OnChanConnect(ptNode);
	m_pcDual->OnChanConnect(ptNode);
	m_pcDataConf->OnChanConnect(ptNode);
	m_pcRollCallMgr->OnChanConnect(ptNode);
	m_pcAudMix->OnChanConnect(ptNode);

	if ( ptNode->m_wEpID == chairID() )
	{//主席上线
		m_pcBas->ChairChanConnect();
	}
	m_pcVmp->OnChanConnect(ptNode);

	TCallNode* ptSpeaker = m_pcNodeMgr->GetNode(curSpeakerID());
	TCapNode* ptFahterNode = m_pcNodeMgr->GetForeFatherNode(ptSpeaker);
	
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
	if (curSpeakerID() == ptNode->m_wEpID)
	{
		//保存发言人格式，用于发言人掉线，取广播合成图像（按发言人格式取）
		m_tSpeakerMediaFmt.SetSpeakerSndVidFmt(ptNode->m_tVidSndFormat.m_tFormat);
	    m_tSpeakerMediaFmt.SetSpeakerSndAudFmt(ptNode->m_tAudSndFormat.m_tFormat);

		if (curSpeakerID() != chairID())
		{
			m_pcBas->AdjustChairBas();
		}

		m_pcVmp->AdjustSpeakerVmp();
		m_pcBas->AdjustSpeakerBas();

		CNetPortMgr::CreateSpeakerToVirSpeaker(this);

		if (IsChairConf() || (!IsChairConf() && m_tSuperInfo.m_bSpeakOnline))
		{
			AdjustNewSpeakerToAllNode();
		}
	}
	//主席上线，此时主席和发言会场不是同一个人，此处m_wCurSpeaker肯定有效
	else if (chairID() == ptNode->m_wEpID)
	{
		//如果发言会场已经上线
		if (ptSpeaker->IsChanOn())
		{
			m_pcVmp->AdjustSpeakerVmp(FALSE, FALSE);
			m_pcBas->AdjustChairBas();
			AdjustNewSpeakerToAllNode(ptFahterNode->m_wEpID);
			AdjustNewSpeakerToAllNode(ptNode->m_wEpID);
		}
		else if( !m_pcUmsDiscuss->IsUIDiscussOn() )//讨论模式下 不不能改变发言人
		{
			//如果默认发言会场晚于主席上线，则取消默认发言会场，将其设置为主席
			SetCurSpeaker(m_cChair.GetSrc());
			//保存发言人格式，用于发言人掉线，取广播合成图像（按发言人格式取）
			m_tSpeakerMediaFmt.SetSpeakerSndVidFmt(ptNode->m_tVidSndFormat.m_tFormat);
			m_tSpeakerMediaFmt.SetSpeakerSndAudFmt(ptNode->m_tAudSndFormat.m_tFormat);

			TCallNode* ptSpeakNode = m_pcNodeMgr->GetCapsetNode(curSpeakerID());
			if (NULL != ptSpeakNode && ptSpeakNode->IsCallOn())
			{
				tInfo.m_tSpeak.SetAlias(ptSpeakNode->m_tConfName.m_abyAlias);
				tInfo.m_bSpeakOnline = TRUE;
				for (TCallNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
				{		
					if (ptItor->IsCallOn() && ptItor->IsUms())
					{				
						m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptItor->m_wEpID);
						UmsSendConfCtrl(tOutHandle, evtp_Conf_StatusInfo_Notify, &tInfo, sizeof(tInfo));
					}
				}
			}

			CNetPortMgr::CreateSpeakerToVirSpeaker(this);

			m_pcVmp->AdjustSpeakerVmp();
			m_pcBas->AdjustSpeakerBas();

			if (IsChairConf() || (!IsChairConf() && m_tSuperInfo.m_bSpeakOnline))
			{
				AdjustNewSpeakerToAllNode();
			}

			// 发言人改变了，需要通知
			NotifyApplySpeakerToUI();
		}
	}
	else
	{

        if ((ptFahterNode && ptSpeaker && ptSpeaker->IsChanOn()) || GetVmp()->IsBrdVmp() || GetAudMix()->IsAudMixMode())
		{
             AdjustNewSpeakerToAllNode(ptNode->m_wEpID);
			 
		}else 
		{
			MdlHint(Ums_Mdl_Call, ("OnChanConnect. Speark Not Online, ConfID:%d, wEpID:%d\n", GetInsID(), ptNode->m_wEpID));

		} 


	}

	NotifyConfInfoToCnsOnChanConnect(ptNode);

	UpdateNodeInfo(tp_OprType_Update, ptNode->m_wEpID);	
}

void CUmsConfInst::OnChanDisConnect(CTpMsg *const ptMsg)
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	u16 wEpID = tHandle.GetEpID();

	EmChannelHandle emChanHandle;
	u16 wChanID;
	CTpTypeAdpt::GetChannelIndex(u32(tHandle.handPaChan), emChanHandle, wChanID);

	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode)
	{
		UmsHangUp(tHandle);
		MdlError(Ums_Mdl_Call, ("OnChanDisConnect ep Index error. ConfID:%d, EpID:%d, chantype:%d, chanid:%d\n"
			, GetInsID(), wEpID, emChanHandle, wChanID));
		return;
	}	
		
	TChanPara* ptPara = NULL;
	if (em_video_send_handle == emChanHandle)
	{
		ptPara = m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_vid_enc, wChanID);
	}
	else if (em_video_recv_handle == emChanHandle)
	{
		ptPara = m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_vid_dec, wChanID);
	}
	else if (em_audio_send_handle == emChanHandle)
	{
		ptPara = m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_aud_enc, wChanID);
	}
	else if (em_audio_recv_handle == emChanHandle)
	{
		ptPara = m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_aud_dec, wChanID);
	}
	else if (em_audio_send_mix_handle == emChanHandle)
	{
		ptPara = m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_Mix_enc, wChanID);
	}
	else if (em_audio_recv_mix_handle == emChanHandle)
	{
		ptPara = m_pcNodeMgr->GetChanByIndex(wEpID, ums_CodecType_Mix_dec, wChanID);
	}

	if (NULL != ptPara)
	{
		MdlHint(Ums_Mdl_Call, ("OnChanDisConnect ConfID:%d, EpID:%d, chanType:%d, chanIndex:%d, chanstate:%d\n", GetInsID()
				, wEpID, emChanHandle, ptPara->m_tPAHandle, ptPara->m_emChanState));
	}

	u16 wIndex = 0;
	if (NULL != ptPara && EmChanSecMaking == ptPara->m_emChanState)
	{
		ptPara->SetOpen(FALSE);
	
		BOOL32 bAllOpen = TRUE;		
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
		{
			if (EmChanSecMaking == ptNode->m_tRmtChan.m_atVidEnc[wIndex].m_emChanState)
			{
				bAllOpen = FALSE;
				break;
			}
		}
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
		{
			if (EmChanSecMaking == ptNode->m_tRmtChan.m_atVidDec[wIndex].m_emChanState)
			{
				bAllOpen = FALSE;
				break;
			}
		}

		if (bAllOpen && !ptNode->IsChanOn())
		{
			ptNode->m_bAdjustChanOn = TRUE;
			AdjustNodeChanOn(ptNode);
		}
		return;
	}
	
	if (NULL != ptPara)
	{
		ptPara->SetOpen(FALSE);
		BOOL32 bAllFailed = TRUE;		
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
		{
			if (EmChanIdle != ptNode->m_tRmtChan.m_atVidEnc[wIndex].m_emChanState)
			{
				bAllFailed = FALSE;
				break;
			}
		}
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
		{
			if (EmChanIdle != ptNode->m_tRmtChan.m_atVidDec[wIndex].m_emChanState)
			{
				bAllFailed = FALSE;
				break;
			}
		}
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
		{
			if (EmChanIdle != ptNode->m_tRmtChan.m_atAudEnc[wIndex].m_emChanState)
			{
				bAllFailed = FALSE;
				break;
			}
		}
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
		{
			if (EmChanIdle != ptNode->m_tRmtChan.m_atAudDec[wIndex].m_emChanState)
			{
				bAllFailed = FALSE;
				break;
			}
		}

		if (bAllFailed)
		{
			UmsHangUp(tHandle);
			MdlError(Ums_Mdl_Call, ("OnChanDisConnect ep all chan fail. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
		}
	}

}	

void CUmsConfInst::OnOpenCascadeChairChan(CTpMsg *const ptMsg)
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TCascadeOpenChanCmd* ptCmd = (TCascadeOpenChanCmd*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	if (!Is_Caller_Node(tHandle.GetEpID()))
	{
		MdlError(Ums_Mdl_Call, ("OnOpenCascadeChairChan Error! ConfID:%d, From:%d\n", GetInsID(), tHandle.GetEpID()));
		return;
	}

	if (!m_pcCallMgr->AnswerCascadeChair(ptCmd))
	{
		UmsHangUp(tHandle);
		ObjError(("OnOpenCascadeChairChan ep Index error. ConfID:%d, EpID:%d\n", GetInsID(), tHandle.GetEpID()));
	}

	//主席通道打开成功 
	//则调整发言人看主席的适配通道并创建交换
	m_pcBas->AdjustChairBas();
	CNetPortMgr::CreateVirChairToBas(this);
}

void CUmsConfInst::OnOpenCascadeChairChanAck(CTpMsg *const ptMsg)
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TCascadeOpenChanAck* ptAck = (TCascadeOpenChanAck*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	TCapNode* ptRmt = m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
	if (NULL == ptRmt || !ptRmt->IsChanOn())
	{
		MdlError(Ums_Mdl_Call, ("OnOpenCascadeChairChanAck Error! ConfID:%d, From:%d\n", GetInsID(), tHandle.GetEpID()));
		return;
	}
	
	m_pcCallMgr->OnCascadeChairAck(ptRmt, ptAck);	
}

/*==============================================================================
函数名    :  HungUp
功能      :  挂断一个结点
算法实现  :  
参数说明  :	wEpID：结点ID
			bDelete：是否删除结点
			bToStack：是否需要向协议栈发送hungup
		
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-6-20               zhaixiaogang
==============================================================================*/
void CUmsConfInst::HungUp(u16 wEpID, BOOL32 bDelete, BOOL32 bToStack, EmCnsCallReason emRes)
{
	u16			wEpAllNum = 0;
	u16			awAllEpID[TP_CONF_MAX_CNSNUM] = {0};
	TCallNode* 	ptNodeTmp = NULL;

	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || ums_UmsConfNodeState_unused == ptNode->m_emCallState)
	{
		ObjError(("HungUp Invalid ep. ConfID:%d, EpID:%d\n", GetInsID(), wEpID));
		return;
	}

	wEpAllNum = m_pcNodeMgr->GetAllNodeByRoot(awAllEpID,TP_CONF_MAX_CNSNUM,ptNode);

	if (bToStack && (ums_UmsConfNodeState_calling == ptNode->m_emCallState || ptNode->IsCallOn()) )
	{
		TUmsHandle tHandle;
		m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
		if (ptNode->IsMtEp() && ptNode->IsCallOn())
		{		
			UmsSendConfCtrl(tHandle, evtp_Conf_CancelMultConf_Notify, NULL, 0);	
		}

		UmsHangUp(tHandle);
	}

	u16 wChnNum = (ptNode->m_wVidSndNum > ptNode->m_wVidRcvNum ? ptNode->m_wVidSndNum : ptNode->m_wVidRcvNum);
	if ( m_dwOnlineChanNum >= wChnNum)
	{
		m_dwOnlineChanNum -= wChnNum;
	}

	StopMediaTrans(ptNode, bDelete, emRes);
	
	//未正在退出会议且非Caller,  释放资源
	if ( !m_bIsQuiting && !Is_Caller_Node(ptNode->m_wEpID))
	{
		if (ptNode->m_wEpID != chairID() && IsChairConf() && ptNode->IsCallOn() )
		{//callcnnt上线 且 通道chanon 才认为上线

			TConfEpIDInfo tConfID;
			tConfID.m_wConfID = GetInsID();
			tConfID.m_wEpID = ptNode->m_wEpID;
			tConfID.m_tAlias = ptNode->m_tConfName;

			if (ptNode->IsUms())
			{
				NotifyConfCtrlMsgToCns(evtp_Conf_LeftConf_Notify, chairID(), &tConfID, sizeof(tConfID));
			}
			else
			{
				if (ptNode->IsChanOn())
				{
					NotifyConfCtrlMsgToCns(evtp_Conf_LeftConf_Notify, chairID(), &tConfID, sizeof(tConfID));
				}
			}
		}

		m_pcNodeMgr->ReleaseNodeRes(ptNode);
		ptNode->HungUp();		
	}

	u16 wIndex = 0;
	if (bDelete)
	{
		m_pcNodeMgr->DeleteNode(ptNode);

		for (wIndex = 0; wIndex < wEpAllNum; ++wIndex)
		{
			UpdateNodeInfo(tp_OprType_Del, awAllEpID[wIndex]);
		}

	}
	else
	{
		ptNode->m_emCallState = ums_UmsConfNodeState_stopcall;
		for (wIndex = 0; wIndex < wEpAllNum; ++wIndex)
		{
			UpdateNodeInfo(tp_OprType_Update, awAllEpID[wIndex]);
		}
	}

	MdlHint(Ums_Mdl_Call, ("HungUp. ConfID:%d, EpID:%d, IsChair:%d, OnlineChanNum:%d.\n"
		, GetInsID(), wEpID, IsChairConf(), m_dwOnlineChanNum));
}

void CUmsConfInst::HungUpFromLow(TCallNode* ptNode, EmCnsCallReason emRes)
{	
	MdlHint(Ums_Mdl_Call, ("HungUpFromLow. ConfID:%d, EpID:%d, SndNum:%d, ChanOn:%d, emReason:%d\n"
					, GetInsID(), ptNode->m_wEpID, ptNode->m_wVidSndNum, ptNode->IsChanOn(), emRes));
	
	StopMediaTrans(ptNode, FALSE, emRes);
	ptNode->HungUp();
	AjustSpeakerOnNodeDisConn(ptNode);
	
	TConfEpIDInfo tConfID;
	tConfID.m_wConfID = GetInsID();
	tConfID.m_wEpID = ptNode->m_wEpID;
	tConfID.m_tAlias = ptNode->m_tConfName;
	NotifyConfCtrlMsgToCns(evtp_Conf_LeftConf_Notify, chairID(), &tConfID, sizeof(tConfID));
}

void CUmsConfInst::HungUpMcuEpFromLow( TCallNode* ptNode, EmCnsCallReason emRes )
{
	MdlHint(Ums_Mdl_Call, ("HungUpMcuEpFromLow. ConfID:%d, EpID:%d, SndNum:%d, ChanOn:%d, emReason:%d\n"
		, GetInsID(), ptNode->m_wEpID, ptNode->m_wVidSndNum, ptNode->IsChanOn(), emRes));

	ptNode->HungUp();
	
	TConfEpIDInfo tConfID;
	tConfID.m_wConfID = GetInsID();
	tConfID.m_wEpID = ptNode->m_wEpID;
	tConfID.m_tAlias = ptNode->m_tConfName;
	NotifyConfCtrlMsgToCns(evtp_Conf_LeftConf_Notify, chairID(), &tConfID, sizeof(tConfID));
}

void CUmsConfInst::StopMediaTrans(TCallNode* ptNode, BOOL32 bDelete, EmCnsCallReason emRes)
{
	u16 wEpID = ptNode->m_wEpID;
	if (ptNode->IsCallOn() && ptNode->IsChanOn())
	{
		m_pcTvWallMgr->HungUpNode(this, ptNode, emRes);
		m_pcDual->HungUpNode(ptNode, bDelete);
		m_pcPollMgr->OnHungup(ptNode);
		m_pcUmsDiscuss->OnHungUpNode(ptNode, emRes);
		m_pcVmp->OnHungUp(ptNode, emRes);
		m_pcSelView->HungUpNode(ptNode);
		m_pcRollCallMgr->OnHungUpNode(ptNode, emRes);
		m_pcAudMix->OnHungUpNode(ptNode, emRes);

		TCapNode* ptFatherNode = m_pcNodeMgr->GetForeFatherNode(ptNode);
		if (ptFatherNode == ptNode)
		{
			CNetPortMgr::DestroyUmsToNode(this, ptFatherNode);
		}

		u16 awChildEpID[TP_CONF_MAX_CNSNUM];
		u16 wEpChildNum = m_pcNodeMgr->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, ptNode);
		for (u16 wI = 0; wI < wEpChildNum; ++wI)
		{
			TCallNode* pTempNode = m_pcNodeMgr->GetNode(awChildEpID[wI]);
			if (NULL == pTempNode)
			{
				continue;
			}

			m_pcDual->HungUpNode(pTempNode, TRUE);
			m_pcPollMgr->OnHungup(pTempNode);
			m_pcSelView->HungUpNode(pTempNode);
			m_pcTvWallMgr->HungUpNode(this, pTempNode, emRes);
			pTempNode->HungUp();
		}
	}
}

void CUmsConfInst::OnIframeBySrcNty(CTpMsg *const ptMsg)
{
	TCheckIFrameBase tBase;
	TIFrameBySrc tBySrc;
	tBySrc.Clear();
	TP_SAFE_CAST(tBase, ptMsg->GetBody());
	TP_SAFE_CAST(tBySrc, ptMsg->GetBody() + sizeof(tBase));

	if (inst_idle == CurState())
	{
		MdlError(Ums_Mdl_Call, ("OnIframeBySrcNty inst idle. ConfID:%d, Port:%d\n", GetInsID(), tBase.m_wPort));
		return;
	}

	MdlError(Ums_Mdl_Call, ("OnIframeBySrcNty ConfID:%d, Port:%d\n", GetInsID(), tBase.m_wPort));
	if (TP_IFrameCheck_Speaker == tBase.m_emType)
	{
		u16 wIEpID = tBySrc.m_wNewSpeakerID;
		if (wIEpID != curSpeakerID())
		{
			MdlError(Ums_Mdl_Call, ("OnIframeBySrcNty epid failed! wConfID:%d, m_wCurSpeaker:%d, IEp:%d\n", GetInsID(), curSpeakerID(), wIEpID));
			return;
		}
		
		u16 wChanIndex = tBySrc.m_wChanIndex;
		if (wChanIndex >= TP_MAX_STREAMNUM)
		{
			MdlError(Ums_Mdl_Call, ("OnIframeBySrcNty chan failed! wConfID:%d, m_wCurSpeaker:%d, IEp:%d, chan:%d\n", GetInsID(), curSpeakerID(), wIEpID, wChanIndex));
			return;
		}
		
		if (!m_abOnIFrameCheck[wChanIndex])
		{
			MdlError(Ums_Mdl_Call, ("OnIframeBySrcNty chan status failed! wConfID:%d, m_wCurSpeaker:%d, IEp:%d, chan:%d\n", GetInsID(), curSpeakerID(), wIEpID, wChanIndex));
			return;
		}
		
		m_abOnIFrameCheck[wChanIndex] = FALSE;
		CNetPortMgr::CreateSpeakerToVirSpeaker(this);
		
		MdlHint(Ums_Mdl_Call, ("OnIframeBySrcNty wConfID:%d, m_wCurSpeaker:%d, IEp:%d, chan:%d\n", GetInsID(), curSpeakerID(), wIEpID, wChanIndex));
		
		CNetPortMgr::DestroySpeakerToVirSpeakerForIframeCheck(this, wChanIndex);
		
		BOOL32 bChanged = TRUE;
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (m_abOnIFrameCheck[wIndex])
			{
				bChanged = FALSE;
			}
		}
		
		if (bChanged)
		{
			MdlHint(Ums_Mdl_Call, ("OnIframeBySrcNty changespeaker final! wConfID:%d, m_wOldSpeaker:%d, m_wCurSpeaker:%d\n", GetInsID(), oldSpeakerID(), curSpeakerID()));
			
			m_pcCallMgr->FlowControl(oldSpeakerID(), FLOW_CTROL_ALL_ENC, 0);	
			
			SetOldSpeaker(NULL);
		}
	}
	else if (TP_IFrameCheck_SingleSpeaker == tBase.m_emType)
	{
		u16 wIEpID = tBySrc.m_wNewSpeakerID;
		if (wIEpID != curSpeakerID())
		{
			MdlError(Ums_Mdl_Call, ("[OnIframeBySrcNty]single epid failed! wConfID:%d, m_wCurSpeaker:%d, Ep:%d\n", GetInsID(), curSpeakerID(), wIEpID));
			return;
		}
		
		if (!m_bOnSingleIframeCheck)
		{
			MdlError(Ums_Mdl_Call, ("[OnIframeBySrcNty]sigle chan status failed! wConfID:%d, m_wCurSpeaker:%d, Ep:%d\n", GetInsID(), curSpeakerID(), wIEpID));
			return;
		}
		
		m_bOnSingleIframeCheck = FALSE;
		CNetPortMgr::CreateSpeakerToVirSpeaker(this);
		
		MdlHint(Ums_Mdl_Call, ("[OnIframeBySrcNty]single wConfID:%d, m_wCurSpeaker:%d, IEp:%d\n", GetInsID(), curSpeakerID(), wIEpID));
		
		CNetPortMgr::DestroySpeakerToSingleVirSpeakerForIframeCheck(this);
	}
}

//ptCapSet默认为FALSE, 为TURE时表示上级过来调整。
void CUmsConfInst::ChangeSpeaker(u16 wNewSpeaker, const TSpeakerCapTr* ptCapSet)
{
	if (m_bIsQuiting)
	{
		ObjHint(("ChangeSpeaker Failed. The Conf is quiting! ConfID:%d\n", GetInsID()));
		return;
	}

	TCallNode* ptNewSpeaker = m_pcNodeMgr->GetNode(wNewSpeaker);
	TCallNode* ptOldSpeaker = m_pcNodeMgr->GetNode(curSpeakerID());
	if (NULL == ptNewSpeaker)
	{
		ObjError(("ChangeSpeaker Failed. ConfID:%d, wNewSpeaker:%d\n", GetInsID(), wNewSpeaker));
		return;
	}

	if (!ptNewSpeaker->IsChanOn())
	{
		ObjHint(("ChangeSpeaker new Ep is chan off. ConfID:%d, wNewSpeaker:%d\n", GetInsID(), wNewSpeaker));
		return;
	}
	
	u16 wOldSpeakerIndex = TP_INVALID_INDEX;
	if ( ptOldSpeaker != NULL )
	{
		if ( ptOldSpeaker->IsChanOn() )
		{
			wOldSpeakerIndex = ptOldSpeaker->GetSpeaker();
		}
	}

	ObjHint(("ChangeSpeaker. ConfID:%d, OldSpeaker:%d, OldSpeakerIndx:%d, wNewSpeaker:%d, NewSpeakerIndx:%d, dualstart:%d\n", 
		GetInsID(), curSpeakerID(), wOldSpeakerIndex, wNewSpeaker, ptNewSpeaker->m_wSpearkIndex, m_pcDual->IsStart()));

	//更新发言人信息
	if (NULL != ptCapSet)
	{
		MdlHint(Ums_Mdl_Call, ("ChangeSpeaker adjust chair capset wConfID:%d, SpeakerIndx:%d\n", GetInsID(), ptCapSet->m_wSpeakerIndex));
		m_tSuperInfo.m_tSpeak.SetAlias(ptCapSet->m_tEpAlias.m_abyAlias);
		
		if (Is_Caller_Node(wNewSpeaker))
		{
			ptNewSpeaker->SetVidSndNum(ptCapSet->m_wVidSnd);
			ptNewSpeaker->SetAudSndNum(ptCapSet->m_wAudSnd);

			ptNewSpeaker->m_wSpearkIndex = ptCapSet->m_wSpeakerIndex;
		}
	}	
	else
	{
		m_tSuperInfo.m_tSpeak.SetAlias(ptNewSpeaker->m_tConfName.m_abyAlias);
	}

    // 新老发言人关键帧检测
	if (!m_pcUmsDiscuss->IsDiscussModle())
	{
		SetSpeakerCheckFrame(ptNewSpeaker, ptOldSpeaker);
	}

	SetOldSpeaker(m_cSpeaker.GetCur());
	SetCurSpeaker(ptNewSpeaker);

    m_tSpeakerMediaFmt.SetSpeakerSndVidFmt(ptNewSpeaker->m_tVidSndFormat.m_tFormat);
	m_tSpeakerMediaFmt.SetSpeakerSndAudFmt(ptNewSpeaker->m_tAudSndFormat.m_tFormat);

	m_pcCallMgr->FlowControl(curSpeakerID(), FLOW_CTROL_ALL_ENC, ptNewSpeaker->m_tVidSndFormat.m_tFormat.m_wBitrate);


    u16 wChairId = chairID();
	if (GetRollCallMgr()->IsRollCallModle())
	{
        wChairId = GetRollCallMgr()->GetRollCallerEpId();
		//为了更新 chair or speaker in vmp
		if (IsChairConf())
		{
			GetVmp()->GetVmpEp();
		}
	}

	//
	TCapNode* ptNewSpeakerFather = GetNodeMgr()->GetForeFatherNode(ptNewSpeaker);
	if (IsChairConf() 
		&& !GetUmsDiscuss()->IsDiscussModle()
		&& NULL != ptNewSpeakerFather 
		&& ptNewSpeakerFather->m_wEpID != wChairId)
	{// 主席不是新发言人，先刷一次到新发言人的交换，避免新发言人一直从虚拟发言人收码流，会出现闪本地
		AdjustNewSpeakerToAllNode(ptNewSpeakerFather->m_wEpID);
	}

	CNetPortMgr::CreateSpeakerToVirSpeaker(this);

	m_pcDual->ChangeSpeakerForVRS();
	m_pcVmp->AdjustSpeakerVmp();
	m_pcBas->AdjustSpeakerBas();
	m_pcTvWallMgr->ChangeSpeaker(this);
	m_pcAudMix->ChangeSpeaker(ptNewSpeaker);
	


	if (GetRollCallMgr()->IsRollCallModle())
	{   //点名模式，点名人与被点名人不同。

        m_pcBas->AdjustChairBas();

	} 
	else 
	{
		if (curSpeakerID() != chairID())
		{
			m_pcBas->AdjustChairBas();
			m_pcCallMgr->FlowControl(chairID(), FLOW_CTROL_ALL_ENC, m_tConfBaseInfo.m_wConfBitRate);
			
			TCapNode* ptChair = m_pcNodeMgr->GetForeFatherNode(chairID());
			if ( NULL != ptChair )
			{
				ptChair->m_tRmtChan.ResetFastStatis();
			}
			AskKeyByEpID(chairID(), EmAskKeyChair);
		}
	}

	return ;
}


void CUmsConfInst::AjustSpeakerOnNodeDisConn(TCallNode* ptNode)
{
	if ( !IsChairConf() )
	{
		MdlHint(Ums_Mdl_Call, ("AjustSpeakerOnNodeDisConn not ChairConf. ConfID:%d, Node:%d\n", GetInsID(), ptNode->m_wEpID));
		return ;
	}

	TCapNode* ptSpeakerFather = m_pcNodeMgr->GetForeFatherNode(curSpeakerID());
	if ( NULL == ptSpeakerFather )
	{
		MdlHint(Ums_Mdl_Call, ("AjustSpeakerOnNodeDisConn ptSpeakerFather is NULL. ConfID:%d, Node:%d\n", GetInsID(), ptNode->m_wEpID));
		return ;
	}

	if (curSpeakerID() == ptNode->m_wEpID || ptSpeakerFather->m_wEpID == ptNode->m_wEpID)
	{
		TCallNode*	ptSpeaker = NULL;		
		do 
		{
			if (m_pcUmsDiscuss->IsDiscussModle())
			{// 讨论模式下，发言会场掉线，切发言会场在讨论中处理
				return;
			}

			if (m_pcRollCallMgr->IsUIRollCallOn() || m_pcRollCallMgr->IsRollCallModle())
			{   //点名模式下，被点名人掉线，看最后一帧, 点名开启后（UI）就不应切换发言人了， 下级没有设置IsUIRollCallOn
                //删掉被点名人（即curSpeakerID()）到虚拟发言人的交换， 被点名人掉线后其端口会被复用，如果不释放被点名人到
				//虚拟发言人的交换，则导致本点名会场看到其他复用的会场的图像
				CNetPortMgr::CreateSpeakerToVirSpeaker(this); 
				return;
			}

			if( ptSpeaker == NULL )
			{
				if (curSpeakerID() != chairID())
				{
					ptSpeaker = GetNode(chairID());
				}
				else
				{//主席兼发言人掉线，不处理
					break;
				}
			}

			ChangeSpeaker(ptSpeaker->m_wEpID, NULL);
			AdjustNewSpeakerToAllNode();
			NotifyApplySpeakerToUI();
			
			return ;

		} while (0);
		
		//最终没有找到合适发言人，说明发言人不在线，直接拆掉所有交换
		CNetPortMgr::CreateSpeakerToVirSpeaker(this);
	}

	if (ptNode->m_wEpID == chairID() && curSpeakerID() != ptNode->m_wEpID)
	{// 主席（非发言会场）掉线，刷新到发言人的交换
		if (!m_pcUmsDiscuss->IsDiscussModle())
		{
			m_pcNodeFsm->UpdateMediaTrans(ptSpeakerFather);
		}
	}
	return;
}

//上级UMS呼入时，拆除下级UMS的相关会议内容
void CUmsConfInst::DestroyMediaOnCallerOnline()
{
	MdlHint(Ums_Mdl_Call, ("DestroyMediaOnCallerOnline. ConfID:%d\n", GetInsID()));
	TCallNode* ptSpeakerNode = m_pcNodeMgr->GetNode(curSpeakerID());
	TCallNode* ptChairNode = m_pcNodeMgr->GetNode(chairID());

	if (m_pcDual->IsStart())
	{
		m_pcDual->StopDual();
	}

	m_pcVmp->OnStopConf();
	m_pcUmsDiscuss->ReleaseDiscuss();
	m_pcAudMix->OnStopConf();

	return;
}

u16	CUmsConfInst::curSpeakerID()const
{	
	const CNodeBase* pcBase = m_cSpeaker.GetCur();
	if (NULL == pcBase || em_Node_Ep != pcBase->GetType())
	{
		return TP_INVALID_INDEX;
	}
	return ((TCallNode*)pcBase)->m_wEpID;
}
u16	CUmsConfInst::oldSpeakerID()const			
{ 
	const CNodeBase* pcBase = m_cSpeaker.GetOld();
	if (NULL == pcBase || em_Node_Ep != pcBase->GetType() )
	{
		return TP_INVALID_INDEX;
	}
	return ((TCallNode*)pcBase)->m_wEpID;
}

u16	CUmsConfInst::chairID()const				
{ 
	const CNodeBase* pcBase = m_cChair.GetSrc();
	if (NULL == pcBase || em_Node_Ep != pcBase->GetType() )
	{
		return TP_INVALID_INDEX;
	}
	return ((TCallNode*)pcBase)->m_wEpID;
}

void CUmsConfInst::SetCurSpeaker(CNodeBase* ptNode)	
{  
	m_cSpeaker.SetCur(ptNode);
}	
void CUmsConfInst::SetOldSpeaker(CNodeBase* ptNode)	
{  
	m_cSpeaker.SetOld(ptNode);
}	
void CUmsConfInst::SetChairID(CNodeBase* ptNode)
{ 
	m_cChair.SetSrc(ptNode);
}

BOOL32 CUmsConfInst::GetChairSndCap(u16 wSpeaker, TSpeakerCapTr& tCapSet)
{//对于CNS来说，wSpeaker没有意义，对于UMS来说，wSpeaker表示下级ID
	if (IsChairConf())
	{
		TCallNode* ptNode = m_pcNodeMgr->GetNode(chairID());
		if (NULL == ptNode )
		{
			MdlHint(Ums_Mdl_Call, ("GetChairSndCap. chair is null, ConfID:%d, chair:%d\n", GetInsID(), chairID()));
			return FALSE;
		}
		
		tCapSet.m_wSpeakerID = wSpeaker;
		tCapSet.m_wVidSnd = ptNode->m_wVidSndNum;
		tCapSet.m_wAudSnd = ptNode->m_wAudSndNum;
		tCapSet.m_tEpAlias = ptNode->m_tConfName;
		tCapSet.m_wSpeakerIndex = ptNode->GetSpeaker();
	}
	else
	{
		TCapNode* ptNode = m_pcNodeMgr->GetCaller();

		tCapSet.m_wSpeakerID = wSpeaker;
		tCapSet.m_wVidSnd = m_tSuperInfo.m_wChairVidSndCap;
		tCapSet.m_wAudSnd = m_tSuperInfo.m_wChairAudSndCap;
		tCapSet.m_tEpAlias.SetAlias(m_tSuperInfo.m_tChair.m_abyAlias);
		tCapSet.m_wSpeakerIndex = ptNode->GetSpeaker();
	}
	return TRUE;
}

BOOL32 CUmsConfInst::GetSpeakSndCap(u16 wSpeaker, TSpeakerCapTr& tCapSet)
{
	if (IsChairConf())
	{
		TCallNode* ptNode = m_pcNodeMgr->GetNode(wSpeaker);
		if (NULL == ptNode )
		{
			MdlHint(Ums_Mdl_Call, ("GetChairSndCap. speaker is null, ConfID:%d, wSpeaker:%d\n", GetInsID(), wSpeaker));
			return FALSE;
		}
		
		tCapSet.m_wSpeakerID = ptNode->m_wLowChildEpID;
		tCapSet.m_wVidSnd = ptNode->m_wVidSndNum;
		tCapSet.m_wAudSnd = ptNode->m_wAudSndNum;
		tCapSet.m_tEpAlias = ptNode->m_tConfName;
		tCapSet.m_wSpeakerIndex = ptNode->GetSpeaker();
	}
	else
	{
		TCallNode* ptNode = m_pcNodeMgr->GetNode(wSpeaker);
		if (NULL != ptNode && !Is_Caller_Node(ptNode->m_wEpID))
		{
			tCapSet.m_wSpeakerID = ptNode->m_wLowChildEpID;
			tCapSet.m_wVidSnd = ptNode->m_wVidSndNum;
			tCapSet.m_wAudSnd = ptNode->m_wAudSndNum;
			tCapSet.m_tEpAlias = ptNode->m_tConfName;
			tCapSet.m_wSpeakerIndex = ptNode->GetSpeaker();
		}
		else
		{
			TCapNode* ptNode = m_pcNodeMgr->GetCaller();
			tCapSet.m_wSpeakerID = ptNode->m_wLowChildEpID;
			tCapSet.m_wVidSnd = ptNode->m_wVidSndNum;
			tCapSet.m_wAudSnd = ptNode->m_wAudSndNum;
			tCapSet.m_tEpAlias.SetAlias(m_tSuperInfo.m_tSpeak.m_abyAlias);
			tCapSet.m_wSpeakerIndex = ptNode->GetSpeaker();
		}
	}
	return TRUE;
}

void CUmsConfInst::OnConfYouAreSeeing(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TSpeakerCapTr& tCapSet = *(TSpeakerCapTr*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	if (IsChairConf())
	{
		return;
	}
	if (!tCapSet.m_bIsSpeaker)
	{
		tCapSet.m_wSpeakerID = CALLER_EP_INDEX;
	}
	
	MdlHint(Ums_Mdl_Call, ("OnConfYouAreSeeing. pre(%d) cur(%d), IsSpeaker:%d, SpeakerIndx:%d!\n"
		, curSpeakerID(), tCapSet.m_wSpeakerID, tCapSet.m_bIsSpeaker, tCapSet.m_wSpeakerIndex));

	if (curSpeakerID() == tCapSet.m_wSpeakerID && Is_Caller_Node(curSpeakerID()))
	{
		MdlHint(Ums_Mdl_Call, ("OnConfYouAreSeeing ChangeSpeaker adjust chair capset wConfID:%d\n", GetInsID()));

		TCallNode* ptCaller = m_pcNodeMgr->GetCaller();
		m_tSuperInfo.m_tSpeak.SetAlias(tCapSet.m_tEpAlias.m_abyAlias);
		ptCaller->SetVidSndNum(tCapSet.m_wVidSnd);
		ptCaller->SetAudSndNum(tCapSet.m_wAudSnd);
		ptCaller->m_wSpearkIndex = tCapSet.m_wSpeakerIndex;

		//在切换发言人时， 要先调整一下发言人到虚拟发言人的码流
		//因为m_tSingleVidDec的码流来源随着发言坐席变更
		CNetPortMgr::CreateSpeakerToVirSpeaker(this);

		m_pcVmp->AdjustSpeakerVmp();
	
		for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
		{
			if(!ptNode->m_bUsed || !ptNode->IsChanOn())
			{
				continue;
			}			
			//下级所有会场清空
			ptNode->m_tRmtChan.ResetFastStatis();

			m_pcNodeFsm->ChangeSpeaker(ptNode);
		}


		if (GetRollCallMgr()->IsRollCallModle() 
            && !IsChairConf()
            && VALID_ALL_EPID(GetRollCallMgr()->GetRollCallerEpId())
            && !VALID_ALL_EPID(GetRollCallMgr()->GetCallTargetEpId()))
		{
			TCapNode* pUms = m_pcNodeMgr->GetCaller();
			if (pUms->m_bUsed && pUms->IsChanOn())
			{  // 主席（点名人）在下级， 发言人（被点名人）在上级，向上打主席的码流
				m_pcNodeFsm->ChangeSpeaker(pUms);	
				pUms->m_tRmtChan.ResetFastStatis();
			}
		}

	}
	else
	{
		ChangeSpeaker(tCapSet.m_wSpeakerID, &tCapSet);
		AdjustNewSpeakerToAllNode();
	}	
	
	NotifyApplySpeakerToUI();
}

//从协议栈过来的通道关键帧请求，根据通道句柄查询
void CUmsConfInst::OnConfAskKeyFrame(CTpMsg *const ptMsg)
{
#define GetDstIndexBySrcIndex(SrcNode, DstNode, Index) SrcNode->m_wVidRcvNum > 1 ? Index : (DstNode)->GetSpeaker()

	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TCapNode* ptSrcNode = m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
	if (NULL == ptSrcNode || !ptSrcNode->IsCallOn())
	{
		tpLowDtl(Ums_Mdl_Call, "OnConfAskKeyFrame ConfID:%d, SrcEpID:%d\n", GetInsID(), tHandle.GetEpID());
		return;
	}

	BOOL32 bAskDual = TRUE;
	TVidChanPara* ptSrcChan = m_pcNodeMgr->GetChanByHandle(tHandle.GetEpID(), ums_CodecType_vid_dec_dual, tHandle.handPaChan);
	if (NULL == ptSrcChan)
	{
		ptSrcChan = m_pcNodeMgr->GetChanByHandle(tHandle.GetEpID(), ums_CodecType_vid_dec, tHandle.handPaChan);
		if (NULL == ptSrcChan)
		{
			tpLowDtl(Ums_Mdl_Call, "OnConfAskKeyFrame ConfID:%d, SrcEpID:%d, SrcChanID:%d\n", GetInsID(), tHandle.GetEpID(), tHandle.handPaChan);
			return;
		}

		bAskDual = FALSE;
	}

	if (!IsValidKeyFrameReq(ptSrcChan->m_tKeyFrameStatis))
	{
		tpLowDtl(Ums_Mdl_Call, "OnConfAskKeyFrame Src req frequent! ConfID:%d, SrcEp:%d, SrcChanIndex:%d\n"
			, GetInsID(), tHandle.GetEpID(), ptSrcChan->m_wIndex);
		return;
	}
	ptSrcChan->m_tKeyFrameStatis.Add();

	//双流
	if ( bAskDual )
	{
		m_pcDual->AskFrameForSeeDual(ptSrcNode->m_tDualVidRcvFormat.m_tFormat, FALSE);
		return ;
	}

	//关键帧 全部走目标策略模块
	m_pcNodeFsm->AskKeyFrame(ptSrcNode, ptSrcChan->m_wIndex);

	return ;
}

//根据屏号向目的通道请求关键帧
void CUmsConfInst::AskKeyByScreen(u16 wEpID, u16 wScreenIndex, EmAskKeyType emType, u32 dwRervse1 , u32 dwRervse2 , BOOL32 bReqBySys )
{
	TCallNode* ptDstNode = m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptForeNode = m_pcNodeMgr->GetForeFatherNode(ptDstNode);
	if (NULL == ptDstNode || NULL == ptForeNode || !ptDstNode->IsChanOn())
	{
		tpLowDtl(Ums_Mdl_Call, "AskKeyByScreen Failed! ConfID:%d, DstID:%d\n", GetInsID(), wEpID);
		return;
	}

	TUmsHandle tOutHandle;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptForeNode->m_wEpID);
		
	tpLowDtl(Ums_Mdl_Call, "AskKeyByScreen! ConfID:%d, DstID:%d, wScreenIndex:%d\n", GetInsID(), wEpID, wScreenIndex);
	if (ptDstNode == ptForeNode && wEpID != CALLER_EP_INDEX )
	{
		TVidChanPara* ptDstChan = m_pcNodeMgr->GetVidChanByIndex(ptForeNode->m_wEpID, ums_CodecType_vid_enc, wScreenIndex);
		
		if (NULL != ptDstChan)
		{
			if (!bReqBySys && !IsValidKeyFrameReq(ptDstChan->m_tKeyFrameStatis))
			{
				tpLowDtl(Ums_Mdl_Call, "AskKeyByScreen dst req frequent! ConfID:%d, DstEpID:%d, DstChanID:%d\n"
					, GetInsID(), ptDstNode->m_wEpID, ptDstChan->m_tPAHandle);
				return;
			}
			
			if (!bReqBySys)
			{
				ptDstChan->m_tKeyFrameStatis.Add();
			}
			
			tOutHandle.handPaChan = ptDstChan->m_tPAHandle;
			UmsSendChanCtrl(tOutHandle, evtp_Conf_AskKeyFrame, NULL, 0);
		}
	}
	else
	{
		TAskKeyByScreenTr tAskKey;
		tAskKey.m_wEpID = ptDstNode->m_wLowChildEpID;
		tAskKey.m_wScreenIndex = wScreenIndex;
		tAskKey.m_bReqBySys = bReqBySys;
		tAskKey.m_dwAskType = emType;
		tAskKey.m_dwRervse1 = dwRervse1;
		tAskKey.m_dwRervse2 = dwRervse2;
		UmsSendConfCtrl(tOutHandle, evtp_Conf_AskKeyByScreen, &tAskKey, sizeof(tAskKey));
	}
}

//向wEpID会场的所有通道请求关键帧
void CUmsConfInst::AskKeyByEpID(u16 wEpID, EmAskKeyType emType, u32 dwRervse1, u32 dwRervse2, BOOL32 bReqBySys)
{
	TCallNode* ptDstNode = m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptForeNode = m_pcNodeMgr->GetForeFatherNode(ptDstNode);
	if (NULL == ptDstNode || NULL == ptForeNode || !ptDstNode->IsChanOn())
	{
		tpLowDtl(Ums_Mdl_Call, "AskKeyByEpID Failed! ConfID:%d, DstID:%d\n", GetInsID(), wEpID);
		return;
	}
	
	TUmsHandle tOutHandle;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptForeNode->m_wEpID);
	
	tpLowDtl(Ums_Mdl_Call, "AskKeyByEpID! ConfID:%d, DstID:%d\n", GetInsID(), wEpID);

	s32 symbolflag = 1; 
	u16 wCurIndex = 0;
	u16 wMidIndex = MIDSCREENINDEX;

	if (ptDstNode == ptForeNode && wEpID != CALLER_EP_INDEX )
	{
		for (u16 wIndex = 1; wIndex <= ptDstNode->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = wMidIndex + wIndex / 2 * symbolflag;
			TVidChanPara* ptDstChan = m_pcNodeMgr->GetVidChanByIndex(ptForeNode->m_wEpID, ums_CodecType_vid_enc, wCurIndex);
			if (NULL != ptDstChan)
			{
				if (!bReqBySys && !IsValidKeyFrameReq(ptDstChan->m_tKeyFrameStatis))
				{
					tpLowDtl(Ums_Mdl_Call, "AskKeyByEpID dst req frequent! ConfID:%d, DstEpID:%d, DstChanID:%d\n"
						, GetInsID(), ptDstNode->m_wEpID, ptDstChan->m_tPAHandle);
					continue ;
				}
				if (!bReqBySys)
				{
					ptDstChan->m_tKeyFrameStatis.Add();
				}
				tOutHandle.handPaChan = ptDstChan->m_tPAHandle;
				UmsSendChanCtrl(tOutHandle, evtp_Conf_AskKeyFrame, NULL, 0);
			}
		}
	}
	else
	{
		TAskKeyByScreenTr tAskKey;
		tAskKey.m_wEpID = ptDstNode->m_wLowChildEpID;
		tAskKey.m_bReqBySys = bReqBySys;
		tAskKey.m_dwAskType = emType;
		tAskKey.m_dwRervse1 = dwRervse1;
		tAskKey.m_dwRervse2 = dwRervse2;
		for (u16 wIndex = 1; wIndex <= ptDstNode->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = wMidIndex + wIndex / 2 * symbolflag;
			tAskKey.m_wScreenIndex = wCurIndex;
			UmsSendConfCtrl(tOutHandle, evtp_Conf_AskKeyByScreen, &tAskKey, sizeof(tAskKey));
		}
	}
}

void CUmsConfInst::OnAdjustCnsSpeakerIndx( CTpMsg *const ptMsg )
{
	TUmsHandle tInHandle;
	TP_SAFE_CAST(tInHandle, ptMsg->GetBody());
	TCnsSpeakerAdjust* ptAdjust = (TCnsSpeakerAdjust*)(ptMsg->GetBody() + sizeof(TUmsHandle));
	
	MdlHint(Ums_Mdl_Call, ("OnAdjustCnsSpeakerIndx. ConfID:%d, wEpID:%d, wIndex:%d\n", GetInsID(), ptAdjust->m_wEpID, ptAdjust->m_wSpeakerIndex));

	TCallNode* ptNode = m_pcNodeMgr->GetNode(ptAdjust->m_wEpID);
	TCapNode* ptCapNode = m_pcNodeMgr->GetForeFatherNode(ptNode);
	if ( NULL == ptNode || NULL == ptCapNode )
	{
		MdlError(Ums_Mdl_Call, ("OnAdjustCnsSpeakerIndx ptNode is NULL. ConfID:%d, wEpID:%d, wIndex:%d\n", GetInsID(), ptAdjust->m_wEpID, ptAdjust->m_wSpeakerIndex));
		return ;
	}

	//更新发言人坐席索引
	ptNode->m_wSpearkIndex = ptAdjust->m_wSpeakerIndex;

	TCnsSpeakerAdjust tAdjust;
	if ( ptNode != ptCapNode )
	{
		tAdjust.m_wEpID = ptNode->m_wLowChildEpID;
	}
	else
	{
		tAdjust.m_wEpID = ptNode->m_wEpID;
	}
	tAdjust.m_wSpeakerIndex = ptAdjust->m_wSpeakerIndex;

	TUmsHandle tOutHandle;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptCapNode->m_wEpID);
	UmsSendConfCtrl(tOutHandle, evtp_UmsCnsSpeakerIndxAdjust_Notify, &tAdjust, sizeof(tAdjust));
		
	return ;
}

//CNS通知会场发言坐席改变
void CUmsConfInst::OnAdjustInnerSpeakFromCns(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	u8 bChanId = 0;
	TP_SAFE_CAST(bChanId, ptMsg->GetBody()+sizeof(TUmsHandle));

	TCallNode* ptNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (NULL == ptNode || !ptNode->IsCns() || !ptNode->IsChanOn())
	{
		ObjError(("OnAdjustInnerSpeakFromCns Failed! ConfID:%d, EpID:%d\n", GetInsID(), tHandle.GetEpID()));
		return;
	}
	
	ObjHint(("OnAdjustInnerSpeakFromCns! ConfID:%d, EpID:%d, oldchan:%d, newchan:%d\n"
		, GetInsID(), tHandle.GetEpID(), ptNode->m_wSpearkIndex, bChanId));

	if (bChanId >= TP_MAX_STREAMNUM)
	{
		return;
	}

	if (ptNode->m_wSpearkIndex == bChanId)
	{
		return;
	}
	
	if (ptNode->m_wEpID == chairID())
	{
		m_tSuperChairCap.m_wSpeakerIndex = bChanId;
		NotifyChairCapToLowUms();
	}

	if (ptNode->m_wEpID == curSpeakerID())
	{
		AdjustCnsInnerSpeak( FALSE, bChanId);
	}
	else if (ptNode->m_wEpID == chairID())
	{
		if (!IsChairConf())
		{
			ObjError(("OnAdjustInnerSpeakFromCns chair faild! ConfID:%d, chair:%d\n", GetInsID(), chairID()));
			return;
		}
		ptNode->m_wSpearkIndex = bChanId;
		TCapNode* ptSpeaker = GetNodeMgr()->GetCapsetNode(curSpeakerID());
		if( NULL != ptSpeaker )
		{
			GetNodeFsm()->UpdateMediaTrans(ptSpeaker);
		}
	}

	if (GetRollCallMgr()->IsRollCallModle() && ptNode->m_wEpID == GetRollCallMgr()->GetRollCallerEpId())
	{  
		TCapNode* ptSpeaker = GetNodeMgr()->GetCapsetNode(curSpeakerID());
		if( NULL != ptSpeaker )
		{   //点名者，发言人在同一UMS下
            ptNode->m_wSpearkIndex = bChanId;
			GetNodeFsm()->UpdateMediaTrans(ptSpeaker);
		}

		if (IsChairConf())
		{
			m_pcRollCallMgr->AdjustInnerSpeaker(ptNode);
		}
	}

	
	ptNode->m_wSpearkIndex = (u16)bChanId;

	m_pcPollMgr->AdjustCnsSpeaker(ptNode);
	m_pcGetVidEx->UpdateSpeakerIndex(this, ptNode->m_wEpID, ptNode->m_wSpearkIndex);
	m_pcSelView->AdjustCnsSpeaker(ptNode);
	m_pcVmp->AdjustCnsSpeaker(ptNode);

	if (!IsChairConf())
	{
		if ( ptNode->IsInMix() )
		{//在讨论内，坐席变化后，需要创建到上级的交换
			m_pcNodeFsm->UpdateMediaTrans((TCapNode*)ptNode);
		}

		TCnsSpeakerAdjust tAdjustInfo;
		tAdjustInfo.m_wSpeakerIndex = ptNode->m_wSpearkIndex;
		tAdjustInfo.m_tKey.m_wEpID = ptNode->m_wEpID;

		TUmsHandle tOutHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_CnsSpeakerCascad_Notify, &tAdjustInfo, sizeof(tAdjustInfo));
	}
	else
	{
		AskKeyByScreen(ptNode->m_wEpID, ptNode->m_wSpearkIndex, EmAskKeySpeaker);

		if (m_pcUmsDiscuss->IsDiscussModle())
		{
			if (ptNode->IsInMix())
			{// 在讨论中
				m_pcUmsDiscuss->OnAdjustInnerSpeaker(ptNode);
			}
		}

	}
}

//UMS级联通知会场发言人改变
void CUmsConfInst::OnConfCnsSpeakerCascadNotify(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TCnsSpeakerAdjust* ptAdjust = (TCnsSpeakerAdjust*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	TCallNode* ptNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (NULL == ptNode || !ptNode->IsUms() || !ptNode->IsChanOn())
	{
		ObjError(("OnConfCnsSpeakerCascadNotify Failed! ConfID:%d, EpID:%d\n", GetInsID(), tHandle.GetEpID()));
		return;
	}

	TChanPara* ptChan = m_pcNodeMgr->GetChanByIndex(ptNode->m_wEpID, ums_CodecType_vid_enc, ptAdjust->m_wSpeakerIndex);
	if (NULL == ptChan)
	{
		ObjError(("OnConfCnsSpeakerCascadNotify UnFind Chan! ConfID:%d, EpID:%d, Chan:%d\n", GetInsID(), tHandle.GetEpID(), ptAdjust->m_wSpeakerIndex));
		return;
	}

	TCallNode* ptCaller = m_pcNodeMgr->GetCaller();
	if (ptCaller->m_wEpID == ptNode->m_wEpID)
	{//从上级过来的调整

		MdlHint(Ums_Mdl_Stack, ("OnConfCnsSpeakerCascadNotify DownLevel ConfID:%d, Chair:%d, Speaker:%d, epID:%d, childId:%d, Index:%d\n"
				, tHandle.GetConfID(), chairID(), curSpeakerID(), tHandle.GetEpID(), ptAdjust->m_tKey.m_wEpID, ptAdjust->m_wSpeakerIndex));

		TCallNode* ptSpeaker = m_pcNodeMgr->GetNode(curSpeakerID());
		TCapNode* ptSpeakerFather = m_pcNodeMgr->GetForeFatherNode(ptSpeaker);

		if ( NULL == ptSpeaker || NULL == ptSpeakerFather )
		{
			ObjError(("OnConfCnsSpeakerCascadNotify ptSpeakerFather Failed! ConfID:%d, EpID:%d, Speaker:%d\n", GetInsID(), tHandle.GetEpID(), curSpeakerID()));
			return;
		}

		if ( ptCaller->m_wEpID == curSpeakerID() )
		{
			//发言人在上级
			AdjustCnsInnerSpeak(FALSE, ptChan->m_wIndex);
			ptCaller->m_wSpearkIndex = ptChan->m_wIndex;
		}
		else
		{
			//发言人在本级, 则说明是通过语音激励切换的
			AdjustCnsInnerSpeak( TRUE, ptAdjust->m_wSpeakerIndex);
			ptSpeaker->m_wSpearkIndex = ptAdjust->m_wSpeakerIndex;

			if ( ptSpeakerFather == ptSpeaker )
			{
				AskKeyByScreen(ptSpeaker->m_wEpID, ptSpeaker->m_wSpearkIndex, EmAskKeySpeaker);
			}
		}
	}
	else
	{
		//取得发言会场在本级中的结点
		TCallNode* ptAdjNode = GetSonNode(tHandle, ptAdjust->m_tKey);
		TCapNode* ptAdjFatherNode = m_pcNodeMgr->GetForeFatherNode(ptAdjNode);
		if (NULL == ptAdjNode || NULL == ptAdjFatherNode || ptAdjNode->IsUms())
		{
			ObjError(("OnConfCnsSpeakerCascadNotify ptCnsSpeakerNode Failed! ConfID:%d, EpID:%d, Chan:%d\n", GetInsID(), tHandle.GetEpID(), ptAdjust->m_wSpeakerIndex));
			return;
		}

		TChanPara* ptAdjFatherChan = m_pcNodeMgr->GetChanByIndex(ptAdjFatherNode->m_wEpID, ums_CodecType_vid_enc, ptAdjust->m_wSpeakerIndex);
		if (NULL == ptAdjFatherChan)
		{
			ObjError(("OnConfCnsSpeakerCascadNotify UnFind ptCnsSpeakerChan! ConfID:%d, SpeakerEpID:%d, Chan:%d\n", GetInsID(), ptAdjNode->m_wEpID, ptAdjust->m_wSpeakerIndex));
			return;
		}
		
		MdlHint(Ums_Mdl_Stack, ("OnConfCnsSpeakerCascadNotify Notify UpLevel ConfID:%d, Chair:%d, Speaker:%d, AdjustCnsEpID:%d, Index:%d\n"
				, tHandle.GetConfID(), chairID(), curSpeakerID(), ptAdjNode->m_wEpID, ptAdjust->m_wSpeakerIndex));

		if( curSpeakerID() == ptAdjNode->m_wEpID )
		{
			AdjustCnsInnerSpeak( FALSE, ptAdjFatherChan->m_wIndex, ptAdjFatherNode->m_wEpID);
		}

		if (!IsChairConf())
		{//继续上报
			ptAdjNode->m_wSpearkIndex = ptAdjust->m_wSpeakerIndex;
			
			TCnsSpeakerAdjust tAdjustInfo;
			tAdjustInfo.m_wSpeakerIndex = ptAdjNode->m_wSpearkIndex;
			tAdjustInfo.m_tKey.m_wEpID = ptAdjNode->m_wEpID;

			TUmsHandle tOutHandle;
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CnsSpeakerCascad_Notify, &tAdjustInfo, sizeof(tAdjustInfo));
		}
		else
		{		
			ptAdjNode->m_wSpearkIndex = ptAdjust->m_wSpeakerIndex;
			m_pcPollMgr->AdjustCnsSpeaker(ptAdjNode);
			m_pcGetVidEx->UpdateSpeakerIndex(this, ptAdjNode->m_wEpID, ptAdjNode->m_wSpearkIndex );
			m_pcSelView->AdjustCnsSpeaker(ptAdjNode);
		    m_pcVmp->AdjustCnsSpeaker(ptAdjNode);  //下级通知上级，下级发言人会场坐席有变

			if (m_pcUmsDiscuss->IsDiscussModle())
			{
				if (ptAdjNode->IsInMix())
				{// 在讨论中
					m_pcUmsDiscuss->OnAdjustInnerSpeaker(ptAdjNode);
				}
			} 
			else if(m_pcRollCallMgr->IsRollCallModle())
			{   //点名人 的发言坐席发生了变化，会通知到顶级ums
                m_pcRollCallMgr->AdjustInnerSpeaker(ptAdjNode);
			}

			AskKeyByScreen(ptAdjNode->m_wEpID, ptAdjNode->m_wSpearkIndex, EmAskKeySpeaker);
		}
	}
}

void CUmsConfInst::OnConfMuteRemoteEpCmd(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TMuteRmtEpCmd* ptMute = (TMuteRmtEpCmd*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	TConfEpID tConfId;
	tConfId.m_wConfID = GetInsID();
	tConfId.m_wEpID = ptMute->m_wEpID;
	BOOL32 bIsMute = ptMute->m_bMute;
	
	if (ptMute->m_wEpID == TP_ALLEP_INDEX)
	{
		OnAllMuteEpForUmcCnc(&tConfId, bIsMute);
	}
	else
	{

		TCallNode* ptNode = m_pcNodeMgr->GetNode(ptMute->m_wEpID);
		TCapNode* ptFarther = m_pcNodeMgr->GetForeFatherNode(ptNode);
	
		if (NULL == ptNode || NULL == ptFarther)
		{
		ObjError(("OnConfMuteRemoteEpCmd Failed! ConfID:%d, EpID:%d\n", GetInsID(), ptMute->m_wEpID));
		return;
		}
	
		if (!ptNode->IsMtEp() || !ptNode->IsCallOn())
		{
			ObjError(("OnConfMuteRemoteEpCmd state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), ptMute->m_wEpID, UmsNodeConfType(ptNode->m_emCallState)));
			return;
		}
	
		ObjHint(("OnConfMuteRemoteEpCmd ConfID:%d, EpID:%d, bIsMute:%d, OldState:%d\n", GetInsID(), ptMute->m_wEpID, ptMute->m_bMute, ptNode->m_bMute));
	
		if (ptNode->m_bMute == ptMute->m_bMute)
		{
			return;
		}
	
		TMuteRmtEpCmd tRmtEp;
		if (ptNode == ptFarther)
		{//本级中，将真实ID传出
			tRmtEp.m_wEpID = ptNode->m_wEpID;
		}
		else
		{//下级中，将下级ID传出
			tRmtEp.m_wEpID = ptNode->m_wLowChildEpID;
		}
		tRmtEp.m_bMute = ptMute->m_bMute;
	
		TUmsHandle tOutHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_MuteRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
	}
}

void CUmsConfInst::OnConfMuteRemoteEpInd(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TMuteRmtEpInd* ptMute = (TMuteRmtEpInd*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("OnConfMuteRemoteEpInd. confid:%d, NodeID:%d, IsMute:%d\n",
				GetInsID(), tHandle.GetEpID(), ptMute->m_bMute));
	
	MuteRemoteEpInd(tHandle, ptMute);
}

void CUmsConfInst::MuteRemoteEpInd(TUmsHandle& tHandle, TMuteRmtEpInd* ptMute)
{
	TCallNode* pRootNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	
	if (NULL == pRootNode || !pRootNode->IsCallOn())
	{
		ObjError(("MuteRemoteEpInd Failed! ConfID:%d, EpID:%d\n", GetInsID(), pRootNode->m_wEpID));
		return;
	}
	
	
	TCallNode* pMuteNode = NULL;
	if (pRootNode->IsMtEp())
	{
		pMuteNode = pRootNode;
	}
	
	if (pRootNode->IsUms())
	{
		pMuteNode = GetSonNode(tHandle, ptMute->m_tKeyID);
	}
	
	if (NULL == pMuteNode)
	{
		MdlError(Ums_Mdl_Call, ("MuteRemoteEpInd MuteID error. confid:%d, epid:%d, childId:%d\n", GetInsID()
			, tHandle.GetEpID(), ptMute->m_tKeyID.m_wEpID));
		return;
	}
	
	MdlHint(Ums_Mdl_Call, ("MuteRemoteEpInd. confid:%d, NodeID:%d, IsMute:%d\n", GetInsID(), pMuteNode->m_wEpID, ptMute->m_bMute));
	
	if (pMuteNode->m_bMute == ptMute->m_bMute)
	{
		return;
	}
	pMuteNode->m_bMute = ptMute->m_bMute;
	
	if (!IsChairConf())
	{//通知上级UMS
		TMuteRmtEpInd tRmtEp;
		tRmtEp.m_bMute = ptMute->m_bMute;
		tRmtEp.m_tKeyID.m_wEpID = pMuteNode->m_wEpID;
		
		TCapNode* ptCaller = m_pcNodeMgr->GetCaller();
		TUmsHandle tOutHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptCaller->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_MuteRemoteEp_Ind, &tRmtEp, sizeof(tRmtEp));
	}
	
	//通知UI
	u8 byBuf[sizeof(TConfEpID) + sizeof(BOOL32)] = {0};
	TConfEpID* pConfID = (TConfEpID*)byBuf;
	BOOL32* pBool = (BOOL32*)(byBuf+sizeof(TConfEpID));
	pConfID->m_wConfID = GetInsID();
	pConfID->m_wEpID = pMuteNode->m_wEpID;
	*pBool = ptMute->m_bMute;
	
	NotifyMsgToService(evtp_MuteEp_Ind, byBuf, sizeof(TConfEpID) + sizeof(BOOL32));
	
	if ( IsChairConf() )
	{
		//回应
		NotifyConfCtrlMsgToCns(ev_UmsConfMute_Ind, chairID(), byBuf, sizeof(byBuf));
		//哑音通知
		NotifyConfCtrlMsgToAllCns(ev_UmsConfMute_Nty, byBuf, sizeof(byBuf));
	}
	
	return ;
}

void CUmsConfInst::OnConfQuietRemoteEpCmd(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TQuietRmtEpCmd* ptQuiet = (TQuietRmtEpCmd*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	TConfEpID tConfId;
	tConfId.m_wConfID = GetInsID();
	tConfId.m_wEpID = ptQuiet->m_wEpID;
	BOOL32 bIsMute = ptQuiet->m_bQuiet;
	
	if (ptQuiet->m_wEpID == TP_ALLEP_INDEX)
	{
		OnAllQuietEpForUmcCnc(&tConfId, bIsMute);
	}
	else
	{
		TCallNode* ptNode = m_pcNodeMgr->GetNode(ptQuiet->m_wEpID);
		TCapNode* ptFarther = m_pcNodeMgr->GetForeFatherNode(ptNode);
	
		if (NULL == ptNode || NULL == ptFarther)
		{
			ObjError(("OnConfQuietRemoteEpCmd Failed! ConfID:%d, EpID:%d\n", GetInsID(), ptQuiet->m_wEpID));
			return;
		}
	
		if (!ptNode->IsMtEp() || !ptNode->IsCallOn())
		{
			ObjError(("OnConfQuietRemoteEpCmd state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), ptQuiet->m_wEpID, UmsNodeConfType(ptNode->m_emCallState)));
			return;
		}
	
		ObjHint(("OnConfQuietRemoteEpCmd ConfID:%d, EpID:%d, bIsMute:%d, OldState:%d\n", GetInsID(), ptQuiet->m_wEpID, ptQuiet->m_bQuiet, ptNode->m_bQuiet));
	
		if (ptNode->m_bQuiet == ptQuiet->m_bQuiet)
		{
			return;
		}
	
		TQuietRmtEpCmd tRmtEp;
		if (ptNode == ptFarther)
		{//本级中，将真实ID传出
			tRmtEp.m_wEpID = ptNode->m_wEpID;
		}
		else
		{//下级中，将下级ID传出
			tRmtEp.m_wEpID = ptNode->m_wLowChildEpID;
		}
		tRmtEp.m_bQuiet = ptQuiet->m_bQuiet;
	
		TUmsHandle tOutHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_QuietRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
	}
}

void CUmsConfInst::OnConfQuietRemoteEpInd(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TQuietRmtEpInd* ptQuiet = (TQuietRmtEpInd*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("OnConfQuietRemoteEpInd. confid:%d, NodeID:%d, IsQuiet:%d\n",
		GetInsID(), tHandle.GetEpID(), ptQuiet->m_bQuiet));
	
	QuietRemoteEpInd(tHandle, ptQuiet);
}

void CUmsConfInst::QuietRemoteEpInd(TUmsHandle& tHandle, TQuietRmtEpInd* ptQuiet)
{
	TCallNode* pRootNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	
	if (NULL == pRootNode || !pRootNode->IsCallOn())
	{
		ObjError(("QuietRemoteEpInd Failed! ConfID:%d, EpID:%d\n", GetInsID(), tHandle.GetEpID()));
		return;
	}
	
	TCallNode* pQuietNode = NULL;
	if (pRootNode->IsMtEp())
	{
		pQuietNode = m_pcNodeMgr->GetNode(pRootNode->m_wEpID);
	}
	
	if (pRootNode->IsUms())
	{
		pQuietNode = GetSonNode(tHandle, ptQuiet->m_tKeyID);
	}
	
	if (NULL == pQuietNode)
	{
		MdlError(Ums_Mdl_Call, ("QuietRemoteEpInd MuteID error. confid:%d, epid:%d, childId:%d\n"
			, GetInsID(), tHandle.GetEpID(), ptQuiet->m_tKeyID.m_wEpID));
		return;
	}
	
	MdlHint(Ums_Mdl_Call, ("QuietRemoteEpInd. confid:%d, NodeID:%d, IsQuiet:%d\n", GetInsID(), pQuietNode->m_wEpID, ptQuiet->m_bQuiet));
	
	if (pQuietNode->m_bQuiet == ptQuiet->m_bQuiet)
	{
		return;
	}
	pQuietNode->m_bQuiet = ptQuiet->m_bQuiet;
	
	if (!IsChairConf())
	{//通知上级UMS
		TQuietRmtEpInd tRmtEp;
		tRmtEp.m_bQuiet = ptQuiet->m_bQuiet;
		tRmtEp.m_tKeyID.m_wEpID = pQuietNode->m_wEpID;
		
		TCapNode* ptCaller = m_pcNodeMgr->GetCaller();
		TUmsHandle tOutHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptCaller->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_QuietRemoteEp_Ind, &tRmtEp, sizeof(tRmtEp));
	}
	
	//通知UI
	u8 byBuf[sizeof(TConfEpID) + sizeof(BOOL32)] = {0};
	TConfEpID* pConfID = (TConfEpID*)byBuf;
	BOOL32* pBool = (BOOL32*)(byBuf+sizeof(TConfEpID));
	pConfID->m_wConfID = GetInsID();
	pConfID->m_wEpID = pQuietNode->m_wEpID;
	*pBool = ptQuiet->m_bQuiet;
	
	NotifyMsgToService(evtp_QuietEp_Ind, byBuf, sizeof(TConfEpID) + sizeof(BOOL32));
	
	if ( IsChairConf() )
	{
		//静音回应
		NotifyConfCtrlMsgToCns(ev_UmsConfQuiet_Ind, chairID(), byBuf, sizeof(byBuf));
		NotifyConfCtrlMsgToAllCns(ev_UmsConfQuiet_Nty, byBuf, sizeof(byBuf));
	}
}

void CUmsConfInst::OnConfTvMonitorCmd(CTpMsg *const ptMsg)
{
}
void CUmsConfInst::OnConfTvMonitorInd(CTpMsg *const ptMsg)
{
}
void CUmsConfInst::OnConfTvMonitorStop(CTpMsg *const ptMsg)
{
}

void CUmsConfInst::OnConfAskKeyToScreen(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TAskKeyByScreenTr* ptKey = (TAskKeyByScreenTr*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	EmAskKeyType emType = (EmAskKeyType)ptKey->m_dwAskType;

	u16 wSndEpID = TP_INVALID_INDEX;
	u16 wRcvEpID = TP_INVALID_INDEX;
	if( IsChairConf() )
	{//下级过来的请求
		if ( emType == EmAskKeySpeaker || emType == EmAskKeyBrdVmp )
		{
			wSndEpID = curSpeakerID();
		}
		else if ( emType == EmAskKeyChair )
		{
			wSndEpID = chairID();
			if (GetRollCallMgr()->IsRollCallModle())
			{
                wSndEpID = GetRollCallMgr()->GetRollCallerEpId();
			}
		}
		else if ( emType == EmAskKeySpeakerVmp )
		{
			wSndEpID = m_pcVmp->VmpEp();
		}

		wRcvEpID = tHandle.GetEpID();
	}
	else
	{
		wRcvEpID = CALLER_EP_INDEX;
		wSndEpID = ptKey->m_wEpID;
	}

	TCapNode* ptSndNode = m_pcNodeMgr->GetForeFatherNode(wSndEpID);
	TCapNode* ptRcvNode = m_pcNodeMgr->GetForeFatherNode(wRcvEpID);
	if ( NULL == ptSndNode || !ptSndNode->IsChanOn() || !ptRcvNode->IsChanOn() )
	{
		tpLowDtl(Ums_Mdl_Call, "OnConfAskKeyToScreen. ptSndNode is NULL! ConfID:%d, DstID:%d\n", GetInsID(), ptKey->m_wEpID);
		return ;
	}

	BOOL32 bNeedBas = FALSE;
	if( IsPriNeedBas() && CTpTypeAdpt::IsVidTransNeedBas(ptSndNode->m_tVidSndFormat.m_tFormat, ptRcvNode->m_tVidRcvFormat.m_tFormat) )
	{
		bNeedBas = TRUE;
	}

	tpLowDtl(Ums_Mdl_Call, "OnConfAskKeyToScreen. ConfID:%d, DstID:%d, ScreenIndx:%d, NeedBas:%d, AskType:%d, R1:%d, R2:%d\n", 
				GetInsID(), ptKey->m_wEpID, ptKey->m_wScreenIndex, bNeedBas, emType, ptKey->m_dwRervse1, ptKey->m_dwRervse2);

	//根据请求类型 请求
	switch( emType )
	{
	case EmAskKeySpeaker:
		{
			if ( m_pcBas->IsSpeakerNeedBas(ptRcvNode->m_tVidRcvFormat.m_tFormat) )
			{
				m_pcBas->SeeSpeakerAskFrameToBas(ptKey->m_wScreenIndex);
			}
			else
			{
				AskKeyByScreen(wSndEpID, ptKey->m_wScreenIndex, EmAskKeySpeaker, 0, 0, FALSE);
			}
		}
		break;
	case EmAskKeyChair:
		{
			if ( m_pcBas->IsChairInBas() )
			{
				m_pcBas->SeeChairAskFrameToBas(ptKey->m_wScreenIndex);
			}
			else
			{
				AskKeyByScreen(wSndEpID, ptKey->m_wScreenIndex, EmAskKeyChair, 0, 0, FALSE);
			}
		}
		break;
	case EmAskKeyGetVid:
		{
			m_pcGetVidEx->AskKeyFrameByRmtHandle(ptKey->m_dwRervse1, ptKey->m_dwRervse2);
		}
		break;
	case EmAskKeyBrdVmp:
		{
			m_pcVmp->AskFrameToBrdVmp(m_pcVmp->GetConfBrdVmp(), wRcvEpID);
		}
		break;
	case EmAskKeyPoll:
		{
			m_pcPollMgr->AskKeyFrame(ptKey->m_dwRervse1, FALSE);
		}
		break;
	case EmAskKeySpeakerVmp:
		{
			if ( m_pcVmp->IsSpeakerInVmp() && m_pcBas->IsSpeakerNeedBas(ptRcvNode->m_tVidRcvFormat.m_tFormat) )
			{//优先单屏适配
				m_pcBas->AskFrameToScreenBas(m_cSpeaker.m_pcSingleBas);
			}
			else
			{
				m_pcVmp->AskFrameToSpeakerVmp(curSpeakerID());
			}
		}
		break;
	default:
		{
			AskKeyByScreen(wSndEpID, ptKey->m_wScreenIndex, EmAskKeySpeaker, 0, 0, FALSE);
		}
		break;
	}
	
	return ;
}

void CUmsConfInst::OnConfChairInfo(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	m_tSuperInfo = *(TTPConfInfoNtfy*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	ObjHint(("OnConfChairInfo ConfID:%d, chair:%s, conf:%s, vidNum:%d, audNum:%d, Motive:%d\n"
		, GetInsID(), m_tSuperInfo.m_tChair.m_abyAlias, m_tSuperInfo.m_tConf.m_abyAlias, m_tSuperInfo.m_wChairVidSndCap, 
		m_tSuperInfo.m_wChairAudSndCap, m_tSuperInfo.m_bMixMotive));

	TChairConfInfo tChair;
	tChair.m_wConfID = GetInsID();
	tChair.m_tBeginTime = time(NULL) - m_tConfBaseInfo.m_tStartTime;
	tChair.m_tChairName.SetAlias(m_tSuperInfo.m_tChair.m_abyAlias);
	tChair.m_tConfName.SetAlias(m_tSuperInfo.m_tConf.m_abyAlias);
	NotifyMsgToServiceForUI(evtp_ChairConfInfo_Notify, &tChair, sizeof(tChair));

	TUmsHandle tOutHandle;
	for (TCallNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
	{
		if (ptItor->IsCallOn())
		{			
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptItor->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_StatusInfo_Notify, &m_tSuperInfo, sizeof(m_tSuperInfo));

			//CNS通知主席信息
			if ( ptItor->IsCns() )
			{
				NotifyConfCtrlMsgToCns(ev_UmsChairConfInfo_Nty, ptItor->m_wEpID, &tChair, sizeof(TChairConfInfo));
			}
		}
	}

	if (!IsChairConf() && m_tSuperInfo.m_bSpeakOnline)
	{
		AdjustNewSpeakerToAllNode();
	}
}

void CUmsConfInst::OnConfChairCapNotify(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TChairInfoTr tSuperCap = *(TChairInfoTr*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	ObjHint(("OnConfChairCapNotify ConfID:%d, old:%d, new:%d\n", GetInsID(), m_tSuperChairCap.m_wSpeakerIndex, tSuperCap.m_wSpeakerIndex));

	m_tSuperChairCap.m_wSpeakerIndex = tSuperCap.m_wSpeakerIndex;

	NotifyChairCapToLowUms();

	if (curSpeakerID() != chairID())
	{
		TCapNode* ptSpeaker = GetNodeMgr()->GetCapsetNode(curSpeakerID());
		if( NULL != ptSpeaker )
		{
			GetNodeFsm()->ChangeSpeaker(ptSpeaker);
		}
	}	
}

void CUmsConfInst::OnResetFastUpdate(CTpMsg* const ptMsgr)
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsgr->GetBody());

	ObjHint(("OnResetFastUpdate ConfID:%d, EpID:%d\n", GetInsID(), tHandle.GetEpID()));

	TCapNode* ptCapNode = m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
	if (NULL == ptCapNode)
	{
		ObjError(("OnResetFastUpdate Invalid node. ConfID:%d, EpID:%d\n", GetInsID(), tHandle.GetEpID()));
		return ;
	}

	if (!ptCapNode->IsChanOn())
	{
		ObjError(("OnResetFastUpdate Channel is not opened. ConfID:%d, EpID:%d\n", GetInsID(), tHandle.GetEpID()));
		return ;
	}

	u16 wDstEp = TP_INVALID_INDEX;
	if ( ptCapNode->m_wEpID == curSpeakerID() )
	{//发言人，则清下主席的编码保护
		wDstEp = chairID();
	}
	else
	{
		wDstEp = curSpeakerID();
	}

	TCapNode* ptDstNode = m_pcNodeMgr->GetCapsetNode(wDstEp);
	if ( NULL == ptDstNode )
	{
		ObjError(("OnResetFastUpdate. DstEp Invalid node. ConfID:%d, EpID:%d\n", GetInsID(), wDstEp));
		return ;
	}

	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (ptCapNode->m_tRmtChan.m_atVidDec[wIndex].IsOpen())
		{
			ptCapNode->m_tRmtChan.m_atVidDec[wIndex].m_tKeyFrameStatis.Clear();
		}

		if (ptDstNode->m_tRmtChan.m_atVidEnc[wIndex].IsOpen())
		{
			ptDstNode->m_tRmtChan.m_atVidEnc[wIndex].m_tKeyFrameStatis.Clear();
		}
	}

	return ;
}

void CUmsConfInst::OnConfFlowCtrl(CTpMsg *const ptMsg)
{
	TUmsHandle tHandle;
	TFlowControl tInfo;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(TUmsHandle));
	
	ObjHint(("OnConfFlowCtrl ConfID:%d, DstID:%d, band:%d\n", GetInsID(), tInfo.m_tEpKey.m_wEpID, tInfo.m_wBand));
	
	TCallNode* ptNode = m_pcNodeMgr->GetNode(tInfo.m_tEpKey.m_wEpID);
	if (NULL != ptNode)
	{
		m_pcCallMgr->FlowControl(ptNode->m_wEpID, tInfo.m_wEncNo, tInfo.m_wBand);
		if (tInfo.m_wBand > 0)
		{
			AskKeyByEpID(ptNode->m_wEpID, EmAskKeySpeaker);
		}
	}
}

void CUmsConfInst::OnConfAdjustFrameRate(CTpMsg *const ptMsg)
{
	TUmsHandle tHandle;
	TAdjustFrameRate tInfo;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(TUmsHandle));

	ObjHint(("OnConfAdjustFrameRate ConfID:%d, DstID:%d, frame:%d\n", GetInsID(), tInfo.m_wEpID, tInfo.m_wFrameRate));

	m_pcNodeMgr->AdjustNodeFrame(tInfo.m_wEpID, tInfo.m_wScreenIndx, tInfo.m_wFrameRate, tInfo.m_bReset);

	return ;
}

void CUmsConfInst::OnConfAdjustVidRes(CTpMsg *const ptMsg)
{
	TUmsHandle tHandle;
	TAdjustVidRes tInfo;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(TUmsHandle));
	
	ObjHint(("OnConfAdjustVidRes ConfID:%d, DstID:%d, ScrIndex:%d, res:%d\n", GetInsID(), tInfo.m_wEpID, tInfo.m_wScreenIndx, tInfo.m_dwVidRes));
	
	m_pcNodeMgr->AdjustNodeRes(tInfo.m_wEpID, tInfo.m_wScreenIndx, (EmTpVideoResolution)tInfo.m_dwVidRes, tInfo.m_bReset);
	
	return ;
}

void CUmsConfInst::OnTerListReq( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());

	TCallNode* ptNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if ( NULL == ptNode )
	{
		MdlError(Ums_Mdl_Call, ("OnTerListReq. ConfID:%d, EpID:%d, ptNode:%d\n", GetInsID(), tHandle.GetEpID(), ptNode));
		return ;
	}

	NotifyAllCnsListToCns(ptNode);

	return ;
}

void CUmsConfInst::OnDaemonMediaKeyFail(CTpMsg *const ptMsg,  CApp* pcApp)
{
	u32 dwAppID = GETAPP(ptMsg->GetSrcIId());

	if (dwAppID == AID_UMSSIPADAPTER_APP)
	{
		TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
		u8* pData = ptMsg->GetBody()+sizeof(TUmsHandle);

		TTPQtMediaKeyFail *ptInfo = (TTPQtMediaKeyFail *)(pData);
	    s8* pszAlias = ptInfo->m_szLocalAlias;

		for (u16 wDstInst = 1; wDstInst <= TP_UMS_MAX_CONFNUM; wDstInst++) 
		{
			CUmsConfInst* pcInst =  (CUmsConfInst*)pcApp->GetInstance(wDstInst);
			ObjHint(("[quantum]m_achConfName:%s, LocalAlias:%s, %d-%s\n", pcInst->m_tConfBaseInfo.m_achConfName, pszAlias, ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
			if(inst_idle == pcInst->CurState())
			{
				continue;
			}
			else
			{
				if (0 == strcmp(pcInst->m_tConfBaseInfo.m_achConfName, pszAlias))
				{
					pcInst->MessageProc(ptMsg);
					return;
				}
				if (0 == strcmp(pcInst->m_tConfBaseInfo.m_achConfE164, pszAlias))
				{
					pcInst->MessageProc(ptMsg);
					return;
				}
			}
		}
	}
	else
	{
        ObjError(("OnDaemonMediaKeyFail. msg not from UMSSIPADAPTER!\n"));
	}
}



void CUmsConfInst::OnDaemonMediaKeyNty(CTpMsg *const ptMsg,  CApp* pcApp)
{
     u32 dwAppID = GETAPP(ptMsg->GetSrcIId());

	 if (dwAppID == AID_UMSSIPADAPTER_APP)
	 {
		 TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
		 u8* pData = ptMsg->GetBody()+sizeof(TUmsHandle);
	     TTPMediaKeyInfo *ptInfo = (TTPMediaKeyInfo *)(pData);
		 s8* pszAlias = ptInfo->m_szAlias;

		 for (u16 wDstInst = 1; wDstInst <= TP_UMS_MAX_CONFNUM; wDstInst++) 
		 {
			 CUmsConfInst* pcInst =  (CUmsConfInst*)pcApp->GetInstance(wDstInst);
			 ObjHint(("[quantum]m_achConfName:%s, LocalAlias:%s, %d-%s\n", pcInst->m_tConfBaseInfo.m_achConfName, pszAlias, ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
			
			 if(inst_idle == pcInst->CurState())
			 {
				 continue;
			 }
			 else
			 {
				 if (0 == strcmp(pcInst->m_tConfBaseInfo.m_achConfName, pszAlias))
				 {
					 pcInst->MessageProc(ptMsg);
					 return;
				 }

				 if (0 == strcmp(pcInst->m_tConfBaseInfo.m_achConfE164, pszAlias))
				 {
					 pcInst->MessageProc(ptMsg);
					 return;
				 }
			 }
		 }
	 }
	 else
	 {
		 ObjError(("OnDaemonMediaKeyNty. msg not from UMSSIPADAPTER!\n"));
	 }

	 return;
}


void  CUmsConfInst::SetQtEncryptInfo(u8* pData, u16 wDataSize )
{
	TUmsHandle	tHandle;
	EmTpConfProtocol emProType;
	TTPQTEncryptInfo tTPQTEncryptInfo;
	TEqpRes tAdapterEqp[MAX_ADAPTER_MDL_NUM];
	u8 achBuf[sizeof(TTPQTEncryptInfo) + sizeof(EmTpConfProtocol) + 1];

    TP_SAFE_CAST( tTPQTEncryptInfo, pData );
    emProType = emTpAllProc;

	MdlHint(Ums_Mdl_Call, ("[ CUmsConfInst::SetQtEncryptInfo] QuanTumIP->"TPIPFORMAT", dwQuanTumID->%d\n",
		Tpu32ToIP(tTPQTEncryptInfo.m_dwQuanTumIP),
		tTPQTEncryptInfo.m_dwQuanTumID));

	if (GetAllEqpRes(tAdapterEqp, MAX_ADAPTER_MDL_NUM, em_adapter_mdl))
	{
		for (u16 wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM; ++wIndex)
		{
			tHandle.Clear();

			if (tAdapterEqp[wIndex].IsValid())
			{
				tHandle.m_dwAdapteID  = tAdapterEqp[wIndex].m_dwEqpNode;
				tHandle.MakeAppHandle(AID_UMSCONFMGR, 0);

				memset( achBuf, 0, sizeof(achBuf));
				memcpy( achBuf, &tTPQTEncryptInfo, sizeof(tTPQTEncryptInfo) );
                memcpy( achBuf + sizeof(tTPQTEncryptInfo), &emProType, sizeof(emProType) );
				UmsSetQTEncryptInfo(ev_QTEncryptInfo_Nty, tHandle, achBuf, sizeof(TTPQTEncryptInfo) + sizeof(EmTpConfProtocol) + 1);
			}
		}
	}

}


void CUmsConfInst::DaemonProQtMsg(CTpMsg *const ptMsg,  CApp* pcApp)
{
    u16 wEvent = ptMsg->GetEvent();
	u8* pData = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();

    TUmsHandle tHandle;
    CUmsConfInst* pInst = NULL;

	switch(wEvent)
	{
	    case ev_SetQTEncryptInfo_Cmd:
            SetQtEncryptInfo(pData, wDataSize);
			break;

		case evtp_QtQueryAlias_req:
			DaemonProQueryAlias(ptMsg);
			break;

		case evtp_QtQueryAlias_rsp:
			TP_SAFE_CAST(tHandle, ptMsg->GetBody());
			TTPQTQueryData tInfo;
			EmQueryAliasRes tQuerRet;
			EmTPConfEncFrequency emFrq;
			TP_SAFE_CAST(tInfo, ptMsg->GetBody()+sizeof(TUmsHandle));
			TP_SAFE_CAST(tQuerRet, ptMsg->GetBody()+ sizeof(TUmsHandle) + sizeof(TTPQTQueryData));
            TP_SAFE_CAST(emFrq, ptMsg->GetBody()+ sizeof(TUmsHandle) + sizeof(TTPQTQueryData) + sizeof(EmQueryAliasRes));
			MdlHint( Ums_Mdl_Call, ("[CUmsConfInst::DaemonProQtMsg evtp_QtQueryAlias_rsp] m_wIndex:%d, m_szAlias:%s, Frq:%d(0:EverySeconds), QuerRet:%d(0:Sucess)\n",
				tInfo.m_wIndex, tInfo.m_szAlias, emFrq, tQuerRet) );
			UmsSendConfCtrl(tHandle, ptMsg->GetEvent(), ptMsg->GetBody()+sizeof(tHandle), ptMsg->GetBodyLen()-sizeof(tHandle));
			break;

		case evtp_MediaKey_Nty:
            OnDaemonMediaKeyNty(ptMsg, pcApp);
			break;

        case evtp_QtMediaFail_Cmd:
			OnDaemonMediaKeyFail(ptMsg, pcApp);
			break;


		case evtp_MediaDstMT_Nty:
			TP_SAFE_CAST(tHandle, ptMsg->GetBody());
			pInst =  (CUmsConfInst*)pcApp->GetInstance(tHandle.GetConfID());
			if (pInst)
			{
                 pInst->MessageProc(ptMsg);
			}
			break;

		default:
			break;
	}

	return;
}


void CUmsConfInst::OnMediaKeyFail( CTpMsg* const ptMsg )
{
	TTPQtMediaKeyFail tFail;
	TP_SAFE_CAST(tFail, ptMsg->GetBody()+sizeof(TUmsHandle));
	
	ObjHint(("[OnMediaKeyFail] ConfID:%d, PeerIP->"TPIPFORMAT",LocalAlias:%s,PeerAlias:%s\n", 
		     GetInsID(), Tpu32ToIP(tFail.m_dwPeerIP),tFail.m_szLocalAlias,tFail.m_szPeerAlias));

	//取得的码流秘钥失败，则直接挂断会议
	SelfHungupImmediately(TP_UMS_QT_MediaKeyFail);
}


void CUmsConfInst::OnMediaKeyDstMTNty(CTpMsg* const ptMsg)
{
	TUmsHandle tHandle;
	s8 szAlias[TP_MAX_ALIAS_LEN+1] = {0};
	s8 abyIpAlias[TP_MAX_ALIAS_LEN+1];
	BOOL32 bFindOutMiakeyMT = FALSE;

	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	memcpy(szAlias, ptMsg->GetBody()+sizeof(TUmsHandle), TP_MAX_ALIAS_LEN);
	
	MdlHint(Ums_Mdl_Call, ("OnMediaKeyDstMTNty szAlias:%s\n", szAlias));
	
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if (bFindOutMiakeyMT)
		{
			ptNode->m_bSetMediaKeyMT = TRUE;
			continue;
		}
		
        if (ptNode->m_tCalledAddr.m_tAlias.m_abyAlias[0] != '\0')
		{
			//如协商的是下级ums（ums 和ums协商码流秘钥）,不给该ums发码流秘钥
			if ((strcmp(szAlias, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias) == 0))
			{
				ptNode->m_bSetMediaKeyMT = FALSE;
				MdlHint(Ums_Mdl_Call, ("OnMediaKeyDstMTNty Alias eq ntyalias confid:%d epid:%d NodeAlias:%s  XieShangAlias:%s  bSetMediaKeyMT:%d\n", 
					                   GetInsID(), ptNode->m_wEpID,
					                   ptNode->m_tCalledAddr.m_tAlias.m_abyAlias, szAlias, ptNode->m_bSetMediaKeyMT));
				
				bFindOutMiakeyMT = TRUE;
				continue;
			}
			
		} else if (ptNode->m_tCalledAddr.m_tE164.m_abyAlias[0] != '\0')
		{
			if ((strcmp(szAlias, ptNode->m_tCalledAddr.m_tE164.m_abyAlias) == 0))
			{
				ptNode->m_bSetMediaKeyMT = FALSE;
				MdlHint(Ums_Mdl_Call, ("OnMediaKeyDstMTNty 164 eq ntyalias confid:%d epid:%d Node164Alias:%s  XieShangAlias:%s  bSetMediaKeyMT:%d\n", 
					                  GetInsID(), ptNode->m_wEpID,
					                  ptNode->m_tCalledAddr.m_tE164.m_abyAlias, szAlias, ptNode->m_bSetMediaKeyMT));
				
				bFindOutMiakeyMT = TRUE;
				continue;
			}
		}else if (ptNode->m_tConfName.m_abyAlias[0] != '\0')
		{
			if ((strcmp(szAlias, ptNode->m_tConfName.m_abyAlias) == 0))
			{
				ptNode->m_bSetMediaKeyMT = FALSE;
				MdlHint(Ums_Mdl_Call, ("OnMediaKeyDstMTNty confname eq ntyalias confid:%d epid:%d confname:%s  XieShangAlias:%s  bSetMediaKeyMT:%d\n", 
					                   GetInsID(), ptNode->m_wEpID,
					                  ptNode->m_tConfName.m_abyAlias, szAlias, ptNode->m_bSetMediaKeyMT));
				
				bFindOutMiakeyMT = TRUE;
				continue;
			}
		}	
		else if (ptNode->m_tCalledAddr.m_dwIP)
		{
			sprintf(abyIpAlias, TPIPFORMAT, Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP));
			if ((strcmp(szAlias, abyIpAlias) == 0))
			{
				ptNode->m_bSetMediaKeyMT = FALSE;
				MdlHint(Ums_Mdl_Call, ("OnMediaKeyDstMTNty ipalias eq ntyalias confid:%d epid:%d IpAlias:%s  XieShangAlias:%s  bSetMediaKeyMT:%d\n", 
					                  GetInsID(), ptNode->m_wEpID,
					                  abyIpAlias, szAlias, ptNode->m_bSetMediaKeyMT));
				
				bFindOutMiakeyMT = TRUE;
				continue;
			}
		} else {
			ptNode->m_bSetMediaKeyMT = TRUE;
		}
		
	}
	
}




void CUmsConfInst::OnMediaKeyNty(CTpMsg* const ptMsg)
{
	TUmsHandle tHandle;
	TTPMediaKeyInfo tMediaKeyInfo;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TP_SAFE_CAST(tMediaKeyInfo, ptMsg->GetBody()+sizeof(TUmsHandle));
	
	m_atMediaKey[m_wMediaKeyIndx].m_dwHandle = tMediaKeyInfo.m_dwHandle;
	m_atMediaKey[m_wMediaKeyIndx].m_wIndex   = tMediaKeyInfo.m_wIndex;
	memcpy(m_atMediaKey[m_wMediaKeyIndx].m_szAlias, tMediaKeyInfo.m_szAlias, TP_MAX_ALIAS_LEN);
	memcpy(m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey, tMediaKeyInfo.m_szMediaKey1, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, tMediaKeyInfo.m_szMediaKey2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, tMediaKeyInfo.m_szMediaKey3, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, tMediaKeyInfo.m_szMediaKey4, TP_MAX_MEDIAKEY_LEN/4);
	m_atMediaKey[m_wMediaKeyIndx].m_dwKeyLen       = tMediaKeyInfo.m_dwKeyLen;
	m_atMediaKey[m_wMediaKeyIndx].m_emKeyFrequency = tMediaKeyInfo.m_emKeyFrequency;
	m_atMediaKey[m_wMediaKeyIndx].m_dwQtFlag       = tMediaKeyInfo.m_dwQtFlag;
	

	MdlHint(Ums_Mdl_Call, ("OnMediaKeyNty Handle:%d, Index:%d, QtFlag:%u, dwLen:%d.\n", m_atMediaKey[m_wMediaKeyIndx].m_dwHandle, m_atMediaKey[m_wMediaKeyIndx].m_wIndex,m_atMediaKey[m_wMediaKeyIndx].m_dwQtFlag,m_atMediaKey[m_wMediaKeyIndx].m_dwKeyLen));
	
	m_bSetMediaKey = TRUE;

	//TODO  
	m_pcTvWallMgr->SetMediaKey(this, m_atMediaKey[m_wMediaKeyIndx]);
	m_pcEapu->SetMediaKey(m_atMediaKey[m_wMediaKeyIndx], NULL);  //m_pcEapu中的mix都是本会议所用到的mix
	m_pcVmpTpHandle->SetMediaKey(NULL, m_atMediaKey[m_wMediaKeyIndx], this); //mpu2tp
	m_pcBas->SetQtMediaKey(m_atMediaKey[m_wMediaKeyIndx]);  //vbas abas
	m_pcVmp->SetQtMediaKey(m_atMediaKey[m_wMediaKeyIndx], GetInsID());
	
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn())
		{
			continue;
		}
		
		if (!ptNode->m_bSetMediaKeyMT)
		{
			continue;
		}

		TUmsHandle tOutHandle;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		
		TTPMediaKeyInfo tInfo;
		tInfo.m_dwHandle = m_atMediaKey[m_wMediaKeyIndx].m_dwHandle;
		memcpy(tInfo.m_szAlias, m_atMediaKey[m_wMediaKeyIndx].m_szAlias, TP_MAX_ALIAS_LEN);
		tInfo.m_szAlias[TP_MAX_ALIAS_LEN] = '\0';
		tInfo.m_wIndex = m_atMediaKey[m_wMediaKeyIndx].m_wIndex;
		memcpy(tInfo.m_szMediaKey1, m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey, TP_MAX_MEDIAKEY_LEN/4);
		memcpy(tInfo.m_szMediaKey2, m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
		memcpy(tInfo.m_szMediaKey3, m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
		memcpy(tInfo.m_szMediaKey4, m_atMediaKey[m_wMediaKeyIndx].m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
		
		tInfo.m_dwKeyLen = m_atMediaKey[m_wMediaKeyIndx].m_dwKeyLen;
		tInfo.m_emKeyFrequency = m_atMediaKey[m_wMediaKeyIndx].m_emKeyFrequency;
		tInfo.m_dwQtFlag = m_atMediaKey[m_wMediaKeyIndx].m_dwQtFlag;
		
		UmsSendConfCtrl(tOutHandle, evtp_MediaKey_Nty, &tInfo, sizeof(tInfo));
	}
	
	m_wMediaKeyIndx ++;
	if ( m_wMediaKeyIndx == TP_MAX_OLD_KEY_NUM )
	{
		m_wMediaKeyIndx = 0;
	}
}



void CUmsConfInst::DaemonProQueryAlias(CTpMsg *const ptMsg)
{
    u16 wEvent = ptMsg->GetEvent();
	u8* pData = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();
	
	TTPQTQueryData tQdataInfo;
    TUmsHandle tHandle;
	EmQueryAliasRes emRet = emQueryFailed;
	EmTPConfEncFrequency  emfrq = emTPConfEncFrequencyEveryConf;
	u16 wSaveIndex;

    TP_SAFE_CAST(tHandle, (u8*)pData);
	TP_SAFE_CAST(tQdataInfo, (u8*)pData + sizeof(TUmsHandle));

	u8 abBuf[sizeof(TTPQTQueryData)+sizeof(EmQueryAliasRes)+sizeof(EmTPConfEncFrequency)] = {0};

	if (EmQtAliasType_PartyNumber == tQdataInfo.m_tQueryType)
	{ //临时会议查询
		 if (!tQdataInfo.m_IsMedia)
		 {
              wSaveIndex = m_QueryAliasMgr.SaveQueryData(&tQdataInfo);
			  if (SAVE_INDEX_INVALID != wSaveIndex)
			  { 
				  tHandle.handAppCall = 0xffff;
                  m_QueryAliasMgr.GetRspQueryAliasName(wSaveIndex, tQdataInfo.m_szAlias, sizeof(tQdataInfo.m_szAlias));
				  emRet = emQuerySuccess;

				  if (tQdataInfo.m_emQueryFreq == emTPEncryptTypeQtEverySecond)
				  {
                       emfrq = emTPConfEncFrequencyEverySeconds;
				  } else if (tQdataInfo.m_emQueryFreq == emTPEncryptTypeQtEveryMinute)
				  {
                       emfrq = emTPConfEncFrequencyEveryMinute;
				  }else if(tQdataInfo.m_emQueryFreq == emTPEncryptTypeQtEveryConf)
				  {
                       emfrq = emTPConfEncFrequencyEveryConf;
				  } 
			  } 
			  else
			  {
				  MdlError(Ums_Mdl_Call, ("[CUmsConfInst::DaemonProQueryAlias] SaveQueryData for querykey fail\n"));
			  }
		 }
		 else 
		 {
              wSaveIndex = m_QueryAliasMgr.FindDataInfo(&tQdataInfo);
			  if (SAVE_INDEX_INVALID != wSaveIndex)
			  {
                  tHandle.handAppCall = m_QueryAliasMgr.GetConfID(wSaveIndex);
				  m_QueryAliasMgr.GetRspQueryAliasName(wSaveIndex, tQdataInfo.m_szAlias, sizeof(tQdataInfo.m_szAlias));

				  emRet = emQuerySuccess;
				  EmTPEncryptType emEnc=  m_QueryAliasMgr.GetEncFrq(wSaveIndex);

				  if (emEnc == emTPEncryptTypeQtEverySecond)
				  {
					  emfrq = emTPConfEncFrequencyEverySeconds;
				  } else if (emEnc == emTPEncryptTypeQtEveryMinute)
				  {
					  emfrq = emTPConfEncFrequencyEveryMinute;
				  }else if(emEnc == emTPEncryptTypeQtEveryConf)
				  {
					  emfrq = emTPConfEncFrequencyEveryConf;
				  } 
			  }
			  else
			  {
                   MdlError(Ums_Mdl_Call, ("[CUmsConfInst::DaemonProQueryAlias] FindDataInfo for querymiadiakey  fail\n"));
			  }
		 }

		 memcpy((u8 *)abBuf, &tQdataInfo, sizeof(TTPQTQueryData));
	     memcpy((u8 *)abBuf + sizeof(TTPQTQueryData), &emRet, sizeof(EmQueryAliasRes));
		 memcpy((u8 *)abBuf + sizeof(TTPQTQueryData) + sizeof(EmQueryAliasRes) , &emfrq, sizeof(EmTPConfEncFrequency));

		 MdlHint( Ums_Mdl_Call, ("[CUmsConfInst::DaemonProQueryAlias evtp_QtQueryAlias_rsp] m_wIndex:%d, m_szAlias:%s, Frq:%d(0:EverySeconds), QuerRet:%d(0:Sucess)\n",
			 tQdataInfo.m_wIndex, tQdataInfo.m_szAlias, emfrq, emRet) );
		 UmsSendConfCtrl(tHandle, evtp_QtQueryAlias_rsp, abBuf,sizeof(abBuf));
	}
	else
	{
        NotifyMsgToService(wEvent, pData, wDataSize);
	}


}

BOOL32 CUmsConfInst::ProQtMsg(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	u32 dwAppID = GETAPP(ptMsg->GetSrcIId());


    switch (wEvent)
	{
    case evtp_MediaKey_Nty:
		OnMediaKeyNty(ptMsg);
        break;

	case evtp_QtMediaFail_Cmd:
		OnMediaKeyFail(ptMsg);
        break;

	case evtp_MediaDstMT_Nty:
        OnMediaKeyDstMTNty(ptMsg);
		break;

	case evtp_QuantumEvent_Begin:
	case evtp_QuantumEvent_End:
		MdlError( Ums_Mdl_Call, ("[ CUmsConfInst::ProQtMsg] receive msg evtp_QuantumEvent_Begin, evtp_QuantumEvent_end\n"));
		break;

	default:
		break;
	}


     return TRUE;
}


/*==============================================================================
函数名    :  UpdateNodeInfo
功能      :  避免频繁刷新UI列表
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-25               zhaixiaogang
==============================================================================*/
void CUmsConfInst::UpdateNodeInfo(EmTpOprType emOpr, u16 wEpID)
{
	m_tUpdateNodeList.Add(emOpr, wEpID);

	if (m_tUpdateNodeList.m_bRefreshImm)
	{
		NotifyUpdateNodeToUi();
		KillTimer(evtp_UpdateConfNode_time);
	}
	else
	{
		if (m_tUpdateNodeList.m_wNum == 1)
		{
			SetTimer(evtp_UpdateConfNode_time, TP_INTERVAL_TIME_ONE_SECOND);
		}
	}
}

void CUmsConfInst::NotifyUpdateNodeToUi()
{
	//更新至UI
	TConfCnsInfo tUpdateList;
	tUpdateList.m_wConfID = GetInsID();
	tUpdateList.m_emOpr = tp_OprType_Update;
	
	TConfCnsInfo tAddList;
	tAddList.m_wConfID = GetInsID();
	tAddList.m_emOpr = tp_OprType_Add;
	
	TConfCnsInfo tDelList;
	tDelList.m_wConfID = GetInsID();
	tDelList.m_emOpr = tp_OprType_Del;
	
	TCallNode* ptNode;
	TConfCnsInfo* ptList = NULL;
	for (u16 wIndex = 0; wIndex < m_tUpdateNodeList.m_wNum; ++wIndex)
	{
		ptNode = m_pcNodeMgr->GetNode(m_tUpdateNodeList.m_atNode[wIndex].m_wEpID);
		if (NULL == ptNode)
		{
			continue;
		}
		
		if (tp_OprType_Update == m_tUpdateNodeList.m_atNode[wIndex].m_emOpr)
		{				
			ptList = &tUpdateList;
		}
		else if (tp_OprType_Add == m_tUpdateNodeList.m_atNode[wIndex].m_emOpr)
		{				
			ptList = &tAddList;
		}
		else if (tp_OprType_Del == m_tUpdateNodeList.m_atNode[wIndex].m_emOpr)
		{				
			ptList = &tDelList;
		}

		ptNode->GetCnsInfo(ptList->m_tConfCnsList[ptList->m_wNum]);
		ptList->m_wNum++;
	}

	if (tUpdateList.m_wNum >= 1)
	{
		NotifyMsgToServiceForUI(evtp_UpdateConfCnsList_Notify, &tUpdateList, sizeof(tUpdateList));
		SendNodeInfoToAllCNS(&tUpdateList);
	}
	if (tAddList.m_wNum >= 1)
	{
		NotifyMsgToServiceForUI(evtp_UpdateConfCnsList_Notify, &tAddList, sizeof(tAddList));	
		SendNodeInfoToAllCNS(&tAddList);
	}
	if (tDelList.m_wNum >= 1)
	{
		NotifyMsgToServiceForUI(evtp_UpdateConfCnsList_Notify, &tDelList, sizeof(tDelList));	
		SendNodeInfoToAllCNS(&tDelList);
	}

	//更新至上级列表
	m_pcCallMgr->NotifyToHigherUpdateEp(m_tUpdateNodeList);

	//清除
	m_tUpdateNodeList.Clear();
}


void CUmsConfInst::SendNodeInfoToAllCNS( TConfCnsInfo* ptList )
{
	TUmsHandle tOutHandle;

	for (TCallNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
	{
		if(NULL == ptItor || !ptItor->m_bUsed)
		{
			continue;	
		}

		if ( !ptItor->IsCallOn() )
		{
			continue;
		}

		if( !ptItor->IsMtEp() )
		{
			continue;
		}
		
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptItor->m_wEpID);	
		UmsSendConfCtrl(tOutHandle, evtp_Conf_CnsList_Notify, ptList, sizeof(TConfCnsInfo));
	}
	
	return ;
}

void CUmsConfInst::NotifyConfInfoToCnsOnChanConnect( TCallNode* ptNode )
{
	if ( NULL == ptNode || !ptNode->IsCns() )
	{
		return ;
	}

	TUmsHandle tOutHandle;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);

	if ( ptNode->m_wEpID == chairID() )
	{
		//讨论状态通知 只通知到主席即可
		TConfAuxMixInfo tAudMixInfo;
		m_pcUmsDiscuss->GetDiscussStateInfo(tAudMixInfo);
		NotifyConfCtrlMsgToCns( ev_UmsConfAMixUpdate_Nty, ptNode->m_wEpID, &tAudMixInfo, sizeof(tAudMixInfo));
		
		// 通知主席全局静音哑音状态
		TConfEpID tConfEp;
		tConfEp.m_wConfID = GetInsID();
		tConfEp.m_wEpID = TP_ALLEP_INDEX;
		
		s8 szBuf[sizeof(TConfEpID) + sizeof(BOOL)] = {0};
		memcpy(szBuf, &tConfEp, sizeof(tConfEp));
		memcpy(szBuf+sizeof(tConfEp), &m_bIsAllEpMute, sizeof(BOOL));
		NotifyConfCtrlMsgToCns(ev_UmsConfMute_Nty, ptNode->m_wEpID, szBuf, sizeof(szBuf));
		
		memcpy(szBuf+sizeof(tConfEp), &m_bIsAllEpQuiet, sizeof(BOOL));
		NotifyConfCtrlMsgToCns(ev_UmsConfQuiet_Nty, ptNode->m_wEpID, szBuf, sizeof(szBuf));

		//通知主席会议中的视频源 远遥信息
		TConfVidFeccInfo tVidFeccList;
		tVidFeccList.m_wConfID	= GetInsID();
		tVidFeccList.m_emOpr	= tp_OprType_Update;
		
		for (TCallNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
		{
			if(!ptNode->m_bUsed)
			{
				continue;	
			}		
			
			if (tVidFeccList.m_wNum >= TP_REFRESH_LIST_THREE)
			{
				UmsSendConfCtrl(tOutHandle, evtp_UMS_CNS_VidFeccInfoNty, &tVidFeccList, sizeof(TConfVidFeccInfo));
				tVidFeccList.m_wNum = 0;
			}
			
			ptNode->GetVidFeccInfo(tVidFeccList.m_atVidFeccList[tVidFeccList.m_wNum]);
			tVidFeccList.m_wNum++;
		}
		
		if (tVidFeccList.m_wNum > 0)
		{
			UmsSendConfCtrl(tOutHandle, evtp_UMS_CNS_VidFeccInfoNty, &tVidFeccList, sizeof(TConfVidFeccInfo));
		}

	}
	
	//切换发言人通知
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = GetInsID();
	tConfEpID.m_wEpID = curSpeakerID();

	if (GetRollCallMgr()->IsUIRollCallOn())
	{   //点名时，UMS将被点名人当做发言人处理的，但通知到界面的发言人应为原始发言人 
        tConfEpID.m_wEpID = GetRollCallMgr()->GetBackUpSpeaker();
	}
	
	NotifyConfCtrlMsgToCns( ev_UmsConfApplySpeaker_Nty, ptNode->m_wEpID, &tConfEpID, sizeof(tConfEpID));

	//主席信息
	TChairConfInfo tChair;
	tChair.m_wConfID = GetInsID();

	tChair.m_tBeginTime = time(NULL) - m_tConfBaseInfo.m_tStartTime;
	if ( IsChairConf() )
	{
		TCallNode* ptChair = m_pcNodeMgr->GetNode(chairID());
		if ( ptChair && ptChair->IsCallOn() )
		{
			tChair.m_tChairName.SetAlias(ptChair->m_tConfName.m_abyAlias);
		}
		tChair.m_tConfName.SetAlias(m_tConfBaseInfo.m_achConfName);
	}
	else
	{
		tChair.m_tChairName.SetAlias(m_tSuperInfo.m_tChair.m_abyAlias);
		tChair.m_tConfName.SetAlias(m_tSuperInfo.m_tConf.m_abyAlias);
	}
	NotifyConfCtrlMsgToCns( ev_UmsChairConfInfo_Nty, ptNode->m_wEpID, &tChair, sizeof(tChair));

	return ;
}

void CUmsConfInst::NotifyAllCnsListToCns( TCallNode* ptNode )
{
	//只通知会场列表
	if ( !ptNode->IsMtEp() )
	{
		return ;
	}

	TUmsHandle tOutHandle;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
	
	TConfCnsInfo tCnsList;
	tCnsList.m_bLastPack = FALSE;
	tCnsList.m_wConfID = GetInsID();
	tCnsList.m_emOpr = tp_OprType_Add;
	
	TCallNode* ptNodeUpdate = NULL;
	u16 awAllEpID[TP_CONF_MAX_CNSNUM];
	u16 wEpAllNum = m_pcNodeMgr->GetAllNode( awAllEpID, TP_CONF_MAX_CNSNUM );
	
	for (u16 wI = 0; wI < wEpAllNum; ++wI)
	{
		ptNodeUpdate = m_pcNodeMgr->GetNode(awAllEpID[wI]);
		if(NULL == ptNodeUpdate || !ptNodeUpdate->m_bUsed)
		{
			continue;	
		}
		
		if (awAllEpID[wI] == CALLER_EP_INDEX)
		{
            continue;
		}
		
		if (tCnsList.m_wNum >= TP_REFRESH_LIST_THREE)
		{
			if (wI+1 == wEpAllNum)
			{
				tCnsList.m_bLastPack = TRUE;
			}
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CnsList_Notify, &tCnsList, sizeof(TConfCnsInfo));
			tCnsList.m_wNum = 0;
		}
		
		ptNodeUpdate->GetCnsInfo(tCnsList.m_tConfCnsList[tCnsList.m_wNum]);
		tCnsList.m_wNum++;
	}
	
	if (tCnsList.m_wNum > 0)
	{
		tCnsList.m_bLastPack = TRUE;
		UmsSendConfCtrl(tOutHandle, evtp_Conf_CnsList_Notify, &tCnsList, sizeof(TConfCnsInfo));
	}
}

void CUmsConfInst::OnBrdCastMsg( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();

	switch(ptMsg->GetEvent())
	{
	case ev_UmsConfApplySpeaker_Nty:
		{
			TConfEpID tEpID;
			tEpID.m_wConfID = GetInsID();
			tEpID.m_wEpID = curSpeakerID();

			if (GetRollCallMgr()->IsUIRollCallOn())
			{   //点名时，UMS将被点名人当做发言人处理的，但通知到界面的发言人应为原始发言人 
				tEpID.m_wEpID = GetRollCallMgr()->GetBackUpSpeaker();
			}

			NotifyConfCtrlMsgToAllCns(ptMsg->GetEvent(), &tEpID, 
				sizeof(tEpID));
		}
		break;
	case ev_UmsConfAMixUpdate_Nty:
		{
			TConfAuxMixInfo tMixInfo;
			m_pcUmsDiscuss->GetDiscussStateInfo(tMixInfo);
			//本级无讨论会场则不发送
			if ( tMixInfo.m_bStart )
			{
				NotifyConfCtrlMsgToAllCns(ptMsg->GetEvent(), &tMixInfo, 
					sizeof(tMixInfo));
			}
		}
		break;
	case ev_UmsConfMute_Nty:
	case ev_UmsConfQuiet_Nty:
	case ev_UmsAudMixStatus_Nty:
	case ev_UmsConfDualEp_Nty:
		NotifyConfCtrlMsgToAllCns(ptMsg->GetEvent(), ptMsg->GetBody() + sizeof(TUmsHandle), 
				ptMsg->GetBodyLen() - sizeof(TUmsHandle));
		break;
	default:
		break;
	}

	return ;
}

void CUmsConfInst::NotifyConfCtrlMsgToCns( u16 wEvent, u16 wEpID, void* body, u16 bodyLen )
{
	TUmsHandle tOutHandle;

	m_pcNodeMgr->MakeCallerHandle(tOutHandle, wEpID);
	UmsSendConfCtrl(tOutHandle, wEvent, body, bodyLen);

	return ;
}

//广播到CNS的UI类消息，全部从上级调用
void CUmsConfInst::NotifyConfCtrlMsgToAllCns( u16 wEvent, void* body, u16 bodyLen, u16 wExceptEpID )
{	
	TCallNode* ptNode = NULL;
	TCallNode* ptForeFather = NULL;
	BOOL32 bSnd = TRUE;
	TUmsHandle tOutHandle;
	switch(wEvent)
	{
	case ev_UmsConfApplySpeaker_Nty:
	case ev_UmsConfAMixUpdate_Nty:
		//全部通知
		bSnd = TRUE;
		break;
	case ev_UmsConfMute_Nty:
	case ev_UmsConfQuiet_Nty:
	case ev_UmsConfDualEp_Nty:
		{
			//通知所有CNS，以及结点所在的UMS
			TConfEpID* ptEpID = (TConfEpID*)body;
			ptNode = m_pcNodeMgr->GetNode(ptEpID->m_wEpID);
			ptForeFather = m_pcNodeMgr->GetForeFatherNode(ptNode);
			
			if ( NULL == ptNode || NULL == ptForeFather )
			{
				//双流通知无效值，则全部转发
				if ( ptEpID->m_wEpID == TP_INVALID_INDEX && wEvent == ev_UmsConfDualEp_Nty )
				{
					break;
				}

				MdlError(Ums_Mdl_Call, ("NotifyConfCtrlMsgToAllCns ptNode is NULL in ev_UmsConfMute_Nty. ConfID:%d, EpID:%d\n"
					, GetInsID(), ptEpID->m_wEpID));
				return;
			}

			if ( ptNode != ptForeFather )
			{
				ptEpID->m_wEpID = ptNode->m_wLowChildEpID;
				m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptForeFather->m_wEpID);
				UmsSendConfCtrl(tOutHandle, wEvent, body, bodyLen);
			}
			ptEpID->m_wEpID = ptNode->m_wEpID;
			bSnd = FALSE;
		}
		break;
	case ev_UmsAudMixStatus_Nty:
		{
		}
		break;
	default:
		break;
	}

	for (TCallNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
	{
		if ( ptItor->m_wEpID == wExceptEpID )
		{
			continue;
		}

		if ( ptItor->IsUms() && !bSnd )
		{
			continue;
		}

		if (ptItor->IsCallOn())
		{			
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptItor->m_wEpID);
			UmsSendConfCtrl(tOutHandle, wEvent, body, bodyLen);
		}
	}

	return ;
}

u16 CUmsConfInst::NotifyMsgToServiceForUI(u16 wEvent, void* body, u16 bodyLen, TLogUser* ptUser)
{
	TLogUser tLogUser;
	if (NULL == ptUser)
	{
		ptUser = &tLogUser;
	}
	
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(ptUser, sizeof(TLogUser));
	cMsg.CatBody(body, bodyLen);
	
	return cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
}

u16 CUmsConfInst::NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(body, bodyLen);
	return cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, GetInsID()));
}

void CUmsConfInst::SetPollTimeInterval(u16 wTime)	
{
	m_pcPollMgr->SetPollTimeInterval(wTime);
}

TCallNode* CUmsConfInst::GetNode(u16 wEpID)
{
	return m_pcNodeMgr->GetNode(wEpID);
}

void CUmsConfInst::StopConf()
{
	if (inst_idle != CurState())
	{
		m_bIsQuiting = TRUE;

		m_pcDataConf->HungupConf();

		u16 wIndex = 0;
		CNetPortMgr::FreeMediaTrans(this, m_cSpeaker.m_tToVirSpeakerDs);
		CNetPortMgr::FreeMediaTrans(this, m_cSpeaker.m_tInnerVirSpeaker);
		CNetPortMgr::FreeMediaTrans(this, GetBas()->GetSpeakerBas()->m_tDsList);
		
		//增加临时模板取消SIP和GK注册
		if (0 == m_wConfTemplateID)
		{
			m_pcRegMgr->StopTempReg(GetInsID());
			ClearTempConfSeq(GetInsID());

			if (m_tConfBaseInfo.m_tEncrypt.IsQt())
			{
                m_QueryAliasMgr.HungUpConf(m_tConfBaseInfo.m_achConfName);
			}
		}

		TUmsHandle tHandle;
		TCapNode* ptNode = NULL;				
		for (ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
		{
			if ( ptNode->IsChanOn() )
			{
				m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			}
			HungUp(ptNode->m_wEpID, FALSE);
		}

		m_pcTvWallMgr->HungUpConf(this);

		m_pcDual->StopConf();
		m_pcAudMix->OnStopConf();
		m_pcUmsDiscuss->ReleaseDiscuss();
		m_pcRollCallMgr->ReleaseRollCall();
		m_pcPutAudMgr->ReleaseAll(em_putauduser_none);
		m_tGetConfVidAudMgr->OnStopConf();
		m_pcMcuMgr->OnStopConf();

		m_pcVmp->OnStopConf();
		m_pcBas->StopBas();

		DestroyUmsToAllNode();

		CNetPortMgr::DestoryNetBuf(this);

		m_pcGetVidEx->StopConf(GetInsID());

		TCapNode* ptCaller = m_pcNodeMgr->GetCaller();
		if (ptCaller->m_bUsed)
		{
			HungUp(ptCaller->m_wEpID, TRUE, TRUE);
		}

		m_pcNodeMgr->StopConf();	
		m_pcCallMgr->StopConf();
		m_pcPollMgr->StopConf();
#ifdef _USE_XMPUEQP_
		g_atXmpuInitMeeting[GetInsID()-1].m_bInitXmpuMeeting = FALSE;
		ReleaseXmpuMeeting(GetInsID());
#endif

		u16 wConfID = GetInsID();
		if (m_tEqpConfDs.IsValid())
		{
			CTpMsg cMsg;	
			cMsg.SetEvent(ev_media_clear_conf);
			cMsg.SetBody(&wConfID, sizeof(wConfID));
			cMsg.Post(UMS_MEDIATRANS_APP_INST, m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(GetInsID()));

			TMediaParam tEqpMedia;
			tEqpMedia.m_ptEqpRes = &m_tEqpConfDs;
			tEqpMedia.m_emAssignType = TMediaParam::emAssignConf;
			ReleaseEqpEx(&tEqpMedia);
		}

		
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (m_abOnIFrameCheck[wIndex])
			{
				CNetPortMgr::DestroySpeakerToVirSpeakerForIframeCheck(this, wIndex);
				m_abOnIFrameCheck[wIndex] = FALSE;
			}
		}

		if (m_bOnSingleIframeCheck)
		{
			CNetPortMgr::DestroySpeakerToSingleVirSpeakerForIframeCheck(this);
			m_bOnSingleIframeCheck = FALSE; 
		}

		NextState(inst_idle);

		TEqpRes tAdapterEqp[MAX_ADAPTER_MDL_NUM];
		if (GetAllEqpRes(tAdapterEqp, MAX_ADAPTER_MDL_NUM, em_adapter_mdl))
		{
			TUmsHandle	tHandle;
			for (u16 wIndex = 0; wIndex < MAX_ADAPTER_MDL_NUM; ++wIndex)
			{
				tHandle.Clear();
				if (tAdapterEqp[wIndex].IsValid())
				{
					tHandle.m_dwAdapteID  = tAdapterEqp[wIndex].m_dwEqpNode;
					tHandle.MakeAppHandle(GetInsID(), 0);
					UmsClearConference(tHandle);
				}
			}
		}

		for (wIndex = 0; wIndex < UMS_CONF_MAX_DS_NUM; ++wIndex)
		{
			if (m_atDsEqp[wIndex].IsValid())
			{
				CTpMsg cMsg;	
				cMsg.SetEvent(ev_media_clear_conf);
				cMsg.SetBody(&wConfID, sizeof(wConfID));
				cMsg.Post(UMS_MEDIATRANS_APP_INST, m_atDsEqp[wIndex].m_dwEqpNode, UMS_CALL_APP_INST(GetInsID()));
			}

			m_atDsEqp[wIndex].Clear();
		}

		u8 uSndBuf[sizeof(BOOL32)*2] = {0};
		BOOL32 bChairConf = TRUE;
		BOOL32 bReset = TRUE;
		memcpy(uSndBuf, &bChairConf, sizeof(BOOL32));
		memcpy(uSndBuf+sizeof(BOOL32), &bReset, sizeof(BOOL32));
		UmsSendConfCtrl(tHandle, evtp_QtSetConfInfo_Cmd, uSndBuf, sizeof(uSndBuf));
		
		KillTimer(evtp_KeyProtectOnStart_time);
		KillTimer(evtp_CallNode_time);
		KillTimer(evtp_UpdateConfNode_time);

	}

	m_bIsQuiting = FALSE;
	m_wConfTemplateID = TP_INVALID_INDEX;
	m_bIsNeedKeyProtectOnStart = FALSE;

	m_bIsNeedDelayCallNode = FALSE;
	m_bIsAllEpMute = FALSE;
	m_bIsAllEpQuiet = FALSE;

	KillTimer(evtp_EpNodeTimer_Check);
	m_bEpNodeCheck = FALSE;

	for(u8 byIndx = 0; byIndx < TP_MAX_OLD_KEY_NUM; byIndx++)
	{
		m_atMediaKey[byIndx].clear();
	}
	m_wMediaKeyIndx = 0;
	m_bSetMediaKey = FALSE;


	m_tConfBaseInfo.Clear();
	m_tSuperChairCap.Clear();
	m_tSuperInfo.Clear();
	m_tUpdateNodeList.Clear();	
	m_cSpeaker.m_tToVirSpeakerDs.Clear();
	m_cSpeaker.m_tInnerVirSpeaker.Clear();
	m_tSpeakerMediaFmt.Clear();
	if (NULL != m_pcBas)
	{
		m_pcBas->GetSpeakerBas()->m_tDsList.Clear();
	}
	
	m_cBw.StopConf();
	
	SetCurSpeaker(NULL);
	SetChairID(NULL);
	SetOldSpeaker(NULL);

	m_tEqpConfDs.Clear();
	m_tEqpConfNb.Clear();

	if (NULL != m_pcCallMgr)//daemon退出时，此函数为空
	{
		m_pcCallMgr->SetChair(TRUE);
	}
}

void CUmsConfInst::CallAllLocalNode()
{
	ObjHint(("CallAllLocalNode confID:%d, state:%d\n", GetInsID(), CurState()));
	//遍历会场列表并发起呼叫
	TUmsHandle	tHandle;
	tHandle.handPaCall = 0;
	TMakeCallPara tCallPara;

	u16 wCallNum = 0;
	BOOL32 bIsNeedTimeAgain = FALSE;

	if (m_pcNodeMgr->FirstNode() != m_pcNodeMgr->FirstNeedCallNode())
	{//如果当前还需要处理批量呼叫，则呼叫接收后还需要进行一次失败会场的呼叫
		bIsNeedTimeAgain = TRUE;
	}

	BOOL32 bAdapterRet;
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNeedCallNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(ums_UmsConfNodeState_uncall != ptNode->m_emCallState 
			&& ums_UmsConfNodeState_callfailed != ptNode->m_emCallState)
		{
			continue;	
		}

		if (wCallNum >= m_tCallCfg.m_wMaxOnceCall)
		{		
			//进入此循环表示会议开始的呼叫，3秒钟呼叫一次
			KillTimer(evtp_CallNode_time);
			SetTimer(evtp_CallNode_time, TP_INTERVAL_TIME_THREE_SECOND);
			m_pcNodeMgr->SetLastCallNode(ptNode);
			return;
		}		

		if (!ptNode->IsResReady())
		{			
			bAdapterRet = m_pcNodeMgr->AssignNodeRes(ptNode, NULL);
			MdlHint(Ums_Mdl_Call, ("CallAllLocalNode ConfID:%d, EpID:%d, bAdapterRet:%d\n"
				, GetInsID(), ptNode->m_wEpID, bAdapterRet));
			if (!bAdapterRet)
			{
				bIsNeedTimeAgain = TRUE;
				continue;
			}
		}

		wCallNum++;
		ptNode->m_emCallState = ums_UmsConfNodeState_calling;
		
		tCallPara.Clear();
		m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
		m_pcCallMgr->MakeCallInfo(tCallPara, *ptNode, FALSE);		

		UmsMakeCall(tHandle, tCallPara);
	} 

	m_pcNodeMgr->SetLastCallNode(NULL);

	if (bIsNeedTimeAgain)
	{
		KillTimer(evtp_CallNode_time);
 		SetTimer(evtp_CallNode_time, UMS_RECALL_TIME);
	}
}

//检查本会议是否为主叫会议
BOOL32 CUmsConfInst::IsChairConf()
{
	return m_pcCallMgr->IsChair();
}

TCallNode* CUmsConfInst::GetSonNode(const TUmsHandle& tHandle, const TEpKey& tKey)
{
	
	TCallNode* pRootNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (NULL == pRootNode)
	{
		return NULL;
	}	
	
	TCallNode* ptNode = m_pcNodeMgr->GetNodeByChildEpID(pRootNode, tKey.m_wEpID);

	return ptNode;
}

//会场切换发言人的发言坐席
void CUmsConfInst::AdjustCnsInnerSpeak(BOOL32 bMix, u16 wNewSpeakerIndex, u16 wExcEpID)
{
	TCallNode* ptSpeakerNode = m_pcNodeMgr->GetNode(curSpeakerID());
	TCapNode* ptFahterNode = m_pcNodeMgr->GetForeFatherNode(ptSpeakerNode);
	if (NULL == ptSpeakerNode || NULL == ptFahterNode || !ptSpeakerNode->IsChanOn())
	{
		ObjHint(("AdjustCnsInnerSpeak failed. ConfID:%d, speaker:%d\n", GetInsID(), curSpeakerID()));
		return;
	}	

	ObjHint(("AdjustCnsInnerSpeak. ConfID:%d, speaker:%d, index:%d\n", GetInsID(), curSpeakerID(), wNewSpeakerIndex));

	u16 wOldIndex = ptSpeakerNode->m_wSpearkIndex;

	//在切换发言坐席时 要先调整一下发言人到虚拟发言人的码流
	//因为m_tSingleVidDec的码流来源随着发言坐席变更
	ptSpeakerNode->m_wSpearkIndex = wNewSpeakerIndex;
	CNetPortMgr::CreateSpeakerToVirSpeaker(this);


	TUmsHandle tOutHandle;
	TCnsSpeakerAdjust tAdjustInfo;
	tAdjustInfo.m_wSpeakerIndex = wNewSpeakerIndex;

	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}
		
		//在手动调整中，上级UMS就不需要再通知到发言人所在的下级UMS进行调整了（重复操作）。
		//在语音激励中，则需要通知到所有UMS
		if (ptNode->m_wEpID == curSpeakerID() || ( ptNode->m_wEpID == ptFahterNode->m_wEpID && !bMix ) 
			|| ptNode->m_wEpID == wExcEpID)
		{
			continue;
		}

		if (ptNode->IsMtEp() && ptNode->m_wEpID != chairID())
		{
			m_pcNodeFsm->ChangeSpeaker(ptNode);
		}

		if (ptNode->IsUms())
		{
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
			tOutHandle.handPaCall = ptNode->m_dwStackHandle;
			UmsSendConfCtrl(tOutHandle, evtp_Conf_CnsSpeakerCascad_Notify, &tAdjustInfo, sizeof(tAdjustInfo));
		}
	}
	ptSpeakerNode->m_wSpearkIndex = wOldIndex;
}

void CUmsConfInst::AdjustNewSpeakerToAllNode(u16 wEpID, BOOL32 bUpdate)
{
	if (m_bIsQuiting)
	{
		ObjHint(("AdjustNewSpeakerToAllNode Failed. The Conf is quiting! ConfID:%d\n", GetInsID()));
		return;
	}

	ObjHint(("AdjustNewSpeakerToAllNode. ConfID:%d, Speaker:%d, EpID:%d, bUpdate:%d\n", GetInsID(), curSpeakerID(), wEpID, bUpdate));

	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}

		if ( TP_VALID_HANDLE(wEpID) && wEpID != ptNode->m_wEpID )
		{
			continue;
		}

		//所有会场清空一次
		ptNode->m_tRmtChan.ResetFastStatis();

		if( bUpdate )
		{
			m_pcNodeFsm->UpdateMediaTrans(ptNode);
		}
		else
		{
			m_pcNodeFsm->ChangeSpeaker(ptNode);
		}
	}

	TCapNode* ptSpeaker = m_pcNodeMgr->GetForeFatherNode(curSpeakerID());
	if(NULL != ptSpeaker)
	{
		ptSpeaker->m_tRmtChan.ResetFastStatis();
	}
	AskKeyByEpID(curSpeakerID(), EmAskKeySpeaker);
	
	TCapNode* ptCaller = m_pcNodeMgr->GetCaller();
	if (ptCaller->m_bUsed && ptCaller->IsChanOn())
	{
		if( bUpdate )
		{
			m_pcNodeFsm->UpdateMediaTrans(ptCaller);
		}
		else
		{
			m_pcNodeFsm->ChangeSpeaker(ptCaller);
		}
		ptCaller->m_tRmtChan.ResetFastStatis();
	}

	return ;
}

void CUmsConfInst::DestroyUmsToAllNode()
{
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;	
		}				

		CNetPortMgr::DestroyUmsToNode(this, ptNode);
	}

	TCapNode* ptCaller = m_pcNodeMgr->GetCaller();
	if (ptCaller->m_bUsed)
	{
		CNetPortMgr::DestroyUmsToNode(this, ptCaller);
	}
}

BOOL32 CUmsConfInst::IsValidKeyFrameReq(const TFastUpdateStatis& tStatis)
{
	u32 dwInterval = 0;
	u32 dwTimes = 0;

	if ( m_bIsNeedKeyProtectOnStart )
	{
		dwInterval = CUmsConfigEx::GetInstance()->GetBeginFastUpdateInterval();
		dwTimes = CUmsConfigEx::GetInstance()->GetBeginFastUpdateNeglectNum();
	}
	else
	{
		dwInterval = CUmsConfigEx::GetInstance()->GetFastUpdateInterval();
		dwTimes = CUmsConfigEx::GetInstance()->GetFastUpdateNeglectNum();
	}

	if (dwInterval == 0)
	{
		return TRUE;
	}

	return tStatis.CheckValidInterval(dwInterval, dwTimes);
}

//通知下级UMS主席能力 wDstEpID为无效则全部通知
void CUmsConfInst::NotifyChairCapToLowUms( u16 wDstEpID /*= TP_INVALID_INDEX*/ )
{
	TChairInfoTr tChairCap;
	tChairCap.m_wSpeakerIndex = m_tSuperChairCap.m_wSpeakerIndex;

	TUmsHandle tOutHandle;
	for (TCallNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
	{
		if ( wDstEpID != TP_INVALID_INDEX && ptItor->m_wEpID != wDstEpID )
		{
			continue;
		}

		if (ptItor->IsCallOn() && ptItor->IsUms())
		{				
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptItor->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_ChairCap_Notify, &tChairCap, sizeof(tChairCap));
		}
	}

	return ;
}

TChairCap CUmsConfInst::GetChairCap()
{
	TChairCap tChair;
	if ( IsChairConf() )
	{
		TCallNode* ptChair = m_pcNodeMgr->GetNode(chairID());
		if ( NULL == ptChair || !ptChair->IsChanOn() )
		{
			MdlHint(Ums_Mdl_Call, ("GetChairCap. Chair Off! ConfID:%d\n", GetInsID()));
		}
		else
		{
			tChair.m_tChair.SetAlias(ptChair->m_tConfName.m_abyAlias);
			tChair.m_wSpeakerIndex = ptChair->GetSpeaker();
			tChair.m_wChairAudSndCap = ptChair->m_wAudSndNum;
			tChair.m_wChairVidSndCap = ptChair->m_wVidSndNum;
		}
	}
	else
	{
		if ( m_tSuperInfo.m_wConfID == TP_INVALID_INDEX )
		{
			TCallNode* ptCaller = m_pcNodeMgr->GetNode(CALLER_EP_INDEX);
			if ( NULL != ptCaller && ptCaller->IsChanOn() )
			{
				tChair.m_tChair.SetAlias(ptCaller->m_tConfName.m_abyAlias);
				tChair.m_wSpeakerIndex = ptCaller->GetSpeaker();
				tChair.m_wChairAudSndCap = ptCaller->m_wAudSndNum;
				tChair.m_wChairVidSndCap = ptCaller->m_wVidSndNum;
			}
		}
		else
		{
			tChair.m_tChair.SetAlias(m_tSuperInfo.m_tChair.m_abyAlias);
			tChair.m_wSpeakerIndex = m_tSuperChairCap.GetSpeaker();
			tChair.m_wChairAudSndCap = m_tSuperInfo.m_wChairAudSndCap;
			tChair.m_wChairVidSndCap = m_tSuperInfo.m_wChairVidSndCap;
		}
	}

	return tChair;
}

void CUmsConfInst::GetConfNtfyInfo(TTPConfInfoNtfy& tInfo, TChairConfInfo& tChair)
{	
	tInfo.m_wConfID = GetInsID();

	if (IsChairConf())
	{
		tInfo.m_tConf.SetAlias(m_tConfBaseInfo.m_achConfName);
		
		TCallNode* ptTmpNode = m_pcNodeMgr->GetCapsetNode(chairID());
		if (NULL != ptTmpNode && ptTmpNode->IsCallOn())
		{
			tInfo.m_tChair.SetAlias(ptTmpNode->m_tConfName.m_abyAlias);			
			tInfo.m_wChairVidSndCap = ptTmpNode->m_wVidSndNum;
			tInfo.m_wChairAudSndCap = ptTmpNode->m_wAudSndNum;
			tChair.m_tChairName.SetAlias(ptTmpNode->m_tConfName.m_abyAlias);
		}
		
		tChair.m_wConfID = GetInsID();
		tChair.m_tBeginTime = time(NULL) - m_tConfBaseInfo.m_tStartTime;
		tChair.m_tConfName.SetAlias(m_tConfBaseInfo.m_achConfName);
		
		ptTmpNode = m_pcNodeMgr->GetNode(curSpeakerID());
		if (NULL != ptTmpNode && ptTmpNode->IsCallOn())
		{ 
			tInfo.m_tSpeak.SetAlias(ptTmpNode->m_tConfName.m_abyAlias);
			tInfo.m_bSpeakOnline = TRUE;
		}
		else
		{
			tInfo.m_bSpeakOnline = FALSE;
		}
		
		tInfo.m_tBeginTime = time(NULL) - m_tConfBaseInfo.m_tStartTime;
		tInfo.m_bMixMotive = FALSE;
	}
	else
	{
		tInfo = m_tSuperInfo;
		tInfo.m_tBeginTime = time(NULL) - m_tConfBaseInfo.m_tStartTime;
	}
	
	return ;
}

BOOL32 CUmsConfInst::IsPriNeedBas()
{
	return m_pcBas->GetPriFmtNum() > 1;
}

BOOL32 CUmsConfInst::IsDualNeedBas()
{
	return m_pcBas->GetDualFmtNum() > 1;
}

void CUmsConfInst::OnMuteEpFromUmc( CTpMsg *const ptMsg )
{
	TConfEpID* ptConfEp = (TConfEpID*)(ptMsg->GetBody());
	BOOL32 bIsMute = *(BOOL32*)(ptMsg->GetBody() + sizeof(TConfEpID));

	ObjHint(("OnMuteEpFromUmc ConfID:%d, EpID:%d, bIsMute:%d\n", GetInsID(), ptConfEp->m_wEpID, bIsMute));
	if (ptConfEp->m_wEpID == TP_ALLEP_INDEX)
	{
		if (IsChairConf())
		{
			OnAllMuteEpForUmcCnc(ptConfEp,bIsMute);
		}
	}
	else
	{
		OnMuteEpForUmcCnc(ptConfEp, bIsMute);
	}

}

void CUmsConfInst::OnQuietEpFromUmc( CTpMsg *const ptMsg )
{
	TConfEpID* ptConfEp = (TConfEpID*)(ptMsg->GetBody());
	BOOL32 bIsQuiet = *(BOOL32*)(ptMsg->GetBody() + sizeof(TConfEpID));
	
	ObjHint(("OnQuietEpFromUmc ConfID:%d, EpID:%d, bIsQuiet:%d\n", GetInsID(), ptConfEp->m_wEpID, bIsQuiet));
	if (ptConfEp->m_wEpID == TP_ALLEP_INDEX)
	{
		if (IsChairConf())
		{
			OnAllQuietEpForUmcCnc(ptConfEp, bIsQuiet);
		}
	}
	else
	{
		OnQuietEpForUmcCnc(ptConfEp, bIsQuiet);
	}
		
}

void CUmsConfInst::OnChangeSpeakerFromUmc( CTpMsg *const ptMsg )
{
	TLogUser* ptLogUser = (TLogUser*)(ptMsg->GetBody());
	TConfEpID* ptConfEp = (TConfEpID*)(ptMsg->GetBody() + sizeof(TLogUser));
	u16 wEpID = ptConfEp->m_wEpID;
		
	TCallNode* ptNode = m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = m_pcNodeMgr->GetForeFatherNode(ptNode);
	
	if (ptNode && ptFartherNode && ptFartherNode != ptNode && ptFartherNode->IsMcu())
	{
		OnChangeMcuEpSpeakerFromUmc(ptLogUser, ptConfEp);
		return ;
	}
	EmTpApplySpeakerRet emRet = TP_ApplySpeaker_Success;
	do 
	{

		if (!IsChairConf())
		{
			ObjError(("OnChangeSpeakerFromUmc ep not chair conf! wConfID:%d, EpID:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_ConfUnExist;
			break;
		}

		if (NULL == ptNode)
		{
			ObjError(("OnChangeSpeakerFromUmc ep Index error.wConfID:%d, EpID:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}
		
		if (!ptNode->IsMtEp() || !ptNode->IsCallOn() || !ptNode->IsChanOn() || !ptNode->IsVidSndValid())
		{
			ObjError(("OnChangeSpeakerFromUmc ep state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), wEpID, UmsNodeConfType(ptNode->m_emCallState), ptNode->m_bChannelOpen));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}

		if (ptNode->IsMcu())
		{ // 指定MCU 为发言人(应指定MCU下某一个会场为发言人,简单级联mcu 的类型是emTPEndpointH323SingleMCU)
			ObjError(("OnChangeSpeakerFromUmc ep error,  speaker is mcu! .wConfID:%d, EpID:%d\n", GetInsID(), wEpID));
            emRet = TP_ApplySpeaker_EpStateError;
			break;
		}
		
		if (wEpID == curSpeakerID())
		{
			ObjError(("OnChangeSpeakerFromUmc ep not changer.wConfID:%d, EpID:%d, curspeaker:%d\n", GetInsID(), wEpID, curSpeakerID()));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}


		if (m_pcUmsDiscuss->IsUIDiscussOn())
		{
			TDiscussEpInfo* ptEpInfo = m_pcUmsDiscuss->GetDiscussEpInfoById(wEpID);
			if (NULL == ptEpInfo || !ptEpInfo->IsValid())
			{
				ObjError(("OnChangeSpeakerFromUmc Now it is Dicuss modle, ep is not vaild In discuss. ConfId:%d, epId:%d\n", GetInsID(), wEpID));
				emRet = TP_ApplySpeaker_EpIDError;
				break;
			}
		}


		if (GetRollCallMgr()->IsUIRollCallOn())
		{
			ObjError(("OnChangeSpeakerFromUmc Now it is rollcallmode modle, ConfId:%d, epId:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}

	} while (0);
	
	ObjHint(("OnChangeSpeakerFromUmc ConfID:%d, old Speaker:%d, new Speaker:%d, ret:%d\n", GetInsID(), curSpeakerID(), wEpID, emRet));
	

	
	u8 byBuf[sizeof(TLogUser) + sizeof(TConfEpID) + sizeof(EmTpApplySpeakerRet)] = {0};
	memcpy(byBuf, ptLogUser, sizeof(TLogUser));
	memcpy(byBuf + sizeof(TLogUser), ptConfEp, sizeof(TConfEpID));
	memcpy(byBuf + sizeof(TLogUser) + sizeof(TConfEpID), &emRet, sizeof(EmTpApplySpeakerRet));
	
	// 回应umc
	NotifyMsgToService(evtp_ApplySpeaker_result, byBuf, sizeof(byBuf));
	

	if (TP_ApplySpeaker_Success == emRet)
	{
		if (m_pcUmsDiscuss->IsUIDiscussOn())
		{// 里面会调changspeaker
			m_pcUmsDiscuss->OnChangerSpeaker(ptNode);
		}
		else
		{
			ChangeSpeaker(wEpID, NULL);
			AdjustNewSpeakerToAllNode();
			AdjustNewSpeakerToAllMcuNode();
			NotifyApplySpeakerToUI();
		}
	}

	return;
}

BOOL32 CUmsConfInst::OnAllMuteEpForUmcCnc(TConfEpID* ptConfEp, BOOL32 bIsMute)
{
	u16 wIndex = 0;
	u16 awChildEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpChildNum = 0;
	TCallNode* ptChildNode = NULL;
	TMuteRmtEpCmd tRmtEp;
	tRmtEp.m_bMute = bIsMute;
	TUmsHandle tOutHandle;
	
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		TCapNode* ptFarther = m_pcNodeMgr->GetForeFatherNode(ptNode);
		if (NULL == ptNode || NULL == ptFarther)
		{
			continue;
		}
		
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}
		
		
		if (ptNode->IsUms())
		{
			
			tRmtEp.m_wEpID = TP_ALLEP_INDEX;
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_MuteRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
		}
		
		else if (ptNode->IsMtEp() && ptNode->m_bMute != bIsMute)
		{
			
			tRmtEp.m_wEpID = ptNode->m_wEpID;
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_MuteRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
		}
		else
		{
			// to do..
			ObjHint(("OnAllMuteEpForUmcCnc ConfID:%d, EpID:%d, bIsMute:%d ", GetInsID(), ptNode->m_wEpID, bIsMute))
		}	
	}
	m_bIsAllEpMute = bIsMute;
	u16 wConfID = GetInsID();
	// 通知umc全局静音哑音状态
	s8 szBuf[sizeof(u16) + sizeof(BOOL32)+ sizeof(BOOL32)] = {0};
	memcpy(szBuf, &wConfID, sizeof(u16));
	memcpy(szBuf+sizeof(u16), &m_bIsAllEpQuiet, sizeof(BOOL32));
	memcpy(szBuf+sizeof(u16)+sizeof(BOOL32), &m_bIsAllEpMute, sizeof(BOOL32));
	//MdlHint(Ums_Mdl_Service, ("EventQuietMuteStatusNotify, confID:%d, QuietBool:%d, MuteBool:%d\n", wConfID, m_bIsAllEpQuiet, m_bIsAllEpMute ) );
	NotifyMsgToService(evtp_ConfAllEpQuietMuteStatus_Nty, szBuf, sizeof(u16) + sizeof(BOOL32)+sizeof(BOOL32));

	// 通知主席
	if (IsChairConf())
	{
		// 通知主席全场静音哑音状态
		TConfEpID tConfEp;
		tConfEp.m_wConfID = GetInsID();
		tConfEp.m_wEpID = TP_ALLEP_INDEX;
		
		s8 szBuf[sizeof(TConfEpID) + sizeof(BOOL)] = {0};
		memcpy(szBuf, &tConfEp, sizeof(tConfEp));
		memcpy(szBuf+sizeof(tConfEp), &m_bIsAllEpMute, sizeof(BOOL));
		NotifyConfCtrlMsgToCns(ev_UmsConfMute_Nty, chairID(), szBuf, sizeof(szBuf));	
	}
	
	return TRUE;

}

BOOL32 CUmsConfInst::OnMuteEpForUmcCnc(TConfEpID* ptConfEp, BOOL32 bIsMute)
{
	TCallNode* ptNode = m_pcNodeMgr->GetNode(ptConfEp->m_wEpID);
	TCapNode* ptFarther = m_pcNodeMgr->GetForeFatherNode(ptNode);
	
	if (NULL == ptNode || NULL == ptFarther)
	{
		ObjError(("OnMuteEpForUmcCnc ep Index error. ConfID:%d, EpID:%d\n", GetInsID(), ptConfEp->m_wEpID));
		return FALSE;
	}

	if (!ptNode->IsCallOn() || !ptNode->IsChanOn())
	{
		ObjError(("OnMuteEpForUmcCnc ep state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), ptConfEp->m_wEpID, UmsNodeConfType(ptNode->m_emCallState), ptNode->m_bChannelOpen));
		return FALSE;
	}
	
	if (!ptNode->IsMtEp())
	{
		ObjError(("OnMuteEpForUmcCnc ep type error. ConfID:%d, epID:%d\n", GetInsID(), ptConfEp->m_wEpID));
		return FALSE;
	}
	
	ObjHint(("OnMuteEpForUmcCnc ConfID:%d, EpID:%d, bIsMute:%d, OldState:%d\n", GetInsID(), ptConfEp->m_wEpID, bIsMute, ptNode->m_bMute));
	
	if (ptNode->m_bMute == bIsMute)
	{
		return FALSE;
	}
	
	TMuteRmtEpCmd tRmtEp;
	if (ptNode == ptFarther)
	{//本级中，将真实ID传出
		tRmtEp.m_wEpID = ptNode->m_wEpID;
	}
	else
	{//下级中，将下级ID传出
		tRmtEp.m_wEpID = ptNode->m_wLowChildEpID;
	}
	tRmtEp.m_bMute = bIsMute;
	
	TUmsHandle tOutHandle;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
	UmsSendConfCtrl(tOutHandle, evtp_Conf_MuteRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
	return TRUE;
}

BOOL32 CUmsConfInst::OnAllQuietEpForUmcCnc( TConfEpID* ptConfEp, BOOL32 bIsQuiet )
{
	u16 wIndex = 0;
	u16 awChildEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpChildNum = 0;
	TCallNode* ptChildNode = NULL;
	TQuietRmtEpCmd tRmtEp;
	tRmtEp.m_bQuiet = bIsQuiet;
	TUmsHandle tOutHandle;
	
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		TCapNode* ptFarther = m_pcNodeMgr->GetForeFatherNode(ptNode);
		if (NULL == ptNode || NULL == ptFarther)
		{
			continue;
		}
		
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}
		
		if (ptNode->IsUms())
		{
			
			tRmtEp.m_wEpID = TP_ALLEP_INDEX;
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_QuietRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
			
		}
		else if (ptNode->IsMtEp() && ptNode->m_bQuiet != bIsQuiet)
		{
			tRmtEp.m_wEpID = ptNode->m_wEpID;
			m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_QuietRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
		}
		else
		{
			// to do.... 
			ObjHint(("OnAllQuietEpForUmcCnc ConfID:%d, EpID:%d, bIsQuiet:%d ", GetInsID(), ptNode->m_wEpID, bIsQuiet));
		}
		
	}
	m_bIsAllEpQuiet = bIsQuiet;
	u16 wConfID = GetInsID();
	// 通知umc全局静音哑音状态
	s8 szBuf[sizeof(u16) + sizeof(BOOL32)+ sizeof(BOOL32)] = {0};
	memcpy(szBuf, &wConfID, sizeof(u16));
	memcpy(szBuf+sizeof(u16), &m_bIsAllEpQuiet, sizeof(BOOL32));
	memcpy(szBuf+sizeof(u16)+sizeof(BOOL32), &m_bIsAllEpMute, sizeof(BOOL32));
	//MdlHint(Ums_Mdl_Service, ("EventQuietMuteStatusNotify, confID:%d, QuietBool:%d, MuteBool:%d\n", wConfID, m_bIsAllEpQuiet, m_bIsAllEpMute ) );
	NotifyMsgToService(evtp_ConfAllEpQuietMuteStatus_Nty, szBuf, sizeof(u16) + sizeof(BOOL32)+sizeof(BOOL32));
	
	// 通知主席
	if (IsChairConf())
	{
		// 通知主席全局静音哑音状态
		TConfEpID tConfEp;
		tConfEp.m_wConfID = GetInsID();
		tConfEp.m_wEpID = TP_ALLEP_INDEX;
		
		s8 szBuf[sizeof(TConfEpID) + sizeof(BOOL)] = {0};
		memcpy(szBuf, &tConfEp, sizeof(tConfEp));
		memcpy(szBuf+sizeof(tConfEp), &m_bIsAllEpQuiet, sizeof(BOOL));
		NotifyConfCtrlMsgToCns(ev_UmsConfQuiet_Nty, chairID(), szBuf, sizeof(szBuf));	
	}
	return TRUE;
	
}

BOOL32 CUmsConfInst::OnQuietEpForUmcCnc( TConfEpID* ptConfEp, BOOL32 bIsQuiet )
{
	TCallNode* ptNode = m_pcNodeMgr->GetNode(ptConfEp->m_wEpID);
	TCapNode* ptFarther = m_pcNodeMgr->GetForeFatherNode(ptNode);
	
	if (NULL == ptNode || NULL == ptFarther)
	{
		ObjError(("OnQuietEpForUmcCnc ep Index error. ConfID:%d, EpID:%d\n", GetInsID(), ptConfEp->m_wEpID));
		return FALSE;
	}
	
	if (!ptNode->IsCallOn() || !ptNode->IsChanOn())
	{
		ObjError(("OnQuietEpForUmcCnc ep state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), ptConfEp->m_wEpID, UmsNodeConfType(ptNode->m_emCallState), ptNode->m_bChannelOpen));
		return FALSE;
	}
	
	if (!ptNode->IsMtEp())
	{
		ObjError(("OnQuietEpForUmcCnc ep type error. ConfID:%d, epID:%d\n", GetInsID(), ptConfEp->m_wEpID));
		return FALSE;
	}

	ObjHint(("OnQuietEpForUmcCnc ConfID:%d, EpID:%d, bIsQuiet:%d, OldState:%d\n", GetInsID(), ptConfEp->m_wEpID, bIsQuiet, ptNode->m_bQuiet));
	
	if (ptNode->m_bQuiet == bIsQuiet)
	{
		return FALSE;
	}
	
	TQuietRmtEpCmd tRmtEp;
	if (ptNode == ptFarther)
	{//本级中，将真实ID传出
		tRmtEp.m_wEpID = ptNode->m_wEpID;
	}
	else
	{//下级中，将下级ID传出
		tRmtEp.m_wEpID = ptNode->m_wLowChildEpID;
	}
	tRmtEp.m_bQuiet = bIsQuiet;
	
	TUmsHandle tOutHandle;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
	UmsSendConfCtrl(tOutHandle, evtp_Conf_QuietRemoteEp_Cmd, &tRmtEp, sizeof(tRmtEp));
	return TRUE;
}

void CUmsConfInst::CheckMidChanInfo(TCapNode* ptNode, TUmsNodeCapset& tNodeCapInfo)
{

	u16 wIndex = 0;
	if (1 == tNodeCapInfo.m_wVidDecNum)
	{

		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{

			if (tNodeCapInfo.m_atVidDec[wIndex].m_bIsChanOn)
			{
				break;
			}
		}
		if (1 != wIndex)
		{

			TTPTransAddr tTempAddr;
			tTempAddr = ptNode->m_aptChanAddr[1]->m_tVid.m_tRtcpForSnd;
			ptNode->m_aptChanAddr[1]->m_tVid.m_tRtcpForSnd = ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForSnd;
			ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForSnd = tTempAddr;

			tNodeCapInfo.m_atVidDec[1].Clear();
			memcpy(&tNodeCapInfo.m_atVidDec[1], &tNodeCapInfo.m_atVidDec[wIndex], sizeof(TChanNetPara));
			tNodeCapInfo.m_atVidDec[wIndex].Clear();
			ObjHint(("CheckMidChanInfo VidDec MidChan is error, modify it! ConfId:%d, EpId:%d\n", GetInsID(), ptNode->m_wEpID));
		}
	}

	if (1 == tNodeCapInfo.m_wVidEncNum)
	{

		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{

			if (tNodeCapInfo.m_atVidEnc[wIndex].m_bIsChanOn)
			{
				break;
			}
		}
		if (1 != wIndex)
		{

			TTPTransAddr tTempAddr;
			tTempAddr = ptNode->m_aptChanAddr[1]->m_tVid.m_tRtpAddr;
			ptNode->m_aptChanAddr[1]->m_tVid.m_tRtpAddr = ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtpAddr;
			ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtpAddr = tTempAddr;

			tNodeCapInfo.m_atVidEnc[1].Clear();
			memcpy(&tNodeCapInfo.m_atVidEnc[1], &tNodeCapInfo.m_atVidEnc[wIndex], sizeof(TChanNetPara));
			tNodeCapInfo.m_atVidEnc[wIndex].Clear();
			ObjHint(("CheckMidChanInfo VidEnc MidChan is error, modify it! ConfId:%d, EpId:%d\n", GetInsID(), ptNode->m_wEpID));
		}
	}

	if (1 == tNodeCapInfo.m_wAudDecNum)
	{
		
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			
			if (tNodeCapInfo.m_atAudDec[wIndex].m_bIsChanOn)
			{
				break;
			}
		}
		if (1 != wIndex)
		{
			
			TTPTransAddr tTempAddr;
			tTempAddr = ptNode->m_aptChanAddr[1]->m_tAud.m_tRtcpForSnd;
			ptNode->m_aptChanAddr[1]->m_tAud.m_tRtcpForSnd = ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForSnd;
			ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForSnd = tTempAddr;

			tNodeCapInfo.m_atAudDec[1].Clear();
			memcpy(&tNodeCapInfo.m_atAudDec[1], &tNodeCapInfo.m_atAudDec[wIndex], sizeof(TChanNetPara));
			tNodeCapInfo.m_atAudDec[wIndex].Clear();
			ObjHint(("CheckMidChanInfo AudDec MidChan is error, modify it! ConfId:%d, EpId:%d\n", GetInsID(), ptNode->m_wEpID));
		}
	}

	if (1 == tNodeCapInfo.m_wAudEncNum)
	{
		
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			
			if (tNodeCapInfo.m_atAudEnc[wIndex].m_bIsChanOn)
			{
				break;
			}
		}
		if (1 != wIndex)
		{
			
			TTPTransAddr tTempAddr;
			tTempAddr = ptNode->m_aptChanAddr[1]->m_tAud.m_tRtpAddr;
			ptNode->m_aptChanAddr[1]->m_tAud.m_tRtpAddr = ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtpAddr;
			ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtpAddr = tTempAddr;

			tNodeCapInfo.m_atAudEnc[1].Clear();
			memcpy(&tNodeCapInfo.m_atAudEnc[1], &tNodeCapInfo.m_atAudEnc[wIndex], sizeof(TChanNetPara));
			tNodeCapInfo.m_atAudEnc[wIndex].Clear();
			ObjHint(("CheckMidChanInfo AudEnc MidChan is error, modify it! ConfId:%d, EpId:%d\n", GetInsID(), ptNode->m_wEpID));
		}
	}

}

void CUmsConfInst::CreateMediaToVRS_2S( TCapNode* ptNode )
{
	if ( !ptNode->IsVRS() || !ptNode->IsVidRcvValid())
	{
		return ;
	}

	TCapNode* ptItor = NULL;
	for ( ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
	{
		if ( !ptItor->IsCallOn() || !ptItor->IsChanOn() )
		{
			continue;
		}

		if ( ptItor->IsVRS() )
		{

			continue;
		}

		if ( ptItor->m_tRmtChan.m_atVidEnc[MIDSCREENINDEX].m_tFlowCtrl.IsNoneFlow())
		{
			continue;
		}

		if ( ptItor->IsThreeAudSnd() && ptItor->IsThreeVidSnd() )
		{
			CNetPortMgr::CreateMediaForVRS2S(this, ptNode, ptItor);

			AskKeyByEpID(ptItor->m_wEpID, EmAskKeyChair);
			
			OspDelay(500);

			break;
		}
	}

	ObjHint(("CreateMediaToVRS_2S ConfID:%d, VrsEpID:%d\n", GetInsID(), ptNode->m_wEpID));

	return ;
}

void CUmsConfInst::NotifyApplySpeakerToUI()
{
	//通知CNS发言人变更
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = GetInsID();
	tConfEpID.m_wEpID = curSpeakerID();

	if (GetRollCallMgr()->IsUIRollCallOn())
	{   //点名时，UMS将被点名人当做发言人处理的，但通知到界面的发言人应为原始发言人 
        tConfEpID.m_wEpID = GetRollCallMgr()->GetBackUpSpeaker();
	}


	NotifyConfCtrlMsgToAllCns(ev_UmsConfApplySpeaker_Nty, &tConfEpID, sizeof(TConfEpID));
	//umc
	NotifyMsgToService(evtp_SpeakerChange_Notify, &tConfEpID, sizeof(TConfEpID));
}

void CUmsConfInst::SetSpeakerCheckFrame( TCallNode* ptNewSpeaker, TCallNode* ptOldSpeaker )
{
	TCapNode* ptNewFather = m_pcNodeMgr->GetForeFatherNode(ptNewSpeaker);
	TCapNode* ptOldFather = m_pcNodeMgr->GetForeFatherNode(ptOldSpeaker);
	
	u16 wNewSpeakerIndex = TP_INVALID_INDEX;
	u16 wOldSpeakerIndex = TP_INVALID_INDEX;
	if ( ptOldSpeaker != NULL )
	{
		if ( ptOldSpeaker->IsChanOn() )
		{
			wOldSpeakerIndex = ptOldSpeaker->GetSpeaker();
		}
	}

	wNewSpeakerIndex = ptNewSpeaker->GetSpeaker();
	
	u16 wIndex;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (m_abOnIFrameCheck[wIndex])
		{
			CNetPortMgr::DestroySpeakerToVirSpeakerForIframeCheck(this, wIndex);
			m_abOnIFrameCheck[wIndex] = FALSE;
		}
	}
	
	if (m_bOnSingleIframeCheck)
	{
		CNetPortMgr::DestroySpeakerToSingleVirSpeakerForIframeCheck(this);
		m_bOnSingleIframeCheck = FALSE;
	}
	
	u16 wOldSndNum = ptOldSpeaker == NULL ? 0 : ptOldSpeaker->m_wVidSndNum;
	u16 wNewSndNum = ptNewSpeaker == NULL ? 0 : ptNewSpeaker->m_wVidSndNum;
	u16 wMidIndex = MIDSCREENINDEX;
	
	if (wNewSndNum > 0 && ptNewFather != ptOldFather)
	{//三屏验证哪些需要进行关键帧检测
		BOOL32 bDelay = FALSE;
		s32 symbolflag = 1; 
		u16 wTempNum = 0;
		u16 wChanIndex = 0;
		for (u16 wIndex = 1; wIndex <= TP_MAX_STREAMNUM; ++wIndex, symbolflag *= -1)
		{		
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;
			
			wTempNum++;

			if(	GetVmp()->IsBrdVmp() && wChanIndex == MIDSCREENINDEX )
			{//中间屏为广播合成 不要检测， 一旦检测，则通过虚拟发言人出去的码流，只有老的发言人码流，合成也被丢掉
				continue;
			}

			if (wNewSndNum >= wTempNum && wOldSndNum >= wTempNum)
			{
				m_abOnIFrameCheck[wChanIndex] = TRUE;
				if (!CNetPortMgr::CreateSpeakerToVirSpeakerForIframeCheck(this, ptOldSpeaker, ptNewSpeaker, wChanIndex))
				{
					m_abOnIFrameCheck[wChanIndex] = FALSE;
				}
				else
				{
					bDelay = TRUE;
				}
			}
		}
		
		if (wOldSpeakerIndex != TP_INVALID_INDEX && !GetVmp()->IsBrdVmp()&& !GetVmp()->IsSpeakerInVmp())//广播合成不要检测
		{//三屏验证哪些需要进行关键帧检测
			m_bOnSingleIframeCheck = TRUE;
			if (!CNetPortMgr::CreateSpeakerToSingleVirSpeakerForIframeCheck(this, ptOldSpeaker, wOldSpeakerIndex, ptNewSpeaker, wNewSpeakerIndex))
			{
				m_bOnSingleIframeCheck = FALSE;
			}
			else
			{
				bDelay = TRUE;
			}
		}
		
		if ( ptNewFather != NULL && ptNewFather->m_tMediaEqp.m_dwEqpNode != m_tEqpConfDs.m_dwEqpNode && bDelay )
		{//此时 新发言人不在会议转发板 可能有检测漏包的情况
			OspDelay(20);
		}
	}

	return ;
}

void CUmsConfInst::GetVidFailedCB( CUmsConfInst* pcConf, u16 wIndex, EmGetVidType emType, EmGetVidRet emRet )
{
	if ( wIndex >= TP_UMS_MAX_CALLNUM || NULL == pcConf )
	{
		MdlHint(Ums_Mdl_Call, ("GetVidFailedCB Index:%d, VidType:%d, Ret:%d\n", wIndex, emType, emRet));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("GetVidFailedCB ConfID:%d, Index:%d, VidType:%d\n",pcConf->GetInsID(), wIndex, emType));

	if ( emType == em_GetVid_View || emType == em_GetVid_ViewEp )
	{
		pcConf->GetSelMgr()->AdjustGetVidFailed(pcConf, wIndex, emRet);
	}
	else
	{
		pcConf->GetVmp()->AdjustGetVidFailed(pcConf, wIndex);
		m_pcTvWallMgr->AdjustGetVidFailed(pcConf, wIndex);
		pcConf->GetUmsDiscuss()->AdjustGetVidFailed(wIndex);
	}

	return ;
}

BOOL32 CUmsConfInst::TryAssignVirSingleBas()
{
	if (!IsPriNeedBas() || NULL != GetSpeaker().m_pcSingleBas)
	{
		return TRUE;
	}
	if(!GetBas()->AssignScreenBas(GetSpeaker().m_pcSingleBas, FALSE))
	{//申请广播类
		return FALSE;
	}
	
	GetSpeaker().m_pcSingleBas->SetCB(VirSingleBasCB, this);

	TryAdjustVirSingleBas();
	
	CNetPortMgr::CreateVirSpeakerToBas(this);

	return TRUE;
}

void CUmsConfInst::TryAdjustVirSingleBas()
{
	if (!IsPriNeedBas() || NULL == GetSpeaker().m_pcSingleBas)
	{
		return ;
	}

	TCallNode* ptNode = NULL;

	if (!IsChairConf() && GetUmsDiscuss()->IsDiscussModle())
	{// 下级进入讨论模式，这个适配始终按主席是发言人处理
		ptNode = GetNodeMgr()->GetNode(chairID());
		if ( NULL != ptNode && ptNode->IsChanOn() && ptNode->IsThreeVidSnd() )
		{
			GetBas()->AdjustScreenBas(GetSpeaker().m_pcSingleBas, chairID(), ptNode->GetSpeaker());
		}
		return;
	}

	if(!IsChairConf() && GetRollCallMgr()->IsRollCallModle())
	{// 下级进入点名，这个适配按主席是发言人处理
        ptNode = GetNodeMgr()->GetNode(chairID());
		if ( NULL != ptNode && ptNode->IsChanOn() && ptNode->IsThreeVidSnd() )
		{
			GetBas()->AdjustScreenBas(GetSpeaker().m_pcSingleBas, chairID(), ptNode->GetSpeaker());
		}
		return;
	}

	ptNode = GetNodeMgr()->GetNode(curSpeakerID()); 
	if (NULL != ptNode && ptNode->IsChanOn() && ptNode->IsThreeVidSnd() )
	{
		GetBas()->AdjustScreenBas(GetSpeaker().m_pcSingleBas, curSpeakerID(), ptNode->GetSpeaker());
	}
	else
	{
		ptNode = GetNodeMgr()->GetNode(chairID());
		if ( NULL != ptNode && ptNode->IsChanOn() && ptNode->IsThreeVidSnd() )
		{
			GetBas()->AdjustScreenBas(GetSpeaker().m_pcSingleBas, chairID(), ptNode->GetSpeaker());
		}
	}

	return ;
}

void CUmsConfInst::TryReleaseVirSingleBas()
{
	if (!IsPriNeedBas() || NULL == GetSpeaker().m_pcSingleBas)
	{
		return ;
	}

	if ( m_pcVmp->IsSpeakerInVmp() || GetUmsDiscuss()->IsDiscussModle() )
	{
		return ;
	}

	GetBas()->ReleaseScreenBas(GetSpeaker().m_pcSingleBas);
	GetSpeaker().m_pcSingleBas = NULL;

	if (!m_bIsQuiting)
	{
		CNetPortMgr::CreateVirSpeakerToBas(this);
	}

	return ;
}

void CUmsConfInst::ShowConfMgr()
{
	msgprintnotime("[ShowConfMgr]\n");
	u16 wIndex;
	for (wIndex = 0; wIndex < TP_CONF_MAX_EPNUM; wIndex++)
	{
		TTPConfEpParam* ptParm = &m_tConfEpInfoMrg.m_ConfEpParam[wIndex];

		if (ptParm->IsUsed())
		{
			msgprintnotime("  [%d] ConfID:%d, TimeID:%d, src:%s, dst:%s.\n", wIndex, ptParm->m_wConfID, ptParm->m_dwTimerID, 
				ptParm->m_tCallInfo.m_tSrcAddr.GetValidAlias().m_abyAlias, ptParm->m_tCallInfo.m_tDestAddr.GetValidAlias().m_abyAlias);

		}
	}

	for (wIndex = 0; wIndex < MAX_CONF_MEDIA_NUM; wIndex++)
	{
		TIpmaskinfo* ptIpMask = &m_tMediaNetWorkManger.m_atInfo[wIndex];
		
		if (m_tMediaNetWorkManger.m_abVaild[wIndex])
		{
			msgprintnotime("DaemonConfMediaReg. Ipa:"TPIPFORMAT", maska:"TPIPFORMAT", ipb:"TPIPFORMAT", maskb:"TPIPFORMAT", localOutIP:"TPIPFORMAT".\n", 
				Tpu32ToIP(ptIpMask->m_dwIpa), Tpu32ToIP(ptIpMask->m_dwMaska), Tpu32ToIP(ptIpMask->m_dwIpb), Tpu32ToIP(ptIpMask->m_dwMaskb), Tpu32ToIP(ptIpMask->m_dwOutIp) );
		}
	}

	for (wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; wIndex++)
	{
		TIpmaskinfo* ptIpMask = &m_tMediaNetWorkManger.m_atInfo[wIndex];

		if (m_tXmpuVmpManger.m_aemStat[wIndex] != VmpManger_Idle)
		{
			msgprintnotime("DaemonConfMediaReg. dwVmpID:%d, emVmpStat:%d.\n", 
							m_tXmpuVmpManger.m_adwVmpID[wIndex], m_tXmpuVmpManger.m_aemStat[wIndex]);
		}
	}
#ifdef _USE_XMPUEQP_
	for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		TXmpuInitMeetingConfInfo* pInfo = &g_atXmpuInitMeeting[wIndex];
		if (pInfo->m_bInitXmpuMeeting)
		{
			msgprintnotime("  [%d] ConfID:%d, m_bInitXmpuMeeting:%d, ConfTempId:%d, CallNodeName:%s, DelayCall:%d.\n", 
				wIndex, wIndex+1, pInfo->m_bInitXmpuMeeting, 
				pInfo->m_tXmpuConfTempInfo.m_wID, pInfo->m_tXmpuCallerNode.m_tCalledAddr.GetValidAlias().m_abyAlias,
				pInfo->m_bXmpuNeedDelayCall);
		}
	}
#endif //#ifdef _USE_XMPUEQP_
	return;
}


void CUmsConfInst::CheckFrameDis( u32 dwDsIP, u16 wNewPort, u16 wOldPort, TTPTransAddr& tDst)
{
	MdlHint(Ums_Mdl_Call, ("CheckFrameDis ConfID:%d, NewPort:%d, OldPort:%d, Dst:"TPIPFORMAT":%d\n", 
		GetInsID(), wNewPort, wOldPort, Tpu32ToIP(tDst.m_dwIP), tDst.m_wPort));
	
	TCheckIFrameBase tNewBase;
	TIFrameSndDis	 tNewSndDis;
	TCheckIFrameBase tOldBase;
	TIFrameSndDis	 tOldSndDis;
	
	tNewBase.m_emType = TP_IFrameCheck_Dis;
	tNewBase.m_wConfID = GetInsID();
	tNewBase.m_wExpires = IFRAME_CHECK_TIMEOUT;
	tNewBase.m_dwIP = dwDsIP;
	tNewBase.m_wPort = wNewPort;
	
	tOldBase.m_emType = TP_IFrameCheck_Dis;
	tOldBase.m_wConfID = GetInsID();
	tOldBase.m_wExpires = IFRAME_CHECK_TIMEOUT;
	tOldBase.m_dwIP = dwDsIP;
	tOldBase.m_wPort = wOldPort;
	
	tNewSndDis.m_bCheck = TRUE;
	tNewSndDis.m_dwDstIp = tDst.m_dwIP;
	tNewSndDis.m_wDstPort = tDst.m_wPort;
	tNewSndDis.m_wOldPort = wOldPort;//用于检测到关键帧后，关闭老码流
	
	tOldSndDis.m_bCheck = FALSE;
	tOldSndDis.m_dwDstIp = tDst.m_dwIP;
	tOldSndDis.m_wDstPort = tDst.m_wPort;
	
	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_iframe_SndDis);
	cMsg.SetBody(&tNewBase, sizeof(tNewBase));
	cMsg.CatBody(&tNewSndDis, sizeof(tNewSndDis));
	cMsg.CatBody(&tOldBase, sizeof(tOldBase));
	cMsg.CatBody(&tOldSndDis, sizeof(tOldSndDis));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, GetConfEqpDs().m_dwEqpNode, UMS_CALL_APP_INST(GetInsID()));
	
	return ;
}


void CUmsConfInst::OnMcuCasecadeChanConnected( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsMcuChan& tMcuChan = *(TUmsMcuChan*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	Hint("OnMcuCasecadeChanConnected conf:%d, ep:%d, mcuchan:%d, mcuappchan:%d.\n", 
		GetInsID(), tHandle.GetEpID(), tMcuChan.m_hMcuChan, tMcuChan.m_hMcuAppChan);
	
	if (inst_idle == CurState())
	{
		Error("OnMcuCasecadeChanConnected state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	if (!IsChairConf())
	{// 下级ums不级联mcu
		return;
	}

	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->IsCallOn() || !ptNode->IsSingleMcu())
	{
		Error("OnMcuCasecadeChanConnected ep is null or not single mcu! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
		return;
	}

	if (!CUmsConfigEx::GetInstance()->IsCasecadeMcuOn())
	{
		Hint("OnMcuCasecadeChanConnected cfgex IsCasecadeMcuOn not true! ConfID:%d, EpId:%d.\n", GetInsID(), wEpID);
		return;
	}
	
	m_pcMcuMgr->McuCaseCadeConnect(ptNode);

	ptNode->m_emEpType = emTPEndpointH323MCU; // 级联mcu
	ptNode->m_hMcuChan = tMcuChan.m_hMcuChan;
	ptNode->m_hMcuAppChan = tMcuChan.m_hMcuAppChan;

	TUmsHandle tOutHandle;
	TUmsMcuChan tOutChan;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
	tOutChan.m_hMcuChan = ptNode->m_hMcuChan;
	tOutChan.m_hMcuAppChan = ptNode->m_hMcuAppChan;

	TUmsMcuRegUnReg tReq;
	tReq.m_bReg = TRUE;
	tReq.m_nReqID = ptNode->m_nMcuReqID++;

	UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_RegUnRegReq, &tReq, sizeof(tReq));

	return;
}

void CUmsConfInst::OnMcuCasecadeRegUnRegReq( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsMcuRegUnReg& tReq = *(TUmsMcuRegUnReg*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	Hint("OnMcuCasecadeRegUnRegReq conf:%d, ep:%d, bbReg:%d, ReqId:%d\n", 
		GetInsID(), tHandle.GetEpID(), tReq.m_bReg, tReq.m_nReqID);
	
	if (inst_idle == CurState())
	{
		Error("OnMcuCasecadeRegUnRegReq state error. ConfID:%d\n", GetInsID());
		return;
	}
	
	if (!IsChairConf())
	{// 下级ums不级联mcu
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->IsCallOn() || !ptNode->IsMcu())
	{
		Error("OnMcuCasecadeRegUnRegReq ep is null or not mcu! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
		return;
	}

	TUmsHandle tOutHandle;
	TUmsMcuChan tOutChan;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
	tOutChan.m_hMcuChan = ptNode->m_hMcuChan;
	tOutChan.m_hMcuAppChan = ptNode->m_hMcuAppChan;
	
	TUmsMcuRegUnReg tRsp;
	tRsp.m_bReg = tReq.m_bReg;
	tRsp.m_nReqID = tReq.m_nReqID;
	tRsp.m_emRet = em_umsmcuret_Ok;

	UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_RegUnRegRsp, &tRsp, sizeof(tRsp));

	return;
}

void CUmsConfInst::OnMcuCasecadeRegUnRegRsp( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsMcuRegUnReg& tRsp = *(TUmsMcuRegUnReg*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	
	Hint("OnMcuCasecadeRegUnRegRsp conf:%d, ep:%d, bbReg:%d, ReqId:%d, ret:%d.\n", 
		GetInsID(), tHandle.GetEpID(), tRsp.m_bReg, tRsp.m_nReqID, tRsp.m_emRet);

	// to do ...

	return;
}

void CUmsConfInst::OnMcuCasecadeRosterNotify( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsMcuRosterList& tMcu = *(TUmsMcuRosterList*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	
	Hint("OnMcuCasecadeRosterNotify conf:%d, ep:%d, Num:%d.\n", 
		GetInsID(), tHandle.GetEpID(), tMcu.m_wNum);
	
	if (inst_idle == CurState())
	{
		Error("OnMcuCasecadeRosterNotify state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	if (!IsChairConf())
	{// 下级ums不级联mcu
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->IsCallOn() || !ptNode->IsMcu())
	{
		Error("OnMcuCasecadeRosterNotify ep is null or not mcu! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
		return;
	}

	if (0 == tMcu.m_wNum)
	{// 花名册通知结束标记
	 // 向mcu请求list
		TUmsHandle tOutHandle;
		TUmsMcuChan tOutChan;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		tOutChan.m_hMcuChan = ptNode->m_hMcuChan;
		tOutChan.m_hMcuAppChan = ptNode->m_hMcuAppChan;
		
		s32 nReqId = ptNode->m_nMcuReqID++;
		
		UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_PartListReq, &nReqId, sizeof(nReqId));

		return;
	}
	
	for (u16 wIndex = 0; wIndex< tMcu.m_wNum; wIndex++)
	{
		u16 wLowEpID = GETINS(tMcu.m_atRoster[wIndex].m_dwPID);
		TCallNode * ptAddNode = m_pcNodeMgr->GetNodeByChildEpID(ptNode, wLowEpID);
		if (NULL == ptAddNode)
		{
			ptAddNode = m_pcNodeMgr->AddChildNodeForMcu(ptNode, tMcu.m_atRoster[wIndex]);
			if (NULL == ptAddNode)
			{
				Error("OnMcuCasecadeRosterNotify assign mcu node error! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
				continue;
			}
			UpdateNodeInfo(tp_OprType_Add, ptAddNode->m_wEpID);
		}
		else
		{
			Error("OnMcuCasecadeRosterNotify mcu node already exit! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
			continue;
		}
	}

	return;
}

void CUmsConfInst::OnMcuCasecadePartListReqRsp( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsMcuPartList tList = *(TUmsMcuPartList*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	
	Hint("OnMcuCasecadePartListReqRsp conf:%d, ep:%d nReqId:%d, emRet:%d, PartCount:%d, bLastPack:%d.\n", 
		GetInsID(), tHandle.GetEpID(), tList.m_nReqID, tList.m_emRet,
		tList.m_dwPartCount, tList.m_bLastPack);

	if (inst_idle == CurState())
	{
		Error("OnMcuCasecadePartListReqRsp state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	if (!IsChairConf())
	{// 下级ums不级联mcu
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->IsChanOn() || !ptNode->IsMcu())
	{
		Error("OnMcuCasecadePartListReqRsp ep is null or not mcu! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
		return;
	}

	u16 wIndex = 0;
	TUmcMcuPart tPart;
	u8* pbyBuf = ptMsg->GetBody() + sizeof(TUmsHandle) + sizeof(TUmsMcuPartList);
	for (; wIndex < tList.m_dwPartCount; ++wIndex)
	{
		TP_SAFE_CAST(tPart, (u8*)((u8*)pbyBuf + wIndex*sizeof(TUmcMcuPart)));

		u16 wLowEpID = GETINS(tPart.m_dwPID);
		if (!VALID_ALL_EPID(wLowEpID))
		{
			Error("OnMcuCasecadePartListReqRsp low ep is invalid! ConfID:%d, LowEpID:%d.\n", GetInsID(), wLowEpID);
			continue;
		}

		TCallNode * ptChildNode = m_pcNodeMgr->GetNodeByChildEpID(ptNode, wLowEpID);
		if (NULL == ptChildNode)
		{
			Error("OnMcuCasecadePartListReqRsp can not find this ep! ConfID:%d, LowEpID:%d.\n", GetInsID(), wLowEpID);
			continue;
		}
		
		// 设置mcu会场信息
		ptChildNode->SetMcuNodeCallInfo(tPart);
		BOOL32 bOldChan = ptChildNode->m_bChannelOpen;
		if (!bOldChan && ptChildNode->IsCallOn())
		{//通道上线
			TCallNode* ptParNode = m_pcNodeMgr->GetCapsetNode(ptChildNode->m_wParentEpID);
			ptChildNode->SetMcuNodeChanInfo(ptParNode, tPart);	
			UpdateNodeInfo(tp_OprType_Update, ptChildNode->m_wEpID);
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("OnMcuCasecadePartListReqRsp ep not online, unneed proc. confid:%d, epid:%d, childId:%d, CallState:%d, ChanOn:%d\n"
				, GetInsID(), tHandle.GetEpID(), ptChildNode->m_wLowChildEpID, ptChildNode->m_emCallState, ptChildNode->IsChanOn()));
		}
	}
}

// mcu下级 会场状态变更或者新会场上线
void CUmsConfInst::OnMcuCasecadePartStateNty( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmcMcuPart tMcu	= *(TUmcMcuPart*)(ptMsg->GetBody() + sizeof(TUmsHandle));

	Hint("OnMcuCasecadePartStateNty conf:%d, ep:%d, McuId:%d, MtId:%d, epName:%s, epIp:"IPFORMAT", bState:%d, bMute:%d, bQuiet:%d.\n", 
		GetInsID(), tHandle.GetEpID(), GETAPP(tMcu.m_dwPID), GETINS(tMcu.m_dwPID), tMcu.m_aszEpName, 
		u32ToIP(tMcu.m_dwIP), tMcu.m_byState, tMcu.m_bMute, tMcu.m_bQuiet);

	if (inst_idle == CurState())
	{
		Error("OnMcuCasecadePartStateNty state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	if (!IsChairConf())
	{// 下级ums不级联mcu
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->IsCallOn() || !ptNode->IsMcu())
	{
		Error("OnMcuCasecadePartStateNty ep is null or not mcu! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
		return;
	}

	u16 wLowEpID = GETINS(tMcu.m_dwPID);
	TCallNode * ptAddNode = m_pcNodeMgr->GetNodeByChildEpID(ptNode, wLowEpID);
	if (NULL != ptAddNode)
	{// 下级节点已存在则变更其状态
	
		if (tMcu.m_byState == 1 || tMcu.m_byState == 3)
		{// 1:ums_UmsConfNodeState_calling 和 3:ums_UmsConfNodeState_online
			
			ptAddNode->SetMcuNodeCallInfo(tMcu);

			BOOL32 bOldChan = ptAddNode->m_bChannelOpen;
			if (!bOldChan && ptAddNode->IsCallOn())
			{//通道上线
				TCallNode* ptParNode = m_pcNodeMgr->GetCapsetNode(ptAddNode->m_wParentEpID);
				ptAddNode->SetMcuNodeChanInfo(ptParNode, tMcu);	
				UpdateNodeInfo(tp_OprType_Update, ptAddNode->m_wEpID);
			}
		}
		else
		{
			if (ptAddNode->IsCallOn())
			{
				// mcu下级会场掉线通知
				HungUpMcuEpFromLow(ptAddNode, EmCnsCallReason_peerhungup);
			}
			else
			{//始终没有呼叫上来的下级会场失败状态，也要更新
				ptAddNode->SetMcuNodeCallInfo(tMcu);
			}
		}
		
		UpdateNodeInfo(tp_OprType_Update, ptAddNode->m_wEpID);
	}
	else
	{
		// 下级mcu会场第一次上线 添加node信息
		ptAddNode = m_pcNodeMgr->AddChildNodeForMcu(ptNode, tMcu);
		if (NULL == ptAddNode)
		{
			Error("OnMcuCasecadePartStateNty assign mcu node error! ConfID:%d, LowEpID:%d.\n", GetInsID(), wLowEpID);
			return;
		}
		UpdateNodeInfo(tp_OprType_Add, ptAddNode->m_wEpID);
	}

}

void CUmsConfInst::OnMcuCasecadeDelPartNty( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	u32 dwDelPID		= *(u32*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	
	Hint("OnMcuCasecadeDelPartNty conf:%d, ep:%d delLowEpId:%d.\n", 
		GetInsID(), tHandle.GetEpID(), GETINS(dwDelPID));

	if (inst_idle == CurState())
	{
		Error("OnMcuCasecadeDelPartNty state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	if (!IsChairConf())
	{// 下级ums不级联mcu
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->IsChanOn() || !ptNode->IsMcu())
	{
		Error("OnMcuCasecadeDelPartNty ep is null or not mcu! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
		return;
	}
	
	u16 wLowEpID = GETINS(dwDelPID);
	TCallNode* ptDelNode = m_pcNodeMgr->GetNodeByChildEpID(ptNode, wLowEpID);;
	if (NULL != ptDelNode)
	{
		u16 awChildEpID[TP_CONF_MAX_CNSNUM];
		u16 wEpChildNum = m_pcNodeMgr->GetAllNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, ptDelNode);
		for (u16 wI = 0; wI < wEpChildNum; ++wI)
		{
			UpdateNodeInfo(tp_OprType_Del, awChildEpID[wEpChildNum]);
		}
		m_pcNodeMgr->DeleteNode(ptDelNode);
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("OnMcuCasecadeDelPartNty ep node error. confid:%d, epid:%d, lowEpID:%d\n"
			, GetInsID(), ptNode->m_wEpID, wLowEpID));
	}

}

// 切换mcu下级会场为发言人 mcu下级会场不参与ums 讨论 轮询 
void CUmsConfInst::OnChangeMcuEpSpeakerFromCns( TUmsHandle tHandle, TConfEpID* ptConfEp )
{
	if ( !CheckMsgFromChair(this, tHandle.GetEpID()) )
	{
		return;
	}

	if (NULL == ptConfEp)
	{
	//	ObjError(("OnChangeMcuEpSpeakerFromCns cur ep is not mcu low ep ConfID:%d, old Speaker:%d, new Speaker:%d\n", GetInsID(), curSpeakerID(), wEpID));
		return;
	}

	u16 wEpID = ptConfEp->m_wEpID;
	TCallNode* ptNode = m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (!ptNode || !ptFartherNode || ptFartherNode == ptNode || !ptFartherNode->IsMcu())
	{
		ObjError(("OnChangeMcuEpSpeakerFromCns cur ep is not mcu low ep ConfID:%d, old Speaker:%d, new Speaker:%d\n", GetInsID(), curSpeakerID(), wEpID));
		return ;
	}
	
	EmTpApplySpeakerRet emRet = TP_ApplySpeaker_Success;
	do 
	{
		
		if (!ptNode->IsMtEp() || !ptNode->IsCallOn() || !ptNode->IsChanOn() || !ptNode->IsVidSndValid())
		{
			ObjError(("OnChangeMcuEpSpeakerFromCns ep state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), wEpID, UmsNodeConfType(ptNode->m_emCallState), ptNode->m_bChannelOpen));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}
		
		if (0 == ptNode->m_wVidSndNum && 0 == ptNode->m_wAudSndNum)
		{
			ObjError(("OnChangeMcuEpSpeakerFromCns ep Snd Num error. ConfID:%d, epID:%d, VidSndNum:%d, AudSndNum:%d\n", GetInsID(), wEpID, ptNode->m_wVidSndNum, ptNode->m_wAudSndNum));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}
		
		if (wEpID == curSpeakerID())
		{
			ObjError(("OnChangeMcuEpSpeakerFromCns ep not changer.wConfID:%d, EpID:%d, curspeaker:%d\n", GetInsID(), wEpID, curSpeakerID()));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}
		
		if (m_pcUmsDiscuss->IsUIDiscussOn())
		{// mcu下级会场不参与讨论
			ObjError(("OnChangeMcuEpSpeakerFromCns mcu low ep is not in discuss. ConfId:%d, epId:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}
		
		if (GetRollCallMgr()->IsUIRollCallOn())
		{   //点名模式，不支持切换发言人
			ObjError(("OnChangeMcuEpSpeakerFromCns Now it is rollcallmode modle, ConfId:%d, epId:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}	
		
	} while (0);
	
	ObjHint(("OnChangeMcuEpSpeakerFromCns ConfID:%d, old Speaker:%d, new Speaker:%d, ret:%d\n", GetInsID(), curSpeakerID(), wEpID, emRet));
	
	//回应CNS
	u8 uSndBuf[sizeof(TConfEpID) + sizeof(EmTpApplySpeakerRet)] = { 0 };
	memcpy(uSndBuf, ptConfEp, sizeof(TConfEpID));
	memcpy(uSndBuf + sizeof(TConfEpID), &emRet, sizeof(EmTpApplySpeakerRet));
	NotifyConfCtrlMsgToCns(ev_UmsConfApplySpeaker_Ind, tHandle.GetEpID(), uSndBuf, sizeof(uSndBuf));
	
	TUmsHandle tOutHandle;
	TUmsMcuChan tOutChan;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
	tOutChan.m_hMcuChan = ptFartherNode->m_hMcuChan;
	tOutChan.m_hMcuAppChan = ptFartherNode->m_hMcuAppChan;
	u16 wLowEpId = ptNode->m_wLowChildEpID;
				
	// 请求mcu级联回传通道
	u32 dwPID = MAKEIID(UMS_MCU_PART_MAX_NUM, ptNode->m_wLowChildEpID); // 192 本mcu mcuid + mtId
	UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_SetInReq, &dwPID, sizeof(u32));
	

	// 切换mcu下级发言人
	TMcuSpeakerStausNty	tStatus;
	tStatus.m_dwPID	= MAKEIID(UMS_MCU_PART_MAX_NUM, ptNode->m_wLowChildEpID); // 192 本mcu mcuid + mtId
	tStatus.m_dwStatus = 2; // 指定发言人
	UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_SpeakerStatusNty, &tStatus, sizeof(TMcuSpeakerStausNty));

	if (TP_ApplySpeaker_Success == emRet)
	{
		// 切换发言人
		ChangeSpeaker(wEpID, NULL);
		AdjustNewSpeakerToAllNode();
		AdjustNewSpeakerToAllMcuNode();
		NotifyApplySpeakerToUI();
	}
	
	return;
}

void CUmsConfInst::OnChangeMcuEpSpeakerFromUmc( TLogUser* ptLogUser, TConfEpID* ptConfEp )
{
	if (!ptLogUser || !ptConfEp)
	{
		return;
	}

	u16 wEpID = ptConfEp->m_wEpID;
	TCallNode* ptNode = m_pcNodeMgr->GetNode(wEpID);
	TCapNode* ptFartherNode = m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (!ptNode || !ptFartherNode || ptFartherNode == ptNode || !ptFartherNode->IsMcu())
	{
		ObjError(("OnChangeMcuEpSpeakerFromUmc cur ep is not mcu low ep ConfID:%d, old Speaker:%d, new Speaker:%d\n", GetInsID(), curSpeakerID(), wEpID));
		return ;
	}

	EmTpApplySpeakerRet emRet = TP_ApplySpeaker_Success;
	do 
	{
		if (!ptNode->IsMtEp() || !ptNode->IsCallOn() || !ptNode->IsChanOn() || !ptNode->IsVidSndValid())
		{
			ObjError(("OnChangeMcuEpSpeakerFromUmc ep state error. ConfID:%d, epID:%d, state:%s, chan:%d\n", GetInsID(), wEpID, UmsNodeConfType(ptNode->m_emCallState), ptNode->m_bChannelOpen));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}
		
		if (0 == ptNode->m_wVidSndNum && 0 == ptNode->m_wAudSndNum)
		{
			ObjError(("OnChangeMcuEpSpeakerFromUmc ep Snd Num error. ConfID:%d, epID:%d, VidSndNum:%d, AudSndNum:%d\n", GetInsID(), wEpID, ptNode->m_wVidSndNum, ptNode->m_wAudSndNum));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}
		
		if (wEpID == curSpeakerID())
		{
			ObjError(("OnChangeMcuEpSpeakerFromUmc ep not changer.wConfID:%d, EpID:%d, curspeaker:%d\n", GetInsID(), wEpID, curSpeakerID()));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}
		
		if (m_pcUmsDiscuss->IsUIDiscussOn())
		{// mcu下级会场不参与讨论
			ObjError(("OnChangeMcuEpSpeakerFromUmc mcu low ep is not in discuss. ConfId:%d, epId:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpIDError;
			break;
		}
		
		if (GetRollCallMgr()->IsUIRollCallOn())
		{   //点名模式，不支持切换发言人
			ObjError(("OnChangeMcuEpSpeakerFromUmc Now it is rollcallmode modle, ConfId:%d, epId:%d\n", GetInsID(), wEpID));
			emRet = TP_ApplySpeaker_EpStateError;
			break;
		}	
		
	} while (0);
	
	ObjHint(("OnChangeMcuEpSpeakerFromUmc ConfID:%d, old Speaker:%d, new Speaker:%d, ret:%d\n", GetInsID(), curSpeakerID(), wEpID, emRet));
	
	u8 byBuf[sizeof(TLogUser) + sizeof(TConfEpID) + sizeof(EmTpApplySpeakerRet)] = {0};
	memcpy(byBuf, ptLogUser, sizeof(TLogUser));
	memcpy(byBuf + sizeof(TLogUser), ptConfEp, sizeof(TConfEpID));
	memcpy(byBuf + sizeof(TLogUser) + sizeof(TConfEpID), &emRet, sizeof(EmTpApplySpeakerRet));
	
	// 回应umc
	NotifyMsgToService(evtp_ApplySpeaker_result, byBuf, sizeof(byBuf));

	TUmsHandle tOutHandle;
	TUmsMcuChan tOutChan;
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
	tOutChan.m_hMcuChan = ptFartherNode->m_hMcuChan;
	tOutChan.m_hMcuAppChan = ptFartherNode->m_hMcuAppChan;
	u16 wLowEpId = ptNode->m_wLowChildEpID;
				
	// 请求mcu级联回传通道
	u32 dwPID = MAKEIID(UMS_MCU_PART_MAX_NUM, ptNode->m_wLowChildEpID); // mcuid + mtId
	UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_SetInReq, &dwPID, sizeof(u32));
	
	// 切换mcu下级发言人
	TMcuSpeakerStausNty	tStatus;
	tStatus.m_dwPID	= MAKEIID(UMS_MCU_PART_MAX_NUM, ptNode->m_wLowChildEpID); // 192 本mcu mcuid + mtId
	tStatus.m_dwStatus = 2; // 指定发言人
	UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_SpeakerStatusNty, &tStatus, sizeof(TMcuSpeakerStausNty));
	
	if (TP_ApplySpeaker_Success == emRet)
	{
		// 切换发言人
		ChangeSpeaker(wEpID, NULL);
		AdjustNewSpeakerToAllNode();
		AdjustNewSpeakerToAllMcuNode();
		NotifyApplySpeakerToUI();
	}
	
	return;
}

void CUmsConfInst::AdjustNewSpeakerToAllMcuNode()
{
	if (m_bIsQuiting)
	{
		ObjHint(("AdjustNewSpeakerToAllMcuNode Failed. The Conf is quiting! ConfID:%d\n", GetInsID()));
		return;
	}
	
	ObjHint(("AdjustNewSpeakerToAllNode. ConfID:%d, Speaker:%d\n", GetInsID(), curSpeakerID()));
	
	TCallNode* ptSpeaker = m_pcNodeMgr->GetNode(curSpeakerID());
	TCapNode* ptParent  = m_pcNodeMgr->GetForeFatherNode(ptSpeaker);
	if (!ptSpeaker)
	{
		ObjError(("AdjustNewSpeakerToAllNode. cur speaker is null! ConfID:%d, Speaker:%d\n", GetInsID(), curSpeakerID()));
		return;
	}
	// 发言人为上级会场
	u32 dwPID = MAKEIID(65535, 0);
	u16	awAllEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpAllNum = 0;
	if (ptSpeaker != ptParent && ptParent->IsMcu())
	{// 发言人是mcu的下级会场
		dwPID = MAKEIID(UMS_MCU_PART_MAX_NUM, ptSpeaker->m_wLowChildEpID);// 192 本mcu
	}
	
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn() || !ptNode->IsMcu())
		{
			continue;
		}
	
		TUmsHandle tOutHandle;
		TUmsMcuChan tOutChan;
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		tOutChan.m_hMcuChan = ptNode->m_hMcuChan;
		tOutChan.m_hMcuAppChan = ptNode->m_hMcuAppChan;
		// 找到所有的mcu下级会场
		wEpAllNum = m_pcNodeMgr->GetAllNodeByRoot(awAllEpID,TP_CONF_MAX_CNSNUM,ptNode);
		for (u16 wIndex = 0; wIndex < wEpAllNum; ++wIndex)
		{
			if (awAllEpID[wIndex] != ptNode->m_wEpID)
			{
				UmsCallSendMcuCtrl(tOutHandle, tOutChan, evtp_UMS_MCU_SpeakedChangeNty, &dwPID, sizeof(u32));
			}	
		}

	}

	return ;
}

void CUmsConfInst::OnMcuCasecadeSpyBWNty( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	u32 dwSpyBW		= *(u32*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	
	Hint("OnMcuCasecadeSpyBWNty conf:%d, ep:%d dwSpyBW:%d.\n", GetInsID(), tHandle.GetEpID(), dwSpyBW);
	
	if (inst_idle == CurState())
	{
		Error("OnMcuCasecadeSpyBWNty state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	if (!IsChairConf())
	{// 下级ums不级联mcu
		return;
	}
	
	u16 wEpID = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpID);
	if (NULL == ptNode || !ptNode->IsChanOn() || !ptNode->IsMcu())
	{
		Error("OnMcuCasecadeSpyBWNty ep is null or not mcu! ConfID:%d, EpID:%d.\n", GetInsID(), wEpID);
		return;
	}
	
	m_pcMcuMgr->McuCaseCadeSpyBWNty(ptNode, dwSpyBW);

}

void CUmsConfInst::OnFeccChannedConnnected( CTpMsg *const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	
	Hint("OnFeccChannedConnnected conf:%d, ep:%d.\n", GetInsID(), tHandle.GetEpID());
	
	if (inst_idle == CurState())
	{
		Error("OnFeccChannedConnnected state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	TCallNode* ptNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (!ptNode)
	{
		Error("OnFeccChannedConnnected ep node is null. conf:%d, ep:%d.\n", GetInsID(), tHandle.GetEpID());
		return;
	}
	
	if(!ptNode->Is323Ep() && !ptNode->IsUms())
	{
		Error("OnFeccChannedConnnected ep is not 323 ep. conf:%d, ep:%d.\n", GetInsID(), tHandle.GetEpID());
		return;
	}

	if (!ptNode->IsCallOn())
	{
		Error("OnFeccChannedConnnected ep state error . conf:%d, ep:%d, state:%s.\n", GetInsID(), tHandle.GetEpID(), UmsNodeConfType(ptNode->m_emCallState));
		return;
	}
	
	ptNode->SetAllowFecc(TRUE);
	// 通知umc 主席cns 
//	UpdateNodeInfo(tp_OprType_Update, ptNode->m_wEpID);
}

void CUmsConfInst::OnFeccCamControlFromUmc( CTpMsg* const ptMsg )
{
	TLogUser  tUser = *(TLogUser*)ptMsg->GetBody();
	TCamReq	  tCamReq = *(TCamReq*)(ptMsg->GetBody()+sizeof(TLogUser));
	
	Hint( "OnFeccCamControlFromUmc,confID:%d, dstId:%d, CamAck:%d, CamReq:%d\n",
		tCamReq.m_wConfID, tCamReq.m_wEpID, tCamReq.m_emCamAct, tCamReq.m_emCamReq);

	if (inst_idle == CurState())
	{
		Error("OnFeccCamControlFromUmc state error or chair ep invalid. ConfID:%d.\n", GetInsID());
		return;
	}
	
	u32 dwReason  = 0;
	TFeccInfo tInfo;
	tInfo.m_wConfID = tCamReq.m_wConfID;
	tInfo.m_wEpID   = tCamReq.m_wEpID;
	tInfo.m_tCamAct.setFeccParam(tCamReq.m_emCamAct, tCamReq.m_emCamReq);

	BOOL32 bResult = FeccReqFromUmcCns(tInfo, dwReason);
	if(!bResult)
	{
		// 回应umc
		TTPUmsReasonInd tInd;
		tInd.m_wConfID = GetInsID();
		tInd.m_wEpID = tCamReq.m_wEpID;
		tInd.m_dwReason = dwReason;
		NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd), &tUser);
	}
	
}

void CUmsConfInst::OnFeccPrePosReqFromUmc( CTpMsg* const ptMsg )
{
	TLogUser  tUser = *(TLogUser*)ptMsg->GetBody();
	TPrePos	  tPrePos = *(TPrePos*)(ptMsg->GetBody()+sizeof(TLogUser));
	
	Hint( "OnFeccPrePosReqFromUmc,confID:%d, dstId:%d, PrePos:%d, PrePosReq:%d\n",
		tPrePos.m_wConfID, tPrePos.m_wEpID, tPrePos.m_emPosAct, tPrePos.m_dwSaveNo);
	
	if (inst_idle == CurState())
	{
		Error("OnFeccPrePosReqFromUmc state error or chair ep invalid. ConfID:%d.\n", GetInsID());
		return;
	}
	
	u32 dwReason  = 0;
	TFeccInfo tInfo;
	tInfo.m_wConfID = tPrePos.m_wConfID;
	tInfo.m_wEpID   = tPrePos.m_wEpID;
	tInfo.m_tCamAct.setFeccParam(tPrePos.m_emPosAct, tPrePos.m_dwSaveNo);
	
	BOOL32 bResult = FeccReqFromUmcCns(tInfo, dwReason);
	if(!bResult)
	{
		// 回应umc
		TTPUmsReasonInd tInd;
		tInd.m_wConfID = GetInsID();
		tInd.m_wEpID = tPrePos.m_wEpID;
		tInd.m_dwReason = dwReason;
		NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd), &tUser);
	}
}

void CUmsConfInst::OnFeccSelVidFromUmc( CTpMsg* const ptMsg )
{
	TLogUser  tUser = *(TLogUser*)ptMsg->GetBody();
	TSelVid	  tSelVid = *(TSelVid*)(ptMsg->GetBody()+sizeof(TLogUser));
	
	Hint( "OnFeccSelVidFromUmc,confID:%d, dstId:%d, SelVid:%d, VidNo:%d\n",
		tSelVid.m_wConfID, tSelVid.m_wEpID, tSelVid.m_emVidAct, tSelVid.m_dwVidNo);
	
	if (inst_idle == CurState())
	{
		Error("OnFeccSelVidFromUmc state error or chair ep invalid. ConfID:%d.\n", GetInsID());
		return;
	}
	
	u32 dwReason  = 0;
	TFeccInfo tInfo;
	tInfo.m_wConfID = tSelVid.m_wConfID;
	tInfo.m_wEpID   = tSelVid.m_wEpID;
	tInfo.m_tCamAct.setFeccParam(tSelVid.m_emVidAct, tSelVid.m_dwVidNo);
	
	BOOL32 bResult = FeccReqFromUmcCns(tInfo, dwReason);
	if(!bResult)
	{
		// 回应umc
		TTPUmsReasonInd tInd;
		tInd.m_wConfID = GetInsID();
		tInd.m_wEpID = tSelVid.m_wEpID;
		tInd.m_dwReason = dwReason;
		NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd), &tUser);
	}
}

void CUmsConfInst::OnFeccReqFromCns( CTpMsg* const ptMsg )
{
	TUmsHandle tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TFeccInfo  tInfo = *(TFeccInfo*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	Hint( "OnFeccReqFromCns,confID:%d, dstId:%d, FeccAct:%d, CamReq:%d\n",
		tInfo.m_wConfID, tInfo.m_wEpID,
					tInfo.m_tCamAct.m_emFeccAct, tInfo.m_tCamAct.GetFeccParam());

	if (inst_idle == CurState())
	{
		Error("OnFeccReqFromCns state error. conf:%d.\n", GetInsID());
		return;
	}
	
	if ( !CheckMsgFromChair(this, tHandle.GetEpID()) && !Is_Caller_Node(tHandle.GetEpID()))
	{
		Error("OnFeccReqFromCns is not from chair. conf:%d, AskEp:%d, dstep:%d.\n", 
			     GetInsID(), tHandle.GetEpID(), tInfo.m_wEpID);
		return;
	}
	u32 dwReason  = 0;
	BOOL32 bResult = FeccReqFromUmcCns(tInfo, dwReason);
	if(!bResult)
	{
		// 回应CNS
		TTPUmsReasonInd tInd;
		tInd.m_wConfID = GetInsID();
		tInd.m_wEpID = tHandle.GetEpID();
		tInd.m_dwReason = dwReason;
		NotifyConfCtrlMsgToCns(ev_UmsCommonReasonToUI_Ind, tHandle.GetEpID(), &tInd, sizeof(tInd));
	}
	
}

BOOL32 CUmsConfInst::FeccReqFromUmcCns( TFeccInfo& tInfo, u32& dwReason )
{
	TCallNode* ptNode = m_pcNodeMgr->GetNode(tInfo.m_wEpID);
	TCapNode*  ptParent = m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (!ptNode)
	{
		Error("OnFeccReqFromUmc dst ep node is null. conf:%d, dstep:%d.\n", 
			     GetInsID(), tInfo.m_wEpID);
		return FALSE;
	}
	
	if(!ptNode->Is323Ep())
	{
		Error("OnFeccReqFromUmc dst ep node is not 323 mt . conf:%d, dstep:%d.\n", 
			     GetInsID(), tInfo.m_wEpID);
		dwReason = TP_UMS_FECC_NO_323MT;
		return FALSE;
	}

	if(!ptNode->IsAllowFecc())
	{
		Error("OnFeccReqFromUmc dst ep node is not allow fecc. conf:%d, dstep:%d.\n", 
			     GetInsID(), tInfo.m_wEpID);
		dwReason = TP_UMS_FECC_CHANNEL_NOT_OPEN;
		return FALSE;
	}
	
	// 切源消息,先改变当前源
	if (tInfo.m_tCamAct.m_emFeccAct == em_Fecc_SwitchVideo || tInfo.m_tCamAct.m_emFeccAct == em_Fecc_SelectVideo)
	{
		if (ptNode->m_byCurVidNo == tInfo.m_tCamAct.GetFeccParam())
		{
			return TRUE;
		}
		else
		{
			ptNode->SetCurVidNo(tInfo.m_tCamAct.GetFeccParam());
		}
	}

	TFeccMtInfo  tFeccMtInfo;
	TUmsHandle tOutHandle;
	// 远遥会场为本级会场
	if (ptNode == ptParent)
	{
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		// 目的mcu 192(本mcu) mt EpId
		tFeccMtInfo.m_byDstMcuId = UMS_MCU_PART_MAX_NUM;
		tFeccMtInfo.m_byDstMtId  = tInfo.m_wEpID;
		
		// 源mcu 192(本mcu) mt ChairId
		tFeccMtInfo.m_bySrcMcuId = UMS_MCU_PART_MAX_NUM;
		tFeccMtInfo.m_bySrcMtId  = chairID();
	}
	else
	{// 发送给下级ums mcu
		m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptParent->m_wEpID);
		// 目的ums/mcu 192  mt LowEpId
		tFeccMtInfo.m_byDstMcuId = UMS_MCU_PART_MAX_NUM;
		tFeccMtInfo.m_byDstMtId  = ptNode->m_wLowChildEpID;
		// 源ums/mcu 192 mt ChairId
		tFeccMtInfo.m_bySrcMcuId = UMS_MCU_PART_MAX_NUM;
		tFeccMtInfo.m_bySrcMtId  = chairID();
	}
	
	u8 abyBuf[sizeof(TCamAction) + sizeof(TFeccMtInfo)] = {0};
	memcpy(abyBuf, &tInfo.m_tCamAct, sizeof(TCamAction));
	memcpy(abyBuf + sizeof(TCamAction), &tFeccMtInfo, sizeof(TFeccMtInfo));
	
	UmsSendConfCtrl(tOutHandle, evtp_UMS_CNS_SendFecc_Cmd, &abyBuf, sizeof(abyBuf));

	return TRUE;
}

void CUmsConfInst::OnVidSourceInfoFromCns( CTpMsg* const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TVidSourceInfo tInfo = *(TVidSourceInfo*)(ptMsg->GetBody() + sizeof(TUmsHandle));
	
	Hint("OnVidSourceInfoFromCns conf:%d, ep:%d, byNum:%d.\n", GetInsID(), tHandle.GetEpID(), tInfo.m_byNum);

	for (u16 wIndex =0; wIndex < tInfo.m_byNum; ++wIndex)
	{
		LowHint(" byIndex:%d, byAlias:%s.\n", tInfo.m_atVidInfo[wIndex].m_byIndex, tInfo.m_atVidInfo[wIndex].m_abyAlias);
	}

	
	if (inst_idle == CurState())
	{
		Error("OnVidSourceInfoFromCns state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	TCallNode* ptNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (!ptNode)
	{
		Error("OnVidSourceInfoFromCns ep node is null. conf:%d, ep:%d.\n", GetInsID(), tHandle.GetEpID());
		return;
	}
	
	if(!ptNode->Is323Ep() && !ptNode->IsUms())
	{
		Error("OnVidSourceInfoFromCns ep is not 323 ep. conf:%d, ep:%d.\n", GetInsID(), tHandle.GetEpID());
		return;
	}
	
	if (!ptNode->IsCallOn())
	{
		Error("OnVidSourceInfoFromCns ep state error . conf:%d, ep:%d, state:%s.\n", GetInsID(), tHandle.GetEpID(), UmsNodeConfType(ptNode->m_emCallState));
		return;
	}
	ptNode->SetVidSource(tInfo);
	// 通知umc 主席cns 上级
	NotifyVidFeccInfoToUI(ptNode->m_wEpID);
}

void CUmsConfInst::VidFeccInfoNty( TUmsHandle& tHandle,  u8 byVidNo, BOOL32 bAllowFecc)
{
	
	Hint("VidFeccInfoNty conf:%d, ep:%d, CurVidNo:%d, bAllowFecc:%d.\n",
		GetInsID(), tHandle.GetEpID(), byVidNo, bAllowFecc);
	
	if (inst_idle == CurState())
	{
		Error("VidFeccInfoNty state error. ConfID:%d.\n", GetInsID());
		return;
	}
	
	TCallNode* ptNode = m_pcNodeMgr->GetNode(tHandle.GetEpID());
	if (!ptNode)
	{
		Error("VidFeccInfoNty ep node is null. conf:%d, ep:%d.\n", GetInsID(), tHandle.GetEpID());
		return;
	}
	
	if(!ptNode->Is323Ep() && !ptNode->IsUms())
	{
		Error("VidFeccInfoNty ep is not 323 ep. conf:%d, ep:%d.\n", GetInsID(), tHandle.GetEpID());
		return;
	}
	
	if (!ptNode->IsCallOn())
	{
		Error("VidFeccInfoNty ep state error . conf:%d, ep:%d, state:%s.\n", GetInsID(), tHandle.GetEpID(), UmsNodeConfType(ptNode->m_emCallState));
		return;
	}
	ptNode->SetCurVidNo(byVidNo);
	ptNode->SetAllowFecc(bAllowFecc);
	
	// 通知umc 主席cns 上级
	NotifyVidFeccInfoToUI(ptNode->m_wEpID);
}

void CUmsConfInst::NotifyVidFeccInfoToUI(u16 wEpId)
{
	TCallNode* ptNode = m_pcNodeMgr->GetNode(wEpId);
	if (!ptNode)
	{
		Error("NotifyVidFeccInfoToUI ep is null. conf:%d, ep:%d.\n", GetInsID(), wEpId);
		return;
	}

	m_tUpdateNodeList.Add(tp_OprType_Update, wEpId);
	NotifyUpdateNodeToUi();

	TConfVidFeccInfo tVidFeccList;
	tVidFeccList.m_wConfID	= GetInsID();
	tVidFeccList.m_emOpr	= tp_OprType_Update;
	ptNode->GetVidFeccInfo(tVidFeccList.m_atVidFeccList[tVidFeccList.m_wNum]);
	tVidFeccList.m_wNum++;
	
	NotifyMsgToServiceForUI(evtp_VidFeccMsg_Nty, &tVidFeccList, sizeof(tVidFeccList));

	// 更新给主席远遥 视频源消息
	NotifyVidFeccInfoToChair(tVidFeccList);
	// 更新给上级远遥通道消息
	m_pcCallMgr->NotifyToHigherVidFeccInfo(wEpId);
}

void CUmsConfInst::NotifyVidFeccInfoToChair( TConfVidFeccInfo& tVidFeccList )
{
	TCallNode* ptChair = m_pcNodeMgr->GetNode(chairID());
	if (!ptChair || !ptChair->IsCallOn() || !ptChair->IsMtEp())
	{
		Error("NotifyVidFeccInfoToChair ep is null, or is not call on. conf:%d, Chair:%d, emState:%d.\n", 
			GetInsID(), chairID(), ptChair->m_emCallState);
		return;
	}

	TUmsHandle tOutHandle;	
	m_pcNodeMgr->MakeCallerHandle(tOutHandle, chairID());	
	UmsSendConfCtrl(tOutHandle, evtp_UMS_CNS_VidFeccInfoNty, &tVidFeccList, sizeof(TConfVidFeccInfo));
	
}

void CUmsConfInst::OnEpStatusNty( CTpMsg* const ptMsg )
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TEpStatusInfo tStatusInfo = *(TEpStatusInfo*)(ptMsg->GetBody() + sizeof(TUmsHandle));
	
	// 静音通知处理
	MuteRemoteEpInd(tHandle, &tStatusInfo.m_tMuteInd);

	// 哑音通知处理
	QuietRemoteEpInd(tHandle, &tStatusInfo.m_tQuietInd);

	// 视频源处理
	VidFeccInfoNty(tHandle, tStatusInfo.m_byCurVidNo, tStatusInfo.m_bAllowFecc);
}

void CUmsConfInst::EventEpNodeTimerCheck()
{// 目前用于 323终端入会后，定时检测是否是渠道终端
	Hint("EventEpNodeTimerCheck Timer is coming... ConfId:%d.\n", GetInsID());
	BOOL32 bNeedKillTimer = TRUE;
	TUmsHandle tHandle;
	
	if (!g_bKedaManuOn)
	{
		KillTimer(evtp_EpNodeTimer_Check);
		m_bEpNodeCheck = FALSE;
		return;
	}
	
	for (TCapNode* ptNode = m_pcNodeMgr->FirstNeedCallNode(); ptNode != NULL; ptNode = m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if (!ptNode->IsCallOn() || emTpH323 != ptNode->m_emCallProtocol)
		{// 非上线的323终端，不检测
			continue;
		}
		
		if (ptNode->m_bIsKedaManu)
		{
			continue;
		}
		
		ptNode->m_bKedaManuCheckNum++;
		if (3 == ptNode->m_bKedaManuCheckNum)
		{
			// 挂断此会场
			Hint("EventEpNodeTimerCheck This is not kedamanu ep, hungup! Ep:%d.\n", ptNode->m_wEpID);
			HungUp(ptNode->m_wEpID, FALSE, TRUE, EmCnsCallReason_Local);
		}
		else
		{// 还需要检测
			bNeedKillTimer = FALSE;
		}
	}
	
	if (!bNeedKillTimer)
	{
		SetTimer(evtp_EpNodeTimer_Check, TP_INTERVAL_TIME_TWO_SECOND);
		m_bEpNodeCheck = TRUE;
	}
	else
	{
		KillTimer(evtp_EpNodeTimer_Check);
		m_bEpNodeCheck = FALSE;
	}
	
	return;
}

void CUmsConfInst::OnEpKedaManuProduckNotify( CTpMsg *const ptMsg )
{
	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	u8 byKedaManu;
	TP_SAFE_CAST( byKedaManu, ptMsg->GetBody()+sizeof(TUmsHandle));
	
	Hint("OnEpKedaManuProduckNotify ConfId:%d, Ep:%d, byKedaManu:%u.\n", 
		tHandle.GetConfID(), tHandle.GetEpID(), byKedaManu);
	u16 wEpId = tHandle.GetEpID();
	TCapNode* ptNode = m_pcNodeMgr->GetCapsetNode(wEpId);
	if (NULL == ptNode)
	{
		Error("OnEpKedaManuProduckNotify ptNode is NULL! ConfId:%d, Ep:%d, byKedaManu:%u.\n", 
			GetInsID(), wEpId);
		return;
	}
	
	if (!ptNode->IsCallOn() || emTpH323 != ptNode->m_emCallProtocol)
	{
		Error("OnEpKedaManuProduckNotify ptNode is not callon or not 323! ConfId:%d, Ep:%d, callon:%d, protocol:%d.\n", 
			GetInsID(), ptNode->m_wEpID, ptNode->IsCallOn(), ptNode->m_emCallProtocol);
		return;
	}
	
	ptNode->m_bIsKedaManu = TRUE;
	
	//AdjustNodeChanOn(ptNode);
	
	return;
}

void CUmsConfInst::AdjustNodeChanOn( TCapNode* ptNode )
{
// 	if ((g_bKedaManuOn && !ptNode->m_bIsKedaManu) // 渠道版本and渠道未开 
// 		|| !ptNode->m_bAdjustChanOn)
// 	{
// 		Hint("AdjustNodeChanOn is return! ConfId:%d, ep:%d, m_bIsKedaManu:%d, m_bAdjustChanOn:%d.\n",
// 			GetInsID(), ptNode->m_wEpID, ptNode->m_bIsKedaManu, ptNode->m_bAdjustChanOn);
// 		return;
// 	}
	
	TUmsHandle tHandle;
	m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
	CreateMediaToVRS_2S(ptNode);
	AdjustCapOnChanOn(tHandle, ptNode);
	return;
}

void CUmsConfInst::OnXmpuVmpConnect( CTpMsg *const ptMsg )
{
	TXmpuVmpNty tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	m_tXmpuVmpManger.Clear();
	for (u16 wIndex = 0; wIndex < tInfo.m_byNum; ++wIndex)
	{
		m_tXmpuVmpManger.m_adwVmpID[wIndex] = tInfo.m_adwEqpID[wIndex];
		m_tXmpuVmpManger.m_aemStat[wIndex] = VmpManger_Normal;
		strncpy(m_tXmpuVmpManger.m_aachEqpAlias[wIndex],tInfo.m_aachEqpAlias[wIndex], (TP_MAXLEN_EQP_ALIAS+1));
		m_tXmpuVmpManger.m_aachEqpAlias[wIndex][TP_MAXLEN_EQP_ALIAS] = '\0';
	}
	CUmsVmp::FlushXmpuVmp();
	CEqpService::Instance().FlushXmpuMpu2();
}

void CUmsConfInst::OnXmpuVmpDisConnect( CTpMsg *const ptMsg )
{
	u32 dwEqpID = 0;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());

	u16 wIndex = m_tXmpuVmpManger.GetIndex(dwEqpID);
	if (wIndex >= XMPU_MAX_VMP_NUM)
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::OnXmpuVmpDisConnect. dwEqpID:%d\n", dwEqpID));
		return ;
	}
	//断链处理
	CUmsVmp::DisConnectXmpuVmp(dwEqpID);
	CEqpService::Instance().DisconnectXmpuMpu2(dwEqpID);

	//刷新
	m_tXmpuVmpManger.ReleaseVmp(dwEqpID);
	CUmsVmp::FlushXmpuVmp();
	CEqpService::Instance().FlushXmpuMpu2();
}

void CUmsConfInst::OnXmpuVmpMdyNty( CTpMsg *const ptMsg )
{
	TXmpuVmpMdyInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	u16 wIndex = m_tXmpuVmpManger.GetIndex(tInfo.m_dwEqpID);
	if (wIndex >= XMPU_MAX_VMP_NUM)
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::OnXmpuStartVmpRsp. EqpID:%d, bSucc:%d, byVipNum:%d\n", 
								tInfo.m_dwEqpID, tInfo.m_bSuccess));
		return ;
	}

	if (m_tXmpuVmpManger.m_aemStat[wIndex] == VmpManger_Vmp)
	{
		m_pcVmp->OnXmpuVmpMdyNty(tInfo);
	}
	else if (m_tXmpuVmpManger.m_aemStat[wIndex] == VmpManger_Mpu2tp)
	{
		CEqpService::Instance().OnXmpuVmpMdyNty(this,tInfo);
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CUmsVmp::OnXmpuStartVmpRsp. EqpID:%d, emStat:%d\n", 
			tInfo.m_dwEqpID, m_tXmpuVmpManger.m_aemStat[wIndex]));
	}
}

void CUmsConfInst::OnXmpuAskKeyReq( CTpMsg *const ptMsg )
{
	TTPVmpAskFrame tAskFrame;
	TP_SAFE_CAST(tAskFrame, ptMsg->GetBody());

	u16 wIndex = m_tXmpuVmpManger.GetIndex(tAskFrame.m_byEqpID);
	if (wIndex >= XMPU_MAX_VMP_NUM)
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsConfInst::OnXmpuAskKeyReq. can not find Vmp! ConfID:%d, EqpID:%d, ChanIndx:%d\n", 
			GetInsID(), tAskFrame.m_byEqpID, tAskFrame.m_byChanIndx));
		return ;
	}

	if (m_tXmpuVmpManger.m_aemStat[wIndex] == VmpManger_Vmp)
	{
		m_pcVmp->OnVmpAskFrameToEp(ptMsg);
	}
	else if (m_tXmpuVmpManger.m_aemStat[wIndex] == VmpManger_Mpu2tp)
	{
		m_pcVmpTpHandle->XmpuAskFrame(ptMsg);
	}
	else
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsConfInst::OnXmpuAskKeyReq. can not find Vmp! ConfID:%d, EqpID:%d, emstat:%d\n", 
			GetInsID(), tAskFrame.m_byEqpID, m_tXmpuVmpManger.m_aemStat[wIndex]));
	}
}

BOOL32 CUmsConfInst::IsMtIp( const u32 dwIp )
{
	return m_pcNodeMgr->ismtip(dwIp);
}

void CUmsConfInst::OnXmpuInitMeetingNty( CTpMsg *const ptMsg )
{
#ifdef _USE_XMPUEQP_
	BOOL32 bSuccess = FALSE;
	TP_SAFE_CAST(bSuccess, ptMsg->GetBody());
	u16 wConfID = GetInsID();
	TCapNode*  ptNode = &g_atXmpuInitMeeting[wConfID-1].m_tXmpuCallerNode;
	EmCnsCallReason emReason = EmCnsCallReason_success;

	MdlHint(Ums_Mdl_Call, ("CUmsConfInst::OnXmpuInitMeetingNty ConfID:%d, bSuccess:%d, bInitMeeting:%d.\n",
		wConfID, bSuccess, g_atXmpuInitMeeting[wConfID-1].m_bInitXmpuMeeting));

	if (!g_atXmpuInitMeeting[wConfID-1].m_bInitXmpuMeeting)
	{
		return;
	}

	if (bSuccess)
	{
		if (ptNode->m_dwStackHandle != 0)
		{
			emReason = EventStartConfFromXeqp(&g_atXmpuInitMeeting[GetInsID()-1].m_tXmpuConfTempInfo,
				&g_atXmpuInitMeeting[GetInsID()-1].m_tXmpuCallerNode, g_atXmpuInitMeeting[GetInsID()-1].m_bXmpuNeedDelayCall);
		}
		else
		{
			emReason = EventStartConfFromXeqp(&g_atXmpuInitMeeting[GetInsID()-1].m_tXmpuConfTempInfo,
							NULL, g_atXmpuInitMeeting[GetInsID()-1].m_bXmpuNeedDelayCall);
		}
		
		if (emReason == EmCnsCallReason_success)
		{//开启会议成功
			g_atXmpuInitMeeting[wConfID-1].Clear();
			return;
		}
	}
	// 会议开启失败
	ReleaseXmpuMeeting(wConfID);
	// cnc呼叫
	if (ptNode->m_wEpID != 0)
	{
		TUmsHandle tHandle;
		m_pcNodeMgr->MakeCallerHandle(tHandle, ptNode->m_wEpID);
		UmsAnwserCall(tHandle, FALSE, NULL, EmCnsCallReason_resourcefull);
	}
	NotifyMsgToService(evtp_UmsConfDisConnect, &wConfID, sizeof(wConfID));

	TTPUmsReasonInd tInd;
	tInd.m_wConfID = wConfID;
	tInd.m_dwReason = TP_UMS_InitMeetingFail;
	NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd));

	g_atXmpuInitMeeting[wConfID-1].Clear();
#endif

}
void CUmsConfInst::OnXmpuRefreshVmp(CTpMsg *const ptMsg)
{
	TXmpuVmpNty tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	MdlLowDtl(Ums_Mdl_Call, ("CUmsConfInst::OnXmpuRefreshVmp Vmp:%d\n",tInfo.m_byNum));
	if (tInfo.m_byNum > XMPU_MAX_VMP_NUM )
	{
		MdlError(Ums_Mdl_Call, ("CUmsConfInst::OnXmpuRefreshVmp Update Number Error! Vmp:%d\n",tInfo.m_byNum));
		return;
	}
	//资源板卡增加
	if (tInfo.m_bIncrease)
	{
		for (u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; ++wIndex)
		{	
			if ((tInfo.m_adwEqpID[wIndex]) && (!m_tXmpuVmpManger.m_adwVmpID[wIndex]) && (VmpManger_Idle == m_tXmpuVmpManger.m_aemStat[wIndex]))
			{
				m_tXmpuVmpManger.m_adwVmpID[wIndex] = tInfo.m_adwEqpID[wIndex];
				m_tXmpuVmpManger.m_aemStat[wIndex] = VmpManger_Normal;
				strncpy(m_tXmpuVmpManger.m_aachEqpAlias[wIndex],tInfo.m_aachEqpAlias[wIndex], (TP_MAXLEN_EQP_ALIAS+1));
				m_tXmpuVmpManger.m_aachEqpAlias[wIndex][TP_MAXLEN_EQP_ALIAS] = '\0';
				MdlHint(Ums_Mdl_Call, ("CUmsConfInst::OnXmpuRefreshVmp Update Index :%d, EqpId:%d,EqpName:%s\n",wIndex, m_tXmpuVmpManger.m_adwVmpID[wIndex],m_tXmpuVmpManger.m_aachEqpAlias[wIndex]));
			}
		}
		CUmsVmp::UpdateXmpuUIVmp();
		CEqpService::Instance().UpdateXmpuMpu2();
	}
	//刷新
	else
	{
		CUmsVmp::RefreashXmpuUIVmp(tInfo.m_byNum);
	}
	
}

BOOL32 CUmsConfInst::IsAssignBasReady()
{
	if ((m_pcBas->IsSpeakBasAssigned()) && (m_pcBas->IsChairBasAssigned()))
	{
		return TRUE;
	}
	return FALSE;
}