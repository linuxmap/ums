#ifndef _h_innereventxmpuaudbas_h__
#define _h_innereventxmpuaudbas_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpuaudbas
{
#endif

	_ev_segment( innereventxmpuaudbas )


   /***********************<<  xmpu start audbas rsp  >>********************	
 *[消息体]			 
 *   TXmpuStartAudBasRsp
 *[消息方向]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_StartAudBas_Rsp )
 _body( TXmpuStartAudBasRsp, 1 )
 _ev_end

  /***********************<<  xmpu start aud bas Nty  >>********************	
 *[消息体]			 
 *   TXmpuStartAudBasNty
 *[消息方向]	XmpuEQP - Call
 *
 */
 _event(  evXmpu_UmsStartAudBas_Nty )
 _body( TXmpuStartAudBasNty, 1 )
 _ev_end

    /***********************<<  xmpu set audbas req  >>********************	
 *[消息体]			 
 *   TXmpuAudBasParam
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_SetAudBasParam_Req )
 _body( TXmpuChgAudParam, 1 )
 _ev_end

    /***********************<<  xmpu set audbas rsp  >>********************	
 *[消息体]			 
 *   TXmpuSetAudBasRsp
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_SetAudBasParam_Rsp )
 _body( TXmpuSetAudBasRsp, 1 )
 _ev_end

    /***********************<<  xmpu set audbas Nty  >>********************	
 *[消息体]			 
 *   BOOL32
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_SetAudBasParam_Nty )
 _body( BOOL32, 1 )
 _ev_end

   /***********************<<  xmpu start audbas rsp  >>********************	
 *[消息体]			 
 *   TXmpuSetAudSynInfo
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_AudBasSetSyn_Req )
 _body( TXmpuAudBasSynInfo, 1 )
 _ev_end

  /***********************<<  xmpu audbas disConnect rsp  >>********************	
 *[消息体]			 
 *   u32
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_AudBasDisConnect_Nty )
 _body( u32, 1 )
 _ev_end

 

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innereventxmpuaudbas)
};
#endif


#endif // _h_innereventumsaudiomix_h__
