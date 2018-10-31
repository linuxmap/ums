#ifndef _h_eventoutmpu2tp_h_
#define _h_eventoutmpu2tp_h_

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventMpu2tpMsg
{
#endif
	_ev_segment( outermpu2tp )
 
	//vmp 注册
	_event(ev_mpu2tp_regist)
		_body(TVmpRegistInfo, 1)
	_ev_end

	//vmp 注册成功
	_event(ev_mpu2tp_regist_ack)
		_body(TVmpRegAck, 1)
		_body(TVmpTimeSpan, 1)
		_body(u32, 1)
	_ev_end

	//vmp 注册失败
	_event(ev_mpu2tp_regist_nack)
	_ev_end
 
	//开启合成
	_event(ev_mpu2tp_start_req)
		_body(TVmpStartParam, 1)
	_ev_end
	//结果
	_event(ev_mpu2tp_start_res)
		_body(TVmpStartRes, 1)
	_ev_end
 
	//修改合成参数
	_event(ev_mpu2tp_mdy_param)
		_body(TVmpMdyInfo, 1)
	_ev_end

	//修改合成参数结果
	_event(ev_npu2tp_mdy_param_res)
		_body(TVmpMdyRes, 1)
	_ev_end
 
	//停止画面合成
	_event(ev_mpu2tp_stop_req)
	_ev_end

	//停止画面合成结果
	_event(ev_mpu2tp_stop_res)
		_body(TVmpStopRes, 1)
	_ev_end
 
	 //添加通道
	 _event(ev_mpu2tp_addchan_req)
		_body(TVmpChanInfo, 1)
	 _ev_end

	 //添加通道结果
	_event(ev_mpu2tp_addchan_res)
		_body(TVmpChanRes, 1)
	_ev_end

	//删除通道
	_event(ev_mpu2tp_delchan_req)
		_body(TVmpChanInfo, 1)
	_ev_end

	//删除通道
	_event(ev_mpu2tp_delchan_res)
		_body(TVmpChanRes, 1)
	_ev_end

	//检测合成成员是否需要关键帧
	_event(ev_mpu2tp_NeedFrame_Timer)
	_ev_end

	//检测合成成员是否需要关键帧
	_event(ev_mpu2tp_AskFrame_Req)
	_body(TVmpAskFrame, 1)
	_ev_end

	//更改合成器IP
	_event(ev_mpu2tp_ChangeUmsIP_Req)
	_body(TVmpRegAck, 1)
	_ev_end

	//更新当前发言通道的标识
	_event(ev_mpu2tp_SpeakerFlag_Ntfy)
	_body(TVmpSpeakerFlag, 1)
	_ev_end

	//更新当前发言通道的标识 400ms后通知变成原来颜色
	_event(ev_mpu2tp_UpdateFlag400_Timer)
	_ev_end

	//更新当前发言通道的标识 200ms后通知变成发言人颜色
	_event(ev_mpu2tp_UpdateFlag200_Timer)
	_ev_end


	// qt mediakey
	_event(ev_mpu2tp_SetMediaKey_Req)
	_body(TTPMediaKeyInfo, 1)
	_ev_end

#ifndef _MakeTpEventDescription_
	_ev_segment_end( outermpu2tp )
};
#endif

#endif