#include "handleregservice.h"
#include "umsobject.h"
#include "umsserver.h"
#include "handleconftemplateservice.h"
#include "tpaddrmgr.h"

#include "innereventumsserver.h"
#include "innereventregsrv.h"

// 外部消息
#include "eventoutumsreg.h"
#include "eventoutsipadapter.h"

#define DEFAULT_SIP_PORT		5060
#define DEFAULT_EXPIRE_TIME		10//30


CUmsRegHandleService::CUmsRegHandleService(CTpObject* pcObjec)
:CTpHandler(pcObjec)
{
	m_wTempGroupNum			= 0;
	m_bReqRegInfo			= FALSE;
	ClearRegRet(em_Sip_reg_type);
	ClearRegRet(em_Gk_reg_type);
}


CUmsRegHandleService::~CUmsRegHandleService()
{
	
}

/*==============================================================================
函数名    :  Create
功能      :  需要由业务保证此Create的初始化晚于会议模板的初始化
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2011-5-4               zhaixiaogang
==============================================================================*/
BOOL32 CUmsRegHandleService::Create()
{
	EmRegGroupNum emRegGroupNum = em_AllGroup;
	umsGetSipRegCfg(m_tSipRegCfg);
	umsGetGKRegCfg(m_tGKRegCfg);
	m_tSipRegCfg.dwHostIP = GetLocalIP();
	m_tSipRegCfg.wHostPort = DEFAULT_SIP_PORT;
	m_tSipRegCfg.wExpire = DEFAULT_EXPIRE_TIME;

	m_bReqRegInfo = FALSE;

	TTPQTEncryptInfo tTPQTEncryptInfo;
	umsGetQTEncryptInfo(tTPQTEncryptInfo);
	m_tSipRegCfg.m_dwQtID = tTPQTEncryptInfo.m_dwQuanTumID;
	m_tGKRegCfg.m_dwQtID  = tTPQTEncryptInfo.m_dwQuanTumID;

	//msgprint("[CUmsRegHandleService::Create] m_tSipRegCfg = %d\n",m_tSipRegCfg.bUsed);
	//系统启动做全注册，其余模版状态改变都只做对应组的注册
	if (m_tSipRegCfg.bUsed)
	{
		SetGroupReging(em_Sip_reg_type, emRegGroupNum);
		Register(emRegGroupNum, em_Sip_reg_type);
	}

	if (m_tGKRegCfg.bUsed)
	{
		SetGroupReging(em_Gk_reg_type, emRegGroupNum);
		Register(emRegGroupNum, em_Gk_reg_type);
	}

	return CTpHandler::Create();
}

BOOL32 CUmsRegHandleService::Handler( CTpMsg *const ptMsg )
{
	u16 wEvent = ptMsg->GetEvent();
	u8* pData  = ptMsg->GetBody();
	u16 wSize  = ptMsg->GetBodyLen();
	switch( wEvent ) 
	{
	case ev_SysCmsLoginInd:
		{
			EventLogin(pData, wSize);
		}
		break;

	case ev_SysCmsLogoutInd:
		{
			EventLogout(pData, wSize);
		}
		break;

	case ev_umsreg_cmd:
		{
			EventSetRegCfg(pData, wSize);
		}
		break;

	case ev_umsGKReg_cmd:
		{
			EventSetGkRegCfg(pData, wSize);
		}
		break;

	case evtp_ums_reg_req:
		{
			EventRegReq(pData, wSize);
		}
		break;
		
	case evtp_ums_update_reg:
		{
			EmRegGroupNum emRegGroupNum = *(EmRegGroupNum*)pData;
			EventUpdateReg(emRegGroupNum,FALSE);
		}
		break;
		
	case evtp_ums_adapter_regout:
		{
			EventAdapterRegOut(pData, wSize);
		}
		break;

	case evtp_ums_reg_ret:
		{
			EventRegRet(pData, wSize);
		}
		break;

	case evtp_ums_unreg_req:
		{
			UnRegister(em_Sip_reg_type, em_AllGroup, TRUE);
			ClearRegRet(em_Sip_reg_type);
		//	m_tSipRegCfg.bUsed = FALSE;

			UnRegister(em_Gk_reg_type, em_AllGroup, TRUE);
			ClearRegRet(em_Gk_reg_type);
		//	m_tGKRegCfg.bUsed = FALSE;

			NotifyRegInfoToTpTool();
		}
		break;

	case evtp_ums_unreg_ret:
		{
			EventUnRegRet(pData, wSize);
		}
		break;

	case ev_umsGetRegInfo_Req:
		{
			CTPAddrMgrEx::Instance().ClearSipInfo();
			CTPAddrMgrEx::Instance().ClearGkInfo();
			EventReqRegInfo(ptMsg);
		}
		break;

	case ev_ums_GetRegInfo_Rsp:
		{
			EventReqRegInfoRet(ptMsg);
		}
		break;

	case ev_ums_GetRegInfo_UmsRspEx:
		{
			EventUmsRegInfoRet(ptMsg);
		}
		break;

	case ev_ums_GetRegInfo_CnsRspEx:
		{
			EventCnsRegInfoRet(ptMsg);
		}
		break;

	case ev_ums_GkRegInfo_MtRsp:
		{
			EventMtRegInfoRet(ptMsg);
		}
		break;

	case ev_ums_GkRegInfo_McuRsp:
		{
			EventMcuRegInfoRet(ptMsg);
		}
		break;

	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CUmsRegHandleService::EventRegReq(u8* pDataBuf, u16 wDataSize)
{
	EmRegGroupNum emRegGroupNum;
	emRegGroupNum = *(EmRegGroupNum*)pDataBuf;

	if (m_tSipRegCfg.bUsed)
	{
		UnRegister(em_Sip_reg_type, emRegGroupNum);
		ClearRegRet(em_Sip_reg_type, emRegGroupNum);
		SetGroupReging(em_Sip_reg_type, emRegGroupNum);
		Register(emRegGroupNum, em_Sip_reg_type);
	}
				
	if (m_tGKRegCfg.bUsed)
	{
		UnRegister(em_Gk_reg_type, emRegGroupNum);
		ClearRegRet(em_Gk_reg_type, emRegGroupNum);
		SetGroupReging(em_Gk_reg_type, emRegGroupNum);
		Register(emRegGroupNum, em_Gk_reg_type);
	}
}

void CUmsRegHandleService::EventReqRegInfo(CTpMsg *const ptMsg)
{
	TLogUser         tUser;
	EmGetRegInfoType emType;
	
	TP_SAFE_CAST(tUser, ptMsg->GetBody());
	TP_SAFE_CAST(emType, ptMsg->GetBody()+sizeof(TLogUser));

	if (IsRegOneGroup(em_Sip_reg_type) || IsRegOneGroup(em_Gk_reg_type))
	{
		MdlHint(Ums_Mdl_Service, ("EventReqRegInfo: Req reg info: UserName:%s, ReqType:%d.\n", tUser.m_achName, emType));

		TTPAddrNtyUser tAddNtyUser;
		tAddNtyUser.m_dwIID = tUser.m_dwUserNode;
		tAddNtyUser.m_emType = emType;
		tAddNtyUser.m_wUserData = tUser.m_dwUserInst;

		CTPAddrMgr::GetInstance()->AddOneUserNty(tAddNtyUser);
		CTPAddrMgrEx::Instance().AddUser(tAddNtyUser);
		
		CTpMsg cMsg;
		cMsg.SetEvent(ev_ums_GetRegInfo_Req);
		cMsg.SetBody(&emType,sizeof(EmGetRegInfoType));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));
	}
	else
	{
		MdlHint(Ums_Mdl_Service, ("EventReqRegInfo: Ums not regist to Sip.\n"));

		u8 abRes[sizeof(TTPSipRegPackInfo)+sizeof(EmGetRegInfoType)+sizeof(TTPSipRegInfo)] = {0};
		TTPSipRegPackInfo* ptResPackInfo = (TTPSipRegPackInfo*)abRes;
		EmGetRegInfoType* ptResType = (EmGetRegInfoType*)(abRes + sizeof(TTPSipRegPackInfo));
		TTPSipRegInfo* ptResRegInfo = (TTPSipRegInfo*)(abRes + sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType));

		*ptResType = emType;
		ptResPackInfo->m_wTotalPackNum = 0;
		ptResPackInfo->m_wPackSeq = 0;
		TpNotifyMsgToUeFromService(ev_umsGetRegInfo_Rsp, abRes, sizeof(abRes), tUser);
	}
}

void CUmsRegHandleService::EventUmsRegInfoRet(CTpMsg* const ptMsg)
{
	TRegPackInfoEx tPackInfo;
	TUmsRegPackEx  tRegInfo;
	TP_SAFE_CAST(tPackInfo, ptMsg->GetBody());
	TP_SAFE_CAST(tRegInfo, ptMsg->GetBody()+sizeof(TRegPackInfoEx));

	MdlHint(Ums_Mdl_Service, ("EventUmsRegInfoRet TotalPack:%d, PackSeq:%d, InfoNum:%d.\n",
							   tPackInfo.m_tPackInfo.m_wTotalPackNum, tPackInfo.m_tPackInfo.m_wPackSeq,
							   tRegInfo.m_wSize));

	CTPAddrMgrEx::Instance().AddPack(tPackInfo, tRegInfo);

	PostRegInfoToUserEx();
}

void CUmsRegHandleService::EventCnsRegInfoRet(CTpMsg* const ptMsg)
{
	TRegPackInfoEx tPackInfo;
	TCnsRegPackEx  tRegInfo;
	TP_SAFE_CAST(tPackInfo, ptMsg->GetBody());
	TP_SAFE_CAST(tRegInfo, ptMsg->GetBody()+sizeof(TRegPackInfoEx));
	
	MdlHint(Ums_Mdl_Service, ("EventCnsRegInfoRet TotalPack:%d, PackSeq:%d, InfoNum:%d.\n",
							   tPackInfo.m_tPackInfo.m_wTotalPackNum, tPackInfo.m_tPackInfo.m_wPackSeq,
							   tRegInfo.m_wSize));

	CTPAddrMgrEx::Instance().AddPack(tPackInfo, tRegInfo);

	PostRegInfoToUserEx();
}

void CUmsRegHandleService::EventMtRegInfoRet(CTpMsg* const ptMsg)
{
	EmGetRegInfoType emType;
	TTPMtRegInfo tList;
	TP_SAFE_CAST(emType, ptMsg->GetBody());
	TP_SAFE_CAST(tList, ptMsg->GetBody()+sizeof(EmGetRegInfoType));

	MdlHint(Ums_Mdl_Service, ("EventMtRegInfoRet GetType:%d, ListNum:%d, IsEnd:%d.\n",
							   emType, tList.m_wListNum, tList.m_bIsEnd));

	CTPAddrMgrEx::Instance().AddPack(tList);

	PostRegInfoToUserEx();
}

void CUmsRegHandleService::EventMcuRegInfoRet(CTpMsg* const ptMsg)
{
	EmGetRegInfoType emType;
	TTPMcuRegInfo tList;
	TP_SAFE_CAST(emType, ptMsg->GetBody());
	TP_SAFE_CAST(tList, ptMsg->GetBody()+sizeof(TTPMcuRegInfo));

	MdlHint(Ums_Mdl_Service, ("EventMcuRegInfoRet GetType:%d, ListNum:%d, IsEnd:%d.\n",
							   tList.m_wListNum, tList.m_bIsEnd));

	CTPAddrMgrEx::Instance().AddPack(tList);

	PostRegInfoToUserEx();
}

void CUmsRegHandleService::EventReqRegInfoRet(CTpMsg* const ptMsg)
{
	TTPSipRegPackInfo	tPackInfo;
	EmGetRegInfoType	emRegType;
	TTPSipRegInfo		tSipRegInfo;

	TP_SAFE_CAST(tPackInfo, ptMsg->GetBody());
	TP_SAFE_CAST(emRegType, ptMsg->GetBody() + sizeof(TTPSipRegPackInfo));
	TP_SAFE_CAST(tSipRegInfo, ptMsg->GetBody() + sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType));

	MdlHint(Ums_Mdl_Service, ("EventReqRegInfoRet: TotalPack: %d, PackSeq: %d, ReqType: %d, AliasNums: %d, AliasType: %d.\n", 
			tPackInfo.m_wTotalPackNum, tPackInfo.m_wPackSeq, emRegType, tSipRegInfo.m_wAliasNum, tSipRegInfo.m_emSelfType));

	CTPAddrMgr::GetInstance()->AddOnePack(tPackInfo, tSipRegInfo, emRegType);

	if(CTPAddrMgr::GetInstance()->IsEnableNtyAndSetStatus())
	{
		u16 wUserNums = CTPAddrMgr::GetInstance()->GetUserNtyNum();
		if (0 != wUserNums)
		{
			TTPAddrNtyUser *ptTPAddrNtyUser = new TTPAddrNtyUser[wUserNums];
			if (NULL == ptTPAddrNtyUser)
			{
				MdlHint(Ums_Mdl_Service, ("EventReqRegInfoRet: new  TTPAddrNtyUser[%d] failed.\n", wUserNums));
				return ;
			}
			
			if( !CTPAddrMgr::GetInstance()->GetUserNty( ptTPAddrNtyUser, wUserNums ) )
			{
				MdlHint(Ums_Mdl_Service, ("EventReqRegInfoRet: CTPAddrMgr::GetInstance()->GetUserNty failed.\n"));
				delete[] ptTPAddrNtyUser;
				return;
			}
			
			MdlHint(Ums_Mdl_Service, ("EventReqRegInfoRet: Send Reg info to User: userNums: %d.\n", wUserNums));
			
			TLogUser tUser;
			//遍历注册的用户发送注册信息
			for (u16 wIndex = 0; wIndex < wUserNums; ++wIndex)
			{
				tUser.m_dwUserNode = ptTPAddrNtyUser[wIndex].m_dwIID;
				tUser.m_dwUserInst = ptTPAddrNtyUser[wIndex].m_wUserData;
				PostRegInfoToUser(tUser, ptTPAddrNtyUser[wIndex].m_emType);
			} 
			
			delete[] ptTPAddrNtyUser;

			CTPAddrMgr::GetInstance()->ClearUserNty();
		}
		else
		{
			MdlHint(Ums_Mdl_Service, ("EventReqRegInfoRet: No user to request register info.\n"));
		}

		CTPAddrMgrEx::Instance().ClearUser();
	}
}

void CUmsRegHandleService::NotifyRegInfoToTpTool()
{	
	TTPSipRegistrarCfg tSipCfg;
	memcpy(&tSipCfg, &m_tSipRegCfg, sizeof(TTPSipRegistrarCfg));
	TTPGKCfg tGkCfg;
	memcpy(&tGkCfg, &m_tGKRegCfg, sizeof(TTPGKCfg));
	if (IsRegOneGroup(em_Sip_reg_type))
	{
		tSipCfg.bRegistered = TRUE;
	}
	else
	{
		tSipCfg.bRegistered = FALSE;
	}
	
	TpNotifyMsgToToolUserFromService(ev_umsreg_notify, &tSipCfg, sizeof(tSipCfg));
	
	if (IsRegOneGroup(em_Gk_reg_type))
	{	
		tGkCfg.bRegistered = TRUE;
	}
	else
	{
		tGkCfg.bRegistered = FALSE;
	}
	TpNotifyMsgToToolUserFromService(ev_umsGKReg_notify, &tGkCfg, sizeof(tGkCfg));
}

void CUmsRegHandleService::EventLogout(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);

	TTPAddrNtyUser tAddNtyUser;
	tAddNtyUser.m_dwIID = tUser.m_dwUserNode;
	tAddNtyUser.m_wUserData = tUser.m_dwUserInst;
				
	CTPAddrMgrEx::Instance().DelUser(tAddNtyUser);
}

void CUmsRegHandleService::EventLogin(void* pDataBuf, u16 wDataSize)
{
	TLogUser* pLogUser = (TLogUser*)pDataBuf;
	
	TUCSipRegResult tRegRet;
	do 
	{

		if (IsToolUser(*pLogUser))
		{// 维护工具不通知地址薄
			NotifyRegInfoToTpTool();
			break;
		}


		TTPAddrNtyUser tAddNtyUser;
		tAddNtyUser.m_dwIID = pLogUser->m_dwUserNode;
		tAddNtyUser.m_emType = emGetRegInfoType_ALL;
		tAddNtyUser.m_wUserData = pLogUser->m_dwUserInst;
		CTPAddrMgrEx::Instance().AddUser(tAddNtyUser);

		
		TpNotifyMsgToUeFromService(ev_umsreg_notify, &m_tSipRegCfg, sizeof(m_tSipRegCfg), *pLogUser);
		TpNotifyMsgToUeFromService(ev_umsGKReg_notify, &m_tGKRegCfg, sizeof(m_tGKRegCfg), *pLogUser);

		if (IsRegOneGroup(em_Sip_reg_type) || IsRegOneGroup(em_Gk_reg_type))
		{
			if (CTPAddrMgr::GetInstance()->IsEnableNtyAndSetStatus())
			{
				MdlHint(Ums_Mdl_Service, ("EventLogin: User log in , send reg info userName: %s, reqType: %d.\n", pLogUser->m_achName, emGetRegInfoType_ALL));
				PostRegInfoToUser(*pLogUser, emGetRegInfoType_ALL);
				break;
			}

			if (CTPAddrMgrEx::Instance().IsSipEnd() || CTPAddrMgrEx::Instance().IsGkEnd())
			{

				PostRegInfoToUserEx();

				break;
			}




			EmGetRegInfoType tType = emGetRegInfoType_ALL;
			CTpMsg cMsg;
			cMsg.SetBody(pLogUser, sizeof(TLogUser));
			cMsg.CatBody(&tType, sizeof(tType));
				
			EventReqRegInfo(&cMsg);
		}
	} while (FALSE);

	if (m_tSipRegCfg.bUsed)
	{
		for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
		{
			if (em_reg_failed == m_atRegRet[wIndex][em_Sip_reg_type].m_emRegState)
			{
				tRegRet.m_emTpCnsRegUms = m_atRegRet[wIndex][em_Sip_reg_type].m_emReason;
				TpNotifyMsgToUeFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet), *pLogUser);
				TpNotifyMsgToToolUserFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet));
			}
		}
	}
	
	if (m_tGKRegCfg.bUsed)
	{
		for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
		{
			if (em_reg_failed == m_atRegRet[wIndex][em_Gk_reg_type].m_emRegState)
			{
				tRegRet.m_emTpCnsRegUms = m_atRegRet[wIndex][em_Gk_reg_type].m_emReason;
				TpNotifyMsgToUeFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet), *pLogUser);
				TpNotifyMsgToToolUserFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet));
			}
		}
	}
}

void CUmsRegHandleService::PostRegInfoToUserEx()
{
	BOOL32 bFlag = FALSE;

	u16 wUserNums = CTPAddrMgrEx::Instance().GetUserNums();
	u16 wCnsNum = 0;
	u16 wUmsNum = 0;
	u16 wMtNum  = 0;
	u16 wMcuNum = 0;
	TTPAddrNtyUser *ptTPAddrNtyUser = NULL;
	TCnsRegPackEx* ptCnsInfo = NULL;
	TUmsRegPackEx* ptUmsInfo = NULL;
	TTPMtRegInfo* ptMtInfo = NULL;
	TTPMcuRegInfo* ptMcuInfo = NULL;
	
	do 
	{
		if (0 == wUserNums)
		{
			MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: No req user.\n"));
			break;
		}

		if (CTPAddrMgrEx::Instance().IsSipEnd() ||
			CTPAddrMgrEx::Instance().IsGkEnd())
		{
			ptTPAddrNtyUser = new TTPAddrNtyUser[wUserNums];
			if (NULL == ptTPAddrNtyUser)
			{
				MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: new  TTPAddrNtyUser[%d] failed.\n", wUserNums));
				break;
			}

			wUserNums = CTPAddrMgrEx::Instance().GetUserNty(ptTPAddrNtyUser, wUserNums);
				
			if(0 == wUserNums)
			{
				MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: CTPAddrMgrEx::Instance().GetUserNty failed.\n"));
				delete[] ptTPAddrNtyUser;
				ptTPAddrNtyUser = NULL;
				break;
			}
		}
		else
		{
			MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: Sip and gk all not end.\n"));
			break;
		}


		if (CTPAddrMgrEx::Instance().IsSipEnd())
		{
			wCnsNum = CTPAddrMgrEx::Instance().GetCnsPackNum();
			wUmsNum = CTPAddrMgrEx::Instance().GetUmsPackNum();

			if (0 != wCnsNum)
			{
				ptCnsInfo = new TCnsRegPackEx[wCnsNum];
				if (NULL == ptCnsInfo)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: new  TCnsRegPackEx[%d] failed.\n", wCnsNum));
					break;
				}

				wCnsNum = CTPAddrMgrEx::Instance().GetCnsRegPack(ptCnsInfo, wCnsNum);
				if (0 == wCnsNum)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: CTPAddrMgrEx::Instance().GetCnsRegPack failed.\n"));
					delete[] ptCnsInfo;
					ptCnsInfo = NULL;
					break;
				}
			}

			if (0 != wUmsNum)
			{
				ptUmsInfo = new TUmsRegPackEx[wUmsNum];
				if (NULL == ptUmsInfo)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: new  TUmsRegPackEx[%d] failed.\n", wUmsNum));
					break;
				}

				wUmsNum = CTPAddrMgrEx::Instance().GetUmsRegPack(ptUmsInfo, wUmsNum);
				if (0 == wUmsNum)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: CTPAddrMgrEx::Instance().GetUmsRegPack failed.\n"));
					delete[] ptUmsInfo;
					ptUmsInfo = NULL;
					break;
				}
			}

			CTPAddrMgrEx::Instance().ClearSipInfo();
		}

		if (CTPAddrMgrEx::Instance().IsGkEnd())
		{
			wMtNum  = CTPAddrMgrEx::Instance().GetMtPackNum();
			wMcuNum = CTPAddrMgrEx::Instance().GetMcuPackNum();

			if (0 != wMtNum)
			{
				ptMtInfo = new TTPMtRegInfo[wMtNum];
				if (NULL == ptMtInfo)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: new  TTPMtRegInfo[%d] failed.\n", wMtNum));
					break;
				}

				wMtNum = CTPAddrMgrEx::Instance().GetMtRegPack(ptMtInfo, wMtNum);
				if (0 == wMtNum)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: CTPAddrMgrEx::Instance().GetMtRegPack failed.\n"));
					delete[] ptMtInfo;
					ptMtInfo = NULL;
					break;
				}
			}

			if (0 != wMcuNum)
			{
				ptMcuInfo = new TTPMcuRegInfo[wMcuNum];
				if (NULL == ptMcuInfo)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: new  TTPMcuRegInfo[%d] failed.\n", wMcuNum));
					break;
				}

				wMcuNum = CTPAddrMgrEx::Instance().GetMcuRegPack(ptMcuInfo, wMcuNum);
				if (0 == wMcuNum)
				{
					MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx: CTPAddrMgrEx::Instance().GetMcuRegPack failed.\n"));
					delete[] ptMcuInfo;
					ptMcuInfo = NULL;
					break;
				}
			}

			CTPAddrMgrEx::Instance().ClearGkInfo();
		}

		bFlag = TRUE;

	} while (FALSE);

	if (bFlag)
	{
		MdlHint(Ums_Mdl_Service, ("PostRegInfoToUserEx UserNum:%d, CnsNum:%d, UmsNum:%d, MtNum:%d, McuNum:%d.\n",
								   wUserNums, wCnsNum, wUmsNum, wMtNum, wMcuNum));
		TLogUser tUser;
		for (u16 wIndex = 0; wIndex < wUserNums; ++wIndex)
		{
			tUser.m_dwUserNode = ptTPAddrNtyUser[wIndex].m_dwIID;
			tUser.m_dwUserInst = ptTPAddrNtyUser[wIndex].m_wUserData;

			u16 wPackIndex = 0;
			if (0 != wCnsNum && NULL != ptCnsInfo)
			{
				for (wPackIndex = 0; wPackIndex < wCnsNum; ++wPackIndex)
				{
					if (0 == wUmsNum && wPackIndex+1 == wCnsNum)
					{
						ptCnsInfo[wPackIndex].m_bIsEnd = TRUE;
					}
					else
					{
						ptCnsInfo[wPackIndex].m_bIsEnd = FALSE;
					}

					TpNotifyMsgToUeFromService(ev_umsGetRegInfo_CnsRspEx, &(ptCnsInfo[wPackIndex]), sizeof(TCnsRegPackEx), tUser);

					for (u16 wIndex = 0; wIndex <TP_CNS_MAX_REG_DATA; ++wIndex)
					{
						MdlLowHint(Ums_Mdl_Service, ("PostRegInfoToUserEx CnsAlias:%s.CnsAlias2:%s,IP:"TPIPFORMAT"\n",
							ptCnsInfo[wPackIndex].m_atRegInfo[wIndex].m_atAlias[0].m_abyAlias,
							ptCnsInfo[wPackIndex].m_atRegInfo[wIndex].m_atAlias[2].m_abyAlias,
							Tpu32ToIP(ptCnsInfo[wPackIndex].m_atRegInfo[wIndex].m_locolIP)));
					}
				}
			}

			if (0 != wUmsNum && NULL != ptUmsInfo)
			{
				for (wPackIndex = 0; wPackIndex < wUmsNum; ++wPackIndex)
				{
					if (wPackIndex + 1 == wUmsNum)
					{
						ptUmsInfo[wPackIndex].m_bIsEnd = TRUE;
					}
					else
					{
						ptUmsInfo[wPackIndex].m_bIsEnd = FALSE;
					}

					TpNotifyMsgToUeFromService(ev_umsGetRegInfo_UmsRspEx, &(ptUmsInfo[wPackIndex]), sizeof(TUmsRegPackEx), tUser);

// 					for (u16 wIndex = 0; wIndex < ptUmsInfo[wPackIndex].m_wSize; ++wIndex)
// 					{
// 						MdlLowHint(Ums_Mdl_Service, ("PostRegInfoToUserEx UmsAlias:%d.\n", ptUmsInfo[wPackIndex].m_atRegInfo[wIndex].m_wAliasNum));
// 					}
				}
			}

			if (0 != wMtNum && NULL != ptMtInfo)
			{
				for (wPackIndex = 0; wPackIndex < wMtNum; ++wPackIndex)
				{
					if (0 == wMcuNum && wPackIndex+1 == wMtNum)
					{
						ptMtInfo[wPackIndex].m_bIsEnd = TRUE;
					}
					else
					{
						ptMtInfo[wPackIndex].m_bIsEnd = FALSE;
					}

					TpNotifyMsgToUeFromService(ev_umsGetRegInfo_MtRspEx, &(ptMtInfo[wPackIndex]), sizeof(TTPMtRegInfo), tUser);
				}
			}

			if (0 != wMcuNum && NULL != ptMcuInfo)
			{
				for (wPackIndex = 0; wPackIndex < wMcuNum; ++wPackIndex)
				{
					if (wPackIndex + 1 == wMcuNum)
					{
						ptMcuInfo[wPackIndex].m_bIsEnd = TRUE;
					}
					else
					{
						ptMcuInfo[wPackIndex].m_bIsEnd = FALSE;
					}

					TpNotifyMsgToUeFromService(ev_umsGetRegInfo_McuRspEx, &(ptMcuInfo[wPackIndex]), sizeof(TTPMcuRegInfo), tUser);
				}
			}
		}
	}

	if (NULL != ptTPAddrNtyUser)
	{
		delete[] ptTPAddrNtyUser;
	}

	if (NULL != ptCnsInfo)
	{
		delete[] ptCnsInfo;
	}

	if (NULL != ptUmsInfo)
	{
		delete[] ptUmsInfo;
	}

	if (NULL != ptMtInfo)
	{
		delete[] ptMtInfo;
	}

	if (NULL != ptMcuInfo)
	{
		delete[] ptMcuInfo;
	}
}

void CUmsRegHandleService::PostRegInfoToUser(TLogUser& tUser, const EmGetRegInfoType& tType)
{
	u16 wPackNums = CTPAddrMgr::GetInstance()->GetPackTotalNum(tType);
	TTPSipRegInfo *ptSipRegInfo = new TTPSipRegInfo[wPackNums];

	if (NULL == ptSipRegInfo) 
	{
		MdlHint(Ums_Mdl_Service, ("PostRegInfoToUser error: new  TTPSipRegInfo[%d] failed.\n", wPackNums));
		return ;
	}

	if (!CTPAddrMgr::GetInstance()->GetPack(tType, ptSipRegInfo, wPackNums))
	{
		MdlHint(Ums_Mdl_Service, ("PostRegInfoToUser error: CTPAddrMgr::GetInstance()->GetPack failed.\n"));
		delete[] ptSipRegInfo;
		return ;
	}

	u8 abRes[sizeof(TTPSipRegPackInfo)+sizeof(EmGetRegInfoType)+sizeof(TTPSipRegInfo)] = {0};

	TTPSipRegPackInfo* ptResPackInfo = (TTPSipRegPackInfo*)abRes;
	EmGetRegInfoType* ptResType = (EmGetRegInfoType*)(abRes + sizeof(TTPSipRegPackInfo));
	TTPSipRegInfo* ptResRegInfo = (TTPSipRegInfo*)(abRes + sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType));
	*ptResType = tType;
	if (0 == wPackNums)
	{
		ptResPackInfo->m_wTotalPackNum = 0;
		ptResPackInfo->m_wPackSeq = 0;
		TpNotifyMsgToUeFromService(ev_umsGetRegInfo_Rsp, abRes, sizeof(abRes), tUser);
	}
	else
	{
		ptResPackInfo->m_wTotalPackNum = wPackNums;
			
		for (u16 wIndex = 0; wIndex < wPackNums; ++wIndex)
		{
			ptResPackInfo->m_wPackSeq = wIndex + 1;
			*ptResRegInfo = ptSipRegInfo[wIndex];
			TpNotifyMsgToUeFromService(ev_umsGetRegInfo_Rsp, abRes, sizeof(abRes), tUser);
		}
	}

	delete[] ptSipRegInfo;
}

void CUmsRegHandleService::Register( EmRegGroupNum emRegGroupNum, EmRegType emRegType)
{
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	CUmsConfTemplateHandleService* pConfService = (CUmsConfTemplateHandleService*)pServer->GetService(CTpUmsServer::_CUmsConfTemplateHandleService);

	TTPAlias atAlias[TP_CONFTEMPGROUP_MAXNUM];
	u16		 wAliasNum = 0;
	CTpMsg	 cMsg;
	u16 wGroupIndex = 0;
	u16 wGroupIndexEnd = 0;

	if (em_AllGroup == emRegGroupNum)
	{
		wGroupIndex = 0;
		wGroupIndexEnd = TP_TEMPGROUP_MAXNUM;
	}
	else
	{
		wGroupIndex = emRegGroupNum;
		wGroupIndexEnd = wGroupIndex + 1;
	}

	EmRegGroupNum emTmp = em_AllGroup;

	for(; wGroupIndex < wGroupIndexEnd; wGroupIndex++)
	{
		switch(wGroupIndex)
		{
		case 0:
			{
				emTmp = em_FirstGroup;
			}
			break;
			
		case 1:
			{
				emTmp = em_SecondGroup;
			}
			break;
			
		case 2:
			{
				emTmp = em_ThirdGroup;
			}
			break;
			
		case 3:
			{
				emTmp = em_FourthGroup;
			}
			break;
			
		default:
			{
				emTmp = em_AllGroup;
			}
			break;
			
		}

		memset(atAlias, 0, sizeof(atAlias));
		memset(&cMsg, 0, sizeof(CTpMsg));

		if(em_AllGroup == emTmp)
		{
			continue;
		}

		wAliasNum = pConfService->GetConfTemplateAlias(atAlias, TP_CONFTEMPGROUP_MAXNUM, emTmp);
		if (0 == wAliasNum)
		{// 
			UnRegister(emRegType, emTmp, TRUE);
			ClearRegRet(emRegType, emTmp);
			continue;
		}

		//m_atRegRet[emTmp][emRegType].m_emRegState = em_reging;

		cMsg.SetEvent(evtp_ums_reg_req);
		cMsg.SetBody(&emRegType,sizeof(EmRegType));
		cMsg.CatBody(&emTmp,sizeof(EmRegGroupNum));
		switch (emRegType)
		{
		case em_Sip_reg_type:
			{
				cMsg.CatBody(&m_tSipRegCfg, sizeof(m_tSipRegCfg));
			}
			break;
				
		case em_Gk_reg_type:
			{
				cMsg.CatBody(&m_tGKRegCfg, sizeof(m_tGKRegCfg));
			}
			break;
		}
			
		cMsg.CatBody(&wAliasNum, sizeof(wAliasNum));
		for (u16 wIndex = 0; wIndex < wAliasNum; ++wIndex)
		{
			cMsg.CatBody(&atAlias[wIndex], sizeof(TTPAlias));
		}
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));
	}
}


void CUmsRegHandleService::UnRegister(EmRegType emRegType, EmRegGroupNum emGroupNum /* = em_AllGroup */, BOOL32 bForce /* = FALSE */)
{
	switch (emRegType)
	{	
	case em_Sip_reg_type:
		{
			MdlHint(Ums_Mdl_Service, ("UnRegister: UnRegType:%d, UnRegIP:("ADDRPORT_FORMAT"), GroupNum:%d\n", 
					emRegType, ADDRPORT(m_tSipRegCfg.dwRegIP, m_tSipRegCfg.wRegPort), emGroupNum));
		}
		break;

	case em_Gk_reg_type:
		{
			MdlHint(Ums_Mdl_Service, ("UnRegister: UnRegType:%d, UnRegIP:("TPIPFORMAT"), GroupNum:%d\n", 
					emRegType, Tpu32ToIP(m_tGKRegCfg.dwGKIP), emGroupNum));
		}
		break;

	default:		
		{	
			MdlHint(Ums_Mdl_Service, ("UnRegister: Unknow UnRegType:%d\n", emRegType));
			return ;
		}
	}

	//只取消已经注册成功或者正在注册的数据包
	if (em_AllGroup == emGroupNum)
	{
		EmRegGroupNum emTmp = em_AllGroup;
		for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
		{
			if (em_reging == m_atRegRet[wIndex][emRegType].m_emRegState ||
				em_reg_success == m_atRegRet[wIndex][emRegType].m_emRegState ||
				em_reg_failed == m_atRegRet[wIndex][emRegType].m_emRegState || bForce)
			{
				switch(wIndex)
				{
				case 0:
					{
						emTmp = em_FirstGroup;
					}
					break;
					
				case 1:
					{
						emTmp = em_SecondGroup;
					}
					break;
					
				case 2:
					{
						emTmp = em_ThirdGroup;
					}
					break;
					
				case 3:
					{
						emTmp = em_FourthGroup;
					}
					break;
					
				default:
					{
						emTmp = em_AllGroup;
					}
					break;			
				}
				CTpMsg cMsg;
				cMsg.SetEvent(evtp_ums_unreg_req);
				cMsg.SetBody(&emRegType, sizeof(EmRegType));
				cMsg.CatBody(&emTmp, sizeof(EmRegGroupNum));
				cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));
			}
		}
	}
	else
	{	
		if (em_reging == m_atRegRet[emGroupNum][emRegType].m_emRegState ||
			em_reg_success == m_atRegRet[emGroupNum][emRegType].m_emRegState ||
			em_reg_failed == m_atRegRet[emGroupNum][emRegType].m_emRegState || bForce)
		{
			CTpMsg cMsg;
			cMsg.SetEvent(evtp_ums_unreg_req);
			cMsg.SetBody(&emRegType, sizeof(EmRegType));
			cMsg.CatBody(&emGroupNum, sizeof(EmRegGroupNum));
			cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));
		}
	}
}

void CUmsRegHandleService::EventSetGkRegCfg(u8* pDataBuf, u16 wDataSize)
{
	TLogUser	tUser;
	TTPGKCfg	tGkRegCfg;

	TP_SAFE_CAST(tUser, pDataBuf);
	TP_SAFE_CAST(tGkRegCfg, pDataBuf + sizeof(TLogUser));
	tGkRegCfg.wExpire = TP_EXPIRE_TIME;
	umsSetGKRegCfg(tGkRegCfg);

	MdlHint(Ums_Mdl_Service, ("EventSetGkRegCfg old ("ADDRPORT_FORMAT"), new ("ADDRPORT_FORMAT")\n"
		    , ADDRPORT(m_tGKRegCfg.dwGKIP, m_tGKRegCfg.wRegPort), ADDRPORT(tGkRegCfg.dwGKIP, tGkRegCfg.wRegPort)));

	if (tGkRegCfg.dwGKIP  != m_tGKRegCfg.dwGKIP || 
		tGkRegCfg.bUsed   != m_tGKRegCfg.bUsed)
	{
		if (IsReg(em_Gk_reg_type))
		{
			UnRegister(em_Gk_reg_type);
		}
		ClearRegRet(em_Gk_reg_type);
		memcpy(&m_tGKRegCfg, &tGkRegCfg, sizeof(m_tGKRegCfg));


		TTPQTEncryptInfo tTPQTEncryptInfo;
		umsGetQTEncryptInfo(tTPQTEncryptInfo);
		m_tGKRegCfg.m_dwQtID = tTPQTEncryptInfo.m_dwQuanTumID;

		//同步更新GK配置信息到umsreg
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_GK_Cfg_Update);
		cMsg.SetBody(&m_tGKRegCfg,sizeof(TTPGKCfg));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));

		if (m_tGKRegCfg.bUsed)
		{
			SetGroupReging(em_Gk_reg_type, em_AllGroup);
			Register( em_AllGroup, em_Gk_reg_type);
		}
	}	

	TLogUser tUserTmp;
	TpNotifyMsgToUeFromService(ev_umsGKReg_notify, &m_tGKRegCfg, sizeof(m_tGKRegCfg), tUserTmp);

	NotifyRegInfoToTpTool();
}


void CUmsRegHandleService::EventSetRegCfg(u8* pDataBuf, u16 wDataSize)
{
	TLogUser			tUser;
	TTPSipRegistrarCfg	tRegCfg;

	TP_SAFE_CAST(tUser, pDataBuf);
	TP_SAFE_CAST(tRegCfg, pDataBuf + sizeof(TLogUser));
	tRegCfg.wRegPort = TP_UMS_SIP_LISTIEN_PORT;
	tRegCfg.wExpire = TP_ROUNDTRIP_TIME;
	umsSetSipRegCfg(tRegCfg);

	MdlHint(Ums_Mdl_Service, ("EventSetRegCfg old ("ADDRPORT_FORMAT"), new ("ADDRPORT_FORMAT")\n"
		    , ADDRPORT(m_tSipRegCfg.dwRegIP, m_tSipRegCfg.wRegPort), ADDRPORT(tRegCfg.dwRegIP, tRegCfg.wRegPort)));

	if (tRegCfg.dwRegIP  != m_tSipRegCfg.dwRegIP  ||  
		tRegCfg.bUsed    != m_tSipRegCfg.bUsed)
	{
		if (IsReg(em_Sip_reg_type))
		{
			UnRegister(em_Sip_reg_type);
		}
		ClearRegRet(em_Sip_reg_type);
		memcpy(&m_tSipRegCfg, &tRegCfg, sizeof(m_tSipRegCfg));

		TTPQTEncryptInfo tTPQTEncryptInfo;
		umsGetQTEncryptInfo(tTPQTEncryptInfo);
		m_tSipRegCfg.m_dwQtID = tTPQTEncryptInfo.m_dwQuanTumID;

		//add 更新sip配置信息到umsreg
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_Sip_Cfg_Update);
		cMsg.SetBody(&m_tSipRegCfg, sizeof(TTPSipRegistrarCfg));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));

		if (m_tSipRegCfg.bUsed)
		{
			SetGroupReging(em_Sip_reg_type, em_AllGroup);
			Register( em_AllGroup, em_Sip_reg_type);
		}
	}
	
	TLogUser tUserTmp;
	TpNotifyMsgToUeFromService(ev_umsreg_notify, &m_tSipRegCfg, sizeof(m_tSipRegCfg), tUserTmp);

	NotifyRegInfoToTpTool();
}


void CUmsRegHandleService::EventRegRet(u8* pData, u16 wDataSize)
{
	EmRegType        emRegType = em_Sip_reg_type;
	TCnsRegRetResult tCnsRegResult;
	u16				 wGroupIndex;

	TP_SAFE_CAST(emRegType, pData);
	TP_SAFE_CAST(tCnsRegResult, pData+sizeof(EmRegType));
	TP_SAFE_CAST(wGroupIndex, pData+sizeof(EmRegType)+sizeof(TCnsRegRetResult));

	if (wGroupIndex >= TP_TEMPGROUP_MAXNUM || emRegType >= em_reg_type_end)
	{
		MdlHint(Ums_Mdl_Service, ("EventRegRet Unknow param!!! GroupIndex:%d, type:%d.\n", wGroupIndex, emRegType));
		return;
	}
	
	if (em_un_reg == m_atRegRet[wGroupIndex][emRegType].m_emRegState)
	{
		MdlHint(Ums_Mdl_Service, ("EventRegRet error state!!! GroupIndex:%d, type:%d, state:%d.\n", 
			wGroupIndex, emRegType, m_atRegRet[wGroupIndex][emRegType].m_emRegState));
		return;
	}

	TLogUser        tLogUser;
	TUCSipRegResult tRegRet;
	tRegRet.m_emTpCnsRegUms = tCnsRegResult.m_emReson;

	switch (emRegType)
	{
	case em_Sip_reg_type:
		{
			if (tp_CnsRegRet_Success == tCnsRegResult.m_emReson)
			{
				if (em_reg_success != m_atRegRet[wGroupIndex][emRegType].m_emRegState && m_tSipRegCfg.bUsed)
				{
					TpNotifyMsgToUeFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet), tLogUser);
					TpNotifyMsgToToolUserFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet));
				}
				
				m_atRegRet[wGroupIndex][emRegType].m_emRegState = em_reg_success;

				if (!m_bReqRegInfo)
				{
					m_bReqRegInfo = TRUE;
					
					//注册成功，发送查询消息
					EmGetRegInfoType tReqType = emGetRegInfoType_ALL;
					CTpMsg cMsg;
					cMsg.SetEvent(ev_ums_GetRegInfo_Req);
					cMsg.SetBody(&tReqType,sizeof(EmGetRegInfoType));
					cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));
				}
			}
			else
			{
				if (em_reg_failed != m_atRegRet[wGroupIndex][emRegType].m_emRegState && m_tSipRegCfg.bUsed)
				{
					TpNotifyMsgToUeFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet), tLogUser);
					TpNotifyMsgToToolUserFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet));
				}
				m_atRegRet[wGroupIndex][emRegType].m_emRegState = em_reg_failed;
			}

			break;
		}
	case em_Gk_reg_type:
		{
			if (tp_CnsRegRet_Success == tCnsRegResult.m_emReson)
			{	
				if (em_reg_success != m_atRegRet[wGroupIndex][emRegType].m_emRegState && m_tGKRegCfg.bUsed)
				{
					TpNotifyMsgToUeFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet), tLogUser);
					TpNotifyMsgToToolUserFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet));
				}
				m_atRegRet[wGroupIndex][emRegType].m_emRegState = em_reg_success;
			}
			else
			{
				if (em_reg_failed != m_atRegRet[wGroupIndex][emRegType].m_emRegState && m_tGKRegCfg.bUsed)
				{
					TpNotifyMsgToUeFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet), tLogUser);
					TpNotifyMsgToToolUserFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet));
				}
				m_atRegRet[wGroupIndex][emRegType].m_emRegState = em_reg_failed;
			}
			
			break;
		}
	}

	m_atRegRet[wGroupIndex][emRegType].m_emReason = tCnsRegResult.m_emReson;

	NotifyRegInfoToTpTool();
}

void CUmsRegHandleService::EventUnRegRet(u8* pData, u16 wDataSize)
{
	EmRegType emRegType;
	TUCSipRegResult tSipRegResult;
	u16 wGroupIndex;

	TP_SAFE_CAST(emRegType, pData);
	TP_SAFE_CAST(tSipRegResult, pData+sizeof(EmRegType));
	TP_SAFE_CAST(wGroupIndex, pData+sizeof(EmRegType)+sizeof(TUCSipRegResult));

	if (wGroupIndex >= TP_TEMPGROUP_MAXNUM || emRegType >= em_reg_type_end)
	{
		MdlHint(Ums_Mdl_Service, ("EventUnRegRet Unknow param!!! GroupIndex:%d, type:%d.\n", wGroupIndex, emRegType));
		return;
	}

	if (em_un_reg == m_atRegRet[wGroupIndex][emRegType].m_emRegState)
	{
		MdlHint(Ums_Mdl_Service, ("EventUnRegRet error state!!! GroupIndex:%d, type:%d, state:%d.\n", 
			wGroupIndex, emRegType, m_atRegRet[wGroupIndex][emRegType].m_emRegState));
		return;
	}

	TLogUser tLogUser;
	switch (emRegType)
	{
	case em_Sip_reg_type:
		{
			if (em_reg_failed != m_atRegRet[wGroupIndex][emRegType].m_emRegState && m_tSipRegCfg.bUsed)
			{
				TpNotifyMsgToUeFromService(ev_umsRegResult_notify, &tSipRegResult, sizeof(tSipRegResult), tLogUser);
				TpNotifyMsgToToolUserFromService(ev_umsRegResult_notify, &tSipRegResult, sizeof(tSipRegResult));
			}
			m_atRegRet[wGroupIndex][emRegType].m_emRegState = em_reg_failed;
		}
		break;

	case em_Gk_reg_type:
		{
			if (em_reg_failed != m_atRegRet[wGroupIndex][emRegType].m_emRegState && m_tGKRegCfg.bUsed)
			{
				TpNotifyMsgToUeFromService(ev_umsGKReg_ret, &tSipRegResult, sizeof(tSipRegResult), tLogUser);
			}
			m_atRegRet[wGroupIndex][emRegType].m_emRegState = em_reg_failed;
		}
		break;

	default:
		{
			MdlHint(Ums_Mdl_Service, ("EventUnRegRet Unknow reg type:%d.\n", emRegType));
			return ;
		}
	}

	m_atRegRet[wGroupIndex][emRegType].m_emReason = tSipRegResult.m_emTpCnsRegUms;

	NotifyRegInfoToTpTool();
}

void CUmsRegHandleService::EventAdapterRegOut(u8* pData, u16 wDataSize)
{
	BOOL32 bOnline = FALSE;
	TP_SAFE_CAST(bOnline, pData);

	if (bOnline)
	{
		if (m_tSipRegCfg.bUsed)
		{
			SetGroupReging(em_Sip_reg_type, em_AllGroup);
			Register( em_AllGroup, em_Sip_reg_type);
		}

		if (m_tGKRegCfg.bUsed)
		{
			SetGroupReging(em_Gk_reg_type, em_AllGroup);
			Register( em_AllGroup, em_Gk_reg_type);
		}
	}
	else
	{
		TLogUser tLogUser;
		TUCSipRegResult tRegRet;
		tRegRet.m_emTpCnsRegUms = tp_CnsRegRet_UnRegister;
		
		for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
		{
			if (em_reg_success == m_atRegRet[wIndex][em_Sip_reg_type].m_emRegState && m_tSipRegCfg.bUsed)
			{
				TpNotifyMsgToUeFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet), tLogUser);
				TpNotifyMsgToToolUserFromService(ev_umsRegResult_notify, &tRegRet, sizeof(tRegRet));
			}
			
			if (em_reg_success == m_atRegRet[wIndex][em_Gk_reg_type].m_emRegState && m_tGKRegCfg.bUsed)
			{
				TpNotifyMsgToUeFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet), tLogUser);
				TpNotifyMsgToToolUserFromService(ev_umsGKReg_ret, &tRegRet, sizeof(tRegRet));
			}
		}
		
		ClearRegRet(em_Sip_reg_type);
		ClearRegRet(em_Gk_reg_type);
		
		NotifyRegInfoToTpTool();
	}

	return;
}

void CUmsRegHandleService::EventUpdateReg(const EmRegGroupNum& emGroupNum,BOOL32 bUpdateQtID/* = FALSE */)
{
	//暂时不需要提供更新全部的功能
	if (em_AllGroup == emGroupNum)
	{
		return ;
	}

	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	CUmsConfTemplateHandleService* pConfService = (CUmsConfTemplateHandleService*)pServer->GetService(CTpUmsServer::_CUmsConfTemplateHandleService);

	TTPAlias atAlias[TP_CONFTEMPGROUP_MAXNUM];
	u16		 wAliasNum = 0;
	CTpMsg	 cMsg;

	memset(atAlias, 0, sizeof(atAlias));
	memset(&cMsg, 0, sizeof(CTpMsg));

	wAliasNum = pConfService->GetConfTemplateAlias(atAlias, TP_CONFTEMPGROUP_MAXNUM, emGroupNum);
	//当前更新包别名为空，如果当前包之前已经注册成功，则取消注册
	if (0 == wAliasNum)
	{
		MdlHint(Ums_Mdl_Service, ("EventUpdateReg AliasNum:%d, GroupNum:%d.\n", wAliasNum, emGroupNum));

		UnRegister(em_Sip_reg_type, emGroupNum, TRUE);
		ClearRegRet(em_Sip_reg_type, emGroupNum);

		UnRegister(em_Gk_reg_type, emGroupNum, TRUE);
		ClearRegRet(em_Gk_reg_type, emGroupNum);
	}
	else
	{
		MdlHint(Ums_Mdl_Service, ("EventUpdateReg GroupNum:%d.\n", emGroupNum));
		//如果数据包正在注册，则取消注册
		if (em_reging == m_atRegRet[emGroupNum][em_Sip_reg_type].m_emRegState)
		{
			UnRegister(em_Sip_reg_type, emGroupNum);
		}
		else if (em_un_reg == m_atRegRet[emGroupNum][em_Sip_reg_type].m_emRegState)
		{
			SetGroupReging(em_Sip_reg_type, emGroupNum);
		}

		Register(emGroupNum, em_Sip_reg_type);

		if (em_reging == m_atRegRet[emGroupNum][em_Gk_reg_type].m_emRegState ||bUpdateQtID)
		{
			UnRegister(em_Gk_reg_type, emGroupNum);
		}
		else if (em_un_reg == m_atRegRet[emGroupNum][em_Gk_reg_type].m_emRegState)
		{
			SetGroupReging(em_Gk_reg_type, emGroupNum);
		}
		UnRegister(em_Gk_reg_type, emGroupNum);
		Register(emGroupNum, em_Gk_reg_type);
	}

	NotifyRegInfoToTpTool();
}

void CUmsRegHandleService::ClearRegRet(const EmRegType& emRegType, const EmRegGroupNum& emGroupNums /* = em_AllGroup */)
{
	if (em_reg_type_end == emRegType)
	{
		return ;
	}

	switch (emGroupNums)
	{
	case em_FirstGroup:
		{
			m_atRegRet[0][emRegType].Clear();
		}
		break;
			
	case em_SecondGroup:
		{
			m_atRegRet[1][emRegType].Clear();
		}
		break;

	case em_ThirdGroup:
		{
			m_atRegRet[2][emRegType].Clear();
		}
		break;

	case em_FourthGroup:
		{
			m_atRegRet[3][emRegType].Clear();
		}
		break;

	case em_AllGroup:
		{
			for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
			{
				m_atRegRet[wIndex][emRegType].Clear();
			}
		}
		break;
	}
}

void CUmsRegHandleService::SetGroupReging(const EmRegType& emRegType, const EmRegGroupNum& emGroupNums /* = em_AllGroup */)
{
	if (em_reg_type_end == emRegType)
	{
		return ;
	}
	
	switch (emGroupNums)
	{
	case em_FirstGroup:
		{
			m_atRegRet[0][emRegType].m_emRegState = em_reging;
			m_atRegRet[0][emRegType].m_emReason = tp_CnsRegRet_Unknow;
		}
		break;
		
	case em_SecondGroup:
		{
			m_atRegRet[1][emRegType].m_emRegState = em_reging;
			m_atRegRet[1][emRegType].m_emReason = tp_CnsRegRet_Unknow;
		}
		break;
		
	case em_ThirdGroup:
		{
			m_atRegRet[2][emRegType].m_emRegState = em_reging;
			m_atRegRet[2][emRegType].m_emReason = tp_CnsRegRet_Unknow;
		}
		break;
		
	case em_FourthGroup:
		{
			m_atRegRet[3][emRegType].m_emRegState = em_reging;
			m_atRegRet[3][emRegType].m_emReason = tp_CnsRegRet_Unknow;
		}
		break;
		
	case em_AllGroup:
		{
			for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
			{
				m_atRegRet[wIndex][emRegType].m_emRegState = em_reging;
				m_atRegRet[wIndex][emRegType].m_emReason = tp_CnsRegRet_Unknow;
			}
		}
		break;
	}
}

BOOL32 CUmsRegHandleService::IsRegOneGroup(const EmRegType& emRegType) const
{
	if (em_reg_type_end == emRegType)
	{
		return FALSE;
	}

	for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		if (em_reg_success == m_atRegRet[wIndex][emRegType].m_emRegState)
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL32 CUmsRegHandleService::IsReg(const EmRegType& emRegType)
{
	if (em_reg_type_end == emRegType)
	{
		return FALSE;
	}

	for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		if (em_reging == m_atRegRet[wIndex][emRegType].m_emRegState ||
			em_reg_success == m_atRegRet[wIndex][emRegType].m_emRegState ||
			em_reg_failed == m_atRegRet[wIndex][emRegType].m_emRegState)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void  CUmsRegHandleService::UpdateReg(const EmRegGroupNum emGroupNum)
{
	 MdlHint(Ums_Mdl_Service, ("EventUpdateReg GroupNum:%d.\n", emGroupNum));
     EventUpdateReg(emGroupNum,TRUE);
}

void  CUmsRegHandleService::UpdateQtId(const u32 dwQtid)
{
    m_tSipRegCfg.m_dwQtID = dwQtid;
    m_tGKRegCfg.m_dwQtID = dwQtid;
}

void CUmsRegHandleService::ShowRegState()
{
	for (u16 wIndex = 0; wIndex < TP_TEMPGROUP_MAXNUM; ++wIndex)
	{
		msgprintnotime("ShowRegState GroupIndex:%d, SipReg:%d, SipReason:%d, GkReg:%d, GkReason:%d.\n", 
								  wIndex+1, m_atRegRet[wIndex][em_Sip_reg_type].m_emRegState, 
								  m_atRegRet[wIndex][em_Sip_reg_type].m_emReason,
								  m_atRegRet[wIndex][em_Gk_reg_type].m_emRegState, 
								  m_atRegRet[wIndex][em_Gk_reg_type].m_emReason);
	}
}