#include "umsreg.h"
#include "innereventregsrv.h"
#include "innereventumscall.h"
#include "eventoutsipadapter.h"
#include "umsinnerstruct.h"
#include "umsstackinterface.h"
#include "umsobject.h"
#include "umsconfinst.h"
#include "umsconfig.h"
#include "eqpinterface.h"
#include "umsxmltype.h"

#define ALL_REG   em_AllGroup
CUmsRegMgr::CUmsRegMgr(CTpObject* pcObject)
:CTpHandler(pcObject)
,m_ptCurAdapt(NULL)
{

	memset(&m_tRegCfg,0,sizeof(m_tRegCfg));
	memset(&m_tGkRegCfg, 0, sizeof(m_tGkRegCfg));
	
	u16 wIndex = 0;
	for(wIndex=0; wIndex<TP_TEMPGROUP_MAXNUM; wIndex++)
	{
		m_wSipAliasNum[wIndex] = 0;
		m_wGKAliasNum[wIndex] = 0;
		memset(m_atAlias[wIndex],0,TP_CONFTEMPGROUP_MAXNUM*sizeof(TTPAlias));
	}

	for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; wIndex++)
	{
		m_atRegAdapt[wIndex].Clear();
	}

	ClearSipRegState();
	ClearGkRegState();

	//临时模板初始
	for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		m_adwTempSipRegHandle[wIndex] = INVALID_STACK_HANDLE;
		m_adwTempGkRegHandle[wIndex] = INVALID_STACK_HANDLE;
		m_aemTempGkRegState[wIndex] = em_un_reg;
		m_aemTempSipRegState[wIndex] = em_un_reg;
	}
}

CUmsRegMgr::~CUmsRegMgr()
{

}

BOOL32 CUmsRegMgr::Handler( CTpMsg *const ptMsg )
{
	u8* pData = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();

	switch (ptMsg->GetEvent())
	{
	case evtp_ums_reg_req:
		EventReg(pData, wDataSize);
		break;
	case evtp_ums_unreg_req:
		EventUnReg(pData, wDataSize);
		break;
	case ev_ums_GetRegInfo_Req:
		EventReqRegInfo(ptMsg);
		break;
	case evtp_ums_reg_ret://注册成功
		EventRegRet(pData, wDataSize);
		break;
	case evtp_ums_unreg_ret://sip注册失败
		EventUnRegRet(pData, wDataSize);
		break;
	case evtp_ums_323_unreg_ret://gk注册失败
		Event323UnRegRet(pData, wDataSize);
		break;
	case ev_UmsGetRegInfo_Rsp:
		EventReqRegInfoRet(pData, wDataSize);
		break;
	case ev_UmsGetRegInfo_UmsRspEx:
		EventUmsRegInfoRet(pData, wDataSize);
		break;
	case ev_UmsGetRegInfo_CnsRspEx:
		EventCnsRegInfoRet(pData, wDataSize);
		break;
	case ev_UmsGetGkRegInfo_MtRsp:
		EventMtRegInfoRet(pData, wDataSize);
		break;
	case ev_UmsGetGkRegInfo_McuRsp:
		EventMcuRegInfoRet(pData, wDataSize);
		break;
	case ev_register_handle_info:
		EventHandleInfo(pData, wDataSize);
		break;
	case evtp_RRQ_Timer:
		{
			EventSipRegTimer(pData, wDataSize);
		}
		break;

	case evtp_GK_RRQ_Timer:
		{
			EventGkRegTimer(pData, wDataSize);
		}
		break;

	case evtp_UmsAdapterReg_Notify:
		EventAdapterReg(pData, wDataSize);
		break;
	case evtp_UmsAdapterUnReg_Notify:
		EventAdapterUnReg(pData, wDataSize);
		break;
	case evtp_GK_Cfg_Update:
		EventUpdateGkCfg(pData, wDataSize);
		break;
	case evtp_Sip_Cfg_Update:
		EventUpdateSipCfg(pData, wDataSize);
		break;

	default:
		return FALSE;
	}
	return TRUE;
}

void CUmsRegMgr::EventReqRegInfo(CTpMsg* const ptMsg)
{
	EmGetRegInfoType* ptType = (EmGetRegInfoType*)ptMsg->GetBody();
	TUmsHandle tHandle;
	if (NULL != m_ptCurAdapt)
	{
		tHandle.m_dwAdapteID = m_ptCurAdapt->m_tEqp.m_dwEqpNode;
	}
	
	u32 dwSipHandle = 0;
	u32 dwGkhandle = 0;

	for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		if (m_bSipUnRegPack[wIndex] && m_dwStackHandle[wIndex])
		{
			dwSipHandle = m_dwStackHandle[wIndex];
		}
		
		if (m_bGkUnRegPack[wIndex] && m_dwGkRegHandle[wIndex])
		{
			dwGkhandle = m_dwGkRegHandle[wIndex];
		}
	}

	UmsReqRegInfo(tHandle, m_tRegCfg, *ptType, dwSipHandle, dwGkhandle);
}

void CUmsRegMgr::EventReqRegInfoRet(u8* pData, u16 wDataSize)
{
	
	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(ev_ums_GetRegInfo_Rsp, pData + sizeof(TUmsHandle), 
								 wDataSize - sizeof(TUmsHandle));
}

void CUmsRegMgr::EventUmsRegInfoRet(u8* pData, u16 wDataSize)
{
	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(ev_ums_GetRegInfo_UmsRspEx, pData + sizeof(TUmsHandle), 
								 wDataSize - sizeof(TUmsHandle));
}

void CUmsRegMgr::EventCnsRegInfoRet(u8* pData, u16 wDataSize)
{
	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(ev_ums_GetRegInfo_CnsRspEx, pData + sizeof(TUmsHandle), 
								 wDataSize - sizeof(TUmsHandle));
}

void CUmsRegMgr::EventMtRegInfoRet(u8* pData, u16 wDataSize)
{
	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(ev_ums_GkRegInfo_MtRsp, pData + sizeof(TUmsHandle), 
								 wDataSize - sizeof(TUmsHandle));
}

void CUmsRegMgr::EventMcuRegInfoRet(u8* pData, u16 wDataSize)
{
	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(ev_ums_GkRegInfo_McuRsp, pData + sizeof(TUmsHandle), 
								 wDataSize - sizeof(TUmsHandle));
}

void CUmsRegMgr::EventReg(u8* pData, u16 wDataSize)
{	
	u16 wCurIndex = 0; //记录当前处理的包序号
	u16 wAliasNum = 0;

	EmRegType emRegType = *(EmRegType*)pData;
	pData = pData+sizeof(emRegType);

	EmRegGroupNum emRegGroupNum = *(EmRegGroupNum*)pData;
	switch(emRegGroupNum)
	{
	case em_FirstGroup:
		{
			wCurIndex = 0;
		}
		break;
	case em_SecondGroup:
		{
			wCurIndex = 1;
		}
		break;
	case em_ThirdGroup:
		{
			wCurIndex = 2;
		}
		break;
	case em_FourthGroup:
		{
			wCurIndex = 3;
		}
		break;
	default:
		{
			msgprint("[EventReg] Error for EmGroupNum = %d\n",emRegGroupNum);
			return;
		}
		break;
	}

	u8* pAlias = NULL;
	switch (emRegType)
	{
	case em_Sip_reg_type:
		{
			memset(&m_tRegCfg, 0, sizeof(m_tRegCfg));
			TTPSipRegistrarCfg tSipCfg = *(TTPSipRegistrarCfg*)(pData+sizeof(EmRegGroupNum));
			
			m_tRegCfg.bUsed = tSipCfg.bUsed;
			m_tRegCfg.dwRegIP = tSipCfg.dwRegIP;
			m_tRegCfg.wRegPort = tSipCfg.wRegPort;
			m_tRegCfg.achRegDomain[0] = '\0';
			m_tRegCfg.wExpire = tSipCfg.wExpire;
			
			m_tRegCfg.achHostDomain[0] = '\0';
			snprintf(m_tRegCfg.achCompileTm, sizeof(m_tRegCfg.achCompileTm),"%s,%s",__DATE__,__TIME__);
			m_tRegCfg.achCompileTm[TP_MAX_VERSION_LEN] = '\0';

		    m_tRegCfg.m_dwQTId = tSipCfg.m_dwQtID;

			m_wSipAliasNum[wCurIndex] = *(u16*)(pData+sizeof(EmRegGroupNum)+ sizeof(TTPSipRegistrarCfg));
			if (m_wSipAliasNum[wCurIndex] > 0)
			{
				pAlias = pData+sizeof(EmRegGroupNum)+ sizeof(TTPSipRegistrarCfg)+sizeof(u16);
			}
			wAliasNum = localmin(TP_CONFTEMPGROUP_MAXNUM, m_wSipAliasNum[wCurIndex]);
			break;
		}
 
	case em_Gk_reg_type:
		{
			memset(&m_tGkRegCfg, 0, sizeof(m_tGkRegCfg));
			TTPGKCfg tGkRegCfg = *(TTPGKCfg*)(pData+sizeof(EmRegGroupNum));
			m_tGkRegCfg.m_bUsed = tGkRegCfg.bUsed;
			m_tGkRegCfg.m_tGKAddress.m_dwIP = tGkRegCfg.dwGKIP;
			m_tGkRegCfg.m_nTimeToLive = tGkRegCfg.wExpire;
            m_tGkRegCfg.m_dwQTId = tGkRegCfg.m_dwQtID;
			m_wGKAliasNum[wCurIndex] = *(u16*)(pData+sizeof(EmRegGroupNum)+ sizeof(TTPGKCfg));
			if (m_wGKAliasNum[wCurIndex] > 0)
			{
				pAlias = pData+sizeof(EmRegGroupNum)+ sizeof(TTPGKCfg)+sizeof(u16);
			}
			wAliasNum = localmin(TP_CONFTEMPGROUP_MAXNUM, m_wGKAliasNum[wCurIndex]);
			break;
		}
	}

	// 先清空注册名字
	memset(m_atAlias[wCurIndex],0,TP_CONFTEMPGROUP_MAXNUM*sizeof(TTPAlias));

	for (u16 wIndex = 0; wIndex < wAliasNum; ++wIndex)
	{
		m_atAlias[wCurIndex][wIndex] = *(TTPAlias*)pAlias;
		pAlias += sizeof(TTPAlias);
	}
	
	TUmsStackCallCfg tCallStackCfg;
	umsGetUmsStackCfg(tCallStackCfg);

	umsGetLocalUmsIP(m_tRegCfg.m_atAdaptAddr[0].m_dwIP);
	m_tRegCfg.m_atAdaptAddr[0].m_wPort = tCallStackCfg.m_wCallingPort;

	m_tGkRegCfg.m_tLocalAddress.m_dwIP = m_tRegCfg.m_atAdaptAddr[0].m_dwIP;
	m_tGkRegCfg.m_tLocalAddress.m_wPort = tCallStackCfg.m_wCallingPort;

	switch (emRegType)
	{
	case em_Sip_reg_type:	
		{
			if (!m_tRegCfg.bUsed)
			{
				return ;
			}
		}
		break;

	case em_Gk_reg_type:
		{
			if (!m_tGkRegCfg.m_bUsed)
			{
				return ;
			}
		}
		break;
	}

	Reg(wCurIndex, emRegType);
}

void CUmsRegMgr::Reg(u16 wCurIndex, EmRegType emRegType)
{
	if (NULL == m_ptCurAdapt)
	{
		MdlHint(Ums_Mdl_Call, ("Reg adapter unreg, emRegType:%d\n", emRegType));
		return ;
	}

	if (0 == m_ptCurAdapt->m_tEqp.m_dwEqpNode)
	{
		switch (emRegType)
		{
		case em_Gk_reg_type:
			{
				if (em_AllGroup == wCurIndex)
				{
					for (u16 wGroupIndex = 0; wGroupIndex < TP_TEMPGROUP_MAXNUM; ++wGroupIndex)
					{
						m_bGkUnRegPack[wGroupIndex]  = FALSE;
					}
				}
				else
				{
					m_bGkUnRegPack[wCurIndex] = FALSE;
				}
				
				if (m_tGkRegCfg.m_nTimeToLive > 0)
				{
					KillTimer(evtp_GK_RRQ_Timer);
					SetTimer(evtp_GK_RRQ_Timer, (m_tGkRegCfg.m_nTimeToLive + UMS_REQ_Timer) * 1000 );
				}
			}
			break;

		case em_Sip_reg_type:
			{
				if (em_AllGroup == wCurIndex)
				{
					for (u16 wGroupIndex = 0; wGroupIndex < TP_TEMPGROUP_MAXNUM; ++wGroupIndex)
					{
						m_bSipUnRegPack[wGroupIndex]  = FALSE;
					}
				}
				else
				{
					m_bSipUnRegPack[wCurIndex] = FALSE;
				}
				
				if (m_tRegCfg.wExpire > 0)
				{
					KillTimer(evtp_RRQ_Timer);
					SetTimer(evtp_RRQ_Timer, (m_tRegCfg.wExpire + UMS_REQ_Timer) * 1000);
				}
			}
			break;
		default:
			MdlHint(Ums_Mdl_Call, ("Reg type is invalid!!! type:%d.\n", emRegType));
			return;
		}

		MdlHint(Ums_Mdl_Call, ("Reg adapter id:%d, emRegType:%d\n", m_ptCurAdapt->m_tEqp.m_dwEqpNode, emRegType));
		
		return ;
	}

	u32 dwHandle = 0;
	do 
	{
		if(ALL_REG != wCurIndex)
		{
			break;
		}

		u16 wIndex = 0;
		for(; wIndex< TP_TEMPGROUP_MAXNUM; wIndex++)
		{
			dwHandle = 0;
			TUmsHandle tHandle;
			MakeAdapterHandle(tHandle, wIndex, emRegType);
			
			if (emRegType == em_Sip_reg_type)
			{
				dwHandle = m_dwStackHandle[wIndex];
			}
			else
			{
				dwHandle = m_dwGkRegHandle[wIndex];
			}
			MdlHint(Ums_Mdl_Call, ("Reg handle:0x%x, sipAliasNum:%d, gkAliasNum:%d, emRegType:%d\n", dwHandle, m_wSipAliasNum[wIndex], m_wGKAliasNum[wIndex], emRegType));

			if (em_Sip_reg_type == emRegType)
			{
				if (m_wSipAliasNum[wIndex]>0)
				{
					UmsRegister(tHandle, m_tRegCfg, m_atAlias[wIndex], m_wSipAliasNum[wIndex]);
				}
				else
				{
					if (dwHandle > 0)
					{
						UmsUnregister(tHandle, emRegType);
					}
				}
			}
			else// em_Gk_reg_type
			{
				if (m_wGKAliasNum[wIndex]>0)
				{
					for (u16 wAliasNums = 0; wAliasNums < m_wGKAliasNum[wIndex]; ++wAliasNums)
					{
						m_tGkRegCfg.m_tAlias[wAliasNums] = m_atAlias[wIndex][wAliasNums];
					}
					UmsGkRegister(tHandle, m_tGkRegCfg, m_wGKAliasNum[wIndex]);
				}
				else
				{
					if (dwHandle > 0)
					{
						UmsUnregister(tHandle, emRegType);
					}
				}
			}

		}

		return;

	} while (0);

	//句柄按序号写入
	TUmsHandle tHandle;
	MakeAdapterHandle(tHandle, wCurIndex, emRegType);

	if (emRegType == em_Sip_reg_type)
	{
		dwHandle = m_dwStackHandle[wCurIndex];
	}
	else
	{
		dwHandle = m_dwGkRegHandle[wCurIndex];
	}
	
	MdlHint(Ums_Mdl_Call, ("Reg handle:0x%x, sipAliasNum:%d, gkAliasNum:%d, emRegType:%d\n", 
		dwHandle, m_wSipAliasNum[wCurIndex], m_wGKAliasNum[wCurIndex], emRegType));

	if (em_Sip_reg_type == emRegType)
	{
		if (m_wSipAliasNum[wCurIndex]>0)
		{
			UmsRegister(tHandle, m_tRegCfg, m_atAlias[wCurIndex], m_wSipAliasNum[wCurIndex]);
		}
		else
		{
			if (dwHandle > 0)
			{
				UmsUnregister(tHandle, emRegType);
			}
		}
	}
	else// em_Gk_reg_type
	{
		if (m_wGKAliasNum[wCurIndex]>0)
		{
			for (u16 wAliasNums = 0; wAliasNums < m_wGKAliasNum[wCurIndex]; ++wAliasNums)
			{
				m_tGkRegCfg.m_tAlias[wAliasNums] = m_atAlias[wCurIndex][wAliasNums];
			}
			UmsGkRegister(tHandle, m_tGkRegCfg, m_wGKAliasNum[wCurIndex]);
		}
		else
		{
			if (dwHandle > 0)
			{
				UmsUnregister(tHandle, emRegType);
			}
		}
	}
}

void CUmsRegMgr::UnReg(EmRegType emRegType, const EmRegGroupNum& emGroupNum /* = em_AllGroup */, BOOL32 bFromServer /* = FALSE */)
{
	u32* pdwHandle = NULL;
	TUmsHandle tHandle;
	if (em_AllGroup == emGroupNum)
	{
		for(u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; wIndex++)
		{
			tHandle.Clear();
			MakeAdapterHandle(tHandle, wIndex, emRegType);
			if (em_Sip_reg_type == emRegType)
			{
				pdwHandle = &(m_dwStackHandle[wIndex]);
				m_bSipUnRegPack[wIndex] = TRUE;
				m_bIsSipRegged[wIndex] = FALSE;
				ClearRegResultInfo(wIndex);
			}
			else
			{
				pdwHandle = &(m_dwGkRegHandle[wIndex]);
				m_bGkUnRegPack[wIndex] = TRUE;
				m_bisGkRegged[wIndex] = FALSE;
				ClearGkRegResultInfo(wIndex);
			}

			if (bFromServer)
			{// server来取消注册，清空注册别名信息
				if (em_Sip_reg_type == emRegType)
				{
					m_wSipAliasNum[wIndex] = 0;
				}
				else
				{
					m_wGKAliasNum[wIndex] = 0;
				}
				memset(m_atAlias[wIndex],0,TP_CONFTEMPGROUP_MAXNUM*sizeof(TTPAlias));
			}

			MdlHint(Ums_Mdl_Call, ("UnReg handle:0x%x, RegType:%d, FromServer:%d.\n",  *pdwHandle, emRegType, bFromServer));
			if (0 != *pdwHandle)
			{
				UmsUnregister(tHandle, emRegType);
				*pdwHandle = 0;
			}
		}
	}
	else
	{	
		tHandle.Clear();
		MakeAdapterHandle(tHandle, emGroupNum, emRegType);
		if (em_Sip_reg_type == emRegType)
		{
			pdwHandle = &(m_dwStackHandle[emGroupNum]);
			m_bSipUnRegPack[emGroupNum] = TRUE;
			m_bIsSipRegged[emGroupNum] = FALSE;
			ClearRegResultInfo(emGroupNum);
		}
		else
		{
			pdwHandle = &(m_dwGkRegHandle[emGroupNum]);
			m_bGkUnRegPack[emGroupNum] = TRUE;
			m_bisGkRegged[emGroupNum] = FALSE;
			ClearGkRegResultInfo(emGroupNum);
		}

		if (bFromServer)
		{// server来取消注册，清空注册别名信息
			if (em_Sip_reg_type == emRegType)
			{
				m_wSipAliasNum[emGroupNum] = 0;
			}
			else
			{
				m_wGKAliasNum[emGroupNum] = 0;
			}
			memset(m_atAlias[emGroupNum],0,TP_CONFTEMPGROUP_MAXNUM*sizeof(TTPAlias));
		}

		MdlHint(Ums_Mdl_Call, ("UnReg handle:0x%x, RegType:%d, FromServer:%d.\n",  *pdwHandle, emRegType, bFromServer));
		if (0 != *pdwHandle)
		{
			UmsUnregister(tHandle, emRegType);
			*pdwHandle = 0;
		}
	}	
}

void CUmsRegMgr::EventUnReg(u8* pData, u16 wDataSize)
{
	EmRegType emRegType = *(EmRegType*)pData;
	EmRegGroupNum emGroupNum = *(EmRegGroupNum*)(pData+sizeof(EmRegType));

	UnReg(emRegType, emGroupNum, TRUE);
	
	return;
}


void CUmsRegMgr::EventRegRet(u8* pData, u16 wDataSize)
{
	TUmsHandle* ptHandle = (TUmsHandle*)pData;
	TCnsRegRetResult* ptRetInfo = (TCnsRegRetResult*)(pData + sizeof(TUmsHandle));
	EmRegType emRegType = em_Sip_reg_type;
	switch(ptRetInfo->m_emRegType)
	{
	case em_sip_reg:
		{
			emRegType = em_Sip_reg_type;
			break;
		}

	case em_323_reg:
		{
			emRegType = em_Gk_reg_type;
			break;
		}
	}
	
	//通过应用句柄获得协议栈句柄对应的位置
	u16 wEpID = ptHandle->GetEpID();
	if (wEpID >= CONFTEMP_HANDLE_START)
	{//临时模板注册
		TempRegSuccess(pData, wDataSize);
		return;
	}

	if (wEpID-emRegType>=TP_TEMPGROUP_MAXNUM)
	{
		MdlError(Ums_Mdl_Call, ("EventRegRet index is error! index:%d, handle:0x%x, ret:%d-%s, regType:%d.\n"
			, wEpID-emRegType, ptHandle->handPaCall, TpEnumIdString(EmTpCnsRegUms, ptRetInfo->m_emReson),  emRegType));
		return ;
	}

	switch (emRegType)
	{
	case em_Sip_reg_type:
		{
			if (0 == m_dwStackHandle[wEpID-emRegType] || 
				m_dwStackHandle[wEpID-emRegType] != ptHandle->handPaCall)
			{
				MdlError(Ums_Mdl_Call, ("EventRegRet handle is not matched! old handle:0x%x, new handle:0x%x, ret:%d-%s, regType:%d.\n"
						, m_dwStackHandle[wEpID-emRegType], ptHandle->handPaCall, TpEnumIdString(EmTpCnsRegUms, ptRetInfo->m_emReson),  emRegType));
				return ;
			}

			m_bSipUnRegPack[wEpID - emRegType] = TRUE;
			m_bIsSipRegged[wEpID - emRegType] = TRUE;
			ClearRegResultInfo(wEpID - emRegType);

			BOOL32 bRes = TRUE;
			BOOL32 bTempRes = TRUE;
			u16 wIndex = 0;
			for ( wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
			{
				if (!m_bSipUnRegPack[wIndex])
				{
					bRes = FALSE;
					break;
				}
			}
			for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
			{
				if (em_reg_failed == m_aemTempSipRegState[wIndex])
				{
					bTempRes = FALSE;
					break;
				}
			}
			if (bRes && bTempRes)
			{
				KillTimer(evtp_RRQ_Timer);
			}
		}
		break;

	case em_Gk_reg_type:
		{
			if (0 == m_dwGkRegHandle[wEpID-emRegType] || 
				m_dwGkRegHandle[wEpID-emRegType] != ptHandle->handPaCall)
			{
				MdlError(Ums_Mdl_Call, ("EventRegRet handle is not matched! old handle:0x%x, new handle:0x%x, ret:%d-%s, regType:%d.\n"
					, m_dwGkRegHandle[wEpID-emRegType], ptHandle->handPaCall, TpEnumIdString(EmTpCnsRegUms, ptRetInfo->m_emReson),  emRegType));
				return ;
			}

			m_bGkUnRegPack[wEpID-emRegType] = TRUE;
			m_bisGkRegged[wEpID-emRegType] = TRUE;
			ClearGkRegResultInfo(wEpID-emRegType);

			BOOL32 bRes = TRUE;
			u16 wIndex = 0;
			for (wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
			{
				if (!m_bGkUnRegPack[wIndex])
				{
					bRes = FALSE;
					break;
				}
			}
			BOOL32 bTempRes = TRUE;
			for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
			{
				if (em_reg_failed == m_aemTempGkRegState[wIndex])
				{
					bTempRes = FALSE;
					break;
				}
			}
			if (bRes && bTempRes)
			{
				KillTimer(evtp_GK_RRQ_Timer);
			}
		}
		break;
	}

	u8 abBuf[sizeof(EmRegType) + sizeof(TCnsRegRetResult) + sizeof(u16)] = {0};

	u16 wGroupIndex = wEpID-emRegType;
	memcpy(abBuf, &emRegType, sizeof(EmRegType));
	memcpy(abBuf + sizeof(EmRegType), ptRetInfo, sizeof(TCnsRegRetResult));
	memcpy(abBuf + sizeof(EmRegType) + sizeof(TCnsRegRetResult), &wGroupIndex, sizeof(u16));

	MdlHint(Ums_Mdl_Call, ("EventRegRet handle:0x%x, ret:%d-%s, regType:%d\n"
			, ptHandle->handPaCall, TpEnumIdString(EmTpCnsRegUms, ptRetInfo->m_emReson),  emRegType));

	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(evtp_ums_reg_ret, abBuf, sizeof(abBuf));
	
	return;
}

void CUmsRegMgr::Event323UnRegRet(u8* pData, u16 wDataSize)
{
	TUmsHandle* ptHandle = (TUmsHandle*)pData;
	TUCSipRegResult* ptUCSipRegResult = (TUCSipRegResult*)(pData + sizeof(TUmsHandle));
	u16 nAppId = ptHandle->GetEpID();

	if (nAppId >= CONFTEMP_HANDLE_START)
	{
		Temp323RetFailed(pData, wDataSize);
		return;
	}

	if (nAppId-em_Gk_reg_type>=TP_TEMPGROUP_MAXNUM)
	{
		MdlError(Ums_Mdl_Call, ("Event323UnRegRet index is error! index:%d, handle:0x%x, ret:%d-%s.\n"
			, nAppId-em_Gk_reg_type, ptHandle->handPaCall, TpEnumIdString(EmTpCnsRegUms, ptUCSipRegResult->m_emTpCnsRegUms)));
		return ;
	}

 	MdlHint(Ums_Mdl_Call, ("Event323UnRegRet old handle:0x%x, new handle:0x%x, ret:%d.\n"
		, m_dwGkRegHandle[nAppId-em_Gk_reg_type], ptHandle->handPaCall, ptUCSipRegResult->m_emTpCnsRegUms));
	
	//如果和注册的时候回调的句柄不一致不进行处理
	if (m_dwGkRegHandle[nAppId-em_Gk_reg_type] != ptHandle->handPaCall )
	{
		// 如果本地的注册handle，跟注册失败结果的hanlde不一致，那可能handleinfo的通知消息后到了，先保存一下
		u16 wRegIndex = nAppId-em_Gk_reg_type;
		m_adwGKResultPAHandle[wRegIndex] = ptHandle->handPaCall;
		m_atGkRegResultInfo[wRegIndex].m_emTpCnsRegUms = ptUCSipRegResult->m_emTpCnsRegUms;
		m_atGkRegResultInfo[wRegIndex].m_nAliasNum = ptUCSipRegResult->m_nAliasNum;
		memcpy(m_atGkRegResultInfo[wRegIndex].m_atTPAlias, ptUCSipRegResult->m_atTPAlias,sizeof(TTPAlias)*m_atGkRegResultInfo[wRegIndex].m_nAliasNum);
		m_abGkRegResValid[wRegIndex] = TRUE;
		return ;
	}
	//打印重复别名
	if(tp_CnsRegRet_AliasRepeat == ptUCSipRegResult->m_emTpCnsRegUms)
	{
		MdlHint(Ums_Mdl_Call, ("Event323UnRegRet AliasRepeatNum = %d\n",ptUCSipRegResult->m_nAliasNum));
		for(u16 wIndex = 0; wIndex < ptUCSipRegResult->m_nAliasNum; ++wIndex)
		{
			MdlHint(Ums_Mdl_Call, ("Event323UnRegRet Index = %d, Alias = %s\n",wIndex+1,ptUCSipRegResult->m_atTPAlias[wIndex].m_abyAlias));
		}
		
	}

	GkResultFailProcess(nAppId, ptUCSipRegResult);

	ClearGkRegResultInfo(nAppId-em_Gk_reg_type);

	return;
}


void CUmsRegMgr::EventUnRegRet(u8* pData, u16 wDataSize)
{
	TUmsHandle* ptHandle = (TUmsHandle*)pData;
	TUCSipRegResult* ptUCSipRegResult = (TUCSipRegResult*)(pData + sizeof(TUmsHandle));	
	u16 nAppId = ptHandle->GetEpID();


	if (nAppId >= CONFTEMP_HANDLE_START)
	{//临时模板SIP注册失败
		TempSipRegFailed(pData, wDataSize);
		return;
	}

	if (nAppId-em_Sip_reg_type>=TP_TEMPGROUP_MAXNUM)
	{
		MdlError(Ums_Mdl_Call, ("EventUnRegRet index is error! index:%d, handle:0x%x, ret:%d-%s.\n"
			, nAppId-em_Sip_reg_type, ptHandle->handPaCall, TpEnumIdString(EmTpCnsRegUms, ptUCSipRegResult->m_emTpCnsRegUms)));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("EventUnRegRet old handle:0x%x, new handle:0x%x, ret:%d, num:%d,name:%s,name2:%s.\n"
		, m_dwStackHandle[nAppId-em_Sip_reg_type],  ptHandle->handPaCall,
		ptUCSipRegResult->m_emTpCnsRegUms, ptUCSipRegResult->m_nAliasNum,
		ptUCSipRegResult->m_atTPAlias[0].m_abyAlias, ptUCSipRegResult->m_atTPAlias[1].m_abyAlias));

	if (m_dwStackHandle[nAppId-em_Sip_reg_type] != ptHandle->handPaCall)
	{
		// 如果本地的注册handle，跟注册失败结果的hanlde不一致，那可能handleinfo的通知消息后到了，先保存一下
		u16 wRegIndex = nAppId-em_Sip_reg_type;
		m_adwResultPAHandle[wRegIndex] = ptHandle->handPaCall;
		m_atRegResultInfo[wRegIndex].m_emTpCnsRegUms = ptUCSipRegResult->m_emTpCnsRegUms;
		m_atRegResultInfo[wRegIndex].m_nAliasNum = ptUCSipRegResult->m_nAliasNum;
		memcpy(m_atRegResultInfo[wRegIndex].m_atTPAlias,ptUCSipRegResult->m_atTPAlias,sizeof(TTPAlias)*m_atRegResultInfo[wRegIndex].m_nAliasNum);
		m_abRegResValid[wRegIndex] = TRUE;
		return ;
	}
	
	//打印重复别名
	if(tp_CnsRegRet_AliasRepeat == ptUCSipRegResult->m_emTpCnsRegUms)
	{
		MdlHint(Ums_Mdl_Call, ("EventUnRegRet AliasRepeatNum = %d\n",ptUCSipRegResult->m_nAliasNum));
		for(u16 wIndex = 0; wIndex < ptUCSipRegResult->m_nAliasNum; ++wIndex)
		{
			MdlHint(Ums_Mdl_Call, ("EventUnRegRet Index = %d, Alias = %s\n",wIndex+1,ptUCSipRegResult->m_atTPAlias[wIndex].m_abyAlias));
		}
	
	}

	SipResultFailProcess(nAppId,ptUCSipRegResult);
	
	ClearRegResultInfo(nAppId-em_Sip_reg_type);

	return;
}


void CUmsRegMgr::EventAdapterReg(u8* pData, u16 wDataSize)
{
	MdlHint(Ums_Mdl_Call, ("EventAdapterReg...\n"));
	
	u16 wIndex;
	
	TEqpRes tEqp;
	TTPTransAddr tTransAddr;
	TP_SAFE_CAST(tEqp, pData);
	TP_SAFE_CAST(tTransAddr, pData + sizeof(tEqp));
	
	TRegAdapter* ptAdapt = NULL;	
	for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
	{
		if (m_atRegAdapt[wIndex].m_tEqp.IsValid() &&
			m_atRegAdapt[wIndex].m_tEqp.m_dwEqpNode == tEqp.m_dwEqpNode)
		{
			ptAdapt = &(m_atRegAdapt[wIndex]);
			break;
		}

		if (!m_atRegAdapt[wIndex].m_tEqp.IsValid() && NULL == ptAdapt)
		{
			ptAdapt = &m_atRegAdapt[wIndex];
		}
	}

	if (NULL == ptAdapt)
	{
		MdlError(Ums_Mdl_Call, ("EventAdapterReg no idle adapter..., eqpIP:"TPIPFORMAT"\n", Tpu32ToIP(tTransAddr.m_dwIP)));
		return;
	}

	ptAdapt->m_tEqp = tEqp;
	ptAdapt->m_tAddr = tTransAddr;

	if (NULL == m_ptCurAdapt)
	{
		m_ptCurAdapt = ptAdapt;

		CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
		BOOL32 bOnline = TRUE;
		pService->NotifyMsgToService(evtp_ums_adapter_regout, &bOnline, sizeof(BOOL32));

		if (m_tRegCfg.bUsed)
		{
			TempReg(em_Sip_reg_type);
		}
		
		if (m_tGkRegCfg.m_bUsed)
		{
			TempReg(em_Gk_reg_type);
		}
	}

	MdlHint(Ums_Mdl_Call, ("EventAdapterReg adpater:%d, Reg:%d\n", m_ptCurAdapt->m_tEqp.m_dwEqpNode, m_tRegCfg.bUsed));

	return;
}

void CUmsRegMgr::EventAdapterUnReg(u8* pData, u16 wDataSize)
{
	TEqpRes tEqp;
	TP_SAFE_CAST(tEqp, pData);
	MdlHint(Ums_Mdl_Call, ("EventAdapterUnReg NeedReg:%d, disconAdapter:%d\n", m_tRegCfg.bUsed, tEqp.m_dwEqpNode));

	u16 wIndex = 0;
	TRegAdapter* ptAdapt = NULL;	
	for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
	{
		if (m_atRegAdapt[wIndex].m_tEqp.IsValid() &&
			m_atRegAdapt[wIndex].m_tEqp.m_dwEqpNode == tEqp.m_dwEqpNode)
		{
			ptAdapt = &(m_atRegAdapt[wIndex]);
			break;
		}
	}

	if (NULL == ptAdapt)
	{
		MdlError(Ums_Mdl_Call, ("EventAdapterUnReg Not find the adapter.\n"));
		return ;
	}

	if (NULL != m_ptCurAdapt && ptAdapt == m_ptCurAdapt)
	{
		if (m_tRegCfg.bUsed)
		{
			KillTimer(evtp_RRQ_Timer);
			ClearSipRegState();
		}
		
		if (m_tGkRegCfg.m_bUsed)
		{
			KillTimer(evtp_GK_RRQ_Timer);
			ClearGkRegState();
		}

		m_ptCurAdapt->Clear();
		m_ptCurAdapt = NULL;

		for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
		{
			if (m_atRegAdapt[wIndex].m_tEqp.IsValid())
			{
				m_ptCurAdapt = &(m_atRegAdapt[wIndex]);
				break;
			}
		}

		if (NULL != m_ptCurAdapt)
		{
			if (m_tRegCfg.bUsed)
			{
				Reg(ALL_REG, em_Sip_reg_type);
				TempReg(em_Sip_reg_type);
			}
			
			if (m_tGkRegCfg.m_bUsed)
			{
				Reg(ALL_REG, em_Gk_reg_type);
				TempReg(em_Sip_reg_type);
			}
		}
	}

	if (NULL != ptAdapt)
	{
		ptAdapt->Clear();
	}

	if (NULL == m_ptCurAdapt)
	{
		//没有在去注册,更新regservice里面的状态
		CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
		BOOL32 bOnline = FALSE;
		pService->NotifyMsgToService(evtp_ums_adapter_regout, &bOnline, sizeof(BOOL32));
	}
}

void CUmsRegMgr::EventHandleInfo(u8* pData, u16 wDataSize)
{
	TUmsHandle tHandle = *(TUmsHandle*)pData;
	EmTpRegType emRegType = *(EmTpRegType*)(pData+sizeof(TUmsHandle));
	u16 wIndex = tHandle.GetEpID();
	MdlHint(Ums_Mdl_Call, ("EventHandleInfo handle:0x%x, regType:%d\n", tHandle.handPaCall, emRegType));
	
	if ( wIndex >= CONFTEMP_HANDLE_START )
	{
		msgprint("CUmsRegMgr::EventHandleInfo handle temp group info\n");
		TempHandleInfo(pData, wDataSize);
		return;
	}

	switch(emRegType)
	{
	case em_sip_reg:
		{
			if (wIndex-em_Sip_reg_type>=TP_TEMPGROUP_MAXNUM)
			{
				MdlError(Ums_Mdl_Call, ("EventHandleInfo SipReg index is error! index:%d, handle:0x%x.\n"
					, wIndex-em_Sip_reg_type, tHandle.handPaCall));
				return ;
			}
			m_dwStackHandle[wIndex-em_Sip_reg_type] = tHandle.handPaCall;
			if (m_abRegResValid[wIndex-em_Sip_reg_type] 
				&& m_adwResultPAHandle[wIndex-em_Sip_reg_type] == tHandle.handPaCall)
			{// 跟之前保存的pahandle一致才处理，避免正常逻辑下handle被误清空
				SipResultFailProcess(wIndex, &m_atRegResultInfo[wIndex-em_Sip_reg_type]);
			}
			ClearRegResultInfo(wIndex-em_Sip_reg_type);
		}
		break;

	case em_323_reg:
		{
			if (wIndex-em_Gk_reg_type>=TP_TEMPGROUP_MAXNUM)
			{
				MdlError(Ums_Mdl_Call, ("EventHandleInfo GKReg index is error! index:%d, handle:0x%x.\n"
					, wIndex-em_Gk_reg_type, tHandle.handPaCall));
				return ;
			}
			m_dwGkRegHandle[wIndex-em_Gk_reg_type] = tHandle.handPaCall;
			if (m_abGkRegResValid[wIndex-em_Gk_reg_type]
				&& m_adwGKResultPAHandle[wIndex-em_Gk_reg_type] == tHandle.handPaCall)
			{// 跟之前保存的pahandle一致才处理，避免正常逻辑下handle被误清空
				GkResultFailProcess(wIndex, &m_atGkRegResultInfo[wIndex-em_Gk_reg_type]);
			}
			ClearGkRegResultInfo(wIndex-em_Gk_reg_type);

		}
		break;
	}

	return;
}

void CUmsRegMgr::EventSipRegTimer(u8* pData, u16 wDataSize)
{
	BOOL32 bTempRes = TRUE;
	//判断临时模板
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		if (em_reging != m_aemTempSipRegState[wIndex] && em_reg_success != m_aemTempSipRegState[wIndex])
		{
			if ( !m_atTempAlias[wIndex][0].IsInValid())
			{
				TempReg(em_Sip_reg_type, wIndex);
				bTempRes = FALSE;
			}			
		}
	}

	BOOL32 bRes = TRUE;
	for(wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		if (!m_bSipUnRegPack[wIndex])
		{
			//句柄不为空，先取消注册
			if (m_dwStackHandle[wIndex] != 0)
			{
				UnReg(em_Sip_reg_type, (EmRegGroupNum)wIndex);
			}
				
			Reg(wIndex, em_Sip_reg_type);
			bRes = FALSE;
		}
	}
		
	if (bRes && bTempRes)
	{
		KillTimer(evtp_RRQ_Timer);
	}
}

void CUmsRegMgr::EventGkRegTimer(u8* pData, u16 wDataSize)
{

	u16 wIndex = 0;
	//以下为判断临时模板GK注册情况
	BOOL32 bTempRes = TRUE;
	for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		if (em_reging != m_aemTempGkRegState[wIndex] && em_reg_success != m_aemTempGkRegState[wIndex])
		{
			if ( !m_atTempAlias[wIndex][0].IsInValid())
			{
				TempReg(em_Gk_reg_type, wIndex);
				bTempRes = FALSE;
			}
		}
	}

	BOOL32 bRes = TRUE;
	for(wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		if (!m_bGkUnRegPack[wIndex])
		{
			if (m_dwGkRegHandle[wIndex] != 0)
			{
				UnReg(em_Gk_reg_type, (EmRegGroupNum)wIndex);
			}
			Reg(wIndex, em_Gk_reg_type);
			bRes = FALSE;
		}
	}

	if (bRes && bTempRes)
	{
		KillTimer(evtp_GK_RRQ_Timer);
	}
}

void CUmsRegMgr::MakeAdapterHandle(TUmsHandle& tHandle, u16 wIndex, EmRegType emRegType)
{
	if (wIndex < TP_TEMPGROUP_MAXNUM*2)
	{
		tHandle.MakeAppHandle(AID_UMSCONFMGR, wIndex + emRegType);
		if (em_Sip_reg_type == emRegType)
		{
			tHandle.handPaCall = m_dwStackHandle[wIndex];
		}
		else
		{
			tHandle.handPaCall = m_dwGkRegHandle[wIndex];
		}
		
		if (NULL != m_ptCurAdapt)
		{
			tHandle.m_dwAdapteID = m_ptCurAdapt->m_tEqp.m_dwEqpNode;
		}
	}
}

void CUmsRegMgr::ClearSipRegState()
{
	for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		m_dwStackHandle[wIndex] = 0;
		m_bSipUnRegPack[wIndex] = TRUE;
		m_bIsSipRegged[wIndex] = FALSE;
		ClearRegResultInfo(wIndex);
	}
}

void CUmsRegMgr::ClearGkRegState()
{
	for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		m_dwGkRegHandle[wIndex] = 0;
		m_bGkUnRegPack[wIndex] = TRUE;
		m_bisGkRegged[wIndex] = FALSE;
		ClearGkRegResultInfo(wIndex);
	}
}
void  CUmsRegMgr::GkResultFailProcess(u16 wAppId ,TUCSipRegResult* ptResult )
{
	EmRegType emRegType = em_Gk_reg_type;
	u16 wGroupIndex = wAppId-emRegType;
	u8 abBuf[sizeof(EmRegType) + sizeof(TUCSipRegResult) + sizeof(u16)] = {0};
	memcpy(abBuf, &emRegType, sizeof(EmRegType));
	memcpy(abBuf+sizeof(EmRegType), ptResult, sizeof(TUCSipRegResult));
	memcpy(abBuf+sizeof(EmRegType) + sizeof(TUCSipRegResult), &wGroupIndex, sizeof(u16));
	
	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(evtp_ums_unreg_ret, abBuf, sizeof(abBuf));
	m_dwGkRegHandle[wAppId-emRegType] = 0;
	m_bGkUnRegPack[wAppId-emRegType] = FALSE;
	m_bisGkRegged[wAppId - emRegType] = FALSE;

	if (m_tGkRegCfg.m_nTimeToLive > 0)
	{
		KillTimer(evtp_GK_RRQ_Timer);
		SetTimer(evtp_GK_RRQ_Timer, (m_tGkRegCfg.m_nTimeToLive + UMS_REQ_Timer) * 1000 );
	}

}
void  CUmsRegMgr::SipResultFailProcess(u16 wAppId ,TUCSipRegResult* ptResult )
{
	EmRegType emRegType = em_Sip_reg_type;
	u16 wGroupIndex = wAppId-em_Sip_reg_type;
	u8 abBuf[sizeof(EmRegType) + sizeof(TUCSipRegResult) + sizeof(u16)] = {0};

	memcpy(abBuf, &emRegType, sizeof(EmRegType));
	memcpy(abBuf+sizeof(EmRegType), ptResult, sizeof(TUCSipRegResult));
	memcpy(abBuf + sizeof(EmRegType) + sizeof(TUCSipRegResult), &wGroupIndex, sizeof(u16));

	CUmsConfInst* pService = (CUmsConfInst*)GetInstance();
	pService->NotifyMsgToService(evtp_ums_unreg_ret, abBuf, sizeof(abBuf));	
	
	m_dwStackHandle[wAppId-em_Sip_reg_type] = 0;
	m_bSipUnRegPack[wAppId-em_Sip_reg_type] = FALSE;
	m_bIsSipRegged[wAppId - em_Sip_reg_type] = FALSE;
	
	if (m_tRegCfg.wExpire > 0)
	{
		KillTimer(evtp_RRQ_Timer);
		SetTimer(evtp_RRQ_Timer, (m_tRegCfg.wExpire + UMS_REQ_Timer) * 1000);
	}
				

}

void CUmsRegMgr::StartTempReg(TUmsConfBase& tTemp, u16 wConfID)
{
	if (TP_INVALID_INDEX < wConfID || wConfID <= 0)
	{
		msgprint("CUmsRegMgr::StartTempReg no idle reg:%d\n", wConfID);

		return;
	}

	u16 wIndex = wConfID - 1;

	UndoTempReg(wConfID);

	u16 wAliasNum = 0;
	if (tTemp.m_achConfE164[0] != '\0')
	{
		m_atTempAlias[wIndex][wAliasNum++].SetAlias(tp_Alias_e164, tTemp.m_achConfE164);
	}
	if (strlen(tTemp.m_achConfName) > 0)
	{
		m_atTempAlias[wIndex][wAliasNum++].SetAlias(tp_Alias_h323, tTemp.m_achConfName);
	}

	m_aemTempSipRegState[wIndex] = em_un_reg;
 	m_aemTempGkRegState[wIndex] = em_un_reg;		

	MdlHint(Ums_Mdl_Call, ("StartTempReg ConfID:%d, aliasnum:%d, 323name:%s, 164name:%s\n", wConfID, wAliasNum, 
		m_atTempAlias[wIndex][0].m_abyAlias, m_atTempAlias[wIndex][1].m_abyAlias));
	
	if (wAliasNum > 0)
	{
		if (m_tRegCfg.bUsed)
		{				
			TempReg(em_Sip_reg_type, wIndex);
		}
		
		if (m_tGkRegCfg.m_bUsed)
		{
			TempReg(em_Gk_reg_type, wIndex);
		}
	}
}

void CUmsRegMgr::UndoTempReg(u16 wConfID)
{
	if (TP_INVALID_INDEX < wConfID || wConfID <= 0)
	{
		msgprint("CUmsRegMgr::UndoTempReg no idle reg:%d\n", wConfID);	
		return;
	}
	u16 wIndex = wConfID - 1;

	TUmsHandle tHandle;
	if (NULL != m_ptCurAdapt)
	{
		tHandle.m_dwAdapteID = m_ptCurAdapt->m_tEqp.m_dwEqpNode;
	}

	if (m_tRegCfg.bUsed && (!m_atTempAlias[wIndex][0].IsInValid() || INVALID_STACK_HANDLE != m_adwTempSipRegHandle[wIndex]))
	{
		tHandle.MakeAppHandle(AID_UMSCONFMGR, wIndex + CONFTEMP_HANDLE_START + em_Sip_reg_type);
		tHandle.handPaCall = m_adwTempSipRegHandle[wIndex];
		UmsUnregister(tHandle, em_Sip_reg_type);
		m_adwTempSipRegHandle[wIndex] = INVALID_STACK_HANDLE;
	}
	
	if (m_tGkRegCfg.m_bUsed && (!m_atTempAlias[wIndex][0].IsInValid() || INVALID_STACK_HANDLE != m_adwTempGkRegHandle[wIndex]))
	{
		tHandle.MakeAppHandle(AID_UMSCONFMGR, wIndex + CONFTEMP_HANDLE_START + em_Gk_reg_type);
		tHandle.handPaCall = m_adwTempGkRegHandle[wIndex];
		UmsUnregister(tHandle, em_Gk_reg_type);
		m_adwTempGkRegHandle[wIndex] = INVALID_STACK_HANDLE;
	}
}

BOOL32 CUmsRegMgr::Create()
{
	return TRUE;
}
void CUmsRegMgr::TempReg(const EmRegType& emType, u16 wIndex)
{	
	if (NULL == m_ptCurAdapt)
	{
		msgprint("CUmsRegMgr::TempReg reg adapter umreg, regtype:%d\n", emType);
		return;
	}

	TUmsHandle tHandle;
	tHandle.m_dwAdapteID = m_ptCurAdapt->m_tEqp.m_dwEqpNode;

	switch(emType)
	{
	case em_Sip_reg_type:
		{
			if (!m_tRegCfg.bUsed)
			{
				return;
			}

			if (m_tRegCfg.wExpire > 0)
			{
				KillTimer(evtp_RRQ_Timer);
				SetTimer(evtp_RRQ_Timer, (m_tRegCfg.wExpire + UMS_REQ_Timer) * 1000);
			}
			tHandle.MakeAppHandle(AID_UMSCONFMGR, CONFTEMP_HANDLE_START + wIndex + em_Sip_reg_type);
		}
		break;
	case em_Gk_reg_type:
		{
			if (!m_tGkRegCfg.m_bUsed)
			{
				return;
			}

			if (m_tGkRegCfg.m_nTimeToLive > 0)
			{
				KillTimer(evtp_GK_RRQ_Timer);
				SetTimer(evtp_GK_RRQ_Timer, (m_tGkRegCfg.m_nTimeToLive + UMS_REQ_Timer) * 1000 );
			}
			tHandle.MakeAppHandle(AID_UMSCONFMGR, CONFTEMP_HANDLE_START + wIndex + em_Gk_reg_type);
		}
		break;
	}

	msgprint("CUmsRegMgr::TempReg reg adapter id:%d, reg wIndex:%d, regtype:%d\n", m_ptCurAdapt->m_tEqp.m_dwEqpNode, wIndex, emType);

	u16 wAliasNum = 0;
	for (u16 wI = 0; wI < UMS_MAX_TEMPCONF_NAME; wI++)
	{
		if (!m_atTempAlias[wIndex][wI].IsInValid())
		{
			wAliasNum++;
		}
	}
	if (wAliasNum > 0)
	{		
		if (em_Sip_reg_type == emType)
		{
			UmsRegister(tHandle, m_tRegCfg, m_atTempAlias[wIndex], wAliasNum);
			m_aemTempSipRegState[wIndex] = em_reging;
		}
		if (em_Gk_reg_type == emType)
		{
			for (u16 wID = 0; wID < wAliasNum; wID++)
			{
				m_tGkRegCfg.m_tAlias[wID] = m_atTempAlias[wIndex][wID];
			}
			UmsGkRegister(tHandle, m_tGkRegCfg, wAliasNum);
			m_aemTempGkRegState[wIndex] = em_reging;
		}
	}
}

void CUmsRegMgr::TempReg(const EmRegType& emType)
{
	if (em_Sip_reg_type == emType)
	{
		for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
		{
			if ((em_un_reg != m_aemTempSipRegState[wIndex]) && !m_atTempAlias[wIndex][0].IsInValid())
			{
				TempReg(emType, wIndex);
			}
		}
	}
	else if (em_Gk_reg_type == emType)
	{
		for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
		{
			if ((em_un_reg != m_aemTempGkRegState[wIndex]) && !m_atTempAlias[wIndex][0].IsInValid())
			{
				TempReg(emType, wIndex);
			}
		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("[TempReg] Reg Type error, emType: %d\n", emType));
	}
}

void CUmsRegMgr::TempHandleInfo(u8* pData, u16 wDataSize)
{
	TUmsHandle tHandle = *(TUmsHandle*)pData;
	EmTpRegType emRegType = *(EmTpRegType*)(pData+sizeof(TUmsHandle));
	u16 wEqpID = tHandle.GetEpID();
	MdlHint(Ums_Mdl_Call, ("TempHandleInfo handle:0x%x, regType:%d\n", tHandle.handPaCall, emRegType));
	
	u16 wIndex = wEqpID - CONFTEMP_HANDLE_START - emRegType;

	switch(emRegType)
	{
	case em_sip_reg:
		{
			m_adwTempSipRegHandle[wIndex] = tHandle.handPaCall;
		}
		break;
		
	case em_323_reg:
		{
			m_adwTempGkRegHandle[wIndex] = tHandle.handPaCall;
		}
		break;
	}
}

void CUmsRegMgr::TempSipRegFailed(u8* pData, u16 wDataSize)
{
	TUmsHandle* ptHandle = (TUmsHandle*)pData;
	TUCSipRegResult* ptUCSipRegResult = (TUCSipRegResult*)(pData + sizeof(TUmsHandle));
	u16 wEpID = ptHandle->GetEpID();

	u16 wIndex = wEpID - CONFTEMP_HANDLE_START - em_Sip_reg_type;
	MdlHint(Ums_Mdl_Call, ("TempSipRegFailed wIndex:%d, reson:%d, 323name:%s, 164name:%s\n", wIndex, ptUCSipRegResult->m_emTpCnsRegUms,
		m_atTempAlias[wIndex][0].m_abyAlias, m_atTempAlias[wIndex][1].m_abyAlias));
	
	if (m_adwTempSipRegHandle[wIndex] != ptHandle->handPaCall)
	{
		MdlHint(Ums_Mdl_Call, ("TempSipRegFailed old handle:0x%x, new handle:0x%x\n", m_adwTempSipRegHandle[wIndex], 
			ptHandle->handPaCall));
		return;
	}


	m_aemTempSipRegState[wIndex] = em_reg_failed;
	m_adwTempSipRegHandle[wIndex] = INVALID_STACK_HANDLE;

	if (m_tRegCfg.wExpire > 0)
	{
		KillTimer(evtp_RRQ_Timer);
		SetTimer(evtp_RRQ_Timer, (m_tRegCfg.wExpire +UMS_REQ_Timer) * 1000);
	}
}

void CUmsRegMgr::Temp323RetFailed(u8* pData, u16 wDataSize)
{
	TUmsHandle* ptHandle = (TUmsHandle*)pData;
	TUCSipRegResult* ptUCSipRegResult = (TUCSipRegResult*)(pData + sizeof(TUmsHandle));
	u16 wEpID = ptHandle->GetEpID();

	u16 wIndex = wEpID - CONFTEMP_HANDLE_START - em_Gk_reg_type;
	MdlHint(Ums_Mdl_Call, ("Temp323UnRegRet old handle:0x%x, new handle:0x%x, ret:%d, 323name:%s, 164name:%s\n"
		, m_adwTempGkRegHandle[wIndex], ptHandle->handPaCall, ptUCSipRegResult->m_emTpCnsRegUms, 
		m_atTempAlias[wIndex][0].m_abyAlias, m_atTempAlias[wIndex][1].m_abyAlias));

	if (m_adwTempGkRegHandle[wIndex] != ptHandle->handPaCall)
	{
		return;
	}

	m_aemTempGkRegState[wIndex] = em_reg_failed;
	m_adwTempGkRegHandle[wIndex] = INVALID_STACK_HANDLE;

	if (m_tGkRegCfg.m_nTimeToLive > 0)
	{
		KillTimer(evtp_GK_RRQ_Timer);
		SetTimer(evtp_GK_RRQ_Timer, (m_tGkRegCfg.m_nTimeToLive + UMS_REQ_Timer) * 1000 );
	}
}

void CUmsRegMgr::TempRegSuccess(u8* pData, u16 wDataSize)
{
	TUmsHandle* ptHandle = (TUmsHandle*)pData;
	TCnsRegRetResult* ptRetInfo = (TCnsRegRetResult*)(pData + sizeof(TUmsHandle));
	EmRegType emRegType = em_Sip_reg_type;	

	switch(ptRetInfo->m_emRegType)
	{
	case em_sip_reg:
		emRegType = em_Sip_reg_type;
		break;
	case em_323_reg:
		emRegType = em_Gk_reg_type;
		break;
	}

	u16 wIndex = ptHandle->GetEpID() - CONFTEMP_HANDLE_START - emRegType;
	MdlHint(Ums_Mdl_Call, ("TempRegSuccess wIndex:%d, type:%d, 323name:%s, 164name:%s\n", wIndex, emRegType,
		m_atTempAlias[wIndex][0].m_abyAlias, m_atTempAlias[wIndex][1].m_abyAlias));

	if (em_Sip_reg_type == emRegType)
	{
		m_aemTempSipRegState[wIndex] = em_reg_success;
	}
	else if (em_Gk_reg_type == emRegType)
	{
		m_aemTempGkRegState[wIndex] = em_reg_success;

		CTpMsg cMsg;
		cMsg.SetEvent( evtp_CallNode_time );
		cMsg.Post( MAKEIID(AID_UMSCONFMGR,wIndex+1) );
	}
	
}

void CUmsRegMgr::TempRegRetHandle(u16 wIndex)
{
	if (wIndex > TP_UMS_MAX_CONFNUM)
	{
		MdlError(Ums_Mdl_Call, ("TempRegRetHandle wIndex:%d\n", wIndex));
		return;
	}

	BOOL32 bRegRet = TRUE;
	if (m_tRegCfg.bUsed && 
		(m_aemTempGkRegState[wIndex] != em_reg_success && m_aemTempGkRegState[wIndex] != em_reg_failed) )
	{
		bRegRet = FALSE;
	}
	if (m_tGkRegCfg.m_bUsed && 
		(m_aemTempSipRegState[wIndex] != em_reg_success && m_aemTempSipRegState[wIndex] != em_reg_failed) )
	{
		bRegRet = FALSE;
	}
}

void CUmsRegMgr::EventUpdateSipCfg(u8* pData, u16 wDataSize)
{
	TTPSipRegistrarCfg tTempRegCfg;

	TP_SAFE_CAST(tTempRegCfg, pData);
	if (tTempRegCfg.wExpire != m_tRegCfg.wExpire ||
		tTempRegCfg.dwRegIP != m_tRegCfg.dwRegIP ||
		tTempRegCfg.bUsed != m_tRegCfg.bUsed ||
		tTempRegCfg.wRegPort != m_tRegCfg.wRegPort)
	{//取消注册的临时模板后，重新注册
		for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
		{
			if (em_reg_success == m_aemTempSipRegState[wIndex] || em_reging == m_aemTempSipRegState[wIndex])
			{
				if (!m_atTempAlias[wIndex][0].IsInValid())
				{
					UndoTempReg(wIndex + 1);
				}
			}
		}


        m_tRegCfg.bUsed = tTempRegCfg.bUsed;
        m_tRegCfg.wExpire = tTempRegCfg.wExpire;
        m_tRegCfg.dwRegIP = tTempRegCfg.dwRegIP;
		m_tRegCfg.wRegPort = tTempRegCfg.wRegPort;

		TempReg(em_Sip_reg_type);
	}
}

void CUmsRegMgr::EventUpdateGkCfg(u8* pData, u16 wDataSize)
{
	TTPGKCfg tTempGkCfg;
	TP_SAFE_CAST(tTempGkCfg, pData);
	
	if (tTempGkCfg.bUsed != m_tGkRegCfg.m_bUsed ||
		tTempGkCfg.dwGKIP != m_tGkRegCfg.m_tGKAddress.GetIP() ||
		tTempGkCfg.wRegPort != m_tGkRegCfg.m_tGKAddress.GetPort())
	{
		for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
		{
			if (em_reg_success == m_aemTempGkRegState[wIndex] || em_reging == m_aemTempGkRegState[wIndex])
			{
				if (!m_atTempAlias[wIndex][0].IsInValid())
				{
					UndoTempReg(wIndex + 1);
				}
			}
		}


		m_tGkRegCfg.m_bUsed = tTempGkCfg.bUsed;
		m_tGkRegCfg.m_tGKAddress.SetAddr(tTempGkCfg.dwGKIP, tTempGkCfg.wRegPort);

		TempReg(em_Gk_reg_type);
	}

}


BOOL32 CUmsRegMgr::IsRegSuccess( const EmRegType& emRegType ) const
{

	if (em_Sip_reg_type == emRegType)
	{
		for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
		{
			if (m_bIsSipRegged[wIndex])
			{
				return TRUE;
			}
			else
			{
				continue;
			}
		}
	}
	else if (em_Gk_reg_type == emRegType)
	{
		for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
		{
			if (m_bisGkRegged[wIndex])
			{
				return TRUE;
			}
			else
			{
				continue;
			}
		}
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("IsRegFail emRegType :%d\n", emRegType));
		return FALSE;
	}
	return FALSE;
}

void CUmsRegMgr::StopTempReg( u16 wConfID )
{
	if (TP_INVALID_INDEX < wConfID || wConfID <= 0)
	{
		msgprint("CUmsRegMgr::StopTempReg no idle reg:%d\n", wConfID);	
		return;
	}

	//清掉模板别名
	for ( u16 wIndex = 0; wIndex < UMS_MAX_TEMPCONF_NAME; wIndex ++ )
	{
		m_atTempAlias[wConfID - 1][wIndex].Clear();
	}

	UndoTempReg(wConfID);

	return ;
}

void CUmsRegMgr::Show()
{
	u16 wIndex;
	TRegAdapter* ptAdater = NULL;
	msgprint("RegInfo:\n");
	for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; wIndex++)
	{
		ptAdater = &m_atRegAdapt[wIndex];
		if (ptAdater->m_tEqp.IsValid())
		{
			msgprint(" [%d] EqpIp:"TPIPFORMAT", Node:%d, AdapterIp:"TPIPFORMAT".\n", 
				wIndex, u32ToIP(ptAdater->m_tEqp.m_dwEqpIp), ptAdater->m_tEqp.m_dwEqpNode, u32ToIP(ptAdater->m_tAddr.m_dwIP));
		}
	}

	msgprint("\n");
	if (NULL != m_ptCurAdapt)
	{
		ptAdater = m_ptCurAdapt;

		msgprint(" [Cur] EqpIp:"TPIPFORMAT", Node:%d, AdapterIp:"TPIPFORMAT".\n", 
				u32ToIP(ptAdater->m_tEqp.m_dwEqpIp), ptAdater->m_tEqp.m_dwEqpNode, u32ToIP(ptAdater->m_tAddr.m_dwIP));
	}
	msgprint("\n");
	msgprint("RegPackInfo:\n");

	for (wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; wIndex++)
	{
		msgprint(" [%d] RegSipAliasNum:%d, RegSipHandle:%d, SipReged:%d.\n", wIndex,
			m_wSipAliasNum[wIndex], m_dwStackHandle[wIndex], m_bIsSipRegged[wIndex]);
		msgprint("     RegGKAliasNum:%d, RegRegGkHandle:%d, GKReged:%d.\n", 
			m_wGKAliasNum[wIndex], m_dwGkRegHandle[wIndex], m_bisGkRegged[wIndex]);
	}
	msgprint("\n");
	for (wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; wIndex++)
	{
		if (m_abRegResValid[wIndex])
		{
			msgprint(" [WARN][%d] RegResult:%d, PAhandle:0x%x, AliasNum:%d, bIsRegResValid:%d.\n", wIndex,
				m_atRegResultInfo[wIndex].m_emTpCnsRegUms, m_adwResultPAHandle[wIndex], 
				m_atRegResultInfo[wIndex].m_nAliasNum, m_abRegResValid[wIndex]);
		}
		if (m_abGkRegResValid[wIndex])
		{
			msgprint(" [WARN][%d] GkRegResult:%d, PAhandle:0x%x, AliasNum:%d, bIsGkRegResValid:%d.\n", wIndex,
				m_atGkRegResultInfo[wIndex].m_emTpCnsRegUms, m_adwGKResultPAHandle[wIndex], 
				m_atGkRegResultInfo[wIndex].m_nAliasNum, m_abGkRegResValid[wIndex]);
		}
	}
	
}


