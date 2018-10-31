#ifndef _PROTOCALADAPTER_H
#define _PROTOCALADAPTER_H


#include "osp.h"
#include "kdvcommon.h"
#include "modulecallstruct.h"
#include "tpmodulestruct.h"


#ifdef WIN32
#define PACALLBACK __cdecl
#else
#define PACALLBACK
#endif


#define PA_INVALID_INDEX         -1
#define MAX_PROTOCOL_NUMBER       5
#define PA_IPV6_ADDR_SIZE         16

#define DEFAULT_CALL_NUMBER       128
#define DEFAULT_H225_PORT         1720
#define DEFAULT_H323_PORT_FROM    60000
#define DEFAULT_H323_PORT_TO      60040

#define DEFAULT_SIP_CALLING_PORT  5060
#define DEFAULT_SIP_ALIVE_TIME    30

#define MAX_SENDRECV_BUF_SIZE     20480       //Ĭ���׽��ַ��ͽ��ջ����С

extern u16 g_abyProtocolList[MAX_PROTOCOL_NUMBER + 1];


//Э������
enum EmPAConfProtocol
{
	emPATypeInvalid = 0,
	emPATypeH323  = 1, 
	emPATypeSip   = 2, 
	emPATypeAll   = 3,
};




typedef BOOL (PACALLBACK* PACBNewCallIncoming)(
	EmPAConfProtocol emPAType,
    HMDLCALL         hPACall, 
	TModuleCallInfo *ptCallInfo, 
	TCallCapbility  *ptSndCap, 
	TCallCapbility  *ptRcvCap,
	TCallInfoTP     *ptCallTP, 
	TCallDescriptTP *ptSndTP,
	TCallDescriptTP *ptRcvTP,
	TDualCapList *ptDualCap,
	TBfcpCapSet *ptBfcpCap, 
	TFeccCapbility *ptFeccCap);

typedef BOOL (PACALLBACK* PACBCallConnected)( 
	HMDLCALL    hPACall, 
	HMDLAPPCALL hAppCall,
	TModuleCallInfo *ptCallInfo, 
	TCallInfoTP     *ptCallTP,
	EmPAConfProtocol emPAType );

typedef BOOL (PACALLBACK* PACBCallDisconnected)( 
	HMDLCALL    hPACall,
	HMDLAPPCALL hAppCall,
	EmModuleCallDisconnectReason emReason );

typedef struct tagPACallCBFunction
{
	PACBNewCallIncoming    m_fpNewCallIncoming;
	PACBCallConnected      m_fpCallConnected;
	PACBCallDisconnected   m_fpCallDisconnected;

	tagPACallCBFunction()
	{
		memset( this, 0, sizeof(tagPACallCBFunction) );
	}
}TPACallCBFunction;



typedef BOOL (PACALLBACK* PACBChannelConnected)(
	HMDLCALL hPACall, 
	HMDLAPPCALL hAppCall, 
	TChanConnectedInfo* ptChanConnectInfo,
	s32 nSize, 
	TChanDescriptTP *ptDesTP);

typedef BOOL (PACALLBACK* PACBChannelDisconnected)(
	HMDLCALL hPACall, 
	HMDLAPPCALL hAppCall, 
	TChanDisConnectedInfo *ptDisConInfo, 
	s32 nSize);

typedef BOOL (PACALLBACK* PACBChannelFlowCtrl)( 
	HMDLCALL       hPACall, 
	HMDLAPPCALL    hAppCall,
	HMDLCHANNEL    hPAChan,
	HMDLAPPCHANNEL hAppChan, 
	u16 wBitrate );

typedef BOOL (PACALLBACK* PACBChannelFastUpdate)( 
	HMDLCALL       hPACall, 
	HMDLAPPCALL    hAppCall,
	HMDLCHANNEL    hPAChan,
	HMDLAPPCHANNEL hAppChan );

typedef BOOL (PACALLBACK* PACBDualStreamIncoming)( 
	HMDLCALL       hPACall, 
	HMDLAPPCALL    hAppCall,
	TDualCapList   *ptDual );

typedef BOOL (PACALLBACK* PACBFeccChanConnected)(
    HMDLCALL hCall, 
    HMDLAPPCALL hAppCall, 
    TFeccCapbility *ptFeccCap);

typedef BOOL (PACALLBACK* PACBFeccMsg)(
	HMDLCALL hCall, 
	HMDLAPPCALL hAppCall, 
	TMdlFeccStruct *ptFeccStruct, 
	TMDLTERLABEL *ptSrcLabel, 
	TMDLTERLABEL *ptDstLabel);

typedef BOOL (PACALLBACK* PACBMMcuChanConnected)(
	HMDLCALL hCall, 
	HMDLAPPCALL hAppCall, 
	TChanConnectedInfo *ptChanConnectInfo);

typedef BOOL (PACALLBACK* PACBMMcuMsg)(
	HMDLCALL hCall, 
	HMDLAPPCALL hAppCall, 
	u16 wEvent,
	void *pBuf, 
	u16 wLen);

// typedef BOOL (PACALLBACK* PACBDualStreamConnected)( 
// 	HMDLCALL       hPACall, 
// 	HMDLAPPCALL    hAppCall,
// 	HMDLCHANNEL    hPAChan,
// 	HMDLAPPCHANNEL hAppChan, 
// 	TChanConnectedInfo *ptChanInfo );
// 
// typedef BOOL (PACALLBACK* PACBDualStreamReject)( 
// 	HMDLCALL       hPACall, 
// 	HMDLAPPCALL    hAppCall,
// 	HMDLCHANNEL    hPAChan,
// 	HMDLAPPCHANNEL hAppChan );
// 
// typedef BOOL (PACALLBACK* PACBDualStreamStop)( 
// 	HMDLCALL       hPACall, 
// 	HMDLAPPCALL    hAppCall,
// 	HMDLCHANNEL    hPAChan,
// 	HMDLAPPCHANNEL hAppChan );

typedef BOOL (PA_CALLBACK* PACBChanCtrlTP)(
	HMDLCALL hPACall ,
	HMDLAPPCALL hAppCall, 
	HMDLCHANNEL hChan, 
	s32 nMsgType, 
	u8 *pbyBuf, 
	s32 nSize );

typedef BOOL (PA_CALLBACK* PACBConfCtrlTP)(
	 HMDLCALL hPACall ,
	 HMDLAPPCALL hAppCall,  
	 s32 nMsgType, 
	 u8 *pbyBuf, 
	 s32 nSize, 
	 EmPAConfProtocol emPAType);

typedef BOOL (PA_CALLBACK* PACBConfCtrl)(
     HMDLCALL hPACall ,
     HMDLAPPCALL hAppCall,  
     s32 nMsgType, 
     u8 *pbyBuf, 
	 s32 nSize,
	 EmPAConfProtocol emPAType);

typedef BOOL (PACALLBACK* PACBDualStreamIncomingBfcp)( 
	HMDLCALL       hPACall, 
	HMDLAPPCALL    hAppCall,
	BOOL32 bNotify );

typedef struct tagPAChannelCBFunction
{
	PACBChannelConnected     m_fpChannelConnected;
	PACBChannelDisconnected  m_fpChannelDisconnected;

	PACBChannelFlowCtrl      m_fpChannelFlowCtrl;
	PACBChannelFastUpdate    m_fpChannelFastUpdate;
	PACBDualStreamIncoming   m_fpDualStreamIncoming;
    PACBFeccChanConnected    m_fpFeccChanConnected;
	PACBFeccMsg				 m_fpFeccMsg;
	PACBMMcuChanConnected    m_fpMMcuChanConnected;
	PACBMMcuMsg				 m_fpMMcuMsg;
	PACBChanCtrlTP           m_fpChanCtrlTP;
	PACBConfCtrlTP           m_fpConfCtrlTP;
	PACBConfCtrl             m_fpConfCtrl;

	PACBDualStreamIncomingBfcp   m_fpDualStreamIncomingBfcp;
// 	PACBDualStreamConnected  m_fpDualStreamConnected;
// 	PACBDualStreamReject     m_fpDualStreamReject;
// 	PACBDualStreamStop       m_fpDualStreamStop;
	
	tagPAChannelCBFunction()
	{
		memset( this , 0 , sizeof(tagPAChannelCBFunction) );
	}
}TPAChannelCBFunction;


/*====================================================================
�� �� ���� PACBRegResult
��    �ܣ� ע�����Ļص�����
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� EmPAConfProtocol emPAType : Э������
           HMDLREG          hReg     : Э��ջ���
           HMDLAPPREG       hAppReg  : Ӧ�ò���
           BOOL32     bRegistered : �Ƿ�ע��ɹ�
           u8* pAppendData    : ���ע��ɹ�����pBuf = NULL; ����ָ�� EmPARegFailedReason
           u16 wAppendDataLen : ���ע��ɹ�����wLen = 0;    ����Ϊ EmPARegFailedReason �ĳ���
��ע��     ���������Ŀ����ע��ʧ�ܣ�����ʧ��ԭ��ΪemPARegisterNameDupʱ��
           pAppendDataָ����ڴ�ṹΪ��EmPARegFailedReason + nSize + nSize*TPARegName
======================================================================*/
typedef BOOL (PACALLBACK* PACBRegResult)( 
	EmPAConfProtocol emPAType,										 
	HMDLREG          hReg, 
	HMDLAPPREG       hAppReg,
	BOOL32           bRegistered,
	u8              *pbyAppendData,
	u16              wAppendDataLen );

/*====================================================================
�� �� ���� PACBUnRegResult
��    �ܣ� ȡ��ע�����Ļص�����
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� EmPAConfProtocol emPAType : Э������
           HMDLREG          hReg     : Э��ջ���
           HMDLAPPREG       hAppReg  : Ӧ�ò���
           u8* pBuf : ָ�� EmPARegFailedReason
           u16 wLen : EmPARegFailedReason �ĳ���
��ע: ȡ��ע��Ľ�����ٻص�, ��Э��ջ��ȷ��ȡ��ע��ɹ�.
======================================================================*/
// typedef BOOL (PACALLBACK* PACBUnRegResult)( 
// 	EmPAConfProtocol emPAType,
// 	HMDLREG    hReg, 
// 	HMDLAPPREG hAppReg,
// 	s8 *pBuf, 
// 	s32 nLen );


/*====================================================================
�� �� ���� PACBUnRegResult
��    �ܣ� ��ȡȫ����CNS��ȫ��ע����Ϣ�Ļص�����
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� s32  nAppId : Ӧ�ò���
           u8  *pBuf   : ����ΪTPARegPackInfo, EmPAGetRegInfoType, TPARegInfo
           u16  wLen   : ���ݳ���
��ע    :  
======================================================================*/
typedef BOOL (PACALLBACK* PACBGetRegInfoAckTP)(
	const EmPAConfProtocol protocolType,
    const s32 nAppId, 
	const u8 *pbyBuf, 
	const s32 nLen,
	const u8  byVersion);


typedef struct tagPARegistCBFunction
{
	PACBRegResult        m_cbRegistResult;
 //	PACBUnRegResult      m_cbUnRegistResult;
	PACBGetRegInfoAckTP  m_cbGetRegInfoAckTP;
	tagPARegistCBFunction()
	{
		memset( this , 0 , sizeof(tagPARegistCBFunction) );
	}

}TPARegistCBFunction;



//#define USE_NEW_CONF

#ifdef USE_NEW_CONF
/*====================================================================
�� �� ���� PACBMultipleConf
��    �ܣ� [��ػص��ӿ�] �ն˲�ص��������鿪��
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall      : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL  : Ӧ�ò���о��
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBMultipleConf)( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PACBSelfTerLabel
��    �ܣ� [��ػص��ӿ�] �ն˲�ص����ն�LABEL��Ϣ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall      : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL  : Ӧ�ò���о��
		   TMDLTERLABEL      tTerLabel    : �ն�LABEL
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBSelfTerLabel)( HMDLCALL hPACall, 
											  HMDLAPPCALL hAppCall, 
											  TMDLTERLABEL tTerLabel );

/*====================================================================
�� �� ���� PACBChairTokenOwner
��    �ܣ� [��ػص��ӿ�] �ն˲�ص�����ϯ�ն���Ϣ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall      : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL  : Ӧ�ò���о��
		   TMDLTERMINALINFO  tTerInfo     : ��ϯ�ն���Ϣ
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairTokenOwner)( HMDLCALL hPACall, 
												 HMDLAPPCALL hAppCall, 
												 TMDLTERMINALINFO tTerInfo );

/*====================================================================
�� �� ���� PACBTerList
��    �ܣ� [��ػص��ӿ�] �ն˲�ص�������ն���Ϣ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall       : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL   : Ӧ�ò���о��
		   TMDLTERINFOLIST   tTerList      : ����ն��б���Ϣ
		   BOOL32            bHaveTPParam  : �Ƿ�Я���������
		   TConfCnsList     *ptConfCnsList : �������
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerList )( HMDLCALL hPACall, 
										  HMDLAPPCALL hAppCall, 
										  TMDLTERINFOLIST tTerList,
										  BOOL32       bHaveTPParam,
										  TConfCnsList *ptConfCnsList );

/*====================================================================
�� �� ���� PACBYouAreSeeing
��    �ܣ� [��ػص��ӿ�] �ն˲�ص����ն˵�ǰ��ѡ������
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall        : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL    : Ӧ�ò���о��
		   TMDLTERMINALINFO  tTerInfo       : �����ն˵���Ϣ
		   BOOL32            bHaveTPParam   : �Ƿ�Я���������
		   TYouAreSeeing    *ptYouAreSeeing : �������
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBYouAreSeeing)( HMDLCALL hPACall, 
											  HMDLAPPCALL hAppCall, 
											  TMDLTERMINALINFO tTerInfo, 
											  BOOL32 bHaveTPParam, 
											  TYouAreSeeing *ptYouAreSeeing);

/*====================================================================
�� �� ���� PACBSeeByAll
��    �ܣ� [��ػص��ӿ�] �ն˲�ص����㲥Դָʾ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall        : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL    : Ӧ�ò���о��
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBSeeByAll)( HMDLCALL hPACall, HMDLAPPCALL hAppCall );


/*====================================================================
�� �� ���� PACBTerFloorReqToChair
��    �ܣ� [��ػص��ӿ�] �ն˲�ص�(��ϯ)���ն�������
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall        : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL    : Ӧ�ò���о��
		   TMDLTERLABEL      tTerLabel    : �ն�LABEL
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerFloorReqToChair)( HMDLCALL hPACall, 
													HMDLAPPCALL hAppCall, 
													TMDLTERMINALINFO tTerInfo );

/*====================================================================
�� �� ���� PACBTerFloorReqToChair
��    �ܣ� [��ػص��ӿ�] �ն˲�ص�(��ϯ)����ϯѡ���ظ�
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL          hPACall        : Э��ջ���о��
           HMDLAPPCALL       HMDLAPPCALL    : Ӧ�ò���о��
		   TMDLTERLABEL      tTerLabel    : �ն�LABEL
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBSendThisSourceRsp)( HMDLCALL hCall,
                                                   HMDLAPPCALL hAppCall,
                                                   BOOL32 bIsSuccess );


/*====================================================================
�� �� ���� PACBChairSendThisSource
��    �ܣ� [��ػص��ӿ�] MC��ص����յ���ϯѡ��ָʾ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������ 
           HMDLCALL        hViewer      : Э��ջ���о��(ѡ����)
           HMDLAPPCALL     hAppViewer   : Ӧ�ò���о��(ѡ����)
           HMDLCALL        hViewed      : Э��ջ���о��(��ѡ����)
           HMDLAPPCALL     hAppViewed   : Ӧ�ò���о��(��ѡ����)
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairSendThisSource)( HMDLAPPCONFID hAppConfId, 
													 HMDLCALL hViewer, 
													 HMDLAPPCALL hAppViewer, 
													 HMDLCALL hViewed, 
													 HMDLAPPCALL hAppViewed );
// TODO:
/*====================================================================
�� �� ���� PACBChairCancelSendThisSource
��    �ܣ� [��ػص��ӿ�] MC��ص����յ���ϯȡ��ѡ��ָʾ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������ 
           HMDLCALL        hViewer      : Э��ջ���о��(ѡ����)
           HMDLAPPCALL     hAppViewer   : Ӧ�ò���о��(ѡ����)
           HMDLCALL        hViewed      : Э��ջ���о��(��ѡ����)
           HMDLAPPCALL     hAppViewed   : Ӧ�ò���о��(��ѡ����)
��ע: 
======================================================================*/

/*====================================================================
�� �� ���� PACBChairBroadcastTerminal
��    �ܣ� [��ػص��ӿ�] MC��ص����յ���ϯָʾ�����ն�
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������ 
           HMDLCALL        hPACall      : Э��ջ���о��
           HMDLAPPCALL     hAppCall     : Ӧ�ò���о��
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairBroadcastTerminal)( HMDLAPPCONFID hAppConfId,
														HMDLCALL hPACall, 
														HMDLAPPCALL hAppCall);

/*====================================================================
�� �� ���� PACBChairCancelBroadcastTerminal
��    �ܣ� [��ػص��ӿ�] MC��ص����յ���ϯȡ�������ն�
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������ 
           HMDLCALL        hPACall      : Э��ջ���о��
           HMDLAPPCALL     hAppCall     : Ӧ�ò���о��
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBChairCancelBroadcastTerminal)( HMDLAPPCONFID hAppConfId,
															  HMDLCALL hPACall, 
															  HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PACBTerFloorReqToMc
��    �ܣ� [��ػص��ӿ�] MC��ص����յ��ն����뷢��
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������ 
           HMDLCALL        hPACall      : Э��ջ���о��
           HMDLAPPCALL     hAppCall     : Ӧ�ò���о��
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerFloorReqToMc)( HMDLAPPCONFID hAppConfId, 
												 HMDLCALL hPACall, 
												 HMDLAPPCALL hAppCall );
/*====================================================================
�� �� ���� PACBTerChairReqToMc
��    �ܣ� [��ػص��ӿ�] MC��ص����յ��ն�������ϯ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������ 
           HMDLCALL        hPACall      : Э��ջ���о��
           HMDLAPPCALL     hAppCall     : Ӧ�ò���о��
��ע: 
======================================================================*/
typedef BOOL32 (PACALLBACK* PACBTerChairReqToMc)( HMDLAPPCONFID hAppConfId, 
												 HMDLCALL hPACall, 
												 HMDLAPPCALL hAppCall );


typedef struct tagPAConfCallBack
{
	// MC��ص����յ�chair������
	PACBChairSendThisSource          m_fpChairSendThisSource;
	PACBChairBroadcastTerminal       m_fpChairBroadcastTerminal;
	PACBChairCancelBroadcastTerminal m_fpChairCancelBroadcastTerminal;
	
	// MC��ص����յ�Terminal������
	PACBTerFloorReqToMc m_fpTerFloorReqToMc;
	PACBTerChairReqToMc m_fpTerChairReqToMc;

	//terminal��ص�
	PACBMultipleConf    m_fpMultipleConf;
	PACBSelfTerLabel    m_fpSelfTerLabel;
	PACBChairTokenOwner m_fpChairTokenOwner;
	PACBTerList         m_fpTerList;
	PACBYouAreSeeing    m_fpYouAreSeeing;
	PACBSeeByAll        m_fpSeeByAll;
	
	//terminal��ص�(chair)
	PACBTerFloorReqToChair m_fpTerFloorReqToChair;
    PACBSendThisSourceRsp  m_fpSendThisSouceRsp;

    tagPAConfCallBack()
    {
        memset( this , 0 , sizeof(tagPAConfCallBack) );
	}
	
}TPAConfCBFunction;

#endif


typedef struct tagPACallBackFunc
{
	TPACallCBFunction      m_tPACallCBFunction;
	TPAChannelCBFunction   m_tPAChannelCBFunction;
	TPARegistCBFunction    m_tPARegistCBFunction;

#ifdef USE_NEW_CONF
	TPAConfCBFunction      m_tPAConfCBFunction;
#endif
	ALL_LOG_CALlBACK       m_fpPALogCB;
	
	tagPACallBackFunc()
	{
		memset( this, 0, sizeof(tagPACallBackFunc) );
	}
	
}TPACallBackFunc, *PTPACallBackFunc;


typedef struct tagPAH323Cfg
{
	u32 m_dwh323StackIp;
	u8  m_abyh323StackIp_ipv6[PA_IPV6_ADDR_SIZE];
	
	u16 m_wh225port;
	u16 m_dwh323StackPortStart;
	u16 m_dwh323StackPortEnd;
	
	u16 m_wH323TotalCallNum;
	
	emModuleEndpointType m_emEndpointType;

	tagPAH323Cfg()
	{		
		m_wh225port = DEFAULT_H225_PORT;
		m_dwh323StackIp = 0;
		
		memset(m_abyh323StackIp_ipv6 , 0 , sizeof(m_abyh323StackIp_ipv6) );
		
		m_wH323TotalCallNum = DEFAULT_CALL_NUMBER;
		m_dwh323StackPortStart = DEFAULT_H323_PORT_FROM;
		m_dwh323StackPortEnd   = DEFAULT_H323_PORT_TO;

		m_emEndpointType = emModuleEndpointMT;
	}
	
}TPAH323Cfg;


typedef struct tagPASipCfg
{
	emModuleEndpointType m_emEndpointType;
	u16  m_wCallingPort;            //���ж˿�
	u16  m_wSipTotalCallNum;
	u16  m_wIfProxy;                //��Ϊע������������0 ������0
	u32  m_dwKeepAliveTime;         //��λ: ��
	u16  m_wRegClientNum;           //֧��CNS���ע�������
	u32  m_dwMaxSendRecvBufferSize; //�׽��ַ��ͽ��ջ����С(��ʱʹ��Ĭ��ֵ)
	BOOL32  m_bSendRecv;            //��ʾsip��������(sendrecv����sendonly��recvonly)
	BOOL32	m_bSendRecvWithComCap;	//��ʶsipͨ������Ϊsendrecvʱ����ȡ����
	BOOL32 m_bAutoAnswerFCS;	//BFCP server�յ�bfcp������Ϣ�Ƿ��Զ��ظ�
	BOOL32 m_bUseStandardSipAlias;	//sip������д�Ƿ���ñ�׼������"����"<sip:E164��@����IP>�����ǷǱ�����������user-agent���棩

	s32					  m_nProductIdSize;
	u8					  m_abyProductId[MAX_LEN_PRODUCT_ID];				//��Ʒ��
	s32					  m_nVerIdSize;
	u8					  m_abyVersionId[MAX_LEN_VERSION_ID];				//�汾��
	
	u32     m_dwPaLocalIP;            //����ҵ��ָ���󶨵�ַ.������
	tagPASipCfg()
	{	
		m_emEndpointType = emModuleEndpointMT;
		m_wCallingPort = DEFAULT_SIP_CALLING_PORT;
		m_wSipTotalCallNum = DEFAULT_CALL_NUMBER;
		m_wIfProxy = FALSE;
		m_dwKeepAliveTime = DEFAULT_SIP_ALIVE_TIME;
		m_nProductIdSize = 0;
		m_nVerIdSize = 0;
		m_wRegClientNum = MAX_INSTANCE_PROTOCAL;
		m_dwMaxSendRecvBufferSize = MAX_SENDRECV_BUF_SIZE;
		m_bSendRecv = FALSE;
		m_bSendRecvWithComCap = FALSE;
		m_bAutoAnswerFCS = FALSE;
		m_bUseStandardSipAlias = FALSE;
		memset( m_abyProductId, 0, MAX_LEN_PRODUCT_ID );
		memset( m_abyVersionId, 0, MAX_LEN_VERSION_ID );
		m_dwPaLocalIP = 0;
	}
	
}TPASipCfg;


typedef struct tagPAConfig
{
	TPAH323Cfg m_tH323Config;
	TPASipCfg  m_tSipConfig;

#ifdef _ENABLE_QUANTUM_PROJECT_
	TQtInitParam	m_tQuantumInitParam;					//�������ӳ�ʼ����ֱ�ӻ�ȡ����MyQtID
#endif
	
	tagPAConfig(){ }

	void SetH323Config( TPAH323Cfg & tH323Config )
	{
		memcpy( &m_tH323Config , &tH323Config, sizeof(TPAH323Cfg));
	}

	TPAH323Cfg & GetH323Config()
	{
		return m_tH323Config;
	}

	void SetSipConfig( TPASipCfg & tSipConfig )
	{
		memcpy( &m_tSipConfig , &tSipConfig, sizeof(TPASipCfg));
	}
	
	TPASipCfg & GetSipConfig()
	{
		return m_tSipConfig;
	}

}TPAConfig, *PTPAConfig;



/*-------------------------------------------------
 *     Main API
 *-----------------------------------------------*/
BOOL PA_Init( TPAConfig &tPAConfig ,  BOOL bOptimizeMem = TRUE);

void PA_Quit();

BOOL PA_SetCallBackFunc( TPACallBackFunc &tPACallBackFunc );


/*-------------------------------------------------
 *     Call API
 *-----------------------------------------------*/


/*���makeCallʱtdual�������� ����Ϊ˫��������tdual, ���Ǻ���ʱ˫������������ȥ
�ϲ����sendual�ŷ�˫����ȥ�� �Ͳ��ص�dualincoming, ֻ�ص�channelconnected,��disconnected*/

BOOL PA_MakeCall( 
    EmPAConfProtocol emPAType,
	HMDLCALL        *phCall,
	HMDLAPPCALL      hAppCall,
	TModuleCallInfo *ptCallInfo = NULL ,
	TCallCapbility  *ptSndCap = NULL, 
	TCallCapbility  *ptRcvCap = NULL,
	TCallInfoTP     *ptCallInfoTP = NULL,
	TCallDescriptTP *ptSndTP = NULL, 
	TCallDescriptTP *ptRcvTP = NULL,
	TDualCapList    *ptDualCapList = NULL,
    HMDLAPPCONFID    hAppConfId = 0, 
    TMDLTERLABEL    *ptTerLabel = NULL,
    TBfcpCapSet     *ptBfcp = NULL,
    TFeccCapbility  *ptFeccCap = NULL,
	TMMcuCapbility  *ptMMcuCap = NULL);

BOOL PA_AnwserCall( 
	HMDLCALL         hPACall, 
	HMDLAPPCALL      hAppCall,
	TModuleCallInfo *ptCallInfo = NULL ,
	TCallCapbility  *ptSndCap = NULL, 
	TCallCapbility  *ptRcvCap = NULL,
	TCallInfoTP     *ptCallInfoTP = NULL,
	TCallDescriptTP *ptSndTP = NULL, 
	TCallDescriptTP *ptRcvTP = NULL,
	TDualCapList    *ptDualCapList = NULL,
    HMDLAPPCONFID    hAppConfId = 0, 
    TMDLTERLABEL    *ptTerLabel = NULL,
    TBfcpCapSet     *ptBfcp = NULL,
    TFeccCapbility  *ptFeccCap = NULL,
	TMMcuCapbility  *ptMMcuCap = NULL);    


BOOL PA_RejectCall( 
	HMDLCALL      hPACall, 
	HMDLAPPCALL   hAppCall, 
	EmModuleCallDisconnectReason emReason );

BOOL PA_HangupCall( 
	HMDLCALL      hPACall, 
	HMDLAPPCALL   hAppCall,  
	EmModuleCallDisconnectReason emReason );


/*-------------------------------------------------
 *     Channel API
 *-----------------------------------------------*/
//added by jacky for Channel On/Off switch
BOOL PA_ChannelSwitch( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL ahChan[], HMDLAPPCHANNEL ahAppChan[], u8 bySize, BOOL32 bOn);

 BOOL PA_CloseChannel( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL ahChan[], HMDLAPPCHANNEL ahAppChan[], u8 bySize );

//����˫��, ���makecallʱ˫��������������sendDual���͵���makecall��������˫������
BOOL PA_SendDualSteam(HMDLCALL hPACall , HMDLAPPCALL hAppCall, TDualCapList *ptDualCapList = NULL);    

//bSucΪTRUE, ��˫���� bSucΪFalse, �ܾ�˫��, answerDual�Ƕ�����˫����Ӧ��
BOOL PA_AnswerDualStream(HMDLCALL hPACall , HMDLAPPCALL hAppCall, BOOL32 bSuc, TDualCapList *ptDualCapList = NULL);  

BOOL PA_StopDualStream(HMDLCALL hPACall , HMDLAPPCALL hAppCall, EmChannelReason emReason = emModuleChannelDisconnectNormal ); 



BOOL PA_FlowControl( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitrate );

BOOL PA_FastUpdate( HMDLCALL hPACall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );


//����ͨ��������PA_SendChanCtrlTP
BOOL PA_SendChanCtrlTP(HMDLCALL hPACall , HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, s32 nMsgType,u8 *pbyBuf, s32 nSize );
BOOL PA_SendChanCtrl(HMDLCALL hPACall , HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, s32 nMsgType,u8 *pbyBuf, s32 nSize );


/*====================================================================
������      : PA_SendFeccMsg
����        : ����Զң����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hPACall��hAppCall - ���о��
			  ptFeccAction      - Զң������TMdlFeccStruct
			  ptSrcLabel		- TMDLTERLABEL���ͣ�Զң���ͷ��ڻ����е�label����Ե�ȫ����0
			  ptDstLabel		- TMDLTERLABEL���ͣ�ԶңĿ�ķ��ڻ����е�label����Ե�ȫ����0
����ֵ˵��  : TRUE if succeed, FALSE if fails
====================================================================*/
BOOL PA_SendFeccMsg(HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMdlFeccStruct *ptFeccAction, TMDLTERLABEL *ptSrcLabel, TMDLTERLABEL *ptDstLabel);


/*-------------------------------------------------
 *     Conf API
 *-----------------------------------------------*/

//h323��׼���PA_SendConfCtrl
BOOL PA_SendConfCtrl( HMDLCALL hPACall , HMDLAPPCALL hAppCall, s32 nMsgType, u8 *pbyBuf, s32 nSize); 

//h323����MMCU PA_SendMMcuCtrl
BOOL PA_SendMMcuCtrl( HMDLCALL hPACall , HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, s32 nMsgType, u8 *pbyBuf, s32 nSize); 

//��������PA_SendConfCtrlTP,sip��
BOOL PA_SendConfCtrlTP( HMDLCALL hPACall , HMDLAPPCALL hAppCall, s32 nMsgType, u8 *pbyBuf, s32 nSize);

// ��������, ��MCʹ��
BOOL PA_MCStopConference( HMDLAPPCONFID hAppConfId );




/*-------------------------------------------------
 *     Regist API
 *-----------------------------------------------*/

/*====================================================================
�� �� ���� PA_Register
��    �ܣ� �����������ע�������ΪH323��SIP�ı�׼�ӿ�
�㷨ʵ�֣� 
��    ���� EmPAConfProtocol emPAType  : Э������
           HMDLREG         *phReg     : ָ��PA�����ָ��
           HMDLAPPREG       hAppReg   : Ӧ�ò���
           TRegistReq      *ptRegInfo : ָ��ע����Ϣ�ṹ���ָ��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
��ע    �� 1. H323�ն���GK����ע�ᣬSIP�ն���ע�����������ע��
		   2. �ӿ�ͬʱ�����״�ע��͸���ע�����ֲ�����
		      �״�ע��ʱphRegָ��ľ��ֵӦΪ0������ӿڵ���ʧ�ܣ����ֵ����Ϊ-1
			  ����ע��ʱphRegָ��ľ��ֵӦΪPA�������������ʧ�ܣ����ֵ����
		   3. ����ע������������ڻص�ע��ɹ���ſ��Խ���.
======================================================================*/
BOOL PA_Register( EmPAConfProtocol emPAType, HMDLREG *phPAReg , HMDLAPPREG hAppReg, TRegistReq *ptRegInfo );


/*====================================================================
�� �� ���� PA_UnRegister
��    �ܣ� �����������ȡ��ע�������ΪH323��SIP�ı�׼�ӿ�
�㷨ʵ�֣� 
��    ���� EmPAConfProtocol emPAType  : Э������
           HMDLREG          hPAReg    : PA���
           HMDLAPPREG       hAppReg   : Ӧ�ò���
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
��ע    �� 
======================================================================*/
BOOL PA_UnRegister( EmPAConfProtocol emPAType, HMDLREG hPAReg , HMDLAPPREG hAppReg );


/*====================================================================
�� �� ���� PA_RegisterTP
��    �ܣ� [����ӿ�]��ע�����������ע�����
�㷨ʵ�֣� 
��    ���� EmPAConfProtocol emPAType  : Э������
           HMDLREG         *phReg     : ָ��PA�����ָ��
           HMDLAPPREG       hAppReg   : Ӧ�ò���
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
��ע    �� �Ǳ�ע�ᣬͨ��XMLע�ᣬ����ע��������
======================================================================*/
BOOL PA_RegisterTP( HMDLREG *phPAReg, HMDLAPPREG hAppReg, TPARegCfg *ptPARegCfg ); 


/*====================================================================
�� �� ���� PA_GetRegInfoReqTP
��    �ܣ� [����ӿ�]��ȡע��������ϵ�ע����Ϣ
�㷨ʵ�֣� 
��    ���� s32 nAppId                   : Ӧ�ò�ı�ʶ
           TPAGetRegInfo tPAGetRegInfo  : ע����Ϣ�ṹ��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
��ע    �� 
======================================================================*/
BOOL PA_GetRegInfoReq( const s32 nAppId, HMDLREG hSipReg, HMDLREG h323Reg, TPAGetRegInfo tPAGetRegInfo );


BOOL PA_SetNatIp(u32 dwIp, EmPAConfProtocol emPAType);



/*-------------------------------------------------
 *     Conf API
 *-----------------------------------------------*/

#ifdef USE_NEW_CONF
/*====================================================================
�� �� ���� PA_MCMakeSpeaker
��    �ܣ� [��ؽӿ�] MCָ��������
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId : Ӧ�ò������
           HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_MCMakeSpeaker( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PA_MCWithdrawSpeaker
��    �ܣ� [��ؽӿ�] MC����������
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId : Ӧ�ò������
           HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_MCWithdrawSpeaker( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PA_MCMakeChair
��    �ܣ� [��ؽӿ�] MCָ����ϯ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId : Ӧ�ò������
           HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_MCMakeChair( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PA_MCWithdrawChair
��    �ܣ� [��ؽӿ�] MC������ϯ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId : Ӧ�ò������
           HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_MCWithdrawChair( HMDLAPPCONFID hAppConfId, HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PA_MCSendThisSource
��    �ܣ� [��ؽӿ�] MCָ��ѡ��
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������
           HMDLCALL        hViewer      : Э��ջ���о��(ѡ����)
           HMDLAPPCALL     hAppViewer   : Ӧ�ò���о��(ѡ����)
           HMDLCALL        hViewed      : Э��ջ���о��(��ѡ����)
           HMDLAPPCALL     hAppViewed   : Ӧ�ò���о��(��ѡ����)
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_MCSendThisSource( HMDLAPPCONFID hAppConfId, HMDLCALL hViewer, HMDLAPPCALL hAppViewer, HMDLCALL hViewed, HMDLAPPCALL hAppViewed );

/*====================================================================
�� �� ���� PA_MCCancelSendThisSource
��    �ܣ� [��ؽӿ�] MCȡ��ѡ��
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLAPPCONFID   hAppConfId   : Ӧ�ò������
           HMDLCALL        hViewer      : Э��ջ���о��(ѡ����)
           HMDLAPPCALL     hAppViewer   : Ӧ�ò���о��(ѡ����)
           HMDLCALL        hViewed      : Э��ջ���о��(��ѡ����)
           HMDLAPPCALL     hAppViewed   : Ӧ�ò���о��(��ѡ����)
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_MCCancelSendThisSource( HMDLAPPCONFID hAppConfId,  HMDLCALL hViewer, HMDLAPPCALL hAppViewer, HMDLCALL hViewed, HMDLAPPCALL hAppViewed );



/*====================================================================
�� �� ���� PA_TerMakeMeSpeaker
��    �ܣ� [��ؽӿ�] �ն����뷢��
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_TerMakeMeSpeaker( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PA_TerMakeMeChair
��    �ܣ� [��ؽӿ�] �ն�������ϯ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_TerMakeMeChair( HMDLCALL hPACall, HMDLAPPCALL hAppCall );


/*====================================================================
�� �� ���� PA_ChairCancelMakeMeChair
��    �ܣ� [��ؽӿ�] ��ϯ�ͷ���ϯ����
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_ChairCancelMakeMeChair( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PA_ChairSendThisSourceCmd
��    �ܣ� [��ؽӿ�] ��ϯѡ���ն�
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
		   TMDLTERLABEL    tTerLabel  : �ն�LABEL
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_ChairSendThisSourceCmd( HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );

/*====================================================================
�� �� ���� PA_ChairCancelSendThisSource
��    �ܣ� [��ؽӿ�] ��ϯȡ��ѡ���ն�
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_ChairCancelSendThisSource( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

/*====================================================================
�� �� ���� PA_ChairBroadcastTerminalReq
��    �ܣ� [��ؽӿ�] ��ϯ��MC�ύ�����ն˵�����
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
		   TMDLTERLABEL    tTerLabel  : �ն�LABEL
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_ChairBroadcastTerminalReq( HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );

/*====================================================================
�� �� ���� PA_ChairBroadcastTerminalCmd
��    �ܣ� [��ؽӿ�] ��ϯ��MC�ύ�����ն˵�����
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
		   TMDLTERLABEL    tTerLabel  : �ն�LABEL
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_ChairBroadcastTerminalCmd( HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );

/*====================================================================
�� �� ���� PA_ChairCancelBroadcastTerminal
��    �ܣ� [��ؽӿ�] ��ϯȡ�������ն�
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� HMDLCALL        hPACall    : Э��ջ���о��
           HMDLAPPCALL     hAppCall   : Ӧ�ò���о��
����ֵ  �� �ɹ�������TRUE��ʧ�ܣ�����FALSE
======================================================================*/
BOOL PA_ChairCancelBroadcastTerminal( HMDLCALL hPACall, HMDLAPPCALL hAppCall );

#endif

#ifdef _ENABLE_QUANTUM_PROJECT_
/*====================================================================
��	 ��   ��: kdvPAQuantumInit
��	      ��: ���ñ������Ӽ��ܳ�ʼ���������������ñ����������ýӿڣ�
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: tQuantumInitParam			- �������Ӽ��ܳ�ʼ������
			  emPAType                  - Э������
��   ��   ֵ: �ɹ� - TRUE
ʧ�� - FALSE
====================================================================*/
BOOL32 kdvPAQuantumInit(TQtInitParam &tQuantumInitParam, EmPAConfProtocol emPAType);

#endif

#endif
