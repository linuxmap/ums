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
2004/09/25  2.0         ����      ����linux�汾����֧��
2004/10/19  2.0         ����      ���붯̬�غ������Լ����ܽӿ�
2004/10/19  2.0         ����      ��������
2004/10/19  3.0         ����      ����DES����ģʽ֧��
2004/11/30  3.0         ����      ����AES����ģʽ֧��
2004/12/02  2.0         ����      ����֡�ϱ�ʱ��ʹ��m_dwContext�ֶ��ϱ����Ͷ˵� ԴIP��������
2004/12/02  2.0         ����      ȡ���ϱ�:����֡�ϱ�ʱ��ʹ��m_dwContext�ֶ��ϱ����Ͷ˵� ԴIP��������
2004/12/22  2.0         ����      ����֡�ϱ�ʱ��֡��Ϣ�ṹ������һ���ֶ��ϱ� ���Ͷ˵�ԴIP��������
******************************************************************************/


#ifndef _KDVDATANET_0302_H_
#define _KDVDATANET_0302_H_

#include "kdvtype.h"
#include "osp.h"
#include "kdvcommon.h"

#ifdef _ENABLE_QUANTUM_PROJECT_
#include "qtstruct.h"
#endif

//ģ��汾��Ϣ�ͱ���ʱ�� �� �����Ŀ�İ汾�ͱ���ʱ��
PROTO_EXTERN_API void kdvdatanetver();
PROTO_EXTERN_API void kdvdatanetlog(u8 level);
PROTO_EXTERN_API void printrtppacklen();
PROTO_EXTERN_API void kdvdatanetinfo(); //��ӡrecv��send����Ϣ

//ģ�������Ϣ �� �����Ŀ�İ�����Ϣ
PROTO_EXTERN_API void kdvdatanethelp();

#define  MAXWATCHDATASOCKPORT  (u16)10599//max watchsock port
#define  MINWATCHDATASOCKPORT  (u16)10500//min watchsock port

#define  DATA_PINHOLE_INTERVAL		10 //10s ��ʱ����
#define  DATANET_NO_ERROR                   (u16)0//�ɹ�����ֵ  

#define  ERROR_DATA_NET_BASE                (u16)16000
#define  ERROR_SND_PARAM		    (ERROR_DATA_NET_BASE+1)//���÷���ģ��������� 
#define  ERROR_SND_NOCREATE		    (ERROR_DATA_NET_BASE+2)//����ģ��û�д���
#define  ERROR_SND_MEMORY		    (ERROR_DATA_NET_BASE+3)//����ģ���ڴ��������
#define  ERROR_SND_CREATE_SOCK		    (ERROR_DATA_NET_BASE+4)//����ģ�鴴��socket
#define  ERROR_RTP_SSRC                     (ERROR_DATA_NET_BASE+5)//RTPͬ��Դ����.
#define  ERROR_LOOPBUF_CREATE               (ERROR_DATA_NET_BASE+6)//��״���崴������  
#define  ERROR_RTP_NO_INIT                  (ERROR_DATA_NET_BASE+7)//RTP����Щ����û����
#define  ERROR_RTCP_NO_INIT                 (ERROR_DATA_NET_BASE+8)//RTCP����Щ����û����
#define  ERROR_RTCP_SET_TIMER               (ERROR_DATA_NET_BASE+9)//RTCP���ö�ʱ������
#define  ERROR_RTP_SSRC_COLLISION           (ERROR_DATA_NET_BASE+10)//RTP ͬ��Դ����
#define  ERROR_SOCK_INIT                    (ERROR_DATA_NET_BASE+11)//socket û�г�ʼ��
#define  ERROR_H261_PACK_NUM                (ERROR_DATA_NET_BASE+12)//H261�İ���������
#define  ERROR_PACK_TOO_LEN                 (ERROR_DATA_NET_BASE+13)//���ݰ�̫��
#define  ERROR_H263_PACK_NUM                (ERROR_DATA_NET_BASE+14)//H263�İ���������
#define  ERROR_H263_PACK_TOOMUCH            (ERROR_DATA_NET_BASE+15)//H263�����ݰ�̫��

#define  ERROR_NET_RCV_PARAM                (ERROR_DATA_NET_BASE+100)//���ý���ģ���������
#define  ERROR_NET_RCV_NOCREATE             (ERROR_DATA_NET_BASE+101)//����ģ��û�д���
#define  ERROR_NET_RCV_MEMORY               (ERROR_DATA_NET_BASE+102)//����ģ���ڴ��������
#define  ERROR_RCV_RTP_CREATE               (ERROR_DATA_NET_BASE+103)//����ģ��RTP����ʧ��
#define  ERROR_RCV_RTP_CALLBACK             (ERROR_DATA_NET_BASE+104)//����ģ������RTP�ص�����ʧ��
#define  ERROR_RCV_RTP_SETREMOTEADDR        (ERROR_DATA_NET_BASE+105)//����ģ������RTPԶ�˵�ַʧ��
#define  ERROR_CREATE_LOOP_BUF              (ERROR_DATA_NET_BASE+106)//������״����ʧ��
#define  ERROR_RCV_NO_CREATE                (ERROR_DATA_NET_BASE+107)//����ģ����ն���û�д���

#define  ERROR_WSA_STARTUP                  (ERROR_DATA_NET_BASE+200)//wsastartup error
#define  ERROR_CREATE_SEMAPORE              (ERROR_DATA_NET_BASE+201)//create semapore error
#define  ERROR_SOCKET_CALL                  (ERROR_DATA_NET_BASE+202)//����socket() ��������
#define  ERROR_BIND_SOCKET                  (ERROR_DATA_NET_BASE+203)//socket �󶨳���
#define  ERROR_CREATE_THREAD                (ERROR_DATA_NET_BASE+204)//�����̳߳��� 

#define  ERROR_LOOPBUF_FULL                 (ERROR_DATA_NET_BASE+205)//ѭ��������


#define  ERROR_SET_DECRYPTKEY               (ERROR_DATA_NET_BASE+210)//���ý���keyʧ��
#define  ERROR_DECRYPT_FRAME                (ERROR_DATA_NET_BASE+212)//����һ֡ʧ��
#define  ERROR_SET_ENCRYPTKEY               (ERROR_DATA_NET_BASE+213)//���ü���keyʧ��
#define  ERROR_ENCRYPT_FRAME                (ERROR_DATA_NET_BASE+215)//����һ֡ʧ��


#define ERROR_SND_FRAME          (s32)-1;


#ifndef DES_ENCRYPT_MODE
#define DES_ENCRYPT_MODE         (u8)0      //DES����ģʽ
#define AES_ENCRYPT_MODE         (u8)1      //AES����ģʽ
#define QT_ENCRYPT_MODE          (u8)2      //QT����ģʽ
#define ENCRYPT_KEY_SIZE         (u8)32     //��Կ���� ȡ���еĽϴ�ֵ
#define DES_ENCRYPT_KEY_SIZE     (u8)8      //DES��Կ����
#define AES_ENCRYPT_KEY_SIZE_MODE_A (u8)16  //AES Mode-A ��Կ����
#define AES_ENCRYPT_KEY_SIZE_MODE_B (u8)24  //AES Mode-B ��Կ����
#define AES_ENCRYPT_KEY_SIZE_MODE_C (u8)32  //AES Mode-C ��Կ����
#endif

#ifndef  MAX_NETSND_DEST_NUM
	#define  MAX_NETSND_DEST_NUM   5
#endif

/////////////////////////////////////////////////FECC////////////////////////////////////////////////
#define MAX_FECC_LEN 256               //��󳤶�

//H323 Annex Q
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
enum EmFeccAction
{
	emActionInvalid					= 0,  
	emActionStart					= 0x01,  //��ʼ
	emActionContinue				= 0x02,  //����
	emActionStop					= 0x03,  //ֹͣ
	emActionSelectVideoSource		= 0x04,  //ѡ����ƵԴ
	emActionVideoSourceSwitched		= 0x05,  //�л���ƵԴ
	emActionStoreAsPreset			= 0x06,  //�洢Ԥ��λ
	emActionActivatePreset			= 0x07,  //�ָ���Ԥ��λ
	emActionAutoFocus				= 0x11,  //�Զ�����
};

//PTFZ codes, parameters for action Start, continue and stop.
enum EmFeccPTFZRequest
{
	emRequestInvalid			= 0,
	emRequestPanLeft			= 0x80,	//�����ƶ�
	emRequestPanRight			= 0xc0,	//�����ƶ�
	emRequestTiltUp			    = 0x30,	//�����ƶ�
	emRequestTiltDown			= 0x20,	//�����ƶ�
	emRequestFocusIn			= 0x03,	//����
	emRequestFocusOut			= 0x02,	//Զ��
	
	emRequestZoomIn				= 0x0c,	//��Ұ��С
	emRequestZoomOut			= 0x08,	//��Ұ���

	emRequestBrightnessUp		= 0x01,	//���ȼ�(nonstandard)
	emRequestBrightnessDown		= 0x04  //���ȼ�(nonstandard)
};

//Զңģ�鷵��ֵ����
typedef enum
{
	annexQNotInited				= -20,
	annexQBindError				= -15,
	annexQParamError			= -14,
	annexQLockError				= -12,	
	annexQCodingError			= -10,
	annexQSendError				= -9,	
	annexQGeneralError			= -5,
	annexQOk					= 1
}annexQResult;

//for tanderg
enum EmFeccVideoSourceNumber
{
    emVideoSourceDefault               = 0,    //��ǰ��ƵԴ
    emVideoSourceMainCamera            = 1,    //����ƵԴ
    emVideoSourceAuxCamera             = 2,    //������ƵԴ
    emVideoSourceDocCamera             = 3,    //�ļ�չʾ̨
    emVideoSourceAuxDocCamera          = 4,    //�����ļ�չʾ̨������̩��Ϊvcr
    emVideoSourceVideoPlaybackSource   = 5,    //vcr������̩��ΪPC
};

////CME message type
enum EmCMEMsgType
{
	CMEInvalid,				//��Ч
	CMEClientListInfo,		//�ͻ��б���Ϣ֪ͨ
	CMEClientListCommond,	//����ͻ��б�
	CMEExtraCapInfo,		//����������Ϣ֪ͨ
	CMEExtraCapCommond,		//�����������

};

//H323 Annex Q
//CME��Ϣ�Լ�������Ϣ������һ���ṹ����
typedef struct PROTO_API tagFeccStruct
{
	BOOL32 m_bIsCMEMsg;		    

	u8	m_byCMEMsgType;		  //ClientListInfo/Commond,ExtraCapInfo/Commond

	u8 m_byAction;			  //start, continue, stop, video source, preset	
	union
	{
		u8 m_byRequest;		  //for PTFZ operations
		u8 m_bySourceNo;      //for VIDEO SOURCE operations
		u8 m_byPresetNo;      //for PRESET operations
	}arguments;	
	u8 m_byTimeout;			  //for start action only ,unit 50ms, 0��ʾ800ms
public:
	tagFeccStruct()
	{
		m_bIsCMEMsg		= FALSE;
		m_byCMEMsgType	= CMEInvalid;
		m_byAction		= emActionInvalid;
		arguments.m_byRequest = 0;	
		m_byTimeout		= 0;
	}
}TFeccStruct, *PTFeccStruct;


//�˿ڸ���ʱ��Ҫ����streamId��
#define FECC_ENDPOINTID_LEN 32
typedef struct PROTO_API tagFeccStreamIdInfo
{
	s8  aszEndPointId[FECC_ENDPOINTID_LEN];	//�ն˵�id, ��ǰ��֧��e164��
	u32 IdLen;				//�ն�id�ĳ���
	u32 StreamId;			//��id
	BOOL32 bSendChan;		//�Ƿ���Զң����ͨ��

public:
	tagFeccStreamIdInfo()
	{
		memset(aszEndPointId, 0, FECC_ENDPOINTID_LEN);
	}
}TFeccStreamIdInfo;


/*====================================================================
������      : kdvAnnexQInit
����        : Զңģ���ʼ��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: dwMaxFeccChannels - ���FECCͨ����
			  nDataPinhleAppID  - ��app��id,Ĭ��ֵ��APPID_DATANET_PINHOLE	
			  nMinPort			- ����watchdog socket��С�˿ں�
			  nMaxPort			- ����watchdog socket���˿ں�
����ֵ˵��  : annexQOk if succeed, or other if fails
====================================================================*/
PROTO_EXTERN_API s32 kdvAnnexQInit(u32 dwMaxFeccChannels, s32 nDataPinhleAppID=APPID_DATANET_PINHOLE, u16 dwMinPort=MINWATCHDATASOCKPORT, u16 dwMaxPort=MAXWATCHDATASOCKPORT);

/*====================================================================
������      : kdvAnnexQEnd
����        : �ر�Զң����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: ��			  
����ֵ˵��  : ��
====================================================================*/
PROTO_EXTERN_API void kdvAnnexQEnd();

/*====================================================================
������      : NotifyFeccMsg
����        : H.224, H.281���ܻص�����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext   - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
			  tFeccStruct- Զң����(TFeccStruct)
			  terSrc     - Դ���ն��б�
			  terDst     - Ŀ�Ķ��ն��б�
����ֵ˵��  : �ɹ� - annexQOK
              ʧ�� - annexQParamError
====================================================================*/
typedef s32 (PROTO_CALLBACK *NotifyFeccMsg)(MemId pContext,  TFeccStruct tFeccStruct, TTERLABEL terSrc, TTERLABEL terDst);

/*====================================================================
��	 ��   ��: kdvSetFeccCallBack
��	      ��: ע��Ӧ�ûص�����(�������ͨ������һ�Σ��ص�ָ��ȫ�ֱ���)
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: pNotifyFeccMsg - �ص������ṹָ��
��   ��   ֵ: �ɹ� - annexQOK
			  ʧ�� - annexQParamError
====================================================================*/
PROTO_API s32  kdvSetFeccCallBack(IN NotifyFeccMsg pNotifyFeccMsg);

/*====================================================================
��	 ��   ��: kdvSetFeccChanCallBack
��	      ��: ע��Ӧ�ûص�����(���ÿ��ͨ������һ�Σ��ص�ָ�뱣����ÿ��ͨ����Ϣ��)
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��:	pContext	   - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
				pNotifyFeccMsg - �ص������ṹָ��
��   ��   ֵ: �ɹ� - annexQOK
			  ʧ�� - annexQParamError
====================================================================*/
PROTO_API s32  kdvSetFeccChanCallBack( IN MemId pContext, IN NotifyFeccMsg pNotifyFeccMsg);

/*====================================================================
������      : kdvAnnexQInitSendSession
����        : Զң�ŵ����������ʼ��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext		- ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
              dwRemoteIp	- ����ͨ�������ĶԶ˵�IP��ַ
              dwRemotePort	- ����ͨ�������ĶԶ˵Ķ˿ں�
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQInitSendSession(IN MemId pContext, IN u32 dwRemoteIp, IN u16 dwRemotePort);

/*====================================================================
������      : kdvAnnexQNewSendSession
����        : ����Զң����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext  - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
			  dwLocalIp	- ����ͨ����ip
			  wLocalPort- ����ͨ����port
			  bSip      - �Ƿ���sip��Զҡ����
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQNewSendSession(IN MemId pContext, IN u32 dwLocalIp, IN u16 wLocalPort, IN BOOL32 bSip=FALSE);

/*====================================================================
������      : kdvAnnexQDeleteSendSession
����        : ɾ������Զң���ݵ��ŵ�
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext  - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����			  
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQDeleteSendSession(IN MemId pContext);

/*====================================================================
������      : kdvAnnexQNewRecvSession
����        : ����Զң���ݵ��ŵ�
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext  - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
              dwLocalIp	- IP��ַ
              wLocalPort- �˿ں�			  
			  bSip      - �Ƿ���sip��Զҡ����
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQNewRecvSession(IN MemId pContext, IN u32 dwLocalIp, IN u16 wLocalPort, IN BOOL32 bSip=FALSE);

/*====================================================================
������      : kdvAnnexQDeleteRecvSession
����        : ɾ������Զң���ݵ��ŵ�
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext  - ÿ��FECCͨ����Ψһ��ʶ�������ŵ���� 			  
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQDeleteRecvSession(IN MemId pContext); 

/*====================================================================
������      : kdvAnnexQSetEncryptSendSession
����        : ���÷���Զң�����ŵ��ļ�����Ϣ
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext			- ÿ��FECCͨ����Ψһ��ʶ�������ŵ���� 
			  ptEncryptSync		- ������Ϣ(TEncryptSync)			  
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetEncryptSendSession(IN MemId pContext, IN TEncryptSync *ptEncryptSync);

/*====================================================================
������      : kdvAnnexQSetDecryptRecvSession
����        : ���ý���Զң�����ŵ��ļ�����Ϣ
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext			- ÿ��FECCͨ����Ψһ��ʶ�������ŵ���� 
			  ptEncryptSync		- ������Ϣ(TEncryptSync)			  
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetDecryptRecvSession(IN MemId pContext, IN TEncryptSync *ptEncryptSync);


/*====================================================================
��	 ��   ��: kdvFeccBind
��	      ��: �������а�Զң���󣬵�Ե����ʱ�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: pContext	 - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
              localTer   - �����ն��б�(TTERLABEL)
			  remoteTer  - Զ���ն��б�(TTERLABEL)
��   ��   ֵ: �ɹ� - annexQOk
              ʧ�� - !annexQOk
====================================================================*/
PROTO_API s32 kdvFeccBind(IN MemId pContext, IN TTERLABEL localTer, IN TTERLABEL remoteTer, IN BOOL32 bSync = TRUE);

/*====================================================================
��	 ��   ��: kdvSendFeccMsg
��	      ��: ͨ��h224ͨ������Զң����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: pContext	 - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
			  feccStruct - Զң����(TFeccStruct)
��   ��   ֵ: �ɹ� - annexQOk
              ʧ�� - !annexQOk
====================================================================*/
PROTO_API s32 kdvSendFeccMsg(IN MemId pContext, IN TFeccStruct tFeccStruct, IN BOOL32 bSync = TRUE);

/*====================================================================
������      : kdvFeccSetStreamId
����        : �˿ڸ���ʱ����Զң����id
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext		- ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
			  EndPointId    - �ն˵�id, ��ǰ��֧��e164��
			  IdLen         - �ն�id�ĳ���
			  StreamId      - ��id
			  bSendChan		- �Ƿ���Զң����ͨ��
����ֵ˵��  : annexQOk if succeed, or other if fails
====================================================================*/
PROTO_API s32 kdvFeccSetStreamId(IN MemId pContext, TFeccStreamIdInfo tFeccStreamIdInfo, IN BOOL32 bSync = TRUE);

/*====================================================================
������      : kdvAnnexQSetKeepAliveAddress
����        : ����h460��Զң��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext  - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
			  dwLocalIp	- KeepAliveͨ����ip
			  wLocalPort- KeepAliveͨ����port
              dwInterval- KeepAliveͨ���Ĵ�ʱ����
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetKeepAliveAddress(IN MemId pContext, IN u32 dwKeepAliveIp, IN u16 wKeepAlivePort, IN s32 dwInterval=0, IN BOOL32 bSync = TRUE);

#ifdef _ENABLE_QUANTUM_PROJECT_
/*====================================================================
������      : kdvAnnexQSetQtEncrptyHandle
����        : ����QT���ܾ��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hQtCallHandle  - ���Ӻ��о��
              bQTEnable      - ���Ӽ���
			  bSendChannel   - ͨ������

����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetQTEncrptyHandle(IN MemId pContext,IN QTCALLHANDLE hQtCallHandle,IN BOOL32 bSendChannel = FALSE);
#endif

#ifdef _KDV_SRTP_SUPPORT_
/*====================================================================
������      : kdvFeccSetSrtp
����        : ����Զҡͨ����srtp����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: pContext    - ÿ��FECCͨ����Ψһ��ʶ�������ŵ����
             bSend  	 - ͨ������TRUEΪ����ͨ����FALSEΪ����ͨ��
             tSrtpCrypto - srtp�����Ϣ		  
����ֵ˵��  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvFeccSetSrtp(IN MemId pContext, IN BOOL32 bSend, IN TMediaSrtpCrypto tSrtpCrypto, IN BOOL32 bSync=TRUE); 
#endif

//����ԶңTOSֵ
PROTO_API s32 kdvSetDataTOS(s32 nTOS);
PROTO_API s32 kdvGetDataTOS();


//Frame Header Structure
typedef struct tagH224Data
{
    u8     *m_pData;       // ���ݻ���
    u32     m_dwDataSize;  // m_pDataָ���ʵ�ʻ����С�����С
}TH224Data,*PTH224Data;

typedef struct PROTO_API tagH224Session
{
public:
	TTERLABEL	m_tSrcLabel;
	TTERLABEL	m_tDstLabel;
	BOOL32      m_bSip;//sip��323��Զҡ��������sip�޽��ǡ��ֽ��򲻷�ת������У��͡�������0����

public:
	tagH224Session()
	{	
		Clear();
	}
	~tagH224Session()
	{        
        Clear();
	}

	void Clear()
	{
		m_tSrcLabel.Clear();
		m_tDstLabel.Clear();
		m_bSip = FALSE;
	}
    void FeccBind(IN TTERLABEL tSrcLabel, IN TTERLABEL tDstLabel );

/*====================================================================
������      : kdvCreateFeccMsg
����        : ����FECC����Ϣ����TFeccStruct-->TH224Data
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: tFeccStruct	- ҵ��ʹ�õ�Զң��Ϣ�ṹ��TFeccStruct
			  tDataHdr		- FECC����Ϣ��RTP���ݲ���
����ֵ˵��  : TRUE if succeed, or FALSE if fails
====================================================================*/
	BOOL32  kdvCreateFeccMsg( IN TFeccStruct &tFeccStruct, OUT TH224Data &tDataHdr);

/*====================================================================
������      : kdvExtractFeccMsg
����        : ����FECC��Ϣ����TH224Data-->TFeccStruct
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: tFeccStruct	- ҵ��ʹ�õ�Զң��Ϣ�ṹ��TFeccStruct
			  TH224Data		- FECC����Ϣ��RTP���ݲ���
����ֵ˵��  : TRUE if succeed, or FALSE if fails
====================================================================*/
	BOOL32  kdvExtractFeccMsg( OUT TFeccStruct &tFeccStruct, IN const TH224Data &tDataHdr);

//	void operator = (const tagH224Session& tH224Session);

private:
    u16 PackH224Payload(IN u8* h224Buf,  IN u16 h224Len, OUT u8* rawData, IN u32 rawBufLen);
	u32 ExtractH224Payload(IN u8* rawData, IN u32 rawLen, OUT u8* h224Buf, IN u16 h224BufLen);
	u16 GenCRC16Code( u8 *pbyBuff, u16 wBuffLen );
 	
}TH224Session;
  

#endif

