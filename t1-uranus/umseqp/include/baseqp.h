#ifndef _BASEQP_H_
#define _BASEQP_H_
#include "umseqp.h"
#include "tpsys.h"
#include "eqpinterface.h"
#include "eqpmgr.h"
#include "eqpinst.h"

#define BAS_MAX_PORT_SPAN		1000		//每个适配外设最大使用1000个端口
#define BAS_MAX_DEC_PORT_SPAN	500			//解码和编码间隔500

#define BAS_ENHACNED_OUT_CHN_MAX_NUM_1		7
#define BAS_ENHACNED_OUT_CHN_MAX_NUM_2		8
#define BAS_ENHACNED_OUT_CHN_MAX_NUM_OTHER	5

#define BAS_BASIC_OUT_CHN_MAX_NUM_1			6
#define BAS_BASIC_OUT_CHN_MAX_NUM_2			6
#define BAS_BASIC_OUT_CHN_MAX_NUM_OTHER		5

class CBasModle;

typedef struct tagTBasChn
{
	enum	EmChnStat
	{
		Stat_BasChn_Idle,
		Stat_BasChn_Normal,
		Stat_BasChn_Reserve,
		Stat_BasChn_Starting,
		Stat_BasChn_Running,
		Stat_BasChn_Stoping,
		Stat_BasChn_Error,
	};
	
	u16				m_wConfID;

	EmChnStat		m_emChnStat;			//通道状态
	u8    			m_byChnID;			    //通道ID
	u8				m_byEqpID;				//外设ID
	u16				m_wEncAbility;			//编码能力 即EncRes 数量
	u8				m_byOutChnNum;			//该通道支持几路后适配 编码	

	CBasModle*		m_pcBasMdl;				//所在的板子

	TFrameStatis	m_tKeyFrameStatis;	//关键帧保护
	TFrameStatis	m_tKeyFrameStatisToEqp;	//关键帧保护

	tagTBasChn() { Clear(); }
	
	void Clear()
	{
		memset(this, 0, sizeof(sizeof(tagTBasChn)));
		m_wConfID = TP_INVALID_INDEX;
		m_emChnStat = Stat_BasChn_Idle;
		m_pcBasMdl = NULL;

		m_tKeyFrameStatisToEqp.Clear();
		m_tKeyFrameStatis.Clear();

		m_byChnID = 0;
		m_byEqpID = 0;
		m_wEncAbility = 0;
		m_byOutChnNum = 0;

		//mpu2适配 关键帧保护 用3s
		m_tKeyFrameStatis.SetIntrval(3);
		m_tKeyFrameStatisToEqp.SetIntrval(3);
	}

	//后适配通道数量
	void SetOutChnNum( u8 byChnIndx, EMEqpModleType emMdlType )
	{
		if ( byChnIndx == 0 )
		{
			if ( emMdlType == em_bas_basic_eqp_mdl )
			{
				m_byOutChnNum = BAS_BASIC_OUT_CHN_MAX_NUM_1;
				m_wEncAbility = BAS_ENCRES_1500;
			}
			else
			{
				m_wEncAbility = BAS_ENCRES_3000;
				m_byOutChnNum = BAS_ENHACNED_OUT_CHN_MAX_NUM_1;
			}
		}
		else if( byChnIndx == 1 )
		{
			if ( emMdlType == em_bas_basic_eqp_mdl )
			{
				m_wEncAbility = BAS_ENCRES_1500;
				m_byOutChnNum = BAS_BASIC_OUT_CHN_MAX_NUM_2;
			}
			else
			{
				m_wEncAbility = BAS_ENCRES_3000;
				m_byOutChnNum = BAS_ENHACNED_OUT_CHN_MAX_NUM_2;
			}
		}
		else
		{
			if ( emMdlType == em_bas_basic_eqp_mdl )
			{
				m_wEncAbility = BAS_ENCRES_1000;
				m_byOutChnNum = BAS_BASIC_OUT_CHN_MAX_NUM_OTHER;
			}
			else
			{
				m_wEncAbility = BAS_ENCRES_1000;
				m_byOutChnNum = BAS_ENHACNED_OUT_CHN_MAX_NUM_OTHER;
			}
		}
		return ;
	}
	
	BOOL32 CheckAbility(u8 byOutChnNum)
	{
		if ( byOutChnNum <= m_byOutChnNum )
		{//通道数量检测
			return TRUE;
		} 
		return FALSE;
	}
}TBasChn;

//外设管理
class CBasModle : public CEqpModle
{
public:
	enum EmEqpStat
	{
		EpqStat_OffLine,	//掉线
		EqpStat_Idle,		//外设未注册
		EqpStat_Normal,		//在线
	};

	//以下为外设上线更新
	u8			m_byEqpID;			//外设唯一ID
	EmEqpStat	m_emStat;			//外设状态
	EMEqpModleType	m_emMdlType;	//外设模式

	u32			m_dwMediaIP;			// 转发板ip
	
	u16			m_wEqpRcvStartPort; // 外设起始端口
	u16			m_wUmsRcvStartPort; // UMS起始端口

	//初始化分配 永不删除
	u8			m_byIndx;			//在数组中的索引

	CBasModle() :  CEqpModle()
	{
		m_byIndx = 0;
		Clear();
	}
	void Clear()
	{
		m_byEqpID = 0;
		m_emStat = EpqStat_OffLine;
		m_emMdlType = em_unknow_eqp_mdl;
		m_dwMediaIP = 0;

		m_wEqpRcvStartPort = 0;
		m_wUmsRcvStartPort = 0;

		CEqpModle::Clear();
	}
	
	u16	GetMdlChnBeginIndx()
	{
		return m_byIndx * BAS_CHN_MAX_NUM_EHANCED;
	}
};

class CBasEqp : public CEqpBase
{
public:
	CBasEqp(CUmsEqpInst* pInst);
	virtual ~CBasEqp();
	
	virtual void Init();
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Show();
	
	virtual BOOL32 AssignEqp(u16 wCapCount, TEqpRes& tEqp) { return FALSE; };
	virtual BOOL32 ReleaseEqp(u16 wEqpIndex, u16 wCapCount) { return FALSE; };
	
	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);
	
	virtual BOOL32 OnDisConnect(u32 dwNode);
	
	void SendMsgToEqpSsn( u32 dwSrcIID, u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0 );
	void SendMsgToCall( u16 wConfID, u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0 );	//板子上线后，需要给该板子上的外设分配一个外设位置
	CBasModle* InsertBas(TTPEqpCfg& tCfg, u32 dwNode);
	void DeleteBas( u8 byEqpID );

	void CalcEqpUsedStat(TTPBrdUsedInfo& tUsed);

	// 变更适配器send转发板ip
	void	ChangeBasMeidaDsIp(TBasSndAddr& tSndAddr);
protected:

	void OnBasReg(CTpMsg *const ptMsg);
	void OnBasStatNtfy(CTpMsg *const ptMsg);
	
	void OnBasChnStatNtfy(CTpMsg *const ptMsg);

	void OnStartAdapter(CTpMsg *const ptMsg);

	void OnStartAdapterAck(CTpMsg *const ptMsg);
	void OnStartAdapterNAck(CTpMsg *const ptMsg);
	void OnStopAdapterAck(CTpMsg *const ptMsg);
	void OnStopAdapterNAck(CTpMsg *const ptMsg);

	void OnAskFrameToCall(CTpMsg *const ptMsg);
	void OnAskFrameToEqp(CTpMsg *const ptMsg);

	void OnQtSetMediaKey(CTpMsg *const ptMsg);

	void StopAdatper(TBasChn* ptBasChn);

	CBasModle* FindBasMdl( u8 byEqpID );
	CBasModle* FindBasMdl( u32 dwNode );
	TBasChn* FindSuitableBasChn( TBasParam::EmAssignType emType, u8 byOutChanNum, u16& wChnIndx);
	
private:
	CBasModle	m_atBasMdl[TP_UMS_MAX_BAS_NUM];
	TBasChn		m_atBasChn[BAS_CHN_MAX_NUM_EHANCED*TP_UMS_MAX_BAS_NUM]; //所有通道信息
};
#endif
