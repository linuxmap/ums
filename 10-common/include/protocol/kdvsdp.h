#ifndef __KDVSDP_H__
#define __KDVSDP_H__

#include "sipcallstdstruct.h"
#include "kdvsiphandle.h"

//设置sdp能力（将CSipCapSet对象转换为协议栈sdp能力）
PROTO_API BOOL32 kdvsdp_create_sdp(CSipCapSet *pcCap, TSdpHandle hHandle);

//获取sdp能力（将协议栈sdp能力转换为CSipCapSet对象）
PROTO_API BOOL32 kdvsdp_build_capset(TSdpHandle hHandle, CSipCapSet *pcCap);

PROTO_API void sdpregfunlinux();

PROTO_API BOOL32 sdpIsTps(emEndpointType m_emEndpointType);
//调试接口
PROTO_EXTERN_API void sdphelp();

PROTO_EXTERN_API void sdplogon(s32 nLevel);

PROTO_EXTERN_API void sdplogoff();

PROTO_EXTERN_API void sdpver();

PROTO_EXTERN_API void sdplogto(u8 byFilter);

#endif