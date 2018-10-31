/******************************************************************************
ģ����	    ��H261��H263��Mpeg4����������
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����һЩ�����Ż��˵ĺ�����ԭ�͡�
              Ϊ����PC��EQUATORƽ̨������޶ȵĹ�����룬����ά��Win32��Equator
              ��������汾���������Ԥ��������ͬƽ̨�ϵĺ������ڵ��ó�����ֻ��
              д�����������壬�������ʲôƽ̨�ϵĺ����ɱ������Զ�ѡ��Ԥ������
              �������ģ�
              ����һ��OPTIMIZE_FOR����������ȡֵ���ֲ�ͬƽ̨��
              OPTIMIZE_FOR_EQUATOR:��EQUATORƽ̨���Ż�
              OPTIMIZE_FOR_EQUATOR_INLINE:��EQUATORƽ̨���Ż�(����inline��ʽ)
              �����û���Ż�(C���԰汾)
              ����ʵ��ʱ����EQUATORƽ̨�ϣ���makefile�м��룺OPTIMIZE_FOR = 100
              ���ߣ�OPTIMIZE_FOR_INLINE = 200��ʵ��inline��ʽ�ĵ���
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼:
  ��  ��	      �汾	    	�޸���		�޸�����
2004.09.07        1.0          ZouWenyi       ����
******************************************************************************/

#ifndef _COMMONLIB_H_
#define _COMMONLIB_H_

#include "algorithmtype.h"

#ifdef _MSC_VER
	//warning C4206: nonstandard extension used : translation unit is empty
	#pragma warning(disable : 4206)
#endif//_MSC_VER

#ifndef ARCH_BLACKFIN_STANDALONE 	//sq 05.6.6
#define abs(x)  ((x) > 0)?(x):(-(x))
#endif
		
//�˶�ʸ��
typedef struct MotionVector
{
    int16_t x;
    int16_t y;    
} TMotionVector;

typedef struct
{
	int32_t		iActQuant;      //act_quant;	
	int32_t		iFrameRate;     //֡��
	int32_t		iTargetRate;    //Ŀ������
	int32_t		iMaxQuant;      //�������ϵ��
	int32_t		iMinQuant;      //��С����ϵ�� 

	int32_t		iTargetFrameSize;

	int32_t		iVbvDelay;
	int32_t		iVopDelay;
	int32_t		iClickPerBit;
	int32_t		iMaxVbvDelay;
	int32_t		iVbvDelayUpperTh;
	int32_t		iVbvDelayLowerTh;
	int32_t		iMidVbvDelay;
	int32_t		iLowVbvDelay;


	int32_t		iRCConstant;
	int32_t		iKp;
	int32_t         iSceneChange;

	int32_t		iFrameLength[25];  //ÿ֡�����ĳ���

	int64_t  	iTotalSize;
	int64_t  	iDecodingTime;
	int64_t 	iTargetBits;
	
	//H261 Liwei Song  7/17/2004
	int32_t         iPreLose;       //֮ǰ��֡��
	int32_t         iLoseFrameNum;  //�����������ò�ͬ�Ķ�֡��Ŀ768��һ֡��384����֡
	
}TRateControl;  //���ʿ���


//���ʿ��Ƴ�ʼ��
int LibRateControlInit(TRateControl *pRateControl, int32_t iTargetRate, int32_t iFrameRate,
					int32_t iMaxQuant, int32_t iMinQuant, BOOL IsLoseFrame);
					
//��ȡ���Ƶ�����ϵ��
int LibGetEstimatedQ(TRateControl *pRateControl);

//��������ϵ��
int LibRateControlGetQ(TRateControl *pRateControl, int32_t iVopType, BOOL IsLoseFrame);
					
//�������ʿ��Ʋ���
int LibRateControlUpdate(TRateControl * pRateControl, int32_t iFrameSize, int32_t iVopType);					
					

//������֡ͼ��������
float  PSNR(uint8_t *pSrcFrame, uint8_t *pRecFrame, int32_t iHeight, int32_t iWidth);
					

//��16��16�����˶�ʸ����ȫ������ʽ(����λΪ������)
int32_t MotionSearch16x16FullPelFullSearch(uint8_t *pRefMB, int32_t iRefStride, uint8_t  *pCurrMB, 
				  int32_t  iCurrStride, int32_t  iSearchMinX, int32_t iSearchMaxX, 
				  int32_t   iSearchMinY, int32_t iSearchMaxY, TMotionVector  *pMV);
				  

//��16��16�����˶�ʸ��������������ʽ(����λΪ������)
int32_t MotionSearch16x16FullPelMVFAST(uint8_t *pRefMB, int32_t iRefStride, uint8_t  *pCurrMB, 
					   int32_t  iCurrStride, int32_t  iSearchMinX, int32_t iSearchMaxX, 
					   int32_t   iSearchMinY, int32_t iSearchMaxY,  TMotionVector  predMV[3],
					   TMotionVector  *pMV);

//��16��16�����˶�ʸ��(����λΪ������)					   
int32_t MotionSearch16x16HalfPel8Points(uint8_t *pRefMB, int32_t iRefStride, uint8_t *pCurrMB, 
                                           int32_t iCurrStride, int32_t iSearchMinX, int32_t iSearchMaxX,
                                           int32_t iSearchMinY, int32_t iSearchMaxY, int32_t iSad, 
                                           int32_t iRounding, TMotionVector *pMV);
                                           

//��8��8����˶�ʸ����ȫ������ʽ(����λΪ������)                                          
int32_t MotionSearch8x8FullPelFullSearch(uint8_t *pRefMB, int32_t iRefStride, uint8_t *pCurrMB, 
                                           int32_t iCurrStride, int32_t iSearchMinX, int32_t iSearchMaxX,
                                           int32_t iSearchMinY, int32_t iSearchMaxY, TMotionVector *pMV);
                                     
      
//��8��8�����˶�ʸ��(����Ϊ������)                                            
int32_t MotionSearch8x8HalfPel8Points(uint8_t *pRefMB, int32_t iRefStride, uint8_t *pCurrMB, 
                                           int32_t iCurrStride, int32_t iSearchMinX, int32_t iSearchMaxX,
                                           int32_t iSearchMinY, int32_t iSearchMaxY, int32_t iSad, 
                                           int32_t iRounding, TMotionVector *pMV);                                          

void MotionSearch16x16FullPelEtiH263( uint8_t *pRefMB, int32_t iRefStride,uint8_t *pCurrMB, 
                                     int32_t iCurrStride,int32_t iSearchMinX, int32_t iSearchMaxX,
                                     int32_t iSearchMinY, int32_t iSearchMaxY, int32_t *pSadOpt,
                                     TMotionVector *pMV, int32_t iQuant);                                           					  

//��ȡ�汾��Ϣ
void  GetCommonLibVersion(void *pVer, int iBufLen, int *pVerLen);

#if  defined(OPTIMIZE_FOR) && (OPTIMIZE_FOR == 100)   //��EQUATOR���Ż�

//QUANAT/DEQUANT
//��8x8��Intra��������
uint32_t QuantIntra_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant);

//��8x8��Inter��������
uint32_t QuantInter_map(const int16_t *pInCoeff,int16_t *pOutCoeff, uint8_t iQuant);

//��8x8��Intra����������
void DeQuantIntra_map(int16_t *pInCoeff,int16_t *pOutCoeff, uint8_t iQuant);

//��8x8��Inter����������
void DeQuantInter_map(int16_t *pInCoeff, int16_t *pOutCoeff, int32_t iQuant);

//��8x8��Intra����������(����ֱ�Ӵ�Vlx���������)
void DeQuantIntraVlx_map(const int16_t *pInCoeff, int16_t *pOutCoeff,const int32_t iQuant);

//��8x8��Inter����������(����ֱ�Ӵ�Vlx���������)
void DeQuantInterVlx_map(const int16_t *pInCoeff, int16_t *pOutCoeff, const int32_t iQuant);

//Mpeg2��8x8��Intra�������� 
int ComlibMpeg2QuantIntra_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iDcScaler, uint8_t iQuant);
 
//Mpeg2��8x8��Inter��������
int ComlibMpeg2QuantInter_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant);

//Mpeg2��8x8��Intra����������
void Mpeg2DeQuantIntra_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t  iDcScaler, uint8_t  iQuant);

//Mpeg2��8x8��Inter����������
void Mpeg2DeQuantInter_map(int16_t  *pInCoeff, int16_t  *pOutCoeff,  uint8_t  iQuant);

//��8x8��Intra����������(����ֱ�Ӵ�Vlx���������)
void Mpeg2DeQuantIntraVlx_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iDcScaler, uint8_t iQuant);

//��8x8��Inter����������(����ֱ�Ӵ�Vlx���������)
void Mpeg2DeQuantInterVlx_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant);




//Mpeg4��8x8��Intra��������
uint32_t ComlibMpeg4QuantIntra_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant, int32_t iDcScaler);

//Mpeg4��8x8��Inter��������
uint32_t ComlibMpeg4QuantInter_map(int16_t *pInCoeff, int16_t * pOutCoeff, int32_t iQuant);

//Mpeg4��8x8��Intra����������
uint32_t Mpeg4DeQuantIntra_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant, int32_t iDcScaler);

//Mpeg4��8x8��Inter����������
void Mpeg4DeQuantInter_map(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant);



//DCT/IDCT
//8��8��DCT�任
void  DCT_map(int16_t* pBlock);

//8��8��DCT�任
void  IDCT_map(int16_t* pBlock);

//SAD
//����16x16ģ��SAD
uint32_t SAD16x16_map(uint8_t *pCurrMB, int32_t iCurrStride,uint8_t *pRefMB, int32_t iRefStride);

//����16x16ģ��SAD
uint32_t SAD8x8_map(const uint8_t *pCurrMB, int32_t iCurrStride, const uint8_t *pRefMB, int iRefStride);


//���˶�ʸ��
void  RowSAD16_map(uint8_t *pCurrMB, int32_t iCurrStride, uint8_t *pRefMB, int32_t iRefStride,
		int32_t *psad_opt, TMotionVector *pmv, int16_t min_x, int16_t min_y);

//DEVIATION
//��16��16����ڸ�����ֵ��ƽ��ֵ��ľ���ֵ֮��
int32_t DeviationMB_map(const uint8_t *pMB, int32_t iStride);

//Interpolation
//16��16����ˮƽ�����ֵ
void InterpolateHalfPelH16x16_map(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//16��16���Ĵ�ֱ�����ֵ
void InterpolateHalfPelV16x16_map(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst,  int32_t iDstStride, int32_t iRounding);

//16��16���ĶԽǷ����ֵ
void InterpolateHalfPelHV16x16_map(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//8��8���ˮƽ�����ֵ
void InterpolateHalfPelH8x8_map(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//8��8��Ĵ�ֱ�����ֵ
void InterpolateHalfPelV8x8_map(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//8��8��ĶԽǷ����ֵ
void InterpolateHalfPelHV8x8_map(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);


//QUANT/DEQUANT
#define	  QuantIntra       QuantIntra_map    
#define   QuantInter       QuantInter_map    
#define   DeQuantIntra     DeQuantIntra_map  
#define   DeQuantInter     DeQuantInter_map  
#define	  DeQuantIntraVlx  DeQuantIntraVlx_map  
#define   DeQuantInterVlx  DeQuantInterVlx_map
 
//MPEG2QUANT/MPEG4DEQUANT  
#define   Mpeg2QuantIntra        ComlibMpeg2QuantIntra_map
#define   Mpeg2QuantInter        ComlibMpeg2QuantInter_map
#define   Mpeg2DeQuantIntra      Mpeg2DeQuantIntra_map
#define   Mpeg2DeQuantInter      Mpeg2DeQuantInter_map
#define   Mpeg2DeQuantIntraVlx   Mpeg2DeQuantIntraVlx_map
#define   Mpeg2DeQuantInterVlx   Mpeg2DeQuantInterVlx_map
 
//MPEG4QUANT/MPEG4DEQUANT
#define   Mpeg4QuantIntra   ComlibMpeg4QuantIntra_map
#define   Mpeg4QuantInter   ComlibMpeg4QuantInter_map  
#define   Mpeg4DeQuantIntra Mpeg4DeQuantIntra_map 
#define   Mpeg4DeQuantInter Mpeg4DeQuantInter_map

//DCT/IDCT
#define   DCT        DCT_map  
#define   IDCT       IDCT_map 

//SAD
#define   SAD16x16   SAD16x16_map  
#define   SAD8x8     SAD8x8_map
#define   RowSAD16   RowSAD16_map

//DEVIATIONAMB
#define    DeviationMB     DeviationMB_map

//INTERPOLATION
#define     InterpolateHalfPelH16x16    InterpolateHalfPelH16x16_map
#define     InterpolateHalfPelV16x16    InterpolateHalfPelV16x16_map
#define     InterpolateHalfPelHV16x16   InterpolateHalfPelHV16x16_map
#define     InterpolateHalfPelH8x8      InterpolateHalfPelH8x8_map 
#define     InterpolateHalfPelV8x8      InterpolateHalfPelV8x8_map
#define     InterpolateHalfPelHV8x8     InterpolateHalfPelHV8x8_map



#elif defined(COMMONLIB_INLINE)   //����inline��ʽ

inline_declare
{
		
	#include "../../../30-video/CommonLib/source/equator/DCT_IDCT.c"
	#include "../../../30-video/CommonLib/source/equator/DeviationMB.c"
	#include "../../../30-video/CommonLib/source/equator/QuantDeQuant.c"
	#include "../../../30-video/CommonLib/source/equator/SAD.c"
	#include "../../../30-video/CommonLib/source/equator/Interpolation.c"


}  

#else       //û���Ż�(C���԰汾)

//QUANAT/DEQUANT
//��8x8��Intra��������
uint32_t QuantIntra_c(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant);

//��8x8��Inter��������
uint32_t QuantInter_c(const int16_t *pInCoeff,int16_t *pOutCoeff, uint8_t iQuant);

//��8x8��Intra����������
void DeQuantIntra_c(int16_t *pInCoeff,int16_t *pOutCoeff, uint8_t iQuant);

//��8x8��Inter����������
void DeQuantInter_c(int16_t *pInCoeff, int16_t *pOutCoeff, int32_t iQuant);



//Mpeg4��8x8��Intra��������
uint32_t ComlibMpeg4QuantIntra_c(const int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant, uint8_t iDcScaler);

//Mpeg4��8x8��Inter��������
uint32_t ComlibMpeg4QuantInter_c(const int16_t *pInCoeff, int16_t * pOutCoeff, uint8_t iQuant);

//Mpeg4��8x8��Intra����������
void Mpeg4DeQuantIntra_c(const int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant, uint8_t iDcScaler);

//Mpeg4��8x8��Inter����������
void Mpeg4DeQuantInter_c(const int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant);



//Mpeg2��8x8��Intra��������
int ComlibMpeg2QuantIntra_c(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iDcScaler, uint8_t iQuant);

//Mpeg2��8x8��Inter��������
int ComlibMpeg2QuantInter_c(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t iQuant);

//Mpeg2��8x8��Intra����������
void Mpeg2DeQuantIntra_c(int16_t *pInCoeff, int16_t *pOutCoeff, uint8_t  iDcScaler, uint8_t  iQuant);

//Mpeg2��8x8��Inter����������
void Mpeg2DeQuantInter_c(int16_t  *pInCoeff, int16_t  *pOutCoeff,  uint8_t  iQuant);



//DCT/IDCT
//8��8��DCT�任
void  DCT_c(int16_t* pBlock);

//8��8��DCT�任
void  IDCT_c(int16_t* pBlock);

//SAD
//����16x16ģ��SAD
uint32_t SAD16x16_c(uint8_t *pCurrMB, int32_t iCurrStride,uint8_t *pRefMB, int32_t iRefStride);

//����16x16ģ��SAD
uint32_t SAD8x8_c(uint8_t *pCurrMB,int32_t iCurrStride, uint8_t *pRefMB, int32_t iRefStride);


//DEVIATION
//��16��16����ڸ�����ֵ��ƽ��ֵ��ľ���ֵ֮��
int32_t DeviationMB_c(const uint8_t *pMB, int32_t iStride);

//Interpolation
//16��16����ˮƽ�����ֵ
void InterpolateHalfPelH16x16_c(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//16��16���Ĵ�ֱ�����ֵ
void InterpolateHalfPelV16x16_c(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst,  int32_t iDstStride, int32_t iRounding);

//16��16���ĶԽǷ����ֵ
void InterpolateHalfPelHV16x16_c(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//8��8���ˮƽ�����ֵ
void InterpolateHalfPelH8x8_c(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//8��8��Ĵ�ֱ�����ֵ
void InterpolateHalfPelV8x8_c(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);

//8��8��ĶԽǷ����ֵ
void InterpolateHalfPelHV8x8_c(const uint8_t *pSrc, int32_t iSrcStride, uint8_t *pDst, int32_t iDstStride, int32_t iRounding);


//QUANT/DEQUANT
#define	  QuantIntra       QuantIntra_c    
#define   QuantInter       QuantInter_c    
#define   DeQuantIntra     DeQuantIntra_c  
#define   DeQuantInter     DeQuantInter_c  

//MPEG4QUANT/MPEG4DEQUANT
#define   Mpeg4QuantIntra   ComlibMpeg4QuantIntra_c
#define   Mpeg4QuantInter   ComlibMpeg4QuantInter_c  
#define   Mpeg4DeQuantIntra Mpeg4DeQuantIntra_c 
#define   Mpeg4DeQuantInter Mpeg4DeQuantInter_c


//MPEG2QUANT/MPEG2DEQUANT
#define  Mpeg2QuantIntra     ComlibMpeg2QuantIntra_c
#define  Mpeg2QuantInter     ComlibMpeg2QuantInter_c
#define  Mpeg2DeQuantIntra   Mpeg2DeQuantIntra_c
#define  Mpeg2DeQuantInter   Mpeg2DeQuantInter_c


//DCT/IDCT
#define   DCT        DCT_c  
#define   IDCT       IDCT_c 

//SAD
#define   SAD16x16   SAD16x16_c  
#define   SAD8x8     SAD8x8_c

//DEVIATIONAMB
#define    DeviationMB     DeviationMB_c

//INTERPOLATION
#define     InterpolateHalfPelH16x16    InterpolateHalfPelH16x16_c
#define     InterpolateHalfPelV16x16    InterpolateHalfPelV16x16_c
#define     InterpolateHalfPelHV16x16   InterpolateHalfPelHV16x16_c
#define     InterpolateHalfPelH8x8      InterpolateHalfPelH8x8_c 
#define     InterpolateHalfPelV8x8      InterpolateHalfPelV8x8_c
#define     InterpolateHalfPelHV8x8     InterpolateHalfPelHV8x8_c

  

#endif

#endif // _COMMON_H_ 

