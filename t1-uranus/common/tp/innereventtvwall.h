#ifndef _h_innereventtvwall_h__
#define _h_innereventtvwall_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmUmsumsinnertvwall
{
#endif

	_ev_segment( umsinnertvwall )

/***********************<<  ���һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	server	-->  call
 *
 */_event(  ev_AddTvMonitor_req )
	_body( TAddTvMonitor, 1)
	_body( BOOL32, 1 ) 
	_body( BOOL32, 1 ) 
   _ev_end

/***********************<<  ���һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	server	-->  call
 *
 */_event(  ev_AddTvMonitor_ack )
	_body( TAddTvMonitorAck,		1)
	_body( BOOL32, 1)
   _ev_end


 /***********************<<  ɾ��һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	server	<--  call
 *
 */_event(  ev_DelTvMonitor_req )
	_body( TTPHduPlayReq	, 1)
   _ev_end

 /***********************<<  ɾ��һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	server	-->  call
 *
 */_event(  ev_DelTvMonitor_ack )
	_body( TTPHduPlayReq	, 1)
   _ev_end



 /***********************<<  ����һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	server	-->  call
 *
 */_event(  ev_RestartTvMonitor_cmd )
	_body( TAddTvMonitor	, 1)
   _ev_end


 /***********************<<  �Ҷ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	-->  server
 *
 */_event(  ev_HungUpHdu_cmd )
	_body( u16	, 1)
	_body( u8, 1)
	_body(EmCnsCallReason, 1)
   _ev_end


 /***********************<<  �Ҷϻ��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	-->  server
 *
 */_event(  ev_HungUpConf_Hdu_cmd )
	_body( u16	, 1)
   _ev_end



 /***********************<<  ɾ��һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	server	-->  call
 *
 */_event(  ev_TvMonitor_AskKey )
	_body( TTPHduPlayReq	, 1)
   _ev_end


 /***********************<<  Hdu�������ǽ��Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	-->  server
 *
 */
_event(  ev_HduPlanInfo_Req )
_body( u16	, 1)
_body( u16	, 1)
_ev_end


 /***********************<<  nty qt media key >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	-->  server
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
