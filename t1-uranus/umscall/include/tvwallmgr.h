#ifndef _h_tvwallmgr_h__
#define _h_tvwallmgr_h__
#include "tphandle.h"
#include "callinnerstruct.h"
#include "umsvmp.h"

#define TV_WALL_MAX_CHAN	HDU_STYLE_MAX_NUM * HDU_MAX_VMP_SUBCHAN

typedef struct tagTVWallInfo
{
	TTvChanInfo		m_tChanInfo;
	TBrdVmpRes*		m_ptVmp;
	TUmsVidFormat	m_tFormat;
	u16				m_wGetVidIndex;
	TGetVidAddr		m_tAddr;
	BOOL32			m_bAdjstRes;

	tagTVWallInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tChanInfo.Clear();
		m_tFormat.Clear();
		m_ptVmp = NULL;
		m_wGetVidIndex = TP_UMS_MAX_CALLNUM;
		m_bAdjstRes = FALSE;
	}
}TVWallInfo;

class CUmsConfInst;
class CTvWallMgr
{
public:
	CTvWallMgr(CUmsConfInst* pcInst);
	virtual ~CTvWallMgr();
	virtual BOOL32 Handler(CTpMsg *const ptMsg, CApp* pcApp);
	virtual BOOL32 Create();

public:
	u16 InitPort(u16 wStartPort);
	void ResetMediaIp(const TEqpRes& tConfDs);
	void Show();
	void ShowPortRes();
	void AdjustGetVidFailed(CUmsConfInst* pcInst, u16 wGetVidIndex);

	void ChannelConnect(CUmsConfInst* pcInst, TCallNode* ptNode);
	void HungUpNode(CUmsConfInst* pcInst, TCallNode* ptNode, EmCnsCallReason emRes);
	void HungUpConf(CUmsConfInst* pcInst);
	void ChangeSpeaker(CUmsConfInst* pcInst);

	void BrdVmpCB(TBrdVmpRes* ptRes, EmBrdVmpCBOprType emOpr);

public:
    void SetMediaKey(CUmsConfInst* pcInst, const TTPQTMediaKeyInfo& tInfo, TVWallInfo* ptInfo = NULL);
	
protected:
	void OnAddMonitor(CTpMsg *const ptMsg, CApp* pcApp);
	void OnDelMonitor(CTpMsg *const ptMsg, CApp* pcApp);
	void OnUptateMonitor(CTpMsg *const ptMsg, CApp* pcApp);
	void OnAskKey(CTpMsg *const ptMsg, CApp* pcApp);
	void HduPlanInfoReq(u16 wConfID, u16 wEpID);

private:

	void CreateMediaTrans(CUmsConfInst* pcInst, TVWallInfo* ptInfo);
	void DestroyMediaTrans(CUmsConfInst* pcInst, TVWallInfo* ptInfo);

	////////////////////////////////////////////////
	void EventHduPlayReq(CTpMsg *const ptMsg, CApp* pcApp);

	void EventHduPlayInd(CTpMsg *const ptMsg, CApp* pcApp);

	void EventHduStopReq(CTpMsg *const ptMsg, CApp* pcApp);
	
	void EventHduStopInd(CTpMsg *const ptMsg, CApp* pcApp);

	void EventHduAllStopReq(CTpMsg *const ptMsg, CApp* pcApp);

	void EventHduSetVolReq(CTpMsg *const ptMsg, CApp* pcApp);

	void EventHduSetVolInd(CTpMsg *const ptMsg, CApp* pcApp);

	void EventHduChangeModeReq(CTpMsg *const ptMsg, CApp* pcApp);

	void EventHduChangeModeInd(CTpMsg *const ptMsg, CApp* pcApp);

	void SendHduPlanInfo(CTpMsg *const ptMsg, CApp* pcApp);

	void NotifyMsgToCns(CApp* pcApp, u16 wEvent, const TUmsHandle& tHandle, const void* pBuf, u16 wSize);

	void NotifyMsgToAllOnLineChair(CApp* pcApp, u16 wEvent, const TUmsHandle& tHandle, const void* pBuf, u16 wSize);

private:
	CUmsConfInst* m_pcConf;
	TVWallInfo	m_atInfo[TV_WALL_MAX_CHAN];
};


#endif // _h_tvwallmgr_h__
