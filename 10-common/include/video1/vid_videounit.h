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

#include "videodefines.h"
#include "img_imagelib.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define VideoCodecHandle  void*

//VideoUnitEnc��չ����(sunxx,20081212)
typedef enum
{
    ENC_TEST_TYPE = 1,
    ENC_FILTER_TYPE,            //ʱ���˲���չ����
    ENC_DEINTERLACE_TYPE        //Deinterlace��չ����
}TExtendEncType;

//ENC_FILTER_TYPE���͵���չ�ṹ��
typedef struct
{
    TExtendEncType tExtendType; //�ṹ��չ����
    l32 l32IsDeinterlace;       //�Ƿ�Deinterlace
    l32 l32IsTemporalFilter;    //�Ƿ�ʱ���˲�
}TVideoEncFilterParam;

//ENC_DEINTERLACE_TYPE���͵���չ�ṹ��
typedef struct
{
    u32 u32ReservedType;            // ���������չ����(ENC_DEINTERLACE_TYPE)
    l32 l32EncDeinterlaceEnable;    // ����Deinterlace����
    l32 l32DeinterlaceMode;         // DeInterlace����ģʽ
    l32 l32Interlace;               // Deinterlace�����֡����ʽ
    u32 u32Reserved;                // ��������
}TVideoEncDeinterlaceParam;

//VideoUnit������������չ�ṹ��(sunxx,20081212)
typedef struct
{
    TExtendEncType tExtendType; //�ṹ��չ����
    l32 l32IsDeinterlace;       //�Ƿ�Deinterlace
    l32 l32IsTemporalFilter;    //�Ƿ�ʱ���˲�
    u32 u32Reserved;
}TVideoEncTestParam;

//VideoUnit ��չ���� add by wgz in 08-12-12
typedef enum
{
    DEC_TEST_TYPE = 1,          //videounit��������
    DEC_NonH264_DEBLOCK_TYPE    //�Ƿ�Է�264��������Deblock����
}TExtendDecType;

//VideoUnit ������������չ�ṹ�� add by wgz in 08-12-12
typedef struct
{
    TExtendDecType tExtendType; //������������չ�ṹ�������
    u32 u32Reserved;            //��������
}TVideoDecTestParam;

//VideoUnitDec ���ý�������Deblock���� add by zhaobo 2010-8-26
typedef struct
{
    u32 u32ReservedType;    //���������չ����(DEC_DEBLOCK_TYPE)
    l32 l32SetDeblock;      //���÷�264��ʽ�����Ƿ���Ҫ����Deblock����
    l32 l32DeblockMode;     //��ʱδ���š����ֶ�����Ϊ0
    u32 u32Reserved;        //��������
}TVideoDecNonH264DeblockParam;

typedef struct
{
    l32 l32StartMB;                     //����ʧ����ʼ���
    l32 l32EndMB;                       //����ʧ�Ľ������
}TSliceRegion;

typedef struct  
{
    l32 l32DropSliceNum;                              //��¼��slice����Ŀ
    TSliceRegion tSliceRegion[MAX_DAMAGED_SLICE_NUM]; //��¼������Ϣ�Ľṹ������
}TDropSliceInfo;

// �������������������slice����ṹ��
typedef struct
{
    u32 u32EncReservedType; // ���������չ����(ENC_EC)
    TDropSliceInfo tDSInfo; // ���������صĶ�ʧ��slice����
    u32 u32Reserved;
}TDecFeedBack;

// ����ָ������ṹ��
typedef struct
{
    u32 u32EncReservedType; // ���������չ����(ENC_EC)
    l32 l32ECLevel;         // ����ָ�����ļ���(��Ҫ�����)
    u32 u32Reserved;        // ��������
}TECParam;

// ����У������ṹ��
typedef struct
{
    u32 u32EncReservedType; // ���������չ����(ENC_CHECK_BS)
    l32 l32EnableCheckBs;   // �Ƿ�������У��(1:��; 0:�ر�)
    u32 u32Reserved;        // ��������
}TEncCheckBsParam;

// Slice���ò����ṹ��
typedef struct
{
    u32 u32EncReservedType; // ���������չ����(ENC_SET_SLICE)
    l32 l32EncSliceLen;     // ����Slice����
    u32 u32Reserved;        // ��������
}TEncSetSlice;

// ����Slice��������ṹ��
typedef struct
{
    u32 u32EncReservedType;   // ���������չ����(ENC_SET_SLICE)
    l32 l32EnableSliceAlign;  // ʹ��slice���ֽڶ���
    u32 u32Reserved;          // ��������
}TEncSliceAlign;

//H.264������VA������չ(����Linuxƽ̨VAӲ��������)
typedef struct
{
    u32 u32ReservedType;        // ���������չ����(ENC_VA_PARAM)
    void *pvDisplay;            // Display���(XOpenDisplay()�õ�)
    void *pvVADisplay;          // VA Display���(vaGetDisplay()�õ�)
    l32 l32EnableInputSurfaceID;// �Ƿ��ⲿֱ�Ӵ������ͼ��surfaceid
    u32 u32Reserved;            // ��������
}TVAEncParam;

// TReservedStructContainer �ṹ������
typedef enum 
{
    ReservedType_StructContainer = 0xfedcba98  // ȫ��Ψһ�����ͱ�ʶ��
} TReservedTypeStructContainer;

// �������ɶ����չ���͵Ľṹ��
typedef struct  
{
    l32 l32ReservedType;        // ��չ���ͣ�ReservedType_StructContainer
    l32 l32ReservedStructNum;   // ��չ�ṹ�����Ŀ
    void *pvReservedStruct;     // ָ����չ�ṹ�������
} TReservedStructContainer;

#define MIN_ENC_NUM 1
#define MAX_ENC_NUM 4
//��������չ����
typedef struct
{
    u32  u32EncExtendType;      //��չ����(ENC_NUM_TYPE)
    u32  u32EncNum;             //���������̱߳���(֧��MIN_ENC_NUM-MAX_ENC_NUM)
    l32 l32EnableBindCPU;       // ʹ��CPU�󶨹���
    l32 al32CPUID[MAX_ENC_NUM]; // ÿ���̴߳��󶨵�cpu id��cpu id��0��ʼ������l32EnableBindCPU��0ʱ���ֶο���ʹ��
    u32  u32Reserved;           //��������
}TEncNumParam;

//��������ʼ���ṹ��
typedef struct
{
    u32	u32EncType;			    //����������
    l32	l32EncPacketMode;		//���ģʽ
    l32	l32EncWidth;		    //������
    l32	l32EncHeight;			//����߶�
    l32 l32EncMaxFrameRate;     //���֡��
    l32 l32EncMinFrameRate;     //��С֡��
    l32 l32EncMaxBitRate;       //�������
    l32 l32EncMinBitRate;       //��С����
    l32	l32EncMaxQP;		    //�����������
    l32	l32EncMinQP;		    //��С��������
    l32	l32EncKeyFrameInterval;	//I֡���������I֡��P��B֡����
    l32	l32EncQuality;	        //����ͼ������(auto, 1, 2)
    l32 l32EncVideoMode;        //����ͼ����ʽ(��ʽ����:videodefines.h��VIDEOMODETYPE)
    l32 l32EncInterlace;        //����ͼ��֡������
    l32 l32NeedUserInfo;        //�Ƿ�д���û���Ϣ
    u32	u32Reserved;			//��������
}TEncParam;

//������ͳ����Ϣ�ṹ��
typedef struct
{
	l32 l32EncFrameRate;      //��ǰ����֡��
	l32 l32EncSkipFrameRate;  //Skip֡֡��
	l32 l32EncDropFrameRate;  //��֡֡��
	u32 u32EncTotalFrame;     //�ܵı���֡��
	u32 u32EncTotalSkipFrame; //�ܵ�Skip֡֡��
	u32 u32EncTotalDropFrame; //�ܵĶ�֡֡��
	l32 l32EncBitRate;        //��ǰ��������
	l32	l32EncQuality;	      //��ǰ����ͼ������(����ȼ�)
	u32	u32Reserved;		  //��������
}TEncStatisParam;

//ͼ��ǰ����״̬�ṹ��
typedef struct  
{
	l32 l32IsLogoBanner;    //�Ƿ����ͼ��
	l32 l32IsMotionSurveil; //�Ƿ�����˶����
	u32 u32Reserved;        //��������
}TPreProcessStatusParam;

//ͼ��ǰ����ṹ��
typedef struct 
{
	l32 l32SrcYUVType;     //����ͼ��YUV����
	l32 l32SrcIsInterlace; //����ͼ���֡����ʽ
    l32 l32SrcWidth;       //����ͼ��Ŀ��
    l32 l32SrcHeight;      //����ͼ��ĸ߶�
    l32 l32SrcYStride;     //����ͼ��Y�����Ĳ���
	l32 l32SrcUVStride;    //����ͼ��UV�����Ĳ���

	l32 l32DstYUVType;     //���ͼ��YUV����
	l32 l32DstIsInterlace; //���ͼ���֡����ʽ
    l32 l32DstWidth;       //���ͼ��Ŀ��
    l32 l32DstHeight;      //���ͼ��ĸ߶�
    l32 l32DstYStride;     //���ͼ��Y�����Ĳ���
	l32 l32DstUVStride;    //���ͼ��UV�����Ĳ���
	l32 l32ImageQuality;   //ͼ���������ȼ�()
	u32 u32Reserved;       //��������
}TPreProcessParam;

//�˶���Ϣ�ṹ��
typedef struct
{
	u8 *pu8MotionInfo;	     //ָ�򱣴��˶���Ϣ��ָ��
	l32	l32MotionInfoLen;    //�����˶���Ϣ����ĳ���(ͼ��Ŀ�ȳ���ͼ��ĸ߶ȳ���8)
	u8 u8Threshold;          //�˶������������ֵ
    u32 u32Reserved;         //��������
}TMotionSurveil;

//����,ͼ��ǰ����,�˶����ṹ��
typedef struct
{
	TEncParam tEncParam;                    //�����������ṹ��
	TPreProcessParam tPreProcessParam;      //ǰ��������ṹ��
    l32 l32IsLogo;                          //�Ƿ��̨���־λ(LOGO_ENABLE: ��ͼ��,����:����ͼ��)
    TLogoInfo tLogoInfo;                    //��ͼ������ṹ��
    l32 l32IsBanner;                        //�Ƿ�Ӻ����־λ(BANNER_ENABLE: �����,����:�������)
    TBanner tBanner;                        //�Ӻ�������ṹ��
    l32 l32IsBannerLogo;                    //�Ƿ���������־λ(BANNER_LOGO_ENABLE: �������,����:���������)
    TImageBannerLogoParam tBannerLogoParam; //��������������ýṹ��
    l32 l32IsMotionSurveil;                 //�Ƿ�����˶����ı�־λ(MOTION_SURVEIL_ENABLE: �˶����,����:���˶����)
    TMotionSurveil tEncMotionSurveil;       //�˶���Ϣ�����ṹ��
	u32 u32Reserved;                        //��������
}TVideoUnitEncParam;

//������״̬�ṹ��
#define TEncStatusParam TEncParam
#define TVideoUnitEncStatusParam TVideoUnitEncParam

typedef struct
{
    u32 u32ReserverdType;   // ������������չ����(H261BLANKFRAME)
    l32 l32H261BlankFrame;  // H.261�Ƿ�Ҫ���֡(1:���֡,����:��������)
    u32 u32Reserved;        // ��������
}TH261EncBlankFrame;

//��������ṹ��
typedef struct
{
    u8 *pu8YUV;             //ָ�����������ͼ��ָ��
    u32	u32EncSetKeyFrame;	//���ñ���ؼ�֡,1: ��ǰ֡����I֡,����: �������Զ�
    u32	u32Reserved;	    //��������
}TEncInput;

//H.264����������VA��Ϣ��չ(����Linuxƽ̨VAӲ������������surface id)
typedef struct
{
    u32 u32ReservedType;    // ������������չ����(ENC_VA_INPUT)
    u32 u32SurfaceID;       // ��������surface id
    u32 u32EncBsBufSize;    //�ⲿ����ı�������Buffer��С
    u32 u32Reserved;        // ��������
}TVAEncInput;

//��������ṹ��չ�ṹ��(���ڽ���������)
typedef struct
{
    u32 u32ReservedType;        // ������������չ����(DEC_FEEDBACK)
    TDropSliceInfo tDSInfo;     // ������������Ϣ
    u32 u32Reserved;            // ��������
}TDecFeedBackParam;

//��������ṹ��
typedef struct
{
    u8 *pu8EncBitstream;	//ָ���������ָ��
    l32	l32EncBitstreamLen;	//�����������
    l32	l32EncFrameType;	//����֡����,I֡,P֡,SKIP֡,DROP֡
    u32	u32Reserved;		//��������
}TEncOutput;

typedef struct
{
    u32 u32ReservedType;    // �����������չ����(ENC_VA_OUTPUT)
    u32 u32ExtBSBufSize;    // �ⲿ����buffer�Ĵ�С����λΪ�ֽ�
    u32 u32Reserved;        // ��������
}TVAEncOutput;

//�����ͼ����ṹ��
typedef struct
{
	l32 l32OutYUVType;     //���ͼ���YUV����
	l32 l32OutIsInterlace; //���ͼ���֡����ʽ
    l32 l32OutWidth;       //���ͼ��Ŀ��
    l32 l32OutHeight;      //���ͼ��ĸ߶�
    l32 l32OutYStride;     //���ͼ��Y�����Ĳ���
	l32 l32OutUVStride;    //���ͼ��UV�����Ĳ���
	l32 l32ImageQuality;   //���ͼ��������ȼ�
	u32	u32Reserved;	   //��������
}TPostProcessParam;

//ͼ����������չ�ṹ��
typedef struct  
{
    //Դ�ü���ز���
    u32 u32PostReservedType; //������չ����(POST_SPECIAL_RESIZER)
    l32 l32SrcTopCutLine;     //Դͼ����Ĳü���������ӦΪ2�ı���
	l32 l32SrcBottomCutLine;  //Դͼ����Ĳü���������ӦΪ2�ı���
	l32 l32SrcLeftCutPoint;   //Դͼ��ߵĲü��ĵ�����ӦΪ2�ı���
	l32 l32SrcRightCutPoint;  //Դͼ�ұߵĲü��ĵ�����ӦΪ2�ı���
	//Ŀ�������ز���
	l32 l32DstTopFillLine;    //Ŀ��ͼ�����������ɫ������ӦΪ2�ı���
	l32 l32DstBottomFillLine; //Ŀ��ͼ�����������ɫ������ӦΪ2�ı���
	l32 l32DstLeftFillPoint;  //Ŀ��ͼ��ߵ�������ɫ������ӦΪ2�ı���
	l32 l32DstRightFillPoint; //Ŀ��ͼ�ұߵ�������ɫ������ӦΪ2�ı���
	l32 l32DstFillYColor;     //Ŀ��ͼ��Ե�����ɫY����ֵ
	l32 l32DstFillUColor;     //Ŀ��ͼ��Ե�����ɫU����ֵ
	l32 l32DstFillVColor;     //Ŀ��ͼ��Ե�����ɫV����ֵ��Ŀǰ��ɫΪY:0x01,UV:0x80,��ɫ��ȫ��
	
    u32 u32Reserved;          //��������,������
}TPostSpecialResizerParam;

//ͼ�����״̬�ṹ��
typedef struct  
{
	l32 l32IsLogoBanner;    //�Ƿ����ͼ��
	l32 l32IsMotionSurveil; //�Ƿ�����˶����
	u32 u32Reserved;        //��������
}TPostProcessStatusParam;

//��������ʼ���ṹ��
typedef struct
{
	u32	u32DecType;		  	   //����������
	l32	l32DecPacketMode;	   //�������ģʽ
    l32 l32DecMaxWidth;        //����ͼ��������
    l32 l32DecMaxHeight;       //����ͼ������߶�
	u32	u32Reserved;	       //��������
}TDecParam;

//��������ʼ����չ�ṹ��(���ڴ����ڱ�)
typedef struct
{
    u32 u32ReservedType;        // ���������չ����(DEC_EC)
    l32 l32ErrorConcealFlag;    // �Ƿ�򿪴����ڱο���(EC_ON:��; EC_OFF:�ر�)
    u32 u32Reserved;            // ��������
}TDecECParam;
//������������չ(��������У��)
typedef struct
{
    u32 u32ReservedType;        // ���������չ����(DEC_CHECK_BS)
    l32 l32EnableCheckBs;       // �Ƿ�򿪽��������У��(1:��; 0:�ر�)
    u32 u32Reserved;            // ��������
}TDecCheckBsParam;

//������������չ(����Win7ϵͳӲ��������)
typedef struct
{
    u32 u32ReservedType;        // ���������չ����(DEC_GPU_PARAM)
    l32 l32EnableD3dAlloc;      //�Ƿ���ʹ��D3d�Դ����
    l32 l32EnableDecCopy;       //�Ƿ��������������
    u32 u32Reserved;            // ��������
}TGPUDecParam;

//����VA��GPU������������չ������LinuxϵͳӲ����������
typedef struct
{
    u32 u32ReservedType;        // VA���������չ����(DEC_VA_PARAM)
    void *pvDisplay;            // Display���(XOpenDisplay()�õ�)
    void *pvVADisplay;          // VA Display���(vaGetDisplay()�õ�)
    l32 l32EnableOutSurfaceId;  // �Ƿ��������surfaceid
    l32 l32EnableOutYUV;        // �Ƿ��������YUV����
    u32 u32Reserved;
}TVADecParam;

typedef struct
{
    u32 u32ReservedType;        // ���������չ����(DEC_MULTI_THREAD)
    l32 l32EnableMultiThread;   // �Ƿ�򿪶��߳̽���(1:��; 0:�ر�)
    u32 u32Reserved;            // ��������
}TDecMultiThreadParam;


//��������ʼ����չ�ṹ��(���ں͹�˾Ĭ�ϵ�ͼ���ʽ��ͬ�ĳ���)
typedef struct
{
    u32 u32ReservedType;        // ���������չ����(DEC_IMAGE_FORMAT)
    l32 l32SrcInterlace;        // ������֡����ʽ
    u32 u32Reserved;            // ��������
}TDecSrcImageParam;

//����������״̬�ṹ��
typedef struct
{
	l32 l32DecFrameRate;       //����֡��
	l32 l32DecBitRate;         //��������
	u32 u32DecTotalFrame;      //�ܵĽ���֡��
	u32 u32DecTotalErrorFrame; //�ܵĽ���ʧ��֡��
    l32 l32DecWidth;           //����ͼ��Ŀ��
    l32 l32DecHeight;          //����ͼ��ĸ߶�
	u32	u32Reserved;	       //��������
}TDecStatisParam;

//TDecParam�ṹ����u32Reserved��չΪ�Ƿ���Deinterlace����
typedef struct
{
    u32 u32ReservedType;          // ���������չ����(DEC_DEINTERLACE)
    l32 l32DecDeinterlaceEnable;  // ����Deinterlace����
    l32 l32DeinterlaceMode;       // DeInterlace����ģʽ
    u32 u32Reserved;              // ��������
}TDecDeinterlaceParam;

//TDecParam�ṹ����u32Reserved��չΪ�Ƿ����ý���������ͼ��֡����ʽ��
typedef struct
{
    u32 u32ReservedType;        // ���������չ����(DEC_SET_INPUT_FRAME_TYPE)
    l32 l32Width;               // ͼ����
    l32 l32Height;              // ͼ��߶�
    l32 l32SrcInterlaceType;    // ����������ͼ���֡����ʽ
    u32 u32Reserved;            // ��������
}TDecSrcFrameTypeParam;

//������,ͼ�����,�˶�״̬�ṹ��
typedef struct
{
	TDecParam tDecParam;                      //�����������ṹ��
	TPostProcessParam tPostProcessParam;       //��������ṹ��
    l32 l32DecIsLogo;                          //����ͼ���Ƿ��ͼ��
    TLogoInfo tDecLogoInfo;                    //��ͼ������ṹ��
    l32 l32DecIsBanner;                        //����ͼ���Ƿ񻭺��
    TBanner tDecBanner;                        //�Ӻ�������ṹ��
    l32 l32DecIsBannerLogo;                    //����ͼ���Ƿ�������
    TImageBannerLogoParam tDecBannerLogoParam; //��������������ýṹ��
    l32 l32DecIsMotionSurveil;                 //�Ƿ�����˶����
	TMotionSurveil tDecMotionSurveil;          //�˶���Ϣ�����ṹ��
	u32 u32Reserved;                           //��������
}TVideoUnitDecParam;

//����������״̬�ṹ��
#define TDecStatusParam TDecParam
#define TVideoUnitDecStatusParam TVideoUnitDecParam

//����������ṹ��
typedef struct
{
	u8 *pu8DecBitstream;	//������������
	u32 u32DecBitstreamLen;	//һ֡��������Ч����
    l32 l32DecIsOutputYUV;  //����ͼ���Ƿ����[0��ʾ����������ʾ�����]
	u32 u32Reserved;		//��������
}TDecInput;

//����������ṹ��
typedef struct
{
    u8 *pu8YUV;		     //ָ����������ͼ�󻺳��ָ��
    l32	l32DecWidth;     //����ͼ���ʵ�ʿ��
    l32	l32DecHeight;    //����ͼ���ʵ�ʸ߶�
    l32	l32DecFrameType; //����֡����
    l32 l32DecInterlaceType; //����֡������
    u32	u32Reserved;	 //��������
}TDecOutput;

//��·����������ṹ��
typedef struct
{
    u32 u32ReservedType;//���������չ����(MULTI_DEC_OUT_PUT)
    u8 *pu8OutY;	    //ָ����������ͼ�󻺳�Y������ָ��
    u8 *pu8OutU;        //ָ����������ͼ�󻺳�UV������ָ��
    u8 *pu8OutV;        //ָ����������ͼ�󻺳�UV������ָ��
    l32 l32OutYStride;  //ָ����������ͼ�󻺳�Y����Stride 
    l32 l32OutUVStride; //ָ����������ͼ�󻺳�UV����Stride
    l32 l32DecWidth;    //����ͼ���ʵ�ʿ��
    l32 l32DecHeight;   //����ͼ���ʵ�ʸ߶�
    l32 l32DecFrameType;//����֡����
    u32 u32Reserved;    //��������
}TMultiDecOutput;

//����ָ�����ṹ��
typedef struct
{
    u32 u32ReservedType;        //���������չ����(DEC_EC_OUTPUT)
    TDropSliceInfo tDSInfo;     //����һ֡��ͳ�Ƶõ���slice��ʧ���
    l32 l32ValidMBRatio;        //��ʶ��Ч���ı���������-1��ʾ���ֶ���Ч
    u32 u32Reserved;            //��������
}TECOutput;

//����У������ṹ��
typedef struct
{
    u32 u32ReservedType;        //���������չ����(DEC_CHECK_OUTPUT)
    l32 l32CheckBsVal;          //У����(0:У��ʧ�ܣ� 1��У��ɹ�)
    u32 u32Reserved;            //��������
}TDecCheckOutput;

//VA��������ṹ��
typedef struct
{
    u32 u32ReservedType;//���������չ����(DEC_VA_OUTPUT)
    void *pvVADisplay;   //���ؽ�����ʹ�õ�VADisplay���
    u32 u32SurfaceId;   //����ͼ���surfaceid
    u32 u32Reserved;	//��������
}TVADecOutput;

//�������Ƿ����ǰһ֡ͼ����
typedef struct
{
    u32 u32ReservedType;     //���������չ����(DEC_OUT_PRE_FRAME)
    l32 l32OutPreFrameFlag;  //���ǰһ֡ͼ���ʶ(1:���ǰһ֡��0:�����ǰһ֡��
    u32 u32Reserved;         //��������
}TDecOutPreFlag;

typedef struct
{
    l32 l32GPUCodecSupport;       //�Ƿ�֧��H.264 GPU���루1-֧�֣�0-��֧�֣�
    l32 l32GPUCodecMinorVersion;  //GPU Codec�汾��(minor)
    l32 l32GPUCodecMajorVersion;  //GPU Codec�汾��(major)
    u32 u32Reserved;
}TVidGPUCodecInfoOutput;

/*====================================================================
������		: VideoUnitEncoderGetVersion
����		: �������ӿڰ汾��Ϣ
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : pvVer: �������[out]
			  l32BufLen: ���泤��[in]
			  pl32VerLen: ��Ϣ����[in/out]
			  u32EncType: ����������[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32EncType);

/*====================================================================
������		: VideoUnitEncoderOpen
����		: ��ʼ����������ǰ����
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle: ָ����������ָ��[in/out]
              ptVideoUnitEncParam: ָ������ʼ�������ṹ��ָ��[in]
			  pvEncMemParam: ָ���ڴ�����ṹ��ָ��[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderOpen(VideoCodecHandle *ptHandle, TVideoUnitEncParam *ptVideoUnitEncParam, void *pvEncMemParam);

/*====================================================================
������		: VideoUnitEncoderProcess
����		: ����һ֡ͼ��
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle: ָ����������ָ��[in]
              ptEncInput: ָ���������ṹ��ָ��[in]
              ptEncOutput: ָ���������ṹ��ָ��[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderProcess(VideoCodecHandle ptHandle, TEncInput *ptEncInput, TEncOutput *ptEncOutput);

/*====================================================================
������		: VideoUnitEncoderClose
����		: �رձ�����
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
�������˵��: ptHandle: ָ����������ָ��[in]
�������˵��: ��
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderClose(VideoCodecHandle ptHandle);

/*====================================================================
������		: VideoUnitEncoderSetParam
����		: ���ñ���������
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle:	���������[in/out]
			  ptVideoUnitParam: �������ò���[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
�������ر�˵��: Ŀǰ���øú����ɸı�Ĳ��������������Ⱥ͸߶ȣ�����ı�
                ����ͼ��Ŀ�ߣ����ȹر�ԭ���������ٰ��µĿ�߳�ʼ���µı�����
====================================================================*/
l32 VideoUnitEncoderSetParam(VideoCodecHandle ptHandle, TVideoUnitEncParam *ptVideoUnitParam);

/*====================================================================
������		: VideoUnitEncoderGetStatus
����		: ��ȡ����������״̬
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle: ���������[in]
			  ptVidUnitEncStatusParam: ����״̬����[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderGetStatus(VideoCodecHandle ptHandle, TVideoUnitEncStatusParam *ptVidUnitEncStatusParam);

/*====================================================================
������		: VideoUnitEncoderGetStatis
����		: ��ȡ����������ͳ����Ϣ
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle: ָ����������ָ��[in]
			  ptEncStatisParam: ָ�������ͳ����Ϣ�ṹ��ָ��[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderGetStatis(VideoCodecHandle ptHandle, TEncStatisParam *ptEncStatisParam);

/*====================================================================
������		: VideoUnitEncoderDebug
����		: ������������Ϣ
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle:	ָ����������ָ��[in]
              pvDebugInfo : ָ�������Ϣָ��[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderDebug(VideoCodecHandle ptHandle, void *pvDebugInfo);

/*====================================================================
������	    : VideoUnitEncoderAnalyzeErrorCode
����	    : ���������������
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        :  ptHandle: ָ����������ָ��[in/out]
              l32ErrorCode: ������[in]
              l32BufLen: ���泤��[in]
              pvErrorCodeInfo: ����buffer[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderAnalyzeErrorCode(VideoCodecHandle ptHandle, l32 l32ErrorCode, l32 l32BufLen, void *pvErrorCodeInfo);

/*====================================================================
������	    : VideoUnitEncoderGetMemSize
����	    : ��ȡ������Ҫ�ڴ��С
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptVideoUnitDecParam: ָ������ʼ�������ṹ��ָ��[in]
              pl32EncMemSize: ��Ҫ�ڴ��С[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitEncoderGetMemSize(TVideoUnitEncParam *ptVideoUnitEncParam, l32 *pl32EncMemSize);

/*====================================================================
������		: VideoUnitDecoderGetVersion
����		: �������ӿڰ汾��Ϣ
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : pvVer: �������[in/out]
			  l32BufLen: ���泤��[in]
			  pl32VerLen: ��Ϣ����[out]
			  u32DecType: ����������[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32DecType);

/*====================================================================
������		: VideoUnitDecoderOpen
����		: ��ʼ��������
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle: ָ����������ָ��[in/out]
              ptVideoUnitDecParam: ָ������ʼ�������ͽ������ͼ��ṹ��ָ��[in]
			  pvDecMemParam: ָ���ڴ�ռ�����ṹ��ָ��[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderOpen(VideoCodecHandle *ptHandle, TVideoUnitDecParam *ptVideoUnitDecParam, void *pvDecMemParam);

/*====================================================================
������		: VideoUnitDecoderProcess
����		: ����һ֡ͼ��
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle: ���������[in]
              ptDecInput: ָ���������������ṹ��ָ��[in]
              ptDecOutput: ָ���������������ṹ��ָ��[out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderProcess(VideoCodecHandle ptHandle, TDecInput *ptDecInput, TDecOutput *ptDecOutput);

/*====================================================================
������		: VideoUnitDecoderClose
����		: �رս�����
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle:	���������[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderClose(VideoCodecHandle ptHandle);

/*====================================================================
������		: VideoUnitDecoderSetParam
����		: ���ý���������
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle: ָ����������ָ��[in/out]
			  ptVideoUnitDecParam: ָ���������ʼ�������ṹ��ָ��[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
�������ر�˵��: Ŀǰ���øú����ɸı�Ĳ��������������Ⱥ͸߶�, ����ı�
                ����ͼ��Ŀ��, ���ȹر�ԭ������, �ٰ��µĿ�߳�ʼ���µ�
====================================================================*/
l32 VideoUnitDecoderSetParam(VideoCodecHandle ptHandle, TVideoUnitDecParam *ptVideoUnitDecParam);

/*====================================================================
������		: VideoUnitDecoderGetStatus
����		: ��ȡ����������״̬
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle:	ָ�����������Ľṹָ��[in]
			  ptVideoUnitDecStatusParam: ָ�����״̬�����ṹ��ָ��[out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderGetStatus(VideoCodecHandle ptHandle, TVideoUnitDecStatusParam *ptVideoUnitDecStatusParam);

/*====================================================================
������		: VideoUnitDecoderGetStatis
����		: ��ȡ������ͳ����Ϣ״̬
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle:	ָ�����������Ľṹָ��[in]
			  ptDecStatisParam: ָ�������ͳ����Ϣ�ṹ��ָ��[out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderGetStatis(VideoCodecHandle ptHandle, TDecStatisParam *ptDecStatisParam);

/*====================================================================
������		: VideoUnitDecoderDumpStatus
����		: ������������Ϣ
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptHandle:	ָ����������ָ��[in]
              pvDebugInfo: ָ�������Ϣָ��[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderDebug(VideoCodecHandle ptHandle, void *pvDebugInfo);

/*====================================================================
������	    : VideoUnitDecoderAnalyzeErrorCode
����	    : ���������������
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : l32ErrorCode:  ������[in]
              l32BufLen: ���泤��[in]
              pvErrorCodeInfo: ����buffer[in]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderAnalyzeErrorCode(VideoCodecHandle ptHandle, l32 l32ErrorCode, l32 l32BufLen, void *pvErrorCodeInfo);

/*====================================================================
������	    : VideoUnitDecoderGetMemSize
����	    : ��ȡ������Ҫ�ڴ��С
�㷨ʵ��	: ��
����ȫ�ֱ���: ��
����        : ptVideoUnitDecParam: ָ������ʼ�������ͽ������ͼ��ṹ��ָ��[in]
              pl32DecMemSize: ��Ҫ�ڴ��С[in/out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoUnitDecoderGetMemSize(TVideoUnitDecParam *ptVideoUnitDecParam, l32 *pl32DecMemSize);

/*====================================================================
������	    : VideoCodecQuery
����	    : ��ȡ�����������Ϣ
����        : u32QueryType:         ��ѯ����(QUERY_GPU_CODEC��
              pvVidCodecInfoInput:  ��ȡ�����������Ϣ����ṹָ��[in] 
              pvVidCodecInfoOutput:	��ȡ�����������Ϣ����ṹָ��[out]
����ֵ˵��  : �ɹ�: VIDEO_SUCCESS, ʧ��: ���ش�����
====================================================================*/
l32 VideoCodecQuery(u32 u32QueryType, void *pvVidCodecInfoInput, void* pvVidCodecInfoOutput);
#ifdef __cplusplus
}
#endif

#endif	//_VIDEOUNIT_H_
