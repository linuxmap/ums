#ifndef _h_umsbrd_h__
#define _h_umsbrd_h__

#include "tptype.h"
#include "tpobject.h"

typedef void (*StartUpCallBack)();

BOOL StartupBrd(EMEqpType* aemMdlType, StartUpCallBack* atFun, u16 wMdlNum);
void StopBrd();

u32 GetConnNode();


class CTpBrdInst :  public CTpObject
{
public:
    CTpBrdInst();
	
public:
	
protected:
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit();
protected:
	virtual void InstanceDump(u32=0);
protected:
	void MessageProc(CTpMsg *const ptMsg);	
		
protected:
	void OnRegSuccess(CTpMsg *const ptMsg);
	void OnConnectToUms();
	void OnDisConnect();
	
private:

};



#endif // _h_umsbrd_h__
