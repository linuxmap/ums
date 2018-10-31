/*****************************************************************************
ģ����      : 
�ļ���      : xdm_videnc_com.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ����
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/2/26   1.0         ����        ����
******************************************************************************/
#ifndef  XDM_VIDENC_COM_H_
#define  XDM_VIDENC_COM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CHAR_BIT
   #define CHAR_BIT 8
#endif

/* : IVIDENC_Cmd */
enum VidEncCmdId
{
    VID_ENC_SET_PARAMS = 257,
    VID_ENC_GET_STATIS,
    VID_ENC_GET_STATUS,
    VID_ENC_PARSE_ERR_CODE,
    VID_ENC_GET_VER,
    VID_ENC_DEBUG		
};

/* :public IVIDENC_Params*/
typedef struct
{
    IVIDENC_Params videnc_Params;
    XDAS_UInt32 u32VidUnitEncParamAddr;    //VieoUnit��������ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
}TVidEncoderParams;

/* :public IVIDENC_InArgs*/
typedef struct
{
    IVIDENC_InArgs videnc_Inargs;
    TEncInput tEncInput;             //VideoUnit��������
}TVideoEncoderInputParam;

/* : public IVIDENC_OutArgs*/
typedef struct
{
	IVIDENC_OutArgs videnc_Outargs;
	TEncOutput tEncOutput;          //VideoUnit�������
}TVideoEncoderOutputParam;

/* :public IVIDENC_DynamicParams*/
typedef struct
{
    IVIDENC_DynamicParams videnc_DynamicParams;
    XDAS_UInt32 u32VidUnitEncDynParamAddr;    //VieoUnit���붯̬�����ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
    XDAS_UInt32 u32VidUnitEncStatAddr;        //VieoUnit����״̬�����ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
}TVidEncoderDynParams;

/* :public IVIDENC_Status*/
typedef struct
{
    IVIDENC_Status videnc_Status;
}TVidEncoderStat;

#ifdef __cplusplus
}
#endif

#endif
