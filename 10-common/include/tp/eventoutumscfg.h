#ifndef _h_eventoutumscfg_h__
#define _h_eventoutumscfg_h__

//#include "tpeventcomm.h"
#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumscfg
{
#endif
	
	_ev_segment( outerumscfg )
		
/***********************<<   >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *����UMSIP
 */
_event(  ev_UmsIPCfg )
_body(TTPEthnetInfo, 1)
_body(EmEthInfoType, 1)
_ev_end


_event(  ev_UmsIPCfg_Ind )
_body(TTPEthnetInfo, 1)
_body(EmEthInfoType, 1)
_ev_end



/***********************<< ����ʱ�� >>********************** 
*[��Ϣ��]
+TTPTime		
*[��Ϣ����]
*  ums	  <- umc
*/
_event( ev_UmsSetSysTime_Cmd )
_body( TTPTime, 1 )
_ev_end

/***********************<< ��ѯʱ�� >>********************** 
*[��Ϣ��]
+TTPTime
*[��Ϣ����]
*  ums	  <- umc
*/
_event( ev_UmsGetSysTime_Req)
_ev_end


/***********************<< ��ѯʱ����Ӧ >>********************** 
*[��Ϣ��]
+TTPTime
*[��Ϣ����]
*  ums	  -> umc
*/
_event( ev_UmsGetSysTime_Rsp)
_body( TTPTime, 1 )
_ev_end


/***********************<<  ������ܷ�����  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_NMServerAdd_req )
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  ������ܷ�����Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_NMServerAdd_rsp )
	_body(EmModifyNMServerRet, 1)
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  �޸����ܷ�����  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_NMServerMdy_req )
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  �޸����ܷ�����Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_NMServerMdy_rsp )
	_body(EmModifyNMServerRet, 1)
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  ɾ�����ܷ�����  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_NMServerDel_req )
	_body(TTPNMServerCfg, 1)
_ev_end

/***********************<<  ɾ�����ܷ�����Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_NMServerDel_rsp )
	_body(EmModifyNMServerRet, 1)
	_body(TTPNMServerCfg, 1)
_ev_end


/***********************<<  ���ܷ������б�  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_NMServer_nty )
	_body(u16,	1)
	_body(TTPNMServerCfg, TP_MAX_NMSERVER)
_ev_end

/***********************<<  ���¼���  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_VcrAdd_req )
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  ���¼���Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_VcrAdd_rsp )
	_body(EmModifyVcrRet, 1)
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  �޸�¼���  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_VcrMdy_req )
	_body(TVcrCfg,	1)	//�޸�ǰ��Ϣ
	_body(TVcrCfg,	1)	//�޸ĺ���Ϣ
_ev_end

/***********************<<  �޸�¼���Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_VcrMdy_rsp )
	_body(EmModifyVcrRet, 1)
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  ɾ��¼���  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_VcrDel_req )
	_body(TVcrCfg, 1)
_ev_end

/***********************<<  ɾ��¼���Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_VcrDel_rsp )
	_body(EmModifyVcrRet, 1)
	_body(TVcrCfg, 1)
_ev_end


/***********************<<  ¼����б�  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	tool  -->  ums	
 *
 */
 _event(  ev_Vcr_nty )
	_body(u16, 1)
	_body(TVcrCfg, TP_MAX_VCR)
_ev_end


/***********************<<  ums �汾��Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 */

_event(  ev_umsverInfo_Nty )
_body(TUmsVersion,	1)
_ev_end


/***********************<<  umc����ums >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	umc  -->  ums	
 */
 _event(  ev_umcrebootUms_cmd )
 _ev_end
 
#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumscfg)
};
#endif




#endif // _h_eventoutumscfg_h__
