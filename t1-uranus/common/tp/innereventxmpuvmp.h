#ifndef _h_innereventxmpuvmp_h__
#define _h_innereventxmpuvmp_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpuvmp
{
#endif

	_ev_segment( innereventxmpuvmp )

	 /***********************<<  xmpu init metting rsp  >>********************	
 *[消息体]			 
 *   TXmpuInitMettingRsp
 *[消息方向]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_InitMetting_Rsp )
 _body( TXmpuInitMettingRsp, 1 )
 _ev_end

 	 /***********************<<  xmpu init metting Faild nty  >>********************	
 *[消息体]			 
 *   
 *[消息方向] XmpuEqp - Call
 *
 */
 _event(  evXmpu_InitMettingFaild_Nty )
  _body( BOOL32, 1 )
 _ev_end

 	 /***********************<<  xmpu stop conf  >>********************	
 *[消息体]			 
 *   u16
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuStopConf_Nty )
 _body( u16, 1 )
 _ev_end

 /***********************<<  xmpu vmp connect  nty  >>********************	
 *[消息体]			 
 *   BOOL32
 *[消息方向]	MediaSoruce - XmpuEqp
 *
 */
 _event(  evXmpu_VmpConnect_Nty )
 _body( TXmpuVmpNty, 1 )
 _ev_end

 /***********************<<  xmpu start vmp rsp  >>********************	
 *[消息体]			 
 *   BOOL32
 *[消息方向]	MediaSoruce - XmpuEqp
 *
 */
 _event(  evXmpu_StartVmp_Rsp )
 _body( TXmpuStartVmpRsp, 1 )
 _ev_end

 
 /***********************<<  xmpu change vmp rsp  >>********************	
 *[消息体]			 传统画面合成使用该消息
 *   TTPBasReg
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_ChangeVmp_Req )
 _body( TXmpuStartVmpInfo, 1 )
 _ev_end

  /***********************<<  xmpu start mpu2 req  >>********************	
 *[消息体]			 多画面合成开启
 *   TTPBasReg
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_StartMpu2_Req )
 _body( TVmpStartInfo, 1 )
 _ev_end

 /***********************<<  xmpu UpdateSpeakerSide  >>********************	
 *[消息体]			 设置有声音的边框变绿
 *   TTPBasReg
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_UpdateSpeakerSide_Req )
 _body( TVmpSpeakerFlag, 1 )
 _ev_end
 

 /***********************<<  xmpu vmp 向ums请求关键帧 >>********************	
 *[消息体]			 
 *   TTPBasReg
 *[消息方向]	MediaSource - XmpuEqp - call
 *
 */

 _event(  evXmpu_AskVmpKey_Req ) 
 _body( TTPVmpAskFrame, 1 )
 _body(u32 , 1) 
 _ev_end

 /***********************<< ums 向 xmpu vmp  请求关键帧 >>********************	
 *[消息体]			 
 *   TTPBasReg
 *[消息方向]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuAskVmpKey_Req )
 _body( TTPVmpAskFrame, 1 )
 _ev_end

  /***********************<<  xmpu vmp  状态变更通知 >>********************	
 *[消息体]			 
 *   TTPBasReg
 *[消息方向]	XmpuEqp - Call
 *
 */
 _event(  evXmpu_VmpMdy_Nty ) 
 _body( TXmpuVmpMdyInfo, 1 )
 _ev_end

   /***********************<<  xmpu vmp  掉线通知 >>********************	
 *[消息体]			 
 *   TTPBasReg
 *[消息方向]	 MediaSource - XmpuEqp - Calll
 *
 */
 _event(  evXmpu_VmpDisConnect_Nty ) 
 _body( u32, 1 )
 _ev_end


    /***********************<<  get all res used info  >>********************	
 *[消息体]			 
 *[消息方向]	Ums - XmpuEqp 
 *
 */
 _event(  evXmpu_res_usd_info_req )
 _body( EMXmpuEqpType, 1 )		//外设类型
 _ev_end

 _event(  evXmpu_res_usd_info_res )
 _body( TTPBrdUsedInfo, 1 )
 _ev_end

 /***********************<<  资源获取定时器  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *	定时器
 */
 _event(  evXmpu_Get_Resource_Time )
 _ev_end	

  /***********************<<  xmpu vmp Update UI Nty  >>********************	
 *[消息体]			 
 *   BOOL32
 *[消息方向]	XmpuEqp - umscall
 *
 */
 _event(  evXmpu_VmpRefresh_Nty )
 _body( TXmpuVmpNty, 1 )
 _ev_end

  /***********************<<  刷新资源定时器  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *	定时器
 */
 _event(  evXmpu_Refresh_Resource_Time )
 _ev_end	



 #ifndef _MakeTpEventDescription_
   _ev_segment_end(innereventxmpuvmp)
};
 #endif


#endif // _h_innereventumsaudiomix_h__
