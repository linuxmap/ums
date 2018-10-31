#ifndef _h_eventoutumsbrdvmp_h_
#define _h_eventoutumsbrdvmp_h_

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterumsbrdvmp
{
#endif

	_ev_segment( outerumsbrdvmp )
		
/***********************<<   >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *  UMC ���� ռ�úϳ�
 */
_event(  ev_UMC_UMS_RervesBrdVmp_Req )
_body(TRersvesEqpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CNC	-->  UMS
 *  CNC ���� ռ�úϳ�
 */
_event(  ev_CNC_UMS_RervesBrdVmp_Req )
_body(TUmsHandle, 1)
_body(TRersvesEqpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  UMS��umc  ռ�úϳ� �Ļ�Ӧ
 */
_event(  ev_UMS_UMC_RervesBrdVmp_Ind )
_body(TRersvesEqpRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CNC
 *  UMS��cnc ռ�úϳ� �Ļ�Ӧ
 */
_event(  ev_UMS_CNC_RervesBrdVmp_Ind )
_body(TUmsHandle, 1)
_body(TRersvesEqpRsp, 1)
_ev_end


/***********************<<   >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *  UMC ���� ���úϳ�
 */
_event(  ev_UMC_UMS_SetBrdVmp_Req )
_body(TSetVmpInfoReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CNC	-->  UMS
 *  CNC ���� ���úϳ�
 */
_event(  ev_CNC_UMS_SetBrdVmp_Req )
_body(TUmsHandle, 1)
_body(TSetVmpInfoReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  UMS��umc  ���úϳ� �Ļ�Ӧ
 */
_event(  ev_UMS_UMC_SetBrdVmp_Ind )
_body(TSetVmpInfoRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CNC
 *  UMS��cnc ���úϳ� �Ļ�Ӧ
 */
_event(  ev_UMS_CNC_SetBrdVmp_Ind )
_body(TUmsHandle, 1)
_body(TSetVmpInfoRsp, 1)
_ev_end


/***********************<<   >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *  UMC ���� �㲥�ϳ�
 */
_event(  ev_UMC_UMS_BrdVmp_Req )
_body(TBrdVmpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CNC	-->  UMS
 *  CNC ���� �㲥�ϳ�
 */
_event(  ev_CNC_UMS_BrdVmp_Req )
_body(TUmsHandle, 1)
_body(TBrdVmpReq, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  UMS��umc  �㲥�ϳ� �Ļ�Ӧ
 */
_event(  ev_UMS_UMC_BrdVmp_Ind )
_body(TBrdVmpRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CNC
 *  UMS��cnc �㲥�ϳ� �Ļ�Ӧ
 */
_event(  ev_UMS_CNC_BrdVmp_Ind )
_body(TUmsHandle, 1)
_body(TBrdVmpRsp, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  ֪ͨUMC�ĺϳ���״̬
 */
_event(  ev_UMS_UMC_BrdVmp_Ntfy )
_body(TBrdVmpResArray, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CNC
 *  ֪ͨCNC�ĺϳ���״̬
 */
_event(  ev_UMS_CNC_BrdVmp_Ntfy )
_body(TUmsHandle, 1)
_body(TBrdVmpResArray, 1)
_ev_end

/***********************<<   >>********************	

 *[��Ϣ����]	UMS	-->  UMS
 *  ֪ͨ��UMS���ϳɹ㲥�������˺ϳɵ�״̬
 */
_event(  ev_UMS_UMS_VmpCasecade_Ntfy )
_body(TUmsHandle, 1)
_body(TVmpCasecadeNtfy, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *  UMC ���� ����ϳ�Ԥ��
 */
_event(  ev_UMC_UMS_SaveVmpCfg_Cmd )
_body(TTpVmpMemberCfg, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CNC	-->  UMS
 *  CNC ���� ����ϳ�Ԥ��
 */
_event(  ev_CNC_UMS_SaveVmpCfg_Cmd )
_body(TUmsHandle, 1)
_body(TTpVmpMemberCfg, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *  UMS��umc  ����ϳ�Ԥ�� �Ļ�Ӧ
 */
_event(  ev_UMS_UMC_SaveVmpCfg_Ind )
_body(TTpVmpMemberCfgInd, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CNC
 *  UMS��cnc ����ϳ�Ԥ�� �Ļ�Ӧ
 */
_event(  ev_UMS_CNC_SaveVmpCfg_Ind )
_body(TUmsHandle, 1)
_body(TTpVmpMemberCfgInd, 1)
_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  call
 *  UMS��cnc ����ϳ�Ԥ�� �Ļ�Ӧ
 */
_event(  ev_Save_VmpCfg_Ack )
_body(u16, 1)         //�ϳ�Ԥ�������±�
_body(BOOL32, 1)	  //������
_ev_end


#ifndef _MakeTpEventDescription_
_ev_segment_end(outerumsbrdvmp)
};
#endif




#endif // _h_eventoutumsbrdvmp_h_
