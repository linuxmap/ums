/******************************************************************************
ģ����        ��jpegdec_v100
�ļ���        ��jpegdec_v100
����ļ�    ��
�ļ�ʵ�ֹ��ܣ��ӿں�������
����        ��������
�汾        ��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��            �汾        �޸���        �߶���    �޸�����
2008/01/28        1.0            ������                  ����
******************************************************************************/
#ifndef _JPEG_DECODER_PUBLIC_H_
#define _JPEG_DECODER_PUBLIC_H_

#include "algorithmtype.h"
#include "vid_videounit.h"
#include "funclist.h"

#ifdef __cplusplus
extern "C"
{
#endif 

#ifndef CHIP_DM64XPLUS
#define RESTRICT 
#else
#define RESTRICT restrict 
#endif		

/* version information: 1.00(JPEG_MAJOR.JPEG_MINOR) */
#define JPEGDEC_MAJOR  ((u32) 1)
#define JPEGDEC_MINOR  ((u32) 00)
#define JPEGDEC_VERSION ((u32)JPEGDEC_MAJOR << 16 |(u32)JPEGDEC_MINOR)

//������
enum
{
    ERR_VID_JPEGDEC_START_VALUE = (ERR_START_VALUE | ERR_VID_MOD| ERR_VID_JPEGENC_MOD),    //JPEG������������ʼֵ
    ERR_VID_JPEGDEC_OPEN_INPUT_POINT,      //OPEN����ָ�����
    ERR_VID_JPEGDEC_OPEN_MEM_HANDLE,       //�����ڴ�������
    ERR_VID_JPEGDEC_MALLOC_DEC_HANDLE,     //����������������
    ERR_VID_JPEGDEC_MALLOC_MB_BUF,         //�������������ڴ����
    ERR_VID_JPEGDEC_PROC_INPUT_POINT,      //PROCESS����ָ�����
    ERR_VID_JPEGDEC_SETPARAM_INPUT_POINT,  //SETPARAM����ָ�����
    ERR_VID_JPEGDEC_WIDTH_HEIGHT,          //�����ߴ���
    ERR_VID_JPEGDEC_GET_VERSION,           //��ȡ�汾��Ϣ����
    ERR_VID_JPEGDEC_GETSTATUS_INPUT_POINT, //GETSTATUS����ָ�����
    ERR_VID_JPEGDEC_CLOSE_INPUT_POINT,     //CLOSE����ָ�����
    ERR_VID_JPEGDEC_MAX_WIDTH_HEIGHT,      //����ͼ����������
    ERR_VID_JPEGDEC_UNEXPECTED_BYTE,       //û���ҵ�MARK��־
    ERR_VID_JPEGDEC_HEADER_LASTBLOCK,      //�ļ�ͷ�оͰ���������־
    ERR_VID_JPEGDEC_HEADER_SOF0,           //����SOF0����
    ERR_VID_JPEGDEC_HEADER_DRI,            //����DRI����
    ERR_VID_JPEGDEC_DQT_ID,            //����DQT����
    ERR_VID_JPEGDEC_DHT_TYPE,              //����DHT����
    ERR_VID_JPEGDEC_DHT_ID,                //����DHTʱ��ID����
    ERR_VID_JPEGDEC_DHT_LESS_BYTE,         //����DHTʱ��ʱ���ݲ���
    ERR_VID_JPEGDEC_HEADER_SOS,            //����SOS����
    ERR_VID_JPEGDEC_HEADER_LESS_BYTE,      //����ʱ���ݲ���
    ERR_VID_JPEGDEC_SOF0_HEIGHT,           //����SOF0ʱ�߶�Ϊ0
    ERR_VID_JPEGDEC_SOF0_COMNUM,           //����SOF0ʱ����������
    ERR_VID_JPEGDEC_SOF0_COMID,            //����SOF0ʱ����ID���� 
    ERR_VID_JPEGDEC_SOF0_FACTOR,           //����SOF0ʱ�������Ӵ���
    ERR_VID_JPEGDEC_SOF0_QTID,             //����SOF0ʱ������ID����
    ERR_VID_JPEGDEC_SCAN_LESS_BYTE         //����SCANLINEʱ���ݲ��� 
};

l32 JpegDecoderOpen(VideoCodecHandle *ppvDecoder, TDecParam* ptDecParam, void* pvInputMemHandle);
l32 JpegDecoderProcess(VideoCodecHandle pvHandle, TDecInput *ptDecInput, TDecOutput *ptDecOutput);
l32 JpegDecoderClose(VideoCodecHandle pvHandle);
l32 JpegDecoderSetParams(VideoCodecHandle pvHandle, TDecParam* ptDecParam);
l32 JpegDecoderGetStatus(VideoCodecHandle pvHandle, TDecStatusParam* ptEncStatusParam);
l32 JpegDecoderGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);
l32 JpegDecoderDebug(VideoCodecHandle pvHandle, void *pvDecDebug);
l32 JpegDecoderAnalyzeErrorCode(l32 l32ErrorCode, l32 l32BufLen, void* pvErrorCodeInfo);

extern TDecFunction tJpegDec;

#ifdef __cplusplus
};
#endif

#endif
