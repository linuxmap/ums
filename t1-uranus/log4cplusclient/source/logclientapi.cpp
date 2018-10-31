#include "logclientapi.h"
#include "logclient.h"

namespace log4cpclient{

	LOGCLIENT_API BOOL32 Init( std::string strLogCfgName, BOOL32 bIsLogTaskOn /*= TRUE*/, BOOL32 bIsTelnetPrintOn /*= TRUE*/ )
	{
		return CLogClient::GetInstance()->Init(strLogCfgName, bIsLogTaskOn, bIsTelnetPrintOn);
	}

	LOGCLIENT_API BOOL32 RegMod( std::string strModName )
	{
		return CLogClient::GetInstance()->RegLogger(strModName);
	}

	LOGCLIENT_API void Debug( std::string strModName, const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(strModName, emLogDebug, abuf, dwLen);		
	}

	LOGCLIENT_API void Info( std::string strModName, const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(strModName, emLogInfo, abuf, dwLen);
	}

	LOGCLIENT_API void Warn( std::string strModName, const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(strModName, emLogWarn, abuf, dwLen);
	}

	LOGCLIENT_API void Error( std::string strModName, const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(strModName, emLogError, abuf, dwLen);
	}

	LOGCLIENT_API void Fatal( std::string strModName, const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(strModName, emLogFatal, abuf, dwLen);
	}

	LOGCLIENT_API BOOL32 Exit()
	{
		return CLogClient::GetInstance()->Exit();
	}

	LOGCLIENT_API void SetConsoleLog( BOOL32 bOnoff )
	{
		CLogClient::GetInstance()->SetConsoleLog(bOnoff);
	}

	LOGCLIENT_API void SetDebugOn()
	{
		CLogClient::GetInstance()->SetLogLevel(emLogDebug);
	}

	LOGCLIENT_API void SetInfoOn()
	{
		CLogClient::GetInstance()->SetLogLevel(emLogInfo);
	}

	LOGCLIENT_API void SetWarnOn()
	{
		CLogClient::GetInstance()->SetLogLevel(emLogWarn);
	}

	LOGCLIENT_API void SetErrorOn()
	{
		CLogClient::GetInstance()->SetLogLevel(emLogError);
	}

	LOGCLIENT_API void SetFatalOn()
	{
		CLogClient::GetInstance()->SetLogLevel(emLogFatal);
	}

	LOGCLIENT_API void SetLogOff()
	{
		CLogClient::GetInstance()->SetLogOff();
	}


	LOGCLIENT_API void ShowInfo()
	{
		CLogClient::GetInstance()->Show();
	}

	CLogBase::CLogBase()
	{
		m_strModName.clear();
	}

	CLogBase::~CLogBase()
	{
		m_strModName.clear();
	}

	BOOL32 CLogBase::SetModName(std::string strModName)
	{
		if (CLogClient::GetInstance()->RegLogger(strModName))
		{
			m_strModName.assign(strModName);
			return TRUE;
		}
		return FALSE;
	}

	void CLogBase::LogDebug( const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(m_strModName, emLogDebug, abuf, dwLen);
	}

	void CLogBase::LogInfo( const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(m_strModName, emLogInfo, abuf, dwLen);
	}

	void CLogBase::LogWarn( const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(m_strModName, emLogWarn, abuf, dwLen);
	}

	void CLogBase::LogError( const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(m_strModName, emLogError, abuf, dwLen);
	}

	void CLogBase::LogFatal( const s8* format,... )
	{
		s8 abuf[MAX_ONE_LOG_LEN+1] = {0};
		va_list args;
		va_start(args,format);
		u32 dwLen = vsnprintf(abuf, MAX_ONE_LOG_LEN-1, format, args);
		va_end(args);
		if (0 >= dwLen || MAX_ONE_LOG_LEN <= dwLen)
		{
			return;
		}
		CLogClient::GetInstance()->Log(m_strModName, emLogFatal, abuf, dwLen);
	}
}