#include "umsserver.h"
#include "tpsys.h"
#include "tptime.h"
#include "eventtpsys.h"
#include "handleconftemplateservice.h"
#include "handlecallservice.h"
#include "handleregservice.h"
#include "handletoolservice.h"
#include "handlehduservice.h"
#include "handleboardservice.h"
#include "handlelicense.h"
#include "tpconfig.h"
#include "umsobject.h"
#include "umsueinit.h"
#include "umscallinit.h"
#include "mediatransinit.h"
#include "umsapi.h"
#include "eqpinterface.h"
#include "addrbook.h"
#include "ummessagestruct.h"
#include "jdconfig.h"
#include "innereventumsserver.h"
#include "innereventumshdu.h"
#include "innereventtvwall.h"
#include "innereventumsboard.h"
#include "innereventregsrv.h"
#include "innereventxmpuvmp.h"



// 外部消息
#include "eventoutumsconftemplate.h"
#include "eventoutsipadapter.h"
#include "eventoutumscall.h"
#include "eventoutumscfg.h"
#include "eventoutumsreg.h"
#include "eventoutumstool.h"
#include "eventoutumsboard.h"
#include "eventoutumshdu2.h"
#include "eventoutumsselview.h"
#include "eventoutumsbrdvmp.h" 
#include "eventoutquantum.h"
#include "eventoutcfgex.h"
#include "eventoutumsmediatrans.h"

extern BOOL32 g_bKedaManuOn;
#define LINUX_HARD_VERSON "tmm v1.0"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"
#endif

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
// 默认值取决于驱动设置
BOOL32 g_bMpcTelnetPortOn = TRUE; // 板卡的telnetport默认放开
BOOL32 g_bMpcFtpOn = TRUE; // 板卡的ftp默认放开 
#endif

API void reboot();
BOOL32 SetEthParam( EmEthInfoType emType ,TTPEthnetInfo& tEth );

CTpUmsServerApp g_cTPUmsServerApp;
API BOOL StartupTpServer()
{
	
	if ( !::InitAddressBook( MAX_ADDRENTRY, MAX_ADDRGROUP, UmsGetFileName(emUmsAddrBookFile) ) )
	{
		msgprint("InitAddressBook failed!\n");
	}

	g_cTPUmsServerApp.CreateApp("TpService",AID_UMSSERVER_APP,100, 1024);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( UMS_SERVICE_APP_INST );
	return TRUE;
}



API void StartNtpd()
{
#ifdef _LINUX_
	TNtpdInfo tNtpdInfo;
	umsGetNtpdInfo( tNtpdInfo );
	CTpTypeAdpt::StartNtpd(tNtpdInfo.m_dwNtpdIp);
#endif
}

API void StopMtService()
{
	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_exit );
	cMsg.Post( UMS_SERVICE_APP_INST,0,UMS_SERVICE_APP_INST );
}

u32	GetLocalIP()
{
	return CTpUmsServer::GetLocalIP();
}

s8*    CTpUmsServer::m_apcServiceName[EndService];
u32 CTpUmsServer::m_dwLocalIP = 0;
EmAppState CTpUmsServer::m_emCallApp = AppIdle;
EmAppState CTpUmsServer::m_emEqpApp = AppIdle;
EmAppState CTpUmsServer::m_emXmpuApp = AppIdle;

CTpUmsServer::CTpUmsServer()
:m_pcTimerMgr(NULL)
{
	m_dwWdGuardTime = 0;
	m_wLogModuleId = Ums_Mdl_Service;
	for( u8 byIdx =0  ;byIdx < EndService ;byIdx++ )
	{
		m_apcService[byIdx] = NULL;	
	}
}



void CTpUmsServer::MessageProc(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	BOOL32 bProccess = FALSE;
	if (wEvent > segment_begin(innerregsrv) && wEvent < segment_end(innerregsrv)
		|| wEvent > segment_begin(outerumsreg) && wEvent < segment_end(outerumsreg) )
	{
		if(m_apcService[_CUmsRegHandleService])
		{
			bProccess = m_apcService[_CUmsRegHandleService]->Handler(ptMsg);
		}
	}
	else if (wEvent > segment_begin(outerumsconftemplate) && wEvent < segment_end(outerumsconftemplate))
	{
		 if(m_apcService[_CUmsConfTemplateHandleService])
		{
			bProccess = m_apcService[_CUmsConfTemplateHandleService]->Handler(ptMsg);
		}
	}
	else if (wEvent > segment_begin(outerumscall) && wEvent < segment_end(outerumscall)
		|| wEvent > segment_begin(outerumsselview) && wEvent < segment_end(outerumsselview))
	{
		if(m_apcService[_CUmsCallHandleService])
		{
			bProccess = m_apcService[_CUmsCallHandleService]->Handler(ptMsg);
		}
	}
	else if (wEvent > segment_begin(outerumstool) && wEvent < segment_end(outerumstool))
	{
		if (m_apcService[_CUmsToolHandleService])
		{
			bProccess = m_apcService[_CUmsToolHandleService]->Handler(ptMsg);
		}
	}
	else if ( (wEvent > segment_begin(tpumswithumshdu2) && wEvent < segment_end(tpumswithumshdu2)) ||
			  (wEvent > segment_begin(umsinnerhdu)  && wEvent < segment_end(umsinnerhdu))  ||
			  (wEvent > segment_begin(umsinnertvwall) && wEvent < segment_end(umsinnertvwall)) ||
			  (wEvent >=  evTPUMS_CNS_hduPlan_Nty && wEvent <= evTPUMS_CNS_HduChangeChanMode_Ind))
	{
		if (m_apcService[_CUmsHduHandleService])
		{
			bProccess = m_apcService[_CUmsHduHandleService]->Handler(ptMsg);
		}
	}
	else if (wEvent > segment_begin(outerumsboard) && wEvent < segment_end(outerumsboard) ||
			(wEvent > segment_begin(umsinnerboard) && wEvent < segment_end(umsinnerboard)) ||
			(wEvent == evXmpu_res_usd_info_res)  )
	{
		if (m_apcService[_CUmsBoardHandleService])
		{
			bProccess = m_apcService[_CUmsBoardHandleService]->Handler(ptMsg);
		}
	}
	else if (wEvent == ev_MpcIsMaster_Ntf || wEvent == ev_umsGetlicenseInfo_Req)
	{
		bProccess = m_apcService[_CUmsLicenseService]->Handler(ptMsg);
	} 
	else if (wEvent > segment_begin(outerumsquantum) && wEvent < segment_end(outerumsquantum))
	{
        bProccess = EvProcQTmsg(ptMsg);
	}
	else if (wEvent > segment_begin(outerumscfgex) && wEvent < segment_end(outerumscfgex) )
	{
		bProccess = EvProcCfgExmsg(ptMsg);
	}
	else
	{
		switch( wEvent ) 
		{
		
		case ev_SysCmsLogoutInd:
			{
				if (NULL != m_apcService[_CUmsRegHandleService])
				{
					bProccess = m_apcService[_CUmsRegHandleService]->Handler(ptMsg);
				}
			}
			break;
		case ev_SysCmsLoginInd:			
			{
				bProccess = EvUserLogin(ptMsg);
				break;
			}

		case EVTP_TIMER_PER_SECOND:		
			{
				bProccess = OnTick();
				break;
			}

		case EVTP_RUNNING:				
			{
				bProccess = OnModulRun(ptMsg);
				break;
			}

		case ev_UmsIPCfg:				
			{
				bProccess = EvSetIpCfg(ptMsg);
				break;
			}

		case ev_UmsSetSysTime_Cmd:		
			{
				bProccess = EvSetSysTime(ptMsg);
				break;
			}

		case ev_UmsGetSysTime_Req:		
			{
				bProccess = EvGetSysTime(ptMsg);
				break;
			}

		//eventoutsipadapter.h中的消息
		case evtp_ums_unreg_ret:
		case evtp_ums_reg_ret:
			{
				if(m_apcService[_CUmsRegHandleService])
				{
					bProccess = m_apcService[_CUmsRegHandleService]->Handler(ptMsg);
				}
			}
			break;

		case ev_kdvmsg_sys_init_ind:		
			bProccess = TRUE;
			break;

		case EVTP_TIMER_WatchdogNotify:
			{
				bProccess = TRUE;
				KillTimer( EVTP_TIMER_WatchdogNotify );				
				SetTimer( EVTP_TIMER_WatchdogNotify, m_dwWdGuardTime );
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
				SysNoticeWdGuard();
#endif
			}
        break;
		
		case ev_umcrebootUms_cmd:
			{
			    bProccess = TRUE;
                SysReboot();
			}
			break;

		default:
			bProccess = ForEach(ptMsg);
			break;			
		}
	}

	if (!bProccess)
	{
		ObjError(("CTpUmsServer::MessageProc msg unproess. msg(%d->%s)\n", wEvent, GetEventNamebyID(wEvent)));
	}
}


BOOL32 CTpUmsServer::ForEach(CTpMsg *const ptMsg)
{			
	for( u8 byIdx =0 ;byIdx < EndService ;byIdx++ )
	{
		if(  m_apcService[byIdx]->Handler( ptMsg ) )
		{
			return TRUE;
		}
	}
	ObjHint(("CTpUmsServer event %d->%s not process!\n" , ptMsg->GetEvent(), GetEventNamebyID(ptMsg->GetEvent()) ));
	return FALSE;
}

BOOL32 CTpUmsServer::BroadCast(CTpMsg *const ptMsg)
{
	for( u8 byIdx =0 ;byIdx < EndService ;byIdx++ )
	{
		if(  m_apcService[byIdx]->Handler( ptMsg ) )
		{
		}
	}
	return TRUE;
}

#define _LoadService( classname )\
	if( NULL == m_apcService[_##classname] )\
{\
	m_apcServiceName[_##classname] = #classname;\
	m_apcService[_##classname] = new classname( this );\
	if( NULL == m_apcService[_##classname] )\
{\
	ObjError(("Init %s failed!\n",#classname ));\
	return FALSE;\
}\
}

BOOL32 CTpUmsServer::OnModulRun(CTpMsg *const ptMsg)
{
	u16 wAppID = GETAPP( ptMsg->GetSrcIId() );
	
	switch( wAppID )
	{
	case  AID_UMSCONFMGR: 
		{
			m_emCallApp = AppRunning;
		}
		break;
	case AID_UMSEQP_APP:
		{
			m_emEqpApp = AppRunning;
		}
		break;
	case AID_UMSXMPU_APP:
		{
			m_emXmpuApp = AppRunning;
		}
		break;
		default:
		{
			msgprint( "OnModulRun unexpected aid->%d\n", wAppID );
		}
	}

	if (AppRunning == m_emEqpApp)
	{
		_LoadService(CUmsHduHandleService);
	}

	

    if( IsAllAppRuning() )
	{
		for( u8 byIdx =0 ;byIdx < EndService ;byIdx++ )
		{
			if(!m_apcService[byIdx]->Create())
			{
				ObjError((" CTpUmsServer::OnModulRun. handle Create Fail! ObjectExit\n"));
				ObjectExit();
				return FALSE;
			}
		}
		
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
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
		
		BrdWebsSetPath( "/usr/bin/webroot" );
		
#endif
		s8* pcUsrInfoFilePath = UmsGetFileName(emUmsUserMgrFile);
		TUmsUeCfg tUeCfg;
		tUeCfg.m_dwUeInst = MAKEIID(AID_CMS2UMS_APP, 0);
		tUeCfg.m_dwToolInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);
		tUeCfg.m_dwServiceInst = UMS_SERVICE_APP_INST;
		umsGetUmsListenPortCfg(tUeCfg.m_wListenPort);
		memcpy(tUeCfg.m_acUsrInfoFilePath, pcUsrInfoFilePath, 
			strlen(pcUsrInfoFilePath)>=TP_MAX_USR_FILE_PATH_LEN?TP_MAX_USR_FILE_PATH_LEN:strlen(pcUsrInfoFilePath));
		tUeCfg.m_acUsrInfoFilePath[TP_MAX_USR_FILE_PATH_LEN-1] = '\0'; 
		
		InitUeLib(tUeCfg);

		//
		OspDelay(3000);

		// 默认关闭mpc2板卡的ftp和telnetport
		CUmsBoardHandleService* pcHandle = (CUmsBoardHandleService*)GetService(_CUmsBoardHandleService);
		pcHandle->SwitchMpcTelnetFtp(em_BoardSwitch_telnet, FALSE);
		pcHandle->SwitchMpcTelnetFtp(em_BoardSwitch_ftp, FALSE);
	}
	return TRUE;
}

BOOL32 CTpUmsServer::IsAllAppRuning()
{
	if( m_emCallApp     != AppRunning ) return FALSE;	
#ifdef	_USE_XMPUEQP_
	if( m_emXmpuApp     != AppRunning ) return FALSE;
#endif
	if( m_emEqpApp     != AppRunning ) return FALSE;
	return TRUE;
}

void  CTpUmsServer::SysReboot(void)
{
	ObjHint((" CTpUmsServer::SysReboot !\n"));
	//立即保存
	ImmediatelySave();
	reboot();
}


BOOL32 CTpUmsServer::ObjectInit(u32 wParam, u32 lParam)
{
	msgprint("CTpUmsServer::ObjectInit\n");
	SetLogTitle("[CTpUmsServer]");
	
	umsGetLocalUmsIP(m_dwLocalIP);

// 	TTPEthnetInfo tEth;
// 	umsGetLocalEthInfo( tEth );
// 	if(!SetParam(DEFAULT_NETMAX_INDEX1, tEth))
// 	{
// 		SetParam(DEFAULT_NETMAX_INDEX0, tEth);
// 	}

	_LoadService( CUmsConfTemplateHandleService				);
	_LoadService( CUmsCallHandleService						);
	_LoadService( CUmsRegHandleService						);
	_LoadService( CUmsToolHandleService						);
	_LoadService( CUmsBoardHandleService                    );
	_LoadService( CUmsLicenseService	                    );


	if (NULL == m_pcTimerMgr)
	{
		m_pcTimerMgr = new CTpTimerMgr;
		m_pcTimerMgr->Create(100);
	}
	//SetTimer(EVTP_TIMER_PER_SECOND, TP_INTERVAL_TIME_ONE_SECOND);
		
	m_bInit = TRUE;

	EvStartModule();
	return TRUE;
}

void CTpUmsServer::ObjectExit()
{
	for( u8 byIdx =0  ;byIdx < EndService ;byIdx++ )
	{
		if( NULL != m_apcService[byIdx] )
		{
			m_apcService[byIdx]->Destroy();
			delete m_apcService[byIdx];
			m_apcService[byIdx] = NULL;
		}
	}

	if (NULL != m_pcTimerMgr)
	{
		delete m_pcTimerMgr;
		m_pcTimerMgr = NULL;
	}
	CUmsObject::ObjectExit();
}




BOOL32 CTpUmsServer::OnTick()
{
	if (NULL != m_pcTimerMgr)
	{
		m_pcTimerMgr->Check();
	}
		
	SetTimer(EVTP_TIMER_PER_SECOND, TP_INTERVAL_TIME_ONE_SECOND);
	return TRUE;
}


u32 CTpUmsServer::AddTimer(u32 dwInterval, u32 pCallBack, void* context)
{
	if (NULL != m_pcTimerMgr)
	{
		return u32(m_pcTimerMgr->AddTimer(dwInterval, (KdvTimerHandler)pCallBack, context));
	}
	return 0;
}

s32 CTpUmsServer::DelTimer(u32 dwTime)
{
	if (NULL != m_pcTimerMgr)
	{
		return m_pcTimerMgr->DeleteTimer((TTpTimer*)dwTime);
	}
	return 0;
}


void CTpUmsServer::NotifySelf(u16 wEvent, u8* pData, u16 wDataSize)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(pData, wDataSize);
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_SERVICE_APP_INST);
}

void InitEqpLib();

#ifdef	_USE_XMPUEQP_
void InitXmpuLib();
#endif
void CTpUmsServer::EvStartModule()
{
	msgprint(" EvStartModule() \n");
		
	TUmsCallCfg tCallCfg;
	umsGetStartUdpPortCfg(tCallCfg.m_wStartPort);
	umsGetMaxOnceCallCfg(tCallCfg.m_wMaxOnceCall);
	InitUmsConfMgr(tCallCfg);
	m_emCallApp = AppStarting;

#ifdef	_USE_XMPUEQP_
	InitXmpuLib();
	m_emXmpuApp = AppStarting;
#endif

	InitEqpLib();
	m_emEqpApp = AppStarting;

	SetTimer(EVTP_TIMER_PER_SECOND, TP_INTERVAL_TIME_ONE_SECOND);
}


void GetSysInfo(TToolSysInfo &tSysInfo)
{
	TOspCpuInfo tCpu;
	if(OspGetCpuInfo(&tCpu))
	{
		tSysInfo.m_dwCpuRate = 100 - tCpu.m_byIdlePercent;
	}

	TOspMemInfo tMem;	
	if(OspGetMemInfo(&tMem))
	{
		u32 dwByteAlloc = tMem.m_dwAllocSize/1024;
		u32 dwByteTotal = tMem.m_dwPhysicsSize/1024;
		u32 dwMemRate = (dwByteAlloc & 0x0000ffff) + (dwByteTotal << 16);
		u32 dwMemAllSize = dwMemRate >> 16;
		u32 dwMemAlloc = dwMemRate & 0xFFFF;
		tSysInfo.m_dwMemRate = dwMemAlloc * 100 / dwMemAllSize;
	}

}

BOOL32 CTpUmsServer::EvUserLogin(CTpMsg *const ptMsg)
{
	TLogUser* pLogUser = (TLogUser*)ptMsg->GetBody();
	EmEthInfoType emEthType;
	TTPEthnetInfo tEth,tVirEth,tEth1,tVirEth1;
	u8 abyBuf[sizeof(TTPEthnetInfo)+sizeof(EmEthInfoType)] = {0};

	umsGetLocalVirEthInfo(tVirEth);
	emEthType = em_eth0_virtual_type;
	memcpy(abyBuf,&tVirEth,sizeof(TTPEthnetInfo));
	memcpy(abyBuf + sizeof(TTPEthnetInfo),&emEthType,sizeof(EmEthInfoType));
	TpNotifyMsgToUeFromService(ev_UmsIPCfg_Ind, abyBuf, sizeof(abyBuf), *pLogUser);

	umsGetLocalEth1Info(tEth1);
	emEthType = em_eth1_type;
	memcpy(abyBuf,&tEth1,sizeof(TTPEthnetInfo));
	memcpy(abyBuf + sizeof(TTPEthnetInfo),&emEthType,sizeof(EmEthInfoType));
	TpNotifyMsgToUeFromService(ev_UmsIPCfg_Ind, abyBuf, sizeof(abyBuf), *pLogUser);

	umsGetLocalVirEth1Info(tVirEth1);
	emEthType = em_eth1_virtual_type;
	memcpy(abyBuf,&tVirEth1,sizeof(TTPEthnetInfo));
	memcpy(abyBuf + sizeof(TTPEthnetInfo),&emEthType,sizeof(EmEthInfoType));
	TpNotifyMsgToUeFromService(ev_UmsIPCfg_Ind, abyBuf, sizeof(abyBuf), *pLogUser);
	
	umsGetLocalEthInfo(tEth);
	emEthType = em_eth0_type;
	memcpy(abyBuf,&tEth,sizeof(TTPEthnetInfo));
	memcpy(abyBuf + sizeof(TTPEthnetInfo),&emEthType,sizeof(EmEthInfoType));
	TpNotifyMsgToUeFromService(ev_UmsIPCfg_Ind, abyBuf, sizeof(abyBuf), *pLogUser);

	
	TTPTime tTPTime;
	TPGetSysTime(tTPTime);
	TpNotifyMsgToUeFromService(ev_UmsGetSysTime_Rsp, &tTPTime, sizeof(tTPTime), *pLogUser);

    TTPQTEncryptInfo tTPQTEncryptInfo;
    umsGetQTEncryptInfo(tTPQTEncryptInfo);
	TpNotifyMsgToUeFromService(ev_QTMTInfo_Nty, &tTPQTEncryptInfo, sizeof(tTPQTEncryptInfo), *pLogUser);

	TPwdCycleInfo tTPPwdCycleInfo;
	umsGetPwdCycleInfo(tTPPwdCycleInfo);
	TpNotifyMsgToUeFromService(ev_updatepwdtimer_Nty, &tTPPwdCycleInfo, sizeof(tTPPwdCycleInfo), *pLogUser);

	// ntpd 配置通知
	TNtpdInfo tNtpdInfo;
	umsGetNtpdInfo(tNtpdInfo);
	TpNotifyMsgToUeFromService(ev_ums_ntpdcfg_nty, &tNtpdInfo.m_dwNtpdIp, sizeof(tNtpdInfo.m_dwNtpdIp), *pLogUser);
// 
	TJDInfo tJdInfo;
	CJDConfig::GetInstance()->GetFromConfigFile(tJdInfo); 
	TpNotifyMsgToUeFromService(ev_ums_Jdcfg_nty,&tJdInfo,sizeof(tJdInfo),*pLogUser);

	BroadCast(ptMsg);

	TUmsVersion tVersion;
	tVersion.SetSoftVersion(GetSoftVersion());
	tVersion.SetHardVersion(GetHardVersion());
	tVersion.m_bKedaManu = g_bKedaManuOn;
	TpNotifyMsgToUeFromService(ev_verInfo_Nty, &tVersion, sizeof(TUmsVersion),*pLogUser);
	MdlHint(Ums_Mdl_Service, ("[EventSysInfo] softver:%s, hardver:%s,IsChanon:%d\n", tVersion.m_abSoftVersion, tVersion.m_abHardVersion,tVersion.m_bKedaManu));
	
	TToolSysInfo tSysInfo;
	GetSysInfo(tSysInfo);
	TpNotifyMsgToUeFromService(ev_sysInfo_Nty, &tSysInfo, sizeof(TToolSysInfo),*pLogUser);
	MdlHint(Ums_Mdl_Service, ("[EventSysInfo] CpuRate:%d, MemRate:%d.\n", tSysInfo.m_dwCpuRate, tSysInfo.m_dwMemRate));

	TLogUser tUserTmp;
	tUserTmp.m_dwUserInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);

	CTpMsg cMsg;
	cMsg.SetEvent(ev_authCount_req);
	cMsg.SetBody(&tUserTmp, sizeof(tUserTmp));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, UMS_SERVICE_APP_INST);
	
	return TRUE;
}

BOOL32 CTpUmsServer::EvSetIpCfg(CTpMsg *const ptMsg)
{
	BOOL32 bIsExit = FALSE;
	TLogUser* pLogUser = (TLogUser*)ptMsg->GetBody();
	TTPEthnetInfo* ptNet = (TTPEthnetInfo*)(ptMsg->GetBody() + sizeof(TLogUser));
	EmEthInfoType * pemEthType = (EmEthInfoType*)(ptMsg->GetBody() + sizeof(TLogUser)+sizeof(TTPEthnetInfo));
	if (*pemEthType == em_eth0_type || *pemEthType == em_eth1_type )
	{
		SetUmsOldIP();
	}
	
	umsSetLocalEthInfo(*ptNet,*pemEthType);

	SetEthParam(*pemEthType, *ptNet);
    u8 abyBuf[sizeof(TTPEthnetInfo)+sizeof(EmEthInfoType)] = {0};
	memcpy(abyBuf,ptNet,sizeof(TTPEthnetInfo));
	memcpy(abyBuf + sizeof(TTPEthnetInfo),pemEthType,sizeof(EmEthInfoType));
	TPBroadMsgToUi(ev_UmsIPCfg_Ind, abyBuf, sizeof(abyBuf));
	TpNotifyMsgToToolUserFromService(ev_UmsIPCfg_Ind, abyBuf, sizeof(abyBuf));

	ObjHint((" EvSetIpCfg success. new Ip("TPIPFORMAT"),type :%d\n", Tpu32ToIP(ptNet->dwIP),*pemEthType));

#if defined(WIN32) || defined(_DISENABLE_MODIFY_SYSTEM_IP_)
	// do not need reboot
#else
	//立即保存
//	ImmediatelySave();
//	reboot(); // let umc reboot the system.
#endif
	return TRUE;
}

BOOL32 CTpUmsServer::EvSetSysTime(CTpMsg *const ptMsg)
{
	TLogUser* pLogUser = (TLogUser*)ptMsg->GetBody();
	TTPTime tTime = *(TTPTime*)(ptMsg->GetBody() + sizeof(TLogUser));

	msgprint(" [EvSetSysTime]:tm_year->%d, tm_mon->%d, tm_mday->%d, tm_hour->%d, tm_min->%d, tm_sec->%d\n", 
		tTime.m_wYear, tTime.m_byMonth, tTime.m_byMDay, tTime.m_byHour, tTime.m_byMinute, tTime.m_bySecond);

	TMpcParam tMpc;
	if (!AssignEqpEx(&tMpc))
	{
		ObjError((" EvSetSysTime No mpc reg. time not save!\n"));
	}

	CTpMsg cMsg;
	cMsg.SetEvent(ev_UmsSetSysTime_Cmd);
	cMsg.SetBody(&tTime, sizeof(tTime));
	cMsg.Post(UMS_EQP_APP_INST, 0, UMS_SERVICE_APP_INST);

	TPSetSysTime(tTime);

	//修改时间通知license做相应判断
	m_apcService[_CUmsLicenseService]->Handler(ptMsg);

	UmsNotifyMsgToService(ev_UpdateConfTimer, NULL, 0);
	
	TPBroadMsgToUi(ev_UmsGetSysTime_Rsp, (u8*)&tTime, sizeof(tTime));

	TpNotifyMsgToToolUserFromService(ev_UmsGetSysTime_Rsp, (u8*)&tTime, sizeof(tTime));

	return TRUE;
}

BOOL32 CTpUmsServer::EvGetSysTime(CTpMsg *const ptMsg)
{
	TLogUser* pLogUser = (TLogUser*)ptMsg->GetBody();
	TTPTime tTPTime;

	MdlHint(Ums_Mdl_Service, (" EvGetSysTime usr:%s!\n", pLogUser->m_achName));
	
	TPGetSysTime(tTPTime);

	TpNotifyMsgToUeFromService(ev_UmsGetSysTime_Rsp, &tTPTime, sizeof(tTPTime), *pLogUser);

	return TRUE;
}

static s8* GetEthInfoTypeName(EmEthInfoType emType)
{
	switch(emType)
	{
	case em_eth0_type:
		return "eth0";
	case em_eth0_virtual_type:
		return "eth0:1";
	case em_eth1_type:
		return "eth1";
	case em_eth1_virtual_type:
		return "eth1:1";
	default:
		return "error";
	}
	return "error";
}


BOOL32 SetEthParam( EmEthInfoType emType ,TTPEthnetInfo& tEth )
{
	MdlHint(Ums_Mdl_Service, ("[SetEthParam] eth type:%d-%s, IP:"TPIPFORMAT", Mask:"TPIPFORMAT", GateWay:"TPIPFORMAT".\n",
		emType, GetEthInfoTypeName(emType), Tpu32ToIP(tEth.dwIP), Tpu32ToIP(tEth.dwMask), Tpu32ToIP(tEth.dwGateWay)));
	
#ifdef _DISENABLE_MODIFY_SYSTEM_IP_
	MdlHint(Ums_Mdl_Service, ("[SetEthParam] _DISENABLE_MODIFY_SYSTEM_IP is on, can not modify system ip!\n"));
	return TRUE;
#endif//_DISENABLE_MODIFY_SYSTEM_IP_
	
#ifdef WIN32
	MdlHint(Ums_Mdl_Service, ("[SetEthParam] can not modify system ip in win32!\n"));
	return TRUE;
#endif //WIN32

#ifndef _JD_TMM_
	if (0 == tEth.dwIP)
	{
		MdlError(Ums_Mdl_Service, ("[SetEthParam] input ip is zero, return false!\n"));
		return FALSE;
	}
#endif // _JD_TMM_

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)

	u8 byIndex = 0;
	if (emType == em_eth0_type || emType == em_eth0_virtual_type)
	{
		byIndex = 0;
	}
	else if (emType == em_eth1_type || emType == em_eth1_virtual_type)
	{
		byIndex = 1;
	}
	else
	{
		return FALSE;
	}

	TBrdEthParam tEtherPara;
	
	tEtherPara.dwIpAdrs = tEth.dwIP;
	tEtherPara.dwIpMask = tEth.dwMask;
	memset( tEtherPara.byMacAdrs, 0, sizeof(tEtherPara.byMacAdrs) );
	if( BrdSetEthParam( byIndex, Brd_SET_IP_AND_MASK, &tEtherPara ) != OK )
	{
		MdlError(Ums_Mdl_Service, ("[api] FAILED! Set Eth%d IP "TPIPFORMAT"Mask"TPIPFORMAT"failed\n",
			byIndex ,Tpu32ToIP( tEth.dwIP ),Tpu32ToIP( tEth.dwMask)));
		return FALSE;
	}
	
	if (BrdSetDefGateway(tEth.dwGateWay) != OK )
	{
		MdlError(Ums_Mdl_Service, ("[api] FAILED! BrdSetDefGateway. Eth%d IP "TPIPFORMAT"Mask"TPIPFORMAT"GW"TPIPFORMAT"\n",
			byIndex ,Tpu32ToIP( tEth.dwIP ),Tpu32ToIP( tEth.dwMask), Tpu32ToIP( tEth.dwGateWay)));
		return FALSE;
	}

	if( BrdSaveNipConfig() != OK)
	{
		MdlError(Ums_Mdl_Service, ("[CEthnetService::SetParam]BrdSaveNipConfig retrun error!\n"));
	}
	MdlHint(Ums_Mdl_Service, ("[api] Set Eth%d IP "TPIPFORMAT"Mask"TPIPFORMAT"GW"TPIPFORMAT"\n",
			byIndex ,Tpu32ToIP( tEth.dwIP ),Tpu32ToIP( tEth.dwMask), Tpu32ToIP( tEth.dwGateWay)));
	return TRUE;
#endif

#ifdef _LINUX_
#if !defined(_PPC_82XX_) && !defined(_PPC_85XX_)
#ifdef _JD_TMM_

	int nRet;
	s8 achNetInfo[255];
	s8 achCommand[255];
	s8 achRmqInfo[255];
		
	s8 achIp[32];
	s8 achMask[32];
	s8 achGateWay[32];

	
	s8 achDeviceName[32];
	s8 achNetName[32];


	BOOL32 bVirtualIp = FALSE;


	if (emType == em_eth0_type)
	{
		memcpy(achDeviceName, "ifcfg-eth0", sizeof("ifcfg-eth0"));
		memcpy(achNetName, "eth0", sizeof("eth0"));
		bVirtualIp = FALSE;
	}
	else if (emType == em_eth0_virtual_type)
	{
		memcpy(achDeviceName, "ifcfg-eth0:1", sizeof("ifcfg-eth0:1"));
		memcpy(achNetName, "eth0:1", sizeof("eth0:1"));
		bVirtualIp = TRUE;
	}
	else if (emType == em_eth1_type)
	{
		memcpy(achDeviceName, "ifcfg-eth1", sizeof("ifcfg-eth1"));
		memcpy(achNetName, "eth1", sizeof("eth1"));
		bVirtualIp = FALSE;
	}
	else if (emType == em_eth1_virtual_type)
	{
		memcpy(achDeviceName, "ifcfg-eth1:1", sizeof("ifcfg-eth1:1"));
		memcpy(achNetName, "eth1:1", sizeof("eth1:1"));
		bVirtualIp = TRUE;
	}
	else
	{
		return FALSE;
	}

	sprintf(achIp, TPIPFORMAT, Tpu32ToIP( tEth.dwIP ));
	sprintf(achMask, TPIPFORMAT, Tpu32ToIP( tEth.dwMask ));
	sprintf(achGateWay, TPIPFORMAT, Tpu32ToIP( tEth.dwGateWay ));

	if ( 0 == tEth.dwIP)
	{
		sprintf(achCommand, "[ -f /etc/sysconfig/network-scripts/%s ] && rm -rf /etc/sysconfig/network-scripts/%s", achDeviceName, achDeviceName);

		nRet = system(achCommand);
		MdlHint(Ums_Mdl_Service, ("[SetEthParam] ret:%d commond:%s\n", nRet, achCommand));
		return TRUE;
	}


	sprintf(achNetInfo,"\"TYPE=Ethernet\nBOOTPROTO=static\nDEVICE=%s\nONBOOT=yes\nNM_CONTROLLED=no\nIPADDR=%s\nNETMASK=%s\nGATEWAY=%s\""
		, achNetName, achIp, achMask, achGateWay);
 	
	sprintf(achCommand, "echo -e %s > /tp/%s", achNetInfo, achDeviceName);
	nRet = system(achCommand);

	sprintf(achCommand, "cp -f /tp/%s /etc/sysconfig/network-scripts/%s", achDeviceName, achDeviceName);

	nRet = system(achCommand);

	MdlHint(Ums_Mdl_Service, ("[SetEthParam] ret:%d commond:%s\n", nRet, achCommand));

	if (!bVirtualIp)
	{
//		SetHostFile(achIp);
		u32_ip dwIP = 0;
		GetUmsOldip(dwIP);
		#define IP_MODIFY_SH "/tp/modifyip.sh"
		// 通过脚本更改host文件
		s8 abyBuf[MAX_MSG_LEN_TMP] = {0};
		sprintf(abyBuf, "%s "TPIPFORMAT" "TPIPFORMAT" &", IP_MODIFY_SH, u32ToIP(dwIP),u32ToIP(tEth.dwIP));

		msgprint("[modifyip] system cmd:%s.\n", abyBuf);
		system(abyBuf);
		SetGKConfigFile(achIp);
	}

	return TRUE;
#else
	u8 byIndex = 0;
	if (emType == em_eth0_type || emType == em_eth0_virtual_type)
	{
		byIndex = 0;
	}
	else if (emType == em_eth1_type || emType == em_eth1_virtual_type)
	{
		byIndex = 1;
	}
	else
	{
		return FALSE;
	}

	int nRet;
	s8 achNetInfo[255];
	s8 achCommand[255];
	s8 achIp[32];
	s8 achMask[32];
	s8 achGateWay[32];

	s8 achDeviceName[32];
	sprintf(achDeviceName, "ifcfg-eth%d", byIndex);

	sprintf(achIp, TPIPFORMAT, Tpu32ToIP( tEth.dwIP ));
	sprintf(achMask, TPIPFORMAT, Tpu32ToIP( tEth.dwMask ));
	sprintf(achGateWay, TPIPFORMAT, Tpu32ToIP( tEth.dwGateWay ));

	sprintf(achNetInfo,"\"DEVICE=eth%d\nONBOOT=yes\nBOOTPROTO=static\nIPADDR=%s\nNETMASK=%s\nGATEWAY=%s\""
		, byIndex, achIp, achMask, achGateWay);

	sprintf(achCommand, "echo -e %s > /usr/%s", achNetInfo, achDeviceName);
	nRet = system(achCommand);

	MdlHint(Ums_Mdl_Service, ("[SetEthParam] ret:%d commond:%s\n", nRet, achCommand));

	sprintf(achCommand, "mv -f /usr/%s /etc/sysconfig/network-scripts/%s", achDeviceName, achDeviceName);
	nRet = system(achCommand);
	MdlHint(Ums_Mdl_Service, ("[SetEthParam] ret:%d commond:%s\n", nRet, achCommand));

	return TRUE;
#endif// _JD_TMM_
#endif //!defined(_PPC_82XX_) && !defined(_PPC_85XX_)
#endif // _LINUX_

	return FALSE;
}


enum tp_ums_service_dump
{
	ums_service_dump_show_conftemp,
	ums_servuce_dump_show_reg_state,
	ums_service_dump_show_board,
	ums_service_dump_show_hdu,
	ums_service_dump_show_hdu_style,
	ums_service_dump_show_license,
	
	ums_service_dump_read_license,
	
	ums_service_dump_show_confinfo,
};

void CTpUmsServer::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case ums_service_dump_show_conftemp:
		{
			CUmsConfTemplateHandleService* pHandle = (CUmsConfTemplateHandleService*)GetService(_CUmsConfTemplateHandleService);
			pHandle->ShowConfTemp();
		}
		break;

	case ums_service_dump_show_confinfo:
		{
			CUmsCallHandleService* pHandle = (CUmsCallHandleService*)GetService(_CUmsCallHandleService);
			pHandle->ShowAllConf();
		}
		break;

	case ums_servuce_dump_show_reg_state:
		{
			CUmsRegHandleService* pHandle = (CUmsRegHandleService*)GetService(_CUmsRegHandleService);
			pHandle->ShowRegState();
		}
		break;
	case ums_service_dump_show_board:
		{
			CUmsBoardHandleService* pcHandle = (CUmsBoardHandleService*)GetService(_CUmsBoardHandleService);
			pcHandle->ShowBoard();
		}
		break;

	case ums_service_dump_show_hdu:
		{
			CUmsHduHandleService* pcHandle = (CUmsHduHandleService*)GetService(_CUmsHduHandleService);
			pcHandle->ShowHdu();
		}
		break;

	case ums_service_dump_show_hdu_style:
		{
			CUmsHduHandleService* pcHandle = (CUmsHduHandleService*)GetService(_CUmsHduHandleService);
			pcHandle->ShowHduStyle();
		}
		break;

	case ums_service_dump_show_license:
		{
			CUmsLicenseService* pcHandle = (CUmsLicenseService*)GetService(_CUmsLicenseService);
			pcHandle->ShowLicense();
		}
		break;
	case ums_service_dump_read_license:
		{
			CUmsLicenseService* pcHandle = (CUmsLicenseService*)GetService(_CUmsLicenseService);
			pcHandle->ReadLicense();
		}
		break;
	default:
		break;
	}
}

s8* CTpUmsServer::GetSoftVersion()
{
	static s8 achSoftWare[MAX_DEVICEVER_LEN] = {0};
	sprintf(achSoftWare, "V%s.%s", UMS_VerID, ConvertDateFormat());
	return achSoftWare;
}

s8* CTpUmsServer::GetHardVersion()
{
	static s8 achHardware[20] = {0};

#ifdef _LINUX_

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	TBrdE2PromInfo tBrdE2PromInfo = { 0 };
	STATUS st = BrdGetE2PromInfo(&tBrdE2PromInfo);
	if (ERROR == st)
	{
		sprintf(achHardware, "%d.%d", BrdQueryHWVersion(), 0);
	}
	else
	{
		sprintf(achHardware, "%d.%d", BrdQueryHWVersion(), tBrdE2PromInfo.dwHWSubVersion);
	}
#else
	sprintf(achHardware,"%s", LINUX_HARD_VERSON);
#endif //defined(_PPC_82XX_) || defined(_PPC_85XX_)

#else

#ifdef WIN32
	sprintf(achHardware,"%s","Win32");
#else
	sprintf(achHardware,"%s","Unkown");
#endif //WIN32

#endif//_LINUX_

	return achHardware;

}
BOOL32 CTpUmsServer::EvSetPwdCycleInfo(CTpMsg *const ptMsg)
{
	TLogUser tLogUser;
	TPwdCycleInfo tTPPwdCycleInfo;
	
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody() );
	TP_SAFE_CAST( tTPPwdCycleInfo, ptMsg->GetBody() + sizeof(TLogUser) );
	
	ObjHint(("EvSetPwdCycleInfo bstart:%d, cycle:%d\n",  tTPPwdCycleInfo.m_bStartUpdate, tTPPwdCycleInfo.m_emPwdCycle));
	
	BOOL32 bRet = FALSE;
	do 
	{
		bRet = umsSetPwdCycleInfo(tTPPwdCycleInfo);

	} while (0);
	
	u8 abyBuf[sizeof(tTPPwdCycleInfo) + sizeof(BOOL32)] =  {0};
	memcpy(abyBuf,&tTPPwdCycleInfo,sizeof(TPwdCycleInfo));
	memcpy(abyBuf + sizeof(TPwdCycleInfo),&bRet,sizeof(BOOL32));
//	ObjHint(("ev_updatepwdtimer_Ind bstart:%d, cycle:%d ,result:%d\n",  tTPPwdCycleInfo.m_bStartUpdate, tTPPwdCycleInfo.m_emPwdCycle,bRet));
	TpNotifyMsgToUeFromService( ev_updatepwdtimer_Ind, abyBuf, sizeof(abyBuf), tLogUser );
	
	
	return TRUE;
	
}


BOOL32 CTpUmsServer::EvSetQTEncryptInfoCmd( CTpMsg *const ptMsg )
{
	TLogUser tLogUser;
	TTPQTEncryptInfo tTPQTEncryptInfo;
	TTPQTEncryptInfo tEncInfoInServer;

	TP_SAFE_CAST( tLogUser, ptMsg->GetBody() );
	TP_SAFE_CAST( tTPQTEncryptInfo, ptMsg->GetBody() + sizeof(TLogUser) );
	
	ObjHint( ("[CTpUmsServer::EvSetQTEncryptInfoCmd] QtOn->%d QuanTumIP->"TPIPFORMAT", dwQuanTumID->%d\n",
		tTPQTEncryptInfo.m_bIsEncQT,
		Tpu32ToIP(tTPQTEncryptInfo.m_dwQuanTumIP),
		tTPQTEncryptInfo.m_dwQuanTumID) );
	
	BOOL32 bRet = FALSE;


	do {
        umsGetQTEncryptInfo(tEncInfoInServer);
		if ((tEncInfoInServer.m_dwQuanTumIP == tTPQTEncryptInfo.m_dwQuanTumIP)  &&
			(tEncInfoInServer.m_dwQuanTumID == tTPQTEncryptInfo.m_dwQuanTumID)  &&
			(tEncInfoInServer.m_bIsEncQT    == tTPQTEncryptInfo.m_bIsEncQT))
		{
            break;
		}

        //有会议不允许改qtip,qtid
		CUmsCallHandleService *pCallHandle = (CUmsCallHandleService*)GetService(_CUmsCallHandleService);
		if (pCallHandle && (pCallHandle->GetRunningConf() > 0))
		{
			 break;
		}

		//修改的qtip qtid 更新到配置
		bRet = umsSetQTEncryptInfo( tTPQTEncryptInfo );


		CTpMsg cMsg;
		cMsg.SetEvent( ev_SetQTEncryptInfo_Cmd );
		cMsg.SetBody( &tTPQTEncryptInfo, sizeof(tTPQTEncryptInfo) );
	    cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON));	

        //更改qtid qtip 重新注册模板

		CUmsRegHandleService* pRegHandle = NULL;
		if (tEncInfoInServer.m_dwQuanTumID != tTPQTEncryptInfo.m_dwQuanTumID)
        {
            pRegHandle = (CUmsRegHandleService*)GetService(_CUmsRegHandleService);

            pRegHandle->UpdateQtId(tTPQTEncryptInfo.m_dwQuanTumID);

			for(u16 wIndex = em_FirstGroup; wIndex <= em_FourthGroup ; wIndex++ )
			{
				pRegHandle->UpdateReg((const EmRegGroupNum)wIndex);
			}
		}


	}while(0);
	
	
	u8 abyBuf[sizeof(TTPQTEncryptInfo) + sizeof(BOOL32)] =  {0};
	memcpy(abyBuf,&tTPQTEncryptInfo,sizeof(TTPQTEncryptInfo));
	memcpy(abyBuf + sizeof(TTPQTEncryptInfo),&bRet,sizeof(BOOL32));
	TpNotifyMsgToUeFromService( ev_SetQTEncryptInfo_Ind, abyBuf, sizeof(abyBuf), tLogUser );

	TLogUser tUserumc;
	if (GETAPP(tLogUser.m_dwUserInst) == AID_UMSTOOL2UMS_APP)
	{    //发给umc , user中app 不为tptool的app 则发给umc
         TpNotifyMsgToUeFromService( ev_SetQTEncryptInfo_Ind, abyBuf, sizeof(abyBuf), tUserumc );
	} else 
	{    //发给tptools
	     TpNotifyMsgToToolUserFromService(ev_SetQTEncryptInfo_Ind, (u8*)abyBuf, sizeof(abyBuf));
	}

	return TRUE;
}

BOOL32 CTpUmsServer::EvProcQTmsg(CTpMsg *const ptMsg)
{
    u16 wEvent = ptMsg->GetEvent();
    BOOL32 bProccess = FALSE;
	switch( wEvent ) 
	{
	case ev_SetQTEncryptInfo_Cmd:
		bProccess = EvSetQTEncryptInfoCmd( ptMsg );
		break;

	case evtp_QtQueryAlias_req:
        bProccess = m_apcService[_CUmsConfTemplateHandleService]->Handler(ptMsg);
		break;

	default:
		bProccess =  FALSE;
	}

	return bProccess;
}

BOOL32 CTpUmsServer::EvProcCfgExmsg(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
    BOOL32 bProccess = FALSE;
	switch( wEvent ) 
	{
	case ev_updatepwdtimer_cmd:
		bProccess = EvSetPwdCycleInfo( ptMsg );
		break;
		
	case ev_ums_ntpdcfg_cmd:
		bProccess = EvNtpdCfgInfo(ptMsg);
		break;
	case evtp_AddConfTemplateEx_req:
		if(m_apcService[_CUmsConfTemplateHandleService])
		{
			bProccess = m_apcService[_CUmsConfTemplateHandleService]->Handler(ptMsg);
		}
		break;
	case ev_ums_downloadlog_req:
		bProccess = DownloadLogInfo(ptMsg);
		break;
	default:
		bProccess =  FALSE;
	}
	
	return bProccess;

}

BOOL32 CTpUmsServer::EvNtpdCfgInfo( CTpMsg *const ptMsg )
{
	TLogUser	tLogUser;
	u32_ip		dwNtpdIp = 0;
	TNtpdInfo	tNtpdInfo;

	TP_SAFE_CAST( tLogUser, ptMsg->GetBody() );
	TP_SAFE_CAST( dwNtpdIp, ptMsg->GetBody() + sizeof(TLogUser) );
	umsGetNtpdInfo(tNtpdInfo);
	
	ObjHint(("CTpUmsServer::EvNtpdCfgInfo oldNtpdIp:"TPIPFORMAT", newIp:"TPIPFORMAT"\n",
			u32ToIP(tNtpdInfo.m_dwNtpdIp), u32ToIP(dwNtpdIp)));
	
	if (dwNtpdIp != tNtpdInfo.m_dwNtpdIp)
	{
		tNtpdInfo.m_dwNtpdIp = dwNtpdIp;
		umsSetNtpdInfo(tNtpdInfo);
#ifdef _LINUX_
		CTpTypeAdpt::StartNtpd(dwNtpdIp);
#endif
	}
	
	TpNotifyMsgToUeFromService( ev_ums_ntpdcfg_nty, &dwNtpdIp, sizeof(dwNtpdIp), tLogUser );
	
	return TRUE;
}

BOOL32 CTpUmsServer::DownloadLogInfo(CTpMsg *const ptMsg)
{
#ifdef _LINUX_
	BOOL32 bRet;
	u32 dwRet;
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody() );
	#define UMSLOG_START_SH "/tp/downloadlog.sh"
	s8 abyBuf[MAX_MSG_LEN_TMP] = {0};
	memcpy(abyBuf,UMSLOG_START_SH,sizeof(UMSLOG_START_SH));
	msgprint("[DownloadLogInfo] system cmd: %s.\n", abyBuf);
	dwRet = system(abyBuf);
	if (dwRet == 0)
	{
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}
	ObjHint(("CTpUmsServer::DownloadLogInfo result:%d\n",bRet));
	TpNotifyMsgToUeFromService( ev_ums_downloadlog_rsp, &bRet, sizeof(bRet), tLogUser );

	
#endif
	return TRUE;

}
API void showconftemp()
{
	OspInstDump(AID_UMSSERVER_APP,  1, ums_service_dump_show_conftemp);
}

API void showallconf()
{
	OspInstDump(AID_UMSSERVER_APP,  1, ums_service_dump_show_confinfo);
}

API void showregstate()
{
	OspInstDump(AID_UMSSERVER_APP,  1, ums_servuce_dump_show_reg_state);
}

API void showhdu()
{
	OspInstDump(AID_UMSSERVER_APP,  1, ums_service_dump_show_hdu);
}

API void showhdustyle()
{
	OspInstDump(AID_UMSSERVER_APP,  1, ums_service_dump_show_hdu_style);
}

API void showlicense()
{
	OspInstDump(AID_UMSSERVER_APP,  1, ums_service_dump_show_license);
}

API void readlicense()
{
	//OspInstDump(AID_UMSSERVER_APP,  1, ums_service_dump_read_license);	
	TLogUser tLogUser;
	CTpMsg cMsg;
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.SetEvent(ev_umsGetlicenseInfo_Req);
	cMsg.Post(UMS_SERVICE_APP_INST);

}

API void reqallreginfo()
{
	TLogUser tLogUser;
	EmGetRegInfoType tType = emGetRegInfoType_ALL;
	
	CTpMsg cMsg;
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tType, sizeof(tType));
	cMsg.SetEvent(ev_umsGetRegInfo_Req);
	cMsg.Post(UMS_SERVICE_APP_INST);	
}

API void requmsreginfo()
{
	TLogUser tLogUser;
	EmGetRegInfoType tType = emGetRegInfoType_UMS;
	
	CTpMsg cMsg;
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tType, sizeof(tType));
	cMsg.SetEvent(ev_umsGetRegInfo_Req);
	cMsg.Post(UMS_SERVICE_APP_INST);	
}

API void reqcnsreginfo()
{
	TLogUser tLogUser;
	EmGetRegInfoType tType = emGetRegInfoType_CNS;
	
	CTpMsg cMsg;
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tType, sizeof(tType));
	cMsg.SetEvent(ev_umsGetRegInfo_Req);
	cMsg.Post(UMS_SERVICE_APP_INST);	
}


API void setqt(u8 byOnOff, s8* pszQtIP, s32 dwQtID )
{
	TLogUser tLogUser;
	TTPQTEncryptInfo tTPQTEncryptInfo;

    tTPQTEncryptInfo.m_bIsEncQT = FALSE;
	if (byOnOff)
	{
        tTPQTEncryptInfo.m_bIsEncQT = TRUE;
	}

	tTPQTEncryptInfo.m_dwQuanTumIP = inet_addr(pszQtIP);
	tTPQTEncryptInfo.m_dwQuanTumID = dwQtID;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_SetQTEncryptInfo_Cmd);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tTPQTEncryptInfo, sizeof(tTPQTEncryptInfo));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void setcycle(BOOL32 bStart,EmUpdatePwdTimer emTimer)
{
	TLogUser tLogUser;
	TPwdCycleInfo tTPPwdCycleInfo;
	tTPPwdCycleInfo.m_bStartUpdate = bStart;
	tTPPwdCycleInfo.m_emPwdCycle = emTimer;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_updatepwdtimer_cmd);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tTPPwdCycleInfo, sizeof(tTPPwdCycleInfo));
	cMsg.Post(UMS_SERVICE_APP_INST);
}
API void setip(s8* pszIp, s8* pszMask, s8* pszGate,u16 wType)
{
	TLogUser tUser;
	TTPEthnetInfo tEthNet;
	tEthNet.bEnable = TRUE;
	tEthNet.dwIP = inet_addr(pszIp);
	tEthNet.dwMask = inet_addr(pszMask);
	tEthNet.dwGateWay = inet_addr(pszGate);
	EmEthInfoType emEthType = (EmEthInfoType)wType;
	CTpMsg cMsg;	
	cMsg.SetEvent(ev_UmsIPCfg);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tEthNet, sizeof(tEthNet));
	cMsg.CatBody(&emEthType, sizeof(emEthType));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);	

}
API void setreg(BOOL32 bUsed, s8* pDstIp, u16 wDstPort, u16 wExpire)
{
	TLogUser tUser;
	TTPSipRegistrarCfg tReg;
	tReg.bUsed = bUsed;
	tReg.dwRegIP = inet_addr(pDstIp);
	tReg.wRegPort = wDstPort;
	tReg.wExpire = wExpire;
	
	CTpMsg cMsg;	
	cMsg.SetEvent(ev_umsreg_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tReg, sizeof(tReg));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);	
}

API void setgkreg(BOOL32 bUsed, s8* pDstIp, u16 wExpire)
{
	TLogUser tUser;
	TTPGKCfg tGkRegInfo;
	tGkRegInfo.bUsed = bUsed;
	tGkRegInfo.dwGKIP = inet_addr(pDstIp);
	tGkRegInfo.wExpire = wExpire;

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_umsGKReg_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tGkRegInfo, sizeof(tGkRegInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);	
}

API void unreg()
{
	TLogUser tUser;
	CTpMsg cMsg;	
	cMsg.SetEvent(evtp_ums_unreg_req);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);	
}

API void addex(u16 wConfId,u16 wNum,u16 wEpId1,EmTpConfProtocol emEpCall1,u16 wEpId2,EmTpConfProtocol emEpCall2,
				 u16 wEpId3,EmTpConfProtocol emEpCall3)
{
	TLogUser tLogUser;
	TTemplateConfEx tTmpCall;
	tTmpCall.m_wTempID = wConfId;
	tTmpCall.m_wNum = wNum;
	if (wNum >0)
	{
		tTmpCall.m_awEpID[0] = wEpId1;
		tTmpCall.m_aemCallProtocol[0] = emEpCall1;
	}
	if (wNum >1)
	{
		tTmpCall.m_awEpID[1] = wEpId2;
		tTmpCall.m_aemCallProtocol[1] = emEpCall2;
	}
	if (wNum >2)
	{
		tTmpCall.m_awEpID[2] = wEpId3;
		tTmpCall.m_aemCallProtocol[2] = emEpCall3;
	}



	CTpMsg cMsg;
	
	cMsg.SetEvent(evtp_AddConfTemplateEx_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tTmpCall, sizeof(TTemplateConfEx));
	cMsg.Post(UMS_SERVICE_APP_INST);

	
}
API void add(s8* pE164Name, u8 byEncryptModel,  u16 wEpNum, s8* pEpName1 = NULL, s8* pEpName2 = NULL, s8* pEpName3 = NULL
			 , s8* pEpName4 = NULL, s8* pEpName5 = NULL, s8* pEpName6 = NULL)
{
	TLogUser tLogUser;

	TTPConfTemplate tInfo;
	tInfo.m_wID = TP_INVALID_INDEX;
	strcpy(tInfo.m_achConfName, pE164Name);
	tInfo.m_wConfBitRate	= TP_UMS_CHAN_BITRATE;
	tInfo.m_dwPersistenceTime = 10240;
	tInfo.m_tStartTime = 0;
//	tInfo.m_emTpAudioFormat = emTPAMpegAACLD;
/*	tInfo.m_byEncryptModel = emTPEncryptTypeNone;*/
	tInfo.m_wDefaultChairMan = 0;
	tInfo.m_tTurnList.m_wInterval = 30;
	tInfo.m_wMainNum = 1;
	tInfo.m_wMinorNum = 1;
	tInfo.m_atTpMainVideoRes[0].m_emRes = emTPVHD1080p1920x1080;
	tInfo.m_atTpMinorVideoRes[0].m_emRes = emTPVHD1080p1920x1080;
//	tInfo.m_tEncrypt.m_emEncryptModel = emTPEncryptTypeAES;
//	tInfo.m_bDefaultEncrypt = TRUE;
//	strcpy(tInfo.m_tEncrypt.m_achEncKey,"!@###@F`~2");

	switch(byEncryptModel)
	{
	case emTPEncryptTypeDES:
	case emTPEncryptTypeAES:
	case emTPEncryptTypeH239:
	case emTPEncryptTypeQtEverySecond:
	case emTPEncryptTypeQtEveryMinute:
	case emTPEncryptTypeQtEveryConf:
        tInfo.m_tEncrypt.m_emEncryptModel = (EmTPEncryptType)byEncryptModel;
		break;
	default:
		tInfo.m_tEncrypt.m_emEncryptModel = emTPEncryptTypeNone;
		break;
	}


	if (wEpNum > 6)
	{
		wEpNum = 0;
	}

	if ( wEpNum > 0 )
	{
		tInfo.m_atEpList.m_tCnsList[0].m_wEpID = 0;
		tInfo.m_atEpList.m_tCnsList[0].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tInfo.m_atEpList.m_tCnsList[0].m_tEpAddr.m_tAlias.m_abyAlias, pEpName1);

		tInfo.m_atEpList.m_wNum ++;
	}
	
	if ( wEpNum > 1 )
	{
		tInfo.m_atEpList.m_tCnsList[1].m_wEpID = 1;
		tInfo.m_atEpList.m_tCnsList[1].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tInfo.m_atEpList.m_tCnsList[1].m_tEpAddr.m_tAlias.m_abyAlias, pEpName2);

		tInfo.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 2 )
	{
		tInfo.m_atEpList.m_tCnsList[2].m_wEpID = 2;
		tInfo.m_atEpList.m_tCnsList[2].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tInfo.m_atEpList.m_tCnsList[2].m_tEpAddr.m_tAlias.m_abyAlias, pEpName3);
		
		tInfo.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 3 && pEpName4 )
	{
		tInfo.m_atEpList.m_tCnsList[3].m_wEpID = 3;
		tInfo.m_atEpList.m_tCnsList[3].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tInfo.m_atEpList.m_tCnsList[3].m_tEpAddr.m_tAlias.m_abyAlias, pEpName4);
		
		tInfo.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 4 && pEpName5 )
	{
		tInfo.m_atEpList.m_tCnsList[4].m_wEpID = 4;
		tInfo.m_atEpList.m_tCnsList[4].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tInfo.m_atEpList.m_tCnsList[4].m_tEpAddr.m_tAlias.m_abyAlias, pEpName5);
		
		tInfo.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 5 && pEpName6 )
	{
		tInfo.m_atEpList.m_tCnsList[5].m_wEpID = 5;
		tInfo.m_atEpList.m_tCnsList[5].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tInfo.m_atEpList.m_tCnsList[5].m_tEpAddr.m_tAlias.m_abyAlias, pEpName6);
		
		tInfo.m_atEpList.m_wNum ++;
	}
	
	TTPConfTemplateBuf tBuf;
	tBuf.SetValue(tInfo);

	CTpMsg cMsg;

	cMsg.SetEvent(evtp_AddConfTemplate_req1);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tBuf.m_tTemplate, sizeof(tBuf.m_tTemplate));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void add128template()
{
	s8 szTemplatename[256] = {0};
	
	for(u16 wIndex = 0 ;wIndex < TP_CONFTEMPLATE_MAXNUM ; ++wIndex)
	{
		sprintf(szTemplatename,"%s%d","template_",wIndex+1);
		add(szTemplatename,0,5,"y1","y2","y3","y4","y5");
		OspDelay(50);
	}
}

API void addfulltemp(s8 *confnamebase,s8 *e164namebase)
{
	TLogUser tLogUser;
 
	TTPConfTemplate* tInfo = new TTPConfTemplate[TP_CONFTEMPLATE_MAXNUM];

	s8 achconfname[256] = {0};
	s8 achE164name[256] = {0};
	s8 achconfnamebu[256] = {0};
	s8 achE164namebu[256] = {0};

	for(u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		tInfo[wIndex].m_wID = TP_INVALID_INDEX;
		memset(achconfname,0,256);
		memset(achE164name,0,256);
		memset(achconfnamebu,0,256);
		memset(achE164namebu,0,256);
		sprintf(achconfnamebu,"%d",wIndex+1);
		sprintf(achE164namebu,"%d",wIndex+1);

		
		strcpy(achconfname,confnamebase);
		strcpy(achE164name,e164namebase);
		strcat(achconfname,achconfnamebu);
		strcat(achE164name,achE164namebu);

		strcpy(tInfo[wIndex].m_achConfName,achconfname);
		strcpy(tInfo[wIndex].m_achConfE164,achE164name);

		tInfo[wIndex].m_wConfBitRate	= TP_UMS_CHAN_BITRATE;
		tInfo[wIndex].m_dwPersistenceTime = 10240;
		tInfo[wIndex].m_tStartTime = 0;
	//	tInfo[wIndex].m_emTpAudioFormat = emTPAMpegAACLD;
/*		tInfo[wIndex].m_byEncryptModel = emTPEncryptTypeNone;*/
		tInfo[wIndex].m_wDefaultChairMan = 1;
		tInfo[wIndex].m_tTurnList.m_wInterval = 20;

		TTPConfTemplateBuf tBuf;
		tBuf.SetValue(tInfo[wIndex]);

		CTpMsg cMsg;

		cMsg.SetEvent(evtp_AddConfTemplate_req1);
		cMsg.SetBody(&tLogUser, sizeof(tLogUser));
		cMsg.CatBody(&tBuf.m_tTemplate, sizeof(tBuf.m_tTemplate));
		cMsg.Post(UMS_SERVICE_APP_INST);
		OspDelay(500);
	}

	delete[] tInfo;
	tInfo = NULL;
}
API void downloadlog()
{
	TLogUser tLogUser;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_ums_downloadlog_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.Post(UMS_SERVICE_APP_INST);	

}

API void del(u16 wConfid)
{
	TLogUser tLogUser;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_DelConftemplate_Req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&wConfid, sizeof(wConfid));
	cMsg.Post(UMS_SERVICE_APP_INST);	
}

API void delall()
{
	for(u16 wIndex =  1 ; wIndex <= TP_CONFTEMPLATE_MAXNUM; wIndex++)
	{
		TLogUser tLogUser;
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_DelConftemplate_Req);
		cMsg.SetBody(&tLogUser,sizeof(tLogUser));
		cMsg.CatBody(&wIndex,sizeof(wIndex));
		cMsg.Post(UMS_SERVICE_APP_INST);
	}
}

API void startconf(u16 wConfID)
{
	TLogUser tLogUser;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_StartConfTemplate_Req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&wConfID, sizeof(wConfID));
	cMsg.Post(UMS_SERVICE_APP_INST);
	
}

API void startmeet(s8* pE164Name, u16 wEpNum, s8* pEpName1 = NULL, s8* pEpName2 = NULL, s8* pEpName3 = NULL
				   , s8* pEpName4 = NULL, s8* pEpName5 = NULL, s8* pEpName6 = NULL)
{
	static u16 tempconfid = TP_CONFTEMPLATE_MAXNUM;
	TLogUser tLogUser;
	TTPConfMeet tRes;
	TTPConfMeet tRhs;
	tRes.m_wID = tempconfid;
    tempconfid++;
	strcpy(tRes.m_achConfName, pE164Name);
	tRes.m_wConfBitRate	= TP_UMS_CHAN_BITRATE;

	tRes.m_wMainNum = 1;
	tRes.m_wMinorNum = 1;
	tRes.m_atTpMainVideoRes[0].m_emRes = emTPVHD1080p1920x1080;
	tRes.m_atTpMinorVideoRes[0].m_emRes = emTPVHD1080p1920x1080;


	if (wEpNum > 6)
	{
		wEpNum = 0;
	}

	if ( wEpNum > 0 )
	{
		tRes.m_atEpList.m_tCnsList[0].m_wEpID = 0;
		tRes.m_atEpList.m_tCnsList[0].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tRes.m_atEpList.m_tCnsList[0].m_tEpAddr.m_tAlias.m_abyAlias, pEpName1);

		tRes.m_atEpList.m_wNum ++;
	}
	
	if ( wEpNum > 1 )
	{
		tRes.m_atEpList.m_tCnsList[1].m_wEpID = 1;
		tRes.m_atEpList.m_tCnsList[1].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tRes.m_atEpList.m_tCnsList[1].m_tEpAddr.m_tAlias.m_abyAlias, pEpName2);

		tRes.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 2 )
	{
		tRes.m_atEpList.m_tCnsList[2].m_wEpID = 2;
		tRes.m_atEpList.m_tCnsList[2].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tRes.m_atEpList.m_tCnsList[2].m_tEpAddr.m_tAlias.m_abyAlias, pEpName3);
		
		tRes.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 3 && pEpName4 )
	{
		tRes.m_atEpList.m_tCnsList[3].m_wEpID = 3;
		tRes.m_atEpList.m_tCnsList[3].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tRes.m_atEpList.m_tCnsList[3].m_tEpAddr.m_tAlias.m_abyAlias, pEpName4);
		
		tRes.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 4 && pEpName5 )
	{
		tRes.m_atEpList.m_tCnsList[4].m_wEpID = 4;
		tRes.m_atEpList.m_tCnsList[4].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tRes.m_atEpList.m_tCnsList[4].m_tEpAddr.m_tAlias.m_abyAlias, pEpName5);
		
		tRes.m_atEpList.m_wNum ++;
	}

	if ( wEpNum > 5 && pEpName6 )
	{
		tRes.m_atEpList.m_tCnsList[5].m_wEpID = 5;
		tRes.m_atEpList.m_tCnsList[5].m_tEpAddr.m_tAlias.m_byType = tp_Alias_h323;
		strcpy(tRes.m_atEpList.m_tCnsList[5].m_tEpAddr.m_tAlias.m_abyAlias, pEpName6);
		
		tRes.m_atEpList.m_wNum ++;
	}



	tRhs.m_wID = htons(tRes.m_wID);

	u16 wIndex = 0;

	memcpy(tRhs.m_achConfName, tRes.m_achConfName, TP_MAX_ALIAS_LEN+1);
	memcpy(tRhs.m_achConfE164, tRes.m_achConfE164, TP_MAX_ALIAS_LEN+1);
	
	tRhs.m_wConfBitRate = htons(tRes.m_wConfBitRate);
	tRhs.m_wHpDualBitRate = htons(tRes.m_wHpDualBitRate);

	tRhs.m_tEncrypt = tRes.m_tEncrypt;
	tRhs.m_tEncrypt.m_emEncryptModel = (EmTPEncryptType)htonl(tRes.m_tEncrypt.m_emEncryptModel);
	tRhs.m_bDefaultEncrypt = (BOOL32)htonl(tRes.m_bDefaultEncrypt);
	
	
	tRhs.m_wMainNum = htons(tRes.m_wMainNum);
	tRhs.m_wMinorNum = htons(tRes.m_wMinorNum);
	
	for ( wIndex = 0; wIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; wIndex ++ )
	{
		tRhs.m_atTpMainVideoRes[wIndex].m_emFormat = (EmTpVideoFormat)htonl(tRes.m_atTpMainVideoRes[wIndex].m_emFormat);
		tRhs.m_atTpMainVideoRes[wIndex].m_emQualityLvl = (EmTpVideoQualityLevel)htonl(tRes.m_atTpMainVideoRes[wIndex].m_emQualityLvl);
		tRhs.m_atTpMainVideoRes[wIndex].m_emRes = (EmTpVideoResolution)htonl(tRes.m_atTpMainVideoRes[wIndex].m_emRes);
		tRhs.m_atTpMainVideoRes[wIndex].m_wBitrate = htons(tRes.m_atTpMainVideoRes[wIndex].m_wBitrate);
		tRhs.m_atTpMainVideoRes[wIndex].m_wFrameRate = htons(tRes.m_atTpMainVideoRes[wIndex].m_wFrameRate);
	}
	
	for ( wIndex = 0; wIndex < TP_CONF_MAX_MINOR_VIDEO_RES_NUM; wIndex ++ )
	{
		tRhs.m_atTpMinorVideoRes[wIndex].m_emFormat = (EmTpVideoFormat)htonl(tRes.m_atTpMinorVideoRes[wIndex].m_emFormat);
		tRhs.m_atTpMinorVideoRes[wIndex].m_emQualityLvl = (EmTpVideoQualityLevel)htonl(tRes.m_atTpMinorVideoRes[wIndex].m_emQualityLvl);
		tRhs.m_atTpMinorVideoRes[wIndex].m_emRes = (EmTpVideoResolution)htonl(tRes.m_atTpMinorVideoRes[wIndex].m_emRes);
		tRhs.m_atTpMinorVideoRes[wIndex].m_wBitrate = htons(tRes.m_atTpMinorVideoRes[wIndex].m_wBitrate);
		tRhs.m_atTpMinorVideoRes[wIndex].m_wFrameRate = htons(tRes.m_atTpMinorVideoRes[wIndex].m_wFrameRate);
	}
	
	tRhs.m_wAudFmtNum = htons(tRes.m_wAudFmtNum);
	for ( wIndex = 0; wIndex < TP_CONF_MAX_AUD_FMT_NUM; wIndex ++ )
	{
		tRhs.m_atAudFmt[wIndex].m_emFormat = (EmTpAudioFormat)htonl(tRes.m_atAudFmt[wIndex].m_emFormat);
		tRhs.m_atAudFmt[wIndex].m_emSampleFreq = (EmTPAACSampleFreq)htonl(tRes.m_atAudFmt[wIndex].m_emSampleFreq);
		tRhs.m_atAudFmt[wIndex].m_emChnlCfg = (EmTPAACChnlCfg)htonl(tRes.m_atAudFmt[wIndex].m_emChnlCfg);
		tRhs.m_atAudFmt[wIndex].m_byReserve1 = tRes.m_atAudFmt[wIndex].m_byReserve1;
		tRhs.m_atAudFmt[wIndex].m_byReserve2 = tRes.m_atAudFmt[wIndex].m_byReserve2;
	}
	
	tRhs.m_wUpBandWid = htons(tRes.m_wUpBandWid);
	tRhs.m_wDownBandWid = htons(tRes.m_wDownBandWid);
	
	tRhs.m_atEpList.m_wNum = htons(tRes.m_atEpList.m_wNum);
	for ( wIndex = 0; wIndex < TP_CONF_MAX_EPNUM; wIndex ++ )
	{
		tRhs.m_atEpList.m_tCnsList[wIndex].m_wEpID = htons(tRes.m_atEpList.m_tCnsList[wIndex].m_wEpID);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_bAliasIP = htonl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_bAliasIP);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_byCallType = (EmTpAliasType)htonl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_byCallType);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP = tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP;
		
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_byType = (EmTpAliasType)htonl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_byType);
		strncpy(tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias, tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
		
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_byType = (EmTpAliasType)htonl(tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_byType);
		strncpy(tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias, tRes.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);
		tRhs.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	}
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_StartInterimMeeting_Req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tRhs, sizeof(tRhs));
	cMsg.Post(UMS_SERVICE_APP_INST);
}


// add by gaoyong  
// umc控制远端哑音
API void umcmuteep(u16 wConfID, u16 wEpId, BOOL32 bIsMute)
{
	TLogUser tLogUser;
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = wConfID;
	tConfEpID.m_wEpID = wEpId;

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_MuteEp_cmd);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tConfEpID, sizeof(tConfEpID));
	cMsg.CatBody(&bIsMute, sizeof(bIsMute));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);

}

// umc控制远端静音
API void umcquietep(u16 wConfID, u16 wEpId, BOOL32 bIsQuiet)
{
	TLogUser tLogUser;
	TConfEpID tConfEpID;
	tConfEpID.m_wConfID = wConfID;
	tConfEpID.m_wEpID = wEpId;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_QuietEp_cmd);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tConfEpID, sizeof(tConfEpID));
	cMsg.CatBody(&bIsQuiet, sizeof(bIsQuiet));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
	
}

// umc挂断会议中的某个会场
API void umcdropep(u16 wConfID, u16 wEpId)
{
	TLogUser tLogUser;
	TConfEpID tConfEpId;

	tConfEpId.m_wConfID = wConfID;
	tConfEpId.m_wEpID = wEpId;

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_DropEp_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfEpId, sizeof(TConfEpID));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

// umc呼叫会议中某个不在线的会场
API void umccallep(u16 wConfID, u16 wEpId)
{
	TLogUser tLogUser;
	TConfEpID tConfEpId;
	
	tConfEpId.m_wConfID = wConfID;
	tConfEpId.m_wEpID = wEpId;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_CallExistEP_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfEpId, sizeof(TConfEpID));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

// umc邀请会场加入会议
API void umcinviteep(u16 wConfID, s8* pAlias)
{
	TLogUser tLogUser;	
	TConfCallEpAddr tConfEpAddr;
	tConfEpAddr.m_wConfID = wConfID;
	tConfEpAddr.m_tCallAddr.m_tAlias.m_byType = tp_Alias_h323;
	strncpy(tConfEpAddr.m_tCallAddr.m_tAlias.m_abyAlias, pAlias, TP_MAX_ALIAS_LEN + 1);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_CallEP_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfEpAddr, sizeof(TConfCallEpAddr));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

// umc指定会议发言人
API void umcapplyspeaker(u16 wConfId, u16 wEpId)
{
	TLogUser tLogUser;
	TConfEpID tConfEpId;
	
	tConfEpId.m_wConfID = wConfId;
	tConfEpId.m_wEpID = wEpId;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ApplySpeaker_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfEpId, sizeof(TConfEpID));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

// 远遥请求 fromumc
API void umcfeccep(u16 wConfID, u16 wDstEp, u8 byFeccType, u8 byCamType)
{
	TLogUser tLogUser;

	CTpMsg cMsg;
	switch((EmUmsFeccActType)byFeccType)
	{
	case em_Fecc_CamerStart:
	case em_Fecc_CamerStop:
	case em_Fecc_CamerAudoFocus:
		{
			TCamReq tReq;
			tReq.m_wConfID	= wConfID;
			tReq.m_wEpID	= wDstEp;
			tReq.m_emCamAct = (EmUmsFeccActType)byFeccType;
			tReq.m_emCamReq = (EmUmsCamerReqType)byCamType;
			cMsg.SetEvent(evtp_FeccCamera_Req);
			cMsg.SetBody(&tLogUser, sizeof(TLogUser));
			cMsg.CatBody(&tReq, sizeof(TCamReq));
		}
		break;
	case em_Fecc_SavePos:
	case em_Fecc_LoadPos:
		{
			TPrePos tReq;
			tReq.m_wConfID	= wConfID;
			tReq.m_wEpID	= wDstEp;
			tReq.m_emPosAct = (EmUmsFeccActType)byFeccType;
			tReq.m_dwSaveNo = (u32)byCamType;
			cMsg.SetEvent(evtp_FeccPrePos_Req);
			cMsg.SetBody(&tLogUser, sizeof(TLogUser));
			cMsg.CatBody(&tReq, sizeof(TCamReq));
		}
		break;
	case em_Fecc_SwitchVideo:
	case em_Fecc_SelectVideo:
		{
			TSelVid tReq;
			tReq.m_wConfID	= wConfID;
			tReq.m_wEpID	= wDstEp;
			tReq.m_emVidAct = (EmUmsFeccActType)byFeccType;
			tReq.m_dwVidNo  = (u32)byCamType;
			cMsg.SetEvent(evtp_FeccSelVid_Req);
			cMsg.SetBody(&tLogUser, sizeof(TLogUser));
			cMsg.CatBody(&tReq, sizeof(TCamReq));

		}
		break;
	default:
		return;

	}
	
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

//发双流
API void umcstartdual(u16 wConfId, u16 wEpId)
{
	TLogUser tLogUser;
	TConfEpID tConfEpId;
	
	tConfEpId.m_wConfID = wConfId;
	tConfEpId.m_wEpID = wEpId;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_StartDual_Cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfEpId, sizeof(TConfEpID));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

//停止双流
API void umcstopdual(u16 wConfId, u16 wEpId)
{
	TLogUser tLogUser;
	TConfEpID tConfEpId;
	
	tConfEpId.m_wConfID = wConfId;
	tConfEpId.m_wEpID = wEpId;
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_StopDual_Cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfEpId, sizeof(TConfEpID));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

//轮询
API void umcpoll(u16 wConfId, BOOL32 bIsStart)
{
	TLogUser tLogUser;

	CTpMsg cMsg;
	if (bIsStart)
	{
		cMsg.SetEvent(evtp_StartTurn_cmd);
	}
	else
	{
		cMsg.SetEvent(evtp_StopTurn_cmd);
	}	
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&wConfId, sizeof(u16));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

//轮询列表更新
API void umcupdatepoll(u16 wConfId)
{
	TLogUser tLogUser;
	TConfTurnInfo tConfTurnInfo;
	
	tConfTurnInfo.m_wConfID = wConfId;
	tConfTurnInfo.m_atTurnList.m_wInterval = 5;
	tConfTurnInfo.m_atTurnList.m_bPollOn = FALSE;

	CTpMsg cMsg;

	cMsg.SetEvent(evtp_UpdateTurn_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfTurnInfo, sizeof(TConfTurnInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

//选看
API void umcview(u16 wConfID, u16 wEpID, u16 wStreenIndex)
{
	TLogUser tLogUser;
	TConfEpID tConfEpId;

	tConfEpId.m_wConfID = wConfID;
	tConfEpId.m_wEpID = wEpID;

	CTpMsg cMsg;

	cMsg.SetEvent(evtp_ViewObj_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfEpId, sizeof(TConfEpID));
	cMsg.CatBody(&wStreenIndex, sizeof(u16));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);	
}

//取消选看
API void umcunview(u16 wConfID, u16 wStreenIndex)
{
	TLogUser tLogUser;
	
	CTpMsg cMsg;
	
	cMsg.SetEvent(evtp_UndoViewObj_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&wConfID, sizeof(u16));
	cMsg.CatBody(&wStreenIndex, sizeof(u16));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);	
}

//开启关闭讨论,非讨论下更新讨论成员
API void umcdis(u16 wConfID, BOOL32 bStart, u16 wOne = 0, u16 wTwo = 0, u16 wThree = 0, u16 wFoure = 0)
{
	TLogUser tLogUser;
	TConfAuxMixInfo tConfMixInfo;
	
	tConfMixInfo.m_wConfID = wConfID;
	tConfMixInfo.m_bStart = bStart;
	
	if (0 != wOne)
	{
		tConfMixInfo.m_atAuxMixList.AddMixID(wOne);
	}

	if (0 != wTwo)
	{
		tConfMixInfo.m_atAuxMixList.AddMixID(wTwo);
	}

	if (0 != wThree)
	{
		tConfMixInfo.m_atAuxMixList.AddMixID(wThree);
	}

	if (0 != wFoure)
	{
		tConfMixInfo.m_atAuxMixList.AddMixID(wFoure);
	}

	CTpMsg cMsg;
	
	cMsg.SetEvent(evtp_StartAuxMix_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tConfMixInfo, sizeof(TConfTurnInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

//讨论下，添加和删除讨论会场
API void umcdisopr(u16 wConfID, u16 wEpId1 = 0, u16 wEpId2 = 0, u16 wEpId3 = 0, u16 wType = 0)
{
	TLogUser tUser;
	TDiscussListOpr tListOpr;
	
	tListOpr.m_wConfId = wConfID;
	if (0 == wType)
	{
		tListOpr.m_emOprType = em_DisListOpr_Add;
	}
	else
	{
		tListOpr.m_emOprType = em_DisListOpr_Del;
	}

	u16 wNum = 0;
	if (0 != wEpId1)
	{
		tListOpr.m_awEpId[wNum] = wEpId1;
		wNum++;
	}
	
	if (0 != wEpId2)
	{
		tListOpr.m_awEpId[wNum] = wEpId2;
		wNum++;
	}

	if (0 != wEpId3)
	{
		tListOpr.m_awEpId[wNum] = wEpId3;
		wNum++;
	}
	

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_UpdateAudMixInfo_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tListOpr, sizeof(tListOpr));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void umcdisvac(u16 wConfId, BOOL32 bVacOn)
{
	TLogUser tUser;
	TConfAuxMixVacOpr tVac;

	tVac.m_wConfID = wConfId;
	tVac.m_bVacOn = bVacOn;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_AuxMixVacSwitch);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tVac, sizeof(tVac));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void umcmixmode(u16 wConfId, u16 wType, u16 wEp1, u16 wEp2, u16 wEp3)
{
	TLogUser tUser;
	TUmsAudMixInfo tCmd;
	
	tCmd.m_wConfId = wConfId;
	if (0 == wType)
	{
		tCmd.m_emMode = em_umsaudmixmode_idle;
	}
	else if (1 == wType)
	{
		tCmd.m_emMode = em_umsaudmixmode_smart;
	}
	else
	{
		tCmd.m_emMode = em_umsaudmixmode_custom;
	}

	tCmd.m_tMixList.AddID(wEp1);
	tCmd.m_tMixList.AddID(wEp2);
	tCmd.m_tMixList.AddID(wEp3);
	
	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ConfAudMixMode_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tCmd, sizeof(tCmd));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void umcmixlist(u16 wConfId, BOOL32 bDel, u16 wEp1, u16 wEp2, u16 wEp3)
{
	TLogUser tUser;
	TUmsAudMixListCmd tCmd;
	
	tCmd.m_wConfId = wConfId;
	tCmd.m_emOpr = bDel?em_umsaudmixlistopr_del:em_umsaudmixlistopr_add;
	tCmd.m_tList.AddID(wEp1);
	tCmd.m_tList.AddID(wEp2);
	tCmd.m_tList.AddID(wEp3);

	CTpMsg cMsg;
	cMsg.SetEvent(evtp_ConfAudMixList_cmd);
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tCmd, sizeof(tCmd));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void showboard()
{
	OspInstDump(AID_UMSSERVER_APP,  1, ums_service_dump_show_board);
}

API void addboard(EMBrdType emBrdType, u8 byBrdLayer, u8 byBrdSlot, s8* pszBrdIp)
{
	TLogUser	tLogUser;
	TTPBrdCfg	tBrdInfo;
	
	tBrdInfo.m_tBrdPos.m_emBrdType = emBrdType;
	tBrdInfo.m_tBrdPos.m_byBrdLayer = byBrdLayer;
	tBrdInfo.m_tBrdPos.m_byBrdSlot = byBrdSlot;
	tBrdInfo.m_tBrdPos.m_dwBrdIP = inet_addr(pszBrdIp);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_cardAdd_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tBrdInfo, sizeof(tBrdInfo));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void delboard(u8 byBrdLayer, u8 byBrdSlot)
{
	TLogUser	tLogUser;
	TTPBrdCfg	tDelBrd;
	tDelBrd.m_tBrdPos.m_byBrdLayer = byBrdLayer;
	tDelBrd.m_tBrdPos.m_byBrdSlot = byBrdSlot;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_cardDel_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tDelBrd, sizeof(tDelBrd));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void modifyboard(u8 byBrdType, u8 byBrdLayer, u8 byBrdSlot, s8* pszIp)
{
	TLogUser	tLogUser;
	TTPBrdCfg	tModifyBrd;

	tModifyBrd.m_tBrdPos.m_byBrdLayer = byBrdLayer;
	tModifyBrd.m_tBrdPos.m_byBrdSlot = byBrdSlot;
	tModifyBrd.m_tBrdPos.m_emBrdType = (EMBrdType)byBrdType;
	tModifyBrd.m_tBrdPos.m_dwBrdIP = inet_addr(pszIp);

	CTpMsg cMsg;
	cMsg.SetEvent(ev_cardModify_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tModifyBrd, sizeof(tModifyBrd));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

// API void addbrdmode(u8 byBrdModeType, u8 byBrdLayer, u8 byBrdSlot, s8* pszModeAlias)
// {
// 	TLogUser tLogUser;
// 	TTPBrdMdlInfo tAddBrdMode;
// 
// 	tAddBrdMode.m_atMdlCfg[0].m_emEqpType = (EMEqpType)byBrdModeType;
// 	if (NULL == pszModeAlias)
// 	{
// 		return;
// 	}
// 	strncpy(tAddBrdMode.m_atMdlCfg[0].m_szEqpAlias, pszModeAlias, sizeof(MAXLEN_EQP_ALIAS));
// 	tAddBrdMode.m_byLayer = byBrdLayer;
// 	tAddBrdMode.m_bySlot = byBrdSlot;
// 
// 	CTpMsg cMsg;
// 	cMsg.SetEvent(ev_cardModeModify_req);
// 	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
// 	cMsg.CatBody(&tAddBrdMode, sizeof(TTPBrdMdlInfo));
// 	cMsg.Post(UMS_SERVICE_APP_INST);
// }

API void delbrdmode(u8 byBrdLayer, u8 byBrdSlot, u8 byNum = 1)
{
	TLogUser tLogUser;
	TTPBrdMdlInfo tDelBrdMode;

	tDelBrdMode.m_byLayer = byBrdLayer;
	tDelBrdMode.m_bySlot = byBrdSlot;
	tDelBrdMode.m_byIndex = byNum;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_cardModeDel_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tDelBrdMode, sizeof(TTPBrdMdlInfo));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void modifybrdmode(u8 byLayer, u8 bySlot, u8 byMdlType, s8* pszMdlAlias1, u8 byNum = 1, u8 bymixNum1 = 0, s8* pszMdlAlias2 = NULL, u8 bymixNum2 = 0)
{
	TLogUser tLogUser;
	TTPBrdMdlInfo tModifyBrdMode;
	

	tModifyBrdMode.m_byIndex = byNum;
	if (1 == byNum)
	{
		tModifyBrdMode.m_atMdlCfg[0].m_emEqpType = (EMEqpType)byMdlType;
		tModifyBrdMode.m_atMdlCfg[0].m_byAudmixNum = bymixNum1;
		if (NULL != pszMdlAlias1)
			strncpy(tModifyBrdMode.m_atMdlCfg[0].m_szEqpAlias, pszMdlAlias1, sizeof(tModifyBrdMode.m_atMdlCfg[0].m_szEqpAlias));
	}
	else if (2 == byNum)
	{
		tModifyBrdMode.m_atMdlCfg[0].m_emEqpType = (EMEqpType)byMdlType;
		tModifyBrdMode.m_atMdlCfg[1].m_emEqpType = (EMEqpType)byMdlType;

		tModifyBrdMode.m_atMdlCfg[0].m_byAudmixNum = bymixNum1;
		tModifyBrdMode.m_atMdlCfg[1].m_byAudmixNum = bymixNum2;

		if (NULL != pszMdlAlias1)
			strncpy(tModifyBrdMode.m_atMdlCfg[0].m_szEqpAlias, pszMdlAlias1, sizeof(tModifyBrdMode.m_atMdlCfg[0].m_szEqpAlias));
		if (NULL != pszMdlAlias2)
			strncpy(tModifyBrdMode.m_atMdlCfg[1].m_szEqpAlias, pszMdlAlias2, sizeof(tModifyBrdMode.m_atMdlCfg[1].m_szEqpAlias));	
	}

	tModifyBrdMode.m_byLayer = byLayer;
	tModifyBrdMode.m_bySlot = bySlot;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_cardModeModify_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tModifyBrdMode, sizeof(TTPBrdMdlInfo));
	cMsg.Post(UMS_SERVICE_APP_INST);
}
// API void showvmpused()
// {
// 	TLogUser tLogUser;
// 	CTpMsg cMsg;
// 	cMsg.SetEvent(ev_card_vmp_used_req);
// 	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
// 	cMsg.Post(UMS_SERVICE_APP_INST);
// }
// API void showbasused()
// {
// 	TLogUser tLogUser;
// 	CTpMsg cMsg;
// 	cMsg.SetEvent(ev_card_bas_used_req);
// 	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
// 	cMsg.Post(UMS_SERVICE_APP_INST);
// }
// API void showeapuused()
// {
// 	TLogUser tLogUser;
// 	CTpMsg cMsg;
// 	cMsg.SetEvent(ev_card_audiomix_used_req);
// 	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
// 	cMsg.Post(UMS_SERVICE_APP_INST);
// }

API void showeqpused()
{
	TLogUser tLogUser;
	EMEqpType emType = em_max_mdl;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_card_eqp_used_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&emType, sizeof(emType));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void showmediaused()
{
	TLogUser tLogUser;
	EMEqpType emType = em_dataswitch_mdl;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_card_eqp_used_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&emType, sizeof(emType));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void brdreboot(u8 byLayer, u8 bySlot)
{
	TLogUser tLogUser;
	TTPBrdPos tPos;
	tPos.m_byBrdLayer = byLayer;
	tPos.m_byBrdSlot = bySlot;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_card_reboot_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tPos, sizeof(TTPBrdPos));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

API void brdupdate(u8 byLayer, u8 bySlot, s8* pszFileName)
{
	TLogUser tLogUser;
	TTPBrdUpGrade tUpdate;
	tUpdate.m_byLayer = byLayer;
	tUpdate.m_bySlot = bySlot;
	strncpy(tUpdate.m_szFileName, pszFileName, sizeof(tUpdate.m_szFileName));
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_card_upgrade_req);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	cMsg.CatBody(&tUpdate, sizeof(TTPBrdUpGrade));
	cMsg.Post(UMS_SERVICE_APP_INST);
}

//umc保存预案
API void saveumcvmp(u16 wConfID)
{	
	TLogUser tLogUser;
	TTpVmpMemberCfg tCfg;
	tCfg.m_wConfID = wConfID;
	tCfg.m_emStyle = tp_VmpStyle_FOUR;
	tCfg.m_wEpNum = 2;
	tCfg.m_atEpList[0].m_tEpAlias.SetAlias("tA3");
	tCfg.m_atEpList[1].m_tEpAlias.SetAlias("tA1");

	CTpMsg cMsg;
	cMsg.SetEvent(ev_UMC_UMS_SaveVmpCfg_Cmd);
 	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
    cMsg.CatBody(&tCfg, sizeof(TTpVmpMemberCfg));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}


//开启关闭点名,非点名下更新讨论成员
API void umcrollcall(u16 wConfID, BOOL32 bStart, u16 wCaller = 0,  u16 wOne = 0, u16 wtwo = 0, u16 wThree = 0, u16 wFour = 0, u16 wFive = 0)
{
	TLogUser tLogUser;
	TConfRollCallInfo tRollCallInfo;
	
	tRollCallInfo.m_wConfID = wConfID;
	tRollCallInfo.m_bStart = bStart;
	
	if (0 != bStart && 0 == wCaller)
	{
		msgprint("Caller = %d  error!\n", wCaller);
		msgprint("use as: umcrollcall  confid  bstart  caller  ep1 -- ep5 \n");
		return;
	}

	tRollCallInfo.m_atRollCallMemList.SetRollCaller(wCaller);

	
	if (0 != wOne)
	{
        tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wOne);
	}

	if (0 != wtwo)
	{
        tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wtwo);
	}

	if (0 != wThree)
	{
        tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wThree);
	}

	if (0 != wFour)
	{
        tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wFour);
	}

	if (0 != wFive)
	{
        tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wFive);
	}
	
	CTpMsg cMsg;
	
	cMsg.SetEvent(evtp_StartRollCall_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tRollCallInfo, sizeof(TConfRollCallInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}


API void umcrollcallnext(u16 wConfID, u16 wCaller = 0, u16 wtarget = 0)
{
	TLogUser tLogUser;
	TRollCallNextEpInfo tRollCallInfo;
	
	tRollCallInfo.m_wConfID = wConfID;

	
	if (0 == wCaller || 0 == wtarget)
	{
		msgprint("Caller = %d or Targe = %d  error!\n", wCaller, wtarget);
		return;
	}
	
	tRollCallInfo.m_wRollCaller = wCaller;
	tRollCallInfo.m_wCallTarget = wtarget;
	
	CTpMsg cMsg;
	
	cMsg.SetEvent(evtp_RollCallNext_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tRollCallInfo, sizeof(TRollCallNextEpInfo));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}


API void umcrollcalladdlist(u16 wConfID, u16 wAdd = 1, u16 wOne = 0, u16 wtwo = 0, u16 wThree = 0, u16 wFour = 0)
{
	TLogUser tLogUser;
	TUpdataRollCallList tRollCallInfo;
	
	tRollCallInfo.m_wConfID = wConfID;

	if (wAdd)
	{
        tRollCallInfo.m_bAdd    = TRUE;
	}
	else 
	{
        tRollCallInfo.m_bAdd    = FALSE;
	}
	
	
	if (0 == wOne && 0 == wtwo && 0 == wThree && 0 == wFour)
	{
		msgprint("no vaild ep \n");
		return;
	}
	
	if (0 != wOne)
	{
		tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wOne);
	}


	if (0 != wtwo)
	{
		tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wtwo);
	}


	if (0 != wThree)
	{
		tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wThree);
	}


	if (0 != wFour)
	{
		tRollCallInfo.m_atRollCallMemList.AddRollCallTarget(wFour);
	}

	
	CTpMsg cMsg;
	
	cMsg.SetEvent(evtp_RollCallUpdateList_cmd);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tRollCallInfo, sizeof(TUpdataRollCallList));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}



API void serverhelp()
{
	msgprintnotime("ver()                           --- 显示UMSServer版本号\n");
	msgprintnotime("showconftemp()                  --- 显示会议模板信息\n");
	msgprintnotime("showregstate()                  --- 显示server侧包的注册状态\n");
	msgprintnotime("showboard()                     --- 显示server侧的单板信息\n");

	msgprintnotime("\n以下命令仅供开发本地调试使用!\n");

	//cms -> ums

	msgprintnotime("setreg(BOOL32 bUsed, s8* pDstIp, u16 wDstPort, u16 wExpire)	--- 设置注册信息\n");
	msgprintnotime("setip(s8* pszIp, s8* pszMask, s8* pszGate)                    --- 设置UMS IP\n");

	msgprintnotime("add(s8* ConfName)                                             --- 添加一个名为ConfName的会议模板\n");
	msgprintnotime("del(u16 id)                                                   --- 删除ID为id的会议模板\n");
	msgprintnotime("startconf(u16 id)                                             --- 开启会议模板ID为id的会议\n");
	msgprintnotime("stopconf(u16 ConfID)                                          ---  结束会议\n");
	msgprintnotime("setgkreg(BOOL32 bUsed, s8* pDstIp, u16 wExpire)               ---  设置GK注册信息\n");
	msgprintnotime("addfulltemp(s8 *confnamebase,s8 *e164namebase)                ---  添加会议模板\n");
	msgprintnotime("saveumcvmp(u16 wConfID)								 		---  保存合成预案\n");
	
    //cmc->ums
	msgprintnotime("reqallreginfo()							-------  查询所有的注册信息\n");
	msgprintnotime("requmsreginfo()							-------	 查询UMS注册信息\n");
	msgprintnotime("reqcnsreginfo()							-------	 查询CNS注册信息\n");
	
	msgprintnotime("setvol(u16 wIndex, u16 wVol, BOOL32 bIsMute)                 ---  设置电视墙通道音量\n");
	msgprintnotime("changemode(u16 wIndex, u16 wMode)                            ---  改变电视墙通道模式\n");
	msgprintnotime("void playhdu(u16 wConfid, u16 wDstep, BOOL32 bVmp, u16 wIndex, u16 wSubIndex = 0)  ---  拖会场上墙\n");

	//->ums
    msgprintnotime("unreg()                                   -------  请求删除注册\n");

	//-tool -> ums
	msgprintnotime("addboard(u8 byBrdType, u8 byBrdLayer, u8 byBrdSlot, s8* pszBrdIp)              ---  添加单板\n");
	msgprintnotime("delboard(u8 byBrdLayer, u8 byBrdSlot)                                          ---  删除单板\n");
	msgprintnotime("modifyboard(u8 byBrdLayer, u8 byBrdSlot, u8 byBrdType, s8* pszBrdIp)           ---  修改单板\n");
	msgprintnotime("delbrdmode(u8 byBrdLayer, u8 byBrdSlot)                                        ---  删除单板模式\n");
	msgprintnotime("modifybrdmode(u8 byLayer, u8 bySlot, u8 byMdlType, s8* pszMdlAlias1, u8 byNum, u8 bymixNum1, s8* pszMdlAlias2, u8 bymixNum2) ---  修改单板模式\n");
	msgprintnotime("brdreboot(u8 byLayer, u8 bySlot)                                               ---  单板重启\n");
	msgprintnotime("brdupdate(u8 byLayer, u8 bySlot, s8* pszFileName)                              ---  单板升级\n");
}


#define  VER_umsserver_ver   UMS_VerID
API void ver()
{
	msgprint("umsserver ver: %s  compile time: %s, %s\n", VER_umsserver_ver, __DATE__,  __TIME__);
}


API void telnetportoff()
{// 通过iptables限制23端口，关闭板卡对外telnet服务
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	system("/usr/bin/telnetportonoff.sh off &");
	g_bMpcTelnetPortOn = FALSE;
#else
	msgprint("This command is not valid!\n");
#endif
}

API void telnetporton()
{// 通过iptables放开23端口，开启板卡对外telnet服务
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	system("/usr/bin/telnetportonoff.sh on &");
	g_bMpcTelnetPortOn = TRUE;
#else
	msgprint("This command is not valid!\n");
#endif
}

//ftp
API void switchftp(u8 byFtpOn)
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	if (byFtpOn)
	{
		BrdEnableFtpd();
		g_bMpcFtpOn = TRUE;
	}
	else 
	{
		BrdDisableFtpd();
		g_bMpcFtpOn = FALSE;
	}
#else
	msgprint("This command is not valid!\n");	
#endif	
}

API BOOL32 checkftp()
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
    STATUS nRet = BrdFtpdStatus();
	if (1 == nRet)
	{
		msgprint("The Ftp status is on, check ret is %d.\n", nRet);
		return TRUE;
	}
	else  
	{
		msgprint("The Ftp status is Off, check ret is %d.\n", nRet);
		return FALSE;
	}
#else
	msgprint("This command is not valid!\n");
	return FALSE;	
#endif	
}

API void showftptel()
{
#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
	msgprint("g_bMpcTelnetPortOn=%d, g_bMpcFtpOn=%d.\n", g_bMpcTelnetPortOn, g_bMpcFtpOn);
#endif
}


API void boardtel(u8 layer, u8 slot, u8 onoff)
{
	TLogUser tLogUser;
	TPBoardSwitch tBoardSwitch;

	tBoardSwitch.m_byLayer = layer;
	tBoardSwitch.m_bySlot = slot;
	tBoardSwitch.m_emType = em_BoardSwitch_telnet;
	tBoardSwitch.m_bSwitch = onoff;

	CTpMsg cMsg;
	cMsg.SetEvent(ev_card_switchtelnetftp_req);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tBoardSwitch, sizeof(tBoardSwitch));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void boardftp(u8 layer, u8 slot, u8 onoff)
{
	TLogUser tLogUser;
	TPBoardSwitch tBoardSwitch;
	
	tBoardSwitch.m_byLayer = layer;
	tBoardSwitch.m_bySlot = slot;
	tBoardSwitch.m_emType = em_BoardSwitch_ftp;
	tBoardSwitch.m_bSwitch = onoff;
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_card_switchtelnetftp_req);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tBoardSwitch, sizeof(tBoardSwitch));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}

API void switchssh(BOOL32 bIson)
{
	TLogUser tLogUser;
	TPBoardSwitch tBoardSwitch;
	tBoardSwitch.m_bSwitch = bIson;
	CTpMsg cMsg;
	cMsg.SetEvent(ev_card_switchtelnetftp_req);
	cMsg.SetBody(&tLogUser, sizeof(TLogUser));
	cMsg.CatBody(&tBoardSwitch, sizeof(tBoardSwitch));
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_UE_APP_INST);
}


void regist_ums_service_commond()
{
#ifdef _LINUX_
	OspRegCommand("ver", (void*)ver, "ver()");
	OspRegCommand("showconftemp", (void*)showconftemp, "showconftemp()");
	OspRegCommand("showallconf", (void*)showallconf, "showallconf()");

	OspRegCommand("serverhelp", (void*)serverhelp, "serverhelp()");
	OspRegCommand("add", (void*)add, "add(s8* , s8* , s8* , s8* )");
	OspRegCommand("startmeet", (void*)startmeet, "startmeet(s8* , s8* , s8* , s8* )");
	OspRegCommand("add128template",(void*)add128template,"add128template");
	OspRegCommand("del", (void*)del, "del(int)");
	
	
	OspRegCommand("delall",(void*)delall, "delall()");
	OspRegCommand("startconf", (void*)startconf, "startconf(int)");
	
	OspRegCommand("addfulltemp", (void*)addfulltemp, "addfulltemp(int)");
	OspRegCommand("setgkreg", (void*)setgkreg, "setgkreg");
	OspRegCommand("unreg", (void*)unreg, "unreg");
	
	OspRegCommand("umcmuteep", (void*)umcmuteep, "umcmuteep");
	OspRegCommand("umcquietep", (void*)umcquietep, "umcquietep");
	OspRegCommand("umcdropep", (void*)umcdropep, "umcdropep");
	OspRegCommand("umccallep", (void*)umccallep, "umccallep");
	OspRegCommand("umcinviteep", (void*)umcinviteep, "umcinviteep");
	OspRegCommand("umcapplyspeaker", (void*)umcapplyspeaker, "umcapplyspeaker");
	OspRegCommand("umcpoll", (void*)umcpoll, "umcpoll");
	OspRegCommand("umcview", (void*)umcview, "umcview");
	OspRegCommand("umcunview", (void*)umcunview, "umcunview");
	OspRegCommand("umcupdatepoll", (void*)umcupdatepoll, "umcupdatepoll");
	OspRegCommand("umcstartdual", (void*)umcstartdual, "umcstartdual");
	OspRegCommand("umcstopdual", (void*)umcstopdual, "umcstopdual");
	OspRegCommand("umcdis", (void*)umcdis, "umcdis");
	
	OspRegCommand("umcfeccep", (void*)umcfeccep, "umcfeccep");

	OspRegCommand("umcdisopr", (void*)umcdisopr, "umcdisopr");
	
	OspRegCommand("setip", (void*)setip, "setip(int)");
	OspRegCommand("setreg", (void*)setreg, "setreg(int)");
	
	OspRegCommand("reqallreginfo", (void*)reqallreginfo, "reqallreginfo");
	OspRegCommand("requmsreginfo", (void*)requmsreginfo, "requmsreginfo");
	OspRegCommand("reqcnsreginfo", (void*)reqcnsreginfo, "reqcnsreginfo");

	OspRegCommand("showregstate", (void*)showregstate, "showregstate");

	//测试维护工具命令


	//单板操作命令
	OspRegCommand("showboard", (void*)showboard, "showboard");
	OspRegCommand("addboard", (void*)addboard, "addboard");
	OspRegCommand("delboard", (void*)delboard, "delboard");
	OspRegCommand("modifyboard", (void*)modifyboard, "modifyboard");
	OspRegCommand("delbrdmode", (void*)delbrdmode, "delbrdmode");
	OspRegCommand("modifybrdmode", (void*)modifybrdmode, "modifybrdmode");
	OspRegCommand("showeqpused", (void*)showeqpused, "showeqpused");
	OspRegCommand("brdreboot", (void*)brdreboot, "brdreboot");
	OspRegCommand("brdupdate", (void*)brdupdate, "brdupdate");
	OspRegCommand("showlicense", (void*)showlicense, "showlicense");
	OspRegCommand("readlicense", (void*)readlicense, "readlicense");
	//电视墙命令
	OspRegCommand("showhdu", (void*)showhdu, "showhdu");
	OspRegCommand("showhdustyle", (void*)showhdustyle, "showhdustyle");	

	OspRegCommand("saveumcvmp", (void*)saveumcvmp, "saveumcvmp");	

	//点名
	OspRegCommand("umcrollcall", (void*)umcrollcall, "umcrollcall");
	OspRegCommand("umcrollcallnext", (void*)umcrollcallnext, "umcrollcallnext");
	OspRegCommand("umcrollcalladdlist", (void*)umcrollcalladdlist, "umcrollcalladdlist");

	//QT
    OspRegCommand("setqt", (void*)setqt, "setqt");
	
	OspRegCommand("setcycle", (void*)setcycle, "setcycle");
	OspRegCommand("StartNtpd", (void*)StartNtpd, "StartNtpd()");


	//ftp
    OspRegCommand("switchftp",   (void*)switchftp,   "switchftp()");
	OspRegCommand("checkftp",    (void*)checkftp,    "checkftp()");
	OspRegCommand("showftptel",    (void*)showftptel,    "showftptel()");


	// telnet iptables rule
	OspRegCommand("telnetporton", (void*)telnetporton, "telnetporton()");
	OspRegCommand("telnetportoff", (void*)telnetportoff, "telnetportoff()");
	
	OspRegCommand("boardtel", (void*)boardtel, "boardtel()");
	OspRegCommand("boardftp", (void*)boardftp, "boardftp()");

	OspRegCommand("switchssh", (void*)switchssh, "switchssh()");
	OspRegCommand("addex",(void*)addex,"addex()");
	OspRegCommand("showmediaused", (void*)showmediaused, "showmediaused");
	OspRegCommand("downloadlog",(void*)downloadlog, "downloadlog()");

#endif
}
