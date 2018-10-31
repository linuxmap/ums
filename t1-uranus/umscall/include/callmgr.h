#ifndef _h_callmgr_h__
#define _h_callmgr_h__

#include "tphandle.h"
#include "callinnerstruct.h"

class TCapNode;
class CUmsConfInst;
class CCallMgr : public CTpHandler
{
public:
	CCallMgr(CUmsConfInst* pcConf);
	virtual ~CCallMgr();
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack(TUmsHandle& tHandle, u16 wEvent, u8* pData);

	BOOL32 HandlerFromUmc(CTpMsg *const ptMsg);

public:
	BOOL32 IsChair()				{ return m_bIsChair; }
	void SetChair(BOOL32 bFlag)		{ m_bIsChair = bFlag; }
	void StopConf();

	BOOL32 MakeCallInfo(TMakeCallPara& tCallPara, TCapNode& tRmtNode, BOOL32 bIsAnswerCall);
	void MakeSecVidCap(TUmsVidCapParam& tRcv, TUmsVidCapParam& tSnd);
	void MakeAudCap(TUmsAudCap& tCap);
	BOOL32 MakeCascadeChair(TCapNode& tRmtNode);
	BOOL32 AnswerCascadeChair(TCascadeOpenChanCmd* ptCmd);
	BOOL32 OnCascadeChairAck(TCapNode* ptRmt, TCascadeOpenChanAck* ptAck);
	
	void OnCallEp(const TUmsHandle& tHandle, u8* pData);
	void OnCallExistEpFromCns(const TUmsHandle& tHandle, u8* pData);
	void OnCallExistEpFromCascade(const TUmsHandle& tHandle, u8* pData);

	void OnConfDropEpFromCns(const TUmsHandle& tHandle, u8* pData);
	void OnConfDropEpFromCascade(const TUmsHandle& tHandle, u8* pData);
	
	void OnUpdateEpCallInfo(const TUmsHandle& tHandle, TConfNodeCallUpdateTrList& tNodeList);
	void OnUpdateEpChanInfo(const TUmsHandle& tHandle, TConfNodeChanUpdateTrList& tNodeList);
	void OnDelEpNode(const TUmsHandle& tHandle, u8* pData);
	void OnCnsJoinConf(const TUmsHandle& tHandle,u8* pData);

	// 切源 远遥消息通知
	void OnUpdateEpVidFeccInfo(const TUmsHandle& tHandle, TConfEpVidFeccList& tNodeList);

	void FlowControl(u16 wEpID, u16 wScreeNo, u16 wBitRate);
	void AskKeyFrame(u16 wEpID, u16 wScreeNo);
	
	// umc会控消息
	// add by gaoyong
	void OnConfDropEpFromUmc(CTpMsg *const ptMsg);    
	void OnConfCallEpFromUmc(CTpMsg *const ptMsg);    
	void OnConfInviteEpFromUmc(CTpMsg *const ptMsg);  
	void OnConfJoinEpFromUmc(CTpMsg *const ptMsg);
public:
	//向上级报告结点信息
	void NotifyToHigherUpdateEp(TRefrenUiNodeList& tList);
	void NotifyToHigherVidFeccInfo(u16 wEpId);
	//上级上线
	void CallerConnect();

protected:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }

	// add by gaoyong
	EmCnsCallReason OnConfDropEp(u16 wEpID);   // 挂断一个会场
	EmCnsCallReason OnConfCallEp(u16 wEpID);  // 呼叫一个会场（会议列表中存在的未上线会场）
	EmCnsCallReason OnConfInviteEp(TTpCallAddr* ptAlias); // 邀请一个会场
	
	EmCnsCallReason OnConfCallMcuEp(u16 wEpID);  // 呼叫一个会场（会议列表中存在的未上线会场）
	EmCnsCallReason OnConfDropMcuEp(u16 wEpID);   // 挂断mcu 下级一个会场
	
protected:
	CUmsConfInst* m_pcConf;
	BOOL32	m_bIsChair;

};
#endif // _h_callmgr_h__

