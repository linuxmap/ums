#ifndef _umsrollcall_h_
#define _umsrollcall_h_


#include "callinnerstruct.h"
#include "umscommonstruct.h"
#include "vmpserviecehandler.h"
#include "callnodemgr.h"
#include "umseapu.h"
#include "getvidaud.h"
#include "putaud.h"

enum EMRollCallEpMem
{
	em_RollCallerEp  = 0,       //点名者
	em_CallTargetEp,
	em_RollCallEpMemEnd = 3,
};


typedef struct tagTTargetResInfo
{
	u16 m_wEpId;                           //保存上一个点名者 ，用于释放上一个PUTAUD通道
	u16 m_aVidAudIndex;                    //保存上一个AssVidAud码流Index ,用于释放上一个上调码流通道

    tagTTargetResInfo()
	{
        Clear();
	}

	~tagTTargetResInfo()
	{
        Clear();
	}

	void Clear()
	{
         m_wEpId = TP_INVALID_INDEX;
		 m_aVidAudIndex = TP_INVALID_INDEX;
	}

}TTargetResInfo;



typedef struct tagTRollCallMixRes
{
	TAudMixInfo*	    m_ptMixRes;
	CDsListInfo         m_cToMixDsInfo;
	
	tagTRollCallMixRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_ptMixRes = NULL;
		m_cToMixDsInfo.Clear();
	}
	
}TRollCallMixRes;


typedef struct tagTRollCallEpInfo
{
    u16  m_wIndex;        // 在TRollCallEpInfo[em_RollCallEpMemEnd]中的索引，固定
    u16  m_wEpID;
	u16  m_wStrceenNum;   // 屏数
    BOOL32 m_bAudMixOn;   // 有无混音

	BOOL32  m_bIsSmallChanOn;
	BOOL32  m_bMtAdjustRes;   // 该会场是否支持降分辨率
	
	TTPMediaTransAddr   m_atPutAuddr[TP_MAX_STREAMNUM]; // 此讨论成员在下级中会用到；1. 上级将该会场需要的音频地址打到这里；2. 下级取这里的音频给node    
	CDsListInfo         m_cToPutAuddrDsInfo;

	TTPMediaTransAddr	m_tAudAddr;
	u32					m_dwMediaNode;
	u16					m_wGetindex;


    tagTRollCallEpInfo()
	{
		Clear();
	}

	void Clear()
	{
        m_wIndex = TP_INVALID_INDEX;
        m_wEpID  = TP_INVALID_INDEX;
        m_wStrceenNum = 0;
        m_bAudMixOn      = FALSE;

        m_bIsSmallChanOn = FALSE;
        m_bMtAdjustRes   = FALSE;
		
        ClearPutAuddr();
        ClearGetAudAddr();
	}

	void ClearPutAuddr()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atPutAuddr[wIndex].Clear();
		}
		m_cToPutAuddrDsInfo.Clear();
	}

	void ClearGetAudAddr()
	{
		m_tAudAddr.Clear();
		m_dwMediaNode = 0;
		m_wGetindex = TP_INVALID_INDEX;
	}

	BOOL32 IsValid()
	{
		return (IsSingleScr() || IsThreeScr());
	}
	
	BOOL32 IsSingleScr()
	{
		return (1 == m_wStrceenNum);
	}
	
	BOOL32 IsThreeScr()
	{
		return (3 == m_wStrceenNum);
	}

	void SetGetAudAddr(TGetVidAddr& tAddr)
	{
		m_tAudAddr = m_bAudMixOn ? tAddr.m_tMixAddr : tAddr.m_atAudAddr[MIDSCREENINDEX];
		m_dwMediaNode = tAddr.m_dwMedia;
	}


} TRollCallEpInfo;


typedef struct tagTVirCallerAddr
{
	TTPMediaTransAddr*	m_aptVidAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr*	m_aptAudAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr*	m_aptSmallAddr[TP_MAX_STREAMNUM];
	TTPMediaTransAddr*	m_ptMixAddr;

	u32					m_adwMediaNode[TP_MAX_STREAMNUM];	//仅供会场选看使用
	u32					m_dwMedia;
    
	tagTVirCallerAddr()
	{
        Clear();
	}


	void Clear()
	{
        for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
            m_aptVidAddr[wIndex] = NULL;
			m_aptAudAddr[wIndex] = NULL;
			m_aptSmallAddr[wIndex] = NULL;

			m_adwMediaNode[wIndex] = 0;
		}

        m_ptMixAddr = NULL;
		m_dwMedia = 0;
	}

	void Release()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if (NULL != m_aptVidAddr[wIndex])
			{
				CUmsConfInst::GetRollAddrList()->FreeBuff(m_aptVidAddr[wIndex]);
				m_aptVidAddr[wIndex] = NULL;
			}
			
			if (NULL != m_aptAudAddr[wIndex])
			{
				CUmsConfInst::GetRollAddrList()->FreeBuff(m_aptAudAddr[wIndex]);
				m_aptAudAddr[wIndex] = NULL;
			}
			
			if (NULL != m_aptSmallAddr[wIndex])
			{
				CUmsConfInst::GetRollAddrList()->FreeBuff(m_aptSmallAddr[wIndex]);
				m_aptSmallAddr[wIndex] = NULL;
			}

            m_adwMediaNode[wIndex] = 0;

		}
		
		if (NULL != m_ptMixAddr)
		{
			CUmsConfInst::GetRollAddrList()->FreeBuff(m_ptMixAddr);
			m_ptMixAddr = NULL;
		}
        m_dwMedia = 0;
	}


	BOOL32 AssignAddr(CUmsConfInst* pInst)
	{
        for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_aptVidAddr[wIndex] = CUmsConfInst::GetRollAddrList()->AllocNode();
			if (NULL == m_aptVidAddr[wIndex])
			{
				//MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local vid-address failed.\n"));
				Release();
				return FALSE;
			}
			else
			{
				m_aptVidAddr[wIndex]->SetIP(pInst->GetConfEqpDs().m_dwEqpIp);
			} 


			m_aptAudAddr[wIndex] = CUmsConfInst::GetRollAddrList()->AllocNode();
			if (NULL == m_aptAudAddr[wIndex])
			{
				//MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local aud-address failed.\n"));
				Release();
				return FALSE;
			}
			else
			{
				m_aptAudAddr[wIndex]->SetIP(pInst->GetConfEqpDs().m_dwEqpIp);
			}


			m_aptSmallAddr[wIndex] = CUmsConfInst::GetRollAddrList()->AllocNode();
			if (NULL == m_aptSmallAddr[wIndex])
			{
				//MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local small-address failed.\n"));
				Release();
				return FALSE;
			}
			else
			{
				m_aptSmallAddr[wIndex]->SetIP(pInst->GetConfEqpDs().m_dwEqpIp);
			}

            m_adwMediaNode[wIndex] = pInst->GetConfEqpDs().m_dwEqpNode;

		}

		m_ptMixAddr = CUmsConfInst::GetRollAddrList()->AllocNode();
		if (NULL == m_ptMixAddr)
		{
			//MdlError(Ums_Mdl_Call, ("CDispatchInfo::AssignLocalAddr Assign local mix-address failed.\n"));
			Release();
			return FALSE;
		}
		else
		{
			m_ptMixAddr->SetIP(pInst->GetConfEqpDs().m_dwEqpIp);
		}

        m_dwMedia = pInst->GetConfEqpDs().m_dwEqpNode;


		return TRUE;
	}

    ~tagTVirCallerAddr()
	{
        Release();
	}


}TVirCallerAddr;



typedef struct tagTRollCallInfo
{
	TRollCallEpInfo  m_atRollCallEpInfo[em_RollCallEpMemEnd];

	TVirCallerAddr  m_tVirCallerAddr;
    CDsListInfo     m_cToVirCallerDsInfo;


    //TRollCallNotifyEpInfo   m_TEpState[TP_MAX_ROLLCALL_NUM];

    tagTRollCallInfo()
	{
		Clear();
	}


	void Clear()
	{   
		u16 wIndex;

        m_tVirCallerAddr.Clear();
		m_cToVirCallerDsInfo.Clear();
 
		for(wIndex = 0; wIndex < em_RollCallEpMemEnd; wIndex++)
		{
            m_atRollCallEpInfo[wIndex].Clear();
		}
	}

    TRollCallEpInfo *GetRollCallEpInfo(u16 wEpID)
	{
        for(u16 wIndex = 0; wIndex < em_RollCallEpMemEnd; wIndex++)
		{
            if (m_atRollCallEpInfo[wIndex].m_wEpID == wEpID)
			{
                return &m_atRollCallEpInfo[wIndex];
			}
		}

		return NULL;	 
	}


	TRollCallEpInfo *GetRollCallEpInfoByIndex(u16 wIndex)
	{
        if (wIndex < em_RollCallEpMemEnd)
		{
            return &m_atRollCallEpInfo[wIndex];
		}
		
		return NULL;	 
	}


    TRollCallEpInfo *AddEp(TCallNode* ptNode)
	{
		if (NULL == ptNode)
		{
			return NULL;
		}


		for (u16 wIndex = 0; wIndex < em_RollCallEpMemEnd; wIndex++)
		{
			if (m_atRollCallEpInfo[wIndex].m_wEpID == ptNode->m_wEpID)
			{
				return NULL;
			}
			if (m_atRollCallEpInfo[wIndex].m_wEpID == TP_INVALID_INDEX)
			{
				m_atRollCallEpInfo[wIndex].m_wIndex         = wIndex;
				m_atRollCallEpInfo[wIndex].m_wEpID          = ptNode->m_wEpID;
				m_atRollCallEpInfo[wIndex].m_bAudMixOn      = ptNode->IsThreeAudSnd()?TRUE:FALSE; // 三屏会场有混音
				m_atRollCallEpInfo[wIndex].m_wStrceenNum    = ptNode->m_wVidSndNum;  // 终端的视频发送通道数，即为屏数
				m_atRollCallEpInfo[wIndex].m_bIsSmallChanOn = ptNode->IsSmallVidSnd();
				m_atRollCallEpInfo[wIndex].m_bMtAdjustRes   = ptNode->IsCanAdjustRes(); // 除vrs外的，科达终端支持降分辨率

				return &m_atRollCallEpInfo[wIndex];
			}
		}

        return NULL;
	}


    void DelEp(u16 wEp)
	{
		for (u16 wIndex = 0; wIndex < em_RollCallEpMemEnd; wIndex++)
		{
			if (m_atRollCallEpInfo[wIndex].m_wEpID == wEp)
			{
				m_atRollCallEpInfo[wIndex].Clear();
				return;
			}
		}

	    return;
	}


	void GetTargetResInfo(u16 wOldTarget, TTargetResInfo &TargetRes)
	{
		TargetRes.m_wEpId        = wOldTarget;

        for (u16 wIndex = 0; wIndex < em_RollCallEpMemEnd; wIndex++)
		{
			if (m_atRollCallEpInfo[wIndex].m_wEpID == wOldTarget)
			{
				TargetRes.m_aVidAudIndex = m_atRollCallEpInfo[wIndex].m_wGetindex;
				return;
			}
		}

	}


}TRollCallInfo;



class CUmsRollCallMgr
{

public:
	CUmsRollCallMgr(CUmsConfInst* pcInst):m_pcConf(pcInst) {}
	~CUmsRollCallMgr(){}

	void Exit();
	void Show();
	void Enter();

    void ReleaseRollCall();


#ifdef _USE_XMPUEQP_
	void XmpuMixCB( u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData );	
#else
	void MixCB( TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo );
#endif

	TRollCallEpInfo* GetRollCallEpInfoById(const u16 wEpId) { return m_tRollCallInfo.GetRollCallEpInfo(wEpId);}
	void GetRollCallEpAudAddr(u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr);

	 //主席（点名人）在下级，往上级UMS打点名人主码流
    void UploadRollCallerMainVid(TCapNode* ptNodeUms, TUmsDsData *ptDsData, u16 &wDsNum); 

	//点名模式下，往上级打小码流（发言人的小码流或主席小码流）  
	void UploadRollCallerSmallVid(TCapNode* ptNodeUms, TUmsDsData *ptDsData, u16 &wDsNum);
   
	BOOL32 IsRollCallModle() { return m_bRollcallStaus; }
	BOOL32 IsUIRollCallOn()  { return m_bUIRollcallStatus;}   // 上级使用：跟界面同步的一个点名状态


    TVirCallerAddr *GetVirCallerAddr(){ return &m_tRollCallInfo.m_tVirCallerAddr;}
    CDsListInfo&  GetVirCallerDs(){ return m_tRollCallInfo.m_cToVirCallerDsInfo;}

	u16 GetRollCallerEpId() {return m_tRollCallEpList.GetRollCaller();}
    u16 GetCallTargetEpId() {return m_tRollCallEpList.GetRollCallTarget();}

	TRollCallMixRes *GetMixRes() {return &m_tMixRes;}


	void GetSpeakertObj(TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);
	void GetChairObj(TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);

    //获取 “被点名者” 视频三屏源地址 （“被点名者”需要看的目标）
    void GetTargetVidSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);
	//获取 “被点名者” 单屏混音源地址（所有非点名者，非被点名者 的目标，即点名者、被名者 的混音）
    void GetTargetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam );
	
	
	//获取 所有三屏会场音频
	void GetRollCallSrcAud(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);
	

	//获取 非 “被点名者”（obj = speaker）  MIX 地址
    void GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam );

    BOOL32 AskKeyFrameToChair(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);

	void RollCallInfoNotifyToLowUms(EMRollCallNotyToLowUmsType emNotyType); 

    void AdjustInnerSpeaker(TCallNode* ptNode);
	
	void RollCallAudPudDown(u16 wCallerEpId);


	// 上线和下线处理
	void OnChanConnect(TCallNode* ptNode);
	void OnHungUpNode(TCallNode* ptNode, EmCnsCallReason emReason = EmCnsCallReason_success);

	u16 GetBackUpSpeaker() {return m_wBackSpeaker;}

	//获取点名状态
	void GetRollCallStateInfo(TConfRollCallInfo& tRollCallInfo, EmRollCallRspRet emRspState = em_RollCallOprRsp_Ok);
    
	//获取点名与会状态
	void GetAllRollCallPresentStateInfo(TRollCallPresentStateMsg& tPresentState);

protected:
	void Clear();
    CUmsConfInst* Inst(){ return (CUmsConfInst*)m_pcConf; }

	//点名状态通知
    void RollCallStatesNotify(EmRollCallRspRet	emRspState = em_RollCallOprRsp_Ok);

	//点名答到情况通知
	void RollCallPresentStateNotify();

	//点名终止
    void StopRollCallModle();

	EmRollCallRspRet	AssignResource();  // edited
	void				ReleaseResoure();  // edited
	

	void AddDelListUmcCnc(TUpdataRollCallList &tListInfo, TUpdataRollCallListRes &TRet);

    void RollCallStatusCmdFromUmcCnc(TConfRollCallInfo& tRollCallInfo);
	BOOL32 UptateRollCallListFromUI(TRollCallList  &tRollCallList);

    BOOL32 StartRollCallModle(TConfRollCallInfo& tRollCallInfo);
    void OnRollCallStatusCmdFromUmc( CTpMsg* const ptMsg );  // UMC过来，开启、关闭点名
    void OnRollCallNextEpFromUmc(CTpMsg* const ptMsg );      // UMC过来，点名下一个
	void OnRollCallUpdateListFromUmc(CTpMsg* const ptMsg );    //UMC过来，更新列表
	void OnRollCallUpdatePresentStateFromUmc(CTpMsg* const ptMsg);    //UMC过来，更新会场答到情况


    BOOL32 RollCallNextEpFromUmcCnc(TRollCallNextEpInfo &tCallNextEpInfo);
    void OnRollCallStatusCmdFromCnc(CTpMsg *const ptMsg);  // 主席过来，开启、关闭点名
	void OnRollCallNextEpFromCnc(CTpMsg *const ptMsg);   //主席过来，点名下一个
   	void OnRollCallUpdateListFromCnc(CTpMsg* const ptMsg );    //主席过来，更新列表
	void OnRollCallUpdatePresentStateFromCmc(CTpMsg* const ptMsg);    //主席过来，更新会场答到情况


	void AdjustRollCallStatus();  

	void MakeNotifyMsg(TRollCallCasecadeNtfy &tNtfy, EMRollCallNotyToLowUmsType emNotyType, u16 wCaller, u16 wTarget);
	void OnCasecadeRollCallNtfy(CTpMsg *const ptMsg); // edited

    void MixRollCallerAndTarget();  
	u16 GetRollCallerToVirRollCaller();

	BOOL32 AddRollCallEpChan(u16 wEpId);
    void ReleaseRollCallEpChan(u16 wEpId);


    BOOL32 UpdateRollCallEpInfo(u16 wEpId);

	//获取 “被点名者” 单屏视频源地址 （单屏“被点名者” 需要看的目标）
	void GetTargetMixVidSrcAddr(TCapNode* ptNode, TTransParam &tParam);
	//获取  “被点名者”三屏视频源地址
    void GetTargetVid(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);


	//获取 三屏 非 “被点名者”音频源地址
    void GetAudSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);
	//获取 “被点名者” 音频源地址
    void GetTargetAudSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);

	//点名按被点名人为发言人处理的，结束点名恢复原发言人
    void GetBackupSpeaker();
	void ModRestore();

    BOOL32 CheckRollCallEpCap(u16 wEpId);

	BOOL32 IsNeedSendRollCallerSmall();

public:

    // 处理umc消息
	BOOL32 HandlerFromUmc(CTpMsg *const ptMsg);
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );

	void OpenEpDownAudCmd( CTpMsg *const ptMsg );
    void OpenEpDownAudAck( CTpMsg *const ptMsg );
    void CloseEpDownAudCmd( CTpMsg *const ptMsg );

private:
    
	u16                     m_wBackSpeaker;   //开启点名前的发言人

    TRollCallCasecadeNtfy   m_tNoty;          //下级使用，上级通知到下级，用于保存当前点名者、被点名者信息

	CUmsConfInst*           m_pcConf;

	TRollCallMixRes			m_tMixRes;        // edited

    TRollCallInfo           m_tRollCallInfo;


	TRollCallList			m_tRollCallEpList;//点名列表
    EmRollCallPresentState  m_aemPresentState[TP_MAX_ROLLCALL_NUM];    // 会场答到信息


	BOOL32                  m_bUIRollcallStatus;  //与 UI 同步一个状态，所有会场尚未刷点名的码流, 开启点名设置此变量
	BOOL32                  m_bRollcallStaus;     //点名开启/关闭， 真正开始点名某会场设置此变量

};



#endif