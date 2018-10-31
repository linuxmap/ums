#ifndef _LOGCLIENTAPI_H_
#define _LOGCLIENTAPI_H_

// for win32 dll
#if (defined(WIN32) || defined(_WIN32) ) && defined(_USRLOG4CPLUSCLIENTDLL)

#ifdef LOG4CPLUSCLIENTDLL_EXPORTS
#define LOGCLIENT_API __declspec(dllexport)
#else
#define LOGCLIENT_API __declspec(dllimport)
#endif

#else  // 其他平台的，或者是静态链接

#define LOGCLIENT_API 

#endif 
// end for win32 dll

#include <string>
#include "kdvtype.h"

namespace log4cpclient{

	// init接口必须首先调用！

	// log配置文件可配置本地文件 远端服务器等输出方式
	LOGCLIENT_API BOOL32 Init(std::string strLogCfgName, BOOL32 bIsLogTaskOn = TRUE, BOOL32 bIsTelnetPrintOn = TRUE);

	LOGCLIENT_API BOOL32 Exit();

	// 打印模块注册接口，必须先注册，再调用打印接口，否则无效
	LOGCLIENT_API BOOL32 RegMod(std::string strModName);
	
	// 打印接口
	LOGCLIENT_API void Debug(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Info(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Warn(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Error(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Fatal(std::string strModName, const s8* format,...);

	// 设置是否开启consolelog，默认是开启的
	LOGCLIENT_API void SetConsoleLog(BOOL32 bOnoff);

	// 打印级别控制接口
	// 只能控制telnet console输出级别
	LOGCLIENT_API void	 SetDebugOn(); // 输出debug info warn error fatal
	LOGCLIENT_API void	 SetInfoOn();  // 输出info warn error fatal
	LOGCLIENT_API void	 SetWarnOn();  // 输出warn error fatal
	LOGCLIENT_API void	 SetErrorOn(); // 输出error fatal
	LOGCLIENT_API void	 SetFatalOn(); // 输出fatal
	LOGCLIENT_API void	 SetLogOff();  // 所有层级均不输出，慎用！！！

	LOGCLIENT_API void   ShowInfo(); // 静态show打印

	// 打印基类
	class LOGCLIENT_API CLogBase
	{
	protected:
		CLogBase();
		virtual ~CLogBase();

		// 必须先设置，否则打印接口无效
		BOOL32 SetModName(std::string strModName); 	
		
		void LogDebug(const s8* format,...);
		void LogInfo(const s8* format,...);
		void LogWarn(const s8* format,...);
		void LogError(const s8* format,...);
		void LogFatal(const s8* format,...);

	protected:
		std::string m_strModName;
	};
}

#endif//_LOGCLIENTAPI_H_