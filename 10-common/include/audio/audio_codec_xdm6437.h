/*****************************************************************************
ģ   ��   ��: ��Ƶ��tms320c6437��װ
��   ��   ��: audio_codec_xdm6437.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: ��������ؽṹ�����Ͷ���
��        ��: V1.0  Copyright(C) 2006-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2007/12/12      1.0         ½־��     ��    ��
******************************************************************************/
#ifndef AUDIO_CODEC_XDM6437_H
#define AUDIO_CODEC_XDM6437_H
#ifdef __cplusplus
extern "C" {
#endif

#include "audio_codec.h"
/***************************************************/
/*             ��Ƶ����Control ID�Ŷ���            */
/***************************************************/
enum XDM_AudioEncId{
	GETENC_VERSION = 0,                  //�õ�����汾��
	GETENC_STATUS                       //�õ�����״̬��Ϣ
}; 

/***************************************************/
/*             ������ؽṹ������                  */
/***************************************************/
//��������ṹ
typedef struct tagAUDIOENC_KDC_Params 
{
    IAUDENC_Params tAudEncParams;     //MUST be first field of all XDAS algs
    TAudEncParam tAudEncParam;         //��Ƶ�����ʹ�������ṹ��
} TAUDIOENC_KDC_Params;

//������������ṹ
typedef struct tagAUDIOENC_KDC_InArgs 
{
    IAUDENC_InArgs tAudEncInArgs;      //MUST be first field of all XDAS algs 
    TAudEncInput  tAudEncInput ;        // ��Ƶ��������ṹ��
} TAUDIOENC_KDC_InArgs;

//������������ṹ
typedef struct tagAUDIOENC_KDC_OutArgs 
{
    IAUDENC_OutArgs tAudEncOutArgs;       //MUST be first field of all XDAS algs 
    TAudEncOutput  tAudEncOutput;         //��Ƶ��������ṹ��
}TAUDIOENC_KDC_OutArgs;

//���붯̬�����ṹ
typedef struct tagAUDIOENC_KDC_DynamicParams 
{
    IAUDENC_DynamicParams  tAudEncDynamicParams;      // MUST be first field of all XDAS algs 
    XDAS_Int8 *             ps8VerBuf;                //  the buffer first_address of  the  version string 
    XDAS_Int32              l32InAudStrLen;           // the biggest length  of  the version string 
    XDAS_Int32              l32OutAudStrLen;          // the real length  of  the version string 
}TAUDIOENC_KDC_DynamicParams;

//����״̬�����ṹ
typedef struct tagAUDIOENC_KDC_Status 
{
    IAUDENC_Status tAudEncStatus;             // MUST be first field of all XDAS algs              
    TAudEncStatusParam  tAudEncStatusParam;   //��Ƶ����״̬�ṹ��
}TAUDIOENC_KDC_Status;

/***************************************************/
/*             ��Ƶ����Control ID�Ŷ���            */
/***************************************************/
enum XDM_AudioDecId{
    GETDEC_VERSION = 0,                  //�õ�����汾��
    GETDEC_STATUS                       //�õ�����״̬��Ϣ
}; 

/***************************************************/
/*             ������ؽṹ������                  */
/***************************************************/
//��������ṹ
typedef struct tagAUDIODEC_KDC_Params
{
    IAUDDEC_Params tAudDecParams;      // MUST be first field of all XDAS algs 
    TAudDecParam  tAudDecParam;         //��Ƶ�����ʹ�������ṹ��
}TAUDIODEC_KDC_Params;

//������������ṹ
typedef struct tagAUDIODEC_KDC_InArgs 
{
    IAUDDEC_InArgs tAudDecInArgs;      // MUST be first field of all XDAS algs 
    TAudDecInput tAudDecInput;        // ��Ƶ��������ṹ��
}TAUDIODEC_KDC_InArgs;

//������������ṹ
typedef struct tagAUDIODEC_KDC_OutArgs 
{
    IAUDDEC_OutArgs tAudDecOutArgs;      //MUST be first field of all XDAS algs 
    TAudDecOutput tAudDecOutput;         //��Ƶ��������ṹ��
} TAUDIODEC_KDC_OutArgs;

//���붯̬�����ṹ
typedef struct tagAUDIODEC_KDC_DynamicParams 
{
    IAUDDEC_DynamicParams  tAudDECDynamicParams;      // MUST be first field of all XDAS algs 
    XDAS_Int8 *             ps8VerBuf;                 //  the buffer first_address of  the  version string 
    XDAS_Int32              l32InAudStrLen;           // the biggest length  of  the version string 
    XDAS_Int32              l32OutAudStrLen;          // the real length  of  the version string 
}TAUDIODEC_KDC_DynamicParams;

//����״̬�����ṹ
typedef struct tagAUDIODEC_KDC_Status 
{
    IAUDDEC_Status tAudDecStatus;             // MUST be first field of all XDAS algs              
    TAudDecStatusParam  tAudDecStatusParam ;  //��Ƶ����״̬�ṹ��
}TAUDIODEC_KDC_Status;

#ifdef __cplusplus
}
#endif
#endif













