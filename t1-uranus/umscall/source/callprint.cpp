#include "umsconfinst.h"
#include "callnodemgr.h"
#include "umsdiscussnew.h"
#include "dualmgr.h"
#include "umsvmp.h"
#include "umsbas.h"
#include "umseapu.h"
#include "umsnetportmgr.h"
#include "tvwallmgr.h"
#include "getvidaud.h"
#include "innereventtvwall.h"
#include "eventoutumscall.h"
#include "eventoutsipadapter.h"
#include "innereventumscall.h"
#include "innereventumsaudiomix.h"
#include "eventoutumsselview.h"
#include "selviewmgr.h"
#include "umsreg.h"
#include "eventoutumsbrdvmp.h"
#include "pollmgr.h"
#include "nodefsm.h"
#include "dataconfhandler.h"
#include "umsaudmix.h"
#include "umsgetconfvidaud.h"
#include "umsmcumgr.h"

namespace UmsTpmsg {
void tplocaltime(struct tm& t, const time_t& ti);
} //namespace UmsTpmsg
//////////////////////////////////////////////////////////////////////////
#define  VER_umscall_ver UMS_VerID
API void callver()
{
	msgprint("umscall ver: %s  compile time: %s:%s\n",
		VER_umscall_ver, __DATE__,  __TIME__);
}

API void showumsreg()
{
	CUmsRegMgr* pRegMgr = CUmsConfInst::GetRegMgr();
	if (NULL == pRegMgr)
	{
		msgprint("get pRegMgr error...\n");
	}
	else
	{
		pRegMgr->Show();
	}
}

extern CUmsCallMgrApp g_cUmsCallMgrApp;
API void setpolltime(u16 wConfID, u16 wTime)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	if (NULL != pInst)
	{
		pInst->SetPollTimeInterval(wTime);
	}
}

API void mixone(u16 wConfID)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	if (NULL != pInst)
	{
		pInst->GetEapu()->AssignMixer(NULL, pInst);
	}
}

API void mixthree(u16 wConfID)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	if (NULL != pInst)
	{
		TAudMixInfo* pInfo = pInst->GetEapu()->AssignMixer(NULL, pInst, 10, 3);

		if (NULL != pInfo)
		{
			u32 wNode = pInfo->m_tEqpRes.m_dwEqpNode;
			
			pInst->GetEapu()->AssignMixer(NULL, pInst, 10, 3, wNode);
			pInst->GetEapu()->AssignMixer(NULL, pInst, 10, 3, wNode);
		}
	}
}



static void GetChairHandle(TUmsHandle& tHandle, u16 wConfID, u16 wChanID)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	if (NULL == pInst)
	{
		return;		
	}
	
	
	TCapNode* ptNode = (TCapNode*)pInst->GetNode(pInst->chairID());
	if (NULL == ptNode)
	{
		return;
	}
	
	if (wChanID >= TP_MAX_STREAMNUM)
	{
		return;
	}
	tHandle.MakeAppHandle(wConfID, pInst->chairID());
	tHandle.handPaCall = ptNode->m_dwStackHandle;
	tHandle.handPaChan = ptNode->m_tRmtChan.m_atVidDec[wChanID].m_tPAHandle;
}

static void NotifyMsgToCall(u16 wEvent, const TUmsHandle& tHandle, void* pBuf, u16 wSize)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	if (NULL != pBuf)
	{
		cMsg.CatBody(pBuf, wSize);
	}
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

enum tp_ums_call_dump
{
	dump_show_call,
	dump_show_port,
	dump_show_ds,
	dump_show_poll,
	dump_show_dis,
	dump_show_dual,
	dump_show_allport,
	dump_show_tv,
	dump_show_vmp,
	dump_show_bas,
	dump_show_eapu,
	dump_show_portres,
	dump_show_resfrm,
	dump_show_selview,
	dump_show_getvidaudex,
	dump_show_bw,
	dump_show_eqpser,
	dump_show_cm,
	dump_show_rollcall,
	dump_show_audmix,
	dump_show_getstream,
	dump_show_getmcumgr,
	dump_show_qtaliasdata,
	dump_show_eplist,
};


void CUmsConfInst::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_call:
		ShowCallInfo();
		break;
	case dump_show_port:
		ShowCallPort();
		break;
	case dump_show_ds:
		ShowCallDs();
		break;
	case dump_show_poll:
		ShowCallPoll();
		break;
	case dump_show_dis:
		ShowDiscuss();
		break;
	case dump_show_eapu:
		ShowEapu();
		break;
	case dump_show_dual:
		ShowAudDual();
		break;
	case dump_show_allport:
		ShowAllPort();
		break;
	case dump_show_tv:
		ShowTv();
		break;
	case dump_show_vmp:
		ShowVmp();
		break;
	case dump_show_bas:
		ShowBas();
		break;
	case dump_show_resfrm:
		ShowResFrm();
		break;
	case dump_show_selview:
		ShowSelView();
		break;
	case dump_show_getvidaudex:
		m_pcGetVidEx->Show(GetInsID());
		break;
	case dump_show_bw:
		m_cBw.ShowBW();
		break;
	case dump_show_eqpser:
		CEqpService::Instance().Show();
		break;
	case dump_show_cm:
		ShowConfMgr();
		break;

	case dump_show_rollcall:
        ShowRollCall();
		break;

	case dump_show_audmix:
        ShowAudMix();
		break;

	case dump_show_getstream:
        ShowGetStream();
		break;
	case dump_show_getmcumgr:
		ShowMcuMgr();
		break;
	case dump_show_eplist:
		{
			m_pcNodeMgr->showip();
		}
		break;
	default:
		break;
	}
}

void CUmsConfInst::DaemonInstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_portres:
		{
			DaemonShowPortRes();
		}
		break;
	case dump_show_qtaliasdata:
		{
            m_QueryAliasMgr.Show();
		}
		break;

	}
}	


API void umscall(int callID)
{
	if (callID == 0)
	{
		for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; ++wIndex)
		{
			OspInstDump(AID_UMSCONFMGR,  wIndex+1, dump_show_call);
		}
	}
	else
	{
		OspInstDump(AID_UMSCONFMGR,  callID, dump_show_call);
	}
	
}


API void umsport(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_port);
	}	
}


API void umsds(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_ds);
	}	
}

API void umspoll(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_poll);
	}	
}

API void umsdis(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_dis);
	}	
}

API void umsview(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_selview);
	}
}

API void umseapu(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_eapu);
	}	
}


API void umsdual(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_dual);
	}	
}

API void umsallport(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_allport);
	}	
}

API void umsvmp(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_vmp);
	}
}

API void umsbas(int callID)
{
	if (callID != 0)
	{
		OspInstDump(AID_UMSCONFMGR, callID, dump_show_bas);
	}
}

API void umsgetvid(int callID)
{
	OspInstDump(AID_UMSCONFMGR, callID, dump_show_getvidaudex);
}

API void umsbw(int callID)
{
	OspInstDump(AID_UMSCONFMGR, callID, dump_show_bw);
}

API void umsvmptp()
{
	OspInstDump(AID_UMSCONFMGR, 1, dump_show_eqpser);
}

API void umscm()
{
	OspInstDump(AID_UMSCONFMGR, 1, dump_show_cm);
}

API void umseplist(int callID)
{
	if (callID == 0)
	{
		for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; ++wIndex)
		{
			OspInstDump(AID_UMSCONFMGR,  wIndex+1, dump_show_eplist);
		}
	}
	else
	{
		OspInstDump(AID_UMSCONFMGR,  callID, dump_show_eplist);
	}
}

API void umsaudmix(int callID)
{
	OspInstDump(AID_UMSCONFMGR, callID, dump_show_audmix);
}

API void umsgetstream(int callID)
{
	OspInstDump(AID_UMSCONFMGR, callID, dump_show_getstream);
}

API void umsshowmcu(int callID)
{
	OspInstDump(AID_UMSCONFMGR, callID, dump_show_getmcumgr);
}

API void umstv()
{
	OspInstDump(AID_UMSCONFMGR, 1, dump_show_tv);
}

API void umsportres()
{
	OspInstDump(AID_UMSCONFMGR,  CInstance::DAEMON, dump_show_portres);
}

API void umsresfrm(int callID)
{
	OspInstDump(AID_UMSCONFMGR, callID, dump_show_resfrm);
}

API void umsrollcall(int callID)
{
	OspInstDump(AID_UMSCONFMGR, callID, dump_show_rollcall);
}

API void qtaliasdata()
{
	OspInstDump(AID_UMSCONFMGR, CInstance::DAEMON, dump_show_qtaliasdata);
}

extern CUmsCallMgrApp g_cUmsCallMgrApp;
void CUmsConfInst::DaemonShowPortRes()
{
	u32 dwIndex = 0;

	u32 dwNum = 0;

	dwNum = m_cLocChanAddrMgr.GetTotalNum();
	msgprintnotime("loc chan, num:%d. rtp,rtcpForRcv,rtcpForSnd, left, right, rtp,rtcpForRcv,rtcpForSnd\n", dwNum);
    for (dwIndex = 0; dwIndex < dwNum; ++dwIndex)
    {
		TLocalChanAddr* ptChan = m_cLocChanAddrMgr.GetDataByIndex(dwIndex);
	
		msgprintnotime("  chan:%3d, vid(%d,%d,%d), aud(%d,%d,%d)\n", dwIndex + 1
			, ptChan->m_tVid.m_tRtpAddr.m_wPort, ptChan->m_tVid.m_tRtcpForRcv.m_wPort, ptChan->m_tVid.m_tRtcpForSnd.m_wPort
			, ptChan->m_tAud.m_tRtpAddr.m_wPort, ptChan->m_tAud.m_tRtcpForRcv.m_wPort, ptChan->m_tAud.m_tRtcpForSnd.m_wPort);
		OspDelay(10);
    }
	
	dwNum = m_clocDualAddrMgr.GetTotalNum();
	msgprintnotime("dual chan, num:%d. rtp,rtcpForRcv,rtcpForSnd, rtp,rtcpForRcv,rtcpForSnd\n", dwNum);
	for (dwIndex = 0; dwIndex < dwNum; ++dwIndex)
    {		
		TSingleScreenAddr* ptDual = m_clocDualAddrMgr.GetDataByIndex(dwIndex);
		msgprintnotime("  chan:%3d, vid:(%d,%d,%d), aud:(%d,%d,%d)\n", dwIndex + 1
			, ptDual->m_tVid.m_tRtpAddr.m_wPort, ptDual->m_tVid.m_tRtcpForRcv.m_wPort, ptDual->m_tVid.m_tRtcpForSnd.m_wPort
			, ptDual->m_tAud.m_tRtpAddr.m_wPort, ptDual->m_tAud.m_tRtcpForRcv.m_wPort, ptDual->m_tAud.m_tRtcpForSnd.m_wPort);
		OspDelay(10);
    }
	
	dwNum = m_cLocSmallChanAddrMgr.GetTotalNum();
	msgprintnotime("smallvid chan, num:%d. rtp,rtcpForRcv,rtcpForSnd, rtp,rtcpForRcv,rtcpForSnd\n", dwNum);
	for (dwIndex = 0; dwIndex < dwNum; ++dwIndex)
	{		
		TChanRcvAddr* ptChanSmall = m_cLocSmallChanAddrMgr.GetDataByIndex(dwIndex);

		msgprintnotime("  chan:%3d, smallvid:(%d,%d,%d)", dwIndex + 1
			, ptChanSmall->m_tRtpAddr.m_wPort, ptChanSmall->m_tRtcpForRcv.m_wPort, ptChanSmall->m_tRtcpForSnd.m_wPort);
		if (dwIndex % 2 == 1)
		{
			msgprintnotime("\n");
		}
		else
		{
			msgprintnotime("  ");
		}
		OspDelay(10);
	}

	dwNum = m_clocMixAddrMgr.GetTotalNum();
	msgprintnotime("audmix chan, num:%d. rtp,rtcpForRcv,rtcpForSnd\n", dwNum);
	for (dwIndex = 0; dwIndex < dwNum; ++dwIndex)
    {
		TChanRcvAddr* ptMixRcv = m_clocMixAddrMgr.GetDataByIndex(dwIndex);	
		
		msgprintnotime("  chan:%3d, mixaud:(%d,%d,%d)", dwIndex + 1
			, ptMixRcv->m_tRtpAddr.m_wPort, ptMixRcv->m_tRtcpForRcv.m_wPort, ptMixRcv->m_tRtcpForSnd.m_wPort);

		if (dwIndex % 2 == 1)
		{
			msgprintnotime("\n");
		}
		else
		{
			msgprintnotime("  ");
		}
		OspDelay(10);
    }

	dwNum = m_cCascadeChairAddrMgr.GetTotalNum();
	msgprintnotime("for CascadeChair node, num:%d. rtp,rtcpForRcv,rtcpForSnd\n", dwNum);
	//接收视频地址
    for (dwIndex = 0; dwIndex < dwNum; ++dwIndex)
    {		
		TCascadeChairAddr* itor = m_cCascadeChairAddrMgr.GetDataByIndex(dwIndex);
		for (u16 wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
		{
			msgprintnotime("  node:%3d, vid:(%d,%d,%d), aud:(%d,%d,%d)\n", dwIndex + 1
				, itor->m_atVid[wChanIndex].m_tRtpAddr.m_wPort, itor->m_atVid[wChanIndex].m_tRtcpForRcv.m_wPort, itor->m_atVid[wChanIndex].m_tRtcpForSnd.m_wPort
				, itor->m_atAud[wChanIndex].m_tRtpAddr.m_wPort, itor->m_atAud[wChanIndex].m_tRtcpForRcv.m_wPort, itor->m_atAud[wChanIndex].m_tRtcpForSnd.m_wPort);
		}
		msgprintnotime("  node:%3d, MixAud:(%d,%d,%d), DisSingleVid(%d,%d,%d), DisSingleAud(%d,%d,%d)\n", dwIndex + 1
			, itor->m_tMixAud.m_tRtpAddr.m_wPort, itor->m_tMixAud.m_tRtcpForRcv.m_wPort, itor->m_tMixAud.m_tRtcpForSnd.m_wPort
			, itor->m_tDisSingleVid.m_tRtpAddr.m_wPort, itor->m_tDisSingleVid.m_tRtcpForRcv.m_wPort, itor->m_tDisSingleVid.m_tRtcpForSnd.m_wPort
			, itor->m_tDisSingleAud.m_tRtpAddr.m_wPort, itor->m_tDisSingleAud.m_tRtcpForRcv.m_wPort, itor->m_tDisSingleAud.m_tRtcpForSnd.m_wPort);
		OspDelay(10);
    }
	TTPMediaTransAddr* ptStartChan = NULL;
	TTPMediaTransAddr* ptEndChan   = NULL;

	//轮询地址
	dwNum = m_cLocPollAddrMgr.GetTotalNum();
	msgprintnotime("Poll List, num:%d, FreeNum:%d. rtp,rtcp\n", dwNum,m_cLocPollAddrMgr.GetFreeBlocks());
	ptStartChan = m_cLocPollAddrMgr.GetDataByIndex(0);
	ptEndChan   = m_cLocPollAddrMgr.GetDataByIndex(dwNum - 1);
	msgprintnotime("Poll list: Begin:(%d,%d)  End:(%d,%d)\n"
			, ptStartChan->m_tRtpAddr.m_wPort,ptStartChan->m_tBackRtcpAddr.m_wPort
			, ptEndChan->m_tRtpAddr.m_wPort,ptEndChan->m_tBackRtcpAddr.m_wPort);
	OspDelay(10);
   

    //点名地址
	dwNum = m_cLocRollAddrMgr.GetTotalNum();
	msgprintnotime("Roll List, num:%d, FreeNum:%d. rtp,rtcp\n", dwNum,m_cLocRollAddrMgr.GetFreeBlocks());
	ptStartChan = m_cLocRollAddrMgr.GetDataByIndex(0);
	ptEndChan   = m_cLocRollAddrMgr.GetDataByIndex(dwNum - 1);
	msgprintnotime("Roll list: Begin:(%d,%d)  End:(%d,%d)\n"
			, ptStartChan->m_tRtpAddr.m_wPort,ptStartChan->m_tBackRtcpAddr.m_wPort
			, ptEndChan->m_tRtpAddr.m_wPort,ptEndChan->m_tBackRtcpAddr.m_wPort);
	OspDelay(10);

	//上下级音频通道地址
	dwNum = m_cPutAudAddrMgr.GetTotalNum();
	msgprintnotime("PutAud List, num:%d, FreeNum:%d. rtp,rtcp\n", dwNum,m_cPutAudAddrMgr.GetFreeBlocks());
	ptStartChan = m_cPutAudAddrMgr.GetDataByIndex(0);
	ptEndChan   = m_cPutAudAddrMgr.GetDataByIndex(dwNum - 1);
	msgprintnotime("PutAud list: Begin:(%d,%d)  End:(%d,%d)\n"
		, ptStartChan->m_tRtpAddr.m_wPort,ptStartChan->m_tBackRtcpAddr.m_wPort
		, ptEndChan->m_tRtpAddr.m_wPort,ptEndChan->m_tBackRtcpAddr.m_wPort);
   	OspDelay(10);

	//混音器地址
	dwNum = m_cEapuAddrMgr.GetTotalNum();
	msgprintnotime("Eapu List, num:%d, FreeNum:%d. rtp,rtcp\n", dwNum,m_cEapuAddrMgr.GetFreeBlocks());
	ptStartChan = m_cEapuAddrMgr.GetDataByIndex(0);
	ptEndChan   = m_cEapuAddrMgr.GetDataByIndex(dwNum - 1);
	msgprintnotime("Eapu list: Begin:(%d,%d)  End:(%d,%d)\n"
		, ptStartChan->m_tRtpAddr.m_wPort,ptStartChan->m_tBackRtcpAddr.m_wPort
		, ptEndChan->m_tRtpAddr.m_wPort,ptEndChan->m_tBackRtcpAddr.m_wPort);
	OspDelay(10);

	//动态分配
	dwNum = m_cAddrList.GetTotalNum();
	msgprintnotime("Addr List, num:%d, FreeNum:%d. rtp,rtcp\n", dwNum, m_cAddrList.GetFreeBlocks());
	ptStartChan = m_cAddrList.GetDataByIndex(0);
	ptEndChan = m_cAddrList.GetDataByIndex(dwNum - 1);

	msgprintnotime("Addr list: Begin:(%d,%d)  End:(%d,%d)\n"
		, ptStartChan->m_tRtpAddr.m_wPort,ptStartChan->m_tBackRtcpAddr.m_wPort
		, ptEndChan->m_tRtpAddr.m_wPort,ptEndChan->m_tBackRtcpAddr.m_wPort);



	OspDelay(100);
	for( u16 wIndex = 1; wIndex <= TP_UMS_MAX_CONFNUM; wIndex++ )
	{
		CInstance* pcInst = ((CApp*)&g_cUmsCallMgrApp)->GetInstance(wIndex);
		((CUmsConfInst*)pcInst)->ShowPortRes();
		OspDelay(10);
	}
}


void CUmsConfInst::ShowPortRes()
{
	msgprintnotime("ConfID:%d\n", GetInsID());
	msgprintnotime("  vir speaker vid: 1(%d,%d), 2(%d,%d), 3(%d,%d), single(%d,%d)\n"
		,m_cSpeaker.m_atVidDec[0].m_tRtpAddr.m_wPort, m_cSpeaker.m_atVidDec[0].m_tBackRtcpAddr.m_wPort
		,m_cSpeaker.m_atVidDec[1].m_tRtpAddr.m_wPort, m_cSpeaker.m_atVidDec[1].m_tBackRtcpAddr.m_wPort
		,m_cSpeaker.m_atVidDec[2].m_tRtpAddr.m_wPort, m_cSpeaker.m_atVidDec[2].m_tBackRtcpAddr.m_wPort
		,m_cSpeaker.m_tSingleVidDec.m_tRtpAddr.m_wPort, m_cSpeaker.m_tSingleVidDec.m_tBackRtcpAddr.m_wPort);

	msgprintnotime("  vir speaker aud: 1(%d,%d), 2(%d,%d), 3(%d,%d), mix(%d,%d)\n"
		,m_cSpeaker.m_atAudDec[0].m_tRtpAddr.m_wPort, m_cSpeaker.m_atAudDec[0].m_tBackRtcpAddr.m_wPort
		,m_cSpeaker.m_atAudDec[1].m_tRtpAddr.m_wPort, m_cSpeaker.m_atAudDec[1].m_tBackRtcpAddr.m_wPort
		,m_cSpeaker.m_atAudDec[2].m_tRtpAddr.m_wPort, m_cSpeaker.m_atAudDec[2].m_tBackRtcpAddr.m_wPort
		,m_cSpeaker.m_tAudMixDec.m_tRtpAddr.m_wPort, m_cSpeaker.m_tAudMixDec.m_tBackRtcpAddr.m_wPort);

	//发言人NetBuf地址
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		msgprintnotime("  vir speaker nb [%d]: RcvRtp(%d), SndRtp(%d), RcvRtcp(%d), RmtRtcp(%d)\n", wIndex
			,m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtpAddr.m_wPort, m_cSpeaker.m_atVidBuf[wIndex].m_wSndAddr.m_wPort
			,m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtcpAddr.m_wPort, m_cSpeaker.m_atVidBuf[wIndex].m_tRmtRtcpAddr.m_wPort);
	}

	msgprintnotime("  vir speaker nb single: RcvRtp(%d), SndRtp(%d), RcvRtcp(%d), RmtRtcp(%d)\n"
		,m_cSpeaker.m_tSingleVidBuf.m_tRcvRtpAddr.m_wPort, m_cSpeaker.m_tSingleVidBuf.m_wSndAddr.m_wPort
		,m_cSpeaker.m_tSingleVidBuf.m_tRcvRtcpAddr.m_wPort, m_cSpeaker.m_tSingleVidBuf.m_tRmtRtcpAddr.m_wPort);

	msgprintnotime("  vir chair vid: 1(%d), 2(%d), 3(%d)\n"
		,m_cChair.m_atVidDec[0].m_wPort
		,m_cChair.m_atVidDec[1].m_wPort
		,m_cChair.m_atVidDec[2].m_wPort);
	
	msgprintnotime("  vir chair aud: 1(%d), 2(%d), 3(%d)\n"
		,m_cChair.m_atAudDec[0].m_wPort
		,m_cChair.m_atAudDec[1].m_wPort
		,m_cChair.m_atAudDec[2].m_wPort);

	m_pcDual->ShowPortRes();
}

static void PrintCallNode(TCallNode* ptNode, TRmtChan* ptAddr, u16 lv)
{
	s8 szSpaceBuf[255] = "";
	u16 wIndex;
	for (wIndex = 0; wIndex < lv; ++wIndex)
	{
		sprintf(szSpaceBuf+wIndex, "%s", "  ");
	}

	msgprintnotime("   %sEpID:%d, LowID:%d, Called Type:%d, Alias:%s, E164:%s, IP:"TPIPFORMAT", bIPAlias:%d, Name:%s\n"
		,szSpaceBuf , ptNode->m_wEpID, ptNode->m_wLowChildEpID
		, ptNode->m_tCalledAddr.m_byCallType, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias,ptNode->m_tCalledAddr.m_tE164.m_abyAlias
		,Tpu32ToIP(ptNode->m_tCalledAddr.m_dwIP),ptNode->m_tCalledAddr.m_bAliasIP,ptNode->m_tConfName.m_abyAlias);

	msgprintnotime("    %scall:%s, chan:%d, chs:%d, %s, %s, %s, ver:%u, vendor:%s.\n", szSpaceBuf , 
		UmsNodeConfType(ptNode->m_emCallState), ptNode->IsChanOn(), ptNode->GetSpeaker(), UmsNodeType(ptNode->m_emEpType), 
		ptNode->m_abyPrdutID, UmsCallProto(ptNode->m_emCallProtocol), ptNode->m_byVer, UmsPrintVendor(ptNode->m_emVendorID));

	msgprintnotime("    %sMix:%d, SelNum:%d, bMute:%d, bQuiet:%d.\n", szSpaceBuf , 
		ptNode->m_wMixIndex, ptNode->GetSelNum(), ptNode->m_bMute, ptNode->m_bQuiet);
	
	if ( VALID_LOCAL_EPID(ptNode->m_wEpID) || ptNode->m_wEpID == CALLER_EP_INDEX )
	{//本级会场
		TCapNode* ptCapNode = (TCapNode*)ptNode;

		msgprintnotime("	PaHandle:%d, Ds:%d, Adapter:"TPIPFORMAT", Obj:(%s,%s,%s), LastObj:%s\n", 
			ptCapNode->m_dwStackHandle, ptCapNode->m_tMediaEqp.m_wEqpIndex
			, Tpu32ToIP(ptCapNode->m_tAdapterEqp.m_dwEqpIp), GetNodeObj(ptCapNode->m_aemObj[0])
			, GetNodeObj(ptCapNode->m_aemObj[1]), GetNodeObj(ptCapNode->m_aemObj[2]), GetNodeObj(ptCapNode->m_emLastObj));
		
		msgprintnotime("	McuChan:%d, McuAppChan:%d, McuReqId:%d, bAdjustChanOn:%d, bKedaManu:%d, KedaManuCheckNum:%d.\n", 
			ptCapNode->m_hMcuChan, ptCapNode->m_hMcuAppChan, ptCapNode->m_nMcuReqID,
			ptCapNode->m_bAdjustChanOn, ptCapNode->m_bIsKedaManu, ptCapNode->m_bKedaManuCheckNum);
	}
	
	if (ptNode->IsCallOn())
	{
		msgprintnotime("	bAllFecc:%d, byCurVidNo:%d, byAliasCount:%d.\n", 
			ptNode->m_bAllowFecc, ptNode->m_byCurVidNo, ptNode->m_tVidSourceInfo.m_byNum);

		if (ptNode->m_bAllowFecc)
		{
			u16 wAlisaNum = localmin(ptNode->m_tVidSourceInfo.m_byNum, UMS_MAX_VID_SOURCE_NUM);
			TVidAliasInfo* ptAliasInfo = NULL;
			for (u16 wIndex = 0; wIndex < wAlisaNum; ++wIndex)
			{
				
				ptAliasInfo = &ptNode->m_tVidSourceInfo.m_atVidInfo[wIndex];
				msgprintnotime("	AliasIndex:%d , Alias:%s ", ptAliasInfo->m_byIndex, ptAliasInfo->m_abyAlias);
				if ((wIndex+1)%3 == 0 || (wIndex+1) == wAlisaNum)
				{
					msgprintnotime("\n");
				}
				
			}
		}
		

		msgprintnotime("       %saud snd:%d(%-10s,sload:%d,dload:%d), vid snd:%d ", szSpaceBuf, ptNode->m_wAudSndNum
				, UmsAudFormatPrint(ptNode->m_tAudSndFormat.m_tFormat.m_emFormat)
				, ptNode->m_tAudSndFormat.m_wStaticPayload, ptNode->m_tAudSndFormat.m_wDynamicPayload, ptNode->m_wVidSndNum);
		if (ptNode->m_wVidSndNum > 0)
		{
			msgprintnotime("(%s,%s,%s,%d,%d  sload:%d,dload:%d)\n", UmsVidFormatPrint(ptNode->m_tVidSndFormat.m_tFormat.m_emFormat),
							UmsVidProfilePrint(ptNode->m_tVidSndFormat.m_tFormat.m_emQualityLvl), UmsVidResPrint(ptNode->m_tVidSndFormat.m_tFormat.m_emRes),
							ptNode->m_tVidSndFormat.m_tFormat.m_wFrameRate, ptNode->m_tVidSndFormat.m_tFormat.m_wBitrate,
							ptNode->m_tVidSndFormat.m_wStaticPayload, ptNode->m_tVidSndFormat.m_wDynamicPayload);
		}
		else
		{
			msgprintnotime("\n");
		}

		msgprintnotime("       %saud rcv:%d(%-10s,sload:%d,dload:%d), vid rcv:%d ", szSpaceBuf, ptNode->m_wAudRcvNum
				, UmsAudFormatPrint(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat)
				, ptNode->m_tAudRcvFormat.m_wStaticPayload, ptNode->m_tAudRcvFormat.m_wDynamicPayload, ptNode->m_wVidRcvNum);
		if (ptNode->m_wVidRcvNum > 0)
		{
			msgprintnotime("(%s,%s,%s,%d,%d  sload:%d,dload:%d)\n", UmsVidFormatPrint(ptNode->m_tVidRcvFormat.m_tFormat.m_emFormat),
							UmsVidProfilePrint(ptNode->m_tVidRcvFormat.m_tFormat.m_emQualityLvl), UmsVidResPrint(ptNode->m_tVidRcvFormat.m_tFormat.m_emRes),
							ptNode->m_tVidRcvFormat.m_tFormat.m_wFrameRate, ptNode->m_tVidRcvFormat.m_tFormat.m_wBitrate, 
							ptNode->m_tVidRcvFormat.m_wStaticPayload, ptNode->m_tVidRcvFormat.m_wDynamicPayload);
		}
		else
		{
			msgprintnotime("\n");
		}

		if (VALID_CAPSET_EPID(ptNode->m_wEpID))
		{
#define THIS_CALC_TEMP wAddmid = (wIndex+1)/2 ; if ((wIndex+1) %2 == 0) wAddmid *= -1;wScreeID = wMidIndex + wAddmid;	
			u16 wMidIndex = MIDSCREENINDEX;	
			s32 wAddmid;
			s16 wScreeID;
			TChanPara* ptAudPara;
			TChanPara* ptAudRcvPara;

			TVidChanPara* ptVidPara;
			TVidChanPara* ptVidRcvPara;
			for (wIndex = 0; (wIndex < ptNode->m_wVidSndNum || wIndex < ptNode->m_wVidRcvNum); ++wIndex)
			{
				THIS_CALC_TEMP;
				if (ptNode->m_emEpType != emTPEndpointTypeCNS && ptNode->m_emEpType != emTPEndpointTypeUMS)
				{
					wScreeID = MIDSCREENINDEX;	
				}
				ptVidPara = &ptAddr->m_atVidEnc[wScreeID];
				ptVidRcvPara = &ptAddr->m_atVidDec[wScreeID];
				msgprintnotime("       %svid ChanIndex:%d, snd(PAHand:%d, Flow:%d), rcv(PAHand:%d) "
					, szSpaceBuf, ptVidPara->m_wIndex, ptVidPara->m_tPAHandle, ptVidPara->m_tFlowCtrl.m_dwState, ptVidRcvPara->m_tPAHandle);
				
				if ( ptNode->IsThreeVidRcv() )
				{//三屏接收 则 尝试打印小码流
					ptVidPara = &ptAddr->m_atSmallVidEnc[wScreeID];
					ptVidRcvPara = &ptAddr->m_atSmallVidDec[wScreeID];
					msgprintnotime(" small snd(Open:%d) rcv(Open:%d)\n", ptVidPara->IsOpen(), ptVidRcvPara->IsOpen());
				}
				else
				{
					msgprintnotime(" \n");
				}
			}
			for (wIndex = 0; (wIndex < ptNode->m_wAudSndNum || wIndex < ptNode->m_wAudRcvNum); ++wIndex)
			{ 
				THIS_CALC_TEMP;
				if (ptNode->m_emEpType != emTPEndpointTypeCNS && ptNode->m_emEpType != emTPEndpointTypeUMS)
				{
					wScreeID = MIDSCREENINDEX;	
				} 
				ptAudPara = &ptAddr->m_atAudEnc[wScreeID];
				ptAudRcvPara = &ptAddr->m_atAudDec[wScreeID];
				msgprintnotime("       %saud ChanIndex:%d, snd(PAHand:%d), rcv(PAHand:%d)\n", szSpaceBuf, ptAudPara->m_wIndex,  ptAudPara->m_tPAHandle , ptAudRcvPara->m_tPAHandle);
			}

			ptAudPara = &ptAddr->m_tAudMixEnc;
			ptAudRcvPara = &ptAddr->m_tAudMixDec;
			msgprintnotime("       %sAudMix snd(PAHand:%d, Open:%d), rcv(PAHand:%d, Open:%d)\n"
				, szSpaceBuf, ptAudPara->m_tPAHandle, ptAudPara->m_emChanState, ptAudRcvPara->m_tPAHandle, ptAudRcvPara->m_emChanState);

			ptVidPara = &ptAddr->m_tDualVidEnc;
			ptVidRcvPara = &ptAddr->m_tDualVidDec;

			msgprintnotime("       %sDual vsnd(PAHand:%d, Open:%d ", szSpaceBuf, ptVidPara->m_tPAHandle, ptVidPara->m_emChanState);
			if (ptVidPara->IsOpen())
			{
				msgprintnotime("snd(%s,%s,%s,%d,%d  sload:%d,dload:%d) )\n", UmsVidFormatPrint(ptNode->m_tDualVidSndFormat.m_tFormat.m_emFormat), UmsVidProfilePrint(ptNode->m_tDualVidSndFormat.m_tFormat.m_emQualityLvl)
							, UmsVidResPrint(ptNode->m_tDualVidSndFormat.m_tFormat.m_emRes), ptNode->m_tDualVidSndFormat.m_tFormat.m_wFrameRate,
							ptNode->m_tDualVidSndFormat.m_tFormat.m_wBitrate, 
							ptNode->m_tDualVidSndFormat.m_wStaticPayload,
							ptNode->m_tDualVidSndFormat.m_wDynamicPayload);

			}
			else
			{
				msgprintnotime(" )\n");
			}
			msgprintnotime("       %sDual vrcv(PAHand:%d, Open:%d ", szSpaceBuf, ptVidRcvPara->m_tPAHandle, ptVidRcvPara->m_emChanState);
			if (ptVidRcvPara->IsOpen())
			{
				msgprintnotime("rcv(%s,%s,%s,%d,%d  sload:%d,dload:%d) )\n", UmsVidFormatPrint(ptNode->m_tDualVidRcvFormat.m_tFormat.m_emFormat), UmsVidProfilePrint(ptNode->m_tDualVidRcvFormat.m_tFormat.m_emQualityLvl)
								, UmsVidResPrint(ptNode->m_tDualVidRcvFormat.m_tFormat.m_emRes), ptNode->m_tDualVidRcvFormat.m_tFormat.m_wFrameRate,
								ptNode->m_tDualVidRcvFormat.m_tFormat.m_wBitrate,
								ptNode->m_tDualVidRcvFormat.m_wStaticPayload,
								ptNode->m_tDualVidRcvFormat.m_wDynamicPayload);
			}
			else
			{
				msgprintnotime(" )\n");
			}
			
			ptAudPara = &ptAddr->m_tDualAudEnc;
			ptAudRcvPara = &ptAddr->m_tDualAudDec;
			msgprintnotime("       %sDual asnd(PAHand:%d, Open:%d), aRcv(PAHand:%d, Open:%d)\n"
				, szSpaceBuf, ptAudPara->m_tPAHandle, ptAudPara->m_emChanState, ptAudRcvPara->m_tPAHandle, ptAudRcvPara->m_emChanState);
		}
		else
		{
			msgprintnotime("       SmallOpenEnc:%d, SmallOpenDec:%d\n", ptNode->m_bSmallOpenEnc, ptNode->m_bSmallOpenDec);
		}
	}
}

void CUmsConfInst::ShowCallInfo()
{
	if (CurState() == inst_idle)
	{
		msgprint(" this Conf is idle!  confID:%d\n", GetInsID());
		return;
	}
	
	struct tm t;
	tplocaltime(t, m_tConfBaseInfo.m_tStartTime);
	
	msgprintnotime("ConfID:%d, ConfName:%s, e164:%s, AudFmt:(%s, %s, %s, %s) start:%2.2u-%2.2u %2.2u:%2.2u:%2.2u\n"
		, GetInsID(), m_tConfBaseInfo.m_achConfName, m_tConfBaseInfo.m_achConfE164
		, m_tConfBaseInfo.m_wAudFmtNum >= 1 ? UmsAudFormatPrint(m_tConfBaseInfo.m_atAudFmt[0].m_emFormat) : ""
		, m_tConfBaseInfo.m_wAudFmtNum >= 2 ? UmsAudFormatPrint(m_tConfBaseInfo.m_atAudFmt[1].m_emFormat) : ""
		, m_tConfBaseInfo.m_wAudFmtNum >= 3 ? UmsAudFormatPrint(m_tConfBaseInfo.m_atAudFmt[2].m_emFormat) : ""
		, m_tConfBaseInfo.m_wAudFmtNum >= 4 ? UmsAudFormatPrint(m_tConfBaseInfo.m_atAudFmt[3].m_emFormat) : "", 
		t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);


	TTPEncrypt* ptEncrypt = &GetConfEncryptInfo();
	msgprintnotime("ConfEncryptType:%s, Len:%d, Key:%s\n", TpEnumString(EmTPEncryptType, ptEncrypt->m_emEncryptModel), 
		ptEncrypt->m_byKeyLen, ptEncrypt->m_achEncKey);

	msgprintnotime("DataConf stat:%d, serverIP:"TPIPFORMAT"\n", m_pcDataConf->ConfStatus(), u32ToIP(m_pcDataConf->ServerIP()));
	
	msgprintnotime("Rs time: %d %d %d %d, ConfHpBit:%d, ConfBpBit:%d, ConfDualHpbit:%d, ConfDualBpBit:%d.\n"
		, m_tConfBaseInfo.m_tRsParam.m_wFirstTimeSpan, m_tConfBaseInfo.m_tRsParam.m_wSecondTimeSpan
		, m_tConfBaseInfo.m_tRsParam.m_wThirdTimeSpan, m_tConfBaseInfo.m_tRsParam.m_wRejectTimeSpan
		, m_tConfBaseInfo.m_wConfBitRate, m_tConfBaseInfo.m_wBpConfBitRate, m_tConfBaseInfo.m_wHpDualBitRate
		, m_tConfBaseInfo.m_wBpDualBitRate);

	msgprintnotime("m_bIsAllEpMute:%d, m_bIsAllEpQuiet:%d, m_bEpNodeCheck:%d.\n"
		, m_bIsAllEpMute, m_bIsAllEpQuiet, m_bEpNodeCheck);

	msgprintnotime("ConfDs EqpIndex:%d, EqpNode:%d, EqpIP"TPIPFORMAT"\n", m_tEqpConfDs.m_wEqpIndex
		, m_tEqpConfDs.m_dwEqpNode, Tpu32ToIP(m_tEqpConfDs.m_dwEqpIp));
	
	for(u16 wIndex = 0; wIndex < UMS_CONF_MAX_DS_NUM; ++wIndex)
	{
		msgprintnotime("Ds(%d) EqpIndex:%d, EqpNode:%d, EqpIP"TPIPFORMAT"\n", wIndex, m_atDsEqp[wIndex].m_wEqpIndex
		, m_atDsEqp[wIndex].m_dwEqpNode, Tpu32ToIP(m_atDsEqp[wIndex].m_dwEqpIp));
	}
	
	if (m_pcNodeMgr->GetCaller()->m_bUsed)
	{
		msgprint("The conf is lower!  ConfName:%s, ChairName:%s, SpeakerName:%s\n", m_tSuperInfo.m_tConf.m_abyAlias, 
			m_tSuperInfo.m_tChair.m_abyAlias, m_tSuperInfo.m_tSpeak.m_abyAlias);

		TCapNode* ptCap = m_pcNodeMgr->GetCaller();				
		PrintCallNode(ptCap, &ptCap->m_tRmtChan, 0);		
	}

	msgprintnotime("ep list: \n");
	
	m_pcNodeMgr->ForEachTreeNode(PrintCallNode, m_pcNodeMgr->FirstNode(), 0);

	msgprintnotime("Defchair:%d, Speaker:%d, chair:%d, oldSpeaker:%d\n", m_tConfBaseInfo.m_wDefaultChairMan, curSpeakerID(), chairID(), oldSpeakerID());
}


void CUmsConfInst::ShowCallDs()
{
	u16 dsNum = 0;
	TCapNode* ptNode;
	TUmsDsData atDsData[MAX_CHANNEL_DS_NUM];

	CDsListPtr ptHead;

	ptHead = m_cSpeaker.m_tInnerVirSpeaker.GetHead();
	msgprintnotime(" To Speaker Netbuf. dsNum:%d\n", m_cSpeaker.m_tInnerVirSpeaker.GetElementNum());
	PrintDsList(ptHead)
//	msgprintnotime(" \n");

	ptHead = m_pcBas->GetSpeakerBas()->m_tDsList.GetHead();
	msgprintnotime(" To Speaker Bas. dsNum:%d\n", m_pcBas->GetSpeakerBas()->m_tDsList.GetElementNum());
	PrintDsList(ptHead)
//	msgprintnotime(" \n");
	
	ptHead = m_cSpeaker.m_tToVirSpeakerDs.GetHead();
	msgprintnotime(" Speaker to vir speaker. Speaker EpId:%d, dsNum:%d\n", curSpeakerID(), m_cSpeaker.m_tToVirSpeakerDs.GetElementNum());
	PrintDsList(ptHead)
	msgprintnotime("\n");
		
	m_pcDual->ShowDs();

	for (u16 wNodeIndex = 0; wNodeIndex <= CALLER_EP_INDEX; ++wNodeIndex)
	{
		ptNode = m_pcNodeMgr->GetCapsetNode(wNodeIndex);
		if ( NULL == ptNode || !ptNode->m_bUsed)
		{
			continue;
		}
	
		ptHead = ptNode->m_tDsList.GetHead();
		msgprintnotime(" To Node epID:%d, name:%s, dsNum:%d, Obj:(%s,%s,%s)\n"
			, ptNode->m_wEpID, ptNode->m_tConfName.m_abyAlias, ptNode->m_tDsList.GetElementNum(),
			GetNodeObj(ptNode->m_aemObj[0]), GetNodeObj(ptNode->m_aemObj[1]), GetNodeObj(ptNode->m_aemObj[2]));

		PrintDsList(ptHead)
	}
}

void CUmsConfInst::ShowCallPoll()
{
	m_pcPollMgr->Show();
}

void CUmsConfInst::ShowDiscuss()
{
	if (CurState() != inst_idle)
	{
		m_pcUmsDiscuss->Show();
	}
}

void CUmsConfInst::ShowEapu()
{
	m_pcEapu->Show();
}

void CUmsConfInst::ShowAudDual()
{
	m_pcDual->Show();
}

void CUmsConfInst::ShowTv()
{
	m_pcTvWallMgr->Show();
}

void CUmsConfInst::ShowVmp()
{
	m_pcVmp->Show();
}

void CUmsConfInst::ShowBas()
{
	m_pcBas->Show();
}

void PrintEpDs(TTPTransAddr atTransAddr[], u16 wDsNum)
{
	if ( wDsNum == 0 )
	{
		return ;
	}

	for ( u16 wIndex = wDsNum - 1; wIndex >= 0; wIndex -- )
	{
		for ( u16 wTabNum = 0; wTabNum < wDsNum - wIndex; wTabNum ++ )
		{
			msgprintnotime("  ");
		}

		if ( wIndex != wDsNum -1 )
		{
			msgprintnotime("  ->");
		}

		msgprintnotime(""ADDRPORT_FORMAT"", ADDRNET(atTransAddr[wIndex]));

		msgprintnotime("\n");

		if ( wIndex == 0 )
		{
			break;
		}
	}
}

void CUmsConfInst::ShowSelView()
{
	m_pcSelView->Show();
}

void CUmsConfInst::ShowResFrm()
{
	msgprintnotime("\n==== ConfID:%d, NodeResFrm ===\n", GetInsID());

	for (TCapNode* ptItor = m_pcNodeMgr->FirstNode();  ptItor != NULL; ptItor = m_pcNodeMgr->NextLoalNode(ptItor))
	{
		if ( !ptItor->IsChanOn() )
		{
			continue;
		}

		if ( ptItor->IsUms() )
		{
			continue;
		}

		ForEachChanList(ptItor->m_wVidSndNum,
			msgprintnotime(" EpID:%d, ScreenIndx:%d\n", ptItor->m_wEpID, ewIndex);\
			ptItor->m_atResFrm[ewIndex].PrintInfo();
			);
	}
}


void CUmsConfInst::ShowRollCall()
{
	if (CurState() != inst_idle)
	{
		m_pcRollCallMgr->Show();
	}
}

void CUmsConfInst::ShowAudMix()
{
	if (CurState() != inst_idle)
	{
		m_pcAudMix->Show();
	}
}

void CUmsConfInst::ShowGetStream()
{
	if (CurState() != inst_idle)
	{
		m_tGetConfVidAudMgr->Show();
	}
}

void CUmsConfInst::ShowMcuMgr()
{
	if (CurState() != inst_idle)
	{
		m_pcMcuMgr->Show();
	}
}

extern u16 g_wAudMixStartPort;
extern u16 g_wAudMixEndPort;


void CUmsConfInst::ShowAllPort()
{
	u16 wIndex;
	TTPTransAddr* ptRtp;
	TTPTransAddr* ptRtcp;
	TTPTransAddr* ptRmtRtcp;
	TTPTransAddr* ptSnd;

	TTPTransAddr* ptBackRtcp;

	struct tm t;
	tplocaltime(t, m_tConfBaseInfo.m_tStartTime);
	
	msgprint("ConfID:%d, e164:%s starttime:%2.2u-%2.2u %2.2u:%2.2u:%2.2u\n", GetInsID(), m_tConfBaseInfo.m_achConfName
		, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	msgprintnotime(" vir speaker netbuf:\n");
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ptRtp = &m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtpAddr;
		ptRtcp = &m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtcpAddr;
		ptSnd = &m_cSpeaker.m_atVidBuf[wIndex].m_wSndAddr;
		ptRmtRtcp = &m_cSpeaker.m_atVidBuf[wIndex].m_tRmtRtcpAddr;
		msgprintnotime("   vid %d, rcv  rtp:%d, rcv rtcp:%d, snd addr:%d, rmt rtcp:%d\n"
			, wIndex+1, ptRtp->m_wPort, ptRtcp->m_wPort, ptSnd->m_wPort, ptRmtRtcp->m_wPort);
	}
	msgprintnotime(" \n");

	msgprintnotime(" vir speaker addr:\n");
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ptRtp = &m_cSpeaker.m_atVidDec[wIndex].m_tRtpAddr;
		ptBackRtcp = &m_cSpeaker.m_atVidDec[wIndex].m_tBackRtcpAddr;
		ptSnd = &m_cSpeaker.m_atAudDec[wIndex].m_tRtpAddr;
		ptRmtRtcp = &m_cSpeaker.m_atAudDec[wIndex].m_tBackRtcpAddr;

		msgprintnotime("   rcv %d, Vid(%d-%d), Aud(%d-%d)\n", wIndex+1
			, ptRtp->m_wPort, ptBackRtcp->m_wPort, ptSnd->m_wPort, ptRmtRtcp->m_wPort);
	}

	ptRtp = &m_cSpeaker.m_tAudMixDec.m_tRtpAddr;
	ptBackRtcp = &m_cSpeaker.m_tAudMixDec.m_tBackRtcpAddr;
	msgprintnotime("   Mix (%d-%d), Vmp (%d-%d)\n", ptRtp->m_wPort,  ptBackRtcp->m_wPort, 
		m_cSpeaker.m_tSingleVidDec.m_tRtpAddr.m_wPort, m_cSpeaker.m_tSingleVidDec.m_tBackRtcpAddr.m_wPort);

	msgprintnotime(" vir chair addr:\n");
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{		
		msgprintnotime("   rcv %d, Vid(%d), Aud(%d)\n", wIndex+1
			, m_cChair.m_atVidDec[wIndex].m_wPort, m_cChair.m_atAudDec[wIndex].m_wPort);
	}

	msgprintnotime(" \n");
	
	m_pcPollMgr->Show();
	m_pcEapu->Show();
	m_pcDual->Show();
	m_pcVmp->Show();
	m_pcBas->Show();
	ShowSelView();
}

void CUmsConfInst::ShowCallPort()
{
	if (CurState() == inst_idle)
	{
		msgprint(" this Conf is idle!  confID:%d\n", GetInsID());
		return;
	}	

	u16 wIndex;
	TTPTransAddr* ptRtp;
	TTPTransAddr* ptRtcp;
	TTPTransAddr* ptRmtRtcp;
	TTPTransAddr* ptSnd;

	TTPTransAddr* ptBackRtcp;

	struct tm t;
	tplocaltime(t, m_tConfBaseInfo.m_tStartTime);
	
	msgprint("ConfID:%d, e164:%s starttime:%2.2u-%2.2u %2.2u:%2.2u:%2.2u\n"
		, GetInsID(), m_tConfBaseInfo.m_achConfName
		, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	msgprintnotime(" vir speaker netbuf:\n");
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ptRtp = &m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtpAddr;
		ptRtcp = &m_cSpeaker.m_atVidBuf[wIndex].m_tRcvRtcpAddr;
 		ptSnd = &m_cSpeaker.m_atVidBuf[wIndex].m_wSndAddr;
		ptRmtRtcp = &m_cSpeaker.m_atVidBuf[wIndex].m_tRmtRtcpAddr;

		msgprintnotime("   vid %d, rcv  rtp:%d, rcv rtcp:%d, snd addr:%d, rmt rtcp:%d\n"
			, wIndex+1, ptRtp->m_wPort, ptRtcp->m_wPort, ptSnd->m_wPort, ptRmtRtcp->m_wPort);
	}

	ptRtp = &m_cSpeaker.m_tSingleVidBuf.m_tRcvRtpAddr;
	ptRtcp = &m_cSpeaker.m_tSingleVidBuf.m_tRcvRtcpAddr;
	ptSnd = &m_cSpeaker.m_tSingleVidBuf.m_wSndAddr;
	ptRmtRtcp = &m_cSpeaker.m_tSingleVidBuf.m_tRmtRtcpAddr;
	msgprintnotime("   (Single) rcv  rtp:%d, rcv rtcp:%d, snd addr:%d, rmt rtcp:%d\n"
			, ptRtp->m_wPort, ptRtcp->m_wPort, ptSnd->m_wPort, ptRmtRtcp->m_wPort);

	msgprintnotime(" \n");

	msgprintnotime(" vir speaker addr:\n");
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ptRtp = &m_cSpeaker.m_atVidDec[wIndex].m_tRtpAddr;
		ptBackRtcp = &m_cSpeaker.m_atVidDec[wIndex].m_tBackRtcpAddr;
		ptSnd = &m_cSpeaker.m_atAudDec[wIndex].m_tRtpAddr;
		ptRmtRtcp = &m_cSpeaker.m_atAudDec[wIndex].m_tBackRtcpAddr;

		msgprintnotime("   rcv %d, Vid(%d-%d), Aud(%d-%d)\n", wIndex+1
			, ptRtp->m_wPort, ptBackRtcp->m_wPort, ptSnd->m_wPort, ptRmtRtcp->m_wPort);
	}

	ptRtp = &m_cSpeaker.m_tAudMixDec.m_tRtpAddr;
	ptBackRtcp = &m_cSpeaker.m_tAudMixDec.m_tBackRtcpAddr;
	msgprintnotime("   Mix (%d-%d), Vmp (%d-%d)\n", ptRtp->m_wPort,  ptBackRtcp->m_wPort, 
		m_cSpeaker.m_tSingleVidDec.m_tRtpAddr.m_wPort, m_cSpeaker.m_tSingleVidDec.m_tBackRtcpAddr.m_wPort);
	
	msgprintnotime(" vir chair addr:\n");
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{		
		msgprintnotime("   rcv %d, Vid(%d), Aud(%d)\n", wIndex+1
			, m_cChair.m_atVidDec[wIndex].m_wPort, m_cChair.m_atAudDec[wIndex].m_wPort);
	}

	msgprintnotime(" \n");
	
	TCapNode* ptNode;
	for (u16 wNodeIndex = 0; wNodeIndex <= CALLER_EP_INDEX; ++wNodeIndex)
	{
		ptNode = m_pcNodeMgr->GetCapsetNode(wNodeIndex);

		if ( NULL == ptNode )
		{
			continue;
		}

		if(!ptNode->IsCallOn())
		{
			continue;	
		}		

		ptNode = m_pcNodeMgr->GetCapsetNode(ptNode->m_wEpID);
		msgprintnotime(" \nep addr. epID:%d\n", ptNode->m_wEpID);

		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (ptNode->m_aptChanAddr[wIndex] == NULL)
			{
				continue;
			}
			ptRtp = &ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtpAddr;
			ptRtcp = &ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForRcv;
			ptBackRtcp = &ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForSnd;
			msgprintnotime("   local vid:%d, rtp:"ADDRPORT_FORMAT" ToNode:"ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
				, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptRtcp)), ADDRNET((*ptBackRtcp)));
			
			if ( ptNode->m_aptSmallChanAddr[wIndex] == NULL )
			{
				continue;
			}

			ptRtp = &ptNode->m_aptSmallChanAddr[wIndex]->m_tRtpAddr;
			ptRtcp = &ptNode->m_aptSmallChanAddr[wIndex]->m_tRtcpForRcv;
			ptBackRtcp = &ptNode->m_aptSmallChanAddr[wIndex]->m_tRtcpForSnd;
			msgprintnotime("   local small vid:%d, rtp:"ADDRPORT_FORMAT" ToNode:"ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
				, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptRtcp)), ADDRNET((*ptBackRtcp)));
		}
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (ptNode->m_aptChanAddr[wIndex] == NULL)
			{
				continue;
			}
			ptRtp = &ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtpAddr;
			ptRtcp = &ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForRcv;
			ptBackRtcp = &ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForSnd;
			msgprintnotime("   local aud:%d, rtp:"ADDRPORT_FORMAT" ToNode:"ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
				, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptRtcp)), ADDRNET((*ptBackRtcp)));
		}

		if (ptNode->m_ptMixAddr != NULL)
		{
			ptRtp = &ptNode->m_ptMixAddr->m_tRtpAddr;
			ptRtcp = &ptNode->m_ptMixAddr->m_tRtcpForRcv;
			ptBackRtcp = &ptNode->m_ptMixAddr->m_tRtcpForSnd;
			msgprintnotime("   local aud mix, rtp:"ADDRPORT_FORMAT" ToNode: "ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
				, ADDRNET((*ptRtp)), ADDRNET((*ptRtcp)), ADDRNET((*ptBackRtcp)));

		}
		
		ptRtp = &ptNode->m_ptDualAddr->m_tVid.m_tRtpAddr;
		ptRtcp = &ptNode->m_ptDualAddr->m_tVid.m_tRtcpForRcv;
		ptBackRtcp = &ptNode->m_ptDualAddr->m_tVid.m_tRtcpForSnd;
		msgprintnotime("   local dual vid, rtp:"ADDRPORT_FORMAT" ToNode:"ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
				, ADDRNET((*ptRtp)), ADDRNET((*ptRtcp)), ADDRNET((*ptBackRtcp)));

		ptRtp = &ptNode->m_ptDualAddr->m_tAud.m_tRtpAddr;
		ptRtcp = &ptNode->m_ptDualAddr->m_tAud.m_tRtcpForRcv;
		ptBackRtcp = &ptNode->m_ptDualAddr->m_tAud.m_tRtcpForSnd;
		msgprintnotime("   local dual aud, rtp:"ADDRPORT_FORMAT" ToNode:"ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
				, ADDRNET((*ptRtp)), ADDRNET((*ptRtcp)), ADDRNET((*ptBackRtcp)));
		
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{	
			if (ptNode->m_tRmtChan.m_atVidEnc[wIndex].IsOpen())
			{
				ptRtp = &ptNode->m_tRmtChan.m_atVidEnc[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcp = &ptNode->m_tRmtChan.m_atVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcp = &ptNode->m_tRmtChan.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				msgprintnotime("   vid snd %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
					, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));

				ptRtp = &ptNode->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcp = &ptNode->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcp = &ptNode->m_tRmtChan.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				msgprintnotime("    small vid snd %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
					, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
			}
		}
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (ptNode->m_tRmtChan.m_atVidDec[wIndex].IsOpen())
			{
				ptRtp = &ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcp = &ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcp = &ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				msgprintnotime("   vid rcv %d, rtp:"ADDRPORT_FORMAT" rtcp:"ADDRPORT_FORMAT"\n"
					, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));

				ptRtp = &ptNode->m_tRmtChan.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcp = &ptNode->m_tRmtChan.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcp = &ptNode->m_tRmtChan.m_atSmallVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				msgprintnotime("    small vid rcv %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
					, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
			}
		}
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (ptNode->m_tRmtChan.m_atAudEnc[wIndex].IsOpen())
			{
				ptRtp = &ptNode->m_tRmtChan.m_atAudEnc[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcp = &ptNode->m_tRmtChan.m_atAudEnc[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcp = &ptNode->m_tRmtChan.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				msgprintnotime("   aud snd %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
					, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
			}
		}
		
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (ptNode->m_tRmtChan.m_atAudDec[wIndex].IsOpen())
			{
				ptRtp = &ptNode->m_tRmtChan.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				ptRtcp = &ptNode->m_tRmtChan.m_atAudDec[wIndex].m_tChanAddr.m_tRtcpAddr;
				ptBackRtcp = &ptNode->m_tRmtChan.m_atAudDec[wIndex].m_tChanAddr.m_tBackRtcpAddr;
				msgprintnotime("   aud rcv %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
					, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
			}
		}

		if (ptNode->m_tRmtChan.m_tAudMixDec.IsOpen())
		{
			ptRtp = &ptNode->m_tRmtChan.m_tAudMixDec.m_tChanAddr.m_tRtpAddr;
			ptRtcp = &ptNode->m_tRmtChan.m_tAudMixDec.m_tChanAddr.m_tRtcpAddr;
			ptBackRtcp = &ptNode->m_tRmtChan.m_tAudMixDec.m_tChanAddr.m_tBackRtcpAddr;
			msgprintnotime("   aud mix rcv %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
				, 1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
		}

		if (ptNode->m_tRmtChan.m_tAudMixEnc.IsOpen())
		{
			ptRtp = &ptNode->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tRtpAddr;
			ptRtcp = &ptNode->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tRtcpAddr;
			ptBackRtcp = &ptNode->m_tRmtChan.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr;
			msgprintnotime("   aud mix snd %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
				, 1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
		}

		if (ptNode->m_tRmtChan.m_tDualVidEnc.IsOpen())
		{
			ptRtp = &ptNode->m_tRmtChan.m_tDualVidEnc.m_tChanAddr.m_tRtpAddr;
			ptRtcp = &ptNode->m_tRmtChan.m_tDualVidEnc.m_tChanAddr.m_tRtcpAddr;
			ptBackRtcp = &ptNode->m_tRmtChan.m_tDualVidEnc.m_tChanAddr.m_tBackRtcpAddr;
			msgprintnotime("   Dual vid snd, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
				, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
		}

		if (ptNode->m_tRmtChan.m_tDualAudEnc.IsOpen())
		{
			ptRtp = &ptNode->m_tRmtChan.m_tDualAudEnc.m_tChanAddr.m_tRtpAddr;
			ptRtcp = &ptNode->m_tRmtChan.m_tDualAudEnc.m_tChanAddr.m_tRtcpAddr;
			ptBackRtcp = &ptNode->m_tRmtChan.m_tDualAudEnc.m_tChanAddr.m_tBackRtcpAddr;
			msgprintnotime("   Dual aud snd, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
				, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
		}

		if (ptNode->m_tRmtChan.m_tDualVidDec.IsOpen())
		{
			ptRtp = &ptNode->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtpAddr;
			ptRtcp = &ptNode->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tRtcpAddr;
			ptBackRtcp = &ptNode->m_tRmtChan.m_tDualVidDec.m_tChanAddr.m_tBackRtcpAddr;
			msgprintnotime("   Dual vid rcv, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
			, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
		}
		
		if (ptNode->m_tRmtChan.m_tDualAudDec.IsOpen())
		{
			ptRtp = &ptNode->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtpAddr;
			ptRtcp = &ptNode->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tRtcpAddr;
			ptBackRtcp = &ptNode->m_tRmtChan.m_tDualAudDec.m_tChanAddr.m_tBackRtcpAddr;
			msgprintnotime("   Dual aud rcv, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
			, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
		}

		if (ptNode->IsUms())
		{
			if (ptNode->m_ptCasCadeChairAddr == NULL)
			{
				msgprintnotime("    asssign chair chan failed!");
				continue;
			}
			if (Is_Caller_Node(ptNode->m_wEpID))
			{
				msgprintnotime("\n");
				for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
				{
					if (ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].IsOpen())
					{

						ptRtp      = &ptNode->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtpAddr;
						ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtcpForSnd;
						msgprintnotime("   Chair vid  local %d, rtp: "ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
							, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
						
						ptRtp      = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].m_tChanAddr.m_tRtpAddr;
						ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].m_tChanAddr.m_tBackRtcpAddr;
						
						msgprintnotime("   Chair vid  rcv  %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
							           , wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));

					}
				}
                msgprintnotime("\n");

				for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
				{
					if (ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].IsOpen())
					{
						ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].m_tChanAddr.m_tBackRtcpAddr;			
						ptRtp = &ptNode->m_ptCasCadeChairAddr->m_atAud[wIndex].m_tRtpAddr;
						msgprintnotime("   Chair aud %d, Local: "ADDRPORT_FORMAT" rmt: "ADDRPORT_FORMAT"\n"
							, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
					}
				}

				ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr.m_tBackRtcpAddr;			
				ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tMixAud.m_tRtpAddr;
				msgprintnotime("   Chair audMix, Local: "ADDRPORT_FORMAT" rmt: "ADDRPORT_FORMAT"\n"
					, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));

				ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tBackRtcpAddr;			
				ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtpAddr;
				msgprintnotime("   DisSingleVid, Local: "ADDRPORT_FORMAT" rmt: "ADDRPORT_FORMAT"\n"
									, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));

				ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleAud.m_tChanAddr.m_tBackRtcpAddr;			
				ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tDisSingleAud.m_tRtpAddr;
				msgprintnotime("   DisSingleAud, Local: "ADDRPORT_FORMAT" rmt: "ADDRPORT_FORMAT"\n"
									, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
			}
			else
			{
				msgprintnotime("\n");
				for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
				{
					if (ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].IsOpen())
					{
	
	                    ptRtp      = &ptNode->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtpAddr;
						ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_atVid[wIndex].m_tRtcpForSnd;
						msgprintnotime("   Chair vid  local %d, rtp: "ADDRPORT_FORMAT" ToVir: "ADDRPORT_FORMAT"\n"
							           , wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));

						ptRtp      = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].m_tChanAddr.m_tRtpAddr;
						ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atVid[wIndex].m_tChanAddr.m_tBackRtcpAddr;
						
						msgprintnotime("   Chair vid  rcv  %d, rtp: "ADDRPORT_FORMAT" rtcp: "ADDRPORT_FORMAT"\n"
							           , wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));

					}
				}
                msgprintnotime("\n");

				for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
				{
					if (ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].IsOpen())
					{
						ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_atAud[wIndex].m_tChanAddr.m_tRtpAddr;			
						ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_atAud[wIndex].m_tRtcpForSnd;
						msgprintnotime("   Chair aud %d, RmtRtp: "ADDRPORT_FORMAT" Local: "ADDRPORT_FORMAT"\n"
							, wIndex+1, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
					}
				}

				ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tMixAud.m_tChanAddr.m_tRtpAddr;			
				ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tMixAud.m_tRtcpForSnd;
				msgprintnotime("   Chair audMix, RmtRtp: "ADDRPORT_FORMAT" Local: "ADDRPORT_FORMAT"\n"
									, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
// 				ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tSpeakerVmpVid.m_tChanAddr.m_tRtpAddr;			
// 				ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tSpeakerVmpVid.m_tRtcpForSnd;
// 				msgprintnotime("   SpeakerVmpVid, RmtRtp: "ADDRPORT_FORMAT" Local: "ADDRPORT_FORMAT"\n"
// 					, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
				ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleVid.m_tChanAddr.m_tRtpAddr;			
				ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tDisSingleVid.m_tRtcpForSnd;
				msgprintnotime("   DisSingleVid, RmtRtp: "ADDRPORT_FORMAT" Local: "ADDRPORT_FORMAT"\n"
					, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
				ptRtp = &ptNode->m_ptCasCadeChairAddr->m_tRmtInfo.m_tDisSingleAud.m_tChanAddr.m_tRtpAddr;			
				ptBackRtcp = &ptNode->m_ptCasCadeChairAddr->m_tDisSingleAud.m_tRtcpForSnd;
				msgprintnotime("   DisSingleAud, RmtRtp: "ADDRPORT_FORMAT" Local: "ADDRPORT_FORMAT"\n"
					, ADDRNET((*ptRtp)), ADDRNET((*ptBackRtcp)));
			}
		}
	}
	
	m_pcPollMgr->Show();
	m_pcEapu->Show();
	m_pcDual->Show();
	m_pcVmp->Show();
	m_pcBas->Show();
	m_cBw.ShowBW();

}


API void viewobj(u16 wConfID, u16 wChanID, u16 wDstEp)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, wChanID);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_ViewObj_Req);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&wDstEp, sizeof(wDstEp));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

API void unviewobj(u16 wConfID, u16 wChanID)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, wChanID);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_UndoViewObj_Req);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

API void startpoll(u16 wConfID)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_StartPoll_Req);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

API void suspendpoll(u16 wConfID, BOOL32 bSuspend)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_SuspendPoll_Req);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&bSuspend, sizeof(BOOL32));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

API void stoppoll(u16 wConfID)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_StopPoll_Req);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

API void startvmp(u16 wConfID, s8* pszDstIP, u16 wDstPort, u32 dwDstEpType)
{//1 为CNS 4为终端 7为G400  0为所有
	u32_ip dwDstIp = inet_addr(pszDstIP);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_StartVmpToT300_Cmd);
	cMsg.SetBody(&dwDstIp, sizeof(dwDstIp));
	cMsg.CatBody(&wDstPort, sizeof(wDstPort));
	cMsg.CatBody(&dwDstEpType, sizeof(dwDstEpType));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID));
}

API u16 startdual(u16 wConfID, u16 wChairEpID, u16 wDuaDstEpID)
{
	TConfEpID tConfID;
	tConfID.m_wConfID = wConfID;
	tConfID.m_wEpID = wDuaDstEpID;
	
	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfID, wChairEpID);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsConfStartDual_Cmd);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tConfID, sizeof(tConfID));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
	
	return 0;
}

API u16 stopdual(u16 wConfID, u16 wChairEpID, u16 wDuaDstEpID)
{
	TConfEpID tConfID;
	tConfID.m_wConfID = wConfID;
	tConfID.m_wEpID = wDuaDstEpID;
	
	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfID, wChairEpID);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsConfStopDual_Cmd);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tConfID, sizeof(tConfID));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
	
	return 0;
}

API void callcon(u16 wConfID, u16 wEpId, u32 type, s8* epname)
{
	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfID, wEpId);
	
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}
	
	TUmsCallInfo tCallInfo;
	tCallInfo.m_emSrcEpType = (EmTPEndpointType)type;
	tCallInfo.m_byVer = tCallInfo.m_emSrcEpType == emTPEndpointTypeCNS?CNS_B4:0;
	tCallInfo.m_tEncrypt = pInst->GetConfEncryptInfo();
	tCallInfo.m_emTpProtocol = tCallInfo.m_emSrcEpType == emTPEndpointTypeCNS?emTpSIP:emTpH323;
	if (NULL != epname)
	{
		tCallInfo.m_tDestAddr.m_tAlias.SetAlias(epname);
	}
	
	NotifyMsgToCall(evtp_Conf_UmsCallConnect, tHandle, &tCallInfo, sizeof(tCallInfo));
}

API void calldiscon(u16 wConfid, u16 wEpId, u32 dwReson)
{
	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfid, wEpId);
	
	EmCnsCallReason emAppReason = (EmCnsCallReason)dwReson;
	NotifyMsgToCall(evtp_Conf_UmsCallDisConnect, tHandle, &emAppReason, sizeof(emAppReason));
	
}

API void addview(u16 wChanIndex, u16 wScreenNum, s8* alias)
{
	u8 abyBuf[sizeof(TAddTvMonitor) + sizeof(BOOL32)] = {0};
	TAddTvMonitor tReq;
	tReq.m_tReq.m_wIndex = wChanIndex;	
	tReq.m_tVidAddr.m_tRtpAddr.SetAddr(0, 10000 + wChanIndex*wChanIndex);
	tReq.m_tAudAddr.m_tRtpAddr.SetAddr(0, 10000 + wChanIndex*wChanIndex+2);

	tReq.m_tReq.m_wScreenNum = wScreenNum;
	
	memcpy(abyBuf, &tReq, sizeof(TAddTvMonitor));
	BOOL32 bHduOnline = TRUE;
	memcpy(abyBuf + sizeof(TAddTvMonitor), &bHduOnline, sizeof(BOOL32));
	
	NotifyCall(ev_AddTvMonitor_req, abyBuf, sizeof(abyBuf));
}

API void delview(u16 wChanIndex)
{
	TTPHduPlayReq tReq;
	tReq.m_wIndex = wChanIndex;	
	NotifyCall(ev_DelTvMonitor_req, &tReq, sizeof(tReq));
}

API void chancon(u16 wConfid, u16 wEpId,  u16 screen, s8* szIp)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfid));

	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfid, wEpId);
		
	TUmsNodeCapset tNodeCap;
	tNodeCap.m_wVidEncNum = screen;
	tNodeCap.m_wVidDecNum = screen;
	
	tNodeCap.m_wAudEncNum = 1;
	tNodeCap.m_wAudDecNum = 1;

	tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = emTPVHD1080p1920x1080;
	tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
	tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = 60;
	
	tNodeCap.m_tVidSndCap.m_tHp.m_emRes = emTPVHD1080p1920x1080;
	tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
	tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate = 60;

	u32 dwDstIP = inet_addr(szIp);
	u16 wOffset = 0;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		wOffset += 20;
		tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, 20000 + wOffset);
		tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, 20001 + wOffset);
		tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, 20003 + wOffset);
		tNodeCap.m_atVidEnc[wIndex].m_bIsChanOn = TRUE;
		tNodeCap.m_atVidEnc[wIndex].m_tPAHandle = wIndex;
		
		tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, 20004 + wOffset);
		tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, 20005 + wOffset);
		tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, 20007 + wOffset);
		tNodeCap.m_atVidDec[wIndex].m_bIsChanOn = TRUE;
		tNodeCap.m_atVidDec[wIndex].m_tPAHandle = wIndex;
		
		
		tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, 20010 + wOffset);
		tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, 20011 + wOffset);
		tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, 20013 + wOffset);
		tNodeCap.m_atAudEnc[wIndex].m_bIsChanOn = TRUE;
		tNodeCap.m_atAudEnc[wIndex].m_tPAHandle = wIndex;
		
		tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, 20014 + wOffset);
		tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, 20015 + wOffset);
		tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, 20017 + wOffset);
		tNodeCap.m_atAudDec[wIndex].m_bIsChanOn = TRUE;
		tNodeCap.m_atAudDec[wIndex].m_tPAHandle = wIndex;
	}
	
	TCapNode* ptNode = pInst->GetNodeMgr()->GetCapsetNode(wEpId);
	pInst->GetNodeMgr()->AssignNodeRes(ptNode, NULL);
	NotifyMsgToCall(evtp_Conf_UmsChannelConnect, tHandle, &tNodeCap, sizeof(tNodeCap));
}

API void stopconf(u16 wConfID)
{
	TLogUser tUser;
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_HungUpConf_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&wConfID, sizeof(wConfID));
	cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SERVICE_APP_INST);	
}

API void callep(u16 wConfID, u16 wType, s8* pDst)
{
	if (NULL == pDst)
	{
		return;
	}

	TTPAlias tAlias;
	tAlias.SetAlias((EmTpAliasType)wType, pDst);
	
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsInviteCnsByAlias_Cmd);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tAlias, sizeof(tAlias));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));	
}

API void calleptest(u16 wConfID, s8* pAlias, s8* pE164, s8* pIp, BOOL bIsAliasIP)
{
	u32_ip dwIP = 0;
	if (NULL != pIp)
	{
		dwIP = inet_addr(pIp);
	}
	
	if (bIsAliasIP)
	{
		if (NULL == pAlias || 0 == dwIP)
		{
			return;
		}
	}
	else
	{
		if (NULL == pAlias && NULL == pE164 && 0 == dwIP)
		{
			return;
		}
	}

	TTpCallAddr tCallAddr;
	tCallAddr.m_tAlias.SetAlias(tp_Alias_h323, pAlias);
	tCallAddr.m_tE164.SetAlias(tp_Alias_e164,pE164);
	tCallAddr.m_dwIP = dwIP;
	tCallAddr.m_bAliasIP = bIsAliasIP;

	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsInviteCnsByAlias_Cmd);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tCallAddr, sizeof(tCallAddr));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));	
}



API void callepid(u16 wConfID, u16 wEpID)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsInviteCnsByEpId_Cmd);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&wEpID, sizeof(wEpID));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

API void dropep(u16 wConfID, u16 wEpID)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsHangupCns_Cmd);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&wEpID, sizeof(wEpID));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
}

// 远遥请求 from cnc
API void cnsfeccep(u16 wConfID, u16 wDstEp, u8 byFeccType, u8 byCamType)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);
	TFeccInfo tInfo;
	tInfo.m_wConfID = wConfID;
	tInfo.m_wEpID = wDstEp;
	tInfo.m_tCamAct.setFeccParam((EmUmsFeccActType)byFeccType, byCamType);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_CNS_UMS_FeccReq);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tInfo, sizeof(TFeccInfo));
	cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SIPADAPTER_APP_INST);	
}

API void changespeaker(u16 wConfID, u16 wEpID)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, 0);

	TConfEpID tConfEp;
	tConfEp.m_wConfID = wConfID;
	tConfEp.m_wEpID = wEpID;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsConfApplySpeaker_Cmd);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&tConfEp, sizeof(tConfEp));
	cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SIPADAPTER_APP_INST);	
}

API void changeseat(u16 wConfID, u16 wEpID, u16 wSeatID)
{
	TUmsHandle tHandle;
	GetChairHandle(tHandle, wConfID, wSeatID);

	u8 bChanId = (u8)wSeatID;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_CnsSpeaker_Notify);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(&bChanId, sizeof(bChanId));
	cMsg.Post(UMS_CALL_APP_INST(wConfID), 0, UMS_SIPADAPTER_APP_INST);
}

API void nodeupdate(u16 wConfID, u16 wEpID, u16 wStartEp, u16 wEndEp, s8* szParentID)
{
	TConfNodeCallUpdateTrList tList;
	tList.m_wNum = wEndEp - wStartEp;
	if (tList.m_wNum >= 5 || tList.m_wNum == 0)
	{
		return;
	}
	for (u16 wIndex = 0; wIndex < tList.m_wNum; ++wIndex)
	{
		if (NULL != szParentID && memcmp(szParentID, "root", 4) == 0)
		{
			sprintf(tList.m_atList[wIndex].m_tID.m_szEpID, "%s.", szParentID);			
		}
		else
		{
			sprintf(tList.m_atList[wIndex].m_tID.m_szEpID, "%s%d.", szParentID, wStartEp+wIndex);
		}
		
		tList.m_atList[wIndex].m_wEpID = wStartEp+wIndex;
		tList.m_atList[wIndex].m_emEpType = emTPEndpointTypeUMS;
		tList.m_atList[wIndex].m_tConfName.SetAlias("a1");
		tList.m_atList[wIndex].m_emCallState = ums_UmsConfNodeState_online;
	}
	
	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfID, wEpID);
	NotifyMsgToCall(evtp_Conf_EpCallInfo_Update, tHandle, &tList, sizeof(tList));
}


//模拟混音器激励出来的会场
API u16 mixpower( u16 wConfID, u8 byEqpID, u8 byVacChanId)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));

	if ( !pInst->IsChairConf() )
	{
		return 0;
	}

	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return 0;
	}

	TMixVacResInfo tVacInfo;
	tVacInfo.m_byEqpId = byEqpID;
	tVacInfo.m_byVacChanId = byVacChanId;
	tVacInfo.m_abyChanId[0] = 0;
	tVacInfo.m_abyChanId[1] = 1;
	tVacInfo.m_abyChanId[2] = 2;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_mixer_vac_result_ntfy);
	cMsg.SetBody(&tVacInfo, sizeof(tVacInfo));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID));
	
	return 0;
}

API u16 adjres( u16 wConfID, u16 wEpID, u32 dwRes)
{
	TAdjustVidRes tRes;
	tRes.m_wEpID = wEpID;
	tRes.m_dwVidRes = dwRes;

	TUmsHandle thandle;
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_AdjustVidRes);
	cMsg.SetBody(&thandle, sizeof(thandle));
	cMsg.CatBody(&tRes, sizeof(tRes));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));

	return 0;
}

API u16 adjframe( u16 wConfID, u16 wEpID, u16 wFr)
{
	TAdjustFrameRate tFrm;
	tFrm.m_wEpID = wEpID;
	tFrm.m_wFrameRate = wFr;
	
	TUmsHandle thandle;
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_Conf_AdjustFrameRate);
	cMsg.SetBody(&thandle, sizeof(thandle));
	cMsg.CatBody(&tFrm, sizeof(tFrm));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID), 0, MAKEIID(AID_UMSSIPADAPTER_APP, 1));
	
	return 0;
}

API void dualep( u16 wConfID, u16 wEpID )
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));

	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}

	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}

	startdual(wConfID, pInst->chairID(), wEpID);

	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfID, wEpID);
	NotifyMsgToCall(ev_OpenDualChan_Incoming, tHandle, NULL, 0);

	TUmsNodeCapset tNodeCap;
	tNodeCap.m_wVidEncNum = 1;
	tNodeCap.m_wVidDecNum = 0;
	
	tNodeCap.m_wAudEncNum = 1;
	tNodeCap.m_wAudDecNum = 0;

	TUmsVidFormat atTpDualVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	memset(atTpDualVideoRes, 0, sizeof(atTpDualVideoRes));
	memcpy(atTpDualVideoRes, pInst->GetConfBase().m_atTpMinorVideoRes, pInst->GetConfBase().m_wMinorNum*sizeof(TUmsVidFormat));

	u16 wFormatIndex = 0;
	if ( atTpDualVideoRes[wFormatIndex].m_emQualityLvl == emTPH264HP )
	{
		tNodeCap.m_tVidSndCap.m_tHp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
		tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
		tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
		tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
		tNodeCap.m_tVidSndCap.m_tHp.m_emQualityLvl = emTPH264HP;
		
		tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
		
// 		tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
// 		tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
// 		tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
// 		tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
// 		tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl = emTPH264HP;
	}
	else
	{
		tNodeCap.m_tVidSndCap.m_tBp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
		tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
		tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
		tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
		tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl = emTPH264BP;

		tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = emTPVResEnd;
		
// 		tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
// 		tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
// 		tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
// 		tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
// 		tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;
	}

	s8 asIP[14] = "172.16.176.20";
	u32 dwDstIP = inet_addr(asIP);
	u16 wStartPort = 30000;
	tNodeCap.m_atVidEnc[0].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
	tNodeCap.m_atVidEnc[0].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
	tNodeCap.m_atVidEnc[0].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
	tNodeCap.m_atVidEnc[0].m_bIsChanOn = TRUE;
	tNodeCap.m_atVidEnc[0].m_tPAHandle = 1;
	wStartPort += 4;
	
	tNodeCap.m_atAudEnc[0].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
	tNodeCap.m_atAudEnc[0].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
	tNodeCap.m_atAudEnc[0].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
	tNodeCap.m_atAudEnc[0].m_bIsChanOn = TRUE;
	tNodeCap.m_atAudEnc[0].m_tPAHandle = 2;
	wStartPort += 4;

	NotifyMsgToCall(ev_OpenDualChan_Connect, tHandle, &tNodeCap, sizeof(tNodeCap));

	return ;
}

API void mkall( u16 wConfID,  u16 wEncrypModel = 0 /*0:none;1:des;2:aes;100:qt_every_s;101:qt_every_m;102:qt_every_conf*/)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));

	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}

	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}

	u16 wAlias = 0;
	s8 asIP[14] = "172.16.176.20";
	s8 cIps = '0';
	u16 wScreen = 3;
	u16 wFormatIndex = 0;

	BOOL32 bBreak = FALSE;
	u16 wBitRate = 3076;

	u16 wAudInx = 0;
	
	TUmsVidFormat atTpMainVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	memset(atTpMainVideoRes, 0, sizeof(atTpMainVideoRes));
	memcpy(atTpMainVideoRes, pInst->GetConfBase().m_atTpMainVideoRes, pInst->GetConfBase().m_wMainNum*sizeof(TUmsVidFormat));

	TUmsVidFormat atTpDualVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	memset(atTpDualVideoRes, 0, sizeof(atTpDualVideoRes));
	memcpy(atTpDualVideoRes, pInst->GetConfBase().m_atTpMinorVideoRes, pInst->GetConfBase().m_wMinorNum*sizeof(TUmsVidFormat));
	
	for (TCapNode* ptNode = pInst->GetNodeMgr()->FirstNode(); ptNode != NULL; ptNode = pInst->GetNodeMgr()->NextLoalNode(ptNode))
	{
		if ( !ptNode->m_bUsed || ptNode->IsChanOn() )
		{
			continue;
		}

		pInst->GetNodeMgr()->AssignNodeRes(ptNode, NULL);
		
		asIP[12] = cIps++;

		wAlias = strlen(ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);

		if ( ptNode->m_tCalledAddr.m_tAlias.m_abyAlias[wAlias-1] == 'T' )
		{
			wScreen = 1;
			callcon(wConfID, ptNode->m_wEpID, emTPEndpointH323MT, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);
		}
		else if ( ptNode->m_tCalledAddr.m_tAlias.m_abyAlias[wAlias-1] == '1' )
		{
			wScreen = 1;
			callcon(wConfID, ptNode->m_wEpID, emTPEndpointTypeCNS, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);
		}
		else if ( ptNode->m_tCalledAddr.m_tAlias.m_abyAlias[wAlias-1] == '3' )
		{
			wScreen = 3;
			callcon(wConfID, ptNode->m_wEpID, emTPEndpointTypeCNS, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);
		}

		TUmsHandle tHandle;
		tHandle.MakeAppHandle(wConfID, ptNode->m_wEpID);
		
		TUmsNodeCapset tNodeCap;

		if (wEncrypModel >= emTPEncryptTypeNone && wEncrypModel <= emTPEncryptTypeQtEveryConf )
		{
		    tNodeCap.m_tEncrypt.m_emEncryptModel = (EmTPEncryptType)wEncrypModel;
		}
        
		tNodeCap.m_wVidEncNum = wScreen;
		tNodeCap.m_wVidDecNum = wScreen;
		
		tNodeCap.m_wAudEncNum = wScreen;
		tNodeCap.m_wAudDecNum = wScreen;

		tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = emTPVResEnd;
		tNodeCap.m_tVidSndCap.m_tBp.m_emRes = emTPVResEnd;
		
		for ( wFormatIndex = 0; wFormatIndex < pInst->GetConfBase().m_wMainNum; wFormatIndex ++ )
		{
			if ( atTpMainVideoRes[wFormatIndex].m_emFormat == emTPVH261 )
			{
				continue;
			}

			atTpMainVideoRes[wFormatIndex].m_emFormat = emTPVH261;

			if ( atTpMainVideoRes[wFormatIndex].m_emQualityLvl == emTPH264HP )
			{
				tNodeCap.m_tVidSndCap.m_tHp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
				tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
				tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
				tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidSndCap.m_tHp.m_emQualityLvl = emTPH264HP;
	

				tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
				tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
				tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
				tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl = emTPH264HP;
				bBreak = TRUE;
				break;
			}
			else if ( atTpMainVideoRes[wFormatIndex].m_emQualityLvl == emTPH264BP )
			{
				tNodeCap.m_tVidSndCap.m_tBp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
				tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
				tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl = emTPH264BP;

				tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;

				bBreak = TRUE;
				break;
			}
		}

		if ( !bBreak )
		{
			if ( atTpMainVideoRes[0].m_emQualityLvl == emTPH264HP )
			{
				tNodeCap.m_tVidSndCap.m_tHp.m_emRes = atTpMainVideoRes[0].m_emRes;
				tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate = atTpMainVideoRes[0].m_wFrameRate;
				tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
				tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidSndCap.m_tHp.m_emQualityLvl = emTPH264HP;
	
				tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = atTpMainVideoRes[0].m_emRes;
				tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = atTpMainVideoRes[0].m_wFrameRate;
				tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
				tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl = emTPH264HP;

				bBreak = TRUE;
			}
			else
			{
				tNodeCap.m_tVidSndCap.m_tBp.m_emRes = atTpMainVideoRes[0].m_emRes;
				tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate = atTpMainVideoRes[0].m_wFrameRate;
				tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl = emTPH264BP;

				tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpMainVideoRes[0].m_emRes;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpMainVideoRes[0].m_wFrameRate;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;
			}
		}

		if ( wAudInx == pInst->GetConfBase().m_wAudFmtNum )
		{
			wAudInx = 0;
		}
		tNodeCap.m_tAudSndCap.m_atAudFmt[0] = pInst->GetConfBase().m_atAudFmt[wAudInx];
		tNodeCap.m_tAudRcvCap.m_atAudFmt[0] = pInst->GetConfBase().m_atAudFmt[wAudInx++];

		bBreak = FALSE;
		
		u32 dwDstIP = inet_addr(asIP);
		u16 wStartPort = 20000;
		u16 wIndex = 0;
		s32 symbolflag = 1;

		for (u16 wSrIndex = 1; wSrIndex <= wScreen; ++wSrIndex, symbolflag *= -1)
		{		
			wIndex = MIDSCREENINDEX + wSrIndex / 2 * symbolflag;

			tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atVidEnc[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atVidEnc[wIndex].m_tPAHandle = wIndex;
//			tNodeCap.m_atVidEnc[wIndex].m_wRealBitRate = wBitRate;
			wStartPort += 4;
			
			tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atVidDec[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atVidDec[wIndex].m_tPAHandle = wIndex;
			wStartPort += 4;

			if( wScreen == 3 )
			{//三屏 小码流
				tNodeCap.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
				tNodeCap.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
				tNodeCap.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
				tNodeCap.m_atSmallVidEnc[wIndex].m_bIsChanOn = TRUE;
				tNodeCap.m_atSmallVidEnc[wIndex].m_tPAHandle = wIndex;
				wStartPort += 4;

				tNodeCap.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
				tNodeCap.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
				tNodeCap.m_atSmallVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
				tNodeCap.m_atSmallVidDec[wIndex].m_bIsChanOn = TRUE;
				tNodeCap.m_atSmallVidDec[wIndex].m_tPAHandle = wIndex;
				wStartPort += 4;
			}
			
			tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atAudEnc[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atAudEnc[wIndex].m_tPAHandle = wIndex;
			wStartPort += 4;
			
			tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atAudDec[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atAudDec[wIndex].m_tPAHandle = wIndex;
			wStartPort += 4;
		}

		if( wScreen == 3 )
		{
			//混音
			tNodeCap.m_tAudMixEnc.m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_tAudMixEnc.m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_tAudMixEnc.m_bIsChanOn = TRUE;
			tNodeCap.m_tAudMixEnc.m_tPAHandle = wIndex;
			wStartPort += 4;
			
			tNodeCap.m_tAudMixDec.m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_tAudMixDec.m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_tAudMixDec.m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_tAudMixDec.m_bIsChanOn = TRUE;
			tNodeCap.m_tAudMixDec.m_tPAHandle = wIndex;
			wStartPort += 4;
		}
		
		NotifyMsgToCall(evtp_Conf_UmsChannelConnect, tHandle, &tNodeCap, sizeof(tNodeCap));

		tNodeCap.Clear();

		tNodeCap.m_wVidEncNum = 0;
		tNodeCap.m_wVidDecNum = 1;

		tNodeCap.m_wAudEncNum = 0;
		tNodeCap.m_wAudDecNum = 0;
		if( wScreen == 3 )
		{
			tNodeCap.m_wAudEncNum = 0;
			tNodeCap.m_wAudDecNum = 1;
		}


		wStartPort = 30000;
		tNodeCap.m_atVidDec[0].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
		tNodeCap.m_atVidDec[0].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
		tNodeCap.m_atVidDec[0].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
		tNodeCap.m_atVidDec[0].m_bIsChanOn = TRUE;
		tNodeCap.m_atVidDec[0].m_tPAHandle = 1;
		wStartPort += 4;
		if( wScreen == 3 )
		{
			tNodeCap.m_atAudDec[0].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atAudDec[0].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atAudDec[0].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atAudDec[0].m_bIsChanOn = TRUE;
			tNodeCap.m_atAudDec[0].m_tPAHandle = 2;
			wStartPort += 4;
		}

		tNodeCap.m_tAudRcvCap.m_atAudFmt[0] = pInst->GetConfBase().m_atAudFmt[0];

		wFormatIndex = 0;
		if( atTpDualVideoRes[wFormatIndex].m_emQualityLvl == emTPH264HP )
		{
			tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
			tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
			tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
			tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
			tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl = emTPH264HP;
		}
		else
		{
			tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
			tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
			tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
			tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
			tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;
		}

		NotifyMsgToCall(ev_OpenDualChan_Connect, tHandle, &tNodeCap, sizeof(tNodeCap));
	}

	return ;
}


API void bastest(u16 wConfID, u16 wSpeakerIndx, u16 wDualIndx, BOOL32 bCreateTmp = FALSE)
{
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_BasTestAdjust_Cmd);
	cMsg.SetBody(&wSpeakerIndx, sizeof(wSpeakerIndx));
	cMsg.CatBody(&wDualIndx, sizeof(wDualIndx));
	cMsg.CatBody(&bCreateTmp, sizeof(u32));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID));
}

//讨论相关命令
API void dis(u16 wConfID, BOOL32 bStart, u16 wOne = 0, u16 wTwo = 0, u16 wThree = 0, u16 wFoure = 0, u16 wFive = 0)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}

// 	if ( bStart && pInst->GetUmsDiscuss()->IsDiscussModle() )
// 	{
// 		msgprint("this Conf is Dis Mdl, can not use [dis] API!\n");
// 		return ;
// 	}
	
	TConfAuxMixInfo tConfEp;
	tConfEp.m_wConfID = wConfID;
	tConfEp.m_bStart = bStart;
	if ( wOne != 0 )
	{
		tConfEp.m_atAuxMixList.AddMixID(wOne);
	}

	if ( wTwo != 0 )
	{
		tConfEp.m_atAuxMixList.AddMixID(wTwo);
	}

	if ( wThree != 0 )
	{
		tConfEp.m_atAuxMixList.AddMixID(wThree);
	}

	if ( wFoure != 0 )
	{
		tConfEp.m_atAuxMixList.AddMixID(wFoure);
	}

	if ( wFive != 0 )
	{
		tConfEp.m_atAuxMixList.AddMixID(wFive);
	}
	
//	tConfEp.m_atAuxMixList.SetSpeakerIndex(wSpeakerIndex);
	
	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());

	NotifyMsgToCall(ev_UmsConfAMixUpdate_Cmd, tOutHandle, &tConfEp, sizeof(TConfAuxMixInfo));
}

API void disadd(u16 wConfID, u16 wEpId1 = 0, u16 wEpId2 = 0, u16 wEpId3 = 0)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}

	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());

	TDiscussListOpr tOpr;
	tOpr.m_wConfId = wConfID;
	u16 wNum = 0;
	if (0 != wEpId1)
	{
		tOpr.m_awEpId[wNum] = wEpId1;
		wNum++;
	}

	if (0 != wEpId2)
	{
		tOpr.m_awEpId[wNum] = wEpId2;
		wNum++;
	}

	if (0 != wEpId3)
	{
		tOpr.m_awEpId[wNum] = wEpId3;
		wNum++;
	}

	tOpr.m_wNum = wNum;
	tOpr.m_emOprType = em_DisListOpr_Add;
	
	NotifyMsgToCall(ev_UmsAudMixDisListOpr_Cmd, tOutHandle, &tOpr, sizeof(tOpr));
}

API void disvac(u16 wConfId, BOOL32 bVacOn)
{

	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfId));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}

	TConfAuxMixVacOpr tVac;

	tVac.m_wConfID = wConfId;
	tVac.m_bVacOn = bVacOn;

	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfId, pInst->chairID());

	NotifyMsgToCall(ev_UmsConfAMixVacSwitch, tOutHandle, &tVac, sizeof(TConfAuxMixVacOpr));
}

API void disdel(u16 wConfID, u16 wEpId1 = 0, u16 wEpId2 = 0, u16 wEpId3 = 0)
{	
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}
	
	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());
	
	TDiscussListOpr tOpr;
	tOpr.m_wConfId = wConfID;
	u16 wNum = 0;
	if (0 != wEpId1)
	{
		tOpr.m_awEpId[wNum] = wEpId1;
		wNum++;
	}
	
	if (0 != wEpId2)
	{
		tOpr.m_awEpId[wNum] = wEpId2;
		wNum++;
	}
	
	if (0 != wEpId3)
	{
		tOpr.m_awEpId[wNum] = wEpId3;
		wNum++;
	}
	
	tOpr.m_wNum = wNum;
	tOpr.m_emOprType = em_DisListOpr_Del;
	
	NotifyMsgToCall(ev_UmsAudMixDisListOpr_Cmd, tOutHandle, &tOpr, sizeof(tOpr));
}

API void selview(u16 wConfID, u16 wEpID, u16 wScrIndx, u16 wDstEpID, u16 wType = 0)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}

	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());

	TTPSelViewReq tReq;
	tReq.m_wEpID = wEpID;
	tReq.m_wScreenIndx = wScrIndx;
	tReq.m_emType = (EmViewEpType)wType;
	tReq.m_wDstID = wDstEpID;

	NotifyMsgToCall(ev_CNC_UMS_SelView_Req, tOutHandle, &tReq, sizeof(tReq));
}

API void brdvmp(u16 wConfID, u16 wEqpID)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}
	
	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());
	
	TRersvesEqpReq tReq;
	tReq.m_bRersves = TRUE;
	tReq.m_tEqp.m_byEqpID = wEqpID;

	NotifyMsgToCall(ev_CNC_UMS_RervesBrdVmp_Req, tOutHandle, &tReq, sizeof(tReq));


	TSetVmpInfoReq tSetReq;
	tSetReq.m_tEqp.m_byEqpID = wEqpID;
	tSetReq.m_tStyle.m_emVmpStyle = tp_VmpStyle_DYNAMIC;

	NotifyMsgToCall(ev_CNC_UMS_SetBrdVmp_Req, tOutHandle, &tSetReq, sizeof(tSetReq));

	TBrdVmpReq tBrdReq;
	tBrdReq.m_tEqp.m_byEqpID = wEqpID;
	tBrdReq.m_bBrd = TRUE;

	NotifyMsgToCall(ev_CNC_UMS_BrdVmp_Req, tOutHandle, &tBrdReq, sizeof(tBrdReq));
}

API void unbrdvmp(u16 wConfID, u16 wEqpID)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}
	
	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());
	
	TRersvesEqpReq tReq;
	tReq.m_bRersves = FALSE;
	tReq.m_tEqp.m_byEqpID = wEqpID;
	
	NotifyMsgToCall(ev_CNC_UMS_RervesBrdVmp_Req, tOutHandle, &tReq, sizeof(tReq));
}

API void unselview(u16 wConfID, u16 wEpID, u16 wScrIndx, u16 wDstEpID, u16 wType = 0)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}
	
	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());
	
	TTPSelViewReq tReq;
	tReq.m_bSel = FALSE;
	tReq.m_wEpID = wEpID;
	tReq.m_wScreenIndx = wScrIndx;
	tReq.m_emType = (EmViewEpType)wType;
	tReq.m_wDstID = wDstEpID;
	
	NotifyMsgToCall(ev_CNC_UMS_SelView_Req, tOutHandle, &tReq, sizeof(tReq));
}

API void setscrnum(u32 dwSetNum)
{
	msgprint("setscrnum setNum = %d, m_dwOnlineChanNum = %d\n", dwSetNum, CUmsConfInst::GetOnlineNum());
	u32 dwTmp = CUmsConfInst::GetLicenseNum();
	if (dwSetNum > dwTmp)
	{
		msgprint("dwSetNum:%d more than m_dwLicenseChanNum:%d,setscrnum failure\n", dwSetNum, dwTmp);
		return;
	}
	CUmsConfInst::SetOnlineNum(dwSetNum);
	msgprint("onlinechan num = %d\n", CUmsConfInst::GetOnlineNum());
}
API void showscrnum()
{
	msgprint("m_dwOnlineChanNum = %d\n", CUmsConfInst::GetOnlineNum());
}

API void setlicenum(u32 dwNum)
{
	msgprint("setlicenum setNum = %d, m_dwLicenseChanNum = %d\n", dwNum, CUmsConfInst::GetLicenseNum());
	if (dwNum > 192)
	{
		msgprint("setnum:%d more than max license maxnum, setlicenum failure\n", dwNum);
		return;
	}
	CUmsConfInst::SetLicenseNum(dwNum);
	msgprint("license num = %d\n", CUmsConfInst::GetLicenseNum());
}

API void showlicenum()
{
	msgprint("m_dwLicenseChanNum = %d\n", CUmsConfInst::GetLicenseNum());
}

API void settime(u32 dwTime)
{
	CUmsConfInst::SetDelayTime(dwTime);
	msgprint("m_dwTime = %d\n", CUmsConfInst::GetDelayTime());
}

API void showtime()
{
	msgprint("m_dwTime = %d\n", CUmsConfInst::GetDelayTime());
}


API void quietep(u16 wConfID, u16 wEpID, BOOL32 bQuiet)
{
	TQuietRmtEpCmd tCmd;
	tCmd.m_bQuiet = bQuiet;
	tCmd.m_wEpID = wEpID;

	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, wEpID);
	NotifyMsgToCall(evtp_Conf_QuietRemoteEp_Cmd, tOutHandle, &tCmd, sizeof(tCmd));
}

API void muteep(u16 wConfID, u16 wEpID, BOOL32 bMute)
{
	TMuteRmtEpCmd tCmd;
	tCmd.m_bMute = bMute;
	tCmd.m_wEpID = wEpID;
	
	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, wEpID);
	NotifyMsgToCall(evtp_Conf_MuteRemoteEp_Cmd, tOutHandle, &tCmd, sizeof(tCmd));
}
API void savecncvmp(u16 wConfID)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));
	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}
	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}
	TUmsHandle tOutHandle;
	tOutHandle.MakeAppHandle(wConfID, pInst->chairID());
	
	TTpVmpMemberCfg tCfg;
	tCfg.m_wConfID = wConfID;
	tCfg.m_emStyle = tp_VmpStyle_FOUR;
	tCfg.m_wEpNum = 2;
	tCfg.m_atEpList[0].m_tEpAlias.SetAlias("tA3");
	tCfg.m_atEpList[1].m_tEpAlias.SetAlias("tA1");
	
//	NotifyMsgToCall(ev_CNC_UMS_SaveVmpCfg_Cmd, tOutHandle, &tCfg, sizeof(tCfg));
}

API void hduplay(u16 wConfid, u16 wDstep, BOOL32 bVmp, u16 wIndex, u16 wSubIndex = 0)
{
	TUmsHandle tHandle;
	TTPHduPlayReq tInfo;
	
	tHandle.MakeAppHandle(wConfid, wDstep);

	tInfo.m_wConfID = wConfid;
	tInfo.m_wDstID = wDstep;
	tInfo.m_emType = EmEpType_Ter;
	tInfo.m_wScreenNum = 1;
	
	tInfo.m_bVmp = bVmp;
	tInfo.m_wIndex = wIndex;
	tInfo.m_bySubIndex = (u8)wSubIndex;
	
	NotifyMsgToCall(evTPCNS_UMS_HduPlay_Req, tHandle, &tInfo, sizeof(tInfo));
}

API void hdustop(u16 wConfid, u16 wDstep, BOOL32 bVmp, u16 wIndex, u16 wSubIndex = 0)
{
	TUmsHandle tHandle;
	TTPHduPlayReq tInfo;
	
	tHandle.MakeAppHandle(wConfid, wDstep);
	
	tInfo.m_wConfID = wConfid;
	tInfo.m_wDstID = wDstep;
	tInfo.m_emType = EmEpType_Ter;
	tInfo.m_wScreenNum = 1;
	
	tInfo.m_bVmp = bVmp;
	tInfo.m_wIndex = wIndex;
	tInfo.m_bySubIndex = (u8)wSubIndex;
	
	NotifyMsgToCall(evTPCNS_UMS_HduStopPlay_Req, tHandle, &tInfo, sizeof(tInfo));
}

API void hdustopall(u16 wConfID, u16 wEpID)
{
	TUmsHandle tHandle;
	tHandle.MakeAppHandle(wConfID, wEpID);
	
	NotifyMsgToCall(evTPCNS_UMS_HduStopAllPlay_Req, tHandle, NULL, 0);
}

API void hdusetvol(u16 wConfID, u16 wEpID, u16 wVol, u16 wMute, u16 wIndex, u16 wSubIndex = 0)
{
	TUmsHandle tHandle;
	THduSetVolInfo tInfo;
	tHandle.MakeAppHandle(wConfID, wEpID);
	tInfo.m_byVol = wVol;
	tInfo.m_bMute = wMute;
	tInfo.m_tInfo.m_wIndex = wIndex;
	tInfo.m_tInfo.m_bySubIndex = (u8)wSubIndex;
	
	NotifyMsgToCall(evTPCNS_UMS_HduSetVol_Req, tHandle, &tInfo, sizeof(tInfo));
}

API void hduchangemode(u16 wConfID, u16 wEpID, u16 wIndex, u16 wMode)
{
	TUmsHandle tHandle;
	THduChanModeSetInfo tInfo;
	tHandle.MakeAppHandle(wConfID, wEpID);
	tInfo.m_wIndex = wIndex;
	tInfo.m_byMode = (u8)wMode;
	NotifyMsgToCall(evTPCNS_UMS_HduChangeChanMode_Req, tHandle, &tInfo, sizeof(tInfo));
}

API void callhelp()
{
	msgprintnotime("callver()                                   --显示umscall版本号\n");

	msgprintnotime("umscall(int callID)                         --显示ID为callID的会议信息，参数为0时显示所有会议的信息\n");
	msgprintnotime("umsport(int callID)                         --显示会议端口信息\n");
	msgprintnotime("umsallport(int callID)                      --显示会议所有分配的静态端口\n");
	msgprintnotime("umsportres(void)                            --显示ums占用的端口资源\n");
	msgprintnotime("umsds(int callID)                           --显示会议的码流交换信息\n");
	
	msgprintnotime("umscm()                                     --显示ums的双网卡转发板信息及会场请求入会信息\n");
	msgprintnotime("umsgetvid()                                 --显示回传通道信息\n");
	msgprintnotime("umsbw(u16 wConfID)                          --显示会议的带宽信息\n");
	msgprintnotime("umsresfrm(int callID)                       --显示会议的分辨率及帧率调整信息\n");

	msgprintnotime("umstv()                                     --显示电视墙信息\n");
	msgprintnotime("umsvmptp()                                  --显示call侧的vmptp信息\n");
	msgprintnotime("umsbas(int callID)                          --显示会议的适配信息\n");
	msgprintnotime("umseapu(int callID)                         --显示会议的混音器信息\n");
	msgprintnotime("umsvmp(int callID)                          --显示会议的合成信息\n");
	msgprintnotime("umsdual(int callID)                         --显示会议的双流信息\n");
	msgprintnotime("umspoll(int callID)                         --显示会议的轮询状态\n");
	msgprintnotime("umsdis(int callID)                          --显示会议讨论信息\n");
	msgprintnotime("umsview(int callID)                         --显示会议选看信息\n");
	msgprintnotime("umsrollcall(int callID)                     --显示会议点名信息\n");
	msgprintnotime("umsaudmix(int callID)                       --显示会议会议混音信息\n");

	msgprintnotime("\n");
	msgprintnotime("showreg()                                   --显示sip和gk注册状态\n");
	msgprintnotime("showscrnum()                                --显示在线屏数\n");
	msgprintnotime("showlicenum()                               --显示授权点数\n");

	msgprintnotime("\n以下命令仅供开发本地调试使用!\n");

	//
	msgprintnotime("callcon(u16 wConfid, u16 wEpId, u32 type, s8* epname)                     --指定节点连接 type(1:CNS, 2:UMS) \n");
	msgprintnotime("chancon(u16 wConfid, u16 wEpId,  u16 screen, s8* szIp)                    --指定节点通道建立 screen:屏数量， IP为结点IP\n");
	msgprintnotime("calldiscon(u16 wConfid, u16 wEpId, u32 dwReson)                           --指定节点断链reson:\n");
	msgprintnotime("setpolltime(u16 wConfID, u16 wTime)                                       --设置轮询时间间隔, 单位秒\n");
	
	//->umscall
	msgprintnotime("mixpower(u16 wConfID, u16 wEpID)                              --- 模拟语音激励切换发言人\n");
	
	msgprintnotime("changespeaker(u16 ConfID, u16 EpID)                           ---  更新发言人\n");
	msgprintnotime("changeseat(u16 ConfID, u16 EpID, u16 Seat)                    ---  更新坐席\n");
	
	msgprintnotime("callep(u16 ConfID, int type, s8*name)                         ---  在会议中呼叫一个节点，type(1: 164, 2: 323ID, 3:IP) \n");
	msgprintnotime("calleptest(u16 wConfID, s8* pAlias, s8* pE164, s8* pIp, BOOL bIsAliasIP)  ---bIsAliasIP为1表示IP+别名呼叫\n");
	msgprintnotime("callepid(u16 ConfID, u16 EpID)                                ---  呼叫节点 ConfID: 会议ID， EpID：节点ID\n");
	msgprintnotime("dropep(u16 ConfID, u16 EpID)                                  ---  挂断 ConfID: 会议ID， EpID：节点ID\n");
	
	msgprintnotime("umcquietep(u16 wConfID, u16 wEpID, BOOL32 bQuiet)                ---  静音 ConfID: 会议ID， EpID：节点ID，TRUE为静音/FALS为恢复\n");
	msgprintnotime("umcmuteep(u16 wConfID, u16 wEpID, BOOL32 bMute)                  ---  哑音 ConfID: 会议ID， EpID：节点ID, TRUE为哑音/FALS为恢复\n");

	msgprintnotime("startpoll(u16 wConfID)                                        ---  开始轮询\n");
	msgprintnotime("stoppoll(u16 wConfID)                                         ---  停止轮询\n");
	msgprintnotime("suspendpoll(u16 wConfID)                                      ---  暂停/恢复轮询\n");
	msgprintnotime("nodeupdate(u16 wConfID, u16 wEpID, u16 wStartEp, u16 wEndEp, s8* szParentID)    --- 下级向上级更新会议结点\n");
	
	msgprintnotime("startdual(u16 wConfID, u16 wChairEpID, u16 wDuaDstEpID)       ---  开启结点双流\n");
	msgprintnotime("stopdual(u16 wConfID, u16 wChairEpID, u16 wDuaDstEpID)        ---  关闭结点双流\n");
	msgprintnotime("mkall(u16 ConfID)                                             ---  模拟呼叫整个会议中的会场\n");
	msgprintnotime("  注意创建模板时，会场别名最后一个字母为T表示终端，为1表示模拟单屏，为3表示模拟三屏）, 使用方法：1、开启会议。2、使用该命令\n");
	
	msgprintnotime("dis(u16 wConfID, BOOL32 bStart, u16 wSpeakerIndex, u16 wOne, u16 wTwo, u16 wThree, u16 wFoure) ---	开启讨论、或者在讨论关闭情况下修改各通道结点\n");
	msgprintnotime("disadd(u16 wConfID, u16 wEpID, u16 wUILocal)                  ---  在讨论开启下，添加一个通道\n");
	msgprintnotime("disdel(u16 wConfID, u16 wEpID, u16 wUILocal)                  ---  在讨论开启下，删除一个通道\n");
	msgprintnotime("setscrnum(u32 dwSetNum)                                       ---  设置会议在线屏数\n");
	msgprintnotime("setlicenum(u32 dwNum)                                         ---  设置授权点数\n");

	msgprintnotime("adjframe(u16 wConfID, u16 wEpID, u16 wFr)                     ---  模拟调整某会场帧率\n");
	msgprintnotime("adjres(u16 wConfID, u16 wEpID, u32 dwRes)                     ---  模拟调整某会场分辨率\n");


	msgprintnotime("startvmp(u16 wConfID, s8* pszDstIP, u16 wDstPort, u32 dwDstEpType)  ---  开启会议合成码流到某个目的地址\n");

	msgprintnotime("bastest(u16 wConfID, u16 wSpeakerIndx, u16 wDualIndx, BOOL32 bCreateTmp = FALSE)  --- 随机测试适配各种格式的适配效果\n");
	msgprintnotime("          - wConfID:任意未开会的Inst，wSpeakerIndx 主视频中选为发言人的索引，wDualIndx 双流选为双流源的索引\n");
	msgprintnotime("          - bCreateTmp 为True 则重新随机生成格式模板。\n");

	msgprintnotime("selview(u16 wConfID, u16 wEpID, u16 wScrIndx, u16 wDstEpID, u16 wType = 0)   --- 模拟CNC自由选看\n");

	msgprintnotime("unselview(u16 wConfID, u16 wEpID, u16 wScrIndx, u16 wDstEpID, u16 wType = 0) --- 模拟CNC取消自由选看\n");

	msgprintnotime("brdvmp(u16 wConfID, u16 wEqpID)                              --- 模拟广播合成\n");
	msgprintnotime("unbrdvmp(u16 wConfID, u16 wEqpID)                            --- 模拟取消广播合成\n");
	msgprintnotime("savecncvmp(u16 wConfID)										 --- 保存合成预案\n");

}
API void getmcuspy(u16 wConf, u16 wMcuLowEpId);
API void mkallbp( u16 wConfID,  u16 wEncrypModel = 0 /*0:none;1:des;2:aes;100:qt_every_s;101:qt_every_m;102:qt_every_conf*/)
{
	CUmsConfInst* pInst = (CUmsConfInst*)(((CApp*)&g_cUmsCallMgrApp)->GetInstance(wConfID));

	if ( NULL == pInst )
	{
		msgprint("this Conf is NULL!\n");
		return ;
	}

	if ( pInst->CurState() ==  CUmsConfInst::inst_idle)
	{
		msgprint("this Conf is Idle!\n");
		return ;
	}

	u16 wAlias = 0;
	s8 asIP[14] = "172.16.176.20";
	s8 cIps = '0';
	u16 wScreen = 3;
	u16 wFormatIndex = 0;

	BOOL32 bBreak = FALSE;
	u16 wBitRate = 3076;

	u16 wAudInx = 0;

	TUmsVidFormat atTpMainVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	memset(atTpMainVideoRes, 0, sizeof(atTpMainVideoRes));
	memcpy(atTpMainVideoRes, pInst->GetConfBase().m_atTpMainVideoRes, pInst->GetConfBase().m_wMainNum*sizeof(TUmsVidFormat));

	TUmsVidFormat atTpDualVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	memset(atTpDualVideoRes, 0, sizeof(atTpDualVideoRes));
	memcpy(atTpDualVideoRes, pInst->GetConfBase().m_atTpMinorVideoRes, pInst->GetConfBase().m_wMinorNum*sizeof(TUmsVidFormat));

	for (TCapNode* ptNode = pInst->GetNodeMgr()->FirstNode(); ptNode != NULL; ptNode = pInst->GetNodeMgr()->NextLoalNode(ptNode))
	{
		if ( !ptNode->m_bUsed || ptNode->IsChanOn() )
		{
			continue;
		}

		pInst->GetNodeMgr()->AssignNodeRes(ptNode, NULL);

		asIP[12] = cIps++;

		wAlias = strlen(ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);

		if ( ptNode->m_tCalledAddr.m_tAlias.m_abyAlias[wAlias-1] == 'T' )
		{
			wScreen = 1;
			callcon(wConfID, ptNode->m_wEpID, emTPEndpointH323MT, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);
		}
		else if ( ptNode->m_tCalledAddr.m_tAlias.m_abyAlias[wAlias-1] == '1' )
		{
			wScreen = 1;
			callcon(wConfID, ptNode->m_wEpID, emTPEndpointTypeCNS, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);
		}
		else if ( ptNode->m_tCalledAddr.m_tAlias.m_abyAlias[wAlias-1] == '3' )
		{
			wScreen = 3;
			callcon(wConfID, ptNode->m_wEpID, emTPEndpointTypeCNS, ptNode->m_tCalledAddr.m_tAlias.m_abyAlias);
		}

		TUmsHandle tHandle;
		tHandle.MakeAppHandle(wConfID, ptNode->m_wEpID);

		TUmsNodeCapset tNodeCap;

		if (wEncrypModel >= emTPEncryptTypeNone && wEncrypModel <= emTPEncryptTypeQtEveryConf )
		{
			tNodeCap.m_tEncrypt.m_emEncryptModel = (EmTPEncryptType)wEncrypModel;
		}

		tNodeCap.m_wVidEncNum = wScreen;
		tNodeCap.m_wVidDecNum = wScreen;

		tNodeCap.m_wAudEncNum = wScreen;
		tNodeCap.m_wAudDecNum = wScreen;

		tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = emTPVResEnd;
		tNodeCap.m_tVidSndCap.m_tHp.m_emRes = emTPVResEnd;

		for ( wFormatIndex = 0; wFormatIndex < pInst->GetConfBase().m_wMainNum; wFormatIndex ++ )
		{
			if ( atTpMainVideoRes[wFormatIndex].m_emFormat == emTPVH261 )
			{
				continue;
			}

			atTpMainVideoRes[wFormatIndex].m_emFormat = emTPVH261;

// 			if ( atTpMainVideoRes[wFormatIndex].m_emQualityLvl == emTPH264BP )
// 			{
// 				tNodeCap.m_tVidSndCap.m_tHp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
// 				tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
// 				tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
// 				tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
// 				tNodeCap.m_tVidSndCap.m_tHp.m_emQualityLvl = emTPH264BP;
// 
// 
// 				tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
// 				tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
// 				tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
// 				tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
// 				tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl = emTPH264BP;
// 				bBreak = TRUE;
// 				break;
// 			}
// 			else 
			if ( atTpMainVideoRes[wFormatIndex].m_emQualityLvl == emTPH264BP )
			{
				tNodeCap.m_tVidSndCap.m_tBp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
				tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
				tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl = emTPH264BP;

				tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpMainVideoRes[wFormatIndex].m_emRes;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpMainVideoRes[wFormatIndex].m_wFrameRate;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;

				bBreak = TRUE;
				break;
			}
		}

		if ( !bBreak )
		{
// 				if ( atTpMainVideoRes[1].m_emQualityLvl == emTPH264HP )
// 				{
// 						tNodeCap.m_tVidSndCap.m_tHp.m_emRes = atTpMainVideoRes[1].m_emRes;
// 						tNodeCap.m_tVidSndCap.m_tHp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
// 						tNodeCap.m_tVidSndCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
// 						tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
// 						tNodeCap.m_tVidSndCap.m_tHp.m_emQualityLvl = emTPH264BP;
// 
// 						tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = atTpMainVideoRes[1].m_emRes;
// 						tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
// 						tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
// 						tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
// 						tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl = emTPH264BP;
// 						
// 						bBreak = TRUE;
// 			}
// 			else 
				if ( atTpMainVideoRes[0].m_emQualityLvl == emTPH264BP )
			{
				tNodeCap.m_tVidSndCap.m_tBp.m_emRes = atTpMainVideoRes[1].m_emRes;
				tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
				tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl = emTPH264BP;

				tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpMainVideoRes[1].m_emRes;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
				tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
				tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;
			}
				else if ( atTpMainVideoRes[1].m_emQualityLvl == emTPH264BP )
				{
					tNodeCap.m_tVidSndCap.m_tBp.m_emRes = atTpMainVideoRes[1].m_emRes;
					tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
					tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
					tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
					tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl = emTPH264BP;

					tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpMainVideoRes[1].m_emRes;
					tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
					tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
					tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
					tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;
				}
				else if ( atTpMainVideoRes[2].m_emQualityLvl == emTPH264BP )
				{
					tNodeCap.m_tVidSndCap.m_tBp.m_emRes = atTpMainVideoRes[1].m_emRes;
					tNodeCap.m_tVidSndCap.m_tBp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
					tNodeCap.m_tVidSndCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
					tNodeCap.m_tVidSndCap.m_wDynamicPayload = MEDIA_TYPE_H264;
					tNodeCap.m_tVidSndCap.m_tBp.m_emQualityLvl = emTPH264BP;

					tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpMainVideoRes[1].m_emRes;
					tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpMainVideoRes[1].m_wFrameRate;
					tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
					tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
					tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;
				}
		}

		if ( wAudInx == pInst->GetConfBase().m_wAudFmtNum )
		{
			wAudInx = 0;
		}
		tNodeCap.m_tAudSndCap.m_atAudFmt[0] = pInst->GetConfBase().m_atAudFmt[wAudInx];
		tNodeCap.m_tAudRcvCap.m_atAudFmt[0] = pInst->GetConfBase().m_atAudFmt[wAudInx++];

		bBreak = FALSE;

		u32 dwDstIP = inet_addr(asIP);
		u16 wStartPort = 20000;
		u16 wIndex = 0;
		s32 symbolflag = 1;

		for (u16 wSrIndex = 1; wSrIndex <= wScreen; ++wSrIndex, symbolflag *= -1)
		{		
			wIndex = MIDSCREENINDEX + wSrIndex / 2 * symbolflag;

			tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atVidEnc[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atVidEnc[wIndex].m_tPAHandle = wIndex;
			//			tNodeCap.m_atVidEnc[wIndex].m_wRealBitRate = wBitRate;
			wStartPort += 4;

			tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atVidDec[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atVidDec[wIndex].m_tPAHandle = wIndex;
			wStartPort += 4;

			if( wScreen == 3 )
			{//三屏 小码流
				tNodeCap.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
				tNodeCap.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
				tNodeCap.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
				tNodeCap.m_atSmallVidEnc[wIndex].m_bIsChanOn = TRUE;
				tNodeCap.m_atSmallVidEnc[wIndex].m_tPAHandle = wIndex;
				wStartPort += 4;

				tNodeCap.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
				tNodeCap.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
				tNodeCap.m_atSmallVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
				tNodeCap.m_atSmallVidDec[wIndex].m_bIsChanOn = TRUE;
				tNodeCap.m_atSmallVidDec[wIndex].m_tPAHandle = wIndex;
				wStartPort += 4;
			}

			tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atAudEnc[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atAudEnc[wIndex].m_tPAHandle = wIndex;
			wStartPort += 4;

			tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atAudDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atAudDec[wIndex].m_bIsChanOn = TRUE;
			tNodeCap.m_atAudDec[wIndex].m_tPAHandle = wIndex;
			wStartPort += 4;
		}

		if( wScreen == 3 )
		{
			//混音
			tNodeCap.m_tAudMixEnc.m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_tAudMixEnc.m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_tAudMixEnc.m_bIsChanOn = TRUE;
			tNodeCap.m_tAudMixEnc.m_tPAHandle = wIndex;
			wStartPort += 4;

			tNodeCap.m_tAudMixDec.m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_tAudMixDec.m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_tAudMixDec.m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_tAudMixDec.m_bIsChanOn = TRUE;
			tNodeCap.m_tAudMixDec.m_tPAHandle = wIndex;
			wStartPort += 4;
		}

		NotifyMsgToCall(evtp_Conf_UmsChannelConnect, tHandle, &tNodeCap, sizeof(tNodeCap));

		tNodeCap.Clear();

		tNodeCap.m_wVidEncNum = 0;
		tNodeCap.m_wVidDecNum = 1;

		tNodeCap.m_wAudEncNum = 0;
		tNodeCap.m_wAudDecNum = 0;
		if( wScreen == 3 )
		{
			tNodeCap.m_wAudEncNum = 0;
			tNodeCap.m_wAudDecNum = 1;
		}


		wStartPort = 30000;
		tNodeCap.m_atVidDec[0].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
		tNodeCap.m_atVidDec[0].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
		tNodeCap.m_atVidDec[0].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
		tNodeCap.m_atVidDec[0].m_bIsChanOn = TRUE;
		tNodeCap.m_atVidDec[0].m_tPAHandle = 1;
		wStartPort += 4;
		if( wScreen == 3 )
		{
			tNodeCap.m_atAudDec[0].m_tChanAddr.m_tRtpAddr.SetAddr(dwDstIP, wStartPort);
			tNodeCap.m_atAudDec[0].m_tChanAddr.m_tRtcpAddr.SetAddr(dwDstIP, wStartPort + 1);
			tNodeCap.m_atAudDec[0].m_tChanAddr.m_tBackRtcpAddr.SetAddr(dwDstIP, wStartPort + 3);
			tNodeCap.m_atAudDec[0].m_bIsChanOn = TRUE;
			tNodeCap.m_atAudDec[0].m_tPAHandle = 2;
			wStartPort += 4;
		}

		tNodeCap.m_tAudRcvCap.m_atAudFmt[0] = pInst->GetConfBase().m_atAudFmt[0];

		wFormatIndex = 0;
		if( atTpDualVideoRes[wFormatIndex].m_emQualityLvl == emTPH264BP )
		{
			tNodeCap.m_tVidRcvCap.m_tHp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
			tNodeCap.m_tVidRcvCap.m_tHp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
			tNodeCap.m_tVidRcvCap.m_tHp.m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
			tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
			tNodeCap.m_tVidRcvCap.m_tHp.m_emQualityLvl = emTPH264BP;
		}
		else
		{
			tNodeCap.m_tVidRcvCap.m_tBp.m_emRes = atTpDualVideoRes[wFormatIndex].m_emRes;
			tNodeCap.m_tVidRcvCap.m_tBp.m_wFrameRate = atTpDualVideoRes[wFormatIndex].m_wFrameRate;
			tNodeCap.m_tVidRcvCap.m_tBp.m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
			tNodeCap.m_tVidRcvCap.m_wDynamicPayload = MEDIA_TYPE_H264;
			tNodeCap.m_tVidRcvCap.m_tBp.m_emQualityLvl = emTPH264BP;
		}

		NotifyMsgToCall(ev_OpenDualChan_Connect, tHandle, &tNodeCap, sizeof(tNodeCap));
	}

	return ;
}

void regist_ums_call_commond()
{
#ifdef _LINUX_
	OspRegCommand("callhelp", (void*)callhelp, "callhelp()");

	OspRegCommand("callver", (void*)callver, "callver(int)");

	// begin instdump
	OspRegCommand("umscall", (void*)umscall, "umscall(int)");
	OspRegCommand("umsport", (void*)umsport, "umsport(int)");
	OspRegCommand("umsallport", (void*)umsallport, "umsallport(int)");
	OspRegCommand("umsportres", (void*)umsportres, "umsportres(void)");
	OspRegCommand("umsds", (void*)umsds, "umsds(int)");

	OspRegCommand("umscm", (void*)umscm, "umscm");
	OspRegCommand("umseplist", (void*)umseplist, "umseplist");
	OspRegCommand("umsvmptp", (void*)umsvmptp, "umsvmptp()");
	OspRegCommand("umsgetvid", (void*)umsgetvid, "umsgetvid()");
	OspRegCommand("umsbw", (void*)umsbw, "umsbw(int)");
	OspRegCommand("umsresfrm", (void*)umsresfrm, "umsresfrm(int)");

	OspRegCommand("umstv", (void*)umstv, "umstv(void)");
	OspRegCommand("umsbas", (void*)umsbas, "umsbas(int)");
	OspRegCommand("umseapu", (void*)umseapu, "umseapu(int)");
	OspRegCommand("umsvmp", (void*)umsvmp, "umsvmp(int)");
	OspRegCommand("umsdual", (void*)umsdual, "umsdual(int)");
	OspRegCommand("umspoll", (void*)umspoll, "umspoll(int)");
	OspRegCommand("umsdis", (void*)umsdis, "umsdis(int)");
	OspRegCommand("umsview", (void*)umsview, "umsview(int)");	
	OspRegCommand("umsrollcall", (void*)umsrollcall, "umsrollcall");
	OspRegCommand("umsaudmix", (void*)umsaudmix, "umsaudmix");
	OspRegCommand("umsgetstream", (void*)umsgetstream, "umsgetstream");
	OspRegCommand("umsshowmcu", (void*)umsshowmcu, "umsshowmcu");
	OspRegCommand("getmcuspy", (void*)getmcuspy, "getmcuspy");
	// end instdump

	OspRegCommand("showumsreg", (void*)showumsreg, "showumsreg()");
	OspRegCommand("showscrnum", (void*)showscrnum, "showscrnum()");
	OspRegCommand("showlicenum", (void*)showlicenum, "showlicenum()");

	// 以下命令用于开发本地调试使用

	OspRegCommand("callcon", (void*)callcon, "callcon(int)");
	OspRegCommand("chancon", (void*)chancon, "chancon(int)");
	OspRegCommand("calldiscon", (void*)calldiscon, "calldiscon(int)");
	OspRegCommand("setpolltime", (void*)setpolltime, "setpolltime(int)");

	OspRegCommand("stopconf", (void*)stopconf, "stopconf(int)");
	OspRegCommand("callep", (void*)callep, "callep(int)");

	OspRegCommand("callepid", (void*)callepid, "callepid(int)");
	
	OspRegCommand("dropep", (void*)dropep, "dropep(int)");
	OspRegCommand("changespeaker", (void*)changespeaker, "changespeaker(int, int)");
	OspRegCommand("cnsfeccep", (void*)cnsfeccep, "cnsfeccep");
	OspRegCommand("changeseat", (void*)changeseat, "changeseat(int, int, int)");
	
	OspRegCommand("nodeupdate", (void*)nodeupdate, "nodeupdate(int)");
	OspRegCommand("startpoll", (void*)startpoll, "startpoll(int)");
	OspRegCommand("stoppoll", (void*)stoppoll, "stoppoll(int)");
	OspRegCommand("suspendpoll", (void*)suspendpoll, "suspendpoll(int)");
	OspRegCommand("viewobj", (void*)viewobj, "viewobj(int)");
	OspRegCommand("unviewobj", (void*)unviewobj, "unviewobj(int)");
	OspRegCommand("startdual", (void*)startdual, "startdual(int)");
	OspRegCommand("stopdual", (void*)stopdual, "stopdual(int)");
	
	//->umscall
	OspRegCommand("mixpower", (void*)mixpower, "mixpower");
	OspRegCommand("mkall", (void*)mkall, "mkall(u16 confid, u16 encryptmodel)");
	OspRegCommand("dis", (void*)dis, "dis(u16)");
	OspRegCommand("disadd", (void*)disadd, "disadd(u16)");
	OspRegCommand("disdel", (void*)disdel, "disdel(u16)");

	OspRegCommand("adjframe", (void*)adjframe, "adjframe(u16)");
	OspRegCommand("adjres", (void*)adjres, "adjres(u16)");

	OspRegCommand("setscrnum", (void*)setscrnum, "setscrnum(u32 dwSetNum)");
	OspRegCommand("setlicenum", (void*)setlicenum, "setlicenum(u32 dwNum)");

	OspRegCommand("settime", (void*)settime, "settime(u32 dwTime)");
	OspRegCommand("showtime", (void*)showtime, "showtime()");

	OspRegCommand("startvmp", (void*)startvmp, "startvmp(int)");
	
	OspRegCommand("bastest", (void*)bastest, "bastest(int)");

	OspRegCommand("selview", (void*)selview, "selview(int)");
	OspRegCommand("unselview", (void*)unselview, "unselview(int)");

	OspRegCommand("brdvmp", (void*)brdvmp, "brdvmp(int)");
	OspRegCommand("unbrdvmp", (void*)unbrdvmp, "unbrdvmp(int)");

	OspRegCommand("savecncvmp", (void*)savecncvmp, "savecncvmp(int)");

	OspRegCommand("hduplay", (void*)hduplay, "hduplay(u16 wConfid, u16 wDstep, BOOL32 bVmp, u16 wIndex, u16 wSubIndex = 0)");
	OspRegCommand("hdustop", (void*)hdustop, "hdustop(u16 wConfid, u16 wDstep, BOOL32 bVmp, u16 wIndex, u16 wSubIndex = 0)");
	OspRegCommand("hdustopall", (void*)hdustopall, "hdustopall(u16 wConfID, u16 wEpID)");
	OspRegCommand("hdusetvol", (void*)hdusetvol, "hdusetvol(u16 wConfID, u16 wEpID, u16 wVol, u16 wMute, u16 wIndex, u16 wSubIndex = 0)");
	OspRegCommand("hduchangemode", (void*)hduchangemode, "hduchangemode(u16 wConfID, u16 wEpID, u16 wIndex, u16 wMode)");


    OspRegCommand("qtaliasdata", (void*)qtaliasdata, "qtaliasdata(void)");
	OspRegCommand("mkallbp", (void*)mkallbp, "mkallbp(u16 confid, u16 encryptmodel)");

#endif
}



