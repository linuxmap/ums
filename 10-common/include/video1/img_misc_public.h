/******************************************************************************
ģ����	    ��img_misc_public
�ļ���	    ��img_misc_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ���������ͼ��Ĳ����ṹ��
����		��zwenyi
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2007/09/14		1.0				zwenyi                  ����
******************************************************************************/
#ifndef _IMG_MISC_PUBLIC_H_
#define _IMG_MISC_PUBLIC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "videodefines.h"

//generateimage���ò����ṹ��
typedef struct
{
    l32 l32PatternType; //ͼ������
	l32 l32Width;       //����ͼ��߶�
	l32 l32Height;      //����ͼ����
}TImageGenerateImageParam;

//generateimage����״̬�ṹ��
#define TImageGenerateImageStatusParam TImageGenerateImageParam

//GenerateImage���������
typedef struct  
{
    u8 *pu8YUV;   //ָ��ͼ��ָ��
}TImageGenerateImageInput;

//GenerateImage���������
typedef struct  
{
    u32 u32Reserved; //��������
}TImageGenerateImageOutput;

#ifdef __cplusplus
}
#endif

#endif // _IMG_MISC_PUBLIC_H_
