#ifndef _h_umsobject_h__
#define _h_umsobject_h__

#include "umsinnerstruct.h"


#include "osp.h"
#include "tpobject.h"
#include "tplog.h"

#define UMS_OpenWdGuard_Param   60
#define UMS_WdGuardNotice_TIME	3

#define UMS_DB_APP_INST			MAKEIID(AID_UMSDB_APP, 1)

#define UMS_SIP_APP_INST		MAKEIID(AID_UMSSIP_APP, 1)

#define UMS_UE_APP_INST			MAKEIID(AID_UMSUE_APP, 1)

#define UMS_SERVICE_APP_INST	MAKEIID(AID_UMSSERVER_APP,1)

#define UMS_MEDIADS_APP_INST	MAKEIID(AID_UMSMEDIADS_APP, 1)

#define UMS_XMPU_APP_INST		MAKEIID(AID_UMSXMPU_APP, 1)

#define UMS_CALL_APP_INST( inst ) MAKEIID(AID_UMSCONFMGR,inst)

#define UMS_BRDSSN_APP_INST		MAKEIID( AID_UMSBRD_SSN_APP,1 )
#define UMS_BRDREG_APP_INST		MAKEIID( AID_UMSBRD_REG_APP,1 )
#define UMS_BOARD_APP_INST		MAKEIID(AID_UMSBOARD_APP, 1)


#define UMS_EQP_APP_INST		MAKEIID(AID_UMSEQP_APP, 1)
#define UMS_SIPADAPTER_APP_INST	MAKEIID(AID_UMSSIPADAPTER_APP, 1)
#define UMS_AUDIOMIX_APP_DEAMON_INST	MAKEIID(AID_UMSAUDIOMIX_APP, CInstance::DAEMON)
#define UMS_MPC_APP_INST		MAKEIID(AID_UMSMPC_APP, 1)
#define UMS_MEDIATRANS_APP_INST	MAKEIID(AID_UMSMEDIATRANS_APP, 1)
#define UMS_NETBUF_APP_INST		MAKEIID(AID_UMSNETBUF_APP, 1)
#define UMS_AGENT_APP_INST		MAKEIID(AID_UMSAGENT_APP, 1)
#define UMS_GUARD_APP_INST		MAKEIID(AID_UMSGUARD_APP, 1)

u32	GetLocalIP();	//UMS地址

//ums模块类型定义
enum EmUmsMdlType
{
	Ums_Mdl_Ue = MID_UMS_1,
	Ums_Mdl_Cfg = MID_UMS_2,
	Ums_Mdl_Service = MID_UMS_3,
	Ums_Mdl_Call = MID_UMS_4,
	Ums_Mdl_Stack = MID_UMS_5,	
	Ums_Mdl_Media = MID_UMS_6,
	Ums_Mdl_Eqp = MID_UMS_7,
	Ums_Mdl_AudioMix = MID_UMS_8,
	Ums_Mdl_Mpc = MID_UMS_9,
	Ums_Mdl_Agent = MID_UMS_10,
	Ums_Mdl_Board = MID_UMS_11,
	Ums_Mdl_Mpu2TP = MID_UMS_12,

	Ums_Mdl_RegServer = MID_UMS_15,
	Ums_Mdl_UpdateSer = MID_UMS_16,
	Ums_Mdl_Xmpu = MID_UMS_17
};

//从SERVICE广播消息到所有CMS
void TPBroadMsgToUi(u16 wEvent, u8* pDataBuf, u16 wDataSize);
//从SERVICE发送消息到对应CMS，用户消息包还在pDataBuf的起始位置
void TPTransMsgToUi(u16 wEvent, u8* pDataBuf, u16 wDataSize);

//Service向UE发送消息
u16 TpNotifyMsgToUeFromService(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser);

u16 TpNotifyMsgToToolUserFromService(u16 wEvent, void* body, u16 bodyLen);

u16 UmsNotifyMsgToService(u16 wEvent, void* body, u16 bodyLen);

u16 UmsNotifyMsgToEqp(u16 wEvent, void* body, u16 bodyLen);

void NotifyCall( u16 wEvent, void* pBuf, u16 dwLen );

void NotifyMsgToConfInst(u16 wEvent, void* pBuf, u16 wLength, u16 wConfID);

u16 UmsNotifyMsgToXmpuEqp(u16 wEvent, void* body, u16 bodyLen);

//判断用户是否是维护工具用户
BOOL32	IsToolUser(const TLogUser& tUser);

#define CUmsObject CTpObject





#endif // _h_umsobject_h__
