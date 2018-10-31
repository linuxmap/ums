#ifndef _LOGCLIENTFILTER_H_
#define _LOGCLIENTFILTER_H_

#include "log4cplus/spi/filter.h"

class CLogLevelAppenderFilter : public log4cplus::spi::Filter
{
public:
	CLogLevelAppenderFilter(){}
	virtual ~CLogLevelAppenderFilter(){}

	virtual log4cplus::spi::FilterResult decide(const log4cplus::spi::InternalLoggingEvent& event) const;
};



#endif //_LOGCLIENTFILTER_H_