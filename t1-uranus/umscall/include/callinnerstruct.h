#ifndef _h_callinnerstruct_h__
#define _h_callinnerstruct_h__
#include "umscommonstruct.h"
#include "umsinnerstruct.h"
#include "tplistbuf.h"
#include "tplist.h"
#include "eqpinterface.h"
#include "umsapi.h"
#include "umsxmltype.h"
#include "tphandle.h"

#define TP_VIR_POLL_NODE_ID	TP_CONF_MAX_CNSNUM + 1

#define TP_JOINCONF_TIME 13

#define TP_MAX_OLD_KEY_NUM   6

//检查消息是否有主席权限
#define CheckMsgFromChair( pInst, wEpID ) (((pInst->chairID()) == (wEpID) && (pInst->IsChairConf())) ? TRUE : FALSE)
#define UMS_RECALL_TIME 30*1000
#define ForEachChanList(Num, par)	if( 1 == 1 )\
{											\
	s32 ewflag = 1;							\
	u16 ewIndex = 0;						\
	for (u16 iii = 1; iii <= Num; ++iii, ewflag *= -1)\
{\
	ewIndex = MIDSCREENINDEX + iii / 2 * ewflag;\
	par;\
}\
}\


#define PrintDsList(ListPtr) while (NULL != ListPtr){\
	msgprintnotime("      rcv("ADDRPORT_FORMAT"), send("ADDRPORT_FORMAT") \n"\
	, ADDRNET(ListPtr->m_tData.m_tRcvFromAddr), ADDRNET(ListPtr->m_tData.m_tSndToAddr));\
		ListPtr = ListPtr->m_ptNext; }

#define IsInSndRange(Index, SndNum)	(0 != SndNum && Index >= (MIDSCREENINDEX - SndNum / 2) && Index <= (MIDSCREENINDEX + SndNum / 2))

#define CAudRcvAddrList CTpListBuff<TTPMediaTransAddr>
#define CAudRcvAddrListItor TTPMediaTransAddr*

#define CMixerChnAddrList CTpListBuff<TTPMediaTransAddr>
#define CMixerChnAddrListItor TTPMediaTransAddr*

//向下级请求关键帧 类型
enum EmAskKeyType
{
	EmAskKeySpeaker,
	EmAskKeyChair,
	EmAskKeyBrdVmp,
	EmAskKeyGetVid,
	EmAskKeyPoll,
	EmAskKeySpeakerVmp
};

enum EmChanState
{
	EmChanIdle ,
	EmChanMaking,
	EmChanSecMaking,
	emChanOpen,
};

enum EmNodeType
{
	em_Node_Ep,
	em_Node_VirSpeak,
	em_Node_VirChair,
	em_Node_SpeakBas,
	em_Node_DualBas,
	em_Node_ChairBas,
	em_Node_Poll,
	em_Node_View,
	em_Node_ViewDown,
	em_Node_BaseBas,
	em_Node_Vmp,
	em_Node_Player,
	em_Node_RecMt,
	em_Node_RecConf,
};


#define CDsList CTpListBuff<TUmsDsData>
#define CDsListPtr CTpListBuff<TUmsDsData>::VectorDataPtr

class CDsListInfo
{
public:
    CDsListInfo()	:m_pHead(NULL),m_dwListNum(0) { }
    ~CDsListInfo()	{ }
	
	void Insert(CDsListPtr ptInsertNode);
	u32	GetElementNum()			{ return m_dwListNum; }
	CDsListPtr GetHead()		{ return m_pHead; }
	
	void Merger(CDsListInfo& tNewList, CDsListInfo& tDelList, CDsListInfo& tRepeatList, TUmsDsData tNeedAddList[], u16& wAddNum);
	
	void GetMediaTrans(TUmsDsData tDelDsData[MAX_CHANNEL_DS_NUM], u16& wDsNum);
	void SetMediaTrans(TUmsDsData tAddDsData[MAX_CHANNEL_DS_NUM], u16 wDsNum, CDsList* pNodeMgr);
	
	CDsListInfo& operator = (CDsListInfo& tRsData);
	void Clear();
private:    
    CDsListPtr		m_pHead;
	u32				m_dwListNum;
};

#ifdef _USE_XMPUEQP_
enum EmXmpuResStatInfo
{
	EmXmpuResStatInfo_Idle,   //
	EmXmpuResStatInfo_Starting, //正在开启，中间状态
	EmXmpuResStatInfo_Running, //正在工作
	EmXmpuResStatInfo_Error,  //异常
};

typedef struct tagtXmpuVidBasRes
{
	u16		m_dwEqpID;			//外设分配ID 初始化分配 永不修改
	u16	    m_wConfID;
	
	EmXmpuResStatInfo	m_emStat;			// 外设状态
	
	TTPTransAddr	m_tDecRtpAddr;
	TTPTransAddr	m_tDecRtcpAddr;
	TTPTransAddr	m_tDecMiddleRtpAddr;// 中转地址
	
	u8				m_byEncChnNum;		//该通道支持几路后适配 编码	
	TTPTransAddr	m_atEncRtpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr	m_atEncRtcpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp编码中转通道地址	
	
	CDsListInfo		m_tMidAddrDs;
	
	tagtXmpuVidBasRes() { Clear(); }
	
	void Clear()
	{
		memset(this, 0, sizeof(tagtXmpuVidBasRes));	
	}
	
}tXmpuVidBasRes;

typedef struct tagtXmpuAudBasRes
{
public:
	u16				m_dwEqpID;			//外设分配ID初始分配永不删除	
	u16				m_wConfID;
	
	EmXmpuResStatInfo		m_emStat;			//通道状态
	
	TTPTransAddr			m_tDecMiddleRtpAddr;//解码中转地址
	TTPTransAddr			m_tDecRtpAddr;
	TTPTransAddr			m_tDecRtcpAddr;
	
	u8			        	m_byEncChnNum;		//该通道支持几路后适配 编码	
	TTPTransAddr			m_atEncRtpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr			m_atEncRtcpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr			m_atEncMiddleRtcpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv
	
	CDsListInfo		m_tMidAddrDs;
	
	tagtXmpuAudBasRes()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagtXmpuAudBasRes));
	}
	
}tXmpuAuddBasRes;

#endif

class CNodeBase
{
public:
	CNodeBase(EmNodeType emType){m_emType = emType; m_pcSrc = NULL;}

	void SetSrc(CNodeBase* pcPlay)	{ m_pcSrc = pcPlay; }
	CNodeBase*	GetSrc()const		{ return m_pcSrc; }

	EmNodeType GetType()const		{ return m_emType;}	
	void SetType(EmNodeType type)	{ m_emType = type;}	

public:
	const s8* GetSrcName()
	{
		if (NULL == m_pcSrc)
		{
			return "end";
		}
		return m_pcSrc->GetName();
	}
	virtual const s8* GetName()
	{
		switch (m_emType)
		{
		case em_Node_Ep:
			return "Ep";
			break;
		case em_Node_VirSpeak:
			return "VirSpeak";
			break;
		case em_Node_VirChair:
			return "VirChair";
			break;
		case em_Node_SpeakBas:
			return "SpeakBas";
			break;
		case em_Node_DualBas:
			return "DualBas";
			break;
		case em_Node_ChairBas:
			return "ChairBas";
			break;
		case em_Node_Poll:
			return "Poll";
			break;
		case em_Node_View:
			return "View";
			break;
		case em_Node_ViewDown:
			return "ViewDown";
			break;
		case em_Node_BaseBas:
			return "BaseBas";
			break;
		case em_Node_Vmp:
			return "Vmp";
			break;
		case em_Node_RecMt:
			return "RecMt";
			break;
		case em_Node_RecConf:
			return "RecConf";
			break;
		}
		return "Default";
	}
protected:
	EmNodeType	m_emType;
	CNodeBase*	m_pcSrc;	//观看目标
};

typedef void (*AudMixerCB)(u32 dwType, void* param1, void* param2);

typedef struct tagTAudMixChnl
{
	u16 m_wEpID;
	u16 m_wScrIndx;        // 0 1 2 对应左中右，3对应混音，4对应双流
	TTPMediaTransAddr		m_tMixAddr;			//混音板的地址
	CMixerChnAddrListItor	m_ptMixChnAddr;		//混音后 本地的接收地址 N-1模式
												//Rtp为混音码流的接收地址，BackRtcp为混音器的重传请求目的地址
	tagTAudMixChnl()
	{
		Clear();
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScrIndx = MIDSCREENINDEX;
		m_tMixAddr.Clear();
		m_ptMixChnAddr = NULL;
	}

	BOOL32 IsExist()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}
}TAudMixChnl;

typedef struct tagTAudMixInfo
{
	enum EmCBOprType
	{
		EmCBOprType_DisConnect,
		EmCBOprType_StartFail,
		EmCBOprType_AddMemberFail
	};

	TMixEqpRes		m_tEqpRes;
	u16				m_wUsdChnNum;
	BOOL32			m_bMixMotive;//当前语音激励状态
	TAudMixChnl		m_atChnl[TP_APU2_MAX_CHAN_NUM];
	u8              m_byForceActiveChan; // 强制混音的通道id

	u8				m_bySyncChnl;
	u8              m_byDelChnld;

	AudMixerCB		m_pcCB;
	void*			m_ptUsrParam;

	//MIX IN  MIDRtp -> Rtp
    TTPTransAddr	m_atN1DecMiddleRtpAddr[TP_APU2_MAX_CHAN_NUM];  // MIX INPUT Mid Addr
	TTPTransAddr	m_atN1DecRtpAddr[TP_APU2_MAX_CHAN_NUM];  // MIX INPUT Real DecRtp  
	//MIX IN RTCP 在m_atChnl中

	//MIX OUT N Rtp
	TTPTransAddr	m_atNEncRtpAddr[UMS_AUDMIX_N_OUT_NUM];  // MIX OUT N Rtp
	//MIX OUT N Rtcp ->Rtpc
    TTPTransAddr	m_atNEncMiddleRtcpAddr[UMS_AUDMIX_N_OUT_NUM]; //MIX OUT N Rtcp 
	u8					m_byNNum;
	TTPTransAddr	m_atNEncRtcpAddr[UMS_AUDMIX_N_OUT_NUM]; // MIX OUT Real Eec Rtcp


	// N-1 RTP 在m_atChnl中， MIX OUT N-1 Rtcp ->Rtpc
	TTPTransAddr	m_atN1EncMiddleRtcpAddr[TP_APU2_MAX_CHAN_NUM]; //MIX OUT N-1 MID RTCP ADDR
	TTPTransAddr	m_atN1EncRtcpAddr[TP_APU2_MAX_CHAN_NUM]; //MIX OUT N-1 REAL RTCP ADDR
	
	CDsListInfo         m_cToMixDsInfo;

	tagTAudMixInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tEqpRes.Clear();
		m_wUsdChnNum = 0;
		m_bMixMotive = FALSE;
		for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++ )
		{
			m_atChnl[wIndex].Clear();
		}
		m_pcCB = NULL;
		m_ptUsrParam = NULL;
		m_byForceActiveChan = 0xFF;
		m_bySyncChnl = 0xFF;
		m_byDelChnld = 0xFF;
		m_byNNum = 0;
		memset(m_atNEncRtpAddr, 0, sizeof(m_atNEncRtpAddr));
		memset(m_atNEncRtcpAddr, 0, sizeof(m_atNEncRtcpAddr));
		memset(m_atNEncMiddleRtcpAddr, 0, sizeof(m_atNEncMiddleRtcpAddr));
		memset(m_atN1DecMiddleRtpAddr, 0, sizeof(m_atN1DecMiddleRtpAddr));
		memset(m_atN1EncMiddleRtcpAddr, 0, sizeof(m_atN1EncMiddleRtcpAddr));
		memset(m_atN1DecRtpAddr, 0, sizeof(m_atN1DecRtpAddr));
		memset(m_atN1EncRtcpAddr, 0, sizeof(m_atN1EncRtcpAddr));
		m_cToMixDsInfo.Clear();
	}

	BOOL32 IsSyncChnl()
	{
		return (0xFF != m_bySyncChnl);
	}

	void SetSyncChnl(u8 byChnl)
	{
		m_bySyncChnl = byChnl;
	}

	BOOL32 IsForceActive()
	{
		return (0xFF != m_byForceActiveChan);
	}
	
	void SetForceActive(u8 bChanId)
	{
		m_byForceActiveChan = bChanId;
	}
	
	void ClearForceActve()
	{
		m_byForceActiveChan = 0xFF;
	}

	u16 AddMember()
	{
		for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++ )
		{
			if ( m_atChnl[wIndex].IsExist() )
			{
				continue;
			}

			IncrementChan();

			return wIndex;
		}
		return TP_INVALID_INDEX;
	}

	u16 GetIndx(u16 wEpID, u16 wScrIndx)
	{
		for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++ )
		{
			if ( m_atChnl[wIndex].m_wEpID == wEpID
				&& m_atChnl[wIndex].m_wScrIndx == wScrIndx)
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}

	u8 GetIndxByEpId(u16 wEpId)
	{
		for ( u8 byIndex = 0; byIndex < TP_APU2_MAX_CHAN_NUM; byIndex++ )
		{
			if ( m_atChnl[byIndex].m_wEpID == wEpId)
			{
				return byIndex;
			}
		}
		return TP_APU2_MAX_CHAN_NUM;
	}

	void DelMember(u16 wEpID, u16 wScrIndx)
	{
		for ( u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++ )
		{
			if ( m_atChnl[wIndex].m_wEpID == wEpID
				&& m_atChnl[wIndex].m_wScrIndx == wScrIndx)
			{
				DecrementChan();

				m_atChnl[wIndex].Clear();
				m_atN1DecRtpAddr[wIndex].Clear();
				m_atN1EncRtcpAddr[wIndex].Clear();
			}
		}
	}

	void DelMember(u8 byChnl)
	{
		if (m_atChnl[byChnl].IsExist())
		{
			DecrementChan();

			m_atChnl[byChnl].Clear();
			m_atN1DecRtpAddr[byChnl].Clear();
			m_atN1EncRtcpAddr[byChnl].Clear();
		}
	}

	u16 IdleChanNum() { return m_tEqpRes.m_wChanNum - m_wUsdChnNum; }
	void IncrementChan() { m_wUsdChnNum ++; }
	void DecrementChan() { if( m_wUsdChnNum > 0 ) m_wUsdChnNum --; }
}TAudMixInfo;

typedef struct tagTAudMixMemberInfo
{
	u16 m_awEpId[TP_APU2_MAX_CHAN_NUM];
	u16 m_awScrIndx[TP_APU2_MAX_CHAN_NUM]; // 0 1 2分别对应座席，3表示需要进混音

	tagTAudMixMemberInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTAudMixMemberInfo));
	}
	
	u16 FindFreeIndex()
	{
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			if (0 == m_awEpId[wIndex])
			{
				return wIndex;
			}
		}
		return TP_APU2_MAX_CHAN_NUM;
	}

	void AddMixMember(u16 wEpId, u16 wScrIndx)
	{
		u16 wAddIndex = FindFreeIndex();
		if ( TP_APU2_MAX_CHAN_NUM == wAddIndex )
		{
			return ;
		}
		m_awEpId[wAddIndex] = wEpId;
		m_awScrIndx[wAddIndex] = wScrIndx;
	}

	BOOL32 IsMixMember(u16 wEpId, u16 wScrIndx)
	{
		for (u16 wLoop = 0; wLoop < TP_APU2_MAX_CHAN_NUM; wLoop++)
		{
			if (wEpId == m_awEpId[wLoop] && wScrIndx == m_awScrIndx[wLoop])
			{
				return TRUE;
			}
		}
		return FALSE;
	}

}TAudMixMemberInfo;

class CBaseService;
class CScreenBasRes;
class CVirSpeaker : public CNodeBase
{
public:
	void SetCur(CNodeBase* pcNode)	{ m_pcSrc = pcNode;	}
	void SetOld(CNodeBase* pcNode)	{ m_pcOld = pcNode;	}
	CNodeBase* GetCur()const { return m_pcSrc; }
	CNodeBase* GetOld()const { return m_pcOld; }
private:
	CNodeBase*			m_pcOld;
public:
	
	TTPMediaTransAddr	m_atVidDec[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_tSingleVidDec;	//接收单屏系统需要的视频流

	TTPMediaTransAddr	m_atAudDec[TP_MAX_STREAMNUM];	
	TTPMediaTransAddr	m_tAudMixDec;
	
	TUmsNetBuf			m_atVidBuf[TP_MAX_STREAMNUM];
	TUmsNetBuf          m_tSingleVidBuf;

	TAudMixInfo*		m_ptAudMix;		//混音器 双流开启时申请，将虚拟发言人、虚拟主席、双流进行混音
	BOOL32              m_bIsDualMixOn;   // 此值用于判断双流是否进混音（注：单单用上面的新资源不为空，不能表明双流一定在混音中）
	CDsListInfo	        m_tToAudMixDs;

	CScreenBasRes*		m_pcSingleBas;	//单屏系统适配  讨论下，上级必须申请到；下级申请不到，不影响讨论状态（需注意判空）
	
	const CBaseService* m_pcSingleVmp;  //单屏合成
	BOOL32              m_bSingleVmpStart;  // 合成器是否已经start
	CDsListInfo	        m_tToVmpDs;
/*	CDsListInfo         m_tToOtherConfDsEqpDs; //会议转发板到其他转发板的交换*/

	CDsListInfo			m_tToVirSpeakerDs;
	CDsListInfo			m_tInnerVirSpeaker;
	
	CVirSpeaker()
		:CNodeBase(em_Node_VirSpeak) 
		,m_pcOld(NULL)
	{
		m_bIsDualMixOn = FALSE;
		m_ptAudMix = NULL;
		m_pcSingleBas = NULL;
		m_pcSingleVmp = NULL;
		m_bSingleVmpStart = FALSE;
	}
};


typedef struct tagTUmsUpdateNode
{
	EmTpOprType m_emOpr;
	u16			m_wEpID;
	tagTUmsUpdateNode()
	{
		m_emOpr = tp_OprType_Update;
		m_wEpID = TP_INVALID_INDEX;
	}
}TUmsUpdateNode;

//需要向UI的转发
typedef struct tagTRefrenUiNodeList
{
	BOOL32 m_bRefreshImm;			//是否需要立即刷新
	u16 m_wNum;
	TUmsUpdateNode m_atNode[TP_REFRESH_LIST_THREE];
	tagTRefrenUiNodeList()
	{
		Clear();
	}
	void Clear()
	{
		m_bRefreshImm = FALSE;
		m_wNum = 0;
	}
	
	void Add(EmTpOprType emOpr, u16 wEpID);
}TRefrenUiNodeList;

class CVirChair : public CNodeBase
{
public:
	TTPTransAddr	m_atVidDec[TP_MAX_STREAMNUM];
	TTPTransAddr	m_atAudDec[TP_MAX_STREAMNUM];

	CDsListInfo		m_tToVirChair;
	
	CVirChair():CNodeBase(em_Node_VirChair){ }
};


typedef struct tagTRes
{
	u16				m_wNum;
	EmTpVideoResolution	m_emRes;
	tagTRes()
	{
		Clear();
	}

	void Clear()
	{
		m_wNum = 0;
		m_emRes = emTPVResEnd;
	}
}TRes;

typedef struct tagTFrm
{
	u16	m_wNum;
	u16	m_wFrm;
	tagTFrm()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wNum = 0;
		m_wFrm = 0;
	}
}TFrm;

//帧率分辨率调整管理
#define NODE_RES_FRM_NUM	5

class TCallNode;
class CResFrmMgr
{
public:
	CResFrmMgr()
	{
		Clear();
	}
	~CResFrmMgr()
	{
		memset(this, 0, sizeof(CResFrmMgr));
	}

	void SetTNode(TCallNode* ptNode) { m_ptNode = ptNode; }

	BOOL32 AdjustRes(EmTpVideoResolution	emRes);
	BOOL32 ResetRes(EmTpVideoResolution	emRes);
	EmTpVideoResolution	GetCurRes();

	BOOL32 AdjustFrm(u16 wFrm);
	BOOL32 ResetFrm(u16 wFrm);
	u16 GetCurFrm();

	void PrintInfo();
	void SetDefault();
	void Clear();
protected:
	u16	FindSmallRes();
	u16	FindSmallFrm();	
private:
	TCallNode*		m_ptNode;
	u16				m_wCurResIndx;//结点当前分辨率
	u16				m_wCurFrmIndx;//结点当前分辨率
	TRes			m_atRes[NODE_RES_FRM_NUM];
	TFrm			m_atFrm[NODE_RES_FRM_NUM];
};

//
class TCallNode : public CNodeBase
{
public:
	BOOL32 m_bUsed;							//结点是否启用
	UMSEP_VER	m_byVer;							//版本号
	
#define NodeNoNeedCall		(u8)0 //挂断后不需要重新呼叫, 根据挂断理由业务处理
#define NodeNeedSipCall		(u8)1 //挂断后需要用sip重新呼叫(不管什么挂断理由)
#define NodeNeedH323Call	(u8)2 //挂断后需要用h323重新呼叫(不管什么挂断理由)
	u8  m_byNeedCallType; 

	//树形表
	u16	m_wEpID;							//本节点

	u16	m_wParentEpID;						//父结点
	u16 m_wChildEpID;						//子节点
	u16 m_wBrotherEpID;						//兄弟结点
	
	u16 m_wLowChildEpID;					//本结点在下级中的索引
	
	EmTPEndpointType m_emEpType;			//结点类型
	EmTpVendorID	 m_emVendorID;			//厂商ID

	s8	m_abyPrdutID[TP_UMS_PRDUT_ID];		//结点产品ID

	EmUmsConfNodeState	m_emCallState;		//呼叫状态
	EmCnsCallReason		m_emCallReason;		//呼叫结果
	BOOL32 m_bChannelOpen;					//通道是否打开
	BOOL32 m_bInPoll;
	TTpCallAddr m_tCalledAddr;				//呼叫此结点时的地址
	TTPAlias m_tConfName;					//会场名
	
	BOOL32 m_bCallByCMC;					//由CMC主动发起的呼叫

	u16	m_wMixIndex;						//本会场在混音中的序号
	EmTPSipLevel	m_emLevel;				//会场等级	保留
	
	EmTPRcvAlignType m_enRcvAlignType;		//

	BOOL32	m_bMute;						//结点是否哑音
	BOOL32	m_bQuiet;						//结点是否哑音
	BOOL32	m_bCheckDualRcv;				//是否重新建对端双流接收(验证能力不合法停掉的不需要重新建)
	//索引按照五个通道 0,1,2,3,4排序，不管本会场真实是几个编码器
	u16 m_wSpearkIndex;			//发言人通道索引
	u16 m_wDualIndex;			//发送双流通道索引
	
	u16	m_wVidSndNum;		// 结点 视频发送通道数量
	u16	m_wVidRcvNum;	
	u16	m_wAudSndNum;	
	u16	m_wAudRcvNum;

	BOOL32	m_bSmallOpenDec;
	BOOL32	m_bSmallOpenEnc;

	EmTpConfProtocol m_emCallProtocol;	//呼叫协议类型
	
	TCallVidFormat	m_tVidRcvFormat; 
	TCallAudFormat	m_tAudRcvFormat;
	
	TCallVidFormat	m_tVidSndFormat;
	TCallAudFormat	m_tAudSndFormat;
	
	TCallVidFormat	m_tDualVidRcvFormat;
	TCallAudFormat	m_tDualAudRcvFormat;

	TCallVidFormat	m_tDualVidSndFormat;
	TCallAudFormat	m_tDualAudSndFormat;

	u16  m_wSelNum;  // 被选看次数

	BOOL32 m_bAllowFecc; // 远遥通道是否打开
	u8	m_byCurVidNo;
	TVidSourceInfo m_tVidSourceInfo; // 会场视频源信息

	BOOL32	m_bNeedReCallBy323;
	u16           m_wCallBy323Num;
public:
	//
	TCallNode();
	
	BOOL32 IsMtEp()	const	{ return emTPEndpointTypeCNS == m_emEpType
								|| emTPEndpointH323MT == m_emEpType
								|| emTPEndpointH323SingleMCU == m_emEpType
								|| emTPEndpointH323G400 == m_emEpType
								|| emTPEndPointVrs == m_emEpType; }

	BOOL32 Is323Ep() const	{ return emTPEndpointH323MT == m_emEpType
								|| emTPEndpointH323SingleMCU == m_emEpType
								|| emTPEndpointH323MCU == m_emEpType
								|| emTPEndpointH323G400 == m_emEpType; }

	BOOL32 IsCns()	const	{ return emTPEndpointTypeCNS == m_emEpType; }
	BOOL32 IsUms()	const	{ return emTPEndpointTypeUMS == m_emEpType; }
	BOOL32 IsG400() const	{ return emTPEndpointH323G400 == m_emEpType; }
	BOOL32 IsSingleMcu() const	{ return emTPEndpointH323SingleMCU == m_emEpType; }
	BOOL32 IsMcu() const	{ return emTPEndpointH323MCU == m_emEpType; }
	BOOL32	IsVRS() { return (strcmp(m_abyPrdutID, "KDCVRS2000E") == 0 || strcmp(m_abyPrdutID, "KDCVRS4000E") == 0 || emTPEndPointVrs == m_emEpType) ? TRUE : FALSE; }

	BOOL32 IsSingleScreen()	const	{ return 1 == m_wVidRcvNum; }
	virtual u32 GetAdapterNode()const{return 0;}

	virtual void Clear();
	virtual void HungUp();	

	virtual const s8* GetName()			{ return m_tConfName.m_abyAlias; }

	void ChannelDisConnect();

	BOOL32	IsKedaMt()				{ return m_emVendorID == EmTp_vendor_KEDA; }

	BOOL32  IsCanAdjustRes()  {return (IsKedaMt() && !IsVRS() && !IsSingleMcu() && !IsG400());}// 可以降分辨率的终端

	BOOL32 IsInMix() const			{ return VALID_AUDMIX_INDEX(m_wMixIndex); }
	u16 GetMixIndex() const			{ return m_wMixIndex; }

	BOOL32 IsVidSndValid() const	{ return m_wVidSndNum > 0 && m_wVidSndNum % 2 != 0; }
	BOOL32 IsVidRcvValid() const	{ return m_wVidRcvNum > 0 && m_wVidRcvNum % 2 != 0; }
	BOOL32 IsAudSndValid() const	{ return (m_wAudSndNum > 0 && m_wAudSndNum % 2 != 0); }
	BOOL32 IsAudRcvValid() const	{ return (m_wAudRcvNum > 0 && m_wAudRcvNum % 2 != 0); }

	u16 IsThreeVidRcv()	const	{	return m_wVidRcvNum == 3; }
	u16 IsSingleVidRcv()const	{	return m_wVidRcvNum == 1; }
	u16 IsThreeVidSnd()	const	{	return m_wVidSndNum == 3; }
	u16 IsSingleVidSnd()const	{	return m_wVidSndNum == 1; }

	BOOL32	IsSmallVidSnd() const { return m_bSmallOpenEnc; }
	BOOL32	IsSmallVidRcv() const { return m_bSmallOpenDec; }
	
	u16 IsThreeAudRcv()	const	{	return m_wAudRcvNum == 3; }
	u16 IsSingleAudRcv()const	{	return m_wAudRcvNum == 1; }
	u16 IsThreeAudSnd()	const	{	return m_wAudSndNum == 3; }
	u16 IsSingleAudSnd()const	{	return m_wAudSndNum == 1; }

	BOOL32	IsB1UMS()const		{   return m_byVer == UMS_B1; }
	BOOL32	IsB3CNS()const		{ return m_emEpType == emTPEndpointTypeCNS && m_byVer < CNS_B4; }
	BOOL32  IsNeedCall()const {return NodeNoNeedCall != m_byNeedCallType;}
	BOOL32  IsNeedH323Call()const {return NodeNeedH323Call== m_byNeedCallType;}
	BOOL32  IsNeedSipCall()const {return NodeNeedSipCall== m_byNeedCallType;}
	void    SetNeedCallType(u8 byCallType)
	{
		if (NodeNeedH323Call==byCallType || NodeNeedSipCall==byCallType) 
		{
			m_byNeedCallType = byCallType;
		}
	}
	void    ResetNeedCall()     { m_byNeedCallType = NodeNoNeedCall;}

	void SetVidSndNum(u16 wNum)	{	if (wNum > TP_MAX_STREAMNUM)return;	m_wVidSndNum = wNum;	}
	void SetVidRcvNum(u16 wNum)	{	if (wNum > TP_MAX_STREAMNUM)return;	m_wVidRcvNum = wNum;	}
	void SetAudSndNum(u16 wNum)	{	if (wNum > TP_MAX_STREAMNUM)return;	m_wAudSndNum = wNum;	}
	void SetAudRcvNum(u16 wNum)	{	if (wNum > TP_MAX_STREAMNUM)return;	m_wAudRcvNum = wNum;	}
	
	void CallOn()				{ m_emCallState = ums_UmsConfNodeState_online; }
	BOOL32 IsCallOn()			{ return m_bUsed && m_emCallState == ums_UmsConfNodeState_online; }
	BOOL32 IsChanOn() const		{ return m_bChannelOpen; }
	BOOL32 IsInPoll() const		{ return m_bInPoll; }

	u32	GetSndBW()				{ return m_tVidSndFormat.m_tFormat.m_wBitrate * m_wVidSndNum; }
	u32	GetRcvBW()				{ return m_tVidRcvFormat.m_tFormat.m_wBitrate * m_wVidRcvNum; }

	//获取发言人, 如果没有发言人，则默认中间一个为发言人
	u16 GetSpeaker()const		{ return m_wSpearkIndex < TP_MAX_STREAMNUM ? m_wSpearkIndex :  (u16)(MIDSCREENINDEX);	}

	void GetCnsInfo(TCnsInfo& tInfo);
	void SetNodeCallInfo(TConfNodeCallUpdateTr& tInfo);
	void SetNodeChanInfo(TConfNodeChanUpdateTr& tInfo);
	
	// Vid and fecc info
	void SetVidFeccInfo(TVidFeccInfo& tInfo);
	void GetVidFeccInfo(TVidFeccInfo& tInfo);
	
	

	// mcu Node info
	void SetMcuNodeCallInfo( TUmcMcuPart& tInfo);
	void SetMcuNodeChanInfo(TCallNode* ptParent, TUmcMcuPart& tInfo);
	void GetNodeCallInfo(TConfNodeCallUpdateTr& tInfo);
	void GetNodeChanInfo(TConfNodeChanUpdateTr& tInfo);

	void ClearSelNum() {m_wSelNum = 0;}
	void IncreaseSelNum(u16 wValue) { m_wSelNum += wValue;}
	void DiscreaseSelNum(u16 wValue) { m_wSelNum > wValue ? m_wSelNum -=wValue : m_wSelNum = 0;}
	u16  GetSelNum() {return m_wSelNum;}
	BOOL32 bIsSel() { return 0 != m_wSelNum;}
	
	BOOL32 IsAllowFecc() { return m_bAllowFecc == TRUE; }
	void SetAllowFecc(BOOL32 bAllow) { m_bAllowFecc = bAllow; }
	void SetVidSource(TVidSourceInfo& tVidInfo) { m_tVidSourceInfo = tVidInfo; };
	void SetCurVidNo(u8 byVidNo) { m_byCurVidNo = byVidNo; }
};

//UMS对NODE的虚拟接收地址
typedef struct tagTChanRcvAddr
{
	TTPTransAddr m_tRtpAddr;			//UMS接收远端码流的RTP地址
	TTPTransAddr m_tRtcpForRcv;			//接收通道的BACKRTCP地址，现在用作上下级之间的回传请求
	TTPTransAddr m_tRtcpForSnd;			//发送通道的BACKRTCP地址，一般用作接收远端(CNS/MT)的重传请求	
	tagTChanRcvAddr()
	{
	}
}TChanRcvAddr;

typedef struct tagTLocalChanAddr	//每个屏的通道地址
{
	TChanRcvAddr m_tVid;	//视频接收
	TChanRcvAddr m_tAud;	//音频接收
}TLocalChanAddr;
#define CLocalChanAddrList CTpListBuff<TLocalChanAddr>
#define CLocalChanAddrListItor TLocalChanAddr*

#define CLocalSmallChanAddrList CTpListBuff<TChanRcvAddr> //小码流通道的接收地址， B4版 T300有小码流
#define CLocalSmallChanAddrListItor TChanRcvAddr*

#define CLocalAudMixAddrList CTpListBuff<TChanRcvAddr>	//混音通道的接收地址， 对于三屏会场和级联需要有混音通道
#define CLocalAudMixAddrListItor TChanRcvAddr*

#define CLocalPollChanAddrList CTpListBuff<TTPMediaTransAddr> //轮询通道地址
#define CLocalPollChanAddrListItor TTPMediaTransAddr*

#define CLocalRollChanAddrList CTpListBuff<TTPMediaTransAddr> //点名通道地址
#define CLocalRollChanAddrListItor TTPMediaTransAddr*

#define CPutAudChanAddrList CTpListBuff<TTPMediaTransAddr>     //上下级音频通道地址
#define CPutAudChanAddrListItor TTPMediaTransAddr*

#define CEapuChanAddrList CTpListBuff<TTPMediaTransAddr>      //混音器通道地址
#define CEapuChanAddrLIstItor TTPMediaTransAddr*

#define CAddrList CTpListBuff<TTPMediaTransAddr>	//Rtp和Rtcp的地址对 供所有动态的业务来使用和分配
#define CAddrListItor TTPMediaTransAddr*

typedef struct tagTSingleScreenAddr	//单个屏幕的地址
{
	TChanRcvAddr m_tVid;
	TChanRcvAddr m_tAud;
}TSingleScreenAddr;

#define CLocalDualAddrList CTpListBuff<TSingleScreenAddr>
#define CLocalDualAddrListItor TSingleScreenAddr*

typedef struct tagTFastUpdateStatis
{
	u32	m_dwStatis[TP_KEYFRAME_STATIS];
	tagTFastUpdateStatis()
	{
		Clear();
	}
	void Clear()
	{
		memset(&m_dwStatis, 0, sizeof(u32)*TP_KEYFRAME_STATIS);
	}
	
	void Add();
	BOOL32 CheckValidInterval(u32 dwInterval, u32 dwTimes) const;

}TFastUpdateStatis;

typedef struct tagTChanFlowCtrl
{
public:
	u32	m_dwState;
public:
	tagTChanFlowCtrl()	{	Clear();		}
	void Clear()		{	m_dwState = 1;	}
	void Inc()	{	m_dwState++;	}
	void Dec()	{	m_dwState--;	}
	BOOL32 IsNoneFlow()	{	return m_dwState == 0;	}
}TChanFlowCtrl;


//通道参数
typedef struct tagTChanPara
{
	u16					m_wIndex;	
	EmChanState			m_emChanState;	//是否打开
	TTPMediaTransAddr	m_tChanAddr;	//地址
	s32					m_tPAHandle;
	
	tagTChanPara()
	{
		m_wIndex = TP_INVALID_INDEX;			//初始化时分配，中间不修改
		m_tPAHandle = TP_INVALID_INDEX;
		m_emChanState = EmChanIdle;
	}
	
	void Clear()
	{
		m_tPAHandle = TP_INVALID_INDEX;
		m_emChanState = EmChanIdle;
		m_tChanAddr.Clear();
	}	
	void SetPara(const TChanNetPara& tPara)
	{
		m_emChanState = tPara.m_bIsChanOn ? emChanOpen : EmChanIdle;
		m_tChanAddr = tPara.m_tChanAddr;
		m_tPAHandle = tPara.m_tPAHandle;
	}
	void SetOpen(BOOL32 bOpen)		{ m_emChanState = bOpen ? emChanOpen : EmChanIdle; }
	BOOL32 IsOpen()					{ return emChanOpen == m_emChanState; }
	BOOL32 IsIdle()                 { return EmChanIdle == m_emChanState; }                
}TChanPara;


typedef struct tagTVidChanPara : public TChanPara
{
	TFastUpdateStatis	m_tKeyFrameStatis;
	TChanFlowCtrl		m_tFlowCtrl;
	tagTVidChanPara()
	{
	}
	
	void Clear()
	{
		m_tKeyFrameStatis.Clear();
		m_tFlowCtrl.Clear();
		TChanPara::Clear();
	}	
}TVidChanPara;

typedef struct tagTRmtChan
{
	TVidChanPara m_atVidEnc[TP_MAX_STREAMNUM];	//远端视频发送通道
	TVidChanPara m_atVidDec[TP_MAX_STREAMNUM];	//远端视频接收通道
	
	TVidChanPara m_atSmallVidEnc[TP_MAX_STREAMNUM];//远端视频小码流发送通道
	TVidChanPara m_atSmallVidDec[TP_MAX_STREAMNUM];//远端视频小码流接收通道

	TChanPara m_atAudEnc[TP_MAX_STREAMNUM];	//远端音频发送通道
	TChanPara m_atAudDec[TP_MAX_STREAMNUM];	//远端音频接收通道
	
	TVidChanPara m_tDualVidDec;				//远端地址
	TChanPara m_tDualAudDec;				//远端地址
	
	TVidChanPara m_tDualVidEnc;				//远端地址
	TChanPara m_tDualAudEnc;				//远端地址
	
	TChanPara m_tAudMixEnc;					//远端地址
	TChanPara m_tAudMixDec;					//远端地址

	tagTRmtChan()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atVidEnc[wIndex].m_wIndex = wIndex;		
			m_atVidDec[wIndex].m_wIndex = wIndex;	
			m_atAudEnc[wIndex].m_wIndex = wIndex;	
			m_atAudDec[wIndex].m_wIndex = wIndex;
			
			m_atSmallVidDec[wIndex].m_wIndex = wIndex;
			m_atSmallVidEnc[wIndex].m_wIndex = wIndex;
		}
		Clear();
	}

	u32 getvalidepip()
	{
		u32 dwIp = 0;
		if (m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr.m_dwIP)
		{
			dwIp = m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr.m_dwIP;
		}
		else if (m_atAudDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr.m_dwIP)
		{
			dwIp = m_atAudDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr.m_dwIP;
		}
		else if (m_atVidEnc[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr.m_dwIP)
		{
			dwIp = m_atVidEnc[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr.m_dwIP;
		}
		else if (m_atAudEnc[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr.m_dwIP)
		{
			dwIp = m_atAudEnc[MIDSCREENINDEX].m_tChanAddr.m_tBackRtcpAddr.m_dwIP;
		}
		else
		{

		}
		return dwIp;
	}

	BOOL32 IsSmallChanOn(u16 wChan)	{ return m_atSmallVidEnc[wChan].IsOpen(); }

	BOOL32	IsDualChanOn()
	{
		return	m_tDualVidDec.IsOpen() || m_tDualAudDec.IsOpen() ||
				m_tDualVidEnc.IsOpen() || m_tDualAudEnc.IsOpen();	
	}

	void Clear()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atVidEnc[wIndex].Clear();			
			m_atVidDec[wIndex].Clear();			
			m_atAudEnc[wIndex].Clear();			
			m_atAudDec[wIndex].Clear();

			m_atSmallVidEnc[wIndex].Clear();
			m_atSmallVidDec[wIndex].Clear();
		}
		m_tDualVidDec.Clear();
		m_tDualAudDec.Clear();

		m_tDualVidEnc.Clear();
		m_tDualAudEnc.Clear();

		m_tAudMixEnc.Clear();
		m_tAudMixDec.Clear();

	}

	void ResetFastStatis()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atVidEnc[wIndex].m_tKeyFrameStatis.Clear();			
			m_atVidDec[wIndex].m_tKeyFrameStatis.Clear();
		}
	}
}TRmtChan;

typedef struct tagTCascadeChairChan
{
	TChanPara m_atVid[TP_MAX_STREAMNUM];
	TChanPara m_atAud[TP_MAX_STREAMNUM];
	TChanPara m_tMixAud;
	TChanPara m_tDisSingleVid;
	TChanPara m_tDisSingleAud;
	tagTCascadeChairChan()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atVid[wIndex].m_wIndex = wIndex;			
			m_atAud[wIndex].m_wIndex = wIndex;	
		}
		m_tMixAud.m_wIndex = 0;
		m_tDisSingleVid.m_wIndex = 0;
		m_tDisSingleAud.m_wIndex = 0;
		Clear();
	}
	
	void Clear()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atVid[wIndex].Clear();			
			m_atAud[wIndex].Clear();			
		}
		m_tMixAud.Clear();
		m_tDisSingleVid.Clear();
		m_tDisSingleAud.Clear();
	}
}TCascadeChairChan;

typedef struct tagTCascadeChairAddr
{
	TChanRcvAddr m_atVid[TP_MAX_STREAMNUM];
	TChanRcvAddr m_atAud[TP_MAX_STREAMNUM];
	TChanRcvAddr m_tMixAud;
	TChanRcvAddr m_tDisSingleVid;
	TChanRcvAddr m_tDisSingleAud;

	TCascadeChairChan m_tRmtInfo;
}TCascadeChairAddr;

#define CCascadeChairAddrList CTpListBuff<TCascadeChairAddr>
#define CCascadeChairListItor TCascadeChairAddr*



typedef struct tagTVidAddr
{
	//分配上传地址 一大一小
	TTPMediaTransAddr m_tUp;
	TTPMediaTransAddr m_tSmallUp;
	//分配下传地址 一大二小
	TTPMediaTransAddr m_tDown;
	TTPMediaTransAddr m_tSmallDownL;
	TTPMediaTransAddr m_tSmallDownR;

	//记录上传的Rtp、BackRtcp
	TVidUpAddr	m_tRtpUpDst;
	TVidUpAddr	m_tBackRtcpUpDst;

	//记录下传的Rtp、BackRtcp
	TVidDownAddr m_tRtpDownDst;
	TVidDownAddr m_tBackRtcpDownDst;

	tagTVidAddr()
	{
		m_tUp.Clear();
		m_tSmallUp.Clear();

		m_tDown.Clear();
		m_tSmallDownL.Clear();
		m_tSmallDownR.Clear();
		Clear(); 
	}

	void Clear()
	{
		m_tRtpUpDst.Clear();
		m_tBackRtcpUpDst.Clear();

		m_tRtpDownDst.Clear();
		m_tBackRtcpDownDst.Clear();
	}

}TVidAddr;

typedef struct tagTAudDownAddr
{
	//分配
	TTPMediaTransAddr m_tAddr;
	//记录对端端口
	TTPMediaTransAddr m_tAddrDst;
	tagTAudDownAddr()
	{
		m_tAddr.Clear();
		Clear();
	}
	void Clear()
	{
		m_tAddrDst.Clear();
	}
}TAudDownAddr;

typedef struct tagTTPCascadTransAddr
{
	TTPTransAddr m_tRtpAddr;
	TTPTransAddr m_tRtcpForUp;		//接收上级的重传
	TTPTransAddr m_tRtcpForNB;		//接收本地NB的重传
	tagTTPCascadTransAddr()
	{
		Clear();
	}

	tagTTPCascadTransAddr(const tagTTPCascadTransAddr& tAddr)
	{
		m_tRtpAddr = tAddr.m_tRtpAddr;
		m_tRtcpForUp = tAddr.m_tRtcpForUp;
		m_tRtcpForNB = tAddr.m_tRtcpForNB;
	}

	tagTTPCascadTransAddr& operator=(const tagTTPCascadTransAddr& tAddr)
	{
		if (&tAddr != this)
		{
			m_tRtpAddr = tAddr.m_tRtpAddr;
			m_tRtcpForUp = tAddr.m_tRtcpForUp;
			m_tRtcpForNB = tAddr.m_tRtcpForNB;
		}

		return *this;
	}

	void Clear()
	{
		m_tRtpAddr.Clear();
		m_tRtcpForUp.Clear();
		m_tRtcpForNB.Clear();
	}
	void SetIP(u32 dwIP)
	{
		m_tRtpAddr.SetIP(dwIP);
		m_tRtcpForUp.SetIP(dwIP);
		m_tRtcpForNB.SetIP(dwIP);
	}

}TTPCascadTransAddr;


enum EmViewType
{
	em_View_SelView,	//选看
	em_View_TV,			//电视墙
	em_View_Dis,		//讨论
	em_View_Poll,		//主席轮询
	em_View_Vmp,		//合成

	em_View_End,
};

typedef struct tagTSingleCascadAddr	//单个屏幕的地址
{
	TTPCascadTransAddr m_tVid;
	TTPCascadTransAddr m_tAud;
	tagTSingleCascadAddr(){}

	tagTSingleCascadAddr(const tagTSingleCascadAddr& tInfo)
	{
		m_tVid = tInfo.m_tVid;
		m_tAud = tInfo.m_tAud;
	}

	tagTSingleCascadAddr& operator=(const tagTSingleCascadAddr& tInfo)
	{
		if (this != &tInfo)
		{
			m_tVid = tInfo.m_tVid;
			m_tAud = tInfo.m_tAud;
		}

		return *this;
	}
}TSingleCascadAddr;

#define CCascadVidAddrList CTpListBuff<TSingleCascadAddr>	//带音频
#define CCascadVidAddrListItor TSingleCascadAddr*

#define CCascadMixAddrList CTpListBuff<TTPCascadTransAddr>		//混音
#define CCascadMixAddrListItor TTPCascadTransAddr*

class CGetVidInfo : public CNodeBase
{
public:

	u16			m_wIndex;		//本级中的索引
	u16			m_wScreenIndex;	//源屏号
	EmViewType	m_emOprType;
	
	u16			m_wVidCount;	//被选看的次数	
	u16			m_wConfID;
	u16			m_wEpID;		//目标
	u16			m_wDstIndex;	//在上级中的索引
	
	
	BOOL32		m_bUsed;
	BOOL32		m_bNeedBas;		//需要适配
	BOOL32		m_bViewSpeaker;	//是否是仅看发言坐席	
	
	BOOL32		m_abOpen[TP_MAX_STREAMNUM];	//如果是单屏，则中间的视频和中间的音频有效
											//如果是三屏，且三屏图像全选，则三路视频、三路音频、混音码流，全部有效
											//如果是三屏，但只接收一路图像，则中间的视频有效，中间的音频为混音声音

	CCascadVidAddrListItor m_atAddrItor[TP_MAX_STREAMNUM];

	TTPMediaTransAddr	m_atDstAddr[TP_MAX_STREAMNUM];	//
	TTPMediaTransAddr	m_atDstAudAddr[TP_MAX_STREAMNUM];	//

	CCascadMixAddrListItor m_tMixAddrItor;
	TTPMediaTransAddr	m_tDstMixAddr;	//

	CDsListInfo			m_cOnCmdList;	//下级往上级的转发表
	CDsListInfo			m_cRcvFromRmt;	//本级节点，创建EP到VIEW的转发；下级，则主要将RTCP转发出去
		
	CGetVidInfo():CNodeBase(em_Node_View)
	{
		Clear();
	}
	void Clear()
	{
		SetType(em_Node_View);
		SetSrc(NULL);
		
		m_wVidCount = 0;
		m_bUsed = FALSE;
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_wDstIndex = TP_INVALID_INDEX;
		m_bNeedBas = 0;
		m_bViewSpeaker = FALSE;
		m_emOprType = em_View_SelView;
		
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_abOpen[wIndex] = FALSE;

			m_atDstAddr[wIndex].Clear();

			m_atAddrItor[wIndex] = NULL;
		}
		m_tMixAddrItor = NULL;
		m_cOnCmdList.Clear();
		m_cRcvFromRmt.Clear();
	}
	
	void SetInfo(TViewCmdTr& tCmd)
	{
		m_wScreenIndex = tCmd.m_wSrcScreenIndex;
		m_emOprType = (EmViewType)tCmd.m_dwType;
		
		m_wEpID = tCmd.m_wEpID;
		m_wDstIndex = tCmd.m_wIndex;
		
		m_bNeedBas = tCmd.m_bNeedBas;
		m_bViewSpeaker = tCmd.m_bViewSpeaker;	

		memcpy(m_abOpen, tCmd.m_abOpen, sizeof(m_abOpen));
		memcpy(m_atDstAddr, tCmd.m_atAddr, sizeof(m_atDstAddr));
		memcpy(m_atDstAudAddr, tCmd.m_atAudAddr, sizeof(m_atDstAudAddr));
		memcpy(&m_tDstMixAddr, &tCmd.m_tMixAddr, sizeof(m_tDstMixAddr));
	}

	BOOL32 IsNeedBas()	{ return m_bNeedBas; }
	BOOL32 IsGetMid()	{ return !m_abOpen[0] && m_abOpen[MIDSCREENINDEX]; }

private:

	BOOL32 operator == (const CGetVidInfo& tRhs) 
	{
		return FALSE;
	}

};


#define CGetVidList CTpList<CGetVidInfo>		//混音
#define CGetVidListItor CGetVidInfo*


typedef struct tagTTvChanInfo
{
	u16			m_wChan;	//通道号
	u8			m_bySubChan;
	BOOL32      m_bVmp;
	BOOL32		m_bUsed;

	CGetVidListItor	m_cItor;	//
	
	//与CNS交互参数
	BOOL32		m_bOpenToServer;
	EmViewEpType	m_emType;
	u16			m_wConfID;
	u16			m_wDstID;
	u16         m_wScreenIndex;         //屏号
	
	//与Call交互参数
	BOOL32		m_bOpenToCall;
	u16			m_wEpID;
	
	
	TTPMediaTransAddr	m_tTvVidRcv;	//电视墙的接收地址
	TTPMediaTransAddr	m_tTvAudRcv;	//电视墙的接收地址


	CDsListInfo			m_tToHdu;
	
	tagTTvChanInfo()
	{
		m_bUsed = FALSE;
		m_bOpenToServer = FALSE;
		m_bOpenToCall = FALSE;
		Clear();
		m_tToHdu.Clear();
	}
	
	void Clear()
	{
		m_wChan = 0;
		m_bySubChan = 0;
		m_bVmp = 0;
		m_bUsed = FALSE;
		m_bOpenToServer = FALSE;
		m_wScreenIndex = TP_INVALID_INDEX;
		m_bOpenToCall = FALSE;
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		
		m_tTvVidRcv.Clear();
		m_tTvAudRcv.Clear();

		m_cItor = NULL;

		m_emType = EmEpType_Invalid;
		m_wConfID = 0;
		m_wEpID = 0;
	}
}TTvChanInfo;

typedef struct tagTPollIframeCheck
{
	BOOL32	m_abInCheck[TP_MAX_STREAMNUM];		//是否在检测
	BOOL32	m_abNeedClear[TP_MAX_STREAMNUM];	//检测是否被清除
	TTPTransAddr m_tCurAddr[TP_MAX_STREAMNUM];
	TTPTransAddr m_tOldAddr[TP_MAX_STREAMNUM];

	tagTPollIframeCheck()
	{
		Clear();
	}
	void Clear()
	{
		memset(m_abInCheck, 0, sizeof(m_abInCheck));
		memset(m_abNeedClear, 0, sizeof(m_abNeedClear));
		memset(m_tCurAddr, 0, sizeof(m_tCurAddr));
		memset(m_tOldAddr, 0, sizeof(m_tOldAddr));
	}
	
}TPollIframeCheck;

typedef void (*VidBasCB)(u32 dwType, void* param1, void* param2);

class CScreenBasRes : public CNodeBase
{
public:
	enum VidBasCBType
	{
		VidBasCB_AskKey,
		VidBasCB_DisConnect,
		VidBasCB_NAck,
	};
public:
	u16				m_wSrcEp; //前适配会场ID
	u16				m_wSrcScreenIndx;//前适配会场屏索引

#ifdef _USE_XMPUEQP_
    tXmpuVidBasRes  m_tXmpuBas;
#endif

	TBasEqpRes		m_tBasEqpRes;

	u8				m_byFormatNum;
	TUmsVidFormat	m_atVidFormat[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; //后适配格式
	TTPBasVidParam	m_tRealVidPara;

	TUmsVidFormat	m_tSndVidFormat;
	
	u16				m_wNeedAdjustLvl;
	TUmsVidFormat	m_tNeedAdjustFmt;

	BOOL32          m_bIsMultOut;

	u16				m_wAskFrameNum;

	VidBasCB		m_pfCB;
	void*			m_pParam;

	u16				m_wUsdNum;

	EmViewType		m_emType;
public:
	CScreenBasRes():CNodeBase(em_Node_BaseBas) { Clear(); }
	void Clear()		{ memset(this, 0, sizeof(CScreenBasRes)); }

	void SetCB(VidBasCB pfCB, void* pParam){ m_pfCB = pfCB; m_pParam = pParam; }

	//当前资源是否有效
	BOOL32 IsBasValid(void)	
	{ 
#ifdef _USE_XMPUEQP_
        return (m_tXmpuBas.m_dwEqpID != 0);
#else
		return m_tBasEqpRes.IsValid();
#endif
	}

	u16 GetBasEqpId(void)
	{
#ifdef _USE_XMPUEQP_
        return m_tXmpuBas.m_dwEqpID;
#else
        return  m_tBasEqpRes.m_tBasChnInfo.m_byEqpID;   
#endif
	}

	u16 GetBasChnIndex(void)
	{
#ifdef _USE_XMPUEQP_
        return 0;
#else
        return  m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx;   
#endif
	}

	//是否是该资源请求关键帧
	BOOL32 IsNeedKeyFrame(u16 wChnIndx)	{ return wChnIndx == m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx;	}

	BOOL32 IsEqpDisConnect(u8 byEqpID)	{ return m_tBasEqpRes.m_tBasChnInfo.m_byEqpID == byEqpID;	}

	BOOL32 IsEqpChnRetNAck(TTPBasNAck tNAck)
	{
		return (m_tBasEqpRes.m_tBasChnInfo.m_byEqpID == tNAck.m_byEqpID) && 
				(m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx == tNAck.m_wChnIndx);
	}

};

typedef struct tagTChairCap
{
	TTPName	m_tChair;			//主席名称
	u16		m_wSpeakerIndex;
	u16		m_wChairVidSndCap;
	u16		m_wChairAudSndCap;
	
	tagTChairCap()
	{
		Clear();
	}
	void Clear()
	{
		m_tChair.Clear();
		m_wChairAudSndCap = 0;
		m_wChairVidSndCap = 0;
		m_wSpeakerIndex = MIDSCREENINDEX;
	}

	u16 IsChairThreeVidSnd()		{	return m_wChairVidSndCap == 3; }
	u16 IsChairSingleVidSnd()		{	return m_wChairVidSndCap == 1; }
	
	u16 IsChairThreeAudSnd()		{	return m_wChairAudSndCap == 3; }
	u16 IsChairSingleAudSnd()		{	return m_wChairAudSndCap == 1; }
	
}TChairCap;

enum EmGetVidRet
{
	EmGetVidRet_Success,
	EmGetVidRet_BasDisCnnt,
	EmGetVidRet_VmpDisCnnt,
	EmGetVidRet_BWFull,
	EmGetVidRet_NoVid,
	EmGetVidRet_NoVmp,
	EmGetVidRet_VmpDisConnect,
};

typedef struct tagTInComingInfo
{
	TUmsCallInfo		m_tCallInfo;
	TTPConfTemplateBuf	m_tTemp;
	
	tagTInComingInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tCallInfo.Clear();
		m_tTemp.Clear();
	}
}TInComingInfo;

typedef struct tagTTransParam
{
	TTPMediaTransAddr	m_tAddr;
	u16					m_wSpeakerIndx;
	BOOL32				m_bMap;
	u32					m_dwEqpNode;
	
	tagTTransParam()
	{
		memset(this, 0, sizeof(tagTTransParam));
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTransParam));
	}

}TTransParam;


#endif // _h_callinnerstruct_h__
