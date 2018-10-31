#ifndef _h_getvidaud_h__
#define _h_getvidaud_h__

#include "callinnerstruct.h"
#include "tplog.h"
#include "tplist.h"
#include "tpcommontype.h"
#include "umsconfinst.h"
#include "umseqpservice.h"

class CUmsConfInst;

//////////////////////////////////////////////////////////////////////////
//许成	码流调度新版本
#define TP_MAX_LOCAL_ADDR_NUM	TP_UMS_MAX_CALLNUM * 2 + TP_UMS_MAX_CALLNUM/TP_MAX_STREAMNUM

typedef struct tagTGetVidAddr
{
	TTPMediaTransAddr	m_atVidAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_atAudAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_atSmallAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_tMixAddr;
	u32					m_adwMediaNode[TP_MAX_STREAMNUM];	//仅供会场选看使用
	u32					m_dwMedia;
	
	tagTGetVidAddr()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTGetVidAddr));
	}

	tagTGetVidAddr(const TGetVidInfo& tInfo)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atVidAddr[wIndex] = tInfo.m_atVidAddr[wIndex];
			m_atAudAddr[wIndex] = tInfo.m_atAudAddr[wIndex];
			m_atSmallAddr[wIndex] = tInfo.m_atSmallVid[wIndex];
		}
	}

	tagTGetVidAddr(const tagTGetVidAddr& tAddr)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atVidAddr[wIndex] = tAddr.m_atVidAddr[wIndex];
			m_atAudAddr[wIndex] = tAddr.m_atAudAddr[wIndex];
			m_atSmallAddr[wIndex] = tAddr.m_atSmallAddr[wIndex];
			m_adwMediaNode[wIndex] = tAddr.m_adwMediaNode[wIndex];
		}

		m_dwMedia = tAddr.m_dwMedia;
		m_tMixAddr = tAddr.m_tMixAddr;
	}

	tagTGetVidAddr& operator=(const tagTGetVidAddr& tAddr)
	{
		if (this != &tAddr)
		{
			for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
			{
				m_atVidAddr[wIndex] = tAddr.m_atVidAddr[wIndex];
				m_atAudAddr[wIndex] = tAddr.m_atAudAddr[wIndex];
				m_atSmallAddr[wIndex] = tAddr.m_atSmallAddr[wIndex];
				m_adwMediaNode[wIndex] = tAddr.m_adwMediaNode[wIndex];
			}
			
			m_dwMedia = tAddr.m_dwMedia;
			m_tMixAddr = tAddr.m_tMixAddr;
		}

		return *this;
	}
	
}TGetVidAddr;

#define GET_VID_CHECK_NUM 32
typedef struct tagTAdjustSeat
{
	u16	m_awCheck[GET_VID_CHECK_NUM];
	tagTAdjustSeat()
	{
		Clear();
	}

	void Clear()
	{
		memset(m_awCheck, TP_INVALID_INDEX, sizeof(m_awCheck));
	}

	void AddCheck(BOOL32 bCheck)
	{
		for ( u16 wIndex = 0; wIndex < GET_VID_CHECK_NUM; wIndex ++ )
		{
			if ( TP_VALID_HANDLE(m_awCheck[wIndex]) )
			{
				continue;
			}

			if ( bCheck )
			{
				m_awCheck[wIndex] = 1;
			}
			else
			{
				m_awCheck[wIndex] = 0;
			}
			break;
		}
	}

	void DelCheck(BOOL32 bCheck)
	{
		for ( u16 wIndex = 0; wIndex < GET_VID_CHECK_NUM; wIndex ++ )
		{
			if ( !TP_VALID_HANDLE(m_awCheck[wIndex]) )
			{
				continue;
			}
			
			if ( bCheck )
			{
				if ( m_awCheck[wIndex] == 1 )
				{
					m_awCheck[wIndex] = TP_INVALID_INDEX;
				}
			}
			else
			{
				if ( m_awCheck[wIndex] == 0 )
				{
					m_awCheck[wIndex] = TP_INVALID_INDEX;
				}
			}
			break;
		}
	}

	BOOL32 IsAdjust()
	{
		BOOL32 bRet = FALSE;
		for ( u16 wIndex = 0; wIndex < GET_VID_CHECK_NUM; wIndex ++ )
		{
			if ( !TP_VALID_HANDLE(m_awCheck[wIndex]) )
			{
				continue;
			}

			bRet = TRUE;

			if ( m_awCheck[wIndex] == 0 )
			{
				return FALSE;
			}
		}

		return bRet;
	}
}TAdjustSeat;

class CDispatchInfo
{
public:
	CDispatchInfo();
	~CDispatchInfo();

public:
	EmGetVidRes	Init(CUmsConfInst* pcConf, u16 wDstEp, EmGetVidType emType, TCallVidFormat tRcvFormat, 
					BOOL32 bSmall, u16 wBandWidth, u16 wScreenNum, u16 wScreenIndex = TP_MAX_STREAMNUM, 
					BOOL32 bCascade = FALSE, u16 wHandle = TP_INVALID_INDEX);
	void	GetLocalAddr(TGetVidInfo& tAddr);
	void	SetDstAddr(TGetVidInfo& tAddr);
	void	SetScreenIndx(u16 wScreenIndx) { m_wScreenIndex = wScreenIndx; }
	void	Increment();
	void	Decrement();
	void	ClearCount();
	void	UpdateCascadeTran();
	void	UpdateSpeakerIndex();
	void	AskKeyFrame(BOOL32 bBySys = FALSE);

public:
	void	ReleaseScreen(u16 wScreenIndex);

	void	Show(u16 wConfID);
public:
	CUmsConfInst*	ConfInst() const { return m_pcConfInst; }
	EmGetVidType	GetVidType() const { return m_emType; }
	TCallVidFormat	VidFormat() const { return m_tRcvFormat; }
	const CBaseService* VmpService()	{ return m_pcVmp; }
	BOOL32			Working() const { return NULL != ConfInst(); }
	u16				GetDstEp() const { return m_wDstEp; }
	u16				ScreenIndex() const { return m_wScreenIndex; }
	u16				GetHandle() const { return m_wHandle; }
	void			SetHandle(u16 wHandle) { m_wHandle = wHandle; }
	u16				GetRmtHandle() const { return m_wRmtHandle; }
	void			SetRmtHandle(u16 wHandle) { m_wRmtHandle = wHandle; }
	u16				GetBandWidth() const { return m_wBandWidth; }
	TGetVidAddr		GetSrcAddr() const { return m_tSrcAddr; }
	u16				VidCount() { return m_wCount; }
	BOOL32			GetAdjustSeat() { return m_tAdjustSeat.IsAdjust(); }
	void			SetAdjustSeat(EmGetVidType emType)
	{
		if ( emType == em_GetVid_View )
		{//屏选看能调整坐席
			m_tAdjustSeat.AddCheck(TRUE);
		}
		else
		{
			m_tAdjustSeat.AddCheck(FALSE);
		}
	}


	BOOL32	IsEqualVidType(EmGetVidType emType)
	{
		if (emType == em_GetVid_Invalid || m_emType == em_GetVid_Invalid)
		{ 
            return FALSE;
		}

		// em_GetVid_View em_GetVid_ViewEp em_GetVid_OnlyAud此三种调度方式，需要完全匹配才可以复用
		if (em_GetVid_View == m_emType || em_GetVid_ViewEp == m_emType || em_GetVid_OnlyAud == m_emType)
		{
			if (emType == m_emType)
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}

		if (em_GetVid_View == emType || em_GetVid_ViewEp == emType || em_GetVid_OnlyAud == emType)
		{
			return FALSE;
		}

		return TRUE;
	}

private:
	void	Release();

private:
	void	Clear();
	BOOL32	AssignLocalAddr(TCallNode* ptNode);
	void	ReleaseLocalAddr();
	BOOL32	AssignVmp(TCallNode* ptDstNode, TCapNode* ptFatherNode);
	void	ReleaseVmp();
	BOOL32	AssignBas(TCallNode* ptDstNode, TCapNode* ptFatherNode);
	void	ReleaseBas();
	BOOL32	AssingBW();
	void	ReleaseBW(u16 wScreenNum);

private:
	void	CreateSrcAddr(TCallNode* ptDstNode, TCapNode* ptFatherNode);
	void	CreateDsToVmp(TCallNode* ptDstNode, TCapNode* ptFather);
	void	CreateDsToBas(TCallNode* ptDstNode, TCapNode* ptFatherNode);

private:
	static void	VmpServiceCB(const CBaseService* pcService, const EmServiceOpType emOpType, 
							const EmServiceRes emRes, void* param, u16 wTmp1);
	
private:
	CUmsConfInst*	m_pcConfInst;
	EmGetVidType	m_emType;
	TCallVidFormat	m_tRcvFormat;
	u16				m_wDstEp;
	u16				m_wScreenIndex;
	BOOL32			m_bSmall;
	u16				m_wCount;
	u16				m_wHandle;
	u16				m_wRmtHandle;
	u16				m_wBandWidth;
	u16				m_wScreenNum;
	BOOL32			m_bAssignBw;
	BOOL32			m_bFlowCtrl;
	TAdjustSeat		m_tAdjustSeat;

private:
	CDsListInfo			m_cDsList;
	CDsListInfo			m_cCascadeList;
	const CBaseService*	m_pcVmp;
	CScreenBasRes*		m_apcBasRes[TP_MAX_STREAMNUM];
	BOOL32				m_abViewScreen[TP_MAX_STREAMNUM];

private:
	TTPMediaTransAddr*	m_aptVidAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr*	m_aptAudAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr*	m_aptSmallAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr*	m_ptMixAddr;
	
	TTPMediaTransAddr	m_atVidAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_atAudAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_atSmallAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr	m_tMixAddr;

	TGetVidAddr			m_tSrcAddr;
};

class CGetVidAudEx
{
public:
	CGetVidAudEx();
	~CGetVidAudEx();

public:
	//级联信令处理
	BOOL32	Handler(CUmsConfInst* pcConf, CTpMsg* const pcMsg);
	
public:
	//分配码流调度	
	//emtype 为 em_GetVid_View 忽略 bsmall
	//其他调度类型忽略 tRcvFormat
// 	EmGetVidRes	Assign(CUmsConfInst* pcConf, u16 wDstEp, EmGetVidType emType, 
// 						TCallVidFormat tRcvFormat, BOOL32 bSmall, TGetVidAddr& tAddr, u16& wGetVidHande);
	EmGetVidRes	AssignByScreen(CUmsConfInst* pcConf, u16 wDstEp, u16 wScreenIndex, EmGetVidType emType,
								TCallVidFormat tRcvFormat, BOOL32 bSmall, TGetVidAddr& tAddr, u16& wGetVidHandle);
    
	//      根据索引获取Assign wScreenIndex
	u16     GetScreenIndex(u16 wGetVidIndex);
	//      根据索引获取Assign EpID
	u16     GetDstEpByIndex(u16 wGetVidIndex);
	
	//释放一个码流调度
	void	Release(CUmsConfInst* pcConf, u16 wGetVidIndex, EmGetVidType emType = em_GetVid_Invalid, BOOL32 bStopConf = FALSE);
//	void	ReleaseByScreen(CUmsConfInst* pcConf, u16 wGetVidIndex, u16 wScreenIndex);

	EmGetVidRes	UpdateAddr(CUmsConfInst* pcConf, EmGetVidType emType, u16& wGetVidIndex, TGetVidAddr& tAddr, u16 wScreenIndex, TCallVidFormat& tRcvFormat);

	//更新会场的发言坐席
	void	UpdateSpeakerIndex(CUmsConfInst* pcConf, u16 wEpID, u16 wScreenIndx);
	//请求关键帧
	void	AskKeyFrame(u16 wGetVidIndx, BOOL32 bbySys = FALSE);
	void	AskKeyFrameByRmtHandle(u16 wGetVidIndx, BOOL32 bbySys = FALSE);
	//是否提示 没有使用到 合成器
	BOOL32  IsNeedNotifyNoVmp( u16 wGetVidIndx );

	void	StopConf(u16 wConfID);

	void	Show(u16 wConfID);

    CDispatchInfo*	Find(CUmsConfInst* pcConf, const CBaseService* pcService);

private:
	u16		Find(CUmsConfInst* pcConf, u16 wDstEp, u16 wScreenIndex, EmGetVidType emType, TCallVidFormat tRcvFormat);
	u16		FindIdle();
	u16		FindByRmtHandle(u16 wHandle);
    void    ReleaseRepeatdGetVidAudForDown(CUmsConfInst* pcConf, EmGetVidType emType, u16 wDstEp, u16 wScreenIndex);

private:
	void	EventGetVidReq(CUmsConfInst* pcConf, CTpMsg* const pcMsg);
	void	EventGetVidRes(CUmsConfInst* pcConf, CTpMsg* const pcMsg);
	void	EventStopGetVidReq(CUmsConfInst* pcConf, CTpMsg* const pcMsg);

private:
	CDispatchInfo	m_acDispatchInfo[TP_UMS_MAX_CALLNUM];
	u16				m_wLastIndx;//用于偏移用 避免短时间内释放和分配的是同一个索引
};

#endif // _h_getvidaud_h__
