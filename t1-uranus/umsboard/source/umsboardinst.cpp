#include "umsobject.h"
#include "eventtpsys.h"
#include "eventoutumseqp.h"
#include "umsboardcfg.h"
#include "umsboardinst.h"
#include "umsapi.h"
#include "eventoutumscommonbrd.h"
#include "innereventumsboard.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
#include "nipwrapper.h"
#endif

#define Ver_Mpc2	"Mpc2"
#define Ver_Is22	"Is22"
#define Ver_Cri2	"Cri2"
#define Ver_Mpu2Tp	"Mpu2-TP"
#define ver_Unkown  "Unkown"

CTpUmsBoardApp	g_cTpUmsBoardApp;
CTaskUpdate		g_cTaskUpdate;
StartCallBack	g_CallBack;
StartCallBack   g_ReCallBack;
TASKHANDLE		g_hUpdateTask; //文件升级线程句柄
extern TBrdCfgBase g_tBrdCfg;  //单板基本配置信息
BOOL32 g_bInit = FALSE;
void* NewUpdateTaskProc(void * pParam);//线程函数

API void showbrdcfg();
API void StartNtpd();

//telnet iptables port on/off
API void telnetporton();
API void telnetportoff();

//ftp
API void switchftp(u8 byFtpOn);
API BOOL32 checkftp();

API void showftptel();

BOOL StartBoardServer(EMBrdType emBrdType, StartCallBack callBack, StartCallBack ReCallBack)
{
#ifdef _LINUX_
	OspRegCommand("showbrdcfg", (void*)showbrdcfg, "showbrdcfg()");
	OspRegCommand("StartNtpd", (void*)StartNtpd, "StartNtpd");

	// telnet iptables rule
	OspRegCommand("telnetporton", (void*)telnetporton, "telnetporton()");
	OspRegCommand("telnetportoff", (void*)telnetportoff, "telnetportoff()");
	
	//ftp
    OspRegCommand("switchftp",   (void*)switchftp,   "switchftp()");
	OspRegCommand("checkftp",    (void*)checkftp,    "checkftp()");
	OspRegCommand("showftptel",    (void*)showftptel,    "showftptel()");

#endif

	g_CallBack = callBack;  //保存回调函数指针

    if (NULL != ReCallBack)
	{
	    g_ReCallBack = ReCallBack;
	}
	else
	{
		g_ReCallBack = callBack;
	}
	g_cTpUmsBoardApp.CreateApp("BoardApp", AID_UMSBOARD_APP, 100);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( UMS_BOARD_APP_INST );

	return TRUE;
}

void StopBoardServer()
{
	msgprint("[StopBoardServer]\n");

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( UMS_BOARD_APP_INST );

	return;
}

u8 GetBrdLayer()
{
	return g_tBrdCfg.m_tBrdPos.m_byBrdLayer;
}

u8 GetBrdSlot()
{
	return g_tBrdCfg.m_tBrdPos.m_byBrdSlot;
}

CTpBoardServer::CTpBoardServer()
{
	m_bIsUpdate = FALSE;
}
CTpBoardServer::~CTpBoardServer()
{
	
}

BOOL32 CTpBoardServer::ConnectToUms()
{
	msgprint(" [CTpBoardServer::ConnectToUms]:brdtype:(%d->%s), layer:%d, slot:%d, IP:"TPIPFORMAT".\n", TpEnumIdString(EMBrdType, m_tBrdCfg.m_tBrdPos.m_emBrdType)
			, m_tBrdCfg.m_tBrdPos.m_byBrdLayer, m_tBrdCfg.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(m_tBrdCfg.m_tBrdPos.m_dwBrdIP));

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)
	msgprint("brdid:%d.\n", BrdGetBoardID());
#endif

	if (INVALID_NODE != GetNode())
	{
		return TRUE;
	}
	
	m_tBrdCfg.m_dwUmsNode = ::OspConnectTcpNode(m_tBrdCfg.m_dwUmsListenIp, m_tBrdCfg.m_wUmsListenPort);
	if (INVALID_NODE == GetNode())
	{
		return FALSE;
	}
	else
	{
		::OspNodeDiscCBRegQ(GetNode(), GetAppID(), GetInsID());
		
		//单板注册
		TTPBrdRegInfo tBrdReg;
		u8	byNetIndx = 0;
		EMOsType emOsType = em_Win32_OsType;
		tBrdReg.m_tBrdPos = m_tBrdCfg.m_tBrdPos;
		tBrdReg.m_byNetIndx = byNetIndx;
		tBrdReg.m_emOsType = emOsType;
		
		CTpMsg cMsg;
		cMsg.SetEvent(ev_TPBrdReg_Req);
		cMsg.SetBody(&tBrdReg, sizeof(tBrdReg));
		cMsg.Post(UMS_EQP_APP_INST, m_tBrdCfg.m_dwUmsNode, UMS_BOARD_APP_INST);

		return TRUE;
	}
}

BOOL32 CTpBoardServer::ObjectInit(u32 wParam, u32 lParam)
{
	msgprint("CTpBoardServer::ObjectInit\n");
	SetLogTitle("CTpBoardServer");
	
	m_bInit = TRUE;
	m_tBrdCfg.m_dwUmsNode = INVALID_NODE;
	
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	s8 byRet = BrdSetSysRunSuccess();
	BOOL32 bRet = FALSE;
	if ( OK == SysOpenWdGuard(UMS_OpenWdGuard_Param) )
	{
		bRet = TRUE;
		m_dwWdGuardTime = UMS_WdGuardNotice_TIME * 1000 / 2;
		if( m_dwWdGuardTime > 0 )
		{
			SetTimer( EVTP_TIMER_WatchdogNotify, m_dwWdGuardTime );
		}
	}
	else
	{
		m_dwWdGuardTime = 0;
	}	
	msgprint("[SysOpenWdGuard],bRet: %d,  dwNoticeTimeout: %d \n", bRet, UMS_WdGuardNotice_TIME );
#endif

	ReadBrdCfgBaseInfo();
	Init();

	if (!ConnectToUms())
	{
		SetTimer(ev_TPBrdConnect_Timer, TP_INTERVAL_TIME_FIVE_SECOND);
	}

	return TRUE;
}

void CTpBoardServer::ObjectExit()
{
	m_bInit = FALSE;
	if (INVALID_NODE != m_tBrdCfg.m_dwUmsNode)
	{
		OspDisconnectTcpNode(m_tBrdCfg.m_dwUmsNode);
	}
	CUmsObject::ObjectExit();
	return;
}

enum tp_ums_board_dump
{
	dump_show_board
};

API void showbrdcfg()
{
	OspInstDump(AID_UMSBOARD_APP, 1, dump_show_board);
}

void CTpBoardServer::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_board:
		ShowBrdCfg();
		break;
	default:
		break;
	}
	return;
}
void CTpBoardServer::ShowBrdCfg()
{
	msgprint("*****Board Info*****.\n");
	msgprint("Board Layer:%d.\n", m_tBrdCfg.m_tBrdPos.m_byBrdLayer);
	msgprint("Board Slot:%d.\n", m_tBrdCfg.m_tBrdPos.m_byBrdSlot);
	msgprint("Board Type:(%d->%s).\n", TpEnumIdString(EMBrdType, GetBrdType()));
	msgprint("Board Ip:"TPIPFORMAT".\n", Tpu32ToIP(m_tBrdCfg.m_tBrdPos.m_dwBrdIP));
	msgprint("*****End*****.\n");
	showftptel();
}
void CTpBoardServer::MessageProc(CTpMsg *const ptMsg)
{

	u32 dwSrcID = ptMsg->GetSrcIId();
	u16 wSrcAppID = GETAPP(dwSrcID);
	u16 wEvent = ptMsg->GetEvent();

	switch( wEvent )
	{
	case  ev_TPBrdConnect_Timer:
		{
		 	if (ConnectToUms())
			{
				KillTimer(ev_TPBrdConnect_Timer);
			}
			else
			{
				SetTimer(ev_TPBrdConnect_Timer, TP_INTERVAL_TIME_FIVE_SECOND);
			}
		}
		break;
	case EVTP_TIMER_WatchdogNotify:
		{
			KillTimer( EVTP_TIMER_WatchdogNotify );				
			SetTimer( EVTP_TIMER_WatchdogNotify, m_dwWdGuardTime );
			#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
				SysNoticeWdGuard();
			#endif
		}
        break;

	case ev_TPBrdReg_Ack:
		{
			OnBrdRegSuccess(ptMsg);
		}
		break;
	case  ev_TPBrdReg_NAck:
		{
			OnBrdRegNack(ptMsg);
		}
		break;
	case ev_TPMcuBrdGetCfg_Ack:
		{
			//	g_atCallFun[0];//启动相应板子业务的startapp
			OnBrdGetCfgAck(ptMsg);
		}
		break;
	case ev_TPBrdGetCfg_NAck:
		{
			OnBrdGetCfgNack(ptMsg);
		}
		break;
	case ev_TPBrdHDVersion_Req:
		{
			//获取版本号
			OnBrdGetVer(ptMsg);
		}
		break;
	case ev_TPBrdReboot_Cmd:
		{
			//重启
			OnBrdRebootCmd(ptMsg);
		}
		break;
	case ev_TPBrdSetSysTime_Cmd:
		{
			OnBrdSetSysTime(ptMsg);
		}
		break;
	case ev_TPBrdSoftWareUpdate_Req:
		{
			//升级
			OnBrdUpdate(ptMsg);
		}
		break;
	case ev_TPUpdate_Task_Return:
		{
			OnTaskReturn(ptMsg);
		}
		break;
	case ev_TPBrdSwitchTeltp_Req:
		{
			OnBrdSwitch(ptMsg);
		}
		break;

	case OSP_DISCONNECT:
		{
			OnDisConnect(ptMsg);
		}
		break;

	}
}
void CTpBoardServer::Init()
{
	TBrdCfgBase tCfg = GetBrdCfgBase();
	m_tBrdCfg.m_dwUmsListenIp = tCfg.m_dwUmsListenIp;
	m_tBrdCfg.m_wUmsListenPort = UMS_LISTIONPORT_CMS;
	m_tBrdCfg.m_tBrdPos.m_dwBrdIP = tCfg.m_tBrdPos.m_dwBrdIP;
	m_tBrdCfg.m_tBrdPos.m_byBrdLayer = tCfg.m_tBrdPos.m_byBrdLayer;
	m_tBrdCfg.m_tBrdPos.m_byBrdSlot = tCfg.m_tBrdPos.m_byBrdSlot;
	m_tBrdCfg.m_tBrdPos.m_emBrdType = tCfg.m_tBrdPos.m_emBrdType;
}

void CTpBoardServer::OnDisConnect(CTpMsg *const ptMsg)
{
	msgprint("CTpBoardServer::OnDisConnect\n");
	
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	//点灭CRI2板业务功能灯
	msgprint("CTpBoardServer::OnDisConnect Set FUN Lead State:%d.\n", BRD_LED_ON);
	if (m_tBrdCfg.GetBrdType() == em_cri2_brd)
	{
		//点灭MLINK灯
		//BrdLedStatusSet(LED_FUN_ID2, BRD_LED_OFF);
		if (em_dataswitch_mdl == m_emEqpMdl)
		{
			BrdLedStatusSet(LED_FUN_ID2, BRD_LED_OFF);
		}
		if (em_regserver_mdl == m_emEqpMdl)
		{
			BrdLedStatusSet(LED_FUN_ID6, BRD_LED_OFF);
		}
	}
	
#endif

	// 板卡断链，恢复ftp和telnetport状态

	telnetporton();
	switchftp(1);

	
	//通知业务的业务的断链处理
	m_tBrdCfg.Disconnect();
	
	SetTimer(ev_TPBrdConnect_Timer, TP_INTERVAL_TIME_FIVE_SECOND);
}

void CTpBoardServer::OnBrdRegSuccess(CTpMsg *const ptMsg)
{
	//发送获取配置请求
	msgprint("CTpBoardServer::OnBrdRegSuccess Board Reg Success.brdType:(%d->%s), layer:%d, slot:%d, IP:"TPIPFORMAT".\n", 
		TpEnumIdString(EMBrdType, m_tBrdCfg.m_tBrdPos.m_emBrdType), m_tBrdCfg.m_tBrdPos.m_byBrdLayer,
		m_tBrdCfg.m_tBrdPos.m_byBrdSlot, Tpu32ToIP(m_tBrdCfg.m_tBrdPos.m_dwBrdIP));
	
	CTpMsg cMsg;
	cMsg.SetEvent( ev_TPBrdGetCfg_Req );
	cMsg.SetBody(&m_tBrdCfg.m_tBrdPos, sizeof(m_tBrdCfg.m_tBrdPos));
	cMsg.Post(UMS_EQP_APP_INST, m_tBrdCfg.m_dwUmsNode, UMS_BOARD_APP_INST);
}

void CTpBoardServer::OnBrdRegNack(CTpMsg *const ptMsg)
{
	msgprint("[CTpBoardServer::OnBrdRegNack]Board Reg Failure, try to reg again...\n");

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)
	u8 byLocal = BrdMPCQueryLocalMSState();
	MdlHint(Ums_Mdl_Board, ("[OnBrdRegNack] BrdMPCQueryLocalMSState:%d.\n", byLocal));
	if (byLocal == BRD_MPC_RUN_MASTER)
	{//当前状态为主板	
		if (OK == BrdMPCSetLocalMSState(BRD_MPC_RUN_SLAVE))
		{
			MdlHint(Ums_Mdl_Board, ("[OnBrdRegNack] BrdMPCSetLocalMSState BRD_MPC_RUN_SLAVE Success.\n"));
		}
		else
		{
			//设置为备板失败
			MdlHint(Ums_Mdl_Board, ("[OnBrdRegNack] BrdMPCSetLocalMSState BRD_MPC_RUN_SLAVE error.\n"));
		}
	}
#endif
	OspDisconnectTcpNode(m_tBrdCfg.m_dwUmsNode);
	m_tBrdCfg.m_dwUmsNode = INVALID_NODE;
}

void CTpBoardServer::OnBrdGetCfgAck(CTpMsg *const ptMsg)
{
	EMBrdType emBrdType;
	TP_SAFE_CAST(emBrdType, ptMsg->GetBody());
	EMEqpType emEqp;
	TP_SAFE_CAST(emEqp, ptMsg->GetBody() + sizeof(EMBrdType));

	msgprint("[CTpBoardServer::OnBrdGetCfgAck] Board(%d->%s) get cfg success MdlType:(%d->%s).\n"
							, TpEnumIdString(EMBrdType, emBrdType), TpEnumIdString(EMEqpType, emEqp));
	m_emEqpMdl = emEqp;
//点CRI2业务功能灯	
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)
	MdlHint(Ums_Mdl_Mpc, ("CTpBoardServer::OnBrdGetCfgAck Set CRI2 Fun Lead State:%d.\n", BRD_LED_ON));
	if (em_cri2_brd == emBrdType && em_dataswitch_mdl == emEqp)
	{
		BrdLedStatusSet(LED_FUN_ID2, BRD_LED_ON);
	}
	if (em_cri2_brd == emBrdType && em_regserver_mdl == emEqp)
	{
		BrdLedStatusSet(LED_FUN_ID6, BRD_LED_ON);
	}

	if (em_is22_brd == emBrdType || (em_cri2_brd == emBrdType && em_dataswitch_mdl == emEqp))
	{
		CTpTypeAdpt::StartNtpd(g_tBrdCfg.m_dwUmsListenIp);
	}
#endif
	if (!g_bInit)
	{
		g_CallBack(m_tBrdCfg.m_dwUmsNode); //启动业务
		g_bInit = TRUE;
	}
	else
	{
		g_ReCallBack(m_tBrdCfg.m_dwUmsNode);
// 	
	}
	

	return;
}

void CTpBoardServer::OnBrdGetCfgNack(CTpMsg *const ptMsg)
{
	msgprint("[CTpBoardServer::OnBrdGetCfgNack] board get cfg failure.\n");
	
	//获取配置失败，重新请求...
	KillTimer( ev_TPBrdReg_Ack );
	SetTimer(ev_TPBrdReg_Ack, TP_INTERVAL_TIME_FIVE_SECOND);
}

void CTpBoardServer::OnBrdRebootCmd(CTpMsg *const ptMsg)
{
	EMBrdType emBrd = GetBrdType();
	msgprint("[CTpBoardServer::OnBrdRebootCmd] board reboot. BrdType:%d\n", emBrd);
	system("reboot");
}

void CTpBoardServer::OnBrdSetSysTime(CTpMsg *const ptMsg)
{
	TTPTime tTime;
	TP_SAFE_CAST(tTime, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Board, ("[CTpBoardServer::OnBrdSetSysTime] SysTime: %4.4u-%2.2u-%2.2u %2.2u:%2.2u:%2.2u.\n", 
			tTime.m_wYear, tTime.m_byMonth, tTime.m_byMDay, tTime.m_byHour, tTime.m_byMinute, tTime.m_bySecond));

	TPSetSysTime(tTime);

	return ;
}

void CTpBoardServer::OnBrdGetVer(CTpMsg *const ptMsg)
{
	MdlHint(Ums_Mdl_Board, ("CTpBoardServer::OnBrdGetHardVer .\n"));

	s8* pbyHardVer = NULL;
	s8* pbySoftVer = NULL;
	u16 wBrdIndex = CountArrayIndex(m_tBrdCfg.m_tBrdPos);
	if (wBrdIndex < 0 || wBrdIndex >=TP_BOARD_MAX_NUM)
	{
		return;
	}
	
	pbyHardVer = BoardGetHardwareVer();
	pbySoftVer = BoardGetSoftwareVer();

	TBrdVersion tHardVer;
	tHardVer.m_wBrdIndex = wBrdIndex;
	memcpy(tHardVer.m_achBrdVer, pbyHardVer, sizeof(tHardVer.m_achBrdVer));
	memcpy(tHardVer.m_achSoftVer, pbySoftVer, sizeof(tHardVer.m_achSoftVer));

	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBrdHDVersion_Ack);
	cMsg.SetBody(&tHardVer, sizeof(TBrdVersion));
	cMsg.Post(UMS_EQP_APP_INST, m_tBrdCfg.m_dwUmsNode, UMS_BOARD_APP_INST);
}

s8* CTpBoardServer::BoardGetHardwareVer()
{
	static s8 achHardware[TP_BOARD_VERSION_LEN] = {0};
#if defined(_VXWORKS_) || defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)
	if (em_mpc_brd == GetBrdType())
	{
		sprintf(achHardware,"%s-%d", Ver_Mpc2, BrdQueryHWVersion());
	}
	else if (em_is22_brd == GetBrdType())
	{
		sprintf(achHardware,"%s-%d", Ver_Is22, BrdQueryHWVersion());
	}
	else if( em_cri2_brd == GetBrdType() )
	{
		sprintf(achHardware,"%s-%d", Ver_Cri2, BrdQueryHWVersion());
	}
	else if (em_mpu2_tp_brd == GetBrdType())
	{
		sprintf(achHardware,"%s-%d", Ver_Mpu2Tp, BrdQueryHWVersion());
	}
	else
	{
		sprintf(achHardware,"%s-%d", ver_Unkown, BrdQueryHWVersion());
	}
	
#else
	sprintf(achHardware,"%d",8);
#endif
	return achHardware;
}

s8* CTpBoardServer::BoardGetSoftwareVer()
{
	static s8 achOsVer[TP_BOARD_VERSION_LEN] = {0};
#if defined(_VXWORKS_) || defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)
	UINT32 dwLen = 0;
	BrdQueryOsVer(achOsVer,sizeof(achOsVer)-1,&dwLen);
#else
	if (em_mpc_brd == GetBrdType())
	{
		sprintf(achOsVer,"%s","MPC2OS");
	}
	else if (em_is22_brd == GetBrdType())
	{
		sprintf(achOsVer,"%s","EAPU2OS");
	}
	else if(em_cri2_brd == GetBrdType())
	{
		sprintf(achOsVer,"%s","CRI2OS");
	}
	else if(em_mpu2_tp_brd == GetBrdType())
	{
		sprintf(achOsVer,"%s","MPU2-TPOS");
	}
	else
	{
		sprintf(achOsVer,"%s","UnkownOS");
	}
#endif
	return achOsVer;
}

void CTpBoardServer::OnBrdUpdate(CTpMsg *const ptMsg)
{
	TBrdUpInfo tUpDate;
	TP_SAFE_CAST(tUpDate, ptMsg->GetBody());
	msgprint("[CTpBoardServer::OnBrdUpdate] BrdIndex:%d, FileNum:%d, FileName:%s, FileLen:%d.\n", 
							tUpDate.m_byIndex, tUpDate.m_byNum, tUpDate.m_szFileName, tUpDate.m_byNameLen);

	if (m_bIsUpdate)
	{
		msgprint("OnBrdUpdate board is updating...\n");
		return;
	}

	if (NULL == g_hUpdateTask)
	{
		m_bIsUpdate = TRUE;
		g_cTaskUpdate.SetBrdType(GetBrdType());
		g_cTaskUpdate.SetUpdateName(tUpDate.m_szFileName);

		g_hUpdateTask = OspTaskCreate(NewUpdateTaskProc, "tNewUpdateTask", 60, 512*1024, 0, 0);
		if (NULL == g_hUpdateTask)
		{
			msgprint("OnBrdUpdate OspTaskCreate tNewUpdateTask Error...\n");
		}
	}
	else
	{
		msgprint("OnBrdUpdate tNewUpdateTask is running... \n");
	}
}

u16 CTpBoardServer::CountArrayIndex(TTPBrdPos tPos)
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
			MdlError(Ums_Mdl_Eqp, ("[CTpBoardServer::CountArrayIndex] em_mpc_brd tPos.m_byBrdSlot invalid"));
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
			MdlError(Ums_Mdl_Eqp, ("[CTpBoardServer::CountArrayIndex] ordinary brd tPos.m_byBrdSlot invalid"));
		}
	}
	return wRetIndex;
}

void CTpBoardServer::OnTaskReturn(CTpMsg *const ptMsg)
{
	BOOL32 bRet;
	TP_SAFE_CAST(bRet, ptMsg->GetBody());
	msgprint("OnTaskReturn bRet->%d.\n", bRet);
	
	m_bIsUpdate = FALSE;
	
	//返回升级结果
	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBrdSoftWareUpdate_Ack);
	cMsg.SetBody(&bRet, sizeof(BOOL32));
	cMsg.Post(UMS_EQP_APP_INST, GetNode(), UMS_BOARD_APP_INST);
	
	OspDelay(1000);
	if (bRet)
	{//重启
		cMsg.SetEvent(ev_TPBrdReboot_Cmd);
		cMsg.SetBody(NULL, 0);
		cMsg.Post(UMS_BOARD_APP_INST, 0);
	}
}

//telnet ftp
void CTpBoardServer::OnBrdSwitch(CTpMsg *const ptMsg)
{
	TBrdSwitchInfo tBrdSwitchInfo;
	TP_SAFE_CAST(tBrdSwitchInfo, ptMsg->GetBody());
	msgprint("[CTpBoardServer::OnBrdSwitch] BrdIndex:%d, SwitchType:%d, Switch:%d.\n", 
							tBrdSwitchInfo.m_wBrdIndex, tBrdSwitchInfo.m_emType, tBrdSwitchInfo.m_bSwitch);
	EmBoardSwitchType emBrdSwitchType = tBrdSwitchInfo.m_emType;
	BOOL32 bBrdSwitch = tBrdSwitchInfo.m_bSwitch;

    SwitchTelnetFtp(emBrdSwitchType, bBrdSwitch);

    CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBrdSwitchTeltp_Ack);
	cMsg.SetBody(&tBrdSwitchInfo,sizeof(TBrdSwitchInfo));
	cMsg.Post(UMS_EQP_APP_INST, GetNode(), UMS_BOARD_APP_INST);

}

void CTpBoardServer::SwitchTelnetFtp(EmBoardSwitchType emBrdSwitchType,BOOL32 bBrdSwitch)
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	switch(emBrdSwitchType)
	{
		case em_BoardSwitch_telnet:
		{
            if (bBrdSwitch)
			{
				telnetporton();
			}
            else
			{
				telnetportoff();
			}
		}
		break;
		case em_BoardSwitch_ftp:
		{
			switchftp(bBrdSwitch);
		}
		break;
	default:
			MdlError(Ums_Mdl_Board, ("[CTpBoardServer::SwitchTelnetFtp] Switch Board Telnet or Ftp, Switch Type %d Unknown.\n", emBrdSwitchType));
	}
#endif
}


void* NewUpdateTaskProc(void * pParam)
{
#ifdef _LINUX_
	msgprint(" NewUpdateTaskProc: pid:[%d]\n", getpid());
#endif

	BOOL32 bSuccess = FALSE;
#ifdef _LINUX_
	if (g_cTaskUpdate.BrdFileIsUngz(g_cTaskUpdate.GetUpdateName()))
	{
		bSuccess = g_cTaskUpdate.UpdateDavinciLinuxSys_Ungz( g_cTaskUpdate.GetUpdateName());
		msgprint("NewUpdateTaskProc UpdateDavinciLinuxSys_Ungz, bSuccess->%d.\n", bSuccess);
	}
	else
	{
		bSuccess = g_cTaskUpdate.UpdateDavinciLinuxSys( g_cTaskUpdate.GetUpdateName());
		msgprint("NewUpdateTaskProc UpdateDavinciLinuxSys, bSuccess->%d.\n", bSuccess);
	}
#endif

	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPUpdate_Task_Return);
	cMsg.CatBody(&bSuccess, sizeof(BOOL32));
	cMsg.Post(UMS_BOARD_APP_INST, 0);

	g_hUpdateTask = NULL;
	g_cTaskUpdate.Clear();
	return 0;
}


CTaskUpdate::CTaskUpdate()
{
	memset(m_achFileName, 0, sizeof(m_achFileName));
	m_emBrdType = em_unknow_brd;
}

CTaskUpdate::~CTaskUpdate()
{
	Clear();
}

BOOL32 CTaskUpdate::BrdFileIsUngz(s8 * const sFileName)
{
	s8 *pLoc = NULL;	
	pLoc = strstr( sFileName, ".gz");
	
	BOOL bRet = TRUE;
	if ( pLoc )
	{
		bRet = FALSE;
	}
	
	msgprint("[CTaskUpdate::BrdFileIsUngz], bRet->%d \n", bRet );
	return bRet;
}

//gz包升级
BOOL32 CTaskUpdate::UpdateDavinciLinuxSys(s8 * const szFileName)
{
	MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::UpdateDavinciLinuxSys] update gz package.\n"));
	
	BOOL32 bCheck = FALSE;
	BOOL32 bRet = FALSE;
	s8 achFlashFileNameUngz[256] = {0};
	s8* pszFileName = NULL;
	//保存冗余信息
	s8* pszRandomInfo = NULL;
	
	memcpy(achFlashFileNameUngz, szFileName, sizeof(achFlashFileNameUngz));
	//去除.gz
	s8* pszLoc = NULL;
	pszLoc = strstr(achFlashFileNameUngz, ".gz");
	if (pszLoc)
	{
		pszLoc[0] = '\0';
		pszLoc[1] = '\0';
		pszLoc[2] = '\0';
	}
	msgprint("[UpdateDavinciLinuxSys] szFileName->%s, achFlashFileNameUngz->%s.\n", szFileName, achFlashFileNameUngz);
	
	s8 achCommandBuf[256] = {0};
	memcpy(achCommandBuf, "gzip -d ", sizeof("gzip -d "));
	strcat(achCommandBuf, "/ramdisk/");
	strcat(achCommandBuf, szFileName); //将压缩文件解压
	msgprint("[UpdateDavinciLinuxSys] achCommandBuf->%s .\n", achCommandBuf);
	
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	msgprint("[UpdateDavinciLinuxSys] execute command ->%s .\n", achCommandBuf);
	system(achCommandBuf);
#endif
	
	pszFileName = achFlashFileNameUngz;
	msgprint("[UpdateDavinciLinuxSys] pszFileName->%s .\n", pszFileName);
	
	s8 achPathName[256] = {0};
	memcpy(achPathName, "/ramdisk/", sizeof("/ramdisk/"));
	strcat(achPathName, pszFileName);
	msgprint("[UpdateDavinciLinuxSys] update absolute path:%s.\n", achPathName);
	
	//升级包检查
	bCheck = CheckBrdUpdatePackage(achPathName);
	if (!bCheck)
	{
		BoardRemoveFile(achPathName);
		return FALSE;
	}

	//开始升级
	bRet = BoardSysUpGrade(achPathName);	
	//删除flash上文件
	BoardRemoveFile(achPathName);
	return bRet;
}

//bin包升级
BOOL32 CTaskUpdate::UpdateDavinciLinuxSys_Ungz(s8 * const szFileName)
{
	msgprint("[UpdateDavinciLinuxSys_Ungz] update bin package, szFileName->%s.\n", szFileName);
	
	BOOL32 bRet = FALSE;
	BOOL32 bCheck = FALSE;
	s8* pszRandom = NULL;
	s8 achPathName[256] = {0};   //升级文件绝对路径
	
	memcpy(achPathName, "/ramdisk/", sizeof("/ramdisk/"));
	strcat(achPathName, szFileName);

	//升级包校验
	bCheck = CheckBrdUpdatePackage(achPathName);
	if (!bCheck)
	{
		//移除升级文件
		BoardRemoveFile(achPathName);
		return FALSE;
	}

	//开始升级
	bRet = BoardSysUpGrade(achPathName);	
	//删除flash文件
	BoardRemoveFile(achPathName);
	
	return bRet;
}

BOOL32 CTaskUpdate::CheckBrdUpdatePackage(s8 *pszFileName)
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)
	if ( ERROR == BrdCheckUpdatePackage(pszFileName) )
	{
		msgprint("[CTaskUpdate::CheckBrdUpdatePackage], pszFileName->%s, check error!\n", pszFileName);
		return FALSE;		
	}
#endif
	
	msgprint("[CTaskUpdate::CheckBrdUpdatePackage], pszFileName->%s, check success! \n", pszFileName );
	return TRUE;
}

BOOL32 CTaskUpdate::BoardSysUpGrade(s8* pszFileName)
{
	s8 byRet = 0;
	BOOL32 bResult = FALSE;
	BOOL32 bIsDelay = FALSE;
	if (em_mpu2_tp_brd == g_cTaskUpdate.GetBrdType())
	{
		bIsDelay = TRUE;
	}
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	if (bIsDelay)
	{
		byRet = BrdSysUpdate(pszFileName);
	}
	else
	{
		byRet = BrdAllSysUpdate(pszFileName, 1);
	}
	if( bIsDelay )
	{
		OspDelay(1000*120);
	}

	msgprint("update path:%s, bIsDelay:%d, byRet:%d.\n", pszFileName, bIsDelay, byRet);
	switch(byRet)
	{
	case UPDATE_SUCCESS:
		MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::BoardSysUpGrade], UPDATE_SUCCESS update ok !\n"));
		bResult = TRUE;
		break;
		
	case UPDATE_APP_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::BoardSysUpGrade], UPDATE_APP_ERROR app update error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_0S_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::BoardSysUpGrade], UPDATE_0S_ERROR os update error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_BOOT_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::BoardSysUpGrade], UPDATE_BOOT_ERROR boot update error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_SET_FLAG_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::BoardSysUpGrade], UPDATE_SET_FLAG_ERROR set update flag error !\n"));
		bResult = FALSE;
		break;
		
	case UPDATE_ERROR:
		MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::BoardSysUpGrade], UPDATE_ERROR update error !\n"));
		bResult = FALSE;
		break;	
	default:
		MdlHint(Ums_Mdl_Board, ("[CTaskUpdate::BoardSysUpGrade], default error !\n"));
		bResult = FALSE;
		break;
	}
#endif
	msgprint("[CTaskUpdate::BoardSysUpGrade], pszFileName->%s, bResult->%d, bIsDelay:%d \n", pszFileName, bResult, bIsDelay);
	return bResult;
}

BOOL32 CTaskUpdate::BoardRemoveFile(const s8* pszFileName)
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

//获取冗余信息
s8* CTaskUpdate::GetBoardRandomInfo(s8* pszFileName)
{
	static s8 achRandomInfo[256] = {0};
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)  || defined(_LINUX12_)
	if (ERROR == BrdGetUpdateInfo(pszFileName, achRandomInfo))
	{
		msgprint("[CTaskUpdate::GetBoardRandomInfo] achFilePath ->%s, error.\n", pszFileName);
	}
#endif
	msgprint("[CTaskUpdate::GetBoardRandomInfo] pszFileName ->%s, achRandomInfo ->%s, ok .\n", pszFileName, achRandomInfo);
	return achRandomInfo;
}

void CTaskUpdate::Clear()
{
	m_emBrdType = em_unknow_brd;
	memset(m_achFileName, 0, sizeof(m_achFileName));
}