/******************************************************************************
ģ����	    ��H.261�������
����ļ�	�����е�Դ�ļ�
�ļ�ʵ�ֹ��ܣ�H.261�������ͷ�ļ������ṩ���û�ʹ�õģ����ݰ�������H.261������
              ���õ��ĸ��ֺꡢ���������Լ��ӿں�����ԭ��������
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼:
  ��  ��	  �汾		�޸���		�޸�����
2003.5.30	  1.0        ����         �½�
2003.9.1      2.0        �ܺ�         �ؽ�
******************************************************************************/

#ifndef _H261_CORE_LIB_H_
#define _H261_CORE_LIB_H_

#ifdef __cplusplus
extern "C" {
#endif 

#include "algorithmtype.h"
#include "videocommondefines.h"

#define OPTIMIZE_FOR_INTEL      0
#define OPTIMIZE_FOR_EQUATOR    100

//����ֵ���� 
#define ERR_OK          0
#define ERR_ERROR       -1
#define ERR_NOMEM       -2
#define ERR_BADPARAM    -3

//ͼ���ʽ����
#define FF_CIF      1
#define FF_QCIF     2

//H.261��׼�涨һ֡����������256kbit,��32K byte,һ��RTP��1k byte,�����32��	
#define MAX_PACKET_NUM     32   

typedef void * HH261CODEC;
typedef int RESULT ;

//�������������
typedef struct {
    l32 FrameFormat;
    l32 BitRate;
    l32 IFramePeriod;
    l32 IntraFrame;
    l32 MinQUANT;
    l32 MaxQUANT;
    l32 HasRTPPacketInfo;
	l32 l32FrameRate;
}TH261EncParam;     

//����������/�������
typedef struct {
    u8 *   InputBuf;
    u8 *   OutputBuf;
    l32         OutputBitStreamLength;
    BOOL        IsIntraFrame;
    BOOL        IsEncodeOneBlankFrame;
} TH261EncBuffer;   

//����������/�������
typedef struct {
    u8 *   InputBuf;
    u8 *   OutputBuf;
    l32    InputBitStreamLength;
    l32    OutputFrameFormat;
    BOOL   IsIntraFrame;
    BOOL   IsDoPostProcess;   //�Ƿ�������
	l32	   OutputWidth;	      //ʵ�����ͼ���ȣ����������
	l32	   OutputHeight;	  //ʵ�����ͼ��߶ȣ����������	
} TH261DecBuffer;

//RTP�����Ϣ
typedef  struct H261RTP_HEADER_s
{
   u32      H261Header;	   //packet h261 header
   l32      PacketStart;   //packet start pos(in byte,begins with 0)
   l32      PacketLength;  //packet length(byte)
}TH261RTPPacketInfo;


//����H261�����İ汾��Ϣ
void  GetH261Version(void *pVer, l32 iBufLen, l32 *pVerLen);

//H261�������ĳ�ʼ��
l32  H261EncInit(HH261CODEC * pHandle,TH261EncParam * pEncParam);

//H261����һ֡ͼ��
l32  H261EncEncodeOneFrame(HH261CODEC Handle,TH261EncBuffer * pBuffer);

//�������Ĺر�
void  H261EncFree(HH261CODEC Handle);

l32  H261EncGetParam(HH261CODEC Handle,TH261EncParam * pEncParam);

l32  H261EncSetParam(HH261CODEC Handle,TH261EncParam * pEncParam);


//���뺯���ĳ�ʼ��
l32  H261DecInit(HH261CODEC * pHandle);

//����һ֡ͼ��
l32  H261DecDecodeOneFrame (HH261CODEC Handle,TH261DecBuffer * pBuffer);

//�������Ĺر�
void    H261DecFree(HH261CODEC Handle);


#ifdef __cplusplus
};
#endif 

#endif //_H261_CORE_LIB_H_
