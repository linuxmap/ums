#include "tpobject.h"
#include "eventtpsys.h"
#include "tpstruct.h"

namespace UmsTpmsg{

u32 g_dwKdvShowMsg = 0;
u32 g_dwSysApp = INVALID_APP;

API void showmsg(u32 show)
{
	g_dwKdvShowMsg = show;
	msgprint( " g_dwKdvShowMsg = %d\n ", g_dwKdvShowMsg );
}


API void ShowEventInfo(u16 wEventID, s8* pTitle);


CTpObject::CTpObject()
{
	m_bInit = FALSE;
}

CTpObject::~CTpObject()
{
	ObjectExit();
}



BOOL32 CTpObject::DaemonObjectInit(u32 wParam, u32 lParam)
{
	m_bInit = TRUE;
	return TRUE;
}
void CTpObject::DaemonObjectExit(void)
{
	m_bInit = FALSE;
}
void CTpObject::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp )
{
	if (g_dwKdvShowMsg)
	{
		ShowEventInfo(pcMsg->event, m_pLogTitle);
	}


	SetLastEventID(pcMsg->event);
	SetInHandMsg(TRUE);

	if (PreDaemonMessageProc(pcMsg))
	{
		SetInHandMsg(FALSE);
		return;
	}

	switch(pcMsg->event)
	{
	case ev_kdvmsg_sys_init:
		{
			u8* buf = pcMsg->content;
			u32 wParam;
			u32 lParam;
			memcpy( &wParam, buf, sizeof( wParam ) );
			buf += sizeof(u32);
			memcpy( &lParam, buf, sizeof( wParam ) );
			m_bInit = DaemonObjectInit(wParam, lParam);
			
			if ( !m_bInit )
			{
				msgprint("[init Error], app.%d daemon %s Object Init failed! \n", GetAppID(), m_pLogTitle);
			}			
		}
		break;
	case ev_kdvmsg_sys_exit:
		DaemonObjectExit();
		break;
	default:
		{
			if( m_bInit )
			{
				CTpMsg cMsg(pcMsg);
				DaemonMessageProc(&cMsg ,pcApp);
			}
			else 
			{
				msgprint("DaemonInstanceEntry app.%d inst.%d %s not init! event: %d->%s\n",GetAppID(),GetInsID(), m_pLogTitle, pcMsg->event, GetEventNamebyID(pcMsg->event));
 			}
		}
	}


	SetInHandMsg(FALSE);

}


void CTpObject::ObjectExit()
{
	m_bInit = FALSE;
	msgprint("app.%d %s will be exit...\n", GetAppID(), m_pLogTitle);
}


void CTpObject::InstanceEntry(CMessage *const ptMsg)
{
	if (g_dwKdvShowMsg)
	{
		ShowEventInfo(ptMsg->event, m_pLogTitle);
	}

	SetLastEventID(ptMsg->event);
	SetInHandMsg(TRUE);

	if (PreMessageProc(ptMsg))
	{
		SetInHandMsg(FALSE);
		return;
	}

	if (AID_MPU2TP_APP == GETAPP(ptMsg->srcid) && 2 == GETINS(ptMsg->srcid))
	{
		u32 dwVal = 0;
	}

	if (AID_MPU2TP_APP == GETAPP(ptMsg->srcid) && 1 == GETINS(ptMsg->srcid))
	{
		u32 dwVal2 = 0;
	}
	
	CTpMsg cMsg(ptMsg);
	switch( cMsg.GetEvent()) 
	{
	case ev_kdvmsg_sys_init:
		{
			u8* buf = cMsg.GetBody();
			u32 wParam;
			u32 lParam;
			memcpy( &wParam, buf, sizeof( wParam ) );
			buf += sizeof(u32);
			memcpy( &lParam, buf, sizeof( lParam ) );
			
			m_bInit = ObjectInit(wParam, lParam);
			
			if ( !m_bInit )
			{
				msgprint("[init Error], app.%d inst:%d %s Object Init failed! \n", GetAppID(),  GetInsID(), m_pLogTitle);
			}

			if ( INVALID_APP != g_dwSysApp )
			{
				CTpMsg cMsg;
				cMsg.SetEvent( ev_kdvmsg_sys_init_ind );
				cMsg.SetBody( &m_bInit ,sizeof(BOOL) );
				cMsg.Post( g_dwSysApp ,0 ,MAKEIID( GetAppID() ,GetInsID() ) );
			}
		}
		break;
	case ev_kdvmsg_sys_exit:
		{
			msgprint("[ev_kdvmsg_sys_exit], app.%d inst:%d, srcNode:%d, srcApp:%d, srcInst:%d\n"
				, GetAppID(),  GetInsID(), ptMsg->srcnode, GETAPP(ptMsg->srcid), GETINS(ptMsg->srcid));
			ObjectExit();		
		}
		break;

	default:
		{
			
			if( m_bInit )
			{
				MessageProc( &cMsg );
			}
			else 
			{
				msgprint("app.%d Ins:%d %s not init! event:%d->%s\n",GetAppID(),GetInsID(), m_pLogTitle, cMsg.GetEvent(), GetEventNamebyID(cMsg.GetEvent()));
			}
		}	
		break;
	}	
	
	
	SetInHandMsg(FALSE);
}



void CTpObject::SetLogTitle(s8* title)
{
	if (title == NULL)
	{
		title = "[CTpLogInst]";
	}
	
	CTpLog::SetLogTitle(title);
}


} //namespace UmsTpmsg