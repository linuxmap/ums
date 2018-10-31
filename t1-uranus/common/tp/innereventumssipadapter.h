#ifndef _h_innereventumssipadapter_h__
#define _h_innereventumssipadapter_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumssipadapter
{
#endif

	_ev_segment( innerumssipadapter )


 /***********************<<  连接计时器 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_ConnectToUms_Time )
 _ev_end

 /***********************<<  协议栈初始化消息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_SipAdapterInit_Ind )
 _body(BOOL32, 1)
 _ev_end



   
#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerumssipadapter)
};
#endif


#endif // _h_innereventumssipadapter_h__
