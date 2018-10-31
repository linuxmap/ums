#ifndef _H263DEC_H_
#define _H263DEC_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "algorithmtype.h"
#define DECODE_EXCLUDE_VGA 0x0001
#define DECODE_INCLUDE_VGA 0x0000
#define SF_SQCIF                        1  // 001 
#define SF_QCIF                         2  // 010 
#define SF_CIF                          3  // 011 
#define SF_4CIF                         4  // 100 
#define SF_16CIF                        5  // 101 
#define SF_CUSTOM                       6  // 110 
#ifndef RTPBUFFERSIZE
#define RTPBUFFERSIZE 3076
#endif
#ifdef _LINUX_
	typedef enum
	{
		H263DECDRV_OK,
			H263DECDRV_ERROR,
			H263DECDRV_NOMEM,
			H263DECDRV_BADFMT,
			H263DECDRV_WRONG_VERSION,	
			H263DECDRV_KERNEL_MODULE_PROBLEMS,	
	}H263DecDrvError_t;
	
#define H263DECERROR		H263DECDRV_ERROR
#define H263DECOK		    H263DECDRV_OK
#else
#define H263DecDrvError_t    l32 
#define H263DECOK  0
#define H263DECERROR  -1
#endif
	typedef void *H263DecHandle;
	typedef struct 
	{
		u8	*pu8BitStream;		//�������H263һ֡ͼ�������������
		u32	u32YUVLen;          //�����һ֡YUVͼ��ĳ��ȣ��ڰѽ�����YUVͼ�����ʱ�õ�
		u8	*pu8YUV420;			//����YUV���ݻ��������û��ڵ��ý�����ǰ���з���
		u32	u32BitstreamLen;	//�������H263һ֡ͼ�����������
		s16  s16PictureType;    //����֡��ͼ������(I֡����P֡)
		l32  s32Height;         //��ǰ���ڽ����ͼ��ĸ߶�
		l32  s32Width;          //��ǰ���ڽ����ͼ��Ŀ��
		l32 s32DecodeType;       // ���� DECODE_EXCLUDE_VGA: ��vga����  0:vga ����
		l32 s32PostProcess;      // 1: ���� 0: ��
	} TH263DecFramePara;
	
	typedef struct 
	{
		s16 s16PictureType; //����֡��ͼ������(I֡����P֡)
		l32 s32Width;       //��ǰ���ڽ����ͼ��Ŀ��
		l32 s32Height;      //��ǰ���ڽ����ͼ��Ŀ��
		
	}TH263DecFrameHeader;
	
    //H263��������ʼ��
    H263DecDrvError_t H263DecoderInit(void **ppvH263DecHandle,TH263DecFramePara *ptH263DecFramePara);
	
    //H263����һ֡ͼ��
    H263DecDrvError_t H263DecodeOneFrame(void *pvH263DecHandle,TH263DecFramePara *ptH263DecFramePara);
		
    //�ͷ�H263��������Դ
    H263DecDrvError_t H263DecoderClose(void *pvH263DecHandle);
#ifdef __cplusplus
}
#endif 

#endif
