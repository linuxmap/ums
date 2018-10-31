/******************************************************************************
ģ����      ��AacLc������
�ļ���      : aaclcdec_v200.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ�AacLc���������ʹ�����Ͷ��⺯������
����        ��½־��
�汾        ��V200 
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/02/22  V200        ½־��       ��    ��
*******************************************************************************/
#ifndef AACLCDEC_V200_H
#define AACLCDEC_V200_H

#ifdef __cplusplus
extern "C" {
#endif                                         /* __cplusplus */

#include "audcodec_common.h"

enum aaclc_dec_errcode 
{
	ERR_AACLCDEC_SLOWMEM_NULL = ERR_AACLCDEC, //�����ڴ�Ϊ��
	ERR_AACLCDEC_OBJECT_TYPE,                 //�������ʹ���
	ERR_AACLCDEC_FRAMEDEC_NULL,               //����������һ֡������������Ϊ��
	ERR_AACLCDEC_NO_BITS_READ,                //������û�������ɶ�ȡ
	ERR_AACLCDEC_SLOWMEM_SMALL,               //�������ڴ治��
	ERR_AACLCDEC_DECTYPE,                     //�������ʹ���
	ERR_AACLCDEC_BITSIZE,                     //�������ȴ���
	ERR_AACLCDEC_HANDLE_NULL,                 //������Ϊ�մ���
	ERR_AACLCDEC_INOUTBUF_NULL,               //�������뻺��Ϊ�մ���
	ERR_AACLCDEC_VERSION,                     //����汾���� 
	ERR_AACLCDEC_CLOSE,                       //�����ͷ��ڴ����
	ERR_AACLCDEC_CLOSE_NULL,                  //�����ͷ��ڴ�Ϊ��
	ERR_AACLCDEC_PPVHANDLE_NULL,              //ppvHandleΪ��
	ERR_AACLCDEC_NEAACDECOPEN,                //NeAACDecOpen����
	ERR_AACLCDEC_NEAACDECCONFIG,              //NeAACDecSetConfiguration����
	ERR_AACLCDEC_NEAACDECINIT,                //NeAACDecInit����
	ERR_AACLCDEC_FRAMEDECODE,                 //aac_frame_decode����
	ERR_AACLCDEC_ADTSHEAD,                    //ADTSͷ����
	ERR_AACLCDEC_GETSTATUS_NULL,              //״̬��Ϣ���Ϊ��
	ERR_AACLCDEC_NEAACDECOPEN_FREE,           //NeAACDecOpen�ͷ��ڴ����
	ERR_AACLCDEC_NEAACDECCONFIG_FREE          //NeAACDecSetConfiguration�ͷ��ڴ����
};

/*====================================================================
������      : AacLcDecOpen                          
����        : ��ʼ�����������������ڲ�����                                 
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle            ָ����������ָ���ָ��[out]
              ptAudDecParam        ��������ʼ�������ṹ��ָ��[in]
              pvAudMemParam        �������ڴ����ṹ���ָ��[in]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS
              ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcDecOpen(void **ppvHandle, TAudioDecParam *ptAudioDecParam);

/*====================================================================
������      : AacLcDecProcess                          
����        : ����һ֡�����ڲ�����                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : pvHandle                ָ����������ָ��[in]
              ptAudDecInput           ָ���������ṹ��ָ��[in]
              ptAudDecOutput          ָ���������ṹ��ָ��[out]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS
              ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcDecProcess(void *pvHandle, TAudDecInput *ptAudDecInput, TAudDecOutput *ptAudDecOutput);

/*====================================================================                        
������      : AacLcDecClose                                                                 
����        : �������ر�                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle          ָ����������ָ��[in]                                   
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS
              ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcDecClose(void *pvHandle);

/*====================================================================                        
������      : AacLcDecGetStatus                                                                 
����        : �õ�������״̬��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle                 ָ����������ָ��[in]
              ptAudDecStatusParam      ָ�����״̬�����ṹ��ָ��[in/out]                                 
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS
              ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcDecGetStatus(void *pvHandle, TAudioDecStatusParam *ptAudioDecStatusParam);

/*====================================================================                        
������      : AacLcDecGetVersion                                                                 
����        : �õ��������汾��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvVer            �������[out]
              l32BufLen        ���泤��[in]
              pl32VerLen       ��Ϣ����[in/out]                            
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS
              ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcDecGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif

