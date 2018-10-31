#ifndef _LOGCLIENT_H_
#define _LOGCLIENT_H_

#include <string>
#include "osp.h"
#include "log4cplus/appender.h"

#define MAX_LOGMODNAME_LEN		16
#define MAX_ONE_LOG_LEN			512
#define LOG_PATTERN_DEF			"%m"
//#define LOG_PATTERN_DEF			"[%c][%p] %D{%Y/%m/%d %H:%M:%S:%q} [%t] - %m%n"

#define LOGHANDLETASK_STACKSIZE				(u32)(400<<10)
#define LOGHANDLETASK_PRI					(u8)200
#define LOGHANDLE_MAX_WAITING				1024

enum EmLogLevel
{
	emLogDebug = log4cplus::DEBUG_LOG_LEVEL,
	emLogInfo = log4cplus::INFO_LOG_LEVEL,
	emLogWarn = log4cplus::WARN_LOG_LEVEL,
	emLogError = log4cplus::ERROR_LOG_LEVEL,
	emLogFatal = log4cplus::FATAL_LOG_LEVEL,

	emLogLevelEnd = log4cplus::OFF_LOG_LEVEL,
};

typedef struct tagTLogHandleMsgAddr {
	//邮箱消息地址
	u32 m_dwAddress;

	tagTLogHandleMsgAddr()
	{
		m_dwAddress = 0;
	}

	void Clear()
	{
		m_dwAddress = 0;
	}

}TLogHandleMsgAddr;

//log消息头定义
typedef struct tagTLogHandleMsgHead {

	s8				m_achLogModName[MAX_LOGMODNAME_LEN+1];
	EmLogLevel		m_emLogLevel;
	u32				m_dwLogLen;

	tagTLogHandleMsgHead()
	{
		memset(this, 0, sizeof(tagTLogHandleMsgHead));
	}

} TLogHandleMsgHead;

class CLogClient
{
public:
	virtual ~CLogClient();
	static CLogClient* GetInstance();

public:
	// 外部接口
	BOOL32	Init(std::string strLogCfg, BOOL32 bIsLogTaskOn = TRUE, BOOL32 bIsTelnetPrintOn = TRUE);
	BOOL32  Exit();
	BOOL32	RegLogger(std::string strLogger);
	BOOL32	Log( std::string strLogger, EmLogLevel emLevel, const s8* pLogMsg, u32 dwLogLen);
	void    SetConsoleLog(BOOL32 bOnoff);
	void	SetLogLevel(EmLogLevel emLevel);
	void	SetLogOff();
	void	Show();

	// 内部线程函数
	void	LogQueOut();

protected:
	BOOL32	IsLoggerReged(std::string strLogger);
	void	LogLog(const s8* pLogMod, EmLogLevel emLevel, const s8* pLogMsg);

private:
	CLogClient();
	CLogClient(const CLogClient&);
	CLogClient& operator = (const CLogClient&);

	static CLogClient				s_cLogClient;

	SEMHANDLE						m_semLc;
	BOOL32							m_bInited;
	BOOL32							m_bTelnetPrintOn;

	u32								m_dwMailBoxRead;
	u32								m_dwMailBoxWrite;

	//任务号
	u32								m_dwTaskID;
	//任务handle
	TASKHANDLE						m_hTask;
};

#endif //_LOGCLIENT_H_