#ifndef _vidbas_eqp_h_
#define _vidbas_eqp_h_

#include "umsinnerstruct.h"
#include "xmpuinnerstruct.h"
#include "umsinnertype.h"

// Xmpu vidbas��ռ��һ����ת��ַ
// Dec rtp: EpRtp--->MiddleRtp--->MixRtp
// Enc Rtcp: EpRtcp-->MiddleRtcp-->MixRtcp
typedef struct tagTXmpuBasChn
{
	APPHANDLE		m_dwEqpID;			//�������ID ��ʼ������ �����޸�
	HMEDIARES		m_dwHandle;			//Media Handle

	u16				m_wConfID;
	u32_ip			m_dwMediaIP;

	EmXmpuEqpStat	m_emStat;			// ����״̬

	TTPTransAddr	m_tDecMiddleRtpAddr;// ��ת��ַ
	TTPTransAddr	m_tDecRtpAddr;
	TTPTransAddr	m_tDecRtcpAddr;

	u8					m_byEncChnNum;		//��ͨ��֧�ּ�·������ ����	
	TTPTransAddr	m_atEncRtpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp����ͨ��rtcp rcv
	TTPTransAddr	m_atEncRtcpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp����ͨ��rtcp rcv
	TTPTransAddr	m_atEncMiddleRtcpAddr[TP_CONF_MAX_MAIN_VIDEO_RES_NUM]; // vmp������תͨ����ַ
	BOOL32			m_abVaildChn[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	u16					m_wUmsRcvStartPort;


	TXmpuFrameStatis	m_tKeyFrameStatis;	//�ؼ�֡����
	TXmpuFrameStatis	m_tKeyFrameStatisToEqp;	//�ؼ�֡����

	tagTXmpuBasChn() { Clear(); }

	void Clear()
	{
		m_dwHandle = 0;
		m_wConfID = TP_INVALID_INDEX;
		m_emStat = XmpuEqpStat_Idle;
		m_dwMediaIP = 0;
		m_byEncChnNum = 0;
		m_wUmsRcvStartPort = 0;
		m_tDecMiddleRtpAddr.Clear();
		m_tDecRtpAddr.Clear();
		m_tDecRtcpAddr.Clear();
		memset(m_atEncRtpAddr, 0, sizeof(m_atEncRtpAddr));
		memset(m_atEncRtcpAddr, 0, sizeof(m_atEncRtcpAddr));
		memset(m_atEncMiddleRtcpAddr, 0, sizeof(m_atEncMiddleRtcpAddr));
		memset(m_abVaildChn, 0, sizeof(m_abVaildChn));

		m_tKeyFrameStatisToEqp.Clear();
		m_tKeyFrameStatis.Clear();
		//��Ƶ���� �ؼ�֡���� ��3s
		m_tKeyFrameStatis.SetIntrval(3);
		m_tKeyFrameStatisToEqp.SetIntrval(3);
	}

}TXmpuBasChn;



class CUmsXmpuInst;
class CVidBasEqpHandle : public CEqpBaseHandle
{
public:
	CVidBasEqpHandle() {}
	CVidBasEqpHandle(CUmsXmpuInst* pInst);
	virtual ~CVidBasEqpHandle();

	virtual void Init();
	virtual BOOL32 Handle(CTpMsg *const ptMsg);
	virtual BOOL32 StopConf(u16 wConfID);
	virtual void Show();
	virtual void ShowAll();
	
	virtual BOOL32 AssignEqpEx(TXmpuEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TXmpuEqpParam* ptEqpParam);

	virtual u16 OnGetUsedNum(){return m_wVidBasUsedNum ;};
protected:
	
private:
	void OnStartBasRsp( CTpMsg *const ptMsg );
	void OnSetBasEncParamReq( CTpMsg *const ptMsg );
	void OnSetBasEncParamRsp( CTpMsg *const ptMsg );
	void OnXmpuBasAskKey( CTpMsg *const ptMsg );
	void OnUmsBasAskKey( CTpMsg *const ptMsg );
	void OnBasDisConnect( CTpMsg *const ptMsg );

	void  AdjustAddr(TXmpuBasChn* ptChn);
	void SendMsgToCall( u16 wConfID, u16 wEvent, void * const pbyMsg, u16 wLen );
	TXmpuBasChn* FindBasChnMdl(u8 byEqpId);
	TXmpuBasChn* FindIdleBasMdl();

private:
	TXmpuBasChn  m_atBasChn[XMPU_MAX_BAS_NUM];
	u16 m_wVidBasUsedNum;  //vid basʹ������
};


#endif // _vidbas_eqp_h_