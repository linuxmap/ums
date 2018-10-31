#ifndef _h_innereventumscall_h__
#define _h_innereventumscall_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emumsinnercall
{
#endif

	_ev_segment( umsinnercall )

/***********************<<  ��Ȩ����֪ͨ >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsAccessNum_Notify )
_body ( u32  , 1  )	//����
_ev_end		
		
/***********************<<  ����֪ͨ�н���ע�� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsAdapterReg_Notify )
_body ( TEqpRes  , 1  )
_body ( TTPTransAddr  , 1  )		//Э��ջ�������	
_ev_end

/***********************<<  ����֪ͨ�н���ȡ��ע�� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsAdapterUnReg_Notify )
_body ( TEqpRes  , 1  )
_ev_end

/***********************<<  ����֪ͨ�л�����ȡ��ע�� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsAudioMixUnReg_Notify )
_body ( u8  , 1  )//EqpID
_ev_end

/***********************<<  ����֪ͨ�л�����ע�� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsAudioMixReg_Notify )
_body ( TEqpRes  , 1  )
_ev_end

/***********************<<  ����֪ͨ��ת��ע�� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsMediaReg_Notify )
_body ( TEqpRes  , 1  )
_body(TIpmaskinfo, 1)
_ev_end

/***********************<<  ����֪ͨ��ת��ȡ��ע�� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsMediaUnReg_Notify )
_body ( TEqpRes  , 1  )
_ev_end

/***********************<<  ����֪ͨ�кϳɵ��� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsVmpUnReg_Notify )
_ev_end

/***********************<<  ����֪ͨmpcע��ɹ� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp	--> call
 *
 */
_event(  evtp_UmsMpcReged_Notify )
_body ( BOOL32  , 1  )	//�Ƿ�����MPC
_ev_end


/***********************<<  ���ݻ���ģ���ٿ����� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	service	--> call
 *
 */
_event(  evtp_UmsMakeConf )
_body ( TConfTemplateLocal  , 1  )
_ev_end



/***********************<<  ���е��� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> service
 *
 */
 _event(  evtp_UmsConfIncomingAck )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_body ( EmCnsCallReason  , 1  )
_body ( u16  , 1  )
_body ( TConfTemplateLocal  , 1  )
_body ( BOOL32  , 1  )
_ev_end

/***********************<<  ������� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_UmsConfDisConnect )
_body ( u16  , 1  )		//InstID, Ҳ�ǻ����
_ev_end

/***********************<<  ���鶨ʱ����δ���᳡ >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> call
 *
 */
_event(  evtp_CallNode_time )
_ev_end


/***********************<<  ��ʱ��UIˢ�½����Ϣ  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> call
 *
 */
_event(  evtp_UpdateConfNode_time )
_ev_end


/***********************<<  ��ѯ��ʱ��  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> call
 *
 */
_event(  evtp_ExeTurnList_time )
_ev_end

/***********************<<  ���鿪ʼʱ�Ĺؼ�֡����  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> call
 *
 */
_event(  evtp_KeyProtectOnStart_time )
_ev_end

/***********************<<  ����ϳ�ʧ��  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Eqp	--> call
 *
 */
_event(  evtp_VmpToCall_NAck )
_ev_end

/***********************<<  ����ϳ���������  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Eqp	--> call
 *
 */
_event(  evtp_UmsVmpReg_Notify )
_ev_end

/***********************<<  ����ϳɵ�������  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Eqp	--> call
 *
 */
_event(  evtp_StartVmp_Req )
_body( u8, 1 )
_body(TTVmpStartParam, 1)
_ev_end

// 
_event( evtp_AdjustVmp_Req)
_body( u8, 1 )
_body(TUmsVidFormat, 1)
_ev_end

/***********************<<  �����������  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Eqp	--> call
 *
 */
_event(  evtp_UmsBasUnReg_Notify )
_body( u8, 1 )//eqp id
_ev_end

/***********************<<  �������俪��ʧ��  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Eqp	--> call
 *
 */
_event(  evtp_UmsBasStart_NAck )
_body( TTPBasNAck, 1 )//eqp id
_ev_end

/***********************<<  ����ؼ�֡  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Call --> eqp
 *
 */
_event(  evtp_UmsBasAskFrame_Req )
_body( u8 , 1 )//EqpID
_body( u16 , 1 )//chnIndx
_ev_end

/***********************<<  �������ص�ת������  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp --> Call
 *
 */
_event(  evtp_UmsBasChangeDsIP_Req )
_body( TBasMediaInfo , 1 )
_ev_end

/***********************<<  ��ʱ�����������ؼ�֡ >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> call
 *
 */
_event(  evtp_AskFrameToBas_time )
_body(u16, 1)
_ev_end

/***********************<<  ��ʾ���󣺺ϳ�����G400 ��ĳT300 >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	startvmp����	--> call
 *
 */
_event(  evtp_StartVmpToT300_Cmd )
_body(u32_ip, 1)//T300��IP
_body(u16, 1)//T300�Ľ��ն˿�
_body(u32, 1)//�ն����ͣ�MT��CNS��G400
_ev_end

/***********************<<  ������Ϣ��ģ������adjust >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	����	--> call
 *
 */
_event(  evtp_BasTestAdjust_Cmd )
_body(u16, 1)
_ev_end

/***********************<<  ��Ƶ���� ����ʧ�� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	����	--> call
 *
 */
_event(  evtp_AudBasStartAdapter_NAck )
_body(TTPBasNAck, 1)
_ev_end

/***********************<<  ��Ƶ���� ����ת������� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	����	--> call
 *
 */
_event(  evtp_AudBasDsEqpDisConnect_Ntfy )
_body(TBasMediaInfo, 1)
_ev_end

/***********************<<  ҵ������ >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	����	--> call
 *
 */
_event(  evtp_EqpService_Reg )
	_body(TServiceReg, 1)
_ev_end

/***********************<<  ҵ����� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	����	--> call
 *
 */
_event(  evtp_EqpService_UnReg )
	_body(TServiceBaseInfo, 1)
_ev_end

/***********************<<  timerMgr�Ķ�ʱ��  >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> call
 *
 */
_event(  evtp_TimerMgrTimer_Tick )
_ev_end

// �᳡���״̬��ʱ��ⶨʱ��
_event(  evtp_EpNodeTimer_Check )
_ev_end



/***********************<<  ������ʱ��������server >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> server
 *
 */
_event(  evtp_Update_TempConf_To_Server )
    _body(u16, 1)
	_body(TTPAlias, 1)
_ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnercall)
};
#endif




#endif // _h_innereventumscall_h__
