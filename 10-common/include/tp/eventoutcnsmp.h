#ifndef _h_eventoutcnsmp_h__
#define _h_eventoutcnsmp_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSMPPEVENT
{
#endif 

  _ev_segment( outercnsmp  )

/***********************<< �ն�ע��cns���� >>********************	
 *[��Ϣ��]
 * TMtTPEpParam
 *[��Ϣ����]
 *  cns	  <- mt
*/
  _event(  ev_tppregister_req )
  _body( TMtTPEpParam, 1)
  _ev_end

/***********************<< �ն�ע��cns�Ļ�Ӧ >>********************	
 *[��Ϣ��]
 * EmCnMtRegResult
 *[��Ϣ����]
 *  cns	  -> mt
*/
  _event(  ev_tppregister_rsp )
  _body( EmCnMtRegResult, 1 )
  _ev_end

/***********************<< ������Ƶ������� >>********************	
 *[��Ϣ��]
 * TMtADecParam
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppSetADecParamCmd )
  _body( TMtADecParam, 1)
  _ev_end

/***********************<< ������Ƶ������� >>********************	
 *[��Ϣ��]
 * TMtAEncParam
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppSetAEncParamCmd )
  _body( TMtAEncParam, 1)
  _ev_end

/***********************<< ������Ƶ������� >>********************	
 *[��Ϣ��]
 * TMtVDecParam
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppSetVDecParamCmd )
  _body( TMtVDecParam, 1)
  _ev_end     

  /***********************<< ������Ƶ������� >>********************	
 *[��Ϣ��]
 * TMtVEncParam
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppSetVEncParamCmd )
  _body( TMtVEncParam, 1)
  _ev_end

 /***********************<< ������������� >>********************	
 *[��Ϣ��]
 * TTpCodecComponent
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppCodecStartCmd )
  _body( TTpCodecComponent, 1 )
  _ev_end

 /***********************<< ֹͣ����������� >>********************	
 *[��Ϣ��]
 * TTpCodecComponent
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppCodecStopCmd )
  _body( TTpCodecComponent, 1 )
  _ev_end

 /***********************<< ���ն�����ؼ�֡������ >>********************	
 *[��Ϣ��]
 * TTpCodecComponent
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppSndKeyFrame_Req )
  _body( TTpCodecComponent, 1)
  _ev_end
  
 /***********************<< ��������������ʵ����� >>********************	
 *[��Ϣ��]
 * TTpCodecComponent
 *u16 ����
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppFlowCtrl_Cmd )
  _body( TTpCodecComponent, 1)
  _body( u16, 1)
  _ev_end

/***********************<< ѡ�����ص����� >>********************	
 *[��Ϣ��]
 * u16
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppViewLocal_Cmd )
  _body( u16, 1)
  _ev_end
  
/***********************<< ѡ�������᳡������ >>********************	
 *[��Ϣ��]
 * u16
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event(  ev_tppViewcViewOther_Cmd )
  _body( u16, 1)
 _ev_end

/***********************<< ���ն�����ؼ�֡������ >>********************	
 *[��Ϣ��]
 * EmTPVideoType ��Ƶ����
 * EmTPMtVideoPort ��Ƶ�˿�
 * u8 DVIMode
 * u8 �����λ��
 *[��Ϣ����]
 *  cns	  -> mt
 */
  _event( ev_tppVideoSourceSelCmd )
  _body ( EmTPVideoType    , 1    )
  _body ( EmTPMtVideoPort    , 1    )
  _body ( u8    , 1    )
  _body ( u8    , 1    )
  _ev_end

  ///////////////////////////////////////
  /***********************<< �������� >>********************	
 *[��Ϣ��]
 * BOOL
 *[��Ϣ����]
 *  cns	  -> mt,cnc->cns
 */
  _event(  ev_tppMute_Cmd )
  _body( BOOL, 1)
  _ev_end

/***********************<< �������� >>********************	
 *[��Ϣ��]
 * BOOL
 *[��Ϣ����]
 *  cns	  -> mt,cnc->cns
 */
  _event(  ev_tppQuiet_Cmd )
  _body( BOOL, 1)
  _ev_end
  
/***********************<< ������Ϣ��Ӧ >>********************	
 *[��Ϣ��]
 * BOOL
 *[��Ϣ����]
 *  cns	  <- mt,cnc<-cns
 */
	_event( ev_tppQuietInd    )
   _body ( BOOL    , 1    )
   _ev_end

/***********************<< ������Ϣ��Ӧ >>********************	
 *[��Ϣ��]
 * BOOL
 *[��Ϣ����]
 *  cns	  <- mt, cnc<-cns
 */
   _event( ev_tppMuteInd    )
   _body ( BOOL    , 1    )
   _ev_end

  /***********************<< ������������������ >>********************	
 *[��Ϣ��]
 * u8 ��������
 * u8 �������λ��
 *[��Ϣ����]
 *  cns	  -> mt,cnc->cns
 */
 _event( ev_tppInputVolumeCmd )
   _body ( u8    , 1    )
   _body ( u8, 1 )
   _ev_end

  /***********************<< �������������Ļ�Ӧ >>********************	
 *[��Ϣ��]
 * u8 ��������
 *[��Ϣ����]
 *  cns	  <- mt,cnc<-cns
 */
 _event(  ev_tppInputVolumeInd  )
   _body ( u8    , 1    )
   _ev_end

  /***********************<< ����������������� >>********************	
 *[��Ϣ��]
 * u8 �������
 * u8 �������λ��
 *[��Ϣ����]
 *  cns	  -> mt,cnc->cns
 */
_event( ev_tppOutputVolumeCmd )
   _body ( u8    , 1    )
   _body ( u8, 1 )
   _ev_end

  /***********************<< ������������Ļ�Ӧ >>********************	
 *[��Ϣ��]
 * u8 �������
 *[��Ϣ����]
 *  cns	  <- mt,cnc<-cns
 */
_event(  ev_tppOutputVolumeInd  )
   _body ( u8    , 1    )
   _ev_end
///////////////////////

/***********************************/
 /***********************<< ������Ƶ��Aac���������� >>********************	
 *[��Ϣ��]
 * EmTpCodecComponent 
 * u8 Aacͨ������
 * u32 Aac������
 * u16 Aac����
 * EmTpAudioFormat ��Ƶ��ʽ
 * u16 �������λ��
 *[��Ϣ����]
 *  cns	  -> mt,cnc->cns
 */
_event( ev_tppAudAacParam_Cmd )
_body( EmTpCodecComponent, 1 )
_body( u8, 1 )
_body( u32, 1 )
_body( u16, 1 )
_body( EmTpAudioFormat, 1 )
_body( u16, 1 )
_ev_end




_event( ev_tppSetDvi2IntoDvi1Out )
_ev_end

_event( ev_tppSetMainDecIntoDvi1Out )
_ev_end

/***********************<< ��ȡ��ƵԴ״̬������ >>********************	
 *[��Ϣ��]
 * EmTpCodecComponent
 * BOOL �Ƿ������л���ƵԴ
 *[��Ϣ����]
 *  cns	  -> mt
 */
_event( ev_tppGetVidSrcStatusCmd )
_body( EmTpCodecComponent, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< ��ȡ��ƵԴ״̬����Ϣ��Ӧ>>********************	
 *[��Ϣ��]
 * EmTpCodecComponent
 * BOOL ����Ƶ�Ƿ�������Դ
 * BOOL �Ƿ������л���ƵԴ
 *[��Ϣ����]
 *  cns	  <- mt
 */
_event( ev_tppGetVidSrcStatusInd )
_body( EmTpCodecComponent, 1 )
_body( BOOL , 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< ����ep�б� >>********************	
 *[��Ϣ��]
s8* �ļ�ȫ·����
 *[��Ϣ����]
 *  cns	  <- mt
*/
_event(  ev_CnSnapshotShow_Cmd )
_body ( s8    , 128    )
_ev_end

/***********************<< ����ͨ�����ʵ����� >>********************	
 *[��Ϣ��]
 * s32 ͨ��ID
 * u16 ����
 *[��Ϣ����]
 *  cncall	  -> cns
 */
_event( ev_tppFlowCtrlFromStack_Cmd )
_body( s32, 1 )
_body( u16, 1 )
_ev_end

/***********************<< ����ؼ�֡������ >>********************	
 *[��Ϣ��]
 * s32 ͨ��ID
 *[��Ϣ����]
 *  cncall	  -> cns
 */
_event( ev_tppSndKeyFrameFromStack_Req )
_body( s32, 1 )
_ev_end

/***********************<< ѡ��Զ���������Ϣ��Ӧ >>********************	
 *[��Ϣ��]
 * s32 ͨ��ID
 * TTPChanSelecteCascadRes 
 *[��Ϣ����]
 *  cncall	  -> cns
 */
_event( ev_CnSingleViewFromStack_Ind )
_body( s32, 1 )
_body( TTPChanSelecteCascadRes, 1 )
_ev_end

/***********************<< ȡ��ѡ��Զ���������Ϣ��Ӧ >>********************	
 *[��Ϣ��]
 * s32 ͨ��ID
 * TTPChanSelecteCascadCancelRes 
 *[��Ϣ����]
 *  cncall	  -> cns
 */
_event( ev_CnCancelSingleViewFromStack_Ind )
_body( s32, 1 )
_body( TTPChanSelecteCascadCancelRes, 1 )
_ev_end

/***********************<< ѡ��Զ������ >>********************	
 *[��Ϣ��]
 * s32 ͨ��ID
 *[��Ϣ����]
 *  cncall	  -> cns
 */
_event( ev_CnChanViewLocalCmdFromStack )
_body( s32, 1 )
_ev_end

/***********************<< ȡ��ѡ��Զ������ >>********************	
 *[��Ϣ��]
 * s32 ͨ��ID
 *[��Ϣ����]
 *  cncall	  -> cns
 */
_event( ev_CnChanCancelViewLocalCmdFromStack )
_body( s32, 1 )
_ev_end

 /***********************<<������ܷ����� >>************************	
 *[��Ϣ��]			 
 *  TTPNMServerCfg 
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtAddNMServerCmd  )
 _body( TTPNMServerCfg, 1 )
 _ev_end
 
 /***********************<<ɾ�����ܷ����� >>************************	
 *[��Ϣ��]			 
 *  TTPNMServerCfg 
 *
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtDelNMServerCmd  )
 _body( TTPNMServerCfg, 1 )
 _ev_end
 
 /***********************<<�޸����ܷ����� >>************************	
 *[����Ϣ��]			 
 *  TTPNMServerCfg
 *[��Ϣ����]
 *    CNS => AGENT
 */
 _event(  ev_CnAgtModifyNMServerCmd  )
 _body( TTPNMServerCfg, 1 )
 _ev_end

  /***********************<< ���ն�����ؼ�֡������ >>********************	
 *[��Ϣ��]
 * TTpCodecComponent
 *[��Ϣ����]
 *  cnmp	  -> cns
 */
  _event(  ev_tppFastUpdate_Cmd )
  _body( TTpCodecComponent, 1)
  _ev_end

   /***********************<< ��ums����ȥ���ؼ�֡���� >>********************	
 *[��Ϣ��]
 * u32
 *[��Ϣ����]
 * cns	  -> ums
 */
  _event(  ev_tppChanResetKeyFrame_Req )
  _body( u32, 1)
  _ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsmp )
};
#endif
#endif //TPP_EVENT_H
