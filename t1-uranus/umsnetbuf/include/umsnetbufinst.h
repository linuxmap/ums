#ifndef _h_umsnetbufinst_h__
#define _h_umsnetbufinst_h__


#include "tpobject.h"
#include "tphandle.h"
#include "dataswitch.h"
class CNbData;
class CTpNetBufInst :  public CTpObject
{
public:
    CTpNetBufInst();

public:
	void RegTimeOut(u32 dwTime);

protected:
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit();
protected:
	virtual void InstanceDump(u32=0);
	
protected:
	void MessageProc(CTpMsg *const ptMsg);	

	void OnDisConnect(CTpMsg *const ptMsg);
	void OnRegSuccess(CTpMsg *const ptMsg);
	void OnIFrameCheck(CTpMsg *const ptMsg);
	
	void OnCreateMediaTrans(CTpMsg *const ptMsg);
	void OnDestroyMediaTrans(CTpMsg *const ptMsg);
	
	void OnCreateMediaNetBuf(CTpMsg *const ptMsg);
	void OnDestroyMediaNetBuf(CTpMsg *const ptMsg);

	void ConnectToUms();

protected:
	void OnMsgFromCall(CTpMsg *const ptMsg);	


private:
	CNbData* m_pcNbData;
};

typedef zTemplate<CTpNetBufInst, 1> CTpUmsNetbufApp;





#endif // _h_umsnetbufinst_h__
