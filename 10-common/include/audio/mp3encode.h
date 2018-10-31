/******************************************************************************
ģ����      ��
�ļ���      : mp3encode.h
����ļ�    ��
�ļ�ʵ�ֹ��ܣ�mp3 ѹ���������ļ��ӿ��ļ�
����        ��
�汾        ��
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/09/12              ½־��      ���ע��
*******************************************************************************/
#ifndef MP3ENCODE_H
#define MP3ENCODE_H

#define Mp3EncHandle  void *  //mp3���������ָ��
#define MP3_STEREO       0    //������
#define MP3_JOINT_STEREO 2    //����������
#define MP3_MONO         3    //������
#define MP3_ENC_OK       0    //��ʼ���ɹ�
#define MP3_ENC_ERR     -1    //��ʼ��ʧ��

typedef struct
{
    int  iFrequency;   //������
    int  iMode;        //����ģʽ
    int  iBitRate;     //������
    int  iEmphasis;    //
    int  fPrivate;   
    int  fCRC;          
    int  fCopyright;  
    int  fOriginal;   
}TCodecInitIn;

int Mp3EncodeInit(Mp3EncHandle  *pHandle, TCodecInitIn *psIn);
unsigned int Mp3EncodeFrame(Mp3EncHandle  Handle,  void *pSamples,  char *pOutput);
unsigned int Mp3HuffEncodeFrame(Mp3EncHandle  Handle,  void *pSamples,  char *pOutput);//lyg add for mixer

//xuchao add 2005-11-03
//unsigned int Mp3EncMDctFrame(void *Handle, void *pSamples, int *pl32XR);                
void  Mp3EncodeExit(Mp3EncHandle  Handle);
void  SetSpeechFlg(unsigned char * cMp3Stream, int iFlg);
void  GetSpeechFlg(unsigned char * cMp3Stream, int *iFlg);
void  SetMp3EncPara(Mp3EncHandle  Handle,  TCodecInitIn *psIn);
void  GetMp3Version(char*, int, int*);

#endif          /* __CODEC__ */
