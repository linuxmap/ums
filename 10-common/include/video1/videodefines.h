/******************************************************************************
ģ����	    �� VIDEODEFINES
�ļ���	    �� VIDEODEFINES.h
����ļ�	�� ��
�ļ�ʵ�ֹ��ܣ� ����������õ��ĺ궨��
---------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
01/18/2007  1.0          �Բ�                  ����
01/18/2008  1.1         ������                 ����ͼ�걳��ͼ��ɨ�跽ʽ����
                                               ��ǰ֧��ͼ�������Ⱥ͸߶ȸ�Ϊ1920��1080
                                               ����ͼ��720p��1080p��ߵĺ궨��
**************************************************************************************/
#ifndef VIDEO_DEFINES

#define VIDEO_DEFINES

#ifdef __cplusplus
extern "C" {
#endif

#define ALIGN_DEFAULT 8 //8�ֽڶ���

//�����ʽ
//h261:no rtp packet info
#define H261_PACKET_NO_RTPINFO		0

//h261:has rtp packet info
#define H261_PACKET_RTPINFO		    1

//h263:263
#define H263_PACKET_BY_263			0

//h263:263+
#define H263_PACKET_BY_263PLUS		1

//h264:annexb
#define H264_PACKET_BY_ANNEXB		0

//h264:rtp
#define H264_PACKET_BY_RTP			1

//�����������
typedef enum
{
    VCODEC_H261 = 1,  //H261�����������
    VCODEC_H263,      //H263�����������
    VCODEC_H264,      //H264�����������
    VCODEC_MPEG2,     //MPEG2�����������
    VCODEC_MPEG4,     //MPEG4�����������
    VCODEC_VIDUNIT,   //VIDUNIT����,��ȡ�汾��Ϣ
    VCODEC_JPEG,      //JPEG�����������
    VCODEC_H264_HP,   //H264HP����������ͣ�����ͳһ���ã�
    VCODEC_PNG,
    VCODEC_GPU_H264,  //H.264 GPU���������
    VCODEC_NONE       //��֧�ֵı����������
}CODECTYPE;

//��Ƶ��ʽ
typedef enum
{
    VID_PAL_MODE = 1,     //PAL��ʽ,ÿ��25֡
    VID_NTSC_MODE,        //NTSC��ʽ,ÿ��30֡
    VID_VGA_MODE,         //PC����ɼ�ģʽ
    VID_720P_MODE,        //720P��Ƶ�ɼ�ģʽ
    VID_1080P_MODE,       //1080P��Ƶ�ɼ�ģʽ
    VID_1080I_MODE,       //1080I��Ƶ�ɼ�ģʽ
    VID_TRANSCODE_MODE,   //ת����Ƶ�ɼ�ģʽ
    VID_NONE_MODE         //��֧�ֵ���ʽ
}VIDEOMODETYPE;

//�����ȼ��궨��
#define ENC_QUALITY_LEVEL_AUTO        0        //�Զ�ѡ����뼶��
#define ENC_QUALITY_LEVEL_1         (1 << 8)  //����ٶȼ������
#define ENC_QUALITY_LEVEL_2         (1 << 9)  //���ټ������
#define ENC_QUALITY_LEVEL_3         (1 << 10) //�е��ٶȱ���
#define ENC_QUALITY_LEVEL_4         (1 << 11) //���ټ������
#define ENC_QUALITY_LEVEL_5         (1 << 12) //�е������������
#define ENC_QUALITY_LEVEL_6         (1 << 13) //�Ϻ������������
#define ENC_QUALITY_LEVEL_7         (1 << 14) //��������������
#define ENC_QUALITY_LEVEL_11         (1 << 16) //HP���뵥�߳�
#define ENC_QUALITY_LEVEL_13         (1 << 18) //HP������߳�

//��������
#define ENC_QUALITY_PRIOR  ENC_QUALITY_LEVEL_4

//�ٶ�����
#define ENC_SPEED_PRIOR  ENC_QUALITY_LEVEL_2

//HP���뵥�߳�
#define ENC_HP_ST ENC_QUALITY_LEVEL_11
//HP������߳�
#define ENC_HP_MT ENC_QUALITY_LEVEL_13

//���������ȼ�
#define DEC_QUALITY_LEVEL_AUTO   0          //�Զ�ѡ����뼶��
#define DEC_SPEED_PRIOR         (1 << 1)    //�����ٶ�����
#define DEC_QUALITY_PRIOR       (1 << 2)    //������������

//����ϳ�����ͼ����
#define MAX_IMAGES_IN_ONE		16

//���ͼ��ͺ����������
#define MAX_LOGOS_IN_IMAGE		32
#define MAX_BANNERS_IN_IMAGE	32

//�ƶ�֡��������
typedef enum
{
    MOTION_DETECT_SENSITIVE_1 = 1,  //�����ȼ���1���ǳ�������
    MOTION_DETECT_SENSITIVE_2,      //�����ȼ���2��������
    MOTION_DETECT_SENSITIVE_3,      //�����ȼ���3������
    MOTION_DETECT_SENSITIVE_4,      //�����ȼ���4���Ƚ�����
    MOTION_DETECT_SENSITIVE_5       //�����ȼ���5���ǳ�����
}MOTIONDETECTSENSITIVELEVEL;

#define MAX_FINE_TUNING_VALUE 10    //�ƶ����΢��ֵ�����ֵ

#define MIN_FINE_TUNING_VALUE -10   //�ƶ����΢��ֵ����Сֵ

//�ƶ��������������
#define MAX_MOTION_SURVEIL_NUM 16

//����Ӧ̨��һ����������
#define MAX_CHAR_IN_ADAPTIVE_LOGO 1000

//ͼ���ʽ����
//֡��ʽ
#define FRAME_FORMAT   0x01

//����ʽ
#define FIELD_FORMAT   0x02

//���вɼ���֡��ʽ��ʽ
#define FRAME_I_FORMAT   0x03

//��·����״̬��־
typedef enum
{
    NEED_DEC = 0x01,  //��Ҫ����
    NO_NEED_DEC,      //������룬��BUF����
    INVALID_DEC       //�����룬BUF������
}MULTI_DEC_STATUS_TYPE;

//ͼ�걳��ͼ��ɨ�跽ʽ����
typedef enum
{
    IMAGE_INTERLACE = 0x10, //����ɨ��
    IMAGE_PROGRESIVE        //����ɨ��
}IMAGE_SCAN_TYPE;

//ͼ��ı�����ʽ(I֡����P֡)
typedef enum
{
	I_PICTURE = 0x01,  //I֡
	P_PICTURE,         //P֡
	SKIP_PICTURE,      //����֡
	DROP_PICTURE,      //��֡
    B_PICTURE          //B֡
}PICTURETYPE;

//ͼ���������Ͷ���
typedef enum
{
	QUALITY_ON = 0,
	QUALITY_OFF,
    BILINEAR,
	IMAGE_ZOOM_TYPE_MAX
}ZOOMTYPE;

//PN��ת��
//������������Ƿ�Ϊһ��
#define SAME_BUFFER        1
#define DIFFERENT_BUFFER   0

//ͼ�����ʽ
#define KDC_NTSC	78
#define KDC_PAL	    80

//�汾��Ϣ�ʹ�������Ϣ�ĳ���
#define INFO_BUFFER_LEN 100

//���سɹ�����ʧ�ܵĶ���
//success
//����ɹ������
#define  VIDEO_SUCCESS		0
//����ɹ������
#define  VIDEO_NO_OUT		1
//failure
#define  VIDEO_FAILURE      -1
//�����ڱβ��ܴ���
#define VID_DEC_EC_UNSUPPORT -2

//ͼ�����Ͷ���
#define  YUV400     400    //Monochrome
#define  YUV444     444    //ȫ��������ÿ4��Y������4��U������4��V
#define  YUV422     422    //UYVY��ʽ ÿ4��Y����2��U��2��V, YUV��ͬһƽ���� U0 Y0 V0 Y1 U1 Y2 V1 Y3 ��
#define  YUV422P    4221   //YUV Plane��ʽ
#define  YUV420     420    //������ƽ�棬Yƽ�棬Uƽ�棬Vƽ�棬����Uƽ���Vƽ���ΪYƽ���1/4  Y0 Y1 Y2 Y3.. U0 U1.. V0 V1..
#define  YUYV		4201   //ÿ4��Y����2��U��2��V, YUV��ͬһƽ����,   Y0 U0 Y1 V0 Y2 U1 Y3 V1 ��
#define  NV12       42012  //������ƽ�棬��Y����ƽ���UV��֯��ƽ�� Y0 Y1...Yn   U0 V0 U1 V1...
#define  GM8180_YUV420     81803
#define  GM8180_YUV420_2D  81802
#define  GM8180_YUV420_3D  81803

//rgb���Ͷ���
typedef enum
{
	RGB1   = 1,
	RGB4   = 4,
    RGB8   = 8,
	RGB565 = 16,
	RGB555 = 15,
	RGB24  = 24,
	RGB32  = 32 //ÿ�����ݵ�Ԫ��ռ�õ�ʵ�ʴ�С
}RGBTYPE_t;

//����ͼ���ͼ������
typedef enum
{
    GLOBOSITY = 1,  //������״
    RAINBOW,        //�߲�ɫ,�ʺ�
    PURE_COLOR,     //��ɫ
    RAINBOW_HD,         //�߲�ɫ,��׼��ɫ�ʺ�
    PATTERN_NONE    //��֧�ֵ�ͼ������
}PATTERNTYPE;

//�˲�������
typedef enum
{
	FILTER_VERTICAL = 1,  //��ֱ�˲���ʽ,����ȥ����ʽ���ӻ�����˸ЧӦ
	FILTER_NONE           //��֧�ֵ��˲�����
}FILTERTYPE;

//��ǰ֧��ͼ�������Ⱥ͸߶�
#define   MAX_FRAME_WIDTH   1920
#define   MAX_FRAME_HEIGHT  1088

//һ֡ͼ�������������˵����ֵ
#define MAX_MOSAIC_IN_ONE_FRAME 32

//ͼ��״̬����
#define LOGO_STATUS_LEN		20

//���ͼ��������
#ifndef ARCH_ARM_IOS
#define MAX_LOGO_NUM		36
#else
#define MAX_LOGO_NUM		32
#endif

//YUVͼ���ߵĺ궨��
#define YUV_P_D1_WIDTH          720		  // YUVͼ��P��D1ͼ��Ŀ��
#define YUV_P_D1_HEIGHT			576		  // YUVͼ��P��D1ͼ��ĸ߶�
#define YUV_P_4CIF_WIDTH		704		  // YUVͼ��P��4CIFͼ��Ŀ��
#define YUV_P_4CIF_HEIGHT		576		  // YUVͼ��P��4CIFͼ��ĸ߶�
#define YUV_P_2CIF_WIDTH		352		  // YUVͼ��P��2CIFͼ��Ŀ��
#define YUV_P_2CIF_HEIGHT		576		  // YUVͼ��P��2CIFͼ��ĸ߶�
#define YUV_P_CIF_WIDTH			352		  // YUVͼ��P��CIFͼ��Ŀ��
#define YUV_P_CIF_HEIGHT		288		  // YUVͼ��P��CIFͼ��ĸ߶�
#define YUV_P_NINETH_D1_WIDTH   240       // YUVͼ��P��240x192ͼ��Ŀ��
#define YUV_P_NINETH_D1_HEIGHT  192       // YUVͼ��P��240x192ͼ��ĸ߶�
#define YUV_N_NINETH_D1_WIDTH   240       // YUVͼ��N��240x160ͼ��Ŀ��
#define YUV_N_NINETH_D1_HEIGHT  160       // YUVͼ��N��240x160ͼ��ĸ߶�
#define YUV_P_QCIF_WIDTH		176		  // YUVͼ��P��QCIFͼ��Ŀ��
#define YUV_P_QCIF_HEIGHT		144		  // YUVͼ��P��QCIFͼ��ĸ߶�
#define YUV_P_NINETH_CIF_WIDTH  112	      // YUVͼ��P��112x96ͼ��Ŀ��
#define YUV_P_NINETH_CIF_HEIGHT 96		  // YUVͼ��P��112x96ͼ��ĸ߶�

#define YUV_N_D1_WIDTH			720		  // YUVͼ��N��D1ͼ��Ŀ��
#define YUV_N_D1_HEIGHT			480		  // YUVͼ��N��D1ͼ��ĸ߶�
#define YUV_N_4CIF_WIDTH		704		  // YUVͼ��N��4CIFͼ��Ŀ��
#define YUV_N_4CIF_HEIGHT		480		  // YUVͼ��N��4CIFͼ��ĸ߶�
#define YUV_N_2CIF_WIDTH		352		  // YUVͼ��N��2CIFͼ��Ŀ��
#define YUV_N_2CIF_HEIGHT		480		  // YUVͼ��N��2CIFͼ��ĸ߶�
#define YUV_N_CIF_WIDTH			352		  // YUVͼ��N��CIFͼ��Ŀ��
#define YUV_N_CIF_HEIGHT		240		  // YUVͼ��N��CIFͼ��ĸ߶�
#define YUV_N_QCIF_WIDTH		176		  // YUVͼ��N��QCIFͼ��Ŀ��
#define YUV_N_QCIF_HEIGHT		120		  // YUVͼ��N��QCIFͼ��ĸ߶�
#define YUV_N_NINETH_CIF_WIDTH  112	      // YUVͼ��N��112x80ͼ��Ŀ��
#define YUV_N_NINETH_CIF_HEIGHT 80		  // YUVͼ��N��112x80ͼ��ĸ߶�

#define YUV_WXGA_WIDTH          1280      // YUVͼ��WXGAͼ��Ŀ��
#define YUV_WXGA_HEIGHT         800       // YUVͼ��WXGAͼ��ĸ߶�
#define YUV_XGA_WIDTH			1024	  // YUVͼ��XGAͼ��Ŀ��
#define YUV_XGA_HEIGHT			768		  // YUVͼ��XGAͼ��ĸ߶�
#define YUV_SVGA_WIDTH			800	      // YUVͼ��SVGAͼ��Ŀ��
#define YUV_SVGA_HEIGHT			600		  // YUVͼ��SVGAͼ��ĸ߶�
#define YUV_VGA_WIDTH			640	      // YUVͼ��VGAͼ��Ŀ��
#define YUV_VGA_HEIGHT			480	      // YUVͼ��VGAͼ��ĸ߶�
#define YUV_SUBQCIF_WIDTH		128   	  // YUVͼ��SUBQCIFͼ��Ŀ��
#define YUV_SUBQCIF_HEIGHT		96   	  // YUVͼ��SUBQCIFͼ��ĸ߶�

#define YUV_720P_WIDTH          1280      // YUVͼ��720Pͼ��Ŀ��
#define YUV_720P_HEIGHT         720       // YUVͼ��720Pͼ��ĸ߶�
#define YUV_1080P_WIDTH         1920      // YUVͼ��1080Pͼ��Ŀ��
#define YUV_1080P_HEIGHT        1080      // YUVͼ��1080Pͼ��ĸ߶�

//����ͼ��������
typedef enum
{
    IMG_YUV422_TO_YUV420 = 1, //ͼ��YUV422תΪͼ��YUV420
    IMG_YUV420_TO_YUV422,     //ͼ��YUV420תΪͼ��YUV422
    IMG_YUV420_TO_RGB,        //ͼ��YUV420תΪRGBͼ��
    IMG_YUV422_SPLIT,         //ͼ��YUV422���Ϊ4·YUV420ͼ��
    IMG_ZOOM,                 //ͼ��YUV420����С���Ŵ�
    IMG_MERGE,                //ͼ��YUV420�Ļ���ϳ�
    IMG_BMPTOYUVALPHA,        //BMPͼ��תΪYUVͼ������Alphaͨ��
    IMG_LOGO,                 //��̨��
    IMG_BANNER,               //�Ӻ��
    IMG_BANNER_LOGO,          //�������
    IMG_GENERATE_IMAGE,       //ͼ������
    IMG_MOSAIC,               //��������
    IMG_PN_CHANGE,            //ͼ��P�ƺ�N��ת��
    IMG_ADD_IMAGE,            //���л�
    IMG_YUV422_VGA_ZOOM,      //VGA��YUV422ͼ������
    IMG_ADAPT_16vs9,          //ͼ�������16vs9
    IMG_IMGUNIT,              //ͼ���汾��Ϣ����
    IMG_FILTER_OSD,           //��ʱ�����˲�OSD������
    IMG_MULTI_DEC,            //��·����
    IMG_APT_ZOOM_MOD,         //�����ϲ����ò�������ͼ�񲢼Ӻڱ�
    IMG_MERGE_ZOOM,           //ͼ�����Ų�����ϳ�
    IMG_MULTI_DEC_NEW,        //�µĶ�·����
    IMG_YUV422_ZOOM,          //YUV422ͼ������
    IMG_RESIZER,              //resizer����ģ��
    IMG_MULTI_ENC,            //��·����
    IMG_RGB_ZOOM,             //RBG565����ģ��
    IMG_RENOVATION,           //ͼ��ˢ��ģ��
    IMG_MOTION_DETECT_GM8180, //GM8180оƬ�˶����ģ��
    IMG_GM8180_TO_YUV420,     //GM8180��YUV420֮��Ļ���
    IMG_COMMON_ADDLOGO,       //GM8180��ͼ�ϼ�LOGO
    IMG_GM8180ADDMOSAIC,      //GM8180��ͼ�ϼ�MOSAIC
    IMG_DEINTERLACE,          //Deinterlace����
    IMG_FILTER,               //ͼ���˲�ģ��
    IMG_DUAL_ENC,             //˫������ģ�飨ͬԴ��
    IMG_SHARP,                //ͼ����ģ��
    IMG_RGBTOYUV,             //RGBתYUV420ģ��
    IMG_TEMPORAL_FILTER,      //ͼ��ʱ���˲�ģ��
	IMG_MOTION_DETECT,        //�ƶ����ģ��
	IMG_MOTION_DETECT_DM365,  //DM365оƬ�˶����ģ��
    IMG_HQ3DIIR_FILTER,       //ͼ��HQ3dIIR�˲�ģ��
    IMG_POSTDENOISE_HQ3D,     //����HQ3D�㷨��ͼ�������
    IMG_ROTATE,               //ͼ����ת(��������)
    IMG_HAZEREMOVE,           //ͼ��ȥ��ģ��	
    IMG_PROCESS_NONE          //ͼ�������ڵ�����
}ImageProcessType;
#define IMG_GM8180ADDLOGO IMG_COMMON_ADDLOGO

#define PIC_MERGE_NUM_MAX 64 //����ϳ�·�������ֵ

//����ϳ����Ͷ���
typedef enum
{
    PIC_NO_MERGE = 0,       //�޻���ϳ�
    PIC_MERGE_ONE,          //һ����ϳ�
    PIC_MERGE_VTWO,         //��С���������ϳ�
    PIC_MERGE_ITWO,         //һ��һС������ϳ�
    PIC_MERGE_THREE,        //������ϳ�
    PIC_MERGE_FOUR,         //��С����Ļ���ϳ�
    PIC_MERGE_SFOUR,        //һ����С�Ļ���ϳ�
    PIC_MERGE_SIX,          //������ϳ�
    PIC_MERGE_SEVEN,        //�߻���ϳ�
    PIC_MERGE_EIGHT,        //�˻���ϳ�
    PIC_MERGE_NINE,         //�Ż���ϳ�
    PIC_MERGE_TEN,          //ʮ����ϳ�
    PIC_MERGE_TEN_2_8,      //ʮ����ϳ�(�����С)
    PIC_MERGE_TEN_1_9,      //ʮ����ϳ�(һ���С)
    PIC_MERGE_TWELVE,       //ʮ������ϳ�
    PIC_MERGE_THIRTEEN,     //ʮ������ϳ�
    PIC_MERGE_FOURTEEN,     //ʮ�Ļ���ϳ�(һ��ʮ��С)
    PIC_MERGE_SIXTEEN,      //ʮ������ϳ�
    PIC_MERGE_SIXTEEN_1_15, //ʮ������ϳ�(һ��ʮ��С)
    PIC_MERGE_TWENTYFIVE,   //��ʮ�廭��ϳ�
    PIC_MERGE_THIRTYSIX,    //��ʮ������ϳ�
    PIC_MERGE_FORTYNINE,    //��ʮ�Ż���ϳ�
    PIC_MERGE_SIXTYFOUR,    //��ʮ�Ļ���ϳ�
    PIC_MERGE_MAX           //����ϳɷ�ʽ���ֵ
} PicMergeStyle;

//merge_zoomģ�黭��ϳ����Ͷ���
//ģ����_����ϳ�·��_[(λ��)�ȷֻ���][(λ��)����_(λ��)С����]
//��С��λ�ö����ֻ�����PIC_MERGE_ZOOM_M9����С���ֵ�λ�ò�������PIC_MERGE_ZOOM_M3_T1����Сλ�ö���������PIC_MERGE_ZOOM_M6_2_B4
//��д���壺T:Top,B:Bottom,L:Left,R:Right
typedef enum
{
    PIC_MERGE_ZOOM_M0 = 0,              //�޻���ϳ�
    PIC_MERGE_ZOOM_M1 = 100,            //һ����ϳ�(ԭPIC_MERGE_ONE)
    PIC_MERGE_ZOOM_M2 = 200,            //������ϳ�(ԭPIC_MERGE_VTWO)
    PIC_MERGE_ZOOM_M2_1_BR1,            //������ϳ�(һ��һС��С�����ڴ����ڵ����½ǣ�ԭPIC_MERGE_ITWO)
    PIC_MERGE_ZOOM_M3_T1 = 300,         //������ϳ�(��С��ȣ�һ�����£�ԭPIC_MERGE_THREE)
    PIC_MERGE_ZOOM_M3_B1,               //������ϳ�(��С��ȣ�����һ��)
    PIC_MERGE_ZOOM_M3_1_B2,             //������ϳ�(һ����С��С��������)
    PIC_MERGE_ZOOM_M3_1_T2,             //������ϳ�(һ����С��С��������)
    PIC_MERGE_ZOOM_M3_1_R2,             //������ϳ�(һ����С������棬��С����)
    PIC_MERGE_ZOOM_M4 = 400,            //�Ļ���ϳ�(ԭPIC_MERGE_FOUR)
    PIC_MERGE_ZOOM_M4_1_R3,             //�Ļ���ϳ�(һ����С��С�������ң�ԭPIC_MERGE_SFOUR)
    PIC_MERGE_ZOOM_M5_1_R4 = 500,       //�廭��ϳ�(һ����С��С��������)
    PIC_MERGE_ZOOM_M5_1_D4,             //�廭��ϳ�(һ����С��С��������)
    PIC_MERGE_ZOOM_M6 = 600,            //������ϳ�(��С��ȣ���������)
    PIC_MERGE_ZOOM_M6_1_5,              //������ϳ�(һ����С��ԭPIC_MERGE_SIX)
    PIC_MERGE_ZOOM_M6_2_B4,             //������(������С��С��������)
    PIC_MERGE_ZOOM_M6_1_B5,             //������(һ����С��С��������)
    PIC_MERGE_ZOOM_M7_3_TL4 = 700,      //�߻���ϳ�(������С���ĸ�С���������Ͻ�)
    PIC_MERGE_ZOOM_M7_3_TR4,            //�߻���ϳ�(������С���ĸ�С���������Ͻ�)
    PIC_MERGE_ZOOM_M7_3_BL4,            //�߻���ϳ�(������С���ĸ�С���������½�)
    PIC_MERGE_ZOOM_M7_3_BR4,            //�߻���ϳ�(������С���ĸ�С���������½ǣ�ԭPIC_MERGE_SEVEN)
    PIC_MERGE_ZOOM_M7_3_BLR4,           //�߻���ϳ�(������С���ĸ�С������������������)
    PIC_MERGE_ZOOM_M7_3_TLR4,           //�߻���ϳ�(������С���ĸ�С������������������)
    PIC_MERGE_ZOOM_M8_1_7 = 800,        //�˻���ϳ�(һ����С��ԭPIC_MERGE_EIGHT)
    PIC_MERGE_ZOOM_M9 = 900,            //�Ż���ϳ�(ԭPIC_MERGE_NINE)
    PIC_MERGE_ZOOM_M10_2_R8 = 1000,     //ʮ����ϳ�(�����С���˸�С�������Ҳ࣬ԭPIC_MERGE_TEN)
    PIC_MERGE_ZOOM_M10_2_B8,            //ʮ����ϳ�(�����С���˸�С���������棬ԭPIC_MERGE_TEN_2_8)
    PIC_MERGE_ZOOM_M10_2_T8,            //ʮ����ϳ�(�����С���˸�С����������)
    PIC_MERGE_ZOOM_M10_2_L8,            //ʮ����ϳ�(�����С���˸�С���������)
    PIC_MERGE_ZOOM_M10_2_TB8,           //ʮ����ϳ�(����������У����¸��ĸ�С���棩
    PIC_MERGE_ZOOM_M10_1_9,             //ʮ����ϳ�(һ���С��ԭPIC_MERGE_TEN_1_9)
    PIC_MERGE_ZOOM_M12_1_11 = 1200,     //ʮ������ϳ�(һ��ʮһС��ԭPIC_MERGE_TWELVE)
    PIC_MERGE_ZOOM_M13_TL1_12 = 1300,   //ʮ������ϳ�(���������Ͻǣ�PIC_MERGE_THIRTEEN)
    PIC_MERGE_ZOOM_M13_TR1_12,          //ʮ������ϳ�(���������Ͻ�)
    PIC_MERGE_ZOOM_M13_BL1_12,          //ʮ������ϳ�(���������½�)
    PIC_MERGE_ZOOM_M13_BR1_12,          //ʮ������ϳ�(���������½�)
    PIC_MERGE_ZOOM_M13_1_ROUND12,       //ʮ������ϳ�(������У�С���滷������)
    PIC_MERGE_ZOOM_M14_1_13 = 1400,     //ʮ�Ļ���ϳ�(һ��ʮ��С��ԭPIC_MERGE_FOURTEEN)
    PIC_MERGE_ZOOM_M14_TL2_12,          //ʮ�Ļ���ϳ�(�������������Ͻ�)
    PIC_MERGE_ZOOM_M15_T3_12 = 1500,    //ʮ�廭��ϳ�(������ʮ��)
    PIC_MERGE_ZOOM_M16 = 1600,          //ʮ������ϳ�(ԭPIC_MERGE_SIXTEEN)
    PIC_MERGE_ZOOM_M16_1_15,            //ʮ������ϳ�(һ��ʮ��С��ԭPIC_MERGE_SIXTEEN_1_15)
    PIC_MERGE_ZOOM_M20 = 2000,          //��ʮ����ϳ�
    PIC_MERGE_ZOOM_M25 = 2500,          //��ʮ�廭��ϳ�(ԭPIC_MERGE_TWENTYFIVE)
    PIC_MERGE_ZOOM_M36 = 3600,          //��ʮ������ϳ�(ԭPIC_MERGE_THIRTYSIX)
    PIC_MERGE_ZOOM_M49 = 4900,          //��ʮ�Ż���ϳ�(ԭPIC_MERGE_FORTYNINE)
    PIC_MERGE_ZOOM_M64 = 6400           //��ʮ�Ļ���ϳ�(ԭPIC_MERGE_SIXTYFOUR)
} PicMergeZoomStyle;

//ǰ��ͼ������Դö������
typedef enum
{
    FG_PIC_INPUT = 1,                           //ǰ����ͼ������
    NO_PIC_INPUT                                //ǰ����ͼ������
} TFgInputSource;
typedef enum
{
    PIC_ZOOM_ONE = 1,       //ȫ������
    PIC_ZOOM_TWO,           //���ֱ������첢����ͼ������
    PIC_ZOOM_THREE,         //���ֱ������첢����Ŀ������
    PIC_ZOOM_FOUR,          //����ԭ�гߴ�,���ںϳɳߴ��ͼ�����в����ñߴ���
    PIC_ZOOM_FIVE           //����ԭ�гߴ�,���ںϳɳߴ��ͼ��ᰴ�ձ��ֱ������첢����ͼ����������
} TPicZoomStyle;

typedef enum
{
    MERGE_INBUF_ONE = 1,     //����ϳ�һ������Buf
    MERGE_INBUF_MULTI        //����ϳ�������Buf
} PicMergeInputFlag;
//ĳ·ͼ���Ƿ񹴻��߿���
typedef enum
{
    NO_DRAW_FOCUS,   //�������߿���
    DRAW_FOCUS       //�����߿���
}TDrawFocusFlag;

//����ϳ���ǰ��ͼ���Ƿ񻭱߿�
#define PREPROCESS_DRAWSIDES   1

//����ϳ���ǰ��ͼ���Ƿ񹴻�ѡ���߿�
#define PREPROCESS_DRAWFOCUS   1

//����ϳ�����ͼ���Ƿ���䱳��ɫ
#define PREPROCESS_NO_PIC_FILL_BG  1

//����ϳ�����ǰ��ͼ������
#define IMG_MERGE_NO_PIC_INPUT  1

//͸��ϵ��
#define FULL_TRANSPARENCY  0    //ȫ͸��
#define NOT_TRANAPARENCY   255  //��͸��

//�Ƿ��̨��ı�־λ
#define LOGO_ENABLE 0x01

//�Ƿ�Ӻ���ı�־λ
#define BANNER_ENABLE 0x01

//�Ƿ��������ı�־λ
#define BANNER_LOGO_ENABLE 0x01

//�Ƿ��˶����ı�־λ
#define MOTION_SURVEIL_ENABLE  0x01

//��ʼ��ʱ�Ƿ�����ƶ�����ڴ��־λ
#define MOTION_SURVEIL_GET_MEM 0x02

//��������⵽���ݶ�ʧʱ����󷵻�5����ʧ��slice
#define MAX_DAMAGED_SLICE_NUM 5

//�Ƿ����ô����ڱεı�־
typedef enum
{
    EC_OFF,             // �رմ����ڱ�
    EC_ON               // ���������ڱ�
}TDECECFLAG;

// ������������չ
typedef enum
{
    ENC_EC = 101,        // �������Ĵ���ָ�����
    ENC_CHECK_BS = 202,  // ������У������
    ENC_NUM_TYPE = 303,  // ���ñ������߳�����չ
    ENC_SET_SLICE = 404, // ���ñ�����Slice������չ
    ENC_SLICE_ALIGN,     // ����Slice���ֽڶ���
    ENC_VA_PARAM         // VA���������չ(������Linux��VA H.264����)
}TEncParamReservedType;

// �������������صȼ�
typedef enum
{
    ENCECLEVELTYPE_OFF,     // �رմ������ز���
    ENCECLEVELTYPE_LEVEL1,  // �����ʽϵ�ʱʹ�õĴ������ز���
    ENCECLEVELTYPE_LEVEL2   // �����ʽϸ�ʱʹ�õĴ������ز���

}TEncECLevelType;

// �������������صȼ�
#define ISNEEDFREEZE(x) ((x) > 95)

// �������������չ
typedef enum
{
    DEC_FEEDBACK = 201, // ����������
    ENC_VA_INPUT        // VA���������Ϣ��չ(������Linux��VA H.264����)
}TEncInputParam;

typedef enum
{
    ENC_VA_OUTPUT  // VA��������Ϣ��չ(������Linux��VA H.264����)
}TEncOutputParam;

// ������������չ
typedef enum
{
    DEC_EC = 100,               // �����ڱα��
    DEC_IMAGE_FORMAT,           // ����ͼ������
    DEC_DEINTERLACE,            // ������Ƿ���Deinterlace������չ���
    DEC_SET_INPUT_FRAME_TYPE,   // ��������������ͼ��֡����ʽ
    DEC_CHECK_BS,               // ������У��������չ
    DEC_MULTI_THREAD,           // ���������߳�������չ
    DEC_GPU_PARAM,              // Ӳ�����������չ(Win7)
    DEC_VA_PARAM                // VAӲ�����������չ(Linux)
}TDecParamReservedType;

// �������������չ
typedef enum
{
    MULTI_DEC_OUT_PUT = 401,    //��·���������չ
    DEC_EC_OUTPUT,              //�����ڱ������չ
    DEC_CHECK_OUTPUT,           //��������У�������Ϣ��չ
    DEC_VA_OUTPUT               // VAӲ���������������չ(Linux)
}TDecOutReservedType;

typedef enum
{
    DEC_OUT_PRE_FRAME = 301  //�������ǰһ֡���
}TDecInputReservedType;

typedef enum
{
    POST_SPECIAL_RESIZER = 501  //�����������ű��
}TPostParamReservedType;

typedef enum
{
    LOGO_SET_ENABLE = 601      //LOGO��������ʹ�ܱ��
}TLogoReservedType;

//�����Deinterlaceʹ�ܱ�־
typedef enum
{
    DEINTERLACE_ENABLE = 0x01, //����deinterlace����
    DEINTERLACE_DISABLE        //�ر�Deinterlace����
}TDeinterlaceFlag;

//�Ƿ��һ�ν����˶����
typedef enum
{
    FIRST_MOTIONSURVEIL,
    NON_FIRST_MOTIONSURVEIL
}MotionsurveilFirstPicFlag;

// deinterlace��������
typedef enum
{
    DEINTERLACE_MODE_1 = 0, //ȫ��deinterlace����
    DEINTERLACE_MODE_2,     //�Ľ��İ볡deinterlace����
    DEINTERLACE_MODE_3,     //ʹ�ó�ͼ��ͨ�˲�Э�����Deinterlace
    DEINTERLACE_MODE_4,     //����ʱ��������˶����ͷ����˲�����deinterlace
    DEINTERLACE_END         //��֧�ֵ�deinteralce����
}TDeinterlaceMode;

//�����Deblock����
typedef enum
{
    DEC_NOSET_DEBLOCK,                  //δ���ý����Deblock
    DEC_SET_DEBLOCK_AGREED_VIDEOUNIT,   //���ý����Deblcok������videounitĬ�Ϸ�ʽ
    DEC_SET_NODEBLOCK,                  //���ý������Deblock����
    DEC_SET_DEBLOCK,                    //���ý������Deblock����
    DEC_SET_DEBLOCK_END
}TDecDeblockSetMode;

typedef enum
{
	QUERY_GPU_CODEC = 1            // ��ѯGPU�����Ƿ�֧��
}TVideoQueryType;

#define H261BLANKFRAME  0x261BF  // ���Ա�ʶ����������ṹ�����չ��������ʾ����261���������֡

//�����붨��
#define ERR_START_VALUE (int)0x80000000         // �����뿪ʼֵ�����λǿ��Ϊ1

//���д�ģ�鶨�壨ռ������bitλ��29��30λ��Ϊ
#define ERR_VID_MOD (1 << 29)      //videounitģ��
#define ERR_IMG_MOD (2 << 29)      //imageunitģ��
#define ERR_OTHER_MOD (3 << 29)    //����ģ��

//��ģ�鶨�壨ռ��7��bitΪ����22-28λ��Ϊ
#define ERR_VID_SELF_MOD (1 << 22)       //videounitģ������
#define ERR_VID_H261ENC_MOD (2 << 22)    //h261��������ģ��
#define ERR_VID_H261DEC_MOD (3 << 22)    //h261��������ģ��
#define ERR_VID_H263ENC_MOD (4 << 22)    //h263��������ģ��
#define ERR_VID_H263DEC_MOD (5 << 22)    //h263��������ģ��
#define ERR_VID_H264ENC_MOD (6 << 22)    //h264��������ģ��
#define ERR_VID_H264DEC_MOD (7 << 22)    //h264��������ģ��
#define ERR_VID_MPEG2ENC_MOD (8 << 22)   //mpeg2��������ģ��
#define ERR_VID_MPEG2DEC_MOD (9 << 22)   //mpeg2��������ģ��
#define ERR_VID_MPEG4ENC_MOD (10 << 22)  //mpeg4��������ģ��
#define ERR_VID_MPEG4DEC_MOD (11 << 22)  //mpeg4��������ģ��
#define ERR_VID_JPEGENC_MOD  (12 << 22)  //JPEG��������ģ��
#define ERR_VID_JPEGDEC_MOD  (13 << 22)  //JPEG��������ģ��
#define ERR_VID_PNGDEC_MOD  (14 << 22)  //PNG��������ģ��
#define ERR_VID_H264ENC_GPU_MOD  (15 << 22)  //h264Ӳ����������ģ��
#define ERR_VID_H264DEC_GPU_MOD  (16 << 22)  //h264Ӳ����������ģ��
#define ERR_VID_QUERY_MOD  (20 << 22)  //VideoQuery��ģ��

#define ERR_IMG_SELF_MOD (1 << 22)       //imageunitģ������
#define ERR_IMG_MERGE_MOD (2 << 22)      //�ϳ���ģ��
#define ERR_IMG_ZOOM_MOD (3 << 22)       //������ģ��
#define ERR_IMG_COLORSPACE_MOD (4 << 22) //��ɫ�ռ�ת����ģ��
#define ERR_IMG_LOGO_MOD (5 << 22)       //��ͼ�ꡢ�����ģ��
#define ERR_IMG_FILTER_MOD (6 << 22)     //�˲���ģ��
#define ERR_IMG_MOTION_MOD (7 << 22)     //�˶������ģ��
#define ERR_IMG_MOSAIC_MOD (8 << 22)     //��������ģ��
#define ERR_IMG_DEBLOCK_MOD (9 << 22)    //Deblockģ��
#define ERR_IMG_PNCHANGE_MOD (10 << 22)	 //PN��ת��ģ��
#define ERR_IMG_DERING_MOD (11 << 22)    //Deringģ��
#define ERR_IMG_BMPTOYUV_ALPHA_MOD (12 << 22) //BMPתΪYUV������Alphaͨ��ģ��
#define ERR_IMG_GENERATE_IMAGE_MOD (13 << 22) //����ͼ��ģ��
#define ERR_IMG_CROSS_FILTER_MOD (14 << 22)   //ͼ��ʮ���˲�ģ��
#define ERR_IMG_ADD_IMAGE_MOD (15 << 22)      //���л���ģ��
#define ERR_IMG_ADAPT_16vs9_MOD (16 << 22)    //ͼ��ת����16:9��ʽ��ģ��
#define ERR_IMG_UYVYTO420_ANDTF_MOD (17 << 22)    //ͼ��UYVYתΪYUV420������ʱ���˲���ģ��
#define ERR_IMG_FILTEROSD_MOD (18 << 22)    //OSD�˵��˲���ģ��H
#define ERR_IMG_APT_ZOOM_MOD (19 << 22)     //�����ϲ����ò���������ģ��
#define ERR_IMG_ZOOM_UYVY_MOD (20 << 22)     //UYVY��ͼ��������ģ��
#define ERR_IMG_MULTIDEC_MOD (21 << 22)     //���������ģ��
#define ERR_IMG_ENHANCEIMAGE_MOD (22 << 22) //ͼ����ǿģ��
#define ERR_IMG_MERGE_ZOOM_MOD (23 << 22)   //�������ϳ�ģ��
#define ERR_IMG_MULTIDEC_NEW_MOD (24 << 22) //�°��·����ģ��
#define ERR_IMG_TEMPORALFILTER_MOD (25 << 22)   //TemporalFilterģ��
#define ERR_IMG_RESIZER_MOD (26 << 22)          //�°�ͨ������ģ���������ʼλ��
#define ERR_IMG_SHARP_MOD (27 << 22)            //ͼ����ģ���������ʼλ��
#define ERR_IMG_GAUSS_FILTER_MOD (28 << 22)     //��˹�˲�ģ���������ʼλ��
#define ERR_IMG_DEINTERLACE_MOD (29 << 22)      //Deinterlaceģ���������ʼλ��
#define ERR_IMG_MULTIENC_MOD (30 << 22)         //��·����ģ���������ʼλ��
#define ERR_IMG_RGB_ZOOM_MOD (31 << 22)         //RGB565����ģ���������ʼλ��
#define ERR_IMG_RENOVATION_MOD (32 << 22)       //RENOVATIONģ���������ʼλ��
#define ERR_IMG_MOTION_DETECT_GM8180_MOD (33 << 22) //GM8180�˶����ģ���������ʼλ��
#define ERR_IMG_DUALENC_MOD (34 << 22)         //��·����ģ���������ʼλ��
#define ERR_IMG_RGBTOYUV_MOD (35 << 22)         //RGB565����ģ���������ʼλ��
#define ERR_IMG_MOTION_DETECT_DM365_MOD (36 << 22) //DM365�˶����ģ���������ʼλ��
#define ERR_IMG_HQ3DIIRFILTER_MOD (37 << 22)   //TemporalFilterģ��
#define ERR_IMG_DECIIRFILTER_MOD (38 << 22)    //����ͼ�����IIR�˲�ģ��
#define ERR_IMG_ROTATE_MOD (39<<22)            //ͼ����תģ��
#define ERR_IMG_HAZEREMOVE_MOD (40<<22) //ͼ��ȥ��ģ������뿪ʼ
//��ģ�鶨�壨ռ��7��bitΪ����22-28λ��Ϊ
#define ERR_VID_API_MOD (1 << 22)              //��ƵAPI�ӿ�ģ���������ʼ
//API��ģ�鶨��
#define ERR_VID_API_ENC_MOD (1 << 20)          //��ƵAPI����ӿ�ģ���������ʼ
#define ERR_VID_API_DEC_MOD (2 << 20)          //��ƵAPI����ӿ�ģ���������ʼ
#define ERR_VID_API_IMG_MOD (3 << 20)          //��ƵAPIͼ����ӿ�ģ���������ʼ

#define ERR_OTHER_START_VALUE (ERR_START_VALUE | ERR_OTHER_MOD)

enum OTHER_MODULE_ERROR_CODE
{
	ERR_OTHER_ERRORCODE_UNFOUND = ERR_OTHER_START_VALUE + 1,
	ERR_OTHER_ERRORCODE_LENGTH_EXCESS_BUFLEN
};

#define CLIP_POSITIVE(x) ((x) >= 0 ? (x) : 0)
#define CLIP_NEGATIVE(x) ((x) >= 0 ? 0 : (-(x)))
#define ABS(x) ((x) >= 0 ? (x) : (-(x)))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define RGB2Y(u8R, u8G, u8B)  	 (((66 * u8R + 129 * u8G + 25 * u8B + 128) >> 8) + 16)
#define RGB2U(u8R, u8G, u8B)     (((-38 * u8R - 74 * u8G + 112 * u8B + 128) >> 8) + 128)
#define RGB2V(u8R, u8G, u8B)	 (((112 * u8R - 94 * u8G - 18 * u8B + 128) >> 8) + 128)

#ifdef __cplusplus
}
#endif

#endif //VIDEO_DEFINES

