/*****************************************************************************
ģ����      : 
�ļ���      : xdm_imgproc_com.h
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ����
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/2/28   1.0          ����         ����
******************************************************************************/
#ifndef  XDM_IMGPROC_COM_H_
#define  XDM_IMGPROC_COM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CHAR_BIT
   #define CHAR_BIT 8
#endif

/* : IIMGDEC_Cmd */
enum ImgProcCmdId
{
    IMG_PROC_SET_PARAMS = 271,
    IMG_PROC_GET_STATIS,
    IMG_PROC_GET_STATUS,
    IMG_PROC_PARSE_ERR_CODE,
    IMG_PROC_GET_VER,
    IMG_PROC_DEBUG		
};

/*pub;ic:IIMGDEC_Params*/
typedef struct
{
	IVIDDEC_Params img_Params;
	XDAS_UInt32	u32ImgProcType; //ͼ��������
	XDAS_UInt32 u32ImgParamAddr;//ͼ��������ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
	XDAS_UInt32 u32ImgParamSize;//ͼ��������ṹ��С
	XDAS_UInt32 u32ImgRetVal;   //��������Ϣ
}TImgProcParam;

/* :public IIMGDEC_InArgs*/
typedef struct
{
	IVIDDEC_InArgs img_Inargs;
	XDAS_UInt32 u32ImgInputAddr;//ͼ��������ṹ��ַ�����ϲ㴫������ṹ�����ַ
    XDAS_UInt32 u32ImgOutputAddr;//ͼ��������ṹ��ַ�����ϲ㴫������ṹ�����ַ
}TImgInputParam;

/* : public IIMGDEC_OutArgs*/
typedef struct
{
	IVIDDEC_OutArgs img_Outargs;
}TImgOutputParam;

/* :public IIMGDEC_DynamicParams*/
typedef struct
{
    IVIDDEC_DynamicParams img_DynamicParams;
    XDAS_UInt32 u32ImgDynParamAddr;    //ͼ����̬�����ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
    XDAS_UInt32 u32ImgDynParamSize;    //ͼ����̬�����ṹ��С
    XDAS_UInt32 u32ImgStatAddr;        //ͼ����״̬�����ṹ��ַ�����ϲ㴫�²����ṹ�����ַ
}TImgProcDynParams;

/* :public IIMGDEC_Status*/
typedef struct
{
    IVIDDEC_Status img_Status;
}TImgProcStat;

#ifdef __cplusplus
}
#endif

#endif
