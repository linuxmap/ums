#include "getvidaud.h"
#include "umsobject.h"
#include "umsconfinst.h"
#include "callnodemgr.h"
#include "callmgr.h"
#include "umsnetportmgr.h"
#include "umsstackinterface.h"
#include "eventoutumscall.h"
#include "eventoutsipadapter.h"
#include "innereventumscall.h"
#include "umsbas.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpubas.h"
#endif


void DispatchBasCB(u32 dwType, void* param1, void* param2);
//////////////////////////////////////////////////////////////////////////
//许成	码流调度新版本

s8* GetVidTypeRes(EmGetVidType emType)
{
	switch(emType)
	{
	case em_GetVid_View:
		return "View";
	case em_GetVid_Poll:
		return "Poll";
	case em_GetVid_Vmp:
		return "Vmp";
	case em_GetVid_Hdu:
		return "Hdu";
	case em_GetVid_Dis:
		return "Dis";
	case em_GetVid_ViewEp:
		return "ViewEp";
	case em_GetVid_OnlyAud:
		return "OnlyAud";
	default:
		return "Invalid";
	}
}


CDispatchInfo::CDispatchInfo()
{
	m_wHandle = 0;
	Clear();
}

CDispatchInfo::~CDispatchInfo()
{

}

void CDispatchInfo::Clear()
{
	m_pcConfInst = NULL;
	m_emType = em_GetVid_Invalid;
	m_wDstEp = 0;
	m_pcVmp = NULL;
	m_bSmall = FALSE;
	m_wCount = 0;
	m_wRmtHandle = 0;
	m_wBandWidth = 0;
	m_wScreenNum = 0;
	m_wScreenIndex = TP_MAX_STREAMNUM;
	m_bAssignBw = FALSE;
	m_bFlowCtrl = FALSE;
	m_tAdjustSeat.Clear();

	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		m_aptVidAddr[wIndex] = NULL;
		m_aptAudAddr[wIndex] = NULL;
		m_aptSmallAddr[wIndex] = NULL;
		m_apcBasRes[wIndex] = NULL;
		m_abViewScreen[wIndex] = FALSE;

		m_atVidAddr[wIndex].Clear();
		m_atAudAddr[wIndex].Clear();
		m_atSmallAddr[wIndex].Clear();
	}
	m_tMixAddr.Clear();
	m_ptMixAddr = NULL;
	m_tSrcAddr.Clear();
}

void CDispatchInfo::Increment()
{
	++m_wCount;
}

void CDispatchInfo::Decrement()
{
	if (m_wCount > 0)
	{
		--m_wCount;
	}

	if (0 == m_wCount)
	{
		Release();
	}
}

void CDispatchInfo::ClearCount()
{
	m_wCount = 0;
	Release();
}

void CDispatchInfo::SetDstAddr(TGetVidInfo& tAddr)
{
	if (em_GetVid_Invalid == m_emType)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::SetDstAddr\n"));
		return ;
	}

	if (TP_MAX_STREAMNUM != m_wScreenIndex)
	{
		m_atVidAddr[MIDSCREENINDEX] = tAddr.m_atVidAddr[MIDSCREENINDEX];
		m_atAudAddr[MIDSCREENINDEX] = tAddr.m_atAudAddr[MIDSCREENINDEX];
		m_tMixAddr = tAddr.m_tMixAddr;

		if (m_bSmall)
		{
			m_atSmallAddr[MIDSCREENINDEX] = tAddr.m_atSmallVid[MIDSCREENINDEX];
		}
	}
	else
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atVidAddr[wIndex] = tAddr.m_atVidAddr[wIndex];
			m_atAudAddr[wIndex] = tAddr.m_atAudAddr[wIndex];
			
			if (m_bSmall)
			{
				m_atSmallAddr[wIndex] = tAddr.m_atSmallVid[wIndex];
			}
		}
		m_tMixAddr = tAddr.m_tMixAddr;
	}
}

void CDispatchInfo::GetLocalAddr(TGetVidInfo& tAddr)
{
	if (em_GetVid_Invalid == m_emType)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::GetLocalAddr\n"));
		return ;
	}

	if (TP_MAX_STREAMNUM != m_wScreenIndex)
	{
		if (NULL != m_aptVidAddr[MIDSCREENINDEX])
		{
			tAddr.m_atVidAddr[MIDSCREENINDEX] = *(m_aptVidAddr[MIDSCREENINDEX]);
		}
		
		if (NULL != m_aptAudAddr[MIDSCREENINDEX])
		{
			tAddr.m_atAudAddr[MIDSCREENINDEX] = *(m_aptAudAddr[MIDSCREENINDEX]);
		}

		if (NULL != m_ptMixAddr)
		{
			tAddr.m_tMixAddr = *m_ptMixAddr;
		}

		if (m_bSmall && NULL != m_aptSmallAddr[MIDSCREENINDEX])
		{
			tAddr.m_atSmallVid[MIDSCREENINDEX] = *(m_aptSmallAddr[MIDSCREENINDEX]);
		}
	}
	else
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (NULL != m_aptVidAddr[wIndex])
			{
				tAddr.m_atVidAddr[wIndex] = *(m_aptVidAddr[wIndex]);
			}
			
			if (NULL != m_aptAudAddr[wIndex])
			{
				tAddr.m_atAudAddr[wIndex] = *(m_aptAudAddr[wIndex]);
			}

			if (m_bSmall && NULL != m_aptSmallAddr[wIndex])
			{
				tAddr.m_atSmallVid[wIndex] = *(m_aptSmallAddr[wIndex]);
			}
		}
		if (NULL != m_ptMixAddr)
		{
			tAddr.m_tMixAddr = *m_ptMixAddr;
		}
	}
}

EmGetVidRes CDispatchInfo::Init(CUmsConfInst* pcConf, u16 wDstEp, EmGetVidType emType, TCallVidFormat tRcvFormat,
								BOOL32 bSmall, u16 wBandWidth, u16 wScreenNum, u16 wScreenIndex, BOOL32 bCascade, u16 wHandle)
{
	if (Working())
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::Init working.\n"));
		return em_GetVid_Invalid_Param;
	}

	if (NULL == pcConf || em_GetVid_Invalid == emType)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::Init Invalid param.\n"));
		return em_GetVid_Invalid_Param;
	}

	MdlHint(Ums_Mdl_Call, ("CDispatchInfo::Init Handle:%d, RmtHandle:%d, ConfID:%d, DstEp:%d, ScreenIndex:%d, GetVidType:%s.\n",
							m_wHandle, wHandle, pcConf->GetInsID(), wDstEp, wScreenIndex, GetVidTypeRes(emType)));

	TCallNode* ptDstNode = pcConf->GetNodeMgr()->GetNode(wDstEp);
	TCapNode* ptFatherNode = pcConf->GetNodeMgr()->GetForeFatherNode(ptDstNode);
	if (NULL == ptDstNode || NULL == ptFatherNode || !ptDstNode->IsChanOn() || !ptDstNode->IsMtEp())
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::Init  Invalid ep:%d.\n", wDstEp));
		return em_GetVid_Invalid_Param;
	}
	
     
    if (em_GetVid_OnlyAud == emType)
	{
         if (!ptDstNode->IsAudSndValid())
		 {
			 MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen emtype = em_GetVid_OnlyAud  aud-snd invalid.\n"));
             return em_GetVid_Invalid_Param;
		 }
	}
	else
	{
		if (!ptDstNode->IsVidSndValid())
		{
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::Init vid-snd invalid. snd:%d\n", ptDstNode->m_wEpID));
			return em_GetVid_Invalid_Param;
		}
	}


	if ( ptDstNode->IsSingleVidSnd() )
	{
		wScreenIndex = MIDSCREENINDEX;
	}

	m_pcConfInst = pcConf;
	m_wDstEp = wDstEp;
	m_emType = emType;
	m_tRcvFormat = tRcvFormat;
	m_bSmall = bSmall;
	m_wRmtHandle = wHandle;
	m_wBandWidth = wBandWidth;
	m_wScreenNum = wScreenNum;
	m_wScreenIndex = wScreenIndex;

	if ( ptDstNode != ptFatherNode || TP_VALID_HANDLE(wHandle) )
	{//非本级 或 上级过来调

		if (em_GetVid_OnlyAud != emType)
		{// 只调度音频，不申请宽带
			if ( !AssingBW() )
			{
				Release();
				return em_GetVid_No_BandWidth;
			}
		}

		if (!AssignLocalAddr(ptDstNode))
		{
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::Init Assigne local addr failed.\n"));
			Release();
			return em_GetVid_No_AddrResource;
		}
	}

	if (em_GetVid_View == emType)
	{
		BOOL32 bAssignBas = TRUE;
		if (ptDstNode == ptFatherNode && ptDstNode->IsThreeVidSnd() && ptDstNode->IsSmallVidSnd())
		{//三屏且有小码流 则尝试合成
			if (AssignVmp(ptDstNode, ptFatherNode))
			{
				bAssignBas = FALSE;
			}
		}

		if (bAssignBas)
		{
			if (!AssignBas(ptDstNode, ptFatherNode))
			{
				MdlError(Ums_Mdl_Call, ("CDispatchInfo::Init Assign bas failed.\n"));
				Release();
				return em_GetVide_No_BasResource;
			}
		}
		m_abViewScreen[MIDSCREENINDEX] = TRUE;
	}
	else
	{
		if (em_GetVid_ViewEp == emType)
		{
			if (!AssignBas(ptDstNode, ptFatherNode))
			{
				MdlError(Ums_Mdl_Call, ("CDispatchInfo::Init Assign bas failed.\n"));
				Release();
				return em_GetVide_No_BasResource;
			}
		}
		else
		{
			CreateSrcAddr(ptDstNode, ptFatherNode);
		}

		if ( m_wScreenIndex == TP_MAX_STREAMNUM )
		{
			ForEachChanList(ptDstNode->m_wVidSndNum, m_abViewScreen[ewIndex] = TRUE;)
		}
		else
		{
			m_abViewScreen[MIDSCREENINDEX] = TRUE;
		}
	}

	if ( ptDstNode == ptFatherNode )
	{
		if(emType != em_GetVid_OnlyAud)
		{
			pcConf->GetCallMgr()->FlowControl(GetDstEp(), FLOW_CTROL_ALL_ENC, ptDstNode->m_tVidSndFormat.m_tFormat.m_wBitrate);
			((TCapNode*)ptFatherNode)->m_tRmtChan.ResetFastStatis();
		    m_bFlowCtrl = TRUE;
		}

	}

	Increment();

	return em_GetVid_Success;
}

void CDispatchInfo::Release()
{
	if ( NULL == m_pcConfInst )
	{
		return ;
	}

	ReleaseBW(m_wScreenNum);

	if ( m_bFlowCtrl )
	{
		TCallNode* ptDstNode = m_pcConfInst->GetNodeMgr()->GetNode(GetDstEp());
		TCapNode* ptFatherNode = m_pcConfInst->GetNodeMgr()->GetForeFatherNode(ptDstNode);
		if (NULL != ptDstNode && NULL != ptFatherNode && ptDstNode->IsChanOn())
		{
			if ( ptDstNode == ptFatherNode )
			{
				m_pcConfInst->GetCallMgr()->FlowControl(GetDstEp(), FLOW_CTROL_ALL_ENC, 0);
				m_bFlowCtrl = FALSE;
			}
		}
	}

	if ( m_cDsList.GetElementNum() != 0 )
	{
		CNetPortMgr::FreeMediaTrans(m_pcConfInst, m_cDsList);
	}

	if ( m_cCascadeList.GetElementNum() != 0 )
	{
		CNetPortMgr::FreeMediaTrans(m_pcConfInst, m_cCascadeList);
	}

	ReleaseLocalAddr();
	ReleaseVmp();
	ReleaseBas();

	Clear();
}

void CDispatchInfo::UpdateCascadeTran()
{
	if (!Working())
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::UpdateCascadeTran Not in working.\n"));
		return ;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;

	if (m_wScreenIndex != TP_MAX_STREAMNUM)
	{
		TCallNode* ptDstNode = m_pcConfInst->GetNodeMgr()->GetNode(GetDstEp());
		if (NULL == ptDstNode || !ptDstNode->IsChanOn() || !ptDstNode->IsMtEp())
		{
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::UpdateCascadeTran  Invalid ep:%d.\n", GetDstEp()));
			return ;
		}
		if (m_pcConfInst->IsChairConf())
		{
			if ( NULL == m_apcBasRes[MIDSCREENINDEX] && NULL == m_pcVmp )
			{

				if (m_emType != em_GetVid_OnlyAud)
				{
					atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atVidAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_atVidAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;

					if (m_bSmall)
					{
						atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atSmallAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
						atDsData[wDsNum].m_tSndToAddr = m_atSmallAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
						++wDsNum;
					}
				}

				atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_atAudAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_tMixAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
	
			}
		}
		else
		{
			if (m_emType != em_GetVid_OnlyAud)
			{
				atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atVidAddr[MIDSCREENINDEX].m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_atVidAddr[MIDSCREENINDEX].m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_adwMediaNode[MIDSCREENINDEX];
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(MIDSCREENINDEX);
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = m_aptVidAddr[MIDSCREENINDEX]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_atVidAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;

				if (m_bSmall)
				{
					atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atSmallAddr[MIDSCREENINDEX].m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_atSmallAddr[MIDSCREENINDEX].m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_adwMediaNode[MIDSCREENINDEX];
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetSmallVideo(MIDSCREENINDEX);
					++wDsNum;
					
					atDsData[wDsNum].m_tRcvFromAddr = m_aptSmallAddr[MIDSCREENINDEX]->m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
			}

			
			atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX].m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_atAudAddr[MIDSCREENINDEX].m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_adwMediaNode[MIDSCREENINDEX];
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetAudio(MIDSCREENINDEX);
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = m_aptAudAddr[MIDSCREENINDEX]->m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_tMixAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_tMixAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_adwMediaNode[MIDSCREENINDEX];
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetEPMixAudio();
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = m_ptMixAddr->m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
			
		}
	}
	else
	{
		TCallNode* ptDstNode = m_pcConfInst->GetNodeMgr()->GetNode(m_wDstEp);
		TCapNode* ptFatherNode = m_pcConfInst->GetNodeMgr()->GetForeFatherNode(ptDstNode);
		if (NULL == ptDstNode || !ptDstNode->IsChanOn() || !ptDstNode->IsMtEp())
		{
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::UpdateCascadeTran Invalid ep.\n"));
			return ;
		}

		s32 symbolflag = 1;
		u16 wChanIndex = 0;

		if (m_pcConfInst->IsChairConf())
		{
			for (u16 wIndex = 1; wIndex <= ptFatherNode->m_wVidSndNum; ++wIndex, symbolflag *= -1)
			{
				wChanIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

				if ( NULL != m_apcBasRes[wChanIndex] && m_emType == em_GetVid_ViewEp )
				{//上级 如果有适配，Rtcp已经创建了
					continue;
				}

				if (m_emType != em_GetVid_OnlyAud)
				{
					atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atVidAddr[wChanIndex].m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_atVidAddr[wChanIndex].m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;

					if (m_bSmall)
					{
						atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atSmallAddr[wChanIndex].m_tBackRtcpAddr;
						atDsData[wDsNum].m_tSndToAddr = m_atSmallAddr[wChanIndex].m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
						++wDsNum;
					}
				}				
				
				atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atAudAddr[wChanIndex].m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_atAudAddr[wChanIndex].m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;				
				
			}

			atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_tMixAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else
		{
			for (u16 wIndex = 1; wIndex <= ptFatherNode->m_wVidSndNum; ++wIndex, symbolflag *= -1)
			{
				wChanIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
				
				if (m_emType != em_GetVid_OnlyAud)
				{
					atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atVidAddr[wChanIndex].m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_atVidAddr[wChanIndex].m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_dwMedia;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetVideo(wChanIndex);
					++wDsNum;
					
					atDsData[wDsNum].m_tRcvFromAddr = m_aptVidAddr[wChanIndex]->m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_atVidAddr[wChanIndex].m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;

					if (m_bSmall)
					{
						atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atSmallAddr[wChanIndex].m_tRtpAddr;
						atDsData[wDsNum].m_tSndToAddr = m_atSmallAddr[wChanIndex].m_tRtpAddr;
						atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_dwMedia;
						atDsData[wDsNum].m_emSwitchType = emRtpSwap;
						atDsData[wDsNum].SetSmallVideo(wChanIndex);
						++wDsNum;
						
						atDsData[wDsNum].m_tRcvFromAddr = m_aptSmallAddr[wChanIndex]->m_tBackRtcpAddr;
						atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_atAudAddr[wChanIndex].m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
						++wDsNum;
					}
				}

				
				atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_atAudAddr[wChanIndex].m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_atAudAddr[wChanIndex].m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_dwMedia;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetAudio(wChanIndex);
				++wDsNum;

				atDsData[wDsNum].m_tRcvFromAddr = m_aptAudAddr[wChanIndex]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_atAudAddr[wChanIndex].m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
				
				
			}

			atDsData[wDsNum].m_tRcvFromAddr = m_tSrcAddr.m_tMixAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_tMixAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_tSrcAddr.m_dwMedia;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetEPMixAudio();
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = m_ptMixAddr->m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}

	CNetPortMgr::MergerDsList(m_pcConfInst, m_cCascadeList, atDsData, wDsNum, "CDispatchInfo::UpdateCascadeTran");
}

void CDispatchInfo::UpdateSpeakerIndex()
{
	if (!Working())
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::UpdateSpeakerIndex Invalid working state.\n"));
		return ;
	}

	TCallNode* ptDstNode = m_pcConfInst->GetNodeMgr()->GetNode(m_wDstEp);
	TCapNode* ptFatherNode = m_pcConfInst->GetNodeMgr()->GetForeFatherNode(ptDstNode);
	if (NULL == ptDstNode || NULL == ptFatherNode || !ptDstNode->IsChanOn() || !ptDstNode->IsMtEp())
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::UpdateSpeakerIndex  Invalid ep.\n"));
		return ;
	}

	if (em_GetVid_View == m_emType)
	{
		if (NULL != m_pcVmp)
		{
			CreateDsToVmp( ptDstNode, ptFatherNode);
		}
		else
		{
			CreateSrcAddr(ptDstNode, ptFatherNode);
			CreateDsToBas(ptDstNode, ptFatherNode);
		}
	}

	if ( ( m_pcConfInst->IsChairConf() && ptDstNode != ptFatherNode)
		||  (TP_VALID_HANDLE(m_wRmtHandle)) )
	{
		UpdateCascadeTran();
	}

	return ;
}

void CDispatchInfo::ReleaseScreen(u16 wScreenIndex)
{
	if (wScreenIndex >= TP_MAX_STREAMNUM)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::ReleaseScreen Invalid index. Index:%d.\n", wScreenIndex));
		return ;
	}

	if ( m_wScreenIndex != TP_MAX_STREAMNUM )
	{//此时为一个屏的调度 则只释放中间
		wScreenIndex = MIDSCREENINDEX;
	}

	if (NULL != m_aptVidAddr[wScreenIndex])
	{
		CUmsConfInst::GetAddrList()->FreeBuff(m_aptVidAddr[wScreenIndex]);
		m_aptVidAddr[wScreenIndex] = NULL;
		m_atVidAddr[wScreenIndex].Clear();
	}

	if (NULL != m_aptAudAddr[wScreenIndex])
	{
		CUmsConfInst::GetAddrList()->FreeBuff(m_aptAudAddr[wScreenIndex]);
		m_aptAudAddr[wScreenIndex] = NULL;
		m_atAudAddr[wScreenIndex].Clear();
	}

	if (NULL != m_aptSmallAddr[wScreenIndex])
	{
		CUmsConfInst::GetAddrList()->FreeBuff(m_aptSmallAddr[wScreenIndex]);
		m_aptSmallAddr[wScreenIndex] = NULL;
		m_atSmallAddr[wScreenIndex].Clear();
	}

	if (NULL != m_apcBasRes[wScreenIndex])
	{
		m_pcConfInst->GetBas()->ReleaseScreenBas(m_apcBasRes[wScreenIndex]);
		m_apcBasRes[wScreenIndex] = NULL;
	}

	if( m_wScreenNum > 0 )
	{
		m_wScreenNum --;
		
		ReleaseBW(1);
	}

	m_abViewScreen[wScreenIndex] = FALSE;
	if (!m_abViewScreen[0] && !m_abViewScreen[1] && !m_abViewScreen[2])
	{
		Decrement();
	}
}

void CDispatchInfo::AskKeyFrame(BOOL32 bBySys)
{
	if (!Working())
	{
		return;
	}

	if (NULL != m_pcVmp)
	{
		CVmpServiceHandler* pcVmpHandler = CUmsConfInst::GetVmpServiceHandle();
		if (NULL != pcVmpHandler)
 		{
			pcVmpHandler->AskFrameToBaseService(m_pcVmp);
		}
		return ;
	}

	BOOL32 bRes = FALSE;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (NULL != m_apcBasRes[wIndex])
		{
			m_pcConfInst->GetBas()->AskFrameToScreenBas(m_apcBasRes[wIndex]);
			bRes = TRUE;
		}
	}

	if (!bRes)
	{
		if ( m_wScreenIndex == TP_MAX_STREAMNUM )
		{
			m_pcConfInst->AskKeyByEpID(m_wDstEp, EmAskKeyGetVid, GetHandle(), bBySys, bBySys);
		}
		else
		{
			m_pcConfInst->AskKeyByScreen(m_wDstEp, m_wScreenIndex, EmAskKeyGetVid, GetHandle(), bBySys, bBySys);
		}
	}
}

BOOL32 CDispatchInfo::AssignBas(TCallNode* ptDstNode, TCapNode* ptFatherNode)
{//选看需要适配

	BOOL32 bBas = FALSE;
	if (m_wScreenIndex == TP_MAX_STREAMNUM)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (NULL != m_apcBasRes[wIndex])
			{
				continue;
			}
			else
			{
				if (CTpTypeAdpt::IsVidTransNeedBas(ptFatherNode->m_tVidSndFormat.m_tFormat, m_tRcvFormat.m_tFormat))
				{
					if(m_pcConfInst->GetBas()->AssignScreenBas(m_apcBasRes[wIndex]))
					{
						m_pcConfInst->GetBas()->AdjustScreenBas(m_apcBasRes[wIndex], ptDstNode->m_wEpID, wIndex, 1, 
																&m_tRcvFormat.m_tFormat);
						m_apcBasRes[wIndex]->SetCB(DispatchBasCB, this); 

						bBas = TRUE;
					}
					else
					{
						MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignBas assign bas failed. Index:%d.\n", wIndex));
						return FALSE;
					}	
				}
			}
		}
	}
	else
	{
		u16 wIndex = MIDSCREENINDEX;

		if (CTpTypeAdpt::IsVidTransNeedBas(ptFatherNode->m_tVidSndFormat.m_tFormat, m_tRcvFormat.m_tFormat))
		{
			if(m_pcConfInst->GetBas()->AssignScreenBas(m_apcBasRes[wIndex]))
			{
				m_pcConfInst->GetBas()->AdjustScreenBas(m_apcBasRes[wIndex], ptDstNode->m_wEpID, wIndex, 1, 
														&m_tRcvFormat.m_tFormat);
				m_apcBasRes[wIndex]->SetCB(DispatchBasCB, this); 

				bBas = TRUE;
			}
			else
			{
				MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignBas assign bas failed.\n"));
				return FALSE;
			}
			
		}
	}

	if ( bBas )
	{
		CreateDsToBas(ptDstNode, ptFatherNode);
	}
	else
	{
		CreateSrcAddr(ptDstNode, ptFatherNode);
	}
	
	return TRUE;
}

void CDispatchInfo::ReleaseBas()
{
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (NULL != m_apcBasRes[wIndex])
		{
			m_pcConfInst->GetBas()->ReleaseScreenBas(m_apcBasRes[wIndex]);
			m_apcBasRes[wIndex] = NULL;
		}
	}
}

void CDispatchInfo::CreateDsToBas(TCallNode* ptDstNode, TCapNode* ptFatherNode)
{
	if (NULL == ptDstNode || NULL == ptFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::CreateDsToBas Invalid node.\n"));
		return ;
	}

	TTPMediaTransAddr tVidAddr;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;
	if (m_wScreenIndex == TP_MAX_STREAMNUM)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (NULL == m_apcBasRes[wIndex])
			{
				continue;
			}
			m_pcConfInst->GetBas()->GetInChnVidAddr(tVidAddr, m_apcBasRes[wIndex]);
			
			if ( ptDstNode == ptFatherNode )
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptFatherNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tVidAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode =  ptFatherNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wIndex);
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = tVidAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptFatherNode->m_tRmtChan.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
			else
			{
				atDsData[wDsNum].m_tRcvFromAddr = m_aptVidAddr[wIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tVidAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode =  m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wIndex);
				++wDsNum;
				
				if ( 0 != m_atVidAddr[wIndex].m_tBackRtcpAddr.GetPort() )
				{
					atDsData[wDsNum].m_tRcvFromAddr = tVidAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_atVidAddr[wIndex].m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
			}

			m_pcConfInst->GetBas()->GetOutChnVidAddr(m_tSrcAddr.m_atVidAddr[wIndex], m_apcBasRes[wIndex], m_tRcvFormat.m_tFormat);
			m_tSrcAddr.m_adwMediaNode[wIndex] = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
		}
	}
	else
	{
		u16 wIndex =MIDSCREENINDEX;
		u16 wSrcIndx = m_wScreenIndex;

		if (NULL != m_apcBasRes[wIndex])
		{
			TTPMediaTransAddr tVidAddr;
			m_pcConfInst->GetBas()->GetInChnVidAddr(tVidAddr, m_apcBasRes[wIndex]);
			
			if ( ptDstNode == ptFatherNode )
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptFatherNode->m_aptChanAddr[wSrcIndx]->m_tVid.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tVidAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode =  ptFatherNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wIndex);
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = tVidAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptFatherNode->m_tRmtChan.m_atVidEnc[wSrcIndx].m_tChanAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
			else
			{
				atDsData[wDsNum].m_tRcvFromAddr = m_aptVidAddr[wIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tVidAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode =  m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wIndex);
				++wDsNum;
				
				if ( 0 != m_atVidAddr[wIndex].m_tBackRtcpAddr.GetPort() )
				{
					atDsData[wDsNum].m_tRcvFromAddr = tVidAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = m_atVidAddr[wIndex].m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
			}
			
			m_pcConfInst->GetBas()->GetOutChnVidAddr(m_tSrcAddr.m_atVidAddr[wIndex], m_apcBasRes[wIndex], m_tRcvFormat.m_tFormat);
			m_tSrcAddr.m_adwMediaNode[wIndex] = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
			m_tSrcAddr.m_dwMedia = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;;
		}
	}

	CNetPortMgr::MergerDsList(m_pcConfInst, m_cDsList, atDsData, wDsNum, "CDispatchInfo::CreateDsToBas");
}

BOOL32 CDispatchInfo::AssignVmp(TCallNode* ptDstNode, TCapNode* ptFatherNode)
{
	if (NULL == ptDstNode || NULL == ptFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignVmp Invalid param.\n"));
		return FALSE;
	}

	if (NULL != m_pcVmp)
	{
		MdlHint(Ums_Mdl_Call, ("CDispatchInfo::AssignVmp Vmp is already assgned.\n"));
 		return TRUE;
 	}
	
 	CVmpServiceHandler* pcVmpHandler = CUmsConfInst::GetVmpServiceHandle();
 	if (NULL != pcVmpHandler)
 	{
		m_pcVmp = pcVmpHandler->Assign(VmpServiceCB, ConfInst());
 		if (NULL == m_pcVmp)
 		{
 			return FALSE;
 		}
 		else
 		{
 			TVmpUseParam tVmpParam;
			tVmpParam.m_tStyleInfo.m_emVmpStyle = em_ums_vmp_four_pic;
			tVmpParam.m_tStyleInfo.m_emShowMode = ums_vmp_lastframe_mode;
			tVmpParam.m_tStyleInfo.m_byMemberNum = TP_MAX_STREAMNUM + 1;

			tVmpParam.m_tStyleInfo.m_atMemberInfo[0].m_dwHandle = 1;
			tVmpParam.m_tStyleInfo.m_atMemberInfo[0].m_bMerged = FALSE;
			tVmpParam.m_tStyleInfo.m_atDoublePayload[0].m_byRealPayload = ptDstNode->m_tVidSndFormat.m_wStaticPayload;
			tVmpParam.m_tStyleInfo.m_atDoublePayload[0].m_byActivePayload = ptDstNode->m_tVidSndFormat.m_wDynamicPayload;

			for (u16 wIndex = 0; wIndex < 3; ++wIndex)
			{
				tVmpParam.m_tStyleInfo.m_atMemberInfo[wIndex+1].m_dwHandle = wIndex+2;
				tVmpParam.m_tStyleInfo.m_atMemberInfo[wIndex+1].m_bMerged = TRUE;
				tVmpParam.m_tStyleInfo.m_atDoublePayload[wIndex+1].m_byRealPayload = ptDstNode->m_tVidSndFormat.m_wStaticPayload;
				tVmpParam.m_tStyleInfo.m_atDoublePayload[wIndex+1].m_byActivePayload = ptDstNode->m_tVidSndFormat.m_wDynamicPayload;
			}

			tVmpParam.m_tEncParam.m_byEncType = CTpTypeAdpt::GetVidPayloadValue(m_tRcvFormat.m_tFormat.m_emFormat);
			tVmpParam.m_tEncParam.m_byFrameRate = m_tRcvFormat.m_tFormat.m_wFrameRate;
			tVmpParam.m_tEncParam.m_wBitRate = m_tRcvFormat.m_tFormat.m_wBitrate;
			if ( m_tRcvFormat.m_tFormat.m_emQualityLvl == emTPH264HP )
			{
				tVmpParam.m_tEncParam.m_byProfileType = 1;
			}
			else if( m_tRcvFormat.m_tFormat.m_emQualityLvl == emTPH264BP )
			{
				tVmpParam.m_tEncParam.m_byProfileType = 0;
			}

			CTpTypeAdpt::GetWHByVidResolution(m_tRcvFormat.m_tFormat.m_emRes, 
											tVmpParam.m_tEncParam.m_wVideoWidth,
											tVmpParam.m_tEncParam.m_wVideoHeight);

			tVmpParam.m_tEncrypt = m_pcConfInst->GetConfEncryptInfo();

 			if (!pcVmpHandler->Start(m_pcVmp, &(tVmpParam)))
			{
				ReleaseVmp();
 				MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignVmp Start vmp failed.\n"));
 				return FALSE;
 			}
 		}
 	}
	else
	{
 		MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignVmp Vmp handler is NULL.\n"));
 		return FALSE;
 	}

	CreateDsToVmp( ptDstNode, ptFatherNode);

	return TRUE;
}

void CDispatchInfo::ReleaseVmp()
{
	if (NULL != m_pcVmp)
	{
		CVmpServiceHandler* pcVmpHandler = CUmsConfInst::GetVmpServiceHandle();
		if (NULL != pcVmpHandler)
 		{
			pcVmpHandler->Release(m_pcVmp);
			m_pcVmp = NULL;
		}
	}
}

void CDispatchInfo::CreateDsToVmp(TCallNode* ptDstNode, TCapNode* ptFather)
{
	if (NULL == ptFather)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::CreateDsToVmp Invalid node.\n"));
		return ;
	}

	CVmpServiceHandler* pcVmpHandler = CUmsConfInst::GetVmpServiceHandle();
	if (NULL == pcVmpHandler)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::CreateDsToVmp Invalid vmp handler.\n"));
		return ;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;

	TServiceAddr tAddr;
	pcVmpHandler->GetRcvChanAddr(tAddr, m_pcVmp, 0);
	
	u16 wScreenIndex = ptFather->GetSpeaker();

	if ( ptDstNode != ptFather )
	{
		atDsData[wDsNum].m_tRcvFromAddr = m_aptVidAddr[wScreenIndex]->m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetVideo(wScreenIndex);
		++wDsNum;
		
		if ( m_atVidAddr[wScreenIndex].m_tBackRtcpAddr.GetPort() != 0 )
		{
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = m_atVidAddr[wScreenIndex].m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}
	else
	{
		atDsData[wDsNum].m_tRcvFromAddr = ptFather->m_aptChanAddr[wScreenIndex]->m_tVid.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptFather->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetVideo(wScreenIndex);
		++wDsNum;
		
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptFather->m_tRmtChan.m_atVidEnc[wScreenIndex].m_tChanAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}

	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		pcVmpHandler->GetRcvChanAddr(tAddr, m_pcVmp, wIndex+1);
		
		if ( ptDstNode != ptFather )
		{
			atDsData[wDsNum].m_tRcvFromAddr = m_aptSmallAddr[wIndex]->m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetSmallVideo(wScreenIndex);
			++wDsNum;
			
			if ( m_atSmallAddr[wIndex].m_tBackRtcpAddr.GetPort() != 0 )
			{
				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = m_atSmallAddr[wIndex].m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
		}
		else
		{
			atDsData[wDsNum].m_tRcvFromAddr = ptFather->m_aptSmallChanAddr[wIndex]->m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptFather->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetSmallVideo(wIndex);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptFather->m_tRmtChan.m_atSmallVidEnc[wScreenIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}
	
	pcVmpHandler->GetSndChanAddr(tAddr, m_pcVmp);

	//固定放到中间位置输出
	//视频
	m_tSrcAddr.m_adwMediaNode[MIDSCREENINDEX] = tAddr.m_dwMediaNode;
	m_tSrcAddr.m_atVidAddr[MIDSCREENINDEX] = tAddr.m_tAddr;

	//混音
	if ( ptDstNode != ptFather )
	{
		if (0 != m_tMixAddr.m_tBackRtcpAddr.GetPort())
		{
			m_tSrcAddr.m_tMixAddr = *(m_ptMixAddr);
		}
		else
		{
			m_tSrcAddr.m_tMixAddr = *(m_aptAudAddr[wScreenIndex]);
		}
	}
	else
	{
		if (NULL != ptFather->m_ptMixAddr)
		{
			m_tSrcAddr.m_tMixAddr.m_tRtpAddr = ptFather->m_ptMixAddr->m_tRtpAddr;
			m_tSrcAddr.m_tMixAddr.m_tRtcpAddr = ptFather->m_ptMixAddr->m_tRtcpForRcv;
			m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr = ptFather->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
		}
		else
		{
			m_tSrcAddr.m_tMixAddr.m_tRtpAddr = ptFather->m_aptChanAddr[wScreenIndex]->m_tAud.m_tRtpAddr;
			m_tSrcAddr.m_tMixAddr.m_tRtcpAddr = ptFather->m_aptChanAddr[wScreenIndex]->m_tAud.m_tRtcpForRcv;
			m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr = ptFather->m_tRmtChan.m_atVidEnc[wScreenIndex].m_tChanAddr.m_tBackRtcpAddr;
		}
	}

	//音频
	m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX] = m_tSrcAddr.m_tMixAddr;
		
	CNetPortMgr::MergerDsList(m_pcConfInst, m_cDsList, atDsData, wDsNum, "CDispatchInfo::CreateDsToVmp");
}

void CDispatchInfo::CreateSrcAddr(TCallNode* ptDstNode, TCapNode* ptFatherNode)
{
	if (NULL == ptDstNode || NULL == ptFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::CreateDs Invalid node.\n"));
		return ;
	}

	if (ptDstNode == ptFatherNode)
	{
		if ( m_wScreenIndex != TP_MAX_STREAMNUM )
		{
			u16 wChanIndex = m_wScreenIndex;

			if (em_GetVid_OnlyAud != m_emType)
			{
				m_tSrcAddr.m_atVidAddr[MIDSCREENINDEX].m_tRtpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
				m_tSrcAddr.m_atVidAddr[MIDSCREENINDEX].m_tRtcpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtcpForRcv;
				m_tSrcAddr.m_atVidAddr[MIDSCREENINDEX].m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;

				if (m_bSmall && NULL != ptFatherNode->m_aptSmallChanAddr[MIDSCREENINDEX])
				{
					m_tSrcAddr.m_atSmallAddr[MIDSCREENINDEX].m_tRtpAddr = ptFatherNode->m_aptSmallChanAddr[wChanIndex]->m_tRtpAddr;
					m_tSrcAddr.m_atSmallAddr[MIDSCREENINDEX].m_tRtcpAddr = ptFatherNode->m_aptSmallChanAddr[wChanIndex]->m_tRtcpForRcv;
					m_tSrcAddr.m_atSmallAddr[MIDSCREENINDEX].m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_atSmallVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
				}
			}
			
			m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX].m_tRtpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tAud.m_tRtpAddr;
			m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX].m_tRtcpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tAud.m_tRtcpForRcv;
			m_tSrcAddr.m_atAudAddr[MIDSCREENINDEX].m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_atAudEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;		
			
			m_tSrcAddr.m_adwMediaNode[MIDSCREENINDEX] = ptFatherNode->m_tMediaEqp.m_dwEqpNode;

			if (NULL != ptFatherNode->m_ptMixAddr)
			{
				m_tSrcAddr.m_tMixAddr.m_tRtpAddr = ptFatherNode->m_ptMixAddr->m_tRtpAddr;
				m_tSrcAddr.m_tMixAddr.m_tRtcpAddr = ptFatherNode->m_ptMixAddr->m_tRtcpForRcv;
				m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
			}
			m_tSrcAddr.m_dwMedia =  ptFatherNode->m_tMediaEqp.m_dwEqpNode;
		}
		else
		{
			s32 symbolflag = 1;
			u16 wChanIndex = 0;
			for (u16 wIndex = 1; wIndex <= ptFatherNode->m_wVidSndNum; ++wIndex, symbolflag *= -1)
			{
				wChanIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

				if (em_GetVid_OnlyAud != m_emType)
				{
					m_tSrcAddr.m_atVidAddr[wChanIndex].m_tRtpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
					m_tSrcAddr.m_atVidAddr[wChanIndex].m_tRtcpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtcpForRcv;
					m_tSrcAddr.m_atVidAddr[wChanIndex].m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
				
					if (m_bSmall && NULL != ptFatherNode->m_aptSmallChanAddr[wChanIndex])
					{
						m_tSrcAddr.m_atSmallAddr[wChanIndex].m_tRtpAddr = ptFatherNode->m_aptSmallChanAddr[wChanIndex]->m_tRtpAddr;
						m_tSrcAddr.m_atSmallAddr[wChanIndex].m_tRtcpAddr = ptFatherNode->m_aptSmallChanAddr[wChanIndex]->m_tRtcpForRcv;
						m_tSrcAddr.m_atSmallAddr[wChanIndex].m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_atSmallVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
					}
				}			
				
				m_tSrcAddr.m_atAudAddr[wChanIndex].m_tRtpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tAud.m_tRtpAddr;
				m_tSrcAddr.m_atAudAddr[wChanIndex].m_tRtcpAddr = ptFatherNode->m_aptChanAddr[wChanIndex]->m_tAud.m_tRtcpForRcv;
				m_tSrcAddr.m_atAudAddr[wChanIndex].m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_atAudEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
				
				
				
				m_tSrcAddr.m_adwMediaNode[wChanIndex] = ptFatherNode->m_tMediaEqp.m_dwEqpNode;
			}
			
			if (NULL != ptFatherNode->m_ptMixAddr)
			{
				m_tSrcAddr.m_tMixAddr.m_tRtpAddr = ptFatherNode->m_ptMixAddr->m_tRtpAddr;
				m_tSrcAddr.m_tMixAddr.m_tRtcpAddr = ptFatherNode->m_ptMixAddr->m_tRtcpForRcv;
				m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr = ptFatherNode->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
			}
			m_tSrcAddr.m_dwMedia =  ptFatherNode->m_tMediaEqp.m_dwEqpNode;
		}
	}
	else
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (NULL != m_aptVidAddr[wIndex])
			{
				m_tSrcAddr.m_atVidAddr[wIndex] = *m_aptVidAddr[wIndex];
			}

			if (NULL != m_aptAudAddr[wIndex])
			{
				m_tSrcAddr.m_atAudAddr[wIndex] = *m_aptAudAddr[wIndex];
			}

			if (m_bSmall && NULL != m_aptSmallAddr[wIndex])
			{
				m_tSrcAddr.m_atSmallAddr[wIndex] = *m_aptSmallAddr[wIndex];
			}

			m_tSrcAddr.m_adwMediaNode[wIndex] = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
		}

		if (NULL != m_ptMixAddr)
		{
			m_tSrcAddr.m_tMixAddr = *m_ptMixAddr;
		}

		m_tSrcAddr.m_dwMedia = m_pcConfInst->GetConfEqpDs().m_dwEqpNode;
	}
}

BOOL32 CDispatchInfo::AssignLocalAddr(TCallNode* ptNode)
{
	if (NULL == ptNode)
	{
		MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Invalid node.\n"));
		return FALSE;
	}

	ReleaseLocalAddr();

	if (m_wScreenIndex != TP_MAX_STREAMNUM)
	{
		u16 wIndex = MIDSCREENINDEX;

		if (em_GetVid_OnlyAud != m_emType)
		{
			m_aptVidAddr[wIndex] = CUmsConfInst::GetAddrList()->AllocNode();
			if (NULL == m_aptVidAddr[wIndex])
			{
				MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local vid-address failed.\n"));
				ReleaseLocalAddr();
				return FALSE;
			}
			else
			{
				m_aptVidAddr[wIndex]->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
			}

			if (m_bSmall)
			{
				m_aptSmallAddr[wIndex] = CUmsConfInst::GetAddrList()->AllocNode();
				if (NULL == m_aptSmallAddr[wIndex])
				{
					MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local small-address failed.\n"));
					ReleaseLocalAddr();
					return FALSE;
				}
				else
				{
					m_aptSmallAddr[wIndex]->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
				}
			}
		}

		m_aptAudAddr[wIndex] = CUmsConfInst::GetAddrList()->AllocNode();
		if (NULL == m_aptAudAddr[wIndex])
		{
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local aud-address failed.\n"));
			ReleaseLocalAddr();
			return FALSE;
		}
		else
		{
			m_aptAudAddr[wIndex]->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
		}

		m_ptMixAddr = CUmsConfInst::GetAddrList()->AllocNode();
		if (NULL == m_ptMixAddr)
		{
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local mix-address failed.\n"));
			ReleaseLocalAddr();
			return FALSE;
		}
		else
		{
			m_ptMixAddr->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
		}
	}
	else
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (em_GetVid_OnlyAud != m_emType)
			{
				m_aptVidAddr[wIndex] = CUmsConfInst::GetAddrList()->AllocNode();
				if (NULL == m_aptVidAddr[wIndex])
				{
					MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local vid-address failed.\n"));
					ReleaseLocalAddr();
					return FALSE;
				}
				else
				{
					m_aptVidAddr[wIndex]->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
				}

				if (m_bSmall)
				{
					m_aptSmallAddr[wIndex] = CUmsConfInst::GetAddrList()->AllocNode();
					if (NULL == m_aptSmallAddr[wIndex])
					{
						MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local small-address failed.\n"));
						ReleaseLocalAddr();
						return FALSE;
					}
					else
					{
						m_aptSmallAddr[wIndex]->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
					}
				}
			}
		
			m_aptAudAddr[wIndex] = CUmsConfInst::GetAddrList()->AllocNode();
			if (NULL == m_aptAudAddr[wIndex])
			{
				MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local aud-address failed.\n"));
				ReleaseLocalAddr();
				return FALSE;
			}
			else
			{
				m_aptAudAddr[wIndex]->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
			}

		}

		m_ptMixAddr = CUmsConfInst::GetAddrList()->AllocNode();
		if (NULL == m_ptMixAddr)
		{
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local mix-address failed.\n"));
			ReleaseLocalAddr();
			return FALSE;
		}
		else
		{
			m_ptMixAddr->SetIP(m_pcConfInst->GetConfEqpDs().m_dwEqpIp);
		}
	}

	return TRUE;
}

void CDispatchInfo::ReleaseLocalAddr()
{
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (NULL != m_aptVidAddr[wIndex])
		{
			CUmsConfInst::GetAddrList()->FreeBuff(m_aptVidAddr[wIndex]);
			m_aptVidAddr[wIndex] = NULL;
		}
		m_atVidAddr[wIndex].Clear();

		if (NULL != m_aptAudAddr[wIndex])
		{
			CUmsConfInst::GetAddrList()->FreeBuff(m_aptAudAddr[wIndex]);
			m_aptAudAddr[wIndex] = NULL;
		}
		m_atAudAddr[wIndex].Clear();

		if (NULL != m_aptSmallAddr[wIndex])
		{
			CUmsConfInst::GetAddrList()->FreeBuff(m_aptSmallAddr[wIndex]);
			m_aptSmallAddr[wIndex] = NULL;
		}
		m_atSmallAddr[wIndex].Clear();
	}

	if (NULL != m_ptMixAddr)
	{
		CUmsConfInst::GetAddrList()->FreeBuff(m_ptMixAddr);
		m_ptMixAddr = NULL;
	}
	m_tMixAddr.Clear();
}

BOOL32 CDispatchInfo::AssingBW()
{
	BOOL32 bBW = TRUE;
	if ( !m_pcConfInst->IsChairConf() )
	{
		switch (m_emType)
		{
		case em_GetVid_ViewEp:
		case em_GetVid_View:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneUpBW(m_wBandWidth*m_wScreenNum, em_View_SelView);
			}
			break;
			
		case em_GetVid_Poll:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneUpBW(m_wBandWidth*m_wScreenNum, em_View_Poll);
			}
			break;
			
		case em_GetVid_Vmp:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneUpBW(m_wBandWidth*m_wScreenNum, em_View_Vmp);
			}
			break;
			
		case em_GetVid_Hdu:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneUpBW(m_wBandWidth*m_wScreenNum, em_View_TV);
			}
			break;
			
		case em_GetVid_Dis:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneUpBW(m_wBandWidth*m_wScreenNum, em_View_Dis);
			}
			break;
		}
	}
	else
	{
		switch (m_emType)
		{
		case em_GetVid_ViewEp:
		case em_GetVid_View:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneDownBW(m_wBandWidth*m_wScreenNum, em_View_SelView);
			}
			break;
			
		case em_GetVid_Poll:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneDownBW(m_wBandWidth*m_wScreenNum, em_View_Poll);
			}
			break;
			
		case em_GetVid_Vmp:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneDownBW(m_wBandWidth*m_wScreenNum, em_View_Vmp);
			}
			break;
			
		case em_GetVid_Hdu:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneDownBW(m_wBandWidth*m_wScreenNum, em_View_TV);
			}
			break;
			
		case em_GetVid_Dis:
			{
				bBW = m_pcConfInst->GetBandWidth().AssigneDownBW(m_wBandWidth*m_wScreenNum, em_View_Dis);
			}
			break;
		}
	}

	if ( bBW )
	{
		m_bAssignBw = TRUE;
	}

	return bBW;
}

void CDispatchInfo::ReleaseBW(u16 wScreenNum)
{
	if ( !m_bAssignBw )
	{
		return ;
	}
	if ( !m_pcConfInst->IsChairConf() )
	{//下级上行
		switch (m_emType)
		{
		case em_GetVid_ViewEp:
		case em_GetVid_View:
			{
				m_pcConfInst->GetBandWidth().ReleaseUpBW(m_wBandWidth*wScreenNum, em_View_SelView);
			}
			break;
			
		case em_GetVid_Poll:
			{
				m_pcConfInst->GetBandWidth().ReleaseUpBW(m_wBandWidth*wScreenNum, em_View_Poll);
			}
			break;
			
		case em_GetVid_Vmp:
			{
				m_pcConfInst->GetBandWidth().ReleaseUpBW(m_wBandWidth*wScreenNum, em_View_Vmp);
			}
			break;
			
		case em_GetVid_Hdu:
			{
				m_pcConfInst->GetBandWidth().ReleaseUpBW(m_wBandWidth*wScreenNum, em_View_TV);
			}
			break;
			
		case em_GetVid_Dis:
			{
				m_pcConfInst->GetBandWidth().ReleaseUpBW(m_wBandWidth*wScreenNum, em_View_Dis);
			}
			break;
		}
	}
	else
	{//上级下行
		switch (m_emType)
		{
		case em_GetVid_ViewEp:
		case em_GetVid_View:
			{
				m_pcConfInst->GetBandWidth().ReleaseDownBW(m_wBandWidth*wScreenNum, em_View_SelView);
			}
			break;
			
		case em_GetVid_Poll:
			{
				m_pcConfInst->GetBandWidth().ReleaseDownBW(m_wBandWidth*wScreenNum, em_View_Poll);
			}
			break;
			
		case em_GetVid_Vmp:
			{
				m_pcConfInst->GetBandWidth().ReleaseDownBW(m_wBandWidth*wScreenNum, em_View_Vmp);
			}
			break;
			
		case em_GetVid_Hdu:
			{
				m_pcConfInst->GetBandWidth().ReleaseDownBW(m_wBandWidth*wScreenNum, em_View_TV);
			}
			break;
			
		case em_GetVid_Dis:
			{
				m_pcConfInst->GetBandWidth().ReleaseDownBW(m_wBandWidth*wScreenNum, em_View_Dis);
			}
			break;
		}
	}
}

void DispatchBasCB(u32 dwType, void* param1, void* param2)
{
#ifdef _USE_XMPUEQP_
    tXmpuBasCbData *pBasCbData = (tXmpuBasCbData *)param1;

	CUmsConfInst* pInst = (CUmsConfInst*)pBasCbData->pService;
    CDispatchInfo* pcInfo = (CDispatchInfo*)pBasCbData->pParam;
	CScreenBasRes* ptBasRes = (CScreenBasRes*)pBasCbData->pRes;
	TXmpuStartBasNty tStartBastNty;
	BOOL32 bError = FALSE;	
	EmGetVidType	GetVidType = pcInfo->GetVidType();

	if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		memcpy(&tStartBastNty, pBasCbData->pData, sizeof(tStartBastNty));  
		if (!tStartBastNty.m_bSuccess)
		{
			bError = TRUE;
			MdlError(Ums_Mdl_Call, ("CDispatchInfo::BasCB. AssignBas Fail!  ConfID:%d, EqpID:%d, GetVidtype:%d, bSuccess:%d\n", 
				pInst->GetInsID(), ptBasRes->GetBasEqpId(), GetVidType, tStartBastNty.m_bSuccess));
		} else
		{   
			ptBasRes->m_tXmpuBas.m_emStat = EmXmpuResStatInfo_Running;
			pInst->GetBas()->SetXmpuVidBasAssignAddr(&ptBasRes->m_tXmpuBas, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);
			CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, &ptBasRes->m_tXmpuBas);

			TCallVidFormat tAdjFmat = pcInfo->VidFormat();
			pInst->GetBas()->AdjustScreenBas(ptBasRes, ptBasRes->m_wSrcEp, ptBasRes->m_wSrcScreenIndx, 1, 
														&tAdjFmat.m_tFormat);
		}
	
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		//
		
	} else if (dwType == evXmpu_AskBasKey_Req)
	{
		pcInfo->ConfInst()->AskKeyByEpID(pcInfo->GetDstEp(), EmAskKeyGetVid, pcInfo->GetHandle(), 0, FALSE);
		
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
         bError = TRUE;

		 MdlError(Ums_Mdl_Call, ("CDispatchInfo::BasCB. BasDisConnect !  ConfID:%d, EqpID:%d, GetVidtype:%d\n", 
			 pInst->GetInsID(), ptBasRes->GetBasEqpId(), GetVidType));
	}

	if(bError)
	{
		if( pcInfo->ConfInst()->IsChairConf() )
		{
			CUmsConfInst::GetVidFailedCB(pcInfo->ConfInst(), pcInfo->GetHandle(), pcInfo->GetVidType(), EmGetVidRet_BasDisCnnt);
		}
		else
		{
			TGetVidInfoRes tRes;
			
			tRes.m_emRes = em_GetVide_No_BasResource;
			
			tRes.m_tInfo.m_tBaseInfo.m_wEpID = pcInfo->GetDstEp();
			tRes.m_tInfo.m_tBaseInfo.m_emType = pcInfo->GetVidType(); 
			tRes.m_tInfo.m_tBaseInfo.m_wHandle = pcInfo->GetRmtHandle();
			
			TUmsHandle tOutHandle;
			pcInfo->ConfInst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, ev_GetVid_Res, &tRes, sizeof(tRes));
		}	
		pcInfo->Decrement();
	}

#else

	CDispatchInfo* pcInfo = (CDispatchInfo*)param1;
	
	switch (dwType)
	{
	case CScreenBasRes::VidBasCB_AskKey:
		{
			pcInfo->ConfInst()->AskKeyByEpID(pcInfo->GetDstEp(), EmAskKeyGetVid, pcInfo->GetHandle(), 0, FALSE);
		}
		break;
		
	case CScreenBasRes::VidBasCB_DisConnect:
	case CScreenBasRes::VidBasCB_NAck:
		{
			if( pcInfo->ConfInst()->IsChairConf() )
			{
				CUmsConfInst::GetVidFailedCB(pcInfo->ConfInst(), pcInfo->GetHandle(), pcInfo->GetVidType(), EmGetVidRet_BasDisCnnt);
			}
			else
			{
				TGetVidInfoRes tRes;
				
				tRes.m_emRes = em_GetVide_No_BasResource;
				
				tRes.m_tInfo.m_tBaseInfo.m_wEpID = pcInfo->GetDstEp();
				tRes.m_tInfo.m_tBaseInfo.m_emType = pcInfo->GetVidType(); 
				tRes.m_tInfo.m_tBaseInfo.m_wHandle = pcInfo->GetRmtHandle();
				
				TUmsHandle tOutHandle;
				pcInfo->ConfInst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
				UmsSendConfCtrl(tOutHandle, ev_GetVid_Res, &tRes, sizeof(tRes));
			}
			
			pcInfo->Decrement();
		}
		break;
	}

#endif

}

void CDispatchInfo::VmpServiceCB( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, void* param, u16 wTmp1 )
{
	CUmsConfInst* pcInst = (CUmsConfInst*)param;
	CDispatchInfo* pcInfo = CUmsConfInst::GetVidAudEx()->Find(pcInst, pcService);

	if (!pcInfo)
	{
		return ;
	}

	if ( emRes == em_Service_No_Reg
		|| emRes == em_Start_Failed
		|| emRes == em_Stop_Failed
		|| emRes == em_Mdy_Failed
		|| emRes == em_Invalid_Param
		|| emRes == em_Set_Param_Failed)
	{
		MdlHint(Ums_Mdl_Call, ("CDispatchInfo::VmpServiceCB. ConfID:%d, ServiceID:%d, CBType:%d, emRes:%d\n", 
			pcInfo->ConfInst()->GetInsID(), pcService->GetServiceID(), emOpType, emRes));

		if ( pcInfo->ConfInst()->IsChairConf() )
		{
			CUmsConfInst::GetVidFailedCB(pcInfo->ConfInst(), pcInfo->GetHandle(), pcInfo->GetVidType(), EmGetVidRet_VmpDisCnnt);
		}
		else
		{
			TGetVidInfoRes tRes;
			tRes.m_emRes = em_GetVid_DownUmVmpDisconnect;
			tRes.m_tInfo.m_tBaseInfo.m_wEpID = pcInfo->GetDstEp();
			tRes.m_tInfo.m_tBaseInfo.m_emType = pcInfo->GetVidType(); 
			tRes.m_tInfo.m_tBaseInfo.m_wHandle = pcInfo->GetRmtHandle();
			
			TUmsHandle tOutHandle;
			pcInfo->ConfInst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, ev_GetVid_Res, &tRes, sizeof(tRes));
		}

		pcInfo->Decrement();
	}
	else if ( emRes == em_Res_Success )
	{
		if ( emOpType == em_Frame_Service )
		{
			u16 wScreenIndx = MIDSCREENINDEX;
			if ( wTmp1 == 0 )
			{//大图像 取发言坐席
				TCallNode* ptNode = pcInfo->ConfInst()->GetNodeMgr()->GetNode(pcInfo->GetDstEp());
				if( NULL != ptNode )
				{
					wScreenIndx = ptNode->GetSpeaker();
				}
			}
			else if( wTmp1 >= 1 )
			{//小图像 取对应坐席
				wScreenIndx = wTmp1 - 1;
			}
			pcInfo->ConfInst()->AskKeyByScreen(pcInfo->GetDstEp(), wScreenIndx, EmAskKeyGetVid, pcInfo->GetHandle());
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("CDispatchInfo::VmpServiceCB. ConfID:%d, ServiceID:%d, CBType:%d, emRes:%d\n", 
				pcInfo->ConfInst()->GetInsID(), pcService->GetServiceID(), emOpType, emRes));
		}
	}
}

void CDispatchInfo::Show( u16 wConfID )
{
	if ( !Working() || ConfInst()->GetInsID() != wConfID )
	{
		return ;
	}
	msgprintnotime(" Handle:%d, RmtHandle:%d, DstEp:%d, ScreenIndex:%d, %s, Count:%d, Bw:%d, Small:%d, Adj:%d, Screen(%d, %d, %d)\n", 
			GetHandle(), GetRmtHandle(), GetDstEp(), m_wScreenIndex, GetVidTypeRes(m_emType), 
			m_wCount, m_wBandWidth, m_bSmall, m_tAdjustSeat.IsAdjust(), m_abViewScreen[0], m_abViewScreen[1], m_abViewScreen[2]);

	if( NULL != m_pcVmp )
	{
		msgprintnotime("  ");
		CUmsConfInst::GetVmpServiceHandle()->Show(m_pcVmp);
	}

	u16 wIndex = 0;

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_apcBasRes[wIndex] )
		{
			continue;
		}
		msgprintnotime("  BAS Index%d EqpID%d, ChanIndex:%d\n\n", wIndex, 
			m_apcBasRes[wIndex]->GetBasEqpId(), m_apcBasRes[wIndex]->GetBasChnIndex());
	}
	
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_aptVidAddr[wIndex] )
		{
			continue;
		}

		msgprintnotime("  Vid Rtp"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", DstRtp"ADDRPORT_FORMAT", DstRtcp"ADDRPORT_FORMAT"\n", 
			ADDRPORT(m_aptVidAddr[wIndex]->m_tRtpAddr.m_dwIP, m_aptVidAddr[wIndex]->m_tRtpAddr.m_wPort),
			ADDRPORT(m_aptVidAddr[wIndex]->m_tBackRtcpAddr.m_dwIP, m_aptVidAddr[wIndex]->m_tBackRtcpAddr.m_wPort),
			ADDRPORT(m_atVidAddr[wIndex].m_tRtpAddr.m_dwIP, m_atVidAddr[wIndex].m_tRtpAddr.m_wPort),
			ADDRPORT(m_atVidAddr[wIndex].m_tBackRtcpAddr.m_dwIP, m_atVidAddr[wIndex].m_tBackRtcpAddr.m_wPort));
	}

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_aptAudAddr[wIndex] )
		{
			continue;
		}
		
		msgprintnotime("  Aud Rtp"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", DstRtp"ADDRPORT_FORMAT", DstRtcp"ADDRPORT_FORMAT"\n", 
			ADDRPORT(m_aptAudAddr[wIndex]->m_tRtpAddr.m_dwIP, m_aptAudAddr[wIndex]->m_tRtpAddr.m_wPort),
			ADDRPORT(m_aptAudAddr[wIndex]->m_tBackRtcpAddr.m_dwIP, m_aptAudAddr[wIndex]->m_tBackRtcpAddr.m_wPort),
			ADDRPORT(m_atAudAddr[wIndex].m_tRtpAddr.m_dwIP, m_atAudAddr[wIndex].m_tRtpAddr.m_wPort),
			ADDRPORT(m_atAudAddr[wIndex].m_tBackRtcpAddr.m_dwIP, m_atAudAddr[wIndex].m_tBackRtcpAddr.m_wPort));
	}

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == m_aptSmallAddr[wIndex] )
		{
			continue;
		}
		
		msgprintnotime("  SmallVid Rtp"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", DstRtp"ADDRPORT_FORMAT", DstRtcp"ADDRPORT_FORMAT"\n", 
			ADDRPORT(m_aptSmallAddr[wIndex]->m_tRtpAddr.m_dwIP, m_aptSmallAddr[wIndex]->m_tRtpAddr.m_wPort),
			ADDRPORT(m_aptSmallAddr[wIndex]->m_tBackRtcpAddr.m_dwIP, m_aptSmallAddr[wIndex]->m_tBackRtcpAddr.m_wPort),
			ADDRPORT(m_atSmallAddr[wIndex].m_tRtpAddr.m_dwIP, m_atSmallAddr[wIndex].m_tRtpAddr.m_wPort),
			ADDRPORT(m_atSmallAddr[wIndex].m_tBackRtcpAddr.m_dwIP, m_atSmallAddr[wIndex].m_tBackRtcpAddr.m_wPort));
	}

	if ( NULL != m_ptMixAddr )
	{
		msgprintnotime("  MixAud Rtp:"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", DstRtp"ADDRPORT_FORMAT", DstRtcp"ADDRPORT_FORMAT"\n", 
			ADDRPORT(m_ptMixAddr->m_tRtpAddr.m_dwIP, m_ptMixAddr->m_tRtpAddr.m_wPort),
			ADDRPORT(m_ptMixAddr->m_tBackRtcpAddr.m_dwIP, m_ptMixAddr->m_tBackRtcpAddr.m_wPort),
			ADDRPORT(m_tMixAddr.m_tRtpAddr.m_dwIP, m_tMixAddr.m_tRtpAddr.m_wPort),
			ADDRPORT(m_tMixAddr.m_tBackRtcpAddr.m_dwIP, m_tMixAddr.m_tBackRtcpAddr.m_wPort));
	}


    msgprintnotime("TGetVidAddr:\n");
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (m_tSrcAddr.m_atVidAddr[wIndex].m_tRtpAddr.m_dwIP != 0 && m_tSrcAddr.m_atVidAddr[wIndex].m_tRtpAddr.m_wPort != 0)
		{
			msgprintnotime("  TGetVidAddr  vid:%d  Rtp:"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", BackRtcp"ADDRPORT_FORMAT"\n", 
				   wIndex,
				   ADDRPORT(m_tSrcAddr.m_atVidAddr[wIndex].m_tRtpAddr.m_dwIP, m_tSrcAddr.m_atVidAddr[wIndex].m_tRtpAddr.m_wPort),
				   ADDRPORT(m_tSrcAddr.m_atVidAddr[wIndex].m_tRtcpAddr.m_dwIP, m_tSrcAddr.m_atVidAddr[wIndex].m_tRtcpAddr.m_wPort),
			       ADDRPORT(m_tSrcAddr.m_atVidAddr[wIndex].m_tBackRtcpAddr.m_dwIP, m_tSrcAddr.m_atVidAddr[wIndex].m_tBackRtcpAddr.m_wPort));
		}
	
	}

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (m_tSrcAddr.m_atAudAddr[wIndex].m_tRtpAddr.m_dwIP != 0 && m_tSrcAddr.m_atAudAddr[wIndex].m_tRtpAddr.m_wPort != 0)
		{
			msgprintnotime("  TGetVidAddr  Aud:%d  Rtp:"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", BackRtcp"ADDRPORT_FORMAT"\n", 
				  wIndex,
				  ADDRPORT(m_tSrcAddr.m_atAudAddr[wIndex].m_tRtpAddr.m_dwIP,      m_tSrcAddr.m_atAudAddr[wIndex].m_tRtpAddr.m_wPort),
				  ADDRPORT(m_tSrcAddr.m_atAudAddr[wIndex].m_tRtcpAddr.m_dwIP,     m_tSrcAddr.m_atAudAddr[wIndex].m_tRtcpAddr.m_wPort),
			      ADDRPORT(m_tSrcAddr.m_atAudAddr[wIndex].m_tBackRtcpAddr.m_dwIP, m_tSrcAddr.m_atAudAddr[wIndex].m_tBackRtcpAddr.m_wPort));
		}
		
	}

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{

		if (m_tSrcAddr.m_atSmallAddr[wIndex].m_tRtpAddr.m_dwIP != 0 && m_tSrcAddr.m_atSmallAddr[wIndex].m_tRtpAddr.m_wPort != 0)
		{
			msgprintnotime("  TGetVidAddr  SmallAddr:%d  Rtp:"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", BackRtcp"ADDRPORT_FORMAT"\n", 
				  wIndex,
				  ADDRPORT(m_tSrcAddr.m_atSmallAddr[wIndex].m_tRtpAddr.m_dwIP,      m_tSrcAddr.m_atSmallAddr[wIndex].m_tRtpAddr.m_wPort),
				  ADDRPORT(m_tSrcAddr.m_atSmallAddr[wIndex].m_tRtcpAddr.m_dwIP,     m_tSrcAddr.m_atSmallAddr[wIndex].m_tRtcpAddr.m_wPort),
			      ADDRPORT(m_tSrcAddr.m_atSmallAddr[wIndex].m_tBackRtcpAddr.m_dwIP, m_tSrcAddr.m_atSmallAddr[wIndex].m_tBackRtcpAddr.m_wPort));
		}
		
	}

	if (m_tSrcAddr.m_tMixAddr.m_tRtpAddr.m_dwIP != 0 && m_tSrcAddr.m_tMixAddr.m_tRtpAddr.m_wPort != 0)
	{

		msgprintnotime("  TGetVidAddr  MixAddr  Rtp:"ADDRPORT_FORMAT", Rtcp"ADDRPORT_FORMAT", BackRtcp"ADDRPORT_FORMAT"\n", 
			  ADDRPORT(m_tSrcAddr.m_tMixAddr.m_tRtpAddr.m_dwIP,      m_tSrcAddr.m_tMixAddr.m_tRtpAddr.m_wPort),
			  ADDRPORT(m_tSrcAddr.m_tMixAddr.m_tRtcpAddr.m_dwIP,     m_tSrcAddr.m_tMixAddr.m_tRtcpAddr.m_wPort),
		      ADDRPORT(m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr.m_dwIP, m_tSrcAddr.m_tMixAddr.m_tBackRtcpAddr.m_wPort));
	}


	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (m_tSrcAddr.m_adwMediaNode[wIndex] != 0)
		{
			msgprintnotime("  TGetVidAddr MediaNode  index%d : %d\n", wIndex, m_tSrcAddr.m_adwMediaNode[wIndex]);
		}
	}

	if (m_tSrcAddr.m_dwMedia != 0)
	{
        msgprintnotime(" TGetVidAddr mix MediaNode  : %d\n\n", m_tSrcAddr.m_dwMedia);
	}

	return ;
}

//////////////////////////////////////////////////////////////////////////
CGetVidAudEx::CGetVidAudEx()
{
	for ( u16 wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; wIndex ++ )
	{
		m_acDispatchInfo[wIndex].SetHandle(wIndex);
	}
	m_wLastIndx = 0;
}

CGetVidAudEx::~CGetVidAudEx()
{

}

BOOL32 CGetVidAudEx::Handler(CUmsConfInst* pcConf, CTpMsg* const pcMsg)
{
	if (NULL == pcConf || NULL == pcMsg)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Handler Invalid param.\n"));
		return FALSE;
	}

	switch (pcMsg->GetEvent())
	{
	case ev_GetVid_Req:
		{
			EventGetVidReq(pcConf, pcMsg);
		}
		break;

	case ev_GetVid_Res:
		{
			EventGetVidRes(pcConf, pcMsg);
		}
		break;

	case ev_GetVid_Stop_Req:
		{
			EventStopGetVidReq(pcConf, pcMsg);
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

void CGetVidAudEx::EventGetVidReq(CUmsConfInst* pcConf, CTpMsg* const pcMsg)
{
	TUmsHandle tHandle;
	TGetVidInfo tInfo;
	TP_SAFE_CAST(tHandle, pcMsg->GetBody());
	TP_SAFE_CAST(tInfo, pcMsg->GetBody()+sizeof(TUmsHandle));

	TUmsHandle tOutHandle;
	pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, tHandle.GetEpID());

	TGetVidInfoRes tRes;
	memcpy(&tRes.m_tInfo, &tInfo, sizeof(tInfo));
	u16 wIndex = TP_UMS_MAX_CALLNUM;
	BOOL32 bIsThreeScrEp = FALSE;
	do 
	{
		TCapNode* ptDstNode = pcConf->GetNodeMgr()->GetForeFatherNode(tInfo.m_tBaseInfo.m_wEpID);
		if (NULL == ptDstNode || !ptDstNode->IsChanOn() || !ptDstNode->IsMtEp())
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::EventGetVidReq Not invalid ep.\n"));
			tRes.m_emRes = em_GetVid_Invalid_Param;
			break;
		}

	    ReleaseRepeatdGetVidAudForDown(pcConf, tInfo.m_tBaseInfo.m_emType, tInfo.m_tBaseInfo.m_wEpID, tInfo.m_tBaseInfo.m_wScreenIndex);

		if (em_GetVid_OnlyAud == tInfo.m_tBaseInfo.m_emType)
		{
            if (!ptDstNode->IsAudSndValid())
			{
				MdlError(Ums_Mdl_Call, ("CGetVidAudEx::EventGetVidReq. type= em_GetVid_OnlyAud ep AudSnd Invalid.\n"));
				tRes.m_emRes = em_GitVid_No_Resource;
				break;
			}
		}
		else 
		{
			if ( !ptDstNode->IsVidSndValid())
			{
				MdlError(Ums_Mdl_Call, ("CGetVidAudEx::EventGetVidReq. ep VidSnd Invalid.\n"));
				tRes.m_emRes = em_GitVid_No_Resource;
				break;
			}
		}

		bIsThreeScrEp = ptDstNode->IsThreeVidSnd();

		wIndex = FindIdle();
		if (TP_UMS_MAX_CALLNUM == wIndex)
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::EventGetVidReq No idle resourece.\n"));
			tRes.m_emRes = em_GitVid_No_Resource;
			break;
		}

		u16	wScreenNum = ptDstNode->m_wVidSndNum;
		u16 wBandWidth = ptDstNode->m_tVidSndFormat.m_tFormat.m_wBitrate;
		
		if ( tInfo.m_tBaseInfo.m_wScreenIndex != TP_MAX_STREAMNUM )
		{
			wScreenNum = 1;
		}

		TCapNode* ptCaller = pcConf->GetNodeMgr()->GetCaller();
		tRes.m_emRes = m_acDispatchInfo[wIndex].Init(pcConf, tInfo.m_tBaseInfo.m_wEpID, tInfo.m_tBaseInfo.m_emType, 
											ptCaller->m_tVidRcvFormat, tInfo.m_bSamll, wBandWidth, wScreenNum, 
											tInfo.m_tBaseInfo.m_wScreenIndex, TRUE, tInfo.m_tBaseInfo.m_wHandle);

	} while (FALSE);

	MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::EventGetVidReq ConfID:%d, DstEp:%d, ScreenIndex:%d, Type:%d, Small:%d, Handle:%d, Ret:%d.\n",
		pcConf->GetInsID(), tInfo.m_tBaseInfo.m_wEpID, tInfo.m_tBaseInfo.m_wScreenIndex, tInfo.m_tBaseInfo.m_emType, 
							tInfo.m_bSamll, tInfo.m_tBaseInfo.m_wHandle, tRes.m_emRes));

	if (em_GetVid_Success == tRes.m_emRes)
	{
		m_acDispatchInfo[wIndex].SetDstAddr(tInfo);
		m_acDispatchInfo[wIndex].UpdateCascadeTran();
		m_acDispatchInfo[wIndex].GetLocalAddr(tRes.m_tInfo);
		m_acDispatchInfo[wIndex].SetAdjustSeat(tInfo.m_tBaseInfo.m_emType);

		if (bIsThreeScrEp && IsNeedNotifyNoVmp(wIndex) )
		{
			tRes.m_emRes = em_GetVid_DownUmNoVmp;
		}

		//本地handle带到上级
		tRes.m_tInfo.m_tBaseInfo.m_wScreenIndex = wIndex;
	}
	
	UmsSendConfCtrl(tOutHandle, ev_GetVid_Res, &tRes, sizeof(tRes));
}

void CGetVidAudEx::EventGetVidRes(CUmsConfInst* pcConf, CTpMsg* const pcMsg)
{
	TUmsHandle tHandle;
	TGetVidInfoRes tRes;
	TP_SAFE_CAST(tHandle, pcMsg->GetBody());
	TP_SAFE_CAST(tRes, pcMsg->GetBody()+sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::EventGetVidRes ConfID:%d, Handle:%d, DstEp:%d, Type:%d, Ret:%d.\n",
							pcConf->GetInsID(), tRes.m_tInfo.m_tBaseInfo.m_wHandle, tRes.m_tInfo.m_tBaseInfo.m_wEpID,
							tRes.m_tInfo.m_tBaseInfo.m_emType, tRes.m_emRes));

	u16 wIndex = tRes.m_tInfo.m_tBaseInfo.m_wHandle;
	if (wIndex < TP_UMS_MAX_CALLNUM)
	{
		if (!m_acDispatchInfo[wIndex].Working())
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::EventGetVidRes Not in working.\n"));
			return;
		}

		if (em_GetVid_Success != tRes.m_emRes)
		{
			EmGetVidRet emRet = EmGetVidRet_Success;
			if ( tRes.m_emRes == em_GetVide_No_BasResource )
			{
				emRet = EmGetVidRet_BasDisCnnt;
			}
			else if ( tRes.m_emRes == em_GetVid_No_BandWidth )
			{
				emRet = EmGetVidRet_BWFull;
			}
			else if ( tRes.m_emRes == em_GitVid_No_Resource )
			{
				emRet = EmGetVidRet_NoVid;
			}
			else if ( tRes.m_emRes == em_GetVid_DownUmNoVmp )
			{// 并不是调度失败，只是提示上级，下级没有用到vmp资源
				emRet = EmGetVidRet_NoVmp;
			}
			else if ( tRes.m_emRes == em_GetVid_DownUmVmpDisconnect )
			{
				emRet = EmGetVidRet_VmpDisConnect;
			}
			CUmsConfInst::GetVidFailedCB(m_acDispatchInfo[wIndex].ConfInst(), wIndex, m_acDispatchInfo[wIndex].GetVidType(), emRet);
			
			if ( tRes.m_emRes != em_GetVid_DownUmNoVmp )
			{
				m_acDispatchInfo[wIndex].Decrement();
			}
			else
			{
				m_acDispatchInfo[wIndex].SetRmtHandle(tRes.m_tInfo.m_tBaseInfo.m_wScreenIndex);
				m_acDispatchInfo[wIndex].SetDstAddr(tRes.m_tInfo);
				m_acDispatchInfo[wIndex].UpdateCascadeTran();
				// 下级码流成功上调后，主动请求一次
				m_acDispatchInfo[wIndex].AskKeyFrame(TRUE);
			}
		}
		else
		{
			m_acDispatchInfo[wIndex].SetRmtHandle(tRes.m_tInfo.m_tBaseInfo.m_wScreenIndex);
			m_acDispatchInfo[wIndex].SetDstAddr(tRes.m_tInfo);
			m_acDispatchInfo[wIndex].UpdateCascadeTran();
			// 下级码流成功上调后，主动请求一次
			m_acDispatchInfo[wIndex].AskKeyFrame(TRUE);
		}
	}
}

void CGetVidAudEx::EventStopGetVidReq(CUmsConfInst* pcConf, CTpMsg* const pcMsg)
{
	TUmsHandle tHandle;
	TGetVidBaseInfo tInfo;
	TP_SAFE_CAST(tHandle, pcMsg->GetBody());
	TP_SAFE_CAST(tInfo, pcMsg->GetBody()+sizeof(tHandle));

	MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::EventStopGetVidReq ConfID:%d, DstEp:%d, Screen:%d, Type:%d, Handle:%d.\n",
							pcConf->GetInsID(), tInfo.m_wEpID, tInfo.m_wScreenIndex, tInfo.m_emType, tInfo.m_wHandle));

	u16 wIndex = FindByRmtHandle(tInfo.m_wHandle);
	if (TP_UMS_MAX_CALLNUM == wIndex)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::EventStopGetVidReq Not find the info.\n"));
		return ;
	}

	if ( !m_acDispatchInfo[wIndex].Working() )
	{
		return ;
	}

	if (TP_MAX_STREAMNUM != tInfo.m_wScreenIndex)
	{
		m_acDispatchInfo[wIndex].ReleaseScreen(tInfo.m_wScreenIndex);
	}
	else
	{
		m_acDispatchInfo[wIndex].Decrement();
	}
}
/*
EmGetVidRes CGetVidAudEx::Assign(CUmsConfInst* pcConf, u16 wDstEp, EmGetVidType emType, 
								TCallVidFormat tRcvFormat, BOOL32 bSmall, TGetVidAddr& tAddr, u16& wGetVidHandle)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Assign Invalid conf.\n"));
		return em_GetVid_Invalid_Param;
	}

	if (em_GetVid_Invalid == emType)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Assign Invalid getvid type.\n"));
		return em_GetVid_Invalid_Param;
	}

	MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::Assign ConfID:%d, DstEp:%d, GetVidType:%d\n",
							pcConf->GetInsID(), wDstEp, emType));

	u16 wIndex = Find(pcConf, wDstEp, TP_MAX_STREAMNUM, emType, tRcvFormat);
	if (TP_UMS_MAX_CALLNUM != wIndex)
	{
		MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::Assign Already assign.\n"));
		tAddr = m_acDispatchInfo[wIndex].GetSrcAddr();
		m_acDispatchInfo[wIndex].Increment();
		wGetVidHandle = wIndex;

		m_acDispatchInfo->SetAdjustSeat(emType);

		return em_GetVid_Success;
	}
	
	wIndex = FindIdle();
	if (TP_UMS_MAX_CALLNUM == wIndex)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Assign No idle resource.\n"));
		return em_GitVid_No_Resource;
	}
	CDispatchInfo* pcInfo = &(m_acDispatchInfo[wIndex]);

	TCallNode* ptDstNode = pcConf->GetNodeMgr()->GetNode(wDstEp);
	TCapNode* ptFatherNode = pcConf->GetNodeMgr()->GetForeFatherNode(ptDstNode);
	if (NULL == ptDstNode || NULL == ptFatherNode || !ptDstNode->IsChanOn() || !ptDstNode->IsMtEp())
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Assign Not invalid ep.\n"));
		return em_GetVid_Invalid_Param;
	}
	
	if (!ptDstNode->IsVidSndValid())
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Assign vid-snd invalid.\n"));
		return em_GetVid_Invalid_Param;
	}

	u16 wBandWidth = 0;
	u16 wScreenNum = ptDstNode->m_wVidSndNum;

	if (ptDstNode != ptFatherNode)
	{
		wBandWidth = ptFatherNode->m_tVidSndFormat.m_tFormat.m_wBitrate;

		if (!pcConf->GetBandWidth().IsDownBw(wBandWidth*wScreenNum))
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Assign Over band width.\n"));
			return em_GetVid_No_BandWidth;
		}
	}

	EmGetVidRes emRes = pcInfo->Init(pcConf, wDstEp, emType, tRcvFormat, bSmall, wBandWidth, wScreenNum);
 	if (em_GetVid_Success != emRes)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Assign Init resource failed.\n"));
		return emRes;
	}

	pcInfo->SetAdjustSeat(emType);

	tAddr = pcInfo->GetSrcAddr();
	if (ptDstNode != ptFatherNode)
	{
		TUmsHandle tOutHandle;
		pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptFatherNode->m_wEpID);
				
		TGetVidInfo tInfo;
		tInfo.m_tBaseInfo.m_wEpID = ptDstNode->m_wLowChildEpID;
		tInfo.m_tBaseInfo.m_emType = emType; 
		tInfo.m_tBaseInfo.m_wHandle = wIndex;
		tInfo.m_bSamll = bSmall;
		pcInfo->GetLocalAddr(tInfo);
 		UmsSendConfCtrl(tOutHandle, ev_GetVid_Req, &tInfo, sizeof(tInfo));
	}

	wGetVidHandle = wIndex;
	return em_GetVid_Success;
}
*/
EmGetVidRes CGetVidAudEx::AssignByScreen(CUmsConfInst* pcConf, u16 wDstEp, u16 wScreenIndex, EmGetVidType emType, 
										TCallVidFormat tRcvFormat, BOOL32 bSmall, TGetVidAddr& tAddr, u16& wGetVidHandle)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen Invalid conf.\n"));
		return em_GetVid_Invalid_Param;
	}
	
	if (em_GetVid_Invalid == emType)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen Invalid getvid type.\n"));
		return em_GetVid_Invalid_Param;
	}
	
	MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen ConfID:%d, DstEp:%d, ScreenIndex:%d, GetVidType:%d\n",
							pcConf->GetInsID(), wDstEp, wScreenIndex, emType));
	
	u16 wIndex = Find(pcConf, wDstEp, wScreenIndex, emType, tRcvFormat);
	if (TP_UMS_MAX_CALLNUM != wIndex)
	{
		MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen Already assign.\n"));
		tAddr = m_acDispatchInfo[wIndex].GetSrcAddr();
		m_acDispatchInfo[wIndex].Increment();
		wGetVidHandle = wIndex;

		m_acDispatchInfo[wIndex].SetAdjustSeat(emType);
		
		return em_GetVid_Success;
	}
	
	wIndex = FindIdle();
	if (TP_UMS_MAX_CALLNUM == wIndex)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen No idle resource.\n"));
		return em_GitVid_No_Resource;
	}
	CDispatchInfo* pcInfo = &(m_acDispatchInfo[wIndex]);
	
	TCallNode* ptDstNode = pcConf->GetNodeMgr()->GetNode(wDstEp);
	TCapNode* ptFatherNode = pcConf->GetNodeMgr()->GetForeFatherNode(ptDstNode);
	if (NULL == ptDstNode || NULL == ptFatherNode || !ptDstNode->IsChanOn() || !ptDstNode->IsMtEp())
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen Not invalid ep.\n"));
		return em_GetVid_Invalid_Param;
	}
	

	if (em_GetVid_OnlyAud == emType)
	{
        if (!ptDstNode->IsAudSndValid())
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen emtype = em_GetVid_OnlyAud  aud-snd invalid.\n"));
            return em_GetVid_Invalid_Param;
		}
	} 
	else 
	{
        if (!ptDstNode->IsVidSndValid())
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen vid-snd invalid.\n"));
		    return em_GetVid_Invalid_Param;
		}
	}
	
	u16 wBandWidth = 0;
	
	if (ptDstNode != ptFatherNode && emType != em_GetVid_OnlyAud)
	{// 非本级且需要调度视频，验证宽带
		wBandWidth = ptFatherNode->m_tVidSndFormat.m_tFormat.m_wBitrate;
		
		if (!pcConf->GetBandWidth().IsDownBw(wBandWidth))
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen Over band width.\n"));
			return em_GetVid_No_BandWidth;
		}
	}
	
	EmGetVidRes emRes = pcInfo->Init(pcConf, wDstEp, emType, tRcvFormat, bSmall, wBandWidth, 1, wScreenIndex);
	if (em_GetVid_Success != emRes)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AssignByScreen Init resource failed.\n"));
		return emRes;
	}

	pcInfo->SetAdjustSeat(emType);
	
	tAddr = pcInfo->GetSrcAddr();
	if (ptDstNode != ptFatherNode)
	{
		TUmsHandle tOutHandle;
		pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptFatherNode->m_wEpID);
		
		TGetVidInfo tInfo;
		tInfo.m_tBaseInfo.m_wEpID = ptDstNode->m_wLowChildEpID;
		tInfo.m_tBaseInfo.m_emType = emType; 
		tInfo.m_tBaseInfo.m_wHandle = wIndex;
		tInfo.m_bSamll = bSmall;
		tInfo.m_tBaseInfo.m_wScreenIndex = wScreenIndex;
		pcInfo->GetLocalAddr(tInfo);
		UmsSendConfCtrl(tOutHandle, ev_GetVid_Req, &tInfo, sizeof(tInfo));
	}
	
	wGetVidHandle = wIndex;
	return em_GetVid_Success;
}

void CGetVidAudEx::Release(CUmsConfInst* pcConf, u16 wGetVidIndex, EmGetVidType emType /* = em_GetVid_Invalid */, BOOL32 bStopConf /* = FALSE */)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Release Invalid conf.\n"));
		return ;
	}

	if (TP_UMS_MAX_CALLNUM > wGetVidIndex)
	{
		if ( !m_acDispatchInfo[wGetVidIndex].Working() )
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Release AllReady!\n"));
			return ;
		}

		u16 wDstEp = m_acDispatchInfo[wGetVidIndex].GetDstEp();
		EmGetVidType emType = m_acDispatchInfo[wGetVidIndex].GetVidType();

		if (bStopConf)
		{
			m_acDispatchInfo[wGetVidIndex].ClearCount();
		}
		else
		{
			m_acDispatchInfo[wGetVidIndex].Decrement();
		}
		if ( m_acDispatchInfo[wGetVidIndex].VidCount() > 0 )
		{
			m_acDispatchInfo[wGetVidIndex].SetAdjustSeat(emType);
			return;
		}

		TCallNode* ptDstNode = pcConf->GetNodeMgr()->GetNode(wDstEp);
		TCapNode* ptFatherNode = pcConf->GetNodeMgr()->GetForeFatherNode(ptDstNode);
		if (NULL != ptDstNode && NULL != ptFatherNode && ptDstNode != ptFatherNode)
		{
			TUmsHandle tOutHandle;
			pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptFatherNode->m_wEpID);
			
			TGetVidBaseInfo tInfo;
			tInfo.m_wEpID = wDstEp;
			tInfo.m_emType = emType;
			tInfo.m_wHandle = wGetVidIndex;
 			UmsSendConfCtrl(tOutHandle, ev_GetVid_Stop_Req, &tInfo, sizeof(tInfo));
		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Release Invalid index:%d.\n", wGetVidIndex));
	}
}


u16  CGetVidAudEx::GetScreenIndex(u16 wGetVidIndex)
{

    if (TP_UMS_MAX_CALLNUM > wGetVidIndex && m_acDispatchInfo[wGetVidIndex].Working())
	{
		return m_acDispatchInfo[wGetVidIndex].ScreenIndex();
	}

	MdlError(Ums_Mdl_Call, ("CGetVidAudEx::GetScreenIndex Invalid index:%d.\n", wGetVidIndex));
	return TP_INVALID_INDEX;
}


u16 CGetVidAudEx::GetDstEpByIndex(u16 wGetVidIndex)
{
    if (TP_UMS_MAX_CALLNUM > wGetVidIndex && m_acDispatchInfo[wGetVidIndex].Working())
	{
		return m_acDispatchInfo[wGetVidIndex].GetDstEp();
	}

	return TP_INVALID_INDEX;
}


/*
void CGetVidAudEx::ReleaseByScreen(CUmsConfInst* pcConf, u16 wGetVidIndex, u16 wScreenIndex)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::ReleaseByScreen Invalid conf.\n"));
		return ;
	}
	
	if (TP_UMS_MAX_CALLNUM > wGetVidIndex)
	{
		if ( !m_acDispatchInfo[wGetVidIndex].Working() )
		{
			MdlError(Ums_Mdl_Call, ("CGetVidAudEx::ReleaseByScreen AllReady!\n"));
			return ;
		}

		TCallNode* ptDstNode = pcConf->GetNodeMgr()->GetNode(m_acDispatchInfo[wGetVidIndex].GetDstEp());
		TCapNode* ptFatherNode = pcConf->GetNodeMgr()->GetForeFatherNode(ptDstNode);
		if (NULL != ptDstNode && NULL != ptFatherNode && ptDstNode != ptFatherNode)
		{
			TUmsHandle tOutHandle;
			pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptFatherNode->m_wEpID);
			
			TGetVidBaseInfo tInfo;
			tInfo.m_wEpID = m_acDispatchInfo[wGetVidIndex].GetDstEp();
			tInfo.m_emType = m_acDispatchInfo[wGetVidIndex].GetVidType();
			tInfo.m_wHandle = wGetVidIndex;
			tInfo.m_wScreenIndex = wScreenIndex;
			UmsSendConfCtrl(tOutHandle, ev_GetVid_Stop_Req, &tInfo, sizeof(tInfo));
		}

		m_acDispatchInfo[wGetVidIndex].ReleaseScreen(wScreenIndex);
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::ReleaseByScreen Invalid index:%d.\n", wGetVidIndex));
	}
}
*/
void CGetVidAudEx::UpdateSpeakerIndex(CUmsConfInst* pcConf, u16 wEpID, u16 wScreenIndx)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::UpdateSpeakerIndex Invalid conf.\n"));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::UpdateSpeakerIndex Conf:%d, Ep:%d, ScreenIndex:%d.\n", pcConf->GetInsID(), wEpID, wScreenIndx));

	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; ++wIndex)
	{
		if ( !m_acDispatchInfo[wIndex].GetAdjustSeat() )
		{
			continue;
		}

		if (m_acDispatchInfo[wIndex].Working() && m_acDispatchInfo[wIndex].ConfInst()->GetInsID() == pcConf->GetInsID() &&
			m_acDispatchInfo[wIndex].GetDstEp() == wEpID)
		{
			m_acDispatchInfo[wIndex].SetScreenIndx(wScreenIndx);
			m_acDispatchInfo[wIndex].UpdateSpeakerIndex();
		}
	}
}

void CGetVidAudEx::AskKeyFrame(u16 wGetVidIndx, BOOL32 bbySys)
{
	if (wGetVidIndx >= TP_UMS_MAX_CALLNUM)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AskKeyFrame Invalid index.\n"));
		return ;
	}

	if (!m_acDispatchInfo[wGetVidIndx].Working())
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AskKeyFrame Not in working.\n"));
		return ;
	}

	m_acDispatchInfo[wGetVidIndx].AskKeyFrame(bbySys);
}

u16 CGetVidAudEx::Find(CUmsConfInst* pcConf, u16 wDstEp, u16 wScreenIndex, EmGetVidType emType, TCallVidFormat tRcvFormat)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Find Invalid conf.\n"));
		return NULL;
	}

	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; ++wIndex)
	{
		if (m_acDispatchInfo[wIndex].Working() && pcConf->GetInsID() == m_acDispatchInfo[wIndex].ConfInst()->GetInsID() &&
			m_acDispatchInfo[wIndex].GetDstEp() == wDstEp &&
			m_acDispatchInfo[wIndex].IsEqualVidType(emType)
			&& m_acDispatchInfo[wIndex].ScreenIndex() == wScreenIndex )
		{

			if ( em_GetVid_View == emType && NULL == m_acDispatchInfo[wIndex].VmpService()
				&& 0 < CEqpService::Instance().GetIdleNum(em_mpu2tp_service) )
			{//屏选看 但此位置无合成器 且 当前有合成器  不能使用位置
				continue;
			}

			if (em_GetVid_View == emType || em_GetVid_ViewEp == emType)
			{
				if (!CTpTypeAdpt::IsVidTransNeedBas(m_acDispatchInfo[wIndex].VidFormat().m_tFormat, tRcvFormat.m_tFormat))
				{
					return wIndex;
				}
				else
				{
                    continue;
				}
			}
	
			return wIndex;
		}
	}

	return TP_UMS_MAX_CALLNUM;
}


CDispatchInfo* CGetVidAudEx::Find( CUmsConfInst* pcConf, const CBaseService* pcService )
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::Find Invalid conf.\n"));
		return NULL;
	}
	
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; ++wIndex)
	{
		if ( m_acDispatchInfo[wIndex].Working() && 
			pcConf->GetInsID() == m_acDispatchInfo[wIndex].ConfInst()->GetInsID() &&
			pcService == m_acDispatchInfo[wIndex].VmpService())
		{
			return &m_acDispatchInfo[wIndex];
		}
	}
	
	return NULL;
}



u16 CGetVidAudEx::FindIdle()
{
	u16 wForNum = 0;
	u16 wIndex = m_wLastIndx;
	do 
	{
		if ( wForNum >= 2 )
		{
			break;
		}
		//依次往下找
		if ( wIndex >= TP_UMS_MAX_CALLNUM )
		{
			wForNum ++;
			wIndex = 0;
		}

		if (!m_acDispatchInfo[wIndex].Working())
		{
			m_wLastIndx = wIndex + 1;
			return wIndex;
		}

		wIndex ++;

	} while (TRUE);
	
	return TP_UMS_MAX_CALLNUM;
}

u16 CGetVidAudEx::FindByRmtHandle(u16 wHandle)
{
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; ++wIndex)
	{
		if (m_acDispatchInfo[wIndex].GetRmtHandle() == wHandle)
		{
			return wIndex;
		}
	}

	return TP_UMS_MAX_CALLNUM;
}

void CGetVidAudEx::Show( u16 wConfID )
{
	msgprintnotime("=========GetVidAudEx Info ConfID:%d=======\n", wConfID);

	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; ++wIndex)
	{
		m_acDispatchInfo[wIndex].Show(wConfID);
	}

	return ;
}

EmGetVidRes CGetVidAudEx::UpdateAddr( CUmsConfInst* pcConf, EmGetVidType emType, u16& wGetVidIndex, TGetVidAddr& tAddr, u16 wScreenIndex, TCallVidFormat& tRcvFormat)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::UpdateAddr Invalid conf.\n"));
		return em_GetVid_Invalid_Param;
	}
	
	if (TP_UMS_MAX_CALLNUM <= wGetVidIndex)
	{
		return em_GetVid_Invalid_Param;
	}

	MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::UpdateAddr. vidIndx:%d, ScreenIndx:%d\n", wGetVidIndex, wScreenIndex));

	if ( m_acDispatchInfo[wGetVidIndex].GetAdjustSeat() )
	{
		tAddr = m_acDispatchInfo[wGetVidIndex].GetSrcAddr();
		return em_GetVid_Success;
	}

	if ( m_acDispatchInfo[wGetVidIndex].ScreenIndex() == wScreenIndex )
	{
		return em_GetVid_Success;
	}

	u16 wDstEp = m_acDispatchInfo[wGetVidIndex].GetDstEp();

	//释放老的
	Release(pcConf, wGetVidIndex, emType);

	EmGetVidRes emRet = AssignByScreen(pcConf, wDstEp, 
									wScreenIndex, emType, tRcvFormat, TRUE, tAddr, wGetVidIndex);
	if ( emRet != em_GetVid_Success )
	{
		return emRet;
	}

	return em_GetVid_Success;
}


BOOL32 CGetVidAudEx::IsNeedNotifyNoVmp( u16 wGetVidIndx )
{
	if (TP_UMS_MAX_CALLNUM <= wGetVidIndx)
	{
		MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::IsNeedNotifyNoVmp wGetVidIndx Error wGetVidIndx:%d \n", wGetVidIndx));
		return FALSE;
	}


    if (m_acDispatchInfo[wGetVidIndx].GetVidType()    == em_GetVid_View 
		&& m_acDispatchInfo[wGetVidIndx].VmpService() == NULL)
	{
        return  TRUE ;
	} 
	// m_emType = em_GetVid_ViewEp 意为 屏看对应屏 ，不需用到VMP, 不需要提示
	// 非选看 相关的m_emType 不需要提示
	return FALSE;

}


void CGetVidAudEx::AskKeyFrameByRmtHandle( u16 wGetVidIndx, BOOL32 bbySys )
{
	if (wGetVidIndx >= TP_UMS_MAX_CALLNUM)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AskKeyFrameByRmtHandle Invalid index.\n"));
		return ;
	}

	u16 wIndex = FindByRmtHandle(wGetVidIndx);
	if (wIndex >= TP_UMS_MAX_CALLNUM)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::AskKeyFrameByRmtHandle Invalid index.\n"));
		return ;
	}

	AskKeyFrame(wIndex, bbySys);

	return ;
}

void CGetVidAudEx::StopConf( u16 wConfID )
{//结会时候统一释放
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; ++wIndex)
	{
		if ( !m_acDispatchInfo[wIndex].Working() || wConfID != m_acDispatchInfo[wIndex].ConfInst()->GetInsID() )
		{
			continue;
		}

		Release(m_acDispatchInfo[wIndex].ConfInst(), wIndex);
	}
}

void CGetVidAudEx::ReleaseRepeatdGetVidAudForDown(CUmsConfInst* pcConf, EmGetVidType emType, u16 wDstEp, u16 wScreenIndex)
{
	if (NULL == pcConf)
	{
		MdlError(Ums_Mdl_Call, ("CGetVidAudEx::ReleaseRepeatDown Invalid conf.\n"));
		return ;
	}

	if (em_GetVid_View == emType || em_GetVid_ViewEp == emType)
	{
		//此类型会调多次
        return;
	}

	
	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CALLNUM; ++wIndex)
	{
		if (m_acDispatchInfo[wIndex].Working() &&
			pcConf->GetInsID() == m_acDispatchInfo[wIndex].ConfInst()->GetInsID() &&
			m_acDispatchInfo[wIndex].GetDstEp() == wDstEp &&
			m_acDispatchInfo[wIndex].IsEqualVidType(emType)
			&& m_acDispatchInfo[wIndex].ScreenIndex() == wScreenIndex )
		{ 

			MdlHint(Ums_Mdl_Call, ("CGetVidAudEx::ReleaseRepeatdGetVidAudForDown confid:%d, index:%d, dstep:%d, type:%d, screenIndex:%d.\n", 
				    pcConf->GetInsID(), wIndex, wDstEp, emType, wScreenIndex));
            m_acDispatchInfo[wIndex].ReleaseScreen(wScreenIndex);
		    break;
		}
	}
	
	return;

}