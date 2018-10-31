#ifndef _h_eventoutumseqp_h__
#define _h_eventoutumseqp_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumseqp
{
#endif

	_ev_segment( outerumseqp )

  /***********************<<  �������������豸����������ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix -> audiomixeqp	
 *
 */
 _event(  ev_AudioMixInitCfg_Req )
	_body( TModelProp, 1 )
 _ev_end

  /***********************<<  ������������ʼ���ɹ�������豸�������������ע��״̬ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix -> audiomixeqp
 *
 */
 _event(  ev_AudioMixInitSuccess_Ind )
  _body( u16, 1 )
  _body( BOOL32, 1)
 _ev_end


   /***********************<<  Mpc������ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] Mpc -> Mpceqp	
 *
 */
 _event(  ev_MpcInitCfg_Req )
	_body( TModelProp, 1 )
	_body( TTPTime, 1 )	//����ʱ���ʱ��
	_body( TTPTime, 1 )	//ϵͳ��ǰʱ��
 _ev_end

 /***********************<<  Mpcע��ɹ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcInitCfg_ACK )
	_body( TModelProp, 1 )
 _ev_end


   /***********************<<  Mpcע��ʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcInitCfg_NACK )	
 _ev_end

   /***********************<<  Mpc���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcIsMaster_Ntf )
	_body( BOOL32, 1 )		//�Ƿ�����
 _ev_end

    /***********************<<  ����Mpcʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] Mpceqp -> Mpc	
 *
 */
 _event(  ev_MpcSetTime_Cmd )
	_body( TTPTime, 1 )		//����ʱ��
	_body( TTPTime, 1 )		//��ǰʱ��
 _ev_end

 /***********************<<  adapterע�� >>*********************/
_event(  ev_SipAdapterInitCfg_Req ) //adapter -> ums
_body(TModelProp, 1)
_body(EmTpConfProtocol, 1)
_ev_end

/***********************<<  adapterע��ʧ�� >>*********************/
_event(  ev_SipAdapterInitCfg_NACK )
_ev_end

/***********************<<  adapterע��ɹ� >>*********************/
_event(  ev_SipAdapterInitCfg_ACK )
_body(TUmsStackCallCfg, 1)
_body(TTPQTEncryptInfo, 1)
_body(BOOL32,1)
_ev_end

/***********************<<  adapter�����ɹ� >>*********************/
_event(  ev_SipAdapterInitSuccess_Ind )
_body(u16, 1)//ums���豸����
_ev_end
 

/***********************<<  ת��ע�� >>*********************/
_event(  ev_MediaTrans_Req ) //adapter -> ums
_body(TModelProp, 1)
_body(TIpmaskinfo, 1)
_ev_end
_event(  ev_MediaTrans_NACK ) //adapter -> ums
_ev_end
_event(  ev_MediaTrans_ACK ) //adapter -> ums
_body(TUmsMediatransCfg, 1)
_ev_end
/***********************<<  �����ɹ� >>*********************/
_event(  ev_MediatransInitSuccess_Ind )
_body(u16, 1)//ums���豸����
_ev_end




/***********************<<  Netbufע�� >>*********************/
_event(  ev_Netbuf_Req ) //Netbuf -> ums
_body(TModelProp, 1)
_ev_end
_event(  ev_Netbuf_NACK ) //Netbuf -> ums
_ev_end
_event(  ev_Netbuf_ACK ) //Netbuf -> ums
_body(TUmsNetbufCfg, 1)
_ev_end
/***********************<<  �����ɹ� >>*********************/
_event(  ev_NetbufInitSuccess_Ind )
_body(u16, 1)//ums���豸����
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(outerumseqp)
};
#endif


#endif // _h_eventoutumseqp_h__
