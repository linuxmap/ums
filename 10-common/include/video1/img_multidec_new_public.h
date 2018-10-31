/******************************************************************************
ģ����	    ��img_multidec_new_public
�ļ���	    ��img_multidec_new_public.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ����������������ṹ��
����		��������
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2008/05/09		1.0		        ����                 ����
******************************************************************************/
#ifndef _IMG_MULTIDEC_NEW_PUBLIC_H_
#define _IMG_MULTIDEC_NEW_PUBLIC_H_

#include "videodefines.h"
#include "vid_videounit.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_MULTIDEC_NUM    96

//������������ṹ
typedef struct
{
    l32 l32DecoderNum;                                      //����������
    TVideoUnitDecParam atDecParam[MAX_MULTIDEC_NUM];	//����������
    u32 u32Reserved;
}TImageMultiDecNewParam;

//���������������ṹ
typedef struct
{
    l32 al32NeedDecode[MAX_MULTIDEC_NUM];               //�Ƿ����ı�־λ
    TDecInput atDecInput[MAX_MULTIDEC_NUM];	            //�������������ָ��
    u32 u32Reserved;
}TImageMultiDecNewInput;

//���������������ṹ
typedef struct
{
    TMultiDecOutput atMultiDecOutput[MAX_MULTIDEC_NUM]; //��·���������Ϣ
    l32 al32RetVal[MAX_MULTIDEC_NUM];                   //ÿ·���뷵��ֵ
    u8 *pu8OutBuf;                                      //��·�������Buf(һ���Buf)
    TBufGroupInfo atDecBufInfo[MAX_BUF_GROUPS];         //��·�������BUF����Ϣ
    l32 l32DecBufGroups;                                //��·�������BUF����
    l32 l32OffsetY;                                     //U������ʼƫ��
    u32 u32Reserved;                                    
}TImageMultiDecNewOutput;

//�������״̬�����ṹ
typedef struct
{
    l32 l32DecoderNum;                                              //����������
	TVideoUnitDecStatusParam atDecStatus[MAX_MULTIDEC_NUM];     //������״̬����ָ��
	l32 al32RetVal[MAX_MULTIDEC_NUM];                           //��������ֵ
    u32 u32Reserved;
}TImageMultiDecNewStatusParam;

#ifdef __cplusplus
}
#endif

#endif
