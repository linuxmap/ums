#include "stackmsgconvert.h"

void ConverRegNameFromUmsToStack(const TTPAlias& tAlias, TSipRegName& tPAName)
{
	switch(tAlias.m_byType)
	{
		case tp_Alias_e164:
			{
				tPAName.m_emSipAddrType = emUrlE164Num;
				strncpy(tPAName.m_achUserName, tAlias.m_abyAlias, sizeof(tPAName.m_achUserName));
			}
			break;
		case tp_Alias_h323:
			{
				tPAName.m_emSipAddrType = emUrlAlias;
				strncpy(tPAName.m_achUserName, tAlias.m_abyAlias, sizeof(tPAName.m_achUserName));
			}
			break;
		default:
			OspPrintf(TRUE, FALSE, "[ConverRegNameFromUmsToStack]! alias type error:%d\n", tAlias.m_byType);
			break;
	}
}
BOOL32 ConverRegNameFromStackToUms(const TSipRegName& tPAName, TTPAlias& tAlias)
{
	switch(tPAName.m_emSipAddrType)
	{
	case emUrlE164Num:
		{
			tAlias.m_byType = tp_Alias_e164;
			strncpy(tAlias.m_abyAlias, tPAName.m_achUserName, sizeof(tAlias.m_abyAlias));
		}
		break;
	case emUrlAlias:
		{
			tAlias.m_byType = tp_Alias_h323;
			strncpy(tAlias.m_abyAlias, tPAName.m_achUserName, sizeof(tAlias.m_abyAlias));
		}
		break;
	default:
		{
			OspPrintf(TRUE, FALSE, "[ConverRegNameFromStackToUms]! alias type error:%d\n", tPAName.m_emSipAddrType);
			return FALSE;
		}
		break;
	}
	return TRUE;
}

BOOL32 ConvertRegFromStackToApp(RegisterRequest& tStackInfo, TCnsRegInfo& tAppInfo)
{
	tAppInfo.m_tCsnNodeInfo.m_dwExpires = tStackInfo.m_dwExpires;
	tAppInfo.m_tCsnNodeInfo.m_nCSqence = tStackInfo.m_nCSqence;
	memcpy(tAppInfo.m_tCsnNodeInfo.m_aCallId, tStackInfo.m_achCallId, TP_MAX_NUM_CALLID);
	tAppInfo.m_tCsnNodeInfo.m_aCallId[TP_MAX_NUM_CALLID-1] = '\0';
	tAppInfo.m_dwCallType = u32(tStackInfo.m_emSipConnection);

	switch( tStackInfo.m_tLocalInfo.m_emEndpointType )
	{
	case emSipEndpointTypeUnknown:
		tAppInfo.m_tCsnNodeInfo.m_emSelfType = emTPEndpointTypeUnknown;
		break;
	case emSipEndpointTypeCNS:
		tAppInfo.m_tCsnNodeInfo.m_emSelfType = emTPEndpointTypeCNS;
		break;
	case emSipEndpointTypeUMS:
		tAppInfo.m_tCsnNodeInfo.m_emSelfType = emTPEndpointTypeUMS;
		break;
	case emSipEndpointTypeRegister:
		tAppInfo.m_tCsnNodeInfo.m_emSelfType = emTPEndpointTypeRegister;
		break;
	default:
		tAppInfo.m_tCsnNodeInfo.m_emSelfType = emTPEndpointTypeUnknown;
		break;
	}
	tAppInfo.m_tCsnNodeInfo.m_dwSelfAddr = tStackInfo.m_tLocalInfo.m_dwLocalIP/*tStackInfo*/;
	memcpy( tAppInfo.m_tCsnNodeInfo.m_aSelfVer, tStackInfo.m_tLocalInfo.m_achSoftVersion/*tStackInfo*/, sizeof( tAppInfo.m_tCsnNodeInfo.m_aSelfVer ));
	tAppInfo.m_tCsnNodeInfo.m_aSelfVer[TP_MAX_VERSION_LEN] = '\0';
	memcpy( tAppInfo.m_tCsnNodeInfo.m_aCompileTm, tStackInfo.m_tLocalInfo.m_achCompileTime/*tStackInfo*/, sizeof( tAppInfo.m_tCsnNodeInfo.m_aSelfVer ));
	tAppInfo.m_tCsnNodeInfo.m_aSelfVer[TP_MAX_VERSION_LEN] = '\0';

    tAppInfo.m_tCsnNodeInfo.m_dwSelfQtID = tStackInfo.m_dwQtID;

	u16 wMinSize = min(tStackInfo.m_nSipRegArraySize, TP_MAX_ALIAS_NUM);
	for (u16 wIndex = 0; wIndex < wMinSize; ++wIndex)
	{
		if (!ConverRegNameFromStackToUms(tStackInfo.m_atSipRegName[wIndex], tAppInfo.m_tCsnNodeInfo.m_atAlias[wIndex]))
		{
			return FALSE;
		}
	}
	tAppInfo.m_tCsnNodeInfo.m_wAliasNum = wMinSize;
	
	u32 dwMinNum = min(TP_MAX_NUM_CONTACT_ADDR, MAX_NUM_CONTACT_ADDR);
	for (u32 dwIndex = 0; dwIndex < dwMinNum; dwIndex++)
	{
		tAppInfo.m_tCsnNodeInfo.m_atCalledAddr[dwIndex].SetAddr(tStackInfo.m_atContactAddr[dwIndex].m_dwIP, tStackInfo.m_atContactAddr[dwIndex].m_wPort);
	}
	return TRUE;	
}	

void ConvertRegFromAppToStack(TCnsRegInfo& tAppInfo, RegisterRequest& tStackInfo)
{
	tStackInfo.m_emSipConnection = EmSipConnection(tAppInfo.m_dwCallType);
	tStackInfo.m_dwExpires = tAppInfo.m_tCsnNodeInfo.m_dwExpires;
	tStackInfo.m_nCSqence = tAppInfo.m_tCsnNodeInfo.m_nCSqence;
	memcpy(tStackInfo.m_achCallId, tAppInfo.m_tCsnNodeInfo.m_aCallId, MAX_NUM_CALLID);
	tAppInfo.m_tCsnNodeInfo.m_aCallId[MAX_NUM_CALLID-1] = '\0';
	
	u16 wMinSize = min(tAppInfo.m_tCsnNodeInfo.m_wAliasNum, MAX_NUM_REGNAME_SIZE);
	for (u16 wIndex = 0; wIndex < wMinSize; ++wIndex)
	{
		ConverRegNameFromUmsToStack(tAppInfo.m_tCsnNodeInfo.m_atAlias[wIndex], tStackInfo.m_atSipRegName[wIndex]);
	}
	tStackInfo.m_nSipRegArraySize = wMinSize;

	tStackInfo.m_dwQtID = tAppInfo.m_tCsnNodeInfo.m_dwSelfQtID;

	u32 dwMinNum = min(TP_MAX_NUM_CONTACT_ADDR, MAX_NUM_CONTACT_ADDR);
	for (u32 dwIndex = 0; dwIndex < dwMinNum; dwIndex++)
	{
		tStackInfo.m_atContactAddr[dwIndex].m_dwIP = tAppInfo.m_tCsnNodeInfo.m_atCalledAddr[dwIndex].GetIP();
		tStackInfo.m_atContactAddr[dwIndex].m_wPort = tAppInfo.m_tCsnNodeInfo.m_atCalledAddr[dwIndex].GetPort();
	}
}


void ConvertRegReasonFromAppToStack(TCnsRegRetResult& tAppRet, EmRegisterReason& tStackReason)
{
	tStackReason = emRegNone;
	switch (tAppRet.m_emReson)
	{
	case tp_CnsRegRet_Success:
		tStackReason = emRegSuc;
		break;
	case tp_CnsRegRet_MaxRegNum:
		tStackReason = emRegFail;
		break;
	case tp_CnsRegRet_MsgError:
		tStackReason = emRegFail;
		break;
	case tp_CnsRegRet_AliasRepeat:
		tStackReason = emRegNameDup;
		break;
	case tp_CnsRegRet_UnReg:
		tStackReason = emRegNotFound;
		break;
	case tp_CnsRegRet_SysError:
		tStackReason = emRegFail;
		break;
	case tp_CnsRegRet_NotFind:
		tStackReason = emRegNotFound;
		break;
	default:
		break;
	}
}


void ConvertRegInfoTypeToAppStack(EmGetRegInfoType tType, EmSIPRegNSMType& tSipType)
{
	switch (tType)
	{
	case emGetRegInfoType_CNS:		tSipType = emSipRegNSMType_CNS;
									break;
								
	case emGetRegInfoType_UMS:		tSipType = emSipRegNSMType_UMS;
									break;

	case emGetRegInfoType_ALL:		tSipType = emSipRegNSMType_ALL;
									break;
	}
}

void ConvertTpAliasTypeToAppStack(EmTpAliasType tType ,EmSipAliasType& tSipType)
{
	switch (tType)
	{
	case tp_Alias_Unknow:		tSipType = sip_Alias_Unknow;
								break;

	case tp_Alias_e164:			tSipType = sip_Alias_e164;
								break;

	case tp_Alias_h323:			tSipType = sip_Alias_h323;
								break;

	case tp_Alias_IP:			tSipType = sip_Alias_IP;
								break;
	}	
}

void ConvertPtTypeTpAppStack(EmTPEndpointType tType, EmSipEndpointType& tSipType)
{
	switch (tType)
	{
	case emTPEndpointTypeUnknown:		tSipType = emSipEndpointTypeUnknown;
										break;

	case emTPEndpointTypeCNS:			tSipType = emSipEndpointTypeCNS;
										break;

	case emTPEndpointTypeUMS:			tSipType = emSipEndpointTypeUMS;
										break;

	case emTPEndpointTypeRegister:		tSipType = emSipEndpointTypeRegister;
										break;
	}
}

void ConvertRegInfoFromAppToStack(const TReqRegInfoEx& tAppRegInfo, TSipRegPackXmlB2& tStackRegInfo)
{
	ConvertPtTypeTpAppStack(tAppRegInfo.m_emSelfType, tStackRegInfo.m_emEndpointType);
	ConvertRegInfoTypeToAppStack(tAppRegInfo.m_tRegType ,tStackRegInfo.m_emType);
	tStackRegInfo.m_wTotalRegInfo = tAppRegInfo.m_wDataNum;
	tStackRegInfo.m_tPackInfo.m_wTotalPackNum = tAppRegInfo.m_wTotalPackNum;
	tStackRegInfo.m_tPackInfo.m_wPackSeq = tAppRegInfo.m_wPackSeq;
}

void ConvertCnsRegInfoFromAppToStack(const TCnsRegData& tAppData, TSipRegInfoCns& tStackInfo)
{
	tStackInfo.emSipConnection = (EmSipConnection)tAppData.m_dwCallType;
	tStackInfo.m_wAliasNum = tAppData.m_wAliasNum;
	for (u16 wIndex = 0; wIndex < tAppData.m_wAliasNum; ++wIndex)
	{
		memcpy(tStackInfo.m_atAlias[wIndex].m_achAlias, tAppData.m_atAlias[wIndex].m_abyAlias, LEN_USERNAME);
		ConvertTpAliasTypeToAppStack(tAppData.m_atAlias[wIndex].m_byType, tStackInfo.m_atAlias[wIndex].m_emType); 
	}
	for (u16 wAddrIndex = 0; wAddrIndex < TP_MAX_NUM_CONTACT_ADDR; ++wAddrIndex)
	{
		tStackInfo.m_atContactAddr[wAddrIndex].m_dwIP  = tAppData.m_atCalledAddr[wAddrIndex].m_dwIP;
		tStackInfo.m_atContactAddr[wAddrIndex].m_wPort = tAppData.m_atCalledAddr[wAddrIndex].m_wPort;
	}
	tStackInfo.m_dwExpires = tAppData.m_dwExpires;
	memcpy(tStackInfo.m_tSipRegistLocalInfo.m_achCompileTime, tAppData.m_aCompileTm, LEN_USERNAME);
	memcpy(tStackInfo.m_tSipRegistLocalInfo.m_achSoftVersion, tAppData.m_aSelfVer, LEN_USERNAME);
	tStackInfo.m_tSipRegistLocalInfo.m_dwLocalIP = tAppData.m_dwSelfAddr;
	tStackInfo.m_tSipRegistLocalInfo.m_emEndpointType = emSipEndpointTypeCNS;
}

void ConvertUmsRegInfoFromAppToStack(const TUmsRegData& tAppData, TSipRegInfoUms& tStackInfo)
{
	tStackInfo.emSipConnection = (EmSipConnection)tAppData.m_dwCallType;
	tStackInfo.m_wAliasNum = tAppData.m_wAliasNum;
	for (u16 wIndex = 0; wIndex < tAppData.m_wAliasNum; ++wIndex)
	{
		memcpy(tStackInfo.m_atAlias[wIndex].m_achAlias, tAppData.m_atAlias[wIndex].m_abyAlias, LEN_USERNAME);
		ConvertTpAliasTypeToAppStack(tAppData.m_atAlias[wIndex].m_byType, tStackInfo.m_atAlias[wIndex].m_emType); 
	}
	for (u16 wAddrIndex = 0; wAddrIndex < TP_MAX_NUM_CONTACT_ADDR; ++wAddrIndex)
	{
		tStackInfo.m_atContactAddr[wAddrIndex].m_dwIP  = tAppData.m_atCalledAddr[wAddrIndex].m_dwIP;
		tStackInfo.m_atContactAddr[wAddrIndex].m_wPort = tAppData.m_atCalledAddr[wAddrIndex].m_wPort;
	}
	tStackInfo.m_dwExpires = tAppData.m_dwExpires;
	memcpy(tStackInfo.m_tSipRegistLocalInfo.m_achCompileTime, tAppData.m_aCompileTm, LEN_USERNAME);
	memcpy(tStackInfo.m_tSipRegistLocalInfo.m_achSoftVersion, tAppData.m_aSelfVer, LEN_USERNAME);
	tStackInfo.m_tSipRegistLocalInfo.m_dwLocalIP = tAppData.m_dwSelfAddr;
	tStackInfo.m_tSipRegistLocalInfo.m_emEndpointType = emSipEndpointTypeUMS;
}


void ConverUmsQueryInfoFromStackToApp( const TSipRedirectInfo& tSipInfo, TTPAlias& tAlias )
{
	switch (tSipInfo.m_emType)
	{
	case emcat_ip:
		{
			tAlias.m_byType = tp_Alias_IP;
			break;
		}
	case emcat_alias:
		{
			tAlias.m_byType = tp_Alias_h323;
			break;
		}
	case emcat_e164:
		{
			tAlias.m_byType = tp_Alias_e164;
			break;
		}
	case emcat_err:
		{
			tAlias.m_byType = tp_Alias_Unknow;
		}
	default:
		{
			break;
		}
	}
	strncpy(tAlias.m_abyAlias, tSipInfo.m_achBuf, TP_MAX_ALIAS_LEN);
	tAlias.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
}