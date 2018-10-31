#ifndef _EQPVMP_H_
#define _EQPVMP_H_

#include "umseqp.h"
#include "tpsys.h"
#include "eqpinterface.h"
#include "eqpmgr.h"
#include "eqpinst.h"
#define VMP_MAX_PORT_SPAN		400		//ÿ���ϳ��������ʹ��400���˿�
#define VMP_MAX_DEC_PORT_SPAN	300		//����ͱ�����300

class CVmpModle : public CEqpModle
{
public:
	enum EmEqpStat
	{
		EqpStat_OffLine,   //���費����
		EqpStat_Idle,   //����δע��
		EqpStat_Normal,  //����
		EqpStat_Assign,   // ����
		EqpStat_Starting, //���ڿ������м�״̬
		EqpStat_Running, //���ڹ���
		EqpStat_Stoping, //���ڹرգ��м�״̬
		EqpStat_Error,  //�쳣
	};
	//����Ϊ����ʹ����Ϣ
	u16			m_wConfID;
	TTPVMPParam	m_tTpVmpParam;		//�ϳ�����ͨ������

	//����Ϊ�������߸���
	EmEqpStat	m_emStat;			//����״̬
	EMEqpModleType	m_emMdlType;	//����ģʽ

	u8			m_byEqpID;			//�������ID
	u16			m_wEqpRcvStartPort;	//������ʼ�˿�
	u16			m_wUmsRcvStartPort;  //ums��ʼ�˿�

	TFrameStatis	m_tKeyFrameStatis;	//�ؼ�֡����
	TFrameStatis	m_tKeyFrameStatisToEqp;	//�ؼ�֡����

	CVmpModle() :  CEqpModle()
	{
		Clear();
	}
	void Clear()
	{
		m_byEqpID = 0;
		m_wEqpRcvStartPort = 0;
		m_wUmsRcvStartPort = 0;

		m_emMdlType = em_unknow_eqp_mdl;
		m_emStat = EqpStat_OffLine;
		m_wConfID = TP_INVALID_INDEX;
		m_tTpVmpParam.ClearInOutParam();

		m_tKeyFrameStatis.Clear();
		m_tKeyFrameStatis.SetIntrval(2);

		m_tKeyFrameStatisToEqp.Clear();
		m_tKeyFrameStatisToEqp.SetIntrval(1);

		CEqpModle::Clear();
	}
};

class CVmpEqp : public CEqpBase
{
public:
	CVmpEqp(CUmsEqpInst* pInst);
	virtual ~CVmpEqp();

	virtual void Init();
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Show();
	
	virtual BOOL32 AssignEqp(u16 wCapCount, TEqpRes& tEqp) { return FALSE; };
	virtual BOOL32 ReleaseEqp(u16 wEqpIndex, u16 wCapCount) { return FALSE; };
	
	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);
	
	virtual BOOL32 OnDisConnect(u32 dwNode);

	void SendMsgToEqpSsn( u32 dwSrcIID, u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0 );
	void SendMsgToCall( u16 wConfID, u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0 );

	//�������ߺ���Ҫ���ð����ϵ��������һ������λ��
	CVmpModle* InsertVmp( TTPEqpCfg& tCfg, u32 dwNode );
	void DeleteVmp( u8 byEqpID );

	void CalcEqpUsedStat(TTPBrdUsedInfo& tUsed);
protected:
	void OnVmpReg(CTpMsg *const ptMsg);
	
	void OnVmpStatNtfy(CTpMsg *const ptMsg);

	void OnStartVmpAck(CTpMsg *const ptMsg);
	void OnStartVmpNAck(CTpMsg *const ptMsg);
	void OnStartVmpNtfy(CTpMsg *const ptMsg);

	void OnStopVmpAck(CTpMsg *const ptMsg);
	void OnStopVmpNAck(CTpMsg *const ptMsg);
	void OnStopVmpNtfy(CTpMsg *const ptMsg);

	void OnChangeVmpAck(CTpMsg *const ptMsg);
	void OnChangeVmpNAck(CTpMsg *const ptMsg);
	void OnChangeVmpNtfy(CTpMsg *const ptMsg);
	
	void OnStartVmp(CTpMsg *const ptMsg);
	void OnAdjustVmp(CTpMsg *const ptMsg);
	
	void OnStartStopChnReq(CTpMsg *const ptMsg);

	void OnQtSetMediaKey(CTpMsg *const ptMsg);

private:
	CVmpModle* AssignVmpMdl( u8 byMemberNum, u8 byOutMemberNum );
	CVmpModle* FindVmpMdl( u8 byEqpID );
	CVmpModle* FindVmpMdl( u32 dwNode );
	void AskFrameReq( BOOL32 bToEqp, TTPVmpAskFrame& tAskFrame );

private:
	CVmpModle m_atVmpMdl[TP_UMS_MAX_VMP_NUM];
};

#endif