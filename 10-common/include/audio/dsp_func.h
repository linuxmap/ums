/*****************************************************************************
ģ   ��   ��: dsp_func
��   ��   ��: dsp_func.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: dsp��ʹ�õĿ�����ѧ������ͷ����
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2005/05/25      1.0         ��  ��      ��    ��

******************************************************************************/
#ifndef DSP_FUNC_H
#define DSP_FUNC_H

#include "algorithmtype.h"

/*-------------------------------*
 * Mathematic functions.         *
 *-------------------------------*/

l32 Inv_sqrt(   /* (o) Q30 : output value   (range: 0<=val<1)           */
  l32 L_x       /* (i) Q0  : input value    (range: 0<=val<=7fffffff)   */
);

void Log2(
  l32 L_x,       /* (i) Q0 : input value                                 */
  s16 *exponent, /* (o) Q0 : Integer part of Log2.   (range: 0<=val<=30) */
  s16 *fraction  /* (o) Q15: Fractionnal part of Log2. (range: 0<=val<1) */
);

l32 Pow2(        /* (o) Q0  : result       (range: 0<=val<=0x7fffffff) */
  s16 exponent,  /* (i) Q0  : Integer part.      (range: 0<=val<=30)   */
  s16 fraction   /* (i) Q15 : Fractionnal part.  (range: 0.0<=val<1.0) */
);


#endif // endif GMATH_H

