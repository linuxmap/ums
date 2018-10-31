/*****************************************************************************
ģ����      : 
�ļ���      : videnc_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ����
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/4/18   1.0         ����        ����
******************************************************************************/
#ifndef  _VIDENC_API_H_
#define  _VIDENC_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum VidEncCmdId
{
    VIDENC_SET_PARAMS = 201,
    VIDENC_GET_STATUS,
    VIDENC_ANALYZE_ERRCODE,
    VIDENC_DEBUG		
};

l32 VidEncodeOpen(void **ppvHandle, void *in);
l32 VidEncodeClose(void *pvHandle);
l32 VidEncodeProcess(void *pvHandle, void *in, void *out, void *unionparam);
l32 VidEncodeControl(void *pvHandle, l32 cmdid, void *in, void *out);
l32 VidEncodeGetVersion(void *in, void *out);

extern TVidCodecApi tVidEnc;

#ifdef __cplusplus
}
#endif

#endif
