#include "vidbaseqp.h"
#include "innereventxmpubas.h"
#include "umsxmpuinst.h"
#include "xmpuinterface.h"
#include  <map>

#define	 XMPU_BAS_MAX_PORT_SPAN		100		//每个适配通道最大使用250个端口
#define  XMPU_BAS_MAX_DEC_PORT_SPAN	10			//解码和编码间隔100
extern std::map<u32,u32> g_mapBas; 
CVidBasEqpHandle::CVidBasEqpHandle( CUmsXmpuInst* pInst )
	:CEqpBaseHandle(pInst)
{

}

CVidBasEqpHandle::~CVidBasEqpHandle()
{

}

void CVidBasEqpHandle::Init()
{
	u16 wIndex = 0;
	for(wIndex = 0; wIndex < XMPU_MAX_BAS_NUM; ++wIndex)
	{
		m_atBasChn[wIndex].Clear();
		m_atBasChn[wIndex].m_dwEqpID = XMPU_EQP_ID_BAS_BEG + wIndex;
	}
	m_wVidBasUsedNum = 0;
}

BOOL32 CVidBasEqpHandle::Handle( CTpMsg *const ptMsg )
{
	BOOL32 bRes = TRUE;
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();

	switch(wEvent)
	{
	case evXmpu_StartVidBas_Rsp:
		{
			OnStartBasRsp(ptMsg);
			break;
		}
	case evXmpu_SetBasEncParam_Req:
		{
			OnSetBasEncParamReq(ptMsg);
			break;
		}
	case evXmpu_SetBasEncParam_Rsp:
		{
			OnSetBasEncParamRsp(ptMsg);
			break;
		}
	case evXmpu_AskBasKey_Req:
		{
			OnXmpuBasAskKey(ptMsg);
			break;
		}
	case evUms_XmpuAskBasKey_Req:
		{
			OnUmsBasAskKey(ptMsg);
			break;
		}
	case evXmpu_BasDisConnect_Nty:
		{
			OnBasDisConnect(ptMsg);
			break;
		}
	default:
		{
			bRes = FALSE;
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		}
		break;
	}
	return bRes;
}

BOOL32 CVidBasEqpHandle::AssignEqpEx( TXmpuEqpParam* ptEqpParam )
{
	CHECK_XMPU_SEM;

	TXmpuBasChn* ptChn = FindIdleBasMdl();
	if (NULL == ptChn)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::AssignEqpEx.has full base!\n"));
		return FALSE;
	}

	TXmpuBasParam* ptParam = (TXmpuBasParam*)ptEqpParam;
	//状态检测
	if ( ptChn->m_emStat != XmpuEqpStat_Idle)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::AssignEqpEx. bas state error m_byEqpID:%d CurrStat:%s\n", 
			ptChn->m_dwEqpID, GetXmpuEqpStatBuf(ptChn->m_emStat)));	
		return FALSE;
	}
	
	ptChn->m_wConfID = ptParam->m_wConfID;
	ptChn->m_dwMediaIP = ptParam->m_dwMediaIp;
	ptChn->m_emStat = XmpuEqpStat_Starting;
	//初始化端口 10600~17000 每个适配器分配100个端口 解码和编码间隔10
	ptChn->m_wUmsRcvStartPort = XMPU_BAS_BEGIN_PORT + (ptChn->m_dwEqpID - XMPU_EQP_ID_BAS_BEG)*XMPU_BAS_MAX_PORT_SPAN;
	AdjustAddr(ptChn);
	// 出参
	ptParam->m_ptEqp->m_dwEqpID = ptChn->m_dwEqpID;
	memcpy(&ptParam->m_tDecMiddleRtpAddr, &ptChn->m_tDecMiddleRtpAddr, sizeof(ptChn->m_tDecMiddleRtpAddr));
	memcpy(&ptParam->m_tDecRtcpAddr, &ptChn->m_tDecRtcpAddr, sizeof(ptChn->m_tDecRtcpAddr));
	memcpy(ptParam->m_atEncRtpAddr, ptChn->m_atEncRtpAddr, sizeof(ptChn->m_atEncRtpAddr));
	memcpy(ptParam->m_atEncMiddleRtcpAddr, ptChn->m_atEncMiddleRtcpAddr, sizeof(ptChn->m_atEncMiddleRtcpAddr));

	MdlHint(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::AssignEqpEx. dwEqpID:%d, wConfID:%d,  DsIP:"TPIPFORMAT", stat:%s\n",
			ptChn->m_dwEqpID,  ptChn->m_wConfID, Tpu32ToIP(ptChn->m_dwMediaIP),
			GetXmpuEqpStatBuf(ptChn->m_emStat)));

	if (!MediaStartBase(ptChn->m_dwHandle, ptChn->m_dwEqpID, *ptParam))
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::AssignEqpEx. Start Video Bas error!\n"));	
		ptChn->Clear();
		return FALSE;
	}
	++m_wVidBasUsedNum ; //VBas 数量
	return TRUE;
}

BOOL32 CVidBasEqpHandle::ReleaseEqpEx( TXmpuEqpParam* ptEqpParam )
{
	CHECK_XMPU_SEM;
	TXmpuBasChn* ptChn = FindBasChnMdl(ptEqpParam->m_ptEqp->m_dwEqpID);
	if ( NULL == ptChn )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::ReleaseEqpEx. ptVidBasMdl Is NULL! wEqpID:%d\n", ptEqpParam->m_ptEqp->m_dwEqpID));
		return FALSE;
	}

	//状态检测
	if ( ptChn->m_emStat != XmpuEqpStat_Starting && ptChn->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::ReleaseEqpEx.Vid bas state error m_byEqpID:%d CurrStat:%s\n", 
			ptChn->m_dwEqpID, GetXmpuEqpStatBuf(ptChn->m_emStat)));	
		return FALSE;
	}

	MediaReleaseBase(ptChn->m_dwHandle);

	MdlHint(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::ReleaseEqpEx. ConfID:%d, wEqpID:%d, Stat:%s\n", 
		ptChn->m_wConfID, ptChn->m_dwEqpID, GetXmpuEqpStatBuf(ptChn->m_emStat)));

	ptChn->Clear();
	if (m_wVidBasUsedNum)
	{
		-- m_wVidBasUsedNum ;
	}
	return TRUE;
}

void CVidBasEqpHandle::OnXmpuBasAskKey( CTpMsg *const ptMsg )
{
	u32 dwEqpID;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuBasChn* ptChn = FindBasChnMdl(dwEqpID);
	if ( NULL == ptChn )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnXmpuBasAskKey. ptVBasMdl Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if ( !ptChn->m_dwHandle)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnXmpuBasAskKey. VBasHandle Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if ( !ptChn->m_tKeyFrameStatisToEqp.CheckFrameStatis() )
	{
		return ;
	}

	MdlLowDtl(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnXmpuBasAskKey. FastUpdate To Eqp! wConfID:%d, EqpID:%d, ChanIndx:%d\n", 
		ptChn->m_wConfID, dwEqpID));

	SendMsgToCall(ptChn->m_wConfID, evXmpu_AskBasKey_Req, &dwEqpID, sizeof(dwEqpID));

}

void CVidBasEqpHandle::OnUmsBasAskKey( CTpMsg *const ptMsg )
{
	u32 dwEqpID;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuBasChn* ptChn = FindBasChnMdl(dwEqpID);
	if ( NULL == ptChn )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnUmsBasAskKey. ptVBasMdl Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if ( !ptChn->m_dwHandle)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnUmsBasAskKey. VBasHandle Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if ( !ptChn->m_tKeyFrameStatisToEqp.CheckFrameStatis() )
	{
		return ;
	}

	MdlLowDtl(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnUmsBasAskKey. FastUpdate To Eqp! wConfID:%d, EqpID:%d,\n", 
		ptChn->m_wConfID, ptChn->m_dwEqpID));

	for (u8 byIndex =0 ;byIndex < ptChn->m_byEncChnNum; ++byIndex )
	{
		MediaReqBasIFrame(ptChn->m_dwHandle, byIndex);
	}
	
}

void CVidBasEqpHandle::OnStartBasRsp( CTpMsg *const ptMsg )
{
	TXmpuStartBasRsp tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. dwEqpID:%d, Handle:%d, Res:%d, IDNum:%d, bValidI:(%d|%d|%d)\n", 
		tRes.m_dwEqpID, tRes.m_dwHandle, tRes.m_emRes, tRes.m_byChnNum, 
		tRes.m_abVaildChn[0], tRes.m_abVaildChn[1], tRes.m_abVaildChn[2]));

	BOOL32 bRes = TRUE;
	TXmpuBasChn* ptChn = NULL;
	CHECK_XMPU_SEM;
	do 
	{
		ptChn = FindBasChnMdl(tRes.m_dwEqpID);
		if ( NULL == ptChn )
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. ptVBasMdl Is NULL! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			MediaReleaseBase(tRes.m_dwHandle);
			return ;
		}

		if (tRes.m_emRes != StartBasRsp_Success)
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. start bas error! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		if (ptChn->m_emStat != XmpuEqpStat_Starting && ptChn->m_emStat != XmpuEqpStat_Running)
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. bas state error! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		ptChn->m_emStat = XmpuEqpStat_Running;
		ptChn->m_byEncChnNum = tRes.m_byChnNum;
		memcpy(ptChn->m_abVaildChn, tRes.m_abVaildChn, sizeof(u8)*tRes.m_byChnNum);
		//解码通道
		if (!MediaSetBasDecAddr(ptChn->m_dwHandle, ptChn->m_tDecRtcpAddr))
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. Set VBas DecRtcp error!\n"));
			bRes = FALSE;
			break;
		}

		if (!MediaGetBasDecAddr(ptChn->m_dwHandle,ptChn->m_tDecRtpAddr))
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. Get VBas DecRtp error!\n"));
			bRes = FALSE;
			break;
		}

		// 编码通道
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < ptChn->m_byEncChnNum; ++wIndex)
		{
			if (!MediaSetBasEncAddr(ptChn->m_dwHandle, wIndex, ptChn->m_atEncRtpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. Set VBas EncRtp error: windex%d\n", wIndex));
				bRes = FALSE;
				break;
			}

			if (!MediaGetBasEncAddr(ptChn->m_dwHandle, wIndex, ptChn->m_atEncRtcpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnStartBasRsp. Get VBas EecRtcp error: windex%d\n", wIndex));
				bRes = FALSE;
				break;
			}
		}
	} while (0);

	TXmpuStartBasNty tNty;
	tNty.m_dwEqpID = ptChn->m_dwEqpID;
	tNty.m_bSuccess = bRes;
	tNty.m_byEncNum = ptChn->m_byEncChnNum;
	tNty.m_tDecRtpAddr.SetAddr(ptChn->m_tDecRtpAddr.GetIP(), ptChn->m_tDecRtpAddr.GetPort());
	memcpy(tNty.m_atEncRtcpAddr,  ptChn->m_atEncRtcpAddr, sizeof(tNty.m_atEncRtcpAddr));
	SendMsgToCall(ptChn->m_wConfID, evXmpu_UmsStartVidBas_Nty, &tNty, sizeof(tNty));

	if (FALSE == bRes)
	{
		MediaReleaseBase(tRes.m_dwHandle);
		ptChn->Clear();
		if (m_wVidBasUsedNum)
		{
			-- m_wVidBasUsedNum ;
		}
	}
}

void CVidBasEqpHandle::OnSetBasEncParamReq( CTpMsg *const ptMsg )
{
	TXmpuChgBasInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuBasChn* ptBasChn = FindBasChnMdl(tInfo.m_dwEqpID);
	if ( NULL == ptBasChn )
	{
		MdlError(Ums_Mdl_Eqp, ("CVidBasEqpHandle::OnSetBasEncParamReq, not Find EqpID! dwEqpID:%d\n", tInfo.m_dwEqpID));
		return ;
	}

	//状态检测
	if ( ptBasChn->m_emStat != XmpuEqpStat_Starting && ptBasChn->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Eqp, ("CVidBasEqpHandle::OnSetBasEncParamReq. ConfID:%d, wEqpID:%d, CurrStat:%s\n", 
			ptBasChn->m_wConfID, ptBasChn->m_dwEqpID, GetXmpuEqpStatBuf(ptBasChn->m_emStat)));	
		return ;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnSetBasEncParamReq  EqpID:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s,!\n",
		ptBasChn->m_dwEqpID, ptBasChn->m_wConfID, Tpu32ToIP(ptBasChn->m_dwMediaIP), 
		ptBasChn->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptBasChn->m_emStat)));

	MediaSetBasParam(ptBasChn->m_dwHandle, tInfo);
}

void CVidBasEqpHandle::OnSetBasEncParamRsp( CTpMsg *const ptMsg )
{
	TXmpuSetBasEncRsp tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnSetBasEncParamRsp. dwEqpID:%d, Handle:%d, Res:%d, IDNum:%d, ID:(%d|%d|%d)\n", 
		tRes.m_dwEqpID, tRes.m_dwHandle, tRes.m_emRes, tRes.m_byChnNum, 
		tRes.m_abVaildChn[0], tRes.m_abVaildChn[1], tRes.m_abVaildChn[2]));

	BOOL32 bRes = TRUE;
	TXmpuBasChn* ptChn = NULL;
	CHECK_XMPU_SEM;
	do 
	{
		ptChn = FindBasChnMdl(tRes.m_dwEqpID);
		if ( NULL == ptChn )
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnSetBasEncParamRsp. ptVBasMdl Is NULL! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		if (tRes.m_emRes != StartBasRsp_Success)
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnSetBasEncParamRsp. start bas error! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		if (ptChn->m_emStat != XmpuEqpStat_Starting && ptChn->m_emStat != XmpuEqpStat_Running)
		{
			MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnSetBasEncParamRsp. bas state error! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		ptChn->m_emStat = XmpuEqpStat_Running;
		ptChn->m_byEncChnNum = tRes.m_byChnNum;
		memcpy(ptChn->m_abVaildChn, tRes.m_abVaildChn, sizeof(u8)*tRes.m_byChnNum);

	} while (0);

	if (NULL == ptChn )
	{
		MediaReleaseBase(tRes.m_dwHandle);
		return ;
	}

	TXmpuSetBasEncNty tNty;
	tNty.m_dwEqpID = tRes.m_dwEqpID;
	tNty.m_dwHandle = tRes.m_dwHandle;
	tNty.m_byChnNum = tRes.m_byChnNum;
	memcpy(tNty.m_abVaildChn, tRes.m_abVaildChn, sizeof(tNty.m_abVaildChn));

	SendMsgToCall(ptChn->m_wConfID, evXmpu_SetBasEncParam_Nty, &tNty, sizeof(tNty));
}

void CVidBasEqpHandle::AdjustAddr( TXmpuBasChn* ptChn )
{
	u16 wPort = ptChn->m_wUmsRcvStartPort;
	ptChn->m_tDecMiddleRtpAddr.SetAddr(ptChn->m_dwMediaIP, wPort);
	// 中转地址 
	wPort +=5;
	ptChn->m_tDecRtcpAddr.SetAddr(ptChn->m_dwMediaIP, wPort);

	// 编码通道
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; ++wIndex)
	{
		wPort = ptChn->m_wUmsRcvStartPort + XMPU_BAS_MAX_DEC_PORT_SPAN + wIndex*UMS_MCU_PORT_PORTSPAN;
		ptChn->m_atEncRtpAddr[wIndex].SetAddr(ptChn->m_dwMediaIP,wPort);

		wPort+=5;
		ptChn->m_atEncMiddleRtcpAddr[wIndex].SetAddr(ptChn->m_dwMediaIP,wPort);
	}
}

void CVidBasEqpHandle::OnBasDisConnect( CTpMsg *const ptMsg )
{
	u32	dwEqpID = 0;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuBasChn* ptVmpMdl = FindBasChnMdl(dwEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVidBasEqpHandle::OnBasDisConnect. ptVBasMdl Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if (ptVmpMdl->m_emStat == XmpuEqpStat_Starting || ptVmpMdl->m_emStat == XmpuEqpStat_Running)
	{
		SendMsgToCall(ptVmpMdl->m_wConfID, evXmpu_BasDisConnect_Nty, &dwEqpID, sizeof(dwEqpID));
	}

	MdlHint(Ums_Mdl_Eqp, ("CVidBasEqpHandle::OnBasDisConnect. FastUpdate To Eqp! wConfID:%d, EqpID:%d\n", 
		ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID));

	g_mapBas.erase(ptVmpMdl->m_dwHandle);
	ptVmpMdl->Clear();
	
	if (m_wVidBasUsedNum)
	{
		-- m_wVidBasUsedNum ;
	}
}

BOOL32 CVidBasEqpHandle::StopConf( u16 wConfID )
{
	for(u16 wIndex = 0; wIndex < XMPU_MAX_BAS_NUM; ++wIndex)
	{
		if (m_atBasChn[wIndex].m_wConfID == wConfID)
		{
			if (!m_atBasChn[wIndex].m_dwHandle)
			{
				MediaReleaseBase(m_atBasChn[wIndex].m_dwHandle);
			}

			m_atBasChn[wIndex].Clear();
		}
	}
	return TRUE;
}

void CVidBasEqpHandle::SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen )
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

TXmpuBasChn* CVidBasEqpHandle::FindIdleBasMdl()
{
	for (u16 wIndex = 0; wIndex < XMPU_MAX_BAS_NUM;++wIndex)
	{
		if (m_atBasChn[wIndex].m_emStat == XmpuEqpStat_Idle)
		{
			return &m_atBasChn[wIndex];
		}

	}
	return NULL;

}

TXmpuBasChn* CVidBasEqpHandle::FindBasChnMdl( u8 byEqpId )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_BAS_NUM;++wMdlIndex)
	{
		if ( m_atBasChn[wMdlIndex].m_dwEqpID == byEqpId )
		{
			return &m_atBasChn[wMdlIndex];
		}
	}

	return NULL;
}

void CVidBasEqpHandle::ShowAll()
{
	msgprintnotime("VidBas Info : \n");
	TXmpuBasChn* ptChn = NULL;

	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_BAS_NUM; ++wMdlIndex)
	{
		ptChn = &m_atBasChn[wMdlIndex];
		msgprintnotime("	Index:%d, EqpID:%d, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s\n",
			wMdlIndex, ptChn->m_dwEqpID, ptChn->m_dwHandle, ptChn->m_wConfID,Tpu32ToIP(ptChn->m_dwMediaIP), 
			ptChn->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptChn->m_emStat));

		u16 wIndex = 0;
 		msgprintnotime("		DeccMiddleRtp (IP:"TPIPFORMAT" Port:%d), DecRtp (IP:"TPIPFORMAT" Port:%d), DecRtcp (IP:"TPIPFORMAT" Port:%d) \n", 
				Tpu32ToIP(ptChn->m_tDecMiddleRtpAddr.m_dwIP), ptChn->m_tDecMiddleRtpAddr.m_wPort,
				Tpu32ToIP(ptChn->m_tDecRtpAddr.m_dwIP), ptChn->m_tDecRtpAddr.m_wPort, 
				Tpu32ToIP(ptChn->m_tDecRtcpAddr.m_dwIP), ptChn->m_tDecRtcpAddr.m_wPort);
		msgprintnotime("		EncInfo: byEncNum: %d\n", ptChn->m_byEncChnNum );
		for (wIndex = 0; wIndex < ptChn->m_byEncChnNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d, bValid%d EncRtp(IP:"TPIPFORMAT" Port:%d), EncMiddle(IP:"TPIPFORMAT" Port:%d), EncRtcp (IP:"TPIPFORMAT" Port:%d) \n", 
				wIndex, ptChn->m_abVaildChn[wIndex], 
				Tpu32ToIP(ptChn->m_atEncRtpAddr[wIndex].m_dwIP), ptChn->m_atEncRtpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptChn->m_atEncMiddleRtcpAddr[wIndex].m_dwIP), ptChn->m_atEncMiddleRtcpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptChn->m_atEncRtcpAddr[wIndex].m_dwIP), ptChn->m_atEncRtcpAddr[wIndex].m_wPort);

		}
	}
}

void CVidBasEqpHandle::Show()
{
	msgprintnotime("VidBas Info : \n");
	TXmpuBasChn* ptChn = NULL;

	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_BAS_NUM; ++wMdlIndex)
	{
		ptChn = &m_atBasChn[wMdlIndex];
		if (ptChn->m_emStat == XmpuEqpStat_Idle)
		{
			continue;
		}

		msgprintnotime("	Index:%d, EqpID:%d, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s\n",
			wMdlIndex, ptChn->m_dwEqpID, ptChn->m_dwHandle, ptChn->m_wConfID,Tpu32ToIP(ptChn->m_dwMediaIP), 
			ptChn->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptChn->m_emStat));

		u16 wIndex = 0;
		msgprintnotime("		DeccMiddleRtp (IP:"TPIPFORMAT" Port:%d), DecRtp (IP:"TPIPFORMAT" Port:%d), DecRtcp (IP:"TPIPFORMAT" Port:%d) \n", 
			Tpu32ToIP(ptChn->m_tDecMiddleRtpAddr.m_dwIP), ptChn->m_tDecMiddleRtpAddr.m_wPort,
			Tpu32ToIP(ptChn->m_tDecRtpAddr.m_dwIP), ptChn->m_tDecRtpAddr.m_wPort, 
			Tpu32ToIP(ptChn->m_tDecRtcpAddr.m_dwIP), ptChn->m_tDecRtcpAddr.m_wPort);
		msgprintnotime("		EncInfo: byEncNum: %d\n", ptChn->m_byEncChnNum );
		for (wIndex = 0; wIndex < ptChn->m_byEncChnNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d, bValid%d EncRtp(IP:"TPIPFORMAT" Port:%d), EncMiddle(IP:"TPIPFORMAT" Port:%d), EncRtcp (IP:"TPIPFORMAT" Port:%d) \n", 
				wIndex, ptChn->m_abVaildChn[wIndex], 
				Tpu32ToIP(ptChn->m_atEncRtpAddr[wIndex].m_dwIP), ptChn->m_atEncRtpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptChn->m_atEncMiddleRtcpAddr[wIndex].m_dwIP), ptChn->m_atEncMiddleRtcpAddr[wIndex].m_wPort, 
				Tpu32ToIP(ptChn->m_atEncRtcpAddr[wIndex].m_dwIP), ptChn->m_atEncRtcpAddr[wIndex].m_wPort);
		}
	}
}
