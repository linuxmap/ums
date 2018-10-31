#ifndef _h_bandwidth_h__
#define _h_bandwidth_h__

#include "tpsys.h"
#include "callinnerstruct.h"

//带宽策略：
//每个会议都会配置带宽，该带宽主要是限制：除了发言人、主席等基本广播流之外的级联间码流调度。
//带宽分为上行和下行
//主要是针对UMS和UMS之间，本UMS的下行对应的是另外UMS的上线。二者必须都符合才能调用该码流。
typedef struct tagTBw
{
	u32		m_wBW;

	tagTBw() { memset(this, 0, sizeof(tagTBw)); }
}TBw;

class CBandwidth
{
public:
	CBandwidth() { memset(this, 0, sizeof(CBandwidth)); }
	~CBandwidth() { memset(this, 0, sizeof(CBandwidth)); }

	void StartConf(u32 wUpBW, u32 wDownBW);
	void StopConf();

	BOOL32 AssigneUpBW(u32 wBW, EmViewType eType);
	BOOL32 AssigneDownBW(u32 wBW, EmViewType eType);

	void ReleaseUpBW(u32 wBW, EmViewType eType);
	void ReleaseDownBW(u32 wBW, EmViewType eType);

	u32 GetBwInfoByType(EmViewType eType);
	u32	CurUpBw() { return m_wUpBWCfg - m_wUpBW; }
	u32	CurDownBw() { return m_wDownBWCfg - m_wDownBW; }

	void ShowBW();
public:
	BOOL32 IsUpBw(u32 wBW) { return m_wUpBW + wBW <= m_wUpBWCfg ? TRUE : FALSE; }
	BOOL32 IsDownBw(u32 wBW) { return m_wDownBW + wBW <= m_wDownBWCfg ? TRUE : FALSE; }
private:
	u32 m_wUpBWCfg;					//模板配置的最大上行带宽
	u32 m_wDownBWCfg;				//模板配置的最大下行带宽

	u32 m_wUpBW;					//当前占用的总上行
	u32 m_wDownBW;					//当前占用的总下行

	TBw m_atUpBW[em_View_End];		//每种业务占用的上行带宽
	TBw m_atDownBW[em_View_End];	//每种业务占用的下行带宽
};

#endif//#ifndef _h_bandwidth_h__

