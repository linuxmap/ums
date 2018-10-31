#ifndef _h_innereventumsboard_h__
#define _h_innereventumsboard_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emumsinnerboard
{
#endif
	_ev_segment( umsinnerboard )	

	_event( ev_board_cfg_info )        //service��ȡ������������Ϣ֪ͨeqp
	_body( TTPBrdInfo, 1 )  //����������Ϣ
	_body( BOOL32, 1 )      //�����Ƿ�����
	_ev_end

	/***********************<<���µ���ע����>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_reg_result )      //���µ���ע����֪ͨhandleboardservice
	_body( TBrdStateInfo, 1 )
	_ev_end

	/***********************<<���µ���ҵ��ע����>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_mode_reg_result ) //���µ���ҵ��ע����֪ͨhandleboardservice
	_body( TBrdStateInfo, 1 )		//ע����
	_ev_end

	/***********************<<�������֪ͨ>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_disc_nty )
	_body( TBrdStateInfo, 1 )
	_ev_end

	/***********************<<����ɾ��֪ͨ>>********************	
	*[��Ϣ����]	service  -->  eqp
	*
	*/
	_event( ev_board_del_nty )
	_body( u16, 1 )			//��Ӧλ����������
	_ev_end

	/***********************<<�����޸�֪ͨ>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_modify_nty )
	_body( TTPBrdCfg, 1 )
	_ev_end

	/***********************<<����ģʽɾ��֪ͨ>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_mode_del_nty )
	_body( u16, 1 ) //��������
	_body( u16, 1 ) //ģʽ����
	_ev_end

	/***********************<<����ģʽ�޸�֪ͨ>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_mode_modify_nty )
	_body( TTPBrdMdlInfo, 1 )
	_ev_end

	/***********************<<����ʹ�����>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_used_nty )
	_body( TTPBrdUsedInfo, 1 )
	_ev_end

	/***********************<<��������>>********************	
	*[��Ϣ����]	service  -->  eqp
	*
	*/
	_event( ev_board_reboot_req )
	_body( u16, 1 )
	_ev_end

	/***********************<<��������>>********************	
	*[��Ϣ����]	service  -->  eqp
	*
	*/
	_event( ev_board_upgrade_req )
	_body( TBrdUpInfo, 1 )
	_ev_end
	/***********************<<�����������>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_upgrade_res )
	_body( u16, 1) //��������
	_body( BOOL32, 1 )
	_ev_end

	/***********************<<����汾����>>********************	
	*[��Ϣ����]	service  -->  eqp
	*
	*/
	_event( ev_board_getversion_req )
	_ev_end

	/***********************<<����汾��Ӧ>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_getversion_ack )
	_body(TBrdVersion, 1)
	_ev_end

	/***********************<<����������ϳɡ�����ռ���������>>********************	
	*[��Ϣ����]	service  -->  eqp
	*
	*/
	_event( ev_board_used_req )
	_body( EMEqpType, 1 )		//�������� ��ʾ�ǻ�������ϳɻ�����
	_ev_end

	/***********************<<�������������Ӧ>>********************	
	*[��Ϣ����]	umsboard      -->  EqpApp
	*
	*/
	_event(  ev_TPUpdate_Task_Return )
	_body( BOOL32, 1 )
	_ev_end

	/***********************<<����Telnet Ftp ��������>>********************	
	*[��Ϣ����]	service  -->  eqp
	*
	*/
	_event( ev_board_switchtelnetftp_req )
	_body( TBrdSwitchInfo, 1 )
	_ev_end
	/***********************<<����Telnet Ftp ��������>>********************	
	*[��Ϣ����]	eqp  -->  service
	*
	*/
	_event( ev_board_switchtelnetftpe_res )
	_body( TBrdSwitchInfo, 1 )
    _body(EmBoardSwitchRes,1)
	_ev_end


#ifndef _MakeTpEventDescription_
	_ev_segment_end( umsinnerboard )
};
#endif

#endif