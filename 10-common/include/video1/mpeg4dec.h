/* 
 * Brovic Technologies Co., Ltd.  
 *  Copyright (c)2001-2002 
 *  
 *  http://www.brovic.com 
 */ 
#ifndef _MPEG4DEC_H_
#define _MPEG4DEC_H_

#include "algorithmtype.h"

#ifdef __cplusplus
extern "C" {
#endif 

// mp4v_dec return values
#ifdef _LINUX_
typedef enum
{
	MP4DECDRV_OK,
	MP4DECDRV_ERROR,
	MP4DECDRV_NOMEM,
	MP4DECDRV_NOHEAD,
	MP4DECDRV_BADFMT,
	MP4DECDRV_MEMFAIL,
	MP4DECDRV_INITFAIL,
	MP4DECDRV_EXIT,
	MP4DECDRV_WRONG_VERSION,
	MP4DECDRV_KERNEL_MODULE_PROBLEMS,	
}TMp4DecDrvError_t;

#define DEC_OK			    MP4DECDRV_OK
#define	DEC_MEMORY		    MP4DECDRV_NOMEM
#define DEC_NOHEAD          MP4DECDRV_NOHEAD
#define DEC_WRONGVERSION    MP4DECDRV_WRONG_VERSION
#define DEC_BAD_FORMAT      MP4DECDRV_BADFMT

#define DEC_MEM_FAIL		MP4DECDRV_MEMFAIL
#define DEC_INIT_FAIL		MP4DECDRV_INITFAIL
#define DEC_EXIT			MP4DECDRV_EXIT
#else

//������
enum
{
    DEC_OK,                               //success
    ERROR_INIT_MEM = 0x1000,              //init mem fail
    ERROR_MALLOC_MEM,                     //malloc mem fail
    ERROR_FREE_MEM,                       //free mem fail
    ERROR_ALLOC_DS,                       //alloc ds fail
    ERROR_INVALID_PARAMETER,              //invlid parameter
    ERROR_DEBLOCK,                        //deblock error
    ERROR_DERING,                         //dering error
    ERROR_UNSUPPORT_VOTYPEID = 0x8000,    //video_object_type_indication
    ERROR_UNSUPPORT_SHAPE,                //video_object_layer_shape
    ERROR_UNSUPPORT_OBMC,                 //obmc
    ERROR_UNSUPPORT_SPRITE,               //sprite
    ERROR_UNSUPPORT_COMPLXES,             //complexity_estimation
    ERROR_UNSUPPORT_RES,                  //error_res
    ERROR_UNSUPPORT_DP,                   //data partitioning
    ERROR_UNSUPPORT_RRVOP,                //reduced_resolution_vop
    ERROR_UNSUPPORT_SCALABLE,             //scalability
    ERROR_UNSUPPORT_VSOTYPE,              //visual_object_type
    ERROR_UNSUPPORT_BFRAME,               //unsupport B-frame
    ERROR_UNSUPPORT_SIZE,                 //unsupport size
    ERROR_UNSUPPORT_VOPTYPE,              //unsupport vop type
    ERROR_USERDATA,                       //dec user data error
    ERROR_TIMEBASE,                       //dec time base error
    ERROR_BITSTREAM,                      //error dec bs
    ERROR_DEC_COEFF,                      //dec coeff error
    ERROR_DEC_MB,                         //dec mb error
    ERROR_VLXDEC_VOPHEAD = 0x9000,        //dec vop header error
    ERROR_VLXDEC_MB,                      //vlx dec mb error
    ERROR_VLXDEC_WAIT                     //vlx wait time out
};

#endif

#define GET_DEC_POINT_REF   1
#define GET_DEC_POINT_REC   2
#define GET_DEC_WIDTH       3
#define GET_DEC_HEIGHT      4
#define GET_DEC_EDGE_WIDTH  5

#define TMp4vDecHandle void *

typedef struct TMp4vDecFrame
{
	u8 *pu8YUV;          // �������YUV420ͼ��Buffer
	u8 *pu8BitStream;    // ������������Buffer
	u32 length;          // ������������
	l32 l32FrameType;    // �������֡���� 0:I֡; 1:P֡
	l32 l32OutWidth;     // �������ͼ����
	l32 l32OutHeight;    // �������ͼ��߶�
	l32 l32PostProcess;  // �Ƿ������� 1���� 0����
	
	u8 *pu8Output88MV; //�û��ڽ������ⲿ����һ��396*4*sizeof(u8)���ڴ�ָ����Ϊ����
	                   //���44*36��8x8����˶����𣬿��λ������ͼ
	                   //�˶�����ȡֵ��Χ0-9��ֵԽ���˶�Խ���ң������Ϊ0����ʾû���˶�
	                   //ע�⣺�粻��Ҫ�鿴�˶����𣬴˴����봫��NULL !!!!	

} TMp4vDecFrame;

//�ⲿ�ӿں���
l32 Mp4vDecoderInit(TMp4vDecHandle *ppvHandle);
l32 Mp4vDecoderFrame(TMp4vDecHandle pvHandle,TMp4vDecFrame *ptDecFrame);
l32 Mp4vDecoderFree(TMp4vDecHandle pvHandle);
l32 MP4vGetDecInfo(void *pvHandle, l32 l32CmdId, u32 *pu32PtrAddr);
void  GetMPEG4DecoderVersion(void *pVer, l32 l32BufLen, l32 *pl32VerLen);

#ifdef __cplusplus
extern "C" {
#endif 
#endif // _DECORE_H_
