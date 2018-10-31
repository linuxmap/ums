/******************************************************************************
ģ����	    ��img_merge_zoom_public
�ļ���	    ��img_merge_zoom_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ����廭��ϳɲ����ṹ��
����		��������
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2009/03/10		1.0		        ������                 ����
******************************************************************************/
#ifndef _IMG_MERGE_ZOOM_PUBLIC_H_
#define _IMG_MERGE_ZOOM_PUBLIC_H_

#include "videodefines.h"
#include "img_common_public.h"

#ifdef __cplusplus
extern "C" {
#endif

//���Ż���ϳ�ģ��ǰ��ͼ������ṹ
typedef struct
{
    TFgInputSource l32FgInputSource;            //ǰ��ͼ����������ݣ�����FG_PIC_INPUTΪǰ����ͼ�����룻NO_PIC_INPUTΪǰ����ͼ�����룩
    TPicZoomStyle l32ZoomStyle;                 //����ģʽ��PIC_ZOOM_ONE��ȫ�����ţ�PIC_ZOOM_TWO�����ֱ������첢����ͼ��������PIC_ZOOM_THREE�����ֱ������첢����Ŀ������PIC_ZOOM_FOUR������ԭ�гߴ�,���ںϳɳߴ��ͼ�����в����ñߴ���, PIC_ZOOM_FIVE ����ԭ�гߴ�,���ںϳɳߴ��ͼ��ᰴ�ձ��ֱ������첢����ͼ���������ţ�
    l32 l32ZoomScaleWidth;                      //�������ģʽ��ģʽ�����������ſ�߱������ò�����l32ZoomHeightScale�ɶ�ʹ��(��ǰ������4��3�������ţ����ֵΪ4���ò���Ϊ�����ձ�������ͼ���������)
    l32 l32ZoomScaleHeight;                     //�������ģʽ��ģʽ�����������ſ�߱������ò�����l32ZoomWidthScale�ɶ�ʹ��(��ǰ������4��3�������ţ����ֵΪ3���ò���Ϊ�����ձ�������ͼ���������)
    l32 l32FgPositionNum;                       //����λ�ñ�ţ�����λ�ñ��Լ�����մ��ϵ��´�����˳�����α�ţ�
	l32 l32FgSrcWidth;                          //ǰ��������Դͼ����
	l32 l32FgSrcHeight;                         //ǰ��������Դͼ��߶�
	l32 l32FgFrameFieldFormat;                  //ǰ��ͼ�������(֡��ʽ���߳���ʽ)��֡��ʽΪFRAME_FORMAT������ʽΪFIELD_FORMAT��
	l32 l32FgYUVType;                           //ǰ��ͼ���ʽ(YUV422����YUV420)
	l32 l32DrawFocusFlag;                       //�����Ƿ񹴻��߿�ı�ǣ�l32DrawFocusFlagΪ1�������߿�l32DrawFocusFlagΪ0���������߿�
	l32 l32FocusRGB;	                        //����߿�ɫRGB��������ʽΪ0x00RRGGBB��
    l32 l32FocusWidth;                          //�߿�ͳһ��ȣ�֡��ʽͼ����Ϊ2�ı���������ʽͼ����Ϊ4�ı�����,Ŀǰֻ֧����߽��߱���һ��
	u32 u32Reserved;	                        //��������
} TMergeZoomFgParam;

//���Ż���ϳ�ģ�鱳��ͼ������ṹ
typedef struct
{  
	l32 l32BgWidth;                             //����ͼ��Ŀ��
	l32 l32BgHeight;                            //����ͼ��ĸ߶�
	l32 l32BgFrameFieldFormat;                  //����ͼ�������(֡��ʽ���߳���ʽ)��֡��ʽΪFRAME_FORMAT������ʽΪFIELD_FORMAT��
	l32 l32BgYUVType;                           //����ͼ���ʽ(YUV422����YUV420)	
	l32 l32DrawBoundaryFlag;                    //�����Ƿ񹴻��߽��ߵı�ǣ�l32DrawBoundaryFlagΪ1�������߽��ߣ�l32DrawBoundaryFlagΪ0���������߽��ߣ�
    l32 l32BoundaryRGB;                         //����߽�����ɫRGB��������ʽΪ0x00RRGGBB��
    l32 l32BoundaryWidth;                       //�߽���ͳһ��ȣ�֡��ʽͼ����Ϊ2�ı���������ʽͼ����Ϊ4�ı�����
	l32 l32DrawBackgroundFlag;                  //������ͼ���Ƿ���䱳��ɫ
	l32 l32BackgroundRGB;	                    //����ϳɱ������ɫRGB��������ʽΪ0x00RRGGBB��
	u32 u32Reserved;	                        //��������
} TMergeZoomBgParam;

//���Ż���ϳ�ģ������ṹ
typedef struct
{  
    l32 l32MaxFgNum;                            //����ϳɵ����ǰ��������Ĭ��Ϊ���64���棩
    l32	l32MergeStyle;	                        //����ϳ�ģʽ������44�ֺϳ����ͣ����PicMergeZoomStyleö�����ͣ�    
    TMergeZoomBgParam tMergeZoomBgPic;          //����ͼ�������Ϣ
	TMergeZoomFgParam *ptMergeZoomFgPic;        //ǰ��ͼ�������Ϣ������ǰ��ͼ��������ȷ������˴˴����ýṹ��ָ����ʽ��ʵ�ʷ����С�ɻ���ϳɵ����ǰ������������
	u32 u32Reserved;	                        //��������
} TImageMergeZoomParam;

//���Ż���ϳ�ģ��״̬��ѯ�����ṹ
#define TImageMergeZoomStatusParam TImageMergeZoomParam

//���Ż���ϳ�ģ��ͼ����Ϣ�ṹ��
typedef struct 
{
    u8 *pu8Y;                                   //ͼ��Y����
    u8 *pu8U;                                   //ͼ��U����(���YUV��ַ������ſɽ�U��ַ����ΪNULL)
    u8 *pu8V;                                   //ͼ��V����(���YUV��ַ������ſɽ�U��ַ����ΪNULL)
    l32 l32YStride;                             //ͼ��Y��������(���YUV��ַ������ſɽ�l32YStride����Ϊ0)
    l32 l32UVStride;                            //ͼ��UV��������(���YUV��ַ������ſɽ�l32YStride����Ϊ0)
	u32 u32Reserved;	                        //��������
} TImageMergeZoomPicInfo;

//����ϳ�ģ������ṹ��
typedef struct 
{
    TImageMergeZoomPicInfo *ptImageMergeZoomInputPic;    //����ϳɵ�N·����ͼ�����Ϣ������ǰ��ͼ��������ȷ������˴˴����ýṹ��ָ����ʽ��ʵ�ʷ����С�ɻ���ϳɵ����ǰ������������    
    TImageMergeZoomPicInfo tImageMergeZoomOutputPic;     //����ϳɵ����ͼ�����Ϣ
	u32 u32Reserved;	                                 //��������
} TImageMergeZoomInput;
 
//����ϳ�ģ������ṹ��
typedef struct 
{
    u32 u32Reserved;   //�������� 
} TImageMergeZoomOutput;

#ifdef __cplusplus
}
#endif

#endif
