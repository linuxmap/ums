#include "logclient.h"
#include "log4cplus/logger.h"
#include "log4cplus/socketappender.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/configurator.h"
#include "logclientappender.h"
#include "logclientfilter.h"

#define ENTERLOG	OspSemTake(m_semLc)
#define EXITLOG 	OspSemGive(m_semLc)

#define LOGLENMAX(a,b)    (((a) > (b)) ? (a) : (b))
#define LOGLENMIN(a,b)    (((a) < (b)) ? (a) : (b))

#ifdef _DEBUG
u32			g_dwLocalLogLevel = (u32)emLogInfo;
#else
u32			g_dwLocalLogLevel = (u32)emLogWarn;
#endif

BOOL32		g_bConsoleLogOn = TRUE;

s8* GetLogLevelName(u32 dwLogLevel)
{
	switch(dwLogLevel)
	{
	case emLogDebug:
		return "debug";
	case emLogInfo:
		return "info";
	case emLogWarn:
		return "warn";
	case emLogError:
		return "error";
	case emLogFatal:
		return "fatal";
	default:
		return "unkown";
	}
	return "unkown";
}

void*  LogHandleTask(void*)
{
	CLogClient::GetInstance()->LogQueOut();
	return 0;
}
CLogClient CLogClient::s_cLogClient;
CLogClient::CLogClient()
{
//	printf("CLogClient.\n");
	OspSemBCreate(&m_semLc);
	m_bInited = FALSE;
	m_bTelnetPrintOn = FALSE;
	m_dwMailBoxRead = 0;
	m_dwMailBoxWrite = 0;
	m_dwTaskID = 0;
	m_hTask = 0;
}

CLogClient::~CLogClient()
{
//	printf("~CLogClient.\n");
	m_dwMailBoxRead = 0;
	m_dwMailBoxWrite = 0;
	m_dwTaskID = 0;
	m_hTask = 0;
	m_bTelnetPrintOn = FALSE;
	m_bInited = FALSE;
	OspSemDelete(m_semLc);
}

CLogClient* CLogClient::GetInstance()
{
	return &s_cLogClient;
}

BOOL32 CLogClient::Init( std::string strLogCfg, BOOL32 bIsLogTaskOn /*= TRUE*/, BOOL32 bIsTelnetPrintOn /*= TRUE*/ )
{
	ENTERLOG;

	if (m_bInited)
	{
		EXITLOG;
		return TRUE;
	}

	log4cplus::PropertyConfigurator::doConfigure(strLogCfg);

	if (bIsLogTaskOn)
	{
		if (!OspCreateMailbox("LOCCLIENT", LOGHANDLE_MAX_WAITING, sizeof(TLogHandleMsgAddr), &m_dwMailBoxRead, &m_dwMailBoxWrite))
		{
			m_dwMailBoxRead = 0;
			m_dwMailBoxWrite = 0;
			EXITLOG;
			return FALSE;
		}

		m_hTask = OspTaskCreate(LogHandleTask, "LogHandleTask", 
			LOGHANDLETASK_PRI, LOGHANDLETASK_STACKSIZE, NULL, 0, &m_dwTaskID);
		if (0==m_hTask)
		{
			OspCloseMailbox(m_dwMailBoxRead, m_dwMailBoxWrite);
			m_dwMailBoxRead = 0;
			m_dwMailBoxWrite = 0;
			m_dwTaskID = 0;
			EXITLOG;
			return FALSE;
		}
	}

	if (bIsTelnetPrintOn)
	{
		if (!IsOspInitd())
			OspInit(TRUE);

		std::string strPattern(LOG_PATTERN_DEF);
		log4cplus::Logger cLogRoot = log4cplus::Logger::getRoot();
		
		log4cplus::SharedAppenderPtr pcTelnetAppender = log4cplus::SharedAppenderPtr(new CTelnetAppender());
		pcTelnetAppender->setName("LOG_TELNETOUT");
		pcTelnetAppender->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(strPattern)));
		log4cplus::spi::FilterPtr pcTelnetAppenderFilter = log4cplus::spi::FilterPtr(new CLogLevelAppenderFilter());
		pcTelnetAppender->setFilter(pcTelnetAppenderFilter);
		pcTelnetAppender->setThreshold(emLogDebug);

		cLogRoot.addAppender(pcTelnetAppender);
		m_bTelnetPrintOn = TRUE;
	}

	std::string strPattern(LOG_PATTERN_DEF);
	log4cplus::Logger cLogRoot = log4cplus::Logger::getRoot();

	log4cplus::SharedAppenderPtr pcConsoleAppender = log4cplus::SharedAppenderPtr(new CLocalConsoleAppender());
	pcConsoleAppender->setName("LOG_CONSOLEOUT");
	pcConsoleAppender->setLayout(std::auto_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(strPattern)));
	log4cplus::spi::FilterPtr pcConsoleAppenderFilter = log4cplus::spi::FilterPtr(new CLogLevelAppenderFilter());
	pcConsoleAppender->setFilter(pcConsoleAppenderFilter);
	pcConsoleAppender->setThreshold(emLogDebug);

	cLogRoot.addAppender(pcConsoleAppender);


// 	log4cplus::SharedAppenderPtrList appendlist = log4cplus::Logger::getRoot().getAllAppenders();
// 	printf("size:%d.\n", appendlist.size());
// 	for(u16 index = 0; index < appendlist.size(); index++)
// 	{
// 		printf("[%d-%s].\n", index, appendlist[index].get()->getName().c_str());
// 	}

	m_bInited = TRUE;
	EXITLOG;
	return TRUE;
}

BOOL32 CLogClient::Exit()
{
	ENTERLOG;
	if (!m_bInited)
	{
		return FALSE;
	}
	log4cplus::Logger::shutdown();
	m_bInited = FALSE;
	EXITLOG;
	return TRUE;
}

BOOL32 CLogClient::RegLogger(std::string strLogger)
{
	ENTERLOG;
	if (!m_bInited)
	{
		EXITLOG;
		return FALSE;
	}

	if (IsLoggerReged(strLogger))
	{
		EXITLOG;
		return TRUE;
	}

	log4cplus::Logger::getInstance(strLogger);
	
	EXITLOG;
	return TRUE;
}

BOOL32 CLogClient::Log( std::string strLogger, EmLogLevel emLevel, const s8* pLogMsg, u32 dwLogLen )
{
	if (!m_bInited)
	{
		return FALSE;
	}

	if (0 == m_hTask)
	{
		if (!IsLoggerReged(strLogger))
		{
			return FALSE;		
		}
		std::string strLogMsg(pLogMsg);
		log4cplus::Logger::getInstance(strLogger).log(emLevel, strLogMsg);
		return TRUE;
	}

	TLogHandleMsgHead	tLogHead;
	TLogHandleMsgAddr	tLogMsg;
	s8*				pMsg = NULL;

	memcpy(tLogHead.m_achLogModName, strLogger.c_str(), LOGLENMIN(strLogger.length(), MAX_LOGMODNAME_LEN));
	tLogHead.m_emLogLevel = emLevel;
	tLogHead.m_dwLogLen = dwLogLen;

	pMsg = (s8*)OspAllocMem(sizeof(tagTLogHandleMsgHead)+dwLogLen+1);
	if (NULL == pMsg)
	{
		OspPrintf(1, 0, "CLogClient::Log UnifyAllocMem failed!.\n");
		return FALSE;
	}

	memcpy(pMsg, &tLogHead, sizeof(TLogHandleMsgHead));

	if (dwLogLen > 0 && NULL != pLogMsg)
	{
		memcpy(pMsg+sizeof(TLogHandleMsgHead), pLogMsg, dwLogLen);
		pMsg[sizeof(TLogHandleMsgHead)+dwLogLen] = '\0';
	}

	tLogMsg.m_dwAddress = (u32)pMsg;

	BOOL32 bRet = OspSndMsg(m_dwMailBoxWrite, (char*)&tLogMsg, sizeof(tLogMsg), OSP_NO_WAIT);
	if (!bRet)
	{
		OspFreeMem((void*)pMsg);
		OspPrintf(1, 0, "CLogClient::Log UnifySendMsgToMailbox failed!\n");
		return FALSE;
	}

	return TRUE;
}

void CLogClient::LogQueOut()
{
//	OspPrintf(1, 0, "LogQueOut thread id:%d.\n", OspTaskSelfID());
	TLogHandleMsgAddr tLogMsg;
	TLogHandleMsgHead* ptLogHead = NULL;
	s8* pLogMsg = NULL;
	BOOL32	bRet = FALSE;
	u32		dwRcvLen = 0;

	do 
	{
		tLogMsg.Clear();
		bRet = OspRcvMsg(m_dwMailBoxRead, 0xffffffff, (char*)&tLogMsg, sizeof(tLogMsg), &dwRcvLen);
		if (!bRet 
			|| dwRcvLen != sizeof(tLogMsg) 
			|| 0 == tLogMsg.m_dwAddress)
		{
			OspPrintf(1, 0, "CLogClient::LogQueOut UnifyRcvMsgFromMailbox failed! dwRcvLen:%d, addr:%p.\n", 
				dwRcvLen, tLogMsg.m_dwAddress);
			continue;
		}

		ptLogHead = (TLogHandleMsgHead*)tLogMsg.m_dwAddress;
		if (0 == ptLogHead->m_dwLogLen)
		{
			OspFreeMem((void*)tLogMsg.m_dwAddress);
			continue;
		}
		pLogMsg = (s8*)(ptLogHead+1);

		LogLog(ptLogHead->m_achLogModName, ptLogHead->m_emLogLevel, pLogMsg);
		OspFreeMem((void*)tLogMsg.m_dwAddress);

	} while (1);
	OspTaskExit();
	return;
}

void CLogClient::SetConsoleLog( BOOL32 bOnoff )
{
	g_bConsoleLogOn = bOnoff;
}

void CLogClient::SetLogLevel( EmLogLevel emLevel )
{
	g_dwLocalLogLevel = (u32)emLevel;
}

void CLogClient::SetLogOff()
{
	g_dwLocalLogLevel = (u32)(emLogLevelEnd);
}

void CLogClient::Show()
{
	OspPrintf(1, 0, "[CLogClient info]\n");
	OspPrintf(1, 0, "  m_bInited:%d.\n", m_bInited);
	OspPrintf(1, 0, "  m_bTelnetPrintOn:%d.\n", m_bTelnetPrintOn);
	OspPrintf(1, 0, "  m_dwMailBoxRead:%d.\n", m_dwMailBoxRead);
	OspPrintf(1, 0, "  m_dwMailBoxWrite:%d.\n", m_dwMailBoxWrite);
	OspPrintf(1, 0, "  m_dwTaskID:%u.\n", m_dwTaskID);
	OspPrintf(1, 0, "  m_hTask:%u.\n", m_hTask);
	OspPrintf(1, 0, "  g_bConsoleLogOn:%d.\n", g_bConsoleLogOn);
	OspPrintf(1, 0, "  g_dwLocalLogLevel:%s.\n", GetLogLevelName(g_dwLocalLogLevel));
	log4cplus::SharedAppenderPtrList appendlist = log4cplus::Logger::getRoot().getAllAppenders();
	OspPrintf(1, 0, "[CLogClient] appendlist size:%d.\n", appendlist.size());
	for(u16 index = 0; index < appendlist.size(); index++)
	{
		OspPrintf(1, 0, "  [%d-%s].\n", index, appendlist[index].get()->getName().c_str());
	}
	OspPrintf(1, 0, "\n");
	return;
}

BOOL32 CLogClient::IsLoggerReged( std::string strLogger )
{
	log4cplus::LoggerList lstLoggers = log4cplus::Logger::getCurrentLoggers();	
	u16 i = 0;
	BOOL32 bRet = FALSE;
	for (i = 0; i < lstLoggers.size(); i++)
	{
		if (strLogger == lstLoggers[i].getName())
		{
			bRet = TRUE;
			break;
		}
	}
	return bRet;
}

void CLogClient::LogLog( const s8* pLogMod, EmLogLevel emLevel, const s8* pLogMsg )
{
	std::string strLogger(pLogMod);
	std::string strLogMsg(pLogMsg);

	if (!IsLoggerReged(strLogger))
	{
		return;		
	}

	log4cplus::Logger::getInstance(strLogger).log(emLevel, strLogMsg);
	return;
}
