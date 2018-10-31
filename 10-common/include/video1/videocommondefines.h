
#ifndef VIDEO_COMMON_DEFINES

#define VIDEO_COMMON_DEFINES


//ͼ���ʽ����

//֡��ʽ
#define FRAMEFORMAT   0x01

//����ʽ
#define FIELDFORMAT   0x02

//����ͼ���������
//ͼ�󣺽���ͼ������������
#define IMAGE_SIZE_NO_CHANGE			0

//ͼ��:720*576
#define IMAGE_SIZE_720576 				1

//ͼ��:1/4 720*576(352*288)
#define IMAGE_SIZE_QUARTER_720576 		2

//ͼ��:1/9 720*576(240*192)
#define IMAGE_SIZE_NINTH_720576 		3

//ͼ��:1/16 720*576(176*144)
#define IMAGE_SIZE_SIXTEENTH_720576 	4

//ͼ��:720*480
#define IMAGE_SIZE_720480 				5

//ͼ��:1/4 720*480(352*240)
#define IMAGE_SIZE_QUARTER_720480 		6

//ͼ��:1/9 720*480(240*160)
#define IMAGE_SIZE_NINTH_720480 		7

//ͼ��:1/16 720*480(176*120)
#define IMAGE_SIZE_SIXTEENTH_720480 	8

//ͼ��:640*480
#define IMAGE_SIZE_640480				9

//ͼ��:800*600
#define IMAGE_SIZE_800600				10

//ͼ��:1024*768
#define IMAGE_SIZE_1024768				11

//ͼ��:96*80
#define IMAGE_SIZE_SIXTEENTH_352288		12

//ͼ��:112*96
#define IMAGE_SIZE_NINTH_352288			13

//ͼ��:���ڻ���ϳ�ǰ��cif��D1�����ţ�����ϳɵı�����CIF��
#define IMAGE_SIZE_720576_MERGECIF      14

//ͼ��ı�����ʽ(I֡����P֡)
//I֡
#define IPICTURE  0x01

//P֡
#define PPICTURE  0x02

//ͼ��������������
#define  QUALITYON     0
#define  QUALITYOFF    1

//���سɹ�����ʧ�ܵĶ���
#ifdef _LINUX_
typedef enum
{
	VIDEOFAILURE = -1,
	VIDEOSUCCESS,  
    VIDEOSKIP
}imageprocessDrvError_t;
#else

//success
#define  VIDEOSUCCESS		0

//failure
#define  VIDEOFAILURE      -1

//frame not coded
#define	 VIDEOSKIP			1

#endif

//ͼ�����Ͷ���
#define  YUV444     444
#define  YUV422     422
#define  YUV420     420
#define  YUYV		4201		

//rgb���Ͷ���
typedef enum
{
	RGB1   = 1,
	RGB4   = 4,  
    RGB8   = 8,
	RGB565 = 16,
	RGB555 = 15,
	RGB24  = 24,
	RGB32  = 32//ÿ�����ݵ�Ԫ��ռ�õ�ʵ�ʴ�С
}RGBTYPE_t;


//���ɲ���ͼ��Ĳ�ͬͼ��
//������״
#define  GLOBOSITY   4

//��ͬ����ڰ���
#define  BLACKWHITEBAR  5

//�ɰ��𽥼ӵ���
#define   WHITETOBLACK  6

//�߲�ɫ,�ʺ�
#define   RAINBOW   7

//ʱ���˲�ʱ����ֵѡ��
#define   THRESHIGH   0XFF
#define   THRESLOW    0x11

//��ǰ֧��ͼ�������Ⱥ͸߶�
#define   MAXFRAMEWIDTH   1024
#define   MAXFRAMEHEIGHT  768

typedef struct tBanner
{
	l32		l32Width;			//������
	l32		l32Height;			//����߶�
	l32		l32Top;				//������ϽǴ�ֱ����
	l32		l32Left;			//������Ͻ�ˮƽ����
	l32     l32BannerRefPicWidth;    //�����Ӳο�ͼ��Ŀ��
	l32     l32BannerRefPicHeight;   //�����Ӳο�ͼ��ĸ߶�
	l32		l32ShowTimes;		//��ʾ����������һֱ��ʾ��0������ʾ��������ʾ��������ͼ�������
	u8		u8R;				//�����ɫR
	u8		u8G;				//�����ɫG
	u8		u8B;				//�����ɫB
	u8      u8Transparency;     //�����͸��ϵ��(0��ʾȫ͸����255��ʾ��͸����1~254��ʾ����͸��)
	
}TBanner;		//���


#endif //VIDEO_COMMON_DEFINES

