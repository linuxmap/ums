/******************************************************************************
ģ����      ��AacLc������
�ļ���      : aaclcenc_codec.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ�AacLc�������������Ͷ���Ͷ��⺯������
����        ��
�汾        ��
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/10/10  1.0         Ҧ��ǿ      ��    ��
*******************************************************************************/
#ifndef AACLCENC_CODEC_H
#define AACLCENC_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif                                           /* __cplusplus */

#include "audio_codec.h"

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
	ERR_AACLCENC_INIT_FREE                     //AacEncInit�ͷŵ��ڴ����
};

/*====================================================================
������      : AacLcEncOpen                          
����        : ��ʼ������������                                  
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle: ָ����������ָ���ָ��[out]
              ptAudEncParam: ��������ʼ�������ṹ��ָ��[in]
              pvAudMemParam:  �������ڴ����ṹ���ָ��[in]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLcEncOpen(void **ppvHandle, TAudEncParam *ptAudEncParam, void *pvAudMemParam);

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
l32 AacLcEncGetStatus(void *pvHandle, TAudEncStatusParam *ptAudEncStatusParam);

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


