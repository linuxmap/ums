#ifndef _h_innereventumsmediatrans_h__
#define _h_innereventumsmediatrans_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsmediatrans
{
#endif

	_ev_segment( innerumsmediatrans )


 /***********************<<  ���Ӽ�ʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_MediaConnectToUms_Time )
 _ev_end

 /***********************<<  Э��ջ��ʼ����Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_MediaTransInit_Ind )
 _body(BOOL32, 1)
 _ev_end


  /***********************<<  ��⵽�ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_IframeRcvCheck_Res )
 _body(u16, 1)	//port
 _ev_end

 
  /***********************<<  ��⵽�ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_IframeSndCheck_Res )
 _body(u16, 1)	//port
 _ev_end
   
   /***********************<<  ��⵽�ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
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
