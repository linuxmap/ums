#ifndef _h_umsvmp_h__
#define _h_umsvmp_h__
#include "umsconfinst.h"
#include "tphandle.h"
#include "eqpinterface.h"
#include "callinnerstruct.h"
#include "umseqpservice.h"
#include "putaud.h"
#include "getvidaud.h"
#include "umsxmpinterface.h"

//////////////////////////////////////////////////////////////////////////
//�ϳɲ��ԣ�
//�����ˡ���ϯ���⳧�̡���� ����ռ��vip
//1�������ϳɺ��и��棬���������᳡����Ҫʱ��ռvip�������᳡���ν��ϳɣ���Ҫvip�������vip���ȼ���ռvip��
//vip���㣬�򽵷ֱ��ʣ���ʧ���򲻴�������������ϳ���ʾĬ�ϻ��棩������ʾ
//2�����ߺ����ռ����vip�������vip���ȼ���ˢ�£����·���vip��
//3�����ߺ������Ҫռ��vip��������Ƿ���vip��û���򲻴���������
//4���з����ˣ������Ҫռ��vip����ֱ����ռ������Ӱ����ʾ��

//���һ���᳡ռ������ͨ����Ҳ��������ͬʱ�����������ϳ����У���ô��Ҫ�ۺϼ��㡣����Ϊ��
//1�����ȱ�֤�����ˡ���Ҫʱ��ռ��
//2�����һ���ϳ���vip���㣬������һ��������������һ��������������

#define VMP_MAX_SAVE_CFG_NUM 6

enum EmBrdVmpCBOprType
{
	EmBrdVmpCBOprType_DisConnect,
	EmBrdVmpCBOprType_Stop,
	EmBrdVmpCBOprType_OtherFail
};


typedef struct tagTTPDsFrom
{
	TTPTransAddr m_tRtpAddr;
	TTPTransAddr m_tBackRtcpAddr;
	u32			 m_dwEqpNode;
	tagTTPDsFrom()
	{
		m_tRtpAddr.Clear();
		m_tBackRtcpAddr.Clear();
		m_dwEqpNode = 0;
	}
}TTPDsFrom;

typedef struct tagTBrdVmpMember
{
	u8			m_byVip;      // �Ƿ���vip
	u8			m_byDs;       // �Ƿ񴴽�����
	u8          m_bySmallVid; // �Ƿ���С�������ϳ�
	u8          m_byAdjustRes; // �Ƿ�����ֱ���

	TTPVMPMember	m_tVmpMember;
	EmTpVideoResolution m_emRes;

	TGetVidAddr		m_tGetAddr;   //ѡ���ϵ�����
	u16             m_wGetIndex;  //�ϵ�������index���ͷŵ�ʱ����õ�

	u16				m_wIndx;//��ʼ�� �������
	tagTBrdVmpMember()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byVip = 0;
		m_byDs = 0;
		m_bySmallVid = 0;
		m_emRes = emTPVResEnd;
		m_tVmpMember.Clear();
		memset(&m_tGetAddr, 0, sizeof(m_tGetAddr));
		m_wGetIndex = TP_UMS_MAX_CALLNUM;
	}

	void ClearGetVid()
	{
		memset(&m_tGetAddr, 0, sizeof(m_tGetAddr));
		m_wGetIndex = TP_UMS_MAX_CALLNUM;
	}
	BOOL32 IsVidGet() { return TP_UMS_MAX_CALLNUM > m_wGetIndex; }
	
	BOOL32 IsVip(){ return 1 == m_byVip; }
	void   SetVip(){ m_byVip = 1;}
	void   ClearVip(){m_byVip = 0;}

	BOOL32 IsDs(){ return 1 == m_byDs; }
	void   SetDs(){ m_byDs = 1;}
	void   ClearDs(){m_byDs = 0;}

	BOOL32 IsSmallVid(){ return 1 == m_bySmallVid; }
	void   SetSmallVid(){ m_bySmallVid = 1;}
	void   ClearSmallVid(){m_bySmallVid = 0;}

	BOOL32 IsAdjustRes(){ return 1 == m_byAdjustRes; }
	void   SetAdjustRes(){ m_byAdjustRes = 1;}
	void   ClearAdjustRes(){m_byAdjustRes = 0;}

}TBrdVmpMember;

typedef struct tagTVmpMemberPool
{
	u16             m_awLevel[TP_VMP_MAX_IN_CHN_NUM]; 
	TBrdVmpMember*  m_aptVmpMember[TP_VMP_MAX_IN_CHN_NUM];

	tagTVmpMemberPool()
	{
		Clear();
	}

	void Clear()
	{
		for (u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex++)
		{
			m_awLevel[wIndex] = TP_INVALID_INDEX;
			m_aptVmpMember[wIndex] = NULL;
		}
	}

	void Show()
	{
		msgprintnotime("VipPool Info:\n");
		for (u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex++)
		{
			if (NULL == m_aptVmpMember[wIndex])
			{
				continue;
			}
			msgprintnotime("  [%d] wIndex:%d, EpId:%d, ScrIndex:%d, Stat:%d, wLevel:%d.\n", wIndex, m_aptVmpMember[wIndex]->m_wIndx,
				m_aptVmpMember[wIndex]->m_tVmpMember.m_wEpID, m_aptVmpMember[wIndex]->m_tVmpMember.m_wScreenIndx,
				m_aptVmpMember[wIndex]->m_tVmpMember.m_byStat, m_awLevel[wIndex]);
		}
	}

	void AddMember(TBrdVmpMember* ptMember, u16 wLevel)
	{
		if (NULL == ptMember)
		{
			return;
		}
		u16 wIndex = TP_INVALID_INDEX;
		u16 wNullIndex = TP_INVALID_INDEX;

		for (wIndex = TP_VMP_MAX_IN_CHN_NUM; wIndex > 0; wIndex--)
		{// �Ӻ�ʼѭ������֤wNullIndex���ǰ��NULL Index
			if (NULL == m_aptVmpMember[wIndex - 1])
			{
				wNullIndex = wIndex - 1;
				continue;
			}
			else
			{
				if (ptMember->m_wIndx == m_aptVmpMember[wIndex - 1]->m_wIndx)
				{// �Ѿ����ڣ����ظ����
					return;
				}
			}
		}
		if (wNullIndex < TP_VMP_MAX_IN_CHN_NUM)
		{
			m_aptVmpMember[wNullIndex] = ptMember;
			m_awLevel[wNullIndex] = wLevel;
		}
		return;
	}

	void DelMember(u16 wIndex)
	{
		if (NULL != m_aptVmpMember[wIndex])
		{
			m_aptVmpMember[wIndex] = NULL;
			m_awLevel[wIndex] = TP_INVALID_INDEX;
		}
	}

	TBrdVmpMember* GetMember(u16& wIndex, u16 wInLevel)
	{// get��������ɹ���ռ����ҪDelMember

		TBrdVmpMember* ptMember = NULL;
		u16 wLevel = TP_INVALID_INDEX;
		for (u16 wLoop = 0; wLoop < TP_VMP_MAX_IN_CHN_NUM; wLoop++)
		{// ����һ�飬ȡlevel��ͣ���С��wInLevel����Чmember

			if ((NULL != m_aptVmpMember[wLoop]) && (wInLevel > m_awLevel[wLoop]) && (wLevel > m_awLevel[wLoop]))
			{
				ptMember = m_aptVmpMember[wLoop];
				wLevel = m_awLevel[wLoop];
				wIndex = wLoop;
			}
		}

		return ptMember;
	}

}TVmpMemberPool;

typedef void (*BrdVmpCB)(void* param1, void* param2, void *param3);

typedef struct tagTBrdVmpRes : public TBrdVmpResNtfy
{
	TVmpEqpRes		m_tEqpRes;
	u16				m_wMemberNum;
	TBrdVmpMember	m_atMember[TP_VMP_MAX_IN_CHN_NUM];	//�ϳɳ�Ա
	BOOL32			m_bNeedAdjVip;

	u16				m_wVipNum;//Vip���� Ҫ���ݻ᳡��ʽ�͵�ǰ���̬����
	u16				m_wCurVipNum;



	//xmpu vmp ר��
	BOOL32			m_bOnLine;
//	BOOL32			m_bNeedAdjMember;
	TTPTransAddr	m_atDecMiddleRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp����ͨ��rtp rcv
	TTPTransAddr	m_atDecRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp����ͨ��rtp rcv
	TTPTransAddr	m_atDecRtcpAddr[TP_VMP_MAX_IN_CHN_NUM];  // vmp����ͨ�� back rtcp rcv
	TTPTransAddr	m_atEncRtpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp����ͨ��rtcp rcv
	TTPTransAddr	m_atEncRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp����ͨ��rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp����ͨ��rtcp rcv
	CDsListInfo         m_cToVmpDsInfo;

	BrdVmpCB		m_pfSelViewCB;
	void*			m_pSelViewParam;

	BrdVmpCB		m_pfTvWallCB;
	void*			m_pTvWallParam;

	BrdVmpCB		m_pfGetVmpCB;       // �������úϳ�������
	void*			m_pGetVmpParam;

	u8				m_byVipMaxStyle; // ���(4)����£�ȫǰ����ͨ��
	u8				m_byVipNum;		// ������(4)��񣬴��ڵ�ǰ����ͨ������
	CDsListInfo		m_tDsToVmp;
	tagTBrdVmpRes()
	{
		Clear();
	}

	void Clear()
	{
		m_tEqpRes.Clear();
		m_wMemberNum = 0;
		
		for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++ )
		{
			m_atMember[wIndex].Clear();
			m_atMember[wIndex].m_wIndx = wIndex;
		}

		m_bNeedAdjVip = FALSE;
		m_wCurVipNum = 0;
		m_byVipMaxStyle = 0;
		m_byVipNum = 0;
		m_tDsToVmp.Clear();
		m_bOnLine = FALSE;
		TBrdVmpResNtfy::Clear();
		memset(m_atDecMiddleRtpAddr, 0, sizeof(m_atDecMiddleRtpAddr));
		memset(m_atDecRtpAddr, 0, sizeof(m_atDecRtpAddr));
		memset(m_atDecRtcpAddr, 0, sizeof(m_atDecRtcpAddr));
		memset(m_atEncRtpAddr, 0, sizeof(m_atEncRtpAddr));
		memset(m_atEncRtcpAddr, 0, sizeof(m_atEncRtcpAddr));
		memset(m_atEncMiddleRtcpAddr, 0, sizeof(m_atEncMiddleRtcpAddr));
		m_cToVmpDsInfo.Clear();
		m_pfSelViewCB = NULL;
		m_pfTvWallCB  = NULL;
		m_pfGetVmpCB  = NULL;
	}

	void ResetUIInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tVmpStyle.Clear();
	}

	void ReSetMember()
	{
		m_wMemberNum = 0;
		
		for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++ )
		{
			m_atMember[wIndex].Clear();
		}
		
		m_bNeedAdjVip = FALSE;
		m_wCurVipNum = 0;
		m_wVipNum = 0;
	}

	void GetUIInfo(TBrdVmpResNtfy& tNtfy)
	{
		tNtfy.m_wConfID = m_wConfID;
		tNtfy.m_emStat = m_emStat;
		memcpy(&tNtfy.m_tEqpInfo, &m_tEqpInfo, sizeof(m_tEqpInfo));
		memcpy(&tNtfy.m_tVmpStyle, &m_tVmpStyle, sizeof(m_tVmpStyle));
	}

	void SetUIInfo(TSetVmpInfoReq tBrdReq)
	{ 
		memcpy(&m_tVmpStyle, &tBrdReq.m_tStyle, sizeof(m_tVmpStyle));
		m_bVmpAuto = tBrdReq.m_tStyle.m_emVmpStyle == tp_VmpStyle_DYNAMIC ? TRUE : FALSE;
	}

	BOOL32 IsEpInVmp(u16 wEpID)
	{
		for(u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++)
		{
			if( m_tVmpStyle.m_atVmpChnl[wIndex].m_wEpID == wEpID )
			{
				return TRUE;
			}
		}
		
		return FALSE;
	}
}TBrdVmpRes;

typedef struct tagTSaveCfgMgr
{
	u16				m_wIndex;
	BOOL32			m_bUsed;
	EmUIType		m_emUi;
	TLogUser		m_tUser;

	s32				m_sTime;
	TSaveVmpCfg		m_tVmpCfg;
	tagTSaveCfgMgr()
	{
		m_wIndex = 0;
		Clear();
	}
	
	void Clear()
	{
		m_bUsed = FALSE;
		m_emUi = EmUI_UMC;
		m_sTime = 0;
		m_tVmpCfg.Clear();
	}

	BOOL32 IsUsed() { return m_bUsed; }
}TSaveCfgMgr;

typedef struct tagTSaveCfgMgrArray
{
	TSaveCfgMgr m_atCfgMgr[VMP_MAX_SAVE_CFG_NUM];
	tagTSaveCfgMgrArray()
	{
		Clear();
	}
	
	void Clear()
	{
		for ( u16 wIndex = 0; wIndex < VMP_MAX_SAVE_CFG_NUM; wIndex ++ )
		{
			m_atCfgMgr[wIndex].Clear();
			m_atCfgMgr[wIndex].m_wIndex = wIndex;
		}
	}
	
	TSaveCfgMgr* FindCfgMgr(u16 wFlag)
	{
		if (wFlag >= 0 && wFlag < VMP_MAX_SAVE_CFG_NUM)
		{
            return &m_atCfgMgr[wFlag];
		}

		u16 wIndex = 0;
		for ( wIndex = 0; wIndex < VMP_MAX_SAVE_CFG_NUM; wIndex ++ )
		{
			if ( m_atCfgMgr[wIndex].IsUsed() )
			{
				continue;
			}
			time_t CurTime;
			time(&CurTime);
			m_atCfgMgr[wIndex].m_sTime = CurTime;
			return &m_atCfgMgr[wIndex];
		}

		TSaveCfgMgr* ptMgr = NULL;
		//�Ҳ������������һ�����ϵ�����
		for ( wIndex = 0; wIndex < VMP_MAX_SAVE_CFG_NUM; wIndex ++ )
		{
			if ( NULL == ptMgr )
			{
				ptMgr = &m_atCfgMgr[wIndex];
			}

			if ( ptMgr->m_sTime < m_atCfgMgr[wIndex].m_sTime )
			{
				ptMgr = &m_atCfgMgr[wIndex];
			}
		}
		ptMgr->Clear();
		return ptMgr;
	}
}TSaveCfgMgrArray;

typedef struct tagTBrdVmpStyleOpr
{
	u16			m_wChnlNum;
	u16         m_awLevel[TP_VMP_MAX_IN_CHN_NUM];
	TBrdVmpChnl m_atVmpChnl[TP_VMP_MAX_IN_CHN_NUM];
	
	tagTBrdVmpStyleOpr()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wChnlNum = 0;
		for (u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex++)
		{
			m_awLevel[wIndex] = TP_INVALID_INDEX;
			m_atVmpChnl[wIndex].Clear();
		}
		return;
	}
	
	void AddVmpChnl(u16 wEpId, u16 wScreenIndex, u16 wLevel)
	{// ��level�ɸߵ�������
		u16 wIndex = 0;
		u16 wIndexTemp = 0;
		for (wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex++)
		{
			if (m_atVmpChnl[wIndex].IsValid())
			{
				if (m_awLevel[wIndex] < wLevel)
				{
					for (wIndexTemp = TP_VMP_MAX_IN_CHN_NUM-1; wIndexTemp > wIndex; wIndexTemp--)
					{// ��λ���Ժ�ģ�����һλ
						m_atVmpChnl[wIndexTemp].m_wEpID = m_atVmpChnl[wIndexTemp - 1].m_wEpID;
						m_atVmpChnl[wIndexTemp].m_wScrIndx = m_atVmpChnl[wIndexTemp - 1].m_wScrIndx;
						m_awLevel[wIndexTemp] = m_awLevel[wIndexTemp - 1];
					}
					//ȡ��λ��
					m_atVmpChnl[wIndex].m_wEpID = wEpId;
					m_atVmpChnl[wIndex].m_wScrIndx = wScreenIndex;
					m_awLevel[wIndex] = wLevel;
					if (m_wChnlNum < TP_VMP_MAX_IN_CHN_NUM)
					{
						m_wChnlNum++;
					}
					return;
				}
			}
			else
			{
				break;
			}
		}
		
		if (wIndex < TP_VMP_MAX_IN_CHN_NUM)
		{
			m_atVmpChnl[wIndex].m_wEpID = wEpId;
			m_atVmpChnl[wIndex].m_wScrIndx = wScreenIndex;
			m_awLevel[wIndex] = wLevel;
			m_wChnlNum++;
		}
		return;
	}

	void DelVmpChnl()
	{// ɾ��level��͵�һ����Ա
		if (0 < m_wChnlNum)
		{
			m_awLevel[m_wChnlNum - 1] = TP_INVALID_INDEX;
			m_atVmpChnl[m_wChnlNum - 1].Clear();
			m_wChnlNum--;
		}
		return;
	}
	
}TBrdVmpStyleOpr;

class CUmsConfInst;
class CUmsVmp  : public CTpHandler, public CNodeBase
{
public:
	enum EmVmpStat
	{
		VmpStat_Idle,//������
		VmpStat_Running,//��ȷ����
		VmpStat_Full,//�޿��кϳ���
		VmpStat_Error,//�����û�����Զ�����úϳ���
	};
public:
	CUmsVmp(CUmsConfInst* pcInst);
	~CUmsVmp();

	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );

	void Show();

	BOOL32	AskFrameToSpeakerVmp( u16 wSrcEpID );
	BOOL32  AskFrameToSpeakerVmp(const TUmsVidFormat& tFormat);

	BOOL32	AskFrameToBrdVmp( TBrdVmpRes* ptVmpRes, u16 wSrcEpID, BOOL32 bIsFromVirSpeaker = FALSE);
	BOOL32  AskFrameToBrdVmp( TBrdVmpRes* ptVmpRes, const TUmsVidFormat& tFormat, BOOL32 bIsFromVirSpeaker = FALSE);

	void GetBrdVmpOutAddr( TBrdVmpRes* ptVmpRes, TTPDsFrom& tAddr, TUmsVidFormat& tVidFmt, BOOL32 bIsToVirSpeaker = FALSE);
	void GetBrdVmpInAddr( TBrdVmpRes* ptVmpRes, TTPMediaTransAddr& tAddr, u16 wChnIndx);

	void	GetSpeakerVmpInAddr(TTPDsFrom& tAddr, u16 wChnlIndx);
	void	GetSpeakerVmpOutAddr(TTPDsFrom& tAddr);

	BOOL32 IsChairOrSpeakerInVmp()
	{
		if(Inst()->IsChairConf())
		{
			if (!m_pcSpeakerVmp || !m_bSpeakerVmpCfg)
			{
				return FALSE;
			}
			
			GetVmpEp();
			
			return (em_Vmp_Invalid != m_emVmpType);
		}
		else
		{
			return (em_Vmp_Invalid != m_emVmpType);
		}
	}

	BOOL32	IsSpeakerInVmp()
	{// �������Ƿ���ϳ�
		if(Inst()->IsChairConf())
		{
			if (!m_pcSpeakerVmp || !m_bSpeakerVmpCfg)
			{
				return FALSE;
			}

			GetVmpEp();

			return (em_Speaker_In_Vmp == m_emVmpType);
		}
		else
		{
			return (em_Speaker_In_Vmp == m_emVmpType);
		}
	}
	BOOL32	IsChairInVmp()
	{//��ϯ�Ƿ���ϳɣ��Ƿ����˲���
		if(Inst()->IsChairConf())
		{
			if (!m_pcSpeakerVmp || !m_bSpeakerVmpCfg)
			{
				return FALSE;
			}
			
			GetVmpEp();

			return (em_Chair_In_Vmp == m_emVmpType);
		}
		else
		{
			return (em_Chair_In_Vmp == m_emVmpType);
		}
	}

	BOOL32 IsSpeakVmpOn()
	{// �����˺ϳ��Ƿ�����
		return NULL != m_pcSpeakerVmp;
	}

	CDsListInfo& GetToVmpDs()	{ return Inst()->GetSpeaker().m_tToVmpDs; }
	
	TBrdVmpRes* GetConfBrdVmp() { return m_ptConfBrdVmp; }

	s8*			GetBrdVmpAlias() { return m_szBrdVmpAlias; }

//////////////////////////////////////////////////////////////////////////
//�����˺ϳ�
	void StartSpeakerVmp();
	void AdjustSpeakerVmp(BOOL32 bFromDiscuss = FALSE, BOOL32 bChangeSpeaker = TRUE);

	TCallNode* GetVmpEp();
	u16 VmpEp() { return m_wVmpEpID; }

	BOOL32 IsBrdVmp() { return m_bBrdVmp; }

public:

	void InitBrdVmpCfg(TSaveVmpCfg* ptCfg);
	void OnChanConnect(TCallNode* ptNode);
	void OnHungUp(TCallNode* ptNode, EmCnsCallReason emReason = EmCnsCallReason_success);
	void OnStopConf();
	void ChangSpeaker();
	void AdjustDual();

	void AdjustCnsSpeaker(TCallNode* ptNode);

	//���ϳ�״̬���µ����� UMCΪ�����û���CNCΪ���л�������л᳡
	static void NotifyBrdVmpToAllConf(u8 byEqpID, EmTpOprType emOpr);
	static void NotifyBrdVmpToAllConf(TBrdVmpRes* ptVmpRes, EmTpOprType emOpr);
	static void NotifyBrdVmpToUMC(TBrdVmpRes* ptVmpRes, EmTpOprType emOpr);
	void NotifyBrdVmpToCNC(TBrdVmpRes* ptVmpRes, EmTpOprType emOpr);


	void NotifyAllBrdVmpToUMC(TLogUser* ptUser = NULL);
	void NotifyAllBrdVmpToCNC(u16 wEpID);

	void NotifyBrdVmpCfgToUI(BOOL32 bCNC = TRUE, BOOL32 bUmc = TRUE, TLogUser* ptUser = NULL);

	TBrdVmpRes* SelViewVmp(u16 wEqpID, BrdVmpCB	pfCB, void* pParam);
	TBrdVmpRes* VmpToTvWall(u16 wEqpID, BrdVmpCB pfCB, void* pParam);
	
	// �������úϳ�������
	TBrdVmpRes* GetVmpOutConf(u16 wEqpID, BrdVmpCB pfCB, void* pParam);
public:
	//////////////////////////////////////////////////////////////////////////
	//���úϳ�
	void OnUmcRerveseBrdVmpReq(CTpMsg *const ptMsg);
	void OnCncRerveseBrdVmpReq(CTpMsg *const ptMsg);

	void OnUmcSetBrdVmpReq(CTpMsg *const ptMsg);
	void OnCncSetBrdVmpReq(CTpMsg *const ptMsg);

	void OnUmcBrdVmpReq(CTpMsg *const ptMsg);
	void OnCncBrdVmpReq(CTpMsg *const ptMsg);

	void OnUmcVmpMemberCfgCmd(CTpMsg *const ptMsg);
	void OnCncVmpMemberCfgCmd(CTpMsg *const ptMsg);
	void OnSaveVmpPlanAck(CTpMsg *const ptMsg);
	
	//������ϳ�֪ͨ ֪ͨ�¼� 1���Ƿ�㲥�ϳ� 2���Ƿ����˺ϳ�
	void OnCasecadeVmpNtfy(CTpMsg *const ptMsg);

	void VmpCB(const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wMemberIndx);

#ifdef _USE_XMPUEQP_
	void XmpuBasCB(u32 dwType, CScreenBasRes* ptBasRes, void *pData);
#else
	void BasCB(CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes);
#endif
	// get vid failed CB Form down UMS
	BOOL32 AdjustGetVidFailed(CUmsConfInst* pcInst, u16 wGetIndex);

	void SetQtMediaKey(const TTPQTMediaKeyInfo& tInfo, u16 wConfId);
	//ֹͣ�����˺ϳ�
	void StopSpeakerVmp();

	//�ϳɹ㲥��ϳ�������
	static void OnVmpNAck(CTpMsg *const ptMsg);
	static void OnVmpConnect(CTpMsg *const ptMsg);
	static void OnVmpDisConnect(CTpMsg *const ptMsg);

	void OnVmpAskFrameToEp(CTpMsg *const ptMsg);
	// xmpu connect 
	void OnXmpuVmpMdyNty(TXmpuVmpMdyInfo tInfo);
	static void FlushXmpuVmp();
	void OnXmpuVmpDisConnect(u32	dwEqpID);
	static void UpdateXmpuUIVmp();
	static void DisConnectXmpuVmp(u32	dwEqpID);
	static void RefreashXmpuUIVmp(u16 wVmpNum);

protected:
	//UMC ռ�úϳ�����
	EmRervesVmpRet RerveseBrdVmp(TRersvesEqpReq& tReq);
	//UMS ���úϳ�����
	EmBrdVmpRet SetBrdVmp(TSetVmpInfoReq& tBrdReq);

	//UMC �㲥��ȡ���㲥 ֻ��һ�����Թ㲥
	EmBrdVmpRet BrdVmp(TBrdVmpReq& tReq);

	// xmpu Ԥռ�úϳ���
	EmRervesVmpRet RerveseXmpuVmp(TRersvesEqpReq& tReq);
	//UMS ���úϳ�����
	EmBrdVmpRet SetBrdXmpuVmp(TSetVmpInfoReq& tBrdReq);

	void UpdateBrdXmpuVmpParam(TBrdVmpRes* ptVmpRes);
	//�������кϳɳ�Ա��vip��ռ���ֱ���֡�ʵ������������ȵȡ�
	void AdjustBrdXmpuVmpMember(TBrdVmpRes* ptVmpRes);
	void ChangeBrdXmpuVmpParam(TBrdVmpRes* ptVmpRes);

	u16  CalcXmpuVipNum(TBrdVmpRes* ptVmpRes);
	void CalcXmpuVmpVipNum(TBrdVmpRes* ptVmpRes);

protected:

	void NotifySpeakerVmpToDownUms();


	void InstClear();
	//////////////////////////////////////////////////////////////////////////
	//umc���úϳ�

	//���������л᳡��Ŀ�꿴�ϳɹ㲥
	void AdjustNodeObjToBrdVmp(BOOL32 bStart);

	//���Ϳ����ϳ���Ϣ
	void StartBrdVmpReq(TBrdVmpRes* ptVmpRes);

	static TBrdVmpRes* FindIdleBrdVmp();
	static TBrdVmpRes* FindBrdVmpByEqp(u16 wEqpID);

	//�����ն����� ��һ�����ʵķ��
	EMVmpStyle FindStyleByMTNum(u16 wMtNum);

	//���ºϳɲ�������������
	void UpdateBrdVmpParam(TBrdVmpRes* ptVmpRes);
	void AdjustAutoVmpStyle(TBrdVmpRes* ptVmpRes);
	//�ͷŵ�ǰ�ϳɲ���
	void ReleaseBrdVmpParam(TBrdVmpRes* ptVmpRes);

	//���������ˡ���ϯ����
	void AdjustSpeakerFollow(TBrdVmpRes* ptVmpRes);

	//�������кϳɳ�Ա��vip��ռ���ֱ���֡�ʵ������������ȵȡ�
	void AdjustBrdVmpMember(TBrdVmpRes* ptVmpRes);
	BOOL32 AdjustMemberResByOld(TBrdVmpMember* ptMember);

	u16  CalcVipNum(EMVmpStyle tStyle, EMEqpModleType tType);
	void CalcBrdVmpVipNum(TBrdVmpRes* ptVmpRes);

	u16	CalcBrdVmpCanDsEpNum(TBrdVmpRes* ptVmpRes);

	void BackupBrdVmpParam(TBrdVmpRes* ptVmpRes);

	void AdjustVipForMember(TBrdVmpRes* ptVmpRes, TBrdVmpMember* ptMember, TVmpMemberPool* ptMemberPool);

	static u16 CountIdleVmpNum();
private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	friend class CNetPortMgr;
	
protected:
//////////////////////////////////////////////////////////////////////////
//�����˺ϳ�
	EmSpeakerVmpType	m_emVmpType;	//1 ��ϯ�ںϳ��2�������ںϳ���
	u16			m_wVmpEpID;	//��ǰ���ڲ��뻭��ϳɻ᳡ID
	BOOL32		m_bSpeakerVmpCfg;
	const CBaseService* m_pcSpeakerVmp;

//////////////////////////////////////////////////////////////////////////
//UMC���úϳ�
	static TBrdVmpRes	m_atBrdVmp[XMPU_MAX_VMP_NUM];
	TBrdVmpRes*			m_ptConfBrdVmp; //��ǰ�������ڹ㲥�ĺϳ�

	//��ǰ����ĺϳ�Ԥ��
	TSaveVmpCfg			m_tVmpCfg;

	TSaveCfgMgrArray	m_tSaveMgr;		//����Ԥ������

	TBrdVmpRes			m_tBrdVmpOld;   //�ϵ� ���ں��µĶԱ� �������ٷֱ��ʡ��������������ȵ�Ƶ���ͷź�����
	BOOL32				m_b108060;
	BOOL32				m_bBrdVmp;
	s8					m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS];
};

#endif // _h_umsvmp_h__