/*****************************************************************************
ģ����      : 
�ļ���      : xdm_viddec_com.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ����
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/2/26   1.0         ����        ����
******************************************************************************/
#ifndef  XDM_VIDDEC_COM_H_
#define  XDM_VIDDEC_COM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CHAR_BIT
   #define CHAR_BIT 8
#endif

/* : IVIDDEC_Cmd */
enum VidDecCmdId
{
    VID_DEC_SET_PARAMS = 264,
    VID_DEC_GET_STATIS,
    VID_DEC_GET_STATUS,
    VID_DEC_PARSE_ERR_CODE,
    VID_DEC_GET_VER,
    VID_DEC_DEBUG		
};

/* :public IVIDDEC_Params*/
typedef struct
{
	IVIDDEC_Params viddec_Params;
	XDAS_UInt32 u32VidUnitDecParamAddr;  //VieoUnit��������ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
}TVidDecoderParams;

/* :public IVIDDEC_InArgs*/
typedef struct
{
	IVIDDEC_InArgs viddec_Inargs;
	TDecInput tDecInput;             //VideoUnit��������
}TVideoDecoderInputParam;

/* : public IVIDDEC_OutArgs*/
typedef struct
{
	IVIDDEC_OutArgs viddec_Outargs;
	TDecOutput tDecOutput;           //VideoUnit�������
}TVideoDecoderOutputParam;

/* :public IVIDDEC_DynamicParams*/
typedef struct
{
    IVIDDEC_DynamicParams viddec_DynamicParams;
    XDAS_UInt32 u32VidUnitDecDynParamAddr;    //VieoUnit���붯̬�����ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
    XDAS_UInt32 u32VidUnitDecStatAddr;        //VieoUnit����״̬�����ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
}TVidDecoderDynParams;

/* :public IVIDDEC_Status*/
typedef struct
{
    IVIDDEC_Status viddec_Status;
}TVidDecoderStat;

#ifdef __cplusplus
}
#endif

#endif
