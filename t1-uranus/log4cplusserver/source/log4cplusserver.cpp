#include <cstdlib>
#include <list>
#include <iostream>
#include <log4cplus/configurator.h>
#include <log4cplus/socketappender.h>
#include <log4cplus/helpers/socket.h>
#include <log4cplus/thread/threads.h>
#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/logger.h>
#include <log4cplus/thread/syncprims.h>

#include "osp.h"
#include "log4cplusserver.h"

extern u16 g_wListenPort;

#define  VER_LOG4CPLUSSERVER   "0.0.0.0.1"
API void ver()
{
	OspPrintf(1, 0, "log4cplusserver ver:%s, compile time:%s %s.\n",
		VER_LOG4CPLUSSERVER, __DATE__,  __TIME__);
}

API void help()
{
	OspPrintf(1, 0, "showlogserver  ------  show log4cplusserver info\n");
	OspPrintf(1, 0, "\n");
	ver();
}

API void showlogserver()
{
	OspPrintf(1,0,"[log4cplusserver info]\n");
	OspPrintf(1, 0, "  g_wListenPort:%d.\n", g_wListenPort);

	log4cplus::SharedAppenderPtrList appendlist = log4cplus::Logger::getRoot().getAllAppenders();
	OspPrintf(1, 0, "  appendlist size:%d.\n", appendlist.size());
	u16 index = 0;
	for(index = 0; index < appendlist.size(); index++)
	{
		OspPrintf(1, 0, "    [%d-%s].\n", index, appendlist[index].get()->getName().c_str());
	}
	
	log4cplus::LoggerList lstLoggers = log4cplus::Logger::getCurrentLoggers();
	OspPrintf(1, 0, "  logger size:%d.\n", lstLoggers.size());
	for (index = 0; index < lstLoggers.size(); index++)
	{
		OspPrintf(1, 0, "    [%d-%s].\n", index, lstLoggers[index].getName().c_str());
	}

	OspPrintf(1, 0, "\n");
	CLog4plusclientMgr::GetInstance()->Show();
}

#ifdef _LINUX_
#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

u32 GetSelfTaskId()
{
#ifdef _MSC_VER
	return GetCurrentThreadId();
#endif

#ifdef _LINUX_
	return (u32)gettid();
#endif
}


CLog4plusclientMgr CLog4plusclientMgr::s_cLog4plusClientMgr;
CLog4plusclientMgr::CLog4plusclientMgr()
{
	//	printf("CLog4plusclientMgr.\n");
	m_mapClientInfo.clear();
}

CLog4plusclientMgr::~CLog4plusclientMgr()
{
	//	printf("~CLog4plusclientMgr.\n");
	m_mapClientInfo.clear();
}

CLog4plusclientMgr* CLog4plusclientMgr::GetInstance()
{
	return &s_cLog4plusClientMgr;
}

BOOL32 CLog4plusclientMgr::AddClient( std::string strClient, u32 dwTaskId )
{
	m_mapClientInfo[dwTaskId] = strClient;
	return TRUE;
}

BOOL32 CLog4plusclientMgr::DelClient( std::string strClient, u32 dwTaskId )
{
	m_mapClientInfo.erase(dwTaskId);
	return TRUE;
}

void CLog4plusclientMgr::Show()
{
	std::map<u32, std::string>::iterator iter;
	u16 wIndex = 0;
	OspPrintf(1,0,"[client list]\n");
	for (iter = m_mapClientInfo.begin(); iter != m_mapClientInfo.end(); iter++)
	{
		wIndex++;
		OspPrintf(1, 0, "  [%d] TaskId:%u, Client:%s.\n", wIndex, iter->first, iter->second.c_str());
	}
}