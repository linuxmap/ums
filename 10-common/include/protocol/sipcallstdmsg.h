#ifndef _SIPCALLSTDMSG_H
#define _SIPCALLSTDMSG_H

#include "sipcallstdstruct.h"

//呼叫消息
enum EmSipCallMsgType 
{
	h_call_invalidInterface = 0,
	h_call_make				= 1,	//发起呼叫
	h_call_incoming			= 2,	//呼叫到来		
	h_call_answer			= 3,	//接受(拒绝)呼叫 
	h_call_bye              = 4,    //结束呼叫		
	h_call_connected        = 5,    //呼叫建立		 
	h_call_disconnected     = 6,    //呼叫断开		 
	h_call_capsetnotify     = 7,    //能力级交互     
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
	
	h_sip_getreginfo,       //获得regserver上的所有注册信息请求
	h_sip_getreginfoack,    //regserver对注册信息请求的回应
	h_sip_getreginfoack_B2,    //regserver对注册信息请求的回应
	
	h_sip_reg_nonstandard_req,	// SIP nonstandard messages between user agents and REGISTR
	h_sip_registration_ack,

	h_sip_QuanTumGetIpByAlias,	//获取别名对应的ip信息
	
	h_sip_regctrl_end
};

enum EmSipUMSCtrlMsgType
{
	h_ums_invalidInterface	= 0,
	h_ums_registrationcmd	= 1,	// RegisterRequest 注册命令 
	h_ums_registrationind	= 2,	// 注册成功：EmRegisterReason+TRegisterResponse；注册失败：EmRegisterReason (emRegFail); 注册重名 EmRegisterReason(emRegNameDup)+sizeof(s32)+TSipRegName 注册响应
	h_ums_unregistrationcmd	= 3,	// RegisterRequest+bool(if expire all) 取消注册命令
	h_ums_unregistrationind	= 4,	// EmRegisterReason 取消注册响应,原因为取消成功或失败
	h_ums_query				= 5,	// char(别名) 查询		h_ums_answer,      //EmRegisterReason+RegisterResponse 回应查询
	h_ums_answer			= 6,	// EmRegisterReason+RegisterResponse 回应查询
	h_ums_option			= 7,	// 服务器向注册终端发送查询指令， 发option消息， 回调也是option消息,用在regserver查询注册是否还在线
	h_ums_getregreq			= 8,	// ums或cns向regserver请求获得当前的别名, buf中依次为：s32 nAppid, EmSIPRegNSMType
	h_ums_getregack			= 9,	// regserver的应答, buf中依次为，s32 nAppid, TSipRegPackXml
	h_ums_getregack_B2		= 10,	// regserver的应答, buf中依次为，s32 nAppid, TSipRegPackXmlB2, TSipRegInfoUms/TSipRegInfoCns				
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