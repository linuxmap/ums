#include "umsconfig.h"
#include "string.h"
#include "cfgdata.h"
#include "syscfgcom.h"
#include "kdvsys.h"
#include "cfginstance.h"
#include "rwnewcfgfile.h"
#include <stdio.h>
#include "persistfile.h"
#include "displaydata.h"
#include "umsconfigex.h"
#include "jdconfig.h"

#define  VER_umscfg_msg UMS_VerID
#define MAX_LINE 50
#define MAX_COLUMN 256
API void cfgver()
{
	msgprint("umscfg ver: %s  compile time: %s:%s\n",
		VER_umscfg_msg, __DATE__,  __TIME__);
}


s8* UmsGetFileName(EmUmsFile type)
{
#ifdef WIN32
	switch(type)
	{
	case emUmsCfg:
		return "umscfg.ini";

	case emUmsCfgEx:
		return "umscfgex.ini";

	case emUmsExeFile:
		return "umsserver.exe";

	case emUmsExceptionFile:
		return "umsexception.txt";

	case emUmsUserMgrFile:
		return "usrinfo";

	case emUmsTpFile:
		return ".\\templatecfg\\templatecfg_";

	case emUmsTpFolder:
		return ".\\";

	case emUmsTpDownLoadFile:
		return ".\\templatecfg\\template_down.tar";

	case emUmsTpControlFile:
		return ".\\templatecfg\\control.ini";

	case emUmsAddrBookFile:
		return "kdvaddrbook.kdv";

	case emUmsLogCfgFile:
		return "umslog.ini";

	case emUmsTpDownControlFile:
		return ".\\templatecfg\\template_down";

	case emUmsTpDownTemplateFile:
		return ".\\templatecfg\\template_down";

	case emUmsserverLog4cplusCfg:
		return "umsserverlog4cplus.cfg";

	case emUmsConfig:
		return "config.ini";

	}	
#endif

#ifdef _LINUX_ 
#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
	switch(type)
	{
	case emUmsCfg:
		return "/usr/conf/umscfg.ini";

	case emUmsCfgEx:
		return "/usr/conf/umscfgex.ini";

	case emUmsExeFile:
		return "/usr/bin/umsserver";

	case emUmsExceptionFile:
		return "/usr/conf/umsexception.txt";

	case emUmsLog4cpExeFile:
		return "/usr/bin/umsserver_log4cplus";

	case emUmsLog4cpExceptionFile:
		return "/usr/conf/umslog4cpexception.txt";

	case emUmsUserMgrFile:
		return "/usr/conf/usrinfo";

	case emUmsTpFile:
		return "/usr/conf/templatecfg/templatecfg_";

	case emUmsTpFolder:
		return "/ramdisk/";

	case emUmsTpDownLoadFile:
		return "/ramdisk/template_down.tar";

	case emUmsTpControlFile:
		return "/usr/conf/templatecfg/control.ini";

	case emUmsAddrBookFile:
		return "/usr/conf/kdvaddrbook.kdv";

	case emUmsLogCfgFile:
		return "/usr/conf/umslog.ini";

	case emUmsTpDownTemplateFile:
		return "/ramdisk/template_down/templatecfg_";

	case emUmsTpDownControlFile:
		return "/ramdisk/template_down/control.ini";

	case emUmsserverLog4cplusCfg:
		return "/usr/conf/umsserverlog4cplus.cfg";

	case emUmsConfig:
		return "/usr/conf/config.ini";
	}	

#else

	switch(type)
	{
	case emUmsCfg:
		return "/tp/umscfg.ini";

	case emUmsCfgEx:
		return "/usr/umscfgex.ini";

	case emUmsExeFile:
		return "/tp/umsserver";

	case emUmsExceptionFile:
		return "/tp/umsexception.txt";

	case emUmsLog4cpExeFile:
		return "/tp/umsserver_log4cplus";

	case emUmsLog4cpExceptionFile:
		return "/tp/umslog4cpexception.txt";

	case emUmsUserMgrFile:
		return "/usr/usrinfo";

	case emUmsTpFile:
		return "/tp/templatecfg/templatecfg_";

	case emUmsTpFolder:
		return "/usr/";

	case emUmsTpDownLoadFile:
		return "/usr/template_down.tar";

	case emUmsTpControlFile:
		return "/tp/templatecfg/control.ini";

	case emUmsAddrBookFile:
		return "/usr/kdvaddrbook.kdv";

	case emUmsLogCfgFile:
		return "/usr/umslog.ini";

	case emUmsTpDownTemplateFile:
		return "/usr/template_down/templatecfg_";

	case emUmsTpDownControlFile:
		return "/ramdisk/template_down";

	case emUmsserverLog4cplusCfg:
		return "/tp/umsserverlog4cplus.cfg";

	case emUmsConfig:
		return "/usr/config.ini";

	}
#endif
#endif

	msgprint("UmsGetFileName Unknow Type:%d\n", type);
	return "UnKnow";
}


#ifdef _LINUX_
BOOL cnPathExist(const s8* path)
{
	s8  achCurPath[256] ={0};
	s8* pStr = getcwd(achCurPath,sizeof(achCurPath));
	if(NULL == pStr) return FALSE;
	BOOL bRet = (chdir(path) >= 0);
	chdir(achCurPath);
	return bRet;
}
#endif

BOOL UmsMakeDir(const s8* path )
{
	int nRet = 0;
	
#ifdef WIN32
	nRet = CreateDirectory( path, 0 );
	if(nRet != 1)          
		msgprint("%s created failled,error no. = %d\n", path, nRet);
	else
		msgprint("%s created success\n", path);
	return TRUE;
#endif
#ifdef _VXWORKS_
	nRet = mkdir( path  );
#endif
#ifdef _LINUX_
	if(cnPathExist(path)) return FALSE;
	
	nRet = mkdir(path,  S_IRUSR//�ļ������߾߿ɶ�ȡȨ��
		|S_IWUSR//�ļ������߾߿�д��Ȩ��
		    	 |S_IXUSR//�ļ������߾߿�ִ��Ȩ��
				 |S_IRGRP// �û���߿ɶ�ȡȨ��
				 |S_IWGRP//�û���߿�д��Ȩ��
				 |S_IXGRP//�û���߿�ִ��Ȩ��
				 |S_IROTH//�����û��߿ɶ�ȡȨ��
				 |S_IWOTH//�����û��߿�д��Ȩ��
				 |S_IXOTH);//���û��߿�ִ��Ȩ��
#endif
	if(nRet != 0)          
		msgprint("%s created failled,error no. = %d\n",path,nRet);
	else
		msgprint("%s created success\n",path);	
	return TRUE;
}


#define FILE_NAME_LEN 255

CCfgDataApp g_CfgDataApp;
extern CCfgDataManager g_cUmsCfgDataMan;
static SEMHANDLE      s_semAllConfig;
s8 g_szFileName[FILE_NAME_LEN+1] = {0};
extern TALLConfigData g_tALLConfigData;

SEMHANDLE   s_semUmsQuitCfg;

//umsConfig��ӡ����
static BOOL s_bShowConfigInfo = FALSE;

API void Showconfiginfo()
{
    s_bShowConfigInfo = !s_bShowConfigInfo;
	msgprint("[Showconfiginfo], �洢������ʾ :%s \n", (s_bShowConfigInfo)?"��":"�ر�");
	
}

BOOL g_bCfgModuleDisable = FALSE;

static inline void SaveAllCfgData()
{
	::OspPost(MAKEIID(AID_UMS_CFGDATA), EV_MTA_MTAC_UPDATE_CMD, &g_tALLConfigData, sizeof(g_tALLConfigData));	
}


static inline BOOL IsNewCfgFile(FILE* pfFile)
{
	s8 abyBuf[10]={0};
	BOOL bResult = FALSE;
	bResult = GetRegKeyString2(pfFile,umsSecSystem,
							   umsKeySysConfigFileVersion,
							   "",abyBuf,sizeof(abyBuf));
	
	if(!bResult) return FALSE;
	if(strlen(abyBuf) == 0) return FALSE;
	
	s32 dwVal = 0;
	sscanf(abyBuf,"%d",&dwVal);
	if(mtConfigFileVersion != dwVal) return FALSE;

	return TRUE;
}


static inline BOOL ReadNewCfgFile(FILE* pfFile)
{
	if(!IsNewCfgFile(pfFile)) return FALSE;
	LoadDataFromCfgFile(pfFile);	

	return TRUE;
}

static inline BOOL FileIsValid(FILE* pFile)
{
	fseek(pFile,0L,SEEK_END);
	u32  dwLen = ftell(pFile);
	return (dwLen > 0);
}



void ReadDataFromCfgFile(const s8* szFileName)
{
	msgprint("[ReadDataFromCfgFile], szFileName->%s \n", szFileName);

	FILE* pfFile = fopen(szFileName,"rb");
	//if file not exist , then create a new blank file and return
	if(NULL == pfFile)
	{
        if( s_bShowConfigInfo )
            msgprint("[MtConfig]open config file error %s\n",szFileName);
		pfFile = fopen(szFileName,"w");
		if(NULL != pfFile)	fclose(pfFile);
		return;
	}
    //if file invalid close the file and return
	if(!FileIsValid(pfFile))
	{
		fclose(pfFile);		
		return;
	}
	//if the file is new ,readed and return
	if(ReadNewCfgFile(pfFile))return;
    //read the file as old config file
}


static void MtbClientReadDataFromCfgFile(const s8* szFileName)
{
	FILE* pfFile = fopen(szFileName,"rb");
	// if file not exist , then create a new blank file and save 
    // it as default config file  
	if(NULL == pfFile)
	{
        if( s_bShowConfigInfo )
        {
            msgprint("[MtConfig]open config file error %s\n",szFileName);
        }
        //����Ĭ��������Ϣ�������ļ���
        SaveDataToCfgFile(szFileName, g_tALLConfigData);
        return;
	}
    //if file invalid close the file and return
	if(!FileIsValid(pfFile))
	{
        // ����Ĭ��������Ϣ�������ļ���
        SaveDataToCfgFile(szFileName, g_tALLConfigData);
		return;
	}
	//if the file is new ,readed and return
	if(ReadNewCfgFile(pfFile)) return;
    
    // �رմ򿪵������ļ�
    fclose(pfFile);
}


BOOL InitUmsCfg(void)
{
    // ���������ź���--huzilong 2011/09/20
    if( !OspSemCCreate( &s_semUmsQuitCfg, 0, 1 ) )
    {
        msgprint("[umsConfig] create s_semQuitCfg failed!\n" );
		return FALSE;
    }

	//������д�ź���
	if( !OspSemBCreate(&s_semAllConfig) )
	{
        msgprint("[umsConfig] create g_semAllConfig failed!\n" );
		return FALSE;
	}

	CUmsConfigEx::GetInstance();
	CJDConfig::GetInstance();

	//��ʼ����������
	InitData();
	//�����ļ�����
	strncpy(g_szFileName,UmsGetFileName(emUmsCfg),sizeof(g_szFileName)-1);
	//���������ļ�
	g_cUmsCfgDataMan.InitConfigure(g_szFileName);
	//���ļ�ֵ	
	ReadDataFromCfgFile(g_szFileName);
    //�����ļ��־û�����	    
	g_CfgDataApp.CreateApp("CUmsCgfDataApp",AID_UMS_CFGDATA,AID_UMS_PROP);
	::OspPost(MAKEIID(AID_UMS_CFGDATA),EV_SYSCFG_INIT_CMD,g_szFileName,sizeof(g_szFileName));

	//�������ʼ��һ��
	SaveAllCfgData();

	return TRUE;
}


void QuitUmsCfg(void)
{
	//�˴�ǿ�ƶ��ź�������OspSemTake����
	OspSemGive( s_semUmsQuitCfg );
	OspSemTake( s_semUmsQuitCfg );

	ImmediatelySave();

    OspSemTake( s_semUmsQuitCfg );
    OspSemGive( s_semUmsQuitCfg );
    OspSemDelete( s_semUmsQuitCfg );

	OspSemDelete(s_semAllConfig);
	g_bCfgModuleDisable = TRUE;
	printf("the config will be eixt...\n");
}

void ImmediatelySave(void)
{
	if(!g_bCfgModuleDisable)
	{
		::OspSend(MAKEIID(AID_UMS_CFGDATA),EV_MTA_MTAC_SAVE_CMD);
	}

	return ;
}

template<class T>
inline static BOOL GetValue(T& dest,const T& val,u32 dwSize = sizeof(T))
{
	if ( g_bCfgModuleDisable )
	{
		printf("umsConfig mudule has been disabled, can't get configuraton! \n" );
		return FALSE;
	}

	if( !OspSemTakeByTime( s_semAllConfig, WAIT_SEM_TIMEOUT ))
	{
		msgprint("[umsConfig]OspSecTakeByTime "
			"excute failled g_semAllConfig value is %d\n",s_semAllConfig);
        return FALSE;
 	} 
	memcpy(&dest,&val,dwSize);
	OspSemGive( s_semAllConfig );
	return TRUE;
}
/*====================================================================
  �� �� ���� SetValue
  ��    �ܣ� �����ڴ�ֵ
  �㷨ʵ�֣�  �� 
  ȫ�ֱ����� g_semAllConfig
  ��    ���� const T&val ����Դ��ַ
             T& dest  ����Ŀ�ĵ�ַ
             u32 dwSize = sizeof(T) Ĭ�Ͽ�����С
  �� �� ֵ�� BOOL ������ȡ�����ź�����ʱ����FALSE;
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2005/8/15      1.0		    �� ��                   ����
======================================================================*/
template<class T>
inline static BOOL SetValue(const T&val,T& dest,u32 dwSize = sizeof(T))
{
	if ( g_bCfgModuleDisable )
	{
		msgprint( "umsConfig mudule has been disabled, can't save configuraton! \n" );
		return FALSE;
	}

	if( !OspSemTakeByTime( s_semAllConfig, WAIT_SEM_TIMEOUT ))
	{
		msgprint("[umsConfig]OspSecTakeByTime "
			"excute failled g_semAllConfig value is %d\n",s_semAllConfig);
        return FALSE ;
 	} 

	memcpy(&dest,&val,dwSize);

	SaveAllCfgData();
	
	OspSemGive( s_semAllConfig );
	return TRUE;
}



BOOL umsGetLocalUmsIP( u32& dwIp )
{
	return GetValue( dwIp, g_tALLConfigData.m_tLocalCnsInfo.m_tEth.dwIP );
}


BOOL umsGetLocalEthInfo( TTPEthnetInfo& tEth )
{
	return GetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tEth );
}
BOOL umsGetLocalVirEthInfo( TTPEthnetInfo& tEth )
{
	return GetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth );
}
BOOL umsGetLocalEth1Info( TTPEthnetInfo& tEth )
{
	return GetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tEth1 );
}
BOOL umsGetLocalVirEth1Info( TTPEthnetInfo& tEth )
{
	return GetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth1 );
}

BOOL32 IsLocalUmsIP(u32& dwIp)
{
	TTPEthnetInfo tEth,tVirEth,tEth1,tVirEth1;
	umsGetLocalEthInfo(tEth);
	umsGetLocalVirEthInfo(tVirEth);
	umsGetLocalEth1Info(tEth1);
	umsGetLocalVirEth1Info(tVirEth1);
	
	if (dwIp == tEth.dwIP || dwIp == tVirEth.dwIP || dwIp == tEth1.dwIP || dwIp == tVirEth1.dwIP)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL32 GetUmsOldip(u32& dwIp)
{
	 return GetValue( dwIp, g_tALLConfigData.m_tLocalCnsInfo.m_dwUmsoldIP);
}

BOOL32 SetUmsOldIP()
{
	TTPEthnetInfo tEth,tEth1;
	BOOL bRet = FALSE;
	u32_ip dwIP = 0;
	umsGetLocalEthInfo(tEth);
	umsGetLocalEth1Info(tEth1);
	if (tEth.dwIP)
	{
		dwIP = tEth.dwIP;
	}
	else 
	{
		dwIP = tEth1.dwIP;
	}
	bRet = SetValue(dwIP,g_tALLConfigData.m_tLocalCnsInfo.m_dwUmsoldIP);
	return bRet;
}

BOOL umsSetLocalEthInfo( const TTPEthnetInfo& tEth ,EmEthInfoType& emEthType)
{
	BOOL bRet = FALSE;
	switch(emEthType)
	{
	case em_eth0_type:
		{
			bRet = SetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tEth );
			break;
		}
	case em_eth0_virtual_type:
		{
			bRet = SetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth );
			break;
		}
	case em_eth1_type:
		{
			bRet = SetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tEth1 );
			break;
		}
	case em_eth1_virtual_type:
		{
			bRet = SetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tVirEth1 );
			break;
		}
	default:
		   break;

	}
//	BOOL bRet = SetValue( tEth, g_tALLConfigData.m_tLocalCnsInfo.m_tEth );
	
	return bRet;
}


//��ȡ��CMS������������㣬
BOOL umsGetUmsListenPortCfg(u16& Port)
{
	return GetValue( Port, g_tALLConfigData.m_tLocalCnsInfo.m_wListionPortForUi );
}

//����������ʼ�˿ں�
BOOL umsGetStartUdpPortCfg(u16& Port)
{
	return GetValue( Port, g_tALLConfigData.m_tLocalCnsInfo.m_wBeginUdpTransPort );
}

//����һ������������
BOOL umsGetMaxOnceCallCfg(u16& Num)
{
	return GetValue( Num, g_tALLConfigData.m_tLocalCnsInfo.m_wNumMaxOnecCall );
}

//����ǽ������Ϣ
BOOL umsGetHduCfg(u16 wIndex, THduCfgInfo& tInfo)
{
	if (wIndex < HDU_MAX_NUM)
	{
		return GetValue( tInfo, g_tALLConfigData.m_atHduCfg[wIndex] );
	}
	return FALSE;	
}
BOOL umsSetHduCfg(u16 wIndex, const THduCfgInfo& tInfo)
{
	if (wIndex < HDU_MAX_NUM)
	{
		return SetValue( tInfo, g_tALLConfigData.m_atHduCfg[wIndex] );
	}
	return FALSE;
}

//����ǽ���
BOOL umsGetHduStyle(THduStyleCfgInfo& tHduStyle)
{
	return GetValue(tHduStyle, g_tALLConfigData.m_tHduStyleCfg);
}

BOOL umsSetHduStyle(const THduStyleCfgInfo& tHduStyle)
{
	return SetValue(tHduStyle, g_tALLConfigData.m_tHduStyleCfg);
}
/*��ȡ������Ч����*/
BOOL32 umsGetBrdInvalidNum(u8& byValidBrdNum)
{
	return GetValue(byValidBrdNum, g_tALLConfigData.m_byBrdValidNum);
}

/*�趨������Ч����*/
BOOL32 umsSetBrdInvalidNum(const u8& byValidBrdNum)
{
	return SetValue(byValidBrdNum, g_tALLConfigData.m_byBrdValidNum);
}

/*��ȡָ���������Ϣ*/
BOOL32 umsGetBoardInfo(TTPBrdInfo& tBrdCfg, u16 wBrdIndex)
{
	if (wBrdIndex < TP_BOARD_MAX_NUM)
	{
		return GetValue(tBrdCfg, g_tALLConfigData.m_atBrdCfg[wBrdIndex]);
	}
	
	return FALSE;
}

/*����ָ���������Ϣ*/
BOOL32 umsSetBoardInfo(const TTPBrdInfo& tBrdCfg, u16 wBrdIndex)
{
	if (wBrdIndex < TP_BOARD_MAX_NUM)
	{
		return SetValue(tBrdCfg, g_tALLConfigData.m_atBrdCfg[wBrdIndex]);
	}
	
	return FALSE;
}

/*====================================================================
  �� �� ���� cnGetSipRegCfg
  ��    �ܣ� ��ȡע��SIP����
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� TTPSipRegistrarCfg& tSipRegCfg
  �� �� ֵ�� BOOL  
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
 2011/5/09      1.0		    Ф��Ȼ                  ����
======================================================================*/
BOOL umsGetSipRegCfg(TTPSipRegistrarCfg& tSipRegCfg)
{
	return GetValue(tSipRegCfg, g_tALLConfigData.m_tTPSipRegistrarCfg);
}

BOOL umsSetSipRegCfg(const TTPSipRegistrarCfg& tSipRegCfg)
{
	return SetValue(tSipRegCfg, g_tALLConfigData.m_tTPSipRegistrarCfg);
}

BOOL umsGetGKRegCfg(TTPGKCfg& tGKRegCfg)
{
	return GetValue(tGKRegCfg, g_tALLConfigData.m_tGKRegCfg);
}

BOOL umsSetGKRegCfg(const TTPGKCfg& tGKRegCfg)
{
	return SetValue(tGKRegCfg, g_tALLConfigData.m_tGKRegCfg);
}

BOOL umsSetUmsStackCfg(const TUmsStackCallCfg& tStackCfg)
{
	return SetValue(tStackCfg, g_tALLConfigData.m_tSipStackCallCfg);
}

BOOL umsGetUmsStackCfg(TUmsStackCallCfg& tStackCfg)
{
	return GetValue(tStackCfg, g_tALLConfigData.m_tSipStackCallCfg);
}

BOOL32 umsSetQTEncryptInfo( const TTPQTEncryptInfo &tTPQTEncryptInfo )
{
	return SetValue( tTPQTEncryptInfo, g_tALLConfigData.m_tTPQTEncryptInfo );
}

BOOL32 umsGetQTEncryptInfo( TTPQTEncryptInfo &tTPQTEncryptInfo )
{
	return GetValue( tTPQTEncryptInfo, g_tALLConfigData.m_tTPQTEncryptInfo );
}

BOOL32 umsSetPwdCycleInfo( const TPwdCycleInfo &tTPPwdCycleInfo )
{
	return SetValue( tTPPwdCycleInfo, g_tALLConfigData.m_tPwdCycleInfo );
}

BOOL32 umsGetPwdCycleInfo( TPwdCycleInfo &tTPQTEncryptInfo )
{
	return GetValue( tTPQTEncryptInfo, g_tALLConfigData.m_tPwdCycleInfo );
}

BOOL32 umsSetNtpdInfo( const TNtpdInfo &tNtpdInfo )
{
	return SetValue( tNtpdInfo, g_tALLConfigData.m_tNtpdInfo );
}

BOOL32 umsGetNtpdInfo( TNtpdInfo &tNtpdInfo )
{
	return GetValue( tNtpdInfo, g_tALLConfigData.m_tNtpdInfo );
}

void SetHostFile(s8* pszIp)
{
	s8 achBuf[MAX_LINE][MAX_COLUMN];
	memset(achBuf,0,sizeof(achBuf));
	s8 achHostName[32];
	memcpy(achHostName,"/etc/hosts",sizeof("/etc/hosts"));
	u16 wLine = 0;
	FILE* pfFileName = fopen(achHostName,"r+");
	if(NULL == pfFileName)
	{
		MdlError(Ums_Mdl_Service, ("[SetEthParam] File is not exist\n"));
		return;
	}
	while (fgets(achBuf[wLine],MAX_COLUMN,pfFileName))
	{
		if (strstr(achBuf[wLine],"rmq_1"))
		{
			sprintf(achBuf[wLine],"%s rmq_1\n",pszIp);
			MdlHint(Ums_Mdl_Service, ("[SetEthParam] change buf:%s,line:%d\n", achBuf[wLine],wLine));
		}

		wLine++;
		if (wLine > MAX_LINE-1)
		{
			MdlHint(Ums_Mdl_Service, ("[SetEthParam] Line is reached the max\n"));
			break;
		}
	}
	fclose(pfFileName);

	pfFileName = fopen(achHostName,"w+");
	if(NULL == pfFileName)
	{
		MdlError(Ums_Mdl_Service, ("[SetEthParam] File is not exist\n"));
		return;
	}
	for ( u16 wIndex = 0;wIndex < wLine;wIndex ++ )
	{
		fprintf(pfFileName,"%s",achBuf[wIndex]);
	}
	fclose(pfFileName);

}

void SetGKConfigFile(s8* pszIp)
{
	s8 achFileName[MAX_COLUMN] = {0};
	const   s8 umsGkInfo[] = "LocalInfo";
	const   s8 umsKeyGKIP[] = "IpAddr";
	strncpy(achFileName,"/usr/gkconfig.ini",sizeof(achFileName)-1);
	SetRegKeyString(achFileName,umsGkInfo,umsKeyGKIP ,pszIp);

}
API void ResetAllData()
{
	OspPrintf(TRUE, FALSE, "[ResetAllData], �ָ����е�Ĭ������ !\n");
	InitData();
}

API void SaveData()
{
	SaveAllCfgData();
}


