#include "tplog.h"
#include "msgmgr.h"
#include "tplogmgr.h"
#include "tpsys.h"


#ifdef _USE_LOG4CPLUS_
#include "logclientapi.h"
#endif//_USE_LOG4CPLUS_

namespace UmsTpmsg {
extern s8 g_ach_Mod_Name[];
void tplocaltime(struct tm& t, const time_t& ti);

#define LOGCOLOR_NONE			"\033[m"            ///< 无
#define LOGCOLOR_RED			"\033[0;32;31m"     ///< 红色
#define LOGCOLOR_LIGHT_RED		"\033[1;31m"		///< 淡红
#define LOGCOLOR_GREEN			"\033[0;32;32m"		///< 绿色
#define LOGCOLOR_LIGHT_GREEN	"\033[1;32m"		///< 浅绿色
#define LOGCOLOR_BLUE			"\033[0;32;34m"		///< 蓝色
#define LOGCOLOR_LIGHT_BLUE		"\033[1;34m"		///< 浅蓝色
#define LOGCOLOR_DARY_GRAY		"\033[1;30m"		///< 深灰色
#define LOGCOLOR_CYAN			"\033[0;36m"		///< 青色
#define LOGCOLOR_LIGHT_CYAN		"\033[1;36m"		///< 浅青色
#define LOGCOLOR_PURPLE			"\033[0;35m"		///< 紫色的
#define LOGCOLOR_LIGHT_PURPLE	"\033[1;35m"		///< 浅紫色
#define LOGCOLOR_BROWN			"\033[0;33m"		///< 褐色
#define LOGCOLOR_YELLOW			"\033[1;33m"		///< 黄色
#define LOGCOLOR_LIGHT_GRAY		"\033[0;37m"		///< 浅灰色
#define LOGCOLOR_WHITE			"\033[1;37m"		///< 白色

const s8 *g_pchLogColorNONE = LOGCOLOR_NONE;				//无颜色
const s8 *g_pchLogColorError = LOGCOLOR_LIGHT_RED;			//error：	淡红
const s8 *g_pchLogColorHint  = LOGCOLOR_BROWN;				//Hint：	褐色
const s8 *g_pchLogColorLowHint  = LOGCOLOR_CYAN;			//LowHint：	青色
const s8 *g_pchLogColorLowDtl = LOGCOLOR_LIGHT_GREEN;		//LowDtl：	浅绿色

// 目前tplog包含四种层级打印 error hint lowhint lowdtl
void TpLogPrint( const u8 byLevel, const u16 wModule, s8* pMsg)
{

#ifdef _USE_LOG4CPLUS_
	if (CTpLogManager::m_bIsInitLog4cplus)
	{
		switch(byLevel)
		{
		case enLoglowDetail:
			log4cpclient::Debug(g_ach_Mod_Name, "%s", pMsg);
			break;

		case enLogLowest:
			log4cpclient::Info(g_ach_Mod_Name, "%s", pMsg);
			break;

		case enLogHint:
			log4cpclient::Warn(g_ach_Mod_Name, "%s", pMsg);
			break;

		case enLogError:
		default:
			log4cpclient::Error(g_ach_Mod_Name, "%s", pMsg);
			break;
		}
	}
#else
	if (CTpLogManager::m_bIsInitKdvLog)
	{	// 输出到文件或串口
		LogPrint((u8)byLevel, wModule, pMsg);
	}
#endif //_USE_LOG4CPLUS_
	else
	{
		if (CTpLogManager::m_dwLogLevel < byLevel)
		{
			return;
		}
		// 输出到串口
		if (CTpLogManager::m_bIsPrintCom)
		{
			printf("%s", pMsg);
		}
	}

	if (CTpLogManager::m_dwLogLevel < byLevel)
	{
		return;
	}

	// 输出到telnet
	const s8* szColor = NULL;
	if (byLevel == LOG_LVL_ERROR)
	{
		szColor = g_pchLogColorError;
	}
	else if (byLevel == LOG_LVL_WARNING)
	{
		szColor = g_pchLogColorHint;
	}
	else if (byLevel == LOG_LVL_KEYSTATUS)
	{
		szColor = g_pchLogColorLowHint;
	}
	else
	{
		szColor = g_pchLogColorLowDtl;
	}
	
	OspPrintf(TRUE,FALSE, "%s%s%s", szColor, pMsg, LOGCOLOR_NONE);

	return;
	
}

// 包含四种层级打印 error hint lowhint lowdtl, 不写入文件中
void TpLogPrintNoFile( const u8 byLevel, const u16 wModule, s8* pMsg)
{
	if (CTpLogManager::m_dwLogLevel < byLevel)
	{
		return;
	}
	// 输出到串口
	if (CTpLogManager::m_bIsPrintCom)
	{
		printf("%s", pMsg);
	}
	
	// 输出到telnet
	const s8* szColor = NULL;
	if (byLevel == LOG_LVL_ERROR)
	{
		szColor = g_pchLogColorError;
	}
	else if (byLevel == LOG_LVL_WARNING)
	{
		szColor = g_pchLogColorHint;
	}
	else if (byLevel == LOG_LVL_KEYSTATUS)
	{
		szColor = g_pchLogColorLowHint;
	}
	else
	{
		szColor = g_pchLogColorLowDtl;
	}
	
	OspPrintf(TRUE,FALSE, "%s%s%s", szColor, pMsg, LOGCOLOR_NONE);
	
	return;
	
}
void msgprint( char *szFormat, ... )
{
	if(szFormat == NULL)
		return;
	
	char msg[MAX_MSG_LEN_TMP];

	va_list pvList;
    va_start(pvList, szFormat);	

	time_t ti;
	time(&ti);
	struct tm t;
	tplocaltime(t, ti);
	
	int len = sprintf(msg, "%2.2u-%2.2u %2.2u:%2.2u:%2.2u ", t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

	len = vsnprintf( msg+len, MAX_MSG_LEN_TMP-len, szFormat, pvList);
	if ( len > 0 ) 
	{
		msg[sizeof(msg)-1] = '\0'; 
		TpLogPrint(LOG_LVL_ERROR, MID_PUB_ALWAYS, msg );
	}
	else if (len == -1)
	{
		TpLogPrint(LOG_LVL_ERROR, MID_PUB_ALWAYS, "[msgprint]print failed!\n\n\n");
	}

    va_end(pvList);	
}

void msgprintnotime( char *szFormat, ... )
{
	if(szFormat == NULL)
		return;
	
	char msg[MAX_MSG_LEN_TMP];
	
	va_list pvList;
    va_start(pvList, szFormat);	
	
	int len = vsnprintf( msg, MAX_MSG_LEN_TMP, szFormat, pvList);
	if ( len > 0 ) 
	{
		msg[sizeof(msg)-1] = '\0'; 
		TpLogPrint(LOG_LVL_ERROR, MID_PUB_ALWAYS, msg);
	}
	else if (len == -1)
	{
		TpLogPrint(LOG_LVL_ERROR, MID_PUB_ALWAYS, "[msgprint]print failed!\n\n\n");
	}

    va_end(pvList);	
}

void printcallid(u8* pCallID, u16 wCallSize, BOOL32 bPauseZero)
{
#define MAX_LEN_TMP 256
	s8 szBuf[MAX_LEN_TMP];
	if (wCallSize >= MAX_LEN_TMP-2)
	{
		wCallSize = MAX_LEN_TMP - 2;
	}

	szBuf[0] = '\0';

	u16 wIndex = 0;
	if (bPauseZero)
	{
		for (wIndex=0; wIndex<wCallSize; ++wIndex)
		{
			if (0 == pCallID[wIndex])
			{
				break;
			}

			sprintf(&szBuf[wIndex], "%x", pCallID[wIndex]);
		}
	}
	else
	{
		for (int wIndex=0; wIndex<wCallSize; ++wIndex)
		{
			sprintf(&szBuf[wIndex], "%x", pCallID[wIndex]);
		}
	}

	szBuf[wIndex] = '\n';
	szBuf[wIndex+1] = '\0';
	TpLogPrint(LOG_LVL_ERROR, MID_PUB_ALWAYS, szBuf);
}

void mdlmsgprint(u16 wMdl, u16 wLevel, s8* szFormat, va_list& pvList, s8* szTitle)
{
	if(szFormat == NULL)
		return;

	char msg[MAX_MSG_LEN_TMP];
	
	time_t ti;
	time(&ti);
	struct tm t;
	tplocaltime(t, ti);

	int len = sprintf(msg, "%2.2u-%2.2u %2.2u:%2.2u:%2.2u ", t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	
	if(MID_PUB_ALWAYS != wMdl)
	{
		if (((wMdl - MID_CNS_1 + 1) > 0) && (wMdl - MID_CNS_1) < MAX_MSGMDL_NUM && CTpLogManager::m_atmsgModelCtrl[wMdl - MID_CNS_1].m_achlName != NULL)
		{
			len += snprintf(msg+len, MAX_MSG_LEN_TMP-len, "%s ", CTpLogManager::m_atmsgModelCtrl[wMdl - MID_CNS_1].m_achlName);
		}
		if (wLevel < MAX_MSGLEVEL_NUM)
		{
			len += snprintf(msg+len, MAX_MSG_LEN_TMP-len, "%s", CTpLogManager::m_achmsgLogLevel[wLevel]);
		}
		if (szTitle != NULL)
		{
			len += snprintf(msg+len, MAX_MSG_LEN_TMP-len, "%s", szTitle);
		}
		len = vsnprintf( msg+len, MAX_MSG_LEN_TMP-len, szFormat, pvList);
	}
	else
	{
		len = vsnprintf( msg+len, MAX_MSG_LEN_TMP-len, szFormat, pvList);
	}

	if (len > 0) 
	{
		msg[sizeof(msg)-1] = '\0';
		TpLogPrint((u8)wLevel, wMdl, msg);
	}
	else if (len == -1)
	{
		char abyErrMsg[MAX_MSG_LEN_TMP];
		sprintf(abyErrMsg, "[mdlmsgprint] print failed! mdl:%d, lv:%d.\n\n\n", wMdl, wLevel);
		TpLogPrint((u8)wLevel, wMdl, abyErrMsg);
	}
}

void mdlmsgprintnofile(u16 wMdl, u16 wLevel, s8* szFormat, va_list& pvList, s8* szTitle)
{
	if(szFormat == NULL)
		return;
	
	char msg[MAX_MSG_LEN_TMP];
	
	time_t ti;
	time(&ti);
	struct tm t;
	tplocaltime(t, ti);
	
	int len = sprintf(msg, "%2.2u-%2.2u %2.2u:%2.2u:%2.2u ", t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	
	if(MID_PUB_ALWAYS != wMdl)
	{
		if (((wMdl - MID_CNS_1 + 1) > 0) && (wMdl - MID_CNS_1) < MAX_MSGMDL_NUM && CTpLogManager::m_atmsgModelCtrl[wMdl - MID_CNS_1].m_achlName != NULL)
		{
			len += snprintf(msg+len, MAX_MSG_LEN_TMP-len, "%s ", CTpLogManager::m_atmsgModelCtrl[wMdl - MID_CNS_1].m_achlName);
		}
		if (wLevel < MAX_MSGLEVEL_NUM)
		{
			len += snprintf(msg+len, MAX_MSG_LEN_TMP-len, "%s", CTpLogManager::m_achmsgLogLevel[wLevel]);
		}
		if (szTitle != NULL)
		{
			len += snprintf(msg+len, MAX_MSG_LEN_TMP-len, "%s", szTitle);
		}
		len = vsnprintf( msg+len, MAX_MSG_LEN_TMP-len, szFormat, pvList);
	}
	else
	{
		len = vsnprintf( msg+len, MAX_MSG_LEN_TMP-len, szFormat, pvList);
	}
	
	if (len > 0) 
	{
		msg[sizeof(msg)-1] = '\0';
		TpLogPrintNoFile((u8)wLevel, wMdl, msg);
	}
	else if (len == -1)
	{
		char abyErrMsg[MAX_MSG_LEN_TMP];
		sprintf(abyErrMsg, "[mdlmsgprint] print failed! mdl:%d, lv:%d.\n\n\n", wMdl, wLevel);
		TpLogPrintNoFile((u8)wLevel, wMdl, abyErrMsg);
	}
}

void tpLowDtl( u16 wMdl,s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(wMdl, enLoglowDetail, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void tpLowHint( u16 wMdl,s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(wMdl, enLogLowest, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void tpHint( u16 wMdl,s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(wMdl, enLogHint, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void tpError(u16 wMdl, s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(wMdl, enLogError, szFormat, pvList, NULL);

    va_end(pvList);
}

void tpLowDtlNoFile( u16 wMdl,s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprintnofile(wMdl, enLoglowDetail, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void tpLowHintNoFile( u16 wMdl,s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprintnofile(wMdl, enLogLowest, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void tpHintNoFile( u16 wMdl,s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprintnofile(wMdl, enLogHint, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void tpErrorNoFile(u16 wMdl, s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprintnofile(wMdl, enLogError, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void MsgPrintLowDtlLog( s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(MID_PUB_ALWAYS, enLoglowDetail, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void MsgPrintLowHintLog(s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(MID_PUB_ALWAYS, enLogLowest, szFormat, pvList, NULL);
	
    va_end(pvList);
}

void MsgPrintHintLog( s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(MID_PUB_ALWAYS, enLogHint, szFormat, pvList, NULL);

    va_end(pvList);
}

void MsgPrintErrorLog(s8* szFormat, ...)
{
	va_list pvList;
    va_start(pvList, szFormat);	
	
	mdlmsgprint(MID_PUB_ALWAYS, enLogError, szFormat, pvList, NULL);

    va_end(pvList);
}

static BOOL32 g_bInitLogManager = CTpLogManager::Init();
void CTpLogManager::ShowAllTitle()
{
	char* pStr= m_abyTitlePool;
	int i = 0 ; 
	
	while((pStr - m_abyTitlePool) < PoolSize)
	{
		if (*pStr == 0)
		{
			break;
		}
		msgprint("%d :  %s\n",i++,pStr);
		while(*pStr++ && ((pStr - m_abyTitlePool) < PoolSize ));
	}
}

void CTpLogManager::ShowLastMsg()
{
	CTpLog* pKdvLog = NULL;
	for (u16 wIndex = 0; wIndex < m_wEndInst; ++wIndex)
	{
		pKdvLog = m_apcLog[wIndex];

		if ( pKdvLog == NULL )
		{
			continue;
		}

		msgprintnotime("Processing:%d, event:%d-%s, %s, App:%d, Inst:%d\n", pKdvLog->GetInHandMsg()
			, pKdvLog->GetLastEventID(), GetEventNamebyID(pKdvLog->GetLastEventID())
			, pKdvLog->GetTitle(), pKdvLog->GetLogApp(), pKdvLog->GetLogInst());
	}
}

void CTpLogManager::SaveLastMsg(s8* pszFile)
{
	FILE *hLogFile = NULL;
	if (NULL != pszFile)
	{
		hLogFile = fopen(pszFile, "r+b");
	}
	
    if (NULL != hLogFile)
    {
		fseek(hLogFile, 0, SEEK_END);
    }
	

	s8 pachBuf[255];
	CTpLog* pKdvLog = NULL;
	for (u16 wIndex = 0; wIndex < m_wEndInst; ++wIndex)
	{
		pKdvLog = m_apcLog[wIndex];

		if ( NULL == pKdvLog )
		{
			continue;
		}

		if (pKdvLog->GetTitle() == NULL)
		{
			continue;
		}
		
		sprintf( pachBuf, "Processing:%d, event:%d-%s, App:%d, Inst:%d\n", pKdvLog->GetInHandMsg()
			, pKdvLog->GetLastEventID(), GetEventNamebyID(pKdvLog->GetLastEventID())
			, pKdvLog->GetLogApp(), pKdvLog->GetLogInst() );

		printf("%s", pachBuf);

		if (NULL == hLogFile)
		{
			continue;
		}
		s32 nLen = fwrite(pachBuf, strlen(pachBuf), 1, hLogFile);
		if (0 == nLen)
		{
			printf("write to exc.log failed\n");
			return;
		}
    
	}
	if (NULL != hLogFile)
	{
		fclose(hLogFile);
	}
	
}

s8    CTpLogManager::m_abyTitlePool[PoolSize+32];
u16    CTpLogManager::m_wEndInst = 0;
u16    CTpLogManager::m_wTitlePoolEndPos = 0;
u32	   CTpLogManager::m_dwLogLevel = enLogError;
BOOL32 CTpLogManager::m_bIsInitKdvLog = FALSE;
BOOL32 CTpLogManager::m_bIsPrintCom = FALSE;
#ifdef _USE_LOG4CPLUS_
BOOL32 CTpLogManager::m_bIsInitLog4cplus = FALSE;
#endif //_USE_LOG4CPLUS_

CTpLog* CTpLogManager::m_apcLog[]={NULL};

s8 CTpLogManager::m_achmsgLogLevel[MAX_MSGLEVEL_NUM][24];
TMsgPrintCtrl CTpLogManager::m_atmsgModelCtrl[MAX_MSGMDL_NUM];

static CTpLogManager g_kdvLogManager;
CTpLogManager::CTpLogManager()
{
	memset(m_abyTitlePool ,0 ,PoolSize+32);
}

CTpLogManager::~CTpLogManager()
{
	memset(m_abyTitlePool ,0 ,PoolSize+32);
	memset(m_apcLog,0,sizeof(m_apcLog) );
}

BOOL32 CTpLogManager::Init()
{
	m_achmsgLogLevel[enLogLowest][0] = '\0';
	m_achmsgLogLevel[enLogHint][0] = '\0';
	memcpy(&m_achmsgLogLevel[enLogError], "[Error]", strlen("[Error]"));
	m_achmsgLogLevel[enLoglowDetail][0] = '\0';
	return TRUE;
}
	
s8* CTpLogManager::CopyTitle(const s8* const title )
{
	const int  maxtitlelen = 64;
	if(NULL == title) 
		return "";
	

	if( m_wTitlePoolEndPos+maxtitlelen >= PoolSize )
		return "CKdvLogManager title pool full $";

	s8* pTitle = m_abyTitlePool+ m_wTitlePoolEndPos;
	strncpy( pTitle ,title ,maxtitlelen );
	m_wTitlePoolEndPos += strlen(title)+1;
	m_abyTitlePool[m_wTitlePoolEndPos]=0;
	return pTitle;

}

BOOL32 CTpLogManager::Regist(CTpLog* pcLogInst )
{
	if( !pcLogInst )
		return FALSE;
	if( m_wEndInst >= MaxInst )
		return FALSE;

	m_apcLog[m_wEndInst] = pcLogInst;
	m_wEndInst++;
	return TRUE;
}

void CTpLogManager::UnRegist(CTpLog* pcLogInst )
{
	for(int i=0 ;i< m_wEndInst ;i++ )
	{
		if(m_apcLog[m_wEndInst] == pcLogInst)
		{
			m_apcLog[m_wEndInst] = NULL;
			return ;
		}
	}
	return ;
}

void CTpLogManager::ShowAllInst()
{
	for( int i= 0 ;i < m_wEndInst ;i++ )
	{
		if( m_apcLog[i])
		{
			s8* title = m_apcLog[i]->GetTitle();
			
			msgprint( "(%8p) %s <%3d> [%s]\n", m_apcLog[i], i, title ? title:"null");
		}
	}
}

u16 CTpLogManager::GetEndInst()
{
	return m_wEndInst;
}

void setmdllogname(u32 dwMdl, s8* pszName)
{
	if ((dwMdl - MID_CNS_1) < MAX_MSGMDL_NUM && (dwMdl - MID_CNS_1 + 1) > 0)
	{
		strncpy(CTpLogManager::m_atmsgModelCtrl[dwMdl - MID_CNS_1].m_achlName, pszName, MAX_MDL_NAME);
	}
}

API void showmdlname()
{
	for( int i= 0 ;i < MAX_MSGMDL_NUM ;i++ )
	{
		msgprint(" mdl :%d, name :%s\n", i, CTpLogManager::m_atmsgModelCtrl[i].m_achlName);
	}
}

API void showlogtitle()
{
	CTpLogManager::ShowAllTitle();
}

API void showlastmsg()
{
	CTpLogManager::ShowLastMsg();
}

API void savelastmsg(s8* pszFile)
{
	CTpLogManager::SaveLastMsg(pszFile);
}

API void tplogdtl(u32 dwMdl)
{
	if(dwMdl == 0)
	{
		for(u32 i = 0; i < MAX_MSGMDL_NUM; ++i)
		{
			CTpLogManager::m_atmsgModelCtrl[i].m_bShow = TRUE;
		}
	}
	else
	{
		if((dwMdl - MID_CNS_1 + 1) > 0 && (dwMdl - MID_CNS_1) < MAX_MSGMDL_NUM )
		{
			CTpLogManager::m_atmsgModelCtrl[dwMdl - MID_CNS_1].m_bShow = TRUE;
		}
	}
	
	CTpLogManager::m_dwLogLevel = enLoglowDetail;
	
	if (CTpLogManager::m_bIsInitKdvLog)
	{
		logsetlvl(LOG_LVL_DETAIL);
	}
#ifdef _USE_LOG4CPLUS_
	if (CTpLogManager::m_bIsInitLog4cplus)
	{
		log4cpclient::SetDebugOn();
	}
#endif //_USE_LOG4CPLUS_
}

API void tploglow(u32 dwMdl)
{
	if(dwMdl == 0)
	{
		for(u32 i = 0; i < MAX_MSGMDL_NUM; ++i)
		{
			CTpLogManager::m_atmsgModelCtrl[i].m_bShow = TRUE;
		}
	}
	else
	{
		if((dwMdl - MID_CNS_1 + 1) > 0 && (dwMdl - MID_CNS_1) < MAX_MSGMDL_NUM )
		{
			CTpLogManager::m_atmsgModelCtrl[dwMdl - MID_CNS_1].m_bShow = TRUE;
		}
	}
	
	CTpLogManager::m_dwLogLevel = enLogLowest;
	if (CTpLogManager::m_bIsInitKdvLog)
	{
		logsetlvl(LOG_LVL_KEYSTATUS);
	}
#ifdef _USE_LOG4CPLUS_
	if (CTpLogManager::m_bIsInitLog4cplus)
	{
		log4cpclient::SetInfoOn();
	}
#endif //_USE_LOG4CPLUS_
}

API void setconsolelog(BOOL32 bOnoff)
{
	if (bOnoff)
	{
		SetPrintToCom(TRUE);
	}
	else
	{
		SetPrintToCom(FALSE);
	}
}

API void tplogon(u32 dwMdl)
{
	if(dwMdl == 0)
	{
		for (u32 i = 0; i < MAX_MSGMDL_NUM; ++i)
		{
			CTpLogManager::m_atmsgModelCtrl[i].m_bShow = TRUE;
		}
	}
	else
	{
		if ((dwMdl - MID_CNS_1) < MAX_MSGMDL_NUM && (dwMdl - MID_CNS_1 + 1) > 0)
		{
			CTpLogManager::m_atmsgModelCtrl[dwMdl - MID_CNS_1].m_bShow = TRUE;
		}
	}
	
	CTpLogManager::m_dwLogLevel = enLogHint;

	if (CTpLogManager::m_bIsInitKdvLog)
	{
		logsetlvl(LOG_LVL_WARNING);
	}
#ifdef _USE_LOG4CPLUS_
	if (CTpLogManager::m_bIsInitLog4cplus)
	{
		log4cpclient::SetWarnOn();
	}
#endif //_USE_LOG4CPLUS_
}


API void tplogoff()
{
	
	for (u32 i = 0; i < MAX_MSGMDL_NUM; ++i)
	{
		CTpLogManager::m_atmsgModelCtrl[i].m_bShow = FALSE;
	}
	CTpLogManager::m_dwLogLevel = enLogError;

	if (CTpLogManager::m_bIsInitKdvLog)
	{
		logsetlvl(LOG_LVL_ERROR);
	}

#ifdef _USE_LOG4CPLUS_
	if (CTpLogManager::m_bIsInitLog4cplus)
	{
		log4cpclient::SetErrorOn();
	}
#endif //_USE_LOG4CPLUS_
}

API void showlogstatus()
{
	OspPrintf(TRUE,FALSE, "CTpLogManager::m_bIsInitKdvLog->%d\n", CTpLogManager::m_bIsInitKdvLog );
	OspPrintf(TRUE,FALSE, "CTpLogManager::m_bIsPrintCom->%d\n", CTpLogManager::m_bIsPrintCom );
	OspPrintf(TRUE,FALSE, "CTpLogManager::m_dwLogLevel->%d\n", CTpLogManager::m_dwLogLevel );
#ifdef _USE_LOG4CPLUS_
	OspPrintf(TRUE,FALSE, "CTpLogManager::m_bIsInitLog4cplus->%d\n", CTpLogManager::m_bIsInitLog4cplus );
	log4cpclient::ShowInfo();
#endif //_USE_LOG4CPLUS_
}


/*
*
* Linux 系统内存捕获
* 
*/
#ifdef _LINUX_
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>
#include <errno.h>
#include <string.h>


Elf32_Sym *get_symtab(Elf32_Sym *symtab, int tabsize, int addr);
Elf32_Shdr * read_elf_section(FILE *file, Elf32_Ehdr *ehdr);
void *read_symtable(FILE *file, Elf32_Shdr *shdr, Elf32_Ehdr *ehdr,   int *size);
void *read_strtable(FILE *file, Elf32_Shdr *shdr, Elf32_Ehdr *ehdr,  int *size);
int  read_elf_head(FILE *file, Elf32_Ehdr *ehdr);
Elf32_Sym *get_func_symb_by_addr(Elf32_Sym *symtab, int tabsize, int addr);
int printf_symbl_name(int pc);

Elf32_Sym *sym;
char *strtab, *strDir;
int symsize, strsize;

void write_exc_log(const s8 *pachBuf, s32 nBufLen)
{
    if (NULL == pachBuf || nBufLen <= 0)
    {
        printf("invalid param in writeexclog. pachBuf.%d nBufLen.%d\n",
            (int)pachBuf, nBufLen);
        return;
    }  
    
    FILE *hLogFile = fopen(strDir, "r+b");
    if (NULL == hLogFile)
    {
        printf("exc.log not exist and create it. filename:%s\n", strDir);
        hLogFile = fopen(strDir, "w+b");
        if (NULL == hLogFile)
        {
            printf("create exc.log failed for %s\n", strerror(errno));     
			printf("***loginfo:%s \n", pachBuf);     
            return;
        }
    }
    
    fseek(hLogFile, 0, SEEK_END);
    s32 nLen = fwrite(pachBuf, nBufLen, 1, hLogFile);
    if (0 == nLen)
    {
        printf("write to exc.log failed\n");
        return;
    }
    
    fclose(hLogFile);
    return;
}

void write_mdl_exc()
{
	FILE *hLogFile = fopen(strDir, "r+b");
    if (NULL == hLogFile)
    {
        printf("exc.log not exist and create it\n");
        hLogFile = fopen(strDir, "w+b");
        if (NULL == hLogFile)
        {
            printf("create exc.log failed for %s\n", strerror(errno));     
            return;
        }
    }
	fseek(hLogFile, 0, SEEK_END);
	
	s8 szReason[255] = {0};
	s32 nLen = 0;
	sprintf(szReason, "------begin of mdl Dump----------\n\n");
    printf("%s", szReason);
	
	fputs(szReason, hLogFile);
	
	sprintf(szReason, "------end of mdl Dump----------\n\n");
    printf("%s", szReason);
	fputs(szReason, hLogFile);
	
    fclose(hLogFile);
}


#define SECTION_HEADER_INDEX(I)				\
  ((I) < SHN_LORESERVE					\
   ? (I)						\
   : ((I) <= SHN_HIRESERVE				\
      ? 0						\
      : (I) - (SHN_HIRESERVE + 1 - SHN_LORESERVE)))


/*test function that cause segment fault */

void test3sym()
{
	printf(" ");
}
void test4sym()
{
	printf(" ");
}
void testsym()
{
	int a[0x10000];
	
	a[0] = 0 ;
	test4sym();
	*(int *)0x10 = 0;	
}
void test1sym()
{	
	
	int a[0x10000];
	
	a[0] = 0 ;
	test3sym();
	
	testsym();
}
void test2sym()
{	int a[0x10000];
	
	a[0] = 0 ;
	test3sym();
	test4sym();
	test1sym();
}


#ifdef X86
/* parse cpu context information is architecture depent, 
   encapsulate as helper function can be easy */
int parse_x86_context(void* tmp)
{
	struct ucontext* ct = (struct ucontext*)tmp;	
	int* regs = (int*)ct->uc_mcontext.gregs;
	int  epc = regs[14];
	int *presp = (int *)regs[6];

	printf("\nexception instruction address: 0x%x\n", epc);
	
	printf("\n===================CPU registers==============================\n");

	printf("cpu register value:\n");
	printf("GS:0x%x\t FS:0x%x\t ES:0x%x\t DS:0x%x\n", 
	       regs[0], regs[1], regs[2], regs[3]);

	printf("CS:EIP:   0x%x:0x%x\nSS:UESP:  0x%x:0x%x\n", 
	       regs[15],regs[14], regs[18], regs[17]);

	printf("EDI:0x%x\t ESI:0x%x\t EBP:0x%x\n",regs[4], regs[5], regs[6]);
	printf("ESP:0x%x\t EBX:0x%x\t EDX:0x%x\n",regs[7], regs[8], regs[9]);
	printf("ECX:0x%x\t\t EAX:0x%x\n",regs[10], regs[11]);
	printf("TRAPNO:0x%x\t ERR:0x%x\t EFL:0x%x\n",regs[12], regs[13], regs[16]);

	printf("\n=================== call trace ==============================\n");


	/* ebp will record frame-pointer */
#if 0	
	*(stack-1) = epc;/* put the exception addr in the stack */
	for(i = -1;; i++) 
		if (printf_symbl_name(*(stack+i)) == -1)
			break;
#else
	printf_symbl_name(epc);/*fault addr*/
	while(1)
	{
		int ret = printf_symbl_name(*(presp + 1));
		if (ret == -1 || !ret)
		{
			if (!ret)
				printf("programs's user stack error !!\n");
			break;
		}
		presp = (int *)(*(presp));/* pre function's base sp */		
	}
	
#endif			
	free(sym);
	free(strtab);
	return 0;
}
#endif

#ifdef PPC
/* parse cpu context information is architecture depent, 
   encapsulate as helper function can be easy */
int parse_ppc_context(void* tmp)
{
	struct ucontext* ct = (struct ucontext*)tmp;
	int* regs = (int*)ct->uc_mcontext.regs;
	int  epc = regs[32];
	int* stack = (int*)regs[1];
	int  link = regs[36];/* link register */
	int* presp = (int *)(*stack);

	printf("\nexception instruction address: 0x%x\n", epc);

	printf("\n=================== call trace ==============================\n");
	
	char achInfo[255];
    time_t tiCurTime = ::time(NULL);             
    int nLen = sprintf(achInfo, "Sytem time %s\n", ctime(&tiCurTime));
    write_exc_log(achInfo, nLen);
    nLen = sprintf(achInfo, "Exception instruction address: 0x%x\n", epc);
    write_exc_log(achInfo, nLen);
    nLen = sprintf(achInfo, "=========== call trace ============\n");
    write_exc_log(achInfo, nLen);

	/* ebp will record frame-pointer */

	int func_size ;
	func_size = printf_symbl_name(epc);/*fault addr*/
	if (func_size > 0)/* link register and faule addr may be in the same function so do follows */
	{
		if ((epc - link < 0) || (epc - link >= func_size))
			printf_symbl_name(link);
	}
	
	while(1)
	{
		int ret = printf_symbl_name(*(presp + 1));
		if (ret == -1 || !ret)
		{
			if (!ret)
				printf("programs's user stack error !!\n");
			break;
		}
		presp = (int *)(*(presp));/* pre function's base sp */		
	}
	
	free(sym);
	free(strtab);
	return 0;
}
#endif
#ifdef ARM
int parse_arm_context(void* tmp)
{
	struct ucontext* ct = (struct ucontext*)tmp;
	struct sigcontext* sc  = &ct->uc_mcontext;
	int  epc = sc->arm_pc;
	int* presp = (int *)sc->arm_fp;

	printf("lr %lx pc %lx sp %lx ip %lx fp %lx\r\n", sc->arm_lr, sc->arm_pc, sc->arm_sp, sc->arm_ip, sc->arm_fp);
	printf("\nexception instruction address: 0x%x\n", epc);

	printf("\n=================== call trace ==============================\n");
	/* ebp will record frame-pointer */
#if 0	
	*(stack-1) = epc;/* put the exception addr in the stack */
	for(i = -1;; i++) 
		if (printf_symbl_name(*(stack+i)) == -1)
			break;
#else
	int func_size ;
	func_size = printf_symbl_name(epc);/*fault addr*/

	while(1)
	{
		int ret = printf_symbl_name(*(presp - 1));
		if (ret == -1 || !ret)
		{
			if (!ret)
				printf("programs's user stack error !!\n");
			break;
		}
		presp = (int *)(*(presp-3));/* pre function's base sp */		
	}
#endif			
	free(sym);
	free(strtab);
	return 0;	
}	
#endif
void parse_context(void* uc)
{
#ifdef X86		
	parse_x86_context(uc);
#endif
#ifdef PPC	
	parse_ppc_context(uc);
#endif	
#ifdef ARM
	parse_arm_context(uc);
#endif
}

int printf_symbl_name(int pc)
{
	Elf32_Sym *syml = get_func_symb_by_addr(sym,symsize, pc);
	if (syml) {
		if (syml->st_name >= strsize)
		{
			//printf("st_name if big then strtable size\r\n");
			return 1;
		}
		//return (strtab+syml->st_name);
		printf("pc:%x %s\r\n", pc, (strtab+syml->st_name));
		char achInfo[255];
        int nLen = sprintf(achInfo, "pc:%x %s\r\n", pc, (strtab+syml->st_name));
        write_exc_log(achInfo, nLen);

		if (!strcmp((strtab+syml->st_name), "main"))		
			return -1;
			
		return syml->st_value;	
	}	
	return 0;
}
void my_sigaction(int signo, siginfo_t* info, void* ct)
{
	s8 szReason[255] = {0};
	time_t ti;
	struct tm t;

	time(&ti);	
	tplocaltime(t, ti);
	
	sprintf( szReason, "\n\nbegin exc at time: %2.2u-%2.2u %2.2u:%2.2u:%2.2u signo:%d %d \n", 
		t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec, signo, CTpLogManager::GetEndInst() );
    printf( "%s", szReason );
	write_exc_log(szReason, strlen(szReason));

	CTpLogManager::SaveLastMsg(strDir);

	if(signo == SIGSEGV)
	{
		sprintf( szReason, "catch segment fault! pid = %d\n", getpid() );
	}
	if(info->si_code == SI_KERNEL)
		sprintf( szReason, "signal is send by Kernel\n");

	printf( "%s", szReason );
	write_exc_log(szReason, strlen(szReason)); 


	sprintf( szReason, "caused by:\t" );
    printf( "%s", szReason );
	write_exc_log(szReason, strlen(szReason)); 

	if(info->si_code == SEGV_MAPERR)
		sprintf( szReason, "access a fault address: %p\n", info->si_addr );
	else if(info->si_code == SEGV_ACCERR)
		sprintf( szReason, "access a no permission address: %p\n", info->si_addr );
	else
		sprintf( szReason, "unknow reason\n" );

	printf( "%s", szReason );
	write_exc_log(szReason, strlen(szReason)); 

	if (ct)
		parse_context(ct);
	else
		printf("process context is NULL\n");	

	sprintf(szReason, "------End of Crash Dump----------\n\n");
    printf( "%s", szReason );
    write_exc_log(szReason, strlen(szReason));
    if ( strDir )
		free( strDir );
	/* sigment fault is critical fault, we should exit right now */

	exit(1);
}


void unload(int signo, siginfo_t* info, void* ct)
{
	OspPrintf(TRUE, FALSE, "Caught SIGINT, will unload dsp\n");
	printf("Caught SIGINT, will unload dsp\n");
	exit(1);
}


void install_sigaction()
{
	struct sigaction sigact;

	sigemptyset (&sigact.sa_mask);
	//memset(&sigact, 0, sizeof (struct sigaction));
	sigact.sa_flags = SA_ONESHOT | SA_SIGINFO;
	sigact.sa_sigaction = my_sigaction;
	sigaction(SIGSEGV , &sigact, NULL);	

	sigemptyset (&sigact.sa_mask);
	//memset(&sigact, 0, sizeof (struct sigaction));
	sigact.sa_flags = SA_ONESHOT | SA_SIGINFO;
	sigact.sa_sigaction = unload;
	sigaction(SIGINT , &sigact, NULL);	
}



/* get the function'symbol that the "addr" is in the function or the same of the function */
Elf32_Sym *get_func_symb_by_addr(Elf32_Sym *symtab, int tabsize, int addr)
{	
	for (;tabsize > 0; tabsize -= sizeof(Elf32_Sym), symtab ++)
	{		
#if 1
		if (ELF32_ST_TYPE(symtab->st_info) != STT_FUNC || symtab->st_shndx == 0)/* we only find the function symbol and not a und  */	
			continue;
		if (!symtab->st_value)
			continue;
		if (addr >= symtab->st_value && addr < (symtab->st_size+symtab->st_value))
			return symtab;	
#else
		if (ELF32_ST_TYPE(symtab->st_info) == STT_FUNC)/* we only find the function symbol */	
			printf("name %s addr %x size %x\r\n", (strtab+symtab->st_name), symtab->st_value, symtab->st_size);
#endif			
	}
	return NULL;
}	


Elf32_Sym *get_symbol(Elf32_Sym *symtab, int tabsize, int addr)
{
	for (;tabsize > 0; tabsize -= sizeof(Elf32_Sym), symtab ++)
		if (symtab->st_value == addr)
			return symtab;

	return NULL;		
}
Elf32_Shdr * read_elf_section(FILE *file, Elf32_Ehdr *ehdr)
{
	Elf32_Shdr *pshdr;	
	int s_size = ehdr->e_shentsize * ehdr->e_shnum;
	
	pshdr = (Elf32_Shdr *)malloc(s_size);
	if (pshdr == NULL) 
	{
		printf("malloc shdr error\r\n");
		return NULL;
	}	

	if (fseek (file, ehdr->e_shoff, SEEK_SET))
	{
		printf("fseek error\r\n");
		return NULL;
	}	
	
	if (fread(pshdr, s_size, 1, file) != 1)
	{
		printf("read file error in func %s\r\n", __func__);
		return NULL;
	}

	return pshdr;
}


void *read_symtable(FILE *file, Elf32_Shdr *shdr, Elf32_Ehdr *ehdr, int *size)
{
	int sec_num;
	int tb_size;
	void *sym;

	
	for (sec_num = 0; sec_num < ehdr->e_shnum; sec_num ++, shdr ++)
	{
		if (shdr->sh_type == SHT_SYMTAB)
			break;
	}	
	
	if (sec_num == ehdr->e_shnum)
	{
		printf("No symbol table\n");
		return NULL;
	}
	*size = tb_size = shdr->sh_size;
	
	sym = (void *)malloc(tb_size);
	if (sym ==NULL)
	{	
		printf("malloc error in func %s\r\n", __func__);
		return NULL;
	}
	if (fseek (file, shdr->sh_offset, SEEK_SET))
	{
		printf("fseek error\r\n");
		return NULL;
	}	

	if (fread(sym, tb_size, 1, file) != 1)
	{
		printf("read file error in func %s\r\n", __func__);
		return NULL;
	}	
	return sym;
}

void *read_strtable(FILE *file, Elf32_Shdr *shdr, Elf32_Ehdr *ehdr,  int *size)
{
	int sec_num;
	int tb_size;
	void *sym;
	Elf32_Shdr *lshdr = shdr;
	
	for (sec_num = 0; sec_num < ehdr->e_shnum; sec_num ++, shdr ++)
	{
		if (shdr->sh_type == SHT_SYMTAB)
			break;
	}	

	shdr  = lshdr + SECTION_HEADER_INDEX(shdr->sh_link);
	
	*size = tb_size = shdr->sh_size;
	
	sym = (void *)malloc(tb_size);
	if (sym ==NULL)
	{	
		printf("malloc error in func %s\r\n", __func__);
		return NULL;
	}
	if (fseek (file, shdr->sh_offset, SEEK_SET))
	{
		printf("fseek error\r\n");
		return NULL;
	}	

	if (fread(sym, tb_size, 1, file) != 1)
	{
		printf("read file error in func %s\r\n", __func__);
		return NULL;
	}	

	return sym;
}

int  read_elf_head(FILE *file, Elf32_Ehdr *ehdr)
{
	if (fread(ehdr, sizeof(Elf32_Ehdr), 1, file) != 1)
		return -1;

	return 0;
}


int regist_exception(const s8 *pachModuleName ,const s8* LogName)
{	
	Elf32_Ehdr ehdr;
	Elf32_Shdr *shdr;
	FILE *file;

	install_sigaction();
	
	file = fopen(pachModuleName, "rb");
	if (file == NULL)
	{
		printf("open file %s error\r\n",pachModuleName);
		return 0;
	}

	/* read the elf file's head */
	if (read_elf_head(file, &ehdr) == -1)
		return 0;
	
	/* read all sections of the elf file */
	shdr = read_elf_section(file, &ehdr);
	if (shdr == NULL)
		return 0;

	/* read static symbol table through symbol section*/
	sym = (Elf32_Sym *)read_symtable(file, shdr, &ehdr,  &symsize);
	if (sym == NULL)
		return 0;
	
	/* read string table through string section */
	strtab = (char *)read_strtable(file, shdr, &ehdr, &strsize);
	if (strtab == NULL)
		return 0;

	free(shdr);

	
    if ( LogName )
	{
    	strDir = (char*)malloc(strlen(LogName)+1);
		strncpy( strDir, LogName, strlen(LogName) );
	}
	else
		strDir = NULL;
	//test2sym();/* cause exception of segment fault */
	
	return 0;
}

#endif  //_LINUX_

} //namespace UmsTpmsg