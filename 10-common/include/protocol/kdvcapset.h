#ifndef _H323CAPSET_H
#define _H323CAPSET_H
#include "kdvtype.h"
#include "protocolcommonpublic.h"
#include "kdvcommon.h"

#define SIP_ADPT_AUDIO_DEFAUL_SAMPLERATE 8000
#define SIP_ADPT_AUDIO_DEFAULT_PACKTIME 30
#define SIP_ADPT_FECC_DEFAULT_BITRATE	64

#define MAX_CAPTABLE_SIZE	(u16)64					//max 256
#define MAX_ALTCAP_NUM      MAX_CAPTABLE_SIZE		//max 256
#define MAX_SIMUCAP_NUM     (u16)16					//max 256 (CodianΪ13)
#define MAX_DESCAP_NUM      (u16)5					//max 256 (ץ�����ֶ���1��������2����)
#define MAXBITRATE_H261     (u16)19200				//��λ100bps
#define MAXBITRATE_H263     (u32)192400				//��λ100bps

// guzh [9/25/2007] ǰ���������
enum emFECType
{
    emFECNone		= 0x00,
	emFECRaid5		= 0x01,
	emFECRaid6		= 0x02,
	emFECNonStd		= 0x04 //��˾�Լ���NsmFec add by shigubin 20130228
};

//roleLabel ֵ [20140829]
enum emH239RoleLabel 
{
	H239Role_NotSupport				= 0,		//��֧��h239
	H239Role_Presentation			= 1,		//Presentation
	H239Role_Live					= 2,		//Live
	H239Role_LiveAndPresentation	= 3,		//both live and Presentation ==> presentation
};

enum EM_CAPDIRECTION
{
	emCapReceive	= 1,
	emCapTransmit	= 2,
	emCapReceiveAndTransmit=3
};

#ifdef WIN32
	#pragma comment( lib, "ws2_32.lib" ) 
	#pragma pack( push )
	#pragma pack( 1 )
	#define window( x )	x
	#ifndef PACKED
		#define PACKED
	#endif
#else
	#include <netinet/in.h>
	#define window( x )
	#if defined(__ETI_linux__)
		#define PACKED
	#else
		#ifdef PACKED
			#undef PACKED
		#endif
	#define PACKED __attribute__ ((packed))	// ȡ�����������Ż�����
	#endif
#endif

struct PROTO_API TKdvCapSet
{
    u32			m_dwSampleRate;
    PayloadType	m_emPayloadType;
    u16			m_wStaticPayload;
    u16			m_wDynamicPayload;

protected:
	EM_CAPDIRECTION m_emCapDirection;//not init
public:
	TKdvCapSet()
	{
		Clear();
	}

	void Clear()
	{
		m_emPayloadType		= emPayloadTypeBegin;
		m_dwSampleRate		= SIP_ADPT_AUDIO_DEFAUL_SAMPLERATE;
		m_wDynamicPayload	= 0;
		m_wStaticPayload	= 0;
	}

	void SetPayloadType( PayloadType emPt )
	{
        m_emPayloadType = emPt;
	}
	
	PayloadType GetPayloadType()
	{
		return m_emPayloadType;
	}
	
	void SetSampleRate( u32 dwSampleRate )
	{
        m_dwSampleRate = dwSampleRate;
	}
	
	u32 GetSampleRate()
	{
		return m_dwSampleRate;
	}
	
	void SetStaticPayload( u16 wPt )
	{
		m_wStaticPayload = wPt;
	}
	u16 GetStaticPayload()
	{
		return m_wStaticPayload;
	}
	
	void SetDynamicPayload( u16 wDPt )
	{
		m_wDynamicPayload = wDPt;
	}
	u16 GetDynamicPayload()
	{
		return m_wDynamicPayload;
	}

	// Interfaces merged from H.323
    void SetCapDirection(EM_CAPDIRECTION emDirect)
    {
        m_emCapDirection = emDirect;
    }
    EM_CAPDIRECTION GetCapDirection() const
    {
        return m_emCapDirection;
	}
	//virtual void host2net(BOOL32 bhton) = 0;
}PACKED;

//��Ƶ��������������G.7231
struct PROTO_API TKdvAudioCap : public TKdvCapSet
{
	u8   m_byPackTime;     //ÿһRTP�������ʱ��,��λms(1-256); 

public:
	TKdvAudioCap():TKdvCapSet()
	{
		m_byPackTime = SIP_ADPT_AUDIO_DEFAULT_PACKTIME;
	}

	void Clear()
	{
		m_byPackTime = SIP_ADPT_AUDIO_DEFAULT_PACKTIME;
		TKdvCapSet::Clear();
	};

    //���ô��ʱ��
	void SetPackTime(u8 byPackTime)
	{
		m_byPackTime = byPackTime;
	}
    //��ȡ���ʱ��
	u8  GetPackTime()
	{
		return m_byPackTime;
	}

	// interfaces merged from H.323
	void host2net(BOOL32 bhton);
}PACKED;

//G7231��������
struct PROTO_API TKdvG7231Cap : public TKdvAudioCap
{
	u8				m_byMaxFrameNum;		//��������֡��
	BOOL32			m_bSilenceSuppression;	//�Ƿ�������

public:
	TKdvG7231Cap():TKdvAudioCap()
	{
		m_byMaxFrameNum  = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
		m_bSilenceSuppression = TRUE;
	}

	void Clear()
	{
		m_byMaxFrameNum  = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
		m_bSilenceSuppression = TRUE;	    //����Ĭ��֧�־�������
		TKdvAudioCap::Clear();
	}

    //�����Ƿ�֧�־���
    void SetIsSilenceSuppression(BOOL32 bSilenceSuppression)
    {
        m_bSilenceSuppression = bSilenceSuppression;
    }
    //�Ƿ�֧�־���
	BOOL32 IsSilenceSuppression()
	{
		return m_bSilenceSuppression;
	}
    
    //����ÿ�������֡��
	void SetMaxFrameNumPerPack(u8 byMaxFrameNum)
	{
		m_byMaxFrameNum = byMaxFrameNum;
	}
    //��ȡÿ�������֡��
	u8 GetMaxFrameNumPerPack()
	{
		return m_byMaxFrameNum;
	}

	void host2net(BOOL32 bhton)
	{
		s32 nCapDirection = m_emCapDirection;
		if (bhton)
		{
			m_emCapDirection        = (EM_CAPDIRECTION)htonl(nCapDirection);
			m_bSilenceSuppression   = htonl(m_bSilenceSuppression);
		}
		else
		{
			m_emCapDirection        = (EM_CAPDIRECTION)ntohl(nCapDirection);
			m_bSilenceSuppression   = ntohl(m_bSilenceSuppression);
		}
	}
}PACKED;

struct PROTO_API TKdvG7221Cap: public TKdvAudioCap
{
	u8  m_byBitRateType;         //encode bitrate
	enum emG7221Rate
	{
		emG7221RateNone =  0x00,
		emG7221Rate24   =  0x01,
		emG7221Rate32   =  0x02,
		emG7221Rate48   =  0x04
	};

public:
	TKdvG7221Cap():TKdvAudioCap()
	{
		m_byBitRateType = emG7221Rate24;
		m_dwSampleRate = 32000;
	}
	
	void Clear()
	{
		TKdvAudioCap::Clear();
    	m_byBitRateType = emG7221Rate24;
		m_dwSampleRate = 32000;
	};
	
    //����rate
	void SetRateType( u8 byRateType )
	{
		m_byBitRateType = byRateType;
	}
	void OrRateType( emG7221Rate emRateType )
	{
	    m_byBitRateType = (m_byBitRateType | emRateType);
	}

	//��ȡrate
	u8 GetRateType()
	{
		return m_byBitRateType;
	}

	void SetBitRate( u32 dwBitRate )
	{
		m_byBitRateType = 0;
		if ( dwBitRate == 48000 )
			m_byBitRateType = emG7221Rate48;
        else if ( dwBitRate == 32000 )
			m_byBitRateType = emG7221Rate32;
        else
			m_byBitRateType = emG7221Rate24;
	}

	u16 GetBitRate()
	{
		if( m_byBitRateType == emG7221Rate48 )
			return 48000;
		else if ( m_byBitRateType == emG7221Rate32 )
			return 32000;
		else 
			return 24000;
	}
	void host2net(BOOL32 bhton)
	{
		//XXX Why convert CapDirection only rather than all the variants??
		s32 nCapDirection = m_emCapDirection;
		if (bhton)
		{
			m_emCapDirection = (EM_CAPDIRECTION)htonl(nCapDirection);
		}
		else
		{
			m_emCapDirection = (EM_CAPDIRECTION)ntohl(nCapDirection);
		}
	}
}PACKED;

/*
Opus codec
---------------------------------------
supported features are:
  Bitrates from 6 kb/s to 510 kb/s
  Sampling rates from 8 kHz (narrowband) to 48 kHz (fullband)
  Frame sizes from 2.5 ms to 60 ms
  Support for both constant bitrate (CBR) and variable bitrate (VBR)
  Audio bandwidth from narrowband to fullband
  Support for speech and music
  Support for mono and stereo
  Support for up to 255 channels (multistream frames)
  Dynamically adjustable bitrate, audio bandwidth, and frame size
  Good loss robustness and packet loss concealment (PLC)
  Floating point and fixed-point implementation
*/
struct PROTO_API TKdvOpusCap : public TKdvAudioCap
{
	u8              m_byVersion;
    u16             m_wMaxBitrate;
	u16             m_wMinBitrate;

public:
    TKdvOpusCap()
    {
        Clear();
    }
    
    void Clear()
	{
		m_byVersion   = 1;
		m_wMaxBitrate = 510;                    //kbps
		m_wMinBitrate = 6;
		m_dwSampleRate= 8000;
	}
    
    void host2net(BOOL32 bhton);

    void SetMaxBitrate(u16 wBitRate )
    {
        m_wMaxBitrate = wBitRate;
    }
	
    u16 GetMaxBitrate() const
    {
        return m_wMaxBitrate;
    }
	
    void SetMinBitrate(u16 wBitrate) 
    {
        m_wMinBitrate = wBitrate;
    }
	
    u16 GetMinBitrate() const
    {
        return m_wMinBitrate;
    }
	
    void SetVersion(u8 byVersion) 
    {
        m_byVersion = byVersion;
    }
	
    u8 GetVersion() const
    {
        return m_byVersion;
    }
}PACKED;

/*
telephone-event codec
---------------------------------------
according to RFC2833:
Event  encoding (decimal)
_________________________
0--9                0--9
*                     10
#                     11
A--D              12--15
*/

struct PROTO_API TKdvTelephoneEventCap : public TKdvAudioCap
{
	s8 m_achEncoding[256];
public:
	TKdvTelephoneEventCap()
	{
		Clear();
		TKdvAudioCap::Clear();
	}

	void Clear()
	{
		memset(m_achEncoding,0,sizeof(m_achEncoding));
		m_dwSampleRate = 8000;
	}
    
	void SetEventEncoding(s8* pchEventEncoding)
	{
		if ( NULL != pchEventEncoding && 0 != strlen(pchEventEncoding))
		{
			MEMCPY_CAST(m_achEncoding,pchEventEncoding,strlen(pchEventEncoding));
		}
		
	}

	s8* GetEventEncoding( ) 
	{
		return m_achEncoding;
	}

}PACKED;

//MPEG AAC������
struct PROTO_API TKdvAACCap : public TKdvAudioCap
{
    enum emAACSampleFreq                    //sampling frequency
    {
        emFs96000 = 0,
        emFs88200 = 1,
        emFs64000 = 2,
        emFs48000 = 3,
        emFs44100 = 4,
        emFs32000 = 5,
        emFs24000 = 6,
        emFs22050 = 7,
        emFs16000 = 8,
        emFs12000 = 9,
        emFs11025 = 10,
        emFs8000  = 11
    };
    
    enum emAACChnlCfg                       //channel config
    {
        emChnlCust   = 0,
        emChnl1      = 1,                   //������
        emChnl2      = 2,                   //˫����
        emChnl3      = 3,					//����˫��֧��
        emChnl4      = 4,
        emChnl5      = 5,
        emChnl5dot1  = 6,                   //5.1����
        emChnl7dot1  = 7                    //7.1����
    };

    emAACSampleFreq m_emSampleFreq;
    emAACChnlCfg    m_emChnlCfg;
    u16             m_wBitrate;
    u8              m_byMaxFrameNum;

public:
    TKdvAACCap()
    {
        Clear();
    }
    
    void Clear()
    {
        m_emSampleFreq	= emFs32000;
        m_emChnlCfg		= emChnlCust;
        m_byMaxFrameNum = 1;			    //Ŀǰ����ֻ֧�ֵ�֡
        m_wBitrate		= 96;                    //kbps
		TKdvAudioCap::Clear();
    }
    
    void SetSampleFreq(emAACSampleFreq emFs)
    {
        m_emSampleFreq= emFs;
    }

    emAACSampleFreq GetSampleFreq() const
    {
        return m_emSampleFreq;
    }

    void SetChnl(emAACChnlCfg emChnl)
    {
        m_emChnlCfg = emChnl;
    }

    emAACChnlCfg GetChnl() const
    {
        return m_emChnlCfg;
    }

    void SetBitrate(u16 wBitrate) 
    {
        m_wBitrate = wBitrate;
    }

    u16 GetBitrate() const
    {
        return m_wBitrate;
    }

	// interfaces merged from H.323
	void host2net(BOOL32 bhton);
}PACKED;

/*********************����֡�ʵ�����******************
*1��ʾ29.97, 2��ʾ29.97/2, 3��ʾ29.97/3,.....
*H261��cif(1-4) qcif(1-4)
*H263  sqcif,qcif,cif,4cif,16cif  (1-32)
*****************************************************/
//��Ƶ������
struct PROTO_API TKdvVideoCap : public TKdvCapSet
{
	u16         m_wMaxBitRate;						//��λkbps
	u8          m_abyResolution[emResolutionEnd];	//֡�� 
    PayloadType	m_emPayloadType;  //�ظ�������

public:
	TKdvVideoCap()
	{
	    Clear();
	}

	void Clear();

	//��λkbps
	void SetBitRate(u16 wBitRate)
	{
		m_wMaxBitRate = wBitRate;		
	}
	u16 GetBitRate() const
	{
        return m_wMaxBitRate;
	}
	BOOL32 SetResolution(emResolution emRes, u8 byMPI);
	u8 GetResolution( emResolution emRes ) const;

	// Interfaces merged from H.323
	void	host2net(BOOL32 bhton);
	void	MergeVideoCap(const TKdvVideoCap &tVideoCap);
	// toolkit: Res enum to width*height
	BOOL32	Res2WxH(emResolution emRes, u16 &wWidth, u16 &wHeight) const;
}PACKED;

//H.264��Ƶ������
/*********************����֡�ʵ�����******************
*1��ʾ1fps, 60����60fps���������֡�ʿ��Դﵽ����ֵ255
*****************************************************/
struct PROTO_API TKdvH264VideoCap:public TKdvVideoCap
{
protected:
    // H.264 �������壬�μ� ITU H.241�ĵ�
    u8              m_byProfile;
    u8              m_byLevel;
    // ����2���ֶΣ�ȡ Custom ��LevelֵĬ�ϵ� max(��λ��Ϊ���)
    s32             m_nMaxMBPS;
    s32             m_nMaxFS;
    // ���±�����Ǿ��� Custom ���ֶΣ���ʱ��֧�����ã�
    s32             m_nMaxDPB;
    s32             m_nMaxBRandCPB;
    s32             m_nMaxStaticMBPS;
	
	// �����Ǳ�־�ֶ�,�������ƫ����Ӧλ��λ
	s32             m_nParaFlag;
	
	//svc
	u8				m_byAdditionalModes;

	emH264NALMode   m_emH264NALMode;
	
public:
	BOOL32          m_bOld264Level;
	BOOL32			m_bUsed;

public:
    // Э�� 
    enum  emH264ProfileMask
    {
        emProfileBaseline = 64,
        emProfileMain     = 32,
        emProfileExtend   = 16,
        emProfileHigh     = 8
    };

	enum emAdditionalModes
	{
		emModeRCDO	= 64,		//RCDO
		emModeSBP	= 32,		//SCALABLE bp
		emModeSHP	= 16		//SCALABLE hp
	};

    TKdvH264VideoCap();  
    void Clear();

	void host2net(BOOL32 bhton);

	// Э��: ֧�� emH264ProfileMask �������������ǵ��߼���
    void SetSupportProfile(u8 byProfile)
	{
		m_byProfile = byProfile;
		//if(m_byProfile < 64)
		//	m_byProfile = 64;
	}
	BOOL32 IsSupportProfile(u8 byReqProfile) const
	{
		return ((m_byProfile&byReqProfile) == byReqProfile);
	}
	
    u8   GetProfileValue() const
    {
        return m_byProfile;
    }
    
	// ����������
	/*
 	 *function: ��ȡ�ض��ֱ����µ�֡��
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
	 *return:   u8 ֡�� frame/s
	 */
    u8   GetResolution(emResolution emRes) const;
    u8   GetResolution(u16 wWidth, u16 wHeight) const;

	/*
	 *function: �ض��ֱ����£��ض�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�Ƿ�֧��
                ���ڶԶ��Ƿ�֧�ֳ���ʽ��Ҫҵ����� IsSupportProfile �����ж� 
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
     *return:   TRUE/FALSE
	 */
    BOOL32 IsSupport(emResolution emRes, u8 byFps) const;
    BOOL32 IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/*
	 *function: ����֧��ĳ�ֱַ��ʺ�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�����ֱַ��ʿ��Ե�������
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
	 */
    void  SetResolution(emResolution emRes, u8 byFps) ;
    void  SetResolution(u16 wWidth, u16 wHeight, u8 byFps) ;

    // �ڲ�ʹ�ú���
    void  SetMaxMBPS(s32 nMax)
    {
        m_nMaxMBPS = nMax;
    }
    s32   GetMaxMBPS() const
    {
        return m_nMaxMBPS;
    }
    void  SetMaxFS(s32 nMax)
    {
        m_nMaxFS = nMax;
    }
    s32   GetMaxFS() const
    {
        return m_nMaxFS;
    }

	void SetMaxStaticMBPs( s32 nStaticMBPs )
	{
		m_nMaxStaticMBPS = nStaticMBPs;
	}
	s32 GetMaxStaticMBPs() const
	{
		return m_nMaxStaticMBPS;
	}

	//m_nAdditionalModes
	void SetSupportAdditionalModes(u8 byAdditionalModes)
    {
        m_byAdditionalModes = byAdditionalModes;
    }
	
    BOOL32 IsSupportAdditionalModes(u8 byAdditionalModes) const
    {
        return ((m_byAdditionalModes&byAdditionalModes) == byAdditionalModes);
    }
	
    u8   GetAdditionalModes() const   
    {
        return m_byAdditionalModes;
	}

	//m_emH264NALMode
	void SetH264NALMode(emH264NALMode emNalMode)
	{
		m_emH264NALMode = emNalMode;
	}
	emH264NALMode GetH264NALMode() const   
	{
		return m_emH264NALMode;
	}

	void  SetMaxBRandCPB(s32 nMaxBRandCPB)
	{
		m_nMaxBRandCPB = nMaxBRandCPB;
	}
	s32   GetMaxBRandCPB() const
	{
		return m_nMaxBRandCPB;
	}

    //  Level���ⲿ������Ч
    void SetLevel(u8 byLevel)
    {
        m_byLevel = byLevel;
    }
     u8 GetLevel() const
    {
        return m_byLevel;
    }

	s32 GetParaFlag()
	{
		return m_nParaFlag;
	}
	void SetParaFlag(s32 nParaFlag)
    {
        m_nParaFlag = nParaFlag;
    }

	BOOL32 operator <= (const TKdvH264VideoCap& tH264VideoCap);
	void operator = (const TKdvH264VideoCap& tH264VideoCap);
	BOOL32 operator == (const TKdvH264VideoCap& tH264VideoCap);

	BOOL32 AdjustH264Cap();
}PACKED;

//////////////////////////////////////////////////////////////////////////
// H.265 video capability 
// You can refer to T-REC-H.265-201304-I from ITU/T for H.265 standards details
//////////////////////////////////////////////////////////////////////////
struct PROTO_API TKdvH265VideoCap : public TKdvVideoCap
{
protected:
	// H.265 Level Limits, refer to ITU H.241 for more info
    u8		m_byProfile;
    u8		m_byLevel;
	u8		m_byTier;
	s32		m_nMaxLS;			//Max LUMA picture size (samples): 
	s32		m_nMaxLumaPS;		//Max LUMA sample rate (samples/sec) 
	// H.265 capability related variants
	s32		m_nMaxDPB;			//Max Decode Picture Buffer
	s32		m_nMaxBR;			//Max Bit Rate
	s32		m_nMaxCPB;			//Max Code Picture Buffer
	s32		m_nMaxSliceSegmentsPerPic;
	s32		m_nMaxTileRows;
	s32		m_nMaxTileCols;
	s32		m_nMinCbSizeY;
	
public:
	BOOL32	m_bUsed;

public:
	TKdvH265VideoCap();  

public:
	//Refer document: T-REC-H.265-201304-I: Annex A
    enum emH265Profile
    {
        emProfileMain,
        emProfileMain10,
        emProfileMainStill,
    };

	enum emH265Level
	{
		emLevel10,
		emLevel20,
		emLevel21,
		emLevel30,
		emLevel31,
		emLevel40,
		emLevel41,
		emLevel50,
		emLevel51,
		emLevel52,
		emLevel60,
		emLevel61,
		emLevel62,
	};

	enum emH265Tier
	{
		emHignTier,
		emMainTier,
	};

    void	Clear();

    // ����������
     /*
	 *function: ��ȡ�ض��ֱ����µ�֡��
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
     *return:   u8 ֡�� frame/s
	 */
    u8		GetResolution(emResolution emRes) const;
    u8		GetResolution(u16 wWidth, u16 wHeight) const;

	/*
	 *function: �ض��ֱ����£��ض�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�Ƿ�֧��
                ���ڶԶ��Ƿ�֧�ֳ���ʽ��Ҫҵ����� IsSupportProfile �����ж� 
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
     *return:   TRUE/FALSE
	 */
    BOOL32	IsSupport(emResolution emRes, u8 byFps) const;
    BOOL32	IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/*
	 *function: ����֧��ĳ�ֱַ��ʺ�֡��(���ڳ�ģʽ����Ҫ�ϲ�ת��Ϊ֡�ʴ���)�����ֱַ��ʿ��Ե�������
	 *param:	u8 byRes                    �ֱ��ʣ�emResolution ���� emResolutionHD
                u8 byFps                    ֡��frame/s
	 */
    void	SetResolution(emResolution emRes, u8 byFps) ;
    void	SetResolution(u16 wWidth, u16 wHeight, u8 byFps) ;

	
	// Э��: ֧�� emH265ProfileMask �������������ǵ��߼���
    void SetSupportProfile(u8 byProfile)
	{
		m_byProfile = byProfile;
		//if(m_byProfile < 64)
		//	m_byProfile = 64;
	}
	BOOL IsSupportProfile(u8 byReqProfile) const
	{
		return ((m_byProfile&byReqProfile) == byReqProfile);
	}
    u8   GetProfileValue() const
    {
        return m_byProfile;
    }

    // Level
    void	SetLevel(u8 byLevel) { m_byLevel = byLevel; }
	u8		GetLevel() const { return m_byLevel; }
	void	SetProfile(u8 byProfile) { m_byProfile = byProfile; }
	u8		GetProfile() const {return m_byProfile;};
	void	SetTier(u8 byTier) {m_byTier = byTier;}
	u8		GetTier() const {return m_byTier;}

	// Interfaces for internal use only
	s32		GetMaxLumaPS() const {return m_nMaxLumaPS;}
	void	SetMaxLumaPS(s32 nMaxLumaPs) {m_nMaxLumaPS = nMaxLumaPs;}
	s32		GetMaxCPB() const {return m_nMaxCPB;}
	void	SetMaxCPB(s32 nMaxCPB) {m_nMaxCPB = nMaxCPB;}
	s32		GetMaxSliceSegPerPic() const {return m_nMaxSliceSegmentsPerPic;}
	void	SetMaxSliceSegPerPic(s32 nMaxSliceSegPerPic) {m_nMaxSliceSegmentsPerPic = nMaxSliceSegPerPic;}
	s32		GetMaxTileRows() const {return m_nMaxTileRows;}
	void	SetMaxTileRows(s32 nMaxTileRows) {m_nMaxTileRows = nMaxTileRows;}
	s32		GetMaxTileCols() const {return m_nMaxTileCols;}
	void	SetMaxTileCols(s32 nMaxTileCols) {m_nMaxTileCols = nMaxTileCols;}
	s32		GetMaxLS() const {return m_nMaxLS;}
	void	SetMaxLS(s32 nMaxLS) {m_nMaxLS = nMaxLS;}
	s32		GetMaxDPB() const {return m_nMaxDPB;}
	void	SetMaxDPB(s32 nMaxDPB) {m_nMaxDPB = nMaxDPB;}
	s32		GetMaxBR() const {return m_nMaxBR;}
	void	SetMaxBR(s32 nMaxBR) {m_nMaxBR = nMaxBR;}

	BOOL32	operator <= (const TKdvH265VideoCap& tH265VideoCap);
	void	operator =  (const TKdvH265VideoCap& tH265VideoCap);
	BOOL32	operator == (const TKdvH265VideoCap& tH265VideoCap);

	static BOOL32 GetH265LimitsByLevel(IN emH265Level emLevel, OUT s32 &nMaxLS, OUT s32 &nMxLumaPS);
}PACKED;

struct PROTO_API TKdvDataCap : public TKdvCapSet
{
	u32   m_dwMaxBitRate;					//��λkbps; 
public:
	TKdvDataCap()
	{
		Clear();
	}

	void Clear()
	{
		TKdvCapSet::Clear();
		m_dwMaxBitRate = SIP_ADPT_FECC_DEFAULT_BITRATE;
		m_dwSampleRate = 0;
	}

	//��λkbps
	void SetBitRate(u32 dwBitRate)
	{
		m_dwMaxBitRate = dwBitRate;		
	}
	u32 GetBitRate()
	{
        return m_dwMaxBitRate;
	}

	// Interfaces merged from H.323
	void host2net(BOOL32 bhton)
	{
		s32 nCapDirection = m_emCapDirection;
		if (bhton)
		{
			m_emCapDirection = (EM_CAPDIRECTION)htonl(nCapDirection);
			m_dwMaxBitRate   = htonl(m_dwMaxBitRate);
		}
		else
		{
			m_emCapDirection = (EM_CAPDIRECTION)ntohl(nCapDirection);
			m_dwMaxBitRate   = ntohl(m_dwMaxBitRate);
		}
	}
}PACKED;

/************************************
* �������ṹ
* Ŀǰ����Ƶ֧��:h261,h263,h264,mpeg4,h263+,h262
* Ŀǰ����Ƶ֧��:G711u(64k),G711a(64k),G722(64k),G7231,G728,G729,G7221C,MP3,MP2AAC,MP4AAC.
* 
* guzh [12/17/2007] �����ṹ
* guzh [04/03/2008] �����ṹ
 *************************************/
struct PROTO_API TKdv323CapSet
{
private:
	u16 m_awCapTable[MAX_CAPTABLE_SIZE]; //PayloadType array
	u16 m_aaawCapDesc[MAX_DESCAP_NUM][MAX_SIMUCAP_NUM][MAX_ALTCAP_NUM]; //PayloadType array
    //Video
	TKdvVideoCap      m_tH261Cap;
	TKdvVideoCap      m_tH263Cap;
	TKdvVideoCap      m_tH263plusCap;
	TKdvVideoCap      m_tMpeg4Cap;
    TKdvVideoCap      m_tH262Cap;
    //Audio
	TKdvAudioCap      m_tG711u;   
	TKdvAudioCap      m_tG711a;   
	TKdvAudioCap      m_tG722;    
	TKdvAudioCap      m_tG728;	   
	TKdvAudioCap      m_tG729;
	TKdvAudioCap      m_tMP3;
    TKdvAACCap        m_tMpegAacLc;
    TKdvAACCap        m_tMpegAacLd;		
	TKdvG7231Cap      m_tG7231;
    //Data
	TKdvDataCap       m_tT120;
	TKdvDataCap       m_tH224;

    /*�غ����͵��ڲ�ת��:
    |<--------------���ܺ�H239���غ�ת��---------- >|<���ֽ�Ϊ�ϲ�ʹ�õ�����>|
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +  0  +  0  +  0  +  0  +  1  +  1  +  1  +  1  +  payloadType           +             
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            + H239+ AES + DES +NoEnc+   
    */
	u8                m_byEncryptBits;	        //enum emEncryptType
	emH239RoleLabel   m_nSupportH239Type;         //֧��H.239������
    BOOL32            m_bSupportRSVP;           //�Ƿ�֧��RSVP����
	BOOL32            m_bSupportActiveH263Plus; //�Ƿ�֧��H.263+
    u8                m_byFECBits;              //ǰ�����


    //H.264 ����
    TKdvH264VideoCap  m_atH264Cap[MAX_H264CAP_NUM];
	u8			      m_awH264ToSubId[MAX_CAPTABLE_SIZE]; //H264 payload id �� sub id ӳ���
	u8				  m_byH264SubId;
	u32               m_dwH264NALMode;  //H264 mediaPacketization mode,it could be emNALSingle, emNALInterleaved or emNALNonInterleaved

	TKdvAudioCap	  m_tG719; 
	
	TKdvOpusCap		  m_tOpusCap;	
	TKdvG7221Cap	  m_tG7221;		

	//H.265
	TKdvH265VideoCap  m_atH265Cap[MAX_H265CAP_NUM];
	u8				  m_awH265ToSubId[MAX_CAPTABLE_SIZE]; //H265 payload id �� sub id ӳ���
	u8				  m_byH265SubId;

public:
	TKdv323CapSet()
	{
		Clear();
	}

	void Clear();

    void host2net(BOOL32 bhton);

    //����֧��RSVP����
    void SetSupportRSVP(BOOL32 bSupportRSVP)
    {
        m_bSupportRSVP = bSupportRSVP;
    }
    //�Ƿ�֧��RSVP
    BOOL32 IsSupportRSVP()
    {
        return m_bSupportRSVP;
    }

	//����֧��RSVP����
    void SetSupportActiveH263(BOOL32 bSupport)
    {
        m_bSupportActiveH263Plus = bSupport;
    }
    //�Ƿ�֧��RSVP
    BOOL32 IsSupportActiveH263()
    {
        return m_bSupportActiveH263Plus;
    }
    //����ǰ���������
    void SetFECType(u8 emType)
    {
        m_byFECBits = emType;
    }
    //��ȡǰ���������
    u8 GetFECType() const
    {
        return m_byFECBits;
    }
    /*�ϲ���ʱ��ʹ��*/
    void SetSupportH239Type(s32 nSupporth239)
    {
        m_nSupportH239Type = (emH239RoleLabel)nSupporth239;
    }
    s32 GetSupportH239Type()
    {
        return m_nSupportH239Type;
    }

    //modified for h265 [20141124]
    //�����������������H.264����H.265��������⴫��SetH264VideoCap��SetH265VideoCapʱ��Ӧ�������±�bySubId
	BOOL32 SetCapDesc(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex, u16 wPayload, u8 bySubId = 0);
	
	void SetCapDescId(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex, u16 capId);
    //�õ�������    
	u16 GetCapDescId(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex);
   
    BOOL32 IsExistsimultaneous(u16 *pwPayload, s32 nNum, TKdvH264VideoCap* ptH264Cap=NULL, TKdvH265VideoCap* ptH265Cap=NULL,TKdvAACCap *ptAacCap = NULL );
	
	//�õ�������
	u16 GetCapFromTable(u8 byCapIndex)
	{
		if(byCapIndex >= MAX_CAPTABLE_SIZE)
			return 0;
		return m_awCapTable[byCapIndex];
	}

	void SetCapToTable(u8 byCapIndex, u16 wPayload)
	{
		if(byCapIndex >= MAX_CAPTABLE_SIZE)
			return;
		m_awCapTable[byCapIndex] = wPayload;
	}

    //������Ƶ������.������H.264��H.265
	BOOL32 SetVideoCap(TKdvVideoCap &tVideoCap, u16 wPayload);

    //�õ���Ƶ������.������H.264��H.265
    TKdvVideoCap* GetVideoCap(u16 wPayload);

    //����H.264��Ƶ������,����ֵ��byH264SubId,��SetCapDescʱ��
    u8 SetH264VideoCap(TKdvH264VideoCap &tVideoCap);

    //�õ�H.264��Ƶ������
    TKdvH264VideoCap* GetH264VideoCap(u8 bySubId);
  
    //�õ�H264����
	u8 GetH264Num()
	{
		return m_byH264SubId;
	}

	//����H.265��Ƶ������,����ֵ��byH265SubId,��SetCapDescʱ��
    u8 SetH265VideoCap(TKdvH265VideoCap &tVideoCap);

	//�õ�H.265��Ƶ������
    TKdvH265VideoCap* GetH265VideoCap(u8 bySubId)
    {
        if (bySubId >= MAX_H265CAP_NUM)
        {
            return NULL;
        }
        return &(m_atH265Cap[bySubId]);
    }

	//�õ�H265����
	u8 GetH265Num()
	{
		return m_byH265SubId;
	}

	//������G7231/AAC/opus
	TKdvAudioCap* GetAudioCap(u16 wPayload);

	//������G7231/AAC/opus/G7221
	BOOL32 SetAudioCap(TKdvAudioCap &tAudioCap, u16 wPayload);

	//G7231
	TKdvG7231Cap* GetG7231Cap()
	{	
		return &m_tG7231;
	}
	//G7231
	BOOL32 SetG7231Cap(TKdvG7231Cap &tG7231Cap)
	{
		m_tG7231 = tG7231Cap;
		return TRUE;
	}
    //AAC
    TKdvAACCap* GetAACCap(u16 wPayload);

    //AAC
    BOOL32 SetAACCap(TKdvAACCap &tAudioCap, u16 wPayload);
   	
	//Opus
	TKdvOpusCap* GetOpusCap()
	{	
		return &m_tOpusCap;
	}
	BOOL32 SetOpusCap(TKdvOpusCap &tOpusCap)
	{
		m_tOpusCap = tOpusCap;
		return TRUE;
	}
	//G7221
	TKdvG7221Cap* GetG7221Cap()
	{	
		return &m_tG7221;
	}
	//G7221
	BOOL32 SetG7221Cap(TKdvG7221Cap &tG7221Cap)
	{
		m_tG7221 = tG7221Cap;
		return TRUE;
	}

	TKdvDataCap* GetDataCap(u16 wPayload);

	BOOL32 SetDataCap(TKdvDataCap &tDataCap, u16 wPayload);

	/*�����ڷ���������ʱʹ��,��ʾͬʱ֧�ֵļ�������.
	 *��byEncryptBit=emEncryptTypeDES|emEncryptTypeAES;
	 */
	void SetEncryptBits( u8 byEncryptBits)
	{
		m_byEncryptBits = byEncryptBits;
	}
	u8 GetEncryptBits()
	{
		return m_byEncryptBits;
	}

	u8 GetH264SubId(u8 byCapIdex)
	{
		return m_awH264ToSubId[byCapIdex];
	}

	//add by hong for H.265
	u8 GetH265SubId(u8 byCapIndex)
	{
		return m_awH265ToSubId[byCapIndex];	
	}

	void SetH264NALMode(u32 dwNALMode)
	{
		m_dwH264NALMode = dwNALMode;
	}

	u32 GetH264NALMode()
	{
		return m_dwH264NALMode;
	}
	BOOL32 IsH265CapALessEqualB( const TKdvH265VideoCap & tH265A, const TKdvH265VideoCap & tH265B );

	BOOL32 IsH264CapALessEqualB( const TKdvH264VideoCap & tH264A, const TKdvH264VideoCap & tH264B );

/*====================================================================
  �� �� ���� FindH264PeerBestSupport
  ��    �ܣ� ����ĳһ�ֱ����¶Զ���������֧�ֵ����֡�ʵ�TKdvH264VideoCap�ṹ��
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� u16 *pwPayload     payload����
             s32 nNum           payload�����С
			 OUT BOOL &bStatic  ���ص�TKdvH264VideoCap�ṹ�����Ƿ����staticMaxBPS
			 s32 nFirstPtIndex    ��һ·��Ƶ��payload�����е�����������һ·��h264Ϊ-1
			 s32 nSecondPtIndex   �ڶ�·��Ƶ��payload�����е����������޵ڶ�·Ϊ-1
			 TKdvH264VideoCap* ptH264Cap ����������
  �� �� ֵ�� BOOL ƥ��ɹ�TRUE ʧ��FALSE
  ��ע��1������TKdvH264VideoCap* ptH264Cap��INOUT���ͣ����Ǳ��㷨�з��ص�ptH264Cap��������һ������ֵ��Ч��
        ��Ϊֻ���ڵ�һ·�ɹ�����������²Ż᳢�Է��͵ڶ�·��������ptH264Cap[2]�е�ptH264Cap[0]��ֵ��
		�̶����Ƿ�ı䲻��ο���ptH264Cap[1]��ʾ�ڶ�·ƥ��ɹ���ֵ
		2������������H264������֧��
		3�������ڵ���IsExistsimultaneous()ʧ�ܵ�����µ��ñ�����
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  20100830      1.0		    ������                   ����
======================================================================*/
	BOOL32 FindH264PeerBestSupport( u16 *pwPayload, s32 nNum, OUT BOOL32 &bStatic, s32 nFirstPtIndex = -1, s32 nSecondPtIndex = -1, INOUT TKdvH264VideoCap* ptH264Cap = NULL );
	
	BOOL32 FindH265PeerBestSupport( u16 *pwPayload, s32 nNum, s32 nFirstPtIndex = -1, s32 nSecondPtIndex = -1, INOUT TKdvH265VideoCap* ptH265Cap = NULL );
private:
	//�������������������Ϊ H.264����Ҫ����TKdvH264VideoCap�����±꣬����ֵΪpayload��captable�е�����ֵ
	//bySubId ������h264��Ҳ������h265�ģ�����ʵ���������
	u16 AddCapToTable(u16 wPayload, u8 bySubId);

	BOOL32 IsInterExistsimultaneous( u16 *pwPayload, s32 nNum, TKdvH264VideoCap* ptH264Cap=NULL, s32 nH264Num=0, TKdvH265VideoCap* ptH265Cap=NULL, s32 nH265Num=0, TKdvAACCap* ptAacCap = NULL );

    BOOL32 FindH264VideoCap(TKdvH264VideoCap& tH264VideoCap, u8& bySubId);

	BOOL32 FindH265VideoCap(TKdvH265VideoCap& TKdvH265VideoCap, u8& bySubId);
}PACKED;

#ifdef WIN32
#pragma pack( pop )
#endif

PROTO_EXTERN_API u16	GetEType	( IN u16 wType, IN u8 byEBits);
PROTO_EXTERN_API u16	GetH239Type	( IN u16 wType );
PROTO_EXTERN_API BOOL32	IsH239Type	( IN u16 wType );

#endif

