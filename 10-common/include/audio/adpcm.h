
/*****************************************************************************
ģ   ��   ��: IMA ADPCM ������
��   ��   ��: adpcm.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: IMA ADPCM ������ͷ�ļ�
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2006/06/28      1.0         XXR         ����
 2006/10/27      2.0         ��  ��      �����˱�����
******************************************************************************/
#ifndef ADPCM_H
#define ADPCM_H

#ifdef __cplusplus
extern "C" {
#endif
//Get Version NO
void  GetAdpcmDecVersion(u8 *Version, l32 StrLen, l32 *StrLenUsed);

/*=============================================================================
�� �� ��: IMAADPCMDecoder
��    ��: IMA ADPCM������
�㷨ʵ��: ÿ�ν���һ֡���ݣ����ݸ�ʽ����:
	byte0~ byte31: ����ͷ��Ϣ.Ŀǰ�Ľ�����ֻ֧��������, ��Ч��ϢΪbyte28~byte31
	byte32~byte159: ������Ч���ݣ���128�ֽڣ���256������ı���������ǰ��4bit��װ
	
ȫ�ֱ���: ��
��    ��: pu8InputDataAddr		  [in]�������ݵ�ַ
          ps16OutputDataAddr      [out]������ݵ�ַ����256��s16����
          
�� �� ֵ: �������ݳ���(�ֽ�)  �����512(�ֽ�)
��    ��: XXR
=============================================================================*/
u32 IMAADPCMDecoder(u8 *pu8InputDataAddr, s16 *ps16OutputDataAddr);

s16 *IMAADPCMEncInit();
void IMAADPCMEncFree(s16 *ps16State);
s16 IMAADPCMEncoder(s16 *ps16InBuf , u8 *pu8OutBuf, s16 *ps16State);

#ifdef __cplusplus
}
#endif


#endif //end of ADPCM_H
