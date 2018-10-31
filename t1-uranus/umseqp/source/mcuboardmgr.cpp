#include "mcuboardmgr.h"
#include "eventoutumseqp.h"
#include "innereventumsmpu2.h"
#include "innereventumshdu.h"
#include "umscommonstruct.h"
#include "hdudef.h"
#include "umsapi.h"
#include "eventoutumscommonbrd.h"
#include "hduhandler.h"
#include "mcuinstdef.h"
#include "audmixhandler.h"
#include "audbashandler.h"

CTPMcuBrdRegApp g_cBrdRegApp;
CTPMcuBrdSsnApp g_cBrdSsnApp;

IServiceHandler* CTPMcuBrdSsn::m_apServiceHandler[em_eqp_handler_end];

BOOL CTPMcuBrdReg::PreDaemonMessageProc( CMessage *const ptMsg )
{
	u16 wEvent = ptMsg->event;
	
	BOOL32 bProc = TRUE;
	//来自外设板子
	switch( wEvent )
	{
	case UMS_BOARD_MPC_REG:
		OnDaemonBrdReg(ptMsg, (CApp*)&g_cBrdRegApp);
		break;
	default:
		bProc = FALSE;
		break;
	}
	
	return bProc;
}

BOOL CTPMcuBrdReg::PreMessageProc( CMessage *const ptMsg )
{
	u32 dwSrcID = ptMsg->srcid;
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->event;
	
	//来自外设板子
	switch( wEvent )
	{
	case UMS_BOARD_MPC_REG:
		OnBrdReg(ptMsg);
		break;
	case UMS_BOARD_MPC_GET_CONFIG:
		OnBrdGetCfgReq(ptMsg);
		break;
	case UMS_BOARD_MPC_GET_VERSION_ACK:
		OnBrdHDVersionRsp(ptMsg);
		break;
	case UMS_BOARD_MPC_UPDATE_NOTIFY:
		OnBrdSoftWareUpdateNtfy(ptMsg);
		break;
	case OSP_DISCONNECT:
		OnDisconnect(ptMsg);
		break;

	case UMS_MPC_BOARD_FTP_TELNET_SWITCH_NTY:
       OnBrdSwitchNty( ptMsg );
		break;
	default:
		return FALSE;
	}
	
	return TRUE;
}

void CTPMcuBrdReg::MessageProc( CTpMsg *const ptMsg )
{
	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();

	BOOL32 bProc = TRUE;
	
	if ( wSrcAppID == AID_UMSEQP_APP )
	{//来自外设管理模块
		switch( wEvent )
		{
		case ev_TPBrdReg_Ack:
			OnBrdRegAck(ptMsg);
			break;
		case ev_TPBrdReg_NAck:
			SendMsgToBrd(UMS_MPC_BOARD_REG_NACK);
			NextState(STATE_WAITREG);
			break;
		case ev_TPMcuBrdGetCfg_Ack:
			OnBrdGetCfgAck(ptMsg);
			break;
		case ev_TPBrdGetCfg_NAck:
			SendMsgToBrd(UMS_MPC_BOARD_REG_NACK);
			break;
		case ev_TPBrdReboot_Cmd:
			SendMsgToBrd(UMS_MPC_BOARD_RESET_CMD);
			break;
		case ev_TPBrdHDVersion_Req:
			SendMsgToBrd(UMS_MPC_BOARD_GET_VERSION_REQ);
			break;
		case ev_TPBrdSoftWareUpdate_Req:
			OnMpuUpdate(ptMsg);	
			break;

		case ev_TPBrdSwitchTeltp_Req: 
            OnSwitchTelnetFtpCmd( ptMsg );
			break;
		default:
			bProc = FALSE;
			break;
		}
	}
	else
	{
		bProc = FALSE;
	}
	
	if ( !bProc )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::MessageProc. unknow src! SrcAppID:%d, event:%d->%s\n", 
			wSrcAppID, wEvent, GetEventNamebyID(wEvent)));
	}	
}

BOOL CTPMcuBrdReg::DaemonObjectInit( u32 wParam, u32 lParam )
{
	SetLogTitle("[CTPMcuBrdReg]");
	InstClear();
	CTPMcuBrdReg* pcInst = NULL;
	for( u16 wIndex = 1; wIndex <= TP_BOARD_MAX_NUM + HDU_MAX_NUM; wIndex ++ )
	{
		pcInst = (CTPMcuBrdReg*)((CApp*)&g_cBrdRegApp)->GetInstance(wIndex);
		if ( NULL != pcInst )
		{
			pcInst->InstClear();
		}
	}
	return TRUE;
}

void CTPMcuBrdReg::InstClear( )
{
	m_dwBrdNode = INVALID_NODE;
	m_dwBrdIID = 0;

	m_bInit = TRUE;

	NextState(STATE_WAITREG);

	return ;
}

void CTPMcuBrdReg::SendMsgToUmsEqp( u16 wEvent, u8 * const pbyMsg, u16 wLen )
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSBRD_REG_APP, GetInsID()), m_dwBrdNode);

	return ;
}

void CTPMcuBrdReg::SendMsgToBrd( u16 wEvent, u8 * const pbyMsg, u16 wLen )
{
	if ( m_dwBrdNode != INVALID_NODE )
	{
		post(m_dwBrdIID, wEvent, pbyMsg, wLen, m_dwBrdNode);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::SendMsgToBrd. BrdNode Invalid! BrdNode:%d,BrdIID:%d\n", m_dwBrdNode, m_dwBrdIID));
	}

	return ;
}

void CTPMcuBrdReg::OnDaemonBrdReg( CMessage *const ptMsg, CApp* pcApp )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	TBrdPosition tPos;
	memset(&tPos, 0, sizeof(tPos));
	TP_SAFE_CAST(tPos, cServMsg.GetMsgBody());

	u8 byInsID = 1;
	if ( tPos.byBrdID == BRD_TYPE_HDU2 )
	{//电视墙 层和槽单独设置 从1开始
		byInsID += tPos.byBrdLayer*HDU_MAX_SLOT + tPos.byBrdSlot;
	}
	else 
	{//其他板子 层和槽都唯一 排在电视墙后面
		byInsID = HDU_MAX_NUM + 1 + tPos.byBrdLayer*TP_BOARD_MAX_SLOT + tPos.byBrdSlot;
	}

	CInstance* pcInst = pcApp->GetInstance(byInsID);
	if ( NULL != pcInst && 
		STATE_WAITREG == pcInst->CurState() )
	{
		((CTPMcuBrdReg*)pcInst)->PreMessageProc(ptMsg);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnDaemonBrdReg. Inst is null or Stat error! InstId:%d, brdId:%d, layer:%d, slot:%d.\n", 
			byInsID, tPos.byBrdID, tPos.byBrdLayer, tPos.byBrdSlot));
		::OspDisconnectTcpNode( ptMsg->srcnode );
	}

	return ;
}

void CTPMcuBrdReg::OnBrdReg( CMessage *const ptMsg )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 *pBuf = cServMsg.GetMsgBody();
	u16 wLen = cServMsg.GetMsgBodyLen();

	TBrdPosition tPos;
	memset(&tPos, 0, sizeof(tPos));
	TP_SAFE_CAST(tPos, pBuf);
	u32	dwIp = TP_INVALID_INDEX;
	TP_SAFE_CAST(dwIp, pBuf + sizeof(tPos));
	u8	byNetIndex;
	TP_SAFE_CAST( byNetIndex, pBuf + sizeof(tPos) + sizeof(dwIp));
	u8	byOsType;
	TP_SAFE_CAST( byOsType, pBuf + sizeof(tPos) + sizeof(dwIp) + sizeof(byNetIndex));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdReg. New Brd Reg! BrdIP:"TPIPFORMAT", NetIndx:%d, OsType:%d, (ID:%d,Layer:%d,Slot:%d)\n", 
							  Tpu32ToIP(dwIp), byNetIndex, byOsType, tPos.byBrdID, tPos.byBrdLayer, tPos.byBrdSlot));
	
	OspNodeDiscCBRegQ(ptMsg->srcnode, AID_UMSBRD_REG_APP, GetInsID());

	m_dwBrdNode = ptMsg->srcnode;
	m_dwBrdIID = ptMsg->srcid;

	//通知到Eqp
	TTPBrdRegInfo tBrdRegInfo;

	if ( tPos.byBrdID == BRD_TYPE_MPU2ECARD )
	{
		tBrdRegInfo.m_tBrdPos.m_emBrdType = em_mpu2ecard_brd;
	}
	else if( tPos.byBrdID == BRD_TYPE_HDU2 )
	{
		tBrdRegInfo.m_tBrdPos.m_emBrdType = em_hdu2_brd;
	}
	else if ( tPos.byBrdID == BRD_TYPE_APU2 )
	{
		tBrdRegInfo.m_tBrdPos.m_emBrdType = em_apu2_tp_brd;
	}
	else if ( tPos.byBrdID == BRD_TYPE_MPU2 )
	{
		tBrdRegInfo.m_tBrdPos.m_emBrdType = em_mpu2basic_brd;
	}
	else
	{
		//其他板子
		SendMsgToBrd(UMS_MPC_BOARD_REG_NACK);
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdReg. BrdID Invalid! BrdID:%d, Stat:%d\n", 
								tPos.byBrdID, CurState()));
		
		::OspDisconnectTcpNode( m_dwBrdNode );
		return ;
	}
	
	NextState(STATE_INIT);

	tBrdRegInfo.m_byNetIndx = byNetIndex;
	tBrdRegInfo.m_tBrdPos.m_byBrdLayer = tPos.byBrdLayer;
	tBrdRegInfo.m_tBrdPos.m_byBrdSlot = tPos.byBrdSlot;
	tBrdRegInfo.m_tBrdPos.m_dwBrdIP = dwIp;

	if ( byOsType == OS_TYPE_WIN32 )
	{
		tBrdRegInfo.m_emOsType = em_Win32_OsType;
	}
	else if(byOsType == OS_TYPE_LINUX)
	{
		tBrdRegInfo.m_emOsType = em_Linux_OsType;
	}

	SendMsgToUmsEqp(ev_TPBrdReg_Req, (u8*)&tBrdRegInfo, sizeof(tBrdRegInfo));	
}

void CTPMcuBrdReg::OnBrdRegAck( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_INIT )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdRegAck. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	BOOL32 bMpcEnable = TRUE;
	TBrdRegAck tRegAck;
	tRegAck.SetOtherMpcIp(0);// 没有主备
	tRegAck.SetOtherMpcPort(0);

	CServMsg cServMsg;
	cServMsg.SetMsgBody((u8*)&bMpcEnable, sizeof(bMpcEnable));
	cServMsg.CatMsgBody((u8*)&tRegAck, sizeof(tRegAck));

	SendMsgToBrd(UMS_MPC_BOARD_REG_ACK, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());

	return ;
}

void CTPMcuBrdReg::OnBrdGetCfgReq( CMessage *const ptMsg )
{//注意此处：mcu此条消息不是用CServMsg发的
	TBrdPos tPos;
	memset(&tPos, 0, sizeof(tPos));
	TP_SAFE_CAST(tPos, ptMsg->content);

	if ( CurState() != STATE_INIT || m_dwBrdNode == INVALID_NODE || 0 == m_dwBrdIID )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdGetCfgReq. Stat Invalid! InstID:%d, BrdIP:"TPIPFORMAT", (ID:%d,Layer:%d,Slot:%d)\n", 
								GetInsID(), Tpu32ToIP(OspNodeIpGet(ptMsg->srcnode)), tPos.byBrdID, 
								tPos.byBrdLayer, tPos.byBrdSlot));
		return ;
	}

	TTPBrdPos tTpPos;
	tTpPos.m_byBrdLayer = tPos.byBrdLayer;
	tTpPos.m_byBrdSlot = tPos.byBrdSlot;
	tTpPos.m_dwBrdIP = OspNodeIpGet(ptMsg->srcnode);
	
	if ( tPos.byBrdID == BRD_TYPE_MPU2ECARD )
	{
		tTpPos.m_emBrdType = em_mpu2ecard_brd;
	}
	else if ( tPos.byBrdID == BRD_TYPE_MPU2 )
	{
		tTpPos.m_emBrdType = em_mpu2basic_brd;
	}
	else if( tPos.byBrdID == BRD_TYPE_HDU2 )
	{
		tTpPos.m_emBrdType = em_hdu2_brd;
	}
	else if ( tPos.byBrdID == BRD_TYPE_APU2 )
	{
		tTpPos.m_emBrdType = em_apu2_tp_brd;
	}
	else
	{
		//其他板子
		SendMsgToBrd(UMS_MPC_BOARD_GET_CONFIG_NACK);
		::OspDisconnectTcpNode( m_dwBrdNode );
		return ;
	}

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdGetCfgReq. Brd Get Cfg!(Type:%d,Layer:%d,Slot:%d)\n", tPos.byBrdID, 
							  tPos.byBrdLayer, tPos.byBrdSlot));
	
	SendMsgToUmsEqp(ev_TPBrdGetCfg_Req, (u8*)&tTpPos, sizeof(tTpPos));

	return ;
}


void CTPMcuBrdReg::OnBrdSwitchNty( CMessage *const ptMsg )
{//注意此处：mcu此条消息不是用CServMsg发的
	TMcuBoardSwitchNty tMcuSwichNty;
	TP_SAFE_CAST(tMcuSwichNty, ptMsg->content);

	TBrdSwitchInfo tAck;
    tAck.m_wBrdIndex = ntohs(tMcuSwichNty.m_wBrdIndex);
	tAck.m_bSwitch = tMcuSwichNty.m_OnOff;

	MdlHint(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdSwitchNty. index:%d  switchtype:%d(0:telnet 1:ftp) onoff:%d\n", 
		                  tAck.m_wBrdIndex, tMcuSwichNty.m_byswtype, tAck.m_bSwitch));

	switch(tMcuSwichNty.m_byswtype)
	{
	case BOARD_SW_TELNET:
        tAck.m_emType = em_BoardSwitch_telnet;
		break;
	case BOARD_SW_FTP:
        tAck.m_emType = em_BoardSwitch_ftp;
		break;
    case BOARD_SW_ALL:
		tAck.m_emType = em_BoardSwitch_all;
		break;
	default :
	    return;
	}
	
	SendMsgToUmsEqp(ev_TPBrdSwitchTeltp_Ack, (u8*)&tAck, sizeof(TBrdSwitchInfo));	
	return ;
}


void CTPMcuBrdReg::OnBrdGetCfgAck( CTpMsg *const ptMsg )
{
	EMBrdType emBrdType = *(EMBrdType*)ptMsg->GetBody();
	u8 *pBuf = ptMsg->GetBody() + sizeof(emBrdType);
	u16 wDataSize = ptMsg->GetBodyLen() - sizeof(emBrdType);

	if ( CurState() != STATE_INIT )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdGetCfgAck. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	switch (emBrdType)
	{
	case em_mpu2ecard_brd:
	case em_mpu2basic_brd:
		{
			OnMpuGetCfgAck(pBuf, wDataSize);	
		}
		break;

	case em_hdu2_brd:
		{
			OnHduGetCfgAck(pBuf, wDataSize);
		}
		break;

	case em_apu2_tp_brd:
		{
			OnApu2GetCfgAck(pBuf, wDataSize);
		}
		break;

	//添加其他板子

	default:	
		{
			MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdGetCfgAck. Brd Type Invalid! Type:%d\n", emBrdType));
			SendMsgToBrd(UMS_MPC_BOARD_GET_CONFIG_NACK);
			::OspDisconnectTcpNode( m_dwBrdNode );
			return ;
		}
	}

	NextState(STATE_NORMAL);

	return ;
}



void CTPMcuBrdReg::OnSwitchTelnetFtpCmd( CTpMsg *const ptMsg )
{
	TBrdSwitchInfo *pSwtInfo = (TBrdSwitchInfo *)(ptMsg->GetBody());
    TMcuBoardSwitchInfo BoardSwitchInfo;
	
	BoardSwitchInfo.m_wBrdIndex = htons(pSwtInfo->m_wBrdIndex);
    BoardSwitchInfo.m_OnOff = 0;
	if (pSwtInfo->m_bSwitch)
	{
        BoardSwitchInfo.m_OnOff = 1;
	}
	
	switch(pSwtInfo->m_emType)
	{
	case em_BoardSwitch_telnet:
		BoardSwitchInfo.m_byswtype = BOARD_SW_TELNET;
		break;
		
	case em_BoardSwitch_ftp:
		BoardSwitchInfo.m_byswtype = BOARD_SW_FTP;
		break;
		
	case em_BoardSwitch_all:
		BoardSwitchInfo.m_byswtype = BOARD_SW_ALL;
		break;
		
	default:
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnApu2FtpTelNetSwitchCmd! switch type error\n"));
		return;
	};
	
	
	SendMsgToBrd(UMS_MPC_BOARD_FTP_TELNET_SWITCH, (u8 *)&BoardSwitchInfo, sizeof(TMcuBoardSwitchInfo));
	
	return ;
}



void CTPMcuBrdReg::OnMpuGetCfgAck(u8* pData, u16 wDataSize)
{
	TTPMpu2CfgAck* ptCfgAck = (TTPMpu2CfgAck*)(pData);
	
	TMpuEBapEVpuConfigAck tBrdAck;
	memset(&tBrdAck, 0, sizeof(tBrdAck));
	
	if( ptCfgAck->m_byEqpId != 0 )
	{
		tBrdAck.SetEqpId(ptCfgAck->m_byEqpId);
		tBrdAck.SetEqpRcvStartPort(ptCfgAck->m_wEqpRcvStartPort);
		
		//basic 模式 需要分配两个外设
		if ( ptCfgAck->m_byEqpId2 != 0 )
		{
			tBrdAck.SetEqpId2(ptCfgAck->m_byEqpId2);
			tBrdAck.SetEqpRcvStartPort2(ptCfgAck->m_wEqpRcvStartPort2);
		}
	}
	
	if ( ptCfgAck->m_byEqpMdlType == em_vmp_enhanced_eqp_mdl )
	{
		tBrdAck.SetEqpType(TYPE_MPU2VMP_ENHANCED);
	}
	else if ( ptCfgAck->m_byEqpMdlType == em_bas_enhanced_eqp_mdl )
	{
		tBrdAck.SetEqpType(TYPE_MPU2BAS_ENHANCED);
	}
	else if( ptCfgAck->m_byEqpMdlType == em_vmp_basic_eqp_mdl )
	{
		tBrdAck.SetEqpType(TYPE_MPU2VMP_BASIC);
	}
	else if(ptCfgAck->m_byEqpMdlType == em_bas_basic_eqp_mdl)
	{
		tBrdAck.SetEqpType(TYPE_MPU2BAS_BASIC);
	}
	else
	{

	}
	SendMsgToBrd(UMS_MPC_BOARD_GET_CONFIG_ACK, (u8*)&tBrdAck, sizeof(tBrdAck));
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnMpuGetCfgAck! InstID:%d, BrdNode:%d, EqpID1:%d, EqpID2:%d, MdlType:%d, EqpRcvStartPort:%d\n", 
						GetInsID(), m_dwBrdNode, tBrdAck.GetEqpId(), tBrdAck.GetEqpId2(), 
						tBrdAck.GetEqpType(), tBrdAck.GetEqpRcvStartPort()));
	return ;
}

void CTPMcuBrdReg::OnHduGetCfgAck(u8* pData, u16 wDataSize)
{
	THduCfgAck* ptHduCfgAck = (THduCfgAck*)pData;

	TEqpHduEntry tEntryInfo;
	tEntryInfo.SetDefaultEntParam(EQP_TYPE_TVWALL, GetLocalIP());
	tEntryInfo.SetEqpId(ptHduCfgAck->m_byEqpID);
	tEntryInfo.SetStartMode(ptHduCfgAck->GetStartMode());

	u8 byBuf[sizeof(u8*) + sizeof(TEqpHduEntry)] = {0};
	*byBuf = ptHduCfgAck->m_byEqpID;

	memcpy(byBuf+1, &tEntryInfo, sizeof(TEqpHduEntry));
	SendMsgToBrd(UMS_MPC_BOARD_GET_CONFIG_ACK, byBuf, sizeof(u8*) + sizeof(TEqpHduEntry));
}

void CTPMcuBrdReg::OnApu2GetCfgAck(u8* pData, u16 wDataSize)
{
	TTPApu2CfgAck* ptCfgAck = (TTPApu2CfgAck*)(pData);

	u16 byOffSet = 0;
	u8 byEqpType = EQP_TYPE_MIXER;
	
	u8 byBuf[sizeof(u8) + 4*(sizeof(u8) + sizeof(TEqpMixerEntry)) + sizeof(u8) + sizeof(TEqpMpuBasEntry)] = {0}; 
	//外设个数(u8) + 外设类型(u8) + TEqpMixerEntry + 外设类型 + TEqpMixerEntry
	
	memcpy(byBuf + byOffSet, &ptCfgAck->m_byEqpNum, sizeof(u8));
	byOffSet += sizeof(u8);

	u16 wIndex = 0;

	TEqpMixerEntry tEntryInfo;
	TEqpMpuBasEntry tBasEntry;
	for ( wIndex = 0; wIndex < ptCfgAck->m_byEqpNum; ++wIndex)
	{
		if ( ptCfgAck->m_atInfo[wIndex].m_emEqpType == em_audmix_mdl )
		{
			byEqpType = EQP_TYPE_MIXER;

			tEntryInfo.SetEqpId(ptCfgAck->m_atInfo[wIndex].m_byEqpId);
			tEntryInfo.SetMaxChnInGrp(ptCfgAck->m_atInfo[wIndex].m_byChanNum);
			tEntryInfo.SetEqpRecvPort(ptCfgAck->m_atInfo[wIndex].m_wEqpRcvStartPort);
			tEntryInfo.SetMcuRecvPort(ptCfgAck->m_atInfo[wIndex].m_wUmsRcvStartPort);
			
			memcpy(byBuf + byOffSet, &byEqpType, sizeof(u8));
			byOffSet += sizeof(u8);
			memcpy(byBuf + byOffSet, &tEntryInfo, sizeof(tEntryInfo));
			byOffSet += sizeof(TEqpMixerEntry);
		}
		else if( ptCfgAck->m_atInfo[wIndex].m_emEqpType == em_audbas_mdl )
		{
			byEqpType = EQP_TYPE_BAS;

			tBasEntry.SetEqpId(ptCfgAck->m_atInfo[wIndex].m_byEqpId);
			tBasEntry.SetEqpRecvPort(ptCfgAck->m_atInfo[wIndex].m_wEqpRcvStartPort);
			tBasEntry.SetMcuRecvPort(ptCfgAck->m_atInfo[wIndex].m_wEqpRcvStartPort);
			
			memcpy(byBuf + byOffSet, &byEqpType, sizeof(u8));
			byOffSet += sizeof(u8);
			memcpy(byBuf + byOffSet, &tBasEntry, sizeof(tBasEntry));
			byOffSet += sizeof(TEqpMpuBasEntry);
		}
		else
		{
			MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnApu2GetCfgAck EqpType Error ! InstID:%d, BrdNode:%d, EqpID:%d, EqpType:%d\n", 
					GetInsID(), m_dwBrdNode, ptCfgAck->m_atInfo[wIndex].m_byEqpId, ptCfgAck->m_atInfo[wIndex].m_emEqpType));
		}
	}

	SendMsgToBrd(UMS_MPC_BOARD_GET_CONFIG_ACK, byBuf, byOffSet);

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnApu2GetCfgAck! InstID:%d, BrdNode:%d, EqpNum:%d\n", GetInsID(), m_dwBrdNode, ptCfgAck->m_byEqpNum));
}

void CTPMcuBrdReg::OnBrdHDVersionRsp( CMessage *const ptMsg )
{
	TBrdPos tBrd;
	TP_SAFE_CAST(tBrd, ptMsg->content);
	u8* pbyVer = ptMsg->content + sizeof(TBrdPos);
	MdlLowHint(Ums_Mdl_Eqp, ("[CTPMcuBrdReg::OnBrdHDVersionRsp] BrdLayer:%d, BrdSlot:%d, HdVersion:%s\n",
								tBrd.byBrdLayer, tBrd.byBrdSlot, pbyVer));

	TBrdVersion tVer;
	tVer.m_wBrdIndex = FindBrdArrayIndex(tBrd.byBrdLayer, tBrd.byBrdSlot);
	memcpy(tVer.m_achBrdVer, pbyVer, sizeof(tVer.m_achBrdVer));
	if (tVer.m_wBrdIndex < 0 || tVer.m_wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnBrdHDVersionRsp. BrdIndex Invalid! Index:%d\n", tVer.m_wBrdIndex));
		return;
	}
	SendMsgToUmsEqp(ev_TPBrdHDVersion_Ack, (u8*)&tVer, sizeof(TBrdVersion));
}

void CTPMcuBrdReg::OnBrdSoftWareUpdateNtfy( CMessage *const ptMsg )
{
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	u8 *pBuf = cServMsg.GetMsgBody();
	u16 wLen = cServMsg.GetMsgBodyLen();

	u8 byIndex;
	TP_SAFE_CAST(byIndex, pBuf);
	u8 byFileNum;
	TP_SAFE_CAST(byFileNum, pBuf + sizeof(u8));
	u8 abySuc;
	TP_SAFE_CAST(abySuc,  pBuf + sizeof(u8) + sizeof(u8));

	MdlLowHint(Ums_Mdl_Eqp, ("[CTPMcuBrdReg::OnBrdSoftWareUpdateNtfy] byIndex:%d, byFileNum:%d, bySuc:%d.\n", byIndex, byFileNum, abySuc));
	
	BOOL32 bSuc = FALSE;
	if (abySuc == 1)
	{
		bSuc = TRUE;
	}
	SendMsgToUmsEqp(ev_TPBrdSoftWareUpdate_Ack, (u8*)&bSuc, sizeof(BOOL32));
}

void CTPMcuBrdReg::OnDisconnect( CMessage *const ptMsg )
{
	u32 dwNode = *(u32*)ptMsg->content;

	MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnDisconnectProc Brd Disconnect! Node:%d, InsID:%d\n", dwNode, GetInsID()));

	//通知BrdEqpSsn 板子掉线
	post(MAKEIID(AID_UMSBRD_SSN_APP, CInstance::DAEMON), OSP_DISCONNECT, (void*)&dwNode, sizeof(u32));

	InstClear();

	return ;
}

void CTPMcuBrdReg::OnMpuUpdate(CTpMsg* const ptMsg)
{//处理MPU2和HDU2板卡升级
	TBrdUpInfo tUpdate;
	TP_SAFE_CAST(tUpdate, ptMsg->GetBody());
	u8 byIndex = tUpdate.m_byIndex;
	u8 byFileNum = 1;
	u8 byFileLen = tUpdate.m_byNameLen;

	s8 szFile[256] = {0};
	memcpy(szFile, "/ramdisk/", sizeof("/ramdisk/"));
	strcat(szFile, tUpdate.m_szFileName);
	byFileLen = strlen(szFile);

	MdlHint(Ums_Mdl_Eqp, ("CTPMcuBrdReg::OnMpuUpdate update InstId:%d, index:%d, num:%d, len:%d, name:%s.\n", GetInsID(), byIndex, byFileNum, byFileLen, szFile));
	u8 abyBuf[sizeof(u8) * 3 + sizeof(s8)*256] = {0};
	memcpy(abyBuf, &byIndex, sizeof(u8));
	memcpy(abyBuf + sizeof(u8), &byFileNum, sizeof(u8));
	memcpy(abyBuf + 2*sizeof(u8), &byFileLen, sizeof(u8));
	memcpy(abyBuf + 3*sizeof(u8), szFile, sizeof(szFile));

	CServMsg cServMsg;
	cServMsg.SetMsgBody(abyBuf, sizeof(abyBuf));
	cServMsg.SetChnIndex(UPDATE_TOOLS); //mpu2升级后是否重启判断该字段
	SendMsgToBrd(UMS_MPC_BOARD_UPDATE_SOFTWARE_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
}

u16 CTPMcuBrdReg::FindBrdArrayIndex( u8 byLate, u8 bySlot )
{
	u16 wRetIndex = 0;
	if ((bySlot >= 0) && (bySlot < (NORMAL_BRD_UI_SLOT_DOWN_BOUNDS - 1)) )
	{
		wRetIndex = byLate * TP_BOARD_MAX_SLOT + (bySlot + 1);
	}
	else if ((bySlot >= NORMAL_BRD_UI_SLOT_DOWN_BOUNDS && (bySlot <= 14)))
	{
		wRetIndex = byLate * TP_BOARD_MAX_SLOT + (bySlot + 2);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("[CTPMcuBrdReg::FindBrdArrayIndex] ordinary BrdSlot invalid!\n"));
	}

	return wRetIndex;
}

//////////////////////////////////////////////////////////////////////////
//业务

BOOL CTPMcuBrdSsn::PreDaemonMessageProc( CMessage *const ptMsg )
{
	if ( ptMsg->event == OSP_DISCONNECT )
	{
		OnDisconnect(ptMsg);
		return TRUE;
	}

	return FALSE;
}

BOOL32 CTPMcuBrdSsn::PreMessageProc( CMessage *const ptMsg )
{
	u32 dwSrcID = ptMsg->srcid;
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->event;
	
	BOOL32 bProc = FALSE;

	if (AID_UMSEQP_APP != wSrcAppID && EQP_ID_HDU_BEG <= GetInsID() && GetInsID() <= EQP_ID_HDU_END)
	{
		bProc = TRUE;
		if (NULL != m_apServiceHandler[em_hdu_handler])
		{
			m_apServiceHandler[em_hdu_handler]->MsgFromServiceHandler(ptMsg, this);
		}
	}
	else if (AID_UMSEQP_APP != wSrcAppID && EQP_ID_AUD_MIX_BEG <= GetInsID() && GetInsID() <= EQP_ID_AUD_MIX_END)
	{
		bProc = TRUE;
		if (NULL != m_apServiceHandler[em_audmix_handler])
		{
			m_apServiceHandler[em_audmix_handler]->MsgFromServiceHandler(ptMsg, this);
		}
	}
	else if (AID_UMSEQP_APP != wSrcAppID && EQP_ID_AUD_BAS_BEG <= GetInsID() && GetInsID() <= EQP_ID_AUD_BAS_END)
	{
		bProc = TRUE;
		if (NULL != m_apServiceHandler[em_audbas_handler])
		{
			m_apServiceHandler[em_audbas_handler]->MsgFromServiceHandler(ptMsg, this);
		}
	}
	else if( wEvent >= EV_MCUVMP_BGN && wEvent <= EV_MCUVMP_END )
	{
		bProc = VmpMsgFromMcuBrdHandle(ptMsg);
	}
	else if( wEvent >= EV_UMS_MCUBAS_BGN && wEvent <= EV_UMS_MCUBAS_END )
	{
		bProc = BasMsgFromMcuBrdHandle(ptMsg);
	}

	return bProc;
}

void CTPMcuBrdSsn::MessageProc(CTpMsg *const ptMsg)
{
	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();
	
	BOOL32 bProc = FALSE;

	if ( wSrcAppID == AID_UMSEQP_APP )
	{//来自外设管理模块

		if (EQP_ID_HDU_BEG <= GetInsID() && GetInsID() <= EQP_ID_HDU_END)
		{
			if (NULL != m_apServiceHandler[em_hdu_handler])
			{
				bProc = m_apServiceHandler[em_hdu_handler]->MsgFromEqpHandler(ptMsg, this);
			}
		}
		else if ( EQP_ID_AUD_MIX_BEG <= GetInsID() && GetInsID() <= EQP_ID_AUD_MIX_END )
		{
			if (NULL != m_apServiceHandler[em_audmix_handler])
			{
				bProc = m_apServiceHandler[em_audmix_handler]->MsgFromEqpHandler(ptMsg, this);
			}
		}
		else if ( EQP_ID_AUD_BAS_BEG <= GetInsID() && GetInsID() <= EQP_ID_AUD_BAS_END )
		{
			if (NULL != m_apServiceHandler[em_audbas_handler])
			{
				bProc = m_apServiceHandler[em_audbas_handler]->MsgFromEqpHandler(ptMsg, this);
			}
		}
		else if( wEvent > ev_TPVmp_Begin && wEvent < ev_TPVmp_End )
		{
			bProc = VmpMsgFromUmsEqpHandle(ptMsg);
		}
		else if( wEvent > ev_TPBas_Begin && wEvent < ev_TPBas_End )
		{
			bProc = BasMsgFromUmsEqpHandle(ptMsg);
		}

		//通用消息
		if(!bProc)
		{
			switch( wEvent )
			{
			case ev_TPEqp_ChangeSndAddr_Req:
				OnEqpChangeSndAddr(ptMsg);
				bProc = TRUE;
				break;
			default:
				bProc = FALSE;
				break;
			}
		}

	}

	if ( !bProc )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::InstanceEntry. unknow src! InstID:%d, SrcAppID:%d, event:%d->%s\n", 
										GetInsID(), wSrcAppID, ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent())));
	}

	return ;
}

BOOL CTPMcuBrdSsn::ObjectInit(u32 wParam, u32 lParam)
{
	SetLogTitle("[CTPMcuBrdSsn]");
	return TRUE;
}

void CTPMcuBrdSsn::ObjectExit()
{

}

BOOL CTPMcuBrdSsn::DaemonObjectInit(u32 wParam, u32 lParam)
{
	SetLogTitle("[CTPMcuBrdSsn]");
	InstClear();

	CTPMcuBrdSsn* pcInst = NULL;
	for( u16 wIndex = 1; wIndex <= EQP_ID_TOTAL_END; wIndex ++ )
	{
		pcInst = (CTPMcuBrdSsn*)((CApp*)&g_cBrdSsnApp)->GetInstance(wIndex);
		if ( NULL != pcInst )
		{
			pcInst->InstClear();
		}
	}

	for (u16 wHandlerIndex = 0; wHandlerIndex < em_eqp_handler_end; ++wHandlerIndex)
	{
		m_apServiceHandler[wHandlerIndex] = NULL;
	}

	m_apServiceHandler[em_hdu_handler] = new CHduHandler();
	if (NULL == m_apServiceHandler[em_hdu_handler])
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::ObjectInit New HDU hanler failed.\n"));
		return FALSE;
	}
	

	m_apServiceHandler[em_audmix_handler] = new CAudMixHandler();
	if (NULL == m_apServiceHandler[em_audmix_handler])
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::ObjectInit New AudMixer handler failed.\n"));
		return FALSE;
	}

	m_apServiceHandler[em_audbas_handler] = new CAudBasHandler();
	if (NULL == m_apServiceHandler[em_audbas_handler])
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::ObjectInit New AudBas handler failed.\n"));
		return FALSE;
	}

	return TRUE;
}

void CTPMcuBrdSsn::InstClear()
{
	m_dwBrdNode = INVALID_NODE;
	m_dwBrdIID = 0;
	m_bInit = TRUE;
	NextState(STATE_WAITREG);
}

void CTPMcuBrdSsn::OnDisconnect( CMessage *const ptMsg )
{
	u32 dwNode = *(u32*)ptMsg->content;

	CTPMcuBrdSsn* pcInst = NULL;
	for( u16 wIndex = 1; wIndex <= EQP_ID_TOTAL_END; wIndex ++ )
	{
		pcInst = (CTPMcuBrdSsn*)((CApp*)&g_cBrdSsnApp)->GetInstance(wIndex);
		if ( NULL != pcInst && dwNode == pcInst->m_dwBrdNode )
		{
			pcInst->InstClear();
		}
	}

	return ;
}

void CTPMcuBrdSsn::SendMsgToUmsEqp( u16 wEvent, u8 * const pbyMsg, u16 wLen )
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSBRD_SSN_APP, GetInsID()), m_dwBrdNode);
	
	return ;
}

void CTPMcuBrdSsn::SendMsgToBrd( u16 wEvent, u8 * const pbyMsg, u16 wLen )
{
	if ( m_dwBrdNode != INVALID_NODE )
	{
		post(m_dwBrdIID, wEvent, pbyMsg, wLen, m_dwBrdNode);
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::SendMsgToBrd. BrdNode Invalid! BrdNode:%d,BrdIID:%d\n", m_dwBrdNode, m_dwBrdIID));
	}
	return ;
}

//////////////////////////////////////////////////////////////////////////
//Eqp通用
void CTPMcuBrdSsn::OnEqpChangeSndAddr( CTpMsg *const ptMsg )
{

// 音频bas走的audbashandle，没有切换状态，暂时去掉
// 	if ( CurState() != STATE_NORMAL )
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnEqpChangeSndAddr. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
// 		return ;
// 	}

	TBasSndAddr tSndAddr;
	TP_SAFE_CAST(tSndAddr, ptMsg->GetBody());

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnEqpChangeSndAddr. InsID:%d, EqpID:%d, NewIp:"TPIPFORMAT"\n", 
					GetInsID(), tSndAddr.m_byEqpID, Tpu32ToIP(tSndAddr.m_dwNewDsIP)));
	
	//此处不用转了，因为我们本来就是按照网络序储存的，而板子那边会转成主机序存起来的。
	u32 dwSendIP = /* htonl*/(tSndAddr.m_dwNewDsIP);
	SendMsgToBrd(UMS_MCU_EQP_MODSENDADDR_CMD, (u8*)&dwSendIP, sizeof(dwSendIP));

	return ;
}

//////////////////////////////////////////////////////////////////////////
//Vmp

BOOL32 CTPMcuBrdSsn::VmpMsgFromUmsEqpHandle( CTpMsg *const ptMsg )
{
	BOOL32 bProc = TRUE;

	switch( ptMsg->GetEvent() )
	{
	case ev_TPVmp_Reg_Ack:
		OnVmpRegAck(ptMsg);
		break;
	case ev_TPVmp_Reg_NAck:
		OnVmpRegNAck(ptMsg);
		break;
	case ev_TPVmp_StartMix_Req:
	case ev_TPVmp_ChangeMixParam_Req:
		OnVmpStartReq(ptMsg);
		break;
	case ev_TPVmp_StopMix_Req:
		OnVmpStopReq(ptMsg);
		break;
	case ev_TPVmp_StartStopChn_Req:
		OnStartStopChnReq(ptMsg);
		break;
	case ev_TPVmp_FastUpdate_Req:
		OnAskFrameEqpToVmp(ptMsg);
		break;
	case ev_TPVmp_SetMediaKey_Req:
		OnVmpQtSetMediaKey(ptMsg);
		break;
	default:
		bProc = FALSE;
		break;
	}

	return bProc;
}

BOOL32 CTPMcuBrdSsn::VmpMsgFromMcuBrdHandle( CMessage* const ptMsg )
{
	BOOL32 bProc = TRUE;
	
	switch( ptMsg->event )
	{
	case UMS_VMP_MCU_REGISTER_REQ:
		OnVmpReg(ptMsg);
		break;
	case UMS_VMP_MCU_VMPSTATUS_NOTIF:
		OnVmpStateNtfy(ptMsg);
		break;
	case UMS_VMP_MCU_STARTVIDMIX_ACK:
	case UMS_VMP_MCU_STARTVIDMIX_NACK:
	case UMS_VMP_MCU_STARTVIDMIX_NOTIF:
	case UMS_VMP_MCU_STOPVIDMIX_ACK:
	case UMS_VMP_MCU_STOPVIDMIX_NACK:
	case UMS_VMP_MCU_STOPVIDMIX_NOTIF:
	case UMS_VMP_MCU_CHANGEVIDMIXPARAM_ACK:
	case UMS_VMP_MCU_CHANGEVIDMIXPARAM_NACK:
	case UMS_VMP_MCU_CHANGESTATUS_NOTIF:
		OnVmpMixRetInfo(ptMsg);
		break;
	case UMS_VMP_MCU_NEEDIFRAME_CMD:
		OnAskFrameVmpToEqp(ptMsg);
		break;
	default:
		bProc = FALSE;
		break;
	}
	
	return bProc;
}

void CTPMcuBrdSsn::OnVmpReg( CMessage *const ptMsg )
{
	if ( CurState() != STATE_WAITREG )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpReg. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpRegReq tEqpReg;

	const u16 wMsgBodyLen = cServMsg.GetMsgBodyLen();
    memcpy(&tEqpReg, cServMsg.GetMsgBody(), min(sizeof(TPeriEqpRegReq), wMsgBodyLen));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpReg. Vmp Reg! EqpID:%d, InsID:%d, EqpType:%d, EqpIP:"TPIPFORMAT", EqpRcvStartPort:%d, Ver:%d\n", 
					tEqpReg.GetEqpId(), GetInsID(), tEqpReg.GetEqpType(), Tpu32ToIP(tEqpReg.GetPeriEqpIpAddr()), 
					tEqpReg.GetStartPort(), tEqpReg.GetVersion()));

	if ( tEqpReg.GetEqpId() != GetInsID() || tEqpReg.GetEqpType() != EQP_TYPE_VMP )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpReg. EqpID is Invalid!\n"));
		cServMsg.SetErrorCode(ERR_MCU_REGEQP_INVALID);
		post(ptMsg->srcid, ptMsg->event + 2, cServMsg.GetServMsg(),cServMsg.GetServMsgLen(), ptMsg->srcnode);
		
        ::OspDisconnectTcpNode(ptMsg->srcnode);
		return ;
	}

	m_dwBrdNode = ptMsg->srcnode;
	m_dwBrdIID = ptMsg->srcid;

	NextState(STATE_INIT);

	TTPVmpReg tTpVmpReg;
	tTpVmpReg.m_byEqpID = tEqpReg.GetEqpId();
	tTpVmpReg.m_dwEqpIPAddr = tEqpReg.GetPeriEqpIpAddr();
	tTpVmpReg.m_dwEqpPort = tEqpReg.GetStartPort();
	tTpVmpReg.m_dwEqpVer = tEqpReg.GetVersion();
//	tTpVmpReg.m_emEqpMdlType = em_vmp_enhanced_eqp_mdl;
//	if ( !tEqpReg.IsHDEqp() )
//	{
//		tTpVmpReg.m_emEqpMdlType = em_vmp_basic_eqp_mdl;
//	}

	SendMsgToUmsEqp(ev_TPVmp_Reg_Req, (u8*)&tTpVmpReg, sizeof(tTpVmpReg));

	return ;
}

void CTPMcuBrdSsn::OnVmpRegAck( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_INIT )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpRegAck. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	TTPVmpRegAck tAck;
	TUmsRSParam tRsParam;
	TP_SAFE_CAST(tAck, ptMsg->GetBody());
	TP_SAFE_CAST(tRsParam, ptMsg->GetBody() + sizeof(tAck));
	
	TPrsTimeSpan tPrsTimeSpan;
	tPrsTimeSpan.m_wFirstTimeSpan = htons(tRsParam.m_wFirstTimeSpan);
	tPrsTimeSpan.m_wSecondTimeSpan = htons(tRsParam.m_wSecondTimeSpan);
	tPrsTimeSpan.m_wThirdTimeSpan = htons(tRsParam.m_wThirdTimeSpan);
	tPrsTimeSpan.m_wRejectTimeSpan = htons(tRsParam.m_wRejectTimeSpan);
	
	TPeriEqpRegAck tPeriAck;
	tPeriAck.SetMcuIpAddr(ntohl(tAck.m_dwIpAddr));
	tPeriAck.SetMcuStartPort(tAck.m_wStartPort);
	tPeriAck.SetAnotherMpcIp(0);

	u16 wMTUSize = 0;//默认0，mpu2不使用

	CServMsg cServMsg;
	cServMsg.SetMsgBody((u8 *)&tPeriAck, sizeof(tPeriAck));
	cServMsg.CatMsgBody((u8 *)&tPrsTimeSpan, sizeof(tPrsTimeSpan));
	cServMsg.CatMsgBody((u8 *)&wMTUSize, sizeof(u16));

	SendMsgToBrd(UMS_MCU_VMP_REGISTER_ACK, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpRegAck. InsID:%d, UmsIp:"TPIPFORMAT", UmsStartPort:%d, PrsTime(%d,%d,%d,%d)\n", 
						GetInsID(), Tpu32ToIP(tPeriAck.GetMcuIpAddr()), tPeriAck.GetMcuStartPort(), 
						tPrsTimeSpan.m_wFirstTimeSpan, tPrsTimeSpan.m_wSecondTimeSpan, 
						tPrsTimeSpan.m_wThirdTimeSpan, tPrsTimeSpan.m_wRejectTimeSpan));

	NextState(STATE_NORMAL);
	
	return ;
}

void CTPMcuBrdSsn::OnVmpRegNAck( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_INIT )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpRegNAck. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	u16 wErrorCode = *(u16*)ptMsg->GetBody();

	CServMsg cServMsg;
	cServMsg.SetErrorCode(wErrorCode);

	SendMsgToBrd(UMS_MCU_VMP_REGISTER_NACK, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpRegNAck. InsID:%d, ErrorCode:%d\n", 
															GetInsID(), cServMsg.GetErrorCode()));

	NextState(STATE_WAITREG);

	return ;
}

void CTPMcuBrdSsn::OnVmpStateNtfy( CMessage *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpStateNtfy. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpStatus tStatus;
	memset( &tStatus,0,sizeof(TPeriEqpStatus) );
	const u16 wMsgBodyLen = cServMsg.GetMsgBodyLen();
    memcpy(&tStatus, cServMsg.GetMsgBody(), min(sizeof(TPeriEqpStatus), wMsgBodyLen));

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpStateNtfy. EqpID:%d, InsID:%d, EqpType:%d, VmpStyle:%d, Stat:%d, VmpChnNum:%d\n", 
		tStatus.GetEqpId(), GetInsID(), tStatus.GetEqpType(), tStatus.m_tStatus.tVmp.m_tVMPParam.GetVMPStyle(), 
		tStatus.m_tStatus.tVmp.m_byUseState, tStatus.m_tStatus.tVmp.m_byChlNum));
	
	TTPVmpStatNtfy tStatNtfy;
	tStatNtfy.m_byDecodeNum = tStatus.m_tStatus.tVmp.m_byChlNum;
	tStatNtfy.m_byEncodeNum = TP_VMP_MAX_OUT_CHN_NUM;
	tStatNtfy.m_byEqpID = tStatus.GetEqpId();
	tStatNtfy.m_byStat = tStatus.m_tStatus.tVmp.m_byUseState;
	tStatNtfy.m_byVMPStyle = tStatus.m_tStatus.tVmp.m_tVMPParam.GetVMPStyle();

	SendMsgToUmsEqp(ev_TPVmp_State_Nty, (u8*)&tStatNtfy, sizeof(tStatNtfy));

	return ;
}

void CTPMcuBrdSsn::OnVmpStartReq( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpStartReq. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	u8					byEqpID;
	TTPVMPParam			tParam;

	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST(tParam, ptMsg->GetBody() + sizeof(u8));

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpStartReq. InsID:%d, EqpID:%d, OutNum:%d\n", GetInsID(), byEqpID, tParam.m_byVmpOutMemberNum));

	TVmpCommonAttrb tCom;
	CKDVVMPOutMember atOut[MAXNUM_MPU2VMP_CHANNEL];
	memset(atOut, 0, sizeof(atOut));
	
	tCom.m_byMemberNum = tParam.m_byVMPMemberNum;
	tCom.m_byNeedPrs = 1;

	//值是一一对应的
	tCom.m_byVmpStyle = tParam.m_emVmpStyle;
	
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < min(MAXNUM_VMP_MEMBER, tParam.m_byVMPMemberNum); wIndex ++ )
	{
		if ( !TP_VALID_HANDLE(tParam.m_atVMPMember[wIndex].m_wEpID) )
		{//无效值设置为NULL
			tCom.m_atMtMember[wIndex].SetNull();
			if (emTPEncryptTypeAES == tParam.m_atVMPMember[wIndex].m_tEncrypt.m_emEncryptModel)
			{
				tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_AES);
				tCom.m_tVideoEncrypt[wIndex].SetEncryptKey((u8*)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_achEncKey, 
					(s32)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_byKeyLen);
			}
			else if (emTPEncryptTypeDES == tParam.m_atVMPMember[wIndex].m_tEncrypt.m_emEncryptModel)
			{
				tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_DES);
				tCom.m_tVideoEncrypt[wIndex].SetEncryptKey((u8*)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_achEncKey, 
					(s32)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_byKeyLen);
			}
			else if (tParam.m_atVMPMember[wIndex].m_tEncrypt.IsQt())
			{
				tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_QT);
				tCom.m_tVideoEncrypt[wIndex].SetEncryptKey(NULL, 0);
			}
			else
			{
				tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_NONE);
				tCom.m_tVideoEncrypt[wIndex].SetEncryptKey(NULL, 0);
			}
			continue;
		}

		tCom.m_atMtMember[wIndex].SetMcuId(byEqpID);
		tCom.m_atMtMember[wIndex].SetMtId((u8)tParam.m_atVMPMember[wIndex].m_wEpID);
		tCom.m_atMtMember[wIndex].SetMemStatus(tParam.m_atVMPMember[wIndex].m_byStat);
		
		//TMediaEncrypt
		if (emTPEncryptTypeAES == tParam.m_atVMPMember[wIndex].m_tEncrypt.m_emEncryptModel)
		{
			tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_AES);
			tCom.m_tVideoEncrypt[wIndex].SetEncryptKey((u8*)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_achEncKey, 
				(s32)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_byKeyLen);
		}
		else if (emTPEncryptTypeDES == tParam.m_atVMPMember[wIndex].m_tEncrypt.m_emEncryptModel)
		{
			tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_DES);
			tCom.m_tVideoEncrypt[wIndex].SetEncryptKey((u8*)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_achEncKey, 
				(s32)tParam.m_atVMPMember[wIndex].m_tEncrypt.m_byKeyLen);
		}
		else if (tParam.m_atVMPMember[wIndex].m_tEncrypt.IsQt())
		{
			tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_QT);
			tCom.m_tVideoEncrypt[wIndex].SetEncryptKey(NULL, 0);
		}
		else
		{
			tCom.m_tVideoEncrypt[wIndex].SetEncryptMode(CONF_ENCRYPTMODE_NONE);
			tCom.m_tVideoEncrypt[wIndex].SetEncryptKey(NULL, 0);
		}

		//载荷
		tCom.m_tDoublePayload[wIndex].SetActivePayload((u8)tParam.m_atVMPMember[wIndex].m_wDynamicPayload);
		tCom.m_tDoublePayload[wIndex].SetRealPayLoad((u8)tParam.m_atVMPMember[wIndex].m_wStaticPayload);
	}

	//画面风格
	tCom.m_tVmpStyleCfgInfo.SetSchemeId(0);							//方案ID mpu2侧没用
	tCom.m_tVmpStyleCfgInfo.SetSchemeAlias("网呈默认");				//方案别名 mpu2侧没用
	tCom.m_tVmpStyleCfgInfo.SetIsRimEnabled(0);						//默认不使用边框
	tCom.m_tVmpStyleCfgInfo.ResetDefaultColor();					//其他默认属性:背景、字体颜色等等
	tCom.m_tVmpExCfgInfo.m_byIdleChlShowMode = VMP_SHOW_LASTFRAME_MODE; //空闲通道 设置为最后一帧
	tCom.m_tVmpExCfgInfo.m_byIsDisplayMmbAlias = 1;					//默认不显示屏的名字

	u16 wVidH, wVidW;
	for ( wIndex = 0; wIndex < min(MAXNUM_MPU2VMP_CHANNEL, tParam.m_byVmpOutMemberNum); wIndex ++ )
	{

		atOut[wIndex].SetBitRate(tParam.m_atVMPOutMember[wIndex].m_wBitrate);
		atOut[wIndex].SetEncType(CTpTypeAdpt::GetVidPayloadValue(tParam.m_atVMPOutMember[wIndex].m_emFormat));
		atOut[wIndex].SetFrameRate((u8)tParam.m_atVMPOutMember[wIndex].m_wFrameRate);

		if ( tParam.m_atVMPOutMember[wIndex].m_emQualityLvl == emTPH264HP )
		{
			atOut[wIndex].SetProfileType(1);
		}
		else if( tParam.m_atVMPOutMember[wIndex].m_emQualityLvl == emTPH264BP )
		{
			atOut[wIndex].SetProfileType(0);
		}

		CTpTypeAdpt::GetWHByVidResolution(tParam.m_atVMPOutMember[wIndex].m_emRes, wVidW, wVidH);
 		//mpu2业务限制  必须按照1088下参
		if ( tParam.m_atVMPOutMember[wIndex].m_emRes == emTPVHD1080p1920x1080 )
		{
			wVidH = 1088;
 		}
		atOut[wIndex].SetVideoHeight(wVidH);
 		atOut[wIndex].SetVideoWidth(wVidW);

	}
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId(byEqpID);
	cServMsg.SetMsgBody((u8*)&tCom, sizeof(tCom));
	cServMsg.CatMsgBody((u8*)&atOut[0], sizeof(atOut));

	if ( ptMsg->GetEvent() ==  ev_TPVmp_StartMix_Req )
	{
		SendMsgToBrd( UMS_MCU_VMP_STARTVIDMIX_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	}
	else
	{
		SendMsgToBrd( UMS_MCU_VMP_CHANGEVIDMIXPARAM_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	}

	return ;
}

void CTPMcuBrdSsn::OnVmpMixRetInfo( CMessage *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	TTPVmpRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)GetInsID();
	tRetInfo.m_wErrCode = cServMsg.GetErrorCode();
	
	u16 wEvent;
	switch( ptMsg->event )
	{
	case UMS_VMP_MCU_STARTVIDMIX_ACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_STARTVIDMIX_ACK! EqpID:%d, ErrCode:%d\n", 
					tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_StartMix_Ack;
		}
		break;
	case UMS_VMP_MCU_STARTVIDMIX_NACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_STARTVIDMIX_NACK! EqpID:%d, ErrCode:%d\n", 
					tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_StartMix_NAck;
		}
		break;
	case UMS_VMP_MCU_STARTVIDMIX_NOTIF:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_STARTVIDMIX_NOTIF! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_StartMix_Ntfy;
		}
		break;
	case UMS_VMP_MCU_STOPVIDMIX_ACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_STOPVIDMIX_ACK! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_StopMix_Ack;
		}
		break;
	case UMS_VMP_MCU_STOPVIDMIX_NACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_STOPVIDMIX_NACK! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_StopMix_NAck;
		}
		break;
	case UMS_VMP_MCU_STOPVIDMIX_NOTIF:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_STOPVIDMIX_NOTIF! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_StopMix_Ntfy;
		}
		break;
	case UMS_VMP_MCU_CHANGEVIDMIXPARAM_ACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_CHANGEVIDMIXPARAM_ACK! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_ChangeMixParam_Ack;
		}
		break;
	case UMS_VMP_MCU_CHANGEVIDMIXPARAM_NACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_CHANGEVIDMIXPARAM_NACK! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_ChangeMixParam_NAck;
		}
		break;
	case UMS_VMP_MCU_CHANGESTATUS_NOTIF:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. UMS_VMP_MCU_CHANGESTATUS_NOTIF! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			wEvent = ev_TPVmp_ChangeMixParam_Ntfy;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpMixRetInfo. Event Not Find! EqpID:%d, ErrCode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_wErrCode));
			return ;
		}
		break;
	}
	
	SendMsgToUmsEqp(wEvent, (u8*)&tRetInfo, sizeof(tRetInfo));

	return ;
}

void CTPMcuBrdSsn::OnVmpStopReq( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpStopReq. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	u8	byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId(byEqpID);

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpStopReq. EqpID:%d, InstID:%d\n", byEqpID, GetInsID()));

	SendMsgToBrd( UMS_MCU_VMP_STOPVIDMIX_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());

	return ;
}

void CTPMcuBrdSsn::OnStartStopChnReq( CTpMsg *const ptMsg )
{//主控通知外设，打开或者关闭某通道

	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnStartStopChnReq. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	u8 byEqpID, byChnID, byAcitve;
	TP_SAFE_CAST( byEqpID, ptMsg->GetBody());
	TP_SAFE_CAST( byChnID, ptMsg->GetBody() + sizeof(u8));
	TP_SAFE_CAST( byAcitve, ptMsg->GetBody() + sizeof(u8) + sizeof(u8));

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnStartStopChnReq. Stat:%d, EqpID:%d, ChnID:%d, Acitve:%d\n", 
						CurState(), byEqpID, byChnID, byAcitve));

	if ( GetInsID() == byEqpID )
	{
		CServMsg cServMsg;
		cServMsg.SetChnIndex(byChnID);
		cServMsg.SetMsgBody((u8*)&byChnID, sizeof(u8));
		cServMsg.CatMsgBody((u8*)&byAcitve, sizeof(u8));
		
		SendMsgToBrd(UMS_MCU_VMP_STARTSTOPCHNNL_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	}

	return ;
}

void CTPMcuBrdSsn::OnAskFrameVmpToEqp( CMessage *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameVmpToEqp. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TTPVmpAskFrame tEqpFrame;
	tEqpFrame.m_byEqpID = (u8)GetInsID();
	tEqpFrame.m_byChanIndx = cServMsg.GetChnIndex();
	
	MdlLowDtl(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameVmpToEqp. BrdNode:%d, EqpID:%d, ChanIndx:%d\n", 
														m_dwBrdNode, GetInsID(), tEqpFrame.m_byChanIndx));

	SendMsgToUmsEqp(ev_TPVmp_FastUpdate_Req, (u8*)&tEqpFrame, sizeof(tEqpFrame));	
}

void CTPMcuBrdSsn::OnAskFrameEqpToVmp( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameEqpToVmp. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	TTPVmpAskFrame tAskFrame;
	TP_SAFE_CAST(tAskFrame, ptMsg->GetBody());
	MdlLowDtl(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameEqpToVmp. BrdNode:%d, EqpID:%d, ChanIndx:%d\n", 
														m_dwBrdNode, tAskFrame.m_byEqpID, tAskFrame.m_byChanIndx));
	
	CServMsg cServMsg;
	cServMsg.SetChnIndex(tAskFrame.m_byChanIndx);
	cServMsg.SetSrcSsnId((u8)GetInsID());
	
	SendMsgToBrd(UMS_MCU_VMP_FASTUPDATEPIC_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	
	return ;
}

//////////////////////////////////////////////////////////////////////////
//bas

BOOL32 CTPMcuBrdSsn::BasMsgFromUmsEqpHandle( CTpMsg *const ptMsg )
{
	BOOL32 bProc = TRUE;

	switch (ptMsg->GetEvent())
	{
	case ev_TPBas_Reg_Ack:
		OnBasRegAck(ptMsg);
		break;
	case ev_TPBas_Reg_NAck:
		OnBasRegNAck(ptMsg);
		break;
	case ev_TPBas_StartAdapter_Req:
	case ev_TPBas_SetAdapterParam_Req:
		OnBasStartReq(ptMsg);
		break;
	case ev_TPBas_StopAdapter_Req:
		OnBasStopReq(ptMsg);
		break;
	case ev_TPBas_FastUpdate_Req:
		OnAskFrameEqpToBas(ptMsg);
		break;

	case ev_TPBas_SetMediaKey_Req:
		OnBasQtSetMediaKey(ptMsg);
		break;

	default:
		bProc = FALSE;
		break;
	}
	return bProc;
}

BOOL32 CTPMcuBrdSsn::BasMsgFromMcuBrdHandle( CMessage* const ptMsg )
{
	BOOL32 bProc = TRUE;
	
	switch (ptMsg->event)
	{
	case UMS_BAS_MCU_REG_REQ:
		OnBasReg(ptMsg);
		break;
	case UMS_BAS_MCU_BASSTATUS_NOTIF:
		OnBasStateNtfy(ptMsg);
		break;
	case UMS_HDBAS_MCU_CHNNLSTATUS_NOTIF:
		OnBasChnStateNtfy(ptMsg);
		break;
	case UMS_HDBAS_MCU_STARTADAPT_ACK:
	case UMS_HDBAS_MCU_STARTADAPT_NACK:
	case UMS_HDBAS_MCU_STOPADAPT_ACK:
	case UMS_HDBAS_MCU_STOPADAPT_NACK:
		OnBasRetInfo(ptMsg);
		break;
	case UMS_BAS_MCU_NEEDIFRAME_CMD:
		OnAskFrameBasToEqp(ptMsg);
		break;
	default:
		bProc = FALSE;
		break;
	}
	
	return bProc;
}

void CTPMcuBrdSsn::OnBasReg( CMessage* const ptMsg )
{
	if ( CurState() != STATE_WAITREG )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasReg. InsStat Invalid! InstID:%d, SrcNode:%d, Stat:%d\n", GetInsID(), ptMsg->srcnode, CurState()));
		return ;
	}
	
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpRegReq tEqpReg;
	
	const u16 wMsgBodyLen = cServMsg.GetMsgBodyLen();
    memcpy(&tEqpReg, cServMsg.GetMsgBody(), min(sizeof(TPeriEqpRegReq), wMsgBodyLen));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasReg. Bas Reg! EqpID:%d, InsID:%d, EqpType:%d, EqpIP:"TPIPFORMAT", RcvStartPort:%d, Ver:%d, IsHd:%d.\n", 
		tEqpReg.GetEqpId(), GetInsID(), tEqpReg.GetEqpType(), Tpu32ToIP(tEqpReg.GetPeriEqpIpAddr()), 
		tEqpReg.GetStartPort(), tEqpReg.GetVersion(), tEqpReg.IsHDEqp()));
	
	if ( tEqpReg.GetEqpId() != GetInsID() || tEqpReg.GetEqpType() != EQP_TYPE_BAS )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasReg. EqpID is Invalid!\n"));
		cServMsg.SetErrorCode(ERR_MCU_REGEQP_INVALID);
		post(ptMsg->srcid, ptMsg->event + 2, cServMsg.GetServMsg(),cServMsg.GetServMsgLen(), ptMsg->srcnode);
		
        ::OspDisconnectTcpNode(ptMsg->srcnode);
		return ;
	}
	
	m_dwBrdNode = ptMsg->srcnode;
	m_dwBrdIID = ptMsg->srcid;
	
	NextState(STATE_INIT);
	
	TTPBasReg tTpBasReg;
	tTpBasReg.m_byEqpID = tEqpReg.GetEqpId();
	tTpBasReg.m_dwEqpIPAddr = tEqpReg.GetPeriEqpIpAddr();
	tTpBasReg.m_dwEqpPort = tEqpReg.GetStartPort();
	tTpBasReg.m_dwEqpVer = tEqpReg.GetVersion();
// 	tTpBasReg.m_emEqpMdlType = em_bas_basic_eqp_mdl;
// 	if ( tEqpReg.IsHDEqp() )
// 	{
// 		tTpBasReg.m_emEqpMdlType = em_bas_enhanced_eqp_mdl;
// 	}
	
	SendMsgToUmsEqp(ev_TPBas_Reg_Req, (u8*)&tTpBasReg, sizeof(tTpBasReg));
	
	return ;
}

void CTPMcuBrdSsn::OnBasRegAck( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_INIT )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRegAck. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	TTPBasRegAck tAck;
	TUmsRSParam tRsParam;
	TP_SAFE_CAST(tAck, ptMsg->GetBody());
	TP_SAFE_CAST(tRsParam, ptMsg->GetBody() + sizeof(tAck));
	
	TPrsTimeSpan tPrsTimeSpan;
	tPrsTimeSpan.m_wFirstTimeSpan = htons(tRsParam.m_wFirstTimeSpan);
	tPrsTimeSpan.m_wSecondTimeSpan = htons(tRsParam.m_wSecondTimeSpan);
	tPrsTimeSpan.m_wThirdTimeSpan = htons(tRsParam.m_wThirdTimeSpan);
	tPrsTimeSpan.m_wRejectTimeSpan = htons(tRsParam.m_wRejectTimeSpan);
	
	TPeriEqpRegAck tPeriAck;
	tPeriAck.SetMcuIpAddr(ntohl(tAck.m_dwIpAddr));
	tPeriAck.SetMcuStartPort(tAck.m_wStartPort);
	tPeriAck.SetAnotherMpcIp(0);

	TEqpBasHDCfgInfo tHdCfg;
	tHdCfg.SetEqpId(tAck.m_byEqpId);
	tHdCfg.SetEqpStartPort(tAck.m_wEqpStartPort);
	tHdCfg.SetAlias(tAck.m_szAlias);
	tHdCfg.SetType(TYPE_MPU2_ENHANCED);

	u16 wMTUSize = htons(0);			//默认0，mpu2不使用
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)GetInsID());
	cServMsg.SetMsgBody((u8 *)&tPeriAck, sizeof(tPeriAck));
	cServMsg.CatMsgBody((u8 *)&tPrsTimeSpan, sizeof(tPrsTimeSpan));
	cServMsg.CatMsgBody((u8 *)&wMTUSize, sizeof(u16));
	cServMsg.CatMsgBody((u8 *)&tHdCfg, sizeof(tHdCfg));
	
	SendMsgToBrd(UMS_MCU_BAS_REG_ACK, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRegAck. EqpID:%d, InsID:%d, UmsIp:"TPIPFORMAT", UmsPort:%d, EqpPort:%d, Alias:%s, Prs(%d,%d,%d,%d)\n", 
				tHdCfg.GetEqpId(), GetInsID(), Tpu32ToIP(tPeriAck.GetMcuIpAddr()), 
				tPeriAck.GetMcuStartPort(), tHdCfg.GetEqpStartPort(),
				tHdCfg.GetAlias(),
				tPrsTimeSpan.m_wFirstTimeSpan, tPrsTimeSpan.m_wSecondTimeSpan, 
				tPrsTimeSpan.m_wThirdTimeSpan, tPrsTimeSpan.m_wRejectTimeSpan));

	NextState(STATE_NORMAL);

	return ;
}

void CTPMcuBrdSsn::OnBasRegNAck( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_INIT )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRegNAck. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	u16 wErrorCode = *(u16*)ptMsg->GetBody();
	
	CServMsg cServMsg;
	cServMsg.SetErrorCode(wErrorCode);
	
	SendMsgToBrd(UMS_MCU_BAS_REG_NACK, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	
	NextState(STATE_WAITREG);
}

void CTPMcuBrdSsn::OnBasStateNtfy( CMessage *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasStateNtfy. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	TPeriEqpStatus tStatus;
	memset( &tStatus,0,sizeof(TPeriEqpStatus) );
	const u16 wMsgBodyLen = cServMsg.GetMsgBodyLen();
    memcpy(&tStatus, cServMsg.GetMsgBody(), min(sizeof(TPeriEqpStatus), wMsgBodyLen));
	
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasStateNtfy. EqpID:%d, InsID:%d, EqpAlias:%s\n", tStatus.GetEqpId(), GetInsID(), tStatus.GetAlias()));
	
	TTPBasStatNtfy tStatNtfy;
	tStatNtfy.m_byEqpID = tStatus.GetEqpId();
	tStatNtfy.SetAlias(tStatus.GetAlias());

	SendMsgToUmsEqp(ev_TPBas_State_Nty, (u8*)&tStatNtfy, sizeof(tStatNtfy));

	return ;
}

void CTPMcuBrdSsn::OnBasChnStateNtfy( CMessage *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasChnStateNtfy. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	u8  byChnType = *(u8*)cServMsg.GetMsgBody();
	THDBasChnStatus tChnStatus = *(THDBasChnStatus*)(cServMsg.GetMsgBody() + sizeof(u8));
    
	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasChnStateNtfy. InsID:%d, ChnType:%d, Status:%d, Reserved:%d, ChnIdx:%d, Type:%d\n", 
										GetInsID(), byChnType, tChnStatus.GetStatus(), tChnStatus.GetReservedType(), 
										tChnStatus.GetChnIdx(), tChnStatus.GetType()));

	TTPBasChnStatNtfy tChnNtfy;
	tChnNtfy.m_byEqpID = tChnStatus.GetEqp().GetEqpId();
	tChnNtfy.m_byChnIndx = tChnStatus.GetChnIdx();
	tChnNtfy.m_byStat = tChnStatus.GetStatus();
	
	SendMsgToUmsEqp(ev_TPBas_ChnState_Nty, (u8*)&tChnNtfy, sizeof(tChnNtfy));
	return ;
}

void CTPMcuBrdSsn::OnBasStartReq( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasStartReq. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	TStartBasAdapter tTpStart;
	TP_SAFE_CAST(tTpStart, ptMsg->GetBody());

	TTPBasVidParam tBasParam, tMaxBasParam;
	memcpy(&tMaxBasParam, &tTpStart.m_tMaxBasParam, sizeof(TTPBasVidParam));
	memcpy(&tBasParam, &tTpStart.m_tBasParam, sizeof(TTPBasVidParam));

	MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasStartReq. InsID:%d, ChnID:%d, Static:%d, Dynamic:%d, aud:%d\n", 
				GetInsID(), tTpStart.m_byChnID, tTpStart.m_wStaticPayload, tTpStart.m_wDynamicPayload, tTpStart.m_emAudForamt));
	MdlLowHint(Ums_Mdl_Eqp, ("======EncVidFmt===== MaxNum:%d, Num:%d \n", tMaxBasParam.m_byParamNum, tBasParam.m_byParamNum));
	MdlLowHint(Ums_Mdl_Eqp, ("Indx0, %s %s %d  --> %s %s %d\n", 
		UmsVidProfilePrint(tMaxBasParam.m_atVidParam[0].m_emQualityLvl),
		UmsVidResPrint(tMaxBasParam.m_atVidParam[0].m_emRes),
		tMaxBasParam.m_atVidParam[0].m_wFrameRate,
		UmsVidProfilePrint(tBasParam.m_atVidParam[0].m_emQualityLvl),
		UmsVidResPrint(tBasParam.m_atVidParam[0].m_emRes),
		tBasParam.m_atVidParam[0].m_wFrameRate));
	MdlLowHint(Ums_Mdl_Eqp, ("Indx1, %s %s %d  --> %s %s %d\n", 
		UmsVidProfilePrint(tMaxBasParam.m_atVidParam[1].m_emQualityLvl),
		UmsVidResPrint(tMaxBasParam.m_atVidParam[1].m_emRes),
		tMaxBasParam.m_atVidParam[1].m_wFrameRate,
		UmsVidProfilePrint(tBasParam.m_atVidParam[1].m_emQualityLvl),
		UmsVidResPrint(tBasParam.m_atVidParam[1].m_emRes),
		tBasParam.m_atVidParam[1].m_wFrameRate));
	MdlLowHint(Ums_Mdl_Eqp, ("Indx2, %s %s %d  --> %s %s %d\n", 
		UmsVidProfilePrint(tMaxBasParam.m_atVidParam[2].m_emQualityLvl),
		UmsVidResPrint(tMaxBasParam.m_atVidParam[2].m_emRes),
		tMaxBasParam.m_atVidParam[2].m_wFrameRate,
		UmsVidProfilePrint(tBasParam.m_atVidParam[2].m_emQualityLvl),
		UmsVidResPrint(tBasParam.m_atVidParam[2].m_emRes),
		tBasParam.m_atVidParam[2].m_wFrameRate));
	MdlLowHint(Ums_Mdl_Eqp, ("Indx3, %s %s %d  --> %s %s %d\n", 
		UmsVidProfilePrint(tMaxBasParam.m_atVidParam[3].m_emQualityLvl),
		UmsVidResPrint(tMaxBasParam.m_atVidParam[3].m_emRes),
		tMaxBasParam.m_atVidParam[3].m_wFrameRate,
		UmsVidProfilePrint(tBasParam.m_atVidParam[3].m_emQualityLvl),
		UmsVidResPrint(tBasParam.m_atVidParam[3].m_emRes),
		tBasParam.m_atVidParam[3].m_wFrameRate));
	MdlLowHint(Ums_Mdl_Eqp, ("Indx4, %s %s %d  --> %s %s %d\n", 
		UmsVidProfilePrint(tMaxBasParam.m_atVidParam[4].m_emQualityLvl),
		UmsVidResPrint(tMaxBasParam.m_atVidParam[4].m_emRes),
		tMaxBasParam.m_atVidParam[4].m_wFrameRate,
		UmsVidProfilePrint(tBasParam.m_atVidParam[4].m_emQualityLvl),
		UmsVidResPrint(tBasParam.m_atVidParam[4].m_emRes),
		tBasParam.m_atVidParam[4].m_wFrameRate));
	MdlLowHint(Ums_Mdl_Eqp, ("Indx5, %s %s %d  --> %s %s %d\n", 
		UmsVidProfilePrint(tMaxBasParam.m_atVidParam[5].m_emQualityLvl),
		UmsVidResPrint(tMaxBasParam.m_atVidParam[5].m_emRes),
		tMaxBasParam.m_atVidParam[5].m_wFrameRate,
		UmsVidProfilePrint(tBasParam.m_atVidParam[5].m_emQualityLvl),
		UmsVidResPrint(tBasParam.m_atVidParam[5].m_emRes),
		tBasParam.m_atVidParam[5].m_wFrameRate));
	MdlLowHint(Ums_Mdl_Eqp, ("======EncVidFmt=====\n"));

	CServMsg cServMsg;
	cServMsg.SetChnIndex(tTpStart.m_byChnID);
	cServMsg.SetSrcSsnId((u8)GetInsID());

	THDAdaptParam tFirstOutParam;
	THDAdaptParam tSecOutParam;
	
	u8 byIndx = 0;
	u16 wVidH, wVidW;
	for ( byIndx = 0; byIndx < tMaxBasParam.m_byParamNum; byIndx ++)
	{
		tFirstOutParam.Reset();
		
		//注意数组越界
		if( byIndx < TP_CONF_MAX_MINOR_VIDEO_RES_NUM )
		{
			//////////////////////////////////////////////////////////////////////////
			//目前 mpu2的适配 hp、bp只以tFirstOutParam为准，tSecOutParam设置无效
			tMaxBasParam.m_atVidParam[byIndx].m_emQualityLvl = tBasParam.m_atVidParam[byIndx].m_emQualityLvl;

			tFirstOutParam.SetFrameRate((u8)tMaxBasParam.m_atVidParam[byIndx].m_wFrameRate);
			if ( tMaxBasParam.m_atVidParam[byIndx].m_emQualityLvl == emTPH264HP )
			{
				tFirstOutParam.SetProfileType(1);
			}
			else if( tMaxBasParam.m_atVidParam[byIndx].m_emQualityLvl == emTPH264BP )
			{
				tFirstOutParam.SetProfileType(0);
			}
			tFirstOutParam.SetBitRate(tMaxBasParam.m_atVidParam[byIndx].m_wBitrate);
			
			CTpTypeAdpt::GetWHByVidResolution(tMaxBasParam.m_atVidParam[byIndx].m_emRes, wVidW, wVidH);
			tFirstOutParam.SetResolution(wVidW, wVidH);
			
			tFirstOutParam.SetIsNeedByPrs(TRUE);
			tFirstOutParam.SetVidType(CTpTypeAdpt::GetVidPayloadValue(tMaxBasParam.m_atVidParam[byIndx].m_emFormat));

			//H264固定为106  其他需要一定的算法转换，参考MCU代码
			tFirstOutParam.SetVidActiveType(MEDIA_TYPE_H264);
		}
		
		if ( byIndx == 0 )
		{
			cServMsg.SetMsgBody((u8*)&tFirstOutParam, sizeof(tFirstOutParam));
		}
		else
		{
			cServMsg.CatMsgBody((u8*)&tFirstOutParam, sizeof(tFirstOutParam));
		}
	}

	for ( byIndx = 0; byIndx < tBasParam.m_byParamNum; byIndx ++)
	{
		tSecOutParam.Reset();
		
		//注意数组越界
		if( byIndx < TP_CONF_MAX_MINOR_VIDEO_RES_NUM )
		{
			tSecOutParam.SetFrameRate((u8)tBasParam.m_atVidParam[byIndx].m_wFrameRate);
			if ( tBasParam.m_atVidParam[byIndx].m_emQualityLvl == emTPH264HP )
			{
				tSecOutParam.SetProfileType(1);
			}
			else if( tBasParam.m_atVidParam[byIndx].m_emQualityLvl == emTPH264BP )
			{
				tSecOutParam.SetProfileType(0);
			}
			tSecOutParam.SetBitRate(tBasParam.m_atVidParam[byIndx].m_wBitrate);

			CTpTypeAdpt::GetWHByVidResolution(tBasParam.m_atVidParam[byIndx].m_emRes, wVidW, wVidH);
			tSecOutParam.SetResolution(wVidW, wVidH);

			tSecOutParam.SetIsNeedByPrs(TRUE);
			tSecOutParam.SetVidType(CTpTypeAdpt::GetVidPayloadValue(tBasParam.m_atVidParam[byIndx].m_emFormat));

			//H264固定为106  其他需要一定的算法转换，参考MCU代码
			tSecOutParam.SetVidActiveType(MEDIA_TYPE_H264);
		}
		
		cServMsg.CatMsgBody((u8*)&tSecOutParam, sizeof(tSecOutParam));
	}

	TMediaEncrypt		tVideoEncrypt;  //视频加密参数
	TDoublePayload		tDoublePayload;	//双载荷
	tDoublePayload.SetActivePayload((u8)tTpStart.m_wDynamicPayload);
	tDoublePayload.SetRealPayLoad((u8)tTpStart.m_wStaticPayload);

	if (emTPEncryptTypeAES == tTpStart.m_tEncrypt.m_emEncryptModel)
	{
		tVideoEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_AES);
		tVideoEncrypt.SetEncryptKey((u8*)tTpStart.m_tEncrypt.m_achEncKey, (s32)tTpStart.m_tEncrypt.m_byKeyLen);
	}
	else if (emTPEncryptTypeDES == tTpStart.m_tEncrypt.m_emEncryptModel)
	{
		tVideoEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_DES);
		tVideoEncrypt.SetEncryptKey((u8*)tTpStart.m_tEncrypt.m_achEncKey, (s32)tTpStart.m_tEncrypt.m_byKeyLen);
	}
	else if ( tTpStart.m_tEncrypt.IsQt() )
	{
		tVideoEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_QT);
		tVideoEncrypt.SetEncryptKey(NULL, 0);
	}
	else
	{
		tVideoEncrypt.SetEncryptMode(CONF_ENCRYPTMODE_NONE);
		tVideoEncrypt.SetEncryptKey(NULL, 0);
	}

	//唇音同步
	u8 byAudType = CTpTypeAdpt::GetAudPayloadValue(tTpStart.m_emAudForamt);

	cServMsg.CatMsgBody((u8*)&tVideoEncrypt, sizeof(TMediaEncrypt));
	cServMsg.CatMsgBody((u8*)&tDoublePayload, sizeof(TDoublePayload));
	cServMsg.CatMsgBody((u8*)&byAudType, sizeof(u8));
	
	if ( ptMsg->GetEvent() ==  ev_TPBas_StartAdapter_Req )
	{
		SendMsgToBrd( UMS_MCU_HDBAS_STARTADAPT_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	}
	else
	{
		SendMsgToBrd( UMS_MCU_HDBAS_SETADAPTPARAM_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	}

	return ;
}

void CTPMcuBrdSsn::OnBasStopReq( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasStopReq. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	u8	byChnID;
	TP_SAFE_CAST(byChnID, ptMsg->GetBody());
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)GetInsID());
	cServMsg.SetChnIndex(byChnID);
	
	SendMsgToBrd( UMS_MCU_HDBAS_STOPADAPT_REQ, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	
	return ;
}

void CTPMcuBrdSsn::OnBasRetInfo( CMessage *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRetInfo. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	CServMsg cServMsg(ptMsg->content, ptMsg->length);
	
	TTPBasRetInfo tRetInfo;
	tRetInfo.m_byEqpID = (u8)GetInsID();
	tRetInfo.m_byChnID = cServMsg.GetChnIndex();

	u16 wEvent;
	switch( ptMsg->event )
	{
	case UMS_HDBAS_MCU_STARTADAPT_ACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRetInfo. UMS_HDBAS_MCU_STARTADAPT_ACK! EqpID:%d, ChnID:%d\n", 
																	tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
			wEvent = ev_TPBas_StartAdapter_Ack;
		}
		break;
	case UMS_HDBAS_MCU_STARTADAPT_NACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRetInfo. UMS_HDBAS_MCU_STARTADAPT_NACK! EqpID:%d, ChnID:%d, errorcode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_byChnID, cServMsg.GetErrorCode()));
			wEvent = ev_TPBas_StartAdapter_NAck;
		}
		break;
	case UMS_HDBAS_MCU_STOPADAPT_ACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRetInfo. UMS_HDBAS_MCU_STOPADAPT_ACK! EqpID:%d, ChnID:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
			wEvent = ev_TPBas_StopAdapter_Ack;
		}
		break;
	case UMS_HDBAS_MCU_STOPADAPT_NACK:
		{
			MdlLowHint(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRetInfo. UMS_HDBAS_MCU_STOPADAPT_NACK! EqpID:%d, ChnID:%d, errorcode:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_byChnID, cServMsg.GetErrorCode()));
			wEvent = ev_TPBas_StopAdapter_NAck;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasRetInfo. Event Not Find! EqpID:%d, ChnID:%d\n", 
				tRetInfo.m_byEqpID, tRetInfo.m_byChnID));
			return ;
		}
	}

	SendMsgToUmsEqp(wEvent, (u8*)&tRetInfo, sizeof(tRetInfo));

	return ;
}

void CTPMcuBrdSsn::OnAskFrameEqpToBas( CTpMsg *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameEqpToBas. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}

	TTPBasAskFrame tAsk;
	TP_SAFE_CAST(tAsk, ptMsg->GetBody());

	MdlLowDtl(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameEqpToBas. InsID:%d, EqpID:%d, ChnID:%d\n", 
																GetInsID(), tAsk.m_byEqpID, tAsk.m_byChanID));

	CServMsg cServMsg;
	cServMsg.SetSrcSsnId((u8)GetInsID());
	cServMsg.SetChnIndex(tAsk.m_byChanID);

	SendMsgToBrd(UMS_MCU_BAS_FASTUPDATEPIC_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());	

	return ;
}

void CTPMcuBrdSsn::OnAskFrameBasToEqp( CMessage *const ptMsg )
{
	if ( CurState() != STATE_NORMAL )
	{
		MdlError(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameBasToEqp. InsStat Invalid! InstID:%d, Stat:%d\n", GetInsID(), CurState()));
		return ;
	}
	
	CServMsg cServMsg(ptMsg->content, ptMsg->length);

	TTPBasAskFrame tEqpFrame;
	tEqpFrame.m_byEqpID = (u8)GetInsID();
	tEqpFrame.m_byChanID = cServMsg.GetChnIndex();
	
	MdlLowDtl(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnAskFrameBasToEqp. BrdNode:%d, EqpID:%d, ChanID:%d\n", 
													m_dwBrdNode, GetInsID(), tEqpFrame.m_byChanID));
	
	SendMsgToUmsEqp(ev_TPBas_FastUpdate_Req, (u8*)&tEqpFrame, sizeof(tEqpFrame));

	return ;
}

void CTPMcuBrdSsn::OnBasQtSetMediaKey( CTpMsg *const ptMsg )
{
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	TQTMediaKeyInfo tQTKeyInfo;
	tQTKeyInfo.SetHandle(tInfo.m_dwHandle);
	tQTKeyInfo.SetIndex(tInfo.m_wIndex);
	tQTKeyInfo.SetKeyFrequency(tInfo.m_emKeyFrequency);
	tQTKeyInfo.SetKeyLen(tInfo.m_dwKeyLen);
	tQTKeyInfo.SetQtFlag(tInfo.m_dwQtFlag);
	
	memcpy(tQTKeyInfo.m_szAlias, tInfo.m_szAlias, TP_MAX_ALIAS_LEN);
	
	memcpy(tQTKeyInfo.m_szMediaKey1, tInfo.m_szMediaKey, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey2, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey3, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey4, tInfo.m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	
	MdlLowDtl(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnBasQtSetMediaKey. BrdNode:%d, EqpID:%d, KeyLen:%d, QtFlag:%u, Freq:%d\n", 
		m_dwBrdNode, GetInsID(), tInfo.m_dwKeyLen, tInfo.m_dwQtFlag, tInfo.m_emKeyFrequency));
	
	CServMsg cServMsg;
	cServMsg.SetChnIndex(tInfo.m_dwHandle);
	cServMsg.SetMsgBody((u8 *)&tQTKeyInfo, sizeof(tQTKeyInfo));
	
	SendMsgToBrd( UMS_MCU_HDBAS_QTENCRYPT_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
	
}

void CTPMcuBrdSsn::OnVmpQtSetMediaKey( CTpMsg *const ptMsg )
{
	TTPQTMediaKeyInfo tInfo;
	TP_SAFE_CAST(tInfo, ptMsg->GetBody());
	
	MdlLowDtl(Ums_Mdl_Eqp, ("CTPMcuBrdSsn::OnVmpQtSetMediaKey. BrdNode:%d, EqpID:%d, KeyLen:%d, QtFlag:%u, Freq:%d\n", 
		m_dwBrdNode, GetInsID(), tInfo.m_dwKeyLen, tInfo.m_dwQtFlag, tInfo.m_emKeyFrequency));
	
	TQTMediaKeyInfo tQTKeyInfo;
	tQTKeyInfo.SetHandle(tInfo.m_dwHandle);
	tQTKeyInfo.SetIndex(tInfo.m_wIndex);
	tQTKeyInfo.SetKeyFrequency(tInfo.m_emKeyFrequency);
	tQTKeyInfo.SetKeyLen(tInfo.m_dwKeyLen);
	tQTKeyInfo.SetQtFlag(tInfo.m_dwQtFlag);
	
	memcpy(tQTKeyInfo.m_szAlias, tInfo.m_szAlias, TP_MAX_ALIAS_LEN);
	
	memcpy(tQTKeyInfo.m_szMediaKey1, tInfo.m_szMediaKey, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey2, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey3, tInfo.m_szMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tQTKeyInfo.m_szMediaKey4, tInfo.m_szMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	
	CServMsg cServMsg;
	cServMsg.SetSrcSsnId(tInfo.m_dwHandle);
	cServMsg.SetMsgBody((u8 *)&tQTKeyInfo, sizeof(tQTKeyInfo));
	
	SendMsgToBrd( UMS_MCU_VMP_SETQTMEDIAKEY_CMD, cServMsg.GetServMsg(), cServMsg.GetServMsgLen());
}

