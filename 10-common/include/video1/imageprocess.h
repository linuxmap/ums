/***************************************************************************************
�ļ���	    �� ImageProcess.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ��ṩͼ����Ķ���ӿ�.

����		��������
�汾		��2005.03.10
-------------------------------------------------------------------------------
��  ��		�汾		�޸���		�߶���    �޸�����
03/10/2005	1.0         ������                 ����
06/20/2005	1.1	 	zhaobo							���Linuxƽ̨���������
***************************************************************************************/
#ifndef  _IMAGEPROCESS_H_
#define  _IMAGEPROCESS_H_

#include "algorithmtype.h"
#include "videocommondefines.h"

#ifdef __cplusplus
extern "C"
{
#endif 

#define LOGOADAPTIVECOLOR 0x01


//ͼ����Ϣ�Ľṹ��
typedef struct 
{
	u8   *pu8Y;           //ͼ���Y����
	u8   *pu8U;           //ͼ���U����
	u8   *pu8V;           //ͼ���V����(U��V�������Բ���ֵ��ֱ�Ӹ���NULL����ע�������߱���ͬʱ�����)
	l32  l32Width;        //ͼ��Ŀ��
	l32  l32Height;       //ͼ��ĸ߶�
	l32  l32YStride;      //ͼ���Y��������
	l32  l32UVStride;     //ͼ���UV��������
	l32	 l32ImageType;    //ͼ�������(֡��ʽ���߳���ʽ)
	l32  l32YUVType;      //ͼ��ͼ���ʽ(YUV422����YUV420)

}TImageInfo;

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
	u8   *pu8YUV;               //ǰ��ͼ������ָ���ַ(ͼ���ʽΪYUV422ʱ,
	                            //����Ŀռ��СΪl32Width*l32Height*2,ͼ���ʽΪYUV420ʱ,����Ŀռ��СΪl32Width*l32Height*3/2)
	u8   *pu8Alpha;             //ǰ��ͼ���alphaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	u8   *pu8Beta;              //��Ӧ����ͼ���betaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	u8   u8FgTransparency;      //ǰ��ͼ��͸��ϵ��
	u8   u8BgTransparency;      //����ͼ��͸��ϵ��
 	l32  l32Width;              //ǰ��ͼ��Ŀ��
	l32  l32Height;             //ǰ��ͼ��ĸ߶�	
	l32  l32YUVType;            //ͼ��ͼ���ʽ(YUV422����YUV420)
	l32  l32Top,l32Left;        //ǰ��ͼ��λ��ƫ��
	l32  l32TopCutLine;         //ǰ��ͼ���ϱ߲�ȥ������
	l32  l32BottomCutLine;      //ǰ��ͼ���±߲�ȥ������
	l32  l32LeftCutLine;        //ǰ��ͼ����߲�ȥ������
	l32  l32RightCutLine;       //ǰ��ͼ���ұ߲�ȥ������
	l32  l32ImageType;          //ǰ��ͼ�������(֡��ʽ���߳���ʽ)
	l32  l32LogoRefPicWidth;    //ͼ�����ɵĲο�ͼ��߶�
	l32  l32LogoRefPicHeight;   //ͼ�����ɵĲο�ͼ����
    l32  l32IsAdaptiveColor;    //�Ƿ���ݵ�ɫ�ı�ͼ�����ɫ,1��ʾ��Ҫ�ı�ͼ�����ɫ,������ʾ����Ҫ�ı�ͼ�����ɫ
    TFontInfo tFontInfo;        //��¼ͼ�����ֵ���Ϣ�ṹ��
} TLogoInfo;

//YUV422תΪYUV420������ʱ���˲��Ĳ�������
typedef struct 
{
    l32 l32SrcWidth;    //YUV422ͼ��Ŀ��
    l32 l32SrcHeight;   //YUV422ͼ��ĸ߶�
    l32 l32SrcStride;   //YUV422ͼ��Ĳ���
    l32 l32DstWidth;    //YUV420ͼ��Ŀ��
    l32 l32DstHeight;   //YUV420ͼ��ĸ߶�
    l32 l32DstYStride;  //YUV420Y�����Ĳ���
    l32 l32FilterType;  //�˲������ͣ����ݲ�ͬ�ı�����ѡ��ͬ�˲���ʽ���������õ���ֵ
} TYUV422ToYUV420Param;

//Mapƽ̨��Windowsƽ̨��Linuxƽ̨�¹��õĺ�������

/*===========================================================================
������	    : GetImageProcessVersion;
����		�����ذ汾��Ϣ
�㷨ʵ��	��
����˵��    ��
�汾��Ϣ��ָ�� : void *pVer
               l32 l32BufLen  δ��
			   l32 *pl32VerLen  �汾��Ϣ�ĳ���
����ֵ˵��  ����
����˵��    ��
=============================================================================*/
void  GetImageProcessVersion(void *pVer, l32 l32BufLen, l32 *pl32VerLen);

/*====================================================================
������      ��ConvertBMPToYUVAndAlpha
����        ����ͼ��RGBֵ��ΪYUVֵ��ͬʱ����ǰ��ͼ���alphaͨ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵����
	          u8  *pu8Bmp         RGB�����ָ��
              TLogoInfo *ptLogo   ������ǰ��ͼ����Ϣ�Ľṹ��ָ��
			  u8  u8BackR         ������ɫ��R����
			  u8  u8BackG         ������ɫ��G����
			  u8  u8BackB         ������ɫ��B����
			  u8  u8FgTransparency  ǰ��͸����(255��ʾ��͸��,0��ʾȫ͸��,1~254��ʾ����͸��)
����ֵ˵��  ���ɹ�,VIDEOSUCCESS ;ʧ�ܣ�VIDEOFAILURE
�ر�˵�� : ��ȡBMPͼ�������ʱ, Ϊ�����ݵĶ���, Ҫ��BMPͼ����ļ�ͷǰ��
           �ճ�2��byte; ��puBmpָ��ָ���ǰ2��byteΪ��,Ȼ���ٶ�ȡʵ�ʵ�BMPͼ��
		   ������
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/11/24    1.0         HuangKui		����
05/04/07    1.1         ZouWenyi      ����淶��
====================================================================*/
l32 ConvertBMPToYUVAndAlpha(u8 *pu8Bmp, TLogoInfo *ptLogo, u8 u8BackR, u8 u8BackG, u8 u8BackB, u8 u8FgTransparency);

/*====================================================================
������      �� CalculateSum88
����    	�� ��Y����8*8�����ĺ�,��UV����4*4�����ĺ�
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵����
              u8  *pu8YUV : ָ��yuvͼ�����ݵ�ָ��
			  l32  l32Height : ͼ��ĸ߶�
			  l32  l32Width  : ͼ��Ŀ��
			  l32  l32YStride : Y�����Ĳ���
			  l32  l32UVStride : UV�����Ĳ���
			  u16 *pu16Sum : �������Ľ��
              
����ֵ˵��  ���ɹ�����VIDEOSUCCESS; ʧ�ܷ���VIDEOFAILURE
----------------------------------------------------------------------
  �޸ļ�¼    ��
  ��  ��      �汾        �޸���        �޸�����
  05/03/07             ZouWenyi	        ����
====================================================================*/
l32 CalculateSum88(u8 *pu8YUV, l32 l32Height, l32 l32Width, l32 l32YStride, l32 l32UVStride, u16 *pu16Sum);

/*====================================================================
������      ��FrameGenerator420
����        ������һ֡ͼ�񣨸�ʽΪYUV420��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo *ptImage : ָ������ͼ��Ľṹ��ָ��
              l32    l32ImageForm : ����ͼ�����״(ͼ����ѡ�����£�
                   GLOBOSITY��ʾ������״��BLACKWHITEBAR��ʾ��ͬ����ڰ��� ��
                   WHITETOBLACK��ʾ�ɰ��𽥼ӵ��ڣ�RAINBOW��ʾ�߲�ɫ)

����ֵ˵��  ���ɹ�����VIDEOSUCCESS; ʧ�ܷ���VIDEOFAILURE
����˵�� : Ŀǰֻ֧������720*576��420����ʽͼ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
05/11/2004    1.0        ZouWenYi         ����    
05/18/2005    1.1        ZouWenyi       ����淶��
====================================================================*/	
l32 FrameGenerator420(TImageInfo *ptImage, l32 l32ImageForm);

/*====================================================================
������      :  copy_image
����	    :  ����һ֡ͼ��
�㷨ʵ��    ;  ����DS��CPUͬʱ��������(ֻ�ṩMAP�汾)
����ȫ�ֱ����� ��
�������˵���� 	u8 *pu8Dst, Ŀ�ĵ�ַ
				u8 *pu8Src, Դ��ַ
				l32 l32Width, ���
				l32 l32Height �߶�
����ֵ˵��  �� ��
----------------------------------------------------------------------
  �޸ļ�¼    ��
  ��  ��		   �汾		�޸���		�߶���      �޸�����
  07/07/2006       1.0      �ƿ�                    ���� 
====================================================================*/
void copy_image(u8 *pu8Dst, u8 *pu8Src, l32 l32Width, l32 l32Height);

/*====================================================================
������      :  GenerateYUVtoRGBTables
����	    :  ��ʼ��YUV��RGBװ����ɫ�ʱ��
�㷨ʵ��    ;  
����ȫ�ֱ����� ��
�������˵���� ��
����ֵ˵��  �� ��
----------------------------------------------------------------------
  �޸ļ�¼    ��
  ��  ��		   �汾		�޸���		�߶���      �޸�����
  07/10/2006       1.0       �Բ�                     ���� 
====================================================================*/
void GenerateYUVtoRGBTables(void);


#if defined MAP_CODE  //MAP ��������
/*====================================================================
������      :	D1YUV422FieldPToN_map
����        :	��4cif�ĳ���ʽYUV422ͼ����P��ת��ΪN��
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	�Ѽӵĺڱ߲�ȥ
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/09/29    1.0         zhaobo			����
====================================================================*/
l32 D1YUV422FieldPToN_map(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  D1YUV422FieldPToN  D1YUV422FieldPToN_map

/*====================================================================
������      :	D1YUV422FieldNToP_map
����        :	��4cif�ĳ���ʽYUV422ͼ����N��ת��ΪP��
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	���¼Ӻڱ�
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/09/29    1.0         zhaobo			����
====================================================================*/
l32 D1YUV422FieldNToP_map(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  D1YUV422FieldNToP  D1YUV422FieldNToP_map

/*====================================================================
������      :	D1YUV422FieldNToPOneBuffer_map
����        :	��4cif�ĳ���ʽYUV422ͼ����N��ת��ΪP��,������ͬһ��buffer
				����
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	���¼Ӻڱ�
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/10/10    1.0         zhaobo			����
====================================================================*/
l32 D1YUV422FieldNToPOneBuffer_map(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define D1YUV422FieldNToPOneBuffer D1YUV422FieldNToPOneBuffer_map

/*====================================================================
������      :	D1YUV420FieldPToNOneBuffer_map
����        :	��4cif�ĳ���ʽYUV420ͼ����P��ת��ΪN��, ��һ��buffer
				����
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	�Ѽӵĺڱ߲�ȥ
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/10/10    1.0         zhaobo			����
====================================================================*/
l32 D1YUV420FieldPToNOneBuffer_map(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define D1YUV420FieldPToNOneBuffer D1YUV420FieldPToNOneBuffer_map

/*====================================================================
������      :	D1YUV420FieldNToPTwoBuffer_map
����        :	��4cif�ĳ���ʽYUV420ͼ����N��ת��ΪP��
				����
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	�Ӻڱ�
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
10/27/06    1.0         zhaobo			����
====================================================================*/
l32 D1YUV420FieldNToPTwoBuffer_map(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define D1YUV420FieldNToPTwoBuffer D1YUV420FieldNToPTwoBuffer_map
/*====================================================================
������      ��ProduceMosaic
����        ����ͼ���������
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����  TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
                l32 l32Left            : ����������������
                l32 l32Top             : ����������������
                l32 l32WindowWidth     : ������������
                l32 l32WindowHeight    : ����������߶�
                l32 l32Granularity     : ����������
����ֵ˵��  ���ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/11/24    1.0         HuangKui		����
06/06/22    1.5         zhaobo        �淶�����޸�
06/09/07    2.0         zhaobo        MAP�Ż�
====================================================================*/
l32 ProduceMosaic_map(TImageInfo *ptInImage, TImageInfo *ptOutImage, 
				      l32 l32Left, l32 l32Top, l32 l32WindowWidth, l32 l32WindowHeight, l32 l32Granularity);
#define  ProduceMosaic  ProduceMosaic_map
/*====================================================================
������      ��MergePictureInit_map
����        ��ͼ��ϳɳ�ʼ��
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����void **ppvHandle : ���
			  
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
�ر�˵�� :  ֻ֧��YUV420��ͼ��ϲ�
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾         �޸���        �޸�����
11/24/2003  1.0         HuangKui	     ����
04/26/2005  1.1         ZouWenyi       ����淶��         
08/10/2006  2.0            zb            ʹ��DS  
====================================================================*/
l32 MergePictureInit_map(void **ppvHandle);
#define  MergePictureInit  MergePictureInit_map
/*====================================================================
������      �� MergePicture
����        ����Сͼ�񸲸ǵ���ͼ���ָ��λ��
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����void *pvHandle ���
			  TImageInfo *ptBackgroundImage   ָ�򱳾�ͼ���ָ��
              TLogoInfo *ptLogo  ָ�������ǰ��ͼ����Ϣ�Ľṹ��ָ��
			    (Сͼ������ݷ���ptLogo��pu8YUV��Ա����,��Ҫ����ptLogo��
				������Ա����:l32Height(Сͼ��ĸ߶�), l32Width(Сͼ��Ŀ��), 
				l32Left(Сͼ���ڴ�ͼ����ˮƽ����ƫ�ƵĴ�С), l32Top(Сͼ����
				��ͼ���д�ֱ����ƫ�ƵĴ�С), l32ImageType(֡��ʽ���߳���ʽ),
				l32TopCutLine(Сͼ���ϱ߲�ȥ������),l32BottomCutLine(Сͼ����
				�߲�ȥ������), l32LeftCutLine(Сͼ����߲�ȥ������), l32RightCutLine
				(Сͼ���ұ߲�ȥ������))
			  
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
�ر�˵�� :  ֻ֧��YUV420��ͼ��ϲ�
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾         �޸���        �޸�����
11/24/2003  1.0         HuangKui	     ����
04/26/2005  1.1         ZouWenyi       ����淶��         
08/10/2006  2.0            zb            ʹ��DS  
====================================================================*/
l32 MergePicture_map(void *pvHandle, TImageInfo *ptBackgroundImage, TLogoInfo *ptLogo);

#define  MergePicture  MergePicture_map
/*====================================================================
������      �� MergePictureClose
����        �� ͼ��ϳɹر�
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����void *pvHandle ���			  
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
�ر�˵�� :  ֻ֧��YUV420��ͼ��ϲ�
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾         �޸���        �޸�����
11/24/2003  1.0         HuangKui	     ����
04/26/2005  1.1         ZouWenyi       ����淶��         
08/10/2006  2.0            zb            ʹ��DS  
====================================================================*/
l32 MergePictureClose_map(void *pvHandle);

#define  MergePictureClose  MergePictureClose_map
/*====================================================================
������      :	ImageSizeChange_map
����	    :	����˫���Բ�ֵ�ķ�����Դͼ�����ű�ͼ��
�㷨ʵ��    :	
����ȫ�ֱ���:	��
�������˵��:	TImageInfo *ptInImage : �任ǰ��ͼ��ָ��
				TImageInfo *ptOutImage : �任���ͼ��ָ��
����ֵ˵��  :	��
----------------------------------------------------------------------
�޸ļ�¼:    
��  ��		   �汾		�޸���		�߶���      �޸�����
03/29/2006      1.0      �Բ�                    ���� 
====================================================================*/
l32 ImageSizeChange_map(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  ImageSizeChange  ImageSizeChange_map

/*====================================================================
������      �� DrawBanner_map
����        ����ͼ������Ӻ��(�����ο�����Ϊָ������ɫ)
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo  *ptImage   : ָ��ͼ��ṹ���ָ��
		      TBanner *ptBanner      : ָ�����ṹ��ָ��

����ֵ˵��  ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE  
�ر�˵�� : ͼ�������ָ���ͼ�����е�Y����            
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
01/16/2006    1.0        ZouWenyi        ����
====================================================================*/
l32 DrawBanner_map(TImageInfo *ptImage, TBanner *ptBanner);

#define  DrawBanner DrawBanner_map


/*====================================================================
������      ��  YUV422ToYUV420AndTemporalFilterInit_map
����        ��ͼ��YUV422ת��ΪYUV420������ʱ���˲��ĳ�ʼ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void **ppvHandle    : ָ��ͼ��ǰ��������ָ��
              ptYUV422To420Param  : YUV422תΪYUV420ͼ��Ĳ�������
			               
����ֵ˵��  ���ɹ�����VIDEOSUCCESSFUL, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
  ��  ��	  �� ��		 �޸���		�߶���      �޸�����
2006/04/13	   1.0       ������                   ����
====================================================================*/
l32  YUV422ToYUV420AndTemporalFilterInit_map(void **ppvHandle, TYUV422ToYUV420Param *ptYUV422To420Param);


#define  YUV422ToYUV420AndTemporalFilterInit YUV422ToYUV420AndTemporalFilterInit_map

/*====================================================================
������      �� YUV422ToYUV420AndTemporalFilter_map
����        ��ͼ��YUV422ת��ΪYUV420�Ĵ���
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              u8   *pu8Src     : ָ��Դͼ�����ݵ�ָ��
			  u8   *pu8Dst     : ָ��Ŀ��ͼ�����ݵ�ָ��
			  
����ֵ˵��  ���ɹ����� VIDEOSUCCESSFUL, ���󷵻�VIDEOFAILURE
�������ر�˵����ֻ֧�ֱַ���720*576��YUV422ת���ֱ���720*576,352*576, 352*288��YUV420ͼ��
----------------------------------------------------------------------
�޸ļ�¼    ��
   ��  ��	  �� ��		 �޸���		�߶���      �޸�����
2006/04/14	   1.0       ������                   ����
====================================================================*/
l32 YUV422ToYUV420AndTemporalFilter_map(void *pvHandle, u8 *pu8Src, u8 *pu8Dst);

#define  YUV422ToYUV420AndTemporalFilter  YUV422ToYUV420AndTemporalFilter_map

/*====================================================================
������      �� YUV422ToYUV420AndTemporalFilterClose_map
����        ���ͷ�ǰ����ľ����DS
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle  : ͼ��YUV422תΪYUV420�ľ��
             
����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
  ��  ��	  �� ��		 �޸���		�߶���      �޸�����
2006/04/13	   1.0       ������                   ����
====================================================================*/	
l32 YUV422ToYUV420AndTemporalFilterClose_map(void *pvHandle);

#define  YUV422ToYUV420AndTemporalFilterClose YUV422ToYUV420AndTemporalFilterClose_map


/*====================================================================
������      �� YUV422ToYUV420AndTemporalFilterSetParam_map
����        ��ͼ��ǰ����Ĳ�������
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle      : ָ��ͼ��ǰ��������ָ��
              ptYUV422To420Param  : YUV422תΪYUV420ͼ��Ĳ�������
             
����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
  ��  ��	  �� ��		 �޸���		�߶���      �޸�����
2006/04/13	   1.0       ������                   ����
====================================================================*/
l32 YUV422ToYUV420AndTemporalFilterSetParam_map(void *pvHandle, TYUV422ToYUV420Param *ptYUV422To420Param);

#define  YUV422ToYUV420AndTemporalFilterSetParam YUV422ToYUV420AndTemporalFilterSetParam_map

/*====================================================================
������      �� YUV422ToYUV420Init_map
����        ��ͼ��YUV422ת��ΪYUV420�ĳ�ʼ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void **ppvHandle   : ָ��ͼ��ǰ��������ָ��
              l32 l32SrcWidth    : Դͼ��Ŀ��
			  l32 l32SrcHeight   : Դͼ��ĸ߶�
			  l32 l32SrcStride   : Դͼ��Ĳ���
			  l32 l32DstWidth    : Ŀ��ͼ��Ŀ��
			  l32 l32DstHeight   : Ŀ��ͼ��ĸ߶�
			  l32 l32DstStride   : Ŀ��ͼ��Ĳ���
             
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/04/13    1.0        ZouWenYi        ����
====================================================================*/
l32 YUV422ToYUV420Init_map(void **ppvHandle, l32 l32SrcWidth, l32 l32SrcHeight, l32 l32SrcStride,
				   l32 l32DstWidth, l32 l32DstHeight, l32 l32DstStride);

/*====================================================================
������      �� YUV422ToYUV420_map
����        ��ͼ��YUV422ת��ΪYUV420�Ĵ���
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              u8   *pu8Src     : ָ��Դͼ�����ݵ�ָ��
			  u8   *pu8Dst     : ָ��Ŀ��ͼ�����ݵ�ָ��
			  u16  *pu16Sum8x8 : ָ��Y����8*8�������֮��,UV����4*4������֮�͵�ָ��,
			                     ����ָ��Ϊ��ʱ,��ʾ������8*8�������֮��			  
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
�������ر�˵����ֻ֧�ֱַ���720*576��YUV422ת���ֱ���720*576,352*576, 352*288��YUV420ͼ��
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/04/13    1.0        ZouWenYi         ����
====================================================================*/
l32 YUV422ToYUV420_map(void *pvHandle, u8 *pu8Src, u8 *pu8Dst, u16 *pu16Sum8x8);

/*====================================================================
������      �� YUV422ToYUV420Close_map
����        ���ͷ�ǰ����ľ����DS
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle  : ͼ��ǰ����ľ��
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/04/11    1.0        ZouWenYi      ����淶��
====================================================================*/	
l32 YUV422ToYUV420Close_map(void *pvHandle);

/*====================================================================
������      �� YUV422ToYUV420SetParam_map
����        ��ͼ��ǰ����Ĳ�������
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              l32 l32SrcWidth    : Դͼ��Ŀ��
			  l32 l32SrcHeight   : Դͼ��ĸ߶�
			  l32 l32SrcStride   : Դͼ��Ĳ���
			  l32 l32DstWidth    : Ŀ��ͼ��Ŀ��
			  l32 l32DstHeight   : Ŀ��ͼ��ĸ߶�
			  l32 l32DstStride   : Ŀ��ͼ��Ĳ���
             
����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/04/13    1.0        ZouWenYi        ����
====================================================================*/
l32 YUV422ToYUV420SetParam_map(void *pvHandle, l32 l32SrcWidth, l32 l32SrcHeigt, l32 l32SrcStride,
					   l32 l32DstWidth, l32 l32DstHeight, l32 l32DstStride);

//ͼ��ǰ����
#define  YUV422ToYUV420Init      YUV422ToYUV420Init_map
#define  YUV422ToYUV420          YUV422ToYUV420_map
#define  YUV422ToYUV420Close     YUV422ToYUV420Close_map
#define  YUV422ToYUV420SetParam  YUV422ToYUV420SetParam_map

/*====================================================================
������      ��AddLogo_map
����        ����Logo�ӵ�ͼ����
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����TImageInfo *ptBackgroundImage   ָ�򱳾�ͼ���ָ��
              TLogoInfo *ptLogo  ָ�������ǰ��ͼ����Ϣ�Ľṹ��ָ��

����ֵ˵��  ���ɹ�����VIDEOSUCCESS; ���󷵻� VIDEOFAILURE

�ر�˵�� : ͼ��Ŀ��Ϊ8�ı���,�߶�Ϊ4�ı���,���򷵻ش���.
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/11/24    1.0         HuangKui		����
05/04/07    1.1         ZouWenyi       ����淶�����㷨�ĸĽ�
====================================================================*/
l32 AddLogo_map(TImageInfo *ptBackgroundImage, TLogoInfo *ptLogo);

//���ͼ��
#define  AddLogo_map  AddLogo

/*====================================================================
������  �� ImageDering_map
����	: ��ͼ�����ȥ����ЧӦ
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptImage   ��Deringͼ��ָ��
               l32         l32Quant  : ��������(��Χ2~62)

����ֵ˵�� ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ͼ��Ŀ�ȱ���Ϊ8�ı���   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
05/14/2005             ZouWenyi    ����淶������
====================================================================*/
l32 ImageDering_map(TImageInfo *ptImage, l32 l32Quant);

//Dering
#define  ImageDering  ImageDering_map


/*====================================================================
������      �� imagezoom_map
����        �� ��ͼ��YUV420��ʽ�����ź�����ת��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo *pOld : �任ǰ��ͼ��ָ��
              TImageInfo *pNew : �任���ͼ��ָ��
			  u8 u8IamgeQuality : ͼ��任������־
             
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
03/24/2005    1.0         zhaobo        ����
====================================================================*/
l32 ImageZoom_map(TImageInfo *ptOld, TImageInfo *ptNew, u8 u8ImageQuality);

//ͼ������
#define ImageZoom ImageZoom_map


/*====================================================================
������      ��ImageTypeChange_map
����        ����ͼ��(YUV420��ʽ)��֡���ͱ任
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵����TImageInfo *pOld ���Ŵ�ǰ��ͼ��ָ��
              TImageInfo *pNew ���Ŵ���ͼ��ָ��			  
����ֵ˵��  ����
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		   �汾		�޸���		�߶���      �޸�����
04/26/2005	   1.0		�Բ�					����
====================================================================*/
l32 ImageTypeChange_map(TImageInfo *ptOld, TImageInfo *ptNew);

//ͼ������ת��
#define ImageTypeChange ImageTypeChange_map

/*====================================================================
������      �� YUYVToYUV420_c
����        �� ͼ��YUV422ת��ΪYUV420
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo *pOld ���Ŵ�ǰ��ͼ��ָ��
              TImageInfo *pNew ���Ŵ���ͼ��ָ��
             
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/12/11    1.0         zhaobo          ����
====================================================================*/
l32 YUYVToYUV420_map(TImageInfo *ptOld, TImageInfo *ptNew);

#define YUYVToYUV420 YUYVToYUV420_map

/*====================================================================
������      �� YUV420To422_map
����        ��ͼ��YUV420תΪYUV422
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo *ptYUV420 : ָ��YUV420��ͼ��ṹ��ָ��
              TImageInfo *ptYUV422 : ָ��YUV422��ͼ��ṹ��ָ��(YVU
			  422��ͼ�����ݴ���ڽṹ���Y��������)
             
����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
�ر�˵�� : ͼ��Ŀ��Ϊ8�ı���,�߶�Ϊ2�ı��� 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
05/16/2005    1.0        ZouWenYi      ����淶��
====================================================================*/
l32  YUV420To422_map(TImageInfo *ptYUV420, TImageInfo *ptYUV422);

#define  YUV420To422   YUV420To422_map

/*====================================================================
������  �� ImageDeblockInit_map
����	:  ��ͼ�����ȥ���ʼ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� l32  l32Width  :��ͼ������(����Ϊ8�ı���)

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ͼ��Ŀ�ȱ���Ϊ8�ı���   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
09/08/2005             ZouWenyi         ����
====================================================================*/
l32 ImageDeblockInit_map(l32 l32Width);

/*====================================================================
������  �� ImageDeblock_map
����	: ��ͼ�����ȥ�鴦��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptOldImage   ��ָ��Deblockǰ��ͼ��ָ��
               TImageInfo *ptNewImage   : ָ��Deblock���ͼ��ָ��
               l32  l32Quant     : ��������

����ֵ˵�� ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ͼ��Ŀ�ȱ���Ϊ8�ı���   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
05/23/2005             ZouWenyi         ����
====================================================================*/
l32 ImageDeblock_map(TImageInfo *ptOldImage, TImageInfo *ptNewImage, l32 l32Quant);

/*====================================================================
������  �� ImageDeblockClose_map
����	:  �ر�ͼ��Deblock
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� 

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   :  
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
09/08/2005             ZouWenyi         ����
====================================================================*/
l32 ImageDeblockClose_map();

//Deblock
#define  ImageDeblockInit   ImageDeblockInit_map
#define  ImageDeblock       ImageDeblock_map
#define  ImageDeblockClose  ImageDeblockClose_map

/*====================================================================
������      �� TemporalFilterInit_map
����    	�� ʱ���˲���ʼ������
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� void **ppvHandle : ���
               l32  l32Width    : ͼ��Ŀ��
			   l32  l32Height   : ͼ��ĸ߶�

����ֵ˵��  :  �ɹ����� VIDEOFAILURE, ʧ�ܷ��� VIDEOSUCCESS;
�ر�˵��: ͼ��Ŀ��Ϊ32�ı���,֧�����ͼ��Ϊ352*576
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/19/2004  1.0        Huangkui         ����
03/07/2005  1.0        ZouWenyi        ���DS
06/01/2005             ZouWenyi	      ����淶��
====================================================================*/
l32 TemporalFilterInit_map(void **ppvHandle, l32 l32Width, l32 l32Height);


/*====================================================================
������      �� TemporalFilter
����    	�� ʱ���˲�
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� void *pvHandle : ָ��ʱ���˲��ṹ���ָ��
               u8 *pu8RawImage          : ָ���˲�ǰͼ��ָ��
			   u8 *pu8FilteredImage     : ָ���˲���ͼ��ָ��
			   u16 *pu16CurSum8x8        : ��ǰ֡ÿ8��8��(Y����)��4��4��(UV����)���ص���ֵ֮��

����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
�ر�˵��: ͼ��Ŀ��Ϊ32�ı���,֧�����ͼ��Ϊ352*576
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/19/2004  1.0        Huangkui         ����
03/07/2005  1.0        ZouWenyi        ���DS
06/01/2005             ZouWenyi	      ����淶��
====================================================================*/
l32 TemporalFilter_map(void *pvHandle, u8 *pu8RawImage, u8 *pu8FilteredImage, u16 *pu16CurSum8x8);

/*====================================================================
������      �� TemporalFilterClose_map
����    	�� �ر�ʱ���˲����
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� 
            void *pvHandle  :  ָ��ͼ��ǰ����ľ��

����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/19/2004  1.0        Huangkui         ����
03/07/2005  1.0        ZouWenyi        ���DS
06/01/2005             ZouWenyi	      ����淶��
====================================================================*/
l32 TemporalFilterClose_map(void *pvHandle);

/*====================================================================
������      �� TemporalFilterSetParam_map
����    	�� ʱ���˲��Ĳ����ı�
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� void *pvHandle : ���
               l32  l32Width    : ͼ��Ŀ��
               l32  l32Height   : ͼ��ĸ߶�
			   l32  l32Threshold : �˲�ʱ����ֵѡ��
			        (THRESHIGHΪ����ֵ, THRESLOWΪ����ֵ)

����ֵ˵��  :  �ɹ�����VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
�ر�˵��: ͼ��Ŀ��Ϊ32�ı���,֧�����ͼ��Ϊ352*576
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
11/19/2004  1.0        Huangkui         ����
06/02/2005             ZouWenyi	      ����淶��
====================================================================*/
l32 TemporalFilterSetParam_map(void *pvHandle, l32 l32Width, l32 l32Height, l32  l32Threshold);

/*====================================================================
������      �� TemporalFilterSetThreshold_map
����    	�� ʱ���˲��Ĳ�������ֵ�ı�
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� void *pvHandle : ���
			   l32  l32Threshold : �˲�ʱ����ֵѡ��
			      (THRESHIGHΪ����ֵ, THRESLOWΪ����ֵ(H264������))

����ֵ˵��  : �ɹ����� VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/27/2006             ZouWenyi	        ����
====================================================================*/
l32 TemporalFilterSetThreshold_map(void *pvHandle, l32 l32Threshold);

//ͼ���ʱ���˲�
#define  TemporalFilterInit          TemporalFilterInit_map
#define  TemporalFilter              TemporalFilter_map
#define  TemporalFilterClose         TemporalFilterClose_map
#define  TemporalFilterSetParam      TemporalFilterSetParam_map
#define  TemporalFilterSetThreshold  TemporalFilterSetThreshold_map


/*====================================================================
������  �� ImageCrossFilter
����	: ��ͼ�����ʮ���˲�
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo  *ptOld  ��ָ��Դͼ��ṹ���ָ��
               TImageInfo  *ptNew  : ָ���˲���ͼ��ṹ���ָ��

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ͼ��Ŀ�ȱ���Ϊ8�ı���   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
05/30/2005             ZouWenyi        ����
====================================================================*/
l32 ImageCrossFilter_map(TImageInfo *ptOld, TImageInfo *ptNew);

//ͼ��ʮ���˲�
#define  ImageCrossFilter  ImageCrossFilter_map

/*====================================================================
������  �� ZoomImageAndMerge420_map
����	:  �ȶ�ͼ�������С,Ȼ��ϲ�������ͼ����,ͼ��ĸ�ʽΪ420
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptForegroundImage  :��ָ��ǰ��ͼ��ṹ���ָ��
               TImageInfo *ptBackgroundImage  :  ָ�򱳾�ͼ��ṹ���ָ��
			   l32  l32Top      : ǰ��ͼ����С���ڱ���ͼ���еĴ�ֱ�����λ��
			   l32  l32Left     : ǰ��ͼ����С���ڱ���ͼ���е�ˮƽ�����λ��
			   l32  l32ZoomType : ǰ��ͼ����С����(֧��1/4, 1/9, 1/16)

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ��   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
10/11/2005             ZouWenyi         ����
====================================================================*/
l32 ZoomImageAndMerge420_map(TImageInfo *ptForegroundImage, TImageInfo *ptBackgroundImage, l32 l32Top, l32 l32Left, l32 l32ZoomType);

#define  ZoomImageAndMerge420  ZoomImageAndMerge420_map

/*====================================================================
������  �� IrregularZoomImageAndMerge420_map
����	:  �ȶ�ͼ�������С,Ȼ��ϲ�������ͼ����,ͼ��ĸ�ʽΪ420
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptForegroundImage  :��ָ��ǰ��ͼ��ṹ���ָ��
               TImageInfo *ptBackgroundImage  :  ָ�򱳾�ͼ��ṹ���ָ��
			   l32  l32Top      : ǰ��ͼ����С���ڱ���ͼ���еĴ�ֱ�����λ��
			   l32  l32Left     : ǰ��ͼ����С���ڱ���ͼ���е�ˮƽ�����λ��
			   l32  l32Width    : ǰ��ͼ����С���ڱ���ͼ���еĿ��
			   l32 l32Height    : ǰ��ͼ����С���ڱ���ͼ���еĸ߶�

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ��   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾    �޸���     �߶���      �޸�����
10/31/2005  1.0    	zhaobo                   ���� 
===========================================================================*/
l32 IrregularZoomImageAndMerge420_map(TImageInfo *ptForegroundImage, TImageInfo *ptBackgroundImage, l32 l32Top, l32 l32Left, l32 l32Width, l32 l32Height);

#define  IrregularZoomImageAndMerge420  IrregularZoomImageAndMerge420_map

/*====================================================================
������      �� MotionSurveil
����    	�� ͼ����˶����
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� TImageInfo  *ptCurImage  : ָ��ǰ֡ͼ���ָ��
               TImageInfo  *ptPreImage  : ָ��ǰһ֡ͼ���ָ��
			   u8 *pu8MotionLevel       : ָ���˶��������ָ��
			                            (��ÿ��bit,0��ʾ��ֹ��1��ʾ�˶�)
����ֵ˵��  ���ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾    �޸���     �߶���      �޸�����
10/31/2005  1.0    	zhaobo                   ���� 
====================================================================*/
l32 MotionSurveil_map(TImageInfo *ptCurImage, TImageInfo *ptPreImage, u8 *pu8MotionLevel);

#define  MotionSurveil  MotionSurveil_map

#elif  defined  C_CODE
////////////////C���԰�ĺ�������//////////////////////////////////
/*====================================================================
������      :	4CifYUV422FieldPToN
����        :	��4cif�ĳ���ʽYUV422ͼ����P��ת��ΪN��
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	�Ѽӵĺڱ߲�ȥ
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/09/29    1.0         zhaobo			����
====================================================================*/
l32 D1YUV422FieldPToN_c(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  D1YUV422FieldPToN  D1YUV422FieldPToN_c

/*====================================================================
������      :	4CifYUV422FieldNToP_c
����        :	��4cif�ĳ���ʽYUV422ͼ����N��ת��ΪP��
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	���¼Ӻڱ�
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/09/29    1.0         zhaobo			����
====================================================================*/
l32 D1YUV422FieldNToP_c(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  D1YUV422FieldNToP  D1YUV422FieldNToP_c

/*====================================================================
������      :	D1YUV422FieldNToP_c
����        :	��4cif�ĳ���ʽYUV422ͼ����N��ת��ΪP��,������ͬһ��buffer
				����
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	���¼Ӻڱ�
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/10/10    1.0         zhaobo			����
====================================================================*/
l32 D1YUV422FieldNToPOneBuffer_c(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  D1YUV422FieldNToPOneBuffer  D1YUV422FieldNToPOneBuffer_c

/*====================================================================
������      :	D1YUV420FieldPToNOneBuffer_c
����        :	��4cif�ĳ���ʽYUV420ͼ����P��ת��ΪN��, ��һ��buffer
				����
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	�Ѽӵĺڱ߲�ȥ
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
06/10/10    1.0         zhaobo			����
====================================================================*/
l32 D1YUV420FieldPToNOneBuffer_c(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  D1YUV420FieldPToNOneBuffer  D1YUV420FieldPToNOneBuffer_c

/*====================================================================
������      :	D1YUV420FieldNToPTwoBuffer_c
����        :	��4cif�ĳ���ʽYUV420ͼ����N��ת��ΪP��
				����
����ȫ�ֱ���:	�� 
�㷨ʵ��    :	�Ӻڱ�
�������˵��:	TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
����ֵ˵��  :	�ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
10/27/06    1.0         zhaobo			����
====================================================================*/
l32 D1YUV420FieldNToPTwoBuffer_c(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  D1YUV420FieldNToPTwoBuffer  D1YUV420FieldNToPTwoBuffer_c
/*====================================================================
������      ��ProduceMosaic
����        ����ͼ���������
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����  TImageInfo *ptInImage  : ����ͼ��
				TImageInfo *ptOutImage : ���ͼ��
                l32 l32Left            : ����������������
                l32 l32Top             : ����������������
                l32 l32WindowWidth     : ������������
                l32 l32WindowHeight    : ����������߶�
                l32 l32Granularity     : ����������
����ֵ˵��  ���ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/11/24    1.0         HuangKui		����
06/06/22    1.5         zhaobo        �淶�����޸�
====================================================================*/
l32 ProduceMosaic_c(TImageInfo *ptInImage, TImageInfo *ptOutImage, 
				      l32 l32Left, l32 l32Top, l32 l32WindowWidth, l32 l32WindowHeight, l32 l32Granularity);
#define  ProduceMosaic  ProduceMosaic_c

/*====================================================================
������      ��MergePictureInit
����        ��ͼ��ϳɳ�ʼ��
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����void **ppvHandle : ���
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
�ر�˵�� :  ֻ֧��YUV420��ͼ��ϲ�
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾         �޸���        �޸�����
11/24/2003  1.0         HuangKui	     ����
04/26/2005  1.1         ZouWenyi       ����淶��         
08/10/2006  2.0            zb         ��Map�汾һ�� 
====================================================================*/
l32 MergePictureInit_c(void **ppvHandle);
#define  MergePictureInit  MergePictureInit_c
/*====================================================================
������      �� MergePicture
����        ����Сͼ�񸲸ǵ���ͼ���ָ��λ��
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����void *pvHandle ���
			  TImageInfo *ptBackgroundImage   ָ�򱳾�ͼ���ָ��
              TLogoInfo *ptLogo  ָ�������ǰ��ͼ����Ϣ�Ľṹ��ָ��
			    (Сͼ������ݷ���ptLogo��pu8YUV��Ա����,��Ҫ����ptLogo��
				������Ա����:l32Height(Сͼ��ĸ߶�), l32Width(Сͼ��Ŀ��), 
				l32Left(Сͼ���ڴ�ͼ����ˮƽ����ƫ�ƵĴ�С), l32Top(Сͼ����
				��ͼ���д�ֱ����ƫ�ƵĴ�С), l32ImageType(֡��ʽ���߳���ʽ),
				l32TopCutLine(Сͼ���ϱ߲�ȥ������),l32BottomCutLine(Сͼ����
				�߲�ȥ������), l32LeftCutLine(Сͼ����߲�ȥ������), l32RightCutLine
				(Сͼ���ұ߲�ȥ������))
			  
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
�ر�˵�� :  ֻ֧��YUV420��ͼ��ϲ�
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾         �޸���        �޸�����
11/24/2003  1.0         HuangKui	     ����
04/26/2005  1.1         ZouWenyi       ����淶��         
08/10/2006  2.0            zb         ��Map�汾һ��
====================================================================*/
l32 MergePicture_c(void *pvHandle, TImageInfo *ptBackgroundImage, TLogoInfo *ptLogo);

#define  MergePicture  MergePicture_c
/*====================================================================
������      �� MergePictureClose
����        �� ͼ��ϳɹر�
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����void *pvHandle ���			  
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
�ر�˵�� :  ֻ֧��YUV420��ͼ��ϲ�
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾         �޸���        �޸�����
11/24/2003  1.0         HuangKui	     ����
04/26/2005  1.1         ZouWenyi       ����淶��         
08/10/2006  2.0            zb         ��Map�汾һ��  
====================================================================*/
l32 MergePictureClose_c(void *pvHandle);

#define  MergePictureClose  MergePictureClose_c

/*====================================================================
������      :	ImageSizeChange_c
����	    :	����˫���Բ�ֵ�ķ�����Դͼ�����ű�ͼ��
�㷨ʵ��    :	
����ȫ�ֱ���:	��
�������˵��:	TImageInfo *ptInImage : �任ǰ��ͼ��ָ��
				TImageInfo *ptOutImage : �任���ͼ��ָ��
����ֵ˵��  :	��
----------------------------------------------------------------------
�޸ļ�¼:    
��  ��		   �汾		�޸���		�߶���      �޸�����
03/07/2006      1.0      �Բ�                    ���� 
====================================================================*/
l32 ImageSizeChange_c(TImageInfo *ptInImage, TImageInfo *ptOutImage);

#define  ImageSizeChange  ImageSizeChange_c

/*====================================================================
������      :	YUV420toRGB
����	    :	YUV420��ʽת��Ϊrgb��ʽ
�㷨ʵ��    :	
����ȫ�ֱ���:	��
�������˵��:	u8 *pu8Dst            : rgbͼ���ָ��
				l32 l32RGBTop         : rgbͼ����ұ߽�
				l32 l32RGBLeft        : rgbͼ�����߽�
				l32 l32RGBWidth       : rgbͼ��Ŀ��
				l32 l32RGBHeight      : rgbͼ��ĸ߶�
				(������ͼ��������rgbͼ��ʱ���ò�����0���ɣ���Ȼ����ʵ�ʿ��)
				u8 u8RGBType          : rgbͼ�������
				TImageInfo *ptInImage : �����YUV420ͼ��
����ֵ˵��  :	��
----------------------------------------------------------------------
�޸ļ�¼:    
��  ��		   �汾		�޸���		�߶���      �޸�����
06/29/2006     1.0       �Բ�                     ���� 
====================================================================*/
l32 YUV420toRGB_c(u8 *pu8Dst, l32 l32RGBTop, l32 l32RGBLeft, l32 l32RGBWidth, l32 l32RGBHeight, u8 u8RGBType, TImageInfo *ptInImage);

#define  YUV420toRGB	YUV420toRGB_c

/*====================================================================
������      �� DrawBanner_c
����        ����ͼ������Ӻ��(�����ο�����Ϊָ������ɫ)
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo  *ptImage   : ָ��ͼ��ṹ���ָ��
		      TBanner *ptBanner      : ָ�����ṹ��ָ��

����ֵ˵��  ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE  
�ر�˵�� : ͼ�������ָ���ͼ�����е�Y����            
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
05/18/2005    1.1        ZouWenyi        ����
10/27/2005    1.2        ZouWenyi        �޸�
====================================================================*/
l32 DrawBanner_c(TImageInfo *ptImage, TBanner *ptBanner);

#define  DrawBanner  DrawBanner_c

/*====================================================================
������      �� YUV422ToYUV420AndTemporalFilterInit_c
����        �� ͼ��YUV422ת��ΪYUV420�ĳ�ʼ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void **ppvHandle   : ָ��ͼ��ǰ��������ָ��
              ptYUV422To420Param  : YUV422תΪYUV420ͼ��Ĳ�������
              
����ֵ˵��  ���ɹ�����VIDEOSUCCESSFUL, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/21    1.0        ZouWenYi        ����
====================================================================*/
l32  YUV422ToYUV420AndTemporalFilterInit_c(void **ppvHandle, TYUV422ToYUV420Param *ptYUV422To420Param);

#define  YUV422ToYUV420AndTemporalFilterInit YUV422ToYUV420AndTemporalFilterInit_c

/*====================================================================
������      �� YUV422ToYUV420AndTemporalFilter_c
����        ��ͼ��YUV422ת��ΪYUV420�Ĵ�������ʱ���˲�
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              u8   *pu8Src     : ָ��Դͼ�����ݵ�ָ��
			  u8   *pu8Dst     : ָ��Ŀ��ͼ�����ݵ�ָ��
								 
����ֵ˵��  ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ���VIDEOFAILURE;
�������ر�˵����ֻ֧�ֱַ���720*576��YUV422ת���ֱ���720*576,352*576, 352*288��YUV420ͼ��
                ʱ���˲�ֻ֧��352*288��352*576
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/21    1.0        ZouWenYi         ����
====================================================================*/
l32 YUV422ToYUV420AndTemporalFilter_c(void *pvHandle, u8 *pu8Src, u8 *pu8Dst);

#define  YUV422ToYUV420AndTemporalFilter YUV422ToYUV420AndTemporalFilter_c

/*====================================================================
������      �� YUV422ToYUV420AndTemporalFilterSetParam_c
����        ��ͼ��YUV422ת��YUV420�Ĳ�������
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              ptYUV422To420Param  : YUV422תΪYUV420ͼ��Ĳ�������
             
����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/21    1.0        ZouWenYi        ����
====================================================================*/
l32 YUV422ToYUV420AndTemporalFilterSetParam_c(void *pvHandle, TYUV422ToYUV420Param *ptYUV422To420Param);

#define  YUV422ToYUV420AndTemporalFilterSetParam  YUV422ToYUV420AndTemporalFilterSetParam_c

/*====================================================================
������      �� YUV422ToYUV420AndTemporalFilterClose_c
����        ���ͷ�ǰ����ľ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle  : ͼ��YUV422תΪYUV420�ľ��

����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/04/21    1.0        ZouWenYi         ����
====================================================================*/	
l32 YUV422ToYUV420AndTemporalFilterClose_c(void *pvHandle);

#define  YUV422ToYUV420AndTemporalFilterClose YUV422ToYUV420AndTemporalFilterClose_c

/*====================================================================
������      �� TemporalFilterInit_c
����    	�� ʱ���˲���ʼ������
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� void **ppvHandle : ���
               l32  l32Width    : ͼ��Ŀ��
			   l32  l32Height   : ͼ��ĸ߶�
			   u8   *pu8CommonBuf :  ��������(����Ĵ�СΪ(7*352*576*3/2) + (46*352*576/64) + (20<<10); 
			   ����7*352*576*3/2����ǰ��7֡������, (46*352*576/64)����ǰ��7֡8*8������֮�ͺ�
			   ����8*8������֮��֮��������ֵ, ���20<<10��DSʹ�õĹ���Buffer,C���԰治��Ҫ

����ֵ˵��  :  �ɹ����� VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE;
�ر�˵��: ͼ��Ŀ��Ϊ32�ı���,֧�����ͼ��Ϊ352*576
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/10/2005              ZouWenyi	       ����
====================================================================*/
l32 TemporalFilterInit_c(void **ppvHandle, l32 l32Width, l32 l32Height);

/*====================================================================
������      �� TemporalFilter
����    	��  ʱ���˲�
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� TTemporalFilterHandle *ptTemporalFilter : ָ��ʱ���˲��ṹ���ָ��
               u8 *pu8RawImage          : ָ���˲�ǰͼ��ָ��
			   u8 *pu8FilteredImage     : ָ���˲���ͼ��ָ��
			   u16 *pu16CurSum8x8        : ��ǰ֡ÿ8��8��(Y����)��4��4��(UV����)���ص���ֵ֮��

����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
�ر�˵��: ͼ��Ŀ��Ϊ32�ı���,֧�����ͼ��Ϊ352*576
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/10/2005              ZouWenyi	       ����
====================================================================*/
l32 TemporalFilter_c(void *ptTemporalFilter, u8 *pu8RawImage, u8 *pu8FilteredImage, u16 *pu16CurSum8x8);

/*====================================================================
������      �� TemporalFilterClose_c
����    	�� �ر�ʱ���˲����
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� 
            void *pvHandle  :  ָ��ͼ��ǰ����ľ��

����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/10/2005             ZouWenyi	       ����
====================================================================*/
l32 TemporalFilterClose_c(void *pvHandle);

/*====================================================================
������      �� TemporalFilterSetParam_c
����    	�� ʱ���˲��Ĳ����ı�
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� void *pvHandle : ���
               l32  l32Width    : ͼ��Ŀ��
			   l32  l32Height   : ͼ��ĸ߶�
			   l32  l32Threshold : �˲�ʱ����ֵѡ��
			                     (THRESHIGHΪ����ֵ, THRESLOWΪ����ֵ)

����ֵ˵��  :  �ɹ����� VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/10/2005             ZouWenyi	        ����
====================================================================*/
l32 TemporalFilterSetParam_c(void *pvHandle, l32 l32Width, l32 l32Height, l32 l32Threshold);

/*====================================================================
������      �� TemporalFilterSetThreshold_c
����    	�� ʱ���˲��Ĳ�������ֵ�ı�
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� void *pvHandle : ���
			   l32  l32Threshold : �˲�ʱ����ֵѡ��
			      (THRESHIGHΪ����ֵ, THRESLOWΪ����ֵ(H264������))

����ֵ˵��  : �ɹ����� VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/27/2006             ZouWenyi	        ����
====================================================================*/
l32 TemporalFilterSetThreshold_c(void *pvHandle, l32 l32Threshold);

/*====================================================================
������      �� imagezoom_c
����        �� ��ͼ��YUV420��ʽ�����ź�����ת��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo *pOld : �任ǰ��ͼ��ָ��
              TImageInfo *pNew : �任���ͼ��ָ��
			  u8 u8IamgeQuality : ͼ��任������־
             
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
03/24/2005    1.0         zhaobo        ����
====================================================================*/
l32 ImageZoom_c(TImageInfo *ptOld, TImageInfo *ptNew, u8 u8ImageQuality);

//ͼ������
#define ImageZoom ImageZoom_c


/*====================================================================
������      ��ImageTypeChange_c
����        ����ͼ��(YUV420��ʽ)��֡���ͱ任
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵����TImageInfo *pOld ���Ŵ�ǰ��ͼ��ָ��
              TImageInfo *pNew ���Ŵ���ͼ��ָ��			  
����ֵ˵��  ����
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��		   �汾		�޸���		�߶���      �޸�����
04/26/2005	   1.0		�Բ�					����
====================================================================*/
l32 ImageTypeChange_c(TImageInfo *ptOld, TImageInfo *ptNew);

//ͼ������ת��
#define ImageTypeChange ImageTypeChange_c

/*====================================================================
������      �� YUYVToYUV420_c
����        �� ͼ��YUV422ת��ΪYUV420
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo *pOld ���Ŵ�ǰ��ͼ��ָ��
              TImageInfo *pNew ���Ŵ���ͼ��ָ��
             
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2006/12/11    1.0         zhaobo          ����
====================================================================*/
l32 YUYVToYUV420_c(TImageInfo *ptOld, TImageInfo *ptNew);

#define YUYVToYUV420 YUYVToYUV420_c

/*====================================================================
������      �� YUV422ToYUV420Init_c
����        �� ͼ��YUV422ת��ΪYUV420�ĳ�ʼ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void **ppvHandle   : ָ��ͼ��ǰ��������ָ��
              l32 l32SrcWidth    : Դͼ��Ŀ��
			  l32 l32SrcHeight   : Դͼ��ĸ߶�
			  l32 l32SrcStride   : Դͼ��Ĳ���
			  l32 l32DstWidth    : Ŀ��ͼ��Ŀ��
			  l32 l32DstHeight   : Ŀ��ͼ��ĸ߶�
			  l32 l32DstStride   : Ŀ��ͼ��Ĳ���
             
����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ���󷵻� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/05/13    1.0        ZouWenYi        ����
====================================================================*/
l32 YUV422ToYUV420Init_c(void **ppvHandle, l32 l32SrcWidth, l32 l32SrcHeight, l32 l32SrcStride,
					   l32 l32DstWidth, l32 l32DstHeight, l32 l32DstStride);


/*====================================================================
������      �� YUV422ToYUV420_c
����        ��ͼ��YUV422ת��ΪYUV420�Ĵ���
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              u8   *pu8Src     : ָ��Դͼ�����ݵ�ָ��
			  u8   *pu8Dst     : ָ��Ŀ��ͼ�����ݵ�ָ��
			  u16  *pu16Sum8x8 : ָ��Y����8*8�������֮��,UV����4*4������֮�͵�ָ��,
			                     ����ָ��Ϊ��ʱ,��ʾ������8*8�������֮��			  

����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ���VIDEOFAILURE;
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/05/13    1.0        ZouWenYi         ����
====================================================================*/
l32 YUV422ToYUV420_c(void *pvHandle, u8 *pu8Src, u8 *pu8Dst, u16 *pu16Sum8x8);


/*====================================================================
������      �� YUV422ToYUV420SetParam_c
����        ��ͼ��YUV422ת��YUV420�Ĳ�������
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle   : ָ��ͼ��ǰ��������ָ��
              l32 l32SrcWidth    : Դͼ��Ŀ��
			  l32 l32SrcHeight   : Դͼ��ĸ߶�
			  l32 l32SrcStride   : Դͼ��Ĳ���
			  l32 l32DstWidth    : Ŀ��ͼ��Ŀ��
			  l32 l32DstHeight   : Ŀ��ͼ��ĸ߶�
			  l32 l32DstStride   : Ŀ��ͼ��Ĳ���
             
����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/05/13    1.0        ZouWenYi        ����
====================================================================*/
l32 YUV422ToYUV420SetParam_c(void *pvHandle, l32 l32SrcWidth, l32 l32SrcHeigt, l32 l32SrcStride,
							 l32 l32DstWidth, l32 l32DstHeight, l32 l32DstStride);

/*====================================================================
������      �� YUV422ToYUV420Close_c
����        ���ͷ�ǰ����ľ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����void *pvHandle  : ͼ��YUV422תΪYUV420�ľ��

����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
2005/05/13    1.0        ZouWenYi         ����
====================================================================*/	
l32 YUV422ToYUV420Close_c(void *pvHandle);
							 
/*====================================================================
������      ��AddLogo_c
����        ����Logo�ӵ�ͼ����
����ȫ�ֱ������� 
�㷨ʵ��    ��(��ѡ��)
�������˵����TImageInfo *ptBackgroundImage   ָ�򱳾�ͼ���ָ��
              TLogoInfo *ptLogo  ָ�������ǰ��ͼ����Ϣ�Ľṹ��ָ��

����ֵ˵��  ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE

�ر�˵�� : ͼ��Ŀ��Ϊ8�ı���,�߶�Ϊ4�ı���,���򷵻ش���.
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾           �޸���        �޸�����
04/26/2005    1.1         ZouWenyi         ����
====================================================================*/
l32 AddLogo_c(TImageInfo *ptBackgroundImage, TLogoInfo *ptLogo);

/*====================================================================
������  �� ImageDering_c
����	:  ��ͼ�����ȥ����ЧӦ
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptImage   ��Deringͼ��ָ��
               l32         l32Quant  : ��������(��Χ2~62)

����ֵ˵�� ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ͼ��Ŀ�ȱ���Ϊ8�ı���   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
05/14/2005             ZouWenyi    ����淶������
====================================================================*/
l32 ImageDering_c(TImageInfo *ptImage, l32 l32Quant);

/*====================================================================
������      �� YUV420To422_c
����        ��ͼ��YUV420תΪYUV422
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ������� 
�������˵����TImageInfo *ptYUV420 : ָ��YUV420��ͼ��ṹ��ָ��
              TImageInfo *ptYUV422 : ָ��YUV422��ͼ��ṹ��ָ��(YVU
                 422��ͼ�����ݴ���ڽṹ���Y��������, ���������Y����
				 �Ĳ���)

����ֵ˵��  ���ɹ����� VIDEOSUCCESS, ���󷵻�VIDEOFAILURE
�ر�˵�� : ͼ��Ŀ��Ϊ8�ı���,�߶�Ϊ2�ı��� 
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��        �汾        �޸���        �޸�����
05/16/2005    1.0        ZouWenYi        ����
====================================================================*/
l32  YUV420To422_c(TImageInfo *ptYUV420, TImageInfo *ptYUV422);

/*====================================================================
������  �� ImageDeblockInit_c
����	:  ��ͼ�����ȥ���ʼ��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� l32  l32Width  :��ͼ������(����Ϊ8�ı���)

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   :  
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
09/08/2005             ZouWenyi         ����
====================================================================*/
l32 ImageDeblockInit_c(l32 l32Width);

/*====================================================================
������  �� ImageDeblock_c
����	: ��ͼ�����ȥ�鴦��
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptOldImage   ��ָ��Deblockǰ��ͼ��ָ��
               TImageInfo *ptNewImage   : ָ��Deblock���ͼ��ָ��
               l32  l32Quant  : ��������

����ֵ˵�� ���ɹ�����VIDEOSUCCESS, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ͼ��Ŀ�ȱ���Ϊ8�ı���   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
05/23/2005             ZouWenyi         ����
====================================================================*/
l32 ImageDeblock_c(TImageInfo *ptOldImage, TImageInfo *ptNewImage, l32 l32Quant);

/*====================================================================
������  �� ImageDeblockClose_c
����	:  �ر�ͼ��Deblock
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� 

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   :  
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
09/08/2005             ZouWenyi         ����
====================================================================*/
l32 ImageDeblockClose_c();

/*====================================================================
������  �� ZoomImageAndMerge420_c
����	:  �ȶ�ͼ�������С,Ȼ��ϲ�������ͼ����,ͼ��ĸ�ʽΪ420
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptForegroundImage  :��ָ��ǰ��ͼ��ṹ���ָ��
               TImageInfo *ptBackgroundImage  :  ָ�򱳾�ͼ��ṹ���ָ��
			   l32  l32Top      : ǰ��ͼ����С���ڱ���ͼ���еĴ�ֱ�����λ��
			   l32  l32Left     : ǰ��ͼ����С���ڱ���ͼ���е�ˮƽ�����λ��
			   l32  l32ZoomType : ǰ��ͼ����С����(֧��1/4, 1/9, 1/16)

����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ��   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
10/11/2005             ZouWenyi         ����
====================================================================*/
l32 ZoomImageAndMerge420_c(TImageInfo *ptForegroundImage, TImageInfo *ptBackgroundImage, l32 l32Top, l32 l32Left, l32 l32ZoomType);

/*====================================================================
������  �� IrregularZoomImageAndMerge420_c
����	:  �ȶ�ͼ�������С,Ȼ��ϲ�������ͼ����,ͼ��ĸ�ʽΪ420
�㷨ʵ��    ��(��ѡ��)
����ȫ�ֱ�������
�������˵���� TImageInfo *ptForegroundImage  :��ָ��ǰ��ͼ��ṹ���ָ��
               TImageInfo *ptBackgroundImage  :  ָ�򱳾�ͼ��ṹ���ָ��
			   l32  l32Top      : ǰ��ͼ����С���ڱ���ͼ���еĴ�ֱ�����λ��
			   l32  l32Left     : ǰ��ͼ����С���ڱ���ͼ���е�ˮƽ�����λ��
			   l32  l32Width    : ǰ��ͼ����С���ڱ���ͼ���еĿ��
			   l32 l32Height    : ǰ��ͼ����С���ڱ���ͼ���еĸ߶�
			
����ֵ˵�� ���ɹ�����VIDEOSUCCESSFUL, ʧ�ܷ��� VIDEOFAILURE
����˵��   : ��   
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
03/31/2006              zhaobo          ����
====================================================================*/
l32 IrregularZoomImageAndMerge420_c(TImageInfo *ptForegroundImage, TImageInfo *ptBackgroundImage, l32 l32Top, l32 l32Left, l32  l32Width, l32 l32Height);

/*====================================================================
������      �� MotionSurveil
����    	�� ͼ����˶����
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� TImageInfo  *ptCurImage  : ָ��ǰ֡ͼ���ָ��
               TImageInfo  *ptPreImage  : ָ��ǰһ֡ͼ���ָ��
			   u8 *pu8MotionLevel       : ָ���˶��������ָ��
			                            (��ÿ��bit,0��ʾ��ֹ��1��ʾ�˶�)
����ֵ˵��  ���ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾    �޸���     �߶���      �޸�����
10/31/2005  1.0    	zhaobo                   ���� 
====================================================================*/
l32 MotionSurveil_c(TImageInfo *ptCurImage, TImageInfo *ptPreImage, u8 *pu8MotionLevel);

#define  MotionSurveil  MotionSurveil_c

//ͼ���ʱ���˲�
#define  TemporalFilterSetParam      TemporalFilterSetParam_c
#define  TemporalFilterInit          TemporalFilterInit_c
#define  TemporalFilter              TemporalFilter_c
#define  TemporalFilterClose         TemporalFilterClose_c
#define  TemporalFilterSetThreshold  TemporalFilterSetThreshold_c

//ȥ����ЧӦ
#define   ImageDering   ImageDering_c

//���ͼ��
#define   AddLogo   AddLogo_c

//ͼ��YUV422תΪYUV420
#define  YUV422ToYUV420Init     YUV422ToYUV420Init_c
#define  YUV422ToYUV420         YUV422ToYUV420_c
#define  YUV422ToYUV420Close    YUV422ToYUV420Close_c
#define  YUV422ToYUV420SetParam YUV422ToYUV420SetParam_c

//ͼ��YUV420תΪYUV422
#define  YUV420To422      YUV420To422_c

//ͼ��Deblock
#define  ImageDeblockInit   ImageDeblockInit_c
#define  ImageDeblock       ImageDeblock_c
#define  ImageDeblockClose  ImageDeblockClose_c

//ͼ����С�ͺϲ�
#define  ZoomImageAndMerge420  ZoomImageAndMerge420_c
#define  IrregularZoomImageAndMerge420  IrregularZoomImageAndMerge420_c

#endif

#ifdef __cplusplus
};
#endif 

#endif // _IMAGEPROCESS_H_

