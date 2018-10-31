/*****************************************************************************
ģ����      : 
�ļ���      : imgproc_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ����
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/4/18   1.0          ����         ����
******************************************************************************/
#ifndef  _VIDCOM_API_H_
#define  _VIDCOM_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{	
	l32	(*Open) (void **ppvHandle, void *in);
	l32 (*Close)(void *pvHandle);
	l32 (*Process)(void *pvHandle, void *in, void *out, void *unionparam);
	l32 (*Control)(void *pvHandle, l32 cmdid, void *in, void *out);
	l32 (*GetVerSion)(void *in, void *out);
}TVidCodecApi;

#ifdef __cplusplus
}
#endif

#endif
