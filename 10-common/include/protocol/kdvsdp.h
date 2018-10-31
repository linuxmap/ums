#ifndef __KDVSDP_H__
#define __KDVSDP_H__

#include "sipcallstdstruct.h"
#include "kdvsiphandle.h"

//����sdp��������CSipCapSet����ת��ΪЭ��ջsdp������
PROTO_API BOOL32 kdvsdp_create_sdp(CSipCapSet *pcCap, TSdpHandle hHandle);

//��ȡsdp��������Э��ջsdp����ת��ΪCSipCapSet����
PROTO_API BOOL32 kdvsdp_build_capset(TSdpHandle hHandle, CSipCapSet *pcCap);

PROTO_API void sdpregfunlinux();

PROTO_API BOOL32 sdpIsTps(emEndpointType m_emEndpointType);
//���Խӿ�
PROTO_EXTERN_API void sdphelp();

PROTO_EXTERN_API void sdplogon(s32 nLevel);

PROTO_EXTERN_API void sdplogoff();

PROTO_EXTERN_API void sdpver();

PROTO_EXTERN_API void sdplogto(u8 byFilter);

#endif