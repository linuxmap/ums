#include "umsconfig.h"
#include "kdvsys.h"
#include "tpsys.h"
#include "tplog.h"
#include "jdconfig.h"

 
 static const u8 CONF_FILE_NAME_LEN = 255;
 static s8  g_Config[CONF_FILE_NAME_LEN] = {0};

 static const s8 umsSec[] = "config";
//服务域moid
 static const s8 mtKeyServerDomainMoid[] ="service_domain_moid";
//平台域moid
 static const s8 mtKeyPlatFormMoid[] ="platform_domain_moid";

 static const s8 mtKeyMachineRoomMoid[] ="machine_room_moid";

 static const s8 mtKeyTpsMoid[] ="tps_moid";

 static const s8	umsSecAddrParam[] = "config";

 static const s8 umsKeyRmqeIP[] = "rmq_ip";
 static const s8 umsKeyRmqPort[] = "rmq_port";
 static const s8 umsKeyZKIP[] = "zk_ip";
 static const s8 umsKeyZKPort[] = "zk_port";
 static const s8 umsKeyRedisIP[] = "redis_ip";
 static const s8 umsKeyRedisPort[] = "redis_port";
 static const s8 umsKeySsoAddr[] = "sso_addr";
 static const s8 umsKeyMqUrl[] = "mqurl";
 static const s8 umsJDMqUrl[] = "amqp://dev:dev@127.0.0.1:6672";
#define GetIPStr(dwIp,achStr)\
 {\
	struct in_addr addr;\
	addr.s_addr = dwIp;\
	sprintf(achStr,IPFORMAT,u32ToIP(dwIp));\
 }
 

 CJDConfig* CJDConfig::m_pcInstance = NULL;
 void CJDConfig::ShowAll()
{
	s8 abyIp[20];
	msgprintnotime("\n\n[Config]\n");
	msgprintnotime("%s = %s\n",mtKeyServerDomainMoid,m_tJDInfo.m_abyServerMoid);
	msgprintnotime("%s = %s\n",mtKeyPlatFormMoid,m_tJDInfo.m_abyPlatformMoid);

	msgprintnotime("%s = %s\n",mtKeyMachineRoomMoid,m_tJDInfo.m_abyMachineMoid);
	msgprintnotime("%s = %s\n\n",mtKeyTpsMoid,m_tJDInfo.m_abyTpsMoid);

	GetIPStr(m_tJDInfo.m_dwRmqIP, abyIp);
	msgprintnotime("%s = %s\n",umsKeyRmqeIP,abyIp);
	msgprintnotime("%s = %d\n",umsKeyRmqPort,m_tJDInfo.m_dwRmqPort);

	GetIPStr(m_tJDInfo.m_dwZkIP, abyIp);
	msgprintnotime("%s = %s\n",umsKeyZKIP,abyIp);
	msgprintnotime("%s = %d\n",umsKeyZKPort,m_tJDInfo.m_dwZkPort);

	GetIPStr(m_tJDInfo.m_dwRedisIP, abyIp);
	msgprintnotime("%s = %s\n", umsKeyRedisIP, abyIp);
	msgprintnotime("%s = %d\n\n", umsKeyRedisPort, m_tJDInfo.m_dwRedisPort);

	msgprintnotime("%s = %s\n\n", umsKeySsoAddr, m_tJDInfo.m_abySsoAddr);
	msgprintnotime("%s = %s\n\n", umsKeyMqUrl, m_tJDInfo.m_abyMqUrl);

}
 
 BOOL32 CJDConfig::GetIPValue(FILE*pfFile,u32& dwVal,const s8* const szSection,const s8* const szKey )
 {
	 s8 achTemp[256] = {0};
	 BOOL bResult = GetRegKeyString2(pfFile,szSection,
		 szKey,"",achTemp,sizeof(achTemp));
	 if(!bResult) 
		 return FALSE;
	 Trim(achTemp);
	dwVal = inet_addr(achTemp);
	return TRUE;
 }

 BOOL32 CJDConfig::GetMoidValue(FILE*pfFile,s8* szMoidVal,const s8* const szSection,const s8* const szKey )
 {
	 s8 achTemp[256] = {0};
	 BOOL bResult = GetRegKeyString2(pfFile,szSection,
		 szKey,"",achTemp,sizeof(achTemp));
	 if(!bResult) 
		 return FALSE;
	 Trim(achTemp);
	 strncpy(szMoidVal,achTemp,TP_MAX_ALIAS_LEN);
	 return TRUE;
 }

BOOL32 CJDConfig::ReadFromConfigFile()
{
	s32 dwVal;
	FILE* pfFile = fopen(g_Config,"rb");
	if(NULL == pfFile)
	{
		return FALSE;
	}

	GetMoidValue(pfFile,m_tJDInfo.m_abyServerMoid,umsSec,mtKeyServerDomainMoid);
	GetMoidValue(pfFile,m_tJDInfo.m_abyPlatformMoid,umsSec,mtKeyPlatFormMoid);
	GetMoidValue(pfFile,m_tJDInfo.m_abyMachineMoid,umsSec,mtKeyMachineRoomMoid);
	GetMoidValue(pfFile,m_tJDInfo.m_abyTpsMoid,umsSec,mtKeyTpsMoid);

	GetIPValue(pfFile,m_tJDInfo.m_dwRmqIP,umsSecAddrParam,umsKeyRmqeIP);
	GetRegKeyInt(g_Config,umsSecAddrParam,umsKeyRmqPort, 5, &dwVal);
	m_tJDInfo.m_dwRmqPort = dwVal;
	GetIPValue(pfFile,m_tJDInfo.m_dwZkIP,umsSecAddrParam,umsKeyZKIP);

	GetRegKeyInt(g_Config,umsSecAddrParam,umsKeyZKPort, 5, &dwVal);
	m_tJDInfo.m_dwZkPort = dwVal;
	GetIPValue(pfFile,m_tJDInfo.m_dwRedisIP,umsSecAddrParam,umsKeyRedisIP);

	GetRegKeyInt(g_Config,umsSecAddrParam,umsKeyRedisPort, 5, &dwVal);
	m_tJDInfo.m_dwRedisPort = dwVal;
	GetMoidValue(pfFile,m_tJDInfo.m_abySsoAddr,umsSecAddrParam,umsKeySsoAddr);
	if (!GetMoidValue(pfFile,m_tJDInfo.m_abyMqUrl,umsSecAddrParam,umsKeyMqUrl))
	{
		memcpy(m_tJDInfo.m_abyMqUrl,umsJDMqUrl,sizeof(umsJDMqUrl));
	}
	return TRUE;
}
void CJDConfig::GetFromConfigFile(TJDInfo &tJDInfo)
{
    memcpy(tJDInfo.m_abyServerMoid,m_tJDInfo.m_abyServerMoid,TP_MAX_ALIAS_LEN);
	memcpy(tJDInfo.m_abyPlatformMoid,m_tJDInfo.m_abyPlatformMoid,TP_MAX_ALIAS_LEN);
	memcpy(tJDInfo.m_abyMachineMoid,m_tJDInfo.m_abyMachineMoid,TP_MAX_ALIAS_LEN);
	memcpy(tJDInfo.m_abyTpsMoid,m_tJDInfo.m_abyTpsMoid,TP_MAX_ALIAS_LEN);
	tJDInfo.m_dwRedisIP = m_tJDInfo.m_dwRedisIP;
	tJDInfo.m_dwRedisPort = m_tJDInfo.m_dwRedisPort;
	tJDInfo.m_dwRmqIP = m_tJDInfo.m_dwRmqIP;
	tJDInfo.m_dwRmqPort = m_tJDInfo.m_dwRmqPort;
	tJDInfo.m_dwZkIP = tJDInfo.m_dwZkIP;
	tJDInfo.m_dwZkPort = tJDInfo.m_dwZkPort;
	memcpy(tJDInfo.m_abySsoAddr,m_tJDInfo.m_abySsoAddr,TP_MAX_ALIAS_LEN);
	memcpy(tJDInfo.m_abyMqUrl,m_tJDInfo.m_abyMqUrl,TP_MAX_ALIAS_LEN);
}

CJDConfig* CJDConfig::GetInstance()
{
	if ( NULL == m_pcInstance )
	{
		m_pcInstance = new CJDConfig;
		if ( NULL == m_pcInstance )
		{
			msgprint( "[CConfig::GetInstance]m_pcInstance mem alloc failed!\n" );
			return NULL;
		}
	}
	if( !m_pcInstance->m_bIsInited )
	{
		strncpy(g_Config,UmsGetFileName(emUmsConfig),sizeof(s8)*CONF_FILE_NAME_LEN);
		m_pcInstance->m_bIsInited = m_pcInstance->ReadFromConfigFile();
	}

	return m_pcInstance;
};






