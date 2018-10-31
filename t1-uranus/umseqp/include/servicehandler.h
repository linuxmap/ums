#ifndef __service_handler_h_
#define __service_handler_h_

#include "tpsys.h"
#include "tptype.h"
#include "tpmsg.h"

using namespace UmsTpmsg;

class CTPMcuBrdSsn;

//定义业务消息处理接口
class IServiceHandler
{
public:
	IServiceHandler()
	{
	}
	virtual ~IServiceHandler(){}

public:
	//处理来自业务的消息
	virtual BOOL32		MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst) = 0;
	//处理来自EQP的消息
	virtual BOOL32		MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst) = 0;
};

#endif