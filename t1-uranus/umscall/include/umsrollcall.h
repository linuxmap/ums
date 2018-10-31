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
	em_RollCallerEp  = 0,       //������
	em_CallTargetEp,
	em_RollCallEpMemEnd = 3,
};


typedef struct tagTTargetResInfo
{
	u16 m_wEpId;                           //������һ�������� �������ͷ���һ��PUTAUDͨ��
	u16 m_aVidAudIndex;                    //������һ��AssVidAud����Index ,�����ͷ���һ���ϵ�����ͨ��

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
    u16  m_wIndex;        // ��TRollCallEpInfo[em_RollCallEpMemEnd]�е��������̶�
    u16  m_wEpID;
	u16  m_wStrceenNum;   // ����
    BOOL32 m_bAudMixOn;   // ���޻���

	BOOL32  m_bIsSmallChanOn;
	BOOL32  m_bMtAdjustRes;   // �û᳡�Ƿ�֧�ֽ��ֱ���
	
	TTPMediaTransAddr   m_atPutAuddr[TP_MAX_STREAMNUM]; // �����۳�Ա���¼��л��õ���1. �ϼ����û᳡��Ҫ����Ƶ��ַ�����2. �¼�ȡ�������Ƶ��node    
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

	u32					m_adwMediaNode[TP_MAX_STREAMNUM];	//�����᳡ѡ��ʹ��
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
				m_atRollCallEpInfo[wIndex].m_bAudMixOn      = ptNode->IsThreeAudSnd()?TRUE:FALSE; // �����᳡�л���
				m_atRollCallEpInfo[wIndex].m_wStrceenNum    = ptNode->m_wVidSndNum;  // �ն˵���Ƶ����ͨ��������Ϊ����
				m_atRollCallEpInfo[wIndex].m_bIsSmallChanOn = ptNode->IsSmallVidSnd();
				m_atRollCallEpInfo[wIndex].m_bMtAdjustRes   = ptNode->IsCanAdjustRes(); // ��vrs��ģ��ƴ��ն�֧�ֽ��ֱ���

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

	 //��ϯ�������ˣ����¼������ϼ�UMS�������������
    void UploadRollCallerMainVid(TCapNode* ptNodeUms, TUmsDsData *ptDsData, u16 &wDsNum); 

	//����ģʽ�£����ϼ���С�����������˵�С��������ϯС������  
	void UploadRollCallerSmallVid(TCapNode* ptNodeUms, TUmsDsData *ptDsData, u16 &wDsNum);
   
	BOOL32 IsRollCallModle() { return m_bRollcallStaus; }
	BOOL32 IsUIRollCallOn()  { return m_bUIRollcallStatus;}   // �ϼ�ʹ�ã�������ͬ����һ������״̬


    TVirCallerAddr *GetVirCallerAddr(){ return &m_tRollCallInfo.m_tVirCallerAddr;}
    CDsListInfo&  GetVirCallerDs(){ return m_tRollCallInfo.m_cToVirCallerDsInfo;}

	u16 GetRollCallerEpId() {return m_tRollCallEpList.GetRollCaller();}
    u16 GetCallTargetEpId() {return m_tRollCallEpList.GetRollCallTarget();}

	TRollCallMixRes *GetMixRes() {return &m_tMixRes;}


	void GetSpeakertObj(TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);
	void GetChairObj(TCapNode* ptNode, u16 wScreenIndx, TTpObj& tObj);

    //��ȡ ���������ߡ� ��Ƶ����Դ��ַ �����������ߡ���Ҫ����Ŀ�꣩
    void GetTargetVidSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);
	//��ȡ ���������ߡ� ��������Դ��ַ�����зǵ����ߣ��Ǳ������� ��Ŀ�꣬�������ߡ������� �Ļ�����
    void GetTargetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam );
	
	
	//��ȡ ���������᳡��Ƶ
	void GetRollCallSrcAud(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);
	

	//��ȡ �� ���������ߡ���obj = speaker��  MIX ��ַ
    void GetMixSrcAddr( TCapNode* ptNode, TTransParam& tVidParam, TTransParam& tAudParam );

    BOOL32 AskKeyFrameToChair(TCapNode* ptNode, u16 wDecIndex, BOOL32 bReqBySys);

	void RollCallInfoNotifyToLowUms(EMRollCallNotyToLowUmsType emNotyType); 

    void AdjustInnerSpeaker(TCallNode* ptNode);
	
	void RollCallAudPudDown(u16 wCallerEpId);


	// ���ߺ����ߴ���
	void OnChanConnect(TCallNode* ptNode);
	void OnHungUpNode(TCallNode* ptNode, EmCnsCallReason emReason = EmCnsCallReason_success);

	u16 GetBackUpSpeaker() {return m_wBackSpeaker;}

	//��ȡ����״̬
	void GetRollCallStateInfo(TConfRollCallInfo& tRollCallInfo, EmRollCallRspRet emRspState = em_RollCallOprRsp_Ok);
    
	//��ȡ�������״̬
	void GetAllRollCallPresentStateInfo(TRollCallPresentStateMsg& tPresentState);

protected:
	void Clear();
    CUmsConfInst* Inst(){ return (CUmsConfInst*)m_pcConf; }

	//����״̬֪ͨ
    void RollCallStatesNotify(EmRollCallRspRet	emRspState = em_RollCallOprRsp_Ok);

	//���������֪ͨ
	void RollCallPresentStateNotify();

	//������ֹ
    void StopRollCallModle();

	EmRollCallRspRet	AssignResource();  // edited
	void				ReleaseResoure();  // edited
	

	void AddDelListUmcCnc(TUpdataRollCallList &tListInfo, TUpdataRollCallListRes &TRet);

    void RollCallStatusCmdFromUmcCnc(TConfRollCallInfo& tRollCallInfo);
	BOOL32 UptateRollCallListFromUI(TRollCallList  &tRollCallList);

    BOOL32 StartRollCallModle(TConfRollCallInfo& tRollCallInfo);
    void OnRollCallStatusCmdFromUmc( CTpMsg* const ptMsg );  // UMC�������������رյ���
    void OnRollCallNextEpFromUmc(CTpMsg* const ptMsg );      // UMC������������һ��
	void OnRollCallUpdateListFromUmc(CTpMsg* const ptMsg );    //UMC�����������б�
	void OnRollCallUpdatePresentStateFromUmc(CTpMsg* const ptMsg);    //UMC���������»᳡�����


    BOOL32 RollCallNextEpFromUmcCnc(TRollCallNextEpInfo &tCallNextEpInfo);
    void OnRollCallStatusCmdFromCnc(CTpMsg *const ptMsg);  // ��ϯ�������������رյ���
	void OnRollCallNextEpFromCnc(CTpMsg *const ptMsg);   //��ϯ������������һ��
   	void OnRollCallUpdateListFromCnc(CTpMsg* const ptMsg );    //��ϯ�����������б�
	void OnRollCallUpdatePresentStateFromCmc(CTpMsg* const ptMsg);    //��ϯ���������»᳡�����


	void AdjustRollCallStatus();  

	void MakeNotifyMsg(TRollCallCasecadeNtfy &tNtfy, EMRollCallNotyToLowUmsType emNotyType, u16 wCaller, u16 wTarget);
	void OnCasecadeRollCallNtfy(CTpMsg *const ptMsg); // edited

    void MixRollCallerAndTarget();  
	u16 GetRollCallerToVirRollCaller();

	BOOL32 AddRollCallEpChan(u16 wEpId);
    void ReleaseRollCallEpChan(u16 wEpId);


    BOOL32 UpdateRollCallEpInfo(u16 wEpId);

	//��ȡ ���������ߡ� ������ƵԴ��ַ ���������������ߡ� ��Ҫ����Ŀ�꣩
	void GetTargetMixVidSrcAddr(TCapNode* ptNode, TTransParam &tParam);
	//��ȡ  ���������ߡ�������ƵԴ��ַ
    void GetTargetVid(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);


	//��ȡ ���� �� ���������ߡ���ƵԴ��ַ
    void GetAudSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);
	//��ȡ ���������ߡ� ��ƵԴ��ַ
    void GetTargetAudSrcAddr(u16 wScreenIndex, TCapNode* ptNode, TTransParam &tParam);

	//��������������Ϊ�����˴���ģ����������ָ�ԭ������
    void GetBackupSpeaker();
	void ModRestore();

    BOOL32 CheckRollCallEpCap(u16 wEpId);

	BOOL32 IsNeedSendRollCallerSmall();

public:

    // ����umc��Ϣ
	BOOL32 HandlerFromUmc(CTpMsg *const ptMsg);
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );

	void OpenEpDownAudCmd( CTpMsg *const ptMsg );
    void OpenEpDownAudAck( CTpMsg *const ptMsg );
    void CloseEpDownAudCmd( CTpMsg *const ptMsg );

private:
    
	u16                     m_wBackSpeaker;   //��������ǰ�ķ�����

    TRollCallCasecadeNtfy   m_tNoty;          //�¼�ʹ�ã��ϼ�֪ͨ���¼������ڱ��浱ǰ�����ߡ�����������Ϣ

	CUmsConfInst*           m_pcConf;

	TRollCallMixRes			m_tMixRes;        // edited

    TRollCallInfo           m_tRollCallInfo;


	TRollCallList			m_tRollCallEpList;//�����б�
    EmRollCallPresentState  m_aemPresentState[TP_MAX_ROLLCALL_NUM];    // �᳡����Ϣ


	BOOL32                  m_bUIRollcallStatus;  //�� UI ͬ��һ��״̬�����л᳡��δˢ����������, �����������ô˱���
	BOOL32                  m_bRollcallStaus;     //��������/�رգ� ������ʼ����ĳ�᳡���ô˱���

};



#endif