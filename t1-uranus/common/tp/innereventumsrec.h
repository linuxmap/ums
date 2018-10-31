#ifndef __inner_event_umsrec_h_
#define __inner_event_umsrec_h_

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmumsinnerRec
{
#endif
	_ev_segment( umsinnerrec )
	
	//添加录播服务器配置信息
	_event ( ev_rec_add_cfg )
		_body( TRecorderCfg, 1)
	_ev_end

	//更新录播服务器配置信息
	_event( ev_rec_mdy_cfg)
		_body( TRecorderCfg, 1)	//老的配置信息
		_body( TRecorderCfg, 1)	//新的配置信息
	_ev_end

	//删除配置信息
	_event( ev_rec_del_cfg)
		_body( TRecorderCfg, 1)
	_ev_end

	//删除注册
	_event( ev_rec_disconnect)
	_ev_end

	//更新注册状态
	_event( ev_rec_update_reg)
		_body(TRecRegStatus, 1)
	_ev_end

	//更新录播使用的转发板
	_event( ev_rec_update_media)
		_body(TRecUseMedia, 1)
	_ev_end

	//注册
	_event(  ev_rec_reg_req ) 
		_body( TRecRegInfo, 1 )
	_ev_end

	//注册失败
	_event( ev_rec_req_nack)
	_ev_end

	//注册成功
	_event( ev_rec_req_ack)
		_body(TRecRegAck, 1)
	_ev_end

	//更新状态
	_event( ev_rec_status_nty)
		_body(TRecStatusNty, 1)
	_ev_end

	//请求文件列表
	_event( ev_rec_file_list_req)
		_body(u8, 1)	//设备ID
	_ev_end

	//请求文件列表失败
	_event( ev_rec_file_list_nack)
		_body(u8, 1)	//设备ID
	_ev_end

	//文件列表
	_event( ev_rec_file_list)
		_body(TRecFileList, 1)
	_ev_end

	//删除文件
	_event( ev_recDelFile)
		_body(TRecMdyFileInfo, 1)
	_ev_end

	//删除文件成功
	_event( ev_recDelFile_ack)
	_ev_end

	//删除文件失败
	_event( ev_recDelFile_nack)
		_body(EmMdyRecFileRes, 1)
	_ev_end

	//修改文件
	_event(ev_recMdyFile)
		_body(TRecMdyFileInfo, 1)	//
		_body(TRecMdyFileInfo, 1s)
	_ev_end

	//修改文件成功
	_event(ev_recMdyFile_ack)
	_ev_end

	//修改文件失败
	_event(ev_recMdyFile_nack)
		_body(EmMdyRecFileRes, 1)
	_ev_end

	//校验录像参数
	_event(ev_rec_check_param)
		_body(TStartRecInfo, 1)
	_ev_end

	//校验录像参数结果
	_event(ev_rec_check_param_rsp)
		_body(EmUseReccorderRes, 1)
		_body(TStartRecInfo, 1)
	_ev_end

	//录像请求
	_event( ev_rec_recorder_conf)
		_body(TStartRecInfo, 1)
	_ev_end

	//录像请求成功
	_event( ev_rec_recorder_conf_ack)
		_body(TRecConfResult, 1)
	_ev_end

	//录像请求失败
	_event( ev_rec_recorder_conf_nack)
		_body(TRecConfResult, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//创建录像交换
	_event( ev_recBulidRecTrans)
		_body(TRecConfTrans, 1)
	_ev_end

	//创建交换失败
	_event( ev_recBuildRecTrans_rsp)
		_body(BOOL32,	1)
		_body(TRecConfTrans, 1)
	_ev_end

	//拆除交换
	_event( ev_recDesRecTrans)
		_body(TRecConfTrans, 1)
	_ev_end

	//删除放像交换
	_event( ev_recDesPlayTrans)
	_ev_end

	//创建放像交换
	_event( ev_recBuildPlayTrans)
		_body(TPlayTrans, 1)
	_ev_end

	//更新放像交换
	_event( ev_recUpdatePlayTrans)
		_body(TPlayTrans, 1)
	_ev_end

	//创建放像交换成功
	_event( ev_recBuildPlayTrans_rsp)
		_body(BOOL32, 1)
		_body(TPlayTrans, 1)
	_ev_end


	//暂停会议录像
	_event( ev_recPauseConfRec)
		_body(TRecPauseInfo, 1)
	_ev_end

	//暂停会议成功
	_event( ev_recPauseConfRec_ack)
		_body(TRecPauseInfo, 1)
	_ev_end

	//暂停会议失败
	_event( ev_recPauseConfRec_nack)
		_body(TRecPauseInfo, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//继续录像
	_event(ev_recResumeConfRec)
		_body(TRecPauseInfo, 1)
	_ev_end

	_event(ev_recResumeConfRec_ack)
		_body(TRecPauseInfo, 1)
	_ev_end

	_event(ev_recResumeConfRec_nack)
		_body(TRecPauseInfo, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//停止录像
	_event( ev_recStopConfRec)
		_body(TRecPauseInfo, 1)
	_ev_end

	//停止录像成功
	_event( ev_recStopConfRec_ack)
		_body(TRecPauseInfo, 1)
	_ev_end

	//停止录像失败
	_event( ev_recStopConfRec_nack)
		_body(TRecPauseInfo, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//检查放像参数
	_event( ev_rec_check_play_param)
		_body(TConfPlayInfo, 1)
	_ev_end

	//检查放像参数应答
	_event( ev_rec_check_play_param_rsp)
		_body(EmUseReccorderRes, 1)
		_body(TConfPlayInfo, 1)
	_ev_end

	//放像请求
	_event( ev_recPlay)
		_body(TConfPlayInfo, 1)
	_ev_end

	//放像请求成功
	_event( ev_recPlay_ack)
		_body(TConfPlayAck, 1)
	_ev_end

	//放像请求失败
	_event( ev_recPlay_nack)
		_body(TConfPlayNack, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//暂停放像
	_event( ev_recPauseFilePlay)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recPauseFilePlay_ack)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recPauseFilePlay_nack)
		_body(TMdyFilePlay, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//继续放像
	_event( ev_recResumeFilePlay)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recResumeFilePlay_ack)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recResumeFilePlay_nack)
		_body(TMdyFilePlay, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//停止放像
	_event( ev_recStopFilePlay)
		_body(TMdyFilePlay, 1)
	_ev_end

	//停止放像成功
	_event( ev_recStopFilePlay_ack)
		_body(TMdyFilePlay, 1)
	_ev_end

	//停止放像失败
	_event( ev_recStopFilePlay_nack)
		_body(TMdyFilePlay, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//更新通道状态
	_event( ev_recUpdataChanStatus)
		_body(TRecChanStatus, 1)
	_ev_end

	//关键帧请求
	_event( ev_recIFrameReq)
		_body(TRecIFrameReq, 1)
	_ev_end

	//放像交换建立完成
	_event( ev_recSwitch_nty)
		_body(TMdyFilePlay, 1)
	_ev_end

	//更新通道进度
	_event( ev_recUpdateProg)
		_body(TRecChanProgInfo, 1)
	_ev_end

	//挂断终端录像
	_event( ev_rec_hungup_mt_rec)
		_body(THungupRecInfo,	1)
	_ev_end

	//调码流失败
	_event( ev_rec_getvid_failed)
		_body(TRecGetVidInfo, 1)
	_ev_end

	//挂断会议录像
	_event( ev_rec_hungup_conf_rec)
		_body(THungupRecInfo,	1)
	_ev_end

	//挂断会场放像
	_event( ev_rec_hungun_conf_play)
		_body(THungupRecInfo,	1)
	_ev_end

	//请求会场格式
	_event( ev_recMtFormat_req)
		_body(TLogUser, 1)
		_body(u16, 1)
	_ev_end

	//会场格式应答
	_event( ev_recMtFormat_rsp)
		_body(TLogUser, 1)
		_body(TTPRecMtFormat, 1)
	_ev_end

#ifndef _MakeTpEventDescription_
	_ev_segment_end(umsinnerrec)
};
#endif

#endif