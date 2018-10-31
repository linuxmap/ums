// Module:  LOG4CPLUS
// File:    loggingserver.cxx
// Created: 5/2003
// Author:  Tad E. Smith
//
//
// Copyright 2003-2015 Tad E. Smith
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdlib>
#include <list>
#include <iostream>
#include <log4cplus/configurator.h>
#include <log4cplus/socketappender.h>
#include <log4cplus/helpers/socket.h>
#include <log4cplus/thread/threads.h>
#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/logger.h>
#include <log4cplus/thread/syncprims.h>

#include "osp.h"
#include "log4cplusserver.h"

u16 g_wListenPort = 0;


namespace loggingserver
{


typedef std::list<log4cplus::thread::AbstractThreadPtr> ThreadQueueType;


class ReaperThread
    : public log4cplus::thread::AbstractThread
{
public:
    ReaperThread (log4cplus::thread::Mutex & mtx_,
        log4cplus::thread::ManualResetEvent & ev_,
        ThreadQueueType & queue_)
        : mtx (mtx_)
        , ev (ev_)
        , queue (queue_)
        , stop (false)
    { }

    virtual
    ~ReaperThread ()
    { }

    virtual void run ();

    void signal_exit ();

private:
    log4cplus::thread::Mutex & mtx;
    log4cplus::thread::ManualResetEvent & ev;
    ThreadQueueType & queue;
    bool stop;
};


typedef log4cplus::helpers::SharedObjectPtr<ReaperThread> ReaperThreadPtr;


void
ReaperThread::signal_exit ()
{
    log4cplus::thread::MutexGuard guard (mtx);
    stop = true;
    ev.signal ();
}


void
ReaperThread::run ()
{
    ThreadQueueType q;

    while (true)
    {
        ev.timed_wait (30 * 1000);

        {
            log4cplus::thread::MutexGuard guard (mtx);

            // Check exit condition as the very first thing.
            if (stop)
            {
                std::cout << "Reaper thread is stopping..." << std::endl;
                return;
            }

            ev.reset ();
            q.swap (queue);
        }

        if (! q.empty ())
        {
            std::cout << "Reaper thread is reaping " << q.size () << " threads."
                      << std::endl;

            for (ThreadQueueType::iterator it = q.begin (), end_it = q.end ();
                 it != end_it; ++it)
            {
                AbstractThread & t = **it;
                t.join ();
            }

            q.clear ();
        }
    }
}



/**
   This class wraps ReaperThread thread and its queue.
 */
class Reaper
{
public:
    Reaper ()
    {
        reaper_thread = ReaperThreadPtr (new ReaperThread (mtx, ev, queue));
        reaper_thread->start ();
    }

    ~Reaper ()
    {
        reaper_thread->signal_exit ();
        reaper_thread->join ();
    }

    void visit (log4cplus::thread::AbstractThreadPtr const & thread_ptr);

private:
    log4cplus::thread::Mutex mtx;
    log4cplus::thread::ManualResetEvent ev;
    ThreadQueueType queue;
    ReaperThreadPtr reaper_thread;
};


void
Reaper::visit (log4cplus::thread::AbstractThreadPtr const & thread_ptr)
{
    log4cplus::thread::MutexGuard guard (mtx);
    queue.push_back (thread_ptr);
    ev.signal ();
}


class ClientThread
    : public log4cplus::thread::AbstractThread
{
public:
    ClientThread(log4cplus::helpers::Socket clientsock_, Reaper & reaper_)
        : self_reference (log4cplus::thread::AbstractThreadPtr (this))
        , clientsock(clientsock_)
        , reaper (reaper_)
    {
        std::cout << "Received a client connection!!!!" << std::endl;
    }

    ~ClientThread()
    {
        std::cout << "Client connection closed." << std::endl;
    }

    virtual void run();

private:
    log4cplus::thread::AbstractThreadPtr self_reference;
    log4cplus::helpers::Socket clientsock;
    Reaper & reaper;
};


void
loggingserver::ClientThread::run()
{
	std::string strLoggerName;
	u32 dwTaskId = 0;
    try
    {
        while (1)
        {
            if (!clientsock.isOpen())
                break;

            log4cplus::helpers::SocketBuffer msgSizeBuffer(sizeof(unsigned int));
            if (!clientsock.read(msgSizeBuffer))
                break;

            unsigned int msgSize = msgSizeBuffer.readInt();

            log4cplus::helpers::SocketBuffer buffer(msgSize);
            if (!clientsock.read(buffer))
                break;

            log4cplus::spi::InternalLoggingEvent event
                = log4cplus::helpers::readFromBuffer(buffer);

			if (!dwTaskId)
			{
				dwTaskId = GetSelfTaskId();
				strLoggerName.assign(event.getLoggerName());
//				OspPrintf(1, 0, "[Add] LoggerName:%s, ThreadId:%u.\n", 
//					strLoggerName.c_str(), dwTaskId);
				CLog4plusclientMgr::GetInstance()->AddClient(strLoggerName, dwTaskId);
			}

            log4cplus::Logger logger
                = log4cplus::Logger::getInstance(event.getLoggerName());
            logger.callAppenders(event);
        }
    }
    catch (...)
    {
        reaper.visit (self_reference);
        self_reference = log4cplus::thread::AbstractThreadPtr ();
		if (dwTaskId)
		{
			CLog4plusclientMgr::GetInstance()->DelClient(strLoggerName, dwTaskId);
//			OspPrintf(1, 0, "[catch][Del] LoggerName:%s, ThreadId:%u.\n", 
//				strLoggerName.c_str(), dwTaskId);
			strLoggerName.clear();
			dwTaskId = 0;
		}
        throw;
    }

    reaper.visit (self_reference);
    self_reference = log4cplus::thread::AbstractThreadPtr ();
	if (dwTaskId)
	{
		CLog4plusclientMgr::GetInstance()->DelClient(strLoggerName, dwTaskId);
//		OspPrintf(1, 0, "[Del] LoggerName:%s, ThreadId:%u.\n", 
//			strLoggerName.c_str(), dwTaskId);
		strLoggerName.clear();
		dwTaskId = 0;
	}
}

} // namespace loggingserver

int
main(int argc, char** argv)
{

	if (!OspInit(TRUE, 2998))
		return 3;

	OspSetPrompt("log4cplusserver");

#ifdef _LINUX_
	OspRegCommand("ver", (void*)ver, "ver");
	OspRegCommand("help", (void*)help, "help");
	OspRegCommand("showlogserver", (void*)showlogserver, "showlogserver");
#endif

    log4cplus::initialize ();

    if(argc < 3) {
        std::cout << "Usage: port config_file" << std::endl;
        return 1;
    }
    g_wListenPort = std::atoi(argv[1]);
    const log4cplus::tstring configFile = LOG4CPLUS_C_STR_TO_TSTRING(argv[2]);

    log4cplus::PropertyConfigurator config(configFile);
    config.configure();

    log4cplus::helpers::ServerSocket serverSocket(g_wListenPort);
    if (!serverSocket.isOpen()) {
        std::cerr << "Could not open server socket, maybe port "
            << g_wListenPort << " is already in use." << std::endl;
        return 2;
    }

    loggingserver::Reaper reaper;

    for (;;)
    {
        loggingserver::ClientThread *thr =
            new loggingserver::ClientThread(serverSocket.accept(), reaper);
        thr->start();
    }

    log4cplus::Logger::shutdown();

    return 0;
}
