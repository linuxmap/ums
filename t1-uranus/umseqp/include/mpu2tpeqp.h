#ifndef _mpu2_tp_eqp_h_
#define _mpu2_tp_eqp_h_
#include "umseqp.h"
#include "eqpinst.h"

#define TP_MAX_MPU2TP_NUM 16

enum EmMpu2TpState
{
	em_mpu2tp_idle,
	em_mpu2tp_Assgin,
	em_mpu2tp_working,
	em_mpu2tp_error,
};

typedef struct tagTMpu2TpModule
{
	//基本信息
	u8		m_byLayer;
	u8		m_bySlot;
	u16		m_wChanID;
	BOOL32	m_bReg;

	u16		m_wServiceID;
//	u32		m_dwMediaNode;
//	u32		m_dwMediaIndex;
//	u32		m_dwMediaIP;
	u16		m_wUmsStartPort;

	u16		m_wRcvChanNum;
	u16		m_wSndChanNum;
	u16		m_wEqpStartPort;
	u32		m_dwSrcIID;
	u32		m_dwSrcNode;

	//使用信息
	EmMpu2TpState	m_emState;	//工作状态

	TFrameStatis	m_tKeyFrameStatisToEqp;	//关键帧保护
	u16				m_wFrameTimesToEqp;

	TFrameStatis	m_tKeyFrameStatis;	//关键帧保护
	u16				m_wFrameTimes;

	tagTMpu2TpModule()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = 0;
		m_bySlot = 0;
		m_wChanID = 0;
		m_bReg = FALSE;

		m_wUmsStartPort = 0;
		
		m_wRcvChanNum = 0;
		m_wSndChanNum = 0;
		m_wEqpStartPort = 0;
		m_dwSrcIID = 0;
		m_dwSrcNode = 0;

		m_tKeyFrameStatisToEqp.Clear();
		//关键帧保护用2s
		m_tKeyFrameStatisToEqp.SetIntrval(2);
        m_wFrameTimesToEqp = 0;

        m_tKeyFrameStatis.Clear();
        m_tKeyFrameStatis.SetIntrval(2);
		m_wFrameTimes = 0;
		
		//使用信息
		m_emState = em_mpu2tp_idle;
//		memset(this, 0, sizeof(TMpu2TpModule));
	}
}TMpu2TpModule;

class CMpu2TpEqp : public CEqpBase
{
public:
//	CMpu2TpEqp();
	CMpu2TpEqp(CUmsEqpInst* ptInst);
	virtual ~CMpu2TpEqp();

public:
	virtual void Handle(CTpMsg *const ptMsg);

	virtual void Init();
	void Show();
public:
	virtual BOOL32 OnDisConnect(u32 dwNode);
	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam) { return TRUE; }
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam) { return TRUE; }

	virtual void CalcEqpUsedStat(TTPBrdUsedInfo& tUsed);

//	void MediaEqpDisConnect(u32 dwMediaIP);
//	void MediaEqpConnect();
private:
	void	EventRegist(CTpMsg* const ptMsg);
	void	EventStartRes(CTpMsg* const ptMsg);
	void	EventMdyRes(CTpMsg* const ptMsg);
	void	EventStopRes(CTpMsg* const ptMsg);
	void	EventAddChanRes(CTpMsg* const ptMsg);
	void	EventDelChanRes(CTpMsg* const ptMsg);
	void	EventUpdateSpeakerFlag(CTpMsg* const ptMsg);
	void	EventSetMediaKey(CTpMsg* const ptMsg);
	void	EventChangeDsIP(CTpMsg* const ptMsg);

private:
	void    EventAssginReq(CTpMsg* const ptMsg);
	void	EventStartReq(CTpMsg* const ptMsg);
	void	EventStopReq(CTpMsg* const ptMsg);
	void	EventMdyStyleReq(CTpMsg* const ptMsg);

	void	EventAskFrameReq(CTpMsg* const ptMsg);
private:
	u16		FindEqp(const u8 byLayer, const u8 bySlot, const u16 wChanID) const;
	u16		FindEqpByServiceID(const u16 wServiceID) const;
	u16		FindEqpByChanID(const u16 wChanID, const u32 dwNode) const;
	u16		FindIdleEqp() const;

private:
	void	SendMsgToCall(u16 wEvent, void* const pbyMsg = NULL, u16 wLen = 0);
	void	SendMsgToEqp(u16 wEvent, u32 dwDstIID, u32 dwNode, void* const pbyMsg = NULL, u16 wLen = 0);

private:
	void	ConvertRes(EmVmpRes emVmpRes, EmServiceRes& emServiceRes);
private:
	TMpu2TpModule	m_atModule[TP_MAX_MPU2TP_NUM];
};

#endif