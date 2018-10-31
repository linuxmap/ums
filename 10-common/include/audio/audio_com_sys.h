/*****************************************************************************
ģ   ��   ��: ��Ƶ��davinci��װ
��   ��   ��: audio_com_sys.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: �������Ͷ���
��        ��: V1.0  Copyright(C) 2006-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�� �� �� ¼:
��       ��      �汾        �޸���      �޸�����
 2007/01/23      1.0         ��  ��      ��    ��
******************************************************************************/
#ifndef AUDIO_COM_SYS_H
#define AUDIO_COM_SYS_H

#ifdef __cplusplus
extern "C" {
#endif

//������·��
#define MAX_MIX_CH_NUM      32

/*��Ƶ�任�ĺ궨��(����)*/         
#define   PROC_BW_MASK          (1)    //λ��任
#define   PROC_CH_MASK          (1<<1) //�����任
#define   PROC_RES_MASK         (1<<2) //�����ʱ任 note
#define   PROC_VOL_MASK         (1<<3) //��������
#define   PROC_POW_MASK         (1<<4) //ƽ������ͳ��
#define   PROC_EXCIT_MASK       (1<<5) //�������� note

/*
//��Ƶ�任�Ĳ����ʱ任ģʽ
typedef enum
{
	PROC_SRC_48K_8K=0,
	PROC_SRC_8K_48K,
	PROC_SRC_48K_16K,
	PROC_SRC_16K_48K,
	PROC_SRC_48K_32K,
	PROC_SRC_32K_48K
}TEnumAdSRCMode;
*/
//Aec type
#ifndef AEC_NEW_TYPE_MP3
#define AEC_NEW_TYPE_MP3	2
#endif

#ifndef AEC_NEW_TYPE_G711
#define AEC_NEW_TYPE_G711	3
#endif

#ifndef AEC_NEW_TYPE_G722
#define AEC_NEW_TYPE_G722	4
#endif

#ifndef AEC_NEW_TYPE_G729
#define AEC_NEW_TYPE_G729	5
#endif

#ifndef AEC_NEW_TYPE_G7221C
#define AEC_NEW_TYPE_G7221C	6
#endif

//����λ��ģʽ
typedef enum
{
	BIT16_MODE = 16,
	BIT32_MODE = 32
}TEnumAdBitWthMode;

//��Ƶ������ģʽ
typedef enum
{
	SRATE_8K = 8000,
	SRATE_16K = 16000,
	SRATE_32K = 32000,
	SRATE_48K = 48000
}TEnumAdSrateMode;

//��ƵCODECģʽ
typedef enum
{
	G711a_CODEC=0,
	G711u_CODEC,
	G7231_CODEC,
	G728_CODEC,
	G729_CODEC,
	ADPCM_CODEC,
	G722_CODEC,
	G7221C_CODEC,
	MP3_CODEC, 
	AAC_CODEC    //2007-7-17 xc add
}TEnumAdCodecMode;


//2007-7-17 xc add
typedef enum
{
	AAC_16k_MONO = 0,
	AAC_16k_STEREO,
	AAC_32k_MONO,
	AAC_32k_STEREO,
	AAC_48k_MONO,
	AAC_48k_STEREO
}TEnumAACType;

//2007-7-17 xc add
typedef union tagAudCodecSubType
{
	TEnumAACType tAacSubType;
}TAudCodecSubType;

//��Ƶ����ģʽ
typedef enum
{
	MIX_16=0,
	MIX_32
}TEnumAdMixMode;

//AEC����ģʽ
typedef enum
{
	AEC_SETREF_MODE=0,                 //�ο��ź�����ģʽ
	AEC_PROC_MODE                      //��������ģʽ
}TEnumAdAecMode;


//��ƵXDM��װģ����������ö�ٶ���
//ע:ģ�������ռ��7��bit(bit24~bit30),���λbit31Ϊ0
typedef enum
{
	ERR_G711ENC = (1<<24),
	ERR_G711DEC = (2<<24),

	ERR_G722ENC = (3<<24),
	ERR_G722DEC = (4<<24),

	ERR_G7221CENC = (5<<24),
	ERR_G7221CDEC = (6<<24),

	ERR_G728ENC = (7<<24),
	ERR_G728DEC = (8<<24),

	ERR_G729ENC = (9<<24),
	ERR_G729DEC = (10<<24),

	ERR_MP3ENC = (11<<24),
	ERR_MP3DEC = (12<<24),

	ERR_ADPCMENC = (13<<24),
	ERR_ADPCMDEC = (14<<24),

	ERR_AEC8K = (15<<24),          //15, 8k��������ģ��
	ERR_AEC16K = (16<<24),         //16, 16k��������ģ��
	ERR_DTMF = (17<<24),           //17, ˫����Ƶģ��
	ERR_MIXER = (18<<24),          //18, ������ģ��
	ERR_SPLIT = (19<<24),          //19, һ·�ֽ���·����ģ��
	ERR_AACENC = (20<<24),         //20   2007-7-17 xc add
	ERR_AACDEC = (21<<24),          //21   2007-7-24 xc add

	ERR_AUDPROC = (22<<24)         //22   2007-8-17 xc add
}TEnumAdErrMode;

#ifdef __cplusplus
}
#endif

#endif





