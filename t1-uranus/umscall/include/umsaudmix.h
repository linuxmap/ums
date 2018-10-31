#ifndef _h_umsaudmix_h_
#define _h_umsaudmix_h_

#include "callinnerstruct.h"
#include "umseapu.h"
#include "getvidaud.h"

// �����᳡��Ϣ
typedef struct tagTUmsAudMixEpInfo
{
	u16     m_wIndex;  // ����
	u16     m_wEpID;
	BOOL32	m_bThreeAudEp;  // �����᳡�ᷢ�ͻ���

	BOOL32				m_bLocalEp; // �Ƿ��Ǳ����᳡
	TTPMediaTransAddr   m_atPutAuddr[TP_MAX_STREAMNUM]; // �˻᳡���¼��л��õ���1. �ϼ����û᳡��Ҫ����Ƶ��ַ(n-1)�����2. �¼�ȡ�������Ƶ(n-1)��node    
	CDsListInfo         m_cToPutAuddrDsInfo;  // �ϼ����潻����

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
	u16						m_wLimitNum; // ȡ���ڻ�������ͨ����
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
				m_atAudMixEp[wIndex].m_bThreeAudEp = ptNode->IsThreeAudSnd()?TRUE:FALSE; // �����᳡�л���
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
					m_atAudMixEp[wIndex].m_bThreeAudEp = ptNode->IsThreeAudSnd()?TRUE:FALSE; // �����᳡�л���
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
	void RemoveSomeEpFromMixChan(u16 wNum); // �ӻ���ͨ���У����ɾ�������᳡

	EmUmsAudMixRes AddEpToMixChan(u16 wEp);
	EmUmsAudMixRes DelEpFromMixChan(u16 wEp);

	void GetNewMixMember(TAudMixMemberInfo& tNewMixMember);

public:
	void Show();
	// ����Э��ջ��Ϣ
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	// ����umc��Ϣ
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
	void GetMixNModeRcvAddr(TUmsAudFormat& tFormat, TServiceAddr& tAddr, BOOL32 bToSingle); // ��Ϊ�¼�û�л������������¼�ȡ��nģʽֻ�м�����Ƶ��ʽһ��

	void GetMixAudSrcAddr(TCapNode* ptNode, TTransParam& tAudParam);

#ifdef _USE_XMPUEQP_
	void XmpuMixCB(u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData);
#else
	void MixCB(TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo);
#endif

	// ���˫��������ͨ����С��ʵ�ʻ������������ʵ�ʻ��������������С����һ��
	void CheckDualMixChan();

    void CreatToDulAudMix(u16 wDualEp);

	void PutAudDown();

	void GetConfAudMixStateInfo(TUmsAudMixInfo& tNotify);

protected:
	CUmsConfInst*				m_pcConf;

	TUmsAudMixList				m_tMixListUI; // ���ƻ�����ǻ���״̬�£�����Ļ����б�
	TUmsAudMixList				m_tMixLocalList;
	TUmsAudMixEpInfoList		m_tMixEpInfoList;
	TUmsAudMixEqp				m_tMixEqp;
	
	EmUmsAudMixMode				m_emMixMode;
};

#endif // _h_umsaudmix_h_