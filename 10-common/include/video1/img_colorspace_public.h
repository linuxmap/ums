/******************************************************************************
ģ����	    ��img_colorspace_public
�ļ���	    ��img_colorspace_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ�������ɫ�ռ�ת�������ṹ��
����		��wgz
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸����� 
2007/09/14		1.0				������                 ����
******************************************************************************/
#ifndef _IMG_COLORSPACE_PUBLIC_H_
#define _IMG_COLORSPACE_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//YUV422�����Ĳ������ýṹ��
typedef struct 
{
    l32 l32SrcWidth;	   //YUV422VGAͼ��Ŀ��
    l32 l32SrcHeight;      //YUV422VGAͼ��ĸ߶�
	l32 l32SrcISInterlace; //YUV422VGAͼ���֡������
    l32 l32DstWidth;       //�������YUV422ͼ��Ŀ��
    l32 l32DstHeight;      //�������YUV422ͼ��ĸ߶�
	l32 l32DstISInterlace; //�������YUV422ͼ���֡������
}TYUV422VGAzoomParam;

//YUV422����ģ��״̬�����ṹ��
#define TImageYUV422VGAzoomStatusParam TYUV422VGAzoomParam
//YUV422����������ṹ��
typedef struct
{
	u8 *pu8SrcImgBuff; //ָ��YUV422ͼ��Ĵ���ռ�
	u8 *pu8DstImgBuff; //ָ��YUV422ͼ��Ĵ���ռ�
}TImageYUV422VGAzoomInput;

//YUV422����������ṹ��
typedef struct
{
	l32 l32DstISInterlace;  //YUV422ͼ���֡������
}TImageYUV422VGAzoomOutput;

//YUV422תΪYUV420�Ĳ������ýṹ��
typedef struct 
{
    l32 l32SrcWidth;	  //YUV422ͼ��Ŀ��
    l32 l32SrcHeight;     //YUV422ͼ��ĸ߶�
	l32 l32SrcISInterlace;  //YUV422ͼ���֡������
    l32 l32DstWidth;      //YUV420ͼ��Ŀ��
    l32 l32DstHeight;     //YUV420ͼ��ĸ߶�
	l32 l32DstISInterlace;  //YUV420ͼ���֡������
}TYUV422ToYUV420Param;

//YUV422תΪYUV420ģ��״̬�����ṹ��
#define TImageYUV422ToYUV420StatusParam TYUV422ToYUV420Param
//YUV422תYUV420����ṹ��
typedef struct
{
	u8 *pu8SrcImgBuff; //ָ��YUV422ͼ��Ĵ���ռ�
	u8 *pu8DstImgBuff; //ָ��YUV420ͼ��Ĵ���ռ�
}TImageYUV422ToYUV420Input;

//YUV422תYUV420����ṹ��
typedef struct
{
	l32 l32DstISInterlace;  //YUV420ͼ���֡������
	l32 l32IntraFrameFlag;  //I֡֡����
    u32 u32Reserved;  //��������
}TImageYUV422ToYUV420Output;

//YUV420תΪYUV422�Ĳ������ýṹ��
typedef struct 
{
    l32 l32SrcWidth;      //YUV420ͼ��Ŀ��
    l32 l32SrcHeight;     //YUV420ͼ��ĸ߶�
	l32 l32SrcISInterlace;  //YUV420ͼ���֡������
    l32 l32DstWidth;      //YUV422ͼ��Ŀ��
    l32 l32DstHeight;     //YUV422ͼ��ĸ߶�
	l32 l32DstISInterlace;  //YUV422ͼ���֡������
}TYUV420ToYUV422Param;
//YUV420תΪYUV422ģ��״̬�����ṹ��
#define TImageYUV420ToYUV422StatusParam TYUV420ToYUV422Param

//YUV420תYUV422����ṹ��
typedef struct
{
	u8 *pu8SrcImgBuff;  //ָ��YUV420ͼ��Ĵ���ռ�
	u8 *pu8DstImgBuff;  //ָ��YUV422ͼ��Ĵ���ռ�
}TImageYUV420ToYUV422Input;

//YUV420תYUV422����ṹ��
typedef struct
{
	l32 l32DstISInterlace;  //YUV422ͼ���֡������	
}TImageYUV420ToYUV422Output;

//YUV420תRGB��չ����
typedef enum
{
    YUV420_TO_RGB_NO_FLIP_IMG = 1,
}TExtendYUV420ToRGBType;

//YUV420תRGB��չ�ṹ��
typedef struct
{
    TExtendYUV420ToRGBType tExtendType; //�ṹ��չ����
    u32 u32IsNoFlipRGB;                 //�Ƿ񲻷�תRGBͼ��(���ﲻ�ܶ���u8 ������androidƽ̨�ϻ����ֽڶ�������)
}TYUV420ToRGBExtend;

// YUV420תRGB�Ĳ������ýṹ��
typedef struct
{
	l32 l32SrcWidth;      //YUV420ͼ��Ŀ��
	l32 l32SrcHeight;     //YUV420ͼ��ĸ߶�
	l32 l32RGBTop;        //RGBͼ����YUV420ͼ���ϵ���ʼy����
	l32 l32RGBLeft;       //RGBͼ����YUV420ͼ���ϵ���ʼx����
	l32 l32WindowWidth;   //RGBͼ�񴰵Ŀ��
	l32 l32WindowHeight;  //RGBͼ�񴰵ĸ߶� 
	u8 u8RGBType;         //RGBͼ�������
}TYUV420ToRGBParam;

//YUV420תΪRGBģ��״̬�����ṹ��
#define TImageYUV420ToRGBStatusParam TYUV420ToRGBParam
//YUV420תRGB����ṹ��
typedef struct
{
	u8 *pu8SrcImgBuff;  //ָ��YUV420ͼ��Ĵ���ռ�
	u8 *pu8DstImgBuff;  //ָ��RGBͼ��Ĵ���ռ�
}TImageYUV420ToRGBInput;

//YUV420תRGB����ṹ��
typedef struct
{
	u32 u32Reserved;  //��������	
}TImageYUV420ToRGBOutput;

//YUV422���Ϊ4��cif��С��YUV420�Ĳ������ýṹ��
typedef struct 
{
    l32 l32SrcWidth;	  //YUV422ͼ��Ŀ��
    l32 l32SrcHeight;     //YUV422ͼ��ĸ߶�
	l32 l32DstWidth1;     //��һ��cifͼ��Ŀ��
    l32 l32DstHeight1;    //��һ��cifͼ��ĸ߶�
	l32 l32DstWidth2;     //�ڶ���cifͼ��Ŀ��
    l32 l32DstHeight2;    //�ڶ���cifͼ��Ŀ��
	l32 l32DstWidth3;     //������cifͼ��Ŀ��
    l32 l32DstHeight3;    //������cifͼ��Ŀ��
	l32 l32DstWidth4;     //���ĸ�cifͼ��Ŀ��
    l32 l32DstHeight4;    //���ĸ�cifͼ��Ŀ��
}TYUV422ToYUV420D1To4xCifParam;

//YUV422���Ϊ4��cif��С��YUV420ģ��״̬�����ṹ��
#define TImageYUV422ToYUV420D1To4xCifStatusParam TYUV422ToYUV420D1To4xCifParam
//YUV422D1���Ϊ4��cifYUV420����ṹ��
typedef struct
{
	u8 *pu8SrcImgBuff;	  //ָ��YUV422ͼ��Ĵ���ռ�
	u8 *pu8DstImgBuff[4]; //ָ��YUV420ͼ��Ĵ���ռ�
}TImageD1SplitInput;

//YUV422D1���Ϊ4��cifYUV420����ṹ��
typedef struct
{
	u32 u32Reserved;  //��������	
}TImageD1SplitOutput;

//BMPתΪYUV������Alphaͨ�������ṹ��
typedef struct  
{
	l32 l32YUVType;    //YUV����
	u8 u8BackR;        //������ɫ��R����
	u8 u8BackG;        //������ɫ��G����
	u8 u8BackB;        //������ɫ��B����
	u8 u8Transparency; //͸����(0��ʾȫ͸��,255��ʾ��͸��)
}TImageBMPToYUVAlphaParam;

//BMPתΪYUV������Alphaͨ����״̬�����ṹ��
#define TImageBMPToYUVAlphaStatusParam TImageBMPToYUVAlphaParam

//BMPתΪYUV������Alphaͨ����������ṹ��
typedef struct  
{
	u8 *pu8InBMP;     //ָ������BMPͼ��ָ��
    u8 *pu8OutYUV;    //ָ�����ͼ�����ʼ��ַָ��
	u8 *pu8OutAlpha;  //ָ�����Alphaϵ������ʼ��ַָ��
	u8 *pu8OutBeta;   //ָ�����Betaϵ������ʼ��ַָ��
}TImageBMPToYUVAlphaInput;

//BMPתΪYUV������Alphaͨ����������ṹ��
typedef struct  
{
	l32 l32Height;     //YUVͼ��ĸ߶�
	l32 l32Width;      //YUVͼ��Ŀ��
	l32 l32YUVType;    //YUVͼ������
	u8 u8Transparency; //͸����(0��ʾȫ͸��,255��ʾ��͸��)
}TImageBMPToYUVAlphaOutput;

//GM8180��YUV420��ת�Ĳ����ṹ��
typedef struct
{
    l32 l32Width;         //Դͼ��Ŀ�
    l32 l32Height;        //Դͼ��ĸ�
    l32 l32Left;          //Ҫת���Ĳ���ͼ����Դͼ���е�X����
    l32 l32Top;           //Ҫת���Ĳ���ͼ����Դͼ���е�Y����
    l32 l32BlockWidth;    //Ҫת���Ĳ���ͼ����
    l32 l32BlockHeight;   //Ҫת���Ĳ���ͼ��߶�
    l32 l32ImageType;       //����ͼ�������(��ΪGM8180_YUV420���ΪYUV420, ��ΪYUV420���ΪGM8180_YUV420)
} TImgGM8180ToYUV420Param;

//GM8180��YUV420��ת��״̬�����ṹ��
#define TImageGM8180ToYUV420StatusParam TImgGM8180ToYUV420Param

//GM8180��YUV420��ת����������ṹ��
typedef struct  
{
    u8 *pu8Input;     //ָ������ͼ���ָ��
    u8 *pu8Output;    //ָ�����ͼ���ָ��
}TImageGM8180ToYUV420Input;

//GM8180��YUV420��ת����������ṹ��
typedef struct  
{
    u32 u32Reserved;  //��������
}TImageGM8180ToYUV420Output;

#ifdef __cplusplus
}
#endif

#endif 
