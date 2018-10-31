#ifndef _h_procnodeds_h__
#define _h_procnodeds_h__

#include "umsobject.h"
#include "callinnerstruct.h"
#include "tphandle.h"
#include "callnodemgr.h"


class CUmsConfInst;
class CDsStrategy
{
protected:
public:
	virtual u16 GetDsToNode(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs) = 0;
};

//双流到节点的交换
class CDsStrategyToNodeForDual : public CDsStrategy
{
protected:
	u16 m_wDstNodeID;
public:
	CDsStrategyToNodeForDual(u16 wDstID):m_wDstNodeID(wDstID) {}
public:

	virtual u16 GetDsToNode(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);
};


//------------------- 到发言人的交换  begin -------------------
class CDSStrategyToSpeaker : public CDsStrategy
{
protected:
	BOOL32		m_bIsSupuer;		//最上级UMS
	TCapNode*	m_ptChair;
	TCapNode*	m_ptFarSpeaker;
	TCallNode*	m_ptSpeaker;
	virtual u16 GetDsToNode(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs) {return 0;}
public:
	void SetPara(TCapNode* ptChair, TCapNode* ptFarSpeaker, TCallNode* ptSpeaker, BOOL32 bIsSupuer)
	{
		m_ptChair = ptChair;
		m_ptFarSpeaker = ptFarSpeaker;
		m_ptSpeaker = ptSpeaker;
		m_bIsSupuer = bIsSupuer;
	}
	void GetVidAddr(CUmsConfInst* pInst, TTPTransAddr atChairRtp[TP_MAX_STREAMNUM], TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM], u32 adwRtpEqpNode[TP_MAX_STREAMNUM], BOOL32 bNeedBas = TRUE);
	void GetAudAddr(CUmsConfInst* pInst, 
		TTPTransAddr atChairRtp[TP_MAX_STREAMNUM], TTPTransAddr atChairRtcp[TP_MAX_STREAMNUM], 
		TTPTransAddr& tChairMixRtp, TTPTransAddr& tChairMixRtcp,
		u32 adwRtpEqpNode[TP_MAX_STREAMNUM], u32& dwMixAudEqpNode, BOOL32 bNeedBas = TRUE);

};

//主席 到 适配板 的交换
class CDsStrategyChairToBas : public CDSStrategyToSpeaker
{
protected:
public:
	virtual u16 GetDsToNode(CUmsConfInst* pInst, TUmsDsData atDsData[], u16 wMaxDs);
};




#endif // _h_procnodeds_h__
