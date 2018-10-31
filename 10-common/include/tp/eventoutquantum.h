#ifndef _h_eventoutquantum_h__
#define _h_eventoutquantum_h__


#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumsquantum
{
#endif
	
	_ev_segment( outerumsquantum )


_event(  evtp_QuantumEvent_Begin ) 
_ev_end

 /***********************<< ���Ӽ���������������  >>********************	
  *[��Ϣ��]
  *TTPQTEncryptInfo   ���Ӽ�����Ϣ
  *[��Ϣ����]	  umc	-->  ums
  *
  */
  _event( ev_SetQTEncryptInfo_Cmd )
  _body( TTPQTEncryptInfo, 1 )
  _ev_end


  /***********************<< ���Ӽ�������������Ӧ  >>********************	
  *[��Ϣ��]
  *TTPQTEncryptInfo   ���Ӽ�����Ϣ
  *BOOL ���������������Ƿ�ɹ�
  *[��Ϣ����]	  ums	-->  umc
  *
  */
  _event( ev_SetQTEncryptInfo_Ind )
  _body( TTPQTEncryptInfo, 1 )
  _body( BOOL32, 1 )
  _ev_end


  /***********************<< ���Ӽ�������nty  >>********************	
  *[��Ϣ��]
  *TTPQTEncryptInfo   ���Ӽ�����Ϣ
  *BOOL ���������������Ƿ�ɹ�
  *[��Ϣ����]	  ums	-->  umc
  *
  */
  _event( ev_QTMTInfo_Nty )
  _body( TTPQTEncryptInfo, 1 )
  _ev_end




/***********************<< ���Ӽ�����������֪ͨ  >>********************	
  *[��Ϣ��]
  *TTPQTEncryptInfo   ���Ӽ�����Ϣ
  *[��Ϣ����]	  ums	-->  umsadapter
  *
  */
  _event( ev_QTEncryptInfo_Nty )
  _body(TUmsHandle, 1)
  _body( TTPQTEncryptInfo, 1 )
  _body(EmTpConfProtocol, 1)
  _ev_end


/***********************<< ���Ӳ�ѯ������***************	
  *[��Ϣ��]
  *TTPQTQueryInfo   
  *[��Ϣ����]
  *
  */
  _event(evtp_QtQueryAlias_req)
  _body(TUmsHandle, 1)
  _body(TTPQTQueryData, 1)
  _ev_end


/***********************<< ���Ӳ�ѯ�������ظ�***************	
  *[��Ϣ��]  
  *[��Ϣ����]
  *
  */
  _event(evtp_QtQueryAlias_rsp)
  _body(TUmsHandle, 1)
  _body(TTPQTQueryData, 1)
  _body(EmQueryAliasRes, 1)
  _body(EmTPConfEncFrequency, 1)
 _ev_end


 /***********************<< ����������Կ֪ͨ  >>********************
 */
 _event( evtp_MediaKey_Nty )
 _body ( TUmsHandle  , 1  )
 _body ( TTPMediaKeyInfo, 1)
 _ev_end



 /***********************<< ����������Կʧ��֪ͨ  >>********************
 */
 _event(evtp_QtMediaFail_Cmd)
 _body(TUmsHandle, 1)
 _body(TTPQtMediaKeyFail, 1)
 _ev_end



 /***********************<< ֪ͨЭ����Կ�Ļ᳡  >>********************
 */
 _event( evtp_MediaDstMT_Nty )
 _body ( TUmsHandle  , 1  )
 _body ( s8, TP_MAX_ALIAS_LEN+1)
 _ev_end


 /***********************<< ��֪qt �Ƿ�Ϊ�¼��᳡ >>********************
 */
_event(evtp_QtSetConfInfo_Cmd)
_body(TUmsHandle, 1)
_body(BOOL32, 1)
_body(BOOL32, 1)
_ev_end

 
_event(  evtp_QuantumEvent_End ) 
_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumsquantum)
};
#endif




#endif // _h_eventoutquantum_h__
