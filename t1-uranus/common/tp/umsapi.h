#ifndef _h_umsapi_h__
#define _h_umsapi_h__

#include "osp.h"
#include "patype.h"
#include "tpstruct.h"
#include "umsinnertype.h"
#include "umscommonstruct.h"
#include "eventoutumseqp.h"
#include "umsobject.h"
#include "tptype.h"
#include "kdvsys.h"

enum ums_stack_print_info
{
	ums_stack_print_makecall,
	ums_stack_print_answercall,
	ums_stack_print_makesenddual,
	ums_stack_print_channelconnect,
	ums_stack_print_ConfEpCallInfo,
	ums_stack_print_ConfEpChanInfo,
	ums_stack_print_ConfEpIDInfo,
	ums_stack_print_CallIncoming,
	ums_stack_print_makechan,
};

#ifdef _LINUX_

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_) || defined(_LINUX12_)
#define emUmsBrdCfg "/usr/conf/umsbrdcfg.ini"
#else
#define emUmsBrdCfg "/usr/umsbrdcfg.ini"
#endif
#else
#define emUmsBrdCfg "umsbrdcfg.ini"
#endif

#ifdef WIN32
#define emUmsmpcExeFileName "umsmpc"
#define emUmsmpcKdvLogCfg "umsmpclog.ini" // logclient的配置
#define emUmsmpcCfg "umsmpccfg.ini"

#define emUmsSipAdapterLogCfgFileName "umssipadapterlog.ini" // logclient的配置
#define emUmsSipAdapterCfgFileName "umssipadaptercfg.ini"
#define emUmssipadapterLog4cplusCfg "umssipadapterlog4cplus.cfg"

#define emUmsMdiatransLogCfgFileName "umsmdiatranslog.ini" // logclient的配置
#define emUmsMdiatransCfgFileName "umsmediatranscfg.txt"

#define emUmsNetbufLogCfgFileName "umsnblog.ini" // logclient的配置
#define emUmsNetbufCfgFileName "umsnbcfg.txt"
#else

#if defined(_PPC_82XX_) || defined(_PPC_85XX_) || defined(_PPC_8377_)
#define emUmsmpcExeFileName "/usr/bin/umsmpc"
#define emUmsmpcExceptionFileName "/usr/conf/umsmpcexception.txt"
#define emUmsmpcKdvLogCfg "/usr/conf/umsmpclog.ini" // logclient的配置
#define emUmsmpcCfg "/usr/conf/umsmpccfg.ini"

#define emUmsSipAdapterExeFileName "/usr/bin/umssipadapter"
#define emUmsSipAdapterExceptionFileName "/usr/conf/umssipadapterexception.txt"
#define emUmsSipAdapterLog4cpExeFileName "/usr/conf/umssipadapter_log4cplus"
#define emUmsSipAdapterLog4cpExceptionFileName "/usr/conf/umssipadapterlog4cpexception.txt"
#define emUmsSipAdapterLogCfgFileName "/usr/conf/umssipadapterlog.ini" // logclient的配置
#define emUmsSipAdapterCfgFileName "/usr/conf/umssipadaptercfg.ini"
#define emUmssipadapterLog4cplusCfg "/usr/conf/umssipadapterlog4cplus.cfg"

#define emUmsNetbufExeFileName "/usr/bin/umsnetbuf"
#define emUmsNetbufExceptionFileName "/usr/conf/umsnbexception.txt"
#define emUmsNetbufLogCfgFileName "/usr/conf/umsnblog.ini" // logclient的配置
#define emUmsNetbufCfgFileName "/usr/conf/umsnbcfg.txt"

#define emUmsMdiatransExeFileName "/usr/bin/umsmediatrans"
#define emUmsMdiatransExceptionFileName "/usr/conf/umsmediatransexception.txt"
#define emUmsMdiatransLogCfgFileName "/usr/conf/umsmdiatranslog.ini" // logclient的配置
#define emUmsMdiatransCfgFileName "/usr/conf/umsmediatranscfg.txt"

#else
#define emUmsmpcExeFileName "/tp/umsmpc"
#define emUmsmpcExceptionFileName "/tp/umsmpcexception.txt"
#define emUmsmpcKdvLogCfg "/usr/umsmpclog.ini" // logclient的配置
#define emUmsmpcCfg "/usr/umsmpccfg.ini"

#define emUmsSipAdapterExeFileName "/tp/umssipadapter"
#define emUmsSipAdapterExceptionFileName "/tp/umssipadapterexception.txt"
#define emUmsSipAdapterLog4cpExeFileName "/tp/umssipadapter_log4cplus"
#define emUmsSipAdapterLog4cpExceptionFileName "/tp/umssipadapterlog4cpexception.txt"
#define emUmssipadapterLog4cplusCfg "/tp/umssipadapterlog4cplus.cfg"
#define emUmsSipAdapterLogCfgFileName "/usr/umssipadapterlog.ini" // logclient的配置
#define emUmsSipAdapterCfgFileName "/usr/umssipadaptercfg.ini"

#define emUmsNetbufExeFileName "/tp/umsnetbuf"
#define emUmsNetbufExceptionFileName "/tp/umsnbexception.txt"
#define emUmsNetbufLogCfgFileName "/usr/umsnblog.ini" // logclient的配置
#define emUmsNetbufCfgFileName "/usr/umsnbcfg.txt"

#define emUmsMdiatransExeFileName "/tp/umsmediatransnew"
#define emUmsMdiatransExceptionFileName "/tp/umsmediatransexception.txt"
#define emUmsMdiatransLogCfgFileName "/usr/umsmdiatranslog.ini" // logclient的配置
#define emUmsMdiatransCfgFileName "/usr/umsmediatranscfg.txt"
#endif

#endif

#define INSIGN "<<"
#define OUTSIGN ">>"

class CTpTypeAdpt
{
public:
	
	static u8 GetVidPayloadValue(EmTpVideoFormat emFormat);
	static u8 GetAudPayloadValue(EmTpAudioFormat emFormat);

	static EmTpAudioFormat GetAudioFormat( u16 wAFormat );

	static EmDualReason GetDualReason(EmTPDualReason emType);
	static EmTPDualReason GetDualReason(EmDualReason emType);

	static u32 GetLocalIP(u8 byIndex, u8 bySubIndex = 1);
	static u32 GetLocalIPPerfer(u8 byIndex, u8 bySubIndex);
	static u32 GetLocalNetMask(u8 byIndex, u8 bySubIndex = 1);
	static u32 GetLocalNetMaskPerfer(u8 byIndex, u8 bySubIndex);
	static void GetLocalMacAddr(u8 byIndex,  u8* pszMacAddr);

	static u32 GetChannelHandle(const EmChannelHandle& emChHandle, u16 wIndex);
	static void GetChannelIndex(u32 dwHandle, EmChannelHandle& emChHandle, u16& wIndex);

	static BOOL32 IsDualChannel(u32 dwChanHandle);

	static void GetWHByVidResolution( EmTpVideoResolution emResolution, u16 &wWidth, u16 &wHeight );
	static BOOL32 ResolutionSmallOpr( EmTpVideoResolution emLeft, EmTpVideoResolution emRight );
	static BOOL32 ResolutionEqualOpr( EmTpVideoResolution emLeft, EmTpVideoResolution emRight );
	static BOOL32 ResolutionMaxOpr( EmTpVideoResolution emLeft, EmTpVideoResolution emRight );
	static BOOL32 CapMaxOpr( TUmsVidFormat* ptLeft, TUmsVidFormat* ptRight );
	
	static BOOL32 IsVidTransNeedBas(const TUmsVidFormat& tSnd, const TUmsVidFormat& tRcv );

	//从发送数组中选择一个最适合接收的格式, 返回数组中的某个索引
	static const u16 GetRcvFormat(const TUmsVidFormat& tRcv, const TUmsVidFormat tSnd[], u16 wNum);

	//从模板中选择一个最适合作为发送的格式，返回模板数组中的索引
	static const u16 GetRcvFormatForSnd(const TUmsVidFormat& tSnd, const TUmsConfBase& tConfBase);

	//验证协商的能力是否符合模板的能力
	static BOOL32 IsValidPriFormat(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase, BOOL32 bIsCns, BOOL32 bIsSnd);
	static BOOL32 IsValidDualFormat(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase, BOOL32 bIsCns, BOOL32 bIsSnd);
	
	//计算出媒体格式在bas中占用的资源值
	static u16 CalcBasOutChnEncRes( u8 byOutChnNum, TUmsVidFormat atVidParam[] );

	//add
	static BOOL32 IsEqualConfBaseCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase);
	static BOOL32 IsEqualDualConfCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase);
	//返回该位置在会议模板中的数组索引
	static u16 GetSuitConfBaseCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase);//主流
	static u16 GetSuitDualConfCap(const TUmsVidFormat& tLeft, const TUmsConfBase& tConfBase);//双流

	static void GetConfBaseMaxCap(const TUmsConfBase& tConfBase, u16& wMaxHp, u16& wMaxBp);
	static void GetConfBaseMinCap(const TUmsConfBase& tConfBase, u16& wMinHp, u16& wMinBp);

	static u16 GetVmpMemberNumByStyle(const EMVmpStyle& emStyle);
	static EmTpVideoResolution GetVmpMemberResByChnlIndx(const EMVmpStyle& emStyle, u16 wChnIndx);

	static void PrintMsgWithStack(ums_stack_print_info type, u8* pBuf, const TUmsHandle& tHandle, s8* sign);

	static EmTpStartConfRet GetConfRetByCallReason(const EmCnsCallReason& emCallRet);

	static BOOL32 PortIsVaild( u16 wPort );
	
	static void StartNtpd( u32_ip dwServerIp ); 

	static void GetMaxCap(const TUmsVidFormat* ptFormat, u8 byNum, u16& wMaxIndex);
};

namespace UmsTpmsg {
    void tplocaltime(struct tm& t, const time_t& ti);
} //namespace UmsTpmsg

API void showsem();
API void semlogon();
API void semlogoff();

#define CSemInfo_Des_Len 128

class CSemInfo
{
public:
	static CSemInfo* GetSem()
	{
		if( m_pcSem == NULL )
		{
			m_pcSem = new CSemInfo;

#ifdef _LINUX_
			OspRegCommand("showsem", (void*)showsem, "showsem()");
			OspRegCommand("semlogon", (void*)semlogon, "semlogon()");
			OspRegCommand("semlogoff", (void*)semlogoff, "semlogoff()");
#endif
		}

		return m_pcSem;
	}

	void SemIn( char *szDes, ... )
	{
		if(szDes == NULL)
			return;
		
		m_dwTimeIn = 0;
		memset(m_acDesIn, 0, sizeof(m_acDesIn));
		
		time_t ti;
		time(&ti);

		m_dwTimeIn = ti;

		struct tm t;
		tplocaltime(t, ti);
		int lenTime = sprintf(m_acDesIn, "%2.2u-%2.2u %2.2u:%2.2u:%2.2u ", t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

		va_list pvList;
		va_start(pvList, szDes);
		
		int len = vsnprintf( m_acDesIn + lenTime, CSemInfo_Des_Len - lenTime, szDes, pvList);
		if ( len > 0 ) 
		{
			m_acDesIn[sizeof(m_acDesIn)-1] = '\0'; 
		}
		else if (len == -1)
		{
			OspPrintf(TRUE,FALSE, "SemIn( char *szDes, ... ) failed!\n");
		}

		OspPrintf(m_bLogon,FALSE, "%s\n", m_acDesIn);
		
		va_end(pvList);	
	}

	void SemOut( char *szDes, ... )
	{
		if(szDes == NULL)
			return;
		
		m_dwTimeOut = 0;
		memset(m_acDesOut, 0, sizeof(m_acDesOut));
		
		time_t ti;
		time(&ti);

		m_dwTimeOut = ti;

		struct tm t;
		tplocaltime(t, ti);
		int lenTime = sprintf(m_acDesOut, "%2.2u-%2.2u %2.2u:%2.2u:%2.2u ", t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
		
		va_list pvList;
		va_start(pvList, szDes);
		
		int len = vsnprintf( m_acDesOut + lenTime, CSemInfo_Des_Len - lenTime, szDes, pvList);
		if ( len > 0 ) 
		{
			m_acDesOut[sizeof(m_acDesOut)-1] = '\0'; 
		}
		else if (len == -1)
		{
			OspPrintf(TRUE,FALSE, "SemOut( char *szDes, ... ) failed!\n");
		}

		OspPrintf(m_bLogon,FALSE, "%s\n", m_acDesOut);

		if ( m_dwTimeOut - m_dwTimeIn > m_dwTimeIntrval )
		{//备份一份异常打印

			m_dwTimeIntrval = m_dwTimeOut - m_dwTimeIn;

			OspPrintf(TRUE,FALSE, "CSemInfo Time Out:%d !!!!\n", m_dwTimeOut - m_dwTimeIn);

			memcpy(m_acDesInTmp, m_acDesIn, sizeof(m_acDesIn));
			memcpy(m_acDesOutTmp, m_acDesOut, sizeof(m_acDesOut));

			Show();
		}
		
		va_end(pvList);	
	}

	void Show()
	{
		OspPrintf(TRUE,FALSE, "Time Max Interval:%d\n", m_dwTimeIntrval);
		OspPrintf(TRUE,FALSE, "%s\n", m_acDesIn);
		OspPrintf(TRUE,FALSE, "%s\n\n", m_acDesOut);

		OspPrintf(TRUE,FALSE, "Tmp Info：\n");
		OspPrintf(TRUE,FALSE, "%s\n", m_acDesInTmp);
		OspPrintf(TRUE,FALSE, "%s\n", m_acDesOutTmp);
	}

	void LogOn() { m_bLogon = TRUE; }
	void LogOff() { m_bLogon = FALSE; }

protected:

	CSemInfo()
	{
		m_pcSem = NULL;
		memset(m_acDesIn, 0, sizeof(m_acDesIn));
		memset(m_acDesOut, 0, sizeof(m_acDesOut));
		memset(m_acDesInTmp, 0, sizeof(m_acDesInTmp));
		memset(m_acDesOutTmp, 0, sizeof(m_acDesOutTmp));

		m_dwTimeIn = 0;
		m_dwTimeOut = 0;

		m_dwTimeIntrval = 1;
		m_bLogon = FALSE;
	}

private:
	s8 m_acDesIn[CSemInfo_Des_Len];
	s8 m_acDesOut[CSemInfo_Des_Len];
	u32 m_dwTimeIn;
	u32 m_dwTimeOut;

	u32 m_dwTimeIntrval;

	s8 m_acDesInTmp[CSemInfo_Des_Len];
	s8 m_acDesOutTmp[CSemInfo_Des_Len];

	BOOL32	m_bLogon;

	static CSemInfo* m_pcSem;
};


BOOL TpMakeDir(const s8* path );

void TPSetSysTime(TTPTime& tTime);
void TPGetSysTime(TTPTime& tTime);
s8 *ConvertDateFormat();	//获取软件版本中编译时间格式的转化
s8* UmsVidProfilePrint(EmTpVideoQualityLevel emProfile);
s8* UmsVidFormatPrint(EmTpVideoFormat emFormat);
s8* UmsVidResPrint(EmTpVideoResolution emRes);
s8* UmsAudFormatPrint(EmTpAudioFormat emFormat);
s8* UmsPrintVendor( const EmTpVendorID& emUms );

#endif //_h_umsapi_h__