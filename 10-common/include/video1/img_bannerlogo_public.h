/******************************************************************************
ģ����	    ��img_bannerlogo_public
�ļ���	    ��img_bannerlogo_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ�������,ͼ��ṹ��
����		��zwenyi
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2007/09/14		1.0				zwenyi                  ����
******************************************************************************/
#ifndef _IMG_BANNERLOGO_PUBLIC_H_
#define _IMG_BANNERLOGO_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//ͼ�����ֵ���Ϣ�ṹ��
typedef struct  
{
	l32 l32FontHeight;  //�ֵĸ߶�
	l32 l32WidthBufLen; //��¼�ֵĿ�ȵĻ����С
	u8 *pu8FontWidth;   //ÿ���ֵĿ��,������,���ϵ��µ�˳��
}TFontInfo;

//ͼ����Ϣ�Ľṹ��
typedef struct 
{
	u8 *pu8YUV;                //ǰ��ͼ������ָ���ַ(ͼ���ʽΪYUV422ʱ,
	                           //����Ŀռ��СΪl32Width*l32Height*2,ͼ���ʽΪYUV420ʱ,����Ŀռ��СΪl32Width*l32Height*3/2)
	u8 *pu8Alpha;              //ǰ��ͼ���alphaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	u8 *pu8Beta;               //��Ӧ����ͼ���betaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	u8 u8Transparency;         //ͼ��͸��ϵ��
	l32 l32Width;              //ǰ��ͼ��Ŀ��
	l32 l32Height;             //ǰ��ͼ��ĸ߶�	
	l32 l32YUVType;            //ͼ��ͼ���ʽ(YUV422����YUV420)
	l32 l32Top;                //ǰ��ͼ��λ��ƫ��
	l32	l32Left;               //ǰ��ͼ��λ��ƫ��
	l32 l32TopCutLine;         //ǰ��ͼ���ϱ߲�ȥ������
	l32 l32BottomCutLine;      //ǰ��ͼ���±߲�ȥ������
	l32 l32LeftCutLine;        //ǰ��ͼ����߲�ȥ������
	l32 l32RightCutLine;       //ǰ��ͼ���ұ߲�ȥ������
	l32 l32IsInterlace;        //ǰ��ͼ�������(֡��ʽ���߳���ʽ)
	l32 l32LogoRefPicWidth;    //ͼ�����ɵĲο�ͼ��߶ȣ�������8�ı�������ֵ���ڼ���ͼ��������ű�����������ͼ�겻��Ҫ���ţ���ֵ���ڱ���ͼ����
	l32 l32LogoRefPicHeight;   //ͼ�����ɵĲο�ͼ���ȣ�������4�ı�������ֵ���ڼ���ͼ���������ű�����������ͼ�겻��Ҫ���ţ���ֵ���ڱ���ͼ��߶�	
	l32 l32IsAdaptiveColor;    //�Ƿ���ݵ�ɫ�ı�ͼ�����ɫ,1��ʾ��Ҫ�ı�ͼ�����ɫ,������ʾ����Ҫ�ı�ͼ�����ɫ
    TFontInfo tFontInfo;       //��¼ͼ�����ֵ���Ϣ�ṹ��
} TLogoInfo;

//ͼ����Ϣ�Ľṹ��
typedef struct tLogo
{
	u8 *pu8YUV;                //ǰ��ͼ������ָ���ַ(ͼ���ʽΪYUV422ʱ,����Ŀռ��СΪl32Width*l32Height*2,ͼ���ʽΪYUV420ʱ,����Ŀռ��СΪl32Width*l32Height*3/2)
	u8 *pu8Alpha;     		   //ǰ��ͼ���alphaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	u8 *pu8Beta;			   //��Ӧ����ͼ���betaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	u32	u32Width;              //ͼ��ͼ��Ŀ��, ���뱣֤����ֵ�ڳ��Ա���ͼ�����ٳ���u32LogoRefPicWidth��Ҫ��8�ı���
	u32	u32Height;             //ͼ��ͼ��ĸ߶�, ���뱣֤����ֵ�ڳ��Ա���ͼ��߶��ٳ���u32LogoRefPicHeight��Ҫ��4�ı���
	l32	l32YUVType;            //ͼ��ͼ���ʽ(YUV422����YUV420)
	l32	l32IsInterlace;        //ǰ��ͼ�������(֡��ʽ���߳���ʽ)
	u32 u32LogoRefPicWidth;    //ͼ����Ӳο�ͼ��Ŀ�ȣ�������8�ı�������ֵ���ڼ���ͼ��������ű�����������ͼ�겻��Ҫ���ţ���ֵ���ڱ���ͼ����
	u32 u32LogoRefPicHeight;   //ͼ����Ӳο�ͼ��ĸ߶ȣ�������4�ı�������ֵ���ڼ���ͼ���������ű�����������ͼ�겻��Ҫ���ţ���ֵ���ڱ���ͼ��߶�	
	u8 u8Transparency;         //ͼ��͸��ϵ��
	l32 l32Top;				   //ͼ��ͼ��ֱλ��ƫ�ƣ��������ʾ���ڣ�, ���뱣֤����ֵ�ڳ��Ա���ͼ��߶��ٳ���u32LogoRefPicHeight��Ҫ��2�ı����������ǳ�ͼ��ʱΪ4�ı���
	l32	l32Left;        	   //ͼ��ͼ��ˮƽλ��ƫ�ƣ��������ʾ���ڣ�, ���뱣֤����ֵ�ڳ��Ա���ͼ�����ٳ���u32LogoRefPicWidth��Ҫ��4�ı���
	s16	s16StepH;			   //ͼ��ˮƽ�˶��ٶȣ�ÿ֡�ƶ��������������Ҹ�����, ���뱣֤����ֵ�ڳ��Ա���ͼ�����ٳ���u32LogoRefPicWidth��Ҫ��ż��
	s16	s16StepV;			   //ͼ�괹ֱ�˶��ٶȣ�ÿ֡�ƶ��������������ϸ����£�, ���뱣֤����ֵ�ڳ��Ա���ͼ��߶��ٳ���u32LogoRefPicHeight��Ҫ��ż��,���ڳ�ͼ����Ҫ��4�ı���
	l32	l32ShowTimes;		   //ͼ����ʾ����������һֱ��ʾ��0������ʾ������ͼ�����ٶ�ʱΪѭ����ʾ������ͼ�����ٶ�ʱ���ô�����
	l32	l32PauseIntervalH;	   //ͼ��ˮƽ�˶���ͣ�����������������������ͣ�� ����������ͣ��
	l32	l32PauseIntervalV;	   //ͼ�괹ֱ�˶���ͣ�����������������������ͣ�� ����������ͣ��
	l32	l32PauseTime;		   //ͼ����ͣʱ�䣨���ô�����
	l32	l32WindowTop;		   //��ʾ���ڴ�ֱλ��, ���뱣֤����ֵ�ڳ��Ա���ͼ��߶��ٳ���u32LogoRefPicHeight��Ҫ��ż��
	l32	l32WindowLeft;		   //��ʾ����ˮƽλ��
	l32	l32WindowWidth;	       //��ʾ���ڿ��
	l32	l32WindowHeight;	   //��ʾ���ڸ߶�
	l32 l32IsAdaptiveColor;    //�Ƿ���ݵ�ɫ�ı�ͼ�����ɫ,1��ʾ��Ҫ�ı�ͼ�����ɫ,������ʾ����Ҫ�ı�ͼ�����ɫ
    TFontInfo tFontInfo;       //��¼ͼ�����ֵ���Ϣ�ṹ��
	u32	u32Reserved;		   //��������
}TLogo;			//ͼ��

//ͼ����Ϣʹ�ܽṹ��
typedef struct 
{
    u32 u32LogoReservedType; //TLogo�ṹ�屣���ֶ���չ����
    l32 l32LogoEnable;       //Logo�����Ƿ�ʹ�ܣ�����bannerlogoģ���У�
    l32 l32LogoShow;         //Logo�Ƿ���ʾ������bannerlogoģ���У�
    u32 u32Reserved;         //��������
}TLogoEnableParam;	

//�����Ϣ�Ľṹ��
typedef struct tBanner
{
	l32		l32Width;			//������
	l32		l32Height;			//����߶�
	l32		l32Top;				//������ϽǴ�ֱ����
	l32		l32Left;			//������Ͻ�ˮƽ����
	l32     l32BannerRefPicWidth;    //�����Ӳο�ͼ��Ŀ��
	l32     l32BannerRefPicHeight;   //�����Ӳο�ͼ��ĸ߶�
	u8		u8R;				//�����ɫR
	u8		u8G;				//�����ɫG
	u8		u8B;				//�����ɫB
	u8      u8Transparency;     //�����͸��ϵ��(0��ʾȫ͸����255��ʾ��͸����1~254��ʾ����͸��)	
}TBanner;		//���

//����ͼ����Ϣ�Ľṹ��
typedef struct 
{
	l32  l32Width;        //ͼ��Ŀ��
	l32  l32Height;       //ͼ��ĸ߶�
	l32	 l32IsInterlace;  //ͼ�������(֡��ʽ���߳���ʽ)
    l32 l32IsInterleaved;   //����ɨ�軹�Ǹ���ɨ��
	l32  l32YUVType;      //ͼ��ͼ���ʽ(YUV422����YUV420)	
}TBackgroundImage;

//ͼ�����
typedef struct 
{
    TLogoInfo tLogo;           //ͼ�����
	TBackgroundImage tImage;   //����ͼ�����
} TImageLogoParam;

//ͼ��ģ��״̬��ѯ�ṹ��
#define TImageLogoStatusParam TImageLogoParam

//�������
typedef struct 
{
	TBanner tBanner;           //�������
    TBackgroundImage tImage;   //����ͼ�����
} TImageBannerParam;

//���ģ��״̬��ѯ�ṹ��
#define TImageBannerStatusParam TImageBannerParam

//���ͼ���������
typedef struct
{
	TLogo atLogo[MAX_LOGO_NUM];                 //ͼ������ṹ����
    TBanner atBanner[MAX_LOGO_NUM];             //��������ṹ����
	TBackgroundImage tImage;                    //����ͼ������ṹ
	l32 l32LogoNum;                             //ͼ�����
	l32 l32BannerNum;                           //�������
} TImageBannerLogoParam;

//�������ģ��״̬��ѯ�ṹ��
#define TImageBannerLogoStatusParam TImageBannerLogoParam

typedef enum 
{ 
    ZOOM_BY_REF_IMG = 0,                      //LOGO���ο�ͼ���뱳��ͼ����Ӧ��߱�����
    ZOOM_BY_SELF                              //LOGO�����ţ�Ŀ������TLogoZoomInfo��
} ELogoZoomMode; 

typedef struct 
{ 
    l32 l32DstLogoWidth;                      //�������Logo��� 
    l32 l32DstLogoHeight;                     //�������Logo�߶� 
    u32 u32Reserved;                          //�������� 
} TLogoZoomInfo; 

typedef struct 
{ 
    TLogoInfo tLogo[MAX_LOGO_NUM];               //ͼ������ṹ���� 
    TBackgroundImage tImage;                     //����ͼ������ṹ 
    l32 l32LogoNum;                              //ͼ����� 
    ELogoZoomMode eLogoZoomMode;                 //Logo����ģʽ(ELogoZoomMode) 
    TLogoZoomInfo atLogoZoomInfo[MAX_LOGO_NUM];  //Logo���Ų����ṹ���� 
    u32 u32Reserved;                             //�������� 
} TImageCommonAddLogoParam; 

#define TImageGM8180AddLogoParam TImageCommonAddLogoParam

//ͼ��ģ��״̬��ѯ�ṹ��
#define TImageGM8180AddLogoStatusParam TImageCommonAddLogoParam

//ͼ������ṹ
typedef struct
{
	u8 *pu8YUV;	      //�������ͼ������
} TImageLogoInput;

//ͼ������ṹ
typedef struct
{
	u32	u32Reserved;  //��������
} TImageLogoOutput;

//�������ṹ
typedef struct
{
	u8 *pu8YUV;	      //�������ͼ������
} TImageBannerInput;

//�������ṹ
typedef struct
{
	u32	u32Reserved;  //��������
} TImageBannerOutput;

//�������ͼ������ṹ
typedef struct
{
	u8 *pu8YUV;	      //�������ͼ������
} TImageBannerLogoInput;

//�������ͼ������ṹ
typedef struct
{
	u32	u32Reserved;  //��������
} TImageBannerLogoOutput;

//GM8180�ϼӶ��LOGO������ṹ
typedef struct
{
    u8 *pu8YUV;	      //�������ͼ������
} TImageCommonAddLogoInput;

#define TImageGM8180AddLogoInput TImageCommonAddLogoInput

//GM8180�ϼӶ��LOGO������ṹ
typedef struct
{
    u32	u32Reserved;  //��������
} TImageCommonAddLogoOutput;

#define TImageGM8180AddLogoOutput TImageCommonAddLogoOutput

#ifdef __cplusplus
}
#endif

#endif //_IMG_BANNERLOGO_PUBLIC_H_
