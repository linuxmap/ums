#ifndef HANDLE_TOOL_SERVICE_H
#define HANDLE_TOOL_SERVICE_H
#include "tphandle.h"
#include "umsinnerstruct.h"

//处理维护工具相关信息的获取
class CUmsToolHandleService : public CTpHandler
{
public:
	CUmsToolHandleService(CTpObject* pcObjec);
	~CUmsToolHandleService();

public:
	virtual BOOL32 Handler( CTpMsg *const ptMsg );
	
public:
	//更新正在开会的数量到维护工具
	void	UpdateConfCount();

private:
	//处理用户登录信息
	void	EventLogin();
	//获取系统信息包括CPU 和内存
	void	EventSysInfo();
	//获取正在开会的会议数量
	void	EventConfCount();
	//重启UMS
	void	EventRebootUms();
	//查询授权使用数量
	void	EventAuthCount();
	void	EventAuthCountNty(u16 wEvent, u8* pDataBuf, u16 wDataSize);

	void 	EventLicenseOutputReq();

	//电视墙使用情况
	void	EventHduCount();

private:
};

#endif