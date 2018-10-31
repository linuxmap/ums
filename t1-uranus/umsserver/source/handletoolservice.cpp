#include "handletoolservice.h"
#include "umsobject.h"
#include "umsserver.h"
#include "handlecallservice.h"
#include "handleconftemplateservice.h"
#include "handlehduservice.h"
#include "handlelicense.h"
#include "umsinnertype.h"
#include "umsconfig.h"


#include "innereventumsserver.h"

// 外部消息
#include "eventoutumstool.h"

extern BOOL32 g_bKedaManuOn;

API void reboot();
CUmsToolHandleService::CUmsToolHandleService( CTpObject* pcObjec )
											: CTpHandler(pcObjec)
{
}

CUmsToolHandleService::~CUmsToolHandleService()
{
	
}

BOOL32 CUmsToolHandleService::Handler( CTpMsg *const ptMsg )
{
	TLogUser tUser;
	TP_SAFE_CAST(tUser, ptMsg->GetBody());

// 	if (!IsToolUser(tUser))
// 	{
// 		//MdlError(Ums_Mdl_Service, ("[CUmsToolHandleService::Handler] Is not tool user.\n"));
// 		return FALSE;
// 	}

	u16 wEvent = ptMsg->GetEvent();
	u8*	pData = ptMsg->GetBody() + sizeof(TLogUser);
	u16 wSize = ptMsg->GetBodyLen() - sizeof(TLogUser);

	switch (wEvent)
	{
	case ev_SysCmsLoginInd:		
		EventLogin();						
		break;

	case ev_sysInfo_req:		
		EventSysInfo();
		break;

	case ev_confCount_req:		
		EventConfCount();
		break;

	case ev_rebootUms_cmd:		
		EventRebootUms();
		break;
		
	case ev_authCount_req:		
		EventAuthCount();
		break;

	case ev_hduCount_req:		
		EventHduCount();
		break;

	case ev_authCount_Nty:
		EventAuthCountNty(wEvent, pData, wSize);
		break;
	case ev_licenseOutput_req:
		EventLicenseOutputReq();
		break;
	}
	
	return TRUE;	
}

void CUmsToolHandleService::EventHduCount()
{
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	TLogUser tLogUser;
	if (NULL == pServer)
	{
		MdlError(Ums_Mdl_Service, ("[EventHduCount] Server instance is NULL.\n"));
		return ;
	}
	CUmsHduHandleService* pHduService = (CUmsHduHandleService*)pServer->GetService(CTpUmsServer::_CUmsHduHandleService);
	if (NULL == pHduService)
	{
		MdlError(Ums_Mdl_Service, ("[EventHduCount] Hdu service is NULL.\n"));
		return ;
	}

	TTPBrdUsedInfo tUseInfo;
	tUseInfo.m_emType = em_hdu_mdl;
	pHduService->GetHduUesInfo(tUseInfo);

	TpNotifyMsgToToolUserFromService(ev_hduCount_Nty, &tUseInfo, sizeof(TTPBrdUsedInfo));
	TpNotifyMsgToUeFromService(ev_hduCount_Nty, &tUseInfo, sizeof(TTPBrdUsedInfo),tLogUser);
	MdlHint(Ums_Mdl_Service, ("[EventHduCount] UseNum:%d, RegNum:%d.\n", tUseInfo.m_wUsedNum, tUseInfo.m_wRegNum));
}

void CUmsToolHandleService::EventAuthCount()
{
	TLogUser tUserTmp;
	tUserTmp.m_dwUserInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_authCount_req);
	cMsg.SetBody(&tUserTmp, sizeof(tUserTmp));
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, UMS_SERVICE_APP_INST);
}

void CUmsToolHandleService::EventAuthCountNty(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{	
	TLogUser tLogUser;
	TpNotifyMsgToUeFromService(wEvent, pDataBuf, wDataSize,tLogUser);
	TpNotifyMsgToToolUserFromService(wEvent, pDataBuf, wDataSize);
}

void CUmsToolHandleService::EventRebootUms()
{
	MdlHint(Ums_Mdl_Service, ("[EventRebootUms] Reboot Ums.\n"));
	//立即保存
	ImmediatelySave();
	reboot();
}

void CUmsToolHandleService::UpdateConfCount()
{
	EventConfCount();
}

void CUmsToolHandleService::EventConfCount()
{
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	TLogUser tLogUser;
	if (NULL == pServer)
	{
		MdlError(Ums_Mdl_Service, ("[EventConfCount] Server instance is NULL.\n"));
		return ;
	}
	CUmsCallHandleService* pCallService = (CUmsCallHandleService*)pServer->GetService(CTpUmsServer::_CUmsCallHandleService);
	if (NULL == pCallService)
	{
		MdlError(Ums_Mdl_Service, ("[EventConfCount] Call service is NULL.\n"));
		return ;
	}

	u32 dwConfCount = pCallService->GetRunningConf();

	TpNotifyMsgToToolUserFromService(ev_confCount_Nty, &dwConfCount, sizeof(u32));
	TpNotifyMsgToUeFromService(ev_confCount_Nty, &dwConfCount, sizeof(u32),tLogUser);
	MdlHint(Ums_Mdl_Service, ("[EventConfCount] Running conf Count:%d.\n", dwConfCount));
}

void CUmsToolHandleService::EventSysInfo()
{
	TToolSysInfo tSysInfo;
	TLogUser tLogUser;
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

	TpNotifyMsgToToolUserFromService(ev_sysInfo_Nty, &tSysInfo, sizeof(TToolSysInfo));
	TpNotifyMsgToUeFromService(ev_sysInfo_Nty,&tSysInfo, sizeof(TToolSysInfo),tLogUser);
	MdlHint(Ums_Mdl_Service, ("[EventSysInfo] CpuRate:%d, MemRate:%d.\n", tSysInfo.m_dwCpuRate, tSysInfo.m_dwMemRate));
}


void CUmsToolHandleService::EventLogin()
{
	CTpUmsServer* pServer = (CTpUmsServer*)GetInstance();
	TUmsVersion tVersion;
	tVersion.SetSoftVersion(pServer->GetSoftVersion());
	tVersion.SetHardVersion(pServer->GetHardVersion());
	tVersion.m_bKedaManu = g_bKedaManuOn;

	TpNotifyMsgToToolUserFromService(ev_verInfo_Nty, &tVersion, sizeof(TUmsVersion));

	EventSysInfo();
	EventConfCount();
	EventAuthCount();
	EventHduCount();
}


void CUmsToolHandleService::EventLicenseOutputReq()
{
	CUmsLicenseService* pService = (CUmsLicenseService*)((CTpUmsServer*)GetInstance())->GetService(CTpUmsServer::_CUmsLicenseService);

	u8 abyMem[sizeof(BOOL32) + 256] = {0};
	BOOL32* pSuc = (BOOL32*)(abyMem);
	if (pService->ProccessLicenseOutputReq((s8*)(abyMem+sizeof(BOOL32)), 255))
	{
		*pSuc = TRUE;
	}
	else
	{
		*pSuc = FALSE;
	}
	TpNotifyMsgToToolUserFromService(ev_licenseOutput_Ind, abyMem, sizeof(abyMem));
}