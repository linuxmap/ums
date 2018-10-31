#ifndef _h_eventoutcnssipconf_h__
#define _h_eventoutcnssipconf_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSIPCONFEVENT
{
#endif 

  _ev_segment( outercnssipconf  )

_event(  ev_CnBeChairMan_Ind )
_body( BOOL, 1 )
_ev_end
/***********************<< ���÷����� >>********************** 
*[��Ϣ��]
+u8		�����
*[��Ϣ����]
*  cns	  <- cnc
*/
_event(  ev_CnSetInnerSpeaker_Cmd )
_body( u8, 1 )
_ev_end

/***********************<< ���÷�������Ӧ >>********************** 
*[��Ϣ��]
+u8		��ǰ���������
*[��Ϣ����]
*  cns	  -> cnc
*/
_event(  ev_CnSetInnerSpeaker_Ind )
_body( u8, 1 )
_ev_end

/***********************<< ���÷��Ի᳡��Ӧ >>********************** 
*[��Ϣ��]
+u8		�����
+s8		�������û᳡��
*[��Ϣ����]
*  cns	  -> cnc
*/
_event(  ev_CnYouAreSeeing_Ind )
_body( TTPYouAreSeeing, 1 )
_ev_end

/***********************<< ����״ָ̬ʾ >>********************** 
*[��Ϣ��]
+EmCALLSTATE		����״̬
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_CnConfState_Nty )
_body( TTPCnsConfStatus, 1 )
_ev_end


/***********************<<  ������ѯ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnStartPoll_Cmd )
_ev_end

/***********************<<  ������ѯ��Ӧ >>********************	
 *[��Ϣ��]
 +EmPollReason 
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_CnStartPoll_Ind )
_body ( EmTPPollResult  , 1  )
_ev_end

/***********************<<  �ر���ѯ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnStopPoll_Cmd )
_ev_end

/***********************<<  �ر���ѯ��Ӧ >>********************	
 *[��Ϣ��]
 +EmPollReason 
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_CnStopPoll_Ind )
_body ( EmTPPollResult  , 1  )
_ev_end

/***********************<<  ��ѯ״̬֪ͨ >>********************	
 *[��Ϣ��]
 +BOOL  �� or ��
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnPollStatus_Nty )
_body ( TTpPollStat  , 1  )
_ev_end


/***********************<<  ����ѡ�� >>********************	
 *[��Ϣ��]
 +u8 �����
 +u16 Ҫѡ���᳡��epid
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnSingleView_Cmd )
_body ( u8  , 1  )
_body ( u16  , 1  )
_ev_end

/***********************<<  ����ѡ����Ӧ >>********************	
 *[��Ϣ��]
 +u8 �����
 +EmTPViewResult �ɹ����
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnSingleView_Ind )
_body ( u8  , 1  )
_body ( EmTPViewResult, 1 )
_ev_end

/***********************<<  �ر�ѡ�� >>********************	
 *[��Ϣ��]
 +u8 �����
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnCancelSingleView_Cmd )
_body ( u8  , 1  )
_ev_end

/***********************<<  �ر�ѡ����Ӧ >>********************	
 *[��Ϣ��]
 +u8 �����
 +EmTPViewResult ���
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnCancelSingleView_Ind )
_body ( u8  , 1  )
_body ( EmTPViewResult, 1 )
_ev_end

//���ڽ���ģ�鵥��һ�����̣�������ֲ���ⲿ��Ϣ
_event(  ev_CnChanViewLocalCmd )
_ev_end

_event(  ev_CnChanCancelViewLocalCmd )
_ev_end

/***********************<< ����˫����Ӧ  >>********************	
 *[��Ϣ��]
 +BOOL
 +EmTPDualReason
 *[��Ϣ����]
 *  cncall  -> cns
*/
_event(  ev_CnRequestDualStreamInd )
_body( BOOL, 1 )
_body( EmTPDualReason, 1 )
_ev_end

/***********************<< ֪ͨ˫���ն�����  >>********************	
 *[��Ϣ��]
 +s8 ˫���ն���
 *[��Ϣ����]
 *  cncall  -> cns
*/
_event(  ev_Cn_DualNameNty )
_body( s8, TP_MAX_NAME_LEN +1 )
_ev_end

/***********************<< ֪ͨ��ѯ�᳡����  >>********************	
 *[��Ϣ��]
 +TTPPollDstName
 *[��Ϣ����]
 *  cncall  -> cns
*/
_event(  ev_Cn_PollNameNty )
_body( TTPPollDstName, 1 )
_ev_end

/***********************<<  ������״̬֪ͨ >>********************	
 *[��Ϣ��]
 u8 �����
 EmTPPosStatus ״̬
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_CnActivePos_Nty )
_body( u8 , 1 )
_body( EmTPPosStatus , 1 )
_body( EMPosPic , 1 )
_ev_end




/***********************<< ����ep�б� >>********************	
 *[��Ϣ��]
TConfCnsInfo
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_CnConfEpList_Nty )
_body( TConfCnsInfo , 1 )
_ev_end

/***********************<< ������ѡ������ >>********************	
 *[��Ϣ��]
u8
 *[��Ϣ����]
 *  cnc	 -> cns
*/
_event(  ev_CnViewLocal_Cmd )
_body( u8 , 1 )
_ev_end

/***********************<< ������ѡ������ظ� >>********************	
 *[��Ϣ��]
u8
 *[��Ϣ����]
 *  cns	 -> cnc
*/
_event(  ev_CnViewLocal_Ind )
_body( u8 , 1 )
_body( EmTPViewLocalResult, 1 )
_ev_end


/***********************<< ȡ������ѡ������ >>********************	
 *[��Ϣ��]
u8
 *[��Ϣ����]
 *  cnc	 -> cns
*/
_event(  ev_CnCancelViewLocal_Cmd )
_body( u8 , 1 )
_ev_end

/***********************<< ȡ������ѡ������ظ� >>********************	
 *[��Ϣ��]
u8
 *[��Ϣ����]
 *  cns	 -> cnc
*/
_event(  ev_CnCancelViewLocal_Ind )
_body( u8 , 1 )
_body( EmTPViewLocalResult, 1 )
_ev_end


/***********************<<  ��Ļ״̬������ͳһ��ʾ >>********************	
 *[��Ϣ��]
 u8 �����
 EMPosPic ״̬
 s8 ��Ļ����
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_CnPosAllStatus_Nty )
_body( u8 , 1 )
_body( EMPosPic , 1 )
_body( s8, TP_MAX_NAME_LEN+1 )
_ev_end


/***********************<<  ���������ۿ��� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppConfAMixUpdate_Cmd )
_body( TConfAuxMixInfo , 1 )
_ev_end


/***********************<<  ���������ۿ�����Ӧ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfAMixUpdate_Ind )
_body( TConfAuxMixInfo , 1 )
_ev_end

/***********************<<  ���������ۿ���֪ͨ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfAMixUpdate_Nty )
_body( TConfAuxMixInfo , 1 )
_ev_end


/***********************<<  �������л������� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppConfApplySpeaker_Cmd )
_body( TConfEpID , 1 )
_ev_end


/***********************<<  �������л������� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfApplySpeaker_Ind )
_body( TConfEpID , 1 )
_body( EmTpApplySpeakerRet, 1 )
_ev_end


/***********************<<  �������л������� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfApplySpeaker_Nty )
_body( TConfEpID , 1 )
_ev_end

/***********************<<  ���������Զ������ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppConfMute_Cmd )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<<  ���������Զ������ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfMute_Ind )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end


/***********************<<  ���������Զ������ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfMute_Nty )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<<  ���������Զ�˾��� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppConfQuiet_Cmd )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���_
_ev_end

/***********************<<  ���������Զ�˾��� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfQuiet_Ind )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���_
_ev_end


/***********************<<  ���������Զ�˾��� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfQuiet_Nty )
_body( TConfEpID , 1 )
_body( BOOL,  1)//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���_
_ev_end

/***********************<<  ��������ͨ�����������б��в����ڵĻ᳡ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByAlias_Cmd )
_body( TTpCallAddr , 1 )
_ev_end

/***********************<<  ��������ͨ�����������б��в����ڵĻ᳡��Ӧ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByAlias_Ind )
_body( TTpCallAddr ,1 )
_body( EmCnsCallReason    , 1    )
_ev_end

/***********************<<  ��������ͨ��EPID�����б��д��ڵĲ����߻᳡ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByEpId_Cmd )
_body( u16 ,1 )
_ev_end

/***********************<<  ��������ͨ��EPID�����б��д��ڵĲ����߻᳡��Ӧ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppInviteCnsByEpId_Ind )
_body( u16 ,1 )
_body( EmCnsCallReason    , 1    )
_ev_end

/***********************<<  ���Ҷ�ָ���᳡ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppHangupCns_Cmd )
_body( u16 ,1 )
_ev_end

/***********************<<  ���Ҷ�ָ���᳡��Ӧ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppHangupCns_Ind )
_body( u16 ,1 )
_body( EmCnsCallReason, 1 )
_ev_end

/***********************<<  �Ҷϻ��� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppHangupConf_Cmd )
_ev_end

/***********************<<  ��ѯ�б�֪ͨ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppUpdateConfTurnlist_Nty )
_body( TConfTurnInfo  , 1  )
_ev_end

/***********************<<  ֪ͨ��ϯ������Ϣ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppChairConfInfo_Nty )
_body( TChairConfInfo  , 1  )
_ev_end


/***********************<<  �᳡��������״̬֪ͨ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppAudMixStatus_Nty )
_body( TAudMixStat  , 1  )
_ev_end

/***********************<<  ��������֪ͨ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppDiscussScreenStat_Notify )
_body( TTPDisScreenStat  , 1  )
_ev_end

/***********************<<  ���ۻ᳡��������ӡ�ɾ���� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppAudMixDisListOpr_Cmd )
_body( TDiscussListOpr  , 1  )
_ev_end

/***********************<<  ���ۻ᳡��������ӡ�ɾ���� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppAudMixDisListOpr_Ind )
_body( TDiscussListOpr  , 1  )
_ev_end

/***********************<< ������� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cnc	  <- cns
*/
_event(  ev_TppModuleTerminalJoinConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< �뿪���� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cnc	  <- cns
*/
_event(  ev_TppModuleterminalLeftConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<<  >>********************** 
*[��Ϣ��]
TTPUmsReasonInd
*[��Ϣ����]
*  cnc	  <- cns
*/
_event( ev_TppUmsCommonReasonToUI_Ind )
_body( TTPUmsReasonInd, 1 )
_ev_end

/***********************<< �����ػ��л� >>********************** 
*[��Ϣ��]
*u8 ����
*BOOL ���ػ��л��Ƿ���
*[��Ϣ����]
*  cnc	-> cns
*/
_event( ev_CnViewLocalPIP_Cmd )
_body( u8, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< �����ػ��л� >>********************** 
*[��Ϣ��]
*u8 ����
*EmTPViewLocalResult
*[��Ϣ����]
*  cnc	<- cns
*/
_event( ev_CnViewLocalPIP_Ind )
_body( u8, 1 )
_body( EmTPViewLocalResult, 1 )
_ev_end

/***********************<< �����ػ��л� >>********************** 
*[��Ϣ��]
*u8 ����
*BOOL ���ػ��л��Ƿ���
*[��Ϣ����]
*  cnc	<- cns
*/
_event( ev_CnViewLocalPIP_Nty )
_body( u8, 1 )
_body( BOOL, 1 )
_ev_end


/***********************<<  ����ѡ������ǽ >>********************	
 *[��Ϣ��]
 +u8 �����
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnSelTVSView_Cmd )
_body ( u8  , 1  )
_ev_end

/***********************<<  ����ѡ������ǽ��Ӧ >>********************	
 *[��Ϣ��]
 +u8 �����
 +BOOL �ɹ����
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_CnSelTVSView_Ind )
_body ( u8  , 1  )
_body ( BOOL, 1 )
_ev_end

/***********************<<  �ر�ѡ������ǽ >>********************	
 *[��Ϣ��]
 +u8 �����
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_CnCancelSelTVSView_Cmd )
_body ( u8  , 1  )
_ev_end

/***********************<<  �ر�ѡ������ǽ��Ӧ >>********************	
 *[��Ϣ��]
 +u8 �����
 +BOOL ���
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_CnCancelSelTVSView_Ind )
_body ( u8  , 1  )
_body ( BOOL, 1 )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipconf )
};
#endif
#endif //TPP_EVENT_H
