#include "handleboardservice.h"
#include "umsserver.h"
#include "umsobject.h"
#include "umsconfig.h"
#include "umsinnerstruct.h"
#include "umsxmltype.h"
#include "umsinnertype.h"
#include "umsconfigex.h"

#include "innereventumsserver.h"
#include "innereventumsboard.h"
#include "innereventxmpuvmp.h"

// �ⲿ��Ϣ
#include "eventoutumsboard.h"
#include "eventoutumsmediatrans.h"
#include "eventoutumseqp.h"
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif
TASKHANDLE		g_hNewUpdateTask; //�ļ������߳̾��
CUmsMainBoardUpdateTask	g_cMainBoardUpdateTask;
void* NewMainBoardUpdateTaskProc(void * pParam);
API void reboot();
//telnet��ftp������Ϣ����
API void telnetportoff();
API void telnetporton();
API void switchftp(u8 byFtpOn);
CUmsBoardHandleService::CUmsBoardHandleService(CTpObject* pcObject)
:CTpHandler(pcObject)
{
	m_bSshSwitch = FALSE;
	m_bIsUpdate = FALSE;
	m_wMpcBrdIndex = 0xFFFF;
}

CUmsBoardHandleService::~CUmsBoardHandleService()
{

}

void CUmsBoardHandleService::ReadBrdInfoFromUmsCfg()
{
	/*�����Ŵ������ļ��ж�ȡ������Ϣ*/
	TTPBrdInfo tBrdInfo;
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex++)
	{
		if (umsGetBoardInfo(tBrdInfo, wIndex))
		{
			m_tHandleBoard.AddBoard(tBrdInfo.m_tBrdCfg, wIndex);
			for (u16 wModeIndex = 0; wModeIndex < TP_UMS_BRD_MAXNUM_EQP; wModeIndex++)
			{
				if (tBrdInfo.m_tBrdMode[wModeIndex].m_wEqpId != 0)
				{
					m_tHandleBoard.m_abEqp[tBrdInfo.m_tBrdMode[wModeIndex].m_wEqpId - EQP_ID_VMP_BEG] = TRUE;
				}
				//else
				//{
				//	m_tHandleBoard.m_abEqp[tBrdInfo.m_tBrdMode[wModeIndex].m_wEqpId - EQP_ID_VMP_BEG] = FALSE;
				//}
				m_tHandleBoard.AddBrdMode(tBrdInfo.m_tBrdMode[wModeIndex], wIndex);
			}
			//֪ͨeqp������Ϣ
			if (em_unknow_brd == tBrdInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType)
			{
				continue;
			}
			else
			{
				UmsNotifyMsgToEqp(ev_board_cfg_info, &tBrdInfo, sizeof(TTPBrdInfo)); //������Ϣ���͵�eqp
			}	
		}
	}

	if (Ums_Run_On_Cri2 == CUmsConfigEx::GetInstance()->GetUmsRunType())
	{// �ڵ�ǰλ�ã�����һ��cri2�忨���Ա�ת��ҵ��ע���ϣ����ҵ���cri2�忨
		
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)		
		TBrdPosition tPos;
		BrdQueryPosition(&tPos);

		u8 byUISlot = CountUiSlotbySaveSlot(tPos.byBrdSlot, em_cri2_brd);
		u16 wBrdIndex = tPos.byBrdLayer*TP_BOARD_MAX_SLOT+byUISlot; // ����brdindex�Ǹ��ݽ���Ĳۺ�������ģ��мǡ�

		TTPBrdInfo tBrdNote;
		tBrdNote.m_bBrdUsed = TRUE;
		tBrdNote.m_tBrdMode[0].m_emEqpType = em_dataswitch_mdl;
		tBrdNote.m_tBrdCfg.m_byBrdID = wBrdIndex;
		tBrdNote.m_tBrdCfg.m_tBrdPos.m_byBrdLayer = tPos.byBrdLayer;
		tBrdNote.m_tBrdCfg.m_tBrdPos.m_byBrdSlot = tPos.byBrdSlot;
		tBrdNote.m_tBrdCfg.m_tBrdPos.m_dwBrdIP = GetLocalIP();
		tBrdNote.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_cri2_brd;

		m_tHandleBoard.AddBoard(tBrdNote.m_tBrdCfg, wBrdIndex);
		m_tHandleBoard.AddBrdMode(tBrdNote.m_tBrdMode[0], wBrdIndex);

		UmsNotifyMsgToEqp(ev_board_cfg_info, &tBrdNote, sizeof(TTPBrdInfo)); //������Ϣ���͵�eqp
#endif
	}
	else if (Ums_Run_On_Mpc2 == CUmsConfigEx::GetInstance()->GetUmsRunType())
	{
		ReadMpcInfo();
	}
	else
	{

	}
	return;
}

//���������ļ���Ϣ
void CUmsBoardHandleService::UpdateBrdCfgInfo(u16 wBrdIndex)
{
	umsSetBoardInfo(m_tHandleBoard.m_atBrdCfg[wBrdIndex], wBrdIndex);
}

BOOL32 CUmsBoardHandleService::Create()
{
	ReadBrdInfoFromUmsCfg();
	return CTpHandler::Create();
}

void CUmsBoardHandleService::ShowBoard()
{
	tpHint(Ums_Mdl_Service, "Show Board Info:\n\n");

	TTPBrdCfg* ptBrdCfg = NULL;
	TTPMdlCfg* ptMdlCfg = NULL;
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex++)
	{
		ptBrdCfg = &(m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdCfg);
		ptMdlCfg = m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdMode;
		if (em_unknow_brd == ptBrdCfg->m_tBrdPos.m_emBrdType)
		{
			continue;
		}
		msgprintnotime("BrdID:%d, BrdType:(%d->%s), BrdLayer:%d, BrdSlot:%d, BrdIp:"TPIPFORMAT", BrdState:%d(0-offline, 1-online), HardVer:%s, Ver:%s,Telnet:%d, Ftp: %d.\n",
						ptBrdCfg->m_byBrdID, TpEnumIdString(EMBrdType, ptBrdCfg->m_tBrdPos.m_emBrdType), ptBrdCfg->m_tBrdPos.m_byBrdLayer,
						ptBrdCfg->m_tBrdPos.m_byBrdSlot, Tpu32ToIP(ptBrdCfg->m_tBrdPos.m_dwBrdIP), m_tHandleBoard.m_atBrdCfg[wIndex].m_bReg,
						m_tHandleBoard.m_tBrdVer[wIndex].m_achBrdVer, m_tHandleBoard.m_tBrdVer[wIndex].m_achSoftVer,
						m_tHandleBoard.m_tBrdTelFtpStat[wIndex].m_bTelnetStatus,m_tHandleBoard.m_tBrdTelFtpStat[wIndex].m_bFtpStatus);
		//ģʽ��ʾ
		for(u16 wModeIndex = 0; wModeIndex < TP_UMS_BRD_MAXNUM_EQP; wModeIndex++)
		{
			if (em_unknow_mdl == ptMdlCfg->m_emEqpType)
			{
				++ptMdlCfg;
				continue;
			}
			msgprintnotime("	BrdModeType:(%d->%s)(%d-%s), BrdModeAlias:%s", TpEnumIdString(EMEqpType, ptMdlCfg->m_emEqpType), 
				TpEnumIdString(EMEqpModleType, ptMdlCfg->m_emEqpMdlType), ptMdlCfg->m_szEqpAlias);
			if (em_audmix_mdl == ptMdlCfg->m_emEqpType)
			{
				msgprintnotime(", AudmixNum:%d", ptMdlCfg->m_byAudmixNum);
			}
			msgprintnotime(", EqpId:%d, EqpState:%d.\n", ptMdlCfg->m_wEqpId, m_tHandleBoard.m_atBrdCfg[wIndex].m_abEqpReg[wModeIndex]);
			ptMdlCfg++;
		}
		msgprintnotime("\n");
	}
	msgprintnotime("m_bIsUpdate=%d, m_wMpcBrdIndex:%d,m_bSwitchSshInfo:%d.\n", m_bIsUpdate, m_wMpcBrdIndex,m_bSshSwitch);
	msgprintnotime("\n");
}

BOOL32 CUmsBoardHandleService::Handler(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	u8* pData = ptMsg->GetBody();
	u16 wSize = ptMsg->GetBodyLen();
	
	switch (wEvent)
	{
	case ev_SysCmsLoginInd:
		{
			EventLogin(pData, wSize);
		}
		break;
	//eqp������Ϣ
	case ev_board_reg_result:
		{
			EventBrdRegResult(pData, wSize);
		}
		break;
	case ev_board_mode_reg_result:
		{
			EventBrdModeRegResult(pData, wSize);
		}
		break;
	case ev_board_disc_nty:
		{
			EventBrdDisc(pData, wSize);
		}
		break;
	case ev_board_used_nty:
		{
			EventBrdUsed(pData, wSize);
		}
		break;
	case ev_board_getversion_ack:
		{
			EventBoardVerAck(pData, wSize);
		}
		break;
	case ev_board_upgrade_res:
		{
			EventBrdUpdateAck(pData, wSize);
		}
		break;
	case ev_board_switchtelnetftpe_res:
		{
			EventBrdSwitchTelFtpRes(pData, wSize);
		}
		break;
		// from xmpu
	case evXmpu_res_usd_info_res:
		{
			EventXmpuResUsed(pData, wSize);
		}
		break;
	//ά�����߹�����Ϣ
	case ev_cardAdd_req:
		{
			EventAddBoard(pData, wSize);
		}
		break;
		
	case ev_cardDel_req:
		{
			EventDelBoard(pData, wSize);
		}
		break;
		
	case ev_cardModify_req:
		{
			EventModifyBoard(pData, wSize);
		}
		break;
	
		
	case ev_cardModeDel_req:
		{
			EventDelBoardMode(pData, wSize);
		}
		break;
		
	case ev_cardModeModify_req:
		{
			EventModifyBoardMode(pData, wSize);
		}
		break;
	case ev_card_reboot_req:
		{
			EventBrdReoot(pData, wSize);
		}
		break;
	case ev_card_upgrade_req:
		{
			EventBrdUpGrade(pData, wSize);
		}
		break;

	case ev_card_eqp_used_req:
		{
			EventEqpUsedReq(pData, wSize);
		}
		break;
	case ev_TPUpdate_Task_Return:
		{
			EventUpdateTaskReturn(pData, wSize);
		}
		break;
	case ev_card_switchtelnetftp_req:
		{
		    EventSwitchTelnetFtp(pData, wSize);  
		}
		break;
	default :
		return FALSE;
		//	break;
	}
	
	return TRUE;
}

void CUmsBoardHandleService::EventLogin(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex++)
	{
		if (em_unknow_brd  == m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			continue;
		}
		TTPBrdInfo tUiInfo;
		u8 achHardVer[TP_BOARD_VERSION_LEN] = {0};
		u8 achSoftVer[TP_BOARD_VERSION_LEN] = {0};
		memcpy(achHardVer, m_tHandleBoard.m_tBrdVer[wIndex].m_achBrdVer, sizeof(achHardVer));
		memcpy(achSoftVer, m_tHandleBoard.m_tBrdVer[wIndex].m_achSoftVer, sizeof(achSoftVer));
		
		CountUiBrdLocation(wIndex, tUiInfo);
		u8 abyBuf[sizeof(TTPBrdInfo) + 2 * sizeof(u8) * TP_BOARD_VERSION_LEN];
		memcpy(abyBuf, &tUiInfo, sizeof(TTPBrdInfo));
		memcpy(abyBuf + sizeof(TTPBrdInfo), achHardVer, sizeof(achHardVer));
		memcpy(abyBuf + sizeof(TTPBrdInfo) + sizeof(achHardVer), achSoftVer, sizeof(achSoftVer));
		//��ά�����߷�����Ч������Ϣ
		TpNotifyMsgToToolUserFromService(ev_cardInfo_Nty, (void*)abyBuf, sizeof(abyBuf));
		TelnetFtpStatNty(wIndex, em_BoardSwitch_all);//֪ͨ����telnet ��ftp������Ϣ
	}
		TPBoardSwitch tBrdSwitch;
		tBrdSwitch.m_bSwitch = m_bSshSwitch;
		TpNotifyMsgToUeFromService(ev_card_switchtelnet_ntf, &tBrdSwitch, sizeof(TPBoardSwitch), tUser);
#ifdef _USE_XMPUEQP_
	EMXmpuEqpType emType;
	emType = em_Xmpu_unknow;
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_res_usd_info_req);
	cMsg.SetBody((void*)&emType, sizeof(EMXmpuEqpType));
	cMsg.Post(UMS_XMPU_APP_INST, 0, UMS_SERVICE_APP_INST);

	EMEqpType emReqType = em_dataswitch_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emReqType, sizeof(EMEqpType));

#else
	//���� ����ϳ� ����ռ���������
	EMEqpType emType;
	emType = em_audmix_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
	emType = em_vmp_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
	emType = em_bas_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
	emType = em_audbas_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
	emType = em_vmp_tp_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
#endif
}

void CUmsBoardHandleService::EventBrdRegResult(u8* pDataBuf, u16 wDataSize)
{
	TBrdStateInfo tRegBrd;
	TP_SAFE_CAST(tRegBrd, pDataBuf);
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdRegResult] wIndex:%d, BrdRes:%d, bEqp1:%d, bEqp2:%d.\n",
							  tRegBrd.m_wIndex, tRegBrd.m_bReg, tRegBrd.m_abEqpReg[0], tRegBrd.m_abEqpReg[1]));

	BOOL32  bBrdReg = FALSE;
	TTPBrdInfo tUiInfo;
	u16 wBrdIndex = tRegBrd.m_wIndex;
	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdRegResult] BrdIndex %d Invalid.\n", wBrdIndex));
		return;
	}
	if (NeedStateNty(wBrdIndex, tRegBrd.m_abEqpReg))
	{
		bBrdReg = m_tHandleBoard.IsBrdReg(wBrdIndex);
		m_tHandleBoard.SetBrdRegInfo(tRegBrd, wBrdIndex);
		//���߻����Ҫ֪ͨά�����߽�����
		u8 achHardVer[TP_BOARD_VERSION_LEN] = {0};
		u8 achSoftVer[TP_BOARD_VERSION_LEN] = {0};
		memcpy(achHardVer, m_tHandleBoard.m_tBrdVer[wBrdIndex].m_achBrdVer, sizeof(achHardVer));
		memcpy(achSoftVer, m_tHandleBoard.m_tBrdVer[wBrdIndex].m_achSoftVer, sizeof(achSoftVer));
		
		CountUiBrdLocation(wBrdIndex, tUiInfo);
		u8 abyBuf[sizeof(TTPBrdInfo) + 2 * sizeof(u8) * TP_BOARD_VERSION_LEN];
		memcpy(abyBuf, &tUiInfo, sizeof(TTPBrdInfo));
		memcpy(abyBuf + sizeof(TTPBrdInfo), achHardVer, sizeof(achHardVer));
		memcpy(abyBuf + sizeof(TTPBrdInfo) + sizeof(achHardVer), achSoftVer, sizeof(achSoftVer));
		TpNotifyMsgToToolUserFromService(ev_cardInfo_Nty, abyBuf, sizeof(abyBuf));

	    EMBrdType emBrdType = m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType;
		if ((em_is22_brd != emBrdType) &&
			(em_cri2_brd != emBrdType) &&
			(em_mpc_brd != emBrdType)  &&
			(em_mpu2_tp_brd != emBrdType) &&
			(em_apu2_tp_brd != emBrdType))
		{
            return;
		}

		if (tRegBrd.m_bReg && !bBrdReg)
		{//�忨���ߣ��ر���ftp��telnetport
			TLogUser tLogUser;
			TPBoardSwitch tBoardSwitch;

			MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdRegResult] Close Lay:%d Slot:%d ftp telnet.\n", 
				    tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer, 
					tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot));

			tBoardSwitch.m_byLayer = tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
			tBoardSwitch.m_bySlot = tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;
			tBoardSwitch.m_emType = em_BoardSwitch_telnet;
			tBoardSwitch.m_bSwitch = FALSE;
			
			CTpMsg cMsg;
			cMsg.SetEvent(ev_card_switchtelnetftp_req);
			cMsg.SetBody(&tLogUser, sizeof(TLogUser));
			cMsg.CatBody(&tBoardSwitch, sizeof(tBoardSwitch));
			cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);

			tBoardSwitch.m_emType = em_BoardSwitch_ftp;

			cMsg.SetBody(&tLogUser, sizeof(TLogUser));
			cMsg.CatBody(&tBoardSwitch, sizeof(tBoardSwitch));
			cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);

		}
	} 

}

//����ҵ��ע��
void CUmsBoardHandleService::EventBrdModeRegResult(u8* pDataBuf, u16 wDataSize)
{
	TBrdStateInfo tRgeMode;
	TP_SAFE_CAST(tRgeMode, pDataBuf);
	MdlHint(Ums_Mdl_Service, ("[EventBrdModeRegResult] wIndex:%d, BrdModeRes:%d.\n",
							  tRgeMode.m_wIndex, tRgeMode.m_bReg));

	u16 wBrdIndex = tRgeMode.m_wIndex;
	if (wBrdIndex <0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlHint(Ums_Mdl_Service, ("[EventBrdModeRegResult] BrdIndex Invalid.\n"));
		return;
	}

}

void CUmsBoardHandleService::EventBrdDisc(u8* pDataBuf, u16 wDataSize)
{
	TBrdStateInfo tState;
	TP_SAFE_CAST(tState, pDataBuf);
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdDisc] wIndex:%d, BrdState:%d.\n",
							  tState.m_wIndex, tState.m_bReg));
	TTPBrdInfo tUiInfo;
	u16 wBrdIndex = tState.m_wIndex;
	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdDisc] BrdIndex %d Invalid.\n", wBrdIndex));
		return;
	}

	m_tHandleBoard.SetBrdRegInfo(tState, wBrdIndex);
	u8 achHardVer[TP_BOARD_VERSION_LEN] = {0};
	u8 achSoftVer[TP_BOARD_VERSION_LEN] = {0};
	memcpy(achHardVer, m_tHandleBoard.m_tBrdVer[wBrdIndex].m_achBrdVer, sizeof(achHardVer));
	memcpy(achSoftVer, m_tHandleBoard.m_tBrdVer[wBrdIndex].m_achSoftVer, sizeof(achSoftVer));
	
	u8 abyBuf[sizeof(TTPBrdInfo) + 2 * sizeof(u8) * TP_BOARD_VERSION_LEN];
	CountUiBrdLocation(wBrdIndex, tUiInfo);
	memcpy(abyBuf, &tUiInfo, sizeof(TTPBrdInfo));
	memcpy(abyBuf + sizeof(TTPBrdInfo), achHardVer, sizeof(achHardVer));
	memcpy(abyBuf + sizeof(TTPBrdInfo) + sizeof(achHardVer), achSoftVer, sizeof(achSoftVer));
	TpNotifyMsgToToolUserFromService(ev_cardInfo_Nty, abyBuf, sizeof(abyBuf));
	
	//�忨���������ftp��telnet״̬
	m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].Clear();
}

void CUmsBoardHandleService::EventBrdUsed(u8* pDataBuf, u16 wDataSize)
{
	TTPBrdUsedInfo tUsed;
	TP_SAFE_CAST(tUsed, pDataBuf);
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdUsed] Type:(%d->%s), Reg:%d, Used:%d.\n",
							 TpEnumIdString(EMEqpType, tUsed.m_emType), tUsed.m_wRegNum, tUsed.m_wUsedNum));
	
	//����������������䣬Ҫ֪ͨ��UMC

		//�㲥��Ϣ�����е�¼��umc
		TLogUser tUser;
		TpNotifyMsgToUeFromService(ev_conf_bas_used_nty, &tUsed, sizeof(TTPBrdUsedInfo), tUser);
	
	//֪ͨά������
	TpNotifyMsgToToolUserFromService(ev_card_used_nty, &tUsed, sizeof(TTPBrdUsedInfo));
}

void CUmsBoardHandleService::EventXmpuResUsed(u8* pDataBuf, u16 wDataSize)
{
	TTPBrdUsedInfo tUsed;
	TP_SAFE_CAST(tUsed, pDataBuf);
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventXmpuResUsed] Type:(%d->%s), Reg:%d, Used:%d.\n",
		TpEnumIdString(EMEqpType, tUsed.m_emType), tUsed.m_wRegNum, tUsed.m_wUsedNum));

	//����������������䣬Ҫ֪ͨ��UMC
// 	if (em_bas_mdl == tUsed.m_emType || em_audbas_mdl == tUsed.m_emType)
// 	{
		//�㲥��Ϣ�����е�¼��umc
		TLogUser tUser;
		TpNotifyMsgToUeFromService(ev_conf_bas_used_nty, &tUsed, sizeof(TTPBrdUsedInfo), tUser);
	//}
	//֪ͨά������
	TpNotifyMsgToToolUserFromService(ev_card_used_nty, &tUsed, sizeof(TTPBrdUsedInfo));
}

void CUmsBoardHandleService::EventAddBoard(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TTPBrdCfg tAddBrdInfo;
	TTPBrdCfg tSavedInfo;
	TP_SAFE_CAST(tUser, pDataBuf);
	TP_SAFE_CAST(tAddBrdInfo, (pDataBuf+sizeof(TLogUser)));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventAddBoard] Add Board: Type:(%d->%s), Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n", 
							   TpEnumIdString(EMBrdType, tAddBrdInfo.m_tBrdPos.m_emBrdType),
							   tAddBrdInfo.m_tBrdPos.m_byBrdLayer, tAddBrdInfo.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tAddBrdInfo.m_tBrdPos.m_dwBrdIP)));

	u16 wIndex = TP_INVALID_INDEX;
	u8 byBrdNum = 0;
	EmTpBoardRet emAddRes = emTP_Board_AddSuccess;
	EmTpBoardRet emMdlRet = emTP_Board_Mode_ModifySuccess;
	do 
	{
		//��������У��
		u8 byBrdType = tAddBrdInfo.m_tBrdPos.m_emBrdType;
		u8 byBrdLayer = tAddBrdInfo.m_tBrdPos.m_byBrdLayer;
		u8 byBrdSlot = tAddBrdInfo.m_tBrdPos.m_byBrdSlot;
		
		if ( (em_unknow_brd == byBrdType) || (byBrdType > em_brdtype_end) )
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventAddBoard] Add Board, brdtype unknown.\n"));
			emAddRes = emTP_Board_UnKonw;
			break;
		}
		
		if ( ( (byBrdLayer < 0) || (byBrdLayer >= TP_BOARD_MAX_LAYER) )
			|| ( (byBrdSlot < 0) ||(byBrdSlot >= TP_BOARD_MAX_SLOT) ) )
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventAddBoard] Add Board, BrdLocation layer:%d, slot:%d Invalid.\n", byBrdLayer, byBrdSlot));
			emAddRes = emTP_Board_UnKnowLoc;
			break;
		}
		//�ȸ��ݲ�Ų�λ�Ŷ�λ��Ҫ��ӵ������������
		wIndex = m_tHandleBoard.FindBrdIndex(byBrdLayer, byBrdSlot);
		//�жϸ�λ���Ƿ��Ѿ����ڵ���
		if (em_unknow_brd != m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventAddBoard] Add Board, board has exsit in the location.\n"));
			emAddRes = emTP_Board_Repeat;
			break;
		}

		if ( tAddBrdInfo.m_tBrdPos.m_byBrdSlot == NORMAL_BRD_UI_SLOT_DOWN_BOUNDS && tAddBrdInfo.m_tBrdPos.m_emBrdType != em_is22_brd)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventAddBoard] slot 7 is not is22.\n"));
			emAddRes = emTP_Board_UnKonw;
		}
		
		//���Լ�����ж�
		if (emTP_Board_AddSuccess != emAddRes)
		{
			break;
		}

		//�ҵ����е�λ����ӵ�����Ϣ
		tAddBrdInfo.m_byBrdID = (u8)(wIndex);
		memcpy(&tSavedInfo, &tAddBrdInfo, sizeof(TTPBrdCfg));
		tSavedInfo.m_tBrdPos.m_byBrdSlot = CountBrdSavedSlot(tAddBrdInfo.m_tBrdPos.m_byBrdSlot, tAddBrdInfo.m_tBrdPos.m_emBrdType);

		m_tHandleBoard.AddBoard(tSavedInfo, wIndex);
		m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdCfg;

		//��ģʽ���Ӵ���
		if(IsBrdSingleMdl(tAddBrdInfo.m_tBrdPos.m_emBrdType))
		{
			emMdlRet = SingleBrdMdlHandler(tAddBrdInfo.m_tBrdPos.m_emBrdType, wIndex);
		}

	} while (0);
	
	//��ά�����߷��͵���������
	u8 abyBuf[sizeof(TTPBrdCfg) + sizeof(EmTpBoardRet)] = {0};
	memcpy(abyBuf, &tAddBrdInfo, sizeof(TTPBrdCfg));
	memcpy(abyBuf + sizeof(TTPBrdCfg), &emAddRes, sizeof(EmTpBoardRet));
	
	if (emTP_Board_AddSuccess == emAddRes)
	{
		UpdateBrdCfgInfo(wIndex);
		UmsNotifyMsgToEqp(ev_board_cfg_info, &m_tHandleBoard.m_atBrdCfg[wIndex], sizeof(TTPBrdInfo));
	}
	//ά�����߽��淢����ӵ���ɹ���Ϣ
	TpNotifyMsgToToolUserFromService(ev_cardAdd_rsp, abyBuf, sizeof(abyBuf));
	
	if(IsBrdSingleMdl(tAddBrdInfo.m_tBrdPos.m_emBrdType))
	{
		TTPBrdMdlInfo tMdl;
		memcpy(&tMdl.m_atMdlCfg[0], &m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdMode[0], sizeof(TTPMdlCfg));
		memcpy(&tMdl.m_byLayer, &tAddBrdInfo.m_tBrdPos.m_byBrdLayer, sizeof(u8));
		memcpy(&tMdl.m_bySlot, &tAddBrdInfo.m_tBrdPos.m_byBrdSlot, sizeof(u8));
		tMdl.m_byIndex = 1;//��ģʽ����ֻ��һ������ģʽ
		u8 abyMdlBuf[sizeof(TTPBrdMdlInfo) + sizeof(EmTpBoardRet)] = {0};
		memcpy(abyMdlBuf, &tMdl, sizeof(TTPBrdMdlInfo));
		memcpy(abyMdlBuf + sizeof(TTPBrdMdlInfo), &emMdlRet, sizeof(EmTpBoardRet));
		TpNotifyMsgToToolUserFromService(ev_cardModeModify_rsp, abyMdlBuf, sizeof(abyMdlBuf));
	}
	
}

void CUmsBoardHandleService::EventDelBoard(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	TTPBrdCfg tDelBrdInfo;
	TP_SAFE_CAST(tDelBrdInfo, pDataBuf + sizeof(TLogUser));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoard] Delete Board: Layer:%d, Slot:%d.\n",
								tDelBrdInfo.m_tBrdPos.m_byBrdLayer, tDelBrdInfo.m_tBrdPos.m_byBrdSlot) );

	TTPBrdCfg* ptDelBrd = NULL;
	BOOL32 bDelete = FALSE;
	u8 byBrdNum = 0;
	EmTpBoardRet emDelResult;
	emDelResult = emTP_Board_DelSuccess;
	u16 wBrdIndex = TP_INVALID_INDEX;
	do 
	{
		//��������У��
		u8 byBrdType = tDelBrdInfo.m_tBrdPos.m_emBrdType;
		u8 byBrdLayer = tDelBrdInfo.m_tBrdPos.m_byBrdLayer;
		u8 byBrdSlot = tDelBrdInfo.m_tBrdPos.m_byBrdSlot;
		
		if (tDelBrdInfo.m_byBrdID >= TP_BOARD_MAX_NUM)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoard] Del Board, BrdID %d more than MaxNum.\n", tDelBrdInfo.m_byBrdID));
			emDelResult = emTP_Board_MaxNum;
			break;
		}
		//���Ҫɾ����������
		if ((byBrdType >= em_brdtype_end) || (byBrdType < em_unknow_brd))
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoard] Del Board, Board Type (%d->%s) Unknow.\n", TpEnumIdString(EMBrdType, byBrdType)));
			emDelResult = emTP_Board_UnKonw;
			break;
		}
		//���Ҫɾ������λ��
		if ( ( (byBrdLayer > TP_BOARD_MAX_LAYER) || (byBrdLayer < 0) )
			&& ( (byBrdSlot > TP_BOARD_MAX_SLOT) || (byBrdSlot < 0) ) )
		{
			MdlError(Ums_Mdl_Service, ("[EventDelBoard] Del Board, Board layer %d and slot %d Invalid.\n", byBrdLayer, byBrdSlot));
			emDelResult = emTP_Board_UnKnowLoc;
			break;
		}
		
		//ɾ�����������ݲ�ŲۺŶ�λ
		wBrdIndex = m_tHandleBoard.FindBrdIndex(byBrdLayer, byBrdSlot);
		if (wBrdIndex >= TP_BOARD_MAX_NUM)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoard] Del Board, BrdIndex %d invalid.\n", wBrdIndex));
			emDelResult = emTP_Board_MaxNum;
			break;
		}
		ptDelBrd = m_tHandleBoard.DelBoard(wBrdIndex);

	} while (0);
	
	if (NULL == ptDelBrd)
	{
		MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoard] Del Board, ptDelBrd is Null.\n"));
		return;
	}
	//��ά�����߷��͵���������
	TTPBrdInfo tUiInfo;
	u8 abyBuf[sizeof(TTPBrdCfg) + sizeof(EmTpBoardRet)] = {0};
	CountUiBrdLocation(wBrdIndex, tUiInfo);
	memcpy(abyBuf, &tUiInfo.m_tBrdCfg, sizeof(TTPBrdCfg));
	memcpy(abyBuf + sizeof(TTPBrdCfg), &emDelResult, sizeof(EmTpBoardRet));
	if (emDelResult == emTP_Board_DelSuccess)
	{
		UpdateBrdCfgInfo(wBrdIndex);
		UmsNotifyMsgToEqp(ev_board_del_nty, &wBrdIndex, sizeof(u16));
	}
	TpNotifyMsgToToolUserFromService(ev_cardDel_rsp, abyBuf, sizeof(abyBuf));
}

void CUmsBoardHandleService::EventModifyBoard(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	TTPBrdCfg tModifyBrd;
	TP_SAFE_CAST(tModifyBrd, pDataBuf + sizeof(TLogUser));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoard] Modify Board: Type:(%d->%s), Layer:%d, Slot:%d, IP:"TPIPFORMAT".\n",
								TpEnumIdString(EMBrdType, tModifyBrd.m_tBrdPos.m_emBrdType), tModifyBrd.m_tBrdPos.m_byBrdLayer, 
								tModifyBrd.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(tModifyBrd.m_tBrdPos.m_dwBrdIP)));

	u16 wBrdIndex = TP_INVALID_INDEX;
	BOOL32 bModify = FALSE;
	EmTpBoardRet emModifyRes;
	emModifyRes = emTP_Board_ModifySuccess;

	TTPBrdCfg* ptSrcBrd = NULL;
	do 
	{
		u8 byBrdType = tModifyBrd.m_tBrdPos.m_emBrdType;
		u8 byBrdLayer = tModifyBrd.m_tBrdPos.m_byBrdLayer;
		u8 byBrdSlot = tModifyBrd.m_tBrdPos.m_byBrdSlot;
		u32_ip dwBrdIp = tModifyBrd.m_tBrdPos.m_dwBrdIP;
		
		wBrdIndex = m_tHandleBoard.FindBrdIndex(byBrdLayer, byBrdSlot);
		//Խ���ж�
		if (wBrdIndex >= TP_BOARD_MAX_NUM)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoard] Modify Board, BrdID more than MaxNum.\n"));
			emModifyRes = emTP_Board_MaxNum;
			break;
		}
		//��Ų�λ���ж�
		if ( ( (byBrdLayer >= TP_BOARD_MAX_LAYER) || (byBrdLayer < 0) )
			&& ( (byBrdSlot >= TP_BOARD_MAX_SLOT) || (byBrdSlot < 0) ) )
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoard] Modify Board, Brd layer and slot invalid.\n"));
			emModifyRes = emTP_Board_UnKnowLoc;
			break;
		}

		//�ж�Ҫ���µ�λ�ð��Ӵ治����
		if (em_unknow_brd == m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoard] Modify Board, Board doesn't exist in this layer and slot.\n")); 
			//��λ�õ��岻����
			emModifyRes = emTP_Board_UnFind;
			break;
		}
		ptSrcBrd = &m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg;
		if (NULL == ptSrcBrd)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoard] Modify Board, pointer ptSrcBrd is null.\n"));
			break;
		}
		if ( (byBrdType == ptSrcBrd->m_tBrdPos.m_emBrdType) && (dwBrdIp == ptSrcBrd->m_tBrdPos.m_dwBrdIP))
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoard] Modify Board, Modify contents are same as original.\n"));
			emModifyRes = emTP_Board_Repeat;
			break;
		}
		
		if (emModifyRes != emTP_Board_ModifySuccess)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoard] Modify Board, Modify error.\n"));
			break;
		}
		
		//����
		tModifyBrd.m_tBrdPos.m_byBrdLayer = m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer;
		tModifyBrd.m_tBrdPos.m_byBrdSlot = m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot;
		m_tHandleBoard.ModifyBoard(tModifyBrd, wBrdIndex);
		bModify = TRUE;
	} while (0);
	
	//֪ͨά�����ߵ���������
	TTPBrdInfo tUiInfo;
	u8 abyBuf[sizeof(TTPBrdCfg) + sizeof(EmTpBoardRet)] = {0};
	CountUiBrdLocation(wBrdIndex, tUiInfo);
	memcpy(abyBuf, &tUiInfo.m_tBrdCfg, sizeof(TTPBrdCfg));
	memcpy(abyBuf + sizeof(TTPBrdCfg), &emModifyRes, sizeof(EmTpBoardRet));
	
	if (bModify)
	{
		UpdateBrdCfgInfo(wBrdIndex);
		UmsNotifyMsgToEqp(ev_board_modify_nty, ptSrcBrd, sizeof(TTPBrdCfg));
	}
	//֪ͨά������
	TpNotifyMsgToToolUserFromService(ev_cardModify_rsp, abyBuf, sizeof(abyBuf));
}

void CUmsBoardHandleService::EventDelBoardMode(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	TTPBrdMdlInfo tDelBrdMode;
	TP_SAFE_CAST(tDelBrdMode, pDataBuf + sizeof(TLogUser));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoardMode] Del BrdMode: Layer:%d, Slot:%d, MdlNum:%d, MdlType:(%d->%s), MdlAlias:%s.\n", tDelBrdMode.m_byLayer,
								tDelBrdMode.m_bySlot, tDelBrdMode.m_byIndex, TpEnumIdString(EMEqpModleType, tDelBrdMode.m_atMdlCfg[0].m_emEqpMdlType), tDelBrdMode.m_atMdlCfg[0].m_szEqpAlias));

	EmTpBoardRet emDelModeRst = emTP_Board_Mode_DelSuccess;
	
	u16 wBrdIndex = TP_INVALID_INDEX;
	u16 wMdlIndex = tDelBrdMode.m_byIndex;
	
	do 
	{
		u8 byBrdLayer = tDelBrdMode.m_byLayer;
		u8 byBrdSlot = tDelBrdMode.m_bySlot;
		
		wBrdIndex = m_tHandleBoard.FindBrdIndex(byBrdLayer, byBrdSlot);
		if (wBrdIndex >= TP_BOARD_MAX_NUM)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoardMode] Del BrdMode, BrdIndex %d More Than BrdMaxNum.\n", wBrdIndex));
			emDelModeRst = emTP_Board_MaxNum;
			break;
		}
		if (wMdlIndex >= TP_UMS_BRD_MAXNUM_EQP)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventDelBoardMode] Del BrdMode, MdlIndex %d more than Mdlmaxnum!\n", wMdlIndex));
			emDelModeRst = emTP_BrdMode_MaxNum;
 			break;
		}
		//���õ�����û������ģʽ
		if (!m_tHandleBoard.CheckBrdIsCfgMdl(wBrdIndex))
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode, Brd %d No configuration mode.\n", wBrdIndex));
			emDelModeRst = emTP_BrdMode_NoConfig;
			break;
		}
		for (u8 byIndex = 0; byIndex < TP_UMS_BRD_MAXNUM_EQP; byIndex++)
		{
			u16 wNum = m_tHandleBoard.GetEqpID(wBrdIndex, byIndex);
			if ( wNum >= EQP_ID_VMP_BEG)
			{
				m_tHandleBoard.m_abEqp[wNum - EQP_ID_VMP_BEG] = FALSE;
			}	
		}
		//ɾ��
		m_tHandleBoard.DelBrdMode(wBrdIndex);
	} while (0);
	
	u8 abyBuf[sizeof(TTPBrdMdlInfo) + sizeof(EmTpBoardRet)] = {0};
	
	memcpy(tDelBrdMode.m_atMdlCfg, m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdMode, sizeof(tDelBrdMode.m_atMdlCfg));
	memcpy(abyBuf, &tDelBrdMode, sizeof(TTPBrdMdlInfo));
	memcpy(abyBuf + sizeof(TTPBrdMdlInfo), &emDelModeRst, sizeof(EmTpBoardRet));
	if (emTP_Board_Mode_DelSuccess == emDelModeRst)
	{
		UpdateBrdCfgInfo(wBrdIndex);
		u8 abyMdlBuf[sizeof(u16) + sizeof(u16)] = {0};
		memcpy(abyMdlBuf, &wBrdIndex, sizeof(u16));
		memcpy(abyMdlBuf + sizeof(u16), &wMdlIndex, sizeof(u16));
		UmsNotifyMsgToEqp(ev_board_mode_del_nty, abyMdlBuf, sizeof(abyMdlBuf));
	}
	TpNotifyMsgToToolUserFromService(ev_cardModeDel_rsp, abyBuf, sizeof(abyBuf));
}

void CUmsBoardHandleService::EventModifyBoardMode(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	TTPBrdMdlInfo tModifyBrdMode;
	TP_SAFE_CAST(tModifyBrdMode, pDataBuf + sizeof(TLogUser));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode: Layer:%d, Slot:%d, MdlNum:%d, MdlType:(%d->%s).\n", 
								tModifyBrdMode.m_byLayer,tModifyBrdMode.m_bySlot, tModifyBrdMode.m_byIndex, 
								TpEnumIdString(EMEqpType, tModifyBrdMode.m_atMdlCfg[0].m_emEqpType)));

	TTPMdlCfg atMdlCfg[TP_UMS_BRD_MAXNUM_EQP];
	memcpy(atMdlCfg, &tModifyBrdMode.m_atMdlCfg, sizeof(atMdlCfg));
	EmTpBoardRet emModifyModeRst = emTP_Board_Mode_ModifySuccess;
	
	u16 wBrdIndex = TP_INVALID_INDEX;
	u16 wMdlNum = tModifyBrdMode.m_byIndex;
	TTPMdlCfg* ptBrdModify = NULL;
	do 
	{
		u8 byBrdLayer = tModifyBrdMode.m_byLayer;
		u8 byBrdSlot = tModifyBrdMode.m_bySlot;
		
		wBrdIndex = m_tHandleBoard.FindBrdIndex(byBrdLayer, byBrdSlot);
		if (wBrdIndex >= TP_BOARD_MAX_NUM)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode, BrdIndex %d More Than BrdMaxNum.\n", wBrdIndex));
			emModifyModeRst = emTP_Board_MaxNum;
			break;
		}
		//�ڽ�����������ģʽʱ���˴���Ӽ���ģʽ����
		if (wMdlNum >= TP_UMS_BRD_MAXNUM_EQP)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode, MdlIndex %d more than Mdlmaxnum!\n", wMdlNum));
			emModifyModeRst = emTP_BrdMode_MaxNum;
 			break;
		}
		EMBrdType emBrdType = m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType;
		if (em_unknow_brd == emBrdType)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode, BrdType Unknown.\n"));
			//��λ�õ�������δ֪
			emModifyModeRst = emTP_Board_UnKonw;
			break;
		}

		EMEqpType emErrorType = em_unknow_mdl;
		//��Ҫ��ӻ��޸ĵ�ģʽ�������λ�ð�������ƥ��
		if (!m_tHandleBoard.BrdTypeCheck(emBrdType, atMdlCfg, wMdlNum, emErrorType))
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode, SrcBrd type (%d->%s) modify modebrd type (%d->%s).\n", 
				TpEnumIdString(EMBrdType, emBrdType), TpEnumIdString(EMEqpType, emErrorType)));
			emModifyModeRst = emTP_BrdType_NotMatch_EqpType;
			break;
		}

		if (em_audmix_mdl == atMdlCfg[0].m_emEqpType && em_audmix_mdl == atMdlCfg[1].m_emEqpType)
		{
			u8 byTempMixNum = atMdlCfg[0].m_byAudmixNum + atMdlCfg[1].m_byAudmixNum;
			if (1 == atMdlCfg[0].m_byAudmixNum || 1 == atMdlCfg[1].m_byAudmixNum || byTempMixNum > TP_APU2_MAX_CHAN_NUM)
			{
				MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode AudMix ChanNum Error, layer:%d, slot:%d, brdtype:(%d->%s), audmixNum:%d, audmix(%d, %d).\n"
					, tModifyBrdMode.m_byLayer, tModifyBrdMode.m_bySlot, TpEnumIdString(EMBrdType, emBrdType), tModifyBrdMode.m_byIndex
					, tModifyBrdMode.m_atMdlCfg[0].m_byAudmixNum, tModifyBrdMode.m_atMdlCfg[1].m_byAudmixNum));
				emModifyModeRst = emTp_BrdMode_AudMix_MaxNum;
				break;
			}
		}

		u8 byTempMixNum = 0;
		for (u16 wIndex = 0; wIndex < TP_UMS_BRD_MAXNUM_EQP; ++wIndex)
		{
			if (em_audmix_mdl == atMdlCfg[wIndex].m_emEqpType )
			{
				byTempMixNum += atMdlCfg[wIndex].m_byAudmixNum;
				if (1 == atMdlCfg[wIndex].m_byAudmixNum || byTempMixNum > TP_APU2_MAX_CHAN_NUM)
				{
					MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode AudMix ChanNum Error, layer:%d, slot:%d, brdtype:(%d->%s), audmixNum:%d, audmix(%d, %d).\n"
						, tModifyBrdMode.m_byLayer, tModifyBrdMode.m_bySlot, TpEnumIdString(EMBrdType, emBrdType), tModifyBrdMode.m_byIndex
						, tModifyBrdMode.m_atMdlCfg[0].m_byAudmixNum, tModifyBrdMode.m_atMdlCfg[1].m_byAudmixNum));
					emModifyModeRst = emTp_BrdMode_AudMix_MaxNum;
					break;
				}
			}
		}

		if (emTP_Board_Mode_ModifySuccess != emModifyModeRst)
		{
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode, Modify Mode error.\n"));
			break;
		}

		if ( (em_mpu2ecard_brd == emBrdType || em_mpu2basic_brd == emBrdType) && (em_unknow_eqp_mdl == atMdlCfg[0].m_emEqpMdlType))
		{
			if (em_bas_mdl == atMdlCfg[0].m_emEqpType)
			{
				if (em_mpu2basic_brd == emBrdType)
				{
					atMdlCfg[0].m_emEqpMdlType = em_bas_basic_eqp_mdl;
				}
				else
				{
					if (wMdlNum > 1)
					{
						atMdlCfg[0].m_emEqpMdlType = em_bas_basic_eqp_mdl;
						atMdlCfg[1].m_emEqpMdlType = em_bas_basic_eqp_mdl;
					}
					else
					{
						atMdlCfg[0].m_emEqpMdlType = em_bas_enhanced_eqp_mdl;
					}
				}
			}
			else
			{
				if ( em_mpu2basic_brd == emBrdType )
				{
					atMdlCfg[0].m_emEqpMdlType = em_vmp_basic_eqp_mdl;
				}
				else
				{//ehance�İ忨 ����������basic�����һ��ehance����
					if ( wMdlNum > 1 )
					{
						atMdlCfg[0].m_emEqpMdlType = em_vmp_basic_eqp_mdl;
						atMdlCfg[1].m_emEqpMdlType = em_vmp_basic_eqp_mdl;
					}
					else
					{
						atMdlCfg[0].m_emEqpMdlType = em_vmp_enhanced_eqp_mdl;
					}
				}
			}
		}
		
		if (em_unknow_mdl == m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdMode[0].m_emEqpType)
		{//δ����ģʽ �������
			//����EqpID
			for (u8 byIndex = 0; byIndex < wMdlNum; byIndex++)
			{
				atMdlCfg[byIndex].m_wEqpId = m_tHandleBoard.MakeMdlEqpId(atMdlCfg[byIndex].m_emEqpType);
				if (!IsBrdSingleMdl(emBrdType) && (0 == atMdlCfg[byIndex].m_wEqpId))
				{
					emModifyModeRst = emTp_BrdMode_Resource_Full;
					break;
				}
			}
			//û��ģʽ��������Ӳ���
			m_tHandleBoard.AddBrdMode(atMdlCfg, wBrdIndex);
		}
		else
		{
			//����ģʽ�������޸Ĳ���
			if (IsModifiedSame(atMdlCfg, m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdMode))
			{//Ҫ�޸�������ԭ������ͬ
				MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventModifyBoardMode] Modify BrdMode, Modify mdltype:(%d->%s),mdlalias:%s repeat.\n",
					TpEnumIdString(EMEqpType, atMdlCfg[0].m_emEqpType), atMdlCfg[0].m_szEqpAlias));
				emModifyModeRst = emTP_BrdMode_Repeat;
				break;
			}

			//�޸�ǰ���ͷŷ��䵽��ģʽ��m_wEqpId��Ȼ��������
			if (!IsBrdSingleMdl(emBrdType))
			{
				for (u8 byIndex = 0; byIndex < wMdlNum; byIndex++)
				{
					u16 wEqpID = m_tHandleBoard.GetEqpID(wBrdIndex, byIndex);
					if (0 != wEqpID && wEqpID >=  EQP_ID_VMP_BEG)
					{
						m_tHandleBoard.m_abEqp[wEqpID - EQP_ID_VMP_BEG] = FALSE;
						atMdlCfg[byIndex].m_wEqpId = 0;
					}
					//���·���
					atMdlCfg[byIndex].m_wEqpId = m_tHandleBoard.MakeMdlEqpId(atMdlCfg[byIndex].m_emEqpType);
					if (!IsBrdSingleMdl(emBrdType) && (0 == atMdlCfg[byIndex].m_wEqpId))
					{
						emModifyModeRst = emTp_BrdMode_Resource_Full;
						break;
					}
				}
			}
			//�޸�
			m_tHandleBoard.ModifyBrdMode(atMdlCfg, wBrdIndex);
		}
	} while (0);

	u8 abyBuf[sizeof(TTPBrdMdlInfo) + sizeof(EmTpBoardRet)] = {0};
	memcpy(abyBuf, &tModifyBrdMode, sizeof(TTPBrdMdlInfo));
	memcpy(abyBuf + sizeof(TTPBrdMdlInfo), &emModifyModeRst, sizeof(EmTpBoardRet));

	if (emTP_Board_Mode_ModifySuccess == emModifyModeRst)
	{
		UpdateBrdCfgInfo(wBrdIndex);

		TTPBrdMdlInfo tMdl;
		memcpy(&tMdl, &tModifyBrdMode, sizeof(TTPBrdMdlInfo));
		memcpy(&tMdl.m_atMdlCfg, &m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdMode, sizeof(tMdl.m_atMdlCfg));
		UmsNotifyMsgToEqp(ev_board_mode_modify_nty, &tMdl, sizeof(tMdl));
	}
	TpNotifyMsgToToolUserFromService(ev_cardModeModify_rsp, abyBuf, sizeof(abyBuf));
}

void CUmsBoardHandleService::EventBrdReoot(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	TTPBrdPos tBrd;
	TP_SAFE_CAST(tBrd, pDataBuf + sizeof(TLogUser));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdReoot] Reboot Board: BrdType:%d, Layer:%d, Slot:%d, Ip:"TPIPFORMAT".\n", tBrd.m_emBrdType, 
								tBrd.m_byBrdLayer, tBrd.m_byBrdSlot, Tpu32ToIP(tBrd.m_dwBrdIP)));

	u16 wBrdIndex = 0;
	wBrdIndex = m_tHandleBoard.FindBrdIndex(tBrd.m_byBrdLayer, tBrd.m_byBrdSlot);
	//�жϸ�λ�ð��ӵĺϷ���
	if (wBrdIndex <0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdReoot] Reboot Board, BrdIndex More Than BrdMaxNum.\n"));
		return;
	}



	if (em_mpc_brd == m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType)
	{
		//mpc����
		MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdReoot] mpc2 board reboot.\n"));
		system("reboot");
		return;
	}
	//֪ͨeqp����
	UmsNotifyMsgToEqp(ev_board_reboot_req, &wBrdIndex, sizeof(u16));
}
void CUmsBoardHandleService::EventBoardVerAck(u8* pDataBuf, u16 wDataSize)
{
	TBrdVersion tVer;
	TP_SAFE_CAST(tVer, pDataBuf);
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBoardVerAck] HardVer: BrdIndex:%d, ver:%s.\n", tVer.m_wBrdIndex, tVer.m_achBrdVer));

	m_tHandleBoard.m_tBrdVer[tVer.m_wBrdIndex].m_wBrdIndex = tVer.m_wBrdIndex;
	memcpy(m_tHandleBoard.m_tBrdVer[tVer.m_wBrdIndex].m_achBrdVer, tVer.m_achBrdVer, sizeof(m_tHandleBoard.m_tBrdVer[tVer.m_wBrdIndex].m_achBrdVer));
}
//��������
void CUmsBoardHandleService::EventBrdUpGrade(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	TTPBrdUpGrade tUpGrade;
	TP_SAFE_CAST(tUpGrade, pDataBuf + sizeof(TLogUser));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdUpGrade] UpGrade Board: Layer:%d, Slot:%d, FileName:%s.\n", 
								tUpGrade.m_byLayer, tUpGrade.m_bySlot, tUpGrade.m_szFileName));

	BOOL32 bRet = TRUE;
	s8 szFileName[TP_UPGRADE_FILENAME_LENGTH] = {0};
	u16 wBrdIndex = m_tHandleBoard.FindBrdIndex(tUpGrade.m_byLayer, tUpGrade.m_bySlot);
	do 
	{
		if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
		{
			bRet = FALSE;
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdUpGrade] UpGrade Board, BrdIndex More Than BrdMaxNum.\n"));
			break;
		}
		//������
		if (!m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_bReg)
		{
			bRet = FALSE;
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdUpGrade] UpGrade Board, BrdIndex %d not online.\n", wBrdIndex));
			break;
		}
		//��ȡ��Ӧλ�õ�������
		EMBrdType emBrdType = m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType;
		if (em_unknow_brd == emBrdType)
		{
			bRet = FALSE;
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdUpGrade] UpGrade Board, BrdType Unknown.\n"));
			break;;
		}
		//���ͺ������ļ���ƥ���ж�
		memcpy(szFileName, tUpGrade.m_szFileName, sizeof(szFileName));
		if (em_mpc_brd == emBrdType)
		{
			//���ص�������
			bRet = UpdateMpcBrd(tUpGrade);
		}
	} while (0);

	if (!bRet)
	{
		u8 abyBuf[sizeof(u8) + sizeof(u8) + sizeof(BOOL32)] = {0};
		memcpy(abyBuf, &tUpGrade.m_byLayer, sizeof(u8));
		memcpy(abyBuf + sizeof(u8), &tUpGrade.m_bySlot, sizeof(u8));
		memcpy(abyBuf + sizeof(u8) + sizeof(u8), &bRet, sizeof(BOOL32));
		TpNotifyMsgToToolUserFromService(ev_card_upgrade_res, abyBuf, sizeof(abyBuf));
	}
	else
	{
		if (em_mpc_brd != m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType)
		{
			//֪ͨeqp
			TBrdUpInfo tUpInfo;
			tUpInfo.m_byIndex = (u8)wBrdIndex;
			memcpy(tUpInfo.m_szFileName, szFileName, sizeof(tUpInfo.m_szFileName));
			UmsNotifyMsgToEqp(ev_board_upgrade_req, (void*)&tUpInfo, sizeof(TBrdUpInfo));
		}
	}
}

void CUmsBoardHandleService::EventBrdUpdateAck(u8* pDataBuf, u16 wDataSize)
{
	u16 wBrdIndex = TP_INVALID_INDEX;
	TP_SAFE_CAST(wBrdIndex, pDataBuf);
	BOOL32 bRet;
	TP_SAFE_CAST(bRet, pDataBuf + sizeof(u16));
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdUpdateAck] brdindex:%d, update result:%d.\n", wBrdIndex, bRet));

	//��ά������֪ͨ�������
	u8 byUILayer = wBrdIndex / TP_BOARD_MAX_SLOT;
	u8 byUISlot = wBrdIndex % TP_BOARD_MAX_SLOT;
	u8 abyBuf[sizeof(u8) + +sizeof(u8) + sizeof(BOOL32)];
	memcpy(abyBuf, &byUILayer, sizeof(u8));
	memcpy(abyBuf + sizeof(u8), &byUISlot, sizeof(u8));
	memcpy(abyBuf + sizeof(u8) + sizeof(u8), &bRet, sizeof(BOOL32));
	TpNotifyMsgToToolUserFromService(ev_card_upgrade_res, abyBuf, sizeof(abyBuf));
}
void CUmsBoardHandleService::EventAudiomixUsed(u8* pDataBuf, u16 wDataSize)
{
#ifdef _USE_XMPUEQP_
	EMXmpuEqpType emType;
	emType = em_XmpuMix_Eqp;
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_res_usd_info_req);
	cMsg.SetBody((void*)&emType, sizeof(EMXmpuEqpType));
	cMsg.Post(UMS_XMPU_APP_INST, 0, UMS_SERVICE_APP_INST);
#else
	EMEqpType emType;
	emType = em_audmix_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
#endif
}

void CUmsBoardHandleService::EventVmpUsed(u8* pDataBuf, u16 wDataSize)
{

#ifdef _USE_XMPUEQP_
	EMXmpuEqpType emType;
	emType = em_XmpuVmp_Eqp;
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_res_usd_info_req);
	cMsg.SetBody((void*)&emType, sizeof(EMXmpuEqpType));
	cMsg.Post(UMS_XMPU_APP_INST, 0, UMS_SERVICE_APP_INST);
#else
	EMEqpType emType;
	emType = em_vmp_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
#endif
}

void CUmsBoardHandleService::EventBasUsed(u8* pDataBuf, u16 wDataSize)
{
#ifdef _USE_XMPUEQP_
	EMXmpuEqpType emType;
	emType = em_XmpuVidBas_Eqp;
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_res_usd_info_req);
	cMsg.SetBody((void*)&emType, sizeof(EMXmpuEqpType));
	cMsg.Post(UMS_XMPU_APP_INST, 0, UMS_SERVICE_APP_INST);
#else
	EMEqpType emType;
	emType = em_bas_mdl;
	UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
#endif
}

void CUmsBoardHandleService::EventEqpUsedReq( u8* pDataBuf, u16 wDataSize )
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	EMEqpType emReqType;
	TP_SAFE_CAST(emReqType, pDataBuf + sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventEqpUsedReq] ReqType:%d.\n", emReqType));

	if (em_max_mdl == emReqType)
	{
#ifdef _USE_XMPUEQP_
		emReqType = em_dataswitch_mdl;
		UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emReqType, sizeof(emReqType));

		EMXmpuEqpType emType;
		emType = em_Xmpu_unknow;
		CTpMsg cMsg;
		cMsg.SetEvent(evXmpu_res_usd_info_req);
		cMsg.SetBody((void*)&emType, sizeof(EMXmpuEqpType));
		cMsg.Post(UMS_XMPU_APP_INST, 0, UMS_SERVICE_APP_INST);
#else
		EMEqpType emType;
		emType = em_audmix_mdl;
		UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
		emType = em_vmp_mdl;
		UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
		emType = em_bas_mdl;
		UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
		emType = em_audbas_mdl;
		UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
		emType = em_vmp_tp_mdl;
		UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emType, sizeof(EMEqpType));
#endif
	}
	else if (em_unknow_mdl == emReqType)
	{
		return;
	}
	else
	{
#ifdef _USE_XMPUEQP_
		EMXmpuEqpType emType;
		if (em_bas_mdl == emReqType)
		{
			emType = em_XmpuVidBas_Eqp;
		}
		else if (em_audbas_mdl == emReqType)
		{
			emType = em_XmpuAudBas_Eqp;
		}
		else if (em_audmix_mdl == emReqType)
		{
			emType = em_XmpuMix_Eqp;
		}
		else if (em_vmp_mdl == emReqType)
		{
			emType = em_XmpuVmp_Eqp;
		}
		else
		{
			emType = em_Xmpu_unknow;
		}

		CTpMsg cMsg;
		cMsg.SetEvent(evXmpu_res_usd_info_req);
		cMsg.SetBody((void*)&emType, sizeof(EMXmpuEqpType));
		cMsg.Post(UMS_XMPU_APP_INST, 0, UMS_SERVICE_APP_INST);
#else
		UmsNotifyMsgToEqp(ev_board_used_req, (void*)&emReqType, sizeof(EMEqpType));
#endif//_USE_XMPUEQP_
	}

	return;
}

BOOL32 CUmsBoardHandleService::IsBrdSingleMdl(EMBrdType emType)
{
	if (em_mpc_brd == emType || em_cri2_brd == emType || em_mpu2_tp_brd == emType || em_is22_brd == emType || em_apu2_tp_brd ==emType)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
EmTpBoardRet CUmsBoardHandleService::SingleBrdMdlHandler(EMBrdType emType, u16 wBrdIndex)
{
	TTPMdlCfg tMdlCfg;
	u16 wMdlIndex = TP_UMS_BRD_MAXNUM_EQP;
	u16 wIndex = 0;
	if (em_mpc_brd == emType)
	{
		tMdlCfg.m_emEqpType = em_mpc_mdl;
		wMdlIndex = m_tHandleBoard.AddBrdMode(tMdlCfg, wBrdIndex);
	}
	else if (em_apu2_tp_brd == emType)
	{
		for(wIndex = 0; wIndex < TP_MAX_AUD_MIX_NUM ; wIndex++)  
		{			
			tMdlCfg.m_emEqpType = em_audmix_mdl;
			tMdlCfg.m_wEqpId = m_tHandleBoard.MakeMdlEqpId(tMdlCfg.m_emEqpType);
			tMdlCfg.m_byAudmixNum = (u8)CUmsConfigEx::GetInstance()->GetMixNum(wIndex);
			wMdlIndex = m_tHandleBoard.AddBrdMode(tMdlCfg, wBrdIndex);
		}
		tMdlCfg.m_emEqpType = em_audbas_mdl;
		tMdlCfg.m_wEqpId = m_tHandleBoard.MakeMdlEqpId(em_audbas_mdl);
		wMdlIndex = m_tHandleBoard.AddBrdMode(tMdlCfg, wBrdIndex);
	}
	else if (em_cri2_brd == emType)
	{
		tMdlCfg.m_emEqpType = em_dataswitch_mdl;
		wMdlIndex = m_tHandleBoard.AddBrdMode(tMdlCfg, wBrdIndex);
	}
	else if (em_is22_brd == emType)
	{
		tMdlCfg.m_emEqpType = em_dataswitch_mdl;
		wMdlIndex = m_tHandleBoard.AddBrdMode(tMdlCfg, wBrdIndex);
	}
	else if (em_mpu2_tp_brd == emType)
	{
		for(wIndex = 0; wIndex < TP_MAX_MPU2TP_EQP_NUM; wIndex++)
		{
			tMdlCfg.m_emEqpType = em_vmp_tp_mdl;
			wMdlIndex = m_tHandleBoard.AddBrdMode(tMdlCfg, wBrdIndex);
		}
	}

	else
	{
		return emTP_Board_UnKonw;
	}

	if (TP_UMS_BRD_MAXNUM_EQP == wMdlIndex)
	{
		return emTP_BrdMode_MaxNum;
	}
	return emTP_Board_Mode_ModifySuccess;
}

BOOL32 CUmsBoardHandleService::NeedStateNty(u16 wBrdIndex, BOOL32 abState[])
{
	for(u8 byIndex = 0; byIndex < TP_UMS_BRD_MAXNUM_EQP; byIndex++)
	{
		if ((abState[byIndex] && !m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_abEqpReg[byIndex])
			|| (!abState[byIndex] && m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_abEqpReg[byIndex]))
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL32 CUmsBoardHandleService::IsModifiedSame(TTPMdlCfg tSrc[], TTPMdlCfg tDst[])
{
	BOOL32 bRes = TRUE;
	for (u16 wIndex = 0; wIndex < TP_UMS_BRD_MAXNUM_EQP; ++wIndex)
	{
		if (em_unknow_mdl == tSrc[wIndex].m_emEqpType &&
			em_unknow_mdl == tDst[wIndex].m_emEqpType)
		{
			break;
		}

		if (tSrc[wIndex].m_emEqpType != tDst[wIndex].m_emEqpType ||
			0 != strcmp(tSrc[wIndex].m_szEqpAlias, tDst[wIndex].m_szEqpAlias))
		{
			bRes = FALSE;
			break;
		}
	}

	return bRes;
}

void CUmsBoardHandleService::ReadMpcInfo()
{//���ظĳ�mpc �Ժ�Ҫ��ȡmpc��
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	TTPBrdInfo tUiInfo;		//��������İ�����Ϣ
	tUiInfo.m_bReg = TRUE;
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType = em_mpc_brd;
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_dwBrdIP = GetLocalIP();
	tUiInfo.m_tBrdMode[0].m_emEqpType = em_mpc_mdl;

	u8	bySavedLayer = 0;
	u8	bySavedSlot = 0;

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TBrdPosition tPos;
	if (ERROR == BrdQueryPosition(&tPos))
	{
		msgprint("[CUmsBoardHandleService::ReadMpcInfo] read mpc TBrdPosition error !\n ");
		return;
	}
	msgprint("[CUmsBoardHandleService::ReadMpcInfo] read mpc TBrdPosition right, layer:%d, slot:%d.\n", tPos.byBrdLayer, tPos.byBrdSlot);
	bySavedLayer = tPos.byBrdLayer;
	bySavedSlot = tPos.byBrdSlot;
#endif
	//BoardService������Ϣ�����б����mpc���ӵ���Ϣ
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer = bySavedLayer;
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot = bySavedSlot == 0 ? 0 : NORMAL_BRD_UI_SLOT_UPBOUNDS;

	u16 wBrdIndex = tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer * TP_BOARD_MAX_SLOT + tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot;
	m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_bReg = TRUE;
	m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_byBrdID = (u8)wBrdIndex;
	m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_byBrdLayer = bySavedLayer;
	m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_byBrdSlot = bySavedSlot;
	m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP = GetLocalIP();
	m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType = em_mpc_brd;
	m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_abEqpReg[0] = TRUE;
	memcpy(&m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdMode, &tUiInfo.m_tBrdMode, sizeof(TTPMdlCfg));

	// �������ذ�����
	m_wMpcBrdIndex = wBrdIndex;
}

//�������ذ���
BOOL32 CUmsBoardHandleService::UpdateMpcBrd(TTPBrdUpGrade tBrd)
{
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::UpdateMpcBrd] brdlayer:%d, brdslot:%d, update file name:%s.\n", 
								tBrd.m_byLayer, tBrd.m_bySlot, tBrd.m_szFileName));

	if (NULL == tBrd.m_szFileName)
	{
		msgprint("UpdateMpcBrd update file name is null\n");
		return FALSE;
	}
	if (m_bIsUpdate)
	{
		msgprint("UpdateMpcBrd board is updating...\n");
		return FALSE;
	}
	
	if (NULL == g_hNewUpdateTask)
	{
		m_bIsUpdate = TRUE;
		g_cMainBoardUpdateTask.SetUpdateName(tBrd.m_szFileName);

		g_hNewUpdateTask = OspTaskCreate(NewMainBoardUpdateTaskProc, "NewMainBoardUpdateTaskProc", 60, 512*1024, 0, 0);
		if (NULL == g_hNewUpdateTask)
		{
			msgprint("UpdateMpcBrd OspTaskCreate NewMainBoardUpdateTaskProc Error...\n");
			return FALSE;
		}
		else
		{
			msgprint("UpdateMpcBrd NewMainBoardUpdateTaskProc is running... \n");
		}
	}
	return TRUE;
}

void CUmsBoardHandleService::CountUiBrdLocation(u16 wIndex, TTPBrdInfo& tUiInfo)
{
	//�����淢�͵���ʾ�Ĳ�Ųۺ�
	u8 byUiLayer = wIndex / TP_BOARD_MAX_SLOT;
	u8 byUiSlot = wIndex % TP_BOARD_MAX_SLOT;
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdLayer = byUiLayer;
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_byBrdSlot = byUiSlot;
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_dwBrdIP = m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_dwBrdIP;
	tUiInfo.m_tBrdCfg.m_tBrdPos.m_emBrdType = m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType;
	memcpy(tUiInfo.m_tBrdMode, m_tHandleBoard.m_atBrdCfg[wIndex].m_tBrdMode, sizeof(tUiInfo.m_tBrdMode));
	tUiInfo.m_bBrdUsed = m_tHandleBoard.m_atBrdCfg[wIndex].m_bBrdUsed;
	tUiInfo.m_bReg = m_tHandleBoard.m_atBrdCfg[wIndex].m_bReg;
	memcpy(tUiInfo.m_abEqpReg, m_tHandleBoard.m_atBrdCfg[wIndex].m_abEqpReg, sizeof(tUiInfo.m_abEqpReg));
}

u8 CUmsBoardHandleService::CountBrdSavedSlot(u8 bySlot, EMBrdType emType)
{
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::CountBrdSavedSlot] type:(%d->%s), slot:%d.\n", 
								TpEnumIdString(EMBrdType, emType), bySlot));

	u8 byRetSlot = (u8)TP_INVALID_INDEX;
	if (em_mpc_brd == emType)
	{
		if (MC0_BRD_UI_SLOT == bySlot)
		{
			byRetSlot = 0;
		}
		if (MC1_BRD_UI_SLOT == bySlot)
		{
			byRetSlot = 1;
		}
	}
	else
	{//��������
		if ((bySlot > 0) && (bySlot <= NORMAL_BRD_UI_SLOT_DOWN_BOUNDS))
		{
			byRetSlot = bySlot - 1;
		}
		if ((bySlot > NORMAL_BRD_UI_SLOT_UPBOUNDS) && (bySlot < TP_BOARD_MAX_SLOT))
		{
			byRetSlot = bySlot - 2;
		}
	}
	return byRetSlot;
}


u8 CUmsBoardHandleService::CountUiSlotbySaveSlot( u8 bySlot, EMBrdType emType )
{
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::CountUiSlotbySaveSlot] type:(%d->%s), slot:%d.\n", 
								TpEnumIdString(EMBrdType, emType), bySlot));
	u8 byRetSlot = (u8)TP_INVALID_INDEX;
	if (em_mpc_brd == emType)
	{
		if (0 == bySlot)
		{
			byRetSlot = MC0_BRD_UI_SLOT;
		}
		if (1 == bySlot)
		{
			byRetSlot = MC1_BRD_UI_SLOT;
		}
	}
	else
	{//��������
		if ((bySlot > 0) && (bySlot <= 7))  // ά�����߳��˵�һ����mpc�⣬��һ����0��7���ڶ�����8��14
		{
			byRetSlot = bySlot + 1;
		}
		if ((bySlot > 7) && (bySlot <= 14))
		{
			byRetSlot = bySlot + 2;
		}
	}
	return byRetSlot;
}


void CUmsBoardHandleService::EventUpdateTaskReturn(u8* pDataBuf, u16 wDataSize)
{
	BOOL32 bSuccess;
	TP_SAFE_CAST(bSuccess, pDataBuf);

	m_bIsUpdate = FALSE;
	u16 wRet = TP_BOARD_MAX_NUM;
	for (u16 wIndex = 0; wIndex < TP_BOARD_MAX_NUM; wIndex++)
	{
		if (em_mpc_brd == m_tHandleBoard.GetBrdType(wIndex))
		{
			wRet = wIndex;
			break;
		}
	}
	if ( wRet == TP_BOARD_MAX_NUM )
	{
		return ;
	}

	u8 byUiLayer = wRet / TP_BOARD_MAX_SLOT;
	u8 byUiSlot = wRet % TP_BOARD_MAX_SLOT;

	//��ά�����߷��������������
	u8 abyBuf[sizeof(u8) + sizeof(u8) + sizeof(BOOL32)] = {0};
	memcpy(abyBuf, &byUiLayer, sizeof(u8));
	memcpy(abyBuf + sizeof(u8), &byUiSlot, sizeof(u8));
	memcpy(abyBuf + sizeof(u8) + sizeof(u8), &bSuccess, sizeof(BOOL32));
	TpNotifyMsgToToolUserFromService(ev_card_upgrade_res, abyBuf, sizeof(abyBuf));
	
	OspDelay(1000);
	if (bSuccess)
	{//����
		system("reboot");
	}
}


void CUmsBoardHandleService::EventSwitchTelnetFtp(u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, pDataBuf);
	TPBoardSwitch tBoardSwitch;
	TP_SAFE_CAST(tBoardSwitch, pDataBuf + sizeof(TLogUser));

	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventSwitchTelnetFtp] Switch:Type:%d Layer:%d, Slot:%d Switch:%d.\n", 
								tBoardSwitch.m_emType, tBoardSwitch.m_byLayer, tBoardSwitch.m_bySlot,tBoardSwitch.m_bSwitch));
#ifdef _LINUX_ 
	#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	EmBoardSwitchRes emSwitchRet = em_BoardSwitchRes_ok;
    EmBoardSwitchType emBrdSwitchType = tBoardSwitch.m_emType;
	BOOL32 bBoardSwitch = tBoardSwitch.m_bSwitch;
	u16 wBrdIndex = m_tHandleBoard.FindBrdIndex(tBoardSwitch.m_byLayer, tBoardSwitch.m_bySlot);
	EMBrdType emBrdType = em_unknow_brd;
	do 
	{
		if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
		{
			emSwitchRet = em_BoardSwitchRes_notfind;
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventSwitchTelnetFtp] Switch Board Telnet or Ftp, BrdIndex More Than BrdMaxNum.\n"));
			break;
		}
		//������
		if (!m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_bReg)
		{
			emSwitchRet = em_BoardSwitchRes_offline;
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventSwitchTelnetFtp] Switch Board Telnet or Ftp, BrdIndex %d not online.\n", wBrdIndex));
			break;
		}
		//��ȡ��Ӧλ�õ�������
        emBrdType = m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType;
		//ֻ֧��is2.2 cri2 mpc2  mpu2tp apu2tp
		if ((em_is22_brd != emBrdType) && (em_cri2_brd != emBrdType) && (em_mpc_brd != emBrdType)
			 &&(em_mpu2_tp_brd != emBrdType) && (em_apu2_tp_brd != emBrdType))
		{
			emSwitchRet = em_BoardSwitchRes_brderror;
			MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventSwitchTelnetFtp] Switch Board Telnet or Ftp, BrdType %d not support.\n",emBrdType));
			break;
		}

		//�������ͺͿ��������ж�
		if ((em_BoardSwitch_telnet != emBrdSwitchType) && (em_BoardSwitch_ftp != emBrdSwitchType))
		{
			emSwitchRet = em_BoardSwitchRes_switcherr;
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventSwitchTelnetFtp] Switch Board Telnet or Ftp, SwitchType %d not support.\n",emBrdSwitchType));
			break;
		}	     
		if (em_mpc_brd == emBrdType)
		{
		    SwitchMpcTelnetFtp(emBrdSwitchType, bBoardSwitch); //���ذ忪��Telnet Ftp
			TelnetFtpStatNty(wBrdIndex, em_BoardSwitch_all);
			return;
		}

	} while (0);

	u8 abyBuf[sizeof(TPBoardSwitch) + sizeof(EmBoardSwitchRes)] = {0};
	memcpy(abyBuf, &tBoardSwitch, sizeof(TPBoardSwitch));
	memcpy(abyBuf + sizeof(TPBoardSwitch), &emSwitchRet, sizeof(EmBoardSwitchRes));
    if (em_BoardSwitchRes_ok != emSwitchRet)
    {
	    TpNotifyMsgToToolUserFromService(ev_card_switchtelnetftp_rsp, abyBuf, sizeof(abyBuf));
		return;
    }

	//֪ͨeqp

	TBrdSwitchInfo tBrdSwithInfo;
	tBrdSwithInfo.m_wBrdIndex = wBrdIndex;
	tBrdSwithInfo.m_emType    = emBrdSwitchType; 
	tBrdSwithInfo.m_bSwitch   = bBoardSwitch;
    UmsNotifyMsgToEqp(ev_board_switchtelnetftp_req, (void*)&tBrdSwithInfo, sizeof(TBrdSwitchInfo));
#else
	s8 achCommand[MAX_COMMEND_LEN];
	s8 achSshInfo[MAX_SSH_INFO];
	u32 dwRet;
	u32 dwlubanRet;
	EmBoardSwitchRes emSwitchRet = em_BoardSwitchRes_end;
	m_bSshSwitch = tBoardSwitch.m_bSwitch;
	if (tBoardSwitch.m_bSwitch)
	{
		memcpy(achSshInfo,"start",sizeof("start"));
		sprintf(achCommand, "service sshd %s",achSshInfo);
		dwRet = system(achCommand);
		memset(achCommand,0,sizeof(achCommand));
		sprintf(achCommand, "service luban-sshd %s",achSshInfo);
		dwlubanRet = system(achCommand);
		MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventSwitchSsh] dwRet:%d  dwLubanRet:%d bOnOff:%d commond:%s\n", dwRet, dwlubanRet, m_bSshSwitch, achCommand));
	}
	else
	{
		memcpy(achSshInfo,"stop",sizeof("stop"));
		sprintf(achCommand, "service sshd %s",achSshInfo);
		dwRet = system(achCommand);
		memset(achCommand,0,sizeof(achCommand));
		sprintf(achCommand, "service luban-sshd %s",achSshInfo);
		dwlubanRet = system(achCommand);
		MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventSwitchSsh] dwRet:%d dwLubanRet:%d bOnOff:%d commond:%s\n", dwRet, dwlubanRet, m_bSshSwitch, achCommand));
	}

	TpNotifyMsgToUeFromService(ev_card_switchtelnet_ntf, &tBoardSwitch, sizeof(tBoardSwitch),tUser); 
	
	//֪ͨeqp
	TPBoardSwitch tSshSwithInfo;
	tSshSwithInfo.m_bSwitch   = m_bSshSwitch;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_media_switchtelnetftp_req);
	cMsg.SetBody(&tSshSwithInfo, sizeof(tSshSwithInfo));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_MEDIATRANS_APP_INST);

#endif
#endif
}
void CUmsBoardHandleService::EventBrdSwitchTelFtpRes(u8* pDataBuf, u16 wDataSize)
{
	TBrdSwitchInfo tBrdSwithInfo;
	TP_SAFE_CAST(tBrdSwithInfo, pDataBuf);
	EmBoardSwitchRes emSwitchRet;
	TP_SAFE_CAST(emSwitchRet, pDataBuf + sizeof(TPBoardSwitch));
	
	MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdSwitchTelFtpRes] board index:%d,switch type %d(0:tel 1:ftp),switch status %d,switch onoff res %d.\n", 
								tBrdSwithInfo.m_wBrdIndex,tBrdSwithInfo.m_emType,tBrdSwithInfo.m_bSwitch, emSwitchRet));
    TPBoardSwitch tBrdSwitch;
	u16 wBrdIndex = tBrdSwithInfo.m_wBrdIndex;
	u8 byUiLayer  = wBrdIndex / TP_BOARD_MAX_SLOT;
	u8 byUiSlot   = wBrdIndex % TP_BOARD_MAX_SLOT;
	tBrdSwitch.m_byLayer = byUiLayer;
	tBrdSwitch.m_bySlot  = byUiSlot; 
    
	EmBoardSwitchType emBrdSwitchType = tBrdSwithInfo.m_emType;
	BOOL32 bBrdSwitchStat = tBrdSwithInfo.m_bSwitch;
	tBrdSwitch.m_bSwitch = bBrdSwitchStat;

	switch(emBrdSwitchType)
	{
		case em_BoardSwitch_telnet:
		{
			tBrdSwitch.m_emType = em_BoardSwitch_telnet;
			if (emSwitchRet == em_BoardSwitchRes_ok)
			{
				m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bTelnetStatus = bBrdSwitchStat;
			}
		}
		break;
		case em_BoardSwitch_ftp:
		{
			tBrdSwitch.m_emType = em_BoardSwitch_ftp;
			if (emSwitchRet == em_BoardSwitchRes_ok)
			{
				m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bFtpStatus = bBrdSwitchStat;
			}
		}
		break;
		default:
			{
				MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::EventBrdSwitchTelFtpRes] Switch Board Telnet or Ftp, Switch Type Unknown.\n"));
				return;
			}
	}
    
	if (emSwitchRet != em_BoardSwitchRes_ok)
	{
		u8 abyBuf[sizeof(TPBoardSwitch) + sizeof(EmBoardSwitchRes)] = {0};
		memcpy(abyBuf, &tBrdSwitch, sizeof(TPBoardSwitch));
		memcpy(abyBuf + sizeof(TPBoardSwitch), &emSwitchRet, sizeof(EmBoardSwitchRes));
		TpNotifyMsgToToolUserFromService(ev_card_switchtelnetftp_rsp, abyBuf, sizeof(abyBuf));
	}

	TelnetFtpStatNty(wBrdIndex, tBrdSwitch.m_emType);

	return;
}
void CUmsBoardHandleService::TelnetFtpStatNty(u16 wBrdIndex,EmBoardSwitchType emBrdSwitchType)
{
	TPBoardSwitch tBrdSwitch;
	
	u8 byUiLayer = wBrdIndex / TP_BOARD_MAX_SLOT;
	u8 byUiSlot = wBrdIndex % TP_BOARD_MAX_SLOT;

	tBrdSwitch.m_byLayer = byUiLayer;
	tBrdSwitch.m_bySlot  = byUiSlot; 
	EMBrdType emBrdType  = em_unknow_brd;
	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::TelnetFtpstatNty] BrdIndex %d More Than BrdMaxNum.\n",
			wBrdIndex));
		return ;
	}
    //��ȡ��Ӧλ�õ�������
    emBrdType = m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_tBrdCfg.m_tBrdPos.m_emBrdType;
	//ֻ֧��is2.2 cri2 mpc2  mpu2tp apu2tp
	if ((em_is22_brd != emBrdType) && (em_cri2_brd != emBrdType) && (em_mpc_brd != emBrdType)
			&&(em_mpu2_tp_brd != emBrdType) && (em_apu2_tp_brd != emBrdType))
	{
		MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::TelnetFtpStatNty] BrdType %d not support, wBrdIndex:%d.\n",
			emBrdType, wBrdIndex));
		return;
	}
	if (!m_tHandleBoard.m_atBrdCfg[wBrdIndex].m_bReg)
	{
		MdlHint(Ums_Mdl_Service, ("[CUmsBoardHandleService::TelnetFtpStatNty] Board not online, wBrdIndex:%d.\n", 
			emBrdType, wBrdIndex));
		return;
	}

	switch(emBrdSwitchType)
	{		
		case em_BoardSwitch_telnet:
		{
			tBrdSwitch.m_emType  = em_BoardSwitch_telnet;
			tBrdSwitch.m_bSwitch = m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bTelnetStatus;
		    TpNotifyMsgToToolUserFromService(ev_card_switchtelnet_ntf, &tBrdSwitch, sizeof(tBrdSwitch));
		}
		break;
		case em_BoardSwitch_ftp:
		{

			tBrdSwitch.m_emType  = em_BoardSwitch_ftp;
			tBrdSwitch.m_bSwitch = m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bFtpStatus;
		    TpNotifyMsgToToolUserFromService(ev_card_switchftp_ntf, &tBrdSwitch, sizeof(tBrdSwitch));
		}
		break;
		case em_BoardSwitch_all:
		{
			tBrdSwitch.m_emType  = em_BoardSwitch_telnet;
			tBrdSwitch.m_bSwitch = m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bTelnetStatus;
		    TpNotifyMsgToToolUserFromService(ev_card_switchtelnet_ntf, &tBrdSwitch, sizeof(tBrdSwitch));

			tBrdSwitch.m_emType  = em_BoardSwitch_ftp;
			tBrdSwitch.m_bSwitch = m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bFtpStatus;
			TpNotifyMsgToToolUserFromService(ev_card_switchftp_ntf, &tBrdSwitch, sizeof(tBrdSwitch));
		}
		break;
		default:
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::SwitchTelnetFtp] Switch Type %d Unknown, wBrdIndex:%d.\n",
				emBrdSwitchType, wBrdIndex));
	}

}


//����Telnet��Ftp
void CUmsBoardHandleService::SwitchMpcTelnetFtp(EmBoardSwitchType emBrdSwitchType, BOOL32 bBoardSwitch)
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	u16 wBrdIndex = m_wMpcBrdIndex;
	if (wBrdIndex < 0 || wBrdIndex >= TP_BOARD_MAX_NUM)
	{
		MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::SwitchTelnetFtp] Invalid m_wMpcBrdIndex:%d.\n", m_wMpcBrdIndex));
		return;
	}
	switch(emBrdSwitchType)
	{
	    case em_BoardSwitch_telnet:
		{
            if (bBoardSwitch)
			{
	            telnetporton();
			}
            else
			{
	            telnetportoff();
			}
			m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bTelnetStatus = bBoardSwitch;
		}
		break;
	    case em_BoardSwitch_ftp:
		{
			switchftp(bBoardSwitch);
			m_tHandleBoard.m_tBrdTelFtpStat[wBrdIndex].m_bFtpStatus = bBoardSwitch;
		}
		break;
		default:
			MdlError(Ums_Mdl_Service, ("[CUmsBoardHandleService::SwitchTelnetFtp] Switch Board Telnet or Ftp, Switch Type %d Unknown.\n", emBrdSwitchType));
	}
#endif	     
}

//MPC�������̴߳�����
void* NewMainBoardUpdateTaskProc(void * pParam)
{
#ifdef _LINUX_
	msgprint(" NewMainBoardUpdateTaskProc: pid:[%d]\n", getpid());
#endif
	BOOL32 bSuccess = FALSE;
#ifdef _LINUX_
	if (Ums_Run_On_Mpc2 == CUmsConfigEx::GetInstance()->GetUmsRunType())
	{
		if ( g_cMainBoardUpdateTask.BrdFileIsUngz(g_cMainBoardUpdateTask.GetUpdateName()) )
		{
			bSuccess = g_cMainBoardUpdateTask.UpdateMpc2BoardLinuxSys_Ungz( g_cMainBoardUpdateTask.GetUpdateName() );
			msgprint("[NewMainBoardUpdateTaskProc] UpdateMpc2BoardLinuxSys_Ungz, bSuccess->%d.\n", bSuccess);
		}
		else
		{
			bSuccess = g_cMainBoardUpdateTask.UpdateMpc2BoardLinuxSys( g_cMainBoardUpdateTask.GetUpdateName() );
			msgprint("[NewMainBoardUpdateTaskProc] UpdateMpc2BoardLinuxSys, bSuccess->%d.\n", bSuccess);
		}
	}
#endif

	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPUpdate_Task_Return);
	cMsg.SetBody(&bSuccess, sizeof(BOOL32));
	cMsg.Post(UMS_SERVICE_APP_INST, 0);
	
	g_hNewUpdateTask = NULL;
	g_cMainBoardUpdateTask.Clear();
	return 0;
}

CUmsMainBoardUpdateTask::CUmsMainBoardUpdateTask()
{
	Clear();
}

CUmsMainBoardUpdateTask::~CUmsMainBoardUpdateTask()
{

}

BOOL32 CUmsMainBoardUpdateTask::BrdFileIsUngz(s8 * const sFileName)
{
	s8 *pLoc = NULL;	
	pLoc = strstr( sFileName, ".gz");
	BOOL bRet = TRUE;
	if ( pLoc )
	{
		bRet = FALSE;
	}
	msgprint("[CUmsMainBoardUpdateTask::BrdFileIsUngz], bRet->%d, FileName:%s \n", bRet, sFileName );
	return bRet;	
}

BOOL32 CUmsMainBoardUpdateTask::UpdateMpc2BoardLinuxSys(s8 * const szFileName)
{	
	BOOL32 bRet = FALSE;
	s8 achFlashFileNameUngz[256] = {0};
	s8* pszFileName = NULL;
	s8 achRandom[256] = {0};
	
	strncpy(achFlashFileNameUngz, szFileName, sizeof(achFlashFileNameUngz));

	//ȥ��.gz
	s8* pszLoc = NULL;
	pszLoc = strstr(achFlashFileNameUngz, ".gz");
	if (pszLoc)
	{
		pszLoc[0] = '\0';
		pszLoc[1] = '\0';
		pszLoc[2] = '\0';
	}
	msgprint("[UpdateMpc2BoardLinuxSys] achFlashFileNameUngz->%s .\n", achFlashFileNameUngz);
	
	s8 achCommandBuf[256] = {0};
	memcpy(achCommandBuf, "gzip -d ", sizeof("gzip -d "));
	strcat(achCommandBuf, "/ramdisk/");
	strcat(achCommandBuf, szFileName); //��ѹ���ļ���ѹ
	msgprint("[UpdateMpc2BoardLinuxSys] achCommandBuf->%s .\n", achCommandBuf);
	
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	msgprint("[UpdateMpc2BoardLinuxSys] execute command ->%s .\n", achCommandBuf);
	system(achCommandBuf);
#endif
	
	pszFileName = achFlashFileNameUngz;
	msgprint("[UpdateMpc2BoardLinuxSys] pszFileName->%s .\n", pszFileName);
	
	s8 achPathName[256] = {0};
	memcpy(achPathName, "/ramdisk/", sizeof("/ramdisk/"));
	strcat(achPathName, pszFileName);
	msgprint("[UpdateMpc2BoardLinuxSys] update absolute path:%s.\n", achPathName);

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	//������У��
	if (ERROR == BrdCheckUpdatePackage(achPathName))
	{
		msgprint("UpdateMpc2BoardLinuxSys check gz package->%s error\n", achPathName);
		RemoveFile(achPathName);
		return FALSE;	
	}
	//ȡ������Ϣ���Ƚ�
	if (ERROR == BrdGetUpdateInfo(achPathName, achRandom))
	{
		msgprint("UpdateMpc2BoardLinuxSys get gz package->%s random info error\n", achPathName);
		RemoveFile(achPathName);
		return FALSE;
	}
#endif
	//��ʼ����
	bRet = Mpc2SysUpGrade(achPathName);	
	//ɾ��flash���ļ�
	RemoveFile(achPathName);
	return bRet;
}

BOOL32 CUmsMainBoardUpdateTask::UpdateMpc2BoardLinuxSys_Ungz(s8 * const szFileName)
{
	BOOL32 bRet = FALSE;
	s8 achRandom[256] = {0};
	s8 achPathName[256] = {0};   //�����ļ�����·��
	msgprint("[UpdateMpc2BoardLinuxSys_Ungz] szFileName->%s.\n", szFileName);
	
	memcpy(achPathName, "/ramdisk/", sizeof("/ramdisk/"));
	strcat(achPathName, szFileName);

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	//������У��
	if (ERROR == BrdCheckUpdatePackage(achPathName))
	{
		msgprint("UpdateMpc2BoardLinuxSys_Ungz check bin package->%s error\n", achPathName);
		RemoveFile(achPathName);
		return FALSE;	
	}
	//ȡ������Ϣ���Ƚ�
	if (ERROR == BrdGetUpdateInfo(achPathName, achRandom))
	{
		msgprint("UpdateMpc2BoardLinuxSys_Ungz get bin package->%s random info error\n", achPathName);
		RemoveFile(achPathName);
		return FALSE;
	}
	//��ʼ����
	bRet = Mpc2SysUpGrade(achPathName);	
	//ɾ��flash�ļ�
	RemoveFile(achPathName);
#endif
	
	return bRet;
}

BOOL32 CUmsMainBoardUpdateTask::Mpc2SysUpGrade(s8* pszFileName)
{
	s8 byRet = 0;
	BOOL32 bResult = FALSE;
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	byRet = BrdAllSysUpdate(pszFileName, 1);
	msgprint("Mpc2SysUpGrade update path:%s, byRet:%d.\n", pszFileName, byRet);
	switch(byRet)
	{
	case UPDATE_SUCCESS:
		MdlHint(Ums_Mdl_Board, ("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], UPDATE_SUCCESS update ok !\n"));
		bResult = TRUE;
		break;
		
	case UPDATE_APP_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], UPDATE_APP_ERROR app update error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_0S_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], UPDATE_0S_ERROR os update error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_BOOT_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], UPDATE_BOOT_ERROR boot update error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_SET_FLAG_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], UPDATE_SET_FLAG_ERROR set update flag error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], UPDATE_ERROR update error !\n"));
		bResult = FALSE;
		break;	
	default:
		MdlHint(Ums_Mdl_Board, ("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], default error !\n"));
		bResult = FALSE;
		break;
	}
#endif
	msgprint("[CUmsMainBoardUpdateTask::Mpc2SysUpGrade], pszFileName->%s, bResult->%d \n", pszFileName, bResult);
	return bResult;
}

BOOL32 CUmsMainBoardUpdateTask::RemoveFile(const s8* pszFileName)
{
#ifdef _VXWORKS_
	rm(pszFileName);
#endif
#ifdef _LINUX_
	remove(pszFileName);
#endif
#ifdef WIN32
	DeleteFile(pszFileName);
#endif
	return TRUE;
}

void CUmsMainBoardUpdateTask::SetUpdateName(s8* pszName)
{
	if (NULL == pszName)
	{
		msgprint("CUmsMainBoardUpdateTask::SetUpdateName set error, pszName is null.\n");
		return;
	}
	memcpy(m_achFileName, pszName, sizeof(m_achFileName));
}



