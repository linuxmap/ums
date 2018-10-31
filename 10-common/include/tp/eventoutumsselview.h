#ifndef _h_eventoutumsselview_h_
#define _h_eventoutumsselview_h_

//#include "tpeventcomm.h"
#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumsselview
{
#endif

	_ev_segment( outerumsselview )
		
/***********************<<   >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *  UMC ���� ѡ��
 */
_event(  ev_UMC_UMS_SelView_Req )
_body(TTPSelViewReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CNC	-->  UMS
 *  CNC ���� ѡ��
 */
_event(  ev_CNC_UMS_SelView_Req )
_body(TUmsHandle, 1)
_body(TTPSelViewReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  UMS��umc�Ļ�Ӧ
 */
_event(  ev_UMS_UMC_SelView_Ind )
_body(TTPSelViewInd, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CNC
 *  UMS��cnc�Ļ�Ӧ
 */
_event(  ev_UMS_CNC_SelView_Ind )
_body(TUmsHandle, 1)
_body(TTPSelViewInd, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  �¼� �� �ϼ�ѡ������Ļ�Ӧ
 */
_event(  ev_UMS_UMS_SelView_Ind )
_body(TUmsHandle, 1)
_body(TTPSelViewInd, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  ֪ͨUMC��ѡ��״̬
 */
_event(  ev_UMS_UMC_SelView_Ntfy )
_body(TTPSelViewNtfy, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CNC
 *  ֪ͨUMC��ѡ��״̬
 */
_event(  ev_UMS_CNC_SelView_Ntfy )
_body(TUmsHandle, 1)
_body(TTPSelViewNtfy, 1)
_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumsselview)
};
#endif




#endif // _h_eventoutumsselview_h_
