#include "callinnerstruct.h"
#include "tplog.h"

void TRefrenUiNodeList::Add(EmTpOprType emOpr, u16 wEpID)
{
	//保护
	if (m_wNum >= TP_REFRESH_LIST_THREE)
	{
		m_bRefreshImm = TRUE;
		return;
	}
	
	//检测重复更新
	for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
	{
		if (m_atNode[wIndex].m_wEpID == wEpID)
		{
			if (tp_OprType_Del == emOpr)
			{
				if (tp_OprType_Add == m_atNode[wIndex].m_emOpr)
				{
					if (wIndex == m_wNum - 1)
					{
						
					}
					else
					{
						memcpy(&m_atNode[wIndex], &m_atNode[wIndex+1], sizeof(TUmsUpdateNode) * (m_wNum - wIndex - 1));
					}
					--m_wNum;
				}
				else if (tp_OprType_Update == m_atNode[wIndex].m_emOpr)
				{
					m_atNode[wIndex].m_emOpr = tp_OprType_Del;
					m_bRefreshImm = TRUE;
				}
			}
			return;
		}
	}
	
	m_atNode[m_wNum].m_emOpr = emOpr;
	m_atNode[m_wNum].m_wEpID = wEpID;
	++m_wNum;
	
	if (m_wNum == TP_REFRESH_LIST_THREE || tp_OprType_Del == emOpr)
	{
		m_bRefreshImm = TRUE;
	}
}


/////////////
TCallNode::TCallNode()
:CNodeBase(em_Node_Ep)
,m_bUsed(FALSE)
,m_wParentEpID(TP_INVALID_INDEX)
,m_wChildEpID(TP_INVALID_INDEX)
,m_wBrotherEpID(TP_INVALID_INDEX)
,m_wLowChildEpID(TP_INVALID_INDEX)
,m_emEpType(emTPEndpointTypeCNS)
,m_wMixIndex(TP_INVALID_INDEX)
,m_emLevel(emTPSipProvince)
,m_bAllowFecc(FALSE)
,m_bNeedReCallBy323(FALSE)
,m_wCallBy323Num(0)
{	
	HungUp();
	m_emCallReason = EmCnsCallReason_Local;
	m_emCallState = ums_UmsConfNodeState_unused;
	m_bCallByCMC = FALSE;
	m_bInPoll = FALSE;
	m_tDualVidSndFormat.m_tFormat.m_emRes = emTPVResEnd;
	m_tDualAudSndFormat.m_tFormat.m_emFormat = emTPAEnd;
	m_tDualVidRcvFormat.m_tFormat.m_emRes = emTPVResEnd;
	m_tDualAudRcvFormat.m_tFormat.m_emFormat = emTPAEnd;
	m_byCurVidNo = 0; // 默认源
	m_tVidSourceInfo.Clear();
}

void TCallNode::Clear()
{
	m_bUsed = FALSE;
	m_byVer = 0;
	m_byNeedCallType = 0;
	m_wParentEpID = TP_INVALID_INDEX;
	m_wChildEpID = TP_INVALID_INDEX;
	m_wBrotherEpID = TP_INVALID_INDEX;
				
	m_wLowChildEpID = TP_INVALID_INDEX;
	
	m_emEpType = emTPEndpointTypeCNS;
	m_tCalledAddr.Clear();
	
	m_wMixIndex = TP_INVALID_INDEX;
	m_emLevel = emTPSipProvince;
	m_bAllowFecc = FALSE;
	m_bNeedReCallBy323 = FALSE;
	m_wCallBy323Num = 0;
	m_tVidSourceInfo.Clear();
	m_byCurVidNo = 0;
	
	HungUp();
	m_emCallReason = EmCnsCallReason_Local;
	m_emCallState = ums_UmsConfNodeState_unused;
	m_bCallByCMC = FALSE;

	m_bInPoll = FALSE;
}

void TCallNode::HungUp()
{
	m_bMute = FALSE;
	m_bQuiet = FALSE;
	
	memset(m_abyPrdutID, 0, sizeof(m_abyPrdutID));

	m_emCallState = ums_UmsConfNodeState_stopcall;
	m_emLevel = emTPSipProvince;
	m_enRcvAlignType = emTPRcvAlignTypeMidAlign;
	m_emCallReason = EmCnsCallReason_hungup;
	m_emCallProtocol = emTpSIP;
	m_emVendorID = EmTp_vendor_KEDA;
	m_bCheckDualRcv = TRUE;
	m_bAllowFecc = FALSE;
	m_byCurVidNo	= 0;
	m_tVidSourceInfo.Clear();
	ChannelDisConnect();
	//m_bNeedReCallBy323 = FALSE;

	m_tDualVidSndFormat.m_tFormat.m_emRes = emTPVResEnd;
	m_tDualAudSndFormat.m_tFormat.m_emFormat = emTPAEnd;
	m_tDualVidRcvFormat.m_tFormat.m_emRes = emTPVResEnd;
	m_tDualAudRcvFormat.m_tFormat.m_emFormat = emTPAEnd;
}	

void TCallNode::ChannelDisConnect()
{
	m_bChannelOpen = FALSE;
	m_bSmallOpenDec = FALSE;
	m_bSmallOpenEnc = FALSE;
	
	m_wSpearkIndex = TP_INVALID_INDEX;
	m_wDualIndex = TP_INVALID_INDEX;
	
	m_wVidSndNum = 0;
	m_wVidRcvNum = 0;	
	m_wAudSndNum = 0;	
	m_wAudRcvNum = 0;

	m_tVidRcvFormat.m_tFormat.Clear();
	m_tVidSndFormat.m_tFormat.Clear();

	ClearSelNum();
}
void TCallNode::GetCnsInfo(TCnsInfo& tInfo)
{
	tInfo.m_wEpID = m_wEpID;
	tInfo.m_wParentEpID = m_wParentEpID;
	tInfo.m_wChildEpID = m_wChildEpID;
	tInfo.m_wBrotherEpID = m_wBrotherEpID;
	
	tInfo.m_emEpType = m_emEpType;
	tInfo.m_bOnline = IsChanOn();

	tInfo.m_tCalledAddr = m_tCalledAddr.GetValidAlias();  //???
	tInfo.m_wLevel = m_emLevel;
	
	tInfo.m_bMute = m_bMute;
	tInfo.m_bQuiet = m_bQuiet;
	tInfo.m_emCallReason = m_emCallReason;
	tInfo.m_wSpeakerNum = m_wVidSndNum > m_wAudSndNum? m_wVidSndNum : m_wAudSndNum;

	strncpy(tInfo.m_achRoomName, m_tConfName.m_abyAlias, TP_MAX_ALIAS_LEN);

	strncpy(tInfo.m_achRoomE164, m_tCalledAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);
	tInfo.m_dwRoomIp = m_tCalledAddr.m_dwIP;
}

void TCallNode::SetNodeCallInfo(TConfNodeCallUpdateTr& tInfo)
{
	m_wLowChildEpID = tInfo.m_wEpID;
	
	m_emEpType = tInfo.m_emEpType;
	m_emVendorID = tInfo.m_emVendorID;
	m_emCallState = tInfo.m_emCallState;
	m_emCallReason = tInfo.m_emCallReason;
	m_tCalledAddr  = tInfo.m_tCalledAddr ;
	m_tConfName = tInfo.m_tConfName;
	
	m_emLevel = tInfo.m_emLevel;
	m_enRcvAlignType = tInfo.m_enRcvAlignType;
	
	m_bMute = tInfo.m_bMute;
	m_bQuiet = tInfo.m_bQuiet;
	m_wSpearkIndex = tInfo.m_wSpearkIndex;
	m_wDualIndex = tInfo.m_wDualIndex;
}

void TCallNode::SetNodeChanInfo(TConfNodeChanUpdateTr& tInfo)
{
	m_bChannelOpen = tInfo.bChanOpen;
	m_bSmallOpenDec = tInfo.bSmallOpenDec;
	m_bSmallOpenEnc = tInfo.bSmallOpenEnc;

	m_bInPoll = tInfo.bInPoll;

	SetVidRcvNum(tInfo.wVidRcv);
	SetVidSndNum(tInfo.wVidSnd);
	SetAudRcvNum(tInfo.wAudRcv);
	SetAudSndNum(tInfo.wAudSnd);

	m_tVidRcvFormat.m_tFormat = tInfo.tVidRcv;
	m_tVidSndFormat.m_tFormat = tInfo.tVidSnd;
	m_tDualVidRcvFormat.m_tFormat = tInfo.tDualVidRcv;
	m_tDualVidSndFormat.m_tFormat = tInfo.tDualVidSnd;

	m_tAudRcvFormat.m_tFormat = tInfo.tAudRcv;
	m_tAudSndFormat.m_tFormat = tInfo.tAudSnd;
	m_tDualAudRcvFormat.m_tFormat = tInfo.tDualAudRcv;
	m_tDualAudSndFormat.m_tFormat = tInfo.tDualAudSnd;

	m_tVidRcvFormat.m_wStaticPayload = tInfo.awPd[0];
	m_tVidRcvFormat.m_wDynamicPayload = tInfo.awPd[1];

	m_tVidSndFormat.m_wStaticPayload = tInfo.awPd[2];
	m_tVidSndFormat.m_wDynamicPayload = tInfo.awPd[3];

	m_tDualVidRcvFormat.m_wStaticPayload = tInfo.awPd[4];
	m_tDualVidRcvFormat.m_wDynamicPayload = tInfo.awPd[5];

	m_tDualVidSndFormat.m_wStaticPayload = tInfo.awPd[6];
	m_tDualVidSndFormat.m_wDynamicPayload = tInfo.awPd[7];

	m_tAudRcvFormat.m_wStaticPayload = tInfo.awPd[8];
	m_tAudRcvFormat.m_wDynamicPayload = tInfo.awPd[9];

	m_tAudSndFormat.m_wStaticPayload = tInfo.awPd[10];
	m_tAudSndFormat.m_wDynamicPayload = tInfo.awPd[11];

	m_tDualAudRcvFormat.m_wStaticPayload = tInfo.awPd[12];
	m_tDualAudRcvFormat.m_wDynamicPayload = tInfo.awPd[13];

	m_tDualAudSndFormat.m_wStaticPayload = tInfo.awPd[14];
	m_tDualAudSndFormat.m_wDynamicPayload = tInfo.awPd[15];
}

// MCU 只有一路码流 依据单屏策略
void TCallNode::SetMcuNodeCallInfo( TUmcMcuPart& tInfo )
{
	m_wLowChildEpID = GETINS(tInfo.m_dwPID);

	m_emEpType		= emTPEndpointH323MT;
	m_emVendorID	= EmTp_vendor_KEDA;
	m_emCallReason	= EmCnsCallReason_success;
	m_tCalledAddr.m_tAlias.SetAlias(tp_Alias_h323, tInfo.m_aszEpName);
	m_tCalledAddr.m_dwIP = tInfo.m_dwIP;
	m_tConfName.SetAlias(tp_Alias_h323, tInfo.m_aszEpName);
	if (1 == tInfo.m_byState)
	{
		m_emCallState = ums_UmsConfNodeState_online;
	}
	else if (2 == tInfo.m_byState)
	{
		m_emCallState = ums_UmsConfNodeState_stopcall;
	}
	else if (3 == tInfo.m_byState)
	{
		m_emCallState = ums_UmsConfNodeState_calling;
	}
	else
	{
		m_emCallState = ums_UmsConfNodeState_unused;
	}

	m_bMute			= tInfo.m_bMute;
	m_bQuiet		= tInfo.m_bQuiet;
	m_wSpearkIndex	= 1;

	
}

void TCallNode::SetMcuNodeChanInfo( TCallNode* ptParent, TUmcMcuPart& tInfo )
{
	m_bSmallOpenEnc = FALSE; 
	m_bSmallOpenDec = FALSE;  
	
	m_bInPoll = FALSE;
	
	// MCU 只有一路码流 在线通道数为1 不在线为0
	u16 wVidAutNum = 0;
	if (ums_UmsConfNodeState_online == m_emCallState)
	{
		m_bChannelOpen	= TRUE;
		wVidAutNum = 1;
	}
	
	SetVidRcvNum(wVidAutNum);
	SetVidSndNum(wVidAutNum);
	SetAudRcvNum(wVidAutNum);
	SetAudSndNum(wVidAutNum);
	
	
	if (NULL == ptParent)
	{
		return;
	}
	
	// mcu Node的通道格式与父节点一致
	m_tVidRcvFormat.m_tFormat = ptParent->m_tVidRcvFormat.m_tFormat;
	m_tVidSndFormat.m_tFormat = ptParent->m_tVidSndFormat.m_tFormat;
	m_tDualVidRcvFormat.m_tFormat = ptParent->m_tDualVidRcvFormat.m_tFormat;
	m_tDualVidSndFormat.m_tFormat = ptParent->m_tDualVidSndFormat.m_tFormat;
	
	m_tAudRcvFormat.m_tFormat = ptParent->m_tAudRcvFormat.m_tFormat;
	m_tAudSndFormat.m_tFormat = ptParent->m_tAudSndFormat.m_tFormat;
	m_tDualAudRcvFormat.m_tFormat = ptParent->m_tDualAudRcvFormat.m_tFormat;
	m_tDualAudSndFormat.m_tFormat = ptParent->m_tDualAudSndFormat.m_tFormat;
	
	m_tVidRcvFormat.m_wStaticPayload = ptParent->m_tVidRcvFormat.m_wStaticPayload;
	m_tVidRcvFormat.m_wDynamicPayload = ptParent->m_tVidRcvFormat.m_wDynamicPayload;
	
	m_tVidSndFormat.m_wStaticPayload = ptParent->m_tVidSndFormat.m_wStaticPayload;
	m_tVidSndFormat.m_wDynamicPayload = ptParent->m_tVidSndFormat.m_wDynamicPayload;
	
	m_tDualVidRcvFormat.m_wStaticPayload = ptParent->m_tDualVidRcvFormat.m_wStaticPayload;
	m_tDualVidRcvFormat.m_wDynamicPayload = ptParent->m_tDualVidRcvFormat.m_wDynamicPayload;
	
	m_tDualVidSndFormat.m_wStaticPayload = ptParent->m_tDualVidSndFormat.m_wStaticPayload;
	m_tDualVidSndFormat.m_wDynamicPayload = ptParent->m_tDualVidSndFormat.m_wDynamicPayload;
	
	m_tAudRcvFormat.m_wStaticPayload = ptParent->m_tAudRcvFormat.m_wStaticPayload;
	m_tAudRcvFormat.m_wDynamicPayload = ptParent->m_tAudRcvFormat.m_wDynamicPayload;
	
	m_tAudSndFormat.m_wStaticPayload = ptParent->m_tAudSndFormat.m_wStaticPayload;
	m_tAudSndFormat.m_wDynamicPayload = ptParent->m_tAudSndFormat.m_wDynamicPayload;
	
	m_tDualAudRcvFormat.m_wStaticPayload = ptParent->m_tDualAudRcvFormat.m_wStaticPayload;
	m_tDualAudRcvFormat.m_wDynamicPayload = ptParent->m_tDualAudRcvFormat.m_wDynamicPayload;
	
	m_tDualAudSndFormat.m_wStaticPayload = ptParent->m_tDualAudSndFormat.m_wStaticPayload;
	m_tDualAudSndFormat.m_wDynamicPayload = ptParent->m_tDualAudSndFormat.m_wDynamicPayload;
}

void TCallNode::GetNodeCallInfo(TConfNodeCallUpdateTr& tInfo)
{
	tInfo.m_wEpID = m_wEpID;
	tInfo.m_emEpType = m_emEpType;
	tInfo.m_emVendorID = m_emVendorID;
	tInfo.m_emCallState = m_emCallState;
	tInfo.m_emCallReason = m_emCallReason;
	
	tInfo.m_tCalledAddr = m_tCalledAddr;
	tInfo.m_tConfName = m_tConfName;
	
	tInfo.m_emLevel = m_emLevel;
	tInfo.m_enRcvAlignType = m_enRcvAlignType;
	
	tInfo.m_bMute = m_bMute;
	tInfo.m_bQuiet = m_bQuiet;
	tInfo.m_wSpearkIndex = m_wSpearkIndex;
	tInfo.m_wDualIndex = m_wDualIndex;
}

void TCallNode::GetNodeChanInfo(TConfNodeChanUpdateTr& tInfo)
{
	tInfo.wEpID = m_wEpID;
	tInfo.bChanOpen = m_bChannelOpen;
	tInfo.bSmallOpenEnc = m_bSmallOpenEnc;
	tInfo.bSmallOpenDec = m_bSmallOpenDec;
	
	tInfo.SetVidRcvNum(m_wVidRcvNum);
	tInfo.SetVidSndNum(m_wVidSndNum);
	tInfo.SetAudRcvNum(m_wAudRcvNum);
	tInfo.SetAudSndNum(m_wAudSndNum);

	tInfo.tVidRcv = m_tVidRcvFormat.m_tFormat;
	tInfo.awPd[0] = m_tVidRcvFormat.m_wStaticPayload;
	tInfo.awPd[1] = m_tVidRcvFormat.m_wDynamicPayload;

	tInfo.tVidSnd = m_tVidSndFormat.m_tFormat;
	tInfo.awPd[2] = m_tVidSndFormat.m_wStaticPayload;
	tInfo.awPd[3] = m_tVidSndFormat.m_wDynamicPayload;
	
	tInfo.tDualVidRcv = m_tDualVidRcvFormat.m_tFormat;
	tInfo.awPd[4] = m_tDualVidRcvFormat.m_wStaticPayload;
	tInfo.awPd[5] = m_tDualVidRcvFormat.m_wDynamicPayload;

	tInfo.tDualVidSnd = m_tDualVidSndFormat.m_tFormat;
	tInfo.awPd[6] = m_tDualVidSndFormat.m_wStaticPayload;
	tInfo.awPd[7] = m_tDualVidSndFormat.m_wDynamicPayload;

	tInfo.tAudRcv = m_tAudRcvFormat.m_tFormat;
	tInfo.awPd[8] = m_tAudRcvFormat.m_wStaticPayload;
	tInfo.awPd[9] = m_tAudRcvFormat.m_wDynamicPayload;

	tInfo.tAudSnd = m_tAudSndFormat.m_tFormat;
	tInfo.awPd[10] = m_tAudSndFormat.m_wStaticPayload;
	tInfo.awPd[11] = m_tAudSndFormat.m_wDynamicPayload;

	tInfo.tDualAudRcv = m_tDualAudRcvFormat.m_tFormat;
	tInfo.awPd[12] = m_tDualAudRcvFormat.m_wStaticPayload;
	tInfo.awPd[13] = m_tDualAudRcvFormat.m_wDynamicPayload;

	tInfo.tDualAudSnd = m_tDualAudSndFormat.m_tFormat;
	tInfo.awPd[14] = m_tDualAudSndFormat.m_wStaticPayload;
	tInfo.awPd[15] = m_tDualAudSndFormat.m_wDynamicPayload;
}

void TCallNode::SetVidFeccInfo( TVidFeccInfo& tInfo )
{
	m_bAllowFecc = tInfo.m_bAllowFecc;
	m_byCurVidNo = tInfo.m_byVidno;
	m_tVidSourceInfo = tInfo.m_tVidSourceInfo;
}

void TCallNode::GetVidFeccInfo( TVidFeccInfo& tInfo )
{
	tInfo.m_wEpID	   = m_wEpID;
	tInfo.m_bAllowFecc = m_bAllowFecc;
	tInfo.m_byVidno	   = m_byCurVidNo;
	tInfo.m_tVidSourceInfo = m_tVidSourceInfo;
}

////////////////////////////
void CDsListInfo::Insert(CDsListPtr ptInsertNode)
{
	m_dwListNum++;
	if (NULL == m_pHead)
	{
		m_pHead = ptInsertNode;
		ptInsertNode->m_ptNext = NULL;
		return;
	}
	
	if (m_pHead->m_tData > ptInsertNode->m_tData)
	{
		ptInsertNode->m_ptNext = m_pHead;
		m_pHead = ptInsertNode;
		return;
	}

	CDsListPtr ptNode = m_pHead;
	while(NULL != ptNode->m_ptNext)
	{
		if (ptNode->m_ptNext->m_tData > ptInsertNode->m_tData)
		{
			break;
		}
		ptNode = ptNode->m_ptNext;
	}

	ptInsertNode->m_ptNext = ptNode->m_ptNext;
	ptNode->m_ptNext = ptInsertNode;
}

CDsListInfo& CDsListInfo::operator = (CDsListInfo& tRsData)
{
	m_pHead = tRsData.m_pHead;
	m_dwListNum = tRsData.m_dwListNum;
	return *this;
}

void CDsListInfo::Clear()
{
	m_pHead = NULL;
	m_dwListNum = 0;
}


void CDsListInfo::Merger(CDsListInfo& tNewList, CDsListInfo& tDelList, CDsListInfo& tRepeatList, TUmsDsData tNeedAddList[], u16& wAddNum)
{
	tDelList.Clear();
	tRepeatList.Clear();
	wAddNum = 0;;

	CDsListPtr ptNewHead = tNewList.GetHead();
	CDsListPtr ptOldHead = GetHead();
	if (NULL == ptNewHead)
	{
		tDelList = *this;
		Clear();
		return;
	}
	
	
	if (NULL == ptOldHead)
	{
		while(ptNewHead != NULL)
		{
			tNeedAddList[wAddNum++] = ptNewHead->m_tData;
			ptNewHead = ptNewHead->m_ptNext;
		}
		*this = tNewList;
		return;
	}

	CDsListPtr ptDelTmp = NULL;	//待删除节点
	CDsListPtr ptNewTmp = NULL;

	CDsListPtr ptReservePre = NULL;	//保留链表
	while (ptNewHead != NULL && ptOldHead != NULL)
	{
		if (ptOldHead->m_tData < ptNewHead->m_tData)
		{
			ptDelTmp = ptOldHead;
			ptOldHead = ptOldHead->m_ptNext;
			tDelList.Insert(ptDelTmp);
		}
		else if (ptOldHead->m_tData > ptNewHead->m_tData)
		{
			tNeedAddList[wAddNum++] = ptNewHead->m_tData;
			ptNewTmp = ptNewHead->m_ptNext;

			if (NULL == ptReservePre)
			{
				m_pHead = ptNewHead;
			}
			else
			{
				ptReservePre->m_ptNext = ptNewHead;
			}
			//ptNewHead->m_ptNext = ptOldHead;
			ptReservePre = ptNewHead;

			ptNewHead = ptNewTmp;
		}
		else
		{			
			//将老链表的节点保留
			if (NULL == ptReservePre)
			{
				m_pHead = ptOldHead;
			}
			else
			{
				ptReservePre->m_ptNext = ptOldHead;
			}
			ptReservePre = ptOldHead;

			//删除新链表的节点
			ptDelTmp = ptNewHead;

			//老链表递增
			ptOldHead = ptOldHead->m_ptNext;

			//新链表递增
			ptNewHead = ptNewHead->m_ptNext;

			//删除重复节点
			tRepeatList.Insert(ptDelTmp);
		}
	}
	
	while(ptOldHead != NULL)
	{
		ptDelTmp = ptOldHead;
		ptOldHead = ptOldHead->m_ptNext;
		tDelList.Insert(ptDelTmp);
	}


	while(ptNewHead != NULL)
	{
		tNeedAddList[wAddNum++] = ptNewHead->m_tData;
		//将老链表的节点保留
		if (NULL == ptReservePre)
		{
			m_pHead = ptNewHead;
		}
		else
		{
			ptReservePre->m_ptNext = ptNewHead;
		}
		ptReservePre = ptNewHead;

		ptNewHead = ptNewHead->m_ptNext;//++
	}

	if (ptReservePre != NULL)
	{
		ptReservePre->m_ptNext = NULL;
	}
}


void CDsListInfo::GetMediaTrans(TUmsDsData tDelDsData[MAX_CHANNEL_DS_NUM], u16& wDsNum)
{
	wDsNum = 0;

	CDsListPtr ptHead = GetHead();
	while (NULL != ptHead)
	{
		if (wDsNum < MAX_CHANNEL_DS_NUM)
		{
			tDelDsData[wDsNum++] = ptHead->m_tData;
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("GetMediaTrans set list failed. dsNum:%d\n", GetElementNum()));
			return;
		}
		ptHead = ptHead->m_ptNext;
	}
}
void CDsListInfo::SetMediaTrans(TUmsDsData tAddDsData[MAX_CHANNEL_DS_NUM], u16 wDsNum, CDsList* pNodeMgr)
{
	CDsListPtr ptItor;
	for (u16 wIndex = 0; wIndex < wDsNum; ++wIndex)
	{
		ptItor = pNodeMgr->WriteBuffItor(tAddDsData[wIndex]);
		if (ptItor != NULL)
		{
			Insert(ptItor);
		}			
	}
}




void TFastUpdateStatis::Add()
{
	for (u32 wIndex = TP_KEYFRAME_STATIS-1; wIndex > 0 ; --wIndex)
	{
		m_dwStatis[wIndex] = m_dwStatis[wIndex-1];
	}
	
	time_t t_time;
	time(&t_time);
	m_dwStatis[0] = t_time;
}

BOOL32 TFastUpdateStatis::CheckValidInterval(u32 dwInterval, u32 dwTimes) const
{
	time_t t_time;
	time(&t_time);
	u32 dwNow = t_time;

	if ( dwNow <= m_dwStatis[0] )
	{//1s内的请求也认为重复
		return FALSE;
	}
	
	u32 dwReqTimes = 0;
	for (u32 wIndex = 0; wIndex < TP_KEYFRAME_STATIS; ++wIndex)
	{
		if (dwNow - m_dwStatis[wIndex] < dwInterval)
		{
			dwReqTimes++;
		}
	}
	if (dwReqTimes < dwTimes)
	{
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//帧率分辨率调整管理
BOOL32 CResFrmMgr::AdjustRes( EmTpVideoResolution emRes )
{
	if ( emRes == emTPVResEnd )
	{
		return FALSE;
	}

	u16 wIndex = 0 ;
	for ( wIndex = 0 ; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{//当前是否存在
		if ( m_atRes[wIndex].m_emRes == emRes )
		{//已经有了，就不要调整了
			m_atRes[wIndex].m_wNum ++;
			return FALSE;
		}
	}

	for ( wIndex = 0 ; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{//找出空闲位置 存储
		if ( m_atRes[wIndex].m_emRes != emTPVResEnd )
		{
			continue;
		}
		
		m_atRes[wIndex].m_emRes = emRes;
		m_atRes[wIndex].m_wNum ++;

		break;
	}

	if ( wIndex == NODE_RES_FRM_NUM )
	{
		return FALSE;
	}

	//查找出最小的分辨率和帧率
	u16 wSmallFmt = FindSmallRes();

	if ( wSmallFmt == m_wCurResIndx )
	{
		return FALSE;
	}

	m_wCurResIndx = wSmallFmt;

	return TRUE;
}

BOOL32 CResFrmMgr::ResetRes( EmTpVideoResolution emRes )
{
	if ( emRes == emTPVResEnd )
	{
		return FALSE;
	}
	
	u16 wIndex = 0 ;
	for ( wIndex = 0 ; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{//查找
		if ( m_atRes[wIndex].m_emRes == emTPVResEnd )
		{
			continue;
		}
		
		if ( m_atRes[wIndex].m_emRes == emRes)
		{//找到 则删除
			break ;
		}
	}

	if ( wIndex == NODE_RES_FRM_NUM )
	{//无
		return FALSE;
	}

	if ( --m_atRes[wIndex].m_wNum == 0 )
	{
		m_atRes[wIndex].m_emRes = emTPVResEnd;

		if ( wIndex == m_wCurResIndx )
		{
			m_wCurResIndx = FindSmallRes();		
		}

		return TRUE;
	}

	return FALSE;
}

EmTpVideoResolution CResFrmMgr::GetCurRes()
{
	if( TP_VALID_HANDLE(m_wCurResIndx) )
	{
		return m_atRes[m_wCurResIndx].m_emRes;
	}
	else
	{
		return m_ptNode->m_tVidSndFormat.m_tFormat.m_emRes;
	}
}

u16 CResFrmMgr::FindSmallRes()
{//找到当前最合适的
	EmTpVideoResolution emRet = emTPVHD1080p1920x1080;
	u16 wSmallIndx = 0;
	for ( u16 wIndex = 0; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{
		if ( m_atRes[wIndex].m_emRes == emTPVResEnd )
		{
			continue;
		}
		if(CTpTypeAdpt::ResolutionMaxOpr(emRet, m_atRes[wIndex].m_emRes))
		{
			emRet = m_atRes[wIndex].m_emRes;
			wSmallIndx = wIndex;
		}
	}
	return wSmallIndx;
}

BOOL32 CResFrmMgr::AdjustFrm( u16 wFrm )
{
	if ( wFrm < 5 || wFrm > 60 )
	{
		return FALSE;
	}

	u16 wIndex = 0 ;
	for ( wIndex = 0 ; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{//有相同的则不处理
		if ( m_atFrm[wIndex].m_wFrm == wFrm )
		{//已经有了，就不要调整了
			m_atFrm[wIndex].m_wNum ++;
			return FALSE;
		}
	}

	for ( wIndex = 0 ; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{//找出空闲位置 存储
		if ( m_atFrm[wIndex].m_wFrm != 0 )
		{
			continue;
		}
		
		m_atFrm[wIndex].m_wFrm = wFrm;
		m_atFrm[wIndex].m_wNum ++;

		break;
	}

	if ( wIndex == NODE_RES_FRM_NUM )
	{
		return FALSE;
	}

	//查找出最小的分辨率和帧率
	u16 wSmallFmt = FindSmallFrm();

	if ( wSmallFmt == m_wCurFrmIndx )
	{
		return FALSE;
	}

	m_wCurFrmIndx = wSmallFmt;

	return TRUE;
}

BOOL32 CResFrmMgr::ResetFrm( u16 wFrm )
{
	if ( wFrm < 5 || wFrm > 60 )
	{
		return FALSE;
	}
	
	u16 wIndex = 0 ;
	for ( wIndex = 0 ; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{//查找
		if ( m_atFrm[wIndex].m_wFrm == 0 )
		{
			continue;
		}
		
		if ( m_atFrm[wIndex].m_wFrm == wFrm)
		{//找到 则删除
			break ;
		}
	}

	if ( wIndex == NODE_RES_FRM_NUM )
	{//无
		return FALSE;
	}

	if ( --m_atFrm[wIndex].m_wNum == 0 )
	{
		m_atFrm[wIndex].m_wFrm = 0;

		if ( wIndex == m_wCurFrmIndx )
		{
			m_wCurFrmIndx = FindSmallFrm();		
		}

		return TRUE;
	}

	return FALSE;
}

u16 CResFrmMgr::GetCurFrm()
{
	if( TP_VALID_HANDLE(m_wCurFrmIndx) )
	{
		return m_atFrm[m_wCurFrmIndx].m_wFrm;
	}
	else
	{
		return m_ptNode->m_tVidSndFormat.m_tFormat.m_wFrameRate;
	}
}

u16 CResFrmMgr::FindSmallFrm()
{//找到当前最合适的
	u16 wFrm = 60;
	u16 wSmallIndx = 0;
	for ( u16 wIndex = 0; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{
		if( wFrm > m_atFrm[wIndex].m_wFrm )
		{
			wFrm = m_atFrm[wIndex].m_wFrm;
			wSmallIndx = wIndex;
		}
	}
	return wSmallIndx;
}

void CResFrmMgr::Clear()
{
	for ( u16 wIndex = 0; wIndex < NODE_RES_FRM_NUM; wIndex ++)
	{
		m_atRes[wIndex].Clear();
		m_atFrm[wIndex].Clear();
	}

	m_wCurResIndx = TP_INVALID_INDEX;
	m_wCurFrmIndx = TP_INVALID_INDEX;
}

void CResFrmMgr::PrintInfo()
{
	msgprintnotime("  curResIndx:%d, curFrmIndx:%d \n", m_wCurResIndx, m_wCurFrmIndx);

	msgprintnotime("  default-> res:%s frm:%d\n"
		, UmsVidResPrint(m_ptNode->m_tVidSndFormat.m_tFormat.m_emRes), m_ptNode->m_tVidSndFormat.m_tFormat.m_wFrameRate);

	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < NODE_RES_FRM_NUM; wIndex ++ )
	{
		msgprintnotime("   (%d). res:%s num:%d\n", wIndex
			, UmsVidResPrint(m_atRes[wIndex].m_emRes), m_atRes[wIndex].m_wNum);
	}

	msgprintnotime("\n");

	for ( wIndex = 0; wIndex < NODE_RES_FRM_NUM; wIndex ++ )
	{
		msgprintnotime("   (%d). frm:%d num:%d\n", wIndex
			, m_atFrm[wIndex].m_wFrm, m_atFrm[wIndex].m_wNum);
	}

	msgprintnotime("\n");

	return ;
}

void CResFrmMgr::SetDefault()
{
	m_wCurResIndx = 0;
	m_atRes[0].m_emRes = m_ptNode->m_tVidSndFormat.m_tFormat.m_emRes;
	m_atRes[0].m_wNum ++;

	m_wCurFrmIndx = 0;
	m_atFrm[0].m_wFrm = m_ptNode->m_tVidSndFormat.m_tFormat.m_wFrameRate;
	m_atFrm[0].m_wNum ++;
}
