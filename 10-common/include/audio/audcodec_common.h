/******************************************************************************
ģ����      �� audcodec_common              
�ļ���      �� audcodec_common.h
����ļ�    ����
�ļ�ʵ�ֹ��ܣ� ����뺯������������
---------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��                  �汾            �޸���     �߶���        �޸�����
02/22/2008              1.0             ½־��                    ����
**************************************************************************************/
#ifndef _AUDCODEC_COMMON_H_
#define _AUDCODEC_COMMON_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#define AUDIO_SUCCESS          0        //�ɹ�����ֵ        
#define AUDIO_FAILURE         (-1)      //ʧ�ܷ���ֵ
#define AUDIO_VER_LEN          128      //�汾����Ҫ����С�ڴ�ռ��С

#define TAudioEncStatusParam TAudioEncParam
#define TAudioDecStatusParam TAudioDecParam

//��Ƶ������ģʽ
typedef enum
{
	SAMPLE_RATE_8K = 8000,         //������Ϊ8kHz
	SAMPLE_RATE_16K = 16000,       //������Ϊ16kHz
	SAMPLE_RATE_24K = 24000,       //������Ϊ24kHz
	SAMPLE_RATE_32K = 32000,       //������Ϊ32kHz
	SAMPLE_RATE_48K = 48000        //������Ϊ48kHz
}TEnumAudSampleRate;

//��Ƶ����������
typedef enum
{
	  SAMPLE_RATE96000_INDEX = 0, //������Ϊ96kHz��������0
		SAMPLE_RATE88200_INDEX,     //������Ϊ88.2kHz��������1
		SAMPLE_RATE64000_INDEX,     //������Ϊ64kHz��������2
		SAMPLE_RATE48000_INDEX,     //������Ϊ48kHz��������3
		SAMPLE_RATE44100_INDEX,     //������Ϊ44.1kHz��������4
		SAMPLE_RATE32000_INDEX,     //������Ϊ32kHz��������5
		SAMPLE_RATE24000_INDEX,     //������Ϊ24kHz��������6  
		SAMPLE_RATE22050_INDEX,     //������Ϊ22.05kHz��������7
		SAMPLE_RATE16000_INDEX,     //������Ϊ16kHz��������8
		SAMPLE_RATE12000_INDEX,     //������Ϊ12kHz��������9
		SAMPLE_RATE11025_INDEX,     //������Ϊ11.025kHz��������10 
		SAMPLE_RATE8000_INDEX      //������Ϊ8kHz��������11
}TEnumAudSampleRateIndex;

//����ģʽ
typedef enum
{
	CH_MONO = 1,                  //������
	CH_STEREO                     //˫����
}TEnumAudChannel;

//����λ��ģʽ
typedef enum
{
	BIT_WIDTH_16 = 16,            //����λ��Ϊ16bit
	BIT_WIDTH_32 = 32             //����λ��Ϊ32bit
}TEnumAudBitWidth;

//������ģʽ
typedef enum
{
	AACLC_MO_16K_48K = 48000,//������ʽ���㷨_����_������_������
	AACLC_MO_32K_72K = 72000,
	AACLC_MO_48K_96K = 96000,
	AACLC_ST_16K_48K = 48000,
	AACLC_ST_32K_72K = 72000,
	AACLC_ST_48K_96K = 96000,
}TEnumAudBitRate;

//��������ʼ�������ṹ��
typedef struct
{
    l32 l32Channel;     //����ģʽ��TEnumAudChannel��
    l32 l32BitWidth;    //����λ��ģʽ��TEnumAudBitWidth��
    l32 l32SampleRate;  //��Ƶ������ģʽ��TEnumAudSampleRate��
    l32 l32BitRate;     //������ģʽ(TEnumAudBitRate)
    l32 l32FrameLen;    //����һ֡������
    u32 u32FrameHeadFlag; //ÿ֡�����Ƿ��ͷ��Ϣ(1���У�0����)
    u32 u32Reserved;    //��������
}TAudioEncParam;

//��������ṹ��
typedef struct
{
    u8 *pu8InBuf;      //ָ����������뻺��ָ��
    u32 u32InBufSize;  //���뻺���ֽ��� 
    u8 *pu8OutBuf;     //ָ��������������ָ��
    u32 u32OutBufSize; //��������ֽ���  
    u32 u32Reserved;   //��������
}TAudEncInput;

//��������ṹ��
typedef struct
{       
    u32  u32OutBitStreamSize;   //����������ֽ���
    u32  u32StatisCycles;       //����һ֡Ч��ͳ��
    u32  u32Reserved;           //��������
}TAudEncOutput;

//��������ʼ�������ṹ��                  
typedef struct                                  
{                                               
    l32 l32BitRate;     //������ģʽ(TEnumAudBitRate)
    u32 u32FrameHeadFlag; //ÿ֡�����Ƿ��ͷ��Ϣ(1���У�0����)
    u32 u32Reserved;    //��������                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}TAudioDecParam;        

//����������ṹ��                                                 
typedef struct                                 
{                                              
    u8 *pu8InBuf;            //ָ����������뻺��ָ��   
    u32 u32InBufSize;        //���뻺���ֽ���                                                                                                                                                                                                                                                                                      ���ָ��

    u8 *pu8OutBuf;           //ָ��������������ָ�� 
    u32 u32OutBufSize;       //��������ֽ���                                                                                                                                                                                                                                                                                           
    u32 u32InBitStreamSize;  //ÿ֡�������ֽ���   
    u32 u32SampelFreIndex;   //ÿ֡����������
    u32 u32Channels;         //ÿ֡ͨ����                                                                                                                                                                                                                                                                        ��ֽ���

    u32 u32Reserved;         //��������                                                                                                                                                                                                                                                                                                
}TAudDecInput;      

//����������ṹ��
typedef struct
{               
    u32  u32OutFrameLen ; //ÿ֡���������
    u32  u32StatisCycles; //����һ֡Ч��ͳ��
    u32  u32Reserved;     //��������
}TAudDecOutput; 

//�����붨��
#define ERR_AACLCENC  (15 << 24)    //AACLC������ģ��    
#define ERR_AACLCDEC  (16 << 24)    //AACLC������ģ��
                                                                                                                    
#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


