/******************************************************************************
ģ����	    ��img_resizer_public
�ļ���	    ��img_resizer_public.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����ͼ�����ſ�����ṹ��
����		����ȫ��
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���      �޸�����
2008/06/18		1.0				��ȫ��                  create
******************************************************************************/
#ifndef _IMG_RESIZER_PUBLIC_H_
#define _IMG_RESIZER_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//Դͼ��Ľṹ��Ϣ
typedef struct
{
	l32 l32SrcWidth;     //Դͼ��Ŀ��
	l32 l32SrcHeight;    //Դͼ��ĸ߶�
	l32 l32SrcYUVType;	 //Դͼ���ͼ�����ͣ�ΪYUV420����YUV422
	l32 l32SrcInterlace; //Դͼ���֡������

	l32 l32SrcTopCutLine;     //����Ĳü���������ӦΪ2�ı���
	l32 l32SrcBottomCutLine;  //����Ĳü���������ӦΪ2�ı���
	l32 l32SrcLeftCutPoint;   //��ߵĲü��ĵ�����ӦΪ2�ı���
	l32 l32SrcRightCutPoint;  //�ұߵĲü��ĵ�����ӦΪ2�ı���

	u32 u32Reserved;
}TSrcInfo;

//Ŀ��ͼ��Ľṹ����
typedef struct
{
	l32 l32DstWidth;        //Ŀ��ͼ��Ŀ��
	l32 l32DstHeight;		//Ŀ��ͼ��ĸ߶�
	l32 l32DstYUVType;		//Ŀ��ͼ���ͼ�����ͣ�ΪYUV420����YUV422
	l32 l32DstInterlace;	//Ŀ��ͼ���֡������

	l32 l32DstTopCutLine;     //����Ĳü���������ӦΪ2�ı���
	l32 l32DstBottomCutLine;  //����Ĳü���������ӦΪ2�ı���
	l32 l32DstLeftCutPoint;   //��ߵĲü��ĵ�����ӦΪ2�ı���
	l32 l32DstRightCutPoint;  //�ұߵĲü��ĵ�����ӦΪ2�ı���

	l32 l32TopFillLine;     //�������ӵ���ɫ������ӦΪ2�ı���
	l32 l32BottomFillLine;  //�������ӵ���ɫ������ӦΪ2�ı���
	l32 l32LeftFillPoint;   //��ߵ���ӵ���ɫ������ӦΪ2�ı���
	l32 l32RightFillPoint;  //�ұߵ���ӵ���ɫ������ӦΪ2�ı���

	l32 l32YColor;
	l32 l32UColor;
	l32 l32VColor;          //���ı�Ե����ɫ��Ŀǰ��ɫΪY:0x01,UV:0x80,��ɫ��ȫ�㣬Ҳ���Կ������ó�RGB��������

	u32 u32Reserved;
}TDstInfo;

//ͼ�����Ų���
//���õĽṹ
//ͼ��ͨ�����Žṹ��
//ͼ��Ŀ�Ȱ������ҵĺڱ߿�ȣ�ͼ���ȿ���С��ͼ��Ŀ��
//ͼ��ĸ߶Ȱ������µĺڱ߿��
//ͨ������ṹ�Ϳ���ʵ��Դͼ��������λ�õ�ͼ�����ŵ�Ŀ��ͼ�������λ�ã���֧�ּӺڱ�
//���������ȫ����ʡȥͼ��ϳɵ�����
typedef struct
{
	TSrcInfo tSrcInfo;   //Դͼ��������Ϣ

	TDstInfo tDstInfo;   //Ŀ��ͼ��������Ϣ

    u32 u32Reserved;
}TImageResizerParam;

//ͼ������ģ��״̬�ṹ��
#define TImageResizerStatusParam TImageResizerParam

//ͼ�������������
typedef struct
{
	u8 *pu8SrcYAddr;			//Դͼ��Y������ַ
	u8 *pu8SrcUAddr;			//Դͼ��U������ַ
	u8 *pu8SrcVAddr;			//Դͼ��V������ַ

	l32 l32SrcYStride;          //Դͼ���Y����ֵ
	l32 l32SrcUVStride;			//Դͼ���UV����ֵ

	u32 u32Reserved;
}TImageResizerInput;

//ͼ�������������
typedef struct
{
	u8 *pu8DstYAddr;			//Ŀ��ͼ���Y������ַ
	u8 *pu8DstUAddr;			//Ŀ��ͼ���U������ַ
	u8 *pu8DstVAddr;			//Ŀ��ͼ���V������ַ

	l32 l32DstYStride;          //Ŀ��ͼ���Y����ֵ
	l32 l32DstUVStride;			//Ŀ��ͼ���UV����ֵ

	l32 l32IntraFrameFlag;      //���������
	u32 u32Reserved;
}TImageResizerOutput;

#define RESIZER_MODE_EXPAND   0xaaaa
#define RESIZER_MODE_NEAREST  0x5555
//�������ṹ���u32Reservedָ������Ľṹ��
typedef struct
{
    u32 u32ResizerModeExpend;     //��չ���ͣ���Ҫ������ĺ�RESIZER_MODE_EXPAND��ֵ
    l32 l32ResizerMode;           //����ģʽ��Ŀǰֻ֧���ٽ���RESIZER_MODE_NEAREST

    u32 u32Reserved;
}TReszierMode;
#ifdef __cplusplus
}
#endif

#endif //_IMG_RESIZER_PUBLIC_H_
