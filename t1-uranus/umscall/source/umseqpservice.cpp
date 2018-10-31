#include "umsobject.h"
#include "tplog.h"
#include "innereventumscall.h"
#include "umseqpservice.h"
#include "umsconfinst.h"
#include "vmpserviecehandler.h"
#include "innereventumsvmp.h"
#include "umsxmpinterface.h"
#include "umsvmp.h"
#include "umsnetportmgr.h"
#include "innereventxmpuvmp.h"

//////////////////////////////////////////////////////////////////////////
CBaseService::CBaseService()
{
	Clear();
}

CBaseService::~CBaseService()
{

}

void CBaseService::Init(const TServiceReg& tInfo)
{
	m_emType = tInfo.m_tBaseInfo.m_emType;
	m_wServiceID = tInfo.m_tBaseInfo.m_wServiceID;
	m_wEqpStartPort = tInfo.m_wEqpStartPort;
	m_dwEqpIP = tInfo.m_dwEqpIP;
	m_wUmsStartPort = tInfo.m_wUmsStartPort;
	//m_dwLocalIP = tInfo.m_dwLocalIP;
	//m_dwMediaNode = tInfo.m_dwMediaNode;
}

void CBaseService::Clear()
{
	m_emType = em_unknow_service;
	m_wServiceID = 0;
	m_wEqpStartPort = 0;
	m_dwEqpIP = 0;
	m_wUmsStartPort = 0;
	m_dwMediaIP = 0;
	m_dwMediaNode = 0;
}

BOOL32 CBaseService::operator ==(const CBaseService& cInfo) const
{
	return	m_emType == cInfo.GetType() && m_wServiceID == cInfo.GetServiceID();
}

//////////////////////////////////////////////////////////////////////////
CServiceInfo::CServiceInfo()
{
	m_emStatus = em_Idle;
	m_cbFun = NULL;
	m_param = NULL;
	m_bOnLine = FALSE;
	m_tStyleInfo.Clear();
	m_tEncParam.Clear();
	memset(m_atDecMiddleRtpAddr, 0, sizeof(m_atDecMiddleRtpAddr));
	memset(m_atDecRtpAddr, 0, sizeof(m_atDecRtpAddr));
	memset(m_atDecRtcpAddr, 0, sizeof(m_atDecRtcpAddr));
	m_tEncRtpAddr.Clear();
	m_tEncRtcpAddr.Clear();
	m_tEncMiddleRtcpAddr.Clear();
	m_cToMpuDsInfo.Clear();
}

CServiceInfo::~CServiceInfo()
{
	if (!IdleStatus())
	{
		RunCBFun(em_Normal_Op, em_Res_Success);
	}
}

BOOL32 CServiceInfo::Assign(ServiceCB cbFun, void* param)
{
	if (NULL == cbFun)
	{
		MdlError(Ums_Mdl_Call, ("CServiceInfo::Assign Invalid param.\n"));
		return FALSE;
	}

	if (!IdleStatus())
	{
		MdlError(Ums_Mdl_Call, ("CServiceInfo::Assign Service is not idle.\n"));
		return FALSE;
	}

	m_emStatus = em_Assigned;
	m_cbFun = cbFun;
	m_param = param;
	
	SetMediaIP(((CUmsConfInst*)m_param)->GetConfEqpDs().m_dwEqpIp);
	SetMediaNode(((CUmsConfInst*)m_param)->GetConfEqpDs().m_dwEqpNode);

	//将合成板 挂载到 会议转发板
	TSndDsAddr tSndAddr;
	tSndAddr.m_wServiceID	= GetServiceID();
	tSndAddr.m_dwMediaIP	= GetMediaIP();
	tSndAddr.m_wStartPort	= GetUmsStartPort();
	CTpMsg cMsg;
	cMsg.SetEvent(ev_vmp_ChangeDsIP_Req);
	cMsg.SetBody(&tSndAddr, sizeof(tSndAddr));
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, ((CUmsConfInst*)m_param)->GetInsID()));
	return TRUE;
}

void CServiceInfo::Stop()
{
// 	if (IdleState())
// 	{
// 		MdlHint(Ums_Mdl_Call, ("CServiceInfo::Stop Service is allready Idle.\n"));
// 		return ;
// 	}

	m_emStatus = em_Idle;
	m_cbFun = NULL;
	m_bOnLine = FALSE;
	m_tStyleInfo.Clear();
	m_tEncParam.Clear();
	memset(m_atDecMiddleRtpAddr, 0, sizeof(m_atDecMiddleRtpAddr));
	memset(m_atDecRtpAddr, 0, sizeof(m_atDecRtpAddr));
	memset(m_atDecRtcpAddr, 0, sizeof(m_atDecRtcpAddr));
	m_tEncRtpAddr.Clear();
	m_tEncRtcpAddr.Clear();
	m_tEncMiddleRtcpAddr.Clear();

	if (m_cToMpuDsInfo.GetElementNum() != 0)
	{
		CNetPortMgr::FreeMediaTrans((CUmsConfInst*)m_param, m_cToMpuDsInfo);
	}
	m_param = NULL;

	m_cToMpuDsInfo.Clear();

}

void CServiceInfo::RunCBFun(const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wTmp1)
{
	if (NULL != m_cbFun)
	{
		m_cbFun(this, emOpType, emRes, m_param, wTmp1);
	}
}

void CServiceInfo::Show()
{
	msgprintnotime("ServiceID:%d.\n", GetServiceID());
	msgprintnotime("  Eqp Type:%d, Eqp Style:%d, Mode:%d, Num:%d.\n", GetType(),m_tStyleInfo.m_emVmpStyle, m_tStyleInfo.m_emShowMode, m_tStyleInfo.m_byMemberNum);
	msgprintnotime("  Eqp EncType:%d, Hp/Bp:%d, FrameRate:%d, BitRate:%d, W:%d, H:%d.\n", m_tEncParam.m_byEncType, m_tEncParam.m_byProfileType,
		m_tEncParam.m_byFrameRate, m_tEncParam.m_wBitRate, m_tEncParam.m_wVideoWidth, m_tEncParam.m_wVideoHeight);
	msgprintnotime("  Xmpu m_bOnline:%d, DsNum:%d.\n", m_bOnLine, m_cToMpuDsInfo.GetElementNum());
	for (u16 wIndex = 0; wIndex < m_tStyleInfo.m_byMemberNum; wIndex++)
	{
		msgprintnotime("  [%d] Dec Rtp:%d, MidRtp:%d, Rtcp:%d.\n", wIndex, 
			m_atDecRtpAddr[wIndex].GetPort(), m_atDecMiddleRtpAddr->GetPort(), m_atDecRtcpAddr[wIndex].GetPort());
	}
	msgprintnotime("  Enc Rtp:%d, Rtcp:%d, MiddleRtcp:%d.\n",  
		m_tEncRtpAddr.GetPort(), m_tEncRtcpAddr.GetPort(), m_tEncMiddleRtcpAddr.GetPort());
	msgprintnotime("\n");

	return;
}

BOOL32 CServiceInfo::AssignXmpu( ServiceCB cbFun, void* param )
{
	CUmsConfInst* pcInst = (CUmsConfInst*)param;

	if (NULL == cbFun)
	{
		MdlError(Ums_Mdl_Call, ("CServiceInfo::AssignXmpu Invalid param.\n"));
		return FALSE;
	}

	if (!IdleStatus())
	{
		MdlError(Ums_Mdl_Call, ("CServiceInfo::AssignXmpu Service is not idle.\n"));
		return FALSE;
	}

	TXmpuVmpParam tVmpParam;
	TXmpuEqpRes tRes;
	tRes.m_dwEqpID = GetServiceID();

	tVmpParam.m_ptEqp = &tRes;
	tVmpParam.m_emEqpType = em_XmpuVmp_Eqp;
	tVmpParam.m_wConfID = pcInst->GetInsID();
	tVmpParam.m_dwMediaIp =  pcInst->GetConfEqpDs().m_dwEqpIp;
	tVmpParam.m_emVmpTpStyle = em_ums_vmp_ten_pic;
	tVmpParam.m_byOutMemBerNum = 1;
	u16 wMaxHp = TP_INVALID_INDEX;
	u16 wMaxBp = TP_INVALID_INDEX;
	CTpTypeAdpt::GetConfBaseMaxCap(pcInst->GetConfBase(), wMaxHp, wMaxBp);
	if (TP_INVALID_INDEX != wMaxHp)
	{
		tVmpParam.m_atVMPOutMember[0]= pcInst->GetConfBase().m_atTpMainVideoRes[wMaxHp];
	}
	else
	{
		tVmpParam.m_atVMPOutMember[0] = pcInst->GetConfBase().m_atTpMainVideoRes[wMaxBp];
	}

	tVmpParam.m_atVMPMember[0].m_tEncrypt =pcInst->GetConfBase().m_tEncrypt;
#ifdef _USE_XMPUEQP_
	if ( !AssignXmpuEqp(&tVmpParam) )
	{
		MdlError(Ums_Mdl_Call, ("CServiceInfo::AssignXmpu. AssignEqpEx Failed! ConfID:%d, EqpID:%d\n", pcInst->GetInsID(), GetServiceID()));
		return FALSE;
	}
	// 占用mpu2-tp  通知vmp模块刷新合成器
	CUmsConfInst::m_tXmpuVmpManger.TaskVmp(tRes.m_dwEqpID, FALSE);
	CUmsVmp::FlushXmpuVmp();
#endif

	memcpy(m_atDecMiddleRtpAddr, tVmpParam.m_atDecMiddleRtpAddr, sizeof(m_atDecMiddleRtpAddr));
	memcpy(m_atDecRtcpAddr, tVmpParam.m_atDecRtcpAddr, sizeof(m_atDecRtcpAddr));
	memcpy(&m_tEncRtpAddr, tVmpParam.m_atEncRtpAddr, sizeof(m_tEncRtpAddr));
	memcpy(&m_tEncMiddleRtcpAddr, tVmpParam.m_atEncMiddleRtcpAddr, sizeof(m_tEncMiddleRtcpAddr));

	m_emStatus = em_Assigned;
	m_cbFun = cbFun;
	m_param = param;

	SetMediaIP(pcInst->GetConfEqpDs().m_dwEqpIp);
	SetMediaNode(pcInst->GetConfEqpDs().m_dwEqpNode);

	return TRUE;
}

void CServiceInfo::ReleaseMpu2()
{
	TXmpuVmpParam tVmpParam;
	TXmpuEqpRes tRes;
	tRes.m_dwEqpID = GetServiceID();
	tVmpParam.m_ptEqp = &tRes;
	tVmpParam.m_emEqpType = em_XmpuVmp_Eqp;
#ifdef _USE_XMPUEQP_
	if ( !ReleaseXmpuEqp(&tVmpParam) )
	{
		MdlError(Ums_Mdl_Call, ("CServiceInfo::ReleaseXmpu. ReleaseEqpEx Failed! EqpID:%d\n", GetServiceID()));
	}
	// 释放mpu2 通知vmp模块刷新合成器
	CUmsConfInst::m_tXmpuVmpManger.ReleaseVmp(tRes.m_dwEqpID);
	CUmsVmp::FlushXmpuVmp();
#endif
	Stop();

}

void CServiceInfo::GetDecAddr( TServiceAddr& tAddr ,u16 wChanIndex)
{
	tAddr.m_tAddr.m_tRtpAddr.m_wPort = m_atDecMiddleRtpAddr[wChanIndex].GetPort();
	tAddr.m_tAddr.m_tRtpAddr.m_dwIP = m_atDecMiddleRtpAddr[wChanIndex].GetIP();

	//ums主控的rtcp接收
	tAddr.m_tAddr.m_tBackRtcpAddr.m_wPort = m_atDecRtcpAddr[wChanIndex].GetPort();
	tAddr.m_tAddr.m_tBackRtcpAddr.m_dwIP = m_atDecRtcpAddr[wChanIndex].GetIP();

	tAddr.m_dwMediaNode = GetMediaNode();
}

void CServiceInfo::GetEncAddr( TServiceAddr& tAddr )
{
	tAddr.m_dwMediaNode = GetMediaNode();

	tAddr.m_tAddr.m_tRtpAddr.m_wPort = m_tEncRtpAddr.GetPort();
	tAddr.m_tAddr.m_tRtpAddr.m_dwIP = m_tEncRtpAddr.GetIP();

	tAddr.m_tAddr.m_tBackRtcpAddr.m_wPort = m_tEncMiddleRtcpAddr.GetPort();
	tAddr.m_tAddr.m_tBackRtcpAddr.m_dwIP = m_tEncMiddleRtcpAddr.GetIP();
}

void CServiceInfo::SetXmpuVmpTPOnline( TXmpuVmpMdyInfo tInfo )
{
	memcpy(&m_atDecRtpAddr, tInfo.m_atDecRtpAddr, sizeof(m_atDecRtpAddr));
	memcpy(&m_tEncRtcpAddr, tInfo.m_atEncRtcpAddr, sizeof(m_tEncRtcpAddr));

	m_bOnLine = TRUE;

	if (0 != m_tEncParam.m_wBitRate)
	{
		CUmsConfInst* pcInst = (CUmsConfInst*)m_param;
		TVmpStartInfo tParam;
		tParam.m_tVmpParam.m_tEncParam = m_tEncParam;
		tParam.m_tVmpParam.m_tStyleInfo = m_tStyleInfo;
		tParam.m_tVmpParam.m_tEncrypt = pcInst->GetConfEncryptInfo();
		tParam.m_wServiceID = GetServiceID();

		CTpMsg cMsg;
		cMsg.SetEvent(evXmpu_StartMpu2_Req);
		cMsg.SetBody(&tParam, sizeof(tParam));
		cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, 0));
	}
}


//////////////////////////////////////////////////////////////////////////
CEqpService& CEqpService::Instance()
{
	static CEqpService cEqpService;
	return cEqpService;
}

CEqpService::CEqpService()
{

}

CEqpService::~CEqpService()
{

}

const CBaseService* CEqpService::Assign(const EmServiceType emType, ServiceCB cbFun, void* param)
{
	if (em_unknow_service == emType || NULL == cbFun)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::Assign Invalid param. Type:%d.\n", emType));
		return NULL;
	}

	CBaseService* ptService = NULL;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && m_acInfo[wIndex].IdleStatus())
		{
			if (m_acInfo[wIndex].Assign(cbFun, param))
			{
				ptService = &(m_acInfo[wIndex]);
				break;
			}
		}
	}

	MdlHint(Ums_Mdl_Call, ("CEqpService::Assign type:%d, service:%d.\n", emType, ptService));
	return ptService;
}

void CEqpService::Release(const CBaseService* pcService, const EmServiceType emType)
{
	if (NULL == pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::Release Invalid param.\n"));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CEqpService::Release type:%d, service:%d.\n", emType, pcService));

	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (pcService->GetServiceID() == m_acInfo[wIndex].GetServiceID() && !m_acInfo[wIndex].IdleStatus())
		{
			m_acInfo[wIndex].Stop();
			break;
		}
	}
}

// void CEqpService::Release(const EmServiceType emType, const u16 wServiceID)
// {
// 	CServiceInfo* pcService = Find(emType, wServiceID);
// 	if (NULL == pcService)
// 	{
// 		MdlError(Ums_Mdl_Call, ("CEqpService::Release Can not find the service. Type:%d, EpID:%d.\n",
// 								emType, wServiceID));
// 		return ;
// 	}
// 	else
// 	{
// 		Release(pcService);
// 	}
// }

void CEqpService::OperateRet(const EmServiceType emType, const u16 wServiceID, 
								const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wTmp1)
{
	CServiceInfo* pcService = Find(emType, wServiceID);
	if (NULL == pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::OperateFailed Can not find the service. Type:%d, EpID:%d.\n",
								emType, wServiceID));
		return ;
	}
	else
	{
		if (pcService->IdleStatus())
		{
			MdlError(Ums_Mdl_Call, ("CEqpService::OperateFailed Service is idle.\n"));
			return ;
		}

		pcService->RunCBFun(emOpType, emRes, wTmp1);
	}
}

u16 CEqpService::GetTotalNum(const EmServiceType emType) const
{
	u16 wNum = 0;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType())
		{
			++wNum;
		}
	}

	return wNum;
}

u16 CEqpService::GetWorkingNum(const EmServiceType emType) const
{
	u16 wNum = 0;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && m_acInfo[wIndex].GetStatus() == em_Working)
		{
			++wNum;
		}
	}
	
	return wNum;
}

u16 CEqpService::GetIdleNum(const EmServiceType emType) const
{
	u16 wNum = 0;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && m_acInfo[wIndex].GetStatus() == em_Idle)
		{
			++wNum;
		}
	}
	
	return wNum;
}

BOOL32 CEqpService::Handler(CTpMsg* const pcMsg)
{
	switch (pcMsg->GetEvent())
	{
	case evtp_EqpService_Reg:
		{
			EventReg(pcMsg);
		}
		break;

	case evtp_EqpService_UnReg:
		{
			EventUnReg(pcMsg);
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

void CEqpService::EventReg(CTpMsg* const pcMsg)
{
	TServiceReg tRegInfo;
	TP_SAFE_CAST(tRegInfo, pcMsg->GetBody());
	
	MdlHint(Ums_Mdl_Call, ("CEqpService::EventReg EqpID:%d, Type:%d.\n", tRegInfo.m_tBaseInfo.m_wServiceID,
							tRegInfo.m_tBaseInfo.m_emType));

	if (tRegInfo.m_tBaseInfo.Invalid())
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::EventReg Invalid service.\n"));
		return ;
	}

	CServiceInfo* pcService = FindIdle();
	if (NULL == pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::EventReg Service is full.\n"));
		return ;
	}

	pcService->Init(tRegInfo);
}

void CEqpService::EventUnReg(CTpMsg* const pcMsg)
{
	TServiceBaseInfo tBaseInfo;
	TP_SAFE_CAST(tBaseInfo, pcMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("CEqpService::EventUnReg ServiceID:%d, Type:%d.\n", tBaseInfo.m_wServiceID, tBaseInfo.m_emType));

	if (tBaseInfo.Invalid())
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::EventUnReg Invalid service.\n"));
		return ;
	}

	CServiceInfo* pcService = Find(tBaseInfo.m_emType, tBaseInfo.m_wServiceID);
	if (NULL == pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::EventUnReg Can not find the service.\n"));
		return ;
	}

	if (!pcService->IdleStatus())
	{
		pcService->RunCBFun(em_Normal_Op, em_Service_No_Reg);
		pcService->Stop();
	}

	pcService->Clear();
}

CServiceInfo* CEqpService::FindIdle()
{
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (m_acInfo[wIndex].Invalid())
		{
			return &(m_acInfo[wIndex]);
		}
	}

	return NULL;
}

CServiceInfo* CEqpService::Find(const EmServiceType emType, const u16 wServiceID)
{
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && wServiceID == m_acInfo[wIndex].GetServiceID())
		{
			return &(m_acInfo[wIndex]);
		}
	}

	return NULL;
}

void CEqpService::Show()
{
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (em_mpu2tp_service == m_acInfo[wIndex].GetType())
		{
			CUmsConfInst::GetVmpServiceHandle()->Show((CBaseService*)(&m_acInfo[wIndex]));
			m_acInfo[wIndex].Show();
		}
	}
}

BOOL32 CEqpService::SetWorking( const EmServiceType emType, const u16 wServiceID )
{
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && wServiceID == m_acInfo[wIndex].GetServiceID())
		{
			m_acInfo[wIndex].SetStatus(em_Working);
			return TRUE;
		}
	}
	return FALSE;
}

void CEqpService::SetError( const EmServiceType emType, const u16 wServiceID )
{
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && wServiceID == m_acInfo[wIndex].GetServiceID())
		{
			m_acInfo[wIndex].SetStatus(em_Error);
			break;
		}
	}
	return;
}

void CEqpService::SaveInfo(const EmServiceType emType, const u16 wServiceID, TVmpStyleInfo& tInfo, TVmpEncParam& tParam)
{
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && wServiceID == m_acInfo[wIndex].GetServiceID())
		{
			m_acInfo[wIndex].SaveInfo(tInfo, tParam);
			break;
		}
	}
	return;
}

BOOL32 CEqpService::IsSameInfo(const EmServiceType emType, const u16 wServiceID, TVmpStyleInfo& tInfo, TVmpEncParam& tParam)
{
	BOOL32 bRet = FALSE;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && wServiceID == m_acInfo[wIndex].GetServiceID())
		{
			bRet = m_acInfo[wIndex].IsSameInfo(tInfo, tParam);
			if (!bRet)
			{
				m_acInfo[wIndex].SaveInfo(tInfo, tParam);
			}
			break;
		}
	}
	return bRet;
}

const CBaseService* CEqpService::AssignXmpuMpu2( const EmServiceType emType, ServiceCB cbFun, void* param )
{
	if (em_unknow_service == emType || NULL == cbFun)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::Assign Invalid param. Type:%d.\n", emType));
		return NULL;
	}

	CBaseService* ptService = NULL;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (emType == m_acInfo[wIndex].GetType() && m_acInfo[wIndex].IdleStatus())
		{
			if (m_acInfo[wIndex].AssignXmpu(cbFun, param))
			{
				ptService = &(m_acInfo[wIndex]);
				break;
			}
		}
	}

	MdlHint(Ums_Mdl_Call, ("CEqpService::AssignXmpuMpu2 type:%d, service:%d.\n", emType, ptService));
	return ptService;
}

void CEqpService::FlushXmpuMpu2()
{
	TXmpuVmpManger* ptManger = &CUmsConfInst::m_tXmpuVmpManger;
	TServiceReg tInfo;
	tInfo.m_tBaseInfo.m_emType = em_mpu2tp_service;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		CServiceInfo* pcService  = Find(em_mpu2tp_service, ptManger->m_adwVmpID[wIndex]);
		if ( NULL != pcService )
		{
			// vmp 掉线
			if (ptManger->m_aemStat[wIndex] == VmpManger_Vmp ||
				((ptManger->m_aemStat[wIndex] == VmpManger_Normal)&&(pcService->AssignState()|| pcService->WorkStatus())))
			{
				MdlHint(Ums_Mdl_Call, ("CEqpService::FlushXmpuMpu2. Disconnect EqpID:%d,  state:%d\n", ptManger->m_adwVmpID[wIndex], ptManger->m_aemStat[wIndex]));
				OnXmpuMpu2DisConnnect(ptManger->m_adwVmpID[wIndex]);
			}
			else
			{
				MdlHint(Ums_Mdl_Call, ("CEqpService::FlushXmpuMpu2. ptVmp is already exit. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
			}

			continue ;
		}

		// 当前vmp不在线
		if (ptManger->m_aemStat[wIndex]  != VmpManger_Normal)
		{
			continue ;
		}

		pcService = FindIdle();
		if (NULL == pcService)
		{
			MdlError(Ums_Mdl_Call, ("CEqpService::FlushXmpuMpu2. ptVmp is NULL, no idle. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
			return;
		}
		MdlHint(Ums_Mdl_Call, ("CEqpService::FlushXmpuMpu2. wIndex:%d, EqpID:%d\n", wIndex, ptManger->m_adwVmpID[wIndex]));
		tInfo.m_tBaseInfo.m_wServiceID = ptManger->m_adwVmpID[wIndex];
		pcService->Init(tInfo);
	}

}

void CEqpService::OnXmpuMpu2DisConnnect( u32 dwEqpID )
{
	MdlHint(Ums_Mdl_Call, ("CEqpService::OnXmpuMpu2DisConnnect ServiceID:%d,.\n", dwEqpID));

	if (dwEqpID == 0)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::OnXmpuMpu2DisConnnect Invalid service.\n"));
		return ;
	}

	CServiceInfo* pcService = Find(em_mpu2tp_service, dwEqpID);
	if (NULL == pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::OnXmpuMpu2DisConnnect Can not find the service.\n"));
		return ;
	}

	if (!pcService->IdleStatus())
	{
		pcService->RunCBFun(em_Normal_Op, em_Service_No_Reg);
		pcService->Stop();
	}

	pcService->Clear();
}

void CEqpService::ReleaseXmpuMpu2( const CBaseService* pcService, const EmServiceType emType )
{
	if (NULL == pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::ReleaseXmpuMpu2 Invalid param.\n"));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CEqpService::ReleaseXmpuMpu2 type:%d, service:%d.\n", emType, pcService->GetServiceID()));

	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if (pcService->GetServiceID() == m_acInfo[wIndex].GetServiceID() && !m_acInfo[wIndex].IdleStatus())
		{
			m_acInfo[wIndex].ReleaseMpu2();
			break;
		}
	}
}

void CEqpService::OnXmpuVmpMdyNty(CUmsConfInst* pcInst, TXmpuVmpMdyInfo tInfo )
{
	CServiceInfo* pcService  = Find(em_mpu2tp_service, tInfo.m_dwEqpID);
	if (NULL == pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::OnXmpuVmpMdyNty. ptInfo is Invalid! dwEqpID:%d\n", pcService->GetServiceID()));
		return ;
	}

	MdlHint(Ums_Mdl_Call, ("CEqpService::OnXmpuVmpMdyNty., EqpID:%d, chanIndex:%d\n", 
			tInfo.m_dwEqpID, tInfo.m_bSuccess));
	if (!tInfo.m_bSuccess)
	{
		OnXmpuMpu2DisConnnect(tInfo.m_dwEqpID);
		//刷新失败合成器，并初始化
		CUmsConfInst::m_tXmpuVmpManger.ReleaseVmp(tInfo.m_dwEqpID);
		CUmsVmp::FlushXmpuVmp();
		FlushXmpuMpu2();
		return;
	}

	((CServiceInfo*)pcService)->SetXmpuVmpTPOnline(tInfo);
	// 刷新交换
	CNetPortMgr::AdjustXmpuMiddleAddrToMpu2(pcInst, pcService);
}

void CEqpService::FlushXmpuMiddleAddrToMpu2( const CBaseService* pcService )
{
#ifndef _USE_XMPUEQP_
	return;
#endif

	if (!pcService)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::FlushXmpuMiddleAddrToMpu2. pcService is NULL！\n"));
		return;
	}
	CUmsConfInst* pcInst = (CUmsConfInst*)((CServiceInfo*)pcService)->Param();
	if (!pcInst)
	{
		MdlError(Ums_Mdl_Call, ("CEqpService::FlushXmpuMiddleAddrToMpu2. pcInst is NULL dwEqpID:%d\n", 
					pcService->GetServiceID()));
		return;
	}
	CNetPortMgr::AdjustXmpuMiddleAddrToMpu2(pcInst, (CServiceInfo*)pcService);
}

void CEqpService::UpdateXmpuMpu2()
{
	MdlHint(Ums_Mdl_Call, ("CEqpService::UpdateXmpuMpu2.\n"));

	TXmpuVmpManger* ptManger = &CUmsConfInst::m_tXmpuVmpManger;
	TServiceReg tInfo;
	tInfo.m_tBaseInfo.m_emType = em_mpu2tp_service;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if ((ptManger->m_adwVmpID[wIndex] == 0) || (ptManger->m_aemStat[wIndex]  != VmpManger_Normal))
		{
			continue;
		}
				
		CServiceInfo* pcService  = Find(em_mpu2tp_service, ptManger->m_adwVmpID[wIndex]);
		if ( NULL == pcService )
		{
			pcService = FindIdle();
			if (NULL == pcService)
			{
				MdlError(Ums_Mdl_Call, ("CEqpService::FlushXmpuMpu2. ptVmp is NULL, no idle. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
				return;
			}
			MdlHint(Ums_Mdl_Call, ("CEqpService::FlushXmpuMpu2. wIndex:%d, EqpID:%d\n", wIndex, ptManger->m_adwVmpID[wIndex]));
			tInfo.m_tBaseInfo.m_wServiceID = ptManger->m_adwVmpID[wIndex];
			pcService->Init(tInfo);
			
		}
		else
		{
			MdlHint(Ums_Mdl_Call, ("CEqpService::UpdateXmpuMpu2. ptVmp is already exist. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
		}
		
	}
}

void CEqpService::DisconnectXmpuMpu2(u32 dwEqpID)
{
	MdlHint(Ums_Mdl_Call, ("CEqpService::DisconnectXmpuMpu2. Disconnect EqpID:%d\n",dwEqpID));
	TXmpuVmpManger* ptManger = &CUmsConfInst::m_tXmpuVmpManger;
	for (u16 wIndex = 0; wIndex < UMS_MAX_SERVICE_NUM; ++wIndex)
	{
		if ((ptManger->m_aemStat[wIndex]  != VmpManger_Normal) && (ptManger->m_aemStat[wIndex] != VmpManger_Mpu2tp))
		{
			continue ;
		}
		if (dwEqpID == ptManger->m_adwVmpID[wIndex])
		{
			// 查找断链mpu2
			CServiceInfo* pcService  = Find(em_mpu2tp_service, ptManger->m_adwVmpID[wIndex]);
			if ( NULL != pcService )
			{
				// vmp 掉线
				if (ptManger->m_aemStat[wIndex] == VmpManger_Mpu2tp ||
					((ptManger->m_aemStat[wIndex] == VmpManger_Normal)&&(pcService->AssignState()|| pcService->WorkStatus())))
				{
					MdlHint(Ums_Mdl_Call, ("CEqpService::DisconnectXmpuMpu2. Disconnect EqpID:%d,  state:%d\n", ptManger->m_adwVmpID[wIndex], ptManger->m_aemStat[wIndex]));
					OnXmpuMpu2DisConnnect(ptManger->m_adwVmpID[wIndex]);
					break;
				}
				else
				{
					MdlHint(Ums_Mdl_Call, ("CEqpService::DisconnectXmpuMpu2. ptVmp is already exit. EqpID:%d\n", ptManger->m_adwVmpID[wIndex]));
				}
			}
		}
		
		continue;
	}
	return;		
}
 