// czip.h: interface for the CGZip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GZIP_H__40AD6D0E_0E52_4E5A_8727_0AFA8CFC98D4__INCLUDED_)
#define AFX_GZIP_H__40AD6D0E_0E52_4E5A_8727_0AFA8CFC98D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kdvtype.h"
#include <WTYPES.H>

class CGZip
{
public:
	CGZip();
	virtual ~CGZip();

public:
    /*=============================================================================
    �� �� ��: Zip
    ��    ��: ѹ��
    ��    ��: LPCSTR lpszSrcFile        [in]    ��ѹ���ļ�
              LPCSTR lpszDstFile        [in]    ѹ������ļ�
    ע    ��: ��
    �� �� ֵ: ѹ���ɹ�: TRUE; ѹ��ʧ��: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2007/06/29  1.0     ���    ����
    =============================================================================*/
    BOOL32 Zip(LPCSTR lpszSrcFile, LPCSTR lpszDstFile);

    /*=============================================================================
    �� �� ��: Unzip
    ��    ��: ��ѹ
    ��    ��: LPCSTR lpszSrcFile        [in]    ����ѹ�ļ�
              LPCSTR lpszDstFile        [in]    ��ѹ����ļ�
    ע    ��: ��
    �� �� ֵ: ��ѹ�ɹ�: TRUE; ��ѹʧ��: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2007/06/29  1.0     ���    ����
    =============================================================================*/
    BOOL32 Unzip(LPCSTR lpszSrcFile, LPCSTR lpszDstFile);

private:
};

#endif // !defined(AFX_GZIP_H__40AD6D0E_0E52_4E5A_8727_0AFA8CFC98D4__INCLUDED_)
