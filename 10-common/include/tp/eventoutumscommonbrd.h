#ifndef _h_eventoutumscommonbrd_h__
#define _h_eventoutumscommonbrd_h__

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumscommonbrd
{
#endif
	_ev_segment( outerumscommonbrd )	
	
	/***********************<<����ע������>>********************	
	*[��Ϣ����]	umsboard  -->  EqpApp
	*
	*/
	_event(  ev_TPBrdReg_Req )
	_body(TTPBrdRegInfo, 1)
	_ev_end
	
	/***********************<<����ע��Ack>>********************	
	*[��Ϣ����]	EqpApp  -->  umsboard
	*
	*/
	_event(  ev_TPBrdReg_Ack )
	_ev_end

	/***********************<<����ע��Nack>>********************	
	*[��Ϣ����]	EqpApp  -->  umsboard
	*
	*/
	_event(  ev_TPBrdReg_NAck )
	_ev_end
	
	/***********************<<�����ȡ��������>>********************	
	*[��Ϣ����]	umsboard   -->  EqpApp
	*
	*/
	_event(  ev_TPBrdGetCfg_Req )
	_body(TTPBrdPos, 1)
	_ev_end
	
	/***********************<<�����ȡ����Ack>>********************	
	*[��Ϣ����]	EqpApp    -->  umsboard
	*
	*/
	_event(  ev_TPMcuBrdGetCfg_Ack )
	_body(u8, 256)
	_ev_end
	
	/***********************<<�����ȡ����Nack>>********************	
	*[��Ϣ����]	EqpApp    -->  umsboard
	*
	*/
	_event(  ev_TPBrdGetCfg_NAck )// EqpApp -> ����
	_ev_end
	
	/***********************<<�����ȡ����Nack>>********************	
	*[��Ϣ����]	umsboard     -->  EqpApp
	*
	*/
	_event(  ev_TPBrdConnect_Timer )
	_ev_end

	/***********************<<��������Cmd>>********************	
	*[��Ϣ����]	EqpApp     -->  umsboard
	*
	*/
	_event(  ev_TPBrdReboot_Cmd )
	_ev_end
	
	/***********************<<֪ͨ����ͬ������ʱ��>>********************	
	*[��Ϣ����]	EqpApp     -->  umsboard
	*
	*/
	_event(  ev_TPBrdSetSysTime_Cmd )
	_body( TTPTime, 1 )
	_ev_end

	/***********************<<�����ȡ�汾����>>********************	
	*[��Ϣ����]	EqpApp      -->  umsboard
	*
	*/
	_event(  ev_TPBrdHDVersion_Req )
	_ev_end

	/***********************<<�����ȡ�汾Ack>>********************	
	*[��Ϣ����]	umsboard     -->  EqpApp
	*
	*/
	_event(  ev_TPBrdHDVersion_Ack )
	_body( TBrdVersion , 1)
	_ev_end

	/***********************<<������������>>********************	
	*[��Ϣ����]	EqpApp      -->  umsboard
	*
	*/
	_event(  ev_TPBrdSoftWareUpdate_Req )
	_body( TBrdUpInfo, 1 )
	_ev_end

	/***********************<<�������������Ӧ>>********************	
	*[��Ϣ����]	umsboard      -->  EqpApp
	*
	*/
	_event(  ev_TPBrdSoftWareUpdate_Ack )
	_body( BOOL32, 1 )
	_ev_end


	/***********************<<����Telnet Ftp ��������>>********************	
	*[��Ϣ����]	EqpApp      -->  umsboard
	*
	*/
	_event( ev_TPBrdSwitchTeltp_Req )
	_body( TBrdSwitchInfo, 1 )
	_ev_end

	/***********************<<����Telnet Ftp ������Ӧ>>********************	
	*[��Ϣ����]	umsboard      -->  EqpApp
	*
	*/
	_event( ev_TPBrdSwitchTeltp_Ack )
	_body( TBrdSwitchInfo, 1 )
	_ev_end	




#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumscommonbrd )
};
#endif

#endif