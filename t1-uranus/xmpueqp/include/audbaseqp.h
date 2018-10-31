#ifndef _audbas_eqp_h_
#define _audbas_eqp_h_

#include "umsinnerstruct.h"
#include "xmpuinnerstruct.h"
#include "umsinnertype.h"


// Xmpu audbas多占用一组中转地址
// Dec rtp: EpRtp--->MiddleRtp--->MixRtp
// Enc Rtcp: EpRtcp-->MiddleRtcp-->MixRtcp
typedef struct tagTXmpuAudBasModle
{
public:
	APPHANDLE				m_dwEqpID;			//外设分配ID初始分配永不删除
	HMEDIARES				m_dwHandle;			//Media Handle
	u32_ip						m_dwMediaIP;
	u16							m_wConfID;

	EmXmpuEqpStat		m_emStat;			//通道状态

	EmTpAudioFormat		m_emDecFormat;
	EmTpAudioFormat		m_aemEncFormat[AUD_BAS_MAX_OUT_CHNL_NUM];

	TTPTransAddr			m_tDecMiddleRtpAddr;//解码中转地址
	TTPTransAddr			m_tDecRtpAddr;
	TTPTransAddr			m_tDecRtcpAddr;

	u8							m_byEncNum;
	TTPTransAddr			m_atEncRtpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr			m_atEncRtcpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr			m_atEncMiddleRtcpAddr[AUD_BAS_MAX_OUT_CHNL_NUM]; // vmp编码通道rtcp rcv

	// 外设端口
	u16							m_wUmsRcvStartPort;  //ums起始端口
	tagTXmpuAudBasModle()
	{
		Clear();
	}
	void Clear()
	{
		m_dwHandle = 0;
		m_dwMediaIP = 0;
		m_wConfID = TP_INVALID_INDEX;
		m_emStat = XmpuEqpStat_Idle;
		m_tDecMiddleRtpAddr.Clear();
		m_tDecRtpAddr.Clear();
		m_tDecRtcpAddr.Clear();
		m_byEncNum = 0;
		memset(m_atEncRtpAddr, 0, sizeof(m_atEncRtpAddr));
		memset(m_atEncRtcpAddr, 0, sizeof(m_atEncRtcpAddr));
		memset(m_atEncMiddleRtcpAddr, 0, sizeof(m_atEncMiddleRtcpAddr));
		m_wUmsRcvStartPort = 0;
		m_emDecFormat = emTPAEnd;
		for (u16 wIndex = 0; wIndex < AUD_BAS_MAX_OUT_CHNL_NUM;++wIndex)
		{
			m_aemEncFormat[wIndex] = emTPAEnd;
		}
	}

}TXmpuAudBasModle;

class CUmsXmpuInst;
class CAudioBasEqpHandle : public CEqpBaseHandle
{
public:
	CAudioBasEqpHandle()  {};
	CAudioBasEqpHandle(CUmsXmpuInst* pInst);
	virtual ~CAudioBasEqpHandle();

	virtual void Init();
	virtual BOOL32 Handle(CTpMsg *const ptMsg);
	virtual BOOL32 StopConf(u16 wConfID);
	virtual void Show();
	virtual void ShowAll();

	virtual BOOL32 AssignEqpEx(TXmpuEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TXmpuEqpParam* ptEqpParam);
	virtual u16 OnGetUsedNum(){return m_wAudBasUsedNum;};
protected:
	
private:
	void OnStartAudBasRsp(CTpMsg *const ptMsg);
	void OnSetAudBasSynReq(CTpMsg *const ptMsg);
	void OnSetAudBasParamReq(CTpMsg *const ptMsg);
	void OnSetAudBasParamRsp(CTpMsg *const ptMsg);
	void OnAudBasDisConnect( CTpMsg *const ptMsg );

	void  AdjustAddr(TXmpuAudBasModle* ptModle);
	void SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen );

	TXmpuAudBasModle* FindIdleAudBasModle();
	TXmpuAudBasModle* FindAudBasModle(u32 dwEqpID);

private:
	TXmpuAudBasModle m_atAudModle[XMPU_AUD_BAS_MAX_CHN];
	u16 m_wAudBasUsedNum; //aud bas使用数量
};


#endif // _audbas_eqp_h_