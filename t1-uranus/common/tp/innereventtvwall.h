#ifndef _h_innereventtvwall_h__
#define _h_innereventtvwall_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmUmsumsinnertvwall
{
#endif

	_ev_segment( umsinnertvwall )

/***********************<<  添加一个监控 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	server	-->  call
 *
 */_event(  ev_AddTvMonitor_req )
	_body( TAddTvMonitor, 1)
	_body( BOOL32, 1 ) 
	_body( BOOL32, 1 ) 
   _ev_end

/***********************<<  添加一个监控 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	server	-->  call
 *
 */_event(  ev_AddTvMonitor_ack )
	_body( TAddTvMonitorAck,		1)
	_body( BOOL32, 1)
   _ev_end


 /***********************<<  删除一个监控 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	server	<--  call
 *
 */_event(  ev_DelTvMonitor_req )
	_body( TTPHduPlayReq	, 1)
   _ev_end

 /***********************<<  删除一个监控 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	server	-->  call
 *
 */_event(  ev_DelTvMonitor_ack )
	_body( TTPHduPlayReq	, 1)
   _ev_end



 /***********************<<  重启一个监控 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	server	-->  call
 *
 */_event(  ev_RestartTvMonitor_cmd )
	_body( TAddTvMonitor	, 1)
   _ev_end


 /***********************<<  挂断 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	call	-->  server
 *
 */_event(  ev_HungUpHdu_cmd )
	_body( u16	, 1)
	_body( u8, 1)
	_body(EmCnsCallReason, 1)
   _ev_end


 /***********************<<  挂断会议 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	call	-->  server
 *
 */_event(  ev_HungUpConf_Hdu_cmd )
	_body( u16	, 1)
   _ev_end



 /***********************<<  删除一个监控 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	server	-->  call
 *
 */_event(  ev_TvMonitor_AskKey )
	_body( TTPHduPlayReq	, 1)
   _ev_end


 /***********************<<  Hdu请求电视墙信息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	call	-->  server
 *
 */
_event(  ev_HduPlanInfo_Req )
_body( u16	, 1)
_body( u16	, 1)
_ev_end


 /***********************<<  nty qt media key >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	call	-->  server
 *
 */
_event(  ev_TvMonitor_MediaKey_Nty )
_body( u16, 1)
_body( u8, 1)
_body( TTPQTMediaKeyInfo	, 1)
_ev_end



#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnertvwall)
};
#endif




#endif // _h_innereventtvwall_h__
