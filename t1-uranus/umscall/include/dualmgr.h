#ifndef _h_dualmgr_h__
#define _h_dualmgr_h__

#include "callinnerstruct.h"
#include "tphandle.h"

class TCapNode;
class CUmsConfInst;
class CDualMgr : public CTpHandler
{
public:
	CDualMgr(CUmsConfInst* pcInst);
	~CDualMgr();
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	
	BOOL32 HandlerFromUmc( CTpMsg *const ptMsg );

	virtual BOOL32 Create();
	BOOL32 StartConf();
	void StopConf();
	
	void Show();
	void ShowDs();
	void ShowPortRes();

	u16 InitPort(u16 wStartPort);
	void ResetMediaIp(const TEqpRes& tConfDs);
	void ResetNbIp(const TEqpRes& tConfNb);

	BOOL32 IsStart()	{return m_bStart;}
	u16 GetDualID()		{ return m_wCurDual; }
	void StopDual();
		
	void OnChanConnect(TCapNode* ptNode);
	void HungUpNode(TCallNode* ptNode, BOOL32 bDelete);

public:
	TTPTransAddr	GetNetBufRtcpAddr(){ return m_tVidNetBuf.m_tRcvRtcpAddr; }
	BOOL32 AskFrameForSeeDual(TUmsVidFormat& tVidFormat, BOOL32 bReqBySys = TRUE, BOOL32 bReqToScrEp = FALSE);
	void   AskFrameToDualSrcEp();
	
public:
  	void OnReqDualStreamCmd(CTpMsg *const ptMsg);
  	void OnReqDualStreamInd(CTpMsg *const ptMsg);
	void OnStopSendDual(CTpMsg *const ptMsg);
	void OnStopRcvDual(CTpMsg *const ptMsg);
	void OnOpenCasecadeDualChanCmd(CTpMsg *const ptMsg);
	void OnOpenCascadeDualChanInd(CTpMsg *const ptMsg);
	void OnAskKeyFrame(CTpMsg *const ptMsg);
	void OnSrcNameInd(CTpMsg *const ptMsg);
	void OnStartRcvDaul(CTpMsg *const ptMsg);

	void OnStartDualCmd( CTpMsg *const ptMsg );
	void OnStopDualCmd( CTpMsg *const ptMsg );

	void OnStartDualCmdForUmcCnc(u16 wEpId);
	void OnStopDualCmdForUmcCnc();

	// umc�����Ϣ
	void OnStartDualCmdFormUmc( CTpMsg *const ptMsg );
	void OnStopDualCmdFormUmc( CTpMsg *const ptMsg );

	//Э��ջ��������Ϣ
public:
	void OnDualIncoming(CTpMsg *const ptMsg);
	void OnDualChanConnect(CTpMsg *const ptMsg);
	void OnDualChanDisConnect(CTpMsg *const ptMsg);
	
	void StopEpSndDual(TCapNode* ptNode, EmTPChannelReason emReason = emTPChannelDisconnectNormal);
	
	void AdjustDualMix();
	void AdjustDualMixForRollCall();
    void AdjustDualMixForConfAudMix();
	void ChangeSpeakerForVRS();

#ifdef _USE_XMPUEQP_
	void DualXmpuAudMixCB(u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData);
#else
	void DualAudMixCB(TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo);
#endif

public:

	//��������˫��Դ��������᳡˫������ͨ���Ƿ�򿪣�δ�򿪣���
	void	CheckEpDualRcv(u16 wExceptID, u16 wExceptID2 = TP_INVALID_INDEX, u16 wExceptID3 = TP_INVALID_INDEX);

	// ������״̬��Ϊ��ͨ״̬��ʱ��˫��������������Ҫ�����������۹���һ��������Դ��
	void  AdjustDualMediaForDiscuss();
private:
	void AjustAllDualMedia(BOOL32 bStart = TRUE);
	void MakeDualCap(TCapNode* ptNode, BOOL32 bSnd, BOOL32 bRes = TRUE);

	void NotifyAllEpStartRcvDual(u16 wExceptID);
	void NotifyAllEpSrcDualName(u16 wExceptID);
	void DualEpNotify();
	BOOL32 GetDualSrcName(TTPAlias& tAlias);
	
	void CloseSendChan(u16 wDualID);
private:
	void ChangeDualEpProc(u16 wExpeceID = TP_INVALID_INDEX);

	void ExitDualModel(u16 wExceptID);

	BOOL32 IsDualCns() {return 1 == m_byDualType;}
	void  SetDualCns(BOOL32 bIsCns) {m_byDualType = bIsCns?1:0;}
	void  ClearDualType() {m_byDualType = 0;}
		
private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	
	friend class CNetPortMgr;
	friend class CDsStrategyToNodeForDual;
protected:
	BOOL32				m_bStart;	
	TFastUpdateStatis	m_tKeyFrameStatis;

	u16					m_wNextDual;		//˫��ԴCNS��Ӧ�󣬱����˫��ԴID��
											//�յ�dualchanCnnt�����
											//�յ�OpenchanDisCnnt������ý���m_wNextDualһֱ��˵����˫��Դ��˫��ʧ�ܣ���ʾ����
    u8                  m_byDualType;       //˫��Դ���ͣ�cns����cns)
	u16					m_wCurDual;			//��ǰ˫��Դ
	u16					m_wReqDual;			//��ǰ���������˫��Դ
	u16					m_wChairReq;         //��ϯ����ָ���᳡����˫��
	
	TTPMediaTransAddr   m_tVidRcvAddr;		//����CNS�����¼��������������� ������Զ�������ش��ĵ�ַ	
	TTPMediaTransAddr   m_tAudRcvAddr;		
	TUmsNetBuf			m_tVidNetBuf;		//NETBUF		

	CDsListInfo			m_tDualDsEpToUms;	//˫��Դ��UMS�Ľ���

	TTPAlias			m_tDualAlias;		//˫��Դ�ı������ϼ�֪ͨ�¼�
	CDsListInfo			m_tToUpUms;
};

#endif // _h_dualmgr_h__
