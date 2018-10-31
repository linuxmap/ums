#ifndef _h_innereventxmpubas_h__
#define _h_innereventxmpubas_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpubas
{
#endif

	_ev_segment( innereventxmpubas )

 /***********************<<  xmpu start vid bas rsp  >>********************	
 *[消息体]			 
 *   TXmpuStartBasRsp
 *[消息方向]	MediaSource - XmpuEQP
 *
 */
 _event(  evXmpu_StartVidBas_Rsp )
 _body( TXmpuStartBasRsp, 1 )
 _ev_end

  /***********************<<  xmpu start vid bas Nty  >>********************	
 *[消息体]			 
 *   TXmpuStartBasNty
 *[消息方向]	XmpuEQP - Call
 *
 */
 _event(  evXmpu_UmsStartVidBas_Nty )
 _body( TXmpuStartBasNty, 1 )
 _ev_end

   /***********************<<  xmpu set vid bas Param req  >>********************	
 *[消息体]			 
 *   TXmpuChgBasInfo
 *[消息方向]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_SetBasEncParam_Req )
 _body( TXmpuChgBasInfo, 1 )
 _ev_end

  /***********************<<  xmpu start vid bas Nty  >>********************	
 *[消息体]			 
 *   tagTXmpuSetBasEncRsp
 *[消息方向]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_SetBasEncParam_Rsp )
 _body( TXmpuSetBasEncRsp,  1 )
 _ev_end

  /***********************<<  xmpu start vid bas Nty  >>********************	
 *[消息体]			 
 *   TXmpuStartBasNty
 *[消息方向]	XmpuEQP - Call
 *
 */
 _event(  evXmpu_SetBasEncParam_Nty )
 _body( TXmpuSetBasEncNty, 1 )
 _ev_end

 /***********************<<  请求关键帧 >>********************	
 *[消息体]			 
 *   TTPVmpAskFrame
 *[消息方向]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_AskBasKey_Req ) 
 _body( u32, 1 )
 _ev_end

 /***********************<<  请求关键帧 >>********************	
 *[消息体]			 
 *   TTPVmpAskFrame
 *[消息方向]	call - XmpuEqp
 *
 */
 _event(  evUms_XmpuAskBasKey_Req ) 
 _body( u32, 1 )
 _ev_end

  /***********************<< VidBas disconnect >>********************	
 *[消息体]			 
 *   TTPBasReg
 *[消息方向]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_BasDisConnect_Nty )
 _body( u32, 1 )
 _ev_end

   /***********************<< StartbasRsp common  >>********************	
 *[消息体]			 
 *   TXmpuStartBasCommonRsp
 *[消息方向]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_StartBas_Rsp )
 _body (TXmpuStartBasCommonRsp ,1)
 _ev_end
    /***********************<< SetbasEncparam common  >>********************	
 *[消息体]			 
 *   TXmpuStartBasCommonRsp
 *[消息方向]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_SetBasCommonEncParam_Rsp )
 _body (TXmpuStartBasCommonRsp ,1)
 _ev_end
 
   /***********************<< Bas disconnect commonn>>********************	
 *[消息体]			 
 *   TTPBasReg
 *[消息方向]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_BasCommonDisConnect_Nty )
 _body( u32, 1 )
 _ev_end
#ifndef _MakeTpEventDescription_
   _ev_segment_end(innereventxmpubas)
};
#endif


#endif // _h_innereventumsaudiomix_h__
