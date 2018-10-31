
#include "handlelicense.h"
#include "readlicense.h"
#include "umsinnertype.h"
#include "umsapi.h"

#include "innereventumsserver.h"
#include "innereventumscall.h"

// 外部消息
#include "eventoutumscfg.h"


#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "nipwrapper.h"

#endif

#define SUCCESS_LICENSE	0
#define LICENSE_VERSION "KEY_LICENSE_VERSION"
#define LICENSE_TYPE "KEY_LICENSE_TYPE"
#define DEVICE_ID "KEY_DEVICE_ID"
#define ACCESS_NUM "KEY_ACCESS_NUM"
#define EX_DATE "KEY_EX_DATE"
#define key_project_name "project_name"
#define key_user_type "user_type"
#define key_contrace_code "contrace_code"
#define key_customer_name "customer_name"
#define key_seller "seller"
#define key_description "description"

#define len_limit 6
// inline void Trim(s8* pKey)  
// {  
//     s8 *pTmp = pKey;  
// 	
//     while (*pKey != '\0')   
//     {  
//         if (*pKey != ' ')  
//         {  
//             *pTmp++ = *pKey;  
//         }  
//         ++pKey;  
//     }  
//     *pTmp = '\0';  
// }

CUmsLicenseService::CUmsLicenseService(CTpObject* pcObjec)
:CTpHandler(pcObjec)
{
	m_bIsMaster = FALSE;
}


CUmsLicenseService::~CUmsLicenseService()
{
	
}

BOOL32 CUmsLicenseService::Handler( CTpMsg *const ptMsg )
{
	u16 wEvent = ptMsg->GetEvent();
	u8* pData = ptMsg->GetBody();
	u16 wDataSize = ptMsg->GetBodyLen();

	u16 wAppID = GETAPP(ptMsg->GetSrcIId());

	switch(wEvent)
	{
	case ev_MpcIsMaster_Ntf:
		{
			m_bIsMaster = TRUE;
		}
		break;
	case ev_UmsSetSysTime_Cmd:
		{
			TTPTime tTime;
			TP_SAFE_CAST(tTime, ptMsg->GetBody() + sizeof(TLogUser));
			TTPTime tLicenseTime = GetLicenseTime();

			msgprint("ums time %d-%d-%d %d:%d:%d, license time %d-%d-%d %d:%d:%d\n", tTime.m_wYear, tTime.m_byMonth, tTime.m_byMDay
				, tTime.m_byHour, tTime.m_byMinute, tTime.m_bySecond, tLicenseTime.m_wYear, tLicenseTime.m_byMonth
				, tLicenseTime.m_byMDay, tLicenseTime.m_byHour, tLicenseTime.m_byMinute, tLicenseTime.m_bySecond);

			u32 dwAccessNum = 0;
			CTpMsg cMsg;
			cMsg.SetEvent( evtp_UmsAccessNum_Notify );
			if (tLicenseTime < tTime)
			{
				m_bTimeIsValid = FALSE;
			}
			else
			{	
				m_bTimeIsValid = TRUE;
				dwAccessNum = GetAccessNum();
			}

			cMsg.SetBody(&dwAccessNum, sizeof(dwAccessNum));
			cMsg.Post( MAKEIID(AID_UMSCONFMGR,CInstance::DAEMON), 0, UMS_SERVICE_APP_INST );
		}
		break;
	case ev_umsGetlicenseInfo_Req:
		{
			ReadLicense();
		}
		break;
	default:
		break;
	}

	return TRUE;
}


BOOL32 CUmsLicenseService::Create()
{
	ReadLicense();
	return TRUE;
}


BOOL32 CUmsLicenseService::ProccessLicenseOutputReq(s8* szPathName, u16 wPathLen)
{
#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)

	strncpy(szPathName, "/ramdisk/license.ini", wPathLen - 1);
#else
	strncpy(szPathName, "/usr/license.ini", wPathLen - 1);
#endif
	FILE * pFile = fopen( szPathName, "wb" );
	if ( NULL == pFile )
	{
		msgprint("[ProccessLicenseOutputReq][Setup]:Open File %s Fail\n",szPathName );
		return FALSE;
	}
	
	const u16 wLen = LICENSE_MSG_LEN * 2;
	s8 szBuf[LICENSE_MSG_LEN * 2 + 1];

	snprintf(szBuf, wLen, "%s = %s;\n", LICENSE_VERSION, m_tInfo.abyLicenseVer);
	fwrite( szBuf, 1, strlen(szBuf), pFile );

	snprintf(szBuf, wLen, "%s = %s;\n", LICENSE_TYPE, m_tInfo.abyLicenseType);
	fwrite( szBuf, 1, strlen(szBuf), pFile );

	snprintf(szBuf, wLen, "%s = %02X:%02X:%02X:%02X:%02X:%02X;\n", DEVICE_ID, m_tInfo.abyDeviceMac[0]
		, m_tInfo.abyDeviceMac[1], m_tInfo.abyDeviceMac[2], m_tInfo.abyDeviceMac[3], m_tInfo.abyDeviceMac[4], m_tInfo.abyDeviceMac[5]);
	fwrite( szBuf, 1, strlen(szBuf), pFile );

	snprintf(szBuf, wLen, "%s = %d;\n", ACCESS_NUM, m_tInfo.wAccessNum);
	fwrite( szBuf, 1, strlen(szBuf), pFile );

	snprintf(szBuf, wLen, "%s = %d-%d-%d;\n", EX_DATE, m_tInfo.tTime.m_wYear, m_tInfo.tTime.m_byMonth, m_tInfo.tTime.m_byMDay);
	fwrite( szBuf, 1, strlen(szBuf), pFile );

	fclose( pFile );
	return TRUE;

#endif

	return FALSE;
}


void CUmsLicenseService::ShowLicense()
{
	msgprint("%s = %s\n", LICENSE_VERSION, m_tInfo.abyLicenseVer);
	msgprint("%s = %s\n", LICENSE_TYPE, m_tInfo.abyLicenseType);

	msgprint("%s = %02X:%02X:%02X:%02X:%02X:%02X\n", DEVICE_ID
		, m_tInfo.abyDeviceMac[0], m_tInfo.abyDeviceMac[1], m_tInfo.abyDeviceMac[2]
		, m_tInfo.abyDeviceMac[3], m_tInfo.abyDeviceMac[4], m_tInfo.abyDeviceMac[5]);

	msgprint("%s = %d\n", ACCESS_NUM, m_tInfo.wAccessNum);
	msgprint("%s = %d-%d-%d\n", EX_DATE, m_tInfo.tTime.m_wYear, m_tInfo.tTime.m_byMonth, m_tInfo.tTime.m_byMDay);

}

void CUmsLicenseService::ReadLicense()
{
	printf("[CUmsLicenseService::ReadLicense] BEGIN!\n");
	OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] BEGIN!\n");
#ifdef _LINUX_
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	m_tInfo.wAccessNum = 0;
	u16 wRet = 0;
	if(SUCCESS_LICENSE != ReadLicenseFile( (s8*)(LPCSTR)"/usr/conf/kedalicense.key" )) 
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Open kedalicense.key failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Open kedalicense.key failed!\n");
		return;
	}

	s32 wNum = GetKeyValueNum();
	printf("[CUmsLicenseService::ReadLicense] Open key num:%d.\n", wNum);
	OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Open key num:%d.\n", wNum);
	
	TKeyValue* ptValue = new TKeyValue[wNum];
	if (NULL != ptValue)
	{
		EnumKeyList(ptValue, wNum);
		
		for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
		{
			printf("  key:%s = %s.\n", ptValue[wIndex].achKey, ptValue[wIndex].achValue);
			OspPrintf(1, 0, "  key:%s = %s.\n", ptValue[wIndex].achKey, ptValue[wIndex].achValue);
		}
		
		delete[] ptValue;
		ptValue = NULL;
	}

	TKeyValue tValue;
	s32 wValueLen;
//////////////////////////////////////////////////////////////////////////
//mac校验 任何一个网口校验正确就可以
	wValueLen = sizeof(tValue.achValue);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, DEVICE_ID);	
	if( SUCCESS_LICENSE != GetValue(tValue.achKey, tValue.achValue, wValueLen) )
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_DEVICE_ID failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_DEVICE_ID failed!\n");
		return ;
	}
	Trim(tValue.achValue);

	printf("[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_DEVICE_ID is %s.\n", tValue.achValue);
	OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_DEVICE_ID is %s.\n", tValue.achValue);

	TBrdEthParam tEtherPara;
	memset( tEtherPara.byMacAdrs, 0, sizeof(tEtherPara.byMacAdrs) );
	TBrdEthParam tEtherPara0;
	memset( tEtherPara0.byMacAdrs, 0, sizeof(tEtherPara0.byMacAdrs) );

	STATUS sRet = BrdGetEthParam( DEFAULT_NETMAX_INDEX1, &tEtherPara );
	STATUS sRet0 = BrdGetEthParam( DEFAULT_NETMAX_INDEX0, &tEtherPara0 );

	if ( sRet == ERROR && sRet0 == ERROR )
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Get Eth all failed\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Get Eth all failed\n");
		return;
	}

	TBrdEthParam* ptParam = NULL;
	if ( sRet != ERROR )
	{
		snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, "%02X:%02X:%02X:%02X:%02X:%02X"
			, tEtherPara.byMacAdrs[0], tEtherPara.byMacAdrs[1], tEtherPara.byMacAdrs[2]
			, tEtherPara.byMacAdrs[3], tEtherPara.byMacAdrs[4], tEtherPara.byMacAdrs[5]);

		StrUpper(tValue.achValue);
		StrUpper(tValue.achKey);
		printf("[CUmsLicenseService::ReadLicense] Get Eth1 KEY_DEVICE_ID is %s.\n", tValue.achKey);
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Get Eth1 KEY_DEVICE_ID is %s.\n", tValue.achKey);
		if(strcmp(tValue.achValue, tValue.achKey) == 0)
		{
			ptParam = &tEtherPara;
		}
	}

	if ( sRet0 != ERROR )
	{
		snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, "%02X:%02X:%02X:%02X:%02X:%02X"
			, tEtherPara0.byMacAdrs[0], tEtherPara0.byMacAdrs[1], tEtherPara0.byMacAdrs[2]
			, tEtherPara0.byMacAdrs[3], tEtherPara0.byMacAdrs[4], tEtherPara0.byMacAdrs[5]);

		StrUpper(tValue.achValue);
		StrUpper(tValue.achKey);
		printf("[CUmsLicenseService::ReadLicense] Get Eth0 KEY_DEVICE_ID is %s.\n", tValue.achKey);
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Get Eth0 KEY_DEVICE_ID is %s.\n", tValue.achKey);
		if(strcmp(tValue.achValue, tValue.achKey) == 0)
		{
			ptParam = &tEtherPara0;
		}
	}

	if (ptParam == NULL)
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Check KEY_DEVICE_ID failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Check KEY_DEVICE_ID failed!\n");
		return;
	}
	memcpy(m_tInfo.abyDeviceMac, ptParam->byMacAdrs, sizeof(m_tInfo.abyDeviceMac));
//////////////////////////////////////////////////////////////////////////
//授权数量
	wValueLen = sizeof(tValue.achValue);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, ACCESS_NUM);	
	if( SUCCESS_LICENSE != GetValue(tValue.achKey, tValue.achValue, wValueLen) )
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_ACCESS_NUM failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_ACCESS_NUM failed!\n");
		return;
	}
	Trim(tValue.achValue);
	
	printf("[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_ACCESS_NUM is %s.\n", tValue.achValue);
	OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_ACCESS_NUM is %s.\n", tValue.achValue);

	m_tInfo.wAccessNum = atoi(tValue.achValue);
	if (m_tInfo.wAccessNum < 1 || m_tInfo.wAccessNum > 192)
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Check KEY_ACCESS_NUM failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Check KEY_ACCESS_NUM failed!\n");
		m_tInfo.wAccessNum = 0;
		return;
	}

	wValueLen = sizeof(tValue.achValue);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, EX_DATE);	
	if( SUCCESS_LICENSE == GetValue(tValue.achKey, tValue.achValue, wValueLen) )
	{//日期格式为：2013-06-18 ，严格匹配

		Trim(tValue.achValue);
		
		printf("[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_EX_DATE is %s.\n", tValue.achValue);
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_EX_DATE is %s.\n", tValue.achValue);

		memcpy(tValue.achKey, tValue.achValue, sizeof(tValue.achKey));
		tValue.achKey[4] = '\0';
		tValue.achKey[7] = '\0';

		m_tInfo.tTime.m_wYear = atoi(tValue.achKey);
		m_tInfo.tTime.m_byMonth = atoi(tValue.achKey + 5);
		m_tInfo.tTime.m_byMDay = atoi(tValue.achKey + 8);

		if (m_tInfo.tTime.m_byMonth > 12 || m_tInfo.tTime.m_byMDay > 31)
		{
			printf("[CUmsLicenseService::ReadLicense] FAILED! Check KEY_EX_DATE failed!\n");
			OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Check KEY_EX_DATE failed!\n");
			return;
		}
	}
	else
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_EX_DATE failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_EX_DATE failed!\n");
		return ;
	}
 #else	
   u8 abybuf[len_limit] = {0};
  // memset( tEtherPara.byMacAdrs, 0, sizeof(tEtherPara.byMacAdrs) );
   m_tInfo.wAccessNum = 0;
   u16 wRet = 0;
   if(SUCCESS_LICENSE != ReadLicenseFile( (s8*)(LPCSTR)"/usr/kedalicense.key" )) 
   {
	  printf("[CUmsLicenseService::ReadLicense] FAILED! Open kedalicense.key failed!\n");
	  OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Open kedalicense.key failed!\n");
	  return;
   }

   s32 wNum = GetKeyValueNum();
   printf("[CUmsLicenseService::ReadLicense] Open key num:%d.\n", wNum);
   OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Open key num:%d.\n", wNum);

   TKeyValue* ptValue = new TKeyValue[wNum];
   if (NULL != ptValue)
   {
	   EnumKeyList(ptValue, wNum);

	  for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	  {
		 printf("  key:%s = %s.\n", ptValue[wIndex].achKey, ptValue[wIndex].achValue);
		 OspPrintf(1, 0, "  key:%s = %s.\n", ptValue[wIndex].achKey, ptValue[wIndex].achValue);
	  }

	  delete[] ptValue;
	  ptValue = NULL;
   }

   TKeyValue tValue;
   s32 wValueLen;
   //////////////////////////////////////////////////////////////////////////
   //mac校验 任何一个网口校验正确就可以
   wValueLen = sizeof(tValue.achValue);
   snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, DEVICE_ID);	
   if( SUCCESS_LICENSE != GetValue(tValue.achKey, tValue.achValue, wValueLen) )
   {
	   printf("[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_DEVICE_ID failed!\n");
	   OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_DEVICE_ID failed!\n");
	   return ;
   }
   Trim(tValue.achValue);

   printf("[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_DEVICE_ID is %s.\n", tValue.achValue);
   OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_DEVICE_ID is %s.\n", tValue.achValue);
   CTpTypeAdpt::GetLocalMacAddr(0,abybuf);
   snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, "%02X:%02X:%02X:%02X:%02X:%02X", abybuf[0], abybuf[1], abybuf[2], abybuf[3], abybuf[4], abybuf[5]);
   
   StrUpper(tValue.achValue);
   StrUpper(tValue.achKey);
   printf("[CUmsLicenseService::ReadLicense] Get Eth0 KEY_DEVICE_ID is %s.\n", tValue.achKey);
   OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Get Eth0 KEY_DEVICE_ID is %s.\n", tValue.achKey);
   if(strcmp(tValue.achValue, tValue.achKey) == 0)
   {
	   printf("[CUmsLicenseService::ReadLicense] Get Key success.\n");
	   OspPrintf(1,0,"[CUmsLicenseService::ReadLicense] Get Key success.\n");
   }
   else
   {
	   CTpTypeAdpt::GetLocalMacAddr(1,abybuf);
	   snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, "%02X:%02X:%02X:%02X:%02X:%02X", abybuf[0], abybuf[1], abybuf[2], abybuf[3], abybuf[4], abybuf[5]);

	   StrUpper(tValue.achValue);
	   StrUpper(tValue.achKey);
	   printf("[CUmsLicenseService::ReadLicense] Get Eth1 KEY_DEVICE_ID is %s.\n", tValue.achKey);
	   OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Get Eth1 KEY_DEVICE_ID is %s.\n", tValue.achKey);
	   if(strcmp(tValue.achValue, tValue.achKey) == 0)
	   {
		   printf("[CUmsLicenseService::ReadLicense] Get Key success.\n");
		   OspPrintf(1,0,"[CUmsLicenseService::ReadLicense] Get Key success.\n");
	   }
	   else
	   {
		   printf("[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_DEVICE_ID failed\n");
		   OspPrintf(1,0,"[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_DEVICE_ID failed.\n");
		   return;

	   }

   }

	memcpy(m_tInfo.abyDeviceMac, abybuf, sizeof(m_tInfo.abyDeviceMac));
	//////////////////////////////////////////////////////////////////////////
	//授权数量
	wValueLen = sizeof(tValue.achValue);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, ACCESS_NUM);	
	if( SUCCESS_LICENSE != GetValue(tValue.achKey, tValue.achValue, wValueLen) )
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_ACCESS_NUM failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_ACCESS_NUM failed!\n");
		return;
	}
	Trim(tValue.achValue);

	printf("[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_ACCESS_NUM is %s.\n", tValue.achValue);
	OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_ACCESS_NUM is %s.\n", tValue.achValue);

	m_tInfo.wAccessNum = atoi(tValue.achValue);
	if (m_tInfo.wAccessNum < 1 || m_tInfo.wAccessNum > 192)
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Check KEY_ACCESS_NUM failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Check KEY_ACCESS_NUM failed!\n");
		m_tInfo.wAccessNum = 0;
		return;
	}

	wValueLen = sizeof(tValue.achValue);
	snprintf(tValue.achKey, sizeof(tValue.achKey) - 1, EX_DATE);	
	if( SUCCESS_LICENSE == GetValue(tValue.achKey, tValue.achValue, wValueLen) )
	{//日期格式为：2013-06-18 ，严格匹配

		Trim(tValue.achValue);

		printf("[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_EX_DATE is %s.\n", tValue.achValue);
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] Read kedalicense.key KEY_EX_DATE is %s.\n", tValue.achValue);

		memcpy(tValue.achKey, tValue.achValue, sizeof(tValue.achKey));
		tValue.achKey[4] = '\0';
		tValue.achKey[7] = '\0';

		m_tInfo.tTime.m_wYear = atoi(tValue.achKey);
		m_tInfo.tTime.m_byMonth = atoi(tValue.achKey + 5);
		m_tInfo.tTime.m_byMDay = atoi(tValue.achKey + 8);

		if (m_tInfo.tTime.m_byMonth > 12 || m_tInfo.tTime.m_byMDay > 31)
		{
			printf("[CUmsLicenseService::ReadLicense] FAILED! Check KEY_EX_DATE failed!\n");
			OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Check KEY_EX_DATE failed!\n");
			return;
		}
	}
	else
	{
		printf("[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_EX_DATE failed!\n");
		OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] FAILED! Read kedalicense.key KEY_EX_DATE failed!\n");
		return ;
	}
   

#endif 
#endif
#ifdef WIN32
	// 非ppc82和ppc85，暂定默认给最大授权
	m_tInfo.wAccessNum = 192;
	m_tInfo.tTime.m_wYear = 2050;
	m_tInfo.tTime.m_byMonth = 1;
	m_tInfo.tTime.m_byMDay = 1;
#endif //_PPC_82XX_ _PPC_85XX_

	LicenseTimeCheck(m_tInfo.tTime);
	
	printf("[CUmsLicenseService::ReadLicense] END!\n");
	OspPrintf(1, 0, "[CUmsLicenseService::ReadLicense] END!\n");

	// 主动向umscall更新一次授权数
	u32 dwAccessNum = m_tInfo.wAccessNum;
	CTpMsg cMsg;
	cMsg.SetEvent( evtp_UmsAccessNum_Notify );
	cMsg.SetBody(&dwAccessNum, sizeof(dwAccessNum));
	cMsg.Post( MAKEIID(AID_UMSCONFMGR,CInstance::DAEMON), 0, UMS_SERVICE_APP_INST );

	return;
}

void CUmsLicenseService::LicenseTimeCheck(TTPTime tLicense)
{
	TTPTime tSysTime;
	TPGetSysTime(tSysTime);
	printf("[CUmsLicenseService::LicenseTimeCheck] ums time %d-%d-%d %d:%d:%d, license time %d-%d-%d %d:%d:%d.\n", tSysTime.m_wYear, tSysTime.m_byMonth
		, tSysTime.m_byMDay, tSysTime.m_byHour, tSysTime.m_byMinute, tSysTime.m_bySecond, tLicense.m_wYear, tLicense.m_byMonth
		, tLicense.m_byMDay, tLicense.m_byHour, tLicense.m_byMinute, tLicense.m_bySecond);

	OspPrintf(1, 0, "[CUmsLicenseService::LicenseTimeCheck] ums time %d-%d-%d %d:%d:%d, license time %d-%d-%d %d:%d:%d.\n", tSysTime.m_wYear, tSysTime.m_byMonth
		, tSysTime.m_byMDay, tSysTime.m_byHour, tSysTime.m_byMinute, tSysTime.m_bySecond, tLicense.m_wYear, tLicense.m_byMonth
		, tLicense.m_byMDay, tLicense.m_byHour, tLicense.m_byMinute, tLicense.m_bySecond);

	if (tLicense < tSysTime)
	{
		m_bTimeIsValid = FALSE;
	}
	else
	{
		m_bTimeIsValid = TRUE;
	}
	printf("[CUmsLicenseService::LicenseTimeCheck] m_bTimeIsValid is %d.\n", m_bTimeIsValid);
	OspPrintf(1, 0, "[CUmsLicenseService::LicenseTimeCheck] m_bTimeIsValid is %d.\n", m_bTimeIsValid);
}
