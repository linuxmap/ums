/*****************************************************************************
ģ����      : radiusstack
�ļ���      : radiusstack.h
����ļ�    : radiusstack.cpp
�ļ�ʵ�ֹ���: ���ϲ�Ӧ���ṩAPI�����ͻص�����ԭ��
����        : 
�汾        : V4.0  Copyright(C) 2006 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2006.11.15  4.0         ���Ҿ�      radius server ����Ҫ�Ľӿڶ���
******************************************************************************/

#ifndef _RADIUSSTACK_H_
#define _RADIUSSTACK_H_

#include "osp.h"


////////////////////////////////���Դ�ӡ����////////////////////////////////
//��ӡkdvradius������Ϣ
API void kdvradiushelp();
//����:��ӡkdvradius�汾��Ϣ
API void kdvradiusver();
//���ܣ�������־����
API void setradiuslog(u8 level);
//��ӡЭ��ջ����
API void showradius();
//��ӡSession��
API void showradiustable();
//��ӡSession��Ϣ
API void showradiusmessage(s32 i);


////////////////////////////////�궨��/////////////////////////////////////
#define VER_KDVRADIUS "40.10.01.00.16.101108"

#define SERVERIP    inet_addr("127.0.0.1")
#define RADIUS_ACCESS_PORT	1812
#define RADIUS_ACCT_PORT	1813

#define RADIUS_ERROR 0
#define RADIUS_OK	 1
#define RADIUS_FAIL  -1

#define RAD_TRANSACTION_MAX 100
#define RAD_MESSAGE_POOL_SIZE RAD_TRANSACTION_MAX * 2

#define RAD_TRANS_TIMEOUT_LEN 15000 //�����һ�γ�ʱ��ʱ�䳤��
#define RAD_OPERATE_MSG_SAFEGUARD_TIME  10000  //����Ӧ����Ϣ�ı�����ʱ������ֹ��Ϣ�屻����
#define RAD_REQ_RETRY_MAX               2   //�ط��Ĵ�������=�ܹ����ʹ���-1

#define SECRET_DATA_LEN_MAX 128


#ifndef DECLARE_OPAQUE
#define DECLARE_OPAQUE(name)    typedef struct { int unused; } name##__ ; \
	typedef const name##__ * name; \
typedef name*  LP##name
#endif


////////////////////////////////���Զ���///////////////////////////////////

#define RAD_ATTR_NULL 0 //���������
#define RAD_ATTR_USER_NAME 1 //User-Name(String)
#define RAD_ATTR_USER_PASSWORD 2 //User-Password(String)
#define RAD_ATTR_CHAP_PASSWORD 3 //CHAP-Password(1 octet + String)
#define RAD_ATTR_NAS_IP_ADDRESS 4 //NAS-IP-Address(Address)
#define RAD_ATTR_NAS_PORT 5 //NAS-Port(Value)
#define RAD_ATTR_SERVICE_TYPE 6 //Service-Type(Value)
#define RAD_ATTR_FRAMED_PROTOCOL 7 //Framed-Protocol(Value)
#define RAD_ATTR_FRAMED_IP_ADDRESS 8 //Framed-IP-Address(Address)
#define RAD_ATTR_FRAMED_IP_NETMASK 9 //Framed-IP-Netmask(Address)
#define RAD_ATTR_FRAMED_ROUTING 10 //Framed-Routing(Value)
#define RAD_ATTR_FILTER_ID 11 //Filter-Id(Text)
#define RAD_ATTR_FRAMED_MTU 12 //Framed-MTU(Value)
#define RAD_ATTR_FRAMED_COMPRESSION 13 //Framed-Compression(Value)
#define RAD_ATTR_LOGIN_IP_HOST 14 //Login-IP-Host(Address)
#define RAD_ATTR_LOGIN_SERVICE 15 //Login-Service(Value)
#define RAD_ATTR_LOGIN_TCP_PORT 16 //Login-TCP-Port(Value)

#define RAD_ATTR_REPLY_MESSAGE 18 //Reply-Message(Text)
#define RAD_ATTR_CALLBACK_NUMBER 19 //Callback-Number(String)
#define RAD_ATTR_CALLBACK_ID 20 //Callback-Id(String)

#define RAD_ATTR_FRAMED_ROUTE 22 //Framed-Route(Text)
#define RAD_ATTR_FRAMED_IPX_NETWORK 23 //Framed-IPX-Network(Value)
#define RAD_ATTR_STATE 24 //State(String)
#define RAD_ATTR_CLASS 25 //Class(String)
#define RAD_ATTR_VENDOR_SPECIFIC 26 //Vendor-Specific(...)
#define RAD_ATTR_SESSION_TIMEOUT 27 //Session-Timeout(Value)
#define RAD_ATTR_IDLE_TIMEOUT 28 //Idle-Timeout(Value)
#define RAD_ATTR_TERMINATION_ACTION 29 //Termination-Action(Value)
#define RAD_ATTR_CALLED_STATION_ID 30 //Called-Station-Id(String)
#define RAD_ATTR_CALLING_STATION_ID 31 //Calling-Station-Id(String)
#define RAD_ATTR_NAS_IDENTIFIER 32 //NAS-Identifier(String)
#define RAD_ATTR_PROXY_STATE 33 //Proxy-State(String)
#define RAD_ATTR_LOGIN_LAT_SERVICE 34 //Login-LAT-Service(String)
#define RAD_ATTR_LOGIN_LAT_NODE 35 //Login-LAT-Node(String)
#define RAD_ATTR_LOGIN_LAT_GROUP 36 //Login-LAT-Group(String)
#define RAD_ATTR_FRAMED_APPLETALK_LINK 37 //Framed-AppleTalk-Link(Value)
#define RAD_ATTR_FRAMED_APPLETALK_NETWORK 38 //Framed-AppleTalk-Network(Value)
#define RAD_ATTR_FRAMED_APPLETALK_ZONE 39 //Framed-AppleTalk-Zone(String)

#define RAD_ATTR_ACCT_STATUS_TYPE 40 //Acct-Status-Type(Value)
#define RAD_ATTR_ACCT_DELAY_TIME 41 //Acct-Delay-Time(Value)
#define RAD_ATTR_ACCT_INPUT_OCTETS 42 //Acct-Input-Octets(Value)
#define RAD_ATTR_ACCT_OUTPUT_OCTETS 43 //Acct-Output-Octets(Value)
#define RAD_ATTR_ACCT_SESSION_ID 44 //Acct-Session-Id(String)
#define RAD_ATTR_ACCT_AUTHENTIC 45 //Acct-Authentic(Value)
#define RAD_ATTR_ACCT_SESSION_TIME 46 //Acct-Session-Time(Value)
#define RAD_ATTR_ACCT_INPUT_PACKETS 47 //Acct-Input-Packets(Value)
#define RAD_ATTR_ACCT_OUTPUT_PACKETS 48 //Acct-Output-Packets(Value)
#define RAD_ATTR_ACCT_TERMINATE_CAUSE 49 //Acct-Terminate-Cause(Value)
#define RAD_ATTR_ACCT_MULTI_SESSION_ID 50 //Acct-Multi-Session-Id(String)
#define RAD_ATTR_ACCT_LINK_COUNT 51 //Acct-Link-Count(Value)

#define RAD_ATTR_CHAP_CHALLENGE 60 //CHAP-Challenge(String)
#define RAD_ATTR_NAS_PORT_TYPE 61 //NAS-Port-Type(Value)
#define RAD_ATTR_PORT_LIMIT 62 //Port-Limit(Value)
#define RAD_ATTR_LOGIN_LAT_PORT 63 //Login-LAT-Port(String)

#define RAD_ATTR_MESSAGE_AUTHENTICATOR 80 //Message-Authenticator(String)

#define RAD_ATTR_USER_CREDIT_AMOUNT 224 //User-credit-amount
#define RAD_ATTR_CALL_TYPE          225 //account-type

typedef u8 RadAttributeType;

////////////////////////////��չ���Զ���(��������ͨ���淶)/////////////////////////
#define RAD_ATTR_SPEC_USER_TYPE           160
#define RAD_ATTR_SPEC_SITE_RATE           164
#define RAD_ATTR_SPEC_CONFENCE_TYPE       165
#define RAD_ATTR_SPEC_RESOURCE_NUM        166
#define RAD_ATTR_SPEC_ACCT_BEGIN_TIME     169
#define RAD_ATTR_SPEC_ACCT_END_TIME       170
#define RAD_ATTR_SPEC_ACCT_ITEM           171
#define RAD_ATTR_SPEC_ACCT_TYPE           172
#define RAD_ATTR_SPEC_ACCT_FEE            173
#define RAD_ATTR_SPEC_ACCT_FLAG           175
#define RAD_ATTR_SPEC_DUAL_VIDEO          211
#define RAD_ATTR_SPEC_DATA_RATE           212
#define RAD_ATTR_SPEC_FLOW_MEDIA_TYPE     214   
#define RAD_ATTR_SPEC_VERSION             254
#define RAD_ATTR_SPEC_PRODUCTI_ID         255

#define RAD_ATTR_SPEC_CONFENCE_ID         180
#define RAD_ATTR_SPEC_TERMINAL_NUM        181
#define RAD_ATTR_SPEC_MULTIPIC_NUM        182
#define RAD_ATTR_SPEC_RATEADAPTER_NUM     183
#define RAD_ATTR_SPEC_MULTIVOICE_NUM      184
#define RAD_ATTR_SPEC_DATACONFENCE        185
#define RAD_ATTR_SPEC_ENCRYPT_USED        186
#define RAD_ATTR_SPEC_CASCADE_USED        187
#define RAD_ATTR_SPEC_CONFENCE_NAME       188
#define RAD_ATTR_SPEC_MULTICAST_USED      189  


//////////////////////////////////////ö�ٶ���/////////////////////////////////////
//Radius Msg-Type
typedef enum
{
	RADMSG_UNKOWN = 0,
	RADMSG_ACCESS_REQUEST = 1, //Access-Request
	RADMSG_ACCESS_ACCEPT  = 2, //Access-Accept
	RADMSG_ACCESS_REJECT  = 3, //Access-Reject
	RADMSG_ACCOUNTING_REQUEST = 4, //Accounting-Request
	RADMSG_ACCOUNTING_RESPONSE = 5, //Accounting-Response
	RADMSG_ACCESS_CHALLENGE = 11 //Access-Challenge
}RadMsgType;

//Service-Type
typedef enum
{
    RAD_ST_LOGIN=1,
    RAD_ST_FRAMED,
    RAD_ST_CALLBACK_LOGIN,
    RAD_ST_CALLBACK_FRAMED,
    RAD_ST_OUTBOUND,
    RAD_ST_ADMINISTRATIVE,
    RAD_ST_NAS_PROMPT,
    RAD_ST_AUTHENTICATE_ONLY,
    RAD_ST_CALLBACK_NAS_PROMPT,
    RAD_ST_CALL_CHECK=10,
    RAD_ST_CALLBACK_ADMINISTRATIVE,
}RadServiceType;


//Acct-Terminate-Cause
typedef enum
{
    RAD_ATC_USER_REQUEST=1,
    RAD_ATC_LOST_CARRIER,
    RAD_ATC_LOST_SERVICE,
    RAD_ATC_IDLE_TIMEOUT,
    RAD_ATC_SESSION_TIMEOUT,
    RAD_ATC_ADMIN_RESET,
    RAD_ATC_ADMIN_REBOOT,
    RAD_ATC_PORT_ERROR,
    RAD_ATC_NAS_ERROR,
    RAD_ATC_NAS_REQUEST=10,
    RAD_ATC_NAS_REBOOT,
    RAD_ATC_PORT_UNNEEDED,
    RAD_ATC_PORT_PREEMPTED,
    RAD_ATC_PORT_SUSPENDED,
    RAD_ATC_SERVICE_UNAVAILABLE,
    RAD_ATC_CALLBACK,
    RAD_ATC_USER_ERROR,
    RAD_ATC_HOST_REQUEST,
}RadAcctTerminateCause;

//NAS-Port-Type
typedef enum
{
    RAD_NPT_ASYNC=0,
    RAD_NPT_SYNC,
    RAD_NPT_ISDN_SYNC,
    RAD_NPT_ISDN_ASYNC_V120,
    RAD_NPT_ISDN_ASYNC_V110,
    RAD_NPT_VIRTUAL,
    RAD_NPT_PIAFS,
    RAD_NPT_HDLC,// CLEAR CHANNEL,
    RAD_NPT_X25,
    RAD_NPT_X75,
    RAD_NPT_G3_FAX = 10,
    RAD_NPT_SDSL,// SYMMETRIC DSL,
    RAD_NPT_ADSL_CAP, //- ASYMMETRIC DSL, CARRIERLESS AMPLITUDE PHASE,MODULATION
    RAD_NPT_ADSL_DMT,//- ASYMMETRIC DSL, DISCRETE MULTI-TONE
    RAD_NPT_IDSL ,//- ISDN DIGITAL SUBSCRIBER LINE
    RAD_NPT_ETHERNET,
    RAD_NPT_XDSL,// - DIGITAL SUBSCRIBER LINE OF UNKNOWN TYPE
    RAD_NPT_CABLE,
    RAD_NPT_WIRELESS_OTHER,
    RAD_NPT_WIRELESS_IEEE802_11 =19,
}RadNASPortType;

//Login-Service-Type
typedef enum
{
	RAD_LST_Telnet = 0 ,
	RAD_LST_Rlogin = 1 ,
	RAD_LST_TCP_Clear = 2,
	RAD_LST_PortMaster = 3, //(proprietary)
	RAD_LST_LAT = 4,
	RAD_LST_X25_PAD = 5,
	RAD_LST_X25_T3POS = 6,
	RAD_LST_TCP_Clear_Quiet = 8 //(suppresses any NAS-generated connect string)
}RadLoginServiceType;

//Acct-Status-Type
typedef enum
{
    RAD_AST_Start=1,
    RAD_AST_Stop=2,
    RAD_AST_Interim_Update=3,
    RAD_AST_Accounting_On=4,
    RAD_AST_Accounting_Off=5,
       //...9-14 Reserved for Tunnel Accounting  //��������Ʒ�
    RAD_AST_Reserved_for_Failed=15,
}RadAcctStatusType;

//Acct-Authentic  ��Ȩ����
//�����й���Ȩ���û��������ɼ��ʰ�
typedef enum
{
    RAD_AA_RADIUS=1,
    RAD_AA_Local,
    RAD_AA_Remote, 
}RadAcctAuthentic;

typedef enum
{
    RAD_ACCOUNT_CALL_TYPE_TELEPHONE,   //�绰�Ʒ�
    RAD_ACCOUNT_CALL_TYPE_VOIP,        //��ҵ��Ʒ�
}RadAcctCallType;

typedef enum
{
    RAD_CALL_TYPE_TELE=1,
    RAD_CALL_TYPE_VOIP,    
}RadCallType;


typedef enum
{
    RAD_TIMER_OPT,          //���յ��ظ������ʱ�䱣��
    RAD_TIMER_SEND_REQ,     //�����ط���ʱ��
}RadTimerId;

typedef enum
{
    PT_ERROR = 0,
    PT_WARN,
    PT_NORMAL,
	PT_ALL
} PT_LEVEL;


/////////////////////////////////////�ṹ����/////////////////////////////////////

DECLARE_OPAQUE(RadSessionHandle);

typedef u8 (*FuncRadRcvAcctResponse)(RadSessionHandle handle);
typedef u8 (*FuncRadRcvAccAccept)(RadSessionHandle handle);
typedef u8 (*FuncRadRcvAccReject)(RadSessionHandle handle);
typedef u8 (*FuncRadAcctTimeOut)(RadSessionHandle handle);
typedef u8 (*FuncRadAccTimeOut)(RadSessionHandle handle);

//ΪRadius���������������Ϣ�ص��ӿ� 
typedef u8 (*FuncRadRcvAcessRequest)(RadSessionHandle hSession);
typedef u8 (*FuncRadRcvAccountRequest)(RadSessionHandle hSession);

typedef struct 
{
    FuncRadRcvAcctResponse acctResponseHook;
    FuncRadRcvAccAccept accAcceptHook;
    FuncRadRcvAccReject accRejectHook;
    FuncRadAcctTimeOut acctTimeOutHook;
    FuncRadAccTimeOut accTimeOutHook;
    FuncRadRcvAcessRequest accessRequestHook;
    FuncRadRcvAccountRequest accountRequestHook;
} RadiusEvent;


typedef u8 UINT8;
typedef u16 UINT16;
//typedef int STATUS;


void lpt(s32 nLevel, s8 * format,...);


/////////////////////////////////////��Ϣ�շ�����/////////////////////////////////////

/*====================================================================
��������radCreateSession 
���ܣ�	����һ����Session
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�� �� ��  ��: MsgType - Radius��Ϣ����
�� �� ��  ��: handle  - Session���

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radCreateSession(RadSessionHandle *handle, RadMsgType MsgType);

/*====================================================================
�������� radReqAddAttr
���ܣ�   Req����ض�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�� �� ��  ��: handle  - Session���
			  type	  - ��������
			  date	  - ����
			  len	  - ����

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radReqAddAttr(RadSessionHandle handle, RadAttributeType type, u8 *data, u8 len);

/*====================================================================
��������radReqGetAttr
����:   ��ȡ������Ϣ���ض�����
����:handle	�Ự���
   	type	Ҫ��ȡ������
   	len		data�ĳ���
   	index	��ʾ�ڼ����������ԣ�����1
���:data	����������
����:�ɹ�����data��ʵ�ʳ���
   	 ʧ�ܻ��߳�����ERROR
====================================================================*/
u8 radReqGetAttr(RadSessionHandle handle, RadAttributeType type, u8 *data, u8 len, u8 index = 1);


/*====================================================================
����:��ȡӦ����Ϣ���ض�����
����:handle	�Ự���
   	type		Ҫ��ȡ������
   	len		data�ĳ���
   	index	��ʾ�ڼ����������ԣ�����1
���:data	����������
����:�ɹ�����data��ʵ�ʳ���
   	        ʧ�ܻ��߳�����ERROR
====================================================================*/
u8 radRspGetAttr(RadSessionHandle handle, RadAttributeType type, u8 *data, u8 len, u8 index = 1);//index ��1��ʼ

/*====================================================================
�������� radReqCheckAttr
���ܣ�   ���REQ��Ϣ���Ƿ����ض�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����handle  �Ự���
			  type	  Ҫ��ȡ������

����ֵ˵�����ɹ�������Ϣ�����Գ��ֵĴ���
			ʧ�ܻ��߳�����RADIUS_ERROR
====================================================================*/
u8 radReqCheckAttr(RadSessionHandle handle, RadAttributeType type);

/*====================================================================
�������� radReqCheckAttr
���ܣ�   ���RSP��Ϣ���Ƿ����ض�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����handle  �Ự���
			  type	  Ҫ��ȡ������

����ֵ˵�����ɹ�������Ϣ�����Գ��ֵĴ���
			ʧ�ܻ��߳�����RADIUS_ERROR
====================================================================*/
u8 radRspCheckAttr(RadSessionHandle handle, RadAttributeType type);

/*====================================================================
�������� radSendReq
���ܣ�   ����������Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����hSessionHandle	�Ự���
              pbyUserData       �û����ݻ�����ָ��
              wDataLen          �û����ݳ���
����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radSendReq(RadSessionHandle hSessionHandle, u8 *pbyUserData, u16 wDataLen);

/*====================================================================
�������� radEndSession
���ܣ��ر�Session
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����handle	�Ự���
����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radEndSession(RadSessionHandle handle);

/*====================================================================
�������� radGetUserData
���ܣ����Session���û�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����handle	   �Ự���
              pbyInOutBuf  ���ݻ���
����ֵ˵�����ɹ�����TRUE,���򷵻�FALSE
====================================================================*/
BOOL32 radGetUserData(RadSessionHandle handle, u8 *pbyInOutBuf, u16 wInBufLen,u16 &wOutLen);

/*====================================================================
�������� printSessionMsg
���ܣ���ӡsession��Ϣ������Req��Rsp��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����handle	�Ự���
����ֵ˵����
====================================================================*/
void printSessionMsg(RadSessionHandle handle);

/////////////////////////////////////Э��ջ���ú���/////////////////////////////////////

/*====================================================================
�������� RadStackInit
���ܣ�RADIUS��ʼ��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ip	RADIUS��������ַ

����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE.
====================================================================*/
BOOL32 RadStackInit(u32 ip = SERVERIP);

/*====================================================================
�������� radStackSetServerIp
���ܣ�����ServerIP
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ip	IP��ַ

����ֵ˵����
====================================================================*/
u8 radStackSetServerIp(u32 ip);

/*====================================================================
��������radStackSetServerAccessPort 
���ܣ�  ����Server��Access�˿�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵����
====================================================================*/
u8 radStackSetServerAccessPort(u16 port = RADIUS_ACCESS_PORT);

/*====================================================================
��������radStackSetServerAcctPort 
���ܣ�  ����Server��Account�˿�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵����
====================================================================*/
u8 radStackSetServerAcctPort(u16 port = RADIUS_ACCT_PORT);

/*====================================================================
��������radSetSecret 
���ܣ�����secret
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radSetSecret(u8 *secret, u8 bySecretLen);

/*====================================================================
��������radStackSetMaxRetryTimes 
���ܣ����÷�������������Դ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radStackSetMaxRetryTimes(u8 maxRetryTimes = RAD_REQ_RETRY_MAX);

/*====================================================================
��������radStackSetTimeOutInterval 
���ܣ����÷��ͳ�ʱ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radStackSetTimeOutInterval(u32 TimeOutInterval = RAD_TRANS_TIMEOUT_LEN);

/*====================================================================
��������radStackSetCallBack
���ܣ�  ����radStack�Ļص�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵����
====================================================================*/
void radStackSetCallBack(RadiusEvent* ptUserCB);

/*====================================================================
��������radStackStart 
���ܣ�  ����Э��ջ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����bAutoSelect	�Ƿ��Զ�select

����ֵ˵����
====================================================================*/
s32 radStackStart(BOOL32 bAutoSelect);

/*====================================================================
�������� radStackSelect
���ܣ�Э��ջSelect��
�������ʱ��ʹ��AutoSelect������Ҫ�ֶ����ڵ��øú���������Ϣ��ȡ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵����
====================================================================*/
s32 radStackSelect();

/*====================================================================
��������radStackEnd 
���ܣ�  �ر�Э��ջ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

����ֵ˵����
====================================================================*/
s32 radStackEnd();



/*====================================================================
��������radStackServerStart 
���ܣ�  Server������Э��ջ.��������socket(access/accout)
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����bAutoSelect	�Ƿ��Զ�select

����ֵ˵����
====================================================================*/
s32 radStackServerStart(BOOL32 bAutoSelect);

/*====================================================================
��������radSendAccessAccept 
���ܣ�  ����Access-Accept��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����hSession  ��Ӧ����Ự�ľ��

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radSendAccessAccept(RadSessionHandle hSession);


/*====================================================================
��������radSendAccessReject 
���ܣ�  ����Access-Reject��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����hSession  ��Ӧ����Ự�ľ��

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radSendAccessReject(RadSessionHandle hSession);


/*====================================================================
��������radSendAccountResponse
���ܣ�  ����Account-Response��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����hSession  ��Ӧ����Ự�ľ��

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radSendAccountResponse(RadSessionHandle hSession);


/*====================================================================
��������radGetUserName
����:��ȡ access-request ��Ϣ��username
����:hSession	�Ự���
   	 pNameBuf	���ڱ������ֵ�buf
     byBufLen    buf����
     wNameLen   ���ֵ�ʵ�ʳ��ȡ���ȡʧ�ܸ�ֵΪ0��
���:pNameBuf   
     wNameLen  
����:
====================================================================*/
//void radGetUserName(RadSessionHandle hSession, u8 *pNameBuf, u8 byBufLen, u16 &wNameLen);
BOOL32 radGetUserData(RadSessionHandle handle, u8 *pbyInOutBuf, u16 wInBufLen,u16 &wOutLen);

/*====================================================================
��������radGetPassword
����:  ��ȡ access-request ��Ϣ�о������ܺ��password
����:  hSession	    �Ự���
       pPassword    ����password��buf
       byBufLen     buf����
���:  pPassword	
       wPasswordLen   passwordʵ�ʳ���. ��ȡʧ�ܸ�ֵΪ0��
����:
====================================================================*/
void radGetPassword(RadSessionHandle hSession, u8 *pPassword, u8 byBufLen, u16 &wPasswordLen);



/*====================================================================
��������radGetAccountType
����: ��� account-request ��Ϣ�м�������
����:hSession	�Ự���
���: 
���أ��������� start(1)/stop(2). ʧ�ܻ������RADIUS_ERROR�� 
====================================================================*/
u32 radGetAccountRequestType(RadSessionHandle hSession);


/*====================================================================
��������radCloseHandle
����:�ر�������
����:hSession	�Ự���

����:�ɹ����� RADIUS_OK
   	        ʧ�ܻ��߳����� RADIUS_ERROR 
====================================================================*/
u8 radCloseHandle(RadSessionHandle hSession);

/*====================================================================
�������� radRspAddAttr
���ܣ�   ��Response��Ϣ������ض�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�� �� ��  ��: hSession  - Session���
			  tAttrType	  - ��������
			  pbyDate	  - ����
			  byLen	  - ����

����ֵ˵�����ɹ�����RADIUS_OK��ʧ�ܷ���RADIUS_ERROR.
====================================================================*/
u8 radRspAddAttr(RadSessionHandle hSession, RadAttributeType tAttrType, u8 *pbyData, u8 byLen);


//�����չ����ͷ��
u8 radReqAddSpecAttrHead(RadSessionHandle hSession, u8 *pVenderId,u8 byLen);

//�����չ�������ݣ������ԣ�
u8 radReqAddSpecAttrContent(RadSessionHandle hSession,RadAttributeType tSubAttrType, u8 *pVenderId,u8 byLen);

//��request��Ϣ�л�ȡ��չ����ֵ
u8 radReqGetSpecAttr(RadSessionHandle hSession,RadAttributeType tSubAttrType,u8* pByValueBuf, u8 byBufLen);


#endif //_RADIUSSTACK_H_
