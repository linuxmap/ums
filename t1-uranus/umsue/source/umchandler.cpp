#include "umchandler.h"
#include "ueinterface.h"
#include "umsueinit.h"
#include "umsxmltype.h"

#include "innereventumsserver.h"

// 外部消息
#include "eventoutumslogin.h"
#include "eventoutumshdu2.h"
#include "eventoutumscfg.h"
#include "eventoutumscall.h"
#include "eventoutumsreg.h"
#include "eventoutumsconftemplate.h"
#include "eventoutcfgex.h"
#include "eventoutumstool.h"
#include "eventoutumsboard.h"

API void switchssh(BOOL32 bIson);
extern TUmsUeCfg g_cUmsUeCfg;

CUmcHandler::CUmcHandler(CTpObject* pcObject, u32 dwUmcAppID)
						: CTpHandler(pcObject)
						, m_cUserMG((u8*)g_cUmsUeCfg.m_acUsrInfoFilePath)
{
	m_dwUmcAppID = dwUmcAppID;

	CUserFullInfo cUser;
	cUser.m_dwGuid = 1;
	cUser.SetActor(UM_ADMIN);
	cUser.SetName(UMS_UserName);
	cUser.SetPassword(UMS_PassWord);
	m_cUserMG.ModifyInfo(&cUser);

	m_tLogUser.Create(10);
	for (u32 dwIndex = 0; dwIndex < m_tLogUser.MaxSize(); ++dwIndex)
	{
		m_tLogUser[dwIndex].m_dwUserID = dwIndex + 1;
	}
}

CUmcHandler::~CUmcHandler()
{
	m_tLogUser.Destroy();
}

BOOL32 CUmcHandler::Handler(CTpMsg* const ptMsg)
{
	u16 wEvent	= ptMsg->GetEvent();
	CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();

	u16 wAppID	= GETAPP(ptMsg->GetSrcIId());
	//界面到业务
	if (wAppID == GETAPP(m_dwUmcAppID))
	{
		TLogUser tLogUser;
		tLogUser.m_dwUserNode = ptMsg->GetSrcNode();
		CTpVector<TLogUser>::iterator Itor = m_tLogUser.Find(tLogUser);
		
		if (Itor != m_tLogUser.end())
		{
			pUeInst->NotifyMsgToService(wEvent, ptMsg->GetBody(), ptMsg->GetBodyLen(), *Itor);
		}
		else
		{
			MdlHint(Ums_Mdl_Ue, ("Umc Unknow User. SrcNode:%d, Msg:%d-%s\n", ptMsg->GetSrcNode(), wEvent, GetEventNamebyID(wEvent)));
		}

		PrintEventInfoFromUI(ptMsg);
	}
	else
	{
		TLogUser* pLogUser	= (TLogUser*)ptMsg->GetBody();
		void* pDataBuf		= ptMsg->GetBody() + sizeof(TLogUser);
		u16 wDataSize		= ptMsg->GetBodyLen() - sizeof(TLogUser);
		u16 wEvent			= ptMsg->GetEvent();
		
		CTpMsg cMsg;
		cMsg.SetEvent(wEvent);
		cMsg.SetBody(pDataBuf, wDataSize);

		if (pLogUser->m_dwUserNode == 0)
		{//广播消息
			for (CTpVector<TLogUser>::iterator Itor = m_tLogUser.begin(); Itor != m_tLogUser.end(); ++Itor)
			{
				if (!Itor->Invalid())
				{
					if ( evtp_AddConftemplate_Notify1 == wEvent || evtp_Updateconftemplate_Notify1 == wEvent || ev_hduPlan_Nty == wEvent)
					{//模板直接 发送
						::OspPost(Itor->m_dwUserInst, wEvent, pDataBuf, wDataSize, Itor->m_dwUserNode, UMS_UE_APP_INST);
					}
					else
					{
						cMsg.Post(Itor->m_dwUserInst, Itor->m_dwUserNode, UMS_UE_APP_INST);
					}
				}
			}
		}
		else
		{//单播消息
			if ( evtp_AddConftemplate_Notify1 == wEvent || evtp_Updateconftemplate_Notify1 == wEvent || ev_hduPlan_Nty == wEvent)
			{//模板直接 发送
				::OspPost(pLogUser->m_dwUserInst, wEvent, pDataBuf, wDataSize, pLogUser->m_dwUserNode, UMS_UE_APP_INST);
			}
			else
			{
				cMsg.Post(pLogUser->m_dwUserInst, pLogUser->m_dwUserNode, UMS_UE_APP_INST);
			}
		}
		PrintEventInfo(ptMsg);
	}

	return TRUE;
}

BOOL32 CUmcHandler::PreHandler(CMessage *const ptMsg)
{

	switch (ptMsg->event)
	{
	case ev_UMSLoginReq:
		{
			EventUserLogin(ptMsg);
		}
		break;
	case ev_UMSAddUserReq:
		{
			EventAddUserReq(ptMsg);
		}
		break;
	case ev_UMSDelUserReq:
		{	
			EventDelUser(ptMsg);
		}
		break;
	case ev_UMSChangePWDReq:
		{
			EventChangePwdReq(ptMsg);
		}
		break;
	case evtp_AddConfTemplate_req1:
		{
			TLogUser tLogUser;
			tLogUser.m_dwUserNode = ptMsg->srcnode;
			CTpVector<TLogUser>::iterator Itor = m_tLogUser.Find(tLogUser);
			if ( Itor != m_tLogUser.end())
			{
				CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();
				pUeInst->NotifyMsgToService( evtp_AddConfTemplate_req1, ptMsg->content, ptMsg->length, *Itor );
			}
		}
		break;	
	case evtp_Updateconftemplate_Req1:
		{
			TLogUser tLogUser;
			tLogUser.m_dwUserNode = ptMsg->srcnode;
			CTpVector<TLogUser>::iterator Itor = m_tLogUser.Find(tLogUser);
			if ( Itor != m_tLogUser.end() )
			{
				CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();
				pUeInst->NotifyMsgToService( evtp_Updateconftemplate_Req1, ptMsg->content, ptMsg->length, *Itor );
			}
		}
		break;
	case evtp_StartInterimMeeting_Req:
		{

			TTPConfMeet tMeet = *(TTPConfMeet*)(ptMsg->content);
			MdlHint(Ums_Mdl_Ue, ("evtp_StartInterimMeeting_Req, tempID:%d, name:%s,name1:%s,format:%d\n", 
				tMeet.m_wID, 
				tMeet.m_achConfName,
				tMeet.m_atEpList.m_tCnsList[0].m_tEpAddr.m_tAlias.m_abyAlias,
				tMeet.m_wAudFmtNum));

			TLogUser tLogUser;
			tLogUser.m_dwUserNode = ptMsg->srcnode;
			CTpVector<TLogUser>::iterator Itor = m_tLogUser.Find(tLogUser);
			if ( Itor != m_tLogUser.end())
			{
				CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();
				pUeInst->NotifyMsgToService( evtp_StartInterimMeeting_Req, ptMsg->content, ptMsg->length, *Itor );
			}
		}
		break;
	case OSP_DISCONNECT:
		{
			EventDisconnect(ptMsg);
		}
		break;

	}
	return TRUE;
}

void CUmcHandler::EventDisconnect(CMessage* const ptMsg)
{
 	u32 dwNode = *(u32*)ptMsg->content;

 	TLogUser tLogUser;
 	tLogUser.m_dwUserNode = dwNode;
	
 	CTpVector<TLogUser>::iterator Itor = m_tLogUser.Del(tLogUser);
 	if (Itor != m_tLogUser.end())
 	{
		CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();
		pUeInst->NotifyMsgToService( ev_SysCmsLogoutInd, NULL, 0, *Itor );

 		MdlHint(Ums_Mdl_Ue, ("Umc Disconnect. Name:%s\n", Itor->m_achName));	
		Itor->Clear();
 	}
	if (m_tLogUser.size() == 0)
	{
		switchssh(TRUE);
	}
}

void CUmcHandler::EventChangePwdReq(CMessage* const ptMsg)
{
	CUserFullInfo tUser ;
	TP_SAFE_CAST( tUser, ptMsg->content );
	
	MdlHint(Ums_Mdl_Ue, ("Umc Change user pwd Req. Name:%s, Pwd:%s\n", tUser.GetName(), tUser.GetPassword()));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UMSChangePWDRet);
	
	EmTpRet emRet = tp_Ret_FAILED;
	u16 errcode = 0;
	
	if(m_cUserMG.ModifyInfo(&tUser))
	{
		emRet = tp_Ret_Success;
		
		cMsg.SetBody(&emRet, sizeof(emRet));
		cMsg.CatBody(&errcode, sizeof(errcode));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode, UMS_UE_APP_INST);
		
		//发送此用户信息给所有用户
		CTpVector<TLogUser>::iterator Itor;
		for (Itor = m_tLogUser.begin(); Itor != m_tLogUser.end(); ++Itor)
		{
			if (!Itor->Invalid())
			{
				::OspPost(Itor->m_dwUserInst, ev_UmsUpdateUser_Notify, &tUser, sizeof(tUser), Itor->m_dwUserNode, UMS_UE_APP_INST);
			}
		}

		MdlHint(Ums_Mdl_Ue, ("Umc Change user pwd success. Name:%s, Pwd:%s\n", tUser.GetName(), tUser.GetPassword()));
	}
	else
	{
		errcode = m_cUserMG.GetLastError();
		
		cMsg.SetBody(&emRet, sizeof(emRet));
		cMsg.CatBody(&errcode, sizeof(errcode));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode, UMS_UE_APP_INST);
		
		MdlHint(Ums_Mdl_Ue, ("Umc Change user pwd failed. Name:%s, Pwd:%s, ErrorCode:%d\n", tUser.GetName(),tUser.GetPassword(), errcode));
	}
}

void CUmcHandler::EventDelUser(CMessage* const ptMsg)
{
	CUserFullInfo tUser;
	TP_SAFE_CAST(tUser, ptMsg->content);
	
	MdlHint(Ums_Mdl_Ue, ("Umc Del user. Name:%s, Pwd:%s\n", tUser.GetName(), tUser.GetPassword()));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UMSDelUserRet);
	
	EmTpRet emRet = tp_Ret_FAILED;
	u16 errcode = 0;
	if(m_cUserMG.DelUser(&tUser))
	{
		emRet = tp_Ret_Success;
		cMsg.SetBody(&emRet, sizeof(emRet));
		cMsg.CatBody(&errcode, sizeof(errcode));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode, UMS_UE_APP_INST);
		
		//发送此用户信息给所有用户
		CTpVector<TLogUser>::iterator Itor;
		for (Itor = m_tLogUser.begin(); Itor != m_tLogUser.end(); ++Itor)
		{
			if (!Itor->Invalid())
			{
				::OspPost(Itor->m_dwUserInst, ev_UmsDelUser_Notify, &tUser, sizeof(tUser), Itor->m_dwUserNode, UMS_UE_APP_INST);
			}
		}
	}
	else
	{
		errcode = m_cUserMG.GetLastError();
		
		cMsg.SetBody(&emRet, sizeof(emRet));
		cMsg.CatBody(&errcode, sizeof(errcode));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode, UMS_UE_APP_INST);
		
		MdlHint(Ums_Mdl_Ue, ("Umc Del user failed. Name:%s, Pwd:%s, ErrorCode:%d\n", tUser.GetName(), 
							 tUser.GetPassword(), errcode));
	}
}

void CUmcHandler::EventAddUserReq(CMessage* const ptMsg)
{
	CUserFullInfo tUser;
	TP_SAFE_CAST( tUser, ptMsg->content );

	CUserFullInfo* pUser = &tUser;
	MdlHint(Ums_Mdl_Ue, ("Umc Add user Req. Name:%s  Pwd:%s\n", pUser->GetName(),pUser->GetPassword()));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UMSAddUserRet);
	
	EmTpRet emRet = tp_Ret_FAILED;
	u16 errcode = 0;
	if(m_cUserMG.AddUser(pUser))
	{
		emRet = tp_Ret_Success;
		cMsg.SetBody(&emRet, sizeof(emRet));
		cMsg.CatBody(&errcode, sizeof(errcode));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
		
		//发送此用户信息给所有用户
		CTpVector<TLogUser>::iterator Itor;
		for (Itor = m_tLogUser.begin(); Itor != m_tLogUser.end(); ++Itor)
		{
			if (!Itor->Invalid())
			{
				::OspPost(Itor->m_dwUserInst, ev_UmsAddUser_Notify, &tUser, sizeof(tUser), Itor->m_dwUserNode, UMS_UE_APP_INST);
			}
		}

		MdlHint(Ums_Mdl_Ue, ("Umc Add user success. Name:%s  Pwd:%s\n", tUser.GetName(),tUser.GetPassword()));
	}
	else
	{
		errcode = m_cUserMG.GetLastError();
		
		cMsg.SetBody(&emRet, sizeof(emRet));
		cMsg.CatBody(&errcode, sizeof(errcode));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode, UMS_UE_APP_INST);
		
		MdlHint(Ums_Mdl_Ue, ("Umc Add usr failed. Name:%s, Pwd:%s, ErrorCode:%d\n", pUser->GetName(),
							 pUser->GetPassword(), errcode));
	}
}

void CUmcHandler::EventUserLogin(CMessage* const ptMsg)
{
	TLoginRet tLoginRet;
	tLoginRet.m_emRet = tp_LoginUms_sucess;

    CTpMsg cMsg;
	cMsg.SetEvent(ev_UMSLoginRet);

	CLoginRequest tLogin;
	TP_SAFE_CAST( tLogin, ptMsg->content);
	MdlHint(Ums_Mdl_Ue, ("Umc User login. Name:%s, %s\n", tLogin.GetName(), tLogin.GetPassword()));	

	CLoginRequest tLoginSDK;
	tLoginSDK.SetName(UMSSDK_UserName);
	tLoginSDK.SetPassword(UMSSDK_PassWord);
	if (0 == strcmp(tLoginSDK.GetName(), tLogin.GetName()) && 0 == strcmp(tLoginSDK.GetPassword(), tLogin.GetPassword()))
	{
		u32_ip dwSDKIP = ::OspNodeIpGet( ptMsg->srcnode );
		TLogUser tSDKUser;
		tSDKUser.m_dwUserInst = ptMsg->srcid;
		tSDKUser.m_dwUserNode = ptMsg->srcnode;
		tSDKUser.m_dwUserIP	= dwSDKIP;
		strncpy(tSDKUser.m_achName, tLogin.GetName(), MAX_CHARLENGTH);
		tSDKUser.m_achName[MAX_CHARLENGTH-1] = '\0';
		
		CTpVector<TLogUser>::iterator Iter;
		Iter = m_tLogUser.Add(tSDKUser);
		
		if (Iter == m_tLogUser.end())
		{
			tLoginRet.m_emRet = tp_LoginUms_MaxLogin;
			tLoginRet.m_dwErrorCode = m_cUserMG.GetLastError();
			
			cMsg.SetBody(&tLoginRet, sizeof(tLoginRet));
			cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
			
			MdlHint(Ums_Mdl_Ue, ("User sdk login full. Name:%s\n", tLogin.GetName()));		
			return;
		}
		
		cMsg.SetBody(&tLoginRet, sizeof(tLoginRet));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
		
		OspNodeDiscCBReg(ptMsg->srcnode, AID_UMSUE_APP, 1);
		
		CUmsUeInst* pcUeInst = (CUmsUeInst*)GetInstance();
		pcUeInst->NotifyMsgToService( ev_SysCmsLoginInd, NULL, 0, tSDKUser );

		return;
	}

	CUserFullInfo cUserTable;
	s32 nUserCount  = m_cUserMG.GetUserNum();
	s32 nItermCount = nUserCount > MAX_USERNUM ? MAX_USERNUM : nUserCount;	
	
	//检查是否存在用户
	BOOL32 bIsUserExist = FALSE;
	for(s32 nIndex = 0; nIndex < nItermCount; nIndex++)
	{
		BOOL bGetVal = m_cUserMG.GetUserFullInfo(&cUserTable,nIndex);			
		if(!bGetVal)
		{
			continue;
		}		
		if (0 == strcmp(cUserTable.GetName(), tLogin.GetName()))
		{
			bIsUserExist = TRUE;
			break;
		}
	}

	if (!bIsUserExist)
	{
		tLoginRet.m_emRet		= tp_LoginUms_NameError;
		tLoginRet.m_dwErrorCode = m_cUserMG.GetLastError();
		
		cMsg.SetBody(&tLoginRet, sizeof(tLoginRet));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
		
		MdlError(Ums_Mdl_Ue, ("Login failed, Not find user.Name:%s\n", tLogin.GetName()));		
		return;
	}

	//登录失败
	if(!m_cUserMG.CheckLoginValid(&tLogin))
	{
		tLoginRet.m_emRet		= tp_LoginUms_PwdError;
		tLoginRet.m_dwErrorCode = m_cUserMG.GetLastError();
		
		cMsg.SetBody(&tLoginRet, sizeof(tLoginRet));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
		
		MdlError(Ums_Mdl_Ue, ("Check user failed.Name:%s\n", tLogin.GetName()));		
		return ;
	}

	//检查是否重复登录
	u32_ip dwLogIP = ::OspNodeIpGet( ptMsg->srcnode );
	CTpVector<TLogUser>::iterator Itor;
	for (Itor = m_tLogUser.begin(); Itor != m_tLogUser.end(); ++Itor)
	{
		if (strcmp(Itor->m_achName, tLogin.GetName()) == 0)
		{
			CTpMsg cMsg;
			cMsg.SetEvent(ev_UmsLoginByOther_Notify);
			cMsg.SetBody(&dwLogIP, sizeof(dwLogIP));
			cMsg.Post(Itor->m_dwUserInst, Itor->m_dwUserNode, UMS_UE_APP_INST);
			
			MdlHint(Ums_Mdl_Ue, ("User occupy: Name:%s. SrcIp:"TPIPFORMAT", DstIp:"TPIPFORMAT" \n", 
				 tLogin.GetName(), Tpu32ToIP(Itor->m_dwUserIP), Tpu32ToIP(dwLogIP)));	

			::OspDelay( 200 );

			OspDisconnectTcpNode(Itor->m_dwUserNode);

			//清除
			m_tLogUser.Del(*Itor);
			Itor->Clear();			
			break;
		}
	}

	TLogUser tLogUser;
	tLogUser.m_dwUserInst = ptMsg->srcid;
	tLogUser.m_dwUserNode = ptMsg->srcnode;
	tLogUser.m_dwUserIP	= dwLogIP;
	strncpy(tLogUser.m_achName, tLogin.GetName(), MAX_CHARLENGTH);
	tLogUser.m_achName[MAX_CHARLENGTH-1] = '\0';
	
	Itor = m_tLogUser.Add(tLogUser);

	if (Itor == m_tLogUser.end())
	{
		tLoginRet.m_emRet = tp_LoginUms_MaxLogin;
		tLoginRet.m_dwErrorCode = m_cUserMG.GetLastError();
		
		cMsg.SetBody(&tLoginRet, sizeof(tLoginRet));
		cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
		
		MdlHint(Ums_Mdl_Ue, ("User login full. Name:%s\n", tLogin.GetName()));		
		return;
	}

	if (m_tLogUser.size() == 1)
	{
		switchssh(FALSE);
	}

	cMsg.SetBody(&tLoginRet, sizeof(tLoginRet));
	cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
	
	OspNodeDiscCBReg(ptMsg->srcnode, AID_UMSUE_APP, 1);

	CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();
	pUeInst->NotifyMsgToService( ev_SysCmsLoginInd, NULL, 0, tLogUser );

	
	//发送用户列表给登录客户端	
	for(s32 nCount = 0; nCount < nItermCount; ++nCount)
	{
		BOOL bGetVal = m_cUserMG.GetUserFullInfo(&cUserTable,nCount);			
		if(!bGetVal)
		{
			return;
		}		
		::OspPost(ptMsg->srcid, ev_UmsAddUser_Notify, &cUserTable, sizeof(cUserTable), ptMsg->srcnode, UMS_UE_APP_INST);
	}
}

void CUmcHandler::ShowLogin()
{
 	msgprintnotime("Umc login Num:%d, MaxNum:%d\n", m_tLogUser.size(), m_tLogUser.MaxSize());

 	CTpVector<TLogUser>::iterator Itor;
 	for (Itor = m_tLogUser.begin(); Itor != m_tLogUser.end(); ++Itor)
 	{
 		msgprintnotime("UserID:%d UserName:%s, Node:%d, Inst:%d, Ip:"TPIPFORMAT"\n"
 				, Itor->m_dwUserID, Itor->m_achName, Itor->m_dwUserNode, Itor->m_dwUserInst
 				, Tpu32ToIP(Itor->m_dwUserIP));
 	}	
 
 	msgprintnotime("\n\n");

 	m_cUserMG.ShowAll();

	msgprintnotime("\n*************User Info*************\n");

	CUserFullInfo cUserTable;
	for(s32 nCount = 0; nCount < MAX_USERNUM; ++nCount)
	{
		BOOL bGetVal = m_cUserMG.GetUserFullInfo(&cUserTable,nCount);			
		if(!bGetVal)
		{
			continue;
		}		
		msgprintnotime("Index:%d, Guid:%d, user name:%s, pw:%s, Actor:%u, fullname:%s, discription:%s.\n", 
			nCount, cUserTable.m_dwGuid, cUserTable.GetName(), cUserTable.GetPassword(),
			cUserTable.m_byActor, cUserTable.m_achfullname, cUserTable.m_achdiscription);
	}
}

void CUmcHandler::PrintEventInfoFromUI(CTpMsg* const ptMsg)
{
	u16 wEvent    = ptMsg->GetEvent();
	u8* pDataBuf  = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();
	
	if(!IsCanPrint(Ums_Mdl_Ue, enLogLowest))
	{
		return;
	}

	switch(wEvent)
	{

	case ev_HduPlay_Req:
		{
			TTPHduPlayReq tReq;
			TP_SAFE_CAST(tReq, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduPlay_Req Index:%d, ScreenNum:%d.\n",
									 tReq.m_wIndex, tReq.m_wScreenNum));
		}
		break;

	case ev_HduAllStopPlay_Req:
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduAllStopPlay_Req Stop all hdu.\n"));
		}
		break;

	case ev_HduStopPlay_Req:
		{
			TTPHduPlayReq tReq;
			TP_SAFE_CAST(tReq, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduStopPlay_Req Index:%d, ScreenNum:%d.\n",
									 tReq.m_wIndex, tReq.m_wScreenNum));
		}
		break;
	case ev_Hdu_SetVol:
		{
			THduSetVolInfo tVolInfo;
			TP_SAFE_CAST(tVolInfo, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_Hdu_SetVol Index:%d, subIndex:%d, byVol:%d, bMute:%d\n", tVolInfo.m_tInfo.m_wIndex, tVolInfo.m_tInfo.m_bySubIndex,
				tVolInfo.m_byVol, tVolInfo.m_bMute));
		}
		break;

	case ev_NMServerAdd_req:
		{
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(tCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerAdd_req  GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT"\n",
									 tCfg.wNMGetSetPort, tCfg.WNMTrapPort,tCfg.achNMReadCommunity, 
									 tCfg.achNMWriteCommunity, tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
		}
		break;
		
	case ev_NMServerMdy_req:
		{
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(tCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerMdy_req  GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT"\n",
									 tCfg.wNMGetSetPort, tCfg.WNMTrapPort,tCfg.achNMReadCommunity, 
									 tCfg.achNMWriteCommunity, tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
		}
		break;
	case ev_NMServerDel_req:
		{
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(tCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerDel_req  GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT"\n",
									 tCfg.wNMGetSetPort, tCfg.WNMTrapPort,tCfg.achNMReadCommunity, 
									 tCfg.achNMWriteCommunity, tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
		}
		break;
	case evtp_StartInterimMeeting_Req:
		{
			TTPConfMeet tReq = *(TTPConfMeet*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("evtp_StartInterimMeeting_Req ConfName:%s, id:%d, EpName:%s.\n", tReq.m_achConfName, tReq.m_wID, tReq.m_atEpList.m_tCnsList[0].m_tEpAddr.m_tAlias.m_abyAlias));
			
		}
		break;

	case ev_umcrebootUms_cmd:
		{
			MdlLowHint(Ums_Mdl_Ue, (" reboot msg from umc \n"));
		}
		break;

	default:
		break;
	}
}

void CUmcHandler::PrintEventInfo(CTpMsg* const ptMsg)
{
	u16 wEvent    = ptMsg->GetEvent();
	u8* pDataBuf  = ptMsg->GetBody() + sizeof(TLogUser);
	u16 wDataSize = ptMsg->GetBodyLen() - sizeof(TLogUser);
	
	if(!IsCanPrint(Ums_Mdl_Ue, enLogLowest))
	{
		return;
	}

	switch (wEvent)
	{

	case evtp_AddConftemplate_Notify1:	
		{
			TTPConfTemplate tConf;
			TP_SAFE_CAST(tConf, pDataBuf);
			BOOL32 bRefresh;
			TP_SAFE_CAST(bRefresh, pDataBuf + sizeof(TTPConfTemplate));
			MdlLowHint(Ums_Mdl_Ue, ("evtp_AddConftemplate_Notify1 EventID:%d, EventName:%s, confName:%s, bRefresh:%d.\n", wEvent, GetEventNamebyID(wEvent), tConf.m_achConfName, ntohl(bRefresh)));
		}
		break;

	case evtp_Updateconftemplate_Notify1:
		{
			TTPConfTemplate tTmp;
			TP_SAFE_CAST(tTmp, pDataBuf);
			BOOL32 bRefresh;
			TP_SAFE_CAST(bRefresh, pDataBuf + sizeof(TTPConfTemplate));
			MdlLowHint(Ums_Mdl_Ue, ("evtp_Updateconftemplate_Notify1 bRefresh:%d, ConfName:%s, MainNum:%d\n", ntohl(bRefresh), tTmp.m_achConfName, ntohs(tTmp.m_wMainNum)));
			for (u16 wIndex = 0; wIndex < ntohs(tTmp.m_wMainNum); wIndex++)
			{
				MdlLowDtl(Ums_Mdl_Ue, ("[(%d->%s),(%d->%s),%d].\n", TpEnumIdString(EmTpVideoQualityLevel, (u16)ntohl(tTmp.m_atTpMainVideoRes[wIndex].m_emQualityLvl))
					, TpEnumIdString(EmTpVideoResolution, (u16)ntohl(tTmp.m_atTpMainVideoRes[wIndex].m_emRes)), ntohs(tTmp.m_atTpMainVideoRes[wIndex].m_wFrameRate)));
			}

		}
		break;
	case evtp_AddConfList_Notify:
		{
			TAddConfList tList;
			TP_SAFE_CAST(tList, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("evtp_AddConfList_Notify ConfID:%d, SpeakerID:%d, DualID:%d, bIsChairUms:%d.\n",
									 tList.m_atTmpList[0].m_wConfID, tList.m_atTmpList[0].m_wSpeaker,
									 tList.m_atTmpList[0].m_wDual, tList.m_atTmpList[0].m_bIsChairUms));
		}
		break;
		
	case ev_hduPlan_Nty:
		{
			THduPlanData tData;
			TP_SAFE_CAST(tData, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduPlan_Nty Row:%d, Column:%d, wNum:%d.\n", tData.m_byRow, tData.m_byCol, ntohs(tData.m_wNum)));

			u16 wIndex = 0;
			for (u8 byRowIndex = 0; byRowIndex < tData.m_byRow; ++byRowIndex)
			{
				for (u8 byColIndex = 0; byColIndex < tData.m_byCol; ++byColIndex)
				{
					MdlLowDtl(Ums_Mdl_Ue, ("Row:%d, Column:%d, Reged:%d, Valid:%d, Index:%d, name:%s, vmp:%d, vol:%d, mute:%d, chanid:%d.\n",
											byRowIndex, byColIndex, tData.m_atUnits[wIndex].m_byReged, tData.m_atUnits[wIndex].m_byValid,
											ntohs(tData.m_atUnits[wIndex].m_wIndex), tData.m_atUnits[wIndex].m_tHduName.m_abyAlias,
											tData.m_atUnits[wIndex].m_byVmp, tData.m_atUnits[wIndex].m_byVol, tData.m_atUnits[wIndex].m_byMute,
											tData.m_atUnits[wIndex].m_byChanIndex));
					++wIndex;
				}
			}
		}
		break;

	case ev_HduPlay_Ack:
		{
			u16 wIndex;
			TP_SAFE_CAST(wIndex, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduPlay_Ack Index:%d.\n", wIndex));
		}
		break;

	case ev_HduPlay_NAck:
		{
			u16 wIndex;
			EmTpHduPlayNackReason emReason;
			TP_SAFE_CAST(wIndex, pDataBuf);
			TP_SAFE_CAST(emReason, pDataBuf+sizeof(u16));
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduPlay_NAck Index:%d, Reason:%d.\n", wIndex, emReason));
		}
		break;

	case ev_HduCall_Valid:
		{
			TTPHduPlayReq tReq;
			BOOL32 bValid;
			TP_SAFE_CAST(tReq, pDataBuf);
			TP_SAFE_CAST(bValid, pDataBuf+sizeof(TTPHduPlayReq));
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduCall_Valid Index:%d, ScreenNum:%d, Valid:%d.\n",
									 tReq.m_wIndex, tReq.m_wScreenNum, bValid));
		}
		break;

	case ev_HduStopPlay_Ack:
		{
			u16 wIndex;
			TP_SAFE_CAST(wIndex, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduStopPlay_Ack Index:%d.\n", wIndex));
		}
		break;

	case ev_HduStopPlay_NAck:
		{
			u16 wIndex;
			TP_SAFE_CAST(wIndex, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduStopPlay_NAck Index:%d.\n", wIndex));
		}
		break;

	case ev_HduReg_Status_Nty:
		{
			u16 wIndex = 0;
			BOOL32 bReged = FALSE;
			TP_SAFE_CAST(wIndex, pDataBuf);
			TP_SAFE_CAST(bReged, pDataBuf+sizeof(u16));
			MdlLowHint(Ums_Mdl_Ue, ("ev_HduReg_Status_Nty Index:%d, Reged:%d.\n", wIndex, bReged));
		}
		break;
		
	case ev_NMServer_nty:
		{
			u16 wValidNum = 0;
			TP_SAFE_CAST(wValidNum, pDataBuf);
			TTPNMServerCfg tCfg;
			for (u16 wIndex = 0; wIndex < wValidNum; ++wIndex)
			{
				TP_SAFE_CAST(tCfg, pDataBuf+sizeof(u16)+sizeof(TTPNMServerCfg)*wIndex);
				MdlLowHint(Ums_Mdl_Ue, ("ev_NMServer_nty GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT".\n",
										 tCfg.wNMGetSetPort, tCfg.WNMTrapPort,
										 tCfg.achNMReadCommunity, tCfg.achNMWriteCommunity,
									  	 tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
			}
		}
		break;
	case evtp_StartConfTemplate_Ret:
		{
			TStartConfResult tRet;
			TP_SAFE_CAST(tRet, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("evtp_StartConfTemplate_Ret TemplateId:%d, ConfID:%d, Reason:(%d->%s).\n"
									, tRet.m_wConfTemplateID, tRet.m_wConfID, TpEnumIdString(EmTpStartConfRet, tRet.m_emReason)));
		}
		break;
	case evpt_OperatorConfTemplate_Ret:
		{
			TOprConfTmpResult tRet;
			TP_SAFE_CAST(tRet, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("evpt_OperatorConfTemplate_Ret TemplateId:%d, Reason:(%d->%s).\n", tRet.m_wID, TpEnumIdString(EmTpConfTemplateRet, tRet.m_emReason)));
		}
		break;
	case evtp_Delconftemplate_Notify:
		{
			TDelRefreshConfTemplate tDel;
			TP_SAFE_CAST(tDel, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("evtp_Delconftemplate_Notify RefreshNum:%d, TmpList[0]:%d.\n", tDel.m_wRefreshNum, tDel.m_awTmpList[0]));
		}
		break;
	case ev_del_all_conftemp_rsp:
		{
			TOprConfTmpResult tRet;
			TP_SAFE_CAST(tRet, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_del_all_conftemp_rsp ret:%d\n", tRet.m_emReason));
		}
		break;

	case ev_umsGetRegInfo_CnsRspEx:
		{
			TCnsRegPackEx tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);
			
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGetRegInfo_CnsRspEx Size:%d, IsEnd:%d.\n",
									 tInfo.m_wSize, tInfo.m_bIsEnd));

			for (u16 wIndex = 0; wIndex < tInfo.m_wSize; ++wIndex)
			{
				MdlLowDtl(Ums_Mdl_Ue, ("ev_umsGetRegInfo_CnsRspEx Index:%d, AliasNum:%d.\n",
										 wIndex+1,  tInfo.m_atRegInfo[wIndex].m_wAliasNum));
			}
		}
		break;

	case ev_umsGetRegInfo_UmsRspEx:
		{
			TUmsRegPackEx tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGetRegInfo_UmsRspEx Size:%d, IsEnd:%d.\n",
									 tInfo.m_wSize, tInfo.m_bIsEnd));

			for (u16 wIndex = 0; wIndex < tInfo.m_wSize; ++wIndex)
			{
				MdlLowDtl(Ums_Mdl_Ue, ("ev_umsGetRegInfo_UmsRspEx Index:%d, AliasNum:%d.\n",
										 wIndex+1, tInfo.m_atRegInfo[wIndex].m_wAliasNum));
			}
		}
		break;

	case ev_umsGetRegInfo_MtRspEx:
		{
			TTPMtRegInfo tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGetRegInfo_MtRspEx Size:%d, IsEnd:%d.\n",
									 tInfo.m_wListNum, tInfo.m_bIsEnd));
		}
		break;

	case ev_umsGetRegInfo_McuRspEx:
		{
			TTPMcuRegInfo tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGetRegInfo_McuRspEx IsEnd:%d, AliasNum:%d.\n",
									 tInfo.m_bIsEnd, tInfo.m_wListNum));
		}
		break;

	case ev_umsreg_notify:
		{
			TTPSipRegistrarCfg tSipCfg = *(TTPSipRegistrarCfg*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsreg_notify ServerInfo:"ADDRPORT_FORMAT" Used:%d\n", 
									 ADDRPORT(tSipCfg.dwRegIP, tSipCfg.wRegPort), tSipCfg.bUsed));
		}	
		break;
		
	case ev_umsGKReg_notify:
		{
			TTPGKCfg tGkCfg = *(TTPGKCfg*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGKReg_notify ServerInfo:"ADDRPORT_FORMAT"\n", ADDRPORT(tGkCfg.dwGKIP, tGkCfg.wRegPort)));
		}
		break;
	case ev_updatepwdtimer_Ind:
		{
			TPwdCycleInfo tCycleInfo;
			BOOL32 bRet;
			TP_SAFE_CAST(tCycleInfo, pDataBuf);
			TP_SAFE_CAST(bRet,pDataBuf+sizeof(TPwdCycleInfo));
			MdlLowHint(Ums_Mdl_Ue, ("ev_updatepwdtimer_Ind bstart:%d, cycle:%d,result:%d.\n", tCycleInfo.m_bStartUpdate, tCycleInfo.m_emPwdCycle,bRet));
			
		}
		break;
	case ev_updatepwdtimer_Nty:
		{
			TPwdCycleInfo tCycleInfo;
			TP_SAFE_CAST(tCycleInfo, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_updatepwdtimer_Nty bstart:%d, cycle:%d\n", tCycleInfo.m_bStartUpdate, tCycleInfo.m_emPwdCycle));
			
		}
		break;
	case evtp_AddConfTemplateEx_res:
		{
			TTemplateConfEx tTempExRet;
			EmAddTempConfExRes emRet;
			TP_SAFE_CAST(tTempExRet, pDataBuf);
			TP_SAFE_CAST(emRet,pDataBuf+sizeof(TTemplateConfEx));
			MdlLowHint(Ums_Mdl_Ue, ("evtp_AddConfTemplateEx_res EventID:%d, EventName:%s, TempID:%d,reason:%d->%s.\n", 
				wEvent, GetEventNamebyID(wEvent), tTempExRet.m_wTempID,TpEnumIdString(EmAddTempConfExRes, emRet)));
		}
		break;
	case evtp_AddConfTemplateEx_Notify:	
		{
			TTemplateConfEx tConftempex;
			TP_SAFE_CAST(tConftempex, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("evtp_AddConfTemplateEx_Notify EventID:%d, EventName:%s, TempID:%d.\n", wEvent, GetEventNamebyID(wEvent), tConftempex.m_wTempID));
		}
		break;
	case ev_card_switchtelnetftp_rsp:
		{
			TPBoardSwitch tBrdSwitch;
			TP_SAFE_CAST(tBrdSwitch, pDataBuf);
			EmBoardSwitchRes emBrdSwitchRes;
			TP_SAFE_CAST(emBrdSwitchRes, pDataBuf + sizeof(TPBoardSwitch));
			MdlLowHint(Ums_Mdl_Ue, ("ue ev_card_switchtelnetftp_rsp layer:%d, slot:%d, type:%d, bonoff:%d, res:%d.\n",
				tBrdSwitch.m_byLayer, tBrdSwitch.m_bySlot, tBrdSwitch.m_emType, tBrdSwitch.m_bSwitch, emBrdSwitchRes));

		}
		break;
	case ev_card_switchtelnet_ntf:
		{
			TPBoardSwitch tBrdSwitch;
			TP_SAFE_CAST(tBrdSwitch, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ue ev_card_switchtelnet_ntf layer:%d, slot:%d, type:%d, bonoff:%d.\n",
				tBrdSwitch.m_byLayer, tBrdSwitch.m_bySlot, tBrdSwitch.m_emType, tBrdSwitch.m_bSwitch));

		}
		break;
	case ev_authCount_Nty:
		{
			u32 dwTotal = *(u32*)pDataBuf;
			u32 dwUseNum = *(u32*)(pDataBuf+sizeof(u32));
			MdlLowHint(Ums_Mdl_Ue, ("ue ev_authCount_Nty TotalCount:%d, UseCount:%d.\n", dwTotal, dwUseNum));
		}
		break;

	case ev_hduCount_Nty:
		{
			TTPBrdUsedInfo tUseInfo = *(TTPBrdUsedInfo*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ue ev_hduCount_Nty Type:%d, UseNum:%d, RegNum:%d.\n",
				tUseInfo.m_emType, tUseInfo.m_wUsedNum, tUseInfo.m_wRegNum));
		}
		break;
	case ev_verInfo_Nty:	
		{
			TUmsVersion tver = *(TUmsVersion*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ue ev_verInfo_Nty Softver:%s, HardVer:%s.\n", tver.m_abSoftVersion, tver.m_abHardVersion));
		}
		break;
	case ev_sysInfo_Nty:
		{
			TToolSysInfo tSysInfo = *(TToolSysInfo*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ue ev_sysInfo_Nty CpuRate:%d, MemRate:%d\n", tSysInfo.m_dwCpuRate, tSysInfo.m_dwMemRate));
		}
		break;

	case ev_confCount_Nty:
		{
			u32 dwConfCount = *(u32*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ue ev_confCount_Nty ConfCount:%d\n", dwConfCount));
		}
		break;
	}

	
}