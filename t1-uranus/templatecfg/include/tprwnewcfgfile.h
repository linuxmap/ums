#ifndef TPRWNEWCFGFILE_H
#define TPRWNEWCFGFILE_H
#include "tpcfgdata.h"
#include <stdio.h>

#define TP_FILENAME_LENGTH  256

/*====================================================================
�� �� ���� SaveDataToTpFile
��    �ܣ� ���ڴ����ݽṹSAVE������ģ���ļ���
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� const s8 szFileName[TP_FILENAME_LENGTH],TTPConfTemplate atTPConfTemplate[TP_CONFTEMPLATE_MAXNUM]
�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
BOOL  SaveDataToTpFile( const s8 szFileName[TP_FILENAME_LENGTH], const TConfTemplateLocal atAllConfigData[TP_CONFTEMPLATE_MAXNUM], u16 wNum);

/*====================================================================
�� �� ���� SaveDataToTpFile
��    �ܣ� ���ڴ����ݽṹSAVE������ģ���ļ���
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� FILE* pfFileName,TTPConfTemplate atTPConfTemplate[TP_CONFTEMPLATE_MAXNUM]
�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
BOOL  SaveDataToTpFile( FILE* pfFileName, const TConfTemplateLocal atAllConfigData[TP_CONFTEMPLATE_MAXNUM], 
					   u16 wNum, s8* szFileName);

BOOL SaveDataToControlFile(const s8 *szControlFile, const TControlData tControlData);

#endif