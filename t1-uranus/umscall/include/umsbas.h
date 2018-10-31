#ifndef _h_umsbas_h__
#define _h_umsbas_h__
#include "umsconfinst.h"
#include "tphandle.h"
#include "eqpinterface.h"
#include "callinnerstruct.h"
#include "umsvmp.h"


#define BAS_CHN_RES_MAX_NUM 32

#define VID_FRAME_RATE_60 60
#define VID_FRAME_RATE_50 50
#define VID_FRAME_RATE_30 30
#define VID_FRAME_RATE_25 25

#define ASKFRAME_TOBAS_TIME_200MS 200

#ifdef _USE_XMPUEQP_

typedef struct tagtXmpuBasCbData{
    void *pService;
	void *pRes;
	void *pData;
	void *pParam;
    tagtXmpuBasCbData()
	{
		memset(this, 0, sizeof(tagtXmpuBasCbData));
	}
}tXmpuBasCbData;

#endif

typedef struct tagTAudBasScreen
{

#ifdef _USE_XMPUEQP_
    tXmpuAuddBasRes  m_tXmpuAudBas;
#endif
	TBasEqpRes m_tEqpRes;
	TUmsAudFormat	m_tSndAudFmt;
	TUmsAudFormat	m_atAudFmt[UMS_AUDBAS_ENC_NUM];
	tagTAudBasScreen()
	{
		memset(this, 0, sizeof(tagTAudBasScreen));
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTAudBasScreen));
		
		m_tSndAudFmt.m_emFormat = emTPAEnd;

		for ( u16 wIndex = 0; wIndex < UMS_AUDBAS_ENC_NUM; wIndex ++ )
		{
			m_atAudFmt[wIndex].m_emFormat = emTPAEnd;
		}
	}

	u16 FindIndex(EmTpAudioFormat emFmt)
	{
		for ( u16 wIndex = 0; wIndex < UMS_AUDBAS_ENC_NUM; wIndex ++ )
		{
			if( m_atAudFmt[wIndex].m_emFormat == emFmt )
			{
				return wIndex;
			}
		}

		return TP_INVALID_INDEX;
	}

	BOOL32 IsBasValid(void)
	{
#ifdef _USE_XMPUEQP_
        return (m_tXmpuAudBas.m_dwEqpID != 0);
#else
        return m_tEqpRes.IsValid();
		
#endif
	}

	void ClearBas(void)
	{
#ifdef _USE_XMPUEQP_
        m_tXmpuAudBas.Clear();
#else
		m_tEqpRes.Clear();
#endif
		return;
	}

	u16 GetBasEqpId(void)
	{
#ifdef _USE_XMPUEQP_
        return m_tXmpuAudBas.m_dwEqpID;
#else
		return m_tEqpRes.m_tBasChnInfo.m_byEqpID;
#endif
	}

}TAudBasScreen;

class CSpeakerBas : public CNodeBase
{
public:
	CSpeakerBas():CNodeBase(em_Node_SpeakBas){m_wScreenEx = 0;}
	
public:
	TBasParam::EmAssignType m_emAsgType;
	TTPBasVidParam	m_tVidPara;		  //发言人后适配分配参数
	TTPBasVidParam	m_tRealVidPara;   //发言人后适配实际参数
	TUmsVidFormat	m_tSndVidFormat;

	u16             m_wScreenEx;      // add for brdvmp 目前只有下级ums用到
	TTPBasVidParam	m_tRealVidParaEx;  
	TUmsVidFormat	m_tSndVidFormatEx;

	u16				m_wNeedAdjustLvl;
	TUmsVidFormat	m_tNeedAdjustFmt;

#ifdef _USE_XMPUEQP_
    tXmpuVidBasRes  m_atXmpuBas[TP_MAX_STREAMNUM];//看发言人
#else
#endif
	TBasEqpRes		m_atBas[TP_MAX_STREAMNUM];//看发言人

	CDsListInfo		m_tDsList;

	void ClearExInfo()
	{// 初始值是0
		m_wScreenEx = 0;
	}

	BOOL32 IsExInfo(u16 wScreen)
	{// 屏号加1
		wScreen++;
		return (0 != m_wScreenEx && wScreen == m_wScreenEx);
	}

	BOOL32 IsBasValid(u16 wScreenIndex)
	{
		if (wScreenIndex >= TP_MAX_STREAMNUM)
		{
            return FALSE;
		}

#ifdef _USE_XMPUEQP_
        return (m_atXmpuBas[wScreenIndex].m_dwEqpID != 0);
#else
		return m_atBas[wScreenIndex].IsValid();
#endif
	}

};

class CDualBas : public CNodeBase
{
public:
	CDualBas():CNodeBase(em_Node_DualBas){}
	
public:
	TBasParam::EmAssignType m_emAsgType;	
	TUmsVidFormat	m_tEpFormat;	//双流源格式
	TTPBasVidParam	m_tVidPara;		//双流后适配分配参数
	TTPBasVidParam	m_tRealVidPara; //双流后适配实际参数
	
	u16				m_wNeedAdjustLvl;
	TUmsVidFormat	m_tNeedAdjustFmt;

#ifdef _USE_XMPUEQP_
    tXmpuVidBasRes  m_tXmpuBas;    //看双流
#endif
	TBasEqpRes		m_tBas;			//看双流
};

class CChairBas : public CNodeBase
{
public:
	CChairBas():CNodeBase(em_Node_ChairBas){}
	
public:	

#ifdef _USE_XMPUEQP_
	tXmpuVidBasRes  m_atXmpuBas[TP_MAX_STREAMNUM];//看主席
#endif

	TBasEqpRes		m_atBas[TP_MAX_STREAMNUM];//看主席
	
	BOOL32 IsBasValid(u16 wIndex)
	{
#ifdef _USE_XMPUEQP_
        return (m_atXmpuBas[wIndex].m_dwEqpID != 0);
#else
        return m_atBas[wIndex].IsValid();
#endif
	}
};


//会议中的bas管理
typedef struct tagTConfBasMgr
{		
	BOOL32			m_bSpeaker;
	BOOL32			m_bChair;
	BOOL32			m_bSel;
	BOOL32			m_bDual;

	CScreenBasRes	m_atBasChsRes[BAS_CHN_RES_MAX_NUM];

	tagTConfBasMgr() { Clear(); }
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTConfBasMgr));
		m_bSpeaker = FALSE;
		m_bChair = FALSE;
		m_bDual = FALSE;
		m_bSel = FALSE;
	}

	u16 FindIdleBasChnRes()
	{
		for (u8 byIndx = 0; byIndx < BAS_CHN_RES_MAX_NUM; byIndx ++ )
		{
            if(m_atBasChsRes[byIndx].IsBasValid())
			{
				continue;
			}

			if ( byIndx < TP_MAX_STREAMNUM )
			{//前三个位置 固定留给选看和轮询
				continue;
			}

			return byIndx;
		}

		return TP_INVALID_INDEX;
	}

	u16 FindBasChnResByIndx( CScreenBasRes* ptScreenBasRes )
	{
		for (u8 byIndx = 0; byIndx < BAS_CHN_RES_MAX_NUM; byIndx ++ )
		{
			if(&m_atBasChsRes[byIndx] == ptScreenBasRes)
			{
				return byIndx;
			}
		}

		return TP_INVALID_INDEX;
	}

    CScreenBasRes* BasChnRes(u16 wIndex) { return &m_atBasChsRes[wIndex]; }

}TConfBasMgr;

class CUmsConfInst;
class CUmsBas  : public CTpHandler
{
public:
	CUmsBas(CUmsConfInst* pcInst);
	~CUmsBas();
	
	void Show();

	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	BOOL32 HandlerFromStack( CTpMsg *const ptMsg );
	
	TConfBasMgr* GetBasMgr(){ return &m_tConfBasMgr; }
	CSpeakerBas* GetSpeakerBas(){ return &m_cSpeaker; }
	CDualBas* GetDualBas(){ return &m_cDual; }
	CChairBas* GetChairBas(){ return &m_cChair; }
	void OnAskFrameTime();
	u16	GetPriFmtNum() { return m_wPriNum; }
	u16	GetDualFmtNum() { return m_wDualNum; }

	/*开会就为发言人分配bas 按照最大三屏分配*/
	BOOL32 IsSpeakerNeedBas( TUmsVidFormat& tRcv , u16 wScreenIndex = TP_INVALID_INDEX);
	void AdjustSpeakerBas(u16 wIndex = TP_INVALID_INDEX, BOOL32 bAdjustAud = TRUE);//切换发言人调用 调整后适配
	void ReleaseSpeakerBas();
#ifdef _USE_XMPUEQP_
	BOOL32 AssignSpeakerBasFromXmpu(void);
	void SetXmpuSpeakerBasEncCmd(u16 wIndex = TP_INVALID_INDEX, BOOL32 bAdjustAud = TRUE);
#else
	BOOL32 AssignSpeakerBas();
	void SetSpeakerBasEncCmd(u16 wIndex = TP_INVALID_INDEX, BOOL32 bAdjustAud = TRUE);//切换发言人调用 调整后适配
#endif
	void AdjustSpeakerBasForBrdVmp(BOOL32 bBrdVmpOn);  // 对下级ums，brdvmp会占用中间路发言人适配，但是此时brdvmp的格式为主席（即上级ums的发送格式）
	BOOL32 SeeSpeakerAskFrameToBas(u16 wScreenIndx);
	void GetInChnSpeakerVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx );
	void GetOutChnSpeakerVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx , TUmsVidFormat& tVidFormat );

	/*双流开启后才分配*/
	BOOL32 IsDualNeedBas(TUmsVidFormat& tRcv);
	BOOL32 AssignDualBas();  // 分配所需的双流适配资源，如果已申请，返回ture
	void ReleaseDualBas();
	void AdjustDualBas();
#ifdef _USE_XMPUEQP_
    BOOL32 AssignDualBasFromXmpuEqp(void);
	void SetXmpuDualVidBasEncCmd(void);
#else
    BOOL32 AssignDualBasFromOldEqp(void);
	void SetDualVidBasEncCmd(void);
#endif
	BOOL32 SeeDualAskFrameToBas();
	void GetInDualVidAddr(TTPMediaTransAddr& tAddr);
	void GetOutDualVidAddr(TTPMediaTransAddr& tAddr, TUmsVidFormat& tVidFormat );


	//开会就分配发言人看主席	
	void ReleaseChairBas();
	void AdjustChairBas(u16 wIndex = TP_INVALID_INDEX);//开启适配 调整适配
#ifdef _USE_XMPUEQP_
    BOOL32 AssignChairBasFromXmpu(void);
	void SetXmpuChairVidBasEncCmd(u16 wIndex);
#else
	BOOL32 AssignChairBas();
	void SetChairVidBasEncCmd(u16 wIndex);
#endif
	BOOL32 SeeChairAskFrameToBas(u16 wScreenIndx);	
	void GetInChnChairVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx );
	void GetOutChnChairVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx );

	BOOL32 IsChairInBas()
	{ 
		return (m_tConfBasMgr.m_bChair && m_cChair.IsBasValid(MIDSCREENINDEX));
	}

	CDsListInfo&	GetChairToBasDsList()		{ return m_tChairToBasDs; }


	/*根据屏分配接口 供业务调用*/
	BOOL32 AssignScreenBas( CScreenBasRes*& pcBasRes, BOOL32 bSingleOut = TRUE );
#ifdef _USE_XMPUEQP_
	BOOL32 AssignScreenBasFromXmpuEqp( CScreenBasRes*& pcBasRes, BOOL32 bSingleOut);
	void SetXmpuScreenBasEncCmd(CScreenBasRes* ptScreenBasRes, u16 wSrcEp, u16 wScreenIndx, u8 byFormatNum, TUmsVidFormat atVidFormat[]);
#else 
	BOOL32 AssignScreenBasFromOldEqp( CScreenBasRes*& pcBasRes, BOOL32 bSingleOut);
	void SetScreenBasEncCmd(CScreenBasRes* ptScreenBasRes, u16 wSrcEp, u16 wScreenIndx, u8 byFormatNum, TUmsVidFormat atVidFormat[]);
#endif
	void AdjustScreenBas(CScreenBasRes* ptScreenBasRes, u16 wSrcEp, u16 wScreenIndx, u8 byFormatNum = 1, TUmsVidFormat atVidFormat[] = NULL);
	void ReleaseScreenBas(CScreenBasRes*& ptScreenBasRes);
	void AskFrameToScreenBas(CScreenBasRes* ptScreenBasRes);
	
	void GetInChnVidAddr(TTPMediaTransAddr& tAddr, CScreenBasRes* ptScreenRes);
	void GetOutChnVidAddr(TTPMediaTransAddr& tAddr, CScreenBasRes* ptScreenRes, TUmsVidFormat& tVidFormat );

	//////////////////////////////////////////////////////////////////////////
	//音频适配
   
#ifdef _USE_XMPUEQP_
    BOOL32 AssignAudBasFromXmpu(void);
	void SetSpeakerAudBasSyncForXmpu(void);
	void SetChairAudBasSyncForXmpu(void);
#else 
	BOOL32 AssignAudBas();
	void SetSpeakerAudBasSync();
	void SetChairAudBasSync();
#endif
	void RealseAudBasByScreen(TAudBasScreen *ptScreenBas);
	void ReleaseAudBas();

     // 发言人音频适配
#ifdef _USE_XMPUEQP_
	void SetXmpuSpeakerAudBasEncCmd(void);
#else
	void SetSpeakerAudBasEncCmd(void);
#endif
	void AdjustSpeakerAudBas();
	BOOL32	IsSpeakerNeedAudBas(EmTpAudioFormat emFmt);
	void GetSpeakerAudBasInAddr( u16 wScreenIndx, TTPDsFrom& tAddr);
	void GetSpeakerAudBasOutAddr(u16 wScreenIndx, EmTpAudioFormat emFmt, TTPDsFrom& tAddr);

	// 单屏音频适配
	void GetSpeakerMixAudBasInAddr( TTPDsFrom& tAddr);
	void GetSpeakerMixAudBasOutAddr( EmTpAudioFormat emFmt, TTPDsFrom& tAddr);

	//主席音频适配
#ifdef _USE_XMPUEQP_
	void SetXmpuChairAudBasEncCmd(void);
#else
	void SetChairAudBasEncCmd(void);
#endif
	void AdjustChairAudBas();
	BOOL32	IsChairNeedAudBas(EmTpAudioFormat emFmt);
	void GetChairAudBasInAddr(u16 wScreenIndx, TTPDsFrom& tAddr);
	void GetChairAudBasOutAddr(u16 wScreenIndx,  EmTpAudioFormat emFmt, TTPDsFrom& tAddr);

	//双流音频适配
#ifdef _USE_XMPUEQP_
    BOOL32 AssignDualAudBasFromXmpu(void); 
	void SetXmpuDualAudBasEncCmd(void);
#else
	BOOL32 AssignDualAudBas(); 
	void SetDualAudBasEncCmd(void);
#endif
    void AdjustDualAudBas();
	void   ReleaseDualAudBas(); 
	BOOL32	IsDualNeedAudBas(EmTpAudioFormat emFmt);
	void GetDualAudBasInAddr( TTPDsFrom& tAddr );
	void GetDualAudBasOutAddr( EmTpAudioFormat emFmt, TTPDsFrom& tAddr);

	void ChairChanConnect(); //主席上线
	BOOL32 StartBas();  //开启会议调用
	void StopBas();     //退出会议调用
	
	void GetDefaultMaxFormat(TUmsVidFormat& tVidFormat)
	{
		//按照默认最大分配
		tVidFormat.m_emQualityLvl = emTPH264HP;
		tVidFormat.m_emFormat = emTPVH264;
		tVidFormat.m_emRes = emTPVHD1080p1920x1080;
		tVidFormat.m_wBitrate = Inst()->GetConfBase().m_wConfBitRate;
		tVidFormat.m_wFrameRate = 60;
	}


	// cns呼叫ums会议模板时，会议码流和双流码率会有调整
	void AdjustConfBitrateForBas(u16 wConfBitrate);

	void AdjustDualBitrateForBas(u16 wDualBitrate);

    void SetQtMediaKey(const TTPQTMediaKeyInfo& tInfo);
	void SetQtMediaKeyByBasEqp(const TBasEqpRes *ptBasEqpRes, const TTPQTMediaKeyInfo& tInfo);

#ifdef _USE_XMPUEQP_
	void SetXmpuVidBasAssignAddr(tXmpuVidBasRes *pBasRes, TTPTransAddr *pDecRtpAddr, TTPTransAddr *pEncRtcpAddr, u16 wEncAddrNum);
	void SetXmpuAudBasAssignAddr(tXmpuAuddBasRes *pBasRes, TTPTransAddr *pDecRtpAddr, TTPTransAddr *pEncRtcpAddr, u16 wEncAddrNum);

#endif

	BOOL32 IsSpeakBasAssigned();
	BOOL32 IsChairBasAssigned();

protected:

	void InstClear();

	//调试命令
	void OnBasTestShow(CTpMsg *const ptMsg);
	void BasShow(u16 wIndxPrs, u16 wIndxDual);

	void OnBasDisConnect(CTpMsg *const ptMsg);
	void OnBasNAck(CTpMsg *const ptMsg);
	void OnChangeBasSndAddr(CTpMsg *const ptMsg);
	//外设来请求关键帧
	void OnBasAskFrame(CTpMsg *const ptMsg);
	
	//替换上面的
	void BasEqpRetProc(CScreenBasRes::VidBasCBType emType, u8 byEqpID, u16 wChnIndx = TP_INVALID_INDEX);
	
	void AdjustMediaTransBasToNode();
	
	//模板接口
	BOOL32 IsMediaFormatSameLvl(TUmsVidFormat atVidFormat[], u16 wNum);
	u16 CheckAndProcConfTempFormat(TUmsVidFormat atVidFormat[], u16 wNum);
	
	void ParseConfTempFirstVidFormat();
	void ParseConfTempSecondVidFormat();
	void ParseConfTempVidFormatAPI(TUmsVidFormat m_atVideoRes[], u16 wFormatNum, u16& wAdjustIndx, TUmsVidFormat& tNeedAdjustFmt);
	void XmpuParseConfTempVidFormatAPI(TUmsVidFormat m_atVideoRes[], u16 wFormatNum, u16& wAdjustIndx, TUmsVidFormat& tNeedAdjustFmt);


	u16	GetNeedAdjustIndx(TUmsVidFormat m_atVideoRes[], u16 wFormatNum, TUmsVidFormat* ptFormat);

	void CalcBasSpeakerOutVidParam(const TUmsVidFormat& tSndVidFormat);
	void CalcBasSpeakerOutVidParamEx(const TUmsVidFormat& tSndVidFormat);
	void CalcBasDualOutVidParam(const TUmsVidFormat& tSndVidFormat);
	void CalcBasVidParamAPI(BOOL32 bDual, const TUmsVidFormat& tSndVidFormat, 
						TTPBasVidParam& tVidParam, TTPBasVidParam& tRealVidParam, u16 wAdjustIndx, TUmsVidFormat& tNeedAdjustFmt);
 
	
#ifdef _USE_XMPUEQP_
	//申请 xmpu bas 统一接口
	BOOL32 AssignXmpuBas(const TUmsVidFormat  *pBasInParam, const TTPBasVidParam *pBasOutParam, tXmpuVidBasRes *pBasRes);
	void ReleaseXmpuBas(u8 byCapCount, tXmpuVidBasRes *pBasRes);

	//处理vidbas audbas 回调
	void OnXmpuVidBasStateNty(CTpMsg *const ptMsg);
    void OnXmpuAudBasStateNty(CTpMsg *const ptMsg);
	void HandleXmpuSpeakerVidBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuVidBasRes* pBasRes, void* pData, void* param);
	void HandleXmpuChairVidBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuVidBasRes* pBasRes, void* pData, void* param);
	void HandleXmpuDualVidBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuVidBasRes* pBasRes, void* pData);
	void HandleXmpuSpeakerAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData, void* param);
	void HandleXmpuChairAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData, void* param);
	void HandleXmpuSigleAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData);
	void HandleXmpuDualAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData);

#endif

	//统一分配接口
	BOOL32 AssignBas(TBasParam::EmAssignType emType, u8 byCapCount, TBasEqpRes atBasRes[], u8 byOutNum, u16 wAsignIndx = TP_INVALID_INDEX);
	void ReleaseBas(u8 byCapCount, TBasEqpRes atEqpRes[], u16 wRelIndx = TP_INVALID_INDEX);	

	//////////////////////////////////////////////////////////////////////////
	//音频适配接入
#ifdef _USE_XMPUEQP_
	BOOL32 AssignXmpuAudBas(const TUmsAudFormat *pBasInParam, const TUmsAudFormat *pBasOutParam, u16 dwOutCh, tXmpuAuddBasRes *pBasRes);
	void ReleaseXmpuAudBas(tXmpuAuddBasRes *pBasRes);
#endif
	BOOL32 AssignBas(TBasEqpRes& tRes, u16 wReqNum = 1, u32 dwNode = 0);
private:
	CUmsConfInst* Inst()	{ return (CUmsConfInst*)m_pcInstance; }
	friend class CNetPortMgr;
	
protected:
	TConfBasMgr m_tConfBasMgr;
	CSpeakerBas	m_cSpeaker;
	CDualBas	m_cDual;
	CChairBas	m_cChair;
	CDsListInfo		m_tChairToBasDs;				//主席进适配板交换
	CDsListInfo	m_tToConfDsEqpDs;

	u16			m_wPriNum;
	TUmsVidFormat m_atPriFmt[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	u16			m_wDualNum;
	TUmsVidFormat m_atDualFmt[TP_CONF_MAX_MINOR_VIDEO_RES_NUM];

	//////////////////////////////////////////////////////////////////////////
	//音频适配接入
	
	TAudBasScreen		m_atAudBasSpeaker[TP_MAX_STREAMNUM];//发言人进适配
	TAudBasScreen		m_tAudBasSpeakerMix;//发言人混音
	TAudBasScreen		m_atAudBasChair[TP_MAX_STREAMNUM];//主席进适配
	TAudBasScreen		m_tAudBasDual;//双流源进适配
};


#endif // _h_umsvmp_h__