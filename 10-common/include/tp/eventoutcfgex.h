#ifndef _h_eventoutcfgex_h__
#define _h_eventoutcfgex_h__


#include "umseventcomm.h"
#include "tpcommonstruct.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumscfgex
{
#endif
	
	_ev_segment( outerumscfgex )


/***********************<<  umc������Կ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	umc  -->  ums	
 */
 _event(  ev_updatepwdtimer_cmd )
 _body(TPwdCycleInfo,	1)
 _ev_end
 
  /***********************<< umc������Կ������Ӧ  >>********************	
  *[��Ϣ��]
  *TPwdCycleInfo   ��Կ������Ϣ
  *BOOL �����Ƿ�ɹ�
  *[��Ϣ����]	  ums	-->  umc
  *
  */
  _event( ev_updatepwdtimer_Ind )
  _body( TPwdCycleInfo, 1 )
  _body( BOOL32, 1 )
  _ev_end


  /***********************<< ������Կ����nty  >>********************	
  *[��Ϣ��]
  *TPwdCycleInfo   ��Կ������Ϣ
  *[��Ϣ����]	  ums	-->  umc
  *
  */
  _event( ev_updatepwdtimer_Nty )
  _body( TPwdCycleInfo, 1 )
  _ev_end

  /***********************<< �޸�ntpd���������� >>********************** 
 *[��Ϣ����]
 *  umc	  -> ums
 */
  _event( ev_ums_ntpdcfg_cmd )
  _body( u32_ip, 1 )  //GK�Ƿ�ע��
  _ev_end

   /***********************<< ntpd����������֪ͨ >>********************** 
 *[��Ϣ����]
 *  umc	  -> ums
 */
  _event( ev_ums_ntpdcfg_nty )
  _body( u32_ip, 1 )  //GK�Ƿ�ע��
  _ev_end

/***********************<<���ģ����չ��Ϣ>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event(  evtp_AddConfTemplateEx_req  )
	_body (TTemplateConfEx , 1  )
	_ev_end

/***********************<<���ģ����չ��ϢӦ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event(  evtp_AddConfTemplateEx_res  )
	_body ( TTemplateConfEx , 1  )
	_body ( EmAddTempConfExRes , 1  )
	_ev_end



/***********************<<ģ��᳡�����Ϣ֪ͨ>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event(  evtp_AddConfTemplateEx_Notify  )
	_body ( TTemplateConfEx , 1  )
	_ev_end
	
 	/***********************<<JD������Ϣ>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event(  ev_ums_Jdcfg_nty  )
	_body ( TJDInfo , 1  )
	_ev_end 
		/***********************<<������־������Ϣ>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event(  ev_ums_downloadlog_req  )
	_ev_end 

			/***********************<<������־�����Ӧ>>********************	
 *[��Ϣ����]	ums	-->  umc
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
