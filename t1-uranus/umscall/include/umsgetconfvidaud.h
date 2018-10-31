#ifndef _umsgetconfvidaudss_h_
#define _umsgetconfvidaudss_h_


#include "umscommonstruct.h"
#include "callinnerstruct.h"
#include "umsconfinst.h"
#include "umsvmp.h"


#define   GET_CONF_BRD_VID_AUD_MAX_USER		5
#define   GET_CONF_VMP_VID_MAX_USER			16
#define   GET_EP_SCREEN_STREAM_MAX_USER		192

typedef struct tagTBroadCastInfo
{
	BOOL32          m_bUsed;
	TLogUser		m_tUser;

	CDsListInfo	    m_cDsInfo;
	TTPTransAddr	m_atVidAddr[TP_MAX_STREAMNUM];   
	TTPTransAddr	m_tSingleVidAddr;             
	
	TTPTransAddr	m_atAudAddr[TP_MAX_STREAMNUM];	
	TTPTransAddr	m_tAudMixAddr;
	
	tagTBroadCastInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_bUsed   = FALSE;
		m_tUser.Clear();
		m_cDsInfo.Clear();
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
		{
			m_atVidAddr[wIndex].Clear();
			m_atAudAddr[wIndex].Clear();
		}
		m_tSingleVidAddr.Clear();
		m_tAudMixAddr.Clear();
	}
}TBroadCastInfo;


typedef struct tagTGetVmpInfo
{
	BOOL32          m_bUsed;
	TLogUser        m_tUser;
	TBrdVmpRes*		m_ptVmp;

	CDsListInfo	    m_cToVmpVid;
	TUmsVidFormat	m_tFormat;
	TTPTransAddr    m_tRtpAddr;         // 码流目的地址(来自umc请求)
	
	tagTGetVmpInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_bUsed   = FALSE;
		m_tFormat.Clear();
		m_ptVmp   = NULL;
		m_cToVmpVid.Clear();
		m_tUser.Clear();
		m_tRtpAddr.Clear();
	}
}TGetVmpInfo;


typedef struct tagTUmsGetEpScreenInfo
{
	u16				m_wEpID;
	u16				m_wScreenID;

	TLogUser		m_tUser;
	BOOL32          m_bUsed;
	
	CDsListInfo	    m_cDsInfo;
	u16				m_wVidHandle;
	TTPTransAddr	m_tVidAddr;                
	TTPTransAddr	m_tAudAddr;	
	TTPTransAddr	m_tAudMixAddr;

	tagTUmsGetEpScreenInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wEpID		= TP_INVALID_INDEX;
		m_wScreenID	= TP_INVALID_INDEX;
		m_bUsed		= FALSE;
		m_wVidHandle = TP_INVALID_INDEX;
		m_tUser.Clear();
		m_cDsInfo.Clear();
		m_tVidAddr.Clear();
		m_tAudAddr.Clear();
		m_tAudMixAddr.Clear();
	}

}TUmsGetEpScreenInfo;

class CGetConfVidAudMgr
{

public:	

	CGetConfVidAudMgr(CUmsConfInst* pcInst):m_pcConf(pcInst) {}

    ~CGetConfVidAudMgr(){}

	void Enter() {Clear();}	
 	void Exit(){}
    void OnStopConf();

	BOOL32 HandlerFromUmc(CTpMsg *const ptMsg);

	void Show();

protected:

	void Clear();

	u16 GetExistVmpUser(TLogUser tUser, u16 wEqpId);
	u16 GetIdleVmpUser();
	BOOL32 ReleaseVmpInfo(u16 wIndex);

	u16 GetExistBroadCastUser(TLogUser tUser);
	u16 GetIdleBroadCastUser();
	BOOL32 ReleaseBroadCastUser(u16 wIndex);
	void OnReleaseGetConfBrdVidAud( CTpMsg* const ptMsg );
    void OnGetConfBrdVidAudReq( CTpMsg* const ptMsg );
	void OnGetConfBrdVidAudAskKey(CTpMsg* const ptMsg);

	void OnGetConfVmpVidReq( CTpMsg* const ptMsg );
	void OnReleaseConfVmpVidReq( CTpMsg* const ptMsg );
	void OnGetConfVmpVidAskKeyReq( CTpMsg* const ptMsg );

	u16 GetIdleEpScreenUser();
	u16 GetExistEpScreenUser(TLogUser tUser, TGetEpScreenInfo tInfo);
	BOOL32 ReleaseEpScreenUser(u16 wIndex);

	void OnGetEpScreenStreamReq( CTpMsg* const ptMsg );
	void OnReleaseEpScreenStreamReq( CTpMsg* const ptMsg );
	void OnGetEpScreenAskKeyReq( CTpMsg* const ptMsg );
	
public:
	void GetVmpCB( TBrdVmpRes* ptRes, EmBrdVmpCBOprType emOpr);

private:

	TBroadCastInfo		m_atBroadCastInfo[GET_CONF_BRD_VID_AUD_MAX_USER];
	TGetVmpInfo			m_atVmpInfo[GET_CONF_VMP_VID_MAX_USER];
	TUmsGetEpScreenInfo	m_atEpSreenInfo[GET_EP_SCREEN_STREAM_MAX_USER];


    CUmsConfInst*   m_pcConf;

};



#endif