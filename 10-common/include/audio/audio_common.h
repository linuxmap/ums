/*****************************************************************************
ģ   ��   ��: audio_common
��   ��   ��: audio_common.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: �汾��Ϣ���ڴ���Ϣ�ṹ�嶨��
��        ��: V100  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
2009/03/26       v100        ½־��      ��    ��
2013/04/10       v101        ½־��      �����ڴ���Ϣ�ṹ��
******************************************************************************/
#ifndef _AUDIO_COMMON_H_
#define _AUDIO_COMMON_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

//�汾��Ϣ����ṹ
typedef struct
{
    void* pvVer;         //�汾��Ϣ����     
    l32 l32BufLen;       //�汾��Ϣ����ռ��С
    u32 u32CodecType;    //���������aec����
    u32 u32Reserve;      
}TAudVerInfoInput;

//�汾��Ϣ����ṹ
typedef struct
{               
    l32 l32VerLen;      //����汾��Ϣ��ռ�ֽ���
    u32 u32Reserve;    
}TAudVerInfoOutput;

//�ڴ���Ϣ����ṹ��
typedef struct
{
    void* pvDMAHandle;              //DMAͨ�����
    void* pvFastMem;                //Ƭ�ڿ����ڴ���
    void* pvSlowMem;                //Ƭ�������ڴ���
    void* pvSlowScratchMem;         //Ƭ��Scratch�ڴ���
    l32 l32FastMemSize;             //Ƭ�ڿ����ڴ��ܴ�С
    l32 l32SlowMemSize;             //Ƭ�������ڴ��ܴ�С
} TAudInputMemParam;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif 



