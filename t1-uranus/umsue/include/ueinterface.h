#ifndef _h_ueinterface_h__
#define _h_ueinterface_h__

#include "umsobject.h"
#include "usermanage.h"
#include "umsinnerstruct.h"
#include "tpvector.h"
#include "umchandler.h"
#include "toolhandler.h"

class CUsrManage;
class CUmsUeInst :  public CUmsObject
{
public:
    CUmsUeInst();
	~CUmsUeInst();

public:
	u16				NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser);
	u16				NotifyMsgToHdu(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser);
	
protected:
	virtual BOOL	PreMessageProc ( CMessage *const ptMsg ); 
	virtual void	MessageProc( CTpMsg *const ptMsg);
	virtual BOOL32	ObjectInit(u32 wParam, u32 lParam);
	virtual void	ObjectExit();
	virtual void	InstanceDump(u32=0);
	
protected:
	//显示UMC用户登录信息
	void			ShowLogin();
	//显示维护工具登录用户信息
	void			ShowToolLogin();

private:
	void			OnDisconnect(CMessage *const ptMsg);
	//分发PreMessageProc消息
	void			DispatchPreMsg(CMessage* const pMsg);

private:
	static CUmcHandler*		m_pcUmcHandler;		//UMC用户处理接口
	static CToolHandler*	m_pcToolHandler;	//维护工具处理接口

private:
	u32		m_dwUmcAppID;	//UMC的APPID
	u32		m_dwToolAppID;	//维护工具的APPID
	u32		m_dwListenNode;	//监听节点
	u32		m_dwServiceInst;
};

typedef zTemplate<CUmsUeInst, 1> CUmsUeApp;


#endif // _h_ueinterface_h__
