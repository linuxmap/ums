#ifndef _h_callnodemgr_h__
#define _h_callnodemgr_h__
#ifdef WIN32
#pragma warning(disable : 4786) 
#endif
#include <map>
#include "callinnerstruct.h"
#include "tphandle.h"

typedef void (*PForEachFun)(TCallNode* pNode, TRmtChan* ptAddr, u16 lv);


class TCapNode : public TCallNode
{
public:
	u32					m_dwStackHandle;		//协议栈句柄
	BOOL32				m_bIsCaller;			//是否本地主呼
	TEqpRes				m_tAdapterEqp;			//接入，需要分配
	TEqpRes				m_tMediaEqp;			//转发，需要分配

	TRmtChan			m_tRmtChan;

	CLocalChanAddrListItor		m_aptChanAddr[TP_MAX_STREAMNUM];	//主流接收通道，音视频
	CLocalSmallChanAddrListItor	m_aptSmallChanAddr[TP_MAX_STREAMNUM];//小码流接收通道 视频
	CLocalDualAddrListItor		m_ptDualAddr;						//双流接收地址
	CLocalAudMixAddrListItor	m_ptMixAddr;						//混音接收地址


	CDsListInfo					m_tDsList;

	CCascadeChairListItor		m_ptCasCadeChairAddr;	//级联时的主席通道

	EMScreenObj		m_emLastObj;
	EMScreenObj		m_aemObj[TP_MAX_STREAMNUM];

	CResFrmMgr		m_atResFrm[TP_MAX_STREAMNUM];

	s32				m_hMcuChan; // 结点类型是mcu时，，级联mcu需要用到
	s32				m_hMcuAppChan;
	s32				m_nMcuReqID;

	BOOL32          m_bSetMediaKeyMT;

	BOOL32			m_bAdjustChanOn; // 是否需要调用AdjustNodeChanOn
	BOOL32			m_bIsKedaManu; // 是否是渠道终端
	u16				m_bKedaManuCheckNum; // 检测次数			

	TCapNode()
	{
		Clear();

		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atResFrm[wIndex].SetTNode((TCapNode*)this);
		}
	}

	virtual u32 GetAdapterNode()	{return m_tAdapterEqp.m_dwEqpNode;}

	virtual void Clear()
	{
		m_bIsCaller = TRUE;
		m_bSetMediaKeyMT = TRUE;
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_aptChanAddr[wIndex] = NULL;
			m_aptSmallChanAddr[wIndex] = NULL;
			m_aemObj[wIndex] = emObjSelf;
			m_atResFrm[wIndex].Clear();
		}
		m_emLastObj = emObjSelf;
		m_ptDualAddr = NULL;
		m_ptMixAddr = NULL;
		m_ptCasCadeChairAddr = NULL;
		m_tRmtChan.Clear();
		m_tAdapterEqp.Clear();
		m_tMediaEqp.Clear();

		m_hMcuChan = 0;
		m_hMcuAppChan = 0;
		m_nMcuReqID = 0;

		m_bAdjustChanOn = FALSE;
		m_bIsKedaManu = FALSE;
		m_bKedaManuCheckNum = 0;

		m_dwStackHandle = 0;
		TCallNode::Clear();
	}
	
	virtual void HungUp()
	{
		m_bIsCaller = TRUE;
		m_dwStackHandle = 0;
		m_tRmtChan.Clear();
		m_tAdapterEqp.Clear();
		m_tMediaEqp.Clear();

		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_aemObj[wIndex] = emObjSelf;
			m_atResFrm[wIndex].Clear();
		}
		m_emLastObj = emObjSelf;
		m_bSetMediaKeyMT = TRUE;

		m_hMcuChan = 0;
		m_hMcuAppChan = 0;
		m_nMcuReqID = 0;

		m_bAdjustChanOn = FALSE;
		m_bIsKedaManu = FALSE;
		m_bKedaManuCheckNum = 0;

		TCallNode::HungUp();
	}	
	BOOL32 IsResReady()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (m_aptChanAddr[wIndex] == NULL)
			{
				return FALSE;
			}
			if ( m_aptSmallChanAddr[wIndex] == NULL )
			{
				return FALSE;
			}
		}
		if (m_ptDualAddr == NULL)
		{
			return FALSE;
		}
		if (m_ptMixAddr == NULL)
		{
			return FALSE;
		}
		return m_tAdapterEqp.IsValid() && m_tMediaEqp.IsValid();
	}

	BOOL32 ResetIpForRes(u32 dwResetIP)
	{
		if (!this->IsResReady())
		{
			return FALSE;
		}
		
		if (dwResetIP == this->m_tMediaEqp.m_dwEqpIp)
		{
			return FALSE;
		}
		
		TChanRcvAddr* ptVirLocalNode = NULL;
		u16 wChanIndex = 0;
		for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
		{
			ptVirLocalNode = &this->m_aptChanAddr[wChanIndex]->m_tVid;
			ptVirLocalNode->m_tRtpAddr.SetIP(dwResetIP);
			ptVirLocalNode->m_tRtcpForRcv.SetIP(dwResetIP);
			ptVirLocalNode->m_tRtcpForSnd.SetIP(dwResetIP);
		}
		
		//接收视频地址
		for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
		{
			ptVirLocalNode = &this->m_aptChanAddr[wChanIndex]->m_tAud;	
			ptVirLocalNode->m_tRtpAddr.SetIP(dwResetIP);
			ptVirLocalNode->m_tRtcpForRcv.SetIP(dwResetIP);
			ptVirLocalNode->m_tRtcpForSnd.SetIP(dwResetIP);		
			
		}
		
		for (wChanIndex = 0; wChanIndex < TP_MAX_STREAMNUM; ++wChanIndex)
		{
			ptVirLocalNode = this->m_aptSmallChanAddr[wChanIndex];
			ptVirLocalNode->m_tRtpAddr.SetIP(dwResetIP);
			ptVirLocalNode->m_tRtcpForRcv.SetIP(dwResetIP);
			ptVirLocalNode->m_tRtcpForSnd.SetIP(dwResetIP);
		}
		
		this->m_ptMixAddr->m_tRtpAddr.SetIP(dwResetIP);
		this->m_ptMixAddr->m_tRtcpForRcv.SetIP(dwResetIP);
		this->m_ptMixAddr->m_tRtcpForSnd.SetIP(dwResetIP);
		
		this->m_ptDualAddr->m_tVid.m_tRtpAddr.SetIP(dwResetIP);
		this->m_ptDualAddr->m_tVid.m_tRtcpForRcv.SetIP(dwResetIP);
		this->m_ptDualAddr->m_tVid.m_tRtcpForSnd.SetIP(dwResetIP);
		
		this->m_ptDualAddr->m_tAud.m_tRtpAddr.SetIP(dwResetIP);
		this->m_ptDualAddr->m_tAud.m_tRtcpForRcv.SetIP(dwResetIP);
		this->m_ptDualAddr->m_tAud.m_tRtcpForSnd.SetIP(dwResetIP);

		return TRUE;
	}
};


class CUmsConfInst;
class CCallNodeMgr : public CTpHandler
{
public:
	CCallNodeMgr(CUmsConfInst* pcInst);
	~CCallNodeMgr();
	virtual BOOL32 Handler( CTpMsg *const ptMsg ){	return FALSE;};

	virtual BOOL32 Create();
	
	void StopConf();
public:
	//对本级会场的结点操作(不包括上级UMS)
	TCapNode* FirstNode();			//返回本级的第一个结点
	TCapNode* NextLoalNode(TCallNode* ptNode);
	TCapNode* GetLocalNode(u16 wEpID);
	TCapNode* GetLocalNode(TTpCallAddr& tCallAlias);	

	void InitCallNode(TEpAddrList& tList,TTemplateConfEx& tTempEx );
	
	TCapNode* AddNewCall(TTpCallAddr& tDstAlias, BOOL32& bExist);	//添加一个会场

	TCapNode* FirstNeedCallNode();	
	void SetLastCallNode(TCapNode* ptNode);

	void addepip(u16 wEpid, u32 dwEpIp);
	void delepip(u16 wEpid);
	BOOL32 ismtip(const u32 dwIp);
	void showip();
public:
	//本级操作（包括上级UMS）
	TCapNode* GetCapsetNode(u16 wEpID);	//返回本级的呼叫结点(包括上级UMS)	
	void SetNodeCapSet(TCapNode* ptNode, const TUmsNodeCapset& tNodeCap);
	//add
	void SetDualNodeCapset(TCapNode* ptNode, const TUmsNodeCapset& tNodeCap);//设置双流结点的能力
	void GetDualNodeCapset(TCapNode* ptNode, TUmsNodeCapset& tNodeCap);
	TVidChanPara* GetChanByHandle(u16 wEpID, EmUmsCodecType enChanType, HandleChannle chanHandle);
	TChanPara* GetChanByIndex(u16 wEpID, EmUmsCodecType enChanType, u16 wIndex);
	TVidChanPara* GetVidChanByIndex(u16 wEpID, EmUmsCodecType enChanType, u16 wIndex);

	TCapNode* GetCaller()		{ return (TCapNode*)m_aptCallNode[CALLER_EP_INDEX]; }

public:
	void AdjustNodeRes( u16 wEpID, u16 wScreenIndx, EmTpVideoResolution emRes, BOOL32 bReset = FALSE);
	void AdjustNodeFrame( u16 wEpID, u16 wScreenIndx, u16 wFrame, BOOL32 bReset = FALSE);

public:
	//对所有结点操作
	void MakeCallerHandle(TUmsHandle& tHandle, u16 wEpID);
	TCallNode* GetNode(u16 wEpID);
	TCallNode* GetNodeByChildIDList(TCallNode* ptRoot, u16 awLowEpID[], u16 wNum, TCallNode** pParent);
	TCallNode* GetNodeByChildEpID(TCallNode* ptRoot, u16 wLowerEp);
	TCallNode* GetNodeByName(TTPAlias& tAlias, TCallNode* ptRoot);
	//获取呼叫类别
	TCallNode* GetCallLev(TCapNode &ptCurNode);
	//获取呼叫级别最高且可用的类型
	void GetValidCallType(TTpCallAddr& tCallAddr);
	//获取所有结点
	u16 GetAllNode(u16 atNodeID[], u16 wMaxNum);
	//获取包括ROOT的子节点列表
	u16 GetAllNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot);
	//获取不包括ROOT的子节点列表
	u16 GetAllChildNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot);
		
	TCapNode* GetForeFatherNode(TCallNode* ptNode);
	TCapNode* GetForeFatherNode(u16 wEpID);

	BOOL32 GetPathKey(TEpPathKey& tKeyID, u16 wEpID);

	//删除一个结点及其子节点
	void DeleteNode(TCallNode* ptNode);

	//增加一个下级子列表
	TCallNode* AddChildNode(u16 wParentID, TConfNodeCallUpdateTr& tDstInfo);
	TCallNode* AddChildNodeForMcu(TCapNode* ptMcuNode, TUmsMcuRosterItem& tRosterItem);
	TCallNode* AddChildNodeForMcu(TCapNode* ptMcuNode, TUmcMcuPart& tPart);

	//初始化TEpID结构体
	BOOL32 InitTEpKey( TEpKey& tEpID, BOOL32 bIsUPToDown, u16 wLocalEpID, u16 wLowerEpID=TP_INVALID_INDEX );
	//从TEpID结构体中取得本地的EpID
	u16 GetLocalEpIDByTEpKey( u16 wRootEpID, const TEpKey& tEpID );

	TCallNode* GetNodeUnderThisUms(TCapNode* pUmsNode, u16 wEpId);

public:
	void ForEachTreeNode(PForEachFun pCbFun, TCallNode* pRootNode, u16 lv);

	BOOL32 AssignDsRes(BOOL32 bIsNode, TEqpRes* ptRes, u32_ip dwNodeIp=0);
	BOOL32 AssignNodeRes(TCapNode* ptNode, TEqpRes*ptAdatper);
	BOOL32 ReleaseNodeRes(TCapNode* ptNode);
	BOOL32 AdjustResOnChanConnect(TCapNode* ptNode);

private:
	
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	void ClearAllChildNode(TCallNode* ptNode);

	//查找一个空闲的下级结点位置
	u16 FindIdleChildNode();

	u16 GetNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot);
protected:

	//会议ID从1编号
	TCapNode*		m_ptCurCallNode;						//当前需要呼叫的结点
	TCapNode*		m_ptHeadNode;							//根节点

	TCallNode*		m_aptCallNode[TP_CONF_MAX_CNSNUM];		//会议内所有会场，包括下级的

	std::map<u16,u32>		m_mapEpIp;
};



#endif // _h_callnodemgr_h__
