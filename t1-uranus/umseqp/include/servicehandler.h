#ifndef __service_handler_h_
#define __service_handler_h_

#include "tpsys.h"
#include "tptype.h"
#include "tpmsg.h"

using namespace UmsTpmsg;

class CTPMcuBrdSsn;

//����ҵ����Ϣ����ӿ�
class IServiceHandler
{
public:
	IServiceHandler()
	{
	}
	virtual ~IServiceHandler(){}

public:
	//��������ҵ�����Ϣ
	virtual BOOL32		MsgFromServiceHandler(CMessage* const ptMsg, CTPMcuBrdSsn* pInst) = 0;
	//��������EQP����Ϣ
	virtual BOOL32		MsgFromEqpHandler(CTpMsg* const ptMsg, CTPMcuBrdSsn* pInst) = 0;
};

#endif