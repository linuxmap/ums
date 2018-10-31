#ifndef _h_eventoutcnssipdual_h__
#define _h_eventoutcnssipdual_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSIPDUALEVENT
{
#endif 

  _ev_segment( outercnssipdual  )
//˫��

/***********************<<  ����˫������ >>********************	
 *[��Ϣ��]
 TTPDualRequest
 *[��Ϣ����]
 *  cnc	  -> cns ��cncall->cns
*/
  _event(  ev_TppRequestDualStream_Cmd )
  _body (TTPDualRequest, 1)
  _ev_end
  
/***********************<<  ����˫������ >>********************	
 *[��Ϣ��]
 TTPDualInfo ˫����Ϣ
 *[��Ϣ����]
 *  cnc	  -> cns ��cncall->cns
*/
  _event(  ev_TppSendDual_Cmd )
  _body( TTPDualInfo, 1 )
  _ev_end
 
/***********************<<  ֹͣ����˫������ >>********************	
 *[��Ϣ��]
 * NULL
 *[��Ϣ����]
 *  cnc	  -> cns 
*/
  _event(  ev_TppStopDual_Cmd )
  _ev_end
  
/***********************<<  ֹͣ����˫����Ӧ >>********************	
 *[��Ϣ��]
 * NULL
 *[��Ϣ����]
 *  cnc	  <- cns 
*/
  _event(  ev_TppStopDual_Ind )
  _body( EmTPDualReason , 1 )
  _ev_end
 
 /***********************<<  ������˫����Ӧ >>********************	
 *[��Ϣ��]
 * TTPDualInfoAck
 *[��Ϣ����]
 *  cncall	-> cns 
*/
  _event(  ev_TppSendDualStream_Ind )
  _body( TTPDualInfoAck, 1)
  _ev_end
  
/***********************<<  ����˫���ؼ�֡����>>********************	
 *[��Ϣ��]
 * NULL
 *[��Ϣ����]
 *  cncall	-> cns 
*/
  _event(  ev_TppDualSendKeyFrame_Cmd )
  _body(BOOL, 1)
 _ev_end

/***********************<<  ��ʼ����˫����Ӧ>>********************	
 *[��Ϣ��]
 * u32
 *[��Ϣ����]
 *  cncall	-> cns 
*/
 _event( ev_tppStartRcvDual_Ind )
 _body( u32, 1 )
 _ev_end
 
/***********************<<  ֹͣ����˫����Ӧ>>********************	
 *[��Ϣ��]
 * u32
 *[��Ϣ����]
 *  cncall	-> cns 
*/
 _event( ev_tppStopRcvDual_Ind )
  _body( u32, 1 )
_ev_end

/***********************<<  ����˫�� >>********************	
 *[��Ϣ��]
 * NULL 
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppStartDual_Cmd )
_ev_end

/***********************<<  ����˫����Ӧ >>********************	
 *[��Ϣ��]
 EmTPDualReason
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppStartDual_Ind )
_body( EmTPDualReason , 1 )
_ev_end


/***********************<<  �Ƿ��ڷ�˫��֪ͨ >>********************	
 *[��Ϣ��]
 BOOL
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppIsDual_Nty )
_body( BOOL , 1 )
_ev_end


/***********************<<  �Ƿ�����˫��֪ͨ >>********************	
 *[��Ϣ��]
 BOOL
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppIsRcvDual_Nty )
_body( BOOL , 1 )
_ev_end

/***********************<<  ����˫�����ܵ�ַ >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cnc	  -> cns
 *  BODY�зֱ������Ƶ����Ƶ������˳���ܵߵ���
*/
_event(  ev_TppAddDualRcvAddr_Cmd )
_body( TTPCnMediaTransPort, 2 )
_ev_end

/***********************<<  ����˫�����ܵ�ַ��Ӧ >>********************	
 *[��Ϣ��]
 EmTPDualReason
 *[��Ϣ����]
 *  cnc	  <- cns
 * BODY�зֱ���������Ƶ����Ƶ�����Ľ�������������l�����ͱ�ʶ��˳���ܵߵ�)
*/
_event(  ev_TppAddDualRcvAddr_Ind )
_body( EmTPAddDualRcvResult, 2 )
_body( TTPCnMediaTransPort, 2 )
_body( u16,  2 )
_ev_end

/***********************<<  ɾ��˫�����ܵ�ַ >>********************	
 *[��Ϣ��]
 *��u16����λ�š���
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppDelDualRcvAddr_Cmd )
_body( u16,  1 )
_ev_end


/***********************<<  ɾ��˫�����ܵ�ַ��Ӧ >>********************	
 *[��Ϣ��]
 * EmTPDeleteDualRcvResult
 * u16 ��λ��
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppDelDualRcvAddr_Ind )
_body( EmTPDeleteDualRcvResult, 1 )
_body( u16, 1 )
_ev_end



/***********************<<  ˫��ͨ���������� >>********************	
 *[��Ϣ��]
 * NULL
 *[��Ϣ����]
 * cncall -> cns
*/
_event(  ev_TppDualChannelIncoming_Nty )
_ev_end

/***********************<<  ����ѡ��˫�� >>********************	
 *[��Ϣ��]
 * u16 ����
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppSelDualView_Cmd )
_body( u16, 1 )
_ev_end
  

/***********************<<  ����ѡ��˫����Ӧ>>********************	
 *[��Ϣ��]
 * u16 ����
 * EmTPAddDualRcvResult ��ӽ��
 * s8 ˫���ն�����
 *[��Ϣ����]
 *  cns	  -> cnc
*/
_event(  ev_TppSelDualView_Ind )
_body( u16, 1 )
_body( EmTPAddDualRcvResult, 1 )
_body( s8, TP_MAX_NAME_LEN +1 )
_ev_end


/***********************<<  ȡ��ѡ��˫�� >>********************	
 *[��Ϣ��]
 * u16 ����
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppCancelSelDualView_Cmd )
_body( u16, 1 )
_ev_end
  

/***********************<<  ȡ��ѡ��˫����Ӧ>>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *  cns	  -> cnc
*/
_event(  ev_TppCancelSelDualView_Ind )
_body( u16, 1 )
_body( EmTPDeleteDualRcvResult, 1 )
_ev_end

/***********************<<  PAD˫���ؼ�֡����>>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *u16 SlotID
 *BOOL bForce �Ƿ�ǿ��
 *  cnc	  -> cns
*/
_event(  ev_TppPadDualKeyFrame_Req )
_body( u16, 1 )
_body( BOOL, 1 )
_ev_end


/***********************<<  ������˫������ >>********************	
 *[��Ϣ��]
 *TConfEpID ����ID
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event(  ev_TppConfStartDual_Cmd )
_body( TConfEpID, 1 )
_ev_end

/***********************<<  ������˫������Ӧ�� >>********************	
 *[��Ϣ��]
 *TConfEpID ����ID
 *EmTPDualReason ����˫�����
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfStartDual_Ind )
_body( TConfEpID, 1 )
_body( EmTPDualReason, 1 )
_ev_end

/***********************<<  ������˫���᳡�㲥֪ͨ >>********************	
 *[��Ϣ��]
 *TConfEpID ����ID
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppConfDualEp_Nty )
_body( TConfEpID, 1 )
_ev_end

/***********************<<  ˫���ն˵��߹Ҷ�˫�� >>********************	
 *[��Ϣ��]
 *NULL
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppStopDualOffLine_Cmd )
_ev_end

/***********************<<  ˫���ն˵��߹Ҷ�˫�� >>********************	
 *[��Ϣ��]
 * EmTPChannelReason
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event(  ev_TppDualRcvInterrupt_Nty )
_body( EmTPChannelReason, 1 )
_ev_end



/***********************<<  ������ͣ˫������ >>********************	
 *[��Ϣ��]
 *TConfEpID ����ID
 *[��Ϣ����]
 *  cnc	  -> cns
*/
_event( ev_TppConfStopDual_Cmd )
_body( TConfEpID, 1 )
_ev_end

/***********************<<  ������ͣ˫�������Ӧ >>********************	
 *[��Ϣ��]
 *TConfEpID ����ID
 *EmTPDualReason ����˫�����
 *[��Ϣ����]
 *  cnc	  <- cns
*/
_event( ev_TppConfStopDual_Ind )
_body( TConfEpID, 1 )
_body( EmTPDualReason, 1)
_ev_end

//Add by tanxiaodong 2012-07-17.
/***********************<<����˫������˿���������  >>********************
*[��Ϣ��]
* TVgaInfo ˫��ԴVga��Ϣ
* BOOL �Ƿ����óɹ�
*[��Ϣ����]
*  cnc	  -> cns
*/
_event( ev_TppSetDualInputPortName_Cmd )
_body(TVgaInfo, 1)
_body(BOOL, 1)
_ev_end

/***********************<<����˫������˿����ƻ�Ӧ  >>********************
*[��Ϣ��]
* BOOL�Ƿ����óɹ�
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_TppSetDualInputPortName_Ind )
_body( BOOL, 1)
_ev_end
  
/***********************<<ѡ��˫������˿�����  >>************************
*[��Ϣ��]
*EmVgaType Ҫ�л���������ʾԴ����
*EmVgaType �����ʾԴ����
*[��Ϣ����]
*  cns	  -> mt
*/
_event( ev_TppSelDualInputPort_Cmd )
_body(EmVgaType, 2)
_ev_end
	
/***********************<<ѡ��˫������˿ڻ�Ӧ  >>************************
*[��Ϣ��]
*BOOL �л����
*EmVgaType �л������ʾԴ��������
*EmVgaSwitchResult�л����
*[��Ϣ����]
*  mt	   -> cns
*/
_event( ev_TppSelDualInputPort_Ind )
_body(BOOL, 1)
_body(EmVgaType, 1)
_body(EmVgaSwitchResult, 1)
_ev_end

/***********************<<��ǰVGA�ӿ���Ϣ֪ͨ  >>************************
*[��Ϣ��]
* TVgaInfo 7����ʾԴ��Ϣ
* TVgaInfo Ĭ����ʾԴ��Ϣ
* EmVgaType ��ǰ��ʾԴ����
*TTPVgaMixInfo
*[��Ϣ����]
*  cns	   -> cnc
*/
_event( ev_TppCurrentVgaInfo_Nty )
_body(TVgaInfo, CNS_VGA_TYPE_NUM)
_body(TVgaInfo, 1)
_body(EmVgaType, 1)
_body(TTPVgaMixInfo, 1)
_ev_end

/***********************<<��ǰ����VGA�ӿ���Ϣ֪ͨ  >>************************
*[��Ϣ��]
* EmVgaType ��ǰ��ʾԴ����
*[��Ϣ����]
*  cns	   -> cnc
*/
_event( ev_TppConfVgaInfo_Nty )
_body(EmVgaType, 1)
_ev_end
//End to add.

/***********************<<���˫��Դ�ӿ��Ƿ���Դ�Ķ�ʱ��  >>************************
*[��Ϣ��]
*NULL
*[��Ϣ����]
*  cns	   -> cns
*/
_event( ev_TppCheckDualSrc_Timer )
_ev_end

/***********************<< ���ڹ��ܲ�����Ϣ >>************************
*[��Ϣ��]
*NULL
*[��Ϣ����]
*  cns	   -> cns
*/
_event( ev_TppProduceTestSerial_Cmd )
_body(EmSerialType, 1)
_body(EmSerialType, 1)
_ev_end

/***********************<<ѡ��˫������˿ڶ�ʱ��  >>************************
*[��Ϣ��] vcs�Ƿ���˫��
*[��Ϣ����]
*  cncall	   -> cns
*/
_event( ev_TppChgSecVidSend_Cmd )
_body( BOOL, 1 )
_ev_end

/***********************<<  �Ƿ�ʼ�ļ�˫��֪ͨ >>********************	
 *[��Ϣ��]
 *  +BOOL                  TRUE=��ʼ FALSE =ֹͣ
 *[��Ϣ����]
 *  TPad	  -> cns
*/
_event(  ev_TppTPadDualVideo_Cmd )
_body( BOOL , 1 )
_ev_end

/***********************<< ��ʼ�ļ�˫������  >>************************
 *[��Ϣ��]			 
 *  +BOOL             TRUE=PC˫�� FALSE =��PC˫��
 *[��Ϣ����]
 *
 *    cns => TPad
 */_event(  ev_TppTPadDualVideo_Ind   )
   _body ( BOOL, 1 )
   _ev_end

/***********************<<  ��ʼ�ļ�˫������ >>********************	
 *[��Ϣ��]
 *  +TTPCnMediaTransPort   ���ؽ��յ�rtp��ַ�Ͷ˿� 
 *[��Ϣ����]
 *  TPad <- cns
*/
_event(  ev_TppTPadDualRcvAddr_Cmd )
_body( TTPCnMediaTransPort, 1 )
_ev_end

/***********************<<  �����ļ�˫�����ܵ�ַ��Ӧ >>********************	
 *[��Ϣ��]
 *EmTPAddDualRcvResult
 *TTPCnMediaTransPort
 *u16
 *[��Ϣ����]
 *  TPad -> cns
 * BODY�м�����Ƶ������������l�����ͱ�ʶ
*/
_event(  ev_TppTPadDualRcvAddr_Ind )
_body( EmTPAddDualRcvResult, 1 )
_body( TTPCnMediaTransPort, 1 )
_body( u16,  1 )
_ev_end

/***********************<<�����ʾԴ�ӿ�״̬  >>************************
*[��Ϣ��]
*BOOL ��ʾԴ�ӿ��Ƿ���Դ
*[��Ϣ����]
*  cnmp	   -> cns
*/
_event( ev_TppGetDualVidSrc_Nty )
_body( BOOL, 1 )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipdual )
};
#endif
#endif //TPP_EVENT_H
