#include "dualmgr.h"
#include "umsconfinst.h"
#include "callnodemgr.h"
#include "eventoutumscall.h"
#include "eventoutsipadapter.h"
#include "innereventumscall.h"
#include "umsnetportmgr.h"
#include "umsstackinterface.h"
#include "innereventumsconf.h"
#include "callmgr.h"
#include "umsconfigex.h"
#include "umsbas.h"
#include "nodefsm.h"
#include "tperrno.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpumix.h"
#endif

CDualMgr::CDualMgr(CUmsConfInst* pcInst)
:CTpHandler(pcInst)
,m_bStart(FALSE)
,m_wCurDual(TP_INVALID_INDEX)
,m_wReqDual(TP_INVALID_INDEX)
,m_wNextDual(TP_INVALID_INDEX)
{
	m_tDualDsEpToUms.Clear();
	m_tToUpUms.Clear();
	m_wChairReq = TP_INVALID_INDEX;
}


CDualMgr::~CDualMgr()
{
}

	
BOOL32 CDualMgr::Create()
{
	return TRUE;
}

BOOL32 CDualMgr::Handler( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	switch (ptMsg->GetEvent())
	{
	case ev_OpenDualChan_Incoming:
		OnDualIncoming(ptMsg);
		break;
	case ev_OpenDualChan_Connect:
		OnDualChanConnect(ptMsg);
		break;
	case ev_DualChan_DisConnect:
		OnDualChanDisConnect(ptMsg);
		break;

	case evtp_Conf_RequestDualStream_cmd:
		OnReqDualStreamCmd(ptMsg);
		break;
	case evtp_Conf_RequestDualStream_Ind:
		OnReqDualStreamInd(ptMsg);
		break;
	case evtp_Conf_StopRcvDual_Ind:
		OnStopRcvDual(ptMsg);
		break;
	case evtp_cascade_OpenDualChan_Cmd:
		OnOpenCasecadeDualChanCmd(ptMsg);
		break;
	case evtp_cascade_OpenDualChan_Ind:
		OnOpenCascadeDualChanInd(ptMsg);
		break;
	case evtp_Conf_DualFastUpdate_Ind:
		OnAskKeyFrame(ptMsg);		
		break;
	case evtp_Conf_SrcDualName_Ind:
		OnSrcNameInd(ptMsg);
		break;
	case evtp_Conf_StartRcvDual_Ind:
		OnStartRcvDaul(ptMsg);
		break;
	case evtp_Conf_StopSendDual_Ind:
		OnStopSendDual(ptMsg);
		break;
	case ev_UmsConfStartDual_Cmd:
		OnStartDualCmd(ptMsg);
		break;
	case ev_UmsConfStopDual_Cmd:
		OnStopDualCmd(ptMsg);
		break;
	case ev_UmsConfDualEp_Nty:
		pInst->OnBrdCastMsg(ptMsg);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL32 CDualMgr::HandlerFromUmc( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case evtp_StartDual_Cmd:
		{
			OnStartDualCmdFormUmc(ptMsg);
			break;
		}
	case evtp_StopDual_Cmd:
		{
			OnStopDualCmdFormUmc(ptMsg);
			break;
		}
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}


BOOL32 CDualMgr::StartConf()
{
	CUmsConfInst* pInst = Inst();

	MediaCreateNetBuf(pInst, m_tVidNetBuf);
	
	return TRUE;
}

void CDualMgr::StopConf()
{
	CUmsConfInst* pInst = Inst();
	TUmsDsData tDsData;

	MediaDestroyNetBuf(pInst, m_tVidNetBuf);
	
	ExitDualModel(TP_INVALID_INDEX);
}

void CDualMgr::Show()
{
	CUmsConfInst* pInst = Inst();
	msgprintnotime("DualMgr ConfID:%d, bStart:%d, ReqDual:%d, CurDual:%d, DualType:%d.\n", 
		pInst->GetInsID(), m_bStart, m_wReqDual, m_wCurDual, m_byDualType);
	
	msgprintnotime("\n");

	msgprintnotime(" UP Rcv. Vid(%d-%d), aud(%d-%d)\n"
		, m_tVidRcvAddr.m_tRtpAddr.m_wPort, m_tVidRcvAddr.m_tBackRtcpAddr.m_wPort
		, m_tAudRcvAddr.m_tRtpAddr.m_wPort, m_tAudRcvAddr.m_tBackRtcpAddr.m_wPort);	
	
	msgprintnotime(" UP Vid NetBuf. RcvRtp(%d), RcvRtcp(%d), SndRtp(%d), RmtRtcp(%d)\n"
		, m_tVidNetBuf.m_tRcvRtpAddr.m_wPort, m_tVidNetBuf.m_tRcvRtcpAddr.m_wPort
		, m_tVidNetBuf.m_wSndAddr.m_wPort, m_tVidNetBuf.m_tRmtRtcpAddr.m_wPort);

	msgprintnotime("\n");
}

void CDualMgr::ShowDs()
{

}

u16 CDualMgr::InitPort(u16 wStartPort)
{
	u32 dwIP = GetLocalIP();
	u16 wOffsetPort = wStartPort;

	m_tVidRcvAddr.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
	m_tVidRcvAddr.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
	m_tVidRcvAddr.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
	wOffsetPort += 4;

	m_tAudRcvAddr.m_tRtpAddr.SetAddr(dwIP, wOffsetPort);
	m_tAudRcvAddr.m_tRtcpAddr.SetAddr(dwIP, wOffsetPort+1);
	m_tAudRcvAddr.m_tBackRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
	wOffsetPort += 4;
	
	m_tVidNetBuf.m_tRcvRtpAddr.SetAddr(dwIP, wOffsetPort);	
	m_tVidNetBuf.m_wSndAddr.SetAddr(dwIP, wOffsetPort+2);	
	m_tVidNetBuf.m_tRcvRtcpAddr.SetAddr(dwIP, wOffsetPort+3);
	m_tVidNetBuf.m_tRmtRtcpAddr = m_tVidRcvAddr.m_tBackRtcpAddr;
	wOffsetPort += 4;

	return wOffsetPort;
}

void CDualMgr::ShowPortRes()
{
	msgprintnotime(" dual, vid(%d,%d), aud(%d,%d), nb(%d,%d,%d,%d)\n" 
		, m_tVidRcvAddr.m_tRtpAddr.m_wPort, m_tVidRcvAddr.m_tBackRtcpAddr.m_wPort
		, m_tAudRcvAddr.m_tRtpAddr.m_wPort, m_tAudRcvAddr.m_tBackRtcpAddr.m_wPort
		, m_tVidNetBuf.m_tRcvRtpAddr.m_wPort, m_tVidNetBuf.m_wSndAddr.m_wPort
		, m_tVidNetBuf.m_tRcvRtcpAddr.m_wPort,m_tVidNetBuf.m_tRmtRtcpAddr.m_wPort
		);
}

void CDualMgr::ResetMediaIp(const TEqpRes& tConfDs)
{
	u32 dwEqpIP = tConfDs.m_dwEqpIp;
		
	m_tVidRcvAddr.m_tRtpAddr.SetIP(dwEqpIP);
	m_tVidRcvAddr.m_tRtcpAddr.SetIP(dwEqpIP);
	m_tVidRcvAddr.m_tBackRtcpAddr.SetIP(dwEqpIP);
	
	m_tAudRcvAddr.m_tRtpAddr.SetIP(dwEqpIP);
	m_tAudRcvAddr.m_tRtcpAddr.SetIP(dwEqpIP);
	m_tAudRcvAddr.m_tBackRtcpAddr.SetIP(dwEqpIP);


}

void CDualMgr::ResetNbIp(const TEqpRes& tConfNb)
{
	u32 dwEqpIP = tConfNb.m_dwEqpIp;
	m_tVidNetBuf.m_tRcvRtpAddr.SetIP(dwEqpIP);	
	m_tVidNetBuf.m_wSndAddr.SetIP(dwEqpIP);	
	m_tVidNetBuf.m_tRcvRtcpAddr.SetIP(dwEqpIP);
	m_tVidNetBuf.m_tRmtRtcpAddr = m_tVidRcvAddr.m_tBackRtcpAddr;
}


void CDualMgr::OnAskKeyFrame(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	BOOL32 bReqBySys = *(BOOL32*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	if (!m_bStart)
	{
		tpLowDtl(Ums_Mdl_Call, "OnAskKeyFrame Dual is not start. ConfID:%d\n", pInst->GetInsID());
		return;
	}

	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
	TCapNode* ptFarther = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFarther)
	{
		if (pInst->IsChairConf())
		{
			tpLowDtl(Ums_Mdl_Call, "OnAskKeyFrame Dual state failed!. ConfID:%d, CurDual:%d\n", pInst->GetInsID(), m_wCurDual);
			return;
		}

		ptNode = pInst->m_pcNodeMgr->GetCaller();
		ptFarther = pInst->m_pcNodeMgr->GetCaller();
	}
	
	if (ptNode->IsMtEp())
	{
		if (!bReqBySys && !pInst->IsValidKeyFrameReq(m_tKeyFrameStatis))
		{
			tpLowDtl(Ums_Mdl_Call, "CDualMgr::AskKeyFrame frequent! ConfID:%d, DstEpID:%d\n"
				, pInst->GetInsID(), ptNode->m_wEpID);
			return;
		}

		if (!bReqBySys)
		{
			m_tKeyFrameStatis.Add();
		}
	}	
	
	tpLowDtl(Ums_Mdl_Call, "OnAskKeyFrame Dual! ConfID:%d, tHandle.GetEpID:%d, CurDual:%d, dstEp:%d\n"
		, pInst->GetInsID(), tHandle.GetEpID(), m_wCurDual, ptFarther->m_wEpID);
	
	if ( pInst->IsDualNeedBas() && TP_VALID_HANDLE(tHandle.GetEpID()) )
	{//这种情况 需要向适配板请求一次
		Inst()->GetBas()->SeeDualAskFrameToBas();
	}

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarther->m_wEpID);
	if ( ptNode == ptFarther && ptNode->IsMtEp() )
	{
		TChanPara* ptChanDst = pInst->m_pcNodeMgr->GetChanByIndex(ptFarther->m_wEpID, ums_CodecType_vid_enc_dual, TP_INVALID_INDEX);
		if( NULL == ptChanDst )
		{
			tpLowDtl(Ums_Mdl_Call, "OnAskKeyFrame Dual.  ptChanDst is NULL!. ConfID:%d, CurDual:%d\n", pInst->GetInsID(), m_wCurDual);
			return ;
		}
		tOutHandle.handPaChan = ptChanDst->m_tPAHandle;
		UmsSendChanCtrl(tOutHandle, evtp_Conf_AskKeyFrame, NULL, 0);
	}
	else
	{
		UmsSendConfCtrl(tOutHandle, evtp_Conf_DualFastUpdate_Ind, &bReqBySys, sizeof(bReqBySys));
	}
}

void CDualMgr::OnSrcNameInd(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TTPAlias* ptAlias = (TTPAlias*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	TEpKey* ptKey = (TEpKey*)(ptMsg->GetBody()+sizeof(TUmsHandle) + sizeof(TTPAlias));

	if (Is_Caller_Node(tHandle.GetEpID()))
	{
		m_tDualAlias = *ptAlias;
		CheckEpDualRcv(tHandle.GetEpID());
	}
	else
	{
		TCapNode* ptForther = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
		TCallNode* ptNode = pInst->m_pcNodeMgr->GetNodeByChildEpID(ptForther, ptKey->m_wEpID);
		if (NULL == ptNode)
		{
			MdlError(Ums_Mdl_Call, ("OnSrcNameInd not find dst! wConfID:%d, dual:%d\n", pInst->GetInsID(), ptKey->m_wEpID));
			m_wCurDual = TP_INVALID_INDEX;
		}
		else
		{
			m_tDualAlias = ptNode->m_tConfName;
			m_wCurDual = ptNode->m_wEpID;
		}
		//双流源在下级，上级ums收到该消息
		CheckEpDualRcv(ptForther->m_wEpID);
	}

	NotifyAllEpSrcDualName(tHandle.GetEpID());
}

void CDualMgr::OnStartRcvDaul(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();

	if (!pInst->IsChairConf() && !pInst->GetBas()->AssignDualBas())
	{
		MdlError(Ums_Mdl_Call, ("OnStartRcvDaul, Down ums assign bas failed. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
		
		TUmsHandle tOutHandle;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);

		TDualRequestAckTr tAck;
		tAck.m_bAccept = FALSE;
		tAck.m_dwReason = emTPDualBasLacking;
		UmsSendConfCtrl(tHandle, evtp_Conf_RequestDualStream_Ind, &tAck, sizeof(tAck));

		return;
	}

	NotifyAllEpStartRcvDual(tHandle.GetEpID());

	m_wCurDual = tHandle.GetEpID();
	
	//调整双流
	Inst()->m_pcBas->AdjustDualBas();
	
	m_bStart = TRUE;
	CNetPortMgr::AjustDualFromNodeToUms(pInst);
	AjustAllDualMedia();

	DualEpNotify();

	return;
}

void CDualMgr::OnChanConnect(TCapNode* ptNode)
{	
	if (!Is_Caller_Node(ptNode->m_wEpID))
	{

		if (ptNode->Is323Ep() && !IsStart())
		{
            if (!ptNode->IsVRS())
			{
                return;
			}
		}


		if (ptNode->IsVRS() && !ptNode->IsVidRcvValid())
		{
             return;
		}

        MakeDualCap(ptNode, TRUE);
	}
}

void CDualMgr::MakeDualCap(TCapNode* ptNode, BOOL32 bSnd, BOOL32 bRes/* = TRUE*/)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);

	if (NULL == ptNode->m_ptDualAddr)
	{
		MdlError(Ums_Mdl_Call, ("MakeDualCap Invalid dual address.\n"));
		return ;	
	}
	
	if (bSnd)
	{

		if (EmChanIdle != ptNode->m_tRmtChan.m_tDualVidDec.m_emChanState)
		{
			return;
		}

		TUmsNodeCapset tNodeCap;
		pInst->m_pcCallMgr->MakeSecVidCap(tNodeCap.m_tVidRcvCap, tNodeCap.m_tVidSndCap);
		pInst->m_pcCallMgr->MakeAudCap(tNodeCap.m_tAudSndCap);
		pInst->m_pcCallMgr->MakeAudCap(tNodeCap.m_tAudRcvCap);
		
		tNodeCap.m_atVidEnc[0].m_tChanAddr.m_tBackRtcpAddr = ptNode->m_ptDualAddr->m_tVid.m_tRtcpForSnd;
		tNodeCap.m_atAudEnc[0].m_tChanAddr.m_tBackRtcpAddr = ptNode->m_ptDualAddr->m_tAud.m_tRtcpForSnd;
		tNodeCap.m_wAudEncNum = 1;
		tNodeCap.m_wVidEncNum = 1;

		ptNode->m_tRmtChan.m_tDualVidDec.m_emChanState = EmChanMaking;
		
		UmsMakeSendDual(tOutHandle, tNodeCap);
	}	
	else
	{
		TUmsNodeCapset tNodeCap;
		pInst->m_pcCallMgr->MakeSecVidCap(tNodeCap.m_tVidRcvCap, tNodeCap.m_tVidSndCap);		
		pInst->m_pcCallMgr->MakeAudCap(tNodeCap.m_tAudSndCap);
		pInst->m_pcCallMgr->MakeAudCap(tNodeCap.m_tAudRcvCap);
		
		tNodeCap.m_atVidDec[0].m_tChanAddr.m_tRtpAddr = ptNode->m_ptDualAddr->m_tVid.m_tRtpAddr;
		tNodeCap.m_atAudDec[0].m_tChanAddr.m_tRtpAddr = ptNode->m_ptDualAddr->m_tAud.m_tRtpAddr;
		tNodeCap.m_wAudDecNum = 1;
		tNodeCap.m_wVidDecNum = 1;
		
		UmsAnswerSendDual(tOutHandle, tNodeCap, bRes);
	}
}
void CDualMgr::HungUpNode(TCallNode* ptNode, BOOL32 bDelete)
{
	CUmsConfInst* pInst = Inst();
	if (NULL == ptNode)
	{
		return;
	}

	if (ptNode->IsUms())
	{
		TCapNode* ptTransChan = pInst->m_pcNodeMgr->GetCapsetNode(ptNode->m_wEpID);
		if (NULL != ptTransChan)
		{			
			TUmsDsData atDsData[4];
			u16 wDsNum = 0;
			if (ptTransChan->m_tRmtChan.m_tDualVidDec.IsOpen())
			{
				atDsData[wDsNum].m_tRcvFromAddr = m_tVidRcvAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptTransChan->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr;	
				atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;	//会议转发板
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetDualVideo();
				wDsNum++;

				atDsData[wDsNum].m_tRcvFromAddr = ptTransChan->m_ptDualAddr->m_tVid.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = m_tVidNetBuf.m_tRcvRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptTransChan->m_tMediaEqp.m_dwEqpNode;	//节点转发板
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;				
			}

			if (ptTransChan->m_tRmtChan.m_tDualAudDec.IsOpen())
			{
				atDsData[wDsNum].m_tRcvFromAddr = m_tAudRcvAddr.m_tRtpAddr;
				atDsData[wDsNum].m_tSndToAddr = ptTransChan->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtpAddr;	
				atDsData[wDsNum].m_dwEqpNode = pInst->m_tEqpConfDs.m_dwEqpNode;	//会议转发板
				atDsData[wDsNum].m_emSwitchType = emRtpSwap;
				atDsData[wDsNum].SetDualAudio();
				wDsNum++;
				
				atDsData[wDsNum].m_tRcvFromAddr = ptTransChan->m_ptDualAddr->m_tAud.m_tRtcpForSnd;
				atDsData[wDsNum].m_tSndToAddr = m_tAudRcvAddr.m_tBackRtcpAddr;
				atDsData[wDsNum].m_dwEqpNode = ptTransChan->m_tMediaEqp.m_dwEqpNode;	//节点转发板
				atDsData[wDsNum].m_emSwitchType = emRtcpSwap;
				wDsNum++;
			}

			if (wDsNum > 0)
			{
				MdlHint(Ums_Mdl_Call, ("CDualMgr::HungUpNode DestroyMediaTrans! wConfID:%d, DsNum:%d\n", pInst->GetInsID(), wDsNum));
				CNetPortMgr::DestroyMediaTrans(pInst, atDsData, wDsNum);
			}
		}
	}
		

	if (m_bStart)
	{
		if (m_wCurDual == ptNode->m_wEpID)
		{

			ExitDualModel(TP_INVALID_INDEX);
		}
	}
}

void CDualMgr::OnDualIncoming(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();


	if ( Is_Caller_Node(tHandle.GetEpID()) )
	{//会议开始时上级过来打开双流通道

		MdlHint(Ums_Mdl_Call, ("OnDualIncoming from super. ConfID:%d\n", pInst->GetInsID()));

		TCapNode* ptChair = pInst->m_pcNodeMgr->GetCaller();
		if (ptChair->IsCallOn())
		{
			MakeDualCap(ptChair, FALSE);			
		}
	}
	else
	{

		TCapNode* ptNode = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());

		if (NULL == ptNode)
		{
			MdlError(Ums_Mdl_Call, ("OnDualIncoming error! No find vaild Node. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
			UmsStopDual(tHandle);
			return;
		}


		if ( localmax(pInst->GetConfBase().m_wHpDualBitRate, pInst->GetConfBase().m_wBpDualBitRate) == 0 )
		{
			MdlError(Ums_Mdl_Call, ("OnDualIncoming. ums dual BitRate is Zero!. ConfID:%d,  DstEpID:%d\n", 
				pInst->GetInsID(), tHandle.GetEpID()));
			
			MakeDualCap(ptNode, FALSE, FALSE);
			return;
		}


		//MT过来打开双流通道
		if (!ptNode->IsMtEp())
		{
			MdlError(Ums_Mdl_Call, ("OnDualIncoming from ep is not valid mt. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
			MakeDualCap(ptNode, FALSE, FALSE);
			return;
		}

		if(!pInst->GetBas()->AssignDualBas())
		{
			MdlError(Ums_Mdl_Call, ("OnDualIncoming Bas Is Full. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
			MakeDualCap(ptNode, FALSE, FALSE);
			
            do {

				if (ptNode->Is323Ep() && !IsStart())
				{
                    if (!ptNode->IsVRS())
					{
                        break;
					}
				}

				if (ptNode->IsVRS() && !ptNode->IsVidRcvValid())
				{
                    break;
				}

                MakeDualCap(ptNode, TRUE);

			}while(0);
			
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Dual_BasFull, Inst()->chairID());
			return ;
		}

		TCallNode* ptSpeaker = Inst()->GetNodeMgr()->GetNode(Inst()->curSpeakerID());
		if ( NULL != ptSpeaker && ptSpeaker->IsChanOn() && ptSpeaker->IsVRS() && m_wCurDual == pInst->curSpeakerID() )
		{
			MdlError(Ums_Mdl_Call, ("OnDualIncoming. curDualEp is VRS. ConfID:%d, epID:%d, curDualEp:%d\n", 
				pInst->GetInsID(), tHandle.GetEpID(), m_wCurDual));
			MakeDualCap(ptNode, FALSE, FALSE);
			
			do {

				if (ptNode->Is323Ep() && !IsStart())
				{
                    if (!ptNode->IsVRS())
					{
                        break;
					}
				}
				
				if (ptNode->IsVRS() && !ptNode->IsVidRcvValid())
				{
                    break;
				}
				
                MakeDualCap(ptNode, TRUE);

			} while(0);

			return;
		}

		MdlHint(Ums_Mdl_Call, ("OnDualIncoming ConfID:%d, m_wReqDual:%d, NewReq:%d\n", pInst->GetInsID(), m_wReqDual, ptNode->m_wEpID));

		if (TP_VALID_HANDLE(m_wReqDual))
		{
			
			if (TP_VALID_HANDLE(m_wChairReq) && m_wChairReq != tHandle.GetEpID())
			{
				m_wChairReq = TP_INVALID_INDEX;
			}
			m_wReqDual = TP_INVALID_INDEX;
		}

		if (ptNode->IsCallOn())
		{
			MakeDualCap(ptNode, FALSE);
		}

		m_wReqDual = ptNode->m_wEpID;
	}
}

void CDualMgr::OnDualChanConnect(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TUmsNodeCapset tNodeCap = *(TUmsNodeCapset*)(ptMsg->GetBody() + sizeof(TUmsHandle));

	TCapNode* ptReqNode = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());

	if (NULL == ptReqNode)
	{
		MdlError(Ums_Mdl_Call, ("OnDualChanConnect , epid failed. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
		UmsStopDual(tHandle);
		return;
	}

	// 协商上来的码流密钥和本地密钥比对
	if (!(pInst->GetConfEncryptInfo() == tNodeCap.m_tEncrypt) && !pInst->GetConfEncryptInfo().IsQt())
	{
		UmsStopDual(tHandle);
		MdlError(Ums_Mdl_Call, ("OnDualChanConnect ep Encrypt not equal! ConfID:%d, EpID:%d, local(%d(Encrymode), %d, %s), from ChanConnect(%d(Encrymode), %d, %s)\n", 
			pInst->GetInsID(), ptReqNode->m_wEpID, pInst->GetConfEncryptInfo().m_emEncryptModel,
			pInst->GetConfEncryptInfo().m_byKeyLen, 
			pInst->GetConfEncryptInfo().m_achEncKey, tNodeCap.m_tEncrypt.m_emEncryptModel, 
			tNodeCap.m_tEncrypt.m_byKeyLen,tNodeCap.m_tEncrypt.m_achEncKey));

		return;
	}

	TUmsConfBase tConfBaseInfoBk;
	memcpy(&tConfBaseInfoBk, &(pInst->m_tConfBaseInfo), sizeof(TUmsConfBase));

	BOOL32 bIsAdjustDualBit = FALSE;

	if (pInst->m_bIsNeedDelayCallNode && !bIsAdjustDualBit)
	{// cns呼叫会议模板，需要调整会议双流码率后，再呼叫结点
		tConfBaseInfoBk.m_wHpDualBitRate = tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate;
		tConfBaseInfoBk.m_wBpDualBitRate = tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate;
	}

	//双流能力合法性判断
	u16 wIndex = 0;
	u16 wLoop = 0;

	MdlHint(Ums_Mdl_Call, ("Before Check Dual vidrcv cap:(%s,%s,%d,%d)(%s,%s,%d,%d)\n", UmsVidProfilePrint(tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl)
		, UmsVidResPrint(tNodeCap.m_tVidRcvCap.m_tHp.m_emRes), tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate, tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate
		, UmsVidProfilePrint(tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl), UmsVidResPrint(tNodeCap.m_tVidRcvCap.m_tBp.m_emRes)
			, tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate, tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate));

	//接收通道
	if (!CTpTypeAdpt::IsValidDualFormat(tNodeCap.m_tVidRcvCap.m_tHp, tConfBaseInfoBk, ptReqNode->IsMtEp(), FALSE))
	{//Clear 不是清成无效值
		tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = emTPVResEnd;
		if (!CTpTypeAdpt::IsValidDualFormat(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk, ptReqNode->IsMtEp(), FALSE))
		{
			MdlHint(Ums_Mdl_Call, ("OnDualChanConnect vid rcv hp and bp cap invalid.\n"));
			tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
			UmsCloseChan(tHandle, emChanRecvSecondVideo, tNodeCap);
		}
		else
		{
			if (!ptReqNode->IsMtEp())
			{
				if (!CTpTypeAdpt::IsEqualDualConfCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk))
				{
					u16 wLoc = CTpTypeAdpt::GetSuitDualConfCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk);
					if (TP_INVALID_INDEX == wLoc)
					{
						MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid rcv bp cap wrong.\n"));
						tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
						UmsCloseChan(tHandle, emChanRecvSecondVideo, tNodeCap);
					}
					else
					{
						memcpy(&tNodeCap.m_tVidRcvCap.m_tBp, &tConfBaseInfoBk.m_atTpMinorVideoRes[wLoc], sizeof(TUmsVidFormat));
					}
				}
			}

			if (pInst->m_bIsNeedDelayCallNode && !bIsAdjustDualBit)
			{
				pInst->m_tConfBaseInfo.m_wHpDualBitRate = tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate;
				pInst->m_tConfBaseInfo.m_wBpDualBitRate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;				
				bIsAdjustDualBit = TRUE;

				for ( wLoop = 0; wLoop < pInst->m_tConfBaseInfo.m_wMinorNum; wLoop++)
				{
					pInst->m_tConfBaseInfo.m_atTpMinorVideoRes[wLoop].m_wBitrate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;
				}

				// for bas
				pInst->m_pcBas->AdjustDualBitrateForBas(pInst->m_tConfBaseInfo.m_wHpDualBitRate);

				MdlHint(Ums_Mdl_Call, ("OnDualChanConnect Rcv hp is invalid, bp is valid, set to ConfBitRate, m_wHpDualBitRate:%d.\n"
						, pInst->m_tConfBaseInfo.m_wHpDualBitRate));
			}

		}
	}
	else
	{
		if (!ptReqNode->IsMtEp())
		{
			if (!CTpTypeAdpt::IsEqualDualConfCap(tNodeCap.m_tVidRcvCap.m_tHp, tConfBaseInfoBk))
			{
				u16 wLoc = CTpTypeAdpt::GetSuitDualConfCap(tNodeCap.m_tVidRcvCap.m_tHp, tConfBaseInfoBk);
				if (TP_INVALID_INDEX == wLoc)
				{
					MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid rcv hp cap wrong.\n"));
					tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = emTPVResEnd;
				}
				else
				{
					memcpy(&tNodeCap.m_tVidRcvCap.m_tHp, &tConfBaseInfoBk.m_atTpMinorVideoRes[wLoc], sizeof(TUmsVidFormat));
				}
			}

			if (emTPVResEnd == tNodeCap.m_tVidRcvCap.m_tHp.m_emRes)
			{
				if (!CTpTypeAdpt::IsValidDualFormat(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk, ptReqNode->IsMtEp(), TRUE))
				{
					MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid rcv hp cap wrong and bp cap invalid.\n"));
					tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
					UmsCloseChan(tHandle, emChanSendSecondVideo, tNodeCap);
				}
				else
				{
					if (!CTpTypeAdpt::IsEqualDualConfCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk))
					{
						u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidRcvCap.m_tBp, tConfBaseInfoBk);
						if (TP_INVALID_INDEX == wLoc)
						{
							MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid rcv hp cap wrong and get rcv bp cap wrong.\n"));
							tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
							UmsCloseChan(tHandle, emChanRecvSecondVideo, tNodeCap);
						}
						else
						{
							memcpy(&tNodeCap.m_tVidRcvCap.m_tBp, &tConfBaseInfoBk.m_atTpMinorVideoRes[wLoc], sizeof(TUmsVidFormat));
						}
					}
				}
			}
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("OnDualChanConnect cns vid rcv hp valid, set bp cap invalid.\n"));
			tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;	
		}

		if (pInst->m_bIsNeedDelayCallNode && !bIsAdjustDualBit)
		{
			pInst->m_tConfBaseInfo.m_wHpDualBitRate = tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate;
			pInst->m_tConfBaseInfo.m_wBpDualBitRate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;				
			bIsAdjustDualBit = TRUE;

			for ( wLoop = 0; wLoop < pInst->m_tConfBaseInfo.m_wMinorNum; wLoop++)
			{
				pInst->m_tConfBaseInfo.m_atTpMinorVideoRes[wLoop].m_wBitrate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;
			}

			// for bas
			pInst->m_pcBas->AdjustDualBitrateForBas(pInst->m_tConfBaseInfo.m_wHpDualBitRate);

			MdlHint(Ums_Mdl_Call, ("OnDualChanConnect rcv hp is valid, set to ConfBitRate, m_wHpDualBitRate:%d.\n"
				, pInst->m_tConfBaseInfo.m_wHpDualBitRate));
		}

	}

	if (pInst->m_bIsNeedDelayCallNode && !bIsAdjustDualBit)
	{// 之前调整过双流码率，则不需要再次调整
		tConfBaseInfoBk.m_wHpDualBitRate = tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate;
		tConfBaseInfoBk.m_wBpDualBitRate = tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate;
	}

	MdlHint(Ums_Mdl_Call, ("Before Check Dual vidsnd cap:(%s,%s,%d,%d)(%s,%s,%d,%d)\n", UmsVidProfilePrint(tNodeCap.m_tVidSndCap.m_tHp.m_emQualityLvl)
		, UmsVidResPrint(tNodeCap.m_tVidSndCap.m_tHp.m_emRes), tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate, tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate
		, UmsVidProfilePrint(tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl), UmsVidResPrint(tNodeCap.m_tVidSndCap.m_tBp.m_emRes)
			, tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate, tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate));

	//发送通道
	if (!CTpTypeAdpt::IsValidDualFormat(tNodeCap.m_tVidSndCap.m_tHp, tConfBaseInfoBk, ptReqNode->IsMtEp(), TRUE))
	{
		tNodeCap.m_tVidSndCap.m_tHp.m_emRes = emTPVResEnd;
		if (!CTpTypeAdpt::IsValidDualFormat(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk, ptReqNode->IsMtEp(), TRUE))
		{
			MdlHint(Ums_Mdl_Call, ("OnDualChanConnect vid snd hp and bp cap invalid.\n"));
			tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
			UmsCloseChan(tHandle, emChanSendSecondVideo, tNodeCap);
		}
		else
		{
			if (!ptReqNode->IsMtEp())
			{
				if (!CTpTypeAdpt::IsEqualDualConfCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk))
				{
					u16 wLoc = CTpTypeAdpt::GetSuitDualConfCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk);
					if (TP_INVALID_INDEX == wLoc)
					{
						MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid snd bp cap wrong.\n"));
						tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
						UmsCloseChan(tHandle, emChanSendSecondVideo, tNodeCap);
					}
					else
					{
						memcpy(&tNodeCap.m_tVidSndCap.m_tBp, &tConfBaseInfoBk.m_atTpMinorVideoRes[wLoc], sizeof(TUmsVidFormat));
					}
				}
			}

			if (pInst->m_bIsNeedDelayCallNode && !bIsAdjustDualBit)
			{
				pInst->m_tConfBaseInfo.m_wHpDualBitRate = tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate;
				pInst->m_tConfBaseInfo.m_wBpDualBitRate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;
				bIsAdjustDualBit = TRUE;

				for ( wLoop = 0; wLoop < pInst->m_tConfBaseInfo.m_wMinorNum; wLoop++)
				{
					pInst->m_tConfBaseInfo.m_atTpMinorVideoRes[wLoop].m_wBitrate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;
				}

				// for bas
				pInst->m_pcBas->AdjustDualBitrateForBas(pInst->m_tConfBaseInfo.m_wHpDualBitRate);

				MdlHint(Ums_Mdl_Call, ("OnDualChanConnect snd hp is invalid, bp is valid, set to ConfBitRate, m_wHpDualBitRate:%d.\n"
					, pInst->m_tConfBaseInfo.m_wHpDualBitRate));
			}

		}
	}
	else
	{
		if (!ptReqNode->IsMtEp())
		{
			if (!CTpTypeAdpt::IsEqualDualConfCap(tNodeCap.m_tVidSndCap.m_tHp, tConfBaseInfoBk))
			{
				u16 wLoc = CTpTypeAdpt::GetSuitDualConfCap(tNodeCap.m_tVidSndCap.m_tHp, tConfBaseInfoBk);
				if (TP_INVALID_INDEX == wLoc)
				{
					MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid snd hp cap wrong.\n"));
					tNodeCap.m_tVidSndCap.m_tHp.m_emRes = emTPVResEnd;
				}
				else
				{
					memcpy(&tNodeCap.m_tVidSndCap.m_tHp, &tConfBaseInfoBk.m_atTpMinorVideoRes[wLoc], sizeof(TUmsVidFormat));
				}
			}

			if (emTPVResEnd == tNodeCap.m_tVidSndCap.m_tHp.m_emRes)
			{
				if (!CTpTypeAdpt::IsValidDualFormat(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk, ptReqNode->IsMtEp(), TRUE))
				{
					MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid snd hp cap wrong and bp cap invalid.\n"));
					tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
					UmsCloseChan(tHandle, emChanSendSecondVideo, tNodeCap);
				}
				else
				{
					if (!CTpTypeAdpt::IsEqualDualConfCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk))
					{
						u16 wLoc = CTpTypeAdpt::GetSuitConfBaseCap(tNodeCap.m_tVidSndCap.m_tBp, tConfBaseInfoBk);
						if (TP_INVALID_INDEX == wLoc)
						{
							MdlHint(Ums_Mdl_Call, ("OnDualChanConnect GetSuitDualCap vid snd hp cap wrong and get snd bp cap wrong.\n"));
							tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
							UmsCloseChan(tHandle, emChanSendPrimoVideo, tNodeCap);
						}
						memcpy(&tNodeCap.m_tVidSndCap.m_tBp, &pInst->GetConfBase().m_atTpMinorVideoRes[wLoc], sizeof(TUmsVidFormat));
					}
				}
			}
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("OnDualChanConnect cns vid snd hp valid, set vid snd bp invalid.\n"));
			tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
		}

		if (pInst->m_bIsNeedDelayCallNode && !bIsAdjustDualBit)
		{
			pInst->m_tConfBaseInfo.m_wHpDualBitRate = tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate;
			pInst->m_tConfBaseInfo.m_wBpDualBitRate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;
			bIsAdjustDualBit = TRUE;

			for ( wLoop = 0; wLoop < pInst->m_tConfBaseInfo.m_wMinorNum; wLoop++)
			{
				pInst->m_tConfBaseInfo.m_atTpMinorVideoRes[wLoop].m_wBitrate = pInst->m_tConfBaseInfo.m_wHpDualBitRate;
			}

			// for bas
			pInst->m_pcBas->AdjustDualBitrateForBas(pInst->m_tConfBaseInfo.m_wHpDualBitRate);

			MdlHint(Ums_Mdl_Call, ("OnDualChanConnect snd hp is valid, set to ConfBitRate, m_wHpDualBitRate:%d.\n"
				, pInst->m_tConfBaseInfo.m_wHpDualBitRate));
		}

	}

	// add by gaoyong
	if (pInst->m_bIsNeedDelayCallNode)
	{// cns呼叫会议模板，在这里呼叫各结点

		pInst->m_bIsNeedDelayCallNode = FALSE;
		
		MdlHint(Ums_Mdl_Call, ("OnDualChanConnect, Begin to CallAllLocalNode, ConfId:%d, ConfHpBit:%d, ConfBpBit:%d, ConfDualHpBit:%d, ConfDualBpBit:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wConfBitRate, pInst->m_tConfBaseInfo.m_wBpConfBitRate, 
			pInst->m_tConfBaseInfo.m_wHpDualBitRate, pInst->m_tConfBaseInfo.m_wBpDualBitRate));
		
		pInst->CallAllLocalNode();
	}
	// end

	if (!tNodeCap.m_tVidRcvCap.IsValidCap() && !tNodeCap.m_tVidSndCap.IsValidCap())
	{
		ptReqNode->m_bCheckDualRcv = FALSE;
	}

	if (!tNodeCap.m_tVidRcvCap.IsValidCap() && !tNodeCap.m_tVidSndCap.IsValidCap())
	{//双流发送接收通道能力不合法	
		UmsStopDual(tHandle, emTPChannelDisconnectNormal);
		MdlError(Ums_Mdl_Call, ("OnDualChanConnect vid and aud chan not open, stop Dual. ConfID:%d, EpID:%d\n", pInst->GetInsID(), ptReqNode->m_wEpID));

		if (tNodeCap.m_wVidEncNum > 0 || tNodeCap.m_wAudEncNum > 0)
		{
			if (TP_VALID_HANDLE(m_wChairReq) && m_wChairReq == tHandle.GetEpID())
			{//主席主动指定会场发双流
				TConfEpID tEpID;
				tEpID.m_wConfID = pInst->GetInsID();
				tEpID.m_wEpID = m_wReqDual;
				EmTPDualReason emReason = emTpDualPeerReject;
				s8 bySndBuf[sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
				memcpy(bySndBuf, &tEpID, sizeof(TConfEpID));
				memcpy(bySndBuf + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));
				pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStartDual_Ind, pInst->chairID(), bySndBuf, sizeof(bySndBuf));

				// 通知umc
				pInst->NotifyMsgToServiceForUI(evtp_StartDual_Ind, bySndBuf, sizeof(bySndBuf));

			}
		}	
		return;
	}

	if (ptReqNode->m_tRmtChan.IsDualChanOn())
	{
		MdlHint(Ums_Mdl_Call, ("OnDualChanConnect. ConfID:%d, wEpID:%d dual chan had opend, vidsnd chanstate:%d, vidrcv chanstate:%d\n", pInst->GetInsID()
			, ptReqNode->m_wEpID, ptReqNode->m_tRmtChan.m_tDualVidEnc.IsOpen(), ptReqNode->m_tRmtChan.m_tDualVidDec.IsOpen()));
		TUmsNodeCapset tNode;
		pInst->GetNodeMgr()->GetDualNodeCapset(ptReqNode, tNode);
		if (ptReqNode->m_wVidSndNum > 0 && ptReqNode->m_tRmtChan.m_tDualVidEnc.IsOpen())
		{
			UmsCloseChan(tHandle, emChanSendSecondVideo, tNode);
		}
		if (ptReqNode->m_wVidRcvNum > 0 && ptReqNode->m_tRmtChan.m_tDualVidDec.IsOpen())
		{
			UmsCloseChan(tHandle, emChanRecvSecondVideo, tNode);
		}
	}

	pInst->GetNodeMgr()->SetDualNodeCapset(ptReqNode, tNodeCap);
	//end add

	m_wNextDual = TP_INVALID_INDEX;
	
	if ( Is_Caller_Node(tHandle.GetEpID()) )
	{//与上级建立链接
		if (tNodeCap.m_wVidEncNum > 0)
		{//向上接收通道(即上级向下发送)
			MdlHint(Ums_Mdl_Call, ("OnDualChanConnect from super. Superior open, ConfID:%d\n", pInst->GetInsID()));

			TCapNode* ptChair = pInst->m_pcNodeMgr->GetCaller();			
			ptChair->m_tRmtChan.m_tDualVidEnc.SetPara(tNodeCap.m_atVidEnc[0]);
			ptChair->m_tRmtChan.m_tDualAudEnc.SetPara(tNodeCap.m_atAudEnc[0]);

			//下级的双流接收通道建立好后，立即向上级发起建立发送通道
			TDualInfoTr tDualCmd;

			tDualCmd.m_tDualCap.m_tVid.m_tChanAddr.m_tBackRtcpAddr = ptChair->m_ptDualAddr->m_tVid.m_tRtcpForSnd;
			tDualCmd.m_tDualCap.m_tAud.m_tChanAddr.m_tBackRtcpAddr = ptChair->m_ptDualAddr->m_tAud.m_tRtcpForSnd;
			
			TUmsHandle tOutHandle;
			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, evtp_cascade_OpenDualChan_Cmd, &tDualCmd, sizeof(tDualCmd));
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("OnDualChanConnect Failed from super. Superior open, ConfID:%d\n", pInst->GetInsID()));
		}
	}
	else
	{
		do 
		{
			if (tNodeCap.m_wVidDecNum > 0 || tNodeCap.m_wAudDecNum > 0)
			{//向下打开发送通道成功
				MdlHint(Ums_Mdl_Call, ("OnDualChanConnect to lower. ConfID:%d, EpID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
				
				ptReqNode->m_tRmtChan.m_tDualVidDec.SetPara(tNodeCap.m_atVidDec[0]);
				ptReqNode->m_tRmtChan.m_tDualAudDec.SetPara(tNodeCap.m_atAudDec[0]);
				
				if (IsStart())
				{
					u8 abyBuf[sizeof(TTPAlias)+sizeof(TEpKey)];
					TEpKeyEx tSrcKeyEx;
					TTPAlias* ptAlias = (TTPAlias*)abyBuf;
					TEpKey* ptSrcKey = (TEpKey*)(abyBuf+sizeof(TTPAlias));
					ptAlias->Clear();
					ptSrcKey->Clear();
					
					GetDualSrcName(*ptAlias);	
					ptSrcKey->m_wEpID = TP_INVALID_INDEX;
					tSrcKeyEx.m_wEpID = TP_INVALID_INDEX;

					// add by gaoyong  这里的tHandle，之前没有赋值呼叫类型
					tHandle.m_emProtocol = ptReqNode->m_emCallProtocol;

					UmsSendConfCtrl(tHandle, evtp_Conf_StartRcvDual_Ind, &tSrcKeyEx, sizeof(tSrcKeyEx));
					UmsSendConfCtrl(tHandle, evtp_Conf_SrcDualName_Ind, abyBuf, sizeof(TTPAlias)+sizeof(TEpKey));	

					if (!ptReqNode->IsUms())
					{
						//通知界面双流结点
						TConfEpID tConfEpID;
						tConfEpID.m_wConfID = pInst->GetInsID();
						tConfEpID.m_wEpID = GetDualID();
						pInst->NotifyConfCtrlMsgToCns( ev_UmsConfDualEp_Nty, tHandle.GetEpID(), &tConfEpID, sizeof(tConfEpID));
					}
					pInst->GetNodeFsm()->UpdateMediaTrans(ptReqNode);

					// 替终端请求一次关键帧
					m_tKeyFrameStatis.Clear();
					AskFrameToDualSrcEp();

				}
				break;
			}
			
			if (tNodeCap.m_wVidEncNum > 0 || tNodeCap.m_wAudEncNum > 0)
			{//接收通道
				
				if ( ptReqNode->IsVRS() && ptReqNode->m_wEpID != pInst->curSpeakerID() )
				{//放像
					ptReqNode->m_tRmtChan.m_tDualVidEnc.SetPara(tNodeCap.m_atVidEnc[0]);
					ptReqNode->m_tRmtChan.m_tDualAudEnc.SetPara(tNodeCap.m_atAudEnc[0]);
					
					MdlHint(Ums_Mdl_Call, ("OnDualChanConnect from VRS. ConfID:%d, m_wReqDual:%d, epID:%d\n"
						, pInst->GetInsID(), m_wReqDual, tHandle.GetEpID()));
					return ;
				}

				//链接不是当前请求，则挂断
				if (m_wReqDual != tHandle.GetEpID() && !ptReqNode->IsCns())
				{
					MdlError(Ums_Mdl_Call, ("OnDualChanConnect from cns is not CurReq. ConfID:%d, m_wReqDual:%d, epID:%d\n"
						, pInst->GetInsID(), m_wReqDual, tHandle.GetEpID()));
					
					StopEpSndDual(ptReqNode);
					return;
				}
				
				MdlHint(Ums_Mdl_Call, ("OnDualChanConnect to Ums. ConfID:%d, EpID:%d, VidEncNum:%d, AudEncNum:%d\n", 
												pInst->GetInsID(), tHandle.GetEpID(), tNodeCap.m_wVidEncNum, tNodeCap.m_wAudEncNum));
					
				TCallNode* ptOldNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
				TCapNode* ptOldFarther = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldNode);

				TUmsHandle tOutHandle;
				if (NULL != ptOldNode && NULL != ptOldFarther && CALLER_EP_INDEX != m_wCurDual)
				{					
					if (ptOldNode == ptOldFarther)
					{
						StopEpSndDual(ptOldFarther, emTPForceStop);
					}
					else
					{
						TEpKey tKey;
						tKey.m_wEpID = ptOldNode->m_wLowChildEpID;
						
						pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptOldFarther->m_wEpID);
						UmsSendConfCtrl(tOutHandle, evtp_Conf_StopSendDual_Ind, &tKey, sizeof(tKey));
					}

					ptOldFarther->m_tRmtChan.m_tDualVidDec.m_tKeyFrameStatis.Clear();
				}

				m_wReqDual = ptReqNode->m_wEpID;

				ptReqNode->m_tRmtChan.m_tDualVidEnc.SetPara(tNodeCap.m_atVidEnc[0]);
				ptReqNode->m_tRmtChan.m_tDualAudEnc.SetPara(tNodeCap.m_atAudEnc[0]);
				
				if (pInst->IsChairConf())
				{
					CheckEpDualRcv(ptReqNode->m_wEpID, m_wCurDual);
					ChangeDualEpProc(TP_INVALID_INDEX);
				}
				else
				{
					//本级中
					if (NULL != ptOldNode && CALLER_EP_INDEX != ptOldNode->m_wEpID)
					{//向上通道已经打开
						m_tDualAlias = ptReqNode->m_tConfName;
						CheckEpDualRcv(ptReqNode->m_wEpID, m_wCurDual);
						ChangeDualEpProc(TP_INVALID_INDEX);
					}
					else
					{//首先打开向上通道
						//检查下级除双流源的所有会场接收
						CheckEpDualRcv(m_wReqDual);

						TEpKeyEx tCmd;
						tCmd.m_wEpID = ptReqNode->m_wEpID;

						pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
						UmsSendConfCtrl(tOutHandle, evtp_Conf_RequestDualStream_cmd, &tCmd, sizeof(tCmd));
					}
				}//if (pInst->IsChairConf())

				m_tKeyFrameStatis.Clear();
				//双流上来后，主动向双流源请求关键帧
				AskFrameToDualSrcEp();

				break;
			}

			//没有打开视频通道
			MdlError(Ums_Mdl_Call, ("OnDualChanConnect not open vid. ConfID:%d, m_wReqDual:%d, epID:%d, VidDecNum:%d, VidEncNum:%d.\n"
									, pInst->GetInsID(), m_wReqDual, tHandle.GetEpID(), tNodeCap.m_wVidDecNum, tNodeCap.m_wVidEncNum));
			
		} while (0);
	}
}

void CDualMgr::AskFrameToDualSrcEp()
{
	CUmsConfInst* pInst = Inst();
	TChanPara* ptChanDst = pInst->m_pcNodeMgr->GetChanByIndex(m_wCurDual, ums_CodecType_vid_enc_dual, TP_INVALID_INDEX);
	if( NULL == ptChanDst )
	{
		tpLowDtl(Ums_Mdl_Call, "AskFrameToDualSrcEp ptChanDst is NULL!. ConfID:%d, CurDual:%d\n", pInst->GetInsID(), m_wCurDual);
		return ;
	}

	TUmsHandle tOutHandle;	
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, m_wCurDual);
	tOutHandle.handPaChan = ptChanDst->m_tPAHandle;
	UmsSendChanCtrl(tOutHandle, evtp_Conf_AskKeyFrame, NULL, 0);
}

void CDualMgr::OnDualChanDisConnect(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	EmTPChannelReason emReason = *(EmTPChannelReason*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("OnDualChanDisConnect ConfID:%d, EpID:%d, CurDual:%d, AppChan:%d, emReason:%d\n"
		, pInst->GetInsID(), tHandle.GetEpID(), m_wCurDual, tHandle.handPaChan, emReason));
	
	TCapNode* ptNode = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
	if (NULL == ptNode)
	{
		MdlError(Ums_Mdl_Call, ("OnDualChanDisConnect failed. ConfID:%d, EpID:%d, CurDual:%d\n"
			, pInst->GetInsID(), tHandle.GetEpID(), m_wCurDual));
		return;
	}

	//协议栈断链时，暂不支持单向。这里业务做处理：业务端的通道状态已经断开，却还收到断链则不处理
	if ( tHandle.handPaChan == em_second_vidsnd_handle && ptNode->m_tRmtChan.m_tDualVidDec.IsIdle() )
	{
		return ;
	}
	if ( tHandle.handPaChan == em_second_vidrcv_handle && ptNode->m_tRmtChan.m_tDualVidEnc.IsIdle() )
	{
		return ;
	}

	if ( tHandle.handPaChan == em_second_audsnd_handle && ptNode->m_tRmtChan.m_tDualAudDec.IsIdle() )
	{
		return ;
	}
	if ( tHandle.handPaChan == em_second_audrcv_handle && ptNode->m_tRmtChan.m_tDualAudEnc.IsIdle() )
	{
		return ;
	}

	// add by gaoyong
	if (pInst->m_bIsNeedDelayCallNode)
	{ // cns呼叫会议模板，延迟呼叫各结点
		pInst->m_bIsNeedDelayCallNode = FALSE;
		
		MdlHint(Ums_Mdl_Call, ("OnDualChanDisConnect, Begin to CallAllLocalNode, ConfId:%d, ConfHpBit:%d, ConfBpBit:%d, ConfDualHpBit:%d, ConfDualBpBit:%d\n", 
				pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wConfBitRate, pInst->m_tConfBaseInfo.m_wBpConfBitRate, 
				pInst->m_tConfBaseInfo.m_wHpDualBitRate, pInst->m_tConfBaseInfo.m_wBpDualBitRate));

		pInst->CallAllLocalNode();
	}

	if (em_second_vidsnd_handle == tHandle.handPaChan)
	{
		ptNode->m_tRmtChan.m_tDualVidDec.SetOpen(FALSE);
	}
	if (em_second_audsnd_handle == tHandle.handPaChan)
	{
		ptNode->m_tRmtChan.m_tDualAudDec.SetOpen(FALSE);
	}

	if (m_wReqDual == ptNode->m_wEpID && em_second_vidrcv_handle == tHandle.handPaChan)
	{
		m_wReqDual = TP_INVALID_INDEX;
	}

	pInst->GetNodeFsm()->UpdateMediaTrans(ptNode);
	
	if (em_second_vidrcv_handle == tHandle.handPaChan)
	{
		ptNode->m_tRmtChan.m_tDualVidEnc.SetOpen(FALSE);
	}

	if (em_second_vidrcv_handle == tHandle.handPaChan && ptNode->IsMtEp())
	{//如果是会场，并且通道为会场向UMS的发送通道
	 //重新打开UMS向会场的发送通道		

		if (!ptNode->m_tRmtChan.m_tDualVidDec.IsOpen())
		{

			do {
                if (ptNode->Is323Ep() && !IsStart())
				{ //对于323终端，如果双流没有开启，暂时不开到对端的双流通道
                    if (!ptNode->IsVRS())
					{
                         break;
					}
				}


				if (ptNode->Is323Ep() && m_wCurDual == ptNode->m_wEpID)
				{ //或者双流开启的情形下，发双流的323终端自己关闭了双流，也不需要重建到对端的通道
					if (!ptNode->IsVRS())
					{
						break;
					}
				}

                
				if (ptNode->IsVRS() && !ptNode->IsVidRcvValid())
				{
					break;
				}


				MakeDualCap(ptNode, TRUE);

			} while (0);
		}

		if (m_wChairReq == ptNode->m_wEpID)
		{
			m_wChairReq = TP_INVALID_INDEX;
		}
		
		if (m_wCurDual == ptNode->m_wEpID)
		{
			m_wCurDual = TP_INVALID_INDEX;
			ExitDualModel(TP_INVALID_INDEX);
		}
	}

	if (em_second_audrcv_handle == tHandle.handPaChan)
	{
		ptNode->m_tRmtChan.m_tDualAudEnc.SetOpen(FALSE);
	}
}

void CDualMgr::StopEpSndDual(TCapNode* ptNode, EmTPChannelReason emReason)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
	UmsStopDual(tOutHandle, emReason);
}


void CDualMgr::StopDual()
{
	CUmsConfInst* pInst = Inst();
	if (!m_bStart)
	{
		return;
	}
	if (!pInst->IsChairConf())
	{
		MdlError(Ums_Mdl_Call, ("EventStopDual is not chair! ConfID:%d\n", pInst->GetInsID()));
		return;
	}

	MdlHint(Ums_Mdl_Call, ("StopDual ConfID:%d, CurDual:%d\n", pInst->GetInsID(), m_wCurDual));
	
	ExitDualModel(TP_INVALID_INDEX);	
}

void CDualMgr::OnReqDualStreamCmd(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TEpKeyEx* ptKeyEx = (TEpKeyEx*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	CUmsConfInst* pInst = Inst();
	
	TEpKey tKey;
	TEpKey* ptKey = &tKey;

	ptKey->m_wEpID = ptKeyEx->m_wEpID;

	MdlHint(Ums_Mdl_Call, ("OnReqDualStreamCmd ConfID:%d, EpID:%d, dstID:%d, start:%d\n"
		, pInst->GetInsID(), tHandle.GetEpID(), ptKey->m_wEpID, m_bStart));
	
	TUmsHandle tOutHandle;
	if (Is_Caller_Node(tHandle.GetEpID()))
	{//从上级过来，通知下级的某个终端发送双流		

		TDualRequestAckTr tAck;
		
		do 
		{
			TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(ptKey->m_wEpID);
			TCapNode* ptFartherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
			if (NULL == ptNode || NULL == ptFartherNode || !ptNode->m_bUsed)
			{
				tAck.m_dwReason = emTpDualPeerStop;
				break;
			}

			if (!pInst->GetBas()->AssignDualBas())
			{
				tAck.m_dwReason = emTPDualBasLacking;
				break;
			}

			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFartherNode->m_wEpID);
			
			TEpKeyEx tCmd;
			if (ptNode == ptFartherNode)
			{// 通知会场
				tCmd.m_wEpID = ptNode->m_wEpID;
			}
			else
			{// 通知ums
				tCmd.m_wEpID = ptNode->m_wLowChildEpID;
			}
				
			UmsSendConfCtrl(tOutHandle, evtp_Conf_RequestDualStream_cmd, &tCmd, sizeof(tCmd));

			return;

		} while (0);

		// 回复失败
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());		

		tAck.m_bAccept = FALSE;
		tAck.m_tEpKey = *ptKey;
		UmsSendConfCtrl(tOutHandle, evtp_Conf_RequestDualStream_Ind, &tAck, sizeof(tAck));
	
	}
	else
	{//下级或本级会场过来请求发送双流

		TCallNode* ptReqNode = NULL;
		TCapNode* ptReqFarther = NULL;

		ptReqFarther = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
		ptReqNode = pInst->m_pcNodeMgr->GetNodeByChildEpID(ptReqFarther, ptKey->m_wEpID);
		if (NULL == ptReqFarther || NULL == ptReqNode)
		{
			MdlError(Ums_Mdl_Call, ("OnReqDualStreamCmd, epid failed. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
			
			TDualRequestAckTr tAck;
			tAck.m_bAccept = FALSE;
			tAck.m_dwReason = emTpDualPeerStop;
			tAck.m_tEpKey = *ptKey;
			UmsSendConfCtrl(tHandle, evtp_Conf_RequestDualStream_Ind, &tAck, sizeof(tAck));
			return;
		}


	    if ( localmax(pInst->GetConfBase().m_wHpDualBitRate, pInst->GetConfBase().m_wBpDualBitRate) == 0 )
		{
            //下级会场请求发双流，上级会场BitRate 为0
			MdlError(Ums_Mdl_Call, ("OnReqDualStreamCmd, ums dual BitRate is Zero!. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));

			TDualRequestAckTr tAck;
			tAck.m_bAccept = FALSE;
			tAck.m_dwReason = emTpDualPeerStop;
			tAck.m_tEpKey = *ptKey;
			UmsSendConfCtrl(tHandle, evtp_Conf_RequestDualStream_Ind, &tAck, sizeof(tAck));
			return;
		}


		if (!pInst->GetBas()->AssignDualBas())
		{
			MdlError(Ums_Mdl_Call, ("OnReqDualStreamCmd, bas failed. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
			
			TDualRequestAckTr tAck;
			tAck.m_bAccept = FALSE;
			tAck.m_dwReason = emTPDualBasLacking;
			tAck.m_tEpKey = *ptKey;
			UmsSendConfCtrl(tHandle, evtp_Conf_RequestDualStream_Ind, &tAck, sizeof(tAck));
			return;
		}
			
		u16 wTempReqDual = m_wReqDual;
		u16 wTempCurDual = m_wCurDual;
		//如果有正在请求的会场，则停止该请求
		TCallNode* ptOldReqNode = pInst->m_pcNodeMgr->GetNode(m_wReqDual);
		TCapNode* ptOldReqNodeFar = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldReqNode);
		if (NULL != ptOldReqNode)
		{

			if (ptOldReqNodeFar->IsUms())
			{
				TEpKey tKey;
				tKey.m_wEpID = ptOldReqNode->m_wLowChildEpID;
				pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptOldReqNodeFar->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_StopSendDual_Ind, &tKey, sizeof(tKey));
			}	
			m_wReqDual = TP_INVALID_INDEX;
		}
		
		BOOL32 bCurDual = FALSE;//当前双流源在本级中

		//如果有正在发送的双流，停止发送
		ptOldReqNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
		ptOldReqNodeFar = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldReqNode);
		if (NULL != ptOldReqNode)
		{
			if (ptOldReqNodeFar->IsMtEp())
			{
				StopEpSndDual(ptOldReqNodeFar, emTPForceStop);
			}
			
			if (ptOldReqNodeFar->IsUms())
			{
				TEpKey tKey;
				tKey.m_wEpID = ptOldReqNode->m_wLowChildEpID;
				pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptOldReqNodeFar->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_StopSendDual_Ind, &tKey, sizeof(tKey));
			}	

			m_wCurDual = TP_INVALID_INDEX;
			
			CNetPortMgr::AjustDualFromNodeToUms(pInst);

			bCurDual = TRUE;
		}

		//同意
		TDualRequestAckTr tAck;
		tAck.m_bAccept = TRUE;
		tAck.m_dwReason = emTpDualAccept;
		tAck.m_tEpKey.m_wEpID = ptReqNode->m_wLowChildEpID;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptReqFarther->m_wEpID);
		UmsSendConfCtrl(tHandle, evtp_Conf_RequestDualStream_Ind, &tAck, sizeof(tAck));
		
		if (pInst->IsChairConf())
		{

			m_wReqDual = ptReqNode->m_wEpID;
			CheckEpDualRcv(tHandle.GetEpID(), wTempCurDual, wTempReqDual);
			ChangeDualEpProc(tHandle.GetEpID());
		}
		else
		{			
			if (bCurDual)//双流源在本级中，则直接改变双流源
			{
				ChangeDualEpProc(TP_INVALID_INDEX);
			}
			else
			{// 继续向上发
				TEpKeyEx tCmd;
				tCmd.m_wEpID = ptReqNode->m_wEpID;

				pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_RequestDualStream_cmd, &tCmd, sizeof(tCmd));
			}
		}
	}
}

void CDualMgr::OnReqDualStreamInd(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TDualRequestAckTr tCmdAck = *(TDualRequestAckTr*)(ptMsg->GetBody()+sizeof(TUmsHandle));	
	MdlHint(Ums_Mdl_Call, ("OnReqDualStreamInd ConfID:%d,EpID:%d, start:%d, Accept:%d, Reason:(%d-%s), keyPath:%d\n"
		, pInst->GetInsID(), tHandle.GetEpID(), m_bStart, tCmdAck.m_bAccept, TpEnumIdString(EmTPDualReason, tCmdAck.m_dwReason),  tCmdAck.m_tEpKey.m_wEpID));

	TCapNode* ptForeNode = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
	if (NULL == ptForeNode)
	{
		MdlError(Ums_Mdl_Call, ("OnReqDualStreamInd FAILED! ConfID:%d, epid:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
		return;
	}

	TCallNode* ptNode = NULL;
	if (Is_Caller_Node(ptForeNode->m_wEpID))
	{
		if (m_wReqDual != tCmdAck.m_tEpKey.m_wEpID)
		{
			MdlHint(Ums_Mdl_Call, ("OnReqDualStreamInd SrcChange! ConfID:%d, ReqDual:%d, AckDual:%d\n "
				,pInst->GetInsID(), m_wReqDual, tCmdAck.m_tEpKey.m_wEpID));
			return;
		}

		if (!tCmdAck.m_bAccept)
		{// 上级拒绝了
			
			ExitDualModel(TP_INVALID_INDEX);

			if (emTPDualBasLacking ==  tCmdAck.m_dwReason)
			{
				pInst->NotifyReasonToUI(EmUI_UMC, TP_UMS_Dual_BasFull);
			}

			return;
		}

		TCapNode* ptReqNode = pInst->m_pcNodeMgr->GetCapsetNode(m_wReqDual);
		m_tDualAlias = ptReqNode->m_tConfName;

		ChangeDualEpProc(CALLER_EP_INDEX);
		TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
		TCapNode* ptForNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
		if (NULL != ptNode && ptNode != ptForNode)
		{
			TDualRequestAckTr tAck;
			tAck.m_bAccept = TRUE;
			tAck.m_dwReason = emTpDualAccept;
			tAck.m_tEpKey.m_wEpID = ptNode->m_wEpID;
			
			TUmsHandle tOutHandle;
			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptForNode->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_RequestDualStream_Ind, &tAck, sizeof(tAck));
		}
	}
	else
	{//从下面过来的确认信息
		if (ptForeNode->IsMtEp())
		{
			ptNode = ptForeNode;

			//本级会场为双流源
			if( tCmdAck.m_bAccept )
			{
				m_wNextDual = ptNode->m_wEpID;
			}
		}
		else
		{
			ptNode = pInst->m_pcNodeMgr->GetNodeByChildEpID(ptForeNode, tCmdAck.m_tEpKey.m_wEpID);
		}

		if (NULL == ptNode)
		{
			tCmdAck.m_bAccept = FALSE;
		}
		
		if (!pInst->IsChairConf())
		{//继续向上级徽标
			TDualRequestAckTr tRmtEp;
			tRmtEp.m_bAccept = tCmdAck.m_bAccept;
			tRmtEp.m_dwReason = tCmdAck.m_dwReason;
			if (NULL != ptNode)
			{
				tRmtEp.m_tEpKey.m_wEpID = ptNode->m_wEpID;				
			}
			else
			{			
				tRmtEp.m_bAccept = FALSE;
				tRmtEp.m_dwReason = emTpDualLocalStop;
			}
			
			TUmsHandle tOutHandle;
			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_RequestDualStream_Ind, &tRmtEp, sizeof(tRmtEp));
		}
		else
		{//通知主席结果
			TConfEpID tConfEp;
			tConfEp.m_wConfID = pInst->GetInsID();
			if (NULL != ptNode)
			{
				tConfEp.m_wEpID = ptNode->m_wEpID;
			}

			EmTPDualReason emReason;
			if (FALSE == tCmdAck.m_bAccept)
			{//失败，
				emReason = tCmdAck.m_dwReason == emTpDualAccept ? emTpDualPeerReject : tCmdAck.m_dwReason;

				if (m_bStart && emTPDualBasLacking == emReason)
				{// 已经开启双流，但是下级双流适配不足，需要停止双流，并提示
					ExitDualModel(TP_INVALID_INDEX);
					pInst->NotifyReasonToUI(EmUI_CNC|EmUI_UMC, TP_UMS_Dual_BasFull, pInst->chairID());
				}
				else if (!m_bStart)
				{// 未开启
					ExitDualModel(TP_INVALID_INDEX);
				}
				else
				{
					// 无需处理
				}

			}
			else
			{
				emReason = emTpDualAccept;
			}

			s8 bySndBuf[sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
			memcpy(bySndBuf, &tConfEp, sizeof(TConfEpID));
			memcpy(bySndBuf + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));
			pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStartDual_Ind, pInst->chairID(), bySndBuf, sizeof(bySndBuf));
			
			// 通知umc
			pInst->NotifyMsgToServiceForUI(evtp_StartDual_Ind, bySndBuf, sizeof(bySndBuf));

		}
	}
}
void CDualMgr::OnStopSendDual(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();	
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TEpKey tEpKey = *(TEpKey*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("OnStopSendDual ConfID:%d, IsChair:%d, StopEp:%d m_wReqDual:%d, m_wCurDual:%d\n"
		, pInst->GetInsID(), pInst->IsChairConf(), tEpKey.m_wEpID, m_wReqDual, m_wCurDual));

	TUmsHandle tOutHandle;

	TCallNode* ptOldReqNode = pInst->m_pcNodeMgr->GetNode(tEpKey.m_wEpID);
	TCapNode* ptOldReqNodeFar = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldReqNode);
	if (NULL != ptOldReqNode)
	{
		if (ptOldReqNode->m_wEpID == m_wReqDual)
		{
			
			if (ptOldReqNodeFar->IsUms())
			{
				TEpKey tKey;
				tKey.m_wEpID = ptOldReqNode->m_wLowChildEpID;
				pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptOldReqNodeFar->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_StopSendDual_Ind, &tKey, sizeof(tKey));
			}
			m_wReqDual = TP_INVALID_INDEX;
		}
		
		if (ptOldReqNode->m_wEpID == m_wCurDual)
		{
			if (ptOldReqNodeFar->IsMtEp())
			{
				StopEpSndDual(ptOldReqNodeFar, emTPForceStop);
			}
			
			if (ptOldReqNodeFar->IsUms())
			{
				TEpKey tKey;
				tKey.m_wEpID = ptOldReqNode->m_wLowChildEpID;
				pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptOldReqNodeFar->m_wEpID);
				UmsSendConfCtrl(tOutHandle, evtp_Conf_StopSendDual_Ind, &tKey, sizeof(tKey));
			}

			m_wCurDual = TP_INVALID_INDEX;
			m_bStart = FALSE;


			TConfEpID tConfEp;
			tConfEp.m_wConfID = pInst->GetInsID();
			tConfEp.m_wEpID = m_wCurDual;
			
			CTpMsg cMsg;
			cMsg.SetEvent(evtp_DualEp_Notify);
			cMsg.SetBody(&tConfEp, sizeof(tConfEp));
			cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
			pInst->NotifyConfCtrlMsgToAllCns(ev_UmsConfDualEp_Nty, &tConfEp, sizeof(tConfEp));

			CNetPortMgr::AjustDualFromNodeToUms(pInst);
		}
	}
}


void CDualMgr::OnStopRcvDual(CTpMsg *const ptMsg)
{
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	EmTPDualReason emDual = *(EmTPDualReason*)(ptMsg->GetBody()+sizeof(TUmsHandle));

	CUmsConfInst* pInst = Inst();	

	MdlHint(Ums_Mdl_Call, ("OnStopRcvDual ConfID:%d, IsChair:%d, m_wCurDual:%d, reason:(%d->%s)\n"
		, pInst->GetInsID(), pInst->IsChairConf(), m_wCurDual, TpEnumIdString(EmTPDualReason, emDual)));
	
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
	TCapNode* ptNodeFarether = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);


	if (pInst->IsChairConf())
	{
		if (NULL != ptNode && NULL != ptNodeFarether && ptNodeFarether->m_wEpID == tHandle.GetEpID())
		{
			ExitDualModel(tHandle.GetEpID());
		}
	}
	else
	{
        ExitDualModel(CALLER_EP_INDEX);
	}


	if (m_wReqDual == tHandle.GetEpID())
	{
		m_wReqDual = TP_INVALID_INDEX;
	}
}

void CDualMgr::OnOpenCasecadeDualChanCmd(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TDualInfoTr* ptDualCmd = (TDualInfoTr*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	TTPMediaTransAddr* ptVidAddr = &ptDualCmd->m_tDualCap.m_tVid.m_tChanAddr;

	TCapNode* ptNode = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());

	if (NULL == ptNode)
	{
		MdlError(Ums_Mdl_Call, ("OnOpenCasecadeDualChanCmd, epid failed. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
		
		TDualInfoAckTr tDualAck;
		tDualAck.m_bAccept = FALSE;
		tDualAck.m_tDualInfo = *ptDualCmd;
		UmsSendConfCtrl(tHandle, evtp_cascade_OpenDualChan_Ind, &tDualAck, sizeof(tDualAck));
		return;
	}
	
	if (!ptNode->IsCallOn() || !ptNode->IsChanOn())
	{
		MdlError(Ums_Mdl_Call, ("OnOpenCasecadeDualChanCmd, call failed. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
		
		TDualInfoAckTr tDualAck;
		tDualAck.m_bAccept = FALSE;
		tDualAck.m_tDualInfo = *ptDualCmd;
		UmsSendConfCtrl(tHandle, evtp_cascade_OpenDualChan_Ind, &tDualAck, sizeof(tDualAck));
		return;
	}

	
	if (pInst->IsChairConf() && ptNode->IsUms() && !ptNode->m_tRmtChan.m_tDualVidDec.IsOpen())
	{   // 如果向下的级双流联通道没有打开，就不打开向上的级联双流通道，处理上下级双流格式大小不一致，行为不一致的问题
		// eg 上级（dual 1080p hp） 下级 （dual 720p hp） 下级的会场发双流，上级能得到
		//    上级（dual 720 hp） 下级 （dual 1080p hp） 下级的会场发双流，上级 不能 看到
		MdlError(Ums_Mdl_Call, ("OnOpenCasecadeDualChanCmd, Casecade dual recv chan not open. ConfID:%d, epID:%d\n", pInst->GetInsID(), tHandle.GetEpID()));
		
		TDualInfoAckTr tDualAck;
		tDualAck.m_bAccept = FALSE;
		tDualAck.m_tDualInfo = *ptDualCmd;
		UmsSendConfCtrl(tHandle, evtp_cascade_OpenDualChan_Ind, &tDualAck, sizeof(tDualAck));
		return;
	}


	MdlHint(Ums_Mdl_Call, ("OnOpenCasecadeDualChanCmd ConfID:%d, bStart:%d, IsChair:%d, ReqID:%d, wEpID:%d, backrtcp:"ADDRPORT_FORMAT"\n"
		, pInst->GetInsID(), m_bStart, pInst->IsChairConf(), m_wReqDual, tHandle.GetEpID(), ADDRNET(ptVidAddr->m_tBackRtcpAddr)));

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	
	TDualInfoAckTr tDualAck;
	tDualAck.m_bAccept = TRUE;
	tDualAck.m_tDualInfo = *ptDualCmd;

	tDualAck.m_tDualInfo.m_tDualCap.m_tVid.m_tChanAddr.m_tRtpAddr = ptNode->m_ptDualAddr->m_tVid.m_tRtpAddr;
	tDualAck.m_tDualInfo.m_tDualCap.m_tAud.m_tChanAddr.m_tRtpAddr = ptNode->m_ptDualAddr->m_tAud.m_tRtpAddr;
	UmsSendConfCtrl(tOutHandle, evtp_cascade_OpenDualChan_Ind, &tDualAck, sizeof(tDualAck));

	ptNode->m_tRmtChan.m_tDualVidEnc.m_tChanAddr.m_tBackRtcpAddr = ptDualCmd->m_tDualCap.m_tVid.m_tChanAddr.m_tBackRtcpAddr;
	ptNode->m_tRmtChan.m_tDualAudEnc.m_tChanAddr.m_tBackRtcpAddr = ptDualCmd->m_tDualCap.m_tAud.m_tChanAddr.m_tBackRtcpAddr;
}

void CDualMgr::OnOpenCascadeDualChanInd(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TDualInfoAckTr* ptDualAck = (TDualInfoAckTr*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	
	TTPMediaTransAddr* ptVidAddr = &ptDualAck->m_tDualInfo.m_tDualCap.m_tVid.m_tChanAddr;
	MdlHint(Ums_Mdl_Call, ("OnOpenCascadeDualChanInd ConfID:%d, wEpID:%d, rtp:"ADDRPORT_FORMAT" \n"
		, pInst->GetInsID(), tHandle.GetEpID(), ADDRNET(ptVidAddr->m_tRtpAddr)));
	
	TCapNode* ptChair = NULL;
	if(ptDualAck->m_bAccept)
    {
		ptChair = pInst->m_pcNodeMgr->GetCaller();
		
		ptChair->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr = ptDualAck->m_tDualInfo.m_tDualCap.m_tVid.m_tChanAddr.m_tRtpAddr;
		ptChair->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtpAddr = ptDualAck->m_tDualInfo.m_tDualCap.m_tAud.m_tChanAddr.m_tRtpAddr;
		
	}
}

BOOL32 CDualMgr::GetDualSrcName(TTPAlias& tAlias)
{
	CUmsConfInst* pInst = Inst();
	if (pInst->IsChairConf())
	{
		TCallNode* ptDualNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
		if (NULL != ptDualNode)
		{
			tAlias = ptDualNode->m_tConfName;			
		}
	}
	else
	{
		tAlias = m_tDualAlias;
	}

	return TRUE;
}


void CDualMgr::CloseSendChan(u16 wDualID)
{
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wDualID);
	TCallNode* ptFarter = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);

	if (NULL == ptNode || NULL == ptFarter)
	{
		MdlError(Ums_Mdl_Call, ("CloseSendChan failed. ConfID:%d, epID:%d\n", pInst->GetInsID(), wDualID));
		return;
	}

	MdlHint(Ums_Mdl_Call, ("CloseSendChan. ConfID:%d, epID:%d\n", pInst->GetInsID(), wDualID));
	TUmsHandle tOutHandle;
	if (ptNode == ptFarter)
	{
		if ( Is_Caller_Node(ptNode->m_wEpID) )
		{
			return;
		}
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, wDualID);
		UmsStopDual(tOutHandle);
	}
	else
	{
		TEpKey tKey;
		tKey.m_wEpID = ptNode->m_wLowChildEpID;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptFarter->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_StopSendDual_Ind, &tKey, sizeof(tKey));
	}
}

void CDualMgr::AjustAllDualMedia(BOOL32 bStart)
{
	CUmsConfInst* pInst = Inst();
	MdlHint(Ums_Mdl_Call, ("AjustAllDualMedia ConfID:%d, bStart:%d\n", pInst->GetInsID(), bStart));

	if(!pInst->GetUmsDiscuss()->IsDiscussModle())
	{//演讲模式 需要处理双流混音，如果当前双流源是cns尝试申请混音器，让323终端听到双流声音;
		if( bStart )
		{
			
			// 尝试申请一个混音器，否则尝试释放
			if (TRUE)
			{
				if (NULL == pInst->GetSpeaker().m_ptAudMix)
				{
					pInst->GetSpeaker().m_ptAudMix = pInst->GetEapu()->AssignMixer(VirSingleMixCB, pInst);
				}
				
				if ( NULL != pInst->GetSpeaker().m_ptAudMix )
				{
					pInst->GetSpeaker().m_bIsDualMixOn = TRUE; 
				}
				else
				{
					pInst->GetSpeaker().m_bIsDualMixOn = FALSE;
				}
			}
			else
			{
				if (NULL != pInst->GetSpeaker().m_ptAudMix && !pInst->GetUmsDiscuss()->IsUIDiscussOn())
				{// 如果界面不是讨论on状态，混音器释放
					pInst->GetEapu()->ReleaseMixer(pInst->GetSpeaker().m_ptAudMix);
					pInst->GetSpeaker().m_ptAudMix = NULL;
					CNetPortMgr::FreeMediaTrans(pInst, pInst->GetSpeaker().m_tToAudMixDs);
				}
				pInst->GetSpeaker().m_bIsDualMixOn = FALSE;
			}
		}
		else
		{//退出
			if ( NULL != pInst->GetSpeaker().m_ptAudMix && !pInst->GetUmsDiscuss()->IsUIDiscussOn())
			{
				pInst->GetEapu()->ReleaseMixer(pInst->GetSpeaker().m_ptAudMix);
				pInst->GetSpeaker().m_ptAudMix = NULL;
				CNetPortMgr::FreeMediaTrans(pInst, pInst->GetSpeaker().m_tToAudMixDs);
			}
			pInst->GetSpeaker().m_bIsDualMixOn = FALSE;
		}
		
	}
	else
	{
		if (pInst->IsChairConf())
		{
			pInst->GetUmsDiscuss()->AdjustDualAudMedia();
		}
		else
		{// 讨论下，如果双流开启，那么下级的单屏会场双流声音，直接从上级下传下来，混音器可以释放

			if (NULL != pInst->GetSpeaker().m_ptAudMix)
			{// 混音器释放
				pInst->GetEapu()->ReleaseMixer(pInst->GetSpeaker().m_ptAudMix);
				pInst->GetSpeaker().m_ptAudMix = NULL;
				CNetPortMgr::FreeMediaTrans(pInst, pInst->GetSpeaker().m_tToAudMixDs);
			}
			pInst->GetSpeaker().m_bIsDualMixOn = FALSE;

		}
	}

	CNetPortMgr::CreateSpeakerToVirSpeaker(pInst); //

	pInst->GetVmp()->AdjustDual();

	pInst->AdjustNewSpeakerToAllNode( TP_INVALID_INDEX, TRUE);

	return;
}


void CDualMgr::NotifyAllEpStartRcvDual(u16 wExceptID)
{
	CUmsConfInst* pInst = Inst();
	
	TCallNode* ptSrcNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
	TCapNode* ptSrcForther = pInst->m_pcNodeMgr->GetForeFatherNode(ptSrcNode);

	TUmsHandle tOutHandle;

	TEpKeyEx tSrcKeyEx;

	if ( m_bStart && wExceptID != m_wCurDual )
	{
		//抢断 则向新的双流源发送一次开始接收
		tSrcKeyEx.m_wEpID = TP_INVALID_INDEX;
		if (NULL != ptSrcForther)
		{
			MdlHint(Ums_Mdl_Call, ("Notify ExDualEp Rcv Dual, ConfID:%d, CurDualEp:%d, ReqDualEp:%d\n", pInst->GetInsID(), m_wCurDual, m_wReqDual));
			tSrcKeyEx.m_wEpID = ptSrcNode->m_wLowChildEpID;

			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptSrcForther->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_StartRcvDual_Ind, &tSrcKeyEx, sizeof(tSrcKeyEx));
		}

		return ;
	}

	MdlHint(Ums_Mdl_Call, ("NotifyAllEpStartDual ConfID:%d\n", pInst->GetInsID()));

	TCallNode* ptNode;
	for (ptNode = pInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pInst->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->m_bUsed || !ptNode->IsChanOn() || wExceptID == ptNode->m_wEpID)
		{
			continue;
		}
		
		tSrcKeyEx.m_wEpID = TP_INVALID_INDEX;
		if (NULL != ptSrcForther && ptSrcForther == ptNode)
		{	
			tSrcKeyEx.m_wEpID = ptSrcNode->m_wLowChildEpID;
		}
		
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		
		UmsSendConfCtrl(tOutHandle, evtp_Conf_StartRcvDual_Ind, &tSrcKeyEx, sizeof(tSrcKeyEx));
	}

	ptNode = pInst->m_pcNodeMgr->GetCaller();
	if (ptNode->IsChanOn() && wExceptID != ptNode->m_wEpID)
	{
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		tSrcKeyEx.m_wEpID = m_wCurDual; 
		UmsSendConfCtrl(tOutHandle, evtp_Conf_StartRcvDual_Ind, &tSrcKeyEx, sizeof(tSrcKeyEx));
	}
}

void CDualMgr::NotifyAllEpSrcDualName(u16 wExceptID)
{
	CUmsConfInst* pInst = Inst();
	MdlHint(Ums_Mdl_Call, ("NotifyAllEpSrcDualName ConfID:%d\n", pInst->GetInsID()));
	
	u8 abyBuf[sizeof(TTPAlias)+sizeof(TEpKey)];
	TTPAlias* ptAlias = (TTPAlias*)abyBuf;
	TEpKey* ptSrcKey = (TEpKey*)(abyBuf+sizeof(TTPAlias));
	ptAlias->Clear();
	ptSrcKey->Clear();
	GetDualSrcName(*ptAlias);

	TCallNode* ptDualNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
	TCapNode* ptDualFather = pInst->m_pcNodeMgr->GetForeFatherNode(ptDualNode);
	TUmsHandle tOutHandle;
	TCallNode* ptNode;
	for (ptNode = pInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pInst->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->m_bUsed || !ptNode->IsChanOn() || wExceptID == ptNode->m_wEpID)
		{
			continue;
		}
		
		ptSrcKey->m_wEpID = TP_INVALID_INDEX;
		if (NULL != ptDualFather && ptNode->m_wEpID == ptDualFather->m_wEpID)
		{
			ptSrcKey->m_wEpID = ptDualNode->m_wLowChildEpID;
		}

		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_SrcDualName_Ind, abyBuf, sizeof(abyBuf));	
	}

	ptNode = pInst->m_pcNodeMgr->GetCaller();
	if (ptNode->IsChanOn() && wExceptID != ptNode->m_wEpID)
	{
		ptSrcKey->m_wEpID = m_wCurDual;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_SrcDualName_Ind, abyBuf, sizeof(abyBuf));
	}

	//通知界面
	DualEpNotify();

	return ;
}

void CDualMgr::ExitDualModel(u16 wExceptID)
{	
	CUmsConfInst* pInst = Inst();
	MdlHint(Ums_Mdl_Call, ("ExitDualModel ConfID:%d, start:%d\n", pInst->GetInsID(), m_bStart));
	if (!m_bStart  && pInst->IsChairConf())
	{
		m_wCurDual = TP_INVALID_INDEX;
		m_wReqDual = TP_INVALID_INDEX;
		m_bStart = FALSE;
		pInst->GetBas()->ReleaseDualBas();
		return;		
	}
	EmTPDualReason emDual = emTpDualPreemptive;	
	
	TUmsHandle tOutHandle;
	TCallNode* ptNode;

	if (!pInst->IsChairConf())
	{	
		CNetPortMgr::DestroyDualFromDownToUp(pInst);
	}
	
	if (TP_VALID_HANDLE(m_wCurDual))
	{
		CloseSendChan(m_wCurDual);
	}

	if (TP_VALID_HANDLE(m_wReqDual))
	{
		CloseSendChan(m_wReqDual);
	}
	
	for (ptNode = pInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pInst->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->m_bUsed || !ptNode->IsChanOn() || wExceptID == ptNode->m_wEpID)
		{
			continue;	
		}
		
		if (ptNode->Is323Ep())
		{// 双流结束，关闭到323的双流
			CloseSendChan(ptNode->m_wEpID);
		}

		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_StopRcvDual_Ind, &emDual, sizeof(emDual));	
	}

	ptNode = pInst->m_pcNodeMgr->GetCaller();
	if (ptNode->IsChanOn() && wExceptID != ptNode->m_wEpID)
	{
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_Conf_StopRcvDual_Ind, &emDual, sizeof(emDual));	
	}
	
	m_wCurDual = TP_INVALID_INDEX;
	m_wReqDual = TP_INVALID_INDEX;
	m_bStart = FALSE;

	m_wNextDual = TP_INVALID_INDEX;

	m_tToUpUms.Clear();

	AjustAllDualMedia(FALSE);
	CNetPortMgr::AjustDualFromNodeToUms(pInst);

	// 停止双流，释放双流适配
	pInst->GetBas()->ReleaseDualBas();

	DualEpNotify();

	m_tDualDsEpToUms.Clear();

	return ;
}

void CDualMgr::DualEpNotify()
{
	CUmsConfInst* pInst = Inst();

	TConfEpID tConfEp;
	tConfEp.m_wConfID = pInst->GetInsID();
	tConfEp.m_wEpID = m_wCurDual;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_DualEp_Notify);
	cMsg.SetBody(&tConfEp, sizeof(tConfEp));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));

	if ( pInst->IsChairConf() )
	{
		pInst->NotifyConfCtrlMsgToAllCns(ev_UmsConfDualEp_Nty, &tConfEp, sizeof(tConfEp));
	}

	return ;
}


void CDualMgr::OnStartDualCmd( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle = *(TUmsHandle*)(ptMsg->GetBody());
	TConfEpID tEpID = *(TConfEpID*)( ptMsg->GetBody() + sizeof(TUmsHandle) );

	if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) )
	{
		return ;
	}

	EmTPDualReason emReason = emTpDualPeerReject;
	s8 bySndBuf[sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
	memcpy(bySndBuf, &tEpID, sizeof(TConfEpID));
	memcpy(bySndBuf + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));

	if ( localmax(pInst->GetConfBase().m_wHpDualBitRate, pInst->GetConfBase().m_wBpDualBitRate) == 0 )
	{//模板配置双流码流为0 ，则拒绝双流发起
		MdlError(Ums_Mdl_Call, ("OnStartDualCmd  ums dual BitRate is Zero. ConfID:%d, epID:%d\n", pInst->GetInsID(), tEpID.m_wEpID));
		pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStartDual_Ind, tHandle.GetEpID(), bySndBuf, sizeof(bySndBuf));
		return;
	}
	
	if ( m_wCurDual == pInst->curSpeakerID() )
	{
		TCallNode* ptSpeaker = Inst()->GetNodeMgr()->GetNode(Inst()->curSpeakerID());
		if ( NULL != ptSpeaker && ptSpeaker->IsChanOn() && ptSpeaker->IsVRS() )
		{
			MdlError(Ums_Mdl_Call, ("OnStartDualCmd. VRS is curDualEP!!! ConfID:%d, start:%d, DstEpID:%d, CurDual:%d\n", 
				pInst->GetInsID(), m_bStart, tEpID.m_wEpID, m_wCurDual));
			
			pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStartDual_Ind, tHandle.GetEpID(), bySndBuf, sizeof(bySndBuf));
			return ;
		}
	}

	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(tEpID.m_wEpID);
	if ( NULL == ptNode || ( tEpID.m_wEpID == m_wCurDual && m_bStart ) )
	{
		MdlError(Ums_Mdl_Call, ("OnStartDualCmd. ptNode is NULL or DstDual Same!. ConfID:%d, start:%d, DstEpID:%d, CurDual:%d\n", 
			pInst->GetInsID(), m_bStart, tEpID.m_wEpID, m_wCurDual));

		pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStartDual_Ind, tHandle.GetEpID(), bySndBuf, sizeof(bySndBuf));
		return ;
	}

	if (!ptNode->IsMtEp())
	{
		MdlError(Ums_Mdl_Call, ("OnStartDualCmd  ptNode is not mt. ConfID:%d, epID:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
		pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStartDual_Ind, tHandle.GetEpID(), bySndBuf, sizeof(bySndBuf));
		return;
	}

	if ( !pInst->GetBas()->AssignDualBas() )
	{
		MdlError(Ums_Mdl_Call, ("OnStartDualCmd. Bas is Full!. ConfID:%d, start:%d, DstEpID:%d, CurDual:%d\n", 
			pInst->GetInsID(), m_bStart, tEpID.m_wEpID, m_wCurDual));
		
		pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStartDual_Ind, tHandle.GetEpID(), bySndBuf, sizeof(bySndBuf));
		Inst()->NotifyReasonToUI( EmUI_CNC, TP_UMS_Dual_BasFull, Inst()->chairID());
		return ;
	}
	
	OnStartDualCmdForUmcCnc(tEpID.m_wEpID);

	return ;
}

void CDualMgr::OnStopDualCmd( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle = *(TUmsHandle*)(ptMsg->GetBody());
	TConfEpID tEpID = *(TConfEpID*)( ptMsg->GetBody() + sizeof(TUmsHandle) );

	if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) )
	{
		return ;
	}

	EmTPDualReason emReason = emTpDualAccept;

	if (m_wCurDual == tEpID.m_wEpID)
	{
		TCallNode* ptSpeaker = Inst()->GetNodeMgr()->GetNode(Inst()->curSpeakerID());
		if ( NULL != ptSpeaker && ptSpeaker->IsChanOn() && ptSpeaker->IsVRS() && m_wCurDual == pInst->curSpeakerID() )
		{
			MdlError(Ums_Mdl_Call, ("OnStopDualCmd. VRS is curDualEP!!! ConfID:%d, start:%d, DstEpID:%d, CurDual:%d\n", 
				pInst->GetInsID(), m_bStart, tEpID.m_wEpID, m_wCurDual));
			
			emReason = emTpDualPeerReject;
		}
		else
		{
			OnStopDualCmdForUmcCnc();
		}
	}
	else
	{
		emReason = emTpDualPeerReject;
	}
	
	s8 bySndBuf[sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
	memcpy(bySndBuf, &tEpID, sizeof(TConfEpID));
	memcpy(bySndBuf + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));
	pInst->NotifyConfCtrlMsgToCns(ev_UmsConfStopDual_Ind, tHandle.GetEpID(), bySndBuf, sizeof(bySndBuf));

	MdlHint(Ums_Mdl_Call, ("OnStopDualCmd ConfID:%d, start:%d, DstEpID:%d\n", pInst->GetInsID(), m_bStart, tEpID.m_wEpID));
	
	return ;
}

void CDualMgr::ChangeDualEpProc(u16 wExpeceID)
{
	CUmsConfInst* pInst = Inst();

	NotifyAllEpStartRcvDual(wExpeceID);

	m_wCurDual = m_wReqDual;
	m_wReqDual = TP_INVALID_INDEX;

	m_bStart = TRUE;

	//调整双流
	Inst()->m_pcBas->AdjustDualBas();
	
	AjustAllDualMedia();
	NotifyAllEpSrcDualName(wExpeceID);
	CNetPortMgr::AjustDualFromNodeToUms(Inst());

	if( !Inst()->IsChairConf() )
	{//每次都运行一次，本交换需要根据双流源格式调整
		CNetPortMgr::CreateDualFromDownToUp(Inst());
	}

	return ;
}

BOOL32 CDualMgr::AskFrameForSeeDual( TUmsVidFormat& tVidFormat, BOOL32 bReqBySys , BOOL32 bReqToScrEp)
{
	if ( !m_bStart )
	{
		tpLowDtl(Ums_Mdl_Call, "CDualMgr::AskFrameForSeeDual. Dual not Start!\n");
		return FALSE;
	}

	tpLowDtl(Ums_Mdl_Call, "CDualMgr::AskFrameForSeeDual ConfID:%d, ReqSys:%d\n", Inst()->GetInsID(), bReqBySys);

	if( bReqToScrEp || !Inst()->GetBas()->IsDualNeedBas(tVidFormat) )
	{//双流单格式 或 该格式无需适配
		TUmsHandle tHandle;
		tHandle.MakeAppHandle(Inst()->GetInsID(), TP_INVALID_INDEX);
		CTpMsg tAskMsg;
		tAskMsg.SetBody(&tHandle, sizeof(tHandle));
		tAskMsg.CatBody(&bReqBySys, sizeof(bReqBySys));
		OnAskKeyFrame(&tAskMsg);
	}
	else
	{
		Inst()->GetBas()->SeeDualAskFrameToBas();
	}
	
	return TRUE;
}

void CDualMgr::CheckEpDualRcv(u16 wExceptID, u16 wExceptID2, u16 wExceptID3)
{
    //检查除双流源外的在线会场双流接收是否打开
	CUmsConfInst* pInst = Inst();

	MdlHint(Ums_Mdl_Call, ("CheckEpDualRcv, Confid:%d, ExceptID(%d, %d, %d) \n", pInst->GetInsID(), wExceptID, wExceptID2, wExceptID3));

	for (TCapNode* ptTmp = pInst->GetNodeMgr()->FirstNode(); ptTmp != NULL;  ptTmp = pInst->GetNodeMgr()->NextLoalNode(ptTmp) )
	{
		if (NULL == ptTmp)
		{
			continue;
		}
		
		if (ptTmp->m_wEpID == wExceptID || ptTmp->m_wEpID == wExceptID2 || ptTmp->m_wEpID == wExceptID3)
		{
			continue;
		}
		
		if (!ptTmp->IsCallOn() || !ptTmp->IsChanOn())
		{
			continue;
		}

		//VRS不用动通道
		if ( ptTmp->IsVRS() && !ptTmp->IsVidRcvValid())
		{
			continue;
		}
		
		if (!ptTmp->m_bCheckDualRcv)
		{
			MdlHint(Ums_Mdl_Call, ("CheckEpDualRcv, Confid:%d, ep:%d  CheckDualRcv fail \n", pInst->GetInsID(), ptTmp->m_wEpID));
			continue;
		}

		if (EmChanIdle == ptTmp->m_tRmtChan.m_tDualVidDec.m_emChanState)
		{
			MdlHint(Ums_Mdl_Call, ("CheckEpDualRcv, begin MakeDualCap, Confid:%d, Node:%d, Type:%d\n", pInst->GetInsID(), ptTmp->m_wEpID, ptTmp->m_emEpType));
			ptTmp->m_bCheckDualRcv = TRUE;
			MakeDualCap(ptTmp, TRUE);
		}
	}
}

void CDualMgr::OnStartDualCmdFormUmc( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID tEpID	= *(TConfEpID*)(pData+sizeof(TLogUser));

	CUmsConfInst* pInst = Inst();

	do
	{
		if ( localmax(pInst->GetConfBase().m_wHpDualBitRate, pInst->GetConfBase().m_wBpDualBitRate) == 0 )
		{
			MdlError(Ums_Mdl_Call, ("OnStartDualCmdFormUmc. ums dual BitRate is Zero!. ConfID:%d, start:%d, DstEpID:%d, CurDual:%d\n", 
				pInst->GetInsID(), m_bStart, tEpID.m_wEpID, m_wCurDual));
			break;
		}

		TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(tEpID.m_wEpID);
		if ( NULL == ptNode || ( tEpID.m_wEpID == m_wCurDual && m_bStart ) )
		{
			MdlError(Ums_Mdl_Call, ("OnStartDualCmdFormUmc. ptNode is NULL or DstDual Same!. ConfID:%d, start:%d, DstEpID:%d, CurDual:%d\n", 
				pInst->GetInsID(), m_bStart, tEpID.m_wEpID, m_wCurDual));
			break;
		}

		if (!ptNode->IsMtEp())
		{
			MdlError(Ums_Mdl_Call, ("OnStartDualCmdFormUmc  ptNode is not mt. ConfID:%d, epID:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
			break;
		}

		if ( !pInst->GetBas()->AssignDualBas() )
		{
			MdlError(Ums_Mdl_Call, ("OnStartDualCmdFormUmc. Bas is Full!. ConfID:%d, start:%d, DstEpID:%d, CurDual:%d\n", 
				pInst->GetInsID(), m_bStart, tEpID.m_wEpID, m_wCurDual));
			Inst()->NotifyReasonToUI( EmUI_UMC, TP_UMS_Dual_BasFull);
			break;
		}

		OnStartDualCmdForUmcCnc(tEpID.m_wEpID);
		return;

	}while(0);

	EmTPDualReason emReason = emTpDualPeerReject;	
	s8 bySndBuf[sizeof(TLogUser) + sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
	memcpy(bySndBuf, ptUserTmp, sizeof(TLogUser));
	memcpy(bySndBuf + sizeof(TLogUser), &tEpID, sizeof(TConfEpID));
	memcpy(bySndBuf + sizeof(TLogUser) + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));
	pInst->NotifyMsgToService(evtp_StartDual_Ind, bySndBuf, sizeof(bySndBuf));

	return ;

}

void CDualMgr::OnStopDualCmdFormUmc( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wAppID = GETAPP(ptMsg->GetSrcIId());
	TLogUser* ptUserTmp = (TLogUser*)pData;
	TConfEpID tEpID	= *(TConfEpID*)(pData+sizeof(TLogUser));

	CUmsConfInst* pInst = Inst();
	EmTPDualReason emReason = emTpDualAccept;
	
	if (m_wCurDual == tEpID.m_wEpID)
	{
		OnStopDualCmdForUmcCnc();
	}
	else
	{
		emReason = emTpDualPeerReject;
	}
	
	s8 bySndBuf[sizeof(TLogUser) + sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
	memcpy(bySndBuf, ptUserTmp, sizeof(TLogUser));
	memcpy(bySndBuf + sizeof(TLogUser), &tEpID, sizeof(TConfEpID));
	memcpy(bySndBuf + sizeof(TLogUser) + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));

	pInst->NotifyMsgToService(evtp_StopDual_Ind, bySndBuf, sizeof(bySndBuf));
	
	MdlHint(Ums_Mdl_Call, ("OnStopDualCmdFormUmc ConfID:%d, start:%d, DstEpID:%d\n", pInst->GetInsID(), m_bStart, tEpID.m_wEpID));
	
	return ;
}

void CDualMgr::OnStartDualCmdForUmcCnc(u16 wEpId)
{
	CUmsConfInst* pInst = Inst();

	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wEpId);
	TCapNode* ptForeFatherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptForeFatherNode->m_wEpID);
	
	TEpKeyEx tEpKey;
	if ( ptNode == ptForeFatherNode )
	{
		tEpKey.m_wEpID = ptNode->m_wEpID;
	}
	else
	{
		tEpKey.m_wEpID = ptNode->m_wLowChildEpID;
	}
	
	UmsSendConfCtrl(tOutHandle, evtp_Conf_RequestDualStream_cmd, &tEpKey, sizeof(tEpKey));
	
	if ( m_bStart && TP_VALID_HANDLE(m_wCurDual) )
	{//如果是抢断双流
		//主动向发言人或主席请求关键帧
		pInst->AskKeyByEpID(pInst->chairID(), EmAskKeyChair);
		if (pInst->chairID() != pInst->curSpeakerID())
		{
			pInst->AskKeyByEpID(pInst->curSpeakerID(), EmAskKeySpeaker);
		}
	}
	
	m_wChairReq = wEpId;
	
	MdlHint(Ums_Mdl_Call, ("OnStartDualCmdForUmcCnc ConfID:%d, start:%d, DstEpID:%d, ChairReq:%d\n", pInst->GetInsID()
			, m_bStart, wEpId, m_wChairReq));
}

void CDualMgr::OnStopDualCmdForUmcCnc()
{
	CUmsConfInst* pInst = Inst();
		
	ExitDualModel(TP_INVALID_INDEX);
		
	//主动向发言人请求关键帧
	pInst->AskKeyByEpID(pInst->chairID(), EmAskKeyChair);
		if (pInst->chairID() != pInst->curSpeakerID())
	{
		pInst->AskKeyByEpID(pInst->curSpeakerID(), EmAskKeySpeaker);
	}
}

void CDualMgr::ChangeSpeakerForVRS()
{
	CUmsConfInst* pInst = Inst();

	TCallNode* ptSpeaker = pInst->GetNodeMgr()->GetNode(Inst()->curSpeakerID());

	if ( NULL == ptSpeaker || !ptSpeaker->IsChanOn() )
	{
		return ;
	}

	if ( !ptSpeaker->IsVRS() )
	{//当前发言人不是vrs
		if ( TP_VALID_HANDLE(m_wCurDual) )
		{//此时如果双流源是vrs，则停止双流
			TCallNode* ptDualNode = pInst->GetNodeMgr()->GetNode(m_wCurDual);
			if ( NULL != ptSpeaker && ptDualNode->IsChanOn() && ptDualNode->IsVRS() )
			{
				m_wCurDual = TP_INVALID_INDEX;
				ExitDualModel(TP_INVALID_INDEX);
			}
		}
		return ;
	}

	if ( !ptSpeaker->m_tDualVidSndFormat.IsValid() )
	{
		return ;
	}

	m_wReqDual = ptSpeaker->m_wEpID;

	TCallNode* ptOldNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
	TCapNode* ptOldFarther = pInst->m_pcNodeMgr->GetForeFatherNode(ptOldNode);				
	TUmsHandle tOutHandle;
	if (NULL != ptOldNode && NULL != ptOldFarther && CALLER_EP_INDEX != m_wCurDual)
	{					
		if (ptOldNode == ptOldFarther)
		{
			StopEpSndDual(ptOldFarther, emTPForceStop);
		}
		else
		{
			TEpKey tKey;
			tKey.m_wEpID = ptOldNode->m_wLowChildEpID;
			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, ptOldFarther->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_Conf_StopSendDual_Ind, &tKey, sizeof(tKey));
		}
		ptOldFarther->m_tRmtChan.m_tDualVidDec.m_tKeyFrameStatis.Clear();
	}
	
	CheckEpDualRcv(m_wReqDual);
	
	ChangeDualEpProc();
}

#ifdef _USE_XMPUEQP_

void CDualMgr::DualXmpuAudMixCB(u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData)
{
	TXmpuStartMixNty  tStartInfo;
    TXmpuAddMixMemNty tAddMemInfo;
	
	BOOL32 bError = FALSE;
	
    if (dwEvent == evXmpu_UmsStartMix_Nty)
	{
        memcpy(&tStartInfo, pData, sizeof(tStartInfo));
		if (!tStartInfo.m_bSuccess)
		{
            bError = TRUE;
		}
	} else if (dwEvent == evUms_XmpuAddMixMember_Nty)
	{
		memcpy(&tAddMemInfo, pData, sizeof(TXmpuAddMixMemNty));
		if (!tAddMemInfo.m_bSuccess)
		{
			bError = TRUE;
		}
	} else if (dwEvent == evXmpu_VacActive_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixVoiceDetection_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixDisConnect_Nty)
	{
		bError = TRUE;
	}
	
	if (bError)
	{
		MdlError(Ums_Mdl_Call, ("[CDualMgr::DualXmpuAudMixCB] ConId:%d, CBType:%d(startfail:%d, addmemfail:%d, discon:%d ), StopDual\n", 
			Inst()->GetInsID(), dwEvent, evXmpu_UmsStartMix_Nty, evUms_XmpuAddMixMember_Nty, evXmpu_MixDisConnect_Nty));
		
    	OnStopDualCmdForUmcCnc();
	//给界面提示
	    Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Dual_MixDisCnnt, Inst()->chairID());
    	return ;
	}
	
	return;
}

#else
void CDualMgr::DualAudMixCB( TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo )
{
	//停止双流
	OnStopDualCmdForUmcCnc();

	//给界面提示
	Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Dual_MixDisCnnt, Inst()->chairID());
	return ;
}
#endif

void CDualMgr::AdjustDualMediaForDiscuss()
{
	CUmsConfInst* pInst = Inst();

	MdlHint(Ums_Mdl_Call, ("AdjustDualMediaForDiscuss ConfID:%d, m_bStart:%d, m_wCurDual:%d, ChairReq:%d\n", pInst->GetInsID()
			, m_bStart, m_wCurDual));

	if (!m_bStart || NULL == pInst->GetSpeaker().m_ptAudMix)
	{
		return;
	}

	TCallNode* ptDualNode = pInst->m_pcNodeMgr->GetNode(m_wCurDual);
	if (NULL == ptDualNode)
	{
		MdlError(Ums_Mdl_Call, ("AdjustDualMediaForDiscuss m_wCurDual Node is NULL! ConfID:%d, wCurDual:%d, bStart:%d\n", 
						pInst->GetInsID(), m_wCurDual, m_bStart));
		return;
	}
				

	if (ptDualNode->IsCns() && emTPAEnd != ptDualNode->m_tDualAudSndFormat.m_tFormat.m_emFormat)
	{
		TAudMixMemberInfo tInfo;
		tInfo.AddMixMember(m_wCurDual, TP_MAX_STREAMNUM+1);
		tInfo.AddMixMember(pInst->curSpeakerID(), TP_MAX_STREAMNUM);
		if( pInst->curSpeakerID() != pInst->chairID() )
		{
			tInfo.AddMixMember(pInst->chairID(), TP_MAX_STREAMNUM);
		}
					
		pInst->GetEapu()->AdjustAudMixMember(pInst->GetSpeaker().m_ptAudMix, &tInfo);
		pInst->GetSpeaker().m_bIsDualMixOn = TRUE;
		CNetPortMgr::CreateMediaToSingleMixer(pInst);
	}
	else
	{
		if (!pInst->GetUmsDiscuss()->IsUIDiscussOn())
		{// 如果界面不是讨论on状态，混音器释放
			pInst->GetEapu()->ReleaseMixer(pInst->GetSpeaker().m_ptAudMix);
			pInst->GetSpeaker().m_ptAudMix = NULL;
			CNetPortMgr::FreeMediaTrans(pInst, pInst->GetSpeaker().m_tToAudMixDs);
		}
		pInst->GetSpeaker().m_bIsDualMixOn = FALSE;
	}

	return;
}

void CDualMgr::AdjustDualMix()
{
	CUmsConfInst* pInst = Inst();

	TAudMixMemberInfo tInfo;

	TCallNode* ptDualNode = Inst()->GetNode(m_wCurDual);
	if (NULL != ptDualNode && ptDualNode->IsChanOn() && 
		emTPAEnd != ptDualNode->m_tDualAudSndFormat.m_tFormat.m_emFormat)
	{
		tInfo.AddMixMember(m_wCurDual, TP_MAX_STREAMNUM+1);
	}

	tInfo.AddMixMember(pInst->curSpeakerID(), TP_MAX_STREAMNUM);
	if( pInst->curSpeakerID() != pInst->chairID() )
	{
		tInfo.AddMixMember(pInst->chairID(), TP_MAX_STREAMNUM);
	}
	pInst->GetEapu()->AdjustAudMixMember(pInst->GetSpeaker().m_ptAudMix, &tInfo);

	CNetPortMgr::CreateMediaToSingleMixer(pInst);

	return;
}


void CDualMgr::AdjustDualMixForRollCall()
{
	CUmsConfInst* pInst = Inst();
	
    if (pInst->IsChairConf())
	{
		TAudMixMemberInfo tInfo;

		TCallNode* ptDualNode = Inst()->GetNode(m_wCurDual);
		if (NULL != ptDualNode && ptDualNode->IsChanOn() && 
			emTPAEnd != ptDualNode->m_tDualAudSndFormat.m_tFormat.m_emFormat)
		{
			tInfo.AddMixMember(m_wCurDual, TP_MAX_STREAMNUM+1);
		}

		tInfo.AddMixMember(pInst->curSpeakerID(), TP_MAX_STREAMNUM);

        u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();
		tInfo.AddMixMember(wRollCaller, TP_MAX_STREAMNUM);

		pInst->GetEapu()->AdjustAudMixMember(pInst->GetSpeaker().m_ptAudMix, &tInfo);

		// 点名人 + 被点名人 + 双流
		CNetPortMgr::CreateRollCallMediaToDulMixer(pInst);
	}
	else
	{  
       //下级不使用mix 
        
	}


	return;
}



void CDualMgr::AdjustDualMixForConfAudMix()
{
	CUmsConfInst* pInst = Inst();
	
    if (pInst->IsChairConf())
	{
		pInst->GetAudMix()->CheckDualMixChan();

        //调整双流的MIX
		pInst->GetAudMix()->CreatToDulAudMix(m_wCurDual);
	}
	else
	{  
		//下级不使用mix 
        
	}
}