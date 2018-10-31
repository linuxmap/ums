#include "osp.h"
#include "pbinstance.h"
#include "pbmsg.h"

#include "common.h"
#include "convert.h"
#include "server.h"

#ifndef WIN32
#define _snprintf	snprintf
#endif

class CServerInst : public pbmsg::CPBInstance
{
protected:
	virtual BOOL32	InstInit(u32 dwParam)
	{
		s8 szModName[32] = {0};
		_snprintf(szModName, 31, "%s-%d", SERVER_APP_NAME, GetInsID());

		std::string strLog(szModName);
		SetModName(strLog);

		BuildInstAllMsgMap();

		LogInfo("InstInit is Ok!");

		return TRUE;
	}
	virtual BOOL32	DaemonInstInit(u32 dwParam, CApp* pcApp)
	{
		s8 szModName[32] = {0};
		_snprintf(szModName, 31, "%s-%s", SERVER_APP_NAME, "Daemon");

		std::string strLog(szModName);
		SetModName(strLog);

		BuildDaemonInstAllMsgMap();

		LogInfo("DaemonInstInit is Ok!");

		return TRUE;
	}

	virtual void	InstExit(){}
	virtual void	DaemonInstExit(){}

	virtual BOOL32 MessageProc( CMessage *const pcMsg)
	{
		if (OSP_DISCONNECT == pcMsg->event)
		{
			u32 dwNode = *(u32*)pcMsg->content;
			LogInfo("MessageProc event OSP_DISCONNECT, dwNode:%d.", 
				dwNode);				
			OspDisconnectTcpNode(dwNode);
			return TRUE;
		}

		if (!HandleMsg(pcMsg))
		{
			LogInfo("MessageProc event %d from %d(%d-%d) node %d is unkonw!", 
				pcMsg->event, pcMsg->srcid, 
				GETAPP(pcMsg->srcid), GETINS(pcMsg->srcid), pcMsg->srcnode);
		}

		return FALSE;
	}
	virtual BOOL32 DaemonMessageProc(CMessage* const pcMsg, CApp* pcApp)
	{
		if (OSP_DISCONNECT == pcMsg->event)
		{
			u32 dwNode = *(u32*)pcMsg->content;
			LogInfo("DaemonMessageProc event OSP_DISCONNECT, dwNode:%d.", 
				dwNode);				
			OspDisconnectTcpNode(dwNode);
			return TRUE;
		}

		if (!HandleMsg(pcMsg))
		{
			LogInfo("DaemonMessageProc event %d from %d(%d-%d) node %d is unkonw!", 
				pcMsg->event, pcMsg->srcid, 
				GETAPP(pcMsg->srcid), GETINS(pcMsg->srcid), pcMsg->srcnode);
		}
		return TRUE;
	}

	virtual BOOL32 PBMessageProc(pbmsg::CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode)
	{
		if (!HandlePBMsg(pcPBMsg, dwSrcId, dwSrcNode))
		{
			LogInfo("PBMessageProc event %s from %d(%d-%d) node %d is unkonw!.", 
				pcPBMsg->GetMsgName().c_str(), dwSrcId,
				GETAPP(dwSrcId), GETINS(dwSrcId), dwSrcNode);
		}
		return TRUE;
	}
	virtual BOOL32 DaemonPBMessageProc(pbmsg::CPBMsg* pcPBMsg, CApp* pcApp, u32 dwSrcId, u32 dwSrcNode)
	{
		if (!HandlePBMsg(pcPBMsg, dwSrcId, dwSrcNode))
		{
			LogInfo("DaemonPBMessageProc event %s from %d(%d-%d) node %d is unkonw!.", 
				pcPBMsg->GetMsgName().c_str(), dwSrcId,
				GETAPP(dwSrcId), GETINS(dwSrcId), dwSrcNode);
		}
		return TRUE;
	}

protected:
	void	BuildInstAllMsgMap()
	{
		RegPBMsgFunc("Ev_View_Req", (pbmsg::PFPBMsgFunc)&CServerInst::OnViewReq);
	}
	void	BuildDaemonInstAllMsgMap()
	{
		RegPBMsgFunc("Ev_View_Req", (pbmsg::PFPBMsgFunc)&CServerInst::OnViewReq);
	}

	//
	BOOL32	OnViewReq(pbmsg::CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode)
	{
		LogInfo("OnViewReq dwSrcId:%u(%d,%d), dwSrcNode:%u.", 
			dwSrcId, GETAPP(dwSrcId), GETINS(dwSrcId), dwSrcNode);

		LogInfo("msgname:%s, seqid:%d, size:%d.",
			pcPBMsg->GetMsgName().c_str(), pcPBMsg->GetSequenceID(), pcPBMsg->GetMsgBodySize());
		
		pbmsg::TViewReq tpbReq;
		TViewReq tReq;
		if (pcPBMsg->GetMsgBodySize()>0)
		{
			tpbReq = *(pbmsg::TViewReq*)(pcPBMsg->GetMsgBody(0));
			ConvertViewReqFromPB(tpbReq, tReq);
		}

		LogInfo("OnViewReq confid:%d, src:%d-%d, dst:%d-%d, type:%d.", tReq.m_wConfId,
			tReq.m_wSrcEpId, tReq.m_wSrcScreenIndex, tReq.m_wDstEpId,
			tReq.m_wDstScreenIndex, tReq.m_emViewType);

		u32 bRet = Opr_Ok;
		u8 abBuf[sizeof(tReq)+sizeof(u32)]={0};
		memcpy(abBuf, &tReq, sizeof(tReq));
		memcpy(abBuf+sizeof(tReq), &bRet, sizeof(BOOL32));
		post(dwSrcId, Ev_View_ReqRsp, abBuf, sizeof(abBuf), dwSrcNode);

		return TRUE;
	}

};

typedef zTemplate<CServerInst, SERVER_INST_NUM> CServerApp;

CServerApp		g_cServerApp;


void ServerRun()
{
	g_cServerApp.CreateApp(SERVER_APP_NAME, SERVER_APP_ID, SERVER_APP_PRI,
		SERVER_APP_QUEUESIZE, SERVER_APP_STACKSIZE);

	OspPost(MAKEIID(SERVER_APP_ID, CInstance::DAEMON), Ev_OSP_PBInst_Init);
// 	for (u16 wIndex = 0; wIndex < SERVER_INST_NUM; wIndex++)
// 	{
// 		OspPost(MAKEIID(SERVER_APP_ID, wIndex+1), Ev_OSP_PBInst_Init);
// 	}

	return;
}
