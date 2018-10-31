#include "umsaudmix.h"
#include "umsnetportmgr.h"
#include "eventoutumscall.h"
#include "eventoutsipadapter.h"
#include "umsstackinterface.h"
#include "nodefsm.h"
#include "umsbas.h"
#include "dualmgr.h"
#include "tperrno.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpumix.h"
#endif

inline s8* GetUmsMixModeName(EmUmsAudMixMode emMode)
{
	switch (emMode)
	{
	case em_umsaudmixmode_idle:
		{
			return "idle";
		}
	case em_umsaudmixmode_smart:
		{
			return "smart";
		}
	case em_umsaudmixmode_custom:
		{
			return "custom";
		}
	default:
		{
			return "error";
		}
	}
}

void UmsAudMixCB(u32 dwType, void* param1, void* param2)
{
#ifdef _USE_XMPUEQP_
    tXmpuMixCbData* ptCbData = (tXmpuMixCbData* )param1;
    CUmsConfInst*	pInst = (CUmsConfInst*)ptCbData->pService;
	if (pInst)
	{
		CUmsAudMixMgr* ptMgr = pInst->GetAudMix();
		if (ptMgr)
		{
			ptMgr->XmpuMixCB(dwType, (TAudMixInfo*)ptCbData->pRes, ptCbData->pData);
		}
	}

#else
	TAudMixInfo::EmCBOprType emType = (TAudMixInfo::EmCBOprType)dwType;
	TAudMixInfo* ptMixInfo = (TAudMixInfo*)param1;
	CUmsAudMixMgr* ptMgr = NULL;

	CUmsConfInst* pInst =  (CUmsConfInst*)param2;
	if (pInst)
	{
         CUmsAudMixMgr* ptMgr = pInst->GetAudMix();
		 if (ptMgr)
		 {
	          ptMgr->MixCB(emType, ptMixInfo);
		 }
	}
	
#endif
	return;
}

void CUmsAudMixMgr::Enter()
{
	ResetData();
	m_tMixListUI.Clear();
}

void CUmsAudMixMgr::Exit()
{	
}

void CUmsAudMixMgr::ResetData()
{
	m_emMixMode = em_umsaudmixmode_idle;
	m_tMixEqp.Clear();
	m_tMixEpInfoList.Clear();
	m_tMixLocalList.Clear();
	Inst()->GetPutAudMgr()->ReleaseAll(em_putauduser_audmix);
}

// TTPMediaTransAddr
#define UmsAudMixPrintAddr(Addr) if (1){\
	msgprintnotime("      Rtp("ADDRPORT_FORMAT"), BackRtcp("ADDRPORT_FORMAT")\n"\
	, ADDRNET(Addr.m_tRtpAddr), ADDRNET(Addr.m_tBackRtcpAddr));}

void CUmsAudMixMgr::Show()
{
	CUmsConfInst* pInst = Inst();
	u16	wIndex = 0;
	msgprintnotime("\n");
	msgprintnotime("[CumsAudMixMgr]	conf:%d, mode:%s.\n", pInst->GetInsID(), GetUmsMixModeName(m_emMixMode));
	
//	if (em_umsaudmixmode_idle == m_emMixMode)
	{
		msgprintnotime("  [MixListUI] num:%d.\n", m_tMixListUI.m_wNum);
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			if (TP_INVALID_INDEX == m_tMixListUI.m_awMixEp[wIndex])
			{
				continue;
			}
			msgprintnotime("    index:%d, ep:%d.\n", wIndex, m_tMixListUI.m_awMixEp[wIndex]);
		}
	}
//	else
	{
		msgprintnotime("  [MixListLocal] num:%d.\n", m_tMixLocalList.m_wNum);
		for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			if (TP_INVALID_INDEX == m_tMixLocalList.m_awMixEp[wIndex])
			{
				continue;
			}
			msgprintnotime("    index:%d, ep:%d.\n", wIndex, m_tMixLocalList.m_awMixEp[wIndex]);
		}
	}

	msgprintnotime("\n");
	msgprintnotime("  [MixEpInfoList] limitnum:%d, num:%d.\n", m_tMixEpInfoList.m_wLimitNum, m_tMixEpInfoList.m_wNum);
	TUmsAudMixEpInfo* ptEp = NULL;
	for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		ptEp = &m_tMixEpInfoList.m_atAudMixEp[wIndex];
		if (!ptEp->IsValid())
		{
			continue;
		}

		msgprintnotime("    [MixEp] Index:%d, EpID:%d, ThreeAudEp:%d.\n", ptEp->m_wIndex, ptEp->m_wEpID, ptEp->m_bThreeAudEp);		
		
		if (ptEp->m_wGetindex < TP_UMS_MAX_CALLNUM)
		{
			msgprintnotime("    [GetAud] Getindex:%d, MediaNode:%d, AudAddr:\n", ptEp->m_wGetindex, ptEp->m_dwMediaNode);
			UmsAudMixPrintAddr(ptEp->m_tAudAddr);
		}
	
		if (!ptEp->m_bLocalEp || !pInst->IsChairConf())
		{
			msgprintnotime("    [PutAud] LocalEp:%d, PudAddr:\n", ptEp->m_bLocalEp);
			UmsAudMixPrintAddr(ptEp->m_atPutAuddr[MIDSCREENINDEX]);
		}
	}

	msgprintnotime("\n");
	msgprintnotime("  [MixEqp].\n");
	pInst->GetEapu()->ShowMixInfo(m_tMixEqp.m_ptMixRes);
	
	msgprintnotime("\n");
	msgprintnotime("  [PutAudMgr].\n");
	pInst->GetPutAudMgr()->Show();
	msgprintnotime("\n[CUmsAudMixMgr Info] End!\n");
}

BOOL32 CUmsAudMixMgr::HandlerFromStack( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case evtp_CNS_UMS_ConfAudMixMode_cmd:
		{
			OnAudMixModeCmdFromCns(ptMsg);
		}
		break;

	case evtp_CNS_UMS_ConfAudMixList_cmd:
		{
			OnAudMixListCmdFromCns(ptMsg);
		}
		break;

	case evtp_UMS_UMS_ConfAudMixMode_Notify:
		{
			OnCasecadeNotify(ptMsg);
		}
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL32 CUmsAudMixMgr::HandlerFromUmc( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case evtp_ConfAudMixMode_cmd:
		{
			OnAudMixModeCmdFromUmc(ptMsg);
		}
		break;
	case evtp_ConfAudMixList_cmd:
		{
			OnAudMixListCmdFromUmc(ptMsg);
		}
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL32 CUmsAudMixMgr::AssignMixRes()
{
	BOOL32 bRet = TRUE;
	if (NULL == m_tMixEqp.m_ptMixRes)
	{
		m_tMixEqp.m_ptMixRes = Inst()->GetEapu()->AssignMixer(UmsAudMixCB, Inst());
		if (NULL == m_tMixEqp.m_ptMixRes)
		{
			bRet = FALSE;
		}
		m_tMixEpInfoList.m_wLimitNum = m_tMixEqp.GetTotalChanNum();

		tpHint(Ums_Mdl_Call, "[CUmsAudMixMgr::AssignMixRes] ConfID:%d, AssignMixRes chan:%d.\n", m_pcConf->GetInsID(), m_tMixEpInfoList.m_wLimitNum);

	}
	return bRet;
}

void CUmsAudMixMgr::ResetConfAudMix()
{
	CUmsConfInst* pInst = Inst();
	if (NULL != m_tMixEqp.m_ptMixRes)
	{
		pInst->GetEapu()->ReleaseMixer(m_tMixEqp.m_ptMixRes);
		if (0 != m_tMixEqp.m_cToMixDsInfo.GetElementNum())
		{
			CNetPortMgr::FreeMediaTrans(pInst, m_tMixEqp.m_cToMixDsInfo);
		}
	}
	ResetData();
}

#ifdef _USE_XMPUEQP_
void CUmsAudMixMgr::XmpuMixCB(u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData)
{
	TXmpuStartMixNty  tStartInfo;
    TXmpuAddMixMemNty tAddMemInfo;

	BOOL32 bStopAudMix = FALSE;

    if (dwEvent == evXmpu_UmsStartMix_Nty)
	{
        memcpy(&tStartInfo, pData, sizeof(tStartInfo));
		if (!tStartInfo.m_bSuccess)
		{
            bStopAudMix = TRUE;
		}
	} else if (dwEvent == evUms_XmpuAddMixMember_Nty)
	{
         memcpy(&tAddMemInfo, pData, sizeof(TXmpuAddMixMemNty));
		 if (!tAddMemInfo.m_bSuccess)
		 {
             bStopAudMix = TRUE;
		 }
	} else if (dwEvent == evXmpu_VacActive_Ntf)
	{

	} else if (dwEvent == evXmpu_MixVoiceDetection_Ntf)
	{

	} else if (dwEvent == evXmpu_MixDisConnect_Nty)
	{
         bStopAudMix = TRUE;
	}

	if (bStopAudMix)
	{
		tpError(Ums_Mdl_Call, "[CUmsAudMixMgr::XmpuMixCB] ConId:%d, CBType:%d(startfail:%d, addmemfail:%d, discon:%d ) StopAudMix\n", 
			   Inst()->GetInsID(), dwEvent, evXmpu_UmsStartMix_Nty, evUms_XmpuAddMixMember_Nty, evXmpu_MixDisConnect_Nty);

		StopAudMixMode();
		m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_MIX_ERROR, m_pcConf->chairID());
		
		NotifyAudMixMode();
	}
}

#else
void CUmsAudMixMgr::MixCB( TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo )
{
	if (NULL == ptMixInfo)
	{
		return;
	}
	
	tpError(Ums_Mdl_Call, "[MixCB] ConId:%d, EqpId:%d, CBType:%d\n", 
		Inst()->GetInsID(), ptMixInfo->m_tEqpRes.m_byEqpID, emType);
	
	StopAudMixMode();
	m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_MIX_ERROR, m_pcConf->chairID());

	NotifyAudMixMode();

	return;
}
#endif

void CUmsAudMixMgr::OnAudMixModeCmdFromCns(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TUmsAudMixInfo tAudMix;
	TP_SAFE_CAST( tAudMix, ptMsg->GetBody()+sizeof(TUmsHandle));
	


	TUmsAudMixModeCmdRes tRes;
	tRes.m_wConfId = tAudMix.m_wConfId;
	tRes.m_emCmdMode = tAudMix.m_emMode;

	do 
	{
		if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
		{
			
			tpError(Ums_Mdl_Call, "[OnAudMixModeCmdFromCns] ConfID:%d, start confaudmix  CmdMode:%d (0-idle, 1-smart, 2-custom), unauthorized.\n", 
				    pInst->GetInsID(),  tAudMix.m_emMode);

			tRes.m_emRes = em_umsaudmixres_unauthorized;
			break ;
		}

		tpHint(Ums_Mdl_Call, "[OnAudMixModeCmdFromCns] ConfID:%d, EpNum:%d, CmdMode:%d (0-idle, 1-smart, 2-custom), CurrentMode:%d (0-idle, 1-smart, 2-custom).\n", 
			pInst->GetInsID(), tAudMix.m_tMixList.m_wNum, tAudMix.m_emMode, m_emMixMode);
		
		OnAudMixModeCmdFromUmcCnc(tAudMix, tRes);
		
	} while (0);


	tpHint(Ums_Mdl_Call, "[OnAudMixModeCmdFromCns] ConfID:%d, start confaudmix  CmdMode:%d (0-idle, 1-smart, 2-custom), ret:%d.\n", 
		   pInst->GetInsID(),  tAudMix.m_emMode, tRes.m_emRes);


	//回复umc 操作结果
	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, evtp_UMS_CNS_ConfAudMixMode_ind, &tRes, sizeof(TUmsAudMixModeCmdRes));

	NotifyAudMixMode();


}


void CUmsAudMixMgr::OnAudMixModeCmdFromUmc( CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TUmsAudMixInfo tAudMix;
	TP_SAFE_CAST( tAudMix, ptMsg->GetBody()+sizeof(TLogUser));


	tpHint(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmc] ConfID:%d, EpNum:%d, CmdMode:%d (0-idle, 1-smart, 2-custom), CurrentMode:%d (0-idle, 1-smart, 2-custom).\n", 
		pInst->GetInsID(), tAudMix.m_tMixList.m_wNum, tAudMix.m_emMode, m_emMixMode);



	TUmsAudMixModeCmdRes tRes;
	tRes.m_wConfId = tAudMix.m_wConfId;
	tRes.m_emCmdMode = tAudMix.m_emMode;
	OnAudMixModeCmdFromUmcCnc(tAudMix, tRes);


	tpHint(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmc] ConfID:%d, start confaudmix  CmdMode:%d (0-idle, 1-smart, 2-custom), ret:%d.\n", 
		pInst->GetInsID(),  tAudMix.m_emMode, tRes.m_emRes);

		//回复umc 操作结果
	pInst->NotifyMsgToServiceForUI(evtp_ConfAudMixMode_ind, &tRes, sizeof(tRes), &tLogUser);

	NotifyAudMixMode();


	return;
}


void CUmsAudMixMgr::OnAudMixListCmdFromCns(CTpMsg* const ptMsg)
{
	CUmsConfInst* pInst = Inst();

	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TUmsAudMixListCmd tAudMix;
	TP_SAFE_CAST( tAudMix, ptMsg->GetBody()+sizeof(TUmsHandle));
	
	
    TUmsAudMixListCmdRes tRes;
    tRes.m_wConfId = tAudMix.m_wConfId;
    tRes.m_tList = tAudMix.m_tList;
	
	do 
	{
		if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
		{
			tpError(Ums_Mdl_Call, "[OnAudMixListCmdFromCns] ConfID:%d, update confaudmix list unauthorized.\n", pInst->GetInsID());

			tRes.m_aemRes[0] = em_umsaudmixres_unauthorized;
			break ;
		}
		
        tpHint(Ums_Mdl_Call, "[OnAudMixListCmdFromCns] ConfID:%d, EpNum:%d, CmdType:%d (0-add, 1-del), CurrentMode:%d (0-idle, 1-smart, 2-custom).\n", 
 		      pInst->GetInsID(), tAudMix.m_tList.m_wNum, tAudMix.m_emOpr, m_emMixMode);

	    OnAudMixListCmdFromUmcCnc(tAudMix, tRes);
		
	} while (0);
	
	
	//回复主席 操作结果
	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, evtp_UMS_CNS_ConfAudMixList_ind, &tRes, sizeof(TUmsAudMixListCmdRes));

	NotifyAudMixMode();

}



void CUmsAudMixMgr::OnAudMixListCmdFromUmc( CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TUmsAudMixListCmd tAudMix;
	TP_SAFE_CAST( tAudMix, ptMsg->GetBody()+sizeof(TLogUser));

	tpHint(Ums_Mdl_Call, "[OnAudMixListCmdFromUmc] ConfID:%d, EpNum:%d, CmdType:%d (0-add, 1-del), CurrentMode:%d (0-idle, 1-smart, 2-custom).\n", 
		pInst->GetInsID(), tAudMix.m_tList.m_wNum, tAudMix.m_emOpr, m_emMixMode);

	TUmsAudMixListCmdRes tRes;
	tRes.m_wConfId = tAudMix.m_wConfId;
	tRes.m_tList = tAudMix.m_tList;
	OnAudMixListCmdFromUmcCnc(tAudMix, tRes);


	//回复umc 操作结果
	pInst->NotifyMsgToServiceForUI(evtp_ConfAudMixList_ind, &tRes, sizeof(tRes), &tLogUser);

	NotifyAudMixMode();
	return;
}

void CUmsAudMixMgr::OnAudMixModeCmdFromUmcCnc(TUmsAudMixInfo& tInfo, TUmsAudMixModeCmdRes& tRes )
{
	CUmsConfInst* pInst = Inst();

	if (!pInst->IsChairConf())
	{
		tpError(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix opr  not chairconf.\n", pInst->GetInsID());
		tRes.m_emRes = em_umsaudmixres_unauthorized;
		return;
	}

    if (em_umsaudmixmode_smart == tInfo.m_emMode || em_umsaudmixmode_custom == tInfo.m_emMode)
	{
		if (pInst->GetUmsDiscuss()->IsUIDiscussOn())
		{
			tpError(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix  fail  now is discuss mode.\n", pInst->GetInsID());
			tRes.m_emRes = em_umsaudmixres_dismode;
			return;
		}
		
		if (pInst->GetRollCallMgr()->IsUIRollCallOn())
		{
			tpError(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix  fail  now is rollcall mode.\n", pInst->GetInsID());
			tRes.m_emRes = em_umsaudmixres_rollcallmode;
			return;
		}
	}


	if (tInfo.m_emMode == m_emMixMode)
	{
		tpError(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix  fail  the same mode %d.\n", pInst->GetInsID(), m_emMixMode);
		tRes.m_emRes = em_umsaudmixres_samemode;
		return;
	}

	if (em_umsaudmixmode_idle == tInfo.m_emMode)
	{
		tpHint(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmcCnc] ConfID:%d, user stop audmix.......\n", pInst->GetInsID());
		StopAudMixMode();
		tRes.m_emRes = em_umsaudmixres_sucess;
	}
	else
	{
		if (em_umsaudmixmode_idle == m_emMixMode)
		{

			tpHint(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmcCnc] ConfID:%d, audmix start mod:%d(0-idle, 1-smart, 2-custom) \n", pInst->GetInsID(), tInfo.m_emMode);

			//判断是否有可用的媒体资源
			if (!CheckIdleMediaSource(0, 0, SINGLE_NUMBER))
			{
				tRes.m_emRes= em_umsaudmixres_start_nomix;
				MdlError(Ums_Mdl_Call, ("[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix no idle mixer source.\n", pInst->GetInsID()));
				return;
			}


			if (!AssignMixRes())
			{
				tpError(Ums_Mdl_Call, "[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix no mixer.\n", pInst->GetInsID());
				tRes.m_emRes = em_umsaudmixres_start_nomix;
				return;
			}
		}
		
		tRes.m_emRes = StartAudMixMode(tInfo);
		if (em_umsaudmixres_sucess == tRes.m_emRes)
		{
			tpHint(Ums_Mdl_Call, "\n[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix  success mod:%d(0-idle, 1-smart, 2-custom)......\n\n",
				   pInst->GetInsID(), tInfo.m_emMode);
			AdjustAudMixMode();
		}
		else
		{
			tpError(Ums_Mdl_Call, "\n[OnAudMixModeCmdFromUmcCnc] ConfID:%d, start audmix  fail mod:%d(0-idle, 1-smart, 2-custom), ret:%d\n\n",
				   pInst->GetInsID(), tInfo.m_emMode, tRes.m_emRes);

			StopAudMixMode();
			m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_STOP_NO_EP, m_pcConf->chairID());

		}
	}

	return;
}

void CUmsAudMixMgr::OnAudMixListCmdFromUmcCnc( const TUmsAudMixListCmd& tCmd, TUmsAudMixListCmdRes& tRes )
{
	CUmsConfInst* pInst = Inst();

	if (m_emMixMode == em_umsaudmixmode_smart)
	{// 智能混音模式，不准添删
		tpError(Ums_Mdl_Call, "[OnAudMixListCmdFromUmcCnc] ConfID:%d, smart mod not allow add list.\n", pInst->GetInsID());
		return;
	}
	
	if (m_emMixMode == em_umsaudmixmode_idle)
	{// 非混音模式，替界面保存列表
		tpHint(Ums_Mdl_Call, "[OnAudMixListCmdFromUmcCnc] ConfID:%d, confaudmix mode idle,just update eplist.\n", pInst->GetInsID());
		OnAudMixListFromUIUpdate(tCmd, tRes);
		return;
	}


    u16 wAddtoMixFailCt  = 0;
	u16 wIndex = 0;
	u16 wEp = 0;
	if (tCmd.m_emOpr == em_umsaudmixlistopr_add)
	{
		for (wIndex = 0; wIndex < tCmd.m_tList.m_wNum; wIndex++)
		{
			wEp = tCmd.m_tList.m_awMixEp[wIndex];			
			tRes.m_aemRes[wIndex] = AddEpToMixChan(wEp);
			if (em_umsaudmixres_sucess == tRes.m_aemRes[wIndex])
			{
				m_tMixListUI.AddID(wEp);
			} else if (em_umsaudmixres_add_mixchanfull == tRes.m_aemRes[wIndex])
			{
                wAddtoMixFailCt++;
			}
		}

		if (wAddtoMixFailCt > 0)
		{
			m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_MIXCHAN_FULL, m_pcConf->chairID());
		}

		AdjustAudMixMode();
	}
	else if (tCmd.m_emOpr == em_umsaudmixlistopr_del)
	{
		for (wIndex = 0; wIndex < tCmd.m_tList.m_wNum; wIndex++)
		{
			wEp = tCmd.m_tList.m_awMixEp[wIndex];

            if (wEp == pInst->curSpeakerID())
			{
				m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_DELETE_SPEAKER, m_pcConf->chairID());
                tRes.m_aemRes[wIndex] = em_umsaudmixres_sucess;
				continue;
			}

			tRes.m_aemRes[wIndex] = DelEpFromMixChan(wEp);
			if (em_umsaudmixres_sucess == tRes.m_aemRes[wIndex])
			{
				m_tMixListUI.DelId(wEp);
			}
		}

		if (0 == m_tMixLocalList.m_wNum)
		{
			StopAudMixMode();
			m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_STOP_NO_EP, m_pcConf->chairID());
		}
		else
		{
			AdjustAudMixMode();
		}
	}
	else
	{
		// 无需处理
	}

	tpHint(Ums_Mdl_Call, "[OnAudMixListCmdFromUmcCnc] ConfID:%d update audmix ep list success.\n", pInst->GetInsID());

	return;
}

inline void ShowMixMember( TAudMixMemberInfo* ptMixInfo )
{	
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 != ptMixInfo->m_awEpId[wIndex])
		{
			msgprintnotime("<%d-%d> ",ptMixInfo->m_awEpId[wIndex], ptMixInfo->m_awScrIndx[wIndex]);
		}
	}
	msgprintnotime("\n");
	return;
}

void CUmsAudMixMgr::GetNewMixMember( TAudMixMemberInfo& tNewMixMember )
{
	tNewMixMember.Clear();
	TUmsAudMixEpInfo* ptEp = NULL;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		ptEp = &m_tMixEpInfoList.m_atAudMixEp[wIndex];
		if (ptEp->IsValid())
		{
			tNewMixMember.AddMixMember(ptEp->m_wEpID, TP_MAX_STREAMNUM);
		}
	}

#ifdef _WIN32
	ShowMixMember(&tNewMixMember);
#endif

	return;
}


void CUmsAudMixMgr::CheckDualMixChan()
{
	u16 wDualMixNum  = m_pcConf->GetSpeaker().m_ptAudMix->m_tEqpRes.m_wChanNum;
	u16 wConfMixChanNum = m_tMixEqp.GetTotalChanNum();

	u16 wMinMixChan = wDualMixNum < wConfMixChanNum ?wDualMixNum : wConfMixChanNum;

	wMinMixChan = wMinMixChan - 1;//1: 可用的通道还要减一个双流通道

	if (m_tMixLocalList.m_wNum  > wMinMixChan)
	{ 
        RemoveSomeEpFromMixChan(m_tMixLocalList.m_wNum - wMinMixChan);

		// 重新调整到会议混音的MIX 的交换
        CreatAudToConfAudMix();
	}
 
	return;
}



void CUmsAudMixMgr::CreatAudToConfAudMix()
{
	//if (em_umsaudmixmode_idle == m_emMixMode || NULL == m_tMixEqp.m_ptMixRes)
	//{
	//	return;
	//}


	//CUmsConfInst* pInst = Inst();
	//if (!pInst->IsChairConf())
	//{
	//	return;
	//}


	TAudMixMemberInfo tMixMember;
	GetNewMixMember(tMixMember);
	m_pcConf->GetEapu()->AdjustAudMixMember(m_tMixEqp.m_ptMixRes, &tMixMember);
	
	// update to mix ds
	CNetPortMgr::AdjustEpAudToMixDs(m_pcConf, &m_tMixEqp, &tMixMember);


	return;
}


void CUmsAudMixMgr::CreatToDulAudMix(u16 wDualEp)
{
	TAudMixMemberInfo tInfo;

	TCallNode* ptDualNode = Inst()->GetNode(wDualEp);
	if (NULL != ptDualNode && ptDualNode->IsChanOn() && 
		emTPAEnd != ptDualNode->m_tDualAudSndFormat.m_tFormat.m_emFormat)
	{
		tInfo.AddMixMember(wDualEp, TP_MAX_STREAMNUM+1);
	}

	TUmsAudMixEpInfo* ptEp = NULL;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		ptEp = &m_tMixEpInfoList.m_atAudMixEp[wIndex];
		if (ptEp->IsValid())
		{
			tInfo.AddMixMember(ptEp->m_wEpID, TP_MAX_STREAMNUM);
		}
	}

	m_pcConf->GetEapu()->AdjustAudMixMember(m_pcConf->GetSpeaker().m_ptAudMix, &tInfo);
	
	// 点名人 + 被点名人 + 双流
	CNetPortMgr::AdjustConfMixToDulMixer(m_pcConf, &tInfo);
}



void CUmsAudMixMgr::AdjustAudMixMode()
{
	if (em_umsaudmixmode_idle == m_emMixMode || NULL == m_tMixEqp.m_ptMixRes)
	{
		return;
	}

	CUmsConfInst* pInst = Inst();
	if (!pInst->IsChairConf())
	{
		return;
	}


    CreatAudToConfAudMix();

	AdjustAllNodeToUmsAudMix();


	return;
}

void CUmsAudMixMgr::StopAudMixMode()
{	
	CUmsConfInst* pInst = Inst();

	m_emMixMode = em_umsaudmixmode_idle;

	TUmsAudMixEpInfo* ptEp = NULL;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		ptEp = &m_tMixEpInfoList.m_atAudMixEp[wIndex];
		if (ptEp->IsValid())
		{
			DelEpFromMixChan(ptEp->m_wEpID);
		}
	}

	ResetConfAudMix();

	AdjustAllNodeToUmsAudMix();

	return;
}

EmUmsAudMixRes CUmsAudMixMgr::StartAudMixMode(TUmsAudMixInfo& tInfo )
{
	if (tInfo.m_emMode == em_umsaudmixmode_idle)
	{
		tpHint(Ums_Mdl_Call, "[StartAudMixMode] Confid:%d  Never Get here, someting wrong\n", m_pcConf->GetInsID());
		return em_umsaudmixres_unkown;
	}

	if (tInfo.m_emMode == em_umsaudmixmode_custom && 0 == tInfo.m_tMixList.m_wNum)
	{
		return em_umsaudmixres_start_novalidep;
	}

	CUmsConfInst* pInst = Inst();

	u16 wIndex = 0;
	u16 wEp = 0;
	TUmsAudMixEpInfo* ptEp = NULL;

	u16 wAddtoMixFailCt  = 0;
	EmUmsAudMixRes  emAddToMixRet = em_umsaudmixres_sucess;

	if (tInfo.m_emMode == em_umsaudmixmode_smart)
	{// 智能混音
		m_tMixListUI.Clear();
		AdjustAllEpToMixChan(wAddtoMixFailCt);
	}
	else
	{// 定制混音
		if (0 == tInfo.m_tMixList.m_wNum)
		{
			tInfo.m_tMixList.AddID(pInst->curSpeakerID());
		}

		if (m_emMixMode == em_umsaudmixmode_smart)
		{// 之前是智能混音，先把不在list中的，从mixchan中删掉

			tpHint(Ums_Mdl_Call, "[StartAudMixMode] Confid:%d  Changemod from smart to custom\n", m_pcConf->GetInsID());

			for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
				ptEp = &m_tMixEpInfoList.m_atAudMixEp[wIndex];
				if (!ptEp->IsValid())
				{
					continue;
				}
				if (!tInfo.m_tMixList.IsInList(ptEp->m_wEpID))
				{
					DelEpFromMixChan(ptEp->m_wEpID);
				}
			}
		}

		m_tMixListUI = m_tMixLocalList;
		for (wIndex = 0; wIndex < tInfo.m_tMixList.m_wNum; wIndex++)
		{
			wEp = tInfo.m_tMixList.m_awMixEp[wIndex];
			emAddToMixRet = AddEpToMixChan(wEp);
			if (em_umsaudmixres_sucess == emAddToMixRet)
			{
				m_tMixListUI.AddID(wEp);
			}
			else if (em_umsaudmixres_add_mixchanfull == emAddToMixRet)
			{
				tpHint(Ums_Mdl_Call, "[StartAudMixMode] Confid:%d  add ep:%d to mix fail, mix chan full\n",
					   m_pcConf->GetInsID(), wEp);

                wAddtoMixFailCt++;
			}
		}

		if (0 == m_tMixLocalList.m_wNum)
		{
			return em_umsaudmixres_start_novalidep;
		}
	}


	if (wAddtoMixFailCt > 0)
	{
		m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_MIXCHAN_FULL, m_pcConf->chairID());
	}

	m_emMixMode = tInfo.m_emMode;


	return em_umsaudmixres_sucess;
}

EmUmsAudMixRes CUmsAudMixMgr::AddEpToMixChan(u16 wEp)
{
	CUmsConfInst* pInst = Inst();
	
	tpHint(Ums_Mdl_Call, "[AddEpToMixChan] Confid:%d  add ep:%d  to mix chan,.\n", pInst->GetInsID(), wEp);

	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEp);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode 
		|| (!ptNode->IsMtEp() && !ptFatherNode->IsMcu()) 
		|| !ptNode->IsAudSndValid() 
		||  (ptFatherNode->IsMcu() && ptNode!=ptFatherNode))
	{// （合并级联）mcu下级的会场不进入混音，mcu可以进入混音
		tpError(Ums_Mdl_Call, "[AddEpToMixChan] Confid:%d, add ep:%d to mix fail  ptnode(%p) ptfathernode(%p) ismt(%d) issndvalid(%d) ismcu(%d).\n",
			    pInst->GetInsID(), 
				wEp,
				ptNode, 
				ptFatherNode,
				(ptNode==NULL)? 65535: ptNode->IsMtEp(),
				(ptNode==NULL)? 65535: ptNode->IsAudSndValid(),
		        (ptFatherNode==NULL)? 65535:ptFatherNode->IsMcu());
		return em_umsaudmixres_add_invalidep;
	}

	if (NULL != m_tMixEpInfoList.GetEp(wEp))
	{// 已经在里面，不重复添加
		tpError(Ums_Mdl_Call, "[AddEpToMixChan] add ep :%d to mix fail (repeatadd).\n", pInst->GetInsID(), wEp);
		return em_umsaudmixres_add_repeatadd;
	}

	TUmsAudMixEpInfo* ptEp = m_tMixEpInfoList.AddEp(ptNode);
	if (NULL == ptEp || !ptEp->IsValid())
	{
		tpError(Ums_Mdl_Call, "[AddEpToMixChan] add ep :%d to mix fail (mixchanfull).\n", pInst->GetInsID(), wEp);
		return em_umsaudmixres_add_mixchanfull;
	}

	TGetVidAddr tAddr;
	EmGetVidRes emRes = pInst->GetVidAudEx()->AssignByScreen(m_pcConf, ptNode->m_wEpID, MIDSCREENINDEX, em_GetVid_OnlyAud,
		TCallVidFormat(), FALSE, tAddr, ptEp->m_wGetindex);
	if (emRes != em_GetVid_Success)
	{
		DelEpFromMixChan(wEp);
		tpError(Ums_Mdl_Call, "[AddEpToMixChan] add ep :%d to mix fail (getaudfail).\n", pInst->GetInsID(), wEp);
		return em_umsaudmixres_add_getaudfail;
	}

	ptEp->SetGetAudAddr(tAddr);

	if (ptNode != ptFatherNode)
	{
		if (!pInst->GetPutAudMgr()->AssignAudChnl(ptNode->m_wEpID, em_putauduser_audmix, ptEp->m_atPutAuddr))
		{
			DelEpFromMixChan(wEp);
			tpError(Ums_Mdl_Call, "[AddEpToMixChan] add ep :%d to mix fail (assignaudfail).\n", pInst->GetInsID(), wEp);
			return em_umsaudmixres_add_assignaudfail;
		}
		ptEp->m_bLocalEp = FALSE;
	}

	m_tMixLocalList.AddID(wEp);

    //通知对应会场进入会议混音
    NotifyIsEpInAudMix(wEp, TRUE);
	
	return em_umsaudmixres_sucess;
}

EmUmsAudMixRes CUmsAudMixMgr::DelEpFromMixChan( u16 wEp )
{
	CUmsConfInst* pInst = Inst();

	tpHint(Ums_Mdl_Call, "[DelEpFromMixChan] Confid:%d  delete ep :%d \n", pInst->GetInsID(), wEp);

	TUmsAudMixEpInfo* ptEp = m_tMixEpInfoList.GetEp(wEp);
	if (NULL == ptEp)
	{
		tpError(Ums_Mdl_Call, "[DelEpFromMixChan] Confid:%d  ep:%d umsaudmixres_del_notfind \n", pInst->GetInsID(), wEp);
		return em_umsaudmixres_del_notfind;
	}

	if (!ptEp->m_bLocalEp)
	{
		pInst->GetPutAudMgr()->ReleaseAudChnl(wEp, em_putauduser_audmix);
		CNetPortMgr::FreeMediaTrans(pInst, ptEp->m_cToPutAuddrDsInfo);
		ptEp->ClearPutAuddr();
	}

	if (ptEp->m_wGetindex < TP_UMS_MAX_CALLNUM)
	{
		pInst->GetVidAudEx()->Release(pInst, ptEp->m_wGetindex);
		ptEp->ClearGetAudAddr();
	}

	m_tMixEpInfoList.DelEp(wEp);

	m_tMixLocalList.DelId(wEp);


	//通知对应会场退出会议混音
	NotifyIsEpInAudMix(wEp, FALSE);

	return em_umsaudmixres_sucess;
}

void CUmsAudMixMgr::AdjustAllEpToMixChan(u16 &wEpAddFailCt)
{
	CUmsConfInst* pInst = Inst();
	wEpAddFailCt = 0;
	if (!pInst->IsChairConf())
	{
		return;
	}

	if (em_umsaudmixres_add_mixchanfull == AddEpToMixChan(pInst->curSpeakerID()))
	{

		tpHint(Ums_Mdl_Call, "[AdjustAllEpToMixChan] Confid:%d  add speaker(%d) to mix full, RemoveSomeEpFromMixChan.\n",
			                 pInst->GetInsID(), pInst->curSpeakerID());

        wEpAddFailCt++;
		RemoveSomeEpFromMixChan(1);
		AddEpToMixChan(pInst->curSpeakerID());
	}

	if (pInst->chairID() != pInst->curSpeakerID())
	{

		if (em_umsaudmixres_add_mixchanfull == AddEpToMixChan(pInst->chairID()))
		{
			tpHint(Ums_Mdl_Call, "[AdjustAllEpToMixChan] Confid:%d  add chair(%d) to mix full, RemoveSomeEpFromMixChan.\n",
			                 pInst->GetInsID(), pInst->chairID());

			wEpAddFailCt++;
			RemoveSomeEpFromMixChan(1);
			AddEpToMixChan(pInst->chairID());
		}
	}
	
	u16 wIndex = 0;
	u16 awChildEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpChildNum = 0;
	TCallNode* ptChildNode = NULL;
	for (TCapNode* ptNode = pInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pInst->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsAudSndValid())
		{
			tpError(Ums_Mdl_Call, "[AdjustAllEpToMixChan] Confid:%d  add ep:%d fail, chanon:%d, audsndvalid:%d.\n", 
				  pInst->GetInsID(), ptNode->m_wEpID, ptNode->IsCallOn(), ptNode->IsAudSndValid());
			continue;
		}

		if (ptNode->IsMtEp())
		{
			if (m_tMixEpInfoList.GetIdleNum() > 0)
			{
                AddEpToMixChan(ptNode->m_wEpID);
			}
			else 
			{
				tpError(Ums_Mdl_Call, "[AdjustAllEpToMixChan] Confid:%d  add ep:%d fail, mix chan full.\n", pInst->GetInsID(), ptNode->m_wEpID);
				wEpAddFailCt++;
			}
			
			continue;
		}
		
		if (ptNode->IsUms())
		{
			wEpChildNum = pInst->GetNodeMgr()->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, (TCallNode*)ptNode);
			for (wIndex = 0; wIndex < wEpChildNum; wIndex++)
			{

				ptChildNode = pInst->GetNodeMgr()->GetNode(awChildEpID[wIndex]);
				if (NULL != ptChildNode && ptChildNode->IsMtEp() && ptChildNode->IsAudSndValid())
				{
					if (m_tMixEpInfoList.GetIdleNum() > 0)
					{
                         AddEpToMixChan(ptChildNode->m_wEpID);
					} 
					else 
					{
						tpHint(Ums_Mdl_Call, "[AdjustAllEpToMixChan] Confid:%d  add child ep:%d fail, mix chan full.\n", pInst->GetInsID(), ptChildNode->m_wEpID);
                         wEpAddFailCt++;
					}

				}
			}
		}
	}
}

void CUmsAudMixMgr::RemoveSomeEpFromMixChan( u16 wNum )
{// 不删主会场和发言会场
	u16 wDelNum = wNum;
	if (0 == wDelNum)
	{
		return;
	}

	CUmsConfInst* pInst = Inst();
	TUmsAudMixEpInfo* ptEp = NULL;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 == wDelNum)
		{
			break;
		}
		ptEp = &m_tMixEpInfoList.m_atAudMixEp[wIndex];
		if (ptEp->IsValid() && ptEp->m_wEpID != pInst->chairID() && ptEp->m_wEpID != pInst->curSpeakerID())
		{
			DelEpFromMixChan(ptEp->m_wEpID);
			wDelNum--;
		}
	}
	return;
}

void CUmsAudMixMgr::OnAudMixListFromUIUpdate( const TUmsAudMixListCmd& tCmd, TUmsAudMixListCmdRes& tRes )
{
	if (m_emMixMode == em_umsaudmixmode_idle)
	{ 
		if (tCmd.m_emOpr == em_umsaudmixlistopr_add)
		{
			u16 wEp = 0;
			for (u16 wIndex = 0; wIndex < tCmd.m_tList.m_wNum; wIndex++)
			{
				wEp = tCmd.m_tList.m_awMixEp[wIndex];
				tRes.m_aemRes[wIndex] = m_tMixListUI.AddID(wEp)?em_umsaudmixres_sucess:em_umsaudmixres_unkown;
			}
		}
		else if (tCmd.m_emOpr == em_umsaudmixlistopr_del)
		{
			u16 wEp = 0;
			for (u16 wIndex = 0; wIndex < tCmd.m_tList.m_wNum; wIndex++)
			{
				wEp = tCmd.m_tList.m_awMixEp[wIndex];
				m_tMixListUI.DelId(wEp);
				tRes.m_aemRes[wIndex] = em_umsaudmixres_sucess;
			}
		}
		else
		{
			// 无需处理
		}
	}
}


void CUmsAudMixMgr::GetConfAudMixStateInfo(TUmsAudMixInfo& tNotify)
{
	tNotify.m_wConfId = m_pcConf->GetInsID();
	tNotify.m_emMode = m_emMixMode;
	tNotify.m_tMixList = em_umsaudmixmode_smart == m_emMixMode?m_tMixLocalList:m_tMixListUI;

	return;
}

void CUmsAudMixMgr::NotifyAudMixMode()
{
	CUmsConfInst* pInst = Inst();
	TUmsAudMixInfo tNotify;

	GetConfAudMixStateInfo(tNotify);

	// 通知主席
	Inst()->NotifyConfCtrlMsgToCns(evtp_UMS_CNS_ConfAudMixMode_Notify,  Inst()->chairID(), &tNotify, sizeof(tNotify));
	
	// 通知umc
	Inst()->NotifyMsgToServiceForUI(evtp_ConfAudMixMode_Notify, &tNotify, sizeof(tNotify));
}



void CUmsAudMixMgr::NotifyIsEpInAudMix(u16 wEpId, BOOL32 bIsInAudMix)
{
	TCallNode* ptNotifyNode     = m_pcConf->m_pcNodeMgr->GetNode(wEpId);
	TCapNode*  ptNotifyForether = m_pcConf->m_pcNodeMgr->GetForeFatherNode(ptNotifyNode);

	if (NULL == ptNotifyForether)
	{
		tpError(Ums_Mdl_Call, "[NotifyIsEpInAudMix] Confid:%d  EP:%d NotifyIsEpInAudMix fail.\n", m_pcConf->GetInsID(), wEpId);
        return;
	}

   	TUmsHandle tOutHandle;
	if(ptNotifyForether == ptNotifyNode)
	{
		m_pcConf->m_pcNodeMgr->MakeCallerHandle(tOutHandle, wEpId);
		UmsSendConfCtrl(tOutHandle, evtp_UMS_CNS_EpInAudMix_Notify, &bIsInAudMix, sizeof(bIsInAudMix));
	}

	return;
}


void CUmsAudMixMgr::OnStopConf()
{
	CUmsConfInst* pInst = Inst();

	if ( !pInst->IsChairConf() )
	{
		Enter();
		return;
	}
	
	if (m_emMixMode != em_umsaudmixmode_idle)
	{
		StopAudMixMode();
	}
	Enter();

	return;
}

void CUmsAudMixMgr::OnChanConnect( TCallNode* ptNode )
{
	CUmsConfInst* pInst = Inst();

	tpHint(Ums_Mdl_Call, "[CUmsAudMixMgr::OnChanConnect] Confid:%d  ep:%d ChanConnect.\n", pInst->GetInsID(), ptNode->m_wEpID);

	if ( !pInst->IsChairConf() )
	{// 非上级不处理
		return;
	}

	if (m_emMixMode == em_umsaudmixmode_idle)
	{
		return;
	}
	

	EmUmsAudMixRes  emAddToMixRet = em_umsaudmixres_sucess;


	if (m_emMixMode == em_umsaudmixmode_custom &&  ptNode->m_wEpID == pInst->curSpeakerID())
	{
        m_tMixListUI.AddID(ptNode->m_wEpID);
	}


    BOOL32 bAddSuc = FALSE;
	if (m_emMixMode == em_umsaudmixmode_smart || (m_tMixListUI.IsInList(ptNode->m_wEpID)))
	{// 智能混音，或者定制混音的情形下，在UI列表中，尝试加进来

		emAddToMixRet = AddEpToMixChan(ptNode->m_wEpID);
		if (em_umsaudmixres_sucess == emAddToMixRet)
		{
			bAddSuc = TRUE;

		} else if (em_umsaudmixres_add_mixchanfull == emAddToMixRet)
		{
			if ( ptNode->m_wEpID == pInst->curSpeakerID())
			{
				tpHint(Ums_Mdl_Call, "[CUmsAudMixMgr::OnChanConnect] Confid:%d  add speaker(%d) to mix full, RemoveSomeEpFromMixChan.\n", 
					  pInst->GetInsID(), pInst->curSpeakerID());
				
				RemoveSomeEpFromMixChan(1);
		        AddEpToMixChan(pInst->curSpeakerID());
				bAddSuc = TRUE;
			}
			else
			{
				m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_MIXCHAN_FULL, m_pcConf->chairID());
			}
		}
	}


    if (bAddSuc)
	{
		AdjustAudMixMode();
        NotifyAudMixMode();
	} else if (ptNode->m_wEpID == Inst()->chairID())
	{
        NotifyAudMixMode();
	}


	return;
}

void CUmsAudMixMgr::OnHungUpNode( TCallNode* ptNode, EmCnsCallReason emReason /*= EmCnsCallReason_success*/ )
{
	CUmsConfInst* pInst = Inst();

	tpHint(Ums_Mdl_Call, "[CUmsAudMixMgr::OnHungUpNode] Confid:%d  ep:%d HungUpNode.\n", pInst->GetInsID(), ptNode->m_wEpID);

	if (pInst->m_bIsQuiting)
	{// 正在退出，不处理
		return;
	}

	if (m_emMixMode == em_umsaudmixmode_idle)
	{
		return;
	}

	if (!pInst->IsChairConf())
	{
		m_tMixEpInfoList.DelEp(ptNode->m_wEpID);
		return;
	}

	if (ptNode->IsUms())
	{
		TUmsAudMixEpInfo* ptEpInfo = NULL;
		BOOL32  bAdjust = FALSE;
		u16 awChildEpID[TP_CONF_MAX_CNSNUM];
		u16 wEpChildNum = pInst->GetNodeMgr()->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, ptNode);
		for (u16 wI = 0; wI < wEpChildNum; ++wI)
		{
			ptEpInfo = m_tMixEpInfoList.GetEp(awChildEpID[wI]);
			if (NULL != ptEpInfo)
			{
				DelEpFromMixChan(ptEpInfo->m_wEpID);
				bAdjust = TRUE;
			}
		}
        
		if (m_emMixMode == em_umsaudmixmode_custom && m_tMixLocalList.m_wNum == 0)
		{   //定制混音 如会场都掉线了，则停止会议混音
            StopAudMixMode();
			m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_STOP_NO_EP, m_pcConf->chairID());

			NotifyAudMixMode();
			return;
		}

		if (bAdjust)
		{
			AdjustAudMixMode();
			NotifyAudMixMode();
		}
		return;
	}

	if (m_emMixMode == em_umsaudmixmode_custom && (emReason == EmCnsCallReason_hungup || emReason == EmCnsCallReason_peerhungup))
	{// 主动挂断的，从定制混音的UI列表中删除
		m_tMixListUI.DelId(ptNode->m_wEpID);
	}


	EmUmsAudMixRes emRet = DelEpFromMixChan(ptNode->m_wEpID);
	if (m_emMixMode == em_umsaudmixmode_custom && m_tMixLocalList.m_wNum == 0)
	{   //定制混音 如会场都掉线了，则停止会议混音
		StopAudMixMode();
		m_pcConf->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_CONFAUDMIX_STOP_NO_EP, m_pcConf->chairID());

		NotifyAudMixMode();
		return;
	}

	if (em_umsaudmixres_sucess == emRet)
	{
		AdjustAudMixMode();
		NotifyAudMixMode();
	}

	return;
}

void CUmsAudMixMgr::ChangeSpeaker( TCallNode* ptSpeakerNode )
{
	CUmsConfInst* pInst = Inst();
	
	if ( !pInst->IsChairConf() || NULL == ptSpeakerNode)
	{// 非上级不处理
		return;
	}
	
	if (m_emMixMode == em_umsaudmixmode_idle)
	{
		return;
	}

	u16 wOldSpeaker = pInst->oldSpeakerID();
	if (m_emMixMode == em_umsaudmixmode_custom)
	{// 定制混音切换发言会场，删掉老的发言人，添加新的发言人
        
		m_tMixListUI.DelId(wOldSpeaker);
        m_tMixListUI.AddID(ptSpeakerNode->m_wEpID);

		DelEpFromMixChan(wOldSpeaker);
		AddEpToMixChan(ptSpeakerNode->m_wEpID);
		AdjustAudMixMode();
		NotifyAudMixMode();
	}
	else
	{
		if (NULL == m_tMixEpInfoList.GetEp(ptSpeakerNode->m_wEpID))
		{// 新的发言人不在混音通道中，加进去
			if (0 == m_tMixEpInfoList.GetIdleNum())
			{// 通道不足，踢掉一个
				RemoveSomeEpFromMixChan(1);
			}
			AddEpToMixChan(ptSpeakerNode->m_wEpID);
			AdjustAudMixMode();
			NotifyAudMixMode();
		}
	}

	return;
}

void CUmsAudMixMgr::OpenEpDownAudCmd( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	if (pInst->IsChairConf())
	{
		return;
	}

	TVidChanCmd* ptVidCmd = (TVidChanCmd*)(ptMsg->GetBody() + sizeof(TUmsHandle));
	
	EmPutAudUser emUser = (EmPutAudUser)ptVidCmd->m_atUpRtp[1].m_tAddr.m_wPort;
	if (em_putauduser_audmix != emUser)
	{
		return;
	}
	
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(ptVidCmd->m_tEpKey.m_wEpID);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{
		return;
	}
	
	tpHint(Ums_Mdl_Call, "[OpenEpDownAudCmd] ConfID:%d, wEpID:%d, emUser:%d.\n", pInst->GetInsID(), ptNode->m_wEpID, emUser);
	
	TUmsAudMixEpInfo* ptEpInfo = m_tMixEpInfoList.AddEpForLowUms(ptNode);
	if (NULL == ptEpInfo)
	{
		return;
	}
	
	pInst->GetPutAudMgr()->GetAudLocalAddr(ptNode->m_wEpID, em_putauduser_audmix, ptEpInfo->m_atPutAuddr);


    // 打开到该下级会场的音频通道，说明该下级会场在混音中
	NotifyIsEpInAudMix(ptNode->m_wEpID, TRUE);
	
	return;
}

void CUmsAudMixMgr::OpenEpDownAudAck( CTpMsg *const ptMsg )
{
	if (Inst()->IsChairConf())
	{
		TUmsHandle tInHandle = *(TUmsHandle*)(ptMsg->GetBody());
		TVidChanAck tVidAck = *(TVidChanAck*)(ptMsg->GetBody() + sizeof(TUmsHandle));
		
		EmPutAudUser emUser = tVidAck.m_atUpBackRtcp[1].m_tAddr.m_wPort;
		if (em_putauduser_audmix != emUser)
		{
			return;
		}
		
		TCapNode* ptForeNode = Inst()->GetNodeMgr()->GetCapsetNode(tInHandle.GetEpID());
		if ( NULL == ptForeNode )
		{
			return ;
		}
		
		//不是本级结点，则取得该会场的本级EpID
		if ( ptForeNode->IsUms() )
		{
			TCallNode* ptNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tVidAck.m_tEpKey.m_wEpID);
			if ( NULL == ptNode || !ptNode->m_bUsed )
			{
				return ;
			}
			tVidAck.m_tEpKey.m_wEpID = ptNode->m_wEpID;
		}
		
		tpHint(Ums_Mdl_Call, "[OpenEpDownAudAck] ConfID:%d, wEpID:%d, emUser:%d.\n", Inst()->GetInsID(), tVidAck.m_tEpKey.m_wEpID, emUser);
		
		TUmsAudMixEpInfo* ptEpInfo = m_tMixEpInfoList.GetEp(tVidAck.m_tEpKey.m_wEpID);
		if (NULL != ptEpInfo && tVidAck.m_wReason != TP_RET_OK)
		{
			DelEpFromMixChan(ptEpInfo->m_wEpID);

			if (0 == m_tMixLocalList.m_wNum)
			{
				tpError(Ums_Mdl_Call, "[OpenEpDownAudAck] ConfID:%d, put aud down fail.\n", Inst()->GetInsID());
				StopAudMixMode();
			}
			else
			{
				AdjustAudMixMode();
			}

			NotifyAudMixMode();
		}
	}
}

void CUmsAudMixMgr::CloseEpDownAudCmd( CTpMsg *const ptMsg )
{
	if (Inst()->IsChairConf())
	{
		return;
	}

	u16 wEpID;
	u32	dwType;
	TP_SAFE_CAST( wEpID, ptMsg->GetBody() + sizeof(TUmsHandle));
	TP_SAFE_CAST( dwType, ptMsg->GetBody() + sizeof(TUmsHandle) + sizeof(u16));
	
	EmPutAudUser emUser = (EmPutAudUser)dwType;
	if (emUser != em_putauduser_audmix)
	{
		return;
	}
	
	tpHint(Ums_Mdl_Call, "[CloseEpDownAudCmd] ConfID:%d, wEpID:%d, user:%d.\n", Inst()->GetInsID(), wEpID, emUser);
	
	TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(wEpID);
	if (NULL == ptNode)
	{
		return;
	}

	m_tMixEpInfoList.DelEp(wEpID);

	
	// 关闭到该下级会场的音频通道，说明该下级会场退出混音
	NotifyIsEpInAudMix(wEpID, FALSE);

	return;
}



void CUmsAudMixMgr::PutAudDown()
{
	CUmsConfInst* pInst = Inst();

	u16 awChildEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpChildNum = 0;
	TCallNode* ptChildNode = NULL;
	TUmsAudMixEpInfo* ptEpInfo = NULL;
	

	for (TCapNode* ptNode = pInst->GetNodeMgr()->FirstNode(); ptNode != NULL; ptNode = pInst->GetNodeMgr()->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}
		
		if (ptNode->IsUms() && ptNode->m_wEpID != pInst->chairID())
		{//
			
			if (pInst->IsChairConf() && m_emMixMode != em_umsaudmixmode_idle)
			{// 最上级将n-1模式音频码流下传
				wEpChildNum = pInst->GetNodeMgr()->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, (TCallNode*)ptNode);
				for (u16 wIndex = 0; wIndex < wEpChildNum; wIndex++)
				{
					ptEpInfo = m_tMixEpInfoList.GetEp(awChildEpID[wIndex]);
					if (NULL != ptEpInfo && !ptEpInfo->m_bThreeAudEp)
					{   //单屏才PUT

						CNetPortMgr::PutMixAudToLowUmsEp(pInst, ptEpInfo);
					}
				}
			}
		}
		
		
	}
}


void CUmsAudMixMgr::AdjustAllNodeToUmsAudMix()
{
	CUmsConfInst* pInst = Inst();
	if (pInst->m_bIsQuiting)
	{
		return;
	}
	
	CNetPortMgr::CreateSpeakerToVirSpeaker(pInst);
	//调整音频适配，如果发言人为三屏，开启混音，需要取消同步；退出混音，也需要恢复同步
	Inst()->GetBas()->AdjustSpeakerAudBas();


	TUmsHandle tHandle;
	TUmsAudMixCasecadeInfo tNotify;
	tNotify.m_emMode = m_emMixMode;

	u16 wIndex = 0;
	u16 awChildEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpChildNum = 0;
	TCallNode* ptChildNode = NULL;
	TUmsAudMixEpInfo* ptEpInfo = NULL;

	for (TCapNode* ptNode = pInst->GetNodeMgr()->FirstNode(); ptNode != NULL; ptNode = pInst->GetNodeMgr()->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}

		if (ptNode->IsUms() && ptNode->m_wEpID != pInst->chairID())
		{//

			if (pInst->IsChairConf() && m_emMixMode != em_umsaudmixmode_idle)
			{// 最上级将n-1模式音频码流下传
				wEpChildNum = pInst->GetNodeMgr()->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, (TCallNode*)ptNode);
				for (wIndex = 0; wIndex < wEpChildNum; wIndex++)
				{
					ptEpInfo = m_tMixEpInfoList.GetEp(awChildEpID[wIndex]);
					if (NULL != ptEpInfo)
					{
						CNetPortMgr::PutMixAudToLowUmsEp(pInst, ptEpInfo);
					}
				}
			}

			pInst->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			UmsSendConfCtrl(tHandle, evtp_UMS_UMS_ConfAudMixMode_Notify, &tNotify, sizeof(tNotify));
		}

		pInst->GetNodeFsm()->UpdateMediaTrans(ptNode);

	}
	
	return ;
}

void CUmsAudMixMgr::OnCasecadeNotify( CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TUmsAudMixCasecadeInfo tNtfy;	
	TP_SAFE_CAST(tNtfy, ptMsg->GetBody() + sizeof(TUmsHandle));
	
	tpHint(Ums_Mdl_Call, "[OnCasecadeNotify] ConfID:%d, NtfyModle:%d, NowModle:%d.\n",
		pInst->GetInsID(), tNtfy.m_emMode, m_emMixMode);

	m_emMixMode = tNtfy.m_emMode;

	if (m_emMixMode == em_umsaudmixmode_idle)
	{
		Enter();
	}

	AdjustAllNodeToUmsAudMix();

	return;
}


void CUmsAudMixMgr::GetMixEpAudSndAddr( u16 wEpId,  TServiceAddr& tAddr)
{
	// 清空
	tAddr.Clear();

	TUmsAudMixEpInfo* ptEp = m_tMixEpInfoList.GetEp(wEpId);
	if (NULL != ptEp)
	{
		tAddr.m_tAddr = ptEp->m_tAudAddr;
		tAddr.m_dwMediaNode = ptEp->m_dwMediaNode;
	}
	return;
}

void CUmsAudMixMgr::GetMixAudRcvAddrForMixEp( TUmsAudMixEpInfo* ptEp, TServiceAddr& tAddr)
{
	// 清空
	tAddr.Clear();

	CUmsConfInst* pInst = Inst();
	if (NULL != ptEp)
	{// 在混音列表，取n-1
		if (pInst->IsChairConf())
		{
			if (!ptEp->m_bThreeAudEp && pInst->GetSpeaker().m_bIsDualMixOn)
			{// 双流开启的情形下，给单屏的地址，这里的地址要包含双流音频，to do...
                 
				pInst->GetEapu()->GetMixerChnOutAddr(pInst->GetSpeaker().m_ptAudMix, tAddr, ptEp->m_wEpID, TP_MAX_STREAMNUM);

			}
			else
			{
				pInst->GetEapu()->GetMixerChnOutAddr(m_tMixEqp.m_ptMixRes, tAddr, ptEp->m_wEpID, TP_MAX_STREAMNUM);
			}
		}
		else
		{
			tAddr.m_tAddr.m_tRtpAddr = ptEp->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
			tAddr.m_tAddr.m_tBackRtcpAddr = ptEp->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
			tAddr.m_dwMediaNode = pInst->GetConfEqpDs().m_dwEqpNode;
		}
	}
}

void CUmsAudMixMgr::GetMixNModeRcvAddr(TUmsAudFormat& tFormat, TServiceAddr& tAddr, BOOL32 bToSingle)
{// 因为下级没有混音器，所以下级取的n模式只有级联音频格式一种
	// 清空
	tAddr.Clear();

	CUmsConfInst* pInst = Inst();

	if (pInst->IsChairConf())
	{
		if (bToSingle && pInst->GetSpeaker().m_bIsDualMixOn)
		{// 双流开启的情形下，bToSingle为TURE时，这里的地址要包含双流音频，to do...
            pInst->GetEapu()->GetNModeAudRcvAddr(pInst->GetSpeaker().m_ptAudMix, tAddr, tFormat);
		}
		else
		{
			pInst->GetEapu()->GetNModeAudRcvAddr(m_tMixEqp.m_ptMixRes, tAddr, tFormat);
		}
	}
	else
	{// 
		TCapNode* ptCaller = pInst->GetNodeMgr()->GetCaller();
		if ( NULL != ptCaller && ptCaller->IsChanOn())
		{
			if (pInst->curSpeakerID() == ptCaller->m_wEpID)
			{// 发言人是上级
				if (bToSingle)
				{
					if (NULL != ptCaller->m_ptMixAddr)
					{
						tAddr.m_tAddr.m_tRtpAddr = ptCaller->m_ptMixAddr->m_tRtpAddr;
						tAddr.m_tAddr.m_tBackRtcpAddr = ptCaller->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
						tAddr.m_dwMediaNode = ptCaller->m_tMediaEqp.m_dwEqpNode;

					}else
					{
						tpError(Ums_Mdl_Call, "[CUmsAudMixMgr::GetMixNModeRcvAddr] ConfID:%d, ptCaller->m_ptMixAddr is NULL.\n",
							pInst->GetInsID());
					}
				}
				else
				{
					if (ptCaller->m_aptChanAddr[MIDSCREENINDEX] != NULL)
					{					
						
						tAddr.m_tAddr.m_tRtpAddr = ptCaller->m_aptChanAddr[MIDSCREENINDEX]->m_tAud.m_tRtpAddr;
					    tAddr.m_tAddr.m_tBackRtcpAddr = ptCaller->m_tRmtChan.m_atAudEnc[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr;
					    tAddr.m_dwMediaNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
					} else
					{
						tpError(Ums_Mdl_Call, "[CUmsAudMixMgr::GetMixNModeRcvAddr] ConfID:%d, ptCaller->m_aptChanAddr[MIDSCREENINDEX] is NULL.\n",
		                        pInst->GetInsID());
					}
				}
			}
			else
			{// 发言人不是上级
				if (NULL != ptCaller->m_ptCasCadeChairAddr)
				{
					if (bToSingle)
					{
						tAddr.m_tAddr.m_tRtpAddr = ptCaller->m_ptCasCadeChairAddr->m_tMixAud.m_tRtpAddr;
						tAddr.m_tAddr.m_tBackRtcpAddr = ptCaller->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr.m_tBackRtcpAddr;
						tAddr.m_dwMediaNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
					}
					else
					{
						tAddr.m_tAddr.m_tRtpAddr = ptCaller->m_ptCasCadeChairAddr->m_atAud[MIDSCREENINDEX].m_tRtpAddr;
						tAddr.m_tAddr.m_tBackRtcpAddr = ptCaller->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr;
						tAddr.m_dwMediaNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
					}
				}
			}
		}
	}
}

void CUmsAudMixMgr::GetMixAudSrcAddr( TCapNode* ptNode, TTransParam& tAudParam )
{
	TUmsAudMixEpInfo* ptEp = m_tMixEpInfoList.GetEp(ptNode->m_wEpID);
	if (NULL != ptEp)
	{// 听n-1
		TServiceAddr tAudRcvAddr;
		GetMixAudRcvAddrForMixEp(ptEp, tAudRcvAddr);
		tAudParam.m_dwEqpNode = tAudRcvAddr.m_dwMediaNode;
		tAudParam.m_tAddr.m_tRtpAddr = tAudRcvAddr.m_tAddr.m_tRtpAddr;
		tAudParam.m_tAddr.m_tBackRtcpAddr = tAudRcvAddr.m_tAddr.m_tBackRtcpAddr;
		return;
	}

	// 听n
	if (m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
	{//音频适配 需要优先接收
		TTPDsFrom tAddr;
		m_pcConf->GetBas()->GetSpeakerMixAudBasOutAddr(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
		
		tAudParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
		tAudParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
		tAudParam.m_dwEqpNode = tAddr.m_dwEqpNode;
	}
	else 
	{
		//混音或者坐席
		tAudParam.m_tAddr = m_pcConf->GetSpeakerAudMix();
		tAudParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
		tAudParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
	}

	return;
}

