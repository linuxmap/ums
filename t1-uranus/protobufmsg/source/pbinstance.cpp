#include "pbinstance.h"

namespace pbmsg{

BOOL32 CPBInstance::RegPBMsgFunc( std::string strMsgName, PFPBMsgFunc pPBMsgFunc )
{
	m_mapPBMsgFunc[strMsgName] = pPBMsgFunc;
	return TRUE;
}

BOOL32 CPBInstance::UnRegPBMsgFunc( std::string strMsgName )
{
	std::map<std::string, PFPBMsgFunc>::iterator itElem = m_mapPBMsgFunc.find(strMsgName);
	if (itElem != m_mapPBMsgFunc.end())
	{
		m_mapPBMsgFunc.erase(itElem);
	}
	return TRUE;
}

BOOL32 CPBInstance::IsPBMsgFuncReg( std::string strMsgName )
{
	if (m_mapPBMsgFunc.find(strMsgName) != m_mapPBMsgFunc.end())
	{
		return TRUE;
	}
	return FALSE;
}

void CPBInstance::ClearPBMsgFunc()
{
	m_mapPBMsgFunc.clear();
}

BOOL32 CPBInstance::HandlePBMsg( CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode )
{
	if (IsPBMsgFuncReg(pcPBMsg->GetMsgName()))
	{
		(this->*((pbmsg::PFPBMsgFunc)(m_mapPBMsgFunc[pcPBMsg->GetMsgName()])))(pcPBMsg, dwSrcId, dwSrcNode);
		return TRUE;
	}
	return FALSE;
}


BOOL32 CPBInstance::RegMsgFunc( u16 wEvent, PFMsgFunc pMsgFunc )
{
	m_mapMsgFunc[wEvent] = pMsgFunc;
	return TRUE;
}

BOOL32 CPBInstance::UnRegMsgFunc( u16 wEvent )
{
	std::map<u16, PFMsgFunc>::iterator itElem = m_mapMsgFunc.find(wEvent);
	if (itElem != m_mapMsgFunc.end())
	{
		m_mapMsgFunc.erase(itElem);
	}
	return TRUE;
}

BOOL32 CPBInstance::IsMsgFuncReg( u16 wEvent )
{
	if (m_mapMsgFunc.find(wEvent) != m_mapMsgFunc.end())
	{
		return TRUE;
	}
	return FALSE;
}

void CPBInstance::ClearMsgFunc()
{
	m_mapMsgFunc.clear();
}

BOOL32 CPBInstance::HandleMsg( CMessage* const pcMsg )
{
	if (IsMsgFuncReg(pcMsg->event))
	{
		(this->*((pbmsg::PFMsgFunc)(m_mapMsgFunc[pcMsg->event])))(pcMsg);
		return TRUE;
	}
	return FALSE;
}


void CPBInstance::DaemonInstanceEntry( CMessage* const pMsg, CApp* pcApp )
{
	u16 wEvent = pMsg->event;
	if (Ev_OSP_PBInst_Init == wEvent)
	{
		if (m_bInit){
			return;
		}

		u32 dwParam = pMsg->length == 0?0:*(reinterpret_cast<u32*>(pMsg->content));
		if (DaemonInstInit(dwParam, pcApp))
		{
			m_bInit = TRUE;
		}
	}
	else if (Ev_OSP_PBInst_Exit == wEvent)
	{
		if (!m_bInit){
			return;
		}
		DaemonInstExit();
		m_bInit = FALSE;
	}
	else
	{
		if (m_bInit)
		{
			if (Ev_OSP_PBInst_PBMsg == wEvent)
			{
				CPBMsg cPBMsg;
				cPBMsg.Decode(pMsg->content, pMsg->length);
				DaemonPBMessageProc(&cPBMsg, pcApp, pMsg->srcid, pMsg->srcnode);
			}
			else
			{
				DaemonMessageProc(pMsg, pcApp);
			}
		}
		else
		{
			// instance is not init!
		}
	}
}

void CPBInstance::InstanceEntry( CMessage* const pMsg )
{
	u16 wEvent = pMsg->event;
	if (Ev_OSP_PBInst_Init == wEvent)
	{
		if (m_bInit){
			return;
		}

		u32 dwParam = pMsg->length == 0?0:*(reinterpret_cast<u32*>(pMsg->content));
		if (InstInit(dwParam))
		{
			m_bInit = TRUE;
		}
	}
	else if (Ev_OSP_PBInst_Exit == wEvent)
	{
		if (!m_bInit){
			return;
		}
		InstExit();
		m_bInit = FALSE;
	}
	else
	{
		if (m_bInit)
		{
			if (Ev_OSP_PBInst_PBMsg == wEvent)
			{
				CPBMsg cPBMsg;
				cPBMsg.Decode(pMsg->content, pMsg->length);
				PBMessageProc(&cPBMsg, pMsg->srcid, pMsg->srcnode);
			}
			else
			{
				MessageProc(pMsg);
			}
		}
		else
		{
			// instance is not init!
		}
	}
}

}