/*===========================================================================================
模块名：meetingtemplate
文件名   : tpconfig.cpp                                                     
相关文件 :                                                                 
实现功能 : 会议模版参数的读取，设置，初始化等操作
作者：胡子龙
版权：
----------------------------------------------------------------------------------------------
修改记录：
日期            版本            修改人            走读人         修改记录
2011-7-25       v1.0            胡子龙                           创建

==============================================================================================*/
#include "tpconfig.h"
#include "string.h"
#include "systpcom.h"
#include "kdvsys.h"
#include "tpcfginstance.h"
#include "tprwnewcfgfile.h"
#include <stdio.h>
#include "tppersistfile.h"
#include "tplog.h"
#include "umsconfig.h"
#include "tpsys.h"
#include "osp.h"
#include "umsobject.h"
#include "tpinfo.h"

#ifdef _LINUX_
#include <sys/stat.h>
#endif


CTpCfgDataApp g_cTpCfgDataApp;
extern CTpCfgDataManager g_cTpCfgDataMan[TP_CONFTEMPLATE_MAXNUM];
extern CTpCfgDataManager g_cTpControlDataMan;

SEMHANDLE   s_semQuitCfg;


#ifndef FILE_TPCFG_INI
#define FILE_TPCFG_INI (s8*)"templatecfg_"
#endif


BOOL TemplateMakeDir(s8 *szFileName)
{
#ifdef _LINUX_
	mode_t oldmode;
#endif
	/*先创建目录*/
	s8 achDirName[TP_FILENAME_LENGTH] = {0};
	s8 *pchDest = NULL;
	
	strncpy( achDirName, szFileName, sizeof(achDirName) );
	pchDest = strstr( achDirName, FILE_TPCFG_INI );
	if ( !pchDest )
	{
        MdlError(Ums_Mdl_Cfg,("[TpConfig]:[TpMakeDir] Wrong Get file path %s error \n",
			achDirName));
		return FALSE;
	}
	
	pchDest--;
	if ( *pchDest != '\\' && *pchDest != '/' )
	{
		MdlError(Ums_Mdl_Cfg,("[TpConfig]:[TpMakeDir] %s Wrong %s file path %d\n",
			__FILE__,pchDest,__LINE__ ));
		return FALSE;
	}
	
	*pchDest = '\0';
	
	if( strlen(achDirName) != 0 )
	{
#ifdef _LINUX_
		oldmode = umask(0);
#endif
		UmsMakeDir( achDirName );
#ifdef _LINUX_
		umask(oldmode);
#endif
	}
	else
	{
		MdlError(Ums_Mdl_Cfg,("[TpConfig]:[TpMakeDir]  %s Wrong %s file path %d\n",
			__FILE__,achDirName,__LINE__ ));
		return FALSE;
		
	}
	
	return TRUE;
}

/*====================================================================
  函 数 名： InitCfg
  功    能： 初始化配置文件模块
  算法实现： 
  全局变量： g_CfgDataApp，g_szTpFileName, g_semAllConfig
  参    数： void
  返 回 值： BOOL 
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/8/16      1.0		    张 飞                   创建
======================================================================*/
BOOL InitTpCfg(void)
{
    // 创建计数信号量--huzilong/2011/09/20
    if( !OspSemCCreate( &s_semQuitCfg, 0, 1 ) )
    {
        MdlError(Ums_Mdl_Cfg,("[InitTpCfg] create s_semQuitCfg failed!\n" ));
		return FALSE;
    }

	//初始化控制配置文件，序号使用INVALID
	g_cTpControlDataMan.InitConfigure(UmsGetFileName(emUmsTpControlFile),TP_INVALID_INDEX);

	//初始化创建配置文件
	for(u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{	
		g_cTpCfgDataMan[wIndex].InitConfigure(UmsGetFileName(emUmsTpFile), wIndex);
	}

	if (!CTemplateInfo::Instance().Init())
	{
		MdlError(Ums_Mdl_Cfg,("[InitTpCfg] CTemplateInfo init failed!\n" ));
		return FALSE;
	}

    //启动文件持久化程序	    
	g_cTpCfgDataApp.CreateApp("CTPCFGAPP",AID_TP_CFGDATA,AID_TP_PROP, 512);
	::OspPost(MAKEIID(AID_TP_CFGDATA),EV_TPCFG_INIT_CMD, NULL, 0);


	msgprint("InitTpCfg Complete\n");

	return TRUE;
}

/*====================================================================
  函 数 名： QuitCfg
  功    能： 释放资源，并退出该模块
  算法实现： 
  全局变量： s_semAllConfig
  参    数： void
  返 回 值： void 
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/8/17      1.0		    张 飞                   创建
======================================================================*/
void QuitTp(void)
{
	msgprint("Tpconfig begin to eixt.\n");

	::OspSend(MAKEIID(AID_TP_CFGDATA), EV_TP_SAVE_CMD);

    OspSemTake( s_semQuitCfg );
    OspSemGive( s_semQuitCfg );
    OspSemDelete( s_semQuitCfg );

	msgprint("the Tpconfig will be eixt...\n");
}

/*====================================================================
函 数 名： umsSetConfTempInfo
功    能： 设置指定索引的会议模版信息
算法实现： 
全局变量： 
参    数： TTPConfTemplate tTpConfTemplate, u16 wIndex
返 回 值： 
--------------------------------------------------------------------
修改记录：
日  期	      版本		    修改人		走读人    修改内容
2011/7/28     1.0		    胡子龙                   创建
======================================================================*/
BOOL umsSetConfTempInfo( TConfTemplateLocal& tTpConfTemplate, u16 wIndex )
{
	return CTemplateInfo::Instance().SetConfTempInfo(tTpConfTemplate, wIndex);
}

BOOL32 umsDelConfTempInfo(u16 wIndex)
{
	return CTemplateInfo::Instance().DelConfTempInfo(wIndex);
}


/*====================================================================
函 数 名： umsGetConfTempInfo
功    能： 获得指定索引的会议模版
算法实现： 
全局变量： 
参    数： TTPConfTemplate &tTpConfTemplate, u16 wIndex
返 回 值： 
--------------------------------------------------------------------
修改记录：
日  期	      版本		    修改人		走读人    修改内容
2011/7/28     1.0		    胡子龙                   创建
======================================================================*/
BOOL umsGetConfTempInfo( TConfTemplateLocal &tTpConfTemplate, u16 wIndex )
{
	return CTemplateInfo::Instance().GetConfTempInfo(tTpConfTemplate, wIndex);
}

void umsUpLoadConfTempFile(s8* szFileName)
{
	::OspPost(MAKEIID(AID_TP_CFGDATA), EV_TP_UPLOAD_FILE, szFileName,  strlen(szFileName) + 1);
}

void umsDownLoadConTemp()
{
	::OspPost(MAKEIID(AID_TP_CFGDATA), EV_TP_DOWNLOAD_FILE, NULL,  0);
}