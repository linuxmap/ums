#ifndef _h_tplog_h__
#define _h_tplog_h__


#include "osp.h"
#include "tplogmgr.h"
#include "tpmsg.h"
#include "loguserdef.h"
#include "tpsys.h"


#ifdef WIN32
#ifndef vsnprintf
#define vsnprintf		_vsnprintf
#endif

#ifndef snprintf
#define snprintf		_snprintf
#endif

#ifndef strncasecmp
#define strncasecmp		_strnicmp
#endif
#endif


#define MAX_MSG_LEN_TMP 235


namespace UmsTpmsg {

enum ENLogLevel
{
	enLoglowDetail = LOG_LVL_DETAIL,
	enLogLowest = LOG_LVL_KEYSTATUS,
	enLogHint = LOG_LVL_WARNING,
	enLogError = LOG_LVL_ERROR,
};

class CTpLog
{
public:
	CTpLog();
	virtual ~CTpLog();

protected:
	s8*   m_pLogTitle;

	u16   m_wLogModuleId;
	u16	  m_wLastEventID;	//最后一条处理的消息
	BOOL  m_bInHandMsg;		//是否还在处理中,   消息入口置TRUE，出口置FALSE

protected:

	void Error(s8* szFormat, ...);
	void Hint(s8* szFormat, ...);
	void LowHint(s8* szFormat, ... );
	void LowDtlHint(s8* szFormat, ... );

	void SetLogTitle( s8* title );//设置日志打印标题

public:
	virtual u16  GetLogApp()				{ return 0; }	
	virtual u16  GetLogInst()				{ return 0; }
	s8*  GetTitle()							{ return m_pLogTitle; }	
	u16  GetLastEventID(void)	const		{ return m_wLastEventID; }	
	BOOL GetInHandMsg() const				{ return m_bInHandMsg; }
	void SetLogModule( u16 wModuleId){m_wLogModuleId = wModuleId;};
	void SetLastEventID(u16 dwEventID)		{ m_wLastEventID = dwEventID; }
	void SetInHandMsg(BOOL bInHandMsg )		{ m_bInHandMsg = bInHandMsg; }
};

void printcallid(u8* pCallID, u16 wCallSize, BOOL32 bPauseZero = TRUE);
void msgprint( char *szFormat, ... ); // 直接打印，带时间，一般用于show
void msgprintnotime( char *szFormat, ... ); // 直接打印，不带时间

void setmdllogname(u32 dwMdl, s8* pszName);

//放开指定模块的打印， 0为所有
API void tplogon(u32 dwMdl);
API void tploglow(u32 dwMdl);
API void tplogdtl(u32 dwMdl);
API void tplogoff();

// 需要继承log类，可以内部直接调用，显示mdl名，title名
#define ObjLowDtl(printParams)			LowDtlHint printParams;
#define ObjLowHint(printParams)			LowHint printParams;
#define ObjHint(printParams)			Hint printParams;
#define ObjError(printParams)			Error printParams;

// 慎用，无mdl名
void MsgPrintLowDtlLog( s8* szFormat, ...);
void MsgPrintLowHintLog(s8* szFormat, ...);
void MsgPrintHintLog(s8* szFormat, ...);
void MsgPrintErrorLog(s8* szFormat, ...);

// 推荐用，可以指定mdl名
void tpLowDtl( u16 wMdl,s8* szFormat, ...);
void tpLowHint( u16 wMdl,s8* szFormat, ...);
void tpHint( u16 wMdl, s8* szFormat, ...);
void tpError(u16 wMdl, s8* szFormat, ...);

// 不推荐用，无法指明mdl名
#define MdlLowDtl(mdl, printParams)			MsgPrintLowDtlLog printParams;
#define MdlLowHint(mdl, printParams)		MsgPrintLowHintLog printParams;
#define MdlHint(mdl, printParams)			MsgPrintHintLog printParams;
#define MdlError(mdl, printParams)			MsgPrintErrorLog printParams;

// 不输出到日志文件,适用频繁调用的流程打印
void tpLowDtlNoFile( u16 wMdl,s8* szFormat, ...);
void tpLowHintNoFile( u16 wMdl,s8* szFormat, ...);
void tpHintNoFile( u16 wMdl, s8* szFormat, ...);
void tpErrorNoFile(u16 wMdl, s8* szFormat, ...);

/*
1. 打印级别 loglowdtl < loglowhint < hint < error 
2. 级别最低的lowdtl不会输出到日志文件，一般用于关键帧消息打印，其余级别都会输出到日志文件
3. 级别控制函数，只改变控制台输出的级别，不影响输出到日志文件
4. 日志文件通过kdvlogserver服务器输出，有日志缓存，通过SetLogFlush可以让日志服务器将缓存即可写入文件
5. kdvlog客户端侧配置文件，通过initKdvLog第一个参数提供，可以配置日志服务器的ip
*/

//异常时输出
#ifdef _LINUX_
int regist_exception(const s8 *pachModuleName ,const s8* LogName);
#endif

void regist_tp_commond();

BOOL32 initKdvLog(s8 * pchName, BOOL32 bPrintToCom = FALSE);
void SetPrintToCom(BOOL32 bPrint);
void SetLogFlush(); //将日志缓冲区数据写入文件
void ExitKdvLog();



#ifdef _USE_LOG4CPLUS_
#define MAX_MOD_NAME_LEN  32
BOOL32 initLog4CPlusLog(s8 *pchCfgFileName, s8 *pchModeName, BOOL32 bPrintToCom = FALSE);
void   ExitLog4CPlusLog();
#endif //_USE_LOG4CPLUS_


} //namespace UmsTpmsg

using namespace UmsTpmsg;

#endif//!_h_tplog_h__


