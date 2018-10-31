#ifndef _LOGCLIENTAPPENDER_H_
#define _LOGCLIENTAPPENDER_H_
#include "log4cplus/appender.h"
#include "log4cplus/consoleappender.h"

class CTelnetAppender : public log4cplus::Appender
{
public:
	CTelnetAppender();
	~CTelnetAppender();

	virtual void close();
protected:
	virtual void append(const log4cplus::spi::InternalLoggingEvent& event);
};

class CLocalConsoleAppender : public log4cplus::ConsoleAppender
{
protected:
	virtual void append(const log4cplus::spi::InternalLoggingEvent& event);
};

#endif // _LOGCLIENTAPPENDER_H_