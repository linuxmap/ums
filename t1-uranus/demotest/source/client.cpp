#include "osp.h"
#include "pbinstance.h"

#include "common.h"
#include "convert.h"
#include "client.h"

#define PBMSG_MAX_LEN			1024		
static u8		g_achBuf[PBMSG_MAX_LEN+1] = {0};

#ifndef WIN32
#define _snprintf	snprintf
#endif


class CClientInst : public pbmsg::CPBInstance
{
protected:
	virtual BOOL32	InstInit(u32 dwParam)
	{
		s8 szModName[32] = {0};
		_snprintf(szModName, 31, "%s-%d", CLIENT_APP_NAME, GetInsID());
		
		std::string strLog(szModName);
		SetModName(strLog);

		BuildInstAllMsgMap();

		LogInfo("InstInit is Ok!");

		return TRUE;
	}
	virtual BOOL32	DaemonInstInit(u32 dwParam, CApp* pcApp)
	{
		s8 szModName[32] = {0};
		_snprintf(szModName, 31, "%s-%s", CLIENT_APP_NAME, "Daemon");

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
		RegMsgFunc(Ev_View_Req, (pbmsg::PFMsgFunc)&CClientInst::OnViewReq);
		RegMsgFunc(Ev_View_ReqRsp, (pbmsg::PFMsgFunc)&CClientInst::OnViewReqRsp);
	}
	void	BuildDaemonInstAllMsgMap()
	{
		RegMsgFunc(Ev_View_Req, (pbmsg::PFMsgFunc)&CClientInst::OnViewReq);
		RegMsgFunc(Ev_View_ReqRsp, (pbmsg::PFMsgFunc)&CClientInst::OnViewReqRsp);
	}

	//
	BOOL32	OnViewReq(CMessage* const pcMsg)
	{
		LogInfo("OnViewReq dwSrcId:%u(%d,%d), dwSrcNode:%u.", pcMsg->srcid, GETAPP(pcMsg->srcid), GETINS(pcMsg->srcid), pcMsg->srcnode);
		
		TViewReq tReq;
		if (pcMsg->length >= sizeof(tReq))
		{
			memcpy(&tReq, pcMsg->content, sizeof(tReq));
		}

		LogInfo("OnViewReq confid:%d, src:%d-%d, dst:%d-%d, type:%d.", tReq.m_wConfId,
			tReq.m_wSrcEpId, tReq.m_wSrcScreenIndex, tReq.m_wDstEpId,
			tReq.m_wDstScreenIndex, tReq.m_emViewType);

		pbmsg::TViewReq tPBViewReq;
		ConvertViewReqToPB(tReq, tPBViewReq);

		pbmsg::CPBMsg pbMsg;
		pbMsg.SetMsgName("Ev_View_Req");
		pbMsg.SetSequenceID(1);
		pbMsg.AddMsgBody(&tPBViewReq);

		u16 wLen = PBMSG_MAX_LEN;
		memset(g_achBuf,0,sizeof(g_achBuf));
		pbMsg.Encode(g_achBuf, wLen);

		LogInfo("Ev_View_Req before len %d after enc wLen=%d.", sizeof(TViewReq), wLen);

		post(MAKEIID(SERVER_APP_ID, CInstance::DAEMON), Ev_OSP_PBInst_PBMsg, g_achBuf, wLen);
		
		return TRUE;
	}

	BOOL32	OnViewReqRsp(CMessage* const pcMsg)
	{
		LogInfo("OnViewReqRsp dwSrcId:%u(%d,%d), dwSrcNode:%u.", pcMsg->srcid, GETAPP(pcMsg->srcid), GETINS(pcMsg->srcid), pcMsg->srcnode);

		TViewReq tReq;
		u32 bRet = 0xFFFFFFFF;
		if (pcMsg->length >= sizeof(tReq)+sizeof(bRet))
		{
			memcpy(&tReq, pcMsg->content, sizeof(tReq));
			memcpy(&bRet, pcMsg->content+sizeof(tReq), sizeof(bRet));
		}

		LogInfo("OnViewReqRsp confid:%d, src:%d-%d, dst:%d-%d, type:%d, ret:%d.", tReq.m_wConfId,
			tReq.m_wSrcEpId, tReq.m_wSrcScreenIndex, tReq.m_wDstEpId,
			tReq.m_wDstScreenIndex, tReq.m_emViewType, bRet);

		return TRUE;
	}

};

typedef zTemplate<CClientInst, CLIENT_INST_NUM> CClientApp;

CClientApp		g_cClientApp;

void ClientRun()
{
	g_cClientApp.CreateApp(CLIENT_APP_NAME, CLIENT_APP_ID, CLIENT_APP_PRI,
		CLIENT_APP_QUEUESIZE, CLIENT_APP_STACKSIZE);

	OspPost(MAKEIID(CLIENT_APP_ID, CInstance::DAEMON), Ev_OSP_PBInst_Init);
// 	for (u16 wIndex = 0; wIndex < SERVER_INST_NUM; wIndex++)
// 	{
// 		OspPost(MAKEIID(CLIENT_APP_ID, wIndex+1), Ev_OSP_PBInst_Init);
// 	}

	return;
}

void ViewReq(TViewReq& tReq)
{
	OspPost(MAKEIID(CLIENT_APP_ID, CInstance::DAEMON), Ev_View_Req, &tReq, sizeof(tReq));
}

