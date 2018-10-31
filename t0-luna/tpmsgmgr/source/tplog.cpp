#include "tplog.h"
#include "tplogmgr.h"
#include "tpmsg.h"


#ifdef _USE_LOG4CPLUS_
#include "logclientapi.h"
#endif//_USE_LOG4CPLUS_

namespace UmsTpmsg {

#ifdef _USE_LOG4CPLUS_
s8 g_ach_Mod_Name[MAX_MOD_NAME_LEN+1] = {0};
#endif//_USE_LOG4CPLUS_

void OpenAllMod();
void OpenAllCnsMod();
void OpenAllUmsMod();

void CloseAllMod();
void CloseAllCnsMod();
void CloseAllUmsMod();

void mdlmsgprint(u16 wMdl, u16 wLevel, s8* szFormat, va_list& pvList, s8* szTitle);

CTpLog::CTpLog()
{
	m_pLogTitle = NULL;
	m_wLogModuleId = 0;	
	m_wLastEventID = 0;
	m_bInHandMsg = FALSE;
	CTpLogManager::Regist(this);
}


CTpLog::~CTpLog()
{
	CTpLogManager::UnRegist(this);
}


void CTpLog::Error(s8* szFormat, ... )
{
    va_list pvList;
    va_start(pvList, szFormat);	

	mdlmsgprint(m_wLogModuleId, enLogError, szFormat, pvList, m_pLogTitle);

    va_end(pvList);

}

void CTpLog::LowHint(s8* szFormat, ... )
{

    va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(m_wLogModuleId, enLogLowest, szFormat, pvList, m_pLogTitle);

    va_end(pvList);
	
}

void CTpLog::LowDtlHint(s8* szFormat, ... )
{
	
    va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(m_wLogModuleId, enLoglowDetail, szFormat, pvList, m_pLogTitle);
	
    va_end(pvList);
	
}

void CTpLog::Hint(s8* szFormat, ... )
{

    va_list pvList;
    va_start(pvList, szFormat);	

	mdlmsgprint(m_wLogModuleId, enLogHint, szFormat, pvList, m_pLogTitle);

    va_end(pvList);

}


void CTpLog::SetLogTitle(s8* title)
{
	if (title == NULL)
	{
		title = "[CKdvLog]";
	}
	m_pLogTitle = CTpLogManager::CopyTitle( title );
}

void tplocaltime(struct tm& t, const time_t& ti)
{
	time_t tTmp = ti;

#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)

#define TIME_ZONE_BEIJING 8*60*60
	tTmp += TIME_ZONE_BEIJING;//转成北京时间

#endif
#endif

	t = *(localtime(&tTmp));
	t.tm_year += 1900;
	t.tm_mon += 1;
}


API void showlogtitle();
API void showlastmsg();
API void msghelp()
{
	msgprintnotime("tpver()                                      --  tpver\n");
	msgprintnotime("msgver()                                     --  msgver\n");
	msgprintnotime("showlogtitle()                               --  显示日志前缀\n");
	msgprintnotime("showlastmsg()                                --  显示各模块处理的最后一条消息\n");
	msgprintnotime("showtppevent(u16 wEvent)                     --  显示外部消息名称， 0为所有\n");
	msgprintnotime("showeventbyid(u16 wEvent)                    --  根据ID查询内外部消息名称\n");
	msgprintnotime("showeventbyname(  s8 abyEventName[50] )      --  根据名字查询内外部消息id\n");
	msgprintnotime("showmsg(u32 dwShow)                          --  1. 显示消息， 2. 显示消息内容\n");

	msgprintnotime("tplogon(u32 dwMdl)                           --  放开所有的消息\n");
	msgprintnotime("tploglow(u32 dwMdl)                          --  放开低等级打印\n");
	msgprintnotime("tplogdtl(u32 dwMdl)                          --  放开最最低等级打印\n");
	msgprintnotime("tplogoff()                                   --  关闭所有的打印\n");	

	msgprintnotime("showmdlname()                                --  显示模块名\n");

}


#define  VER_tpmsg_ver UMS_VerID
API void tpver()
{
	msgprint("tpmsg ver: %s  compile time: %s:%s\n",
		VER_tpmsg_ver, __DATE__,  __TIME__);
}

char* GetEventNamebyID( u32 wEvent );
u16 GetEventbyName(  s8 abyEventName[50] );
API void showeventbyid( u32 wEvent )
{
	s8* pszName = GetEventNamebyID(wEvent);
	msgprint("%d -> %s\n", wEvent, pszName);
}
API void showeventbyname(  s8 abyEventName[50] )
{
	u16  wEvent = GetEventbyName( abyEventName );
	msgprint("%d -> %s\n", wEvent, abyEventName);
}


API void showtppevent( u16 wEvent );
API void showmsg(u32 dwShow);

API void setconsolelog(BOOL32 bOnoff);
API void tplogon(u32 dwMdl);
API void tploglow(u32 dwMdl);
API void tplogdtl(u32 dwMdl);
API void tplogoff();

API void showmdlname();
API void showlogstatus();

API void testlogfun()
{
	MsgPrintLowDtlLog("this is low dtl log!\n");
	MsgPrintLowHintLog("this is low hint log!\n");
	MsgPrintHintLog("this is hint log!\n");
	MsgPrintErrorLog("this is error log!\n");
}

void regist_tp_commond()
{
#ifdef _LINUX_
	OspRegCommand("msghelp", (void*)msghelp, "API void msghelp()");
	OspRegCommand("tpver", (void*)tpver, "API void tpver()");
	OspRegCommand("showlogtitle", (void*)showlogtitle, "API void showlogtitle()");
	OspRegCommand("showlastmsg", (void*)showlastmsg, "API void showlastmsg()");
	OspRegCommand("showtppevent", (void*)showtppevent, "API void showtppevent()");
	OspRegCommand("showeventbyid", (void*)showeventbyid, "API void showeventbyid()");
	OspRegCommand("showeventbyname", (void*)showeventbyname, "API void showeventbyname()");
	OspRegCommand("showmsg", (void*)showmsg, "API void showmsg()");

	OspRegCommand("tplogon", (void*)tplogon, "API void tplogon()");
	OspRegCommand("tploglow", (void*)tploglow, "API void tploglow()");
	OspRegCommand("tplogoff", (void*)tplogoff, "API void tplogoff()");
	OspRegCommand("tplogdtl", (void*)tplogdtl, "API void tplogdtl()");
	
	OspRegCommand("showmdlname", (void*)showmdlname, "API void showmdlname()");
	OspRegCommand( "showlogstatus", (void*)showlogstatus, "API void showlogstatus()" );

	OspRegCommand("setconsolelog", (void*)setconsolelog, "API void setconsolelog()");
	OspRegCommand("testlogfun", (void*)testlogfun, "API void testlogfun()");
#endif // _LINUX_
}

void SetPrintToCom(BOOL32 bPrint)
{
	if (bPrint)
	{
		CTpLogManager::m_bIsPrintCom = TRUE;
		if (CTpLogManager::m_bIsInitKdvLog)
		{
			logsetdst(LOG_DST_SERIAL|LOG_DST_FILE);
		}
#ifdef _USE_LOG4CPLUS_
		if (CTpLogManager::m_bIsInitLog4cplus)
		{
			log4cpclient::SetConsoleLog(TRUE);
		}
#endif //_USE_LOG4CPLUS_
	}
	else
	{
		CTpLogManager::m_bIsPrintCom = FALSE;
		if (CTpLogManager::m_bIsInitKdvLog)
		{
			logsetdst(LOG_DST_FILE);
		}
#ifdef _USE_LOG4CPLUS_
		if (CTpLogManager::m_bIsInitLog4cplus)
		{
			log4cpclient::SetConsoleLog(FALSE);
		}
#endif //_USE_LOG4CPLUS_
	}
}

BOOL32 initKdvLog(s8 * pchFileName, BOOL32 bPrintToCom)
{
	BOOL32 bInit = IsOspInitd();
	if ( bInit == FALSE )
	{
		bInit = OspInit( TRUE ); 
		if ( bInit == FALSE )
		{
			printf("osp init fail ! \n");
			return FALSE;			
		}
	}
	
	Err_t ret = LogInit(pchFileName);
	CTpLogManager::m_bIsInitKdvLog = (LOG_ERR_NO_ERR == ret ? TRUE : FALSE) ;

	if( ret != LOG_ERR_NO_ERR )
	{
		printf("log init fail !\n");
		return FALSE;
	}

	SetPrintToCom(bPrintToCom);

	// 不再用kdvlog输出到telnet窗口
	CloseAllMod();
	
	return TRUE;
}

void SetLogFlush()
{
	if (CTpLogManager::m_bIsInitKdvLog)
	{
		logflush();
	}
}

void ExitKdvLog()
{
	if (CTpLogManager::m_bIsInitKdvLog)
	{
		LogQuit();
		CTpLogManager::m_bIsInitKdvLog = FALSE;
	}
#ifdef _USE_LOG4CPLUS_
	ExitLog4CPlusLog();
#endif//_USE_LOG4CPLUS_
}


void OpenAllMod()
{
	if (!CTpLogManager::m_bIsInitKdvLog)
		return;
	OpenAllCnsMod();
	OpenAllUmsMod();
	logenablemod(MID_PUB_ALWAYS);
}

void OpenAllCnsMod()
{
	logenablemod(MID_CNS_1);	
	logenablemod(MID_CNS_2);	
	logenablemod(MID_CNS_3);	
	logenablemod(MID_CNS_4);	
	logenablemod(MID_CNS_5);	
	logenablemod(MID_CNS_6);
	logenablemod(MID_CNS_7);	
	logenablemod(MID_CNS_8);	
	logenablemod(MID_CNS_9);	
	logenablemod(MID_CNS_10);	
	logenablemod(MID_CNS_11);	
	logenablemod(MID_CNS_12);
	logenablemod(MID_CNS_13);	
	logenablemod(MID_CNS_14);	
	logenablemod(MID_CNS_15);	
	logenablemod(MID_CNS_16);	
	logenablemod(MID_CNS_17);	
	logenablemod(MID_CNS_18);
	logenablemod(MID_CNS_19);	
	logenablemod(MID_CNS_20);
}

void OpenAllUmsMod()
{
	logenablemod(MID_UMS_1);	
	logenablemod(MID_UMS_2);
	logenablemod(MID_UMS_3);	
	logenablemod(MID_UMS_4);
	logenablemod(MID_UMS_5);	
	logenablemod(MID_UMS_6);
	logenablemod(MID_UMS_7);	
	logenablemod(MID_UMS_8);
	logenablemod(MID_UMS_9);	
	logenablemod(MID_UMS_10);
	logenablemod(MID_UMS_11);	
	logenablemod(MID_UMS_12);
	logenablemod(MID_UMS_13);	
	logenablemod(MID_UMS_14);
	logenablemod(MID_UMS_15);	
	logenablemod(MID_UMS_16);
	logenablemod(MID_UMS_17);	
	logenablemod(MID_UMS_18);
	logenablemod(MID_UMS_19);	
	logenablemod(MID_UMS_20);
}

void CloseAllMod()
{
	if (!CTpLogManager::m_bIsInitKdvLog)
		return;
	CloseAllCnsMod();
	CloseAllUmsMod();
	logdisablemod(MID_PUB_ALWAYS);
}

void CloseAllCnsMod()
{
	logdisablemod(MID_CNS_1);	
	logdisablemod(MID_CNS_2);	
	logdisablemod(MID_CNS_3);	
	logdisablemod(MID_CNS_4);	
	logdisablemod(MID_CNS_5);	
	logdisablemod(MID_CNS_6);
	logdisablemod(MID_CNS_7);	
	logdisablemod(MID_CNS_8);	
	logdisablemod(MID_CNS_9);	
	logdisablemod(MID_CNS_10);	
	logdisablemod(MID_CNS_11);	
	logdisablemod(MID_CNS_12);
	logdisablemod(MID_CNS_13);	
	logdisablemod(MID_CNS_14);	
	logdisablemod(MID_CNS_15);	
	logdisablemod(MID_CNS_16);	
	logdisablemod(MID_CNS_17);	
	logdisablemod(MID_CNS_18);
	logdisablemod(MID_CNS_19);	
	logdisablemod(MID_CNS_20);
}

void CloseAllUmsMod()
{
	logdisablemod(MID_UMS_1);	
	logdisablemod(MID_UMS_2);
	logdisablemod(MID_UMS_3);	
	logdisablemod(MID_UMS_4);
	logdisablemod(MID_UMS_5);	
	logdisablemod(MID_UMS_6);
	logdisablemod(MID_UMS_7);	
	logdisablemod(MID_UMS_8);
	logdisablemod(MID_UMS_9);	
	logdisablemod(MID_UMS_10);
	logdisablemod(MID_UMS_11);	
	logdisablemod(MID_UMS_12);
	logdisablemod(MID_UMS_13);	
	logdisablemod(MID_UMS_14);
	logdisablemod(MID_UMS_15);	
	logdisablemod(MID_UMS_16);
	logdisablemod(MID_UMS_17);	
	logdisablemod(MID_UMS_18);
	logdisablemod(MID_UMS_19);	
	logdisablemod(MID_UMS_20);
}


#ifdef _USE_LOG4CPLUS_
BOOL32 initLog4CPlusLog( s8 *pchCfgFileName, s8 *pchModeName, BOOL32 bPrintToCom /*= FALSE*/ )
{
	if (!pchCfgFileName || !pchModeName)
	{
        return FALSE;
	}

	u32 dwModNameLen = strlen(pchModeName);
    if (!dwModNameLen)
	{
		return FALSE;
	}

	if (dwModNameLen > MAX_MOD_NAME_LEN)
	{
        dwModNameLen = MAX_MOD_NAME_LEN;
	}

	strncpy(g_ach_Mod_Name, pchModeName, dwModNameLen);
    g_ach_Mod_Name[dwModNameLen] = '\0';

	if (!log4cpclient::Init(pchCfgFileName, TRUE, FALSE))
	{
		return FALSE;
	}

	if (!log4cpclient::RegMod(g_ach_Mod_Name))
	{
		return FALSE;
	}

	log4cpclient::SetErrorOn();  // 默认打印级别

	CTpLogManager::m_bIsInitLog4cplus = TRUE;

	SetPrintToCom(bPrintToCom);

	// mediaclient打印使用
	LogInit();

	return TRUE;
}

void ExitLog4CPlusLog()
{
	if (CTpLogManager::m_bIsInitLog4cplus)
	{
		log4cpclient::Exit();
		CTpLogManager::m_bIsInitLog4cplus = FALSE;
	}
}

#endif //_USE_LOG4CPLUS_

} //namespace UmsTpmsg