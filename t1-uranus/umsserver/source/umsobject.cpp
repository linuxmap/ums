#include "umsobject.h"
#include "tpsys.h"
#include "eventtpsys.h"
#include "msgmgr.h"


u16 TpNotifyMsgToUeFromService(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tLogUser, sizeof(tLogUser));
	
	if (NULL != body)
	{
		cMsg.CatBody(body,bodyLen);
	}
	return cMsg.Post(UMS_UE_APP_INST,0,UMS_SERVICE_APP_INST);
}

u16 TpNotifyMsgToToolUserFromService(u16 wEvent, void* body, u16 bodyLen)
{
	TLogUser tUserTmp;
	tUserTmp.m_dwUserInst = MAKEIID(AID_UMSTOOL2UMS_APP, 0);
	
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(&tUserTmp, sizeof(tUserTmp));
	
	if (NULL != body)
	{
		cMsg.CatBody(body,bodyLen);
	}
	return cMsg.Post(UMS_UE_APP_INST,0,UMS_SERVICE_APP_INST);
}

u16 UmsNotifyMsgToService(u16 wEvent, void* body, u16 bodyLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(body, bodyLen);
	return cMsg.Post(UMS_SERVICE_APP_INST);
}

u16 UmsNotifyMsgToEqp(u16 wEvent, void* body, u16 bodyLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(body, bodyLen);
	
	return cMsg.Post(MAKEIID(AID_UMSEQP_APP, 1), 0, UMS_SERVICE_APP_INST);
}


void TPBroadMsgToUi(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TLogUser tUserTmp;
	TpNotifyMsgToUeFromService(wEvent, pDataBuf, wDataSize, tUserTmp);
}


void TPTransMsgToUi(u16 wEvent, u8* pDataBuf, u16 wDataSize)
{
	TLogUser* ptUser = (TLogUser*)pDataBuf;
	TpNotifyMsgToUeFromService(wEvent, pDataBuf + sizeof(TLogUser), wDataSize - sizeof(TLogUser), *ptUser);
}

void NotifyCall( u16 wEvent, void* pBuf, u16 dwLen )
{
	CTpMsg cMsg;
	cMsg.SetEvent( wEvent );
	cMsg.SetBody( pBuf, dwLen );
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, UMS_SERVICE_APP_INST);
}

void NotifyMsgToConfInst(u16 wEvent, void* pBuf, u16 wLength, u16 wConfID)
{
	CTpMsg cMsg;
	cMsg.SetEvent( wEvent );
	cMsg.SetBody( pBuf, wLength );
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, wConfID), 0, UMS_SERVICE_APP_INST);
}

BOOL32 IsToolUser( const TLogUser& tUser )
{
	return GETAPP(tUser.m_dwUserInst) == AID_UMSTOOL2UMS_APP;
}

u16 UmsNotifyMsgToXmpuEqp(u16 wEvent, void* body, u16 bodyLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(body, bodyLen);

	return cMsg.Post(UMS_XMPU_APP_INST, 0, UMS_SERVICE_APP_INST);;
}
