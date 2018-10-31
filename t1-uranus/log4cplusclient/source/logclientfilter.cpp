#include "logclientfilter.h"
#include "log4cplus/spi/loggingevent.h"
#include "kdvtype.h"

extern	u32			g_dwLocalLogLevel;

log4cplus::spi::FilterResult CLogLevelAppenderFilter::decide( const log4cplus::spi::InternalLoggingEvent& event ) const
{
	if ((u32)event.getLogLevel() < g_dwLocalLogLevel)
	{
		return log4cplus::spi::DENY;
	}
	return log4cplus::spi::ACCEPT;
}
