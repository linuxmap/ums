
#include "umsconfinst.h"
#include "eventoutsipadapter.h"
#include "eventoutumscall.h"		
#include "umsgetconfvidaud.h"
#include "umsnetportmgr.h"

void GetConfVmpCB(void* param1, void* param2, void* param3)
{
	CGetConfVidAudMgr* ptGetConfMsg  = (CGetConfVidAudMgr*)param1;
	TBrdVmpRes*        ptRes		 = (TBrdVmpRes*)param2;
	
	ptGetConfMsg->GetVmpCB(ptRes, *(EmBrdVmpCBOprType *)param3);
}


void CGetConfVidAudMgr::Clear()
{
	u16 wIndex = 0;
	for(; wIndex < GET_CONF_BRD_VID_AUD_MAX_USER; wIndex++)
	{
		m_atBroadCastInfo[wIndex].Clear();
	}
	
	for(wIndex = 0; wIndex < GET_CONF_VMP_VID_MAX_USER; wIndex++)
	{	
		m_atVmpInfo[wIndex].Clear();
	}
	
	for(wIndex = 0; wIndex < GET_EP_SCREEN_STREAM_MAX_USER; wIndex++)
	{	
		m_atEpSreenInfo[wIndex].Clear();
	}

}

u16 CGetConfVidAudMgr::GetExistBroadCastUser(TLogUser tUser)
{
	for(u16 wIndex = 0; wIndex < GET_CONF_BRD_VID_AUD_MAX_USER; wIndex++)
	{
		if(m_atBroadCastInfo[wIndex].m_bUsed && 
		   m_atBroadCastInfo[wIndex].m_tUser == tUser
		  )
		{
			return wIndex;
		}
	}
    
    return TP_INVALID_INDEX;
}

u16 CGetConfVidAudMgr::GetIdleBroadCastUser()
{
    for(u16 wIndex = 0; wIndex < GET_CONF_BRD_VID_AUD_MAX_USER; wIndex++)
	{
		if(!m_atBroadCastInfo[wIndex].m_bUsed)
		{
			return wIndex;
		}
	}
    
    return TP_INVALID_INDEX;
}

BOOL32 CGetConfVidAudMgr::ReleaseBroadCastUser(u16 wIndex)
{
	if (wIndex >= GET_CONF_BRD_VID_AUD_MAX_USER)
	{
        return FALSE;
	}
	
	if (m_atBroadCastInfo[wIndex].m_bUsed)
	{
		CNetPortMgr::FreeMediaTrans(m_pcConf, m_atBroadCastInfo[wIndex].m_cDsInfo);
		
	}
	
	m_atBroadCastInfo[wIndex].Clear();
	
	return TRUE;
}

u16 CGetConfVidAudMgr::GetExistVmpUser(TLogUser tUser, u16 wEqpId)
{
	for(u16 wIndex = 0; wIndex < GET_CONF_VMP_VID_MAX_USER; wIndex++)
	{
		if (!m_atVmpInfo[wIndex].m_ptVmp)
		{
			continue;
		}

		if(m_atVmpInfo[wIndex].m_bUsed && 
		   m_atVmpInfo[wIndex].m_tUser == tUser &&
		   m_atVmpInfo[wIndex].m_ptVmp->m_tEqpRes.m_byEqpID == wEqpId)
		{
			return wIndex;
		}
	}
    
    return TP_INVALID_INDEX;
}

u16 CGetConfVidAudMgr::GetIdleVmpUser()
{
    for(u16 wIndex = 0; wIndex < GET_CONF_VMP_VID_MAX_USER; wIndex++)
	{
		if(!m_atVmpInfo[wIndex].m_bUsed)
		{
			return wIndex;
		}
	}
    
    return TP_INVALID_INDEX;
}

BOOL32 CGetConfVidAudMgr::ReleaseVmpInfo(u16 wIndex)
{
	if (wIndex >= GET_CONF_VMP_VID_MAX_USER)
	{
        return FALSE;
	}
	
	if (m_atVmpInfo[wIndex].m_bUsed)
	{
		CNetPortMgr::FreeMediaTrans(m_pcConf, m_atVmpInfo[wIndex].m_cToVmpVid);
	}
	
	m_atVmpInfo[wIndex].Clear();
	
	return TRUE;
}

u16 CGetConfVidAudMgr::GetExistEpScreenUser(TLogUser tUser, TGetEpScreenInfo tInfo)
{
	for(u16 wIndex = 0; wIndex < GET_EP_SCREEN_STREAM_MAX_USER; wIndex++)
	{
		if(m_atEpSreenInfo[wIndex].m_bUsed && 
		   m_atEpSreenInfo[wIndex].m_tUser == tUser &&
		   m_atEpSreenInfo[wIndex].m_wEpID == tInfo.m_wEpID &&
		   m_atEpSreenInfo[wIndex].m_wScreenID == tInfo.m_wScreenID)
		{
			return wIndex;
		}
	}
    
    return TP_INVALID_INDEX;
}

u16 CGetConfVidAudMgr::GetIdleEpScreenUser()
{
    for(u16 wIndex = 0; wIndex < GET_EP_SCREEN_STREAM_MAX_USER; wIndex++)
	{
		if(!m_atEpSreenInfo[wIndex].m_bUsed)
		{
			return wIndex;
		}
	}
    
    return TP_INVALID_INDEX;
}

BOOL32 CGetConfVidAudMgr::ReleaseEpScreenUser(u16 wIndex)
{

	if (wIndex >= GET_EP_SCREEN_STREAM_MAX_USER)
	{
		return FALSE;
	}
	if (m_atEpSreenInfo[wIndex].m_bUsed)
	{
		CNetPortMgr::FreeMediaTrans(m_pcConf, m_atEpSreenInfo[wIndex].m_cDsInfo);
		m_pcConf->GetVidAudEx()->Release(m_pcConf, m_atEpSreenInfo[wIndex].m_wVidHandle);
	}
	
	m_atEpSreenInfo[wIndex].Clear();
	
	return TRUE;
}

BOOL32 CGetConfVidAudMgr::HandlerFromUmc(CTpMsg *const ptMsg)
{
	switch (ptMsg->GetEvent())
	{	
	case evtp_GetConfBrdVidAud_cmd:
		{
            OnGetConfBrdVidAudReq(ptMsg);
            break;
		}	
	case evtp_ReleasConfBrdVidAud_cmd:          
		{    
            OnReleaseGetConfBrdVidAud(ptMsg);
			break;
		}
	case evtp_GetConfBrdVidAudAskKey:
		{
			OnGetConfBrdVidAudAskKey(ptMsg);
			break;
		}
	// 不入会获取画面合成码流
	case evtp_GetConfVmpVid_cmd:
		{
			OnGetConfVmpVidReq(ptMsg);
			break;
		}
	case evtp_ReleaseConfVmpVid_cmd:
		{
			OnReleaseConfVmpVidReq(ptMsg);
			break;
		}
	case evtp_GetConfVmpVidAskKey_cmd:
		{
			OnGetConfVmpVidAskKeyReq(ptMsg);
			break;
		}
	// 请求会场指定屏音视频码流
	case evtp_GetEpSreenStream_cmd:
		{
			OnGetEpScreenStreamReq(ptMsg);
			break;
		}
	case evtp_ReleaseEpSreenStream_cmd:
		{
			OnReleaseEpScreenStreamReq(ptMsg);
			break;
		}
	case evtp_GetEpSreenAskKey_cmd:
		{
			OnGetEpScreenAskKeyReq(ptMsg);
			break;
		}
		
	default:
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

void CGetConfVidAudMgr::OnGetConfBrdVidAudReq( CTpMsg* const ptMsg )
{
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TUmsGetConfBrdVidAudInfo tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(TLogUser));

    TUmsGetConfBrdVidAudInfo tInd;
	tInd.m_wConfID	= tReq.m_wConfID;
	tInd.m_emRet = em_GetConfBrdVidAudRet_success;

	TTPTransAddr* ptAddr = NULL;
	TBroadCastInfo* ptInfo = NULL;
	u16 wUmserIndex = TP_INVALID_INDEX;
	do 
	{
		if (m_pcConf->CurState() != CUmsConfInst::inst_run)
		{
			MdlError(Ums_Mdl_Call, ("[GetConfBrdVidAudReq] ConfID:%d idle\n", m_pcConf->GetInsID()));
            tInd.m_emRet = em_GetConfBrdVidAudRet_idleconf; 
			break;
		}
		
		wUmserIndex = GetExistBroadCastUser(tLogUser);
		if (wUmserIndex < GET_CONF_BRD_VID_AUD_MAX_USER)
		{
			tInd.m_emRet = em_GetConfBrdVidAudRet_userExist; 
			if (m_atBroadCastInfo[wUmserIndex].m_bUsed)
			{
				CNetPortMgr::FreeMediaTrans(m_pcConf, m_atBroadCastInfo[wUmserIndex].m_cDsInfo);
			}
			break;
		}

		wUmserIndex = GetIdleBroadCastUser();
		if (wUmserIndex >= GET_CONF_BRD_VID_AUD_MAX_USER)
		{
			MdlError(Ums_Mdl_Call, ("[GetConfBrdVidAudReq] ConfID:%d  user full\n", m_pcConf->GetInsID()));
            tInd.m_emRet = em_GetConfBrdVidAudRet_full; 
			break;
		}

	}while(0);

	MdlHint(Ums_Mdl_Call, ("[GetConfBrdVidAudReq] ConfID:%d ret:%d\n", m_pcConf->GetInsID(), tInd.m_emRet));
	
	if(tInd.m_emRet != em_GetConfBrdVidAudRet_userExist && tInd.m_emRet != em_GetConfBrdVidAudRet_success)
	{
		m_pcConf->NotifyMsgToServiceForUI(evtp_GetConfBrdVidAud_ind, &tInd, sizeof(tInd), &tLogUser);
		return;
	}

	ptInfo = &m_atBroadCastInfo[wUmserIndex];
	if (0 == CNetPortMgr::AdjustConfVidAudToTarget(m_pcConf, ptInfo->m_cDsInfo, tReq))
	{
		MdlError(Ums_Mdl_Call, ("[GetConfBrdVidAudReq] ConfID:%d AdjustConfVidAudToTarget fail\n", m_pcConf->GetInsID()));
		tInd.m_emRet = em_GetConfBrdVidAudRet_unkown;
		m_pcConf->NotifyMsgToServiceForUI(evtp_GetConfBrdVidAud_ind, &tInd, sizeof(tInd), &tLogUser);
		return;
	}
	
	ptInfo->m_bUsed = TRUE;
	ptInfo->m_tUser = tLogUser;
	for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		//三屏视频
		ptAddr = &tReq.m_atVidAddr[wIndex];
		ptInfo->m_atVidAddr[wIndex] = *ptAddr;
		if (0 != ptAddr->m_dwIP &&  0 != ptAddr->m_wPort)
		{
			tInd.m_atVidAddr[wIndex] = m_pcConf->GetSpeakerVidDec(wIndex).m_tBackRtcpAddr;
		}
		
		//三屏音频
		ptAddr = &tReq.m_atAudAddr[wIndex];
		ptInfo->m_atAudAddr[wIndex] = *ptAddr;
		if (0 != ptAddr->m_dwIP &&  0 != ptAddr->m_wPort)
		{   
			tInd.m_atVidAddr[wIndex] = m_pcConf->GetSpeakerAudDec(wIndex).m_tBackRtcpAddr;
		}
	}
	
	//单屏视频
	ptAddr = &tReq.m_tSingleVidAddr;
	ptInfo->m_tSingleVidAddr = *ptAddr;
	if (0 != ptAddr->m_dwIP &&  0 != ptAddr->m_wPort)
	{
		tInd.m_tSingleVidAddr = m_pcConf->GetSingleVidDec().m_tBackRtcpAddr;
	}
	
	//单屏音频
	ptAddr = &tReq.m_tAudMixAddr;
	ptInfo->m_tAudMixAddr = *ptAddr;
	if (0 != ptAddr->m_dwIP &&  0 != ptAddr->m_wPort)
	{
		tInd.m_tAudMixAddr = m_pcConf->GetSpeakerAudMix().m_tBackRtcpAddr;
	}
	
	tInd.m_wUserIndex = wUmserIndex;
	m_pcConf->NotifyMsgToServiceForUI(evtp_GetConfBrdVidAud_ind, &tInd, sizeof(tInd), &tLogUser);
}

void CGetConfVidAudMgr::OnReleaseGetConfBrdVidAud( CTpMsg* const ptMsg )
{
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TUmsReleaseConfBrdVidAudInfo tInd;
	TP_SAFE_CAST( tInd, ptMsg->GetBody()+sizeof(TLogUser));
	tInd.m_emRet = em_ReleaseConfBrdVidAudRet_success;

	do 
	{	
		if (m_pcConf->CurState() != CUmsConfInst::inst_run)
		{
			MdlError(Ums_Mdl_Call, ("[OnReleaseGetConfBrdVidAud] ConfID:%d idle\n", m_pcConf->GetInsID()));
            tInd.m_emRet = em_ReleaseConfBrdVidAudRet_idleconf; 
			break;
		}

		if (FALSE == ReleaseBroadCastUser(tInd.m_wUserIndex))
		{
			MdlError(Ums_Mdl_Call, ("[OnReleaseGetConfBrdVidAud] ConfID:%d ReleaseUserIndex fail\n", m_pcConf->GetInsID()));
            tInd.m_emRet = em_ReleaseConfBrdVidAudRet_unkown; 
			break;  
		} 
		
	}while(0);
	
	MdlHint(Ums_Mdl_Call, ("[OnReleaseGetConfBrdVidAud] ConfID:%d ReleaseIndex:%d ret:%d\n", m_pcConf->GetInsID(),tInd.m_wUserIndex, tInd.m_emRet));
	
	m_pcConf->NotifyMsgToServiceForUI(evtp_ReleasConfBrdVidAud_ind, &tInd, sizeof(tInd), &tLogUser);
}

void CGetConfVidAudMgr::OnGetConfBrdVidAudAskKey(CTpMsg* const ptMsg)
{
   	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TUmsGetConfBrdVidAudAskKey tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(TLogUser)); 

	MdlLowDtl(Ums_Mdl_Call, ("[OnGetConfBrdVidAudAskKey] ConfID:%d  UserIndex:%d  OprScreenIndex:%d\n",
			m_pcConf->GetInsID(), tReq.m_wUserIndex, tReq.m_wScreenIndex));
		
	if (m_pcConf->CurState() != CUmsConfInst::inst_run)
	{
		MdlLowDtl(Ums_Mdl_Call, ("[OnGetConfBrdVidAudAskKey] ConfID:%d idle\n", m_pcConf->GetInsID()));
		return;
	}

	if (tReq.m_wUserIndex >= GET_CONF_BRD_VID_AUD_MAX_USER || tReq.m_wScreenIndex > 4)
	{
		MdlLowDtl(Ums_Mdl_Call, ("[OnGetConfBrdVidAudAskKey] ConfID:%d para error UserIndex:%d  OprScreenIndex:%d\n",
				 m_pcConf->GetInsID(), tReq.m_wUserIndex, tReq.m_wScreenIndex));
		return;
	}

	// 0,1,2 代表三屏中的 左，中，右，3 代表合成的单屏，4代表所有视频
	if (tReq.m_wScreenIndex > TP_MAX_STREAMNUM + 1 )
	{
		return;
	}

	if (m_pcConf->GetUmsDiscuss()->IsDiscussModle())
	{
		m_pcConf->GetUmsDiscuss()->AskKeyFrameForConfBrdUser(tReq.m_wScreenIndex);
		return;
	}

	u16  wProScreen = tReq.m_wScreenIndex;
	if (tReq.m_wScreenIndex == TP_MAX_STREAMNUM + 1)
	{
		wProScreen = MIDSCREENINDEX;
	}

	if (tReq.m_wScreenIndex  < TP_MAX_STREAMNUM  || tReq.m_wScreenIndex == TP_MAX_STREAMNUM + 1)
	{
		if ( m_pcConf->GetVmp()->IsBrdVmp() &&  wProScreen == MIDSCREENINDEX )
		{//广播合成 中间屏
			if (m_pcConf->IsChairConf())
			{
				m_pcConf->GetVmp()->AskFrameToBrdVmp(m_pcConf->GetVmp()->GetConfBrdVmp(), m_pcConf->curSpeakerID(), TRUE);
			}
			else
			{
				m_pcConf->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeyBrdVmp);
			}
		}
		else
		{
			m_pcConf->AskKeyByScreen(m_pcConf->curSpeakerID(), wProScreen, EmAskKeySpeaker);
		}
	}
	
	if (tReq.m_wScreenIndex  == TP_MAX_STREAMNUM  ||  tReq.m_wScreenIndex == TP_MAX_STREAMNUM + 1)
	{
		if ( m_pcConf->IsChairConf() )
		{
			if (m_pcConf->GetVmp()->IsSpeakerInVmp())
			{
				m_pcConf->GetVmp()->AskFrameToSpeakerVmp(m_pcConf->curSpeakerID());
			} 
			else 
			{
				m_pcConf->AskKeyByScreen(m_pcConf->curSpeakerID(), wProScreen, EmAskKeySpeaker);

			}
		}
		else
		{
			m_pcConf->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeySpeakerVmp);
		}
	}

}

void CGetConfVidAudMgr::OnStopConf() 
{
	u16 wIndex = 0;
	for(wIndex = 0; wIndex < GET_CONF_BRD_VID_AUD_MAX_USER; wIndex++)
	{
        if (m_atBroadCastInfo[wIndex].m_bUsed)
		{
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_atBroadCastInfo[wIndex].m_cDsInfo);
		}
		m_atBroadCastInfo[wIndex].Clear();
	}

	for(wIndex = 0; wIndex < GET_CONF_VMP_VID_MAX_USER; wIndex++)
	{
        if (m_atVmpInfo[wIndex].m_bUsed)
		{
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_atVmpInfo[wIndex].m_cToVmpVid);   
		}	
		m_atVmpInfo[wIndex].Clear();
	}

	for(wIndex = 0; wIndex < GET_CONF_VMP_VID_MAX_USER; wIndex++)
	{
        if (m_atEpSreenInfo[wIndex].m_bUsed)
		{
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_atEpSreenInfo[wIndex].m_cDsInfo);
			m_pcConf->GetVidAudEx()->Release(m_pcConf, m_atEpSreenInfo[wIndex].m_wVidHandle);
		}	
		m_atEpSreenInfo[wIndex].Clear();
	}

}

void CGetConfVidAudMgr::OnGetConfVmpVidReq( CTpMsg* const ptMsg )
{
	TLogUser tUser;
	TP_SAFE_CAST( tUser, ptMsg->GetBody());
	TUmsGetVmpVidInfo tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(tUser));
	
	TUmsGetVmpVidInfo tInfo;
	tInfo.m_wConfID		= tReq.m_wConfID;
	tInfo.m_wEqpID		= tReq.m_wEqpID;
	tInfo.m_tRtpAddr	= tReq.m_tRtpAddr;
	tInfo.m_emRet		= em_GetVmpVidRet_success;

	TTPDsFrom     tVmp; 
	TGetVmpInfo* pTGetVmpInfo = NULL;
	u16 wVmpInfoIndex = TP_INVALID_INDEX;
	do 
	{	
		MdlHint(Ums_Mdl_Call, ("[OnGetConfVmpVidReq] ConfID:%d!\n", m_pcConf->GetInsID()));

		if (m_pcConf->CurState() != CUmsConfInst::inst_run)
		{
			MdlError(Ums_Mdl_Call, ("[OnGetConfVmpVidReq] ConfID:%d idle\n", m_pcConf->GetInsID()));
            tInfo.m_emRet = em_GetVmpVidRet_idleconf; 
			break;
		}
		
		wVmpInfoIndex = GetExistVmpUser(tUser, tReq.m_wEqpID);
		if (wVmpInfoIndex < GET_CONF_VMP_VID_MAX_USER)
		{
			MdlError(Ums_Mdl_Call, ("[OnGetConfVmpVidReq] ConfID:%d  user full\n", m_pcConf->GetInsID()));
            tInfo.m_emRet = em_GetVmpVidRet_vmpUserExist; 
			if (m_atVmpInfo[wVmpInfoIndex].m_bUsed)
			{
				CNetPortMgr::FreeMediaTrans(m_pcConf, m_atVmpInfo[wVmpInfoIndex].m_cToVmpVid);
			}
			break;
		}

		wVmpInfoIndex = GetIdleVmpUser();
		if (wVmpInfoIndex >= GET_CONF_VMP_VID_MAX_USER)
		{
			MdlError(Ums_Mdl_Call, ("[OnGetConfVmpVidReq] ConfID:%d  user full\n", m_pcConf->GetInsID()));
            tInfo.m_emRet = em_GetVmpVidRet_vmpInfofull; 
			break;
		}
		
		pTGetVmpInfo = &m_atVmpInfo[wVmpInfoIndex];

		// 找到合成器
		pTGetVmpInfo->m_ptVmp = m_pcConf->GetVmp()->GetVmpOutConf(tReq.m_wEqpID, GetConfVmpCB, this);
		if (NULL == pTGetVmpInfo->m_ptVmp)
		{
			MdlError(Ums_Mdl_Call, ("OnAddMonitor error! Assign vmp failed.\n"));
			pTGetVmpInfo->Clear();
			tInfo.m_emRet = em_GetVmpVidRet_assvmpfail;
			break;
		}
		u16 wMaxHp = TP_INVALID_INDEX;
		u16 wMaxBp = TP_INVALID_INDEX;
		CTpTypeAdpt::GetConfBaseMaxCap(m_pcConf->GetConfBase(), wMaxHp, wMaxBp);
		if (TP_INVALID_INDEX == wMaxHp && TP_INVALID_INDEX == wMaxBp)
		{
			MdlError(Ums_Mdl_Call, ("OnGetConfVmpVidReq error! Not vaild format.\n"));
			pTGetVmpInfo->Clear();
			tInfo.m_emRet = em_GetVmpVidRet_vaildformat;
			break;
		}
		
		if (TP_INVALID_INDEX != wMaxHp)
		{
			pTGetVmpInfo->m_tFormat = m_pcConf->GetConfBase().m_atTpMainVideoRes[wMaxHp];
		}
		else
		{
			pTGetVmpInfo->m_tFormat = m_pcConf->GetConfBase().m_atTpMainVideoRes[wMaxBp];
		}
	
		pTGetVmpInfo->m_bUsed = TRUE;
		pTGetVmpInfo->m_tUser = tUser;
	} while(0);

	MdlHint(Ums_Mdl_Call, ("[OnGetConfVmpVidReq] ConfID:%d ret:%d\n", m_pcConf->GetInsID(), tInfo.m_emRet));
		
	if (tInfo.m_emRet != em_GetVmpVidRet_vmpUserExist &&
		tInfo.m_emRet != em_GetVmpVidRet_success)
	{
		m_pcConf->NotifyMsgToServiceForUI(evtp_GetConfVmpVid_ind, &tInfo, sizeof(tInfo), &tUser);
		return;
	}

	if (!pTGetVmpInfo)
	{
		pTGetVmpInfo = &m_atVmpInfo[wVmpInfoIndex];
	}
	
	// 以当前会议的最大分辨率选取合成通道
	m_pcConf->GetVmp()->GetBrdVmpOutAddr(pTGetVmpInfo->m_ptVmp, tVmp, pTGetVmpInfo->m_tFormat);
	// 创建交换
	CNetPortMgr::AdjustConfVmpVidToTarget(m_pcConf, pTGetVmpInfo->m_cToVmpVid, tVmp, tReq);
	
	// rtcp 地址
	tInfo.m_wVmpInfoIndex  = wVmpInfoIndex;
	tInfo.m_tRtcpAddr	= tVmp.m_tBackRtcpAddr;
	tInfo.m_tFormat		= pTGetVmpInfo->m_tFormat;
	tInfo.m_tEncrypt	= m_pcConf->GetConfEncryptInfo();
	
	pTGetVmpInfo->m_tRtpAddr	= tInfo.m_tRtpAddr;
	m_pcConf->NotifyMsgToServiceForUI(evtp_GetConfVmpVid_ind, &tInfo, sizeof(tInfo), &tUser);

}

void CGetConfVidAudMgr::OnReleaseConfVmpVidReq( CTpMsg* const ptMsg )
{
	TLogUser tUser;
	TP_SAFE_CAST( tUser, ptMsg->GetBody());
	TUmsReleaseVmpVidInfo tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(tUser));
	
	TUmsReleaseVmpVidInfo tInfo;
	tInfo.m_wConfID	 = tReq.m_wConfID;
	tInfo.m_wVmpInfoIndex = tReq.m_wVmpInfoIndex;
	tInfo.m_emRet	 = em_ReleaseVmpVidRet_success;

	do 
	{	
		MdlHint(Ums_Mdl_Call, ("[OnReleaseConfVmpVidReq] ConfID:%d  ReleaseIndex:%d\n",
			m_pcConf->GetInsID(),
			tInfo.m_wVmpInfoIndex));
		
		if (m_pcConf->CurState() != CUmsConfInst::inst_run)
		{
			MdlError(Ums_Mdl_Call, ("[OnReleaseGetConfBrdVidAud] ConfID:%d idle\n", m_pcConf->GetInsID()));
            tInfo.m_emRet = em_ReleaseVmpVidRet_idleconf; 
			break;
		}
		
		if (FALSE == ReleaseVmpInfo(tInfo.m_wVmpInfoIndex))
		{
			MdlError(Ums_Mdl_Call, ("[OnReleaseGetConfBrdVidAud] ConfID:%d ReleaseUserIndex fail\n", m_pcConf->GetInsID()));
            tInfo.m_emRet = em_ReleaseVmpVidRet_idlevmpinfo; 
			break;  
		} 	
		
		
	}while(0);
	
	
	MdlHint(Ums_Mdl_Call, ("[OnReleaseGetConfBrdVidAud] ConfID:%d ret:%d\n", m_pcConf->GetInsID(), tInfo.m_emRet));

	m_pcConf->NotifyMsgToServiceForUI(evtp_ReleaseConfVmpVid_ind, &tInfo, sizeof(tInfo), &tUser);

}

void CGetConfVidAudMgr::OnGetConfVmpVidAskKeyReq( CTpMsg* const ptMsg )
{
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TUmsGetVmpVidAskKey tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(TLogUser)); 
	
	TGetVmpInfo* ptInfo = NULL;
	do 
	{	
		MdlLowDtl(Ums_Mdl_Call, ("[OnGetConfVmpVidAskKeyReq] ConfID:%d  UserIndex:%d  OprScreenIndex:%d\n",
			m_pcConf->GetInsID(), tReq.m_wVmpInfoIndex));
		
		if (m_pcConf->CurState() != CUmsConfInst::inst_run)
		{
			MdlLowDtl(Ums_Mdl_Call, ("[OnGetConfVmpVidAskKeyReq] ConfID:%d idle\n", m_pcConf->GetInsID())); 
			break;
		}

		if (tReq.m_wVmpInfoIndex >= GET_CONF_VMP_VID_MAX_USER)
		{
			MdlLowDtl(Ums_Mdl_Call, ("[OnGetConfVmpVidAskKeyReq] ConfID:%d  UserIndex:%d idle vmp info index!\n",
						m_pcConf->GetInsID()));
			break;
		}

		ptInfo = &m_atVmpInfo[tReq.m_wVmpInfoIndex];
		m_pcConf->GetVmp()->AskFrameToBrdVmp(ptInfo->m_ptVmp, ptInfo->m_tFormat);

	}while(0);
	
    return;
}

void CGetConfVidAudMgr::GetVmpCB( TBrdVmpRes* ptRes, EmBrdVmpCBOprType emOpr)
{
	//合成器掉线或释放
	MdlHint(Ums_Mdl_Call, ("[CGetConfVidAudMgr] GetVmpCB! VmpID:%d\n", ptRes->m_tEqpRes.m_byEqpID));
	
	TUmsVmpVidData  tVmpData;
	EmCnsCallReason emRes = EmCnsCallReason_hungup;
	
	TGetVmpInfo* ptInfo = NULL;
	for(u16 wIndex = 0; wIndex < GET_CONF_VMP_VID_MAX_USER; ++wIndex)
	{
		ptInfo = &(m_atVmpInfo[wIndex]);
		if (!ptInfo->m_bUsed)
		{
			continue;
		}
		if ( ptInfo->m_ptVmp != ptRes )
		{
			continue;
		}
		
		CNetPortMgr::FreeMediaTrans(m_pcConf, ptInfo->m_cToVmpVid);
		
		tVmpData.m_wConfID = m_pcConf->GetInsID();
		tVmpData.m_wVmpInfoIndex = wIndex;

		if (EmBrdVmpCBOprType_DisConnect == emOpr || EmBrdVmpCBOprType_Stop == emOpr)
		{
            tVmpData.m_emRet = em_VmpVidRes_notonline;
		} else {
            tVmpData.m_emRet = em_VmpVidRes_unkown;
		}
		
		ptInfo->Clear();
		m_pcConf->NotifyMsgToServiceForUI(evtp_ConfVmpVid_nty, &tVmpData, sizeof(tVmpData), &(ptInfo->m_tUser));
	}

}

void CGetConfVidAudMgr::Show()
{
	msgprintnotime("[CGetConfVidAudMgr:]\n");
	
	msgprintnotime("[VmpInfo:]\n");
	TGetVmpInfo* ptVmpInfo = NULL;
	u16 wIndex = 0;
	for (; wIndex < GET_CONF_VMP_VID_MAX_USER; ++wIndex)
	{	
		ptVmpInfo = &m_atVmpInfo[wIndex];
		if (!m_atVmpInfo[wIndex].m_bUsed)
		{
			continue;
		}
		msgprintnotime("  useIndex:%d, bUsed:%d, VmpId:%d\n", wIndex, ptVmpInfo->m_bUsed, 
										ptVmpInfo->m_ptVmp->m_tEqpRes.m_byEqpID);
		msgprintnotime("  useID:%d, useName:%s, useIp:"TPIPFORMAT", InstId:%d, Node:%d\n",
							ptVmpInfo->m_tUser.m_dwUserID, ptVmpInfo->m_tUser.m_achName,
							Tpu32ToIP(ptVmpInfo->m_tUser.m_dwUserIP), ptVmpInfo->m_tUser.m_dwUserInst,
							ptVmpInfo->m_tUser.m_dwUserNode);
		msgprintnotime("  rtp("ADDRPORT_FORMAT")\n\n", ADDRNET(ptVmpInfo->m_tRtpAddr));
	}

	msgprintnotime("[BroadCastInfo:]\n");
	TBroadCastInfo* ptBroadCastInfo = NULL;
	for (wIndex = 0; wIndex < GET_CONF_BRD_VID_AUD_MAX_USER; ++wIndex)
	{	
		ptBroadCastInfo = &m_atBroadCastInfo[wIndex];
		if (!ptBroadCastInfo->m_bUsed)
		{
			continue;
		}
		msgprintnotime("useIndex:%d, bUsed:%d\n", wIndex, ptBroadCastInfo->m_bUsed);
		msgprintnotime("  useID:%d, useName:%s, useIp:"TPIPFORMAT", InstId:%d, Node:%d\n",
			ptBroadCastInfo->m_tUser.m_dwUserID, ptBroadCastInfo->m_tUser.m_achName,
			Tpu32ToIP(ptBroadCastInfo->m_tUser.m_dwUserIP), ptBroadCastInfo->m_tUser.m_dwUserInst,
							ptBroadCastInfo->m_tUser.m_dwUserNode);
		u16 wAddrIndex = 0;
		msgprintnotime("[SpeakerVid:]\n");
		for (; wAddrIndex < TP_MAX_STREAMNUM; ++wAddrIndex)
		{
			msgprintnotime("  VidIndex:%d, rtp("ADDRPORT_FORMAT")\n", wAddrIndex, 
					ADDRNET(ptBroadCastInfo->m_atVidAddr[wIndex]));
		}
		msgprintnotime("[SpeakerSingleVid:]\n");
		msgprintnotime("  rtp("ADDRPORT_FORMAT")\n", ADDRNET(ptBroadCastInfo->m_tSingleVidAddr));
		

		msgprintnotime("[SpeakerAud:]\n");
		for (wAddrIndex = 0; wAddrIndex < TP_MAX_STREAMNUM; ++wAddrIndex)
		{
			msgprintnotime("  AudIndex:%d, rtp("ADDRPORT_FORMAT")\n", wAddrIndex,
				ADDRNET(ptBroadCastInfo->m_atAudAddr[wIndex]));
		}
		msgprintnotime("[SpeakerAudMix:]\n");
		msgprintnotime("  rtp("ADDRPORT_FORMAT")\n\n", ADDRNET(ptBroadCastInfo->m_tAudMixAddr));
	//	
	}
	msgprintnotime("[EpScreenInfo:]\n");
	TUmsGetEpScreenInfo* ptInfo = NULL;
	for (wIndex = 0; wIndex < GET_EP_SCREEN_STREAM_MAX_USER; ++wIndex)
	{	
		ptInfo = &m_atEpSreenInfo[wIndex];
		if (!m_atEpSreenInfo[wIndex].m_bUsed)
		{
			continue;
		}
		msgprintnotime("  useIndex:%d, bUsed:%d, EpId:%d, ScreenId:%d\n", wIndex, ptInfo->m_bUsed, 
			ptInfo->m_wEpID, ptInfo->m_wScreenID);
		msgprintnotime("  useID:%d, useName:%s, useIp:"TPIPFORMAT", InstId:%d, Node:%d\n",
			ptInfo->m_tUser.m_dwUserID, ptInfo->m_tUser.m_achName,
			Tpu32ToIP(ptInfo->m_tUser.m_dwUserIP), ptInfo->m_tUser.m_dwUserInst,
			ptInfo->m_tUser.m_dwUserNode);
		msgprintnotime("[VidSnd:]\n");
		msgprintnotime("  rtp("ADDRPORT_FORMAT")\n\n", ADDRNET(ptInfo->m_tVidAddr));
		msgprintnotime("[AudSnd:]\n");
		msgprintnotime("  rtp("ADDRPORT_FORMAT")\n\n", ADDRNET(ptInfo->m_tAudAddr));
		msgprintnotime("[AudMixSnd:]\n");
		msgprintnotime("  rtp("ADDRPORT_FORMAT")\n\n", ADDRNET(ptInfo->m_tAudMixAddr));
	}
}

void CGetConfVidAudMgr::OnGetEpScreenStreamReq( CTpMsg* const ptMsg )
{
	TLogUser tUser;
	TP_SAFE_CAST( tUser, ptMsg->GetBody());
	TGetEpScreenInfo tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(tUser));
	
	TGetEpScreenInd tInd;
	tInd.m_wConfID		= tReq.m_wConfID;
	tInd.m_wEpID		= tReq.m_wEpID;
	tInd.m_wScreenID	= tReq.m_wScreenID;
	tInd.m_emRet		= em_GetEpSreenStreamRet_success;
	
	u16 wUserIndex = TP_INVALID_INDEX;
	TUmsGetEpScreenInfo* ptInfo = NULL;
	TCallNode* ptNode = NULL;
	TGetVidAddr tAddr;
	u16 wVidHandle = 0;
	do 
	{	
		if (m_pcConf->CurState() != CUmsConfInst::inst_run)
		{
			MdlError(Ums_Mdl_Call, ("[OnGetEpScreenStreamReq] ConfID:%d idle\n", m_pcConf->GetInsID()));
            tInd.m_emRet = em_GetEpSreenStreamRet_idleconf; 
			break;
		}
		
		ptNode = m_pcConf->GetNode(tReq.m_wEpID);
		if (!ptNode || !IsInSndRange(tReq.m_wScreenID, ptNode->m_wAudSndNum))
		{
			MdlError(Ums_Mdl_Call, ("[OnGetEpScreenStreamReq] ConfID:%d  screen id:%d\n", m_pcConf->GetInsID(), tReq.m_wScreenID));
			tInd.m_emRet = em_GetEpSreenStreamRet_idleEpScreen;
			break;
		}

		wUserIndex = GetExistEpScreenUser(tUser, tReq);
		if ( wUserIndex < GET_EP_SCREEN_STREAM_MAX_USER)
		{// 同一个用户请求相同的码流 拆除旧交换 刷新交换
			tInd.m_emRet = em_GetEpSreenStreamRet_userExit;

			if (m_atEpSreenInfo[wUserIndex].m_bUsed)
			{
				CNetPortMgr::FreeMediaTrans(m_pcConf, m_atEpSreenInfo[wUserIndex].m_cDsInfo);
				m_atEpSreenInfo[wUserIndex].m_cDsInfo.Clear();
				m_pcConf->GetVidAudEx()->Release(m_pcConf, m_atEpSreenInfo[wUserIndex].m_wVidHandle);
			}

			break;
		}

		wUserIndex = GetIdleEpScreenUser();
		if (wUserIndex >= GET_EP_SCREEN_STREAM_MAX_USER)
		{
			MdlError(Ums_Mdl_Call, ("[OnGetEpScreenStreamReq] ConfID:%d  user full\n", m_pcConf->GetInsID()));
            tInd.m_emRet = em_GetEpSreenStreamRet_full; 
			break;
		}

	} while(0);

	MdlHint(Ums_Mdl_Call, ("[OnGetEpScreenStreamReq] ConfID:%d, epID:%d, screenID:%d, ret:%d\n", 
				m_pcConf->GetInsID(), tInd.m_wEpID, tInd.m_wScreenID, tInd.m_emRet));
	MdlHint(Ums_Mdl_Call, ("vid:("ADDRPORT_FORMAT"), aud:("ADDRPORT_FORMAT"), audmix:("ADDRPORT_FORMAT")\n",
		 ADDRNET(tReq.m_tVidAddr),  ADDRNET(tReq.m_tAudAddr),  ADDRNET(tReq.m_tAudMixAddr)));
	if (tInd.m_emRet != em_GetEpSreenStreamRet_success &&
		tInd.m_emRet != em_GetEpSreenStreamRet_userExit)
	{
		m_pcConf->NotifyMsgToServiceForUI(evtp_GetEpSreenStream_Ind, &tInd, sizeof(tInd), &tUser);
		return;
	}

	ptInfo	= &m_atEpSreenInfo[wUserIndex];
	// 获取会场码流
	if (em_GetVid_Success != m_pcConf->GetVidAudEx()->AssignByScreen(m_pcConf, ptNode->m_wEpID, tReq.m_wScreenID, em_GetVid_SdkGetAudVid,
		ptNode->m_tVidSndFormat, FALSE, tAddr, wVidHandle))
	{
		tInd.m_emRet = em_GetEpSreenStreamRet_noStream;
		MdlError(Ums_Mdl_Call, ("[OnGetEpScreenStreamReq] get stream error ConfID:%d, epID:%d, screenID:%d, ret:%d\n", 
			m_pcConf->GetInsID(), tInd.m_wEpID, tInd.m_wScreenID, tInd.m_emRet));
		m_pcConf->NotifyMsgToServiceForUI(evtp_GetEpSreenStream_Ind, &tInd, sizeof(tInd), &tUser);
		return;
	}
	// 创建交换
	BOOL32 bAudMix = !ptNode->IsSingleAudSnd();
	if(0 == CNetPortMgr::AdjustEpScreenStreamToTarget(m_pcConf, ptInfo->m_cDsInfo, tReq, tAddr, bAudMix))
	{
		tInd.m_emRet = em_GetEpSreenStreamRet_noStream;
		MdlError(Ums_Mdl_Call, ("[OnGetEpScreenStreamReq] rtp can not used ConfID:%d, epID:%d, screenID:%d, ret:%d\n", 
			m_pcConf->GetInsID(), tInd.m_wEpID, tInd.m_wScreenID, tInd.m_emRet));
		m_pcConf->NotifyMsgToServiceForUI(evtp_GetEpSreenStream_Ind, &tInd, sizeof(tInd), &tUser);
		return;
	}
	
	// 本地保存 
	ptInfo->m_wEpID		= tInd.m_wEpID;
	ptInfo->m_wScreenID = tInd.m_wScreenID;
	ptInfo->m_tUser		= tUser;
	ptInfo->m_bUsed		= TRUE;
	ptInfo->m_wVidHandle = wVidHandle;
	ptInfo->m_tVidAddr	= tReq.m_tVidAddr;
	ptInfo->m_tAudAddr	= tReq.m_tAudAddr;
	if (bAudMix)
	{
		ptInfo->m_tAudMixAddr = tReq.m_tAudMixAddr;
	}
	
	// 回应
	if (0 != tReq.m_tVidAddr.m_dwIP &&  0 != tReq.m_tVidAddr.m_wPort)
	{
		tInd.m_tVidAddr = tAddr.m_atVidAddr[tReq.m_wScreenID].m_tBackRtcpAddr;
	}
	if (0 != tReq.m_tAudAddr.m_dwIP &&  0 != tReq.m_tAudAddr.m_wPort)
	{   
		tInd.m_tAudAddr = tAddr.m_atAudAddr[tReq.m_wScreenID].m_tBackRtcpAddr;
	}
	if (bAudMix)
	{
		if (0 != tReq.m_tAudMixAddr.m_dwIP &&  0 != tReq.m_tAudMixAddr.m_wPort)
		{   
			tInd.m_tAudMixAddr = tAddr.m_tMixAddr.m_tBackRtcpAddr;
		}	
	}
	tInd.m_wUserIndex  = wUserIndex;
	tInd.m_tVidSndFormat = ptNode->m_tVidSndFormat.m_tFormat;
	tInd.m_tAudSndFormat = ptNode->m_tAudSndFormat.m_tFormat;
	tInd.m_tEncrypt = m_pcConf->GetConfEncryptInfo();
	m_pcConf->NotifyMsgToServiceForUI(evtp_GetEpSreenStream_Ind, &tInd, sizeof(tInd), &tUser);
}

void CGetConfVidAudMgr::OnReleaseEpScreenStreamReq( CTpMsg* const ptMsg )
{
	TLogUser tUser;
	TP_SAFE_CAST( tUser, ptMsg->GetBody());
	TReleaseEpScreenInfo tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(tUser));

	TReleaseEpScreenInfo tInfo;
	tInfo.m_wConfID	 = tReq.m_wConfID;
	tInfo.m_wUserIndex = tReq.m_wUserIndex;
	tInfo.m_emRet	 = em_ReleaseEpSreenStreamRet_success;
	
	do 
	{
		if (m_pcConf->CurState() != CUmsConfInst::inst_run)
		{
			MdlError(Ums_Mdl_Call, ("[OnReleaseEpScreenStreamReq] ConfID:%d idle\n", m_pcConf->GetInsID()));
            tInfo.m_emRet = em_ReleaseEpSreenStreamRet_idleconf; 
			break;
		}

		if (!ReleaseEpScreenUser(tReq.m_wUserIndex))
		{
			MdlError(Ums_Mdl_Call, ("[OnReleaseEpScreenStreamReq] user index error ConfID:%d\n",
				m_pcConf->GetInsID()));
            tInfo.m_emRet = em_ReleaseEpSreenStreamRet_idleIndex; 
		}

	}while(0);
	
	MdlHint(Ums_Mdl_Call, ("[OnReleaseGetConfBrdVidAud] ConfID:%d wUserIndex:%d ret:%d\n", m_pcConf->GetInsID(), tInfo.m_wUserIndex, tInfo.m_emRet));
	
	m_pcConf->NotifyMsgToServiceForUI(evtp_ReleaseEpSreenStream_Ind, &tInfo, sizeof(tInfo), &tUser);
}

void CGetConfVidAudMgr::OnGetEpScreenAskKeyReq( CTpMsg* const ptMsg )
{
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TGetEpScreenAskKey tReq;
	TP_SAFE_CAST( tReq, ptMsg->GetBody()+sizeof(TLogUser)); 
	
	TGetVmpInfo* ptInfo = NULL;
	MdlLowDtl(Ums_Mdl_Call, ("[OnGetEpScreenAskKeyReq] ConfID:%d  UserIndex:%d  OprScreenIndex:%d\n",
			m_pcConf->GetInsID(), tReq.m_wUserIndex));
		
	if (m_pcConf->CurState() != CUmsConfInst::inst_run)
	{
		MdlLowDtl(Ums_Mdl_Call, ("[OnGetEpScreenAskKeyReq] ConfID:%d idle\n", m_pcConf->GetInsID())); 
		return;
	}
		
	if (tReq.m_wUserIndex >= GET_EP_SCREEN_STREAM_MAX_USER)
	{
		MdlLowDtl(Ums_Mdl_Call, ("[OnGetEpScreenAskKeyReq] ConfID:%d  UserIndex:%d idle vmp info index!\n",
			m_pcConf->GetInsID()));
		return;
	}
	m_pcConf->GetVidAudEx()->AskKeyFrame(m_atEpSreenInfo[tReq.m_wUserIndex].m_wVidHandle);
}



