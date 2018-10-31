
#ifndef _SIPADAPTER_
#define _SIPADAPTER_

#ifdef _LINUX_
#include "osp.h"

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#endif

#ifndef _CBB50_TPS_
#define _CBB50_TPS_
#endif

#include "rvsipstack.h"
#include "rvsdpmsg.h"
#include "kdvtype.h"
#include "sipcallstdmsg.h" 
#include "sipconfnonstdstruct.h"

extern u32 g_dwLogOn;
extern BOOL32 g_bFirstInviteWithDualMedia;

enum EmSipLogModule
{
	emSipMdlBegin,
	emSipMdlNone = emSipMdlBegin,
	emSipMdlAll,
	emSipMdlAllExceptFrequent,
	emSipMdlCall,
	emSipMdlCap,
	emSipMdlChannel,
	emSipMdlConf,
	emSipMdlRegister,
	emSipMdlFrequent,
	emSipMdlEnd = 30,
};
enum EmSipLogType
{
	emSipLogBegin,
	emSipLogNormal,
	emSipLogWarning,
	emSipLogError,
};

RV_DECLARE_HANDLE(RvSipAppChanHandle);
RV_DECLARE_HANDLE(RvSipChanHandle);
RV_DECLARE_HANDLE(RvSipAppRASHandle);
RV_DECLARE_HANDLE(RvSipRASHandle);
/*====================================================================
������      : NotifyNewCallT
����        : �������о��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall   - Э��ջ���о��
    		  lphaCall - Ӧ�ó�����о��
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyNewCallT)( RvSipCallLegHandle hsCall, LPRvSipAppCallLegHandle lphaCall, const void* pBuf,u16 wBufLen);


/*====================================================================
������      : NotifyCallCtrlMsgT
����        : ���п���֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
			  hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyCallCtrlMsgT)(RvSipAppCallLegHandle haCall,RvSipCallLegHandle hsCall,u16 wMsgType,
											  const void* pBuf,u32 dwBufLen);

/*====================================================================
������      : NotifyChanCtrlMsgT
����        : �ŵ�����֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haChan  - Ӧ�ó����ŵ����
			  hsChan  - Э��ջ�ŵ����
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyChanCtrlMsgT)(RvSipAppCallLegHandle haCall,RvSipCallLegHandle hsCall,
											 RvSipAppChanHandle haChan,RvSipChanHandle hsChan,
											 u16 wMsgType,const void* pBuf,u16 wBufLen);

/*====================================================================
������      : NotifyConfCtrlMsgT
����        : �������֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyConfCtrlMsgT)(RvSipAppCallLegHandle haCall,RvSipCallLegHandle hsCall,
											 RvSipTranscHandle hTransc,u16 wMsgType,const void* pBuf,u16 wBufLen);
/*====================================================================
������      : NotifyRasCtrlMsgT
����        : RAS��Ϣ֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haRas   - Ӧ�ó���RAS���
			  hsRas   - Э��ջRAS���
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyRegCtrlMsgT)(IN  RvSipAppRegClientHandle         hAppRegClient,
											IN  RvSipRegClientHandle            hRegClient,
                                            u16 wMsgType, const void* pBuf,u16 wBufLen);

/*====================================================================
������      : NotifyFeccMsgT
����        : H.224, H.281���ܻص�����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall     - Э��ջ���о��
              hsChan     - Э��ջ�ŵ����
			  feccStruct - Զң����(TFeccStruct)
			  terSrc     - Դ���ն��б�
			  terDst     - Դ���ն��б�
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV *NotifyFeccMsgT)( RvSipCallLegHandle hsCall, TFeccStruct tFeccStruct, TTERLABEL tTerSrc, TTERLABEL tTerDst);

/*====================================================================
������      : NotifyUMSCtrlMsgT
����        : UMS��Ϣ֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: RvSipTranscHandle  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haRas   - Ӧ�ó���RAS���
			  hsRas   - Э��ջRAS���
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (RVCALLCONV* NotifyUMSCtrlMsgT)(IN RvSipTranscHandle hTransc, u16 wMsgType, const void* pBuf, u16 wBufLen);
//�ص�����ָ��ṹ
typedef struct 
{
	NotifyRegCtrlMsgT	fpRegCtrlMsg;
    NotifyNewCallT		fpNewCall;
	NotifyCallCtrlMsgT  fpCallCtrlMsg;
    NotifyChanCtrlMsgT  fpChanCtrlMsg;
	NotifyFeccMsgT      fpFeccCtrlMsg;
	NotifyConfCtrlMsgT  fpConfCtrlMsg;
	NotifyUMSCtrlMsgT   fpUMSCtrlMsg;
}SIPEVENT,*LPSIPEVENT;

class CMediaStreamCtrl;

class PROTO_API CSipInterface
{
public:
   /*====================================================================
   ��	 ��   ��: SipAdapterInit
   ��	      ��: ��ʼ��Sip����ģ��
   �� �� ʵ  ��: 
   ����ȫ�ֱ���: 
   �������˵��: tSipAdapterCfg 

   ��   ��   ֵ: �ɹ� - &g_hApp
   ʧ�� - NULL		
	====================================================================*/
    static RvStatus AdapterInit( TSipAdapterCfg tSipAdapterCfg );
	/*====================================================================
	��	 ��   ��: SipAdapterQuit
	��	      ��: �˳�SIP����ģ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: ��
	��   ��   ֵ: ��
	====================================================================*/
    static void AdapterQuit();
	/*====================================================================
	��	 ��   ��: SetSipAppCallBack
	��	      ��: ע��Ӧ�ûص�����
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static void  SetAppCallBack(IN LPSIPEVENT lpEvent);

	/*====================================================================
	��	 ��   ��: CbNotifyFeccMsg
	��	      ��: ע��Զң�ص�����
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsChan   --- ��Ӧsip�ĺ��о��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static s32 CbNotifyFeccMsg(MemId hsChan, TFeccStruct feccStruct, TTERLABEL terSrc, TTERLABEL terDst);
	/*====================================================================
	��	 ��   ��: SipCheckMessage
	��	      ��: �����Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: u32 - ����ʱ��(����)
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static void CheckMessage( u32 dwMiliSecond );
	/*====================================================================
	��	 ��   ��: CreateNewCall
	��	      ��: �����µĺ��У������ڷ��ͺ�����Ϣǰ����,�����ȴ����ٺ���
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus CreateNewCall(IN RvSipAppCallLegHandle haCall, OUT LPRvSipCallLegHandle lphsCall );
	/*====================================================================
	��	 ��   ��: CreateNewChan
	��	      ��: �����µ�ͨ�������߼�ǰ�ȴ���
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus CreateNewChan( IN RvSipCallLegHandle hsCall, IN RvSipAppChanHandle haChan, IN EmSipMediaType emMediaType, IN BOOL32 bSend, OUT LPRvSipChanHandle lphsChan );
	/*====================================================================
	��	 ��   ��: ReleaseChan
	��	      ��: �ͷ�һ��ͨ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: lpEvent - �ص������ṹָ��
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus ReleaseChan(IN RvSipCallLegHandle hsCall, IN RvSipChanHandle hsChan );
	/*====================================================================
	��	 ��   ��: SendCallCtrlMsg
	��	      ��: ���ͺ��п�����Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsCall  - ���о��
	msgType - ��Ϣ����
	pBuf    - ����������
	nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus SendCallCtrlMsg( RvSipCallLegHandle hsCall, u16 wMsgType, const u8* pbyBuf, u32 dwBufLen );
	/*====================================================================
	��	 ��   ��: SendChanCtrlMsg
	��	      ��: �����ŵ�������Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsChan  - �ŵ����
	msgType - ��Ϣ����
	pBuf    - ����������
	nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus SendChanCtrlMsg( RvSipCallLegHandle hsCall, IN RvSipChanHandle hsChan, IN EmSipChanCtrlMsgType emMsgType, IN const u8* pbyBuf,IN u16 wBufLen );
	/*====================================================================
	��	 ��   ��: SetSdpSession
	��	      ��: sdp session info
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsCall  - ���о��
	              msgType - ��Ϣ����
	              pBuf    - ����������
	              nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static void SetSdpSession( RvSipCallLegHandle hsCall, s8* pchSessionName, u32 dwStartTime, u32 dwStopTime );
	/*====================================================================
	��	 ��   ��: SendRegCtrlMsg
	��	      ��: �����ŵ�������Ϣ
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsChan  - �ŵ����
	msgType - ��Ϣ����
	pBuf    - ����������
	nBufLen - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus SendRegCtrlMsg( IN EmSipRegCtrlMsgType emMsgType, IN const u8* pbyBuf,IN u16 wBufLen );
	/*====================================================================
	��	 ��   ��: OpenFeccChannel
	��	      ��: ��h224ͨ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: 
	�������˵��: hsCall - �Ի����
                  bSend  - ����/����
	��   ��   ֵ: �ɹ� - 
	ʧ�� - С��0
	====================================================================*/
	static RvStatus OpenFeccChannel(IN RvSipCallLegHandle hsCall, const void* pBuf, u32 dwBufLen);
	/*====================================================================
	��	 ��   ��: CloseFeccChannel
	��	      ��: �ر�h224ͨ��
	�� �� ʵ  ��: 
	����ȫ�ֱ���: 
	�������˵��: hsCall - �Ի����
                  bSend  - ����/����
	��   ��   ֵ: �ɹ� - 
	ʧ�� - С��0
	====================================================================*/
	static RvStatus CloseFeccChannel(IN RvSipCallLegHandle hsCall, BOOL32 bSend  );

	/*====================================================================
	��	 ��   ��: NotifyFeccMsg
	��	      ��: Զң��Ϣ���
	�� �� ʵ  ��: 
	����ȫ�ֱ���: ��
	�������˵��: hsCall  - �ŵ����
	              feccStruct - ��Ϣ����
	              terSrc    - ����������
	              terDst - ��������
	��   ��   ֵ: �ɹ� - act_ok
	ʧ�� - act_err
	====================================================================*/
	static RvStatus RVCALLCONV NotifyFeccMsg(RvSipCallLegHandle hsCall, TFeccStruct tFeccStruct, TTERLABEL tTerSrc, TTERLABEL tTerDst);
	static u8 GetPayload(PayloadType emPt);
	static RvStatus SendConfCtrlMsg(IN RvSipCallLegHandle hsCall, IN RvSipTranscHandle hTransc, IN EmSipConfCtrlMsgType emMsgType, IN const u8* pbyBuf,IN u16 wBufLen);
	static RvStatus SendUMSCtrlMsg(IN RvSipTranscHandle hTransc, IN EmSipUMSCtrlMsgType emMsgType, IN const u8* pbyBuf,IN u16 wBufLen);
	static RvStatus SetAppHanleToUMS(void *pAppHandle);
	static RvStatus SetAppHanleToCall(IN RvSipCallLegHandle hCallLeg, IN RvSipAppCallLegHandle hAppCallLeg);

	static void SetInterworking(BOOL32 bInter); //sipadapter�Ƿ�����interworking�У����򲻷���option��ѯע������
	static s32 OnCreateSipRegister(IN  RvSipAppRegClientHandle hAppRegClient, OUT LPRvSipRegClientHandle lphRegClient);
	static s8* GetResolutionName(emResolution emResType);
	static emResolution GetResolutionByName( s8 *pchName );

	static const s8* GetMediaName(PayloadType emPayLoadType);
	static PayloadType GetPayloadByName(const s8 *pchName);

	//SIP register related non-standard message
	//	Registrar --> UA
	//Parameters:
	//	TSIPRegNSM tSIPRegNSM	: contains with the IP address info and NONSTANDARD message type
	//  const s8* pchNSMRegXML	: detail XML for the message
	//	s32 nBytes				: XML content length
	//	HMDLREG hReg			: Register handle which you get when you succeeded to register to the registrar
	//	s32 nAppID				: upper layer ID, same with interface SipModuleGetRegInfoReq(). *Legacy issue, leaving it only to keep interface compatibility with old TPS interfaces;
	static RvStatus SendRegNSMRsp(IN RvSipTranscHandle hTransc, IN EmSipRegCtrlMsgType emMsgType, IN s32 nAppID, IN const s8* pchXML, IN u32 nBytes);
	//SIP register related non-standard message
	//	UA --> Registrar
	//Parameters:
	//	TSIPRegNSM tSIPRegNSM	: contains with the IP address info and NONSTANDARD message type
	//  const s8* pchXML		: detail XML for the message
	//	s32 nBytes				: XML content length
	//	s32 nAppID				: upper layer ID, same with interface SipModuleGetRegInfoReq(). *Legacy issue, leaving it only to keep interface compatibility with old TPS interfaces;
	static BOOL32	SendRegNSMReq(IN TSIPRegNSM tRegNSM, IN const s8* pchXML, IN u32 nBytes, IN s32 nAppId);

private:
	/*set stack callback*/
    static void SipAppSetCallBack();
	//callback  function
	static SIPEVENT    m_tEventProcess;

	/*Handle to the stack manager. This parameter is returned when calling
    RvSipStackConstruct. You should supply this handle when using the stack
	manager API functions.*/
	static RvSipStackHandle      m_hStackMgr;
	
	/*Handle to the call-leg manager. You can get this handle by calling
	RvSipStackGetCallLegMgrHandle. You should supply this handle when
	using the call-leg manager API functions.*/
	static RvSipCallLegMgrHandle m_hCallLegMgr;
	
	/*Handle to the log-module. You can get this handle by calling
	RvSipStackGetLogHandle. You need this value in order to construct the application
	memory pool.*/
    static RV_LOG_Handle         m_hLog;;
	
	/*Handle to the application memory pool. The application should construct its own
	memory using rpool API. The pool is needed for encoding messages or message
	parts. (See AppPrintMessage() )*/
	static HRPOOL                m_appPool;

	/*Handle to the Authenticator manager. This value is returned when calling
	RvSipStackGetAuthenticationHandle. You should supply this handle when using the
	Authenticator manager API functions.*/
	static RvSipAuthenticatorHandle m_hAuthenticatorMgr;
	static s8 m_achAuthenUserName[LEN_USERNAME + 1];      //��֤�û���
	static s8 m_achAuthenPassword[LEN_PASSWORD + 1];      //��֤����

    //call operation
    static s32 OnMakeCall( RvSipCallLegHandle hsCall, const void* pBuf,u32 dwBufLen );
    static s32 OnAcceptCall( RvSipCallLegHandle hsCall, const void* pBuf,u32 dwBufLen );
	static s32 OnCallDisConnect( RvSipCallLegHandle hsCall, const void* pBuf,u16 wBufLen );

	//call ctrl 
	// static int OnSendConfCtrlMsg( IN RvSipCallLegHandle hsCall, SipChanCtrlMsgType emMsgType );
	
	/*incoming call callback*/
    static void RVCALLCONV AppCallLegCreatedEvHandler(IN  RvSipCallLegHandle     hCallLeg,
		                                              OUT RvSipAppCallLegHandle  *phAppCallLeg);
	
	/*call status change callback*/
	static void RVCALLCONV AppCallLegStateChangedEvHandler( IN  RvSipCallLegHandle hCallLeg,
		                                                    IN  RvSipAppCallLegHandle  hAppCallLeg,
		                                                    IN  RvSipCallLegState      emState,
		                                                    IN  RvSipCallLegStateChangeReason emReason);
	
	/*dual status change callback*/
	static void RVCALLCONV AppCallLegModifyStateChangedEvHandler( IN  RvSipCallLegHandle hCallLeg,
		                                                          IN  RvSipAppCallLegHandle   hAppCallLeg,
		                                                          IN  RvSipCallLegModifyState emState,
		                                                          IN  RvSipCallLegStateChangeReason emReason);
	
	static RvStatus RVCALLCONV AppCallLegMsgToSendEvHandler( IN  RvSipCallLegHandle          hCallLeg,
		                                          IN  RvSipAppCallLegHandle       hAppCallLeg,
 		                                          IN  RvSipMsgHandle              hMsg);
	
	static RvStatus RVCALLCONV AppCallLegMsgReceivedEvHandler( IN  RvSipCallLegHandle       hCallLeg,
		                                                       IN  RvSipAppCallLegHandle    hAppCallLeg,
		                                                       IN  RvSipMsgHandle           hMsg);

	/*call ctrl incoming callback*/
	static void  RVCALLCONV AppCallLegTranscCreatedEvHandler( IN  RvSipCallLegHandle            hCallLeg,
                                                              IN  RvSipAppCallLegHandle         hAppCallLeg,
                                                              IN  RvSipTranscHandle             hTransc,
                                                              OUT RvSipAppTranscHandle          *phAppTransc,
                                                              OUT RvBool                       *pbAppHandleTransc);

	static void RVCALLCONV AppCallLegTranscStateChangedEvHandler(	IN  RvSipCallLegHandle    hCallLeg,
		                                                IN  RvSipAppCallLegHandle hAppCallLeg,
		                                                IN  RvSipTranscHandle     hTransc,
		                                                IN  RvSipAppTranscHandle  hAppTransc,
		                                                IN  RvSipCallLegTranscState  emTranscState,
		                                                IN  RvSipTransactionStateChangeReason emReason);
/*register status change callback */
    static void RVCALLCONV AppRegClientStateChangedEvHandler(
                           IN  RvSipRegClientHandle            hRegClient,
                           IN  RvSipAppRegClientHandle         hAppRegClient,
                           IN  RvSipRegClientState             emState,
                           IN  RvSipRegClientStateChangeReason emReason);

    static RvStatus RVCALLCONV AppRegClientMsgReceivedEvHandler(
                           IN  RvSipRegClientHandle          hRegClient,
                           IN  RvSipAppRegClientHandle       hAppRegClient,
                           IN  RvSipMsgHandle                hMsg);

	static void RVCALLCONV AppAuthenticationMD5Ev(IN  RvSipAuthenticatorHandle  hAuthenticator,
                                              IN  RvSipAppAuthenticatorHandle    hAppAuthenticator,
                                              IN  RPOOL_Ptr                     *pRpoolMD5Input,
                                              IN  RvUint32                     length,
                                              OUT RPOOL_Ptr                     *pRpoolMD5Output);


	static void RVCALLCONV AppAuthenticationGetSharedSecretEv(
                                   IN  RvSipAuthenticatorHandle       hAuthenticator,
                                   IN  RvSipAppAuthenticatorHandle    hAppAuthenticator,
                                   IN  void*                          hObject,
                                   IN  void*                          peObjectType,
                                   IN  RPOOL_Ptr                     *pRpoolRealm,
                                   OUT RPOOL_Ptr                     *pRpoolUserName,
                                   OUT RPOOL_Ptr                     *pRpoolPassword);

	static void RVCALLCONV StackLog(IN void* pcontext , IN RvSipLogFilters filter , IN const RvChar   *pformattedText);


	static void OnGetRegInfo(s32 nAppId, TSIPRegNSM tSipGetRegInfo, u8* pbyXmlInfo, const u32 dwXmlSize);
	
	static void OnRegister( TRegisterInfo *ptRegInfo, s32 nSameReg, void *pHandle, TSipRegName *patSipRegName, s32 nArraySize );

	static void OnUnregister( const s32 nAppId, void *pHandle );

//     static RvStatus RVCALLCONV AppRegClientMsgToSendEvHandler(
//                            IN  RvSipRegClientHandle          hRegClient,
//                            IN  RvSipAppRegClientHandle       hAppRegClient,
//                            IN  RvSipMsgHandle                hMsg);

	static const RvChar* AppGetRegClientStateName(IN  RvSipRegClientState  emState);
    //other
	static void ConstructURI( TSipUrl tUrlAddr, s8 *pachOut, EmSipConnection emSipConnection = emSipTcpConnection, BOOL32 bAddPasswd = FALSE , BOOL32 bTo = FALSE );

    static void AppPrintMessage(IN RvSipMsgHandle hMsg);
	static void RVCALLCONV   AppSipTransactionStateChangedEv(	IN RvSipTranscHandle                 hTransc,
																IN RvSipTranscOwnerHandle            hTranscOwner,
																IN RvSipTransactionState             eState,
																IN RvSipTransactionStateChangeReason eReason);
	static void RVCALLCONV  AppSipTransactionCreatedEv(	IN    RvSipTranscHandle        hTransc,
														IN    void                     *pAppContext,
														OUT   RvSipTranscOwnerHandle   *phAppTransc,
														OUT   RvBool                  *pb_handleTransc);
	static s32 OnSendAck( RvSipCallLegHandle hsCall, const void* pBuf,u32 dwBufLen );
	static RvStatus RVCALLCONV AppRegserverMsgReceivedEvHandler( 
												IN RvSipTranscHandle      hTransc,
												IN RvSipTranscOwnerHandle hTranscOwner,
												IN RvSipMsgHandle         hMsgReceived );
	static RvStatus RVCALLCONV AppRegserverMsgToSendEvHandler(  
												IN RvSipTranscHandle       hTransc,
												IN RvSipTranscOwnerHandle  hTranscOwner,
												IN RvSipMsgHandle          hMsgToSend );
private:
	//begin sdp part
	//���̺�
	static s8	m_achVendorId[SESSION_USERNAME_LEN + 1]; 
	//��Ʒ�ͺ�
	static s8	m_achProductId[SESSION_USERNAME_LEN + 1]; 
	//�汾��
	static s8	m_achVersion[SESSION_INFO_LEN + 1];
	//���ó��̺źͰ汾��Ϣ
    static void SetSdpInfo( s8* pchProductId, s8* pchVersionId );

	static  RvStatus AddDisConnectReason(IN RvSipCallLegHandle hsCall,IN RvSipMsgHandle hMsg, u8 byReason);

	static RvStatus AddScreenNum( IN RvSipCallLegHandle hsCall,IN RvSipMsgHandle hMsg, TSipCallParam &tSipCallParam );

	static RvStatus AddLevelHeader( IN RvSipCallLegHandle hsCall, IN RvSipMsgHandle hMsg, TSipCallParam &tSipCallParam );
	//����User-Agent
	static RvStatus AddUserAgent( IN RvSipMsgHandle hMsg );

	static RvStatus AddUserAgent( IN RvSipCallLegHandle hsCall, IN RvSipMsgHandle hMsg, TSipCallParam &tSipCallParam );
	//����allow header
	static RvStatus AddAllowHeader( IN RvSipMsgHandle hMsg );
	//����supported header
	static RvStatus AddSupportedHeader( IN RvSipMsgHandle hMsg );
	//����require header
	static RvStatus AddRequireHeader( IN RvSipMsgHandle hMsg );
	//�����Զ���sip��ͷ����֧���Զ����ַ�����
	static RvStatus AddCustomHeader( IN RvSipMsgHandle hMsg, IN s8 *pchHeadName, IN s8 *pchHeadValue );
	//add sdp msg to invite transaction
    static  RvStatus AddSdpBodyToMsg( IN RvSipCallLegHandle hCallLeg, CSipCapSet *pcCapSet, TSipCallParam *ptSipParam, BOOL32 bSave, BOOL32 bAddTpAttr );
// 	//add sdp msg to re-invite transaction
// 	static  RvStatus AddSdpBodyToReInvite(IN RvSipCallLegHandle hCallLeg, BOOL32 bOffer, CSipCapSet *pcCapSet );
	//uas retrieve call parameter from incoming invite transaction
	
	static  RvStatus RetrieveDisReason(IN RvSipCallLegHandle hCallLeg, OUT u8& byReason);
	
	static  RvStatus RetrieveParamFromCall( IN RvSipCallLegHandle hCallLeg, OUT TSipCallParam& tCallParam, BOOL32 bCaller = TRUE );
	//uas retrieve sdp msg from incoming invite transaction
    static  RvStatus RetrieveSDPBodyFromMsg( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet, INOUT TSipCallParam *ptSipParam = NULL );
	//uac retrieve sdp msg from outcoming invite 200 ok transaction
//	static  RvStatus RetrieveSDPBodyFromInvite2xxOk( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet );
	//uas retrieve sdp msg from incoming re-invite  transaction
//	static  RvStatus RetrieveSDPBodyFromReInvite( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet );
	//uac retrieve sdp msg from outcoming re-invite 200ok  transaction
//	static  RvStatus RetrieveSDPBodyFromReInvite2xxOk( IN RvSipCallLegHandle hCallLeg, OUT CSipCapSet& tCapSet );
	static BOOL32 BuildSdpBfcpFromCapset( IN RvSdpMsg* pSdpMsg, IN CBfcpMediaStream *pcMediaStream );
	
	static BOOL32 BuildSdpFeccFromCapset( IN RvSdpMsg* pSdpMsg, IN RvSdpConnectionMode rvMode, IN CFeccMediaStream *pcMediaStream );

	static BOOL32 BuildSdpAudVidFromCapset(RvSdpMsg *pSdpMsg, CSipCapSet *pcCapSet, EmCapOrder emCapOrder, s32 nIndex, BOOL32 bTP);

    //sdp offer-answer mode build offer sdp msg
	static BOOL32 BuildSdpFromCapset( IN RvSdpMsg* pSdpMsg, BOOL32 bOffer, IN RvSdpConnectionMode rvMode, 
		                       IN CSipMediaStream *ptMediaStream, u16 wRecvRtcpPort, BOOL32 bTP = TRUE );

	static BOOL32 BuildCapsetFromSdpBfcp( CBfcpMediaStream *pcStream, RvSdpMediaDescr *pMediaDesc );

	static BOOL32 BuildCapsetFromSdpFecc( CFeccMediaStream *pcStream, RvSdpMediaDescr *pMediaDesc );

	static BOOL32 BuildCapsetFromSdpAudVid(EmSipMediaType emMediaType, RvSdpMediaDescr *pMediaDesc, u32 dwConnectionAddr, CSipCapSet &cCapSet, EmCapOrder &emCapOrder);
    //build audio video capset according sdp msg
	static BOOL32 BuildCapsetFromSdp(EmSipMediaType emMediaType, RvSdpConnectionMode emConnectionMode, 
		IN RvSdpMediaDescr *pMediaDesc, IN u32 dwConnectionAddr, OUT CSipCapSet &cCapSet, OUT EmCapOrder &emCapOrder);

	//build H264 capset
	static void BuildH264Capset( RvSdpRtpMap* pSdpRtpMap, TKdvH264VideoCap &tH264Cap, s8 *pchAttr = NULL );
	//build video capset except h264 
	static void BuildCommonVideoCapset( RvSdpRtpMap* pSdpRtpMap, TKdvVideoCap &tHCommonCap,
		                                s8 *pchAttr =NULL );

	
	static u8 GetDynamicPayloadType( PayloadType emPt );
	static BOOL32 GetValueByFieldIds( s8 *pchString, s8 *pchField, s32 &nValue );
	static BOOL32 GetValueByFieldIds( s8 *pchString, s8 *pchField, s8 *pchValue );
	static PayloadType GetFormat( u16 wPayload );
	static s8*  GetFmtp( s32 nPayload, RvSdpMediaDescr *pMediaDesc, s32 nlcCap = 0, s32 nldCap = 0  );
	static s8*  GetFmtpH264(RvSdpMediaDescr *pMediaDesc, s32 nIndex);
	static s32 GetH264Bitrate( RvSdpMediaDescr *pMediaDesc, s8 *pchAttr );
	static RvStatus AppViewSDPMessage(IN RvSdpMsg* pSdpMsg );

	static BOOL32 CheckRequestUri( RvSipCallLegHandle hCall , RvSipAppCallLegHandle haCall );
	static BOOL32 CheckContentAndResponse( RvSipCallLegHandle hCallLeg , RvSipMsgHandle hMsg );
	static BOOL32 CheckExpiresAndResponse( RvSipCallLegHandle hCallLeg , RvSipMsgHandle hMsg );
	static BOOL32 SendRoundTrip( RvSipCallLegHandle hsCall  );
	static s32 GetFormatInRtpmaplistPosition( u16 wPayload, RvSdpMediaDescr *pMediaDesc );

	static s8*  GetContentAttrName( EmSipContentAttr emSipcontentAttr );
	static s8*  GetFloorControlAttrName( EmSipFloorcontrolAttr emFloorcontrolAttr );
	static s8*  GetSetupAttrName( EmSipSetupAttr emSetupAttr );
	static s8*  GetConnectionAttrName( EmSipConnectionAttr emConnectionAttr );
	static EmSipContentAttr  GetContentAttrValue( const s8 *pchContentName );
	static EmSipFloorcontrolAttr  GetFloorControlAttrValue( const s8 *pchFloorcontrolName );
	static EmSipSetupAttr  GetSetupAttrValue( const s8 *pchSetupName );
	static EmSipConnectionAttr  GetConnectionAttrValue( const s8 *pchConnectionName );
	static s8* GetTpCapsignName( EmSipCapSign emTpCapSign );
	static EmSipCapSign GetTpCapsignValue(  const s8 *pchTpCapsign );
	
	//Jacky, H.265 video support
	static void		BuildH265Capset	(RvSdpRtpMap* pSdpRtpMap, TKdvH265VideoCap &tH265Cap, s8 *achAttr);
	static s8*		GetFmtpH265		(s32 nPayload, RvSdpMediaDescr *pMediaDesc, s32 nIndex);
	static s32		GetH265Bitrate	(RvSdpMediaDescr *pMediaDesc, s8 *pchAttr);

	/*
	static BOOL32 DealSipXmlMsgCallback( 
		IN RvSipAppCallLegHandle hAppCallLeg,
		IN RvSipCallLegHandle hCallLeg,
		IN RvSipTranscHandle hTransc,
		IN u8* pBuf, 
		IN u16 wLen );
	static BOOL32 CBSipConfCtrl(
		IN RvSipAppCallLegHandle hAppCallLeg,
		IN RvSipCallLegHandle hCallLeg,
		IN RvSipTranscHandle hTransc,
		IN u16 wEvt, 
		IN u8* pBuf, 
		IN u16 wLen );
	static BOOL32 CBSipConfCtrlNonStd( 
		IN RvSipAppCallLegHandle hAppCallLeg,
		IN RvSipCallLegHandle hCallLeg,
		IN RvSipTranscHandle hTransc,
		IN u16 wEvt, 
		IN u8* pbyBuf, 
		IN u16 wLen );
	static BOOL32 CBSipChanCtrlNonStd( 
		IN RvSipAppCallLegHandle hAppCallLeg,
		IN RvSipCallLegHandle hCallLeg,
		IN RvSipTranscHandle hTransc,
		IN u16 wEvt, 
		IN u8* pbySrcBuf, 
		IN u8* pbyDstBuf );
	*/
private:
   //ͨ������
	static CMediaStreamCtrl *m_pcStreamCtrl;
}; 
  
PROTO_API void Sip_Printf( EmSipLogModule emPAModule, EmSipLogType emPALogType, const s8* pchFormat, ... );
PROTO_API RvStatus RegClientGetCallId (IN  RvSipRegClientHandle   hRegClient,
							IN  RvInt32             nStrCallIdSize,
							OUT RvChar              *pchStrCallId,
							OUT RvInt32             *pnActualSize);
PROTO_API void KdvSetIsH460GW(BOOL32 bIsGw);

typedef struct tagSipRedirectInfo
{
	CallAddrType m_emType;		//���ͣ�������E164�š�IP��ַ��
	s8 m_achBuf[LEN_ALIAS + 1];	//������ΪIP��ַ��bufΪ����255.255.255.255���ַ���
	
	tagSipRedirectInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_emType = emcat_err;
		memset( m_achBuf, 0, sizeof(m_achBuf) );
	}
	
}TSipRedirectInfo, *PTSipRedirectInfo;
#endif

