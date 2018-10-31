#ifndef UMC_HANDLER_H
#define UMC_HANDLER_H
#include "tphandle.h"
#include "usermanage.h"
#include "umsinnerstruct.h"
#include "tpvector.h"

class CUmcHandler : public CTpHandler
{
public:
	CUmcHandler(CTpObject* pcObject, u32 dwUmcAppID);
	virtual ~CUmcHandler();
	
public:
	virtual BOOL32 Handler(CTpMsg* const ptMsg);

public:
	//处理前置的信息
	BOOL32			PreHandler(CMessage* const ptMsg);
	//显示登录用户的信息
	void			ShowLogin();

private:
	//用户登录处理
	void			EventUserLogin(CMessage* const ptMsg);
	//添加用户
	void			EventAddUserReq(CMessage* const ptMsg);
	//删除用户
	void			EventDelUser(CMessage* const ptMsg);
	//修改用户密码
	void			EventChangePwdReq(CMessage* const ptMsg);
	//断链处理
	void			EventDisconnect(CMessage* const ptMsg);

private:
	//打印事件的信息，主要供测试使用
	void			PrintEventInfo(CTpMsg* const ptMsg);
	//打印从界面来的消息
	void			PrintEventInfoFromUI(CTpMsg* const ptMsg);
private:
	CUsrManage			m_cUserMG;		//用户管理
	CTpVector<TLogUser> m_tLogUser;		//已经登录的用户
	u32					m_dwUmcAppID;	//UMCAPPID
};	

#endif