#include "umsvmpinst.h"
#include "tpsys.h"
#include "tpmsg.h"
#include "eventoutmpu2tp.h"
#include "umsobject.h"
#include "umsboardinst.h"
#include "umsinnerstruct.h"

#define UMS_VMP_INIT				OSP_USEREVENT_BASE + 1
#define UMS_VMP_REGIST_TIMER_ID		OSP_USEREVENT_BASE + 2	
#define UMS_VMP_REGIST_TIME			10000
#define UMS_VMP_CHECK_IFRAME_INTERVAL	1000

#define IPFORMAT		"%d.%d.%d.%d"
#define u32ToIP(ip)		(u8)(ntohl(ip)>>24),\
						(u8)(ntohl(ip)>>16),\
						(u8)(ntohl(ip)>>8), \
                        (u8)ntohl(ip) 

extern BOOL32 g_bLogon;
CUmsVmpApp	g_cUmsVmpApp;

u32 g_dwMpu2tpNetBandMul = 20;

void InitUmsVmp(u32 dwNode)
{
	if (INVALID_NODE == dwNode)
	{
		MdlError(Ums_Mdl_Mpu2TP, ("InitUmsVmp Invalid node.\n"));
		return ;
	}

 	g_cUmsVmpApp.SetNode(dwNode);
 	if (!g_cUmsVmpApp.IsInit())
 	{
 		g_cUmsVmpApp.Init();
 		g_cUmsVmpApp.CreateApp("UmsVmpApp", AID_MPU2TP_APP, 80, 4096);
 	}
 
 	for (u16 wIndex = 0; wIndex < UMS_VMP_MAX_CHANNEL; ++wIndex)
 	{
 		OspPost(MAKEIID(AID_MPU2TP_APP, wIndex+1), UMS_VMP_INIT);
 	}
}

void StopApp()
{
	OspDisconnectTcpNode(g_cUmsVmpApp.ConnectNode());
	SetLogFlush();
	ExitKdvLog();
	OspQuit();
}

//////////////////////////////////////////////////////////////////////////
//vmpdata
CVmpData::CVmpData()
{
	m_bInit = FALSE;

	Clear();
}

CVmpData::~CVmpData()
{

}

void CVmpData::Clear()
{
	m_dwNode = INVALID_NODE;
}


//////////////////////////////////////////////////////////////////////////
//CUmsVmpIns

CUmsVmpInst::CUmsVmpInst()
{
	Clear();
}

CUmsVmpInst::~CUmsVmpInst()
{

}

void CUmsVmpInst::InstanceEntry(CMessage *const pcMsg)
{
	CTpMsg cMsg(pcMsg);

	switch (pcMsg->event)
	{
	case UMS_VMP_INIT:
		{
			EventInit(pcMsg);
		}
		break;

	case UMS_VMP_REGIST_TIMER_ID:
		{
			EventRegTimer(cMsg);
		}
		break;

	case ev_mpu2tp_NeedFrame_Timer:
		{
			EventCheckFrameTimer(pcMsg);
		}
		break;

	case ev_mpu2tp_regist_ack:
		{
			EventRegAck(cMsg);
		}
		break;

	case ev_mpu2tp_regist_nack:
		{
			EventRegNack(cMsg);
		}
		break;

	case OSP_DISCONNECT:
		{
			EventDisconnect(pcMsg);
		}
		break;

	case ev_mpu2tp_start_req:
		{
			EventStartReq(cMsg);
		}
		break;

	case ev_mpu2tp_mdy_param:
		{
			EventMdyParam(cMsg);
		}
		break;

	case ev_mpu2tp_stop_req:
		{
			EventStopReq(cMsg);
		}
		break;

	case ev_mpu2tp_AskFrame_Req:
		{
			EventFrameReq(cMsg);
		}
		break;
	case ev_mpu2tp_ChangeUmsIP_Req:
		{
			TVmpRegAck tAck;
			memcpy(&tAck, cMsg.GetBody(), sizeof(tAck));
			m_cUmsVmp.UpdateRmtPort(tAck.m_dwRcvIP, tAck.m_wRcvPort);
		}
		break;
	case ev_mpu2tp_SpeakerFlag_Ntfy:
		{
			EventUpdateSpeakerFlag(cMsg);
		}
		break;
	case ev_mpu2tp_UpdateFlag400_Timer:
		{
			m_cUmsVmp.UpdateSidelineColor();
//			SetTimer(ev_mpu2tp_UpdateFlag200_Timer, 200);
		}
		break;
	case ev_mpu2tp_UpdateFlag200_Timer:
		{
			m_cUmsVmp.UpdateSidelineColor(FALSE);
		}
		break;

//Protocol_file

 	case ev_mpu2tp_SetMediaKey_Req:
		{
			EventSetMediaKey(cMsg);
		}
		break;


	default:
		MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::InstanceEntry. evnet:%d no proc!!!\n", pcMsg->event));
		break;
	}
}

void CUmsVmpInst::EventInit(CMessage *const pcMsg)
{
	Clear();

	Register();
	SetTimer(UMS_VMP_REGIST_TIMER_ID, UMS_VMP_REGIST_TIME);

	::OspNodeDiscCBRegQ(g_cUmsVmpApp.ConnectNode(), GetAppID(), GetInsID());

	MdlHint(Ums_Mdl_Mpu2TP, ("EventInit Registed to ums. VmpID:%d\n", m_cUmsVmp.m_wVmpID));
}

void CUmsVmpInst::EventRegTimer(CTpMsg& cMsg)
{
	KillTimer(UMS_VMP_REGIST_TIMER_ID);
	if ( m_bRegState )
	{
		MdlHint(Ums_Mdl_Mpu2TP, ("EventRegTimer Vmp already register to ums, kill timer\n"));
		return ;
	}
	Register();
	SetTimer(UMS_VMP_REGIST_TIMER_ID, UMS_VMP_REGIST_TIME);
}

void CUmsVmpInst::EventRegAck(CTpMsg& cMsg)
{
	KillTimer(UMS_VMP_REGIST_TIMER_ID);

	TVmpRegAck tAck;
	TVmpTimeSpan tSpan;
	memcpy(&tAck, cMsg.GetBody(), sizeof(tAck));
	memcpy(&tSpan, cMsg.GetBody()+sizeof(tAck), sizeof(tSpan));

	if(cMsg.GetBodyLen() >= sizeof(tAck) + sizeof(tSpan) + sizeof(u32))
	{
        u32 dwMpu2tpNetBandMul = 0;
		memcpy(&dwMpu2tpNetBandMul, cMsg.GetBody()+sizeof(tAck) + sizeof(tSpan), sizeof(u32));
		if (dwMpu2tpNetBandMul >=10  && dwMpu2tpNetBandMul <= 50)
		{
            g_dwMpu2tpNetBandMul = dwMpu2tpNetBandMul;
		}
	}


	if (m_bRegState)
	{
		MdlHint(Ums_Mdl_Mpu2TP, ("EventRegAck Vmp already register to ums.\n"));
		return ;
	}

	MdlHint(Ums_Mdl_Mpu2TP, ("EventRegAck RcvIP:"IPFORMAT", RcvPort:%d, FirstFime:%d, SecondTime:%d, ThirdTime:%d, RejectTime:%d.\n", 
			u32ToIP(tAck.m_dwRcvIP), tAck.m_wRcvPort, tSpan.m_wFirstTimeSpan, tSpan.m_wSecondTimeSpan,
			tSpan.m_wThirdTimeSpan, tSpan.m_wRejectTimeSpan));

	if (!m_cUmsVmp.Init(tAck.m_dwRcvIP, tAck.m_wRcvPort, UMS_VMP_RCV_PORT+GetInsID()*UMS_VMP_CHAN_SPAN,
						UMS_VMP_SND_PORT+GetInsID()*UMS_VMP_CHAN_SPAN, tSpan))
	{
		MdlError(Ums_Mdl_Mpu2TP, ("EventRegAck Init vmp ep failed.\n"));
	}
	else
	{
		m_bRegState = TRUE;
		m_curState = em_vmp_idle;
	}
}

void CUmsVmpInst::EventRegNack(CTpMsg& cMsg)
{
	KillTimer(UMS_VMP_REGIST_TIMER_ID);

	MdlHint(Ums_Mdl_Mpu2TP, ("EventRegNack \n"));

	SetTimer(UMS_VMP_REGIST_TIMER_ID, UMS_VMP_REGIST_TIME);
}

void CUmsVmpInst::EventDisconnect(CMessage *const pcMsg)
{
	MdlHint(Ums_Mdl_Mpu2TP, ("EventDisconnect \n"));
	KillTimer(UMS_VMP_REGIST_TIMER_ID);

	m_cUmsVmp.Stop();
	Clear();

//	SetTimer(UMS_VMP_REGIST_TIMER_ID, UMS_VMP_REGIST_TIME);
}

void CUmsVmpInst::EventStartReq(CTpMsg& cMsg)
{
	TVmpStartParam tInfo;
	memcpy(&tInfo, cMsg.GetBody(), sizeof(tInfo));

	TVmpStartRes tRes;
	tRes.m_wChanID = GetInsID();
	do 
	{
		if (em_vmp_invalid == m_curState)
		{
			MdlError(Ums_Mdl_Mpu2TP, ("EventStartReq Invalid channel.\n"));
			tRes.m_emRes = em_ums_vmp_invalid_chan;
			break;
		}

		if (em_vmp_working == m_curState)
		{
			MdlError(Ums_Mdl_Mpu2TP, ("EventStartReq Channel is working.\n"));
			tRes.m_emRes = em_ums_vmp_chan_working;
			break;
		}

		tRes.m_emRes = m_cUmsVmp.Start(tInfo);

	} while (FALSE);

	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_start_res, &tRes, sizeof(tRes));

	if (em_ums_vmp_success == tRes.m_emRes)
	{
		m_curState = em_vmp_working;

		SetTimer(ev_mpu2tp_NeedFrame_Timer, UMS_VMP_CHECK_IFRAME_INTERVAL);
	}

	MdlHint(Ums_Mdl_Mpu2TP, ("EventStartReq ChanID:%d, PicMode:%d, ShowMode:%d, MumberNum:%d, Res:%d.\n", 
			GetInsID(), tInfo.m_tStyleInfo.m_emVmpStyle, tInfo.m_tStyleInfo.m_emShowMode, 
			tInfo.m_tStyleInfo.m_byMemberNum, tRes.m_emRes));
	MdlHint(Ums_Mdl_Mpu2TP, ("  Encrypt Modl:%d, Len:%d, Key:%s\n", 
		tInfo.m_tEncrypt.m_emEncryptModel, tInfo.m_tEncrypt.m_byKeyLen, tInfo.m_tEncrypt.m_achEncKey));
	MdlHint(Ums_Mdl_Mpu2TP, ("  EncParam EncType:%d, Profile:%d, FrameRate:%d, BitRate:%d, Width:%d, Height:%d\n", 
		tInfo.m_tEncParam.m_byEncType, tInfo.m_tEncParam.m_byProfileType, tInfo.m_tEncParam.m_byFrameRate,
		tInfo.m_tEncParam.m_wBitRate, tInfo.m_tEncParam.m_wVideoWidth, tInfo.m_tEncParam.m_wVideoHeight));
}

void CUmsVmpInst::EventMdyParam(CTpMsg& cMsg)
{
	TVmpMdyInfo tInfo;
	TP_SAFE_CAST(tInfo, cMsg.GetBody());

	EmVmpRes emRes = em_ums_vmp_success;
	do 
	{
		if (em_vmp_working != m_curState)
		{
			MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventMdyParam Invalid state. State:%d.\n", CurState()));
			emRes = em_ums_vmp_invalid_chan;
			break;
		}

		emRes = m_cUmsVmp.SetEncParam(tInfo.m_tEncParam);
		if ( emRes != em_ums_vmp_success )
		{
			break;
		}

		emRes = m_cUmsVmp.ChangeStyleParam(tInfo.m_tStyleInfo);

	} while (FALSE);

	TVmpMdyRes tMdyRes;
	tMdyRes.m_emRes = emRes;
	tMdyRes.m_wChanID = GetInsID();

	PostMsg(UMS_EQP_APP_INST, ev_npu2tp_mdy_param_res, &tMdyRes, sizeof(tMdyRes));

	MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventMdyParam Res:%d.\n", emRes));
}

void CUmsVmpInst::EventStopReq(CTpMsg& cMsg)
{
	EmVmpRes emRes = em_ums_vmp_success;
	do 
	{
		if (em_vmp_working != m_curState)
		{
			MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventStopReq Channel is not in working.\n"));
			emRes = em_ums_vmp_invalid_chan;
			break;
		}

		m_cUmsVmp.Stop();

		NextState(em_vmp_idle);

		KillTimer(ev_mpu2tp_NeedFrame_Timer);

	} while (FALSE);

	TVmpStopRes tStopRes;
	tStopRes.m_emRes = emRes;
	tStopRes.m_wChanID = GetInsID();

	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_stop_res, &tStopRes, sizeof(tStopRes));
	
	MdlHint(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventStopReq Res:%d.\n", emRes));
}

void CUmsVmpInst::Register()
{
	TVmpRegistInfo tInfo;
	tInfo.m_byLayer = GetBrdLayer();
	tInfo.m_bySlot = GetBrdSlot();
	tInfo.m_wChanID = GetInsID();
	tInfo.m_dwStartPort = UMS_VMP_RCV_PORT+GetInsID()*UMS_VMP_CHAN_SPAN;
	tInfo.m_wRcvChanNum = UMS_VMP_MAX_RCV;
	tInfo.m_wSendChanNum = UMS_VMP_MAX_SND;

	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_regist, &tInfo, sizeof(tInfo));
}

void CUmsVmpInst::PostMsg(u32 dwDestIID, u16 wEvent, void* pBuf, u16 wLength)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if( pBuf != NULL )
	{
		cMsg.SetBody(pBuf, wLength);
	}

	cMsg.Post(dwDestIID, g_cUmsVmpApp.ConnectNode(), MAKEIID(AID_MPU2TP_APP, GetInsID()));
}

void CUmsVmpInst::Clear()
{
	m_bRegState = FALSE;
	m_curState = em_vmp_invalid;
	m_cUmsVmp.m_wVmpID = GetInsID();
    //Protocol_file

    m_cUmsVmp.SetQtHandle(GetInsID());


	m_dwLastTime = 0;
	KillTimer(ev_mpu2tp_NeedFrame_Timer);
}

void CUmsVmpInst::InstanceDump(u32 dwParam)
{
	switch (dwParam)
	{
	case em_init_channel:
		{
			TestInitChannel();
		}
		break;
	case em_ask_frame:
		{
			//TestAskFrame();
		}
		break;
	case em_show_info:
		{
			Show();
		}
		break;
	case em_show_enc:
		{
			m_cUmsVmp.m_bShowEnc = !m_cUmsVmp.m_bShowEnc;
		}
		break;
	}
}

void CUmsVmpInst::TestInitChannel()
{
	m_curState = em_vmp_idle;
}

void CUmsVmpInst::TestAskFrame()
{
	TVmpAskFrame tAskFrame;
	tAskFrame.m_wChanID = GetInsID();
	tAskFrame.m_wMemberIndx = 0;
	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_AskFrame_Req, &tAskFrame, sizeof(tAskFrame));

	tAskFrame.m_wMemberIndx = 1;
	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_AskFrame_Req, &tAskFrame, sizeof(tAskFrame));
	tAskFrame.m_wMemberIndx = 2;
	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_AskFrame_Req, &tAskFrame, sizeof(tAskFrame));
	tAskFrame.m_wMemberIndx = 3;
	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_AskFrame_Req, &tAskFrame, sizeof(tAskFrame));
	tAskFrame.m_wMemberIndx = 4;
	PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_AskFrame_Req, &tAskFrame, sizeof(tAskFrame));
}

void CUmsVmpInst::EventCheckFrameTimer( CMessage *const pcMsg )
{
	TVmpAskFrame tAskFrame;

//	OspPrintf(g_bLogon, FALSE ,  "CUmsVmp::EventCheckFrameTimer Beg. VmpID:%d\n", GetInsID());
	for ( u16 wIndex = 0; wIndex < UMS_VMP_MAX_RCV; wIndex ++)
	{
		if(m_cUmsVmp.CheckFrame(wIndex))
		{
			tAskFrame.m_wChanID = GetInsID();
			tAskFrame.m_wMemberIndx = wIndex;
			PostMsg(UMS_EQP_APP_INST, ev_mpu2tp_AskFrame_Req, &tAskFrame, sizeof(tAskFrame));
		}
	}
//	OspPrintf(g_bLogon, FALSE ,  "CUmsVmp::EventCheckFrameTimer End. VmpID:%d\n", GetInsID());

	SetTimer(ev_mpu2tp_NeedFrame_Timer, UMS_VMP_CHECK_IFRAME_INTERVAL);
}

void CUmsVmpInst::EventFrameReq( CTpMsg& cMsg )
{
	if (!m_cUmsVmp.SetFast())
	{
		MdlLowDtl(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventFrameReq fail!\n"));
	}
	else
	{
		MdlLowDtl(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventFrameReq success!\n"));
	}
	return ;
}

void CUmsVmpInst::Show()
{
	OspPrintf(TRUE, 0, "\nVmp-tp %d Info\n", GetInsID());
	OspPrintf(TRUE, 0, "Reg:%d\n", m_bRegState);
	m_cUmsVmp.Show();
}

void CUmsVmpInst::EventUpdateSpeakerFlag( CTpMsg& cMsg )
{
	TVmpSpeakerFlag tFlag;
	TP_SAFE_CAST(tFlag, cMsg.GetBody());

	MdlLowDtl(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventUpdateSpeakerFlag VmpID:%d (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)!\n", GetInsID()
		, tFlag.m_abyFlag[0], tFlag.m_abyFlag[1], tFlag.m_abyFlag[2], tFlag.m_abyFlag[3], tFlag.m_abyFlag[4], 
		tFlag.m_abyFlag[5], tFlag.m_abyFlag[6], tFlag.m_abyFlag[7], tFlag.m_abyFlag[8], tFlag.m_abyFlag[9]));

	m_cUmsVmp.SetSideLineFlag(tFlag.m_abyFlag, UMS_VMP_MAX_RCV);
	if ( m_cUmsVmp.UpdateSidelineColor(FALSE) )
	{//Ë¢ÐÂÆµÂÊ500ms
		KillTimer(ev_mpu2tp_UpdateFlag400_Timer);
		SetTimer(ev_mpu2tp_UpdateFlag400_Timer, 500);
	}

	return ;
}

//Protocol_file

void CUmsVmpInst::EventSetMediaKey( CTpMsg& cMsg )
{
	TTPMediaKeyInfo tMediaKeyInfo;
	TP_SAFE_CAST( tMediaKeyInfo, cMsg.GetBody());
	
	MdlError(Ums_Mdl_Mpu2TP, ("CUmsVmpInst::EventSetMediaKey Inst:%d ChanID:%d keyindex:%d MediaKeyLen:%d, Flag:%u!\n", 
		      GetInsID(), 
			  tMediaKeyInfo.m_dwHandle, 
			  tMediaKeyInfo.m_wIndex,
			  tMediaKeyInfo.m_dwKeyLen, 
			  tMediaKeyInfo.m_dwQtFlag));
	
	TTPQTMediaKeyInfo tInfo;
	tInfo.m_dwHandle = tMediaKeyInfo.m_dwHandle;
	tInfo.m_wIndex   = tMediaKeyInfo.m_wIndex;
	memcpy(tInfo.m_szAlias, tMediaKeyInfo.m_szAlias, TP_MAX_ALIAS_LEN);
	memcpy(tInfo.m_szMediaKey, tMediaKeyInfo.m_szMediaKey1, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, tMediaKeyInfo.m_szMediaKey2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, tMediaKeyInfo.m_szMediaKey3, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tInfo.m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, tMediaKeyInfo.m_szMediaKey4, TP_MAX_MEDIAKEY_LEN/4);
	tInfo.m_dwKeyLen = tMediaKeyInfo.m_dwKeyLen;
	tInfo.m_emKeyFrequency = tMediaKeyInfo.m_emKeyFrequency;
	tInfo.m_dwQtFlag = tMediaKeyInfo.m_dwQtFlag;
	
	m_cUmsVmp.SetMediaKey(tInfo);
}


