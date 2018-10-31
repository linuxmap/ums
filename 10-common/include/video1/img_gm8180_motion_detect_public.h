/******************************************************************************
ģ����	    ��img_gm8180_motion_detect_public
�ļ���	    ��img_gm8180_motion_detect_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����GM8180ͼ���˶��������ṹ��
����		��zouwenyi
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸����� 
2008/11/25		1.0				������                 ����
******************************************************************************/
#ifndef _IMG_GM8180_MOTION_DETECT_PUBLIC_H_
#define _IMG_GM8180_MOTION_DETECT_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//GM8180�˶��������ṹ��
typedef struct  
{
    l32 l32MBWidth;       //����ͼ������
    l32 l32MBHeight;       //����ͼ����߶�
    l32 l32IsUseSad;      //use sad info flag(ĿǰGM8180��֧�֣�ֻ����0)
    l32 l32InterlaceMode; //interlace mode (1: interlaced; 0: non-interlaced)
    l32 l32MvThrehold;    //�Ƿ��˶�����ֵ
    l32 l32MDInterval;    //�����˶����ļ��֡��
}TImgGM8180MotionDetectParam;

//GM8180�˶����״̬�����ṹ��
#define TImgGM8180MotionDetectStatusParam TImgGM8180MotionDetectParam
    
//GM8180�˶��������ṹ��
typedef struct  
{
    u8 *pu8MBInfo;     //ģ����Ϣָ��(GM8180Ӳ���ṩ����Ϣ)
    u8 *pu8MotionInfo; //����˶�������Ϣ(ÿ���ֽڴ���һ������Ƿ��˶��ı�־��
                       //0����ֹ��1���˶�,�������ң����ϵ���˳���������)
}TImgGM8180MotionDetectInput;

//GM8180�˶������������ṹ��
typedef struct
{
    u32 u32Reserved; //��������
}TImgGM8180MotionDetectOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_GM8180_MOTION_DETECT_PUBLIC_H_
