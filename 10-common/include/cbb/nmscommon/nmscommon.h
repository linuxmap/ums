/*=======================================================================
ģ����      : ���ܹ���ģ���
�ļ���      : nmscommon.h
����ļ�    : 
�ļ�ʵ�ֹ���: �������������ģ�������
����        : ���ǿ
�汾        : V4.0  Copyright(C) 2003-2006 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2004/07/16  3.0     ���ǿ  ����
2005/12/08  4.0     ���    �����ļ������빦��
=======================================================================*/

#ifndef _NMSCOMMON_H
#define _NMSCOMMON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <comcat.h>
#include <afxole.h>
#include <objsafe.h>
#include <AFXCTL.H>
#include "osp.h"
#include "ftpctrl.h"
#include "calladdr.h"
#include "tplarray.h"
#include "tplhash.h"
#include "logmanage.h"
#include "hexasciistring.h"

//	ɾ������ָ��
#define DEL_PTR(p)              if (p != NULL) { delete p; p = NULL; }
//	ɾ������ָ��
#define DEL_PTR_ARRAY(p)        if (p != NULL) { delete [] p; p = NULL; }

//////////////////////////////////////////////////////////////////////////
//
//     ��ȫע��ocx�ؼ��ĸ�������
//
// Helper function to create a component category and associated description
HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription);
// Helper function to register a CLSID as belonging to a component category
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
// Helper function to unregister a CLSID as belonging to a component category
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid);

/*=============================================================================
�� �� ��:nmscommonver
��    ��:��ӡNmsCommon��İ汾��
��    ��:��
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2004/09/13  3.5     ���ǿ  ����
=============================================================================*/
API void nmscommonver(void);

/*=============================================================================
�� �� ��:GetConfBitrate
��    ��:��ȡ��������
��    ��:u32 **ppdwBitrate              [out]   ������������
         s32 &nNum                      [out]   �����С
         u32 dwMCUType                  [in]    MCU����
ע    ��:����Ҫ��ppdwBitrate����ռ�, �Ҳ���delete ppdwBitrate
         8000C MCUֻ֧�ֵ�4M
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2004/09/29  3.5     ���    ����
2007/04/25  4.0     ������  �޸�
=============================================================================*/
void GetConfBitrate(u32 **ppdwBitrate, s32 &nNum, u32 dwMCUType = 0);

/*=============================================================================
�� �� ��:GetModuleFullPath
��    ��:��ȡģ�������ļ���ȫ·��, ��������\
��    ��:��
ע    ��:���� C:\
�� �� ֵ:�ļ����ַ���
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2004/10/26  3.5     ���    ����
=============================================================================*/
CString GetModuleFullPath(void);

/*=============================================================================
�� �� ��:ModuleRegToOsp
��    ��:��OSPע�᱾ģ��
��    ��:��
ע    ��:��
�� �� ֵ:�ɹ���TRUE; ʧ�ܣ�FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2004/10/26  3.5     ���    ����
=============================================================================*/
BOOL32 ModuleRegToOsp(void);

/*=============================================================================
�� �� ��:GetUrl
��    ��:��ȡIE��ַ������
��    ��:const COleControl *pcCtrl          [in]    ocx�ؼ�
         CString &cstrUrl                   [out]    ��ַ������
ע    ��:��
�� �� ֵ:�ɹ�:TRUE; ʧ��:FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/08  4.0     ���    ����
=============================================================================*/
BOOL32 GetUrl(const COleControl *pcCtrl, CString &cstrUrl);

/*=============================================================================
�� �� ��:EncryptPwd
��    ��:�������
��    ��:LPCSTR lpszPwd                     [in]    ԭʼ����, �32λ(����'/0')
         s8 aszEncryptedPwd[64]             [out]   ��������
�㷨˵��:�ַ��滻
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/21  4.0     ���    ����
=============================================================================*/
void EncryptPwd(LPCSTR lpszPwd, s8 aszEncryptedPwd[64]);

/*=============================================================================
�� �� ��:DecryptPwd
��    ��:�������
��    ��:s8 aszEncryptedPwd[64]             [in]    ��������
         LPSTR lpszPwd                      [out]   ԭʼ����, �32λ(����'/0')
�㷨˵��:�ַ��滻
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/21  4.0     ���    ����
=============================================================================*/
void DecryptPwd(s8 aszEncryptedPwd[64], LPSTR lpszPwd);

/*=============================================================================
�� �� ��:InitNonChineseCtrl
��    ��:�����Ĳ���ϵͳ�����ʼ��
��    ��:��
�㷨˵��:��
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/08/04  4.0     ���    ����
=============================================================================*/
inline void InitNonChineseCtrl(void)
{
    //  wanghao 2006/08/04 �����Ĳ���ϵͳ����
    if ( PRIMARYLANGID( GetSystemDefaultLangID() ) != LANG_CHINESE )
    {
        TCHAR aszFontFile[MAX_PATH + 1] = _T("");
        GetWindowsDirectory( aszFontFile, MAX_PATH );
        _tcscat( aszFontFile, _T("\\Fonts\\simsun.ttc") );
        FILE *pf = fopen( aszFontFile, "r" );
        if ( pf != NULL )
        {
            fclose( pf );
            pf = NULL;
            ShellExecute( NULL, "open", aszFontFile, "", "", SW_HIDE );
            Sleep( 500 );   //�ȴ����尲װ���
        }
        else
        {
            CString cstrFontFile = GetModuleFullPath() + _T("simsun.ttc");
            pf = fopen( cstrFontFile, "r" );
            if ( pf != NULL )
            {
                fclose( pf );
                pf = NULL;
                CopyFile( cstrFontFile, aszFontFile, TRUE );
                ShellExecute( NULL, "open", aszFontFile, "", "", SW_HIDE );
                Sleep( 500 );   //�ȴ����尲װ���
            }
        }
    }
}

/*=============================================================================
�� �� ��: GetModuleCfgFileFullName
��    ��: ��ȡ�����ļ�ȫ·��
��    ��: LPCSTR lptrFileName                   [in]    �����ļ���
ע    ��: ��
�� �� ֵ: �����ļ�ȫ·��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2007/03/01  1.0     ���    ����
=============================================================================*/
CString GetModuleCfgFileFullName(LPCSTR lptrFileName);

/*========================================================================
�� �� ����CheckIEBHOAvailable
��    �ܣ����IE���Ƿ�����˺����ǵ�OCX�ؼ������ݵĲ��
ע    �⣺�����ڿؼ���InitInstance()�н��е��ã��緵��FALSE��ؼ��˳�
          ���磺
            BOOL CTestApp::InitInstance()
            {
	            BOOL bInit = COleControlModule::InitInstance();

	            if (bInit)
	            {
                    BOOL bBHOAvailable = CheckIEBHOAvailable( 0 );
                    if ( FALSE == bBHOAvailable )
                    {
                        return FALSE;
                    }
	            }

	            return bInit;
            }

��    ����u32 dwLanguage        [in]    ��������    0ΪӢ�ģ�1Ϊ����
�� �� ֵ��TRUE��    û�в����ݵĲ�����û�ѡ��ж����Ӧ�Ĳ��
          FALSE��   ��⵽�в����ݵĲ�������û�ѡ��ж����Ӧ�Ĳ��
�����Ϣ��
--------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾    �޸���  �޸�����
2007/11/07  1.0     ������    ����
========================================================================*/
BOOL32 CheckIEBHOAvailable(u32 dwLanguage);


#endif // _NMSCOMMON_H