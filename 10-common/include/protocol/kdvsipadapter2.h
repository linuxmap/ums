#ifndef __SIPADAPTER_H__
#define __SIPADAPTER_H__

#include "kdvtype.h"
#include "sipcallstdstruct.h"
#include "sipconfnonstdmsg.h"

class PROTO_API CSipAdapter
{
public:	
	
	static BOOL32 sipadpt_app_init(TSipAdapterCfg *ptCfg);

	static BOOL32 sipadpt_app_destroy();

	static u16 sipadpt_get_call_count();

	static void sipadpt_set_app_callback(TSipAdapterCB *ptEvent);

	static void sipadpt_regc_get_callid(s32 hsReg, s8 *pchCallid, s32 &nLen);

	static BOOL32 sipadpt_set_call_app_handle(s32 haCall, s32 hsCall);

	static BOOL32 sipadpt_create_new_call(s32 haCall, s32 &hsCall);

	static BOOL32 sipadpt_get_tlssituation_frominfo(IN s32 hsCall, OUT BOOL32 *pbTls,  OUT u32 *pdwPeerCertificatStatus,  OUT s32 *pnCipher);

	static BOOL32 sipadpt_create_new_reg(s32 haReg, s32 &hsReg);

	/*
	wMsgType：pbyBuf，dwLen
	h_call_make：TSipCallParam+CSipCapSet，sizeof(TSipCallParam) + sizeof(CSipCapSet)，可以不包含CSipCapSet对象
	h_call_answer：TSipCallParam+CSipCapSet，sizeof(TSipCallParam) + sizeof(CSipCapSet)
	h_call_ack：TSipCallParam+CSipCapSet，sizeof(TSipCallParam) + sizeof(CSipCapSet)，可以不包含CSipCapSet对象
	h_call_bye：u8，sizeof(u8)
	h_call_reinvite：CSipCapSet+u8，sizeof(CSipCapSet)+sizeof(u8)
	h_call_200OK：CSipCapSet+u8，sizeof(CSipCapSet)+sizeof(u8)
	h_call_roundtripdelay：NULL，0
	*/
	static BOOL32 sipadpt_send_call_ctrl_msg(s32 hsCall, u16 wMsgType, const u8 *pbyBuf, u32 dwLen);

	/*
	若与dialog无关，则hsCall为-1；否则，ptHandle为NULL
	wMsgType：pbyBuf，dwLen
	h_sip_info，h_sip_options：TSipNonStdData+buffer，sizeof(TSipNonStdData)+sizeof(buffer)（dialog无关）；buffer，sizeof(buffer)（dialog相关）
	*/
	static BOOL32 sipadpt_send_conf_ctrl_reqmsg(s32 hsCall, u16 wMsgType, const u8 *pbyBuf, u32 dwLen, TSipUacHandle *ptHandle);

	/*
	tHandle为非空句柄（收到请求时回调），nStatusCode为应答码，pbyBuf和dwLen暂为NULL及0
	*/
	static BOOL32 sipadpt_send_conf_ctrl_rspmsg(TSipUasHandle tHandle, s32 nStatusCode, const u8 *pbyBuf, u32 dwLen);

	/*
	wMsgType：pbyBuf，wLen
	h_sip_registration：TRegisterInfo+注册别名个数(s32)+buffer长度(s32)+buffer，sizeof(TRegisterInfo)+2*sizeof(s32)+sizeof(buffer)
	h_sip_unregistration：NULL，0
	h_sip_getreginfo，h_sip_reg_nonstandard_req：非标包头个数(u8)+非标包头个数*TSipHead+TSIPRegNSM+buffer,
		sizeof(u8)+非标包头个数*sizeof(TSipHead)+sizeof(TSIPRegNSM)+sizeof(buffer)
	*/
	static BOOL32 sipadpt_send_reg_ctrl_reqmsg(s32 hsReg, u16 wMsgType, const u8 *pbyBuf, u16 wLen);

	/*
	同sipadpt_send_conf_ctrl_rspmsg各参数定义
	*/
	static BOOL32 sipadpt_send_reg_ctrl_rspmsg(TSipUasHandle tHandle, s32 nStatusCode, const u8 *pbyBuf, u32 dwLen);

	static BOOL32 sipadpt_send_fecc_ctrl_msg(s32 hsCall, u16 wMsgType, const u8 *pbyBuf, u16 wLen);

	static void sipadpt_set_nat_ip(u32 dwIp);

	static BOOL32 sipadpt_send_dtmf_info(s32 hsCall, const u8 *pbyBuf, u16 wLen);

#ifdef _ENABLE_QUANTUM_PROJECT_
	static BOOL32 sipadpt_set_qt_init_param(u8* pbyBuf, u16 wLen);
#endif

private:

	static void sipadpt_default_config();
	
	static BOOL32 sipadpt_set_config(TSipAdapterCfg *ptCfg);
	
};

PROTO_EXTERN_API void sipadapterhelp();
PROTO_EXTERN_API void sipadapterver();
PROTO_EXTERN_API void sipadapterlogon(s32 nType);
PROTO_EXTERN_API void sipadapterlogoff();
PROTO_EXTERN_API void setsiptrace(u32 dwFlag = 0);
PROTO_EXTERN_API void sipstacklogon(s32 nLevel = 0);
PROTO_EXTERN_API void sipstacklogoff();
PROTO_EXTERN_API void showsipstack();
PROTO_EXTERN_API void sipadapterlogto(u8 byFilter);
PROTO_EXTERN_API void sipstacklogto(u8 byFilter);
PROTO_EXTERN_API void siptsxtimeout(s32 nTimeout1, s32 nTimeout2, s32 nTimeout4, s32 nTimeoutTD);

#endif
