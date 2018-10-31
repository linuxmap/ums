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
#include "iframecheck.h"
#include "tptime.h"
#include "umsxmltype.h"
#include "umsapi.h"

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

API void sshonoff(BOOL32 bIson)
{
	TPBoardSwitch tBoardSwitch;
	tBoardSwitch.m_bSwitch = bIson;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_media_switchtelnetftp_req);
	cMsg.SetBody(&tBoardSwitch, sizeof(tBoardSwitch));
	cMsg.Post(UMS_MEDIATRANS_APP_INST, 0, UMS_SERVICE_APP_INST);
}

API void StopMediaTrans()
{
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( UMS_MEDIATRANS_APP_INST, 0, UMS_MEDIATRANS_APP_INST);
}

BOOL32   CreatLocalSwitchId(const DSID idMediaDsID, const TTPTransAddr tSrcAddr, DSRTPSID& dLocalId)
{
	dLocalId = tSrcAddr.m_wPort;
	return TRUE;

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
	return TRUE;

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
	return 0;
	dsRtpEndpointStatis tRtpInfo;
	memset(&tRtpInfo, 0, sizeof(tRtpInfo));
	dsGetRtpRtcpSwitchStatistics( dLocalId, &tRtpInfo);
	return tRtpInfo.udpStatis.pkt.totalPkts;
}

u32 GetStatisBySrcDstAddr(const DSRTPSID dLocalId, const TTPTransAddr tSrcAddr, const TTPTransAddr tDstAddr)
{
	return 0;
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
		case ev_IframeRcvCheck_Res:
			{
				OnIFrameRcvCheckRes(ptMsg);
			}
			break;
		case ev_IframeSndCheck_Res:
			{
				OnIFrameSndCheckRes(ptMsg);
			}
			break;

		case ev_IframeSndDisCheck_Res:
			{
				OnIFrameSndDisCheckRes(ptMsg);
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

   	for (u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		m_pcMpData->ClearConfSwitch(wIndex, m_MediaDsID);
	}

	DelAllCheck();
	sshonoff(TRUE);
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
	u32 dwListenIP = GetUmsListenIp();
	msgprint("OnRegSuccess, ServerIp:"TPIPFORMAT"\n", Tpu32ToIP(dwListenIP));

	TP_SAFE_CAST( g_tMediatransCfg, ptMsg->GetBody());
	KillTimer(ev_MediaConnectToUms_Time);

	//点MS业务启用灯(以注册为准)
#if defined(_PPC_82XX_)
	MdlHint(Ums_Mdl_Mpc, ("CTpMediatransInst::OnRegSuccess Set CRI2 Lead State:%d.\n", BRD_LED_ON));
	BrdLedStatusSet(LED_CRI2_MS, BRD_LED_ON);
#endif

	u32 dwIP = GetLocalIP();

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
//开启ntpd
#ifdef _LINUX_
	if (dwListenIP != dwIP)
	{
		CTpTypeAdpt::StartNtpd(dwListenIP);
	}
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

	case ev_media_ds_iframe_bySrc:
		OnAddIFrameCheckBySrc(ptMsg);
		break;
	case ev_media_ds_iframe_TwoRcvPort:
		OnAddIFrameCheckTwoRcvPort(ptMsg);
		break;
	case ev_media_ds_iframe_SndBySrc:
		OnAddIFrameCheckSndBySrc(ptMsg);
		break;
	case ev_media_ds_iframe_SndDis:
		OnAddIFrameCheckSndDis(ptMsg);
		break;
	case ev_media_ds_del_iframe:
		OnDelIFrameCheck(ptMsg);
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
	
	u32 dwRet = dsAddManyToOne(m_MediaDsID, ptData->m_tRcvFromAddr.m_dwIP, ptData->m_tRcvFromAddr.m_wPort, 0
		, ptData->m_tSndToAddr.m_dwIP, ptData->m_tSndToAddr.m_wPort, 0);

	MdlHint(Ums_Mdl_Media, ("dsAddManyToOne ret:%d, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
		, dwRet, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	
	//改源
	if (ptData->m_tMapedAddr.m_wPort != 0)
	{
		dwRet = dsSetSpecifyFwdSrc(m_MediaDsID, ptData->m_tRcvFromAddr.m_dwIP, ptData->m_tRcvFromAddr.m_wPort, 
			ptData->m_tSndToAddr.m_dwIP, ptData->m_tSndToAddr.m_wPort,
			ptData->m_tMapedAddr.m_dwIP, ptData->m_tMapedAddr.m_wPort);
		MdlHint(Ums_Mdl_Media, ("dsSetSpecifyFwdSrc ret:%d, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
			, dwRet, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
	}
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

	u32 dwRet = dsRemoveManyToOne(m_MediaDsID, ptData->m_tRcvFromAddr.m_dwIP, ptData->m_tRcvFromAddr.m_wPort, ptData->m_tSndToAddr.m_dwIP, ptData->m_tSndToAddr.m_wPort);

	MdlHint(Ums_Mdl_Media, ("dsRemoveManyToOne ret:%d, rcv("ADDRPORT_FORMAT")to("ADDRPORT_FORMAT")map("ADDRPORT_FORMAT").\n"
		, dwRet, ADDRNET(ptData->m_tRcvFromAddr), ADDRNET(ptData->m_tSndToAddr), ADDRNET(ptData->m_tMapedAddr)));
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
	s8 achCommand[MAX_COMMEND_LEN];
	s8 achSshInfo[MAX_SSH_INFO];
	u32 dwRet;
	u32 dwlubanRet;
	if (tBrdSwitch.m_bSwitch)
	{
		memcpy(achSshInfo,"start",sizeof("start"));
		sprintf(achCommand, "service sshd %s",achSshInfo);
		dwRet = system(achCommand);
		memset(achCommand,0,sizeof(achCommand));
		sprintf(achCommand, "service luban-sshd %s",achSshInfo);
		dwlubanRet = system(achCommand);
		MdlHint(Ums_Mdl_Service, ("[CTpMediatransInst::EventSwitchSsh] dwRet:%d dwLubanRet:%d bOnOff:%d commond:%s\n", dwRet, dwlubanRet, tBrdSwitch.m_bSwitch, achCommand));
	}
	else
	{
		memcpy(achSshInfo,"stop",sizeof("stop"));
		sprintf(achCommand, "service sshd %s",achSshInfo);
		dwRet = system(achCommand);
		memset(achCommand,0,sizeof(achCommand));
		sprintf(achCommand, "service luban-sshd %s",achSshInfo);
		dwlubanRet = system(achCommand);
		MdlHint(Ums_Mdl_Service, ("[CTpMediatransInst::EventSwitchSsh] dwRet:%d dwLubanRet bOnOff:%d commond:%s\n", dwRet, dwlubanRet, tBrdSwitch.m_bSwitch, achCommand));
	}
#endif
}

s32 PreRcvTimerCB(u32 dwTimerId, void* param)
{
	CTpMediatransInst* pcRunTimerDB = (CTpMediatransInst*)(((CApp*)&g_cTPUmsNetbufApp)->GetInstance(1));
    
    pcRunTimerDB->RcvTimeOut(u32(param));
	return TP_RET_OK;
}

s32 PreSndTimerCB(u32 dwTimerId, void* param)
{
	CTpMediatransInst* pcRunTimerDB = (CTpMediatransInst*)(((CApp*)&g_cTPUmsNetbufApp)->GetInstance(1));
    
    pcRunTimerDB->SndTimeOut(u32(param));
	return TP_RET_OK;
}

void CTpMediatransInst::OnAddIFrameCheckSndBySrc(CTpMsg *const ptMsg)
{
	TUnitData tUnitData;
	TCheckIFrameBase tBase;
	TP_SAFE_CAST(tBase, ptMsg->GetBody());
	TP_SAFE_CAST(tUnitData.m_tSndBySrc, ptMsg->GetBody() + sizeof(tBase));
	MdlHint(Ums_Mdl_Media, ("OnAddIFrameCheckSndBySrc Port:%d, Conf:%d, wExpires:%d, type:%d->%s\n"
		, tBase.m_wPort, tBase.m_wConfID, tBase.m_wExpires,  TpEnumIdString(EmTpIFrameCheckType, tBase.m_emType)));

	tUnitData.m_emType = tBase.m_emType;
	CUnitListPtr Itor = m_tUnitList.WriteBuffItor(tUnitData);
	if (Itor == NULL)
	{
		MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndBySrc, Port:%d, Conf:%d\n", tBase.m_wPort, tBase.m_wConfID));
		return;
	}

	TCheckIFrame* ptIFrame = CMpData::m_tSndCheck.Add(tBase.m_wPort);	
	if (NULL != ptIFrame)
	{
		ENTER_UPDATESEM;
		Itor->m_tData.m_bIFrameCheck = TRUE;
		ptIFrame->AddUnit(tBase, Itor);
		EXIT_UPDATESEM;

		dsSetSendCallback(m_MediaDsID, tBase.m_dwIP, tBase.m_wPort, 0, 0, SndFilterCallBackFun);				
	
		TTpTimer* ptTimer = (TTpTimer*)ptIFrame->m_dwTimerID;
		if (ptTimer)
		{
			m_pcTimerMgr->UpdateTimer(ptTimer);
		}
		else
		{
			ptTimer = m_pcTimerMgr->AddTimer(tBase.m_wExpires, PreSndTimerCB, (void*)((u32)tBase.m_wPort));										
			if (NULL == ptTimer)
			{
				MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndBySrc.AddTimer Failed. Port:%d, ConfID:%d\n", tBase.m_wPort, tBase.m_wConfID));
			}
			ptIFrame->m_dwTimerID = u32(ptTimer);
		}
	}
	else
	{
		m_tUnitList.FreeBuff(Itor);
	}
}

void CTpMediatransInst::OnAddIFrameCheckSndDis( CTpMsg *const ptMsg )
{
	TUnitData tNewUnitData;
	TCheckIFrameBase tNewBase;
	TUnitData tOldUnitData;
	TCheckIFrameBase tOldBase;

	TP_SAFE_CAST(tNewBase, ptMsg->GetBody());
	TP_SAFE_CAST(tNewUnitData.m_tSndDis, ptMsg->GetBody() + sizeof(tNewBase));

	TP_SAFE_CAST(tOldBase, ptMsg->GetBody()+sizeof(tNewBase)+sizeof(TIFrameSndDis));
	TP_SAFE_CAST(tOldUnitData.m_tSndDis, ptMsg->GetBody() + sizeof(tOldBase) + sizeof(tNewBase)+sizeof(TIFrameSndDis));

	MdlHint(Ums_Mdl_Media, ("OnAddIFrameCheckSndDis New Port:%d, Conf:%d, wExpires:%d, type:%d->%s\n"
		, tNewBase.m_wPort, tNewBase.m_wConfID, tNewBase.m_wExpires,  TpEnumIdString(EmTpIFrameCheckType, tNewBase.m_emType)));
	MdlHint(Ums_Mdl_Media, ("                       Old Port:%d, Conf:%d, wExpires:%d, type:%d->%s\n"
		, tOldBase.m_wPort, tOldBase.m_wConfID, tOldBase.m_wExpires,  TpEnumIdString(EmTpIFrameCheckType, tOldBase.m_emType)));
	
	tOldUnitData.m_emType = tOldBase.m_emType;
	tNewUnitData.m_emType = tNewBase.m_emType;

	CUnitListPtr ItorNew = m_tUnitList.WriteBuffItor(tNewUnitData);
	if (ItorNew == NULL)
	{
		MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndDis, new Port:%d, Conf:%d\n", tNewBase.m_wPort, tNewBase.m_wConfID));
		return;
	}

	CUnitListPtr ItorOld = m_tUnitList.WriteBuffItor(tOldUnitData);
	if (ItorOld == NULL)
	{
		m_tUnitList.FreeBuff(ItorNew);
		MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndDis, Old Port:%d, Conf:%d\n", tOldBase.m_wPort, tOldBase.m_wConfID));
		return;
	}
	
	//新 m_bIFrameCheck 为FALSE则不发送  为TRUE则发送
	TCheckIFrame* ptIFrame = CMpData::m_tSndCheck.Add(tNewBase.m_wPort);	
	if (NULL != ptIFrame)
	{
		ENTER_UPDATESEM;
		ItorNew->m_tData.m_bIFrameCheck = FALSE;
		ptIFrame->AddUnit(tNewBase, ItorNew);
		ptIFrame->m_bCheck = TRUE;
		EXIT_UPDATESEM;
		
		dsSetSendCallback(m_MediaDsID, tNewBase.m_dwIP, tNewBase.m_wPort, 0, 0, SndFilterCallBackFun);				
		
		TTpTimer* ptTimer = (TTpTimer*)ptIFrame->m_dwTimerID;
		if (ptTimer)
		{
			m_pcTimerMgr->UpdateTimer(ptTimer);
		}
		else
		{
			ptTimer = m_pcTimerMgr->AddTimer(tNewBase.m_wExpires, PreSndTimerCB, (void*)((u32)tNewBase.m_wPort));										
			if (NULL == ptTimer)
			{
				MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndDis. new AddTimer Failed. Port:%d, ConfID:%d\n", tNewBase.m_wPort, tNewBase.m_wConfID));
			}
			ptIFrame->m_dwTimerID = u32(ptTimer);
		}
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndDis. new  m_tSndCheck.Add Fail! Port:%d, ConfID:%d\n", tNewBase.m_wPort, tNewBase.m_wConfID));

		m_tUnitList.FreeBuff(ItorNew);
		m_tUnitList.FreeBuff(ItorOld);
		return ;
	}

	ptIFrame = CMpData::m_tSndCheck.Add(tOldBase.m_wPort);	
	if (NULL != ptIFrame)
	{
		ENTER_UPDATESEM;
		ItorOld->m_tData.m_bIFrameCheck = TRUE;
		ptIFrame->AddUnit(tOldBase, ItorOld);
		ptIFrame->m_bCheck = TRUE;
		EXIT_UPDATESEM;
		
		dsSetSendCallback(m_MediaDsID, tOldBase.m_dwIP, tOldBase.m_wPort, 0, 0, SndFilterCallBackFun);				
		
		TTpTimer* ptTimer = (TTpTimer*)ptIFrame->m_dwTimerID;
		if (ptTimer)
		{
			m_pcTimerMgr->UpdateTimer(ptTimer);
		}
		else
		{
			ptTimer = m_pcTimerMgr->AddTimer(tOldBase.m_wExpires, PreSndTimerCB, (void*)((u32)tOldBase.m_wPort));										
			if (NULL == ptTimer)
			{
				MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndDis.AddTimer Failed. Port:%d, ConfID:%d\n", tOldBase.m_wPort, tOldBase.m_wConfID));
			}
			ptIFrame->m_dwTimerID = u32(ptTimer);
		}
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckSndDis. Old  m_tSndCheck.Add Fail! Port:%d, ConfID:%d\n", tOldBase.m_wPort, tOldBase.m_wConfID));

		CTpMsg tMsg;
		tMsg.SetEvent(ev_IframeSndCheck_Res);
		tMsg.SetBody(&tNewBase.m_wPort, sizeof(tNewBase.m_wPort));
		tMsg.Post(UMS_MEDIATRANS_APP_INST);
		OnIFrameSndCheckRes(&tMsg);

		m_tUnitList.FreeBuff(ItorOld);
	}
}

void CTpMediatransInst::OnAddIFrameCheckBySrc(CTpMsg *const ptMsg)
{
	TCheckIFrameBase tBase;
	TUnitData tUnitData;
	TP_SAFE_CAST(tBase, ptMsg->GetBody());
	TP_SAFE_CAST(tUnitData.m_tBySrc, ptMsg->GetBody() + sizeof(tBase));
	MdlHint(Ums_Mdl_Media, ("OnAddIFrameCheckBySrc Port:%d, Conf:%d, wExpires:%d, type:%d->%s\n"
		, tBase.m_wPort, tBase.m_wConfID, tBase.m_wExpires,  TpEnumIdString(EmTpIFrameCheckType, tBase.m_emType)));
	
	tUnitData.m_emType = tBase.m_emType;
	CUnitListPtr Itor = m_tUnitList.WriteBuffItor(tUnitData);
	if (Itor == NULL)
	{
		MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckBySrc, Port:%d, Conf:%d\n", tBase.m_wPort, tBase.m_wConfID));
		return;
	}

	TCheckIFrame* ptIFrame = CMpData::m_tRcvCheck.Add(tBase.m_wPort);
	if (NULL != ptIFrame)
	{
		ENTER_UPDATESEM;
		ptIFrame->AddUnit(tBase, Itor);
		EXIT_UPDATESEM;
		
		if( tBase.m_wPort != 0 )
		{
			dsSetFilterFunc(m_MediaDsID, tBase.m_dwIP, tBase.m_wPort, RcvFilterCallBackFun);
		}

		TTpTimer* ptTimer = (TTpTimer*)ptIFrame->m_dwTimerID;
		if (ptTimer)
		{
			m_pcTimerMgr->UpdateTimer(ptTimer);
		}
		else
		{
			ptTimer = m_pcTimerMgr->AddTimer(tBase.m_wExpires, PreRcvTimerCB, (void*)((u32)tBase.m_wPort));
			if (NULL == ptTimer)
			{
				MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckBySrc.AddTimer Failed. Port:%d, ConfID:%d\n", tBase.m_wPort, tBase.m_wConfID));
			}
			ptIFrame->m_dwTimerID = u32(ptTimer);
		}
	}
	else
	{
		MdlHint(Ums_Mdl_Media, ("OnAddIFrameCheckBySrc change direct. Port:%d, Conf:%d, wExpires\n", tBase.m_wPort, tBase.m_wConfID, tBase.m_wExpires));
		
		CTpMsg cMsg;	
		cMsg.SetEvent(ev_media_ds_iframe_bySrc_Ind);
		cMsg.SetBody(&tBase, sizeof(tBase));
		cMsg.CatBody(&tUnitData.m_tBySrc, sizeof(tUnitData.m_tBySrc));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, tBase.m_wConfID), g_dwUmsNode, UMS_MEDIATRANS_APP_INST);

		m_tUnitList.FreeBuff(Itor);
	}
}

void CTpMediatransInst::OnAddIFrameCheckTwoRcvPort(CTpMsg *const ptMsg)
{
	TCheckIFrameBase tBase;
	TUnitData tUnitData;
	TP_SAFE_CAST(tBase, ptMsg->GetBody());
	TP_SAFE_CAST(tUnitData.m_tTwoRcv, ptMsg->GetBody() + sizeof(tBase));
	MdlHint(Ums_Mdl_Media, ("OnAddIFrameCheckTwoRcvPort Port:%d, %d, Conf:%d, wExpires:%d, type:%d->%s\n"
		, tUnitData.m_tTwoRcv.m_wOldPort, tUnitData.m_tTwoRcv.m_wNewPort, tBase.m_wConfID, tBase.m_wExpires,  TpEnumIdString(EmTpIFrameCheckType, tBase.m_emType)));

	TCheckIFrame* ptOld = CMpData::m_tRcvCheck.Add(tUnitData.m_tTwoRcv.m_wOldPort);
	TCheckIFrame* ptNew = CMpData::m_tRcvCheck.Add(tUnitData.m_tTwoRcv.m_wNewPort);
	
	tUnitData.m_emType = tBase.m_emType;
	CUnitListPtr UnitNew = m_tUnitList.WriteBuffItor(tUnitData);
	CUnitListPtr UnitOld = m_tUnitList.WriteBuffItor(tUnitData);
	if (UnitNew == NULL || UnitOld == NULL)
	{
		m_tUnitList.FreeBuff(UnitNew);
		m_tUnitList.FreeBuff(UnitOld);
		MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckTwoRcvPort, Port:%d, Conf:%d\n", tBase.m_wPort, tBase.m_wConfID));
		return;
	}

	if (NULL != ptOld && NULL != ptNew)
	{	

		ENTER_UPDATESEM;
		UnitNew->m_tData.m_tTwoRcv.m_bTrans = FALSE;
		ptNew->AddUnit(tBase, UnitNew);

		UnitOld->m_tData.m_tTwoRcv.m_wOldPort = 0;
		UnitOld->m_tData.m_tTwoRcv.m_bTrans = TRUE;
		ptOld->AddUnit(tBase, UnitOld);
		EXIT_UPDATESEM;
		
		if ( tUnitData.m_tTwoRcv.m_wOldPort != 0 )
		{
			dsSetFilterFunc(m_MediaDsID, tBase.m_dwIP, tUnitData.m_tTwoRcv.m_wOldPort, RcvFilterCallBackFun);
		}
		if ( tUnitData.m_tTwoRcv.m_wNewPort != 0 )
		{
			dsSetFilterFunc(m_MediaDsID, tBase.m_dwIP, tUnitData.m_tTwoRcv.m_wNewPort, RcvFilterCallBackFun);
		}
		
		TTpTimer* ptTimer = (TTpTimer*)ptNew->m_dwTimerID;
		if (ptTimer)
		{
			m_pcTimerMgr->UpdateTimer(ptTimer);
		}
		else
		{
			ptTimer = m_pcTimerMgr->AddTimer(tBase.m_wExpires, PreRcvTimerCB, (void*)((u32)tUnitData.m_tTwoRcv.m_wNewPort));
			if (NULL == ptTimer)
			{
				MdlError(Ums_Mdl_Media, ("OnAddIFrameCheckTwoRcvPort.AddTimer Failed. Port:%d, %d, ConfID:%d\n", tBase.m_wPort, tUnitData.m_tTwoRcv.m_wNewPort, tBase.m_wConfID));
			}
			ptNew->m_dwTimerID = u32(ptTimer);
		}
	}
	else
	{
		if (NULL != ptOld)
		{			
			CMpData::m_tRcvCheck.Del(tBase.m_wPort);	
		}
		if (NULL != ptNew)
		{		
			CMpData::m_tRcvCheck.Del(tUnitData.m_tTwoRcv.m_wNewPort);	
		}

		MdlHint(Ums_Mdl_Media, ("OnAddIFrameCheckTwoRcvPort change direct. Port:%d, %d, Conf:%d, wExpires\n", tBase.m_wPort, tUnitData.m_tTwoRcv.m_wNewPort, tBase.m_wConfID, tBase.m_wExpires));
		
		CTpMsg cMsg;	
		cMsg.SetEvent(ev_media_ds_iframe_TwoRcvPort_Ind);
		cMsg.SetBody(&tBase, sizeof(tBase));
		cMsg.CatBody(&tUnitData.m_tTwoRcv, sizeof(tUnitData.m_tTwoRcv));
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, tBase.m_wConfID), g_dwUmsNode, UMS_MEDIATRANS_APP_INST);

		m_tUnitList.FreeBuff(UnitNew);
		m_tUnitList.FreeBuff(UnitOld);
	}
}	

void CTpMediatransInst::OnDelIFrameCheck(CTpMsg *const ptMsg)
{
	TTPTransAddr tAddr;
	TP_SAFE_CAST(tAddr, ptMsg->GetBody());

	OspDelay(100);

	dsSetFilterFunc(m_MediaDsID, tAddr.m_dwIP, tAddr.m_wPort, NULL);

	BOOL32 bFlag = TRUE;
	ENTER_UPDATESEM;

	bFlag = DelCheck(CMpData::m_tRcvCheck, tAddr.m_wPort);	

	EXIT_UPDATESEM;

	MdlHint(Ums_Mdl_Media, ("OnDelIFrameCheck Port:%d, Ret:%d\n", tAddr.m_wPort, bFlag));
}

void CTpMediatransInst::OnIFrameRcvCheckRes(CTpMsg *const ptMsg)
{
	u16 wRcvPort = *(u16*)ptMsg->GetBody();
	TP_SAFE_CAST(wRcvPort, ptMsg->GetBody());

	TCheckIFrame* ptCheck =  CMpData::m_tRcvCheck.FindByPort(wRcvPort);	
	if (NULL == ptCheck || ptCheck->m_tUnit.GetHead() == NULL)
	{
		MdlError(Ums_Mdl_Media, ("OnIFrameRcvCheckRes Failed port:%d\n", wRcvPort));
		return;
	}

	MdlHint(Ums_Mdl_Media, ("OnIFrameRcvCheckRes confID:%d, port:%d\n", ptCheck->m_wConfID, wRcvPort));

	TTpTimer* ptTimer = (TTpTimer*)ptCheck->m_dwTimerID;
	m_pcTimerMgr->DeleteTimer(ptTimer);
	ptCheck->m_dwTimerID = 0;

	TUnitData* ptUnitData = &ptCheck->m_tUnit.GetHead()->m_tData;
	TCheckIFrameBase tBase;
	tBase.m_wConfID = ptCheck->m_wConfID;
	tBase.m_wExpires = ptCheck->m_wExpires;
	tBase.m_emType = ptUnitData->m_emType;
	tBase.m_dwIP = ptCheck->m_dwIP;
	tBase.m_wPort = ptCheck->m_wPort;

	CTpMsg cMsg;	
	cMsg.SetBody(&tBase, sizeof(tBase));
	
	if (TP_IFrameCheck_Speaker == ptUnitData->m_emType || TP_IFrameCheck_SingleSpeaker == ptUnitData->m_emType)
	{
		cMsg.CatBody(&ptUnitData->m_tBySrc, sizeof(ptUnitData->m_tBySrc));
		cMsg.SetEvent(ev_media_ds_iframe_bySrc_Ind);
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, ptCheck->m_wConfID), g_dwUmsNode, UMS_MEDIATRANS_APP_INST);
	}
	else if (TP_IFrameCheck_Poll == ptUnitData->m_emType)
	{
		cMsg.CatBody(&ptUnitData->m_tTwoRcv, sizeof(ptUnitData->m_tTwoRcv));
		cMsg.SetEvent(ev_media_ds_iframe_TwoRcvPort_Ind);
		cMsg.Post(MAKEIID(AID_UMSCONFMGR, ptCheck->m_wConfID), g_dwUmsNode, UMS_MEDIATRANS_APP_INST);
	}
}

void CTpMediatransInst::OnIFrameSndDisCheckRes( CTpMsg *const ptMsg )
{
	u16 wRcvPort;
	TP_SAFE_CAST(wRcvPort, ptMsg->GetBody());
	u16 wDstPort;
	TP_SAFE_CAST(wDstPort, ptMsg->GetBody()+sizeof(u16));
	
	TCheckIFrame* ptCheck = CMpData::m_tSndCheck.FindByPort(wRcvPort);
	if (NULL == ptCheck)
	{
		MdlError(Ums_Mdl_Media, ("OnIFrameSndDisCheckRes Failed port:%d\n", wRcvPort));
		return;
	}

	MdlHint(Ums_Mdl_Media, ("OnIFrameSndDisCheckRes port:%d, dstport:%d\n", wRcvPort, wDstPort));

	TCheckIFrameBase tBase;
	tBase.m_emType = TP_IFrameCheck_Dis;
	tBase.m_wConfID = ptCheck->m_wConfID;
	tBase.m_wExpires = ptCheck->m_wExpires;
	tBase.m_dwIP = ptCheck->m_dwIP;
	tBase.m_wPort = ptCheck->m_wPort;
	
	CTpMsg cMsg;	
	cMsg.SetBody(&tBase, sizeof(tBase));
	cMsg.CatBody(&wDstPort, sizeof(wDstPort));
	cMsg.SetEvent(ev_media_ds_iframe_byDis_Ind);
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, ptCheck->m_wConfID), g_dwUmsNode, UMS_MEDIATRANS_APP_INST);
}

void CTpMediatransInst::OnIFrameSndCheckRes(CTpMsg *const ptMsg)
{	
	u16 wRcvPort = *(u16*)ptMsg->GetBody();
	TP_SAFE_CAST(wRcvPort, ptMsg->GetBody());
	
	TCheckIFrame* ptCheck = CMpData::m_tSndCheck.FindByPort(wRcvPort);
	if (NULL == ptCheck)
	{
		MdlError(Ums_Mdl_Media, ("OnIFrameSndCheckRes Failed port:%d\n", wRcvPort));
		return;
	}
	
	MdlHint(Ums_Mdl_Media, ("OnIFrameSndCheckRes confID:%d, port:%d\n", ptCheck->m_wConfID, wRcvPort));
	
	if (DelChecked(CMpData::m_tSndCheck, wRcvPort))
	{
		dsSetSendCallback(m_MediaDsID, ptCheck->m_dwIP, ptCheck->m_wPort, 0, 0, 0);

		TTpTimer* ptTimer = (TTpTimer*)ptCheck->m_dwTimerID;
		m_pcTimerMgr->DeleteTimer(ptTimer);
		ptCheck->m_dwTimerID = 0;
	}
}

void CTpMediatransInst::RcvTimeOut(u32 dwPort)
{
	TCheckIFrame* ptCheck = CMpData::m_tRcvCheck.FindByPort((u16)dwPort);
	if (NULL != ptCheck && ptCheck->m_tUnit.GetHead() != NULL)
	{
		MdlHint(Ums_Mdl_Media, ("RcvTimeOut. wConfID:%d, wPort:%d\n", ptCheck->m_wConfID, dwPort));		
		
		TTpTimer* ptTimer = (TTpTimer*)ptCheck->m_dwTimerID;
		m_pcTimerMgr->DeleteTimer(ptTimer);
		ptCheck->m_dwTimerID = 0;

		TUnitData* ptUnitData = &ptCheck->m_tUnit.GetHead()->m_tData;
		
		
		CTpMsg cMsg;	
		TCheckIFrameBase tBase;
		tBase.m_wConfID = ptCheck->m_wConfID;
		tBase.m_wExpires = ptCheck->m_wExpires;
		tBase.m_emType = ptUnitData->m_emType;
		tBase.m_dwIP = ptCheck->m_dwIP;
		tBase.m_wPort = ptCheck->m_wPort;

		cMsg.SetBody(&tBase, sizeof(tBase));

		
		if (TP_IFrameCheck_Speaker == ptUnitData->m_emType || TP_IFrameCheck_SingleSpeaker == ptUnitData->m_emType)
		{
			cMsg.CatBody(&ptUnitData->m_tBySrc, sizeof(ptUnitData->m_tBySrc));
			cMsg.SetEvent(ev_media_ds_iframe_bySrc_Ind);
			cMsg.Post(MAKEIID(AID_UMSCONFMGR, ptCheck->m_wConfID), g_dwUmsNode, UMS_MEDIATRANS_APP_INST);
		}
		else if (TP_IFrameCheck_Poll == ptUnitData->m_emType)
		{
			cMsg.CatBody(&ptUnitData->m_tTwoRcv, sizeof(ptUnitData->m_tTwoRcv));
			cMsg.SetEvent(ev_media_ds_iframe_TwoRcvPort_Ind);
			cMsg.Post(MAKEIID(AID_UMSCONFMGR, ptCheck->m_wConfID), g_dwUmsNode, UMS_MEDIATRANS_APP_INST);
		}
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("RcvTimeOut Failed Port:%d\n", dwPort));
	}
}

void CTpMediatransInst::SndTimeOut(u32 dwPort)
{
	TCheckIFrame* ptIFrame = CMpData::m_tSndCheck.FindByPort((u16)dwPort);
	if (NULL != ptIFrame && ptIFrame->m_tUnit.GetHead() != NULL)
	{
		MdlHint(Ums_Mdl_Media, ("SndTimeOut. wConfID:%d, wPort:%d, Type%d\n", ptIFrame->m_wConfID, dwPort, ptIFrame->m_tUnit.GetHead()->m_tData.m_emType));		
		
		TTpTimer* ptTimer = (TTpTimer*)ptIFrame->m_dwTimerID;
		m_pcTimerMgr->DeleteTimer(ptTimer);
		ptIFrame->m_dwTimerID = 0;
				
		if (TP_IFrameCheck_ChairWait == ptIFrame->m_tUnit.GetHead()->m_tData.m_emType)
		{
			dsSetSendCallback(m_MediaDsID, ptIFrame->m_dwIP, ptIFrame->m_wPort, 0, 0, 0);
		}
		else if (TP_IFrameCheck_Dis == ptIFrame->m_tUnit.GetHead()->m_tData.m_emType)
		{//存在两个的情况，有一个清除，就都清除
			dsSetSendCallback(m_MediaDsID, ptIFrame->m_dwIP, ptIFrame->m_wPort, 0, 0, 0);
		}
		DelCheck(CMpData::m_tSndCheck, (u16)dwPort);
	}
	else
	{
		MdlError(Ums_Mdl_Media, ("SndTimeOut Failed Port:%d\n", dwPort));
	}
}

BOOL32 CTpMediatransInst::DelCheck(CPortVector& cVec, u16 wPort)
{
	TCheckIFrame* pIframe = cVec.FindByPort(wPort);
	if (NULL == pIframe)
	{
		return FALSE;
	}
	m_tUnitList.FreeBuff(pIframe->m_tUnit.GetHead());
	pIframe->m_tUnit.Clear();

	cVec.Del(wPort);
	return TRUE;
}

BOOL32 CTpMediatransInst::DelChecked(CPortVector& cVec, u16 wPort)
{
	TCheckIFrame* ptIframe = cVec.FindByPort(wPort);
	if (NULL == ptIframe)
	{
		return TRUE;
	}

	BOOL32 bDel = TRUE;
	CUnitListPtr Itor = ptIframe->m_tUnit.GetHead();
	while(NULL != Itor)
	{
		if (Itor->m_tData.m_bIFrameCheck)
		{
			bDel = FALSE;
			break;
		}
		Itor = Itor->m_ptNext;
	}

	if (bDel)
	{
		m_tUnitList.FreeBuff(ptIframe->m_tUnit.GetHead());
		ptIframe->m_tUnit.Clear();
		return TRUE;
	}
	
	return FALSE;
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
	msgprint("showrcvpack(BOOL32 bShow)   需要进行接收关键帧检测的码流包\n");	
	msgprint("showsndpack(BOOL32 bShow)   需要进行发送过滤的码流包\n");	
	msgprint("showsenddst(BOOL32 bShow)   发送目标的过滤\n");
	msgprint("showsendinfo(BOOL32 bShow)  发送检测包过程\n");
}

#define  VER_umsmediatrans_ver  UMS_VerID
API void ver()
{
	msgprint("umsmediatrans ver: %s  compile time: %s %s\n",
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
API void showrcvpack(BOOL32 bShow);
API void showsndpack(BOOL32 bShow);
API void showsenddst(BOOL32 bShow);
API void showsndinfo(BOOL32 bShow);
API void startntpd(const s8* pszNtpdIP)
{
	if (NULL == pszNtpdIP)
	{
		return;
	}
	u32_ip dwServerIp = inet_addr(pszNtpdIP);
#ifdef _LINUX_
	CTpTypeAdpt::StartNtpd(dwServerIp);
#endif
}
void regist_ums_mediatrans_commond()
{
#ifdef _LINUX_
	OspRegCommand("help", (void*)help, "help()");	
	OspRegCommand("reboot", (void*)reboot, "reboot()");	
	OspRegCommand("showcfg", (void*)showcfg, "showcfg()");	
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("showreg", (void*)showreg, "showreg()");
	OspRegCommand("showds", (void*)showds, "showds()");
	OspRegCommand("showrcvpack", (void*)showrcvpack, "showrcvpack()");	
	OspRegCommand("showsndpack", (void*)showsndpack, "showsndpack()");	
	OspRegCommand("showsenddst", (void*)showsenddst, "showsenddst()");	
	OspRegCommand("showsndinfo", (void*)showsndinfo, "showsndinfo()");
	OspRegCommand("settest", (void*)settest, "settest()");
	OspRegCommand("destroyds", (void*)destroyds, "destroyds()");
	OspRegCommand("testaddds", (void*)testaddds, "testaddds()");
	OspRegCommand("testdelds", (void*)testdelds, "testdelds()");
	OspRegCommand("sshonoff", (void*)sshonoff, "sshonoff()");
	OspRegCommand("startntpd", (void*)startntpd, "startntpd(s8* pszNtpdIP)");
#endif
}

BOOL32 CTpMediatransInst::DelAllCheck()
{
	TCheckIFrame* ptIFrame = NULL;
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < m_pcMpData->m_tRcvCheck.MaxSize(); wIndex++)
	{
		ptIFrame = m_pcMpData->m_tRcvCheck.FindByIndex(wIndex);
		if (NULL == ptIFrame)
		{
			MdlError(Ums_Mdl_Media, ("Cannot Find Rcv Frame Index:%d\n", wIndex));
			continue;
		}
		if (ptIFrame->m_tUnit.GetElementNum() == 0)
		{
			continue;
		}
		dsSetFilterFunc(m_MediaDsID, ptIFrame->m_dwIP, ptIFrame->m_wPort, NULL);
		m_tUnitList.FreeBuff(ptIFrame->m_tUnit.GetHead());
		ptIFrame->m_tUnit.Clear();	
		m_pcMpData->m_tRcvCheck.Del(ptIFrame->m_wPort);
		
	}
	for (wIndex = 0; wIndex < m_pcMpData->m_tSndCheck.MaxSize(); wIndex++)
	{
		ptIFrame = m_pcMpData->m_tSndCheck.FindByIndex(wIndex);
		if (NULL == ptIFrame)
		{
			MdlError(Ums_Mdl_Media, ("Cannot Find Snd Frame Index:%d\n", wIndex));
			continue;
		}
		if (ptIFrame->m_tUnit.GetElementNum() == 0)
		{
			continue;
		}
		dsSetFilterFunc(m_MediaDsID, ptIFrame->m_dwIP, ptIFrame->m_wPort, NULL);
		m_tUnitList.FreeBuff(ptIFrame->m_tUnit.GetHead());
		ptIFrame->m_tUnit.Clear();	
		m_pcMpData->m_tSndCheck.Del(ptIFrame->m_wPort);
	}
	return TRUE;
}


