#ifndef _h_pollmgr_h__
#define _h_pollmgr_h__

#include "umsconfinst.h"
#include "callinnerstruct.h"
#include "callnodemgr.h"
#include "innereventumscall.h"

//////////////////////////////////////////////////////////////////////////
//diaolei
//轮询需求：上级可以任意组合配置本级和所有下级的轮询顺序
//思路：
//1、轮询主业务由上级做，包括：状态、轮询列表、启停。
//2、每级都有适配。合成在最上级做。
//3、平滑：做在进适配前，当前轮询结点和下一个轮询结点不在一个UMS上时，由上做平滑。当在同一个UMS时，由这个UMS做平滑

typedef struct tagTPollListEx
{
	u16			m_wInterval;						//轮询间隔，单位秒
	u16			m_wNum;								//参与轮询数量
	TCallNode*	m_apcNode[TP_CONF_MAX_CNSNUM];

	tagTPollListEx()					{	Clear();  }
	BOOL32 IsValid(u16 wIndex)		{	return wIndex < TP_CONF_MAX_CNSNUM && m_apcNode[wIndex] != NULL; }
	void SetInterval(u16 interval)	
	{
		m_wInterval = interval < TP_CONF_TURN_MIN_INTERVAL ? TP_CONF_TURN_MIN_INTERVAL : interval; 
	}
	void Clear()
	{
		m_wInterval = 20;
		m_wNum = 0;
		for(u16 wIndex = 0; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
		{
			m_apcNode[wIndex] = NULL;
		}

	}
	
	u16 FindIndexByEp(u16 wEpID)
	{
		for(u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
		{
			if (((TCallNode*)m_apcNode[wIndex])->m_wEpID == wEpID)
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}
	void RemoveOneEp(u16 wEpID)
	{
		u16 wIndx = FindIndexByEp(wEpID);
		
		if ( !IsValid(wIndx) )
		{
			return ;
		}
		
		memmove(&m_apcNode[wIndx], &m_apcNode[wIndx+1], sizeof(m_apcNode[0])*(m_wNum - wIndx - 1));
	
		m_apcNode[m_wNum-1] = NULL;
		
		m_wNum--;
		
	}

	void AddOneEp(TCallNode* pcNode, u16 wIndex)
	{
		if ( wIndex >= TP_CONF_MAX_CNSNUM || m_wNum >=  TP_CONF_MAX_CNSNUM )
		{
			return ;
		}
		
		memmove(&m_apcNode[wIndex+2], &m_apcNode[wIndex+1], sizeof(m_apcNode[0])*(m_wNum - wIndex - 1));
		
		m_apcNode[wIndex+1] = pcNode;
		
		m_wNum++;
		
	}
}TPollListEx;

typedef struct tagTPollAddrEx
{
	u16					m_wPollEpID;						//记录正在被轮询结点ID
	u16					m_wPollIndx;						//记录正在被轮询的索引
	TTPMediaTransAddr*	m_aptLocalAddr[TP_MAX_STREAMNUM];	//本地两个平滑地址
	TTPTransAddr		m_atRmtRtcp[TP_MAX_STREAMNUM];		//上级存储下级Rtcp

	TTPMediaTransAddr*	m_aptSmallAddr[TP_MAX_STREAMNUM];	//本地两个小码流平滑地址
	TTPTransAddr		m_atSmallRmtRtcp[TP_MAX_STREAMNUM];	//上级存储小码流下级Rtcp

	tagTPollAddrEx()
	{
		Clear();
	}

	void Clear()
	{
		m_wPollEpID = TP_INVALID_INDEX;
		m_wPollIndx = TP_INVALID_INDEX;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_aptLocalAddr[wIndex] = NULL;
			m_atRmtRtcp[wIndex].Clear();

			m_aptSmallAddr[wIndex] = NULL;
			m_atSmallRmtRtcp[wIndex].Clear();
		}
	}

	BOOL32 IsValid()
	{
		return TP_VALID_HANDLE(m_wPollEpID);
	}
}TPollAddrEx;

typedef struct tagTTpPollList
{
	BOOL32	m_wUpdate;					//正在更新 不接收新的更新
	u32		m_dwFlag;					//更新标识
	u16		m_wInterval;				//轮询间隔，单位秒
	u16		m_wTotalNum;				//总数量
	u16		m_wCurNum;					//当前数量
	u16		m_awList[TP_CONF_MAX_CNSNUM];
	tagTTpPollList()
	{
		Clear();
	}
	void Clear()
	{
		m_wUpdate = FALSE;
		m_dwFlag = 0;
		m_wInterval = 5;
		m_wTotalNum = 0;
		m_wCurNum = 0;
		memset(m_awList, 0, sizeof(m_awList));
	}
}TTpPollList;

typedef struct tagTTpDownUms
{
	u16		m_wEpID;
	u16		m_wScreenNum;
	tagTTpDownUms()
	{
		Clear();
	}
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenNum = TP_MAX_STREAMNUM;
	}
}TTpDownUms;

#define DOWN_UMS_MGR 4
typedef struct tagTTpDownUmsMgr
{
	TTpDownUms	m_atDowNum[DOWN_UMS_MGR];
	tagTTpDownUmsMgr()
	{
		Clear();
	}
	void Clear()
	{
		for ( u16 wIndex = 0; wIndex < DOWN_UMS_MGR; wIndex ++)
		{
			m_atDowNum[wIndex].Clear();
		}
	}
	void SetValue(u16 wUmsEpID, u16 wScreenNum)
	{
		TTpDownUms* ptDowUms = NULL;
		for ( u16 wIndex = 0; wIndex < DOWN_UMS_MGR; wIndex ++)
		{
			if ( !TP_VALID_HANDLE(m_atDowNum[wIndex].m_wEpID) )
			{
				ptDowUms = &m_atDowNum[wIndex];
				continue;
			}

			if ( m_atDowNum[wIndex].m_wEpID == wUmsEpID  )
			{
				if ( m_atDowNum[wIndex].m_wScreenNum > wScreenNum )
				{
					m_atDowNum[wIndex].m_wScreenNum = wScreenNum;
				} 
				return;
			}
		}

		if ( NULL != ptDowUms )
		{
			ptDowUms->m_wEpID = wUmsEpID;
			ptDowUms->m_wScreenNum = wScreenNum;
		}
	}

	BOOL32 Check(u16 wUmsEpID, u16 wScreenNum)
	{
		for ( u16 wIndex = 0; wIndex < DOWN_UMS_MGR; wIndex ++)
		{
			if ( !TP_VALID_HANDLE(m_atDowNum[wIndex].m_wEpID) )
			{
				continue;
			}
			
			if ( m_atDowNum[wIndex].m_wEpID == wUmsEpID  )
			{
				if ( m_atDowNum[wIndex].m_wScreenNum <= wScreenNum )
				{
					return FALSE;
				}
			}
		}
		return TRUE;
	}
}TTpDownUmsMgr;


class CUmsConfInst;
class CPollMgr  : public CTpHandler
{
public:
	CPollMgr(CUmsConfInst* pcInst);
	~CPollMgr();
	
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	void Show();

	TPollAddrEx* GetCurAddr() { return m_ptCurAddr; }
	TPollAddrEx* GetOldAddr() { return m_ptOldAddr; }
	TTPTransAddr& GetUpRtp(u16 wScrIndx)  { return m_atRmtRtp[wScrIndx]; }
	TTPTransAddr& GetSmallUpRtp(u16 wScrIndx)  { return m_atSmallRmtRtp[wScrIndx]; }
	CDsListInfo& GetPollDs()	{ return m_tToPollDs; }
	TPollIframeCheck& GetIframeCheck() { return m_tIframeCheck; }
	const CBaseService* GetVmp() { return m_pcPollVmp; }

	BOOL32	IsPollStart() { return m_emStat == EmPollStat_Start; }
	BOOL32	IsPollUiOn()  { return m_emUiStat == EmPollStat_Start || m_emUiStat == EmPollStat_Suspend; }
	BOOL32	IsDefaultPoll() { return m_bIsDefaultPoll; }

	void TrySuspendPoll()
	{
		if( m_emUiStat != EmPollStat_Start || !Inst()->IsChairConf() ) return;
		if( Inst()->curSpeakerID() == m_wVirEpID ) return;//切轮询自己发言 则 不暂停
		KillTimer(evtp_ExeTurnList_time); m_emStat = EmPollStat_Suspend;
		m_emUiStat = m_emStat;
		NotifyPollStatToUI();
	}

#ifdef _USE_XMPUEQP_
	void XmpuBasCB( u32 dwType, CScreenBasRes* ptBasRes, void *pData );
#else
	void BasCB( CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes );
#endif
	void VmpCB( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes );

	void ResetMediaIp();

	//设置轮询间隔
	void SetPollTimeInterval(u16 wInterval) { m_tCfg.m_wInterval = wInterval; }

	void InitPollList(const TConfTurnList* ptList);
	void InitPollList();

	BOOL32 IsAddEpInPollList(TCallNode* ptNodeAdd);
    void AddLowInviteEp(TCallNode* ptNodeAdd);


	void StopConf();
	void AddNode(TCapNode* ptNode);
	void OnChanConnect(TCallNode* ptNode);
	void OnHungup(TCallNode* ptNode);
	void AdjustCnsSpeaker(TCallNode* ptNode);

	//开启
	void OnCncStartPollReq(CTpMsg *const ptMsg);
	void OnUmcStartPollReq(CTpMsg *const ptMsg);

	//暂停 保持当前轮询状态
	void OnCncSuspendPollReq(CTpMsg *const ptMsg); 
	void OnUmcSuspendPollReq(CTpMsg *const ptMsg);

	//停止
	void OnCncStopPollReq(CTpMsg *const ptMsg); 
	void OnUmcStopPollReq(CTpMsg *const ptMsg);

	//更新
	void OnUpdatePollListFromUmc(CTpMsg *const ptMsg);
	void OnUpdatePollListFromCnc(CTpMsg *const ptMsg);

	//收到上级轮询某结点请求：先判断老结点是否本地，如果是则需先做平滑，不是则直接建到上级交换
	void OnCasecadePollEpReq(CTpMsg *const ptMsg);
	//收到下级的回应：有错误，比如：无视频源、已掉线、无带宽、无适配等，则继续轮询下一个
	void OnCasecadePollEpRsp(CTpMsg *const ptMsg);

	void OnIframeBySrcNty(CTpMsg *const ptMsg);

	//轮询定时 只有上级有
	void OnPollTimer(CTpMsg *const ptMsg);

	EmTPPollResult StartPoll();
	EmTPPollResult SuspendPoll(BOOL32 bSuspend, BOOL32 bTimer = FALSE);
	EmTPPollResult StopPoll();

	BOOL32 UpdatePollList(TTpPollListNtfy& tList, TTpPollListInd& tInd);

	void NotifyPollListToUI(BOOL32 bCNC = TRUE, BOOL32 bUmc = TRUE, TLogUser* ptUser = NULL);
	void NotifyPollStatToUI(TLogUser* ptUser = NULL);

	void AskKeyFrame(u16 wScreenIndx, BOOL32 bBySys);

	BOOL32 GetLocalPollInAddr(TTPMediaTransAddr& tAddr, u32& dwEqpNode, u16 wScreenIndx, u16 wPollEpSpeakerIndex);
	BOOL32 GetLocalPollOutAddr(TTPMediaTransAddr& tAddr, u32& dwEqpNode, u16 wScreenIndx);
private:

	BOOL32 UpdatePollTempList(TTpPollListNtfy& tList);

	EmTPPollResult PollNextEp(u16 wPollIndx = TP_INVALID_INDEX);
	void CreatePollEpMedia(u16 wCurPollEp, u16 wPollIndx, BOOL32 bDownUmsRsp = FALSE);
	BOOL32	HavePollEp();

	u16 GetNextPollEp(u16 wCurIndx);

	void SetIFrameCheck();
	void DestroyIframeCheck();

	void PollClear();

	void NextAddr();

public:
//////////////////////////////////////////////////////////////////////////
//虚拟结点态
	void InitVirNode();
	void ReleaseVirNode();
	void AdjustDsToVirNode();

private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	friend class CNetPortMgr;
	
protected:
	EmPollStat		m_emUiStat;			//界面轮询状态
	EmPollStat		m_emStat;			//轮询状态

	BOOL32			m_bIsDefaultPoll;	//是否是默认列表

	TPollAddrEx*	m_ptCurAddr;
	TPollAddrEx*	m_ptOldAddr;
	TPollAddrEx		m_tAddrOne;
	TPollAddrEx		m_tAddrTwo;

	TTpDownUmsMgr	m_tFailEpID;							//级联会议时，下级失败的UMS节点

	TTPMediaTransAddr*	m_aptLocalChair[TP_MAX_STREAMNUM];	//本地平滑后地址，无合成，无适配时，需要占用

	TTPTransAddr	m_atRmtRtp[TP_MAX_STREAMNUM];//保存上级rtp地址
	TTPTransAddr	m_atSmallRmtRtp[TP_MAX_STREAMNUM];//保存上级Small rtp地址

	BOOL32				m_bBas;
	TCallVidFormat		m_tChairFmt;					//主席的接收格式
	
	CScreenBasRes*		m_apcBasRes[TP_MAX_STREAMNUM];  //适配 一旦需要 则固定占用，除非停止

	u32					m_dwBw;							//当前占用的带宽

	const CBaseService* m_pcPollVmp;					//主席单屏时候用 只有上级合成
	BOOL32				m_bVmpStart;					//合成是否开启
	
	TPollIframeCheck	m_tIframeCheck;					//关键帧检测信息
	
	TPollListEx			m_tCfg;

	TTpPollList			m_tUiListTemp;					//更新时做备份

	CDsListInfo			m_tToPollDs;

	BOOL32				m_bPrint;						//定时轮询打印开关

	u16					m_wVirEpID;
	CDsListInfo			m_tVirDs;
};


#endif // _h_pollmgr_h__