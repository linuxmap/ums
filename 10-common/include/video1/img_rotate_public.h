/******************************************************************************
ģ����      ��img_rotate_public
�ļ���      ��img_rotate_public.h
����ļ�    ��
�ļ�ʵ�ֹ��ܣ�����ͼ����ת�����ṹ��
����        ���Բ�
�汾        ��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��            �汾            �޸���        �߶���      �޸�����
2012/03/14        1.0             �Բ�                        ����
******************************************************************************/
#ifndef _IMG_ROTATE_PUBLIC_H_
#define _IMG_ROTATE_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define IMAGE_MIRROR -1

//ͼ����ת��ʼ������
typedef struct
{
    l32 l32SrcWidth;    //����ͼ��Ŀ��
    l32 l32SrcHeight;   //����ͼ��ĸ߶�
       
    l32 l32DstWidth;    //Ŀ��ͼ���ͼ�Ŀ��(������ڵ���l32Width)
    l32 l32DstHeight;   //Ŀ��ͼ���ͼ�ĸ߶�(������ڵ���l32Height)

    l32 l32YUVType;     //����ͼ���ͼ�����ͣ�ΪYUV420����YUV422P

    l32 l32BgYColor;    //������ͼ��������ɫY����,ĿǰTI�汾��֧�ֱ������
    l32 l32BgUColor;    //������ͼ��������ɫU����,ĿǰTI�汾��֧�ֱ������
    l32 l32BgVColor;    //������ͼ��������ɫV����,ĿǰTI�汾��֧�ֱ������
    
    l32 l32Angel;       //ͼ����ת�Ƕȡ�����תΪIMAGE_MIRROR��

    u32 u32Reserved;
}TImageRotateParam;


//ͼ����תģ��״̬�ṹ��
#define TImageRotateStatusParam TImageRotateParam

//ͼ����ת�������
typedef struct
{
    u8 *pu8SrcY;    //Դͼ��Y������ַ
    u8 *pu8SrcU;    //Դͼ��U������ַ(���YUV��ַ���������Խ�pu8SrcU��pu8SrcV��ΪNULL)
    u8 *pu8SrcV;    //Դͼ��V������ַ(���YUV��ַ���������Խ�pu8SrcU��pu8SrcV��ΪNULL)

    l32 l32SrcYStride;  //Դͼ���Y����ֵ
    l32 l32SrcUVStride; //Դͼ���UV����ֵ(l32SrcYStride��һ�룬����Ҫ��д)

    u32 u32Reserved;
}TImageRotateInput;

//ͼ����ת�������
typedef struct
{
    u8 *pu8DstY;    //Ŀ��ͼ���Y������ַ
    u8 *pu8DstU;    //Ŀ��ͼ���U������ַ(���YUV��ַ���������Խ�pu8DstU��pu8DstV��ΪNULL)
    u8 *pu8DstV;    //Ŀ��ͼ���V������ַ(���YUV��ַ���������Խ�pu8DstU��pu8DstV��ΪNULL)

    l32 l32DstYStride;  //Ŀ��ͼ���Y����ֵ(���ͼ���stride��������ͼ��Ŀ��)
    l32 l32DstUVStride; //Ŀ��ͼ���UV����ֵ(l32DstYStride��һ�룬����Ҫ��д)

    u32 u32Reserved;
}TImageRotateOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_ROTATE_PUBLIC_H_
