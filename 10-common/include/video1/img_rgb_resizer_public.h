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
#ifndef _IMG_RGB_RESIZER_PUBLIC_H_
#define _IMG_RGB_RESIZER_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	l32 l32SrcWidth;     //Դͼ��Ŀ��
	l32 l32SrcHeight;    //Դͼ��ĸ߶�
	l32 l32SrcRGBType;

	l32 l32DstWidth;        //Ŀ��ͼ��Ŀ��
	l32 l32DstHeight;		//Ŀ��ͼ��ĸ߶�
	l32 l32DstRGBType;

    u32 u32Reserved;
}TImageRGBResizerParam;

//ͼ������ģ��״̬�ṹ��
#define TImageRGBResizerStatusParam TImageRGBResizerParam

//ͼ�������������
typedef struct
{
    //Դͼ��Y������ַ�����ڼ���RGB��stride��Ҫ���ֽڶ��룬
    //��������ռ�����ķ�ʽӦ����stride(((ptInput->l32SrcStride  * ptRGBResizerInfo->l32SrcRGBType  + 31) & ~31) >> 3)���Ը߶�
    // �ϲ��������ڴ��ʱ����Ҫע�⣬��Ҫ����Ŀռ䲻��
	u8 *pu8SrcAddr;			//Դͼ��Y������ַ
    void *pvRGBQuadMap;      //��ɫ����������
	l32 l32SrcStride;       //Դͼ���Y����ֵ��Ŀǰ��Ҫ���ľ���ͼ����ߵ�ͼ��ʵ��������
	u32 u32Reserved;
}TImageRGBResizerInput;

//ͼ�������������
typedef struct
{
    //Ŀ��ͼ���Y������ַ�����ڼ���RGB��stride��Ҫ���ֽڶ��룬
    //��������ռ�����ķ�ʽӦ����stride(((ptOutput->l32DstStride * ptRGBResizerInfo->l32DstRGBType + 31) & ~31) >> 3)���Ը߶�
    // �ϲ��������ڴ��ʱ����Ҫע�⣬��Ҫ����Ŀռ䲻������ɵײ�дԽ��
	u8 *pu8DstAddr;			//Ŀ��ͼ���Y������ַ
	l32 l32DstStride;       //Ŀ��ͼ���Y����ֵ
	u32 u32Reserved;
}TImageRGBResizerOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_RGB_RESIZER_PUBLIC_H_
