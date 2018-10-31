#ifndef SIPMODULE_H
#define SIPMODULE_H

#include "kdvtype.h"
#include "modulecallstruct.h"
#include "modulemananger.h"
#include "tpmodulestruct.h"

#include "kdvsipcommon.h"
#include "sipconfnonstdstruct.h"
#include "sipconfnonstdmsg.h"

#define S2H_DEFAULT_MAXSENDRECVBUFFERSIZE	20480       //Ĭ���׽��ַ��ͽ��ջ����С
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

//TPΪ�������
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

typedef BOOL32 (PROTO_CALLBACK* CBCallDisconnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, const EmModuleCallDisconnectReason EmReason ); //sip�Ҷϻ�ܾ�


//�ص��ɹ���ͨ��
typedef BOOL32 (PROTO_CALLBACK* CBChannelConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *pTConnectedInfo, s32 nSize, TChanDescriptTP *pTDesTP );       
//�ص�ʧ�ܵ�ͨ��
typedef BOOL32 (PROTO_CALLBACK* CBChannelDisconnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanDisConnectedInfo *pTDisConInfo, s32 nSize );
//�ص���ǰ���е�˫��
typedef BOOL32 (PROTO_CALLBACK* CBSipDualIncoming)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TDualCapList *tDual);


typedef BOOL32 (PROTO_CALLBACK* CBFastUpdapte)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );
typedef BOOL32 (PROTO_CALLBACK* CBFlowControl)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitRate);

//�ӷ������յ�ע��ɹ���Ӧ��pbybuf������Ƿ��NAT���жϽ����Ϊһ��BOOL32����,TRUEΪ��NAT��FALSEΪ����NAT
typedef BOOL32 (PROTO_CALLBACK* CBSipRegister)( HMDLREG hReg, HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pbyBuf, const s32 nLen );
typedef BOOL32 (PROTO_CALLBACK* CBSipUnRegister)( HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pbyBuf, const s32 nLen);
//����ӷ������յ�ע��ʧ�ܻ�Ӧ�������������pbuf�����η���emPARegisterNameDup��nsize,TPARegName�� 
//����ǳ�������֮���ʧ�ܣ� pBuf�з���emPARegisterFailed
//������������ɴ�, pbuf�з���emPARegistrarUnReachable
//��������� pbuf�з��� emPAUnknownReason 

typedef BOOL32 (PROTO_CALLBACK* CBSipNonStdMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, const u8 *pbyBuf, const s32 nBufLen );
typedef BOOL32 (PROTO_CALLBACK* CBGetRegInfoAck)(const s32 nAppId, const u8 *pbyBuf, const s32 nLen, const u8  byVersion );
//��ȡȫ����CNS��ȫ��ע����Ϣ�ص��� pBuf������Ϊ�� TPARegPackInfo ��EmPAGetRegInfoType,  TPARegInfo

typedef BOOL32 (PROTO_CALLBACK* CBFeccChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TFeccCapbility *ptFeccCap);
typedef BOOL32 (PROTO_CALLBACK* CBFeccMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccStruct, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );
typedef BOOL32 (PROTO_CALLBACK* CBSipRegNSMAck)(const s32 nAppId, const u8 *pbyBuf, const s32 nLen);

//�ص���ǰ˫������ʹ��bfcp��
typedef BOOL32 (PROTO_CALLBACK* CBSipDualIncomingBfcp)(HMDLCALL hCall, HMDLAPPCALL hAppCall, BOOL32 bNotify);

//�ص�RoundTrip��ʱ
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
	s8      m_achCACertFile[MAX_FILE_PATH_LEN]; //�����CA֤���ļ����������У�飬CACertFile��CACertPath��һ�����ɡ�
	s8      m_achCACertPath[MAX_FILE_PATH_LEN]; //�����CA֤��Ŀ¼���������У�飬CACertFile��CACertPath��һ�����ɡ�
	s8      m_achCertFile[MAX_FILE_PATH_LEN];   //�����֤���ļ�������������ã��ͻ���ѡ�������á�
	s8      m_achKeyFile[MAX_FILE_PATH_LEN];    //private key������������ã��ͻ���ѡ�������á�
	u16     m_wLocalTlsPort;		            //����tls�����˿�,defult��5061

	//֤��Ȼص��ӿڣ������ϲ���֤�����Ϣ
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
	
	emModuleEndpointType m_emEndpointType;	//MT��CNS��UMS
	u16 m_wTotalCallNum;	//��������
	u16 m_wTotalRegNum;		//���ע�����
	u16	m_wCallingPort;		//���ж˿�
	u32	m_dwKeepAliveTime;	//�����������second��
	u32	m_dwMaxSendRecvBufferSize;	//�׽��ַ��ͽ��ջ����С(��ʱʹ��Ĭ��ֵ)
	s32	m_nProductIdSize;
	u8 m_abyProductId[MAX_LEN_PRODUCT_ID];	//��Ʒ��
	s32	m_nVerIdSize;
	u8 m_abyVersionId[MAX_LEN_VERSION_ID];	//�汾��

	BOOL32 m_bSendRecv;	//sipͨ�������Ƿ�Ϊsendrecv
	BOOL32 m_bSendRecvWithCommonCap;	//sip�����Ƿ�ȡ����
	BOOL32 m_bAutoAnswerFCS;	//BFCP server�յ�bfcp������Ϣ�Ƿ��Զ��ظ�
	BOOL32 m_bUseStandardSipAlias;	//sip������д�Ƿ���ñ�׼������"����"<sip:E164��@����IP>�����ǷǱ�����������user-agent���棩
	BOOL32 m_bCompareCapsetInOrder;	//sip�������Ƚ��Ƿ����˳��Ƚϣ�Ĭ�ϲ�������ֲ����㷨�Ƚϣ�

	BOOL32 m_bUseTLS;		//�Ƿ�����TLS�����������tls�˿�Ĭ����tcp+1(5061)
	TModuleTlsCfg m_tModuleTlsCfg;

	TCallCBFunction m_tCallCBFuntion;

	TSipTsxTimeout	m_tSipTsxTimeout;

	ALL_LOG_CALlBACK  m_fpModuleLogCB;

	u16		m_wPortRangeStart; // tcp or tls port range must be assigned by business, or random allocation
	u16		m_wPortRangeEnd;

	u32     m_dwSetLocalIP;            //���˵�ַ.������

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
	
	 //���makeCallʱtdual�������� ����Ϊ˫��������tdual, ���Ǻ���ʱ˫������������ȥ���ϲ����sendual�ŷ�˫����ȥ�� �Ͳ��ص�dualincoming, ֻ�ص�channelconnected,��disconnected
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

	 //Ӧ��call ����ͬ��������
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

	 //call ACK, ����ͬ��������
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
	
	 static BOOL32 SipModuleCallReject(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   //�ܾ�call
	 static BOOL32 SipModuleCallHangup(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   //�Ҷ�call

public:
	//֧�ֹرն��ͨ�� 
	static BOOL32	CloseChannel(HMDLCALL hCall , HMDLAPPCALL hAppCall,  HMDLCHANNEL ahChan[], HMDLAPPCHANNEL ahAppChan[], u8 bySize, EmChannelReason emReason = emModuleChannelDisconnectNormal );   
	//ÿ��ͨ��Я��ָ��������
	static BOOL32	ChangeChannel(HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptConnectedInfo, s32 nSize, BOOL32 bChangeAddress = FALSE ); 
	static BOOL32	SipModuleRegister(HMDLREG hReg, HMDLAPPREG hAppReg, TRegistReq* ptRegInfo);     //ÿ��ֻ��ע��һ����������׼ע��
	static BOOL32	SipModuleUnregister(HMDLREG hReg, HMDLAPPREG hAppReg);
	static BOOL32	FlowCtrl(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitrate);
	static BOOL32	FastUpdate(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan);
	static BOOL32	FastUpdateWithoutID(HMDLCALL hCall , HMDLAPPCALL hAppCall);             //����fastupdate����ID
	static BOOL32	SipModuleSendFeccMsg( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccAction, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );
	static BOOL32	SipModuleSetFeccStreamId( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStreamIdInfo tFeccStreamIdInfo );
	//�򶴵ĵ�ַ��dwKeepAliveIp��wKeepAlivePort���򶴼����nInterval
	static BOOL32	SipModuleSetFeccKeepAlive( HMDLCALL hCall, HMDLAPPCALL hAppCall, u32 dwKeepAliveIp, u16 wKeepAlivePort, s32 nInterval);

	//////////////////////////////////////////////////////////////////////////
	//˫��API
	//����˫��,���ͨ�����ϲ�ҵ�����, ���makecallʱ˫��������������sendDual���͵���makecall��������˫������
	static BOOL32	SipModuleSendDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, TDualCapList *ptDual = NULL);    
	//bSucΪTRUE, ��˫���� bSucΪFalse, �ܾ�˫��, answerDual�Ƕ�����˫����Ӧ��
	static BOOL32	SipModuleAnswerDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, BOOL32 bSuc, TDualCapList *ptDual = NULL);  
	//stopdualֹͣȫ��˫��,  ��˫������ȥ��medialine, ��������Ϊinactive
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
	//��������� API
	static BOOL32	SipModuleRegisterTP		(HMDLREG hReg, HMDLAPPREG hAppReg, TPARegCfg tPARegCfg); //ע�����������Ǳ�ע�ᣬͨ��xmlע��
	static BOOL32	SipModuleSendNonStdMsg	(HMDLCALL hCall , HMDLAPPCALL hAppCall,  u8 *pbyBuf,  s32 nBufLen); //���淢��NonStandard-conf��Ϣ

	static BOOL32	SipModuleGetTlsSituationFromInfo(IN HMDLCALL hCall , OUT BOOL32 *pbTls, OUT u32 *pdwPeerCertificatStatus,  OUT s32 *pnCipher); //Ӧ�ô�info��Ϣ�õ�Tls����ϸ���

	static BOOL32	SipModuleGetRegInfoReq	(s32 nAppId, TPAGetRegInfo tPAGetRegInfo, HMDLREG hReg = (HMDLREG)-1);	//��Ϊ�ϰ汾��hRegȡĬ��ֵ-1
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
	emSIPPrintDefault = 0,	//0, ����callid alias
	emSIPPrintByCallID,		//1�� ��callid ��ӡ 
	emSIPPrintByAlias,		//2�� ��alias��ӡ
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
		m_nLevel		= 0;							 //�쳣��ӡ
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
