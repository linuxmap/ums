#ifndef _h_audiomixeqp_h__
#define _h_audiomixeqp_h__

#include "umseqp.h"
#include "tpsys.h"
#include "eqpinterface.h"

class CAudioMixModle : public CEqpModle
{
	public:
	enum EmAudMixStat
	{
		EmAudMix_Idle,
		EmAudMix_InitIng,
		EmAudMix_Normal,
		EmAudMix_Reserve,
		EmAudMix_StartIng,
		EmAudMix_Running,
		EmAudMix_StopIng,
		EmAudMix_Error,
	};

	//分配和使用更新
	u16				m_wConfID;
	EmAudMixStat	m_emStat;

	//注册更新
	u8				m_byEqpID;			//外设分配ID
	u16				m_wChanNum;			//通道数量
	u16				m_wOffSet;			//通道的便宜
	u16				m_wEqpRcvStartPort;	//外设起始端口
	u16				m_wEqpRcvRtcpStartPort;  //外设rtcp起始端口
	u16				m_wUmsRcvStartPort; //UMS起始端口

public:
	CAudioMixModle() :  CEqpModle()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_emStat = EmAudMix_Idle;

		m_wChanNum = 0;
		m_byEqpID = 0;
		m_wEqpRcvStartPort = 0;
		m_wEqpRcvRtcpStartPort = 0;
		m_wUmsRcvStartPort = 0;

		m_wOffSet = 0;

		CEqpModle::Clear();
	}

	BOOL32 IsUsable()
	{
		if (EmAudMix_Normal == m_emStat && TP_INVALID_INDEX == m_wConfID && m_bRegsited)
		{
			return TRUE;
		}
		return FALSE;
	}

	u32 GetUnUsedChanNum( )
	{
		return (this->m_tRegInfo.m_dwCapSet - m_dwUsed);
	}
};

class CAudioMixEqp : public CEqpBase
{
public:
	CAudioMixEqp(CUmsEqpInst* pInst);
	virtual ~CAudioMixEqp();
	
public:
	CAudioMixModle* FindMixMdl( u8 byEqpID );
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Show();

	virtual BOOL32 AssignEqp(u16 wCapCount, TEqpRes& tEqp) { return FALSE; };
	virtual BOOL32 ReleaseEqp(u16 wEqpIndex, u16 wCapCount) { return FALSE; };

	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);

	virtual BOOL32 OnDisConnect(u32 dwNode);

	CAudioMixModle* InsertMix( TTPEqpCfg& tCfg, u32 dwNode, u16 wOffSet );
	void DeleteMix( u8 byEqpID );

	void CalcEqpUsedStat(TTPBrdUsedInfo& tUsed);
protected:
	void OnEqpReg(CTpMsg *const ptMsg);
	void OnMixerStatNtfy(CTpMsg *const ptMsg);
	
	void OnStartMix(CTpMsg *const ptMsg);
	void OnStartMixAck(CTpMsg *const ptMsg);
	void OnStartMixNAck(CTpMsg *const ptMsg);

	void OnStopMix(CTpMsg *const ptMsg);
	void OnStopMixAck(CTpMsg *const ptMsg);
	void OnStopMixNAck(CTpMsg *const ptMsg);

	void OnStartVAC(CTpMsg *const ptMsg);
	void OnStopVAC(CTpMsg *const ptMsg);

	void OnAddMixMember(CTpMsg *const ptMsg);
	void OnAddMixMemberAck(CTpMsg *const ptMsg);
	void OnAddMixMemberNAck(CTpMsg *const ptMsg);

	void OnDelMixMember(CTpMsg *const ptMsg);
	void OnDelMixMemberAck(CTpMsg *const ptMsg);
	void OnDelMixMemberNAck(CTpMsg *const ptMsg);

	void OnForceActive(CTpMsg *const ptMsg);
	void OnCancelForceActive(CTpMsg *const ptMsg);

	void OnSetVacKeepTime(CTpMsg *const ptMsg);

	void OnVacResultNtfy(CTpMsg *const ptMsg);

	void OnifSndNtfy(CTpMsg *const ptMsg);

	void OnSyncChnlCmd(CTpMsg *const ptMsg);

    void OnSetMediaKeyNtfy(CTpMsg *const ptMsg);

	u16  FindSuitableMixMdl(u16 wChanLimit);
	u16  FindSuitableMixMdl(u16 wChanLimit, u32 dwNode);
	u32  FindSuitableApu2(u16 wChanLimit, u16 wReqNum);

private:
	CAudioMixModle m_atAudioMix[MAX_AUDMIX_MDL_NUM];
};

#endif // _h_adaptereqp_h__
