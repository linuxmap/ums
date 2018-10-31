/*****************************************************************************
ģ   ��   ��: G.729����Ӧ�뱾������������ģ��
��   ��   ��: adaptive_codebook.h
�� ��  �� ��: ����Ӧ�뱾���������������ƪ����ĵ�
�ļ�ʵ�ֹ���: G.729����Ӧ�뱾������������ļ���
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
2005/06/13       1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef ADAPTIVE_CODEBOOK_H
#define ADAPTIVE_CODEBOOK_H

s16 s16EncodePitch( s16 s16PitchInt, s16 s16PitchFrac, s16 *ps16PitchMinSearch,
				    s16 *ps16PitchMaxSearch, s16 s16SubframeFlag );
void DecodePitch( s16 *ps16PitchInt, s16 *ps16PitchFrac, 
				 s16 s16PitchIndex, s16 s16SubframeFlag );
s16 s16ParityPitch( s16 s16PitchIndex );
s16 s16CheckParityPitch( s16 s16PitchIndex, s16 s16PitchParity );
s16 s16GainPitch( s16 *ps16Target, s16 *ps16AdaptCodebkFiltered,
				  s16 *ps16CorrGain, s16 s16SubframLen);

#endif