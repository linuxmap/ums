/******************************************************************************
ģ����	    ��img_multidec_public
�ļ���	    ��img_multidec_public.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ����������������ṹ��
����		��������
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2008/01/02		1.0		        ������                ����
******************************************************************************/
#ifndef _IMG_MULTIDEC_PUBLIC_H_
#define _IMG_MULTIDEC_PUBLIC_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "videodefines.h"
#include "vid_videounit.h"

#define MAX_MULTIDEC_NUM    64

//������������ṹ
typedef struct
{
    l32 l32DecoderNum;                                  //����������
    TVideoUnitDecParam atDecParam[MAX_MULTIDEC_NUM];	//����������
}TImageMultiDecParam;

//���������������ṹ
typedef struct
{
    l32 al32NeedDecode[MAX_MULTIDEC_NUM];             //�����־λ(0:�����룻1�����룻2�����ǰһ֡ͼ��
    TDecInput atDecInput[MAX_MULTIDEC_NUM];	         //�������������ָ��
}TImageMultiDecInput;

//���������������ṹ
typedef struct
{
    TDecOutput atDecOutput[MAX_MULTIDEC_NUM];	        //�������������ָ��
    l32 al32RetVal[MAX_MULTIDEC_NUM];                  //��������ֵ
}TImageMultiDecOutput;

//�������״̬�����ṹ
typedef struct
{
    l32 l32DecoderNum;                                          //����������
	TVideoUnitDecStatusParam atDecStatus[MAX_MULTIDEC_NUM];     //������״̬����ָ��
	l32 al32RetVal[MAX_MULTIDEC_NUM];                           //��������ֵ
}TImageMultiDecStatusParam;

#ifdef __cplusplus
}
#endif

#endif
