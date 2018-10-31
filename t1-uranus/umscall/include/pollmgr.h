#ifndef _h_pollmgr_h__
#define _h_pollmgr_h__

#include "umsconfinst.h"
#include "callinnerstruct.h"
#include "callnodemgr.h"
#include "innereventumscall.h"

//////////////////////////////////////////////////////////////////////////
//diaolei
//��ѯ�����ϼ���������������ñ����������¼�����ѯ˳��
//˼·��
//1����ѯ��ҵ�����ϼ�����������״̬����ѯ�б���ͣ��
//2��ÿ���������䡣�ϳ������ϼ�����
//3��ƽ�������ڽ�����ǰ����ǰ��ѯ������һ����ѯ��㲻��һ��UMS��ʱ��������ƽ��������ͬһ��UMSʱ�������UMS��ƽ��

typedef struct tagTPollListEx
{
	u16			m_wInterval;						//��ѯ�������λ��
	u16			m_wNum;								//������ѯ����
	TCallNode*	m_apcNode[TP_CONF_MAX_CNSNUM];

	tagTPollListEx()					{	Clear();  }
	BOOL32 IsValid(u16 wIndex)		{	return wIndex < TP_CONF_MAX_CNSNUM && m_apcNode[wIndex] != NULL; }
	void SetInterval(u16 interval)	
	{
		m_wInterval = interval < TP_CONF_TURN_MIN_INTERVAL ? TP_CONF_TURN_MIN_INTERVAL : interval; 
	}
	void Clear()
	{
		m_wInterval = 20;
		m_wNum = 0;
		for(u16 wIndex = 0; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
		{
			m_apcNode[wIndex] = NULL;
		}

	}
	
	u16 FindIndexByEp(u16 wEpID)
	{
		for(u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
		{
			if (((TCallNode*)m_apcNode[wIndex])->m_wEpID == wEpID)
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}
	void RemoveOneEp(u16 wEpID)
	{
		u16 wIndx = FindIndexByEp(wEpID);
		
		if ( !IsValid(wIndx) )
		{
			return ;
		}
		
		memmove(&m_apcNode[wIndx], &m_apcNode[wIndx+1], sizeof(m_apcNode[0])*(m_wNum - wIndx - 1));
	
		m_apcNode[m_wNum-1] = NULL;
		
		m_wNum--;
		
	}

	void AddOneEp(TCallNode* pcNode, u16 wIndex)
	{
		if ( wIndex >= TP_CONF_MAX_CNSNUM || m_wNum >=  TP_CONF_MAX_CNSNUM )
		{
			return ;
		}
		
		memmove(&m_apcNode[wIndex+2], &m_apcNode[wIndex+1], sizeof(m_apcNode[0])*(m_wNum - wIndex - 1));
		
		m_apcNode[wIndex+1] = pcNode;
		
		m_wNum++;
		
	}
}TPollListEx;

typedef struct tagTPollAddrEx
{
	u16					m_wPollEpID;						//��¼���ڱ���ѯ���ID
	u16					m_wPollIndx;						//��¼���ڱ���ѯ������
	TTPMediaTransAddr*	m_aptLocalAddr[TP_MAX_STREAMNUM];	//��������ƽ����ַ
	TTPTransAddr		m_atRmtRtcp[TP_MAX_STREAMNUM];		//�ϼ��洢�¼�Rtcp

	TTPMediaTransAddr*	m_aptSmallAddr[TP_MAX_STREAMNUM];	//��������С����ƽ����ַ
	TTPTransAddr		m_atSmallRmtRtcp[TP_MAX_STREAMNUM];	//�ϼ��洢С�����¼�Rtcp

	tagTPollAddrEx()
	{
		Clear();
	}

	void Clear()
	{
		m_wPollEpID = TP_INVALID_INDEX;
		m_wPollIndx = TP_INVALID_INDEX;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_aptLocalAddr[wIndex] = NULL;
			m_atRmtRtcp[wIndex].Clear();

			m_aptSmallAddr[wIndex] = NULL;
			m_atSmallRmtRtcp[wIndex].Clear();
		}
	}

	BOOL32 IsValid()
	{
		return TP_VALID_HANDLE(m_wPollEpID);
	}
}TPollAddrEx;

typedef struct tagTTpPollList
{
	BOOL32	m_wUpdate;					//���ڸ��� �������µĸ���
	u32		m_dwFlag;					//���±�ʶ
	u16		m_wInterval;				//��ѯ�������λ��
	u16		m_wTotalNum;				//������
	u16		m_wCurNum;					//��ǰ����
	u16		m_awList[TP_CONF_MAX_CNSNUM];
	tagTTpPollList()
	{
		Clear();
	}
	void Clear()
	{
		m_wUpdate = FALSE;
		m_dwFlag = 0;
		m_wInterval = 5;
		m_wTotalNum = 0;
		m_wCurNum = 0;
		memset(m_awList, 0, sizeof(m_awList));
	}
}TTpPollList;

typedef struct tagTTpDownUms
{
	u16		m_wEpID;
	u16		m_wScreenNum;
	tagTTpDownUms()
	{
		Clear();
	}
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenNum = TP_MAX_STREAMNUM;
	}
}TTpDownUms;

#define DOWN_UMS_MGR 4
typedef struct tagTTpDownUmsMgr
{
	TTpDownUms	m_atDowNum[DOWN_UMS_MGR];
	tagTTpDownUmsMgr()
	{
		Clear();
	}
	void Clear()
	{
		for ( u16 wIndex = 0; wIndex < DOWN_UMS_MGR; wIndex ++)
		{
			m_atDowNum[wIndex].Clear();
		}
	}
	void SetValue(u16 wUmsEpID, u16 wScreenNum)
	{
		TTpDownUms* ptDowUms = NULL;
		for ( u16 wIndex = 0; wIndex < DOWN_UMS_MGR; wIndex ++)
		{
			if ( !TP_VALID_HANDLE(m_atDowNum[wIndex].m_wEpID) )
			{
				ptDowUms = &m_atDowNum[wIndex];
				continue;
			}

			if ( m_atDowNum[wIndex].m_wEpID == wUmsEpID  )
			{
				if ( m_atDowNum[wIndex].m_wScreenNum > wScreenNum )
				{
					m_atDowNum[wIndex].m_wScreenNum = wScreenNum;
				} 
				return;
			}
		}

		if ( NULL != ptDowUms )
		{
			ptDowUms->m_wEpID = wUmsEpID;
			ptDowUms->m_wScreenNum = wScreenNum;
		}
	}

	BOOL32 Check(u16 wUmsEpID, u16 wScreenNum)
	{
		for ( u16 wIndex = 0; wIndex < DOWN_UMS_MGR; wIndex ++)
		{
			if ( !TP_VALID_HANDLE(m_atDowNum[wIndex].m_wEpID) )
			{
				continue;
			}
			
			if ( m_atDowNum[wIndex].m_wEpID == wUmsEpID  )
			{
				if ( m_atDowNum[wIndex].m_wScreenNum <= wScreenNum )
				{
					return FALSE;
				}
			}
		}
		return TRUE;
	}
}TTpDownUmsMgr;


class CUmsConfInst;
class CPollMgr  : public CTpHandler
{
public:
	CPollMgr(CUmsConfInst* pcInst);
	~CPollMgr();
	
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	void Show();

	TPollAddrEx* GetCurAddr() { return m_ptCurAddr; }
	TPollAddrEx* GetOldAddr() { return m_ptOldAddr; }
	TTPTransAddr& GetUpRtp(u16 wScrIndx)  { return m_atRmtRtp[wScrIndx]; }
	TTPTransAddr& GetSmallUpRtp(u16 wScrIndx)  { return m_atSmallRmtRtp[wScrIndx]; }
	CDsListInfo& GetPollDs()	{ return m_tToPollDs; }
	TPollIframeCheck& GetIframeCheck() { return m_tIframeCheck; }
	const CBaseService* GetVmp() { return m_pcPollVmp; }

	BOOL32	IsPollStart() { return m_emStat == EmPollStat_Start; }
	BOOL32	IsPollUiOn()  { return m_emUiStat == EmPollStat_Start || m_emUiStat == EmPollStat_Suspend; }
	BOOL32	IsDefaultPoll() { return m_bIsDefaultPoll; }

	void TrySuspendPoll()
	{
		if( m_emUiStat != EmPollStat_Start || !Inst()->IsChairConf() ) return;
		if( Inst()->curSpeakerID() == m_wVirEpID ) return;//����ѯ�Լ����� �� ����ͣ
		KillTimer(evtp_ExeTurnList_time); m_emStat = EmPollStat_Suspend;
		m_emUiStat = m_emStat;
		NotifyPollStatToUI();
	}

#ifdef _USE_XMPUEQP_
	void XmpuBasCB( u32 dwType, CScreenBasRes* ptBasRes, void *pData );
#else
	void BasCB( CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes );
#endif
	void VmpCB( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes );

	void ResetMediaIp();

	//������ѯ���
	void SetPollTimeInterval(u16 wInterval) { m_tCfg.m_wInterval = wInterval; }

	void InitPollList(const TConfTurnList* ptList);
	void InitPollList();

	BOOL32 IsAddEpInPollList(TCallNode* ptNodeAdd);
    void AddLowInviteEp(TCallNode* ptNodeAdd);


	void StopConf();
	void AddNode(TCapNode* ptNode);
	void OnChanConnect(TCallNode* ptNode);
	void OnHungup(TCallNode* ptNode);
	void AdjustCnsSpeaker(TCallNode* ptNode);

	//����
	void OnCncStartPollReq(CTpMsg *const ptMsg);
	void OnUmcStartPollReq(CTpMsg *const ptMsg);

	//��ͣ ���ֵ�ǰ��ѯ״̬
	void OnCncSuspendPollReq(CTpMsg *const ptMsg); 
	void OnUmcSuspendPollReq(CTpMsg *const ptMsg);

	//ֹͣ
	void OnCncStopPollReq(CTpMsg *const ptMsg); 
	void OnUmcStopPollReq(CTpMsg *const ptMsg);

	//����
	void OnUpdatePollListFromUmc(CTpMsg *const ptMsg);
	void OnUpdatePollListFromCnc(CTpMsg *const ptMsg);

	//�յ��ϼ���ѯĳ����������ж��Ͻ���Ƿ񱾵أ��������������ƽ����������ֱ�ӽ����ϼ�����
	void OnCasecadePollEpReq(CTpMsg *const ptMsg);
	//�յ��¼��Ļ�Ӧ���д��󣬱��磺����ƵԴ���ѵ��ߡ��޴���������ȣ��������ѯ��һ��
	void OnCasecadePollEpRsp(CTpMsg *const ptMsg);

	void OnIframeBySrcNty(CTpMsg *const ptMsg);

	//��ѯ��ʱ ֻ���ϼ���
	void OnPollTimer(CTpMsg *const ptMsg);

	EmTPPollResult StartPoll();
	EmTPPollResult SuspendPoll(BOOL32 bSuspend, BOOL32 bTimer = FALSE);
	EmTPPollResult StopPoll();

	BOOL32 UpdatePollList(TTpPollListNtfy& tList, TTpPollListInd& tInd);

	void NotifyPollListToUI(BOOL32 bCNC = TRUE, BOOL32 bUmc = TRUE, TLogUser* ptUser = NULL);
	void NotifyPollStatToUI(TLogUser* ptUser = NULL);

	void AskKeyFrame(u16 wScreenIndx, BOOL32 bBySys);

	BOOL32 GetLocalPollInAddr(TTPMediaTransAddr& tAddr, u32& dwEqpNode, u16 wScreenIndx, u16 wPollEpSpeakerIndex);
	BOOL32 GetLocalPollOutAddr(TTPMediaTransAddr& tAddr, u32& dwEqpNode, u16 wScreenIndx);
private:

	BOOL32 UpdatePollTempList(TTpPollListNtfy& tList);

	EmTPPollResult PollNextEp(u16 wPollIndx = TP_INVALID_INDEX);
	void CreatePollEpMedia(u16 wCurPollEp, u16 wPollIndx, BOOL32 bDownUmsRsp = FALSE);
	BOOL32	HavePollEp();

	u16 GetNextPollEp(u16 wCurIndx);

	void SetIFrameCheck();
	void DestroyIframeCheck();

	void PollClear();

	void NextAddr();

public:
//////////////////////////////////////////////////////////////////////////
//������̬
	void InitVirNode();
	void ReleaseVirNode();
	void AdjustDsToVirNode();

private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	friend class CNetPortMgr;
	
protected:
	EmPollStat		m_emUiStat;			//������ѯ״̬
	EmPollStat		m_emStat;			//��ѯ״̬

	BOOL32			m_bIsDefaultPoll;	//�Ƿ���Ĭ���б�

	TPollAddrEx*	m_ptCurAddr;
	TPollAddrEx*	m_ptOldAddr;
	TPollAddrEx		m_tAddrOne;
	TPollAddrEx		m_tAddrTwo;

	TTpDownUmsMgr	m_tFailEpID;							//��������ʱ���¼�ʧ�ܵ�UMS�ڵ�

	TTPMediaTransAddr*	m_aptLocalChair[TP_MAX_STREAMNUM];	//����ƽ�����ַ���޺ϳɣ�������ʱ����Ҫռ��

	TTPTransAddr	m_atRmtRtp[TP_MAX_STREAMNUM];//�����ϼ�rtp��ַ
	TTPTransAddr	m_atSmallRmtRtp[TP_MAX_STREAMNUM];//�����ϼ�Small rtp��ַ

	BOOL32				m_bBas;
	TCallVidFormat		m_tChairFmt;					//��ϯ�Ľ��ո�ʽ
	
	CScreenBasRes*		m_apcBasRes[TP_MAX_STREAMNUM];  //���� һ����Ҫ ��̶�ռ�ã�����ֹͣ

	u32					m_dwBw;							//��ǰռ�õĴ���

	const CBaseService* m_pcPollVmp;					//��ϯ����ʱ���� ֻ���ϼ��ϳ�
	BOOL32				m_bVmpStart;					//�ϳ��Ƿ���
	
	TPollIframeCheck	m_tIframeCheck;					//�ؼ�֡�����Ϣ
	
	TPollListEx			m_tCfg;

	TTpPollList			m_tUiListTemp;					//����ʱ������

	CDsListInfo			m_tToPollDs;

	BOOL32				m_bPrint;						//��ʱ��ѯ��ӡ����

	u16					m_wVirEpID;
	CDsListInfo			m_tVirDs;
};


#endif // _h_pollmgr_h__