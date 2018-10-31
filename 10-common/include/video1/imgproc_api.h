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
#ifndef  _IMGPROC_API_H_
#define  _IMGPROC_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum VidImgProcCmdId
{
    IMGPROC_SET_PARAMS = 401,
    IMGPROC_GET_STATUS,
    IMGPROC_ANALYZE_ERRCODE,
    IMGPROC_DEBUG		
};

typedef struct
{
    void *pvImgParam;   //ͼ��������ṹָ��
	u32	u32ImgProcType; //ͼ��������
	u32 u32Reserved;    // ��������
}TImgProcParam;

l32 ImgProcOpen(void **ppvHandle, void *in);
l32 ImgProcClose(void *pvHandle);
l32 ImgProcProcess(void *pvHandle, void *in, void *out, void *unionparam);
l32 ImgProcControl(void *pvHandle, l32 cmdid, void *in, void *out);
l32 ImgProcGetVersion(void *in, void *out);

extern TVidCodecApi tImgProc;

#ifdef __cplusplus
}
#endif

#endif
