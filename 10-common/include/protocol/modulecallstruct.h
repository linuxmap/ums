#ifndef MODULECALLSTRUCT_H
#define MODULECALLSTRUCT_H

#include "protocolcommonpublic.h"
#include "kdvcommon.h"
#include "osp.h"
#include "kdvdef.h"

#ifdef _ENABLE_QUANTUM_PROJECT_
#include "qtinterface.h"					
#endif

#define MAX_LEN_CALLID			128
#define MAX_LEN_CALL_ALIAS		64
#define MAX_LEN_PRODUCT_ID		128
#define MAX_LEN_VERSION_ID		128
#define MAX_AUDIO_NUM			4
#define MAX_VIDEO_NUM			4
#define MAX_FECC_NUM			1
#define MAX_TP_STREAM_NUM		3
#define MAX_ENCRYPT_KEY_LEN		(u8)128
#define MAX_LEN_EPID			64
#define MAX_ALIAS_NUM			64
#define MAX_E164_NUM			64
#define MAX_CONFMT_NUM			192
#define MAX_TERMINALID_LEN		128
#define MAX_PASSWD_LEN			128
#define MAX_ONLINE_LIST_NUM		64
#define MAX_H243PWD_LEN		    (u16)32                 //���볤��

#define AES_KEY_LEN				(u8)16

#define MAX_FLOOR_NUM			5
#define MAX_MEDIA_NUM_PER_FLOOR 5
#define MAX_MEDIA_CAP_NUM		20
#define MAX_CONF_ID_LEN			16
#define MAX_CONF_NAME_LEN		96
#define MAX_CONF_E164_LEN		16
#define MAX_USERNAME_LEN		32			// For SIP DIGEST authorization, be noticed that LEN_USERNAME is defined with 64 in kdvsipcommon.h
#define MAX_PASSWORD_LEN		16			// If we wish to store the DIGEST password, we must make the password len up to 32 bytes
#define MAX_TERMINAL_NUM		32
#define MAX_DOMAINNAME_LEN      64

#define MAX_MTCAMERA_NUM		7			// ����ͷ������ (���ն˶���MT_MAX_CAMERA_NUMͳһ)
#define MAX_CONF_AUDMIX_NUM_TP	27			// ��������������
#define INVALID_INDEX_TP		0xFFFF

#define MODULE_VIDEO_DEFAULT_BITRATE		768
#define MODULE_VIDEO_DEFAULT_MPI			1
#define MODULE_AUDIO_DEFAULT_TIMEPERCAPTURE 20
#define MODULE_AUDIO_DEFAULT_PAYLOADTYPE	0
#define MODULE_AUDIO_DEFAULT_MAXFRAME		1
#define MODULE_VIDEO_DEFAULT_FRAMERATE		30
#define MODULE_VIDEO_DEFAULT_PAYLOADTYPE	0
#define MODULE_REG_DEFAULT_TIMETOLIVE		60
#define MODULE_CONF_MAX_TERMINALNO			192
#define SEEN_BY_OTHERLIST_MASK_NUM 6
#define TelephoneEventCap_ENCODING_LEN 256
#define MAX_SIP_NONSTD_HEADER_NUM       10
#define MAX_SDP_ATTR_NAME_LEN           50
#define MAX_SDP_ATTR_VALUE_LEN          300

#ifdef _KDV_SRTP_SUPPORT_
#define MODULE_MAX_CRYPTO_NUM 12
#define MODULE_MAX_CRYPTO_KEY_LEN 100
#endif

#include <string.h> 

#ifndef DECLARE_MODULE_HANDLE
#define DECLARE_MODULE_HANDLE(name)    typedef struct { MemId unused; } name##__ ; \
	typedef const name##__ * name; \
typedef name*  LP##name;
#endif

#ifndef MIN
#define MIN(a,b) ((a)>(b)?(b):(a))
#endif

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

DECLARE_MODULE_HANDLE(HMDLAPPCALL)
DECLARE_MODULE_HANDLE(HMDLCALL)
DECLARE_MODULE_HANDLE(HMDLAPPCHANNEL)
DECLARE_MODULE_HANDLE(HMDLCHANNEL)
DECLARE_MODULE_HANDLE(HMDLREG)
DECLARE_MODULE_HANDLE(HMDLAPPREG)
DECLARE_MODULE_HANDLE(HMDLAPPCONFID)

enum emModuleEndpointType
{
	emModuletypeBegin = 0,
	emModuleEndpointMcu,
	emModuleEndpointMT ,
	emModuleEndpointGk , 
	emModuleEndpointGateway,
	emModuleEndpointCNS,
	emModuleEndpointUMS,
	emModuleEndpointVRS,
};

enum emModuleAliasType
{
	emModuleType_aliastype,
	emModuleType_e164 = 0x1,
	emModuleType_h323ID,
	emModuleType_email,
	emModuleType_epID,
	emModuleType_GKID,
	emModuleType_partyNumber,
	emModuleType_others
};

enum emModuleIpType
{
	emModuleIPV4,
	emModuleIPV6,
};

enum emModuleCallType
{
	emModuleIPCall,
	emModuleAliasCall,
	emModuleE164Call,
};

//���йҶ�ԭ��
enum EmModuleCallDisconnectReason
{
	emModuleDisconnect_Busy = 1   ,//�Զ�æ
	emModuleDisconnect_Normal     ,//�����Ҷ�
	emModuleDisconnect_Rejected   ,//�Զ˾ܾ�
	emModuleDisconnect_Unreachable ,//�Զ˲��ɴ�
	emModuleDisconnect_Local       ,//����ԭ��
	emModuleDisconnect_unknown     ,//δ֪ԭ��
	emModuleDisconnect_custom     ,//δ֪ԭ��

	//TP
	emModuleDisconnect_AlredayInDualStream, //����˫���У��޷���������˫��
	emModuleDisconnect_Normal_Peer,         //�Է��Ҷ�
	emModuleDisconnect_Abnormal,            //���˵��߹Ҷ�
	emModuleDisconnect_Abnormal_Peer,       //�Զ˵��߹Ҷ�
	emModuleDisconnect_MultiConfOver,       //���������
	emModuleDisconnect_ConfAlredayExit,     //�����Ѿ�����
	emModuleDisconnect_InvalidDestAddr,		//��Ч��Ŀ�ĵ�ַ

	emModuleDisconnect_CallFull, //���о������(���ܴ��ں��о��δ�ͷŵ�����)

	emModuleDisconnect_MaxMtNum, //�����к����Ѵ�����

	//����ԭ��
	emModuleDisconnect_StreamEncryptKeyNotEqual,    //��������֧�ֵ��������ܣ���ʽ����Կ����һ��
	
#ifdef _ENABLE_QUANTUM_PROJECT_
	emModuleDisconnect_RegSerUnreachable,			//ע����������ɴ�
	emModuleDisconnect_AliasNotFound,				//����������
	emModuleDisconnect_GetSignalEncryptKeyFailed,	//��ȡ����������Կʧ��
	emModuleDisconnect_AutoGetRegSerAddrFailed,		//IP����ʱ��ȡע���������ַʧ��
	emModuleDisconnect_QTDevConnectionBroken,		//���������ն˵���
	emModuleDisconnect_QTDevConnectionBroken_peer,		//�Զ������ն˵���
#endif
	
	//mcu
	emModuleDisconnect_RmtReconnect = 100,   // ��������ȶԶ˵�  
	emModuleDisconnect_EncrypeErr,    
	emModuleDisconnect_AdaptBusy,     
	emModuleDisconnect_MccDrop,              // ��عҶ�     
	emModuleDisconnect_ChairDrop,            // ��ϯ�Ҷ�     
	emModuleDisconnect_MMcuDrop,             // �ϼ�����Ҷ�  
	emModuleDisconnect_ConfReleaseNoMt,      // ���ն��Զ����-1����   
	emModuleDisconnect_ConfReleaseNoJoinedMt,// �������ն��Զ����-5����    
	emModuleDisconnect_ConfReleaseOnlyOneMt, // ��һ�������ն��Զ����-10����  
	emModuleDisconnect_Exception,            // �쳣�Ҷ�   
	emModuleDisconnect_MpDisconnect,         //mp����    

	//�ն�
	emModuleDisconnect_DonotDisturb,         //�����
	

};//not same as CBB5.0 Check again

//the value is same as EmVendorProductId(kdvcommon.h)
enum EmModuleVendorID
{
	emModule_vendor_MICROSOFT_NETMEETING = 1,
	emModule_vendor_KEDA,
	emModule_vendor_HUAWEI,
	emModule_vendor_POLYCOM,
	emModule_vendor_POLYCOM_MCU,
	emModule_vendor_TANDBERG,
	emModule_vendor_RADVISION,
	emModule_vendor_VCON,
	emModule_vendor_SONY,
	emModule_vendor_VTEL,
	emModule_vendor_ZTE,
	emModule_vendor_ZTE_MCU,
	emModule_vendor_CODIAN,
	emModule_vendor_AETHRA,
	emModule_vendor_CHAORAN,
	emModule_vendor_AVCON,
	emModule_vendor_DONJIN,
	emModule_vendor_UNKNOWN,
	emModule_vendor_END
};

enum EmModuleConnection
{
	emModuleConnectionType = 0,
	emModuleTcpConnection,
	emModuleUdpConnection,
	emModuleSCTPConnection,
	emModuleTLSConnection,
};

enum EmModuleDirection
{
	emModule_Direction_Begin = 0,
	emModule_Direction_SendOnly = 1,
	emModule_Direction_RecvOnly = 2,
	emModule_Direction_SendRecv = 3,
};

typedef struct tagCallIpAddr
{
	emModuleIpType m_emIpType;
	u32 m_dwIp;
	u8  m_abyIp[16];
public:
	tagCallIpAddr()
	{
		Clear();
	}

	void Clear()
	{
		m_emIpType	= emModuleIPV4;
		m_dwIp		= 0;
		memset(m_abyIp, 0, sizeof(m_abyIp));
	}

	void SetIpAddr( u32 dwIp ) 
	{
		m_emIpType = emModuleIPV4;
		m_dwIp = dwIp;
	}
	u32 GetIpAddr()
	{
		if ( emModuleIPV4 == m_emIpType )
		{
			return m_dwIp;
		}
		else
			return 0;
	}
	void SetIpv6Addr( u8 abyIpv6[] )
	{
		if ( NULL == abyIpv6 )
		{
			return;
		}
		m_emIpType = emModuleIPV6;
		memcpy( m_abyIp , abyIpv6 , 16 );
	}

	void GetIpv6Addr( u8* pbyIpv6 )
	{
		if ( NULL == pbyIpv6 )
		{
			return;
		}
		if ( emModuleIPV6 == m_emIpType )
		{
			memcpy( pbyIpv6 , m_abyIp , 16 );
		}
		else
			return;
	}
}TCallIpAddr;

typedef struct tagCallAliasAddr
{
	u8 m_abyCallAliasAddr[MAX_LEN_CALL_ALIAS + 1];
public:
	tagCallAliasAddr()
	{
		Clear();
	}

	void Clear()
	{
		memset( m_abyCallAliasAddr , 0 , sizeof(m_abyCallAliasAddr) );
	}

	void SetCallAliasAddr( u8* pbyAlias , u16 wLen )
	{
		if ( NULL == pbyAlias || 0 == wLen )
		{
			return;
		}
		strncpy( (s8*)m_abyCallAliasAddr , (s8*)pbyAlias ,  MAX_LEN_CALL_ALIAS );
	}

	void GetAliasAddr( u8* pbyAlias , u16 wLen )
	{
		if ( NULL == pbyAlias || 0 == wLen )
		{
			return;
		}
		strncpy( (s8*)pbyAlias , (s8*)m_abyCallAliasAddr, wLen ); 
	}
}TCallAliasAddr;

typedef struct tagModuleTransportAddress
{
	emModuleIpType m_emIpType;
	u32 m_dwIp;
	u8  m_abyIp[16];
	u16 m_wPort;
	
public:
	tagModuleTransportAddress()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emIpType = emModuleIPV4;
		m_dwIp = 0;
		memset( m_abyIp , 0 , 16 );
		m_wPort = 0;
	}
	
	void SetIpAddr( u32 dwIp , u16 wPort ) 
	{
		m_emIpType = emModuleIPV4;
		m_dwIp = dwIp;
		m_wPort = wPort;
	}
	void GetIpAddr( u32* pdwIp , u16* pwPort )
	{
		if ( NULL == pdwIp && NULL == pwPort )
		{
			return;
		}
		if ( emModuleIPV4 == m_emIpType )
		{
			*pdwIp	= m_dwIp;
			*pwPort = m_wPort;
		}
		else
			return;
	}
	void SetIpv6Addr( u8 abyIpv6[] , u16 wPort=0 )
	{
		if ( NULL == abyIpv6 )
		{
			return;
		}
		m_emIpType = emModuleIPV6;
		memcpy( m_abyIp , abyIpv6 , 16 );
	}
	
	//This function will not return Port value according to the current implementation
	void GetIpv6Addr( u8* pbyIpv6 , u16* pwPort )
	{
		if (NULL != pbyIpv6 && NULL != pwPort)
		{
			return;
		}
		if ( emModuleIPV6 == m_emIpType )
		{
			memcpy( pbyIpv6 , m_abyIp , 16 );
		}
	}
}TModuleTransportAddress;

enum EmModuleProfileMask
{
	emModuleProfileBaseline = 64,
	emModuleProfileMain		= 32,
	emModuleProfileExtend	= 16,
	emModuleProfileHigh		= 8
};

// H.264 NAL mode --> packetization mode
enum EmModuleH264NALMode
{
	emModuleNALSingle          = 0,       // single
	emModuleNALNoneInterleaved = 1,       // not interleaved
	emModuleNALInterleaved     = 2,       // interleaved
};

enum EmModuleH265ProfileMask
{
	//emModuleH265ProfileGeneral = 1,
	emModuleH265ProfileMain		,
	emModuleH265ProfileMain10	,
	emModuleH265ProfileMainStill,
};

//��ƵЭ������
enum EmModuleVideoFormat
{
    emModuleVH261     = 0,
	emModuleVH262     = 1,
	emModuleVH263     = 2,
	emModuleVH263plus = 3,
	emModuleVH264     = 4,
	emModuleVMPEG4    = 5,
	emModuleVH265     = 6,
	
	emModuleVEnd =  10,
};

//��ƵЭ������
enum EmModuleAudioFormat
{
    emModuleAG711a			= 0,
	emModuleAG711u			= 1,
	emModuleAG722			= 2,
	emModuleAG7231			= 3,
	emModuleAG728			= 4,
	emModuleAG729			= 5,
	emModuleAMP3			= 6,
	emModuleAG721			= 7,
	emModuleAG7221			= 8,
	emModuleAG719			= 9,
	emModuleAMpegAACLC		= 10,
	emModuleAMpegAACLD		= 11,
	
	emModuleAMpegAACLCDual	= 12,
	emModuleAMpegAACLDDual	= 13,
	emModuleOPUS            = 14,
	emModuleTelephoneEvent	= 15,
	emModuleAEnd			= 20,	 
};

enum EmModuleAudioSampleFreq                    //sampling frequency
{
	emModuleFs96000 = 0,
    emModuleFs88200 = 1,
    emModuleFs64000 = 2,
    emModuleFs48000 = 3,
    emModuleFs44100 = 4,
    emModuleFs32000 = 5,
    emModuleFs24000 = 6,
    emModuleFs22050 = 7,
    emModuleFs16000 = 8,
    emModuleFs12000 = 9,
    emModuleFs11025 = 10,
    emModuleFs8000  = 11
};

enum EmModuleAudioChnlCfg
{
	emModuleChnlCust   = 0,
    emModuleChnl1      = 1,                   //������
    emModuleChnl2      = 2,                   //˫����
    emModuleChnl3      = 3,
    emModuleChnl4      = 4,
    emModuleChnl5      = 5,
    emModuleChnl5dot1  = 6,                   //5.1����
    emModuleChnl7dot1  = 7                    //7.1����
};

//�ֱ�������
enum EmModuleVideoResolution
{
    emModuleVResolutionAuto     = 0,   //�Զ�
	emModuleVSQCIF              = 1,   //SQCIF128x96
	emModuleVQCIF               = 2,   //QCIF176x144
	emModuleVCIF                = 3,   //CIF352x288
	emModuleV2CIF               = 4,   //2CIF352x576
	emModuleV4CIF               = 5,   //4CIF704x576
	emModuleV16CIF              = 6,   //16CIF1408x1152
	
	emModuleVHD480i720x480      = 7,   //480i720x480
	emModuleVHD480p720x480      = 8,   //480p720x480
	emModuleVHD576i720x576      = 9,   //576i720x576
	emModuleVHD576p720x576      = 10,  //576p720x576
	emModuleVHD720p1280x720     = 11,  //720p1280x720
	emModuleVHD1080i1920x1080   = 12,  //1080i1920x1080
	emModuleVHD1080p1920x1080   = 13,  //1080p1920x1080
	
	emModuleVGA352x240          = 14,  //352x240
	emModuleVGA704x480          = 15,  //704x480
	emModuleVGA640x480          = 16,  //VGA640x480
	emModuleVGA800x600          = 17,  //SVGA800x600
	emModuleW4CIF               = 18,  //Wide4CIF 16:9 1024*576
	emModuleVGA1024x768         = 19,  //XGA1024x768
	emModuleVGA1280x768         = 20,  //WXGA1280x768
	emModuleVGA1280x800         = 21,  //WXGA1280x800
	emModuleVGA1366x768         = 22,  //WXGA1366x768
	emModuleVGA1280x854         = 23,  //WSXGA1280x854
	emModuleVGA1440x900         = 24,  //WSXGA1440x900
	emModuleVGA1280x1024        = 25,  //SXGA1280x1024
	emModuleVGA1680x1050        = 26,  //SXGA+1680x1050
	emModuleVGA1600x1200        = 27,  //UXGA1600x1200
	emModuleVGA1920x1200        = 28,  //WUXGA1920x1200
	
	//Resolutions supported by H.265, added by zgf according to kdvcommon.h
	emModuleVRes2Kx1K           = 29,			// 2048 1024  2 097 152  - - - - - 31.8 63.7 
	emModuleVRes2Kx1080         = 30,			// 2048 1080  2 228 224  - - - - - 30.0 60.0 
	emModuleVRes4XGA            = 31,				// 2048 1536  3 145 728  - - - - - -  - 
	emModuleVRes16VGA           = 32,				// 2560 1920  4 915 200  - - - - - -  - 
	emModuleVRes3616x1536       = 33,			// (2.35:1)  3616  1536  5 603 328  - - - - - -  - 
	emModuleVRes3672x1536       = 34,			// (2.39:1)  3680  1536  5 701 632  - - - - - -  - 
	emModuleVRes3840x2160       = 35,			// (4*HD)  3840  2160  8 355 840 - - - - - -  - 
	emModuleVRes4Kx2K           = 36,				// 4096 2048  8 388 608  - - - - - -  - 
	emModuleVRes4096x2160       = 37,			// 4096 2160  8 912 896  - - - - - -  - 
	emModuleVRes4096x2304       = 38,			// (16:9)  4096  2304  9 437 184  - - - - - -  - 
	emModuleVRes7680x4320       = 39,			// 7680 4320  33 423 360  - - - - - -  - 
	emModuleVRes8192x4096       = 40,			// 8192 4096  33 554 432 - - - - - -  - 
	emModuleVRes8192x4320       = 41,			// 8192 4320  35 651 584 - - - - - -  - 
	emModuleVResEnd ,
};

enum EmModuleConfMsgType
{
	emModuleConfMsgTypeBegin = 500,  //���Ҫ��TP����Ϣ����ͻ
		
	emModuleMultipleConference,   //NULL
	emModuleCancelMultipleConference, //NULL
	emModuleTerminalNumberAssign, //TMDLTERLABEL
	emModuleTerminalYouAreSeeing, //TMDLTERMINALINFO + BOOL32 + TYouAreSeeing
	emModuleSeenByAll,  //NULL
	emModuleCancelSeenByAll,  //NULL

	emModuleTerminalListRequest, //NULL
	emModuleTerminalListResponce, //TMDLTERLABELLIST
	emModuleTerminalIDListRequest, //NULL
	emModuleTerminalIDListResponse, //TMDLTERINFOLIST + BOOL32 + TConfCnsList

	emModuleTerminalJoinConf,  //TMDLTERMINALINFO
	emModuleterminalLeftConf,  //TMDLTERMINALINFO

	emModuleRequestTerminalID, //TMDLTERLABEL
	emModuleMcTerminalIDResponse, //TMDLTERMINALINFO

	emModuleMakeTerQuietCmd, //TMDLTERLABEL(dst) + BOOL32(TRUE = ����/ FALSE = �ر�) ����
	emModuleMakeTerMuteCmd, //TMDLTERLABEL(dst) + BOOL32(TRUE = ����/ FALSE = �ر�) ����
	emModuleChgSecVidSendCmd, //BOOL32(����/�ر�) ��-��˫��

		//add by yj for confMSG [20130726]
	emModulevideoFpsChangeCmd,		//u32(emModuleChannelType) + u8(֡��)


	emModulevideoFormatChangeCmd,	    //���ͣ�emModuleVideoType + u8(����vccommon.h�����Ƶ��ʽ) ( ��߿���ѡ������˳��With(u32)+Height(u32) )
										//���գ�emModuleVideoType + u32 + u32 (�����նˣ������Ǳ�����ֻ���������ȷ���ֱ���)
		
										//*    +   u8  ͨ������   LOGCHL_VIDEO      (Ĭ������Ƶͨ��)
										//*    +   u8  �ֱ������� VIDEO_FORMAT_QCIF (176*144)
										//ע���µ�MCU���������¿�Ⱥ͸߶��ֶΣ��ϵ�MCUû�������ֶ�(PA������ֱ�Ӱѿ�ߴ���)
										//*    +   u32  �ֱ��ʿ�� 
										//*    +   u32  �ֱ��ʸ߶�
		
	emModuleterStatusInd,				//TModuleTerStatus ter->Mc
	emModulesetAudioVolumeCmd,			// ��������(u8) + ����(u8)
		//end [20130726]

		//added by sna for dual channel on/off [20140107]
	emModuleStartRcvDualInd,			//NULL
	emModuleStopRcvDualInd,				//NULL
		//added end [20140107]
	emModuleNSMGeneral,              //�Ǳ�����Ϣadded by hong[20140910]

	emModuleChairSelectViewCmd,  //TMDLTERLABEL(dst) + u32(EmDataType:audio��video��av) ��ϯѡ��--�Ǳ�
	emMoudleSendThisSource,      //TMDLTERLABEL(dst) + u32(EmCtrlMode:command��request)  ѡ���ն�--��׼
	emMoudleSendThisSourceResponse, //B00L32(bGranted:TRUE FALSE)
	emMoudleCancelSendThisSource, //NULL
	emMoudleVideoAliasInd,
	emModuleEnterH243Password,		//MCѯ�ʻ�������    MC->ter,   [incoming]&[outgoing]: NULL
	emModulePasswordResponse,		//ter->MC,   [incoming]&[outgoing]: [TPassRsp]
	emModuleKedaManuProduct,			//������������ʶ�� mt<-->mcu��mt<-->mt�Ǳ����ݣ�
										//V5.0 <--> V5.0: protobuf
										//V5.0 <--> V4.x(HD3): TKedaManuProduct
										//TPS <--> TPS: TKedaManuProduct
	emModuleConfInfoRsp,		//���������Ϣ��״̬	
	emModuleDropConference,     //�������� chair->MC,MC->ter,  [incoming]&[outgoing]: NULL
#ifdef _ENABLE_QUANTUM_PROJECT_
	emModuleQuantumMediaKey,
#endif
	emModuleConfMsgTypeEnd
};

enum EmModuleMMcuMsgType
{
	emModuleMMcuBegin = emModuleConfMsgTypeEnd + 1,			

	emModuleRegUnReg_Req,		//[IN]&[OUT]:[TRegUnRegReq]	register request

	emModuleRegUnReg_Rsp,		//[IN]&[OUT]:[TRegUnRegRsp]	register response

	emModuleNewRoster_Ntf,		//[IN]&[OUT]:[TRosterList]  roster notify

	emModulePartList_Req,		//[IN]&[OUT]:[TReq]         request part list

	emModulePartList_Rsp,		//[IN]&[OUT]:[TPartListMsg + n*sizeof(TPart)] reponse part list (dwpid ==0 ��ʾ�Է���MCU)

	emModuleInvitePart_Req,		//[IN]&[OUT]:[TInvitePartReq]  invite part request

	emModuleInvitePart_Rsp,		//[IN]&[OUT]:[Tsp]             invite part response

	emModuleNewPart_Ntf,		//[IN]&[OUT]:[TPart]           new part notify

	emModuleCall_Alerting_Ntf,	//[IN]&[OUT]:[TCallNtf]

	emModuleReinvitePart_Req,	//[IN]&[OUT]:[TReInviteReq]    reinvite part request

	emModuleReinvitePart_Rsp,	//[IN]&[OUT]:[Tsp]        reinvite part response

	emModuleDisconnPart_Req,	//[IN]&[OUT]:[TPartReq]     disconnect part request

	emModuleDisconnpart_Rsp,	//[IN]&[OUT]:[Tsp]         disconnect part response

	emModuleDisconnpart_Ntf,	//[IN]&[OUT]:[TDiscPartNF] disconnect part notify

	emModuleDeletepart_Req,		//[IN]&[OUT]:[TPartReq]		delete part request

	emModuleDeletepart_Rsp,		//[IN]&[OUT]:[Tsp]			delete part response

	emModuleDeletepart_Ntf,		//[IN]&[OUT]:[TPartNtf]   delete part notify (whether or not local)

	emModuleSetIn_Req,			//[IN]&[OUT]:[TSetInReq]    request video in

	emModuleSetIn_Rsp,			//[IN]&[OUT]:[Tsp]          response msg

	emModuleSetOut_Req,			//[IN]&[OUT]:[TSetOutReq]//��Ƶ������Լ�������(��Ƶ����:MCU->MT)

	emModuleSetOut_Rsp,			//[IN]&[OUT]:[Tsp]//��Ƶ������Լ���Ӧ��(��Ƶ����:MCU->MT)

	emModuleOutPut_Ntf,			//[IN]&[OUT]:[TPartOutputNtf]      video output notify (dwpid ==0 ��ʾ�Է���MCU)

	emModuleNewSpeaker_Ntf,		//[IN]&[OUT]:[TNewSpeakerNtf]      newSpeaker output notify (dwpid ==0 ��ʾ�Է���MCU)

	emModuleAudioInfo_Req,		//[IN]&[OUT]:[TConfVideInfoReq]         audio info request 

	emModuleAudioInfo_Rsp,		//[IN]&[OUT]:[TConfAudioInfo]    audio info response

	emModuleVideoInfo_Req,		//[IN]&[OUT]:[pReq]          conference videoinfo request

	emModuleVideoInfo_Rsp,		//[IN]&[OUT]:[TConfVideoInfo] conference videoinfo response

	emModuleConfView_Chg_Ntf,	//[IN]&[OUT]:[TConfViewChgNtf] conference view format(layout geometry)change notify

	emModulePartMediaChan_Req,	//[IN]&[OUT]:[TPartMediaChanReq] ��������Ա��/�ر���/��Ƶ/����ͨ��

	emModulePartMediaChan_Rsp,	//[IN]&[OUT]:[TRsp]    response

	emModulePartMediaChan_Ntf,	//[IN]&[OUT]:[TPartMediaChanNtf] �����Ա����/��Ƶ/����ͨ����/�رյ�֪ͨ

	emModuleGetMcuServiceList_Req,	//[IN]&[OUT]:[TReq] ��ȡMCU�ϵķ���ģ���б��������Ϣ

	emModuleGetMcuServiceList_Rsp,	//[IN]&[OUT]:[��ʱδ����]  response

	emModuleGetMucConfList_Req,		//[IN]&[OUT]:[TMCUConfListReq] ��ȡMCU�ϵ�ǰ�ٿ������л�����б�

	emModuleGetMucConfList_Rsp,		//[IN]&[OUT]:[��ʱδ����]

	emModuleGetConfgIdByName_Req,	//[IN]&[OUT]:[TGetConfIDByNameReq] ͨ���������ֻ�û���ID��������Ϣ

	emModuleGetConfgIdByName_Rsp,	//[IN]&[OUT]:[��ʱδ����]

	emModuleGet_ConfProfile_Req,	//[IN]&[OUT]:[TConfProfileReq] ��ȡMCU�ϵ�ǰ�ٿ������л����profile

	emModuleGet_ConfProfile_Rsp,	//[IN]&[OUT]:[��ʱδ����]

	emModuleNonStandard_Req,		//[IN]&[OUT]:[TNonStandardReq] �Ǳ�(�Զ���)������Ϣ

	emModuleNonStandard_Rsp,		//[IN]&[OUT]:[TNonStandardRsp] �Ǳ�(�Զ���)response��Ϣ

	emModuleNonStandard_Ntf,		//[IN]&[OUT]:[TNonStandardMsg] �Ǳ�(�Զ���)notify��Ϣ

	emModuleNot_Supported,			//Ŀǰ���ǻ���֧��,����radmuc֧�ֵ���Ϣ����

	emModuleVA_Req,					//[IN]&[OUT]:[TVAReq]

	emModuleVA_Rsp,					//[IN]&[OUT]:[TRsp]

	emModuleReleaseControl_of_Conf_Req,		//[IN]&[OUT]:[]

	emModuleReleaseControl_of_Conf_Rsp,		//[IN]&[OUT]:[]

	emModuleTakeControl_of_Conf_Req,		//[IN]&[OUT]:[]

	emModuleTakeControl_of_Conf_Rsp,		//[IN]&[OUT]:[]

	emModuleAllPart_SetOut_Req,				//[IN]&[OUT]:[]

	emModuleAllPart_SetOut_Rsp,				//[IN]&[OUT]:[]

	emModuleCreate_Conf_Req,				//[IN]&[OUT]:[]

	emModuleCreate_Conf_Rsp,				//[IN]&[OUT]:[]

	emModuleTerminate_Conf_Req,				//[IN]&[OUT]:[]

	emModuleTerminate_Conf_Rsp,				//[IN]&[OUT]:[]

	emModuleUndefined_Req,					//[IN]&[OUT]:[]

	emModuleUndefined_Rsp,					//[IN]&[OUT]:[]

	emModuleUndefined_Ntf,					//[IN]&[OUT]:[]

	emModuleSet_Layout_AutoSwitch_Request,	//[IN]&[OUT]:TSetLayoutAutoswitchReq

	emModuleSet_Layout_AutoSwitch_Response,

	emModuleMMcuEnd
};

//��������
enum  EmDataType 
{
	emModeNone = 0,
	emModeAudio,
	emModeVideo,
	emModeData,
};

//�������:makeTerminalBroadcaster��sendThisSource�Ĳ�����ʽ
enum EmCtrlMode 
{
	emModeInvalid = -1,
	emModeCommand,
	emModeRequest,
};

//����ģʽ
enum EmCallModeType
{
	emModeJoin,
	emModeCreate,
	emModeInvite
};
//��������
enum EmMdlEncryptType
{
	emMdlEncryptTypeNone = 1,//00000001
	emMdlEncryptTypeDES  = 2,//00000010
	emMdlEncryptTypeAES  = 4,//00000100
	emMdlEncryptTypeH239 = 8,//00001000
	emMdlEncryptTypeAES256  = 16,//00010000
};

#ifdef _KDV_SRTP_SUPPORT_
enum EmMdlSrtpMode
{
	emMdlSrtpModeNone,
	emMdlSrtpModeOptional,
	emMdlSrtpModeMandatory
};

enum EmMdlSrtpCryptoType
{
	emMdlSrtpCryptoNone = 0,     //������
	emMdlSrtpCryptoAES_CM_128,
	emMdlSrtpCryptoAES_CM_192,
	emMdlSrtpCryptoAES_CM_256,
	emMdlSrtpCryptoAES_GCM_128, 
	emMdlSrtpCryptoAES_GCM_192,
	emMdlSrtpCryptoAES_GCM_256,    
	emMdlSrtpCryptoSM4_CM_128,    //SMĿǰֻ��128��  
	emMdlSrtpCryptoSM1_CM_128, 
};

//for AES-CM and SM,the authType is HMAC_SHA1 and have tag length
//for AES-GCM,only has tag length
enum EmMdlSrtpAuthType
{
	emMdlSrtpAuthNone = 0,     //����֤
	emMdlSrtpAuthTag_8,
	emMdlSrtpAuthTag_16,
	emMdlSrtpAuthTag_32,
	emMdlSrtpAuthTag_80,	
};

typedef struct tagMdlMediaSrtpCrypto
{
	s32 m_nTag;
	EmMdlSrtpCryptoType m_emCryptoType;
	EmMdlSrtpAuthType   m_emAuthType;
	s8 m_achCryptoKey[MODULE_MAX_CRYPTO_KEY_LEN];

	tagMdlMediaSrtpCrypto()
	{
		Clear();
	}
	void Clear()
	{
		m_nTag = 0;
		m_emCryptoType = emMdlSrtpCryptoNone;
		m_emAuthType   = emMdlSrtpAuthNone;
		memset(m_achCryptoKey, 0, sizeof(m_achCryptoKey));
	}
} TMdlMediaSrtpCrypto;

typedef struct tagMdlSrtpMediaSetting
{
	EmMdlSrtpMode m_emSrtpMode;
	u32 m_dwCryptoCount;
	TMdlMediaSrtpCrypto m_atSrtpCrypto[MODULE_MAX_CRYPTO_NUM];

	tagMdlSrtpMediaSetting()
	{
		Clear();
	}
	void Clear()
	{
		m_emSrtpMode = emMdlSrtpModeNone;
		m_dwCryptoCount = 0;
		for (s32 i = 0; i < sizeof(m_atSrtpCrypto)/sizeof(m_atSrtpCrypto[0]); i++)
		{
			m_atSrtpCrypto[i].Clear();
		}
	}
} TMdlSrtpMediaSetting;
#endif

//������������ʶ�� mt<-->mcu���ݶ��˷Ǳ����ݳ���Ϊһ��BYTE�����ڴ洢������ʶ����
//��Ӧ�Ǳ���Ϣh_ctrl_KedaManuProduct	= 1121
typedef struct tagKedaManuProductTP
{
	u8	m_byAgentID; //�ݶ��˷Ǳ����ݳ���Ϊһ��BYTE�����ڴ洢������ʶ����
	tagKedaManuProductTP()
	{
		m_byAgentID = 0;
	}
}TKedaManuProductTP;

typedef struct PROTO_API tagPassRspTP
{
	TTERLABEL m_tTer;
	s32       m_nPassLen;
	u8        m_abyPassword[MAX_H243PWD_LEN+1]; 

	tagPassRspTP()
	{
		Clear();
	}

	void Clear()
	{
		memset( &m_tTer, 0, sizeof(m_tTer) );
		m_nPassLen = 0;
		memset( m_abyPassword, 0, sizeof(m_abyPassword) );
	}

	void host2net(BOOL32 bhton);

	//����TTERLABEL
	void SetTerLabel( TTERLABEL &tTerLabel )
	{
		m_tTer = tTerLabel;
	}
	//��ȡTTERLABEL
	TTERLABEL& GetTerlabel()
	{
		return m_tTer;
	}

	//����Password
	void SetPassword( u8 *pPassword, u16 wLen );

	//��ȡPassword
	u16 GetPassword( u8 *pbyPassword, u16 &wLen );

}TPassRspTP;

typedef struct tagTMdlPollInfoTP
{
	BOOL32 m_bIsPoll;
	u16  m_wPollExpire;
	
	tagTMdlPollInfoTP()
	{
		Clear();
	}

	void Clear()
	{
		//memset( this, 0, sizeof(tagTMdlPollInfoTP) );
		m_bIsPoll		= FALSE;
		m_wPollExpire = 0;
	}
}TMdlPollInfoTP;

typedef struct tagTMdlConfAuxMixInfoTP
{
	BOOL32 m_bStart;
	u16	m_wConfID;
	u16 m_wSpeakerIndex;					//�������������
	u16	m_awList[MAX_CONF_AUDMIX_NUM_TP];	//����ID

	void Clear()
	{
		m_bStart			= FALSE;
		m_wConfID			= INVALID_INDEX_TP;
		m_wSpeakerIndex	= 0;
		memset(this, 0, sizeof(tagTMdlConfAuxMixInfoTP));
	}
	tagTMdlConfAuxMixInfoTP()
	{
		Clear();
	}
}TMdlConfAuxMixInfoTP;

//����������Ϣ
typedef struct tagTMdlConfInfo
{
	s8	 m_achConfId[MAX_CONF_ID_LEN + 1];			// ����ID
	s8	 m_achConfName[MAX_CONF_NAME_LEN + 1];		// ������
	s8	 m_achConfNumber[MAX_CONF_E164_LEN + 1];	    // �������
	s8	 m_achConfPwd[MAX_PASSWORD_LEN + 1];			// ��������
	BOOL32 m_bNeedPassword;                             // �Ƿ���Ҫ����
	u16  m_wConfDuration;							    // �������ʱ��		
	EmModuleVideoFormat   m_emVideoFormat;			// ������Ƶ��ʽ(VIDEO_H261��)
	EmModuleAudioFormat   m_emAudioFormat;			// ������Ƶ��ʽ(AUDIO_MP3��)
	EmModuleVideoResolution  m_emResolution;			// ������Ƶ�ֱ���(VIDEO_CIF��)
//	EmModuleProfileMask m_emProfile;					// ����profile
	u32 m_emProfile;					// ����profile
	u8 m_byVidMPI;					                // ����֡��
	BOOL32 m_bIsAutoVMP;								// �Ƿ��Զ�����ϳ�
	BOOL32 m_bIsMix;	    							// �Ƿ����
	EmModuleVideoFormat	m_emSecVideoFormat;			// ˫����ʽ
	EmModuleVideoResolution m_emSecVidRes;			// ˫���ֱ���
//	EmModuleProfileMask m_emSecProfile;				// ˫��profile
	u32 m_emSecProfile;				// ˫��profile
	u8 m_bySecVidMPI;					                // ˫��֡��
	u16 m_wCallRate;									// ��������(kbps)
	u16	m_wDualCallRate;								// ˫����������(kbps)
	TMdlPollInfoTP  m_tPollInfo;
	TMdlConfAuxMixInfoTP m_tConfAudMixInfo;

public:
	tagTMdlConfInfo()
	{ 
		Clear();	
	}
	void Clear()
	{
		memset( this, 0, sizeof(tagTMdlConfInfo) );
		m_tPollInfo.Clear();
		m_tConfAudMixInfo.Clear();
	}
}TMdlConfInfo, *PTMdlConfInfo;

typedef struct tagModuleTEncryptKey
{
	EmMdlEncryptType m_emEncryptType;
	u8 m_byLen;   //��Կ����
	u8 m_abyKey[MAX_ENCRYPT_KEY_LEN]; //��Կ����
public:
	void Clear()
	{
		memset( this, 0, sizeof(tagModuleTEncryptKey) );
		m_emEncryptType = emMdlEncryptTypeNone;
	}
	tagModuleTEncryptKey()
	{
		Clear();
	}

	//����H235Key
	u8 SetEncryptKey(u8 *pBuf, u8 byLen)
	{
		m_byLen = MIN(byLen, MAX_ENCRYPT_KEY_LEN);
		memcpy(m_abyKey, pBuf, m_byLen);
		return m_byLen;
	}	
	//��ȡH235Key�ĳ���
	u8 GetEncryptKeyLen() 
	{
		return m_byLen; 
	}
	//��ȡH235Key
	u8* GetEncryptKey()
	{
		return m_abyKey;
	}

	void SetEncryptType( EmMdlEncryptType emEncryptType )
	{
		m_emEncryptType = emEncryptType;
	}

	EmMdlEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}

	//generate a key
	struct tagModuleTEncryptKey & GenerateEncrytKey()
	{
		s32 i = 0;
		s8 abyBuf[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,./;\"'<>?";
		s32 nstrLen = strlen( abyBuf );
		
		if ( m_emEncryptType == emMdlEncryptTypeAES )	// 16BYTE
		{
			for( i = 0; i < AES_KEY_LEN; i++ )
			{
				sprintf( (s8*)m_abyKey+i, "%c", abyBuf[rand() % nstrLen] );
			}
			m_byLen = AES_KEY_LEN;
		}
		else if (m_emEncryptType == emMdlEncryptTypeDES)  // 8BYTE
		{
			for( i = 0; i < 8; i++ )
			{
				sprintf( (s8*)m_abyKey+i, "%c", abyBuf[rand() % nstrLen] );
			}
			m_byLen = 8;
		}
		else
		{
			m_byLen = 0;
		}
		return *this;
	}

	void Print()
	{
		OspPrintf(TRUE, FALSE, "TModuleEncryptKey:EncryptType=%d, m_byLen=%d, key:", m_emEncryptType, m_byLen);
		s32 nLen = Minimum(m_byLen, AES_KEY_LEN);
		if ( emMdlEncryptTypeNone != m_emEncryptType )
		{
			for (int i = 0; i < nLen; i++)
			{
				OspPrintf(TRUE, FALSE, "%c", m_abyKey[i]);
				if ( i == (nLen - 1))
				{
					OspPrintf(TRUE, FALSE, "\n");
				}
			}
		}		
	}

}TModuleEncryptKey;


//�ն˵�ַ
typedef struct tagTerminalAddress
{
	emModuleCallType	m_emCallType;
	s8	m_achAlias[MAX_LEN_CALL_ALIAS + 1];	//�ն˱�����E164��
	TModuleTransportAddress	m_tModuleAddress;	//�ն�IP��ַ

public:
	tagTerminalAddress()
	{
		Clear();
	}
	void Clear()
	{
		m_emCallType = emModuleAliasCall;
		memset(m_achAlias, 0 ,sizeof(m_achAlias));
		m_tModuleAddress.Clear();
	}
}TerminalAddress, *PTerminalAddress;

typedef struct PROTO_API tagSipNstHeader
{
	s8	m_achName[MAX_SDP_ATTR_NAME_LEN];	/**< Param/header name.	    */
	s8	m_achValue[MAX_SDP_ATTR_VALUE_LEN];	/**< Param/header value.    */

	void Clear()
	{
		memset(m_achName, 0, sizeof(m_achName));
		memset(m_achValue, 0, sizeof(m_achValue));
	}
	tagSipNstHeader()
	{
		Clear();
	}
}TSipNstHeader;

typedef struct tagModuleCallInfo
{
	u8 m_abyCallId[MAX_LEN_CALLID];
	
	u16 m_wBitrate;
	emModuleEndpointType m_emEndpointType;
	emModuleEndpointType m_emPeerEndpointType;
	
	emModuleCallType m_emCallType;
	EmModuleConnection  m_emSipConnection; 
	
	TModuleTransportAddress m_emCallerIp;
	TModuleTransportAddress m_emCalleeIp;
	
	TCallAliasAddr m_emCallerAlias;
	TCallAliasAddr m_emCalleeAlias;
	
	TCallAliasAddr m_emCallerE164;
	TCallAliasAddr m_emCalleeE164;
	
	s8 m_achLocalProductId[MAX_LEN_PRODUCT_ID + 1];
	s8 m_achLocalVersionId[MAX_LEN_VERSION_ID + 1];
	
	s8 m_achPeerProductId[MAX_LEN_PRODUCT_ID + 1];
	s8 m_achPeerVersionId[MAX_LEN_VERSION_ID + 1];
	
	EmModuleVendorID m_emVendorId;
	EmModuleVendorID m_emPeerVendorId;
	EmCallModeType   m_emCallMode;			// ��������:JOIN|CREATE|INVITE

	BOOL32 m_bIsInterworking;				//added by sna for interworking [20140214]
	//////////////////////////////////////////////////////////////////////////
	//���½����ڴ�������
	BOOL32				m_bCreateConf;		//�Ƿ��Ǵ�������
	u8					m_byTerNum;			//�����ն˸���
	TerminalAddress		m_atList[MAX_TERMINAL_NUM];	//�����ն��б�
	TMdlConfInfo		m_tConfInfo;			//������Ϣ
	
	BOOL32				m_bNatCall;	//�����Ƿ��nat

	TModuleEncryptKey	m_tStreamKey;	//��m_tStreamKey.m_emEncryptType=emMdlEncryptTypeNone ��ʾ����������
	u32					m_dwSendRoundTripTime;	//������ⷢ�ͳ�ʱ���룩
	u32					m_dwRecvRoundTripTime;	//���������ճ�ʱ���룩
	u32					m_dwStaticNATAddr;		//��̬NAT��ַ
	
	BOOL32              m_bStrongAut;           //�����Ƿ����ǿ��֤
	
	s8 m_achPassword[MAX_PASSWORD_LEN+1]; //��֤����
	s8 m_achUsername[MAX_LEN_CALL_ALIAS+1];	//��֤�û���
	s8 m_achDomainName[MAX_DOMAINNAME_LEN+1];	//����

#ifdef _ENABLE_QUANTUM_PROJECT_
	BOOL32                  m_bSignalEncrypt;	//���������Ƿ����
	TQtCallParam            m_tQtCallParam;		//���Ӻ��в���
	EmQtRetReason           m_emQtRetReason;
#endif
    
	u8 m_byNonStdHdrNum;	//�Ǳ�sip��ͷ����
	TSipNstHeader m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];	 //�Ǳ�sip��ͷ
	
public:
	tagModuleCallInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emVendorId = emModule_vendor_KEDA;
		m_emPeerVendorId = emModule_vendor_KEDA;
		m_emEndpointType = emModuleEndpointMT;
		m_emPeerEndpointType = emModuleEndpointMT;
		m_emCallType = emModuleIPCall;
		m_emSipConnection    = emModuleUdpConnection;
		memset( m_achLocalProductId , 0 , sizeof(m_achLocalProductId) );
		memset( m_achLocalVersionId , 0 , sizeof(m_achLocalVersionId) );
		memset( m_achPeerProductId , 0 , sizeof(m_achPeerProductId) );
		memset( m_achPeerVersionId , 0 , sizeof(m_achPeerVersionId) );
		memcpy( m_achLocalProductId, "kedacom", sizeof("kedacom") );
		memcpy( m_achLocalVersionId, "unknown", sizeof("unknown") );
		memset( m_abyCallId , 0 , sizeof(m_abyCallId) );
		memset( m_achPassword, 0, sizeof( m_achPassword) );
		memset( m_achUsername, 0, sizeof(m_achUsername) );
		memset( m_achDomainName, 0, sizeof(m_achDomainName) );
		m_wBitrate = 768;
		m_emCallMode = emModeCreate;
		m_bCreateConf = FALSE;
		m_byTerNum = 0;
		m_tConfInfo.Clear();
		m_bNatCall = FALSE;
		m_bIsInterworking = FALSE;
		for ( u8 i = 0; i < MAX_TERMINAL_NUM; i++ )
		{
			m_atList[i].Clear();
		}
		m_tStreamKey.Clear();
		m_dwSendRoundTripTime = 0;
		m_dwRecvRoundTripTime = 0;
		m_dwStaticNATAddr	  = 0;
        m_byNonStdHdrNum      = 0;
		for ( u8 j = 0; j < MAX_SIP_NONSTD_HEADER_NUM; j++ )
		{
			m_atNonStdHdr[j].Clear();
		}

#ifdef _ENABLE_QUANTUM_PROJECT_
		m_bSignalEncrypt = FALSE;
		MEMSET_CAST(&m_tQtCallParam,0 ,sizeof(m_tQtCallParam));
		m_tQtCallParam.m_emKeyFrequency = EmQtFrequencyEveryConf;
		m_tQtCallParam.m_bCallEncryption = FALSE;
#endif

	}
}TModuleCallInfo;

//��Ƶ������
struct TVideoDescript
{
	EmModuleVideoResolution m_emRes; //�ֱ���
	u8                m_byMPI;       //֡�� 1=30 2=15 ...? Where is the definition about the MPI values?
	u16               m_wMaxBitrate; //֧���������
public:
	TVideoDescript()
	{
		Clear();
	}

	void Clear()
	{
		m_emRes			= emModuleVResEnd;
		m_byMPI			= MODULE_VIDEO_DEFAULT_MPI;
		m_wMaxBitrate	= MODULE_VIDEO_DEFAULT_BITRATE;
	}
};

//ָ����Ƶ��ʽ�����б�
struct TVideoFormatCapbility
{
	u8     m_byNum;
	u8     m_byDynamicPayload;
	EmModuleVideoFormat m_emFormat;
	EmModuleH264NALMode m_emH264NALMode; //h264��
	u32	   m_emProfile; //h264 h265��
	TVideoDescript      m_atItem[emModuleVResEnd]; //for h264 and h265, only Max Resolution enable 
	
	TVideoFormatCapbility()
	{
		Clear();
	}

	void Clear()
	{
		m_byNum				= 0;
		m_emFormat			= emModuleVEnd;
		m_byDynamicPayload	= 0;
		m_emProfile			= 0;
		m_emH264NALMode     = emModuleNALSingle;
		for (u8 i = 0; i < emModuleVResEnd; i ++)
		{
			m_atItem[i].Clear();
		}
	}
};

//��Ƶ������
struct TVideoCapbilityList
{
	u8 m_byNum;
	TVideoFormatCapbility m_atList[emModuleVEnd];
	
	HMDLAPPCHANNEL m_hAppChan;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;
	BOOL32 m_bActive;
	u8     m_byBitratePercent;
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting m_tSrtpSetting;
#endif
	
public:
	TVideoCapbilityList()
	{
		Clear();
	}

	void Clear()
	{
		m_byNum = 0;
		m_hAppChan = NULL;

		for ( u8 i=0; i<emModuleVEnd; i++ )
		{
			m_atList[i].Clear();
		}
		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_bActive = TRUE;
		m_byBitratePercent = 0;
#ifdef _KDV_SRTP_SUPPORT_
		m_tSrtpSetting.Clear();
#endif
	}
};

//��Ƶ������
struct TAudioDescript
{
	EmModuleAudioFormat m_emFormat;
	u8           m_byPackTime;
	u8           m_byDynamicPayload;

	
	EmModuleAudioSampleFreq m_emSampleFreq;
	//AAC ��
	EmModuleAudioChnlCfg	m_emChnlCfg;

	//g7231��
	u8				m_byMaxFrameNum;		//��������֡��
	BOOL32			m_bSilenceSuppression;	//�Ƿ�������
	
	//g7221��
	u16				m_wBitRate;

	//TelephoneEvent ��
	//this array must use '0' or '1' to fill when you want to use 
	//EventEncoding default value is 0-15
	s8 m_achEventEncoding[TelephoneEventCap_ENCODING_LEN];

public: 
	TAudioDescript()
	{
		Clear();
	}

	void Clear()
	{
		m_emFormat				= emModuleAEnd;
		m_byPackTime			= MODULE_AUDIO_DEFAULT_TIMEPERCAPTURE;
		m_byDynamicPayload		= MODULE_AUDIO_DEFAULT_PAYLOADTYPE;
		m_emChnlCfg				= emModuleChnl1;
		m_emSampleFreq			= emModuleFs32000;
		m_byMaxFrameNum			= MODULE_AUDIO_DEFAULT_MAXFRAME;
		m_bSilenceSuppression	= FALSE;
		m_wBitRate			= 0;
		memset(m_achEventEncoding,0,sizeof(m_achEventEncoding));
	}
};

//��Ƶ������
struct TAudioCapbilityList
{
	u8 m_byNum;
	TAudioDescript m_atItem[emModuleAEnd];

	HMDLAPPCHANNEL m_hAppChan;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;
	BOOL32  m_bActive;

	//extmap��չ��audio-level��
	EmModuleDirection m_emAudLvlDirect;
	u8 m_byAudLvlId;
	BOOL32 m_bAudLvlVadOn;
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting m_tSrtpSetting;
#endif
	
public:
	TAudioCapbilityList()
	{
		Clear();
	}

	void Clear()
	{
		m_hAppChan	= NULL;
		m_byNum		= 0;
		
		for ( u8 i=0; i<emModuleAEnd; i++ )
		{
			m_atItem[i].Clear();
		}

		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_bActive	= TRUE;
		m_emAudLvlDirect = emModule_Direction_Begin;
		m_byAudLvlId = 0;
		m_bAudLvlVadOn = TRUE;
#ifdef _KDV_SRTP_SUPPORT_
		m_tSrtpSetting.Clear();
#endif
	}
};

typedef enum 
{
	emDualAttribueBegin = 0,
	emDualSendOnly = 1,
	emDualSendRecv = 2,
	emDualSendOnlyAndRecvOnly = 3,
}EmDualAttribue;

typedef struct tagMdlCallCap
{
	u16 m_wSndVidNum;
	u16 m_wRcvVidNum;
	u16 m_wSndAudNum;
	u16 m_wRcvAudNum;
	
	TVideoCapbilityList m_atSndVidCap[MAX_VIDEO_NUM];
	TVideoCapbilityList m_atRcvVidCap[MAX_VIDEO_NUM];
	TAudioCapbilityList m_atSndAudCap[MAX_AUDIO_NUM];
	TAudioCapbilityList m_atRcvAudCap[MAX_AUDIO_NUM];
	
	void Clear()
	{	
		u8 i = 0;
		m_wSndAudNum = 0;
		m_wRcvAudNum = 0;
		m_wSndVidNum = 0;
		m_wRcvVidNum = 0;
		for (i = 0; i < MAX_VIDEO_NUM; i++)
		{
			m_atSndVidCap[i].Clear();
			m_atRcvVidCap[i].Clear();
		}
		for (i = 0; i < MAX_AUDIO_NUM; i++)
		{
			m_atSndAudCap[i].Clear();
			m_atRcvAudCap[i].Clear();
		}
	}

	tagMdlCallCap()
	{
		Clear();
	}
	
}TMdlCallCap;

typedef struct tagDualCapList
{
	EmDualAttribue m_emDualAttribue;
	TMdlCallCap m_tCallCap;
	
	void Clear()
	{
		m_emDualAttribue = emDualSendOnlyAndRecvOnly;
		m_tCallCap.Clear();
	}
	tagDualCapList()
	{
		Clear();
	}
}TDualCapList;


typedef enum 
{
	emFECCCapReceive	=1,
	emFECCCapTransmit	=2,
	emFECCCapReceiveAndTransmit=3
} cmFECCCapDirection;

typedef enum 
{
	emMMcuCapReceive	=1,
	emMMcuCapTransmit	=2,
	emMMcuCapReceiveAndTransmit=3
} cmMMcuCapDirection;

typedef struct tagFeccCapbility
{	
	TModuleTransportAddress m_tSendAddress;	//FECC���͵�ַ
	TModuleTransportAddress m_tRecvAddress;	//FECC���յ�ַ
	cmFECCCapDirection		m_byDirection;
	u16						m_wSampleRate;
	u8						m_byDynamicPayload;
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting    m_tSrtpSetting; 
#endif

	void Clear()
	{
		m_tSendAddress.Clear();
		m_tRecvAddress.Clear();
		m_wSampleRate		= 0;
		m_byDynamicPayload	= MEDIA_TYPE_H224	;
		m_byDirection		= emFECCCapReceiveAndTransmit;

#ifdef _KDV_SRTP_SUPPORT_
		m_tSrtpSetting.Clear();
#endif
	}
	
	tagFeccCapbility()
	{
		Clear();
	}
	
}TFeccCapbility;

typedef struct tagMMcuCapbility
{	
	TModuleTransportAddress m_tListenAddress;	//MMcu������ַ
	cmMMcuCapDirection		m_byDirection;
	u8						m_byDynamicPayload;

	void Clear()
	{
		m_tListenAddress.Clear();
		m_byDynamicPayload	=  MEDIA_TYPE_MMCU;
		m_byDirection		= emMMcuCapReceiveAndTransmit;
		m_tListenAddress.m_dwIp = 0;
		m_tListenAddress.m_wPort = 3337;
	}

	tagMMcuCapbility()
	{
		Clear();
	}

}TMMcuCapbility;


typedef struct tagCallCapbility
{
	u16 m_wAudioNum;
	TAudioCapbilityList m_atAudioCapList[MAX_AUDIO_NUM];     //ÿһ��ͨ��
	u16 m_wVideoNum;
	TVideoCapbilityList m_atVideoCapList[MAX_VIDEO_NUM];

	//////////////////////////////////////////////////////////////////////////
	//Jacky Invite with BFCP
	//	The following variants will be used only for H.323 call
	u16 m_wDualVideoNum;
	TVideoCapbilityList m_tDualCapList;						//��Ƶ˫��������Ĭ��Ϊ1·
	//////////////////////////////////////////////////////////////////////////

	tagCallCapbility()
	{
		Clear();
	}

	void Clear()
	{
		u8 i			= 0;
		m_wAudioNum		= 0;
		m_wVideoNum		= 0;
		m_wDualVideoNum = 1;

		for ( i=0; i<MAX_AUDIO_NUM; i++)
		{
			m_atAudioCapList[i].Clear();
		}

		for ( i=0; i<MAX_VIDEO_NUM; i++)
		{
			m_atVideoCapList[i].Clear();
		}

		m_tDualCapList.Clear();
	}

}TCallCapbility;

//defined in rfc4145
typedef enum 
{
	emSetupBegin = 0,
	emActive   = 1,	//The endpoint will initiate an outgoing connection.
	emPassive  = 2,	//The endpoint will accept an incoming connection.
	emActpass  = 3,	//The endpoint is willing to accept an incoming connection or to initiate an outgoing connection.
	emHoldconn = 4,	//The endpoint does not want the connection to be established for the time being.
}EmSetupAttr;

//defined in rfc4145
typedef enum 
{
	emConnectionBegin = 0,
	emNew = 1,
	emExisting = 2,
}EmConnectionAttr;

//defined in rfc4583
typedef enum 
{
	emFloorcontrolBegin = 0,
	emClientOnly = 1,	//The answerer will act as a floor control client. Consequently, the offerer will act as a floor control server.
	emServerOnly = 2,	//The answerer will act as a floor control server. Consequently, the offerer will act as a floor control client.
	emClientServer = 3,	//The answerer will act both as a floor control client and as a floor control server. Consequently, the offerer will also act
						//both as a floor control client and as a floor control server.
}EmFloorcontrolAttr;

typedef enum
{
	emBfcpSdpBegin = 0,
	emTcpBfcp,
	emTcpTlsBfcp,
	emUdpBfcp,
	emUdpTlsBfcp,
}EmBfcpSdpAttr;

typedef struct tagBfcpFloor
{
	u16 m_wFloorId;
	s32 m_nLabelNum;
	s32 m_anLabelList[MAX_MEDIA_NUM_PER_FLOOR];

	void Clear()
	{
		m_wFloorId = 0;
		m_nLabelNum = 0;
		for (s32 i = 0; i < MAX_MEDIA_NUM_PER_FLOOR; i++)
		{
			m_anLabelList[i] = 0;
		}
	}
	tagBfcpFloor()
	{
		Clear();
	}
}TBfcpFloor;

typedef struct tagBfcpCapSet
{	
	u16 m_wPort;	//BFCP���ն˶˿�
	
	EmFloorcontrolAttr m_emFloorcontrolAttr;	//BFCPʵ�壨Floorcontrol���ԣ�
	EmSetupAttr m_emSetupAttr;	//BFCP������������Setup���ԣ�
	EmConnectionAttr m_emConnectionAttr;	//�������ԣ�Ĭ��new��
	EmBfcpSdpAttr m_emBfcpSdpAttr;	//TCPBFCP��TCPTLSBFCP��UDPBFCP��UDPTLSBFCP

	u32 m_dwConfId;	//����ID
	u16 m_wUserId;	//�û�ID
	s32 m_nFloorNum;	//Floor Number
	TBfcpFloor m_atBfcpFloor[MAX_FLOOR_NUM];	//Floor

	void Clear()
	{
		m_wPort = 0;

		m_emFloorcontrolAttr = emFloorcontrolBegin;
		m_emSetupAttr = emSetupBegin;
		m_emConnectionAttr = emConnectionBegin;
		m_emBfcpSdpAttr = emUdpBfcp;

		m_dwConfId = 0;
		m_wUserId = 0;
		m_nFloorNum = 0;

		for (s32 i = 0; i < MAX_FLOOR_NUM; i++)
		{
			m_atBfcpFloor[i].Clear();
		}
	}
	tagBfcpCapSet()
	{
		Clear();
	}
}TBfcpCapSet;


//H323 Annex Q
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
enum emModulefeccAction
{
	emModuleactionInvalid				= 0,  
	emModuleactionStart					= 0x01,  //��ʼ
	emModuleactionContinue				= 0x02,  //����
	emModuleactionStop					= 0x03,  //ֹͣ
	emModuleactionSelectVideoSource		= 0x04,  //ѡ����ƵԴ
	emModuleactionVideoSourceSwitched	= 0x05,  //�л���ƵԴ
	emModuleactionStoreAsPreset			= 0x06,  //�洢Ԥ��λ
	emModuleactionActivatePreset		= 0x07,  //�ָ���Ԥ��λ
	emModuleactionAutoFocus				= 0x11,  //�Զ�����
};

//PTFZ codes, parameters for action Start, continue and stop.
enum emModulefeccPTFZRequest
{
	emModulerequestInvalid				= 0,
	emModulerequestPanLeft				= 0x80,	//�����ƶ�
	emModulerequestPanRight				= 0xc0,	//�����ƶ�
	emModulerequestTiltUp				= 0x30,	//�����ƶ�
	emModulerequestTiltDown				= 0x20,	//�����ƶ�
	emModulerequestFocusIn				= 0x03,	//����
	emModulerequestFocusOut				= 0x02,	//Զ��
	
	emModulerequestZoomIn				= 0x0c,	//��Ұ��С
	emModulerequestZoomOut				= 0x08,	//��Ұ���

	emModulerequestBrightnessUp			= 0x01,	//���ȼ�(nonstandard)
	emModulerequestBrightnessDown		= 0x04  //���ȼ�(nonstandard)
};

////CME message type
enum emModuleCMEMsgType
{
	emModuleCMEInvalid,				//��Ч									
	emModuleCMEClientListInfo,		//�ͻ��б���Ϣ֪ͨ
	emModuleCMEClientListCommond,	//����ͻ��б�	
	emModuleCMEExtraCapInfo,		//����������Ϣ֪ͨ			
	emModuleCMEExtraCapCommond,		//�����������			
};

// H323 Annex Q
//CME��Ϣ�Լ�������Ϣ������һ���ṹ����
//if m_bIsCMEMsg is true,only use m_byCMEMsgType, otherwise use others
typedef struct tagMdlFeccStruct
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
	tagMdlFeccStruct()
	{
		m_bIsCMEMsg		= FALSE;
		m_byCMEMsgType	= emModuleCMEInvalid;
		m_byAction		= emModuleactionInvalid;
		arguments.m_byRequest = emModulerequestInvalid;	
		m_byTimeout		= 0;
	}
	
}TMdlFeccStruct, *PTMdlFeccStruct;

//�˿ڸ���ʱ��Ҫ����streamId��
#define FECC_ENDPOINTID_LEN 32
typedef struct tagMdlFeccStreamIdInfo
{
	s8  aszEndPointId[FECC_ENDPOINTID_LEN];	//�ն˵�id, ��ǰ��֧��e164��
	u32 IdLen;				//�ն�id�ĳ���
	u32 StreamId;			//��id
	BOOL32 bSendChan;		//�Ƿ���Զң����ͨ��

public:
	tagMdlFeccStreamIdInfo()
	{
		memset(aszEndPointId, 0, FECC_ENDPOINTID_LEN);
	}
}TMdlFeccStreamIdInfo;

//��Ƶͨ������
typedef struct tagTModuleVideoChanParam
{
	EmModuleVideoFormat     m_emVideoFormat;
	EmModuleVideoResolution m_emVideoResolution;
	u16                m_wChanMaxBitrate;      // ��λ Kbps
	u8                 m_byPayload;			   //��̬�غ�
	TModuleEncryptKey  m_tKey;				   //��tKey.byLen=0 ��ʾ������
	u8                 m_byFrameRate;          //֡��
public:
	tagTModuleVideoChanParam()
	{ 
		Clear();
	}	
	void Clear()
	{
		m_emVideoFormat		= emModuleVEnd;
		m_emVideoResolution = emModuleVResEnd;
		m_wChanMaxBitrate   = 0;
		m_byPayload         = MODULE_VIDEO_DEFAULT_PAYLOADTYPE;
		memset( &m_tKey ,0 ,sizeof(m_tKey) );
		m_byFrameRate		= MODULE_VIDEO_DEFAULT_FRAMERATE;
	}
}TModuleVideoChanParam, *PTModuleVideoChanParam;

//��Ƶͨ������ 
typedef struct tagTModuleAudioChanParam
{
	EmModuleAudioFormat   m_emAudioFormat;
	u8					  m_byPayload;     //��̬�غ�
	TModuleEncryptKey     m_tKey;          //��tKey.byLen=0 ��ʾ������
public:
	tagTModuleAudioChanParam()
	{
		Clear();
	}

	void Clear()
	{
		m_emAudioFormat = emModuleAEnd;
		m_byPayload     = 0;
		memset( &m_tKey ,0 ,sizeof(m_tKey));
	}
}TModuleAudioChanParam;

typedef struct tagModuleVideoChannelParam
{
	TModuleVideoChanParam m_tParam;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;

}TModuleVideoChannelParam;

typedef struct tagModuleAudioChannelParam
{
	TModuleVideoChannelParam m_tParam;
	TModuleTransportAddress m_tRtpAddr;
	TModuleTransportAddress m_tRtcpAddr;
	
}TModuleAudioChannelParam;

enum emChanType
{
	emModuleChanTypeBegin,
	emModuleSndAud,
	emModuleSndVid,
	emModuleRcvAud,  
	emModuleRcvVid,
};

enum emAVType
{
	emModuleTypeBegin,
	emModuleAudioType,
	emModuleVideoType,

	emModuleAudioSecondType,
	emModuleVideoSecondType,

	//data type
	emModuleH224Type,
	emModuleT120Type,
	emModuleMMcuType
};
//add by yj for conf MSG [20130726]
//���ڵ���֡��ʱ��дͨ������
//����10��ͨ��
enum emModuleChannelType
{
	emModuleChanSendAudio,
	emModuleChanSendPrimoVideo,
	emModuleChanSendSecondVideo,
	emModuleChanSendFecc,
	emModuleChanSendT120,
	
	//����ͨ��
	emModuleChanRecvAudio,
	emModuleChanRecvPrimoVideo,
	emModuleChanRecvSecondVideo,
	emModuleChanRecvFecc,
	emModuleChanRecvT120,
	
	emModuleChanTypeEnd	
};

//��Ƶ����
enum emModVideoType
{
	emModulePriomVideo = 0 ,//����Ƶ
	emModuleSecondVideo = 1//�ڶ�·��Ƶ
};

//�ն��ͺ�
enum EmModuleMtModel
{
	emModuleUnknownMtModel = 0,
	emModulePCMT  = 1 ,//�����ն�
	emModule8010      ,
	emModule8010A     ,
	emModule8010Aplus ,//8010A+
	emModule8010C     ,
	emModule8010C1    ,//8010C1
	emModuleIMT       ,
	emModule8220A     ,
	emModule8220B     ,
	emModule8220C     ,
	emModule8620A     ,
	emModuleTS6610E   ,
	emModuleTS6210    ,
	emModule8010A_2   ,
	emModule8010A_4   ,
	emModule8010A_8   ,
	emModule7210      ,
	emModule7610      ,
	emModuleTS5610    ,
	emModuleTS6610    ,
	emModule7810      ,
	emModule7910      ,
	emModule7620_A    ,
	emModule7620_B    ,
	emModule7820_A	,
	emModule7820_B	,
	emModule7920_A	,
	emModule7920_B	,
	emModuleKDV1000   ,
	emModule7921_L    ,
	emModule7921_H    ,
	emModuleH600_LB    ,
	emModuleH600_B    ,
	emModuleH600_C    ,
	emModuleH700_A    ,
	emModuleH700_B    ,
	emModuleH700_C    ,
	emModuleH900_A    ,
	emModuleH900_B    ,
	emModuleH900_C    ,
	emModuleH600_LC   ,
	emModuleH800_A    ,
	emModuleH800_B    ,
	emModuleH800_C    ,
};

// << �ļ�ϵͳ���� >>
enum EmModuleFileSys
{
	emModuleRAWFS = 1,//raw file system [ramdisk + rawblock + tffs]
	emModuleTFFS  //tffs
};

//����
enum EmModuleAction
{
    emModuleStart,
	emModuleStop,
	emModulePause,
	emModuleResume,
};

//λ��
enum EmModuleSite
{
    emModuleLocal = 0,  //����
	emModuleRemote    //Զ��
};

//����ģʽ
enum EmModuleConfMode
{
	emModuleP2PConf = 0,//��Ե����
	emModuleMCCConf = 1 //������
};

//�ն���Ƶ�˿�
enum EmModuleMtVideoPort
{
	emModuleMtVidPort1 = 0,  
	emModuleMtVidPort2    ,  
	emModuleMtVidPort3    ,  
	emModuleMtVidPort4    ,  
	emModuleMtVidPort5    ,  
	emModuleMtVidPort6    ,  
	emModuleMtVidPort7	  , 
	emModuleMtVidPort8    ,
	emModuleMtVidPort9    ,
	emModuleMtVidPort10   ,
	
	emModuleMtExternalVid,
	emModuleMtVidPortMaxCount = 40, //���֧����ƵԴ����
	emModuleMtVidInvalid = 255 
};

//�����㷨
enum EmModuleEncryptArithmetic
{
	emModuleEncryptNone = 0,
	emModuleDES         = 1,
	emModuleAES         = 2,
	emModuleEncryptAuto = 3,
	
	emModuleEncryptEnd		
};

enum EmModuleUIPosion
{
	emModuleMT = 0,
	emModuleMTC = 1
};

//��Ƶ�����״̬
typedef struct tagTModuleMtVideoCodecStatus
{
	BOOL32                m_bRuning;           //�Ƿ��ڹ���
	EmModuleVideoFormat       m_emFormat;          //��Ƶ�����ʽ
	EmModuleVideoResolution   m_emRes;             //��Ƶ�����ʽ
	u16                 m_wBitrate;          //��Ƶ��������(��λ:kbps)
	u16                 m_wAverageBitrate;   //����Ƶ��ƽ��������(��λ:kbps)
	BOOL32                m_bIsEncrypt;         //����Ƶ�����Ƿ����
	EmModuleEncryptArithmetic m_emArithmetic;	   //���ӱ���ʹ�õļ����㷨	
	
public:
	tagTModuleMtVideoCodecStatus()
	{ 
		memset ( this ,0 ,sizeof( struct tagTModuleMtVideoCodecStatus) );
	}
}TModuleMtVideoCodecStatus, *PTModuleMtVideoCodecStatus;

//�ն�״̬
typedef struct tagTModuleTerStatus
{
	EmModuleMtModel  m_emMtModel;				    //�ն��ͺ�
	EmModuleFileSys  m_emFileSys;                 //�ļ�ϵͳ����
	
	u8		m_byEncVol;					//��ǰ��������(��λ:�ȼ�)
	u8		m_byDecVol;					//��ǰ��������(��λ:�ȼ�)
	BOOL32	m_bIsMute;					//�Ƿ�����	
	BOOL32	m_bIsQuiet;					//�Ƿ���			
	BOOL32	m_bIsLoopBack;				//�Ƿ��Ի�
	BOOL32    m_bIsInMixing;                //�Ƿ�μӻ���
	BOOL32    m_bRegGkStat;			    	//GKע����	1 �ɹ� 0 ʧ��
	EmModuleAction   m_emPollStat;		//��ѯ״̬		emStart ,emPause ,emStop /��ʼ/��ͣ/ֹͣ
	EmModuleSite	 m_emCamCtrlSrc;		//��ǰ��������ͷԴ���� emLocal, emRemote
	u8		m_byLocalCamCtrlNo;			    //��ǰ���Ƶı�������ͷ��(1-6������ͷ)
	u8		m_byRemoteCamCtrlNo;			    //��ǰ���Ƶ�Զ������ͷ��(1-6������ͷ)
	u8      m_byE1UnitNum ;                   //�ն�E1ģ��ĵ�E1����
	BOOL32	m_bFECCEnalbe;				//�Ƿ�����Զң
	BOOL32    m_bLocalIsVAG;                //���صڶ�·����������Ƿ�VGA
	BOOL32    m_bPVHasVideo;                //��һ·�Ƿ�����ƵԴ
	BOOL32    m_bSVHasVideo;                //�ڶ�·�Ƿ�����ƵԴ
	//һ�²��ֲ�����ʹ��
	BOOL32	m_bIsAudioPowerTest;			//�Ƿ��ڲ�����Ƶ	
	BOOL32	m_bIsLocalImageTest;			//�Ƿ񱾵�ͼ�����
	BOOL32	m_bIsRemoteImageTest;			//�Ƿ�Զ��ͼ����� 
	//	///////����״̬///////
	BOOL32       m_bIsInConf;				//�Ƿ��ڻ�����	
	EmModuleConfMode m_emConfMode;				//����ģʽ		1 ���� 2 ���		
    BOOL32       m_bCallByGK;				//�Ƿ�ͨ��GK���� TRUE GK·�� FALSEֱ�Ӻ���
	//	
	//	///////�豸״̬///////
	BOOL32	m_bMatrixStatus;				    //���þ���״̬		(TRUE ok FALSE err)
	u8		m_byCamNum;					    //����ͷ����	(0~6)
	BOOL32	m_bCamStatus[MAX_MTCAMERA_NUM];					//����ͷ״̬ (TRUE ok FALSE err)
	EmModuleMtVideoPort m_emVideoSrc;					//��ǰ������ƵԴ(0:S����,1-6:C����)
	
	BOOL32    m_bIsEncrypt;
	//	//�������״̬
	EmModuleAudioFormat	    m_emADecFormat;	//��Ƶ�����ʽ
	EmModuleAudioFormat	    m_emAEncFormat;	//��Ƶ�����ʽ
	TModuleMtVideoCodecStatus  m_tPVEncStatus;   //����Ƶ������
	TModuleMtVideoCodecStatus  m_tSVEncStatus;   //����Ƶ������
	TModuleMtVideoCodecStatus  m_tPVDecStatus;   //����Ƶ������
	TModuleMtVideoCodecStatus  m_tSVDecStatus;   //����Ƶ������
	//	
	u16		m_wSysSleep;					//����ʱ��(0x0��ʾ������)
	//VOD states
	BOOL32	m_bIsInVOD;
	EmModuleUIPosion	m_emVodUser;
	//////����״̬///////
public:
	tagTModuleTerStatus(){ memset ( this, 0, sizeof( struct tagTModuleTerStatus) );}
}TModuleTerStatus, *PTModuleTerStatus;
//end [20130726]

enum emModuleChannelDirection
{
	emModuleChannelDirectionBegin,
	emModuleChannelSend,
	emModuleChannelRecv,
	emModuleChannelBidirectional,
};

enum EmChannelReason
{
	emModuleChannelReasonBegin,
	emModuleChannelDisconnectNormal,
	emModuleDualOffLine, 
	emModuleChannelDisconnectForce,        //����˫����˫�������ͳɹ������յ��Զ˷�200Ok������Ӧ��
	emModuleDualNotSend,	//˫��δ��Э��ջ���ͳ�ȥ����ǰ״̬����ȷ������Э��ջδ���ͣ�
	emModuleDualAudioNotSupport,  //��˫��ʱ��ֱ�ӻص�˫����Ƶʧ�ܣ�ֻ���323�����ṩ��������t300�ж���˫����Ƶ�ġ�[20141029]
};

typedef struct tagModuleChannelType
{
	emAVType m_emAVType;
	emModuleChannelDirection m_emDirection;
public:
	tagModuleChannelType()
	{
		Clear();
	}
	void Clear()
	{
		m_emAVType = emModuleTypeBegin;
		m_emDirection = emModuleChannelDirectionBegin;
	}
}TModuleChannelType;

typedef struct tagTCapSetInfo
{
	u8   m_byDynamicPayload;
	EmModuleAudioFormat m_emAudioFormat;        //��Ƶ����
	u8                  m_byPackTime;           //��Ƶ����
	EmModuleAudioChnlCfg m_emAudioChnlCfg;      //��Ƶͨ����
	EmModuleAudioSampleFreq m_emAudioSampleFreq;//��Ƶ������
	//g7231��
	u8				m_byMaxFrameNum;		    //��Ƶ��������֡��
	BOOL32			m_bSilenceSuppression;	    //��Ƶ�Ƿ�������
	
	EmModuleVideoFormat m_emVideoFormat;        //��Ƶ����
	TVideoDescript      m_atItem;               //��Ƶ����
	//EmModuleProfileMask m_emProfile;
	u32 m_emProfile;

public:
	tagTCapSetInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_byDynamicPayload = 0;
		m_emAudioFormat = emModuleAEnd;
		m_byPackTime = 0;
		m_emAudioChnlCfg = emModuleChnlCust;
		m_emAudioSampleFreq = emModuleFs96000;
		m_byMaxFrameNum = 0;
		m_bSilenceSuppression = FALSE;
		m_emVideoFormat = emModuleVEnd;
		m_emProfile = 0;
		m_atItem.Clear();
	}
}TCapSetInfo;

typedef struct tagTCapSetChanInfo
{
	TModuleTransportAddress		m_tLocalRtcpAddr;
	TModuleTransportAddress     m_tLocalRtpAddr;
	TModuleTransportAddress		m_tPeerRtcpAddr;
	TModuleTransportAddress     m_tPeerRtpAddr;
	
	u8	m_byMediaCount;
	TCapSetInfo	m_atCapSetInfo[MAX_MEDIA_CAP_NUM];
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting m_tChanSrtpSetting;
#endif

// 	u8                          m_byDynamicPayload;
// 	
// 	EmModuleAudioFormat m_emAudioFormat;        //��Ƶ����
// 	u8                  m_byPackTime;           //��Ƶ����
// 	EmModuleAudioChnlCfg m_emAudioChnlCfg;      //��Ƶͨ����
// 	EmModuleAudioSampleFreq m_emAudioSampleFreq;//��Ƶ������
// 	//g7231��
// 	u8				m_byMaxFrameNum;		    //��Ƶ��������֡��
// 	BOOL32			m_bSilenceSuppression;	    //��Ƶ�Ƿ�������
// 	
// 	EmModuleVideoFormat m_emVideoFormat;        //��Ƶ����
// 	TVideoDescript      m_atItem;               //��Ƶ����
	
public:
    tagTCapSetChanInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tLocalRtcpAddr.Clear();
		m_tLocalRtpAddr.Clear();
		m_tPeerRtcpAddr.Clear();
		m_tPeerRtpAddr.Clear();
		m_byMediaCount = 0;
		for ( s32 i =0; i < MAX_MEDIA_CAP_NUM; i++ )
		{
			m_atCapSetInfo[i].Clear();
		}
#ifdef _KDV_SRTP_SUPPORT_
		m_tChanSrtpSetting.Clear();
#endif

	}
}TCapSetChanInfo;

typedef struct tagTChanConnectedInfo
{
	HMDLCHANNEL         m_hChan;
	HMDLAPPCHANNEL      m_hAppChan;
    TModuleChannelType  m_tChanType;
    TCapSetChanInfo     m_tCapsetInfo;
	TModuleEncryptKey	m_tStreamKey;
	
	tagTChanConnectedInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_hChan = (HMDLCHANNEL)0;
		m_hAppChan = (HMDLAPPCHANNEL)0;
		m_tChanType.Clear();
		m_tCapsetInfo.Clear();
		m_tStreamKey.Clear();
	}
}TChanConnectedInfo;


typedef struct tagTChanDisConnectedInfo
{
	HMDLCHANNEL         m_hChan;
	HMDLAPPCHANNEL      m_hAppChan; 
	
	EmChannelReason     m_emReason;

    tagTChanDisConnectedInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_hChan = (HMDLCHANNEL)0;
		m_hAppChan = (HMDLAPPCHANNEL)0;
		m_emReason = emModuleChannelReasonBegin;
	}
}TChanDisConnectedInfo;


typedef struct tagRegistReq
{
	//  �ĳɶ����֧��
	TCallAliasAddr m_atH323Alias[MAX_ALIAS_NUM];
	TCallAliasAddr m_atE164[MAX_E164_NUM];
	
	s8 m_achEPID[MAX_LEN_EPID + 1];
	
	EmModuleConnection m_emConnection;	//ע���ַ����
	TModuleTransportAddress m_tLocalAddress;    //��Ҫע��ĵ�ַ
	TModuleTransportAddress m_tGKAddress;
	TModuleTransportAddress m_tRegAddress;      //sip regserver��ַ

	s32	m_nTimeToLive;      //��

	s8	m_achProductId[MAX_LEN_PRODUCT_ID + 1];
	s8	m_achVersionId[MAX_LEN_VERSION_ID + 1];
	emModuleEndpointType m_emEndpointType;
	s8	m_achUsername[MAX_USERNAME_LEN + 1];
	s8	m_achPassword[MAX_PASSWORD_LEN + 1]; //ע������
	s8	m_achDomainName[MAX_DOMAINNAME_LEN+1];	//����

	BOOL32 m_bPortReused;	//�Ƿ�˿ڸ���
#ifdef _ENABLE_QUANTUM_PROJECT_
	u32	m_dwQtID;	//���Ӽ���ע���ʶ
#endif

public:
	tagRegistReq()
	{
		Clear();
	}
	void Clear()
	{
		memset( m_atE164 , 0 , sizeof(m_atE164) );
		memset( m_atH323Alias , 0 , sizeof(m_atH323Alias) );
		memset( m_achEPID, 0, sizeof( m_achEPID) );
		memset( m_achProductId, 0, sizeof( m_achProductId) );
		memset( m_achVersionId, 0, sizeof( m_achVersionId) );
		memset( m_achUsername, 0, sizeof( m_achUsername) );
		memset( m_achPassword, 0, sizeof( m_achPassword) );
		memset( m_achDomainName, 0, sizeof( m_achDomainName) );
		m_tLocalAddress.Clear();
		m_tGKAddress.Clear();
		m_tRegAddress.Clear();
		m_nTimeToLive = MODULE_REG_DEFAULT_TIMETOLIVE;
		m_emConnection = emModuleUdpConnection;
		m_bPortReused = FALSE;
		m_emEndpointType = emModuleEndpointMT;
#ifdef _ENABLE_QUANTUM_PROJECT_
		m_dwQtID = 0;
#endif
	}
}TRegistReq;


//�ն˱�Ų���
typedef struct tagModuleTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	
	tagModuleTerminalLabel()
	{
        m_byMcuNo = 0xff;
		m_byTerNo = 0xff;		
	}

    ~tagModuleTerminalLabel()
    {
        m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
    }
	
	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

	BOOL32 isValid()
	{
		return ( m_byTerNo <= MAX_CONFMT_NUM && m_byMcuNo != 0xff );
	}

	BOOL32 operator == (const tagModuleTerminalLabel& tTerLabel)
	{
        return !memcmp(this, (void*)&tTerLabel, sizeof(tTerLabel));
	}

}TMDLTERLABEL,*PMDLTTERLABEL;


//�ն���Ϣ(�����)
typedef struct tagModuleTerminalInfo
{
	u8 m_byMcuNo;   
	u8 m_byTerNo;
	u8 m_byConfNo;   //�������
	s8 m_achTerminalId[MAX_TERMINALID_LEN+1];    //TerminalID
	BOOL32 m_bIsChair;   //�Ƿ�����ϯ
	BOOL32 m_bIsFloor;   //�Ƿ��Ƿ�����

	BOOL32 m_bLastPack;  // �Ƿ������һ��
	BOOL32 m_bOnline;    // �Ƿ�����

	TMDLTERLABEL m_tTerYouAreView;    //����ѡ��˭
	u32 m_adwSeenByOtherListMask[SEEN_BY_OTHERLIST_MASK_NUM];   //6��int��ʾ192��λ������ʾ192���նˣ�˭ѡ��������ն�

	tagModuleTerminalInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byConfNo = 0xff;
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
		memset( m_achTerminalId, 0, sizeof(m_achTerminalId) );
		m_bIsChair = FALSE;
		m_bIsFloor = FALSE;

		m_bLastPack = FALSE;
		m_bOnline   = FALSE;
		m_tTerYouAreView.Clear();
		
		memset( m_adwSeenByOtherListMask, 0, sizeof(m_adwSeenByOtherListMask) );
	}

	void AddSeenByOtherList( u8 terNo )
	{
		if( terNo >= 192 )
			return;

		u8 i = terNo/(sizeof(u32)*8);
		u8 j = terNo%(sizeof(u32)*8);
		
		u32 mask = 0x00000001;
		mask <<= j;
		
		m_adwSeenByOtherListMask[i] |= mask;
	}

	void DelSeenByOtherList( u8 terNo )
	{
		if( terNo >= 192 )
			return;

		u8 i = terNo/(sizeof(u32)*8);
		u8 j = terNo%(sizeof(u32)*8);

		u32 mask = 0x00000001;
		mask <<= j;

		m_adwSeenByOtherListMask[i] &= ~mask;
	}

	BOOL32 IsSeenByOtherListEmpty( )
	{
		u32 temp[SEEN_BY_OTHERLIST_MASK_NUM];
		memset( temp, 0, sizeof(temp) );
		return !memcmp( temp, m_adwSeenByOtherListMask, sizeof(temp) );
	}

	void ResetSeenByOtherList( )
	{
		memset( m_adwSeenByOtherListMask, 0, sizeof(m_adwSeenByOtherListMask) );
	}

	u8 GetSeenByOtherList( u8* list )  //�������������192��u8
	{ 
		u8 count = 0;

		for( u8 i = 0; i < SEEN_BY_OTHERLIST_MASK_NUM; i++ )
		{
			if( m_adwSeenByOtherListMask[i] != 0 )
			{
				for( u8 j = 0; j < sizeof(u32)*8; j++ )
				{
					u32 mask = 0x00000001;
					mask <<= j;

					if( m_adwSeenByOtherListMask[i] & mask )
					{
						list[count++] = (u8)(sizeof(u32)*8*i + j);
					}
				}
			}
		}
		return count;
	}

}TMDLTERMINALINFO,*PMDLTERMINALINFO;


enum EmModuleOperateType
{
	emModuleOperateType_NULL,       //�ղ���
	emModuleOperateType_Add,        //���Ӳ���
	emModuleOperateType_Del,        //ɾ������
	emModuleOperateType_Update      //�޸Ĳ���
};

typedef struct tagModuleTerInfoList
{
	EmModuleOperateType	    m_emOperateType;
	u8 m_byNum;
	TMDLTERMINALINFO m_atTerInfoList[MAX_CONFMT_NUM];
	
	tagModuleTerInfoList()
	{
		Clear();
	}

	void Clear()
	{
		m_emOperateType = emModuleOperateType_Add;
		m_byNum = 0;
		memset( m_atTerInfoList, 0, sizeof(m_atTerInfoList) );
		for( u8 index = 0; index < MAX_CONFMT_NUM; index++ )
		{
			m_atTerInfoList[index].Clear();
		}
	}
}TMDLTERINFOLIST,*PTMDLTERINFOLIST;



typedef struct tagModuleTerLabelList
{
	u8 m_byNum;
	TMDLTERLABEL m_atTerLabelList[MAX_CONFMT_NUM];
	
	tagModuleTerLabelList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byNum = 0;
		//memset( m_atTerLabelList, 0, sizeof(m_atTerLabelList) );
		for( u8 index = 0; index < MAX_CONFMT_NUM; index++ )
		{
			m_atTerLabelList[index].Clear();
		}
	}
}TMDLTERLABELLIST,*PTMDLTERLABELLIST;

typedef struct tagModuleConfList
{
	u8 m_byConfNo;  //�����
	u8 m_byTerCount;
	HMDLCALL m_ahCall[MAX_CONFMT_NUM];

	tagModuleConfList()
	{
		Clear();
	}

	void Clear()
	{
		m_byConfNo = 0xff;
		m_byTerCount = 0;
		memset( m_ahCall, 0, sizeof(m_ahCall) );
	}
}TMDLCONFLIST, *PTMDLCONFLIST;



typedef struct tagModuleAlias
{
	emModuleAliasType m_emAliasType;
	u8 m_abyCallAliasAddr[MAX_LEN_CALL_ALIAS + 1];

	tagModuleAlias()
	{
		Clear();
	}
	void Clear()
	{
		m_emAliasType = emModuleType_aliastype;
		memset( m_abyCallAliasAddr, 0, sizeof(m_abyCallAliasAddr) );
	}
}TModuleAlias;

typedef struct tagModuleTerminal
{
	u32 m_dwIp;
	TModuleAlias m_atAlias[2];
	emModuleEndpointType m_emTerminalType;

	tagModuleTerminal()
	{
		Clear();
	}
	
	void Clear()
	{
		memset( m_atAlias, 0, sizeof(m_atAlias) );
		m_emTerminalType = emModuletypeBegin;
		m_dwIp = 0;
	}
}TModuleTerminal;

typedef struct tagModuleMtOnlineList
{
	u16 m_wListNum;
	TModuleTerminal m_atTerminal[MAX_ONLINE_LIST_NUM];
	BOOL32 m_bIsEnd;

	tagModuleMtOnlineList()
	{
		Clear();
	}

	void Clear()
	{
		m_wListNum = 0;
		memset( m_atTerminal, 0, sizeof(m_atTerminal) );
		m_bIsEnd = FALSE;
	}
}TModuleMtOnlineList;

typedef struct tagModuleMcuOnlineList
{
	u16 m_wAliasNum;
	TModuleAlias m_atAlias[MAX_ALIAS_NUM];
	u32 m_dwIp;
	BOOL32 m_bIsEnd;

	tagModuleMcuOnlineList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof(m_atAlias) );
		m_bIsEnd = FALSE;
		m_dwIp = 0;
	}
}TModuleMcuOnlineList;



//ע����
enum EmRegResult
{
	emModuleRegResultBegin = 0,
	emModuleRegResultReg,
	emModuleRegResultUnReg,
};

enum EmPARegFailedReason
{
	emPALocalNormalUnreg = 0,
	emPAInvalidUserNameAndPassword,
	emPARegistrarUnReachable,
	emPAInvalidAlias,
	emPAUnknownReason,
	emPARegisterFailed,
	emPARegisterNameDup,
	emPAUnRegistSuccess,
};

enum emModuleRasReason
{
	emModuleRasGKUnReachable,
	emModuleRasInvalidAlias,
	emModuleRasInvalidCallSignalAddress,
	emModuleRasInvalidTerminalType,
	emModuleRasFullRegistrationRequired,
	emModuleRasInvalidTerminalAliases,
	emModuleRasDuplicateAlias,
	emModuleRasUnknownReason
};

enum EmModuleGetGKInfoType
{
	emModuleGetGKInfoType_MT = 0,
	emModuleGetGKInfoType_MCU,
	emModuleGetGKInfoType_ALL
};

//��ӡ��ģ��
enum emModuleType 
{
	emModuleNon = 0,
	emModuleService,
	emModuleStackin,
	emModuleStackout,
	emModuleCapSet,
	emModule,
	emModuleAll,
	emModuleAllExceptCapSet,
};

enum emCallBy
{
	emModuleCallByNum = 0,
	emModuleCallByName,
};

//��־������
#define LOG_EXP			        (s32)0		//�쳣
#define LOG_IMT			        (s32)1		//��Ҫ��־
#define LOG_DEBUG		        (s32)2		//һ��������Ϣ
#define LOG_ALL                 (s32)3      //���е�����Ϣ 
#define LOG_CONF                (s32)4      //���������Ϣ����ء��ؼ�֡�ȣ� 

//int����ipת�����ַ���
#define IP2CHAR(ip)  ((u8 *)&(ip))[0], \
				     ((u8 *)&(ip))[1], \
					 ((u8 *)&(ip))[2], \
					 ((u8 *)&(ip))[3]


#endif



