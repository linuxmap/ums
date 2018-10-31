#ifndef _SIPCOMMON_H
#define _SIPCOMMON_H

#include "kdvcommon.h"
#ifdef _ENABLE_QUANTUM_PROJECT_
#include "qtinterface.h"
#endif
#define LEN_MAXMT_NUM   				(u16)192				//每个会议中的最大呼叫数
#define LEN_USERNAME    				(u16)64			    	//用户名长度
#define LEN_PASSWORD					(u16)16					//密码长度
#define LEN_DOMAINNAME    				(u16)64			    	//域名长度
#define LEN_ENCKEY_MAX					(u16)64					//(1-65535) 
#define SIP_CHAN_SPAN					10
#define SESSION_NAME_LEN				64
#define SESSION_ID_LEN					64
#define SESSION_USERNAME_LEN			64
#define SESSION_VERSION_LEN				64
#define SESSION_INFO_LEN				128
#define MAX_LEN_SESSION_DESCRIPTION		1024*10
#define MAX_LEN_LANGUAGE_HEADER			32
#define MAX_LEN_ENCODE_TYPE_HEADER		32
#define MAX_LEN_HEADER_NAME				64
#define MAX_NUM_TRANC_PERCALL			64
#define MAX_NUM_CALLID					128
#define MAX_NUM_CONTACT_ADDR			5
#define MAX_NUM_REGCLIENT				128
#define MAX_NUM_REGNAME_SIZE			64
#define MAX_NUM_CHAN					20
#define MAX_XML_LEN						65536
#define DEFAULT_BUFF_LEN				1024
#define MAX_AAC_CAP_NUM					2
#define MAX_SIP_REG_INFO_NUM			2
#define MAX_FLOOR_NUM					5
#define MAX_MEDIA_NUM_PER_FLOOR			5
#define MAX_TERMINAL_NUM				32
#define MAX_SIP_REG_INFO_NUM_UMS		3
#define MAX_SIP_REG_INFO_NUM_CNS		20
#define SIP_CALL_ID_SIZE				128
#define MAX_NUM_REGNAME_SIZE_CNS		2
#define MAX_SIP_CONF_ID_LEN				16
#define MAX_SIP_CONF_NAME_LEN			96
#define MAX_SIP_CONF_E164_LEN			16
#define MAX_SIP_PASSWORD_LEN			32
#define MAX_SIP_TERMINAL_NUM			32
#define MAX_SIP_CONF_AUDMIX_NUM_TP		4			//最大混音参与数量
#define SIP_INVALID_INDEX_TP			0xFFFF

#define SIP_ADPT_INVALID_ARRAY_INDEX	-1

#define MAX_SIP_ENCRYPT_KEY_LEN			(u8)128
#define MAX_SDP_ATTR_NAME_LEN           50
#define MAX_SDP_ATTR_VALUE_LEN          300
#define MAX_SIP_NONSTD_HEADER_NUM       10
#define MAX_SIP_ATTR_NUM                10
#define MAX_HOST_LEN                    300

#define DEFAULT_TLS_CA_NAME             "tls-cacert.pem"
#define DEFAULT_TLS_CERT_NAME           "tls-cert.pem"
#define DEFAULT_TLS_KEY_NAME            "tls-key.pem"

#ifdef _ENABLE_QUANTUM_PROJECT_
#define AES_ENCRYPT_BYTENUM    (s32)16// AES 加密为16字节对齐
#define QUANTUM_HDR_MAGIC   0xFFDEFFDF
#define QT_KEY_LEN_16	16
#endif
#define KDV_PORTRANGE_DEFAULT_START		15000
#define KDV_PORTRANGE_DEFAULT_FINISH	65535
/*
enum  PayloadType 
{
	emPayloadTypeBegin	= 0,
	//音频格式
	emAudioTypeBegin		= 1,
	emG711a					= 2,
	emG711u					= 3,
	emG722					= 4,
	emG7231					= 5,
	emG728					= 6,
	emG729					= 7,
	emMp3					= 8,  
	emG723					= 9,
	emG7221					= 10,
	emMpegaaclc				= 11,
	emMpegaacld				= 12,
	emG719					= 13,
	emAudioTypeEnd			= 49,
		
	//视频格式
	emVideoTypeBegin		= 50,	
	emH261					= 51,
	emH263					= 52,
	emH263plus				= 53,
	emH264					= 54,
	emH262					= 55,
	emMpeg4					= 56,
	emH265					= 57,
	emVideoTypeEnd			= 99,

	emDataTypeBegin			= 100,	
	emT120					= 101,
	emH224					= 102,
	emDataTypeEnd		= 149,    //changed

	emPayloadTypeEnd		= 255
};
*/

/*
//分辨率
//sipadapter目前支持的有效分辨率如下（从高到低顺序）
//emHD1080、emUXGA、emSXGA、em1280x800、em1366x768、emHD720、emXGA、emSVGA、emCIF4、emSIF4、emVGA、emCIF、emSIF、emQCIF、emSQCIF
typedef enum 
{
	emResolutionBegin	= 0,
	emSQCIF				= 1,
	emQCIF				= 2,
	emCIF				= 3,
	emCIF2				= 4,
	emCIF4				= 5,
	emCIF16				= 6,
		
	emSIF				= 7,
	emSIF4				= 8,
	emVGA				= 9,
	emSVGA				= 10,
	emXGA				= 11,

	emW4CIF				= 12,	//1024*576
	emHD720				= 13,	//1280*720
	em1280x768			= 14,	//1280*768
	em1366x768			= 15,	//1366*768
	em1280x800			= 16,	//1280*800
	emSXGA				= 17,   //1280*1024
	emUXGA				= 18,   //1600*1200
	emHD1080				= 19,	//1920*1080
	emAUTO				= 20,

	//Resolutions supported by H.265, added by Jacky according to T-REC-H.265-201304-I!!PDF-E
	emResolution2Kx1K,				// 2048 1024  2 097 152  - - - - - 31.8 63.7 
	emResolution2Kx1080,			// 2048 1080  2 228 224  - - - - - 30.0 60.0 
	emResolution4XGA,				// 2048 1536  3 145 728  - - - - - -  - 
	emResolution16VGA,				// 2560 1920  4 915 200  - - - - - -  - 
	emResolution3616x1536,			// (2.35:1)  3616  1536  5 603 328  - - - - - -  - 
	emResolution3672x1536,			// (2.39:1)  3680  1536  5 701 632  - - - - - -  - 
	emResolution3840x2160,			// (4*HD)  3840  2160  8 355 840 - - - - - -  - 
	emResolution4Kx2K,				// 4096 2048  8 388 608  - - - - - -  - 
	emResolution4096x2160,			// 4096 2160  8 912 896  - - - - - -  - 
	emResolution4096x2304,			// (16:9)  4096  2304  9 437 184  - - - - - -  - 
	emResolution7680x4320,			// 7680 4320  33 423 360  - - - - - -  - 
	emResolution8192x4096,			// 8192 4096  33 554 432 - - - - - -  - 
	emResolution8192x4320,			// 8192 4320  35 651 584 - - - - - -  - 
	emResolutionEnd		= 99
}emResolution;
*/

enum EmSipLogFilter
{
	emSipLogTelnet = 0x01,
	emSipLogStdout = 0x02,
	emSipLogAll = emSipLogTelnet | emSipLogStdout,
};

typedef struct PROTO_API tagTSipPollInfoTP
{
	BOOL32 m_bIsPoll;
	u16  m_wPollExpire;
	
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipPollInfoTP) );
	}
	tagTSipPollInfoTP()
	{
		Clear();
	}
}TSipPollInfoTP;

typedef struct PROTO_API tagTSipConfAuxMixInfoTP
{
	BOOL32 m_bStart;
	u16	m_wConfID;
	u16 m_wSpeakerIndex;					//下面数组的索引
	u16	m_awList[MAX_SIP_CONF_AUDMIX_NUM_TP];	//混音ID
	
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipConfAuxMixInfoTP) );
		m_wConfID = SIP_INVALID_INDEX_TP;
		m_bStart = FALSE;
	}
	tagTSipConfAuxMixInfoTP()
	{
		Clear();
	}
}TSipConfAuxMixInfoTP;

//基本会议信息
typedef struct PROTO_API tagTSipConfInfo
{
	s8	 m_achConfId[MAX_SIP_CONF_ID_LEN + 1];			// 会议ID
	s8	 m_achConfName[MAX_SIP_CONF_NAME_LEN + 1];		// 会议名
	s8	 m_achConfNumber[MAX_SIP_CONF_E164_LEN + 1];	    // 会议号码
	s8	 m_achConfPwd[MAX_SIP_PASSWORD_LEN + 1];			// 会议密码
	BOOL32 m_bNeedPassword;                             // 是否需要密码
	u16  m_wConfDuration;							    // 会议持续时间		
	PayloadType   m_emVideoFormat;				// 会议视频格式(VIDEO_H261等)
	PayloadType   m_emAudioFormat;				// 会议音频格式(AUDIO_MP3等)
	emResolution  m_emResolution;					// 会议视频分辨率(VIDEO_CIF等)
	u8 m_byProfile;									// 主流profile
	u8 m_byVidMPI;					                // 主流帧率
	BOOL32 m_bIsAutoVMP;								// 是否自动画面合成
	BOOL32 m_bIsMix;	    							// 是否混音
	PayloadType	m_emSecVideoFormat;			// 双流格式
	emResolution m_emSecVidRes;					// 双流分辨率
	u8 m_bySecProfile;								// 双流profile
	u8 m_bySecVidMPI;					                // 双流帧率
	u16 m_wCallRate;									// 呼叫速率(kbps)
	u16	m_wDualCallRate;								// 双流呼叫速率(kbps)
	TSipPollInfoTP  m_tPollInfo;
	TSipConfAuxMixInfoTP m_tConfAudMixInfo;
	
public:
	tagTSipConfInfo()
	{ 
		Clear();	
	}
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipConfInfo) );
		m_tPollInfo.Clear();
		m_tConfAudMixInfo.Clear();
	}
	
}TSipConfInfo ,*PTSipConfInfo;

enum EmSipMediaType
{
	emSipMediaNone,
	emSipMediaAudio,
	emSipMediaVideo,
	emSipMediaH224,
	emSipMediaT120,
	emSipMediaBfcp,
};

typedef enum 
{
	emSendRecvBegin = 0,
	emSendOnly = 1,
	emRecvOnly = 2,
	emSendRecv = 3
}emSendRecvAttr;

//IP传输地址
typedef struct PROTO_API tagTransAddress
{
	u32 m_dwIP ;//网络序
	u16 m_wPort;//主机序
public:
	void Clear()
	{
		m_dwIP = 0;
		m_wPort = 0;
	}
	tagTransAddress()
	{
		Clear();
	}
}TIPTransAddress;

class PROTO_API CFeccMediaStream
{
public:
	CFeccMediaStream();
	
	void Clear();

	void operator = (const CFeccMediaStream& cCopyMedia);
	
	void SetMediaType( EmSipMediaType emMediaType )
	{
		m_emMediaType = emMediaType;
	}

	EmSipMediaType GetMediaType()
	{
		return m_emMediaType;
	}
    
	void SetConnectAttribute( emSendRecvAttr emConnectAttr )
	{
		m_emSendRecvAttr = emConnectAttr;
	}

	emSendRecvAttr GetConnectAttribute()
	{
		return m_emSendRecvAttr;
	}
	
	void SetLocalIp( u32 dwIp )
	{
		m_dwLocalIp = dwIp;
	}

	u32 GetLocalIp()
	{
		return m_dwLocalIp;
	}

	void SetLocalSendAddress( u16 wPort )
	{
		m_tLocalSendAddress.m_dwIP = m_dwLocalIp;
		m_tLocalSendAddress.m_wPort = wPort;
	}

	TIPTransAddress* GetLocalSendAddress()
	{
		return &m_tLocalSendAddress;
	}
	
	void SetLocalRecvAddress( u16 wPort )
	{
		m_tLocalRecvAddress.m_dwIP = m_dwLocalIp;
		m_tLocalRecvAddress.m_wPort = wPort;
	}
	
	TIPTransAddress* GetLocalRecvAddress()
	{
		return &m_tLocalRecvAddress;
	}

	void SetRemoteIp( u32 dwIp )
	{
		m_tRemotRecvAddress.m_dwIP = dwIp;
	}
	
	u32 GetRemoteIp()
	{
		return m_tRemotRecvAddress.m_dwIP;
	}

	void SetRemotePort( u16 wPort )
	{
		m_tRemotRecvAddress.m_wPort = wPort;
	}
	
	u16 GetRemotePort()
	{
		return m_tRemotRecvAddress.m_wPort;
	}

	void SetFeccSampleRate( u16 wSampleRate )
	{
		m_wSampleRate = wSampleRate;
	}
	
	u16 GetFeccSampleRate()
	{
		return m_wSampleRate;
	}

#ifdef _KDV_SRTP_SUPPORT_
	void SetSendSrtpSetting( TSrtpMediaSetting tSendSrtpSetting )
	{
		m_tSendSrtpSetting = tSendSrtpSetting;
	}

	TSrtpMediaSetting* GetSendSrtpSetting()
	{
		return &m_tSendSrtpSetting;
	}

	void SetRecvSrtpSetting( TSrtpMediaSetting tRecvSrtpSetting )
	{
		m_tRecvSrtpSetting = tRecvSrtpSetting;
	}

	TSrtpMediaSetting* GetRecvSrtpSetting()
	{
		return &m_tRecvSrtpSetting;
	}
#endif

private:
	EmSipMediaType m_emMediaType;
	emSendRecvAttr m_emSendRecvAttr;
	u32 m_dwLocalIp;
	TIPTransAddress m_tRemotRecvAddress;  //send = <LocalSend,RemotRecv>
	TIPTransAddress	m_tLocalSendAddress;
	TIPTransAddress	m_tLocalRecvAddress;
	u16 m_wSampleRate;
#ifdef _KDV_SRTP_SUPPORT_
	TSrtpMediaSetting	m_tSendSrtpSetting;
	TSrtpMediaSetting	m_tRecvSrtpSetting;
#endif
};

#ifdef _ENABLE_QUANTUM_PROJECT_
enum EmGetIpByAliasReason
{
	emGetIpByAliasSuccess,
	emGetIpByAliasRegSerUnreachable, //注册服务器不可达
	emGetIpByAliasNotExist,           //别名不存在
	emGetIpByAliasUnKnow,			  //未知原因
};

typedef struct tagSipSrcAndDstAddr
{
	u32	m_dwSrcIp;         
	u16	m_wSrcPort;  
	u32	m_dwDstIp;    
	u16	m_wDstPort; 

	void Clear()
	{
		memset(this, 0, sizeof(tagSipSrcAndDstAddr));
	}
	tagSipSrcAndDstAddr()
	{
		Clear();
	}
}TSipSrcAndDstAddr;

typedef struct tagQuantumHdr
{
	u32	m_dwMagic;
	u32	m_dwCheck;
	u32	m_dwSize;
	u16	m_wPadding;
	QTKEYHANDLE	m_hQtKey;
	u8 m_abyReserved[QT_UNIQUE_ID_MAX_LEN + 1];
}TQuantumHdr;

typedef struct tagQtEncryptInfo
{
	BOOL32 m_bUsed;
	BOOL32 m_bSegment;
	TQtCallParam	m_tQtCallParam;
	u32	m_hQtHandle;
	u16 m_wKeyLen;
	s8 m_achKey[QT_KEY_LEN_16+1];
	u8 *m_pbyInBuf;	//加解密原始数据临时缓存
	u8 *m_pbyOutBuf;	//加解密后数据缓存
	s32 m_nbufLen;	//以上缓存大小（最大值）
	u32 m_dwWritePos;	//解密数据写位置
	u32 m_dwReadPos;	//解密数据读位置

public:
	void Clear()
	{
		m_bUsed = FALSE;
		m_bSegment = FALSE;
		m_pbyInBuf		= NULL;
		m_pbyOutBuf		= NULL;
		m_nbufLen		= 0;
		m_dwReadPos		= 0;
		m_dwWritePos	= 0;
		m_wKeyLen		= 0;
		memset(m_achKey, 0, sizeof(m_achKey));
		memset(&m_tQtCallParam, 0, sizeof(TQtCallParam));
		m_hQtHandle = 0xFFFFFFFF;
		m_tQtCallParam.m_emKeyFrequency = EmQtFrequencyEveryConf;
	}

	tagQtEncryptInfo()
	{
		Clear();
	}

	~tagQtEncryptInfo()
	{
		delete[] m_pbyInBuf;
		delete[] m_pbyOutBuf;
		Clear();
	}

	void Init(s32 nSize)
	{
		m_pbyInBuf	= new u8[nSize];
		m_pbyOutBuf = new u8[nSize];
		m_nbufLen	= nSize;
	}

	void ClearContent()
	{
		m_bUsed = FALSE;
		m_bSegment = FALSE;
		memset(m_pbyInBuf, 0, m_nbufLen);
		//memset(m_pbyOutBuf, 0, m_nbufLen);
		m_dwReadPos		= 0;
		m_dwWritePos	= 0;
		memset(&m_tQtCallParam, 0, sizeof(TQtCallParam));
		m_hQtHandle = 0xFFFFFFFF;
		m_tQtCallParam.m_emKeyFrequency = EmQtFrequencyEveryConf;
	}
} TQtEncryptInfo;
#endif

#endif