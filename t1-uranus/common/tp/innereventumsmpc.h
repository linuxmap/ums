#ifndef _h_innereventumsmpc_h__
#define _h_innereventumsmpc_h__


#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsmpc
{
#endif

	_ev_segment( innerumsmpc )

 /***********************<<  ���Ӽ�ʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_MpcConnectToUms_Time )
 _ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerumsmpc)
};
#endif

#endif // _h_innereventumsmpc_h__
