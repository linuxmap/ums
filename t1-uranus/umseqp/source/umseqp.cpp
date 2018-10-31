#include "umseqp.h"

#if defined(_PPC_82XX_) || defined(_PPC_85XX_)
#include "stdlib.h"
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/types.h>
#endif


CEqpBase::CEqpBase(CUmsEqpInst* pInst)
:m_pcInst(pInst)
{

}

CEqpBase::~CEqpBase()
{
}



void CEqpBase::Init()
{

}

void CEqpBase::Show()
{
	
}


void CEqpBase::NotifyMsgToEqp(u32 dwDstNode, u32 dwDstInst, u16 wEvent, void* body, u16 bodyLen)
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(body, bodyLen);
	cMsg.Post(dwDstInst, dwDstNode, UMS_EQP_APP_INST);
}


