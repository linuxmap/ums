#ifndef _SIPCALLSTDMSG_H
#define _SIPCALLSTDMSG_H

#include "sipcallstdstruct.h"

//������Ϣ
enum EmSipCallMsgType 
{
	h_call_invalidInterface = 0,
	h_call_make				= 1,	//�������
	h_call_incoming			= 2,	//���е���		
	h_call_answer			= 3,	//����(�ܾ�)���� 
	h_call_bye              = 4,    //��������		
	h_call_connected        = 5,    //���н���		 
	h_call_disconnected     = 6,    //���жϿ�		 
	h_call_capsetnotify     = 7,    //����������     
	h_dual_failed			= 8,
	h_call_roundtripdelay   = 9,    //roundtrip implemented by options method
	h_call_ack				= 10,
	h_call_reinvite			= 11,
	h_call_200OK			= 12,
	h_call_callidnotify		= 13,
};

enum EmSipRegCtrlMsgType
{
	h_sip_registration   = 0, 
	h_sip_unregistration = 1,

	h_sip_state2registered,
	h_sip_state2failed,
	h_sip_state2terminated,

	h_sip_state2redirected,
	h_sip_state2sendmsgfailed,
	
	h_sip_getreginfo,       //���regserver�ϵ�����ע����Ϣ����
	h_sip_getreginfoack,    //regserver��ע����Ϣ����Ļ�Ӧ
	h_sip_getreginfoack_B2,    //regserver��ע����Ϣ����Ļ�Ӧ
	
	h_sip_reg_nonstandard_req,	// SIP nonstandard messages between user agents and REGISTR
	h_sip_registration_ack,

	h_sip_QuanTumGetIpByAlias,	//��ȡ������Ӧ��ip��Ϣ
	
	h_sip_regctrl_end
};

enum EmSipUMSCtrlMsgType
{
	h_ums_invalidInterface	= 0,
	h_ums_registrationcmd	= 1,	// RegisterRequest ע������ 
	h_ums_registrationind	= 2,	// ע��ɹ���EmRegisterReason+TRegisterResponse��ע��ʧ�ܣ�EmRegisterReason (emRegFail); ע������ EmRegisterReason(emRegNameDup)+sizeof(s32)+TSipRegName ע����Ӧ
	h_ums_unregistrationcmd	= 3,	// RegisterRequest+bool(if expire all) ȡ��ע������
	h_ums_unregistrationind	= 4,	// EmRegisterReason ȡ��ע����Ӧ,ԭ��Ϊȡ���ɹ���ʧ��
	h_ums_query				= 5,	// char(����) ��ѯ		h_ums_answer,      //EmRegisterReason+RegisterResponse ��Ӧ��ѯ
	h_ums_answer			= 6,	// EmRegisterReason+RegisterResponse ��Ӧ��ѯ
	h_ums_option			= 7,	// ��������ע���ն˷��Ͳ�ѯָ� ��option��Ϣ�� �ص�Ҳ��option��Ϣ,����regserver��ѯע���Ƿ�����
	h_ums_getregreq			= 8,	// ums��cns��regserver�����õ�ǰ�ı���, buf������Ϊ��s32 nAppid, EmSIPRegNSMType
	h_ums_getregack			= 9,	// regserver��Ӧ��, buf������Ϊ��s32 nAppid, TSipRegPackXml
	h_ums_getregack_B2		= 10,	// regserver��Ӧ��, buf������Ϊ��s32 nAppid, TSipRegPackXmlB2, TSipRegInfoUms/TSipRegInfoCns				
	//h_sip_reg_nonstandard_rsp,	// SIP nonstandard messages between user agents and REGISTRAR
};

enum EmSipArbitraryMsgType
{
	h_sip_invalid,
	h_sip_info,
	h_sip_info_ack,
	h_sip_options,
	h_sip_options_ack,
};
#endif