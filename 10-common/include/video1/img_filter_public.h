/******************************************************************************
ģ����	    ��img_filter_public
�ļ���	    ��img_filter_public.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����ͼ���˲��Ĳ����ṹ��,Ŀǰ�ư������������
����		��zwenyi
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2007/09/14		1.0				zwenyi                  ����
2009/06/17      2.0             Z.Q.L                   ������ֱ�˲�
******************************************************************************/
#ifndef _IMG_FILTER_PUBLIC_H_
#define _IMG_FILTER_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	l32 l32WindowLeft;		//���������������߽�
	l32 l32WindowTop;		//��������������ϱ߽�
	l32 l32WindowWidth;		//������������Ŀ��
	l32 l32WindowHeight;	//������������ĸ߶�
	l32 l32Granularity;		//�����˵�����
}TMosaicInfo;

//�������˵Ĳ���
typedef struct
{
	l32 l32Width;			//ͼ��Ŀ��
	l32 l32Height;			//ͼ��ĸ߶�
	l32 l32YStride;			//ͼ��Y�����Ŀ��
	l32 l32UVStride;		//ͼ��UV�����Ŀ��
	l32 l32YUVType;			//ͼ���ͼ������
	l32 l32IsInterlace;		//ͼ���֡������

	l32 l32MosaicNum;		//��������˵�ʵ��·��
	TMosaicInfo tMosaicInfo[32];
}TImageMosaicParam;

//��������ģ��״̬�ṹ��
#define TImageMosaicStatusParam TImageMosaicParam

//�������˵��������
typedef struct
{
	u8 *pu8Input;			//Դͼ��
	u8 *pu8Output;			//Ŀ��ͼ��(Դͼ���Ŀ��ͼ�����һ��)
}TImageMosaicInput;

//�������˵��������
typedef struct
{
	u32 u32Reserved;		//��������
}TImageMosaicOutput;

//OSD filter�Ĳ���
typedef struct
{
    u8  u8Mask11;           //ƽ���˲�ǿ��
    s16 s16Brightness;      //���Ȳ���
    s16 s16Contrast;        //�ԱȶȲ���
    l32 l32Width;           //ͼ��Ŀ��
    l32 l32Height;          //ͼ��ĸ߶�
    u32 *pu32RefPic;        //�ο�ͼ���ַ
    u8  u8Sign;             //�Ƿ����µĲο�ͼ�����־λ
}TFilterOSDParam;

//OSD filter���������
typedef struct
{
    u32 *pu32Input;			//Դͼ��
	u32 *pu32Output;		//Ŀ��ͼ��(Դͼ���Ŀ��ͼ�����һ��)
}TFilterOSDInput;

//OSD filter���������
typedef struct
{
	u32 u32Reserved;		//��������
}TFilterOSDOutput;

//ͼ���˲�����
typedef struct
{
	l32 l32ImgWidth;     //Դͼ��Ŀ��
	l32 l32ImgHeight;    //Դͼ��ĸ߶�
	l32 l32ImgYStride;   //Դͼ���Y����ֵ
	l32 l32ImgUVStride;  //Դͼ���UV����ֵ�������Ĭ��Y����ֵ��һ�룬������Ը���0

	l32 l32YUVType;      //Դ��YUVtype
	l32 l32Interlace;    //Դ��֡������
	l32 l32FilterType;   //�˲���������
	l32 l32Quility;      //�����ȼ���Ŀǰ�˲�����û��ʹ��

    u32 u32Reserved;
}TImageFilterParam;

//ͼ���˲�ģ��״̬�ṹ��
#define TImageFilterStatusParam TImageFilterParam

//ͼ���˲��������
typedef struct
{
	u8 *pu8ImgYAddr;			//Դͼ��Y������ַ
	u8 *pu8ImgUAddr;			//Դͼ��U������ַ,����������ռ䣬�η������Ը���
	u8 *pu8ImgVAddr;			//Դͼ��V������ַ,����������ռ䣬�η������Ը���

	u32 u32Reserved;
}TImageFilterInput;

//ͼ���˲��������
typedef struct
{
	u32 u32Reserved;
}TImageFilterOutput;


//ͼ���񻯲�������ģ��֧��ԭλ��
typedef struct
{
	l32 l32ImgWidth;     //Դͼ��Ŀ��
	l32 l32ImgHeight;    //Դͼ��ĸ߶�

	l32 l32Factor;       //��ʱ��Ȩ��ֵ,��ΧΪ0-255���Ƽ�ֵΪ128

    u32 u32Reserved;
}TImageSharpParam;

//ͼ����ģ��״̬�ṹ��
#define TImageSharpStatusParam TImageSharpParam

//ͼ�������������pu8SrcUAddr��pu8SrcVAddr��l32SrcUVStride������һ��Ϊ������Ϊʱ����buffer
typedef struct
{
	u8 *pu8SrcYAddr;			//Դͼ��Y������ַ
	u8 *pu8SrcUAddr;			//Դͼ��U������ַ�����Ը�ֵΪ0����������Ϊͼ����������
	u8 *pu8SrcVAddr;			//Դͼ��V������ַ�����Ը�ֵΪ0����������Ϊͼ����������

	l32 l32SrcYStride;          //Դͼ���Y����ֵ
	l32 l32SrcUVStride;			//Դͼ���UV����ֵ�����Ը�ֵΪ0����������Ϊͼ����������

	u32 u32Reserved;
}TImageSharpInput;

//ͼ�����������,Ŀ��ͼ����Ժ�Դͼ����ȫһ�£�����Ҫ��һ��
//pu8DstUAddr��pu8DstVAddr��l32DstUVStride������һ��Ϊ������Ϊʱ����buffer
typedef struct
{
	u8 *pu8DstYAddr;			//Ŀ��ͼ���Y������ַ
	u8 *pu8DstUAddr;			//Ŀ��ͼ���U������ַ�����Ը�ֵΪ0����������Ϊͼ����������
	u8 *pu8DstVAddr;			//Ŀ��ͼ���V������ַ�����Ը�ֵΪ0����������Ϊͼ����������

	l32 l32DstYStride;          //Ŀ��ͼ���Y����ֵ
	l32 l32DstUVStride;			//Ŀ��ͼ���UV����ֵ�����Ը�ֵΪ0����������Ϊͼ����������

	u32 u32Reserved;
}TImageSharpOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_FILTER_PUBLIC_H_
