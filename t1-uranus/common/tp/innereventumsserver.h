#ifndef _h_innereventumsserver_h__
#define _h_innereventumsserver_h__



#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsumslogin
{
#endif

	_ev_segment( umsinnerserver )

/***********************<<  CMS��¼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_SysCmsLoginInd )
	_body( TLogUser,		1)
   _ev_end


/***********************<<  umc�˳� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_SysCmsLogoutInd )
	_body( TLogUser,		1)
   _ev_end


/***********************<<  ����ԤԼ�����ʱ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_UpdateConfTimer )
   _ev_end

 /***********************<<��ȡ��Ȩ������Ϣ>>********************	
 *[��Ϣ����]		-->  ums
 *
 */
 _event(  ev_umsGetlicenseInfo_Req  )
_ev_end 


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnerserver)
};
#endif




#endif // _h_innereventumsserver_h__
