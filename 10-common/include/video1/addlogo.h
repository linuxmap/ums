#ifndef _ADDLOGO_H_
#define _ADDLOGO_H_
/*
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef short          int16_t;
typedef unsigned long  n32u;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long LONG;
typedef unsigned char  BYTE;
#define uint32_t	unsigned int
#define int32_t		int

#define FALSE 0
#define TRUE  1
*/


typedef struct tagLogoInfo
{
  uint8_t   *pFg;                      //ǰ��ͼ������ָ���ַ
  uint8_t   *pAlphaY;                  //ǰ��ͼ��Y������alphaͨ��ָ��
  uint8_t   *pBetaY;                   //��Ӧ����ͼ����ڲ�ϵ��
  uint8_t   *pAlphaUV;                 //ǰ��ͼ��UV������alphaͨ��ָ��
  uint8_t   *pBetaUV;                  //��Ӧ����ͼ����ڲ�ϵ�� 
  uint16_t  nWidth, nHeight;           //ǰ��ͼ��Ŀ�Ⱥ͸߶�
  uint8_t  byTransparency;             //ǰ��ͼ��͸��ϵ��
  int16_t   sTop,sLeft;                //ǰ��ͼ��λ��ƫ��
  int16_t	sTopCut, sBottomCut, sLeftCut, sRightCut;  	//ǰ��ͼ���ϡ��²�ȥ����
} TLogoInfo;


typedef struct tagImageParam
{
  uint8_t   *pImageData;      		//ͼ��YUV����         
  int nWidth;				//ͼ����
  int nHeight;          		//ͼ��߶�
  int  nStride;				//ͼ�񲽳�
} TImageParam;


void ResCreate (uint8_t *YImg, uint8_t *UImg, uint8_t *VImg);
void ColorCreate (uint8_t *YImg, uint8_t *UImg, uint8_t *VImg);
void HueCreate (uint8_t *YImg, uint8_t *UImg, uint8_t *VImg);

//��ȡ�汾��Ϣ
void GetZoomImageVersion(void *pVer, int iBufLen, int *pVerLen);


//BMPת����YUV������ALPHA����
int ConvertBMPToYUVAndAlpha(uint8_t *pLogoBmp, TLogoInfo *pFgInfo, int nYUVType, uint8_t back_r, uint8_t back_g, uint8_t back_b, uint8_t transparency);



//��ͼ��
//void AddLogo(TImageParam *pBackgroundImage, TLogoInfo *pForegroundInfo, int nYUVType);
int AddLogo(TImageParam *pBackgroundImage, TLogoInfo *pForegroundInfo, int nTop, int nLeft, int nYUVType);


//ͼ����С�󸲸ǵ���ͼ��
//nZoomOutType 1:1/4; 2:1/9; 3:1/16; 4:1/2(horizontal) 5:1/2(vertical) 6:4/9 7:9/16 8:1/25 9:3/4(vertical)
int ZoomOutImageAndMerge(int nZoomOutType, TImageParam *pBackgroundImage, TImageParam *pForegroundImage, int nTop, int nLeft, int nIsFrame);

//422��ʽ720*576ͼ����С�󸲸ǵ���ͼ��   05.2.20 sq add
//s32ZoomOutType 1:1/4; 2:1/9; 3:1/16
int ZoomOutImageAndMerge422Field(int s32ZoomOutType, TImageParam *ptBackgroundImage, TImageParam *ptForegroundImage, int s32Top, int s32Left);
//sq end

//��Сͼ����ԭͼ1/4
void ZoomOutImageQuarter(int nOldWidth, int nOldHeight, unsigned char *pOldImageData, unsigned char *pNewImageData);

//��Сͼ����ԭͼ1/9
void ZoomOutImageNinth(int nOldWidth, int nOldHeight, unsigned char *pOldImageData, unsigned char *pNewImageData);

//��Сͼ����ԭͼ1/16
void ZoomOutImageSixteenth(int nOldWidth, int nOldHeight, unsigned char *pOldImageData, unsigned char *pNewImageData);

//Сͼ�񸲸Ǵ�ͼ��
/*====================================================================
    ������      ��MergePicture
    ����        ����Сͼ��YUV420�����ǵ���ͼ��YUV420����ָ��λ�ã�����ʽ��
    �㷨ʵ��    ��(��ѡ��)
    ����ȫ�ֱ�������
    �������˵����TImageParam *pBackgroundImage: ����ͼ��ָ�� 
		  TImageParam *pForegroundImage: ǰ��ͼ��ָ��
    		  uint16_t fgTop�� Сͼ��ֱ����ƫ��
    		  uint16_t fgLeft��Сͼ��ˮƽ����ƫ��
			  int nIsFrame���Ƿ�Ϊ֡��ʽ
    		  uint16_t fgTopOffset: Сͼ���ϱ�ɾ������
    		  uint16_t fgLeftOffset��Сͼ�����ɾ������
    		  uint16_t fgBottonOffset:Сͼ���±�ɾ������
    		  uint16_t fgRightOffset:Сͼ���ұ�ɾ������
    ����ֵ˵��  ����
====================================================================*/
void MergePicture(TImageParam *pBackgroundImage,TImageParam *pForegroundImage, uint16_t fgTop, uint16_t fgLeft, int nIsFrameFg, int nIsFrameBg, int fgTopOffset, int fgLeftOffset,
				uint16_t fgBottonOffset, uint16_t fgRightOffset);

void de_interlacing_map(unsigned char *pYUV, int width, int height, int stride);

//����һ���˶�������֡
void TestFrameGenerator(int nColumnWidth, int nSpeed, int nSkipInterval, int nSkipCount, 
		unsigned char *pYUV, int nHeight, int nWidth, unsigned char *pBuffer);
/*************
����һ������һ֡
int nColumnWidth ��������ȣ�������Ϊ20��
int nSpeed  �������ٶȣ�������Ϊ8��
int nSkipInterval ������֡������Ϊ0��ʾ����֡���˶�������
int nSkipCount ��֡���
unsigned char *pYUV ���ͼ������
int nHeight ͼ��߶�
int nWidth ͼ����
unsigned char *pBuffer ���棨720*576*3/2 byte��
*************************/







#endif
