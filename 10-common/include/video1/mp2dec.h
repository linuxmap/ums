#ifndef _MP2DEC_H_
#define _MP2DEC_H_

#ifdef __cplusplus
extern "C" {
#endif 
#include "algorithmType.h"


#define MP2DEC_OK      0
#define MP2DEC_ERROR   -1

	typedef void *Mp2DecHandle;			//���������

	typedef struct TagMp2DecFrame
	{	
		u8 *pu8InputBitstream;		//���������ĵ�ַ
		u8 *pu8OutputBuffer;			//���������ŵĵ�ַ
		l32 s32InputBitstreamLength;	//�����������������
		l32 s32ChromaFormat;			//���ͼ��ĸ�ʽ  1��420��ʽ 2��422��ʽ
		l32 s32Height;				//�������ͼ��ĸ߶� 
		l32 s32Width;				//�������ͼ��Ŀ��
		l32 s32FrameType;			//���ͼ���ʽ1:I֡; 0:P֡
		l32 s32PostProcess;			//���룺�Ƿ���� 1���� 0����
	}TMp2DecFrame;


	l32 Mp2DecoderInit(Mp2DecHandle *pHMp2Dec);//��������ʼ��

	l32 Mp2DecodeOneFrame(Mp2DecHandle hMp2Dec,TMp2DecFrame *pMp2DecFrame);//����һ֡

	l32 Mp2DecFree(Mp2DecHandle hMp2Dec);  //�ͷŽ�����

#ifdef __cplusplus
}
#endif 

#endif
