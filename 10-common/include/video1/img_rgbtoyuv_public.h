/******************************************************************************
ģ����        ��img_rgbtoyuv_public
�ļ���        ��img_rgbtoyuv_public.h
����ļ�    ��
�ļ�ʵ�ֹ��ܣ�����RGBת����YUV��ʽ�Ĳ����ṹ��
����        ����ȫ��
�汾        ��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��            �汾            �޸���        �߶���      �޸�����
2009/12/22        1.0                ��ȫ��                  create
******************************************************************************/
#ifndef _IMG_RGBTOYUV_PUBLIC_H_
#define _IMG_RGBTOYUV_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    l32 l32SrcWidth;         //Դͼ��Ŀ��
    l32 l32SrcHeight;        //Դͼ��ĸ߶�
    l32 l32SrcStride;        //Դͼ���Y����ֵ��Ŀǰ��Ҫ���ľ���RGBͼ����ߵ�ͼ��ʵ��������
    l32 l32SrcRGBType;

    l32 l32DstWidth;         //Ŀ��ͼ��Ŀ�ȣ�Ŀǰֻ֧��ͬ�ߴ��ת�����˲�����ɸ�Դһ�����ɣ�������Ϊ���Ժ���չ
    l32 l32DstHeight;         //Ŀ��ͼ��ĸ߶ȣ�Ŀǰֻ֧��ͬ�ߴ��ת�����˲�����ɸ�Դһ�����ɣ�������Ϊ���Ժ���չ
    l32 l32DstStride;        //Ŀ��ͼ���Y����ֵ������������ͼ���ȼ���
    l32 l32DstYUVType;

    l32 l32TransposeFlag;    //�Ƿ���Ҫͼ��ת��0��ʾ����ת��1��ʾ��ת
    u32 u32Reserved;
}TImageRGBtoYUVParam;

//ͼ������ģ��״̬�ṹ��
#define TImageRGBtoYUVStatusParam TImageRGBtoYUVParam

//ͼ�������������
typedef struct
{
    u8 *pu8SrcBAddr;         //Դͼ��B������ַ,��������Ǳ�׼��RGB��ʽ��ֻ��Ҫ����һ��ָ�뼴��
    u8 *pu8SrcGAddr;         //Դͼ��G������ַ
    u8 *pu8SrcRAddr;         //Դͼ��R������ַ

    void *pvRGBQuadMap;      //��ɫ����������,Ϊ�˽�����չ��������ʱ���Բ���
    u32 u32Reserved;
}TImageRGBtoYUVInput;

//ͼ�������������
typedef struct
{
    u8 *pu8DstYAddr;            //Ŀ��ͼ���Y������ַ
    u8 *pu8DstUAddr;            //Ŀ��ͼ���U������ַ
    u8 *pu8DstVAddr;            //Ŀ��ͼ���V������ַ

    u32 u32Reserved;
}TImageRGBtoYUVOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_RGBTOYUV_PUBLIC_H_
