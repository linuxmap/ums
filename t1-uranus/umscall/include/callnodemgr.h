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
	u32					m_dwStackHandle;		//Э��ջ���
	BOOL32				m_bIsCaller;			//�Ƿ񱾵�����
	TEqpRes				m_tAdapterEqp;			//���룬��Ҫ����
	TEqpRes				m_tMediaEqp;			//ת������Ҫ����

	TRmtChan			m_tRmtChan;

	CLocalChanAddrListItor		m_aptChanAddr[TP_MAX_STREAMNUM];	//��������ͨ��������Ƶ
	CLocalSmallChanAddrListItor	m_aptSmallChanAddr[TP_MAX_STREAMNUM];//С��������ͨ�� ��Ƶ
	CLocalDualAddrListItor		m_ptDualAddr;						//˫�����յ�ַ
	CLocalAudMixAddrListItor	m_ptMixAddr;						//�������յ�ַ


	CDsListInfo					m_tDsList;

	CCascadeChairListItor		m_ptCasCadeChairAddr;	//����ʱ����ϯͨ��

	EMScreenObj		m_emLastObj;
	EMScreenObj		m_aemObj[TP_MAX_STREAMNUM];

	CResFrmMgr		m_atResFrm[TP_MAX_STREAMNUM];

	s32				m_hMcuChan; // ���������mcuʱ��������mcu��Ҫ�õ�
	s32				m_hMcuAppChan;
	s32				m_nMcuReqID;

	BOOL32          m_bSetMediaKeyMT;

	BOOL32			m_bAdjustChanOn; // �Ƿ���Ҫ����AdjustNodeChanOn
	BOOL32			m_bIsKedaManu; // �Ƿ��������ն�
	u16				m_bKedaManuCheckNum; // ������			

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
		
		//������Ƶ��ַ
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
	//�Ա����᳡�Ľ�����(�������ϼ�UMS)
	TCapNode* FirstNode();			//���ر����ĵ�һ�����
	TCapNode* NextLoalNode(TCallNode* ptNode);
	TCapNode* GetLocalNode(u16 wEpID);
	TCapNode* GetLocalNode(TTpCallAddr& tCallAlias);	

	void InitCallNode(TEpAddrList& tList,TTemplateConfEx& tTempEx );
	
	TCapNode* AddNewCall(TTpCallAddr& tDstAlias, BOOL32& bExist);	//���һ���᳡

	TCapNode* FirstNeedCallNode();	
	void SetLastCallNode(TCapNode* ptNode);

	void addepip(u16 wEpid, u32 dwEpIp);
	void delepip(u16 wEpid);
	BOOL32 ismtip(const u32 dwIp);
	void showip();
public:
	//���������������ϼ�UMS��
	TCapNode* GetCapsetNode(u16 wEpID);	//���ر����ĺ��н��(�����ϼ�UMS)	
	void SetNodeCapSet(TCapNode* ptNode, const TUmsNodeCapset& tNodeCap);
	//add
	void SetDualNodeCapset(TCapNode* ptNode, const TUmsNodeCapset& tNodeCap);//����˫����������
	void GetDualNodeCapset(TCapNode* ptNode, TUmsNodeCapset& tNodeCap);
	TVidChanPara* GetChanByHandle(u16 wEpID, EmUmsCodecType enChanType, HandleChannle chanHandle);
	TChanPara* GetChanByIndex(u16 wEpID, EmUmsCodecType enChanType, u16 wIndex);
	TVidChanPara* GetVidChanByIndex(u16 wEpID, EmUmsCodecType enChanType, u16 wIndex);

	TCapNode* GetCaller()		{ return (TCapNode*)m_aptCallNode[CALLER_EP_INDEX]; }

public:
	void AdjustNodeRes( u16 wEpID, u16 wScreenIndx, EmTpVideoResolution emRes, BOOL32 bReset = FALSE);
	void AdjustNodeFrame( u16 wEpID, u16 wScreenIndx, u16 wFrame, BOOL32 bReset = FALSE);

public:
	//�����н�����
	void MakeCallerHandle(TUmsHandle& tHandle, u16 wEpID);
	TCallNode* GetNode(u16 wEpID);
	TCallNode* GetNodeByChildIDList(TCallNode* ptRoot, u16 awLowEpID[], u16 wNum, TCallNode** pParent);
	TCallNode* GetNodeByChildEpID(TCallNode* ptRoot, u16 wLowerEp);
	TCallNode* GetNodeByName(TTPAlias& tAlias, TCallNode* ptRoot);
	//��ȡ�������
	TCallNode* GetCallLev(TCapNode &ptCurNode);
	//��ȡ���м�������ҿ��õ�����
	void GetValidCallType(TTpCallAddr& tCallAddr);
	//��ȡ���н��
	u16 GetAllNode(u16 atNodeID[], u16 wMaxNum);
	//��ȡ����ROOT���ӽڵ��б�
	u16 GetAllNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot);
	//��ȡ������ROOT���ӽڵ��б�
	u16 GetAllChildNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot);
		
	TCapNode* GetForeFatherNode(TCallNode* ptNode);
	TCapNode* GetForeFatherNode(u16 wEpID);

	BOOL32 GetPathKey(TEpPathKey& tKeyID, u16 wEpID);

	//ɾ��һ����㼰���ӽڵ�
	void DeleteNode(TCallNode* ptNode);

	//����һ���¼����б�
	TCallNode* AddChildNode(u16 wParentID, TConfNodeCallUpdateTr& tDstInfo);
	TCallNode* AddChildNodeForMcu(TCapNode* ptMcuNode, TUmsMcuRosterItem& tRosterItem);
	TCallNode* AddChildNodeForMcu(TCapNode* ptMcuNode, TUmcMcuPart& tPart);

	//��ʼ��TEpID�ṹ��
	BOOL32 InitTEpKey( TEpKey& tEpID, BOOL32 bIsUPToDown, u16 wLocalEpID, u16 wLowerEpID=TP_INVALID_INDEX );
	//��TEpID�ṹ����ȡ�ñ��ص�EpID
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

	//����һ�����е��¼����λ��
	u16 FindIdleChildNode();

	u16 GetNodeByRoot(u16 atNodeID[], u16 wMaxNum, TCallNode* ptRoot);
protected:

	//����ID��1���
	TCapNode*		m_ptCurCallNode;						//��ǰ��Ҫ���еĽ��
	TCapNode*		m_ptHeadNode;							//���ڵ�

	TCallNode*		m_aptCallNode[TP_CONF_MAX_CNSNUM];		//���������л᳡�������¼���

	std::map<u16,u32>		m_mapEpIp;
};



#endif // _h_callnodemgr_h__
