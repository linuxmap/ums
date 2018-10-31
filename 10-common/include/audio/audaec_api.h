/*****************************************************************************
ģ����      : 
�ļ���      : audaec_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ½־��
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/5/13   1.0         ½־��        ����
******************************************************************************/
#ifndef  _AUDAEC_API_H_
#define  _AUDAEC_API_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#include "audcom_api.h"

enum AudAecCmdId
{
    AUDAEC_GET_STATUS = 901,
    AUDAEC_AECTYPE_RESET,              //�޸ı��������ʱ�������
    AUDAEC_PLAYSIG_SET,                //��Զ���źŷ���Զ���źŵĻ�����
    AUDAEC_ANALYZE_ERRCODE,
    AUDAEC_DEBUG		
};

l32 AudAecOpen(void **ppvHandle, void *ptAudAecParam);
l32 AudAecClose(void *pvHandle);
l32 AudAecProcess(void *pvHandle, void *ptAecCapInput, void *out, void *unionparam);
l32 AudAecControl(void *pvHandle, l32 cmdid, void *ptAecControlInParam, void *ptAecControlOutParam);
l32 AudAecGetVersion(void *ptAudVerInfoInput, void *ptAudVerInfoOutput);

extern TAudCodecApi tAudAec;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


