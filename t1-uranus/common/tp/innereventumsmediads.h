#ifndef _h_innereventumsmediads_h__
#define _h_innereventumsmediads_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsumsinnermediads
{
#endif

	_ev_segment( umsinnermediads )

/***********************<<  ����һ������ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_media_dscreate )
	_body( TUmsDsData,		1)
   _ev_end

/***********************<<  ����һ������ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_media_dsdestroy )
	_body( TUmsDsData,		1)
   _ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnermediads)
};
#endif




#endif // _h_innereventumsmediads_h__
