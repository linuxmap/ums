/******************************************************************************
�ļ���	    ��H264Enc.h
����ļ�	��H264Enc.c
�ļ�ʵ�ֹ��ܣ������ϲ�Ӧ�ò�ֻ��Ϊ����һ֡�ṩMAX_FRAME_BUFFER_LEN(128k)�Ļ��棬
              ����������������ָ�֡��������������ó��ȣ�����ʧ�ܣ���Σ��ϵ����
              �󣬶���һ��352x288��ͼ�񣬱���Ϊ��֡���Դﵽ81k !!! ��λ���ֽ�
���ڹ����棺����ʹ�ù����ڴ棬���С����ֱ�Ӹ������ڴ˽��ṩCIF��ʽ�±���������
              ���ڴ��С�ο�ֵ(2500,000Byte)���ⲿ�����߲ο����¹�ʽ���乲���ڴ�:
			  ���乲���ڴ��С > ����ͼ���С * 2500000 / CIF !!!
����		���ż���
�汾		��2004.8.28
-------------------------------------------------------------------------------
��  ��		�汾		�޸���		�߶���    �޸�����
01/18/2005	1.0         ��  ��      �ż���    ���ע�ͣ��޸ĺ�������������
******************************************************************************/
#ifndef H264ENC_H
#define H264ENC_H

#include "algorithmtype.h"

#ifdef _LINUX_
#define H264vEncHandle void *
typedef enum
{
	H264ENCDRV_OK,
	H264ENCDRV_ERROR,
	H264ENCDRV_NOMEM,
	H264ENCDRV_BADFMT,
	H264ENCDRV_WRONG_VERSION,	
	H264ENCDRV_KERNEL_MODULE_PROBLEMS,	
}H264encDrvError_t;

#define ENC_FAIL		    -1
#define ENC_OK			    H264ENCDRV_OK
#define	ENC_MEMORY		    H264ENCDRV_NOMEM
#define ENC_BAD_FORMAT		    H264ENCDRV_BADFMT
#else
#define H264encDrvError_t    l32 
#define ENC_FAIL		    -1
#define ENC_OK			    0
#define	ENC_MEMORY		    1
#define ENC_BAD_FORMAT		2
#endif

#define MAX_FRAME_BUFFER_LEN (128*1024)         // �����һ֡������󳤶�
#ifndef MAX_NALU_NUM    
#define MAX_NALU_NUM  128                       // ���NALU��Ŀ
#define	MAX_NALU_UNIT_SIZE	 (4*MAX_NALU_NUM)   // ���һ��NALU��Ԫ���� (sizeof(int) * MAX_NALU_NUM)
#endif

#define H264SimpleLevel1	1
#define H264SimpleLevel2	2
#define H264SimpleLevel3	3
#define H264AdvanceLevel1	101
//add for f264
#define F264Level1          110

#ifdef __cplusplus
extern "C"
{
#endif 
// �ӿڽṹ�嶨��
	
	typedef struct {
		u8	*pu8YUV420;         //����YUV���ݻ��������û��ڵ��ý�����ǰ���з���
		u32	u32YUVLen;          //ԭʼͼ�񻺳�������
		u8	*pu8BitStream;	    //����֡�����������
		u32	u32BitstreamLen;    //���������������
		u32	u32ReturnWidth;     //���뷵��ͼ��֡���
		u32	u32ReturnHeight;    //���뷵��ͼ��֡����
		l32	l32FrameType;       //����֡����
		u32 u32EncodeCycles;	    //����1֡����ʹ��ָ��������(��ʹ��Ϊ0)
		u8  *pu8Output88MV;

        u64 u64FrameTimeStamp;  //֡ʱ���
        void* pvNetParam;       //����״̬����
	} TH264EncFramePara;
    /*-------------------------------------------------------------------------
    frametype ����˵����
    ��Encoder���ԣ�
    ��Ϊ���������frametypeΪ1��ʾ����ǰ֡ǿ�Ʊ��I֡��frametypeΪ0��ʾ�Ե�ǰ֡
                  �������Ͳ���ǿ��
    ��Ϊ���������frametypeΪ1��ʾ��ǰ֡��I֡��frametypeΪ0��ʾ��ǰ֡��P֡
    --------------------------------------------------------------------------*/			
	
	typedef struct {
		l32 l32FrameRate;       // ֡��
		l32 l32BitsRate;    	// ����
		l32 l32QPMin;           // ��С��������(1-51)
		l32 l32QPMax;           // �����������(1-51)
		l32 l32XDim;		   	// ����ͼ����[0,720]����Ϊ16�ı���
		l32 l32YDim;		    // ����ͼ��߶�[0,576]����Ϊ16�ı���
		l32 l32PRate;           // I֡���
		l32 l32SkipFrames;		// ������������֡����
		l32 l32EncMode;		    // ���뷽ʽ	 
        l32 l32PicMerge;        // �Ƿ���ϳ�
		u32 u32Quality;			// ָ��ʹ�õ�264������
        l32 l32CoreNum;         //�����õ����ں���
        l32 l32SliceLen;
    } TH264EncParam;
    /*-------------------------------------------------------------------------
	l32EncMode����˵����
    1:֡���뷽ʽ H264EncFrame.bitstreamָ��������һ֡���������
	0:RTP�����뷽ʽ��Ĭ�ϣ�H264EncFrame.bitstream��ǰMAX_NALU_UNIT_SIZE�ֽڱ�ʾ
    MAX_NALU_NUM��int32_t���͵�������Щint32_t���ķ���ֵ�ĸ�����ʾÿ֡ʵ�ʵ�Nalu
    ��������ÿ֡�зֵ�RTP����������int32_t����ʾ��֡�е�ĳ��Nalu���ȣ�
	H264EncFrame.bitstream+MAX_NALU_UNIT_SIZEָ��������һ֡���������
    --------------------------------------------------------------------------*/			
        
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  TH264EncFramePara.bitstream������ͼ��
//  ----------------------------------------------------------------------------------------------------------------------------------------
//  | Nalulen 1 | Nalulen 2 | Nalulen 3 | ..... | Nalulen N |     Nalu 1     |     Nalu 2     |     Nalu 3     | ........ |     Nalu n     |
//  ----------------------------------------------------------------------------------------------------------------------------------------
//  |-- MAX_NALU_UNIT_SIZE = sizeof(int32_t) * MAX_NALU_NUM  -- | ------------------------encoded frame data-----------------------------------|
//  ע��
//  1. ����NΪ����NALU����MAX_NALU_NUM��  nΪһ֡����������ʵ��Nalu�ĸ���
//  2. ��nEncMode==1, ��bitstream��������û��ǰMAX_NALU_NUM��int32_t���͵�����ֻ�б�����֡����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

	
// �ӿں�������

    
    //��������ʼ������
	H264encDrvError_t H264EncoderInit(void **ppvHandle,   TH264EncParam * ptEncParam);
		
    //����һ����֡����
	H264encDrvError_t H264EncoderNull (void *pvHandle, TH264EncFramePara* ptFrame); 

    //����һ֡ͼ����
	H264encDrvError_t H264EncoderFrame(void *pvHandle, TH264EncFramePara* ptFrame);	
	
    //�޸ı�������������
	H264encDrvError_t H264SetEncParams(void *pvHandle, TH264EncParam * ptEncParam) ;	
	
    //�ͷű�������Դ����	
	H264encDrvError_t H264EncoderClose(void *pvHandle);	

    //��������������
    void H264EncHelp(void);
	
    //H264�������汾��Ϣ����
    void  GetH264Version(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

	//��ѯ������״̬
	H264encDrvError_t H264EncoderGetStatus(void *pvHandle, TH264EncParam * ptEncParam);
	
//����ͼ���С��ȡ����Buffer��С  ����ֵ��λΪkb �����/��Ӧ��CIFͼ��������
	//�����/��ӦΪ0 ������-1
	l32 H264EncoderGetBufferSize(l32 l32FrameWidth, l32 l32FrameHeight);
	
	
#ifdef __cplusplus
};
#endif


#endif //end of "#ifndef H264ENC_H"





















