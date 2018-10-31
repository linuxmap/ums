#ifndef _h_eventoutumsreg_h__
#define _h_eventoutumsreg_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumsreg
{
#endif

	_ev_segment( outerumsreg )

/***********************<<   >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *CMS����UMS��ע����Ϣ
 */
_event(  ev_umsreg_cmd )
_body(TTPSipRegistrarCfg,	1)
_ev_end


/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *UMS��֪CMS������Ϣ
 */
_event(  ev_umsreg_notify )
_body(TTPSipRegistrarCfg,	1)
_ev_end


/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *UMS��֪CMSע��ɹ����
 */
_event(  ev_umsRegResult_notify )
_body(TUCSipRegResult,	1)
_ev_end


/***********************<<   >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *����GKע����Ϣ
 */
_event(  ev_umsGKReg_cmd )
_body(TTPGKCfg,	1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *GKע����Ϣ֪ͨ
 */
_event(  ev_umsGKReg_notify )
_body(TTPGKCfg,	1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *UMS��֪CMSע��ʧ�ܽ��
 */
_event(  ev_umsGKReg_ret )
_body(TUCSipRegResult,	1)
_ev_end

/***********************<< ��ȡȫ����UMS��CNS��ȫ��ע����Ϣ >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cmc	  -> UMS
*/
_event( ev_umsGetRegInfo_Req )
_body( EmGetRegInfoType, 1 )
_ev_end

/***********************<< ��ȡȫ����UMS��CNS��ȫ��ע����Ϣ�ظ� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  UMS	  -> cmc
*/
_event( ev_umsGetRegInfo_Rsp )
_body( TTPSipRegPackInfo, 1 )
_body( EmGetRegInfoType, 1 )
_body( TTPSipRegInfo, 1 )
_ev_end

/***********************<< B2�汾UMSע����Ϣ >>********************** 
*[��Ϣ��]

  *[��Ϣ����]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_UmsRspEx )
	_body( TUmsRegPackEx, 1)
_ev_end

/***********************<< B2�汾CNSע����Ϣ >>********************** 
*[��Ϣ��]

  *[��Ϣ����]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_CnsRspEx )
	_body( TCnsRegPackEx, 1)
_ev_end

/***********************<< B2�汾mtע����Ϣ >>********************** 
*[��Ϣ��]

  *[��Ϣ����]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_MtRspEx )
	_body( TTPMtRegInfo, 1)
_ev_end

/***********************<< B2�汾mcuע����Ϣ >>********************** 
*[��Ϣ��]

  *[��Ϣ����]
  *  UMS	  -> cmc
  */
  _event( ev_umsGetRegInfo_McuRspEx )
	_body( TTPMcuRegInfo, 1)
_ev_end

/***********************<< ά������Sipע����֪ͨ >>********************** 
 *[��Ϣ����]
 *  ums	  -> tool
 */
  _event( ev_ums_sipreg_state_nty )
  _body( BOOL32, 1 )  //Sip�Ƿ�ע����
  _body( TTPSipRegistrarCfg, 1)
  _ev_end

 /***********************<< ά������GKע����֪ͨ >>********************** 
 *[��Ϣ����]
 *  ums	  -> tool
 */
  _event( ev_ums_gkreg_state_nty )
  _body( BOOL32, 1 )  //GK�Ƿ�ע��
  _body( TTPGKCfg, 1)
  _ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(outerumsreg)
};
#endif

#endif //_h_eventoutumsreg_h__

