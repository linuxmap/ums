#ifndef _h_innereventumssipadapter_h__
#define _h_innereventumssipadapter_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumssipadapter
{
#endif

	_ev_segment( innerumssipadapter )


 /***********************<<  ���Ӽ�ʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_ConnectToUms_Time )
 _ev_end

 /***********************<<  Э��ջ��ʼ����Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
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
