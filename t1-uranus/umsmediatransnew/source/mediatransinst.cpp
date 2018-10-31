#include "mediatransrinst.h"
#include "mediatranscfg.h"
#include "umscommonstruct.h"
#include "innereventumsmediatrans.h"
#include "eventoutumsmediatrans.h"
#include "tpsys.h"
#include "tptime.h"
#include "eventtpsys.h"
#include "eventoutumseqp.h"
#include "umsobject.h"
#include "mpdata.h"
#include "tptime.h"
#include "umsxmltype.h"

#if defined(_PPC_82XX_)
#include "nipwrapper.h"
#endif

const u16 MAX_RCV_GRP = 2048;
const u16 MAX_SNDMMB_PERRCVGRP = 64;

TUmsMediatransCfg	g_tMediatransCfg;
//u32 g_dwUmsNode = INVALID_NODE;
extern u32 g_dwUmsNode;
u32 g_dwUmsInst = INVALID_NODE;
extern u32 g_dwUmsListenIp;
BOOL32 g_bDsCreat = FALSE;
extern TIpmaskinfo	g_tIpMaskInfo;

CTpUmsMediatransApp g_cTPUmsNetbufApp;
API BOOL StartupMediaTrans()
{
	g_cTPUmsNetbufApp.CreateApp("MediatransApp",AID_UMSMEDIATRANS_APP,100, 500);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( UMS_MEDIATRANS_APP_INST );
	return TRUE;
}

API void StopMediaTrans()
{
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( UMS_MEDIATRANS_APP_INST, 0, UMS_MEDIATRANS_APP_INST);
}

BOOL32   CreatLocalSwitchId(const DSID idMediaDsID, const TTPTransAddr tSrcAddr, DSRTPSID& dLocalId)
{
	dLocalId = INVALID_RTPSWITCHID;
	if (0 == tSrcAddr.m_dwIP || 0 == tSrcAddr.m_wPort)
	{
		return FALSE;
	}
	dsNetAddr local_addr;

	DS_SET_NETADDR_ADDR(&(local_addr), AF_INET, tSrcAddr.m_dwIP);
	DS_SET_NETADDR_PORT(&(local_addr), AF_INET, tSrcAddr.m_wPort);
	dLocalId = dsCreateRtpRtcpSwitch(idMediaDsID, &local_addr);
	if (INVALID_RTPSWITCHID == dLocalId)
	{
		MdlError(Ums_Mdl_Media, ("CreatLocalSwitchId DSRTPSID error! src("ADDRPORT_FORMAT").\n"
			, ADDRNET(tSrcAddr)));
		return FALSE;
	}
	return TRUE;
}

BOOL32 DestroyLocalSwitchId(const DSID idMediaDsID, const DSRTPSID dLocalId)
{
	if (INVALID_DSID == idMediaDsID || INVALID_RTPSWITCHID == dLocalId)
	{
		return FALSE;
	}
	u32 dwRet = dsDestroyRtpSwitch(idMediaDsID, dLocalId);
	MdlLowHint(Ums_Mdl_Media, ("DestroyLocalSwitchId dwRet:%d, idMediaDsID:%d, dLocalId:%d.\n", 
		dwRet, idMediaDsID, dLocalId));
	return dwRet == DSOK;
}

BOOL32 AddDsRule(const DSID idMediaDsID, const DSRTPSID localdsrtpsid, TUmsDsData* ptData)
{
	if (NULL == ptData || INVALID_DSID == idMediaDsID || INVALID_RTPSWITCHID == localdsrtpsid)
	{
		return FALSE;
	}

//	MdlHint(Ums_Mdl_Media, ("AddDsRule type:%d, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
//		, ptData->m_emSwitchType, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));

	dsRtpEndpoint mdy;
	dsRtpEndpoint dst;
	DS_INIT_RTP_ENDPOINT(&mdy);
	DS_INIT_RTP_ENDPOINT(&dst);

	DS_SET_NETADDR_ADDR(&(dst.addr), AF_INET, ptData->m_tSndToAddr.m_dwIP);
	DS_SET_NETADDR_PORT(&(dst.addr), AF_INET, ptData->m_tSndToAddr.m_wPort);

	u32 dwRet = DSERROR;
	if (ptData->m_emSwitchType == emRtpSwap)
	{
#ifdef WIN32
		dwRet = dsAddRtpSwitchRule(localdsrtpsid, NULL, NULL, &dst, 80);
#else
		if (0 != ptData->m_tMapedAddr.m_wPort)
		{
			DS_SET_NETADDR_ADDR(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_dwIP);
			DS_SET_NETADDR_PORT(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_wPort);
			dwRet = dsAddRtpSwitchRule(localdsrtpsid, NULL, &mdy, &dst, 80);
		}
		else
		{
			dwRet = dsAddRtpSwitchRule(localdsrtpsid, NULL, NULL, &dst, 80);
		}
#endif	
		MdlHint(Ums_Mdl_Media, ("AddDsRule Rtp Ret:%d, id:%u, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, dwRet, localdsrtpsid, ADDRNET(ptData->m_tRcvFromAddr)
			, ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	}
	else if (ptData->m_emSwitchType == emRtcpSwap)
	{
#ifdef WIN32
		dwRet = dsAddRtcpSwitchRule(localdsrtpsid, NULL, NULL, &dst, 80);
#else
		if (0 != ptData->m_tMapedAddr.m_wPort)
		{
			DS_SET_NETADDR_ADDR(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_dwIP);
			DS_SET_NETADDR_PORT(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_wPort);
			dwRet = dsAddRtcpSwitchRule(localdsrtpsid, NULL, &mdy, &dst, 80);
		}
		else
		{
			dwRet = dsAddRtcpSwitchRule(localdsrtpsid, NULL, NULL, &dst, 80);
		}
#endif	
		MdlHint(Ums_Mdl_Media, ("AddDsRule Rtcp Ret:%d, id:%u, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, dwRet, localdsrtpsid, ADDRNET(ptData->m_tRcvFromAddr)
			, ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("AddDsRule unknow Type! id:%u, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, localdsrtpsid, ADDRNET(ptData->m_tRcvFromAddr)
			, ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	}
	return dwRet == DSOK;
}

BOOL32 DelDsRule(const DSID idMediaDsID, const DSRTPSID localdsrtpsid, TUmsDsData* ptData)
{
	if (NULL == ptData || INVALID_DSID == idMediaDsID || INVALID_RTPSWITCHID == localdsrtpsid)
	{
		return INVALID_RTPSWITCHID;
	}

//	MdlHint(Ums_Mdl_Media, ("DelDsRule type:%d, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
//		, ptData->m_emSwitchType, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));

	dsRtpEndpoint mdy;
	dsRtpEndpoint dst;
	DS_INIT_RTP_ENDPOINT(&mdy);
	DS_INIT_RTP_ENDPOINT(&dst);


	DS_SET_NETADDR_ADDR(&(dst.addr), AF_INET, ptData->m_tSndToAddr.m_dwIP);
	DS_SET_NETADDR_PORT(&(dst.addr), AF_INET, ptData->m_tSndToAddr.m_wPort);

	u32 dwRet = DSERROR;
	if (ptData->m_emSwitchType == emRtpSwap)
	{
#ifdef WIN32
		dwRet = dsRemoveRtpSwitchRule(localdsrtpsid, NULL, NULL, &dst);
#else
		if (0 != ptData->m_tMapedAddr.m_wPort)
		{
			DS_SET_NETADDR_ADDR(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_dwIP);
			DS_SET_NETADDR_PORT(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_wPort);
			dwRet = dsRemoveRtpSwitchRule(localdsrtpsid, NULL, &mdy, &dst);
		}
		else
		{
			dwRet = dsRemoveRtpSwitchRule(localdsrtpsid, NULL, NULL, &dst);
		}
#endif	
		MdlHint(Ums_Mdl_Media, ("DelDsRule Rtp Ret:%d, id:%u, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, dwRet, localdsrtpsid, ADDRNET(ptData->m_tRcvFromAddr)
			, ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	}
	else if (ptData->m_emSwitchType == emRtcpSwap)
	{
#ifdef WIN32
		dwRet = dsRemoveRtcpSwitchRule(localdsrtpsid, NULL, NULL, &dst);
#else
		if (0 != ptData->m_tMapedAddr.m_wPort)
		{
			DS_SET_NETADDR_ADDR(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_dwIP);
			DS_SET_NETADDR_PORT(&(mdy.addr), AF_INET, ptData->m_tMapedAddr.m_wPort);
			dwRet = dsRemoveRtcpSwitchRule(localdsrtpsid, NULL, &mdy, &dst);
		}
		else
		{
			dwRet = dsRemoveRtcpSwitchRule(localdsrtpsid, NULL, NULL, &dst);
		}
#endif	
		MdlHint(Ums_Mdl_Media, ("DelDsRule Rtcp Ret:%d, id:%u, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, dwRet, localdsrtpsid, ADDRNET(ptData->m_tRcvFromAddr)
			, ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("DelDsRule unknow Type! id:%u, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, localdsrtpsid, ADDRNET(ptData->m_tRcvFromAddr)
			, ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	}
	return dwRet == DSOK;
}

u32	GetStatisBySrcAddr(const DSRTPSID dLocalId, const TTPTransAddr tSrcAddr)
{
	dsRtpEndpointStatis tRtpInfo;
	memset(&tRtpInfo, 0, sizeof(tRtpInfo));
	dsGetRtpRtcpSwitchStatistics( dLocalId, &tRtpInfo);
	return tRtpInfo.udpStatis.pkt.totalPkts;
}

u32 GetStatisBySrcDstAddr(const DSRTPSID dLocalId, const TTPTransAddr tSrcAddr, const TTPTransAddr tDstAddr)
{
	dsRtpEndpointStatis tSrcRtpInfo;
	dsRtpEndpointStatis tDstRtpInfo;
	dsRtpEndpoint dst;
	memset(&tSrcRtpInfo, 0, sizeof(tSrcRtpInfo));
	memset(&tDstRtpInfo, 0, sizeof(tDstRtpInfo));
	DS_INIT_RTP_ENDPOINT(&dst);
	DS_SET_NETADDR_ADDR(&(dst.addr), AF_INET, tDstAddr.m_dwIP);
	DS_SET_NETADDR_PORT(&(dst.addr), AF_INET, tDstAddr.m_wPort);
	dsGetRtpSwitchRuleStatistics(dLocalId, NULL, &dst, &tSrcRtpInfo, &tDstRtpInfo);
	return tDstRtpInfo.udpStatis.pkt.totalPkts;
}

CTpMediatransInst::CTpMediatransInst()
{
	m_wLogModuleId = Ums_Mdl_Media;
	m_MediaDsID = INVALID_DSID;
	m_pcMpData = NULL;
	m_pcTimerMgr = NULL;
}


BOOL32 CTpMediatransInst::ObjectInit(u32 wParam, u32 lParam)
{
	msgprint("CTpMediatransInst::ObjectInit\n");
	SetLogTitle("CTpMediatransInst");
		
	if (m_bInit)
	{
		msgprint("CTpMediatransInst::ObjectInit repeat\n");
		return FALSE;
	}
	m_pcMpData = new CMpData;
	if (NULL == m_pcMpData || !m_pcMpData->Init(MAX_RCV_GRP * MAX_SNDMMB_PERRCVGRP, MAX_IFRAME_PORT))
	{
		msgprint("CTpMediatransInst::ObjectInit new CMpData failed\n");
		ObjectExit();
		return FALSE;
	}

	m_pcTimerMgr = new CTpTimerMgr();
	if (NULL == m_pcTimerMgr || !m_pcTimerMgr->Create(MAX_IFRAME_PORT))
	{
		msgprint("CTpMediatransInst::ObjectInit new CTpTimerMgr failed\n");
		ObjectExit();
		return FALSE;
	}

	m_tUnitList.Create(1000);

	m_bInit = TRUE;

	ConnectToUms();

	KillTimer(EVTP_TIMER_PER_SECOND);
	SetTimer(EVTP_TIMER_PER_SECOND, TP_INTERVAL_TIME_ONE_SECOND);

	return TRUE;
}

void CTpMediatransInst::ObjectExit()
{
	
	if (INVALID_NODE != g_dwUmsNode)
	{
		OspDisconnectTcpNode(g_dwUmsNode);
	}

	m_pcMpData->Quit(m_MediaDsID);

	if (INVALID_DSID != m_MediaDsID)
	{
		dsDestroy(m_MediaDsID);
		m_MediaDsID = INVALID_DSID;
	}

	if (NULL != m_pcMpData)
	{
		delete m_pcMpData;
		m_pcMpData = NULL;
	}

	if (m_pcTimerMgr)
	{
		delete m_pcTimerMgr;
		m_pcTimerMgr = NULL;
	}

	m_tUnitList.Destroy();

	CUmsObject::ObjectExit();
}


void CTpMediatransInst::MessageProc(CTpMsg *const ptMsg)
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
		case ev_MediaConnectToUms_Time:
			{
				ConnectToUms();
			}		
			break;
			
		case OSP_DISCONNECT:
			{
				OnDisConnect( ptMsg );			
			}
			break;

		case ev_MediaTrans_NACK:
			{
				OspDisconnectTcpNode(g_dwUmsNode);
				g_dwUmsNode = INVALID_NODE;
				KillTimer(ev_MediaConnectToUms_Time);
				SetTimer(ev_MediaConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
			}
			break;

		case ev_MediaTrans_ACK:
			{
				OnRegSuccess(ptMsg);
			}
			break;

		case EVTP_TIMER_PER_SECOND:
			{
				SetTimer(EVTP_TIMER_PER_SECOND, TP_INTERVAL_TIME_ONE_SECOND);
				if (m_pcTimerMgr)
				{	
					m_pcTimerMgr->Check();
				}
			}
			break;
		case ev_media_switchtelnetftp_req:
			{
				OnSwitchSsh(ptMsg);
			}
			break;
		default:
			ObjError(("CTpMediatransInst::MessageProc msg unproess. msg(%d->%s).\n", wEvent, GetEventNamebyID(wEvent)));
			break;
		}
	}
}

API void reboot();
void CTpMediatransInst::OnDisConnect(CTpMsg *const ptMsg)
{
	msgprint("CTpMediatransInst::OnDisConnect.\n");

#if defined(_PPC_82XX_)
	//点灭CRI2板MS业务启用灯
	MdlHint(Ums_Mdl_Mpc, ("CTpMediatransInst::OnDisConnect Set CRI2 M/S Lead State:%d.\n", BRD_LED_OFF));
	BrdLedStatusSet(LED_CRI2_MS, BRD_LED_OFF);
#endif
	
	g_dwUmsNode = INVALID_NODE;
	sshonoff(TRUE);
   	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		m_pcMpData->ClearConfSwitch(wIndex, m_MediaDsID);
	}

	m_pcTimerMgr->DeleteAllTimer();

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	// nothing
#else
	KillTimer(ev_MediaConnectToUms_Time);
 	SetTimer(ev_MediaConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
#endif


	return;
}


void CTpMediatransInst::OnRegSuccess(CTpMsg *const ptMsg)
{
	u32 dwIP = GetUmsListenIp();
	msgprint("OnRegSuccess, ServerIp:"TPIPFORMAT"\n", Tpu32ToIP(dwIP));

	TP_SAFE_CAST( g_tMediatransCfg, ptMsg->GetBody());
	KillTimer(ev_MediaConnectToUms_Time);

	//点MS业务启用灯(以注册为准)
#if defined(_PPC_82XX_)
	MdlHint(Ums_Mdl_Mpc, ("CTpMediatransInst::OnRegSuccess Set CRI2 Lead State:%d.\n", BRD_LED_ON));
	BrdLedStatusSet(LED_CRI2_MS, BRD_LED_ON);
#endif

	dwIP = GetLocalIP();

	if (!g_bDsCreat)
	{
		dsSetCapacity(MAX_RCV_GRP, MAX_SNDMMB_PERRCVGRP);
		m_MediaDsID = dsCreate( 1, &dwIP );
		if (INVALID_DSID == m_MediaDsID)
		{
			MdlError(Ums_Mdl_Media, ("dsCreate error!\n"));
			reboot();
			return;
		}
		g_bDsCreat = TRUE;
	}


#if defined(_PPC_82XX_)
// 	s8 abyBuf[MAX_MSG_LEN_TMP] = {0};
// 	sprintf(abyBuf, "/usr/bin/ntpdate "TPIPFORMAT"", u32ToIP(g_dwUmsListenIp));
// 	system("killall ntpd");
// 	system(abyBuf);
// 	Sleep(1);
// 	system("/usr/bin/ntpd -c /usr/bin/ntp.conf");
#endif

	CTpMsg cMsg;
	cMsg.SetEvent(ev_MediatransInitSuccess_Ind);
	cMsg.SetBody(&g_tMediatransCfg.m_wUmsIndex, sizeof(g_tMediatransCfg.m_wUmsIndex));
	cMsg.Post(UMS_EQP_APP_INST, g_dwUmsNode, UMS_MEDIATRANS_APP_INST);

}

#include "umsapi.h"

void CTpMediatransInst::ConnectToUms()
{
	MdlHint(Ums_Mdl_Stack, ("ConnectToUms retry!\n"));

	KillTimer(ev_MediaConnectToUms_Time);
	if (INVALID_NODE == g_dwUmsNode)
	{
		g_dwUmsNode = ::OspConnectTcpNode(GetUmsListenIp(), GetUmsListenPort());
		if (INVALID_NODE == g_dwUmsNode)
		{
			SetTimer(ev_MediaConnectToUms_Time, TP_INTERVAL_TIME_FIVE_SECOND);
			return;
		}
	}
	
	::OspNodeDiscCBRegQ(g_dwUmsNode, GetAppID(), GetInsID());
	TModelProp tMdl;
	tMdl.m_dwEqpIP = GetLocalIP();
	tMdl.m_wEqpType = em_dataswitch_mdl;
	tMdl.m_dwCapSet = MAX_RCV_GRP * MAX_SNDMMB_PERRCVGRP;

	TIpmaskinfo tIpmask;

	tIpmask.m_dwIpa = g_tIpMaskInfo.m_dwIpa;
	tIpmask.m_dwIpb = g_tIpMaskInfo.m_dwIpb;
	tIpmask.m_dwMaska = g_tIpMaskInfo.m_dwMaska;
	tIpmask.m_dwMaskb = g_tIpMaskInfo.m_dwMaskb;
	tIpmask.m_dwOutIp = g_tIpMaskInfo.m_dwOutIp;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_MediaTrans_Req);
	cMsg.SetBody(&tMdl, sizeof(tMdl));
	cMsg.CatBody(&tIpmask, sizeof(tIpmask));
	cMsg.Post(UMS_EQP_APP_INST, g_dwUmsNode, UMS_MEDIATRANS_APP_INST);

	return;
}

void CTpMediatransInst::OnMsgFromCall(CTpMsg *const ptMsg)
{
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();
	
	switch( wEvent ) 
	{
	case ev_media_ds_create:
		OnAddMediaTrans(ptMsg);	
		break;
		
	case ev_media_ds_remove:
		OnDelMediaTrans( ptMsg );
		break;

	case ev_media_clear_conf:
		OnClearConfTrans(ptMsg);
		break;

	default:
		ObjError(("CTpMediatransInst::MessageProc msg unproess. msg(%d->%s).\n", wEvent, GetEventNamebyID(wEvent)));
		break;
	}
}

inline u32 GetLocalOutIp(u32 dwDstIp)
{
	u32 dwRetIp = 0;
	if (g_tIpMaskInfo.IsValid())
	{
		if (dwDstIp)
		{
			dwRetIp = g_tIpMaskInfo.GetSameNetWork(dwDstIp);
			if (dwRetIp)
			{
				return dwRetIp;
			}
		}

		if (g_tIpMaskInfo.m_dwOutIp)
		{
			return g_tIpMaskInfo.m_dwOutIp;
		}
	}
	return 0;
}

void CTpMediatransInst::OnAddMediaTrans(CTpMsg *const ptMsg)
{
	u16 wConfID;
	TP_SAFE_CAST(wConfID, ptMsg->GetBody());

	TUmsDsData* ptData = (TUmsDsData*)(ptMsg->GetBody() + sizeof(u16));

	u32 dwOutIp = 0;
	if (ptData->m_bNeedModifySrc)
	{
		dwOutIp = GetLocalOutIp(ptData->m_tSndToAddr.m_dwIP);
		if (0 != dwOutIp && dwOutIp != ptData->m_tRcvFromAddr.m_dwIP)
		{
			ptData->m_tMapedAddr.m_dwIP = dwOutIp;
			ptData->m_tMapedAddr.m_wPort = ptData->m_tRcvFromAddr.m_wPort;
			tpLowHint(Ums_Mdl_Media, "AddTrans Modify! OldOutIp:"IPFORMAT", NewOutIp:"IPFORMAT", SrcPort:%d, DstIp:"IPFORMAT", DstPort:%d.\n", 
				u32ToIP(ptData->m_tRcvFromAddr.m_dwIP), u32ToIP(dwOutIp), ptData->m_tRcvFromAddr.m_wPort, 
				u32ToIP(ptData->m_tSndToAddr.m_dwIP), ptData->m_tSndToAddr.m_wPort);
		}
	}

	DSRTPSID tlocalId = INVALID_RTPSWITCHID;
	if (!m_pcMpData->AddSwitch(m_MediaDsID, wConfID, ptData, tlocalId))
	{
		MdlError(Ums_Mdl_Media, ("AddTrans failed! tlocalId:%u, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, tlocalId, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
		return;
	}

//	MdlHint(Ums_Mdl_Media, ("AddTrans rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
//			, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));

	// 添加一条交换规则
	AddDsRule(m_MediaDsID, tlocalId, ptData);
	
	return;
}

void CTpMediatransInst::OnDelMediaTrans(CTpMsg *const ptMsg)
{
	u16 wConfID;
	TP_SAFE_CAST(wConfID, ptMsg->GetBody());
	TUmsDsData* ptData = (TUmsDsData*)(ptMsg->GetBody() + sizeof(u16));

	DSRTPSID tlocalId = INVALID_RTPSWITCHID;
	if (!m_pcMpData->DelSwitch(wConfID, ptData, tlocalId))
	{
		MdlError(Ums_Mdl_Media, ("DelTrans Not find ds! rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
		//不返回继续删除
	}

//	MdlHint(Ums_Mdl_Media, ("DelTrans rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
//		, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));

	// 删除一条交换规则
	DelDsRule(m_MediaDsID, tlocalId, ptData);
	
	return;
}

void CTpMediatransInst::OnClearConfTrans(CTpMsg *const ptMsg)
{
	u16 wConfID;
	TP_SAFE_CAST(wConfID, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Media, ("OnClearConfTrans ConfID:%d.\n", wConfID));

	m_pcMpData->ClearConfSwitch(wConfID, m_MediaDsID);
}
void CTpMediatransInst::OnSwitchSsh(CTpMsg *const ptMsg)
{
	TPBoardSwitch tBrdSwitch;
	TP_SAFE_CAST(tBrdSwitch, ptMsg->GetBody());
#ifdef _LINUX_ 
	s8 achCommand[255];
	s8 achSshInfo[10];
	u32 dwRet;
	if (tBrdSwitch.m_bSwitch)
	{
		memcpy(achSshInfo,"start",sizeof("start"));
		sprintf(achCommand, "service sshd %s",achSshInfo);
		dwRet = system(achCommand);
		MdlHint(Ums_Mdl_Service, ("[CTpMediatransInst::EventSwitchSsh] dwRet:%d bOnOff:%d commond:%s\n", dwRet,tBrdSwitch.m_bSwitch, achCommand));
	}
	else
	{
		memcpy(achSshInfo,"stop",sizeof("stop"));
		sprintf(achCommand, "service sshd %s",achSshInfo);
		dwRet = system(achCommand);
		MdlHint(Ums_Mdl_Service, ("[CTpMediatransInst::EventSwitchSsh] dwRet:%d bOnOff:%d commond:%s\n", dwRet,tBrdSwitch.m_bSwitch, achCommand));
	}
#endif
}

enum tp_ums_media_dump
{
	dump_show_ds,
	dump_show_dsall,
};

void CTpMediatransInst::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_ds:
		{
			if (m_pcMpData != NULL)
			{
				m_pcMpData->ShowSwitch(m_MediaDsID);
				m_tUnitList.Show();
			}
		}		
		break;
	case dump_show_dsall:
		{
			if (m_pcMpData != NULL)
			{
				m_pcMpData->ShowSwitch(m_MediaDsID,1);
				m_tUnitList.Show();
			}
		}
		break;
	default:
		break;
	}
}


API void help()
{
	msgprint("ver()                       版本号\n");
	msgprint("showcfg()                   本地配置\n");
	msgprint("showreg()                   注册信息\n");
	msgprint("showds()                    所有转发\n");
}

#define  VER_umsmediatrans_ver  UMS_VerID
API void ver()
{
	msgprint("umsmediatransnew ver: %s  compile time: %s %s\n",
		VER_umsmediatrans_ver, __DATE__,  __TIME__);
}

API void showreg()
{
	msgprint("m_dwUmsNode = %d\n", g_tMediatransCfg.m_dwUmsNode);
	msgprint("m_wUmsIndex = %d\n", g_tMediatransCfg.m_wUmsIndex);
}

API void showds(u8 byPrintType = 0)
{
	if (0 == byPrintType)
	{
		OspInstDump(AID_UMSMEDIATRANS_APP, 1, dump_show_ds);
	}
	else
	{
		OspInstDump(AID_UMSMEDIATRANS_APP, 1, dump_show_dsall);
	}
}

API void destroyds(DSID dwId, DSRTPSID dwRtpId)
{
	DestroyLocalSwitchId(dwId, dwRtpId);
}

API void testaddds(DSID dwid, u8 byType, s8* srcip, u16 srcPort, s8* dstip, u16 dstport, s8* mapip = NULL, u16 mapport = 0)
{
	TUmsDsData tData;
	TUmsDsData* ptData=&tData;

	ptData->m_emSwitchType = (EmSwitchType)byType;
	ptData->m_tRcvFromAddr.m_dwIP = inet_addr(srcip);
	ptData->m_tRcvFromAddr.m_wPort = srcPort;
	ptData->m_tSndToAddr.m_dwIP = inet_addr(dstip);	
	ptData->m_tSndToAddr.m_wPort = dstport;

	if (NULL != mapip && 0 != mapport)
	{
		ptData->m_tMapedAddr.m_dwIP = inet_addr(mapip);
		ptData->m_tMapedAddr.m_wPort = mapport;
	}


	u16 wConfId = 1;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_media_ds_create);
	cMsg.SetBody(&wConfId, sizeof(wConfId));
	cMsg.CatBody(ptData, sizeof(TUmsDsData));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, 0, UMS_CALL_APP_INST(1));
}


API void sshonoff(BOOL32 bIson)
{
	TPBoardSwitch tBoardSwitch;
	tBoardSwitch.m_bSwitch = bIson;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_media_switchtelnetftp_req);
	cMsg.SetBody(&tBoardSwitch, sizeof(tBoardSwitch));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, 0, UMS_SERVICE_APP_INST);
}

API void testdelds(DSID dwid, u8 byType, s8* srcip, u16 srcPort, s8* dstip, u16 dstport, s8* mapip = NULL, u16 mapport = 0)
{
	TUmsDsData tData;
	TUmsDsData* ptData=&tData;

	ptData->m_emSwitchType = (EmSwitchType)byType;
	ptData->m_tRcvFromAddr.m_dwIP = inet_addr(srcip);
	ptData->m_tRcvFromAddr.m_wPort = srcPort;
	ptData->m_tSndToAddr.m_dwIP = inet_addr(dstip);	
	ptData->m_tSndToAddr.m_wPort = dstport;

	if (NULL != mapip && 0 != mapport)
	{
		ptData->m_tMapedAddr.m_dwIP = inet_addr(mapip);
		ptData->m_tMapedAddr.m_wPort = mapport;
	}

	u16 wConfId = 1;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_media_ds_remove);
	cMsg.SetBody(&wConfId, sizeof(wConfId));
	cMsg.CatBody(ptData, sizeof(TUmsDsData));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, 0, UMS_CALL_APP_INST(1));
}

API void settest(u32 dwTest);
API void showcfg();
void regist_ums_mediatrans_commond()
{
#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");	
	OspRegCommand("reboot", (void*)reboot, "reboot()");	
	OspRegCommand("showcfg", (void*)showcfg, "showcfg()");	
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("showreg", (void*)showreg, "showreg()");
	OspRegCommand("showds", (void*)showds, "showds()");
	OspRegCommand("settest", (void*)settest, "settest()");
	OspRegCommand("destroyds", (void*)destroyds, "destroyds()");
	OspRegCommand("testaddds", (void*)testaddds, "testaddds()");
	OspRegCommand("testdelds", (void*)testdelds, "testdelds()");
	OspRegCommand("sshonoff", (void*)sshonoff, "sshonoff()");
	
#endif
}


