#ifndef _h_innereventumshdu_h__
#define _h_innereventumshdu_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emumsinnerhdu
{
#endif

	_ev_segment( umsinnerhdu )

	//电视墙业务注册
	_event(  ev_hdu_reg_req ) 
		_body( THduRegInfo, 1 )
	_ev_end
		
	//reg ack
	_event(  ev_hdu_req_ack )
		_body( TUmsRSParam,    1 )
		_body( THduRegCfgAck,  1 )
	_ev_end
		
	//reg nack
	_event(  ev_hdu_req_nack )
	_ev_end

	//修改板子配置信息
	_event( ev_hdu_brd_modify)
		_body(TTPBrdPos,	1)
	_ev_end

	//升级板子
	_event( ev_hdu_update_req)
		_body(TTPBrdUpGrade, 1)
	_ev_end

	_event( ev_hdu_update_res)
		_body(THduUpdateRes, 1)
	_ev_end

	//升级板子结果
	_event( ev_hdu_update_nty)
		_body(TTPBrdUpGrade, 1)
		_body(EmUpdateHduRet, 1)
	_ev_end

	//修改通道信息
	_event( ev_hdu_chan_modify)
		_body(THduInfo,		1)
	_ev_end

	//删除通道
	_event( ev_hdu_chan_del)
		_body(TTPBrdPos,	1)
	_ev_end

	//重启
	_event( ev_hdu_reboot)
	_body(TTPBrdPos,	1)
	_ev_end

	//通知eqp配置信息
	_event( ev_hdu_cfg_info)
		_body(THduCfgInfo, 1)
	_ev_end

	_event( ev_hdu_disconnect)
	_ev_end

	//通知service板子注册状态
	_event( ev_hdu_brd_reg_res)
		_body(THduRegStatus, 1)
	_ev_end

	//更新板子上业务的注册状态
	_event( ev_hdu_service_reg_res)
		_body(THduRegStatus, 1)
		_body(u16, 1)
	_ev_end
		
	//修改通道信息
	_event( ev_hdu_notify_channel)
		_body(THduInfo, 1)
	_ev_end

	//删除电视墙信息
	_event( ev_hdu_del )
		_body(u8, 1)	//层号
		_body(u8, 1)	//槽号
	_ev_end

	//播放请求
	_event( ev_hdu_play_req)
		_body(THduPlayInfo, 1)
		_body(TAddTvMonitorAck, 1)
	_ev_end

	//播放请求应答
	_event ( ev_hdu_play_ack)
		_body(THduPlayInfo, 1)
	_ev_end

	//播放请求应答
	_event ( ev_hdu_play_nack)
		_body(THduPlayInfo, 1)
	_ev_end

	//停止播放请求
	_event( ev_hdu_stop_play_req)
		_body(THduPlayInfo, 1)
	_ev_end

	_event( ev_hdu_stop_play_ack)
		_body(THduPlayInfo, 1)
	_ev_end

	_event( ev_hdu_stop_play_nack)
		_body(THduPlayInfo, 1)
	_ev_end

	//更新通道状态
	_event( ev_hdu_update_chan_status)
		_body(THduChanStatus, 1)
	_ev_end

	//请求关键帧
	_event( ev_hdu_req_iframe)
		_body(THduIFrameInfo, 1)
	_ev_end

	//业务更新状态
	_event( ev_hdu_updata_status)
		_body(THduUpdateInfo, 1)
	_ev_end

	//设置音量
	_event(ev_hdu_set_vol)
		_body(THduVolInfo, 1)
	_ev_end

	_event(ev_hdu_set_vol_res)
		_body(THduVolInfo, 1)
		_body(EmTpHduSetVolRes, 1)
	_ev_end

	// 切换通道画面模式
	_event(ev_hdu_change_chan_mode)
	_body(THduChanModeInfo, 1)
	_ev_end
	
	_event(ev_hdu_change_chan_mode_res)
	_body(THduChanModeInfo, 1)
	_body(EmTpHduChangeChanModeRes, 1)
	_ev_end


	//nty qt media key
	_event( ev_hdu_media_key_nty)
	_body(THduPlayInfo, 1)
	_body(TTPQTMediaKeyInfo, 1)
	_ev_end	


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnerhdu)
};
#endif

#endif