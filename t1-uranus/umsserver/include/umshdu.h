#ifndef _ums_hdu_h_
#define _ums_hdu_h_

#include "umsinnerstruct.h"
#include "tpcommontype.h"

#define INVALID_LAYER  10
#define INVALID_SLOT   7
#define INVALID_CHANNEL 2
#define HDU_PORT_SPAN	10
#define HDU_VMP_PORT_SPAN	20

//电视墙预案通道状态
enum EmHduChanStatus
{	
	em_hdu_chan_idle = 0,		//空闲
	em_hdu_chan_to_call,	//初始化call
	em_hdu_chan_to_hdu,		//初始化hdu
	em_hdu_chan_working,	//工作

	em_hdu_chan_invalid = 100,
};

typedef struct tagTPlayInfo
{
	u16		m_wConfID;		//会议ID
	u16		m_wDstID;
	s8      m_achAlias[TP_MAX_ALIAS_LEN+1];
	u16		m_wScreenNum;	//屏号
	EmViewEpType	m_emType;
	EmHduChanStatus	m_emStatus;	//通道状态

	tagTPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wDstID = TP_INVALID_INDEX;
		m_achAlias[0] = '\0';
		m_wScreenNum = TP_INVALID_INDEX;
		m_emType = EmEpType_Invalid;
		m_emStatus = em_hdu_chan_idle;
	}

	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_ALIAS_LEN);
		m_achAlias[TP_MAX_ALIAS_LEN] = '\0';
	}

	tagTPlayInfo& operator = (const tagTPlayInfo& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		memcpy(this, &tRhs, sizeof(tRhs));
		return *this;
	}

}TPlayInfo;

//////////////////////////////////////////////////////////////////////////
//重构电视墙  
//原因：对原有的通道进行了合成的支持，原有的封装存在扩展的问题
//方式：针对播放通道一层层的进行封装

class CHduEx;

class CHduChannelEx
{
public:
	CHduChannelEx();
	~CHduChannelEx();

public:
	void	Init(const THduChanInfo& tInfo);
	void	Clear();

public:
	void	GetCfgInfo(THduChanInfo& tInfo);
	u8		GetChanID() const { return m_byChanID; }
	BOOL32	IsVmpChan() const { return m_bVmpChan; }
	BOOL32  IsSameMode(u8 byMode) const {return m_bVmpChan == byMode;}
	void    SetVmpMode(u8 byMode) {m_bVmpChan = byMode;}

public:
	void	SetVol(u8 byVol) { m_byVol = byVol; }
	u8		GetVol() const { return m_byVol; }
	void	SetMute(BOOL32 bMute) { m_bMute = bMute; }
	BOOL32	IsMute() const { return m_bMute; }

public:
	BOOL32	ValidPlayInfo(u8 bySubChanIndex) const;
	void	SetChanStatus(u8 bySubChanIndex, EmHduChanStatus emStatus);
	void	SetPlayInfo(u8 bySubChanIndex, const TPlayInfo& tInfo);
	void	ClearPlayInfo(u8 bySubChanIndex);
	BOOL32	UseStatus() const;
	TPlayInfo	GetPlayInfo(u8 bySubChanIndex) const;
	EmHduChanStatus	GetChanStatus(u8 bySubChanIndex) const;

private:
	friend class CHduEx;

private:
	void	SetChanID(u8 byChanID) { m_byChanID = byChanID; }

private:
	BOOL32		m_bVmpChan;		//是否为合成通道
	u8			m_byChanID;
	u8			m_byVol;
	BOOL32		m_bMute;
	TPlayInfo	m_atPlayInfo[HDU_MAX_VMP_SUBCHAN];

private:
	EmHduOutPort	m_emOutPortType;	//接口类型
    EmHduOutMode	m_emOutModeType;	//输出制式
	EmHduZoomRate	m_emZoomRate;		//缩放比列
	EmHduShowMode	m_emShowMode;		//输出比例
};



class CHduEx
{
public:
	CHduEx();
	~CHduEx();

public:
	void	Init(const THduCfgInfo& tInfo);
	void	GetCfgInfo(THduCfgInfo& tInfo);

public:
	void	SetBrdInfo(const TTPBrdPos& tInfo);
	void	ClearBrdInfo();
	BOOL32	ValidBrd() const;
	BOOL32	BrdRegState() const { return m_bBrdReg; }
	void	UpdateBrdState(BOOL32 bReg) { m_bBrdReg = bReg; }
	u8		Layer() const { return m_byLayer; }
	u8		Slot() const { return m_bySlot; }
	u32		BrdIP() const { return m_dwIP; }
	EMBrdType BrdType() const { return m_emBrdType; }

public:
	void	SetServiceInfo(const THduChanInfo atInfo[], const TTPName& tName);
	void	ClearServiceInfo();
	BOOL32	ServiceRegState() const { return m_bServiceReg; }
	void	UpdateServiceState(BOOL32 bReg) { m_bServiceReg = bReg; }
	void	SetStartPort(u16 wPort) { m_wStartPort = wPort; }
	u16		GetStartPort() const { return m_wStartPort; }
	CHduChannelEx*	GetChannel(u8 byChanID);
	s8*		GetHduName()  { return m_tName.m_abyAlias; }

	BOOL32  IsHaveVmpChan();

public:
	void	GetCfgInfo(THduCfg& tInfo);
	void	Dump() const;

private:	//板子信息
	u8		m_byLayer;
	u8		m_bySlot;
	u32		m_dwIP;
	BOOL32	m_bBrdReg;
	EMBrdType  m_emBrdType;

private:	//业务信息
	BOOL32	m_bServiceReg;
	u16		m_wStartPort;
	TTPName	m_tName;
	CHduChannelEx	m_acChannel[HDU_MAX_CHANNEL_NUM];
};


typedef struct tagTHduPlayUnit
{
	CHduEx*			m_pcHdu;
	CHduChannelEx*	m_pcChannel;
	u16				m_wIndex;
	TTPName			m_tName;

	tagTHduPlayUnit()
	{
		m_pcHdu = NULL;
		m_pcChannel = NULL;
		m_wIndex = 0;
		m_tName.Clear();
	}

}THduPlayUnit;

class CHduPlan
{
public:
	CHduPlan();
	~CHduPlan();

public:
	void	Init(u8 byRow, u8 byCol, const THduPlayUnit atUnit[]);
	void	Clear();

public:
	u16				TotalChannel()  const { return m_byRow * m_byCol; }
	u8				RowNum() const { return m_byRow; }
	u8				ColNum() const { return m_byCol; }
	u16				GetValidNum() const;
	THduPlayUnit*	FindChannel(u8 byLayer, u8 bySlot, u8 byChanID);
	THduPlayUnit*	GetChannel(u16 wIndex);
	BOOL32			SetHduName(u16 wIndex,s8* pbyName);
	s8*				GetHduName(u16 wIndex);
public:
	void	Dump() const;
	
private:
	u8		m_byRow;
	u8		m_byCol;
	THduPlayUnit	m_atUnit[HDU_STYLE_MAX_NUM];
};

#endif