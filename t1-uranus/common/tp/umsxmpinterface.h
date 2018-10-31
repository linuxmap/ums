#ifndef _UMS_XMPU_INTERFACE_
#define _UMS_XMPU_INTERFACE_

#include "tpcommontype.h"
#include "tpcommonstruct.h"
#include "tpsys.h"
#include "umsinnerstruct.h"

#define XMPU_MAX_VMP_NUM		32	//合成器Eqp最大数量
#define XMPU_MAX_BAS_NUM		64	//适配器Eqp最大数量
#define XMPU_MAX_AUDMIX_NUM		32 // 混音器Eqp最大数量
#define  XMPU_AUDMIX_N1_NUM  64		// 混音器最大通道数量
#define  XMPU_AUD_BAS_MAX_CHN  16*7 //音频视频器Eqp最大数量

// 从10000 到 40000，用于外设板卡
//以下 将20000-22000之间的端口空出来，因为有其他底层模块可能会占用
#define XMPU_BAS_BEGIN_PORT		10600	//每个板子使用100个端口，最大共64个板子 共6400  到17000
#define XMPU_VMP_BEGIN_PORT		22000	//每个板子使用250个端口，最大共32个板子  共8000   到30000
#define XMPU_AUD_MIX_BEGIN_PORT	30000	//每个混音器150个，32个混音器 共占用4800 到 35000		
#define XMPU_AUD_BAS_BEGIN_PORT	35000	//每个适配器占用40个，16*7个适配器，共占用4480     到39480

#define XMPU_EQP_ID_VMP_BEG		10
#define XMPU_EQP_ID_VMP_END		41

#define XMPU_EQP_ID_BAS_BEG		42
#define XMPU_EQP_ID_BAS_END		105

#define XMPU_EQP_ID_AUD_MIX_BEG		106
#define XMPU_EQP_ID_AUD_MIX_END		137

#define XMPU_EQP_ID_AUD_BAS_BEG		138
#define XMPU_EQP_ID_AUD_BAS_END		250


typedef struct tagTXmpuMettingInfo
{
	u16							m_wConfID;
	s8								m_achConfName[TP_MAX_ALIAS_LEN+1];	//会议名称
	s8								m_achConfE164[TP_MAX_ALIAS_LEN+1];	//会议e164
	TUmsVidFormat		m_tFormat;
	u32							m_dwMaxMtNum;
	BOOL32					m_bNeedVidBas;
	BOOL32					m_bNeedAudBas;

	s8								m_abyMqUrl[TP_MAX_ALIAS_LEN];
	s8								m_abyMoid[TP_MAX_ALIAS_LEN];
	tagTXmpuMettingInfo()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTXmpuMettingInfo));
	}
}TXmpuMettingInfo;

typedef struct tagTXmpuEqpRes
{
	u32 m_dwEqpID;
	tagTXmpuEqpRes()
	{
		m_dwEqpID = 0;
	}

}TXmpuEqpRes;

typedef struct tagTXmpuEqpParam
{
	EMXmpuEqpType m_emEqpType;
	TXmpuEqpRes*		m_ptEqp;
	tagTXmpuEqpParam()
	{
		Clear();
	}

	void Clear()
	{
		m_emEqpType = em_Xmpu_unknow;
		m_ptEqp = NULL;
	}
}TXmpuEqpParam;

//xmpu合成参数
typedef struct tagTXmpuVmpParam:public TXmpuEqpParam
{
	u16				m_wConfID;
	EMVmpStyle		m_emVmpStyle;
	EmUmsVmpStyle	m_emVmpTpStyle;
	u32_ip			m_dwMediaIp;

	u8				m_byVMPMemberNum;	  //当前合成成员数目
	TTPVMPMember	m_atVMPMember[TP_VMP_MAX_IN_CHN_NUM]; //画面合成成员
	u8				m_byOutMemBerNum;
	TUmsVidFormat	m_atVMPOutMember[TP_VMP_MAX_OUT_CHN_NUM];

	// 以下为出参
	TTPTransAddr	m_atDecMiddleRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码通道中转rtp rcv
	TTPTransAddr	m_atDecRtcpAddr[TP_VMP_MAX_IN_CHN_NUM];  // vmp解码通道 back rtcp rcv
	TTPTransAddr	m_atEncRtpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv

	u8				m_byVipMaxStyle; // 最大几(4)风格下，全前适配通道
	u8				m_byVipNum;		// 超过几(4)风格，存在的前适配通道数量
	tagTXmpuVmpParam()
	{
		m_emVmpStyle = tp_VmpStyle_DYNAMIC;
		m_emVmpTpStyle = em_ums_vmp_invalid;
		m_wConfID = TP_INVALID_INDEX;
		m_dwMediaIp = 0;
		m_emEqpType = em_Xmpu_unknow;
		m_byVMPMemberNum = 0;
		m_byOutMemBerNum = 0;

		memset(m_atVMPMember, 0, sizeof(m_atVMPMember));
		memset(m_atVMPOutMember, 0, sizeof(m_atVMPOutMember));
		memset(m_atDecMiddleRtpAddr, 0, sizeof(m_atDecMiddleRtpAddr));
		memset(m_atDecRtcpAddr, 0, sizeof(m_atDecRtcpAddr));
		memset(m_atEncRtpAddr, 0, sizeof(m_atEncRtpAddr));
		memset(m_atEncMiddleRtcpAddr, 0, sizeof(m_atEncMiddleRtcpAddr));

		m_byVipMaxStyle = 0;
		m_byVipNum = 0;
	}

}TXmpuVmpParam;


//xmpu视频适配参数
typedef struct tagTXmpuBasParam:public TXmpuEqpParam
{
	u16				m_wConfID;
	u32_ip			m_dwMediaIp;
	u16				m_wEncAbility;

	TTPBasVidParam m_tBasParam;    // 后适配通道参数
	TUmsVidFormat  m_tMaxBasParam; // 前适配最大参数

	u16	m_wStaticPayload; // 静态载荷
	u16 m_wDynamicPayload; // 动态载荷
	TTPEncrypt m_tEncrypt;// 加密参数

	//以下为出参
	TTPTransAddr	m_tDecMiddleRtpAddr;// 中转地址
	TTPTransAddr	m_tDecRtcpAddr;
	
	TTPTransAddr	m_atEncRtpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp编码中转通道地址

	tagTXmpuBasParam()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_dwMediaIp = 0;
		m_wEncAbility = 0;
		m_emEqpType = em_Xmpu_unknow;
		memset(&m_tBasParam, 0, sizeof(m_tBasParam));
		memset(&m_tMaxBasParam, 0, sizeof(m_tMaxBasParam));
		m_wStaticPayload = 0;
		m_wDynamicPayload = 0;
		m_tEncrypt.Clear();
	}

}TXmpuBasParam;

//xmpu视频适配参数
typedef struct tagTXmpuChgBasInfo
{
	u32				m_dwEqpID;
	u16				m_wConfID;

	TTPBasVidParam m_tBasParam;    // 后适配通道参数

	u16	m_wStaticPayload; // 静态载荷
	u16 m_wDynamicPayload; // 动态载荷
	TTPEncrypt m_tEncrypt;// 加密参数

	tagTXmpuChgBasInfo()
	{
		m_dwEqpID = 0;
		m_wConfID = TP_INVALID_INDEX;
		memset(&m_tBasParam, 0, sizeof(m_tBasParam));
		m_wStaticPayload = 0;
		m_wDynamicPayload = 0;
		m_tEncrypt.Clear();
	}

}TXmpuChgBasInfo;

//xmpu混音参数
typedef struct tagTXmpuMixParam:public TXmpuEqpParam
{
	u16				m_wConfID;
	u32_ip			m_dwMediaIp;

	u8				m_byChanNum;
	u8				m_byMixDepth;
	u8				m_byNNum;
	TUmsAudFormat	m_atAudFmt[UMS_AUDMIX_N_OUT_NUM];
	TTPEncrypt      m_tEncrypt;

	//下面地址为出参
	TTPTransAddr	m_atNEncRtpAddr[UMS_AUDMIX_N_OUT_NUM];
	// N出中专地址
	TTPTransAddr	m_atNEncMiddleRtcpAddr[UMS_AUDMIX_N_OUT_NUM]; // N出编码通道地址
	// N-1路中转地址
	TTPTransAddr	m_atDecMiddleRtpAddr[TP_APU2_MAX_CHAN_NUM];  // N-1出解码
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_APU2_MAX_CHAN_NUM]; // N-1出编码
	tagTXmpuMixParam()
	{
		memset(this, 0, sizeof(tagTXmpuMixParam));
	}

}TXmpuMixParam;

typedef struct tagTXmpuMixMember
{
	u32				m_dwEqpID;
	u8				m_byIndex;
	u16				m_wEpID;
	u16				m_wScreenIndex;
	TTPTransAddr	m_tLocalRtpRcv;
	TTPTransAddr	m_tLocalRtcpRcv;

	EmTpAudioFormat     m_emAudFormat;

	//  n-1所出的音频格式
	EmTpAudioFormat     m_emOutAudFormat;	

	TTPEncrypt      m_tEncrypt;

	tagTXmpuMixMember()	{	Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTXmpuMixMember));
		m_emAudFormat = emTPAEnd;
		m_emOutAudFormat = emTPAEnd;
		m_wScreenIndex = TP_INVALID_INDEX;
	}
}TXmpuMixMember;

//xmpu合成参数
typedef struct tagTXmpuAudBasParam:public TXmpuEqpParam
{
	u32_ip						m_dwMediaIP;
	u16							m_wConfID;
	TUmsAudFormat		m_tAudDec;
	TUmsAudFormat		m_atAudEnc[AUD_BAS_MAX_OUT_CHNL_NUM];
	TTPEncrypt				m_tEncrypt;

	//以下为出参
	TTPTransAddr			m_tDecMiddleRtpAddr;//解码中转地址
	TTPTransAddr			m_tDecRtcpAddr;

	TTPTransAddr			m_atEncRtpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr			m_atEncMiddleRtcpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv
	tagTXmpuAudBasParam()
	{
		memset(this, 0, sizeof(tagTXmpuAudBasParam));

		m_tAudDec.Clear();
		m_tAudDec.m_emFormat = emTPAEnd;

		for (u16 wIndex = 0; wIndex < AUD_BAS_MAX_OUT_CHNL_NUM;++wIndex)
		{
			m_atAudEnc[wIndex].Clear();
			m_atAudEnc[wIndex].m_emFormat = emTPAEnd;
		}
	}

}TXmpuAudBasParam;

typedef struct tagTXmpuChgAudParam
{
	u32							m_dwEqpID;
	TUmsAudFormat		m_tAudDec;
	EmTpAudioFormat		m_aemEncFormat[AUD_BAS_MAX_OUT_CHNL_NUM];
	TTPEncrypt				m_tEncrypt;

	tagTXmpuChgAudParam()
	{
		memset(this, 0, sizeof(tagTXmpuChgAudParam));
		m_tAudDec.Clear();
		m_tAudDec.m_emFormat = emTPAEnd;
		for(u16 wIndex = 0;wIndex < AUD_BAS_MAX_OUT_CHNL_NUM;++wIndex)
		{
			m_aemEncFormat[wIndex] = emTPAEnd;

		}
	}

}TXmpuChgAudParam;

typedef struct tagTXmpuVmpMdyInfo
{
	u32					m_dwEqpID;
	BOOL32			m_bSuccess;

	u8					m_byDecNum;	  //当前合成成员数目
	TTPTransAddr	m_atDecRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码通道rtp rcv

	u8					m_byEncNum;
	TTPTransAddr	m_atEncRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv

	tagTXmpuVmpMdyInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTXmpuVmpMdyInfo));
	}
}TXmpuVmpMdyInfo;

typedef struct tagTXmpuVmpNty
{
	u8			m_byNum;
	u32		m_adwEqpID[XMPU_MAX_VMP_NUM];			//EqpID
	s8			m_aachEqpAlias[XMPU_MAX_VMP_NUM][TP_MAXLEN_EQP_ALIAS+1];//外设别名

	BOOL32  m_bIncrease;
	
	tagTXmpuVmpNty()
	{
		Clear();
	}
	void Clear()
	{
		m_byNum = 0;
		memset(m_adwEqpID, 0, sizeof(m_adwEqpID));
		memset(m_aachEqpAlias,0,sizeof(m_aachEqpAlias));

		m_bIncrease = FALSE;
	}
}TXmpuVmpNty;

typedef struct tagTXmpuStartBasNty
{
	u32					m_dwEqpID;
	BOOL32			m_bSuccess;

	TTPTransAddr	m_tDecRtpAddr;    // Bas解码通道rtp rcv

	u8					m_byEncNum;
	TTPTransAddr	m_atEncRtcpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // Bas编码通道rtcp rcv
	tagTXmpuStartBasNty()
	{
		Clear();
	}

	void Clear()
	{
		m_dwEqpID = 0;
		m_bSuccess = 0;
		m_tDecRtpAddr.Clear();
		m_byEncNum = 0;
		memset(m_atEncRtcpAddr, 0, sizeof(m_atEncRtcpAddr));
	}
}TXmpuStartBasNty;

typedef struct tagTXmpuSetBasEncNty
{
	u32				m_dwEqpID;
	u32				m_dwHandle;
	u8				m_byChnNum;
	BOOL32		m_abVaildChn[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	tagTXmpuSetBasEncNty()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_dwHandle = 0;
		m_byChnNum = 0;
		memset(m_abVaildChn, 0, sizeof(m_abVaildChn));
	}

}TXmpuSetBasEncNty;

typedef struct tagTXmpuStartAudBasNty
{
	u32					m_dwEqpID;
	BOOL32			m_bSuccess;

	TTPTransAddr	m_tDecRtpAddr;    // Bas解码通道rtp rcv
	TTPTransAddr	m_atEncRtcpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // Bas编码通道rtcp rcv
	tagTXmpuStartAudBasNty()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTXmpuStartAudBasNty));
	}
}TXmpuStartAudBasNty;

typedef struct tagTXmpuAudBasSynInfo
{
	u32			m_adwEqpID[TP_MAX_STREAMNUM];
	EMXmpuSynType m_emSynType;
	tagTXmpuAudBasSynInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(m_adwEqpID, 0, sizeof(m_adwEqpID));
		m_emSynType = em_Xmpu_SynIndex_End;
	}
}TXmpuAudBasSynInfo;

typedef struct tagTXmpuStartMixNty
{
	u32					m_dwEqpID;
	BOOL32			m_bSuccess;

	u8					m_byNum;
	TTPTransAddr	m_atNEncRtcpAddr[UMS_AUDMIX_N_OUT_NUM]; 
	tagTXmpuStartMixNty()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTXmpuStartMixNty));
	}
}TXmpuStartMixNty;

typedef struct tagTXmpuAddMixMemNty
{
	u32					m_dwEqpID;
	u8					m_byChnID;
	BOOL32			m_bSuccess;

	TTPTransAddr	m_tN1DecRtpAddr;
	TTPTransAddr	m_tN1EncRtcpAddr; 
	tagTXmpuAddMixMemNty()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTXmpuAddMixMemNty));
	}
}TXmpuAddMixMemNty;

typedef struct tagTForceActiveInfo
{
	u32			m_dwEqpID;
	u8			m_byChnID;
	BOOL32	m_bStart;

	tagTForceActiveInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTForceActiveInfo));
	}
}TForceActiveInfo;

typedef struct tagTXmpuVacActiveNty
{
	u32				m_dwEqpID;
	u8				m_byChnID;
	tagTXmpuVacActiveNty()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_byChnID = 0;
	}
}TXmpuVacActiveNty;

typedef struct tagTVoiceDetectionNty
{
	u32			m_dwEqpID;
	u8				m_byNum;
	u8				m_abyChanId[MAXNUM_MIXER_DEPTH];  // 有声音的通道索引数组
	tagTVoiceDetectionNty()
	{
		Clear();
	}
	void Clear()
	{
		m_dwEqpID = 0;
		m_byNum = 0;
		memset(m_abyChanId, 255, sizeof(m_abyChanId));
	}
}TVoiceDetectionNty;

typedef struct tagTXmpuMixSynInfo
{
	u32			m_adwEqpID[TP_MAX_STREAMNUM];
	u8			m_abyChanId[TP_MAX_STREAMNUM];
	EMXmpuSynType m_emSynType;

	tagTXmpuMixSynInfo()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++ wIndex )
		{
			m_adwEqpID[0] = 0xFF;
			m_abyChanId[0] = 0xFF;
		}
		m_emSynType = em_Xmpu_SynIndex_End;
	}
}TXmpuMixSynInfo;


void InitXmpuLib();
void regist_ums_xmpueqp_commond();

BOOL32 AssignXmpuEqp( TXmpuEqpParam* ptParam);

BOOL32 ReleaseXmpuEqp( TXmpuEqpParam* ptParam );

BOOL32 InitXmpuMeeting(TXmpuMettingInfo tInfo);

BOOL32 ReleaseXmpuMeeting(u32 wConfID);

BOOL32 InitMediaClient();

BOOL32 CheckIdleMediaSource(u16 wVmpNum = 0, u16 wMix8Num = 0, u16 wMix192Num = 0);

#endif // end of _UMS_XMPU_INTERFACE_