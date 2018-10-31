/*****************************************************************************
ģ����      : 
�ļ���      : audmixer_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ½־��
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/5/13   1.0         ½־��        ����
******************************************************************************/
#ifndef  _AUDMIXER_API_H_
#define  _AUDMIXER_API_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#include "audcom_api.h"

enum AudMixerCmdId
{
    AUDMIX_GET_STATUS = 801,
    AUDMIX_ANALYZE_ERRCODE,
    AUDMIX_DEBUG		
};

l32 AudMixerOpen(void **ppvHandle, void *ptAudMixParam);
l32 AudMixerClose(void *pvHandle);
l32 AudMixerProcess(void *pvHandle, void *ptAudMixInput, void *ptAudMixOutput, void *unionparam);
l32 AudMixerControl(void *pvHandle, l32 cmdid, void *ptAudMixControlInParam, void *ptAudMixControlOutParam);
l32 AudMixerGetVersion(void *ptAudVerInfoInput, void *ptAudVerInfoOutput);

extern TAudCodecApi tAudMixer;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


