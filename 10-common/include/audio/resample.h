/*****************************************************************************
ģ   ��   ��: resample
��   ��   ��: resample_4.c, resample_2.c
              resample_1dot5.c, resample_3.c, resample_6.c
�� ��  �� ��: 
�ļ�ʵ�ֹ���: ����Ƶ�ʵ�ת��
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
2005/11/17       1.0         ��  ��      ��    ��
2006/07/13       2.0         ��  ��      ��������48k��������صı任����
******************************************************************************/
#ifndef RESAMPLE_H
#define RESAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define RESAMPLE_OK  0
#define RESAMPLE_ERR -1

#define FILTER112_LEN	112

typedef struct tSRCStruct
{
	l32 l32SmallFramLen;                //������ʱ����֡��or������ʱ���֡��
	l32 l32BigFramLen;                  //������ʱ����֡��or������ʱ���֡��

	s16 *ps16LtoHBuf;                   //������buf
	s16 *ps16HtoLBuf;                   //������buf

	s16 as16LtoHCoef[FILTER112_LEN];    //������
	s16 as16HtoLCoef[FILTER112_LEN];    //������
} SRCStruct;

/*====================================================================
��   ��   ��: SRCReSet_4
��        ��: 4�������任����(�ı�filter����, ����֡��, ���������)
����ȫ�ֱ���: ��
�������˵��: ��
���� ֵ ˵��: RESAMPLE_OK �ɹ� RESAMPLE_ERR ʧ��
�� ��  ˵ ��: �������峤��һ��,�������
              (FILTER112_LEN + l32SmallFramLen *4)*2
			  ���ֽ�Ϊ��λ
======================================================================*/
l32 SRCReSet_4(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);


/*====================================================================
��   ��   ��: SRCInit_4
��        ��: 4�������任��ʼ��(ϵ������ĳ�ʼ��, ��������)
����ȫ�ֱ���: ��
�������˵��: ��
���� ֵ ˵��: RESAMPLE_OK �ɹ� RESAMPLE_ERR ʧ��
�� ��  ˵ ��: �������峤��һ��,�������
              (FILTER112_LEN + l32SmallFramLen *4)*2
			  ���ֽ�Ϊ��λ
======================================================================*/
l32 SRCInit_4(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);

void SRC32kTo8k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);

void SRC8kTo32k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);


/*====================================================================
��   ��   ��: SRCReSet_2
��        ��: 2�������任����(�ı�filter����, ����֡��, ���������)
����ȫ�ֱ���: ��
�������˵��: ��
���� ֵ ˵��: RESAMPLE_OK �ɹ� RESAMPLE_ERR ʧ��
�� ��  ˵ ��: �������峤��һ��,�������
              (FILTER112_LEN + l32SmallFramLen *2)*2
			  ���ֽ�Ϊ��λ
======================================================================*/
l32 SRCReSet_2(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);

/*====================================================================
��   ��   ��: SRCInit_2
��        ��: 2�������任��ʼ��(ϵ������ĳ�ʼ��, ��������)
����ȫ�ֱ���: ��
�������˵��: ��
���� ֵ ˵��: RESAMPLE_OK �ɹ� RESAMPLE_ERR ʧ��
�� ��  ˵ ��: �������峤��һ��,�������
              (FILTER112_LEN + l32SmallFramLen *2)*2
			  ���ֽ�Ϊ��λ
======================================================================*/
l32 SRCInit_2(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);

void SRC32kTo16k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);

void SRC16kTo32k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);


/*====================================================================
��   ��   ��: SRCReSet_1dot5
��        ��: �����任����(�ı�filter����, ����֡��, ���������)
����ȫ�ֱ���: ��
�������˵��: ��
���� ֵ ˵��: RESAMPLE_OK �ɹ� RESAMPLE_ERR ʧ��
�� ��  ˵ ��: �������峤��һ��,�������
              (FILTER112_LEN + l32SmallFramLen *1.5)*2
			  ���ֽ�Ϊ��λ
======================================================================*/
l32 SRCReSet_1dot5(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);
/*====================================================================
��   ��   ��: SRCInit_1dot5
��        ��: 48k-32k�������˲�
����ȫ�ֱ���: ��
�������˵��: 
              1-(i) pSRCHand      ���
			  2-(i) ps16InData    ��������buf
			  3-(o) ps16InData    �������buf
���� ֵ ˵��: ��
�� ��  ˵ ��: ��
======================================================================*/
l32 SRCInit_1dot5(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);
void SRC32kTo48k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);
void SRC48kTo32k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);


/*====================================================================
��   ��   ��: SRCReSet_3
��        ��: �����任����(�ı�filter����, ����֡��, ���������)
����ȫ�ֱ���: ��
�������˵��: ��
���� ֵ ˵��: RESAMPLE_OK �ɹ� RESAMPLE_ERR ʧ��
�� ��  ˵ ��: �������峤��һ��,�������
              (FILTER112_LEN + l32SmallFramLen *3)*2
			  ���ֽ�Ϊ��λ
======================================================================*/
l32 SRCReSet_3(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);

/*====================================================================
��   ��   ��: SRCInit_3
��        ��: 48k-16k�������˲�
����ȫ�ֱ���: ��
�������˵��: 
              1-(i) pSRCHand      ���
			  2-(i) ps16InData    ��������buf
			  3-(o) ps16InData    �������buf
���� ֵ ˵��: ��
�� ��  ˵ ��: ��
======================================================================*/
l32 SRCInit_3(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);
void SRC16kTo48k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);
void SRC48kTo16k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);



/*====================================================================
��   ��   ��: SRCReSet_6
��        ��: �����任����(�ı�filter����, ����֡��, ���������)
����ȫ�ֱ���: ��
�������˵��: ��
���� ֵ ˵��: RESAMPLE_OK �ɹ� RESAMPLE_ERR ʧ��
�� ��  ˵ ��: �������峤��һ��,�������
              (FILTER112_LEN + l32SmallFramLen *6)*2
			  ���ֽ�Ϊ��λ
======================================================================*/
l32 SRCReSet_6(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);

/*====================================================================
��   ��   ��: SRCInit_6
��        ��: 48k-8k�������˲�
����ȫ�ֱ���: ��
�������˵��: 
              1-(i) pSRCHand      ���
			  2-(i) ps16InData    ��������buf
			  3-(o) ps16InData    �������buf
���� ֵ ˵��: ��
�� ��  ˵ ��: ��
======================================================================*/
l32 SRCInit_6(SRCStruct *pSRCHand, s16 *ps16HtoLBuf, s16 *ps16LtoHBuf, l32 l32SmallFramLen);
void SRC8kTo48k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);
void SRC48kTo8k(SRCStruct *pSRCHand, s16 *ps16InData, s16 *ps16OutData);

#ifdef __cplusplus
}
#endif

#endif //end of RESAMPLE_H

