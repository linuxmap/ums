#ifndef TOOL_HANDLER_H
#define TOOL_HANDLER_H
#include "tphandle.h"
#include "umsinnerstruct.h"

//维护工具用户信息管理
class CToolHandler : public CTpHandler
{
public:
	CToolHandler(CTpObject* pcObject, u32 dwToolAppID);
	virtual ~CToolHandler();

public:
	virtual BOOL32 Handler(CTpMsg* const ptMsg);

public:
	//处理前置的信息
	BOOL32			PreHandler(CMessage* const ptMsg);
	//显示登录用户的信息
	void			ShowLogin();

private:
	//用户登录
	void			EventUserLogin(CMessage* const ptMsg);
	//断链处理
	void			EventDisconnect(CMessage* const ptMsg);

private:
	//打印事件的信息，主要供测试使用
	void			PrintEventInfo(CTpMsg* const ptMsg);
	//打印从界面来的消息
	void			PrintEventInfoFromUI(CTpMsg* const PtMsg);

private:
	TLogUser		m_tCurLogUser;	//当前登录用户
	u32				m_dwToolAppID;	//维护工具APPID

	BOOL32          m_bLockflag;     //锁定
	u32             m_dwLockReason;   //锁定理由，UE 只保存不解释         
};

#endif