#include "umsdiscussnew.h"
#include "umsconfinst.h"
#include "umsstackinterface.h"
#include "putaud.h"
#include "eventoutsipadapter.h"
#include "umsnetportmgr.h"

CPutAud::CPutAud( CUmsConfInst* pcInst )
{
	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex ++ )
	{
		m_atChanle[wIndex].Clear();
		m_atChanle[wIndex].m_wIndx = wIndex;
	}

	m_pcConf = pcInst;
}

CPutAud::~CPutAud()
{
	
}

BOOL32 CPutAud::Handler( CTpMsg *const ptMsg )
{
	BOOL32 bProc = TRUE;
	switch(ptMsg->GetEvent())
	{
	case evtp_OpenVidChan_Cmd:
		{
			OnAudChnlReq(ptMsg);
			m_pcConf->GetUmsDiscuss()->OpenEpDownAudCmd(ptMsg);
			m_pcConf->GetRollCallMgr()->OpenEpDownAudCmd(ptMsg);
			m_pcConf->GetAudMix()->OpenEpDownAudCmd(ptMsg);
		}
		break;
	case evtp_OpenVidChan_Ack:
		{
			OnAudChnlRsp(ptMsg);
			m_pcConf->GetUmsDiscuss()->OpenEpDownAudAck(ptMsg);
			m_pcConf->GetRollCallMgr()->OpenEpDownAudAck(ptMsg);
			m_pcConf->GetAudMix()->OpenEpDownAudAck(ptMsg);
		}
		break;
	case evtp_CloseVidChan_Cmd:
		{
			OnAudChnlClose(ptMsg);
			m_pcConf->GetUmsDiscuss()->CloseEpDownAudCmd(ptMsg);
			m_pcConf->GetRollCallMgr()->CloseEpDownAudCmd(ptMsg);
			m_pcConf->GetAudMix()->CloseEpDownAudCmd(ptMsg);
		}
		break;
	default:
		bProc = FALSE;
		break;
	}

	return bProc;
}

void CPutAud::Show()
{
	msgprintnotime("putaud info: confID:%d\n", m_pcConf->GetInsID());
	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex ++ )
	{
		if ( !m_atChanle[wIndex].m_bUsed )
		{
			continue;
		}

		msgprintnotime("index:%d, EpID:%d, check:%d, user:%d, usednum:%d\n", wIndex, m_atChanle[wIndex].m_wEpID, 
			m_atChanle[wIndex].m_wCheck, m_atChanle[wIndex].m_emUser, m_atChanle[wIndex].m_wUsedNum);
		for ( u16 wScrIndx = 0; wScrIndx < TP_MAX_STREAMNUM; wScrIndx ++ )
		{
			if ( NULL == m_atChanle[wIndex].m_aptLocalAddr[wScrIndx] )
			{
				continue;
			}
			msgprintnotime("local:%d rtp:"ADDRPORT_FORMAT", rtcp:"ADDRPORT_FORMAT", rmt rtp:"ADDRPORT_FORMAT" rtcp:"ADDRPORT_FORMAT" \n", 
				wScrIndx,
				ADDRNET(m_atChanle[wIndex].m_aptLocalAddr[wScrIndx]->m_tRtpAddr), ADDRNET(m_atChanle[wIndex].m_aptLocalAddr[wScrIndx]->m_tBackRtcpAddr),
				ADDRNET(m_atChanle[wIndex].m_atRmtAddr[wScrIndx].m_tRtpAddr), ADDRNET(m_atChanle[wIndex].m_atRmtAddr[wScrIndx].m_tBackRtcpAddr)
				);
		}
		msgprintnotime("\n");
	}
}

void CPutAud::OnAudChnlReq( CTpMsg *const ptMsg )
{
	TVidChanCmd* ptVidCmd = (TVidChanCmd*)(ptMsg->GetBody() + sizeof(TUmsHandle));
	
	TVidChanAck tVidAck;
	tVidAck.m_tEpKey.m_wEpID = ptVidCmd->m_tEpKey.m_wEpID;
	tVidAck.m_atUpBackRtcp[0].m_tAddr.m_wPort = ptVidCmd->m_atUpRtp[0].m_tAddr.m_wPort;
	tVidAck.m_atUpBackRtcp[1].m_tAddr.m_wPort = ptVidCmd->m_atUpRtp[1].m_tAddr.m_wPort;
		
	MdlHint(Ums_Mdl_Call, ("CPutAud::OnAudChnlReq. ConfID:%d, wEpID:%d, wIndex:%d\n", 
		m_pcConf->GetInsID(), ptVidCmd->m_tEpKey.m_wEpID, ptVidCmd->m_atUpRtp[0].m_tAddr.m_wPort));
	MdlHint(Ums_Mdl_Call, ("	AudBackRtcp0:"ADDRPORT_FORMAT", AudBackRtcp1:"ADDRPORT_FORMAT", AudBackRtcp2:"ADDRPORT_FORMAT"\n",
		ADDRNET(ptVidCmd->m_atAudBackRtcp[0]), ADDRNET(ptVidCmd->m_atAudBackRtcp[1]), ADDRNET(ptVidCmd->m_atAudBackRtcp[2])));

	TUmsHandle tOutHandle;
	m_pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);

	TCallNode* ptNode = m_pcConf->GetNodeMgr()->GetNode(tVidAck.m_tEpKey.m_wEpID);
	TCapNode* ptNodeFather = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptNode);		
	if (NULL == ptNode || NULL == ptNodeFather || !ptNode->IsChanOn())
	{
		tVidAck.m_wReason = TP_RET_ERROR;
		UmsSendConfCtrl(tOutHandle, evtp_OpenVidChan_Ack, &tVidAck, sizeof(tVidAck));
		return ;
	}

    EmPutAudUser emUser = (EmPutAudUser)ptVidCmd->m_atUpRtp[1].m_tAddr.m_wPort;
	ReleaseRepeatdPutAudForDown(m_pcConf->GetInsID(), ptNode->m_wEpID, emUser);

	TPutAudChnl* ptPutAud = FindIdle();
	if ( NULL == ptPutAud )
	{
		tVidAck.m_wReason = TP_RET_ERROR;
		UmsSendConfCtrl(tOutHandle, evtp_OpenVidChan_Ack, &tVidAck, sizeof(tVidAck));
		return ;
	}

	BOOL32 bError = FALSE;
	ForEachChanList(ptNode->m_wAudRcvNum,
		ptPutAud->m_aptLocalAddr[ewIndex] = m_pcConf->GetPutAudAddrList()->AllocNode();\
		if ( NULL == ptPutAud->m_aptLocalAddr[ewIndex] )\
		{\
		bError = TRUE;\
		break;\
		}\
		ptPutAud->m_aptLocalAddr[ewIndex]->SetIP(m_pcConf->GetConfEqpDs().m_dwEqpIp);
		);
		
	u16 wIndex = 0;
	if ( bError )
	{//释放
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if ( NULL == ptPutAud->m_aptLocalAddr[wIndex] )
			{
				continue;
			}
			
			m_pcConf->GetPutAudAddrList()->FreeBuff(ptPutAud->m_aptLocalAddr[wIndex]);
			ptPutAud->m_aptLocalAddr[wIndex] = NULL;
		}
		tVidAck.m_wReason = TP_RET_ERROR;
		UmsSendConfCtrl(tOutHandle, evtp_OpenVidChan_Ack, &tVidAck, sizeof(tVidAck));
		return ;
	}

	ptPutAud->m_bUsed = TRUE;
	ptPutAud->m_wEpID = ptNode->m_wEpID;
	ptPutAud->m_wUsedNum ++;
	ptPutAud->m_wCheck = ptVidCmd->m_atUpRtp[0].m_tAddr.m_wPort;
	ptPutAud->m_emUser = emUser;

	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == ptPutAud->m_aptLocalAddr[wIndex] )
		{
			continue;
		}
		tVidAck.m_atAudRtp[wIndex] = ptPutAud->m_aptLocalAddr[wIndex]->m_tRtpAddr;
		ptPutAud->m_atRmtAddr[wIndex].m_tBackRtcpAddr = ptVidCmd->m_atAudBackRtcp[wIndex];
	}

	if ( ptNode != ptNodeFather )
	{
		TVidChanCmd tVidCmd;
		tVidCmd.m_tEpKey.m_wEpID = ptNode->m_wLowChildEpID;
		tVidCmd.m_atUpRtp[0].m_tAddr.m_wPort = ptPutAud->m_wIndx;
		tVidCmd.m_atUpRtp[1].m_tAddr.m_wPort = ptPutAud->m_emUser;
		
		ForEachChanList(ptNode->m_wAudRcvNum,
			tVidCmd.m_atAudBackRtcp[ewIndex] = ptPutAud->m_aptLocalAddr[ewIndex]->m_tBackRtcpAddr;\
			);
		
		TUmsHandle tOutHandle;
		m_pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNodeFather->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_OpenVidChan_Cmd, &tVidCmd, sizeof(tVidCmd));
	}
	else
	{//本级

		UmsSendConfCtrl(tOutHandle, evtp_OpenVidChan_Ack, &tVidAck, sizeof(tVidAck));
	}

	//创建 ptPutAud->m_aptLocalAddr->m_tBackRtcpAddr  到 ptPutAud->m_atRmtAddr[wIndex].m_tBackRtcpAddr
	CNetPortMgr::CreatPutAudBackRtpToUp(m_pcConf, ptPutAud);
	
	return;
}

void CPutAud::OnAudChnlRsp( CTpMsg *const ptMsg )
{
	TUmsHandle tInHandle = *(TUmsHandle*)(ptMsg->GetBody());
	TVidChanAck tInVidAck = *(TVidChanAck*)(ptMsg->GetBody() + sizeof(TUmsHandle));
	
	TUmsHandle tOutHandle;
	m_pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
	
	TCapNode* ptForeNode = Inst()->GetNodeMgr()->GetCapsetNode(tInHandle.GetEpID());
	if ( NULL == ptForeNode )
	{
		MdlError(Ums_Mdl_Call, ("CPutAud::OnAudChnlRsp ptSrcCapNode is NULL . ConfID:%d, handleEpID:%d\n", Inst()->GetInsID(), tInHandle.GetEpID()));
		return ;
	}
	
	//不是本级结点，则取得该会场的本级EpID
	if ( ptForeNode->IsUms() )
	{
		TCallNode* ptNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tInVidAck.m_tEpKey.m_wEpID);
		if ( NULL == ptNode || !ptNode->m_bUsed )
		{
			MdlError(Ums_Mdl_Call, ("CPutAud::OnAudChnlRsp ptNode is NULL . ConfID:%d, EpID:%d\n", Inst()->GetInsID(), tInVidAck.m_tEpKey.m_wEpID));
			return ;
		}
		tInVidAck.m_tEpKey.m_wEpID = ptNode->m_wEpID;
	}
	
	MdlHint(Ums_Mdl_Call, ("CPutAud::OnAudChnlRsp. ConfID:%d, wEpID:%d, Reason:%d\n", m_pcConf->GetInsID(), tInVidAck.m_tEpKey.m_wEpID, tInVidAck.m_wReason));
	
	if( tInVidAck.m_wReason == TP_RET_OK )
	{		
		MdlHint(Ums_Mdl_Call, ("	AudRtp0:"ADDRPORT_FORMAT", AudRtp1:"ADDRPORT_FORMAT", AudRtp2:"ADDRPORT_FORMAT"\n",
			ADDRNET(tInVidAck.m_atAudRtp[0]), ADDRNET(tInVidAck.m_atAudRtp[1]), ADDRNET(tInVidAck.m_atAudRtp[2])));
	}

	TVidChanAck tVidAck;
	TPutAudChnl* ptPutAud = NULL;
	do 
	{
		ptPutAud = FindByEpID(tInVidAck.m_tEpKey.m_wEpID, tInVidAck.m_atUpBackRtcp[1].m_tAddr.m_wPort);
		if ( NULL == ptPutAud )
		{
			tVidAck.m_wReason = TP_RET_ERROR;
			MdlError(Ums_Mdl_Call, ("CPutAud::OnAudChnlRsp. ptPutAud is NULL! EpID:%d, ConfID:%d\n", tInVidAck.m_tEpKey.m_wEpID, m_pcConf->GetInsID()));
			return ;
		}
		
		if ( ptPutAud->m_wCheck != tInVidAck.m_atUpBackRtcp[0].m_tAddr.m_wPort )
		{//该次回应超时
			tVidAck.m_wReason = TP_RET_ERROR;
			MdlError(Ums_Mdl_Call, ("CPutAud::OnAudChnlRsp. Ack Invalid! EpID:%d, ConfID:%d, wIndex:%d, AckIndex:%d\n", 
				tInVidAck.m_tEpKey.m_wEpID, m_pcConf->GetInsID(), ptPutAud->m_wIndx, tInVidAck.m_atUpBackRtcp[0].m_tAddr.m_wPort));
			break ;
		}

		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if ( NULL == ptPutAud->m_aptLocalAddr[wIndex] )
			{
				continue;
			}
			ptPutAud->m_atRmtAddr[wIndex].m_tRtpAddr = tInVidAck.m_atAudRtp[wIndex];
		}
	} while (0);

	if ( m_pcConf->IsChairConf() )
	{
		if ( tVidAck.m_wReason == TP_RET_ERROR )
		{
			ReleaseAudChnl(tInVidAck.m_tEpKey.m_wEpID, ptPutAud->m_emUser);
			return ;
		}
	}
	else
	{
		tVidAck.m_tEpKey.m_wEpID = tVidAck.m_tEpKey.m_wEpID;
		tVidAck.m_atUpBackRtcp[0].m_tAddr.m_wPort = ptPutAud->m_wCheck;
		tVidAck.m_atUpBackRtcp[1].m_tAddr.m_wPort = ptPutAud->m_emUser;

		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if ( NULL == ptPutAud->m_aptLocalAddr[wIndex] )
			{
				continue;
			}
			tVidAck.m_atAudRtp[wIndex] = ptPutAud->m_aptLocalAddr[wIndex]->m_tRtpAddr;
		}
		UmsSendConfCtrl(tOutHandle, evtp_OpenVidChan_Ack, &tVidAck, sizeof(tVidAck));
	}

	//创建 ptPutAud->m_aptLocalAddr->m_tRtpAddr 到 ptPutAud->m_atRmtAddr->m_tRtpAddr
	CNetPortMgr::CreatPutAudRtpToDown(m_pcConf, ptPutAud);
	

	return ;
}

BOOL32 CPutAud::AssignAudChnl(u16 wEpID, EmPutAudUser emUser, TTPMediaTransAddr atAddr[])
{
	TCallNode* ptNode = m_pcConf->GetNodeMgr()->GetNode(wEpID);
	TCapNode* ptNodeFather = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptNode);	
	
	MdlHint(Ums_Mdl_Call, ("CPutAud::AssignAudChnl. ConfId:%d, EpId:%d  user:%d(1:dis, 2:rollcall, 3:audmix).", 
			m_pcConf->GetInsID(), wEpID, emUser));

	if (NULL == ptNode || NULL == ptNodeFather || !ptNode->IsChanOn())
	{
		return FALSE;
	}

	if ( ptNode == ptNodeFather )
	{//本级不申请
		return FALSE;
	}
	else
	{

		TPutAudChnl* ptPutAud = FindByEpID(wEpID, emUser);
		if ( NULL != ptPutAud )
		{
			MdlError(Ums_Mdl_Call, ("CPutAud::AssignAudChnl. EpId already exists. ConfId:%d, EpId:%d.", 
				m_pcConf->GetInsID(), wEpID));
			return FALSE;

// 			ptPutAud->m_wUsedNum ++;
// 			ForEachChanList(ptNode->m_wAudRcvNum,
// 				atAddr[ewIndex].m_tRtpAddr = ptPutAud->m_aptLocalAddr[ewIndex]->m_tRtpAddr;\
// 				atAddr[ewIndex].m_tBackRtcpAddr = ptPutAud->m_aptLocalAddr[ewIndex]->m_tBackRtcpAddr;\
// 			);
// 			return TRUE;
		}
		
		ptPutAud = FindIdle();
		if ( NULL == ptPutAud )
		{
			return FALSE;
		}

		BOOL32 bError = FALSE;
		ForEachChanList(ptNode->m_wAudRcvNum,
			ptPutAud->m_aptLocalAddr[ewIndex] = m_pcConf->GetPutAudAddrList()->AllocNode();\
			if ( NULL == ptPutAud->m_aptLocalAddr[ewIndex] )\
			{\
				bError = TRUE;\
				break;\
			}\
			ptPutAud->m_aptLocalAddr[ewIndex]->SetIP(m_pcConf->GetConfEqpDs().m_dwEqpIp);\
			);

		if ( bError )
		{//释放
			for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			{
				if ( NULL == ptPutAud->m_aptLocalAddr[wIndex] )
				{
					continue;
				}

				m_pcConf->GetPutAudAddrList()->FreeBuff(ptPutAud->m_aptLocalAddr[wIndex]);
				ptPutAud->m_aptLocalAddr[wIndex] = NULL;
			}
			return FALSE;
		}

		ptPutAud->m_bUsed = TRUE;
		ptPutAud->m_wEpID = wEpID;
		ptPutAud->m_wUsedNum ++;
		ptPutAud->m_emUser = emUser;

		static u16 wCheck = 0;
		ptPutAud->m_wCheck = wCheck ++;

		TVidChanCmd tVidCmd;
		tVidCmd.m_tEpKey.m_wEpID = ptNode->m_wLowChildEpID;
		tVidCmd.m_atUpRtp[0].m_tAddr.m_wPort = ptPutAud->m_wCheck;
		tVidCmd.m_atUpRtp[1].m_tAddr.m_wPort = ptPutAud->m_emUser;

		ForEachChanList(ptNode->m_wAudRcvNum,
			atAddr[ewIndex].m_tRtpAddr = ptPutAud->m_aptLocalAddr[ewIndex]->m_tRtpAddr;\
			atAddr[ewIndex].m_tBackRtcpAddr = ptPutAud->m_aptLocalAddr[ewIndex]->m_tBackRtcpAddr;\
			tVidCmd.m_atAudBackRtcp[ewIndex] = ptPutAud->m_aptLocalAddr[ewIndex]->m_tBackRtcpAddr;\
			);

		TUmsHandle tOutHandle;
		m_pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNodeFather->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_OpenVidChan_Cmd, &tVidCmd, sizeof(tVidCmd));
	}

	return TRUE;
}

void CPutAud::ReleaseAudChnl( u16 wEpID , EmPutAudUser emUser)
{
	TPutAudChnl* ptPutAud = FindByEpID(wEpID, emUser);
	if ( NULL == ptPutAud )
	{
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CPutAud::ReleaseAudChnl. ConfID:%d, wEpID:%d, usedNum:%d\n", m_pcConf->GetInsID(), wEpID, ptPutAud->m_wUsedNum));

	if ( --ptPutAud->m_wUsedNum != 0 )
	{
		return ;
	}

	CNetPortMgr::FreeMediaTrans(m_pcConf, ptPutAud->m_tDs);

	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( NULL == ptPutAud->m_aptLocalAddr[wIndex] )
		{
			continue;
		}
		
		m_pcConf->GetPutAudAddrList()->FreeBuff(ptPutAud->m_aptLocalAddr[wIndex]);
	}

	ptPutAud->Clear();
	
	TCallNode* ptNode = m_pcConf->GetNodeMgr()->GetNode(wEpID);
	TCapNode* ptNodeFather = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptNode);		
	if (NULL == ptNode || NULL == ptNodeFather || !ptNode->IsChanOn())
	{
		return ;
	}

	if ( ptNode != ptNodeFather )
	{
		TUmsHandle tOutHandle;
		m_pcConf->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNodeFather->m_wEpID);
		u8 byBuf[sizeof(u16)+sizeof(u32)] = {0};
		u32	dwType = emUser;
		memcpy(byBuf, &ptNode->m_wLowChildEpID, sizeof(u16));
		memcpy(byBuf+sizeof(u16), &dwType, sizeof(u32));
		UmsSendConfCtrl(tOutHandle, evtp_CloseVidChan_Cmd, &byBuf, sizeof(byBuf));
	}

	return ;
}

void CPutAud::OnAudChnlClose( CTpMsg *const ptMsg )
{
	u16 wEpID;
	u32	dwType;
	TP_SAFE_CAST( wEpID, ptMsg->GetBody() + sizeof(TUmsHandle));
	TP_SAFE_CAST( dwType, ptMsg->GetBody() + sizeof(TUmsHandle) + sizeof(u16));

	MdlHint(Ums_Mdl_Call, ("CPutAud::OnAudChnlClose. ConfID:%d, wEpID:%d, dwType:%d.\n", m_pcConf->GetInsID(), wEpID, dwType));

	ReleaseAudChnl(wEpID, (EmPutAudUser)dwType);

	return ;
}

TPutAudChnl* CPutAud::FindIdle()
{
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( m_atChanle[wIndex].m_bUsed )
		{
			continue;
		}

		return &m_atChanle[wIndex];
	}
	return NULL;
}

TPutAudChnl* CPutAud::FindByEpID( u16 wEpID, EmPutAudUser emUser)
{
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( m_atChanle[wIndex].m_wEpID != wEpID || m_atChanle[wIndex].m_emUser != emUser)
		{
			continue;
		}
		
		return &m_atChanle[wIndex];
	}
	return NULL;
}

void CPutAud::ReleaseAll(EmPutAudUser emUser)
{
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		TPutAudChnl* ptPutAud = &m_atChanle[wIndex];
		if ( !ptPutAud->m_bUsed )
		{
			continue;
		}

		if (em_putauduser_none != emUser && ptPutAud->m_emUser != emUser)
		{
			continue;
		}

		CNetPortMgr::FreeMediaTrans(m_pcConf, ptPutAud->m_tDs);

		for (u16 wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
		{
			if (NULL != ptPutAud->m_aptLocalAddr[wLoop])
			{
				m_pcConf->GetPutAudAddrList()->FreeBuff(ptPutAud->m_aptLocalAddr[wLoop]);
			}
		}

		ptPutAud->Clear();	
	}
	return;
}

void CPutAud::GetAudLocalAddr( u16 wEpId, EmPutAudUser emUser, TTPMediaTransAddr atAddr[] )
{
	TPutAudChnl* ptAudChnl = FindByEpID(wEpId, emUser);
	if (NULL == ptAudChnl)
	{
		return;
	}

	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEpId);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{// 
		return;
	}

	ForEachChanList(ptNode->m_wAudRcvNum,
		atAddr[ewIndex].m_tRtpAddr = ptAudChnl->m_aptLocalAddr[ewIndex]->m_tRtpAddr;\
		atAddr[ewIndex].m_tBackRtcpAddr = ptAudChnl->m_aptLocalAddr[ewIndex]->m_tBackRtcpAddr;\
		)

	return;
}

void CPutAud::ReleaseRepeatdPutAudForDown(u16 wConfid, u16 wEpID, EmPutAudUser emUser)
{
	for ( u16 wIndex = 0; wIndex < MAX_AUDMIX_MDL_NUM; wIndex ++ )
	{
		if ( m_atChanle[wIndex].m_bUsed && 
			 wEpID == m_atChanle[wIndex].m_wEpID &&
			 emUser == m_atChanle[wIndex].m_emUser)
		{
			MdlHint(Ums_Mdl_Call, ("CPutAud::ReleaseRepeatdPutAudForDown. ConfID:%d, wEpID:%d, user:%d(1:dis,2:rollcall, 3:audmix).\n", 
				   wConfid, wEpID, emUser));
			ReleaseAudChnl(wEpID, emUser);
			break;
		}
		
	}

	return ;
}