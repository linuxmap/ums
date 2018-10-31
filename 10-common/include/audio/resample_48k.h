/*****************************************************************************
ģ   ��   ��: �����ʱ任ģ��
��   ��   ��: resample_48k.h
�� ��  �� ��: resample_48k.h, resample_48k.c
�ļ�ʵ�ֹ���: ʵ��8k,16k,32k��������48k������֮���ת��
��        ��: V1.0  Copyright(C) 2006-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2006/06/20      1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef RESAMPLE_48K_H
#define RESAMPLE_48K_H

#ifdef __cplusplus
extern "C" {
#endif

//�궨��
#define MAXFACTOR_RES48K 8                          //Maximum Factor without output buff overflow
#define MAXIBUFFSIZE_RES48K 2048                    //Input buffer size
#define MAXOBUFFSIZE_RES48K (MAXIBUFFSIZE_RES48K*MAXFACTOR_RES48K+2) //Calc'd out buffer size

//�ṹ���Ͷ���
typedef enum  tagENUM_RES
{
	//������
	RES_48TO8,
	RES_48TO16,
	RES_48TO32,

	//������
	RES_8TO48,
	RES_16TO48,
	RES_32TO48
} ENUM_RES;

typedef void (*PRESFUN)(void *, s16 *, s16 *, l32 *, l32 *);

typedef struct tagRESAMPLE_HANDLE
{
	u32 u32Time; 
	s16 *ps16Imp;
	PRESFUN Resamp;  //����ָ��

	//�������Buf
	s16 as16X[MAXIBUFFSIZE_RES48K];
	s16 as16Y[MAXOBUFFSIZE_RES48K];

	u16 u16FrameLen;
	u16 u16OutBufLen;
	u16 u16Xp;
	u16 u16XOff;
	u16 u16Xread;
	u16 u16LpScl;
	u16 u16OSkip;
	u16 u16Dhb;      
	u16 u16Dtb;
} RESAMPLE_HANDLE, *PRESAMPLE_HANDLE;

//�ӿں�������
void InitRes48k(PRESAMPLE_HANDLE pResH, ENUM_RES eRes, u16 u16FrameLen);
l32 ResFlow48k(PRESAMPLE_HANDLE pResH,s16 *ps16InData, s16 *ps16OutData);

#ifdef __cplusplus
}
#endif

#endif // end of RESAMPLE_48K_H
