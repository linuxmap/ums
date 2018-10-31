#ifndef _AUDBASEQP_H_
#define _AUDBASEQP_H_
#include "umseqp.h"
#include "tpsys.h"
#include "eqpinterface.h"
#include "eqpmgr.h"
#include "eqpinst.h"

#define AUD_BAS_MAX_PORT_SPAN		210		//每个适配外设最大使用210个端口

class CAudBasModle;

typedef struct tagTAudBasChn
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

	TUmsAudFormat	m_tAudDec;
	TUmsAudFormat	m_atAudEnc[UMS_AUDBAS_ENC_NUM];

	CAudBasModle*	m_pcBasMdl;				//所在的板子

	tagTAudBasChn() { Clear(); }
	
	void Clear()
	{
		memset(this, 0, sizeof(sizeof(tagTAudBasChn)));
		m_wConfID = TP_INVALID_INDEX;
		m_emChnStat = Stat_BasChn_Idle;
		m_pcBasMdl = NULL;
	}
}TAudBasChn;

//外设管理
class CAudBasModle : public CEqpModle
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

	u32			m_dwMediaIP;		// 转发板ip
	
	u16			m_wEqpRcvStartPort; // 外设起始端口
	u16			m_wUmsRcvStartPort; // UMS起始端口

	//初始化分配 永不删除
	u8			m_byIndx;			//在数组中的索引

	CAudBasModle() :  CEqpModle()
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

class CAudBasEqp : public CEqpBase
{
public:
	CAudBasEqp(CUmsEqpInst* pInst);
	virtual ~CAudBasEqp();
	
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
	CAudBasModle* InsertBas(TTPEqpCfg& tCfg, u32 dwNode);
	void DeleteBas( u8 byEqpID );

	void CalcEqpUsedStat(TTPBrdUsedInfo& tUsed);

	// 修改转发板send ip
	void ChangeBasMeidaDsIp(TBasSndAddr& tSndAddr);
protected:

	void OnBasReg(CTpMsg *const ptMsg);
	void OnBasStatNtfy(CTpMsg *const ptMsg);
	void OnBasChnStatNtfy(CTpMsg *const ptMsg);

	void OnStartAdapter(CTpMsg *const ptMsg);

	void OnStartAdapterAck(CTpMsg *const ptMsg);
	void OnStartAdapterNAck(CTpMsg *const ptMsg);

	void OnStopAdapterAck(CTpMsg *const ptMsg);
	void OnStopAdapterNAck(CTpMsg *const ptMsg);
	
	void StopAdatper(TAudBasChn* ptBasChn);

	CAudBasModle* FindBasMdl( u8 byEqpID );
	CAudBasModle* FindBasMdl( u32 dwNode );
	TAudBasChn* FindSuitableBasChn();

	TAudBasChn* FindSuitableBasChn(TAudBasParam* ptBasParam);
	
	void OnSetSyncChnl( CTpMsg *const ptMsg );

	void OnSetMediaKey( CTpMsg *const ptMsg );
private:
	CAudBasModle	m_atBasMdl[TP_UMS_MAX_AUD_BAS_NUM];
	TAudBasChn		m_atBasChn[AUD_BAS_MAX_CHNL_NUM*TP_UMS_MAX_AUD_BAS_NUM]; //所有通道信息
};
#endif
