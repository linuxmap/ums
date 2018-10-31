#include "toolhandler.h"
#include "ueinterface.h"
#include "umsxmltype.h"

#include "innereventumsserver.h"

// 外部消息
#include "eventoutumslogin.h"
#include "eventoutumstool.h"
#include "eventoutumscfg.h"
#include "eventoutumsreg.h"
#include "eventoutumsconftemplate.h"
#include "eventoutumshdu2.h"
#include "eventoutumsboard.h"
#include "eventoutquantum.h"

CToolHandler::CToolHandler(CTpObject* pcObject, u32 dwToolAppID)
						  : CTpHandler(pcObject)
{
	m_dwToolAppID = dwToolAppID;

	m_bLockflag   = FALSE;
	m_dwLockReason = 0;
}

CToolHandler::~CToolHandler()
{

}

BOOL32 CToolHandler::Handler(CTpMsg* const ptMsg)
{

	u16	  wEvent	= ptMsg->GetEvent();
	void* pDataBuf  = ptMsg->GetBody();
	u16   wDataSize = ptMsg->GetBodyLen();
	u16   wAppID	= GETAPP(ptMsg->GetSrcIId());
	CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();

	//从界面到业务
	if (wAppID == GETAPP(m_dwToolAppID))
	{
		PrintEventInfoFromUI(ptMsg);

		switch (wEvent)
		{
		case ev_sysInfo_req:	
		case ev_confCount_req:
		case ev_rebootUms_cmd:
		case ev_downloadConftemp_req:
		case ev_authCount_req:
		case ev_UmsGetSysTime_Req:
		case ev_hduCount_req:
		case ev_licenseOutput_req:
		case ev_hduStyle_Del_Req:
			{
				pUeInst->NotifyMsgToService(wEvent, NULL, 0, m_tCurLogUser);
			}
			break;

		case ev_card_eqp_used_req:
		case ev_uploadConftemp_req:
		case ev_UmsSetSysTime_Cmd:
		case ev_UmsIPCfg:
		case ev_umsreg_cmd:
		case ev_umsGKReg_cmd:
		case ev_hduBrdModify_req:
		case ev_hduBrdAdd_req:
		case ev_hduReboot_req:
		case ev_hduChanModify_req:
		case ev_hduChanAdd_req:
		case ev_hduChanDel_req:
		case ev_hduDel_req:
		case ev_hduStyle_Add:
		case ev_hduStyle_update_Req:
		case ev_cardAdd_req:
		case ev_cardDel_req:
		case ev_cardModify_req:
		case ev_cardModeDel_req:
		case ev_cardModeModify_req:
		case ev_card_reboot_req:
		case ev_card_upgrade_req:
		case ev_NMServerAdd_req:
		case ev_NMServerMdy_req:
		case ev_NMServerDel_req:
		case ev_hduUpdate_req:
		case ev_card_switchtelnetftp_req:
		case ev_SetQTEncryptInfo_Cmd:
			{
				pUeInst->NotifyMsgToService(wEvent, pDataBuf, wDataSize, m_tCurLogUser);
			}
			break;

		case ev_TPtoolLock_Cmd:
			{
                m_bLockflag     = *(BOOL32 *)pDataBuf;
				m_dwLockReason   = *(u32*)((u8*)pDataBuf + sizeof(BOOL32));
			}
			break;
		
		default:		return FALSE;
		}
	}
	else
	{
		if ( evtp_AddConftemplate_Notify1 == wEvent || evtp_Updateconftemplate_Notify1 == wEvent )
		{
			return TRUE;
		}
		if (0 == m_tCurLogUser.m_dwUserNode)
		{
			return FALSE;
		}

		//从业务到界面
		void* pDataBuf	= ptMsg->GetBody() + sizeof(TLogUser);
		u16 wDataSize	= ptMsg->GetBodyLen() - sizeof(TLogUser);
		u16 wEvent		= ptMsg->GetEvent();
			
		CTpMsg cMsg;
		cMsg.SetEvent(wEvent);
		cMsg.SetBody(pDataBuf, wDataSize);
		cMsg.Post(m_tCurLogUser.m_dwUserInst, m_tCurLogUser.m_dwUserNode, UMS_UE_APP_INST);

		PrintEventInfo(ptMsg);
	}

	return TRUE;
}

BOOL32 CToolHandler::PreHandler(CMessage *const ptMsg)
{
	switch (ptMsg->event)
	{
	case ev_UMSLoginReq:
		{
			EventUserLogin(ptMsg);
		}
		break;

	case OSP_DISCONNECT:
		{
			EventDisconnect(ptMsg);
		}
		break;
	}
	return TRUE;
}

void CToolHandler::EventDisconnect(CMessage* const ptMsg)
{
	u32 dwNode = *(u32*)ptMsg->content;
	if (dwNode == m_tCurLogUser.m_dwUserNode)
	{
		MdlHint(Ums_Mdl_Ue, ("Tool user disconnect. CurUserIP:"TPIPFORMAT"\n", Tpu32ToIP(m_tCurLogUser.m_dwUserIP)));
		m_tCurLogUser.Clear();
		m_bLockflag = FALSE;
		m_dwLockReason = 0;
	}
}

void CToolHandler::EventUserLogin(CMessage* const ptMsg)
{
	u32_ip dwLogIP = ::OspNodeIpGet(ptMsg->srcnode);
	MdlHint(Ums_Mdl_Ue, ("Tool user login. CurUserIP:"TPIPFORMAT", LoginUserIP:"TPIPFORMAT" \n", 
		  Tpu32ToIP(m_tCurLogUser.m_dwUserIP), Tpu32ToIP(dwLogIP)));


	if (m_bLockflag)
	{
		CTpMsg cMsgrefuse;
		cMsgrefuse.SetEvent(ev_TPtoolLockReason_Nty);
		cMsgrefuse.SetBody(&m_tCurLogUser.m_dwUserIP, sizeof(m_tCurLogUser.m_dwUserIP));
		cMsgrefuse.CatBody(&m_dwLockReason ,sizeof(m_dwLockReason) );

		cMsgrefuse.Post(ptMsg->srcid, ptMsg->srcnode, UMS_UE_APP_INST);
		
		::OspDelay(200);
		OspDisconnectTcpNode(ptMsg->srcnode);
		return;
	}


	//抢断登录
	if (m_tCurLogUser.m_dwUserIP != 0)
	{
		CTpMsg cMsg;
		cMsg.SetEvent(ev_UmsLoginByOther_Notify);
		cMsg.SetBody(&dwLogIP, sizeof(dwLogIP));
		cMsg.Post(m_tCurLogUser.m_dwUserInst, m_tCurLogUser.m_dwUserNode, UMS_UE_APP_INST);
	
		::OspDelay(200);
		OspDisconnectTcpNode(m_tCurLogUser.m_dwUserNode);
	}

	m_tCurLogUser.m_dwUserInst = ptMsg->srcid;
	m_tCurLogUser.m_dwUserNode = ptMsg->srcnode;
	m_tCurLogUser.m_dwUserIP   = dwLogIP;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_UMSLoginRet);

	TLoginRet tLoginRet;
	tLoginRet.m_emRet = tp_LoginUms_sucess;
	cMsg.SetBody(&tLoginRet, sizeof(tLoginRet));

	cMsg.Post(ptMsg->srcid, ptMsg->srcnode);
	
	OspNodeDiscCBReg(ptMsg->srcnode, AID_UMSUE_APP, 1);

	CUmsUeInst* pUeInst = (CUmsUeInst*)GetInstance();
	pUeInst->NotifyMsgToService( ev_SysCmsLoginInd, NULL, 0, m_tCurLogUser );
}

void CToolHandler::ShowLogin()
{
	if (m_tCurLogUser.m_dwUserNode == 0)
	{
		MdlHint(Ums_Mdl_Ue, ("No tool user login.\n"));
		return ;
	}

	MdlHint(Ums_Mdl_Ue, ("Tool user login. Ip:"TPIPFORMAT"\n", Tpu32ToIP(m_tCurLogUser.m_dwUserIP)));

	MdlHint(Ums_Mdl_Ue, ("Tool user IsLocked:%d  Lockreason:%d\n", m_bLockflag, m_dwLockReason));

}

void CToolHandler::PrintEventInfoFromUI(CTpMsg* const ptMsg)
{
	u16 wEvent    = ptMsg->GetEvent();
	u8* pDataBuf  = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();

	if(!IsCanPrint(Ums_Mdl_Ue, enLogLowest))
	{
		return;
	}

	switch (wEvent)
	{
	case ev_sysInfo_req:				
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_sysInfo_req Get system info req.\n"));
		}
		break;

	case ev_confCount_req:				
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_confCount_req Get running conf count.\n"));
		}	
		break;

	case ev_rebootUms_cmd:				
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_rebootUms_cmd Reboot ums req.\n"));
		}
		break;

	case ev_downloadConftemp_req:		
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_downloadConftemp_req Download conf templete.\n"));
		}	
		break;

	case ev_authCount_req:				
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_authCount_req Get auth count.\n"));
		}	
		break;

	case ev_UmsGetSysTime_Req:			
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_UmsGetSysTime_Req Get system time.\n"));
		}	
		break;

	case ev_hduCount_req:				
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduCount_req Get hdu ues count.\n"));
		}	
		break;
		
	case ev_card_eqp_used_req:
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_eqp_used_req Get eqp used count.\n"));
		}
		break;
	case ev_licenseOutput_req:
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_licenseOutput_req \n"));
		}
		break;

	case ev_uploadConftemp_req:
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_uploadConftemp_req FileName:%s.\n", (s8*)pDataBuf));
		}
		break;

	case ev_UmsSetSysTime_Cmd:
		{
			TTPTime tTPTime = *(TTPTime*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_UmsSetSysTime_Cmd Year:%d, Month:%d, Day:%d, Hour:%d, Min:%d, Sec:%d.\n", 
									tTPTime.m_wYear, tTPTime.m_byMonth, tTPTime.m_byMDay, tTPTime.m_byHour, 
									tTPTime.m_byMinute, tTPTime.m_bySecond));
		}
		break;

	case ev_UmsIPCfg:
		{
			TTPEthnetInfo tEth = *(TTPEthnetInfo*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_UmsIPCfg IP "TPIPFORMAT"Mask"TPIPFORMAT"\n",
									Tpu32ToIP( tEth.dwIP ),Tpu32ToIP( tEth.dwMask)));
		}
		break;

	case ev_umsreg_cmd:
		{
			TTPSipRegistrarCfg tSipCfg = *(TTPSipRegistrarCfg*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsreg_cmd ServerInfo:"ADDRPORT_FORMAT" Used:%d\n", 
									ADDRPORT(tSipCfg.dwRegIP, tSipCfg.wRegPort), tSipCfg.bUsed));
		}
		break;

	case ev_umsGKReg_cmd:
		{
			TTPGKCfg tGkCfg = *(TTPGKCfg*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGKReg_cmd ServerInfo:"ADDRPORT_FORMAT"\n", ADDRPORT(tGkCfg.dwGKIP, tGkCfg.wRegPort)));
		}
		break;

	case ev_hduBrdModify_req:
		{
			TTPBrdPos tInfo = *(TTPBrdPos*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduBrdModify_req Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n",
									 tInfo.m_byBrdLayer, tInfo.m_byBrdSlot, Tpu32ToIP(tInfo.m_dwBrdIP)));
		}
		break;

	case ev_hduBrdAdd_req:
		{
			TTPBrdPos tInfo = *(TTPBrdPos*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduBrdAdd_req Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n",
									 tInfo.m_byBrdLayer, tInfo.m_byBrdSlot, Tpu32ToIP(tInfo.m_dwBrdIP)));
		}
		break;

	case ev_hduReboot_req:
		{
			TTPBrdPos tInfo = *(TTPBrdPos*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduReboot_req Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n",
									 tInfo.m_byBrdLayer, tInfo.m_byBrdSlot, Tpu32ToIP(tInfo.m_dwBrdIP)));
		}
		break;

	case ev_hduChanAdd_req:
		{
			THduInfo tHduInfo;
			TP_SAFE_CAST(tHduInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduChanAdd_req Layer:%d, Slot:%d, Alias:%s, BrdType:%d.\n",
									 tHduInfo.m_byLayer, tHduInfo.m_bySlot, tHduInfo.m_tName.m_abyAlias,
									 tHduInfo.m_emBrdType));

			for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
			{
				MdlLowHint(Ums_Mdl_Ue, ("ChanIndex:%d, OutPort:%d, OutMode:%d, ZoomRate:%d, ShowMode:%d.\n",
										 byIndex, tHduInfo.m_atChanInfo[byIndex].GetOutType(),
										 tHduInfo.m_atChanInfo[byIndex].GetOutMode(),
										 tHduInfo.m_atChanInfo[byIndex].GetZoomRate(),
										 tHduInfo.m_atChanInfo[byIndex].GetShowMode()));
			}
		}
		break;

	case ev_hduChanModify_req:
		{
			THduInfo tHduInfo;
			TP_SAFE_CAST(tHduInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduChanModify_req Layer:%d, Slot:%d, Alias:%s, BrdType:%d.\n",
									 tHduInfo.m_byLayer, tHduInfo.m_bySlot, tHduInfo.m_tName.m_abyAlias,
									 tHduInfo.m_emBrdType));

			for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
			{
				MdlLowHint(Ums_Mdl_Ue, ("ChanIndex:%d, OutPort:%d, OutMode:%d, ZoomRate:%d, ShowMode:%d.\n",
										 byIndex, tHduInfo.m_atChanInfo[byIndex].GetOutType(),
										 tHduInfo.m_atChanInfo[byIndex].GetOutMode(),
										 tHduInfo.m_atChanInfo[byIndex].GetZoomRate(),
										 tHduInfo.m_atChanInfo[byIndex].GetShowMode()));
			}
		}
		break;

	case ev_hduChanDel_req:
		{
			TTPBrdPos tBrdPos;
			TP_SAFE_CAST(tBrdPos, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduChanDel_req Del Channel: Layer:%d, Slot:%d.\n",
									 tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot));
		}
		break;

	case ev_hduDel_req:
		{
			TTPBrdPos tBrdPos;
			TP_SAFE_CAST(tBrdPos, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduDel_req Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n",
									 tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdPos.m_dwBrdIP)));
		}
		break;

	case ev_hduStyle_Add:
		{
			THduStyleData tData;
			TP_SAFE_CAST(tData, pDataBuf);
			
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_Add Row:%d, Column:%d.\n", tData.m_byRow, tData.m_byCol));
			
			THduStyleUnit tIno;
			for (u8 byRowIndex = 0; byRowIndex < tData.m_byRow; ++byRowIndex)
			{
				for (u8 byColIndex = 0; byColIndex < tData.m_byCol; ++byColIndex)
				{
					u16 wIndex = byRowIndex*(tData.m_byCol)+byColIndex;
					tIno = tData.m_atUnits[wIndex];
					
					MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_Add Row:%d, Column:%d, Layer:%d, Slot:%d, ChanIndex:%d.\n",
											 byRowIndex, byColIndex, tIno.m_byLayer, tIno.m_bySlot, 
											 tIno.m_byChanIndex));
				}
			}
		}
		break;
	case ev_hduStyle_Del_Req:
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_Del_Req \n"));	
		}
		break;
	case ev_cardAdd_req:
		{
			TTPBrdCfg tCfg;
			TP_SAFE_CAST(tCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardAdd_req Type:(%d->%s), Layer:%d, Slot:%d, IP:%d.\n", 
									TpEnumIdString(EMBrdType, tCfg.m_tBrdPos.m_emBrdType),
									tCfg.m_tBrdPos.m_byBrdLayer, tCfg.m_tBrdPos.m_byBrdSlot, 
									Tpu32ToIP(tCfg.m_tBrdPos.m_dwBrdIP)));

		}
		break;
	case ev_cardDel_req:
		{
			TTPBrdCfg tDelCfg;
			TP_SAFE_CAST(tDelCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardDel_req Type:%d, Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n", tDelCfg.m_tBrdPos.m_emBrdType,
									tDelCfg.m_tBrdPos.m_byBrdLayer, tDelCfg.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tDelCfg.m_tBrdPos.m_dwBrdIP)));
		}
		break;
	case ev_cardModify_req:
		{
			TTPBrdCfg tModify;
			TP_SAFE_CAST(tModify, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardModify_req Type:%d, Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n", tModify.m_tBrdPos.m_emBrdType,
				tModify.m_tBrdPos.m_byBrdLayer, tModify.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tModify.m_tBrdPos.m_dwBrdIP)));
		}
		break;
	case ev_cardModeDel_req:
		{
			TTPBrdMdlInfo tDelMdl;
			TP_SAFE_CAST(tDelMdl, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardModeDel_req Layer:%d, Slot:%d, MdlType:(%d->%s), MdlAlias:%s.\n", tDelMdl.m_byLayer,
				tDelMdl.m_bySlot, TpEnumIdString(EMEqpType, tDelMdl.m_atMdlCfg[0].m_emEqpType), tDelMdl.m_atMdlCfg[0].m_szEqpAlias));
		}
		break;
	case ev_cardModeModify_req:
		{
			TTPBrdMdlInfo tMdl;
			TP_SAFE_CAST(tMdl, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardModeModify_req Layer:%d, Slot:%d, MdlType:(%d->%s), MdlAlias:%s.\n", tMdl.m_byLayer,
				tMdl.m_bySlot, TpEnumIdString(EMEqpType, tMdl.m_atMdlCfg[0].m_emEqpType), tMdl.m_atMdlCfg[0].m_szEqpAlias));
		}
		break;
	case ev_card_reboot_req:
		{
			TTPBrdPos tPos;
			TP_SAFE_CAST(tPos, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_reboot_req  Type:(%d->%s), Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n", 
									TpEnumIdString(EMBrdType, tPos.m_emBrdType), tPos.m_byBrdLayer, tPos.m_byBrdSlot, Tpu32ToIP(tPos.m_dwBrdIP)))
		}
		break;
	case ev_card_upgrade_req:
		{
			TTPBrdUpGrade tUpdate;
			TP_SAFE_CAST(tUpdate, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_upgrade_req  Layer:%d, Slot:%d, FileName:%s.\n", tUpdate.m_byLayer,
									tUpdate.m_bySlot, tUpdate.m_szFileName));
		}
		break;

	case ev_NMServerAdd_req:
		{
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(tCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerAdd_req  GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT"\n",
									 tCfg.wNMGetSetPort, tCfg.WNMTrapPort,tCfg.achNMReadCommunity, 
								     tCfg.achNMWriteCommunity, tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
		}
		break;

	case ev_NMServerMdy_req:
		{
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(tCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerMdy_req  GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT"\n",
									 tCfg.wNMGetSetPort, tCfg.WNMTrapPort,tCfg.achNMReadCommunity, 
									 tCfg.achNMWriteCommunity, tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
		}
		break;
	case ev_NMServerDel_req:
		{
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(tCfg, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerDel_req  GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT"\n",
									 tCfg.wNMGetSetPort, tCfg.WNMTrapPort,tCfg.achNMReadCommunity, 
									 tCfg.achNMWriteCommunity, tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
		}
		break;

	case ev_hduUpdate_req:
		{
			TTPBrdUpGrade tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduUpdate_req Layer:%d, Slot:%d, FileName:%s.\n",
									 tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_szFileName));
		}
		break;

	case ev_SetQTEncryptInfo_Cmd:
		{
			TTPQTEncryptInfo tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_SetQTEncryptInfo_Cmd QTIP:%x, QTID:%d.\n",tInfo.m_dwQuanTumIP, tInfo.m_dwQuanTumID));
		}
		break;
	case ev_card_switchtelnetftp_req:
		{
			TPBoardSwitch tBrdSwitch;
			TP_SAFE_CAST(tBrdSwitch, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_switchtelnetftp_req layer:%d, slot:%d, type:%d, onoff:%d.\n",
				                     tBrdSwitch.m_byLayer,tBrdSwitch.m_bySlot,tBrdSwitch.m_emType,tBrdSwitch.m_bSwitch));
		}
		break;
	}
}

void CToolHandler::PrintEventInfo( CTpMsg* const ptMsg )
{
	u16 wEvent    = ptMsg->GetEvent();
	u8* pDataBuf  = ptMsg->GetBody() + sizeof(TLogUser);
	u16 wDataSize = ptMsg->GetBodyLen() - sizeof(TLogUser);

	if(!IsCanPrint(Ums_Mdl_Ue, enLogLowest))
	{
		return;
	}

	switch (wEvent)
	{
	case ev_verInfo_Nty:	
		{
			TUmsVersion tver = *(TUmsVersion*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_verInfo_Nty Softver:%s, HardVer:%s.\n", tver.m_abSoftVersion, tver.m_abHardVersion));
		}
		break;

	case ev_sysInfo_Nty:
		{
			TToolSysInfo tSysInfo = *(TToolSysInfo*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_sysInfo_Nty CpuRate:%d, MemRate:%d\n", tSysInfo.m_dwCpuRate, tSysInfo.m_dwMemRate));
		}
		break;

	case ev_confCount_Nty:
		{
			u32 dwConfCount = *(u32*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_confCount_Nty ConfCount:%d\n", dwConfCount));
		}
		break;

	case ev_UmsIPCfg_Ind:
		{
			TTPEthnetInfo tEth = *(TTPEthnetInfo*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_UmsIPCfg_Ind IP "TPIPFORMAT"Mask"TPIPFORMAT"\n",
									Tpu32ToIP( tEth.dwIP ),Tpu32ToIP( tEth.dwMask)));
		}
		break;

	case ev_UmsGetSysTime_Rsp:
		{
			TTPTime tTPTime = *(TTPTime*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_UmsGetSysTime_Rsp Year:%d, Month:%d, Day:%d, Hour:%d, Min:%d, Sec:%d.\n", 
									tTPTime.m_wYear, tTPTime.m_byMonth, tTPTime.m_byMDay, tTPTime.m_byHour, 
									tTPTime.m_byMinute, tTPTime.m_bySecond));
		}
		break;

	case ev_umsreg_notify:
		{
			TTPSipRegistrarCfg tSipCfg = *(TTPSipRegistrarCfg*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsreg_notify ServerInfo:"ADDRPORT_FORMAT" Used:%d, bRegister:%d\n", 
									ADDRPORT(tSipCfg.dwRegIP, tSipCfg.wRegPort), tSipCfg.bUsed, tSipCfg.bRegistered));
		}	
		break;

	case ev_umsGKReg_notify:
		{
			TTPGKCfg tGkCfg = *(TTPGKCfg*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGKReg_notify ServerInfo:"ADDRPORT_FORMAT", bRegister:%d\n"
						, ADDRPORT(tGkCfg.dwGKIP, tGkCfg.wRegPort), tGkCfg.bRegistered));
		}
		break;

	case ev_umsRegResult_notify:
		{
			TUCSipRegResult tRes = *(TUCSipRegResult*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsRegResult_notify Reg result:%d-%s\n", TpEnumIdString(EmTpCnsRegUms, tRes.m_emTpCnsRegUms)));
		}
		break;

	case ev_umsGKReg_ret:
		{
			TUCSipRegResult tRes = *(TUCSipRegResult*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_umsGKReg_ret Reg result:%d-%s\n", TpEnumIdString(EmTpCnsRegUms, tRes.m_emTpCnsRegUms)));	
		}
		break;

	case ev_uploadConftemp_rsq:
		{
			MdlLowHint(Ums_Mdl_Ue, ("ev_uploadConftemp_rsq Upload template file end.\n"));
		}
		break;

	case ev_downloadConftemp_rsq:
		{
			s8 szFileName[TP_UPLOAD_FILE_NAME_LENGTH + 1] = {0};
			memcpy(szFileName, pDataBuf, TP_UPLOAD_FILE_NAME_LENGTH);
			MdlLowHint(Ums_Mdl_Ue, ("ev_downloadConftemp_rsq Downloada file name:%s.\n", szFileName));
		}
		break;

	case ev_authCount_Nty:
		{
			u32 dwTotal = *(u32*)pDataBuf;
			u32 dwUseNum = *(u32*)(pDataBuf+sizeof(u32));
			MdlLowHint(Ums_Mdl_Ue, ("ev_authCount_Nty TotalCount:%d, UseCount:%d.\n", dwTotal, dwUseNum));
		}
		break;

	case ev_hduCount_Nty:
		{
			TTPBrdUsedInfo tUseInfo = *(TTPBrdUsedInfo*)pDataBuf;
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduCount_Nty Type:%d, UseNum:%d, RegNum:%d.\n",
				tUseInfo.m_emType, tUseInfo.m_wUsedNum, tUseInfo.m_wRegNum));
		}
		break;
		
	case ev_hduInfo_Nty:
		{
			THduCfg tCfgInfo;
			TP_SAFE_CAST(tCfgInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduInfo_Nty Layer:%d, Slot:%d, IP:"TPIPFORMAT", Alias:%s, ChanNum:%d.\n",
									tCfgInfo.m_byLayer, tCfgInfo.m_bySlot, Tpu32ToIP(tCfgInfo.m_dwIP), 
									tCfgInfo.m_tName.m_abyAlias, tCfgInfo.m_byChanNum));

			for (u16 wIndex = 0; wIndex < tCfgInfo.m_byChanNum; ++wIndex)
			{
				MdlLowHint(Ums_Mdl_Ue, ("ev_hduInfo_Nty ChanInfo: Index:%d, OutPortType:%d, OutMode:%d, ZoomRate:%d.\n",
										wIndex, tCfgInfo.m_atChanInfo[wIndex].GetOutType(), 
										tCfgInfo.m_atChanInfo[wIndex].GetOutMode(),
										tCfgInfo.m_atChanInfo[wIndex].GetZoomRate()));
			}
		}
		break;

	case ev_hduReboot_rsp:
		{
			EmModifyHduRet emRet;
			TTPBrdPos tBrdPos;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tBrdPos, pDataBuf+sizeof(EmModifyHduRet));
			
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduReboot_rsp Layer:%d, Slot:%d, IP:"TPIPFORMAT", Ret:%d.\n",
									tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdPos.m_dwBrdIP), emRet));
		}
		break;

	case ev_hduBrdAdd_rsp:
		{
			EmModifyHduRet emRet;
			TTPBrdPos tBrdPos;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tBrdPos, pDataBuf+sizeof(EmModifyHduRet));
			
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduBrdAdd_rsp Layer:%d, Slot:%d, IP:"TPIPFORMAT", Ret:%d.\n",
									tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdPos.m_dwBrdIP), emRet));
		}
		break;

	case ev_hduBrdModify_rsp:
		{
			EmModifyHduRet emRet;
			TTPBrdPos tBrdPos;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tBrdPos, pDataBuf+sizeof(EmModifyHduRet));

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduBrdModify_rsp  Layer:%d, Slot:%d, IP:"TPIPFORMAT", Ret:%d.\n",
									tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdPos.m_dwBrdIP), emRet));
		}
		break;

	case ev_hduChanAdd_rsp:
		{
			EmModifyHduRet emRet;
			THduInfo tInfo;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tInfo, pDataBuf+sizeof(EmModifyHduRet));
			
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduChanAdd_rsp Layer:%d, Slot:%d, Alias:%s, Ret:%d.\n",
									 tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_tName.m_abyAlias, emRet));

			for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
			{
				MdlLowHint(Ums_Mdl_Ue, ("ChanIndex:%d, OutPort:%d, OutMode:%d, ZoomRate:%d, ShowMode:%d.\n",
					byIndex, tInfo.m_atChanInfo[byIndex].GetOutType(),
					tInfo.m_atChanInfo[byIndex].GetOutMode(),
					tInfo.m_atChanInfo[byIndex].GetZoomRate(),
					tInfo.m_atChanInfo[byIndex].GetShowMode()));
			}
		}
		break;

	case ev_hduChanModify_rsp:
		{
			EmModifyHduRet emRet;
			THduInfo tInfo;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tInfo, pDataBuf+sizeof(EmModifyHduRet));

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduChanModify_rsp Layer:%d, Slot:%d, Ret:%d.\n",
									 tInfo.m_byLayer, tInfo.m_bySlot, emRet));
		}
		break;

	case ev_hduChanDel_rsp:
		{
			EmModifyHduRet emRet;
			TTPBrdPos tBrdPos;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tBrdPos, pDataBuf+sizeof(EmModifyHduRet));

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduChanDel_rsp Layer:%d, Slot:%d, Ret:%d.\n",
									 tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, emRet));
		}
		break;
		
	case ev_hduStyle_Nty:
		{
			THduStyleData tStyleData;
			TP_SAFE_CAST(tStyleData, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_hdu_style_nty Row:%d, Column:%d.\n", tStyleData.m_byRow, tStyleData.m_byCol));

			u16 wIndex = 0;
			for (u8 byRowIndex = 0; byRowIndex < tStyleData.m_byRow; ++byRowIndex)
			{
					for (u8 byColumnIndex = 0; byColumnIndex < tStyleData.m_byCol; ++byColumnIndex)
					{
						MdlLowHint(Ums_Mdl_Ue, ("ev_hdu_style_nty HduInfo: Row:%d, Column:%d, Layer:%d, Slot%d, ChanIndex:%d, Name:%s\n", 
												byRowIndex, byColumnIndex, tStyleData.m_atUnits[wIndex].m_byLayer, tStyleData.m_atUnits[wIndex].m_bySlot,
												tStyleData.m_atUnits[wIndex].m_byChanIndex, tStyleData.m_atUnits[wIndex].m_tName.m_abyAlias));
						++wIndex;
					}
			}
		}
		break;

	case ev_hduStyle_Add_Rsp:
		{
			EmModifyHduRet emRet;
			THduStyleData tData;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tData, pDataBuf+sizeof(EmModifyHduRet));

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_Add_Rsp   Ret:%d.\n", emRet));
			
			u16 wIndex = 0;
			for (u8 byRowIndex = 0; byRowIndex < tData.m_byRow; ++byRowIndex)
			{
				for (u8 byColIndex = 0; byColIndex < tData.m_byCol; ++byColIndex)
				{					
					MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_Add_Rsp Row:%d, Column:%d, Layer:%d, Slot:%d, ChanIndex:%d.\n",
											 byRowIndex, byColIndex, tData.m_atUnits[wIndex].m_byLayer, 
											 tData.m_atUnits[wIndex].m_bySlot, 
											 tData.m_atUnits[wIndex].m_byChanIndex));

					++wIndex;
				}
			}
		}
		break;
	case ev_hduStyle_Del_Rsp:
		{
			EmModifyHduRet emRet;
			TP_SAFE_CAST(emRet, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_Del_Rsp ret:%d\n", emRet));
		}
		break;
	case ev_hduStyle_update_Rsp:
		{
			EmModifyHduRet emRet;
			TP_SAFE_CAST(emRet, pDataBuf);
			THduStyleData tData;
			TP_SAFE_CAST(tData, pDataBuf + sizeof(EmModifyHduRet));
			MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_update_Rsp  row:%d, col:%d, emRet:%d.\n", tData.m_byRow, tData.m_byCol, emRet));
			
			u16 wIndex = 0;
			for (u8 byRowIndex = 0; byRowIndex < tData.m_byRow; ++byRowIndex)
			{
				for (u8 byColIndex = 0; byColIndex < tData.m_byCol; ++byColIndex)
				{					
					MdlLowHint(Ums_Mdl_Ue, ("ev_hduStyle_update_Rsp Row:%d, Column:%d, Layer:%d, Slot:%d, ChanIndex:%d,Name:%s.\n",
						byRowIndex, byColIndex, tData.m_atUnits[wIndex].m_byLayer, tData.m_atUnits[wIndex].m_bySlot, 
						tData.m_atUnits[wIndex].m_byChanIndex, tData.m_atUnits[wIndex].m_tName.m_abyAlias));
					
					++wIndex;
				}
			}
		}
		break;
	case ev_hduDel_rsp:
		{
			EmModifyHduRet emRet;
			TTPBrdPos tBrdPos;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tBrdPos, pDataBuf+sizeof(EmModifyHduRet));

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduDel_rsp Layer:%d, Slot:%d, Ret:%d.\n",
									 tBrdPos.m_byBrdLayer, tBrdPos.m_byBrdSlot, emRet));
		}
		break;

	case ev_cardInfo_Nty:
		{
			TTPBrdInfo tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_cardInfo_Nty Type:%d, Layer:%d, Slot:%d, IP:"TPIPFORMAT", Reged:%d, EqpReg:%d.\n", tInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType, 
									tInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer, tInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tInfo.m_tBrdCfg.m_tBrdPos.m_dwBrdIP),
									tInfo.m_bReg, tInfo.m_abEqpReg[0]));
		}
		break;
		
	case ev_card_used_nty:
		{	
			TTPBrdUsedInfo tInfo;
			TP_SAFE_CAST(tInfo, pDataBuf);

			MdlLowHint(Ums_Mdl_Ue, ("ev_card_used_nty  Type:%d, RegNum:%d, UseNum:%d.\n",
									 tInfo.m_emType, tInfo.m_wRegNum, tInfo.m_wUsedNum));
		}	
		break;
	case ev_cardAdd_rsp:
		{
			TTPBrdCfg tBrdCfg;
			TP_SAFE_CAST(tBrdCfg, pDataBuf);
			EmTpBoardRet emRes;
			TP_SAFE_CAST(emRes, pDataBuf + sizeof(TTPBrdCfg));
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardAdd_rsp Type:(%d->%s), Layer:%d, Slot:%d, IP:"TPIPFORMAT", Reason:(%d->%s).\n", TpEnumIdString(EMBrdType, tBrdCfg.m_tBrdPos.m_emBrdType), 
									tBrdCfg.m_tBrdPos.m_byBrdLayer, tBrdCfg.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tBrdCfg.m_tBrdPos.m_dwBrdIP), TpEnumIdString(EmTpBoardRet, emRes)));
		}
		break;
	case ev_cardDel_rsp:
		{
			TTPBrdCfg tDel;
			TP_SAFE_CAST(tDel, pDataBuf);
			EmTpBoardRet emDelRes;
			TP_SAFE_CAST(emDelRes, pDataBuf + sizeof(TTPBrdCfg));
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardDel_rsp Type:(%d->%s), Layer:%d, Slot:%d, IP:"TPIPFORMAT", Reason:(%d->%s).\n", TpEnumIdString(EMBrdType, tDel.m_tBrdPos.m_emBrdType), 
									tDel.m_tBrdPos.m_byBrdLayer, tDel.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tDel.m_tBrdPos.m_dwBrdIP), TpEnumIdString(EmTpBoardRet, emDelRes)));
		}
		break;
	case ev_cardModify_rsp:
		{
			TTPBrdCfg tModify;
			TP_SAFE_CAST(tModify, pDataBuf);
			EmTpBoardRet emModifyRes;
			TP_SAFE_CAST(emModifyRes, pDataBuf + sizeof(TTPBrdCfg));
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardModify_rsp Type:(%d->%s), Layer:%d, Slot:%d, IP:"TPIPFORMAT", Reason:(%d->%s).\n", TpEnumIdString(EMBrdType, tModify.m_tBrdPos.m_emBrdType), 
									tModify.m_tBrdPos.m_byBrdLayer, tModify.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tModify.m_tBrdPos.m_dwBrdIP), TpEnumIdString(EmTpBoardRet, emModifyRes)));
		}
		break;
	case ev_cardModeDel_rsp:
		{
			TTPBrdMdlInfo tDel;
			TP_SAFE_CAST(tDel, pDataBuf);
			EmTpBoardRet emDelRes;
			TP_SAFE_CAST(emDelRes, pDataBuf + sizeof(TTPBrdMdlInfo));
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardModeDel_rsp Layer:%d, Slot:%d, MdlType:(%d->%s), MdlAlias:%s, Reason:(%d->%s).\n",
									tDel.m_byLayer, tDel.m_bySlot, TpEnumIdString(EMEqpType, tDel.m_atMdlCfg[0].m_emEqpType), 
									tDel.m_atMdlCfg[0].m_szEqpAlias, TpEnumIdString(EmTpBoardRet, emDelRes)));
		}
		break;
	case ev_cardModeModify_rsp:
		{
			TTPBrdMdlInfo tMdl;
			TP_SAFE_CAST(tMdl, pDataBuf);
			EmTpBoardRet emMdlRes;
			TP_SAFE_CAST(emMdlRes, pDataBuf + sizeof(TTPBrdMdlInfo));
			MdlLowHint(Ums_Mdl_Ue, ("ev_cardModeModify_rsp Layer:%d, Slot:%d, MdlType:(%d->%s), MdlAlias:%s, Reason:(%d->%s).\n",
									tMdl.m_byLayer, tMdl.m_bySlot, TpEnumIdString(EMEqpType, tMdl.m_atMdlCfg[0].m_emEqpType), 
									tMdl.m_atMdlCfg[0].m_szEqpAlias, TpEnumIdString(EmTpBoardRet, emMdlRes)));
		}
		break;
	case ev_card_upgrade_res:
		{
			u8 byLayer;
			TP_SAFE_CAST(byLayer, pDataBuf);
			u8 bySlot;
			TP_SAFE_CAST(bySlot, pDataBuf + sizeof(u8));
			BOOL32 bRes;
			TP_SAFE_CAST(bRes, pDataBuf + sizeof(u8) + sizeof(u8));
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_upgrade_res layer:%d, slot:%d, res:%d\n", byLayer, bySlot, bRes));
		}
		break;
	case ev_NMServerAdd_rsp:
		{
			EmModifyNMServerRet emRet;
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tCfg, pDataBuf+sizeof(EmModifyNMServerRet));
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerAdd_rsp IsServerOn:%d, GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT", Ret:%d.\n",
									 tCfg.bIsServerOn, tCfg.wNMGetSetPort, tCfg.WNMTrapPort,
									 tCfg.achNMReadCommunity, tCfg.achNMWriteCommunity,
									 tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP), emRet));
		}
		break;

	case ev_NMServerMdy_rsp:
		{
			EmModifyNMServerRet emRet;
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tCfg, pDataBuf+sizeof(EmModifyNMServerRet));
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerMdy_rsp IsServerOn:%d, GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT", Ret:%d.\n",
							    	 tCfg.bIsServerOn, tCfg.wNMGetSetPort, tCfg.WNMTrapPort,
									 tCfg.achNMReadCommunity, tCfg.achNMWriteCommunity,
									 tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP), emRet));
		}
		break;
	case ev_NMServerDel_rsp:
		{
			EmModifyNMServerRet emRet;
			TTPNMServerCfg tCfg;
			TP_SAFE_CAST(emRet, pDataBuf);
			TP_SAFE_CAST(tCfg, pDataBuf+sizeof(EmModifyNMServerRet));
			MdlLowHint(Ums_Mdl_Ue, ("ev_NMServerDel_rsp IsServerOn:%d, GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT", Ret:%d.\n",
									 tCfg.bIsServerOn, tCfg.wNMGetSetPort, tCfg.WNMTrapPort,
									 tCfg.achNMReadCommunity, tCfg.achNMWriteCommunity,
									 tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP), emRet));
		}
		break;
		
	case ev_NMServer_nty:
		{
			u16 wValidNum = 0;
			TP_SAFE_CAST(wValidNum, pDataBuf);
			TTPNMServerCfg tCfg;
			for (u16 wIndex = 0; wIndex < wValidNum; ++wIndex)
			{
				TP_SAFE_CAST(tCfg, pDataBuf+sizeof(u16)+sizeof(TTPNMServerCfg)*wIndex);
				MdlLowHint(Ums_Mdl_Ue, ("ev_NMServer_nty IsServerOn:%d, GetSetPort:%d, TrapPort:%d, ReadCom:%s, WriteCom:%s, NO:%d, IP:"TPIPFORMAT".\n",
										 tCfg.bIsServerOn, tCfg.wNMGetSetPort, tCfg.WNMTrapPort,
										 tCfg.achNMReadCommunity, tCfg.achNMWriteCommunity,
										 tCfg.wNMServerNO, Tpu32ToIP(tCfg.dwNMServerIP)));
			}
		}
		break;
		
	case ev_hduUpdate_rsp:
		{
			TTPBrdUpGrade tInfo;
			EmUpdateHduRet emRet;
			TP_SAFE_CAST(tInfo, pDataBuf);
			TP_SAFE_CAST(emRet, pDataBuf+sizeof(TTPBrdUpGrade));

			MdlLowHint(Ums_Mdl_Ue, ("ev_hduUpdate_rsp Layer:%d, Slot:%d, FileName:%s, Res:%d.\n",
									 tInfo.m_byLayer, tInfo.m_bySlot, tInfo.m_szFileName, emRet));
		}
		break;
	case ev_licenseOutput_Ind:
		{
			BOOL32 bRet;
			TP_SAFE_CAST(bRet, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_licenseOutput_Ind ret:%d, filename:%s.\n", bRet, (pDataBuf + sizeof(BOOL32))));
		}
		break;

	case ev_SetQTEncryptInfo_Ind:
        {
			TTPQTEncryptInfo tEncInfo;
            BOOL32 bRet;
            TP_SAFE_CAST(tEncInfo, pDataBuf);
            TP_SAFE_CAST(bRet, pDataBuf + sizeof(TTPQTEncryptInfo));
			MdlLowHint(Ums_Mdl_Ue, ("ev_SetQTEncryptInfo_Ind QTIP:%x, QTID:%d, Ret:%d\n",
				   tEncInfo.m_dwQuanTumIP, tEncInfo.m_dwQuanTumID, bRet));
		}
		break;

	case ev_QTMTInfo_Nty:
		{
            TTPQTEncryptInfo tNtyEncInfo;
			TP_SAFE_CAST(tNtyEncInfo, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_QTMTInfo_Nty QTIP:%x, QTID:%d\n", tNtyEncInfo.m_dwQuanTumIP, tNtyEncInfo.m_dwQuanTumID));

		}
		break;
	case ev_card_switchtelnetftp_rsp:
		{
			TPBoardSwitch tBrdSwitch;
			TP_SAFE_CAST(tBrdSwitch, pDataBuf);
			EmBoardSwitchRes emBrdSwitchRes;
			TP_SAFE_CAST(emBrdSwitchRes, pDataBuf + sizeof(TPBoardSwitch));
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_switchtelnetftp_rsp layer:%d, slot:%d, type:%d, bonoff:%d, res:%d.\n",
				tBrdSwitch.m_byLayer, tBrdSwitch.m_bySlot, tBrdSwitch.m_emType, tBrdSwitch.m_bSwitch, emBrdSwitchRes));

		}
		break;
	case ev_card_switchtelnet_ntf:
		{
			TPBoardSwitch tBrdSwitch;
			TP_SAFE_CAST(tBrdSwitch, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_switchtelnet_ntf layer:%d, slot:%d, type:%d, bonoff:%d.\n",
				tBrdSwitch.m_byLayer, tBrdSwitch.m_bySlot, tBrdSwitch.m_emType, tBrdSwitch.m_bSwitch));

		}
		break;
	case ev_card_switchftp_ntf:
		{
			TPBoardSwitch tBrdSwitch;
			TP_SAFE_CAST(tBrdSwitch, pDataBuf);
			MdlLowHint(Ums_Mdl_Ue, ("ev_card_switchftp_ntf layer:%d, slot:%d, type:%d, bonoff:%d.\n",
				            tBrdSwitch.m_byLayer, tBrdSwitch.m_bySlot, tBrdSwitch.m_emType, tBrdSwitch.m_bSwitch));
			
		}
		break;
	}
}