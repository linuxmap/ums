#include "regoprdb.h"
#include "tpsys.h"
#include "innereventregsrv.h"
#include "eventoutsipadapter.h"
#include "eventtpsys.h"
#include "tptime.h"
#include "umsobject.h"
#include "regstruct.h"
#include "lanman.h"

CTpRegOprdbApp g_cTpRegOprdbApp;
API BOOL StartupTpDBInterface()
{
	g_cTpRegOprdbApp.CreateApp("RegOprdbApp",AID_UMSDB_APP,100);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( MAKEIID(AID_UMSDB_APP,1) );
	return TRUE;
}



void NotifyMsgToStack(u16 wEvent, void* pBuf, u16 wLen, TUmsHandle& tHandle)
{
	#define UMS_STACK_APP_INST	MAKEIID(AID_REGSIPSTACKOUT_APP, 1)
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(pBuf, wLen);
	cMsg.Post(UMS_STACK_APP_INST);
}


//服务器注册信息
typedef struct tagRegInfo
{
	u32					m_dwIpAddr;
	EmTPEndpointType	m_emType;
	BOOL32				m_bCheck;
	s8					m_acVersion[TP_MAX_VERSION_LEN + 1];
	s8					m_acCompileTm[TP_MAX_VERSION_LEN + 1];
	
	tagRegInfo()
	{
		memset(this, 0, sizeof(tagRegInfo));
	}
	
	tagRegInfo& operator = (const tagRegInfo& tRgs)
	{
		if ( this == &tRgs )
		{
			return *this;
		}
		
		memcpy(this, &tRgs, sizeof(tagRegInfo));
		
		return *this;
	}
	
	BOOL32 operator == (const tagRegInfo& tRhs)
	{
		if (m_dwIpAddr == tRhs.m_dwIpAddr && m_emType == tRhs.m_emType)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	
}TRegInfo;


typedef struct tagTRegInfoArray
{
	TRegInfo m_atRegInfo[MAX_SEND_REGINFO_NUM_ONE_TIME];
	u16		 m_wRegInfoNum;
	tagTRegInfoArray()
	{
		memset(this, 0, sizeof(tagTRegInfoArray));
	}
}TRegInfoArray;


s32 PreRegTimerCB(u32 dwTimerId, void* param)
{
    CTpRegOprdb* pcRunTimerDB = (CTpRegOprdb*)param;
    
    pcRunTimerDB->RegTimeOut(dwTimerId);
	return TP_RET_OK;
}

CTpRegOprdb::CTpRegOprdb()
:m_pcTimerMgr(NULL)
{
	m_wLogModuleId = Ums_Mdl_RegServer;
}

CTpRegOprdb::~CTpRegOprdb()
{
	ObjectExit();
}

void CTpRegOprdb::MessageProc( CTpMsg *const ptMsg)
{
	switch (ptMsg->GetEvent())
	{
	case evtp_ums_reg_req:
		{
			ProcessRegEvent(ptMsg);
			break;
		}

	case evtp_ums_unreg_req:
		{
			ProcessUnRegEvent(ptMsg);
			break;
		}

	case evtp_ums_arq_req:
		{
			ProcessARQEvent(ptMsg);
			break;
		}

	case evtp_ums_reg_info_req:		
		{
			ProcessRegInfoEvent(ptMsg);
			break;			
		}
			
	case EVTP_TIMER_PER_SECOND:
		{
			SetTimer(EVTP_TIMER_PER_SECOND, TP_INTERVAL_TIME_ONE_SECOND);
			if (m_pcTimerMgr)
			{	
				m_pcTimerMgr->Check();
			}
		}
		break;
	case evtp_ums_RegSer_Req_RegInfo:
		{
			SendRegInfoToUpgradTool(ptMsg);
			break;
		}
	default:
		break;
	}
}

BOOL CTpRegOprdb::ObjectInit(u32 wParam, u32 lParam)
{
	if (m_bInit)
	{
		return TRUE;
	}

	m_wCnsNums = 0;
	m_wUmsNums = 0;

	m_wUmsNodeNums = 0;
	m_wCnsNodeNums = 0;

	SetLogTitle("CTpDBInterface");

	m_pcTimerMgr = new CTpTimerMgr();
	m_pcTimerMgr->Create(TP_UMS_MAX_REGNUM+5);

	//每秒的定时器
	KillTimer(EVTP_TIMER_PER_SECOND);
	SetTimer(EVTP_TIMER_PER_SECOND, TP_INTERVAL_TIME_ONE_SECOND);

	return TRUE;
}

void CTpRegOprdb::ObjectExit(void)
{
	
	if (m_pcTimerMgr)
	{
		delete m_pcTimerMgr;
		m_pcTimerMgr = NULL;
	}

	m_wCnsNums = 0;
	m_wUmsNums = 0;

	CTpObject::ObjectExit();
}


/*==============================================================================
函数名    :  ProcessReg
功能      :  处理CNS的注册
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-3-8                 zhaixiaogang
==============================================================================*/
BOOL32 CTpRegOprdb::ProcessRegEvent(CTpMsg *const ptMsg)
{	
	TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
	TCnsRegInfo* ptRegInfo = (TCnsRegInfo*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	TCnsRegInfo tCnsRegInfo;
	
	tCnsRegInfo.Clear();
	tCnsRegInfo = *ptRegInfo;
	
	EmTpCnsRegUms byReason = AddReg(&tCnsRegInfo);
	
	u8 abyBuf[sizeof(TCnsRegRetResult)+sizeof(TCnsRegInfo)];

	TCnsRegRetResult* ptRet = (TCnsRegRetResult*)abyBuf;
	TCnsRegInfo* ptFindRet = (TCnsRegInfo*)(abyBuf+sizeof(TCnsRegRetResult));
	ptFindRet->Clear();

	ptRet->m_emReson = byReason;	

	memcpy(abyBuf+sizeof(TCnsRegRetResult), &tCnsRegInfo, sizeof(TCnsRegInfo));
	
	NotifyMsgToStack(evtp_ums_reg_ret, abyBuf, sizeof(abyBuf), *ptHandle);

	return TRUE;
}


BOOL32 CTpRegOprdb::ProcessUnRegEvent(CTpMsg *const ptMsg)
{
	TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
	TCnsRegInfo* ptRegInfo = (TCnsRegInfo*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	EmTpCnsRegUms byReason = DelReg(ptRegInfo);
	

	u8 abyBuf[sizeof(TCnsRegRetResult)+sizeof(TCnsRegInfo)];
	
	TCnsRegRetResult* ptRet = (TCnsRegRetResult*)abyBuf;
	TCnsRegInfo* ptFindRet = (TCnsRegInfo*)(abyBuf+sizeof(TCnsRegRetResult));
	ptFindRet->Clear();
	ptRet->m_emReson = byReason;	
	
	memcpy(abyBuf+sizeof(TCnsRegRetResult), ptRegInfo, sizeof(TCnsRegInfo));

	NotifyMsgToStack(evtp_ums_unreg_ret, abyBuf, sizeof(abyBuf), *ptHandle);	
	return TRUE;
}


BOOL32 CTpRegOprdb::ProcessARQEvent(CTpMsg *const ptMsg)
{
	TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
	TTPAlias* ptDstAlias = (TTPAlias*)(ptMsg->GetBody()+sizeof(TUmsHandle));
	u8 abyBuf[sizeof(TCnsRegRetResult)+sizeof(TCnsRegInfo)];
	
	TCnsRegRetResult* ptRet = (TCnsRegRetResult*)abyBuf;
	TCnsRegInfo* ptDstReg = (TCnsRegInfo*)(abyBuf+sizeof(TCnsRegRetResult));
	ptDstReg->Clear();
	
	ptDstReg->m_tCsnNodeInfo.m_atAlias[0] = *ptDstAlias;
	
	ptRet->m_emReson = tp_CnsRegRet_Unknow;
	do 
	{
		
		if (tp_Alias_Unknow == ptDstAlias->m_byType)
		{
			break;
		}
		
		//通过IP查询   add by gaoyong
		if (tp_Alias_IP == ptDstAlias->m_byType)
		{
			u32_ip dwQueryIp= inet_addr(ptDstAlias->m_abyAlias);
			BOOL32 bIsFind = FALSE;
			TRegData* pRegData = m_regDataMem.First();
			while (NULL != pRegData)
			{
				for (u16 wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
				{
					if (0 == pRegData->m_atCalledAddr[wIndex].m_dwIP)
					{
						continue;
					}
					if (dwQueryIp == pRegData->m_atCalledAddr[wIndex].m_dwIP)
					{
						bIsFind = TRUE;
						break;
					}
				}
				if (bIsFind)
				{
					break;
				}
				else
				{
					pRegData = m_regDataMem.Next();
				}				
			}
			if (bIsFind)
			{
				ptRet->m_emReson = tp_CnsRegRet_Success;
				ptDstReg->m_dwCallType = pRegData->m_dwCallType;
				ptDstReg->m_tCsnNodeInfo.m_atCalledAddr[0] = pRegData->m_atCalledAddr[0];
				memcpy(ptDstReg->m_tCsnNodeInfo.m_aCallId, pRegData->m_aCallId, TP_MAX_NUM_CALLID);
				//量子终端的ID
				ptDstReg->m_tCsnNodeInfo.m_dwSelfQtID = pRegData->m_dwSelfQtID;
                break;
			}
			else
			{
				ptRet->m_emReson = tp_CnsRegRet_NotFind;
				break;
			}
		}
		
		TAliasID* pdwAliasID = m_aliasTre.Find(ptDstAlias->m_abyAlias);
		
		if (NULL != pdwAliasID)
		{
			// 			EmTpAliasType tType = m_regDataMem.FindByID(pdwAliasID->m_dwParentID)->m_alias.FindByID(pdwAliasID->m_dwAliasID)->m_byType;
			// 			if (ptDstAlias->m_byType == tType)
			// 			{
			ptRet->m_emReson = tp_CnsRegRet_Success;
			ptDstReg->m_dwCallType = m_regDataMem.FindByID(pdwAliasID->m_dwParentID)->m_dwCallType;
			ptDstReg->m_tCsnNodeInfo.m_atCalledAddr[0] = m_regDataMem.FindByID(pdwAliasID->m_dwParentID)->m_atCalledAddr[0];
			memcpy(ptDstReg->m_tCsnNodeInfo.m_aCallId, m_regDataMem.FindByID(pdwAliasID->m_dwParentID)->m_aCallId, TP_MAX_NUM_CALLID);
			ptDstReg->m_tCsnNodeInfo.m_dwSelfQtID = m_regDataMem.FindByID(pdwAliasID->m_dwParentID)->m_dwSelfQtID;
			// 			}
			// 			else
			// 			{
			// 				ptRet->m_emReson = tp_CnsRegRet_NotFind;
			// 			}
		}
		else
		{
			ptRet->m_emReson = tp_CnsRegRet_NotFind;
		}
		
	} while (0);
	
	NotifyMsgToStack(evtp_ums_arq_ret, abyBuf, sizeof(abyBuf), *ptHandle);	
	
	return TRUE;
}
/*====================================================================
函数名    ：ProcessRegInfoEvent
功能      ：处理查询注册信息消息
算法实现  ：
参数说明  ：[I]ptMsg 消息
返回值说明：
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          创建
====================================================================*/
BOOL32 CTpRegOprdb::ProcessRegInfoEvent(CTpMsg* const ptMsg)
{
	TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
	u8* pData = ptMsg->GetBody()+sizeof(TUmsHandle);
	u16 wSize = ptMsg->GetBodyLen() - sizeof(TUmsHandle);

	s32 nAppID = 0;
	EmGetRegInfoType emType = emGetRegInfoType_ALL;
	TP_SAFE_CAST( nAppID, pData );
	TP_SAFE_CAST( emType, pData + sizeof(s32) );
	u16 wLeftSize = wSize-sizeof(s32)-sizeof(EmGetRegInfoType);

	//B1 版本的请求
	if (0 == wLeftSize)
	{
		ReqRegInfoFromOldVer(ptHandle, nAppID, emType);

		return TRUE;
	}
	else
	{
		BOOL32 bFlag = TRUE;
		do 
		{

			s8	aCallId[TP_MAX_NUM_CALLID];
			memcpy(aCallId, pData+sizeof(s32)+sizeof(EmGetRegInfoType), TP_MAX_NUM_CALLID);
			
			bFlag = ReqRegInfoFromNewVer(ptHandle, nAppID, emType, aCallId);

		} while (FALSE);

		if (!bFlag)
		{
			TReqRegInfoEx tRegInfoEx;
			tRegInfoEx.m_wTotalPackNum = 0;
			tRegInfoEx.m_wPackSeq = 0;
			tRegInfoEx.m_tRegType = emType;
			tRegInfoEx.m_emSelfType = emTPEndpointTypeUMS;

			u8 abBuf[sizeof(s32)+sizeof(TReqRegInfoEx)] = {0};
			memcpy(abBuf, &nAppID, sizeof(s32));
			memcpy(abBuf+sizeof(s32), &tRegInfoEx, sizeof(TReqRegInfoEx));
			NotifyMsgToStack(evtp_ums_reg_info_rspEx, abBuf, sizeof(abBuf), *ptHandle);
			
			return FALSE;
		}

		return TRUE;
	}
}

void CTpRegOprdb::ReqRegInfoFromOldVer(TUmsHandle* ptHandle, s32 nAppID, const EmGetRegInfoType& emReqType)
{
	u16 wCurPackSeq = 1;
	u8 abyUmsBuf[sizeof(s32)+sizeof(TReqRegInfo)];
	u8 abyCnsBuf[sizeof(s32)+sizeof(TReqRegInfo)];
	memcpy(abyCnsBuf, &nAppID, sizeof(s32));
	memcpy(abyUmsBuf, &nAppID, sizeof(s32));
	TReqRegInfo tUmsRegInfo, tCnsRegInfo;
	tUmsRegInfo.m_emSelfType = emTPEndpointTypeUMS;
	tUmsRegInfo.m_tRegType = emReqType;
	tUmsRegInfo.m_wTotalPackNum = GetPackNums(emReqType);
	
	if (0 == tUmsRegInfo.m_wTotalPackNum)
	{
		tUmsRegInfo.m_wPackSeq = 0;
		memcpy(abyUmsBuf+sizeof(s32), &tUmsRegInfo, sizeof(TReqRegInfo));
		NotifyMsgToStack(evtp_ums_reg_info_rsp, abyUmsBuf, sizeof(abyUmsBuf), *ptHandle);
		return ;
	}
	
	tCnsRegInfo.m_emSelfType = emTPEndpointTypeCNS;
	tCnsRegInfo.m_tRegType = emReqType;
	tCnsRegInfo.m_wTotalPackNum = GetPackNums(emReqType);
	
	TRegData* ptRegData = m_regDataMem.First();
	while (NULL != ptRegData)
	{
		if (emTPEndpointTypeCNS == ptRegData->m_emSelfType && 
		   (emReqType == emGetRegInfoType_CNS || emReqType == emGetRegInfoType_ALL))
		{
			TTPAlias* ptCnsAlias = ptRegData->m_alias.First();
			while (NULL != ptCnsAlias)
			{
				tCnsRegInfo.m_atAlias[tCnsRegInfo.m_wAliasNum].m_byType = ptCnsAlias->m_byType;
				memcpy(tCnsRegInfo.m_atAlias[tCnsRegInfo.m_wAliasNum].m_abyAlias, ptCnsAlias->m_abyAlias, TP_MAX_ALIAS_LEN);
				++(tCnsRegInfo.m_wAliasNum);
				if (TP_REGNAME_SIZE == tCnsRegInfo.m_wAliasNum)
				{
					tCnsRegInfo.m_wPackSeq = wCurPackSeq;
					memcpy(abyCnsBuf+sizeof(s32), &tCnsRegInfo, sizeof(tCnsRegInfo));
					NotifyMsgToStack(evtp_ums_reg_info_rsp, abyCnsBuf, sizeof(abyCnsBuf), *ptHandle);
					tCnsRegInfo.m_wAliasNum = 0;
					++wCurPackSeq;
				}
				ptCnsAlias = ptRegData->m_alias.Next();
			}
		}
		else
		{
			if (emTPEndpointTypeUMS == ptRegData->m_emSelfType && 
				(emReqType == emGetRegInfoType_UMS || emReqType == emGetRegInfoType_ALL))
			{
				TTPAlias* ptUmsAlias = ptRegData->m_alias.First();
				while (NULL != ptUmsAlias)
				{
					tUmsRegInfo.m_atAlias[tUmsRegInfo.m_wAliasNum].m_byType = ptUmsAlias->m_byType;
					memcpy(tUmsRegInfo.m_atAlias[tUmsRegInfo.m_wAliasNum].m_abyAlias, ptUmsAlias->m_abyAlias, TP_MAX_ALIAS_LEN);
					++(tUmsRegInfo.m_wAliasNum);
					if (TP_REGNAME_SIZE == tUmsRegInfo.m_wAliasNum)
					{
						tUmsRegInfo.m_wPackSeq = wCurPackSeq;
						memcpy(abyUmsBuf+sizeof(s32), &tUmsRegInfo, sizeof(tUmsRegInfo));
						NotifyMsgToStack(evtp_ums_reg_info_rsp, abyUmsBuf, sizeof(abyUmsBuf), *ptHandle);
						tUmsRegInfo.m_wAliasNum = 0;
						++wCurPackSeq;
					}
					
					ptUmsAlias = ptRegData->m_alias.Next();
				}
			}
		}
		
		ptRegData = m_regDataMem.Next();
	}
	
	if (0 != tCnsRegInfo.m_wAliasNum)
	{
		tCnsRegInfo.m_wPackSeq = wCurPackSeq;
		memcpy(abyCnsBuf+sizeof(s32), &tCnsRegInfo, sizeof(tCnsRegInfo));
		NotifyMsgToStack(evtp_ums_reg_info_rsp, abyCnsBuf, sizeof(abyCnsBuf), *ptHandle);
		++wCurPackSeq;
	}
	
	if (0 != tUmsRegInfo.m_wAliasNum)
	{
		tUmsRegInfo.m_wPackSeq = wCurPackSeq;
		memcpy(abyUmsBuf+sizeof(s32), &tUmsRegInfo, sizeof(tUmsRegInfo));
		NotifyMsgToStack(evtp_ums_reg_info_rsp, abyUmsBuf, sizeof(abyUmsBuf), *ptHandle);
	}
}	

BOOL32 CTpRegOprdb::ReqRegInfoFromNewVer(TUmsHandle* ptHandle, s32 nAppID, const EmGetRegInfoType& emReqType, s8* pCallID)
{
	u32* pdwID = m_regTre.Find(pCallID);
	if (NULL != pdwID)
	{
		TRegData* ptRegData = m_regDataMem.FindByID(*pdwID);
		if (NULL == ptRegData)
		{
			ObjError(("[ReqRegInfoFromNewVer] Find exist obj Failed. EP CallID:\n"));
			printcallid((u8*)pCallID, TP_MAX_NUM_CALLID);
			return FALSE;
		}
	}
	else
	{
		ObjError(("[ReqRegInfoFromNewVer] Not find the callid. CallID:\n"));
		printcallid((u8*)pCallID, TP_MAX_NUM_CALLID);

		return FALSE;
	}

	u16 wTotalPack = GetPackNumsEx(emReqType);
	if (0 == wTotalPack)
	{
		ObjHint(("ReqRegInfoFromNewVer Total Pack is 0.\n"));
		return FALSE;
	}

	u8 abUmsBuf[sizeof(TUmsRegData)*TP_UMS_MAX_REG_DATA] = {0};
	u8 abCnsBuf[sizeof(TCnsRegData)*TP_CNS_MAX_REG_DATA] = {0};

 	TReqRegInfoEx tUmsRegInfoEx, tCnsRegInfoEx;
	tUmsRegInfoEx.m_tRegType = emReqType;
	tUmsRegInfoEx.m_emSelfType = emTPEndpointTypeUMS;
	tUmsRegInfoEx.m_wTotalPackNum = wTotalPack;

	tCnsRegInfoEx.m_tRegType = emReqType;
	tCnsRegInfoEx.m_emSelfType = emTPEndpointTypeCNS;
	tCnsRegInfoEx.m_wTotalPackNum = wTotalPack;

	u16 wCurPackSeq = 1;
 	TRegData* ptRegData = m_regDataMem.First();
 	while (NULL != ptRegData)
 	{
 		if (emTPEndpointTypeCNS == ptRegData->m_emSelfType && 
 		    (emReqType == emGetRegInfoType_CNS || emReqType == emGetRegInfoType_ALL))
		{
			TCnsRegData tCnsData;
			tCnsData.m_wAliasNum = 0;
 
 			memcpy(tCnsData.m_aCompileTm, ptRegData->m_aCompileTm, TP_MAX_VERSION_LEN);
 			memcpy(tCnsData.m_aSelfVer, ptRegData->m_aSelfVer, TP_MAX_VERSION_LEN);
			for (u8 byIndex = 0; byIndex < TP_MAX_NUM_CONTACT_ADDR; ++byIndex)
			{
				tCnsData.m_atCalledAddr[byIndex] = ptRegData->m_atCalledAddr[byIndex];
			}
			tCnsData.m_dwCallType = ptRegData->m_dwCallType;
			tCnsData.m_dwExpires  = ptRegData->m_dwExpires;
			tCnsData.m_dwSelfAddr = ptRegData->m_dwSelfAddr;

			TTPAlias* ptCnsAlias = ptRegData->m_alias.First();
			while (NULL != ptCnsAlias)
			{
				tCnsData.m_atAlias[tCnsData.m_wAliasNum].m_byType = ptCnsAlias->m_byType;
				
				//memcpy(tCnsData.m_atAlias[tCnsData.m_wAliasNum].m_abyAlias, ptCnsAlias->m_abyAlias, TP_MAX_ALIAS_LEN);
				//上面这种拷贝，限定了字节数，如果有汉字，易出错
				memcpy(tCnsData.m_atAlias[tCnsData.m_wAliasNum].m_abyAlias, ptCnsAlias->m_abyAlias, sizeof(ptCnsAlias->m_abyAlias));
				
				++(tCnsData.m_wAliasNum);
				if (tCnsData.m_wAliasNum >= CNS_MAX_ALIAS_SIZE)
				{
					break;
				}
				ptCnsAlias = ptRegData->m_alias.Next();
			}

			memcpy(abCnsBuf+sizeof(TCnsRegData)*tCnsRegInfoEx.m_wDataNum, &tCnsData, sizeof(TCnsRegData));
			++(tCnsRegInfoEx.m_wDataNum);

			if (tCnsRegInfoEx.m_wDataNum == TP_CNS_MAX_REG_DATA)
			{
				tCnsRegInfoEx.m_wPackSeq = wCurPackSeq;
				CTpMsg cMsg;
				cMsg.SetEvent(evtp_ums_reg_info_rspEx);
				cMsg.SetBody(ptHandle, sizeof(TUmsHandle));
				cMsg.CatBody(&nAppID, sizeof(s32));
				cMsg.CatBody(&tCnsRegInfoEx, sizeof(TReqRegInfoEx));
				cMsg.CatBody(abCnsBuf, sizeof(abCnsBuf));
				cMsg.Post(UMS_STACK_APP_INST);

				tCnsRegInfoEx.m_wDataNum  = 0;
				++wCurPackSeq;
			}
 		}
		else
		{
			if (emTPEndpointTypeUMS == ptRegData->m_emSelfType && 
				(emReqType == emGetRegInfoType_UMS || emReqType == emGetRegInfoType_ALL))
			{
				TUmsRegData tUmsData;
				tUmsData.m_wAliasNum = 0;
				
				memcpy(tUmsData.m_aCompileTm, ptRegData->m_aCompileTm, TP_MAX_VERSION_LEN);
				memcpy(tUmsData.m_aSelfVer, ptRegData->m_aSelfVer, TP_MAX_VERSION_LEN);
				for (u8 byIndex = 0; byIndex < TP_MAX_NUM_CONTACT_ADDR; ++byIndex)
				{
					tUmsData.m_atCalledAddr[byIndex] = ptRegData->m_atCalledAddr[byIndex];
				}
				tUmsData.m_dwCallType = ptRegData->m_dwCallType;
				tUmsData.m_dwExpires  = ptRegData->m_dwExpires;
				tUmsData.m_dwSelfAddr = ptRegData->m_dwSelfAddr;
				
				TTPAlias* ptCnsAlias = ptRegData->m_alias.First();
				while (NULL != ptCnsAlias)
				{
					tUmsData.m_atAlias[tUmsData.m_wAliasNum].m_byType = ptCnsAlias->m_byType;
					memcpy(tUmsData.m_atAlias[tUmsData.m_wAliasNum].m_abyAlias, ptCnsAlias->m_abyAlias, TP_MAX_ALIAS_LEN);
					++(tUmsData.m_wAliasNum);
					if (tUmsData.m_wAliasNum >= UMS_MAX_ALIAS_SIZE)
					{
						break;
					}
					ptCnsAlias = ptRegData->m_alias.Next();
				}
				
				memcpy(abUmsBuf+sizeof(TUmsRegData)*tUmsRegInfoEx.m_wDataNum, &tUmsData, sizeof(TUmsRegData));
				++(tUmsRegInfoEx.m_wDataNum);
				
				if (tUmsRegInfoEx.m_wDataNum == TP_UMS_MAX_REG_DATA)
				{
					tUmsRegInfoEx.m_wPackSeq = wCurPackSeq;
					CTpMsg cMsg;
					cMsg.SetEvent(evtp_ums_reg_info_rspEx);
					cMsg.SetBody(ptHandle, sizeof(TUmsHandle));
					cMsg.CatBody(&nAppID, sizeof(s32));
					cMsg.CatBody(&tUmsRegInfoEx, sizeof(TReqRegInfoEx));
					cMsg.CatBody(abUmsBuf, sizeof(abUmsBuf));
					cMsg.Post(UMS_STACK_APP_INST);
					
					tUmsRegInfoEx.m_wDataNum  = 0;
					++wCurPackSeq;
				}
			}
		}
		
		ptRegData = m_regDataMem.Next();
	}

	if (0 != tCnsRegInfoEx.m_wDataNum)
	{
		tCnsRegInfoEx.m_wPackSeq = wCurPackSeq;
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_ums_reg_info_rspEx);
		cMsg.SetBody(ptHandle, sizeof(TUmsHandle));
		cMsg.CatBody(&nAppID, sizeof(s32));
		cMsg.CatBody(&tCnsRegInfoEx, sizeof(TReqRegInfoEx));
		cMsg.CatBody(abCnsBuf, sizeof(TCnsRegData)*tCnsRegInfoEx.m_wDataNum);
		cMsg.Post(UMS_STACK_APP_INST);

		++wCurPackSeq;
	}

	if (0 != tUmsRegInfoEx.m_wDataNum)
	{
		tUmsRegInfoEx.m_wPackSeq = wCurPackSeq;
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_ums_reg_info_rspEx);
		cMsg.SetBody(ptHandle, sizeof(TUmsHandle));
		cMsg.CatBody(&nAppID, sizeof(s32));
		cMsg.CatBody(&tUmsRegInfoEx, sizeof(TReqRegInfoEx));
		cMsg.CatBody(abUmsBuf, sizeof(TUmsRegData)*tUmsRegInfoEx.m_wDataNum);
		cMsg.Post(UMS_STACK_APP_INST);
	}

 	return TRUE;
}

/*====================================================================
函数名    ：GetTimerObj
功能      ：查找定时器ID对应的对象ID
算法实现  ：
参数说明  ：[I]dwTimer 定时器ID
返回值说明：对象的存储ID，不存在返回0
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          创建
====================================================================*/
u32 CTpRegOprdb::GetTimerObj(u32 dwTimer)
{
	TRegData* pRegData = m_regDataMem.First();
	while (NULL != pRegData)
	{
		if (pRegData->m_dwTimerID == dwTimer)
		{
			return m_regDataMem.GetCurID();
		}
		pRegData = m_regDataMem.Next();
	}

	return 0;
}

/*====================================================================
函数名    ：DelAlias
功能      ：删除别名
算法实现  ：
参数说明  ：[I]dwID ID
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          创建
====================================================================*/
void CTpRegOprdb::DelAlias(u32 dwID)
{
	switch (m_regDataMem.FindByID(dwID)->m_emSelfType)
	{
		case emTPEndpointTypeCNS:	
			{
				m_wCnsNums -= (u16)m_regDataMem.FindByID(dwID)->m_alias.Size();
				--m_wCnsNodeNums;
				break;
			}

		case emTPEndpointTypeUMS:	
			{
				m_wUmsNums -= (u16)m_regDataMem.FindByID(dwID)->m_alias.Size();
				--m_wUmsNodeNums;
				break;
			}
	}

	TTPAlias* pAlias = m_regDataMem.FindByID(dwID)->m_alias.First();
	while (NULL != pAlias)
	{
		m_aliasTre.Erase(pAlias->m_abyAlias);
		pAlias = m_regDataMem.FindByID(dwID)->m_alias.Next();
	}
}


/*====================================================================
函数名    ：RegTimeOut
功能      ：注册超时
算法实现  ：
参数说明  ：[I]dwTime 超时时间
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          修改
====================================================================*/
void CTpRegOprdb::RegTimeOut(u32 dwTime)
{
	u32 dwID = GetTimerObj(dwTime);
	if (0 != dwID)
	{
		++(m_regDataMem.FindByID(dwID)->m_dwTryTimes);
		if (m_regDataMem.FindByID(dwID)->m_dwTryTimes >= 3)
		{
			ObjHint(("Reg Timeout. callID:"));
			if (IsCanPrint(m_wLogModuleId, enLogHint))
			{
				printcallid((u8*)m_regDataMem.FindByID(dwID)->m_aCallId, TP_MAX_NUM_CALLID);
			}
			
			TTPAlias* pAliase = m_regDataMem.FindByID(dwID)->m_alias.First();
			u32 dwAliasNum = 1;
			while (NULL != pAliase)
			{
				ObjHint(("  [alias %d]:%s\n", dwAliasNum++, pAliase->m_abyAlias));
				pAliase = m_regDataMem.FindByID(dwID)->m_alias.Next();
			}
			
			for (u32 wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
			{
				if (m_regDataMem.FindByID(dwID)->m_atCalledAddr[wIndex].m_dwIP == 0)
				{
					break;
				}
				ObjHint(("  addr %d:"ADDRPORT_FORMAT"\n", wIndex+1, 
						 ADDRPORT(m_regDataMem.FindByID(dwID)->m_atCalledAddr[wIndex].m_dwIP,
						          m_regDataMem.FindByID(dwID)->m_atCalledAddr[wIndex].m_wPort)));
			}
			
			
			TTpTimer* ptTimer = (TTpTimer*)m_regDataMem.FindByID(dwID)->m_dwTimerID;
			m_pcTimerMgr->DeleteTimer(ptTimer);
			
			DelAlias(dwID);
			m_regTre.Erase(m_regDataMem.FindByID(dwID)->m_aCallId);
			m_regDataMem.EraseByID(dwID);			
		}
		else
		{
			TTpTimer* ptTimer = (TTpTimer*)m_regDataMem.FindByID(dwID)->m_dwTimerID;
			if (ptTimer)
			{
				m_pcTimerMgr->UpdateTimer(ptTimer);
			}
		}		
	}
}


/*====================================================================
函数名    ：AddReg
功能      ：添加注册
算法实现  ：
参数说明  ：[I]ptRegInfo 注册信息
返回值说明：返回注册结果
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          修改
====================================================================*/
EmTpCnsRegUms CTpRegOprdb::AddReg(TCnsRegInfo* ptRegInfo)
{
	if (ptRegInfo->m_tCsnNodeInfo.m_wAliasNum <= 0)
	{
		return tp_CnsRegRet_MsgError;
	}

	TRegData* ptRegData = NULL;
	u32* pdwID = m_regTre.Find(ptRegInfo->m_tCsnNodeInfo.m_aCallId);
	if (NULL != pdwID)
	{
		ptRegData = m_regDataMem.FindByID(*pdwID);
		if (NULL == ptRegData)
		{
			ObjError(("[CTpRegOprdb::AddReg]m_regDataMem.FindByID. Find exist obj Failed. EP CallID:\n"));
			printcallid((u8*)ptRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
			return tp_CnsRegRet_SysError;
		}

		ptRegData->Update(ptRegInfo->m_tCsnNodeInfo);
		if (IsRepeatExceptSelfNode(ptRegInfo, *pdwID))
		{
			DelReg(ptRegInfo);
			return tp_CnsRegRet_AliasRepeat;
		}

		if (TP_UMS_MAX_REGALIAS <= m_aliasTre.GetTotalNodes() + ptRegInfo->m_tCsnNodeInfo.m_wAliasNum)
		{
			DelReg(ptRegInfo);
			return tp_CnsRegRet_MaxAliasNum;
		}
		
		UpdateAlias(ptRegInfo, *pdwID);
		ptRegData->m_dwTryTimes = 0;
		TTpTimer* ptTimer = (TTpTimer*)ptRegData->m_dwTimerID;
		m_pcTimerMgr->UpdateTimer(ptTimer);

 		return tp_CnsRegRet_Success;
	}
	else
	{
		DelExistReg(ptRegInfo);

		if (TP_UMS_MAX_REGNUM <= m_regTre.GetTotalNodes())
		{
			return tp_CnsRegRet_MaxRegNum;
		}
		
		if (IsRepeat(ptRegInfo))
		{
			return tp_CnsRegRet_AliasRepeat;
		}
		
		if (ptRegInfo->m_tCsnNodeInfo.m_dwExpires == 0)
		{
			ptRegInfo->m_tCsnNodeInfo.m_dwExpires = TP_KEEPALIVE_TIME;
		}
		
		u32 dwID = m_regDataMem.Add();
		if (0 == dwID)
		{
			ObjError(("[CTpRegOprdb::AddReg]m_regDataMem.Add Failed. EP CallID:\n"));
			printcallid((u8*)ptRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
			return tp_CnsRegRet_SysError;
		}

		ptRegData = m_regDataMem.FindByID(dwID);
		if (NULL == ptRegData)
		{
			ObjError(("[CTpRegOprdb::AddReg]m_regDataMem.FindByID. Find new obj Failed. EP CallID:\n"));
			printcallid((u8*)ptRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
			return tp_CnsRegRet_SysError;
		}

		ptRegData->SetValue(*ptRegInfo);
		TTpTimer* ptTimer = m_pcTimerMgr->AddTimer(ptRegInfo->m_tCsnNodeInfo.m_dwExpires, PreRegTimerCB, this);
		
		if (NULL == ptTimer)
		{
			ObjError(("m_pcTimerMgr.AddTimer Failed. EP CallID:\n"));
			printcallid((u8*)ptRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
			return tp_CnsRegRet_SysError;
		}
		
		AddAlias(ptRegInfo, dwID);
		ptRegData->m_dwTryTimes = 0;
		ptRegData->m_dwTimerID = u32(ptTimer);

		m_regTre.Insert(ptRegData->m_aCallId, dwID);
		
		return tp_CnsRegRet_Success;
	}

	return tp_CnsRegRet_Unknow;
}

/*====================================================================
函数名    ：DelReg
功能      ：删除注册
算法实现  ：
参数说明  ：[I]ptRegInfo 注册信息
返回值说明：返回解除注册的结果
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          修改
====================================================================*/
EmTpCnsRegUms CTpRegOprdb::DelReg(TCnsRegInfo* ptRegInfo)
{
	u32* pdwID = m_regTre.Find(ptRegInfo->m_tCsnNodeInfo.m_aCallId);
	if (NULL != pdwID)
	{
		u32 dwTemp = *pdwID;
		TRegData* ptRegData = m_regDataMem.FindByID(dwTemp);
		if (NULL == ptRegData)
		{
			ObjError(("[CTpRegOprdb::DelReg]m_regDataMem.FindByID. Find obj Failed. EP CallID:\n"));
			printcallid((u8*)ptRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
			return tp_CnsRegRet_SysError;
		}

		ObjHint(("DelReg  CallID:"));
		printcallid((u8*)ptRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);

		ptRegData->GetValue(*ptRegInfo);
		TTpTimer* ptTimer = (TTpTimer*)ptRegData->m_dwTimerID;
		m_pcTimerMgr->DeleteTimer(ptTimer);

		switch (ptRegData->m_emSelfType)
		{
		case emTPEndpointTypeCNS:		
			{
				m_wCnsNums -= (u16)ptRegData->m_alias.Size();
				--m_wCnsNodeNums;
				break;
			}
			
		case emTPEndpointTypeUMS:		
			{
				m_wUmsNums -= (u16)ptRegData->m_alias.Size();
				--m_wUmsNodeNums;
				break;
			}
		}

		//删除节点
		TTPAlias* pAlias = ptRegData->m_alias.First();
		while (NULL != pAlias)
		{
			m_aliasTre.Erase(pAlias->m_abyAlias);
			pAlias = ptRegData->m_alias.Next();
		}

		m_regTre.Erase(ptRegInfo->m_tCsnNodeInfo.m_aCallId);
		m_regDataMem.EraseByID(dwTemp);

		return tp_CnsRegRet_Success;
	}
	else
	{
		return tp_CnsRegRet_UnReg;
	}
}

/*====================================================================
函数名    ：AddAlias
功能      ：添加别名
算法实现  ：
参数说明  ：[I]ptRegInfo 注册信息 [I]dwParentID ID
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
BOOL32 CTpRegOprdb::AddAlias(TCnsRegInfo* ptRegInfo, u32 dwParentID)
{
	TRegData* ptRegData = m_regDataMem.FindByID(dwParentID);
	if (NULL == ptRegData)
	{
		return FALSE;
	}

	switch (ptRegData->m_emSelfType)
	{
	case emTPEndpointTypeCNS:		
		{
			m_wCnsNums += ptRegInfo->m_tCsnNodeInfo.m_wAliasNum;
			++m_wCnsNodeNums;
			break;
		}

		
	case emTPEndpointTypeUMS:		
		{
			m_wUmsNums += ptRegInfo->m_tCsnNodeInfo.m_wAliasNum;
			++m_wUmsNodeNums;
			break;
		}
	}

	TAliasID tAliasID;
	tAliasID.m_dwParentID = dwParentID;

	for (u16 wIndex = 0; wIndex < ptRegInfo->m_tCsnNodeInfo.m_wAliasNum; ++wIndex)
	{
		tAliasID.m_dwAliasID = ptRegData->m_alias.Add();
		if (0 == tAliasID.m_dwAliasID)
		{
			return FALSE;
		}
		else
		{
			*(ptRegData->m_alias.FindByID(tAliasID.m_dwAliasID)) = ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex];
			m_aliasTre.Insert(ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex].m_abyAlias, tAliasID);
		}
	}

	return TRUE;
}

/*====================================================================
函数名    ：UpdateAlias
功能      ：更新别名别名
算法实现  ：
参数说明  ：[I]ptRegInfo 注册信息 [O]dwParentID ID
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
BOOL32 CTpRegOprdb::UpdateAlias(TCnsRegInfo* ptRegInfo, u32 dwParentID)
{
	TRegData* ptRegData = m_regDataMem.FindByID(dwParentID);
	if (NULL == ptRegData)
	{
		return FALSE;
	}

	switch (ptRegData->m_emSelfType)
	{
	case emTPEndpointTypeCNS:		
		{
			m_wCnsNums -= (u16)ptRegData->m_alias.Size();
			break;
		}
									
	case emTPEndpointTypeUMS:		
		{
			m_wUmsNums -= (u16)ptRegData->m_alias.Size();
			break;
		}
	}

	TTPAlias* pTalias = ptRegData->m_alias.First();
	while (NULL != pTalias)
	{
		m_aliasTre.Erase(pTalias->m_abyAlias);
		pTalias = ptRegData->m_alias.Next();
	}

	ptRegData->m_alias.Clear();
	TAliasID tAliasID;
	tAliasID.m_dwParentID = dwParentID;
	
	switch (ptRegData->m_emSelfType)
	{
	case emTPEndpointTypeCNS:		
		{
			m_wCnsNums += ptRegInfo->m_tCsnNodeInfo.m_wAliasNum;
			break;
		}
		
	case emTPEndpointTypeUMS:		
		{
			m_wUmsNums += ptRegInfo->m_tCsnNodeInfo.m_wAliasNum;
			break;
		}
	}

	for (u16 wIndex = 0; wIndex < ptRegInfo->m_tCsnNodeInfo.m_wAliasNum; ++wIndex)
	{
		tAliasID.m_dwAliasID = ptRegData->m_alias.Add();
		if (0 == tAliasID.m_dwAliasID)
		{
			return FALSE;
		}
		else
		{
			*(ptRegData->m_alias.FindByID(tAliasID.m_dwAliasID)) = ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex];
			m_aliasTre.Insert(ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex].m_abyAlias, tAliasID);
		}
	}

	return TRUE;
}


/*====================================================================
函数名    ：IsRepeat
功能      ：查找是否存在重复的别名
算法实现  ：
参数说明  ：[I]ptRegInfo 注册信息
返回值说明：存在返回TRUE，否则会回FALSE
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
BOOL32 CTpRegOprdb::IsRepeat(TCnsRegInfo* ptRegInfo)
{
	BOOL32 			bRet = FALSE;
	TTPAlias		atAlias[TP_MAX_ALIAS_NUM];
	u16				wAliasNum = 0;

	memset( atAlias, 0, sizeof(TTPAlias)*TP_MAX_ALIAS_NUM );
	
	TAliasID* ptAliasID;
	for (u16 wIndex = 0; wIndex < ptRegInfo->m_tCsnNodeInfo.m_wAliasNum; ++wIndex)
	{
		ptAliasID = m_aliasTre.Find(ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex].m_abyAlias);
		if (NULL != ptAliasID)
		{
			bRet = TRUE;
			memcpy( &atAlias[wAliasNum++], &(ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex]), sizeof(TTPAlias));
		}
	}
	
	if (bRet)
	{
		ptRegInfo->m_tCsnNodeInfo.m_wAliasNum = wAliasNum;
		memcpy( ptRegInfo->m_tCsnNodeInfo.m_atAlias, atAlias, sizeof( TTPAlias )*wAliasNum );
	}
	
	return bRet;
}

/*====================================================================
函数名    ：IsRepeatExceptSelfNode
功能      ：查找除本身以外是否存在重复的别名
算法实现  ：
参数说明  ：[I]ptRegInfo 注册信息 [I]dwID 上一级ID
返回值说明：存在返回TRUE，否则会回FALSE
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
BOOL32 CTpRegOprdb::IsRepeatExceptSelfNode(TCnsRegInfo* ptRegInfo, u32 dwID)
{
	BOOL32 			bRet = FALSE;
	TTPAlias		atAlias[TP_MAX_ALIAS_NUM];
	u16				wAliasNum = 0;
	
	memset( atAlias, 0, sizeof(TTPAlias)*TP_MAX_ALIAS_NUM );
	
	TAliasID* ptAliasID;
	for (u16 wIndex = 0; wIndex < ptRegInfo->m_tCsnNodeInfo.m_wAliasNum; ++wIndex)
	{
		ptAliasID = m_aliasTre.Find(ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex].m_abyAlias);
		if (NULL != ptAliasID)
		{
			if (dwID != ptAliasID->m_dwParentID)
			{
				bRet = TRUE;
				memcpy( &atAlias[wAliasNum++], &(ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex]), sizeof(TTPAlias));
			}
		}
	}
	
	if ( bRet )
	{
		ptRegInfo->m_tCsnNodeInfo.m_wAliasNum = wAliasNum;
		memcpy(ptRegInfo->m_tCsnNodeInfo.m_atAlias, atAlias, sizeof( TTPAlias )*wAliasNum);
	}
	
	return bRet;
}

/*====================================================================
函数名    ：SendRegInfoToUpgradTool
功能      ：发送消息给升级工具
算法实现  ：
参数说明  ：
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          修改
====================================================================*/
void CTpRegOprdb::SendRegInfoToUpgradTool(CTpMsg *const ptMsg)
{
	u16				wIndex = 0;
	TRegInfoArray	tRegInfoArray;
	TRegInfo*		ptRegTmp = tRegInfoArray.m_atRegInfo;
	TRegData*		pRegData = m_regDataMem.First();

	while (NULL != pRegData)
	{
		ptRegTmp->m_dwIpAddr	= pRegData->m_dwSelfAddr;
		ptRegTmp->m_emType		= pRegData->m_emSelfType;
		strncpy(ptRegTmp->m_acVersion, pRegData->m_aSelfVer, sizeof(ptRegTmp->m_acVersion));
		ptRegTmp->m_acVersion[TP_MAX_VERSION_LEN] = '\0';
		strncpy(ptRegTmp->m_acCompileTm, pRegData->m_aCompileTm, sizeof(ptRegTmp->m_acCompileTm));
		ptRegTmp->m_acCompileTm[TP_MAX_VERSION_LEN] = '\0';

		++wIndex;
		if (MAX_SEND_REGINFO_NUM_ONE_TIME == wIndex)
		{
			tRegInfoArray.m_wRegInfoNum = MAX_SEND_REGINFO_NUM_ONE_TIME;
			::OspPost(ptMsg->GetSrcIId(), evtp_ums_RegSer_Rsp_RegInfo, &tRegInfoArray, sizeof(TRegInfoArray), ptMsg->GetSrcNode());		
			memset(&tRegInfoArray, 0, sizeof(TRegInfoArray));
			wIndex = 0;
			ptRegTmp = tRegInfoArray.m_atRegInfo;
		}
		else
		{
			++ptRegTmp;
		}

		pRegData = m_regDataMem.Next();
	}
				
	tRegInfoArray.m_wRegInfoNum = wIndex;			
	::OspPost(ptMsg->GetSrcIId(), evtp_ums_RegSer_Rsp_RegInfo, &tRegInfoArray, sizeof(TRegInfoArray), ptMsg->GetSrcNode());
				
	return ;
}

u16 CTpRegOprdb::GetPackNumsEx(const EmGetRegInfoType& emType) const
{
	u16 wRes = 0;
	switch (emType)
	{
	case emGetRegInfoType_CNS:		
		{
			if (m_wCnsNodeNums % TP_CNS_MAX_REG_DATA == 0)
			{
				return m_wCnsNodeNums / TP_CNS_MAX_REG_DATA;
			}
			else
			{
				return m_wCnsNodeNums / TP_CNS_MAX_REG_DATA + 1;
			}
		}
		
	case emGetRegInfoType_UMS:		
		{
			if (m_wUmsNodeNums % TP_UMS_MAX_REG_DATA == 0)
			{
				return m_wUmsNodeNums / TP_UMS_MAX_REG_DATA;
			}
			else
			{
				return m_wUmsNodeNums / TP_UMS_MAX_REG_DATA + 1;
			}
		}
		
	case emGetRegInfoType_ALL:
		{
			if (m_wCnsNodeNums % TP_CNS_MAX_REG_DATA == 0)
			{
				wRes += m_wCnsNodeNums / TP_CNS_MAX_REG_DATA;
			}
			else
			{
				wRes += m_wCnsNodeNums / TP_CNS_MAX_REG_DATA + 1;
			}
			
			if (m_wUmsNodeNums % TP_UMS_MAX_REG_DATA == 0)
			{
				wRes += m_wUmsNodeNums / TP_UMS_MAX_REG_DATA;
			}
			else
			{
				wRes += m_wUmsNodeNums / TP_UMS_MAX_REG_DATA + 1;
			}
			
			return wRes;
		}
	}
	
	return 0;	
}

u16 CTpRegOprdb::GetPackNums(const EmGetRegInfoType& emType) const
{
	u16 wRes = 0;
	switch (emType)
	{
	case emGetRegInfoType_CNS:		
		{
			if (m_wCnsNums % TP_REGNAME_SIZE == 0)
			{
				return m_wCnsNums / TP_REGNAME_SIZE;
			}
			else
			{
				return m_wCnsNums / TP_REGNAME_SIZE + 1;
			}
		}
		
	case emGetRegInfoType_UMS:		
		{
			if (m_wUmsNums % TP_REGNAME_SIZE == 0)
			{
				return m_wUmsNums / TP_REGNAME_SIZE;
			}
			else
			{
				return m_wUmsNums / TP_REGNAME_SIZE + 1;
			}
		}
		
	case emGetRegInfoType_ALL:
		{
			if (m_wCnsNums % TP_REGNAME_SIZE == 0)
			{
				wRes += m_wCnsNums / TP_REGNAME_SIZE;
			}
			else
			{
				wRes += m_wCnsNums / TP_REGNAME_SIZE + 1;
			}
			
			if (m_wUmsNums % TP_REGNAME_SIZE == 0)
			{
				wRes += m_wUmsNums / TP_REGNAME_SIZE;
			}
			else
			{
				wRes += m_wUmsNums / TP_REGNAME_SIZE + 1;
			}
			
			return wRes;
		}
	}
	
	return 0;
}

void CTpRegOprdb::DelExistReg(TCnsRegInfo* ptRegInfo)
{
	if (NULL == ptRegInfo || 0 == ptRegInfo->m_tCsnNodeInfo.m_wAliasNum)
	{
		return ;
	}

	TAliasID* ptAliasID = m_aliasTre.Find(ptRegInfo->m_tCsnNodeInfo.m_atAlias[0].m_abyAlias);
	if (NULL == ptAliasID)
	{
		return ;
	}

	u32 dwID = ptAliasID->m_dwParentID;
	TRegData* ptData = m_regDataMem.FindByID(dwID);
	if (NULL == ptData)
	{
		return ;
	}

	BOOL bFlag = FALSE;
	if (ptData->m_dwSelfAddr   == ptRegInfo->m_tCsnNodeInfo.m_dwSelfAddr &&
		ptData->m_emSelfType   == ptRegInfo->m_tCsnNodeInfo.m_emSelfType &&
		ptData->m_alias.Size() == ptRegInfo->m_tCsnNodeInfo.m_wAliasNum)
	{
		for (u16 wIndex = 0; wIndex < ptRegInfo->m_tCsnNodeInfo.m_wAliasNum; ++wIndex)
		{
			TTPAlias* ptAlias = ptData->m_alias.First();
			while (NULL != ptAlias)
			{
				if (*ptAlias == ptRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex])
				{
					bFlag = TRUE;
					break;
				}
				else
				{
					bFlag = FALSE;
				}
				ptAlias = ptData->m_alias.Next();
			}

			if (!bFlag)
			{
				break;
			}
		}
	}

	//存在相同的注册
	if (bFlag)
	{
		u32* pdwID = m_regTre.Find(ptData->m_aCallId);
		if (NULL != pdwID)
		{

			u32 dwTemp = *pdwID;
			
			TTpTimer* ptTimer = (TTpTimer*)ptData->m_dwTimerID;
			m_pcTimerMgr->DeleteTimer(ptTimer);
			
			switch (ptData->m_emSelfType)
			{
			case emTPEndpointTypeCNS:		
				{
					m_wCnsNums -= (u16)ptData->m_alias.Size();
					--m_wCnsNodeNums;
					break;
				}
				
			case emTPEndpointTypeUMS:		
				{
					m_wUmsNums -= (u16)ptData->m_alias.Size();
					--m_wUmsNodeNums;
					break;
				}
			}
			
			//删除节点
			TTPAlias* ptAlias = ptData->m_alias.First();
			while (NULL != ptAlias)
			{
				m_aliasTre.Erase(ptAlias->m_abyAlias);
				ptAlias = ptData->m_alias.Next();
			}
			
			m_regTre.Erase(ptData->m_aCallId);
			m_regDataMem.EraseByID(dwTemp);
		}
	}
}


enum tp_ums_reg_dump
{
	dump_show_reg,
	dump_show_timer,
	dump_show_node,
	dump_show_meminfo,
	dump_req_reg_info,
	dump_add_reg,
};

API void showreg()
{
	OspInstDump(AID_UMSDB_APP, 1, dump_show_reg);	
}

API void meminfo()
{
	OspInstDump(AID_UMSDB_APP, 1, dump_show_meminfo);
}

API void showtime()
{
	OspInstDump(AID_UMSDB_APP, 1, dump_show_timer);	
}

API void shownode()
{
	OspInstDump(AID_UMSDB_APP, 1, dump_show_node);	
}

API void reqreginfo()
{
	TUmsHandle tHandle;
	s32 nAppID = 1;
	EmGetRegInfoType emType = emGetRegInfoType_ALL;
	
	u8 callID[] = "336363323233632333623333633323336";
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ums_reg_info_req);
	cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
	cMsg.CatBody(&nAppID, sizeof(s32));
	cMsg.CatBody(&emType, sizeof(EmGetRegInfoType));
	cMsg.CatBody(callID, sizeof(callID));
	cMsg.Post(MAKEIID(AID_UMSDB_APP, 1));
}

API void addreg()
{
	TUmsHandle tHandle;
	TCnsRegInfo tInfo;
	u8 callID[] = "336363323233632333623333633323336";
	memcpy(tInfo.m_tCsnNodeInfo.m_aCallId, callID, 128);
	tInfo.m_tCsnNodeInfo.m_atAlias[0].SetAlias("test1");
	tInfo.m_tCsnNodeInfo.m_atAlias[1].SetAlias("test2");
	tInfo.m_tCsnNodeInfo.m_atAlias[2].SetAlias("test3");
	tInfo.m_tCsnNodeInfo.m_atAlias[3].SetAlias("test4");
	tInfo.m_tCsnNodeInfo.m_atAlias[4].SetAlias("test5");
	tInfo.m_tCsnNodeInfo.m_atAlias[5].SetAlias("test6");
	tInfo.m_tCsnNodeInfo.m_atAlias[6].SetAlias("test7");
	tInfo.m_tCsnNodeInfo.m_atAlias[7].SetAlias("test8");
	tInfo.m_tCsnNodeInfo.m_atAlias[8].SetAlias("test9");
	tInfo.m_tCsnNodeInfo.m_atAlias[9].SetAlias("test10");
	tInfo.m_tCsnNodeInfo.m_atAlias[10].SetAlias("test11");
	tInfo.m_tCsnNodeInfo.m_atAlias[11].SetAlias("test12");
	tInfo.m_tCsnNodeInfo.m_wAliasNum = 12;
	tInfo.m_tCsnNodeInfo.m_emSelfType = emTPEndpointTypeCNS;
	tInfo.m_tCsnNodeInfo.m_dwExpires = 1111111111;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ums_reg_req);
	cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
	cMsg.CatBody(&tInfo, sizeof(TCnsRegInfo));
	cMsg.Post(MAKEIID(AID_UMSDB_APP, 1));
}

/*====================================================================
函数名    ：InstanceDump
功能      ：
算法实现  ：
参数说明  ：
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          修改
====================================================================*/
void CTpRegOprdb::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_reg:		ShowAllReg();
							break;

	case dump_show_timer:	ShowTimer();
							break;
	case dump_show_node:	ShowNode();
							break;
	case dump_show_meminfo:	ShowRegMem();
							break;

	case dump_req_reg_info:	//GetRegInfo();
							break;

	case dump_add_reg:		//AddRegInfo();
							break;

	default:				break;
	}
}

void CTpRegOprdb::ShowRegMem()
{
	msgprint("TotalSize:%d, UseSize:%d\n", m_regDataMem.TotalSize(), m_regDataMem.UseSize());
}

void CTpRegOprdb::GetRegInfo()
{
	TUmsHandle tHandle;
	s32 nAppID = 1;
	EmGetRegInfoType emType = emGetRegInfoType_ALL;
	
	u8 callID[] = "336363323233632333623333633323336";
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ums_reg_info_req);
	cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
	cMsg.CatBody(&nAppID, sizeof(s32));
	cMsg.CatBody(&emType, sizeof(EmGetRegInfoType));
	cMsg.CatBody(callID, sizeof(callID));

	MessageProc(&cMsg);
}

void CTpRegOprdb::AddRegInfo()
{
	TUmsHandle tHandle;
	TCnsRegInfo tInfo;
	u8 callID[] = "336363323233632333623333633323336";
	memcpy(tInfo.m_tCsnNodeInfo.m_aCallId, callID, 128);
	tInfo.m_tCsnNodeInfo.m_atAlias[0].SetAlias("test1");
	tInfo.m_tCsnNodeInfo.m_atAlias[1].SetAlias("test2");
	tInfo.m_tCsnNodeInfo.m_atAlias[2].SetAlias("test3");
	tInfo.m_tCsnNodeInfo.m_atAlias[3].SetAlias("test4");
	tInfo.m_tCsnNodeInfo.m_atAlias[4].SetAlias("test5");
	tInfo.m_tCsnNodeInfo.m_atAlias[5].SetAlias("test6");
	tInfo.m_tCsnNodeInfo.m_atAlias[6].SetAlias("test7");
	tInfo.m_tCsnNodeInfo.m_atAlias[7].SetAlias("test8");
	tInfo.m_tCsnNodeInfo.m_atAlias[8].SetAlias("test9");
	tInfo.m_tCsnNodeInfo.m_atAlias[9].SetAlias("test10");
	tInfo.m_tCsnNodeInfo.m_atAlias[10].SetAlias("test11");
	tInfo.m_tCsnNodeInfo.m_atAlias[11].SetAlias("test12");
	tInfo.m_tCsnNodeInfo.m_wAliasNum = 12;
	tInfo.m_tCsnNodeInfo.m_emSelfType = emTPEndpointTypeCNS;
	tInfo.m_tCsnNodeInfo.m_dwExpires = 1111111111;

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ums_reg_req);
	cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
	cMsg.CatBody(&tInfo, sizeof(TCnsRegInfo));

	MessageProc(&cMsg);
}

/*====================================================================
函数名    ：ShowAllReg
功能      ：显示注册信息
算法实现  ：
参数说明  ：无
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          创建
====================================================================*/
void CTpRegOprdb::ShowAllReg()
{
	msgprint("------------- all reg begin---------------\n");
	msgprint("reg num:%d\n", m_regTre.GetTotalNodes());
	msgprint("csn alias num:%d\n", m_wCnsNums);
	msgprint("ums alias num:%d\n", m_wUmsNums);

	u16 wNum = 1;
	TRegData* pRegData = m_regDataMem.First();
	while (NULL != pRegData)
	{
		msgprint("  EP No.%d\n", wNum++);
		msgprint("  EP CallID:");
		printcallid((u8*)pRegData->m_aCallId, TP_MAX_NUM_CALLID);
		msgprint("  KeepLiveTime:%d\n", pRegData->m_dwExpires);
		msgprint("  TimesID:0x%x\n", pRegData->m_dwTimerID);

		//输出别名
		u16 wAliasNum = 1;
		TTPAlias* pAlias = pRegData->m_alias.First();
		while (NULL != pAlias)
		{

			s8 * pzAliasUTF8 = NULL;
	
			utf8_to_gb2312((s8 *)pAlias->m_abyAlias, &pzAliasUTF8);
			msgprint("  [alias %d]:%s\n", wAliasNum++, pzAliasUTF8);
			pAlias = pRegData->m_alias.Next();
			free(pzAliasUTF8);
		}

		for (u16 wIndex = 0; wIndex<TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
		{
			if (pRegData->m_atCalledAddr[wIndex].m_dwIP == 0)
			{
				break;
			}
			msgprint("  addr %d:"ADDRPORT_FORMAT"\n", wIndex + 1, 
					 ADDRPORT(pRegData->m_atCalledAddr[wIndex].m_dwIP,
							 pRegData->m_atCalledAddr[wIndex].m_wPort));
		}
		
		msgprint("  LocalInfo TpEndpointType:%d, LocalIP:"TPIPFORMAT", EndPointVersion:%s, EPCompileTm:%s\n", 
			pRegData->m_emSelfType, 
			Tpu32ToIP(pRegData->m_dwSelfAddr), 
			pRegData->m_aSelfVer,
			pRegData->m_aCompileTm);

		msgprint("  QTID:%d\n", pRegData->m_dwSelfQtID);

		msgprint("  \n");

		pRegData = m_regDataMem.Next();
	}
	
	msgprint("------------- all reg end-----------------\n");
}


void CTpRegOprdb::ShowTimer()
{
	msgprint("m_pcTimerMgr:0x%x\n", m_pcTimerMgr);
	if (NULL != m_pcTimerMgr)
	{
		u32 nowtime;
		s32 total, used;
		m_pcTimerMgr->GetStatis(&nowtime, &total, &used);
		msgprint("nowtime:%d, total:%d, used:%d\n", nowtime, total, used);

		msgprint("m_ptUsedList:0x%x\n", m_pcTimerMgr->m_ptUsedList);
		msgprint("m_ptFreeListFirst:0x%x\n", m_pcTimerMgr->m_ptFreeListFirst);
		msgprint("m_ptFreeListLast:0x%x\n", m_pcTimerMgr->m_ptFreeListLast);
		msgprint("m_patTimer:0x%x\n", m_pcTimerMgr->m_patTimer);
	}
}

/*====================================================================
函数名    ：ShowNode
功能      ：
算法实现  ：
参数说明  ：无
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/10  1.0   许成          创建
====================================================================*/
void CTpRegOprdb::ShowNode()
{
	msgprint("alias list  total:%d\n", m_aliasTre.GetTotalNodes());
	msgprint("reg vector  total:%d\n", m_regTre.GetTotalNodes());
}
