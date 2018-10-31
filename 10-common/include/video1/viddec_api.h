/*****************************************************************************
ģ����      : viddec_api
�ļ���      : viddec_api.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ����
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/4/18   1.0         ����        ����
******************************************************************************/
#ifndef  _VIDDEC_API_H_
#define  _VIDDEC_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum VidDecCmdId
{
    VIDDEC_SET_PARAMS = 301,
    VIDDEC_GET_STATUS,
    VIDDEC_ANALYZE_ERRCODE,
    VIDDEC_DEBUG		
};

l32 VidDecodeOpen(void **ppvHandle, void *in);
l32 VidDecodeClose(void *pvHandle);
l32 VidDecodeProcess(void *pvHandle, void *in, void *out, void *unionparam);
l32 VidDecodeControl(void *pvHandle, l32 cmdid, void *in, void *out);
l32 VidDecodeGetVersion(void *in, void *out);

extern TVidCodecApi tVidDec;

#ifdef __cplusplus
}
#endif

#endif
