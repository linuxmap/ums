/*****************************************************************************
ģ����      : KdvMediaNet
�ļ���      : KdvMediaNet.h
����ļ�    : KdvMediaNet.cpp
�ļ�ʵ�ֹ���: KdvMediaSnd KdvMediaRcv�ඨ��
����        : κ�α� ������
�汾        : V2.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2003/06/03  2.0         κ�α�      Create
2003/06/03  2.0         κ�α�      Add RTP Option
******************************************************************************/

#ifndef _KDVMEDIANET_0603_H_
#define _KDVMEDIANET_0603_H_

// #ifndef _VXWORKS_
// #include "fcnet.h"
// #endif


//ģ��汾��Ϣ�ͱ���ʱ�� �� �����Ŀ�İ汾�ͱ���ʱ��
API void kdvmedianetver();
API void KdvGetMedianetVer(char** ppVerionString);

//ģ�������Ϣ �� �����Ŀ�İ�����Ϣ
API void kdvmedianethelp();


#define  MEDIANET_NO_ERROR                  (u16)0//�ɹ�����ֵ  
#define  ERROR_MEDIA_NET_BASE               (u16)16000
#define  ERROR_SND_PARAM                    (ERROR_MEDIA_NET_BASE+1)//���÷���ģ��������� 
#define  ERROR_SND_NOCREATE	                (ERROR_MEDIA_NET_BASE+2)//����ģ��û�д���
#define  ERROR_SND_MEMORY	                (ERROR_MEDIA_NET_BASE+3)//����ģ���ڴ��������
#define  ERROR_SND_CREATE_SOCK	            (ERROR_MEDIA_NET_BASE+4)//����ģ�鴴��socket
#define  ERROR_RTP_SSRC                     (ERROR_MEDIA_NET_BASE+5)//RTPͬ��Դ����.
#define  ERROR_LOOPBUF_CREATE               (ERROR_MEDIA_NET_BASE+6)//��״���崴������  
#define  ERROR_RTP_NO_INIT                  (ERROR_MEDIA_NET_BASE+7)//RTP����Щ����û����
#define  ERROR_RTCP_NO_INIT                 (ERROR_MEDIA_NET_BASE+8)//RTP����Щ����û����
#define  ERROR_RTCP_SET_TIMER               (ERROR_MEDIA_NET_BASE+9)//RTCP���ö�ʱ������
#define  ERROR_RTP_SSRC_COLLISION           (ERROR_MEDIA_NET_BASE+10)//RTP ͬ��Դ����
#define  ERROR_SOCK_INIT                    (ERROR_MEDIA_NET_BASE+11)//socket û�г�ʼ��
#define  ERROR_H261_PACK_NUM                (ERROR_MEDIA_NET_BASE+12)//H261�İ���������
#define  ERROR_PACK_TOO_LEN                 (ERROR_MEDIA_NET_BASE+13)//G.711�����ٰ�̫��
#define  ERROR_H263_PACK_NUM                (ERROR_MEDIA_NET_BASE+14)//H263�İ���������
#define  ERROR_H263_PACK_TOOMUCH            (ERROR_MEDIA_NET_BASE+15)//H263�����ݰ�̫��

#define  ERROR_SND_INVALID_SOCK	            (ERROR_MEDIA_NET_BASE+16)//����ģ����Чsocket
#define  ERROR_SND_SEND_UDP	                (ERROR_MEDIA_NET_BASE+17)//����ģ�����ݰ�Ͷ��ʧ�ܣ�Ŀ����ܲ��ɴ
#define  ERROR_SND_FRAME                     (ERROR_MEDIA_NET_BASE+18)//����ģ��֡�������

#define  ERROR_NET_RCV_PARAM                (ERROR_MEDIA_NET_BASE+100)//���ý���ģ���������
#define  ERROR_NET_RCV_NOCREATE             (ERROR_MEDIA_NET_BASE+101)//����ģ��û�д���
#define  ERROR_NET_RCV_MEMORY               (ERROR_MEDIA_NET_BASE+102)//����ģ���ڴ��������
#define  ERROR_RCV_RTP_CREATE               (ERROR_MEDIA_NET_BASE+103)//����ģ��RTP����ʧ��
#define  ERROR_RCV_RTP_CALLBACK             (ERROR_MEDIA_NET_BASE+104)//����ģ������RTP�ص�����ʧ��
#define  ERROR_RCV_RTP_SETREMOTEADDR        (ERROR_MEDIA_NET_BASE+105)//����ģ������RTPԶ�˵�ַʧ��
#define  ERROR_CREATE_LOOP_BUF              (ERROR_MEDIA_NET_BASE+106)//������״����ʧ��
#define  ERROR_RCV_NO_CREATE                (ERROR_MEDIA_NET_BASE+107)//����ģ����ն���û�д���

#define  ERROR_WSA_STARTUP                  (ERROR_MEDIA_NET_BASE+200)//wsastartup error
#define  ERROR_CREATE_SEMAPORE              (ERROR_MEDIA_NET_BASE+201)// create semapore error
#define  ERROR_SOCKET_CALL                  (ERROR_MEDIA_NET_BASE+202)//����socket() ��������
#define  ERROR_BIND_SOCKET                  (ERROR_MEDIA_NET_BASE+203)//socket �󶨳���
#define  ERROR_CREATE_THREAD                (ERROR_MEDIA_NET_BASE+204)//�����̳߳��� 

#define  ERROR_LOOPBUF_FULL                 (ERROR_MEDIA_NET_BASE+205)//ѭ��������
#define  ERROR_NULL_POINT                 (ERROR_MEDIA_NET_BASE+206)//��ָ��

#define  ERROR_SET_DECRYPTKEY               (ERROR_MEDIA_NET_BASE+210)//���ý���keyʧ��
#define  ERROR_DECRYPT_FRAME                (ERROR_MEDIA_NET_BASE+212)//����һ֡ʧ��
#define  ERROR_SET_ENCRYPTKEY               (ERROR_MEDIA_NET_BASE+213)//���ü���keyʧ��
#define  ERROR_ENCRYPT_FRAME                (ERROR_MEDIA_NET_BASE+215)//����һ֡ʧ��
#define  ERROR_SET_USERDATA                 (ERROR_MEDIA_NET_BASE+216)//����һ֡ʧ��
#define  ERROR_SENDER_FEC_CRC	                 (ERROR_MEDIA_NET_BASE+217)//����fec�������
#define  ERROR_RECEIVER_FEC_CRC	                 (ERROR_MEDIA_NET_BASE+218)//����fec�������
#define  ERROR_RECEIVER_FEC_MODE_INVALID         (ERROR_MEDIA_NET_BASE+219)//����fecģʽ����
#define  ERROR_SENDER_FEC_INORDER         (ERROR_MEDIA_NET_BASE+220)//����fec����
#define  ERROR_SENDER_FEC_INVALID_PARAM         (ERROR_MEDIA_NET_BASE+221)//����fec�������

#define  ERROR_NET_BIND_ADDR_SOCKET					(ERROR_MEDIA_NET_BASE + 222) //�����������IP�󶨴���
#define  ERROR_NET_BIND_PORT_SOCKET					(ERROR_MEDIA_NET_BASE + 223) //������������˿ڰ󶨴���
#define  ERROR_NET_OTHER_BIND_ERROR					(ERROR_MEDIA_NET_BASE + 224) //�������������󶨴���

#define  ERROR_NET_CREATE_ERROR_SOCKET			(ERROR_MEDIA_NET_BASE + 225) //�����������ʱ��������

// define the byte order type [20120816]
#define  BYTE_ORDER_UNKNOWN   (u8)0
#define  BYTE_ORDER_BIG       (u8)1
#define  BYTE_ORDER_LITTLE    (u8)2


#define MIN_PRE_BUF_SIZE                    (s32)28// G.711���ټ�һ�ֽ�

#define MAX_H261_HEADER_LEN      (s32)388//
#define MAX_H263_HEADER_LEN      (s32)3076//
#define MAX_H263PLUS_HEADER_LEN  (s32)3076//

#ifndef DES_ENCRYPT_MODE
#define DES_ENCRYPT_MODE         (u8)0      //DES����ģʽ
#define AES_ENCRYPT_MODE         (u8)1      //AES����ģʽ
#define QT_ENCRYPT_MODE          (u8)2      //���Ӽ���ģʽ
#define ENCRYPT_KEY_SIZE         (u8)32     //��Կ���� ȡ���еĽϴ�ֵ
#define DES_ENCRYPT_KEY_SIZE     (u8)8      //DES��Կ����
#define AES_ENCRYPT_KEY_SIZE_MODE_A (u8)16  //AES Mode-A ��Կ����
#define AES_ENCRYPT_KEY_SIZE_MODE_B (u8)24  //AES Mode-B ��Կ����
#define AES_ENCRYPT_KEY_SIZE_MODE_C (u8)32  //AES Mode-C ��Կ����
#endif

//fec raid5�㷨
#define FEC_MODE_RAID5	0
//fec raid6�㷨
#define FEC_MODE_RAID6	1	
//fec raid5 interlace
#define FEC_MODE_RAID5_INTERLEAVE	2
//fec raid6 interlace
#define FEC_MODE_RAID6_INTERLEAVE	3

//Frame Header Structure
typedef struct tagFrameHdr
{
    u8     m_byMediaType; //ý������
    u8    *m_pData;       //���ݻ���
    u32    m_dwPreBufSize;//m_pData����ǰԤ���˶��ٿռ䣬���ڼ�
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
                   BOOL32    m_bHighProfile; // H264 HP��ʶ - 2012/03/01
              }m_tVideoParam;
        u8    m_byAudioMode;//��Ƶģʽ
    };
	
}FRAMEHDR,*PFRAMEHDR;



#ifndef  MAX_NETSND_DEST_NUM
#define  MAX_NETSND_DEST_NUM   5
#endif

#ifndef TNETSTRUCT//��ֹ��ַ�ṹ�ض���
#define TNETSTRUCT

#define MAX_USERDATA_LEN    16

/*�������*/
typedef struct tagNetSession
{
    tagNetSession(){m_dwRTPAddr=0; m_wRTPPort=0; m_dwRTCPAddr=0; m_wRTCPPort=0; \
                    m_dwRtpUserDataLen = 0; m_dwRtcpUserDataLen = 0;}
    
	u32   m_dwRTPAddr;  //RTP��ַ(������)
	u16   m_wRTPPort;   //RTP�˿�(������)
	u32   m_dwRTCPAddr; //RTCP��ַ(������)
	u16   m_wRTCPPort;  //RTCP�˿�(������)
    u32   m_dwRtpUserDataLen;   //Rtp�û����ݳ���,�����ڴ��������,��Ҫ��ÿ��udpͷǰ��ӹ̶�ͷ���ݵ����
    u8    m_abyRtpUserData[MAX_USERDATA_LEN]; //�û�����ָ��
    u32   m_dwRtcpUserDataLen;   //Rtcp�û����ݳ���,�����ڴ��������,��Ҫ��ÿ��udpͷǰ��ӹ̶�ͷ���ݵ����
    u8    m_abyRtcpUserData[MAX_USERDATA_LEN]; //�û�����ָ��
}TNetSession;

/*�����������*/
/*��������pxy����, ���ص�ַ�е�m_wUserLen��ʾ����ʱ��Ҫȥ����ͷ����*/
typedef struct tagLocalNetParam
{
	TNetSession m_tLocalNet;
	u32         m_dwRtcpBackAddr;//RTCP�ط���ַ(������)
	u16         m_wRtcpBackPort; //RTCP�ط��˿ڣ�������
    //u32         m_dwRtcpBackUserDataLen;   //RtcpBack�û����ݳ���
    //u8          m_abyRtcpBackUserData[MAX_USERDATA_LEN]; //�û�����ָ��
}TLocalNetParam;

/*���緢�Ͳ���*/
typedef struct tagNetSndParam
{
	u8          m_byNum;	//ʵ�ʵ�ַ����
	TNetSession m_tLocalNet;//���ص�ַ��
	TNetSession m_tRemoteNet[MAX_NETSND_DEST_NUM];//Զ�˵�ַ��
}TNetSndParam;

#endif //end TNETSTRUCT

typedef BOOL32 (*ChangeRate)(u32 dwContext  , u32 dwBand);

typedef struct tagFecParam
{
	BOOL32		m_bUseFec;
	BOOL32		m_bIntraFrame;
	u8			m_nFecMode;
	s32			m_nFecPacklen;
	s32			m_nFecDataPackNum;
	s32			m_nFecCrcPackNum;
}TFecParam;

/*����ģ��״̬��Ϣ*/
typedef struct tagKdvSndStatus
{
	u8           m_byMediaType;   //ý������
	u32          m_dwMaxFrameSize;//����֡��С
	u32  	     m_dwNetBand;     //���ʹ���
	u32          m_dwFrameID;     //����֡��ʶ
	u8           m_byFrameRate;   //����Ƶ��
	TNetSndParam m_tSendAddr;     //���͵�ַ
	TFecParam	 m_tFecParam;
	BOOL32				m_bReverseG7221c;
}TKdvSndStatus;

/*����ģ��ͳ����Ϣ*/
typedef struct tagKdvSndStatistics
{
	u32	m_dwPackSendNum; //�ѷ��͵İ���
	u32	m_dwFrameNum;	 //�ѷ��͵�֡��
	u32	m_dwFrameLoseNum;//���ڻ�������ԭ����ɵķ��͵Ķ�֡��
}TKdvSndStatistics;

/*����scoket��Ϣ*/
typedef struct tagKdvSndSocketInfo
{
    BOOL32 m_bUseRawSocket;
    u32    m_dwSrcIP;
    u32    m_wPort;
}TKdvSndSocketInfo;

/*����ģ��״̬��Ϣ*/
typedef struct tagKdvRcvStatus
{
	BOOL32	       m_bRcvStart;  //�Ƿ�ʼ����
	u32            m_dwFrameID;  //����֡ID
	TLocalNetParam m_tRcvAddr;   //���յ��ص�ַ
	u32            m_dwFecFrameId;
	BOOL32         m_bReverseG7221c;
	BOOL32         m_bH264DependMark; //H264��֡ʱ�Ƿ�������MARK��־λ
 }TKdvRcvStatus;

/*������ͳ����Ϣ*/
typedef struct tagKdvRcvStatistics
{
	u32    m_dwPackNum;       //�ѽ��յİ���
	u32    m_dwPackLose;      //�G����(Ϊ������û���յ������µĶ�����)
	u32    m_dwPackIndexError;//��������
	u32    m_dwFrameNum;      //�ѽ��յ�֡��
	u32		m_dwPhysicalPackLose;//�����Ķ�����
	//	u32    m_dwFrameLoseNum;  //��������Դ�л���ն��е�ԭ����ɵĽ��յĶ�֡��

	u32 m_dwFecPackNum;//���յ���fec����,  δ����
	u32 m_dwFecPackLose;//fec�����������������ɻָ��ĺͿɻָ���
	u32 m_dwFecRealFrameNum;//fec��֡���������յ���fec������
	u32 m_dwFecNeedRecovery;
	u32 m_dwFecRecoSucc;
	u32 m_dwFecRecoFail;
	u32 m_dwFecGroupFail;
}TKdvRcvStatistics;

/*=============================================================================
	������		��KdvSocketStartUp
	����		��kdv socket ��ʼ��,��ʹ���շ���֮ǰ����ô˺�����
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�����
	�������˵������
	              

	����ֵ˵�����μ������붨��
=============================================================================*/
u16 KdvSocketStartup();

/*=============================================================================
	������		��KdvSocketCleanUp
	����		����KdvSocketStartup���Ӧ���������
	�㷨ʵ��	������ѡ�
	����ȫ�ֱ�������
	�������˵������
	              

	����ֵ˵������
=============================================================================*/
u16 KdvSocketCleanup();


/*=============================================================================
    ������      ��setCheckPacketTime
    ����        ����������Ƶ�Ƿ������ʱ���
    �������˵��  �� bVideoUsed  ��Ƶ�Ƿ���
                     bAudioUsed  ��Ƶ�Ƿ���
    ����ֵ˵��    �� TRUE �ɹ���FALSEʧ��
=============================================================================*/
BOOL32 setCheckPacketTime (BOOL32 bVideoUsed, BOOL32 bAudioUsed);
/*============================================================================
API BOOL32 KdvSetUdpMaxLen(u32 dwMaxUdpPackLen):����udp���͵�������
dwMaxUdpPackLen:������,��ֵ����С�ڵ���1450,���ڵ���1000
��Ϊ�ϰ汾��ÿ֡���96��������,����ÿ֡128*1024������,�����128k��֡�Ļ�,
����Сudp���������1370��
============================================================================*/
API BOOL32 KdvSetUdpMaxLen(s32 dwMaxUdpPackLen);

API void setUseRawSend(BOOL32 bUsed);

/*============================================================================
����ƽ�����͵�API
============================================================================*/
API s32 SetSendUseTimer(s32 nMode);


/*=============================================================================
	������		��SetH264FrameHPFlag
	����		������H264SPS��Ϣ������֡ͷ�ṹ��HighProfile��ʶ�ֶΡ�
	�������˵��  �� PFRAMEHDR pFrmHdr�� ָ��H264֡ͷ�ṹ��ָ��
	����ֵ˵��    �� MEDIANET_NO_ERRORΪ�ɹ�������Ϊʧ�ܣ���ο������붨��
=============================================================================*/
API u16  SetH264FrameHPFlag( PFRAMEHDR pFrmHdr );

API s32 SetForceLocalPT(s32 nForceLocalPT);

typedef struct tagRtpPack
{
    u8	 m_byMark;			//�Ƿ�֡�߽�1��ʾ���һ��
    u8   m_byExtence;		//�Ƿ�����չ��Ϣ
    u8   m_byPadNum;		//���ܵ�padding����
    u8   m_byPayload;		//�غ�
    u32  m_dwSSRC;			//ͬ��Դ
    u16  m_wSequence;		//���к�
    u32  m_dwTimeStamp;		//ʱ���
    u8  *m_pExData;         //��չ����
    s32  m_nExSize;			//��չ��С��sizeof(u32)�ı�����
    u8  *m_pRealData;		//ý������ 
    s32  m_nRealSize;		//���ݴ�С 
    s32  m_nPreBufSize;		//m_pRealDataǰԤ����Ŀռ�;
}TRtpPack;

typedef struct tagRSParam
{
    u16  m_wFirstTimeSpan;   //��һ���ش�����
    u16  m_wSecondTimeSpan;  //�ڶ����ش�����
    u16  m_wThirdTimeSpan;   //�������ش�����
    u16  m_wRejectTimeSpan;  //���ڶ�����ʱ����
} TRSParam;

//���Ͷ˸߼����ò���
typedef struct tagAdvancedSndInfo
{
    s32      m_nMaxSendNum;      // ���ݴ�����������ʹ���;	
    BOOL32   m_bRepeatSend;      // ���� (mp4) �Ƿ��ط�
    u16      m_wBufTimeSpan;
    BOOL32   m_bEncryption;      // ���� (mp4/H.26X/Audio) �Ƿ����ü���
    u8       m_byEncryptMode;    // ����ģʽ Aes ���� Des
    u16      m_wKeySize;         // ������Կ����
    s8       m_szKeyBuf[ENCRYPT_KEY_SIZE+1];   // ������Կ����
    u8       m_byLocalActivePT;  // ��̬�غ�PTֵ
    s32      m_nResendTimes;  //�ط�����
    s32      m_nResendSpan;   //�ط����
	BOOL32	 m_bHdFlag;//�Ƿ����ڸ���
	BOOL32	m_bFregmentSlice;//�Ƿ���Ƭ
	BOOL32  m_bSmoothSnd;//�Ƿ�������ƽ������
	
	u32		m_nRLBUnitNum;      //�ش��������
	u32		m_dwPrintFlag;
	u32		m_dwSSRC;
} TAdvancedSndInfo;

//���ն˸߼����ò���
typedef struct tagAdvancedRcvInfo
{
    BOOL32    m_bConfuedAdjust;  // ���� (mp3) �Ƿ����������	
    BOOL32    m_bRepeatSend;     // ���� (mp4) �Ƿ��ط�
    TRSParam  m_tRSParam;
    BOOL32    m_bDecryption;     // ���� (mp4/H.26X/Audio) �Ƿ����ý���
    u8        m_byDecryptMode;   // ����ģʽ Aes ���� Des
    u16       m_wKeySize;        // ������Կ����
    s8        m_szKeyBuf[ENCRYPT_KEY_SIZE+1];   // ������Կ����
    u8        m_byRmtActivePT;   // ���յ��Ķ�̬�غɵ�Playloadֵ
    u8        m_byRealPT;        // �ö�̬�غ�ʵ�ʴ���ĵ�Playload���ͣ�ͬ�ڷ���ʱ��PTԼ��
	u8			m_byLastFrameType;
	BOOL32	 m_bHdFlag;//�Ƿ����ڸ���
	BOOL32   m_bSmoothSend;

	s32		  m_nPacketBuffNum;
	u32		  m_dwBufBlockSize;
	u32		  m_dwBufTotalNum;
	u32			m_dwPrintFlag;
	u32			m_dwSSRC;
} TAdvancedRcvInfo;

//Frame Rcv CallBack Function
typedef   void (*PFRAMEPROC )(PFRAMEHDR pFrmHdr, u32 dwContext);
//RTP PACK Call back
typedef   void (*PRTPCALLBACK)(TRtpPack *pRtpPack, u32 dwContext); 


class CKdvNetSnd;
class CKdvMediaSnd
{
public:
    CKdvMediaSnd();
    ~CKdvMediaSnd();
public:
	//��������ģ��
    u16 Create( u32 dwMaxFrameSize, u32 dwNetBand, 
                u8 ucFrameRate, u8 ucMediaType, u32 dwSSRC = 0);

	//�����Ƿ����ı�־(����h264֡�ṹ�������Ĳ�һ�����ڵ���create����ص����������)
	u16	SetHDFlag( BOOL32 bHdFlag );

    // set timestamp value,after this timestamp increase 
    // base by dwtimestamp, call after function Create
    u16 SetTimestamp(u32 dwtimestamp);
	//�Ƿ���Ƭ,�����ݼ�rtpͷ����(1456+12)ʱ���Ƿ���Ƭ��־��ֻ��h264��Ч
	u16 SetFregmentSlice( BOOL32 bFregmentSlice );
	
	//�������緢�Ͳ���(���еײ��׽��ӵĴ������󶨶˿�,�Լ�����Ŀ���ַ���趨�ȶ���)
    u16 SetNetSndParam( TNetSndParam tNetSndParam , BOOL32 bReuseAddr = FALSE);

	//�Ƴ����緢�ͱ��ص�ַ����(���еײ��׽��ӵ�ɾ�����ͷŶ˿ڵȶ���)
    u16 RemoveNetSndLocalParam();

	//���� ��̬�غɵ� Playloadֵ, byLocalActivePT����Ϊ0-��ʾ��� ���˶�̬�غɱ��
    u16 SetActivePT( u8 byLocalActivePT );

	//���ü���key�ִ������������Ķ�̬�غ�PTֵ, pszKeyBuf����ΪNULL-��ʾ������
    u16 SetEncryptKey( s8 *pszKeyBuf, u16 wKeySize, u8 byEncryptMode=DES_ENCRYPT_MODE );	

	//����֡ID
    u16 ResetFrameId();
	//����ͬ��ԴSSRC
    u16 ResetSSRC(u32 dwSSRC = 0);

	//���÷��Ͷ��ش�����Ŀ���,�رպ󣬽������Ѿ����͵����ݰ����л���
    u16 ResetRSFlag(u16 wBufTimeSpan, BOOL32 bRepeatSnd = FALSE);

	//���÷���ѡ��
    u16 SetSndInfo(u32 dwNetBand, u8 ucFrameRate);

	//���÷���ѡ��
	u16 ResetSndInfo(void);

	//�������ݰ�
    u16 Send ( PFRAMEHDR pFrmHdr, BOOL32 bAvalid=TRUE );
	//����ת��H261��H263���ݰ�
    u16 Send (TRtpPack *pRtpPack, BOOL32 bTrans = TRUE, BOOL32 bAvalid = TRUE);
 
	//�õ�״̬
    u16 GetStatus ( TKdvSndStatus &tKdvSndStatus );
	//�õ�ͳ��
    u16 GetStatistics ( TKdvSndStatistics &tKdvSndStatistics );	
	//�õ����Ͷ˸߼����ò������ش��ȣ�
    u16 GetAdvancedSndInfo(TAdvancedSndInfo &tAdvancedSndInfo);
	
	//�����Բ���
    u16 SelfTestSend (int nFrameLen, int nSndNum, int nSpan);

	//rtcp��ʱrtcp���ϱ�, �ڲ�ʹ�ã��ⲿ�������
    u16 DealRtcpTimer();

    //����Դ��ַ������IPαװ��ֻ����ʹ��raw socket��ʱ�����Ч
    u16 SetSrcAddr(TNetSession tSrcNet);

    //�õ�socket��ص���Ϣ
    u16 GetSndSocketInfo(TKdvSndSocketInfo &tRtpSockInfo, TKdvSndSocketInfo &tRtcpSockInfo);

    u16 GetNetSndParam(TNetSndParam* ptNetSndParam);

    //������Ƶ�ط�nSendTimes���ط�������nSendSpan��ÿ���ط��������Ҫ�ѷ����ش���
    u16 SetAudioResend(s32 nSendTimes, s32 nSendSpan);
	
	//����˳�򣬿���ֻ����SetFecEnable����Ĭ��raid5, 5+1, �а�988�ֽ�
	//SetFecMode,SetFecIntraFrame,SetFecXYӦ����SetFecEnable֮ǰ����,
	//�����SetFecEnable֮����ã����������������κ�һ�����ᵼ��ǰ��ssrc�����ã�����Ƕ�֡����
	//SetFecEnable�����Ĳ�����true��false��ÿ���л����ᵼ�¶�֡����
	//SetFecPackLen����ʱ����	
	//ʹ��fec ����
	u16 SetFecEnable( BOOL32 bEnableFec );
	//����fec���а�����
	u16 SetFecPackLen( u16 wPackLen );
	//�Ƿ�֡��fec
	u16 SetFecIntraFrame( BOOL32 bIntraFrame );
	//����fec�㷨 FEC_MODE_RAID5
	u16 SetFecMode( u8 byAlgorithm );
	//����fec��x�����ݰ� + y�������
	u16 SetFecXY(s32 nDataPackNum, s32 nCrcPackNum);

	u16 SetFecParam(const TFecParam& tPara);

	//���÷�תg7221c
	u16 SetReverseG7221c( BOOL32 bReverse );

	// �����ֽ��� [20120816]
	u16 SetCurByteOrderH261( u8 byOrder );

	//��ӡ��Ϣ
	void SetPrintFlag(u32 dwFlag);
	void AddPrintFlag(u32 dwFlag);
	void SaveSendData(u32 dwFrameNum);
	u16	RsFecSndStart(u32 dwContext = 0 , ChangeRate pFunc = NULL, u8 byDataNum = 20);
	u16 RsFecSndStop();

	void RsReSetPacketNum(int nNewPacketNum);
public:

	u16 SendRtcpStatisReq(u8* pBuf, u16 wLen, u32 dwTargetIp, u16 wTargetPort);	

private:
    CKdvNetSnd *m_pcNetSnd;
    void*       m_hSndSynSem;  //���ڶ���ĵ��̲߳�����ͬ����
	TNetSndParam	m_tNetSndParam;
};

class CKdvNetRcv;
class CKdvMediaRcv
{
public:
    CKdvMediaRcv();
    ~CKdvMediaRcv();
public:
	//��������ģ��
    u16 Create( u32 dwMaxFrameSize, 
                PFRAMEPROC pFrameCallBackProc, 
                u32 dwContext,
                u32 dwSSRC = 0);
    u16 Create( u32 dwMaxFrameSize,
                PRTPCALLBACK PRtpCallBackProc,
                u32 dwContext,
                u32 dwSSRC = 0);

	//�����Ƿ����ı�־(����h264�ص�֡�ĸ�ʽ��������ͬ������create����ص����������)	
	/*
	 *	֡�ṹ�����512��nal��ÿ2�ֽڴ���nal�ĳ��ȣ���2�ֽ�Ϊ�����򣬵�����Ϊ0ʱ����nal����
	 *	��ʵ�ʵ�����֮ǰԤ��2*512=1024�ֽ�
	 *	---------------------------------------------------------------------------
	 *	| Len0 | Len1 | Len2 | ... | Len511 | NALU0 | NALU1 | NALU2 | ... | NALUx |
	 *	---------------------------------------------------------------------------  
	 *	framehdr�ṹ��m_pDataָ��Len0����m_dwDataSize����ǰ���1024�ֽ�
	 */
	u16	SetHDFlag( BOOL32 bHdFlag );
	
	//���ý��յ�ַ����(���еײ��׽��ӵĴ������󶨶˿ڵȶ���)
    u16 SetNetRcvLocalParam ( TLocalNetParam tLocalNetParam , BOOL32 bReuseAddr = FALSE);
	
	//�Ƴ����յ�ַ����(���еײ��׽��ӵ�ɾ�����ͷŶ˿ڵȶ���)
    u16 RemoveNetRcvLocalParam();

	//���� ��̬�غɵ� Playloadֵ, byRmtActivePT����Ϊ0-��ʾ��� ���˶�̬�غɱ��
    u16 SetActivePT( u8 byRmtActivePT, u8 byRealPT );

	//���ý��ն˶���mpeg4����H.264���õ��ش�����Ŀ���,�رպ󣬽��������ش�����
    u16 ResetRSFlag(TRSParam tRSParam, BOOL32 bRepeatSnd = FALSE);

	//���ý��ն˶��� (mp3) �Ƿ���������������Ŀ���, �رպ󣬽�������
    u16 ResetCAFlag(BOOL32 bConfuedAdjust = TRUE);
	
	//����RTP�ص��ӿ���Ϣ
    u16 ResetRtpCalllback(PRTPCALLBACK pRtpCallBackProc, u32 dwContext);

	//���ý��ս���key�ִ�, pszKeyBuf����ΪNULL-��ʾ������
    u16 SetDecryptKey(s8 *pszKeyBuf, u16 wKeySize, u8 byDecryptMode=DES_ENCRYPT_MODE);
		
	//��ʼ����
    u16 StartRcv();
	//ֹͣ����
    u16 StopRcv();
	//�õ�״̬
    u16 GetStatus ( TKdvRcvStatus &tKdvRcvStatus );
	//�õ�ͳ��
    u16 GetStatistics ( TKdvRcvStatistics &tKdvRcvStatistics );
	//�õ����ն˸߼����ò������ش����������ŵȣ�
    u16 GetAdvancedRcvInfo(TAdvancedRcvInfo &tAdvancedRcvInfo);
	//�õ���ǰ���յ������֡�ߴ�
    u16 GetMaxFrameSize(u32 &dwMaxFrameSize);
	//�õ���ǰ���յ���ý������
    u16 GetLocalMediaType(u8 &byMediaType);
	
	//rtcp��ʱrtcp���ϱ�, �ڲ�ʹ�ã��ⲿ�������
    u16 DealRtcpTimer();

    u16 RelayRtpStart(u32 dwIP, u16 wPort);
    u16 RelayRtpStop();

	//�ش���natʱ�����ñ�����rtp���ն˿ڶ�Ӧ�Ĺ�����ַ,Ŀ��Ϊʹ�ش�ʱ���ù㲥
	//u32 dwRtpPublicIp:���ؽ���rtp��Ӧ�Ĺ���ip
	//u16 wRtpPublicPort:���ؽ���rtp��Ӧ�Ĺ���port
	u16 SetRtpPublicAddr(u32 dwRtpPublicIp, u16 wRtpPublicPort);

	//���÷�תg7221c
	u16 SetReverseG7221c( BOOL32 bReverse );
	//��¼֡��Ϣ��������
	u16 SaveSendData(u32 dwFrameNum);

    //����H264��֡ʱ�Ƿ�������MARK��־λ, FALSE��ʾ������MARK, TRUE��ʾ����, Ĭ��ֵΪTRUE.
    u16 SetRcvH264DependInMark( BOOL32 bH264DependMark );


	//��ӡ��Ϣ
	void SetPrintFlag(u32 dwFlag);
	void AddPrintFlag(u32 dwFlag);
	u16	RsFecRcvStart();
	u16 RsFecRcvStop();
	void RsSetRepeatAndFecOn(BOOL32 bRepeat , BOOL32 bFecOn);
private:
    CKdvNetRcv *m_pcNetRcv;
    void*       m_hRcvSynSem;  //���ڶ���ĵ��̲߳�����ͬ����
};


//����ý��TOSֵ nType����0:ȫ�� 1:��Ƶ 2:��Ƶ 3: ����
API s32 kdvSetMediaTOS(s32 nTOS, s32 nType);
API s32 kdvGetMediaTOS(s32 nType);
API BOOL32 Rs_Fec_Test_1();
// 
// #ifndef _VXWORKS_
// 
// /*�������*/
// /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// ע��
// �����漰������ip ��Ϊ������
// portΪ������	
// ��������:��λbit/s
// ����ʱ�䵥λ:millisecond
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
// 
// /*===============================
// typedef void (*NETBDNOTICECB)(u32 dwIp, u32 dwBandWidth, u32 dwContext);
// //���ض�̬����֪ͨ�ص�
// u32 dwip: Ŀ��ip����ʶͨ����
// u32 dwBd��ͨ����Ľ������
// u32 dwContext���û�����
// ================================*/
// typedef void (*NETBDNOTICECB)(u32 dwIp, u32 dwBandWidth, u32 dwContext);
// 
// /*===============================
// typedef void(*NETBDDETECTCB)(u32 dwTargetIp, u32 dwBandWidth, u32 dwContext);
// //������֪ͨ�ص�
// u32 dwip: Ŀ��ip����ʶͨ����
// u32 dwBd��ͨ����Ľ������
// u32 dwContext���û�����
// ================================*/
// typedef void(*NETBDDETECTCB)(u32 dwTargetIp, u32 dwBandWidth, u32 dwContext);
// 
// /*==================================
// u16 KdvInitFcNet(u16 wCtrlPort, u16 wStartDataPort, u16 wDataPortNum, u32 dwTotalGrpNum=0 );
// //��ʼ��
// //�����ڴ���mediasnd֮ǰ����
// ������ָ����ʼ�˿ںźͶ˿������ں������ܵļ�ⷢ����ѡȡָ����Χ�ڿ��õĶ˿ڽ��м����������(����)��
// u16 wCtrlPort:�����������port����Ϊtcp����;���������������˿�
// u16 wStartDataPort����������port,��Ϊudp;���������ݽ��ն˿ڿ��÷�Χ��ʼֵ
// u16 wDataPortNum��ͬʱ�����ж����⣬��Ϊ�������õ�����port��;���������ݽ��ն˿ڶ������������0��ʾֻ��
//                 ��ʼֵ���ã�1��ʾ���ö˿ڷ�ΧΪ[start_data_port, start_data_port+1],��������
// u16 wInnerStartPort:ģ���ڲ�ʹ�õĶ˿ڿ��÷�Χ��ʼֵ
// u16 wInnerPortNum:ģ���ڲ�ʹ�ö˿ڶ������������0��ʾֻ����ʼֵ���ã�
// 						1��ʾ���ö˿ڷ�ΧΪ[start_inner_port, start_inner_port+1]����������
// u32 dwTotalGrpNum:ͨ��������=0��ȡĬ��ֵ:INTERFCNET_DEFAULT_CHANNEL_NUM;
// ====================================*/
// u16 KdvInitFcNet(u16 wCtrlPort, u16 wStartDataPort, u16 wDataPortNum, u16 wInnerStartPort, u16 wInnerPortNum, u32 dwTotalGrpNum=0 );
// u16 KdvQuitFcNet();
// 
// /*=================================
// u16 KdvRegChnlGrp(u32 dwChnlGrpIp, NETBDNOTICECB pNetBdNoticeC, u32 dwContext, u32 dwFcTimeInterval=0);
// //��ָ��ʱ������ȥ��ָ���Զ˵�ͨ��������/�����Զ���������
// u32 dwIp��Ŀ��ip
// u32 dwFcTimeInterval������ʱ����,=0��ȡĬ��ֵINTERFCNET_DEFAULT_TIMEOUT_MILLIS;
// �Ժ���ƣ�����ȡֵ��ΧΪ<100, 600000>��Ϊ�Ͼ�ȷ�ظ�������ʵ���շ������
// ��ֵ�������÷�ΧΪ<500, 5000>
// NETBDNOTICECB pNetBdNoticeC������֪ͨ�ص�����
// u32 dwContext���û�����
// ==================================*/
// u16 KdvRegChnlGrp(u32 dwChnlGrpIp, NETBDNOTICECB pNetBdNoticeCb, u32 dwContext, u32 dwFcTimeInterval=0);
// //�رն�ȥ��ָ���Զ˵�ͨ�������������
// u16 KdvUnregChnlGrp(u32 dwChnlGrpIp);
// 
// 
// /*========================================================
// u16 KdvDcbDetect(u32 dwTargetIp, u32 dwInitBandWidth, u32 dwContext, NETBDDETECTCB pNetBdDetectCb);
// //���ӱ��˵�ָ����ַ��ȫ�̿��ô���
// u32 dwTargetIp:Ŀ��ip
// u16 wPort:�Զ˼�������˿�
// u32 dwInitBandWidth:���ʱ��ʼ�������,����Ϊ�����ڼ��ټ�����
// u32 dwContext:��������
// NETBDDETECTCB pNetBdDetectCb:������֪ͨ�ص�
// =========================================================*/
// u16 KdvDcbDetect(u32 dwTargetIp, u16 wPort, u32 dwInitBandWidth, u32 dwContext, NETBDDETECTCB pNetBdDetectCb);
// 
// #endif	//




#ifndef _VXWORKS_
//�˴��ĺ���ȫ��Ϊ�պ�������Ϊ���ն��ܹ�����ͨ����
//�����ʵ����Щ������ʹ��ͷ�ļ�#include "fcnet.h"�ж�Ӧ�ĺ��� 

typedef void (*NETBDNOTICECB)(u32 dwIp, u32 dwBandWidth, u32 dwContext);
typedef void(*NETBDDETECTCB)(u32 dwTargetIp, u32 dwBandWidth, u32 dwContext);

u16 KdvInitFcNet(u16 wCtrlPort, u16 wStartDataPort, u16 wDataPortNum, u16 wInnerStartPort, u16 wInnerPortNum, u32 dwTotalGrpNum=0 );
u16 KdvQuitFcNet();
u16 KdvRegChnlGrp(u32 dwChnlGrpIp, NETBDNOTICECB pNetBdNoticeCb, u32 dwContext, u32 dwFcTimeInterval=0);
u16 KdvUnregChnlGrp(u32 dwChnlGrpIp);
u16 KdvDcbDetect(u32 dwTargetIp, u16 wPort, u32 dwInitBandWidth, u32 dwContext, NETBDDETECTCB pNetBdDetectCb);

#endif	//


#endif	//_KDVMEDIANET_0603_H_



