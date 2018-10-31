
#ifndef _PA_CALL_EVENT_H_
#define _PA_CALL_EVENT_H_
#include "protocaladapter.h"
enum EmPACall
{
	emPACallBegin = OSP_USEREVENT_BASE + 100,
/***********************<< ��������  >>************************
 *[��Ϣ��]			 
 *  + TDialParam
 *
 *[��Ϣ����]
 *    UI        => MtService
 *    MtService => 323/320/sip
 */
	ev_MakeCallCmd,  //TDialParam


/***********************<< �������ڴ���ָʾ  >>************************
 *[��Ϣ��]			 
 *  ��
 *
 *[��Ϣ����]
 *
 *    MtService <= 323/320/sip
 */
	ev_CallProccedingInd,

/***********************<< ��������  >>************************
 *[��Ϣ��]			 
 *  + TDialParam
 *
 *[��Ϣ����]
 *
 *    MtService <= 323/320/sip
 */
	ev_CallIncomingInd,//TDialParam



/***********************<< ���н����ɹ�  >>************************
 *[��Ϣ��]			 
 *  ����Ϣ��
 *
 *[��Ϣ����]
 *
 *    MtService <= 323/320/sip
 */
	ev_CallConnectedInd,



/***********************<< ���ܺ���ָʾ  >>************************
 *[��Ϣ��]			 
 *  + BOOL  TRUE=���ܺ���  FALSE=�ܾ�����  
 *
 *[��Ϣ����]
 *
 *    MtService => 323/320/sip
 */
	ev_CallAcceptInd,//BOOL



/***********************<< ���йҶ�ָʾ  >>************************
 *[��Ϣ��]			 
 *  +u8  byReason	�Ҷ�ԭ��
 *
 *[��Ϣ����]
 *
 *    MtService <=> 323/320/sip
 */
	ev_CallDisconnectedInd,//EmCallDisconnectReason

 
/***********************<< �ҶϺ���  >>************************
 *[��Ϣ��]			 
 *  +u8  byReason	�Ҷ�ԭ��
 *
 *[��Ϣ����]
 *
 *    MtService <=> 323/320/sip
 */
	ev_CallHangupCmd,//u8

/***********************<< ������֪ͨ  >>************************
 *[��Ϣ��]			 
 *  
 *
 *[��Ϣ����]
 *
 *    MtService <=> sip
 */
   ev_CallCapbility,
/***********************<< ��ʱָʾ  >>************************
 *[��Ϣ��]			 
 *  +u32
 *
 *[��Ϣ����]
 *
 *    MtService <=> 323/320/sip
 */
	ev_CallKeepLiveTimeOutInd,//u32









 /***********************<< ��ʼ˫������  >>************************
 *[��Ϣ��]			 
 *  +EmMtVideoPort  
 *  +BOOL             TRUE=��ʼ FALSE =ֹͣ
 *[��Ϣ����]
 *
 *    MtService <=> 323/320/sip
 */
	ev_DualVideoCmd,//EmMtVideoPort BOOL





/***********************<< ��ʼ˫������  >>************************
 *[��Ϣ��]			 
 *  +EmMtVideoPort  
 *  +BOOL             TRUE=��ʼ FALSE =ֹͣ
 *[��Ϣ����]
 *
 *    MtService <=> 323/320/sip
 */
	ev_DualVideoInd,//EmMtVideoPort  BOOL

/***********************<< ͨ��״̬�ı� >>************************	
 *[��Ϣ��]		 
 * EmChanType 
 * BOOL       
 *[��Ϣ����]
 *    UI => MtService
 */
	ev_ChannelStatusChanged,//EmChanType BOOL

/***********************<< �����Ƿ����ָʾ >>************************	
 *[��Ϣ��]		 
 *  +BOOL  //�Ƿ����
 *[��Ϣ����]
 *    MtService => UI
 */
	ev_CallEncryptInd ,//BOOL 

/***********************<< ����˫��ָʾ  >>************************
 *[��Ϣ��]
 *  +BOOL             TRUE=��ʼ FALSE =ֹͣ
 *[��Ϣ����]
 *
 *    MtService <=> 323/320/sip
 */
	ev_RecvDualVideoInd,//BOOL
	ev_StopDualVideoCmd,
   
/***********************<< �鲥ģʽ��ַָʾ  >>************************
 *[��Ϣ��]
 * +TIPTransAddr     ��Ƶ���յ�ַ
 * +TIPTransAddr     ��һ·��Ƶ���յ�ַ
 * +TIPTransAddr     �ڶ�·��Ƶ���յ�ַ
 *[��Ϣ����]
 *
 *    MtService <= 323/320/sip
 */
	ev_MulticastModeAddrInd,//TIPTransAddr*3   )


	/***********************<< ���齨����ʱ��Ϣ   >>************************
	*[��Ϣ��]			 
	*  ��
	*
	*[��Ϣ����]
	*    MtH323Service �ڲ�
	*  ����Ϣ�ں��н��������ö�ʱ���ڳ�ʱ��ʱ����δ�ɹ���ͨ��
	*/
	ev_InnerConfEstablishTimeOut,
	
	/***********************<< ���齨����ʱ��Ϣ   >>************************
	*[��Ϣ��]			 
	*  ��
	*
	*[��Ϣ����]
	*    MtH323Service �ڲ�
	*  ����Ϣ��ʾ�Ѿ�����Ƶ�����ŵ����Խ���Ի�ģʽ
	*/
	ev_InnerConfStartInd,
	
	/***************<< ����RoundTripDelay��Ϣָʾ   >>***********************
	*[��Ϣ��]			 
	*  ��
	*
	*[��Ϣ����]
	*    MtH323Service �ڲ�
	*  ����Ϣ��ʾ�Ѿ�����Ƶ�����ŵ����Խ���Ի�ģʽ
	*/
//	ev_InnerSendRoundTripDelayInd,
	
 
	ev_SipRegisterReq,
	ev_SipUnRegisterReq,
	ev_SipRegisterResultInd,
	ev_SipGetRegReq,
	
	ev_SipFastUpdate,
	ev_SipFlowCtrl,
	ev_ConfCtrl,
	ev_SendDual,
	ev_AnswerDual,
	ev_StopDual,
};
typedef s32 (PA_CALLBACK* CBSipCallConnected)( const s32 nAppId, const s32 nCallId, CPACapSet *ptPACapSet, TPADialParam *ptPADial );
typedef s32 (PA_CALLBACK* CBSipChannelConnected)( const s32 nAppId, const s32 nCallId, CPACapMap *pCapMap, const s32 nArraySize );
typedef s32 (PA_CALLBACK* CBSipChannelDisConnect)( const s32 nAppId, const s32 nCallId, const s32 nChannelId, EmPAChannelReason emChannelReason );
typedef s32 (PA_CALLBACK* CBSipCallIncoming)( const s32 nCallId, TPADialParam *ptPADialParam );
typedef s32 (PA_CALLBACK* CBSipCallDisconnect)( const s32 nAppId, const s32 nCallId, const EmPACallDisconnectReason EmReason );
typedef s32 (PA_CALLBACK* CBSipRegister)( const s32 nAppId, void *pRegHandle, EmRegResult emPARegResult );
typedef s32 (PA_CALLBACK* CBSipUnRegister)( const s32 nAppId, EmRegResult emPARegResult, const u8 *pBuf, const s32 nLen);
typedef s32 (PA_CALLBACK* CBSipChanCtrl)( const s32 nAppId, const s32 nCallId, const s32 nChannelId, const s32 nMsgType, const u8 *pBuf, const s32 nSize );
typedef s32 (PA_CALLBACK* CBSipConfCtrl)( const s32 nAppId, const s32 nCallId, const s32 nMsgType, const u8 *pBuf, const s32 nSize );
typedef s32 (PA_CALLBACK* CBSipDualIncoming)( const s32 nAppId, const s32 nCallId, TPACascadeInfo *ptPACas );
typedef s32 (PA_CALLBACK* CBSipDualConnected)( const s32 nAppId, const s32 nCallId, CPACapMap *pDualCapMap, const s32 nArraySize, TPACascadeInfo *ptPACas );

typedef s32 (PA_CALLBACK* CBSipDualDisconnect)( const s32 nAppId, const s32 nCallId, s32 *pChannelId, const s32 nChannelSize, const EmPAChannelReason EmReason );

typedef s32 (PA_CALLBACK* CBSipInitStackRes)(const EmPAInitSipStackRes emPAStackRes); //�ص���ʼ��Э��ջ���
typedef s32 (PA_CALLBACK* CBSipGetRegInfoAck)(s32 nAppid, const u8 *pBuf, const s32 nLen);

typedef struct tagSipServiceEvent
{
	CBSipCallConnected cbSipCallConnected;
	CBSipCallIncoming  cbSipCallIncoming;
	CBSipCallDisconnect cbSipCallDisconnect;
	CBSipRegister		cbSipRegister;
	CBSipUnRegister     cbSipUnRegister;
	CBSipChanCtrl          cbSipChanCtrl;
	CBSipConfCtrl		cbSipConfCtrl;
	CBSipDualIncoming   cbSipDualIncoming;
	CBSipDualConnected  cbSipDualConnected;
	CBSipDualDisconnect cbSipDualDisconnect;
	CBSipChannelConnected cbSipChannelConnected;
	CBSipChannelDisConnect cbSipChannelDisConnect;
	CBSipInitStackRes   cbSipInitStackRes;
	CBGetRegInfoAck     cbGetRegInfoAck;
	tagSipServiceEvent()
	{
		memset(this, 0, sizeof(tagSipServiceEvent) );
	}
}TSipServiceEvent;
extern TSipServiceEvent g_tSipServiceEvent;
inline void SetSipServiceEvent( const TSipServiceEvent & tSipServiceEvent )
{
	g_tSipServiceEvent.cbSipCallConnected = tSipServiceEvent.cbSipCallConnected;
	g_tSipServiceEvent.cbSipCallIncoming = tSipServiceEvent.cbSipCallIncoming;
	g_tSipServiceEvent.cbSipCallDisconnect = tSipServiceEvent.cbSipCallDisconnect;
	g_tSipServiceEvent.cbSipRegister = tSipServiceEvent.cbSipRegister;
	g_tSipServiceEvent.cbSipUnRegister = tSipServiceEvent.cbSipUnRegister;
	g_tSipServiceEvent.cbSipChanCtrl = tSipServiceEvent.cbSipChanCtrl;
	g_tSipServiceEvent.cbSipDualIncoming = tSipServiceEvent.cbSipDualIncoming;
	g_tSipServiceEvent.cbSipDualConnected = tSipServiceEvent.cbSipDualConnected;
	g_tSipServiceEvent.cbSipDualDisconnect = tSipServiceEvent.cbSipDualDisconnect;
	g_tSipServiceEvent.cbSipChannelConnected = tSipServiceEvent.cbSipChannelConnected;
	g_tSipServiceEvent.cbSipChannelDisConnect = tSipServiceEvent.cbSipChannelDisConnect;
	g_tSipServiceEvent.cbSipConfCtrl = tSipServiceEvent.cbSipConfCtrl;
	g_tSipServiceEvent.cbSipInitStackRes = tSipServiceEvent.cbSipInitStackRes;
	g_tSipServiceEvent.cbGetRegInfoAck = tSipServiceEvent.cbGetRegInfoAck;
}
inline TSipServiceEvent *GetSipServiceEvent()
{
	return &g_tSipServiceEvent;
}
#endif

