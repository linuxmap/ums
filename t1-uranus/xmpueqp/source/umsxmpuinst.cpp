#include "umsxmpuinst.h"
#include "vmpeqp.h"
#include "vidbaseqp.h"
#include "audmixeqp.h"
#include "audbaseqp.h"
#include "eventtpsys.h"
#include "xmpuinterface.h"
#include "innereventxmpubas.h"
#include "innereventxmpuaudbas.h"
#include "innereventxmpuvmp.h"
#include "innereventxmpumix.h"
#include "jdconfig.h"
#include "umsxmltype.h"
#include "mediaerrcode.h"
#include "tplog.h"

#define min(a,b)    (((a) < (b)) ? (a) : (b))
CUmsXmpuApp g_cUmsXmpuApp;
SEMHANDLE g_SemXmpuEqp = NULL;
BOOL32	g_bXmpuInit = FALSE;
BOOL32 g_bMediaInit = TRUE;
API void npmcmsg();
void InitXmpuLib()
{
	OspSemBCreate(&g_SemXmpuEqp);
	if (NULL == g_SemXmpuEqp)
	{
		msgprint("InitEqpLib Create m_DataSem failed!\n");
	}

	g_cUmsXmpuApp.CreateApp("UmsXmpuApp",AID_UMSXMPU_APP,100, 4096);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( UMS_XMPU_APP_INST );
}

void QuitXmpuLib()
{
	if (NULL == g_SemXmpuEqp)
	{
		OspSemTake(g_SemXmpuEqp);
		OspSemDelete(g_SemXmpuEqp);
		g_SemXmpuEqp = NULL;
	}
}

u32 g_dwXmpuCheck = 0;
s8* g_pszXmpuFileName = NULL;
u32	g_dwXmpuFileLine = 0;
CXmpuSem::CXmpuSem(s8* pszPos, u32 dwLine)
{
	g_dwXmpuCheck = 1;
	g_pszXmpuFileName = pszPos;
	g_dwXmpuFileLine = dwLine;
	if (g_SemXmpuEqp != NULL)
	{
		OspSemTake(g_SemXmpuEqp);
	}
	else
	{
		msgprint("enter. CEqpSem::g_SemEqpData is null!\n");
	}
}

CXmpuSem::~CXmpuSem()
{
	g_dwXmpuCheck = 0; 
	g_pszXmpuFileName = NULL;
	g_dwXmpuFileLine = 0;
	if (g_SemXmpuEqp != NULL)
	{
		OspSemGive(g_SemXmpuEqp);
	}
	else
	{
		msgprint("quit. CEqpSem::g_SemEqpData is null!\n");
	}
}


#define _LoadEqp( classname, eqptype )\
	if( NULL == m_atEqpHandle[_##classname].m_pcHandle )\
{\
	m_atEqpHandle[_##classname].m_pcHandle = new classname(this);\
	if( NULL == m_atEqpHandle[_##classname].m_pcHandle )\
{\
	MdlError(Ums_Mdl_Eqp, ("CUmsXmpuInst::ObjectInit malloc %s Failed\n", #classname)); \
	return FALSE;\
}\
	m_atEqpHandle[_##classname].m_emEqpType = eqptype; \
	m_atEqpHandle[_##classname].m_pcHandle->Init(); \
}

CUmsXmpuInst::CUmsXmpuInst()
{

}

CUmsXmpuInst::~CUmsXmpuInst()
{
	ObjectExit();
}

BOOL CUmsXmpuInst::PreMessageProc( CMessage *const ptMsg )
{
	return FALSE;
}
u32 GetBasEqpID(u32 dwHandle);

void CUmsXmpuInst::MessageProc( CTpMsg *const ptMsg )
{
	u16 wEvent = ptMsg->GetEvent();
	if (wEvent == evXmpu_InitMetting_Rsp)
	{
		OnInitMettingRsp(ptMsg);
		return;
	}
	if (wEvent == evXmpu_StartBas_Rsp)
	{
		TXmpuStartBasCommonRsp tRes;
		TP_SAFE_CAST(tRes, ptMsg->GetBody());
		u32 dwEqpID = GetBasEqpID(tRes.m_dwHandle);
		if (dwEqpID >= XMPU_EQP_ID_BAS_BEG && dwEqpID <= XMPU_EQP_ID_BAS_END)
		{
			TXmpuStartBasRsp tResult;
			tResult.m_dwEqpID = (u8)dwEqpID;
			tResult.m_dwHandle = tRes.m_dwHandle;
			tResult.m_emRes = (tRes.m_wErrCode== ERR_CODE_NORMAL?StartBasRsp_Success:StartBasRsp_FAILD);
			tResult.m_byChnNum = tRes.m_byNum;
			for (u16 wIndex = 0; wIndex < tResult.m_byChnNum; ++wIndex)
			{
				tResult.m_abVaildChn[tRes.m_abyID[wIndex]] = TRUE;
			}

			CTpMsg cMsg;
			cMsg.SetEvent(evXmpu_StartVidBas_Rsp);
			cMsg.SetBody(&tResult,sizeof(tResult));
			m_atEqpHandle[_CVidBasEqpHandle].m_pcHandle->Handle(&cMsg);
			return;

		}
		else if (dwEqpID >= XMPU_EQP_ID_AUD_BAS_BEG && dwEqpID <= XMPU_EQP_ID_AUD_BAS_END)
		{
			TXmpuStartAudBasRsp tAudResult;
			tAudResult.m_dwEqpID = (u8)dwEqpID;
			tAudResult.m_dwHandle = tRes.m_dwHandle;
			tAudResult.m_emRes = (tRes.m_wErrCode== ERR_CODE_NORMAL?StartAudBasRsp_Success:StartAudBasRsp_FAILD);
			tAudResult.m_byChnNum = tRes.m_byNum;
			for (u16 wIndex = 0; wIndex < min(tRes.m_byNum,UMS_AUDBAS_ENC_NUM); ++wIndex)
			{
				tAudResult.m_abVaildChn[tRes.m_abyID[wIndex]] = TRUE;
			}
			CTpMsg cMsg;
			cMsg.SetEvent(evXmpu_StartAudBas_Rsp);
			cMsg.SetBody(&tAudResult,sizeof(tAudResult));
			m_atEqpHandle[_CAudioBasEqpHandle].m_pcHandle->Handle(&cMsg);
			return;
		}
		else
		{
			MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::evXmpu_StartBas_Rsp epid is invalied, epid:%d!\n", dwEqpID));
			return ;

		}

	}
	if (wEvent == evXmpu_SetBasCommonEncParam_Rsp)
	{

		TXmpuStartBasCommonRsp tRes;
		TP_SAFE_CAST(tRes, ptMsg->GetBody());
		u32 dwEqpID = GetBasEqpID(tRes.m_dwHandle);
		if (dwEqpID >= XMPU_EQP_ID_BAS_BEG && dwEqpID <= XMPU_EQP_ID_BAS_END)
		{
			TXmpuSetBasEncRsp tResult;
			u16 wIndex = 0;
			tResult.m_dwEqpID = (u8)dwEqpID;
			tResult.m_dwHandle = tRes.m_dwHandle;
			tResult.m_emRes = (tRes.m_wErrCode== ERR_CODE_NORMAL?SetBasEncRsp_Success:SetBasEncRsp_FAILD);
			tResult.m_byChnNum = tRes.m_byNum;
			for (wIndex = 0; wIndex < tResult.m_byChnNum ; ++wIndex)
			{
				tResult.m_abVaildChn[tRes.m_abyID[wIndex]] = TRUE;
			}
			CTpMsg cMsg;
			cMsg.SetEvent(evXmpu_SetBasEncParam_Rsp);
			cMsg.SetBody(&tResult,sizeof(tResult));
			m_atEqpHandle[_CVidBasEqpHandle].m_pcHandle->Handle(&cMsg);
			return;
		}
		else if (dwEqpID >= XMPU_EQP_ID_AUD_BAS_BEG && dwEqpID <= XMPU_EQP_ID_AUD_BAS_END)
		{
		TXmpuSetAudBasRsp tAudResult;
		tAudResult.m_dwEqpID = (u8)dwEqpID;
		tAudResult.m_dwHandle = tRes.m_dwHandle;
		tAudResult.m_byChnNum = tRes.m_byNum;
		tAudResult.m_emRes = (tRes.m_wErrCode== ERR_CODE_NORMAL?SetAudBasEncRsp_Success:SetAudBasEncRsp_FAILD);
		for (u16 wIndex = 0; wIndex < tRes.m_byNum; ++wIndex)
		{
			tAudResult.m_abVaildChn[tRes.m_abyID[wIndex]] = TRUE;
		}
		CTpMsg cMsg;
		cMsg.SetEvent(evXmpu_SetAudBasParam_Rsp);
		cMsg.SetBody(&tAudResult,sizeof(tAudResult));
		m_atEqpHandle[_CAudioBasEqpHandle].m_pcHandle->Handle(&cMsg);
		return;
		}
		else
		{
			MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::evXmpu_SetBasCommonEncParam_Rsp epid is invalied, epid:%d!\n", dwEqpID));
			return ;

		}

	}
	if (wEvent == evXmpu_BasCommonDisConnect_Nty)
	{
		HMEDIARES dwHandle = 0;
		TP_SAFE_CAST(dwHandle, ptMsg->GetBody());
		u32 dwEqpID = GetBasEqpID(dwHandle);
		MdlHint(Ums_Mdl_Xmpu, ("CUmsXmpuInst::evXmpu_BasCommonDisConnect_Nty epid:%d dwhandle is %d!\n", dwEqpID,dwHandle));
		if (dwEqpID >= XMPU_EQP_ID_BAS_BEG && dwEqpID <= XMPU_EQP_ID_BAS_END)
		{
			CTpMsg cMsg;
			cMsg.SetEvent(evXmpu_BasDisConnect_Nty);
			cMsg.SetBody(&dwEqpID,sizeof(dwEqpID));
			m_atEqpHandle[_CVidBasEqpHandle].m_pcHandle->Handle(&cMsg);
			return;
		}
		else if (dwEqpID >= XMPU_EQP_ID_AUD_BAS_BEG && dwEqpID <= XMPU_EQP_ID_AUD_BAS_END)
		{
			CTpMsg cMsg;
			cMsg.SetEvent(evXmpu_AudBasDisConnect_Nty);
			cMsg.SetBody(&dwEqpID,sizeof(dwEqpID));
			m_atEqpHandle[_CAudioBasEqpHandle].m_pcHandle->Handle(&cMsg);
			return;
		}
		else
		{
			MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::evXmpu_BasCommonDisConnect_Nty epid is invalied, epid:%d!\n", dwEqpID));
			return ;

		}

	}
	if (wEvent == evXmpu_AskBasKey_Req)
	{
		HMEDIARES dwHandle = 0;
		TP_SAFE_CAST(dwHandle, ptMsg->GetBody());
		u32 dwEqpID = GetBasEqpID(dwHandle);
		if (dwEqpID >= XMPU_EQP_ID_BAS_BEG && dwEqpID <= XMPU_EQP_ID_BAS_END)
		{
			CTpMsg cMsg;
			cMsg.SetEvent(evXmpu_AskBasKey_Req);
			cMsg.SetBody(&dwEqpID,sizeof(dwEqpID));
			m_atEqpHandle[_CVidBasEqpHandle].m_pcHandle->Handle(&cMsg);
			return;
		}
		else
		{
			MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::evXmpu_AskBasKey_Req epid is invalied, epid:%d!\n", dwEqpID));
			return ;

		}
	}
	if (wEvent == evXmpu_res_usd_info_req)
	{
		OnGetXmpuIdleResReq(ptMsg);
		return;
	}
	if (wEvent == evXmpu_Get_Resource_Time)
	{
		OnGetXmpuResourceTime();
		return;
	}
	if (wEvent == evXmpu_Refresh_Resource_Time)
	{
		OnRefreshXmpuResourceTime();
		return;
	}
	
	if (wEvent > segment_begin(innereventxmpuvmp) && wEvent < segment_end(innereventxmpuvmp))
	{
		m_atEqpHandle[_CVmpEqpHandle].m_pcHandle->Handle(ptMsg);
	}
	else if (wEvent > segment_begin(innereventxmpubas) && wEvent < segment_end(innereventxmpubas))
	{
		m_atEqpHandle[_CVidBasEqpHandle].m_pcHandle->Handle(ptMsg);
	}
	else if (wEvent > segment_begin(innereventxmpuaudbas) && wEvent < segment_end(innereventxmpuaudbas))
	{
		m_atEqpHandle[_CAudioBasEqpHandle].m_pcHandle->Handle(ptMsg);
	}
	else if (wEvent > segment_begin(innereventxmpumix) && wEvent < segment_end(innereventxmpumix))
	{
		m_atEqpHandle[_CAudioMixEqpHandle].m_pcHandle->Handle(ptMsg);
	}

}

BOOL32 CUmsXmpuInst::ObjectInit( u32 wParam, u32 lParam )
{
	if (m_bInit)
	{
		return TRUE;
	}

	_LoadEqp(CVmpEqpHandle, em_XmpuVmp_Eqp);
	_LoadEqp(CVidBasEqpHandle, em_XmpuVidBas_Eqp);
	_LoadEqp(CAudioMixEqpHandle, em_XmpuMix_Eqp);
	_LoadEqp(CAudioBasEqpHandle, em_XmpuAudBas_Eqp);

	m_bInit = TRUE;
	m_tEqpMgr.Clear();
	for ( u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex ++ )
	{
		m_atSynMsg[wIndex].Clear();
	}

	CTpMsg cMsg;
	cMsg.SetEvent( EVTP_RUNNING );
	cMsg.Post( UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);

	return TRUE;
}

void CUmsXmpuInst::ObjectExit()
{
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < _CEqpHandleEnd; wIndex ++ )
	{
		if ( NULL != m_atEqpHandle[wIndex].m_pcHandle )
		{
			delete m_atEqpHandle[wIndex].m_pcHandle;
		}
		m_atEqpHandle[wIndex].Clear();
	}
	for ( wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex ++ )
	{
		m_atSynMsg[wIndex].Clear();
	}
	m_tEqpMgr.Clear();
	m_bInit = FALSE;
	CUmsObject::ObjectExit();
}

void CUmsXmpuInst::InstanceDump( u32 wParam/*=0*/ )
{
	if ( wParam == dump_showxmpu )
	{
		ShowEqp();
	}
	else if( wParam == dump_showsyn)
	{
		ShowSynInfo();
	}
	else if (wParam == dump_showxmpuall)
	{
		ShowEqpAll();
	}
}

BOOL32 CUmsXmpuInst::AssignEqpEx( TXmpuEqpParam* ptEqpParam)
{
	BOOL32 bRet = FALSE;
	CEqpBaseHandle* ptHandle = GetHandle(ptEqpParam->m_emEqpType);
	if ( NULL != ptHandle )
	{
		bRet = ptHandle->AssignEqpEx(ptEqpParam);
	}

	return bRet;
}

BOOL32 CUmsXmpuInst::ReleaseEqpEx( TXmpuEqpParam* ptEqpParam )
{
	BOOL32 bRet = FALSE;
	CEqpBaseHandle* ptHandle = GetHandle(ptEqpParam->m_emEqpType);
	if ( NULL != ptHandle )
	{
		bRet = ptHandle->ReleaseEqpEx(ptEqpParam);
	}

	return bRet;
}

CEqpBaseHandle* CUmsXmpuInst::GetHandle( EMXmpuEqpType emEqp )
{
	for ( u16 wIndex = 0; wIndex < _CEqpHandleEnd; wIndex ++ )
	{
		if (m_atEqpHandle[wIndex].m_emEqpType == emEqp)
		{
			return m_atEqpHandle[wIndex].m_pcHandle;
		}
	}
	return NULL;
}

void CUmsXmpuInst::ShowEqp()
{

	msgprintnotime("Xmpu :g_bXmpuInit:%d vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264portCount:%d, 265portCount:%d\n",
		g_bXmpuInit, m_tEqpMgr.m_dw264VmpCnt, m_tEqpMgr.m_dw265_264VmpCnt, 
		m_tEqpMgr.m_dw264BasCnt, m_tEqpMgr.m_dw265_264BasCnt, m_tEqpMgr.m_dwABasCnt,
		m_tEqpMgr.m_dwMixer8Cnt, m_tEqpMgr.m_dwMixer192Cnt, m_tEqpMgr.m_dw264Port, m_tEqpMgr.m_dw265Port);
	msgprintnotime("Used:g_bXmpuInit:%d vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264portCount:%d, 265portCount:%d\n",
		g_bXmpuInit, m_tEqpMgr.m_dw264VmpUsedCnt, m_tEqpMgr.m_dw265_264VmpUsedCnt, 
		m_tEqpMgr.m_dw264BasUsedCnt, m_tEqpMgr.m_dw265_264BasUsedCnt, m_tEqpMgr.m_dwABasUsedCnt,
		m_tEqpMgr.m_dwMixer8UsedCnt, m_tEqpMgr.m_dwMixer192UsedCnt,
		m_tEqpMgr.m_dw264UsedPort, m_tEqpMgr.m_dw265UsedPort);

	for ( u16 wIndex = 0; wIndex < _CEqpHandleEnd; wIndex ++ )
	{
		if ( m_atEqpHandle[wIndex].m_pcHandle == NULL )
		{
			continue;
		}
		m_atEqpHandle[wIndex].m_pcHandle->Show();
	}
}
void CUmsXmpuInst::ShowEqpAll()
{

	msgprintnotime("Xmpu :g_bXmpuInit:%d vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264portCount:%d, 265portCount:%d\n",
		g_bXmpuInit, m_tEqpMgr.m_dw264VmpCnt, m_tEqpMgr.m_dw265_264VmpCnt, 
		m_tEqpMgr.m_dw264BasCnt, m_tEqpMgr.m_dw265_264BasCnt, m_tEqpMgr.m_dwABasCnt,
		m_tEqpMgr.m_dwMixer8Cnt, m_tEqpMgr.m_dwMixer192Cnt, m_tEqpMgr.m_dw264Port, m_tEqpMgr.m_dw265Port);
	msgprintnotime("Used:g_bXmpuInit:%d vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264portCount:%d, 265portCount:%d\n",
		g_bXmpuInit, m_tEqpMgr.m_dw264VmpUsedCnt, m_tEqpMgr.m_dw265_264VmpUsedCnt, 
		m_tEqpMgr.m_dw264BasUsedCnt, m_tEqpMgr.m_dw265_264BasUsedCnt, m_tEqpMgr.m_dwABasUsedCnt,
		m_tEqpMgr.m_dwMixer8UsedCnt, m_tEqpMgr.m_dwMixer192UsedCnt,
		m_tEqpMgr.m_dw264UsedPort, m_tEqpMgr.m_dw265UsedPort);

	for ( u16 wIndex = 0; wIndex < _CEqpHandleEnd; wIndex ++ )
	{
		if ( m_atEqpHandle[wIndex].m_pcHandle == NULL )
		{
			continue;
		}
		m_atEqpHandle[wIndex].m_pcHandle->ShowAll();
	}
}

void CUmsXmpuInst::OnInitMettingRsp( CTpMsg *const ptMsg )
{
	TXmpuInitMettingRsp	tRsp;
	TP_SAFE_CAST(tRsp, ptMsg->GetBody());

	TXmpuSynMsg* ptSyn = FindSynMsg(tRsp.m_dwConfID);
	if (NULL == ptSyn)
	{
		MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::OnInitMettingRsp. no this userdata, userdata:%d!\n", tRsp.m_dwConfID));
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CUmsXmpuInst::OnInitMettingRsp. userdata:%d, bySynNum:%d, synId:(%d|%d|%d|%d), emRes:%d!\n", 
				tRsp.m_dwConfID, tRsp.m_bySynNum, tRsp.m_adwSynID[0], tRsp.m_adwSynID[1],
				tRsp.m_adwSynID[2], tRsp.m_adwSynID[3], tRsp.m_emRes));

	if (tRsp.m_emRes != InitMettingRsp_Success)
	{
		ptSyn->Clear();
		MediaReleaseMeeting(tRsp.m_dwConfID);
		return;
	}

	ptSyn->m_bySynNum = tRsp.m_bySynNum;
	for (u16 wIndex = 0; wIndex < ptSyn->m_bySynNum; ++wIndex)
	{
		ptSyn->m_abySynInfo[wIndex].m_dwSynID = tRsp.m_adwSynID[wIndex];
	}
	
}

void CUmsXmpuInst::SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen )
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

TXmpuSynMsg* CUmsXmpuInst::FindSynMsg( u16 wConfID )
{
	for(u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		if (wConfID == m_atSynMsg[wIndex].m_wConfID)
		{
			return &m_atSynMsg[wIndex];
		}
	}
	return NULL;
}

TXmpuSynMsg* CUmsXmpuInst::FindIdleSynMsg()
{
	for(u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		if (!m_atSynMsg[wIndex].IsValidConfID())
		{
			return &m_atSynMsg[wIndex];
		}
	}
	return NULL;
}
BOOL32 CUmsXmpuInst::InitMeeting(TXmpuMettingInfo tInfo)
{
	CHECK_XMPU_SEM;
	TXmpuSynMsg* ptSyn = FindIdleSynMsg();
	if (NULL == ptSyn)
	{
		MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::InitMeeting. conf is full, confID:%d!\n", tInfo.m_wConfID ));
		return FALSE;
	}

	if (m_tEqpMgr.m_dw264BasCnt == 0 && m_tEqpMgr.m_dw264VmpCnt == 0)
	{
		return FALSE;
	}

	if (!MediaInitMeeting(tInfo))
	{
		MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::InitMeeting. initmeeting error, confID:%d!\n", tInfo.m_wConfID ));
		return FALSE;
	}

	MdlHint(Ums_Mdl_Xmpu, ("  CUmsXmpuInst::InitMeeting wConfID:%d, E164:%s, mFormat:%d,emRes:%d, wFrameRate:%d, wBitrate:%d,emQualityLvl:%d\n", 
		tInfo.m_wConfID, tInfo.m_achConfE164,tInfo.m_tFormat.m_emFormat, tInfo.m_tFormat.m_emRes, tInfo.m_tFormat.m_wFrameRate,
		tInfo.m_tFormat.m_wBitrate, tInfo.m_tFormat.m_emQualityLvl));

	ptSyn->m_wConfID = tInfo.m_wConfID;
	memcpy(ptSyn->m_achConfE164, tInfo.m_achConfE164, sizeof(ptSyn->m_achConfE164));
	memcpy(ptSyn->m_achConfName, tInfo.m_achConfName, sizeof(ptSyn->m_achConfName));
	return TRUE;
}
// 必须在销毁所有媒体业务句柄后才能调用
BOOL32 CUmsXmpuInst::ReleaseMeeting( u16 wConfID )
{
	CHECK_XMPU_SEM;

	MdlHint(Ums_Mdl_Xmpu, ("CUmsXmpuInst::ReleaseMeeting. confID:%d!\n", wConfID ));
	for ( u16 wIndex = 0; wIndex < _CEqpHandleEnd; wIndex++ )
	{
			m_atEqpHandle[wIndex].m_pcHandle->StopConf(wConfID);
	}

	TXmpuSynMsg* ptSyn = FindSynMsg(wConfID);
	if (NULL == ptSyn)
	{
		MdlError(Ums_Mdl_Xmpu, ("CUmsXmpuInst::ReleaseMeeting. conf is not find! confID:%d!\n", wConfID ));
		return FALSE;
	}

	MediaReleaseMeeting(ptSyn->m_wConfID);
	ptSyn->Clear();
	return TRUE;
}

void CUmsXmpuInst::SetSynID( u16 wConfID, EMXmpuSynType emSynIndex, TXmpuSynChn* ptSynChn )
{
	MdlHint(Ums_Mdl_Xmpu, ("CUmsXmpuInst::SetSynID. confID:%d, emSynType:%d\n", wConfID, emSynIndex));
	if (emSynIndex >= em_Xmpu_SynIndex_End || NULL == ptSynChn)
	{
		return;
	}

	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		if (m_atSynMsg[wIndex].m_wConfID == wConfID)
		{
			break;
		}
	}
	if (wIndex >= TP_UMS_MAX_CONFNUM)
	{
		return;
	}

	s8	 achBuf[TP_MAX_ALIAS_LEN+1] = {0};	//会议e164
	if (strlen(m_atSynMsg[wIndex].m_achConfE164) !=0 )
	{
		memcpy(achBuf, m_atSynMsg[wIndex].m_achConfE164, strlen(m_atSynMsg[wIndex].m_achConfE164));
	}
	else
	{
		memcpy(achBuf, m_atSynMsg[wIndex].m_achConfName, strlen(m_atSynMsg[wIndex].m_achConfName));
	}

	TXmpuSynInfo* ptInfo = &m_atSynMsg[wIndex].m_abySynInfo[emSynIndex];
	if (ptInfo->IsUsing())
	{//释放旧同步
		if (emSynIndex == em_Xmpu_Mix_SpeakerEp || emSynIndex == em_Xmpu_Mix_OtherThreeEp)
		{
			MediaMixFreeSynId(TP_MAX_STREAMNUM, ptInfo->m_atSynChn, achBuf);
		}
		else
		{
			MediaAudBasFreeSynId(TP_MAX_STREAMNUM, ptInfo->m_atSynChn, achBuf);
		}
	}

	memset(ptInfo->m_atSynChn, 0, sizeof(ptInfo->m_atSynChn));
	//添加新的同步
	if (emSynIndex == em_Xmpu_Mix_SpeakerEp || emSynIndex == em_Xmpu_Mix_OtherThreeEp)
	{
		// 参数无效释放同步参数
		if (ptSynChn[0].m_bySynChn >= XMPU_AUDMIX_N1_NUM ||
			ptSynChn[1].m_bySynChn >= XMPU_AUDMIX_N1_NUM ||
			ptSynChn[2].m_bySynChn >= XMPU_AUDMIX_N1_NUM )
		{
			
		}
		else
		{
			memcpy(ptInfo->m_atSynChn, ptSynChn, sizeof(ptInfo->m_atSynChn));
			MediaMixSetSynId(ptInfo->m_dwSynID,TP_MAX_STREAMNUM, ptInfo->m_atSynChn, achBuf);
		}
	}
	else
	{
		if (ptSynChn[0].m_dwEqpID == 0 ||
			ptSynChn[1].m_dwEqpID == 0 ||
			ptSynChn[2].m_dwEqpID == 0 )
		{

		}
		else
		{
			memcpy(ptInfo->m_atSynChn, ptSynChn, sizeof(ptInfo->m_atSynChn));
			MediaAudBasSetSynId(ptInfo->m_dwSynID,TP_MAX_STREAMNUM, ptInfo->m_atSynChn, achBuf);
		}
	}
	
}

BOOL32 CUmsXmpuInst::InitMediaClient()
{
	CHECK_XMPU_SEM;

	TJDInfo tJdInfo;
	CJDConfig::GetInstance()->GetFromConfigFile(tJdInfo); 
	g_bMediaInit = XmpuInitMediaClient(tJdInfo.m_abyMqUrl, tJdInfo.m_abyTpsMoid);
	if(!g_bMediaInit)
	{
		return FALSE;
	}
	GetMediaSource(tJdInfo.m_abyMqUrl, tJdInfo.m_abyMachineMoid, m_tEqpMgr);

	g_bXmpuInit = FALSE;
	
	SetTimer(evXmpu_Get_Resource_Time, TP_INTERVAL_TIME_THREE_SECOND);

	//关闭mc打印
	npmcmsg();
	return TRUE;
}

void CUmsXmpuInst::ShowSynInfo()
{
	TXmpuSynInfo* ptInfo = NULL;
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM;++wIndex)
	{
		if (!m_atSynMsg[wIndex].IsValidConfID())
		{
			continue;
		}

		msgprintnotime("wConfID:%d\n", m_atSynMsg[wIndex].m_wConfID);
		for (u16 wSynIndex = 0; wSynIndex < XMPU_MAX_SYN_NUM; ++wSynIndex)
		{
			ptInfo = &m_atSynMsg[wIndex].m_abySynInfo[wSynIndex];
			msgprintnotime("	SynType:%s m_dwSynID:%d ", GetSynType(wSynIndex), ptInfo->m_dwSynID);
			if (!ptInfo->IsUsing())
			{
				msgprintnotime("\n");
				continue;
			}

			msgprintnotime("  0:(EqpID:%d, chnId:%d), 1:(EqpID:%d, chnId:%d), 2:(EqpID:%d, chnId:%d)\n",
					ptInfo->m_atSynChn[0].m_dwEqpID, ptInfo->m_atSynChn[0].m_bySynChn,
					ptInfo->m_atSynChn[1].m_dwEqpID, ptInfo->m_atSynChn[1].m_bySynChn,
					ptInfo->m_atSynChn[2].m_dwEqpID, ptInfo->m_atSynChn[2].m_bySynChn);
		}

	}
}

void  CUmsXmpuInst::OnGetXmpuIdleResReq(CTpMsg *const ptMsg)
{
	EMXmpuEqpType emEqp;
	TP_SAFE_CAST(emEqp, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Xmpu, (" CUmsXmpuInst::OnGetXmpuIdleRes EqpType:%d-%s.\n", TpEnumIdString(EMXmpuEqpType, emEqp)));
	TTPBrdUsedInfo tBrdInfo;
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_res_usd_info_res);
	//OnGetUsedXmpu();
	switch(emEqp)
	{
	case em_XmpuVmp_Eqp:
		tBrdInfo.m_emType = em_vmp_tp_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dw264VmpCnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dw264VmpUsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);
		break;
	case em_XmpuAudBas_Eqp:
		tBrdInfo.m_emType = em_audbas_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dwABasCnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dwABasUsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);
		break;
	case  em_XmpuVidBas_Eqp:
		tBrdInfo.m_emType = em_bas_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dw264BasCnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dw264BasUsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);
		break;
	case em_XmpuMix_Eqp:
		tBrdInfo.m_emType = em_audmix_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dwMixer192Cnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dwMixer192UsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);
		break;
	case em_XmpuMix8_Eqp:
		tBrdInfo.m_emType = em_audmix_8_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dwMixer8Cnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dwMixer8UsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);
		break;
	default:
		tBrdInfo.m_emType = em_vmp_tp_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dw264VmpCnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dw264VmpUsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);

		tBrdInfo.m_emType = em_audbas_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dwABasCnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dwABasUsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);

		tBrdInfo.m_emType = em_bas_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dw264BasCnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dw264BasUsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);

		tBrdInfo.m_emType = em_audmix_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dwMixer192Cnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dwMixer192UsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);

		tBrdInfo.m_emType = em_audmix_8_mdl;
		tBrdInfo.m_wRegNum = m_tEqpMgr.m_dwMixer8Cnt;
		tBrdInfo.m_wUsedNum = m_tEqpMgr.m_dwMixer8UsedCnt;
		cMsg.SetBody(&tBrdInfo, sizeof(tBrdInfo));
		cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_XMPU_APP_INST);
		break;
	}

	return;
}

API void showsyn()
{
	OspInstDump(AID_UMSXMPU_APP, 1, CUmsXmpuInst::dump_showsyn);
}

API void showidlesource()
{
	TJDInfo tJdInfo;
	CJDConfig::GetInstance()->GetFromConfigFile(tJdInfo); 
	TMediaEqpMgr tEqpMgr;
	GetMediaSource(tJdInfo.m_abyMqUrl, tJdInfo.m_abyMachineMoid, tEqpMgr);

	msgprintnotime("g_bXmpuInit:%d vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264portCount:%d, 265portCount:%d\n",
		g_bXmpuInit, tEqpMgr.m_dw264VmpCnt, tEqpMgr.m_dw265_264VmpCnt, 
		tEqpMgr.m_dw264BasCnt, tEqpMgr.m_dw265_264BasCnt, tEqpMgr.m_dwABasCnt,
		tEqpMgr.m_dwMixer8Cnt, tEqpMgr.m_dwMixer192Cnt, tEqpMgr.m_dw264Port, tEqpMgr.m_dw265Port);
}

API void showxmpueqp()
{
	OspInstDump(AID_UMSXMPU_APP, 1, CUmsXmpuInst::dump_showxmpu);
}
API void showxmpusem()
{
	msgprintnotime("g_dwXmpuCheck = %d\n",g_dwXmpuCheck);
	msgprintnotime("g_dwXmpuFileLine = %d\n",g_dwXmpuFileLine);
	if (NULL == g_pszXmpuFileName)
	{
		msgprintnotime("g_pszXmpuFileName is null\n");
	}
	else
	{
		msgprintnotime("g_pszXmpuFileName is %s\n", g_pszXmpuFileName);
	}
}
API void showxmpumap()
{
	ShowVmpMap();
	ShowBasMap();
	ShowMixMap();
}
API void xmputime(BOOL32 bStart)
{
	CUmsXmpuInst* pInst = (CUmsXmpuInst*)((CApp*)&g_cUmsXmpuApp)->GetInstance(1);
	pInst->XmpuTime(bStart);
}
API void showxmpuall()
{
	OspInstDump(AID_UMSXMPU_APP, 1, CUmsXmpuInst::dump_showxmpuall);
}

void regist_ums_xmpueqp_commond()
{
#ifdef _LINUX_
	OspRegCommand("showxmpueqp", (void*)showxmpueqp, "showxmpueqp()");
	OspRegCommand("showidlesource", (void*)showidlesource, "showidlesource()");
	OspRegCommand("showxmpusem", (void*)showxmpusem, "showxmpusem(int)");
	OspRegCommand("showsyn", (void*)showsyn, "showsyn()");
	OspRegCommand("showxmpumap", (void*)showxmpumap, "showxmpumap()");	
	OspRegCommand("xmputime", (void*)xmputime, "xmputime()");	
	OspRegCommand("showxmpuall", (void*)showxmpuall, "showxmpuall()");
#endif
}

void CUmsXmpuInst::OnGetUsedXmpu()
{
	TJDInfo tJdInfo;
	CJDConfig::GetInstance()->GetFromConfigFile(tJdInfo); 
	TMediaEqpMgr tEqpIdle;
	GetMediaSource(tJdInfo.m_abyMqUrl, tJdInfo.m_abyMachineMoid, tEqpIdle);
	u16 wVmpUsedNum = m_atEqpHandle[_CVmpEqpHandle].m_pcHandle->OnGetUsedNum();
	u16 wVidBasUsedNum = m_atEqpHandle[_CVidBasEqpHandle].m_pcHandle->OnGetUsedNum();
	u16 wAudBasUsedNum = m_atEqpHandle[_CAudioBasEqpHandle].m_pcHandle->OnGetUsedNum();
	u16 wMix192UsedNum = m_atEqpHandle[_CAudioMixEqpHandle].m_pcHandle->OnGetUsedNum();
	u16 wMix8UsedNum = ((CAudioMixEqpHandle*)(m_atEqpHandle[_CAudioMixEqpHandle].m_pcHandle))->OnGetMix8UsedNum();
	BOOL32 bIncrease = FALSE;
	if (tEqpIdle.IsNoIdleSource())
	{
		MdlHint(Ums_Mdl_Xmpu, (" CUmsXmpuInst::OnGetUsedXmpu No Idle Resource\n"));
		memset(&m_tEqpMgr,0, sizeof(TMediaEqpMgr));
	}
	else
 	{
		if ((tEqpIdle.m_dw264VmpCnt + tEqpIdle.m_dw265_264VmpCnt) > m_tEqpMgr.m_dwVmpInitCnt)
		{
			//增加VMP资源
			MdlHint(Ums_Mdl_Xmpu, (" CUmsXmpuInst::OnGetUsedXmpu Increase Vmp Resource\n"));
			bIncrease = TRUE;
			m_tEqpMgr.SetVmpInitCnt(tEqpIdle.m_dw264VmpCnt + tEqpIdle.m_dw265_264VmpCnt);

		}
		//刷新资源

		//264vmp
		m_tEqpMgr.m_dw264VmpUsedCnt = wVmpUsedNum;
		m_tEqpMgr.m_dw264VmpCnt = tEqpIdle.m_dw264VmpCnt +  tEqpIdle.m_dw265_264VmpCnt +wVmpUsedNum;
		m_tEqpMgr.m_dw265_264VmpCnt = tEqpIdle.m_dw265_264VmpCnt;

		//264vidbas
		m_tEqpMgr.m_dw264BasUsedCnt = wVidBasUsedNum;
		m_tEqpMgr.m_dw264BasCnt = tEqpIdle.m_dw264BasCnt + tEqpIdle.m_dw265_264BasCnt +wVidBasUsedNum;
		m_tEqpMgr.m_dw265_264BasCnt = tEqpIdle.m_dw265_264BasCnt;

		//audbas
		m_tEqpMgr.m_dwABasUsedCnt = wAudBasUsedNum;
		m_tEqpMgr.m_dwABasCnt = tEqpIdle.m_dwABasCnt + wAudBasUsedNum;


		//mix 192
		m_tEqpMgr.m_dwMixer192UsedCnt = wMix192UsedNum;
		m_tEqpMgr.m_dwMixer192Cnt = tEqpIdle.m_dwMixer192Cnt + wMix192UsedNum;

		//mix8
		m_tEqpMgr.m_dwMixer8UsedCnt = wMix8UsedNum;
		m_tEqpMgr.m_dwMixer8Cnt = tEqpIdle.m_dwMixer8Cnt + wMix8UsedNum;

		m_tEqpMgr.m_dw264Port = tEqpIdle.m_dw264Port;
		m_tEqpMgr.m_dw264UsedPort = 0;
		m_tEqpMgr.m_dw265Port = tEqpIdle.m_dw265Port;
		m_tEqpMgr.m_dw265UsedPort = 0;

	}

	((CVmpEqpHandle*)(m_atEqpHandle[_CVmpEqpHandle].m_pcHandle))->ReFreshVmpState(bIncrease, (tEqpIdle.m_dw264VmpCnt + tEqpIdle.m_dw265_264VmpCnt));

	MdlLowDtl(Ums_Mdl_Xmpu,( "Xmpu Source: vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264port:%d, 265port:%d\n",
		m_tEqpMgr.m_dw264VmpCnt, m_tEqpMgr.m_dw265_264VmpCnt, 
		m_tEqpMgr.m_dw264BasCnt, m_tEqpMgr.m_dw265_264BasCnt, m_tEqpMgr.m_dwABasCnt,
		m_tEqpMgr.m_dwMixer8Cnt, m_tEqpMgr.m_dwMixer192Cnt,
		m_tEqpMgr.m_dw264Port ,m_tEqpMgr.m_dw265Port));
	MdlLowDtl(Ums_Mdl_Xmpu,("Xmpu Used :vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264port:%d, 265port:%d\n",
		m_tEqpMgr.m_dw264VmpUsedCnt, m_tEqpMgr.m_dw265_264VmpUsedCnt, 
		m_tEqpMgr.m_dw264BasUsedCnt, m_tEqpMgr.m_dw265_264BasUsedCnt, m_tEqpMgr.m_dwABasUsedCnt,
		m_tEqpMgr.m_dwMixer8UsedCnt, m_tEqpMgr.m_dwMixer192UsedCnt,
		m_tEqpMgr.m_dw264UsedPort, m_tEqpMgr.m_dw265UsedPort));
	return;
}


void CUmsXmpuInst::OnGetXmpuResourceTime()
{
	MdlHint(Ums_Mdl_Xmpu, (" CUmsXmpuInst::OnGetXmpuResouceTime.\n"));
	TJDInfo tJdInfo;
	CJDConfig::GetInstance()->GetFromConfigFile(tJdInfo); 
	TMediaEqpMgr tEqpIdle;
	GetMediaSource(tJdInfo.m_abyMqUrl, tJdInfo.m_abyMachineMoid, tEqpIdle);
	if (tEqpIdle.IsNoIdleSource())
	{
		MdlHint(Ums_Mdl_Xmpu, (" CUmsXmpuInst::OnGetXmpuResouceTime No Idle Resource\n"));
		KillTimer(evXmpu_Get_Resource_Time);
		SetTimer(evXmpu_Get_Resource_Time, TP_INTERVAL_TIME_THREE_SECOND);
	}
	else
	{
		if (m_tEqpMgr == tEqpIdle)
		{
			g_bXmpuInit = TRUE;
			m_tEqpMgr = tEqpIdle;
			m_tEqpMgr.SetVmpInitCnt(tEqpIdle.m_dw264VmpCnt + tEqpIdle.m_dw265_264VmpCnt);
			KillTimer(evXmpu_Get_Resource_Time);
			((CVmpEqpHandle*)(m_atEqpHandle[_CVmpEqpHandle].m_pcHandle))->UpdateVmpState(m_tEqpMgr.m_dw264VmpCnt + m_tEqpMgr.m_dw265_264VmpCnt);
			SetTimer(evXmpu_Refresh_Resource_Time, TP_INTERVAL_TIME_FIVE_SECOND);
		}
		else
		{
			m_tEqpMgr = tEqpIdle;
			KillTimer(evXmpu_Get_Resource_Time);
			SetTimer(evXmpu_Get_Resource_Time, TP_INTERVAL_TIME_THREE_SECOND);
		}
	}

	
	MdlLowDtl(Ums_Mdl_Xmpu, (" CUmsXmpuInst::OnGetXmpuResouceTime vmp264count:%d, vmp265count:%d, vidbas264Count:%d, vidbas265Count:%d, audCount:%d, mix8Count:%d, mix192Count:%d, 264portCount:%d, 265portCount:%d\n",
		m_tEqpMgr.m_dw264VmpCnt, m_tEqpMgr.m_dw265_264VmpCnt, 
		m_tEqpMgr.m_dw264BasCnt, m_tEqpMgr.m_dw265_264BasCnt, m_tEqpMgr.m_dwABasCnt,
		m_tEqpMgr.m_dwMixer8Cnt, m_tEqpMgr.m_dwMixer192Cnt, m_tEqpMgr.m_dw264Port, m_tEqpMgr.m_dw265Port));

}

void CUmsXmpuInst::OnRefreshXmpuResourceTime()
{
	MdlLowDtl(Ums_Mdl_Xmpu, (" CUmsXmpuInst::OnRefreshXmpuResourceTime.\n"));
	OnGetUsedXmpu();
	KillTimer(evXmpu_Refresh_Resource_Time);
	SetTimer(evXmpu_Refresh_Resource_Time, TP_INTERVAL_TIME_FIVE_SECOND);
}

void CUmsXmpuInst::XmpuTime(BOOL32 bStart)
{
	if (bStart)
	{
		SetTimer(evXmpu_Refresh_Resource_Time, TP_INTERVAL_TIME_FIVE_SECOND);
	}
	else
	{
		g_bXmpuInit = TRUE;
		KillTimer(evXmpu_Get_Resource_Time);
		KillTimer(evXmpu_Refresh_Resource_Time);
	}	
}
