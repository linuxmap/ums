/*===========================================================================================
ģ������meetingtemplate
�ļ���   : tpconfig.cpp                                                     
����ļ� :                                                                 
ʵ�ֹ��� : ����ģ������Ķ�ȡ�����ã���ʼ���Ȳ���
���ߣ�������
��Ȩ��
----------------------------------------------------------------------------------------------
�޸ļ�¼��
����            �汾            �޸���            �߶���         �޸ļ�¼
2011-7-25       v1.0            ������                           ����

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
	/*�ȴ���Ŀ¼*/
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
  �� �� ���� InitCfg
  ��    �ܣ� ��ʼ�������ļ�ģ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� g_CfgDataApp��g_szTpFileName, g_semAllConfig
  ��    ���� void
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2005/8/16      1.0		    �� ��                   ����
======================================================================*/
BOOL InitTpCfg(void)
{
    // ���������ź���--huzilong/2011/09/20
    if( !OspSemCCreate( &s_semQuitCfg, 0, 1 ) )
    {
        MdlError(Ums_Mdl_Cfg,("[InitTpCfg] create s_semQuitCfg failed!\n" ));
		return FALSE;
    }

	//��ʼ�����������ļ������ʹ��INVALID
	g_cTpControlDataMan.InitConfigure(UmsGetFileName(emUmsTpControlFile),TP_INVALID_INDEX);

	//��ʼ�����������ļ�
	for(u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{	
		g_cTpCfgDataMan[wIndex].InitConfigure(UmsGetFileName(emUmsTpFile), wIndex);
	}

	if (!CTemplateInfo::Instance().Init())
	{
		MdlError(Ums_Mdl_Cfg,("[InitTpCfg] CTemplateInfo init failed!\n" ));
		return FALSE;
	}

    //�����ļ��־û�����	    
	g_cTpCfgDataApp.CreateApp("CTPCFGAPP",AID_TP_CFGDATA,AID_TP_PROP, 512);
	::OspPost(MAKEIID(AID_TP_CFGDATA),EV_TPCFG_INIT_CMD, NULL, 0);


	msgprint("InitTpCfg Complete\n");

	return TRUE;
}

/*====================================================================
  �� �� ���� QuitCfg
  ��    �ܣ� �ͷ���Դ�����˳���ģ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� s_semAllConfig
  ��    ���� void
  �� �� ֵ�� void 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2005/8/17      1.0		    �� ��                   ����
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
�� �� ���� umsSetConfTempInfo
��    �ܣ� ����ָ�������Ļ���ģ����Ϣ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� TTPConfTemplate tTpConfTemplate, u16 wIndex
�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/28     1.0		    ������                   ����
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
�� �� ���� umsGetConfTempInfo
��    �ܣ� ���ָ�������Ļ���ģ��
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� TTPConfTemplate &tTpConfTemplate, u16 wIndex
�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/28     1.0		    ������                   ����
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