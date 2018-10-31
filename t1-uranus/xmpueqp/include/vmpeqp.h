#ifndef _vmp_eqp_h_
#define _vmp_eqp_h_

#include "umsinnerstruct.h"
#include "xmpuinnerstruct.h"

typedef struct tagTXmpuVmpInfo
{
//	EMVmpStyle		m_emVmpStyle;

	u8				m_byVMPMemberNum;	  //��ǰ�ϳɳ�Ա��Ŀ
//	TTPVMPMember	m_atVMPMember[TP_VMP_MAX_IN_CHN_NUM]; //����ϳɳ�Ա
	TTPTransAddr	m_atDecMiddleRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp���� ��ת��ַ
	TTPTransAddr	m_atDecRtpAddr[TP_VMP_MAX_IN_CHN_NUM];    // vmp����ͨ��rtp rcv
	TTPTransAddr	m_atDecRtcpAddr[TP_VMP_MAX_IN_CHN_NUM];  // vmp����ͨ�� back rtcp rcv

	u8				m_byOutMemBerNum;
//	TUmsVidFormat	m_atVMPOutMember[TP_VMP_MAX_OUT_CHN_NUM];
	TTPTransAddr	m_atEncRtpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp����ͨ��rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp���� ��ת��ַ
	TTPTransAddr	m_atEncRtcpAddr[TP_VMP_MAX_OUT_CHN_NUM]; // vmp����ͨ��rtcp rcv
	
	u8				m_byVipMaxStyle;
	u8				m_byVipNum;		// vmpǰ����ͨ��

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

	APPHANDLE			m_dwEqpID;			//�������ID ��ʼ������ �����޸�
	HMEDIARES			m_dwHandle;			//Media Handle
	u32_ip						m_dwMediaIP;
	s8								m_achEqpAlias[TP_MAXLEN_EQP_ALIAS+1];//������� ��ʼ������ �����޸�

	//����Ϊ����ʹ����Ϣ
	u16						m_wConfID;
	TXmpuVmpInfo	m_tTpVmpParam;		//�ϳ�����ͨ������
	EmXmpuEqpStat	m_emStat;			// ����״̬

	u16						m_wUmsRcvStartPort;  //ums��ʼ�˿�
	
	// �ؼ�֡
	TXmpuFrameStatis	m_tKeyFrameStatis;	//�ؼ�֡����
	TXmpuFrameStatis	m_tKeyFrameStatisToEqp;	//�ؼ�֡����
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