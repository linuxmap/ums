/******************************************************************************
ģ����	    ��img_merge_public
�ļ���	    ��img_merge_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ����廭��ϳɲ����ṹ��
����		������ϼ
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2007/09/12		1.0		        ����ϼ                 ����
2007/11/02		1.1		        ����ϼ                 ��ӻ���ϳ����ñ߽��߿�Ȳ���
******************************************************************************/
#ifndef _IMG_MERGE_PUBLIC_H_
#define _IMG_MERGE_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//ǰ��ͼ����Ϣ�ṹ��
typedef struct
{
	l32 l32Width;         //ͼ��Ŀ��
	l32 l32Height;        //ͼ��ĸ߶�
	l32 l32IsInterlace;   //ͼ�������(֡��ʽ���߳���ʽ)
	l32 l32YUVType;       //ͼ��ͼ���ʽ(YUV422����YUV420)
	u8 u8DrawFocusFlag;   //�����Ƿ񹴻��߿�ı��,u8DrawfocusΪ1ʱ����
	u8 u8FocuslineR;	  //����߿�ɫR
	u8 u8FocuslineG;	  //����߿�ɫG
	u8 u8FocuslineB;	  //����߿�ɫB
    u8 u8FocusWidth;      //�߿�ͳһ��ȣ��ݲ������ã�
	u8 u8Pos;			  //����λ�ñ��
	u8 u8NoPicInput;      //��ǰ��ͼ�������־λIMG_MERGE_NO_PIC_INPUT
	u32 u32Reserved;	  //��������
} TImageFgParam;

//����ϳ�ģ���ʼ�������ṹ
typedef struct
{  
	u16	u16MergeStyle;	   //����ϳ�ģʽ
	l32 l32Width;          //����ͼ��Ŀ��
	l32 l32Height;         //����ͼ��ĸ߶�
	l32	l32IsInterlace;    //����ͼ�������(֡��ʽ���߳���ʽ)
	l32 l32YUVType;        //����ͼ���ʽ(YUV422����YUV420)
	u8 u8BackgroundR;	   //����ϳɱ���ɫR
	u8 u8BackgroundG;	   //����ϳɱ���ɫG
	u8 u8BackgroundB;	   //����ϳɱ���ɫB
    u8 u8BoundaryR;        //����ϳɸ�·ͼ��ͳһ�߽�����ɫR
    u8 u8BoundaryG;        //����ϳɸ�·ͼ��ͳһ�߽�����ɫG
    u8 u8BoundaryB;        //����ϳɸ�·ͼ��ͳһ�߽�����ɫB
    u8 u8BoundaryWidth;    //����ϳɱ߽��߿�ȣ�ȱʡֵΪ0������ΪCIFʱ�߽��߿��Ĭ��Ϊ2������ΪD1ʱ�߽��߿��Ĭ��Ϊ4��
    u8 u8PreprocessPic;    //PREPROCESS_NO_PIC_FILL_BG ǰ������ͼ����䱳��ɫ
    u8 u8Drawsides;        //ǰ�����л��߿� PREPROCESS_DRAWSIDES
    u8 u8Drawfocus;        //ǰ��ͼ�񹴻�ѡ���߿� ��ֵΪPREPROCESS_DRAWFOCUS��ǰ��ͼ��Ż���ݸ��Ե����û��߿�
	TImageFgParam atImageInput[PIC_MERGE_NUM_MAX];  //ǰ��ͼ����Ϣ
} TImageMergeParam;

//����ϳ�ģ��״̬��ѯ�ṹ��
#define TImageMergeStatusParam TImageMergeParam

//����ϳ�ģ������ṹ��
typedef struct 
{
    u8 *apu8InY[PIC_MERGE_NUM_MAX];  //����ǰ��N·ͼ���Y������ַ
    u8 *apu8InU[PIC_MERGE_NUM_MAX];  //����ǰ��N·ͼ���U������ַ(���YUV��ַ������ſɽ�U��ַ����ΪNULL)
    u8 *apu8InV[PIC_MERGE_NUM_MAX];  //����ǰ��N·ͼ���V������ַ(���YUV��ַ������ſɽ�V��ַ����ΪNULL)
    u8 *pu8OutY;                 //����ϳ�ͼ���Y������ַ
    u8 *pu8OutU;                 //����ϳ�ͼ���U������ַ(���YUV��ַ������ſɽ�U��ַ����ΪNULL)
    u8 *pu8OutV;                 //����ϳ�ͼ���V������ַ(���YUV��ַ������ſɽ�V��ַ����ΪNULL)
} TImageMergeInput;
 
//����ϳ�ģ������ṹ��
typedef struct 
{
    u32 u32Reserved;   //�������� 
} TImageMergeOutput;

//���л�ģ���ʼ�������ṹ
typedef struct
{  
	l32 l32BgWidth;          //����ͼ��Ŀ��
	l32 l32BgHeight;         //����ͼ��ĸ߶�
	l32 l32BgIsInterlace;    //����ͼ�������(֡��ʽ���߳���ʽ)
	l32 l32BgYUVType;	     //����ͼ��YUV����
	l32 l32FgWidth;          //ǰ��ͼ��Ŀ��
	l32 l32FgHeight;         //ǰ��ͼ��ĸ߶�
	l32	l32FgIsInterlace;    //ǰ��ͼ�������(֡��ʽ���߳���ʽ)
	l32 l32FgYUVType;	     //ǰ��ͼ��YUV����
	l32 l32Top;              //ǰ��ͼ��ֱλ��ƫ��
	l32 l32Left;             //ǰ��ͼ��ˮƽλ��ƫ��
	l32 l32TopCutLine;       //ǰ���Ϸ��ü��߶�
	l32 l32BottomCutLine;    //ǰ���·��ü��߶�
	l32 l32LeftCutLine;      //ǰ�����ü����
	l32 l32RightCutLine;     //ǰ���Ҳ�ü����
}TImageAddImageParam;

//���л�ģ��ͳ����Ϣ�ṹ��
#define TImageAddImageStatusParam TImageAddImageParam

//���л�ģ������ṹ��
typedef struct 
{
    u8 *pu8FgYUV;    //ǰ��ͼ���ַ
    u8 *pu8BgYUV;    //����ͼ���ַ
}TImageAddImageInput;
 
//���л�ģ������ṹ��
typedef struct 
{
    u32 u32Reserved;   //�������� 
}TImageAddImageOutput;

#ifdef __cplusplus
}
#endif

#endif
