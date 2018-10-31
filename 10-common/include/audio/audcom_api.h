/*****************************************************************************
ģ����      : 
�ļ���      : audcom_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ½־��
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/5/13   1.0         ½־��         ����
******************************************************************************/
#ifndef  _AUDCOM_API_H_
#define  _AUDCOM_API_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

typedef struct
{	
	l32	(*Open) (void **ppvHandle, void *in);
	l32 (*Close)(void *pvHandle);
	l32 (*Process)(void *pvHandle, void *in, void *out, void *unionparam);
	l32 (*Control)(void *pvHandle, l32 cmdid, void *in, void *out);
	l32 (*GetVersion)(void *in, void *out);
}TAudCodecApi;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif
