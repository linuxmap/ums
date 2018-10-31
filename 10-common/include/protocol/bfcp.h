#ifndef _BFCP_H
#define _BFCP_H
#include "bfcp_messages.h"

/* Main Function */

PROTO_API BOOL32 bfcp_init_client(s32 nTransport, u32 dwConfId, u16 wUserId, void *pCapset, bfcp_nonstd *ptNonstd, TRequestAddress *ptAddress, CB_BFCPNOTIFY fpNotifier, TBfcpTlsCfg *ptBfcpTlsCfg =NULL);
PROTO_API BOOL32 bfcp_init_server(BOOL32 bAutoAnswer, s32 nTransport, u16 wMaxConf, u16 wPortServer, bfcp_nonstd *ptNonstd, TBfcpTlsCfg *ptBfcpTlsCfg, CB_BFCPNOTIFY fpNotifier);
PROTO_API BOOL32 bfcp_destroy_client(void *pCap);
PROTO_API BOOL32 bfcp_destroy_server();

PROTO_API BOOL32 bfcp_client_update_remote_port(void *pCap, u32 dwPort);
PROTO_API BOOL32 bfcp_client_send_message(s32 nPrimitive, bfcp_attribute_info *ptAttribute, bfcp_nonstd *ptNonstd, void *pCap);
PROTO_API BOOL32 bfcp_server_send_message(s32 nRcvPrimitive, s32 nPrimitive, bfcp_entity *ptEntity, bfcp_attribute_info *ptAttribute, bfcp_nonstd *ptNonstd, sockaddr_in *ptAddress);

PROTO_API BOOL32 bfcp_client_add_floor(u16 wFloorId, void *pCap);
PROTO_API BOOL32 bfcp_client_delete_floor(u16 wFloorId, void *pCap);

PROTO_API BOOL32 bfcp_server_add_conference(u32 dwConfId, u16 wMaxFlrsNum, u16 wMaxNumFlrReq, s32 nAutoPolicy, u32 dwChairWait);
PROTO_API BOOL32 bfcp_server_delete_conference(u32 dwConfId);
PROTO_API BOOL32 bfcp_server_add_floor(u32 dwConfId, u16 wFloorId, u16 wChairId, s32 nLimitGrantedFloor);
PROTO_API BOOL32 bfcp_server_delete_floor(u32 dwConfId, u16 wFloorId);
PROTO_API BOOL32 bfcp_server_add_user(u32 dwConfId, u16 wUserId, s8 *pchUri, s8 *pchDisplayName);
PROTO_API BOOL32 bfcp_server_delete_user(u32 dwConfId, u16 wUserId);
PROTO_API BOOL32 bfcp_server_add_chair(u32 dwConfId, u16 wFloorId, u16 wChairId);
PROTO_API BOOL32 bfcp_server_delete_chair(u32 dwConfId, u16 wFloorId);
PROTO_API BOOL32 bfcp_server_add_client_information(void *pAppPoint, sockaddr_in *ptAddress, u32 dwConfId);
PROTO_API BOOL32 bfcp_server_update_client_information(void *pAppPoint, sockaddr_in *ptAddress);
PROTO_API BOOL32 bfcp_server_delete_client_information(void *pAppPoint, u32 dwConfId);

PROTO_API BOOL32 bfcp_server_change_max_conference_number(u16 wNumber);
PROTO_API BOOL32 bfcp_server_change_granted_floor_number(u32 dwConfId, u16 wFloorId, u16 wLimitGrantedFloor);
PROTO_API BOOL32 bfcp_server_change_user_req_floors_number(u16 wMaxNumFlrReq);
PROTO_API BOOL32 bfcp_chair_change_policy(u32 dwConfId, s32 nAutoPolicy, u32 dwChairWait);
PROTO_API void RegBfcpFunLinux();
#ifdef _ENABLE_QUANTUM_PROJECT_
PROTO_API void bfcp_set_qt_handle(u32 dwPeerMtIp, QTBFCPHANDLE hBfcpHandle, s8 szBfcpID[QT_UNIQUE_ID_MAX_LEN+1]);
#endif

/* Print or Debug Function */
PROTO_EXTERN_API void bfcphelp();
PROTO_EXTERN_API void bfcplogon(s32 nLevel);
PROTO_EXTERN_API void bfcplogoff();
PROTO_EXTERN_API void bfcpver();
PROTO_EXTERN_API void bfcpcltshow();
PROTO_EXTERN_API void bfcpsrvshow();

#endif
