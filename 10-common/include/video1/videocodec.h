#ifndef VIDEO_CODEC_INTERFACE_VER1
#define VIDEO_CODEC_INTERFACE_VER1

#include "algorithmtype.h"
#include "videocommondefines.h"
#include "imageprocess.h"

//some limitations
#define MAX_ENCODER_NUM         2
#define MAX_DECODER_NUM         16
#define MAX_IMAGES_IN_ONE		16
#define MAX_LOGOS_IN_IMAGE		32
#define MAX_BANNERS_IN_IMAGE	32
#define LOGO_STATUS_LEN			20

//�����ʽ
//h261:no rtp packet info
#define H261_PACKET_NO_RTPINFO		0

//h261:has rtp packet info
#define H261_PACKET_RTPINFO		    1

//263:263
#define H263_PACKET_BY_263			0

//263:263+
#define H263_PACKET_BY_263PLUS		1

//264:rtp
#define H264_PACKET_BY_RTP			0

//264:annexb
#define H264_PACKET_BY_ANNEXB		1


//sq 050810 add ����ϳ����Ͷ���
typedef enum {
  PIC_NO_MERGE           ,
  PIC_MERGE_ONE		     ,
  PIC_MERGE_VTWO		 ,
  PIC_MERGE_ITWO		 ,
  PIC_MERGE_THREE		 ,
  PIC_MERGE_FOUR		 ,
  PIC_MERGE_SFOUR		 ,
  PIC_MERGE_SIX		     ,
  PIC_MERGE_SEVEN		 ,
  PIC_MERGE_EIGHT		 ,
  PIC_MERGE_NINE		 ,
  PIC_MERGE_TEN	         ,
  PIC_MERGE_THIRTEEN     ,
  PIC_MERGE_SIXTEEN 
} PicMergeStyle;


//�����������
#define VCODEC_H261					0x0001
#define VCODEC_H263					0x0002
#define VCODEC_MPEG2				0x0003
#define VCODEC_MPEG4				0x0004
#define VCODEC_MPEG4_V200			0x0005
#define VCODEC_H264_SIMPLE_1		0x0011
#define VCODEC_H264_SIMPLE_2		0x0012
#define VCODEC_H264_SIMPLE_3		0x0013
#define VCODEC_H264_ADVANCE			0x0021
#define VCODEC_H264_F264			0x0022


//��map�������map��
typedef enum {
	SINGLE_MAP_ENC_ONE    ,
	MULTI_MAP_ENC_ONE     ,
	MULTI_MAP_ENC_TWO
} EncMapID;

//�������Χ��ʼ�����
typedef enum {
    NO_ENC  ,
    ENC_INIT  
} EncInitFlag;

typedef enum {
    NO_DEC  ,
    DEC_INIT  
} DecInitFlag;

//ĳ·ͼ���Ƿ񹴻��߿���
typedef enum {
    NO_DRAW_FOCUS ,
    DRAW_FOCUS  
} DrawFocusFlag;

//typedef void * VideoCodecHandle
#define VideoCodecHandle  void*

typedef struct tImage
{
	u8		*pu8YUV;			//ͼ��YUVָ��
	l32		l32Width;        	//ͼ��Ŀ��
	l32		l32Height;       	//ͼ��ĸ߶�
	l32		l32ImageType;    	//ͼ�������(֡��ʽ���߳���ʽ)
	l32		l32YUVType;      	//ͼ��ͼ���ʽ(YUV422����YUV420)
	l32		l32YUVLen;			//YUV����

    u8      u8DrawFocusFlag;     //�����Ƿ񹴻��߿�ı��
	u8		u8FocuslineR;		//����߿�ɫR
	u8		u8FocuslineG;		//����߿�ɫG
	u8		u8FocuslineB;		//����߿�ɫB
    u8      u8FocusWidth;        //�߿�ͳһ��ȣ��ݲ������ã�
	u8		u8Pos;				//����λ�ñ��
	
}TImage;		//ͼ��

//ͼ����Ϣ�Ľṹ��
typedef struct tLogo
{
	u8		*pu8YUV;               	//ǰ��ͼ������ָ���ַ(ͼ���ʽΪYUV422ʱ,����Ŀռ��СΪl32Width*l32Height*2,ͼ���ʽΪYUV420ʱ,����Ŀռ��СΪl32Width*l32Height*3/2)
	u8		*pu8Alpha;     			//ǰ��ͼ���alphaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	u8		*pu8Beta;				//��Ӧ����ͼ���betaͨ��ָ��(����ռ�Ĵ�С�ͷ���ͼ�����ݵĴ�Сһ��)
	l32		l32Width;              //ͼ��ͼ��Ŀ��
	l32		l32Height;             //ͼ��ͼ��ĸ߶�
	l32		l32YUVType;            //ͼ��ͼ���ʽ(YUV422����YUV420)
	l32		l32ImageType;          //ǰ��ͼ�������(֡��ʽ���߳���ʽ)
	l32     l32LogoRefPicWidth;    //ͼ����Ӳο�ͼ��Ŀ��(�û���д��Ŀǰ����ʹ��720)
	l32     l32LogoRefPicHeight;   //ͼ����Ӳο�ͼ��ĸ߶�(�û���д��Ŀǰ����ʹ��576)
	l32		l32IsAdaptiveColor;    //�Ƿ���ݵ�ɫ�ı�ͼ�����ɫ,1��ʾ��Ҫ�ı�ͼ�����ɫ,������ʾ����Ҫ�ı�ͼ�����ɫ
	u8	 	u8FgTransparency;       //ǰ��ͼ��͸��ϵ��
    //u8      u8BgTransparency;       //����ͼ��͸��ϵ��
	l32 	l32Top;				    //ͼ��ͼ��ֱλ��ƫ�ƣ��������ʾ���ڣ�
	l32		l32Left;        	    //ͼ��ͼ��ˮƽλ��ƫ�ƣ��������ʾ���ڣ�
	s16		s16StepH;				//ͼ��ˮƽ�˶��ٶȣ�ÿ֡�ƶ��������������Ҹ�����
	s16		s16StepV;				//ͼ�괹ֱ�˶��ٶȣ�ÿ֡�ƶ��������������ϸ����£�
	l32		l32ShowTimes;			//ͼ����ʾ����������һֱ��ʾ��0������ʾ������ͼ�����ٶ�ʱΪѭ����ʾ������ͼ�����ٶ�ʱ���ô�����
	l32		l32PauseIntervalH;		//ͼ��ˮƽ�˶���ͣ�����������������������ͣ�� ����������ͣ��
	l32		l32PauseIntervalV;		//ͼ�괹ֱ�˶���ͣ�����������������������ͣ�� ����������ͣ��
	l32		l32PauseTime;			//ͼ����ͣʱ�䣨���ô�����
	l32		l32WindowTop;			//��ʾ���ڴ�ֱλ��
	l32		l32WindowLeft;			//��ʾ����ˮƽλ��
	l32		l32WindowWidth;			//��ʾ���ڿ��
	l32		l32WindowHeight;		//��ʾ���ڸ߶�

	TFontInfo tFontInfo;			//ͼ�����ֵĽṹ��
	l32		al32LogoStatus[LOGO_STATUS_LEN];	//ͼ��״̬�����ϲ��ʼ��ʱ���㣨�ڲ�ʹ�ã�Ŀǰʹ�������l32[LOGO_H_INTER_MOVE_COUNT]:ͼ��ˮƽ��ͣ�������ƶ�����
	                                            //                                                      l32[LOGO_H_PAUSE_COUNT]:ͼ��ˮƽ��ͣ����
	                                            //                                                      l32[LOGO_V_INTER_MOVE_COUNT]:ͼ�괹ֱ��ͣ�������ƶ�����
	                                            //                                                      l32[LOGO_V_PAUSE_COUNT]:ͼ�괹ֱ��ͣ����
	                                            //                                                      l32[LOGO_CALL_TIME]:ͼ���ܹ���ӵĴ���
	                                            //                                                      l32[LOGO_FIRST_ADD_FLAG]:ͼ���״���ӱ��0:�״� 1:���״�
                                                //                                                      l32[LOGO_CUR_BG_WIDTH]:ͼ����ӻ��ڵı������
                                                //                                                      l32[LOGO_CUR_BG_HEIGHT]:ͼ����ӻ��ڵı����߶�
	
}TLogo;			//ͼ��

typedef struct tEncParam
{
	u32		u32EncoderType;				//����������
	l32		l32FrameRate;				//֡��
	l32		l32BitRate;					//���ʣ�bps��
	l32		l32MinQP;					//��С��������
	l32		l32MaxQP;					//�����������
	l32		l32IFrameInterval;			//I֡���������I֡��P��B֡����
	l32		l32PacketMode;				//���ģʽ
	l32		l32EncodeWidth;				//������
	l32		l32EncodeHeight;			//����߶ȣ����=0&�߶�=0��ʾ����Ӧ��Ŀǰ��������mpeg4��
	l32		l32FrameDropRate;			//����������֡�ʣ�0��ʾ����֡���ٶ����ȣ���0��ʾ�ж�֡���������ȣ�����Ϊ10�ı�������10%Ϊ��λ��
	u32		u32EncodeCycles;			//����һ֡������������Ŀǰ���ڴ������map����Ƶ(����Ϊ��λ)
	l32		l32EncodeYUVType;			//����YUV���ͣ�420��422��444����Ŀǰ��֧�ֶ�420ͼ����룬�˲���û���õ�
    l32     l32CoreNum;                 //�����õ����ں�����1����map���룬2����map���룩
    l32		l32Limitation;				//���������ƣ���
    l32     l32SliceLen;
	
}TEncParam;	//�����ʼ������


typedef struct tEncoderInput
{
	TImage		*aptImage[MAX_IMAGES_IN_ONE+1];			//����ͼ���飨��NULLΪ������־��
	TLogo		*aptLogo[MAX_LOGOS_IN_IMAGE+1];			//ͼ�꣨��NULLΪ������־��
	TBanner		*aptBanner[MAX_BANNERS_IN_IMAGE+1];		//�������NULLΪ������־��

	u8          u8EncMapNumber;                         //���ڱ����map���
	u8			*pu8Bitstream;							//�����������
	l32			l32IsKeyFrame;							//����֡���ͣ����룩 1: ǿ�Ʊ�I֡  0���������Զ�
	u8			*pu8MotionInfo;							//�˶���Ϣ����ʹ�ñ�����ΪNULL��44x36��ȼ�0~9��
	l32 	    l32MotionInfoLen;		                //�˶���Ϣ����
	l32	   		l32OutputPSNR;							//�Ƿ����PSNRֵ

	u16			u16MergeStyle;							//����ϳ�ģʽ
	u8			u8BackgroundR;							//����ϳɱ���ɫR
	u8			u8BackgroundG;							//����ϳɱ���ɫG
	u8			u8BackgroundB;							//����ϳɱ���ɫB
    u8          u8BoundaryR;                            //����ϳɸ�·ͼ��ͳһ�߽�����ɫR
    u8          u8BoundaryG;                            //����ϳɸ�·ͼ��ͳһ�߽�����ɫG
    u8          u8BoundaryB;                            //����ϳɸ�·ͼ��ͳһ�߽�����ɫB
    u8          u8BoundaryWidth;                        //����ϳɸ�·ͼ��ͳһ�߽��߿�ȣ��ݲ������ã�
	l32			l32DisplayImageType;					//�ϳɺ��ֱ����ʾͼ�����ͣ�P��N��: P��0�� N��1��
	u8			*pu8DisplayImage;						//�ϳɺ��ֱ����ʾͼ��ΪNULL�����,��ͼ��ϳ�ģʽ��������������NULL���Խ�ʡcpu��
	l32			l32SkipPreprocess;						//ǰ������, ���ⲿ�����Ƿ���ǰ����	
	l32			l32OutPutMode;							//����ϳɿ��أ���264�б���Ϊ���ͼ������D1��CifΪ��ͼ��ͼ��������Ϊ1��ʾCif���
}TEncoderInput;		//�����������


typedef struct tEncoderOutput
{
	l32		l32BitstreamLen;			//�����������
	l32		l32IsKeyFrame;				//����֡���ͣ������ 1: �������I֡  0���������P֡
	l32		l32EncodeWidth;				//ʵ�ʱ�����
	l32		l32EncodeHeight;			//ʵ�ʱ���߶�
	float	fPSNR;						//PSNRֵ
	u32		u32ConsumedCycles;			//��������������
	l32		l32MotionInfoValid;			//�˶���Ϣ�Ƿ���Ч
	l32		l32LogoNum;					//ͼ����(ʵ����ʾ)
	l32		l32BannerNum;				//�����(ʵ����ʾ)
    //����Ϊ���Խӿ�
    u8      *pu8PpImage;                //ǰ�����δѹ������������ͼ��
    u8      *pu8Pp2encImage;            //ǰ����ѹ������������ͼ��
    
}TEncoderOutput;		//�����������


typedef struct tDecParam
{
	u32		u32DecoderType;					//����������
	l32		l32PacketMode;					//���ģʽ
	l32		l32DecodeYUVType;				//�������YUV���ͣ�420��422��444�� Ŀǰ��֧��420��ͼ�����������֧��������ʽ����Ҫimageprocess���ṩ֧��
	u32		u32DecodeCycles;				//����һ֡������������Ŀǰ���ڴ������map����Ƶ(����Ϊ��λ)
	
	l32		l32Width;						//����ͼ����(��ѯ״̬ʹ��)
	l32		l32Height;						//����ͼ��߶�(��ѯ״̬ʹ��)
	
}TDecParam;		//�����ʼ������


typedef struct tDecoderInput
{
	u8			*pu8YUV;								//ʵ�����ͼ�󻺳�
	u8			*pu8Bitstream;							//������������
	l32			l32BitstreamLen;						//������������
	l32			l32OutputType;							//���ͼ���ʽ��ԭʼ��С��1/4��1/9��1/16,1/1 , 640x480 ,800x600,1024x768��
	TLogo		*aptLogo[MAX_LOGOS_IN_IMAGE+1];			//ͼ�꣨��NULLΪ������־��
	TBanner		*aptBanner[MAX_BANNERS_IN_IMAGE+1];		//�������NULLΪ������־��
	u8			*pu8MotionInfo;							//�˶���Ϣ����ʹ�ñ�����ΪNULL��
	l32			l32MotionInfoLen;						//�˶���Ϣ����
	l32         l32PostProcess;			                //�Ƿ������� 1���� 0����
	l32         l32SizeChangeEdge;                      //ͼ���Ƿ�ӱ߿� 1���� 0���� Ĭ��Ϊ0�������ӱ߿�,Ŀǰ�����1024x768��720x576��ͼ��ʹ�ã�
	
	
}TDecoderInput;		//�������


typedef struct tDecoderOutput
{
	TImage	    tImage;					//����ʵ�����ͼ��
	l32			l32DecodeWidth;			//����ͼ����
	l32			l32DecodeHeight;		//����ͼ��߶�
	l32			l32IsKeyFrame;			//����֡����
	u32			u32ConsumedCycles;		//��������������
	l32			l32MotionInfoValid;		//�˶���Ϣ�Ƿ���Ч
	l32			l32LogoNum;				//ͼ����
	l32			l32BannerNum;			//�����
    //����Ϊ���Խӿ�
    u8          *pu8Decded;	            //���������ԭʼͼ��
    
}TDecoderOutput;			//�������


typedef struct
{
	u32		u32EncoderType;	             //����������
    u8      u8InUseFlag;                 //�������Ƿ���ʹ���еı�־
    VideoCodecHandle pEncoderHandle;     //�������ͱ�����
	TImage	tImageModel;                 //ǰ������ͼ����Ϣ
    TImage	tImageProcessed;             //ǰ�������������������Ϣ
    u8      u8CurBgR;                    //���浱ǰǰ������ɫ
    u8      u8CurBgG;
    u8      u8CurBgB;
    u16     u16CurMergeStyle;            //��ǰ��ͼ��ϳ�����
    u32     u32CapEncUsableCycles;       //�ɱ���map��Ƶ�õ��ı���һ֡�������������ɼ���������
    u32     u32MergeEncUsableCycles;     //�ɱ���map��Ƶ�õ��ı���һ֡������������ͼ��ϳɱ�������
    u32     u32PreviousEncCycles;        //ǰһ֡�������ĵ�ָ��������
    l32		l32CurFrameRate;		     //��ǰ��������֡��
    u8      *pu8FrameRateControlTable;   //ָ�����֡�ʿ��Ʊ�
    u16     u16FrameCount;               //����֡����������֡�ʿ���
    l32		l32SkipPreprocess;			 //ǰ�����أ�����H263����VGA��GOB���룬ǰ����һ֡����һ��
}TEncoder;


typedef struct
{
	u32		u32DecoderType;              //����������
    u8      u8InUseFlag;                 //�������Ƿ���ʹ���еı�־
    VideoCodecHandle pDecoderHandle;     //�������ͽ�����
	TImage	tImageDecoded;               //�������ͼ����Ϣ
	l32		l32DecodeYUVType;            //������������YUV��ʽ
	
}TDecoder;


/*====================================================================
	������		��ResetLogoStatus
	����		������ͼ��״̬
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����TLogo *ptLogo��ͼ�꣩
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 ResetLogoStatus(TLogo *ptLogo);


/*====================================================================
	������		��VideoInitial
	����		����Ƶ�������Χ��ʼ��
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����u8 u8EncFlag       �Ƿ���б�������Χ��ʼ����ENC_INIT: ��  NO_ENC: ��
	              l32 l32EncodeMaxWidth   �豸��֧�ֵ���������
				  l32 l32EncodeMaxHeight  �豸��֧�ֵ�������߶�
                  u8 u8DecFlag       �Ƿ���н�������Χ��ʼ����DEC_INIT: ��  NO_DEC: ��
                  l32 l32DecodeMaxWidth   �豸��֧�ֵ���������
                  l32 l32DecodeMaxHeight  �豸��֧�ֵ�������߶�
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
	�������ر�˵���� Ŀǰǰ��������֧��420��ʽ��
	                 Ŀǰ�������б������ں˵�ͼ��ͳһΪ420��ʽ��
					 ���Ժ�֧��������ʽ��ǰ�����ʼ������������б�ǰ��������ڲ������޸ģ�
====================================================================*/
l32 VideoInitial(u8 u8EncFlag, l32 l32EncodeMaxWidth, l32 l32EncodeMaxHeight, u8 u8DecFlag, l32 l32DecodeMaxWidth, l32 l32DecodeMaxHeight);


/*====================================================================
	������		��VideoClose
	����		����Ƶ�������Χ�ر�
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����u8 u8EncFlag       �Ƿ���б�������Χ��ʼ����ENC_INIT: ��  NO_ENC: ��
                  u8 u8DecFlag       �Ƿ���н�������Χ��ʼ����DEC_INIT: ��  NO_DEC: ��
	�������˵������
	����ֵ˵��  ����
====================================================================*/
void VideoClose(u8 u8EncFlag, u8 u8DecFlag);

/*====================================================================
������		: VideoCodecGetVersion
����		���ӿڰ汾��Ϣ
�㷨ʵ��	������ѡ�
����ȫ�ֱ�����pvVer          �汾��Ϣ
pl32VerLen     �汾��Ϣbuffer
�������˵������
�������˵������
����ֵ˵��  ���ޡ�              
====================================================================*/
void VideoCodecGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

/*====================================================================
������		: VideoImageProcessGetVersion
����		��ͼ�����汾��Ϣ
�㷨ʵ��	������ѡ�
����ȫ�ֱ�����pvVer          �汾��Ϣ
pl32VerLen     �汾��Ϣbuffer
�������˵������
�������˵������
����ֵ˵��  ���ޡ�              
====================================================================*/
void VideoImageProcessGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

/*====================================================================
	������		��VideoEncoderInitial
	����		����ʹ��������
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle *ptHandle����������ŵ�ַ��
                  TEncParam *ptEncParam�������ʼ��������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
	�������ر�˵���� Ŀǰǰ��������֧��420��ʽ��
	                 Ŀǰ�������б������ں˵�ͼ��ͳһΪ420��ʽ��
====================================================================*/
l32 VideoEncoderInitial(VideoCodecHandle *ptHandle, TEncParam *ptEncParam);


/*====================================================================
	������		��VideoEncoderEncode
	����		������һ֡ͼ��
	�㷨ʵ��	��qcif, cif, 2cif, 4cif, vga, svga, xvga are supported
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������, TEncoderInput *ptEncoderInput���������룩, TEncoderOutput *ptEncoderOutput�����������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ�ܣ�VIDEOSKIP������
====================================================================*/
l32 VideoEncoderEncode(VideoCodecHandle ptHandle, TEncoderInput *ptEncoderInput, TEncoderOutput *ptEncoderOutput);


/*====================================================================
������		��VideoEncoderEncodeStage0
����		������һ֡ͼ��
�㷨ʵ��	��qcif, cif, 2cif, 4cif, vga, svga, xvga are supported
����ȫ�ֱ�������
�������˵����VideoCodecHandle ptHandle����������, TEncoderInput *ptEncoderInput���������룩, TEncoderOutput *ptEncoderOutput�����������
�������˵������
����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ�ܣ�VIDEOSKIP������
====================================================================*/
l32 VideoEncoderEncodeStage0(VideoCodecHandle ptHandle, TEncoderInput *ptEncoderInput, TEncoderOutput *ptEncoderOutput);


/*====================================================================
������		��VideoEncoderEncodeStage1
����		������һ֡ͼ��
�㷨ʵ��	��qcif, cif, 2cif, 4cif, vga, svga, xvga are supported
����ȫ�ֱ�������
�������˵����VideoCodecHandle ptHandle����������, TEncoderInput *ptEncoderInput���������룩, TEncoderOutput *ptEncoderOutput�����������
�������˵������
����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ�ܣ�VIDEOSKIP������
====================================================================*/
l32 VideoEncoderEncodeStage1(VideoCodecHandle ptHandle, TEncoderInput *ptEncoderInput, TEncoderOutput *ptEncoderOutput);


/*====================================================================
	������		��VideoEncoderClose
	����		���رձ�����
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoEncoderClose(VideoCodecHandle ptHandle);


/*====================================================================
	������		��VideoEncoderSetParam
	����		�����ñ���������
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������, TEncParam *ptEncParam���������ò�����
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
	�������ر�˵����Ŀǰ���øú����ɸı�Ĳ��������������Ⱥ͸߶ȣ�����ı�
	                ����ͼ��Ŀ�ߣ����ȹر�ԭ���������ٰ��µĿ�߳�ʼ���µı�����
====================================================================*/
l32 VideoEncoderSetParam(VideoCodecHandle ptHandle, TEncParam *ptEncParam);


/*====================================================================
	������		��VideoEncoderGetStatus
	����		����ȡ����������
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������, TEncParam *ptEncParam��������������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoEncoderGetStatus(VideoCodecHandle ptHandle, TEncParam *ptEncParam);


/*====================================================================
	������		��VideoEncoderGetVersion
	����		����ȡ�������汾
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����void *pvVer��������棩, l32 l32BufLen�����泤�ȣ�, l32 *pl32VerLen����Ϣ���ȣ�, u32 u32EncoderType�����������ͣ�
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoEncoderGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32EncoderType);


/*====================================================================
	������		��VideoEncoderDumpStatus
	����		����ӡ��������Ϣ
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoEncoderDumpStatus(VideoCodecHandle ptHandle);


/*====================================================================
	������		��VideoDecoderInitial
	����		����ʹ��������
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle *ptHandle����������ŵ�ַ��
                  TDecParam *ptDecParam�������ʼ��������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
	�������ر�˵���� Ŀǰ���н������ں������ͼ��ͳһΪ420��ʽ���ٸ����û���ptDecParam->l32DecodeYUVType
	                 ���õ������ʽ����Ӧת����420->422,444��
====================================================================*/
l32 VideoDecoderInitial(VideoCodecHandle *ptHandle, TDecParam *ptDecParam);


/*====================================================================
	������		��VideoDecoderDecode
	����		������һ֡ͼ��
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������, TDecoderInput *ptDecoderInput���������룩, TDecoderOutput *ptDecoderOutput�����������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoDecoderDecode(VideoCodecHandle ptHandle, TDecoderInput *ptDecoderInput,  TDecoderOutput *ptDecoderOutput);


/*====================================================================
	������		��VideoDecoderClose
	����		���رս�����
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoDecoderClose(VideoCodecHandle ptHandle);


/*====================================================================
	������		��VideoDecoderSetPatam
	����		�����ý���������
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������, TDecParam *ptDecParam���������ò�����
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoDecoderSetPatam(VideoCodecHandle ptHandle, TDecParam *ptDecParam);


/*====================================================================
	������		��VideoDecoderGetStatus
	����		����ȡ����������
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������, TDecParam *ptDecParam��������������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoDecoderGetStatus(VideoCodecHandle ptHandle, TDecParam *ptDecParam);


/*====================================================================
	������		��VideoDecoderGetVersion
	����		����ȡ�������汾
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����void *pvVer��������棩, l32 l32BufLen�����泤�ȣ�, l32 *pl32VerLen����Ϣ���ȣ�, u32 u32EncoderType�����������ͣ�
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoDecoderGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen, u32 u32DecoderType);


/*====================================================================
	������		��VideoDecoderDumpStatus
	����		����ӡ��������Ϣ
	�㷨ʵ��	����
	����ȫ�ֱ�������
    �������˵����VideoCodecHandle ptHandle����������
	�������˵������
	����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 VideoDecoderDumpStatus(VideoCodecHandle ptHandle);


/*====================================================================
������	    �� LogoDumpStatus
����	    �� ͼ���뱳��ͼ���״̬��Ϣ
�㷨ʵ��    �� ��
����ȫ�ֱ����� ��
�������˵����TLogo *ptLogo      �����ͼ����Ϣָ����
�������˵���� ����ֵΪͼ������ڱ���ͼ���˶���β��λ��
			   ��ֵ��ʾͼ�곯��ͼ���Ե�˶�����ֵ��ʾͼ��Զ��ͼ���Ե�˶�
			   ���ȼ���ͼ���ˮƽ�˶������Ϊ��ֱ�˶�����Ϊ��ֵ��ʾͼ�����˶�
����ֵ˵��  ��VIDEOSUCCESS���ɹ���VIDEOFAILURE��ʧ��
====================================================================*/
l32 LogoDumpStatus(TLogo *ptLogo);

#endif	//not VIDEO_CODEC_INTERFACE_VER1
