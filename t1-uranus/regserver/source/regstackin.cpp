#include "regstackin.h"
#include "umsinnerstruct.h"
#include "stackmsgconvert.h"
#include "innereventregsrv.h"
#include "regserver.h"

CRegStackInApp g_cRegSipStackInApp;
SEMHANDLE g_SipSem;

extern TIPCheck g_tIPCheck;
extern u32 g_dwListenIp;

#define UMS_DB_APP_INST	MAKEIID(AID_UMSDB_APP, 1)
void NotifyMsgToDb(u16 wEvent, void* pBuf, u16 wLen, TUmsHandle& tHandle)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	cMsg.CatBody(pBuf, wLen);
	cMsg.Post(UMS_DB_APP_INST);
}


extern void PrintReqInfo(TUmsHandle& tHandle, u16 wMsgType, const void* pBuf, u16 wBufLen);
static s32 RVCALLCONV RegSrvNotifyUMSCtrlMsg(IN RvSipTranscHandle hTransc, u16 msgType, const void* pBuf, u16 nBufLen)
{

	TUmsHandle tHandle;
	tHandle.handPaCall = u32(hTransc);
	
	PrintReqInfo(tHandle, msgType, pBuf, nBufLen);
	
	switch(msgType)
	{
	case h_ums_registrationcmd:
		{
			RegisterRequest* pRegInfo = (RegisterRequest*)pBuf;
			TCnsRegInfo tReg;
			
			if (!ConvertRegFromStackToApp(*pRegInfo, tReg))
			{
				OspPrintf(TRUE, FALSE, "Reg Failed!\n");
				return 0;
			}
			
			//ipD¡ê?¨¦ 2?o?¡¤¡§?¨°?¨¹??
			for (u16 wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; wIndex ++)
			{
				if ( tReg.m_tCsnNodeInfo.m_atCalledAddr[wIndex].GetIP() == 0 )
				{
					continue;
				}
				if ( !g_tIPCheck.IsExistIp(tReg.m_tCsnNodeInfo.m_atCalledAddr[wIndex].GetIP()) )
				{
					OspPrintf(TRUE, FALSE, "[RegSrvNotifyUMSCtrlMsg] reg IP:"TPIPFORMAT" no exist, CheckFail!\n", u32ToIP(tReg.m_tCsnNodeInfo.m_atCalledAddr[wIndex].GetIP()));			
					u8 abyBufReson[sizeof(EmRegisterReason)+sizeof(RegisterResponse)];
					EmRegisterReason* pReason = (EmRegisterReason*)abyBufReson;
					RegisterResponse* pReasonInfo = (RegisterResponse*)(abyBufReson+sizeof(EmRegisterReason));
					
					*pReason = emRegFail;
					pReasonInfo->m_tContactAddr.m_dwIP = tReg.m_tCsnNodeInfo.m_atCalledAddr[wIndex].GetIP();
					pReasonInfo->m_tContactAddr.m_wPort = tReg.m_tCsnNodeInfo.m_atCalledAddr[wIndex].GetPort();
					
					CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(tHandle.handPaCall), h_ums_registrationind, abyBufReson, sizeof(abyBufReson));
					return 0;
				}
			}

			NotifyMsgToDb(evtp_ums_reg_req, &tReg, sizeof(tReg), tHandle);
		}
		break;
	case h_ums_unregistrationcmd:
		{
			RegisterRequest* pRegInfo = (RegisterRequest*)pBuf;
			TCnsRegInfo tUnReg;
			
			if (!ConvertRegFromStackToApp(*pRegInfo, tUnReg))
			{
				OspPrintf(TRUE, FALSE, "UnReg Failed!\n");
				return 0;
			}
			
			NotifyMsgToDb(evtp_ums_unreg_req, &tUnReg, sizeof(tUnReg), tHandle);
		}
		break;
	case h_ums_query:
		{
			// edit by gaoyong ¡Àe??2¨¦?¡¥¡ê?164o?2¨¦?¡¥¡ê?
			TSipRedirectInfo* tSipInfo = (TSipRedirectInfo*)pBuf;
			TTPAlias tAlias;

			ConverUmsQueryInfoFromStackToApp(*tSipInfo, tAlias);			
			
			NotifyMsgToDb(evtp_ums_arq_req, &tAlias, sizeof(tAlias), tHandle);	
		}
		break;

	case h_ums_getregreq:		
		{
			NotifyMsgToDb(evtp_ums_reg_info_req, (void*)pBuf, nBufLen, tHandle);
		}
		break;
	default:
		break;
	}
	return 0;
}



CRegStackIn::CRegStackIn()
{
}
CRegStackIn::~CRegStackIn()
{

}

BOOL CRegStackIn::InitAdapter( u32 wParam,u32 lParam )
{

	TSipAdapterCfg tCfg;
	tCfg.m_bIfRegister = TRUE;
	tCfg.m_dwLocalIP = lParam;
	tCfg.m_dwMaxCalls = 10;
	tCfg.m_wLocalTcpPort = 5060;
	tCfg.m_wLocalUdpPort = 5060;
	
	memset( tCfg.m_achProduct , 0 , sizeof(tCfg.m_achProduct) );
	memset( tCfg.m_achTerVer , 0 , sizeof(tCfg.m_achTerVer) );
	memcpy( tCfg.m_achProduct , "TPRegSrv" , strlen("TPRegSrv") );
	memcpy( tCfg.m_achTerVer , "V1.1.1.0.0" , strlen("V1.1.1.0.0") );


	if( CSipInterface::AdapterInit( tCfg ) != RV_OK )
	{
		msgprint("AdapterInit error!!!!\n\n");
		ObjError(( "init sip stack failed!\n"));
		return 0;
	}
	
	SIPEVENT sipevent= { 0, 0, 0, 0, 0, 0, RegSrvNotifyUMSCtrlMsg };

	CSipInterface::SetAppCallBack( &sipevent );
	return TRUE;
}

BOOL CRegStackIn::ObjectInit( u32 wParam,u32 lParam )
{	

	BOOL bInit = InitAdapter( wParam , g_dwListenIp );

	bInit = OspSemBCreate(&g_SipSem);
	if ( !bInit )
	{
		ObjError(("[SipStackIn]! ObjectInit: stack init failed!\n"));
	}
	else
	{
		RunSipStack();
	}
	
	return bInit;
}

void CRegStackIn::RunSipStack()
{
	m_bRun = TRUE;
	while ( m_bRun )
	{
		if(!OspSemTake( g_SipSem ))
		{
			OspPrintf( TRUE , FALSE , "OspSemTake ERROR!\n");
			continue;
		}

		CSipInterface::CheckMessage( 100 );

		if(!OspSemGive( g_SipSem ))
		{
			OspPrintf( TRUE , FALSE , "OspSemGive ERROR!\n");
			continue;
		}
		OspDelay(30);
	}

	CSipInterface::AdapterQuit();
	msgprint("[CRegStackIn][Note] ObjectInit: Exit\n" );
}

API BOOL StartupRegStackInApp()
{
	g_cRegSipStackInApp.CreateApp( "REGSIPIN" ,AID_REGSIPSTACKIN_APP ,80,50 ,200*1024);
	
    CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( MAKEIID(AID_REGSIPSTACKIN_APP,1) );

	return TRUE;
}


API void StopSipStackInApp()
{
	g_cRegSipStackInApp.Quit();

	OspSemTake( g_SipSem );
	OspSemGive( g_SipSem );

	CSipInterface::AdapterQuit();	
}

API void reqcnsinfo()
{
	RvSipTranscHandle handle = NULL;
	u8 abyBuf[sizeof(s32)+sizeof(EmGetRegInfoType)];
	s32* pnAppId = (s32*)abyBuf;
	*pnAppId = 10000;
	EmGetRegInfoType* ptVal = (EmGetRegInfoType*)(abyBuf + sizeof(32));
	*ptVal = emGetRegInfoType_CNS;
	
	RegSrvNotifyUMSCtrlMsg(handle, h_ums_getregreq, abyBuf, sizeof(abyBuf));
}

API void requmsinfo()
{
	RvSipTranscHandle handle = NULL;
	u8 abyBuf[sizeof(s32)+sizeof(EmGetRegInfoType)];
	s32* pnAppId = (s32*)abyBuf;
	*pnAppId = 10000;
	EmGetRegInfoType* ptVal = (EmGetRegInfoType*)(abyBuf + sizeof(32));
	*ptVal = emGetRegInfoType_UMS;
	
	RegSrvNotifyUMSCtrlMsg(handle, h_ums_getregreq, abyBuf, sizeof(abyBuf));
}

API void reqallinfo()
{
	RvSipTranscHandle handle = NULL;
	u8 abyBuf[sizeof(s32)+sizeof(EmGetRegInfoType)];
	s32* pnAppId = (s32*)abyBuf;
	*pnAppId = 10000;
	EmGetRegInfoType* ptVal = (EmGetRegInfoType*)(abyBuf + sizeof(32));
	*ptVal = emGetRegInfoType_ALL;
	
	RegSrvNotifyUMSCtrlMsg(handle, h_ums_getregreq, abyBuf, sizeof(abyBuf));
}

API void tregs(u16 wNum, s8* szName, EmSipEndpointType type)
{
	static int sn = 0;
	char paIID[128] = {0};
	
	RvSipTranscHandle handle = NULL;
	RegisterRequest tReg;
	tReg.m_tLocalInfo.m_emEndpointType = type;

	u16 wTotalPack = 0;
	if (wNum % 64 == 0)
	{
		wTotalPack = wNum / 64;
	}
	else
	{
		wTotalPack = wNum / 64 + 1;
	}

	s8 szAlias[128] = {0};
	u16 wIn = 0;
	for (u16 wIndex = 0; wIndex < wTotalPack; ++wIndex) 
	{
		sprintf(paIID, "%s-%d-%d-%d", szName, wNum, type, wIndex);
		strncpy(tReg.m_achCallId, paIID, sizeof(tReg.m_achCallId));

		wIn = 0;
		tReg.m_nSipRegArraySize = 0;

		for (u16 wAliasIndex = wIndex*64; ; ++wAliasIndex)
		{
			if (tReg.m_nSipRegArraySize == 64 || wAliasIndex == wNum) 
			{
				break;
			}

			tReg.m_atSipRegName[wIn].m_emSipAddrType = emUrlAlias;
			sprintf(szAlias, "%s-%d", szName, wAliasIndex);
			strncpy(tReg.m_atSipRegName[wIn].m_achUserName, szAlias, sizeof(tReg.m_atSipRegName[wIn].m_achUserName));
			++(tReg.m_nSipRegArraySize);

			tReg.m_dwExpires = 100000000;
			tReg.m_nCSqence = ++sn;
			tReg.m_atContactAddr[0].m_dwIP = inet_addr("127.0.0.1");
			tReg.m_atContactAddr[0].m_wPort = 5009;

			++wIn;
		}

		RegSrvNotifyUMSCtrlMsg(handle, h_ums_registrationcmd, &tReg, sizeof(tReg));
	}
 }


API void treg(s8* pCallID, s8* pszAlias, s8* pszIp, u16 wPort, u32 dwTimeOut)
{
	static int sn = 0;
	RvSipTranscHandle handle = NULL;
	RegisterRequest tReg;

	tReg.m_nSipRegArraySize = 1;
	tReg.m_atSipRegName[0].m_emSipAddrType = emUrlAlias;
	strncpy(tReg.m_atSipRegName[0].m_achUserName, pszAlias, sizeof(tReg.m_atSipRegName[0].m_achUserName));
	strncpy(tReg.m_achCallId, pCallID, sizeof(tReg.m_achCallId));
	
	tReg.m_dwExpires = dwTimeOut;
	tReg.m_nCSqence = ++sn;

	tReg.m_atContactAddr[0].m_dwIP = inet_addr(pszIp);
	tReg.m_atContactAddr[0].m_wPort = wPort;

	RegSrvNotifyUMSCtrlMsg(handle, h_ums_registrationcmd, &tReg, sizeof(tReg));
}

API void tunreg(s8* pCallID)
{
	RvSipTranscHandle handle = NULL;
	RegisterRequest tReg;
	
	strncpy(tReg.m_achCallId, pCallID, sizeof(tReg.m_achCallId));
		
	RegSrvNotifyUMSCtrlMsg(handle, h_ums_unregistrationcmd, &tReg, sizeof(tReg));
}


API void tarq(s8* pAlias, u8 type)
{
	RvSipTranscHandle handle = NULL;

	TSipRedirectInfo tSipInfo;

	if (1 == type)
	{
		tSipInfo.m_emType = emcat_alias;
	}
	else if (2 == type)
	{
		tSipInfo.m_emType = emcat_e164;
	}
	else if (3 == type)
	{
		tSipInfo.m_emType = emcat_ip;
	}
	else
	{
		tSipInfo.m_emType = emcat_err;
	}
	
	memcpy(tSipInfo.m_achBuf, pAlias, strlen(pAlias));
	tSipInfo.m_achBuf[LEN_ALIAS] = '\0';
	
	RegSrvNotifyUMSCtrlMsg(handle, h_ums_query, &tSipInfo, sizeof(tSipInfo));
}


API void setlistenip(s8* pszIp)
{
    g_dwListenIp = inet_addr(pszIp);;
}

API void showlistenip(void)
{
	OspPrintf(TRUE, FALSE, "listen ip:"IPFORMAT".\n", u32ToIP(g_dwListenIp));
}

void regist_tpreg_test_commond()
{
#ifdef _LINUX_
	OspRegCommand("treg", (void*)treg, "API void treg()");
	OspRegCommand("tunreg", (void*)tunreg, "API void tunreg()");
	OspRegCommand("tarq", (void*)tarq, "API void tarq()");
#endif // _LINUX_
}



