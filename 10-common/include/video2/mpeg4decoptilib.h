/******************************************************************************
�ļ���	    ��mpeg4decoptilib.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�mepg4�����Ż���
����		��������
�汾		��1.0
-------------------------------------------------------------------------------
��  ��		�汾		�޸���		�߶���    �޸�����
2006/08/28	1.0         ������                  ����
*******************************************************************************/

#ifndef  _MPEG4DECOPTILIB_H_
#define  _MPEG4DECOPTILIB_H_

#include <stdio.h>
#include <string.h>
#include <algorithmtype.h>

#if  defined(MAP_CODE)

/*=====================================================================
������       :  MP4IDCT_map
����         �� 8��8ģ���DCT�任 
����ȫ�ֱ��� �� ��
�������˵�� �� s16* ps16Block   ָ��8��8ģ��
����ֵ˵��   �� ��
����˵��     �� pBlock��ַ��Ҫ32λ����
======================================================================*/
void MP4IDCT_map(s16* ps16Block);

/*=====================================================================
�� �� ���� McCopy16to8_map
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
======================================================================*/
void McCopy16to8_map(u8 *const pu8Dst, const s16 *const ps16Src, u32 u32Stride);

/*====================================================================
�� �� ���� McCopy8x8_map
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
====================================================================*/
void McCopy8x8_map(u8 *const pu8Dst, const u8 *const pu8Src, const u32 u32Stride);

/*====================================================================
�� �� ���� McCopy8x4_map
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
====================================================================*/
void McCopy8x4_map(u8 *const pu8Dst, const u8 *const pu8Src, const u32 u32Stride);

/*====================================================================
�� �� ���� McAdd16to8_map
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
=====================================================================*/
void McAdd16to8_map(u8 *const pu8Dst, const s16 *const ps16Src, u32 u32Stride);

/*====================================================================
�� �� ���� DequantH263Inter_map
��    �ܣ� 8x8��inter�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
=====================================================================*/
void DequantH263Inter_map(s16* ps16DCTOut, s16* ps16DCTIn, l32 l32QP);

/*=====================================================================
�� �� ���� DequantH263Intra_map
��    �ܣ� 8x8��intra�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
=====================================================================*/
void DequantH263Intra_map(s16* ps16DCTOut, s16* ps16DCTIn, l32 l32QP, l32 l32DCScaler);

/*====================================================================
�� �� ���� DequantMpegInter_map
��    �ܣ� 8x8��inter�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void DequantMpegInter_map(s16 *const ps16Data, const s16 *ps16Coeff, const u32 u32Quant);

/*=====================================================================
�� �� ���� DequantMpegIntra_map
��    �ܣ� 8x8��intra�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
=====================================================================*/
void DequantMpegIntra_map(s16 *ps16Data, const s16 *ps16Coeff, const u32 u32Quant, const l32 l32DcScalar);

/*====================================================================
������       : Interpolate8x8H_map                            
����         : 8x8���ˮƽ����2Tap��ֵ                        
����ȫ�ֱ��� : ��                                             
�������˵�� :  const u8   *pu8Src        :Դ��ָ��           
                 u16        u16SrcStride  :Դ�鲽��           
                 u8        *pu8Dst        :Ŀ���ָ��         
                 u16        u16DstStride  :Ŀ��鲽��         
                 BOOL        bRounding   :�Ƿ������������    
����ֵ˵��   : ��                                             
����˵��     : ��                                             
=====================================================================*/
void Interpolate8x8H_map(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x8V_map
����         : 8x8��Ĵ�ֱ����2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x8V_map(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x8HV_map
����         : 8x8���б�Ƿ���2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x8HV_map(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x4H_map                            
����         : 8x4���ˮƽ����2Tap��ֵ                        
����ȫ�ֱ��� : ��                                             
�������˵�� :  const u8   *pu8Src        :Դ��ָ��           
                 u16        u16SrcStride  :Դ�鲽��           
                 u8        *pu8Dst        :Ŀ���ָ��         
                 u16        u16DstStride  :Ŀ��鲽��         
                 BOOL        bRounding   :�Ƿ������������    
����ֵ˵��   : ��                                             
����˵��     : ��                                             
=====================================================================*/
void Interpolate8x4H_map(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x4V_map
����         : 8x4��Ĵ�ֱ����2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x4V_map(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x4HV_map
����         : 8x4���б�Ƿ���2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x4HV_map(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

#define MP4IDCT MP4IDCT_map

#define McCopy16to8 McCopy16to8_map

#define McCopy8x8 McCopy8x8_map

#define McCopy8x4 McCopy8x4_map

#define McAdd16to8 McAdd16to8_map

#define DequantH263Inter DequantH263Inter_map

#define DequantH263Intra DequantH263Intra_map

#define DequantMpegInter DequantMpegInter_map

#define DequantMpegIntra DequantMpegIntra_map

#define Interpolate8x8H Interpolate8x8H_map

#define Interpolate8x8V Interpolate8x8V_map

#define Interpolate8x8HV Interpolate8x8HV_map

#define Interpolate8x4H Interpolate8x4H_map

#define Interpolate8x4V Interpolate8x4V_map

#define Interpolate8x4HV Interpolate8x4HV_map

#elif defined(C_CODE)

/*=====================================================================
������       :  MP4IDCT_c
����         �� 8��8ģ���DCT�任 
����ȫ�ֱ��� �� ��
�������˵�� �� s16* ps16Block   ָ��8��8ģ��
����ֵ˵��   �� ��
����˵��     �� pBlock��ַ��Ҫ32λ����
======================================================================*/
void MP4IDCT_c(s16* ps16Block);

/*=====================================================================
�� �� ���� McCopy16to8_c
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
======================================================================*/
void McCopy16to8_c(u8 *const pu8Dst, const s16 *const ps16Src, u32 u32Stride);

/*====================================================================
�� �� ���� McCopy8x8_c
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
====================================================================*/
void McCopy8x8_c(u8 *const pu8Dst, const u8 *const pu8Src, const u32 u32Stride);

/*====================================================================
�� �� ���� McCopy8x4_c
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
====================================================================*/
void McCopy8x4_c(u8 *const pu8Dst, const u8 *const pu8Src, const u32 u32Stride);

/*====================================================================
�� �� ���� McAdd16to8_c
��    �ܣ� 
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� 
�� �� ֵ�� ��
=====================================================================*/
void McAdd16to8_c(u8 *const pu8Dst, const s16 *const ps16Src, u32 u32Stride);

/*====================================================================
�� �� ���� DequantH263Inter_c
��    �ܣ� 8x8��inter�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
=====================================================================*/
void DequantH263Inter_c(s16* ps16DCTOut, s16* ps16DCTIn, l32 l32QP);

/*=====================================================================
�� �� ���� DequantH263Intra_c
��    �ܣ� 8x8��intra�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
=====================================================================*/
void DequantH263Intra_c(s16* ps16DCTOut, s16* ps16DCTIn, l32 l32QP, l32 l32DCScaler);

/*====================================================================
�� �� ���� DequantMpegInter_c
��    �ܣ� 8x8��inter�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void DequantMpegInter_c(s16 *const ps16Data, const s16 *ps16Coeff, const u32 u32Quant);

/*=====================================================================
�� �� ���� DequantMpegIntra_c
��    �ܣ� 8x8��intra�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
=====================================================================*/
void DequantMpegIntra_c(s16 *ps16Data, const s16 *ps16Coeff, const u32 u32Quant, const l32 l32DcScalar);

/*====================================================================
������       : Interpolate8x8H_c                            
����         : 8x8���ˮƽ����2Tap��ֵ                        
����ȫ�ֱ��� : ��                                             
�������˵�� :  const u8   *pu8Src        :Դ��ָ��           
                 u16        u16SrcStride  :Դ�鲽��           
                 u8        *pu8Dst        :Ŀ���ָ��         
                 u16        u16DstStride  :Ŀ��鲽��         
                 BOOL        bRounding   :�Ƿ������������    
����ֵ˵��   : ��                                             
����˵��     : ��                                             
=====================================================================*/
void Interpolate8x8H_c(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x8V_c
����         : 8x8��Ĵ�ֱ����2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x8V_c(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x8HV_c
����         : 8x8���б�Ƿ���2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x8HV_c(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x4H_c                            
����         : 8x4���ˮƽ����2Tap��ֵ                        
����ȫ�ֱ��� : ��                                             
�������˵�� :  const u8   *pu8Src        :Դ��ָ��           
                 u16        u16SrcStride  :Դ�鲽��           
                 u8        *pu8Dst        :Ŀ���ָ��         
                 u16        u16DstStride  :Ŀ��鲽��         
                 BOOL        bRounding   :�Ƿ������������    
����ֵ˵��   : ��                                             
����˵��     : ��                                             
=====================================================================*/
void Interpolate8x4H_c(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x4V_c
����         : 8x4��Ĵ�ֱ����2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x4V_c(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

/*====================================================================
������       : Interpolate8x4HV_c
����         : 8x4���б�Ƿ���2Tap��ֵ
����ȫ�ֱ��� : ��
�������˵�� :  const u8   *pu8Src        :Դ��ָ��
                 u16        u16SrcStride  :Դ�鲽��
                 u8        *pu8Dst        :Ŀ���ָ��
                 u16        u16DstStride  :Ŀ��鲽��
                 BOOL        bRounding   :�Ƿ������������
����ֵ˵��   : ��
����˵��     : ��
======================================================================*/
void Interpolate8x4HV_c(u8 *const pu8Dst, const u8 *pu8Src, const u32 u32Stride, const u32 u32Rounding);

#define MP4IDCT MP4IDCT_c

#define McCopy16to8 McCopy16to8_c

#define McCopy8x8 McCopy8x8_c

#define McCopy8x4 McCopy8x4_c

#define McAdd16to8 McAdd16to8_c

#define DequantH263Inter DequantH263Inter_c

#define DequantH263Intra DequantH263Intra_c

#define DequantMpegInter DequantMpegInter_c

#define DequantMpegIntra DequantMpegIntra_c

#define Interpolate8x8H Interpolate8x8H_c

#define Interpolate8x8V Interpolate8x8V_c

#define Interpolate8x8HV Interpolate8x8HV_c

#define Interpolate8x4H Interpolate8x4H_c

#define Interpolate8x4V Interpolate8x4V_c

#define Interpolate8x4HV Interpolate8x4HV_c

#endif

#endif
