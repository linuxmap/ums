#include "umssipadapterinst.h"
#include "tpsys.h"
#include "tptime.h"
#include "eventtpsys.h"
#include "innereventumssipadapter.h"
#include "eventoutsipadapter.h"
#include "eventoutumseqp.h"
#include "eventoutumsmcucasecade.h"
#include "umsobject.h"
#include "adaptercfg.h"
#include "umsobject.h"
#include "umsstackinterface.h"
#include "eventoutquantum.h"
#include "qtinterface.h"
#include "qtstruct.h"
#include "umsdataconvet.h"

extern BOOL32 g_bKedaManuOn;
TUmsStackCallCfg	g_tUMSStackCfg;
u32 g_dwUmsNode = INVALID_NODE;
u32 g_dwUmsInst = INVALID_NODE;

TTPQTEncryptInfo g_tTPQTEncryptInfo;

//add for qt
void QtCallHandle(u32 dwPeerMtIp, u32 dwPeerQtID, s8 szAlias[QT_ALIAS_MAX_LEN+1], EmQtAliasType emAliasType,  QTCALLHANDLE hCallHandle);
void QtMediaHandle(u32 dwPeerMtIp, u32 dwPeerQtID, s8 szAlias[QT_ALIAS_MAX_LEN+1], EmQtAliasType emAliasType, QTMediaKeyHandle hMediaHandle);
void CBMediaKey(u32 dwConfID, QTMediaKeyHandle hMediaHandle, s8 szAlias[QT_ALIAS_MAX_LEN+1], u8 acMediaKey[QT_MAX_MEDIA_KEY+1], u32 dwKeyLen,EmQtKeyFrequency emKeyFrequency,u32 dwQtFlag,u16 wIndex);
void QtMTState( EmQtMTState emQtMtState, void* wParam);
void QtRetReason(EmQtRetReason emQtRetReason, void* wParam);
void QueryAlias(u16 wIndex, s8 szAlias[TP_MAX_ALIAS_LEN]);
//end for qt

void CreatQtInitParam(BOOL32 bQTOn, u32 dwQtMtIp, u32 dwQtMtId, TQtInitParam& tQtInitParam);

// 定义在qt库内
extern QtCBMediaKeyDstMT  g_pfCBMediaKey;

extern BOOL32	g_bShowSendMsgInfo;

//Protocol_file
void QtCBMediaKeyDstMTcc(u32 dwConfID, s8 szAlias[QT_ALIAS_MAX_LEN+1])
{
	MdlHint(Ums_Mdl_Stack, ("[QtCBMediaKeyDstMTcc]dwConfID->%d, szAlias->%s\n",
		dwConfID, szAlias));
	TUmsHandle tHandle;
	tHandle.handAppCall = dwConfID;
	tHandle.handAppCall = tHandle.handAppCall << 16;
	tHandle.handAppCall |= 1025;   //why 1025?
	
	
	CTpMsg cMsg;	
	tHandle.m_dwAdapteID = g_tUMSStackCfg.m_dwUmsNode;
	cMsg.SetEvent(evtp_MediaDstMT_Nty);
	cMsg.SetHomeplace(node_peer);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	if (NULL != szAlias)
	{
		cMsg.CatBody(szAlias, QT_ALIAS_MAX_LEN+1);
	}
	
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), g_dwUmsNode, UMS_SIPADAPTER_APP_INST);
}



CTpUmsSipAdapterApp g_cTPUmsSipAdapterApp;
API BOOL StartupTpServer()
{
	g_cTPUmsSipAdapterApp.CreateApp("SipAdapterApp",AID_UMSSIPADAPTER_APP,100, 2048);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( UMS_SIPADAPTER_APP_INST );
	return TRUE;
}

API void StopAdapterService()
{
	QuitUmsStack();
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( UMS_SIPADAPTER_APP_INST, 0, UMS_SIPADAPTER_APP_INST);
}

CTpSipAdapterServer::CTpSipAdapterServer()
{
	m_wLogModuleId = Ums_Mdl_Stack;
}




BOOL32 CTpSipAdapterServer::ObjectInit(u32 wParam, u32 lParam)
{
	msgprint("CTpSipAdapterServer::ObjectInit\n");
	SetLogTitle("[CTpSipAdapterServer]");
	
	m_bInit = TRUE;
	g_dwUmsNode = INVALID_NODE;

	//回调给上层协商码流key的EPID
	g_pfCBMediaKey = QtCBMediaKeyDstMTcc;

	ConnectToUms();
	
	return TRUE;
}

void CTpSipAdapterServer::ObjectExit()
{
	if (INVALID_NODE != g_dwUmsNode)
	{
		OspDisconnectTcpNode(g_dwUmsNode);
	}
	QuitUmsStack();
	CUmsObject::ObjectExit();
}


void CTpSipAdapterServer::MessageProc(CTpMsg *const ptMsg)
{
	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();

	if (wSrcAppID == AID_UMSCONFMGR)
	{
		OnMsgFromCall(ptMsg);
	}
	else
	{
		switch( wEvent ) 
		{
		case ev_ConnectToUms_Time:
			{
				ConnectToUms();
			}		
			break;
		case ev_SipAdapterInit_Ind:
			{
				OnSipInitAdapterInd(ptMsg);
			}
			break;
		case ev_SipAdapterInitCfg_NACK:
			{
				OspDisconnectTcpNode(g_dwUmsNode);
				g_dwUmsNode = INVALID_NODE;
				KillTimer(ev_ConnectToUms_Time);
				SetTimer(ev_ConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
			}
			break;
		case ev_SipAdapterInitCfg_ACK:
			{
				OnRegSuccess(ptMsg);
			}
			break;
		default:
			ObjError(("CTpSipAdapterServer::MessageProc msg unproess. msg(%d->%s)", wEvent, GetEventNamebyID(wEvent)));
			break;
		}
	}
}

API void reboot();
void CTpSipAdapterServer::OnDisConnect(CMessage *const ptMsg)
{
	reboot();
}


void CTpSipAdapterServer::OnRegSuccess(CTpMsg *const ptMsg)
{
	u32 dwIP = GetUmsListenIp();
	msgprint("OnRegSuccess, ServerIp:"TPIPFORMAT"\n", Tpu32ToIP(dwIP));

	TP_SAFE_CAST( g_tUMSStackCfg, ptMsg->GetBody());
	KillTimer(ev_ConnectToUms_Time);
	TP_SAFE_CAST(g_tTPQTEncryptInfo, ptMsg->GetBody()+sizeof(g_tUMSStackCfg));
	TP_SAFE_CAST(g_bKedaManuOn,ptMsg->GetBody()+sizeof(g_tUMSStackCfg)+sizeof(g_tTPQTEncryptInfo));
	msgprint("OnRegSuccess, channel on is %d\n", g_bKedaManuOn);
	InitUmsStack(g_tUMSStackCfg, g_tTPQTEncryptInfo);


}

void CTpSipAdapterServer::ConnectToUms()
{
	MdlHint(Ums_Mdl_Stack, ("ConnectToUms retry!\n"));

	KillTimer(ev_ConnectToUms_Time);
	if (INVALID_NODE != g_dwUmsNode)
	{
		return;
	}

	g_dwUmsNode = ::OspConnectTcpNode(GetUmsListenIp(), GetUmsListenPort());

	if (INVALID_NODE == g_dwUmsNode)
	{
		SetTimer(ev_ConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
	}
	else
	{
		::OspNodeDiscCBReg(g_dwUmsNode, GetAppID(), GetInsID());
		TModelProp tMdl;
		tMdl.m_dwEqpIP =  GetLocalIpByDstIp(GetUmsListenIp());
		tMdl.m_wEqpType = em_adapter_mdl;
		tMdl.m_dwCapSet = 96;
		EmTpConfProtocol emProtocol = emTpSIP;

		CTpMsg cMsg;
		cMsg.SetEvent(ev_SipAdapterInitCfg_Req);
		cMsg.SetBody(&tMdl, sizeof(tMdl));
		cMsg.CatBody(&emProtocol, sizeof(emProtocol));
		cMsg.Post(UMS_EQP_APP_INST, g_dwUmsNode, UMS_SIPADAPTER_APP_INST);
	}	
}

void CTpSipAdapterServer::OnSipInitAdapterInd(CTpMsg *const ptMsg)
{
	BOOL32 bSuc;
	TP_SAFE_CAST(bSuc, ptMsg->GetBody());

	msgprint("OnSipInitAdapterInd! Ret:%d\n", bSuc);	

	if (bSuc)
	{
		CTpMsg cMsg;
		cMsg.SetEvent(ev_SipAdapterInitSuccess_Ind);
		cMsg.SetBody(&g_tUMSStackCfg.m_wUmsIndex, sizeof(g_tUMSStackCfg.m_wUmsIndex));
		cMsg.Post(UMS_EQP_APP_INST, g_dwUmsNode, UMS_SIPADAPTER_APP_INST);
	}
	else
	{
		OspDisconnectTcpNode(g_dwUmsNode);
		OspDelay(100);
		reboot();
	}
}



void CTpSipAdapterServer::ProcQtMsgFromCall(const TUmsHandle& tHandle, const s32 wEvent, u8 *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
    u16 wConfID;

	if (wEvent == evtp_QtQueryAlias_rsp)
	{
		//TODO
		TTPQTQueryInfo tInfo;
		TTPQTQueryData tQueryData;
		EmQueryAliasRes emRes;
		EmTPConfEncFrequency emConfEnc;
		//tInfo = *(TTPQTQueryInfo*)pData;
		TP_SAFE_CAST(tQueryData, pBuf);
        tInfo.m_wIndex = tQueryData.m_wIndex;
        memcpy(tInfo.m_szAlias, tQueryData.m_szAlias, sizeof(tInfo.m_szAlias));

		pBuf += sizeof(TTPQTQueryData);
		TP_SAFE_CAST(emRes, pBuf);

		pBuf += sizeof(EmQueryAliasRes);
		TP_SAFE_CAST(emConfEnc, pBuf );

		wConfID = tHandle.handAppCall;

		MdlHint(Ums_Mdl_Stack, ("[CTpSipAdapterServer::OnMsgFromCall]evtp_QtQueryAlias_rsp \
			m_wIndex:%d, m_szAlias:%s, emRes:%d(0:Success), emConfEnc:%d(0:EverySeconds,1:EveryMinute,2:EveryConf),Confid:%d\n",
			tInfo.m_wIndex,
			tInfo.m_szAlias,
			emRes,
			emConfEnc,
			wConfID));

		BOOL32 bRes = FALSE;
		if ( emQuerySuccess == emRes )
		{
			bRes = TRUE;
		}

        //Protocol_file
		EmQtKeyFrequency emQtEncLevel;
		ConvertQTEncryptLevelFromUmsToStack(emConfEnc, emQtEncLevel);
		QtQueryConfEncryptionResult(wConfID, (void*)&tInfo, bRes, emQtEncLevel);

	} else if (wEvent == ev_QTEncryptInfo_Nty)
	{
		TTPQTEncryptInfo tTPQTEncryptInfo;
		TP_SAFE_CAST( tTPQTEncryptInfo, pBuf );
		EmTpConfProtocol emProType;
		TP_SAFE_CAST( emProType, pBuf + sizeof(tTPQTEncryptInfo) );
		MdlHint( Ums_Mdl_Stack, (">>>>ev_QTEncryptInfo_Nty, QTOnOff:%d dwQuanTumID:%d, dwQuanTumIP:"TPIPFORMAT", emregProtocol:%d(1:323; 3:sip; 5:all)\n",
			tTPQTEncryptInfo.m_bIsEncQT,
			tTPQTEncryptInfo.m_dwQuanTumID,
			Tpu32ToIP(tTPQTEncryptInfo.m_dwQuanTumIP),
			emProType));
		
		memcpy(&g_tTPQTEncryptInfo, &tTPQTEncryptInfo, sizeof(TTPQTEncryptInfo)); 
		
		//Protocol_file
		TQtInitParam tQtInitParam; 
		EmPAConfProtocol emPAType;


		CreatQtInitParam(tTPQTEncryptInfo.m_bIsEncQT, tTPQTEncryptInfo.m_dwQuanTumIP, tTPQTEncryptInfo.m_dwQuanTumID, tQtInitParam);
		ConvertRegTypeFromUmsToStack( emProType, emPAType );
			
	    kdvPAQuantumInit( tQtInitParam, emPAType );

	}
    else if (wEvent == evtp_MediaKey_Nty)
	{   //上级notify 到下级
		wConfID = tHandle.GetConfID();
	    u16 wEpID = tHandle.GetEpID();

		TTPMediaKeyInfo tTpInfo;
		TP_SAFE_CAST( tTpInfo, pBuf );
		
		MdlHint( Ums_Mdl_Stack, (">>>>evtp_MediaKey_Nty ConfID:%d, EpID:%d, m_dwHandle->%d, m_wIndex->%d, m_szAlias->%s, m_dwKeyLen->%d, emKeyFrequency->%d, QtFlag:%u, InfoLen:%d\n",
			wConfID, wEpID,
			tTpInfo.m_dwHandle,
			tTpInfo.m_wIndex,
			tTpInfo.m_szAlias,
			tTpInfo.m_dwKeyLen,
			tTpInfo.m_emKeyFrequency,
			tTpInfo.m_dwQtFlag,
			sizeof(TTPMediaKeyInfo)) );
		
		//Protocol_file
		TPAQTMediaKeyInfo tPaInfo;
		tPaInfo.m_dwHandle = tTpInfo.m_dwHandle;
		tPaInfo.m_wIndex = tTpInfo.m_wIndex;
		memcpy(tPaInfo.m_szMediaKey1, tTpInfo.m_szMediaKey1, TP_MAX_MEDIAKEY_LEN/4);
		memcpy(tPaInfo.m_szMediaKey2, tTpInfo.m_szMediaKey2, TP_MAX_MEDIAKEY_LEN/4);
		memcpy(tPaInfo.m_szMediaKey3, tTpInfo.m_szMediaKey3, TP_MAX_MEDIAKEY_LEN/4);
		memcpy(tPaInfo.m_szMediaKey4, tTpInfo.m_szMediaKey4, TP_MAX_MEDIAKEY_LEN/4);
		
		tPaInfo.m_dwKeyLen = tTpInfo.m_dwKeyLen;
		ConvertEpEncryptLevelFromUmsToStack(tTpInfo.m_emKeyFrequency,tPaInfo.m_emKeyFrequency);
		tPaInfo.m_dwQtFlag = tTpInfo.m_dwQtFlag;
		
		PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleQuantumMediaKey, (u8*)(&tPaInfo), sizeof(TPAQTMediaKeyInfo));
	
	} else if (wEvent == evtp_QtSetConfInfo_Cmd)
	{
		BOOL32 bChairConf;
		TP_SAFE_CAST( bChairConf, pBuf );
		BOOL32 bReset;
		TP_SAFE_CAST( bReset, pBuf + sizeof(BOOL32) );
			
		MdlHint( Ums_Mdl_Stack, (">>>>evtp_QtSetConfInfo_Cmd ConfID->%d, ChairConf->%d, Reset->%d\n",
				tHandle.GetConfID(), bChairConf, bReset) );
			
		QtSetConfInfo(tHandle.GetConfID(), bChairConf, bReset);

	}


}


void CTpSipAdapterServer::OnMsgFromCall(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	if (wLen < sizeof(TUmsHandle))
	{
		MdlError(Ums_Mdl_Stack, ("OnMsgFromCall msg len error! event:%d->%s\n", wEvent, GetEventNamebyID(wEvent) ));
		return;
	}
	
	TUmsHandle tHandle = *(TUmsHandle*)pData;
	pData = pData + sizeof(TUmsHandle);
	wLen = wLen - sizeof(TUmsHandle);

	if (g_bShowSendMsgInfo)
	{
		msgprint("CTpSipAdapterServer::OnMsgFromCall event:%d-%s, msgsize:%d, confid:%d, epid:%d, pacall:%d.\n",
			wEvent, GetEventNamebyID(wEvent), wLen, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall);
	}

	if (wEvent > ev_SipAdapter_ChanBegin && wEvent < ev_SipAdapter_DualBegin)
	{
		UmsSendChanCtrl(tHandle, wEvent, pData, wLen);
	}
	else if(wEvent > ev_SipAdapter_DualBegin && wEvent < ev_SipAdapter_PollBegin)
	{
		UmsSendDualConfCtrl(tHandle, wEvent, pData, wLen);
	}
	else if(wEvent > ev_SipAdapter_PollBegin && wEvent < ev_SipAdapter_UmsDiscussBegin)
	{
		UmsSendPollConfCtrl(tHandle, wEvent, pData, wLen);
	}
	else if(wEvent > ev_SipAdapter_UmsDiscussBegin && wEvent < ev_SipAdapter_CnsConfStatBegin)
	{
		UmsSendAudMixConfCtrl(tHandle, wEvent, pData, wLen);
	}
	else if (wEvent > ev_SipAdapter_CnsConfStatBegin && wEvent < ev_SipAdapter_GetVid_Begin)
	{
		UmsSendCnsUIConfCtrl(tHandle, wEvent, pData, wLen);	
	}
	else if (wEvent > evtp_UMS_MCU_Casecade_Event_Begin && wEvent < evtp_UMS_MCU_Casecade_Event_End)
	{
		if (wLen < sizeof(TUmsMcuChan))
		{
			MdlError(Ums_Mdl_Stack, ("OnMsgFromCall ums_mcu msg len error! event:%d->%s.\n", wEvent, GetEventNamebyID(wEvent) ));
			return;
		}

		TUmsMcuChan tMcuChan = *(TUmsMcuChan*)pData;
		pData = pData + sizeof(TUmsMcuChan);
		wLen = wLen - sizeof(TUmsMcuChan);
		UmsSendMcuCtrl(tHandle, tMcuChan, wEvent, pData, wLen);
	}
	else if (wEvent > evtp_QuantumEvent_Begin  && wEvent < evtp_QuantumEvent_End)
	{
         ProcQtMsgFromCall(tHandle, wEvent, pData, wLen);
	}
	else
	{
		UmsSendConfCtrl(tHandle, wEvent, pData, wLen);
	}
}


#define  VER_umssipadapter_ver   UMS_VerID
API void ver()
{
	msgprint("umssipadapter ver: %s  compile time: %s %s\n",
		VER_umssipadapter_ver, __DATE__,  __TIME__);
}



API void showreg()
{
	msgprint("m_dwUmsNode = :%d\n", g_tUMSStackCfg.m_dwUmsNode);
	msgprint("m_wUmsIndex = :%d\n", g_tUMSStackCfg.m_wUmsIndex);
	msgprint("m_wCallingPort = :%d\n", g_tUMSStackCfg.m_wCallingPort);
	msgprint("m_wMaxCallNum = :%d\n", g_tUMSStackCfg.m_wMaxCallNum);
	msgprint("m_dwKeepAliveTime = :%d\n", g_tUMSStackCfg.m_dwKeepAliveTime);
	msgprint("m_dwRegIP = :"TPIPFORMAT"\n", Tpu32ToIP(g_tUMSStackCfg.m_dwRegIP));
	msgprint("m_wRegPort = :%d\n", g_tUMSStackCfg.m_wRegPort);
}

void regist_ums_sipadapter_commond()
{
#ifdef _LINUX_
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("showreg", (void*)showreg, "showreg()");

#endif
}

