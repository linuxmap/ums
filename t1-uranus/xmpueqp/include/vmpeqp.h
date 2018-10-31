#ifndef _vmp_eqp_h_
#define _vmp_eqp_h_

#include "umsinnerstruct.h"
#include "xmpuinnerstruct.h"

typedef struct tagTXmpuVmpInfo
{
//	EMVmpStyle		m_emVmpStyle;

	u8				m_byVMPMemberNum;	  //当前合成成员数目
//	TTPVMPMember	m_atVMPMember[TP_VMP_MAX_IN_CHN_NUM]; //画面合成成员
	TTPTransAddr	m_atDecMiddleRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码 中转地址
	TTPTransAddr	m_atDecRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp解码通道rtp rcv
	TTPTransAddr	m_atDecRtcpAddr[TP_VMP_MAX_IN_CHN_NUM];  // vmp解码通道 back rtcp rcv

	u8				m_byOutMemBerNum;
//	TUmsVidFormat	m_atVMPOutMember[TP_VMP_MAX_OUT_CHN_NUM];
	TTPTransAddr	m_atEncRtpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码 中转地址
	TTPTransAddr	m_atEncRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp编码通道rtcp rcv
	
	u8				m_byVipMaxStyle;
	u8				m_byVipNum;		// vmp前适配通道

	tagTXmpuVmpInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byVipMaxStyle = 0;
		m_byVipNum = 0;
		m_byVMPMemberNum = TP_MAX_STREAMNUM;
		m_byOutMemBerNum = TP_VMP_MAX_OUT_CHN_NUM;

//		memset(m_atVMPMember, 0, sizeof(m_atVMPMember));
		memset(m_atDecMiddleRtpAddr, 0, sizeof(m_atDecMiddleRtpAddr));
		memset(m_atDecRtpAddr, 0, sizeof(m_atDecRtpAddr));
		memset(m_atDecRtcpAddr, 0, sizeof(m_atDecRtcpAddr));
//		memset(m_atVMPOutMember, 0, sizeof(m_atVMPOutMember));
		memset(m_atEncMiddleRtcpAddr, 0, sizeof(m_atEncMiddleRtcpAddr));
		memset(m_atEncRtcpAddr, 0, sizeof(m_atEncRtcpAddr));
		memset(m_atEncRtpAddr, 0, sizeof(m_atEncRtpAddr));
	}
}TXmpuVmpInfo;


typedef struct tagTXmpuVmpModle
{
public:

	APPHANDLE			m_dwEqpID;			//外设分配ID 初始化分配 永不修改
	HMEDIARES			m_dwHandle;			//Media Handle
	u32_ip						m_dwMediaIP;
	s8								m_achEqpAlias[TP_MAXLEN_EQP_ALIAS+1];//外设别名 初始化分配 永不修改

	//以下为外设使用信息
	u16						m_wConfID;
	TXmpuVmpInfo	m_tTpVmpParam;		//合成适配通道参数
	EmXmpuEqpStat	m_emStat;			// 外设状态

	u16						m_wUmsRcvStartPort;  //ums起始端口
	
	// 关键帧
	TXmpuFrameStatis	m_tKeyFrameStatis;	//关键帧保护
	TXmpuFrameStatis	m_tKeyFrameStatisToEqp;	//关键帧保护
	tagTXmpuVmpModle()
	{
		Clear();
	}
	void Clear()
	{
		m_dwHandle = 0;
		m_dwMediaIP = 0;
		m_wConfID = TP_INVALID_INDEX;
		m_emStat = XmpuEqpStat_Idle;
		
		m_wUmsRcvStartPort = 0;
		m_tTpVmpParam.Clear();

		m_tKeyFrameStatis.Clear();
		m_tKeyFrameStatis.SetIntrval(2);

		m_tKeyFrameStatisToEqp.Clear();
		m_tKeyFrameStatisToEqp.SetIntrval(1);

	}
}TXmpuVmpModle;

class CUmsXmpuInst;
class CVmpEqpHandle : public CEqpBaseHandle
{
public:
	CVmpEqpHandle() {}
	CVmpEqpHandle(CUmsXmpuInst* pInst);
	virtual ~CVmpEqpHandle();

	virtual void Init();
	virtual BOOL32 Handle(CTpMsg *const ptMsg);
	virtual BOOL32 StopConf(u16 wConfID);
	virtual void Show();
	virtual void ShowAll();

	virtual BOOL32 AssignEqpEx(TXmpuEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TXmpuEqpParam* ptEqpParam);


	virtual BOOL32 AssignEqp(u16 wCapCount, TEqpRes& tEqp) { return FALSE; };
	virtual BOOL32 ReleaseEqp(u16 wEqpIndex, u16 wCapCount) { return FALSE; };
	virtual u16 OnGetUsedNum() {return m_wVmpUsedNum;};	

	void	UpdateVmpState(u16 wVmpNum);
	void	ReFreshVmpState(BOOL32 bIncrease, u16 wVmpNum);
protected:
	
private:
	void OnStartVmpRsp(CTpMsg *const ptMsg);
	void OnChangeVmpReq(CTpMsg *const ptMsg);
	void OnStartMpu2Req(CTpMsg *const ptMsg);
	void OnChangeMpu2Req(CTpMsg *const ptMsg);
 	void OnXmpuVmpAskKey(CTpMsg *const ptMsg);
	void OnUmsVmpAskKey(CTpMsg *const ptMsg);
	void OnVmpDisConnect(CTpMsg *const ptMsg);
	void SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen );

	void OnUpdateSpeakerSideReq(CTpMsg *const ptMsg);
	TXmpuVmpModle* FindVmpMdl(u8 byEqpId);
	TXmpuVmpModle* FindIdleVmpMdl();
	void  AdjustUmsAddr(TXmpuVmpModle* ptModle);

private:
 	TXmpuVmpModle m_atVmpMdl[XMPU_MAX_VMP_NUM];
	u16 m_wVmpUsedNum;
};


#endif // _vmp_eqp_h_