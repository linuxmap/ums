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
//合成策略：
//发言人、主席、外厂商、监控 可能占用vip
//1、开启合成后，有跟随，则调整跟随会场，必要时抢占vip。其他会场依次进合成，需要vip，则根据vip优先级抢占vip。
//vip不足，则降分辨率，降失败则不创建交换（画面合成显示默认画面），并提示
//2、掉线后，如果占用了vip，则根据vip优先级，刷新，重新分配vip。
//3、上线后，如果需要占用vip，则查找是否有vip。没有则不创建交换。
//4、切发言人，如果需要占用vip，则直接抢占，给出影响提示。

//如果一个会场占用两个通道，也可以理解成同时在两个或多个合成器中，那么需要综合计算。策略为：
//1、首先保证发言人。必要时抢占。
//2、如果一个合成器vip充足，而另外一个不够，则另外一个不创建交换。

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
	u8			m_byVip;      // 是否是vip
	u8			m_byDs;       // 是否创建交换
	u8          m_bySmallVid; // 是否用小码流进合成
	u8          m_byAdjustRes; // 是否调整分辨率

	TTPVMPMember	m_tVmpMember;
	EmTpVideoResolution m_emRes;

	TGetVidAddr		m_tGetAddr;   //选看上调码流
	u16             m_wGetIndex;  //上调码流的index，释放的时候会用到

	u16				m_wIndx;//初始化 永不清除
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
		{// 从后开始循环，保证wNullIndex是最靠前的NULL Index
			if (NULL == m_aptVmpMember[wIndex - 1])
			{
				wNullIndex = wIndex - 1;
				continue;
			}
			else
			{
				if (ptMember->m_wIndx == m_aptVmpMember[wIndex - 1]->m_wIndx)
				{// 已经存在，不重复添加
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
	{// get过后，如果成功抢占，需要DelMember

		TBrdVmpMember* ptMember = NULL;
		u16 wLevel = TP_INVALID_INDEX;
		for (u16 wLoop = 0; wLoop < TP_VMP_MAX_IN_CHN_NUM; wLoop++)
		{// 遍历一遍，取level最低，且小于wInLevel的有效member

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
	TBrdVmpMember	m_atMember[TP_VMP_MAX_IN_CHN_NUM];	//合成成员
	BOOL32			m_bNeedAdjVip;

	u16				m_wVipNum;//Vip数量 要根据会场格式和当前风格动态调整
	u16				m_wCurVipNum;



	//xmpu vmp 专用
	BOOL32			m_bOnLine;
//	BOOL32			m_bNeedAdjMember;
	TTPTransAddr	m_atDecMiddleRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码通道rtp rcv
	TTPTransAddr	m_atDecRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码通道rtp rcv
	TTPTransAddr	m_atDecRtcpAddr[TP_VMP_MAX_IN_CHN_NUM];  // vmp解码通道 back rtcp rcv
	TTPTransAddr	m_atEncRtpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr	m_atEncRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv
	CDsListInfo         m_cToVmpDsInfo;

	BrdVmpCB		m_pfSelViewCB;
	void*			m_pSelViewParam;

	BrdVmpCB		m_pfTvWallCB;
	void*			m_pTvWallParam;

	BrdVmpCB		m_pfGetVmpCB;       // 不入会调用合成器画面
	void*			m_pGetVmpParam;

	u8				m_byVipMaxStyle; // 最大几(4)风格下，全前适配通道
	u8				m_byVipNum;		// 超过几(4)风格，存在的前适配通道数量
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
		//找不到，尝试清掉一个最老的数据
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
	{// 按level由高到低排列
		u16 wIndex = 0;
		u16 wIndexTemp = 0;
		for (wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex++)
		{
			if (m_atVmpChnl[wIndex].IsValid())
			{
				if (m_awLevel[wIndex] < wLevel)
				{
					for (wIndexTemp = TP_VMP_MAX_IN_CHN_NUM-1; wIndexTemp > wIndex; wIndexTemp--)
					{// 此位置以后的，后移一位
						m_atVmpChnl[wIndexTemp].m_wEpID = m_atVmpChnl[wIndexTemp - 1].m_wEpID;
						m_atVmpChnl[wIndexTemp].m_wScrIndx = m_atVmpChnl[wIndexTemp - 1].m_wScrIndx;
						m_awLevel[wIndexTemp] = m_awLevel[wIndexTemp - 1];
					}
					//取代位置
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
	{// 删除level最低的一个成员
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
		VmpStat_Idle,//空闲启
		VmpStat_Running,//正确开启
		VmpStat_Full,//无空闲合成器
		VmpStat_Error,//出错，该会议永远不再用合成器
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
	{// 发言人是否进合成
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
	{//主席是否进合成，非发言人才行
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
	{// 发言人合成是否启用
		return NULL != m_pcSpeakerVmp;
	}

	CDsListInfo& GetToVmpDs()	{ return Inst()->GetSpeaker().m_tToVmpDs; }
	
	TBrdVmpRes* GetConfBrdVmp() { return m_ptConfBrdVmp; }

	s8*			GetBrdVmpAlias() { return m_szBrdVmpAlias; }

//////////////////////////////////////////////////////////////////////////
//发言人合成
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

	//将合成状态更新到界面 UMC为所有用户，CNC为所有会议的所有会场
	static void NotifyBrdVmpToAllConf(u8 byEqpID, EmTpOprType emOpr);
	static void NotifyBrdVmpToAllConf(TBrdVmpRes* ptVmpRes, EmTpOprType emOpr);
	static void NotifyBrdVmpToUMC(TBrdVmpRes* ptVmpRes, EmTpOprType emOpr);
	void NotifyBrdVmpToCNC(TBrdVmpRes* ptVmpRes, EmTpOprType emOpr);


	void NotifyAllBrdVmpToUMC(TLogUser* ptUser = NULL);
	void NotifyAllBrdVmpToCNC(u16 wEpID);

	void NotifyBrdVmpCfgToUI(BOOL32 bCNC = TRUE, BOOL32 bUmc = TRUE, TLogUser* ptUser = NULL);

	TBrdVmpRes* SelViewVmp(u16 wEqpID, BrdVmpCB	pfCB, void* pParam);
	TBrdVmpRes* VmpToTvWall(u16 wEqpID, BrdVmpCB pfCB, void* pParam);
	
	// 不入会调用合成器画面
	TBrdVmpRes* GetVmpOutConf(u16 wEqpID, BrdVmpCB pfCB, void* pParam);
public:
	//////////////////////////////////////////////////////////////////////////
	//配置合成
	void OnUmcRerveseBrdVmpReq(CTpMsg *const ptMsg);
	void OnCncRerveseBrdVmpReq(CTpMsg *const ptMsg);

	void OnUmcSetBrdVmpReq(CTpMsg *const ptMsg);
	void OnCncSetBrdVmpReq(CTpMsg *const ptMsg);

	void OnUmcBrdVmpReq(CTpMsg *const ptMsg);
	void OnCncBrdVmpReq(CTpMsg *const ptMsg);

	void OnUmcVmpMemberCfgCmd(CTpMsg *const ptMsg);
	void OnCncVmpMemberCfgCmd(CTpMsg *const ptMsg);
	void OnSaveVmpPlanAck(CTpMsg *const ptMsg);
	
	//级联间合成通知 通知下级 1、是否广播合成 2、是否发言人合成
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
	//停止发言人合成
	void StopSpeakerVmp();

	//合成广播类合成器处理
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
	//UMC 占用合成外设
	EmRervesVmpRet RerveseBrdVmp(TRersvesEqpReq& tReq);
	//UMS 配置合成外设
	EmBrdVmpRet SetBrdVmp(TSetVmpInfoReq& tBrdReq);

	//UMC 广播和取消广播 只有一个可以广播
	EmBrdVmpRet BrdVmp(TBrdVmpReq& tReq);

	// xmpu 预占用合成器
	EmRervesVmpRet RerveseXmpuVmp(TRersvesEqpReq& tReq);
	//UMS 配置合成外设
	EmBrdVmpRet SetBrdXmpuVmp(TSetVmpInfoReq& tBrdReq);

	void UpdateBrdXmpuVmpParam(TBrdVmpRes* ptVmpRes);
	//调整所有合成成员：vip抢占、分辨率帧率调整、码流调度等。
	void AdjustBrdXmpuVmpMember(TBrdVmpRes* ptVmpRes);
	void ChangeBrdXmpuVmpParam(TBrdVmpRes* ptVmpRes);

	u16  CalcXmpuVipNum(TBrdVmpRes* ptVmpRes);
	void CalcXmpuVmpVipNum(TBrdVmpRes* ptVmpRes);

protected:

	void NotifySpeakerVmpToDownUms();


	void InstClear();
	//////////////////////////////////////////////////////////////////////////
	//umc配置合成

	//调整到所有会场的目标看合成广播
	void AdjustNodeObjToBrdVmp(BOOL32 bStart);

	//发送开启合成消息
	void StartBrdVmpReq(TBrdVmpRes* ptVmpRes);

	static TBrdVmpRes* FindIdleBrdVmp();
	static TBrdVmpRes* FindBrdVmpByEqp(u16 wEqpID);

	//根据终端数量 找一个合适的风格
	EMVmpStyle FindStyleByMTNum(u16 wMtNum);

	//更新合成参数：界面请求
	void UpdateBrdVmpParam(TBrdVmpRes* ptVmpRes);
	void AdjustAutoVmpStyle(TBrdVmpRes* ptVmpRes);
	//释放当前合成参数
	void ReleaseBrdVmpParam(TBrdVmpRes* ptVmpRes);

	//调整发言人、主席跟随
	void AdjustSpeakerFollow(TBrdVmpRes* ptVmpRes);

	//调整所有合成成员：vip抢占、分辨率帧率调整、码流调度等。
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
//发言人合成
	EmSpeakerVmpType	m_emVmpType;	//1 主席在合成里，2发言人在合成中
	u16			m_wVmpEpID;	//当前正在参与画面合成会场ID
	BOOL32		m_bSpeakerVmpCfg;
	const CBaseService* m_pcSpeakerVmp;

//////////////////////////////////////////////////////////////////////////
//UMC配置合成
	static TBrdVmpRes	m_atBrdVmp[XMPU_MAX_VMP_NUM];
	TBrdVmpRes*			m_ptConfBrdVmp; //当前会议正在广播的合成

	//当前会议的合成预案
	TSaveVmpCfg			m_tVmpCfg;

	TSaveCfgMgrArray	m_tSaveMgr;		//保存预案管理

	TBrdVmpRes			m_tBrdVmpOld;   //老的 便于和新的对比 尽量减少分辨率、交换、码流调度等频繁释放和申请
	BOOL32				m_b108060;
	BOOL32				m_bBrdVmp;
	s8					m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS];
};

#endif // _h_umsvmp_h__