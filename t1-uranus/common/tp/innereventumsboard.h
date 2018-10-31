#ifndef _h_innereventumsboard_h__
#define _h_innereventumsboard_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emumsinnerboard
{
#endif
	_ev_segment( umsinnerboard )	

	_event( ev_board_cfg_info )        //service获取到单板配置信息通知eqp
	_body( TTPBrdInfo, 1 )  //单板配置信息
	_body( BOOL32, 1 )      //单板是否配置
	_ev_end

	/***********************<<更新单板注册结果>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_reg_result )      //更新单板注册结果通知handleboardservice
	_body( TBrdStateInfo, 1 )
	_ev_end

	/***********************<<更新单板业务注册结果>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_mode_reg_result ) //更新单板业务注册结果通知handleboardservice
	_body( TBrdStateInfo, 1 )		//注册结果
	_ev_end

	/***********************<<单板断链通知>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_disc_nty )
	_body( TBrdStateInfo, 1 )
	_ev_end

	/***********************<<单板删除通知>>********************	
	*[消息方向]	service  -->  eqp
	*
	*/
	_event( ev_board_del_nty )
	_body( u16, 1 )			//对应位置数组索引
	_ev_end

	/***********************<<单板修改通知>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_modify_nty )
	_body( TTPBrdCfg, 1 )
	_ev_end

	/***********************<<单板模式删除通知>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_mode_del_nty )
	_body( u16, 1 ) //板子索引
	_body( u16, 1 ) //模式索引
	_ev_end

	/***********************<<单板模式修改通知>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_mode_modify_nty )
	_body( TTPBrdMdlInfo, 1 )
	_ev_end

	/***********************<<单板使用情况>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_used_nty )
	_body( TTPBrdUsedInfo, 1 )
	_ev_end

	/***********************<<单板重启>>********************	
	*[消息方向]	service  -->  eqp
	*
	*/
	_event( ev_board_reboot_req )
	_body( u16, 1 )
	_ev_end

	/***********************<<单板升级>>********************	
	*[消息方向]	service  -->  eqp
	*
	*/
	_event( ev_board_upgrade_req )
	_body( TBrdUpInfo, 1 )
	_ev_end
	/***********************<<单板升级结果>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_upgrade_res )
	_body( u16, 1) //板子索引
	_body( BOOL32, 1 )
	_ev_end

	/***********************<<单板版本请求>>********************	
	*[消息方向]	service  -->  eqp
	*
	*/
	_event( ev_board_getversion_req )
	_ev_end

	/***********************<<单板版本响应>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_getversion_ack )
	_body(TBrdVersion, 1)
	_ev_end

	/***********************<<混音、画面合成、适配占用情况请求>>********************	
	*[消息方向]	service  -->  eqp
	*
	*/
	_event( ev_board_used_req )
	_body( EMEqpType, 1 )		//外设类型 表示是混音或画面合成或适配
	_ev_end

	/***********************<<单板升级结果响应>>********************	
	*[消息方向]	umsboard      -->  EqpApp
	*
	*/
	_event(  ev_TPUpdate_Task_Return )
	_body( BOOL32, 1 )
	_ev_end

	/***********************<<单板Telnet Ftp 开关请求>>********************	
	*[消息方向]	service  -->  eqp
	*
	*/
	_event( ev_board_switchtelnetftp_req )
	_body( TBrdSwitchInfo, 1 )
	_ev_end
	/***********************<<单板Telnet Ftp 开关请求>>********************	
	*[消息方向]	eqp  -->  service
	*
	*/
	_event( ev_board_switchtelnetftpe_res )
	_body( TBrdSwitchInfo, 1 )
    _body(EmBoardSwitchRes,1)
	_ev_end


#ifndef _MakeTpEventDescription_
	_ev_segment_end( umsinnerboard )
};
#endif

#endif