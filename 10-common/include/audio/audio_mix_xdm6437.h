/*****************************************************************************
ģ   ��   ��: aud_mix
��   ��   ��: audio_mix_xdm6437.h
�� ��  �� ��: audio_process.h, audio_def.h
�ļ�ʵ�ֹ���: ��Ƶ������
��        ��: V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2007/09/24      1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef AUDIO_MIX_XDM6437_H
#define AUDIO_MIX_XDM6437_H
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

/***************************************************/
/*             ��Ƶ������Control ID�Ŷ���            */
/***************************************************/
enum XDM_AudioMixerId
{
	GETMIXER_VERSION = 0,                 //�õ��������汾��
	GETMIXER_STATUS,                      //�õ�������״̬             
}; 

/***************************************************/
/*             ��������ؽṹ������              */
/***************************************************/
//��Ƶ���������ṹ
typedef struct tagAUDIOMIX_KDC_Params
{
	IAUDENC_Params tAudMixParams;			//MUST be first field of all XDAS algs

	XDAS_UInt32 u32AudMixParamAddr;
} TAUDIOMIX_KDC_Params;

//��Ƶ������������ṹ
typedef struct tagAUDIOMIX_KDC_InArgs 
{
	IAUDENC_InArgs tAudEncInArgs;			//MUST be first field of all XDAS algs
	TEnumAudMixMode tAudMixMode;            //��Ƶ����ģʽ

	XDAS_Int32 l32FrameSize;                //ÿ·ÿ֡�������ݳߴ�(��λ:�ֽ�)
	XDAS_Int32 l32MixChNum;                 //����·��
	XDAS_Int16 as16Val[AUDMIX_MAX_CHANNEL]; //ÿ·��������
    u32 u32Reserved;                        //��������
	/*
	TAudMixInput  tAudMixInput;
	TEnumAudMixMode tAudMixMode;
	                              //����ģʽ
	TAudMixBuf **pptInAudBuf;     //ָ�����������ṹ��ָ������
	u32 u32InChList;              //��������ͨ���б� 
    TAudMixBuf **pptOutAudBuf;    //ָ�������N-1ģʽ����ṹ��ָ������
    TAudMixBuf *ptOutNAudBuf;     //Nģʽ����ṹ��ָ��
    u32 u32InSampleCnt;           //ÿ·����������
    u32 u32Reserved;                        //��������
	*/

} TAUDIOMIX_KDC_InArgs;

//��Ƶ������������ṹ
typedef struct tagAUDIOMIX_KDC_OutArgs 
{
	IAUDENC_OutArgs tAudEncOutArgs;			//MUST be first field of all XDAS algs 
    TAudMixOutput  tAudMixOutput;         
} TAUDIOMIX_KDC_OutArgs;

//��Ƶ����״̬�����ṹ
typedef struct tagtAUDIOMIX_KDC_Status 
{
	IAUDENC_Status tAudEncStatus;			//MUST be first field of all XDAS algs

} TAUDIOMIX_KDC_Status;

//��Ƶ������̬�����ṹ
typedef struct tagAUDIOMIX_KDC_DynamicParams 
{
	IAUDENC_DynamicParams  tAudEncDynamicParams;      // MUST be first field of all XDAS algs 
	XDAS_UInt32 u32AudMixDynParamAddr;
	XDAS_UInt32 u32AudMixStatusParamAddr;
} TAUDIOMIX_KDC_DynamicParams;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif   //end of AUDIO_MIX_XDM6437_H 



