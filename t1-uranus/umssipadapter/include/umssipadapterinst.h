#ifndef _h_umsapp_h__
#define _h_umsapp_h__

#include "tpobject.h"
#include "tphandle.h"
#include "umscommonstruct.h"

enum EmAppState
{
	AppIdle ,//空闲
	AppStarting,//正在启动
	AppRunning//运行
};

class CTpTimerMgr;
class CTpSipAdapterServer :  public CTpObject
{
public:
    CTpSipAdapterServer();

protected:
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit();

protected:
	BOOL PreMessageProc( CMessage *const ptMsg )
	{
		if ( OSP_DISCONNECT == ptMsg->event )
		{
			OnDisConnect( ptMsg );
			return TRUE;
		}
		return FALSE;
	}
	void MessageProc(CTpMsg *const ptMsg);	

	void OnDisConnect(CMessage *const ptMsg);
	void OnRegSuccess(CTpMsg *const ptMsg);
	void OnSipInitAdapterInd(CTpMsg *const ptMsg);

	void ConnectToUms();

protected:
	void OnMsgFromCall(CTpMsg *const ptMsg);
    void ProcQtMsgFromCall(const TUmsHandle& tHandle, const s32 wEvent, u8 *pBuf, const s32 nSize);

private:

};

typedef zTemplate<CTpSipAdapterServer, 1> CTpUmsSipAdapterApp;





#endif // _h_umsapp_h__
