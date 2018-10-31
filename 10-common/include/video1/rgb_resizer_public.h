/******************************************************************************
ģ����	    ��rgb_resizer_public
�ļ���	    ��rgb_resizer_public.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����ͼ�����ſ�����ṹ��
����		����ȫ��
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���      �޸�����
2008/10/17		1.0				��ȫ��                  create
******************************************************************************/
#ifndef _RGB_RESIZER_PUBLIC_H_
#define _RGB_RESIZER_PUBLIC_H_

#include "videodefines.h"

typedef struct
{
	l32 l32SrcWidth;     //Դͼ��Ŀ��
	l32 l32SrcHeight;    //Դͼ��ĸ߶�
	l32 l32SrcRGBType;

	l32 l32DstWidth;        //Ŀ��ͼ��Ŀ��
	l32 l32DstHeight;		//Ŀ��ͼ��ĸ߶�
	l32 l32DstRGBType;

    u32 u32Reserved;
}TRGBResizerParam;

//ͼ������ģ��״̬�ṹ��
#define TRGBResizerStatusParam TRGBResizerParam

//ͼ�������������
typedef struct
{
	u8 *pu8SrcAddr;			//Դͼ��Y������ַ

	l32 l32SrcStride;          //Դͼ���Y����ֵ

	u32 u32Reserved;
}TRGBResizerInput;

//ͼ�������������
typedef struct
{
	u8 *pu8DstAddr;			//Ŀ��ͼ���Y������ַ

	l32 l32DstStride;          //Ŀ��ͼ���Y����ֵ

	u32 u32Reserved;
}TRGBResizerOutput;

#endif //_RGB_RESIZER_PUBLIC_H_
