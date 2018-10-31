#ifndef _h_eventoutumsmediatrans_h__
#define _h_eventoutumsmediatrans_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpoutermediatrans
{
#endif
	
	_ev_segment( tpumswithmediatrans )
		
/***********************<<  ����һ������ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_media_ds_create )
	_body( u16,		1)	//Conf ID
	_body( TUmsDsData,		1)
   _ev_end

/***********************<<  ɾ��һ������ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_media_ds_remove )
	_body( u16,		1)	//Conf ID
	_body( TUmsDsData,		1)
   _ev_end

/***********************<<  ��ӹؼ�֡���  ��������Դ���>>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_iframe_bySrc )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameBySrc,	1)
   _ev_end

/***********************<<  ��ӹؼ�֡���  ��������Դ���>>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_iframe_bySrc_Ind )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameBySrc,	1)
  _ev_end

  /***********************<<  ��ӹؼ�֡���  ��������>>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_iframe_TwoRcvPort )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameTwoRcvPort,	1)
   _ev_end

   /***********************<<  ��ӹؼ�֡���  ��Ŀ�ĵİ����뾭��Դ���>>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_iframe_SndBySrc )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameSndBySrc,	1)
  _ev_end

  /***********************<<  ��ӹؼ�֡���  ��������>>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_iframe_TwoRcvPort_Ind )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameTwoRcvPort,	1)
   _ev_end

   /***********************<<  ɾ���ؼ�֡��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_del_iframe )
	_body( TTPTransAddr,	1)	//check port
   _ev_end


 /***********************<<  ����һ��nb >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */
 _event(  ev_media_nb_create )
_body( TConfEpID,		1)
_body( TUmsRSParam,		1)
_body( TUmsNetBuf,		1)
_ev_end

   
/***********************<<  ɾ��һ��nb >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_media_nb_remove )
	_body( TConfEpID,		1)
	_body( TUmsNetBuf,		1)
   _ev_end

/***********************<<  ɾ����������н��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  ev_media_clear_conf )
	_body( u16,		1)
   _ev_end

    /***********************<<  ��ӹؼ�֡��� ��b4������  ��Ŀ�ĵİ����뾭��Դ���>>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_iframe_SndDis )
	_body( TCheckIFrameBase,	1)
	_body( TIFrameSndDis,	1)
	_body( TCheckIFrameBase,	1)
	_body( TIFrameSndDis,	1)
  _ev_end
    	/***********************<<����ssh ��������>>********************	
	*[��Ϣ����]	service  -->  eqp
	*
	*/
	_event( ev_media_switchtelnetftp_req )
	_body( TPBoardSwitch, 1 )
	_ev_end
  /***********************<<  ��ӹؼ�֡���  ��b4������  ��������Դ���>>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  ev_media_ds_iframe_byDis_Ind )
	_body( TCheckIFrameBase,	1)
	_body( u16,	1)
  _ev_end


#ifndef _MakeTpEventDescription_
_ev_segment_end(tpumswithmediatrans)
};
#endif


#endif // _h_eventoutumsmediatrans_h__
