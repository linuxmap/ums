#ifndef _H262_PUBLIC_H_
#define _H262_PUBLIC_H_

#include "algorithmtype.h"

/* version information: 0.50(F262_MAJOR.F262_MINOR) */
#define F262_MAJOR  ((u32) 0)
#define F262_MINOR  ((u32) 50)
#define F262_VERSION ((u32)F262_MAJOR << 16 |(u32)F262_MINOR)

#define USE_INTER16x8   1
#define USE_PREFERSPEED 2

#ifdef __cplusplus
extern "C"
{
#endif  
    
    typedef struct
    {
        l32 l32Width;
        l32 l32Height;
        u32 u32CpuFreq;
        l32 l32BNum;
        l32 l32GOPLen;
        l32 l32Bitrate;
        l32 l32Framerate;
        l32 l32InitQP;
        l32 l32MinQP;
        l32 l32MaxQP;
        l32 l32EnableStat;
        l32 l32TopFieldFirst;
        l32 l32DCScaler;
        l32 l32Flags;
        s8* ps8RecName;
    } TF262Param;
    
    typedef struct {
        u8	*pu8YUV420;         //����YUV���ݻ��������û��ڵ��ý�����ǰ���з���
        u32	u32YUVLen;          //ԭʼͼ�񻺳�������
        u8	*pu8BitStream;	    //����֡�����������
        u32	u32BitstreamLen;    //���������������
        u32	u32ReturnWidth;     //���뷵��ͼ��֡���
        u32	u32ReturnHeight;    //���뷵��ͼ��֡����
        l32	l32FrameType;       //����֡����
    } TF262EncFramePara;
    
        
    l32 F262EncInit(void **ppvHandle, TF262Param* ptParam);

    l32 F262EncFrame(void *pvHandle, TF262EncFramePara *ptEncFramePara);

    void F262EncClose(void *pvHandle);
    
    l32 F262EncoderSetEncParams(void* pvHandle, TF262Param* ptParam);

    void GetF262EncoderVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);
    
#ifdef __cplusplus
};
#endif





#endif
