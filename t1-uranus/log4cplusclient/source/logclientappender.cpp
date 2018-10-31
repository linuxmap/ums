#include "osp.h"
#include <sstream>
#include "log4cplus/streams.h"
#include <log4cplus/spi/loggingevent.h>
#include "logclientappender.h"
#include "logclient.h"


#define LOGCOLOR_NONE			"\033[m"            ///< 无

#define LOGCOLOR_RED			"\033[31m"			///< 红色
#define LOGCOLOR_GREEN			"\033[32m"			///< 绿色
#define LOGCOLOR_YELLOW			"\033[33m"			///< 黄色
#define LOGCOLOR_BLUE			"\033[34m"			///< 蓝色
#define LOGCOLOR_PURPLE			"\033[35m"			///< 紫色
#define LOGCOLOR_CYAN			"\033[36m"			///< 青色
#define LOGCOLOR_WHITE			"\033[37m"			///< 白色

#define LOGCOLOR_LIGHT_RED		"\033[1;31m"		///< 亮红色
#define LOGCOLOR_LIGHT_GREEN	"\033[1;32m"		///< 亮绿色
#define LOGCOLOR_LIGHT_YELLOW	"\033[1;33m"		///< 亮黄色
#define LOGCOLOR_LIGHT_BLUE		"\033[1;34m"		///< 亮蓝色
#define LOGCOLOR_LIGHT_PURPLE	"\033[1;35m"		///< 亮紫色
#define LOGCOLOR_LIGHT_CYAN		"\033[1;36m"		///< 亮青色
#define LOGCOLOR_LIGHT_WHITE	"\033[1;37m"		///< 亮白色


const s8 *g_pchLogColorNONE_Log4 = LOGCOLOR_NONE;				//无颜色
const s8 *g_pchLogColorFatal_Log4 = LOGCOLOR_LIGHT_RED;			//fatal：	亮红色
const s8 *g_pchLogColorError_Log4 = LOGCOLOR_PURPLE;				//error：	紫色
const s8 *g_pchLogColorWarn_Log4  = LOGCOLOR_YELLOW;				//warn：	黄色
const s8 *g_pchLogColorInfo_Log4  = LOGCOLOR_CYAN;				//info：	青色
const s8 *g_pchLogColorDebug_Log4 = LOGCOLOR_LIGHT_GREEN;		//debug：	亮绿色

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
