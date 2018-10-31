#include "tptype.h"
#include "umsinnertype.h"
#include "kdvtype.h"


s8* UmsNodeConfType(EmUmsConfNodeState emType)
{
	switch(emType)
	{
	case ums_UmsConfNodeState_unused:
		return "unused";
	case ums_UmsConfNodeState_uncall:
		return "uncall";
	case ums_UmsConfNodeState_calling:
		return "calling";
	case ums_UmsConfNodeState_callfailed:
		return "failed";
	case ums_UmsConfNodeState_online:
		return "online";
	case ums_UmsConfNodeState_stopcall:
		return "stopcall";
	default:
		return "default";
	}
	return "default";
}

s8* UmsNodeType(EmTPEndpointType emType)
{
	switch(emType)
	{
	case emTPEndpointTypeUnknown:
		return "UNknow";
	case emTPEndpointTypeCNS:
		return "CNS";
	case emTPEndpointTypeUMS:
		return "UMS";
	case emTPEndpointTypeRegister:
		return "Register";
	case emTPEndpointH323MT:
		return "MT";
	case emTPEndpointH323MCU:
		return "MCU";
	case emTPEndpointH323SingleMCU:
		return "SMCU";
	case emTPEndpointH323G400:
		return "G400";
	case emTPEndPointVrs:
		return "VRS";
	default:
		return "default";
	}
	return "default";
}
s8* UmsCallProto(EmTpConfProtocol emType)
{
	switch(emType)
	{
	case emTpH323:
		return "H323";
	case emTpH320:
		return "H320";
	case emTpSIP:
		return "SIP";
	case emTpSat:
		return "SAT";
	case emTpInvalidConfProtocel:
		return "Invalid";
	default:
		return "default";
	}
	return "default";
}