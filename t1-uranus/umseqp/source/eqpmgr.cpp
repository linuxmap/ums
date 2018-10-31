#include "eqpmgr.h"
#include "eqpinst.h"
#include "vmpeqp.h"
#include "baseqp.h"
#include "mpceqp.h"
#include "mediatranseqp.h"
#include "adaptereqp.h"
#include "innereventumsboard.h"
#include "eventoutumseqp.h"
#include "umsapi.h"
#include "umsxmltype.h"
#include "eventoutumscommonbrd.h"

CEqpMgr::CEqpMgr()
{
	memset(m_atBrdEntry, 0, sizeof(m_atBrdEntry));

// 	TTPBrdPos tPos;
// 	tPos.m_byBrdLayer = 0;
// 	tPos.m_byBrdSlot = 2;
// 	u16 wIndex = FindBrdArrayIndex(tPos);
// 	if (TP_INVALID_INDEX == wIndex)
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo count brd array index invalid.\n"));
// 		return ;
//  	}
// 	m_atBrdEntry[wIndex].m_bUsed = TRUE;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_byBrdID = (u8)wIndex;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 0;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot = 2;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType = em_mpu2_tp_brd;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP = inet_addr("172.16.216.10");
// 	
// 	m_atBrdEntry[wIndex].m_byEqpNum = 1;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_byEqpID = 100;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_emEqpType = em_vmp_tp_mdl;
// 
// 	tPos.m_byBrdLayer = 0;
// 	tPos.m_byBrdSlot = 8;
// 	wIndex = FindBrdArrayIndex(tPos);
// 	if (TP_INVALID_INDEX == wIndex)
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo count brd array index invalid.\n"));
// 		return ;
// 	}
// 	m_atBrdEntry[wIndex].m_bUsed = TRUE;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_byBrdID = (u8)wIndex;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 0;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot = 8;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType = em_mpu2_tp_brd;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP = inet_addr("172.16.216.143");
// 	
// 	m_atBrdEntry[wIndex].m_byEqpNum = 1;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_byEqpID = 101;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_emEqpType = em_vmp_tp_mdl;
// 
// 
// 	tPos.m_byBrdLayer = 0;
// 	tPos.m_byBrdSlot = 12;
// 	wIndex = FindBrdArrayIndex(tPos);
// 	if (TP_INVALID_INDEX == wIndex)
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo count brd array index invalid.\n"));
// 		return ;
// 	}
// 	m_atBrdEntry[wIndex].m_bUsed = TRUE;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_byBrdID = (u8)wIndex;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 0;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot = 12;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType = em_eapu_brd;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP = inet_addr("172.16.40.56");
// 
// 	m_atBrdEntry[wIndex].m_byEqpNum = 4;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_byEqpID = 141;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_emEqpType = em_audmix_mdl;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_byAudmixNum = 34;
// 
// 	m_atBrdEntry[wIndex].m_atEqpCfg[1].m_byEqpID = 142;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[1].m_emEqpType = em_audmix_mdl;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[1].m_byAudmixNum = 10;
// 
// 	m_atBrdEntry[wIndex].m_atEqpCfg[2].m_byEqpID = 143;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[2].m_emEqpType = em_audmix_mdl;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[2].m_byAudmixNum = 10;
// 	
//  	m_atBrdEntry[wIndex].m_atEqpCfg[3].m_byEqpID = 144;
//  	m_atBrdEntry[wIndex].m_atEqpCfg[3].m_emEqpType = em_audmix_mdl;
//  	m_atBrdEntry[wIndex].m_atEqpCfg[3].m_byAudmixNum = 10;
// 
// 
// 	tPos.m_byBrdLayer = 0;
// 	tPos.m_byBrdSlot = 13;
// 	wIndex = FindBrdArrayIndex(tPos);
// 	if (TP_INVALID_INDEX == wIndex)
// 	{
// 		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo count brd array index invalid.\n"));
// 		return ;
// 	}
// 	m_atBrdEntry[wIndex].m_bUsed = TRUE;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_byBrdID = (u8)wIndex;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer = 0;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot = 13;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType = em_eapu_brd;
// 	m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP = inet_addr("172.16.40.56");
// 	
// 	m_atBrdEntry[wIndex].m_byEqpNum = 4;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_byEqpID = 145;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_emEqpType = em_audmix_mdl;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[0].m_byAudmixNum = 34;
// 	
// 	m_atBrdEntry[wIndex].m_atEqpCfg[1].m_byEqpID = 146;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[1].m_emEqpType = em_audmix_mdl;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[1].m_byAudmixNum = 10;
// 	
// 	m_atBrdEntry[wIndex].m_atEqpCfg[2].m_byEqpID = 147;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[2].m_emEqpType = em_audmix_mdl;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[2].m_byAudmixNum = 10;
// 	
// 	m_atBrdEntry[wIndex].m_atEqpCfg[3].m_byEqpID = 148;
// 	m_atBrdEntry[wIndex].m_atEqpCfg[3].m_emEqpType = em_audmix_mdl;
//  	m_atBrdEntry[wIndex].m_atEqpCfg[3].m_byAudmixNum = 10;

}

CEqpMgr::~CEqpMgr()
{
	memset(m_atBrdEntry, 0, sizeof(m_atBrdEntry));
}

BOOL32 CEqpMgr::CheckBrdInfo( TTPBrdRegInfo *const ptBrdInfo, u32 dwNode, u32 dwIns)
{
	if ( NULL == ptBrdInfo )
	{
		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo. ptBrdInfo is NULL!\n"));
		return FALSE;
	}

	if ( ptBrdInfo->m_tBrdPos.m_byBrdLayer >= TP_BOARD_MAX_LAYER ||
		 ptBrdInfo->m_tBrdPos.m_byBrdSlot >= TP_BOARD_MAX_SLOT)
	{
		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo. Brd positon Invalid! layer:%d, slot:%d.\n", 
								ptBrdInfo->m_tBrdPos.m_byBrdLayer,
								ptBrdInfo->m_tBrdPos.m_byBrdSlot));
		return FALSE;
	}

	u16 wIndex = FindBrdArrayIndex(ptBrdInfo->m_tBrdPos);

	if (TP_INVALID_INDEX == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo count brd array index invalid.\n"));
		return FALSE;
	}
	if ( !m_atBrdEntry[wIndex].m_bUsed )
	{
		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo. Brd not Exists! index:%d, used:%d\n", 
								wIndex, m_atBrdEntry[wIndex].m_bUsed));
		return FALSE;
	}

	if (!(m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos == ptBrdInfo->m_tBrdPos))
	{
		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo. Brd  is repeat!! RegBrdInfo<BrdType:%d, Layer:%d, Slot:%d, IP:"IPFORMAT">, BrdCfgInfo<Index:%d, BrdType:%d, Layer:%d, Slot:%d, Ip:"TPIPFORMAT">.\n",
			ptBrdInfo->m_tBrdPos.m_emBrdType,
			ptBrdInfo->m_tBrdPos.m_byBrdLayer,
			ptBrdInfo->m_tBrdPos.m_byBrdSlot,
			Tpu32ToIP(ptBrdInfo->m_tBrdPos.m_dwBrdIP),
			wIndex,
			m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType, 
			m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer, 
			m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot,
			Tpu32ToIP(m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP)));
		return FALSE;
	}

	if ( m_atBrdEntry[wIndex].m_bBrdState )
	{
		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo. Brd Already OnLine! Index:%d, CurNode:%d, NewNode:%d\n", 
								wIndex, m_atBrdEntry[wIndex].m_dwBrdNode, dwNode));
		
		::OspDisconnectTcpNode(m_atBrdEntry[wIndex].m_dwBrdNode);
		BrdDisConnect(m_atBrdEntry[wIndex].m_dwBrdNode);//已经在线 做掉线处理 保证新的注册能注册上

		return FALSE;
	}
	
	if ( m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos == ptBrdInfo->m_tBrdPos )
	{//该位置已经配置并且ip一致
		m_atBrdEntry[wIndex].m_bBrdState = TRUE;//上线
		m_atBrdEntry[wIndex].m_dwBrdNode = dwNode;
		m_atBrdEntry[wIndex].m_emOSType = ptBrdInfo->m_emOsType;
		m_atBrdEntry[wIndex].m_dwBrdIns = dwIns;

		
		//通知service的信息
// 		TBrdStateInfo tBrdReg;
// 		tBrdReg.m_wIndex = wIndex;
// 		tBrdReg.m_bReg = m_atBrdEntry[wIndex].m_bBrdState;
// 		NotifyBrdInfoToService(ev_board_reg_result, (u8*)&tBrdReg, sizeof(TBrdStateInfo));
		
		return TRUE;
	}
	else
	{
		MdlError(Ums_Mdl_Eqp, ("CheckBrdInfo. Fail! RegBrdInfo<BrdType:%d, Layer:%d, Slot:%d, IP:"IPFORMAT">, BrdCfgInfo<Index:%d, BrdType:%d, Layer:%d, Slot:%d, Ip:"TPIPFORMAT">.\n",
								ptBrdInfo->m_tBrdPos.m_emBrdType,
								ptBrdInfo->m_tBrdPos.m_byBrdLayer,
								ptBrdInfo->m_tBrdPos.m_byBrdSlot,
								Tpu32ToIP(ptBrdInfo->m_tBrdPos.m_dwBrdIP),
								wIndex,
								m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType, 
								m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer, 
								m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot,
								Tpu32ToIP(m_atBrdEntry[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP)));
		return FALSE;
	}
}

u16 CEqpMgr::GetBrdIndex(u8 byBrdLayer, u8 byBrdSlot)
{
	return (byBrdLayer * TP_BOARD_MAX_SLOT + byBrdSlot);
}

void CEqpMgr::Handle(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	
	switch (wEvent)
	{
	case ev_board_cfg_info:
		{
			EventBrdCfgInfo(ptMsg);
		}
		break;
	case ev_board_del_nty:
		{
			EventDelHandle(ptMsg);
		}
		break;
	case ev_board_modify_nty:
		{
			EventModifyHandle(ptMsg);
		}
		break;
	case  ev_board_mode_del_nty:
		{
			EventMdlDelHandle(ptMsg);
		}
		break;
	case  ev_board_mode_modify_nty:
		{
			EventMdlModifyHandle(ptMsg);
		}
		break;;
	case ev_board_reboot_req:
		{
			EventReboot(ptMsg);
		}
		break;
	case ev_board_upgrade_req:
		{
			EventUpGrade(ptMsg);
		}
		break;
	case ev_board_used_req:
		{
			EventEqpUsedReq(ptMsg);
		}
		break;
	case ev_TPBrdHDVersion_Ack:
		{
			EventHardVerAck(ptMsg);
		}
		break;
	case ev_TPBrdSoftWareUpdate_Ack:
		{
			EventUpdateAck(ptMsg);
		}
		break;
	case ev_board_switchtelnetftp_req:
		{
			EventSwitchTelnetFtp(ptMsg);
		}
		break;
	case ev_TPBrdSwitchTeltp_Ack:
		{
			EventSwitchTelFtpAck(ptMsg);
		}
		break;
	default:
		break;
	}
}

void CEqpMgr::Init(CUmsEqpInst* pEqpInst)
{
	m_pcEqpInst = pEqpInst;
}

EMEqpType CEqpMgr::BrdDisConnect( u32 dwBrdNode )
{
	TBrdEntry* ptBrdCfg = NULL;
	EMEqpType emType = em_unknow_mdl;

	u16 wEqpNum = 0;

	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex ++ )
	{
		ptBrdCfg = &m_atBrdEntry[wIndex];
		if ( ptBrdCfg == NULL || ptBrdCfg->m_dwBrdNode != dwBrdNode )
		{
			continue;
		}

		wEqpNum = ptBrdCfg->m_byEqpNum;
		
		TBrdStateInfo tBrdState;
		for (u16 wEqpIndx = 0; wEqpIndx < wEqpNum; wEqpIndx ++ )
		{//当前配置的外设
			CEqpBase* pcEqp = m_pcEqpInst->GetEqp(ptBrdCfg->m_atEqpCfg[wEqpIndx].m_emEqpType);
			if (NULL == pcEqp)
			{
				MdlError(Ums_Mdl_Eqp, ("BrdDisConnect. pcEqp is null. EqpIndex:%d \n", wEqpIndx));
				// return emType;  返回 可能会导致下面板子信息清不掉
				continue;
			}

			//通知外设断链
			if (pcEqp->OnDisConnect(ptBrdCfg->m_dwBrdNode))
			{
				tBrdState.m_abEqpReg[wEqpIndx] = FALSE;
				emType = ptBrdCfg->m_atEqpCfg[wEqpIndx].m_emEqpType;

				if (ptBrdCfg->m_bMdlDel)
				{
					ptBrdCfg->m_byEqpNum--;
					ptBrdCfg->BrdMdlDel(wEqpIndx);
				}
			}
		}

		if (ptBrdCfg->m_bBrdDel)
		{
			ptBrdCfg->BrdClear(); //清板子基本信息
		}

		ptBrdCfg->BrdDisConnect();

		tBrdState.m_wIndex = wIndex;
		tBrdState.m_bReg = ptBrdCfg->m_bBrdState;
		tBrdState.m_bUsed = FALSE;
		//通知service单板断链状态信息
		NotifyBrdInfoToService(ev_board_disc_nty, (u8*)&tBrdState, sizeof(TBrdStateInfo));
		
		return emType;
	}

	MdlError(Ums_Mdl_Eqp, ("BrdDisConnect. Brd not Find! dwNode:%d\n", dwBrdNode));
	return emType;
}

TBrdEntry* CEqpMgr::GetBrdCfg( const TTPBrdPos& tBrdPos )
{
	TBrdEntry* ptBrdCfg = NULL;
	for ( u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex ++ )
	{
		ptBrdCfg = &m_atBrdEntry[wIndex];
		if ( ptBrdCfg->m_tBrdCfg.m_tBrdPos == tBrdPos && ptBrdCfg->m_bUsed )
		{
			return ptBrdCfg;
		}
	}
	
	return NULL;
}

TBrdEntry* CEqpMgr::GetBrdCfg(const u8 byLayer, const u8 bySlot, const EMBrdType emType)
{
	TBrdEntry* ptBrdCfg = NULL;
	for ( u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex ++ )
	{
		ptBrdCfg = &m_atBrdEntry[wIndex];
		if (ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdLayer == byLayer && 
			ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdSlot == bySlot &&
			ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_emBrdType == emType)
		{
			return ptBrdCfg;
		}
	}
	
	return NULL;
}

TBrdEntry* CEqpMgr::GetBrdCfg( u32 dwBrdIP )
{
	TBrdEntry* ptBrdCfg = NULL;
	for ( u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex ++ )
	{
		ptBrdCfg = &m_atBrdEntry[wIndex];
		if (ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_dwBrdIP == dwBrdIP)
		{
			return ptBrdCfg;
		}
	}
	
	return NULL;
}

TTPEqpCfg* CEqpMgr::GetEqpCfgByEqpID( u8 byEqpID )
{
	TBrdEntry* ptBrdCfg = NULL;

	for ( u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex ++ )
	{
		ptBrdCfg = &m_atBrdEntry[wIndex];
		for (u16 wEqpIndx = 0; wEqpIndx < ptBrdCfg->m_byEqpNum; wEqpIndx ++ )
		{//当前配置的外设
			if(ptBrdCfg->m_atEqpCfg[wEqpIndx].m_byEqpID == byEqpID)
			{
				return &ptBrdCfg->m_atEqpCfg[wEqpIndx];
			}
		}
	}

	return NULL;
}

void CEqpMgr::EventBrdCfgInfo(CTpMsg* const ptMsg)
{
	TTPBrdInfo tBrdInfo;
	TP_SAFE_CAST(tBrdInfo, ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventBrdCfgInfo] Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n", tBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer,
							tBrdInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdInfo.m_tBrdCfg.m_tBrdPos.m_dwBrdIP)));

	u16 wBrdIndex = FindBrdArrayIndex(tBrdInfo.m_tBrdCfg.m_tBrdPos);
	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventBrdCfgInfo] BrdIndex invalid. BrdIndex:%d.\n", wBrdIndex));
		return;
	}
	if ((em_unknow_brd == tBrdInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType) && (0 == tBrdInfo.m_tBrdCfg.m_tBrdPos.m_dwBrdIP))
	{//单板未配过
		m_atBrdEntry[wBrdIndex].m_bUsed = FALSE;
	}
	else
	{
		m_atBrdEntry[wBrdIndex].m_bUsed = TRUE;
	}

	//添加板子时还在线，则需要先断链处理
	if ( m_atBrdEntry[wBrdIndex].m_dwBrdNode != INVALID_NODE )
	{
		//在线,重启
		m_pcEqpInst->SendToBrd(m_atBrdEntry[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdReboot_Cmd, 
											m_atBrdEntry[wBrdIndex].m_dwBrdIns, m_atBrdEntry[wBrdIndex].m_dwBrdNode);
	}

	m_atBrdEntry[wBrdIndex].SetBrdCfg(tBrdInfo.m_tBrdCfg);

	//防止越界
	m_atBrdEntry[wBrdIndex].m_byEqpNum = 0;
	for (u16 wMdlIndex = 0; wMdlIndex < TP_UMS_BRD_MAXNUM_EQP; wMdlIndex++)
	{
		m_atBrdEntry[wBrdIndex].SetMdlCfg(wMdlIndex, tBrdInfo.m_tBrdMode[wMdlIndex]);
		if (em_unknow_mdl == m_atBrdEntry[wBrdIndex].m_atEqpCfg[wMdlIndex].m_emEqpType)
		{
			continue;
		}
		m_atBrdEntry[wBrdIndex].m_byEqpNum++;
	}
}

void CEqpMgr::EventDelHandle(CTpMsg* const ptMsg)
{
	u16 wBrdIndex;
	TP_SAFE_CAST(wBrdIndex, ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("CEqpMgr::EventDelHandle wBrdIndex:%d.\n", wBrdIndex));

	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventDelHandle] BrdIndex invalid. BrdIndex:%d.\n", wBrdIndex));
		return;
	}
	if (m_atBrdEntry[wBrdIndex].m_bBrdState)
	{
		if (INVALID_NODE == m_atBrdEntry[wBrdIndex].m_dwBrdNode)
		{
			MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventDelHandle] BrdNode is invalid node. BrdIndex:%d.\n", wBrdIndex));
			return;
		}
		m_atBrdEntry[wBrdIndex].m_bBrdDel = TRUE;
		//在线,重启
		m_pcEqpInst->SendToBrd(m_atBrdEntry[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdReboot_Cmd, 
											m_atBrdEntry[wBrdIndex].m_dwBrdIns, m_atBrdEntry[wBrdIndex].m_dwBrdNode);
		//单板在线,断链处理
		//::OspDisconnectTcpNode(m_atBrdEntry[wBrdIndex].m_dwBrdNode);
	}
	else
	{
		m_atBrdEntry[wBrdIndex].BrdClear();
	}
}

void CEqpMgr::EventModifyHandle(CTpMsg* const ptMsg)
{
	TTPBrdCfg tBrdInfo = *(TTPBrdCfg*)ptMsg->GetBody();
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventModifyHandle] Type:%d, Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n", tBrdInfo.m_tBrdPos.m_emBrdType, 
		tBrdInfo.m_tBrdPos.m_byBrdLayer, tBrdInfo.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdInfo.m_tBrdPos.m_dwBrdIP)));
	
	u16 wBrdIndex = FindBrdArrayIndex(tBrdInfo.m_tBrdPos);
	if (TP_INVALID_INDEX == wBrdIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventModifyHandle] count brd array index invalid.\n"));
		return;
	}
	//判断对应的单板是否已经注册
	if ((m_atBrdEntry[wBrdIndex].m_bBrdState) && (m_atBrdEntry[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP != tBrdInfo.m_tBrdPos.m_dwBrdIP))
	{
		//单板在线,断链处理
		if (INVALID_NODE == m_atBrdEntry[wBrdIndex].m_dwBrdNode)
		{
			MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventModifyHandle] BrdNode is invalid node. BrdIndex:%d.\n", wBrdIndex));
			return;
		}
		//在线,重启
		m_pcEqpInst->SendToBrd(m_atBrdEntry[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdReboot_Cmd, 
											m_atBrdEntry[wBrdIndex].m_dwBrdIns, m_atBrdEntry[wBrdIndex].m_dwBrdNode);
		//::OspDisconnectTcpNode(m_atBrdEntry[wBrdIndex].m_dwBrdNode);
	}
	m_atBrdEntry[wBrdIndex].SetBrdCfg(tBrdInfo);
}
//模式删除
void CEqpMgr::EventMdlDelHandle(CTpMsg* const ptMsg)
{
	u8* pBuf = ptMsg->GetBody();
	u16 wBrdIndex;
	TP_SAFE_CAST(wBrdIndex, pBuf);
	u16 wMdlNum;
	TP_SAFE_CAST(wMdlNum, pBuf + sizeof(wBrdIndex));
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventMdlDelHandle] DelMdl, BrdIndex:%d, MdlNum:%d.\n", wBrdIndex, wMdlNum));

	if (wBrdIndex < 0 && wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventMdlDelHandle] DelMdl, BrdIndex invalid. BrdIndex:%d.\n", wBrdIndex));
		return;
	}
	if (wMdlNum < 0 && wMdlNum > TP_UMS_BRD_MAXNUM_EQP)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventMdlDelHandle] DelMdl, MdlNum invalid. MdlNum:%d.\n", wMdlNum));
		return;
	}

	if (m_atBrdEntry[wBrdIndex].m_bBrdState)
	{
		m_atBrdEntry[wBrdIndex].m_bMdlDel = TRUE;
		//在线,重启
		m_pcEqpInst->SendToBrd(m_atBrdEntry[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdReboot_Cmd, 
											m_atBrdEntry[wBrdIndex].m_dwBrdIns, m_atBrdEntry[wBrdIndex].m_dwBrdNode);
		//	::OspDisconnectTcpNode(m_atBrdEntry[wBrdIndex].m_dwBrdNode);
	}
	else
	{
		m_atBrdEntry[wBrdIndex].m_byEqpNum -= wMdlNum;
		for (u8 byIndex = 0; byIndex < wMdlNum; byIndex--)
		{
			m_atBrdEntry[wBrdIndex].BrdMdlDel(byIndex);
		}
	}

	return ;
}

//模式修改
void CEqpMgr::EventMdlModifyHandle(CTpMsg* const ptMsg)
{
	u8* pBuf = ptMsg->GetBody();
	TTPBrdMdlInfo tMdlInfo;
	TP_SAFE_CAST(tMdlInfo, pBuf);
	u16 wBrdIndex = GetBrdIndex(tMdlInfo.m_byLayer, tMdlInfo.m_bySlot);
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventMdlModifyHandle] BrdIndex:%d, MdlNum:%d, MdlType:(%d->%s), MdlAlias:%s.\n",
							wBrdIndex, tMdlInfo.m_byIndex, TpEnumIdString(EMEqpType, tMdlInfo.m_atMdlCfg[0].m_emEqpType), tMdlInfo.m_atMdlCfg[0].m_szEqpAlias));

	//修改模式还是添加模式
	if (em_unknow_mdl != m_atBrdEntry[wBrdIndex].m_atEqpCfg[0].m_emEqpType)
	{
		for (u8 byIndex = 0; byIndex < m_atBrdEntry[wBrdIndex].m_byEqpNum; byIndex++)
		{
			if (NULL == m_pcEqpInst->GetEqp(m_atBrdEntry[wBrdIndex].m_atEqpCfg[byIndex].m_emEqpType))
			{
				MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventMdlModifyHandle] get eqp error, point is null,brdIndex:%d, EqpIndex:%d.\n", wBrdIndex, byIndex));
				continue;
			}
			if (INVALID_NODE != m_atBrdEntry[wBrdIndex].m_dwBrdNode)
			{
				m_pcEqpInst->GetEqp(m_atBrdEntry[wBrdIndex].m_atEqpCfg[byIndex].m_emEqpType)->OnDisConnect(m_atBrdEntry[wBrdIndex].m_dwBrdNode);
			}
		}
		//修改模式,重启板子
		if (INVALID_NODE != m_atBrdEntry[wBrdIndex].m_dwBrdNode)
		{
			m_pcEqpInst->SendToBrd(m_atBrdEntry[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType, 
								ev_TPBrdReboot_Cmd, m_atBrdEntry[wBrdIndex].m_dwBrdIns, m_atBrdEntry[wBrdIndex].m_dwBrdNode);
		}
	}

	for (u8 byIndex = 0; byIndex < tMdlInfo.m_byIndex; byIndex++)
	{
		m_atBrdEntry[wBrdIndex].SetMdlCfg(byIndex, tMdlInfo.m_atMdlCfg[byIndex]);	
	}
	m_atBrdEntry[wBrdIndex].m_byEqpNum = tMdlInfo.m_byIndex;
}

void CEqpMgr::EventReboot(CTpMsg* const ptMsg)
{
	u16 wBrdIndex;
	TP_SAFE_CAST(wBrdIndex, (u8*)ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventBrdReoot] Reboot Board: BrdIndex:%d.\n", wBrdIndex));

	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM )
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventReboot] BrdIndex invalid.\n", wBrdIndex));
		return;
	}

	TBrdEntry* ptBrd = &(m_atBrdEntry[wBrdIndex]);
	if (NULL == ptBrd)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventReboot] ptBrd is null.\n", wBrdIndex));
		return;
	}

	if (INVALID_NODE == ptBrd->m_dwBrdNode)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventReboot] Board Node is Invalid.\n"));
		return;
	}
	if (INVALID_INS == ptBrd->m_dwBrdIns)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventReboot] Board Instance is Invalid.\n"));
		return;
	}

	//发送重启消息
	m_pcEqpInst->SendToBrd(ptBrd->m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdReboot_Cmd, ptBrd->m_dwBrdIns, ptBrd->m_dwBrdNode);
}

void CEqpMgr::EventUpGrade(CTpMsg* const ptMsg)
{
	TBrdUpInfo tUpGrade;
	TP_SAFE_CAST(tUpGrade, (u8*)ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventUpGrade] UpGrade Board: BrdIndex:%d, FileName:%s, num:%d.\n", 
								tUpGrade.m_byIndex, tUpGrade.m_szFileName, tUpGrade.m_byNum));
	
	TBrdEntry* ptBrdInfo = &(m_atBrdEntry[tUpGrade.m_byIndex]);
	if (NULL == ptBrdInfo)
	{
		MdlError(Ums_Mdl_Eqp, ("[EventUpGrade] ptBrd %d is null.\n", tUpGrade.m_byIndex));
		return;
	}
	m_pcEqpInst->SendToBrd(ptBrdInfo->m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdSoftWareUpdate_Req, ptBrdInfo->m_dwBrdIns, ptBrdInfo->m_dwBrdNode, (u8*)(&tUpGrade), sizeof(TBrdUpInfo));
}
//单板版本号
void CEqpMgr::EventHardVerAck(CTpMsg* const ptMsg)
{
	TBrdVersion tVer;
	TP_SAFE_CAST(tVer, (u8*)ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventHardVerAck] HardVer: BrdIndex:%d, Hardver:%s, SoftVer:%s\n", 
														tVer.m_wBrdIndex, tVer.m_achBrdVer, tVer.m_achSoftVer));

	NotifyBrdInfoToService(ev_board_getversion_ack, (u8*)&tVer, sizeof(TBrdVersion));
}

//升级响应
void CEqpMgr::EventUpdateAck(CTpMsg* const ptMsg)
{
	BOOL32 bReturn;
	TP_SAFE_CAST(bReturn, ptMsg->GetBody());
	
	u16 wBrdIndex = GetBrdIndex(ptMsg->GetSrcNode());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventUpdateAck] srcNode:%d, brdIndex :%d, update return :%d.\n", 
		ptMsg->GetSrcNode(), wBrdIndex, bReturn));

	u8 abyBuf[sizeof(u16) + sizeof(BOOL32)];
	memcpy(abyBuf, &wBrdIndex, sizeof(u16));
	memcpy(abyBuf + sizeof(u16), &bReturn, sizeof(BOOL32));
	NotifyBrdInfoToService(ev_board_upgrade_res, abyBuf, sizeof(abyBuf));
}

//混音 画面合成 适配占用情况
void CEqpMgr::EventEqpUsedReq(CTpMsg* const ptMsg)
{
	EMEqpType emEqp;
	TP_SAFE_CAST(emEqp, ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventEqpUsedReq] eqpType:(%d->%s).\n", TpEnumIdString(EMEqpType, emEqp)));

	CEqpBase* ptEqp = m_pcEqpInst->GetEqp(emEqp);
	if (NULL == ptEqp)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventEqpUsedReq] ptEqp is NULL! eqpType:(%d->%s).\n", TpEnumIdString(EMEqpType, emEqp)));
		return;
	}
	
	TTPBrdUsedInfo tUsed;
	ptEqp->CalcEqpUsedStat(tUsed);
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventEqpUsedReq] tEqpUsed Info: eqpType:(%d->%s), RegNum:%d, UsedNum:%d.\n", 
								TpEnumIdString(EMEqpType, tUsed.m_emType), tUsed.m_wRegNum, tUsed.m_wUsedNum));

	NotifyBrdInfoToService(ev_board_used_nty, (u8*)&tUsed, sizeof(TTPBrdUsedInfo));
}

void CEqpMgr::NotifyBrdInfoToService(u16 wEvent, u8* pbyMsg, u16 wLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	
	if (NULL != pbyMsg)
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

//适配实时更新
void CEqpMgr::UpdateBrdUsedState(TTPBrdUsedInfo& tUsed)
{
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::UpdateBrdUsedState] mdlType:(%d->%s), Reg:%d, Used:%d.\n", 
								TpEnumIdString(EMEqpType, tUsed.m_emType),tUsed.m_wRegNum, tUsed.m_wUsedNum));

	NotifyBrdInfoToService(ev_board_used_nty, (u8*)&tUsed, sizeof(TTPBrdUsedInfo));
}

u16 CEqpMgr::FindBrdArrayIndex(TTPBrdPos tPos)
{
	u16 wRetIndex = TP_INVALID_INDEX;
	if (em_mpc_brd == tPos.m_emBrdType)
	{
		if (0 == tPos.m_byBrdSlot)
		{
			wRetIndex = tPos.m_byBrdLayer * TP_BOARD_MAX_SLOT + MC0_BRD_UI_SLOT;
		}
		else if (1 == tPos.m_byBrdSlot)
		{
			wRetIndex = tPos.m_byBrdLayer * TP_BOARD_MAX_SLOT + MC1_BRD_UI_SLOT;
		}
		else
		{
			MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::FindBrdArrayIndex] em_mpc_brd tPos.m_byBrdSlot invalid\n"));
		}
	}
	else if (em_is22_brd == tPos.m_emBrdType)
	{
		wRetIndex = tPos.m_byBrdLayer * TP_BOARD_MAX_SLOT + (tPos.m_byBrdSlot + 1);
	}
	else
	{
		if ((tPos.m_byBrdSlot >= 0) && (tPos.m_byBrdSlot < (NORMAL_BRD_UI_SLOT_DOWN_BOUNDS - 1)) )
		{
			wRetIndex = tPos.m_byBrdLayer * TP_BOARD_MAX_SLOT + (tPos.m_byBrdSlot + 1);
		}
		else if ((tPos.m_byBrdSlot >= NORMAL_BRD_UI_SLOT_DOWN_BOUNDS && (tPos.m_byBrdSlot <= 14)))
		{
			wRetIndex = tPos.m_byBrdLayer * TP_BOARD_MAX_SLOT + (tPos.m_byBrdSlot + 2);
		}
		else
		{
			MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::FindBrdArrayIndex] ordinary brd tPos.m_byBrdSlot invalid\n"));
		}
	}
	return wRetIndex;
}

void CEqpMgr::SendMsgToBrd(u32 dwSrcIID, u32 dwNode, u16 wEvent, u8 * const pbyMsg, u16 wLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if (NULL != pbyMsg)
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	
	cMsg.Post(dwSrcIID, dwNode);
}

void CEqpMgr::ShowBrdInfo()
{
	tpHint(Ums_Mdl_Eqp, "Show Eqp Brd Info:\n\n");
	
	TBrdEntry* ptBrdCfg = NULL;
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex++)
	{
		ptBrdCfg = &m_atBrdEntry[wIndex];
		if (em_unknow_brd == ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			continue;
		}
		msgprintnotime("Type:(%d->%s), Layer:%d, Slot:%d, Ip:"TPIPFORMAT", BrdState:%d(0-offline, 1-online), Node:%d, EqpNum:%d.\n",
						TpEnumIdString(EMBrdType, ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_emBrdType), ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdLayer,
						ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(ptBrdCfg->m_tBrdCfg.m_tBrdPos.m_dwBrdIP), 
						ptBrdCfg->m_bBrdState, ptBrdCfg->m_dwBrdNode, ptBrdCfg->m_byEqpNum);
		
		for (u8 byIndex = 0; byIndex < ptBrdCfg->m_byEqpNum; byIndex++)
		{
			msgprintnotime("	Index:%d, EqpType:(%d->%s), EqpAlias:%s, ", (byIndex + 1), TpEnumIdString(EMEqpType, ptBrdCfg->m_atEqpCfg[byIndex].m_emEqpType)
							, ptBrdCfg->m_atEqpCfg[byIndex].m_szEqpAlias);
			if (em_audmix_mdl == ptBrdCfg->m_atEqpCfg[byIndex].m_emEqpType)
			{
				msgprintnotime("AudMixNum%d:%d, ", byIndex + 1, ptBrdCfg->m_atEqpCfg[byIndex].m_byAudmixNum);
			}
			msgprintnotime("EqpID:%d, EqpState:%d(0-offline, 1-online).\n", ptBrdCfg->m_atEqpCfg[byIndex].m_byEqpID, ptBrdCfg->m_abEqpReg[byIndex]);
		}
	}
}

void CEqpMgr::UpdateEqpRegState(u32 dwNode, u8 byEqpId, BOOL32 bReg)
{
	//根据对应的node号找到对应的板子
	u16 wIndex = GetBrdIndex(dwNode);
	if (TP_INVALID_INDEX == wIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::UpdateEqpRegState] GetBrdIndex node:%d, unfind board.\n", dwNode));
		return;
	}
	TBrdStateInfo tState;
	tState.m_wIndex = wIndex;
	tState.m_bReg = m_atBrdEntry[wIndex].m_bBrdState;
	tState.m_bUsed = m_atBrdEntry[wIndex].m_bUsed;
	u16 wMdlIndex = GetEqpIndex(wIndex, byEqpId);
	if (TP_INVALID_INDEX == wMdlIndex)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::UpdateEqpRegState] GetEqpIndex node:%d, eqpIndex error.\n", dwNode));
		return;
	}
	m_atBrdEntry[wIndex].m_abEqpReg[wMdlIndex] = bReg;
//	tState.m_abEqpReg[wMdlIndex] = bReg;

	memcpy(tState.m_abEqpReg, m_atBrdEntry[wIndex].m_abEqpReg, sizeof(tState.m_abEqpReg));
	//更新注册状态到service
	NotifyBrdInfoToService(ev_board_reg_result, (u8*)&tState, sizeof(TBrdStateInfo));
}

u16 CEqpMgr::GetBrdIndex(u32 dwNode)
{
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex++)
	{
		if (dwNode == m_atBrdEntry[wIndex].m_dwBrdNode)
		{
			return wIndex;
		}
	}

	return TP_INVALID_INDEX;
}

u16 CEqpMgr::GetEqpIndex(u16 wBrdIndex, u8 byEqpId)
{
	for (u16 wIndex = 0; wIndex < TP_UMS_BRD_MAXNUM_EQP; wIndex++)
	{
		if (byEqpId == m_atBrdEntry[wBrdIndex].m_atEqpCfg[wIndex].m_byEqpID)
		{
			return wIndex;
		}
	}

	return TP_INVALID_INDEX;
}

void CEqpMgr::UpdateSysTimeToAllBrd()
{
	TBrdEntry* ptBrdInfo = NULL;

	TTPTime tTime;
	TPGetSysTime(tTime);

	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::UpdateSysTimeToAllBrd] SysTime: %4.4u-%2.2u-%2.2u %2.2u:%2.2u:%2.2u.\n", 
						tTime.m_wYear, tTime.m_byMonth, tTime.m_byMDay, tTime.m_byHour, tTime.m_byMinute, tTime.m_bySecond));

	for ( u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex ++ )
	{
		ptBrdInfo = &m_atBrdEntry[wIndex];

		if (em_unknow_brd == ptBrdInfo->m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			continue;
		}

		if ( !m_pcEqpInst->IsUmsBrd(ptBrdInfo->m_tBrdCfg.m_tBrdPos.m_emBrdType) )
		{
			continue;
		}

		if ( ptBrdInfo->m_tBrdCfg.m_tBrdPos.m_emBrdType == em_mpc_brd )
		{
			continue;
		}

		if (!ptBrdInfo->m_bBrdState)
		{
			continue;
		}

		m_pcEqpInst->SendToBrd(ptBrdInfo->m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdSetSysTime_Cmd, 
								ptBrdInfo->m_dwBrdIns, ptBrdInfo->m_dwBrdNode, &tTime, sizeof(tTime));
	}
	return ;
}

u32 CEqpMgr::GetBrdInst( u16 wBrdIndex )
{
	return m_atBrdEntry[wBrdIndex].m_dwBrdIns;
}

void CEqpMgr::RebootBrd( u32 dwBrdIP )
{
	TBrdEntry* ptBrd = GetBrdCfg(dwBrdIP);
	if ( NULL == ptBrd )
	{
		return ;
	}

	if (INVALID_NODE == ptBrd->m_dwBrdNode)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::RebootBrd] Board Node is Invalid.\n"));
		return;
	}
	if (INVALID_INS == ptBrd->m_dwBrdIns)
	{
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::RebootBrd] Board Instance is Invalid.\n"));
		return;
	}
	
	//发送重启消息
	m_pcEqpInst->SendToBrd(ptBrd->m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdReboot_Cmd, ptBrd->m_dwBrdIns, ptBrd->m_dwBrdNode);

	return ;
}


//telnet ftp开关
void CEqpMgr::EventSwitchTelnetFtp(CTpMsg* const ptMsg)
{
	TBrdSwitchInfo tBrdSwitchInfo;
	TP_SAFE_CAST(tBrdSwitchInfo, (u8*)ptMsg->GetBody());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventSwitchTelbetFtp] Switch Board Telnet or Ftp: BrdIndex:%d, SwitchType:%d, Switch:%d.\n", 
								tBrdSwitchInfo.m_wBrdIndex, tBrdSwitchInfo.m_emType, tBrdSwitchInfo.m_bSwitch));
	u16 wBrdIndex = tBrdSwitchInfo.m_wBrdIndex;	
    EMBrdType emBrdType   = em_unknow_brd;
	TBrdEntry* ptBrdInfo  = NULL;
	EmBoardSwitchRes emSwitchRet = em_BoardSwitchRes_ok;
	do 
	{
		if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
		{
			emSwitchRet = em_BoardSwitchRes_notfind;
			MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventSwitchTelFtpAck] Switch Board Telnet or Ftp, BrdIndex More Than BrdMaxNum.\n"));
			break;
		}		
		//只支持is2.2 cri2 mpc2  mpu2tp apu2tp
 		ptBrdInfo = &(m_atBrdEntry[tBrdSwitchInfo.m_wBrdIndex]);
		 if (NULL == ptBrdInfo)
		 {
	 		MdlError(Ums_Mdl_Eqp, ("[EventSwitchTelbetFtp] ptBrd %d is null.\n", tBrdSwitchInfo.m_wBrdIndex));
			emSwitchRet = em_BoardSwitchRes_notfind;
			break;
		}
		emBrdType = ptBrdInfo->m_tBrdCfg.m_tBrdPos.m_emBrdType;
		if ((em_is22_brd != emBrdType) && (em_cri2_brd != emBrdType) && (em_mpc_brd != emBrdType)
			&&(em_mpu2_tp_brd != emBrdType) && (em_apu2_tp_brd != emBrdType))
		{
			emSwitchRet = em_BoardSwitchRes_brderror;
			MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventSwitchTelFtpAck] Switch Board Telnet or Ftp, BrdType %d not support.\n",emBrdType));
			break;
		}

	} while (0);

	if (em_BoardSwitchRes_ok != emSwitchRet)
	{
		u8 abyBuf[sizeof(TBrdSwitchInfo) + sizeof(EmBoardSwitchRes)];
		memcpy(abyBuf, &tBrdSwitchInfo, sizeof(TBrdSwitchInfo));
		memcpy(abyBuf + sizeof(TBrdSwitchInfo), &emSwitchRet, sizeof(EmBoardSwitchRes));
	    NotifyBrdInfoToService(ev_board_switchtelnetftpe_res, abyBuf, sizeof(abyBuf));
	}
	else
	{
	
		m_pcEqpInst->SendToBrd(ptBrdInfo->m_tBrdCfg.m_tBrdPos.m_emBrdType, ev_TPBrdSwitchTeltp_Req, ptBrdInfo->m_dwBrdIns, ptBrdInfo->m_dwBrdNode, (u8*)(&tBrdSwitchInfo), sizeof(TBrdSwitchInfo));
	}
	
}

void CEqpMgr::EventSwitchTelFtpAck(CTpMsg* const ptMsg)
{
	u8* pBuf = ptMsg->GetBody();
	TBrdSwitchInfo tBrdSwitchInfo;
	TP_SAFE_CAST(tBrdSwitchInfo, pBuf);
	u16 wBrdIndex = GetBrdIndex(ptMsg->GetSrcNode());
	MdlHint(Ums_Mdl_Eqp, ("[CEqpMgr::EventSwitchTelFtpAck] srcNode:%d, brdIndex :%d.\n", 
		ptMsg->GetSrcNode(), wBrdIndex));
	EmBoardSwitchRes emSwitchRet = em_BoardSwitchRes_ok;
	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		emSwitchRet = em_BoardSwitchRes_notfind;
		MdlError(Ums_Mdl_Eqp, ("[CEqpMgr::EventSwitchTelFtpAck] Switch Board Telnet or Ftp, BrdIndex More Than BrdMaxNum.\n"));
	}
	u8 abyBuf[sizeof(TBrdSwitchInfo) + sizeof(EmBoardSwitchRes)];
	memcpy(abyBuf, &tBrdSwitchInfo, sizeof(TBrdSwitchInfo));
	memcpy(abyBuf + sizeof(TBrdSwitchInfo), &emSwitchRet, sizeof(EmBoardSwitchRes));
	NotifyBrdInfoToService(ev_board_switchtelnetftpe_res, abyBuf, sizeof(abyBuf));	
}
