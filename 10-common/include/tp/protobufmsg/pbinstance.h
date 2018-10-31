#ifndef _PB_INSTANCE_H_
#define _PB_INSTANCE_H_

#include <map>
#include "pbmsg.h"
#include "logclientapi.h"
#include "osp.h"

namespace pbmsg {

// OSP event
#define Ev_OSP_PBInst_Init					OSP_USEREVENT_BASE + 1
#define Ev_OSP_PBInst_Exit					OSP_USEREVENT_BASE + 2
#define Ev_OSP_PBInst_PBMsg					OSP_USEREVENT_BASE + 3

class CPBInstance;

// pb消息处理函数
typedef BOOL32 (CPBInstance::*PFPBMsgFunc)(CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode);
// CMessage处理函数
typedef BOOL32 (CPBInstance::*PFMsgFunc)(CMessage* const pcMsg);

class PROTOBUFMSG_API CPBInstance : public log4cpclient::CLogBase , public CInstance
{

public:
	virtual ~CPBInstance(){
		m_bInit = FALSE;
	}

protected:
	CPBInstance(){
		m_bInit = FALSE;
	}

	// 初始化
	virtual BOOL32	InstInit(u32 dwParam) = 0;
	virtual BOOL32	DaemonInstInit(u32 dwParam, CApp* pcApp) = 0;

	// 退出
	virtual void	InstExit() = 0;
	virtual void	DaemonInstExit() = 0;

	// pb消息处理入口
	virtual BOOL32	PBMessageProc(CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode) = 0;
	virtual BOOL32	DaemonPBMessageProc(CPBMsg* pcPBMsg, CApp* pcApp, u32 dwSrcId, u32 dwSrcNode) = 0;

	// CMessage消息处理入口
	virtual BOOL32	MessageProc(CMessage* const pcMsg) = 0;
	virtual BOOL32	DaemonMessageProc(CMessage* const pcMsg, CApp* pcApp) = 0;

	// 用于注册pb消息和实现函数的映射，需要在消息入口函数调用HandlePBMsg
	BOOL32	RegPBMsgFunc(std::string strMsgName, PFPBMsgFunc pPBMsgFunc);
	BOOL32	UnRegPBMsgFunc(std::string strMsgName);
	BOOL32	IsPBMsgFuncReg(std::string strMsgName);
	void	ClearPBMsgFunc();
	BOOL32	HandlePBMsg(CPBMsg* pcPBMsg, u32 dwSrcId, u32 dwSrcNode);

	// 用于注册CMessage消息和实现函数的映射，需要在消息入口函数调用HandleMsg
	BOOL32	RegMsgFunc(u16 wEvent, PFMsgFunc pMsgFunc);
	BOOL32	UnRegMsgFunc(u16 wEvent);
	BOOL32	IsMsgFuncReg(u16 wEvent);
	void	ClearMsgFunc();
	BOOL32	HandleMsg(CMessage* const pcMsg);

private:
	// app实例消息处理的入口，使用者继承此类无需再重载
	virtual void DaemonInstanceEntry( CMessage* const pMsg, CApp* pcApp);
	virtual void InstanceEntry( CMessage* const pMsg);

private:
	BOOL32									m_bInit;
	std::map<std::string, PFPBMsgFunc>		m_mapPBMsgFunc; //pb消息处理函数map
	std::map<u16, PFMsgFunc>				m_mapMsgFunc; //CMessage消息处理函数map
};

}// namespace pbmsg

#endif //_PB_INSTANCE_H_