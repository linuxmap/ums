/******************************************************************************
�ļ���	    ��mpeg4encoptilib.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�mepg4�����Ż���
����		��������
�汾		��1.0
-------------------------------------------------------------------------------
��  ��		�汾		�޸���		�߶���    �޸�����
2006/08/28	1.0         ������                  ����
*******************************************************************************/

#ifndef  _MPEG4ENCOPTILIB_H_
#define  _MPEG4ENCOPTILIB_H_

#include <stdio.h>
#include <string.h>
#include <algorithmtype.h>

#if  defined(MAP_CODE)

/*=====================================================================
������       :  MP4PixAvgH8x8_map
����         �� Դ����ˮƽ�����ֵ
����ȫ�ֱ��� �� ��
�������˵�� ��  pu8Cur        ��Դ���ָ��
                 l32CurStride  ��Դ��鲽��
                 pu8Dst        ��Ŀ����ָ��
                 l32DstStride  ��Ŀ���鲽��
                 l32Width      ����ȣ�Ϊ8�ı�����
                 l32Height     ���߶�
����ֵ˵��   �� ��
����˵��     �� ��
======================================================================*/
void MP4PixAvgH8x8_map(const u8* pu8Cur, l32 l32CurStride, u8* pu8Dst, l32 l32Rouding);

/*=====================================================================
������       :  MP4PixAvgV8x8_map
����         �� Դ���Ĵ�ֱ�����ֵ
����ȫ�ֱ��� �� ��
�������˵�� ��  pu8Cur        ��Դ���ָ��
                 l32CurStride  ��Դ��鲽��
                 pu8Dst        ��Ŀ����ָ��
                 l32DstStride  ��Ŀ���鲽��
                 l32Width      ����ȣ�Ϊ8�ı�����
                 l32Height     ���߶�
����ֵ˵��   �� ��
����˵��     �� ��
======================================================================*/
void MP4PixAvgV8x8_map(const u8* pu8Cur, l32 l32CurStride, u8* pu8Dst, l32 l32Rouding);

/*=====================================================================
������       :  MP4PixAvgC8x8_map
����         �� Դ�������ķ����ֵ
����ȫ�ֱ��� �� ��
�������˵�� ��  pu8Cur        ��Դ���ָ��
                 l32CurStride  ��Դ��鲽��
                 pu8Dst        ��Ŀ����ָ��
                 l32DstStride  ��Ŀ���鲽��
                 l32Width      ����ȣ�Ϊ8�ı�����
                 l32Height     ���߶�
����ֵ˵��   �� ��
����˵��     �� ��
======================================================================*/
void MP4PixAvgC8x8_map(const u8* pu8Cur, l32 l32CurStride, u8* pu8Dst, l32 l32Rouding);

/*=====================================================================
������       :  MP4DCT_map
����         �� 8��8ģ���DCT�任 
����ȫ�ֱ��� �� ��
�������˵�� �� s16* ps16Block   ָ��8��8ģ��
����ֵ˵��   �� ��
����˵��     �� ps16Block��ַ��Ҫ32λ����
======================================================================*/
void MP4DCT_map(s16* ps16Block);

/*====================================================================
������       :  MP4IDCT_map
����         �� 8��8ģ���DCT�任 
����ȫ�ֱ��� �� ��
�������˵�� �� s16* ps16Block   ָ��8��8ģ��
����ֵ˵��   �� ��
����˵��     �� pBlock��ַ��Ҫ32λ����
======================================================================*/
void MP4IDCT_map(s16* ps16Block);

/*=====================================================================
�� �� ���� MP4AddiDCT8x8_map                                           
��    �ܣ� 8x8��DCT�任                                                
�㷨ʵ�֣� ��                                                          
ȫ�ֱ����� ��                                                          
��    ���� ps16Dct        DCT�任ϵ��                                  
           pu8Ref         Ԥ��ͼ��                                     
           pu8Rec         Ŀ��ͼ��                                     
�� �� ֵ�� ��                                                          
======================================================================*/
void MP4AddiDCT8x8_map(s16* ps16DCT, u8* pu8Rec, l32 l32RecStride, u8* pu8Ref, l32 l32RefStride);

/*=====================================================================
�� �� ���� MP4SubDCT8x8_map
��    �ܣ� 8x8��DCT
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16Dct        DCT�任ϵ��
           pu8Src         ԭʼͼ��
           pu8Dst         Ŀ��ͼ��
�� �� ֵ�� �� 
=====================================================================*/
void MP4SubDCT8x8_map(s16* ps16DCT, u8* pu8Src, l32 l32SrcStride, u8* pu8Dst, l32 l32DstStride);

/*=====================================================================
������       :  MP4Deviation16x16_map
����         �� �����ڸ�����ֵ��ƽ��ֵ��ľ���ֵ֮��
����ȫ�ֱ��� �� ��
�������˵�� ��  const u8  *pu8MB     ��ָ����ָ��
                 l32       l32Stride  ����鲽��

����ֵ˵��   �� ����ڸ�����ֵ��ƽ��ֵ��ľ���ֵ֮��
����˵��     �� ��
=====================================================================*/
u32 MP4Deviation16x16_map(const u8 *pu8Cur, l32 l32Stride);

/*====================================================================
������       :  MP4MemCopy8x8_map
����         :  8x8�����ݿ��� 
����ȫ�ֱ��� :  ��
�������˵�� :  u8  *pu8Src        ��Դ��ָ��
                l32  l32SrcStride  ��Դ�鲽��
                u8  *pu8Dst        ��Ŀ���ָ��
                l32  l32DstStride  ��Ŀ��鲽��
����ֵ˵��   :  ��
����˵��     :  ��
====================================================================*/
void MP4MemCopy8x8_map(const u8 *pu8Src, l32 l32SrcStride, u8 *pu8Dst, l32 l32DstStride);

/*====================================================================
�� �� ���� QuantIntra8x8_c
��    �ܣ� 8x8��intra������
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void MP4QuantIntra8x8_map(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32DCScaler, l32 l32QP);

/*====================================================================
�� �� ���� MP4QuantInter8x8_map
��    �ܣ� 8x8��inter������
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
l32 MP4QuantInter8x8_map(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32QP);

/*====================================================================
�� �� ���� MP4DeQuantInter8x8_map
��    �ܣ� 8x8��inter�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void MP4DeQuantInter8x8_map(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32QP);

/*====================================================================
�� �� ���� MP4DeQuantIntra8x8_map
��    �ܣ� 8x8��intra�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void MP4DeQuantIntra8x8_map(s16* ps16DCTIn, s16* ps16DCTOut,  l32 l32DCScaler, l32 l32QP);

/*=============================================================================
�� �� ���� MP4AddiDCTIQuant8x8_map
��    �ܣ� 16x16��DCT�任��Dequant
�㷨ʵ�֣� ��
ȫ�ֱ����� �� 
��    ���� ps16DCTIn     ������ϵ��ָ��
           ps16DCTOut    �����ϵ��ָ��
           pu8Rec        : �ؽ����ŵ�ַ
           l32RecStride  : �ؽ��鲽��
           pu8Ref        ���ο�ͼ��ָ��
           l32RefStride  ���ο�ͼ�񲽳�
           l32Qp         ������ϵ��
           l32IsIntra    ���Ƿ�ΪIntra��(Intra : 1; Inter : 0)
           l32Cbp        ����ǰ���Ƿ���ȫ0��0��ʾ��ȫ0�飬������ȫ0�飩
           l32DcScaler   ��DCϵ������������(Intra��Ż��õ�)
�� �� ֵ�� ��
=============================================================================*/
void MP4AddiDCTIQuant8x8_map(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32QP, u8* pu8Rec, l32 l32RecStride, u8* pu8Ref, l32 l32RefStride, l32 l32IsIntra, l32 l32Cbp, l32 l32DCSalar);

/*=============================================================================
�� �� ���� MP4SubDCTQuant8x8_c
��    �ܣ� 8x8��вDCT��Quant
�㷨ʵ�֣� ��
ȫ�ֱ����� �� 
��    ���� ps16Dct        DCT�任buffer
           pu8Src         ԭʼͼ��
           l32SrcStride   ԭʼͼ�񲽳�
           pu8Dst         �ο�ͼ��
           l32DstStride   �ο�ͼ�񲽳�
           ps16DctOut     ���������buffer
           l32Qp          ����ֵ
           l32IsIntra     ��ǰ���Ƿ���Intra��
           l32DCScaler    ֱ��ϵ������ֵ
�� �� ֵ�� ��
=============================================================================*/
l32 MP4SubDCTQuant8x8_map(s16* ps16DCT, u8* pu8Src, l32 l32SrcStride, u8* pu8Dst, l32 l32DstStride, s16* ps16DCTOut, l32 l32Qp, l32 l32IsIntra, l32 l32DCScalar);

/*=============================================================================
�� �� ��: MP4Interpolate8x8v_map
��    ��: �Բο�ͼ�����ˮƽ��������ز�ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate8x8v_map(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16Stride, u32 u32Num, l32 l32Rouding);

/*=============================================================================
�� �� ��: MP4Interpolate16x16v_map
��    ��: �Բο�ͼ�����ˮƽ��������ز�ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate16x16v_map(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16Stride, u32 u32Num, l32 l32Rouding);

/*=============================================================================
�� �� ��: MP4Interpolate8x8h_map
��    ��: �Բο�ͼ�����ˮƽ��������ذ˳�ͷ��ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate8x8h_map(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16SrcStride, u32 u32Num, l32 l32Rouding);

/*=============================================================================
�� �� ��: MP4Interpolate16x16h_map
��    ��: �Բο�ͼ�����ˮƽ��������ذ˳�ͷ��ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate16x16h_map(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16SrcStride, u32 u32Num, l32 l32Rouding);

#define MP4PixAvgH8x8 MP4PixAvgH8x8_map

#define MP4PixAvgV8x8 MP4PixAvgV8x8_map

#define MP4PixAvgC8x8 MP4PixAvgC8x8_map

#define MP4DCT MP4DCT_map

#define MP4IDCT MP4IDCT_map

#define MP4AddiDCT8x8 MP4AddiDCT8x8_map

#define MP4SubDCT8x8 MP4SubDCT8x8_map

#define MP4Deviation16x16 MP4Deviation16x16_map

#define MP4MemCopy8x8 MP4MemCopy8x8_map

#define MP4QuantIntra8x8 MP4QuantIntra8x8_map

#define MP4QuantInter8x8 MP4QuantInter8x8_map

#define MP4DeQuantInter8x8 MP4DeQuantInter8x8_map

#define MP4DeQuantIntra8x8 MP4DeQuantIntra8x8_map

#define MP4AddiDCTIQuant8x8 MP4AddiDCTIQuant8x8_map

#define MP4SubDCTQuant8x8 MP4SubDCTQuant8x8_map

#define MP4Interpolate8x8v MP4Interpolate8x8v_map

#define MP4Interpolate16x16v MP4Interpolate16x16v_map

#define MP4Interpolate8x8h MP4Interpolate8x8h_map

#define MP4Interpolate16x16h MP4Interpolate16x16h_map

#elif defined(C_CODE)

/*=====================================================================
������       :  MP4PixAvgH8x8_c
����         �� Դ����ˮƽ�����ֵ
����ȫ�ֱ��� �� ��
�������˵�� ��  pu8Cur        ��Դ���ָ��
                 l32CurStride  ��Դ��鲽��
                 pu8Dst        ��Ŀ����ָ��
                 l32DstStride  ��Ŀ���鲽��
                 l32Width      ����ȣ�Ϊ8�ı�����
                 l32Height     ���߶�
����ֵ˵��   �� ��
����˵��     �� ��
======================================================================*/
void MP4PixAvgH8x8_c(const u8* pu8Cur, l32 l32CurStride, u8* pu8Dst, l32 l32Rouding);

/*=====================================================================
������       :  MP4PixAvgV8x8_c
����         �� Դ���Ĵ�ֱ�����ֵ
����ȫ�ֱ��� �� ��
�������˵�� ��  pu8Cur        ��Դ���ָ��
                 l32CurStride  ��Դ��鲽��
                 pu8Dst        ��Ŀ����ָ��
                 l32DstStride  ��Ŀ���鲽��
                 l32Width      ����ȣ�Ϊ8�ı�����
                 l32Height     ���߶�
����ֵ˵��   �� ��
����˵��     �� ��
======================================================================*/
void MP4PixAvgV8x8_c(const u8* pu8Cur, l32 l32CurStride, u8* pu8Dst, l32 l32Rouding);

/*=====================================================================
������       :  MP4PixAvgC8x8_c
����         �� Դ�������ķ����ֵ
����ȫ�ֱ��� �� ��
�������˵�� ��  pu8Cur        ��Դ���ָ��
                 l32CurStride  ��Դ��鲽��
                 pu8Dst        ��Ŀ����ָ��
                 l32DstStride  ��Ŀ���鲽��
                 l32Width      ����ȣ�Ϊ8�ı�����
                 l32Height     ���߶�
����ֵ˵��   �� ��
����˵��     �� ��
======================================================================*/
void MP4PixAvgC8x8_c(const u8* pu8Cur, l32 l32CurStride, u8* pu8Dst, l32 l32Rouding);

/*=====================================================================
������       :  MP4DCT_c
����         �� 8��8ģ���DCT�任 
����ȫ�ֱ��� �� ��
�������˵�� �� s16* ps16Block   ָ��8��8ģ��
����ֵ˵��   �� ��
����˵��     �� ps16Block��ַ��Ҫ32λ����
======================================================================*/
void MP4DCT_c(s16* ps16Block);

/*====================================================================
������       :  MP4IDCT_c
����         �� 8��8ģ���DCT�任 
����ȫ�ֱ��� �� ��
�������˵�� �� s16* ps16Block   ָ��8��8ģ��
����ֵ˵��   �� ��
����˵��     �� pBlock��ַ��Ҫ32λ����
======================================================================*/
void MP4IDCT_c(s16* ps16Block);

/*=====================================================================
�� �� ���� MP4AddiDCT8x8_c                                           
��    �ܣ� 8x8��DCT�任                                                
�㷨ʵ�֣� ��                                                          
ȫ�ֱ����� ��                                                          
��    ���� ps16Dct        DCT�任ϵ��                                  
           pu8Ref         Ԥ��ͼ��                                     
           pu8Rec         Ŀ��ͼ��                                     
�� �� ֵ�� ��                                                          
======================================================================*/
void MP4AddiDCT8x8_c(s16* ps16DCT, u8* pu8Rec, l32 l32RecStride, u8* pu8Ref, l32 l32RefStride);

/*=====================================================================
�� �� ���� MP4SubDCT8x8_c
��    �ܣ� 8x8��DCT
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16Dct        DCT�任ϵ��
           pu8Src         ԭʼͼ��
           pu8Dst         Ŀ��ͼ��
�� �� ֵ�� �� 
=====================================================================*/
void MP4SubDCT8x8_c(s16* ps16DCT, u8* pu8Src, l32 l32SrcStride, u8* pu8Dst, l32 l32DstStride);

/*=====================================================================
������       :  MP4Deviation16x16_c
����         �� �����ڸ�����ֵ��ƽ��ֵ��ľ���ֵ֮��
����ȫ�ֱ��� �� ��
�������˵�� ��  const u8  *pu8MB     ��ָ����ָ��
                 l32       l32Stride  ����鲽��

����ֵ˵��   �� ����ڸ�����ֵ��ƽ��ֵ��ľ���ֵ֮��
����˵��     �� ��
=====================================================================*/
u32 MP4Deviation16x16_c(const u8 *pu8Cur, l32 l32Stride);

/*====================================================================
������       :  MP4MemCopy8x8_c
����         :  8x8�����ݿ��� 
����ȫ�ֱ��� :  ��
�������˵�� :  u8  *pu8Src        ��Դ��ָ��
                l32  l32SrcStride  ��Դ�鲽��
                u8  *pu8Dst        ��Ŀ���ָ��
                l32  l32DstStride  ��Ŀ��鲽��
����ֵ˵��   :  ��
����˵��     :  ��
====================================================================*/
void MP4MemCopy8x8_c(const u8 *pu8Src, l32 l32SrcStride, u8 *pu8Dst, l32 l32DstStride);

/*====================================================================
�� �� ���� QuantIntra8x8_c
��    �ܣ� 8x8��intra������
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void MP4QuantIntra8x8_c(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32DCScaler, l32 l32QP);

/*====================================================================
�� �� ���� MP4QuantInter8x8_c
��    �ܣ� 8x8��inter������
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
l32 MP4QuantInter8x8_c(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32QP);

/*====================================================================
�� �� ���� MP4DeQuantInter8x8_c
��    �ܣ� 8x8��inter�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void MP4DeQuantInter8x8_c(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32QP);

/*====================================================================
�� �� ���� MP4DeQuantIntra8x8_c
��    �ܣ� 8x8��intra�鷴����
�㷨ʵ�֣� ��
ȫ�ֱ����� ��
��    ���� ps16DctIn        DCT�任����ϵ��
           ps16DCTOut       ���������ϵ��
           l32DCScaler      DCϵ����������
           l32QP            ��������
�� �� ֵ�� �� 
====================================================================*/
void MP4DeQuantIntra8x8_c(s16* ps16DCTIn, s16* ps16DCTOut,  l32 l32DCScaler, l32 l32QP);

/*=============================================================================
�� �� ���� MP4AddiDCTIQuant8x8_c
��    �ܣ� 16x16��DCT�任��Dequant
�㷨ʵ�֣� ��
ȫ�ֱ����� �� 
��    ���� ps16DCTIn     ������ϵ��ָ��
           ps16DCTOut    �����ϵ��ָ��
           pu8Rec        : �ؽ����ŵ�ַ
           l32RecStride  : �ؽ��鲽��
           pu8Ref        ���ο�ͼ��ָ��
           l32RefStride  ���ο�ͼ�񲽳�
           l32Qp         ������ϵ��
           l32IsIntra    ���Ƿ�ΪIntra��(Intra : 1; Inter : 0)
           l32Cbp        ����ǰ���Ƿ���ȫ0��0��ʾ��ȫ0�飬������ȫ0�飩
           l32DcScaler   ��DCϵ������������(Intra��Ż��õ�)
�� �� ֵ�� ��
=============================================================================*/
void MP4AddiDCTIQuant8x8_c(s16* ps16DCTIn, s16* ps16DCTOut, l32 l32QP, u8* pu8Rec, l32 l32RecStride, u8* pu8Ref, l32 l32RefStride, l32 l32IsIntra, l32 l32Cbp, l32 l32DCSalar);

/*=============================================================================
�� �� ���� MP4SubDCTQuant8x8_c
��    �ܣ� 8x8��вDCT��Quant
�㷨ʵ�֣� ��
ȫ�ֱ����� �� 
��    ���� ps16Dct        DCT�任buffer
           pu8Src         ԭʼͼ��
           l32SrcStride   ԭʼͼ�񲽳�
           pu8Dst         �ο�ͼ��
           l32DstStride   �ο�ͼ�񲽳�
           ps16DctOut     ���������buffer
           l32Qp          ����ֵ
           l32IsIntra     ��ǰ���Ƿ���Intra��
           l32DCScaler    ֱ��ϵ������ֵ
�� �� ֵ�� ��
=============================================================================*/
l32 MP4SubDCTQuant8x8_c(s16* ps16DCT, u8* pu8Src, l32 l32SrcStride, u8* pu8Dst, l32 l32DstStride, s16* ps16DCTOut, l32 l32Qp, l32 l32IsIntra, l32 l32DCScalar);

/*=============================================================================
�� �� ��: MP4Interpolate8x8v_c
��    ��: �Բο�ͼ�����ˮƽ��������ز�ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate8x8v_c(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16Stride, u32 u32Num, l32 l32Rouding);

/*=============================================================================
�� �� ��: MP4Interpolate16x16v_c
��    ��: �Բο�ͼ�����ˮƽ��������ز�ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate16x16v_c(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16Stride, u32 u32Num, l32 l32Rouding);

/*=============================================================================
�� �� ��: MP4Interpolate8x8h_c
��    ��: �Բο�ͼ�����ˮƽ��������ذ˳�ͷ��ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate8x8h_c(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16SrcStride, u32 u32Num, l32 l32Rouding);

/*=============================================================================
�� �� ��: MP4Interpolate16x16h_c
��    ��: �Բο�ͼ�����ˮƽ��������ذ˳�ͷ��ֵ
�㷨ʵ��: ��
ȫ�ֱ���: ��
��    ��: pu8Dst              Դָ��(8�ֽڶ���)
		  pu8Src              Ŀ��ָ��
		  s16Sride            ͼ�񲽳�
�� �� ֵ: �� 
=============================================================================*/
void MP4Interpolate16x16h_c(u8 *pu8Dst, s16 s16DstStride, u8 *pu8Src, s16 s16SrcStride, u32 u32Num, l32 l32Rouding);

#define MP4PixAvgH8x8 MP4PixAvgH8x8_c

#define MP4PixAvgV8x8 MP4PixAvgV8x8_c

#define MP4PixAvgC8x8 MP4PixAvgC8x8_c

#define MP4DCT MP4DCT_c

#define MP4IDCT MP4IDCT_c

#define MP4AddiDCT8x8 MP4AddiDCT8x8_c

#define MP4SubDCT8x8 MP4SubDCT8x8_c

#define MP4Deviation16x16 MP4Deviation16x16_c

#define MP4MemCopy8x8 MP4MemCopy8x8_c

#define MP4QuantIntra8x8 MP4QuantIntra8x8_c

#define MP4QuantInter8x8 MP4QuantInter8x8_c

#define MP4DeQuantInter8x8 MP4DeQuantInter8x8_c

#define MP4DeQuantIntra8x8 MP4DeQuantIntra8x8_c

#define MP4AddiDCTIQuant8x8 MP4AddiDCTIQuant8x8_c

#define MP4SubDCTQuant8x8 MP4SubDCTQuant8x8_c

#define MP4Interpolate8x8v MP4Interpolate8x8v_c

#define MP4Interpolate16x16v MP4Interpolate16x16v_c

#define MP4Interpolate8x8h MP4Interpolate8x8h_c

#define MP4Interpolate16x16h MP4Interpolate16x16h_c

#endif

#endif
