#include "xmpuinnerstruct.h"

CEqpBaseHandle::CEqpBaseHandle( CUmsXmpuInst* pInst )
	:m_pcInst(pInst)
{

}

CEqpBaseHandle::~CEqpBaseHandle()
{

}

void CEqpBaseHandle::Init()
{

}

void CEqpBaseHandle::NotifyMsgToEqp( u32 dwDstNode, u32 dwDstInst, u16 wEvent, void* body, u16 bodyLen )
{
	CTpMsg cMsg;
	cMsg.SetEvent(wEvent);
	cMsg.SetBody(body, bodyLen);
	cMsg.Post(dwDstInst, dwDstNode, UMS_XMPU_APP_INST);
}


void CEqpBaseHandle::Show()
{

}
void CEqpBaseHandle::ShowAll()
{

}

s8* GetXmpuEqpStatBuf( EmXmpuEqpStat emStat )
{
	switch(emStat)
	{
	case XmpuEqpStat_Idle:
		return "Idle";
		break;
	case XmpuEqpStat_Starting:
		return "Starting";
		break;
	case XmpuEqpStat_Running:
		return "Running";
		break;
	case XmpuEqpStat_Error:
		return "Error";
		break;
	default:
		return "InvalidStat";
		break;
	}

	return NULL;
}

s8* GetSynType( u16 wIndex )
{
	switch(wIndex)
	{
	case em_Xmpu_Mix_SpeakerEp:
		return "em_Xmpu_Mix_SpeakerEp";
		break;
	case em_Xmpu_Mix_OtherThreeEp:
		return "em_Xmpu_Mix_OtherThreeEp";
		break;
	case em_Xmpu_AudBas_SpeakerEp:
		return "em_Xmpu_AudBas_SpeakerEp";
		break;
	case em_Xmpu_AudBas_ChairEp:
		return "em_Xmpu_AudBas_ChairEp";
		break;
	default:
		return "em_Xmpu_SynIndex_End";
		break;
	}

	return NULL;
}