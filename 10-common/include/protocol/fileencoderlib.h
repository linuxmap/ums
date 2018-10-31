
/*****************************************************************************
ģ����      : FileEncoderLib
�ļ���      : FileEncoderLib.h
����ļ�    : FileEncoderLib.cpp
�ļ�ʵ�ֹ���: FEPlayer Class Define
����        : ����
�汾        : V2.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2004/01/14  2.0         ����      Create
2004/11/02  2.0         ����      ���ӻ�ȡ�ļ���������ý��������Ϣ�Ľӿ�
******************************************************************************/


#ifndef _FILEENCODERLIB_0601_H_
#define _FILEENCODERLIB_0601_H_



//ģ��汾��Ϣ�ͱ���ʱ�� �� �����Ŀ�İ汾�ͱ���ʱ��
extern "C" void fileencoderver();


//ģ�������Ϣ �� �����Ŀ�İ�����Ϣ
extern "C" void fileencoderhelp();



#define  FE_OK                      (u16)0		//FileEncoderLib������ɹ� 
#define  FEERR_BASE_CODE            (u16)20000	//�������׼ֵ

//û�г�ʼ��fe��
#define  FEERR_NOT_INIT_LIB         (u16)(FEERR_BASE_CODE + 1)
//�ڴ�������
#define  FEERR_OUTOFMEMORY          (u16)(FEERR_BASE_CODE + 2)
//��Ч�ı�����������ָ��Ϊ��
#define  FEERR_INVAILD_ENCODER      (u16)(FEERR_BASE_CODE + 3)
//����ͬ���ź���ʧ��
#define  FEERR_CREATE_SEMAPORE      (u16)(FEERR_BASE_CODE + 4)
//��Ч���ļ�  
#define  FEERR_INVAILD_FILE			(u16)(FEERR_BASE_CODE + 5)
//��ʱ����������ȷ    
#define FEERR_TIMER_SET_PARAM       (u16)(FEERR_BASE_CODE + 6)
//��ʱ��ע����߳���
#define FEERR_TIMER_FULL_THREAD     (u16)(FEERR_BASE_CODE + 7)
//�����߳̿�
#define FEERR_ENCORDE_THREAD_NULL   (u16)(FEERR_BASE_CODE + 8)


#define AUDIO_FILE				    (u8)0//
#define VIDEO_FILE				    (u8)1//

#define MAX_FESND_DEST_NUM		    (u8)5
#define FE_MAX_ENCODER_NUMBER	    (u8)28

#define DEFAULT_FE_REPEAT_NUM       (u8)0    //ѭ���ز�
#define DEFAULT_FE_MEDIA_TYPE       (u8)255  //���ļ�������Ϣ����
#define DEFAULT_FE_AUDIO_MODE       (u8)255  //���ļ�������Ϣ����
#define DEFAULT_FE_FRAME_RATE       (u8)0    //���ļ�������Ϣ����

//Frame Header Structure
typedef struct tagFEFrameHdr
{
    u8     m_byMediaType; //ý������
    u8    *m_pData;       //���ݻ���
    u32    m_dwPreBufSize;// m_pData����ǰԤ���˶��ٿռ䣬���ڼ�
						  // RTP option��ʱ��ƫ��ָ��һ��Ϊ12+4+12
						  // (FIXED HEADER + Extence option + Extence bit)
    u32    m_dwDataSize;  //m_pDataָ���ʵ�ʻ����С�����С
    u8     m_byFrameRate; //����֡��,���ڽ��ն�
    u32    m_dwFrameID;   //֡��ʶ�����ڽ��ն�
    u32    m_dwTimeStamp; //ʱ���, ���ڽ��ն�
    u32    m_dwSSRC;      //ͬ��Դ, ���ڽ��ն�
    union
    {
        struct{
			BOOL32    m_bKeyFrame;    //Ƶ֡���ͣ�I or P��
			u16       m_wVideoWidth;  //��Ƶ֡��
			u16       m_wVideoHeight; //��Ƶ֡��
		}m_tVideoParam;
        u8    m_byAudioMode;//��Ƶģʽ
    };
	
}FEFRAMEHDR,*PFEFRAMEHDR;

//�������
typedef struct tagFENetSession
{
	u32   m_dwRTPAddr;	//RTP��ַ(������)
	u16   m_wRTPPort;		//RTP�˿�(������)
	u32   m_dwRTCPAddr;	//RTCP��ַ(������)
	u16   m_wRTCPPort;	//RTCP�˿�(������)
}TFENetSession;

// ״̬
typedef enum {
	FE_CLOSE = 0,   //�ļ��������ѹر�
	FE_OPEN  = 1,   //�ļ��������Ѵ�
	FE_START = 2,   //�ļ������������С�����
	FE_STOP  = 3,   //�ļ�������ֹͣ���ţ�����λ�ö�λ���ļ�ͷ��
	FE_PAUSE = 4,   //�ļ���������ͣ��������ǰ����λ��
	FE_END   = 5      //�ļ����������ڲ�����ϻ��߲��ų����������ţ�����λ�ö�λ���ļ�ͷ��
}emFERunStatus;

// �ļ�������״̬
typedef struct tagFEStatusParam
{
	u32            m_dwFrameNum; //�Ѿ����ŵ�����֡��Ŀ
	emFERunStatus  m_emRunStatus;//����״̬����Ϊ���С���ͣ��ֹͣ���򿪡��ر�
}TFEStatusParam, *PTFEStatusParam;


//�ļ��������ļ��� �ļ�Դ����
typedef struct tagFEFileInfoParam
{
	s8   *m_pszFileName;
	u32	  m_dwRepeatNum;	//�ظ����ŵĴ�����DEFAULT_FE_REPEAT_NUM , ѭ���ز�
    u8    m_byMediaType;	//����֡��ý�����ͣ�DEFAULT_FE_MEDIA_TYPE ���ļ�����
	u8    m_byFrameRate;	//��Ƶ֡�ķ���֡�ʣ�DEFAULT_FE_FRAME_RATE ���ļ�����
	u8    m_byAudioMode;	//��Ƶ֡��ģʽ��DEFAULT_FE_AUDIO_MODE ���ļ�����
}TFEFileInfoParam;

//�ļ��������� ���緢�Ͳ��� // - �ɿ��ڲ����ʵ�ʵ����緢�ͣ�
typedef struct tagFENetSndParam
{
	u8            m_byNum;		//ʵ�ʵ�ַ����
	TFENetSession m_tLocalNet;	//���ص�ַ��
	TFENetSession m_tRemoteNet[MAX_FESND_DEST_NUM];//Զ�˵�ַ��
}TFENetSndParam;


//Frame Rcv CallBack Function
typedef void ( *PFEFrameCallBack )(PFEFRAMEHDR pFrmHdr, u32 dwContext);

//Notify Info CallBack Function
typedef void ( *PFENotifyCallBack )(PTFEStatusParam ptFEStatusParam, u32 dwContext);



//�ļ��������ļ��� ��Ϣ�ص����� // - (�����ļ�����״̬�Ļص��Լ���ȡ��������֡�Ļص�)
typedef struct tagFEFileCBParam
{
	u32	              m_dwContext;
	PFEFrameCallBack  m_fpFrameCBFunc;  // - �ɿ��ȡ�ļ�����֡���ص�����㴦��
    PFENotifyCallBack m_fpNotifyCBFunc; // - �ɿ��ȡ�ļ�����״̬���ص�����㴦��
}TFECBParam;

//�ļ��������ļ���������Ϣ
typedef struct tagFileHeaderInfo  
{
	u8   m_byFileType;		  //�ļ����ͣ�0 - ��Ƶ�� 1 - ��Ƶ��
    u8   m_byMediaType;	      //ý������
	u8   m_byRatio;		      //����֡��(ms)
	u32  m_dwFrameNum;		  //������֡��
	u16  m_wVideoWidth;       //��Ƶ֡��
	u16  m_wVideoHeight;      //��Ƶ֡��
	u8   m_byAudioMode;       //��Ƶģʽ
}TFileHeaderInfo;


/*=============================================================================
������		 feInit
����		��ʼ���ļ������,����֮һ�� �ⲿʹ��
�㷨ʵ��	������ѡ�
�������˵����
����ֵ˵���� �ɹ�����FE_OK,  ʧ�ܷ��ش�����
=============================================================================*/
u16 feInit();


/*=============================================================================
������		 feRelease
����		�����ļ������,�������ò�������,ֱ���ͷſ⣬����֮һ�� �ⲿʹ��
�㷨ʵ��	������ѡ�
�������˵������
����ֵ˵���� �ɹ�����FE_OK,  ʧ�ܷ��ش�����
=============================================================================*/
u16 feRelease();



//----------------------------------------------------------------------

class CFEPlayer;
class CFileEncoder
{
public:
    CFileEncoder();
    ~CFileEncoder();

public:

	//���ļ���������������ָ������������ļ���ý�����ͣ�ȷ���ļ�����֡�Ķ�ȡƵ��
	u16 OpenEncoder(TFEFileInfoParam tFEFileInfoParam);
	//�ر��ļ�������
	u16 CloseEncoder();

	//��ȡ�ļ���������ý��������Ϣ
	u16 GetFileInfo(TFileHeaderInfo &tFileInfo);

	//���� ��ȡ��������֡�����֪ͨ����ʽ�����ַ�ʽ��ͬʱ��Ч
	//1.���ɿ��ڲ����ʵ�ʵ����緢�ͣ�����ָ��ΪNULL,���ͷ�ԭ�е��׽���,������
	//2.���ɿ��ȡ�ļ���Ϣ֡���ص�����㴦������ָ��ΪNULL,���ص�
	u16 SetFrameDealParam(TFENetSndParam	*ptFENetSndParam, TFECBParam *ptFECBParam);

	//��ʼ�ļ�����
	u16 StartEncode();
	//ֹͣ�ļ�����
	u16 StopEncode();

	//��ͣ�ļ�����
	u16 PauseEncode();
	//�����ļ�����
	u16 ContinueEncode();
	
private:
	CFEPlayer *m_pcFEPlayer;	
	void*      m_hSynSem;   //���ڶ���ĵ��̲߳�����ͬ����
};

//----------------------------------------------------------------------


#endif /////_FILEENCODERLIB_0601_H_
