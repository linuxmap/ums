#ifndef _h_umsaudmix_h_
#define _h_umsaudmix_h_

#include "callinnerstruct.h"
#include "umseapu.h"
#include "getvidaud.h"

// 混音会场信息
typedef struct tagTUmsAudMixEpInfo
{
	u16     m_wIndex;  // 索引
	u16     m_wEpID;
	BOOL32	m_bThreeAudEp;  // 三屏会场会发送混音

	BOOL32				m_bLocalEp; // 是否是本级会场
	TTPMediaTransAddr   m_atPutAuddr[TP_MAX_STREAMNUM]; // 此会场在下级中会用到；1. 上级将该会场需要的音频地址(n-1)打到这里；2. 下级取这里的音频(n-1)给node    
	CDsListInfo         m_cToPutAuddrDsInfo;  // 上级保存交换用

	TTPMediaTransAddr	m_tAudAddr;
	u32					m_dwMediaNode;
	u16					m_wGetindex;

	tagTUmsAudMixEpInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wIndex = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;

		m_bLocalEp = TRUE;
		m_bThreeAudEp = FALSE;

		ClearGetAudAddr();
		ClearPutAuddr();
		return;
	}
	
	void ClearPutAuddr()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atPutAuddr[wIndex].Clear();
		}
		m_cToPutAuddrDsInfo.Clear();
		m_bLocalEp = TRUE;
	}

	void ClearGetAudAddr()
	{
		m_tAudAddr.Clear();
		m_dwMediaNode = 0;
		m_wGetindex = TP_INVALID_INDEX;
	}

	BOOL32 IsValid()
	{
		return TP_INVALID_INDEX != m_wIndex;
	}

	BOOL32 IsEqualGetVidIndx(u16 wGetVidIndx)
	{
		return wGetVidIndx == m_wGetindex;
	}

	void SetGetAudAddr(TGetVidAddr& tAddr)
	{
		m_tAudAddr = m_bThreeAudEp ? tAddr.m_tMixAddr : tAddr.m_atAudAddr[MIDSCREENINDEX];
		m_dwMediaNode = tAddr.m_dwMedia;
	}
	
}TUmsAudMixEpInfo;

typedef struct tagTUmsAudMixEpInfoList
{
	u16						m_wLimitNum; // 取决于混音器的通道数
	u16						m_wNum;
	TUmsAudMixEpInfo		m_atAudMixEp[TP_APU2_MAX_CHAN_NUM];

	tagTUmsAudMixEpInfoList()
	{
		Clear();
	}

	void Clear()
	{
		m_wLimitNum = 0;
		m_wNum = 0;
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			m_atAudMixEp[wIndex].Clear();
		}
	}

	u16 GetIdleNum() const
	{
		return m_wLimitNum - m_wNum;
	}

	TUmsAudMixEpInfo* GetEp(u16 wEp)
	{
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			if (m_atAudMixEp[wIndex].m_wEpID == wEp)
			{
				return &m_atAudMixEp[wIndex];
			}
		}
		return NULL;
	}

	TUmsAudMixEpInfo* AddEpForLowUms(TCallNode* ptNode)
	{
		if (NULL == ptNode)
		{
			return NULL;
		}

		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			if (!m_atAudMixEp[wIndex].IsValid())
			{
				m_atAudMixEp[wIndex].m_wIndex = wIndex;
				m_atAudMixEp[wIndex].m_wEpID = ptNode->m_wEpID;
				m_atAudMixEp[wIndex].m_bThreeAudEp = ptNode->IsThreeAudSnd()?TRUE:FALSE; // 三屏会场有混音
				m_wNum++;
				return &m_atAudMixEp[wIndex];
			}
		}
		return NULL;
	}

	TUmsAudMixEpInfo* AddEp(TCallNode* ptNode)
	{
		if (NULL == ptNode)
		{
			return NULL;
		}

		if (m_wNum < m_wLimitNum)
		{
			for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
				if (!m_atAudMixEp[wIndex].IsValid())
				{
					m_atAudMixEp[wIndex].m_wIndex = wIndex;
					m_atAudMixEp[wIndex].m_wEpID = ptNode->m_wEpID;
					m_atAudMixEp[wIndex].m_bThreeAudEp = ptNode->IsThreeAudSnd()?TRUE:FALSE; // 三屏会场有混音
					m_wNum++;
					return &m_atAudMixEp[wIndex];
				}
			}
		}

		return NULL;
	}

	void DelEp(u16 wEp)
	{
		for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
		{
			if (m_atAudMixEp[wIndex].m_wEpID == wEp)
			{
				m_atAudMixEp[wIndex].Clear();
				m_wNum--;
				return;
			}
		}
		return;
	}

}TUmsAudMixEpInfoList;

typedef struct tagTUmsAudMixEqp
{
	TAudMixInfo*	    m_ptMixRes;
	CDsListInfo         m_cToMixDsInfo;
	
	tagTUmsAudMixEqp()
	{
		Clear();
	}
	
	void Clear()
	{
		m_ptMixRes = NULL;
		m_cToMixDsInfo.Clear();
	}

	u16	GetTotalChanNum()
	{
		return NULL != m_ptMixRes ? m_ptMixRes->m_tEqpRes.m_wChanNum:0;
	}

	
}TUmsAudMixEqp;


class CUmsConfInst;
class CUmsAudMixMgr
{
public:
	CUmsAudMixMgr(CUmsConfInst* pcInst):m_pcConf(pcInst) {};
	~CUmsAudMixMgr(){}
	void Enter();
	void Exit();

protected:
	CUmsAudMixMgr();
	CUmsAudMixMgr(const CUmsAudMixMgr&);
	CUmsAudMixMgr& operator = (const CUmsAudMixMgr);

	void ResetData();
	CUmsConfInst* Inst(){ return (CUmsConfInst*)m_pcConf; }

	void OnAudMixModeCmdFromCns(CTpMsg *const ptMsg);    
	void OnAudMixModeCmdFromUmc(CTpMsg* const ptMsg);
	void OnAudMixModeCmdFromUmcCnc(TUmsAudMixInfo& tInfo, TUmsAudMixModeCmdRes& tRes);

	void OnAudMixListCmdFromCns(CTpMsg* const ptMsg);
	void OnAudMixListCmdFromUmc(CTpMsg* const ptMsg);
	void OnAudMixListCmdFromUmcCnc(const TUmsAudMixListCmd& tCmd, TUmsAudMixListCmdRes& tRes);

	void OnAudMixListFromUIUpdate(const TUmsAudMixListCmd& tCmd, TUmsAudMixListCmdRes& tRes);

	void OnCasecadeNotify(CTpMsg* const ptMsg);

	BOOL32 AssignMixRes(); 
	void   ResetConfAudMix();

	EmUmsAudMixRes StartAudMixMode(TUmsAudMixInfo& tInfo);
	void StopAudMixMode();
	void AdjustAudMixMode();
	void NotifyAudMixMode();
	void NotifyIsEpInAudMix(u16 wEpId, BOOL32 bIsInAudMix);

    void CreatAudToConfAudMix();
	void AdjustAllNodeToUmsAudMix();

	void AdjustAllEpToMixChan(u16 &wEpAddFailCt);
	void RemoveSomeEpFromMixChan(u16 wNum); // 从混音通道中，随机删除几个会场

	EmUmsAudMixRes AddEpToMixChan(u16 wEp);
	EmUmsAudMixRes DelEpFromMixChan(u16 wEp);

	void GetNewMixMember(TAudMixMemberInfo& tNewMixMember);

public:
	void Show();
	// 处理协议栈消息
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	// 处理umc消息
	BOOL32 HandlerFromUmc(CTpMsg *const ptMsg);

	void OpenEpDownAudCmd(CTpMsg *const ptMsg);
	void OpenEpDownAudAck(CTpMsg *const ptMsg);
	void CloseEpDownAudCmd(CTpMsg *const ptMsg);

	void OnStopConf();

	void OnChanConnect(TCallNode* ptNode);
	void OnHungUpNode(TCallNode* ptNode, EmCnsCallReason emReason = EmCnsCallReason_success);
	
	void ChangeSpeaker(TCallNode* ptSpeakerNode);

	BOOL32 IsAudMixMode(){return !(m_emMixMode == em_umsaudmixmode_idle);}
	TUmsAudMixEpInfo* GetMixEpForID(u16 wEp){ return m_tMixEpInfoList.GetEp(wEp);}

	void GetMixEpAudSndAddr(u16 wEpId, TServiceAddr& tAddr);
	void GetMixAudRcvAddrForMixEp( TUmsAudMixEpInfo* ptEp, TServiceAddr& tAddr);
	void GetMixNModeRcvAddr(TUmsAudFormat& tFormat, TServiceAddr& tAddr, BOOL32 bToSingle); // 因为下级没有混音器，所以下级取的n模式只有级联音频格式一种

	void GetMixAudSrcAddr(TCapNode* ptNode, TTransParam& tAudParam);

#ifdef _USE_XMPUEQP_
	void XmpuMixCB(u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData);
#else
	void MixCB(TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo);
#endif

	// 如果双流混音器通道数小于实际会议混音数，则将实际会议混音数减至较小的那一个
	void CheckDualMixChan();

    void CreatToDulAudMix(u16 wDualEp);

	void PutAudDown();

	void GetConfAudMixStateInfo(TUmsAudMixInfo& tNotify);

protected:
	CUmsConfInst*				m_pcConf;

	TUmsAudMixList				m_tMixListUI; // 定制混音或非混音状态下，界面的混音列表
	TUmsAudMixList				m_tMixLocalList;
	TUmsAudMixEpInfoList		m_tMixEpInfoList;
	TUmsAudMixEqp				m_tMixEqp;
	
	EmUmsAudMixMode				m_emMixMode;
};

#endif // _h_umsaudmix_h_