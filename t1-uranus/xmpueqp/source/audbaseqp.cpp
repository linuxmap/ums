#include "audbaseqp.h"
#include "innereventxmpuaudbas.h"
#include "umsxmpuinst.h"
#include "xmpuinterface.h"
#include "umsinnertype.h"
#include "umsapi.h"
#include <map>

#define XMPU_AUD_BAS_MAX_PORT_SPAN		40		//每个合成器使用40个端口
#define  XMPU_AUD_BAS_MAX_DEC_PORT_SPAN	10			//解码和编码间隔10
extern std::map<u32,u32> g_mapBas; 
CAudioBasEqpHandle::CAudioBasEqpHandle( CUmsXmpuInst* pInst )
	:CEqpBaseHandle(pInst)
{

}

CAudioBasEqpHandle::~CAudioBasEqpHandle()
{

}

void CAudioBasEqpHandle::Init()
{
	u16 wIndex = 0;
	for (wIndex = 0;wIndex < XMPU_AUD_BAS_MAX_CHN; ++wIndex)
	{
		m_atAudModle[wIndex].Clear();
		m_atAudModle[wIndex].m_dwEqpID = XMPU_EQP_ID_AUD_BAS_BEG + wIndex;
	}
	m_wAudBasUsedNum = 0;
}

BOOL32 CAudioBasEqpHandle::Handle( CTpMsg *const ptMsg )
{
	BOOL32 bRes = TRUE;
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();

	switch(wEvent)
	{
	case evXmpu_StartAudBas_Rsp:
		{
			OnStartAudBasRsp(ptMsg);
			break;
		}
	case evXmpu_AudBasSetSyn_Req:
		{
			OnSetAudBasSynReq(ptMsg);
			break;
		}
	case evXmpu_SetAudBasParam_Req:
		{
			OnSetAudBasParamReq(ptMsg);
			break;
		}
	case evXmpu_SetAudBasParam_Rsp:
		{
			OnSetAudBasParamRsp(ptMsg);
			break;
		}
	case evXmpu_AudBasDisConnect_Nty:
		{
			OnAudBasDisConnect(ptMsg);
			break;
		}
	default:
		{
			bRes = FALSE;
			break;
		}
	}
	return bRes;
}

BOOL32 CAudioBasEqpHandle::AssignEqpEx( TXmpuEqpParam* ptEqpParam )
{
	CHECK_XMPU_SEM;
	
	TXmpuAudBasModle* ptModle = FindIdleAudBasModle();
	if (NULL == ptModle)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::AssignEqpEx.has full base!\n"));
		return FALSE;
	}
	//状态检测
	if ( ptModle->m_emStat != XmpuEqpStat_Idle)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::AssignEqpEx. state error m_byEqpID:%d CurrStat:%s\n", 
			ptModle->m_dwEqpID, GetXmpuEqpStatBuf(ptModle->m_emStat)));	
		return FALSE;
	}
	TXmpuAudBasParam* ptParam = (TXmpuAudBasParam*)ptEqpParam;
	ptModle->m_wConfID = ptParam->m_wConfID;
	ptModle->m_dwMediaIP = ptParam->m_dwMediaIP;
	ptModle->m_emStat = XmpuEqpStat_Starting;
	ptModle->m_emDecFormat = ptParam->m_tAudDec.m_emFormat;
	for (u16 wIndex = 0; wIndex < AUD_BAS_MAX_OUT_CHNL_NUM; ++wIndex)
	{
		ptModle->m_aemEncFormat[wIndex] = ptParam->m_atAudEnc[wIndex].m_emFormat;
	}
	//  35000~39480 每个适配器占用30个，16*7个适配器，共占用4480     
	ptModle->m_wUmsRcvStartPort = XMPU_AUD_BAS_BEGIN_PORT + 
					(ptModle->m_dwEqpID - XMPU_EQP_ID_AUD_BAS_BEG)*XMPU_AUD_BAS_MAX_PORT_SPAN;
	AdjustAddr(ptModle);

	u8 byNum = 0;
	for(byNum = 0; byNum < AUD_BAS_MAX_OUT_CHNL_NUM; ++byNum)
	{
		if (ptParam->m_atAudEnc[byNum].m_emFormat == emTPAEnd)
		{
			break;
		}
	}
	ptModle->m_byEncNum = byNum;

	// 以下为出参
	ptParam->m_ptEqp->m_dwEqpID = ptModle->m_dwEqpID;
	memcpy(&ptParam->m_tDecMiddleRtpAddr, &ptModle->m_tDecMiddleRtpAddr, sizeof(ptModle->m_tDecMiddleRtpAddr));
	memcpy(&ptParam->m_tDecRtcpAddr, &ptModle->m_tDecRtcpAddr, sizeof(ptModle->m_tDecRtcpAddr));
	memcpy(ptParam->m_atEncRtpAddr, ptModle->m_atEncRtpAddr, sizeof(ptModle->m_atEncRtpAddr));
	memcpy(ptParam->m_atEncMiddleRtcpAddr, ptModle->m_atEncMiddleRtcpAddr, sizeof(ptModle->m_atEncMiddleRtcpAddr));

	MdlHint(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::AssignEqpEx  EqpID:%d, ConfID:%d, EncNum:%d DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s!\n",
		ptModle->m_dwEqpID, ptModle->m_wConfID, ptModle->m_byEncNum, Tpu32ToIP(ptModle->m_dwMediaIP), 
		ptModle->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptModle->m_emStat)));

	if (!MediaStartAudBas(ptModle->m_dwHandle, ptModle->m_dwEqpID, *ptParam))
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::AssignEqpEx. start Aud Bas error!\n"));	
		ptModle->Clear();
		return FALSE;
	}
	++m_wAudBasUsedNum; //音配适配使用数量加1
	return TRUE;

}

BOOL32 CAudioBasEqpHandle::ReleaseEqpEx( TXmpuEqpParam* ptEqpParam )
{
	CHECK_XMPU_SEM;
	TXmpuAudBasModle* ptAudMdl = FindAudBasModle(ptEqpParam->m_ptEqp->m_dwEqpID);
	if ( NULL == ptAudMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::ReleaseEqpEx. ptAudMdl Is NULL! wEqpID:%d\n", ptEqpParam->m_ptEqp->m_dwEqpID));
		return FALSE;
	}

	//状态检测
	if ( ptAudMdl->m_emStat != XmpuEqpStat_Starting && ptAudMdl->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::ReleaseEqpEx.Aud Bas state error m_byEqpID:%d CurrStat:%s\n", 
			ptAudMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptAudMdl->m_emStat)));	
		return FALSE;
	}

	MediaReleaseBase(ptAudMdl->m_dwHandle);

	MdlHint(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::ReleaseEqpEx. ConfID:%d, wEqpID:%d, Stat:%s,\n", 
		ptAudMdl->m_wConfID, ptAudMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptAudMdl->m_emStat)));

	ptAudMdl->Clear();
	if (m_wAudBasUsedNum)
	{
		--m_wAudBasUsedNum; 
	}
	return TRUE;
}

TXmpuAudBasModle* CAudioBasEqpHandle::FindIdleAudBasModle()
{
	u16 wIndex = 0;
	for(wIndex = 0 ;wIndex < XMPU_AUD_BAS_MAX_CHN; ++wIndex)
	{
		if (m_atAudModle[wIndex].m_emStat == XmpuEqpStat_Idle)
		{
			return &m_atAudModle[wIndex];
		}
	}
	return NULL;
}

TXmpuAudBasModle* CAudioBasEqpHandle::FindAudBasModle( u32 dwEqpID )
{
	u16 wIndex = 0;
	for(wIndex = 0 ;wIndex < XMPU_AUD_BAS_MAX_CHN; ++wIndex)
	{
		if (m_atAudModle[wIndex].m_dwEqpID == dwEqpID)
		{
			return &m_atAudModle[wIndex];
		}
	}
	return NULL;
}

void CAudioBasEqpHandle::OnStartAudBasRsp( CTpMsg *const ptMsg )
{
	TXmpuStartAudBasRsp tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnStartAudBasRsp. dwEqpID:%d, Handle:%d, Res:%d, IDNum:%d, bValidI:(%d|%d|%d)\n", 
		tRes.m_dwEqpID, tRes.m_dwHandle, tRes.m_emRes, tRes.m_byChnNum, 
		tRes.m_abVaildChn[0], tRes.m_abVaildChn[1], tRes.m_abVaildChn[2]));

	BOOL32 bRes = TRUE;
	CHECK_XMPU_SEM;
	TXmpuAudBasModle* ptAudMdl = FindAudBasModle(tRes.m_dwEqpID);
	if ( NULL == ptAudMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnStartAudBasRsp. ptABasMdl Is NULL! wEqpID:%d\n", tRes.m_dwEqpID));	
		return;
	}
	do 
	{
		if (ptAudMdl->m_emStat != XmpuEqpStat_Starting && ptAudMdl->m_emStat != XmpuEqpStat_Running)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnStartAudBasRsp. Stat error!EqpID:%d, Stat:%s\n",
																		ptAudMdl->m_dwEqpID,GetXmpuEqpStatBuf(ptAudMdl->m_emStat)));
			bRes = FALSE;
			break;
		}
		if (!MediaSetAudBasDecAddr(ptAudMdl->m_dwHandle, ptAudMdl->m_tDecRtcpAddr) ||
			!MediaGetAudBasDecAddr(ptAudMdl->m_dwHandle, ptAudMdl->m_tDecRtpAddr))
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnStartAudBasRsp. Get or Set Dec rtcp error!\n"));
			bRes = FALSE;
			break;
		}

		for(u16 wIndex = 0; wIndex < ptAudMdl->m_byEncNum; ++wIndex)
		{
			if (!MediaSetAudBasEncAddr(ptAudMdl->m_dwHandle, wIndex, ptAudMdl->m_atEncRtpAddr[wIndex]) ||
			 !MediaGetAudBasEncAddr(ptAudMdl->m_dwHandle, wIndex, ptAudMdl->m_atEncRtcpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnStartAudBasRsp. Get or Set  Enc rtcp error!\n"));
				bRes = FALSE;
				break;
			}
		}
	} while (0);
	
	TXmpuStartAudBasNty tNty;
	tNty.m_dwEqpID = ptAudMdl->m_dwEqpID;
	tNty.m_bSuccess = bRes;
	tNty.m_tDecRtpAddr.SetAddr(ptAudMdl->m_tDecRtpAddr.GetIP(), ptAudMdl->m_tDecRtpAddr.GetPort());
	memcpy(tNty.m_atEncRtcpAddr,  ptAudMdl->m_atEncRtcpAddr, sizeof(tNty.m_atEncRtcpAddr));

	SendMsgToCall(ptAudMdl->m_wConfID, evXmpu_UmsStartAudBas_Nty, &tNty, sizeof(tNty));

	if (FALSE == bRes)
	{
		MediaReleaseBase(tRes.m_dwHandle);
		ptAudMdl->Clear();
		if (m_wAudBasUsedNum)
		{
			--m_wAudBasUsedNum; 
		}
	}
}

void CAudioBasEqpHandle::OnSetAudBasSynReq( CTpMsg *const ptMsg )
{
	TXmpuAudBasSynInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasSynReq. SynType:%d wEqpID:(%d|%d|%d)\n",
		tInfo.m_emSynType, tInfo.m_adwEqpID[0], tInfo.m_adwEqpID[1], tInfo.m_adwEqpID[2]));	

	if (tInfo.m_emSynType >= em_Xmpu_SynIndex_End)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasSynReq. synIndexType error:%d\n", tInfo.m_emSynType));	
		return;
	}

	TXmpuAudBasModle* ptModle = NULL;
	TXmpuSynChn		atSynChn[TP_MAX_STREAMNUM];
	u16						wConfID = 0;
	CHECK_XMPU_SEM;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ptModle = FindAudBasModle(tInfo.m_adwEqpID[wIndex]);
		if (NULL == ptModle)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasSynReq. ptABasMdl Is NULL! wEqpID:%d\n", tInfo.m_adwEqpID[wIndex]));	
			continue;
		}

		atSynChn[wIndex].m_dwEqpID = ptModle->m_dwEqpID;
		atSynChn[wIndex].m_dwHandle = ptModle->m_dwHandle;
		wConfID = ptModle->m_wConfID;
	}

	m_pcInst->SetSynID(wConfID, tInfo.m_emSynType, atSynChn);

}

void CAudioBasEqpHandle::OnSetAudBasParamReq( CTpMsg *const ptMsg )
{
	TXmpuChgAudParam tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	CHECK_XMPU_SEM;
	TXmpuAudBasModle* ptAudMdl = FindAudBasModle(tInfo.m_dwEqpID);
	if ( NULL == ptAudMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasParamReq. ptABasMdl Is NULL! wEqpID:%d\n", tInfo.m_dwEqpID));	
		return;
	}

	if (ptAudMdl->m_emStat != XmpuEqpStat_Starting && ptAudMdl->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasParamReq. stat  error!EqpID:%d, Stat:%s\n",
																		ptAudMdl->m_dwEqpID,GetXmpuEqpStatBuf(ptAudMdl->m_emStat)));
		return;
	}

	ptAudMdl->m_emDecFormat = tInfo.m_tAudDec.m_emFormat;

	MdlHint(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasParamReq  EqpID:%d, ConfID:%d, DecFormat:%s,DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s!\n",
		ptAudMdl->m_dwEqpID, ptAudMdl->m_wConfID, UmsAudFormatPrint(ptAudMdl->m_emDecFormat), Tpu32ToIP(ptAudMdl->m_dwMediaIP), 
		ptAudMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptAudMdl->m_emStat)));

	memcpy(tInfo.m_aemEncFormat, ptAudMdl->m_aemEncFormat, sizeof(tInfo.m_aemEncFormat));
	
	MediaSetAudBasParam(ptAudMdl->m_dwHandle, tInfo);
}

void CAudioBasEqpHandle::OnSetAudBasParamRsp( CTpMsg *const ptMsg )
{
	TXmpuSetAudBasRsp tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());
	MdlHint(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasParamRsp. dwEqpID:%d, Handle:%d, Res:%d, IDNum:%d, ID:(%d|%d|%d)\n", 
		tRes.m_dwEqpID, tRes.m_dwHandle, tRes.m_emRes, tRes.m_byChnNum, 
		tRes.m_abVaildChn[0], tRes.m_abVaildChn[1], tRes.m_abVaildChn[2]));

	BOOL32 bRes = TRUE;
	TXmpuAudBasModle* ptModle = NULL;
	CHECK_XMPU_SEM;
	do 
	{
		ptModle = FindAudBasModle(tRes.m_dwEqpID);
		if ( NULL == ptModle )
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasParamRsp. ptABasMdl Is NULL! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		if (tRes.m_emRes != StartBasRsp_Success)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasParamRsp. start bas error! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		if (ptModle->m_emStat != XmpuEqpStat_Starting && ptModle->m_emStat != XmpuEqpStat_Running)
		{
			MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnSetAudBasParamRsp. bas state error! wEqpID:%d, Stat:%s\n",
				                                          tRes.m_dwEqpID, GetXmpuEqpStatBuf(ptModle->m_emStat)));
			bRes = FALSE;
			break;
		}

	} while (0);

	if (NULL == ptModle )
	{
		MediaReleaseBase(tRes.m_dwHandle);
		return ;
	}

	SendMsgToCall(ptModle->m_wConfID, evXmpu_SetAudBasParam_Nty, &bRes, sizeof(bRes));
}

void CAudioBasEqpHandle::OnAudBasDisConnect( CTpMsg *const ptMsg )
{
	u32	dwEqpID = 0;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());
	CHECK_XMPU_SEM;
	TXmpuAudBasModle* ptAudBas = FindAudBasModle(dwEqpID);
	if ( NULL == ptAudBas )
	{
		MdlError(Ums_Mdl_Xmpu, ("CAudioBasEqpHandle::OnAudBasDisConnect, ptABasChn Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if (ptAudBas->m_emStat == XmpuEqpStat_Starting || ptAudBas->m_emStat == XmpuEqpStat_Running)
	{
		SendMsgToCall(ptAudBas->m_wConfID, evXmpu_AudBasDisConnect_Nty, &dwEqpID, sizeof(dwEqpID));
	}

	MdlHint(Ums_Mdl_Eqp, ("CAudioBasEqpHandle::OnAudBasDisConnect. FastUpdate To Eqp! wConfID:%d, EqpID:%d\n", 
		ptAudBas->m_wConfID, ptAudBas->m_dwEqpID));

	g_mapBas.erase(ptAudBas->m_dwHandle);
	ptAudBas->Clear();
	
	if (m_wAudBasUsedNum)
	{
		--m_wAudBasUsedNum; 
	}
}

void CAudioBasEqpHandle::AdjustAddr( TXmpuAudBasModle* ptModle )
{
	u16 wPort = ptModle->m_wUmsRcvStartPort;
	ptModle->m_tDecMiddleRtpAddr.SetAddr(ptModle->m_dwMediaIP, wPort);
	wPort+=5;
	ptModle->m_tDecRtcpAddr.SetAddr(ptModle->m_dwMediaIP, wPort);

	for(u16 wIndex = 0; wIndex < AUD_BAS_MAX_OUT_CHNL_NUM; ++wIndex)
	{
		wPort = ptModle->m_wUmsRcvStartPort +XMPU_AUD_BAS_MAX_DEC_PORT_SPAN + wIndex*UMS_MCU_PORT_PORTSPAN;
		ptModle->m_atEncRtpAddr[wIndex].SetAddr(ptModle->m_dwMediaIP, wPort);
		wPort+=5;
		ptModle->m_atEncMiddleRtcpAddr[wIndex].SetAddr(ptModle->m_dwMediaIP, wPort);
	}
}

BOOL32 CAudioBasEqpHandle::StopConf( u16 wConfID )
{
	for(u16 wIndex = 0; wIndex < XMPU_AUD_BAS_MAX_CHN; ++wIndex)
	{
		if (m_atAudModle[wIndex].m_wConfID == wConfID)
		{
			if (!m_atAudModle[wIndex].m_dwHandle)
			{
				MediaReleaseBase(m_atAudModle[wIndex].m_dwHandle);
			}

			m_atAudModle[wIndex].Clear();
		}
	}
	return TRUE;
}

void CAudioBasEqpHandle::SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen )
{
	if ( wConfID == TP_INVALID_INDEX )
	{
		return ;
	}

	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post( MAKEIID( AID_UMSCONFMGR, wConfID) );
}

void CAudioBasEqpHandle::Show()
{
	msgprintnotime("AudBasEqp Info : \n");
	TXmpuAudBasModle* ptMdl = NULL;
	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_AUD_BAS_MAX_CHN; ++wMdlIndex)
	{
		ptMdl = &m_atAudModle[wMdlIndex];
		if (ptMdl->m_emStat == XmpuEqpStat_Idle)
		{
			continue;
		}

		msgprintnotime("	Index:%d, EqpID:%d, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", UmsStartPort:%d, Stat:%s\n",
			wMdlIndex, ptMdl->m_dwEqpID, ptMdl->m_dwHandle, ptMdl->m_wConfID, Tpu32ToIP(ptMdl->m_dwMediaIP), 
			ptMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptMdl->m_emStat));

		u16 wIndex = 0;
		msgprintnotime("		DecInfo: DecFormat:%s, DecMiddleRtp( IP:"TPIPFORMAT" Port:%d), DecRtp ( IP:"TPIPFORMAT" Port:%d) , DecRtcpAddr ( IP:"TPIPFORMAT" Port:%d)\n",
					UmsAudFormatPrint(ptMdl->m_emDecFormat),
					Tpu32ToIP(ptMdl->m_tDecMiddleRtpAddr.m_dwIP), ptMdl->m_tDecMiddleRtpAddr.m_wPort, 
					Tpu32ToIP(ptMdl->m_tDecRtpAddr.m_dwIP), ptMdl->m_tDecRtpAddr.m_wPort, 
					Tpu32ToIP(ptMdl->m_tDecRtcpAddr.m_dwIP), ptMdl->m_tDecRtcpAddr.m_wPort);
		msgprintnotime("		EncInfo: EncNum:%d\n", ptMdl->m_byEncNum );
		for (wIndex = 0; wIndex < ptMdl->m_byEncNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d ,EncFormat:%s,  EncRtp ( IP:"TPIPFORMAT" Port:%d), EncRtcp ( IP:"TPIPFORMAT" Port:%d),  EncMiddleRtcp ( IP:"TPIPFORMAT" Port:%d)\n", 
				wIndex, UmsAudFormatPrint(ptMdl->m_aemEncFormat[wIndex]),
				Tpu32ToIP(ptMdl->m_atEncRtpAddr[wIndex].m_dwIP), ptMdl->m_atEncRtpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptMdl->m_atEncRtcpAddr[wIndex].m_dwIP), ptMdl->m_atEncRtcpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptMdl->m_atEncMiddleRtcpAddr[wIndex].m_dwIP), ptMdl->m_atEncMiddleRtcpAddr[wIndex].m_wPort);
		}
	}
}

void CAudioBasEqpHandle::ShowAll()
{
	msgprintnotime("AudBasEqp Info : \n");
	TXmpuAudBasModle* ptMdl = NULL;
	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_AUD_BAS_MAX_CHN; ++wMdlIndex)
	{
		ptMdl = &m_atAudModle[wMdlIndex];

		msgprintnotime("	Index:%d, EqpID:%d, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", UmsStartPort:%d, Stat:%s\n",
			wMdlIndex, ptMdl->m_dwEqpID, ptMdl->m_dwHandle, ptMdl->m_wConfID, Tpu32ToIP(ptMdl->m_dwMediaIP), 
			ptMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptMdl->m_emStat));

		u16 wIndex = 0;
		msgprintnotime("		DecInfo: DecFormat:%s, DecMiddleRtp( IP:"TPIPFORMAT" Port:%d), DecRtp ( IP:"TPIPFORMAT" Port:%d) , DecRtcpAddr ( IP:"TPIPFORMAT" Port:%d)\n",
			UmsAudFormatPrint(ptMdl->m_emDecFormat),
			Tpu32ToIP(ptMdl->m_tDecMiddleRtpAddr.m_dwIP), ptMdl->m_tDecMiddleRtpAddr.m_wPort, 
			Tpu32ToIP(ptMdl->m_tDecRtpAddr.m_dwIP), ptMdl->m_tDecRtpAddr.m_wPort, 
			Tpu32ToIP(ptMdl->m_tDecRtcpAddr.m_dwIP), ptMdl->m_tDecRtcpAddr.m_wPort);
		msgprintnotime("		EncInfo: EncNum:%d\n", ptMdl->m_byEncNum );
		for (wIndex = 0; wIndex < ptMdl->m_byEncNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d ,EncFormat:%s,  EncRtp ( IP:"TPIPFORMAT" Port:%d), EncRtcp ( IP:"TPIPFORMAT" Port:%d),  EncMiddleRtcp ( IP:"TPIPFORMAT" Port:%d)\n", 
				wIndex, UmsAudFormatPrint(ptMdl->m_aemEncFormat[wIndex]),
				Tpu32ToIP(ptMdl->m_atEncRtpAddr[wIndex].m_dwIP), ptMdl->m_atEncRtpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptMdl->m_atEncRtcpAddr[wIndex].m_dwIP), ptMdl->m_atEncRtcpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptMdl->m_atEncMiddleRtcpAddr[wIndex].m_dwIP), ptMdl->m_atEncMiddleRtcpAddr[wIndex].m_wPort);
		}
	}
}
