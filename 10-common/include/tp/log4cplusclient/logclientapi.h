#ifndef _LOGCLIENTAPI_H_
#define _LOGCLIENTAPI_H_

// for win32 dll
#if (defined(WIN32) || defined(_WIN32) ) && defined(_USRLOG4CPLUSCLIENTDLL)

#ifdef LOG4CPLUSCLIENTDLL_EXPORTS
#define LOGCLIENT_API __declspec(dllexport)
#else
#define LOGCLIENT_API __declspec(dllimport)
#endif

#else  // ����ƽ̨�ģ������Ǿ�̬����

#define LOGCLIENT_API 

#endif 
// end for win32 dll

#include <string>
#include "kdvtype.h"

namespace log4cpclient{

	// init�ӿڱ������ȵ��ã�

	// log�����ļ������ñ����ļ� Զ�˷������������ʽ
	LOGCLIENT_API BOOL32 Init(std::string strLogCfgName, BOOL32 bIsLogTaskOn = TRUE, BOOL32 bIsTelnetPrintOn = TRUE);

	LOGCLIENT_API BOOL32 Exit();

	// ��ӡģ��ע��ӿڣ�������ע�ᣬ�ٵ��ô�ӡ�ӿڣ�������Ч
	LOGCLIENT_API BOOL32 RegMod(std::string strModName);
	
	// ��ӡ�ӿ�
	LOGCLIENT_API void Debug(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Info(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Warn(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Error(std::string strModName, const s8* format,...);
	LOGCLIENT_API void Fatal(std::string strModName, const s8* format,...);

	// �����Ƿ���consolelog��Ĭ���ǿ�����
	LOGCLIENT_API void SetConsoleLog(BOOL32 bOnoff);

	// ��ӡ������ƽӿ�
	// ֻ�ܿ���telnet console�������
	LOGCLIENT_API void	 SetDebugOn(); // ���debug info warn error fatal
	LOGCLIENT_API void	 SetInfoOn();  // ���info warn error fatal
	LOGCLIENT_API void	 SetWarnOn();  // ���warn error fatal
	LOGCLIENT_API void	 SetErrorOn(); // ���error fatal
	LOGCLIENT_API void	 SetFatalOn(); // ���fatal
	LOGCLIENT_API void	 SetLogOff();  // ���в㼶������������ã�����

	LOGCLIENT_API void   ShowInfo(); // ��̬show��ӡ

	// ��ӡ����
	class LOGCLIENT_API CLogBase
	{
	protected:
		CLogBase();
		virtual ~CLogBase();

		// ���������ã������ӡ�ӿ���Ч
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