/******************************************************************************
ģ����	    �� H263DecRtpReform                
�ļ���	    �� H263DecRtpReform.h
����ļ�	�� 
�ļ�ʵ�ֹ��ܣ� ����H263 RTP ��Ϣ
����		�� ����ʤ	
�汾		�� 1.0
---------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
07/08/2005  1.0			����ʤ				  ����
**************************************************************************************/

#ifndef _H263DECRTPREFORM_H_
#define _H263DECRTPREFORM_H_
#ifdef __cplusplus
extern "C" {
#endif


#include "kdvtype.h"


#define  DECRTPERR_OK 0
#define  DECRTPERR_ERROR -300

s32 H263AddRtpHdr(u8 *pu8H320Bitstream, s32 s32BitstreamLen, u8 *au8H323BitstreamBuf,s32 *ps32H323BitstreamLen);

void GetH263DecFormRTPVersion(void *pVer, s32 iBufLen, s32 *pVerLen);
void DumpRTPHead(u8 *pu8RTPData);
#ifdef __cplusplus
};
#endif 

#endif /*_H263DECRTPREFORM_H_*/	
