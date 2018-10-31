
#ifndef VIDEO_COMMON_DEFINES

#define VIDEO_COMMON_DEFINES


//ͼ���ʽ����

//֡��ʽ
#define FRAMEFORMAT   0x01

//����ʽ
#define FIELDFORMAT   0x02

//ͼ��:720*576
#define IMAGE_SIZE_720576 				0

//ͼ��:1/4 720*576(352*288)
#define IMAGE_SIZE_QUARTER_720576 		1

//ͼ��:1/9 720*576(240*192)
#define IMAGE_SIZE_NINTH_720576 		2

//ͼ��:1/16 720*576(176*144)
#define IMAGE_SIZE_SIXTEENTH_720576 	3

//ͼ��ı�����ʽ(I֡����P֡)
//I֡
#define IPICTURE  0x01

//P֡
#define PPICTURE  0x02

//ͼ��������������
#define  QUALITYON     0
#define  QUALITYOFF    1

//���سɹ�����ʧ�ܵĶ���
#define  VIDEOSUCCESS   0
#define  VIDEOFAILURE     -1

//ͼ�����Ͷ���
#define  YUV422     422
#define  YUV420     420

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

#endif //VIDEO_COMMON_DEFINES

