#ifndef _KDVCOMMON_H
#define _KDVCOMMON_H
#include "protocolcommonpublic.h"
#include "kdvdef.h"
#include "osp.h"

#define LEN_ALIAS			(u16)64				    //����������h323-id
#define LEN_TERID			(u16)128				//�ն�������󳤶�
#define MAX_CONF_NUM		(u16)32					//��������
#define LEN_GUID			(u8)16					//GIUD����
#define LEN_1				(u16)1
#define MAX_G7221CAP_NUM    (u8)10                  //G7221��������
#define MAX_H264CAP_NUM     (u8)10                  //H.264��������
#define MAX_H265CAP_NUM     (u8)10					//H.265��������
#define LEN_DES_KEY         (u8)8                   //DES����Կ����
#define LEN_AES_KEY         (u8)16                  //AES����Կ����
#define LEN_AES256_KEY      (u8)32                  //AES����Կ����
#define IPV6_NAME_LEN		(u16)64					//IPv6��ַ������
#define ANNEXQ_DYNAMIC_PT	(u16)100				//h.281��̬�غ�
#define MAX_PRODUCTID_LEN	(u32)128				//���productID��version����
#define MAX_FILE_PATH_LEN	256                     //�ļ�����·����󳤶�
#define MAX_CERTICATE_NUM	2						//Max number of certificates for TLS

#ifdef _KDV_SRTP_SUPPORT_
#define MAX_CRYPTO_NUM 8
#define MAX_CRYPTO_KEY_LEN 100
#endif

//Э���ʹ��˵��
//CBB_FOR_TPS		�������������⻯����ʹ�õĺ꣬Ŀǰ��TNsmInfo�ṹ�����Դ˺�����

#if (!defined(RV_DEBUG)) && (!defined(RV_RELEASE))
	#define RV_RELEASE
#endif

#ifndef TRUE_
	typedef int                  BOOL;
	#define TRUE                 1
	#define FALSE                0
	#define TRUE_
#endif

#ifdef _IOS_PLATFORM_
	#define BOOL32 BOOL
#endif //_IOS_PLATFORM_

#define LEN_MTNUM_PERCONF	(u16)192				//ÿ�������е���������

//APPID ����
//Э��Ӧ�úţ�591-620�� -- kdvdef.h
// #define AID_PROTOCOL_BGN                (AID_TP_END  + 1)
// #define AID_PROTOCOL_END                (AID_PROTOCOL_BGN + 29)
#define APPID_DATANET_PINHOLE	 AID_PROTOCOL_BGN+1

// ���е�ַ����
enum CallAddrType
{
	emcat_err	= -1,
	emcat_ip	= 1, 	//IP����
	emcat_alias	= 2,   	//��������
	emcat_e164	= 3,	//E164����,sip��
};

//�ն�����
typedef enum
{
	emEndpointTypeUnknown	= 0,
	emEndpointTypeMT		= 1,
	emEndpointTypeMCU		= 2,
	emEndPointTypeRegister	= 4,   //for sip
	emEndpointTypeGK		= 8,
	emEndpointTypeCNS       = 16,
	emEndpointTypeUMS       = 32,
	emEndpointTypeGateWay	= 64, 
	emEndpointTypeVRS	    = 128, 
}emEndpointType;


// �豸���ඨ��---�ն����Ͷ���
enum EmSubMtType
{
	emMtTypeNone	= 0, //������Ҳ������
	emMtTypeMt		= 3, 
	emMtTypeMmcu	= 4, //�ϼ�MCU
	emMtTypeSmcu	= 5, //�¼�MCU
	emMtTypePhone	= 6, //�绰�ն�
	emMtTypeSatd	= 7, //�����ն�
};

//ý������
//guzh [12/14/2007] ������Χȷ��
//guzh [03/27/2008] ������ʷԭ��emAudioTypeEnd��emVideoTypeEnd�ȷ�Χ��׼ȷ������������ʹ��
//��ֱ��ʹ�� IsAudioType, IsAudioType, IsDataType�Ƚӿ�
enum  PayloadType 
{
    emPayloadTypeBegin	= 0,
    //��Ƶ��ʽ
    emAudioTypeBegin= 1,
    emG711a			= 2,
    emG711u			= 3,
    emG722			= 4,
    emG7231			= 5,
    emG728			= 6,
    emG729			= 7,
    emMp3			= 8,
    emG723			= 9,
    emG7221			= 10,	//����emG7221c
    emMpegaaclc		= 11,
    emMpegaacld		= 12,
	emOpus			= 13,	//�Ǳ�׼������payloadTypeҪ����ǰһ����ͬemMpeg4��emH262��������м�������
	emG719			= 14,	
	emTelephoneEvent= 15,
	// �������ϰ汾����
    emMpeg4			= 17,    
    emH262			= 18,

    emTypeGeneric	= 48,   // �ڲ�ʹ��
    emAudioTypeEnd	= 49,
        
    //��Ƶ��ʽ
    emVideoTypeBegin= 50,	
    emH261			= 51,
    emH263			= 52,
    emH263plus		= 53,
    emH264			= 54,
	emH265			= 57,
    emVideoGeneric	= 97,
    emVideoExtended	= 98,
    emVideoTypeEnd	= 99,
        
    //���ݸ�ʽ
    emDataTypeBegin	= 100,	
    emT120			= 101,
    emH224			= 102,
    emDataTypeEnd	= 149,
        
    emTH235			= 150,		 //�ڲ�ʹ��
    emTMmcu			= 151,       //����ͨ��
    emTNone			= 152,       //��ͨ����֧��, �����ڼ���
    emTNonstandard	= 153,
    emTHuawei		= 154,
	
	//add for huawei nostandrd [20130427]
	emTHuawei5		= 155,
	emTHuawei6		= 156,
	emTHuawei7		= 157,
	//end [20130427]
		
	//add for ZTE nostandrd [20130507]
	emTZTE8			= 158,	//audio
	emTZTE10		= 159,	//audio
	emTZTE11		= 160,	//audio
	emTZTE13		= 161,	//video ��δ����ͬʱ������
	emTZTE21		= 162,	//video
	//end [20130507]

	//add for Polycom Viavideo HDX 7000 HD GenericControlCapability
	emControlCapType= 163,
	//end [20170417]
    
	emPayloadTypeEnd= 255
};

//�ֱ���,ʹ����ҵͷ�ļ��Ķ��壬�ϲ���emResolutionHD
typedef enum
{
	emResolutionBegin	= 0,
		emSQCIF			= 1,
		emQCIF			= 2,
		emCIF			= 3,
		emCIF2			= 4,
		emCIF4			= 5,
		emCIF16			= 6,
		
		emSIF			= 7,
		emSIF4			= 8,
		emVGA			= 9,
		emSVGA			= 10,
		emXGA			= 11,
		
		emAUTO			= 12,
		
		emEmpty			= 13,
		
		emW4CIF			= 14,				// Wide4CIF 16:9 1024*576
		emHD720			= 15,				// 720   1280*720
		emSXGA			= 16,				// SXGA  1280*1024
		emUXGA			= 17,				// UXGA  1600*1200
		emHD1080		= 18,				// 1080  1920*1080
		
		em1280x800		= 19,
		em1280x768		= 20,
		em480x352		= 21,
		
		em1440x900		= 22,
		em1280x960		= 23,
		emWCIF			= 24,
		em1366x768		= 25,

		em1680x1050		= 26,				// WSXGA+  1680*1050
		
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

		emResolutionEnd
}emResolution;

// H.264 NAL mode --> packetization mode
enum emH264NALMode
{
	emNALNode            = 0x00,       // invalid
	emNALSignal          = 0x01,       // single
	emNALSingle			 = emNALSignal,
	emNALNoneInterleaved = 0x02,       // not interleaved
	emNALInterleaved     = 0x04        // interleaved
};

//�������:����-Ӧ��ʽ���ؽ��
enum CtrlResult 
{
	ctrl_err = -1,
	ctrl_granted,		//�ɹ�
	ctrl_denied			//�ܾ�
};

//�豸���̱�ʶ��Ϣ
enum EmVendorProductId
{
	emMicrosoftNetmeeting	= 1,
	emKeda					= 2,
	emHuaWei				= 3,
	emPolycom				= 4,
	emPolycomMCU			= 5,
	emTandberg				= 6,
	emRadvision				= 7,
	emVcon					= 8,
	emSony					= 9,
	emVtel					= 10,
	emZTE					= 11,		//����
	emZTEMCU				= 12,
	emCodian				= 13,
	emAETHRA				= 14,
	emCHAORAN				= 15,
	emAVCON					= 16,		//��ƽ
	emDonJin				= 17,		//����GW
	emUNKNOWN				= 18,
	emVendorEND				= 19
};

#ifdef _KDV_SRTP_SUPPORT_
enum EmSrtpMode
{
	emSrtpModeNone,
	emSrtpModeOptional,
	emSrtpModeMandatory
};

enum EmSrtpType
{
	emSrtpTypeNone = 0x00,
	emSrtpTypeSdes = 0x01,
	emSrtpTypeDtls = 0x02,
	emSrtpTypeSdesDtls = (emSrtpTypeSdes | emSrtpTypeDtls)
};

enum EmSrtpCryptoType
{
	emSrtpCryptoNone = 0,     //������
	emSrtpCryptoAES_CM_128,
	emSrtpCryptoAES_CM_192,
	emSrtpCryptoAES_CM_256,
	emSrtpCryptoAES_GCM_128,  
	emSrtpCryptoAES_GCM_192,
	emSrtpCryptoAES_GCM_256,    
	emSrtpCryptoSM4_CM_128,    //SMĿǰֻ��128��  
	emSrtpCryptoSM1_CM_128, 
};

enum EmSrtpAuthType
{
	emSrtpAuthNone = 0,     //����֤
	emSrtpAuthTag_8,
	emSrtpAuthTag_16,
	emSrtpAuthTag_32,
	emSrtpAuthTag_80,	
};

typedef struct PROTO_API tagMediaSrtpCrypto
{
	s32 m_nTag;
	EmSrtpCryptoType m_emCryptoType;
	EmSrtpAuthType   m_emAuthType;
	s8 m_achCryptoKey[MAX_CRYPTO_KEY_LEN];

	tagMediaSrtpCrypto()
	{
		Clear();
	}
	void Clear()
	{
		m_nTag = 0;
		m_emCryptoType = emSrtpCryptoNone;
		m_emAuthType   = emSrtpAuthNone;
		memset(m_achCryptoKey, 0, sizeof(m_achCryptoKey));
	}
} TMediaSrtpCrypto;

typedef struct PROTO_API tagSrtpMediaSetting
{
	EmSrtpMode m_emSrtpMode;
	u32 m_dwCryptoCount;
	TMediaSrtpCrypto m_atSrtpCrypto[MAX_CRYPTO_NUM];

	tagSrtpMediaSetting()
	{
		Clear();
	}
	void Clear()
	{
		m_emSrtpMode = emSrtpModeNone;
		m_dwCryptoCount = 0;
		for (s32 i = 0; i < sizeof(m_atSrtpCrypto)/sizeof(m_atSrtpCrypto[0]); i++)
		{
			m_atSrtpCrypto[i].Clear();
		}
	}
} TSrtpMediaSetting;
#endif

/*�غ����͵��ڲ�ת��:
|<--------------���ܺ�H239���غ�ת��---------- >|<���ֽ�Ϊ�ϲ�ʹ�õ�����>|
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+  0  +  0  +  0  + 0  +  1  +  1  +  1  +  1  +  payloadType           +             
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                       + H239+ AES + DES +NoEnc+   
*/
//��������
typedef enum
{
    emEncryptTypeNone = 1,//00000001
    emEncryptTypeDES  = 2,//00000010
    emEncryptTypeAES  = 4,//00000100
    emEncryptTypeH239 = 8,//00001000
	emEncryptTypeAES256  = 16,//00010000

}emEncryptType;

//�ն˱�Ų���
typedef struct PROTO_API tagTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;

	tagTerminalLabel()
	{
		Clear();		
	}

	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

	bool operator ==(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo == tLabel.m_byMcuNo && m_byTerNo == tLabel.m_byTerNo)
			return true;
		else
			return false;
	}

	bool operator !=(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo != tLabel.m_byMcuNo || m_byTerNo != tLabel.m_byTerNo)
			return true;
		else
			return false;
	}
    //��Ч�Լ��
	bool IsValid()
	{
		return ( m_byMcuNo <= LEN_MTNUM_PERCONF && m_byTerNo <= LEN_MTNUM_PERCONF);
	}
    
    //����TerminalLabel
	BOOL32 SetTerminalLabel( u8 byMcuNo, u8 byTerNo )
	{
		if( byMcuNo <= LEN_MTNUM_PERCONF && byTerNo <= LEN_MTNUM_PERCONF )
		{
			m_byMcuNo = byMcuNo;
			m_byTerNo = byTerNo;
            return TRUE;
		}
        return FALSE;
	}
    //��ȡTerminalLabel
	void GetTerminalLabel( u8 *pMcuNo, u8 *pTerNo )
	{
		*pMcuNo = m_byMcuNo;
		*pTerNo = m_byTerNo;
	}
    //��ȡmcu���
	u8 GetMcuNo()
	{
		return m_byMcuNo;
	}
    //��ȡ�ն˱��
	u8 GetTerNo()
	{
		return  m_byTerNo;
	}
}TTERLABEL,*PTTERLABEL;

//------------------------------function--------------------------------------------

/*====================================================================
��	 ��   ��: GetProductName
��	      ��: ��ȡ��������
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: nProductId    - ��ƷID
�������˵������������
��   ��   ֵ: �����ַ���
====================================================================*/
PROTO_API const s8 *GetProductName(EmVendorProductId emProductId);

/*====================================================================
��	 ��   ��: RetrieveVendor
��	      ��: ����product name��ȡ����ID
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: pszProductId    - ������
			  nProductIdSize  - �ַ�������
�������˵���������ַ���
��   ��   ֵ: ����ID or emUNKNOWN if error occured
====================================================================*/
PROTO_API EmVendorProductId RetrieveVendor(const s8* pszProductId, u32 nProductIdSize);

namespace KDV
{
	namespace utils
	{
		//Make the input string lowercased and return;
		PROTO_API s8*		strlcase(INOUT s8* pchStr);
		//Make the input string uppercased and return;
		PROTO_API s8*		strucase(INOUT s8* pchStr);
		//Convert IPv4 address to a string, parameter pchIP must pre-allocated before calling this interface
		PROTO_API s8*		ConvertIpToStr(IN u32 dwIpAddr, OUT s8* pchIP, IN s32 nMaxSize);
		//Get a random u32 number, used to generate CallID, EPID, Session, etc.
		PROTO_API u32		GetRandomNumber(void);

		typedef struct PROTO_API uCID
		{
			u8		m_abyMacAddress[6];
			u8		m_abyTime[8];
			BOOL32	m_bClock_seq_change;
		} uCID;
		
		typedef struct PROTO_API cidLocalStorage
		{
			u32		m_dwStartTime;
			u32		m_dwStartMilliTime;
			u32		m_dwOldMilliTime;
			u8		m_abyLastTime[8];
			BOOL32	m_bNotStart;
			BOOL32	m_bGenerated;
			uCID	m_tUCID;
			u8  	m_abyCid[16];
			u8  	m_abyOldCid[16];
			u16     m_wClock_seq;
		} cidLocalStorage;
		
		//Parameter pbyTime and clockSeqChange must pre-allocated before calling this interface
		PROTO_API cidLocalStorage *GetTime(OUT u8 *pbyTime, OUT BOOL32 *clockSeqChange);
		//Generate a GUID
		PROTO_API u8*		GetGUID(void);
	}
	namespace NET
	{
		//////////////////////////////////////////////////////////////////////////
		//parameter pbyMAC must pre-allocated before calling this interface
		//��δʵ��
		PROTO_API void	GetMACaddress(OUT u8* pbyMAC);
		//s32	GetLocalAddress(s8* pchIPAddr, s8* ETH_NAME /* = "eth0" */);
		//s32	GetLocalMac(u8* pbyVMac, s8* ETH_NAME /* = "eth0" */);
	}

	namespace SYS
	{
		//////////////////////////////////////////////////////////////////////////
		//System - Date time
		//////////////////////////////////////////////////////////////////////////
		PROTO_API u32		timerGetTimeInMilliseconds(void);
		PROTO_API u32		timerGetTimeInSeconds(void);

		//////////////////////////////////////////////////////////////////////////
		//File System - Directory operations
		//////////////////////////////////////////////////////////////////////////
		PROTO_API BOOL32	isDirectoryExisting	(IN const char* strFolder);
		PROTO_API BOOL32	CreateDirectory		(IN const char* strFolder, IN void* pAttr);
		PROTO_API BOOL32	RemoveDirectory		(IN const char* strFolder);
		PROTO_API BOOL32	isDirEmpty			(IN const char* strFolder);
		PROTO_API BOOL32	isDirectory			(IN const char* strFolder);
		PROTO_API BOOL32	IsDiskFull			(IN const char* strPath);

		//////////////////////////////////////////////////////////////////////////
		//File System - File operations
		//////////////////////////////////////////////////////////////////////////
		PROTO_API BOOL32	IsFileExisted		(IN const char* strFileName);
		PROTO_API u64		getFileSize			(IN const char* strFileName);
		PROTO_API BOOL32	DeleteFile			(IN const char* strFileName);
		PROTO_API s8*		getModifiedTime		(IN const char* strFileName);
		PROTO_API s8*		getCreateTime		(IN const char* strFileName);

		//////////////////////////////////////////////////////////////////////////
		//Endian type
		//////////////////////////////////////////////////////////////////////////
		PROTO_API BOOL32	IsLitttleEndian		();
		PROTO_API u64 htonll(u64 host);	// host long 64 to network
		PROTO_API u64 ntohll(u64 host);	//network to host long 64
	}

	namespace algorithm
	{
		//Diffie�CHellman key exchange
		namespace DH
		{
#define LEN_DHKEY_MAX		(u16)256                //dhkey����󳤶�
#define LEN_DH_X			(u16)8                  //dh�е����������
#define LEN_DHKEY			(u16)64                 //dhkey�ĳ���
#define LEN_H235KEY_MAX		(u16)64					//(1-65535)  
#define FREEVLONG(vl)		{if(vl != 0) {KDV::algorithm::DH::vlongFree(&vl);}}
			
			typedef long*  verylong;
			
			PROTO_API void vlongFree(verylong *x);
			
			//m_abyHalfKey = g^x mod n -->[ A = g^a mod p (B = g^b mod p) ==> K = B^a mod p (K = A^b mod p) ]
			typedef struct PROTO_API tagDHSet
			{
				u8	m_abyHalfKey[LEN_DHKEY_MAX];
				u8	m_abyModSize[LEN_DHKEY_MAX];
				u8	m_abyGenerator[LEN_DHKEY_MAX];
				s32 m_nHalfKeyBits;
				s32 m_nModSizeBits;
				s32 m_nGenBits;
				
				verylong n;
				verylong g;
				verylong x;
				
				tagDHSet();
				~tagDHSet();
				void Reset();
				u8* GetHalfKey();
				s32 GetHalfKeyBits();
				s32 SetHalfKeyBits(s32 nBits);
				s32 SetHalfKey(u8 *pbyHalfKey, s32 nBits);
				
				u8* GetModSize();
				s32 GetModSizeBits();
				s32 SetModSizeBits(s32 nBits); 
				s32 SetModeSize(u8 *pbyModSize, s32 nBits);
				
				u8* GetGenerator();
				s32 GetGenBits();
				s32 SetGenBits(s32 nBits); 
				s32 SetGenerator(u8 *pbyGenerator, s32 nBits);
			}TDHSet;
		} // End of namespace DH

		namespace BASE64
		{
			// ��δʵ��: Code to be merged/combined 
			PROTO_API BOOL32 base64_encode(const u8* pbyInput, u32 dwInLen, u8* pbyOutput, u32 &dwOutLen);
			PROTO_API BOOL32 base64_decode(const u8* pbyInput, u32 dwInLen, u8* pbyOutput, u32 &dwOutLen);
		} // End of namespace BASE64

		namespace MD5
		{
			// ��δʵ��: Code to be merged/combined, CBB5.0/20-cbb/kdvsipadapter/source/md5.cpp
			/* MD5 context. */
			/*==========================================================*/
			/* GLOBAL.H - RSAREF types and constants
			*/
			/* PROTOTYPES should be set to one if and only if the compiler supports
				function argument prototyping.
				The following makes PROTOTYPES default to 0 if it has not already
				been defined with C compiler flags.
			*/
#ifndef PROTOTYPES
	#define PROTOTYPES 1
#endif

/* POINTER defines a generic pointer type */
typedef u8 *POINTER;

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
  returns an empty list.
 */
#if PROTOTYPES
	#define PROTO_LIST(list) list
#else
	#define PROTO_LIST(list) ()
#endif
/*================================================================*/
			typedef struct PROTO_API MD5_CTX
			{
				u32 state[4];        /* state (ABCD) */
				u32 count[2];        /* number of bits, modulo 2^64 (lsb first) */
				u8 buffer[64];       /* input buffer */
			} MD5_CTX;

			PROTO_API void MD5Init (MD5_CTX *);
			PROTO_API void MD5Update (MD5_CTX *, u8 *, u32);
			PROTO_API void MD5Final (u8 [16], MD5_CTX *);
			PROTO_API void MD5toString(u8 *digest, s8* buff);
		} // End of namespace MD5

		namespace SHA1
		{
			// ��δʵ��: Code to be merged/combined 

		} // End of namespace SHA1

	} // End of namespace algorithm

} // End of namespace KDV

//����ͬ���ṹ  
typedef struct PROTO_API tagEncryptSync
{
	s32			  m_nSynchFlag;			         //shall be the Dynamic PayloadType for H.323
	u8			  m_abyH235Key[LEN_H235KEY_MAX]; //H.235 encoded value(1-65535)
	s32           m_nH235KeyLen;

	tagEncryptSync()
	{
		Reset();
	}

	void Reset()
	{
		m_nSynchFlag  = 0;
		m_nH235KeyLen = 0;
		memset( m_abyH235Key, 0, sizeof(m_abyH235Key) );
	}

	void host2net(BOOL32 bhton)
	{
		if (bhton)
		{
			m_nSynchFlag  = htonl(m_nSynchFlag);
			m_nH235KeyLen = htonl(m_nH235KeyLen);
		}
		else
		{
			m_nSynchFlag  = ntohl(m_nSynchFlag);
			m_nH235KeyLen = ntohl(m_nH235KeyLen);
		}
	}

	//����SynchFlag
	void SetSynchFlag(s32 nFlag)
	{ 
		m_nSynchFlag = nFlag; 
	}
	//��ȡSynchFlag
	s32  GetSynchFlag() 
	{
		return m_nSynchFlag; 
	}

	//����H235Key
	s32 SetH235Key(u8 *pBuf, s32 nLen)
	{
		m_nH235KeyLen = Minimum(Maximum(0, nLen), (s32)LEN_H235KEY_MAX);
		memcpy(m_abyH235Key, pBuf, m_nH235KeyLen);
		return m_nH235KeyLen;
	}	
	//��ȡH235Key�ĳ���
	s32 GetH235KeyLen() 
	{
		return m_nH235KeyLen; 
	}
	//��ȡH235Key
	u8* GetH235Key()
	{
		return m_abyH235Key;
	}
}TEncryptSync;



#endif
