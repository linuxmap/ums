#ifndef _h_nodefsm_h__
#define _h_nodefsm_h__

#include "callinnerstruct.h"
#include "umsobject.h"
#include "tpsys.h"
#include "tpcommontype.h"
#include "getvidaud.h"

//选看独立
//合成广播 > 讨论 > 发言人

s8* GetNodeObj(EMScreenObj emObj);

class CUmsConfInst;
class CNodeFsm;
class CNodeFsmMgr
{
public:
	CNodeFsmMgr(CUmsConfInst* pcInst);
	~CNodeFsmMgr();
	void Init();
	void Quit();

	void ChanConnect(TCapNode* ptNode);

	void UpdateMediaTrans(TCapNode* ptNode, BOOL32 bYouAreSeeing = FALSE);
	void UpdateMediaTrans(u16 wEpID, BOOL32 bYouAreSeeing = FALSE);

	void ChangeSpeaker(TCapNode* ptNode);

	void StartDis(TCapNode* ptNode);

	void StopDis(TCapNode* ptNode);

	void SelView(TCapNode* ptNode, u16 wScreenIndx);
	void UnView(TCapNode* ptNode, u16 wScreenIndx);

	void StartVmpBrd(TCapNode* ptNode, u16 wScreenIndx = MIDSCREENINDEX);
	void StopVmpBrd(TCapNode* ptNode, u16 wScreenIndx = MIDSCREENINDEX);
	
	void StartPoll(TCapNode* ptNode);
	void StopPoll(TCapNode* ptNode);

	void AskKeyFrame(TCapNode* ptNode, u16 wScreenIndx, BOOL32 bBySys = FALSE);
protected:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcConf; }

	void	CreateMediaTrans(TCapNode* ptNode, TTransParam atVidParam[], TTransParam atAudParam[] , 
							TTransParam& tMixVid, TTransParam& tMixAud);
	void	CreateMediaTransUMS(TCapNode* ptNode, TTransParam atVidParam[], TTransParam atAudParam[] , 
							TTransParam& tMixVid, TTransParam& tMixAud);

	BOOL32	CheckEmObj(EMScreenObj emObj);

	void ChangeState(TCapNode* ptNode, BOOL32 bYouAreSeeing = TRUE);
private:
	CUmsConfInst*	m_pcConf;	
	CNodeFsm*		m_acFsm[emObjLookedEnd];
};

class CNodeFsm
{
public:
	CNodeFsm(CUmsConfInst* pcConf, EMScreenObj state):m_pcConf(pcConf),m_emState(state)		{}
	~CNodeFsm()	{}
	
	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam) = 0;
	virtual void GetAudSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetDisAudSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetAudSrcAddrInMixMode( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam) { }
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj) { }

	virtual	BOOL32 GetStateForChangeSpeaker(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForAdjustSeat(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForStartDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForStopDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForSelView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForUnView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForStartVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForStopVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };

	virtual	BOOL32 GetStateForStartPoll(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };
	virtual	BOOL32 GetStateForStopPoll(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj) { return FALSE; };

	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys) { return FALSE; } 
protected:
	EMScreenObj	m_emState;
	CUmsConfInst*	m_pcConf;
};

class CNodeFsmSelf : public CNodeFsm
{
public:
	CNodeFsmSelf(CUmsConfInst* pcConf):CNodeFsm(pcConf, emObjSelf){}
	~CNodeFsmSelf()	{}
	
	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
    virtual void GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam);
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);

	virtual	BOOL32 GetStateForChangeSpeaker(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForSelView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartPoll(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);

	
protected:
};

class CNodeFsmSpeaker : public CNodeFsm
{
public:
	CNodeFsmSpeaker(CUmsConfInst* pcConf):CNodeFsm(pcConf, emObjSpeaker){}
	~CNodeFsmSpeaker()	{}

	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam);
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);

	virtual	BOOL32 GetStateForChangeSpeaker(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForSelView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual	BOOL32 GetStateForStartPoll(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);
protected:
};

class CNodeFsmChair : public CNodeFsm
{
public:
	CNodeFsmChair(CUmsConfInst* pcConf):CNodeFsm(pcConf, emObjChair){}
	~CNodeFsmChair()	{}
	
	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam);
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);
	
	virtual	BOOL32 GetStateForChangeSpeaker(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForSelView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	
	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);
protected:
};

class CNodeFsmDis : public CNodeFsm
{
public:
	CNodeFsmDis(CUmsConfInst* pcConf):CNodeFsm(pcConf, emObjDiscard){}
	~CNodeFsmDis()	{}

	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam);
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);

	virtual	BOOL32 GetStateForStopDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForSelView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual	BOOL32 GetStateForStartPoll(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);
protected:	
};

class CNodeFsmVmpBrd : public CNodeFsm
{
public:
	CNodeFsmVmpBrd(CUmsConfInst* pcConf):CNodeFsm(pcConf, emObjVmpBrd){}
	~CNodeFsmVmpBrd()	{}

	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);

	virtual	BOOL32 GetStateForSelView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStopVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);
protected:	
};

class CNodeFsmView : public CNodeFsm
{
public:
	CNodeFsmView(CUmsConfInst* pcConf):CNodeFsm(pcConf, emObjView){}
	~CNodeFsmView()	{}

	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);

	virtual	BOOL32 GetStateForUnView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);
protected:	
};

class CNodeFsmPoll : public CNodeFsm
{
public:
	CNodeFsmPoll(CUmsConfInst* pcConf):CNodeFsm(pcConf, emObjPoll){}
	~CNodeFsmPoll()	{}
	
	virtual void GetVidSrcAddr( TCapNode* ptNode, u16 wScreenIndx, TTransParam& tParam);
	virtual void GetObj( TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);
	 
	virtual	BOOL32 GetStateForStartPoll(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStopPoll(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForChangeSpeaker(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStartDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStopDis(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForSelView(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);
	virtual	BOOL32 GetStateForStopVmpBrd(TCapNode* ptNode, u16 wScreenIndx, EMScreenObj& emObj);

	virtual BOOL32 AskKeyFrame(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);
protected:	
};

#endif
