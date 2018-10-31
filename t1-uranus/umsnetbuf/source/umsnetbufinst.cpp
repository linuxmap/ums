#include "umsnetbufinst.h"
#include "umsnetbufcfg.h"
#include "umscommonstruct.h"
#include "innereventumsnetbuf.h"
#include "eventoutumseqp.h"
#include "eventoutumsmediatrans.h"
#include "tpsys.h"
#include "tptime.h"
#include "eventtpsys.h"
#include "umsobject.h"
#include "nbdata.h"
#include "netbuf.h"

const u32 MAX_NETBUF_CAPSET = 1024;

TUmsNetbufCfg	g_tNetbufCfg;
u32 g_dwUmsNode = INVALID_NODE;
u32 g_dwUmsInst = INVALID_NODE;
BOOL32 g_bNbInit = FALSE;	

CTpUmsNetbufApp g_cTPUmsNetbufApp;
API BOOL StartupNetBuf()
{
	g_cTPUmsNetbufApp.CreateApp("NetBufApp",AID_UMSNETBUF_APP,100);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( UMS_NETBUF_APP_INST );
	return TRUE;
}

API void StopNetBuf()
{
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( UMS_NETBUF_APP_INST, 0, UMS_NETBUF_APP_INST);
}



CTpNetBufInst::CTpNetBufInst()
{
	m_wLogModuleId = Ums_Mdl_Media;
	m_pcNbData = NULL;
}


BOOL32 CTpNetBufInst::ObjectInit(u32 wParam, u32 lParam)
{
	msgprint("CTpNetBufInst::ObjectInit\n");
	SetLogTitle("CTpNetBufInst");
		
	if (m_bInit)
	{
		msgprint("CTpNetBufInst::ObjectInit repeat\n");
		return FALSE;
	}

	m_pcNbData = new CNbData;
	if (NULL == m_pcNbData || !m_pcNbData->Init(MAX_NETBUF_CAPSET))
	{
		msgprint("CTpNetBufInst::ObjectInit new CNbData failed\n");
		ObjectExit();
		return FALSE;
	}

	m_bInit = TRUE;
	g_dwUmsNode = INVALID_NODE;

	ConnectToUms();

	return TRUE;
}

void CTpNetBufInst::ObjectExit()
{
	if (INVALID_NODE != g_dwUmsNode)
	{
		OspDisconnectTcpNode(g_dwUmsNode);
	}

	if (NULL != m_pcNbData)
	{
		delete m_pcNbData;
		m_pcNbData = NULL;
	}


	CUmsObject::ObjectExit();
}


void CTpNetBufInst::MessageProc(CTpMsg *const ptMsg)
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
		case ev_NetbufConnectToUms_Time:
			{
				ConnectToUms();
			}		
			break;
			
		case OSP_DISCONNECT:
			{
				OnDisConnect( ptMsg );			
			}
			break;
		case ev_Netbuf_NACK:
			{
				OspDisconnectTcpNode(g_dwUmsNode);
				g_dwUmsNode = INVALID_NODE;
				KillTimer(ev_NetbufConnectToUms_Time);
				SetTimer(ev_NetbufConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
			}
			break;
		case ev_Netbuf_ACK:
			{
				OnRegSuccess(ptMsg);
			}
			break;

		default:
			ObjError(("CTpNetBufInst::MessageProc msg unproess. msg(%d->%s)", wEvent, GetEventNamebyID(wEvent)));
			break;
		}
	}
}

API void reboot();
void CTpNetBufInst::OnDisConnect(CTpMsg *const ptMsg)
{

	g_dwUmsNode = INVALID_NODE;
	m_pcNbData->DelAllNbData();
	KillTimer(ev_NetbufConnectToUms_Time);
	SetTimer(ev_NetbufConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
	return;
}

void CTpNetBufInst::OnRegSuccess(CTpMsg *const ptMsg)
{
	u32 dwIP = GetUmsListenIp();
	msgprint("OnRegSuccess, ServerIp:"TPIPFORMAT"\n", Tpu32ToIP(dwIP));

	TP_SAFE_CAST( g_tNetbufCfg, ptMsg->GetBody());
	KillTimer(ev_NetbufConnectToUms_Time);
	if (!g_bNbInit)
	{
		if (NB_NO_ERROR != nbInit())
		{
			MdlError(Ums_Mdl_Media, ("nbInit error!\n"));
			reboot();
			return;
		}
		else
		{
			g_bNbInit = TRUE;
		}
	}
	

	CTpMsg cMsg;
	cMsg.SetEvent(ev_NetbufInitSuccess_Ind);
	cMsg.SetBody(&g_tNetbufCfg.m_wUmsIndex, sizeof(g_tNetbufCfg.m_wUmsIndex));
	cMsg.Post(UMS_EQP_APP_INST, g_dwUmsNode, UMS_NETBUF_APP_INST);

}


void CTpNetBufInst::ConnectToUms()
{
	MdlHint(Ums_Mdl_Stack, ("ConnectToUms retry!\n"));

	KillTimer(ev_NetbufConnectToUms_Time);
	if (INVALID_NODE != g_dwUmsNode)
	{
		return;
	}

	g_dwUmsNode = ::OspConnectTcpNode(GetUmsListenIp(), GetUmsListenPort());

	if (INVALID_NODE == g_dwUmsNode)
	{
		SetTimer(ev_NetbufConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
	}
	else
	{
		::OspNodeDiscCBReg(g_dwUmsNode, GetAppID(), GetInsID());

		TModelProp tMdl;
		tMdl.m_dwEqpIP = GetLocalIP();
		tMdl.m_wEqpType = em_netbuf_mdl;
		tMdl.m_dwCapSet = MAX_NETBUF_CAPSET;

		CTpMsg cMsg;
		cMsg.SetEvent(ev_Netbuf_Req);
		cMsg.SetBody(&tMdl, sizeof(tMdl));
		cMsg.Post(UMS_EQP_APP_INST, g_dwUmsNode, UMS_NETBUF_APP_INST);
	}	
}

void CTpNetBufInst::OnMsgFromCall(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	switch( wEvent ) 
	{
	case ev_media_nb_create:
		{
			OnCreateMediaNetBuf(ptMsg);
		}
		break;
	case ev_media_nb_remove:
		{
			OnDestroyMediaNetBuf(ptMsg);
		}
		break;
	default:
		ObjError(("CTpNetBufInst::MessageProc msg unproess. msg(%d->%s)", wEvent, GetEventNamebyID(wEvent)));
		break;
	}
}



void CTpNetBufInst::OnCreateMediaNetBuf(CTpMsg *const ptMsg)
{
	TConfEpID* pEpID = (TConfEpID*)ptMsg->GetBody();;
	TUmsRSParam* pRs = (TUmsRSParam*)( ptMsg->GetBody() + sizeof(TConfEpID) );
	TUmsNetBuf* pNb = (TUmsNetBuf*)( ptMsg->GetBody() + sizeof(TUmsRSParam) + sizeof(TConfEpID) );

	CNbListPtr Itor = m_pcNbData->AddNbData(pEpID->m_wConfID, *pNb);
	if (NULL == Itor)
	{
		MdlError(Ums_Mdl_Media, ("CreateNetBuf Failed, no resource!ConfID:%d Snd("ADDRPORT_FORMAT"), RcvRtp ("ADDRPORT_FORMAT")\n"
			, pEpID->m_wConfID, ADDRNET(pNb->m_wSndAddr), ADDRNET(pNb->m_tRcvRtpAddr)));
		return;
	}

	HandleNetbuf tTempHandle = NULL;
	CNetBuf* pNetBuf = new CNetBuf();
	if (NULL == pNetBuf)
	{
		MdlError(Ums_Mdl_Media, ("CreateNetBuf malloc failed. ConfID:%d, RcvRtp ("ADDRPORT_FORMAT")\n"
			, pEpID->m_wConfID, ADDRNET(pNb->m_tRcvRtpAddr)));
		m_pcNbData->DelNbData(pEpID->m_wConfID, *pNb, tTempHandle);
		return;
	}
	
	u16 wRet;
	
	TRSParam tRsPara;
	tRsPara.m_wFirstTimeSpan = pRs->m_wFirstTimeSpan;
	tRsPara.m_wSecondTimeSpan = pRs->m_wSecondTimeSpan;
	tRsPara.m_wThirdTimeSpan = pRs->m_wThirdTimeSpan;
	tRsPara.m_wRejectTimeSpan = pRs->m_wRejectTimeSpan;
	
	wRet = pNetBuf->CreateNetBuf(tRsPara, pNb->m_wSndAddr.m_wPort);
	if (NB_NO_ERROR != wRet)
	{
		MdlError(Ums_Mdl_Media, ("CreateNetBuf failed. ret:%d, ConfID:%d, RcvRtp ("ADDRPORT_FORMAT")\n"
			, wRet, pEpID->m_wConfID, ADDRNET(pNb->m_tRcvRtpAddr)));
		m_pcNbData->DelNbData(pEpID->m_wConfID, *pNb, tTempHandle);
		delete pNetBuf;
		return;
	}
	
	TNetLocalAddr tNatAddr;
	tNatAddr.m_tLocalAddr.m_dwIP = pNb->m_tRcvRtpAddr.m_dwIP;
	tNatAddr.m_tLocalAddr.m_wPort = pNb->m_tRcvRtpAddr.m_wPort;
	
	tNatAddr.m_tRtcpBackAddr.m_dwIP = pNb->m_tRmtRtcpAddr.m_dwIP;
	tNatAddr.m_tRtcpBackAddr.m_wPort = pNb->m_tRmtRtcpAddr.m_wPort;
	
	wRet = pNetBuf->SetLocalAddr(&tNatAddr);
	if (NB_NO_ERROR != wRet)
	{
		MdlError(Ums_Mdl_Media, ("SetLocalAddr failed. ret:%d, ConfID:%d, RcvRtp ("ADDRPORT_FORMAT")\n"
			, wRet, pEpID->m_wConfID, ADDRNET(pNb->m_tRcvRtpAddr)));
		m_pcNbData->DelNbData(pEpID->m_wConfID, *pNb, tTempHandle);
		delete pNetBuf;
		return;
	}
	
	TNetAddr tAddr;
	tAddr.m_dwIP = pNb->m_tRcvRtcpAddr.m_dwIP;
	tAddr.m_wPort = pNb->m_tRcvRtcpAddr.m_wPort;
	wRet = pNetBuf->SetChannelLocalAddr(&tAddr);
	if (NB_NO_ERROR != wRet)
	{
		MdlError(Ums_Mdl_Media, ("SetChannelLocalAddr failed. ret:%d, ConfID:%d, RcvRtp ("ADDRPORT_FORMAT")\n"
			, wRet, pEpID->m_wConfID, ADDRNET(pNb->m_tRcvRtpAddr)));
		m_pcNbData->DelNbData(pEpID->m_wConfID, *pNb, tTempHandle);
		delete pNetBuf;
		return;
	}

	MdlHint(Ums_Mdl_Media, ("CreateNetBuf ConfID:%d Handle:0x%0x, RcvRtp ("ADDRPORT_FORMAT")\n"
		, pEpID->m_wConfID, pNetBuf, ADDRNET(pNb->m_wSndAddr), ADDRNET(pNb->m_tRcvRtpAddr)));
	
	Itor->m_tData.m_Handle = (HandleNetbuf)(pNetBuf);
}


void CTpNetBufInst::OnDestroyMediaNetBuf(CTpMsg *const ptMsg)
{
	TConfEpID* pEpID = (TConfEpID*)ptMsg->GetBody();
	TUmsNetBuf* pNb = (TUmsNetBuf*)( ptMsg->GetBody() + sizeof(TConfEpID) );

	HandleNetbuf tHandle = NULL;
	BOOL32 bRet = m_pcNbData->DelNbData(pEpID->m_wConfID, *pNb, tHandle);
	if (!bRet)
	{
		MdlError(Ums_Mdl_Media, ("OnDestroyMediaNetBuf Failed, no resource! ConfID:%d RcvRtp ("ADDRPORT_FORMAT")\n"
			, pEpID->m_wConfID, ADDRNET(pNb->m_wSndAddr), ADDRNET(pNb->m_tRcvRtpAddr)));
		return;
	}

	if (tHandle != NULL)
	{
		MdlHint(Ums_Mdl_Media, ("OnDestroyMediaNetBuf Handle:0x%x, RcvRtp ("ADDRPORT_FORMAT")\n", tHandle, ADDRNET(pNb->m_tRcvRtpAddr)));
		
		CNetBuf* pNetBuf = (CNetBuf*)tHandle;
		delete pNetBuf;
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("OnDestroyMediaNetBuf Failed, handle NULL!ConfID:%d RcvRtp ("ADDRPORT_FORMAT")\n"
			, pEpID->m_wConfID, ADDRNET(pNb->m_wSndAddr), ADDRNET(pNb->m_tRcvRtpAddr)));
	}
}



enum tp_ums_netbuf_dump
{
	dump_show_nb,
};


void CTpNetBufInst::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_nb:
		m_pcNbData->Show();
		break;
	default:
		break;
	}
}


API void help()
{
	msgprint("ver()\n");
	msgprint("showreg()\n");
	msgprint("shownb()\n");
}

#define  VER_umsnetbuf_ver   UMS_VerID
API void ver()
{
	msgprint("umsnetbuf ver: %s  compile time: %s %s\n",
		VER_umsnetbuf_ver, __DATE__,  __TIME__);
}

API void showreg()
{
	msgprint("m_dwUmsNode = %d\n", g_tNetbufCfg.m_dwUmsNode);
	msgprint("m_wUmsIndex = %d\n", g_tNetbufCfg.m_wUmsIndex);
}


API void shownb(u16 wConfID)
{
	OspInstDump(AID_UMSNETBUF_APP, 1, dump_show_nb);
}



void regist_ums_mediatrans_commond()
{
#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");	
	OspRegCommand("reboot", (void*)reboot, "reboot()");	
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("showreg", (void*)showreg, "showreg()");
	OspRegCommand("shownb", (void*)shownb, "shownb()");
#endif
}

