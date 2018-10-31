/******************************************************************************
ģ����	    ��img_zoom_public
�ļ���	    ��img_zoom_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����ͼ�����ſ�����ṹ��
����		��zhaobo
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���      �޸�����
2007/09/13		1.1				zhaobo                  create
2008/01/02      2.0             zhaobo                  add img_apt_zoom�ṹ��
******************************************************************************/
#ifndef _IMG_ZOOM_PUBLIC_H_
#define _IMG_ZOOM_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//ͼ�����Ų���
typedef struct  
{
	l32 l32SrcWidth;		//����ͼ��Ŀ��
	l32 l32SrcHeight;		//����ͼ��ĸ߶�
	l32 l32SrcYStride;		//����ͼ��Y�����Ŀ��
	l32 l32SrcUVStride;		//����ͼ��UV�����Ŀ��
	l32 l32SrcYUVType;		//����ͼ���ͼ������
	l32 l32SrcIsInterlace;	//����ͼ���֡������

	l32 l32DstWidth;		//���ͼ��Ŀ��
	l32 l32DstHeight;		//���ͼ��ĸ߶�
	l32 l32DstYStride;		//���ͼ��Y�����Ŀ��
	l32 l32DstUVStride;		//���ͼ��UV�����Ŀ��
	l32 l32DstYUVType;		//���ͼ���ͼ������
	l32 l32DstIsInterlace;	//���ͼ���֡������

	u8 u8ImageZoomID;		//ͼ�����Ŵ�������

}TImageZoomParam;

//ͼ������ģ��״̬�ṹ��
#define TImageZoomStatusParam TImageZoomParam

//ͼ�������������
typedef struct
{
	u8 *pu8Input;			//Դͼ��
	u8 *pu8Output;			//Ŀ��ͼ��
}TImageZoomInput;

//ͼ�������������
typedef struct
{
	u32 u32Reserved;		//��������
}TImageZoomOutput;

//PNת���Ĳ���
typedef struct  
{
	l32 l32SrcWidth;		//����ͼ��Ŀ��
	l32 l32SrcHeight;		//����ͼ��ĸ߶�
	l32 l32SrcYStride;		//����ͼ��Y�����Ŀ��
	l32 l32SrcUVStride;		//����ͼ��UV�����Ŀ��
	l32 l32SrcYUVType;		//����ͼ���ͼ������
	l32 l32SrcIsInterlace;	//����ͼ���֡������
	u8 u8SrcTVFormat;		//����ͼ�����ʽ

	l32 l32DstWidth;		//���ͼ��Ŀ��
	l32 l32DstHeight;		//���ͼ��ĸ߶�
	l32 l32DstYStride;		//���ͼ��Y�����Ŀ��
	l32 l32DstUVStride;		//���ͼ��UV�����Ŀ��
	l32 l32DstYUVType;		//���ͼ���ͼ������
	l32 l32DstIsInterlace;	//���ͼ���֡������
	u8 u8DstTVFormat;		//���ͼ�����ʽ
	
	u8 u8InOutIsOneBuffer;	//PN��ת���Ƿ�ʹ��ͬһ���ڴ�
}TImagePNChangeParam;

//PNת����״̬�ṹ��
#define TImagePNChangeStatusParam TImagePNChangeParam

//PNת�����������
typedef struct
{
	u8 *pu8Input;			//Դͼ��
	u8 *pu8Output;			//Ŀ��ͼ��(Դͼ���Ŀ��ͼ�����һ��)
}TImagePNChangeInput;

//PNת�����������
typedef struct
{
	u32 u32Reserved;		//��������
}TImagePNChangeOutput;

//ͼ��ת��Ϊ16:9��ʽģ���ʼ�������ṹ
typedef struct
{  
	l32 l32Width;       //ͼ��Ŀ��
	l32 l32Height;      //ͼ��ĸ߶�
	l32 l32IsInterlace;	//ͼ�������(֡��ʽ���߳���ʽ)
	l32 l32YUVType;		//ͼ��YUV����
	u8 u8TVFormat;		//ͼ����ʽ
	
}TImageAdapt16vs9Param;

//ͼ��ת��Ϊ16:9��ʽģ��״̬�ṹ��
#define TImageAdapt16vs9StatusParam TImageAdapt16vs9Param

//ͼ��ת��Ϊ16:9��ʽģ������ṹ��
typedef struct 
{
    u8 *pu8YUV;    //ͼ���ַ
}TImageAdapt16vs9Input;
 
//ͼ��ת��Ϊ16:9��ʽģ������ṹ��
typedef struct 
{
    u32 u32Reserved;   //�������� 
}TImageAdapt16vs9Output;

//�����ϲ����õĲ�������ͼ��ģ���ʼ�������ṹ
typedef struct
{
    l32 l32Width;		    //Դͼ��Ŀ��
    l32 l32Height;		    //Դͼ��ĸ߶�
    l32 l32YStride;		    //Դͼ��Y�����Ŀ��
    l32 l32UVStride;		//Դͼ��UV�����Ŀ��
    l32 l32SrcYUVType;	    //����ͼ���ͼ������
    l32 l32DstWidth;		//Ŀ��ͼ��Ŀ��
    l32 l32DstHeight;		//Ŀ��ͼ��ĸ߶�
    l32 l32DstStride;		//Ŀ��ͼ��Ŀ��
    l32 l32DstYUVType;		//���ͼ���ͼ������
    l32 l32SrcIsInterlace;  //����ͼ���֡������
    l32 l32DstIsInterlace;	//���ͼ���֡������

    l32 l32LeftOffset;		//���ͼ����ߺڿ���(������4�ı���)
    l32 l32RightOffset;		//���ͼ���ұߺڿ���(������4�ı���)
    l32 l32TopOffset;		//���ͼ���ϱߺڿ���(������4�ı���)
    l32 l32BottomOffset;	//���ͼ���±ߺڿ���(������4�ı���)

    u32 u32Reserved;		//��������
}TImageAptZoomParam;

//�����ϲ����õĲ�������ͼ��ģ��״̬�ṹ��
#define TImageAptZoomStatusParam TImageAptZoomParam

//�����ϲ����õĲ�������ͼ��ģ�������ṹ��
typedef struct 
{
    u8 *pu8Input;			//Դͼ��
    u8 *pu8Output;			//Ŀ��ͼ��
}TImageAptZoomInput;

//�����ϲ����õĲ�������ͼ��ģ�������ṹ��
typedef struct 
{
    u8 *pu8Reserved;        //��������
}TImageAptZoomOutput;

//���õĽṹ
//UYVYͼ�����Žṹ��
//ͼ��Ŀ�Ȱ������ҵĺڱ߿�ȣ�ͼ���ȿ���С��ͼ��Ŀ��
//ͼ��ĸ߶Ȱ������µĺڱ߿��
//Դͼ���Ŀ��ͼ��Ľṹ����
//ͨ������ṹ�Ϳ���ʵ��Դͼ��������λ�õ�ͼ�����ŵ�Ŀ��ͼ�������λ�ã���֧�ּӺڱ�
//���������ȫ����ʡȥͼ��ϳɵ�����
typedef struct
{
    l32 l32SrcWidth;		//����ͼ��Ŀ��
    l32 l32SrcHeight;		//����ͼ��ĸ߶�
    l32 l32SrcStride;		//����ͼ��Y�����Ŀ�ȣ����ͼ�ܿ��Ϊ1280������ֵΪ1280
    l32 l32SrcIsInterlace;	//����ͼ���֡������

    l32 l32DstWidth;		//���ͼ��Ŀ�ȣ������ڱߵĿ��
    l32 l32DstHeight;		//���ͼ��ĸ߶ȣ������ڱߵĿ��
    l32 l32DstStride;		//���ͼ��Y�����Ŀ�ȣ����ͼ�ܿ��Ϊ1280������ֵΪ1280
    l32 l32DstIsInterlace;	//���ͼ���֡������

	l32 l32TopBlackLine;    //����ĺڱ�����
	l32 l32BottomBlackLine; //����ĺڱ�����
	l32 l32LeftBlackLine;   //��ߵĺڱ�������ӦΪ2�ı���
	l32 l32RightBlackLine;  //�ұߵĺڱ�������ӦΪ2�ı���

    l32 l32Reserved;
}TImageAptZoomUYVYParam;

//UYVYͼ������ģ��״̬�ṹ��
#define TImageAptZoomUYVYStatusParam TImageAptZoomUYVYParam

//UYVYͼ�������������
typedef struct
{
    u8 *pu8Input;			//Դͼ�񣬿�����Դͼ�������λ��
    u8 *pu8Output;			//Ŀ��ͼ�󣬿�����Ŀ��ͼ�������λ��
}TImageAptZoomUYVYInput;

//UYVYͼ�������������
typedef struct
{
    u32 u32Reserved;		//��������
}TImageAptZoomUYVYOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_ZOOM_PUBLIC_H_
