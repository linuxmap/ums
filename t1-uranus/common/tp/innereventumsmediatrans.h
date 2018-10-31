#ifndef _h_innereventumsmediatrans_h__
#define _h_innereventumsmediatrans_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsmediatrans
{
#endif

	_ev_segment( innerumsmediatrans )


 /***********************<<  连接计时器 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_MediaConnectToUms_Time )
 _ev_end

 /***********************<<  协议栈初始化消息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_MediaTransInit_Ind )
 _body(BOOL32, 1)
 _ev_end


  /***********************<<  检测到关键帧 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_IframeRcvCheck_Res )
 _body(u16, 1)	//port
 _ev_end

 
  /***********************<<  检测到关键帧 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_IframeSndCheck_Res )
 _body(u16, 1)	//port
 _ev_end
   
   /***********************<<  检测到关键帧 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_IframeSndDisCheck_Res )
 _body(u16, 1)	//port
 _body(u16, 1)	//port
 _ev_end
#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerumsmediatrans)
};
#endif


#endif // _h_innereventumsmediatrans_h__
