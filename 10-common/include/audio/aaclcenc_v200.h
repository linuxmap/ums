/******************************************************************************
ģ����      ��AacLc������
�ļ���      : aaclcenc_v200.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ�AacLc�������������Ͷ���Ͷ��⺯������
����        �� ½־�� 
�汾        �� V200
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/02/22  V200        ½־��      ��    ��
*******************************************************************************/
#ifndef AACLCENC_V200_H
#define AACLCENC_V200_H

#ifdef __cplusplus
extern "C" {
#endif                                           /* __cplusplus */
#include "audcodec_common.h"

enum aaclc_enc_errcode
{
	ERR_AACLCENC_SLOWMEM_NULL = ERR_AACLCENC,  //�ڴ�ռ�Ϊ�մ���
	ERR_AACLCENC_SLOWMEM_SMALL,                //�ڴ�ռ䲻��
	ERR_AACLCENC_ENCTYPE,                      //�������ʹ���
	ERR_AACLCENC_BITWIDTH,                     //λ�����
	ERR_AACLCENC_FRAMLEN,                      //֡������
	ERR_AACLCENC_CHANNEL,                      //������Ŀ�ж�
	ERR_AACLCENC_BITRATE,                      //�����ʴ���
	ERR_AACLCENC_BITSIZE,                      //�������ȴ���
	ERR_AACLCENC_INOUTBUF_NULL,                //���������������Ϊ�մ���        
	ERR_AACLCENC_HANDLE_NULL,                  //������Ϊ�մ���  
	ERR_AACLCENC_VERSION,                      //�汾����
	ERR_AACLCENC_CLOSE,                        //�����ͷ��ڴ����
	ERR_AACLCENC_PPVHANDLE_NULL,               //���Ϊ��
	ERR_AACLCENC_INIT,                         //��ʼ������
	ERR_AACLCENC_GETSTATUS,                    //�õ�״̬��Ϣ����
	ERR_AACLCENC_CLOSE_NULL,                   //�ͷŵ��ڴ�Ϊ��
	ERR_AACLCENC_SAMPLERATE,                   //�����ʴ���
	ERR_AACLCENC_INITELEMENTINFO,              //ͨ����ѡ��ͳ�ʼ������            
	ERR_AACLCENC_PSYMAIN_INIT,                 //PsyMain��ʼ������
	ERR_AACLCENC_InitPsyCon_Long,              //PsyMain������ʼ������
	ERR_AACLCENC_InitPsyCon_Short,             //PsyMain�̴���ʼ������
	ERR_AACLCENC_BITUSED,                      //�ڱ��س�ʹ���У�ʹ�õı����������˱��س����������������һ�㲻�ᷢ��
	ERR_AACLCENC_WRITEBITS,                     //д��������
	ERR_AACLACENC_CODE_BOOK_DELTA               //DELTA > 60
};

/*====================================================================
������      : AacLcEncOpen                          
����        : ��ʼ������������                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle: ָ����������ָ���ָ��[out]
              ptAudEncParam: ��������ʼ�������ṹ��ָ��[in]          
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcEncOpen(void **ppvHandle, TAudioEncParam *ptAudioEncParam);

/*====================================================================
������      : AacLcEncProcess                          
����        : ����һ֡                                 
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : pvHandle: ָ����������ָ��[in]
              ptAudEncInput: ָ���������ṹ��ָ��[in]
              ptAudEncOutput: ָ���������ṹ��ָ��[out]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcEncProcess(void *pvHandle, TAudEncInput *ptAudEncInput, TAudEncOutput *ptAudEncOutput);

/*====================================================================                        
������      : AacLcEncClose                                                                 
����        : �������ر�                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]                                   
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcEncClose(void *pvHandle);

/*====================================================================                        
������      : AacLcEncGetStatus                                                                 
����        : �õ�������״̬��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]
              ptAudEncStatusParam: ָ�����״̬�����ṹ��ָ��[in/out]                                 
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcEncGetStatus(void *pvHandle, TAudioEncStatusParam *ptAudioEncStatusParam);

/*====================================================================                        
������      : AacLcEncGetVersion                                                                 
����        : �õ��������汾��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvVer: �������[out]
              l32BufLen: ���泤��[in]
              pl32VerLen: ��Ϣ����[in/out]                          
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLcEncGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


