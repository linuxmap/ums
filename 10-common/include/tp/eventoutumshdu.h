#ifndef _eventoutumshdu_h_
#define _eventoutumshdu_h_

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsHduEvent
{
#endif

	_ev_segment( outerumshdu )

/***********************<<  hduע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Hduserver	--> UI
 *
 */_event(  ev_SysHduEpReg )
	_body( TTPHduRegInfo,		1)
   _ev_end

   /***********************<<  hdu���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	hduserver	--> UI and ums
 *
 */_event(  ev_SysHduEpDrop )
   _body( u32,		1)//channelhandle
   _ev_end
   /***********************<<  ���󲥷�  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	UI	--> hduserver
 *
 */_event(  ev_SysHduPlayReq )
	_body( TTPHduPlayReq,		1) 
   _ev_end

      /***********************<<  ���󲥷Ż�Ӧ  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	hduserver	--> UI
 *
 */_event(  ev_SysHduPlayAck )
	_body( TTPHduPlayReq,		1)//channelhandle
   _ev_end


         /***********************<<  ���󲥷Ż�Ӧ  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	hduserver	--> UI
 *
 */_event(  ev_SysHduPlayNAck )
	_body( TTPHduPlayReq,      1)//channelhandle
	_body( EmTpHduPlayNackReason,     1)
	_ev_end


/***********************<<  stopplay  >>********************	
 *[��Ϣ��]			 ɾ������ǽ�ļ��
 *   NULL
 *[��Ϣ����]	UI	--> hduserver
 *
 */_event(  ev_SysHduStopPlay )
	_body( TTPHduPlayReq,				  1)
	_ev_end

			         /***********************<<  stopplayack  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	hduserver  -->  UI	
 *
 */_event(  ev_SysHduStopPlayAck )
	_body( TTPHduPlayReq,				  1)
	_ev_end

				         /***********************<<  stopplaynack  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	hduserver  -->  UI	
 *
 */_event(  ev_SysHduStopPlayNAck )
	_body( TTPHduPlayReq,				  1)
	_ev_end

/************************<<֪ͨ����᳡�Ƿ�������>>*************************
*[��Ϣ��]			 
*   NULL
*[��Ϣ����]	hduserver  -->  UI	
*
*/_event(  ev_SysHduCallIsValid )
  _body( TTPHduPlayReq,      1)
  _body( BOOL,				  1)
  _ev_end






#ifndef _MakeTpEventDescription_
   _ev_segment_end(outerumshdu)
};
#endif





#endif //_eventoutumshdu_h_