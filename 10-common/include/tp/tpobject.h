#ifndef _h_tpobject_h__
#define _h_tpobject_h__

#include "tplog.h"

#define ev_kdvmsg_sys_init OSP_USEREVENT_BASE + 1
#define ev_kdvmsg_sys_exit OSP_USEREVENT_BASE + 2
#define ev_kdvmsg_sys_init_ind OSP_USEREVENT_BASE + 3

namespace UmsTpmsg {

extern u32 g_dwSysApp;

class CTpMsg;
class CTpObject : public CTpLog, public CInstance
{
public:
	CTpObject();
	virtual ~CTpObject();

	friend class CTpHandler;

protected:
	BOOL32    m_bInit;//初始化标志
private:
    virtual void DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp );
	void InstanceEntry(CMessage *const ptMsg);
protected:
	
	virtual void MessageProc(CTpMsg *const ptMsg) {};
	virtual void DaemonMessageProc(CTpMsg *const ptMsg,CApp* pcApp){}

	virtual BOOL32 DaemonObjectInit(u32 wParam, u32 lParam);
	virtual void DaemonObjectExit(void);
	virtual BOOL PreDaemonMessageProc( CMessage *const ptMsg )	{	return FALSE; }
	
protected:
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam) = 0;
	virtual void ObjectExit(void);
	
	virtual BOOL PreMessageProc( CMessage *const ptMsg )	{	return FALSE; }

public:
	virtual u16  GetLogApp()				{ return GetAppID(); }	
	virtual u16  GetLogInst()				{ return GetInsID(); }	
	void SetLogTitle( s8* title );//设置日志打印标题
};

} //namespace UmsTpmsg

#endif // _h_tpobject_h__
