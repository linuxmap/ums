/**                                                                            
*** Copyright (c) 2004-2005 Keda Communication Co.LTD.                         
**/

// Name    : prepostprocess.h 

#ifndef _IMAGE_PREPOSTPROCESS_H_
#define _IMAGE_PREPOSTPROCESS_H_

#include "algorithmtype.h"
#include "videocommondefines.h"

#define  QUALITY  0xf1f1

typedef struct tagImageInfo
{
	uint8_t  *pY;          //ͼ���Y����
	uint8_t  *pU;          //ͼ���U����
	uint8_t  *pV;          //ͼ���V����
	int 	 iWidth;       //ͼ��Ŀ��
	int 	 iHeight;      //ͼ��ĸ߶�
	int	 iYStride;     //ͼ���Y��������
	int      iUVStride;    //ͼ���UV��������
	int	 iType;        //ͼ�������
	int  iQuality;     //�Ƿ���������
}ImageInfo;


//////////huangkui ���///////////////////////////////
typedef struct tagPreProcessType3Handle
{
	uint16_t width;		//output image width
	uint16_t height;	//output iamge height
		
	uint16_t *pref;		//pointer to reference image
	uint8_t *counter_y; //pointer to counter of previous  continous 4*4 block's averaged times
	uint8_t *y_status;	//pointer to average or not table for 4*4 blocks
	uint8_t *u_status;	//pointer to average or not table for 2*2 blocks
	uint8_t *v_status;	//pointer to average or not table for 2*2 blocks
	uint8_t *y2_status;	//pointer to average or not table for 4*4 blocks
	
	uint16_t *mbsad;	//pointer to current image's 4*4 block sad
	uint16_t *mbsadref;	//pointer to reference image's 4*4 block sad
	
 	uint16_t *sumrefprev[16];	//pointer to previous continous 15 image's 4*4 block sad
 	
 	uint16_t *sumrefprevbackup;	//pointer to save free pointer for sumrefprev[16]
		
}PreProcessType3Handle;
///////////////////////////////////////////////////////////////////////////

//����ֵ˵��
/**************************
  
  0   �� �������ò�����ʧ�ܣ�
  1   �� �������ú��� ���ɹ���
  
**************************/

//ͼ����С
int ImageDownSize(ImageInfo *pOld, ImageInfo *pNew);


//ͼ��Ŵ�
int ImageEnlargeSize(ImageInfo *pOld, ImageInfo *pNew);


//Deblock(H263��Mpeg4����)
int ImageDeblock(ImageInfo *pOld, ImageInfo *pNew, int iQuant);
//DeblockVariableQp(H261����)
int ImageDeblockVariableQp(ImageInfo *pImage, int *pQuant);

//Dering
int ImageDering(ImageInfo *pImage, int iQuant);


//RGB��YUV�ĸ�ʽת��
void Generate_yuv2rgb_tables(void);

int RGBtoYUV(ImageInfo *pRGB, ImageInfo *pYUV);

int YUVtoRGB(ImageInfo *pYUV, ImageInfo *pRGB);


//֡���任(�任ǰ���ͼ���Сһ��)
int  FieldtoFrame(ImageInfo *pField, ImageInfo *pFrame);

int FrametoField(ImageInfo *pFrame, ImageInfo *pField);

//��������ת��
int CopyUint8toInt16(uint8_t *pSrc, int16_t *pDest, int iSrcStride, int iDestStride);

int CopyUint8toInt16(uint8_t *pSrc, int16_t *pDest, int iSrcStride, int iDestStride);

int SubUint8toInt16(uint8_t *pSrc, uint8_t *pSrcRef, int16_t *pDest, int iSrcStride, int iSrcRefStride, int iDestStride);

int AddInt16toUint8(int16_t *pSrc, uint8_t *pSrcRef, uint8_t *pDest, int iSrcStride, int iSrcRefStride, int iDestStride);



//����ͼ��
int GenerateTestImage(ImageInfo *pImage, int iTestImageType);

//����������
/*====================================================================
    ������      :    DrawRectangleField420
    ����        ���ڸ�����ͼ���������ο飨ͼ���ʽ420��
    �㷨ʵ��    ��(��ѡ��)
    ����ȫ�ֱ������� 
    �������˵����uint8_t *pYUV  :  ͼ��YUV����
                  int32_t iHeight :  ͼ��ĸ߶�
                  int32_t iWidth  :  ͼ��Ŀ��
    		      int32_t iLeft   �� ��������������
                  int32_t iTop    �� ��������������
                  int32_t iRectHeight �� ��������ĸ߶�
                  int32_t iRectWidth  �� ��������Ŀ��
                  uint8_t  iR : ��������ɫ��R����
                  uint8_t  iG : ��������ɫ��G����
                  uint8_t  iB : ��������ɫ��B����
    ����ֵ˵��  ���������ô��󷵻� ��1�� ���򷵻�1��
====================================================================*/	
int32_t DrawRectangleField420(uint8_t *pYUV, int32_t iHeight, int32_t iWidth, int32_t iLeft,
					  int32_t iTop, int32_t iRectHeight, int32_t iRectWidth, 
					  uint8_t iR, uint8_t iG, uint8_t iB);

/*====================================================================
    ������      ��DrawRectangle422
    ����        ���ڸ�����ͼ���������ο飨ͼ���ʽ422��
    �㷨ʵ��    ��(��ѡ��)
    ����ȫ�ֱ������� 
    �������˵����uint8_t *pYUV  :  ͼ��YUV����
                  int32_t iHeight :  ͼ��ĸ߶�
                  int32_t iWidth  :  ͼ��Ŀ��
    		      int32_t iLeft   �� ��������������
                  int32_t iTop    �� ��������������
                  int32_t iRectHeight �� ��������ĸ߶�
                  int32_t iRectWidth  �� ��������Ŀ��
                  uint8_t  iR : ��������ɫ��R����
                  uint8_t  iG : ��������ɫ��G����
                  uint8_t  iB : ��������ɫ��B����
    ����ֵ˵��  ���������ô��󷵻� ��1�� ���򷵻�1��
====================================================================*/	
int32_t DrawRectangleField422(uint8_t *pYUV, int32_t iHeight, int32_t iWidth, int32_t iLeft,
					  int32_t iTop, int32_t iRectHeight, int32_t iRectWidth, 
					  uint8_t iR, uint8_t iG, uint8_t iB);

void  GetPrePostProcessVersion(void *pVer, int iBufLen, int *pVerLen);

//////////huangkui ���///////////////////////////////
int PreprocessType3Initial(PreProcessType3Handle *pHandle, int width, int height);

int PreprocessType3(uint8_t *p422, uint8_t *p420, PreProcessType3Handle *pHandle);

int PreprocessType3Close(PreProcessType3Handle *pHandle);

int PreprocessType3SetParam(PreProcessType3Handle *pHandle, int width, int height);

//0:fail; 1:succeed
int ImagePostprocess(ImageInfo *ptOldImage, ImageInfo *ptNewImage, int u32Type);

//////////////////////////////////////////////////////////

/*====================================================================
������      �� MotionSurveil
����    	�� ͼ����˶����
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵���� TImageInfo  *ptCurImage  : ָ��ǰ֡ͼ���ָ��
               TImageInfo  *ptPreImage  : ָ��ǰһ֡ͼ���ָ��
			   			 u8 *pu8MotionLevel       : ָ���˶��������ָ��
			   			 														(��ÿ��bit,0��ʾ��ֹ��1��ʾ�˶�)
����ֵ˵��  ���ɹ����� VIDEOSUCCESSFUL��ʧ�ܷ��� VIDEOFAILURE
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾    �޸���     �߶���      �޸�����
08/15/2005  1.0    	zhaobo                   ���� 
====================================================================*/
l32 MotionSurveil(ImageInfo *ptCurImage, ImageInfo *ptPreImage, u8 *pu8MotionLevel);

#endif

