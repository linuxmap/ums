#ifndef _h_regserver_h__
#define _h_regserver_h__


#include "tpobject.h"
#include "tpsys.h"
#include "umconst.h"
#include "umsinnerstruct.h"
#include "kdvsys.h"

#define IP_CHECK_LIST_NUM 512
typedef struct tagTIPCheck
{
	BOOL32 m_bCheck;
	u32 m_awIP[IP_CHECK_LIST_NUM];//ÍøÂçÐò
	tagTIPCheck()
	{
		memset(m_awIP, 0, sizeof(m_awIP));
		m_bCheck = FALSE;
	}
	
	void ReadIpFromCfg()
	{
		s8 szData[128] = {0};
		for ( u16 wIndex = 0; wIndex < IP_CHECK_LIST_NUM; wIndex ++ )
		{
			s8 szTmp[16] = {0};
			sprintf(szTmp, "IP_%d", wIndex);
			memset( &szData, 0, sizeof(szData) );
#ifdef _LINUX_ //Òì³£²¶»ñ
			BOOL32 bRet = GetRegKeyString( "/usr/conf/ipcheck.ini",
#else
				BOOL32 bRet = GetRegKeyString( "ipcheck.ini",
#endif
				
				"IPLIST", 
				szTmp,
				"0.0.0.0",
				szData,
				sizeof(szData) );
			if( bRet )
			{
				Trim(szData);
				msgprintnotime("ip_%d: %s.\n", wIndex, szData);
				m_awIP[wIndex] = inet_addr(szData);
				m_bCheck = TRUE;
			}
		}
	}
	
	void showIP()
	{
		msgprintnotime("IPList m_bCheck:%d\n", m_bCheck);
		for ( u16 wIndex = 0; wIndex < IP_CHECK_LIST_NUM; wIndex ++ )
		{
			if ( m_awIP[wIndex] == 0 )
			{
				continue;
			}
			msgprintnotime("ip_%d: "TPIPFORMAT".\n", wIndex, u32ToIP(m_awIP[wIndex]));
		}
	}
	
	BOOL32 IsExistIp(u32 dwIP)
	{
		if ( !m_bCheck )
		{
			return TRUE;
		}
		for ( u16 wIndex = 0; wIndex < IP_CHECK_LIST_NUM; wIndex ++ )
		{
			if ( m_awIP[wIndex] == 0 )
			{
				continue;
			}
			if ( m_awIP[wIndex] == dwIP )
			{
				return TRUE;
			}
		}
		return FALSE;
	}
}TIPCheck;


class CTpRegServer :  public CTpObject
{
public:
    CTpRegServer(){}
	~CTpRegServer(){}
	
protected:

	BOOL32 ObjectInit(u32 wParam, u32 lParam);
};

typedef zTemplate<CTpRegServer, 1> CTpRegServerApp;



#endif // _h_regserver_h__
