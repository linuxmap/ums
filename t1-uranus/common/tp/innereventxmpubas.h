#ifndef _h_innereventxmpubas_h__
#define _h_innereventxmpubas_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpubas
{
#endif

	_ev_segment( innereventxmpubas )

 /***********************<<  xmpu start vid bas rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartBasRsp
 *[��Ϣ����]	MediaSource - XmpuEQP
 *
 */
 _event(  evXmpu_StartVidBas_Rsp )
 _body( TXmpuStartBasRsp, 1 )
 _ev_end

  /***********************<<  xmpu start vid bas Nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartBasNty
 *[��Ϣ����]	XmpuEQP - Call
 *
 */
 _event(  evXmpu_UmsStartVidBas_Nty )
 _body( TXmpuStartBasNty, 1 )
 _ev_end

   /***********************<<  xmpu set vid bas Param req  >>********************	
 *[��Ϣ��]			 
 *   TXmpuChgBasInfo
 *[��Ϣ����]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_SetBasEncParam_Req )
 _body( TXmpuChgBasInfo, 1 )
 _ev_end

  /***********************<<  xmpu start vid bas Nty  >>********************	
 *[��Ϣ��]			 
 *   tagTXmpuSetBasEncRsp
 *[��Ϣ����]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_SetBasEncParam_Rsp )
 _body( TXmpuSetBasEncRsp,  1 )
 _ev_end

  /***********************<<  xmpu start vid bas Nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartBasNty
 *[��Ϣ����]	XmpuEQP - Call
 *
 */
 _event(  evXmpu_SetBasEncParam_Nty )
 _body( TXmpuSetBasEncNty, 1 )
 _ev_end

 /***********************<<  ����ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   TTPVmpAskFrame
 *[��Ϣ����]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_AskBasKey_Req ) 
 _body( u32, 1 )
 _ev_end

 /***********************<<  ����ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   TTPVmpAskFrame
 *[��Ϣ����]	call - XmpuEqp
 *
 */
 _event(  evUms_XmpuAskBasKey_Req ) 
 _body( u32, 1 )
 _ev_end

  /***********************<< VidBas disconnect >>********************	
 *[��Ϣ��]			 
 *   TTPBasReg
 *[��Ϣ����]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_BasDisConnect_Nty )
 _body( u32, 1 )
 _ev_end

   /***********************<< StartbasRsp common  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartBasCommonRsp
 *[��Ϣ����]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_StartBas_Rsp )
 _body (TXmpuStartBasCommonRsp ,1)
 _ev_end
    /***********************<< SetbasEncparam common  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartBasCommonRsp
 *[��Ϣ����]	MediaSource - XmpuEqp - call
 *
 */
 _event(  evXmpu_SetBasCommonEncParam_Rsp )
 _body (TXmpuStartBasCommonRsp ,1)
 _ev_end
 
   /***********************<< Bas disconnect commonn>>********************	
 *[��Ϣ��]			 
 *   TTPBasReg
 *[��Ϣ����]	MediaSource - XmpuEqp - call
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
