#include "osp.h"
#include "logclientapi.h"

#include "common.h"
#include "server.h"
#include "client.h"

#ifdef _MSC_VER
#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "log4cplus.lib")
#pragma comment(lib, "log4cplusclient.lib")
#pragma comment(lib, "protobuf.lib")
#pragma comment(lib, "protobufmsg.lib")
#endif

#define LOG_CONFIG_NAME			"./log.cfg"

std::string  g_strMainLog("main");

BOOL32 g_bRun = TRUE;
BOOL32 g_bShowRun = FALSE;

API void quit()
{
	g_bRun = FALSE;
	log4cpclient::Info(g_strMainLog, "quit g_bRun=%d.", g_bRun);
}

API void showrun()
{
	g_bShowRun = g_bShowRun?FALSE:TRUE;
	log4cpclient::Info(g_strMainLog, "showrun g_bShowRun=%d.", g_bShowRun);
}

API void viewreq(u16 wConfID, u16 wSrcId, u16 wSrcIndex, u16 wDstId, u16 wDstIndex, u32 dwType)
{
	TViewReq tReq;
	tReq.m_wConfId = wConfID;
	tReq.m_wSrcEpId = wSrcId;
	tReq.m_wSrcScreenIndex = wSrcIndex;
	tReq.m_wDstEpId = wDstId;
	tReq.m_wDstScreenIndex = wDstIndex;
	if (dwType <= emViewType_Vmp)
	{
		tReq.m_emViewType = (EmViewType)dwType;
	}
	ViewReq(tReq);
}

int main()
{
	if (!OspInit(TRUE, 2520))
	{
		return -1;
	}
	OspDelay(100);

	std::string strLogCfg(LOG_CONFIG_NAME);
	if (!log4cpclient::Init(strLogCfg, TRUE))
	{
		return -1;
	}

#ifdef _LINUX_
	OspRegCommand("quit", (void*)quit, "quit");
	OspRegCommand("showrun", (void*)showrun, "showrun");
	OspRegCommand("viewreq", (void*)viewreq, "viewreq");
#endif

#ifdef _DEBUG
	log4cpclient::SetDebugOn();
#else
	log4cpclient::SetInfoOn();
#endif

	log4cpclient::RegMod(g_strMainLog);
	log4cpclient::Info(g_strMainLog, "runnig! main thread id:%d.", OspTaskSelfID());

	// server run
	ServerRun();

	// client run
	ClientRun();

	while(g_bRun)
	{
		if (g_bShowRun)
		{
			log4cpclient::Info(g_strMainLog, "still runnig!");
		}
		OspDelay(5000);
	}

	log4cpclient::Info(g_strMainLog, "quit...");

	OspQuit();
	OspDelay(200);

	return 0;
}