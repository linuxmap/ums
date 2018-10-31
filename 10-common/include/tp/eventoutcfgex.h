#ifndef _h_eventoutcfgex_h__
#define _h_eventoutcfgex_h__


#include "umseventcomm.h"
#include "tpcommonstruct.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumscfgex
{
#endif
	
	_ev_segment( outerumscfgex )


/***********************<<  umc配置密钥周期 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	umc  -->  ums	
 */
 _event(  ev_updatepwdtimer_cmd )
 _body(TPwdCycleInfo,	1)
 _ev_end
 
  /***********************<< umc配置密钥周期响应  >>********************	
  *[消息体]
  *TPwdCycleInfo   密钥周期信息
  *BOOL 配置是否成功
  *[消息方向]	  ums	-->  umc
  *
  */
  _event( ev_updatepwdtimer_Ind )
  _body( TPwdCycleInfo, 1 )
  _body( BOOL32, 1 )
  _ev_end


  /***********************<< 配置密钥周期nty  >>********************	
  *[消息体]
  *TPwdCycleInfo   密钥周期信息
  *[消息方向]	  ums	-->  umc
  *
  */
  _event( ev_updatepwdtimer_Nty )
  _body( TPwdCycleInfo, 1 )
  _ev_end

  /***********************<< 修改ntpd服务器配置 >>********************** 
 *[消息方向]
 *  umc	  -> ums
 */
  _event( ev_ums_ntpdcfg_cmd )
  _body( u32_ip, 1 )  //GK是否注册
  _ev_end

   /***********************<< ntpd服务器配置通知 >>********************** 
 *[消息方向]
 *  umc	  -> ums
 */
  _event( ev_ums_ntpdcfg_nty )
  _body( u32_ip, 1 )  //GK是否注册
  _ev_end

/***********************<<添加模板扩展信息>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event(  evtp_AddConfTemplateEx_req  )
	_body (TTemplateConfEx , 1  )
	_ev_end

/***********************<<添加模板扩展信息应答>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event(  evtp_AddConfTemplateEx_res  )
	_body ( TTemplateConfEx , 1  )
	_body ( EmAddTempConfExRes , 1  )
	_ev_end



/***********************<<模板会场添加信息通知>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event(  evtp_AddConfTemplateEx_Notify  )
	_body ( TTemplateConfEx , 1  )
	_ev_end
	
 	/***********************<<JD配置消息>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event(  ev_ums_Jdcfg_nty  )
	_body ( TJDInfo , 1  )
	_ev_end 
		/***********************<<下载日志请求消息>>********************	
 *[消息方向]	umc	-->  ums
 *
 */
 _event(  ev_ums_downloadlog_req  )
	_ev_end 

			/***********************<<下载日志请求回应>>********************	
 *[消息方向]	ums	-->  umc
 *
 */
 _event(  ev_ums_downloadlog_rsp  )
 _body ( BOOL32 , 1  )
	_ev_end 


#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumscfgex)
};
#endif




#endif // _h_eventoutquantum_h__
