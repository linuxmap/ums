#include "procnodeds.h"
#include "umsconfinst.h"
#include "dualmgr.h"
#include "eventoutumsmediatrans.h"
#include "netbuf.h"
#include "umsnetportmgr.h"
#include "umsbas.h"
#include "umsvmp.h"
#include "umseapu.h"


//双流到节点的交换
u16 CDsStrategyToNodeForDual::GetDsToNode(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs)
{
	CDualMgr* pcDualMgr = pInst->GetDualMgr();
	if (!pcDualMgr->IsStart())
	{
		return 0;
	}

	CCallNodeMgr* pcNodeMgr = pInst->GetNodeMgr();
	TCapNode* ptDstNode = pcNodeMgr->GetCapsetNode(m_wDstNodeID);
	if (NULL == ptDstNode)
	{
		return 0;
	}

	TCapNode* ptDualFarther = pcNodeMgr->GetForeFatherNode(pcDualMgr->GetDualID());
	if (NULL == ptDualFarther)
	{
		return 0;
	}
	
	//双流源节点或者双流源节点在次UMS内，不转发
	if (ptDualFarther->m_wEpID == ptDstNode->m_wEpID)
	{
		return 0;
	}

	u16 wDsNum = 0;

	BOOL32 bDualBas = pInst->GetBas()->IsDualNeedBas(ptDstNode->m_tDualVidRcvFormat.m_tFormat);
	u32 dwEqpNode = ptDstNode->m_tMediaEqp.m_dwEqpNode;
	u32	dwEqpIP = ptDstNode->m_tMediaEqp.m_dwEqpIp;
	
	TTPMediaTransAddr tAddr;//适配地址

	TUmsDsData* ptDsData;
	if (ptDstNode->m_tRmtChan.m_tDualVidDec.IsOpen())
	{
		if ( bDualBas )
		{//双流适配
			pInst->GetBas()->GetOutDualVidAddr(tAddr, ptDstNode->m_tDualVidRcvFormat.m_tFormat);
		}
		else
		{
			tAddr.m_tRtpAddr = pcDualMgr->m_tVidRcvAddr.m_tRtpAddr;
			tAddr.m_tRtpAddr.SetIP(dwEqpIP);
			tAddr.m_tBackRtcpAddr = pcDualMgr->m_tVidNetBuf.m_tRcvRtcpAddr;
		}

		ptDsData = atDsData+wDsNum;
		ptDsData->m_tRcvFromAddr = tAddr.m_tRtpAddr;
		ptDsData->m_tSndToAddr = ptDstNode->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr;	
		ptDsData->m_dwEqpNode = dwEqpNode;			//节点所在转发板
		ptDsData->m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		++wDsNum;
		
		ptDsData = atDsData+wDsNum;
		ptDsData->m_tRcvFromAddr = ptDstNode->m_ptDualAddr->m_tVid.m_tRtcpForSnd;
		ptDsData->m_tSndToAddr = tAddr.m_tBackRtcpAddr;
		if( !bDualBas )
		{
			ptDsData->m_tMapedAddr = ptDstNode->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr;
		}
		ptDsData->m_dwEqpNode = dwEqpNode;			//节点所在转发板
		ptDsData->m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}
	
	if (ptDstNode->m_tRmtChan.m_tDualAudDec.IsOpen())
	{
		if ( pInst->IsAudNeedBas() && pInst->GetBas()->IsDualNeedAudBas(ptDstNode->m_tDualAudRcvFormat.m_tFormat.m_emFormat) )
		{
			TTPDsFrom tAudBasAddr;
			pInst->GetBas()->GetDualAudBasOutAddr( ptDstNode->m_tDualAudRcvFormat.m_tFormat.m_emFormat, tAudBasAddr);
			tAddr.m_tRtpAddr = tAudBasAddr.m_tRtpAddr;
			tAddr.m_tBackRtcpAddr = tAudBasAddr.m_tBackRtcpAddr;
			dwEqpNode = tAudBasAddr.m_dwEqpNode;
		}
		else
		{
			tAddr.m_tRtpAddr = pcDualMgr->m_tAudRcvAddr.m_tRtpAddr;
			tAddr.m_tBackRtcpAddr = pcDualMgr->m_tAudRcvAddr.m_tBackRtcpAddr;
			tAddr.m_tRtpAddr.SetIP(dwEqpIP);
		}

		ptDsData = atDsData+wDsNum;
		ptDsData->m_tRcvFromAddr = tAddr.m_tRtpAddr;
		ptDsData->m_tSndToAddr = ptDstNode->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtpAddr;	
		ptDsData->m_dwEqpNode = dwEqpNode;			//节点所在转发板
		ptDsData->m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
		
		ptDsData = atDsData+wDsNum;
		ptDsData->m_tRcvFromAddr = ptDstNode->m_ptDualAddr->m_tAud.m_tRtcpForSnd;
		ptDsData->m_tSndToAddr = tAddr.m_tBackRtcpAddr;
		ptDsData->m_dwEqpNode = ptDstNode->m_tMediaEqp.m_dwEqpNode;	//节点所在转发板
		ptDsData->m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}
	return wDsNum;
}
void CDSStrategyToSpeaker::GetVidAddr(CUmsConfInst* pInst, TTPTransAddr atChairRtp[TP_MAX_STREAMNUM], TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM], u32 adwRtpEqpNode[TP_MAX_STREAMNUM], BOOL32 bNeedBas)
{
	u16 wIndex = 0;
	
	if ( pInst->GetBas()->IsChairInBas() && bNeedBas)
	{//主席在适配中 pInst->IsPriNeedBas() 不能表明主席在适配中
		TTPMediaTransAddr tMediaAddr;
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			pInst->GetBas()->GetOutChnChairVidAddr(tMediaAddr, wIndex);
			atChairRtp[wIndex] = tMediaAddr.m_tRtpAddr;
			atChairRtcp[wIndex] = tMediaAddr.m_tBackRtcpAddr;
			adwRtpEqpNode[wIndex] = pInst->GetConfEqpDs().m_dwEqpNode;
		}	
	}
	else
	{
		if (m_bIsSupuer)
		{			
			for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				if (m_ptChair->m_aptChanAddr[wIndex] != NULL)
				{
					atChairRtp[wIndex] = m_ptChair->m_aptChanAddr[wIndex]->m_tVid.m_tRtpAddr;
				}
				atChairRtcp[wIndex] = m_ptChair->m_tRmtChan.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
			}
		}
		else
		{
			if (m_ptChair->m_ptCasCadeChairAddr != NULL)
			{
				for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
				{
					atChairRtp[wIndex] = m_ptChair->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtpAddr;
					atChairRtcp[wIndex] = m_ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				}
			}	
		}
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			adwRtpEqpNode[wIndex] = m_ptChair->m_tMediaEqp.m_dwEqpNode;
		}
	}
}

void CDSStrategyToSpeaker::GetAudAddr( CUmsConfInst* pInst, 
									  TTPTransAddr atChairRtp[TP_MAX_STREAMNUM], TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM], 
									  TTPTransAddr& tChairMixRtp, TTPTransAddr& tChairMixRtcp, 
									  u32 adwRtpEqpNode[TP_MAX_STREAMNUM], u32& dwMixAudEqpNode, BOOL32 bNeedBas /*= TRUE*/ )
{
	u16 wIndex = 0;
	if (m_bIsSupuer)
	{		
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (m_ptChair->m_aptChanAddr[wIndex] != NULL)
			{
				atChairRtp[wIndex] = m_ptChair->m_aptChanAddr[wIndex]->m_tAud.m_tRtpAddr;
			}
			atChairRtcp[wIndex] = m_ptChair->m_tRmtChan.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
		}
	}
	else
	{
		if (m_ptChair->m_ptCasCadeChairAddr != NULL)
		{
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				atChairRtp[wIndex] = m_ptChair->m_ptCasCadeChairAddr->m_atAud[wIndex].m_tRtpAddr;
				atChairRtcp[wIndex] = m_ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].m_tChanAddr.m_tBackRtcpAddr;
			}
		}
	}

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		adwRtpEqpNode[wIndex] = m_ptChair->m_tMediaEqp.m_dwEqpNode;
	}


	//混音 和适配无关
	if ( m_ptChair->IsThreeAudSnd() )
	{
		if ( m_bIsSupuer )
		{
			if( m_ptChair->m_ptMixAddr != NULL )
			{
				tChairMixRtp = m_ptChair->m_ptMixAddr->m_tRtpAddr;
				tChairMixRtcp = m_ptChair->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
			}
		}
		else
		{
			if (m_ptChair->m_ptCasCadeChairAddr != NULL)
			{//下级接收主席混音
				tChairMixRtp = m_ptChair->m_ptCasCadeChairAddr->m_tMixAud.m_tRtpAddr;
				tChairMixRtcp = m_ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr.m_tBackRtcpAddr;
			}
		}
		dwMixAudEqpNode = m_ptChair->m_tMediaEqp.m_dwEqpNode;
	}
	
	return ;
}

//主席 到适配板的交换
u16 CDsStrategyChairToBas::GetDsToNode( CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs )
{
	if (!m_ptChair->IsVidSndValid())
	{
		MdlHint(Ums_Mdl_Call, ("CDsStrategyChairToBas. ConfID:%d, speaker:%d, chair:%d, ChairVidSndNum:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->chairID(), m_ptChair->IsVidSndValid()));
		return 0;
	}

	TCallNode* ptSpeaker = pInst->GetNodeMgr()->GetNode(pInst->curSpeakerID());	
	if ( NULL == ptSpeaker || !ptSpeaker->IsChanOn() )
	{
		MdlHint(Ums_Mdl_Call, ("CDsStrategyChairToBas::GetDsToNode. ptSpeaker is NULL! confID:%d, speaker:%d, chair:%d\n", 
												pInst->GetInsID(), pInst->curSpeakerID(), pInst->chairID()));
		return 0;
	}
	
	u16 wDsNum = 0;
	s32 symbolflag = 1; 
	
	TTPTransAddr atChairRtp[TP_MAX_STREAMNUM];
	TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM];
	u32 adwRtpEqpNode[TP_MAX_STREAMNUM];
	u32 dwMixAudEqpNode;
	
	TTPTransAddr atChairAudRtp[TP_MAX_STREAMNUM];
	TTPTransAddr atChairAudRtcp[TP_MAX_STREAMNUM];
	TTPTransAddr tChairMixRtp, tChairMixRtcp;

	GetVidAddr(pInst, atChairRtp, atChairRtcp, adwRtpEqpNode, FALSE);//取主席 码流 进前适配通道
	GetAudAddr(pInst, atChairAudRtp, atChairAudRtcp, tChairMixRtp, tChairMixRtcp, adwRtpEqpNode, dwMixAudEqpNode, FALSE);

	TTPMediaTransAddr tBasAddr;

	u16 wIndex = 1;
	u16 wCurIndex = 0;

	if ( pInst->GetBas()->IsChairInBas() )
	{
		for (wIndex = 1; wIndex <= pInst->GetChairCap().m_wChairVidSndCap; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
			
			//视频
			pInst->GetBas()->GetInChnChairVidAddr(tBasAddr, wCurIndex);
			
			atDsData[wDsNum].m_tRcvFromAddr = atChairRtp[wCurIndex];;
			atDsData[wDsNum].m_tSndToAddr = tBasAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = adwRtpEqpNode[wCurIndex];
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wCurIndex);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = tBasAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = atChairRtcp[wCurIndex];					
			atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
	
		}
	}

	if ( pInst->IsAudNeedBas() )
	{

		TTPDsFrom tAddr;

		if (!pInst->IsChairConf() && pInst->GetUmsDiscuss()->IsDiscussModle())
		{// 下级讨论模式下，不管当前发言人是不是三屏，都对应进
			for (wIndex = 1; wIndex <= pInst->GetChairCap().m_wChairAudSndCap; ++wIndex, symbolflag *= -1)
			{
				wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
				
				pInst->GetBas()->GetChairAudBasInAddr(wCurIndex, tAddr);
				atDsData[wDsNum].m_tRcvFromAddr = atChairAudRtp[wCurIndex];;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = adwRtpEqpNode[wCurIndex];
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetAudio(wCurIndex);
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = atChairAudRtcp[wCurIndex];					
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
		}
		else if(tChairMixRtp.m_wPort != 0 && ptSpeaker->IsSingleAudRcv())
		{//发言人单屏 主席有混音通道 则优先进混音 
			pInst->GetBas()->GetChairAudBasInAddr(MIDSCREENINDEX, tAddr);
			atDsData[wDsNum].m_tRcvFromAddr = tChairMixRtp;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwMixAudEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetEPMixAudio();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tChairMixRtcp;					
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else
		{//否则按次序进
			for (wIndex = 1; wIndex <= pInst->GetChairCap().m_wChairAudSndCap; ++wIndex, symbolflag *= -1)
			{
				wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

				pInst->GetBas()->GetChairAudBasInAddr(wCurIndex, tAddr);
				atDsData[wDsNum].m_tRcvFromAddr = atChairAudRtp[wCurIndex];;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = adwRtpEqpNode[wCurIndex];
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetAudio(wCurIndex);
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = atChairAudRtcp[wCurIndex];					
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;

			}
		}
	}

	return wDsNum;
}
