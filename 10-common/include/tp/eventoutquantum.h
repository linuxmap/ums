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

 /***********************<< 量子加密配置设置请求  >>********************	
  *[消息体]
  *TTPQTEncryptInfo   量子加密信息
  *[消息方向]	  umc	-->  ums
  *
  */
  _event( ev_SetQTEncryptInfo_Cmd )
  _body( TTPQTEncryptInfo, 1 )
  _ev_end


  /***********************<< 量子加密配置设置响应  >>********************	
  *[消息体]
  *TTPQTEncryptInfo   量子加密信息
  *BOOL 升级服务器配置是否成功
  *[消息方向]	  ums	-->  umc
  *
  */
  _event( ev_SetQTEncryptInfo_Ind )
  _body( TTPQTEncryptInfo, 1 )
  _body( BOOL32, 1 )
  _ev_end


  /***********************<< 量子加密配置nty  >>********************	
  *[消息体]
  *TTPQTEncryptInfo   量子加密信息
  *BOOL 升级服务器配置是否成功
  *[消息方向]	  ums	-->  umc
  *
  */
  _event( ev_QTMTInfo_Nty )
  _body( TTPQTEncryptInfo, 1 )
  _ev_end




/***********************<< 量子加密配置设置通知  >>********************	
  *[消息体]
  *TTPQTEncryptInfo   量子加密信息
  *[消息方向]	  ums	-->  umsadapter
  *
  */
  _event( ev_QTEncryptInfo_Nty )
  _body(TUmsHandle, 1)
  _body( TTPQTEncryptInfo, 1 )
  _body(EmTpConfProtocol, 1)
  _ev_end


/***********************<< 量子查询会议名***************	
  *[消息体]
  *TTPQTQueryInfo   
  *[消息方向]
  *
  */
  _event(evtp_QtQueryAlias_req)
  _body(TUmsHandle, 1)
  _body(TTPQTQueryData, 1)
  _ev_end


/***********************<< 量子查询会议名回复***************	
  *[消息体]  
  *[消息方向]
  *
  */
  _event(evtp_QtQueryAlias_rsp)
  _body(TUmsHandle, 1)
  _body(TTPQTQueryData, 1)
  _body(EmQueryAliasRes, 1)
  _body(EmTPConfEncFrequency, 1)
 _ev_end


 /***********************<< 会议码流秘钥通知  >>********************
 */
 _event( evtp_MediaKey_Nty )
 _body ( TUmsHandle  , 1  )
 _body ( TTPMediaKeyInfo, 1)
 _ev_end



 /***********************<< 会议码流秘钥失败通知  >>********************
 */
 _event(evtp_QtMediaFail_Cmd)
 _body(TUmsHandle, 1)
 _body(TTPQtMediaKeyFail, 1)
 _ev_end



 /***********************<< 通知协商秘钥的会场  >>********************
 */
 _event( evtp_MediaDstMT_Nty )
 _body ( TUmsHandle  , 1  )
 _body ( s8, TP_MAX_ALIAS_LEN+1)
 _ev_end


 /***********************<< 告知qt 是否为下级会场 >>********************
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
