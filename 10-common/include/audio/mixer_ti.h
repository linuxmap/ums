/******************************************************************
ģ���� 			�������������붨���ļ�
�ļ��� 			��mixErr.h
����ļ�		��
�ļ�ʵ�ֹ���	�������������붨��
����			���Ѵ���	
�汾			��0.1
��������		��2003/6/10
-------------------------------------------------------------------
�޸ļ�¼��
����     	  �汾    	 �޸���    �޸�����
2004/11/19    0.2        ��  ��    �޸��˽ӿ�����MixAud20��MixAud32
******************************************************************/
#ifndef MIXER_TI_H
#define MIXER_TI_H

#define FAILE 1
#define SUCCESS 0

#define MAX_CHANNEL 32


typedef struct
{
    u8    *mPCMValue; //pointer to Audio Buffer
    u32   nVolume;  //Audio Volume
}TAudBuf;

l32 MixAud20(TAudBuf **aptInAudBuf,
			  u32 u32InChList,
              TAudBuf **aptOutAudBuf,
              TAudBuf *ptOutNAudBuf,
               u32 u32InSampleCnt);
             
l32 MixAud32(TAudBuf *InBufArray[],
             u32 InChIndex,
             TAudBuf *OutBufArray[],
             TAudBuf *NoutChannel,
             u32 uiPCMLength);             


#endif

