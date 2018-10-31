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
	u16	  m_wLastEventID;	//���һ���������Ϣ
	BOOL  m_bInHandMsg;		//�Ƿ��ڴ�����,   ��Ϣ�����TRUE��������FALSE

protected:

	void Error(s8* szFormat, ...);
	void Hint(s8* szFormat, ...);
	void LowHint(s8* szFormat, ... );
	void LowDtlHint(s8* szFormat, ... );

	void SetLogTitle( s8* title );//������־��ӡ����

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
void msgprint( char *szFormat, ... ); // ֱ�Ӵ�ӡ����ʱ�䣬һ������show
void msgprintnotime( char *szFormat, ... ); // ֱ�Ӵ�ӡ������ʱ��

void setmdllogname(u32 dwMdl, s8* pszName);

//�ſ�ָ��ģ��Ĵ�ӡ�� 0Ϊ����
API void tplogon(u32 dwMdl);
API void tploglow(u32 dwMdl);
API void tplogdtl(u32 dwMdl);
API void tplogoff();

// ��Ҫ�̳�log�࣬�����ڲ�ֱ�ӵ��ã���ʾmdl����title��
#define ObjLowDtl(printParams)			LowDtlHint printParams;
#define ObjLowHint(printParams)			LowHint printParams;
#define ObjHint(printParams)			Hint printParams;
#define ObjError(printParams)			Error printParams;

// ���ã���mdl��
void MsgPrintLowDtlLog( s8* szFormat, ...);
void MsgPrintLowHintLog(s8* szFormat, ...);
void MsgPrintHintLog(s8* szFormat, ...);
void MsgPrintErrorLog(s8* szFormat, ...);

// �Ƽ��ã�����ָ��mdl��
void tpLowDtl( u16 wMdl,s8* szFormat, ...);
void tpLowHint( u16 wMdl,s8* szFormat, ...);
void tpHint( u16 wMdl, s8* szFormat, ...);
void tpError(u16 wMdl, s8* szFormat, ...);

// ���Ƽ��ã��޷�ָ��mdl��
#define MdlLowDtl(mdl, printParams)			MsgPrintLowDtlLog printParams;
#define MdlLowHint(mdl, printParams)		MsgPrintLowHintLog printParams;
#define MdlHint(mdl, printParams)			MsgPrintHintLog printParams;
#define MdlError(mdl, printParams)			MsgPrintErrorLog printParams;

// ���������־�ļ�,����Ƶ�����õ����̴�ӡ
void tpLowDtlNoFile( u16 wMdl,s8* szFormat, ...);
void tpLowHintNoFile( u16 wMdl,s8* szFormat, ...);
void tpHintNoFile( u16 wMdl, s8* szFormat, ...);
void tpErrorNoFile(u16 wMdl, s8* szFormat, ...);

/*
1. ��ӡ���� loglowdtl < loglowhint < hint < error 
2. ������͵�lowdtl�����������־�ļ���һ�����ڹؼ�֡��Ϣ��ӡ�����༶�𶼻��������־�ļ�
3. ������ƺ�����ֻ�ı����̨����ļ��𣬲�Ӱ���������־�ļ�
4. ��־�ļ�ͨ��kdvlogserver���������������־���棬ͨ��SetLogFlush��������־�����������漴��д���ļ�
5. kdvlog�ͻ��˲������ļ���ͨ��initKdvLog��һ�������ṩ������������־��������ip
*/

//�쳣ʱ���
#ifdef _LINUX_
int regist_exception(const s8 *pachModuleName ,const s8* LogName);
#endif

void regist_tp_commond();

BOOL32 initKdvLog(s8 * pchName, BOOL32 bPrintToCom = FALSE);
void SetPrintToCom(BOOL32 bPrint);
void SetLogFlush(); //����־����������д���ļ�
void ExitKdvLog();



#ifdef _USE_LOG4CPLUS_
#define MAX_MOD_NAME_LEN  32
BOOL32 initLog4CPlusLog(s8 *pchCfgFileName, s8 *pchModeName, BOOL32 bPrintToCom = FALSE);
void   ExitLog4CPlusLog();
#endif //_USE_LOG4CPLUS_


} //namespace UmsTpmsg

using namespace UmsTpmsg;

#endif//!_h_tplog_h__


