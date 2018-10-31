#ifndef _h_umscallinst_h__
#define _h_umscallinst_h__

#include "umsobject.h"
#include "tpvector.h"
#include "tptime.h"
#include "callinnerstruct.h"
#include "umsinnerrecstruct.h"
#include "bandwidth.h"
#include "querytmpalias.h"

class CCallNodeAddrMgr;
class CAudMixAddrMgr;
class CUmsRegMgr;
class CNetPortMgr;
class CCallNodeMgr;
class CTvWallMgr;
class CCallMgr;
class TCapNode;
class CDualMgr;
class CUmsVmp;
class CUmsBas;
class CUmsPollMgr;
class CUmsEapu;
class CNodeFsmMgr;
class CUmsDiscussMgr;
class CVmpServiceHandler;
class CSelView;
class CGetVidAudEx;
class CPollMgr;
class CTpTimerMgr;
class CDataConfHandler;
class CUmsRollCallMgr;
class CPutAud;
class CUmsAudMixMgr;
class CGetConfVidAudMgr;
class CUmsMcuMgr;

void VirSingleVmpCB(const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, void* param, u16 wTmp1);
void VirSingleBasCB(u32 dwType, void* param1, void* param2);
void VirSingleMixCB(u32 dwType, void* param1, void* param2);


typedef struct tagTSpeakMediaFmt
{
	TUmsVidFormat m_SpeakerSndVidFmt;
    TUmsAudFormat m_SpeakerSndAudFmt;

    tagTSpeakMediaFmt()
	{
		Clear();
	}

	void Clear()
	{
        m_SpeakerSndVidFmt.m_emFormat = emTPVEnd;
		m_SpeakerSndAudFmt.m_emFormat  = emTPAEnd;
	}

	void SetSpeakerSndVidFmt(TUmsVidFormat& tSpeakerSndVidFmt)
	{
         m_SpeakerSndVidFmt = tSpeakerSndVidFmt;
	}

    void GetSpeakerSndVidFmt(TUmsVidFormat& tSpeakerSndVidFmt)
	{
         tSpeakerSndVidFmt = m_SpeakerSndVidFmt;
	}

	void SetSpeakerSndAudFmt(TUmsAudFormat& tSpeakerSndAudFmt)
	{
		m_SpeakerSndAudFmt = tSpeakerSndAudFmt;
	}

	void GetSpeakerSndAudFmt(TUmsAudFormat& tSpeakerSndAudFmt)
	{
		tSpeakerSndAudFmt = m_SpeakerSndAudFmt;
	}

	BOOL32 IsSpeakMediaFmtValid()
	{
		return (m_SpeakerSndVidFmt.m_emFormat != emTPVEnd && m_SpeakerSndAudFmt.m_emFormat  != emTPAEnd);
	}
	
}TSpeakMediaFmt;




class CUmsConfInst :  public CUmsObject
{
public:
	enum ENInstState
	{
		inst_idle,
		inst_run,
	};
public:
    CUmsConfInst();
	~CUmsConfInst();
	
	u16 NotifyMsgToServiceForUI(u16 wEvent, void* body, u16 bodyLen, TLogUser* ptUser=NULL);
	u16 NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen);

	void NotifyConfCtrlMsgToCns( u16 wEvent, u16 wEpID, void* body, u16 bodyLen );
	void NotifyConfCtrlMsgToAllCns( u16 wEvent, void* body, u16 bodyLen, u16 wExceptEpID = TP_INVALID_INDEX );
	void NotifyConfInfoToCnsOnChanConnect( TCallNode* ptNode );
	void NotifyAllCnsListToCns( TCallNode* ptNode );
	void NotifyApplySpeakerToUI();
	
	void NotifyChairCapToLowUms(u16 wDstEpID = TP_INVALID_INDEX);

	void SetPollTimeInterval(u16 wTime);
	TCallNode* GetNode(u16 wEpID);
	TChairCap GetChairCap();
	void GetConfNtfyInfo(TTPConfInfoNtfy& tInfo, TChairConfInfo& tChair);

	TUmsConfBase& GetConfBase()	{ return m_tConfBaseInfo; }

	TTPEncrypt&   GetConfEncryptInfo() { return m_tConfBaseInfo.m_tEncrypt;}

	TEqpRes&	GetNbEqp()			{ return m_tEqpConfNb; }
	TChairInfoTr&	GetSuperChairCap()	{ return m_tSuperChairCap; }
	TTPConfInfoNtfy& GetConfInfo()		{ return m_tSuperInfo; }
	BOOL32			IsChairConf();
	u16				curSpeakerID()const;
	u16				oldSpeakerID()const;
	u16				chairID()const;
	void			SetCurSpeaker(CNodeBase* ptNode);
	void			SetOldSpeaker(CNodeBase* ptNode);
	void			SetChairID(CNodeBase* ptNode);

	CUmsDiscussMgr*     GetUmsDiscuss()         { return m_pcUmsDiscuss; }

    CPutAud* GetPutAudMgr()  {return m_pcPutAudMgr;}

	CCallNodeMgr*	GetNodeMgr()		{ return m_pcNodeMgr; }
	CUmsAudMixMgr*    GetAudMix()		{ return m_pcAudMix; }
	CUmsRollCallMgr* GetRollCallMgr()    { return m_pcRollCallMgr;}
	CGetConfVidAudMgr* GetConfVidAudMgr() {return m_tGetConfVidAudMgr;}
	CUmsMcuMgr*		GetMcuMgr()			{return m_pcMcuMgr;}
	CUmsEapu*       GetEapu()		    { return m_pcEapu; }
	CDualMgr*		GetDualMgr()		{ return m_pcDual;	}

	CCallMgr*		GetCallMgr()		{ return m_pcCallMgr; }
	CUmsBas*		GetBas()			{ return m_pcBas; }
	CUmsVmp*		GetVmp()			{ return m_pcVmp; }
	CSelView*		GetSelMgr()			{ return m_pcSelView; }
	CPollMgr*		GetPollMgr()		{ return m_pcPollMgr; }
	CNodeFsmMgr*	GetNodeFsm()		{ return m_pcNodeFsm; }
	TEqpRes&		GetConfEqpDs()		{ return m_tEqpConfDs; }
	CVirSpeaker&	GetSpeaker()		{ return m_cSpeaker;}
	TSpeakMediaFmt& GetSpeakMediaFmt()  { return m_tSpeakerMediaFmt;}
	TTPMediaTransAddr& GetSingleVidDec()			{ return m_cSpeaker.m_tSingleVidDec;}
	TTPMediaTransAddr& GetSpeakerVidDec(u16 wIndex){ return m_cSpeaker.m_atVidDec[wIndex];}
	TTPMediaTransAddr& GetSpeakerAudDec(u16 wIndex){ return m_cSpeaker.m_atAudDec[wIndex];}
	TTPMediaTransAddr& GetSpeakerAudMix()		   { return m_cSpeaker.m_tAudMixDec;}
	TUmsNetBuf&     GetNetBufParam(u16 wScreenIndex) { return m_cSpeaker.m_atVidBuf[wScreenIndex]; }
	TUmsNetBuf&     GetSingleNetBuf(){return m_cSpeaker.m_tSingleVidBuf;}
	CBandwidth&		GetBandWidth() { return m_cBw; }

	static CLocalPollChanAddrList*  GetPollAddrList() { return &m_cLocPollAddrMgr; }
	static CLocalRollChanAddrList*  GetRollAddrList() { return &m_cLocRollAddrMgr; }
	static CPutAudChanAddrList*  GetPutAudAddrList()  { return &m_cPutAudAddrMgr;  }
	static CEapuChanAddrList*    GetEapuAddrList()    { return &m_cEapuAddrMgr;    }
	static CAddrList*		GetAddrList()		{ return &m_cAddrList; }
	static CDsList*			GetDsList()			{ return m_pcCallDs; }

	void AskKeyByScreen(u16 wEpID, u16 wScreenIndex, EmAskKeyType emType, u32 dwRervse1 = 0, u32 dwRervse2 = 0, BOOL32 bReqBySys = TRUE);
	void AskKeyByEpID(u16 wEpID, EmAskKeyType emType, u32 dwRervse1 = 0, u32 dwRervse2 = 0, BOOL32 bReqBySys = TRUE);

	BOOL32			IsPriNeedBas();
	BOOL32			IsDualNeedBas();
	BOOL32			IsAudNeedBas() { return m_tConfBaseInfo.m_wAudFmtNum > 1; }
	BOOL32          IsVidNeedBas()  { return m_tConfBaseInfo.m_wMainNum > 1; }

	BOOL32          IsAssignBasReady();

public:
	static void		GetVidFailedCB(CUmsConfInst* pcConf, u16 wIndex, EmGetVidType emType, EmGetVidRet emRet);
	void			SndTimeOut(	u16 wIndex);

	void			CheckFrameDis(u32 dwDsIP, u16 wNewPort, u16 wOldPort, TTPTransAddr& tDst);

	BOOL32			TryAssignVirSingleBas();
	void			TryAdjustVirSingleBas();
	void			TryReleaseVirSingleBas();

	u32				GetNodeFromMediaIp(const u32 dwIp);
	BOOL32			IsMtIp(const u32 dwIp);

protected:
	virtual void MessageProc( CTpMsg *const ptMsg);	
	virtual void DaemonMessageProc(CTpMsg *const ptMsg,CApp* pcApp);

	//daemon
protected:
	virtual BOOL32 DaemonObjectInit(u32 wParam, u32 lParam);
	virtual void DaemonObjectExit(void);
	void DaemonInitCfg(CTpMsg *const ptMsg,CApp* pcApp);
	void DaemonInitPort(CApp* pcApp);
	u16 DaemonInitLocalAddr(u16 wStartPort);
	u16 DaemonInitCascadeChairAddr(u16 wStartPort);
	u16 DaemonInitPollAddr(u16 wStartPort);
	u16 DaemonInitRollAddr(u16 wStartPort);
	u16 DaemonInitPutAudAddr(u16 wStartPort);
	u16 DaemonInitEapuAddr(u16 wStartPort);


	void DaemonConfAdapterReg(CTpMsg *const ptMsg,CApp* pcApp);		
	void DaemonConfAdapterUnReg(CTpMsg *const ptMsg,CApp* pcApp);		
	void DaemonConfIncomingFromService(CTpMsg *const ptMsg,CApp* pcApp);	

	void DaemonConfMediaReg(CTpMsg *const ptMsg,CApp* pcApp);
	void DaemonConfMediaUnReg(CTpMsg *const ptMsg,CApp* pcApp);

	void DaemonConfAudMixUnReg( CTpMsg *const ptMsg, CApp* pcApp );
	void DaemonConfAudMixReg( CTpMsg *const ptMsg, CApp* pcApp );
	
	void DaemonConfVmpProc( CTpMsg *const ptMsg, CApp* pcApp );
	void DaemonConfBasMsgProc( CTpMsg *const ptMsg, CApp* pcApp );

	void DaemonConfMpcInfo( CTpMsg *const ptMsg, CApp* pcApp );

	void DaemonConfInvalidAppHandleProc(CTpMsg *const ptMsg,CApp* pcApp);
	BOOL32 ConfInvalidAppHandleProc(CTpMsg *ptMsg);

protected:
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit(void);
	u16 InitPort(u16 wStartPort);
	void ResetMediaIp(const TEqpRes& tConfDs);
	void ResetNbIp(const TEqpRes& tConfNb);

	void AdapterQuit(TEqpRes& tEqp);
	void AdapterReg();

	void MediaReg(TEqpRes& tEqp);
	void MediaUnReg(TEqpRes& tEqp);

	EmCnsCallReason OnConfUmsCall(const TUmsHandle& tHandle, TUmsCallInfo& tCaller, TConfTemplateLocal& tConfTemp);
	EmCnsCallReason OnConfCnsCall(const TUmsHandle& tHandle, TUmsCallInfo& tCaller, TConfTemplateLocal* ptConfTemp);
	EmCnsCallReason OnCnsCallExistConf(const TUmsHandle& tInHandle, TUmsCallInfo& tCaller);

	//��Э��ջ��������Ϣ
	void OnCallConnect(CTpMsg *const ptMsg);
	void OnCallDisConnect(CTpMsg *const ptMsg, BOOL32 bFromStack);
	void OnChanConnect(CTpMsg *const ptMsg);
	void OnChanDisConnect(CTpMsg *const ptMsg);
	void OnOpenCascadeChairChan(CTpMsg *const ptMsg);
	void OnOpenCascadeChairChanAck(CTpMsg *const ptMsg);	
	void OnConfYouAreSeeing(CTpMsg *const ptMsg);
	void OnConfAskKeyFrame(CTpMsg *const ptMsg);
	void OnAdjustInnerSpeakFromCns(CTpMsg *const ptMsg);
	void OnConfCnsSpeakerCascadNotify(CTpMsg *const ptMsg);
	void OnConfMuteRemoteEpCmd(CTpMsg *const ptMsg);
	void OnConfMuteRemoteEpInd(CTpMsg *const ptMsg);
	void OnConfQuietRemoteEpCmd(CTpMsg *const ptMsg);
	void OnConfQuietRemoteEpInd(CTpMsg *const ptMsg);
	void OnConfTvMonitorCmd(CTpMsg *const ptMsg);
	void OnConfTvMonitorInd(CTpMsg *const ptMsg);
	void OnConfTvMonitorStop(CTpMsg *const ptMsg);
	void OnConfAskKeyToScreen(CTpMsg *const ptMsg);
	void OnConfChairInfo(CTpMsg *const ptMsg);
	void OnConfChairCapNotify(CTpMsg *const ptMsg);
	void OnConfFlowCtrl(CTpMsg *const ptMsg);
	void OnConfAdjustFrameRate(CTpMsg *const ptMsg);
	void OnConfAdjustVidRes(CTpMsg *const ptMsg);
	void OnResetFastUpdate(CTpMsg* const ptMsg);

	void QuietRemoteEpInd(TUmsHandle& tHandle, TQuietRmtEpInd* ptQuiet);
	void MuteRemoteEpInd(TUmsHandle& tHandle, TMuteRmtEpInd* ptMute);
	
	void OnAdjustCnsSpeakerIndx( CTpMsg *const ptMsg );
	void OnChangeSpeaker( CTpMsg *const ptMsg );
	void OnMuteEp( CTpMsg *const ptMsg );
	void OnQuietEp( CTpMsg *const ptMsg );
	void OnHungConf( CTpMsg *const ptMsg );
	void OnBrdCastMsg( CTpMsg *const ptMsg );

	// mcu����
	void OnMcuCasecadeChanConnected( CTpMsg *const ptMsg );
	void OnMcuCasecadeRegUnRegReq( CTpMsg *const ptMsg );
	void OnMcuCasecadeRegUnRegRsp( CTpMsg *const ptMsg );
	void OnMcuCasecadeRosterNotify( CTpMsg *const ptMsg );
	void OnMcuCasecadePartListReqRsp( CTpMsg *const ptMsg );
	void OnMcuCasecadePartStateNty( CTpMsg *const ptMsg );
	void OnMcuCasecadeDelPartNty( CTpMsg *const ptMsg );
	void OnMcuCasecadeSpyBWNty(CTpMsg *const ptMsg);
	void OnChangeMcuEpSpeakerFromCns(TUmsHandle tHandle, TConfEpID* ptConfEp);
	void OnChangeMcuEpSpeakerFromUmc(TLogUser* ptLogUser, TConfEpID* ptConfEp);
	void OnMcuCasecadeSetInRsp( CTpMsg *const ptMsg);
	void AdjustNewSpeakerToAllMcuNode();
	
	// fecc Զң
	void OnFeccChannedConnnected( CTpMsg *const ptMsg);
	void OnFeccCamControlFromUmc(CTpMsg* const ptMsg);
	void OnFeccPrePosReqFromUmc(CTpMsg* const ptMsg);
	void OnFeccSelVidFromUmc(CTpMsg* const ptMsg);
	void OnFeccReqFromCns(CTpMsg* const ptMsg);
	BOOL32 FeccReqFromUmcCns(TFeccInfo& tInfo, u32& dwReason );
	// �᳡��ƵԴ��Ϣ֪ͨ
	void OnVidSourceInfoFromCns(CTpMsg* const ptMsg);
	void OnEpStatusNty(CTpMsg* const ptMsg);
	void VidFeccInfoNty(TUmsHandle& tHandle,  u8 byVidNo, BOOL32 bAllowFecc);
	void NotifyVidFeccInfoToUI(u16 wEpId);
	void NotifyVidFeccInfoToChair(TConfVidFeccInfo& tVidFeccList);

	void OnEpKedaManuProduckNotify(CTpMsg *const ptMsg);
	
	// add by gaoyong
	BOOL32 OnMuteEpForUmcCnc(TConfEpID* ptConfEp, BOOL32 bIsMute);
	BOOL32 OnQuietEpForUmcCnc(TConfEpID* ptConfEp, BOOL32 bIsQuiet);

	//add by caokeyu
	BOOL32 OnAllMuteEpForUmcCnc(TConfEpID* ptConfEp, BOOL32 bIsMute);
	BOOL32 OnAllQuietEpForUmcCnc(TConfEpID* ptConfEp, BOOL32 bIsQuiet); 

	//��SERVICE��������Ϣ����
	void EventUserLogin(CTpMsg *const ptMsg);
	EmCnsCallReason EventStartConf(u8* pDataBuf, u16 wDataSize, TCapNode* ptCaller,  BOOL32 bIsNeedDelayCall);
	EmCnsCallReason EventStartConfFromXeqp(TConfTemplateLocal* pConfTmp, TCapNode* ptCaller,  BOOL32 bIsNeedDelayCall);
	void EventOnCallTime();
	void EventHungConf(CTpMsg *const ptMsg);		
	void EventOnProtectTime();

	// umc��ع��� add by gaoyong
	void OnMuteEpFromUmc( CTpMsg *const ptMsg );
	void OnQuietEpFromUmc( CTpMsg *const ptMsg );
	void OnChangeSpeakerFromUmc( CTpMsg *const ptMsg);
	
	//323MT��������Ϣ
	void OnTerListReq( CTpMsg *const ptMsg );

	//��ת����������Ϣ
	void OnIframeBySrcNty(CTpMsg *const ptMsg);

 
public:
	
	BOOL32 GetChairSndCap(u16 wSpeaker, TSpeakerCapTr& tCapSet);
	BOOL32 GetSpeakSndCap(u16 wSpeaker, TSpeakerCapTr& tCapSet);
private:
	//��������δ���߻᳡
	void CallAllLocalNode();

	//�������Ϣ���͸�����CNS
	void SendNodeInfoToAllCNS( TConfCnsInfo* ptList );
	//�᳡�л�������ϯ
	void AdjustCnsInnerSpeak(BOOL32 bMix, u16 wNewSpeakerIndex, u16 wExcEpID = TP_INVALID_INDEX);
//	void AdjustCnsInnerSpeakerByMix( TCallNode* ptNode, u16 wNewSpeakerIndex );

	void AdjustNewSpeakerToAllNode(u16 wEpID = TP_INVALID_INDEX, BOOL32 bUpdate = FALSE);

	void DestroyUmsToAllNode();	
	void ChangeSpeaker(u16 wNewSpeaker, const TSpeakerCapTr* ptCapSet);	
	void DestroyMediaOnCallerOnline();

	void SetSpeakerCheckFrame(TCallNode* ptNewSpeaker, TCallNode* ptOldSpeaker);
	
	void EventEpNodeTimerCheck();
	void AdjustNodeChanOn(TCapNode* ptNode);


	//�����ͨ���򿪻��߹ر�ʱ
	void AdjustCapOnChanOn(TUmsHandle& tHandle, TCapNode* ptNode);
	
	//�Ҷ�һ������
	void HungUp(u16 wEpID, BOOL32 bDelete = TRUE, BOOL32 bToStack = TRUE, EmCnsCallReason emRes = EmCnsCallReason_hungup);	
	void StopMediaTrans(TCallNode* ptNode, BOOL32 bDelete, EmCnsCallReason emRes = EmCnsCallReason_hungup);
	void AjustSpeakerOnNodeDisConn(TCallNode* ptNode);

	void HungUpFromLow(TCallNode* ptNode, EmCnsCallReason emRes);
	void HungUpMcuEpFromLow(TCallNode* ptNode, EmCnsCallReason emRes);

	void CreateMediaToVRS_2S(TCapNode* ptNode);

	// Xmpu vmp manager msg
	void OnXmpuVmpConnect(CTpMsg *const ptMsg);
	void OnXmpuVmpDisConnect(CTpMsg *const ptMsg);
	void OnXmpuVmpMdyNty(CTpMsg *const ptMsg);
	void OnXmpuAskKeyReq(CTpMsg *const ptMsg);
	void OnXmpuInitMeetingNty(CTpMsg *const ptMsg);
	void OnXmpuRefreshVmp(CTpMsg *const ptMsg);

protected:
	BOOL32 IsValidKeyFrameReq(const TFastUpdateStatis& tStatis);
		
protected:
	//��ӡ
	virtual void InstanceDump(u32=0);
	virtual void DaemonInstanceDump(u32=0);
	void ShowCallInfo();
	void ShowCallPort();
	void ShowCallDs();
	void ShowCallPoll();
	void ShowDiscuss();
	void ShowEapu();
	void ShowAudDual();
	void ShowAllPort();
	void ShowVmp();
	void ShowTv();
	void ShowBas();
	void ShowResFrm();
	void ShowSelView();

	static void ShowConfMgr(); 
	
	void DaemonShowPortRes();
	void ShowPortRes();
    
	void ShowRollCall();
	void ShowAudMix();
	void ShowGetStream();
	void ShowMcuMgr();


protected:
	void StopConf();
	void NotifySelfHungup(u32 dwReason = 0);
	void SelfHungupImmediately(u32 dwReason = 0);
	void NotifyReasonToUI( u32 dwType, u32 dwReason, u16 wDstEpID = TP_INVALID_INDEX, 
									u32 dwReserve1 = 0, u32 dwReserve2 = 0, u32 dwReserve3 = 0);

	TCallNode* GetSonNode(const TUmsHandle& tHandle, const TEpKey& tKey);

	//������Ҫ��UI���µĽ�㣬��һ��ʱ����ͳһ��UI����
	void UpdateNodeInfo(EmTpOprType emOpr, u16 wEpID);
	void NotifyUpdateNodeToUi();

	// �˺���Ŀ�ģ����Э�̳�����ͨ��ֻ��1·���Ҳ����м�·����ҵ����·ͨ��Ų���м�·
	void CheckMidChanInfo(TCapNode* ptNode, TUmsNodeCapset& tNodeCapInfo);


protected:
	void OnDaemonMediaKeyNty(CTpMsg *const ptMsg,  CApp* pcApp);
    void OnDaemonMediaKeyFail(CTpMsg *const ptMsg,  CApp* pcApp);
	void SetQtEncryptInfo(u8* pData, u16 wDataSize );
	void DaemonProQueryAlias(CTpMsg *const ptMsg);
	void DaemonProQtMsg(CTpMsg *const ptMsg,  CApp* pcApp);


	void OnMediaKeyFail(CTpMsg* const ptMsg);
	void OnMediaKeyDstMTNty(CTpMsg* const ptMsg);
    void OnMediaKeyNty(CTpMsg* const ptMsg);
	BOOL32 ProQtMsg(CTpMsg *const ptMsg);


public:
	static CUmsRegMgr* GetRegMgr()	{	return m_pcRegMgr; }
	static u32	GetOnlineNum()		{	return m_dwOnlineChanNum;	}
	static u32	GetLicenseNum()		{	return m_dwLicenseChanNum;	}
	static void	SetOnlineNum(u32 dwNum)	{	m_dwOnlineChanNum = dwNum;	}
	static void SetLicenseNum(u32 dwNum) {	m_dwLicenseChanNum = dwNum;	}
	static void SetDelayTime(u32 dwTime) {m_dwDelayTime = dwTime;}
	static u32 GetDelayTime() { return m_dwDelayTime;}
	static CVmpServiceHandler* GetVmpServiceHandle() { return m_pcVmpTpHandle; }
	static CGetVidAudEx* GetVidAudEx() { return m_pcGetVidEx;}
protected:
	static CLocalAudMixAddrList	m_clocMixAddrMgr;			//���������᳡�����ĵ�ַ
	static CLocalDualAddrList	m_clocDualAddrMgr;			//�᳡˫����ַ
	static CLocalChanAddrList	m_cLocChanAddrMgr;			//�᳡ͨ����ַ
	static CLocalSmallChanAddrList	m_cLocSmallChanAddrMgr;	//�᳡ͨ����ַ С����
	static CCascadeChairAddrList m_cCascadeChairAddrMgr;	//������ͨ����ַ

	static CLocalPollChanAddrList m_cLocPollAddrMgr;       //��ѯͨ����ַ
	static CLocalRollChanAddrList m_cLocRollAddrMgr;       //����ͨ����ַ
	static CPutAudChanAddrList    m_cPutAudAddrMgr;         //���¼���Ƶͨ����ַ
	static CEapuChanAddrList      m_cEapuAddrMgr;           //������ͨ����ַ          


	static CAddrList		m_cAddrList;//rtp rtcp��ַ�� ����̬ҵ��ʹ�ã����磬�������ȡ�������Ƶ�´���

	static CDsList*			m_pcCallDs;
	static CTvWallMgr*		m_pcTvWallMgr;
	static CUmsRegMgr*		m_pcRegMgr;
	static TUmsCallCfg		m_tCallCfg;
	static CGetVidAudEx*    m_pcGetVidEx;
	static BOOL32			m_bMpcReged;			//�Ƿ���MPCע��
	static u32				m_dwOnlineChanNum;		//��������
	static u32				m_dwLicenseChanNum;		//��Ȩ�Ŀɺ�������
	static CVmpServiceHandler* m_pcVmpTpHandle;
	static CTpTimerMgr*    m_pcTimerMgr;   //��ʱ��
	static u32             m_dwDelayTime;

	static CQueryAliasMgr  m_QueryAliasMgr;

protected:
	friend class CNetPortMgr;
	friend class CCallNodeMgr;
	friend class CChairEpMgr;
	friend class CCallMgr;
	friend class CDualMgr;
	friend class CTvWallMgr;
	friend class CGetVidMgr;
	friend class CUmsVmp;
	friend class CUmsBas;
	friend class CUmsEapu;
	friend class CUmsPollMgr;
	friend class CRecorderMgr;
	friend class CUmsDiscussMgr;
	friend class CSelView;
	friend class CPollMgr;
	friend class CUmsRollCallMgr;
	friend class CUmsAudMixMgr;
	friend class CGetConfVidAudMgr;
	friend class CUmsMcuMgr;

	
	u16				m_wConfTemplateID;
	BOOL32			m_bIsNeedKeyProtectOnStart;
	BOOL32			m_bIsQuiting;
	
	TChairInfoTr	m_tSuperChairCap;		//�ϼ���ϯ��Ϣ ���¼�UMS�����ݸ�ֵȡ��ϯ������ϯ����
	TTPConfInfoNtfy	m_tSuperInfo;			//�ϼ�������Ϣ
	TUmsConfBase	m_tConfBaseInfo;		//���������Ϣ
	
	TRefrenUiNodeList	m_tUpdateNodeList;	//��Ҫ��UI���µ�

	TEqpRes			m_atDsEqp[UMS_CONF_MAX_DS_NUM];
	TEqpRes			m_tEqpConfDs;			//�����ת����
	TEqpRes			m_tEqpConfNb;			//������ش���
	
	BOOL32			m_abOnIFrameCheck[TP_MAX_STREAMNUM];
	BOOL32			m_bOnSingleIframeCheck;

	CVirSpeaker		m_cSpeaker;
	CVirChair		m_cChair;
    TSpeakMediaFmt  m_tSpeakerMediaFmt;
	
	CBandwidth		m_cBw;

	TInComingInfo	m_tTemp;

	CPutAud*        m_pcPutAudMgr;   //���¼�����Ƶ

	CCallNodeMgr*	m_pcNodeMgr;

	CUmsEapu*		m_pcEapu;
	CUmsBas*		m_pcBas;
	CUmsVmp*		m_pcVmp;
	CDualMgr*		m_pcDual;
	CNodeFsmMgr*	m_pcNodeFsm;
	CCallMgr*		m_pcCallMgr;	//��ǰ���й����ϼ������¼�
	CUmsDiscussMgr* m_pcUmsDiscuss; // b4��������
	CSelView*		m_pcSelView;	// ѡ��
	CPollMgr*		m_pcPollMgr;	//��ѯ
	CUmsRollCallMgr* m_pcRollCallMgr; //����

	CUmsAudMixMgr*	m_pcAudMix;     //�������

    CGetConfVidAudMgr*  m_tGetConfVidAudMgr;    //��ȡ����㲥����Ƶ

	CUmsMcuMgr*	m_pcMcuMgr;	// mcu����

	static TTPConfEpParamArray  m_tConfEpInfoMrg;

	static TMediaNetWorkManger  m_tMediaNetWorkManger; // ע�ᵽ���ص�ת���忨������˫����������ͬ���Σ���������ͳһ����

public:
	static TXmpuVmpManger m_tXmpuVmpManger;

private:

	BOOL32          m_bIsNeedDelayCallNode;    // �Ƿ���Ҫ�ӳٺ��н��
	BOOL32          m_bIsAllEpMute;
	BOOL32          m_bIsAllEpQuiet;
	BOOL32			m_bEpNodeCheck;

private:
	CDataConfHandler*	m_pcDataConf;	//���ݻ��鴦��ӿ�

public:
	TTPQTMediaKeyInfo	MediaKey(u16 wIndex) { return m_atMediaKey[wIndex]; }
private:
    TTPQTMediaKeyInfo	m_atMediaKey[TP_MAX_OLD_KEY_NUM];  //�������µ�2��������Կ
	u16                 m_wMediaKeyIndx;//������Կ����
	BOOL32				m_bSetMediaKey;
};


typedef zTemplate<CUmsConfInst, TP_UMS_MAX_CONFNUM> CUmsCallMgrApp;


#endif // _h_umscallinst_h__





