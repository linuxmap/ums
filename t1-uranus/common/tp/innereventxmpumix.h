#ifndef _h_innereventxmpumix_h__
#define _h_innereventxmpumix_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpumix
{
#endif

	_ev_segment( innereventxmpumix )

  /***********************<<  xmpu start mix rsp  >>********************	
 *[消息体]			 
 *   TXmpuStartMixRsp
 *[消息方向]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_UmsStartMix_Rsp )
 _body( TXmpuStartMixRsp, 1 )
 _ev_end

   /***********************<<  xmpu start mix nty  >>********************	
 *[消息体]			 
 *   TXmpuStartMixNty
 *[消息方向]	XmpuEqp - Call
 *
 */
 _event(  evXmpu_UmsStartMix_Nty )
 _body( TXmpuStartMixNty, 1 )
 _ev_end

   /***********************<<  xmpu add mix member req  >>********************	
 *[消息体]			 
 *   TXmpuMixMember
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuAddMixMember_Req )
 _body( TXmpuMixMember, 1 )
 _ev_end

    /***********************<<  xmpu add mix member rsp  >>********************	
 *[消息体]			 
 *   TXmpuAddMixMemRsp
 *[消息方向]	MediaSource - XmpuEqp
 *
 */
 _event(  evUms_XmpuAddMixMember_Rsp )
 _body( TXmpuAddMixMemRsp, 1 )
 _body( u32, 1 )
 _ev_end

   /***********************<<  xmpu add mix member nty  >>********************	
 *[消息体]			 
 *   TXmpuAddMixMemNty
 *[消息方向]	XmpuEqp - Call
 *
 */
 _event(  evUms_XmpuAddMixMember_Nty )
 _body( TXmpuAddMixMemNty, 1 )
 _ev_end

    /***********************<<  xmpu del mix member req  >>********************	
 *[消息体]			 
 *   u32 u8
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuDelMixMember_Req )
 _body( u32, 1 )
 _body( u8, 1 )
 _ev_end

   /***********************<<  xmpu set keep time rep  >>********************	
 *[消息体]			 
 *   
 *[消息方向]	Call - XmpuEqp
 *u32 u32
 */
 _event(  evXmpu_SetKeepTime_Req )
 _body( u32, 1 )
 _body( u32, 1 )
 _ev_end
 
 /***********************<<  xmpu start var req  >>********************	
 *[消息体]			 
 *   u32
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_StartVac_Req )
 _body( u32, 1 )
 _ev_end

    /***********************<<  xmpu start var rsp  >>********************	
 *[消息体]			 
 *   TXmpuStartVacRsp
 *[消息方向]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_StartVac_Rsp )
 _body( TXmpuStartVacRsp, 1 )
 _ev_end

  /***********************<<  xmpu stop var req  >>********************	
  *[消息体]			 
 *   u32
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_StopVar_Req )
 _body( u32, 1 )
 _ev_end

     /***********************<<  xmpu set syn nty  >>********************	
 *[消息体]			 
 *   TXmpuVacActiveNty
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_SetMixSync_Req )
 _body( TXmpuMixSynInfo, 1 )
 _ev_end

    /***********************<<  xmpu Vac activie nty  >>********************	
 *[消息体]			 
 *   TXmpuVacActiveNty
 *[消息方向]	MediaSource - XmpuEqp - Call
 *
 */
 _event(  evXmpu_ForceActive_Req )
 _body( TForceActiveInfo, 1 )
 _ev_end
 
   /***********************<<  xmpu Vac activie nty  >>********************	
 *[消息体]			 
 *   TXmpuVacActiveNty
 *[消息方向]	MediaSource - XmpuEqp - Call
 *
 */
 _event(  evXmpu_VacActive_Ntf )
 _body( TXmpuVacActiveNty, 1 )
 _body(u32,1)
 _ev_end

    /***********************<<  xmpu Vac activie nty  >>********************	
 *[消息体]			 
 *   TXmpuVacActiveNty
 *[消息方向]	MediaSource - XmpuEqp - Call
 *
 */
 _event(  evXmpu_MixVoiceDetection_Ntf )
 _body( TVoiceDetectionNty, 1 )
 _body (u32,1)
 _ev_end

    /***********************<<  xmpu dis connect nty  >>********************	
 *[消息体]			 
 *   u32,
 *[消息方向]	MediaSource - XmpuEqp - Call
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
