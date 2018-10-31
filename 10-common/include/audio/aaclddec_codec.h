/******************************************************************************
ģ����      ��AacLd������
�ļ���      : aaclddec_codec.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ�AacLc���������ʹ�����Ͷ��⺯������
����        ��
�汾        ��
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2008/01/02  1.0         ��  ɯ      ��    ��
*******************************************************************************/
#ifndef AACLDDEC_CODEC_H
#define AACLDDEC_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif                                         /* __cplusplus */

#include "audio_codec.h"

enum aacld_dec_errcode 
{
	ERR_AACLDDEC_PPVHANDLE_NULL = ERR_AACLDDEC,  //AAC LD���������ΪNULL
	ERR_AACLDDEC_DECTYPE,          //AAC LD���������ʹ���
	ERR_AACLDDEC_SLOWMEM_NULL,     //AAC LD������Ƭ���ڴ�Ϊ��
	ERR_AACLDDEC_NEAACDECOPEN,     //AAC LD�������򿪴���
	ERR_AACLDDEC_HANDLE_NULL,      //AAC LD���������صľ��ָ��Ϊ��
	ERR_AACLDDEC_INOUTBUF_NULL,    //AAC LD���������bufferΪ��
	ERR_AACLDDEC_HEADER,           //AAC LD������ͷ����
	ERR_AACLDDEC_FRAMEDECODE,      //AAC LD������������һ֡����
	ERR_AACLDDEC_GETSTATUS_NULL,   //AAC LD������״̬�����ṹ��ָ��Ϊ��
	ERR_AACLDDEC_VERSION,          //AAC LD��������ȡ�汾����
	ERR_AACLDDEC_CLOSE_NULL,       //AAC LD�������رվ��ָ��Ϊ��
	ERR_AACLDDEC_CLOSE,            //AAC LD�������رմ���
	ERR_AACDEC_FORMAT,             //AAC LD��������ʽ����
	ERR_AACLDDEC_QTALBLE,          //AAC LD��������������С����
	ERR_AACLDDEC_FRAME_LEN,        //AAC LD������֡������
	ERR_AACLDDEC_MP4_STRUCT_NULL,  //AAC LD������MP4�ṹ��ָ��Ϊ��
	ERR_AACLDDEC_OBJ_TYPE,         //AAC LD���������������ʹ���
	ERR_AACLDDEC_SAMPLE_INDEX,     //AAC LD��������������������
	ERR_AACLDDEC_SAMPLE_FREQ,      //AAC LD�����������ʴ���
	ERR_AACLDDEC_GA_CONFIG,        //AAC LD������GA config����
	ERR_AACLDDEC_EPCONFIG,         //AAC LD������EP config����
	ERR_AACLDDEC_WIN_SEQUENCE,     //AAC LD������window sequence����
	ERR_AACLDDEC_WIN_SHAPE,        //AAC LD������window shape����
	ERR_AACLDDEC_WIN_INFO,         //AAC LD��������ȡ����Ϣ����
	ERR_AACLDDEC_MAX_SFB,          //AAC LD����������������Ƶ��������
	ERR_AACLDDEC_PULSE_START_SFB,  //AAC LD������pulse escape���ݴ���
	ERR_AACLDDEC_PCE,              //AAC LD������PCE ����
	ERR_AACLDDEC_BIT_STREAM_LEN,   //AAC LD������һ֡���������ȴ���
	ERR_AACLDDEC_CHANNEL_CONFIG    //AAC LD�������������ô���
};                                                       
                                                         
/*====================================================================
������      : AacLdDecOpen                          
����        : ��ʼ������������                                
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : ppvHandle: ָ����������ָ���ָ��[out]
              ptAudDecParam: ��������ʼ�������ṹ��ָ��[in]
              pvAudMemParam:  �������ڴ����ṹ���ָ��[in]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLdDecOpen(void **ppvHandle, TAudDecParam *ptAudDecParam, void *pvAudMemParam);

/*====================================================================
������      : AacLdDecProcess                          
����        : ����һ֡                                
�㷨ʵ��    : ��                                                  
����ȫ�ֱ���: ��                                                      
����        : pvHandle: ָ����������ָ��[in]
              ptAudDecInput: ָ���������ṹ��ָ��[in]
              ptAudDecOutput: ָ���������ṹ��ָ��[out]              
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                   
====================================================================*/
l32 AacLdDecProcess(void *pvHandle, TAudDecInput *ptAudDecInput, TAudDecOutput *ptAudDecOutput);

/*====================================================================                        
������      : AacLdDecClose                                                                 
����        : �������ر�                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]                                   
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLdDecClose(void *pvHandle);

/*====================================================================                        
������      : AacLdDecGetStatus                                                                 
����        : �õ�������״̬��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvHandle: ָ����������ָ��[in]
              ptAudDecStatusParam: ָ�����״̬�����ṹ��ָ��[in/out]                                 
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLdDecGetStatus(void *pvHandle, TAudDecStatusParam *ptAudDecStatusParam);

/*====================================================================                        
������      : AacLdDecGetVersion                                                                 
����        : �õ��������汾��Ϣ                                                                        
�㷨ʵ��    : ��                                                                              
����ȫ�ֱ���: ��                                                                              
����        : pvVer: �������[out]
              l32BufLen: ���泤��[in]
              pl32VerLen: ��Ϣ����[in/out]                            
����ֵ˵��  : �ɹ�: AUDIO_SUCCESS, ʧ��: ���ش�����                                           
====================================================================*/                        
l32 AacLdDecGetVersion(void *pvVer, l32 l32BufLen, l32 *pl32VerLen);

/*
//������ԭʼ�Ľӿڣ�����Ҫ�������ȵ�txt�ļ�
l32 AacLdDecOpen(void *DecHandle, u8 *InBuf, l32 buffersize);
l32 AacLdDecProcess(void *DecHandle, u8 *InBuf, u8 *OutBuf);
void NeAacLdDecClose(void *pvHandle);
*/

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif

