#include "vmpeqp.h"
#include "umsinnerstruct.h"
#include "innereventxmpuvmp.h"
#include "xmpuinterface.h"
#include "umsxmpuinst.h"
#include <map>

#define XMPU_VMP_MAX_PORT_SPAN		250		//每个合成外设最大使用250个端口
#define XMPU_VMP_MAX_DEC_PORT_SPAN	200		//解码和编码间隔200

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif

extern std::map<u32,u32> g_mapVmp; 

// "合成器" GB2312编码
const u8 g_abyVmpAliasNameGB2312[] = {0xBA, 0xCF, 0xB3, 0xC9, 0xC6, 0xF7,0x0};

CVmpEqpHandle::CVmpEqpHandle( CUmsXmpuInst* pInst )
:CEqpBaseHandle(pInst)
{
	
}

CVmpEqpHandle::~CVmpEqpHandle()
{
	
}

u32 GetVmpEqpID(u32 dwHandle);

void CVmpEqpHandle::Init()
{
	for(u16 wIndex = 0; wIndex <XMPU_MAX_VMP_NUM; ++wIndex)
	{
		m_atVmpMdl[wIndex].Clear();
		m_atVmpMdl[wIndex].m_dwEqpID = XMPU_EQP_ID_VMP_BEG + wIndex;
		memset(m_atVmpMdl[wIndex].m_achEqpAlias,0,sizeof(m_atVmpMdl[wIndex].m_achEqpAlias));
		snprintf(m_atVmpMdl[wIndex].m_achEqpAlias, sizeof(m_atVmpMdl[wIndex].m_achEqpAlias), "%s%d", g_abyVmpAliasNameGB2312,(wIndex + 1));
	}
	m_wVmpUsedNum = 0;
}

BOOL32 CVmpEqpHandle::Handle( CTpMsg *const ptMsg )
{	
	BOOL32 bRes = TRUE;
	u8* pData = ptMsg->GetBody();
	u16 wLen =  ptMsg->GetBodyLen();
	u16 wEvent = ptMsg->GetEvent();

	switch(wEvent)
	{
	case evXmpu_StartVmp_Rsp:
		{
			OnStartVmpRsp(ptMsg);
			break;
		}
	case evXmpu_ChangeVmp_Req:
		{
			OnChangeVmpReq(ptMsg);
			break;
		}
	case evXmpu_StartMpu2_Req:
		{
			OnStartMpu2Req(ptMsg);
			break;
		}
	case evXmpu_AskVmpKey_Req:
		{
			OnXmpuVmpAskKey(ptMsg);
			break;
		}
	case evUms_XmpuAskVmpKey_Req:
		{
			OnUmsVmpAskKey(ptMsg);
			break;
		}
	case evXmpu_VmpDisConnect_Nty:
		{
			OnVmpDisConnect(ptMsg);
			break;
		}
	case evXmpu_UpdateSpeakerSide_Req:
		{
			OnUpdateSpeakerSideReq(ptMsg);
			break;
		}
	default:
		{
			bRes = FALSE;
			MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::Handle Unknow event:%d->%s", ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
		}
		break;
	}
	return bRes;
}

BOOL32 CVmpEqpHandle::AssignEqpEx( TXmpuEqpParam* ptEqpParam)
{
	CHECK_XMPU_SEM;

	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(ptEqpParam->m_ptEqp->m_dwEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::AssignEqpEx. has no idle vmp! \n"));
		return FALSE;
	}

	//状态检测
	if ( ptVmpMdl->m_emStat != XmpuEqpStat_Idle)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::AssignEqpEx. vmp state error m_byEqpID:%d CurrStat:%s\n", 
			ptVmpMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptVmpMdl->m_emStat)));	
		return FALSE;
	}
	TXmpuVmpParam* ptInfo = (TXmpuVmpParam*)ptEqpParam;
	//
	ptVmpMdl->m_wConfID = ptInfo->m_wConfID;
	ptVmpMdl->m_dwMediaIP = ptInfo->m_dwMediaIp;
	ptVmpMdl->m_emStat = XmpuEqpStat_Starting;
	ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum = min(TP_VMP_MAX_IN_CHN_NUM, ptInfo->m_byVMPMemberNum);
// 	memcpy(ptVmpMdl->m_tTpVmpParam.m_atVMPMember, ptInfo->m_atVMPMember,
// 		sizeof(TTPVMPMember)*ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum);
	ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum = min(TP_VMP_MAX_OUT_CHN_NUM, ptInfo->m_byOutMemBerNum);
// 	memcpy(ptVmpMdl->m_tTpVmpParam.m_atVMPOutMember, ptInfo->m_atVMPOutMember,
// 		sizeof(TUmsVidFormat)*ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum);
	//初始化端口 22000~33200  每个合成器250个端口 解码和编码间隔200 最大32个合成器
	ptVmpMdl->m_wUmsRcvStartPort = XMPU_VMP_BEGIN_PORT + (ptVmpMdl->m_dwEqpID - XMPU_EQP_ID_VMP_BEG)*XMPU_VMP_MAX_PORT_SPAN;
	AdjustUmsAddr(ptVmpMdl);


	MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::AssignEqpEx  EqpID:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s, emStyle:%d!\n",
		ptVmpMdl->m_dwEqpID, ptVmpMdl->m_wConfID, Tpu32ToIP(ptVmpMdl->m_dwMediaIP), 
		ptVmpMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptVmpMdl->m_emStat),
		ptInfo->m_emVmpStyle));

	// start vmp
	if (!MediaStartVmp(ptVmpMdl->m_dwHandle, ptVmpMdl->m_dwEqpID, *ptInfo))
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::AssignEqpEx. MediaStartVmp Failed! wEqpID:%d, vmphandle:%u.\n", 
			ptVmpMdl->m_dwEqpID, ptVmpMdl->m_dwHandle));
		MediaReleaseVmp(ptVmpMdl->m_dwHandle);
		ptVmpMdl->Clear();
		return FALSE;
	}

	if (!MediaGetVmpVipNum(ptVmpMdl->m_dwHandle, ptVmpMdl->m_tTpVmpParam.m_byVipMaxStyle, ptVmpMdl->m_tTpVmpParam.m_byVipNum))
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::AssignEqpEx. MediaGetVmpVipNum Failed! wEqpID:%d, vmphandle:%u.\n", 
			ptVmpMdl->m_dwEqpID, ptVmpMdl->m_dwHandle));
		MediaReleaseVmp(ptVmpMdl->m_dwHandle);
		ptVmpMdl->Clear();
		return FALSE;
	}

	//出参
	memcpy(ptInfo->m_atDecMiddleRtpAddr, ptVmpMdl->m_tTpVmpParam.m_atDecMiddleRtpAddr, sizeof(ptInfo->m_atDecMiddleRtpAddr));
	memcpy(ptInfo->m_atDecRtcpAddr, ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr, sizeof(ptInfo->m_atDecRtcpAddr));
	memcpy(ptInfo->m_atEncRtpAddr, ptVmpMdl->m_tTpVmpParam.m_atEncRtpAddr, sizeof(ptInfo->m_atEncRtpAddr));
	memcpy(ptInfo->m_atEncMiddleRtcpAddr, ptVmpMdl->m_tTpVmpParam.m_atEncMiddleRtcpAddr, sizeof(ptInfo->m_atEncMiddleRtcpAddr));
	ptInfo->m_byVipMaxStyle = ptVmpMdl->m_tTpVmpParam.m_byVipMaxStyle;
	ptInfo->m_byVipNum = ptVmpMdl->m_tTpVmpParam.m_byVipNum;//0适配通道预占一位
	++m_wVmpUsedNum;
	return TRUE;
}

BOOL32 CVmpEqpHandle::ReleaseEqpEx( TXmpuEqpParam* ptEqpParam )
{
	CHECK_XMPU_SEM;
	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(ptEqpParam->m_ptEqp->m_dwEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::ReleaseEqpEx. ptVmpMdl Is NULL! wEqpID:%d\n", ptEqpParam->m_ptEqp->m_dwEqpID));
		return FALSE;
	}

	//状态检测
	if ( ptVmpMdl->m_emStat != XmpuEqpStat_Starting && ptVmpMdl->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::ReleaseEqpEx.vmp state error m_byEqpID:%d CurrStat:%s\n", 
			ptVmpMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptVmpMdl->m_emStat)));	
		return FALSE;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::ReleaseEqpEx. ConfID:%d, dwEqpID:%d, dwHandle:%d\n", 
		ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID, ptVmpMdl->m_dwHandle));

	MediaReleaseVmp(ptVmpMdl->m_dwHandle);

	ptVmpMdl->Clear();
	if (m_wVmpUsedNum)
	{
		--m_wVmpUsedNum ;
	}
	return TRUE;
}

void CVmpEqpHandle::OnChangeVmpReq( CTpMsg *const ptMsg )
{
	u32 dwEqpID = 0;
	TTVmpStartParam tVmpParam;
	TP_SAFE_CAST(dwEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(tVmpParam, ptMsg->GetBody() + sizeof(u32));

	CHECK_XMPU_SEM;
	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(dwEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnChangeVmpReq, not Find EqpID! dwEqpID:%d\n", dwEqpID));
		return ;
	}

	//状态检测
	if ( ptVmpMdl->m_emStat != XmpuEqpStat_Starting && ptVmpMdl->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnChangeVmpReq. ConfID:%d, wEqpID:%d, CurrStat:%s\n", 
			ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptVmpMdl->m_emStat)));	
		//		SendMsgToCall( CInstance::DAEMON, evtp_VmpToCall_NAck);
		return ;
	}
	
	u8 byNum = ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum;
	ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum = min(TP_VMP_MAX_IN_CHN_NUM, tVmpParam.m_byVMPMemberNum);

// 	memcpy(ptVmpMdl->m_tTpVmpParam.m_atVMPMember, tVmpParam.m_atVMPMember,
// 		sizeof(TTPVMPMember)*ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum);

	MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnChangeVmpReq  EqpID:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s, emStyle:%d!\n",
		ptVmpMdl->m_dwEqpID, ptVmpMdl->m_wConfID, Tpu32ToIP(ptVmpMdl->m_dwMediaIP), 
		ptVmpMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptVmpMdl->m_emStat),
		tVmpParam.m_emVmpStyle));

	MediaChangeVmp(ptVmpMdl->m_dwHandle, tVmpParam, ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum);

	for (u16 wIndex = 0; wIndex < ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum; ++wIndex)
	{ 
		if (!MediaSetVmpDecAddr(ptVmpMdl->m_dwHandle, wIndex, ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex]))
		{
			MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnChangeVmpReq. Set Vmp DecRtcp error: windex%d\n", wIndex));
			break;
		}
	}
	return ;
}

void CVmpEqpHandle::OnStartVmpRsp( CTpMsg *const ptMsg )
{
	TXmpuStartVmpRsp tRes;
	TP_SAFE_CAST(tRes, ptMsg->GetBody());
	tRes.m_dwEqpID = GetVmpEqpID(tRes.m_dwHandle);
	MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. dwEqpID:%d, Handle:%d, Res:%d\n", 
		tRes.m_dwEqpID, tRes.m_dwHandle, tRes.m_emRes));

	BOOL32 bRes = TRUE;
	TXmpuVmpModle* ptVmpMdl = NULL;
	CHECK_XMPU_SEM;
	do 
	{
		ptVmpMdl = FindVmpMdl(tRes.m_dwEqpID);
		if ( NULL == ptVmpMdl )
		{
			MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. ptVmpMdl Is NULL! wEqpID:%d\n", tRes.m_dwEqpID));
			return;
		}

		if (tRes.m_emRes != StartVmpRsp_Success)
		{
			MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. start vmp error! wEqpID:%d\n", tRes.m_dwEqpID));
			bRes = FALSE;
			break;
		}

		if (ptVmpMdl->m_emStat != XmpuEqpStat_Starting && ptVmpMdl->m_emStat != XmpuEqpStat_Running)
		{
			MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. vmp state error! wEqpID:%d, Stat:%s\n", ptVmpMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptVmpMdl->m_emStat)));
			bRes = FALSE;
			break;
		}

		ptVmpMdl->m_emStat = XmpuEqpStat_Running;
		// 解码通道
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; ++wIndex)
		{ 
			if (!MediaSetVmpDecAddr(ptVmpMdl->m_dwHandle, wIndex, ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. Set Vmp DecRtcp error: windex%d\n", wIndex));
				bRes = FALSE;
				break;
			}

			if (!MediaGetVmpDecAddr(ptVmpMdl->m_dwHandle, wIndex,ptVmpMdl->m_tTpVmpParam.m_atDecRtpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. Get Vmp DecRtp error: windex%d\n", wIndex));
				bRes = FALSE;
				break;
			}
		}

		// 编码通道
		for (wIndex = 0; wIndex < ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum; ++wIndex)
		{
			if (!MediaSetVmpEncAddr(ptVmpMdl->m_dwHandle, wIndex, ptVmpMdl->m_tTpVmpParam.m_atEncRtpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. Set  Vmp EncRtp error: windex%d\n", wIndex));
				bRes = FALSE;
				break;
			}

			if (!MediaGetVmpEncAddr(ptVmpMdl->m_dwHandle, wIndex,ptVmpMdl->m_tTpVmpParam.m_atEncRtcpAddr[wIndex]))
			{
				MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartVmpRsp. Get Vmp EncRtcp error: windex%d\n", wIndex));
				bRes = FALSE;
				break;
			}
		}
	} while (0);

	TXmpuVmpMdyInfo tInfo;
	tInfo.m_bSuccess = bRes;
	tInfo.m_dwEqpID = ptVmpMdl->m_dwEqpID;
	tInfo.m_byDecNum = TP_VMP_MAX_IN_CHN_NUM;
	tInfo.m_byEncNum = ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum;
	memcpy(tInfo.m_atDecRtpAddr,  ptVmpMdl->m_tTpVmpParam.m_atDecRtpAddr, sizeof(tInfo.m_atDecRtpAddr));
	memcpy(tInfo.m_atEncRtcpAddr,  ptVmpMdl->m_tTpVmpParam.m_atEncRtcpAddr, sizeof(tInfo.m_atEncRtcpAddr));
	SendMsgToCall(ptVmpMdl->m_wConfID, evXmpu_VmpMdy_Nty, &tInfo, sizeof(tInfo));

	if (FALSE == bRes)
	{
		MediaReleaseVmp(tRes.m_dwHandle);
		ptVmpMdl->Clear();
		if (m_wVmpUsedNum)
		{
			--m_wVmpUsedNum ;
		}
	}
}

void CVmpEqpHandle::OnXmpuVmpAskKey( CTpMsg *const ptMsg )
{
	TTPVmpAskFrame tAskFrame;
	TP_SAFE_CAST(tAskFrame, ptMsg->GetBody());

	HMEDIARES dwHandle;
	TP_SAFE_CAST(dwHandle, ptMsg->GetBody()+ sizeof(TTPVmpAskFrame));
	tAskFrame.m_byEqpID = (u8)GetVmpEqpID(dwHandle);

	CHECK_XMPU_SEM;
	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(tAskFrame.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpAskKey. ptVmpMdl Is NULL! wEqpID:%d\n", tAskFrame.m_byEqpID));
		return ;
	}

	if ( !ptVmpMdl->m_dwHandle)
	{
		MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpAskKey. VmpHandle Is NULL! wEqpID:%d\n", tAskFrame.m_byEqpID));
		return ;
	}

	if ( !ptVmpMdl->m_tKeyFrameStatisToEqp.CheckFrameStatis() )
	{
		return ;
	}

	MdlLowDtl(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpAskKey. FastUpdate To Eqp! wConfID:%d, EqpID:%d, ChanIndx:%d\n", 
		ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID, tAskFrame.m_byChanIndx));

	SendMsgToCall(ptVmpMdl->m_wConfID, evXmpu_AskVmpKey_Req, &tAskFrame, sizeof(tAskFrame));

}

void CVmpEqpHandle::OnUmsVmpAskKey( CTpMsg *const ptMsg )
{
	TTPVmpAskFrame tAskFrame;
	TP_SAFE_CAST(tAskFrame, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(tAskFrame.m_byEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpAskKey. ptVmpMdl Is NULL! wEqpID:%d\n", tAskFrame.m_byEqpID));
		return ;
	}

	if ( !ptVmpMdl->m_dwHandle)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpAskKey. VmpHandle Is NULL! wEqpID:%d\n", tAskFrame.m_byEqpID));
		return ;
	}

	if ( !ptVmpMdl->m_tKeyFrameStatisToEqp.CheckFrameStatis() )
	{
		return ;
	}

	MdlLowDtl(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpAskKey. FastUpdate To call! wConfID:%d, EqpID:%d, ChanIndx:%d\n", 
		ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID, tAskFrame.m_byChanIndx));

	MediaReqVmpIFrame(ptVmpMdl->m_dwHandle, tAskFrame.m_byChanIndx);
}

//解码中转间隔100 编码间隔25
void CVmpEqpHandle::AdjustUmsAddr(TXmpuVmpModle* ptVmpMdl)
{
	if (NULL == ptVmpMdl)
	{
		return;
	}
	u16 wIndex = 0;
	u32_ip dwIp = ptVmpMdl->m_dwMediaIP;
	u16		wPort = 0;
	for (wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; ++wIndex)
	{ 
		wPort = ptVmpMdl->m_wUmsRcvStartPort + wIndex;
		ptVmpMdl->m_tTpVmpParam.m_atDecMiddleRtpAddr[wIndex].SetAddr(dwIp,  wPort);
		wPort+=100;
		ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex].SetAddr(dwIp,  wPort);
	}

	// 编码通道
	for (wIndex = 0; wIndex <TP_VMP_MAX_OUT_CHN_NUM; ++wIndex)
	{
		wPort = ptVmpMdl->m_wUmsRcvStartPort + XMPU_VMP_MAX_DEC_PORT_SPAN + wIndex;
		ptVmpMdl->m_tTpVmpParam.m_atEncRtpAddr[wIndex].SetAddr(dwIp,  wPort);
		wPort+=25;
		ptVmpMdl->m_tTpVmpParam.m_atEncMiddleRtcpAddr[wIndex].SetAddr(dwIp,  wPort);
	}
}

void CVmpEqpHandle::OnVmpDisConnect( CTpMsg *const ptMsg )
{
	
	HMEDIARES dwHandle = 0;
	TP_SAFE_CAST(dwHandle, ptMsg->GetBody());
	u32	dwEqpID = GetVmpEqpID(dwHandle);

	CHECK_XMPU_SEM;
	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(dwEqpID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpDisConnect. ptVmpMdl Is NULL! wEqpID:%d\n", dwEqpID));
		return ;
	}

	if (ptVmpMdl->m_emStat == XmpuEqpStat_Starting || ptVmpMdl->m_emStat == XmpuEqpStat_Running)
	{
		SendMsgToCall(ptVmpMdl->m_wConfID, evXmpu_VmpDisConnect_Nty, &dwEqpID, sizeof(dwEqpID));
	}

	MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnVmpDisConnect. FastUpdate To Eqp! wConfID:%d, EqpID:%d\n", 
		ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID));

	g_mapVmp.erase(dwHandle);
	ptVmpMdl->Clear();

	if (m_wVmpUsedNum)
	{
		--m_wVmpUsedNum ;
	}
}

void CVmpEqpHandle::OnUpdateSpeakerSideReq( CTpMsg *const ptMsg )
{
	TVmpSpeakerFlag tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(tInfo.m_wChanID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnUpdateSpeakerSideReq, not Find EqpID! dwEqpID:%d\n", tInfo.m_wChanID));
		return ;
	}

	//状态检测
	if ( ptVmpMdl->m_emStat != XmpuEqpStat_Starting && ptVmpMdl->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnUpdateSpeakerSideReq. ConfID:%d, wEqpID:%d, CurrStat:%s\n", 
			ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptVmpMdl->m_emStat)));	
		//		SendMsgToCall( CInstance::DAEMON, evtp_VmpToCall_NAck);
		return ;
	}

	MdlLowDtl(Ums_Mdl_Xmpu, ("[CVmpEqpHandle::OnUpdateSpeakerSideReq] ServiceId:%d. (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n", tInfo.m_wChanID,
		tInfo.m_abyFlag[0],tInfo.m_abyFlag[1],tInfo.m_abyFlag[2],tInfo.m_abyFlag[3],tInfo.m_abyFlag[4],
		tInfo.m_abyFlag[5],tInfo.m_abyFlag[6],tInfo.m_abyFlag[7],tInfo.m_abyFlag[8],tInfo.m_abyFlag[9]));

	MediaUpdateLineSide(ptVmpMdl->m_dwHandle, tInfo);
}

void CVmpEqpHandle::OnStartMpu2Req( CTpMsg *const ptMsg )
{
	TVmpStartInfo tVmpInfo;
	TP_SAFE_CAST(tVmpInfo, ptMsg->GetBody());

	CHECK_XMPU_SEM;
	TXmpuVmpModle* ptVmpMdl = FindVmpMdl(tVmpInfo.m_wServiceID);
	if ( NULL == ptVmpMdl )
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartMpu2Req, not Find EqpID! dwEqpID:%d\n", tVmpInfo.m_wServiceID));
		return ;
	}

	//状态检测
	if ( ptVmpMdl->m_emStat != XmpuEqpStat_Starting && ptVmpMdl->m_emStat != XmpuEqpStat_Running)
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartMpu2Req. ConfID:%d, wEqpID:%d, CurrStat:%s\n", 
			ptVmpMdl->m_wConfID, ptVmpMdl->m_dwEqpID, GetXmpuEqpStatBuf(ptVmpMdl->m_emStat)));	
		//		SendMsgToCall( CInstance::DAEMON, evtp_VmpToCall_NAck);
		return ;
	}

	ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum = min(UMS_VMP_MAX_RCV, tVmpInfo.m_tVmpParam.m_tStyleInfo.m_byMemberNum);
	ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum = 1;
	// 	memcpy(ptVmpMdl->m_tTpVmpParam.m_atVMPMember, tVmpInfo.m_atVMPMember,
	// 		sizeof(TTPVMPMember)*ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum);

	MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnStartMpu2Req  EqpID:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s, emStyle:%d!\n",
		ptVmpMdl->m_dwEqpID, ptVmpMdl->m_wConfID, Tpu32ToIP(ptVmpMdl->m_dwMediaIP), 
		ptVmpMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptVmpMdl->m_emStat),
		tVmpInfo.m_tVmpParam.m_tStyleInfo.m_emVmpStyle));

	MediaChangeVmpTP(ptVmpMdl->m_dwHandle, tVmpInfo);

	for (u16 wIndex = 0; wIndex < ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum ; ++wIndex)
	{ 
		if (!MediaSetVmpDecAddr(ptVmpMdl->m_dwHandle, wIndex, ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex]))
		{
			MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle::OnChangeVmpReq. Set Vmp DecRtcp error: windex%d\n", wIndex));
			break;
		}
	}

}

void CVmpEqpHandle::UpdateVmpState( u16 wVmpNum )
{
	if (wVmpNum == 0)
	{
		return;
	}

	MdlHint(Ums_Mdl_Xmpu, ("CVmpEqpHandle UpdateVmpState ...\n"));
	TXmpuVmpNty tInfo;
	tInfo.m_byNum = min(wVmpNum, XMPU_MAX_VMP_NUM);
	for (u16 wIndex = 0; wIndex < tInfo.m_byNum; ++wIndex)
	{
		tInfo.m_adwEqpID[wIndex] = m_atVmpMdl[wIndex].m_dwEqpID;
		strncpy(tInfo.m_aachEqpAlias[wIndex], m_atVmpMdl[wIndex].m_achEqpAlias, (TP_MAXLEN_EQP_ALIAS+1));
		tInfo.m_aachEqpAlias[wIndex][TP_MAXLEN_EQP_ALIAS] = '\0';
	}
	SendMsgToCall(CInstance::DAEMON, evXmpu_VmpConnect_Nty, &tInfo, sizeof(tInfo));
}

void CVmpEqpHandle::SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen )
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
	return ;
}

TXmpuVmpModle* CVmpEqpHandle::FindVmpMdl( u8 byEqpId )
{
	for ( u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_VMP_NUM;++wMdlIndex)
	{
		if ( m_atVmpMdl[wMdlIndex].m_dwEqpID == byEqpId )
		{
			return &m_atVmpMdl[wMdlIndex];
		}
	}

	return NULL;
}

TXmpuVmpModle* CVmpEqpHandle::FindIdleVmpMdl()
{
	for ( u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_VMP_NUM;++wMdlIndex)
	{
		if ( m_atVmpMdl[wMdlIndex].m_emStat == XmpuEqpStat_Idle)
		{
			return &m_atVmpMdl[wMdlIndex];
		}
	}

	return NULL;
}

BOOL32 CVmpEqpHandle::StopConf( u16 wConfID )
{
	for(u16 wIndex = 0; wIndex < XMPU_MAX_VMP_NUM; ++wIndex)
	{
		if (m_atVmpMdl[wIndex].m_wConfID == wConfID)
		{
			if (!m_atVmpMdl[wIndex].m_dwHandle)
			{
				MediaReleaseVmp(m_atVmpMdl[wIndex].m_dwHandle);
			}

			m_atVmpMdl[wIndex].Clear();
		}
	}
	return TRUE;
}

void CVmpEqpHandle::Show()
{
	msgprintnotime("VmpEqp Info : \n");
	TXmpuVmpModle* ptVmpMdl = NULL;

	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_VMP_NUM; ++wMdlIndex)
	{
		ptVmpMdl = &m_atVmpMdl[wMdlIndex];
		if (ptVmpMdl->m_emStat == XmpuEqpStat_Idle)
		{
			continue;
		}

		msgprintnotime("	Index:%d, EqpID:%d, AlisaName:%s, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s, vipNum:%d, maxStyle:%d\n",
			wMdlIndex, ptVmpMdl->m_dwEqpID, ptVmpMdl->m_achEqpAlias, ptVmpMdl->m_dwHandle, ptVmpMdl->m_wConfID,Tpu32ToIP(ptVmpMdl->m_dwMediaIP), 
			ptVmpMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptVmpMdl->m_emStat),
			ptVmpMdl->m_tTpVmpParam.m_byVipNum, ptVmpMdl->m_tTpVmpParam.m_byVipMaxStyle );

		u16 wIndex = 0;
		TTPVMPMember* ptDec = NULL;
		msgprintnotime("		DecMemberInfo:EncNum:%d \n", 
			ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum);
		for (wIndex = 0; wIndex < ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d,  DecMiddleRtp(IP:"TPIPFORMAT" Port:%d), DecRtp (IP:"TPIPFORMAT" Port:%d), DecRtcp(IP:"TPIPFORMAT" Port:%d)\n", 
				wIndex, Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atDecMiddleRtpAddr[wIndex].GetIP()),  ptVmpMdl->m_tTpVmpParam.m_atDecMiddleRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atDecRtpAddr[wIndex].GetIP()),ptVmpMdl->m_tTpVmpParam.m_atDecRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex].GetIP()),ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex].GetPort());
		}

		TUmsVidFormat* ptEnc = NULL;
		msgprintnotime("		EncOutInfo:DecNum:%d \n", 
			ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum);
		for (wIndex = 0; wIndex < ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d, EncRtp(IP:"TPIPFORMAT" Port:%d):, EncMiddleRtcp (IP:"TPIPFORMAT" Port:%d), EncRtcp (IP:"TPIPFORMAT" Port:%d)\n", 
				wIndex, Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atEncRtpAddr[wIndex].GetIP()), ptVmpMdl->m_tTpVmpParam.m_atEncRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atEncMiddleRtcpAddr[wIndex].GetIP()), ptVmpMdl->m_tTpVmpParam.m_atEncMiddleRtcpAddr[wIndex].GetPort(),
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atEncRtcpAddr[wIndex].GetIP()), ptVmpMdl->m_tTpVmpParam.m_atEncRtcpAddr[wIndex].GetPort());
		}
	}
}

void CVmpEqpHandle::ShowAll()
{
	msgprintnotime("VmpEqp Info : \n");
	TXmpuVmpModle* ptVmpMdl = NULL;

	for (u16 wMdlIndex = 0; wMdlIndex < XMPU_MAX_VMP_NUM; ++wMdlIndex)
	{
		ptVmpMdl = &m_atVmpMdl[wMdlIndex];
		msgprintnotime("	Index:%d, EqpID:%d, AlisaName:%s, dwHandle:%d, ConfID:%d, DsIP:"TPIPFORMAT", Port(UmsStartPort:%d), Stat:%s, vipNum:%d, maxStyle:%d\n",
			wMdlIndex, ptVmpMdl->m_dwEqpID, ptVmpMdl->m_achEqpAlias, ptVmpMdl->m_dwHandle, ptVmpMdl->m_wConfID,Tpu32ToIP(ptVmpMdl->m_dwMediaIP), 
			ptVmpMdl->m_wUmsRcvStartPort,GetXmpuEqpStatBuf(ptVmpMdl->m_emStat),
			ptVmpMdl->m_tTpVmpParam.m_byVipNum, ptVmpMdl->m_tTpVmpParam.m_byVipMaxStyle );

		u16 wIndex = 0;
		TTPVMPMember* ptDec = NULL;
		msgprintnotime("		DecMemberInfo:EncNum:%d \n", 
			ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum);
		for (wIndex = 0; wIndex < ptVmpMdl->m_tTpVmpParam.m_byVMPMemberNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d,  DecMiddleRtp(IP:"TPIPFORMAT" Port:%d), DecRtp (IP:"TPIPFORMAT" Port:%d), DecRtcp(IP:"TPIPFORMAT" Port:%d)\n", 
				wIndex, Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atDecMiddleRtpAddr[wIndex].GetIP()),  ptVmpMdl->m_tTpVmpParam.m_atDecMiddleRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atDecRtpAddr[wIndex].GetIP()),ptVmpMdl->m_tTpVmpParam.m_atDecRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex].GetIP()),ptVmpMdl->m_tTpVmpParam.m_atDecRtcpAddr[wIndex].GetPort());
		}

		TUmsVidFormat* ptEnc = NULL;
		msgprintnotime("		EncOutInfo:DecNum:%d \n", 
			ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum);
		for (wIndex = 0; wIndex < ptVmpMdl->m_tTpVmpParam.m_byOutMemBerNum; ++wIndex)
		{
			msgprintnotime("			wIndex:%d, EncRtp(IP:"TPIPFORMAT" Port:%d):, EncMiddleRtcp (IP:"TPIPFORMAT" Port:%d), EncRtcp (IP:"TPIPFORMAT" Port:%d)\n", 
				wIndex, Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atEncRtpAddr[wIndex].GetIP()), ptVmpMdl->m_tTpVmpParam.m_atEncRtpAddr[wIndex].GetPort(), 
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atEncMiddleRtcpAddr[wIndex].GetIP()), ptVmpMdl->m_tTpVmpParam.m_atEncMiddleRtcpAddr[wIndex].GetPort(),
				Tpu32ToIP(ptVmpMdl->m_tTpVmpParam.m_atEncRtcpAddr[wIndex].GetIP()), ptVmpMdl->m_tTpVmpParam.m_atEncRtcpAddr[wIndex].GetPort());
		}
	}
}


void CVmpEqpHandle::ReFreshVmpState(BOOL32 bIncrease, u16 wNum)
{
	MdlLowDtl(Ums_Mdl_Xmpu, ("CVmpEqpHandle ReFreshVmpState bInrease:%d, Num:%d\n", bIncrease, wNum));
	TXmpuVmpNty tInfo;
	if ((wNum > XMPU_MAX_VMP_NUM))
	{
		MdlError(Ums_Mdl_Xmpu, ("CVmpEqpHandle ReFreshVmpState Error Vmp Num:%d\n", wNum));
		return;
	}
	tInfo.m_byNum = wNum;
	tInfo.m_bIncrease = bIncrease;
	if (bIncrease)
	{
		for (u16 wIndex = 0; wIndex < wNum ; ++wIndex)
		{
			tInfo.m_adwEqpID[wIndex] = m_atVmpMdl[wIndex].m_dwEqpID;
			strncpy(tInfo.m_aachEqpAlias[wIndex], m_atVmpMdl[wIndex].m_achEqpAlias, (TP_MAXLEN_EQP_ALIAS+1));
			tInfo.m_aachEqpAlias[wIndex][TP_MAXLEN_EQP_ALIAS] = '\0';
		}
	}

	SendMsgToCall(CInstance::DAEMON, evXmpu_VmpRefresh_Nty, &tInfo, sizeof(tInfo));
}