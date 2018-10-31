/******************************************************************************
ģ����	    ��img_common_public
�ļ���	    ��img_common_public.h            
����ļ�	��
�ļ�ʵ�ֹ��ܣ�����ͼ��⹫�������ṹ��
����		��zwenyi
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��			�汾			�޸���		�߶���    �޸�����
2007/09/14		1.0				zwenyi                  ����
******************************************************************************/
#ifndef _IMG_COMMON_PUBLIC_H_
#define _IMG_COMMON_PUBLIC_H_

#include "videodefines.h"

#ifdef __cplusplus
extern "C"
{
#endif

//ͼ����Ϣ�Ľṹ��
typedef struct 
{
	u8 *pu8Y;            //ͼ���Y����
	u8 *pu8U;            //ͼ���U����
	u8 *pu8V;            //ͼ���V����(U��V�������Բ���ֵ��ֱ�Ӹ���NULL����ע�������߱���ͬʱ�����)
	l32 l32Width;        //ͼ��Ŀ��
	l32 l32Height;       //ͼ��ĸ߶�
	l32 l32YStride;      //ͼ���Y��������
	l32 l32UVStride;     //ͼ���UV��������
	l32 l32IsInterlace;  //ͼ�������(֡��ʽ���߳���ʽ)
	l32 l32YUVType;      //ͼ��ͼ���ʽ(YUV422����YUV420)
}TImageInfo;

#define MAX_BUF_GROUPS  64

typedef struct
{
    s16 s16Width;                   //����BUF���
    s16 s16Height;                  //����BUF�߶�
    l32 l32BufNums;                 //����BUF��Ŀ
    u8 au8Idx[MAX_BUF_GROUPS];      //��Ӧ��������Ľ�����ID���б�
}TBufGroupInfo;

//������������ֶ���չ����
typedef enum
{
    VidReserved_DebugAddress = 1, //��������
    VidReserved_Unknown
}TEnumVidInputReservedType;

//�������Ͳ����ṹ��
typedef struct 
{
    TEnumVidInputReservedType tVidReservedType; //���������չ����
    u32 u32DebugAddress;                        
}TVidInputReservedDebugAddress;

//�汾��Ϣ����ṹ
typedef struct
{
    void* pvVer;
    l32 l32BufLen; 
    u32 u32CodecType;   //���������CODECTYPE����ͼ��⣨ImageProcessType��
}TVerInfoInput;

//�汾��Ϣ����ṹ
typedef struct
{
    l32 l32VerLen;
    u32 u32Reserve;    
}TVerInfoOutput;

//�����������Ϣ����ṹ
typedef struct
{
    l32 l32ErrCode;
    l32 l32BufLen; 
    u32 u32Reserved;
}TErrCodeInfoInput;

//�����������Ϣ����ṹ
typedef struct
{
    void* pvErrCodeInfo;
    u32 u32Reserved;    
}TErrCodeInfoOutput;

//������Ϣ����ṹ
typedef struct
{
    s8 as8DebugInfo[256]; 
    u32 u32Reserved;
}TDebugInfoInput;


#ifdef __cplusplus
}
#endif

#endif //_IMG_IMAGELIB_H_
