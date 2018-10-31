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

	// umc会控消息
	void OnStartDualCmdFormUmc( CTpMsg *const ptMsg );
	void OnStopDualCmdFormUmc( CTpMsg *const ptMsg );

	//协议栈过来的消息
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

	//检查除请求双流源外的其它会场双流接收通道是否打开，未打开，打开
	void	CheckEpDualRcv(u16 wExceptID, u16 wExceptID2 = TP_INVALID_INDEX, u16 wExceptID3 = TP_INVALID_INDEX);

	// 由讨论状态切为普通状态的时候，双流的声音可能需要调整（跟讨论共用一个混音资源）
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

	u16					m_wNextDual;		//双流源CNS回应后，保存该双流源ID，
											//收到dualchanCnnt后清掉
											//收到OpenchanDisCnnt后，如果该结点和m_wNextDual一直，说明是双流源打开双流失败，提示界面
    u8                  m_byDualType;       //双流源类型（cns、非cns)
	u16					m_wCurDual;			//当前双流源
	u16					m_wReqDual;			//当前正在请求的双流源
	u16					m_wChairReq;         //主席主动指定会场发送双流
	
	TTPMediaTransAddr   m_tVidRcvAddr;		//接收CNS或者下级传过来的码流， 本地向远端请求重传的地址	
	TTPMediaTransAddr   m_tAudRcvAddr;		
	TUmsNetBuf			m_tVidNetBuf;		//NETBUF		

	CDsListInfo			m_tDualDsEpToUms;	//双流源到UMS的交换

	TTPAlias			m_tDualAlias;		//双流源的别名，上级通知下级
	CDsListInfo			m_tToUpUms;
};

#endif // _h_dualmgr_h__
