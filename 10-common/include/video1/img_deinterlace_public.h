/******************************************************************************
ģ����	    ��img_deinterlace_public
�ļ���	    ��img_deinterlace_public.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����ͼ�����ſ�����ṹ��
����		����ȫ��
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���      �޸�����
2008/06/18		1.0				��ȫ��                  create
******************************************************************************/
#ifndef _IMG_DEINTERLACE_PUBLIC_H_
#define _IMG_DEINTERLACE_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//Deinterlace���ò����ṹ��
typedef struct
{
	l32 l32Width;           //ͼ��߶�
	l32 l32Height;          //ͼ����
	l32 l32YStride;         //ͼ��Y��������
	l32 l32UVStride;        //ͼ��UV��������
	l32 l32DeinterlaceMode; //DEINTERLACEģʽ
	l32 l32Interlace;	    //ͼ���֡������(�Ƽ�ֵΪFRAME_FORMAT��Ŀǰֻ��DEINTERLACE_MODE_1�²�����FIELD_FORMAT�ĸ�ʽ)
	u32 u32Reserve;
}TImageDeinterlaceParam;

//Deinterlace״̬����
#define TImageDeinterlaceStatusParam TImageDeinterlaceParam

//Deinterlace������ṹ��
typedef struct
{
	u8 *pu8Y;      //ͼ��Y����ָ��
	u8 *pu8U;      //ͼ��U����ָ��
	u8 *pu8V;      //ͼ��V����ָ��
}TImageDeinterlaceInput;

//Deinterlace������ṹ��
typedef struct
{
    u32 u32Reserved; //��������
}TImageDeinterlaceOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_DEINTERLACE_PUBLIC_H_
