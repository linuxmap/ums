/******************************************************************************
ģ����	    ��img_motionsurveil_public
�ļ���	    ��img_motionsurveil_public.h   
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����ͼ�������ṹ��
����		��zhaobo
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��	            �汾		�޸���   �߶���     �޸�����
2007/09/13		1.0	    zhaobo                ����
2009/03/12              1.1         ����                ����֡�����Ͳ���
2009/06/06              1.2        ������               �޸��ƶ����ӿڲ���
******************************************************************************/
#ifndef _IMG_MOTIONSURVEIL_PUBLIC_H_
#define _IMG_MOTIONSURVEIL_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//�ƶ�����������
typedef struct
{
    s16 s16Top;     //�������ֱλ��ƫ�ƣ�16����������
    s16 s16Left;    //�������ˮƽλ��ƫ�ƣ�16����������
    s16 s16Width;   //��������ȣ�16����������
    s16 s16Height;  //�������߶ȣ�16����������
}TImageMotionSurveilArea;

//�˶����Ĳ���
typedef struct  
{
    l32 l32Width;		//ͼ��Ŀ��
    l32 l32Height;		//ͼ��ĸ߶�
    l32 l32YUVType;		//ͼ���ͼ������
    l32 l32Interlace;           //ͼ���֡������(FRAME_FORMAT:֡��ʽ��FIELD_FORMAT:����ʽ)
    l32 l32FineTuneLevel;       //�ƶ���⼶��΢������(��ΧΪ-10��+10,�Ӹ����������������仯,0��ʾ�ƶ���ⲻ����΢��)
    s16 s16SurveilLevel;        //��⼶��(��ֵԽ��Խ����)
    s16 s16SurveilNum;          //����������
    TImageMotionSurveilArea atMotionSurveilArea[MAX_MOTION_SURVEIL_NUM]; //�ƶ��������
    u32 u32Reserved;
}TImageMotionSurveilParam;

//�˶�����״̬�ṹ��
#define TImageMotionSurveilStatusParam TImageMotionSurveilParam

//�˶������������
typedef struct
{
    u8 *pu8InCurImage;        //��ǰ֡Դͼ��
    u8 *pu8OutMotionInfo;     //����˶���Ϣ���ڴ���ַ
    u32 u32Reserved;
}TImageMotionSurveilInput;

//�˶������������
typedef struct
{
	u32 u32Reserved;		//��������
}TImageMotionSurveilOutput;

#ifdef __cplusplus
}
#endif

#endif //_IMG_MOTIONSURVEIL_PUBLIC_H_


