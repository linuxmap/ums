#include "callnodemgr.h"
#include "umsconfinst.h"
#include "umsstackinterface.h"
#include "eqpinterface.h"
#include "eventoutsipadapter.h"
#include "umsconfigex.h"

CCallNodeMgr::CCallNodeMgr(CUmsConfInst* pcInst)
:CTpHandler(pcInst)
,m_ptCurCallNode(NULL)
,m_ptHeadNode(NULL)
{
	for(u16 wIndex = 0; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
	{
		m_aptCallNode[wIndex] = NULL;
	}
}


CCallNodeMgr::~CCallNodeMgr()
{
	for(u16 wIndex = 0; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
	{
		if (NULL != m_aptCallNode[wIndex])
		{
			delete m_aptCallNode[wIndex];
			m_aptCallNode[wIndex] = NULL;
		}		
	}
}

BOOL32 CCallNodeMgr::Create()
{
	u16 wIndex;
	for(wIndex = 0; wIndex < MAX_CAPSET_NODE_NUM; ++wIndex)
	{
		m_aptCallNode[wIndex] = new TCapNode;
		if (NULL == m_aptCallNode[wIndex])
		{
			return FALSE;
		}
		m_aptCallNode[wIndex]->m_wEpID = wIndex;
	}
	for(wIndex = MAX_CAPSET_NODE_NUM; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
	{
		m_aptCallNode[wIndex] = new TCallNode;
		if (NULL == m_aptCallNode[wIndex])
		{
			return FALSE;
		}
		m_aptCallNode[wIndex]->m_wEpID = wIndex;
	}
	
	m_mapEpIp.clear();

	return TRUE;
}


void CCallNodeMgr::StopConf()
{
	while( NULL != m_ptHeadNode)
	{
		DeleteNode(m_ptHeadNode);
	}

	m_mapEpIp.clear();

	m_ptCurCallNode = NULL;
	m_ptHeadNode = NULL;
}

BOOL32 CCallNodeMgr::AssignDsRes(BOOL32 bIsNode, TEqpRes* ptRes, u32_ip dwNodeIp)
{
	CUmsConfInst* pInst = Inst();
	ptRes->Clear();

	TMediaParam tEqpMedia;
	memcpy(tEqpMedia.m_atEqp, pInst->m_atDsEqp, sizeof(pInst->m_atDsEqp[0]) * UMS_CONF_MAX_DS_NUM);

	tEqpMedia.m_ptEqpRes = ptRes;
	tEqpMedia.m_emAssignType = bIsNode == TRUE ? TMediaParam::emAssignNode : TMediaParam::emAssignConf;
	tEqpMedia.m_dwNodeIp = dwNodeIp;

	if (!AssignEqpByNodeEx(&tEqpMedia))
	{
		return FALSE;
	}	

	u16 wIdleIndex = TP_INVALID_INDEX;
	for (u16 wIndex = 0; wIndex < UMS_CONF_MAX_DS_NUM; ++wIndex)
	{
		if (!pInst->m_atDsEqp[wIndex].IsValid())
		{
			wIdleIndex = wIndex;
		}
		if (ptRes->m_dwEqpNode == pInst->m_atDsEqp[wIndex].m_dwEqpNode)
		{
			return TRUE;
		}
	}

	if (wIdleIndex < UMS_CONF_MAX_DS_NUM)
	{
		pInst->m_atDsEqp[wIdleIndex] =  *ptRes;
	}

	return TRUE;
}
void CCallNodeMgr::GetValidCallType(TTpCallAddr& tCallAddr)
{
	TTPCallTypePri tTPCallTypePri;
	tTPCallTypePri.emTPIPLevel    = (EmTpCallLevel)CUmsConfigEx::GetInstance()->GetIpCallLvl();
	tTPCallTypePri.emTPE164Level  = (EmTpCallLevel)CUmsConfigEx::GetInstance()->GetE164CallLvl();
	tTPCallTypePri.emTPAliasLevel = (EmTpCallLevel)CUmsConfigEx::GetInstance()->GetAliasCallLvl();  
	if (tCallAddr.m_bAliasIP)
	{
		tCallAddr.m_byCallType = tp_Alias_Unknow;
	}
	else
	{
		if (emTPCallLevelFirst == tTPCallTypePri.emTPIPLevel)
		{
			if (tCallAddr.m_dwIP)
			{
				tCallAddr.m_byCallType = tp_Alias_IP;
			}
			else if (emTPCallLevelSecond == tTPCallTypePri.emTPE164Level)
			{
				if (!tCallAddr.m_tE164.IsInValid())
				{
					tCallAddr.m_byCallType = tp_Alias_e164;
				}
				else
				{
					tCallAddr.m_byCallType = tp_Alias_h323;
				}
			}
			else
			{
				if (!tCallAddr.m_tAlias.IsInValid())
				{
					tCallAddr.m_byCallType = tp_Alias_h323;
				}
				else
				{
					tCallAddr.m_byCallType = tp_Alias_e164;
				}
			}
		}
		
		if (emTPCallLevelFirst == tTPCallTypePri.emTPE164Level)
		{
			if (!tCallAddr.m_tE164.IsInValid())
			{
				tCallAddr.m_byCallType = tp_Alias_e164;
			}
			else if (emTPCallLevelSecond == tTPCallTypePri.emTPIPLevel)
			{
				if (tCallAddr.m_dwIP)
				{
					tCallAddr.m_byCallType = tp_Alias_IP;
				}
				else 
				{
					tCallAddr.m_byCallType = tp_Alias_h323;
				}
			}
			else
			{
				if (!tCallAddr.m_tAlias.IsInValid())
				{
					tCallAddr.m_byCallType = tp_Alias_h323;
				}
				else
				{
					tCallAddr.m_byCallType = tp_Alias_IP;
				}
			}
		}
		if (emTPCallLevelFirst == tTPCallTypePri.emTPAliasLevel)
		{
			if (!tCallAddr.m_tAlias.IsInValid())
			{
				tCallAddr.m_byCallType = tp_Alias_h323;
			}
			else if (emTPCallLevelSecond == tTPCallTypePri.emTPIPLevel)
			{
				if (tCallAddr.m_dwIP)
				{
					tCallAddr.m_byCallType = tp_Alias_IP;
				}
				else 
				{
					tCallAddr.m_byCallType = tp_Alias_e164;
				}
			}
			else
			{
				if (!tCallAddr.m_tE164.IsInValid())
				{
					tCallAddr.m_byCallType = tp_Alias_e164;
				}
				else 
				{
					tCallAddr.m_byCallType = tp_Alias_IP;
				}
			}
		}
	}
}
void CCallNodeMgr::InitCallNode(TEpAddrList& tList,TTemplateConfEx& tTempEx)
{
	//根据会议模板分配的ID填充会场列表
	TCapNode* ptCurNode = NULL;
	u16 wEpID;
	BOOL32 bExist = FALSE;

	TEqpRes tAdapter;
	TAdaptEqpParam tAdapterEqp;
	tAdapterEqp.m_ptEqpRes = &tAdapter;

	TEqpRes	tMediaEqp;

	BOOL32 bRet;


	for (u16 wIndex = 0; wIndex < tList.m_wNum; ++wIndex)
	{
		bExist = FALSE;
		wEpID = tList.m_tCnsList[wIndex].m_wEpID + 1;	//会议模板ID从0编号，会议ID从1编号

		if (!VALID_LOCAL_EPID(wEpID))	//会议的最大会场数量
		{
			MdlError(Ums_Mdl_Call, ("InitCallNode id invalid. wConfID:%d, wEpID:%d, Name:%s\n"
				, Inst()->GetInsID(), wEpID, tList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias));
			continue;
		}	

		if(tList.m_tCnsList[wIndex].m_tEpAddr.m_bAliasIP)
		{
			for (TCapNode* ptTmp = FirstNode(); ptTmp != NULL;  ptTmp = NextLoalNode(ptTmp))
			{
				if (ptTmp->m_wEpID == wEpID && ptTmp->m_tCalledAddr.m_dwIP == tList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP 
					&& (ptTmp->m_tCalledAddr.m_tAlias == tList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias || ptTmp->m_tCalledAddr.m_tE164 == tList.m_tCnsList[wIndex].m_tEpAddr.m_tE164))
				{
					bExist = TRUE;
					break;
				}
			}
		}
		else
		{	
			GetValidCallType(tList.m_tCnsList[wIndex].m_tEpAddr);  
			for (TCapNode* ptTmp = FirstNode(); ptTmp != NULL;  ptTmp = NextLoalNode(ptTmp))
			{
				switch (tList.m_tCnsList[wIndex].m_tEpAddr.m_byCallType)
				{
				case tp_Alias_IP: 	 
					if (ptTmp->m_wEpID == wEpID || ptTmp->m_tCalledAddr.m_dwIP == tList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP)
					{
						bExist = TRUE;
						break;
					}		
					break;
				case tp_Alias_e164:
					if (ptTmp->m_wEpID == wEpID || ptTmp->m_tCalledAddr.m_tE164 == tList.m_tCnsList[wIndex].m_tEpAddr.m_tE164)
					{
						bExist = TRUE;
						break;
					}	
					break;
				case tp_Alias_h323:
					if (ptTmp->m_wEpID == wEpID || ptTmp->m_tCalledAddr.m_tAlias == tList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias)
					{
						bExist = TRUE;
						break;
					}	
					break;
				default:
					{
						MdlError(Ums_Mdl_Call, ("InitCallNode CallType unknow. wConfID:%d, wEpID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n"
							, Inst()->GetInsID(), wEpID, tList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias,
							tList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias,Tpu32ToIP(tList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP)));
						break;
					}
				}					
			}
		}
	
		if (bExist)
		{
			MdlError(Ums_Mdl_Call, ("InitCallNode repeat. wConfID:%d, wEpID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n"
				, Inst()->GetInsID(), wEpID, tList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias,
				tList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias,Tpu32ToIP(tList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP)));
			continue;
		}
		
		bRet = AssignEqpEx(&tAdapterEqp);
		if (!bRet)
		{//接入分配失败
			MdlError(Ums_Mdl_Call, ("InitCallNode  No idle adapter resource. wConfID:%d, wEpID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n"
				, Inst()->GetInsID(), wEpID, tList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias,
				tList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias,Tpu32ToIP(tList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP)));
		}

		//首元素
		if (NULL == ptCurNode)
		{
			m_ptHeadNode = (TCapNode*)m_aptCallNode[wEpID];
			m_ptCurCallNode = (TCapNode*)m_ptHeadNode;
		}
		else
		{
			ptCurNode->m_wBrotherEpID = wEpID;
		}

		ptCurNode = (TCapNode*)m_aptCallNode[wEpID];
		ptCurNode->m_bUsed = TRUE;
		ptCurNode->m_tCalledAddr = tList.m_tCnsList[wIndex].m_tEpAddr;
		ptCurNode->m_tConfName = tList.m_tCnsList[wIndex].m_tEpAddr.GetValidAlias();


	
		ptCurNode->m_emCallState = ums_UmsConfNodeState_uncall;
		if (TP_INVALID_INDEX != tTempEx.m_wTempID && tList.m_tCnsList[wIndex].m_wEpID == tTempEx.m_awEpID[wIndex])
		{
			ptCurNode->m_emCallProtocol = tTempEx.m_aemCallProtocol[wIndex];
		}

		bRet = AssignNodeRes(ptCurNode, &tAdapter);
		if (!bRet)
		{	
			MdlError(Ums_Mdl_Call, ("InitCallNode  No idle Media resource. wConfID:%d, wEpID:%d, Name:%s\n"
				, Inst()->GetInsID(), wEpID, tList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias));
		}
	}
}

TCapNode* CCallNodeMgr::FirstNeedCallNode()
{
	if (NULL != m_ptCurCallNode)
	{
		return m_ptCurCallNode;
	}
	return FirstNode();
}

void CCallNodeMgr::SetLastCallNode(TCapNode* ptNode)
{
	m_ptCurCallNode = ptNode;
}

TCapNode* CCallNodeMgr::FirstNode()
{
	if (NULL != m_ptHeadNode)
	{
		return (TCapNode*)m_ptHeadNode;
	}
	return NULL;
}	

TCapNode* CCallNodeMgr::NextLoalNode(TCallNode* ptNode)
{
	if(NULL == ptNode)
	{
		return NULL;
	}

	if (VALID_LOCAL_EPID(ptNode->m_wBrotherEpID))
	{
		return (TCapNode*)m_aptCallNode[ptNode->m_wBrotherEpID];
	}
	return NULL;
}


TCapNode* CCallNodeMgr::GetLocalNode(u16 wEpID)
{
	if (VALID_LOCAL_EPID(wEpID))
	{
		return (TCapNode*)m_aptCallNode[wEpID];
	}
	return NULL;
}

TCapNode* CCallNodeMgr::GetLocalNode(TTpCallAddr& tCallAddr)
{
	if (tCallAddr.m_tE164.IsInValid() && tCallAddr.m_tAlias.IsInValid() && 0 == tCallAddr.m_dwIP)
	{
		return NULL;
	}

	for (TCapNode* ptTmp = FirstNode(); ptTmp != NULL;  ptTmp = NextLoalNode(ptTmp) )
	{	
		if (tCallAddr.m_bAliasIP)
		{
			if (ptTmp->m_tCalledAddr.m_dwIP == tCallAddr.m_dwIP && 
				(ptTmp->m_tCalledAddr.m_tAlias == tCallAddr.m_tAlias || ptTmp->m_tCalledAddr.m_tE164 == tCallAddr.m_tE164))
			{
				return ptTmp;			
			}
		}
		else
		{
			if (!tCallAddr.m_tAlias.IsInValid())
			{
				if (ptTmp->m_tCalledAddr.m_tAlias == tCallAddr.m_tAlias)
				{
					return ptTmp;
				}
			}
			if (!tCallAddr.m_tE164.IsInValid())
			{
				if (ptTmp->m_tCalledAddr.m_tE164 == tCallAddr.m_tE164)
				{
					return ptTmp;
				}
			}
			if (0 != tCallAddr.m_dwIP)
			{
				if(ptTmp->m_tCalledAddr.m_dwIP == tCallAddr.m_dwIP)
				{
					return ptTmp;
				}
			}
		}
	}
	return NULL;
}

TCapNode* CCallNodeMgr::GetCapsetNode(u16 wEpID)
{
	if (VALID_CAPSET_EPID(wEpID))
	{
		return (TCapNode*)m_aptCallNode[wEpID];
	}
	return NULL;
}


TVidChanPara* CCallNodeMgr::GetChanByHandle(u16 wEpID, EmUmsCodecType enChanType, HandleChannle chanHandle)
{
	if (!VALID_CAPSET_EPID(wEpID))
	{
		return NULL;
	}

	TCapNode* ptCapNode = (TCapNode*)m_aptCallNode[wEpID];
	switch (enChanType)
	{
	case ums_CodecType_vid_dec:
		{
			for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(ptCapNode->m_tRmtChan.m_atVidDec[wIndex].m_tPAHandle) 
					&& ptCapNode->m_tRmtChan.m_atVidDec[wIndex].m_tPAHandle == chanHandle)
				{
					return &ptCapNode->m_tRmtChan.m_atVidDec[wIndex];
				}
			}
		}
		break;
	case ums_CodecType_vid_enc:
		{
			for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(ptCapNode->m_tRmtChan.m_atVidEnc[wIndex].m_tPAHandle) 
					&& ptCapNode->m_tRmtChan.m_atVidEnc[wIndex].m_tPAHandle == chanHandle)
				{
					return &ptCapNode->m_tRmtChan.m_atVidEnc[wIndex];
				}
			}
		}
		break;
	case ums_CodecType_vid_dec_dual:
		{
			if (TP_VALID_HANDLE(ptCapNode->m_tRmtChan.m_tDualVidDec.m_tPAHandle) 
					&& ptCapNode->m_tRmtChan.m_tDualVidDec.m_tPAHandle == chanHandle)
			{
				return &ptCapNode->m_tRmtChan.m_tDualVidDec;
			}
		}
		break;
	}
	return NULL;
}

TChanPara* CCallNodeMgr::GetChanByIndex(u16 wEpID, EmUmsCodecType enChanType, u16 wIndex)
{
	if (!VALID_CAPSET_EPID(wEpID))
	{
		return NULL;
	}

	TCapNode* ptCapNode = (TCapNode*)m_aptCallNode[wEpID];
	switch (enChanType)
	{
	case ums_CodecType_vid_enc:
		{
			if (wIndex < TP_MAX_STREAMNUM)
			{
				return &ptCapNode->m_tRmtChan.m_atVidEnc[wIndex];
			}
		}
		break;
	case ums_CodecType_vid_dec:
		{
			if (wIndex < TP_MAX_STREAMNUM)
			{
				return &ptCapNode->m_tRmtChan.m_atVidDec[wIndex];
			}
		}
		break;
	case ums_CodecType_aud_enc:
		{
			if (wIndex < TP_MAX_STREAMNUM)
			{
				return &ptCapNode->m_tRmtChan.m_atAudEnc[wIndex];
			}
		}
		break;
	case ums_CodecType_aud_dec:
		{
			if (wIndex < TP_MAX_STREAMNUM)
			{
				return &ptCapNode->m_tRmtChan.m_atAudDec[wIndex];
			}
		}
		break;
	case ums_CodecType_Mix_enc:
		{
			return &ptCapNode->m_tRmtChan.m_tAudMixEnc;
		}
		break;
	case ums_CodecType_Mix_dec:
		{
			return &ptCapNode->m_tRmtChan.m_tAudMixDec;
		}
		break;
	case ums_CodecType_vid_enc_dual:
		{
			if (TP_VALID_HANDLE(ptCapNode->m_tRmtChan.m_tDualVidEnc.m_tPAHandle))
			{
				return &ptCapNode->m_tRmtChan.m_tDualVidEnc;
			}
		}
		break;
	}
	return NULL;
}

TVidChanPara* CCallNodeMgr::GetVidChanByIndex(u16 wEpID, EmUmsCodecType enChanType, u16 wIndex)
{
	if (!VALID_CAPSET_EPID(wEpID))
	{
		return NULL;
	}
	
	TCapNode* ptCapNode = (TCapNode*)m_aptCallNode[wEpID];
	switch (enChanType)
	{
	case ums_CodecType_vid_enc:
		{
			if (wIndex < TP_MAX_STREAMNUM)
			{
				return &ptCapNode->m_tRmtChan.m_atVidEnc[wIndex];
			}
		}
		break;
	case ums_CodecType_vid_dec:
		{
			if (wIndex < TP_MAX_STREAMNUM)
			{
				return &ptCapNode->m_tRmtChan.m_atVidDec[wIndex];
			}
		}
		break;
	case ums_CodecType_vid_enc_dual:
		{
			if (TP_VALID_HANDLE(ptCapNode->m_tRmtChan.m_tDualVidEnc.m_tPAHandle))
			{
				return &ptCapNode->m_tRmtChan.m_tDualVidEnc;
			}
		}
		break;
	}
	return NULL;
}

//视频支持多格式，必须进行二次协商才能赋值；
//音频则第一次协商就可以了
void CCallNodeMgr::SetNodeCapSet(TCapNode* ptNode, const TUmsNodeCapset& tNodeCap)
{
	TRmtChan* ptAddr = &ptNode->m_tRmtChan;
	u16 wIndex = 0;

	if (tNodeCap.m_wVidEncNum > 0 && !tNodeCap.m_tVidSndCap.IsMulCap())
	{
		if (tNodeCap.m_tVidSndCap.IsValidCap())
		{
			ptNode->SetVidSndNum(tNodeCap.m_wVidEncNum);
		}

		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			ptAddr->m_atVidEnc[wIndex].SetPara(tNodeCap.m_atVidEnc[wIndex]);
			ptAddr->m_atSmallVidEnc[wIndex].SetPara(tNodeCap.m_atSmallVidEnc[wIndex]);
		}

		ptNode->m_bSmallOpenEnc = ptAddr->m_atSmallVidEnc[MIDSCREENINDEX].IsOpen();

		const TUmsVidFormat* ptCap = NULL;
		if (tNodeCap.m_tVidSndCap.m_tHp.IsValid())
		{
			ptCap = &tNodeCap.m_tVidSndCap.m_tHp;
		}
		if (tNodeCap.m_tVidSndCap.m_tBp.IsValid())
		{
			ptCap = &tNodeCap.m_tVidSndCap.m_tBp;
		}

		if (NULL != ptCap)
		{
			ptNode->m_tVidSndFormat.m_tFormat = *ptCap;
			ptNode->m_tVidSndFormat.m_wDynamicPayload = tNodeCap.m_tVidSndCap.m_wDynamicPayload;
			ptNode->m_tVidSndFormat.m_wStaticPayload = CTpTypeAdpt::GetVidPayloadValue(ptNode->m_tVidSndFormat.m_tFormat.m_emFormat);
		}
		else
		{
			ptNode->m_tVidSndFormat.m_tFormat.m_emRes = emTPVResEnd;
		}

		ForEachChanList( ptNode->m_wVidSndNum,
			ptNode->m_atResFrm[ewIndex].SetDefault();\
			);

	}
	if (tNodeCap.m_wVidDecNum > 0 && !tNodeCap.m_tVidRcvCap.IsMulCap())
	{
		if (tNodeCap.m_tVidRcvCap.IsValidCap())
		{
			ptNode->SetVidRcvNum(tNodeCap.m_wVidDecNum);
		}

		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			ptAddr->m_atVidDec[wIndex].SetPara(tNodeCap.m_atVidDec[wIndex]);
			ptAddr->m_atSmallVidDec[wIndex].SetPara(tNodeCap.m_atSmallVidDec[wIndex]);
		}

		ptNode->m_bSmallOpenDec = ptAddr->m_atSmallVidDec[MIDSCREENINDEX].IsOpen();

		const TUmsVidFormat* ptCap = NULL;
		if (tNodeCap.m_tVidRcvCap.m_tHp.IsValid())
		{
			ptCap = &tNodeCap.m_tVidRcvCap.m_tHp;
		}
		if (tNodeCap.m_tVidRcvCap.m_tBp.IsValid())
		{
			ptCap = &tNodeCap.m_tVidRcvCap.m_tBp;
		}
		
		if (NULL != ptCap)
		{
			ptNode->m_tVidRcvFormat.m_tFormat = *ptCap;

			ptNode->m_tVidRcvFormat.m_wDynamicPayload = tNodeCap.m_tVidRcvCap.m_wDynamicPayload;
			ptNode->m_tVidRcvFormat.m_wStaticPayload = CTpTypeAdpt::GetVidPayloadValue(ptNode->m_tVidRcvFormat.m_tFormat.m_emFormat);
		}
		else
		{
			ptNode->m_tVidRcvFormat.m_tFormat.m_emRes = emTPVResEnd;
		}
	}
	
	if (tNodeCap.m_wAudEncNum > 0)
	{
		ptNode->SetAudSndNum(tNodeCap.m_wAudEncNum);
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			ptAddr->m_atAudEnc[wIndex].SetPara(tNodeCap.m_atAudEnc[wIndex]);
		}

		ptNode->m_tAudSndFormat.m_tFormat.m_emFormat = tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_emFormat;
		ptNode->m_tAudRcvFormat.m_tFormat.m_emChnlCfg = tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_emChnlCfg;
		ptNode->m_tAudRcvFormat.m_tFormat.m_emSampleFreq = tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_emSampleFreq;

		ptNode->m_tAudSndFormat.m_wDynamicPayload = tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_byReserve1;
		ptNode->m_tAudSndFormat.m_wStaticPayload = CTpTypeAdpt::GetAudPayloadValue(tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_emFormat); 
	}

	if (tNodeCap.m_wAudDecNum > 0)
	{
		ptNode->SetAudRcvNum(tNodeCap.m_wAudDecNum);
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			ptAddr->m_atAudDec[wIndex].SetPara(tNodeCap.m_atAudDec[wIndex]);
		}
		ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat = tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_emFormat;
		ptNode->m_tAudRcvFormat.m_tFormat.m_emChnlCfg = tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_emChnlCfg;
		ptNode->m_tAudRcvFormat.m_tFormat.m_emSampleFreq = tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_emSampleFreq;

		ptNode->m_tAudRcvFormat.m_wDynamicPayload = tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_byReserve1;
		ptNode->m_tAudRcvFormat.m_wStaticPayload = CTpTypeAdpt::GetAudPayloadValue(tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_emFormat);
	}

	if (tNodeCap.m_tAudMixEnc.m_bIsChanOn)
	{
		ptAddr->m_tAudMixEnc.SetPara(tNodeCap.m_tAudMixEnc);
	}

	if (tNodeCap.m_tAudMixDec.m_bIsChanOn)
	{
		ptAddr->m_tAudMixDec.SetPara(tNodeCap.m_tAudMixDec);
	}
}
//add
void CCallNodeMgr::SetDualNodeCapset(TCapNode* ptNode, const TUmsNodeCapset& tNodeCap)
{
	TRmtChan* ptAddr = &ptNode->m_tRmtChan;
	//视频发送
	if (tNodeCap.m_wVidEncNum == 0)
	{
		ptNode->m_tDualVidSndFormat.m_tFormat.m_emRes = emTPVResEnd;
	}
	else
	{
		if (!tNodeCap.m_tVidSndCap.IsMulCap())
		{
			ptAddr->m_tDualVidEnc.SetPara(tNodeCap.m_atVidEnc[0]);
			
			if (tNodeCap.m_tVidSndCap.m_tHp.IsValid())
			{
				memcpy(&ptNode->m_tDualVidSndFormat.m_tFormat, &tNodeCap.m_tVidSndCap.m_tHp, sizeof(TUmsVidFormat));
			}
			if (tNodeCap.m_tVidSndCap.m_tBp.IsValid())
			{
				memcpy(&ptNode->m_tDualVidSndFormat.m_tFormat, &tNodeCap.m_tVidSndCap.m_tBp, sizeof(TUmsVidFormat));
			}
			ptNode->m_tDualVidSndFormat.m_wDynamicPayload = tNodeCap.m_tVidSndCap.m_wDynamicPayload;
			ptNode->m_tDualVidSndFormat.m_wStaticPayload = CTpTypeAdpt::GetVidPayloadValue(ptNode->m_tVidSndFormat.m_tFormat.m_emFormat);	
			
			MdlHint(Ums_Mdl_Call, ("SetDualNodeCapset wConfID:%d, wEpID:%d, DualVidSnd  dualsload:%d  dualdload:%d\n"
				, Inst()->GetInsID(), ptNode->m_wEpID, ptNode->m_tDualVidSndFormat.m_wStaticPayload, ptNode->m_tDualVidSndFormat.m_wDynamicPayload));

		}
	}
	//视频接收
	if (tNodeCap.m_wVidDecNum == 0)
	{
		ptNode->m_tDualVidRcvFormat.m_tFormat.m_emRes = emTPVResEnd;
	}
	else
	{
		if (!tNodeCap.m_tVidRcvCap.IsMulCap())
		{
			ptAddr->m_tDualVidDec.SetPara(tNodeCap.m_atVidDec[0]);
			
			if (tNodeCap.m_tVidRcvCap.m_tHp.IsValid())
			{
				memcpy(&ptNode->m_tDualVidRcvFormat.m_tFormat, &tNodeCap.m_tVidRcvCap.m_tHp, sizeof(TUmsVidFormat));
			}
			if (tNodeCap.m_tVidRcvCap.m_tBp.IsValid())
			{
				memcpy(&ptNode->m_tDualVidRcvFormat.m_tFormat, &tNodeCap.m_tVidRcvCap.m_tBp, sizeof(TUmsVidFormat));
			}
			ptNode->m_tDualVidRcvFormat.m_wDynamicPayload = tNodeCap.m_tVidRcvCap.m_wDynamicPayload;
			ptNode->m_tDualVidRcvFormat.m_wStaticPayload = CTpTypeAdpt::GetVidPayloadValue(ptNode->m_tVidRcvFormat.m_tFormat.m_emFormat);
			
			MdlHint(Ums_Mdl_Call, ("SetDualNodeCapset wConfID:%d, wEpID:%d, DualVidRcv  dualsload:%d  dualdload:%d\n"
				, Inst()->GetInsID(), ptNode->m_wEpID, ptNode->m_tDualVidRcvFormat.m_wStaticPayload, ptNode->m_tDualVidRcvFormat.m_wDynamicPayload));
		}
	}
	//音频发送
	if (tNodeCap.m_wAudEncNum > 0)
	{
		ptAddr->m_tDualAudEnc.SetPara(tNodeCap.m_atAudEnc[0]);
		
		ptNode->m_tDualAudSndFormat.m_tFormat.m_emFormat = tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_emFormat;
		ptNode->m_tDualAudSndFormat.m_wDynamicPayload = tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_byReserve1;
		ptNode->m_tDualAudSndFormat.m_wStaticPayload = CTpTypeAdpt::GetAudPayloadValue(tNodeCap.m_tAudSndCap.m_atAudFmt[0].m_emFormat);
	}
	//音频接收
	if (tNodeCap.m_wAudDecNum > 0)
	{
		ptAddr->m_tDualAudDec.SetPara(tNodeCap.m_atAudDec[0]);

		ptNode->m_tDualAudRcvFormat.m_tFormat.m_emFormat = tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_emFormat;
		ptNode->m_tDualAudRcvFormat.m_wDynamicPayload = tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_byReserve1;
		ptNode->m_tDualAudRcvFormat.m_wStaticPayload = CTpTypeAdpt::GetAudPayloadValue(tNodeCap.m_tAudRcvCap.m_atAudFmt[0].m_emFormat);
	}
}

void CCallNodeMgr::GetDualNodeCapset(TCapNode* ptNode, TUmsNodeCapset& tNodeCap)
{
	tNodeCap.m_wAudDecNum = ptNode->m_wAudRcvNum;
	tNodeCap.m_wAudEncNum = ptNode->m_wAudSndNum;
	tNodeCap.m_wVidDecNum = ptNode->m_wVidRcvNum;
	tNodeCap.m_wVidEncNum = ptNode->m_wVidSndNum;

	if (emTPH264HP == ptNode->m_tDualVidRcvFormat.m_tFormat.m_emQualityLvl)
	{
		memcpy(&tNodeCap.m_tVidRcvCap.m_tHp, &ptNode->m_tDualVidRcvFormat.m_tFormat, sizeof(TUmsVidFormat));
	}
	else
	{
		memcpy(&tNodeCap.m_tVidRcvCap.m_tBp, &ptNode->m_tDualVidRcvFormat.m_tFormat, sizeof(TUmsVidFormat));
	}
	tNodeCap.m_tVidRcvCap.m_wDynamicPayload = ptNode->m_tDualVidRcvFormat.m_wDynamicPayload;

	if (emTPH264HP == ptNode->m_tDualVidSndFormat.m_tFormat.m_emQualityLvl)
	{
		memcpy(&tNodeCap.m_tVidSndCap.m_tHp, &ptNode->m_tDualVidSndFormat.m_tFormat, sizeof(TUmsVidFormat));
	}
	else
	{
		memcpy(&tNodeCap.m_tVidSndCap.m_tBp, &ptNode->m_tDualVidSndFormat.m_tFormat, sizeof(TUmsVidFormat));
	}
	tNodeCap.m_tVidSndCap.m_wDynamicPayload = ptNode->m_tDualVidSndFormat.m_wDynamicPayload;

	if (emChanOpen == ptNode->m_tRmtChan.m_tDualVidDec.m_emChanState)
	{
		tNodeCap.m_atVidDec->m_bIsChanOn = TRUE;
	}
	tNodeCap.m_atVidDec->m_bIsChanOn = ptNode->m_tRmtChan.m_tDualVidDec.m_emChanState;
	tNodeCap.m_atVidDec->m_tChanAddr = ptNode->m_tRmtChan.m_tDualVidDec.m_tChanAddr;
	tNodeCap.m_atVidDec->m_tPAHandle = ptNode->m_tRmtChan.m_tDualVidDec.m_tPAHandle;

	if (emChanOpen == ptNode->m_tRmtChan.m_tDualVidEnc.m_emChanState)
	{
		tNodeCap.m_atVidEnc->m_bIsChanOn = TRUE;
	}
	tNodeCap.m_atVidEnc->m_bIsChanOn = ptNode->m_tRmtChan.m_tDualVidEnc.m_emChanState;
	tNodeCap.m_atVidEnc->m_tChanAddr = ptNode->m_tRmtChan.m_tDualVidEnc.m_tChanAddr;
	tNodeCap.m_atVidEnc->m_tPAHandle = ptNode->m_tRmtChan.m_tDualVidEnc.m_tPAHandle;
}
/*==============================================================================
函数名    :  AddNewCall
功能      :  添加一个呼叫，如果已经存在则不做操作
算法实现  :  本级最大呼叫数为TP_CONF_MAX_EPNUM
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-10               zhaixiaogang
==============================================================================*/
TCapNode* CCallNodeMgr::AddNewCall(TTpCallAddr& tDstAddr, BOOL32& bExist)
{
	bExist = FALSE;

	//查询是否有重名
	TCapNode* ptNode = NULL;

	for (ptNode = FirstNode(); ptNode != NULL; ptNode = NextLoalNode(ptNode))
	{
		if (tDstAddr.m_bAliasIP)
		{
			if (ptNode->m_tCalledAddr.m_dwIP == tDstAddr.m_dwIP && 
				((!tDstAddr.m_tAlias.IsInValid() && ptNode->m_tCalledAddr.m_tAlias == tDstAddr.m_tAlias) || (!tDstAddr.m_tE164.IsInValid() && ptNode->m_tCalledAddr.m_tE164 == tDstAddr.m_tE164)))
			{
				bExist = TRUE;
				return ptNode;			
			}
		}
		else
		{
			if (!tDstAddr.m_tAlias.IsInValid())
			{
				if (ptNode->m_tCalledAddr.m_tAlias == tDstAddr.m_tAlias)
				{
					bExist = TRUE;
					return ptNode;	
				}
			}
			if (!tDstAddr.m_tE164.IsInValid())
			{
				if (ptNode->m_tCalledAddr.m_tE164 == tDstAddr.m_tE164)
				{
					bExist = TRUE;
					return ptNode;
				}
			}
			if (0 != tDstAddr.m_dwIP)
			{
				if (ptNode->m_tCalledAddr.m_dwIP == tDstAddr.m_dwIP)
				{
					bExist = TRUE;
					return ptNode;
				}
			}
		}
	}

	//寻找空位
	u16 wIndex = TP_INVALID_INDEX;
	for (wIndex = 1; wIndex < UMS_CONF_EP_NUM; ++wIndex)
	{
		if (!m_aptCallNode[wIndex]->m_bUsed)
		{
			break;
		}
	}

	if (wIndex == UMS_CONF_EP_NUM)
	{
		MdlError(Ums_Mdl_Call, ("AddNewCall alloc new node failed!\n"));
		return NULL;
	}

	if (NULL != m_ptHeadNode)
	{
		ptNode = m_ptHeadNode;
		
		while(VALID_LOCAL_EPID(ptNode->m_wBrotherEpID))
		{
			ptNode = (TCapNode*)m_aptCallNode[ptNode->m_wBrotherEpID];
		}

		ptNode->m_wBrotherEpID = wIndex;
		ptNode = (TCapNode*)m_aptCallNode[wIndex];
	}
	else
	{
		ptNode = (TCapNode*)m_aptCallNode[wIndex];
		m_ptHeadNode = ptNode;
	}
	ptNode->m_bUsed = TRUE;

	GetValidCallType(tDstAddr);
	ptNode->m_tCalledAddr = tDstAddr;
	ptNode->m_tConfName = ptNode->m_tCalledAddr.GetValidAlias();
	ptNode->m_emCallState = ums_UmsConfNodeState_uncall;

	return ptNode;
}


BOOL32 CCallNodeMgr::AssignNodeRes(TCapNode* ptNode, TEqpRes* ptAdatper)
{
	CUmsConfInst* pInst = Inst();
	BOOL32 bRet;
	u16 wChanIndex = 0;
	
	ReleaseNodeRes(ptNode);

	if (NULL == ptAdatper)
	{
		TAdaptEqpParam tAdapterEqp;
		tAdapterEqp.m_ptEqpRes = &ptNode->m_tAdapterEqp;
		bRet = AssignEqpEx(&tAdapterEqp);
		if (!bRet)
		{	
			MdlError(Ums_Mdl_Call, ("AssignNodeRes alloc adapter failed! wConfID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n", pInst->GetInsID(), 
					ptNode->m_tCalledAddr.m_tAlias.m_abyAlias,ptNode->m_tCalledAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP)));
			return FALSE;
		}
	}
	else
	{
		ptNode->m_tAdapterEqp = *ptAdatper;
	}

	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptNode->m_aptChanAddr[wChanIndex] = CUmsConfInst::m_cLocChanAddrMgr.AllocNode();
		if (ptNode->m_aptChanAddr[wChanIndex] == NULL)
		{		
			MdlError(Ums_Mdl_Call, ("AssignNodeRes alloc chan addr failed! wConfID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n", pInst->GetInsID(), 
				ptNode->m_tCalledAddr.m_tAlias.m_abyAlias,ptNode->m_tCalledAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP)));
			ReleaseNodeRes(ptNode);
			return FALSE;
		}

		ptNode->m_aptSmallChanAddr[wChanIndex] = CUmsConfInst::m_cLocSmallChanAddrMgr.AllocNode();
		if (ptNode->m_aptSmallChanAddr[wChanIndex] == NULL)
		{				
			MdlError(Ums_Mdl_Call, ("AssignNodeRes alloc small chan addr failed! wConfID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n", pInst->GetInsID(), 
				ptNode->m_tCalledAddr.m_tAlias.m_abyAlias,ptNode->m_tCalledAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP)));
			ReleaseNodeRes(ptNode);
			return FALSE;
		}
	}

	ptNode->m_ptDualAddr = CUmsConfInst::m_clocDualAddrMgr.AllocNode();
	if (ptNode->m_ptDualAddr == NULL)
	{				
		MdlError(Ums_Mdl_Call, ("AssignNodeRes alloc dual addr failed! wConfID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n", pInst->GetInsID(), 
			ptNode->m_tCalledAddr.m_tAlias.m_abyAlias,ptNode->m_tCalledAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP)));
		ReleaseNodeRes(ptNode);
		return FALSE;
	}

	ptNode->m_ptMixAddr = CUmsConfInst::m_clocMixAddrMgr.AllocNode();
	if (ptNode->m_ptMixAddr == NULL)
	{					
		MdlError(Ums_Mdl_Call, ("AssignNodeRes alloc mix addr failed! wConfID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n", pInst->GetInsID(), 
			ptNode->m_tCalledAddr.m_tAlias.m_abyAlias,ptNode->m_tCalledAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP)));
		ReleaseNodeRes(ptNode);
		return FALSE;
	}

	bRet = AssignDsRes(TRUE, &ptNode->m_tMediaEqp, ptNode->m_tCalledAddr.m_dwIP);
	if (!bRet)
	{
		MdlError(Ums_Mdl_Call, ("AssignNodeRes alloc media failed! wConfID:%d, Alias:%s,E164:%s,IP:"TPIPFORMAT"\n", pInst->GetInsID(), 
			ptNode->m_tCalledAddr.m_tAlias.m_abyAlias,ptNode->m_tCalledAddr.m_tE164.m_abyAlias,Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP)));
		ReleaseNodeRes(ptNode);
		return FALSE;
	}

	MdlHint(Ums_Mdl_Call, ("AssignNodeRes ConfID:%d, EpID:%d, AdapterIndex:%d, mediaIndex:%d\n"
						, pInst->GetInsID(), ptNode->m_wEpID,  ptNode->m_tAdapterEqp.m_wEqpIndex, ptNode->m_tMediaEqp.m_wEqpIndex));
	
	TChanRcvAddr* ptVirLocalNode;
	u32 dwEqpIP = ptNode->m_tMediaEqp.m_dwEqpIp;
	//接收视频地址
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptVirLocalNode = &ptNode->m_aptChanAddr[wChanIndex]->m_tVid;
		ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);
	}
	
	//接收视频地址
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptVirLocalNode = &ptNode->m_aptChanAddr[wChanIndex]->m_tAud;	
		ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);		

	}
	
	for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
	{
		ptVirLocalNode = ptNode->m_aptSmallChanAddr[wChanIndex];
		ptVirLocalNode->m_tRtpAddr.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForRcv.SetIP(dwEqpIP);
		ptVirLocalNode->m_tRtcpForSnd.SetIP(dwEqpIP);
	}

	ptNode->m_ptMixAddr->m_tRtpAddr.SetIP(dwEqpIP);
	ptNode->m_ptMixAddr->m_tRtcpForRcv.SetIP(dwEqpIP);
	ptNode->m_ptMixAddr->m_tRtcpForSnd.SetIP(dwEqpIP);

	ptNode->m_ptDualAddr->m_tVid.m_tRtpAddr.SetIP(dwEqpIP);
	ptNode->m_ptDualAddr->m_tVid.m_tRtcpForRcv.SetIP(dwEqpIP);
	ptNode->m_ptDualAddr->m_tVid.m_tRtcpForSnd.SetIP(dwEqpIP);

	
	ptNode->m_ptDualAddr->m_tAud.m_tRtpAddr.SetIP(dwEqpIP);
	ptNode->m_ptDualAddr->m_tAud.m_tRtcpForRcv.SetIP(dwEqpIP);
	ptNode->m_ptDualAddr->m_tAud.m_tRtcpForSnd.SetIP(dwEqpIP);

	return TRUE;
}

BOOL32 CCallNodeMgr::ReleaseNodeRes(TCapNode* ptNode)
{
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (ptNode->m_aptChanAddr[wIndex] != NULL)
		{
			CUmsConfInst::m_cLocChanAddrMgr.FreeBuff(ptNode->m_aptChanAddr[wIndex]);
			ptNode->m_aptChanAddr[wIndex] = NULL;
		}

		if (ptNode->m_aptSmallChanAddr[wIndex] != NULL)
		{
			CUmsConfInst::m_cLocSmallChanAddrMgr.FreeBuff(ptNode->m_aptSmallChanAddr[wIndex]);
			ptNode->m_aptSmallChanAddr[wIndex] = NULL;
		}
	}
	
	if (ptNode->m_ptDualAddr != NULL)
	{
		CUmsConfInst::m_clocDualAddrMgr.FreeBuff(ptNode->m_ptDualAddr);
		ptNode->m_ptDualAddr = NULL;
	}
	
	if (ptNode->m_ptMixAddr != NULL)
	{
		CUmsConfInst::m_clocMixAddrMgr.FreeBuff(ptNode->m_ptMixAddr);
		ptNode->m_ptMixAddr = NULL;
	} 

	if (ptNode->m_ptCasCadeChairAddr != NULL)
	{
		CUmsConfInst::m_cCascadeChairAddrMgr.FreeBuff(ptNode->m_ptCasCadeChairAddr);
		ptNode->m_ptCasCadeChairAddr = NULL;
	}

	if (ptNode->m_tAdapterEqp.IsValid())
	{
		TAdaptEqpParam tAdapterEqp;
		tAdapterEqp.m_ptEqpRes = &ptNode->m_tAdapterEqp;
		ReleaseEqpEx(&tAdapterEqp);
		
		ptNode->m_tAdapterEqp.Clear();
	}

	if (ptNode->m_tMediaEqp.IsValid())
	{
		TMediaParam tEqpMedia;
		tEqpMedia.m_ptEqpRes = &ptNode->m_tMediaEqp;
		tEqpMedia.m_emAssignType = TMediaParam::emAssignNode;
		ReleaseEqpEx(&tEqpMedia);

		ptNode->m_tMediaEqp.Clear();
	}

	return TRUE;
}

BOOL32 CCallNodeMgr::AdjustResOnChanConnect(TCapNode* ptNode)
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (ptNode->m_tRmtChan.m_atVidEnc[wIndex].IsOpen() || ptNode->m_tRmtChan.m_atAudEnc[wIndex].IsOpen())
		{
			continue;
		}

		if ( ptNode->m_tRmtChan.m_atVidDec[wIndex].IsOpen() || ptNode->m_tRmtChan.m_atAudDec[wIndex].IsOpen() )
		{
			continue;
		}

		if (ptNode->m_aptChanAddr[wIndex] != NULL)
		{
			CUmsConfInst::m_cLocChanAddrMgr.FreeBuff(ptNode->m_aptChanAddr[wIndex]);
			ptNode->m_aptChanAddr[wIndex] = NULL;
		}
	}

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if ( ptNode->m_tRmtChan.m_atSmallVidEnc[wIndex].IsOpen() || ptNode->m_tRmtChan.m_atSmallVidDec[wIndex].IsOpen() )
		{
			continue;
		}
		
		if (ptNode->m_aptSmallChanAddr[wIndex] != NULL)
		{
			CUmsConfInst::m_cLocSmallChanAddrMgr.FreeBuff(ptNode->m_aptSmallChanAddr[wIndex]);
			ptNode->m_aptSmallChanAddr[wIndex] = NULL;
		}
	}

	if (!ptNode->m_tRmtChan.m_tAudMixEnc.IsOpen()&&!ptNode->m_tRmtChan.m_tAudMixDec.IsOpen())
	{
		CUmsConfInst::m_clocMixAddrMgr.FreeBuff(ptNode->m_ptMixAddr);
		ptNode->m_ptMixAddr = NULL;
	}
	return TRUE;
}

void CCallNodeMgr::MakeCallerHandle(TUmsHandle& tHandle, u16 wEpID)
{	
	TCapNode* ptNode = GetCapsetNode(wEpID);
	if (NULL != ptNode)
	{
		tHandle.m_dwAdapteID  = ptNode->m_tAdapterEqp.m_dwEqpNode;
		tHandle.handPaCall = ptNode->m_dwStackHandle;
		tHandle.MakeAppHandle(Inst()->GetInsID(), ptNode->m_wEpID);
		tHandle.m_emProtocol = ptNode->m_emCallProtocol;
	}
	else
	{
		tHandle.Clear();
		MdlError(Ums_Mdl_Call, ("MakeCallerHandle Failed. ConfID:%d, wEpID:%d\n", Inst()->GetInsID(), wEpID));
	}
}

TCallNode* CCallNodeMgr::GetNode(u16 wEpID)
{
	if (VALID_ALL_EPID(wEpID))
	{
		return m_aptCallNode[wEpID];
	}
	return NULL;
}

TCallNode* CCallNodeMgr::GetNodeByName(TTPAlias& tAlias, TCallNode* ptRoot)
{
	if (NULL == ptRoot)
	{
		ptRoot = m_ptHeadNode;
	}

	if (NULL == ptRoot)
	{
		return NULL;
	}

	if (ptRoot->m_bUsed && (ptRoot->m_tConfName == tAlias || ptRoot->m_tCalledAddr.m_tAlias == tAlias))
	{
		return ptRoot;
	}

	TCallNode* ptTmpNode = NULL;
	if(VALID_ALL_EPID(ptRoot->m_wBrotherEpID))
	{
		ptTmpNode = GetNodeByName(tAlias, m_aptCallNode[ptRoot->m_wBrotherEpID]);
		if (NULL != ptTmpNode)
		{
			return ptTmpNode;
		}
	}

	if (VALID_ALL_EPID(ptRoot->m_wChildEpID))
	{
		ptTmpNode = GetNodeByName(tAlias, m_aptCallNode[ptRoot->m_wChildEpID]);
		if (NULL != ptTmpNode)
		{
			return ptTmpNode;
		}
	}

	return NULL;
}

/*==============================================================================
函数名    :  GetNode
功能      :  以ptRoot为根，按照awLowEpID中的下级ID索引，查找子节点
算法实现  :  
参数说明  :  pParent返回父节点
返回值说明:  目标结点
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-6-1               zhaixiaogang
==============================================================================*/
TCallNode* CCallNodeMgr::GetNodeByChildIDList(TCallNode* ptRoot, u16 awLowEpID[], u16 wNum, TCallNode** pParent)
{
	*pParent = NULL;

	if (NULL == ptRoot)
	{
		return NULL;
	}

	if (wNum == 0)
	{
		if (VALID_ALL_EPID(ptRoot->m_wParentEpID))
		{
			*pParent = m_aptCallNode[ptRoot->m_wParentEpID];
		}
		return ptRoot;
	}

	u16 wIndex = 0;

	TCallNode* pTempParent = ptRoot;
	while(wIndex < (wNum-1) && NULL != pTempParent)
	{
		pTempParent = GetNodeByChildEpID(pTempParent, awLowEpID[wIndex]);
		++wIndex;
	}

	if (NULL == pTempParent || wIndex != (wNum-1))
	{
		return NULL;
	}

	*pParent = pTempParent;
	return GetNodeByChildEpID(pTempParent, awLowEpID[wIndex]);
}

//根据下级的ID索引，查找结点
TCallNode* CCallNodeMgr::GetNodeByChildEpID(TCallNode* ptRoot, u16 wLowerEp)
{
	if (NULL == ptRoot)
	{
		return NULL;
	}

	TCallNode* ptSonNode = NULL;
	TCallNode* ptChild = GetNode(ptRoot->m_wChildEpID);
	while(NULL != ptChild)
	{
		if (ptChild->m_wLowChildEpID == wLowerEp)
		{
			return ptChild;
		}

		ptSonNode = GetNodeByChildEpID(ptChild, wLowerEp);
		if (NULL != ptSonNode)
		{
			return ptSonNode;
		}
		
		ptChild = GetNode(ptChild->m_wBrotherEpID);
	}
	return NULL;
}

u16 CCallNodeMgr::GetAllNode( u16 atNodeID[], u16 wMaxNum )
{
	u16 wNum = 0;
	if (NULL == m_ptHeadNode || wMaxNum == 0)
	{
		return 0;
	}

	wNum = GetNodeByRoot(atNodeID, wMaxNum, m_ptHeadNode);
	
	return wNum;
}


u16 CCallNodeMgr::GetAllNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot)
{
	u16 wNum = 0;
	if (NULL == ptRoot || wMaxNum == 0)
	{
		return 0;
	}
	atNodeID[wNum] = ptRoot->m_wEpID;
	wNum++;

	if (VALID_ALL_EPID(ptRoot->m_wChildEpID))
	{
		wNum += GetNodeByRoot(atNodeID+wNum, wMaxNum - wNum, m_aptCallNode[ptRoot->m_wChildEpID]);
	}
	
	return wNum;
}

u16 CCallNodeMgr::GetAllChildNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot)
{
	u16 wNum = 0;
	if (NULL == ptRoot || wMaxNum == 0)
	{
		return 0;
	}

	if (VALID_ALL_EPID(ptRoot->m_wChildEpID))
	{
		wNum += GetNodeByRoot(atNodeID+wNum, wMaxNum - wNum, m_aptCallNode[ptRoot->m_wChildEpID]);
	}
	
	return wNum;
}

u16 CCallNodeMgr::GetNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot)
{
	u16 wNum = 0;
	if (NULL == ptRoot || wMaxNum == 0)
	{
		return 0;
	}
	atNodeID[wNum] = ptRoot->m_wEpID;
	wNum++;
	
	if (VALID_ALL_EPID(ptRoot->m_wChildEpID))
	{
		wNum += GetNodeByRoot(atNodeID+wNum, wMaxNum - wNum, m_aptCallNode[ptRoot->m_wChildEpID]);
	}
	
	if(VALID_ALL_EPID(ptRoot->m_wBrotherEpID))
	{
		wNum += GetNodeByRoot(atNodeID+wNum, wMaxNum - wNum, m_aptCallNode[ptRoot->m_wBrotherEpID]);
	}
	return wNum;
}


//获取ptNode的祖先结点
TCapNode* CCallNodeMgr::GetForeFatherNode(TCallNode* ptNode)
{
	if (NULL == ptNode)
	{
		return NULL;
	}
	TCallNode* ptTemp = GetNode(ptNode->m_wParentEpID);
	while (NULL != ptTemp)
	{
		ptNode = ptTemp;
		ptTemp = GetNode(ptNode->m_wParentEpID);
	}
	return (TCapNode*)ptNode;
}

TCapNode* CCallNodeMgr::GetForeFatherNode(u16 wEpID)
{
	TCallNode* ptNode = GetNode(wEpID);
	if (NULL == ptNode)
	{
		return NULL;
	}
	TCallNode* ptTemp = GetNode(ptNode->m_wParentEpID);
	while (NULL != ptTemp)
	{
		ptNode = ptTemp;
		ptTemp = GetNode(ptNode->m_wParentEpID);
	}
	return (TCapNode*)ptNode;
}

BOOL32 CCallNodeMgr::GetPathKey(TEpPathKey& tKeyID, u16 wEpID)
{
	TCallNode* ptNode = GetNode(wEpID);
	if (NULL == ptNode)
	{
		return FALSE;
	}
	tKeyID.Clear();
	s8 szBuf[TP_MAX_EPID_LEN+1];

	while(NULL != ptNode)
	{
		snprintf(szBuf, TP_MAX_EPID_LEN, "%d.%s", ptNode->m_wEpID, tKeyID.m_szEpID);
		memcpy(tKeyID.m_szEpID, szBuf, TP_MAX_EPID_LEN+1);
		ptNode = GetNode(ptNode->m_wParentEpID);
	}

	return TRUE;
}
void CCallNodeMgr::DeleteNode(TCallNode* ptNode)
{
	if (NULL == ptNode)
	{
		return;
	}

	if (VALID_CAPSET_EPID(ptNode->m_wEpID))
	{
		TCapNode* ptCapNode = (TCapNode*)ptNode;
		ReleaseNodeRes(ptCapNode);
	}

	if (Is_Caller_Node(ptNode->m_wEpID))
	{
		ptNode->Clear();
		return;
	}

	TCallNode* ptParent = NULL;
	TCallNode* ptBrother = NULL;
	if (VALID_ALL_EPID(ptNode->m_wParentEpID))
	{
		ptParent = m_aptCallNode[ptNode->m_wParentEpID];
		ptBrother = m_aptCallNode[ptParent->m_wChildEpID];
	}
	else
	{
		ptBrother = m_ptHeadNode;
	}

	if (NULL == ptBrother)
	{
		MdlError(Ums_Mdl_Call, ("DeleteNode failed. epid:%d\n", ptNode->m_wEpID));
		return;
	}

	if (ptBrother == ptNode)
	{
		if (VALID_ALL_EPID(ptNode->m_wBrotherEpID))
		{
			if (NULL == ptParent)
			{
				m_ptHeadNode = (TCapNode*)m_aptCallNode[ptNode->m_wBrotherEpID];
			}
			else
			{
				ptParent->m_wChildEpID = ptNode->m_wBrotherEpID;
			}
		}
		else
		{
			if (NULL != ptParent)
			{
				ptParent->m_wChildEpID = TP_INVALID_INDEX;
			}
			if (ptBrother == m_ptHeadNode)
			{
				m_ptHeadNode = NULL;
			}
		}
	}
	else
	{
		if (VALID_ALL_EPID(ptBrother->m_wBrotherEpID))
		{
			while (ptBrother->m_wBrotherEpID != ptNode->m_wEpID)
			{
				ptBrother = m_aptCallNode[ptBrother->m_wBrotherEpID];
			}
			ptBrother->m_wBrotherEpID = ptNode->m_wBrotherEpID;
		}
		
	}

	if (VALID_ALL_EPID(ptNode->m_wChildEpID))
	{
		ClearAllChildNode(m_aptCallNode[ptNode->m_wChildEpID]);
	}
	ptNode->Clear();
}



TCallNode* CCallNodeMgr::AddChildNode(u16 wParentID, TConfNodeCallUpdateTr& tDstInfo)
{
	if (!VALID_ALL_EPID(wParentID))
	{
		MdlError(Ums_Mdl_Call, ("AddChildNode parentID invalid. confid:%d, parentid:%d\n",Inst()->GetInsID(), wParentID));
		return NULL;
	}

	if (!m_aptCallNode[wParentID]->m_bUsed)
	{
		MdlError(Ums_Mdl_Call, ("AddChildNode parentID unused. confid:%d, parentid:%d\n", Inst()->GetInsID(), wParentID));
		return NULL;
	}

	u16 wEpID = FindIdleChildNode();
	if (!VALID_ALL_EPID(wEpID))
	{
		MdlError(Ums_Mdl_Call, ("AddChildNode no idle child index. confid:%d\n", Inst()->GetInsID()));
		return NULL;
	}

	if (!VALID_ALL_EPID(m_aptCallNode[wParentID]->m_wChildEpID))
	{
		m_aptCallNode[wParentID]->m_wChildEpID = wEpID;
	}
	else
	{
		u16 wBrotherID = m_aptCallNode[wParentID]->m_wChildEpID;
		while(VALID_ALL_EPID(m_aptCallNode[wBrotherID]->m_wBrotherEpID))
		{
			wBrotherID = m_aptCallNode[wBrotherID]->m_wBrotherEpID;
		}
		m_aptCallNode[wBrotherID]->m_wBrotherEpID = wEpID;
	}

	m_aptCallNode[wEpID]->m_wParentEpID = wParentID;
	m_aptCallNode[wEpID]->m_bUsed = TRUE;
	m_aptCallNode[wEpID]->SetNodeCallInfo(tDstInfo);
	return m_aptCallNode[wEpID];
}

TCallNode* CCallNodeMgr::AddChildNodeForMcu(TCapNode* ptMcuNode, TUmsMcuRosterItem& tRosterItem)
{
	if (NULL == ptMcuNode || !ptMcuNode->IsMcu())
	{
		return NULL;
	}

	u16 wParentID = ptMcuNode->m_wEpID;
	if (!VALID_ALL_EPID(wParentID))
	{
		MdlError(Ums_Mdl_Call, ("AddMcuChildNode parentID invalid. confid:%d, parentid:%d\n",Inst()->GetInsID(), wParentID));
		return NULL;
	}
	
	if (!m_aptCallNode[wParentID]->m_bUsed)
	{
		MdlError(Ums_Mdl_Call, ("AddMcuChildNode parentID unused. confid:%d, parentid:%d\n", Inst()->GetInsID(), wParentID));
		return NULL;
	}

	u16 wEpID = FindIdleChildNode();
	if (!VALID_ALL_EPID(wEpID))
	{
		MdlError(Ums_Mdl_Call, ("AddMcuChildNode no idle child index. confid:%d\n", Inst()->GetInsID()));
		return NULL;
	}
	
	if (!VALID_ALL_EPID(m_aptCallNode[wParentID]->m_wChildEpID))
	{
		m_aptCallNode[wParentID]->m_wChildEpID = wEpID;
	}
	else
	{
		u16 wBrotherID = m_aptCallNode[wParentID]->m_wChildEpID;
		while(VALID_ALL_EPID(m_aptCallNode[wBrotherID]->m_wBrotherEpID))
		{
			wBrotherID = m_aptCallNode[wBrotherID]->m_wBrotherEpID;
		}
		m_aptCallNode[wBrotherID]->m_wBrotherEpID = wEpID;
	}

	m_aptCallNode[wEpID]->m_wParentEpID = wParentID;
	m_aptCallNode[wEpID]->m_bUsed = TRUE;
	m_aptCallNode[wEpID]->m_wLowChildEpID = GETINS(tRosterItem.m_dwPID); 

	m_aptCallNode[wEpID]->m_emEpType = emTPEndpointH323MT; // mcu的下级mcu使用 323终端类型

	if (1 == tRosterItem.m_byState)
	{
		m_aptCallNode[wEpID]->m_emCallState = ums_UmsConfNodeState_online;
	}
	else if (2 == tRosterItem.m_byState)
	{
		m_aptCallNode[wEpID]->m_emCallState = ums_UmsConfNodeState_stopcall;
	}
	else if (3 == tRosterItem.m_byState)
	{
		m_aptCallNode[wEpID]->m_emCallState = ums_UmsConfNodeState_calling;
	}
	else
	{
		m_aptCallNode[wEpID]->m_emCallState = ums_UmsConfNodeState_unused;
	}
	return m_aptCallNode[wEpID];
}

TCallNode* CCallNodeMgr::AddChildNodeForMcu(TCapNode* ptMcuNode, TUmcMcuPart& tPart)
{
	if (NULL == ptMcuNode || !ptMcuNode->IsMcu())
	{
		return NULL;
	}
	
	u16 wParentID = ptMcuNode->m_wEpID;
	if (!VALID_ALL_EPID(wParentID))
	{
		MdlError(Ums_Mdl_Call, ("AddMcuChildNode parentID invalid. confid:%d, parentid:%d\n",Inst()->GetInsID(), wParentID));
		return NULL;
	}
	
	if (!m_aptCallNode[wParentID]->m_bUsed)
	{
		MdlError(Ums_Mdl_Call, ("AddMcuChildNode parentID unused. confid:%d, parentid:%d\n", Inst()->GetInsID(), wParentID));
		return NULL;
	}
	
	u16 wEpID = FindIdleChildNode();
	if (!VALID_ALL_EPID(wEpID))
	{
		MdlError(Ums_Mdl_Call, ("AddMcuChildNode no idle child index. confid:%d\n", Inst()->GetInsID()));
		return NULL;
	}
	
	if (!VALID_ALL_EPID(m_aptCallNode[wParentID]->m_wChildEpID))
	{
		m_aptCallNode[wParentID]->m_wChildEpID = wEpID;
	}
	else
	{
		u16 wBrotherID = m_aptCallNode[wParentID]->m_wChildEpID;
		while(VALID_ALL_EPID(m_aptCallNode[wBrotherID]->m_wBrotherEpID))
		{
			wBrotherID = m_aptCallNode[wBrotherID]->m_wBrotherEpID;
		}
		m_aptCallNode[wBrotherID]->m_wBrotherEpID = wEpID;
	}
	
	m_aptCallNode[wEpID]->m_wParentEpID = wParentID;
	m_aptCallNode[wEpID]->m_bUsed = TRUE;
	m_aptCallNode[wEpID]->m_wLowChildEpID = GETINS(tPart.m_dwPID);

	m_aptCallNode[wEpID]->SetMcuNodeCallInfo(tPart);

	return m_aptCallNode[wEpID];
}

void CCallNodeMgr::ClearAllChildNode(TCallNode* ptNode)
{
	if (NULL == ptNode)
	{
		return;
	}

	if (VALID_ALL_EPID(ptNode->m_wBrotherEpID))
	{
		ClearAllChildNode(m_aptCallNode[ptNode->m_wBrotherEpID]);
	}

	if (VALID_ALL_EPID(ptNode->m_wChildEpID))
	{
		ClearAllChildNode(m_aptCallNode[ptNode->m_wChildEpID]);
	}

	ptNode->Clear();
}

u16 CCallNodeMgr::FindIdleChildNode()
{
	for (u16 wIndex = MAX_CAPSET_NODE_NUM+1; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
	{
		if (!m_aptCallNode[wIndex]->m_bUsed)
		{
			return wIndex;
		}
	}
	return TP_INVALID_INDEX;
}
void CCallNodeMgr::ForEachTreeNode(PForEachFun pCbFun, TCallNode* pRootNode, u16 Lv)
{
	if (NULL == pRootNode)
	{
		return;
	}

	pCbFun(pRootNode, VALID_CAPSET_EPID(pRootNode->m_wEpID) ? &((TCapNode*)(m_aptCallNode[pRootNode->m_wEpID]))->m_tRmtChan : NULL, Lv);

	if (VALID_ALL_EPID(pRootNode->m_wChildEpID))
	{
		ForEachTreeNode(pCbFun, m_aptCallNode[pRootNode->m_wChildEpID], Lv+1);
	}

	if(VALID_ALL_EPID(pRootNode->m_wBrotherEpID))
	{
		ForEachTreeNode(pCbFun, m_aptCallNode[pRootNode->m_wBrotherEpID], Lv);
	}
}

//1、上级通知下级时为下级ID  2、下级通知上级时为本地
BOOL32 CCallNodeMgr::InitTEpKey( TEpKey& tEpID, BOOL32 bIsUPToDown, u16 wLocalEpID, u16 wLowerEpID )
{	
	if ( bIsUPToDown )
	{
		tEpID.m_wEpID = wLowerEpID;
	}
	else
	{
		tEpID.m_wEpID = wLocalEpID;
	}
	
	return TRUE;
}

u16 CCallNodeMgr::GetLocalEpIDByTEpKey( u16 wRootEpID, const TEpKey& tEpID )
{
	
	TCallNode* pAddNode = NULL;
	TCallNode* pParentNode = NULL;
	
	TCallNode* pRootNode = GetNode(wRootEpID);
	if ( NULL == pRootNode )
	{
		MdlError(Ums_Mdl_Call, ("CCallNodeMgr::GetLocalEpID Node RootEpID. confid:%d, epid:%d\n", Inst()->GetInsID(), tEpID.m_wEpID));
		return TP_INVALID_INDEX;
	}
	
	pAddNode = GetNodeByChildEpID(pRootNode, tEpID.m_wEpID);
	if ( NULL == pAddNode )
	{
		return TP_INVALID_INDEX;
	}
	
	return pAddNode->m_wEpID;
}

void CCallNodeMgr::AdjustNodeRes(u16 wEpID, u16 wScreenIndx, EmTpVideoResolution emRes, BOOL32 bReset )
{

	TCallNode* ptNode = GetNode(wEpID);
	TCapNode* ptFatherNode = GetForeFatherNode(ptNode);
	if ( NULL == ptNode || NULL == ptFatherNode || !ptNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CCallNodeMgr::AdjustNodeRes. Node is NULL! EpID:%d, ConfID:%d, pNode:%d\n", wEpID, Inst()->GetInsID(), ptNode));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CCallNodeMgr::AdjustNodeRes. EpID:%d, ScrIndx:%d, ConfID:%d, Res:%d, Reset:%d\n", 
		wEpID, wScreenIndx, Inst()->GetInsID(), emRes, bReset));

	TAdjustVidRes tRes;
	tRes.m_wScreenIndx = wScreenIndx;
	tRes.m_bReset = bReset;

	TUmsHandle tOutHandle;
	MakeCallerHandle(tOutHandle, ptFatherNode->m_wEpID);

	if ( ptNode != ptFatherNode )
	{
		tRes.m_wEpID = ptNode->m_wLowChildEpID;
		tRes.m_dwVidRes = (u32)emRes;
	}
	else
	{
		BOOL32 bRet = TRUE;
		if ( bReset )
		{
			bRet = ptFatherNode->m_atResFrm[wScreenIndx].ResetRes(emRes);
		}
		else
		{
			bRet = ptFatherNode->m_atResFrm[wScreenIndx].AdjustRes(emRes);
		}

		if ( !bRet )
		{
			//无需调整
			return ;
		}

		tRes.m_wEpID = ptNode->m_wEpID;
		tRes.m_dwVidRes = (u32)ptFatherNode->m_atResFrm[wScreenIndx].GetCurRes();
	}

	UmsSendConfCtrl(tOutHandle, evtp_Conf_AdjustVidRes, &tRes, sizeof(tRes));

	return ;
}

void CCallNodeMgr::AdjustNodeFrame(u16 wEpID, u16 wScreenIndx, u16 wFrame, BOOL32 bReset )
{
	
	TCallNode* ptNode = GetNode(wEpID);
	TCapNode* ptFatherNode = GetForeFatherNode(ptNode);
	if ( NULL == ptNode || NULL == ptFatherNode || !ptNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CCallNodeMgr::AdjustNodeFrame. Node is NULL! EpID:%d, ConfID:%d, pNode:%d\n", wEpID, Inst()->GetInsID(), ptNode));
		return ;
	}
	
	MdlHint(Ums_Mdl_Call, ("CCallNodeMgr::AdjustNodeFrame. EpID:%d, ScrIndx:%d, ConfID:%d, Frame:%d, Reset:%d\n", 
		wEpID, wScreenIndx, Inst()->GetInsID(), wFrame, bReset));
	
	TAdjustFrameRate tFrame;
	tFrame.m_wScreenIndx = wScreenIndx;
	tFrame.m_bReset = bReset;
	
	TUmsHandle tOutHandle;
	MakeCallerHandle(tOutHandle, ptFatherNode->m_wEpID);

	if ( ptNode != ptFatherNode )
	{
		tFrame.m_wEpID = ptNode->m_wLowChildEpID;
		tFrame.m_wFrameRate = wFrame;
	}
	else
	{
		BOOL32 bRet = TRUE;
		if ( bReset )
		{
			bRet = ptFatherNode->m_atResFrm[wScreenIndx].ResetFrm(wFrame);
		}
		else
		{
			bRet = ptFatherNode->m_atResFrm[wScreenIndx].AdjustFrm(wFrame);
		}
		
		if ( !bRet )
		{
			//无需调整
			return ;
		}
		
		tFrame.m_wEpID = ptNode->m_wEpID;
		tFrame.m_wFrameRate = ptFatherNode->m_atResFrm[wScreenIndx].GetCurFrm();;
	}
	
	UmsSendConfCtrl(tOutHandle, evtp_Conf_AdjustFrameRate, &tFrame, sizeof(tFrame));
	
	return ;
}

TCallNode* CCallNodeMgr::GetNodeUnderThisUms( TCapNode* pUmsNode, u16 wEpId )
{// wEpId是挂在此pUmsNode下的节点，则返回其node，否则Null
	if (NULL == pUmsNode || !pUmsNode->IsUms())
	{
		return NULL;
	}

	TCallNode* pNode = GetNode(wEpId);
	TCapNode* pFartherNode = GetForeFatherNode(pNode);

	if (NULL != pNode && NULL != pFartherNode && pFartherNode->m_wEpID == pUmsNode->m_wEpID)
	{
		return pNode;
	}
	return NULL;
}

void CCallNodeMgr::addepip( u16 wEpid, u32 dwEpIp )
{
	m_mapEpIp[wEpid] = dwEpIp;
}

void CCallNodeMgr::delepip( u16 wEpid )
{
	m_mapEpIp.erase(wEpid);
}

BOOL32 CCallNodeMgr::ismtip(const u32 dwIp)
{
	std::map<u16,u32>::iterator  iter;
	for(iter = m_mapEpIp.begin(); iter != m_mapEpIp.end(); iter++)
	{
		if (dwIp == iter->second)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CCallNodeMgr::showip()
{
	msgprintnotime("[eplist]\n");
	std::map<u16,u32>::iterator  iter;
	for(iter = m_mapEpIp.begin(); iter != m_mapEpIp.end(); iter++)
	{
		msgprintnotime("  Ep:%d, IP:"TPIPFORMAT".\n", iter->first, u32ToIP(iter->second));
	}
}