#ifndef _audmix_eqp_h_
#define _audmix_eqp_h_

#include "umsinnerstruct.h"
#include "xmpuinnerstruct.h"
#include "umsinnertype.h"


// Xmpu Mix多占用一组中转地址
// N-1路:  Dec rtp: EpRtp--->MiddleRtp--->MixRtp         Enc rtcp: EpRtcp-->MiddleRtcp-->MixRtcp
// N出:	Enc Rtcp: EpRtcp-->MiddleRtcp-->MixRtcp
typedef struct tagTXmpuMixModle
{
public:

	APPHANDLE	m_dwEqpID;			// 初始分配，用不删除
	HMEDIARES	m_dwHandle;			//Media Handle
	u32_ip		m_dwMediaIP;

	//以下为外设使用信息
	u16						m_wConfID;
	EmXmpuEqpStat			m_emStat;			// 外设状态
	u8						m_byMaxChanNum;

	u8				m_byN1Num;
	TTPTransAddr	m_atN1DecMiddleRtpAddr[XMPU_AUDMIX_N1_NUM];  // N-1出解码中转地址
	TTPTransAddr	m_atN1DecRtpAddr[XMPU_AUDMIX_N1_NUM];  // N-1出解码
	TTPTransAddr	m_atN1EncMiddleRtcpAddr[XMPU_AUDMIX_N1_NUM]; // N-1出编码中转地址
	TTPTransAddr	m_atN1EncRtcpAddr[XMPU_AUDMIX_N1_NUM]; // N-1出编码

	u8				m_byNNum;
	u8				m_abyNChnID[UMS_AUDMIX_N_OUT_NUM];
	TTPTransAddr	m_atNEncRtpAddr[UMS_AUDMIX_N_OUT_NUM]; // N出编码通道地址
	TTPTransAddr	m_atNEncMiddleRtcpAddr[UMS_AUDMIX_N_OUT_NUM]; // N出编码中转地址
	TTPTransAddr	m_atNEncRtcpAddr[UMS_AUDMIX_N_OUT_NUM]; // N出编码通道地址

	// 外设端口
	u16				m_wUmsRcvStartPort;  //ums起始端口

	tagTXmpuMixModle()
	{
		Clear();
	}
	void Clear()
	{
		m_dwHandle = 0;
		m_dwMediaIP = 0;
		m_emStat = XmpuEqpStat_Idle;
		m_wConfID = TP_INVALID_INDEX;
		m_byMaxChanNum = 0;
		m_byN1Num = 0;
		m_byNNum = 0;
		m_wUmsRcvStartPort = 0;
		memset(m_atN1DecMiddleRtpAddr, 0, sizeof(m_atN1DecMiddleRtpAddr));
		memset(m_atN1DecRtpAddr, 0, sizeof(m_atN1DecRtpAddr));
		memset(m_atN1EncMiddleRtcpAddr, 0, sizeof(m_atN1EncMiddleRtcpAddr));
		memset(m_atN1EncRtcpAddr, 0, sizeof(m_atN1EncRtcpAddr));
		memset(m_abyNChnID, 0, sizeof(m_abyNChnID));
		memset(m_atNEncRtpAddr, 0, sizeof(m_atNEncRtpAddr));
		memset(m_atNEncMiddleRtcpAddr, 0, sizeof(m_atNEncMiddleRtcpAddr));
		memset(m_atNEncRtcpAddr, 0, sizeof(m_atNEncRtcpAddr));
	}
}TXmpuMixModle;


class CUmsXmpuInst;
class CAudioMixEqpHandle : public CEqpBaseHandle
{
public:
	CAudioMixEqpHandle() {}
	CAudioMixEqpHandle(CUmsXmpuInst* pInst);
	virtual ~CAudioMixEqpHandle();

	virtual void Init();
	virtual BOOL32 Handle(CTpMsg *const ptMsg);
	virtual BOOL32 StopConf(u16 wConfID);
	virtual void Show();
	virtual void ShowAll();
	
	virtual BOOL32 AssignEqpEx(TXmpuEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TXmpuEqpParam* ptEqpParam);

	virtual u16 OnGetUsedNum(){return m_wMixUsedNum;};
	u16 OnGetMix8UsedNum(){return m_wMix8UsedNum;}

private:
	void OnStartMixRsp(CTpMsg *const ptMsg);
	void OnAddMixMemberReq(CTpMsg *const ptMsg);
	void OnAddMixMemberRsp(CTpMsg *const ptMsg);
	void OnDelMixMemberReq(CTpMsg *const ptMsg);

	void OnStartVacReq(CTpMsg *const ptMsg);
	void OnStopVacReq(CTpMsg *const ptMsg);
	void OnSetSynReq(CTpMsg *const ptMsg);
	void OnSetKeepTimeReq(CTpMsg *const ptMsg);

	void OnForceActiveReq( CTpMsg *const ptMsg );
	void OnVacActiveNty(CTpMsg *const ptMsg );
	void OnVoiceDetection(CTpMsg *const ptMsg);
	void OnMixDisConnect( CTpMsg *const ptMsg );
	TXmpuMixModle* FindIdleMixModle();
	TXmpuMixModle* FindMixModle(u32 dwEqpID);
	void SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen );

	void AdjustAddr( TXmpuMixModle* ptChn );

private:
	TXmpuMixModle  m_atMixModle[XMPU_MAX_AUDMIX_NUM];
	u16 m_wMixUsedNum;//mix192使用数量
	u16 m_wMix8UsedNum;//mix8使用数量
};


#endif // _audmix_eqp_h_