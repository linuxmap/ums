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
#define MAX_SIMUCAP_NUM     (u16)16					//max 256 (Codian为13)
#define MAX_DESCAP_NUM      (u16)5					//max 256 (抓包发现都是1，很少有2以上)
#define MAXBITRATE_H261     (u16)19200				//单位100bps
#define MAXBITRATE_H263     (u32)192400				//单位100bps

// guzh [9/25/2007] 前向纠错类型
enum emFECType
{
    emFECNone		= 0x00,
	emFECRaid5		= 0x01,
	emFECRaid6		= 0x02,
	emFECNonStd		= 0x04 //公司自己的NsmFec add by shigubin 20130228
};

//roleLabel 值 [20140829]
enum emH239RoleLabel 
{
	H239Role_NotSupport				= 0,		//不支持h239
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
	#define PACKED __attribute__ ((packed))	// 取消编译器的优化对齐
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

//音频能力集，不包括G.7231
struct PROTO_API TKdvAudioCap : public TKdvCapSet
{
	u8   m_byPackTime;     //每一RTP包的最大时长,单位ms(1-256); 

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

    //设置打包时间
	void SetPackTime(u8 byPackTime)
	{
		m_byPackTime = byPackTime;
	}
    //获取打包时间
	u8  GetPackTime()
	{
		return m_byPackTime;
	}

	// interfaces merged from H.323
	void host2net(BOOL32 bhton);
}PACKED;

//G7231的能力集
struct PROTO_API TKdvG7231Cap : public TKdvAudioCap
{
	u8				m_byMaxFrameNum;		//单包最大的帧数
	BOOL32			m_bSilenceSuppression;	//是否静音抑制

public:
	TKdvG7231Cap():TKdvAudioCap()
	{
		m_byMaxFrameNum  = 1;			    //目前我们只支持单帧
		m_bSilenceSuppression = TRUE;
	}

	void Clear()
	{
		m_byMaxFrameNum  = 1;			    //目前我们只支持单帧
		m_bSilenceSuppression = TRUE;	    //我们默认支持静音抑制
		TKdvAudioCap::Clear();
	}

    //设置是否支持静音
    void SetIsSilenceSuppression(BOOL32 bSilenceSuppression)
    {
        m_bSilenceSuppression = bSilenceSuppression;
    }
    //是否支持静音
	BOOL32 IsSilenceSuppression()
	{
		return m_bSilenceSuppression;
	}
    
    //设置每包的最大帧数
	void SetMaxFrameNumPerPack(u8 byMaxFrameNum)
	{
		m_byMaxFrameNum = byMaxFrameNum;
	}
    //获取每包的最大帧数
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
	
    //设置rate
	void SetRateType( u8 byRateType )
	{
		m_byBitRateType = byRateType;
	}
	void OrRateType( emG7221Rate emRateType )
	{
	    m_byBitRateType = (m_byBitRateType | emRateType);
	}

	//获取rate
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

//MPEG AAC能力集
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
        emChnl1      = 1,                   //单声道
        emChnl2      = 2,                   //双声道
        emChnl3      = 3,					//单、双都支持
        emChnl4      = 4,
        emChnl5      = 5,
        emChnl5dot1  = 6,                   //5.1声道
        emChnl7dot1  = 7                    //7.1声道
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
        m_byMaxFrameNum = 1;			    //目前我们只支持单帧
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

/*********************关于帧率的设置******************
*1表示29.97, 2表示29.97/2, 3表示29.97/3,.....
*H261：cif(1-4) qcif(1-4)
*H263  sqcif,qcif,cif,4cif,16cif  (1-32)
*****************************************************/
//视频能力集
struct PROTO_API TKdvVideoCap : public TKdvCapSet
{
	u16         m_wMaxBitRate;						//单位kbps
	u8          m_abyResolution[emResolutionEnd];	//帧率 
    PayloadType	m_emPayloadType;  //重复定义了

public:
	TKdvVideoCap()
	{
	    Clear();
	}

	void Clear();

	//单位kbps
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

//H.264视频能力集
/*********************关于帧率的设置******************
*1表示1fps, 60代表60fps，最大允许帧率可以达到理论值255
*****************************************************/
struct PROTO_API TKdvH264VideoCap:public TKdvVideoCap
{
protected:
    // H.264 参数定义，参见 ITU H.241文档
    u8              m_byProfile;
    u8              m_byLevel;
    // 以下2个字段，取 Custom 与Level值默认的 max(单位均为宏块)
    s32             m_nMaxMBPS;
    s32             m_nMaxFS;
    // 以下保存的是绝对 Custom 的字段（暂时不支持设置）
    s32             m_nMaxDPB;
    s32             m_nMaxBRandCPB;
    s32             m_nMaxStaticMBPS;
	
	// 以下是标志字段,如果参数偏大相应位置位
	s32             m_nParaFlag;
	
	//svc
	u8				m_byAdditionalModes;

	emH264NALMode   m_emH264NALMode;
	
public:
	BOOL32          m_bOld264Level;
	BOOL32			m_bUsed;

public:
    // 协议 
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

	// 协议: 支持 emH264ProfileMask 各个参数和它们的逻辑与
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
    
	// 能力集操作
	/*
 	 *function: 获取特定分辨率下的帧率
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
	 *return:   u8 帧率 frame/s
	 */
    u8   GetResolution(emResolution emRes) const;
    u8   GetResolution(u16 wWidth, u16 wHeight) const;

	/*
	 *function: 特定分辨率下，特定帧率(对于场模式，需要上层转化为帧率传入)是否支持
                至于对端是否支持场格式，要业务根据 IsSupportProfile 自行判断 
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
                u8 byFps                    帧率frame/s
     *return:   TRUE/FALSE
	 */
    BOOL32 IsSupport(emResolution emRes, u8 byFps) const;
    BOOL32 IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/*
	 *function: 设置支持某种分辨率和帧率(对于场模式，需要上层转化为帧率传入)。多种分辨率可以叠加设置
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
                u8 byFps                    帧率frame/s
	 */
    void  SetResolution(emResolution emRes, u8 byFps) ;
    void  SetResolution(u16 wWidth, u16 wHeight, u8 byFps) ;

    // 内部使用函数
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

    //  Level，外部调用无效
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

    // 能力集操作
     /*
	 *function: 获取特定分辨率下的帧率
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
     *return:   u8 帧率 frame/s
	 */
    u8		GetResolution(emResolution emRes) const;
    u8		GetResolution(u16 wWidth, u16 wHeight) const;

	/*
	 *function: 特定分辨率下，特定帧率(对于场模式，需要上层转化为帧率传入)是否支持
                至于对端是否支持场格式，要业务根据 IsSupportProfile 自行判断 
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
                u8 byFps                    帧率frame/s
     *return:   TRUE/FALSE
	 */
    BOOL32	IsSupport(emResolution emRes, u8 byFps) const;
    BOOL32	IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/*
	 *function: 设置支持某种分辨率和帧率(对于场模式，需要上层转化为帧率传入)。多种分辨率可以叠加设置
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
                u8 byFps                    帧率frame/s
	 */
    void	SetResolution(emResolution emRes, u8 byFps) ;
    void	SetResolution(u16 wWidth, u16 wHeight, u8 byFps) ;

	
	// 协议: 支持 emH265ProfileMask 各个参数和它们的逻辑与
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
	u32   m_dwMaxBitRate;					//单位kbps; 
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

	//单位kbps
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
* 能力集结构
* 目前的视频支持:h261,h263,h264,mpeg4,h263+,h262
* 目前的音频支持:G711u(64k),G711a(64k),G722(64k),G7231,G728,G729,G7221C,MP3,MP2AAC,MP4AAC.
* 
* guzh [12/17/2007] 调整结构
* guzh [04/03/2008] 调整结构
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

    /*载荷类型的内部转换:
    |<--------------加密和H239的载荷转换---------- >|<低字节为上层使用的类型>|
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +  0  +  0  +  0  +  0  +  1  +  1  +  1  +  1  +  payloadType           +             
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            + H239+ AES + DES +NoEnc+   
    */
	u8                m_byEncryptBits;	        //enum emEncryptType
	emH239RoleLabel   m_nSupportH239Type;         //支持H.239的类型
    BOOL32            m_bSupportRSVP;           //是否支持RSVP功能
	BOOL32            m_bSupportActiveH263Plus; //是否支持H.263+
    u8                m_byFECBits;              //前向纠错


    //H.264 能力
    TKdvH264VideoCap  m_atH264Cap[MAX_H264CAP_NUM];
	u8			      m_awH264ToSubId[MAX_CAPTABLE_SIZE]; //H264 payload id 到 sub id 映射表
	u8				  m_byH264SubId;
	u32               m_dwH264NALMode;  //H264 mediaPacketization mode,it could be emNALSingle, emNALInterleaved or emNALNonInterleaved

	TKdvAudioCap	  m_tG719; 
	
	TKdvOpusCap		  m_tOpusCap;	
	TKdvG7221Cap	  m_tG7221;		

	//H.265
	TKdvH265VideoCap  m_atH265Cap[MAX_H265CAP_NUM];
	u8				  m_awH265ToSubId[MAX_CAPTABLE_SIZE]; //H265 payload id 到 sub id 映射表
	u8				  m_byH265SubId;

public:
	TKdv323CapSet()
	{
		Clear();
	}

	void Clear();

    void host2net(BOOL32 bhton);

    //设置支持RSVP功能
    void SetSupportRSVP(BOOL32 bSupportRSVP)
    {
        m_bSupportRSVP = bSupportRSVP;
    }
    //是否支持RSVP
    BOOL32 IsSupportRSVP()
    {
        return m_bSupportRSVP;
    }

	//设置支持RSVP功能
    void SetSupportActiveH263(BOOL32 bSupport)
    {
        m_bSupportActiveH263Plus = bSupport;
    }
    //是否支持RSVP
    BOOL32 IsSupportActiveH263()
    {
        return m_bSupportActiveH263Plus;
    }
    //设置前向纠错类型
    void SetFECType(u8 emType)
    {
        m_byFECBits = emType;
    }
    //获取前向纠错类型
    u8 GetFECType() const
    {
        return m_byFECBits;
    }
    /*上层暂时不使用*/
    void SetSupportH239Type(s32 nSupporth239)
    {
        m_nSupportH239Type = (emH239RoleLabel)nSupporth239;
    }
    s32 GetSupportH239Type()
    {
        return m_nSupportH239Type;
    }

    //modified for h265 [20141124]
    //设置能力集。如果是H.264或者H.265，则需额外传入SetH264VideoCap、SetH265VideoCap时对应的数组下标bySubId
	BOOL32 SetCapDesc(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex, u16 wPayload, u8 bySubId = 0);
	
	void SetCapDescId(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex, u16 capId);
    //得到能力级    
	u16 GetCapDescId(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex);
   
    BOOL32 IsExistsimultaneous(u16 *pwPayload, s32 nNum, TKdvH264VideoCap* ptH264Cap=NULL, TKdvH265VideoCap* ptH265Cap=NULL,TKdvAACCap *ptAacCap = NULL );
	
	//得到能力表
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

    //设置视频能力集.不包括H.264、H.265
	BOOL32 SetVideoCap(TKdvVideoCap &tVideoCap, u16 wPayload);

    //得到视频能力集.不包括H.264、H.265
    TKdvVideoCap* GetVideoCap(u16 wPayload);

    //设置H.264视频能力集,返回值是byH264SubId,调SetCapDesc时用
    u8 SetH264VideoCap(TKdvH264VideoCap &tVideoCap);

    //得到H.264视频能力集
    TKdvH264VideoCap* GetH264VideoCap(u8 bySubId);
  
    //得到H264个数
	u8 GetH264Num()
	{
		return m_byH264SubId;
	}

	//设置H.265视频能力集,返回值是byH265SubId,调SetCapDesc时用
    u8 SetH265VideoCap(TKdvH265VideoCap &tVideoCap);

	//得到H.265视频能力集
    TKdvH265VideoCap* GetH265VideoCap(u8 bySubId)
    {
        if (bySubId >= MAX_H265CAP_NUM)
        {
            return NULL;
        }
        return &(m_atH265Cap[bySubId]);
    }

	//得到H265个数
	u8 GetH265Num()
	{
		return m_byH265SubId;
	}

	//不包含G7231/AAC/opus
	TKdvAudioCap* GetAudioCap(u16 wPayload);

	//不包含G7231/AAC/opus/G7221
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

	/*仅用于发送能力集时使用,表示同时支持的加密能力.
	 *如byEncryptBit=emEncryptTypeDES|emEncryptTypeAES;
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
  函 数 名： FindH264PeerBestSupport
  功    能： 返回某一分辨率下对端能力集所支持的最大帧率的TKdvH264VideoCap结构体
  算法实现： 
  全局变量： 
  参    数： u16 *pwPayload     payload数组
             s32 nNum           payload数组大小
			 OUT BOOL &bStatic  返回的TKdvH264VideoCap结构体中是否包含staticMaxBPS
			 s32 nFirstPtIndex    第一路视频在payload数组中的索引，若第一路非h264为-1
			 s32 nSecondPtIndex   第二路视频在payload数组中的索引，若无第二路为-1
			 TKdvH264VideoCap* ptH264Cap 能力集数组
  返 回 值： BOOL 匹配成功TRUE 失败FALSE
  备注：1、参数TKdvH264VideoCap* ptH264Cap是INOUT类型，但是本算法中返回的ptH264Cap数组仅最后一个索引值有效，
        因为只有在第一路成功发起的条件下才会尝试发送第二路，故数组ptH264Cap[2]中的ptH264Cap[0]的值已
		固定，是否改变不予参考，ptH264Cap[1]表示第二路匹配成功的值
		2、本函数仅对H264能力集支持
		3、建议在调用IsExistsimultaneous()失败的情况下调用本函数
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  20100830      1.0		    王晓意                   创建
======================================================================*/
	BOOL32 FindH264PeerBestSupport( u16 *pwPayload, s32 nNum, OUT BOOL32 &bStatic, s32 nFirstPtIndex = -1, s32 nSecondPtIndex = -1, INOUT TKdvH264VideoCap* ptH264Cap = NULL );
	
	BOOL32 FindH265PeerBestSupport( u16 *pwPayload, s32 nNum, s32 nFirstPtIndex = -1, s32 nSecondPtIndex = -1, INOUT TKdvH265VideoCap* ptH265Cap = NULL );
private:
	//往能力表添加能力项。如果为 H.264则需要传入TKdvH264VideoCap数组下标，返回值为payload在captable中的索引值
	//bySubId 可以是h264的也可以是h265的，根据实际情况填入
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

