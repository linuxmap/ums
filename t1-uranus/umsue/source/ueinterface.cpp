#include "tpsys.h"
#include "tpstruct.h"
#include "ueinterface.h"
#include "umsueinit.h"
#include "umsconfig.h"

#include "innereventumsserver.h"

// 外部消息
#include "eventoutumslogin.h"
#include "eventoutumsconftemplate.h"
#include "eventoutumscall.h"
#include "eventoutcfgex.h"

#ifdef _USE_XMPUEQP_
#include "umsxmpinterface.h"
#endif

CUmsUeApp g_cUmsUeApp;
TUmsUeCfg g_cUmsUeCfg;

void InitUeLib(TUmsUeCfg& tCfg)
{
	g_cUmsUeCfg = tCfg;

	g_cUmsUeApp.CreateApp("UmsUeApp", AID_UMSUE_APP, 100, 2048);
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_kdvmsg_sys_init);
	cMsg.Post(UMS_UE_APP_INST);
	
	MdlHint(Ums_Mdl_Ue, ("InitUeLib Ue start.\n"));
}


CUmcHandler* CUmsUeInst::m_pcUmcHandler = NULL;
CToolHandler* CUmsUeInst::m_pcToolHandler = NULL;

CUmsUeInst::CUmsUeInst()
{
	m_wLogModuleId	= Ums_Mdl_Ue;
	m_dwUmcAppID	= 0;
	m_dwToolAppID	= 0;
	m_dwListenNode	= 0;
}

CUmsUeInst::~CUmsUeInst()
{
	ObjectExit();
}


BOOL CUmsUeInst::PreMessageProc ( CMessage *const ptMsg )
{
	
	u16 wAppID = GETAPP(ptMsg->srcid);

	if(wAppID == GETAPP(m_dwUmcAppID) || wAppID == GETAPP(m_dwToolAppID))
	{
		switch(ptMsg->event)
		{
		case ev_UMSLoginReq:
			{
				DispatchPreMsg(ptMsg);
			}
			break;

		case ev_UMSAddUserReq:
		case ev_UMSDelUserReq:
		case ev_UMSChangePWDReq:
		case evtp_AddConfTemplate_req1:
		case evtp_Updateconftemplate_Req1:
		case evtp_StartInterimMeeting_Req:
			{

				if (NULL != m_pcUmcHandler)
				{
					m_pcUmcHandler->PreHandler(ptMsg);
				}
			}
			break;

		default:
			return FALSE;
		}
		return TRUE;
	}

	if (ptMsg->event == OSP_DISCONNECT)
	{
		OnDisconnect(ptMsg);
		return TRUE;
	}

	return FALSE;
}
void CUmsUeInst::MessageProc( CTpMsg *const ptMsg)
{
	u16 wAppID	= GETAPP(ptMsg->GetSrcIId());
	//界面的转到业务
	if (wAppID == GETAPP(m_dwUmcAppID))
	{
		m_pcUmcHandler->Handler(ptMsg);
		return ;
	}

	if (wAppID == GETAPP(m_dwToolAppID))
	{
		m_pcToolHandler->Handler(ptMsg);
		return ;
	}

	//从业务转到界面
	TLogUser* pLogUser = (TLogUser*)ptMsg->GetBody();

	if (GETAPP(pLogUser->m_dwUserInst) == GETAPP(m_dwToolAppID))
	{
		m_pcToolHandler->Handler(ptMsg);
		return ;
	}
	else
	{
		m_pcUmcHandler->Handler(ptMsg);
		return ;
	}
}

void CUmsUeInst::DispatchPreMsg(CMessage* const pMsg)
{
	u16 wAppID = GETAPP(pMsg->srcid);

	if (wAppID == GETAPP(m_dwUmcAppID))
	{
		m_pcUmcHandler->PreHandler(pMsg);
		return ;
	}

	if (wAppID == GETAPP(m_dwToolAppID))
	{
		m_pcToolHandler->PreHandler(pMsg);
		return ;
	}

	ObjError(("[DispatchPreMsg] Unknow appid:%d.\n", wAppID));
}

BOOL CUmsUeInst::ObjectInit(u32 wParam, u32 lParam)
{
	if (m_bInit)
	{
		return TRUE;
	}
	SetLogTitle("[CUmsUeInst]");

	if(NULL != m_pcUmcHandler || NULL != m_pcToolHandler)	
	{
		return TRUE;
	}

	m_dwServiceInst = g_cUmsUeCfg.m_dwServiceInst;
	m_dwUmcAppID	= g_cUmsUeCfg.m_dwUeInst;
	m_dwToolAppID	= g_cUmsUeCfg.m_dwToolInst;

	m_pcUmcHandler  = new CUmcHandler(this, m_dwUmcAppID);
	m_pcToolHandler = new CToolHandler(this, m_dwToolAppID);

	if (NULL == m_pcUmcHandler || NULL == m_pcToolHandler)
	{
		return FALSE;
	}

	m_dwListenNode  = OspCreateTcpNode(0, g_cUmsUeCfg.m_wListenPort);
	if (INVALID_SOCKET == m_dwListenNode)
	{
		return FALSE;
	}

	m_bInit	= TRUE;
#ifdef _USE_XMPUEQP_
	InitMediaClient();
#endif

	return TRUE;
}


void CUmsUeInst::ObjectExit()
{
	if (NULL != m_pcUmcHandler)
	{
		delete m_pcUmcHandler;
		m_pcUmcHandler = NULL;
	}

	if (NULL != m_pcToolHandler)
	{
		delete m_pcToolHandler;
		m_pcToolHandler = NULL;
	}

	CUmsObject::ObjectExit();
}

void CUmsUeInst::OnDisconnect(CMessage *const ptMsg)
{
	if (NULL != m_pcUmcHandler)
	{
		m_pcUmcHandler->PreHandler(ptMsg);
	}

	if (NULL != m_pcToolHandler)
	{
		m_pcToolHandler->PreHandler(ptMsg);
	}
}

u16 CUmsUeInst::NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	
	if (NULL != body)
	{
		cMsg.CatBody(body,bodyLen);
	}
	return cMsg.Post(m_dwServiceInst, 0, UMS_UE_APP_INST);
}

u16 CUmsUeInst::NotifyMsgToHdu(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	
	if (NULL != body)
	{
		cMsg.CatBody(body,bodyLen);
	}
	return cMsg.Post(UMS_BRDSSN_APP_INST, 0, UMS_UE_APP_INST);
}


enum tp_ums_ue_dump
{
	dump_show_login,
	dump_show_tool_login,
};


void CUmsUeInst::InstanceDump(u32 wParam)
{
	switch(wParam)
	{
	case dump_show_login:
		{
			ShowLogin();
		}
		break;

	case dump_show_tool_login:
		{
			ShowToolLogin();
		}
		break;
	default:
		break;
	}
}


void CUmsUeInst::ShowLogin()
{
	m_pcUmcHandler->ShowLogin();
}

void CUmsUeInst::ShowToolLogin()
{
	m_pcToolHandler->ShowLogin();
}


API void uelogin()
{
	OspInstDump(AID_UMSUE_APP, 1, dump_show_login);
}

API void toollogin()
{
	OspInstDump(AID_UMSUE_APP, 1, dump_show_tool_login);
}

API void addumcuser(s8* pszUserName,s8* pszUserPwd)
{
	if (NULL == pszUserName || NULL == pszUserPwd)
	{
		return ;
	}
	
	CUserFullInfo cUser;
	cUser.SetName(pszUserName);
	cUser.SetPassword(pszUserPwd);
	OspPost(UMS_UE_APP_INST,ev_UMSAddUserReq,&cUser,sizeof(cUser),0,MAKEIID(AID_UMSTOOL2UMS_APP, 0));
	return ;

}

API void umclogin(s8* pszUserName,s8* pszUserPwd)
{
	if (NULL == pszUserName || NULL == pszUserPwd)
	{
		return ;
	}
	
	CUserFullInfo cUser;
	cUser.SetActor(UM_ADMIN);
	cUser.SetName(pszUserName);
	cUser.SetPassword(pszUserPwd);
	OspPost(UMS_UE_APP_INST,ev_UMSLoginReq,&cUser,sizeof(cUser),0,MAKEIID(AID_UMSTOOL2UMS_APP, 0));
	return ;
	
}

API void mdyumcuser(s8* pszUserName,s8* pszUserPwd)
{
	if (NULL == pszUserName || NULL == pszUserPwd)
	{
		return ;
	}
	
	CUserFullInfo cUser;
	cUser.SetActor(UM_ADMIN);
	cUser.SetName(pszUserName);
	cUser.SetPassword(pszUserPwd);
	OspPost(UMS_UE_APP_INST,ev_UMSChangePWDReq,&cUser,sizeof(cUser),0,MAKEIID(AID_UMSTOOL2UMS_APP, 0));
	return ;
	
}

API void delumcuser(s8* pszUserName, u32 wUserId)
{
	if (NULL == pszUserName)
	{
		return ;
	}

	CUserFullInfo cUser;
	cUser.SetName(pszUserName);
	cUser.m_dwGuid = wUserId;
	OspPost(UMS_UE_APP_INST,ev_UMSDelUserReq,&cUser,sizeof(cUser),0,MAKEIID(AID_UMSTOOL2UMS_APP, 0));
	return ;
}

#define  VER_umsue_ver	UMS_VerID
API void uever()
{
	msgprint("umsue ver: %s  compile time: %s:%s\n",
		VER_umsue_ver, __DATE__,  __TIME__);
}

API void uehelp()
{
	msgprintnotime("uever()                        --- umsue版本号\n");
	msgprintnotime("uelogin()                      --- 显示所有登录用户\n");
	msgprintnotime("toollogin()                    --- 显示维护工具登录用户\n");
	msgprintnotime("addumcuser(s8*,s8*)            --- 添加umc用户\n");
	msgprintnotime("delumcuser(s8*,u32)            --- 删除umc用户\n");
}

void regist_ums_ue_commond()
{
#ifdef _LINUX_
	OspRegCommand("uehelp", (void*)uehelp, "uehelp()");
	OspRegCommand("uever", (void*)uever, "uever(int)");
	OspRegCommand("uelogin", (void*)uelogin, "uelogin(int)");
	OspRegCommand("toollogin", (void*)toollogin, "toollogin(int)");
	OspRegCommand("addumcuser",(void*)addumcuser,  "addumcuser(s8*,s8*)");
	OspRegCommand("delumcuser",(void*)delumcuser,  "delumcuser(s8*,u32)");
#endif
}


 