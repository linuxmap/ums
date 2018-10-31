#ifndef _h_umseapu_h__
#define _h_umseapu_h__

#include "umsconfinst.h"
#include "tphandle.h"
#include "callinnerstruct.h"
#include "eqpinterface.h"
#include "umsconfigex.h"


typedef struct tagtXmpuMixCbData{
    void *pService;
	void *pRes;
	void *pData;
    tagtXmpuMixCbData()
	{
		memset(this, 0, sizeof(tagtXmpuMixCbData));
	}
}tXmpuMixCbData;

typedef struct tagTMixSync
{
	TAudMixInfo*	m_aptMixer[TP_MAX_STREAMNUM];
	u8				m_abyChanId[TP_MAX_STREAMNUM];
	BOOL32		m_bSpeakerObject;
	tagTMixSync()
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++ wIndex )
		{
			m_aptMixer[wIndex] = NULL;
			m_abyChanId[wIndex] = 0xFF;
		}
		m_bSpeakerObject = FALSE;
	}

	void Add(TAudMixInfo* ptInfo, u8 byChnl)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++ wIndex )
		{
			if ( m_aptMixer[wIndex] != NULL )
			{
				continue;
			}
			
			m_aptMixer[wIndex] = ptInfo;
			m_abyChanId[wIndex] = byChnl;

			break;
		}
	}

}TMixSync;

class CUmsConfInst;
class CUmsEapu  : public CTpHandler
{
public:
	CUmsEapu(CUmsConfInst* pcInst);
	~CUmsEapu();
	
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	void Show();

	void ShowMixInfo(TAudMixInfo* ptInfo);

	TAudMixInfo*  AssignMixer(AudMixerCB pCB, CUmsConfInst* ptUsrParam, u16 wChnlLimit = 0, u16 wReqNum = 1, u32 dwNode = 0);
	void ReleaseMixer(TAudMixInfo* ptInfo);

	//取得N模式接收地址
	void GetNModeAudRcvAddr( TAudMixInfo* ptInfo, TServiceAddr& tAddr, TUmsAudFormat& tAudFmt);

public:
	
	//混音模块通知语音激励结果（包括有声音的通道索引数组）
	void OnAudMixExciteInd(CTpMsg *const ptMsg);

	//混音器上线下线
	void OnAudMixDisConnect( CTpMsg *const ptMsg );
	void OnAudMixConnect( CTpMsg *const ptMsg );
	//添加会场和开启混音 操作回应
	void OnAddMemberNAck(CTpMsg *const ptMsg);
	void OnStartMixNAck(CTpMsg *const ptMsg);

	void StartVac(TAudMixInfo* ptInfo);
	void StopVac(TAudMixInfo* ptInfo);

	void SetMixerSyncChnl(TMixSync& tSync);
	void CheckDelMember(TAudMixInfo* ptInfo);

	void AddMember(TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx, u16 wChnlIndx = TP_INVALID_INDEX);
	void DelMember(TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx);

	void AdjustForceActive(TAudMixInfo* ptInfo, u16 wForceActiveEpID = TP_INVALID_INDEX);

	void AdjustAudMixMember( TAudMixInfo* ptMixRes, TAudMixMemberInfo* ptMixNewMember, u16 wSyncEp = TP_INVALID_INDEX, u16 wScreeIndex = TP_INVALID_INDEX);

	void GetMixerChnInAddr(TAudMixInfo* ptInfo, TTPMediaTransAddr& tAddr, u16 wEpID, u16 wScrIndx);
	void GetMixerChnOutAddr(TAudMixInfo* ptInfo, TServiceAddr& tAddr, u16 wEpID, u16 wScrIndx);

	void SetMediaKey(const TTPQTMediaKeyInfo& tInfo, TAudMixInfo* ptInfo = NULL);
protected:
	TAudMixInfo* FindByEqpID(u16 wEqpID);
	TAudMixInfo* FindIdle();
	void AudMixExciteSpeakerEp(TAudMixInfo* ptInfo, u8 byChanId);

private:
	//Xmpu msg
#ifdef _USE_XMPUEQP_
	TAudMixInfo*  AssignXmpuMixer(AudMixerCB pCB, CUmsConfInst* ptUsrParam, u16 wChnlLimit = 0);
	void ReleaseXmpuMixer(TAudMixInfo* ptInfo);
	void OnXmpuStartVacReq( TAudMixInfo* ptInfo);
	void OnXmpuStopVac(TAudMixInfo* ptInfo);
	void SetXmpuMixerSyncChnl(TMixSync& tSync);
	void CheckDelXmpuMember(TAudMixInfo* ptInfo);

	void AddXmpuMember(TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx, u16 wChnlIndx = TP_INVALID_INDEX);
	void DelXmpuMember(TAudMixInfo* ptInfo, u16 wEpID, u16 wScrIndx);

	void AdjustXmpuForceActive(TAudMixInfo* ptInfo, u16 wForceActiveEpID = TP_INVALID_INDEX);

	void OnXmpuAudMixDisConnect( CTpMsg *const ptMsg );
	void OnXmpuStartMixRsp( CTpMsg *const ptMsg );
	void OnXmpuAddMemberRsp( CTpMsg *const ptMsg );

	void OnXmpuAudMixExciteInd(CTpMsg *const ptMsg);
	void OnXmpuVoiceDetectionNty(CTpMsg *const ptMsg);

    void ProcMixCb(CTpMsg *const ptMsg);
#endif

private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	void EapuClear();
	friend class CNetPortMgr;
	
protected:

	TAudMixInfo	m_atAudMix[MAX_AUDMIX_MDL_NUM];
};


#endif // _h_umsvmp_h__