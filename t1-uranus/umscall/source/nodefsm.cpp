#include "umsconfinst.h"
#include "nodefsm.h"
#include "callnodemgr.h"
#include "procnodeds.h"
#include "umsnetportmgr.h"
#include "umsbas.h"
#include "umsvmp.h"
#include "eventoutumsmediatrans.h"
#include "eventoutsipadapter.h"
#include "selviewmgr.h"
#include "pollmgr.h"
#include "umsdiscussnew.h"
#include "umsstackinterface.h"
#include "dualmgr.h"
#include "umsrollcall.h"

#define NODE_FSM_CHECK \
if ( NULL == ptNode ) \
{\
	return;\
}\
if ( !ptNode->IsChanOn() )\
{\
	return ;\
}


#define GetDstIndexBySrcIndex(SrcNode, DstNode, Index) SrcNode->m_wVidRcvNum > 1 ? Index : (DstNode)->GetSpeaker()

s8* GetNodeObj(EMScreenObj emObj)
{
	switch(emObj)
	{
	case emObjSelf:		return "Self";
	case emObjSpeaker:	return "Speaker";
	case emObjChair:	return "Chair";
	case emObjView:		return "View";
	case emObjDiscard:	return "DisCard";
	case emObjVmpBrd:	return "VmpBrd";
	case emObjPoll:		return "Poll";
	default:	break;
	}
	return "unknow";
}

CNodeFsmMgr::CNodeFsmMgr( CUmsConfInst* pcInst )
{
	m_pcConf = pcInst;
}


CNodeFsmMgr::~CNodeFsmMgr()
{
	for ( u16 wIndex = 0; wIndex < emScreenLookedEnd; wIndex ++ )
	{
		if(NULL == m_acFsm[wIndex])
		{
			continue;
		}

		delete m_acFsm[wIndex];
		m_acFsm[wIndex] = NULL;
	}
}


void CNodeFsmMgr::Init()
{
	for ( u16 wIndex = 0; wIndex < emObjLookedEnd; wIndex ++ )
	{
		m_acFsm[wIndex] = NULL;
	}

	m_acFsm[emObjSelf] = new CNodeFsmSelf(Inst());
	m_acFsm[emObjSpeaker] = new CNodeFsmSpeaker(Inst());
	m_acFsm[emObjChair] = new CNodeFsmChair(Inst());
	m_acFsm[emObjPoll] = new CNodeFsmPoll(Inst());
	m_acFsm[emObjView] = new CNodeFsmView(Inst());
	m_acFsm[emObjDiscard] = new CNodeFsmDis(Inst());
	m_acFsm[emObjVmpBrd] = new CNodeFsmVmpBrd(Inst());
}

void CNodeFsmMgr::Quit()
{
	for ( u16 wIndex = 0; wIndex < emObjLookedEnd; wIndex ++ )
	{
		if(NULL == m_acFsm[wIndex])
		{
			continue;
		}
		
		delete m_acFsm[wIndex];
		m_acFsm[wIndex] = NULL;
	}
}

void CNodeFsmMgr::ChangeState(TCapNode* ptNode, BOOL32 bYouAreSeeing /* = TRUE */)
{
	TTransParam atVidParam[TP_MAX_STREAMNUM];
	TTransParam atAudParam[TP_MAX_STREAMNUM];
	TTransParam tMixVid, tMixAud;

	//根据目标发送youareseeing
	TTpYouAreSeeing tSeeing;
	tSeeing.m_bSpeaker = ptNode->m_wEpID == m_pcConf->curSpeakerID() ? TRUE : FALSE;

	//根据目标创建交换
	ForEachChanList(ptNode->m_wVidRcvNum, 
		m_acFsm[ptNode->m_aemObj[ewIndex]]->GetVidSrcAddr(ptNode, ewIndex, atVidParam[ewIndex]);\
		m_acFsm[ptNode->m_aemObj[ewIndex]]->GetObj(ptNode, ewIndex, tSeeing.m_atObj[ewIndex])\
		);
	
	ForEachChanList(ptNode->m_wAudRcvNum, 
		m_acFsm[ptNode->m_aemObj[ewIndex]]->GetAudSrcAddr(ptNode, ewIndex, atAudParam[ewIndex]);\
		);

	m_acFsm[ptNode->m_emLastObj]->GetMixSrcAddr(ptNode, tMixVid, tMixAud);

	if( ptNode->IsUms() )
	{
		if(ptNode->m_wEpID != CALLER_EP_INDEX)
		{
			TUmsHandle tHandle;
			m_pcConf->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);

			TCallNode* ptNewSpeaker = m_pcConf->GetNodeMgr()->GetNode(m_pcConf->curSpeakerID());
			TCapNode* ptNewFahter = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptNewSpeaker);
			if (NULL == ptNewSpeaker || NULL == ptNewFahter || !ptNewSpeaker->IsChanOn())
			{
				MdlHint(Ums_Mdl_Call, ("CNodeFsmMgr::ChangeState failed. ConfID:%d, new speaker:%d\n", m_pcConf->GetInsID(), m_pcConf->curSpeakerID()));
				return;
			}

			TSpeakerCapTr tSpeakerTr;

			if (ptNode->m_wEpID != ptNewFahter->m_wEpID)
			{//看发言人
				m_pcConf->GetSpeakSndCap(m_pcConf->curSpeakerID(), tSpeakerTr);
				tSpeakerTr.m_bIsSpeaker = FALSE;
				tSpeakerTr.m_wSpeakerID = m_pcConf->curSpeakerID();
			}
			else
			{//如果是发言人，看主席。
				m_pcConf->GetChairSndCap(ptNewSpeaker->m_wLowChildEpID, tSpeakerTr);
				tSpeakerTr.m_bIsSpeaker = TRUE;
				tSpeakerTr.m_wSpeakerID = ptNewSpeaker->m_wLowChildEpID;
			}

			UmsSendConfCtrl(tHandle, evtp_Conf_YouAreSeeing_Ind, &tSpeakerTr, sizeof(tSpeakerTr));
		}

		CreateMediaTransUMS(ptNode, atVidParam, atAudParam, tMixVid, tMixAud);
	}
	else
	{
		if( bYouAreSeeing )
		{
			tSeeing.SetVidAudNum();

			TUmsHandle tHandle;
			m_pcConf->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);

			if ( ptNode->IsCns()
				&& ptNode->m_byVer == CNS_B4 )
			{//B4的CNS发送新的目标策略
				UmsSendConfCtrl(tHandle, evtp_Conf_YouAreSeeingEx_Ind, &tSeeing, sizeof(tSeeing));
			}
			else
			{//传统终端 以及 B4以前的CNS
				if( m_pcConf->IsChairConf() || ( !m_pcConf->IsChairConf() && m_pcConf->GetConfInfo().m_bSpeakOnline ) )
				{
					TSpeakerCapTr tSpeakerTr;
					if ( tSeeing.m_atObj[MIDSCREENINDEX].m_emObj == emObjSelf )
					{//本目标 看本地 
						tSpeakerTr.m_wSpeakerID = ptNode->m_wEpID;
					}
					else
					{//其他目标一律给323终端发 发言或主席或无效值 让本地策略切换上看远端目标
						tSpeakerTr.m_wSpeakerID = ptNode->m_wEpID == m_pcConf->curSpeakerID() ? m_pcConf->chairID() : m_pcConf->curSpeakerID();
						
						if ( tSpeakerTr.m_wSpeakerID == ptNode->m_wEpID )
						{//无效值
							tSpeakerTr.m_wSpeakerID = TP_UMS_MAX_CALLNUM;
						}
					}
					tSpeakerTr.m_bIsSpeaker = ptNode->m_wEpID == m_pcConf->curSpeakerID() ? TRUE : FALSE;
					tSpeakerTr.m_wAudSnd = tSeeing.m_wAudNum;
					tSpeakerTr.m_wVidSnd = tSeeing.m_wVidNum;
					tSpeakerTr.m_wSpeakerIndex = MIDSCREENINDEX;
					tSpeakerTr.m_tEpAlias = tSeeing.m_atObj[MIDSCREENINDEX].m_tAlias;

					UmsSendConfCtrl(tHandle, evtp_Conf_YouAreSeeing_Ind, &tSpeakerTr, sizeof(tSpeakerTr));
				}
			}
		}

		CreateMediaTrans(ptNode, atVidParam, atAudParam, tMixVid, tMixAud);
	}
	MdlHint(Ums_Mdl_Call, ("[ChangeState] ConfId:%d, EpId:%d, Obj:(%s, %s, %s), LastObj:%s\n", Inst()->GetInsID(), 
		ptNode->m_wEpID, GetNodeObj(ptNode->m_aemObj[0]), GetNodeObj(ptNode->m_aemObj[1]), 
		GetNodeObj(ptNode->m_aemObj[2]), GetNodeObj(ptNode->m_emLastObj)));
	return;
}

void CNodeFsmMgr::CreateMediaTrans( TCapNode* ptNode, TTransParam atVidParam[], TTransParam atAudParam[], TTransParam& tMixVid, TTransParam& tMixAud )
{
	u16 wDsNum = 0;
	s32 symbolflag = 1;
	u16 wCurIndex = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	BOOL32 bIsSkip = m_pcConf->GetUmsDiscuss()->IsNeedDelay(ptNode->m_wEpID);
	if (bIsSkip)
	{
		MdlHint(Ums_Mdl_Call, ("CNodeFsmMgr::CreateMediaTrans rmt ep ds is skip by ums.....confID:%d, rmtep:%d, bIsSkip:%d.\n"
				, m_pcConf->GetInsID(), ptNode->m_wEpID, bIsSkip));
		return;
	}

//	if (!bIsSkip)
//	{	
		//////////////////////////////////////////////////////////////////////////
		//视频
        if ( ptNode->IsSingleVidRcv())
		{
			if ( tMixVid.m_tAddr.m_tRtpAddr.GetPort() != 0 && ptNode->m_aemObj[MIDSCREENINDEX] == ptNode->m_emLastObj )
			{//单屏先看合成
				atDsData[wDsNum].m_tRcvFromAddr = tMixVid.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tMixVid.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				++wDsNum;
			
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = tMixVid.m_tAddr.m_tBackRtcpAddr;
				if ( tMixVid.m_bMap )
				{
					atDsData[wDsNum].m_tMapedAddr = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;//映射成远端接收端口
				}											
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
			else if(atVidParam[MIDSCREENINDEX].m_tAddr.m_tRtpAddr.GetPort() != 0 
				&& atVidParam[MIDSCREENINDEX].m_tAddr.m_tBackRtcpAddr.GetPort() != 0)
			{//无 则看坐席 atVidParam中间位置存放的是目标的坐席
				atDsData[wDsNum].m_tRcvFromAddr = atVidParam[MIDSCREENINDEX].m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = atVidParam[MIDSCREENINDEX].m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				++wDsNum;
			
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = atVidParam[MIDSCREENINDEX].m_tAddr.m_tBackRtcpAddr;
				if ( atVidParam[MIDSCREENINDEX].m_bMap )
				{
					atDsData[wDsNum].m_tMapedAddr = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;//映射成远端接收端口
				}											
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
		}
		else if( ptNode->IsThreeVidRcv())
		{
			for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			{
				if(atVidParam[wIndex].m_tAddr.m_tRtpAddr.GetPort() == 0)
				{
					continue;
				}

				atDsData[wDsNum].m_tRcvFromAddr = atVidParam[wIndex].m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = atVidParam[wIndex].m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowVideo();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = atVidParam[wIndex].m_tAddr.m_tBackRtcpAddr;
				if ( atVidParam[wIndex].m_bMap )
				{
					atDsData[wDsNum].m_tMapedAddr = ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;//映射成远端接收端口
				}											
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("CNodeFsmMgr::CreateMediaTrans rmt ep vid rcv invalid.confID:%d, speaker:%d, rmtep:%d, vidrcv:%d.\n"
				, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wVidRcvNum));
		}
		
		//////////////////////////////////////////////////////////////////////////
		//音频
		if ( ptNode->IsSingleAudRcv())
		{
			if ( tMixAud.m_tAddr.m_tRtpAddr.GetPort() != 0 )
			{//单屏先听混音
				atDsData[wDsNum].m_tRcvFromAddr = tMixAud.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atAudDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tMixAud.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowAudio();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tAud.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = tMixAud.m_tAddr.m_tBackRtcpAddr;									
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
			else if(atAudParam[MIDSCREENINDEX].m_tAddr.m_tRtpAddr.GetPort() != 0 
				&& atAudParam[MIDSCREENINDEX].m_tAddr.m_tBackRtcpAddr.GetPort() != 0)
			{//无 则听坐席 atAudParam中间位置存放的是目标的坐席
				atDsData[wDsNum].m_tRcvFromAddr = atAudParam[MIDSCREENINDEX].m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atAudDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = atAudParam[MIDSCREENINDEX].m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowAudio();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tAud.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = atAudParam[MIDSCREENINDEX].m_tAddr.m_tBackRtcpAddr;										
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
		}
		else if ( ptNode->IsThreeAudRcv())
		{
			for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			{
				if(atAudParam[wIndex].m_tAddr.m_tRtpAddr.GetPort() == 0)
				{
					continue;
				}
				
				atDsData[wDsNum].m_tRcvFromAddr = atAudParam[wIndex].m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = atAudParam[wIndex].m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowAudio();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = atAudParam[wIndex].m_tAddr.m_tBackRtcpAddr;										
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}

			if(ptNode->IsVRS() && ptNode->m_ptMixAddr != NULL && tMixAud.m_tAddr.m_tRtpAddr.m_wPort != 0)
			{//混音  三屏 vrs 才需要混音
				atDsData[wDsNum].m_tRcvFromAddr = tMixAud.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_tAudMixDec.m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tMixAud.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowAudio();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptMixAddr->m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = tMixAud.m_tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("CNodeFsmMgr::CreateMediaTrans rmt ep aud rcv invalid.confID:%d, speaker:%d, rmtep:%d, audrcv:%d.\n"
				, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		}
//	}
	

	//双流
	CDsStrategyToNodeForDual cDualStrate(ptNode->m_wEpID);
	wDsNum += cDualStrate.GetDsToNode(m_pcConf, atDsData + wDsNum, MAX_CHANNEL_DS_NUM - wDsNum);
	
	CNetPortMgr::MergerDsList(m_pcConf, ptNode->m_tDsList, atDsData, wDsNum, "CNodeFsmMgr::CreateMediaTrans");
}

void CNodeFsmMgr::CreateMediaTransUMS( TCapNode* ptNode, TTransParam atVidParam[], TTransParam atAudParam[] , 
							TTransParam& tMixVid, TTransParam& tMixAud )
{

	u16		wDsNum = 0;
	s32		symbolflag = 1;
	u16		wIndex = 1;
	u16		wCurIndex = 0;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	if ( ptNode->m_emLastObj == emObjChair
		&& ptNode->m_ptCasCadeChairAddr != NULL )
	{//走主席通道
		//主视频
		for ( wIndex = 1; wIndex <= ptNode->m_wVidRcvNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

			if(atVidParam[wCurIndex].m_tAddr.m_tRtpAddr.GetPort() == 0)
			{
				continue;
			}
			
			atDsData[wDsNum].m_tRcvFromAddr = atVidParam[wCurIndex].m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wCurIndex].m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = atVidParam[wCurIndex].m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_atVid[wCurIndex].m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = atVidParam[wCurIndex].m_tAddr.m_tBackRtcpAddr;
			if ( atVidParam[wCurIndex].m_bMap )
			{
				atDsData[wDsNum].m_tMapedAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wCurIndex].m_tChanAddr.m_tRtpAddr;//映射成远端接收端口
			}
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if (tMixVid.m_tAddr.m_tRtpAddr.m_wPort != 0)
		{
			atDsData[wDsNum].m_tRcvFromAddr = tMixVid.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tMixVid.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = tMixVid.m_tAddr.m_tBackRtcpAddr;
			if (tMixVid.m_bMap)
			{
				atDsData[wDsNum].m_tMapedAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;//映射成远端接收端口
			}
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		//主音频
		symbolflag = 1;
		for ( wIndex = 1; wIndex <= ptNode->m_wAudRcvNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

			if(atAudParam[wCurIndex].m_tAddr.m_tRtpAddr.GetPort() == 0)
			{
				continue;
			}
			
			atDsData[wDsNum].m_tRcvFromAddr = atAudParam[wCurIndex].m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wCurIndex].m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = atAudParam[wCurIndex].m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_atAud[wCurIndex].m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = atAudParam[wCurIndex].m_tAddr.m_tBackRtcpAddr;					
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
		
		if(ptNode->m_ptCasCadeChairAddr != NULL && tMixAud.m_tAddr.m_tRtpAddr.m_wPort != 0)
		{//混音
			atDsData[wDsNum].m_tRcvFromAddr = tMixAud.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tMixAud.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_tMixAud.m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = tMixAud.m_tAddr.m_tBackRtcpAddr;					
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	}
	else if ( ptNode->m_emLastObj == emObjSpeaker
		|| ptNode->m_emLastObj == emObjDiscard )
	{//看发言人 讨论  走发言人通道
		symbolflag = 1;
		for ( wIndex = 1; wIndex <= ptNode->m_wVidRcvNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
			
			if(atVidParam[wCurIndex].m_tAddr.m_tRtpAddr.GetPort() == 0)
			{
				continue;
			}
			
			atDsData[wDsNum].m_tRcvFromAddr = atVidParam[wCurIndex].m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atVidDec[wCurIndex].m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = atVidParam[wCurIndex].m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[wCurIndex]->m_tVid.m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = atVidParam[wCurIndex].m_tAddr.m_tBackRtcpAddr;
			if ( atVidParam[wCurIndex].m_bMap )
			{
				atDsData[wDsNum].m_tMapedAddr = ptNode->m_tRmtChan.m_atVidDec[wCurIndex].m_tChanAddr.m_tRtpAddr;//映射成远端接收端口
			}
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}


		BOOL32 bRollCallModle = m_pcConf->GetRollCallMgr()->IsRollCallModle();
        if (bRollCallModle)
		{
            //点名人主视频流  如果是点名模式，并且点名人在下级，通过主席通道向上级UMS打主席VID码流
            m_pcConf->GetRollCallMgr()->UploadRollCallerMainVid(ptNode, atDsData, wDsNum);

			//小码流 如果是点名模式,  如果发言人在下级并且发言人在合成，往上级打发言人的小码流
            //如果主席（点名人）在下级并且主席在合成，往上级打主席的小码流                    
			m_pcConf->GetRollCallMgr()->UploadRollCallerSmallVid( ptNode, atDsData, wDsNum);
		}
  

		if (!bRollCallModle
			&& ptNode->IsSmallVidRcv()
			&& ptNode->m_emLastObj == emObjSpeaker 
			&& ptNode->m_wEpID == CALLER_EP_INDEX 
			&& m_pcConf->curSpeakerID() != CALLER_EP_INDEX)
		{// 发言人在下级，给上级ums打小码流
			TCallNode* ptSpeakerNode = m_pcConf->GetNode(m_pcConf->curSpeakerID());
			TCapNode* ptSpeakerFartherNode = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptSpeakerNode);
			if (NULL != ptSpeakerNode && NULL != ptSpeakerFartherNode && ptSpeakerNode == ptSpeakerFartherNode 
				&& ptSpeakerFartherNode->IsSmallVidSnd())
			{
				for ( wIndex = 1; wIndex <= TP_MAX_STREAMNUM; ++wIndex, symbolflag *= -1)
				{
					wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
					
					atDsData[wDsNum].m_tRcvFromAddr = ptSpeakerFartherNode->m_aptSmallChanAddr[wCurIndex]->m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atSmallVidDec[wCurIndex].m_tChanAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptSpeakerFartherNode->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetSmallVideo(wCurIndex);
					++wDsNum;
					
					atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptSmallChanAddr[wCurIndex]->m_tRtcpForSnd;
					atDsData[wDsNum].m_tSndToAddr = ptSpeakerFartherNode->m_tRmtChan.m_atSmallVidEnc[wCurIndex].m_tChanAddr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
			}
		}




        symbolflag = 1;
		for ( wIndex = 1; wIndex <= ptNode->m_wAudRcvNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

			if(atAudParam[wCurIndex].m_tAddr.m_tRtpAddr.GetPort() == 0)
			{
				continue;
			}
			
			atDsData[wDsNum].m_tRcvFromAddr = atAudParam[wCurIndex].m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_atAudDec[wCurIndex].m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = atAudParam[wCurIndex].m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_aptChanAddr[wCurIndex]->m_tAud.m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = atAudParam[wCurIndex].m_tAddr.m_tBackRtcpAddr;										
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if( ptNode->m_ptMixAddr != NULL && tMixAud.m_tAddr.m_tRtpAddr.m_wPort != 0)
		{// 不包含双流的混音或者混音(讨论下)
			atDsData[wDsNum].m_tRcvFromAddr = tMixAud.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_tRmtChan.m_tAudMixDec.m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tMixAud.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowAudio();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptMixAddr->m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = tMixAud.m_tAddr.m_tBackRtcpAddr;
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}

		if (m_pcConf->IsChairConf() &&
			!m_pcConf->GetUmsDiscuss()->IsDiscussModle() && 
			NULL != ptNode->m_ptCasCadeChairAddr && 
			tMixVid.m_tAddr.m_tRtpAddr.m_wPort != 0)
		{
			atDsData[wDsNum].m_tRcvFromAddr = tMixVid.m_tAddr.m_tRtpAddr;
			atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;
			atDsData[wDsNum].m_dwEqpNode = tMixVid.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtpSwap;
			atDsData[wDsNum].SetUnknowVideo();
			++wDsNum;
			
			atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtcpForSnd;
			atDsData[wDsNum].m_tSndToAddr = tMixVid.m_tAddr.m_tBackRtcpAddr;
			if (tMixVid.m_bMap)
			{
				atDsData[wDsNum].m_tMapedAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;//映射成远端接收端口
			}
			atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
			++wDsNum;
		}
	} else if (ptNode->m_emLastObj == emObjSelf)
	{
        if ( m_pcConf->GetRollCallMgr()->IsRollCallModle())
		{
            //点名人主视频流  如果是点名模式，并且点名人在下级，通过主席通道向上级UMS打主席VID码流
            m_pcConf->GetRollCallMgr()->UploadRollCallerMainVid(ptNode, atDsData, wDsNum);

			//小码流 如果是点名模式,  如果发言人在下级并且发言人在合成，往上级打发言人的小码流
            //如果主席（点名人）在下级并且主席在合成，往上级打主席的小码流                    
			m_pcConf->GetRollCallMgr()->UploadRollCallerSmallVid( ptNode, atDsData, wDsNum);
		}

	} else
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmMgr::CreateMediaTransUMS UMS obj Invalid.confID:%d, speaker:%d, rmtep:%d, obj:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_emLastObj));
	}

	if ( m_pcConf->IsChairConf() )
	{//上级 创建到所有下级UMS的 讨论码流
		//讨论 单屏广播 视频+N模式音频(见下)   三屏广播（视频 + N模式音频）走 上下级UMS通道(见上)， 发言人码流走主席通道下传码流
		if ( m_pcConf->GetUmsDiscuss()->IsDiscussModle() )
		{	
			TTPMediaTransAddr tScrAdr;
			TServiceAddr tMixScrAud;
			TServiceAddr tVmpScrAddr;
			if (ptNode->IsVidRcvValid())
			{// 单屏广播视频 下级会打入虚拟发言人的mixvid中，占用下级的单屏vid适配
				
				if (m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat))
				{				
					m_pcConf->GetBas()->GetOutChnVidAddr(tScrAdr, m_pcConf->GetSpeaker().m_pcSingleBas, ptNode->m_tVidRcvFormat.m_tFormat);
					
					atDsData[wDsNum].m_tRcvFromAddr = tScrAdr.m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetBasVideo();
					++wDsNum;
					
					atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtcpForSnd;
					atDsData[wDsNum].m_tSndToAddr = tScrAdr.m_tBackRtcpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
				else
				{
					atDsData[wDsNum].m_tRcvFromAddr = m_pcConf->GetSingleVidDec().m_tRtpAddr;
					atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtpSwap;
					atDsData[wDsNum].SetUnknowVideo();
					++wDsNum;
					
					atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtcpForSnd;
					atDsData[wDsNum].m_tSndToAddr = m_pcConf->GetSingleNetBuf().m_tRcvRtcpAddr;
					atDsData[wDsNum].m_tMapedAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;
					atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
					atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
					++wDsNum;
				}
			}

			if (ptNode->IsAudRcvValid())
			{// 单屏广播n模式音频(包含双流声音)  下级会打入虚拟发言人的mixaud中，占用下级的单屏aud适配
				m_pcConf->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSingleScrEp, TP_MAX_STREAMNUM, ptNode->m_wEpID, FALSE, tMixScrAud);
				
				atDsData[wDsNum].m_tRcvFromAddr = tMixScrAud.m_tAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleAud.m_tChanAddr.m_tRtpAddr;
				atDsData[wDsNum].m_dwEqpNode = tMixScrAud.m_dwMediaNode;
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetUnknowAudio();
				++wDsNum;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_tDisSingleAud.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = tMixScrAud.m_tAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				++wDsNum;
			}
			
			//讨论下，如果发言会场在此ums下，发言会场目标也要下去，走主席通道（不会占用下级的vid适配），占用下级的主席aud适配
			TCallNode* ptSpeakerNode = m_pcConf->GetNodeMgr()->GetNodeUnderThisUms(ptNode, Inst()->curSpeakerID());
			if (NULL != ptSpeakerNode)
			{// 发言会场挂在这个ptnode下
				symbolflag = 1;
				for ( wIndex = 1; wIndex <= ptSpeakerNode->m_wVidRcvNum; ++wIndex, symbolflag *= -1)
				{// 发言会场目标的视频
					wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

					if (ptNode->IsVidRcvValid())
					{
						m_pcConf->GetUmsDiscuss()->GetObjVmpOutAddr(emDiscussObjForSpeakerEp, wCurIndex, tVmpScrAddr);
						
						atDsData[wDsNum].m_tRcvFromAddr = tVmpScrAddr.m_tAddr.m_tRtpAddr;
						atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wCurIndex].m_tChanAddr.m_tRtpAddr;
						atDsData[wDsNum].m_dwEqpNode = tVmpScrAddr.m_dwMediaNode;
						atDsData[wDsNum].m_emSwitchType = emRtpSwap;
						atDsData[wDsNum].SetVmpVideo();
						++wDsNum;
						
						atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_atVid[wCurIndex].m_tRtcpForSnd;
						atDsData[wDsNum].m_tSndToAddr = tVmpScrAddr.m_tAddr.m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
						++wDsNum;
					}

					if (ptSpeakerNode->IsThreeVidSnd())
					{// 发言人是三屏的时候，下传发言人需要的n模式（n-1模式走putaud）
						m_pcConf->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSpeakerEp, wCurIndex, ptSpeakerNode->m_wEpID, FALSE, tMixScrAud);
						
						if (!tMixScrAud.IsValidAddr())
						{
							continue;
						}
						
						atDsData[wDsNum].m_tRcvFromAddr = tMixScrAud.m_tAddr.m_tRtpAddr;
						atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wCurIndex].m_tChanAddr.m_tRtpAddr;
						atDsData[wDsNum].m_dwEqpNode = tMixScrAud.m_dwMediaNode;
						atDsData[wDsNum].m_emSwitchType = emRtpSwap;
						atDsData[wDsNum].SetUnknowAudio();
						++wDsNum;
						
						atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_atAud[wCurIndex].m_tRtcpForSnd;
						atDsData[wDsNum].m_tSndToAddr = tMixScrAud.m_tAddr.m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
						++wDsNum;
					}
				}
			}

			// SpecialEp在此ums下，相应的目标也要下去，依然走主席通道（不会占用下级的vid适配），占用下级的主席aud适配
			u16 wSpeacialEp = m_pcConf->GetUmsDiscuss()->GetSpeacialEp();
			TCallNode* pSpeacialNode = m_pcConf->GetNodeMgr()->GetNodeUnderThisUms(ptNode, wSpeacialEp);
			if (NULL != pSpeacialNode && pSpeacialNode->IsThreeVidSnd())
			{
				for (wCurIndex = 0; wCurIndex < TP_MAX_STREAMNUM; wCurIndex++)
				{

					if (ptNode->IsVidRcvValid() && MIDSCREENINDEX != wCurIndex)
					{
						m_pcConf->GetUmsDiscuss()->GetObjVmpOutAddr(emDiscussObjForSpeakerEp, wCurIndex, tVmpScrAddr);
						
						atDsData[wDsNum].m_tRcvFromAddr = tVmpScrAddr.m_tAddr.m_tRtpAddr;
						atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wCurIndex].m_tChanAddr.m_tRtpAddr;
						atDsData[wDsNum].m_dwEqpNode = tVmpScrAddr.m_dwMediaNode;
						atDsData[wDsNum].m_emSwitchType = emRtpSwap;
						atDsData[wDsNum].SetVmpVideo();
						++wDsNum;
						
						atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_atVid[wCurIndex].m_tRtcpForSnd;
						atDsData[wDsNum].m_tSndToAddr = tVmpScrAddr.m_tAddr.m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
						++wDsNum;
					}

					if (ptNode->IsAudRcvValid())
					{// 下传SpeaciaEp需要的n模式（n-1模式走putaud）
						m_pcConf->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSpeakerEp, wCurIndex, pSpeacialNode->m_wEpID, FALSE, tMixScrAud);
					
						if (!tMixScrAud.IsValidAddr())
						{
							continue;
						}
						
						atDsData[wDsNum].m_tRcvFromAddr = tMixScrAud.m_tAddr.m_tRtpAddr;
						atDsData[wDsNum].m_tSndToAddr = ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wCurIndex].m_tChanAddr.m_tRtpAddr;
						atDsData[wDsNum].m_dwEqpNode = tMixScrAud.m_dwMediaNode;
						atDsData[wDsNum].m_emSwitchType = emRtpSwap;
						atDsData[wDsNum].SetUnknowAudio();
						++wDsNum;
						
						atDsData[wDsNum].m_tRcvFromAddr = ptNode->m_ptCasCadeChairAddr->m_atAud[wCurIndex].m_tRtcpForSnd;
						atDsData[wDsNum].m_tSndToAddr = tMixScrAud.m_tAddr.m_tBackRtcpAddr;
						atDsData[wDsNum].m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
						atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
						++wDsNum;
					}
				}
			}
		}
	}

	//双流
	CDsStrategyToNodeForDual cDualStrate(ptNode->m_wEpID);
	wDsNum += cDualStrate.GetDsToNode(m_pcConf, atDsData + wDsNum, MAX_CHANNEL_DS_NUM - wDsNum);
	
	CNetPortMgr::MergerDsList(m_pcConf, ptNode->m_tDsList, atDsData, wDsNum, "CNodeFsmMgr::CreateMediaTrans");

	return ;
}

BOOL32 CNodeFsmMgr::CheckEmObj( EMScreenObj emObj )
{
	if ( emObj != emObjLookedEnd )
	{
		return TRUE;
	}
	return FALSE;
}

void CNodeFsmMgr::UpdateMediaTrans(TCapNode* ptNode, BOOL32 bYouAreSeeing /* = FALSE */)
{
	ChangeState(ptNode, bYouAreSeeing);
	return ;
}

void CNodeFsmMgr::UpdateMediaTrans(u16 wEpID, BOOL32 bYouAreSeeing /* = FALSE */)
{
	TCapNode* ptNode = m_pcConf->GetNodeMgr()->GetForeFatherNode(wEpID);
	if ( NULL == ptNode || !ptNode->IsChanOn() )
	{
		return ;
	}
	ChangeState(ptNode, bYouAreSeeing);
	return ;
}

void CNodeFsmMgr::ChangeSpeaker( TCapNode* ptNode)
{
	if ( NULL == ptNode )
	{
		return;
	}
	if ( !ptNode->IsChanOn() )
	{
		return ;
	}


    if ( ptNode->m_emLastObj == emObjDiscard )
	{
		ptNode->m_emLastObj = emObjDiscard;
	}
	else
	{
		EMScreenObj emOldObj = ptNode->m_emLastObj;

		TCapNode* ptSpeakerCap = m_pcConf->GetNodeMgr()->GetForeFatherNode(m_pcConf->curSpeakerID());
		if(( NULL == ptSpeakerCap || !ptSpeakerCap->IsChanOn()) && (!m_pcConf->GetVmp()->IsBrdVmp()) && (!m_pcConf->GetAudMix()->IsAudMixMode()))
		{
	
            return ;
		}

		if ( ptNode->m_wEpID == m_pcConf->curSpeakerID() || ptNode->m_wEpID == ptSpeakerCap->m_wEpID )
		{//发言人
			if ( ptNode->m_wEpID == m_pcConf->chairID() )
			{//主席 且为发言人
				if ( m_pcConf->IsChairConf() && m_pcConf->GetPollMgr()->IsPollStart() )
				{//优先看轮询
					ptNode->m_emLastObj = emObjPoll;
				}
				else
				{
					ptNode->m_emLastObj = emObjSelf;
				}
			}
			else
			{
				ptNode->m_emLastObj = emObjChair;
				if (ptNode->IsMcu())
				{// （合并mcu级联，到下级mcu只有一路音视频）这里切mcu为发言人，即mcu下级会场为发言人，让下级会场看广播码流，所以目标改为看发言人
                   ptNode->m_emLastObj = emObjSpeaker;
				}
			}
		}
		else
		{//非发言人
			if ( ptNode->m_wEpID == m_pcConf->chairID() )
			{//主席
				m_pcConf->GetPollMgr()->TrySuspendPoll();
			}
			ptNode->m_emLastObj = emObjSpeaker;
		}
	}

	EMScreenObj emObj;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (!CheckEmObj(ptNode->m_aemObj[wIndex]) )
		{
			continue;
		}

		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			continue;
		}

		if(m_acFsm[ptNode->m_aemObj[wIndex]]->GetStateForChangeSpeaker(ptNode, wIndex, emObj))
		{
			ptNode->m_aemObj[wIndex] = emObj;
		}
	}

	ChangeState(ptNode);

	return ;
}

void CNodeFsmMgr::StartDis( TCapNode* ptNode )
{
	NODE_FSM_CHECK

	ptNode->m_emLastObj = emObjDiscard;

	if ( ptNode->m_wEpID == m_pcConf->chairID() )
	{
		m_pcConf->GetPollMgr()->TrySuspendPoll();
	}

	EMScreenObj emObj;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (! CheckEmObj(ptNode->m_aemObj[wIndex]) )
		{
			continue;
		}

		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			continue;
		}

		if(m_acFsm[ptNode->m_aemObj[wIndex]]->GetStateForStartDis(ptNode, wIndex, emObj))
		{
			ptNode->m_aemObj[wIndex] = emObj;
		}	
	}

	ChangeState(ptNode);

	return ;
}

void CNodeFsmMgr::StopDis( TCapNode* ptNode )
{
	NODE_FSM_CHECK
	
	TCapNode* ptSpeakerCap = m_pcConf->GetNodeMgr()->GetForeFatherNode(m_pcConf->curSpeakerID());
	if( NULL == ptSpeakerCap || !ptSpeakerCap->IsChanOn() )
	{
		return ;
	}

	if ( ptNode->m_wEpID == m_pcConf->curSpeakerID() || ptNode->m_wEpID == ptSpeakerCap->m_wEpID)
	{
		if ( m_pcConf->IsChairConf() && ptNode->m_wEpID == m_pcConf->chairID() )
		{//主席 且为发言人
			if ( m_pcConf->GetPollMgr()->IsPollStart() )
			{//优先看轮询
				ptNode->m_emLastObj = emObjPoll;
			}
			else
			{
				ptNode->m_emLastObj = emObjSelf;
			}
		}
		else
		{
			ptNode->m_emLastObj = emObjChair;
		}
	}
	else
	{
		ptNode->m_emLastObj = emObjSpeaker;
	}

	EMScreenObj emObj;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (! CheckEmObj(ptNode->m_aemObj[wIndex]) )
		{
			continue;
		}

		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			continue;
		}
		
		if(m_acFsm[ptNode->m_aemObj[wIndex]]->GetStateForStopDis(ptNode, wIndex, emObj))
		{
			ptNode->m_aemObj[wIndex] = emObj;
		}	
	}
	
	ChangeState(ptNode);
	return ;
}

void CNodeFsmMgr::SelView( TCapNode* ptNode, u16 wScreenIndx)
{
	NODE_FSM_CHECK
		
	EMScreenObj emObj;

	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( wIndex != wScreenIndx && wScreenIndx != TP_MAX_STREAMNUM )
		{
			continue;
		}

		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			continue;
		}
		
		if (! CheckEmObj(ptNode->m_aemObj[wIndex]) )
		{
			continue;
		}
		
		if(m_acFsm[ptNode->m_aemObj[wIndex]]->GetStateForSelView(ptNode, wIndex, emObj))
		{
			ptNode->m_aemObj[wIndex] = emObj;
		}
	}
	
	ChangeState(ptNode);
	return ;
}

void CNodeFsmMgr::UnView( TCapNode* ptNode, u16 wScreenIndx)
{
	NODE_FSM_CHECK
		
	EMScreenObj emObj;
	
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( wIndex != wScreenIndx && wScreenIndx != TP_MAX_STREAMNUM )
		{
			continue;
		}

		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			continue;
		}

		if (! CheckEmObj(ptNode->m_aemObj[wIndex]) )
		{
			continue;
		}
		
		if(m_acFsm[ptNode->m_aemObj[wIndex]]->GetStateForUnView(ptNode, wIndex, emObj))
		{
			ptNode->m_aemObj[wIndex] = emObj;
		}
	}
	
	ChangeState(ptNode);
	return ;
}

void CNodeFsmMgr::StartVmpBrd( TCapNode* ptNode, u16 wScreenIndx)
{
	NODE_FSM_CHECK
		
	EMScreenObj emObj;
	
	if (! CheckEmObj(ptNode->m_aemObj[wScreenIndx]) )
	{
		return;
	}

	if ( !IsInSndRange(wScreenIndx, ptNode->m_wVidRcvNum) )
	{
		return;
	}

	if ( ptNode->m_wEpID == m_pcConf->chairID() )
	{
		m_pcConf->GetPollMgr()->TrySuspendPoll();
	}
	
	if(m_acFsm[ptNode->m_aemObj[wScreenIndx]]->GetStateForStartVmpBrd(ptNode, wScreenIndx, emObj))
	{
		ptNode->m_aemObj[wScreenIndx] = emObj;
	}
	
	ChangeState(ptNode);
	return ;
}

void CNodeFsmMgr::StopVmpBrd( TCapNode* ptNode, u16 wScreenIndx)
{
	NODE_FSM_CHECK
		
	EMScreenObj emObj;
	
	if (! CheckEmObj(ptNode->m_aemObj[wScreenIndx]) )
	{
		return;
	}

	if ( !IsInSndRange(wScreenIndx, ptNode->m_wVidRcvNum) )
	{
		return;
	}
	
	if(m_acFsm[ptNode->m_aemObj[wScreenIndx]]->GetStateForStopVmpBrd(ptNode, wScreenIndx, emObj))
	{
		ptNode->m_aemObj[wScreenIndx] = emObj;
	}
	
	ChangeState(ptNode);
	return ;
}

void CNodeFsmMgr::ChanConnect( TCapNode* ptNode )
{
	if ( NULL == ptNode )
	{
		return ;
	}
	if ( !ptNode->IsChanOn() )
	{
		return ;
	}

	//上线后初始化目标
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			ptNode->m_aemObj[wIndex] = emObjSelf;
		//	ptNode->m_emLastObj = emObjSelf;
		}
		else
		{
			if (m_pcConf->GetVmp()->IsBrdVmp() && MIDSCREENINDEX == wIndex)
			{
				ptNode->m_aemObj[wIndex] = emObjVmpBrd;
				ptNode->m_emLastObj = emObjVmpBrd;
				continue;
			}

			if (m_pcConf->GetUmsDiscuss()->IsDiscussModle())
			{
				ptNode->m_aemObj[wIndex] = emObjDiscard;
				ptNode->m_emLastObj = emObjDiscard;
				continue;
			}


			if( ptNode->m_wEpID == m_pcConf->curSpeakerID() )
			{
				if ( ptNode->m_wEpID == m_pcConf->chairID() )
				{
					ptNode->m_emLastObj = emObjSelf;
					ptNode->m_aemObj[wIndex] = emObjSelf;
				}
				else
				{
					ptNode->m_emLastObj = emObjChair;
					ptNode->m_aemObj[wIndex] = emObjChair;
				}
			}
			else
			{
				ptNode->m_aemObj[wIndex] = emObjSpeaker;
				ptNode->m_emLastObj = emObjSpeaker;
			}
		}
	}

	return ;
}

void CNodeFsmMgr::StartPoll( TCapNode* ptNode )
{
	NODE_FSM_CHECK

	if ( !m_pcConf->IsChairConf() || ptNode->m_wEpID != m_pcConf->chairID() )
	{
		return ;
	}

	ptNode->m_emLastObj = emObjPoll;
		
	EMScreenObj emObj;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (! CheckEmObj(ptNode->m_aemObj[wIndex]) )
		{
			continue;
		}

		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			continue;
		}
		
		if(m_acFsm[ptNode->m_aemObj[wIndex]]->GetStateForStartPoll(ptNode, wIndex, emObj))
		{
			ptNode->m_aemObj[wIndex] = emObj;
		}
	}
	
	ChangeState(ptNode);
	return ;
}

void CNodeFsmMgr::StopPoll( TCapNode* ptNode )
{
	NODE_FSM_CHECK
		
	if ( !m_pcConf->IsChairConf() || ptNode->m_wEpID != m_pcConf->chairID() )
	{
		return ;
	}
	
	if ( m_pcConf->GetUmsDiscuss()->IsDiscussModle() )
	{//讨论开启 看讨论
		ptNode->m_emLastObj = emObjDiscard;
	}
	else
	{
		if( ptNode->m_wEpID == m_pcConf->curSpeakerID() )
		{
			if ( m_pcConf->IsChairConf() && ptNode->m_wEpID == m_pcConf->chairID() )
			{//发言人兼主席
				ptNode->m_emLastObj = emObjSelf;
			}
			else
			{
				ptNode->m_emLastObj = emObjChair;
			}
		}
		else
		{
			ptNode->m_emLastObj = emObjSpeaker;
		}
	}

	EMScreenObj emObj;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (! CheckEmObj(ptNode->m_aemObj[wIndex]) )
		{
			continue;
		}

		if ( !IsInSndRange(wIndex, ptNode->m_wVidRcvNum) )
		{
			continue;
		}
		
		if(m_acFsm[ptNode->m_aemObj[wIndex]]->GetStateForStopPoll(ptNode, wIndex, emObj))
		{
			ptNode->m_aemObj[wIndex] = emObj;
		}	
	}
		
	ChangeState(ptNode);
}

void CNodeFsmMgr::AskKeyFrame( TCapNode* ptNode, u16 wScreenIndx, BOOL32 bBySys )
{
	NODE_FSM_CHECK
	
	if (! CheckEmObj(ptNode->m_aemObj[wScreenIndx]) )
	{
		return;
	}
	
	m_acFsm[ptNode->m_aemObj[wScreenIndx]]->AskKeyFrame(ptNode, wScreenIndx, bBySys);
	return ;
}

//////////////////////////////////////////////////////////////////////////
//CNodeFsm
void CNodeFsm::GetAudSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{

	if (!ptNode->IsAudRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsm::GetAudSrcAddr rmt ep aud rcv invalid.confID:%d, rmtep:%d, audrcv:%d\n"
			, m_pcConf->GetInsID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		return;
	}

	if (m_pcConf->GetUmsDiscuss()->IsDiscussModle())
	{
		GetDisAudSrcAddr(ptNode, wScreenIndx, tParam);
		return;
	} 
	else if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{
		m_pcConf->GetRollCallMgr()->GetRollCallSrcAud(wScreenIndx, ptNode, tParam);
		return;
	}
	else if (m_pcConf->GetAudMix()->IsAudMixMode())
	{
		GetAudSrcAddrInMixMode(ptNode, wScreenIndx, tParam);
		return;
	}
	else
	{
		// next
	}

	TCallNode* ptSpeaker = m_pcConf->GetNode(m_pcConf->curSpeakerID());	//发言人可以为任意EP
	TCapNode* ptForeSpeaker = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptSpeaker);
	if (NULL == ptSpeaker || NULL == ptForeSpeaker)
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmSpeaker::GetAudSrcAddr can not find speaker ep.confID:%d, speaker:%d, rmtep:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID));
		return ;
	}

	if ( ptNode->m_wEpID == m_pcConf->curSpeakerID() || ptNode->m_wEpID == ptForeSpeaker->m_wEpID)
	{//发言人 听主席
		
		if (ptNode->m_wEpID == m_pcConf->chairID())
		{// 发言人兼主席，不需要建到发言会场的音频交换
			return;
		}

		TCapNode* ptChair = m_pcConf->GetNodeMgr()->GetCapsetNode(m_pcConf->chairID());	//发言人可以为任意EP
		if (NULL == ptChair)
		{
			MdlError(Ums_Mdl_Call, ("CNodeFsmSpeaker::GetAudSrcAddr can not find speaker ep.confID:%d, speaker:%d, rmtep:%d\n"
				, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID));
			return ;
		}

		if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsChairNeedAudBas(ptForeSpeaker->m_tAudRcvFormat.m_tFormat.m_emFormat) )
		{//音频适配 需要优先接收
			TTPDsFrom tAddr;
			m_pcConf->GetBas()->GetChairAudBasOutAddr(wScreenIndx, ptForeSpeaker->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);

			tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
			tParam.m_dwEqpNode = tAddr.m_dwEqpNode;

			return ;
		}

		TTPTransAddr atChairRtp[TP_MAX_STREAMNUM];
		TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM];
		TTPTransAddr tChairMixRtp, tChairMixRtcp;
		u32 adwRtpEqpNode[TP_MAX_STREAMNUM];
		u32 dwMixAudEqpNode;

		CDSStrategyToSpeaker cStrate;
		cStrate.SetPara(ptChair, ptForeSpeaker, ptSpeaker, m_pcConf->IsChairConf());
		cStrate.GetAudAddr(m_pcConf, atChairRtp, atChairRtcp, tChairMixRtp, tChairMixRtcp, adwRtpEqpNode, dwMixAudEqpNode);

		if (ptChair->IsAudSndValid() && ptNode->IsAudRcvValid())
		{
			tParam.m_tAddr.m_tRtpAddr = atChairRtp[wScreenIndx];
			tParam.m_tAddr.m_tBackRtcpAddr = atChairRtcp[wScreenIndx];
			tParam.m_dwEqpNode = adwRtpEqpNode[wScreenIndx];
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("CNodeFsmSpeaker::GetAudSrcAddr chair rmt ep vid rcv invalid.confID:%d, speaker:%d, rmtep:%d, audrcv:%d\n"
							, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		}
	}
	else
	{//非发言人 听发言人
		if (ptSpeaker->IsAudSndValid() && ptNode->IsThreeAudRcv())
		{
			if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
			{//音频适配 需要优先接收
				TTPDsFrom tAddr;
				m_pcConf->GetBas()->GetSpeakerAudBasOutAddr(wScreenIndx, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
				
				tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tParam.m_dwEqpNode = tAddr.m_dwEqpNode;

				return ;
			}
		
			tParam.m_tAddr = m_pcConf->GetSpeakerAudDec(wScreenIndx);
			tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);

		}
		else if (ptSpeaker->IsAudSndValid() && ptNode->IsSingleAudRcv())
		{
			if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
			{//音频适配 需要优先接收
				TTPDsFrom tAddr;
				m_pcConf->GetBas()->GetSpeakerMixAudBasOutAddr(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
				
				tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
			}
			else 
			{
				//混音或者坐席
				tParam.m_tAddr = m_pcConf->GetSpeakerAudMix();
				tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
				tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			}
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("CNodeFsmSpeaker::GetAudSrcAddr speaker rmt ep vid rcv invalid.confID:%d, speaker:%d, rmtep:%d, audrcv:%d\n"
							, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		}
	}
	
	return ;
}

//////////////////////////////////////////////////////////////////////////
//Speaker
BOOL32 CNodeFsmSpeaker::GetStateForChangeSpeaker( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = ptNode->m_emLastObj;
	return TRUE;
}

BOOL32 CNodeFsmSpeaker::GetStateForStartDis( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{//直接冲发言人

	emObj = emObjDiscard;
	return TRUE;
}

BOOL32 CNodeFsmSpeaker::GetStateForSelView( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjView;
	return TRUE;
}

BOOL32 CNodeFsmSpeaker::GetStateForStartVmpBrd( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if( wScreenIndx == MIDSCREENINDEX )
	{
		emObj = emObjVmpBrd;
		return TRUE;
	}
	return FALSE;
}

void CNodeFsmSpeaker::GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{
	TCallNode* ptSpeaker = m_pcConf->GetNode(m_pcConf->curSpeakerID());	//发言人可以为任意EP
	TCapNode* ptForeSpeaker = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptSpeaker);
	if (NULL == ptSpeaker || NULL == ptForeSpeaker)
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmSpeaker::GetVidSrcAddr can not find speaker ep.confID:%d, speaker:%d, rmtep:%d\n"
							, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID));
		return ;
	}

	if( ptNode->IsVidRcvValid() )
	{
		u16 wSrcIndex = wScreenIndx;
		if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat) )
		{
			m_pcConf->GetBas()->GetOutChnSpeakerVidAddr(tParam.m_tAddr, wScreenIndx, ptNode->m_tVidRcvFormat.m_tFormat);
			tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;

		}
		else
		{
			tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerVidDec(wScreenIndx).m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetNetBufParam(wScreenIndx).m_tRcvRtcpAddr;
			tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			tParam.m_bMap = TRUE;
		}
		
// 老发言人平滑
		if (m_pcConf->oldSpeakerID() == ptNode->m_wEpID &&
			 IsInSndRange(wScreenIndx, ptSpeaker->m_wVidSndNum) )
		{
			TCheckIFrameBase tBase;
			TIFrameSndBySrc tSnd;
			tBase.m_emType = TP_IFrameCheck_ChairWait;
			tBase.m_wConfID = m_pcConf->GetInsID();
			tBase.m_wExpires = IFRAME_CHECK_TIMEOUT;
			
			tBase.m_dwIP = tParam.m_tAddr.m_tRtpAddr.GetIP();
			tBase.m_wPort = tParam.m_tAddr.m_tRtpAddr.GetPort();


			tSnd.m_dwCheckIp = ptForeSpeaker->m_aptChanAddr[wSrcIndex]->m_tVid.m_tRtpAddr.GetIP();
			tSnd.m_wCheckPort = ptForeSpeaker->m_aptChanAddr[wSrcIndex]->m_tVid.m_tRtpAddr.GetPort();
			
			tSnd.m_dwDstIp = ptNode->m_tRmtChan.m_atVidDec[wScreenIndx].m_tChanAddr.m_tRtpAddr.GetIP();
			tSnd.m_wDstPort = ptNode->m_tRmtChan.m_atVidDec[wScreenIndx].m_tChanAddr.m_tRtpAddr.GetPort();
			
//			tSnd.m_wRcvPort = tParam.m_tAddr.m_tRtpAddr.GetPort();
			tSnd.m_wRcvPort = m_pcConf->GetSpeakerVidDec(wScreenIndx).m_tRtpAddr.GetPort();

			
			CTpMsg cMsg;	
			cMsg.SetEvent(ev_media_ds_iframe_SndBySrc);
			cMsg.SetBody(&tBase, sizeof(tBase));
			cMsg.CatBody(&tSnd, sizeof(tSnd));
			cMsg.Post(UMS_MEDIATRANS_APP_INST, m_pcConf->GetConfEqpDs().m_dwEqpNode, UMS_CALL_APP_INST(m_pcConf->GetInsID()));
			
			MdlHint(Ums_Mdl_Call, ("CNodeFsmSpeaker::GetVidSrcAddr IframeCheck ConfID:%d, dstID:%d, wCurIndex:%d, localPort:%d, Dst("ADDRPORT_FORMAT")\n"
				,m_pcConf->GetInsID(), ptNode->m_wEpID, wScreenIndx, tBase.m_wPort, ADDRPORT(tSnd.m_dwDstIp, tSnd.m_wDstPort) ));
		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmSpeaker::GetVidSrcAddr rmt ep vid rcv invalid.confID:%d, speaker:%d, rmtep:%d, vidrcv:%d\n"
							, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wVidRcvNum));
	}
	return ;
}

void CNodeFsmSpeaker::GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam )
{//混音 合成视频
    
	if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{  // 点名模式下，点名人 和其他非被点人（发言人）会场 的OBJ 均为speaker,但 点名人听N-1 ,其他会场听N
        m_pcConf->GetRollCallMgr()->GetMixSrcAddr(ptNode, tVidParam, tAudParam);
		return;
	}


	if (m_pcConf->GetAudMix()->IsAudMixMode())
	{
		m_pcConf->GetAudMix()->GetMixAudSrcAddr(ptNode, tAudParam);
	}
	else if (ptNode->IsAudRcvValid())
	{
		if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
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
	}

	if (ptNode->IsVidRcvValid())
	{
		if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat) )
		{// 需要适配
			TTPMediaTransAddr tAddr;
			if (NULL != m_pcConf->GetSpeaker().m_pcSingleBas && m_pcConf->GetVmp()->IsSpeakerInVmp())
			{// 广播单屏适配（发言人合成图像）
				m_pcConf->GetBas()->GetOutChnVidAddr(tAddr, m_pcConf->GetSpeaker().m_pcSingleBas, ptNode->m_tVidRcvFormat.m_tFormat);
				tVidParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tVidParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tVidParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			}
			else
			{// 取发言人适配的坐席
				TCallNode* ptSpeakerNode = m_pcConf->GetNode(m_pcConf->curSpeakerID());
				if (NULL != ptSpeakerNode && ptSpeakerNode->IsChanOn())
				{
					u16 wSeatIndex = ptSpeakerNode->GetSpeaker();
					m_pcConf->GetBas()->GetOutChnSpeakerVidAddr(tVidParam.m_tAddr, wSeatIndex, ptNode->m_tVidRcvFormat.m_tFormat);
					tVidParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
					
				}
			}
		}
		else
		{//
			tVidParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSingleVidDec().m_tRtpAddr;
			tVidParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSingleNetBuf().m_tRcvRtcpAddr;
			tVidParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			tVidParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			tVidParam.m_bMap = TRUE;
		}
	}

	return ;
}

BOOL32 CNodeFsmSpeaker::GetStateForStartPoll( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}

	emObj = emObjPoll;
	return TRUE;
}

BOOL32 CNodeFsmSpeaker::AskKeyFrame( TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys )
{
	TCallNode* ptSpeaker = m_pcConf->GetNodeMgr()->GetNode(m_pcConf->curSpeakerID());
	if (NULL == ptSpeaker)
	{
		tpLowDtl(Ums_Mdl_Call, "CNodeFsmSpeaker::AskKeyFrame Failed! ConfID:%d, Speaker:%d, SrcID:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID);
		return FALSE;
	}

	u16 wDstChanIndex = GetDstIndexBySrcIndex(ptNode, ptSpeaker, wDecIndex);
	if ( m_pcConf->GetVmp()->IsSpeakerInVmp() && ptNode->IsSingleVidRcv() )
	{//发言人在合成 且 远端为单屏接收
		if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat) )
		{//优先单屏广播适配
			m_pcConf->GetBas()->AskFrameToScreenBas(m_pcConf->GetSpeaker().m_pcSingleBas);
		}
		else
		{
			if ( m_pcConf->IsChairConf() )
			{//上级直接向发言人合成请求
				m_pcConf->GetVmp()->AskFrameToSpeakerVmp(ptNode->m_tVidRcvFormat.m_tFormat);
			}
			else
			{//直接向上级的发言人合成请求
				m_pcConf->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeySpeakerVmp, 0, 0, bReqBySys);
			}
		}
	}
	else if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat) && ptSpeaker->IsVidSndValid() )
	{//需要适配 则向发言人适配通道请求
		m_pcConf->GetBas()->SeeSpeakerAskFrameToBas(wDstChanIndex);
	}
	else
	{//向目的终端请求
		m_pcConf->AskKeyByScreen(m_pcConf->curSpeakerID(), wDstChanIndex, EmAskKeySpeaker,0, 0, bReqBySys);
	}
	return TRUE;
}

void CNodeFsmSpeaker::GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj )
{
	if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{   //点名模式下， 发言人（被点名人） 的目标是点名人，不是会议的主席
        m_pcConf->GetRollCallMgr()->GetSpeakertObj(ptNode, wScreenIndx, tObj);
		return;
	}

	TSpeakerCapTr tSpeakerTr;
	m_pcConf->GetSpeakSndCap(m_pcConf->curSpeakerID(), tSpeakerTr);

	tObj.m_tAlias = tSpeakerTr.m_tEpAlias;
	tObj.m_emObj = emObjSpeaker;
	tObj.m_wScrIndx = wScreenIndx;
	if (tSpeakerTr.m_wVidSnd == 0)
	{// 所看目标无发送通道（例如掉线），统一发1，避免终端和t300出现看静态图片的情形
		tObj.m_wVidNum = 1;
		tObj.m_wAudNum = 1;
	}
	else
	{
		tObj.m_wVidNum = IsInSndRange(wScreenIndx, tSpeakerTr.m_wVidSnd) ? 1 : 0;
		tObj.m_wAudNum = IsInSndRange(wScreenIndx, tSpeakerTr.m_wAudSnd) ? 1 : 0;
	}
	
	return ;
}

//////////////////////////////////////////////////////////////////////////
//Dis

BOOL32 CNodeFsmDis::GetStateForStopDis( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if( ptNode->m_emLastObj == emObjSpeaker )
	{
		emObj = emObjSpeaker;
	}
	else if  ( ptNode->m_emLastObj == emObjChair )
	{
		emObj = emObjChair;
	}
	else if ( ptNode->m_emLastObj == emObjPoll )
	{
		emObj = emObjPoll;
	}
	else if (ptNode->m_emLastObj == emObjSelf )
	{
		emObj = emObjSelf;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL32 CNodeFsmDis::GetStateForSelView( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjView;
	return TRUE;
}

BOOL32 CNodeFsmDis::GetStateForStartVmpBrd( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( wScreenIndx != MIDSCREENINDEX )
	{
		return FALSE;
	}
	emObj = emObjVmpBrd;
	return TRUE;
}

BOOL32 CNodeFsmDis::GetStateForStartPoll( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjPoll;
	return TRUE;
}
void CNodeFsmDis::GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{
	if (!ptNode->IsVidRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmDis::GetVidSrcAddr rmt ep vid rcv invalid.confID:%d, rmtep:%d, vidrcv:%d\n"
							, m_pcConf->GetInsID(), ptNode->m_wEpID, ptNode->m_wVidRcvNum));
		return;
	}

	BOOL32 bFlag = m_pcConf->GetUmsDiscuss()->IsSpeacialEp(ptNode->m_wEpID); //special目标，中间从普通三屏目标中取，两边从发言会场目标中取

	if (!ptNode->IsUms() && (ptNode->m_wEpID == m_pcConf->curSpeakerID() || (bFlag && MIDSCREENINDEX != wScreenIndx)))
	{// 发言会场

		if (m_pcConf->IsChairConf())
		{// 在上级，从合成取
			TServiceAddr tScrAddr;
			m_pcConf->GetUmsDiscuss()->GetObjVmpOutAddr(emDiscussObjForSpeakerEp, wScreenIndx, tScrAddr);
			
			tParam.m_tAddr.m_tRtpAddr = tScrAddr.m_tAddr.m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
			tParam.m_dwEqpNode = tScrAddr.m_dwMediaNode;
		}
		else
		{// 在下级，从主席通道取
			TCapNode* ptChair = m_pcConf->GetNodeMgr()->GetCaller();
			if (NULL != ptChair->m_ptCasCadeChairAddr)
			{// 上级已经适配出此会场需要的码流，不需要过适配，直接取
				tParam.m_tAddr.m_tRtpAddr = ptChair->m_ptCasCadeChairAddr->m_atVid[wScreenIndx].m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wScreenIndx].m_tChanAddr.m_tBackRtcpAddr;
				tParam.m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
			}
		}
	}
	else if (ptNode->IsUms() || ptNode->IsThreeVidRcv())
	{// 非发言的三屏会场(包括ums)
		if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat) )
		{
			m_pcConf->GetBas()->GetOutChnSpeakerVidAddr(tParam.m_tAddr, wScreenIndx, ptNode->m_tVidRcvFormat.m_tFormat);
			tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
		}
		else
		{
			tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerVidDec(wScreenIndx).m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetNetBufParam(wScreenIndx).m_tRcvRtcpAddr;
			tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			tParam.m_bMap = TRUE;
		}
	}
	else
	{// 非发言的单屏会场
		if (m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat))
		{
			if (NULL != m_pcConf->GetSpeaker().m_pcSingleBas)
			{// 广播单屏适配
				m_pcConf->GetBas()->GetOutChnVidAddr(tParam.m_tAddr, m_pcConf->GetSpeaker().m_pcSingleBas, ptNode->m_tVidRcvFormat.m_tFormat);
				tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			}
			else
			{// 下级没有申请广播单屏适配，从广播三屏中选一路有发言会场或者有发言坐席的给单屏
				u16 wSeatIndex = MIDSCREENINDEX;  // 
				m_pcConf->GetBas()->GetOutChnSpeakerVidAddr(tParam.m_tAddr, wSeatIndex, ptNode->m_tVidRcvFormat.m_tFormat);
				tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
			}			
		}
		else
		{
			tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSingleVidDec().m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSingleNetBuf().m_tRcvRtcpAddr;
			tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			tParam.m_bMap = TRUE;
		}
		
		
	}
	return;
}

void CNodeFsm::GetDisAudSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{
	if (!ptNode->IsAudRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsm::GetDisAudSrcAddr rmt ep aud rcv invalid.confID:%d, rmtep:%d, audrcv:%d\n"
			, m_pcConf->GetInsID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		return;
	}

	BOOL32 bFlag = m_pcConf->GetUmsDiscuss()->IsSpeacialEp(ptNode->m_wEpID); //special目标，音频都从发言人三个取
	TServiceAddr tMixAud;

	TTPDsFrom  tAddr;
	if (!ptNode->IsUms() && (ptNode->m_wEpID == m_pcConf->curSpeakerID() || bFlag))
	{// 发言会场
		if (m_pcConf->IsChairConf())
		{// 在上级，从混音器取
			if (ptNode->IsThreeVidSnd())
			{
				m_pcConf->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSpeakerEp, wScreenIndx, ptNode->m_wEpID, FALSE, tMixAud);
			}
			else
			{// 发言会场是单屏的时候，听所有讨论会场的n-1模式混音
				m_pcConf->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSingleScrEp, TP_MAX_STREAMNUM, ptNode->m_wEpID, FALSE, tMixAud);
			}
			tParam.m_tAddr = tMixAud.m_tAddr;
			tParam.m_dwEqpNode = tMixAud.m_dwMediaNode;
		}
		else
		{// 下级讨论内发言会场或speial会场
			m_pcConf->GetUmsDiscuss()->GetMixOutAddrForDown(ptNode, wScreenIndx, tMixAud); 
			if (tMixAud.IsValidAddr())
			{
				tParam.m_tAddr = tMixAud.m_tAddr;
				tParam.m_dwEqpNode = tMixAud.m_dwMediaNode;
			}
			else
			{// 级联主席通道都是下级下传的n模式
				if (m_pcConf->GetBas()->IsChairNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat))
				{
					m_pcConf->GetBas()->GetChairAudBasOutAddr(wScreenIndx, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
					
					tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
					tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
					tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
				}
				else
				{
					TCapNode* ptChair = m_pcConf->GetNodeMgr()->GetCaller();
					if (NULL != ptChair->m_ptCasCadeChairAddr)
					{
						tParam.m_tAddr.m_tRtpAddr = ptChair->m_ptCasCadeChairAddr->m_atAud[wScreenIndx].m_tRtpAddr;
						tParam.m_tAddr.m_tBackRtcpAddr = ptChair->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wScreenIndx].m_tChanAddr.m_tBackRtcpAddr;
						tParam.m_dwEqpNode = ptChair->m_tMediaEqp.m_dwEqpNode;
					}
				}
			}
		}
	}
	else if (ptNode->IsUms() || ptNode->IsThreeAudRcv())
	{// 非发言的三屏(包括ums)		
		if (ptNode->IsInMix())
		{
			if (m_pcConf->IsChairConf())
			{
				m_pcConf->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForThreeScrEp, wScreenIndx, ptNode->m_wEpID, FALSE, tMixAud);
				tParam.m_tAddr = tMixAud.m_tAddr;
				tParam.m_dwEqpNode = tMixAud.m_dwMediaNode;
			}
			else
			{
				// 下级讨论内三屏会场
				m_pcConf->GetUmsDiscuss()->GetMixOutAddrForDown(ptNode, wScreenIndx, tMixAud);
				tParam.m_tAddr = tMixAud.m_tAddr;
				tParam.m_dwEqpNode = tMixAud.m_dwMediaNode;
			}
		}
		else
		{
			if (m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat))
			{// 从音频适配中取
				m_pcConf->GetBas()->GetSpeakerAudBasOutAddr(wScreenIndx, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
				tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
				tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
			}
			else
			{
				tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndx).m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndx).m_tBackRtcpAddr;
				tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			}
		}
	}
	else
	{// 非发言的单屏

		if (ptNode->IsInMix())
		{
			if (m_pcConf->IsChairConf())
			{
				m_pcConf->GetUmsDiscuss()->GetObjMixOutAddr(emDiscussObjForSingleScrEp, TP_MAX_STREAMNUM, ptNode->m_wEpID, FALSE, tMixAud);
				tParam.m_tAddr = tMixAud.m_tAddr;
				tParam.m_dwEqpNode = tMixAud.m_dwMediaNode;
			}
			else
			{
				// 下级讨论内单屏
				m_pcConf->GetUmsDiscuss()->GetMixOutAddrForDown(ptNode, wScreenIndx, tMixAud);
				tParam.m_tAddr = tMixAud.m_tAddr;
				tParam.m_dwEqpNode = tMixAud.m_dwMediaNode;
			}
		}
		else
		{// 上下级虚拟发言人audmix的声音是包含双流的混音(专门给单屏听)
			
			if (m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat))
			{// 从音频适配中取
				m_pcConf->GetBas()->GetSpeakerMixAudBasOutAddr(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
				tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
				tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
			}
			else
			{
				tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerAudMix().m_tRtpAddr;
				tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSpeakerAudMix().m_tBackRtcpAddr;
				tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			}
		}
	}
	return;
}

void CNodeFsm::GetAudSrcAddrInMixMode( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{
	if (!ptNode->IsAudRcvValid())
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsm::GetAudMixSrcAddr rmt ep aud rcv invalid.confID:%d, rmtep:%d, audrcv:%d\n"
			, m_pcConf->GetInsID(), ptNode->m_wEpID, ptNode->m_wAudRcvNum));
		return;
	}

	if (wScreenIndx != MIDSCREENINDEX)
	{// 会议混音模式下，只给中间屏打声音
		return;
	}

	TUmsAudMixEpInfo* ptEp = m_pcConf->GetAudMix()->GetMixEpForID(ptNode->m_wEpID);
	if (NULL != ptEp)
	{// 听n-1
		TServiceAddr tAudRcvAddr;
		m_pcConf->GetAudMix()->GetMixAudRcvAddrForMixEp(ptEp, tAudRcvAddr);
		tParam.m_dwEqpNode = tAudRcvAddr.m_dwMediaNode;
		tParam.m_tAddr.m_tRtpAddr = tAudRcvAddr.m_tAddr.m_tRtpAddr;
		tParam.m_tAddr.m_tBackRtcpAddr = tAudRcvAddr.m_tAddr.m_tBackRtcpAddr;
		return;
	}

	TTPDsFrom  tAddr;
	if (m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat))
	{// 从音频适配中取
		m_pcConf->GetBas()->GetSpeakerAudBasOutAddr(wScreenIndx, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
		tParam.m_dwEqpNode = tAddr.m_dwEqpNode;
		tParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
		tParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
	}
	else
	{
		tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndx).m_tRtpAddr;
		tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetSpeakerAudDec(wScreenIndx).m_tBackRtcpAddr;
		tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
		tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
	}

	return;
}

void CNodeFsmDis::GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam )
{
	if (!ptNode->IsAudRcvValid())
	{
		return;
	}

	if ((ptNode->IsVRS() || ptNode->IsUms()) &&  NULL != ptNode->m_ptMixAddr)
	{// 讨论下，双流同时开启，vrs优先录不含双流的n模式混音，其次录n模式混音）
		if (m_pcConf->IsChairConf())
		{ 
			if (m_pcConf->GetSpeaker().m_bIsDualMixOn)
			{
				TServiceAddr tScrAddr;
				m_pcConf->GetEapu()->GetMixerChnOutAddr(m_pcConf->GetSpeaker().m_ptAudMix, tScrAddr, m_pcConf->GetDualMgr()->GetDualID(), 4);
				if (tScrAddr.IsValidAddr())
				{
					tAudParam.m_tAddr.m_tRtpAddr = tScrAddr.m_tAddr.m_tRtpAddr;
					tAudParam.m_tAddr.m_tBackRtcpAddr = tScrAddr.m_tAddr.m_tBackRtcpAddr;
					tAudParam.m_dwEqpNode = tScrAddr.m_dwMediaNode;
					return;
				}
			}

			if (m_pcConf->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
			{
				TTPDsFrom tAddr;
				m_pcConf->GetBas()->GetSpeakerMixAudBasOutAddr(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
				tAudParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
				tAudParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
				tAudParam.m_dwEqpNode = tAddr.m_dwEqpNode;
			}
			else
			{
				tAudParam.m_tAddr = m_pcConf->GetSpeakerAudMix();
				tAudParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
				tAudParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			}
		}
		else
		{
			// 上级下传下来的audmix
			TCapNode* ptCaller = m_pcConf->GetNodeMgr()->GetCaller();
			if (NULL != ptCaller && NULL != ptCaller->m_ptMixAddr)
			{ 
				tAudParam.m_tAddr.m_tRtpAddr = ptCaller->m_ptMixAddr->m_tRtpAddr;
				tAudParam.m_tAddr.m_tBackRtcpAddr = ptCaller->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
				tAudParam.m_dwEqpNode = ptCaller->m_tMediaEqp.m_dwEqpNode;
			}
		}
	}

	return;
}

BOOL32 CNodeFsmDis::AskKeyFrame( TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys )
{
	m_pcConf->GetUmsDiscuss()->AskKeyFrameFromEp(ptNode, wDecIndex, bReqBySys);
	return TRUE;
}

void CNodeFsmDis::GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj )
{
	m_pcConf->GetUmsDiscuss()->GetDiscussObjInfo(ptNode, tObj, wScreenIndx);
	return ;
}

//////////////////////////////////////////////////////////////////////////
//VmpBrd

BOOL32 CNodeFsmVmpBrd::GetStateForSelView( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjView;
	return TRUE;
}

BOOL32 CNodeFsmVmpBrd::GetStateForStopVmpBrd( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{//讨论或者发言人
	if( ptNode->m_emLastObj == emObjSpeaker )
	{
		emObj = emObjSpeaker;
	}
	else if  ( ptNode->m_emLastObj == emObjChair )
	{
		emObj = emObjChair;
	}
	else if ( ptNode->m_emLastObj == emObjDiscard )
	{
		emObj = emObjDiscard;
	}
	else if ( ptNode->m_emLastObj == emObjPoll )
	{
		emObj = emObjPoll;
	}
	else if (ptNode->m_emLastObj == emObjSelf)
	{
		emObj = emObjSelf;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

void CNodeFsmVmpBrd::GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{//合成 从虚拟发言人接收 先前已经打入到虚拟发言人中了
	if( ptNode->IsVidRcvValid() )
	{
		if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat, wScreenIndx) )
		{
			m_pcConf->GetBas()->GetOutChnSpeakerVidAddr(tParam.m_tAddr, wScreenIndx, ptNode->m_tVidRcvFormat.m_tFormat);
			tParam.m_dwEqpNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
		}
		else
		{
			tParam.m_tAddr.m_tRtpAddr = m_pcConf->GetSpeakerVidDec(wScreenIndx).m_tRtpAddr;
			tParam.m_tAddr.m_tBackRtcpAddr = m_pcConf->GetNetBufParam(wScreenIndx).m_tRcvRtcpAddr;
			tParam.m_dwEqpNode = ptNode->m_tMediaEqp.m_dwEqpNode;
			tParam.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			tParam.m_bMap = TRUE;
		}

		
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmVmpBrd::GetVidSrcAddr rmt ep vid rcv invalid.confID:%d, speaker:%d, rmtep:%d, vidrcv:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wVidRcvNum));
	}
	
	return ;
}

BOOL32 CNodeFsmVmpBrd::AskKeyFrame( TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys )
{
	if ( m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat, MIDSCREENINDEX))
	{//需要适配 则向发言人适配通道请求
		m_pcConf->GetBas()->SeeSpeakerAskFrameToBas(MIDSCREENINDEX);
	}
	else
	{//向广播合成请求
		if ( m_pcConf->IsChairConf() )
		{
			m_pcConf->GetVmp()->AskFrameToBrdVmp(m_pcConf->GetVmp()->GetConfBrdVmp(), ptNode->m_wEpID);
		}
		else
		{
			m_pcConf->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeyBrdVmp, ptNode->m_wEpID);
		}
	}
	return TRUE;
}

void CNodeFsmVmpBrd::GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj )
{
	if ( wScreenIndx != MIDSCREENINDEX )
	{
		return ;
	}

	TSpeakerCapTr tSpeakerTr;
	m_pcConf->GetChairSndCap(m_pcConf->chairID(), tSpeakerTr);

	tObj.m_tAlias.SetAlias(m_pcConf->GetVmp()->GetBrdVmpAlias());
	tObj.m_emObj = emObjVmpBrd;
	tObj.m_wScrIndx = wScreenIndx;
	tObj.m_wVidNum = 1;
	tObj.m_wAudNum = 1;
}

//////////////////////////////////////////////////////////////////////////
//View
BOOL32 CNodeFsmView::GetStateForUnView( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{//合成广播、讨论、发言人
	if ( wScreenIndx == MIDSCREENINDEX && m_pcConf->GetVmp()->IsBrdVmp() )
	{//优先合成广播
		emObj = emObjVmpBrd;
		return TRUE;
	}
	if( ptNode->m_emLastObj == emObjSpeaker )
	{
		emObj = emObjSpeaker;
	}
	else if  ( ptNode->m_emLastObj == emObjChair )
	{
		emObj = emObjChair;
	}
	else if ( ptNode->m_emLastObj == emObjDiscard )
	{
		emObj = emObjDiscard;
	}
	else if ( ptNode->m_emLastObj == emObjPoll )
	{
		emObj = emObjPoll;
	}
	else if ( ptNode->m_emLastObj == emObjSelf )
	{
		emObj = emObjSelf;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

void CNodeFsmView::GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{
	if (!ptNode->IsVidRcvValid())
	{
		return;
	}

	m_pcConf->GetSelMgr()->GetSelSrcAddr(ptNode->m_wEpID, wScreenIndx, tParam.m_tAddr, tParam.m_dwEqpNode);
	return ;
}

BOOL32 CNodeFsmView::AskKeyFrame( TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys )
{
	m_pcConf->GetSelMgr()->AskKeyFrame(ptNode->m_wEpID, wDecIndex);
	return TRUE;
}

void CNodeFsmView::GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj )
{
	tObj.m_emObj = emObjView;
	tObj.m_wAudNum = 1;
	tObj.m_tAlias.SetAlias(m_pcConf->GetSelMgr()->GetSelObj(ptNode->m_wEpID, wScreenIndx, tObj.m_wVidNum));
}

//////////////////////////////////////////////////////////////////////////
//chair
BOOL32 CNodeFsmChair::GetStateForChangeSpeaker( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = ptNode->m_emLastObj;
	return TRUE;
}

BOOL32 CNodeFsmChair::GetStateForStartDis( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = emObjDiscard;
	return TRUE;
}

BOOL32 CNodeFsmChair::GetStateForSelView( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjView;
	return TRUE;
}

BOOL32 CNodeFsmChair::GetStateForStartVmpBrd( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if( wScreenIndx == MIDSCREENINDEX )
	{
		emObj = emObjVmpBrd;
		return TRUE;
	}
	return FALSE;
}

void CNodeFsmChair::GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{
    if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{   //看点名人
        m_pcConf->GetRollCallMgr()->GetTargetVidSrcAddr(wScreenIndx, ptNode, tParam);
		return;
	}

	TCapNode* ptChair = m_pcConf->GetNodeMgr()->GetCapsetNode(m_pcConf->chairID());
	if (NULL == ptChair)
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmChair::GetVidSrcAddr can not find speaker ep.confID:%d, speaker:%d, rmtep:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID));
		return ;
	}

	if( ptNode->IsVidRcvValid() )
	{
		TTPTransAddr atChairRtp[TP_MAX_STREAMNUM];
		TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM];
		u32 adwRtpEqpNode[TP_MAX_STREAMNUM];
		
		CDSStrategyToSpeaker cStrate;
		cStrate.SetPara(ptChair, NULL, NULL, m_pcConf->IsChairConf());
		cStrate.GetVidAddr(m_pcConf, atChairRtp, atChairRtcp, adwRtpEqpNode);

		tParam.m_tAddr.m_tRtpAddr = atChairRtp[wScreenIndx];
		tParam.m_tAddr.m_tBackRtcpAddr = atChairRtcp[wScreenIndx];
		tParam.m_dwEqpNode = adwRtpEqpNode[wScreenIndx];
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmChair::GetVidSrcAddr rmt ep vid rcv invalid.confID:%d, speaker:%d, rmtep:%d, vidrcv:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID, ptNode->m_wVidRcvNum));
	}

	return ;
}

void CNodeFsmChair::GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam )
{

    if(m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{
        m_pcConf->GetRollCallMgr()->GetTargetMixSrcAddr( ptNode, tVidParam, tAudParam );
		return;
	}


	TCapNode* ptChair = m_pcConf->GetNodeMgr()->GetCapsetNode(m_pcConf->chairID());
	if (NULL == ptChair)
	{
		MdlError(Ums_Mdl_Call, ("CNodeFsmChair::GetMixSrcAddr can not find speaker ep.confID:%d, speaker:%d, rmtep:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->curSpeakerID(), ptNode->m_wEpID));
		return ;
	}

	if (ptNode->IsVidRcvValid())
	{
		if ( m_pcConf->GetVmp()->IsChairInVmp() || (ptNode->IsUms() && m_pcConf->GetVmp()->IsChairOrSpeakerInVmp()))
		{// 
			TTPDsFrom tAddr;
			m_pcConf->GetVmp()->GetSpeakerVmpOutAddr(tAddr);
			tVidParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
			tVidParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
			tVidParam.m_dwEqpNode = tAddr.m_dwEqpNode;
		}
		else
		{//取坐席
			TTPTransAddr atChairRtp[TP_MAX_STREAMNUM];
			TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM];
			u32 adwRtpEqpNode[TP_MAX_STREAMNUM];
			
			CDSStrategyToSpeaker cStrate;
			cStrate.SetPara(ptChair, NULL, NULL, m_pcConf->IsChairConf());
			cStrate.GetVidAddr(m_pcConf, atChairRtp, atChairRtcp, adwRtpEqpNode);
			
			tVidParam.m_tAddr.m_tRtpAddr = atChairRtp[m_pcConf->GetChairCap().m_wSpeakerIndex];
			tVidParam.m_tAddr.m_tBackRtcpAddr = atChairRtcp[m_pcConf->GetChairCap().m_wSpeakerIndex];
			tVidParam.m_dwEqpNode = adwRtpEqpNode[m_pcConf->GetChairCap().m_wSpeakerIndex];
		}
	}

	if (m_pcConf->GetAudMix()->IsAudMixMode())
	{
		m_pcConf->GetAudMix()->GetMixAudSrcAddr(ptNode, tAudParam);
	}
	else if (ptNode->IsAudRcvValid())
	{
		if ( m_pcConf->IsAudNeedBas() && m_pcConf->GetBas()->IsChairNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat) )
		{//音频适配 需要优先接收
			TTPDsFrom tAddr;//主席混音 进中间位置
			m_pcConf->GetBas()->GetChairAudBasOutAddr( MIDSCREENINDEX, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tAddr);
			
			tAudParam.m_tAddr.m_tRtpAddr = tAddr.m_tRtpAddr;
			tAudParam.m_tAddr.m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
			tAudParam.m_dwEqpNode = tAddr.m_dwEqpNode;
		}
		else if ( NULL != m_pcConf->GetSpeaker().m_ptAudMix && m_pcConf->GetSpeaker().m_bIsDualMixOn && !ptNode->IsUms() )
		{//优先有双流声音的音频
			TServiceAddr tMixAddr;
			m_pcConf->GetEapu()->GetMixerChnOutAddr(m_pcConf->GetSpeaker().m_ptAudMix, tMixAddr, m_pcConf->curSpeakerID(), TP_MAX_STREAMNUM);
			
			tAudParam.m_dwEqpNode = tMixAddr.m_dwMediaNode;
			tAudParam.m_tAddr.m_tRtpAddr = tMixAddr.m_tAddr.m_tRtpAddr;
			tAudParam.m_tAddr.m_tBackRtcpAddr = tMixAddr.m_tAddr.m_tBackRtcpAddr;
		}
		else
		{
			TTPTransAddr atChairRtp[TP_MAX_STREAMNUM];
			TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM];
			TTPTransAddr tChairMixRtp, tChairMixRtcp;
			u32 adwRtpEqpNode[TP_MAX_STREAMNUM];
			u32 dwMixAudEqpNode;
			
			CDSStrategyToSpeaker cStrate;
			cStrate.SetPara(ptChair, NULL, NULL, m_pcConf->IsChairConf());
			cStrate.GetAudAddr(m_pcConf, atChairRtp, atChairRtcp, tChairMixRtp, tChairMixRtcp, adwRtpEqpNode, dwMixAudEqpNode);
			
			if( tChairMixRtp.m_wPort != 0 && dwMixAudEqpNode != 0 )
			{//取混音
				tAudParam.m_dwEqpNode = dwMixAudEqpNode;
				
				tAudParam.m_tAddr.m_tRtpAddr = tChairMixRtp;
				tAudParam.m_tAddr.m_tBackRtcpAddr = tChairMixRtcp;
			}
			else
			{//取坐席
				tAudParam.m_dwEqpNode = adwRtpEqpNode[m_pcConf->GetChairCap().m_wSpeakerIndex];
				tAudParam.m_tAddr.m_tRtpAddr = atChairRtp[m_pcConf->GetChairCap().m_wSpeakerIndex];
				tAudParam.m_tAddr.m_tBackRtcpAddr = atChairRtcp[m_pcConf->GetChairCap().m_wSpeakerIndex];
			}
		}
	}

	return ;
}

BOOL32 CNodeFsmChair::AskKeyFrame( TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys )
{
	if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{
        return m_pcConf->GetRollCallMgr()->AskKeyFrameToChair(ptNode, wDecIndex, bReqBySys);
	}

	TCallNode* ptChair = m_pcConf->GetNodeMgr()->GetNode(m_pcConf->chairID());
	if (NULL == ptChair)
	{
		tpLowDtl(Ums_Mdl_Call, "CNodeFsmChair::AskKeyFrame Failed! ConfID:%d, chair:%d, SrcID:%d\n"
			, m_pcConf->GetInsID(), m_pcConf->chairID(), ptNode->m_wEpID);
		return FALSE;
	}

	u16 wDstChanIndex = MIDSCREENINDEX;
	if( m_pcConf->IsChairConf() )
	{
		wDstChanIndex = GetDstIndexBySrcIndex(ptNode, ptChair, wDecIndex);
	}
	else
	{//此时主席坐席m_tSuperChairCap
		wDstChanIndex = GetDstIndexBySrcIndex(ptNode, (&m_pcConf->GetSuperChairCap()), wDecIndex);
	}

	if ( m_pcConf->GetVmp()->IsChairInVmp() && ptNode->IsSingleVidRcv() )
	{//主席在合成 且 发言人为单屏接收  则向请求合成器
	//	if ( CTpTypeAdpt::IsVidTransNeedBas(ptChair->m_tVidSndFormat.m_tFormat, ptNode->m_tVidRcvFormat.m_tFormat) )
	//	{//优先单屏广播适配
	//		m_pcConf->GetBas()->AskFrameToScreenBas(m_pcConf->GetSpeaker().m_pcSingleBas);
	//	}
	//	else
		{
			if ( m_pcConf->IsChairConf() )
			{//上级直接向发言人合成请求
				m_pcConf->GetVmp()->AskFrameToSpeakerVmp(ptNode->m_tVidRcvFormat.m_tFormat);
			}
			else
			{//直接向上级的发言人合成请求
				m_pcConf->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeySpeakerVmp);
			}
		}
	}
	else if ( m_pcConf->GetBas()->IsChairInBas() && ptChair->IsVidSndValid() )
	{//主席在适配中 则向主席适配通道请求
		m_pcConf->GetBas()->SeeChairAskFrameToBas(wDstChanIndex);
	}
	else
	{//向目的终端请求
		m_pcConf->AskKeyByScreen(m_pcConf->chairID(), wDstChanIndex, EmAskKeyChair);
	}

	return TRUE;
}

void CNodeFsmChair::GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj )
{
    if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{
        m_pcConf->GetRollCallMgr()->GetChairObj(ptNode, wScreenIndx, tObj);
		return;
	}

	TSpeakerCapTr tChairTr;
	m_pcConf->GetChairSndCap(m_pcConf->chairID(), tChairTr);
	tObj.m_tAlias = tChairTr.m_tEpAlias;
	tObj.m_emObj = emObjChair;
	tObj.m_wScrIndx = wScreenIndx;
	if (tChairTr.m_wVidSnd == 0)
	{// 所看目标无发送通道（例如掉线），统一发1，避免终端和t300出现看静态图片的情形
		tObj.m_wVidNum = 1;
		tObj.m_wAudNum = 1;
	}
	else
	{
		tObj.m_wVidNum = IsInSndRange(wScreenIndx, tChairTr.m_wVidSnd) ? 1 : 0;
		tObj.m_wAudNum = IsInSndRange(wScreenIndx, tChairTr.m_wAudSnd) ? 1 : 0;
	}
	return ;
}

//////////////////////////////////////////////////////////////////////////
//Poll

void CNodeFsmPoll::GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam )
{
	if (!ptNode->IsVidRcvValid())
	{
		return;
	}
	m_pcConf->GetPollMgr()->GetLocalPollOutAddr(tParam.m_tAddr, tParam.m_dwEqpNode, wScreenIndx);
}

BOOL32 CNodeFsmPoll::GetStateForStartVmpBrd( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( wScreenIndx == MIDSCREENINDEX)
	{//优先合成广播
		emObj = emObjVmpBrd;
		return TRUE;
	}
	return FALSE;
}

BOOL32 CNodeFsmPoll::GetStateForStopPoll( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( m_pcConf->GetUmsDiscuss()->IsDiscussModle() )
	{
		emObj = emObjDiscard;
	}
	else
	{
		if ( ptNode->m_wEpID == m_pcConf->curSpeakerID() )
		{
			emObj = emObjSelf;
		}
		else
		{
			emObj = emObjSpeaker;
		}
	}

	return TRUE;
}

BOOL32 CNodeFsmPoll::GetStateForStartPoll( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjPoll;
	return TRUE;
}

BOOL32 CNodeFsmPoll::GetStateForChangeSpeaker( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = ptNode->m_emLastObj;
	return TRUE;
}

BOOL32 CNodeFsmPoll::GetStateForStartDis( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = emObjDiscard;
	return TRUE;
}

BOOL32 CNodeFsmPoll::GetStateForStopVmpBrd( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = emObjPoll;
	return TRUE;
}

BOOL32 CNodeFsmPoll::GetStateForSelView( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjView;
	return TRUE;
}

BOOL32 CNodeFsmPoll::GetStateForStopDis( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = emObjPoll;
	return TRUE;
}

void CNodeFsmPoll::GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj )
{
	TPollAddrEx* ptCurAddr = m_pcConf->GetPollMgr()->GetCurAddr();

	tObj.m_emObj = emObjPoll;

	TCallNode* ptPoll = m_pcConf->GetNodeMgr()->GetNode(ptCurAddr->m_wPollEpID);
	if ( NULL != ptPoll && ptPoll->IsChanOn() )
	{
		tObj.m_tAlias = ptPoll->m_tConfName;
		tObj.m_wVidNum = IsInSndRange(wScreenIndx, ptPoll->m_wVidSndNum) ? 1 : 0;
	}
	tObj.m_wAudNum = 1;
}

BOOL32 CNodeFsmPoll::AskKeyFrame( TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys )
{
	m_pcConf->GetPollMgr()->AskKeyFrame(wDecIndex, bReqBySys);
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//Self

BOOL32 CNodeFsmSelf::AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys)
{
	if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{
		if (m_pcConf->IsChairConf())
		{
			//  ptNode 为会议主席且为发言人（被点名人） ，此时ptNode看点名人
			return m_pcConf->GetRollCallMgr()->AskKeyFrameToChair(ptNode, wDecIndex, bReqBySys);

		}
	}


	return FALSE;
}



void CNodeFsmSelf::GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj)
{
	if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{
		if (m_pcConf->IsChairConf())
		{ //  ptNode 为会议主席且为发言人（被点名人） ，此时ptNode看点名人
            m_pcConf->GetRollCallMgr()->GetChairObj(ptNode, wScreenIndx, tObj);

          //  ptNode 为会议主席且为发言人（被点名人）, 设置OBJ 目标为看远端（即CNS 显示UMS 打过来的码流）
		  //  ptNode 为会议主席时  如果给会场发送OBJ = Chair 则CNS 看本地， 这与看点名人不符
          tObj.m_emObj    = emObjSpeaker;
		}

		return;
	}

    //
	return;
}



void CNodeFsmSelf::GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam)
{
	
    if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{
        if (m_pcConf->IsChairConf())
		{ //  ptNode 为会议主席且为发言人（被点名人） ，此时ptNode看点名人
            m_pcConf->GetRollCallMgr()->GetTargetVidSrcAddr(wScreenIndx, ptNode, tParam);
		} else 
		{ //Node65 obj为self (发言人在上级，被点名人在下级)
			
			tParam.m_dwEqpNode = 0;
	        tParam.m_tAddr.Clear();
		}

		return;
	}


	tParam.m_dwEqpNode = 0;
	tParam.m_tAddr.Clear();
	return;
}


void CNodeFsmSelf::GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam)
{
    if (m_pcConf->GetRollCallMgr()->IsRollCallModle())
	{   
        if (m_pcConf->IsChairConf())
		{//  ptNode 为会议主席且为发言人（被点名人） ，此时ptNode看点名人
			m_pcConf->GetRollCallMgr()->GetTargetMixSrcAddr( ptNode, tVidParam, tAudParam );
		}
		
		return;
	}else if (m_pcConf->GetAudMix()->IsAudMixMode())
	{
		m_pcConf->GetAudMix()->GetMixAudSrcAddr(ptNode, tAudParam);
	}

	//
    return;
}



BOOL32 CNodeFsmSelf::GetStateForChangeSpeaker( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = ptNode->m_emLastObj;
	return TRUE;
}

BOOL32 CNodeFsmSelf::GetStateForStartDis( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = emObjDiscard;
	return TRUE;
}

BOOL32 CNodeFsmSelf::GetStateForSelView( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	emObj = emObjView;
	return TRUE;
}

BOOL32 CNodeFsmSelf::GetStateForStartVmpBrd( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( wScreenIndx == MIDSCREENINDEX )
	{
		emObj = emObjVmpBrd;
		return TRUE;
	}
	
	return FALSE;
}

BOOL32 CNodeFsmSelf::GetStateForStartPoll( TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj )
{
	if ( ptNode->IsUms() )
	{
		return FALSE;
	}
	emObj = emObjPoll;
	return TRUE;
}


