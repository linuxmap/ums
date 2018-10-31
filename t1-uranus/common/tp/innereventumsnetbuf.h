#ifndef _h_innereventumsnetbuf_h__
#define _h_innereventumsnetbuf_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsnetbuf
{
#endif

	_ev_segment( innerumsnetbuf )


 /***********************<<  连接计时器 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_NetbufConnectToUms_Time )
 _ev_end

 /***********************<<  初始化消息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_NetbufTransInit_Ind )
 _body(BOOL32, 1)
 _ev_end


   
#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerumsnetbuf)
};
#endif

#endif // _h_innereventumsnetbuf_h__
