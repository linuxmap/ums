#ifndef _h_eventoutcnsinside_h__
#define _h_eventoutcnsinside_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSH323REGEVENT
{
#endif 

  _ev_segment( outercnsinside  )

/***********************<< ���û����л᳡������ͼ�� >>********************** 
*[��Ϣ��]
+TTpYouAreSeeing �᳡������ͼ��
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_CnYouAreSeeing_Ind_V2 )
_body( TTpYouAreSeeing, 1 )
_ev_end

  
#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsinside )
};
#endif
#endif //TPP_EVENT_H
