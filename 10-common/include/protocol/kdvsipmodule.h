#ifndef SIPMODULE_H
#define SIPMODULE_H

#include "kdvtype.h"
#include "modulecallstruct.h"
#include "modulemananger.h"
#include "tpmodulestruct.h"

#include "kdvsipcommon.h"
#include "sipconfnonstdstruct.h"
#include "sipconfnonstdmsg.h"

#define S2H_DEFAULT_MAXSENDRECVBUFFERSIZE	20480       //默认套接字发送接收缓冲大小
#define MAX_INSTANCE_PROTOCAL				192
#define SIPSERVPRINT_BUFFERSIZE				1024
#define SIP_DEFAULT_SERVER_PORT				5060
#define SIP_DEFAULT_TLS_PORT				5061
#define SIP_DEFAULT_KEEPALIVE_INTERVAL		30
#define SIP_CONFIG_NAME						"MdlTestCfg.ini"
#define MAX_FILE_PATH_LEN					256
template < class T >
T SIP_SAFE_CAST( T &t, u8 *p )
{
	if (NULL == p) return t;
	MEMCPY_CAST( &t, p, sizeof( T ) );
	return t;
}

enum EmSipModRegState
{
	emSipModSateNone,
	emSipModState2Idle,
	emSipModState2Registered,
	emSipModSate2Failed,
	emSipModState2Terminated,
	emSipModSate2Redirected,
	emSipModState2SendMsgFailed,
};

enum emModuleConfigSwitch
{
	emModuleOff = 0,
	emModuleOn	= 1,	
};

enum emModuleConfigType
{
	emTypeBigin		= 0,
	emTypeCallParam = 1,
	emTypeMainCap	= 2,
	emTypeDualCap	= 3,
	emTypeBfcp		= 4,
	emTypeFecc		= 5,
	emTypeRegister	= 6,
	emTypeAll		= 7,
	emTypeEnd
};

typedef struct tagTModuleConfig
{
	emModuleConfigSwitch m_emMdlSwitch;
	emModuleConfigType m_emType;
	tagTModuleConfig()
	{
		m_emType = emTypeBigin;
		m_emMdlSwitch = emModuleOff;
	}
}TModuleConfig;

typedef struct tagTSipModRegResult
{
	BOOL32 m_bRegistered;
	EmSipModRegState m_emRegState;
	u32 m_dwReceiveIp;
	tagTSipModRegResult()
	{
		m_bRegistered = FALSE;
		m_emRegState = emSipModSateNone;
		m_dwReceiveIp = 0;
	}
}TSipModRegResult, *PTSipModRegResult;

//TP为网真参数
typedef BOOL32 (PROTO_CALLBACK* CBNewCallIncoming)( 
			HMDLCALL hCall, 
			TModuleCallInfo *ptModParam, 
			TMdlCallCap *ptMainCap,
			TMdlTPCap *ptTPCap,  
			TDualCapList *ptDualCap,
			TBfcpCapSet *ptBfcpCap, 
			TFeccCapbility *ptFeccCap);

typedef BOOL32 (PROTO_CALLBACK* CBCallConnected)( 
			HMDLCALL hCall, 
			HMDLAPPCALL hAppCall, 
			TModuleCallInfo *ptModParam,
			TCallInfoTP *ptCallTP);

typedef BOOL32 (PROTO_CALLBACK* CBCallDisconnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, const EmModuleCallDisconnectReason EmReason ); //sip挂断或拒绝


//回调成功的通道
typedef BOOL32 (PROTO_CALLBACK* CBChannelConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *pTConnectedInfo, s32 nSize, TChanDescriptTP *pTDesTP );       
//回调失败的通道
typedef BOOL32 (PROTO_CALLBACK* CBChannelDisconnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanDisConnectedInfo *pTDisConInfo, s32 nSize );
//回调当前所有的双流
typedef BOOL32 (PROTO_CALLBACK* CBSipDualIncoming)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TDualCapList *tDual);


typedef BOOL32 (PROTO_CALLBACK* CBFastUpdapte)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );
typedef BOOL32 (PROTO_CALLBACK* CBFlowControl)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitRate);

//从服务器收到注册成功回应，pbybuf里放入是否过NAT的判断结果，为一个BOOL32类型,TRUE为过NAT，FALSE为不过NAT
typedef BOOL32 (PROTO_CALLBACK* CBSipRegister)( HMDLREG hReg, HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pbyBuf, const s32 nLen );
typedef BOOL32 (PROTO_CALLBACK* CBSipUnRegister)( HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pbyBuf, const s32 nLen);
//如果从服务器收到注册失败回应，如果是重名，pbuf中依次放入emPARegisterNameDup，nsize,TPARegName， 
//如果是除了重名之外的失败， pBuf中放入emPARegisterFailed
//如果服务器不可达, pbuf中放入emPARegistrarUnReachable
//其他情况， pbuf中放入 emPAUnknownReason 

typedef BOOL32 (PROTO_CALLBACK* CBSipNonStdMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, const u8 *pbyBuf, const s32 nBufLen );
typedef BOOL32 (PROTO_CALLBACK* CBGetRegInfoAck)(const s32 nAppId, const u8 *pbyBuf, const s32 nLen, const u8  byVersion );
//获取全域内CNS的全部注册信息回调， pBuf中依次为： TPARegPackInfo ，EmPAGetRegInfoType,  TPARegInfo

typedef BOOL32 (PROTO_CALLBACK* CBFeccChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TFeccCapbility *ptFeccCap);
typedef BOOL32 (PROTO_CALLBACK* CBFeccMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccStruct, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );
typedef BOOL32 (PROTO_CALLBACK* CBSipRegNSMAck)(const s32 nAppId, const u8 *pbyBuf, const s32 nLen);

//回调当前双流请求（使用bfcp）
typedef BOOL32 (PROTO_CALLBACK* CBSipDualIncomingBfcp)(HMDLCALL hCall, HMDLAPPCALL hAppCall, BOOL32 bNotify);

//回调RoundTrip超时
typedef BOOL32 (PROTO_CALLBACK* CBSipRoundTripTimeOut)(HMDLCALL hCall, HMDLAPPCALL hAppCall);

typedef struct tagCallCBFunction
{
	CBNewCallIncoming      m_cbNewCallIncoming;
	CBCallDisconnected     m_cbCallDisconnected;
	CBCallConnected        m_cbCallConnected;
	CBChannelConnected     m_cbChannelConnected;
	CBChannelDisconnected  m_cbChannelDisconnected;
	CBFastUpdapte          m_cbFastUpdate;
	CBFlowControl          m_cbFlowControl;
	CBSipDualIncoming      m_cbDualIncoming;
	CBSipRegister          m_cbSipReg;
	CBSipUnRegister        m_cbSipUnReg;
	CBSipNonStdMsg         m_cbSipNonStdMsg;
	CBGetRegInfoAck        m_cbSipGetRegInfoAck;
	CBFeccChannelConnected m_cbFeccChannelConnected;
	CBFeccMsg			   m_cbFeccMsg;
	CBSipRegNSMAck         m_cbSipRegNSMAck;
	CBSipDualIncomingBfcp  m_cbDualIncomingBfcp;
	CBSipRoundTripTimeOut  m_cbRoundTripTimeOut;

	void Clear()
	{
		m_cbNewCallIncoming		= NULL;
		m_cbCallConnected		= NULL;
		m_cbCallDisconnected	= NULL;
		m_cbChannelConnected	= NULL;
		m_cbChannelDisconnected = NULL;
		m_cbFastUpdate			= NULL;
		m_cbFlowControl			= NULL;
		m_cbDualIncoming		= NULL;
		m_cbSipReg				= NULL;
		m_cbSipUnReg			= NULL;
		m_cbSipNonStdMsg		= NULL;
		m_cbSipGetRegInfoAck	= NULL;
		m_cbFeccChannelConnected= NULL;
		m_cbFeccMsg				= NULL;
		m_cbSipRegNSMAck		= NULL;
		m_cbDualIncomingBfcp	= NULL;
		m_cbRoundTripTimeOut    = NULL;
	}

	tagCallCBFunction()
	{
		Clear();
	}
}TCallCBFunction;

typedef struct tagModuleTlsCfg
{
	s8      m_achCACertFile[MAX_FILE_PATH_LEN]; //载入的CA证书文件，如果启用校验，CACertFile和CACertPath有一个即可。
	s8      m_achCACertPath[MAX_FILE_PATH_LEN]; //载入的CA证书目录，如果启用校验，CACertFile和CACertPath有一个即可。
	s8      m_achCertFile[MAX_FILE_PATH_LEN];   //载入的证书文件，服务端需设置，客户端选择性设置。
	s8      m_achKeyFile[MAX_FILE_PATH_LEN];    //private key，服务端需设置，客户端选择性设置。
	u16     m_wLocalTlsPort;		            //本地tls侦听端口,defult：5061

	//证书等回调接口，交给上层验证相关信息
	BOOL32 (PROTO_CALLBACK* cbCertForVerify)(BOOL32 bVerifyServer, s32 nVerifyStatus, const s8 *Cert, u32 dwCertLen);

	tagModuleTlsCfg()
	{
		Clear();
	}

	void Clear()
	{
		memset(this , 0 , sizeof(tagModuleTlsCfg) );
		cbCertForVerify = NULL;
		m_wLocalTlsPort = 5061;
	}
}TModuleTlsCfg;

typedef struct tagSipModuleCfg
{
	s32 m_nsipServiceAppId;
	s32 m_nsipStackinAppId;
	s32 m_nsipStackoutAppId;
	
	emModuleEndpointType m_emEndpointType;	//MT、CNS、UMS
	u16 m_wTotalCallNum;	//最大呼叫数
	u16 m_wTotalRegNum;		//最大注册个数
	u16	m_wCallingPort;		//呼叫端口
	u32	m_dwKeepAliveTime;	//心跳检测间隔（second）
	u32	m_dwMaxSendRecvBufferSize;	//套接字发送接收缓冲大小(暂时使用默认值)
	s32	m_nProductIdSize;
	u8 m_abyProductId[MAX_LEN_PRODUCT_ID];	//产品号
	s32	m_nVerIdSize;
	u8 m_abyVersionId[MAX_LEN_VERSION_ID];	//版本号

	BOOL32 m_bSendRecv;	//sip通道属性是否为sendrecv
	BOOL32 m_bSendRecvWithCommonCap;	//sip能力是否取交集
	BOOL32 m_bAutoAnswerFCS;	//BFCP server收到bfcp请求消息是否自动回复
	BOOL32 m_bUseStandardSipAlias;	//sip别名填写是否采用标准做法（"别名"<sip:E164号@主机IP>）还是非标做法（放在user-agent里面）
	BOOL32 m_bCompareCapsetInOrder;	//sip能力集比较是否采用顺序比较（默认采用类二分查找算法比较）

	BOOL32 m_bUseTLS;		//是否启用TLS，如果启用则tls端口默认是tcp+1(5061)
	TModuleTlsCfg m_tModuleTlsCfg;

	TCallCBFunction m_tCallCBFuntion;

	TSipTsxTimeout	m_tSipTsxTimeout;

	ALL_LOG_CALlBACK  m_fpModuleLogCB;

	u16		m_wPortRangeStart; // tcp or tls port range must be assigned by business, or random allocation
	u16		m_wPortRangeEnd;

	u32     m_dwSetLocalIP;            //本端地址.网络序

	tagSipModuleCfg()
	{
		m_nsipServiceAppId = -1;
		m_nsipStackinAppId = -1;
		m_nsipStackoutAppId= -1;
		m_emEndpointType  = emModuletypeBegin;
		m_wTotalCallNum   = MAX_INSTANCE_PROTOCAL;
		m_wTotalRegNum    = MAX_INSTANCE_PROTOCAL;
		m_wCallingPort    = SIP_DEFAULT_SERVER_PORT;
		m_dwKeepAliveTime = SIP_DEFAULT_KEEPALIVE_INTERVAL;
		m_dwMaxSendRecvBufferSize = S2H_DEFAULT_MAXSENDRECVBUFFERSIZE;
		m_nProductIdSize  = 0;
		m_nVerIdSize      = 0;
		MEMSET_CAST(m_abyProductId, 0, MAX_LEN_PRODUCT_ID);
		MEMSET_CAST(m_abyVersionId, 0, MAX_LEN_VERSION_ID);
		m_bSendRecv = FALSE;
		m_bSendRecvWithCommonCap = FALSE;
		m_bAutoAnswerFCS = FALSE;
		m_bUseStandardSipAlias   = FALSE;
		m_bCompareCapsetInOrder  = FALSE;

		m_tCallCBFuntion.Clear();
		m_tSipTsxTimeout.Clear();

		m_fpModuleLogCB = NULL;

		m_bUseTLS = TRUE;
		m_tModuleTlsCfg.Clear();

		m_wPortRangeStart = KDV_PORTRANGE_DEFAULT_START;
		m_wPortRangeEnd	= KDV_PORTRANGE_DEFAULT_FINISH;

		m_dwSetLocalIP = 0;
	}
	
}TSipModuleCfg;


class PROTO_API CSipModule
{
	//Call API:
public:
	
	//H323 module init function
	 static BOOL32 SipModuleInit( TSipModuleCfg &tCfg );   
	//H323 module start recv
	 static BOOL32 SipModuleStart();
	//H323 module stop recv
	 static BOOL32 SipModuleStop();
	//H323 module exit function
	 static BOOL32 SipModuleExit();
	
	 //如果makeCall时tdual传下来， 就认为双流能力是tdual, 但是呼叫时双流能力不带过去，上层调用sendual才发双流过去， 就不回调dualincoming, 只回调channelconnected,和disconnected
	 static BOOL32 SipModuleMakeOutgoingCall(
				HMDLAPPCALL hAppCall, 
				TModuleCallInfo *ptModParam, 
				BOOL32 bInviteWithSDP = TRUE,
				BOOL32 bInviteWithDual = FALSE,
				BOOL32 bInviteWithBfcp = FALSE,
				BOOL32 bAutoGetRegSrvIP = FALSE,
				TMdlCallCap *ptMainCap = NULL,
				TMdlTPCap *ptTPCap = NULL,  
				TDualCapList *ptDualCap = NULL,
				TBfcpCapSet *ptBfcpCap = NULL, 
				TFeccCapbility *ptFeccCap = NULL
				);

	 //应答call 带共同的能力集
	 static BOOL32 SipModuleCallAnswer(
				HMDLCALL hCall, 
				HMDLAPPCALL hAppCall, 
				BOOL32 bInviteWithDual = FALSE,
				BOOL32 bInviteWithBfcp = FALSE,
				TModuleCallInfo *ptModParam = NULL, 
				TMdlCallCap *ptMainCap = NULL,
				TMdlTPCap *ptTPCap = NULL,  
				TDualCapList *ptDualCap = NULL,
				TBfcpCapSet *ptBfcpCap = NULL, 
				TFeccCapbility *ptFeccCap = NULL
				);

	 //call ACK, 带共同的能力集
	 static BOOL32 SipModuleCallAck(
				HMDLCALL hCall, 
				HMDLAPPCALL hAppCall,                                
				BOOL32 bInviteWithDual = FALSE,
				BOOL32 bInviteWithBfcp = FALSE,
				TMdlCallCap *ptMainCap = NULL,
				TDualCapList *ptDualCap = NULL,
				TBfcpCapSet *ptBfcpCap = NULL, 
				TFeccCapbility *ptFeccCap = NULL
				);
	
	 static BOOL32 SipModuleCallReject(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   //拒绝call
	 static BOOL32 SipModuleCallHangup(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   //挂断call

public:
	//支持关闭多个通道 
	static BOOL32	CloseChannel(HMDLCALL hCall , HMDLAPPCALL hAppCall,  HMDLCHANNEL ahChan[], HMDLAPPCHANNEL ahAppChan[], u8 bySize, EmChannelReason emReason = emModuleChannelDisconnectNormal );   
	//每个通道携带指定的能力
	static BOOL32	ChangeChannel(HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptConnectedInfo, s32 nSize, BOOL32 bChangeAddress = FALSE ); 
	static BOOL32	SipModuleRegister(HMDLREG hReg, HMDLAPPREG hAppReg, TRegistReq* ptRegInfo);     //每次只能注册一个别名，标准注册
	static BOOL32	SipModuleUnregister(HMDLREG hReg, HMDLAPPREG hAppReg);
	static BOOL32	FlowCtrl(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitrate);
	static BOOL32	FastUpdate(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan);
	static BOOL32	FastUpdateWithoutID(HMDLCALL hCall , HMDLAPPCALL hAppCall);             //发送fastupdate不带ID
	static BOOL32	SipModuleSendFeccMsg( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccAction, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );
	static BOOL32	SipModuleSetFeccStreamId( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStreamIdInfo tFeccStreamIdInfo );
	//打洞的地址：dwKeepAliveIp、wKeepAlivePort，打洞间隔：nInterval
	static BOOL32	SipModuleSetFeccKeepAlive( HMDLCALL hCall, HMDLAPPCALL hAppCall, u32 dwKeepAliveIp, u16 wKeepAlivePort, s32 nInterval);

	//////////////////////////////////////////////////////////////////////////
	//双流API
	//发送双流,添加通道，上层业务控制, 如果makecall时双流能力带下来，sendDual发送的是makecall带下来的双流能力
	static BOOL32	SipModuleSendDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, TDualCapList *ptDual = NULL);    
	//bSuc为TRUE, 有双流， bSuc为False, 拒绝双流, answerDual是对所有双流的应答
	static BOOL32	SipModuleAnswerDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, BOOL32 bSuc, TDualCapList *ptDual = NULL);  
	//stopdual停止全部双流,  关双流就是去掉medialine, 关主流设为inactive
	static BOOL32	SipModuleStopDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, EmChannelReason emReason = emModuleChannelDisconnectNormal ); 

	//////////////////////////////////////////////////////////////////////////
	//Independent SIP conference-create related NON-STANDARD messages 
	//		MT/Agent ----> RegServer
	//		Data format: XML must have ConfNSM node right under the root node
	//Parameters:
	//		TSIPRegNSM tSIPRegNSM	: Contains with the IP address info and NONSTANDARD message type
	//		const s8* pchNSMRegXML	: Detail XML for the message
	//		s32 nBytes				: XML content length
	//		HMDLREG hReg			: Register handle which you get when you succeeded to register to the registrar
	//		s32 nAppID				: Upper layer ID, same with interface SipModuleGetRegInfoReq(). *Legacy issue, leaving it only to keep interface compatibility with old TPS interfaces;
	//////////////////////////////////////////////////////////////////////////
	static BOOL32	SipModuleSendRegNSM(TSIPRegNSM tSIPRegNSM, const s8* pchNSMRegXML, s32 nBytes, HMDLREG hReg, s32 nAppID);

	static BOOL32	SipModuleSendDtmfInfo(HMDLCALL hCall, HMDLAPPCALL hAppCall, u8 *pbyBuf, u16 wLen);

public:
	//用于网真的 API
	static BOOL32	SipModuleRegisterTP		(HMDLREG hReg, HMDLAPPREG hAppReg, TPARegCfg tPARegCfg); //注册多个别名，非标注册，通过xml注册
	static BOOL32	SipModuleSendNonStdMsg	(HMDLCALL hCall , HMDLAPPCALL hAppCall,  u8 *pbyBuf,  s32 nBufLen); //网真发送NonStandard-conf消息

	static BOOL32	SipModuleGetTlsSituationFromInfo(IN HMDLCALL hCall , OUT BOOL32 *pbTls, OUT u32 *pdwPeerCertificatStatus,  OUT s32 *pnCipher); //应用从info消息得到Tls的详细情况

	static BOOL32	SipModuleGetRegInfoReq	(s32 nAppId, TPAGetRegInfo tPAGetRegInfo, HMDLREG hReg = (HMDLREG)-1);	//若为老版本，hReg取默认值-1
	static BOOL32	SipModuleSetNatIp		(u32 dwIp);
#ifdef _ENABLE_QUANTUM_PROJECT_
	static BOOL32	SipModuleSetQtInitParam(TQtInitParam *ptQtInitParam);
#endif

private:
	static	BOOL32	Post( CModuleMsg &cMsg );

private:
	static	u16		m_wSipServiceAppId; 
};

enum emSIPPrintFlag
{
	emSIPPrintDefault = 0,	//0, 不分callid alias
	emSIPPrintByCallID,		//1， 按callid 打印 
	emSIPPrintByAlias,		//2， 按alias打印
};

typedef struct tagTSipPrint
{
	emModuleType m_emSipModule;
	s32 m_nLevel;
	s8  m_achAlias[MAX_LEN_CALL_ALIAS + 1];
	u16 m_wCallId;
	emSIPPrintFlag m_emFlag;
	EmSipLogFilter m_emLogFilter;
	tagTSipPrint()
	{
		m_emSipModule	= emModuleService ;
		m_nLevel		= 0;							 //异常打印
		MEMSET_CAST(m_achAlias, 0, sizeof(m_achAlias));
		m_wCallId		= 0;
		m_emFlag		= emSIPPrintDefault;
		m_emLogFilter	= emSipLogTelnet;
	}
}TSipPrint;

PROTO_EXTERN_API void setsiplogalias(s8 *pAlias); 
PROTO_EXTERN_API void setsiplogcallid(u16 wCallId);
PROTO_EXTERN_API void sipmodulelogon(s32 nModule, s32 nLevel);
PROTO_EXTERN_API void sipmlog(s32 nModule, s32 nLevel = 0);
PROTO_EXTERN_API void sipmodulelogoff();
PROTO_EXTERN_API void sipmodulehelp();
PROTO_EXTERN_API void kdvsipmodulehelp();

PROTO_EXTERN_API void sipshowcall();
PROTO_EXTERN_API void sipshowcallid(u16 wCallid);
PROTO_EXTERN_API void sipmodulever();
PROTO_EXTERN_API void sipmver();
PROTO_EXTERN_API void sipshowreg();
PROTO_EXTERN_API void sipmodulelogto(u8 byFilter);
PROTO_EXTERN_API void useregistarip(BOOL32 bUseRegistarIP);
PROTO_EXTERN_API void sipmoduleconfigon(s32 nType);
PROTO_EXTERN_API void sipmoduleconfigoff();
void SipmdlPrintf( emModuleType emSipModule, s32 nLevel, s8 *pAlias, u16 wCallId, const char* pFormat, ... );

#endif
