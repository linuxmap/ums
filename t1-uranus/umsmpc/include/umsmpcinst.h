#ifndef _h_umsmpcinst_h__
#define _h_umsmpcinst_h__

#include "tpobject.h"
#include "tphandle.h"
#include "tpsys.h"
#include "umscommonstruct.h"
#include "umsinnerstruct.h"
#include "umsmpcmain.h"

BOOL StartMpcServer();
void StopMpcServer();

class CTpMpcInst :  public CTpObject
{
public:
    CTpMpcInst();
	~CTpMpcInst();
protected:
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit();
	void InstanceDump(u32 wParam);
public:
protected:
	void MessageProc(CTpMsg *const ptMsg);	
	
	void OnDisConnect(CTpMsg *const ptMsg);
	void OnRegSuccess(CTpMsg *const ptMsg);
	void OnConnectToUms();
	void OnSetMpcTime(CTpMsg *const ptMsg);
	void OnIsMasterMpc(CTpMsg *const ptMsg);
	void OnReboot(CTpMsg *const ptMsg);
	void ShowMpc();
	
public:
	u16	m_wMdlIndex;          //主控索引
	
	u32 m_dwUmsNode;
	u32	m_dwWdGuardTime;
	BOOL32 m_bMaster;
	BOOL32 m_bRegRtn;   //注册结果
};



typedef zTemplate<CTpMpcInst, TP_UMS_MAX_CONFNUM> CTpUmsMpcApp;

#endif // _h_umsmpcinst_h__


