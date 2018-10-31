#ifndef _EQPVMP_H_
#define _EQPVMP_H_

#include "umseqp.h"
#include "tpsys.h"
#include "eqpinterface.h"
#include "eqpmgr.h"
#include "eqpinst.h"
#define VMP_MAX_PORT_SPAN		400		//每个合成外设最大使用400个端口
#define VMP_MAX_DEC_PORT_SPAN	300		//解码和编码间隔300

class CVmpModle : public CEqpModle
{
public:
	enum EmEqpStat
	{
		EqpStat_OffLine,   //外设不在线
		EqpStat_Idle,   //外设未注册
		EqpStat_Normal,  //在线
		EqpStat_Assign,   // 分配
		EqpStat_Starting, //正在开启，中间状态
		EqpStat_Running, //正在工作
		EqpStat_Stoping, //正在关闭，中间状态
		EqpStat_Error,  //异常
	};
	//以下为外设使用信息
	u16			m_wConfID;
	TTPVMPParam	m_tTpVmpParam;		//合成适配通道参数

	//以下为外设上线更新
	EmEqpStat	m_emStat;			//外设状态
	EMEqpModleType	m_emMdlType;	//外设模式

	u8			m_byEqpID;			//外设分配ID
	u16			m_wEqpRcvStartPort;	//外设起始端口
	u16			m_wUmsRcvStartPort;  //ums起始端口

	TFrameStatis	m_tKeyFrameStatis;	//关键帧保护
	TFrameStatis	m_tKeyFrameStatisToEqp;	//关键帧保护

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

	//板子上线后，需要给该板子上的外设分配一个外设位置
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