#ifndef _h_innereventumsserver_h__
#define _h_innereventumsserver_h__



#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsumslogin
{
#endif

	_ev_segment( umsinnerserver )

/***********************<<  CMS登录 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_SysCmsLoginInd )
	_body( TLogUser,		1)
   _ev_end


/***********************<<  umc退出 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_SysCmsLogoutInd )
	_body( TLogUser,		1)
   _ev_end


/***********************<<  更新预约会议计时器  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  ev_UpdateConfTimer )
   _ev_end

 /***********************<<获取授权数量消息>>********************	
 *[消息方向]		-->  ums
 *
 */
 _event(  ev_umsGetlicenseInfo_Req  )
_ev_end 


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnerserver)
};
#endif




#endif // _h_innereventumsserver_h__
