#ifndef _MP2ENC_H_
#define _MP2ENC_H_

#ifdef __cplusplus
extern "C" {
#endif 
#include "algorithmType.h"
//����������ֵ	
#define MP2ENC_OK 0
#define MP2ENC_ERROR -1	
// chroma_format 
#define CHROMA420 1
#define CHROMA422 2
#define CHROMA444 3

	typedef void * Mp2EncHandle;//������
	
	//�������������
	typedef struct TagMp2EncParam
	{
		l32 s32Height;              //ͼ��߶�
		l32 s32Width;               // ͼ����
		l32 s32BitRate;             //��������
		l32 s32IFrameInterval;      //I֡���
		l32 s32ChromaFormat;        //ͼ���ʽCHROMA420/CHROMA422 
		l32 s32MaxQuant;            //�������ϵ��1��31
		l32 s32MinQuant;            //��С����ϵ��1��31
	}TMp2EncParam; 
	
	//����������/�������
	typedef struct TagMp2EncFrame
	{
		u8 *   pu8InputBuf;				//����ͼ���ŵ�ַ
		u8 *   pu8OutputBuf;				//�������������ŵ�ַ
		l32     s32OutputBitStreamLength;//�����������(byte)
		l32     s32ForceIFrame;			//�Ƿ�ǿ��I ֡����; 1:��; 0:��
		l32     s32FrameType;			//����������� 1:I֡; 0:P֡
		l32		s32Width;
		l32		s32Height;
	} TMp2EncFrame;   
	
	//�����ʼ��
	l32 Mp2EncoderInit(Mp2EncHandle *pHMp2Enc, TMp2EncParam *pMp2EncParam);
    //���ñ������
	l32 Mp2EncSetParam(Mp2EncHandle hMp2Enc, TMp2EncParam *pMp2EncParam);	
	//����һ֡ͼ��
	l32 Mp2EncodeOneFrame(Mp2EncHandle hMp2Enc, TMp2EncFrame *pMp2EncFrame);
	//�ͷű�����
	l32 Mp2EncFree(Mp2EncHandle hMp2Enc);
	
	void  GetMpeg2Version(void *pVer, l32 s32BufLen, l32 *ps32VerLen);
	void Mp2GetReconFile(Mp2EncHandle hMp2Enc,s8 *ps8FileName);	
#ifdef __cplusplus
}
#endif 

#endif
