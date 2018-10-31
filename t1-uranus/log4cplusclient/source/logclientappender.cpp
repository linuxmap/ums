#include "osp.h"
#include <sstream>
#include "log4cplus/streams.h"
#include <log4cplus/spi/loggingevent.h>
#include "logclientappender.h"
#include "logclient.h"


#define LOGCOLOR_NONE			"\033[m"            ///< ��

#define LOGCOLOR_RED			"\033[31m"			///< ��ɫ
#define LOGCOLOR_GREEN			"\033[32m"			///< ��ɫ
#define LOGCOLOR_YELLOW			"\033[33m"			///< ��ɫ
#define LOGCOLOR_BLUE			"\033[34m"			///< ��ɫ
#define LOGCOLOR_PURPLE			"\033[35m"			///< ��ɫ
#define LOGCOLOR_CYAN			"\033[36m"			///< ��ɫ
#define LOGCOLOR_WHITE			"\033[37m"			///< ��ɫ

#define LOGCOLOR_LIGHT_RED		"\033[1;31m"		///< ����ɫ
#define LOGCOLOR_LIGHT_GREEN	"\033[1;32m"		///< ����ɫ
#define LOGCOLOR_LIGHT_YELLOW	"\033[1;33m"		///< ����ɫ
#define LOGCOLOR_LIGHT_BLUE		"\033[1;34m"		///< ����ɫ
#define LOGCOLOR_LIGHT_PURPLE	"\033[1;35m"		///< ����ɫ
#define LOGCOLOR_LIGHT_CYAN		"\033[1;36m"		///< ����ɫ
#define LOGCOLOR_LIGHT_WHITE	"\033[1;37m"		///< ����ɫ


const s8 *g_pchLogColorNONE_Log4 = LOGCOLOR_NONE;				//����ɫ
const s8 *g_pchLogColorFatal_Log4 = LOGCOLOR_LIGHT_RED;			//fatal��	����ɫ
const s8 *g_pchLogColorError_Log4 = LOGCOLOR_PURPLE;				//error��	��ɫ
const s8 *g_pchLogColorWarn_Log4  = LOGCOLOR_YELLOW;				//warn��	��ɫ
const s8 *g_pchLogColorInfo_Log4  = LOGCOLOR_CYAN;				//info��	��ɫ
const s8 *g_pchLogColorDebug_Log4 = LOGCOLOR_LIGHT_GREEN;		//debug��	����ɫ

CTelnetAppender::CTelnetAppender()
{

}

CTelnetAppender::~CTelnetAppender()
{
	destructorImpl();
}

void CTelnetAppender::close()
{
	closed = true;
}

void CTelnetAppender::append( const log4cplus::spi::InternalLoggingEvent& event )
{
	log4cplus::tostringstream buf;
	layout->formatAndAppend(buf, event);
	log4cplus::tstring sz = buf.str();

	const s8* szColor = NULL;

	u32 dwLogLevel = (u32)event.getLogLevel();
	switch(dwLogLevel)
	{
	case emLogDebug:
		szColor = g_pchLogColorDebug_Log4;
		break;
	case emLogInfo:
		szColor = g_pchLogColorInfo_Log4;
		break;
	case emLogWarn:
		szColor = g_pchLogColorWarn_Log4;
		break;
	case emLogError:
		szColor = g_pchLogColorError_Log4;
		break;
	case emLogFatal:
		szColor = g_pchLogColorFatal_Log4;
		break;
	default:
		szColor = g_pchLogColorNONE_Log4;
		break;
	}

	OspPrintf(1, 0, "%s%s%s", szColor, sz.c_str(), g_pchLogColorNONE_Log4);
}

extern BOOL32		g_bConsoleLogOn;

void CLocalConsoleAppender::append( const log4cplus::spi::InternalLoggingEvent& event )
{
	if (g_bConsoleLogOn)
	{
		ConsoleAppender::append(event);
	}
}
