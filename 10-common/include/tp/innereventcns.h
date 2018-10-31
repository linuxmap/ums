#ifndef _h_innereventcns_h__
#define _h_innereventcns_h__


#include "cnseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsInnerToCns
{
#endif

_ev_segment( innercns )

 /***********************<<cncall����cns���ڲ���ʱ��>>************************	
 *[����Ϣ��]			 
 *  NULL
 *[��Ϣ����]
 *    cncall => cncall
 */
_event(  ev_tppregcall_timer )
_ev_end

/***********************<<cncall����cns��ʱ����>>************************	
 *[����Ϣ��]			 
 *  NULL
 *[��Ϣ����]
 *    cncall => cncall
 */
_event(  ev_tppregcall_connect_time_out_timer )
_ev_end

/***********************<<cns��ģ����������>>************************	
 *[����Ϣ��]			 
 *  NULL
 *[��Ϣ����]
 *    cns => cns
 */
_event(  ev_TpModuleStartCmd )
_ev_end

/***********************<<cncall������cnsubroutinemgr,Ȼ��cnsubroutinemgr֪ͨcnservice>>************************	
 *[����Ϣ��]			 
 *  NULL
 *[��Ϣ����]
 *    cns => cns
 */
_event(  ev_TpCnCallConnSuccessCmd )
_ev_end

/***********************<<ccncall�Ͽ�cnsubroutinemgr,Ȼ��cnsubroutinemgr֪ͨcnservice>>************************	
 *[����Ϣ��]			 
 *  NULL
 *[��Ϣ����]
 *    cns => cns
 */
_event(  ev_TpCnCallConnFailCmd )
_ev_end

/***********************<<cncall�Ͽ�cnsubroutinemgr,Ȼ��cncall����������cnsubroutinemgr>>************************	
 *[����Ϣ��]			 
 *  NULL
 *[��Ϣ����]
 *    cns => cns
 */
_event(  ev_TpCnCallRepeatConnCmd )
_ev_end

/***********************<<�᳡����>>************************	
 *[����Ϣ��]			 
 *  TMtTPEpParam �᳡����
 *[��Ϣ����]
 *   terinterface->cnservice 
 */
_event(  ev_TpCnOnline_Nty )
_ev_end
 
/***********************<<˫���᳡����>>************************	
 *[����Ϣ��]			 
 *  TMtTPEpParam �᳡����
 *[��Ϣ����]
 *   terinterface->cnservice 
 */
_event(  ev_TpCnDualOnline_Nty )
_ev_end

/***********************<<�᳡����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *   terinterface<->cnservice 
 */
_event(  ev_TpCnOffline_Nty )
_ev_end

/***********************<<˫���᳡����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *   terinterface<->cnservice 
 */
_event(  ev_TpCnDualOffline_Nty )
_ev_end

/***********************<<�᳡���߹Ҷ�>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *   cns-> cns
 */
_event(  ev_TppOffLineHangUp_Cmd )
 _ev_end

 /***********************<<������Ƶ�������>>************************	
 *[����Ϣ��]			 
 * TMtADecParam ��Ƶ�������
 *[��Ϣ����]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetADecParamCmd )
_body( TMtADecParam, 1)
_ev_end

 /***********************<<������Ƶ�������>>************************	
 *[����Ϣ��]			 
 * TMtAEncParam ��Ƶ�������
 *[��Ϣ����]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetAEncParamCmd )
_body( TMtAEncParam, 1)
_ev_end

 /***********************<<��������Ƶ�������>>************************	
 *[����Ϣ��]			 
 * TCnVideoParam ��Ƶ����
 *[��Ϣ����]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetVDecParamCmd )
_body( TMtVDecParam, 1)
_ev_end

 /***********************<<������Ƶ�������>>************************	
 *[����Ϣ��]			 
 * TCnVideoParam ��Ƶ����
 *[��Ϣ����]
 *   mediatransservice-> terinterface
 */
_event(  ev_Cn_SetVEncParamCmd )
_body( TCnVideoParam, 1)
_ev_end

 /***********************<<��ʾ���߻᳡>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_Cn_ShowActiveConf_Dump )
_ev_end

 /***********************<<cnc��¼>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_CnCncLogin_Ind )
_body( TLoginUserMsg, MAX_CNC_USER )
_ev_end

 /***********************<<cnc�˳�>>************************	
 *[����Ϣ��]			 
 * u8 Pad ID
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_CnCncLogout_Ind )
_body( u8, 1)
_ev_end

 /***********************<<����ؼ�֡��ʱ��>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_CnRequestKeyFrame_Timer )
_ev_end

 /***********************<<����˫���ؼ�֡��ʱ��>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_CnRequestDualKeyFrame_Timer )
_ev_end

 /***********************<<cns��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_TpModuleRebootCmd )
_ev_end

 /***********************<<�޸�ϵͳʱ��֪ͨ>>************************	
 *[����Ϣ��]			 
 * time_t
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_CnSysTimeChangeNotify )
_body( time_t, 1)
_ev_end

 /***********************<<���ñ�������>>************************	
 *[����Ϣ��]			 
 * BOOL ���������Ƿ���Ч
 *[��Ϣ����]
 *  cnc->cns
 */
_event( ev_CnSetEth1_Cmd )
_body( BOOL, 1)
_ev_end


 //Added by meifang
 ////////////////////CnAgentģ����Ϣ//////////////////////

  /***********************<< Guard��ȡcnsϵͳ��Ϣ >>********************	
 *[��Ϣ��]			 
 *   ��
 *[��Ϣ����]
 *   cnGuard => cnGuard
 */_event(  ev_CnScanSystem  )
   _ev_end

 /***********************<< NotifyObzerver���� >>********************	
 *[��Ϣ��]			 
 *   ��
 *[��Ϣ����]
 *    UE => UE
 */_event(  ev_CnNotifyObzerverCompletedInd  )
   _ev_end

 /***********************<< ��ʼ���澯APP  >>************************	
 *[��Ϣ��]			 
 *    TSNMPCfg
 *
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtInitInd  )
 _body( TTPNMServerCfg, 2 )
 _ev_end

 /***********************<< ϵͳ������֪ͨ >>************************	
 *[��Ϣ��]			 
 *
 *[��Ϣ����]
 *    CNS => AGENT
 */_event(  ev_CnAgtSysRestarInd  )
 _body( u16, 1 )
 _ev_end
 
 //Added by meifang
 /***********************<< Cpu״̬�ı� >>************************	
 *[��Ϣ��]			 
 *    u32 CPUʹ����
 *
 *[��Ϣ����]
 *    GUARD => AGENT
 */
 _event(  ev_CnAgtCpuInd  )
 _body( u32, 1 )
 _ev_end

 /***********************<< �ڴ�״̬�ı� >>************************	
 *[��Ϣ��]			 
 *    TAlarmCode
 *
 *[��Ϣ����]
 *    CNS => AGENT
 */_event(  ev_CnAgtMemoryInd  )
 _body( u32, 1 )
 _ev_end

 /***********************<<��ȡ cns �᳡��Ϣ >>************************	
 *[��Ϣ��]			 
 *    TTPCnsInfo 
 *
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtGetCnsInfoInd  )
 _body( TTPCnsInfo, 1 )
 _ev_end
 
 /***********************<<��ȡ cns �᳡״̬ >>************************	
 *[��Ϣ��]			 
 *  TTPCurCnsConfStatus 
 *
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtGetCnsStateInd  )
 _body( TTPCurCnsConfStatus, 1 )
 _ev_end
 
 /***********************<<��ȡ cns ע��״̬ >>************************	
 *[��Ϣ��]			 
 *  TTPGkRegistrarCfg 
 *
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtGetCnsRegStateInd  )
 _body( TTPCnsRegStatus, 1 )
 _ev_end
 

  /***********************<<���ܷ�����������Ϣ >>************************	
 *[����Ϣ��]			 
 *  TTPNMServerCfg
 *  u16 ���ܷ���������
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnNMServerCfgInd )
 _body( TTPNMServerCfg, 1 )
 _ev_end

 ////////////////////��������cns��Ϣ//////////////////////
 
 /***********************<< ϵͳ����״̬    >>********************	
  * [����Ϣ��]
 * BOOL �ϴ��ɹ� TRUE , �ϴ�ʧ��FALSE
 * [��Ϣ����] 
 * cns -> cns
 */_event(ev_CnSysfileUploadStatus)
 _body(BOOL , 1)
 _ev_end

 /***********************<< ����ǽ����    >>********************	
  * [����Ϣ��]
 * TEmbedFwNatProxy 
 * [��Ϣ����] 
 *
 */_event(ev_CfgFireWallInd)
 _body(TEmbedFwNatProxy , 1)
 _ev_end
 
 

 //End to add

/***********************<< cnds������cnsubroutinemgr,Ȼ��cnsubroutinemgr֪ͨcnservice   >>********************	
 * [����Ϣ��]
 * NULL
 * [��Ϣ����] 
 * cns -> cns
 */
 _event(  ev_TpCnDsConnSuccessCmd )
 _ev_end	

/***********************<< cnsע���������������ڲ���ʱ�� >>********************	
 * [����Ϣ��]
 * NULL
 * [��Ϣ����] 
 * cns -> cns
 */
 _event( ev_TpCnRegUpdateSer_Timer )
 _ev_end

 /***********************<< cns�������ڲ���ʱ�� >>********************	
 * [����Ϣ��]
 * NULL
 * [��Ϣ����] 
 * cns -> cns
 */
 _event( ev_TpCnsUpdate_Timer )
 _ev_end

 /***********************<< cns�᳡����״̬֪ͨ >>********************	
 * [����Ϣ��]
 * EmCALLSTATE �᳡����״̬
 * [��Ϣ����] 
 * cns -> cns
 */
 _event( ev_TpCnCallState_Nty )
 _body( EmCALLSTATE, 1 )
 _ev_end

  /***********************<< Guard��ȡcnsϵͳ״̬ >>********************	
 *[��Ϣ��]			 
 *   ��
 *[��Ϣ����]
 *   cnGuard => cnGuard
 */
 _event( ev_SystemStatistic )
 _ev_end

 /***********************<< ͳ��֪ͨ >>************************	
 *[��Ϣ��]			 
 *
 *[��Ϣ����]
 *    Guard => AGENT
 */_event(  ev_AgtStatisticsInd  )
 _ev_end


  /***********************<< ����Сͼ�� >>************************	
 *[��Ϣ��]			 
 *
 *[��Ϣ����]
 *    usr => cnservice
 */_event(  ev_CreateDsDebug_Cmd  )
 _body( u32, 1 )
 _body( u32, 1 )
 _body( u16, 1 )
 _body( u16, 1 )
 _body( u16, 1 )
 _body( BOOL, 1 )
 _ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(innercns)
};
#endif



#endif // _h_innereventregsrv_h__
