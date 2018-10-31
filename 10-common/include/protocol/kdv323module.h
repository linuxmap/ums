#ifndef H323MODULE_H
#define H323MODULE_H

#include "kdvtype.h"
#include "kdv323common.h"
#include "modulecallstruct.h"


extern BOOL32 g_bIsStackNull; 

typedef BOOL32 (PROTO_CALLBACK* H323CBNewCallIncoming)	(HMDLCALL hCall, TModuleCallInfo* pcCallInfo);
typedef BOOL32 (PROTO_CALLBACK* H323CBCallDisconnected)	(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);
typedef BOOL32 (PROTO_CALLBACK* H323CBCallConnected)	(HMDLCALL hCall, HMDLAPPCALL hAppCall, TModuleCallInfo* pcCallInfo);
//added by sna for interworking [20140217]
typedef BOOL32 (PROTO_CALLBACK* H323CBPeerRecvCapbility)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TCallCapbility* ptPeerRecvCapbility);
//added end

typedef struct tagH323CallCBFunction
{
	H323CBNewCallIncoming m_cbNewCallIncoming;
	H323CBCallDisconnected m_cbCallDisconnected;
	H323CBCallConnected m_cbCallConnected;
	H323CBPeerRecvCapbility m_cbPeerRecvCapbility;//added by sna for interworking [20170217]

	tagH323CallCBFunction()
	{
		m_cbNewCallIncoming = NULL;
		m_cbCallConnected = NULL;
		m_cbCallConnected = NULL;
		m_cbPeerRecvCapbility = NULL;
	}
}TH323CallCBFunction;


typedef BOOL32 (PROTO_CALLBACK* H323CBChannelConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo* atChanConnectInfo, u8 bySize );
typedef BOOL32 (PROTO_CALLBACK* H323CBChannelDisconnected)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , u8 byReason );
typedef BOOL32 (PROTO_CALLBACK* H323CBChannelFlowCtrl)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , u16 wBitrate );
typedef BOOL32 (PROTO_CALLBACK* H323CBChannelFastUpdate)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan );
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamIncoming)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, TCallCapbility* ptDualCap );
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, TChanConnectedInfo* ptChanInfo );
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamReject)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan );
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamStop)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan );
//added by sna for interworking's reopen [20140217]
typedef BOOL32 (PROTO_CALLBACK* H323CBChanDisconnectedEx)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , TChanConnectedInfo* ptChanDisconnectInfo);
//added end 
typedef BOOL32 (PROTO_CALLBACK* H323CBFeccChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TFeccCapbility *ptFeccCap);
typedef BOOL32 (PROTO_CALLBACK* H323CBMMcuChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptChanInfo);
typedef BOOL32 (PROTO_CALLBACK* H323CBFeccMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct *ptFeccStruct, TMDLTERLABEL *ptSrcLabel, TMDLTERLABEL *ptDstLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBMMcuMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, u16 wEvent, u8* pBuf, u16 wLen );


typedef struct tagH323ChannelCBFunction
{
	H323CBChannelConnected m_cbChannelConnected;
	H323CBChannelDisconnected m_cbChannelDisconnected;
	H323CBChannelFlowCtrl m_cbChannelFlowCtrl;
	H323CBChannelFastUpdate m_cbChannelFastUpdate;
	H323CBDualStreamIncoming m_cbDualStreamIncoming;
	H323CBDualStreamConnected m_cbDualStreamConnected;
	H323CBDualStreamReject m_cbDualStreamReject;
	H323CBDualStreamStop m_cbDualStreamStop;

	H323CBChanDisconnectedEx m_cbChanDisconnectedEx; //added by sna for interworking's reopen [20140217] 
	H323CBFeccChannelConnected m_cbFeccChannelConnected;
	H323CBFeccMsg m_cbFeccMsg;
	H323CBMMcuChannelConnected m_cbMMcuChannelConnected;
	H323CBMMcuMsg m_cbMMcuMsg;

	tagH323ChannelCBFunction()
	{
		memset( this , 0 , sizeof(tagH323ChannelCBFunction) );
	}
}TH323ChannelCBFunction;


typedef BOOL32 (PROTO_CALLBACK* CBRegResult)( HMDLREG hReg , HMDLAPPREG hAppReg , u8* pbuf , u16 wLen );
typedef BOOL32 (PROTO_CALLBACK* CBOnlineList)( HMDLREG hReg , HMDLAPPREG hAppReg , u32 dwAppId, u8* pbuf , u16 wLen );
typedef BOOL32 (PROTO_CALLBACK* H323CBConfEvent)( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );

//conf
// typedef BOOL (H323CALLBACK* H323CBMultipleConf)( HMDLCALL hCall, HMDLAPPCALL hAppCall ); //通知开始多点会议
// typedef BOOL (H323CALLBACK* H323CBConfList)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERINFOLIST tTerInfoList );  //回调与会列表
// typedef BOOL (H323CALLBACK* H323CBTerLabel)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );   //回调MC分配的TerLabel
// typedef BOOL (H323CALLBACK* H323CBConfYouAreSee)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel); //回调当前发言人(YouAreSeeing)
// typedef BOOL (H323CALLBACK* H323CBSeeByAll )( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );  //回调被看指示
// typedef BOOL (H323CALLBACK* H323CBConfTerJoin)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel ); //回调加入会议的终端
// typedef BOOL (H323CALLBACK* H323CBConfTerLeft)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel ); //回调离开会议的终端
// typedef BOOL (H323CALLBACK* H323CBConfTerIDListRequest)( HMDLCALL hCall, HMDLAPPCALL hAppCall );   //回调终端ID列表请求
// typedef BOOL (H323CALLBACK* H323CBConfTerLabelListRequest)( HMDLCALL hCall, HMDLAPPCALL hAppCall );  //回调终端List列表请求



//新会控接口前面的不用
typedef BOOL32 (PROTO_CALLBACK* H323CBTerFloorReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBTerChairReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBTer239TokenReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CB239TokenOwnerToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );


//chiar请求的回调
typedef BOOL32 (PROTO_CALLBACK* H323CBChairSendThisSource)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
typedef BOOL32 (PROTO_CALLBACK* H323CBChairBroadcastTerminal)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBChairCancelBroadcastTerminal)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBSendThisSourceRsp)( HMDLCALL hCall, HMDLAPPCALL hAppCall, BOOL32 bIsSuccess );

//ter侧回调
typedef BOOL32 (PROTO_CALLBACK* H323CBMultipleConf)( HMDLCALL hCall, HMDLAPPCALL hAppCall );
typedef BOOL32 (PROTO_CALLBACK* H323CBSelfTerLabel)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBChairTokenOwner)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );
typedef BOOL32 (PROTO_CALLBACK* H323CBTerList )( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERINFOLIST tTerList );
typedef BOOL32 (PROTO_CALLBACK* H323CBYouAreSeeing)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );
typedef BOOL32 (PROTO_CALLBACK* H323CBSeeByAll)( HMDLCALL hCall, HMDLAPPCALL hAppCall );


typedef BOOL32 (PROTO_CALLBACK* H323CBTerFloorReqToChair)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );

typedef struct tagH323ConfCallBack
{
//ter侧回调
	H323CBMultipleConf m_cbMultipleConf;
	H323CBSelfTerLabel m_cbSelfTerLabel;
	H323CBChairTokenOwner m_cbChairTokenOwner;
	H323CBTerList m_cbTerList;
	H323CBYouAreSeeing m_cbYouAreSeeing;
	H323CBSeeByAll m_cbSeeByAll;
	//chair回调
	H323CBTerFloorReqToChair m_cbTerFloorReqToChair;
	H323CBSendThisSourceRsp m_cbSendThisSouceRsp;
	
	//mc侧回调
	H323CBTerFloorReqToMc m_cbTerFloorReqToMc;
	H323CBTerChairReqToMc m_cbTerChairReqToMc;
	H323CBChairSendThisSource m_cbChairSendThisSource;
	H323CBChairBroadcastTerminal m_cbChairBroadcastTerminal;
	H323CBChairCancelBroadcastTerminal m_cbChairCancelBroadcastTerminal;
	H323CBTer239TokenReqToMc m_cbTer239TokenReqToMc;
	H323CB239TokenOwnerToMc m_cb239TokenOwnerToMc;
	
	tagH323ConfCallBack()
	{
		memset( this , 0 , sizeof(tagH323ConfCallBack) );
	}
}TH323ConfCallBack;


typedef struct tagH323Cfg
{
	s32 m_nh323ServiceAppId;
	s32 m_nh323StackinAppid;
	s32 m_nh323StackoutAppid;

	u32 m_dwh323StackIp;
	u8  m_abyh323StackIp_ipv6[16];

	u16 m_wh225port;
	u16 m_dwh323StackPortStart;
	u16 m_dwh323StackPortEnd;

	u16 m_wTotalCallNum;
	u16 m_wTotalRegNum;

	emModuleEndpointType m_emEndpointType;

	TH323CallCBFunction m_tCallCBFuntion;
	TH323ChannelCBFunction m_tChannelCBFuntion;
	TH323ConfCallBack m_cbConfCallBack;
	CBRegResult     m_cbRegResult;
	H323CBConfEvent m_cbConfEvent;
	CBOnlineList    m_cbOnlineList;

	BOOL32          m_bOptimizeMem;			//初始化是否需要对stack模块内存优化选项(rasInit)

#ifdef _ENABLE_QUANTUM_PROJECT_
	TQtInitParam	m_tQtInitParam;		//二期量子，初始化量子参数
#endif

	tagH323Cfg()
	{
		m_nh323ServiceAppId = -1;
		m_nh323StackinAppid = -1;
		m_nh323StackoutAppid = -1;

		m_wh225port = 1720;
		m_dwh323StackIp = 0;

		memset(m_abyh323StackIp_ipv6 , 0 , sizeof(m_abyh323StackIp_ipv6) );

		m_wTotalCallNum = 10;
		m_wTotalRegNum = 10;
		m_dwh323StackPortStart = 60000;
		m_dwh323StackPortEnd = 60000+4*10;

		m_emEndpointType = emModuleEndpointMT;

		m_cbRegResult = NULL;
		m_cbConfEvent = NULL;
		m_cbOnlineList = NULL;
		m_bOptimizeMem = TRUE;
	}

}TH323Cfg;

class H323Module
{
	//Call API:
public:
	
	//H323 module init function
	static BOOL32 H323ModuleInit( TH323Cfg &tCfg );
	//H323 module start recv
	static BOOL32 H323ModuleStart();
	//H323 module stop recv
	static BOOL32 H323ModuleStop();
	//H323 module exit function
	static BOOL32 H323ModuleExit();
	//H323 module create a new outgoing call
	static BOOL32 H323ModuleMakeOutgoingCall( HMDLAPPCALL hAppCall, TModuleCallInfo* ptModuleCallInfo, TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, HMDLAPPCONFID hAppConfId = 0, TMDLTERLABEL* pTerLabel = NULL, TFeccCapbility* ptFeccCap = NULL,TMMcuCapbility  *ptMMcuCap  = NULL);
	
	static BOOL32 H323ModuleCallAnswer( HMDLCALL hCall, HMDLAPPCALL hAppCall, TModuleCallInfo* ptModuleCallInfo, TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, HMDLAPPCONFID hAppConfId = 0, TMDLTERLABEL* pTerLabel = NULL, TFeccCapbility* ptFeccCap = NULL,TMMcuCapbility  *ptMMcuCap  = NULL);
	
	static BOOL32 H323ModuleCallReject( HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason );
	
	static BOOL32 H323ModuleCallHangup( HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason );

	//added by sna for interworking [20140214]
	static BOOL32 H323LocalSendCapSet( HMDLCALL hCall, HMDLAPPCALL hAppCall , TCallCapbility* ptSendCapbility);
	static BOOL32 H323IWReopenChannel( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan  , TChanConnectedInfo * ptReopenChanInfo);
	//Channel API:
public:
	static BOOL32 CloseChannel( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );
	static BOOL32 FlowCtrl( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan , u16 wBitrate );
    static BOOL32 FastUpdate( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan  );
	static BOOL32 DualSteam( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, TCallCapbility* ptDualCap);
	
	/*=============================================================================
	函 数 名：DualStreamAnswer
	功	  能：answer dual or stop dual(only interworking used)
	参	  数：TChanConnectedInfo* ptDualInfo : [in] the capbility of answer dual
			  BOOL bIsSuc: TRUE is answer,FALSE is stop and ptDualInfo is null
	返 回 值：send message succeed return TRUE,otherwise return FALSE
	=============================================================================*/
	static BOOL32 DualStreamAnswer( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, BOOL32 bIsSuc, TChanConnectedInfo* ptDualInfo );
	static BOOL32 DualStreamStop( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );

    //added by jacky for manual channel on/off
    static BOOL32 ChannelSwitch( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, BOOL32 bActive);
    //end of added by jacky for manual channel on/off 
    
	//added by sna for dual channel on/off[20130107]
	static BOOL32 H323ModuleChanEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wEvent, u8* pBuf, u16 wLen);
	//end of added by sna[20130107]

	// REG API
public:
	static BOOL32 Regist( HMDLREG hReg , HMDLAPPREG hAppReg , TRegistReq* ptRegInfo );
	static BOOL32 UnRegist( HMDLREG hReg , HMDLAPPREG hAppReg );
	static BOOL32 RegistUpdate( HMDLREG hReg, HMDLAPPREG hAppReg, TRegistReq* ptRegInfo );

public:
	// CONFERENCE
	static BOOL32 H323ModuleConfEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );

	//cascade MMcu
	static BOOL32 H323ModuleMMcuEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wEvent, u8* pBuf, u16 wLen);

	// 新接口  上面的不用
	// mc用
	static BOOL32 H323MCStopConference( HMDLAPPCONFID hAppConfId );
	static BOOL32 H323MCMakeSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCWithdrawSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCMakeChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCWithdrawChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL32 H323MCCancelSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL32 H323MCAddTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );
	static BOOL32 H323MCDelTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );

	// chair用
	static BOOL32 H323ChairCancelMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL32 H323ChairSendThisSourceCmd( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerlabel );
	static BOOL32 H323ChairCancelSendThisSource( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL32 H323ChairBroadcastTerminalReq( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
	static BOOL32 H323ChairBroadcastTerminalCmd( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
	static BOOL32 H323ChairCancelBroadcastTerminal( HMDLCALL hCall, HMDLAPPCALL hAppCall );

	// ter用
	static BOOL32 H323TerMakeMeSpeaker( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL32 H323TerMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	
public:
	static BOOL32 H323SendFeccMsg( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccAction, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );
	static BOOL32 H323SetFeccStreamId( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStreamIdInfo tFeccStreamIdInfo);
	
	static BOOL32 H323SetStaticNAT(u32 dwNATIP);
public:
	static BOOL32 H323OnlineListReq( EmModuleGetGKInfoType emType, HMDLREG hReg, HMDLAPPREG hAppReg, u32 dwAppId );

private:
	//added by sna for print capbility form upper level [20140219]
	//bIsOnlyDual变量：DualStream的时候只打印双流发送能力。
	static void H323PrintCapbility( TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, BOOL32 bIsOnlyDual=FALSE );
	//added end

public:
	static u16 m_wh323serviceAppId;
	static TH323ChannelCBFunction m_tCHannelCBFuntion;
	static TH323CallCBFunction m_tCallCBFunction;
//	static TH323ConfCBFunction m_tConfCBFunction;
	static TH323ConfCallBack m_tConfCallBack;
	static CBRegResult     m_CbRegResult;
	static H323CBConfEvent m_CbConfEvent;
//	static H323CBFeccMsg   m_CbFeccMsg;
	static CBOnlineList    m_CbOnlineList;
};

//打印
static u8 g_byMDLLogLevel = 0;
static s8 g_achCallerAlias[MAX_ALIAS_LEN]  = "all";
static u8 g_byModuleType = (int)emModuleAll;
static u16 g_wCallNum = 0;
static emCallBy g_emCallBy = emModuleCallByNum;

#define IS_LOG(n)  (n <= g_byMDLLogLevel)
#define MODULE_PRINT_BUFFERSIZE  1024

PROTO_EXTERN_API void h323setlog( u8 byLevel );
PROTO_EXTERN_API void h323mlog( u8 byLevel );
PROTO_EXTERN_API void h323setcallbyname( s8* pchCallerAlias );
PROTO_EXTERN_API void h323setcallbynum( u8 wCallNum );
PROTO_EXTERN_API void h323setlogtype( u8 byModuel );
PROTO_EXTERN_API void h323setcallby( u8 byCallBy );
PROTO_EXTERN_API void h323help();
PROTO_EXTERN_API void kdv323modulehelp();
PROTO_EXTERN_API void h323showreg();
PROTO_EXTERN_API void h323showcall( u8 i );
PROTO_EXTERN_API void h323showconf();
PROTO_EXTERN_API void h323ver();
PROTO_EXTERN_API void h323mver();

void ModulePrintf( emModuleType ModuleType, u16 byLogLevel, s8* pchCallerAlias, u16 byCallNum, const char* pFormat, ... );

#ifdef _ENABLE_QUANTUM_PROJECT_
/*====================================================================
函	 数   名: kdvModuleQuantumInit
功	      能: 设置本端量子加密初始化参数（若有配置变更，就需调该接口）
算 法 实  现: 
引用全局变量: 
输入参数说明: tQuantumInitParam			- 本端量子加密初始化参数
			 
返   回   值:
====================================================================*/
PROTO_API BOOL32 kdvModuleQuantumInit(TQtInitParam &tQuantumInitParam);
#endif

#endif

