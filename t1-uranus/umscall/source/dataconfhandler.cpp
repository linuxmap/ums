#include "dataconfhandler.h"
#include "umsconfinst.h"
#include "eventoutsipadapter.h"
#include "callnodemgr.h"
#include "umsstackinterface.h"

//////////////////////////////////////////////////////////////////////////
//白板会议管理
CDataConfHandler::CDataConfHandler(CTpObject* pcObject) : CTpHandler(pcObject)
{
	m_emStatus = em_data_conf_idle;
	m_dwServerIP = 0;
}

CDataConfHandler::~CDataConfHandler()
{
	
}

BOOL32 CDataConfHandler::Handler(CTpMsg *const ptMsg)
{
	u16 wEvent = ptMsg->GetEvent();
	switch (wEvent)
	{
	case evtp_JoinWBConf_Cmd:
		{
			EventJoinDataConf(ptMsg);
		}
		break;

	case evtp_JoinWBConf_Ind:
		{
			EventJoinDataConfInd(ptMsg);
		}
		break;

	case evtp_HungUpWBConf_Cmd:
		{
			EventHungUpDataConf(ptMsg);
		}
		break;

	default:
		{
			ObjError(("Handler Invalid data-conf event:%d.\n", wEvent));
		}
		break;
	}

	return TRUE;
}

void CDataConfHandler::EventJoinDataConf(CTpMsg* const ptMsg)
{
	TUmsHandle tHandle;
	u32 dwIP = 0;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TP_SAFE_CAST(dwIP, ptMsg->GetBody()+sizeof(tHandle));

	CUmsConfInst* pInst = (CUmsConfInst*)GetInstance();
	MdlHint( Ums_Mdl_Call, ("EventJoinDataConf ConfID:%d, EpID:%d, IP:"IPFORMAT".\n", pInst->GetInsID(), tHandle.GetEpID(), Tpu32ToIP(dwIP)));

	BOOL32 bRes = TRUE;
	m_emStatus = em_data_conf_working;
	m_dwServerIP = dwIP;

	TUmsHandle tOutHandle;
	pInst->GetNodeMgr()->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, evtp_JoinWBConf_Ind, &bRes, sizeof(bRes));

	if (bRes)
	{
		TCallNode* ptNode;
		for (ptNode = pInst->GetNodeMgr()->FirstNode(); ptNode != NULL; ptNode = pInst->GetNodeMgr()->NextLoalNode(ptNode))
		{
			if(!ptNode->m_bUsed || !ptNode->IsChanOn())
			{
				continue;
			}
			
			if ( ptNode->IsUms() && ptNode->m_wEpID == tHandle.GetEpID() )
			{//下级ums过来的消息，不要再通知下去了
				continue;
			}

			pInst->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_JoinWBConf_Cmd, &dwIP, sizeof(u32));
		}

		ptNode = pInst->GetNodeMgr()->GetCaller();
		if ( NULL != ptNode && ptNode->IsChanOn() && ptNode->m_wEpID != tHandle.GetEpID() )
		{//通知 上级过来通知的 不要再通知上去了
			pInst->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
			UmsSendConfCtrl(tOutHandle, evtp_JoinWBConf_Cmd, &dwIP, sizeof(u32));
		}
	}
}

void CDataConfHandler::EventJoinDataConfInd(CTpMsg* const ptMsg)
{
	TUmsHandle tHandle;
	BOOL32 bRes = TRUE;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	TP_SAFE_CAST(bRes, ptMsg->GetBody()+sizeof(tHandle));

	CUmsConfInst* pInst = (CUmsConfInst*)GetInstance();
	MdlHint( Ums_Mdl_Call, ("EventJoinDataConfInd ConfID:%d, EpID:%d, Res:%d.\n", pInst->GetInsID(), tHandle.GetEpID(), bRes));
}

void CDataConfHandler::EventHungUpDataConf(CTpMsg* const ptMsg)
{
	TUmsHandle tHandle;
	TP_SAFE_CAST(tHandle, ptMsg->GetBody());
	
	CUmsConfInst* pInst = (CUmsConfInst*)GetInstance();
	MdlHint( Ums_Mdl_Call, ("EventJoinDataConfInd ConfID:%d, EpID:%d.\n", pInst->GetInsID(), tHandle.GetEpID()));

	m_emStatus = em_data_conf_idle;
	m_dwServerIP = 0;
	
	TUmsHandle tOutHandle;
	TCallNode* ptNode;
	for (ptNode = pInst->GetNodeMgr()->FirstNode(); ptNode != NULL; ptNode = pInst->GetNodeMgr()->NextLoalNode(ptNode))
	{
		if(!ptNode->m_bUsed || !ptNode->IsChanOn())
		{
			continue;
		}

		if ( ptNode->IsUms() && ptNode->m_wEpID == tHandle.GetEpID() )
		{//下级ums过来的消息，不要再通知下去了
			continue;
		}

		pInst->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_HungUpWBConf_Cmd, NULL, 0);
	}

	ptNode = pInst->GetNodeMgr()->GetCaller();
	if ( NULL != ptNode && ptNode->IsChanOn() && ptNode->m_wEpID != tHandle.GetEpID() )
	{//通知 上级过来通知的 不要再通知上去了
		pInst->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
		UmsSendConfCtrl(tOutHandle, evtp_HungUpWBConf_Cmd, NULL, 0);
	}
}

void CDataConfHandler::OnChanConnect( TCallNode* ptNode )
{
	if (!ConfWorking() || NULL == ptNode )
	{
		return;
	}
	
	CUmsConfInst* pInst = (CUmsConfInst*)GetInstance();
	MdlHint( Ums_Mdl_Call, ("EventJoinDataConfInd ConfID:%d, EpID:%d.\n", pInst->GetInsID(), ptNode->m_wEpID));

	u32 dwIP = ServerIP();
	TUmsHandle tOutHandle;
	Inst()->GetNodeMgr()->MakeCallerHandle(tOutHandle, ptNode->m_wEpID);
	UmsSendConfCtrl(tOutHandle, evtp_JoinWBConf_Cmd, &dwIP, sizeof(u32));
}
