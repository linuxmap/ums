#ifndef _h_innereventumsaudbas_h__
#define _h_innereventumsaudbas_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsaudbas
{
#endif

	_ev_segment( innerumsaudbas )

 /***********************<<  音频适配器注册 >>********************	
 *[消息体]			 
 *   TTPBasReg
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasEqpReg_Req )
 _body( TTPBasReg, 1 )
 _ev_end

  /***********************<<  音频适配器注册 ACK >>********************	
 *[消息体]			 
 *   TTPBasRegAck
 *[消息方向]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasEqpReg_Ack )
 _body( TTPBasRegAck, 1 )
 _body( TUmsRSParam, 1 )
 _ev_end

   /***********************<<  音频适配器注册 NACK >>********************	
 *[消息体]			 
 *   
 *[消息方向]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasEqpReg_NAck )
 _ev_end


  /***********************<<  音频适配器状态通知 >>********************	
 *[消息体]			 
 *   TTPBasStatNtfy
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasEqpStat_Ntfy )
 _body( TTPBasStatNtfy, 1 )
 _ev_end


  /***********************<<  音频适配器 通道 状态通知 >>********************	
 *[消息体]			 
 *   TTPBasStatNtfy
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasChnlStat_Ntfy )
 _body( TTPBasStatNtfy, 1 )
 _ev_end

   /***********************<<  音频适配器 开启适配 >>********************	
 *[消息体]			 
 *   TStartAudAdapter
 *[消息方向]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasStartAdapter_Req )
 _body( TStartAudAdapter, 1 )
 _ev_end

   /***********************<<  音频适配器 通道 开启适配ACK >>********************	
 *[消息体]			 
 *   TTPBasRetInfo
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStartAdapter_Ack )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  音频适配器 通道 开启适配NACK >>********************	
 *[消息体]			 
 *   TTPBasStatNtfy
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStartAdapter_NAck )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  音频适配器 停止适配 >>********************	
 *[消息体]			 
 *   TStartAudAdapter
 *[消息方向]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasStopAdapter_Req )
 _body( u8, 1 )
 _ev_end

   /***********************<<  音频适配器 通道 停止适配ACK >>********************	
 *[消息体]			 
 *   TTPBasRetInfo
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStopAdapter_Ack )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  音频适配器 通道 停止适配NACK >>********************	
 *[消息体]			 
 *   TTPBasStatNtfy
 *[消息方向]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStopAdapter_NAck )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  音频适配器 调整适配 >>********************	
 *[消息体]			 
 *   TStartAudAdapter
 *[消息方向]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasChangeAdapter_Req )
 _body( TStartAudAdapter, 1 )
 _ev_end

   /***********************<<  音频适配通道 同步通道设置 >>********************	
 *[消息体]			 
 *   TAudBasSyncChnl
 *[消息方向]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasSetSync_Req )
 _body( TAudBasSyncChnl, 1 )
 _ev_end



 /***********************<< 通知外设码流秘钥 量子 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_AudBas_set_mediakey_ntfy )
 _body( u8, 1 )//eqpID
 _body( u16, 1 )//ChnlID
 _body( TTPQTMediaKeyInfo	, 1)
 _ev_end
 

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerumsaudbas)
};
#endif


#endif // _h_innereventumsaudiomix_h__
