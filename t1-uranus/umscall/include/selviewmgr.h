#ifndef _h_selviewmgr_h__
#define _h_selviewmgr_h__

#include "tphandle.h"
#include "eqpinterface.h"
#include "callinnerstruct.h"
#include "umsconfigex.h"
#include "umsconfinst.h"
#include "umsvmp.h"

//////////////////////////////////////////////////////////////////////////
//coder : 刁磊
//约束：只能选看本级或者下级会场

//UMC可以操作会场列表中的所有会场进行选看，但选看目标必须在选看会场的本级或者下级。
//因此，UMS只处理本级选看会场，不是本级会场，则转给相应的UMS进行处理。最终选看状态要更新到最上级UMS。

//关键帧请求:在本级处理

//约束：1、同一个屏的请求操作，必须等处理结束给出ntfy或者回应后才能进行下一次处理，否则拒绝。
//2、回应即Ind，只有在错误情况下，才回应。一般根据ntfy为准。
//3、回应 一般是给操作方（界面）回应，并不区分具体用户。界面比如cnc，umc。

#define UMS_MAX_SELVIEW_NUM 100

typedef struct tagTTPSession
{
	EmUIType	m_emType;
	u8			m_auReverse[20];
	tagTTPSession()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPSession));
	}
}TTPSession;

typedef struct tagTSelViewMgr
{
	BOOL32			m_bLocal;//是否本级操作
	BOOL32			m_bEpSel;
	TTPSelViewReq	m_tSelView;

	TBrdVmpRes*			m_ptItor;
	TGetVidAddr			m_tGetAddr;   //选看上调码流
	u16                 m_wGetIndex;  //上调码流的index，释放的时候会用到

	tagTSelViewMgr()
	{
		Clear();
	}

	void Clear()
	{
		m_bLocal = FALSE;
		m_bEpSel = FALSE;
		m_tSelView.Clear();
		m_ptItor = NULL;
		memset(&m_tGetAddr, 0, sizeof(m_tGetAddr));
		m_wGetIndex = TP_UMS_MAX_CALLNUM;
	}

	BOOL32 IsValid()
	{
		return m_tSelView.IsValid();
	}
	
	void SetView(TTPSelViewReq& tView)
	{
		memcpy(&m_tSelView, &tView, sizeof(m_tSelView));
	}

}TSelViewMgr;

typedef struct tagTEpViewInfo
{
	u16			m_wEpID;
	TSelViewMgr	m_atViewMgr[TP_MAX_STREAMNUM];

	tagTEpViewInfo()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atViewMgr[wIndex].Clear();
		}
		m_wEpID = TP_INVALID_INDEX;
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atViewMgr[wIndex].Clear();
		}
	}

	BOOL32 IsHavView()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if ( m_atViewMgr[wIndex].IsValid() )
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL32 Valid()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}

	BOOL32 IsNoGetVidView(u16 wScreenIndex)
	{// 三屏会场选看一个单屏的时候，三屏会场两边屏就是这种情形
		if (m_atViewMgr[wScreenIndex].m_tSelView.m_wScreenIndx < TP_MAX_STREAMNUM && 
			m_atViewMgr[wScreenIndex].m_wGetIndex >= TP_UMS_MAX_CALLNUM)
		{
			return TRUE;
		}
		return FALSE;
	}

}TEpViewInfo;

class CUmsConfInst;
class CSelView  : public CTpHandler
{
public:
	CSelView(CUmsConfInst* pcInst):CTpHandler(pcInst) {  }
	~CSelView() { InstClear(); }
	
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	void Show();

	//请求选看
	void OnSelViewUmc(CTpMsg *const ptMsg);
	void OnSelViewCnc(CTpMsg *const ptMsg);

	//级联间 选看回应
	void OnSelViewCasecadeInd(CTpMsg *const ptMsg);

	//上级UMC取消所有选看
	void OnUnSelAllView(CTpMsg *const ptMsg);

	//选看状态通知
	void OnSelViewNtfy(CTpMsg *const ptMsg);

	void HungUpNode(TCallNode* ptNode);

	void AskKeyFrame(u16 wEpID, u16 wScreenIndx);

	void StopConf();
	void AdjustCnsSpeaker(TCallNode* ptNode); 

	void NtfyAllSelInfoToUI(EmTpOprType emType, TLogUser* ptUser = NULL);

	void GetSelSrcAddr( u16 wEpID, u16 wScreenIndx, TTPMediaTransAddr& tAddr, u32& dwEqpNode );
	s8*	GetSelObj(u16 wEpID, u16 wScreenIndx, u16& wVidNum);

	void BrdVmpCB(TBrdVmpRes* ptRes, EmBrdVmpCBOprType emOpr);
	void AdjustGetVidFailed(CUmsConfInst* pcInst, u16 wGetVideIndex, EmGetVidRet emRet);
protected:
	EmViewRetReason SelView(TTPSelViewReq& tView, TEpViewInfo* ptOutInfo);
	EmViewRetReason UnSelView(TTPSelViewReq& tView, BOOL32 bNtfy = TRUE);
	EmViewRetReason ConvertGetVidReason(const EmGetVidRes emGetVid);
	void NtfySelInfoToUI(TEpViewInfo* ptView);
	
protected:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	friend class CNetPortMgr;

	TEpViewInfo* FindIdle();
	TEpViewInfo* FindByEP(u16 wEpID);
	TEpViewInfo* FindByBasRes(CScreenBasRes* ptBasRes);

	void ReleaseItor();

	void InstClear();

	// 为选看的会场恢复分辨率
	BOOL32   RestoreAdjustedResForSelEp(u16 wSelTargetEp, u16 wScreenIndex);
	// 选看结束，不需要大图像的的讨论会场 降分辨率
    BOOL32   AdjustResForUnSelEp(u16 wSelTargetEp, u16 wScreenIndex);	

	
private:

	TEpViewInfo m_atSelView[UMS_MAX_SELVIEW_NUM];
};

#endif