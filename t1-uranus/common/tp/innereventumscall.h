#ifndef _h_innereventumscall_h__
#define _h_innereventumscall_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emumsinnercall
{
#endif

	_ev_segment( umsinnercall )

/***********************<<  授权数量通知 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsAccessNum_Notify )
_body ( u32  , 1  )	//数量
_ev_end		
		
/***********************<<  外设通知有接入注册 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsAdapterReg_Notify )
_body ( TEqpRes  , 1  )
_body ( TTPTransAddr  , 1  )		//协议栈监听结点	
_ev_end

/***********************<<  外设通知有接入取消注册 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsAdapterUnReg_Notify )
_body ( TEqpRes  , 1  )
_ev_end

/***********************<<  外设通知有混音器取消注册 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsAudioMixUnReg_Notify )
_body ( u8  , 1  )//EqpID
_ev_end

/***********************<<  外设通知有混音器注册 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsAudioMixReg_Notify )
_body ( TEqpRes  , 1  )
_ev_end

/***********************<<  外设通知有转发注册 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsMediaReg_Notify )
_body ( TEqpRes  , 1  )
_body(TIpmaskinfo, 1)
_ev_end

/***********************<<  外设通知有转发取消注册 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsMediaUnReg_Notify )
_body ( TEqpRes  , 1  )
_ev_end

/***********************<<  外设通知有合成掉线 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsVmpUnReg_Notify )
_ev_end

/***********************<<  外设通知mpc注册成功 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp	--> call
 *
 */
_event(  evtp_UmsMpcReged_Notify )
_body ( BOOL32  , 1  )	//是否启用MPC
_ev_end


/***********************<<  根据会议模板召开会议 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	service	--> call
 *
 */
_event(  evtp_UmsMakeConf )
_body ( TConfTemplateLocal  , 1  )
_ev_end



/***********************<<  呼叫到来 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> service
 *
 */
 _event(  evtp_UmsConfIncomingAck )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_body ( EmCnsCallReason  , 1  )
_body ( u16  , 1  )
_body ( TConfTemplateLocal  , 1  )
_body ( BOOL32  , 1  )
_ev_end

/***********************<<  会议结束 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> service
 *
 */
_event(  evtp_UmsConfDisConnect )
_body ( u16  , 1  )		//InstID, 也是会议号
_ev_end

/***********************<<  会议定时呼叫未入会会场 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> call
 *
 */
_event(  evtp_CallNode_time )
_ev_end


/***********************<<  定时向UI刷新结点信息  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> call
 *
 */
_event(  evtp_UpdateConfNode_time )
_ev_end


/***********************<<  轮询定时器  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> call
 *
 */
_event(  evtp_ExeTurnList_time )
_ev_end

/***********************<<  会议开始时的关键帧保护  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> call
 *
 */
_event(  evtp_KeyProtectOnStart_time )
_ev_end

/***********************<<  画面合成失败  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	Eqp	--> call
 *
 */
_event(  evtp_VmpToCall_NAck )
_ev_end

/***********************<<  画面合成外设上线  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	Eqp	--> call
 *
 */
_event(  evtp_UmsVmpReg_Notify )
_ev_end

/***********************<<  画面合成调整参数  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	Eqp	--> call
 *
 */
_event(  evtp_StartVmp_Req )
_body( u8, 1 )
_body(TTVmpStartParam, 1)
_ev_end

// 
_event( evtp_AdjustVmp_Req)
_body( u8, 1 )
_body(TUmsVidFormat, 1)
_ev_end

/***********************<<  码流适配掉线  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	Eqp	--> call
 *
 */
_event(  evtp_UmsBasUnReg_Notify )
_body( u8, 1 )//eqp id
_ev_end

/***********************<<  码流适配开启失败  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	Eqp	--> call
 *
 */
_event(  evtp_UmsBasStart_NAck )
_body( TTPBasNAck, 1 )//eqp id
_ev_end

/***********************<<  请求关键帧  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	Call --> eqp
 *
 */
_event(  evtp_UmsBasAskFrame_Req )
_body( u8 , 1 )//EqpID
_body( u16 , 1 )//chnIndx
_ev_end

/***********************<<  适配板挂载的转发板变更  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp --> Call
 *
 */
_event(  evtp_UmsBasChangeDsIP_Req )
_body( TBasMediaInfo , 1 )
_ev_end

/***********************<<  定时向适配板请求关键帧 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> call
 *
 */
_event(  evtp_AskFrameToBas_time )
_body(u16, 1)
_ev_end

/***********************<<  演示需求：合成所有G400 到某T300 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	startvmp命令	--> call
 *
 */
_event(  evtp_StartVmpToT300_Cmd )
_body(u32_ip, 1)//T300的IP
_body(u16, 1)//T300的接收端口
_body(u32, 1)//终端类型：MT，CNS，G400
_ev_end

/***********************<<  调试消息：模拟适配adjust >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	命令	--> call
 *
 */
_event(  evtp_BasTestAdjust_Cmd )
_body(u16, 1)
_ev_end

/***********************<<  音频适配 开启失败 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	命令	--> call
 *
 */
_event(  evtp_AudBasStartAdapter_NAck )
_body(TTPBasNAck, 1)
_ev_end

/***********************<<  音频适配 所在转发板掉线 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	命令	--> call
 *
 */
_event(  evtp_AudBasDsEqpDisConnect_Ntfy )
_body(TBasMediaInfo, 1)
_ev_end

/***********************<<  业务上线 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	命令	--> call
 *
 */
_event(  evtp_EqpService_Reg )
	_body(TServiceReg, 1)
_ev_end

/***********************<<  业务掉线 >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	命令	--> call
 *
 */
_event(  evtp_EqpService_UnReg )
	_body(TServiceBaseInfo, 1)
_ev_end

/***********************<<  timerMgr的定时器  >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> call
 *
 */
_event(  evtp_TimerMgrTimer_Tick )
_ev_end

// 会场结点状态定时检测定时器
_event(  evtp_EpNodeTimer_Check )
_ev_end



/***********************<<  更新临时会议名到server >>********************	 
 *[消息体]			 
 *   NULL
 *[消息方向]	call	--> server
 *
 */
_event(  evtp_Update_TempConf_To_Server )
    _body(u16, 1)
	_body(TTPAlias, 1)
_ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnercall)
};
#endif




#endif // _h_innereventumscall_h__
