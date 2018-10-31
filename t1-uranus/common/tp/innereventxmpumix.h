#ifndef _h_innereventxmpumix_h__
#define _h_innereventxmpumix_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpumix
{
#endif

	_ev_segment( innereventxmpumix )

  /***********************<<  xmpu start mix rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartMixRsp
 *[��Ϣ����]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_UmsStartMix_Rsp )
 _body( TXmpuStartMixRsp, 1 )
 _ev_end

   /***********************<<  xmpu start mix nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartMixNty
 *[��Ϣ����]	XmpuEqp - Call
 *
 */
 _event(  evXmpu_UmsStartMix_Nty )
 _body( TXmpuStartMixNty, 1 )
 _ev_end

   /***********************<<  xmpu add mix member req  >>********************	
 *[��Ϣ��]			 
 *   TXmpuMixMember
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuAddMixMember_Req )
 _body( TXmpuMixMember, 1 )
 _ev_end

    /***********************<<  xmpu add mix member rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuAddMixMemRsp
 *[��Ϣ����]	MediaSource - XmpuEqp
 *
 */
 _event(  evUms_XmpuAddMixMember_Rsp )
 _body( TXmpuAddMixMemRsp, 1 )
 _body( u32, 1 )
 _ev_end

   /***********************<<  xmpu add mix member nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuAddMixMemNty
 *[��Ϣ����]	XmpuEqp - Call
 *
 */
 _event(  evUms_XmpuAddMixMember_Nty )
 _body( TXmpuAddMixMemNty, 1 )
 _ev_end

    /***********************<<  xmpu del mix member req  >>********************	
 *[��Ϣ��]			 
 *   u32 u8
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuDelMixMember_Req )
 _body( u32, 1 )
 _body( u8, 1 )
 _ev_end

   /***********************<<  xmpu set keep time rep  >>********************	
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	Call - XmpuEqp
 *u32 u32
 */
 _event(  evXmpu_SetKeepTime_Req )
 _body( u32, 1 )
 _body( u32, 1 )
 _ev_end
 
 /***********************<<  xmpu start var req  >>********************	
 *[��Ϣ��]			 
 *   u32
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_StartVac_Req )
 _body( u32, 1 )
 _ev_end

    /***********************<<  xmpu start var rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartVacRsp
 *[��Ϣ����]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_StartVac_Rsp )
 _body( TXmpuStartVacRsp, 1 )
 _ev_end

  /***********************<<  xmpu stop var req  >>********************	
  *[��Ϣ��]			 
 *   u32
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_StopVar_Req )
 _body( u32, 1 )
 _ev_end

     /***********************<<  xmpu set syn nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuVacActiveNty
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_SetMixSync_Req )
 _body( TXmpuMixSynInfo, 1 )
 _ev_end

    /***********************<<  xmpu Vac activie nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuVacActiveNty
 *[��Ϣ����]	MediaSource - XmpuEqp - Call
 *
 */
 _event(  evXmpu_ForceActive_Req )
 _body( TForceActiveInfo, 1 )
 _ev_end
 
   /***********************<<  xmpu Vac activie nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuVacActiveNty
 *[��Ϣ����]	MediaSource - XmpuEqp - Call
 *
 */
 _event(  evXmpu_VacActive_Ntf )
 _body( TXmpuVacActiveNty, 1 )
 _body(u32,1)
 _ev_end

    /***********************<<  xmpu Vac activie nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuVacActiveNty
 *[��Ϣ����]	MediaSource - XmpuEqp - Call
 *
 */
 _event(  evXmpu_MixVoiceDetection_Ntf )
 _body( TVoiceDetectionNty, 1 )
 _body (u32,1)
 _ev_end

    /***********************<<  xmpu dis connect nty  >>********************	
 *[��Ϣ��]			 
 *   u32,
 *[��Ϣ����]	MediaSource - XmpuEqp - Call
 *
 */
 _event(  evXmpu_MixDisConnect_Nty )
 _body( u32, 1 )
 _ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(innereventxmpumix)
};
#endif


#endif // _h_innereventumsaudiomix_h__
