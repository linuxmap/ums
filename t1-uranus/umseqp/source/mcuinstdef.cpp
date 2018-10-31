#include "mcuinstdef.h"
#include "umsobject.h"

void SendMsgToEqp( u16 wEvent, u8 * const pbyMsg, u16 wLen, u16 wInsID, u32 dwNode )
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	if ( NULL != pbyMsg )
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSBRD_SSN_APP, wInsID), dwNode);
}

void SendMsgToEqpSsn(u32 dwDstIID, u16 wEvent, u8 * const pbyMsg, u16 wLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(pbyMsg, wLen);
	cMsg.Post(dwDstIID, 0, UMS_EQP_APP_INST);
}

void SendMsgToServer(u16 wEvent, u8* pbyMsg /* = NULL */, u16 wLen /* = 0 */)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	
	if (NULL != pbyMsg)
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	
	cMsg.Post(UMS_SERVICE_APP_INST, 0, UMS_EQP_APP_INST);
}

void SendMsgToCall(u16 wEvent, u8* pbyMsg /* = NULL */, u16 wLen /* = 0 */)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	
	if (NULL != pbyMsg)
	{
		cMsg.SetBody(pbyMsg, wLen);
	}
	
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), 0, UMS_EQP_APP_INST);
}