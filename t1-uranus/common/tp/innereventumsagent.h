#ifndef _h_innereventumsagent_h__
#define _h_innereventumsagent_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emumsinneragent
{
#endif
	_ev_segment( umsinneragent )

 /***********************<< ���ϵͳ��Ϣ  >>*******************/
 _event( ev_check_system )
 _ev_end

 /***********************<< CPU �����  >>*******************/
 _event( ev_check_cpu_ind)
	_body( u32,	1 ) //CPU ���аٷֱ�
 _ev_end
		
		
#ifndef _MakeTpEventDescription_
		_ev_segment_end(umsinneragent)
};
#endif

#endif