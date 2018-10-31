/******************************************************************************
ģ����	    �� VIDEOUNIT                
�ļ���	    �� videounit.h
����ļ�	�� videounit.c��
�ļ�ʵ�ֹ��ܣ� ��������������
---------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
12/27/2006  1.0          �Բ�                  ����
**************************************************************************************/
#ifndef _VIDEOUNIT_H_
#define _VIDEOUNIT_H_

#include "algorithmtype.h"
#include "videodefines.h"
#include "imageunit.h"

#define VideoCodecHandle  void*

typedef struct
{
    void *pvDMAHandle;         //DMA���
    void *pvInternalMem;       //Ƭ��SRAM����ʼ��ַ
    l32  l32InternalMemSize;   //Ƭ��SRAM�Ĵ�С
    void *pvExternalMem;       //Ƭ��DDR����ʼ��ַ
    l32  l32ExternalMemSize;   //Ƭ��DDR�Ĵ�С
} TMemHandle;  //��¼�ռ��С

typedef struct tEncParam
{
	u32		u32EncType;				//����������
	l32		l32EncFrameRate;		//֡��
	l32		l32EncBitRate;			//���ʣ�bps��
	l32		l32EncMinQP;			//��С��������
	l32		l32EncMaxQP;			//�����������
	l32		l32EncIFrameInterval;	//I֡���������I֡��P��B֡����
	l32		l32EncPacketMode;		//���ģʽ
	l32		l32EncWidth;			//������
	l32		l32EncHeight;			//����߶ȣ����=0&�߶�=0��ʾ����Ӧ��Ŀǰ��������mpeg4��
	l32		l32EncFrameDropRate;	//����������֡�ʣ�0��ʾ����֡���ٶ����ȣ���0��ʾ�ж�֡���������ȣ�����Ϊ10�ı�������10%Ϊ��λ��
	u32		u32EncCycles;			//����һ֡������������Ŀǰ���ڴ������map����Ƶ(����Ϊ��λ)
	l32		l32EncYUVType;			//����YUV���ͣ�420��422��444����Ŀǰ��֧�ֶ�420ͼ����룬�˲���û���õ�
    l32		l32EncLimitation;		//���������ƣ���
    TMemHandle tMemHandle;          //��������Ҫ�õ����ڴ�ռ�ṹ��
	u32		u32EncReserved;			//��������
}TEncParam;	//�����ʼ������


typedef struct tEncoderInput
{
	TLogo		*aptLogo[MAX_LOGOS_IN_IMAGE+1];			//ͼ�꣨��NULLΪ������־��
	TBanner		*aptBanner[MAX_BANNERS_IN_IMAGE+1];		//�������NULLΪ������־��

	TImageInfo	*ptInEncImage;		//�����������ͼ����Ϣ
	u32		u32EncKeyFrame;			//����֡���ͣ����룩 1: ǿ�Ʊ�I֡  0���������Զ�
	u32	   	u32EncOutputPSNR;		//�Ƿ����PSNRֵ	 1: ����  0��������
	u8		*pu8EncMotionInfo;		//�˶���Ϣ����ʹ�ñ�����ΪNULL��44x36��ȼ�0~9��
	u32 	u32EncMotionInfoLen;	//�˶���Ϣ����
	l32		l32EncSkipPreprocess;	//ǰ������, ���ⲿ�����Ƿ���ǰ����
	u32		u32EncReserved;			//��������	
}TEncoderInput;		//�����������


typedef struct tEncoderOutput
{
	u8		*pu8EncBitstream;		//�����������
	l32		l32EncBitstreamLen;		//�����������
	l32		l32EncIsKeyFrame;		//����֡���ͣ������ 1: �������I֡  0���������P֡
	u32		l32EncWidth;			//ʵ�ʱ�����
	u32		l32EncHeight;			//ʵ�ʱ���߶�
	l32		l32EncMotionInfoValid;	//�˶���Ϣ�Ƿ���Ч
	u32		u32EncReserved;			//��������	
    //����Ϊ���Խӿ�
    u8      *pu8Pp2encImage;        //ǰ����ѹ������������ͼ��

}TEncoderOutput;		//�����������


typedef struct tDecParam
{
	u32		u32DecType;				 //����������
	l32		l32DecPacketMode;		 //���ģʽ
	l32		l32DecYUVType;			 //�������YUV���ͣ�420��422��
	u32		u32DecCycles;			 //����һ֡������������Ŀǰ���ڴ������DSP����Ƶ(����Ϊ��λ)
	l32		l32DecWidth;			 //����ͼ����(��ѯ״̬ʹ��)
	l32		l32DecHeight;			 //����ͼ��߶�(��ѯ״̬ʹ��)
    l32     l32DecMaxWidth;          //����ͼ��������
    l32     l32DecMaxHeight;         //����ͼ������߶�
    TMemHandle tMemHandle;           //��������Ҫ�õ����ڴ�ռ�ṹ��
	u32		u32DecReserved;			 //��������
}TDecParam;		//�����ʼ������


typedef struct tDecoderInput
{
	u8			*pu8DecBitstream;	//������������
	u32			u32DecBitstreamLen;	//������������
	TLogo		*aptLogo[MAX_LOGOS_IN_IMAGE+1];			//ͼ�꣨��NULLΪ������־��
	TBanner		*aptBanner[MAX_BANNERS_IN_IMAGE+1];		//�������NULLΪ������־��
	u8			*pu8DecMotionInfo;	//�˶���Ϣ����ʹ�ñ�����ΪNULL��
	u32			u32DecMotionInfoLen;//�˶���Ϣ����
	u32         u32DecPostProcess;	//�Ƿ������� 1���� 0����
	u32			u32DecReserved;		//��������	
}TDecoderInput;		//�����������


typedef struct tDecoderOutput
{
	TImageInfo	*ptDecOutImage;		//���������ͼ�����Ϣ
    l32		l32DecWidth;			//����ͼ����
	l32		l32DecHeight;			//����ͼ��߶�
	l32		l32DecIsKeyFrame;		//����֡����
	u32		u32DecConsumedCycles;	//��������������
	l32		l32DecMotionInfoValid;	//�˶���Ϣ�Ƿ���Ч
	u32		u32DecReserved;			//��������		
    //����Ϊ���Խӿ�
    u8      *pu8Decoded;	        //���������ԭʼͼ��
}TDecoderOutput;			//�����������


/*====================================================================
������		��	VideoUnitEncoderOpen
����		��	��ʼ��������
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
              	ptEncParam:		�����ʼ������              
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
�������ر�˵����Ŀǰǰ��������֧��420��ʽ��
                Ŀǰ�������б������ں˵�ͼ��ͳһΪ420��ʽ��
====================================================================*/
l32 VideoUnitEncoderOpen(VideoCodecHandle *ptHandle, TEncParam *ptEncParam);


/*====================================================================
������		��	VideoUnitEncoderProcess
����		��	����һ֡ͼ��
�㷨ʵ��	��	width and height is multiple of 8 are supported
����ȫ�ֱ�����	��
�������˵����	ptHandle:		���������
             	ptEncoderInput:	�����������
             	ptOutputHandle:	�������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ�ܣ�VIDEOSKIP������
====================================================================*/
l32 VideoUnitEncoderProcess(VideoCodecHandle ptHandle, TEncoderInput *ptEncoderInput, TEncoderOutput *ptEncoderOutput);


/*====================================================================
������		��	VideoUnitEncoderClose
����		��	�رձ�����
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoUnitEncoderClose(VideoCodecHandle ptHandle);


/*====================================================================
������		��	VideoUnitEncoderSetParam
����		��	���ñ���������
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
				ptEncParam:		�������ò���
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
�������ر�˵����Ŀǰ���øú����ɸı�Ĳ��������������Ⱥ͸߶ȣ�����ı�
                ����ͼ��Ŀ�ߣ����ȹر�ԭ���������ٰ��µĿ�߳�ʼ���µı�����
====================================================================*/
l32 VideoUnitEncoderSetParam(VideoCodecHandle ptHandle, TEncParam *ptEncParam);


/*====================================================================
������		��	VideoUnitEncoderGetStatus
����		��	��ȡ����������״̬
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
				ptEncParam:		����������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoUnitEncoderGetStatus(VideoCodecHandle ptHandle, TEncParam *ptEncParam);


/*====================================================================
������		��	VideoUnitEncoderDumpStatus
����		��	��ӡ��������Ϣ
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoUnitEncoderDumpStatus(VideoCodecHandle ptHandle);

/*====================================================================
������		: 	VideoUnitEncoderGetVersion
����		��	�������ӿڰ汾��Ϣ
�㷨ʵ��	��	��
����ȫ�ֱ�����	pvVer:			�������
				l32BufLen:		���泤��
				pl32VerLen:		��Ϣ����
				u32EncoderType:	����������
�������˵����	��
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ�ܡ�              
====================================================================*/
l32 VideoUnitEncoderGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32EncoderType);


/*====================================================================
������		��	VideoUnitDecoderOpen
����		��	��ʼ��������
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle   :  ���������
              	ptDecParam :  �����ʼ������              
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
�������ر�˵����Ŀǰǰ��������֧��420��ʽ��
                Ŀǰ�������б������ں˵�ͼ��ͳһΪ420��ʽ��
====================================================================*/
l32 VideoUnitDecoderOpen(VideoCodecHandle *ptHandle, TDecParam *ptDecParam);


/*====================================================================
������		��	VideoUnitDecoderProcess
����		��	����һ֡ͼ��
�㷨ʵ��	��	width and height is multiple of 8 are supported
����ȫ�ֱ�����	��
�������˵����	ptHandle       :  ��������ŵ�ַ
             	ptDecoderInput :  �����������
             	ptOutputHandle :  �������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ�ܣ�VIDEOSKIP������
====================================================================*/
l32 VideoUnitDecoderProcess(VideoCodecHandle ptHandle, TDecoderInput *ptDecoderInput, TDecoderOutput *ptDecoderOutput);


/*====================================================================
������		��	VideoUnitDecoderClose
����		��	�رս�����
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoUnitDecoderClose(VideoCodecHandle ptHandle);


/*====================================================================
������		��	VideoUnitDecoderSetParam
����		��	���ý���������
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle   :  ���������
				ptDecParam :  �������ò���
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
�������ر�˵����Ŀǰ���øú����ɸı�Ĳ��������������Ⱥ͸߶ȣ�����ı�
                ����ͼ��Ŀ�ߣ����ȹر�ԭ���������ٰ��µĿ�߳�ʼ���µĽ�����
====================================================================*/
l32 VideoUnitDecoderSetParam(VideoCodecHandle ptHandle, TDecParam *ptDecParam);


/*====================================================================
������		��	VideoUnitDecoderGetStatus
����		��	��ȡ����������״̬
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
				ptDecParam:		����������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoUnitDecoderGetStatus(VideoCodecHandle ptHandle, TDecParam *ptDecParam);


/*====================================================================
������		��	VideoUnitDecoderDumpStatus
����		��	��ӡ��������Ϣ
�㷨ʵ��	��	��
����ȫ�ֱ�����	��
�������˵����	ptHandle:	���������
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoUnitDecoderDumpStatus(VideoCodecHandle ptHandle);


/*====================================================================
������		: 	VideoUnitDecoderGetVersion
����		��	�������ӿڰ汾��Ϣ
�㷨ʵ��	��	��
����ȫ�ֱ�����	pvVer:			�������
				l32BufLen:		���泤��
				pl32VerLen:		��Ϣ����
				u32DecoderType:	����������
�������˵����	��
�������˵����	��
����ֵ˵��  ��	VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��              
====================================================================*/
l32 VideoUnitDecoderGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32DecoderType);

#endif	//_VIDEOUNIT_H_
