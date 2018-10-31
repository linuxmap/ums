/******************************************************************************
ģ����	    ��img_multienc_public
�ļ���	    ��img_multienc_public.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ����������������ṹ��
����		���� ��
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2008/10/21		1.0		        �� ��                ����
******************************************************************************/
#ifndef _IMG_MULTIENC_PUBLIC_H_
#define _IMG_MULTIENC_PUBLIC_H_

#include "videodefines.h"
#include "vid_videounit.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_MULTIENC_NUM    8

//������������ṹ
typedef struct
{
    l32 l32EncoderNum;                                  //����������
    TVideoUnitEncParam atEncParam[MAX_MULTIENC_NUM];	//����������
}TImageMultiEncParam;

//���������������ṹ
typedef struct
{
    TEncInput atEncInput[MAX_MULTIENC_NUM];	        //�������������ָ��
    u32 u32Reserved;
}TImageMultiEncInput;

//���������������ṹ
typedef struct
{
    TEncOutput atEncOutput[MAX_MULTIENC_NUM];	        //�������������ָ��
    l32 al32RetVal[MAX_MULTIENC_NUM];                  //��������ֵ
    u32 u32Reserved;
}TImageMultiEncOutput;

//�������״̬�����ṹ
typedef struct
{
    l32 l32EncoderNum;                                          //����������
	TVideoUnitEncStatusParam atEncStatus[MAX_MULTIENC_NUM];     //������״̬����ָ��
	l32 al32RetVal[MAX_MULTIENC_NUM];                           //��������ֵ
}TImageMultiEncStatusParam;

typedef struct
{
    TDebugInfoInput atDebugInfoInput[MAX_MULTIENC_NUM];
    u32 u32Reserved;
}TImageMultiEncDebugInput;

#ifdef __cplusplus
}
#endif

#endif
