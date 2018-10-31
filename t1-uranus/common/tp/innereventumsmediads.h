#ifndef _h_innereventumsmediads_h__
#define _h_innereventumsmediads_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsumsinnermediads
{
#endif

	_ev_segment( umsinnermediads )

/***********************<<  创建一个交换 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_media_dscreate )
	_body( TUmsDsData,		1)
   _ev_end

/***********************<<  销毁一个交换 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_media_dsdestroy )
	_body( TUmsDsData,		1)
   _ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnermediads)
};
#endif




#endif // _h_innereventumsmediads_h__
