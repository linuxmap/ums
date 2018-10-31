#ifndef _h_selviewmgr_h__
#define _h_selviewmgr_h__

#include "tphandle.h"
#include "eqpinterface.h"
#include "callinnerstruct.h"
#include "umsconfigex.h"
#include "umsconfinst.h"
#include "umsvmp.h"

//////////////////////////////////////////////////////////////////////////
//coder : ����
//Լ����ֻ��ѡ�����������¼��᳡

//UMC���Բ����᳡�б��е����л᳡����ѡ������ѡ��Ŀ�������ѡ���᳡�ı��������¼���
//��ˣ�UMSֻ������ѡ���᳡�����Ǳ����᳡����ת����Ӧ��UMS���д�������ѡ��״̬Ҫ���µ����ϼ�UMS��

//�ؼ�֡����:�ڱ�������

//Լ����1��ͬһ�������������������ȴ����������ntfy���߻�Ӧ����ܽ�����һ�δ�������ܾ���
//2����Ӧ��Ind��ֻ���ڴ�������£��Ż�Ӧ��һ�����ntfyΪ׼��
//3����Ӧ һ���Ǹ������������棩��Ӧ���������־����û����������cnc��umc��

#define UMS_MAX_SELVIEW_NUM 100

typedef struct tagTTPSession
{
	EmUIType	m_emType;
	u8			m_auReverse[20];
	tagTTPSession()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPSession));
	}
}TTPSession;

typedef struct tagTSelViewMgr
{
	BOOL32			m_bLocal;//�Ƿ񱾼�����
	BOOL32			m_bEpSel;
	TTPSelViewReq	m_tSelView;

	TBrdVmpRes*			m_ptItor;
	TGetVidAddr			m_tGetAddr;   //ѡ���ϵ�����
	u16                 m_wGetIndex;  //�ϵ�������index���ͷŵ�ʱ����õ�

	tagTSelViewMgr()
	{
		Clear();
	}

	void Clear()
	{
		m_bLocal = FALSE;
		m_bEpSel = FALSE;
		m_tSelView.Clear();
		m_ptItor = NULL;
		memset(&m_tGetAddr, 0, sizeof(m_tGetAddr));
		m_wGetIndex = TP_UMS_MAX_CALLNUM;
	}

	BOOL32 IsValid()
	{
		return m_tSelView.IsValid();
	}
	
	void SetView(TTPSelViewReq& tView)
	{
		memcpy(&m_tSelView, &tView, sizeof(m_tSelView));
	}

}TSelViewMgr;

typedef struct tagTEpViewInfo
{
	u16			m_wEpID;
	TSelViewMgr	m_atViewMgr[TP_MAX_STREAMNUM];

	tagTEpViewInfo()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atViewMgr[wIndex].Clear();
		}
		m_wEpID = TP_INVALID_INDEX;
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atViewMgr[wIndex].Clear();
		}
	}

	BOOL32 IsHavView()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			if ( m_atViewMgr[wIndex].IsValid() )
			{
				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL32 Valid()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}

	BOOL32 IsNoGetVidView(u16 wScreenIndex)
	{// �����᳡ѡ��һ��������ʱ�������᳡������������������
		if (m_atViewMgr[wScreenIndex].m_tSelView.m_wScreenIndx < TP_MAX_STREAMNUM && 
			m_atViewMgr[wScreenIndex].m_wGetIndex >= TP_UMS_MAX_CALLNUM)
		{
			return TRUE;
		}
		return FALSE;
	}

}TEpViewInfo;

class CUmsConfInst;
class CSelView  : public CTpHandler
{
public:
	CSelView(CUmsConfInst* pcInst):CTpHandler(pcInst) {  }
	~CSelView() { InstClear(); }
	
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	void Show();

	//����ѡ��
	void OnSelViewUmc(CTpMsg *const ptMsg);
	void OnSelViewCnc(CTpMsg *const ptMsg);

	//������ ѡ����Ӧ
	void OnSelViewCasecadeInd(CTpMsg *const ptMsg);

	//�ϼ�UMCȡ������ѡ��
	void OnUnSelAllView(CTpMsg *const ptMsg);

	//ѡ��״̬֪ͨ
	void OnSelViewNtfy(CTpMsg *const ptMsg);

	void HungUpNode(TCallNode* ptNode);

	void AskKeyFrame(u16 wEpID, u16 wScreenIndx);

	void StopConf();
	void AdjustCnsSpeaker(TCallNode* ptNode); 

	void NtfyAllSelInfoToUI(EmTpOprType emType, TLogUser* ptUser = NULL);

	void GetSelSrcAddr( u16 wEpID, u16 wScreenIndx, TTPMediaTransAddr& tAddr, u32& dwEqpNode );
	s8*	GetSelObj(u16 wEpID, u16 wScreenIndx, u16& wVidNum);

	void BrdVmpCB(TBrdVmpRes* ptRes, EmBrdVmpCBOprType emOpr);
	void AdjustGetVidFailed(CUmsConfInst* pcInst, u16 wGetVideIndex, EmGetVidRet emRet);
protected:
	EmViewRetReason SelView(TTPSelViewReq& tView, TEpViewInfo* ptOutInfo);
	EmViewRetReason UnSelView(TTPSelViewReq& tView, BOOL32 bNtfy = TRUE);
	EmViewRetReason ConvertGetVidReason(const EmGetVidRes emGetVid);
	void NtfySelInfoToUI(TEpViewInfo* ptView);
	
protected:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	friend class CNetPortMgr;

	TEpViewInfo* FindIdle();
	TEpViewInfo* FindByEP(u16 wEpID);
	TEpViewInfo* FindByBasRes(CScreenBasRes* ptBasRes);

	void ReleaseItor();

	void InstClear();

	// Ϊѡ���Ļ᳡�ָ��ֱ���
	BOOL32   RestoreAdjustedResForSelEp(u16 wSelTargetEp, u16 wScreenIndex);
	// ѡ������������Ҫ��ͼ��ĵ����ۻ᳡ ���ֱ���
    BOOL32   AdjustResForUnSelEp(u16 wSelTargetEp, u16 wScreenIndex);	

	
private:

	TEpViewInfo m_atSelView[UMS_MAX_SELVIEW_NUM];
};

#endif