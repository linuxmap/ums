#include "umsnetportmgr.h"
#include "umsconfinst.h"
#include "callnodemgr.h"
#include "dualmgr.h"
#include "eventoutumsmediatrans.h"
#include "netbuf.h"
#include "umsbas.h"
#include "umsvmp.h"
#include "umseapu.h"
#include "procnodeds.h"
#include "umsdiscussnew.h"
#include "pollmgr.h"
#include "umsrollcall.h"
#include "umsgetconfvidaud.h"

/*
ev_media_ds_iframe_bySrc
     ���Ŀ�꣺�������ⷢ�Խ��ն˿ڡ�һ���������ⷢ�Խ��ն˿�
	 ��    �������ⷢ�Խڵ��ͬʱ�յ����Ϸ����˵��������ڼ�⵽�·����˵Ĺؼ�֡��ͬʱ���л����ߵ�����    

ev_media_ds_iframe_TwoRcvPort
     ���Ŀ�꣺��ѯ�����Խ��ն˿�
	 ��    �����¡����������ն˿�ͬʱ�������������½��ն˿ڼ�⵽�ؼ�֡��ͬʱ���л����ߵ�����

ev_media_ds_iframe_SndBySrc�� 
     ��������������ⷢ�Զ˿ڵ����ݵ�Դ�����·����˹���ʱ������Ŀ��
	         ����Ҫ���ev_media_ds_iframe_bySrcʹ��
     ���Ŀ�꣺1. ���ⷢ���˶˿ڣ� ������ϯ
	                ��ϯ�淢���ˣ��л��·����ˣ�������ϯ����������Ҫ���·����˼�⵽�ؼ�֡����ת��

	           1. ���ⷢ���˶˿ڣ� �����Ϸ��Ի᳡
			         ����ϯ�����ˣ��л��·����ˣ������Ϸ����˵���������Ҫ���·����˼�⵽�ؼ�֡����ת��
*/



CNetPortMgr::CNetPortMgr()
{

}

CNetPortMgr::~CNetPortMgr()
{

}

BOOL32 CNetPortMgr::CreateMediaTrans(CUmsConfInst* pInst, TUmsDsData* ptDs, u16 wDsNum)
{
	u16 wConfID = pInst->GetInsID();
	u32 dwNode = 0;

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_create);
	for (u16 wIndex = 0; wIndex < wDsNum; ++wIndex)
	{
		if (0 == ptDs[wIndex].m_tRcvFromAddr.m_dwIP ||
			0 == ptDs[wIndex].m_tRcvFromAddr.m_wPort ||
			0 == ptDs[wIndex].m_tSndToAddr.m_dwIP ||
			0 == ptDs[wIndex].m_tSndToAddr.m_wPort)
		{
			MdlError(Ums_Mdl_Media, ("CreateMediaTrans RcvAddr or SndAddr is 0 !!! Create("ADDRPORT_FORMAT"->"ADDRPORT_FORMAT"), map("ADDRPORT_FORMAT")\n"
				, ADDRNET(ptDs[wIndex].m_tRcvFromAddr), ADDRNET(ptDs[wIndex].m_tSndToAddr), ADDRNET(ptDs[wIndex].m_tMapedAddr)));
			continue;
		}
		else
		{// nodeͨ��rcvfromip��ȡ������ֹ��ת���峡��node��������
			dwNode = pInst->GetNodeFromMediaIp(ptDs[wIndex].m_tRcvFromAddr.m_dwIP);
		}

		if (0 == dwNode)
		{
			MdlError(Ums_Mdl_Media, ("CreateMediaTrans dwNode is 0. Create("ADDRPORT_FORMAT"->"ADDRPORT_FORMAT"), map("ADDRPORT_FORMAT")\n"
			, ADDRNET(ptDs[wIndex].m_tRcvFromAddr), ADDRNET(ptDs[wIndex].m_tSndToAddr), ADDRNET(ptDs[wIndex].m_tMapedAddr)));
			continue;
		}

		// ��������ʱ����ʶ�Ƿ��ն˵Ľ���
		ptDs[wIndex].m_bNeedModifySrc = pInst->IsMtIp(ptDs[wIndex].m_tSndToAddr.m_dwIP);

		tpLowHint(Ums_Mdl_Media, "CreateMediaTrans Create("ADDRPORT_FORMAT"->"ADDRPORT_FORMAT"), map("ADDRPORT_FORMAT") CalcNode:%d, InNode:%d, Modify:%d.\n"
			, ADDRNET(ptDs[wIndex].m_tRcvFromAddr), ADDRNET(ptDs[wIndex].m_tSndToAddr), ADDRNET(ptDs[wIndex].m_tMapedAddr),
			dwNode, ptDs[wIndex].m_dwEqpNode, ptDs[wIndex].m_bNeedModifySrc);

		cMsg.SetBody(&wConfID, sizeof(wConfID));
		cMsg.CatBody(&ptDs[wIndex], sizeof(ptDs[wIndex]));
		cMsg.Post(UMS_MEDIATRANS_APP_INST, dwNode, UMS_CALL_APP_INST(pInst->GetInsID()));
	}
	
	return TRUE;
}

BOOL32 CNetPortMgr::DestroyMediaTrans(CUmsConfInst* pInst, TUmsDsData* ptDs, u16 wDsNum)
{
	u16 wConfID = pInst->GetInsID();
	u32 dwNode = 0;

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_remove);
	for (u16 wIndex = 0; wIndex < wDsNum; ++wIndex)
	{

		if (0 == ptDs[wIndex].m_tRcvFromAddr.m_dwIP ||
			0 == ptDs[wIndex].m_tRcvFromAddr.m_wPort ||
			0 == ptDs[wIndex].m_tSndToAddr.m_dwIP ||
			0 == ptDs[wIndex].m_tSndToAddr.m_wPort)
		{
			MdlError(Ums_Mdl_Media, ("DestroyMediaTrans RcvAddr or SndAddr is 0 !!! rcv("ADDRPORT_FORMAT"), sendto("ADDRPORT_FORMAT")\n"
			, ADDRNET(ptDs[wIndex].m_tRcvFromAddr), ADDRNET(ptDs[wIndex].m_tSndToAddr)));
			continue;
		}
		else
		{// nodeͨ��rcvfromip��ȡ������ֹ��ת���峡��node��������
			dwNode = pInst->GetNodeFromMediaIp(ptDs[wIndex].m_tRcvFromAddr.m_dwIP);
		}
		
		if (0 == dwNode)
		{
			MdlError(Ums_Mdl_Media, ("DestroyMediaTrans dwNode is 0. rcv("ADDRPORT_FORMAT"), sendto("ADDRPORT_FORMAT")\n"
				, ADDRNET(ptDs[wIndex].m_tRcvFromAddr), ADDRNET(ptDs[wIndex].m_tSndToAddr)));
			continue;
		}
		
		tpLowHint(Ums_Mdl_Media, "DestroyMediaTrans rcv("ADDRPORT_FORMAT"), sendto("ADDRPORT_FORMAT") CalcNode:%d, InNode:%d.\n"
			, ADDRNET(ptDs[wIndex].m_tRcvFromAddr), ADDRNET(ptDs[wIndex].m_tSndToAddr), dwNode, ptDs[wIndex].m_dwEqpNode);
		
		cMsg.SetBody(&wConfID, sizeof(wConfID));
		cMsg.CatBody(&ptDs[wIndex], sizeof(ptDs[wIndex]));
		cMsg.Post(UMS_MEDIATRANS_APP_INST, dwNode, UMS_CALL_APP_INST(pInst->GetInsID()));
	}
	return TRUE;
}



/*==============================================================================
������    :  CreateNetBuf
����      :  ����������Ҫ��netbuf
�㷨ʵ��  :  
����˵��  :  
����ֵ˵��:  
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2011-5-17               zhaixiaogang
==============================================================================*/
void CNetPortMgr::CreateNetBuf(CUmsConfInst* pInst)
{	
	MdlHint(Ums_Mdl_Call, ("CreateNetBuf ConfID:%d\n", pInst->GetInsID()));
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		//���⽨������
		MediaCreateNetBuf(pInst, pInst->GetNetBufParam(wIndex));
	}

	MediaCreateNetBuf(pInst, pInst->GetSingleNetBuf());
	return;
}

void CNetPortMgr::DestoryNetBuf(CUmsConfInst* pInst)
{
	MdlHint(Ums_Mdl_Call, ("DestoryNetBuf ConfID:%d\n", pInst->GetInsID()));	
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		MediaDestroyNetBuf(pInst, pInst->GetNetBufParam(wIndex));
	}
	MediaDestroyNetBuf(pInst, pInst->GetSingleNetBuf());
	return;
}


u16 CNetPortMgr::CreateChairToVirChair(CUmsConfInst* pInst, TCapNode* ptChair)
{
	if (ptChair->m_tMediaEqp.m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
	{
		return 0;
	}

	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	for (u16 wIndex = 0; wIndex <= TP_MAX_STREAMNUM; ++wIndex)
	{		
		if (pInst->IsChairConf())
		{			
			if (ptChair->m_aptChanAddr[wIndex] != NULL)
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptChair->m_aptChanAddr[wIndex]->m_tVid.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->m_cChair.m_atVidDec[wIndex];
				atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wIndex);
				wDsNum++;

				atDsData[wDsNum].m_tRcvFromAddr = ptChair->m_aptChanAddr[wIndex]->m_tAud.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->m_cChair.m_atAudDec[wIndex];
				atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetAudio(wIndex);
				wDsNum++;
			}
		}
		else
		{
			if (ptChair->m_ptCasCadeChairAddr != NULL)
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptChair->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->m_cChair.m_atVidDec[wIndex];
				atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wIndex);
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptChair->m_ptCasCadeChairAddr->m_atAud[wIndex].m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->m_cChair.m_atAudDec[wIndex];
				atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetAudio(wIndex);
				wDsNum++;
			}	
		}
	}

	MergerDsList(pInst, pInst->m_cChair.m_tToVirChair, atDsData, wDsNum, "CreateChairToVirChair");
	return wDsNum;
}

u16 CNetPortMgr::CreateVirSpeakerTrans(CUmsConfInst* pInst)
{
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetNetBufParam(wIndex).m_tRcvRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		wDsNum++;
	}

	atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
	atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleNetBuf().m_tRcvRtpAddr;
	atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
	atDsData[wDsNum].m_emSwitchType = emRtpSwap;
	atDsData[wDsNum].SetUnknowVideo();
	wDsNum++;

	MergerDsList(pInst, pInst->GetSpeaker().m_tInnerVirSpeaker, atDsData, wDsNum, "CreateVirSpeakerTrans");

	CreateVirSpeakerToBas(pInst);

	return wDsNum;
}


u16 CNetPortMgr::CreateSpeakerToVirSpeaker(CUmsConfInst* pInst)
{
	TUmsDsData tDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;

	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		if (pInst->IsChairConf())
		{
			wDsNum = GetDiscussObjToVirSpeaker(pInst, tDsData, MAX_CHANNEL_DS_NUM);
		}
		else
		{
			wDsNum = GetDisCussObjToVirSpeakerForDown(pInst, tDsData, MAX_CHANNEL_DS_NUM);
		}
	} 
	else if (pInst->GetRollCallMgr()->IsRollCallModle())
	{
		if (pInst->IsChairConf())
		{
            wDsNum = GetRollCallObjToVirSpeaker(pInst, tDsData, MAX_CHANNEL_DS_NUM);
		}
		else 
		{
            wDsNum = GetRollCallObjToVirSpeakerForDown(pInst, tDsData, MAX_CHANNEL_DS_NUM);
		}
	}
	else
	{
		wDsNum = GetSpeakerToVirSpeaker(TRUE, pInst, tDsData, MAX_CHANNEL_DS_NUM);
	}

	MdlHint(Ums_Mdl_Call, ("CreateSpeakerToVirSpeaker ConfID:%d, speaker:%d, dsNum:%d\n", pInst->GetInsID(), pInst->curSpeakerID(), wDsNum));

	MergerDsList(pInst, pInst->m_cSpeaker.m_tToVirSpeakerDs, tDsData, wDsNum, "CreateSpeakerToVirSpeaker");

	return wDsNum;
}


u16 CNetPortMgr::DestroyUmsToNode(CUmsConfInst* pInst, TCapNode* ptRmt)
{
	u16 wDelDsNum = 0;
	TUmsDsData tDelDsData[MAX_CHANNEL_DS_NUM];
	ptRmt->m_tDsList.GetMediaTrans(tDelDsData, wDelDsNum);

	CUmsConfInst::m_pcCallDs->FreeBuff(ptRmt->m_tDsList.GetHead());
	ptRmt->m_tDsList.Clear();

	MdlHint(Ums_Mdl_Call, ("DestroyUmsToNode. ConfID:%d, wEpID:%d, DsNum:%d\n", pInst->GetInsID(), ptRmt->m_wEpID, wDelDsNum));
	DestroyMediaTrans(pInst, tDelDsData, wDelDsNum);

	return 0;
}

void CNetPortMgr::FreeMediaTrans(CUmsConfInst* pInst, CDsListInfo& tListInfo)
{	
	u16 wDelDsNum = 0;
	TUmsDsData tDelDsData[MAX_CHANNEL_DS_NUM];
	tListInfo.GetMediaTrans(tDelDsData, wDelDsNum);

	CUmsConfInst::m_pcCallDs->FreeBuff(tListInfo.GetHead());
	tListInfo.Clear();

	MdlHint(Ums_Mdl_Call, ("FreeMediaTrans ConfID:%d, dsNum:%d\n", pInst->GetInsID(), wDelDsNum));
	DestroyMediaTrans(pInst, tDelDsData, wDelDsNum);
}


void CNetPortMgr::CreateVirSpeakerToBas(CUmsConfInst* pInst)
{
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;
	u16 wIndex = 0;

	TTPMediaTransAddr tAddr;

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (pInst->IsPriNeedBas())
		{//����VidBas
			pInst->GetBas()->GetSpeakerBas()->SetSrc(&pInst->GetSpeaker());
			pInst->GetBas()->GetInChnSpeakerVidAddr(tAddr, wIndex);
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetNetBufParam(wIndex).m_tRcvRtcpAddr;
			atDsData[wDsNum].m_tMapedAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		
		}
		
		if (pInst->IsAudNeedBas())
		{//����AudBas
			TTPDsFrom tAudbasAddr;
			pInst->GetBas()->GetSpeakerAudBasInAddr(wIndex, tAudbasAddr);
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAudbasAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAudbasAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAudbasAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;

		}
	}

	if (pInst->IsPriNeedBas()&& NULL != pInst->GetSpeaker().m_pcSingleBas)
	{//����VidBas
		pInst->GetBas()->GetSpeakerBas()->SetSrc(&pInst->GetSpeaker());
		pInst->GetBas()->GetInChnVidAddr(tAddr, pInst->GetSpeaker().m_pcSingleBas);
		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleNetBuf().m_tRcvRtcpAddr;
		atDsData[wDsNum].m_tMapedAddr = tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}
	
	if (pInst->IsAudNeedBas())
	{//Mix����AudBas
		TTPDsFrom tAudbasAddr;
		pInst->GetBas()->GetSpeakerMixAudBasInAddr(tAudbasAddr);
		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAudbasAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tAudbasAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = tAudbasAddr.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	
	}


	MergerDsList(pInst, pInst->GetBas()->GetSpeakerBas()->m_tDsList, atDsData, wDsNum, "CreateVirSpeakerToBas");
	
	return ;
}

void CNetPortMgr::CreateVirChairToBas( CUmsConfInst* pInst )
{
	u16 wDsNum = 0;
	TUmsDsData tDsData[MAX_CHANNEL_DS_NUM];

	TCapNode* ptChair = pInst->m_pcNodeMgr->GetCapsetNode(pInst->chairID());	
	if ( NULL == ptChair || !ptChair->IsChanOn() )
	{
		MdlHint(Ums_Mdl_Call, ("CreateVirChairToBas. ptChair is NULL! confID:%d, speaker:%d, chair:%d\n", 
												pInst->GetInsID(), pInst->curSpeakerID(), pInst->chairID()));
		return ;
	}

	CDsStrategyChairToBas cStrate;
	cStrate.SetPara(ptChair, NULL, NULL, pInst->IsChairConf());
	
	wDsNum = cStrate.GetDsToNode(pInst, tDsData, MAX_CHANNEL_DS_NUM);

	MergerDsList(pInst, pInst->GetBas()->GetChairToBasDsList(), tDsData, wDsNum, "CreateVirChairToBas");

	return ;
}

void CNetPortMgr::CreateMediaToSingleMixer( CUmsConfInst* pInst )
{
	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	
	TTPMediaTransAddr tAddrSrc;
	
	TCapNode* ptChair = pInst->m_pcNodeMgr->GetCapsetNode(pInst->chairID());	
	if ( NULL != ptChair && ptChair->IsChanOn() && NULL != pInst->GetSpeaker().m_ptAudMix
		&& pInst->curSpeakerID() != pInst->chairID() )
	{// ��ϯ�ͷ�������ͬһ����������һ��
		TTPTransAddr atChairAudRtp[TP_MAX_STREAMNUM];
		TTPTransAddr atChairAudRtcp[TP_MAX_STREAMNUM];
		TTPTransAddr tChairMixRtp, tChairMixRtcp;
		u32 adwRtpEqpNode[TP_MAX_STREAMNUM];
		u32 dwMixAudEqpNode;
		
		CDSStrategyToSpeaker cStrategySpeake;
		cStrategySpeake.SetPara(ptChair, NULL, NULL, pInst->IsChairConf());
		cStrategySpeake.GetAudAddr(pInst, atChairAudRtp, atChairAudRtcp, tChairMixRtp, tChairMixRtcp, adwRtpEqpNode, dwMixAudEqpNode, FALSE);
		
		pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tAddrSrc, pInst->chairID(), 3);
		
		if ( tChairMixRtp.m_wPort != 0 )
		{
			atDsData[wDsNum].m_tRcvFromAddr = tChairMixRtp;
			atDsData[wDsNum].m_tSndToAddr = tAddrSrc.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwMixAudEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetEPMixAudio();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddrSrc.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tChairMixRtcp;
			atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		}
		else
		{
			atDsData[wDsNum].m_tRcvFromAddr = atChairAudRtp[ptChair->GetSpeaker()];
			atDsData[wDsNum].m_tSndToAddr = tAddrSrc.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode =adwRtpEqpNode[ptChair->GetSpeaker()];
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetAudio(ptChair->GetSpeaker());
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddrSrc.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = atChairAudRtcp[ptChair->GetSpeaker()];
			atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		}
	}

	if ( NULL != pInst->GetSpeaker().m_ptAudMix  )
	{//�����˺���ϯ��ͬ��ֻ��һ��
		pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tAddrSrc, pInst->curSpeakerID(), 3);
		
		TCallNode* ptSpeaker = pInst->GetNodeMgr()->GetNode(pInst->curSpeakerID());
		TCapNode* ptFatherSpeaker = pInst->GetNodeMgr()->GetForeFatherNode(ptSpeaker);
		if (NULL != ptSpeaker && NULL != ptFatherSpeaker)
		{
			if (NULL != ptFatherSpeaker->m_ptMixAddr)
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptFatherSpeaker->m_ptMixAddr->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddrSrc.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetEPMixAudio();
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddrSrc.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptFatherSpeaker->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}
			else
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptFatherSpeaker->m_aptChanAddr[ptSpeaker->GetSpeaker()]->m_tAud.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddrSrc.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetAudio(ptSpeaker->GetSpeaker());
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddrSrc.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptFatherSpeaker->m_tRmtChan.m_atAudEnc[ptSpeaker->GetSpeaker()].m_tChanAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}
			
		}
	}

	if ( pInst->GetDualMgr()->IsStart() && NULL != pInst->GetSpeaker().m_ptAudMix  )
	{
		pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tAddrSrc, pInst->GetDualMgr()->GetDualID(), 4);

		TCallNode* ptDual = pInst->GetNodeMgr()->GetNode(pInst->GetDualMgr()->GetDualID());
		TCapNode* ptFartherDual = pInst->GetNodeMgr()->GetForeFatherNode(ptDual);
		if (NULL != ptDual && NULL != ptFartherDual)
		{
			//ȡ˫�� ��������
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetDualMgr()->m_tAudRcvAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddrSrc.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptFartherDual->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetDualAudio();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddrSrc.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetDualMgr()->m_tAudRcvAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptFartherDual->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		}
	}
	
	MergerDsList(pInst, pInst->GetSpeaker().m_tToAudMixDs, atDsData, wDsNum, "CreateMediaToSingleMixer");
	
	return ;
}

void CNetPortMgr::CreatVidToSingleVmpTp(CUmsConfInst* pInst)
{
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{// ����ģʽ�£��޷����˺ϳɣ��˺ϳ������۸���
        return;
	}

	TCallNode* ptNode = NULL;
	TCapNode*  ptFartherNode = NULL;
	
	ptNode = pInst->GetVmp()->GetVmpEp();
	ptFartherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	
	if (pInst->GetRollCallMgr()->IsRollCallModle())
	{   //����ģʽ
		CreateRollCallEpToVmp(pInst, ptFartherNode, ptNode);
	} else 
	{   //�ݽ�ģʽ
		CreateMeidaToVmp(pInst, ptFartherNode, ptNode);
	}

	return;
}


void CNetPortMgr::CreateRollCallEpToVmp(CUmsConfInst* pInst, TCapNode* ptFarterNode, TCallNode* ptNode)
{
	u16 wIndex = 0;
    TTPDsFrom tAddr;

	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

    if (pInst->GetVmp()->IsSpeakerInVmp())
	{ //�������ںϳ��У����������ںϳ��У�

		if (NULL != ptNode && NULL != ptFarterNode)
		{

			u32 dwNodeEqp = 0;
			dwNodeEqp = ptFarterNode->m_tMediaEqp.m_dwEqpNode;
			
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{//С���� ������С����
				pInst->GetVmp()->GetSpeakerVmpInAddr(tAddr, wIndex + 1);
				
				atDsData[wDsNum].m_tRcvFromAddr = ptFarterNode->m_aptSmallChanAddr[wIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = dwNodeEqp;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetSmallVideo(wIndex);
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptFarterNode->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;					
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
			
			//��ϯҪ����0��ͨ������Ϊ��ͼ��ʾ
			pInst->GetVmp()->GetSpeakerVmpInAddr(tAddr, 0);
			
			atDsData[wDsNum].m_tRcvFromAddr = ptFarterNode->m_aptChanAddr[ptNode->GetSpeaker()]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwNodeEqp;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(ptNode->GetSpeaker());
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptFarterNode->m_tRmtChan.m_atVidEnc[ptNode->GetSpeaker()].m_tChanAddr.m_tBackRtcpAddr;				
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
        
	} 
	else if(pInst->GetVmp()->IsChairInVmp())
	{ //��ϯ�ںϳ��У��������ںϳ��У�
        if (NULL != ptNode && NULL != ptFarterNode)
		{
			TVirCallerAddr *pVirRollCaller = pInst->GetRollCallMgr()->GetVirCallerAddr();
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{//С���� ������С����
				pInst->GetVmp()->GetSpeakerVmpInAddr(tAddr, wIndex + 1);
				
				atDsData[wDsNum].m_tRcvFromAddr = pVirRollCaller->m_aptSmallAddr[wIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = pVirRollCaller->m_adwMediaNode[wIndex];
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetSmallVideo(wIndex);
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = pVirRollCaller->m_aptSmallAddr[wIndex]->m_tBackRtcpAddr;					
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
			
			//��ϯҪ����0��ͨ������Ϊ��ͼ��ʾ
			pInst->GetVmp()->GetSpeakerVmpInAddr(tAddr, 0);
			
			atDsData[wDsNum].m_tRcvFromAddr = pVirRollCaller->m_aptVidAddr[ptNode->GetSpeaker()]->m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pVirRollCaller->m_adwMediaNode[ptNode->GetSpeaker()];
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(ptNode->GetSpeaker());
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pVirRollCaller->m_aptVidAddr[ptNode->GetSpeaker()]->m_tBackRtcpAddr;				
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		    ++wDsNum;
		}   
	}

	MdlHint(Ums_Mdl_Call, ("CreateRollCallEpToVmp. ConfID:%d, DsNum:%d\n", pInst->GetInsID(), wDsNum));
	MergerDsList(pInst, pInst->GetSpeaker().m_tToVmpDs, atDsData, wDsNum, "CreateRollCallEpToVmp");	

}


void CNetPortMgr::CreateMeidaToVmp(CUmsConfInst* pInst, TCapNode* ptFarterNode, TCallNode* ptNode)
{
	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	if (NULL != ptNode && NULL != ptFarterNode)
	{
		u32 dwEqpIP = 0;
		u32 dwNodeEqp = 0;

		TTPDsFrom tAddr;

		dwEqpIP = ptFarterNode->m_tMediaEqp.m_dwEqpIp;
		dwNodeEqp = ptFarterNode->m_tMediaEqp.m_dwEqpNode;
		
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{//С���� ������С����
			pInst->GetVmp()->GetSpeakerVmpInAddr(tAddr, wIndex + 1);
		
			atDsData[wDsNum].m_tRcvFromAddr = ptFarterNode->m_aptSmallChanAddr[wIndex]->m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwNodeEqp;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetSmallVideo(wIndex);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptFarterNode->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;					
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		
		//��ϯҪ����0��ͨ������Ϊ��ͼ��ʾ
		pInst->GetVmp()->GetSpeakerVmpInAddr(tAddr, 0);
		
		atDsData[wDsNum].m_tRcvFromAddr = ptFarterNode->m_aptChanAddr[ptNode->GetSpeaker()]->m_tVid.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwNodeEqp;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetVideo(ptNode->GetSpeaker());
		++wDsNum;
		
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptFarterNode->m_tRmtChan.m_atVidEnc[ptNode->GetSpeaker()].m_tChanAddr.m_tBackRtcpAddr;				
		atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}

	MdlHint(Ums_Mdl_Call, ("CreateMeidaToVmp. ConfID:%d, DsNum:%d\n", pInst->GetInsID(), wDsNum));
	MergerDsList(pInst, pInst->GetSpeaker().m_tToVmpDs, atDsData, wDsNum, "CreateMeidaToVmp");	
}



void CNetPortMgr::CreateRollCallMediaToDulMixer( CUmsConfInst* pInst )
{
	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	if (pInst->IsChairConf())
	{
		//������
        u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();
		TCallNode *pCallerNode = pInst->GetNodeMgr()->GetNode(wRollCaller);

        TServiceAddr tScrAddr;
        TTPMediaTransAddr tdstAddr;

		if (NULL != pCallerNode && pCallerNode->IsChanOn() && NULL != pInst->GetSpeaker().m_ptAudMix)
		{
			pInst->GetRollCallMgr()->GetRollCallEpAudAddr(wRollCaller, TP_MAX_STREAMNUM, tScrAddr);
			pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tdstAddr, wRollCaller, TP_MAX_STREAMNUM);

			atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tdstAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = tdstAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
            
		}

		//��������(������)
		if ( NULL != pInst->GetSpeaker().m_ptAudMix  )
		{
			pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tdstAddr, pInst->curSpeakerID(), TP_MAX_STREAMNUM);
			
			TCallNode* ptSpeaker = pInst->GetNodeMgr()->GetNode(pInst->curSpeakerID());
			TCapNode* ptFatherSpeaker = pInst->GetNodeMgr()->GetForeFatherNode(ptSpeaker);
			if (NULL != ptSpeaker && NULL != ptFatherSpeaker)
			{
				if (NULL != ptFatherSpeaker->m_ptMixAddr)
				{
					atDsData[wDsNum].m_tRcvFromAddr = ptFatherSpeaker->m_ptMixAddr->m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = tdstAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetEPMixAudio();
					wDsNum++;
					
					atDsData[wDsNum].m_tRcvFromAddr = tdstAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptFatherSpeaker->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}
				else
				{
					u16 wSeatIndex = ptSpeaker->GetSpeaker();
					if (NULL != ptFatherSpeaker->m_aptChanAddr[wSeatIndex])
					{
						atDsData[wDsNum].m_tRcvFromAddr = ptFatherSpeaker->m_aptChanAddr[wSeatIndex]->m_tAud.m_tRtpAddr;
						atDsData[wDsNum].m_tSndToAddr = tdstAddr.m_tRtpAddr;
						atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtpSwap;
						atDsData[wDsNum].SetAudio(wSeatIndex);
						wDsNum++;
						
						atDsData[wDsNum].m_tRcvFromAddr = tdstAddr.m_tBackRtcpAddr;
						atDsData[wDsNum].m_tSndToAddr = ptFatherSpeaker->m_tRmtChan.m_atAudEnc[wSeatIndex].m_tChanAddr.m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = ptFatherSpeaker->m_tMediaEqp.m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					    wDsNum++;
					}

				}
				
			}
		} 

		//˫��
		if ( pInst->GetDualMgr()->IsStart() && NULL != pInst->GetSpeaker().m_ptAudMix  )
		{
			pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tdstAddr, pInst->GetDualMgr()->GetDualID(), 4);
			
			TCallNode* ptDual = pInst->GetNodeMgr()->GetNode(pInst->GetDualMgr()->GetDualID());
			TCapNode* ptFartherDual = pInst->GetNodeMgr()->GetForeFatherNode(ptDual);
			if (NULL != ptDual && NULL != ptFartherDual)
			{
				//ȡ˫�� ��������
				atDsData[wDsNum].m_tRcvFromAddr = pInst->GetDualMgr()->m_tAudRcvAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tdstAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptFartherDual->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetDualAudio();
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tdstAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetDualMgr()->m_tAudRcvAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptFartherDual->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}
		}
	}
	else
	{

	}
	
	MergerDsList(pInst, pInst->GetSpeaker().m_tToAudMixDs, atDsData, wDsNum, "CreateRollCallMediaToDulMixer");

}


void CNetPortMgr::CreateDualFromDownToUp(CUmsConfInst* pInst)
{
	TUmsDsData tDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = FindDualFromDownToUp(pInst, tDsData, MAX_CHANNEL_DS_NUM);
	
	CDualMgr* pcDualMgr = pInst->GetDualMgr();
	MergerDsList(pInst, pcDualMgr->m_tToUpUms, tDsData, wDsNum, "CreateDualFromDownToUp");
	return;
}
void CNetPortMgr::DestroyDualFromDownToUp(CUmsConfInst* pInst)
{
	MdlHint(Ums_Mdl_Call, ("DestroyDualFromDownToUp. ConfID:%d\n", pInst->GetInsID()));
	CDualMgr* pcDualMgr = pInst->GetDualMgr();
	FreeMediaTrans(pInst, pcDualMgr->m_tToUpUms);
	return;	
}

void CNetPortMgr::AjustDualFromNodeToUms(CUmsConfInst* pInst)
{
	TUmsDsData tDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;
	wDsNum = FindDualFromNodeToUms(pInst, tDsData, MAX_CHANNEL_DS_NUM);
	MdlHint(Ums_Mdl_Call, ("AjustDualFromNodeToUms. ConfID:%d, DsNum:%d\n", pInst->GetInsID(), wDsNum));
	MergerDsList(pInst, pInst->m_pcDual->m_tDualDsEpToUms, tDsData, wDsNum, "AjustDualFromNodeToUms");
	return;
}
void CNetPortMgr::DestroyDualFromNodeToUms(CUmsConfInst* pInst)
{
	TUmsDsData tDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = FindDualFromNodeToUms(pInst, tDsData, MAX_CHANNEL_DS_NUM);
	MdlHint(Ums_Mdl_Call, ("DestroyDualFromNodeToUms. ConfID:%d, DsNum:%d\n", pInst->GetInsID(), wDsNum));
	
	DestroyMediaTrans(pInst, tDsData, wDsNum);
	return;	
}


u16 CNetPortMgr::CreateTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo)
{
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = FindTvWallTrans(pInst, ptInfo, atDsData, MAX_CHANNEL_DS_NUM);
	MdlHint(Ums_Mdl_Call, ("CreateTvWallTrans. ConfID:%d, wChanIndex:%d, DsNum:%d\n"
							, pInst->GetInsID(), ptInfo->m_tChanInfo.m_wScreenIndex, wDsNum));

	MergerDsList(pInst, ptInfo->m_tChanInfo.m_tToHdu, atDsData, wDsNum, "CreateTvWallTrans");	
	return wDsNum;
}

u16 CNetPortMgr::DestroyTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo)
{
	TUmsDsData tDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = FindTvWallTrans(pInst, ptInfo, tDsData, MAX_CHANNEL_DS_NUM);
	MdlHint(Ums_Mdl_Call, ("DestroyTvWallTrans. ConfID:%d, wChanIndex:%d, DsNum:%d\n", 
						pInst->GetInsID(), ptInfo->m_tChanInfo.m_wScreenIndex, wDsNum));
	FreeMediaTrans(pInst, ptInfo->m_tChanInfo.m_tToHdu);
	return wDsNum;
}


BOOL32 CNetPortMgr::CreateSpeakerToVirSpeakerForIframeCheck(CUmsConfInst* pInst, TCallNode* ptCurSpeaker, TCallNode* ptNewSpeaker, u16 wChanIndex)
{
	pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
	TTPTransAddr tAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;


	TCapNode* ptNewtForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptNewSpeaker);	
	if (NULL == ptNewtForether)
	{
		MdlError(Ums_Mdl_Call, ("CreateSpeakerToVirSpeakerForIframeCheck Conf:%d, chan:%d ptNewtForether is null\n", pInst->GetInsID(), wChanIndex));
		return FALSE;
	}

	TCapNode* pCurtForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptCurSpeaker);	
	if (NULL == pCurtForether)
	{
		MdlError(Ums_Mdl_Call, ("CreateSpeakerToVirSpeakerForIframeCheck Conf:%d, chan:%d ptCurForether is null\n", pInst->GetInsID(), wChanIndex));
		return FALSE;
	}

	if ( !pCurtForether->IsChanOn() || !ptNewtForether->IsChanOn() )
	{
		MdlHint(Ums_Mdl_Call, ("CreateSpeakerToVirSpeakerForIframeCheck Conf:%d, noOnline. CurChan:%d,NewChan:%d\n", 
			pInst->GetInsID(), pCurtForether->IsChanOn(), ptNewtForether->IsChanOn()));
		return FALSE;
	}

	MdlHint(Ums_Mdl_Call, ("CreateSpeakerToVirSpeakerForIframeCheck Conf:%d, epid:%d, chan:%d, port:%d\n", pInst->GetInsID(), ptNewSpeaker->m_wEpID, wChanIndex, tAddr.m_wPort));
	 
	TCheckIFrameBase tIFrameBase;
	TIFrameBySrc	tIFrameBySrc;

	tIFrameBase.m_emType = TP_IFrameCheck_Speaker;
	tIFrameBase.m_wConfID = pInst->GetInsID();
	tIFrameBase.m_wExpires = IFRAME_CHECK_TIMEOUT;
	
	tIFrameBySrc.m_dwOldIP = pCurtForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr.GetIP();
	tIFrameBySrc.m_wOldPort = pCurtForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr.GetPort();

	tIFrameBySrc.m_dwNewIP = ptNewtForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr.GetIP();
	tIFrameBySrc.m_wNewPort = ptNewtForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr.GetPort();

	tIFrameBase.m_dwIP = tAddr.GetIP();
	tIFrameBase.m_wPort = tAddr.m_wPort;
		
	tIFrameBySrc.m_wNewSpeakerID = ptNewSpeaker->m_wEpID;
	tIFrameBySrc.m_wChanIndex = wChanIndex;


	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_iframe_bySrc);
	cMsg.SetBody(&tIFrameBase, sizeof(tIFrameBase));
	cMsg.CatBody(&tIFrameBySrc, sizeof(tIFrameBySrc));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, pInst->m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));
	return TRUE;
}

u16 CNetPortMgr::DestroySpeakerToVirSpeakerForIframeCheck(CUmsConfInst* pInst, u16 wChanIndex)
{	
	pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
	TTPTransAddr tAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;

	MdlHint(Ums_Mdl_Call, ("DestroySpeakerToVirSpeakerForIframeCheck Conf:%d, chan:%d, port:%d\n", pInst->GetInsID(), wChanIndex, tAddr.m_wPort));

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_del_iframe);
	cMsg.SetBody(&tAddr, sizeof(tAddr));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, pInst->m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));
	return 0;
}


BOOL32 CNetPortMgr::CreateSpeakerToSingleVirSpeakerForIframeCheck(CUmsConfInst* pInst, TCallNode* ptCurSpeaker, u16 wCurIndex, TCallNode* ptNewSpeaker, u16 wNewIndex)
{
	pInst->GetSingleVidDec().SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
	TTPTransAddr tAddr = pInst->GetSingleVidDec().m_tRtpAddr;

	TCapNode* ptNewtForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptNewSpeaker);	
	if (NULL == ptNewtForether)
	{
		MdlError(Ums_Mdl_Call, ("CreateSpeakerToSingleVirSpeakerForIframeCheck Conf:%d, ptNewtForether is null\n", pInst->GetInsID()));
		return FALSE;
	}
	
	TCapNode* ptCurForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptCurSpeaker);	
	if (NULL == ptCurForether)
	{
		MdlError(Ums_Mdl_Call, ("CreateSpeakerToSingleVirSpeakerForIframeCheck Conf:%d, ptCurForether is null\n", pInst->GetInsID()));
		return FALSE;
	}

	if ( !ptCurForether->IsChanOn() || !ptNewtForether->IsChanOn() )
	{
		MdlHint(Ums_Mdl_Call, ("CreateSpeakerToSingleVirSpeakerForIframeCheck Conf:%d, noOnline. CurChan:%d,NewChan:%d\n", 
			pInst->GetInsID(), ptCurForether->IsChanOn(), ptNewtForether->IsChanOn()));
		return FALSE;
	}
	
	MdlHint(Ums_Mdl_Call, ("CreateSpeakerToSingleVirSpeakerForIframeCheck Conf:%d, epid:%d, port:%d\n", pInst->GetInsID(), ptNewSpeaker->m_wEpID, tAddr.m_wPort));
	
	TCheckIFrameBase tIFrameBase;
	TIFrameBySrc	tIFrameBySrc;
	
	tIFrameBase.m_emType = TP_IFrameCheck_SingleSpeaker;
	tIFrameBase.m_wConfID = pInst->GetInsID();
	tIFrameBase.m_wExpires = IFRAME_CHECK_TIMEOUT;

	if (pInst->GetVmp()->IsSpeakVmpOn())   //�������Ժϳ�
	{
		TTPDsFrom tAddrVmp;
		pInst->m_pcVmp->GetSpeakerVmpOutAddr(tAddrVmp);

		if ((ptCurForether->IsThreeVidSnd()) && (ptNewtForether->IsThreeVidSnd()))  
		{
			//���Ϸ����˶�Ϊ�����Ҵ򿪷��Ժϳɣ������ؼ�֡
			return FALSE;

		}
		else if ((ptCurForether->IsThreeVidSnd()))  //�Ϸ�����Ϊ����
		{
			tIFrameBySrc.m_dwOldIP = tAddrVmp.m_tRtpAddr.GetIP();
			tIFrameBySrc.m_wOldPort = tAddrVmp.m_tRtpAddr.GetPort();

			tIFrameBySrc.m_dwNewIP = ptNewtForether->m_aptChanAddr[wNewIndex]->m_tVid.m_tRtpAddr.GetIP();
			tIFrameBySrc.m_wNewPort = ptNewtForether->m_aptChanAddr[wNewIndex]->m_tVid.m_tRtpAddr.GetPort();
		}
		else if ((ptNewtForether->IsThreeVidSnd()))  //�·�����Ϊ����
		{
			tIFrameBySrc.m_dwOldIP = ptCurForether->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtpAddr.GetIP();
			tIFrameBySrc.m_wOldPort = ptCurForether->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtpAddr.GetPort();

			tIFrameBySrc.m_dwNewIP = tAddrVmp.m_tRtpAddr.GetIP();
			tIFrameBySrc.m_wNewPort = tAddrVmp.m_tRtpAddr.GetPort();
		}
	}	
	else   //��Ϊ������δ�������Ժϳ�
	{
		tIFrameBySrc.m_dwOldIP = ptCurForether->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtpAddr.GetIP();
		tIFrameBySrc.m_wOldPort = ptCurForether->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtpAddr.GetPort();

		tIFrameBySrc.m_dwNewIP = ptNewtForether->m_aptChanAddr[wNewIndex]->m_tVid.m_tRtpAddr.GetIP();
		tIFrameBySrc.m_wNewPort = ptNewtForether->m_aptChanAddr[wNewIndex]->m_tVid.m_tRtpAddr.GetPort();
	}
	
	tIFrameBase.m_dwIP = tAddr.GetIP();
	tIFrameBase.m_wPort = tAddr.m_wPort;
	
	tIFrameBySrc.m_wNewSpeakerID = ptNewSpeaker->m_wEpID;
	
	
	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_iframe_bySrc);
	cMsg.SetBody(&tIFrameBase, sizeof(tIFrameBase));
	cMsg.CatBody(&tIFrameBySrc, sizeof(tIFrameBySrc));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, pInst->m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));

	return TRUE;
}

u16 CNetPortMgr::DestroySpeakerToSingleVirSpeakerForIframeCheck(CUmsConfInst* pInst)
{
	TTPTransAddr tAddr = pInst->GetSingleVidDec().m_tRtpAddr;
	MdlHint(Ums_Mdl_Call, ("DestroySpeakerToSingleVirSpeakerForIframeCheck Conf:%d, port:%d\n", pInst->GetInsID(), tAddr.m_wPort));

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_del_iframe);
	cMsg.SetBody(&tAddr, sizeof(tAddr));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, pInst->m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));
	return 0;
}

BOOL32 CNetPortMgr::CreatePollForIframeCheck(CUmsConfInst* pInst, TTPTransAddr* ptCurAddr, TTPTransAddr* ptOldAddr, u16 wChanIndex, u16 wNewPollID)
{
	MdlLowHint(Ums_Mdl_Call, ("CreatePollForIframeCheck Conf:%d, port:%d port:%d\n", pInst->GetInsID(), ptCurAddr->GetPort(), ptOldAddr->GetPort()));
	
	TCheckIFrameBase tBase;
	TIFrameTwoRcvPort tTwoRcv;
	tBase.m_emType = TP_IFrameCheck_Poll;
	tBase.m_wConfID = pInst->GetInsID();
	tBase.m_wExpires = IFRAME_CHECK_TIMEOUT;
	tBase.m_dwIP = ptCurAddr->GetIP();

	tTwoRcv.m_bTrans = TRUE;	
	tTwoRcv.m_wNewPort = ptCurAddr->GetPort();
	tTwoRcv.m_wOldPort = ptOldAddr->GetPort();
	tTwoRcv.m_wChanIndex = wChanIndex;
	tTwoRcv.m_wPollEp = wNewPollID;


	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_iframe_TwoRcvPort);
	cMsg.SetBody(&tBase, sizeof(tBase));
	cMsg.CatBody(&tTwoRcv, sizeof(tTwoRcv));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, pInst->m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));

	return TRUE;
}

BOOL32 CNetPortMgr::DestroyPollForIframeCheck(CUmsConfInst* pInst, TTPTransAddr* ptCurAddr, TTPTransAddr* ptOldAddr)
{	
	MdlLowHint(Ums_Mdl_Call, ("DestroyPollForIframeCheck Conf:%d, port:%d port:%d\n", pInst->GetInsID(), ptCurAddr->GetPort(), ptOldAddr->GetPort()));

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_ds_del_iframe);

	cMsg.SetBody(ptCurAddr, sizeof(TTPTransAddr));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, pInst->m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));

	cMsg.SetBody(ptOldAddr, sizeof(TTPTransAddr));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, pInst->m_tEqpConfDs.m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));

	return TRUE;
}

/*==============================================================================
������    :  GetSpeakerToVirSpeaker
����      :  �����Ի᳡������ת�����ⷢ����
�㷨ʵ��  :  
����˵��  :  
����ֵ˵��:  
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2011-5-12               zhaixiaogang
==============================================================================*/
u16 CNetPortMgr::GetSpeakerToVirSpeaker(BOOL32 bIsCreate, CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs)
{
	TCallNode* ptCurSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->curSpeakerID());
	TCapNode* ptCurForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptCurSpeaker);	

	TCallNode* ptOldSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->oldSpeakerID());
	TCapNode* ptOldForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldSpeaker);	

	if (NULL == ptCurSpeaker && NULL == ptOldSpeaker )
	{
		MdlHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker speaker epid error. confID:%d, curEp:%d, NewEp:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->oldSpeakerID()));
		return 0;
	}

	u16 wDsNum = 0;

	if ( !ptCurSpeaker->IsChanOn() )
	{//��ǰ�����˲����� ɾ�����н���
		MdlHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker speaker stat error. confID:%d, curEp:%d, NewEp:%d, curEpStat:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->oldSpeakerID(), ptCurSpeaker->IsChanOn()));
		

		wDsNum = GetNonSpeakerToVirSpeaker(pInst, atDsData, wMaxDs);
		
		return wDsNum;
	}

	u16 wEqpIndex;
	u32 dwNodeIP = 0;

	u32 dwNodeEqp = 0;
	u32 dwConfEqp = pInst->m_tEqpConfDs.m_dwEqpNode;

	u16 wChanIndex = 0;
	
	TEqpRes* ptEqp;

	u16 wTempNum = 0;
	u16 wMidIndex = MIDSCREENINDEX;
	u16 wIndex = 1;
	s32 symbolflag = 1; 
	BOOL32 bFilterFlag = FALSE;
	//���Ժϳ�
	TTPDsFrom tAddr;
	pInst->GetVmp()->GetSpeakerVmpOutAddr(tAddr);
	//��Ƶ
	if (NULL != ptCurSpeaker && ptCurSpeaker->IsVidSndValid())
	{
		symbolflag = 1; 
		for (u16 wIndex = 1; wIndex <= ptCurSpeaker->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

			pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);

			if(	pInst->GetVmp()->IsBrdVmp() && wChanIndex == MIDSCREENINDEX )
			{//�ϳɹ㲥���������м��� ���պϳɹ㲥
				TTPDsFrom tAddr;
				pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr, ptCurForether->m_tVidSndFormat.m_tFormat, TRUE);

				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVmpVideo();
				++wDsNum;

				atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
				continue;
			}

			atDsData[wDsNum].m_tRcvFromAddr = ptCurForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;

			if (pInst->m_abOnIFrameCheck[wChanIndex])
			{//��Ҫ���ؼ�֡����ؼ�֡������Ȼ�����ϵķ�����
				continue;
			}
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptCurForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if ( pInst->GetVmp()->IsBrdVmp() )
		{
			TTPDsFrom tAddr;
			pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr, ptCurForether->m_tVidSndFormat.m_tFormat, TRUE);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVmpVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else if ( !pInst->GetVmp()->IsSpeakerInVmp())
		{//����ϯ��������û�ڷ����˺ϳ���
			wChanIndex = ptCurSpeaker->GetSpeaker();
			atDsData[wDsNum].m_tRcvFromAddr = ptCurForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptCurForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else
		{//�������˺ϳ�
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}


	if (NULL != ptOldSpeaker && ptOldSpeaker->IsVidSndValid())
	{
		symbolflag = 1; 
		for (u16 wIndex = 1; wIndex <= ptOldSpeaker->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

			if (!pInst->m_abOnIFrameCheck[wChanIndex])
			{//����Ҫ���ؼ�֡
				continue;
			}

			if(	pInst->GetVmp()->IsBrdVmp() && wChanIndex == MIDSCREENINDEX )
			{//�ϳɹ㲥���������м��� ���պϳɹ㲥������Ҫ���
				continue;
			}
				
			pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
			
			atDsData[wDsNum].m_tRcvFromAddr = ptOldForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptOldForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptOldForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if (pInst->m_bOnSingleIframeCheck)
		{//���ڽ��йؼ�֡��⣬���ϵ�����Ҳת�����ⷢ����
			wChanIndex = ptOldSpeaker->GetSpeaker();
			if (ptOldSpeaker->IsThreeVidSnd())   //�Ϸ�����Ϊ����
			{
				if (pInst->GetVmp()->IsSpeakVmpOn())   //�������Ժϳ�
				{
					atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				}
				else
				{
					atDsData[wDsNum].m_tRcvFromAddr = ptOldForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptOldForether->m_tMediaEqp.m_dwEqpNode;
				}
			}
			else
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptOldForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptOldForether->m_tMediaEqp.m_dwEqpNode;
			}
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;
		}
	}

	//��Ƶ
	if (pInst->GetAudMix()->IsAudMixMode() && NULL != ptCurForether)
	{
		TServiceAddr tAddr;
		pInst->GetAudMix()->GetMixNModeRcvAddr(ptCurForether->m_tAudSndFormat.m_tFormat, tAddr, FALSE);

		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;


		if (pInst->IsChairConf() && pInst->GetDualMgr()->IsStart() &&  pInst->GetSpeaker().m_bIsDualMixOn)
		{
			pInst->GetDualMgr()->AdjustDualMixForConfAudMix();// ��Ҫ����

			//�����������֮���ٿ�˫����Ӧ����PUT ������Ƶ
            pInst->GetAudMix()->PutAudDown();
		}

        pInst->GetAudMix()->GetMixNModeRcvAddr(ptCurForether->m_tAudSndFormat.m_tFormat, tAddr, TRUE);
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;

	}
			

	else if (NULL != ptCurSpeaker && ptCurSpeaker->IsAudSndValid())
	{
		symbolflag = 1; 
		for (u16 wIndex = 1; wIndex <= ptCurSpeaker->m_wAudSndNum; ++wIndex, symbolflag *= -1)
		{
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

			pInst->GetSpeakerAudDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);

			atDsData[wDsNum].m_tRcvFromAddr = ptCurForether->m_aptChanAddr[wChanIndex]->m_tAud.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wChanIndex).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetAudio(wChanIndex);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wChanIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptCurForether->m_tRmtChan.m_atAudEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		BOOL32 bDualMix = CUmsConfigEx::GetInstance()->IsDualMixOn();

		TServiceAddr tAudAddr;
		if (pInst->GetDualMgr()->IsStart() &&  pInst->GetSpeaker().m_bIsDualMixOn &&  (bDualMix || pInst->curSpeakerID() < CALLER_EP_INDEX))
		{//˫������ ����˫���ͷ����˵Ļ���
			pInst->GetDualMgr()->AdjustDualMix();// ��Ҫ����
			if (pInst->chairID() == pInst->curSpeakerID())
			{
				pInst->GetEapu()->GetNModeAudRcvAddr(pInst->GetSpeaker().m_ptAudMix, tAudAddr, ptCurForether->m_tAudSndFormat.m_tFormat);
			}
			else
			{
				pInst->GetEapu()->GetMixerChnOutAddr(pInst->GetSpeaker().m_ptAudMix, tAudAddr, pInst->chairID(), TP_MAX_STREAMNUM);
			}
		}
		else if ( ptCurForether->m_ptMixAddr != NULL )
		{//�����˻���
			tAudAddr.m_tAddr.m_tRtpAddr = ptCurForether->m_ptMixAddr->m_tRtpAddr;
			tAudAddr.m_tAddr.m_tBackRtcpAddr = ptCurForether->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
		}
		else
		{//����û�򿪣��ʹ�������ϯ
			tAudAddr.m_tAddr.m_tRtpAddr = ptCurForether->m_aptChanAddr[ptCurSpeaker->GetSpeaker()]->m_tAud.m_tRtpAddr;
			tAudAddr.m_tAddr.m_tBackRtcpAddr = ptCurForether->m_tRmtChan.m_atAudEnc[ptCurSpeaker->GetSpeaker()].m_tChanAddr.m_tBackRtcpAddr;
		}
		atDsData[wDsNum].m_tRcvFromAddr = tAudAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAudAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}
	else
	{
		// 
	}

	for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
	{//�ӻ���ת���壬ת��������ת����
		ptEqp = &pInst->m_atDsEqp[wEqpIndex];
		if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
		{
			MdlLowHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker Valid:%d, EpIndex:%d, ConfIndex:%d.\n",
									   ptEqp->IsValid(), ptEqp->m_wEqpIndex,
									   pInst->m_tEqpConfDs.m_wEqpIndex));
			continue;
		}

		for( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
		}
		
		//�������
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		++wDsNum;

		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;		
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
	}
	
	return wDsNum;
}


u16 CNetPortMgr::FindTvWallTrans(CUmsConfInst* pInst, TVWallInfo* ptInfo, TUmsDsData atDsData[], u16 wMaxDs)
{
	if (NULL == pInst || NULL == ptInfo)
	{
		return 0;
	}

	//Խ�籣��
	if(ptInfo->m_tChanInfo.m_wScreenIndex >= TP_MAX_STREAMNUM)
	{
		MdlError(Ums_Mdl_Call, ("[FindTvWallTrans] Error by SpeakerIndex excess\n"));
		return 0;
	}

	u32	dwMediaNode = 0;
	TTPMediaTransAddr tVidAddr;
	TTPMediaTransAddr tAudAddr;
	if ( ptInfo->m_tChanInfo.m_emType == EmEpType_Ter )
	{
		tVidAddr = ptInfo->m_tAddr.m_atVidAddr[MIDSCREENINDEX];
		tAudAddr = ptInfo->m_tAddr.m_atAudAddr[MIDSCREENINDEX];
		dwMediaNode = ptInfo->m_tAddr.m_dwMedia;
	}
	else
	{
		TTPDsFrom tVmp;
		pInst->GetVmp()->GetBrdVmpOutAddr(ptInfo->m_ptVmp, tVmp, ptInfo->m_tFormat);
		tVidAddr.m_tRtpAddr = tVmp.m_tRtpAddr;
		tVidAddr.m_tBackRtcpAddr = tVmp.m_tBackRtcpAddr;
		dwMediaNode = tVmp.m_dwEqpNode;
	}
	
	u16 wDsNum = 0;

	//��Ƶ
	atDsData[wDsNum].m_tRcvFromAddr = tVidAddr.m_tRtpAddr;
	atDsData[wDsNum].m_tSndToAddr = ptInfo->m_tChanInfo.m_tTvVidRcv.m_tRtpAddr;
	atDsData[wDsNum].m_dwEqpNode = dwMediaNode;
	atDsData[wDsNum].m_emSwitchType = emRtpSwap;
	atDsData[wDsNum].SetUnknowVideo();
	wDsNum++;

	atDsData[wDsNum].m_tRcvFromAddr = ptInfo->m_tChanInfo.m_tTvVidRcv.m_tBackRtcpAddr;
	atDsData[wDsNum].m_tSndToAddr = tVidAddr.m_tBackRtcpAddr;
	atDsData[wDsNum].m_dwEqpNode = dwMediaNode;
	atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
	wDsNum++;

	if (!ptInfo->m_tChanInfo.m_bVmp && ptInfo->m_tChanInfo.m_emType == EmEpType_Ter)
	{// ��Ƶ
		atDsData[wDsNum].m_tRcvFromAddr = tAudAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptInfo->m_tChanInfo.m_tTvAudRcv.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;

		atDsData[wDsNum].m_tRcvFromAddr = ptInfo->m_tChanInfo.m_tTvAudRcv.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAudAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	return wDsNum;
}

u16 CNetPortMgr::FindDualFromDownToUp(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs)
{
	u16 wDsNum = 0;
	TCapNode* ptChair = pInst->m_pcNodeMgr->GetCaller();
	CDualMgr* pcDualMgr = pInst->GetDualMgr();

	//�˴���m_tDualVidSndFormat �����䣬UMS��һ���ǷǱ�ͨ����ý���ʽ���Ǻͱ�׼ͨ��һ��
	BOOL32 bDualBas = pInst->GetBas()->IsDualNeedBas(ptChair->m_tDualVidSndFormat.m_tFormat);

	TTPMediaTransAddr tAddr;//�����ַ
	if ( bDualBas )
	{//˫������
		pInst->GetBas()->GetOutDualVidAddr(tAddr, ptChair->m_tDualVidSndFormat.m_tFormat);
	}
	else
	{
		tAddr.m_tRtpAddr = pcDualMgr->m_tVidRcvAddr.m_tRtpAddr;
		tAddr.m_tBackRtcpAddr = pcDualMgr->m_tVidNetBuf.m_tRcvRtcpAddr;
	}

	if(tAddr.m_tRtpAddr.GetIP() != 0  && 
	   tAddr.m_tRtpAddr.GetPort() != 0 && 
	   ptChair->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr.GetIP() != 0 &&
	   ptChair->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr.GetPort())
	{
		//��Ƶ
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptChair->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr;	
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
	    wDsNum++;
	}



	if (tAddr.m_tBackRtcpAddr.GetIP() != 0 &&
        tAddr.m_tBackRtcpAddr.GetPort() != 0  &&
		ptChair->m_ptDualAddr->m_tVid.m_tRtcpForSnd.GetIP() != 0 &&
		ptChair->m_ptDualAddr->m_tVid.m_tRtcpForSnd.GetPort() != 0)
	{
		//BACKRTCP -> netbuf
		atDsData[wDsNum].m_tRcvFromAddr = ptChair->m_ptDualAddr->m_tVid.m_tRtcpForSnd;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
		if ( !bDualBas  && 
			ptChair->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr.GetIP() != 0 &&
			ptChair->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr.GetPort() != 0)
		{
			atDsData[wDsNum].m_tMapedAddr = ptChair->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr;
		}
		atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
	    wDsNum++;
	}


	tAddr.m_tRtpAddr = pcDualMgr->m_tAudRcvAddr.m_tRtpAddr;
	tAddr.m_tBackRtcpAddr = pcDualMgr->m_tAudRcvAddr.m_tBackRtcpAddr;

	//��Ƶ

	if (tAddr.m_tRtpAddr.GetIP() != 0 &&
		tAddr.m_tRtpAddr.GetPort() != 0 &&
		ptChair->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtpAddr.GetIP() != 0 &&
		ptChair->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtpAddr.GetPort() != 0 )
	{
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptChair->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtpAddr;	
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
	    wDsNum++;
	}

	
	if (tAddr.m_tBackRtcpAddr.GetIP() != 0 &&
		tAddr.m_tBackRtcpAddr.GetPort() != 0 &&
		ptChair->m_ptDualAddr->m_tAud.m_tRtcpForSnd.GetIP() != 0 &&
		ptChair->m_ptDualAddr->m_tAud.m_tRtcpForSnd.GetPort() != 0)
	{
		atDsData[wDsNum].m_tRcvFromAddr = ptChair->m_ptDualAddr->m_tAud.m_tRtcpForSnd;
		atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
	    wDsNum++;
	}


	return wDsNum;
}

u16 CNetPortMgr::FindDualFromNodeToUms(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs)
{
	u16 wDsNum = 0;

	if (pInst->m_pcDual->IsStart())
	{
		TCapNode* ptNode = pInst->m_pcNodeMgr->GetForeFatherNode(pInst->m_pcDual->m_wCurDual);
		if (NULL == ptNode)
		{
			ptNode = pInst->m_pcNodeMgr->GetCaller();
			//�ϼ���Caller
			if ( NULL == ptNode || pInst->IsChairConf() )
			{
				return wDsNum;
			}
		}

		//RTP -> UMS���յ�ַ
		atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptDualAddr->m_tVid.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->m_pcDual->m_tVidRcvAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetDualVideo();
		wDsNum++;

		//RTP  -> netbuf
		atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptDualAddr->m_tVid.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->m_pcDual->m_tVidNetBuf.m_tRcvRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetDualVideo();
		wDsNum++;

		atDsData[wDsNum].m_tRcvFromAddr = pInst->m_pcDual->m_tVidRcvAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_tDualVidEnc.m_tChanAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;

		u16 wEqpIndex = 0;
		TEqpRes* ptEqp = NULL;
		for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
		{//�ӻ���ת���壬ת��������ת����
			ptEqp = &pInst->m_atDsEqp[wEqpIndex];
			if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
			{
				continue;
			}
			//ת��������ת����
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptDualAddr->m_tVid.m_tRtpAddr;
			
			atDsData[wDsNum].m_tSndToAddr = pInst->m_pcDual->m_tVidRcvAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetDualVideo();
			++wDsNum;
		}

		if ( pInst->IsDualNeedBas() )
		{
			//UMS �� �����
			TTPMediaTransAddr tAddr;
			pInst->m_pcBas->GetInDualVidAddr(tAddr);

			//RTP UMS���յ�ַ  -> ˫������ͨ��
			atDsData[wDsNum].m_tRcvFromAddr = pInst->m_pcDual->m_tVidRcvAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetDualVideo();
			wDsNum++;

			//BACKRTCP ˫������ͨ�� -> UMS netbuf
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->m_pcDual->m_tVidNetBuf.m_tRcvRtcpAddr;
			atDsData[wDsNum].m_tMapedAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;

		}

		//��Ƶ
		atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptDualAddr->m_tAud.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->m_pcDual->m_tAudRcvAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetDualAudio();
		wDsNum++;

		atDsData[wDsNum].m_tRcvFromAddr = pInst->m_pcDual->m_tAudRcvAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_tDualAudEnc.m_tChanAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;

		for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
		{//�ӻ���ת���壬ת��������ת����
			ptEqp = &pInst->m_atDsEqp[wEqpIndex];
			if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
			{
				continue;
			}
			//ת��������ת����
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptDualAddr->m_tAud.m_tRtpAddr;
			
			atDsData[wDsNum].m_tSndToAddr = pInst->m_pcDual->m_tAudRcvAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetDualAudio();
			++wDsNum;
		}
		
		if ( pInst->IsAudNeedBas())
		{
			TTPDsFrom tAddr;
			pInst->m_pcBas->GetDualAudBasInAddr(tAddr);
			
			//RTP UMS���յ�ַ  -> ˫����Ƶ����ͨ��
			atDsData[wDsNum].m_tRcvFromAddr = pInst->m_pcDual->m_tAudRcvAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetDualAudio();
			wDsNum++;
			
			//BACKRTCP 
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->m_pcDual->m_tAudRcvAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		}
		
	}

	return wDsNum;
}

u16 CNetPortMgr::AdjustBasDsEqpToConfDsEqp(CUmsConfInst* pInst)
{
	u16 wDsNum = 0;

#ifndef _USE_XMPUEQP_

	u8	byIndx = 0;
	CUmsBas* pcBas = pInst->GetBas();
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	//������
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		wDsNum += CNetPortMgr::FindBasDsEqpToConfDsEqp(pInst, pcBas->GetSpeakerBas()->m_atBas[byIndx].m_tBasChnInfo, 
			pInst->GetBas()->GetSpeakerBas()->m_tVidPara.m_byParamNum, atDsData + wDsNum, TRUE);
	}
	//��ϯ
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		wDsNum += CNetPortMgr::FindBasDsEqpToConfDsEqp(pInst, pcBas->GetChairBas()->m_atBas[byIndx].m_tBasChnInfo, 1, atDsData + wDsNum);
	}
	
	//˫��
	wDsNum += CNetPortMgr::FindBasDsEqpToConfDsEqp(pInst, pcBas->GetDualBas()->m_tBas.m_tBasChnInfo, 
												pcBas->GetDualBas()->m_tVidPara.m_byParamNum, atDsData + wDsNum, TRUE);
	
	//����
	for ( byIndx = 0; byIndx < BAS_CHN_RES_MAX_NUM; byIndx ++ )
	{
		if ( !pcBas->GetBasMgr()->m_atBasChsRes[byIndx].IsBasValid() )
		{
			continue;
		}
		
		wDsNum += CNetPortMgr::FindBasDsEqpToConfDsEqp(pInst, pcBas->GetBasMgr()->m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo, 
											pcBas->GetBasMgr()->m_atBasChsRes[byIndx].m_byFormatNum, atDsData + wDsNum);
	}
	
	if( !( pInst->GetBas()->m_tToConfDsEqpDs.GetElementNum() == 0 &&  wDsNum == 0 ) )
	{
		MdlHint(Ums_Mdl_Call, ("AdjustBasDsEqpToConfDsEqp. ConfID:%d, DsNum:%d\n", pInst->GetInsID(), wDsNum));
		MergerDsList(pInst, pInst->GetBas()->m_tToConfDsEqpDs, atDsData, wDsNum, "AdjustBasDsEqpToConfDsEqp");
	}

#endif

	return wDsNum;
}

//��������ת���� �� ����ת����
u16 CNetPortMgr::FindBasDsEqpToConfDsEqp( CUmsConfInst* pInst, TBasChnInfo& tChnInfo, u16 wOutChanNum, TUmsDsData atDsData[], BOOL32 bIsBrd )
{
	u16 wDsNum = 0;
	TEqpRes* ptEqp = NULL;
	TTPTransAddr tDstAddr;
	TTPTransAddr tSrcAddr;

	if( tChnInfo.m_dwMediaNode != INVALID_NODE && pInst->m_tEqpConfDs.IsValid() )
	{
		//ǰ���� bas����ת���� �� ����ת���� BackRtcp
		if( tChnInfo.m_dwMediaNode != pInst->m_tEqpConfDs.m_dwEqpNode )
		{
			//Vid
			tSrcAddr.SetAddr(tChnInfo.m_dwMediaIP, tChnInfo.m_wEqpStartPort + 1);
			tDstAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, tChnInfo.m_wEqpStartPort + 1);
			
			atDsData[wDsNum].m_tRcvFromAddr = tSrcAddr;
			atDsData[wDsNum].m_tSndToAddr = tDstAddr;
			atDsData[wDsNum].m_dwEqpNode = tChnInfo.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
			
			//Aud
			tSrcAddr.SetAddr(tChnInfo.m_dwMediaIP, tChnInfo.m_wEqpStartPort + 3);
			tDstAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, tChnInfo.m_wEqpStartPort + 3);
			
			atDsData[wDsNum].m_tRcvFromAddr = tSrcAddr;
			atDsData[wDsNum].m_tSndToAddr = tDstAddr;
			atDsData[wDsNum].m_dwEqpNode = tChnInfo.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		//������ bas����ת���� �� ����ת���� Rtp  �㲥��ת�������л���ת����
		for (u16 wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
		{//�ӻ���ת���壬ת��������ת����
			ptEqp = &pInst->m_atDsEqp[wEqpIndex];
			
			if (!ptEqp->IsValid() || ptEqp->m_dwEqpNode == tChnInfo.m_dwMediaNode)
			{
				continue;
			}
			
			if ( !bIsBrd && ptEqp->m_dwEqpNode != pInst->m_tEqpConfDs.m_dwEqpNode )
			{//�㲥 ��������ת���壬 ����ת������ת����
				continue;
			}

			for ( u16 wIndx = 0; wIndx < wOutChanNum; wIndx ++ )
			{
				//Vid
				tDstAddr.SetAddr(ptEqp->m_dwEqpIp, tChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN);
				tSrcAddr.SetAddr(tChnInfo.m_dwMediaIP, tChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN);
				
				atDsData[wDsNum].m_tRcvFromAddr = tSrcAddr;
				atDsData[wDsNum].m_tSndToAddr = tDstAddr;
				atDsData[wDsNum].m_dwEqpNode = tChnInfo.m_dwMediaNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetBasVideo();
				++wDsNum;
			}

			//Aud
			tDstAddr.SetAddr(ptEqp->m_dwEqpIp, tChnInfo.m_wUmsStartPort + 2);
			tSrcAddr.SetAddr(tChnInfo.m_dwMediaIP, tChnInfo.m_wUmsStartPort + 2);
			
			atDsData[wDsNum].m_tRcvFromAddr = tSrcAddr;
			atDsData[wDsNum].m_tSndToAddr = tDstAddr;
			atDsData[wDsNum].m_dwEqpNode = tChnInfo.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetBasAudio();
			++wDsNum;
		}
	}

	return wDsNum;
}

void CNetPortMgr::MergerDsList(CUmsConfInst* pInst, CDsListInfo& cDsList, TUmsDsData aNewDsData[MAX_CHANNEL_DS_NUM], u16 wDsNumm, s8* pszDstDes)
{
	CDsListInfo tListInfo;
	tListInfo.SetMediaTrans(aNewDsData, wDsNumm, CUmsConfInst::m_pcCallDs);

	//add by fjs
// 	static BOOL bInit = CDsPortPool::GetInstance()->Init();
// 	CDsPortPool::GetInstance()->AddDs( pInst->GetInsID() , aNewDsData, wDsNumm );
	//
	
	u16 wAddDsNum = 0;
	TUmsDsData tAddDsData[MAX_CHANNEL_DS_NUM];
	
	u16 wDelDsNum = 0;
	TUmsDsData tDelDsData[MAX_CHANNEL_DS_NUM];
	
	CDsListInfo tDelList;
	CDsListInfo tRepeatList;
	cDsList.Merger(tListInfo, tDelList, tRepeatList, tAddDsData, wAddDsNum);
	
	tDelList.GetMediaTrans(tDelDsData, wDelDsNum);

	MdlHint(Ums_Mdl_Media, ("[%s]MergerDsList! ConfID:%d, wDsNumm:%d, DelNum:%d, AddNum:%d\n"
		, pszDstDes, pInst->GetInsID(), wDsNumm, wDelDsNum, wAddDsNum));

	DestroyMediaTrans(pInst, tDelDsData, wDelDsNum);
	
	CUmsConfInst::m_pcCallDs->FreeBuff(tDelList.GetHead());
	CUmsConfInst::m_pcCallDs->FreeBuff(tRepeatList.GetHead());

	//add by fjs
//	CDsPortPool::GetInstance()->DelDs( pInst->GetInsID() , tDelList.GetHead() );
	
	CreateMediaTrans(pInst, tAddDsData, wAddDsNum);
}

u16 CNetPortMgr::CreateMediaForVRS2S( CUmsConfInst* pInst, TCapNode* ptVRS, TCapNode* ptNodeSrc )
{
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wCurIndex = MIDSCREENINDEX;
	s32 symbolflag = 1;
	u16 wIndex = 0;
	for (wIndex = 1; wIndex <= ptVRS->m_wVidRcvNum; ++wIndex, symbolflag *= -1)
	{
		wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
		atDsData[wDsNum].m_tRcvFromAddr = ptNodeSrc->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptVRS->m_tRmtChan.m_atVidDec[wCurIndex].m_tChanAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptNodeSrc->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetVideo(wCurIndex);
		++wDsNum;
		atDsData[wDsNum].m_tRcvFromAddr = ptVRS->m_tRmtChan.m_atVidEnc[wCurIndex].m_tChanAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptNodeSrc->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtcpForSnd;
		atDsData[wDsNum].m_dwEqpNode = ptVRS->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}
	for (wIndex = 1; wIndex <= ptVRS->m_wAudRcvNum; ++wIndex, symbolflag *= -1)
	{
		wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
		atDsData[wDsNum].m_tRcvFromAddr = ptNodeSrc->m_aptChanAddr[wCurIndex]->m_tAud.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptVRS->m_tRmtChan.m_atAudDec[wCurIndex].m_tChanAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptNodeSrc->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetAudio(wCurIndex);
		++wDsNum;
		atDsData[wDsNum].m_tRcvFromAddr = ptVRS->m_tRmtChan.m_atAudEnc[wCurIndex].m_tChanAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptNodeSrc->m_aptChanAddr[wCurIndex]->m_tAud.m_tRtcpForSnd;
		atDsData[wDsNum].m_dwEqpNode = ptVRS->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}
	if ( NULL != ptVRS->m_ptMixAddr && NULL != ptNodeSrc->m_ptMixAddr )
	{
		atDsData[wDsNum].m_tRcvFromAddr = ptNodeSrc->m_ptMixAddr->m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptVRS->m_tRmtChan.m_tAudMixDec.m_tChanAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = ptNodeSrc->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetEPMixAudio();
		++wDsNum;
		atDsData[wDsNum].m_tRcvFromAddr = ptVRS->m_tRmtChan.m_tAudMixDec.m_tChanAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = ptNodeSrc->m_ptMixAddr->m_tRtcpForSnd;
		atDsData[wDsNum].m_dwEqpNode = ptVRS->m_tMediaEqp.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}
	MdlHint(Ums_Mdl_Media, ("CreateMediaForVRS2S! ConfID:%d, vrsEpID:%d, SrcEpID:%d, dsNum:%d", 
				pInst->GetInsID(), ptVRS->m_wEpID, ptNodeSrc->m_wEpID, wDsNum));
	MergerDsList(pInst, ptVRS->m_tDsList, atDsData, wDsNum, "CreateMediaForVRS2S");
	return 0;
}

u16 CNetPortMgr::AdjustDiscussObjToVmpTp(CUmsConfInst* pInst, TDiscussVmpTpRes* pVmpTpRes, TDiscussScreenInfo* ptDstInfo)
{
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wIndex = 0;
	u16 wScreenIndex = 0;
	u16 wAddIndex = 0;
	TServiceAddr tScrAddr;
	TServiceAddr tDstAddr;
	TDiscussEpInfo* pEpInfo = NULL;
	if (NULL == pVmpTpRes->m_pcVmpTpRes)
	{
		return wDsNum;
	}

	do 
	{
		if (!ptDstInfo->IsDstEpValid())
		{
			break;
		}

		pEpInfo = pInst->GetUmsDiscuss()->GetDiscussEpInfoById(ptDstInfo->m_atMember[0].GetHandleOne());		
		if (NULL == pEpInfo || !pEpInfo->IsValid())
		{
			break;
		}

		// ��ͼ����ϳ�����0·
		pInst->GetVmpServiceHandle()->GetRcvChanAddr(tDstAddr, pVmpTpRes->m_pcVmpTpRes, 0);
		pInst->GetUmsDiscuss()->GetDiscussEpVidAddr(pEpInfo->m_wEpID, ptDstInfo->m_atMember[0].GetHandleTwo(), tScrAddr);

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetVideo(ptDstInfo->m_atMember[0].GetHandleTwo());
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = tDstAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
		
	} while (0);

	for (wIndex = 1; wIndex < UMS_VMP_MAX_RCV;)
	{
		if (0 == ptDstInfo->m_atMember[wIndex].m_dwHandle)
		{
			wIndex++;
			continue;
		}

		pEpInfo = pInst->GetUmsDiscuss()->GetDiscussEpInfoById(ptDstInfo->m_atMember[wIndex].GetHandleOne());		
		if (NULL == pEpInfo || !pEpInfo->IsValid())
		{
			wIndex++;
			continue;
		}

		if (pEpInfo->IsThreeScr())
		{
			wAddIndex = 0;
			for (wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; wScreenIndex++)
			{
				wAddIndex = wIndex + wScreenIndex;
				pInst->GetVmpServiceHandle()->GetRcvChanAddr(tDstAddr, pVmpTpRes->m_pcVmpTpRes, wAddIndex);					
				pInst->GetUmsDiscuss()->GetDiscussEpSmallVidAddr(pEpInfo->m_wEpID, wScreenIndex, tScrAddr);

				if (tScrAddr.IsValidAddr() && tDstAddr.IsValidAddr())
				{
					atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowVideo();
					wDsNum++;
					
					atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = tDstAddr.m_dwMediaNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}
			}
		}
		else
		{// ������С����
			pInst->GetVmpServiceHandle()->GetRcvChanAddr(tDstAddr, pVmpTpRes->m_pcVmpTpRes, wIndex);
			pInst->GetUmsDiscuss()->GetDiscussEpSmallVidAddr(pEpInfo->m_wEpID, MIDSCREENINDEX, tScrAddr);
			
			if (tScrAddr.IsValidAddr() && tDstAddr.IsValidAddr())
			{
				atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = tDstAddr.m_dwMediaNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}
		}
		wIndex+=pEpInfo->m_wStrceenNum;
	}

	MergerDsList(pInst, pVmpTpRes->m_cToVmpDsInfo, atDsData, wDsNum, "AdjustDstEpVidToVmpChan");
	return wDsNum;
}

u16 CNetPortMgr::AdjustDiscussObjToMix( CUmsConfInst* pInst, TDiscussMixRes* pMixRes, TAudMixMemberInfo* ptMemberInfo )
{
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TTPMediaTransAddr tDstAddr;
	TServiceAddr tScrAddr;
	TDiscussEpInfo* pEpInfo = NULL;
	if (NULL == pMixRes->m_ptMixRes)
	{
		return wDsNum;
	}

	u16 wOprEpId = 0;
	u16 wScrIndex = 0;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 == ptMemberInfo->m_awEpId[wIndex])
		{
			continue;
		}
		wOprEpId = ptMemberInfo->m_awEpId[wIndex];
		wScrIndex = ptMemberInfo->m_awScrIndx[wIndex];
		// ��������Ա����Ӧ��ϯ���߻�����������������Ƶ����
		pInst->GetEapu()->GetMixerChnInAddr(pMixRes->m_ptMixRes, tDstAddr, wOprEpId, wScrIndex);			
		pInst->GetUmsDiscuss()->GetDiscussEpAudAddr(wOprEpId, wScrIndex, tScrAddr);

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}
	
	MergerDsList(pInst, pMixRes->m_cToMixDsInfo, atDsData, wDsNum, "AdjustDiscussObjToMix");
	return wDsNum;
}

u16 CNetPortMgr::AdjustSingleDiscussObjToMix(CUmsConfInst* pInst, BOOL32 bIsAddDualAud)
{
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wDsNum = 0;	
	u16 wIndex = 0;
	TTPMediaTransAddr tDstAddr;
	TServiceAddr tScrAddr;
	TDiscussEpInfo* pEpInfo = NULL;
	TAudMixInfo* pMixRes = pInst->GetSpeaker().m_ptAudMix;
	if (NULL == pMixRes)
	{
		return wDsNum;
	}

	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{
		pEpInfo = pInst->GetUmsDiscuss()->GetDiscussEpInfoByIndex(wIndex);
		if (NULL == pEpInfo || !pEpInfo->IsValid())
		{
			continue;
		}
		
		pInst->GetEapu()->GetMixerChnInAddr(pMixRes, tDstAddr, pEpInfo->m_wEpID, TP_MAX_STREAMNUM);
		pInst->GetUmsDiscuss()->GetDiscussEpAudAddr(pEpInfo->m_wEpID, TP_MAX_STREAMNUM, tScrAddr);

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	if (bIsAddDualAud)
	{
		pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tDstAddr, pInst->GetDualMgr()->GetDualID(), 4);
		//ȡ˫�� ��������
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetDualMgr()->m_tAudRcvAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetDualAudio();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetDualMgr()->m_tAudRcvAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	MergerDsList(pInst, pInst->GetSpeaker().m_tToAudMixDs, atDsData, wDsNum, "AdjustSingleDiscussObjToMix");
	return wDsNum;
}

u16 CNetPortMgr::AdjustSingleDiscussObjToVmpTp( CUmsConfInst* pInst, TDiscussScreenInfo* ptDstInfo )
{
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	u16 wIndex = 0;
	u16 wScreenIndex = 0;
	u16 wAddIndex = 0;
	TServiceAddr tScrAddr;
	TServiceAddr tDstAddr;
	TDiscussEpInfo* pEpInfo = NULL;
	const CBaseService* pVmpRes = pInst->GetSpeaker().m_pcSingleVmp;
	if (NULL == pVmpRes)
	{
		return wDsNum;
	}
	
	do 
	{
		if (!ptDstInfo->IsDstEpValid())
		{
			break;
		}
		
		pEpInfo = pInst->GetUmsDiscuss()->GetDiscussEpInfoById(ptDstInfo->m_atMember[0].GetHandleOne());		
		if (NULL == pEpInfo || !pEpInfo->IsValid())
		{
			break;
		}
		
		// ��ͼ����ϳ�����0·
		pInst->GetVmpServiceHandle()->GetRcvChanAddr(tDstAddr, pVmpRes, 0);
		pInst->GetUmsDiscuss()->GetDiscussEpVidAddr(pEpInfo->m_wEpID, ptDstInfo->m_atMember[0].GetHandleTwo(), tScrAddr);

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetVideo(ptDstInfo->m_atMember[0].GetHandleTwo());
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = tDstAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	
	} while (0);
	
	for (wIndex = 1; wIndex < UMS_VMP_MAX_RCV;)
	{
		if (0 == ptDstInfo->m_atMember[wIndex].m_dwHandle)
		{
			wIndex++;
			continue;
		}
		
		pEpInfo = pInst->GetUmsDiscuss()->GetDiscussEpInfoById((u16)ptDstInfo->m_atMember[wIndex].GetHandleOne());
		if (NULL == pEpInfo || !pEpInfo->IsValid())
		{
			wIndex++;
			continue;
		}
		
		if (pEpInfo->IsThreeScr())
		{
			wAddIndex = 0;
			for (wScreenIndex = 0; wScreenIndex < TP_MAX_STREAMNUM; wScreenIndex++)
			{
				wAddIndex = wIndex + wScreenIndex;
				pInst->GetVmpServiceHandle()->GetRcvChanAddr(tDstAddr, pVmpRes, wAddIndex);					
				pInst->GetUmsDiscuss()->GetDiscussEpSmallVidAddr(pEpInfo->m_wEpID, wScreenIndex, tScrAddr);
				
				if (tScrAddr.IsValidAddr() && tDstAddr.IsValidAddr())
				{
					atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowVideo();
					wDsNum++;
					
					atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = tDstAddr.m_dwMediaNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}
			}
		}
		else
		{// ������С����
			pInst->GetVmpServiceHandle()->GetRcvChanAddr(tDstAddr, pVmpRes, wIndex);
			pInst->GetUmsDiscuss()->GetDiscussEpSmallVidAddr(pEpInfo->m_wEpID, MIDSCREENINDEX, tScrAddr);
			
			if (tScrAddr.IsValidAddr() && tDstAddr.IsValidAddr())
			{
				atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = pVmpRes->GetMediaNode();
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}
		}
		wIndex+=pEpInfo->m_wStrceenNum;
	}
	
	MergerDsList(pInst, pInst->GetSpeaker().m_tToVmpDs, atDsData, wDsNum, "AdjustSingleDiscussObjToVmpTp");
	return wDsNum;
}


u16 CNetPortMgr::AdjustDiscussEpToBas(CUmsConfInst* pInst, TDiscussEpInfo* pEpInfo)
{
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TTPMediaTransAddr tDstAddr;
	TServiceAddr      tScrAddr;

	s32 symbolflag = 1;
	u16 wCurIndex = 0;
	for (u16 wIndex = 1; wIndex <= pEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
	{// 
		wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

		if (NULL != pEpInfo->m_apcBas[wCurIndex])
		{
			pInst->GetBas()->GetInChnVidAddr(tDstAddr, pEpInfo->m_apcBas[wCurIndex]);
			pInst->GetUmsDiscuss()->GetDiscussEpVidAddr(pEpInfo->m_wEpID, wCurIndex, tScrAddr);

			atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wCurIndex);
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;

		}
	}

	MergerDsList(pInst, pEpInfo->m_cToBasDsInfo, atDsData, wDsNum, "AdjustDiscussEpToBas");
	return wDsNum;
}

u16 CNetPortMgr::PutAudDownToDiscussEp(CUmsConfInst* pInst, TCallNode* ptNode, TDiscussEpAudInfo* ptEpAudInfo)
{
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TServiceAddr tScrAddr;
	TDiscussEpInfo* ptEpInfo = pInst->GetUmsDiscuss()->GetDiscussEpInfoById(ptNode->m_wEpID);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{
		return wDsNum;
	}

	u16 wIndex = 0;
	BOOL32 bIsSpeaciaEp = ptNode->m_wEpID == pInst->GetUmsDiscuss()->GetSpeacialEp();
	if (ptEpInfo->IsThreeScr())
	{
		if (bIsSpeaciaEp || ptNode->m_wEpID == pInst->curSpeakerID())
		{
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				pInst->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSpeakerEp, wIndex, ptEpInfo->m_wEpID, FALSE, tScrAddr, TRUE);
				
				if (!tScrAddr.IsValidAddr())
				{
					ptEpAudInfo->AddEp(ptNode->m_wLowChildEpID, wIndex);
				}
				else
				{
					atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptEpInfo->m_atPutAuddr[wIndex].m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowAudio();
					wDsNum++;
					
					atDsData[wDsNum].m_tRcvFromAddr = ptEpInfo->m_atPutAuddr[wIndex].m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}
			}
		}
		else
		{
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				pInst->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForThreeScrEp, wIndex, ptEpInfo->m_wEpID, FALSE, tScrAddr, TRUE);
				
				if (!tScrAddr.IsValidAddr())
				{
					ptEpAudInfo->AddEp(ptNode->m_wLowChildEpID, wIndex);
				}
				else
				{
					atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptEpInfo->m_atPutAuddr[wIndex].m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowAudio();
					wDsNum++;
					
					atDsData[wDsNum].m_tRcvFromAddr = ptEpInfo->m_atPutAuddr[wIndex].m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}
			}
		}
	}
	else
	{
		pInst->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSingleScrEp, TP_MAX_STREAMNUM, ptEpInfo->m_wEpID, FALSE, tScrAddr, TRUE);

		if (!tScrAddr.IsValidAddr())
		{
			ptEpAudInfo->AddEp(ptNode->m_wLowChildEpID, MIDSCREENINDEX);
		}
		else
		{
			atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		}
	}
	
	tpHint(Ums_Mdl_Call, "[PutAudDownToDiscussEp] ConfId:%d, Ep:%d, wDsNum:%d.\n", pInst->GetInsID(), ptEpInfo->m_wEpID, wDsNum);

	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{
		if (0 == ptEpAudInfo->m_awDiscussEpId[wIndex])
		{
			break;
		}
		
		tpHint(Ums_Mdl_Call, "  [%d] EpId:%d, IsRcvNMode(%d,%d,%d).\n", wIndex, ptEpAudInfo->m_awDiscussEpId[wIndex],
			ptEpAudInfo->m_abyIsRcvNModeAud[wIndex][0], ptEpAudInfo->m_abyIsRcvNModeAud[wIndex][1],
			ptEpAudInfo->m_abyIsRcvNModeAud[wIndex][2]);
	}

	MergerDsList(pInst, ptEpInfo->m_cToPutAuddrDsInfo, atDsData, wDsNum, "PutAudDownToDiscussEp");
	return wDsNum;
}

u16 CNetPortMgr::CreatPutAudRtpToDown( CUmsConfInst* pInst, TPutAudChnl* ptAudChnl )
{	//���� ptPutAud->m_aptLocalAddr->m_tRtpAddr �� ptPutAud->m_atRmtAddr->m_tRtpAddr
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(ptAudChnl->m_wEpID);
	if (NULL == ptNode)
	{
		return wDsNum;
	}
	
	ForEachChanList(ptNode->m_wAudRcvNum,
		atDsData[wDsNum].m_tRcvFromAddr = ptAudChnl->m_aptLocalAddr[ewIndex]->m_tRtpAddr;\
		atDsData[wDsNum].m_tSndToAddr = ptAudChnl->m_atRmtAddr[ewIndex].m_tRtpAddr;\
		atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
			)

	MergerDsList(pInst, ptAudChnl->m_tDs, atDsData, wDsNum, "CreatPutAudRtpToDown");
	return wDsNum;
}

u16 CNetPortMgr::CreatPutAudBackRtpToUp( CUmsConfInst* pInst, TPutAudChnl* ptAudChnl )
{	//���� ptPutAud->m_aptLocalAddr->m_tBackRtcpAddr  �� ptPutAud->m_atRmtAddr[wIndex].m_tBackRtcpAddr
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(ptAudChnl->m_wEpID);
	if (NULL == ptNode)
	{
		return wDsNum;
	}

	ForEachChanList(ptNode->m_wAudRcvNum,
		atDsData[wDsNum].m_tRcvFromAddr = ptAudChnl->m_aptLocalAddr[ewIndex]->m_tBackRtcpAddr;\
		atDsData[wDsNum].m_tSndToAddr = ptAudChnl->m_atRmtAddr[ewIndex].m_tBackRtcpAddr;\
		atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
	    wDsNum++;
			)

	MergerDsList(pInst, ptAudChnl->m_tDs, atDsData, wDsNum, "CreatPutAudBackRtpToUp");
	return wDsNum;
}

u16 CNetPortMgr::GetDiscussObjToVirSpeaker( CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs )
{// ����ģʽ�£��㲥��������Ŀ�������ⷢ���ˣ���ȥ����3·�ϳ�; �Լ�3·nģʽ��������ʽѡ���Ի᳡���͸�ʽ����
//  �㲥��������ȥ����һ·�ϳɣ���ʽѡ���Ի᳡���͸�ʽ�����ϼ��㲥������������ֱ�Ӵӻ�����ȡ
	u16 wDsNum = 0;	
	u16 wIndex = 0;
	TServiceAddr tAddr;

	TCallNode* ptCurSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->curSpeakerID());
	TCapNode* ptCurForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptCurSpeaker);

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{// �㲥������3·�ϳ�

		if(	pInst->GetVmp()->IsBrdVmp() && wIndex == MIDSCREENINDEX )
		{//�ϳɹ㲥���������м��� ���պϳɹ㲥
			if (NULL == ptCurSpeaker || NULL == ptCurForether)
			{
				continue;
			}
			TTPDsFrom tAddr;
			pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr, ptCurForether->m_tVidSndFormat.m_tFormat, TRUE);
			
			atDstas[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDstas[wDsNum].m_emSwitchType = emRtpSwap;
			atDstas[wDsNum].SetVmpVideo();
			++wDsNum;
			
			atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tBackRtcpAddr;
			atDstas[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;;
			atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
			continue;
		}

		pInst->GetUmsDiscuss()->GetObjVmpOutAddr(emDiscussObjForThreeScrEp, wIndex, tAddr);
		pInst->GetSpeakerVidDec(wIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
		
		atDstas[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
		atDstas[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetVmpVideo();
		wDsNum++;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tBackRtcpAddr;
		atDstas[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	// �����¹㲥������һ·
	if (NULL != pInst->GetSpeaker().m_pcSingleVmp)
	{
		pInst->GetUmsDiscuss()->GetObjVmpOutAddr(emDiscussObjForSingleScrEp, MIDSCREENINDEX, tAddr);
		pInst->GetSingleVidDec().SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
		atDstas[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDstas[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetVmpVideo();
		wDsNum++;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
		atDstas[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	do 
	{
		if (NULL == ptCurSpeaker || NULL == ptCurForether)
		{
			break;
		}


		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{// 3·nģʽ����

			pInst->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForThreeScrEp, wIndex, ptCurSpeaker->m_wEpID, TRUE, tAddr);
			pInst->GetSpeakerAudDec(wIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);

			atDstas[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
			atDstas[wDsNum].m_emSwitchType = emRtpSwap;
			atDstas[wDsNum].SetEQPMixNVideo();
			wDsNum++;

			atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tBackRtcpAddr;
			atDstas[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
			atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		}

		// ����˫����nģʽ����
		pInst->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSingleScrEp, TP_MAX_STREAMNUM, ptCurSpeaker->m_wEpID, TRUE, tAddr);
		
		atDstas[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDstas[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetEQPMixNVideo();
		++wDsNum;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		atDstas[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;


	} while (0);

	u16 wEqpIndex = 0;
	TEqpRes* ptEqp = NULL;
	
	//�ӻ���ת���壬ת��������ת����
	for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
	{
		ptEqp = &pInst->m_atDsEqp[wEqpIndex];
		if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
		{
			MdlLowHint(Ums_Mdl_Call, ("GetDiscussObjToVirSpeaker Valid:%d, EpIndex:%d, ConfIndex:%d.\n",
				ptEqp->IsValid(), ptEqp->m_wEqpIndex,
				pInst->m_tEqpConfDs.m_wEqpIndex));
			continue;
		}		
		MdlLowHint(Ums_Mdl_Call, ("GetDiscussObjToVirSpeaker.\n"));
		//ת��������ת����
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDstas[wDsNum].m_emSwitchType = emRtpSwap;
			atDstas[wDsNum].SetUnknowVideo();
			++wDsNum;

			atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDstas[wDsNum].m_emSwitchType = emRtpSwap;
			atDstas[wDsNum].SetUnknowAudio();
			++wDsNum;
		}

		//�������
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetUnknowVideo();
		++wDsNum;
		

		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;		
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetUnknowAudio();
		++wDsNum;
	}

	MdlHint(Ums_Mdl_Call, ("GetDiscussObjToVirSpeaker DsNum:%d.\n", wDsNum));
	return wDsNum;
}

u16 CNetPortMgr::GetDisCussObjToVirSpeakerForDown( CUmsConfInst* pInst, TUmsDsData atDstas[], u16 wMaxDs )
{// ����ģʽ�£��¼������ⷢ���˵ģ��Ǵ��ϼ������ģ��㲥��������3·��Ƶ��3·��Ƶ���Լ��㲥��������1·��Ƶ��1·��Ƶ
	u16 wDsNum = 0;	
	u16 wIndex = 0;

	TCapNode* ptCaller = pInst->GetNodeMgr()->GetCaller();
	if (NULL == ptCaller)
	{
		return wDsNum;
	}

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{// �㲥������3·��Ƶ

		atDstas[wDsNum].m_tRcvFromAddr = ptCaller->m_aptChanAddr[wIndex]->m_tVid.m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
		atDstas[wDsNum].m_dwEqpNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetVideo(wIndex);
		++wDsNum;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tBackRtcpAddr;
		atDstas[wDsNum].m_tSndToAddr = ptCaller->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForSnd;
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;

		// �㲥������3·��Ƶ
		atDstas[wDsNum].m_tRcvFromAddr = ptCaller->m_aptChanAddr[wIndex]->m_tAud.m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
		atDstas[wDsNum].m_dwEqpNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetAudio(wIndex);
		++wDsNum;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tBackRtcpAddr;
		atDstas[wDsNum].m_tSndToAddr = ptCaller->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForSnd;
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;
	}

	if (NULL != ptCaller->m_ptCasCadeChairAddr)
	{
		// �㲥��������Ƶ
		atDstas[wDsNum].m_tRcvFromAddr = ptCaller->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDstas[wDsNum].m_dwEqpNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetUnknowVideo();
		wDsNum++;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
		atDstas[wDsNum].m_tSndToAddr = ptCaller->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tBackRtcpAddr; 
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;

		// �㲥��������Ƶ�����ϼ���������nģʽ������˫����������
		atDstas[wDsNum].m_tRcvFromAddr = ptCaller->m_ptCasCadeChairAddr->m_tDisSingleAud.m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDstas[wDsNum].m_dwEqpNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetUnknowAudio();
		wDsNum++;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		atDstas[wDsNum].m_tSndToAddr = ptCaller->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleAud.m_tChanAddr.m_tBackRtcpAddr; 
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	u16 wEqpIndex = 0;
	TEqpRes* ptEqp = NULL;
	
	//�ӻ���ת���壬ת��������ת����
	for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
	{
		ptEqp = &pInst->m_atDsEqp[wEqpIndex];
		if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
		{
			MdlLowHint(Ums_Mdl_Call, ("GetDisCussObjToVirSpeakerForDown Valid:%d, EpIndex:%d, ConfIndex:%d.\n",
				ptEqp->IsValid(), ptEqp->m_wEqpIndex,
				pInst->m_tEqpConfDs.m_wEqpIndex));
			continue;
		}		
		MdlLowHint(Ums_Mdl_Call, ("GetDisCussObjToVirSpeakerForDown.\n"));
		//ת��������ת����
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDstas[wDsNum].m_emSwitchType = emRtpSwap;
			atDstas[wDsNum].SetUnknowVideo();
			++wDsNum;

			atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDstas[wDsNum].m_emSwitchType = emRtpSwap;
			atDstas[wDsNum].SetUnknowAudio();
			++wDsNum;
		}

		//�������
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetUnknowVideo();
		++wDsNum;
		
		atDstas[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;		
		atDstas[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDstas[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDstas[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDstas[wDsNum].m_emSwitchType = emRtpSwap;
		atDstas[wDsNum].SetUnknowAudio();
		++wDsNum;
	}

	MdlHint(Ums_Mdl_Call, ("GetDisCussObjToVirSpeakerForDown DsNum:%d.\n", wDsNum));
	return wDsNum;
}

u16 CNetPortMgr::CreateAllMemberToBrdVmp( CUmsConfInst* pInst, TBrdVmpRes* ptVmpRes )
{
	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	TTPMediaTransAddr tDstAddr;
	TBrdVmpMember* ptMember = NULL;
	for ( u16 wIndex = 0; wIndex < ptVmpRes->m_wMemberNum; wIndex ++ )
	{
		if ( !ptVmpRes->m_atMember[wIndex].IsDs() )
		{
			continue;
		}

		ptMember = &ptVmpRes->m_atMember[wIndex];

		pInst->GetVmp()->GetBrdVmpInAddr(ptVmpRes, tDstAddr, wIndex);

		if (ptMember->m_tVmpMember.IsDual())
		{// ��˫������
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetDualMgr()->m_tVidRcvAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetDualVideo();
			wDsNum++;

			atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetDualMgr()->m_tVidNetBuf.m_tRcvRtpAddr;
			atDsData[wDsNum].m_tMapedAddr = tDstAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;
		}
		else if (ptMember->IsVidGet())
		{//���Ƚӿ�ȡ�õ�������
			//��������
			if (ptMember->IsSmallVid())
			{// С�������ϳ�
				atDsData[wDsNum].m_tRcvFromAddr = ptMember->m_tGetAddr.m_atSmallAddr[MIDSCREENINDEX].m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptMember->m_tGetAddr.m_dwMedia;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetSmallVideo(MIDSCREENINDEX);
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptMember->m_tGetAddr.m_atSmallAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptMember->m_tGetAddr.m_dwMedia;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;

			}
			else
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptMember->m_tGetAddr.m_atVidAddr[MIDSCREENINDEX].m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptMember->m_tGetAddr.m_dwMedia;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(MIDSCREENINDEX);
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptMember->m_tGetAddr.m_atVidAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptMember->m_tGetAddr.m_dwMedia;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}
		}
		else
		{
			continue;
		}
	}

	MergerDsList(pInst, ptVmpRes->m_tDsToVmp, atDsData, wDsNum, "CreateAllMemberToBrdVmp");

	MdlHint(Ums_Mdl_Call, ("CreateAllMemberToBrdVmp DsNum:%d.\n", wDsNum));

	return wDsNum;
}

void CNetPortMgr::AdjustPollTransToUms( CUmsConfInst* pInst )
{
	TPollAddrEx* ptCruAddr = pInst->GetPollMgr()->GetCurAddr();
	TPollAddrEx* ptOldAddr = pInst->GetPollMgr()->GetOldAddr();

	s32 symbolflag = 1;
	u16 wCurIndex = 0;
	u16 wIndex = 1;

	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

//������ƽ�����
	TCallNode* ptPoll = pInst->GetNodeMgr()->GetNode(ptCruAddr->m_wPollEpID);
	TCapNode* ptPollCap = pInst->GetNodeMgr()->GetForeFatherNode(ptPoll);
	if ( NULL != ptPoll && NULL != ptPollCap )
	{
		for ( wIndex = 1; wIndex <= ptPoll->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
			if( NULL == ptCruAddr->m_aptLocalAddr[wCurIndex] )
			{
				continue;
			}

			if ( ptPollCap == ptPoll )
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptPollCap->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptCruAddr->m_aptLocalAddr[wCurIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptPollCap->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wCurIndex);
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptLocalAddr[wCurIndex]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptPollCap->m_tRmtChan.m_atVidEnc[wCurIndex].m_tChanAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;

				if ( NULL != ptPollCap->m_aptSmallChanAddr[wCurIndex] )
				{
					atDsData[wDsNum].m_tRcvFromAddr = ptPollCap->m_aptSmallChanAddr[wCurIndex]->m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptCruAddr->m_aptSmallAddr[wCurIndex]->m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptPollCap->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetSmallVideo(wCurIndex);
					wDsNum++;
					
					atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptSmallAddr[wCurIndex]->m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptPollCap->m_tRmtChan.m_atSmallVidEnc[wCurIndex].m_tChanAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}

			}
			else
			{//�� �¼� rtcp
				atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptLocalAddr[wCurIndex]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptCruAddr->m_atRmtRtcp[wCurIndex];
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;

				if ( ptCruAddr->m_atSmallRmtRtcp[wCurIndex].GetPort() != 0 )
				{
					atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptSmallAddr[wCurIndex]->m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptCruAddr->m_atSmallRmtRtcp[wCurIndex];
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}
			}

			if ( !pInst->IsChairConf() )
			{//�¼� �������ϼ����յ�ַ
				atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptLocalAddr[wCurIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetPollMgr()->GetUpRtp(wCurIndex);
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				wDsNum++;

				if ( pInst->GetPollMgr()->GetSmallUpRtp(wCurIndex).GetPort() != 0 )
				{
					atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptSmallAddr[wCurIndex]->m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = pInst->GetPollMgr()->GetSmallUpRtp(wCurIndex);
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowVideo();
					wDsNum++;
				}
			}
		}
	}

	TCallNode* ptPollOld = pInst->GetNodeMgr()->GetNode(ptOldAddr->m_wPollEpID);
	ptPollCap = pInst->GetNodeMgr()->GetForeFatherNode(ptPollOld);
	if ( NULL != ptPollOld && NULL != ptPollCap )
	{
		for ( wIndex = 1; wIndex <= ptPollOld->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

			if( NULL == ptOldAddr->m_aptLocalAddr[wCurIndex] )
			{
				continue;
			}

			if ( ptPollCap == ptPollOld )
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptPollCap->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptOldAddr->m_aptLocalAddr[wCurIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptPollCap->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVideo(wCurIndex);
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptOldAddr->m_aptLocalAddr[wCurIndex]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptPollCap->m_tRmtChan.m_atVidEnc[wCurIndex].m_tChanAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}
			else
			{
				atDsData[wDsNum].m_tRcvFromAddr = ptOldAddr->m_aptLocalAddr[wCurIndex]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptOldAddr->m_atRmtRtcp[wCurIndex];
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}

			if ( !pInst->IsChairConf() && pInst->GetPollMgr()->GetIframeCheck().m_abInCheck[wCurIndex] )
			{//�¼� �������ϼ����յ�ַ �йؼ�֡��� ��ת��
				atDsData[wDsNum].m_tRcvFromAddr = ptOldAddr->m_aptLocalAddr[wCurIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetPollMgr()->GetUpRtp(wCurIndex);
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				wDsNum++;
			}
		}
	}

//�ϼ���������ϯ���ս��
	if( pInst->IsChairConf() )
	{
		TTPMediaTransAddr tAddr;
		u32	dwEqpNode;

		if ( NULL != pInst->GetPollMgr()->GetVmp() )
		{//�кϳ��� ȷ��������ϯ ����ͼ��
			TServiceAddr tSerAddr;
			CUmsConfInst::GetVmpServiceHandle()->GetRcvChanAddr(tSerAddr, pInst->GetPollMgr()->GetVmp(), 0);
			
			tAddr = tSerAddr.m_tAddr;
			dwEqpNode = tSerAddr.m_dwMediaNode;

			if ( ptCruAddr->IsValid() )
			{
				//cur addr
				atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptLocalAddr[ptPoll->GetSpeaker()]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptCruAddr->m_aptLocalAddr[ptPoll->GetSpeaker()]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}

			//old
			if ( ptOldAddr->IsValid() )
			{
				if ( NULL != ptPollOld && pInst->GetPollMgr()->GetIframeCheck().m_abInCheck[ptPollOld->GetSpeaker()] )
				{
					atDsData[wDsNum].m_tRcvFromAddr = ptOldAddr->m_aptLocalAddr[ptPollOld->GetSpeaker()]->m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowVideo();
					wDsNum++;
				}
			}

			if ( ptPoll->IsThreeVidSnd() )
			{
				for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
				{
					if (NULL == ptCruAddr->m_aptSmallAddr[wIndex])
					{
						continue;
					}

					CUmsConfInst::GetVmpServiceHandle()->GetRcvChanAddr(tSerAddr, pInst->GetPollMgr()->GetVmp(), wIndex+1);
					
					tAddr = tSerAddr.m_tAddr;
					dwEqpNode = tSerAddr.m_dwMediaNode;

					//cur addr
					atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptSmallAddr[wIndex]->m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowVideo();
					wDsNum++;
					
					atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptCruAddr->m_aptSmallAddr[wIndex]->m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					wDsNum++;
				}
			}	
		}
		else
		{//�޺ϳ���
			//˳������Ϊ���ϳɡ����䡢������ϯ���ս��   ����ǽ��ϳɣ�������Сͼ��
			for ( wIndex = 1; wIndex <= ptPoll->m_wVidSndNum; ++wIndex, symbolflag *= -1)
			{
				wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
				if(!pInst->GetPollMgr()->GetLocalPollInAddr(tAddr, dwEqpNode, wCurIndex, ptPoll->GetSpeaker()))
				{
					continue;
				}
				
				if ( !ptCruAddr->IsValid() )
				{
					continue;
				}
				
				//cur addr
				atDsData[wDsNum].m_tRcvFromAddr = ptCruAddr->m_aptLocalAddr[wCurIndex]->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptCruAddr->m_aptLocalAddr[wCurIndex]->m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
				
				//old
				if ( !ptOldAddr->IsValid() )
				{
					continue;
				}
				
				if ( pInst->GetPollMgr()->GetIframeCheck().m_abInCheck[wCurIndex] )
				{
					atDsData[wDsNum].m_tRcvFromAddr = ptOldAddr->m_aptLocalAddr[wCurIndex]->m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = tAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowVideo();
					wDsNum++;
				}
			}
		}
	}

	MergerDsList(pInst, pInst->GetPollMgr()->GetPollDs(), atDsData, wDsNum, "AdjustPollTransToUms");
	
	return ;
}

u16 CNetPortMgr::GetNonSpeakerToVirSpeaker( CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs)
{ 
	TCallNode* ptCurSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->curSpeakerID());		
	if (NULL == ptCurSpeaker)
	{
		MdlHint(Ums_Mdl_Call, ("GetNonSpeakerToVirSpeaker speaker epid error. confID:%d, curEp:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID()));
		return 0;
	}

	MdlHint(Ums_Mdl_Call, ("GetNonSpeakerToVirSpeaker speaker not on line. confID:%d, curEp:%d\n"
		                    , pInst->GetInsID(), pInst->curSpeakerID()));

	u16 wDsNum = 0;
	u16 wEqpIndex = 0;
	u32 dwConfNode = pInst->m_tEqpConfDs.m_dwEqpNode;
	TEqpRes* ptEqp = NULL;

	

	if (!pInst->GetSpeakMediaFmt().IsSpeakMediaFmtValid())
	{
		MdlHint(Ums_Mdl_Call, ("GetNonSpeakerToVirSpeaker  speakermediafmt not init . confID:%d\n", pInst->GetInsID()));
	    return wDsNum;
	}

    TUmsVidFormat  tSaveSpeakerSndVidFmt;
    TUmsAudFormat  tSaveSpeakerSndAudFmt;
    pInst->GetSpeakMediaFmt().GetSpeakerSndVidFmt(tSaveSpeakerSndVidFmt);
    pInst->GetSpeakMediaFmt().GetSpeakerSndAudFmt(tSaveSpeakerSndAudFmt);

	if ( !ptCurSpeaker->IsChanOn())
	{ //��ǰ�����˲����� ɾ�����н���
		MdlHint(Ums_Mdl_Call, ("GetNonSpeakerToVirSpeaker speaker stat error. confID:%d, curEp:%d, NewEp:%d, curEpStat:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->oldSpeakerID(), ptCurSpeaker->IsChanOn()));		


	    if(	pInst->GetVmp()->IsBrdVmp())
		{ //33//�ϳɹ㲥���������м��� ���պϳɹ㲥
			TTPDsFrom tAddr;
			pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr,  tSaveSpeakerSndVidFmt, TRUE);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(MIDSCREENINDEX).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVmpVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(MIDSCREENINDEX).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
			
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVmpVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		    ++wDsNum;
		}


    	if (pInst->GetAudMix()->IsAudMixMode())
		{
			TServiceAddr tAddr;
			pInst->GetAudMix()->GetMixNModeRcvAddr(tSaveSpeakerSndAudFmt, tAddr, FALSE);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
			
			
			if (pInst->IsChairConf() && pInst->GetDualMgr()->IsStart() &&  pInst->GetSpeaker().m_bIsDualMixOn)
			{
				pInst->GetDualMgr()->AdjustDualMixForConfAudMix();// ��Ҫ����
				
				//�����������֮���ٿ�˫����Ӧ����PUT ������Ƶ
				pInst->GetAudMix()->PutAudDown();
			}
			
			pInst->GetAudMix()->GetMixNModeRcvAddr(tSaveSpeakerSndAudFmt, tAddr, TRUE);
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
	    	++wDsNum;
		}

	    for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
		{//�ӻ���ת���壬ת��������ת����

			ptEqp = &pInst->m_atDsEqp[wEqpIndex];
			if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
			{
				MdlLowHint(Ums_Mdl_Call, ("GetNonSpeakerToVirSpeaker Valid:%d, EpIndex:%d, ConfIndex:%d.\n",
					ptEqp->IsValid(), ptEqp->m_wEqpIndex,
					pInst->m_tEqpConfDs.m_wEqpIndex));
				continue;
			}
			
			for( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			{
				atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
				atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
				atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowAudio();
				++wDsNum;
			}
			
			//�������
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;		
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
		}

    }

	return wDsNum;

}

//netbuf

//////////////B5 ����/////////////////

u16 CNetPortMgr::AdjustRollCallObjToMix(CUmsConfInst* pInst, TRollCallMixRes* pMixRes, TAudMixMemberInfo* ptMemberInfo)
{
	u16	wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TTPMediaTransAddr tDstAddr;
	TServiceAddr tScrAddr;
	TRollCallEpInfo* pEpInfo = NULL;
	if (NULL == pMixRes->m_ptMixRes)
	{
		return wDsNum;
	}

	u16 wOprEpId = 0;
	u16 wScrIndex = 0;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 == ptMemberInfo->m_awEpId[wIndex])
		{
			continue;
		}
		wOprEpId = ptMemberInfo->m_awEpId[wIndex];
		wScrIndex = ptMemberInfo->m_awScrIndx[wIndex];
		// ��������Ա����Ӧ��ϯ���߻�����������������Ƶ����
		pInst->GetEapu()->GetMixerChnInAddr(pMixRes->m_ptMixRes, tDstAddr, wOprEpId, wScrIndex);			
		pInst->GetRollCallMgr()->GetRollCallEpAudAddr(wOprEpId, wScrIndex, tScrAddr);
		
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}
	
	MergerDsList(pInst, pMixRes->m_cToMixDsInfo, atDsData, wDsNum, "AdjustRollCallObjToMix");

	return wDsNum;
}

void  CNetPortMgr::AdjustRollCallerToBas(CUmsConfInst* pInst)
{
    u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();
    
	TCallNode* ptRollCallerNode = pInst->m_pcNodeMgr->GetNode(wRollCaller);
	TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(wRollCaller);
	
	TCapNode* ptCallerCapNode = pInst->m_pcNodeMgr->GetCapsetNode(wRollCaller);

	TTPTransAddr atRollCallerRtp[TP_MAX_STREAMNUM];
	TTPTransAddr atRollCallerRtcp[TP_MAX_STREAMNUM];
	u32 adwRtpEqpNode[TP_MAX_STREAMNUM] = {0};

    TVirCallerAddr *pVirRollCaller = NULL;

	u16 wDsNum = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];


	s32 symbolflag = 1;
	u16 wChanIndex = 0;
	u16 wIndex  = 0;


	do
	{
		if ( pInst->GetBas()->IsChairInBas() )
		{//��ϯ��Ҫ����������ˣ���������Ҫ�������������)
			
			if(pInst->IsChairConf())
			{  // �ϼ��ǽ�����������˵���ϯbas �Ľ���
				
				if ( NULL == ptRollCallerNode ||  NULL == ptFartherNode )
				{
					MdlError(Ums_Mdl_Call, ("AdjustRollCallerToBas. confID:%d RollCallernode:%p  RollCallerFar:%p  is NULL.\n", 
						    pInst->GetInsID(), ptRollCallerNode, ptFartherNode));
					break;
				}
				
				if(!ptRollCallerNode->IsCallOn()  || 
				   !ptRollCallerNode->IsVidSndValid() ||
				   !ptFartherNode->IsChanOn() ||
				   !ptFartherNode->IsVidSndValid())
				{
					MdlHint(Ums_Mdl_Call, ("AdjustRollCallerToBas. confID:%d, RollCallerOn:%d, RollCallerSndValid:%d CallerFartherOn:%d, CallerFarSndValid:%d  \n", 
						    pInst->GetInsID(),
							ptRollCallerNode->IsCallOn(),
							ptRollCallerNode->IsVidSndValid(),
							ptFartherNode->IsChanOn(),
							ptFartherNode->IsVidSndValid()));
					break;
				}
				
				pVirRollCaller = pInst->GetRollCallMgr()->GetVirCallerAddr();
				symbolflag = 1;
				for (u16 wIndextmp = 1; wIndextmp <= ptRollCallerNode->m_wVidSndNum; ++wIndextmp, symbolflag *= -1)
				{
                     wChanIndex = MIDSCREENINDEX + wIndextmp / 2 * symbolflag;

					 if (NULL != pVirRollCaller && NULL != pVirRollCaller->m_aptVidAddr[wChanIndex])
					 {
						 atRollCallerRtp[wChanIndex]  = pVirRollCaller->m_aptVidAddr[wChanIndex]->m_tRtpAddr;
						 atRollCallerRtcp[wChanIndex] = pVirRollCaller->m_aptVidAddr[wChanIndex]->m_tBackRtcpAddr;
					     adwRtpEqpNode[wChanIndex]    = pVirRollCaller->m_adwMediaNode[wChanIndex];
					 }
					 else
					 {
						 MdlHint(Ums_Mdl_Call, ("AdjustRollCallerToBas. confid:%d  pVirRollCaller=NULL or m_aptVidAddr[%d]=NULL pVirRollCaller = %p \n",   
							 pInst->GetInsID(),
							 pVirRollCaller));
					 }

				}
				
			} else 
			{  // �¼�

                if (NULL != ptCallerCapNode)
				{   //������Ҳ���¼���ȡ�����˵�����
					if (!ptCallerCapNode->IsChanOn())
					{
						MdlHint(Ums_Mdl_Call, ("AdjustRollCallerToBas. confid:%d  rollcaller:%d is not chan on \n",   
							                   pInst->GetInsID(),
							                   wRollCaller));
						break;
					}

					symbolflag = 1;
					for (u16 wIndextmp = 1; wIndextmp <= ptRollCallerNode->m_wVidSndNum; ++wIndextmp, symbolflag *= -1)
					{
                         wChanIndex = MIDSCREENINDEX + wIndextmp / 2 * symbolflag;

						 if (NULL != ptCallerCapNode->m_aptChanAddr[wChanIndex])
						 {
							 atRollCallerRtp[wChanIndex]  = ptCallerCapNode->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
							 atRollCallerRtcp[wChanIndex] = ptCallerCapNode->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
							 adwRtpEqpNode[wChanIndex]    = ptCallerCapNode->m_tMediaEqp.m_dwEqpNode;
						 }
					}
				}
				else 
				{   //�����˲��ڴ�UMS��  ȡ����ͨ������ϯ�������ˣ�
					
					TCapNode* pUms = pInst->GetNodeMgr()->GetCaller();
					if (NULL == pUms  ||  !pUms->IsChanOn() || NULL == pUms->m_ptCasCadeChairAddr)
					{
						MdlHint(Ums_Mdl_Call, ("AdjustRollCallerToBas. caller(EP65) invalid caller:%p iscallerChanOn:%d isCasCadeChairAddr:%d\n",   
							    pUms,
								((NULL==pUms)? 65535 : (pUms->IsChanOn())),
								((NULL==pUms)? 65535 : (NULL == pUms->m_ptCasCadeChairAddr))));
						break;
					}

					symbolflag = 1;
					for (u16 wIndextmp = 1; wIndextmp <= TP_MAX_STREAMNUM; ++wIndextmp, symbolflag *= -1)
					{    //����ͨ���� TP_MAX_STREAMNUM
                         wChanIndex = MIDSCREENINDEX + wIndextmp / 2 * symbolflag;

						 atRollCallerRtp[wChanIndex]  = pUms->m_ptCasCadeChairAddr->m_atVid[wChanIndex].m_tRtpAddr;
						 atRollCallerRtcp[wChanIndex] = pUms->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
						 adwRtpEqpNode[wChanIndex]    = pUms->m_tMediaEqp.m_dwEqpNode;	

					}

				}
                	
			}
			
			TTPMediaTransAddr tBasAddr;
			//�¼���֪���������м�����,���������
			for (wIndex = 0; wIndex <= TP_MAX_STREAMNUM; wIndex++)
			{			
				//��Ƶ
				pInst->GetBas()->GetInChnChairVidAddr(tBasAddr, wIndex);
				
				if (atRollCallerRtp[wIndex].GetPort() != 0)
				{
					atDsData[wDsNum].m_tRcvFromAddr = atRollCallerRtp[wIndex];;
					atDsData[wDsNum].m_tSndToAddr = tBasAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = adwRtpEqpNode[wIndex];
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetVideo(wIndex);
					++wDsNum;
					
					atDsData[wDsNum].m_tRcvFromAddr = tBasAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_tSndToAddr = atRollCallerRtcp[wIndex];					
					atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				    ++wDsNum;
				}
	
				//��Ƶ�� ��ʹ����ϯ��Ƶ����
			}
				
		}

	}while(0);


	MergerDsList(pInst, pInst->GetBas()->GetChairToBasDsList(), atDsData, wDsNum, "AdjustRollCallerToBas");

	return; 
}


u16 CNetPortMgr::GetRollCallObjToVirSpeaker(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs )
{
    TCallNode* ptCurSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->curSpeakerID());
	TCapNode* ptCurForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptCurSpeaker);	

	TCallNode* ptOldSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->oldSpeakerID());
	TCapNode* ptOldForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldSpeaker);	

	if (NULL == ptCurSpeaker && NULL == ptOldSpeaker )
	{
		MdlHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker speaker epid error. confID:%d, curEp:%d, NewEp:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->oldSpeakerID()));
		return 0;
	}

	u16 wDsNum = 0;

	if ( !ptCurSpeaker->IsChanOn() )
	{//��ǰ�����˲����� ɾ�����н���
		MdlHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker speaker stat error. confID:%d, curEp:%d, NewEp:%d, curEpStat:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->oldSpeakerID(), ptCurSpeaker->IsChanOn()));

		wDsNum = GetNonSpeakerToVirSpeaker(pInst, atDsData, wMaxDs);
		
		return wDsNum;
	}

	u16 wEqpIndex;
	u32 dwNodeIP = 0;

	u32 dwNodeEqp = 0;
	u32 dwConfEqp = pInst->m_tEqpConfDs.m_dwEqpNode;

	u16 wChanIndex = 0;
	
	TEqpRes* ptEqp;

	u16 wTempNum = 0;
	u16 wMidIndex = MIDSCREENINDEX;
	u16 wIndex = 1;
	s32 symbolflag = 1; 
	BOOL32 bFilterFlag = FALSE;
	
	//��Ƶ
	if (NULL != ptCurSpeaker && ptCurSpeaker->IsVidSndValid())
	{
		symbolflag = 1; 
		for (u16 wIndex = 1; wIndex <= ptCurSpeaker->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

			pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);

			if(	pInst->GetVmp()->IsBrdVmp() && wChanIndex == MIDSCREENINDEX )
			{//�ϳɹ㲥���������м��� ���պϳɹ㲥
				TTPDsFrom tAddr;
				pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr, ptCurForether->m_tVidSndFormat.m_tFormat, TRUE);

				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVmpVideo();
				++wDsNum;

				atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
				continue;
			}

			atDsData[wDsNum].m_tRcvFromAddr = ptCurForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;

			if (pInst->m_abOnIFrameCheck[wChanIndex])
			{//��Ҫ���ؼ�֡����ؼ�֡������Ȼ�����ϵķ�����
				continue;
			}
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptCurForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if ( pInst->GetVmp()->IsBrdVmp() )
		{
			TTPDsFrom tAddr;
			pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr, ptCurForether->m_tVidSndFormat.m_tFormat, TRUE);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVmpVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else if ( !pInst->GetVmp()->IsSpeakerInVmp())
		{//����ϯ��������û�ڷ����˺ϳ���
			wChanIndex = ptCurSpeaker->GetSpeaker();
			atDsData[wDsNum].m_tRcvFromAddr = ptCurForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptCurForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else
		{//�������˺ϳ�
			TTPDsFrom tAddr;
			pInst->GetVmp()->GetSpeakerVmpOutAddr(tAddr);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}


	if (NULL != ptOldSpeaker && ptOldSpeaker->IsVidSndValid())
	{
		symbolflag = 1; 
		for (u16 wIndex = 1; wIndex <= ptOldSpeaker->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

			if (!pInst->m_abOnIFrameCheck[wChanIndex])
			{//����Ҫ���ؼ�֡
				continue;
			}

			if(	pInst->GetVmp()->IsBrdVmp() && wChanIndex == MIDSCREENINDEX )
			{//�ϳɹ㲥���������м��� ���պϳɹ㲥������Ҫ���
				continue;
			}
				
			pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
			
			atDsData[wDsNum].m_tRcvFromAddr = ptOldForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptOldForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptOldForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if (pInst->m_bOnSingleIframeCheck)
		{//���ڽ��йؼ�֡��⣬���ϵ�����Ҳת�����ⷢ����
			wChanIndex = ptOldSpeaker->GetSpeaker();
			atDsData[wDsNum].m_tRcvFromAddr = ptOldForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptOldForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;
		}
	}


	//����Ŀ����Ƶ, �м�����������  �����������ʽ���ܴ�mix��ȡ�õ������˵������ʽ����
	TServiceAddr tMixOutAddr;
	TRollCallMixRes *pMixRes = pInst->GetRollCallMgr()->GetMixRes();
    pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes->m_ptMixRes, tMixOutAddr, ptCurForether->m_tAudSndFormat.m_tFormat);

	atDsData[wDsNum].m_tRcvFromAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
	atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tRtpAddr;
	atDsData[wDsNum].m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
	atDsData[wDsNum].m_emSwitchType = emRtpSwap;
	atDsData[wDsNum].SetEQPMixNVideo();
	++wDsNum;
	
	atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tBackRtcpAddr;
	atDsData[wDsNum].m_tSndToAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
	atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
	atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
	++wDsNum;



    TServiceAddr tAudAddr;
    if (pInst->GetDualMgr()->IsStart() &&  pInst->GetSpeaker().m_bIsDualMixOn)
	{
        pInst->GetDualMgr()->AdjustDualMixForRollCall();
        // �������� + �������� + ˫��   ���ǹ㲥������
		pInst->GetEapu()->GetNModeAudRcvAddr(pInst->GetSpeaker().m_ptAudMix, tAudAddr, ptCurForether->m_tAudSndFormat.m_tFormat);
		
		atDsData[wDsNum].m_tRcvFromAddr = tAudAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tAudAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetEQPMixNVideo();
		++wDsNum;
		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tAudAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		++wDsNum;

		// ����ڵ������ٿ���˫�����ϼ�Ӧ����PUT һ�µ����߱������ߵ���Ƶ��ʹ�����˫��
		u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();
		u16 wCallTarget = pInst->GetRollCallMgr()->GetCallTargetEpId();
        pInst->GetRollCallMgr()->RollCallAudPudDown(wRollCaller);
		pInst->GetRollCallMgr()->RollCallAudPudDown(wCallTarget);

	}
	else 
	{  // �������� +  ��������
		tMixOutAddr.Clear();

		pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes->m_ptMixRes, tMixOutAddr, ptCurForether->m_tAudSndFormat.m_tFormat);
		//����Ŀ������   �����������ʽ����
		atDsData[wDsNum].m_tRcvFromAddr = tMixOutAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tMixOutAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetEQPMixNVideo();
		++wDsNum;
		
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tMixOutAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
     	++wDsNum;
	}

	for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
	{//�ӻ���ת���壬ת��������ת����
		ptEqp = &pInst->m_atDsEqp[wEqpIndex];
		if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
		{
			MdlLowHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker Valid:%d, EpIndex:%d, ConfIndex:%d.\n",
									   ptEqp->IsValid(), ptEqp->m_wEqpIndex,
									   pInst->m_tEqpConfDs.m_wEqpIndex));
			continue;
		}

		for( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
		}
		
		//�������
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		++wDsNum;

		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;		
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
	}
	
	return wDsNum;

}


u16 CNetPortMgr::GetRollCallObjToVirSpeakerForDown(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs)
{
	TCallNode* ptCurSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->curSpeakerID());
	TCapNode* ptCurForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptCurSpeaker);	

	TCallNode* ptOldSpeaker = pInst->m_pcNodeMgr->GetNode(pInst->oldSpeakerID());
	TCapNode* ptOldForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldSpeaker);	

	if (NULL == ptCurSpeaker && NULL == ptOldSpeaker )
	{
		MdlHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker speaker epid error. confID:%d, curEp:%d, NewEp:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->oldSpeakerID()));
		return 0;
	}

	u16 wDsNum = 0;

	if ( !ptCurSpeaker->IsChanOn() )
	{//��ǰ�����˲����� ɾ�����н���
		MdlHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker speaker stat error. confID:%d, curEp:%d, NewEp:%d, curEpStat:%d\n"
			, pInst->GetInsID(), pInst->curSpeakerID(), pInst->oldSpeakerID(), ptCurSpeaker->IsChanOn()));
		
		//pInst->GetBas()->AdjustSpeakerBas(MIDSCREENINDEX, FALSE);

		wDsNum = GetNonSpeakerToVirSpeaker(pInst, atDsData, wMaxDs);
		
		return wDsNum;
	}

	u16 wEqpIndex;
	u32 dwNodeIP = 0;

	u32 dwNodeEqp = 0;
	u32 dwConfEqp = pInst->m_tEqpConfDs.m_dwEqpNode;

	u16 wChanIndex = 0;
	
	TEqpRes* ptEqp;

	u16 wTempNum = 0;
	u16 wMidIndex = MIDSCREENINDEX;
	u16 wIndex = 1;
	s32 symbolflag = 1; 
	BOOL32 bFilterFlag = FALSE;
	
    // -----��������(��������)���¼�UMSʱ------:
	//(1)������Ҳ���¼���ͨ����ϯͨ������������: 
	//(V0=��  V1=��  V2=��)  
	//(A0=��  A1=������+�������˵Ļ���  A2=��)
	//(singlevid = �����˺ϳ� �� �������˺ϳ�)  
	//(mixaud = ������+�������˵Ļ���)

    //(2) �������ڲ��ڴ��¼�UMS, ͨ����ϯͨ��������������: 
	//(V0=������v0  V1=������v1  V2=������v2)
	//(A0=��  A1=������+�������˵Ļ���  A2=��)
	//(singlevid = �����˺ϳ� �� �������˺ϳ�)
	//(mixaud = ������+�������˵Ļ���)


    // -----��������(��������)�����¼�UMSʱ------:
    //(V0=��������V1  V1=��������V2  V2=��������V3)
	//(A0=��  A1=������+�������˵Ļ���  A2=��)
  	//(Mixdec = ������+�������˵Ļ���)
	//                 ͨ������ͨ��������������:
    //(singlevid = �����˺ϳ� �� �������˺ϳ�)



	//��Ƶ
	if (NULL != ptCurSpeaker && ptCurSpeaker->IsVidSndValid())
	{
		symbolflag = 1; 
		for (u16 wIndex = 1; wIndex <= ptCurSpeaker->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

			pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);

			if(	pInst->GetVmp()->IsBrdVmp() && wChanIndex == MIDSCREENINDEX )
			{//�ϳɹ㲥���������м��� ���պϳɹ㲥
				TTPDsFrom tAddr;
				pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr, ptCurForether->m_tVidSndFormat.m_tFormat, TRUE);

				atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetVmpVideo();

				++wDsNum;

				atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
				continue;
			}

			atDsData[wDsNum].m_tRcvFromAddr = ptCurForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;

			if (pInst->m_abOnIFrameCheck[wChanIndex])
			{//��Ҫ���ؼ�֡����ؼ�֡������Ȼ�����ϵķ�����
				continue;
			}
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptCurForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if ( pInst->GetVmp()->IsBrdVmp() )
		{
			TTPDsFrom tAddr;
			pInst->GetVmp()->GetBrdVmpOutAddr( pInst->GetVmp()->GetConfBrdVmp(), tAddr, ptCurForether->m_tVidSndFormat.m_tFormat, TRUE);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVmpVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else if ( !pInst->GetVmp()->IsSpeakerInVmp())
		{//����ϯ��������û�ڷ����˺ϳ���
			wChanIndex = ptCurSpeaker->GetSpeaker();
			atDsData[wDsNum].m_tRcvFromAddr = ptCurForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptCurForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptCurForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		else
		{//�������˺ϳ�
			TTPDsFrom tAddr;
			pInst->GetVmp()->GetSpeakerVmpOutAddr(tAddr);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAddr.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}


	if (NULL != ptOldSpeaker && ptOldSpeaker->IsVidSndValid())
	{
		symbolflag = 1; 
		for (u16 wIndex = 1; wIndex <= ptOldSpeaker->m_wVidSndNum; ++wIndex, symbolflag *= -1)
		{
			wChanIndex = wMidIndex + wIndex / 2 * symbolflag;

			if (!pInst->m_abOnIFrameCheck[wChanIndex])
			{//����Ҫ���ؼ�֡
				continue;
			}

			if(	pInst->GetVmp()->IsBrdVmp() && wChanIndex == MIDSCREENINDEX )
			{//�ϳɹ㲥���������м��� ���պϳɹ㲥������Ҫ���
				continue;
			}
				
			pInst->GetSpeakerVidDec(wChanIndex).SetIP(pInst->m_tEqpConfDs.m_dwEqpIp);
			
			atDsData[wDsNum].m_tRcvFromAddr = ptOldForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptOldForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wChanIndex).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptOldForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if (pInst->m_bOnSingleIframeCheck)
		{//���ڽ��йؼ�֡��⣬���ϵ�����Ҳת�����ⷢ����
			wChanIndex = ptOldSpeaker->GetSpeaker();
			atDsData[wDsNum].m_tRcvFromAddr = ptOldForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptOldForether->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetVideo(wChanIndex);
			++wDsNum;
		}
	}


	TCapNode* pUms = pInst->GetNodeMgr()->GetCaller();
	   
	//��Ƶ
    if (CALLER_EP_INDEX == pInst->curSpeakerID())
	{// ������(��������)���ڴ��¼�UMS �£� �ǵ����ˡ��Ǳ������� ����Ƶ��ͨ������ͨ��������

		if(NULL != pUms && pUms->IsChanOn() && NULL != pUms->m_aptChanAddr[MIDSCREENINDEX])
		{  
			atDsData[wDsNum].m_tRcvFromAddr = pUms->m_aptChanAddr[MIDSCREENINDEX]->m_tAud.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = pUms->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetAudio(MIDSCREENINDEX);
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = pUms->m_tRmtChan.m_atAudEnc[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
			
			
			if (pUms->m_ptMixAddr != NULL)
			{
				atDsData[wDsNum].m_tRcvFromAddr = pUms->m_ptMixAddr->m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = pUms->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetEPMixAudio();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
				atDsData[wDsNum].m_tSndToAddr = pUms->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		        ++wDsNum;
			}
			else
			{
				MdlError(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker rollcall get aud addr pUms->m_ptMixAddr == NULL\n"));
			}
				
		} else 
		{
			MdlError(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker rollcall get aud addr error. confID:%d, curEp:%d, IsTopUmsNull:%p, TopUmsChanOn:%d, m_aptChanAddr:%d\n"
				, pInst->GetInsID(), pInst->curSpeakerID(), pUms, ((NULL == pUms)? 65535 : pUms->IsChanOn()), ((NULL == pUms)? 65535 : (NULL == pUms->m_aptChanAddr[MIDSCREENINDEX]))));
		}
	} 
	else 
	{// ������(��������)�ڴ��¼�UMS �£� �ǵ����ˡ��Ǳ������� ����Ƶ��ͨ����ϯͨ��������
         
        if ( NULL != pUms && pUms->m_ptCasCadeChairAddr != NULL)
		{
            atDsData[wDsNum].m_tRcvFromAddr = pUms->m_ptCasCadeChairAddr->m_atAud[MIDSCREENINDEX].m_tRtpAddr;
		    atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tRtpAddr;
		    atDsData[wDsNum].m_dwEqpNode = pUms->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetAudio(MIDSCREENINDEX);
		    ++wDsNum;
		
		    atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(MIDSCREENINDEX).m_tBackRtcpAddr;
		    atDsData[wDsNum].m_tSndToAddr = pUms->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr;
		    atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		    ++wDsNum;


		    atDsData[wDsNum].m_tRcvFromAddr = pUms->m_ptCasCadeChairAddr->m_tMixAud.m_tRtpAddr;
		    atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		    atDsData[wDsNum].m_dwEqpNode = pUms->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetEPMixAudio();
		    ++wDsNum;
		
		    atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
		    atDsData[wDsNum].m_tSndToAddr = pUms->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr.m_tBackRtcpAddr;
		    atDsData[wDsNum].m_dwEqpNode = dwConfEqp;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		    ++wDsNum;
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker rollcall1 get aud addr error. confID:%d, curspEp:%d, IsTopUmsNull:%p, CasCadeChair:%d\n"
				, pInst->GetInsID(), pInst->curSpeakerID(), pUms, ((NULL == pUms)? 65535 : (NULL == pUms->m_ptCasCadeChairAddr)) ));
		}
	}


	for (wEqpIndex = 0; wEqpIndex < UMS_CONF_MAX_DS_NUM; ++wEqpIndex)
	{//�ӻ���ת���壬ת��������ת����
		ptEqp = &pInst->m_atDsEqp[wEqpIndex];
		if (!ptEqp->IsValid() || ptEqp->m_wEqpIndex == pInst->m_tEqpConfDs.m_wEqpIndex)
		{
			MdlLowHint(Ums_Mdl_Call, ("GetSpeakerToVirSpeaker Valid:%d, EpIndex:%d, ConfIndex:%d.\n",
									   ptEqp->IsValid(), ptEqp->m_wEqpIndex,
									   pInst->m_tEqpConfDs.m_wEqpIndex));
			continue;
		}

		for( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;

			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
			atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
		}
		
		//�������
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		++wDsNum;

		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;		
		atDsData[wDsNum].m_tSndToAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr.SetIP(ptEqp->m_dwEqpIp);
		atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
	}
	
	return wDsNum;
}


u16 CNetPortMgr::PutAudDownToRollCallEp(CUmsConfInst* pInst,  TCallNode* ptNode)
{
	u16	wDsNum = 0;
    TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	TServiceAddr tAudAddr;
	TRollCallEpInfo* ptEpInfo = pInst->GetRollCallMgr()->GetRollCallEpInfoById(ptNode->m_wEpID);


	do 
	{
		if (NULL == ptEpInfo || !ptEpInfo->IsValid())
		{
            break;
		}


		if (ptNode->IsSingleAudRcv() && pInst->GetDualMgr()->IsStart() &&  pInst->GetSpeaker().m_bIsDualMixOn)
		{// �����᳡���翪˫����Ҫ���˫�������� ��N-1 ��
			pInst->GetEapu()->GetMixerChnOutAddr(pInst->GetSpeaker().m_ptAudMix, tAudAddr, ptNode->m_wEpID, TP_MAX_STREAMNUM);
			
			atDsData[wDsNum].m_tRcvFromAddr = tAudAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAudAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetEQPMixN1Video();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAudAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;

			break;
		} 


		TRollCallMixRes *pMixRes = pInst->GetRollCallMgr()->GetMixRes();
		if (NULL != pMixRes && NULL != pMixRes->m_ptMixRes) 
		{
			pInst->GetEapu()->GetMixerChnOutAddr(pMixRes->m_ptMixRes, tAudAddr, ptNode->m_wEpID, TP_MAX_STREAMNUM); 
			
			atDsData[wDsNum].m_tRcvFromAddr = tAudAddr.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tAudAddr.m_dwMediaNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetEQPMixN1Video();
			wDsNum++;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptEpInfo->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
			atDsData[wDsNum].m_tSndToAddr = tAudAddr.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			wDsNum++;	
		}

	} while(0);

	
    MergerDsList(pInst, ptEpInfo->m_cToPutAuddrDsInfo, atDsData, wDsNum, "PutAudDownToRollCallEp");

	return wDsNum;
	
}


u16 CNetPortMgr::AdjustRollCallerToVirRollCaller(CUmsConfInst* pInst, u16 wCallEpId)
{
    u16 wIndex = 0;
	u16 wChanIndex = 0;
	s32 symbolflag = 1; 

	u16	wDsNum = 0;
    TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	TCallNode* ptCurRollCaller    = pInst->m_pcNodeMgr->GetNode(wCallEpId);
	TCapNode* ptCurCallerForether = pInst->m_pcNodeMgr->GetForeFatherNode(ptCurRollCaller);

    TCallNode* pCallTargetNode = NULL;

    TVirCallerAddr  *pVirRollCaller = pInst->GetRollCallMgr()->GetVirCallerAddr();
	
	if (pInst->IsChairConf())
	{
		if (NULL == ptCurRollCaller || NULL == ptCurCallerForether )
		{
			MdlHint(Ums_Mdl_Call, ("AdjustRollCallerToVirRollCaller wCallEpId epid error. confID:%d, curEp:%d\n"
				, pInst->GetInsID(), wCallEpId));

			return wDsNum;
		}

		if (NULL == pVirRollCaller || NULL == pVirRollCaller->m_aptVidAddr[MIDSCREENINDEX])
		{
            return wDsNum;
		}


        if (ptCurRollCaller == ptCurCallerForether)
		{	
            //���������ϼ�
            symbolflag = 1; 
			for(wIndex = 1; wIndex <= ptCurCallerForether->m_wVidSndNum; ++wIndex, symbolflag *= -1)
			{
                 wChanIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

				 if (NULL != ptCurCallerForether->m_aptChanAddr[wChanIndex])
				 {
					 atDsData[wDsNum].m_tRcvFromAddr = ptCurCallerForether->m_aptChanAddr[wChanIndex]->m_tVid.m_tRtpAddr;
				     atDsData[wDsNum].m_tSndToAddr   = pVirRollCaller->m_aptVidAddr[wChanIndex]->m_tRtpAddr;
				     atDsData[wDsNum].m_dwEqpNode    = ptCurCallerForether->m_tMediaEqp.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					 atDsData[wDsNum].SetVideo(wChanIndex);
				     ++wDsNum;
				 
				     atDsData[wDsNum].m_tRcvFromAddr = pVirRollCaller->m_aptVidAddr[wChanIndex]->m_tBackRtcpAddr;
				     atDsData[wDsNum].m_tSndToAddr   = ptCurCallerForether->m_tRmtChan.m_atVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
				     atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				     ++wDsNum;
				 }
				 
				 //С����
				 if (ptCurRollCaller->IsSmallVidSnd() && NULL != ptCurCallerForether->m_aptSmallChanAddr[wChanIndex])
				 {
					 atDsData[wDsNum].m_tRcvFromAddr = ptCurCallerForether->m_aptSmallChanAddr[wChanIndex]->m_tRtpAddr;
					 atDsData[wDsNum].m_tSndToAddr   = pVirRollCaller->m_aptSmallAddr[wChanIndex]->m_tRtpAddr;
					 atDsData[wDsNum].m_dwEqpNode    = ptCurCallerForether->m_tMediaEqp.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					 atDsData[wDsNum].SetSmallVideo(wChanIndex);
					 ++wDsNum;
					 
					 atDsData[wDsNum].m_tRcvFromAddr = pVirRollCaller->m_aptSmallAddr[wChanIndex]->m_tBackRtcpAddr;
					 atDsData[wDsNum].m_tSndToAddr   = ptCurCallerForether->m_tRmtChan.m_atSmallVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
					 atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					 ++wDsNum;
				}


			}
		}
		else
		{// ���������¼�, �����˵�����������ͨ����ϯͨ�������� ����ǵ�������VMP ��ô�����˵�С����ͨ������ͨ������
		 // ע����  ����ģʽ��  ����ͨ����С����ͨ��:
		 //	(1)�����������¼������Ƿ����˺ϳ�ʱ��С����ͨ���������䷢���˵�С����;
		 // (2)�����������¼���������ϯ�������ˣ��ϳ�ʱ�� С����ͨ��������������˵�С����


			symbolflag = 1; 
			for(wIndex = 1; wIndex <= ptCurCallerForether->m_wVidSndNum; ++wIndex, symbolflag *= -1)
			{
                 wChanIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

				 if (NULL != ptCurCallerForether->m_ptCasCadeChairAddr)
				 {
					 atDsData[wDsNum].m_tRcvFromAddr = ptCurCallerForether->m_ptCasCadeChairAddr->m_atVid[wChanIndex].m_tRtpAddr;
					 atDsData[wDsNum].m_tSndToAddr   = pVirRollCaller->m_aptVidAddr[wChanIndex]->m_tRtpAddr;
					 atDsData[wDsNum].m_dwEqpNode    = ptCurCallerForether->m_tMediaEqp.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					 atDsData[wDsNum].SetVideo(wChanIndex);
					 ++wDsNum;
					 
					 atDsData[wDsNum].m_tRcvFromAddr = pVirRollCaller->m_aptVidAddr[wChanIndex]->m_tBackRtcpAddr;
					 atDsData[wDsNum].m_tSndToAddr   = ptCurCallerForether->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
					 atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				     ++wDsNum;
				 }
				 
				 if (ptCurRollCaller->IsSmallVidSnd() && NULL != ptCurCallerForether->m_aptSmallChanAddr[wChanIndex])
				 {   // ������������¼������ҪȡС����һ���ǴӸü���ͨ�������ģ��ý���Ӧ������������ֻ����һ��
					 atDsData[wDsNum].m_tRcvFromAddr = ptCurCallerForether->m_aptSmallChanAddr[wChanIndex]->m_tRtpAddr;
					 atDsData[wDsNum].m_tSndToAddr   = pVirRollCaller->m_aptSmallAddr[wChanIndex]->m_tRtpAddr;
					 atDsData[wDsNum].m_dwEqpNode    = ptCurCallerForether->m_tMediaEqp.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					 atDsData[wDsNum].SetSmallVideo(wChanIndex);
					 ++wDsNum;
					 
					 atDsData[wDsNum].m_tRcvFromAddr = pVirRollCaller->m_aptSmallAddr[wChanIndex]->m_tBackRtcpAddr;
					 atDsData[wDsNum].m_tSndToAddr   = ptCurCallerForether->m_tRmtChan.m_atSmallVidEnc[wChanIndex].m_tChanAddr.m_tBackRtcpAddr;
					 atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
					 atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					 ++wDsNum;
				} 

			}

		}

		MergerDsList(pInst, pInst->GetRollCallMgr()->GetVirCallerDs(), atDsData, wDsNum, "AdjustRollCallerToVirRollCaller");
	}

	return wDsNum;
}

u16 CNetPortMgr::AdjustEpAudToMixDs( CUmsConfInst* pInst, TUmsAudMixEqp* pMixRes, TAudMixMemberInfo* ptMemberInfo )
{
	u16	wDsNum = 0;
	if (NULL == pMixRes->m_ptMixRes)
	{
		return wDsNum;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TTPMediaTransAddr tDstAddr;
	TServiceAddr tScrAddr;
	u16 wOprEpId = 0;
	u16 wScrIndex = 0;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 == ptMemberInfo->m_awEpId[wIndex])
		{
			continue;
		}
		
		wOprEpId = ptMemberInfo->m_awEpId[wIndex];
		wScrIndex = ptMemberInfo->m_awScrIndx[wIndex];
		// ��������Ա������������Ƶ����
		pInst->GetEapu()->GetMixerChnInAddr(pMixRes->m_ptMixRes, tDstAddr, wOprEpId, wScrIndex);			
		pInst->GetAudMix()->GetMixEpAudSndAddr(wOprEpId, tScrAddr);
		
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}
	
	MergerDsList(pInst, pMixRes->m_cToMixDsInfo, atDsData, wDsNum, "AdjustEpAudToMixDs");
	return wDsNum;

}




u16 CNetPortMgr::AdjustConfMixToDulMixer(CUmsConfInst* pInst, TAudMixMemberInfo* ptMemberInfo)
{
	u16	wDsNum = 0;
	if (NULL == pInst->GetSpeaker().m_ptAudMix)
	{
		return wDsNum;
	}
	
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TTPMediaTransAddr tDstAddr;
	TServiceAddr tScrAddr;

	u16 wOprEpId = 0;
	u16 wScrIndex = 0;
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 == ptMemberInfo->m_awEpId[wIndex])
		{
			continue;
		}
		wOprEpId = ptMemberInfo->m_awEpId[wIndex];
		wScrIndex = ptMemberInfo->m_awScrIndx[wIndex];
		// ��������Ա������������Ƶ����
		pInst->GetEapu()->GetMixerChnInAddr(pInst->GetSpeaker().m_ptAudMix, tDstAddr, wOprEpId, wScrIndex);			
		
		
		if (TP_MAX_STREAMNUM + 1 == wScrIndex  && pInst->IsChairConf() && pInst->GetDualMgr()->IsStart() &&  pInst->GetSpeaker().m_bIsDualMixOn)
		{   //˫����ȡ˫��������
			tScrAddr.Clear();

			TCallNode* ptDual       = pInst->GetNodeMgr()->GetNode(pInst->GetDualMgr()->GetDualID());
			TCapNode* ptFartherDual = pInst->GetNodeMgr()->GetForeFatherNode(ptDual);
			if (NULL != ptDual && NULL != ptFartherDual)
			{
				tScrAddr.m_tAddr.m_tRtpAddr      = pInst->GetDualMgr()->m_tAudRcvAddr.m_tRtpAddr;
				tScrAddr.m_tAddr.m_tBackRtcpAddr = pInst->GetDualMgr()->m_tAudRcvAddr.m_tBackRtcpAddr;
				tScrAddr.m_dwMediaNode           = ptFartherDual->m_tMediaEqp.m_dwEqpNode;;
			}
		}
		else 
		{
			pInst->GetAudMix()->GetMixEpAudSndAddr(wOprEpId, tScrAddr);

		}
		
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr.m_tRtpAddr;
		atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
		
		atDsData[wDsNum].m_tRcvFromAddr = tDstAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}
	
	MergerDsList(pInst, pInst->GetSpeaker().m_tToAudMixDs, atDsData, wDsNum, "AdjustConfMixToDulMixer");
	return wDsNum;
}



u16 CNetPortMgr::PutMixAudToLowUmsEp( CUmsConfInst* pInst, TUmsAudMixEpInfo* ptInfo )
{
	u16	wDsNum = 0;
	if (NULL == ptInfo)
	{
		return wDsNum;
	}
	
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	TServiceAddr tScrAddr;


	pInst->GetAudMix()->GetMixAudRcvAddrForMixEp(ptInfo, tScrAddr);

	atDsData[wDsNum].m_tRcvFromAddr = tScrAddr.m_tAddr.m_tRtpAddr;
	atDsData[wDsNum].m_tSndToAddr = ptInfo->m_atPutAuddr[MIDSCREENINDEX].m_tRtpAddr;
	atDsData[wDsNum].m_dwEqpNode = tScrAddr.m_dwMediaNode;
	atDsData[wDsNum].m_emSwitchType = emRtpSwap;
	atDsData[wDsNum].SetEQPMixN1Video();
	wDsNum++;
	
	atDsData[wDsNum].m_tRcvFromAddr = ptInfo->m_atPutAuddr[MIDSCREENINDEX].m_tBackRtcpAddr;
	atDsData[wDsNum].m_tSndToAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
	atDsData[wDsNum].m_dwEqpNode = pInst->GetConfEqpDs().m_dwEqpNode;
	atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
	wDsNum++;



	MergerDsList(pInst, ptInfo->m_cToPutAuddrDsInfo, atDsData, wDsNum, "PutMixAudToLowUmsEp");
	return wDsNum;
}


u16 CNetPortMgr::AdjustConfVidAudToTarget(CUmsConfInst* pInst, CDsListInfo& DsInfo, const TUmsGetConfBrdVidAudInfo& tVidAudmsgInfo)
{
    u16 wIndex = 0;

	u16	wDsNum = 0;
    TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	const TTPTransAddr* ptDstAddr = NULL;

    for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
	    ptDstAddr = &tVidAudmsgInfo.m_atVidAddr[wIndex];
		//��·��Ƶ
        if (0 != ptDstAddr->m_dwIP && 0 != ptDstAddr->m_wPort)
		{             
			// ���ⷢ���˵�...
	        atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerVidDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr   = *ptDstAddr;
			atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
		}

		//��·��Ƶ
		ptDstAddr = &tVidAudmsgInfo.m_atAudAddr[wIndex];
        if (0 != ptDstAddr->m_dwIP && 0 != ptDstAddr->m_wPort)
		{
			// ���ⷢ���˵�....
			atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudDec(wIndex).m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr   = *ptDstAddr;
			atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
		}
	}

	//������Ƶ
	ptDstAddr = &tVidAudmsgInfo.m_tSingleVidAddr;
	if (0 != ptDstAddr->m_dwIP && 0 != ptDstAddr->m_wPort)
	{
		// ���ⷢ���˵�����rtp
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSingleVidDec().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr   = *ptDstAddr;
		atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		++wDsNum;

	}

	//������Ƶ
	ptDstAddr = &tVidAudmsgInfo.m_tAudMixAddr;
	if (0 != ptDstAddr->m_dwIP && 0 != ptDstAddr->m_wPort)
	{
		// ���ⷢ���˵�����rtp
		atDsData[wDsNum].m_tRcvFromAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr   = *ptDstAddr;
		atDsData[wDsNum].m_dwEqpNode    = pInst->m_tEqpConfDs.m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		++wDsNum;
	}


	MergerDsList(pInst, DsInfo, atDsData, wDsNum, "AdjustConfVidAudToTarget");
	return wDsNum;
}


u16 CNetPortMgr::AdjustConfVmpVidToTarget(CUmsConfInst* pInst, CDsListInfo& DsInfo, TTPDsFrom& tVmp, TUmsGetVmpVidInfo& tInfo)
{
	u16 wIndex = 0;
	
	u16	wDsNum = 0;
    TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	
    TTPMediaTransAddr tVidAddr;
	u32 dwMediaNode = 0;

	tVidAddr.m_tRtpAddr = tVmp.m_tRtpAddr;
	tVidAddr.m_tBackRtcpAddr = tVmp.m_tBackRtcpAddr;
	dwMediaNode = tVmp.m_dwEqpNode;
	
	//��Ƶ
	atDsData[wDsNum].m_tRcvFromAddr = tVidAddr.m_tRtpAddr;
	atDsData[wDsNum].m_tSndToAddr   = tInfo.m_tRtpAddr;
	atDsData[wDsNum].m_dwEqpNode    = dwMediaNode;
	atDsData[wDsNum].m_emSwitchType = emRtpSwap;
	atDsData[wDsNum].SetVmpVideo();
	wDsNum++;

	MergerDsList(pInst, DsInfo, atDsData, wDsNum, "AdjustConfVmpVidToTarget");
	return wDsNum;

}

u16 CNetPortMgr::AdjustEpScreenStreamToTarget(CUmsConfInst* pInst, CDsListInfo& cDsInfo, TGetEpScreenInfo& tInfo, TGetVidAddr& tAddr, BOOL32 bAudMix)
{
	u16 wIndex = 0;
	
	u16	wDsNum = 0;
    TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	
    TTPMediaTransAddr tVidAddr;
	u32 dwMediaNode = 0;

	//��Ƶ
	if (0 != tInfo.m_tVidAddr.m_dwIP &&  0 != tInfo.m_tVidAddr.m_wPort)
	{
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_atVidAddr[tInfo.m_wScreenID].m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr   = tInfo.m_tVidAddr;
		atDsData[wDsNum].m_dwEqpNode    = tAddr.m_dwMedia;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetVideo(tInfo.m_wScreenID);
		wDsNum++;
	}

	//��Ƶ
	if (0 != tInfo.m_tAudAddr.m_dwIP &&  0 != tInfo.m_tAudAddr.m_wPort)
	{
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_atAudAddr[tInfo.m_wScreenID].m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr   = tInfo.m_tAudAddr;
		atDsData[wDsNum].m_dwEqpNode    = tAddr.m_dwMedia;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetAudio(tInfo.m_wScreenID);
		wDsNum++;
	}

	//����
	if (bAudMix && 0 != tInfo.m_tAudMixAddr.m_dwIP &&  0 != tInfo.m_tAudMixAddr.m_wPort)
	{
		atDsData[wDsNum].m_tRcvFromAddr = tAddr.m_tMixAddr.m_tRtpAddr;
		atDsData[wDsNum].m_tSndToAddr   = tInfo.m_tAudMixAddr;
		atDsData[wDsNum].m_dwEqpNode    = tAddr.m_dwMedia;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetEPMixAudio();
		wDsNum++;
	}
	
	MergerDsList(pInst, cDsInfo, atDsData, wDsNum, "AdjustEpScreenStreamToTarget");
	return wDsNum;
	
}

// XmpuMix��ת��ַ����������ַ
u16 CNetPortMgr::AdjustXmpuMiddleAddrToMix( CUmsConfInst* pInst, TAudMixInfo* ptMixInfo )
{
	u16	wDsNum = 0;
	if (NULL == ptMixInfo)
	{
		return wDsNum;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM+UMS_AUDMIX_N_OUT_NUM];
	TTPTransAddr tDstAddr;
	TTPTransAddr tScrAddr;
	u16 wOprEpId = 0;
	u16 wScrIndex = 0;
	u16 wIndex = 0;
	// N EncMiddleRtcp-->EncRtcp
	for (wIndex = 0; wIndex < UMS_AUDMIX_N_OUT_NUM;++wIndex)
	{
		if (ptMixInfo->m_atNEncRtcpAddr[wIndex].m_wPort ==0 )
		{
			continue;
		}

		tScrAddr = ptMixInfo->m_atNEncMiddleRtcpAddr[wIndex];
		tDstAddr = ptMixInfo->m_atNEncRtcpAddr[wIndex];

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	// N-1 DecMiddleRtp-->Mix DecRtp EncMiddleRtcp--> Mix EncRtcp
	for (wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (ptMixInfo->m_atN1DecRtpAddr[wIndex].m_wPort ==0 
			|| ptMixInfo->m_atN1EncRtcpAddr[wIndex].m_wPort == 0)
		{
			continue;
		}

		tScrAddr = ptMixInfo->m_atN1DecMiddleRtpAddr[wIndex];
		tDstAddr = ptMixInfo->m_atN1DecRtpAddr[wIndex];

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;

		tScrAddr = ptMixInfo->m_atN1EncMiddleRtcpAddr[wIndex];
		tDstAddr = ptMixInfo->m_atN1EncRtcpAddr[wIndex];

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	MergerDsList(pInst, ptMixInfo->m_cToMixDsInfo, atDsData, wDsNum, "AdjustXmpuMiddleAddrToMix");
	return wDsNum;
}

u16 CNetPortMgr::AdjustXmpuMiddleAddrToMpu2( CUmsConfInst* pInst, CServiceInfo* pcService )
{
	u16	wDsNum = 0;
	if (NULL == pcService)
	{
		return wDsNum;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM+UMS_AUDMIX_N_OUT_NUM];
	TTPTransAddr tDstAddr;
	TTPTransAddr tScrAddr;
	u16 wOprEpId = 0;
	u16 wScrIndex = 0;
	u16 wIndex = 0;
	//EncMiddleRtcp-->EncRtcp
	tScrAddr = pcService->m_tEncMiddleRtcpAddr;
	tDstAddr = pcService->m_tEncRtcpAddr;

	if (pcService->m_tEncRtcpAddr.GetPort() != 0)
	{
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}
	
	// DecMiddleRtp-->Mix DecRtp
	for (wIndex = 0; wIndex < pcService->GetMpu2MemNum(); wIndex++)
	{
		if (pcService->m_atDecRtpAddr[wIndex].m_wPort ==0 )
		{
			continue;
		}

		tScrAddr = pcService->m_atDecMiddleRtpAddr[wIndex];
		tDstAddr = pcService->m_atDecRtpAddr[wIndex];

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		wDsNum++;
	}

	MergerDsList(pInst, pcService->m_cToMpuDsInfo, atDsData, wDsNum, "AdjustXmpuMiddleAddrToMpu2");
	return wDsNum;
}

u16 CNetPortMgr::AdjustXmpuMiddleAddrToVmp( CUmsConfInst* pInst, TBrdVmpRes* ptVmp )
{
	u16	wDsNum = 0;
	if (NULL == ptVmp)
	{
		return wDsNum;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM+UMS_AUDMIX_N_OUT_NUM];
	TTPTransAddr tDstAddr;
	TTPTransAddr tScrAddr;
	u16 wOprEpId = 0;
	u16 wScrIndex = 0;
	u16 wIndex = 0;

	// EncMiddleRtcp-->EncRtcp
	for (wIndex = 0;wIndex < TP_VMP_MAX_OUT_CHN_NUM; ++wIndex)
	{
		if (ptVmp->m_atEncRtcpAddr[wIndex].m_wPort ==0 )
		{
			continue;
		}
		
		tScrAddr = ptVmp->m_atEncMiddleRtcpAddr[wIndex];
		tDstAddr = ptVmp->m_atEncRtcpAddr[wIndex];

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	

	//  DecMiddleRtp--> DecRtp
	for (wIndex = 0; wIndex < ptVmp->m_wMemberNum; wIndex++)
	{
		if (ptVmp->m_atDecRtpAddr[wIndex].m_wPort ==0 )
		{
			continue;
		}

		tScrAddr = ptVmp->m_atDecMiddleRtpAddr[wIndex];
		tDstAddr = ptVmp->m_atDecRtpAddr[wIndex];

		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
		wDsNum++;
	}

	MergerDsList(pInst, ptVmp->m_cToVmpDsInfo, atDsData, wDsNum, "AdjustXmpuMiddleAddrToVmp");
	return wDsNum;
}

void MediaCreateNetBuf(CUmsConfInst* pInst, TUmsNetBuf& tNetPara)
{
	u32 dwEqpNode = pInst->GetNbEqp().m_dwEqpNode;
	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_nb_create);
	TConfEpID tConfID;
	TUmsRSParam tRsPara = pInst->GetConfBase().m_tRsParam;

	tConfID.m_wConfID = pInst->GetInsID();
		
	cMsg.SetBody(&tConfID, sizeof(tConfID));
	cMsg.CatBody(&tRsPara, sizeof(tRsPara));
	cMsg.CatBody(&tNetPara, sizeof(tNetPara));

	if (dwEqpNode != 0)
	{
		cMsg.Post(UMS_NETBUF_APP_INST, pInst->GetNbEqp().m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("MediaCreateNetBuf failed! not assign eqp. ConfID:%d, dwEqpNode:%d\n", pInst->GetInsID(), dwEqpNode));
	}
	

 	tpLowHint(Ums_Mdl_Media, "MediaCreateNetBuf Snd("ADDRPORT_FORMAT"), RcvRtp ("ADDRPORT_FORMAT")\n", ADDRNET(tNetPara.m_wSndAddr), ADDRNET(tNetPara.m_tRcvRtpAddr));
 	tpLowHint(Ums_Mdl_Media, "              RcvRtcp("ADDRPORT_FORMAT"), RmtRtcp("ADDRPORT_FORMAT")\n", ADDRNET(tNetPara.m_tRcvRtcpAddr), ADDRNET(tNetPara.m_tRmtRtcpAddr));
	
}


void MediaDestroyNetBuf(CUmsConfInst* pInst, TUmsNetBuf& tNetPara)
{
	u32 dwEqpNode = pInst->GetNbEqp().m_dwEqpNode;
	CTpMsg cMsg;	
	cMsg.SetEvent(ev_media_nb_remove);

	TConfEpID tConfID;
	tConfID.m_wConfID = pInst->GetInsID();
	
	cMsg.SetBody(&tConfID, sizeof(tConfID));
	cMsg.CatBody(&tNetPara, sizeof(tNetPara));
	
	if (dwEqpNode != 0)
	{
		cMsg.Post(UMS_NETBUF_APP_INST, pInst->GetNbEqp().m_dwEqpNode, UMS_CALL_APP_INST(pInst->GetInsID()));
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("MediaDestroyNetBuf failed! not assign eqp. ConfID:%d, dwEqpNode:%d\n", pInst->GetInsID(), dwEqpNode));
	}

	tpLowHint(Ums_Mdl_Media, "  Snd("ADDRPORT_FORMAT"), RcvRtp ("ADDRPORT_FORMAT")\n", ADDRNET(tNetPara.m_wSndAddr), ADDRNET(tNetPara.m_tRcvRtpAddr));
	tpLowHint(Ums_Mdl_Media, "  RcvRtcp("ADDRPORT_FORMAT"), RmtRtcp("ADDRPORT_FORMAT")\n", ADDRNET(tNetPara.m_tRcvRtcpAddr), ADDRNET(tNetPara.m_tRmtRtcpAddr));
}


#ifdef _USE_XMPUEQP_

u16 CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(CUmsConfInst* pInst, tXmpuVidBasRes* pVidBasInfo)
{
	u16	wDsNum = 0;
	if (!pInst || !pVidBasInfo)
	{
		return wDsNum;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	TTPTransAddr tDstAddr;
	TTPTransAddr tScrAddr;
	u16 wIndex = 0;
	
	// EncMiddleRtcp-->EncRtcp
	for (wIndex = 0;wIndex <TP_CONF_MAX_MAIN_VIDEO_RES_NUM; ++wIndex)
	{
		if (pVidBasInfo->m_atEncRtcpAddr[wIndex].m_wPort == 0 )
		{
			continue;
		}
		
		tScrAddr = pVidBasInfo->m_atEncMiddleRtcpAddr[wIndex];
		tDstAddr = pVidBasInfo->m_atEncRtcpAddr[wIndex];
		
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}

	if (pVidBasInfo->m_tDecRtcpAddr.m_wPort !=0 )
	{
		tScrAddr = pVidBasInfo->m_tDecMiddleRtpAddr;
		tDstAddr = pVidBasInfo->m_tDecRtpAddr;
		
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowVideo();
	    wDsNum++;
	}
		
	MergerDsList(pInst, pVidBasInfo->m_tMidAddrDs, atDsData, wDsNum, "AdjustXmpuMiddleAddrToVidBas");
	return wDsNum;
}

u16 CNetPortMgr::AdjustXmpuMiddleAddrToAudBas(CUmsConfInst* pInst, tXmpuAuddBasRes* pAudBasInfo) 
{
	u16	wDsNum = 0;
	if (!pInst || !pAudBasInfo)
	{
		return wDsNum;
	}

	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];
	
	TTPTransAddr tDstAddr;
	TTPTransAddr tScrAddr;
	u16 wIndex = 0;
	
	// EncMiddleRtcp-->EncRtcp
	for (wIndex = 0;wIndex <AUD_BAS_MAX_OUT_CHNL_NUM; ++wIndex)
	{
		if (pAudBasInfo->m_atEncRtcpAddr[wIndex].m_wPort == 0 )
		{
			continue;
		}
		
		tScrAddr = pAudBasInfo->m_atEncMiddleRtcpAddr[wIndex];
		tDstAddr = pAudBasInfo->m_atEncRtcpAddr[wIndex];
		
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
		wDsNum++;
	}
	
	if (pAudBasInfo->m_tDecRtcpAddr.m_wPort != 0 )
	{
		tScrAddr = pAudBasInfo->m_tDecMiddleRtpAddr;
		tDstAddr = pAudBasInfo->m_tDecRtpAddr;
		
		atDsData[wDsNum].m_tRcvFromAddr = tScrAddr;
		atDsData[wDsNum].m_tSndToAddr = tDstAddr;
		atDsData[wDsNum].m_dwEqpNode =  pInst->GetConfEqpDs().m_dwEqpNode;
		atDsData[wDsNum].m_emSwitchType = emRtpSwap;
		atDsData[wDsNum].SetUnknowAudio();
		wDsNum++;
	}
	
	MergerDsList(pInst, pAudBasInfo->m_tMidAddrDs, atDsData, wDsNum, "AdjustXmpuMiddleAddrToAudBas");
	return wDsNum;
}

#endif




