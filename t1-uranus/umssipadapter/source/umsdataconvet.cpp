#include <string.h>
#include "umsdataconvet.h"
#include "umsobject.h"
#include "umsapi.h"
#include "lanman.h"

#include "adaptercfg.h"

extern TUmsStackCallCfg g_tUMSStackCfg;
extern TIpmaskinfo	g_tIpMaskInfo;
extern BOOL32 g_bKedaManuOn;

static void ConvertKeyPathFromUmsToStack(const TEpPathKey& tUms, TPAEpKeyID& tPA)
{
	strncpy(tPA.m_achEpID, tUms.m_szEpID, PA_MAX_EPID_LEN);
}

static void ConvertEpKeyPathFromUmsToStack(const TEpPathKey& tUms, TPAEpPathKey& tPA)
{
	strncpy(tPA.m_achEpID, tUms.m_szEpID, PA_MAX_EPID_LEN);
}

static void ConvertEpTypeFromStackToUms(const EmPAEndpointType& emStack, EmTPEndpointType& emUms)
{
	switch(emStack)
	{
	case emPAEndpointTypeCNS:
		{
			emUms = emTPEndpointTypeCNS;
			break;
		}
	case emPAEndpointTypeUMS:
		{
			emUms = emTPEndpointTypeUMS;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertEpTypeFromStackToUms unknow mode :%d\n", emStack));
			break;
		}
	}
}

void ConvertRegProtocolFromUmsToStack(const EmTpRegType& emTpProtocol, EmPAConfProtocol& emPaProtocol)
{
	switch (emTpProtocol)
	{
	case em_323_reg:		
		{
			emPaProtocol =  emPATypeH323;
			break;
		}
		
	case em_sip_reg:		
		{
			emPaProtocol = emPATypeSip;
			break;
		}
		
	default:			
		{
			MdlError(Ums_Mdl_Stack, ("ConvertRegProtocolFromUmsToStack Unknow protocol :%d\n", emTpProtocol));
			break;
		}
	}
}


void ConvertMediaTransAddrFromStackToUms(TTPMediaTransAddr& tUms, const TPaMediaTransAddr& tPA)
{
	tUms.m_tRtpAddr.SetAddr(tPA.m_tRtpAddr.m_dwIP, tPA.m_tRtpAddr.m_wPort);
	tUms.m_tRtcpAddr.SetAddr(tPA.m_tRtcpAddr.m_dwIP, tPA.m_tRtcpAddr.m_wPort);
	tUms.m_tBackRtcpAddr.SetAddr(tPA.m_tBackRtcpAddr.m_dwIP, tPA.m_tBackRtcpAddr.m_wPort);
}

void ConvertMediaTransAddrFromUmsToStack(TPaMediaTransAddr& tPA, const TTPMediaTransAddr& tUms)
{
	tPA.m_tRtpAddr.m_dwIP = tUms.m_tRtpAddr.m_dwIP;
	tPA.m_tRtpAddr.m_wPort = tUms.m_tRtpAddr.m_wPort;

	tPA.m_tRtcpAddr.m_dwIP = tUms.m_tRtcpAddr.m_dwIP;
	tPA.m_tRtcpAddr.m_wPort = tUms.m_tRtcpAddr.m_wPort;

	tPA.m_tBackRtcpAddr.m_dwIP = tUms.m_tBackRtcpAddr.m_dwIP;
	tPA.m_tBackRtcpAddr.m_wPort = tUms.m_tBackRtcpAddr.m_wPort;
}

void ConvertCallProtocolParamFromUmsToStack(const EmTpConfProtocol& emTpProtocol, EmPAConfProtocol& emPaProtocol)
{
	switch (emTpProtocol)
	{
	case emTpH323:		
		{
			emPaProtocol =  emPATypeH323;
			break;
		}

	case emTpSIP:		
		{
			emPaProtocol = emPATypeSip;
			break;
		}

	default:			
		{
			MdlError(Ums_Mdl_Stack, ("ConvertCallProtocolParamFromUmsToStack Unknow protocol :%d\n", emTpProtocol));
			break;
		}
	}
}


void ConvertTpEpTypeFromUmsToStack(const EmTPEndpointType& emTpEpType, emModuleEndpointType& emPaType)
{
	switch (emTpEpType)
	{
	case emTPEndpointTypeCNS:		
		{
			emPaType = emModuleEndpointCNS;
			break;
		}

	case emTPEndpointTypeUMS:		
		{
			emPaType = emModuleEndpointUMS;
			break;
		}

	case emTPEndpointH323MT:		
		{
			emPaType = emModuleEndpointMT;
			break;
		}

	case emTPEndpointH323MCU:		
		{
			emPaType = emModuleEndpointMcu;
			break;
		}

	case emTPEndpointH323SingleMCU:	
		{
			emPaType = emModuleEndpointMcu;
			break;
		}

	case emTPEndpointH323G400:		
		{
			emPaType = emModuleEndpointGateway;
			break;
		}

	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertTpEpTypeFromUmsToStack Unknow tpType:%d.\n", emTpEpType));
			break;
		}
	}
}

void ConvertSipLevelFromUmsToStack(const EmTPSipLevel& emTpLevel, EmPASipLevel&	emPaLevel)
{
	switch (emTpLevel)
	{
	case emTPSipCounty:		
		{
			emPaLevel = emPASipCounty;
			break;
		}

	case emTPSipCity:		
		{
			emPaLevel = emPASipCity;
			break;
		}

	case emTPSipProvince:	
		{
			emPaLevel = emPASipProvince;
			break;
		}

	case emTPSipUnKnown:	
		{
			emPaLevel = emPASipUnKnown;
			break;
		}
	}
}

void ConvertCallInfoFromUmsToStackForH323(const TMakeCallPara& tCallPara, TModuleCallInfo& tModuleInfo, TCallInfoTP& tTpCallInfo, BOOL32 bAnswer)
{	
	tModuleInfo.m_emCallType = emModuleAliasCall;
	tModuleInfo.m_wBitrate = tCallPara.m_tCallInfo.m_wBitRate;


	if (bAnswer)
	{
         tModuleInfo.m_tQtCallParam.m_emAliasType = EmQtAliasType_Others;

		if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.IsInValid())
		{
			tModuleInfo.m_emCallType = emModuleE164Call;
			tModuleInfo.m_emCalleeE164.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);

			memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, sizeof(tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias));
			tModuleInfo.m_tQtCallParam.m_emAliasType = EmQtAliasType_E164;	

		}

		if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.IsInValid())
		{//别名呼叫类型优先
			tModuleInfo.m_emCallType = emModuleAliasCall;
			tModuleInfo.m_emCalleeAlias.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN);

			if (tModuleInfo.m_tQtCallParam.m_emAliasType == EmQtAliasType_Others)
			{
				memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, sizeof(tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias));
			    tModuleInfo.m_tQtCallParam.m_emAliasType = EmQtAliasType_Alias;
			}

		}

		if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.IsInValid() && !tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.IsInValid())
		{
			MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStackForH323 answer Invalid m_tDestAddr!\n"));
		}		
	}
	else
	{
		if (tCallPara.m_tCallInfo.m_tDestAddr.m_bAliasIP)
		{
			tModuleInfo.m_emCallType = emModuleIPCall;	
			if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.IsInValid())
			{
				tModuleInfo.m_emCalleeE164.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);
			}
			else if(!tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.IsInValid())
			{
				tModuleInfo.m_emCalleeAlias.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN);		
			}

			tModuleInfo.m_emCalleeIp.m_dwIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;	
		}
		else
		{
            tModuleInfo.m_tQtCallParam.m_emAliasType = EmQtAliasType_Others;

			switch(tCallPara.m_tCallInfo.m_tDestAddr.m_byCallType)
			{
			case tp_Alias_e164:
				{
					tModuleInfo.m_emCallType = emModuleE164Call;
					tModuleInfo.m_emCalleeE164.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);
					
					memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, sizeof(tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias));
				    tModuleInfo.m_tQtCallParam.m_emAliasType = EmQtAliasType_E164;

					break;
				}	
			case tp_Alias_h323:
				{
					tModuleInfo.m_emCallType = emModuleAliasCall;
					tModuleInfo.m_emCalleeAlias.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN);	

					if (tModuleInfo.m_tQtCallParam.m_emAliasType == EmQtAliasType_Others)
					{
						memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, sizeof(tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias));
				        tModuleInfo.m_tQtCallParam.m_emAliasType = EmQtAliasType_Alias;
					}
					break;
				}
			case tp_Alias_IP:
				{
					tModuleInfo.m_emCallType = emModuleIPCall;
					break;
				}		
			default:
				{
					MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStackForH323 Invalid call type.\n"));
					return ;
				}
			}
		}

	}


	

	tModuleInfo.m_emCallerAlias.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias, TP_MAX_ALIAS_LEN);
	tModuleInfo.m_emCallerE164.SetCallAliasAddr((u8*)tCallPara.m_tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias, TP_MAX_ALIAS_LEN);

	if (tCallPara.m_tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias[0] != '\0')
	{
		memcpy(tModuleInfo.m_tQtCallParam.m_szLocalAlias, tCallPara.m_tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias, sizeof(tCallPara.m_tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias));
	}
	else if(tCallPara.m_tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias[0] != '\0')
	{
		memcpy(tModuleInfo.m_tQtCallParam.m_szLocalAlias, tCallPara.m_tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias, sizeof(tCallPara.m_tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias));
	}

	u32 dwIpCallDstIp = 0;
	u32 dwIpCallLocalIp = 0;
	if (!bAnswer)
	{
		if (emModuleIPCall == tModuleInfo.m_emCallType)
		{
			dwIpCallDstIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
			dwIpCallLocalIp = GetLocalIpByDstIp(dwIpCallDstIp);
			MdlHint(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStackForH323 ip call LocalIp:"TPIPFORMAT", DstIp:"TPIPFORMAT".\n", 
				u32ToIP(dwIpCallLocalIp), u32ToIP(dwIpCallDstIp)));
			tModuleInfo.m_emCallerIp.SetIpAddr(dwIpCallLocalIp, g_tUMSStackCfg.m_wCallingPort) ;
			tModuleInfo.m_emCalleeIp.SetIpAddr(dwIpCallDstIp, TP_DEFAULT_H225_PORT) ;

			sprintf(tModuleInfo.m_tQtCallParam.m_szPeerAlias, ""TPIPFORMAT"", u32ToIP(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP));

		}
		else
		{
			dwIpCallDstIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
			dwIpCallLocalIp = GetLocalIpByDstIp(dwIpCallDstIp);
			MdlHint(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStackForH323 name call LocalIp:"TPIPFORMAT", DstIp:"TPIPFORMAT".\n", 
				u32ToIP(dwIpCallLocalIp), u32ToIP(dwIpCallDstIp)));
			tModuleInfo.m_emCallerIp.SetIpAddr(dwIpCallLocalIp, g_tUMSStackCfg.m_wCallingPort) ;
			tModuleInfo.m_emCalleeIp.SetIpAddr(g_tUMSStackCfg.m_dwRegIP, g_tUMSStackCfg.m_wRegPort) ;
		}
	}
	else
	{
		dwIpCallDstIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
		dwIpCallLocalIp = GetLocalIpByDstIp(dwIpCallDstIp);
		MdlHint(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStackForH323 answer call LocalIp:"TPIPFORMAT", DstIp:"TPIPFORMAT".\n", 
			u32ToIP(dwIpCallLocalIp), u32ToIP(dwIpCallDstIp)));
		tModuleInfo.m_emCalleeIp.SetIpAddr(dwIpCallLocalIp, g_tUMSStackCfg.m_wCallingPort) ;
	}
	
	// 先清空再赋值
	memset(tModuleInfo.m_achLocalProductId, 0, sizeof(tModuleInfo.m_achLocalProductId));
	memcpy(tModuleInfo.m_achLocalProductId, UMS_ProductID, strlen(UMS_ProductID));
	// 先清空再赋值
	memset(tModuleInfo.m_achLocalVersionId, 0, sizeof(tModuleInfo.m_achLocalVersionId));
	memcpy(tModuleInfo.m_achLocalVersionId, UMS_VerID, strlen(UMS_VerID));
	
	ConvertTpEpTypeFromUmsToStack(tCallPara.m_tCallInfo.m_emSrcEpType, tModuleInfo.m_emEndpointType);
	ConvertSipLevelFromUmsToStack(tCallPara.m_tCallInfo.m_emLevel, tTpCallInfo.m_emSipLevel);
	tTpCallInfo.m_nScreenNum = tCallPara.m_tCapSet.m_wVidEncNum;

	BOOL32 bSignalEncrypt = tCallPara.m_tCallInfo.m_tEncrypt.IsQt();
	tModuleInfo.m_bSignalEncrypt = bSignalEncrypt;
	tModuleInfo.m_tQtCallParam.m_bCallEncryption = bSignalEncrypt;
	tModuleInfo.m_tQtCallParam.m_emKeyFrequency = (EmQtKeyFrequency)tCallPara.m_tCallInfo.m_tEncrypt.GetQtLevl();
	
	MdlHint(Ums_Mdl_Call, ("[ConvertCallInfoFromUmsToStackForH323] SrcAddr:%s, DestAddr:%s, m_bCallEncryption:%d.\n", tModuleInfo.m_tQtCallParam.m_szLocalAlias,
		tModuleInfo.m_tQtCallParam.m_szPeerAlias, tModuleInfo.m_tQtCallParam.m_bCallEncryption));

}

void ConvertCallInfoFromUmsToStack(const TMakeCallPara& tCallPara, TModuleCallInfo& tModuleInfo, TCallInfoTP& tTpCallInfo, BOOL32 bAnswer)
{	
	s8 *pzAliasUTF8 = NULL;
	tModuleInfo.m_emCallType = emModuleAliasCall;
	tModuleInfo.m_wBitrate = tCallPara.m_tCallInfo.m_wBitRate;

	// makecall 和 answercall 的时候添加本端渠道版本的字段（SIP）
	if (g_bKedaManuOn)
	{
		tModuleInfo.m_byNonStdHdrNum = 1;
		memcpy(tModuleInfo.m_atNonStdHdr[0].m_achName, KedaManuProductNameDefine, sizeof(KedaManuProductNameDefine));
		memcpy(tModuleInfo.m_atNonStdHdr[0].m_achValue, KedaManuProductValueDefine, sizeof(KedaManuProductValueDefine));
	}
	
	tpHint(Ums_Mdl_Stack, "[ConvertCallInfoFromUmsToStack] local NonStdHdrNum:%d, name:%s, value:%s.\n", 
		tModuleInfo.m_byNonStdHdrNum, tModuleInfo.m_atNonStdHdr[0].m_achName, tModuleInfo.m_atNonStdHdr[0].m_achValue);

	if (bAnswer)
	{
		tModuleInfo.m_tQtCallParam.m_szPeerAlias[0] = '\0';

		if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.IsInValid())
		{
			tModuleInfo.m_emCallType = emModuleE164Call;	
			gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, &pzAliasUTF8);
			tModuleInfo.m_emCalleeE164.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);

			memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, pzAliasUTF8, QT_ALIAS_MAX_LEN);

			free(pzAliasUTF8);

		}
		if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.IsInValid())
		{
			tModuleInfo.m_emCallType = emModuleAliasCall;
			gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, &pzAliasUTF8);
			tModuleInfo.m_emCalleeAlias.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);

			if (tModuleInfo.m_tQtCallParam.m_szPeerAlias[0] == '\0')
			{
				memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, pzAliasUTF8, QT_ALIAS_MAX_LEN);
			}

			free(pzAliasUTF8);	
		}
		if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.IsInValid() && !tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.IsInValid())
		{
			MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStack answer Invalid m_tDestAddr!\n"));
		}	
	} 
	else
	{
		if (tCallPara.m_tCallInfo.m_tDestAddr.m_bAliasIP)
		{
			tModuleInfo.m_emCallType = emModuleIPCall;

			if (!tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.IsInValid())
			{
				gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, &pzAliasUTF8);
				tModuleInfo.m_emCalleeE164.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);

			}else if(!tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.IsInValid())
			{
				gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, &pzAliasUTF8);
				tModuleInfo.m_emCalleeAlias.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);
			}

            if (pzAliasUTF8)
			{
                free(pzAliasUTF8);
			}

			tModuleInfo.m_emCalleeIp.m_dwIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
		}
		else
		{
			switch(tCallPara.m_tCallInfo.m_tDestAddr.m_byCallType)
			{
			case tp_Alias_e164:
				{
					tModuleInfo.m_emCallType = emModuleE164Call;	
					gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, &pzAliasUTF8);
					tModuleInfo.m_emCalleeE164.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);
					memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, pzAliasUTF8, QT_ALIAS_MAX_LEN);
					free(pzAliasUTF8);
					break;
				}			
			case tp_Alias_h323:
				{
					tModuleInfo.m_emCallType = emModuleAliasCall;
					gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, &pzAliasUTF8);
					tModuleInfo.m_emCalleeAlias.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);
					memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, pzAliasUTF8, QT_ALIAS_MAX_LEN);
					free(pzAliasUTF8);			
					break;
				}
			case tp_Alias_IP:
				{
					tModuleInfo.m_emCallType = emModuleIPCall;
					break;
				}
			default:
				{
					MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStack Invalid call type.\n"));
					return ;
				}
			}
			
		}
	}

	

	tModuleInfo.m_tQtCallParam.m_szLocalAlias[0] = '\0';

	pzAliasUTF8 = NULL;
	gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias, &pzAliasUTF8);
	tModuleInfo.m_emCallerAlias.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);
	memcpy(tModuleInfo.m_tQtCallParam.m_szLocalAlias, pzAliasUTF8, QT_ALIAS_MAX_LEN);
	free(pzAliasUTF8);

	pzAliasUTF8 = NULL;
	gb2312_to_utf8((s8 *)tCallPara.m_tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias, &pzAliasUTF8);
	tModuleInfo.m_emCallerE164.SetCallAliasAddr((u8*)pzAliasUTF8, TP_MAX_ALIAS_LEN);
	if (tModuleInfo.m_tQtCallParam.m_szLocalAlias[0] == '\0')
	{
        memcpy(tModuleInfo.m_tQtCallParam.m_szLocalAlias, pzAliasUTF8, QT_ALIAS_MAX_LEN);
	}
	free(pzAliasUTF8);
	u32 dwIpCallDstIp = 0;
	u32 dwIpCallLocalIp = 0;
	if (!bAnswer)
	{
		if ( emModuleIPCall == tModuleInfo.m_emCallType)
		{
			dwIpCallDstIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
			dwIpCallLocalIp = GetLocalIpByDstIp(dwIpCallDstIp);
			MdlHint(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStack ip call LocalIp:"TPIPFORMAT", DstIp:"TPIPFORMAT".\n", 
				u32ToIP(dwIpCallLocalIp), u32ToIP(dwIpCallDstIp)));
			tModuleInfo.m_emCallerIp.SetIpAddr(dwIpCallLocalIp, g_tUMSStackCfg.m_wCallingPort);
			tModuleInfo.m_emCalleeIp.SetIpAddr(dwIpCallDstIp, TP_UMS_SIP_LISTIEN_PORT) ;

			sprintf(tModuleInfo.m_tQtCallParam.m_szPeerAlias, ""TPIPFORMAT"", u32ToIP(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP));
		}
		else
		{
			dwIpCallDstIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
			dwIpCallLocalIp = GetLocalIpByDstIp(dwIpCallDstIp);
			MdlHint(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStack name call LocalIp:"TPIPFORMAT", DstIp:"TPIPFORMAT".\n", 
				u32ToIP(dwIpCallLocalIp), u32ToIP(dwIpCallDstIp)));
			tModuleInfo.m_emCallerIp.SetIpAddr(dwIpCallLocalIp, g_tUMSStackCfg.m_wCallingPort);
			tModuleInfo.m_emCalleeIp.SetIpAddr(g_tUMSStackCfg.m_dwRegIP, g_tUMSStackCfg.m_wRegPort) ;
		}
	}
	else
	{
		dwIpCallDstIp = tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP;
		dwIpCallLocalIp = GetLocalIpByDstIp(dwIpCallDstIp);
		MdlHint(Ums_Mdl_Stack, ("ConvertCallInfoFromUmsToStack answer call LocalIp:"TPIPFORMAT", DstIp:"TPIPFORMAT".\n", 
			u32ToIP(dwIpCallLocalIp), u32ToIP(dwIpCallDstIp)));
		tModuleInfo.m_emCalleeIp.SetIpAddr(dwIpCallLocalIp, g_tUMSStackCfg.m_wCallingPort);
	}

	s8	szTmpAlias[QT_ALIAS_MAX_LEN + 1];
	if ( bAnswer )
	{//answer时 传下的 local 必须是本地的 需要替换下
		memcpy(szTmpAlias, tModuleInfo.m_tQtCallParam.m_szPeerAlias, QT_ALIAS_MAX_LEN);
		memcpy(tModuleInfo.m_tQtCallParam.m_szPeerAlias, tModuleInfo.m_tQtCallParam.m_szLocalAlias, QT_ALIAS_MAX_LEN);
		memcpy(tModuleInfo.m_tQtCallParam.m_szLocalAlias, szTmpAlias, QT_ALIAS_MAX_LEN);
	}
	
	tModuleInfo.m_bSignalEncrypt = tCallPara.m_tCallInfo.m_tEncrypt.IsQt();
 	tModuleInfo.m_tQtCallParam.m_bCallEncryption = tCallPara.m_tCallInfo.m_tEncrypt.IsQt();
	
		tModuleInfo.m_tQtCallParam.m_emKeyFrequency = (EmQtKeyFrequency)tCallPara.m_tCallInfo.m_tEncrypt.GetQtLevl();	MdlHint(Ums_Mdl_Call, ("SrcAddr:%s, DestAddr:%s, bCallEncryption:%d\n", 
		tModuleInfo.m_tQtCallParam.m_szLocalAlias, tModuleInfo.m_tQtCallParam.m_szPeerAlias, tModuleInfo.m_tQtCallParam.m_bCallEncryption));
	
	MdlHint(Ums_Mdl_Call, ("ConvertCallInfoFromUmsToStack, to Stack StreamKeyInfo(%d, %d, %s), m_bSignalEncrypt:%d\n", 
		tModuleInfo.m_tStreamKey.GetEncryptType(), tModuleInfo.m_tStreamKey.GetEncryptKeyLen(), tModuleInfo.m_tStreamKey.GetEncryptKey(),
		tModuleInfo.m_bSignalEncrypt));

	// 先清空再赋值
	memset(tModuleInfo.m_achLocalProductId, 0, sizeof(tModuleInfo.m_achLocalProductId));
	pzAliasUTF8 = NULL;
	gb2312_to_utf8((s8 *)UMS_ProductID, &pzAliasUTF8);
	memcpy(tModuleInfo.m_achLocalProductId, pzAliasUTF8, strlen(UMS_ProductID));
	free(pzAliasUTF8);
	// 先清空再赋值
	memset(tModuleInfo.m_achLocalVersionId, 0, sizeof(tModuleInfo.m_achLocalVersionId));
	pzAliasUTF8 = NULL;
	gb2312_to_utf8((s8 *)UMS_VerID, &pzAliasUTF8);
	memcpy(tModuleInfo.m_achLocalVersionId, pzAliasUTF8, strlen(UMS_VerID));
	free(pzAliasUTF8);

	ConvertTpEpTypeFromUmsToStack(tCallPara.m_tCallInfo.m_emSrcEpType, tModuleInfo.m_emEndpointType);
	ConvertSipLevelFromUmsToStack(tCallPara.m_tCallInfo.m_emLevel, tTpCallInfo.m_emSipLevel);
	tTpCallInfo.m_nScreenNum = tCallPara.m_tCapSet.m_wVidEncNum;
}

void ConvertTpEpTypeFromStackToUms(const EmPAEndpointType& emPaEpType, EmTPEndpointType& emTpType)
{
	switch (emPaEpType)
	{
	case emPAEndpointTypeCNS:		
		{
			emTpType = emTPEndpointTypeCNS;
			break;
		}

	case emPAEndpointTypeUMS:		
		{
			emTpType = emTPEndpointTypeUMS;
			break;
		}
	}
}

void ConvertSipLevelFromStackToUms(const EmPASipLevel& emPaLevel, EmTPSipLevel&	emTpLevel)
{
	switch (emPaLevel)
	{
	case emPASipCounty:		
		{
			emTpLevel = emTPSipCounty;
			break;
		}

	case emPASipCity:		
		{
			emTpLevel = emTPSipCity;
			break;
		}

	case emPASipProvince:	
		{
			emTpLevel = emTPSipProvince;
			break;
		}

	case emPASipUnKnown:	
		{
			emTpLevel = emTPSipUnKnown;
			break;
		}
	}
}

void ConvertProtocolFromPaToTp(const EmPAConfProtocol& emPAType, EmTpConfProtocol& emTpType)
{
	switch (emPAType)
	{
	case emPATypeH323:
		{
			emTpType = emTpH323;
			break;
		}
		
	case emPATypeSip:
		{
			emTpType = emTpSIP;
			break;
		}
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertProtocolFromPaToTp Unknow protocol type. Type:%d\n", emPAType));
			break;
		}
	}
}

void ConvertEndPtTypeFromStackToUms(const TModuleCallInfo& tModuleInfo, EmTPEndpointType& emTpType, BOOL32 bIsSip)
{
	u8 abyTempProductId[MAX_LEN_PRODUCT_ID+1];
	memcpy(abyTempProductId, tModuleInfo.m_achPeerProductId, MAX_LEN_PRODUCT_ID+1);

	emModuleEndpointType emModuleType = bIsSip?tModuleInfo.m_emPeerEndpointType:tModuleInfo.m_emEndpointType;

	switch (emModuleType)
	{
	case emModuleEndpointMcu:
		{
			if (NULL != strstr((s8*)abyTempProductId, "UMS"))
			{
				emTpType = emTPEndpointTypeUMS;
			}
			else
			{
				emTpType = emTPEndpointH323SingleMCU;
			}
			break;
		}

	case emModuleEndpointUMS:
		{
			emTpType = emTPEndpointTypeUMS;
			break;
		}

	case emModuleEndpointMT:
		{
			if (NULL != strstr((s8*)abyTempProductId, "CNS"))
			{
				emTpType = emTPEndpointTypeCNS;
			}
			else if (NULL != strstr((s8*)abyTempProductId, "GATEWAY"))
			{
				emTpType = emTPEndpointH323G400;
			}
			else
			{
				emTpType = emTPEndpointH323MT;
			}
			break;
		}

	case emModuleEndpointCNS:
		{
			emTpType = emTPEndpointTypeCNS;
			break;
		}
		
	case emModuleEndpointGateway:
		{
			emTpType = emTPEndpointH323G400;
			break;
		}
	case emModuleEndpointVRS:
		{
			emTpType = emTPEndPointVrs;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertEndPtTypeFromStackToUms Unknow module endpoint type :%d\n", emModuleType));
			break;
		}
	}
}

void ConvertCallInfoFromStackToUms(const TModuleCallInfo& tModuleInfo, TUmsCallInfo& tCallInfo, BOOL32& bHangUp)
{
// 	if (g_bKedaManuOn &&
// 		(tModuleInfo.m_emPeerEndpointType == emModuleEndpointUMS 
// 		|| tModuleInfo.m_emPeerEndpointType == emModuleEndpointCNS
// 		|| tModuleInfo.m_emPeerEndpointType == emModuleEndpointVRS))
// 	{ 
// 		bHangUp = TRUE;
// 		tpHint(Ums_Mdl_Stack, "[ConvertCallInfoFromStackToUms] Peer NonStdHdrNum:%d.\n", tModuleInfo.m_byNonStdHdrNum);
// 		for (u16 wLoop = 0; wLoop < min(tModuleInfo.m_byNonStdHdrNum,MAX_SIP_NONSTD_HEADER_NUM); wLoop++)
// 		{
// 			
// 			if (0 == strncmp(tModuleInfo.m_atNonStdHdr[wLoop].m_achName, KedaManuProductNameDefine, strlen(KedaManuProductNameDefine)))
// 			{
// 				bHangUp = FALSE;
// 			}
// 			tpHint(Ums_Mdl_Stack, "  wLoop:%d, name:%s, value:%s, bHangUp:%d.\n", wLoop, 
// 				tModuleInfo.m_atNonStdHdr[wLoop].m_achName, tModuleInfo.m_atNonStdHdr[wLoop].m_achValue,
// 				bHangUp);
// 		}
// 	}
// 	else
// 	{
		bHangUp = FALSE;
//	}
	
// 	if (bHangUp)
// 	{
// 		return;
// 	}

	ConvertEndPtTypeFromStackToUms(tModuleInfo, tCallInfo.m_emSrcEpType, TRUE);
	//以sip协议呼叫H323MT，协议回调上来终端类型值为0 ，转为终端类型
	if ( emModuletypeBegin == tModuleInfo.m_emPeerEndpointType )
	{
		tCallInfo.m_emSrcEpType = emTPEndpointH323MT;
	}
	ConvertVersionIDFromStackToUms(tModuleInfo, tCallInfo);

	tCallInfo.m_wBitRate = tModuleInfo.m_wBitrate;

	tCallInfo.m_bIsCreatConf = tModuleInfo.m_bCreateConf;

	ConvertAliasTypeFromStackToUms(tModuleInfo.m_emCallType, tCallInfo.m_tSrcAddr.m_byCallType);

	//将IP带过去
	tCallInfo.m_tSrcAddr.m_dwIP = tModuleInfo.m_emCallerIp.m_dwIp;
	tCallInfo.m_tDestAddr.m_dwIP = tModuleInfo.m_emCalleeIp.m_dwIp;

	//对端是产品ID
	strncpy(tCallInfo.m_acPrdutID, (s8*)tModuleInfo.m_achPeerProductId, sizeof(tCallInfo.m_acPrdutID));
	tCallInfo.m_acPrdutID[sizeof(tCallInfo.m_acPrdutID)-1] = '\0';
	
	if (strlen((s8*)tModuleInfo.m_emCallerAlias.m_abyCallAliasAddr) > 0)
	{
		s8 * pzAliasUTF8 = NULL;
		utf8_to_gb2312((s8 *)tModuleInfo.m_emCallerAlias.m_abyCallAliasAddr, &pzAliasUTF8);
		tCallInfo.m_tSrcAddr.m_tAlias.SetAlias(tp_Alias_h323, pzAliasUTF8);
		free(pzAliasUTF8);

		tpLowHint(Ums_Mdl_Stack, "Caller alias len from stack:%d - in:%d.\n", strlen((s8*)tModuleInfo.m_emCallerAlias.m_abyCallAliasAddr),
			strlen((s8*)tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias));

		if (strlen((s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr) > 0)
		{// caller如果323别名和164号都有，就都带上去
			pzAliasUTF8 = NULL;
			utf8_to_gb2312((s8 *)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr, &pzAliasUTF8);
			tCallInfo.m_tSrcAddr.m_tE164.SetAlias(tp_Alias_e164, pzAliasUTF8);
			free(pzAliasUTF8);

			tpLowHint(Ums_Mdl_Stack, "Caller 164 len from stack:%d - in:%d.\n", strlen((s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr),
			strlen((s8*)tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias));

		}
	}	
	else if (strlen((s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr) > 0)
	{
		s8 * pzAliasUTF8 = NULL;
		utf8_to_gb2312((s8 *)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr, &pzAliasUTF8);
		tCallInfo.m_tSrcAddr.m_tE164.SetAlias(tp_Alias_e164, pzAliasUTF8);
		free(pzAliasUTF8);

		tpLowHint(Ums_Mdl_Stack, "Caller 164 len from stack:%d - in:%d.\n", strlen((s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr),
			strlen((s8*)tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias));

	}
	else
	{
		MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromStackToUms No src alias.\n"));
	}

	ConvertAliasTypeFromStackToUms(tModuleInfo.m_emCallType, tCallInfo.m_tSrcAddr.m_byCallType);

	if (strlen((s8*)tModuleInfo.m_emCalleeAlias.m_abyCallAliasAddr) > 0)
	{
		s8* pzAliasUTF8 = NULL;
		utf8_to_gb2312((s8 *)tModuleInfo.m_emCalleeAlias.m_abyCallAliasAddr, &pzAliasUTF8);
		tCallInfo.m_tDestAddr.m_tAlias.SetAlias(tp_Alias_h323, pzAliasUTF8);
		free(pzAliasUTF8);

		tpLowHint(Ums_Mdl_Stack, "Callee alias len from stack:%d - in:%d.\n", strlen((s8*)tModuleInfo.m_emCalleeAlias.m_abyCallAliasAddr),
			strlen((s8*)tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias));

		if (strlen((s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr) > 0)
		{// callee如果323别名和164号都有，就都带上去
			pzAliasUTF8 = NULL;
			utf8_to_gb2312((s8 *)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr, &pzAliasUTF8);
			tCallInfo.m_tDestAddr.m_tE164.SetAlias(tp_Alias_e164, pzAliasUTF8);
			free(pzAliasUTF8);

			tpLowHint(Ums_Mdl_Stack, "Callee 164 len from stack:%d - in:%d.\n", strlen((s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr),
			strlen((s8*)tCallInfo.m_tDestAddr.m_tE164.m_abyAlias));

		}
	}
	else if (strlen((s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr) > 0)
	{
		s8 * pzAliasUTF8 = NULL;
		utf8_to_gb2312((s8 *)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr, &pzAliasUTF8);
		tCallInfo.m_tDestAddr.m_tE164.SetAlias(tp_Alias_e164, pzAliasUTF8);		
		free(pzAliasUTF8);

		tpLowHint(Ums_Mdl_Stack, "Callee 164 len from stack:%d - in:%d.\n", strlen((s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr),
			strlen((s8*)tCallInfo.m_tDestAddr.m_tE164.m_abyAlias));

	}
	else
	{	
		MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromStackToUms No dest alias.\n"));
	}
}

void ConvertCallInfoFromStackToUmsForH323( const TModuleCallInfo& tModuleInfo, TUmsCallInfo& tCallInfo )
{
	ConvertEndPtTypeFromStackToUms(tModuleInfo, tCallInfo.m_emSrcEpType, FALSE);

	ConvertVersionIDFromStackToUms(tModuleInfo, tCallInfo);

	tCallInfo.m_wBitRate = tModuleInfo.m_wBitrate;
	tCallInfo.m_bIsCreatConf = tModuleInfo.m_bCreateConf;
	
	//对端是产品ID
	strncpy(tCallInfo.m_acPrdutID, (s8*)tModuleInfo.m_achPeerProductId, sizeof(tCallInfo.m_acPrdutID));
	tCallInfo.m_acPrdutID[sizeof(tCallInfo.m_acPrdutID)-1] = '\0';

	ConvertAliasTypeFromStackToUms(tModuleInfo.m_emCallType,tCallInfo.m_tSrcAddr.m_byCallType);

	if ( FALSE )
	{//产品ID 为监控
		tCallInfo.m_emVendorID = EmTp_vendor_KEDA_IPC;
	}

	//将IP带过去
	tCallInfo.m_tSrcAddr.m_dwIP = tModuleInfo.m_emCallerIp.m_dwIp;
	tCallInfo.m_tDestAddr.m_dwIP = tModuleInfo.m_emCalleeIp.m_dwIp;

	if (strlen((s8*)tModuleInfo.m_emCallerAlias.m_abyCallAliasAddr) > 0 && 0 != strcmp("(none)", (s8*)tModuleInfo.m_emCallerAlias.m_abyCallAliasAddr))
	{
		tCallInfo.m_tSrcAddr.m_tAlias.SetAlias(tp_Alias_h323, (s8*)tModuleInfo.m_emCallerAlias.m_abyCallAliasAddr);
		if (strlen((s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr) > 0 && 0 != strcmp("(none)", (s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr))
		{// caller如果323别名和164号都有，就都带上去
			tCallInfo.m_tSrcAddr.m_tE164.SetAlias(tp_Alias_e164, (s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr);
		}
	}
	else if (strlen((s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr) > 0 && 0 != strcmp("(none)", (s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr))
	{
		tCallInfo.m_tSrcAddr.m_tE164.SetAlias(tp_Alias_e164, (s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr);
	}
	else
	{
		MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromStackToUmsForH323 No src alias\n"));
	}

	if (strlen((s8*)tModuleInfo.m_emCalleeAlias.m_abyCallAliasAddr) > 0 && 0 != strcmp("(none)", (s8*)tModuleInfo.m_emCalleeAlias.m_abyCallAliasAddr))
	{
		tCallInfo.m_tDestAddr.m_tAlias.SetAlias(tp_Alias_h323, (s8*)tModuleInfo.m_emCalleeAlias.m_abyCallAliasAddr);
		if (strlen((s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr) > 0 && 0 != strcmp("(none)", (s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr))
		{
			tCallInfo.m_tDestAddr.m_tE164.SetAlias(tp_Alias_e164, (s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr);
		}
	}
	else if (strlen((s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr) > 0 && 0 != strcmp("(none)", (s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr))
	{
		tCallInfo.m_tDestAddr.m_tE164.SetAlias(tp_Alias_e164, (s8*)tModuleInfo.m_emCalleeE164.m_abyCallAliasAddr);
	}
	else
	{	
		MdlError(Ums_Mdl_Stack, ("ConvertCallInfoFromStackToUmsForH323 No dest alias\n"));
	}
}


void ConvertModuleDisReasonFromStackToUms(const EmModuleCallDisconnectReason& emModuleReason, EmCnsCallReason& emCnsReason)
{
	switch (emModuleReason)
	{
	case emModuleDisconnect_Busy:			
		{
			emCnsReason = EmCnsCallReason_Busy;
			break;
		}

	case emModuleDisconnect_Normal:			
		{
			emCnsReason = EmCnsCallReason_peerhungup;
			break;
		}

	case emModuleDisconnect_Rejected:		
		{
			emCnsReason = EmCnsCallReason_Rejected;
			break;
		}

	case emModuleDisconnect_Unreachable:	
		{
			emCnsReason = EmCnsCallReason_Unreachable;
			break;
		}

	case emModuleDisconnect_Local:			
		{
			emCnsReason = EmCnsCallReason_Local;
			break;
		}


	case emModuleDisconnect_unknown:		
		{
			emCnsReason = EmCnsCallReason_unknown;
			break;
		}

	case emModuleDisconnect_ConfAlredayExit:
		{
			emCnsReason = EmCnsCallReason_ConfExist;
			break;
		}
	case emModuleDisconnect_Normal_Peer:
		{
			emCnsReason = EmCnsCallReason_peerhungup;
			break;
		}
	case emModuleDisconnect_Abnormal:
		{
			emCnsReason = EmCnsCallReason_Abnormal;
			break;
		}
	case emModuleDisconnect_Abnormal_Peer:
		{
			emCnsReason = EmCnsCallReason_PeerAbnormal;
			break;
		}
	case emModuleDisconnect_MultiConfOver:
		{
			emCnsReason = EmCnsCallReason_ConfOver;
			break;
		}

	case emModuleDisconnect_RegSerUnreachable:
		{
			emCnsReason = EmCnsCallReason_RegSerUnreachable;
			break;
		}
	case emModuleDisconnect_AliasNotFound:
		{
			emCnsReason = EmCnsCallReason_AliasNotFound;
			break;
		}

	case emModuleDisconnect_StreamEncryptKeyNotEqual:
		{
			emCnsReason = EmCnsCallReason_StreamEncryptFail;
			break;
		}

	case emModuleDisconnect_GetSignalEncryptKeyFailed:
		{
			emCnsReason = EmCnsCallReason_GetSignalEncryptKeyFailed;
			break;
		}
	case emModuleDisconnect_AutoGetRegSerAddrFailed:
		{
			emCnsReason = EmCnsCallReason_AutoGetRegSerAddrFailed;
			break;
		}
	case emModuleDisconnect_QTDevConnectionBroken:
		{
			emCnsReason = EmCnsCallReason_QTDevConnectionBroken;
			break;
		}
	case emModuleDisconnect_QTDevConnectionBroken_peer:
		{
			emCnsReason = EmCnsCallReason_QTDevConnectionBrokenPeer;
			break;
		}
	case emModuleDisconnect_CallFull:
		{//呼叫句柄满，当成本地原因带上上层业务，出现此原因，需要协议排查
			MdlError(Ums_Mdl_Call, ("ConvertModuleDisReasonFromStackToUms disconnect reason CallFull:%d\n", emModuleReason));
			emCnsReason = EmCnsCallReason_Local;
			break;
		}

	default:								
		{
			emCnsReason = EmCnsCallReason_unknown;
			MdlError(Ums_Mdl_Stack, ("ConvertModuleDisReasonFromStackToUms Unknow disconnect reason:%d\n", emModuleReason));
			break;
		}
	}
}

void ConvertModuleDisReasonFromUmsToStack(const EmCnsCallReason& emCnsReason, EmModuleCallDisconnectReason& emModuleReason)
{
	switch (emCnsReason)
	{
	case EmCnsCallReason_Busy:	
		{
			emModuleReason = emModuleDisconnect_Busy;
			break;
		}
	case EmCnsCallReason_hungup:
	case EmCnsCallReason_peerhungup:			
		{
			emModuleReason = emModuleDisconnect_Normal;
			break;
		}
		
	case EmCnsCallReason_Rejected:		
		{
			emModuleReason = emModuleDisconnect_Rejected;
			break;
		}
		
	case EmCnsCallReason_Unreachable:	
		{
			emModuleReason = emModuleDisconnect_Unreachable;
			break;
		}
		
	case EmCnsCallReason_Local:			
		{
			emModuleReason = emModuleDisconnect_Local;
			break;
		}
		
		
	case EmCnsCallReason_unknown:		
		{
			emModuleReason = emModuleDisconnect_unknown;
			break;
		}
		
	case EmCnsCallReason_ConfExist:
		{
			emModuleReason = emModuleDisconnect_ConfAlredayExit;
			break;
		}
	case EmCnsCallReason_Abnormal:
		{
			emModuleReason = emModuleDisconnect_Abnormal;
			break;
		}
	case EmCnsCallReason_PeerAbnormal:
		{
			emModuleReason = emModuleDisconnect_Abnormal_Peer;
			break;
		}
	case EmCnsCallReason_ConfOver:
		{
			emModuleReason = emModuleDisconnect_MultiConfOver;
			break;
		}
	case EmCnsCallReason_StreamEncryptTypeNotEqual:
		{
            emModuleReason = emModuleDisconnect_StreamEncryptKeyNotEqual;
			break;
		}
	default:								
		{
			emModuleReason = emModuleDisconnect_custom;
			MdlError(Ums_Mdl_Stack, ("ConvertModuleDisReasonFromUmsToStack Unknow disconnect reason:%d\n", emCnsReason));
			break;
		}
	}
}

void ConvertVideoResFromUmsToStack(const EmTpVideoResolution& emtpVideRes, EmModuleVideoResolution& emModuleVideoRes)
{
	switch (emtpVideRes)
	{
	case emTPVResolutionAuto:		
		{
			emModuleVideoRes = emModuleVResolutionAuto;
			break;
		}

	case emTPVSQCIF:				
		{
			emModuleVideoRes = emModuleVSQCIF;
			break;
		}

	case emTPVQCIF:					
		{
			emModuleVideoRes = emModuleVQCIF;
			break;
		}

	case emTPVCIF:					
		{
			emModuleVideoRes = emModuleVCIF;
			break;
		}

	case emTPV2CIF:					
		{
			emModuleVideoRes = emModuleV2CIF;
			break;
		}

	case emTPV4CIF:					
		{
			emModuleVideoRes = emModuleV4CIF;
			break;
		}

	case emTPV16CIF:				
		{
			emModuleVideoRes = emModuleV16CIF;
			break;
		}
			
	case emTPVHD480i720x480:		
		{
			emModuleVideoRes = emModuleVHD480i720x480;
			break;
		}

	case emTPVHD480p720x480:		
		{
			emModuleVideoRes = emModuleVHD480p720x480;
			break;
		}

	case emTPVHD576i720x576:		
		{
			emModuleVideoRes = emModuleVHD576i720x576;
			break;
		}

	case emTPVHD576p720x576:		
		{
			emModuleVideoRes = emModuleVHD576p720x576;
			break;
		}
			
	case emTPVHD720p1280x720:		
		{
			emModuleVideoRes = emModuleVHD720p1280x720;
			break;
		}

	case emTPVHD1080i1920x1080:		
		{
			emModuleVideoRes = emModuleVHD1080i1920x1080;
			break;
		}

	case emTPVHD1080p1920x1080:		
		{
			emModuleVideoRes = emModuleVHD1080p1920x1080;
			break;
		}
			
	case emTPVGA352x240:			
		{
			emModuleVideoRes = emModuleVGA352x240;
			break;
		}

	case emTPVGA704x480:			
		{
			emModuleVideoRes = emModuleVGA704x480;
			break;
		}

	case emTPVGA640x480:			
		{
			emModuleVideoRes = emModuleVGA640x480;
			break;
		}

	case emTPVGA800x600:			
		{
			emModuleVideoRes = emModuleVGA800x600;
			break;
		}

	case emTPVGA1024x768:			
		{
			emModuleVideoRes = emModuleVGA1024x768;
			break;
		}

	case emTPVGA1280x768:			
		{
			emModuleVideoRes = emModuleVGA1280x768;
			break;
		}

	case emTPVGA1280x800:			
		{
			emModuleVideoRes = emModuleVGA1280x800;
			break;
		}

	case emTPVGA1366x768:			
		{
			emModuleVideoRes = emModuleVGA1366x768;
			break;
		}

	case emTPVGA1280x854:			
		{
			emModuleVideoRes = emModuleVGA1280x854;
			break;
		}

	case emTPVGA1440x900:			
		{
			emModuleVideoRes = emModuleVGA1440x900;
			break;
		}

	case emTPVGA1280x1024:			
		{
			emModuleVideoRes = emModuleVGA1280x1024;
			break;
		}

	case emTPVGA1680x1050:			
		{
			emModuleVideoRes = emModuleVGA1680x1050;
			break;
		}

	case emTPVGA1600x1200:			
		{
			emModuleVideoRes = emModuleVGA1600x1200;
			break;
		}

	case emTPVGA1920x1200:			
		{
			emModuleVideoRes = emModuleVGA1920x1200;
			break;
		}
			
	case emTPVSQCIF112x96:			
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPVSQCIF96x80:			
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPV320x192:				
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPV432x240:				
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPV480x272:				
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPV640x368:				
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPV864x480:				
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPV960x544:				
		{
			//emModuleVideoRes = ;
			break;
		}

	case emTPV1440x816:				
		{
			//emModuleVideoRes = ;
			break;
		}
	}
}

void ConverDualParamFromStackToUms(TChanConnectedInfo* patChanConnectInfo, u8 bySize, TUmsNodeCapset& tCapSet)
{
	tCapSet.m_wAudDecNum = 0;
	tCapSet.m_wAudEncNum = 0;
	tCapSet.m_wVidDecNum = 0;
	tCapSet.m_wVidEncNum = 0;
	u16 wChannelIndex = 0;
	TChanNetPara* ptChan = NULL;

	for (u8 byIndex = 0; byIndex < bySize; ++byIndex)
	{
		TChanConnectedInfo& tChanInfo = patChanConnectInfo[byIndex];

		
		if (emModuleAudioSecondType == tChanInfo.m_tChanType.m_emAVType)
		{
			if (emModuleChannelRecv == tChanInfo.m_tChanType.m_emDirection)
			{
				ptChan = &(tCapSet.m_atAudEnc[tCapSet.m_wAudEncNum]);
				++tCapSet.m_wAudEncNum;
				//add
				tCapSet.m_tAudSndCap.m_atAudFmt[0].m_byReserve1 = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload;
				ConvertAudFormatFromStackToUms(tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioFormat, tCapSet.m_tAudSndCap.m_atAudFmt[0].m_emFormat);
				//end
				ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
															tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
			}
			else
			{
				if (emModuleChannelSend == tChanInfo.m_tChanType.m_emDirection)
				{
					ptChan = &(tCapSet.m_atAudDec[tCapSet.m_wAudDecNum]);
					++tCapSet.m_wAudDecNum;	
					//add
					tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_byReserve1 = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload;
					ConvertAudFormatFromStackToUms(tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioFormat, tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_emFormat);
					//end
					ptChan->m_tChanAddr.m_tRtpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
														   tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
					ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
  														        tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);

				}
				else
				{
					if (emModuleChannelBidirectional == tChanInfo.m_tChanType.m_emDirection)
					{
						ptChan = &(tCapSet.m_atAudEnc[tCapSet.m_wAudEncNum]);
						++tCapSet.m_wAudEncNum;
						//add
						tCapSet.m_tAudSndCap.m_atAudFmt[0].m_byReserve1 = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload;
						ConvertAudFormatFromStackToUms(tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioFormat, tCapSet.m_tAudSndCap.m_atAudFmt[0].m_emFormat);
						//end
						ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
															tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
					
						ptChan = &(tCapSet.m_atAudDec[tCapSet.m_wAudDecNum]);
						++tCapSet.m_wAudDecNum;	
						//add
						tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_byReserve1 = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload;
						ConvertAudFormatFromStackToUms(tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioFormat, tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_emFormat);
						//end
						ptChan->m_tChanAddr.m_tRtpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
																   tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
						ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
  														        tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
					}
					else
					{
						MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error audio direct :%d\n", tChanInfo.m_tChanType.m_emDirection));
						continue;
					}
				}
			}
		}
		else
		{
			if (emModuleVideoSecondType == tChanInfo.m_tChanType.m_emAVType)
			{
				if (emModuleChannelRecv == tChanInfo.m_tChanType.m_emDirection)
				{
					ptChan = &(tCapSet.m_atVidEnc[tCapSet.m_wVidEncNum]);
					++tCapSet.m_wVidEncNum;

					ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
					//add
					for (u16 wIndex = 0; wIndex < tChanInfo.m_tCapsetInfo.m_byMediaCount; wIndex++)
					{
						EmTpVideoQualityLevel emProfile;
						ConvertVideoProfileFromStackToUms(emProfile, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile);
						
						EmTpVideoResolution emRes;
						ConvertVideoResFromStackToUms(emRes, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_emRes);
						
						if (emModuleProfileBaseline == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
						{
							tCapSet.m_tVidSndCap.m_tBp.m_emRes = emRes;
							tCapSet.m_tVidSndCap.m_tBp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
							tCapSet.m_tVidSndCap.m_tBp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
						}
						
						if (emModuleProfileHigh == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
						{
							tCapSet.m_tVidSndCap.m_tHp.m_emRes = emRes;
							tCapSet.m_tVidSndCap.m_tHp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
							tCapSet.m_tVidSndCap.m_tHp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
						}
						
						tCapSet.m_tVidSndCap.m_wDynamicPayload = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_byDynamicPayload;						
					}
					//end
				}
				else
				{
					if (emModuleChannelSend == tChanInfo.m_tChanType.m_emDirection)
					{
						ptChan = &(tCapSet.m_atVidDec[tCapSet.m_wVidDecNum]);
						++tCapSet.m_wVidDecNum;
						ptChan->m_tChanAddr.m_tRtpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
															   tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
						ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																    tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
						//add
						for (u16 wIndex = 0; wIndex < tChanInfo.m_tCapsetInfo.m_byMediaCount; wIndex++)
						{
							EmTpVideoQualityLevel emProfile;
							ConvertVideoProfileFromStackToUms(emProfile, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile);
							
							EmTpVideoResolution emRes;
							ConvertVideoResFromStackToUms(emRes, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_emRes);
							
							if (emModuleProfileBaseline == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
							{
								tCapSet.m_tVidRcvCap.m_tBp.m_emRes = emRes;
								tCapSet.m_tVidRcvCap.m_tBp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
								tCapSet.m_tVidRcvCap.m_tBp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
							}
							
							if (emModuleProfileHigh == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
							{
								tCapSet.m_tVidRcvCap.m_tHp.m_emRes = emRes;
								tCapSet.m_tVidRcvCap.m_tHp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
								tCapSet.m_tVidRcvCap.m_tHp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
							}
							
							tCapSet.m_tVidRcvCap.m_wDynamicPayload = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_byDynamicPayload;
						}
						//end
					}
					else
					{
						if (emModuleChannelBidirectional == tChanInfo.m_tChanType.m_emDirection)
						{
							ptChan = &(tCapSet.m_atVidEnc[tCapSet.m_wVidEncNum]);
							++tCapSet.m_wVidEncNum;
							ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																		tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
							//add
							u16 wIndex = 0;
							for (wIndex = 0; wIndex < tChanInfo.m_tCapsetInfo.m_byMediaCount; wIndex++)
							{
								EmTpVideoQualityLevel emProfile;
								ConvertVideoProfileFromStackToUms(emProfile, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile);
								
								EmTpVideoResolution emRes;
								ConvertVideoResFromStackToUms(emRes, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_emRes);
								
								if (emModuleProfileBaseline == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
								{
									tCapSet.m_tVidSndCap.m_tBp.m_emRes = emRes;
									tCapSet.m_tVidSndCap.m_tBp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
									tCapSet.m_tVidSndCap.m_tBp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
								}
								
								if (emModuleProfileHigh == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
								{
									tCapSet.m_tVidSndCap.m_tHp.m_emRes = emRes;
									tCapSet.m_tVidSndCap.m_tHp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
									tCapSet.m_tVidSndCap.m_tHp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
								}
								
								tCapSet.m_tVidSndCap.m_wDynamicPayload = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_byDynamicPayload;						
							}
							//end
							ptChan = &(tCapSet.m_atVidDec[tCapSet.m_wVidDecNum]);
							++tCapSet.m_wVidDecNum;
							ptChan->m_tChanAddr.m_tRtpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
																   tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
							ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																	    tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
							//add
							for (wIndex = 0; wIndex < tChanInfo.m_tCapsetInfo.m_byMediaCount; wIndex++)
							{
								EmTpVideoQualityLevel emProfile;
								ConvertVideoProfileFromStackToUms(emProfile, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile);
								
								EmTpVideoResolution emRes;
								ConvertVideoResFromStackToUms(emRes, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_emRes);
								
								if (emModuleProfileBaseline == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
								{
									tCapSet.m_tVidRcvCap.m_tBp.m_emRes = emRes;
									tCapSet.m_tVidRcvCap.m_tBp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
									tCapSet.m_tVidRcvCap.m_tBp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
								}
								
								if (emModuleProfileHigh == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
								{
									tCapSet.m_tVidRcvCap.m_tHp.m_emRes = emRes;
									tCapSet.m_tVidRcvCap.m_tHp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
									tCapSet.m_tVidRcvCap.m_tHp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
								}
								
								tCapSet.m_tVidRcvCap.m_wDynamicPayload = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_byDynamicPayload;
							}
							//end
						}
						else
						{
							MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error audio direct :%d\n", tChanInfo.m_tChanType.m_emDirection));
							continue;
						}
					}
				}
			}
			else
			{
				MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error media type :%d\n", tChanInfo.m_tChanType.m_emAVType));
				continue;
			}
		}
		if (NULL != ptChan)
		{
			ptChan->m_tPAHandle = (s32)patChanConnectInfo[byIndex].m_hChan;
			ptChan->m_bIsChanOn = TRUE;
		}
	}

	if (0 != patChanConnectInfo[0].m_tStreamKey.m_byLen)
	{
		ConverStreamKeyFromStackToUms(patChanConnectInfo[0].m_tStreamKey, tCapSet.m_tEncrypt);
	}
}
 
//协议栈的接收：表示本地接收通道，因此对应到NODE为远端的发送
//协议栈的发送：表示本地发送通道，因此对应到NODE为远端的接收
void ConvertChanConnectParamFromStackToUms(TChanConnectedInfo* patChanConnectInfo, u8 bySize, TChanDescriptTP *ptDesTP, 
										   TUmsNodeCapset& tCapSet)
{
	tCapSet.m_wAudDecNum = 0;
	tCapSet.m_wAudEncNum = 0;
	tCapSet.m_wVidDecNum = 0;
	tCapSet.m_wVidEncNum = 0;
	u16 wChannelIndex = 0;
	TChanNetPara* ptChan = NULL;

	for (u8 byIndex = 0; byIndex < bySize; ++byIndex)
	{
		TChanConnectedInfo& tChanInfo = patChanConnectInfo[byIndex];		
		if (emModuleAudioType == tChanInfo.m_tChanType.m_emAVType || 
			emModuleAudioSecondType == tChanInfo.m_tChanType.m_emAVType)
		{
			if (emModuleChannelRecv == tChanInfo.m_tChanType.m_emDirection)
			{
				if (NULL != ptDesTP && ptDesTP[byIndex].m_tPeerTP.m_bAudMix)
				{
					ptChan = &(tCapSet.m_tAudMixEnc);
				}
				else
				{
					if (NULL != ptDesTP)
					{
						wChannelIndex = ptDesTP[byIndex].m_tLocalTP.m_nScreenNo;
					}
					else
					{
						wChannelIndex = MIDSCREENINDEX;
					}
					if (wChannelIndex >= TP_MAX_STREAMNUM)
					{
						MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error ScreenNo:%d\n", wChannelIndex));
						continue;
					}

					++tCapSet.m_wAudEncNum;
					ptChan = &(tCapSet.m_atAudEnc[wChannelIndex]);
					tCapSet.m_tAudSndCap.m_atAudFmt[0].m_byReserve1 = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload;
					ConvertChnlCfgFromMdlStackToUms(tCapSet.m_tAudSndCap.m_atAudFmt[0].m_emChnlCfg, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioChnlCfg);
					ConvertSampleFreqFromMdlStackToUms(tCapSet.m_tAudSndCap.m_atAudFmt[0].m_emSampleFreq, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioSampleFreq);
					ConvertAudFormatFromStackToUms(tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioFormat, tCapSet.m_tAudSndCap.m_atAudFmt[0].m_emFormat);
				}
				ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
															tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
				
			}
			else if (emModuleChannelSend == tChanInfo.m_tChanType.m_emDirection)
			{
				if (NULL != ptDesTP && ptDesTP[byIndex].m_tPeerTP.m_bAudMix)
				{
					ptChan = &(tCapSet.m_tAudMixDec);
				}
				else
				{
					if (NULL != ptDesTP)
					{
						wChannelIndex = ptDesTP[byIndex].m_tLocalTP.m_nScreenNo;
					}
					else
					{
						wChannelIndex = MIDSCREENINDEX;
					}
					if (wChannelIndex >= TP_MAX_STREAMNUM)
					{
						MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error ScreenNo:%d\n", wChannelIndex));
						continue;
					}

					++tCapSet.m_wAudDecNum;	
					ptChan = &(tCapSet.m_atAudDec[wChannelIndex]);
					tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_byReserve1 = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload;
					ConvertChnlCfgFromMdlStackToUms(tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_emChnlCfg, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioChnlCfg);
					ConvertSampleFreqFromMdlStackToUms(tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_emSampleFreq, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioSampleFreq);
					ConvertAudFormatFromStackToUms(tChanInfo.m_tCapsetInfo.m_atCapSetInfo[0].m_emAudioFormat, tCapSet.m_tAudRcvCap.m_atAudFmt[0].m_emFormat);
				}
				ptChan->m_tChanAddr.m_tRtpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
													   tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
				ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
  														    tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);

			}
			else
			{
			
				MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error audio direct :%d", tChanInfo.m_tChanType.m_emDirection));
				continue;
			}
		}//音频
		else
		{
			if (emModuleVideoType == tChanInfo.m_tChanType.m_emAVType ||
				emModuleVideoSecondType == tChanInfo.m_tChanType.m_emAVType)
			{
				if (emModuleChannelRecv == tChanInfo.m_tChanType.m_emDirection)
				{
					if (NULL != ptDesTP)
					{
						wChannelIndex = ptDesTP[byIndex].m_tLocalTP.m_nScreenNo;
					}
					else
					{
						wChannelIndex = MIDSCREENINDEX;
					}
					if (wChannelIndex >= TP_MAX_STREAMNUM)
					{
						MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error ScreenNo:%d\n", wChannelIndex));
						continue;
					}

					++tCapSet.m_wVidEncNum;
					ptChan = &(tCapSet.m_atVidEnc[wChannelIndex]);
					ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);

					if( NULL != ptDesTP )
					{
						if(emPACapSmall == ptDesTP[byIndex].m_tPeerTP.m_aemPACapSign[0])
						{
							tCapSet.m_atSmallVidEnc[wChannelIndex].m_bIsChanOn = TRUE;
							
	// 						tCapSet.m_atSmallVid[wChannelIndex].m_tChanAddr.m_tRtpAddr.SetAddr(
	// 							ptDesTP[byIndex].m_tPeerTP.m_atRtpAddr[0].m_dwIp
	// 							,ptDesTP[byIndex].m_tPeerTP.m_atRtpAddr[0].m_wPort);
							tCapSet.m_atSmallVidEnc[wChannelIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(
								ptDesTP[byIndex].m_tPeerTP.m_atRtcpAddr[0].m_dwIp
								, ptDesTP[byIndex].m_tPeerTP.m_atRtcpAddr[0].m_wPort);
						}
					}

					for (u16 wIndex = 0; wIndex < tChanInfo.m_tCapsetInfo.m_byMediaCount; wIndex++)
					{
						EmTpVideoQualityLevel emProfile;
						ConvertVideoProfileFromStackToUms(emProfile, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile);
						
						EmTpVideoResolution emRes;
						ConvertVideoResFromStackToUms(emRes, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_emRes);

						if (emModuleProfileBaseline == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
						{
							tCapSet.m_tVidSndCap.m_tBp.m_emRes = emRes;
							tCapSet.m_tVidSndCap.m_tBp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
							tCapSet.m_tVidSndCap.m_tBp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
						}

						if (emModuleProfileHigh == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
						{
							tCapSet.m_tVidSndCap.m_tHp.m_emRes = emRes;
							tCapSet.m_tVidSndCap.m_tHp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
							tCapSet.m_tVidSndCap.m_tHp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
						}

						tCapSet.m_tVidSndCap.m_wDynamicPayload = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_byDynamicPayload;						
					}
				}
				else if (emModuleChannelSend == tChanInfo.m_tChanType.m_emDirection)
				{
					if (NULL != ptDesTP)
					{
						wChannelIndex = ptDesTP[byIndex].m_tLocalTP.m_nScreenNo;
					}
					else
					{
						wChannelIndex = MIDSCREENINDEX;
					}
					if (wChannelIndex >= TP_MAX_STREAMNUM)
					{
						MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error ScreenNo:%d\n", wChannelIndex));
						continue;
					}
					
					++tCapSet.m_wVidDecNum;
					ptChan = &(tCapSet.m_atVidDec[wChannelIndex]);
					ptChan->m_tChanAddr.m_tRtpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
																tChanInfo.m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
					ptChan->m_tChanAddr.m_tBackRtcpAddr.SetAddr(tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																tChanInfo.m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);


					if( NULL != ptDesTP )
					{
						if ( emPACapSmall == ptDesTP[byIndex].m_tPeerTP.m_aemPACapSign[0] )
						{
							tCapSet.m_atSmallVidDec[wChannelIndex].m_bIsChanOn = TRUE;
							
							tCapSet.m_atSmallVidDec[wChannelIndex].m_tChanAddr.m_tRtpAddr.SetAddr(
								ptDesTP[byIndex].m_tPeerTP.m_atRtpAddr[0].m_dwIp
								,ptDesTP[byIndex].m_tPeerTP.m_atRtpAddr[0].m_wPort);
							tCapSet.m_atSmallVidDec[wChannelIndex].m_tChanAddr.m_tBackRtcpAddr.SetAddr(
								ptDesTP[byIndex].m_tPeerTP.m_atRtcpAddr[0].m_dwIp
								,ptDesTP[byIndex].m_tPeerTP.m_atRtcpAddr[0].m_wPort);
						}
					}


					for (u16 wIndex = 0; wIndex < tChanInfo.m_tCapsetInfo.m_byMediaCount; wIndex++)
					{
						EmTpVideoQualityLevel emProfile;
						ConvertVideoProfileFromStackToUms(emProfile, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile);
						
						EmTpVideoResolution emRes;
						ConvertVideoResFromStackToUms(emRes, tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_emRes);

						if (emModuleProfileBaseline == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
						{
							tCapSet.m_tVidRcvCap.m_tBp.m_emRes = emRes;
							tCapSet.m_tVidRcvCap.m_tBp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
							tCapSet.m_tVidRcvCap.m_tBp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
						}
						
						if (emModuleProfileHigh == tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_emProfile)
						{
							tCapSet.m_tVidRcvCap.m_tHp.m_emRes = emRes;
							tCapSet.m_tVidRcvCap.m_tHp.m_wFrameRate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_byMPI;
							tCapSet.m_tVidRcvCap.m_tHp.m_wBitrate = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_atItem.m_wMaxBitrate;
						}

						tCapSet.m_tVidRcvCap.m_wDynamicPayload = tChanInfo.m_tCapsetInfo.m_atCapSetInfo[wIndex].m_byDynamicPayload;
					}
				}
				else
				{
					MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error audio direct :%d", tChanInfo.m_tChanType.m_emDirection));
					continue;
				}
			}
			else
			{
				MdlError(Ums_Mdl_Stack, ("ConvertChanConnectParamFromStackToUms error media type :%d", tChanInfo.m_tChanType.m_emAVType));
				continue;
			}
		}
		if (NULL != ptChan)
		{
			ptChan->m_tPAHandle = (s32)patChanConnectInfo[byIndex].m_hChan;
			ptChan->m_bIsChanOn = TRUE;
		}
	}

	if (0 != patChanConnectInfo[0].m_tStreamKey.m_byLen)
	{
		ConverStreamKeyFromStackToUms(patChanConnectInfo[0].m_tStreamKey, tCapSet.m_tEncrypt);
	}
}


//NODE的发送：对应协议栈本地的接收通道
//NODE的接收：对应协议栈本地的发送通道
void ConvertChanChangeParamFromUmsToStack(TPOUT TChanConnectedInfo* patChanConnectInfo, TPOUT u8& byMaxSize, const TUmsNodeCapset& tCapSet, BOOL32 bIsDual)
{
	u8 bySize = 0;
	TChanConnectedInfo* ptChan = NULL;
	const TUmsVidFormat* ptCap = NULL;

	if (tCapSet.m_tVidSndCap.m_tBp.IsValid())
	{
		ptCap = &tCapSet.m_tVidSndCap.m_tBp;
	}
	else
	{
		ptCap = &tCapSet.m_tVidSndCap.m_tHp;
	}
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (!tCapSet.m_atVidEnc[wIndex].m_bIsChanOn)
		{
			continue;
		}

		ptChan = &patChanConnectInfo[bySize];
		bySize++;
		
		if (!bIsDual)
		{
			ptChan->m_hChan = HMDLCHANNEL(tCapSet.m_atVidEnc[wIndex].m_tPAHandle);
			ptChan->m_hAppChan = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_video_send_handle, wIndex));
			ptChan->m_tChanType.m_emAVType = emModuleVideoType;
			ptChan->m_tChanType.m_emDirection = emModuleChannelRecv;
		}
		else
		{
			ptChan->m_hChan = HMDLCHANNEL(tCapSet.m_atVidEnc[wIndex].m_tPAHandle);
			ptChan->m_hAppChan = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_second_vidrcv_handle, wIndex));
			ptChan->m_tChanType.m_emAVType = emModuleVideoSecondType;
			ptChan->m_tChanType.m_emDirection = emModuleChannelRecv;
		}
		
		ptChan->m_tCapsetInfo.m_byMediaCount = 1;
		
		ConvertVidFormatFromUmsToStack(ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_emVideoFormat, ptCap->m_emFormat);
		ConvertVideoProfileFromUmsToStack(ptCap->m_emQualityLvl, ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_emProfile);
		ConvertVideoResFromUmsToStack(ptCap->m_emRes, ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_atItem.m_emRes);
		ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_atItem.m_byMPI = (u8)ptCap->m_wFrameRate;
		ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_atItem.m_wMaxBitrate = ptCap->m_wBitrate;
		ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload = (u8)tCapSet.m_tVidSndCap.m_wDynamicPayload;

		ptChan->m_tCapsetInfo.m_tPeerRtcpAddr.SetIpAddr(tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.m_dwIP
			, tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.m_wPort);

	}

	if (tCapSet.m_tVidRcvCap.m_tBp.IsValid())
	{
		ptCap = &tCapSet.m_tVidRcvCap.m_tBp;
	}
	else
	{
		ptCap = &tCapSet.m_tVidRcvCap.m_tHp;
	}
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		if (!tCapSet.m_atVidDec[wIndex].m_bIsChanOn)
		{
			continue;
		}
		
		ptChan = &patChanConnectInfo[bySize];
		bySize++;
		
		if (!bIsDual)
		{
			ptChan->m_hChan = HMDLCHANNEL(tCapSet.m_atVidDec[wIndex].m_tPAHandle);
			ptChan->m_hAppChan = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_video_recv_handle, wIndex));
			ptChan->m_tChanType.m_emAVType = emModuleVideoType;
			ptChan->m_tChanType.m_emDirection = emModuleChannelSend;
		}
		else
		{
			ptChan->m_hChan = HMDLCHANNEL(tCapSet.m_atVidDec[wIndex].m_tPAHandle);
			ptChan->m_hAppChan = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_second_vidsnd_handle, wIndex));
			ptChan->m_tChanType.m_emAVType = emModuleVideoSecondType;
			ptChan->m_tChanType.m_emDirection = emModuleChannelSend;
		}
		
		ptChan->m_tCapsetInfo.m_byMediaCount = 1;
		ConvertVidFormatFromUmsToStack(ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_emVideoFormat, ptCap->m_emFormat);
		ConvertVideoProfileFromUmsToStack(ptCap->m_emQualityLvl, ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_emProfile);
		ConvertVideoResFromUmsToStack(ptCap->m_emRes, ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_atItem.m_emRes);
		ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_atItem.m_byMPI = (u8)ptCap->m_wFrameRate;
		ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_atItem.m_wMaxBitrate = ptCap->m_wBitrate;
		ptChan->m_tCapsetInfo.m_atCapSetInfo[0].m_byDynamicPayload = (u8)tCapSet.m_tVidRcvCap.m_wDynamicPayload;
		
		ptChan->m_tCapsetInfo.m_tPeerRtpAddr.SetIpAddr(tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr.m_dwIP
			, tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr.m_wPort);
		ptChan->m_tCapsetInfo.m_tPeerRtcpAddr.SetIpAddr(tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.m_dwIP
			, tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr.m_wPort);

	}

	byMaxSize = bySize;
}

//add
void ConvertChanClosedParamFromUmsToStack(TPOUT HMDLCHANNEL* phChan, TPOUT HMDLAPPCHANNEL* phAppChan, TPOUT u8& bySize, const BOOL32& bIsSnd, const TUmsNodeCapset& tNode)
{
	u8 byRet = 0;

	if (bIsSnd)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (!tNode.m_atVidEnc[wIndex].m_bIsChanOn)
			{
				continue;
			}
			phChan[byRet] = HMDLCHANNEL(tNode.m_atVidEnc[wIndex].m_tPAHandle);
			phAppChan[byRet] = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_video_recv_handle, wIndex));
			byRet++;
		}
		
		bySize = byRet;
	}
	else
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (!tNode.m_atVidDec[wIndex].m_bIsChanOn)
			{
				continue;
			}
			phChan[byRet] = HMDLCHANNEL(tNode.m_atVidDec[wIndex].m_tPAHandle);
			phAppChan[byRet] = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_video_send_handle, wIndex));
			byRet++;
		}
		
		bySize = byRet;
	}
	
}

void ConvertDualChanClosedParamFromUmsToStack(TPOUT HMDLCHANNEL* phChan, TPOUT HMDLAPPCHANNEL* phAppChan, TPOUT u8& bySize, const BOOL32& bIsSnd, const TUmsNodeCapset& tNode)
{
	u8 byRet = 0;
	
	if (bIsSnd)
	{
		if (tNode.m_atVidEnc[0].m_bIsChanOn)
		{
			phChan[0] = HMDLCHANNEL(tNode.m_atVidEnc[0].m_tPAHandle);
			phAppChan[0] = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_second_vidrcv_handle, 0));
			byRet++;
		}
		
		bySize = byRet;
	}
	else
	{
		if (tNode.m_atVidDec[0].m_bIsChanOn)
		{
			phChan[0] = HMDLCHANNEL(tNode.m_atVidDec[0].m_tPAHandle);
			phAppChan[0] = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_second_vidsnd_handle, 0));
			byRet++;
		}		
		bySize = byRet;
	}
}
static void ConvertAudCapToStack(const EmTpAudioFormat emTpType, TAudioDescript& tItem)
{
	//音频能力
	switch (emTpType)
	{
	case emTPAG711a:	
		{
			tItem.m_emFormat = emModuleAG711a;
			tItem.m_byDynamicPayload = MEDIA_TYPE_PCMA;			
		}
		break;
		
	case emTPAG711u:
		{
			tItem.m_emFormat = emModuleAG711u;
			tItem.m_byDynamicPayload = MEDIA_TYPE_PCMU;			
		}
		break;
	case emTPAG722:
		{
			tItem.m_emFormat = emModuleAG722;
			tItem.m_byDynamicPayload = MEDIA_TYPE_G722;	
		}
		break;
	case emTPAG7231:
		{
			tItem.m_emFormat = emModuleAG7231;
			tItem.m_byDynamicPayload = MEDIA_TYPE_G7231;	
		}
		break;
	case emTPAG728:
		{
			tItem.m_emFormat = emModuleAG728;
			tItem.m_byDynamicPayload = MEDIA_TYPE_G728;	
		}
		break;
	case emTPAG729:
		{
			tItem.m_emFormat = emModuleAG729;
			tItem.m_byDynamicPayload = MEDIA_TYPE_G729;	
		}
		break;
	case emTPAMP3:
		{
			tItem.m_emFormat = emModuleAMP3;
			tItem.m_byDynamicPayload = MEDIA_TYPE_MP3;			
		}
		break;
	case emTPAG721:
		{
			tItem.m_emFormat = emModuleAG721;
			tItem.m_byDynamicPayload = MEDIA_TYPE_G721;	
		}
		break;
	case emTPAG7221:
		{
			tItem.m_emFormat = emModuleAG7221;
			tItem.m_byDynamicPayload = MEDIA_TYPE_G7221C;
			tItem.m_wBitRate = 0x01;
			//0x00：RateNone; 0x01:Rate24; 0x02:Rate32; 0x04:Rate48
			//g7221 要填下码率 和 终端协商时用得到 科达终端支持Rate24
		}
		break;
		
	case emTPAG719:
		{
			tItem.m_emFormat = emModuleAG719;
			tItem.m_byDynamicPayload = MEDIA_TYPE_G719;			
		}
		break;
		
	case emTPAMpegAACLC:
		{
			tItem.m_emFormat = emModuleAMpegAACLC;
			tItem.m_byDynamicPayload = MEDIA_TYPE_AACLC;			
		}
		break;
		
	case emTPAMpegAACLD:
		{
			tItem.m_emFormat = emModuleAMpegAACLD;
			tItem.m_byDynamicPayload = MEDIA_TYPE_AACLD;			
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAudCapToStack unknow audio type:%d\n", emTpType ));
			break;
		}
	}
}
//TUDO
void ConvertCapFromUmsToStack(const TMakeCallPara& tCallPara, TCallCapbility& tSendCap, TCallCapbility& tRecvCap,
							  TCallDescriptTP& tSendTp, TCallDescriptTP& tRecvTp)
{
	TAudioCapbilityList tAudioItem;
	tAudioItem.Clear();
	tAudioItem.m_byNum = (u8)tCallPara.m_tCapSet.m_tAudSndCap.m_wAudFmtNum;
	tAudioItem.m_bActive = TRUE;

	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < tAudioItem.m_byNum; wIndex ++ )
	{
		ConvertAudCapToStack(tCallPara.m_tCapSet.m_tAudSndCap.m_atAudFmt[wIndex].m_emFormat, tAudioItem.m_atItem[wIndex]);
	}
	
	TVideoCapbilityList tVideoSndItem;
	tVideoSndItem.Clear();

	TVideoCapbilityList tVideoRcvItem;
	tVideoRcvItem.Clear();

	if(tCallPara.m_tCapSet.m_tVidSndCap.m_tHp.IsValid())
	{
		EmModuleVideoResolution emModuleVideoRes;
		ConvertVideoResFromUmsToStack(tCallPara.m_tCapSet.m_tVidSndCap.m_tHp.m_emRes, emModuleVideoRes);
		
		u32 dwModulePro;
		ConvertVideoProfileFromUmsToStack(tCallPara.m_tCapSet.m_tVidSndCap.m_tHp.m_emQualityLvl, dwModulePro);
		
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emFormat = emModuleVH264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emProfile = dwModulePro;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byNum = 1;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_wMaxBitrate = tCallPara.m_tCapSet.m_tVidSndCap.m_tHp.m_wBitrate;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_byMPI = (u8)tCallPara.m_tCapSet.m_tVidSndCap.m_tHp.m_wFrameRate;
		
		tVideoSndItem.m_byNum++;
		tVideoSndItem.m_bActive = TRUE;
	}

	if(tCallPara.m_tCapSet.m_tVidSndCap.m_tBp.IsValid())
	{
		EmModuleVideoResolution emModuleVideoRes;
		ConvertVideoResFromUmsToStack(tCallPara.m_tCapSet.m_tVidSndCap.m_tBp.m_emRes, emModuleVideoRes);

		u32 dwModulePro;
		ConvertVideoProfileFromUmsToStack(tCallPara.m_tCapSet.m_tVidSndCap.m_tBp.m_emQualityLvl, dwModulePro);

		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emFormat = emModuleVH264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emProfile = dwModulePro;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byNum = 1;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_wMaxBitrate = tCallPara.m_tCapSet.m_tVidSndCap.m_tBp.m_wBitrate;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_byMPI = (u8)tCallPara.m_tCapSet.m_tVidSndCap.m_tBp.m_wFrameRate;

		tVideoSndItem.m_byNum++;
		tVideoSndItem.m_bActive = TRUE;
	}

	memcpy(&tVideoRcvItem, &tVideoSndItem, sizeof(tVideoSndItem));

	u16 wSendIndex = 0;
	u16 wRecvIndex = 0;

	tSendCap.m_wAudioNum = tCallPara.m_tCapSet.m_wAudEncNum + 1;
	tSendCap.m_wVideoNum = tCallPara.m_tCapSet.m_wVidEncNum;
	tSendTp.m_wAudioNum = tCallPara.m_tCapSet.m_wAudEncNum + 1;
	tSendTp.m_wVideoNum = tCallPara.m_tCapSet.m_wVidEncNum;

	tRecvCap.m_wAudioNum = tCallPara.m_tCapSet.m_wAudDecNum + 1;
	tRecvCap.m_wVideoNum = tCallPara.m_tCapSet.m_wVidDecNum;
	tRecvTp.m_wAudioNum = tCallPara.m_tCapSet.m_wAudDecNum + 1;
	tRecvTp.m_wVideoNum = tCallPara.m_tCapSet.m_wVidDecNum;

	u16 wSignNum = 0;
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++ )
	{
		//UMS音频发送
		tSendTp.m_tAudioList[wSendIndex].m_nScreenNo = wIndex;
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atAudEnc[wIndex].m_tChanAddr.m_tRtpAddr, 
								 tAudioItem.m_tRtpAddr);
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atAudEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr, 
								 tAudioItem.m_tRtcpAddr);
		tAudioItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_audio_recv_handle, wIndex);
		tSendCap.m_atAudioCapList[wSendIndex] = tAudioItem;

		//UMS视频发送
		tSendTp.m_tVideoList[wSendIndex].m_nScreenNo = wIndex;
		tSendTp.m_tVideoList[wSendIndex].m_nPACapSignNum = 1;

		tSendTp.m_tVideoList[wSendIndex].m_aemPACapSign[0] = emPACapSmall;
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tRtpAddr, 
					tSendTp.m_tVideoList[wSendIndex].m_atRtpAddr[0]);
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atSmallVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr, 
					tSendTp.m_tVideoList[wSendIndex].m_atRtcpAddr[0]);

		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atVidEnc[wIndex].m_tChanAddr.m_tRtpAddr, 
								 tVideoSndItem.m_tRtpAddr);
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atVidEnc[wIndex].m_tChanAddr.m_tBackRtcpAddr, 
								 tVideoSndItem.m_tRtcpAddr);
		tVideoSndItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_video_recv_handle, wIndex);
		tSendCap.m_atVideoCapList[wSendIndex] = tVideoSndItem;		
	
		++wSendIndex;

		//UMS音频接收
		tRecvTp.m_tAudioList[wRecvIndex].m_nScreenNo = wIndex;
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr, 
								 tAudioItem.m_tRtpAddr);
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atAudDec[wIndex].m_tChanAddr.m_tBackRtcpAddr, 
								 tAudioItem.m_tRtcpAddr);
		tAudioItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_audio_send_handle, wIndex);
		tRecvCap.m_atAudioCapList[wRecvIndex] = tAudioItem;

		//UMS视频接收
		tRecvTp.m_tVideoList[wRecvIndex].m_nScreenNo = wIndex;
		tRecvTp.m_tVideoList[wRecvIndex].m_nPACapSignNum = 1;
		tRecvTp.m_tVideoList[wRecvIndex].m_aemPACapSign[0] = emPACapSmall;		
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atSmallVidDec[wIndex].m_tChanAddr.m_tRtpAddr, 
								tRecvTp.m_tVideoList[wRecvIndex].m_atRtpAddr[0]);
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atSmallVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr, 
								tRecvTp.m_tVideoList[wRecvIndex].m_atRtcpAddr[0]);

		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr, 
								 tVideoRcvItem.m_tRtpAddr);
		ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_atVidDec[wIndex].m_tChanAddr.m_tBackRtcpAddr, 
							     tVideoRcvItem.m_tRtcpAddr);
		tVideoRcvItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_video_send_handle, wIndex);
		tRecvCap.m_atVideoCapList[wRecvIndex] = tVideoRcvItem;
		
		++wRecvIndex;
	}
	
	//混音通道
	tSendTp.m_tAudioList[wSendIndex].m_nScreenNo = 0;
	tSendTp.m_tAudioList[wSendIndex].m_bAudMix = TRUE;
	ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_tAudMixEnc.m_tChanAddr.m_tRtpAddr, 
							 tAudioItem.m_tRtpAddr);
	ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_tAudMixEnc.m_tChanAddr.m_tBackRtcpAddr, 
							 tAudioItem.m_tRtcpAddr);
	tAudioItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_audio_recv_mix_handle, 0);
	tSendCap.m_atAudioCapList[wSendIndex] = tAudioItem;

	tRecvTp.m_tAudioList[wRecvIndex].m_nScreenNo = 0;
	tRecvTp.m_tAudioList[wRecvIndex].m_bAudMix = TRUE;
	ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_tAudMixDec.m_tChanAddr.m_tRtpAddr, 
						 	 tAudioItem.m_tRtpAddr);
	ConverAddrFromUmsToStack(tCallPara.m_tCapSet.m_tAudMixDec.m_tChanAddr.m_tBackRtcpAddr, 
							 tAudioItem.m_tRtcpAddr);
	tAudioItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_audio_send_mix_handle, 0);
	tRecvCap.m_atAudioCapList[wRecvIndex] = tAudioItem;

	//双流能力 针对323MT，makecall和answercall时都携带
 	if ( tCallPara.m_tCallInfo.m_emTpProtocol == emTpH323 )
 	{
 		ConverDualInfoFromUmsToStackForMakeCall(tSendCap.m_tDualCapList, tRecvCap.m_tDualCapList, 
 												tCallPara.m_tDualCapSet);
 	}
}

void ConverAddrFromUmsToStack(const TTPTransAddr& tTpAddr, TModuleTransportAddress& tModuleAddr)
{
	tModuleAddr.m_dwIp = tTpAddr.m_dwIP;
	tModuleAddr.m_wPort = tTpAddr.m_wPort;
}

void ConvertSipRegInfoFromUmsToStack(TPARegCfg& tPaRegCfg, TUmsSipRegCfg& tRegCfg, TTPAlias atAlias[], u16 wAliasNum)
{
	tPaRegCfg.m_dwHostIP  = GetLocalIpByDstIp(tRegCfg.dwRegIP);//tRegCfg.m_atAdaptAddr[0].m_dwIP;
	tPaRegCfg.m_wHostPort = TP_UMS_SIP_LISTIEN_PORT;//tRegCfg.m_atAdaptAddr[0].m_wPort;
	tPaRegCfg.m_dwRegIP   = tRegCfg.dwRegIP;
	tPaRegCfg.m_wRegPort  = tRegCfg.wRegPort;
	tPaRegCfg.m_wExpire   = tRegCfg.wExpire;
	tPaRegCfg.m_emConnection = emPATcpConnection;

	//Protocol_file
	tPaRegCfg.m_dwQtID = tRegCfg.m_dwQTId;

	tPaRegCfg.m_tRegistLocalInfo.m_emEndpointType = emPAEndpointTypeUMS;
	tPaRegCfg.m_tRegistLocalInfo.m_dwLocalIP = tPaRegCfg.m_dwHostIP;
	memcpy(tPaRegCfg.m_tRegistLocalInfo.m_achCompileTime, tRegCfg.achCompileTm, sizeof(tPaRegCfg.m_tRegistLocalInfo.m_achCompileTime));
	tPaRegCfg.m_tRegistLocalInfo.m_achCompileTime[TPMODULE_MAX_NAME_LEN] = '\0'; 
	memcpy(tPaRegCfg.m_tRegistLocalInfo.m_achSoftVersion, UMS_VerID, sizeof(tPaRegCfg.m_tRegistLocalInfo.m_achSoftVersion));
	tPaRegCfg.m_tRegistLocalInfo.m_achSoftVersion[TPMODULE_MAX_NAME_LEN] = '\0';
	
	tPaRegCfg.m_nPARegNameSize = wAliasNum;
	for (u16 wIndex = 0; wIndex < wAliasNum; ++wIndex)
	{
		switch (atAlias[wIndex].m_byType)
		{
		case tp_Alias_Unknow:
			{
				tPaRegCfg.m_atPARegName[wIndex].m_emPAAddrType = emPAUnknown;
				break;
			}

		case tp_Alias_e164:
			{
				tPaRegCfg.m_atPARegName[wIndex].m_emPAAddrType = emPAE164Num;
				break;
			}

		case tp_Alias_h323:
			{
				tPaRegCfg.m_atPARegName[wIndex].m_emPAAddrType = emPAAlias;
				break;
			}

		case tp_Alias_IP:
			{
				tPaRegCfg.m_atPARegName[wIndex].m_emPAAddrType = emPAIPAddr;
				break;
			}
		}

		s8 *pzAliasUTF8 = NULL;
		gb2312_to_utf8((s8 *)atAlias[wIndex].m_abyAlias, &pzAliasUTF8);
		strncpy((s8 *)tPaRegCfg.m_atPARegName[wIndex].m_achUserName, pzAliasUTF8, TP_MAX_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
	}
}

void ConvertGkRegInfoFromUmsToStack(TRegistReq& tRegInfo, TRegCfg& tRegCfg, u16 wAliasNum)
{
	u16 wE164Index = 0;
	u16 wH323Index = 0;
	for (u16 wIndex = 0; wIndex < wAliasNum; ++wIndex)
	{
		 switch (tRegCfg.m_tAlias[wIndex].m_byType)
		 {
		 case tp_Alias_e164:
			 {
// 				 s8 *pzAliasUTF8 = NULL;
// 				 gb2312_to_utf8((s8 *)tRegCfg.m_tAlias[wIndex].m_abyAlias, &pzAliasUTF8);
				 strncpy((s8 *)tRegInfo.m_atE164[wE164Index].m_abyCallAliasAddr, tRegCfg.m_tAlias[wIndex].m_abyAlias, TP_MAX_ALIAS_LEN);
//				 free(pzAliasUTF8);
				 ++wE164Index;
				 break;
			 }
			 
		 case tp_Alias_h323:
			 {
// 				 s8 *pzAliasUTF8 = NULL;
// 				 gb2312_to_utf8((s8 *)tRegCfg.m_tAlias[wIndex].m_abyAlias, &pzAliasUTF8);
				 strncpy((s8 *)tRegInfo.m_atH323Alias[wH323Index].m_abyCallAliasAddr, tRegCfg.m_tAlias[wIndex].m_abyAlias, TP_MAX_ALIAS_LEN);
//				 free(pzAliasUTF8);
				 ++wH323Index;
				 break;
			 }
			 
		 default:
			 {
				 MdlError(Ums_Mdl_Stack, ("ConvertGkRegInfoFromUmsToStack unknow address type :%d, name:%s\n", 
										 tRegCfg.m_tAlias[wIndex].m_byType, tRegCfg.m_tAlias[wIndex].m_abyAlias));
				 break;
			 }
		}
	 }
	 
	tRegInfo.m_tLocalAddress.m_dwIp = GetLocalIpByDstIp(tRegCfg.m_tGKAddress.m_dwIP);//tRegCfg.m_tLocalAddress.m_dwIP;
	tRegInfo.m_tLocalAddress.m_wPort = TP_DEFAULT_H225_PORT;
	 
	tRegInfo.m_tGKAddress.m_dwIp = tRegCfg.m_tGKAddress.m_dwIP;
	tRegInfo.m_dwQtID = tRegCfg.m_dwQTId;

	tRegInfo.m_nTimeToLive = tRegCfg.m_nTimeToLive;
}

void ConvertDualParamFromStackToUms(TChanConnectedInfo *ptChanInfo, TUmsNodeCapset& tNodeCap)
{
	tNodeCap.m_wVidDecNum = 0;
	tNodeCap.m_wVidEncNum = 0;

	TChanNetPara* ptChan = NULL;

	if (emModuleAudioType == ptChanInfo->m_tChanType.m_emAVType)
	{
		if (emModuleChannelRecv == ptChanInfo->m_tChanType.m_emDirection)
		{
			tNodeCap.m_atVidEnc[tNodeCap.m_wVidEncNum].m_tChanAddr.m_tBackRtcpAddr.SetAddr(ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																						   ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
			tNodeCap.m_atVidEnc[tNodeCap.m_wVidEncNum].m_tPAHandle = (s32)ptChanInfo->m_hChan;
			++tNodeCap.m_wVidEncNum;
		}
		else
		{
			if (emModuleChannelSend == ptChanInfo->m_tChanType.m_emDirection)
			{
				tNodeCap.m_atVidDec[tNodeCap.m_wVidDecNum].m_tChanAddr.m_tRtpAddr.SetAddr(ptChanInfo->m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
																						  ptChanInfo->m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
				tNodeCap.m_atVidDec[tNodeCap.m_wVidDecNum].m_tChanAddr.m_tBackRtcpAddr.SetAddr(ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																							   ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
				tNodeCap.m_atVidDec[tNodeCap.m_wVidDecNum].m_tPAHandle = (s32)ptChanInfo->m_hChan;
				++tNodeCap.m_wVidDecNum;
			}
			else
			{
				if (emModuleChannelBidirectional == ptChanInfo->m_tChanType.m_emDirection)
				{
					tNodeCap.m_atVidEnc[tNodeCap.m_wVidEncNum].m_tChanAddr.m_tBackRtcpAddr.SetAddr(ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																							       ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
					tNodeCap.m_atVidEnc[tNodeCap.m_wVidEncNum].m_tPAHandle = (s32)ptChanInfo->m_hChan;
					++tNodeCap.m_wVidEncNum;

					tNodeCap.m_atVidDec[tNodeCap.m_wVidDecNum].m_tChanAddr.m_tRtpAddr.SetAddr(ptChanInfo->m_tCapsetInfo.m_tPeerRtpAddr.m_dwIp,
																						  ptChanInfo->m_tCapsetInfo.m_tPeerRtpAddr.m_wPort);
					tNodeCap.m_atVidDec[tNodeCap.m_wVidDecNum].m_tChanAddr.m_tBackRtcpAddr.SetAddr(ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_dwIp, 
																							ptChanInfo->m_tCapsetInfo.m_tPeerRtcpAddr.m_wPort);
					tNodeCap.m_atVidDec[tNodeCap.m_wVidDecNum].m_tPAHandle = (s32)ptChanInfo->m_hChan;
					++tNodeCap.m_wVidDecNum;
				}
				else
				{
					MdlError(Ums_Mdl_Stack, ("ConvertDualParamFromStackToUms error video direct :%d", ptChanInfo->m_tChanType.m_emAVType));
			
				}
			}
		}
	}
	else
	{
		MdlError(Ums_Mdl_Stack, ("ConvertDualParamFromStackToUms error video direct :%d", ptChanInfo->m_tChanType.m_emAVType));
	}
}

void ConverDualInfoFromUmsToStack(TDualCapList& tDualCapList, const TUmsNodeCapset& tNodeCapSet)
{
	TAudioCapbilityList tAudCap;
	tAudCap.m_bActive = TRUE;
	tAudCap.m_byNum = (u8)tNodeCapSet.m_tAudSndCap.m_wAudFmtNum;

	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < tAudCap.m_byNum; wIndex ++ )
	{
		ConvertAudCapToStack(tNodeCapSet.m_tAudSndCap.m_atAudFmt[wIndex].m_emFormat, tAudCap.m_atItem[wIndex]);
	}

	if (tNodeCapSet.m_wAudEncNum > 0)
	{
		//音频发送
		tAudCap.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_audsnd_handle, 0); 
		tDualCapList.m_tCallCap.m_wSndAudNum = tNodeCapSet.m_wAudEncNum;
		ConverAddrFromUmsToStack(tNodeCapSet.m_atAudEnc[0].m_tChanAddr.m_tRtpAddr, tAudCap.m_tRtpAddr);
		ConverAddrFromUmsToStack(tNodeCapSet.m_atAudEnc[0].m_tChanAddr.m_tBackRtcpAddr, tAudCap.m_tRtcpAddr);
		tDualCapList.m_tCallCap.m_atSndAudCap[0] = tAudCap;
	}

	if (tNodeCapSet.m_wAudDecNum > 0)
	{
		//音频接收
		tAudCap.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_audrcv_handle, 0); 
		tDualCapList.m_tCallCap.m_wRcvAudNum = tNodeCapSet.m_wAudDecNum;
		ConverAddrFromUmsToStack(tNodeCapSet.m_atAudDec[0].m_tChanAddr.m_tRtpAddr, tAudCap.m_tRtpAddr);
		ConverAddrFromUmsToStack(tNodeCapSet.m_atAudDec[0].m_tChanAddr.m_tBackRtcpAddr, tAudCap.m_tRtcpAddr);
		tDualCapList.m_tCallCap.m_atRcvAudCap[0] = tAudCap;
	}


	TVideoCapbilityList tVideoSndItem;
	tVideoSndItem.Clear();
	
	TVideoCapbilityList tVideoRcvItem;
	tVideoRcvItem.Clear();
	
	if(tNodeCapSet.m_tVidSndCap.m_tHp.IsValid())
	{
		EmModuleVideoResolution emModuleVideoRes;
		ConvertVideoResFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tHp.m_emRes, emModuleVideoRes);
		
		u32 dwModulePro;
		ConvertVideoProfileFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tHp.m_emQualityLvl, dwModulePro);
		
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emFormat = emModuleVH264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emProfile = dwModulePro;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byNum = 1;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_wMaxBitrate = tNodeCapSet.m_tVidSndCap.m_tHp.m_wBitrate;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_byMPI = (u8)tNodeCapSet.m_tVidSndCap.m_tHp.m_wFrameRate;
		
		tVideoSndItem.m_byNum++;
		tVideoSndItem.m_bActive = TRUE;
	}
	
	if(tNodeCapSet.m_tVidSndCap.m_tBp.IsValid())
	{
		EmModuleVideoResolution emModuleVideoRes;
		ConvertVideoResFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tBp.m_emRes, emModuleVideoRes);
		
		u32 dwModulePro;
		ConvertVideoProfileFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tBp.m_emQualityLvl, dwModulePro);
		
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emFormat = emModuleVH264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emProfile = dwModulePro;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byNum = 1;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_wMaxBitrate = tNodeCapSet.m_tVidSndCap.m_tBp.m_wBitrate;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_byMPI = (u8)tNodeCapSet.m_tVidSndCap.m_tBp.m_wFrameRate;
		
		tVideoSndItem.m_byNum++;
		tVideoSndItem.m_bActive = TRUE;
	}
	
	memcpy(&tVideoRcvItem, &tVideoSndItem, sizeof(tVideoSndItem));


	if (tNodeCapSet.m_wVidEncNum > 0)
	{
		//视频发送
		tVideoSndItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_vidsnd_handle, 0);
		tDualCapList.m_tCallCap.m_wSndVidNum = tNodeCapSet.m_wVidEncNum;
		ConverAddrFromUmsToStack(tNodeCapSet.m_atVidEnc[0].m_tChanAddr.m_tRtpAddr, tVideoSndItem.m_tRtpAddr);
		ConverAddrFromUmsToStack(tNodeCapSet.m_atVidEnc[0].m_tChanAddr.m_tBackRtcpAddr, tVideoSndItem.m_tRtcpAddr);
		tDualCapList.m_tCallCap.m_atSndVidCap[0] = tVideoSndItem;
	}

	if (tNodeCapSet.m_wVidDecNum > 0)
	{
		//视频接收
		tVideoRcvItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_vidrcv_handle, 0);
		tDualCapList.m_tCallCap.m_wRcvVidNum = tNodeCapSet.m_wVidDecNum;
		ConverAddrFromUmsToStack(tNodeCapSet.m_atVidDec[0].m_tChanAddr.m_tRtpAddr, tVideoRcvItem.m_tRtpAddr);
		ConverAddrFromUmsToStack(tNodeCapSet.m_atVidDec[0].m_tChanAddr.m_tBackRtcpAddr, tVideoRcvItem.m_tRtcpAddr);
		tDualCapList.m_tCallCap.m_atRcvVidCap[0] = tVideoRcvItem;
	}
}

void ConverDualInfoFromUmsToStack( TDualCapList& tDualCapList, const TUmsDualCapsetMc& tNodeCapSet)
{
	TAudioCapbilityList tAudCap;
	tAudCap.m_bActive = TRUE;
	tAudCap.m_byNum = (u8)tNodeCapSet.m_tAudCap.m_wAudFmtNum;
	
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < tAudCap.m_byNum; wIndex ++ )
	{
		ConvertAudCapToStack(tNodeCapSet.m_tAudCap.m_atAudFmt[wIndex].m_emFormat, tAudCap.m_atItem[wIndex]);
	}

	//音频发送
	tAudCap.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_audsnd_handle, 0); 
	tDualCapList.m_tCallCap.m_wSndAudNum = 1;
	ConverAddrFromUmsToStack(tNodeCapSet.m_tAudEnc.m_tChanAddr.m_tRtpAddr, tAudCap.m_tRtpAddr);
	ConverAddrFromUmsToStack(tNodeCapSet.m_tAudEnc.m_tChanAddr.m_tBackRtcpAddr, tAudCap.m_tRtcpAddr);
	tDualCapList.m_tCallCap.m_atSndAudCap[0] = tAudCap;

	//音频接收
	tAudCap.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_audrcv_handle, 0); 
	tDualCapList.m_tCallCap.m_wRcvAudNum = 1;
	ConverAddrFromUmsToStack(tNodeCapSet.m_tAudDec.m_tChanAddr.m_tRtpAddr, tAudCap.m_tRtpAddr);
	ConverAddrFromUmsToStack(tNodeCapSet.m_tAudDec.m_tChanAddr.m_tBackRtcpAddr, tAudCap.m_tRtcpAddr);
	tDualCapList.m_tCallCap.m_atRcvAudCap[0] = tAudCap;
	
	TVideoCapbilityList tVideoSndItem;
	tVideoSndItem.Clear();
	
	TVideoCapbilityList tVideoRcvItem;
	tVideoRcvItem.Clear();
	
	if(tNodeCapSet.m_tVidSndCap.m_tHp.IsValid())
	{
		EmModuleVideoResolution emModuleVideoRes;
		ConvertVideoResFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tHp.m_emRes, emModuleVideoRes);
		
		u32 dwModulePro;
		ConvertVideoProfileFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tHp.m_emQualityLvl, dwModulePro);
		
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emFormat = emModuleVH264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emProfile = dwModulePro;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byNum = 1;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_wMaxBitrate = tNodeCapSet.m_tVidSndCap.m_tHp.m_wBitrate;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_byMPI = (u8)tNodeCapSet.m_tVidSndCap.m_tHp.m_wFrameRate;
		
		tVideoSndItem.m_byNum++;
		tVideoSndItem.m_bActive = TRUE;
	}
	
	if(tNodeCapSet.m_tVidSndCap.m_tBp.IsValid())
	{
		EmModuleVideoResolution emModuleVideoRes;
		ConvertVideoResFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tBp.m_emRes, emModuleVideoRes);
		
		u32 dwModulePro;
		ConvertVideoProfileFromUmsToStack(tNodeCapSet.m_tVidSndCap.m_tBp.m_emQualityLvl, dwModulePro);
		
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emFormat = emModuleVH264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_emProfile = dwModulePro;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_byNum = 1;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_wMaxBitrate = tNodeCapSet.m_tVidSndCap.m_tBp.m_wBitrate;
		tVideoSndItem.m_atList[tVideoSndItem.m_byNum].m_atItem[0].m_byMPI = (u8)tNodeCapSet.m_tVidSndCap.m_tBp.m_wFrameRate;
		
		tVideoSndItem.m_byNum++;
		tVideoSndItem.m_bActive = TRUE;
	}
	
	memcpy(&tVideoRcvItem, &tVideoSndItem, sizeof(tVideoSndItem));
	
	//视频发送
	tVideoSndItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_vidsnd_handle, 0);
	tDualCapList.m_tCallCap.m_wSndVidNum = 1;
	ConverAddrFromUmsToStack(tNodeCapSet.m_tVidEnc.m_tChanAddr.m_tRtpAddr, tVideoSndItem.m_tRtpAddr);
	ConverAddrFromUmsToStack(tNodeCapSet.m_tVidEnc.m_tChanAddr.m_tBackRtcpAddr, tVideoSndItem.m_tRtcpAddr);
	tDualCapList.m_tCallCap.m_atSndVidCap[0] = tVideoSndItem;

	//视频接收
	tVideoRcvItem.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_vidrcv_handle, 0);
	tDualCapList.m_tCallCap.m_wRcvVidNum = 1;
	ConverAddrFromUmsToStack(tNodeCapSet.m_tVidDec.m_tChanAddr.m_tRtpAddr, tVideoRcvItem.m_tRtpAddr);
	ConverAddrFromUmsToStack(tNodeCapSet.m_tVidDec.m_tChanAddr.m_tBackRtcpAddr, tVideoRcvItem.m_tRtcpAddr);
	tDualCapList.m_tCallCap.m_atRcvVidCap[0] = tVideoRcvItem;
}

void ConverDualInfoFromUmsToStackForMakeCall(TVideoCapbilityList& tSndDualCapList, 
											 TVideoCapbilityList& tRecvDualCapList, 
											 const TUmsDualCapsetMc& tDualCapSet)
{	

// 	TVideoCapbilityList tVideoSndItem;
// 	tVideoSndItem.Clear();
	tSndDualCapList.Clear();
// 	
// 	TVideoCapbilityList tVideoRcvItem;
// 	tVideoRcvItem.Clear();
	tRecvDualCapList.Clear();

	{
		if(tDualCapSet.m_tVidSndCap.m_tHp.IsValid())
		{
			EmModuleVideoResolution emModuleVideoRes;
			ConvertVideoResFromUmsToStack(tDualCapSet.m_tVidSndCap.m_tHp.m_emRes, emModuleVideoRes);
			
			u32 dwModulePro;
			ConvertVideoProfileFromUmsToStack(tDualCapSet.m_tVidSndCap.m_tHp.m_emQualityLvl, dwModulePro);
			
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_emFormat = emModuleVH264;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_emProfile = dwModulePro;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_byNum = 1;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_atItem[0].m_wMaxBitrate = tDualCapSet.m_tVidSndCap.m_tHp.m_wBitrate;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_atItem[0].m_byMPI = (u8)tDualCapSet.m_tVidSndCap.m_tHp.m_wFrameRate;
			
			tSndDualCapList.m_byNum++;
			tSndDualCapList.m_bActive = TRUE;
		}
		
		if(tDualCapSet.m_tVidSndCap.m_tBp.IsValid())
		{
			EmModuleVideoResolution emModuleVideoRes;
			ConvertVideoResFromUmsToStack(tDualCapSet.m_tVidSndCap.m_tBp.m_emRes, emModuleVideoRes);
			
			u32 dwModulePro;
			ConvertVideoProfileFromUmsToStack(tDualCapSet.m_tVidSndCap.m_tBp.m_emQualityLvl, dwModulePro);
			
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_emFormat = emModuleVH264;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_emProfile = dwModulePro;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_byNum = 1;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_atItem[0].m_wMaxBitrate = tDualCapSet.m_tVidSndCap.m_tBp.m_wBitrate;
			tSndDualCapList.m_atList[tSndDualCapList.m_byNum].m_atItem[0].m_byMPI = (u8)tDualCapSet.m_tVidSndCap.m_tBp.m_wFrameRate;
			
			tSndDualCapList.m_byNum++;
			tSndDualCapList.m_bActive = TRUE;
		}
	
	}
	
	{
		if(tDualCapSet.m_tVidRcvCap.m_tHp.IsValid())
		{
			EmModuleVideoResolution emModuleVideoRes;
			ConvertVideoResFromUmsToStack(tDualCapSet.m_tVidRcvCap.m_tHp.m_emRes, emModuleVideoRes);
			
			u32 dwModulePro;
			ConvertVideoProfileFromUmsToStack(tDualCapSet.m_tVidRcvCap.m_tHp.m_emQualityLvl, dwModulePro);
			
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_emFormat = emModuleVH264;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_emProfile = dwModulePro;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_byNum = 1;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_atItem[0].m_wMaxBitrate = tDualCapSet.m_tVidRcvCap.m_tHp.m_wBitrate;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_atItem[0].m_byMPI = (u8)tDualCapSet.m_tVidRcvCap.m_tHp.m_wFrameRate;
			
			tRecvDualCapList.m_byNum++;
			tRecvDualCapList.m_bActive = TRUE;
		}
		
		if(tDualCapSet.m_tVidRcvCap.m_tBp.IsValid())
		{
			EmModuleVideoResolution emModuleVideoRes;
			ConvertVideoResFromUmsToStack(tDualCapSet.m_tVidRcvCap.m_tBp.m_emRes, emModuleVideoRes);
			
			u32 dwModulePro;
			ConvertVideoProfileFromUmsToStack(tDualCapSet.m_tVidRcvCap.m_tBp.m_emQualityLvl, dwModulePro);
			
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_emFormat = emModuleVH264;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_byDynamicPayload = MEDIA_TYPE_H264;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_emProfile = dwModulePro;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_byNum = 1;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_atItem[0].m_emRes = emModuleVideoRes;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_atItem[0].m_wMaxBitrate = tDualCapSet.m_tVidRcvCap.m_tBp.m_wBitrate;
			tRecvDualCapList.m_atList[tRecvDualCapList.m_byNum].m_atItem[0].m_byMPI = (u8)tDualCapSet.m_tVidRcvCap.m_tBp.m_wFrameRate;
			
			tRecvDualCapList.m_byNum++;
			tRecvDualCapList.m_bActive = TRUE;
		}
	}


	//视频发送
	tSndDualCapList.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_vidsnd_handle, 0);
	ConverAddrFromUmsToStack(tDualCapSet.m_tVidEnc.m_tChanAddr.m_tRtpAddr, tSndDualCapList.m_tRtpAddr);
	ConverAddrFromUmsToStack(tDualCapSet.m_tVidEnc.m_tChanAddr.m_tBackRtcpAddr, tSndDualCapList.m_tRtcpAddr);

	//视频接收
	tRecvDualCapList.m_hAppChan = (HMDLAPPCHANNEL)CTpTypeAdpt::GetChannelHandle(em_second_vidrcv_handle, 0);
	ConverAddrFromUmsToStack(tDualCapSet.m_tVidDec.m_tChanAddr.m_tRtpAddr, tRecvDualCapList.m_tRtpAddr);
	ConverAddrFromUmsToStack(tDualCapSet.m_tVidDec.m_tChanAddr.m_tBackRtcpAddr, tRecvDualCapList.m_tRtcpAddr);
	
}

static void ConvertKeyPathFromStackToUms(const TPAEpKeyID& tPA, TEpPathKey& tUms)
{
	strncpy(tUms.m_szEpID, tPA.m_achEpID, TP_MAX_EPID_LEN);
}

static void ConvertEpKeyPathFromStackToUms(const TPAEpPathKey& tPA, TEpPathKey& tUms)
{
	strncpy(tUms.m_szEpID, tPA.m_achEpID, TP_MAX_EPID_LEN);
}
void ConvertCallTypeFromStackToUms(const EmPAAliasType& emPA, EmTpAliasType& emUms)
{
	switch(emPA)
	{
	case emPA_Alias_Unknow:
		{
			emUms = tp_Alias_Unknow;
			break;
		}
	case emPA_Alias_e164:
		{
			emUms  = tp_Alias_e164;
			break;
		}
	case emPA_Alias_h323:
		{
			emUms  = tp_Alias_h323;
			break;
		}
	case emPA_Alias_IP:
		{
			emUms  = tp_Alias_IP;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertCallTypeFromStackToUms Unknow Call type:%d\n", emPA));
			break;
		}
	}

}
void ConvertAliasFromStackToUms(const TPAAlias& tPA, TTPAlias& tUms)
{
	switch(tPA.m_emType)
	{
	case emPA_Alias_Unknow:
		{
			tUms.m_byType = tp_Alias_Unknow;
			break;
		}
	case emPA_Alias_e164:
		{
			tUms.m_byType = tp_Alias_e164;
			break;
		}
	case emPA_Alias_h323:
		{
			tUms.m_byType = tp_Alias_h323;
			break;
		}
	case emPA_Alias_IP:
		{
			tUms.m_byType = tp_Alias_IP;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAliasFromStackToUms Unknow alias type:%d\n", tPA.m_emType));
			break;
		}
	}

	strncpy(tUms.m_abyAlias, tPA.m_achAlias, TP_MAX_ALIAS_LEN);
	tUms.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
}

u16 ConvertNodeCallUpdateFromStackToUms(TConfNodeCallUpdateTrList& tUms, const TPAConfNodeUpdateTrList& tPA)
{
	u16 wNum = min(tPA.m_wNum, TP_REFRESH_LIST_THREE);
	tUms.m_wNum = wNum;
	s8 *pzAliasUTF8 = NULL;
	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
		ConvertKeyPathFromStackToUms(tPA.m_atList[wIndex].m_tID, tUms.m_atList[wIndex].m_tID);
		tUms.m_atList[wIndex].m_wEpID = tPA.m_atList[wIndex].m_wEpID;
		
		tUms.m_atList[wIndex].m_emEpType = (EmTPEndpointType)tPA.m_atList[wIndex].m_dwEpType;
		
		tUms.m_atList[wIndex].m_emCallState = (EmUmsConfNodeState)tPA.m_atList[wIndex].m_dwCallState;
		tUms.m_atList[wIndex].m_emCallReason = (EmCnsCallReason)tPA.m_atList[wIndex].m_dwCallReason;
		
		ConvertAliasFromStackToUms(tPA.m_atList[wIndex].m_tCalledAddr, tUms.m_atList[wIndex].m_tCalledAddr.m_tAlias);
		ConvertVendorFromStackToUms(tPA.m_atList[wIndex].m_emVendorID, tUms.m_atList[wIndex].m_emVendorID);
		
		utf8_to_gb2312((s8 *)tUms.m_atList[wIndex].m_tCalledAddr.m_tAlias.m_abyAlias, &pzAliasUTF8);
		strncpy((s8 *)tUms.m_atList[wIndex].m_tCalledAddr.m_tAlias.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;

		ConvertAliasFromStackToUms(tPA.m_atList[wIndex].m_tConfName, tUms.m_atList[wIndex].m_tConfName);

		utf8_to_gb2312((s8 *)tUms.m_atList[wIndex].m_tConfName.m_abyAlias, &pzAliasUTF8);
		strncpy((s8 *)tUms.m_atList[wIndex].m_tConfName.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;

		
		tUms.m_atList[wIndex].m_emLevel = (EmTPSipLevel)tPA.m_atList[wIndex].m_wLevel;
		tUms.m_atList[wIndex].m_enRcvAlignType = (EmTPRcvAlignType)tPA.m_atList[wIndex].m_dwRcvAlignType;
		
		tUms.m_atList[wIndex].m_bMute = tPA.m_atList[wIndex].m_bMute;
		tUms.m_atList[wIndex].m_bQuiet = tPA.m_atList[wIndex].m_bQuiet;
		tUms.m_atList[wIndex].m_wSpearkIndex = tPA.m_atList[wIndex].m_wSpearkIndex;
		tUms.m_atList[wIndex].m_wDualIndex = tPA.m_atList[wIndex].m_wDualIndex;
	}
	return TP_RET_OK;
}

u16 ConvertNodeChanUpdateFromStackToUms(TConfNodeChanUpdateTrList& tUms, const TPAConfNodeUpdateB2NEWTrList& tPA)
{
	u16 wNum = min(tPA.m_wNum, TP_REFRESH_LIST_THREE);
	tUms.m_wNum = wNum;
	
	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
//		ConvertEpKeyPathFromStackToUms(tPA.m_atList[wIndex].tID.m_tKey, tUms.m_atList[wIndex].tID.m_tKey);
		tUms.m_atList[wIndex].tID.m_wEpID = tPA.m_atList[wIndex].m_tID.m_wEpID;
		tUms.m_atList[wIndex].wEpID = tPA.m_atList[wIndex].m_wEpID;
		tUms.m_atList[wIndex].bChanOpen = tPA.m_atList[wIndex].m_bChanOpen;
		tUms.m_atList[wIndex].bInPoll = tPA.m_atList[wIndex].m_bInPoll;

		tUms.m_atList[wIndex].bSmallOpenDec = tPA.m_atList[wIndex].m_bSmallOpenDec;
		tUms.m_atList[wIndex].bSmallOpenEnc = tPA.m_atList[wIndex].m_bSmallOpenEnc;

		tUms.m_atList[wIndex].wVidRcv = tPA.m_atList[wIndex].m_wVidRcv;
		tUms.m_atList[wIndex].wVidSnd = tPA.m_atList[wIndex].m_wVidSnd;
		tUms.m_atList[wIndex].wAudRcv = tPA.m_atList[wIndex].m_wAudRcv;
		tUms.m_atList[wIndex].wAudSnd = tPA.m_atList[wIndex].m_wAudSnd;

		ConvertVidInfoFromStackToUms(tPA.m_atList[wIndex].m_tVidRcv, tUms.m_atList[wIndex].tVidRcv);
		ConvertVidInfoFromStackToUms(tPA.m_atList[wIndex].m_tVidSnd, tUms.m_atList[wIndex].tVidSnd);
		ConvertVidInfoFromStackToUms(tPA.m_atList[wIndex].m_tDualVidRcv, tUms.m_atList[wIndex].tDualVidRcv);
		ConvertVidInfoFromStackToUms(tPA.m_atList[wIndex].m_tDualVidSnd, tUms.m_atList[wIndex].tDualVidSnd);

		ConvertAudInfoFromStackToUms(tPA.m_atList[wIndex].m_tAudRcv, tUms.m_atList[wIndex].tAudRcv);
		ConvertAudInfoFromStackToUms(tPA.m_atList[wIndex].m_tAudSnd, tUms.m_atList[wIndex].tAudSnd);
		ConvertAudInfoFromStackToUms(tPA.m_atList[wIndex].m_tDualAudRcv, tUms.m_atList[wIndex].tDualAudRcv);
		ConvertAudInfoFromStackToUms(tPA.m_atList[wIndex].m_tDualAudSnd, tUms.m_atList[wIndex].tDualAudSnd);
		
		memcpy(tUms.m_atList[wIndex].awPd, tPA.m_atList[wIndex].m_awPd, sizeof(tUms.m_atList[wIndex].awPd));
	}
	return TP_RET_OK;
}

u16 ConvertNodeDelFromStackToUms(TConfNodeDelTrList& tUms, const TPAConfNodeDelTrList& tPA)
{
	u16 wNum = min(tPA.m_wNum, TP_REFRESH_LIST_THREE);
	tUms.m_wNum = wNum;

	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
//		ConvertEpKeyPathFromStackToUms(tPA.m_atList[wIndex].m_tKey, tUms.m_atList[wIndex].m_tKey);
		tUms.m_atList[wIndex].m_wEpID = tPA.m_atList[wIndex].m_wEpID;
	}
	return TP_RET_OK;
}

void ConvertConfNetAddrFromStackToUms(TTPTransAddr& tUms, const TPAIPAddress& tPA)
{
	tUms.m_dwIP = tPA.m_dwIP;
	tUms.m_wPort = tPA.m_wPort;
}

u16 ConvertConfPollAckFromStackToUms(TPAPollAck& tPA, TPollAckTr& tPollAck)
{
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertConfNetAddrFromStackToUms(tPollAck.m_tAddr[wIndex].m_tRtpAddr, tPA.m_atRtpAddr[wIndex]);
		ConvertConfNetAddrFromStackToUms(tPollAck.m_tAddr[wIndex].m_tRtcpAddr, tPA.m_atRtcpAddr[wIndex]);
		ConvertConfNetAddrFromStackToUms(tPollAck.m_tAddr[wIndex].m_tBackRtcpAddr, tPA.m_atBackRtcpAddr[wIndex]);
	}
	tPollAck.m_wReason = tPA.m_wReason;
	return TP_RET_OK;
}

u16 ConvertEpKeyFromStackToUms( const TPAEpKey& tPA, TEpKey& tUms )
{
//	strncpy(tUms.m_tKey.m_szEpID, tPA.m_tKey.m_szEpID, TP_MAX_EPID_LEN);
//	tUms.m_tKey.m_szEpID[TP_MAX_EPID_LEN] = '\0';

	tUms.m_wEpID = tPA.m_wEpID;

	return TP_RET_OK;
}

u16 ConvertAudChanCmdFromStackToUms(const TPAAudChanCmd& tPA, TAudChanCmd& tUms)
{
	
	ConvertEpKeyFromStackToUms(tPA.m_tEpKey, tUms.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromStackToUms(tUms.m_atRtpAddr[wIndex], tPA.m_atRtpAddr[wIndex]);
	}
	ConvertConfNetAddrFromStackToUms(tUms.m_tMixRtpAddr, tPA.m_tMixRtpAddr);
	return TP_RET_OK;
}

u16 ConvertAudChanAckFromStackToUms(const TPAAudChanAck& tPA, TAudChanAck& tUms)
{
	
	ConvertEpKeyFromStackToUms(tPA.m_tEpKey, tUms.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromStackToUms(tUms.m_atBackRtcpAddr[wIndex], tPA.m_atBackRtcpAddr[wIndex]);
	}
	ConvertConfNetAddrFromStackToUms(tUms.m_tMixBackRtcpAddr, tPA.m_tMixBackRtcpAddr);
	return TP_RET_OK;
}

u16 ConvertVidChanCmdFromStackToUms( const TPAVidChanCmd& tPA, TVidChanCmd& tUms )
{
	ConvertEpKeyFromStackToUms(tPA.m_tEpKey, tUms.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromStackToUms(tUms.m_atDownBackRtcp[wIndex].m_tAddr, tPA.m_atDownBackRtcp[wIndex].m_tAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atDownBackRtcp[wIndex].m_tSmallAddrL, tPA.m_atDownBackRtcp[wIndex].m_tSmallAddrL);
		ConvertConfNetAddrFromStackToUms(tUms.m_atDownBackRtcp[wIndex].m_tSmallAddrR, tPA.m_atDownBackRtcp[wIndex].m_tSmallAddrR);
		ConvertConfNetAddrFromStackToUms(tUms.m_atUpRtp[wIndex].m_tAddr, tPA.m_atUpRtp[wIndex].m_tAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atUpRtp[wIndex].m_tSmallAddr, tPA.m_atUpRtp[wIndex].m_tSmallAddr);

		ConvertConfNetAddrFromStackToUms(tUms.m_atAudBackRtcp[wIndex], tPA.m_atAudBackRtcp[wIndex]);
	}
	return TP_RET_OK;	
}

u16 ConvertVidChanAckFromStackToUms( const TPAVidChanAck& tPA, TVidChanAck& tUms )
{
	ConvertEpKeyFromStackToUms(tPA.m_tEpKey, tUms.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromStackToUms(tUms.m_atDownRtp[wIndex].m_tAddr, tPA.m_atDownRtp[wIndex].m_tAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atDownRtp[wIndex].m_tSmallAddrL, tPA.m_atDownRtp[wIndex].m_tSmallAddrL);
		ConvertConfNetAddrFromStackToUms(tUms.m_atDownRtp[wIndex].m_tSmallAddrR, tPA.m_atDownRtp[wIndex].m_tSmallAddrR);
		ConvertConfNetAddrFromStackToUms(tUms.m_atUpBackRtcp[wIndex].m_tAddr, tPA.m_atUpBackRtcp[wIndex].m_tAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atUpBackRtcp[wIndex].m_tSmallAddr, tPA.m_atUpBackRtcp[wIndex].m_tSmallAddr);

		ConvertConfNetAddrFromStackToUms(tUms.m_atAudRtp[wIndex], tPA.m_atAudRtp[wIndex]);
	}
	return TP_RET_OK;	
}

u16 ConvertConfDualStreamFromStackToUms(TDualInfoTr& tUms, const TDualInfo& tPA)
{
// 	tUms.m_emPayload = CTpTypeAdpt::GetVideoFormat(tPA.m_emPayload);
// 	tUms.m_emReslution = CTpTypeAdpt::GetVideoResolution(tPA.m_emReslution);
// 	tUms.m_wFrameRate = tPA.m_wFrameRate;
// 	tUms.m_wBitRate = tPA.m_wBitRate;
 	tUms.m_nScreenNo = tPA.m_nScreenNo;
 	tUms.m_tKey.m_wEpID = tPA.m_nEpId;
// 	strncpy(tUms.m_tKey.m_tKey.m_szEpID, tPA.m_achCascade, TP_MAX_EPID_LEN);
 	
 	ConvertConfNetAddrFromStackToUms(tUms.m_tDualCap.m_tVid.m_tChanAddr.m_tRtpAddr, tPA.m_tVidRtp);
 	ConvertConfNetAddrFromStackToUms(tUms.m_tDualCap.m_tVid.m_tChanAddr.m_tRtcpAddr, tPA.m_tVidRtcp);
 	ConvertConfNetAddrFromStackToUms(tUms.m_tDualCap.m_tVid.m_tChanAddr.m_tBackRtcpAddr, tPA.m_tVidBackRtp);

	ConvertConfNetAddrFromStackToUms(tUms.m_tDualCap.m_tAud.m_tChanAddr.m_tRtpAddr, tPA.m_tAudRtp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tDualCap.m_tAud.m_tChanAddr.m_tRtcpAddr, tPA.m_tAudRtcp);
 	ConvertConfNetAddrFromStackToUms(tUms.m_tDualCap.m_tAud.m_tChanAddr.m_tBackRtcpAddr, tPA.m_tAudBackRtp);
	return TP_RET_OK;
}

void ConverEpKeyFromStackToUms(const TPAEpKey& tPA, TEpKey& tUms)
{
	tUms.m_wEpID = tPA.m_wEpID;
//	tUms.m_tKey.SetKey(tPA.m_tKey.m_szEpID);
}

u16 ConvertAddTvMonitorFromStackToUms(TTvMonitorCmdTr& tUms, const TPATvMonitorCmd& tPA)
{
//	strncpy(tUms.m_tKey.m_szEpID, tPA.m_achCascade, TP_MAX_EPID_LEN);
	tUms.m_wEpID = tPA.m_wEpID;
	tUms.m_wIndex = tPA.m_wIndex;
	tUms.m_wScreenNum = tPA.m_wScreenNum;
	ConvertConfNetAddrFromStackToUms(tUms.m_tVidAddr.m_tRtpAddr, tPA.m_tVidRtp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tVidAddr.m_tRtcpAddr, tPA.m_tVidRtcp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tVidAddr.m_tBackRtcpAddr, tPA.m_tVidBackRtp);
	
	ConvertConfNetAddrFromStackToUms(tUms.m_tAudAddr.m_tRtpAddr, tPA.m_tAudRtp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tAudAddr.m_tRtcpAddr, tPA.m_tAudRtcp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tAudAddr.m_tBackRtcpAddr, tPA.m_tAudBackRtp);
	return TP_RET_OK;
}

u16 ConvertAddTvMonitorIndFromStackToUms(TTvMonitorIndTr& tUms, const TPATvMonitorInd& tPA)
{
	tUms.m_bAccept = tPA.m_bAccept;
//	strncpy(tUms.m_tKey.m_szEpID, tPA.m_achCascade, TP_MAX_EPID_LEN);
	tUms.m_wEpID = tPA.m_wEpID;
	tUms.m_wIndex = tPA.m_wIndex;
	tUms.m_wScreenNum = tPA.m_wScreenNum;
	ConvertConfNetAddrFromStackToUms(tUms.m_tVidAddr.m_tRtpAddr, tPA.m_tVidRtp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tVidAddr.m_tRtcpAddr, tPA.m_tVidRtcp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tVidAddr.m_tBackRtcpAddr, tPA.m_tVidBackRtp);
	
	ConvertConfNetAddrFromStackToUms(tUms.m_tAudAddr.m_tRtpAddr, tPA.m_tAudRtp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tAudAddr.m_tRtcpAddr, tPA.m_tAudRtcp);
	ConvertConfNetAddrFromStackToUms(tUms.m_tAudAddr.m_tBackRtcpAddr, tPA.m_tAudBackRtp);
	return TP_RET_OK;
}

u16 ConvertViewCmdFromStackToUms(TViewCmdTr& tUms, const TPAViewCmd& tPA)
{
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[0].m_tRtpAddr, tPA.m_tLeftRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[0].m_tRtcpAddr, tPA.m_tLeftRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[0].m_tBackRtcpAddr, tPA.m_tLeftBackRtcpAddr);

// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[0].m_tRtpAddr, tPA.m_tLeftSmallRtpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[0].m_tRtcpAddr, tPA.m_tLeftSmallRtcpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[0].m_tBackRtcpAddr, tPA.m_tLeftSmallBackRtcpAddr);

	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[1].m_tRtpAddr, tPA.m_tRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[1].m_tRtcpAddr, tPA.m_tRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[1].m_tBackRtcpAddr, tPA.m_tBackRtcpAddr);
	
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[1].m_tRtpAddr, tPA.m_tSmallRtpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[1].m_tRtcpAddr, tPA.m_tSmallRtcpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[1].m_tBackRtcpAddr, tPA.m_tSmallBackRtcpAddr);

	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[2].m_tRtpAddr, tPA.m_tRightRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[2].m_tRtcpAddr, tPA.m_tRightRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[2].m_tBackRtcpAddr, tPA.m_tRightBackRtcpAddr);

// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[2].m_tRtpAddr, tPA.m_tRightSmallRtpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[2].m_tRtcpAddr, tPA.m_tRightSmallRtcpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[2].m_tBackRtcpAddr, tPA.m_tRightSmallBackRtcpAddr);
	
	//add B2新增
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		ConvertConfNetAddrFromStackToUms(tUms.m_atAudAddr[wIndex].m_tRtpAddr, tPA.m_atAudAddr[wIndex].m_tRtpAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atAudAddr[wIndex].m_tRtcpAddr, tPA.m_atAudAddr[wIndex].m_tRtcpAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atAudAddr[wIndex].m_tBackRtcpAddr, tPA.m_atAudAddr[wIndex].m_tBackRtcpAddr);
	}

	ConvertConfNetAddrFromStackToUms(tUms.m_tMixAddr.m_tRtpAddr, tPA.m_tMixAddr.m_tRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_tMixAddr.m_tRtcpAddr, tPA.m_tMixAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_tMixAddr.m_tBackRtcpAddr, tPA.m_tMixAddr.m_tBackRtcpAddr);
	//end
	tUms.m_wEpID = tPA.m_wEpID;
	tUms.m_wIndex = tPA.m_wChanID;

	tUms.m_abOpen[0] = tPA.m_bLeftOpen;
//	tUms.m_abSmallOpen[0] = tPA.m_bSmallLeftOpen;

	tUms.m_abOpen[1] = tPA.m_bMidOpen;
//	tUms.m_abSmallOpen[1] = tPA.m_bSmallMidOpen;
	
	tUms.m_abOpen[2] = tPA.m_bRightOpen;
//	tUms.m_abSmallOpen[2] = tPA.m_bSmallRightOpen;

	tUms.m_bViewSpeaker = tPA.m_bViewSpeaker;

	tUms.m_bNeedBas = tPA.m_bNeedBas;

	tUms.m_dwType = tPA.m_dwType;

	tUms.m_wSrcScreenIndex = tPA.m_wSrcScreenIndex;

	return TP_RET_OK;
}

u16 ConvertCascadeOpenChanCmdFromStackToUms(TCascadeOpenChanCmd& tUms, const TPACascadeOpenChanCmd& tPA)
{
	u16 wIndex = 0;
	tUms.m_wEpID = tPA.m_wEpID;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertMediaTransAddrFromStackToUms(tUms.m_atVidAddr[wIndex], tPA.m_atVidAddr[wIndex]);
		ConvertMediaTransAddrFromStackToUms(tUms.m_atAudAddr[wIndex], tPA.m_atAudAddr[wIndex]);
//		ConvertMediaTransAddrFromStackToUms(tUms.m_atSmallAddr[wIndex], tPA.m_atSmallAddr[wIndex]);

		tUms.m_abVidOpen[wIndex] = tPA.m_abVidOpen[wIndex];
//		tUms.m_abSmallOpen[wIndex] = tPA.m_abSmallOpen[wIndex];
		tUms.m_abAudOpen[wIndex] = tPA.m_abAudOpen[wIndex];
	}
	ConvertMediaTransAddrFromStackToUms(tUms.m_tMixAudAddr, tPA.m_tMixAudAddr);
	tUms.m_bMixAudOpen = tPA.m_bMixAudOpen;

// 	ConvertMediaTransAddrFromStackToUms(tUms.m_tSpeakerVmpVid, tPA.m_atSmallAddr[0]);
// 	tUms.m_bSpeakerVmpVid = tPA.m_abSmallOpen[0];
	ConvertMediaTransAddrFromStackToUms(tUms.m_tDisSingleVid, tPA.m_atSmallAddr[1]);
	tUms.m_bDisSingleVid = tPA.m_abSmallOpen[1];
	ConvertMediaTransAddrFromStackToUms(tUms.m_tDisSingleAud, tPA.m_atSmallAddr[2]);
	tUms.m_bDisSingleAud = tPA.m_abSmallOpen[2];
	return TP_RET_OK;
}

u16 ConvertCascadeOpenChanAckFromStackToUms(TCascadeOpenChanAck& tUms, const TPACascadeOpenChanAck& tPA)
{
	u16 wIndex = 0;
	tUms.m_wEpID = tPA.m_wEpID;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertMediaTransAddrFromStackToUms(tUms.m_atVidAddr[wIndex], tPA.m_atVidAddr[wIndex]);
		ConvertMediaTransAddrFromStackToUms(tUms.m_atAudAddr[wIndex], tPA.m_atAudAddr[wIndex]);
//		ConvertMediaTransAddrFromStackToUms(tUms.m_atSmallAddr[wIndex], tPA.m_atSmallAddr[wIndex]);
		
		tUms.m_abVidOpen[wIndex] = tPA.m_abVidOpen[wIndex];
//		tUms.m_abSmallOpen[wIndex] = tPA.m_abSmallOpen[wIndex];
		tUms.m_abAudOpen[wIndex] = tPA.m_abAudOpen[wIndex];
	}
	ConvertMediaTransAddrFromStackToUms(tUms.m_tMixAudAddr, tPA.m_tMixAudAddr);
	tUms.m_bMixAudOpen = tPA.m_bMixAudOpen;

// 	ConvertMediaTransAddrFromStackToUms(tUms.m_tSpeakerVmpVid, tPA.m_atSmallAddr[0]);
// 	tUms.m_bSpeakerVmpVid = tPA.m_abSmallOpen[0];
	ConvertMediaTransAddrFromStackToUms(tUms.m_tDisSingleVid, tPA.m_atSmallAddr[1]);
	tUms.m_bDisSingleVid = tPA.m_abSmallOpen[1];
	ConvertMediaTransAddrFromStackToUms(tUms.m_tDisSingleAud, tPA.m_atSmallAddr[2]);
	tUms.m_bDisSingleAud = tPA.m_abSmallOpen[2];
	return TP_RET_OK;
}

u16 ConvertCascadeOpenChanCmdFromUmsToStack(TPACascadeOpenChanCmd& tPA, const TCascadeOpenChanCmd& tUms)
{
	u16 wIndex = 0;
	tPA.m_wEpID = tUms.m_wEpID;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertMediaTransAddrFromUmsToStack(tPA.m_atVidAddr[wIndex], tUms.m_atVidAddr[wIndex]);
		ConvertMediaTransAddrFromUmsToStack(tPA.m_atAudAddr[wIndex], tUms.m_atAudAddr[wIndex]);
//		ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[wIndex], tUms.m_atSmallAddr[wIndex]);
		
		tPA.m_abVidOpen[wIndex] = tUms.m_abVidOpen[wIndex];
//		tPA.m_abSmallOpen[wIndex] = tUms.m_abSmallOpen[wIndex];
		tPA.m_abAudOpen[wIndex] = tUms.m_abAudOpen[wIndex];
	}
	ConvertMediaTransAddrFromUmsToStack(tPA.m_tMixAudAddr, tUms.m_tMixAudAddr);
	tPA.m_bMixAudOpen = tUms.m_bMixAudOpen;
// 	ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[0], tUms.m_tSpeakerVmpVid);
// 	tPA.m_abSmallOpen[0] = tUms.m_bSpeakerVmpVid;
	ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[1], tUms.m_tDisSingleVid);
	tPA.m_abSmallOpen[1] = tUms.m_bDisSingleVid;
	ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[2], tUms.m_tDisSingleAud);
	tPA.m_abSmallOpen[2] = tUms.m_bDisSingleAud;
	return TP_RET_OK;
}

u16 ConvertCascadeOpenChanAckFromUmsToStack(TPACascadeOpenChanAck& tPA, const TCascadeOpenChanAck& tUms)
{
	u16 wIndex = 0;
	tPA.m_wEpID = tUms.m_wEpID;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertMediaTransAddrFromUmsToStack(tPA.m_atVidAddr[wIndex], tUms.m_atVidAddr[wIndex]);
		ConvertMediaTransAddrFromUmsToStack(tPA.m_atAudAddr[wIndex], tUms.m_atAudAddr[wIndex]);
//		ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[wIndex], tUms.m_atSmallAddr[wIndex]);
		
		tPA.m_abVidOpen[wIndex] = tUms.m_abVidOpen[wIndex];
//		tPA.m_abSmallOpen[wIndex] = tUms.m_abSmallOpen[wIndex];
		tPA.m_abAudOpen[wIndex] = tUms.m_abAudOpen[wIndex];
	}
	ConvertMediaTransAddrFromUmsToStack(tPA.m_tMixAudAddr, tUms.m_tMixAudAddr);
	tPA.m_bMixAudOpen = tUms.m_bMixAudOpen;
// 	ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[0], tUms.m_tSpeakerVmpVid);
// 	tPA.m_abSmallOpen[0] = tUms.m_bSpeakerVmpVid;

	ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[1], tUms.m_tDisSingleVid);
	tPA.m_abSmallOpen[1] = tUms.m_bDisSingleVid;

	ConvertMediaTransAddrFromUmsToStack(tPA.m_atSmallAddr[2], tUms.m_tDisSingleAud);
	tPA.m_abSmallOpen[2] = tUms.m_bDisSingleAud;

	return TP_RET_OK;
}

u16 ConvertViewIndFromStackToUms(TViewAckTr& tUms, const TPAViewAck& tPA)
{	
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[0].m_tRtpAddr, tPA.m_tLeftRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[0].m_tRtcpAddr, tPA.m_tLeftRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[0].m_tBackRtcpAddr, tPA.m_tLeftBackRtcpAddr);
	
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[0].m_tRtpAddr, tPA.m_tLeftSmallRtpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[0].m_tRtcpAddr, tPA.m_tLeftSmallRtcpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[0].m_tBackRtcpAddr, tPA.m_tLeftSmallBackRtcpAddr);

	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[1].m_tRtpAddr, tPA.m_tRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[1].m_tRtcpAddr, tPA.m_tRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[1].m_tBackRtcpAddr, tPA.m_tBackRtcpAddr);
	
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[1].m_tRtpAddr, tPA.m_tSmallRtpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[1].m_tRtcpAddr, tPA.m_tSmallRtcpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[1].m_tBackRtcpAddr, tPA.m_tSmallBackRtcpAddr);

	
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[2].m_tRtpAddr, tPA.m_tRightRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[2].m_tRtcpAddr, tPA.m_tRightRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_atAddr[2].m_tBackRtcpAddr, tPA.m_tRightBackRtcpAddr);
	
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[2].m_tRtpAddr, tPA.m_tRightSmallRtpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[2].m_tRtcpAddr, tPA.m_tRightSmallRtcpAddr);
// 	ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[2].m_tBackRtcpAddr, tPA.m_tRightSmallBackRtcpAddr);
	
	//add B2新增
	for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		ConvertConfNetAddrFromStackToUms(tUms.m_atAudAddr[wIndex].m_tRtpAddr, tPA.m_atAudAddr[wIndex].m_tRtpAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atAudAddr[wIndex].m_tRtcpAddr, tPA.m_atAudAddr[wIndex].m_tRtcpAddr);
		ConvertConfNetAddrFromStackToUms(tUms.m_atAudAddr[wIndex].m_tBackRtcpAddr, tPA.m_atAudAddr[wIndex].m_tBackRtcpAddr);
	}
	ConvertConfNetAddrFromStackToUms(tUms.m_tMixAddr.m_tRtpAddr, tPA.m_tMixAddr.m_tRtpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_tMixAddr.m_tRtcpAddr, tPA.m_tMixAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromStackToUms(tUms.m_tMixAddr.m_tBackRtcpAddr, tPA.m_tMixAddr.m_tBackRtcpAddr);
	//end

	tUms.m_emRes = (EmTPViewResult)tPA.m_wReason;
	tUms.m_wIndex = tPA.m_wChanID;

	tUms.m_abOpen[0] = tPA.m_bLeftOpen;
//	tUms.m_abSmallOpen[0] = tPA.m_bSmallLeftOpen;

	tUms.m_abOpen[1] = tPA.m_bMidOpen;
//	tUms.m_abSmallOpen[1] = tPA.m_bSmallMidOpen;
	
	tUms.m_abOpen[2] = tPA.m_bRightOpen;
//	tUms.m_abSmallOpen[1] = tPA.m_bSmallRightOpen;
	return TP_RET_OK;
}

u16 ConvertConfAuxMixInfoFromStackToUms( const TPAConfAuxMixInfo& tPA, TConfAuxMixInfo& tUms )
{
	tUms.m_bVacOn = tPA.m_bVacOn;
	tUms.m_bStart = tPA.m_bStart;
	tUms.m_wConfID = tPA.m_wConfID;
//	tUms.m_atAuxMixList.m_wSpeakerIndex = tPA.m_atAuxMixList.m_wSpeakerIndex;
    tUms.m_emRet = (EmDiscussRspRet)tPA.m_dwRet;

	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex ++ )
	{
		tUms.m_atAuxMixList.m_awList[wIndex] = tPA.m_atAuxMixList.m_awList[wIndex];
	}
	return TP_RET_OK;
}

u16 ConvertConfEpIDFromStackToUms( const TPAConfEpID& tPA, TConfEpID& tUms )
{
	tUms.m_wConfID = tPA.m_wConfID;
	tUms.m_wEpID = tPA.m_wEpID;
	return TP_RET_OK;
}

u16 ConvertConfTurnInfoFromStackToUms( const TPAConfTurnInfo& tPA, TConfTurnInfo& tUms )
{
	tUms.m_wConfID = tPA.m_wConfID;
	tUms.m_atTurnList.m_wNum = tPA.m_tTurnList.m_wNum;
	tUms.m_atTurnList.m_wInterval = tPA.m_tTurnList.m_wInterval;
	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_TURNNUM; wIndex ++ )
	{
		tUms.m_atTurnList.m_awList[wIndex] = tPA.m_tTurnList.m_awList[wIndex];
	}
	return TP_RET_OK;	
}

u16 ConvertChairConfInfoFromStackToUms( const TPAChairConfInfo& tPA, TChairConfInfo& tUms )
{
	tUms.m_wConfID = tPA.m_wConfID;
	tUms.m_tBeginTime = tPA.m_tBeginTime;

	ConvertAliasFromStackToUms(tPA.m_tChairName, tUms.m_tChairName);
	ConvertAliasFromStackToUms(tPA.m_tConfName, tUms.m_tConfName);

	return TP_RET_OK;
}

u16 ConvertEmTpMixStatusFromStackToUms( const EmPATpMixStatus& tPA, EmTpMixStatus& tUms )
{
	switch(tPA)
	{
	case emPAAudMixIdle:
		{
			tUms = emAudMixIdle;
			break;
		}
// 	case emPAAudMixAssignChan_Fail:
// 		{
// 			tUms = emAudMixAssignChan_Fail;
// 			break;
// 		}
// 	case emPAAudMixAssignChan_Success:
// 		{
// 			tUms = emAudMixAssignChan_Success;
// 			break;
// 		}
// 	case emPAAudMixOpenChan_Fail:
// 		{
// 			tUms = emAudMixOpenChan_Fail;
// 			break;
// 		}
// 	case emPAAudMixOpenChan_Success:
// 		{
// 			tUms = emAudMixOpenChan_Success;
// 			break;
// 		}
// 	case emPAAudMixDisConnect:
// 		{
// 			tUms = emAudMixDisConnect;
// 			break;
// 		}
// 	case emPAAudOpenChan_Fail:
// 		{
// 			tUms = emAudOpenChan_Fail;
// 			break;
// 		}
	case emPAAudOpenChan_Success:
		{
			tUms = emAudOpenChan_Success;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertEmTpMixStatusFromStackToUms EmTpMixStatus :%d\n", tPA));
			return TP_RET_ERROR;
		}
	}
	
	return TP_RET_OK;
}

u16 ConvertAudMixStatFromStackToUms( const TPAAudMixStat& tPA, TAudMixStat& tUms )
{
	tUms.m_bIsStart = tPA.m_bIsStart;
	tUms.m_wConfID = tPA.m_wConfID;
	tUms.m_wEpID = tPA.m_wEpID;
	ConvertEmTpMixStatusFromStackToUms(tPA.m_emMixStatus, tUms.m_emMixStatus);
	return TP_RET_OK;
}

void CovertConfNetAddrFromStackToUms(const TPAIPAddress& tPA,  TTPTransAddr& tUms)
{
	tUms.m_dwIP = tPA.m_dwIP;
	tUms.m_wPort = tPA.m_wPort;

}
void ConvertConfNetAddrFromUmsToStack(TPAIPAddress& tPA, const TTPTransAddr& tUms)
{
	tPA.m_dwIP = tUms.m_dwIP;
	tPA.m_wPort = tUms.m_wPort;
}

u16 ConvertConfDualStreamFromUmsToStack(TDualInfo& tPA, const TDualInfoTr& tUms)
{
// 	tPA.m_emPayload = CTpTypeAdpt::GetVideoPT(tUms.m_emPayload);
// 	tPA.m_emReslution = CTpTypeAdpt::GetStackResolution(tUms.m_emReslution);
// 	tPA.m_wFrameRate = tUms.m_wFrameRate;
// 	tPA.m_wBitRate = tUms.m_wBitRate;
 	tPA.m_nScreenNo = tUms.m_nScreenNo;
 	tPA.m_nEpId = tUms.m_tKey.m_wEpID;
// 	strncpy(tPA.m_achCascade, tUms.m_tKey.m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
 
 	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidRtp, tUms.m_tDualCap.m_tVid.m_tChanAddr.m_tRtpAddr);
 	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidRtcp, tUms.m_tDualCap.m_tVid.m_tChanAddr.m_tRtcpAddr);
 	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidBackRtp, tUms.m_tDualCap.m_tVid.m_tChanAddr.m_tBackRtcpAddr);

	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudRtp, tUms.m_tDualCap.m_tAud.m_tChanAddr.m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudRtcp, tUms.m_tDualCap.m_tAud.m_tChanAddr.m_tRtcpAddr);
 	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudBackRtp, tUms.m_tDualCap.m_tAud.m_tChanAddr.m_tBackRtcpAddr);

	return TP_RET_OK;
}

u16 ConvertEpKeyFromUmsToStack( const TEpKey& tUms, TPAEpKey& tPA )
{
//	strncpy(tPA.m_tKey.m_szEpID, tUms.m_tKey.m_szEpID, TP_MAX_EPID_LEN);
	tPA.m_tKey.m_achEpID[TP_MAX_EPID_LEN] = '\0';

	tPA.m_wEpID = tUms.m_wEpID;

	return TP_RET_OK;
}

void ConverEpKeyFromUmsToStack(const TEpKey& tUms, TPAEpKey& tPA)
{
	tPA.m_wEpID = tUms.m_wEpID;
//	strncpy(tPA.m_tKey.m_szEpID, tUms.m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
}

u16 ConvertConfPollCmdFromUmsToStack(TPAPollCmd& tPA, const TPollCmdTr& tPollCmd)
{	
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atRtpAddr[wIndex], tPollCmd.m_tAddr[wIndex].m_tRtpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atRtcpAddr[wIndex], tPollCmd.m_tAddr[wIndex].m_tRtcpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atBackRtcpAddr[wIndex], tPollCmd.m_tAddr[wIndex].m_tBackRtcpAddr);
	}
	tPA.m_wBitrate = tPollCmd.m_wBitrate;
	tPA.m_wInterval = tPollCmd.m_wInterval;
	return 0;
}

u16 ConvertConfPollAckFromUmsToStack(TPAPollAck& tPA, const TPollAckTr& tPollAck)
{
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atRtpAddr[wIndex], tPollAck.m_tAddr[wIndex].m_tRtpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atRtcpAddr[wIndex], tPollAck.m_tAddr[wIndex].m_tRtcpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atBackRtcpAddr[wIndex], tPollAck.m_tAddr[wIndex].m_tBackRtcpAddr);
	}
	tPA.m_wReason = tPollAck.m_wReason;
	return TP_RET_OK;
}

u16 ConvertAudChanCmdFromUmsToStack(const TAudChanCmd& tUms, TPAAudChanCmd& tPA)
{
	
	ConvertEpKeyFromUmsToStack(tUms.m_tEpKey, tPA.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atRtpAddr[wIndex], tUms.m_atRtpAddr[wIndex]);
	}
	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixRtpAddr, tUms.m_tMixRtpAddr);
	return TP_RET_OK;
}

u16 ConvertAudChanAckFromUmsToStack(const TAudChanAck& tUms, TPAAudChanAck& tPA)
{
	tPA.m_wReason = tUms.m_wReason;
	ConvertEpKeyFromUmsToStack(tUms.m_tEpKey, tPA.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atBackRtcpAddr[wIndex], tUms.m_atBackRtcpAddr[wIndex]);
	}
	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixBackRtcpAddr, tUms.m_tMixBackRtcpAddr);
	return TP_RET_OK;
}

u16 ConvertVidChanCmdFromUmsToStack( const TVidChanCmd& tUms, TPAVidChanCmd& tPA )
{
	ConvertEpKeyFromUmsToStack(tUms.m_tEpKey, tPA.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atDownBackRtcp[wIndex].m_tAddr, tUms.m_atDownBackRtcp[wIndex].m_tAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atDownBackRtcp[wIndex].m_tSmallAddrL, tUms.m_atDownBackRtcp[wIndex].m_tSmallAddrL);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atDownBackRtcp[wIndex].m_tSmallAddrR, tUms.m_atDownBackRtcp[wIndex].m_tSmallAddrR);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atUpRtp[wIndex].m_tAddr, tUms.m_atUpRtp[wIndex].m_tAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atUpRtp[wIndex].m_tSmallAddr, tUms.m_atUpRtp[wIndex].m_tSmallAddr);

		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudBackRtcp[wIndex], tUms.m_atAudBackRtcp[wIndex]);
	}
	return TP_RET_OK;	
}

u16 ConvertVidChanAckFromUmsToStack( const TVidChanAck& tUms, TPAVidChanAck& tPA )
{
	ConvertEpKeyFromUmsToStack(tUms.m_tEpKey, tPA.m_tEpKey);
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atDownRtp[wIndex].m_tAddr, tUms.m_atDownRtp[wIndex].m_tAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atDownRtp[wIndex].m_tSmallAddrL, tUms.m_atDownRtp[wIndex].m_tSmallAddrL);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atDownRtp[wIndex].m_tSmallAddrR, tUms.m_atDownRtp[wIndex].m_tSmallAddrR);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atUpBackRtcp[wIndex].m_tAddr, tUms.m_atUpBackRtcp[wIndex].m_tAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atUpBackRtcp[wIndex].m_tSmallAddr, tUms.m_atUpBackRtcp[wIndex].m_tSmallAddr);

		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudRtp[wIndex], tUms.m_atAudRtp[wIndex]);
	}
	return TP_RET_OK;	
}

u16 ConvertConfAuxMixInfoFromUmsToStack( const TConfAuxMixInfo& tUms, TPAConfAuxMixInfo& tPA )
{
	tPA.m_bVacOn = tUms.m_bVacOn;
	tPA.m_bStart = tUms.m_bStart;
	tPA.m_wConfID = tUms.m_wConfID;
//	tPA.m_atAuxMixList.m_wSpeakerIndex = tUms.m_atAuxMixList.m_wSpeakerIndex;
    tPA.m_dwRet  =  tUms.m_emRet;

	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex ++ )
	{
		tPA.m_atAuxMixList.m_awList[wIndex] = tUms.m_atAuxMixList.m_awList[wIndex];
	}
	return TP_RET_OK;
}

u16 ConvertConfEpIDFromUmsToStack( const TConfEpID& tUms, TPAConfEpID& tPA )
{
	tPA.m_wConfID = tUms.m_wConfID;
	tPA.m_wEpID = tUms.m_wEpID;
	return TP_RET_OK;
}

u16 ConvertApplySpeakerRetFromUmsToStack( const EmTpApplySpeakerRet& tUms, EmPATpApplySpeakerRet& tPA )
{
	switch(tUms)
	{
	case TP_ApplySpeaker_Success:
		{
			tPA = emPA_ApplySpeaker_Success;
			break;
		}
	case TP_ApplySpeaker_ConfUnExist:
		{
			tPA = emPA_ApplySpeaker_ConfUnExist;
			break;
		}
	case TP_ApplySpeaker_EpIDError:
		{
			tPA = emPA_ApplySpeaker_EpIDError;
			break;
		}
	case TP_ApplySpeaker_EpStateError:
		{
			tPA = emPA_ApplySpeaker_EpStateError;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertApplySpeakerRetFromUmsToStack ApplySpeakerRet :%d\n", tUms));
			return TP_RET_ERROR;
		}
	}
	
	return TP_RET_OK;	
}
void ConvertCallTypeFromUmsToStack(const EmTpAliasType& emUms, EmPAAliasType& emPA)
{
	switch(emUms)
	{
	case tp_Alias_Unknow:
		{
			emPA = emPA_Alias_Unknow;
			break;
		}
	case tp_Alias_e164:
		{
			emPA = emPA_Alias_e164;
			break;
		}
	case tp_Alias_h323:
		{
			emPA = emPA_Alias_h323;
			break;
		}
	case tp_Alias_IP:
		{
			emPA = emPA_Alias_IP;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAliasFromUmsToStack Unknow Call type:%d\n", emUms));
			break;
		}
	}
}

void ConvertAliasFromUmsToStack(const TTPAlias& tUms, TPAAlias& tPA)
{
	switch(tUms.m_byType)
	{
	case tp_Alias_Unknow:
		{
			tPA.m_emType = emPA_Alias_Unknow;
			break;
		}
	case tp_Alias_e164:
		{
			tPA.m_emType = emPA_Alias_e164;
			break;
		}
	case tp_Alias_h323:
		{
			tPA.m_emType = emPA_Alias_h323;
			break;
		}
	case tp_Alias_IP:
		{
			tPA.m_emType = emPA_Alias_IP;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAliasFromUmsToStack Unknow alias type:%d\n", tUms.m_byType));
			break;
		}
	}
	strncpy(tPA.m_achAlias, tUms.m_abyAlias, PA_MAX_NAME_LEN);
}


u16 ConvertConfTurnInfoFromUmsToStack( const TConfTurnInfo& tUms, TPAConfTurnInfo& tPA )
{
	tPA.m_wConfID = tUms.m_wConfID;
	tPA.m_tTurnList.m_wNum = tUms.m_atTurnList.m_wNum;
	tPA.m_tTurnList.m_wInterval = tUms.m_atTurnList.m_wInterval;
	for ( u16 wIndex = 0; wIndex < TP_CONF_MAX_TURNNUM; wIndex ++ )
	{
		tPA.m_tTurnList.m_awList[wIndex] = tUms.m_atTurnList.m_awList[wIndex];
	}
	return TP_RET_OK;
}

u16 ConvertChairConfInfoFromUmsToStack( const TChairConfInfo& tUms, TPAChairConfInfo& tPA )
{
	tPA.m_wConfID = tUms.m_wConfID;
	tPA.m_tBeginTime = tUms.m_tBeginTime;
	
	ConvertAliasFromUmsToStack(tUms.m_tChairName, tPA.m_tChairName);
	ConvertAliasFromUmsToStack(tUms.m_tConfName, tPA.m_tConfName);

	return TP_RET_OK;
}

u16 ConvertAudMixStatFromUmsToStack( const TAudMixStat& tUms, TPAAudMixStat& tPA )
{
	tPA.m_bIsStart = tUms.m_bIsStart;
	tPA.m_wConfID = tUms.m_wConfID;
	tPA.m_wEpID = tUms.m_wEpID;
	ConvertEmTpMixStatusFromUmsToStack(tUms.m_emMixStatus, tPA.m_emMixStatus);
	return TP_RET_OK;
}

u16 ConvertNodeCallUpdateFromUmsToStack(TPAConfNodeUpdateTrList& tPA, const TConfNodeCallUpdateTrList& tUms)
{
	u16 wNum = min(tUms.m_wNum, PA_REFRESH_LIST_THREE);
	tPA.m_wNum = wNum;
	s8* pzAliasUTF8 = NULL;
	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
		ConvertKeyPathFromUmsToStack(tUms.m_atList[wIndex].m_tID, tPA.m_atList[wIndex].m_tID);
		tPA.m_atList[wIndex].m_wEpID = tUms.m_atList[wIndex].m_wEpID;
		
		tPA.m_atList[wIndex].m_dwEpType = tUms.m_atList[wIndex].m_emEpType;

		tPA.m_atList[wIndex].m_dwCallState = tUms.m_atList[wIndex].m_emCallState;
		tPA.m_atList[wIndex].m_dwCallReason = tUms.m_atList[wIndex].m_emCallReason;
		ConvertVendorFromUmsToStack(tUms.m_atList[wIndex].m_emVendorID, tPA.m_atList[wIndex].m_emVendorID);

		ConvertAliasFromUmsToStack(tUms.m_atList[wIndex].m_tCalledAddr.m_tAlias, tPA.m_atList[wIndex].m_tCalledAddr); 

		gb2312_to_utf8((s8 *)tPA.m_atList[wIndex].m_tCalledAddr.m_achAlias, &pzAliasUTF8);
		strncpy((s8 *)tPA.m_atList[wIndex].m_tCalledAddr.m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;

		ConvertAliasFromUmsToStack(tUms.m_atList[wIndex].m_tConfName, tPA.m_atList[wIndex].m_tConfName);

		gb2312_to_utf8((s8 *)tPA.m_atList[wIndex].m_tConfName.m_achAlias, &pzAliasUTF8);
		strncpy((s8 *)tPA.m_atList[wIndex].m_tConfName.m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
		
		tPA.m_atList[wIndex].m_wLevel = tUms.m_atList[wIndex].m_emLevel;
		tPA.m_atList[wIndex].m_dwRcvAlignType = tUms.m_atList[wIndex].m_enRcvAlignType;

		tPA.m_atList[wIndex].m_bMute = tUms.m_atList[wIndex].m_bMute;
		tPA.m_atList[wIndex].m_bQuiet = tUms.m_atList[wIndex].m_bQuiet;
		tPA.m_atList[wIndex].m_wSpearkIndex = tUms.m_atList[wIndex].m_wSpearkIndex;
		tPA.m_atList[wIndex].m_wDualIndex = tUms.m_atList[wIndex].m_wDualIndex;
	}
	return TP_RET_OK;
}


u16 ConvertNodeChanUpdateFromUmsToStack(TPAConfNodeUpdateB2NEWTrList& tPA, const TConfNodeChanUpdateTrList& tUms)
{
	u16 wNum = min(tUms.m_wNum, PA_REFRESH_LIST_THREE);
	tPA.m_wNum = wNum;

	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
//		ConvertEpKeyPathFromUmsToStack(tUms.m_atList[wIndex].tID.m_tKey, tPA.m_atList[wIndex].tID.m_tKey);
		tPA.m_atList[wIndex].m_tID.m_wEpID = tUms.m_atList[wIndex].tID.m_wEpID;
		tPA.m_atList[wIndex].m_wEpID = tUms.m_atList[wIndex].wEpID;
		tPA.m_atList[wIndex].m_bChanOpen = tUms.m_atList[wIndex].bChanOpen;
		tPA.m_atList[wIndex].m_bInPoll = tUms.m_atList[wIndex].bInPoll;

		tPA.m_atList[wIndex].m_wVidRcv = tUms.m_atList[wIndex].wVidRcv;
		tPA.m_atList[wIndex].m_wVidSnd = tUms.m_atList[wIndex].wVidSnd;
		tPA.m_atList[wIndex].m_wAudRcv = tUms.m_atList[wIndex].wAudRcv;
		tPA.m_atList[wIndex].m_wAudSnd = tUms.m_atList[wIndex].wAudSnd;

		ConvertVidInfoFromUmsToStack(tPA.m_atList[wIndex].m_tVidRcv, tUms.m_atList[wIndex].tVidRcv);
		ConvertVidInfoFromUmsToStack(tPA.m_atList[wIndex].m_tVidSnd, tUms.m_atList[wIndex].tVidSnd);
		ConvertVidInfoFromUmsToStack(tPA.m_atList[wIndex].m_tDualVidRcv, tUms.m_atList[wIndex].tDualVidRcv);
		ConvertVidInfoFromUmsToStack(tPA.m_atList[wIndex].m_tDualVidSnd, tUms.m_atList[wIndex].tDualVidSnd);

		ConvertAudInfoFromUmsToStack(tPA.m_atList[wIndex].m_tAudRcv, tUms.m_atList[wIndex].tAudRcv);
		ConvertAudInfoFromUmsToStack(tPA.m_atList[wIndex].m_tAudSnd, tUms.m_atList[wIndex].tAudSnd);
		ConvertAudInfoFromUmsToStack(tPA.m_atList[wIndex].m_tDualAudRcv, tUms.m_atList[wIndex].tDualAudRcv);
		ConvertAudInfoFromUmsToStack(tPA.m_atList[wIndex].m_tDualAudSnd, tUms.m_atList[wIndex].tDualAudSnd);

		tPA.m_atList[wIndex].m_bSmallOpenEnc = tUms.m_atList[wIndex].bSmallOpenEnc;
		tPA.m_atList[wIndex].m_bSmallOpenDec = tUms.m_atList[wIndex].bSmallOpenDec;
		
		memcpy(tPA.m_atList[wIndex].m_awPd, tUms.m_atList[wIndex].awPd, sizeof(tPA.m_atList[wIndex].m_awPd));
	}
	return TP_RET_OK;
}

void ConvertVidInfoFromStackToUms(const TPAUmsVidFormat& tPa, TUmsVidFormat& tUms)
{
	tUms.m_wBitrate = tPa.m_wBitrate;
	tUms.m_wFrameRate = tPa.m_wFrameRate;
	ConvertVidFormatFromStackToUms(tUms.m_emFormat, tPa.m_emFormat);
	ConvertVidResFromStackToUms(tUms.m_emRes, tPa.m_emRes);
	ConvertVidProFromStackToUms(tUms.m_emQualityLvl, tPa.m_emProfile);
}

void ConvertVidInfoFromUmsToStack(TPAUmsVidFormat& tPa, const TUmsVidFormat& tUms)
{
	tPa.m_wBitrate = tUms.m_wBitrate;
	tPa.m_wFrameRate = tUms.m_wFrameRate;
	ConvertVidFormatFromUmsToStack(tPa.m_emFormat, tUms.m_emFormat);
	ConvertVidResFromUmsToStack(tPa.m_emRes, tUms.m_emRes);
	ConvertVidProFromUmsToStack(tPa.m_emProfile, tUms.m_emQualityLvl);
}

void ConvertAudInfoFromStackToUms(const TPAUmsAudFormat& tPa, TUmsAudFormat& tUms)
{
	tUms.m_byReserve1 = tPa.m_byReserve1;
	tUms.m_byReserve2 = tPa.m_byReserve2;

	ConvertAudFormatFromStackToUms(tUms.m_emFormat, tPa.m_emFormat);
	ConvertChnlCfgFromStackToUms(tUms.m_emChnlCfg, tPa.m_emPAChnlCfg);
	ConvertSampleFreqFromStackToUms(tUms.m_emSampleFreq, tPa.m_emPASampleFreq);
}

void ConvertAudInfoFromUmsToStack(TPAUmsAudFormat& tPa, const TUmsAudFormat& tUms)
{
	tPa.m_byReserve1 = tUms.m_byReserve1;
	tPa.m_byReserve2 = tUms.m_byReserve2;
	
	ConvertAudFormatFromUmsToStack(tPa.m_emFormat, tUms.m_emFormat);
	ConvertChnlCfgFromUmsToStack(tPa.m_emPAChnlCfg, tUms.m_emChnlCfg);
	ConvertSampleFreqFromUmsToStack(tPa.m_emPASampleFreq, tUms.m_emSampleFreq);
}

void ConvertSampleFreqFromStackToUms(EmTPAACSampleFreq& emTpSampleFreq, const EmPAAACSampleFreq& emPaSampleFreq)
{
	switch (emPaSampleFreq)
	{
	case emPAFs96000:
		{
			emTpSampleFreq = emTPFs96000;
		}
		break;
		
	case emPAFs88200:
		{
			emTpSampleFreq = emTPFs88200;
		}
		break;
		
	case emPAFs64000:
		{
			emTpSampleFreq = emTPFs64000;
		}
		break;
		
	case emPAFs48000:
		{
			emTpSampleFreq = emTPFs48000;
		}
		break;
		
	case emPAFs44100:
		{
			emTpSampleFreq = emTPFs44100;
		}
		break;
		
	case emPAFs32000:
		{
			emTpSampleFreq = emTPFs32000;
		}
		break;
		
	case emPAFs24000:
		{
			emTpSampleFreq = emTPFs24000;
		}
		break;
		
	case emPAFs22050:
		{
			emTpSampleFreq = emTPFs22050;
		}
		break;
		
	case emPAFs16000:
		{
			emTpSampleFreq = emTPFs16000;
		}
		break;
		
	case emPAFs12000:
		{
			emTpSampleFreq = emTPFs12000;
		}
		break;
		
	case emPAFs11025:
		{
			emTpSampleFreq = emTPFs11025;
		}
		break;
		
    case emPAFs8000:
		{
			emTpSampleFreq = emTPFs8000;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertSampleFreqFromStackToUms PaSampleFreq:%d\n", emPaSampleFreq));
		}
	}
}

void ConvertSampleFreqFromUmsToStack(EmPAAACSampleFreq& emPaSampleFreq, const EmTPAACSampleFreq& emTpSampleFreq)
{
	switch (emTpSampleFreq)
	{
	case emTPFs96000:
		{
			emPaSampleFreq = emPAFs96000;
		}
		break;

	case emTPFs88200:
		{
			emPaSampleFreq = emPAFs88200;
		}
		break;

	case emTPFs64000:
		{
			emPaSampleFreq = emPAFs64000;
		}
		break;

	case emTPFs48000:
		{
			emPaSampleFreq = emPAFs48000;
		}
		break;

	case emTPFs44100:
		{
			emPaSampleFreq = emPAFs44100;
		}
		break;

	case emTPFs32000:
		{
			emPaSampleFreq = emPAFs32000;
		}
		break;

	case emTPFs24000:
		{
			emPaSampleFreq = emPAFs24000;
		}
		break;

	case emTPFs22050:
		{
			emPaSampleFreq = emPAFs22050;
		}
		break;

	case emTPFs16000:
		{
			emPaSampleFreq = emPAFs16000;
		}
		break;

	case emTPFs12000:
		{
			emPaSampleFreq = emPAFs12000;
		}
		break;

	case emTPFs11025:
		{
			emPaSampleFreq = emPAFs11025;
		}
		break;

    case emTPFs8000:
		{
			emPaSampleFreq = emPAFs8000;
		}
		break;

	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertSampleFreqFromUmsToStack TpSampleFreq:%d\n", emTpSampleFreq));
		}
	}
}

void ConvertChnlCfgFromStackToUms(EmTPAACChnlCfg& emTpChnlCfg, const EmPAAACChnlCfg& emPaChnlCfg)
{
	switch (emPaChnlCfg)
	{
	case emPAChnlCust:
		{
			emTpChnlCfg = emTPChnlCust;
		}
		break;
		
	case emPAChnl1:
		{
			emTpChnlCfg = emTPChnl1;
		}
		break;
		
	case emPAChnl2:
		{
			emTpChnlCfg = emTPChnl2;
		}
		break;
		
	case emPAChnl3:
		{
			emTpChnlCfg = emTPChnl3;
		}
		break;
		
	case emPAChnl4:
		{
			emTpChnlCfg = emTPChnl4;
		}
		break;
		
	case emPAChnl5:
		{
			emTpChnlCfg = emTPChnl5;
		}
		break;
		
	case emPAChnl5dot1:
		{
			emTpChnlCfg = emTPChnl5dot1;
		}
		break;
		
    case emPAChnl7dot1:
		{
			emTpChnlCfg = emTPChnl7dot1;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertChnlCfgFromStackToUms PaChnlCfg:%d\n", emPaChnlCfg));
		}
	}
}

void ConvertChnlCfgFromUmsToStack(EmPAAACChnlCfg& emPaChnlCfg, const EmTPAACChnlCfg& emTpChnlCfg)
{
	switch (emTpChnlCfg)
	{
	case emTPChnlCust:
		{
			emPaChnlCfg = emPAChnlCust;
		}
		break;

	case emTPChnl1:
		{
			emPaChnlCfg = emPAChnl1;
		}
		break;

	case emTPChnl2:
		{
			emPaChnlCfg = emPAChnl2;
		}
		break;

	case emTPChnl3:
		{
			emPaChnlCfg = emPAChnl3;
		}
		break;

	case emTPChnl4:
		{
			emPaChnlCfg = emPAChnl4;
		}
		break;

	case emTPChnl5:
		{
			emPaChnlCfg = emPAChnl5;
		}
		break;

	case emTPChnl5dot1:
		{
			emPaChnlCfg = emPAChnl5dot1;
		}
		break;

    case emTPChnl7dot1:
		{
			emPaChnlCfg = emPAChnl7dot1;
		}
		break;

	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertChnlCfgFromUmsToStack TpChnlCfg:%d\n", emTpChnlCfg));
		}
	}
}

void ConvertAudFormatFromStackToUms(EmTpAudioFormat& emTpFormat, const EmPAAudioFormat& emPaFormat)
{
	switch (emPaFormat)
	{
	case emPAAG711a:
		{
			emTpFormat = emTPAG711a;
		}
		break;
		
	case emPAAG711u:
		{
			emTpFormat = emTPAG711u;
		}
		break;
		
	case emPAAG722:
		{
			emTpFormat = emTPAG722;
		}
		break;
		
	case emPAAG7231:
		{
			emTpFormat = emTPAG7231;
		}
		break;
		
	case emPAAG728:
		{
			emTpFormat = emTPAG728;
		}
		break;
		
	case emPAAG729:
		{
			emTpFormat = emTPAG729;
		}
		break;
		
	case emPAAMP3:
		{
			emTpFormat = emTPAMP3;
		}
		break;
		
	case emPAAG721:
		{
			emTpFormat = emTPAG721;
		}
		break;
		
	case emPAAG7221:
		{
			emTpFormat = emTPAG7221;
		}
		break;
		
	case emPAAG719:
		{
			emTpFormat = emTPAG719;
		}
		break;
		
	case emPAAMpegAACLC:
		{
			emTpFormat = emTPAMpegAACLC;
		}
		break;
		
	case emPAAMpegAACLD:
		{
			emTpFormat = emTPAMpegAACLD;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAudFormatFromStackToUms AudPaFormat:%d\n", emPaFormat));
		}
	}
}

void ConvertAudFormatFromStackToUms(const EmModuleAudioFormat& emPaFormat, EmTpAudioFormat& emTpFormat)
{
	switch (emPaFormat)
	{
	case emModuleAG711a:
		{
			emTpFormat = emTPAG711a;
		}
		break;
		
	case emModuleAG711u:
		{
			emTpFormat = emTPAG711u;
		}
		break;
		
	case emModuleAG722:
		{
			emTpFormat = emTPAG722;
		}
		break;
		
	case emModuleAG7231:
		{
			emTpFormat = emTPAG7231;
		}
		break;
		
	case emModuleAG728:
		{
			emTpFormat = emTPAG728;
		}
		break;
		
	case emModuleAG729:
		{
			emTpFormat = emTPAG729;
		}
		break;
		
	case emModuleAMP3:
		{
			emTpFormat = emTPAMP3;
		}
		break;
		
	case emModuleAG721:
		{
			emTpFormat = emTPAG721;
		}
		break;
		
	case emModuleAG7221:
		{
			emTpFormat = emTPAG7221;
		}
		break;
		
	case emModuleAG719:
		{
			emTpFormat = emTPAG719;
		}
		break;
		
	case emModuleAMpegAACLC:
		{
			emTpFormat = emTPAMpegAACLC;
		}
		break;
		
	case emModuleAMpegAACLD:
		{
			emTpFormat = emTPAMpegAACLD;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAudFormatFromStackToUms AudModuleFormat:%d\n", emPaFormat));
		}
	}
}

// void ConvertAudFormatFromUmsToStack_MDL(EmModuleAudioFormat& emPaFormat, const EmTpAudioFormat& emTpFormat)
// {
// 	switch (emTpFormat)
// 	{
// 	case emTPAG711a:
// 		{
// 			emPaFormat = emModuleAG711a;
// 		}
// 		break;
// 		
// 	case emTPAG711u:
// 		{
// 			emPaFormat = emModuleAG711u;
// 		}
// 		break;
// 		
// 	case emTPAG722:
// 		{
// 			emPaFormat = emModuleAG722;
// 		}
// 		break;
// 		
// 	case emTPAG7231:
// 		{
// 			emPaFormat = emModuleAG7231;
// 		}
// 		break;
// 		
// 	case emTPAG728:
// 		{
// 			emPaFormat = emModuleAG728;
// 		}
// 		break;
// 		
// 	case emTPAG729:
// 		{
// 			emPaFormat = emModuleAG729;
// 		}
// 		break;
// 		
// 	case emTPAMP3:
// 		{
// 			emPaFormat = emModuleAMP3;
// 		}
// 		break;
// 		
// 	case emTPAG721:
// 		{
// 			emPaFormat = emModuleAG721;
// 		}
// 		break;
// 		
// 	case emTPAG7221:
// 		{
// 			emPaFormat = emModuleAG7221;
// 		}
// 		break;
// 		
// 	case emTPAG719:
// 		{
// 			emPaFormat = emModuleAG719;
// 		}
// 		break;
// 		
// 	case emTPAMpegAACLC:
// 		{
// 			emPaFormat = emModuleAMpegAACLC;
// 		}
// 		break;
// 		
// 	case emTPAMpegAACLD:
// 		{
// 			emPaFormat = emModuleAMpegAACLD;
// 		}
// 		break;
// 		
// 	default:
// 		{
// 			MdlError(Ums_Mdl_Call, ("ConvertAudFormatFromUmsToStack EmModuleAudioFormat AudTpFormat:%d\n", emTpFormat));
// 		}
// 	}
// }


void ConvertAudFormatFromUmsToStack(EmPAAudioFormat& emPaFormat, const EmTpAudioFormat& emTpFormat)
{
	switch (emTpFormat)
	{
	case emTPAG711a:
		{
			emPaFormat = emPAAG711a;
		}
		break;

	case emTPAG711u:
		{
			emPaFormat = emPAAG711u;
		}
		break;

	case emTPAG722:
		{
			emPaFormat = emPAAG722;
		}
		break;

	case emTPAG7231:
		{
			emPaFormat = emPAAG7231;
		}
		break;

	case emTPAG728:
		{
			emPaFormat = emPAAG728;
		}
		break;

	case emTPAG729:
		{
			emPaFormat = emPAAG729;
		}
		break;

	case emTPAMP3:
		{
			emPaFormat = emPAAMP3;
		}
		break;

	case emTPAG721:
		{
			emPaFormat = emPAAG721;
		}
		break;

	case emTPAG7221:
		{
			emPaFormat = emPAAG7221;
		}
		break;

	case emTPAG719:
		{
			emPaFormat = emPAAG719;
		}
		break;

	case emTPAMpegAACLC:
		{
			emPaFormat = emPAAMpegAACLC;
		}
		break;

	case emTPAMpegAACLD:
		{
			emPaFormat = emPAAMpegAACLD;
		}
		break;
	
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAudFormatFromUmsToStack AudTpFormat:%d\n", emTpFormat));
		}
	}
}

void ConvertVidResFromStackToUms(EmTpVideoResolution& emTpRes, const EmPAVideoResolution emPaRes)
{
	switch (emPaRes)
	{
	case emPAVResolutionAuto:
		{
			emTpRes = emTPVResolutionAuto;
		}
		break;

	case emPAVSQCIF:
		{
			emTpRes = emTPVSQCIF;
		}
		break;

	case emPAVQCIF:
		{
			emTpRes = emTPVQCIF;
		}
		break;

	case emPAVCIF:
		{
			emTpRes = emTPVCIF;
		}
		break;

	case emPAV2CIF:
		{
			emTpRes = emTPV2CIF;
		}
		break;

	case emPAV4CIF:
		{
			emTpRes = emTPV4CIF;
		}
		break;

	case emPAV16CIF:
		{
			emTpRes = emTPV16CIF;
		}
		break;
			
	case emPAVHD480i720x480:
		{
			emTpRes = emTPVHD480i720x480;
		}
		break;

	case emPAVHD480p720x480:
		{
			emTpRes = emTPVHD480p720x480;
		}
		break;

	case emPAVHD576i720x576:
		{
			emTpRes = emTPVHD576i720x576;
		}
		break;

	case emPAVHD576p720x576:
		{
			emTpRes = emTPVHD576p720x576;
		}
		break;
			
	case emPAVHD720p1280x720:
		{
			emTpRes = emTPVHD720p1280x720;
		}
		break;

	case emPAVHD1080i1920x1080:
		{
			emTpRes = emTPVHD1080i1920x1080;
		}
		break;

	case emPAVHD1080p1920x1080:
		{
			emTpRes = emTPVHD1080p1920x1080;
		}
		break;
			
	case emPAVGA352x240:
		{
			emTpRes = emTPVGA352x240;
		}
		break;

	case emPAVGA704x480:
		{
			emTpRes = emTPVGA704x480;
		}
		break;

	case emPAVGA640x480:
		{
			emTpRes = emTPVGA640x480;
		}
		break;

	case emPAVGA800x600:
		{
			emTpRes = emTPVGA800x600;
		}
		break;

	case emPAVGA1024x768:
		{
			emTpRes = emTPVGA1024x768;
		}
		break;

	case emPAVGA1280x768:
		{
			emTpRes = emTPVGA1280x768;
		}
		break;

	case emPAVGA1280x800:
		{
			emTpRes = emTPVGA1280x800;
		}
		break;

	case emPAVGA1366x768:
		{
			emTpRes = emTPVGA1366x768;
		}
		break;

	case emPAVGA1280x854:
		{
			emTpRes = emTPVGA1280x854;
		}
		break;

	case emPAVGA1440x900:
		{
			emTpRes = emTPVGA1440x900;
		}
		break;

	case emPAVGA1280x1024:
		{
			emTpRes = emTPVGA1280x1024;
		}
		break;

	case emPAVGA1680x1050:
		{
			emTpRes = emTPVGA1680x1050;
		}
		break;

	case emPAVGA1600x1200:
		{
			emTpRes = emTPVGA1600x1200;
		}
		break;

	case emPAVGA1920x1200:
		{
			emTpRes = emTPVGA1920x1200;
		}
		break;
			
	case emPAVSQCIF112x96:
		{
			emTpRes = emTPVSQCIF112x96;
		}
		break;

	case emPAVSQCIF96x80:
		{
			emTpRes = emTPVSQCIF96x80;
		}
		break;

	case emPAV320x192:
		{
			emTpRes = emTPV320x192;
		}
		break;

	case emPAV432x240:
		{
			emTpRes = emTPV432x240;
		}
		break;

	case emPAV480x272:
		{
			emTpRes = emTPV480x272;
		}
		break;

	case emPAV640x368:
		{
			emTpRes = emTPV640x368;
		}
		break;

	case emPAV864x480:
		{
			emTpRes = emTPV864x480;
		}
		break;

	case emPAV960x544:
		{
			emTpRes = emTPV960x544;
		}
		break;

	case emPAV1440x816:
		{
			emTpRes = emTPV1440x816;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVidResFromStackToUms TpRes:%d\n", emPaRes));
		}
	}
}

void ConvertVidResFromUmsToStack(EmPAVideoResolution& emPaRes, const EmTpVideoResolution& emTpRes)
{		
	switch (emTpRes)
	{
	case emTPVResolutionAuto:
		{
			emPaRes = emPAVResolutionAuto;
		}
		break;

	case emTPVSQCIF:
		{
			emPaRes = emPAVSQCIF;
		}
		break;

	case emTPVQCIF:
		{
			emPaRes = emPAVQCIF;
		}
		break;

	case emTPVCIF:
		{
			emPaRes = emPAVCIF;
		}
		break;

	case emTPV2CIF:
		{
			emPaRes = emPAV2CIF;
		}
		break;

	case emTPV4CIF:
		{
			emPaRes = emPAV4CIF;
		}
		break;

	case emTPV16CIF:
		{
			emPaRes = emPAV16CIF;
		}
		break;
			
	case emTPVHD480i720x480:
		{
			emPaRes = emPAVHD480i720x480;
		}
		break;

	case emTPVHD480p720x480:
		{
			emPaRes = emPAVHD480p720x480;
		}
		break;

	case emTPVHD576i720x576:
		{
			emPaRes = emPAVHD576i720x576;
		}
		break;

	case emTPVHD576p720x576:
		{
			emPaRes = emPAVHD576p720x576;
		}
		break;
			
	case emTPVHD720p1280x720:
		{
			emPaRes = emPAVHD720p1280x720;
		}
		break;

	case emTPVHD1080i1920x1080:
		{
			emPaRes = emPAVHD1080i1920x1080;
		}
		break;

	case emTPVHD1080p1920x1080:
		{
			emPaRes = emPAVHD1080p1920x1080;
		}
		break;
			
	case emTPVGA352x240:
		{
			emPaRes = emPAVGA352x240;
		}
		break;

	case emTPVGA704x480:
		{
			emPaRes = emPAVGA704x480;
		}
		break;

	case emTPVGA640x480:
		{
			emPaRes = emPAVGA640x480;
		}
		break;

	case emTPVGA800x600:
		{
			emPaRes = emPAVGA800x600;
		}
		break;

	case emTPVGA1024x768:
		{
			emPaRes = emPAVGA1024x768;
		}
		break;

	case emTPVGA1280x768:
		{
			emPaRes = emPAVGA1280x768;
		}
		break;

	case emTPVGA1280x800:
		{
			emPaRes = emPAVGA1280x800;
		}
		break;

	case emTPVGA1366x768:
		{
			emPaRes = emPAVGA1366x768;
		}
		break;

	case emTPVGA1280x854:
		{
			emPaRes = emPAVGA1280x854;
		}
		break;

	case emTPVGA1440x900:
		{
			emPaRes = emPAVGA1440x900;
		}
		break;

	case emTPVGA1280x1024:
		{
			emPaRes = emPAVGA1280x1024;
		}
		break;

	case emTPVGA1680x1050:
		{
			emPaRes = emPAVGA1680x1050;
		}
		break;

	case emTPVGA1600x1200:
		{
			emPaRes = emPAVGA1600x1200;
		}
		break;

	case emTPVGA1920x1200:
		{
			emPaRes = emPAVGA1920x1200;
		}
		break;
			
	case emTPVSQCIF112x96:
		{
			emPaRes = emPAVSQCIF112x96;
		}
		break;

	case emTPVSQCIF96x80:
		{
			emPaRes = emPAVSQCIF96x80;
		}
		break;

	case emTPV320x192:
		{
			emPaRes = emPAV320x192;
		}
		break;

	case emTPV432x240:
		{
			emPaRes = emPAV432x240;
		}
		break;

	case emTPV480x272:
		{
			emPaRes = emPAV480x272;
		}
		break;

	case emTPV640x368:
		{
			emPaRes = emPAV640x368;
		}
		break;

	case emTPV864x480:
		{
			emPaRes = emPAV864x480;
		}
		break;

	case emTPV960x544:
		{
			emPaRes = emPAV960x544;
		}
		break;

	case emTPV1440x816:
		{
			emPaRes = emPAV1440x816;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVidResFromUmsToStack TpRes:%d\n", emTpRes));
		}
	}
}

void ConvertVidFormatFromUmsToStack(EmModuleVideoFormat& emPaFormat, const EmTpVideoFormat& emTpFormat)
{
	switch(emTpFormat)
	{
	case emTPVH261:		
		{
			emPaFormat = emModuleVH261;
		}
		break;
		
	case emTPVH262:
		{
			emPaFormat = emModuleVH262;
		}
		break;
		
	case emTPVH263:
		{
			emPaFormat = emModuleVH263;
		}
		break;
		
	case emTPVH263plus:
		{
			emPaFormat = emModuleVH263plus;
		}
		break;
		
	case emTPVH264:
		{
			emPaFormat = emModuleVH264;
		}
		break;
		
	case emTPVMPEG4:
		{
			emPaFormat = emModuleVMPEG4;
		}
		break;
		
	default:	
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVidFormatFromUmsToStack EmModuleVideoFormat VideoFormat:%d\n", emTpFormat));
		}
	}
}
void ConvertVidFormatFromUmsToStack(EmPAVideoFormat& emPaFormat, const EmTpVideoFormat& emTpFormat)
{
	switch(emTpFormat)
	{
	case emTPVH261:		
		{
			emPaFormat = emPAVH261;
		}
		break;

	case emTPVH262:
		{
			emPaFormat = emPAVH262;
		}
		break;

	case emTPVH263:
		{
			emPaFormat = emPAVH263;
		}
		break;

	case emTPVH263plus:
		{
			emPaFormat = emPAVH263plus;
		}
		break;

	case emTPVH264:
		{
			emPaFormat = emPAVH264;
		}
		break;

	case emTPVMPEG4:
		{
			emPaFormat = emPAVMPEG4;
		}
		break;

	default:	
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVidFormatFromUmsToStack VideoFormat:%d\n", emTpFormat));
		}
	}
}

void ConvertVidFormatFromStackToUms(EmTpVideoFormat& emTpFormat, const EmPAVideoFormat& emPaFormat)
{
	switch(emPaFormat)
	{
	case emPAVH261:		
		{
			emTpFormat = emTPVH261;
		}
		break;
		
	case emPAVH262:
		{
			emTpFormat = emTPVH262;
		}
		break;
		
	case emPAVH263:
		{
			emTpFormat = emTPVH263;
		}
		break;
		
	case emPAVH263plus:
		{
			emTpFormat = emTPVH263plus;
		}
		break;
		
	case emPAVH264:
		{
			emTpFormat = emTPVH264;
		}
		break;
		
	case emPAVMPEG4:
		{
			emTpFormat = emTPVMPEG4;
		}
		break;
		
	default:	
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVidFormatFromStackToUms VideoFormat:%d\n", emPaFormat));
		}
	}
}	

u16 ConvertEmTpMixStatusFromUmsToStack( const EmTpMixStatus& tUms, EmPATpMixStatus& tPA )
{
	switch(tUms)
	{
	case emAudMixIdle:
		{
			tPA = emPAAudMixIdle;
			break;
		}
// 	case emAudMixAssignChan_Fail:
// 		{
// 			tPA = emPAAudMixAssignChan_Fail;
// 			break;
// 		}
// 	case emAudMixAssignChan_Success:
// 		{
// 			tPA = emPAAudMixAssignChan_Success;
// 			break;
// 		}
// 	case emAudMixOpenChan_Fail:
// 		{
// 			tPA = emPAAudMixOpenChan_Fail;
// 			break;
// 		}
// 	case emAudMixOpenChan_Success:
// 		{
// 			tPA = emPAAudMixOpenChan_Success;
// 			break;
// 		}
// 	case emAudMixDisConnect:
// 		{
// 			tPA = emPAAudMixDisConnect;
// 			break;
// 		}
// 	case emAudOpenChan_Fail:
// 		{
// 			tPA = emPAAudOpenChan_Fail;
// 			break;
// 		}
	case emAudOpenChan_Success:
		{
			tPA = emPAAudOpenChan_Success;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertEmTpMixStatusFromUmsToStack EmTpMixStatus :%d\n", tUms));
			return TP_RET_ERROR;
		}
	}
	
	return TP_RET_OK;
}

void ConvertCallResonFromUmsToStack(const EmCnsCallReason& emUms, EmPACnsCallReason& emStack)
{
	switch(emUms)
	{
	case EmCnsCallReason_success:
		{
			emStack = EmPACnsCallReason_success;
			break;
		}
	case EmCnsCallReason_hungup:
		{
			emStack = EmPACnsCallReason_hungup;
			break;
		}
	case EmCnsCallReason_Unreachable:
		{
			emStack = EmPACnsCallReason_Unreachable;
			break;
		}
	case EmCnsCallReason_resourcefull:
		{
			emStack = EmPACnsCallReason_resourcefull;
			break;
		}
	case EmCnsCallReason_dstnotfind:
		{
			emStack = EmPACnsCallReason_dstnotfind;
			break;
		}
	case EmCnsCallReason_unknown:
		{
			emStack = EmPACnsCallReason_unknown;
			break;
		}
	case EmCnsCallReason_Busy:
		{
			emStack = EmPACnsCallReason_Busy;
			break;
		}
	case EmCnsCallReason_Local:
		{
			emStack = EmPACnsCallReason_Local;
			break;
		}
	case EmCnsCallReason_NoConf:
		{
			emStack = EmPACnsCallReason_NoConf;
			break;
		}
	case EmCnsCallReason_Exist:
		{
			emStack = EmPACnsCallReason_Exist;
			break;
		}
	case EmCnsCallReason_Rejected:
		{
			emStack = EmPACnsCallReason_Rejected;
			break;
		}
	case EmCnsCallReason_peerhungup:
		{
			emStack = EmPACnsCallReason_peerhungup;
			break;
		}
	case EmCnsCallReason_Abnormal:
		{
			emStack = EmPACnsCallReason_Abnormal;
			break;
		}
	case EmCnsCallReason_PeerAbnormal:
		{
			emStack = EmPACnsCallReason_PeerAbnormal;
			break;
		}
	case EmCnsCallReason_ConfExist:
		{
			emStack = EmPACnsCallReason_Exist;
			break;
		}

	case EmCnsCallReason_AutoGetRegSerAddrFailed:
	case EmCnsCallReason_RegSerUnreachable:
	case EmCnsCallReason_AliasNotFound:
		{//回给cnc的上述原因，当作不可达处理
			emStack = EmPACnsCallReason_Unreachable;
			break;
		}
	case EmCnsCallReason_GetSignalEncryptKeyFailed:
		{
			emStack = EmPACnsCallReason_GetSignalEncryptKeyFailed;
			break;
		}

	case EmCnsCallReason_ConfOver:
	case EmCnsCallReason_cncallexception:
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertCallResonFromUmsToStack EmPACnsCallReason unknow protocol :%d\n", emUms));
			break;
		}
	}
}

u16 ConvertNodeDelFromUmsToStack(TPAConfNodeDelTrList& tPA, const TConfNodeDelTrList& tUms)
{
	u16 wNum = min(tUms.m_wNum, PA_REFRESH_LIST_FIVE);
	tPA.m_wNum = wNum;
	for (u16 wIndex = 0; wIndex < wNum; ++wIndex)
	{
		tPA.m_atList[wIndex].m_wEpID = tUms.m_atList[wIndex].m_wEpID;
		//ConvertEpKeyPathFromUmsToStack(tUms.m_atList[wIndex].m_tKey, tPA.m_atList[wIndex].m_tKey);
	}
	return TP_RET_OK;
}

u16 ConvertAddTvMonitorFromUmsToStack(TPATvMonitorCmd& tPA, const TTvMonitorCmdTr& tUms)
{
//	strncpy(tPA.m_achCascade, tUms.m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
	tPA.m_wEpID = tUms.m_wEpID;
	tPA.m_wIndex = tUms.m_wIndex;
	tPA.m_wScreenNum = tUms.m_wScreenNum;
	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidRtp, tUms.m_tVidAddr.m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidRtcp, tUms.m_tVidAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidBackRtp, tUms.m_tVidAddr.m_tBackRtcpAddr);
	
	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudRtp, tUms.m_tAudAddr.m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudRtcp, tUms.m_tAudAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudBackRtp, tUms.m_tAudAddr.m_tBackRtcpAddr);
	return TP_RET_OK;
}

u16 ConvertAddTvMonitorIndFromUmsToStack(TPATvMonitorInd& tPA, const TTvMonitorIndTr& tUms)
{
	tPA.m_bAccept = tUms.m_bAccept;	
//	strncpy(tPA.m_achCascade, tUms.m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
	tPA.m_wIndex = tUms.m_wIndex;
	tPA.m_wEpID = tUms.m_wEpID;
	tPA.m_wScreenNum = tUms.m_wScreenNum;
	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidRtp, tUms.m_tVidAddr.m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidRtcp, tUms.m_tVidAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tVidBackRtp, tUms.m_tVidAddr.m_tBackRtcpAddr);
	
	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudRtp, tUms.m_tAudAddr.m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudRtcp, tUms.m_tAudAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tAudBackRtp, tUms.m_tAudAddr.m_tBackRtcpAddr);
	return TP_RET_OK;
}

u16 ConvertConfCnsListFromUmsToStack(TPAConfCnsList& tPA, TConfCnsInfo& tUms)
{
	switch (tUms.m_emOpr)
	{
	case tp_OprType_Add:
		{
			tPA.m_tCnsList.m_emPAOpr = PA_OprType_Add;
			break;
		}
	case tp_OprType_Del:
		{
			tPA.m_tCnsList.m_emPAOpr = PA_OprType_Del;
			break;
		}
	case tp_OprType_Update:
		{
			tPA.m_tCnsList.m_emPAOpr = PA_OprType_Update;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertConfCnsListFromUmsToStack unknow type:%d\n", tUms.m_emOpr));
			break;
		}
	}
	tPA.m_tCnsList.m_wConfID = tUms.m_wConfID;
	tPA.m_tCnsList.m_wNum = min(tUms.m_wNum, PA_REFRESH_LIST_FIVE);
	
	TPACnsInfo* ptPACns;
	TCnsInfo* ptUmsCns;

	for(u16 wIndex = 0; wIndex < tPA.m_tCnsList.m_wNum; ++wIndex)
	{
		ptPACns = &tPA.m_tCnsList.m_atConfCnsList[wIndex];
		ptUmsCns = &tUms.m_tConfCnsList[wIndex];
		
		ptPACns->m_wEpID = ptUmsCns->m_wEpID;
		ptPACns->m_wParentEpID = ptUmsCns->m_wParentEpID;
		ptPACns->m_wChildEpID = ptUmsCns->m_wChildEpID;
		ptPACns->m_wBrotherEpID = ptUmsCns->m_wBrotherEpID;

		switch(ptUmsCns->m_emEpType)
		{
		case emTPEndpointTypeCNS:
			{
				ptPACns->m_emPAEpType = emPATPEndpointTypeCNS;
			}
			break;
		case emTPEndpointTypeUMS:
			{
				ptPACns->m_emPAEpType = emPATPEndpointTypeUMS;	
			}
			break;
		case emTPEndpointTypeRegister:
			{
				ptPACns->m_emPAEpType = emPATPEndpointTypeRegister;
			}
			break;
		case emTPEndpointH323MT:
			{
				ptPACns->m_emPAEpType = emPATPEndpointH323MT;
			}
			break;
		case emTPEndpointH323MCU:
			{
				ptPACns->m_emPAEpType = emPATPEndpointH323MCU;
			}
			break;
		case emTPEndpointH323SingleMCU:
			{
				ptPACns->m_emPAEpType = emPATPEndpointH323SingleMCU;
			}	
			break;
		case emTPEndpointH323G400:
			{
				ptPACns->m_emPAEpType = emPATPEndpointH323G400;
			}
			break;
		case emTPEndPointVrs:
			{
				ptPACns->m_emPAEpType = emPATPEndpointTypeVRS;
			}
			break;
		default:
			{
				MdlError(Ums_Mdl_Stack, ("ConvertConfCnsListFromUmsToStack Unknow end point type:%d\n", ptUmsCns->m_emEpType));
			}
			break;
		}	
		
		ConvertAliasFromUmsToStack(ptUmsCns->m_tCalledAddr, ptPACns->m_tCalledAddr);

		s8 * pzAliasUTF8 = NULL;
		gb2312_to_utf8(ptPACns->m_tCalledAddr.m_achAlias, &pzAliasUTF8);
		strncpy(ptPACns->m_tCalledAddr.m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
	
		ptPACns->m_bOnline = ptUmsCns->m_bOnline;

		ConvertCallResonFromUmsToStack(ptUmsCns->m_emCallReason, ptPACns->m_emPACallReason);

		gb2312_to_utf8((s8 *)ptUmsCns->m_achRoomName, &pzAliasUTF8);
		strncpy(ptPACns->m_achRoomName, pzAliasUTF8, PA_MAX_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;

		ptPACns->m_wLevel = ptUmsCns->m_wLevel;

		ptPACns->m_bMute = ptUmsCns->m_bMute;
		ptPACns->m_bQuiet = ptUmsCns->m_bQuiet;

		ptPACns->m_wSpeakerNum = ptUmsCns->m_wSpeakerNum;

		for (u16 i = 0; i < TP_MAX_STREAMNUM; ++i)
		{
			gb2312_to_utf8((s8 *)ptUmsCns->m_achSpeakerName[i], &pzAliasUTF8);
			strncpy(ptPACns->m_achSpeakerName[i], pzAliasUTF8, PA_MAX_ALIAS_LEN);
			free(pzAliasUTF8);
			pzAliasUTF8 = NULL;
		}
		MdlHint(Ums_Mdl_Stack, ("[ConvertConfCnsListFromUmsToStack] Ep List Show, wIndex:%d, EpId:%d, Alise:%s, bOnline:%d\n", wIndex, ptUmsCns->m_wEpID, ptUmsCns->m_tCalledAddr.m_abyAlias, ptUmsCns->m_bOnline));
	}
	return TP_RET_OK;
}

u16 ConvertViewCmdFromUmsToStack(TPAViewCmd& tPA, const TViewCmdTr& tUms)
{
	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftRtpAddr, tUms.m_atAddr[0].m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftRtcpAddr, tUms.m_atAddr[0].m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftBackRtcpAddr, tUms.m_atAddr[0].m_tBackRtcpAddr);

// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftSmallRtpAddr, tUms.m_atSmallAddr[0].m_tRtpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftSmallRtcpAddr, tUms.m_atSmallAddr[0].m_tRtcpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftSmallBackRtcpAddr, tUms.m_atSmallAddr[0].m_tBackRtcpAddr);

	ConvertConfNetAddrFromUmsToStack(tPA.m_tRtpAddr, tUms.m_atAddr[1].m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tRtcpAddr, tUms.m_atAddr[1].m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tBackRtcpAddr, tUms.m_atAddr[1].m_tBackRtcpAddr);
	
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tSmallRtpAddr, tUms.m_atSmallAddr[1].m_tRtpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tSmallRtcpAddr, tUms.m_atSmallAddr[1].m_tRtcpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tSmallBackRtcpAddr, tUms.m_atSmallAddr[1].m_tBackRtcpAddr);


	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightRtpAddr, tUms.m_atAddr[2].m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightRtcpAddr, tUms.m_atAddr[2].m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightBackRtcpAddr, tUms.m_atAddr[2].m_tBackRtcpAddr);
	
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightSmallRtpAddr, tUms.m_atSmallAddr[2].m_tRtpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightSmallRtcpAddr, tUms.m_atSmallAddr[2].m_tRtcpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightSmallBackRtcpAddr, tUms.m_atSmallAddr[2].m_tBackRtcpAddr);
	
	//add B2新增
	for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudAddr[wIndex].m_tRtpAddr, tUms.m_atAudAddr[wIndex].m_tRtpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudAddr[wIndex].m_tRtcpAddr, tUms.m_atAudAddr[wIndex].m_tRtcpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudAddr[wIndex].m_tBackRtcpAddr, tUms.m_atAudAddr[wIndex].m_tBackRtcpAddr);
	}

	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixAddr.m_tRtpAddr, tUms.m_tMixAddr.m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixAddr.m_tRtcpAddr, tUms.m_tMixAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixAddr.m_tBackRtcpAddr, tUms.m_tMixAddr.m_tBackRtcpAddr);
	//end

	tPA.m_wEpID = tUms.m_wEpID;
	tPA.m_wChanID = tUms.m_wIndex;
	
	tPA.m_bLeftOpen = tUms.m_abOpen[0];
//	tPA.m_bSmallLeftOpen = tUms.m_abSmallOpen[0];

	tPA.m_bMidOpen = tUms.m_abOpen[1];
//	tPA.m_bSmallMidOpen = tUms.m_abSmallOpen[1];
	
	tPA.m_bRightOpen = tUms.m_abOpen[2];
//	tPA.m_bSmallRightOpen = tUms.m_abSmallOpen[2];

	tPA.m_bViewSpeaker = tUms.m_bViewSpeaker;

	tPA.m_bNeedBas = tUms.m_bNeedBas;

	tPA.m_dwType = tUms.m_dwType;

	tPA.m_wSrcScreenIndex = tUms.m_wSrcScreenIndex;

	return TP_RET_OK;
}

u16 ConvertViewIndFromUmsToStack(TPAViewAck& tPA, const TViewAckTr& tUms)
{
	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftRtpAddr, tUms.m_atAddr[0].m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftRtcpAddr, tUms.m_atAddr[0].m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftBackRtcpAddr, tUms.m_atAddr[0].m_tBackRtcpAddr);

// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftSmallRtpAddr, tUms.m_atSmallAddr[0].m_tRtpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftSmallRtcpAddr, tUms.m_atSmallAddr[0].m_tRtcpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tLeftSmallBackRtcpAddr, tUms.m_atSmallAddr[0].m_tBackRtcpAddr);

	ConvertConfNetAddrFromUmsToStack(tPA.m_tRtpAddr, tUms.m_atAddr[1].m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tRtcpAddr, tUms.m_atAddr[1].m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tBackRtcpAddr, tUms.m_atAddr[1].m_tBackRtcpAddr);
	
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tSmallRtpAddr, tUms.m_atSmallAddr[1].m_tRtpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tSmallRtcpAddr, tUms.m_atSmallAddr[1].m_tRtcpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tSmallBackRtcpAddr, tUms.m_atSmallAddr[1].m_tBackRtcpAddr);
	
	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightRtpAddr, tUms.m_atAddr[2].m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightRtcpAddr, tUms.m_atAddr[2].m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightBackRtcpAddr, tUms.m_atAddr[2].m_tBackRtcpAddr);
	
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightSmallRtpAddr, tUms.m_atSmallAddr[2].m_tRtpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightSmallRtcpAddr, tUms.m_atSmallAddr[2].m_tRtcpAddr);
// 	ConvertConfNetAddrFromUmsToStack(tPA.m_tRightSmallBackRtcpAddr, tUms.m_atSmallAddr[2].m_tBackRtcpAddr);

	//add B2新增
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudAddr[wIndex].m_tRtpAddr, tUms.m_atAudAddr[wIndex].m_tRtpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudAddr[wIndex].m_tRtcpAddr, tUms.m_atAudAddr[wIndex].m_tRtcpAddr);
		ConvertConfNetAddrFromUmsToStack(tPA.m_atAudAddr[wIndex].m_tBackRtcpAddr, tUms.m_atAudAddr[wIndex].m_tBackRtcpAddr);
	}

	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixAddr.m_tRtpAddr, tUms.m_tMixAddr.m_tRtpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixAddr.m_tRtcpAddr, tUms.m_tMixAddr.m_tRtcpAddr);
	ConvertConfNetAddrFromUmsToStack(tPA.m_tMixAddr.m_tBackRtcpAddr, tUms.m_tMixAddr.m_tBackRtcpAddr);
	//end 

	tPA.m_wReason = tUms.m_emRes;
	tPA.m_wChanID = tUms.m_wIndex;
	
	tPA.m_bLeftOpen = tUms.m_abOpen[0];
//	tPA.m_bSmallLeftOpen = tUms.m_abSmallOpen[0];

	tPA.m_bMidOpen = tUms.m_abOpen[1];
//	tPA.m_bSmallMidOpen = tUms.m_abSmallOpen[1];
	
	tPA.m_bRightOpen = tUms.m_abOpen[2];
//	tPA.m_bSmallRightOpen = tUms.m_abSmallOpen[2];
	
	tPA.m_wReason = tUms.m_emRes;
	tPA.m_wChanID = tUms.m_wIndex;
	return TP_RET_OK;
}

u16 ConvertConfPollCmdFromStackToUms(TPAPollCmd& tPA, TPollCmdTr& tPollCmd)
{
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertConfNetAddrFromStackToUms(tPollCmd.m_tAddr[wIndex].m_tRtpAddr, tPA.m_atRtpAddr[wIndex]);
		ConvertConfNetAddrFromStackToUms(tPollCmd.m_tAddr[wIndex].m_tRtcpAddr, tPA.m_atRtcpAddr[wIndex]);
		ConvertConfNetAddrFromStackToUms(tPollCmd.m_tAddr[wIndex].m_tBackRtcpAddr, tPA.m_atBackRtcpAddr[wIndex]);
	}
	tPollCmd.m_wBitrate = tPA.m_wBitrate;
	tPollCmd.m_wInterval = tPA.m_wInterval;
	return TP_RET_OK;
}


u16 ConvertGetRegInfoTypeFromUmsToStack( const EmGetRegInfoType& tUms, EmPAGetRegInfoType& tPA )
{
	switch(tUms)
	{
	case emGetRegInfoType_CNS:
		{
			tPA = emPAGetRegInfoType_CNS;
			break;
		}

	case emGetRegInfoType_UMS:
		{
			tPA = emPAGetRegInfoType_UMS;
			break;
		}

	case emGetRegInfoType_ALL:
		{
			tPA = emPAGetRegInfoType_ALL;
			break;
		}

	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertGetRegInfoTypeFromUmsToStack EmGetRegInfoType :%d\n", tUms));
			return TP_RET_ERROR;
		}
	}
	
	return TP_RET_OK;	
}

u16 ConvertSipRegInfoFromStackToUms( const TPARegInfo& tPA, TTPSipRegInfo& tUms )
{
	tUms.m_wAliasNum = tPA.m_wAliasNum;
	EmTPEndpointType emUms = emTPEndpointTypeUnknown;
	ConvertEpTypeFromStackToUms(tPA.m_emSelfType, emUms);
	for ( u16 wIndex = 0; wIndex < tPA.m_wAliasNum; wIndex ++ )
	{
		ConvertAliasFromStackToUms(tPA.m_atAlias[wIndex], tUms.m_atAlias[wIndex]);
	}
	
	tUms.m_emSelfType = emUms;
	return TP_RET_OK;
}

u16 ConvertGetRegInfoTypeFromStackToUms( const EmPAGetRegInfoType& tPA, EmGetRegInfoType& tUms )
{
	switch(tPA)
	{
	case emPAGetRegInfoType_CNS:
		{
			tUms = emGetRegInfoType_CNS;
			break;
		}

	case emPAGetRegInfoType_UMS:
		{
			tUms = emGetRegInfoType_UMS;
			break;
		}

	case emPAGetRegInfoType_ALL:
		{
			tUms = emGetRegInfoType_ALL;
			break;
		}

	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertGetRegInfoTypeFromStackToUms EmPAGetRegInfoType :%d\n", tPA));
			return TP_RET_ERROR;
		}
	}
	
	return TP_RET_OK;
}

u16 ConvertSipRegPackInfoFromStackToUms( const TPARegPackInfo& tPA, TTPSipRegPackInfo& tUms )
{
	tUms.m_wPackSeq = tPA.m_wPackSeq;
	tUms.m_wTotalPackNum = tPA.m_wTotalPackNum;
	
	return TP_RET_OK;
}


u16 ConvertEmChannelReasonFromStackToUms( const EmChannelReason& tPA, EmTPChannelReason& tUms )
{
	switch(tPA)
	{
	case emModuleChannelReasonBegin:
		{
			tUms = emTPChannelReasonBegin;
			break;
		}

	case emModuleChannelDisconnectNormal:
		{
			tUms = emTPChannelDisconnectNormal;
			break;
		}

	case emModuleDualOffLine:
		{
			tUms = emTPDualOffLine;
			break;
		}

	case emModuleChannelDisconnectForce:
		{
			tUms = emTPForceStop;
			break;
		}
	case emModuleDualNotSend:
//	case emModuleDualNotSendMdl:
		{
			tUms = emTPDualNotSend;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertEmChannelReasonFromStackToUms EmPAChannelReason :%d\n", tPA));
			return TP_RET_ERROR;
		}
	}
	
	return TP_RET_OK;	
}

void ConvertCallDisconnectReasonFromUmsToStack(const EmCnsCallReason& emUmsReason ,EmModuleCallDisconnectReason& emModuleReason)
{
	switch(emUmsReason)
	{
	case EmCnsCallReason_hungup:
		{
			emModuleReason = emModuleDisconnect_Busy;
			break;
		}

	case EmCnsCallReason_Unreachable:
		{
			emModuleReason = emModuleDisconnect_Unreachable;
			break;
		}

	case EmCnsCallReason_resourcefull:
		{
			emModuleReason = emModuleDisconnect_Busy;
			break;
		}

	case EmCnsCallReason_dstnotfind:
		{
			emModuleReason = emModuleDisconnect_Rejected;
			break;
		}

	case EmCnsCallReason_Busy:
		{
			emModuleReason = emModuleDisconnect_Busy;
			break;
		}

	case EmCnsCallReason_Local:
		{
			emModuleReason = emModuleDisconnect_Local;
			break;
		}

	case EmCnsCallReason_ConfExist:
		{
			emModuleReason = emModuleDisconnect_ConfAlredayExit;
			break;
		}
		
	case EmCnsCallReason_Rejected:
		{
			emModuleReason = emModuleDisconnect_Rejected;
			break;
		}

	case EmCnsCallReason_peerhungup:
		{
			emModuleReason = emModuleDisconnect_Normal_Peer;
			break;
		}
		
	case EmCnsCallReason_Abnormal:
		{
			emModuleReason = emModuleDisconnect_Abnormal;
			break;
		}

	case EmCnsCallReason_PeerAbnormal:
		{
			emModuleReason = emModuleDisconnect_Abnormal_Peer;
			break;
		}

	case EmCnsCallReason_ConfOver:
		{
			emModuleReason = emModuleDisconnect_MultiConfOver;
			break;
		}

	default:
		{
			emModuleReason = emModuleDisconnect_unknown;
			MdlError(Ums_Mdl_Stack, ("ConvertCallDisconnectReasonFromUmsToStack unknow EmPACallReason protocol :%d\n", emModuleReason));
			break;
		}
	}
}

void ConvertOpTypeFromUmsToStack(const EmTpOprType& emUmsOpType, EmModuleOperateType& emModuleOpType)
{	
	switch (emUmsOpType)
	{
	case tp_OprType_Add:
		{
			emModuleOpType = emModuleOperateType_Add;
		}
		break;
			
	case tp_OprType_Del:
		{
			emModuleOpType = emModuleOperateType_Del;
		}
		break;

	case tp_OprType_Update:
		{
			emModuleOpType = emModuleOperateType_Update;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertOpTypeFromUmsToStack unknow  op type:%d\n", emUmsOpType));
			break;
		}
	}
}

void ConvertOpTypeFromUmsToStack( const EmTpOprType& emUmsOpType, EmPAModuleOperateType& emModuleOpType )
{
	switch (emUmsOpType)
	{
	case tp_OprType_Add:
		{
			emModuleOpType = emPAModuleOperateType_Add;
		}
		break;
		
	case tp_OprType_Del:
		{
			emModuleOpType = emPAModuleOperateType_Del;
		}
		break;
		
	case tp_OprType_Update:
		{
			emModuleOpType = emPAModuleOperateType_Update;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertOpTypeFromUmsToStack unknow  op type:%d\n", emUmsOpType));
			break;
		}
	}
}

//add
void ConvertVideoProfileFromUmsToStack(const EmTpVideoQualityLevel& emProfile, u32& emModuleProfile)
{
	switch(emProfile)
	{
	case emTPH264BP:
		{
			emModuleProfile = emModuleProfileBaseline;
			break;
		}
	case emTPH264HP:
		{
			emModuleProfile = emModuleProfileHigh;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVideoProfileFromUmsToStack unknow  op type:%d\n", emProfile));
			break;
		}
	}
}

void ConvertVideoProfileFromStackToUms(EmTpVideoQualityLevel& emProfile, const u32& emModuleProfile)
{
	switch(emModuleProfile)
	{
	case emModuleProfileBaseline:
		{
			emProfile = emTPH264BP;
			break;
		}

	case emModuleProfileHigh:
		{
			emProfile = emTPH264HP;
			break;
		}
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVideoProfileFromStackToUms unknow  op type:%d\n", emModuleProfile));
			break;
		}
	}
}

void ConvertVideoResFromStackToUms(EmTpVideoResolution& emRes, const EmModuleVideoResolution& emModuleVideoRes)
{
	emRes = emTPVResEnd;

	switch (emModuleVideoRes)
	{
	case emModuleVResolutionAuto:		
		{
			emRes = emTPVResolutionAuto;
			break;
		}

	case emModuleVSQCIF:				
		{
			emRes = emTPVSQCIF;
			break;
		}

	case emModuleVQCIF:					
		{
			emRes = emTPVQCIF;
			break;
		}

	case emModuleVCIF:					
		{
			emRes = emTPVCIF;
			break;
		}

	case emModuleV2CIF:					
		{
			emRes = emTPV2CIF;
			break;
		}

	case emModuleV4CIF:					
		{
			emRes = emTPV4CIF;
			break;
		}

	case emModuleV16CIF:				
		{
			emRes = emTPV16CIF;
			break;
		}
			
	case emModuleVHD480i720x480:		
		{
			emRes = emTPVHD480i720x480;
			break;
		}

	case emModuleVHD480p720x480:		
		{
			emRes = emTPVHD480p720x480;
			break;
		}

	case emModuleVHD576i720x576:		
		{
			emRes = emTPVHD576i720x576;
			break;
		}

	case emModuleVHD576p720x576:		
		{
			emRes = emTPVHD576p720x576;
			break;
		}
			
	case emModuleVHD720p1280x720:		
		{
			emRes = emTPVHD720p1280x720;
			break;
		}

	case emModuleVHD1080i1920x1080:		
		{
			emRes = emTPVHD1080i1920x1080;
			break;
		}

	case emModuleVHD1080p1920x1080:		
		{
			emRes = emTPVHD1080p1920x1080;
			break;
		}
			
	case emModuleVGA352x240:			
		{
			emRes = emTPVGA352x240;
			break;
		}

	case emModuleVGA704x480:			
		{
			emRes = emTPVGA704x480;
			break;
		}

	case emModuleVGA640x480:			
		{
			emRes = emTPVGA640x480;
			break;
		}

	case emModuleVGA800x600:			
		{
			emRes = emTPVGA800x600;
			break;
		}

	case emModuleVGA1024x768:			
		{
			emRes = emTPVGA1024x768;
			break;
		}

	case emModuleVGA1280x768:			
		{
			emRes = emTPVGA1280x768;
			break;
		}

	case emModuleVGA1280x800:			
		{
			emRes = emTPVGA1280x800;
			break;
		}

	case emModuleVGA1366x768:			
		{
			emRes = emTPVGA1366x768;
			break;
		}

	case emModuleVGA1280x854:			
		{
			emRes = emTPVGA1280x854;
			break;
		}

	case emModuleVGA1440x900:			
		{
			emRes = emTPVGA1440x900;
			break;
		}

	case emModuleVGA1280x1024:			
		{
			emRes = emTPVGA1280x1024;
			break;
		}

	case emModuleVGA1680x1050:			
		{
			emRes = emTPVGA1680x1050;
			break;
		}

	case emModuleVGA1600x1200:			
		{
			emRes = emTPVGA1600x1200;
			break;
		}

	case emModuleVGA1920x1200:			
		{
			emRes = emTPVGA1920x1200;
			break;
		}
	}
}

void ConvertVideoFormatFromStackToUms(EmTpVideoFormat& emTpFormat, const EmModuleVideoFormat& emPaFormat)
{
	switch(emPaFormat)
	{
	case emModuleVH261:		
		{
			emTpFormat = emTPVH261;
		}
		break;
		
	case emModuleVH262:
		{
			emTpFormat = emTPVH262;
		}
		break;
		
	case emModuleVH263:
		{
			emTpFormat = emTPVH263;
		}
		break;
		
	case emModuleVH263plus:
		{
			emTpFormat = emTPVH263plus;
		}
		break;
		
	case emModuleVH264:
		{
			emTpFormat = emTPVH264;
		}
		break;
		
	case emModuleVMPEG4:
		{
			emTpFormat = emTPVMPEG4;
		}
		break;
		
	default:	
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVideoFormatFromStackToUms VideoFormat:%d\n", emPaFormat));
		}
	}
}
void ConvertAliasTypeFromStackToUms(const emModuleCallType& emPaType, TPOUT EmTpAliasType& emTpType)
{
	switch(emPaType)
	{
	case emModuleIPCall:
		{
			emTpType = tp_Alias_IP;
		}
		break;
	case emModuleAliasCall:
		{
			emTpType = tp_Alias_h323;
		}
		break;
	case emModuleE164Call:
		{
			emTpType = tp_Alias_e164;
		}
		break;
	default:
		{
			emTpType = tp_Alias_Unknow;
		}
		break;
	}
}

void ConvertCreatConfInfoFromStackToUms(const TModuleCallInfo& tModuleInfo, TPOUT TTPConfTemplate& tConf)
{
	TTPConfTemplate tTemp;
	tTemp.m_wID = 0; //临时会议，模板ID统一为0
	s8 * pzAliasUTF8 = NULL;

	u16 wIndex = 0;
	//会场列表转化
	tTemp.m_atEpList.m_wNum = tModuleInfo.m_byTerNum;
	msgprintnotime("MTListNum:%d\n", tModuleInfo.m_byTerNum);
	for (wIndex = 0; wIndex < tModuleInfo.m_byTerNum; wIndex++)
	{
		EmTpAliasType emTpType = tp_Alias_Unknow;
		tTemp.m_atEpList.m_tCnsList[wIndex].m_wEpID = wIndex;
		
		ConvertAliasTypeFromStackToUms(tModuleInfo.m_atList[wIndex].m_emCallType, emTpType);
	
		if (tp_Alias_h323 == emTpType)
		{
			utf8_to_gb2312((s8 *)tModuleInfo.m_atList[wIndex].m_achAlias, &pzAliasUTF8);
			tTemp.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.SetAlias(emTpType, pzAliasUTF8);
			msgprintnotime("wIndex:%d, AliasName:%s\n", wIndex, tTemp.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tAlias.m_abyAlias);
		}
		else if (tp_Alias_e164 == emTpType)
		{
			utf8_to_gb2312((s8 *)tModuleInfo.m_atList[wIndex].m_achAlias, &pzAliasUTF8);
			tTemp.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.SetAlias(emTpType, pzAliasUTF8);
			msgprintnotime("wIndex:%d, E164Name:%s\n", wIndex, tTemp.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_tE164.m_abyAlias);
		}
		else if (tp_Alias_IP == emTpType)
		{
			tTemp.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP = tModuleInfo.m_atList[wIndex].m_tModuleAddress.m_dwIp;
			msgprintnotime("wIndex:%d, IP:"TPIPFORMAT"\n", wIndex, Tpu32ToIP(tTemp.m_atEpList.m_tCnsList[wIndex].m_tEpAddr.m_dwIP));
			continue;
		}
		else
		{
			MdlError(Ums_Mdl_Stack, ("ConvertCreatConfInfoFromStackToUms EpList type error!!! wIndex:%d, Type: %d\n", wIndex, emTpType));
			continue;
		}
		
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
	}
	
	utf8_to_gb2312((s8 *)tModuleInfo.m_tConfInfo.m_achConfName, &pzAliasUTF8);
	memcpy(tTemp.m_achConfName, pzAliasUTF8, sizeof(tTemp.m_achConfName));
	free(pzAliasUTF8);
	pzAliasUTF8 = NULL;

	// 码流加密信息
	ConverStreamKeyFromStackToUms(tModuleInfo.m_tStreamKey, tTemp.m_tEncrypt);
	// 临时模板的量子加密字段
	if ( tModuleInfo.m_bSignalEncrypt )
	{
		ConvertEpEncryptTypeFromStackToUms(tModuleInfo.m_tQtCallParam.m_emKeyFrequency, tTemp.m_tEncrypt.m_emEncryptModel);
	}
	msgprintnotime("[ConvertCreatConfInfoFromStackToUms] SignalEncrypt:%d, EncryptModel:%d\n", tModuleInfo.m_bSignalEncrypt, tTemp.m_tEncrypt.m_emEncryptModel);

	utf8_to_gb2312((s8 *)tModuleInfo.m_tConfInfo.m_achConfNumber, &pzAliasUTF8);
	memcpy(tTemp.m_achConfE164, pzAliasUTF8, sizeof(tTemp.m_achConfE164));
	free(pzAliasUTF8);
	pzAliasUTF8 = NULL;

	tTemp.m_dwPersistenceTime = tModuleInfo.m_tConfInfo.m_wConfDuration;
	tTemp.m_wDefaultChairMan = tTemp.m_atEpList.m_tCnsList[0].m_wEpID;
	
	tTemp.m_wAudFmtNum = 1;
	ConvertAudFormatFromStackToUms(tModuleInfo.m_tConfInfo.m_emAudioFormat, tTemp.m_atAudFmt[0].m_emFormat);

	//主视频格式转换
	tTemp.m_wMainNum = 1;
	ConvertVideoFormatFromStackToUms(tTemp.m_atTpMainVideoRes[0].m_emFormat, tModuleInfo.m_tConfInfo.m_emVideoFormat);
	ConvertVideoProfileFromStackToUms(tTemp.m_atTpMainVideoRes[0].m_emQualityLvl, tModuleInfo.m_tConfInfo.m_emProfile);
	ConvertVideoResFromStackToUms(tTemp.m_atTpMainVideoRes[0].m_emRes, tModuleInfo.m_tConfInfo.m_emResolution);
	tTemp.m_atTpMainVideoRes[0].m_wFrameRate = tModuleInfo.m_tConfInfo.m_byVidMPI;
	
	tTemp.m_wConfBitRate = tModuleInfo.m_tConfInfo.m_wCallRate;
	tTemp.m_wBpConfBitRate = tTemp.m_wConfBitRate;

	//轮询信息
	tTemp.m_tTurnList.m_bPollOn = tModuleInfo.m_tConfInfo.m_tPollInfo.m_bIsPoll;//轮询开关
	tTemp.m_tTurnList.m_wInterval = tModuleInfo.m_tConfInfo.m_tPollInfo.m_wPollExpire;//轮询间隔

	//讨论信息
	tTemp.m_atAuxMixList.m_bAudMixOn = tModuleInfo.m_tConfInfo.m_tConfAudMixInfo.m_bStart;//讨论开关
//	tTemp.m_atAuxMixList.m_wSpeakerIndex = tModuleInfo.m_tConfInfo.m_tConfAudMixInfo.m_wSpeakerIndex;
//	memcpy(tTemp.m_atAuxMixList.m_awList, tModuleInfo.m_tConfInfo.m_tConfAudMixInfo.m_awList, (sizeof(u16) * TP_CONF_MAX_AUDMIXNUM));//讨论列表

	//辅视频格式转换
	tTemp.m_wMinorNum = 1;
	ConvertVideoFormatFromStackToUms(tTemp.m_atTpMinorVideoRes[0].m_emFormat, tModuleInfo.m_tConfInfo.m_emSecVideoFormat);
	ConvertVideoProfileFromStackToUms(tTemp.m_atTpMinorVideoRes[0].m_emQualityLvl, tModuleInfo.m_tConfInfo.m_emSecProfile);
	ConvertVideoResFromStackToUms(tTemp.m_atTpMinorVideoRes[0].m_emRes, tModuleInfo.m_tConfInfo.m_emSecVidRes);
	tTemp.m_atTpMinorVideoRes[0].m_wFrameRate = tModuleInfo.m_tConfInfo.m_bySecVidMPI;

	tTemp.m_wHpDualBitRate = tModuleInfo.m_tConfInfo.m_wDualCallRate;
	tTemp.m_wBpDualBitRate = tTemp.m_wHpDualBitRate;


	memcpy(&tConf, &tTemp, sizeof(TTPConfTemplate));
	
}

void ConvertTpEpTypeFromStackToUms(const emModuleEndpointType& emPaType, EmTPEndpointType& emTpEpType)
{
	switch (emPaType)
	{
	case emModuleEndpointMT:		
		{
			emTpEpType = emTPEndpointH323MT;
			break;
		}
		
	case emModuleEndpointMcu:		
		{
			emTpEpType = emTPEndpointH323MCU;
			break;
		}
		
	case emModuleEndpointCNS:		
		{
			emTpEpType = emTPEndpointTypeCNS;
			break;
		}
		
	case emModuleEndpointUMS:		
		{
			emTpEpType = emTPEndpointTypeUMS;
			break;
		}
		
	case emModuleEndpointGateway:		
		{
			emTpEpType = emTPEndpointH323G400;
			break;
		}
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertTpEpTypeFromUmsToStack Unknow tpType:%d.\n", emTpEpType));
			break;
		}
	}
}


void ConvertModuleAliasFromStackToUms(const TModuleAlias& tPA, TTPAlias& tUms)
{
	switch(tPA.m_emAliasType)
	{
	case emModuleType_e164:
		{
			tUms.m_byType = tp_Alias_e164;
			break;
		}
	case emModuleType_h323ID:
		{
			tUms.m_byType = tp_Alias_h323;
			break;
		}
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertAliasFromStackToUms Unknow alias type:%d\n", tPA.m_emAliasType));
			break;
		}
	}
	
	memcpy(tUms.m_abyAlias, tPA.m_abyCallAliasAddr, TP_MAX_ALIAS_LEN);
	tUms.m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';	
}

void ConvertMtOnLineList(const TModuleMtOnlineList& tPaInfo, TTPMtRegInfo& tTpInfo)
{
	tTpInfo.m_wListNum = tPaInfo.m_wListNum;
	tTpInfo.m_bIsEnd = tPaInfo.m_bIsEnd;
	for (u16 wIndex = 0; wIndex < tPaInfo.m_wListNum; ++wIndex)
	{
		ConvertTpEpTypeFromStackToUms(tPaInfo.m_atTerminal[wIndex].m_emTerminalType,
									  tTpInfo.m_atTerminal[wIndex].m_emType);
		tTpInfo.m_atTerminal[wIndex].m_dwIp = tPaInfo.m_atTerminal[wIndex].m_dwIp;
		
		for (u16 wAliasIndex = 0; wAliasIndex < MAX_MT_ALIAS_NUM; ++wAliasIndex)
		{
			if (0 != strlen((s8*)(tPaInfo.m_atTerminal[wIndex].m_atAlias[wAliasIndex].m_abyCallAliasAddr)))
			{
				ConvertModuleAliasFromStackToUms(tPaInfo.m_atTerminal[wIndex].m_atAlias[wAliasIndex],
												 tTpInfo.m_atTerminal[wIndex].m_atAlias[wAliasIndex]);
			}
		}
	}
}

void ConvertMcuOnLineList(const TModuleMcuOnlineList& tPaInfo, TTPMcuRegInfo& tTpInfo)
{
	tTpInfo.m_wListNum = tPaInfo.m_wAliasNum;
	tTpInfo.m_dwIP = tPaInfo.m_dwIp;
	tTpInfo.m_bIsEnd = tPaInfo.m_bIsEnd;
	
	for (u16 wIndex = 0; wIndex < tPaInfo.m_wAliasNum; ++wIndex)
	{
		ConvertModuleAliasFromStackToUms(tPaInfo.m_atAlias[wIndex], tTpInfo.m_atAlias[wIndex]);
	}
}

void ConvertRegPackInfoFromStackToUms(const TPARegPack& tPaInfo, TRegPackInfoEx& tTpInfo)
{
	ConvertSipRegPackInfoFromStackToUms(tPaInfo.m_tPackInfo, tTpInfo.m_tPackInfo);
	ConvertGetRegInfoTypeFromStackToUms(tPaInfo.m_emType, tTpInfo.m_emType);
	ConvertTpEpTypeFromStackToUms(tPaInfo.m_emEndpointType, tTpInfo.m_emEndpointType);
}

void ConvertUmsRegInfoFromStackToUms(TPARegInfoUms& tPaInfo, TUmsRegInfoEx& tTpInfo)
{
	tTpInfo.m_wAliasNum = tPaInfo.m_wAliasNum;
	u16 wIndex = 0;

	s8 *pzAliasUTF8 = NULL;
	for (wIndex = 0; wIndex < tPaInfo.m_wAliasNum; ++wIndex)
	{
		ConvertAliasFromStackToUms(tPaInfo.m_atAlias[wIndex], tTpInfo.m_atAlias[wIndex]);

		utf8_to_gb2312((s8 *)tTpInfo.m_atAlias[wIndex].m_abyAlias, &pzAliasUTF8);
		strncpy(tTpInfo.m_atAlias[wIndex].m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
	}

	for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
	{
		ConvertConfNetAddrFromUmsToStack(tPaInfo.m_atContactAddr[wIndex], tTpInfo.m_atContactAddr[wIndex]);
	}

	tTpInfo.m_dwExpires = tPaInfo.m_dwExpires;
	ConvertEpTypeFromStackToUms(tPaInfo.m_tPaRegistLocalInfo.m_emEndpointType, tTpInfo.m_emEndpointType);
	tTpInfo.m_locolIP = tPaInfo.m_tPaRegistLocalInfo.m_dwLocalIP;
	memcpy(tTpInfo.m_softversion, tPaInfo.m_tPaRegistLocalInfo.m_achSoftVersion, TP_MAX_VERSION_LEN);
}

void ConvertCnsRegInfoFromStackToUms(TPARegInfoCns& tPaInfo, TCnsRegInfoEx& tTpInfo)
{
	tTpInfo.m_wAliasNum = tPaInfo.m_wAliasNum;
	u16 wIndex = 0;
	
	s8 *pzAliasUTF8 = NULL;
	for (wIndex = 0; wIndex < tPaInfo.m_wAliasNum; ++wIndex)
	{
		ConvertAliasFromStackToUms(tPaInfo.m_atAlias[wIndex], tTpInfo.m_atAlias[wIndex]);

		utf8_to_gb2312((s8 *)tTpInfo.m_atAlias[wIndex].m_abyAlias, &pzAliasUTF8);
		strncpy(tTpInfo.m_atAlias[wIndex].m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
	}
	
	for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
	{
		CovertConfNetAddrFromStackToUms(tPaInfo.m_atContactAddr[wIndex], tTpInfo.m_atContactAddr[wIndex]);
	}
	
	tTpInfo.m_dwExpires = tPaInfo.m_dwExpires;
	ConvertEpTypeFromStackToUms(tPaInfo.m_tPaRegistLocalInfo.m_emEndpointType, tTpInfo.m_emEndpointType);
	tTpInfo.m_locolIP = tPaInfo.m_atContactAddr[0].m_dwIP;
	memcpy(tTpInfo.m_softversion, tPaInfo.m_tPaRegistLocalInfo.m_achSoftVersion, TP_MAX_VERSION_LEN);
}

void ConvertVidProFromStackToUms(EmTpVideoQualityLevel& emPro, const EmPAProfileMask& emPaPro)
{
	switch(emPaPro)
	{
	case emPAProfileBaseline:
		{
			emPro = emTPH264BP;
		}
		break;
	case emPAProfileHigh:
		{
			emPro = emTPH264HP;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVidProFromStackToUms error, unknow EmPAProfileMask type\n"));
		}
		break;
	}
}
void ConvertVidProFromUmsToStack(EmPAProfileMask& emPaPro, const EmTpVideoQualityLevel& emPro)
{
	switch(emPro)
	{
	case emTPH264BP:
		{
			emPaPro = emPAProfileBaseline;
		}
		break;
	case emTPH264HP:
		{
			emPaPro = emPAProfileHigh;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVidProFromUmsToStack error, unknow type\n"));
		}
		break;
	}
}

void ConvertChnlCfgFromMdlStackToUms( EmTPAACChnlCfg& emTpChnlCfg, const EmModuleAudioChnlCfg& emPaChnlCfg )
{
	switch(emPaChnlCfg)
	{
	case emModuleChnlCust:
		emTpChnlCfg = emTPChnlCust;
		break;
	case emModuleChnl1:
		emTpChnlCfg = emTPChnl1;
		break;
	case emModuleChnl2:
		emTpChnlCfg = emTPChnl2;
		break;
	case emModuleChnl3:
		emTpChnlCfg = emTPChnl3;
		break;
	case emModuleChnl4:
		emTpChnlCfg = emTPChnl4;
		break;
	case emModuleChnl5:
		emTpChnlCfg = emTPChnl4;
		break;
	case emModuleChnl5dot1:
		emTpChnlCfg = emTPChnl5dot1;
		break;
	case emModuleChnl7dot1:
		emTpChnlCfg = emTPChnl7dot1;
		break;
	default:
		break;
	}
}

void ConvertSampleFreqFromMdlStackToUms( EmTPAACSampleFreq& emTpSampleFreq, const EmModuleAudioSampleFreq& emPaSampleFreq )
{
	switch(emPaSampleFreq)
	{
	case emModuleFs96000:
		emTpSampleFreq = emTPFs96000;
		break;
	case emModuleFs88200:
		emTpSampleFreq = emTPFs88200;
		break;
	case emModuleFs64000:
		emTpSampleFreq = emTPFs64000;
		break;
	case emModuleFs48000:
		emTpSampleFreq = emTPFs48000;
		break;
	case emModuleFs44100:
		emTpSampleFreq = emTPFs44100;
		break;
	case emModuleFs32000:
		emTpSampleFreq = emTPFs32000;
		break;
	case emModuleFs24000:
		emTpSampleFreq = emTPFs24000;
		break;
	case emModuleFs22050:
		emTpSampleFreq = emTPFs22050;
		break;
	case emModuleFs16000:
		emTpSampleFreq = emTPFs16000;
		break;
	case emModuleFs12000:
		emTpSampleFreq = emTPFs12000;
		break;
	case emModuleFs11025:
		emTpSampleFreq = emTPFs11025;
		break;
	case emModuleFs8000:
		emTpSampleFreq = emTPFs8000;
		break;
	default:
		break;
	}
}

//void CheckCallerIsInConfList(TTPConfTemplate& tconf, const TModuleCallInfo& tModuleInfo, TPOUT TUmsCallInfo& tCallInfo )
// {
// 	TEpAddr* ptEpAddr = tconf.m_atEpList.FindEp(tCallInfo.m_tSrcAddr);	
// 	if (NULL == ptEpAddr)
// 	{
// 		if (tCallInfo.m_tSrcAddr.m_byCallType == tp_Alias_e164)
// 		{
// 			return;
// 		}
// 		else
// 		{
// 			if (strlen((s8*)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr) > 0)
// 			{// caller的323别名不在邀请终端列表中，在caller有e164号的情况下，将caller的e164别名带到umscall
// 				s8 * pzAliasUTF8 = NULL;
// 				utf8_to_gb2312((s8 *)tModuleInfo.m_emCallerE164.m_abyCallAliasAddr, &pzAliasUTF8);
// 				tCallInfo.m_tSrcAddr.m_tE164.SetAlias(tp_Alias_e164, pzAliasUTF8);
// 				free(pzAliasUTF8);
// 				return;
// 			}
// 		}
// 	}
// 	return;
// }

void ConvertAudChanClosedParamFromUmsToStack( TPOUT HMDLCHANNEL* phChan, TPOUT HMDLAPPCHANNEL* phAppChan, TPOUT u8& bySize, const BOOL32& bIsSnd, const TUmsNodeCapset& tNode )
{
	u8 byRet = 0;
	if (bIsSnd)
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (!tNode.m_atAudEnc[wIndex].m_bIsChanOn)
			{
				continue;
			}
			phChan[byRet] = HMDLCHANNEL(tNode.m_atAudEnc[wIndex].m_tPAHandle);
			phAppChan[byRet] = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_audio_recv_handle, wIndex));
			byRet++;
		}
		bySize = byRet;
	}
	else
	{
		for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (!tNode.m_atAudDec[wIndex].m_bIsChanOn)
			{
				continue;
			}
			phChan[byRet] = HMDLCHANNEL(tNode.m_atAudDec[wIndex].m_tPAHandle);
			phAppChan[byRet] = HMDLAPPCHANNEL(CTpTypeAdpt::GetChannelHandle(em_audio_send_handle, wIndex));
			byRet++;
		}
		bySize = byRet;
	}
}

void ConvertSelViewReqFromUmsToStack( const TTPSelViewReq& tTpInfo, TPATPSelViewReq& tPAInfo )
{
	tPAInfo.m_bSel = tTpInfo.m_bSel;
	ConvertUITypeFromUmsToStack(tTpInfo.m_emUIType, tPAInfo.m_emUIType);
	ConvertViewEpTypeFromUmsToStack(tTpInfo.m_emType, tPAInfo.m_emType);
	tPAInfo.m_wConfID = tTpInfo.m_wConfID;
	tPAInfo.m_wDstID = tTpInfo.m_wDstID;
	tPAInfo.m_wEpID = tTpInfo.m_wEpID;
	tPAInfo.m_wScreenIndx = tTpInfo.m_wScreenIndx;
    tPAInfo.m_wDstScrIndx = tTpInfo.m_wDstScrIndx;
	return ;
}

void ConvertSelViewReqFromStackToUms( const TPATPSelViewReq& tPAInfo, TTPSelViewReq& tTpInfo )
{
	tTpInfo.m_bSel = tPAInfo.m_bSel;
	ConvertUITypeFromStackToUms(tPAInfo.m_emUIType, tTpInfo.m_emUIType);
	ConvertViewEpTypeFromStackToUms(tPAInfo.m_emType, tTpInfo.m_emType);
	tTpInfo.m_wConfID = tPAInfo.m_wConfID;
	tTpInfo.m_wDstID = tPAInfo.m_wDstID;
	tTpInfo.m_wEpID = tPAInfo.m_wEpID;
	tTpInfo.m_wScreenIndx = tPAInfo.m_wScreenIndx;
	tTpInfo.m_wDstScrIndx = tPAInfo.m_wDstScrIndx;

}

void ConvertSelViewIndFromUmsToStack( const TTPSelViewInd& tTpInfo, TPATPSelViewInd& tPAInfo )
{
	ConvertSelViewReqFromUmsToStack(tTpInfo.m_tSelView, tPAInfo.m_tSelView);
	tPAInfo.m_emRet = tTpInfo.m_emRet;
}

void ConvertSelViewIndFromStackToUms( const TPATPSelViewInd& tPAInfo, TTPSelViewInd& tTpInfo )
{
	ConvertSelViewReqFromStackToUms(tPAInfo.m_tSelView, tTpInfo.m_tSelView);
	tTpInfo.m_emRet = (EmViewRetReason)tPAInfo.m_emRet;
}

void ConvertSelViewNtfyFromUmsToStack( const TTPSelViewNtfy& tTpInfo, TPASelViewNtfy& tPAInfo )
{
	tPAInfo.m_wEpID = tTpInfo.m_wEpID;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertSelViewReqFromUmsToStack(tTpInfo.m_atSelView[wIndex], tPAInfo.m_atSelView[wIndex]);
	}
}

void ConvertSelViewNtfyFromStackToUms( const TPASelViewNtfy& tPAInfo, TTPSelViewNtfy& tTpInfo )
{
	tTpInfo.m_wEpID = tPAInfo.m_wEpID;
	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ConvertSelViewReqFromStackToUms(tPAInfo.m_atSelView[wIndex], tTpInfo.m_atSelView[wIndex]);
	}
}

void ConvertUITypeFromUmsToStack( const EmUIType& emTp, EmPAUIType& emPA )
{
	switch (emTp)
	{
	case EmUI_CNC:
		{
			emPA = EmPAUI_CNC;
		}
		break;
		
	case EmUI_UMC:
		{
			emPA = EmPAUI_UMC;
		}
		break;
		
	case EmUI_Tools:
		{
			emPA = EmPAUI_Tools;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertUITypeFromUmsToStack unknow  op type:%d\n", emTp));
			break;
		}
	}
}

void ConvertUITypeFromStackToUms( const EmPAUIType& emPA, EmUIType& emTp )
{
	switch (emPA)
	{
	case EmPAUI_CNC:
		{
			emTp = EmUI_CNC;
		}
		break;
		
	case EmPAUI_UMC:
		{
			emTp = EmUI_UMC;
		}
		break;
		
	case EmPAUI_Tools:
		{
			emTp = EmUI_Tools;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertUITypeFromStackToUms unknow  op type:%d\n", emPA));
			break;
		}
	}
}

void ConvertViewEpTypeFromUmsToStack( const EmViewEpType& emTp, EmPAViewEpType& emPA )
{
	switch (emTp)
	{
	case EmEpType_Ter:
		{
			emPA = EmPAEpType_Ter;
		}
		break;
		
	case EmEpType_Eqp:
		{
			emPA = EmPAEpType_Eqp;
		}
		break;
	default:
		{
			break;
		}
	}
}

void ConvertViewEpTypeFromStackToUms( const EmPAViewEpType& emPA, EmViewEpType& emTp )
{
	switch (emPA)
	{
	case EmPAEpType_Ter:
		{
			emTp = EmEpType_Ter;
		}
		break;
		
	case EmPAEpType_Eqp:
		{
			emTp = EmEpType_Eqp;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertViewEpTypeFromStackToUms unknow  op type:%d\n", emPA));
			break;
		}
	}
}

void ConvertOpTypeFromStackToUms( const EmModuleOperateType& emModuleOpType, EmTpOprType& emUmsOpType )
{
	switch (emModuleOpType)
	{
	case emModuleOperateType_Add:
		{
			emUmsOpType = tp_OprType_Add;
		}
		break;
		
	case emModuleOperateType_Del:
		{
			emUmsOpType = tp_OprType_Del;
		}
		break;
		
	case emModuleOperateType_Update:
		{
			emUmsOpType = tp_OprType_Update;
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertOpTypeFromStackToUms unknow  op type:%d\n", emModuleOpType));
			break;
		}
	}
}

void ConvertOprTypeFromUmsToStack( const EmTpOprType& emUmsOpType, EmPAOprType& emModuleOpType )
{
	switch (emUmsOpType)
	{
	case tp_OprType_Add:
		{
			emModuleOpType = PA_OprType_Add;
		}
		break;
		
	case tp_OprType_Del:
		{
			emModuleOpType = PA_OprType_Del;
		}
		break;
		
	case tp_OprType_Update:
		{
			emModuleOpType = PA_OprType_Update;
		}
		break;

	case tp_OprType_NULL:
		{
			emModuleOpType = PA_OprType_Null;
		}
		break;		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertOprTypeFromUmsToStack unknow  op type:%d\n", emUmsOpType));
			break;
		}
	}
}

void ConvertOprTypeFromStackToUms( const EmPAOprType& emModuleOpType, EmTpOprType& emUmsOpType )
{
	switch (emModuleOpType)
	{
	case PA_OprType_Add:
		{
			emUmsOpType = tp_OprType_Add;
		}
		break;
		
	case PA_OprType_Del:
		{
			emUmsOpType = tp_OprType_Del;
		}
		break;
		
	case PA_OprType_Update:
		{
			emUmsOpType = tp_OprType_Update;
		}
		break;
	
	case PA_OprType_Null:
		{
			emUmsOpType = tp_OprType_NULL;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertOprTypeFromStackToUms unknow  op type:%d\n", emModuleOpType));
			break;
		}
	}
}

void ConvertMdlVendorFromStackToUms( const EmModuleVendorID emPA, EmTpVendorID& emUms )
{
	switch (emPA)
	{
	case emModule_vendor_MICROSOFT_NETMEETING:
		{
			emUms = EmTp_vendor_MICROSOFT_NETMEETING;
		}
		break;
		
	case emModule_vendor_KEDA:
		{
			emUms = EmTp_vendor_KEDA;
		}
		break;
		
	case emModule_vendor_HUAWEI:
		{
			emUms = EmTp_vendor_HUAWEI;
		}
		break;
		
	case emModule_vendor_POLYCOM:
		{
			emUms = EmTp_vendor_POLYCOM;
		}
		break;
	case emModule_vendor_POLYCOM_MCU:
		{
			emUms = EmTp_vendor_POLYCOM_MCU;
		}
		break;
		
	case emModule_vendor_TANDBERG:
		{
			emUms = EmTp_vendor_TANDBERG;
		}
		break;
		
	case emModule_vendor_RADVISION:
		{
			emUms = EmTp_vendor_RADVISION;
		}
		break;
		
	case emModule_vendor_VCON:
		{
			emUms = EmTp_vendor_VCON;
		}
		break;
	case emModule_vendor_SONY:
		{
			emUms = EmTp_vendor_SONY;
		}
		break;
		
	case emModule_vendor_VTEL:
		{
			emUms = EmTp_vendor_VTEL;
		}
		break;
		
	case emModule_vendor_ZTE:
		{
			emUms = EmTp_vendor_ZTE;
		}
		break;
		
	case emModule_vendor_ZTE_MCU:
		{
			emUms = EmTp_vendor_ZTE_MCU;
		}
		break;
	case emModule_vendor_CODIAN:
		{
			emUms = EmTp_vendor_CODIAN;
		}
		break;
		
	case emModule_vendor_AETHRA:
		{
			emUms = EmTp_vendor_AETHRA;
		}
		break;
		
	case emModule_vendor_CHAORAN:
		{
			emUms = EmTp_vendor_CHAORAN;
		}
		break;
		
	case emModule_vendor_UNKNOWN:
		{
			emUms = EmTp_vendor_UNKNOWN;
		}
		break;
	case emModule_vendor_END:
		{
			emUms = EmTp_vendor_END;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVendorFromStackToUms unknow  op type:%d\n", emPA));
			break;
		}
	}
}

void ConvertMdlVendorFromUmsToStack( const EmTpVendorID emUms, EmModuleVendorID& emPA )
{
	switch (emUms)
	{
	case EmTp_vendor_MICROSOFT_NETMEETING:
		{
			emPA = emModule_vendor_MICROSOFT_NETMEETING;
		}
		break;
		
	case EmTp_vendor_KEDA:
		{
			emPA = emModule_vendor_KEDA;
		}
		break;
		
	case EmTp_vendor_HUAWEI:
		{
			emPA = emModule_vendor_HUAWEI;
		}
		break;
		
	case EmTp_vendor_POLYCOM:
		{
			emPA = emModule_vendor_POLYCOM;
		}
		break;
	case EmTp_vendor_POLYCOM_MCU:
		{
			emPA = emModule_vendor_POLYCOM_MCU;
		}
		break;
		
	case EmTp_vendor_TANDBERG:
		{
			emPA = emModule_vendor_TANDBERG;
		}
		break;
		
	case EmTp_vendor_RADVISION:
		{
			emPA = emModule_vendor_RADVISION;
		}
		break;
		
	case EmTp_vendor_VCON:
		{
			emPA = emModule_vendor_VCON;
		}
		break;
	case EmTp_vendor_SONY:
		{
			emPA = emModule_vendor_SONY;
		}
		break;
		
	case EmTp_vendor_VTEL:
		{
			emPA = emModule_vendor_VTEL;
		}
		break;
		
	case EmTp_vendor_ZTE:
		{
			emPA = emModule_vendor_ZTE;
		}
		break;
		
	case EmTp_vendor_ZTE_MCU:
		{
			emPA = emModule_vendor_ZTE_MCU;
		}
		break;
	case EmTp_vendor_CODIAN:
		{
			emPA = emModule_vendor_CODIAN;
		}
		break;
		
	case EmTp_vendor_AETHRA:
		{
			emPA = emModule_vendor_AETHRA;
		}
		break;
		
	case EmTp_vendor_CHAORAN:
		{
			emPA = emModule_vendor_CHAORAN;
		}
		break;
		
	case EmTp_vendor_UNKNOWN:
		{
			emPA = emModule_vendor_UNKNOWN;
		}
		break;
	case EmTp_vendor_END:
		{
			emPA = emModule_vendor_END;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVendorFromUmsToStack unknow  op type:%d\n", emUms));
			break;
		}
	}
}

void ConvertMtVIDEO_FORMATFromStackToUms( const u8 byFramteR, EmTpVideoResolution& emUms )
{
	switch (byFramteR)
	{
	case VIDEO_FORMAT_SQCIF:
		{
			emUms = emTPVSQCIF;
		}
		break;
	case VIDEO_FORMAT_QCIF:
		{
			emUms = emTPVQCIF;
		}
		break;
	case VIDEO_FORMAT_CIF:
		{
			emUms = emTPVCIF;
		}
		break;
	case VIDEO_FORMAT_2CIF:
		{
			emUms = emTPV2CIF;
		}
		break;
	case VIDEO_FORMAT_4CIF:
		{
			emUms = emTPV4CIF;
		}
		break;
	case VIDEO_FORMAT_16CIF:
		{
			emUms = emTPV16CIF;
		}
		break;
	case VIDEO_FORMAT_AUTO:
		{
			emUms = emTPVResolutionAuto;
		}
		break;
	case VIDEO_FORMAT_SIF:
		{
			emUms = emTPVGA352x240;
		}
		break;
	case VIDEO_FORMAT_2SIF:
		{//无此枚举 转成小的
			emUms = emTPVGA352x240;
		}
		break;
	case VIDEO_FORMAT_4SIF:
		{
			emUms = emTPVGA704x480;
		}
		break;
	case VIDEO_FORMAT_VGA:
		{
			emUms = emTPVGA640x480;
		}
		break;
	case VIDEO_FORMAT_SVGA:
		{
			emUms = emTPVGA800x600;
		}
		break;
	case VIDEO_FORMAT_XGA:
		{
			emUms = emTPVGA1024x768;
		}
		break;
	case VIDEO_FORMAT_WXGA:
		{
			emUms = emTPVGA1280x768;
		}
		break;
	case VIDEO_FORMAT_SQCIF_112x96:
		{
			emUms = emTPVSQCIF112x96;
		}
		break;
	case VIDEO_FORMAT_SQCIF_96x80:
		{
			emUms = emTPVSQCIF96x80;
		}
		break;
	case VIDEO_FORMAT_W4CIF:
		{//无此枚举 转成小的
			emUms = emTPVGA704x480;
		}
		break;
	case VIDEO_FORMAT_HD720:
		{
			emUms = emTPVHD720p1280x720;
		}
		break;
	case VIDEO_FORMAT_SXGA:
		{
			emUms = emTPVGA1280x1024;
		}
		break;
	case VIDEO_FORMAT_UXGA:
		{
			emUms = emTPVGA1600x1200;
		}
		break;
	case VIDEO_FORMAT_HD1080:
		{
			emUms = emTPVHD1080p1920x1080;
		}
		break;
	case VIDEO_FORMAT_1440x816:
		{
			emUms = emTPV1440x816;
		}
		break;
	case VIDEO_FORMAT_1280x720:
		{
			emUms = emTPVHD720p1280x720;
		}
		break;
	case VIDEO_FORMAT_960x544:
		{
			emUms = emTPV960x544;
		}
		break;
	case VIDEO_FORMAT_640x368:
		{
			emUms = emTPV640x368;
		}
		break;
	case VIDEO_FORMAT_480x272:
		{
			emUms = emTPV480x272;
		}
		break;
	case VIDEO_FORMAT_720_960x544:
		{
			emUms = emTPV960x544;
		}
		break;
	case VIDEO_FORMAT_720_864x480:
		{
			emUms = emTPV864x480;
		}
		break;
	case VIDEO_FORMAT_720_640x368:
		{
			emUms = emTPV640x368;
		}
		break;
	case VIDEO_FORMAT_720_432x240:
		{
			emUms = emTPV432x240;
		}
		break;
	case VIDEO_FORMAT_720_320x192:
		{
			emUms = emTPV320x192;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertMtVIDEO_FORMATFromStackToUms unknow FrmateR:%d\n", byFramteR));
			break;
		}
	}
}

void ConvertMtVIDEO_FORMATFromUmsToStack( const EmTpVideoResolution emUms, u8& byFramteR )
{
	switch (emUms)
	{
	case emTPVSQCIF:
		{
			byFramteR = VIDEO_FORMAT_SQCIF;
		}
		break;
	case emTPVQCIF:
		{
			byFramteR = VIDEO_FORMAT_QCIF;
		}
		break;
	case emTPVCIF:
		{
			byFramteR = VIDEO_FORMAT_CIF;
		}
		break;
	case emTPV2CIF:
		{
			byFramteR = VIDEO_FORMAT_2CIF;
		}
		break;
	case emTPV4CIF:
		{
			byFramteR = VIDEO_FORMAT_4CIF;
		}
		break;
	case emTPV16CIF:
		{
			byFramteR = VIDEO_FORMAT_16CIF;
		}
		break;
	case emTPVResolutionAuto:
		{
			byFramteR = VIDEO_FORMAT_AUTO;
		}
		break;
	case emTPVGA352x240:
		{
			byFramteR = VIDEO_FORMAT_SIF;
		}
		break;
// 	case emTPVGA352x240:
// 		{//无此枚举 转成小的
// 			byFramteR = VIDEO_FORMAT_2SIF;
// 		}
// 		break;
	case emTPVGA704x480:
		{
			byFramteR = VIDEO_FORMAT_4SIF;
		}
		break;
	case emTPVGA640x480:
		{
			byFramteR = VIDEO_FORMAT_VGA;
		}
		break;
	case emTPVGA800x600:
		{
			byFramteR = VIDEO_FORMAT_SVGA;
		}
		break;
	case emTPVGA1024x768:
		{
			byFramteR = VIDEO_FORMAT_XGA;
		}
		break;
	case emTPVGA1280x768:
		{
			byFramteR = VIDEO_FORMAT_WXGA;
		}
		break;
	case emTPVSQCIF112x96:
		{
			byFramteR = VIDEO_FORMAT_SQCIF_112x96;
		}
		break;
	case emTPVSQCIF96x80:
		{
			byFramteR = VIDEO_FORMAT_SQCIF_96x80;
		}
		break;
// 	case emTPVGA704x480:
// 		{//无此枚举 转成小的
// 			byFramteR = VIDEO_FORMAT_W4CIF;
// 		}
// 		break;
	case emTPVHD720p1280x720:
		{
			byFramteR = VIDEO_FORMAT_HD720;
		}
		break;
	case emTPVGA1280x1024:
		{
			byFramteR = VIDEO_FORMAT_SXGA;
		}
		break;
	case emTPVGA1600x1200:
		{
			byFramteR = VIDEO_FORMAT_UXGA;
		}
		break;
	case emTPVHD1080p1920x1080:
		{
			byFramteR = VIDEO_FORMAT_HD1080;
		}
		break;
	case emTPV1440x816:
		{
			byFramteR = VIDEO_FORMAT_1440x816;
		}
		break;
// 	case emTPVHD720p1280x720:
// 		{
// 			byFramteR = VIDEO_FORMAT_1280x720;
// 		}
// 		break;
	case emTPV960x544:
		{
			byFramteR = VIDEO_FORMAT_960x544;
		}
		break;
	case emTPV640x368:
		{
			byFramteR = VIDEO_FORMAT_640x368;
		}
		break;
	case emTPV480x272:
		{
			byFramteR = VIDEO_FORMAT_480x272;
		}
		break;
// 	case emTPV960x544:
// 		{
// 			byFramteR = VIDEO_FORMAT_720_960x544;
// 		}
// 		break;
	case emTPV864x480:
		{
			byFramteR = VIDEO_FORMAT_720_864x480;
		}
		break;
// 	case emTPV640x368:
// 		{
// 			byFramteR = VIDEO_FORMAT_720_640x368;
// 		}
// 		break;
	case emTPV432x240:
		{
			byFramteR = VIDEO_FORMAT_720_432x240;
		}
		break;
	case emTPV320x192:
		{
			byFramteR = VIDEO_FORMAT_720_320x192;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertMtVIDEO_FORMATFromUmsToStack unknow Res:%d\n", emUms));
			break;
		}
	}
}

void ConvertCasecadePollEpReqFromStackToUms( const TPACasecadePollEpReq& tPa, TCasecadePollEpReq& tUms )
{
	tUms.m_bCreate = tPa.m_bCreate;
	tUms.m_wEpID = tPa.m_wEpID;
	
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		ConvertConfNetAddrFromStackToUms(tUms.m_atPollAddr[wIndex], tPa.m_atPollAddr[wIndex]);
		ConvertConfNetAddrFromStackToUms(tUms.m_atSmallAddr[wIndex], tPa.m_atPollSmallAddr[wIndex]);
	}
}

void ConvertCasecadePollEpReqFromUmsToStack( const TCasecadePollEpReq& tUms, TPACasecadePollEpReq& tPa )
{
	tPa.m_bCreate = tUms.m_bCreate;
	tPa.m_wEpID = tUms.m_wEpID;
	
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		ConvertConfNetAddrFromUmsToStack(tPa.m_atPollAddr[wIndex], tUms.m_atPollAddr[wIndex]);
		ConvertConfNetAddrFromUmsToStack(tPa.m_atPollSmallAddr[wIndex], tUms.m_atSmallAddr[wIndex]);
	}
}

void ConvertEqpInfoFromStackToUms( const TPAEqpInfo& tPa, TEqpInfo& tUms )
{
	tUms.m_byEqpID = tPa.m_byEqpID;
	tUms.m_emEqpType = (EMEqpType)tPa.m_emEqpType;

	s8 *pzAliasUTF8 = NULL;
	utf8_to_gb2312((s8*)tPa.m_szEqpAlias, &pzAliasUTF8);
	strncpy(tUms.m_szEqpAlias, pzAliasUTF8, TP_MAXLEN_EQP_ALIAS);
	tUms.m_szEqpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';
	free(pzAliasUTF8);
	pzAliasUTF8 = NULL;
}

void ConvertEqpInfoFromUmsToStack( const TEqpInfo& tUms, TPAEqpInfo& tPa )
{
	tPa.m_byEqpID = tUms.m_byEqpID;
	tPa.m_emEqpType = tUms.m_emEqpType;

	s8 *pzAliasUTF8 = NULL;
	gb2312_to_utf8((s8*)tUms.m_szEqpAlias, &pzAliasUTF8);
	strncpy(tPa.m_szEqpAlias, pzAliasUTF8, TP_MAXLEN_EQP_ALIAS);
	tPa.m_szEqpAlias[TP_MAXLEN_EQP_ALIAS-1] = '\0';
	free(pzAliasUTF8);
	pzAliasUTF8 = NULL;
}

void ConvertVmpStyleInfoFromStackToUms( const TPABrdVmpStyle& tPa, TBrdVmpStyle& tUms )
{
	tUms.m_emVmpStyle = (EMVmpStyle)tPa.m_emVmpStyle;
	tUms.m_wSpeakerIndx = tPa.m_wSpeakerIndx;
	tUms.m_wDualIndx = tPa.m_wChairIndx;
	tUms.m_wChnlNum = tPa.m_wChnlNum;
	memcpy(tUms.m_atVmpChnl, tPa.m_atVmpChnl, sizeof(tUms.m_atVmpChnl));
}

void ConvertVmpStyleInfoFromUmsToStack( const TBrdVmpStyle& tUms, TPABrdVmpStyle& tPa )
{
	tPa.m_emVmpStyle = (EmPATPVMPStyle)tUms.m_emVmpStyle;
	tPa.m_wSpeakerIndx = tUms.m_wSpeakerIndx;
	tPa.m_wChairIndx = tUms.m_wDualIndx;
	tPa.m_wChnlNum = tUms.m_wChnlNum;
	memcpy(tPa.m_atVmpChnl, tUms.m_atVmpChnl, sizeof(tPa.m_atVmpChnl));
}

void ConvertVendorFromStackToUms( const EmPAVendorID emPA, EmTpVendorID& emUms )
{
	switch (emPA)
	{
	case emPA_vendor_MICROSOFT_NETMEETING:
		{
			emUms = EmTp_vendor_MICROSOFT_NETMEETING;
		}
		break;
		
	case emPA_vendor_KEDA:
		{
			emUms = EmTp_vendor_KEDA;
		}
		break;

	case emPA_vendor_KEDA_IPC:
		{
			emUms = EmTp_vendor_KEDA;
		}
		break;
		
	case emPA_vendor_HUAWEI:
		{
			emUms = EmTp_vendor_HUAWEI;
		}
		break;
		
	case emPA_vendor_POLYCOM:
		{
			emUms = EmTp_vendor_POLYCOM;
		}
		break;
	case emPA_vendor_POLYCOM_MCU:
		{
			emUms = EmTp_vendor_POLYCOM_MCU;
		}
		break;
		
	case emPA_vendor_TANDBERG:
		{
			emUms = EmTp_vendor_TANDBERG;
		}
		break;
		
	case emPA_vendor_RADVISION:
		{
			emUms = EmTp_vendor_RADVISION;
		}
		break;
		
	case emPA_vendor_VCON:
		{
			emUms = EmTp_vendor_VCON;
		}
		break;
	case emPA_vendor_SONY:
		{
			emUms = EmTp_vendor_SONY;
		}
		break;
		
	case emPA_vendor_VTEL:
		{
			emUms = EmTp_vendor_VTEL;
		}
		break;
		
	case emPA_vendor_ZTE:
		{
			emUms = EmTp_vendor_ZTE;
		}
		break;
		
	case emPA_vendor_ZTE_MCU:
		{
			emUms = EmTp_vendor_ZTE_MCU;
		}
		break;
	case emPA_vendor_CODIAN:
		{
			emUms = EmTp_vendor_CODIAN;
		}
		break;
		
	case emPA_vendor_AETHRA:
		{
			emUms = EmTp_vendor_AETHRA;
		}
		break;
		
	case emPA_vendor_CHAORAN:
		{
			emUms = EmTp_vendor_CHAORAN;
		}
		break;
		
	case emPA_vendor_UNKNOWN:
		{
			emUms = EmTp_vendor_UNKNOWN;
		}
		break;
	case emPA_vendor_END:
		{
			emUms = EmTp_vendor_END;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVendorFromStackToUms unknow  op type:%d\n", emPA));
			break;
		}
	}
}

void ConvertVendorFromUmsToStack( const EmTpVendorID emUms, EmPAVendorID& emPA )
{
	switch (emUms)
	{
	case EmTp_vendor_MICROSOFT_NETMEETING:
		{
			emPA = emPA_vendor_MICROSOFT_NETMEETING;
		}
		break;
		
	case EmTp_vendor_KEDA:
		{
			emPA = emPA_vendor_KEDA;
		}
		break;

	case EmTp_vendor_KEDA_IPC:
		{
			emPA = emPA_vendor_KEDA_IPC;
		}
		break;
		
	case EmTp_vendor_HUAWEI:
		{
			emPA = emPA_vendor_HUAWEI;
		}
		break;
		
	case EmTp_vendor_POLYCOM:
		{
			emPA = emPA_vendor_POLYCOM;
		}
		break;
	case EmTp_vendor_POLYCOM_MCU:
		{
			emPA = emPA_vendor_POLYCOM_MCU;
		}
		break;
		
	case EmTp_vendor_TANDBERG:
		{
			emPA = emPA_vendor_TANDBERG;
		}
		break;
		
	case EmTp_vendor_RADVISION:
		{
			emPA = emPA_vendor_RADVISION;
		}
		break;
		
	case EmTp_vendor_VCON:
		{
			emPA = emPA_vendor_VCON;
		}
		break;
	case EmTp_vendor_SONY:
		{
			emPA = emPA_vendor_SONY;
		}
		break;
		
	case EmTp_vendor_VTEL:
		{
			emPA = emPA_vendor_VTEL;
		}
		break;
		
	case EmTp_vendor_ZTE:
		{
			emPA = emPA_vendor_ZTE;
		}
		break;
		
	case EmTp_vendor_ZTE_MCU:
		{
			emPA = emPA_vendor_ZTE_MCU;
		}
		break;
	case EmTp_vendor_CODIAN:
		{
			emPA = emPA_vendor_CODIAN;
		}
		break;
		
	case EmTp_vendor_AETHRA:
		{
			emPA = emPA_vendor_AETHRA;
		}
		break;
		
	case EmTp_vendor_CHAORAN:
		{
			emPA = emPA_vendor_CHAORAN;
		}
		break;
		
	case EmTp_vendor_UNKNOWN:
		{
			emPA = emPA_vendor_UNKNOWN;
		}
		break;
	case EmTp_vendor_END:
		{
			emPA = emPA_vendor_END;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConvertVendorFromUmsToStack unknow  op type:%d\n", emUms));
			break;
		}
	}
}
void ConvertGetVidBaseInfoFromUmsToStack(const TGetVidBaseInfo& tTpInfo, TPAGetVidBaseInfo& tPaInfo)
{
	tPaInfo.m_wHandle = tTpInfo.m_wHandle;
	tPaInfo.m_wEpID = tTpInfo.m_wEpID;
	tPaInfo.m_wScreenIndex = tTpInfo.m_wScreenIndex;

	switch (tTpInfo.m_emType)
	{
	case em_GetVid_View:
		{
			tPaInfo.m_emType = em_PAGetVid_View;
		}
		break;

	case em_GetVid_Poll:
		{
			tPaInfo.m_emType = em_PAGetVid_Poll;
		}
		break;

	case em_GetVid_Vmp:
		{
			tPaInfo.m_emType = em_PAGetVid_Vmp;
		}
		break;

	case em_GetVid_Hdu:
		{
			tPaInfo.m_emType = em_PAGetVid_Hdu;
		}
		break;

	case em_GetVid_Dis:
		{
			tPaInfo.m_emType = em_PAGetVid_Dis;
		}
		break;

	case em_GetVid_ViewEp:
		{
			tPaInfo.m_emType = em_PAGetVid_ViewEp;
		}
		break;
	case em_GetVid_OnlyAud:
		{
			tPaInfo.m_emType = em_PAGetVid_OnlyAud;
		}
		break;

	default:
		{
			tPaInfo.m_emType = em_PAGetVid_Invalid;
			MdlError(Ums_Mdl_Stack, ("ConvertGetVidBaseInfoFromUmsToStack Invalid type:%d.\n", tTpInfo.m_emType));
		}
	}
}

void ConvertGetVidInfoFromUmsToStack(const TGetVidInfo& tTpInfo, TPAGetVidInfo& tPaInfo)
{
	ConvertGetVidBaseInfoFromUmsToStack(tTpInfo.m_tBaseInfo, tPaInfo.m_tBaseInfo);

	tPaInfo.m_bSamll = tTpInfo.m_bSamll;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertMediaTransAddrFromUmsToStack(tPaInfo.m_atAudAddr[wIndex], tTpInfo.m_atAudAddr[wIndex]);
		ConvertMediaTransAddrFromUmsToStack(tPaInfo.m_atSmallVid[wIndex], tTpInfo.m_atSmallVid[wIndex]);
		ConvertMediaTransAddrFromUmsToStack(tPaInfo.m_atVidAddr[wIndex], tTpInfo.m_atVidAddr[wIndex]);
	}
	ConvertMediaTransAddrFromUmsToStack(tPaInfo.m_tMixAddr, tTpInfo.m_tMixAddr);
}

void ConvertGetVidResFromUmsToStack(const TGetVidInfoRes& tTpInfo, TPAGetVidInfoRes& tPaInfo)
{
	ConvertGetVidInfoFromUmsToStack(tTpInfo.m_tInfo, tPaInfo.m_tInfo);
	tPaInfo.m_emRes = (EmPAGetVidRes)tTpInfo.m_emRes;
// 	switch (tTpInfo.m_emRes)
// 	{
// 	case em_GetVid_Success:
// 		{
// 			tPaInfo.m_emRes = em_PAGetVid_Success;
// 		}
// 		break;
// 
// 	case em_GitVid_No_Resource:
// 		{
// 			tPaInfo.m_emRes = em_PAGitVid_No_Resource;
// 		}
// 		break;
// 
// 	default:
// 		{
// 			MdlError(Ums_Mdl_Stack, ("ConvertGetVidResFromUmsToStack Invalid res:%d.\n", tTpInfo.m_emRes));
// 		}
// 	}
}

void ConvertGetVidStopResFromUmsToStack(const TStopGetVid& tTpInfo, TPAStopGetVid& tPaInfo)
{
	ConvertGetVidBaseInfoFromUmsToStack(tTpInfo.m_tInfo, tPaInfo.m_tInfo);
	tPaInfo.m_emRes = (EmPAGetVidRes)tTpInfo.m_emRes;
// 	switch (tTpInfo.m_emRes)
// 	{
// 	case em_GetVid_Success:
// 		{
// 			tPaInfo.m_emRes = em_PAGetVid_Success;
// 		}
// 		break;
// 		
// 	case em_GitVid_No_Resource:
// 		{
// 			tPaInfo.m_emRes = em_PAGitVid_No_Resource;
// 		}
// 		break;
// 		
// 	default:
// 		{
// 			MdlError(Ums_Mdl_Stack, ("ConvertGetVidStopResFromUmsToStack Invalid res:%d.\n", tTpInfo.m_emRes));
// 		}
// 	}
}

void ConvertGetVidBaseInfoFromStackToUms(const TPAGetVidBaseInfo& tPaInfo, TGetVidBaseInfo& tTpInfo)
{
	tTpInfo.m_wHandle = tPaInfo.m_wHandle;
	tTpInfo.m_wEpID = tPaInfo.m_wEpID;
	tTpInfo.m_wScreenIndex = tPaInfo.m_wScreenIndex;
	
	switch (tPaInfo.m_emType)
	{
	case em_PAGetVid_View:
		{
			tTpInfo.m_emType = em_GetVid_View;
		}
		break;
		
	case em_PAGetVid_Poll:
		{
			tTpInfo.m_emType = em_GetVid_Poll;
		}
		break;
		
	case em_PAGetVid_Vmp:
		{
			tTpInfo.m_emType = em_GetVid_Vmp;
		}
		break;
		
	case em_PAGetVid_Hdu:
		{
			tTpInfo.m_emType = em_GetVid_Hdu;
		}
		break;
		
	case em_PAGetVid_Dis:
		{
			tTpInfo.m_emType = em_GetVid_Dis;
		}
		break;

	case em_PAGetVid_ViewEp:
		{
			tTpInfo.m_emType = em_GetVid_ViewEp;
		}
		break;
	case em_PAGetVid_OnlyAud:
		{
			tTpInfo.m_emType = em_GetVid_OnlyAud;
		}
		break;
	default:
		{
			tTpInfo.m_emType = em_GetVid_Invalid;
			MdlError(Ums_Mdl_Stack, ("ConvertGetVidBaseInfoFromStackToUms Invalid type:%d.\n", tPaInfo.m_emType));
		}
	}
}
void ConvertGetVidInfoFromStackToUms(const TPAGetVidInfo& tPaInfo, TGetVidInfo& tTpInfo)
{
	ConvertGetVidBaseInfoFromStackToUms(tPaInfo.m_tBaseInfo, tTpInfo.m_tBaseInfo);
	
	tTpInfo.m_bSamll = tPaInfo.m_bSamll;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ConvertMediaTransAddrFromStackToUms(tTpInfo.m_atAudAddr[wIndex], tPaInfo.m_atAudAddr[wIndex]);
		ConvertMediaTransAddrFromStackToUms(tTpInfo.m_atSmallVid[wIndex], tPaInfo.m_atSmallVid[wIndex]);
		ConvertMediaTransAddrFromStackToUms(tTpInfo.m_atVidAddr[wIndex], tPaInfo.m_atVidAddr[wIndex]);
	}
	ConvertMediaTransAddrFromStackToUms(tTpInfo.m_tMixAddr, tPaInfo.m_tMixAddr);
}
void ConvertGetVidResFromStackToUms(const TPAGetVidInfoRes& tPaInfo, TGetVidInfoRes& tTpInfo)
{
	ConvertGetVidInfoFromStackToUms(tPaInfo.m_tInfo, tTpInfo.m_tInfo);
	
	tTpInfo.m_emRes = (EmGetVidRes)tPaInfo.m_emRes;

// 	switch (tPaInfo.m_emRes)
// 	{
// 	case em_PAGetVid_Success:
// 		{
// 			tTpInfo.m_emRes = em_GetVid_Success;
// 		}
// 		break;
// 		
// 	case em_PAGitVid_No_Resource:
// 		{
// 			tTpInfo.m_emRes = em_GitVid_No_Resource;
// 		}
// 		break;
// 		
// 	default:
// 		{
// 			MdlError(Ums_Mdl_Stack, ("ConvertGetVidResFromStackToUms Invalid res:%d.\n", tPaInfo.m_emRes));
// 		}
// 	}
}
void ConvertGetVidStopResFromStackToUms(const TPAStopGetVid& tPaInfo, TStopGetVid& tTpInfo)
{
	ConvertGetVidBaseInfoFromStackToUms(tPaInfo.m_tInfo, tTpInfo.m_tInfo);

	tTpInfo.m_emRes = (EmGetVidRes)tPaInfo.m_emRes;

// 	switch (tPaInfo.m_emRes)
// 	{
// 	case em_PAGetVid_Success:
// 		{
// 			tTpInfo.m_emRes = em_GetVid_Success;
// 		}
// 		break;
// 		
// 	case em_PAGitVid_No_Resource:
// 		{
// 			tTpInfo.m_emRes = em_GitVid_No_Resource;
// 		}
// 		break;
// 		
// 	default:
// 		{
// 			MdlError(Ums_Mdl_Stack, ("ConvertGetVidStopResFromStackToUms Invalid res:%d.\n", tTpInfo.m_emRes));
// 		}
// 	}
}

void ConverStreamKeyFromStackToUms( TPIN const TModuleEncryptKey& tStreamKey, TPOUT TTPEncrypt& tEnc )
{   
	tEnc.Clear();

	if (0 == tStreamKey.m_byLen || emMdlEncryptTypeNone == tStreamKey.m_emEncryptType)
	{
		MdlHint(Ums_Mdl_Stack, ("ConverStreamKeyFromStackToUms, From stack Key is 0, len:%d, type:%d\n", tStreamKey.m_byLen, tStreamKey.m_emEncryptType));
		return;
	}

	// 密钥类型转换
	switch(tStreamKey.m_emEncryptType)
	{
	case emMdlEncryptTypeAES:
		{
			tEnc.m_emEncryptModel = emTPEncryptTypeAES;
		}
		break;
	case emMdlEncryptTypeDES:
		{
			tEnc.m_emEncryptModel = emTPEncryptTypeDES;
		}
		break;
	case emMdlEncryptTypeH239:
		{
			tEnc.m_emEncryptModel = emTPEncryptTypeH239;
		}
		break;
	case emMdlEncryptTypeNone:
		{
			tEnc.m_emEncryptModel = emTPEncryptTypeNone;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("ConverStreamKeyFromStackToUms Invalid Type:%d.\n", tStreamKey.m_emEncryptType));
			return;
		}
	}
	
	// 密钥长度
	tEnc.m_byKeyLen = tStreamKey.m_byLen;//strlen((s8*)tStreamKey.m_abyKey);
	
	// 码流密钥
	memcpy(tEnc.m_achEncKey, (s8*)tStreamKey.m_abyKey, tEnc.m_byKeyLen);
	
	MdlHint(Ums_Mdl_Stack, ("ConverStreamKeyFromStackToUms, from stack(%d, %d, %s), to ums(%d, %d, %s)\n",
		    tStreamKey.m_emEncryptType, tStreamKey.m_byLen, tStreamKey.m_abyKey,
			tEnc.m_emEncryptModel, tEnc.m_byKeyLen, tEnc.m_achEncKey));
	return;
}

void ConverStreamKeyFromUmsToStack( TPIN const TTPEncrypt& tEnc, TPOUT TModuleEncryptKey& tStreamKey )
{
	tStreamKey.Clear();

	if (0 == tEnc.m_byKeyLen || emTPEncryptTypeNone == tEnc.m_emEncryptModel)
	{
		MdlHint(Ums_Mdl_Stack, ("ConverStreamKeyFromUmsToStack, From ums key is 0, len:%d, type:%d\n", tEnc.m_byKeyLen, tEnc.m_emEncryptModel));
		return;
	}

	// 密钥类型转换
	switch(tEnc.m_emEncryptModel)
	{
	case emTPEncryptTypeAES:
		{
			tStreamKey.m_emEncryptType = emMdlEncryptTypeAES;
		}
		break;
	case emTPEncryptTypeDES:
		{
			tStreamKey.m_emEncryptType = emMdlEncryptTypeDES;
		}
		break;
	case emTPEncryptTypeH239:
		{
			tStreamKey.m_emEncryptType = emMdlEncryptTypeH239;
		}
		break;
	case emTPEncryptTypeNone:
		{
			tStreamKey.m_emEncryptType = emMdlEncryptTypeNone;
		}
		break;
	case emTPEncryptTypeQtEverySecond:
	case emTPEncryptTypeQtEveryMinute:
	case emTPEncryptTypeQtEveryConf:
		{
			tStreamKey.m_emEncryptType = emMdlEncryptTypeNone;
		}
		break;
	default:
		{
			tStreamKey.m_emEncryptType = emMdlEncryptTypeNone;
			MdlError(Ums_Mdl_Stack, ("ConverStreamKeyFromUmsToStack Invalid Type:%d.\n", tEnc.m_emEncryptModel));
			return;
		}
	}
	
	// 密钥长度
	tStreamKey.m_byLen = tEnc.m_byKeyLen;
	
	// 码流密钥
	memcpy(tStreamKey.m_abyKey, (u8*)tEnc.m_achEncKey, tStreamKey.m_byLen);
	
	MdlHint(Ums_Mdl_Stack, ("ConverStreamKeyFromUmsToStack, to stack(%d, %d, %s), from ums(%d, %d, %s)\n",
		tStreamKey.m_emEncryptType, tStreamKey.m_byLen, tStreamKey.m_abyKey,
			tEnc.m_emEncryptModel, tEnc.m_byKeyLen, tEnc.m_achEncKey));
	return;
}

void ConvertVersionIDFromStackToUms( const TModuleCallInfo& tModuleInfo, TUmsCallInfo& tCallInfo )
{
	s8* pszVer = (s8*)tModuleInfo.m_achPeerVersionId;
	if (emTPEndpointTypeUMS == tCallInfo.m_emSrcEpType || emTPEndpointTypeCNS == tCallInfo.m_emSrcEpType)
	{//前几个字节为 1.1.1是B1版本， 为1.1.2是B2版本		
		if ( NULL != (strstr(pszVer, "1.1.1")) 
			|| NULL != (strstr(pszVer, "1.1.2"))
			|| NULL != (strstr(pszVer, "1.1.3")) )
		{
			if ( emTPEndpointTypeUMS == tCallInfo.m_emSrcEpType )
			{
				tCallInfo.m_byVer = UMS_B3;
			}
			else
			{
				tCallInfo.m_byVer = CNS_B3;
			}
		}
		else if ( NULL != strstr(pszVer, "1.1.4"))
		{
			if ( emTPEndpointTypeUMS == tCallInfo.m_emSrcEpType )
			{
				tCallInfo.m_byVer = UMS_B4;
			}
			else
			{
				tCallInfo.m_byVer = CNS_B4;
			}
		}
		else
		{//其他的，比如未来版本 1.1.5 也暂定认为是B4
			if ( emTPEndpointTypeUMS == tCallInfo.m_emSrcEpType )
			{
				tCallInfo.m_byVer = UMS_B4;
			}
			else
			{
				tCallInfo.m_byVer = CNS_B4;
			}
		}
	}
	else
	{
		tCallInfo.m_byVer = 0;
	}
	return;
}


/////////////////////////////////////////////////////////
// 电视墙相关

/********CNS to UMS********/
void ConvertHduReqInfoFromStackToUms(const TPAHduPlayReq& tPaReq, TTPHduPlayReq& tReq)
{
	ConvertViewEpTypeFromStackToUms(tPaReq.m_emType, tReq.m_emType);
	tReq.m_wConfID    = tPaReq.m_wConfID;
	tReq.m_wDstID     = tPaReq.m_wDstID;
	//strncpy(tReq.m_achAlias, tPaReq.m_achAlias, sizeof(tReq.m_achAlias));
	tReq.m_wScreenNum = tPaReq.m_wScreenNum;
	tReq.m_wIndex     = tPaReq.m_wIndex;
	tReq.m_bySubIndex = tPaReq.m_bySubIndex;
	tReq.m_bVmp       = tPaReq.m_bVmp;	

	s8* pzAliasGb2312 = NULL;
	utf8_to_gb2312((s8 *)tPaReq.m_achAlias, &pzAliasGb2312);
	memcpy(tReq.m_achAlias, pzAliasGb2312, PA_MAX_ALIAS_LEN);
	tReq.m_achAlias[PA_MAX_ALIAS_LEN-1] = '\0';
	free(pzAliasGb2312);

}

/*****UMS to CNS*****/
void ConvertHduInfoFromUmsToStack(const TPHduBaseInfo& tBaseInfo, TPAHduBaseInfo& tPaBaseInfo)
{
	tPaBaseInfo.m_wIndex     = tBaseInfo.m_wIndex;
	tPaBaseInfo.m_bySubIndex = tBaseInfo.m_bySubIndex;
}

void ConvertHduReasonFromUmsToStack(const EmTpHduPlayNackReason& emReason, EmPAHduPlayNackReason& emPaReason)
{
	switch(emReason)
	{
		case em_hdu_play_success: 
			{
				emPaReason = em_PAhdu_play_success;
			}
			break;
		case em_Hdu_Invalid_Index: 
			{
				emPaReason = em_PAHdu_Invalid_Index;
			}
			break;
		case em_Hdu_Invalid_ID: 
			{
				emPaReason = em_PAHdu_Invalid_ID;
			}
			break;
		case em_Hdu_No_Reged: 
			{
				emPaReason = em_PAHdu_No_Reged;
			}
			break;
		case em_Hdu_Illegal: 
			{
				emPaReason = em_PAHdu_Illegal;
			}
			break;
		case em_Alias_Illegal: 
			{
				emPaReason = em_PAAlias_Illegal;
			}
			break;
		case em_Monitor_Fail: 
			{
				emPaReason = em_PAMonitor_Fail;
			}
			break;
		case em_Hdu_PlayNack: 
			{
				emPaReason = em_PAHdu_PlayNack;
			}
			break;
		case em_Same_Alias: 
			{
				emPaReason = em_PASame_Alias;
			}
			break;
		case em_Same_Info: 
			{
				emPaReason = em_PASame_Info;
			}
			break;
		case em_unknown: 
			{
				emPaReason = em_PAunknown;
			}
			break;
		default:
			{
				MdlError(Ums_Mdl_Stack, (">>>> ConvertHduReasonFromUmsToStack case error reason:%d \n",emReason));
			}
			break;
	}
}

void ConvertHduVolReasonFromUmsToStack(const EmTpHduSetVolRes& emRes, EmPAHduSetVolRes& emPaRes)
{

	switch(emRes)
	{
	case em_hdu_SetVol_Success:
		{
			emPaRes	= em_PAhdu_SetVol_Success;
		}
		break;
	case em_hdu_SetVol_Invalid_Index:
		{
			emPaRes	= em_PAhdu_SetVol_Invalid_Index;
		}
		break;
	case em_hdu_SetVol_UnReg:
		{
			emPaRes	= em_PAhdu_SetVol_UnReg;
		}
		break;
	case em_hdu_SetVol_VmpChan:
		{
			emPaRes	= em_PAhdu_SetVol_VmpChan;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, (">>>> ConvertHduVolReasonFromUmsToStack case error reason:%d \n",emRes));
		}
		break;
	}
}

void ConvertHduModeResFromUmsToStack(const EmTpHduChangeChanModeRes& emRes, EmPAHduChangeChanModeRes& emPaRes)
{
	switch(emRes)
	{
	case em_hdu_change_mode_success:
		{
			emPaRes	= em_PAhdu_change_mode_success;
		}
		break;
	case em_hdu_change_mode_error_index:
		{
			emPaRes	= em_PAhdu_change_mode_error_index;
		}
		break;
	case em_hdu_change_mode_error_param:
		{
			emPaRes	= em_PAhdu_change_mode_error_param;
		}
		break;
	case em_hdu_change_mode_error_regstate:
		{
			emPaRes	= em_PAhdu_change_mode_error_regstate;
		}
		break;
	case em_hdu_change_mode_error_onlyoneVmp:
		{
			emPaRes	= em_PAhdu_change_mode_error_onlyoneVmp;
		}
		break;
	case em_hdu_change_mode_error_workingstate:
		{
			emPaRes	= em_PAhdu_change_mode_error_workingstate;
		}
		break;
	case em_hdu_change_mode_error_fromhdu:
		{
			emPaRes	= em_PAhdu_change_mode_error_fromhdu;
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, (">>>> ConvertHduModeResFromUmsToStack case error reason:%d \n",emRes));
		}
		break;
	}
}

void ConvertHduRunStatusFromUmsToStack(const EmTPHduRunStatus& emTp, EmPAHduRunStatus& emPa )
{
	switch(emTp)
	{
	case emTPHduIdle:
	{
		emPa = emPAHdu_Idle;
	}
	break;
	case emTPHduWaiting:
		{
			emPa = emPAHdu_Waiting;
		}
	break;
	case emTPHduPlaying:
		{
			emPa = emPAHdu_Playing;
		}
	break;
	case emTPHduUnknow:
		{
			emPa = emPAHdu_Unknow;
		}
	break;
	default:
		{
			MdlError(Ums_Mdl_Stack, (">>>> ConvertHduRunStatusFromUmsToStack case error reason:%d \n",emPa));
		}
		break;
	}	
}

void ConvertFeccActFromUmsToStack( const TCamAction& tInfo, TMdlFeccStruct& tMdlInfo )
{
	memset( &tMdlInfo, 0, sizeof(TMdlFeccStruct) );

	switch(tInfo.m_emFeccAct)
	{
	case em_Fecc_CamerStart:
	case em_Fecc_CamerStop:
		{
			if (tInfo.m_emFeccAct == em_Fecc_CamerStart)
			{
				tMdlInfo.m_byAction  = (u8)emModuleactionStart;
				tMdlInfo.m_byTimeout = 0x08; 
			}
			else
			{
				tMdlInfo.m_byAction  = (u8)emModuleactionStop;
			}
			switch(tInfo.m_emCamReq)
			{
			case em_Camer_Up:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestTiltUp;
				break;
			case em_Camer_Down:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestTiltDown;
				break;
			case em_Camer_Left:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestPanLeft;
				break;
			case em_Camer_Right:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestPanRight;
				break;
			case em_Camer_UpLeft:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestTiltUp | (u8)emModulerequestPanLeft;
				break;
			case em_Camer_UpRight:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestTiltUp | (u8)emModulerequestPanRight;
				break;
			case em_Camer_DownLeft:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestTiltDown | (u8)emModulerequestPanLeft;
				break;
			case em_Camer_DownRight:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestTiltDown | (u8)emModulerequestPanRight;
				break;
			case em_Camer_ZoomIN:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestZoomIn;
				break;
			case em_Camer_ZoomOut:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestZoomOut;
				break;
			case em_Camer_FocusIn:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestFocusIn;
				break;
			case em_Camer_FocusOut:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestFocusOut;
				break;
			case em_Camer_BrightUp:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestBrightnessUp;
				break;
			case em_Camer_BrightDown:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestBrightnessDown;
				break;
			case em_Camer_AudoFocus:
				tMdlInfo.m_byAction = (u8)emModuleactionAutoFocus;
				break;
			default:
				tMdlInfo.arguments.m_byRequest = (u8)emModulerequestInvalid;
				break;
			}

		}
		break;
	case em_Fecc_CamerAudoFocus:
		tMdlInfo.m_byAction = (u8)emModuleactionAutoFocus;
		break;
	case em_Fecc_SavePos:
		{
			tMdlInfo.m_byAction = (u8)emModuleactionStoreAsPreset;
			tMdlInfo.arguments.m_byPresetNo = (u8)tInfo.m_dwSaveNo;	
		}
		break;
	case em_Fecc_LoadPos:
		{
			tMdlInfo.m_byAction = (u8)emModuleactionActivatePreset;
			tMdlInfo.arguments.m_byPresetNo = (u8)tInfo.m_dwSaveNo;	
		}
		break;
	case em_Fecc_SwitchVideo:
		{
			tMdlInfo.m_byAction = (u8)emModuleactionVideoSourceSwitched;
			tMdlInfo.arguments.m_bySourceNo = (u8)tInfo.m_dwVidNo;
		}
		break;
	case em_Fecc_SelectVideo:
		{
			tMdlInfo.m_byAction = (u8)emModuleactionSelectVideoSource;
			tMdlInfo.arguments.m_bySourceNo = (u8)tInfo.m_dwVidNo;
		}
		break;
	default:
		MdlError(Ums_Mdl_Stack, ("ConvertFeccActFromUmsToStack unknow mode :%d\n", tInfo.m_emFeccAct));
		break;
	}
}

void ConvertFeccActFromsTackToUms( const TMdlFeccStruct& tMdlInfo, TCamAction& tInfo )
{
	tInfo.Clear();
	
	switch(tMdlInfo.m_byAction)
	{
	case emModuleactionStart:
	case emModuleactionStop:
		{
			if (tMdlInfo.m_byAction == emModuleactionStart)
			{
				tInfo.m_emFeccAct  = em_Fecc_CamerStart;
			}
			else
			{
				tInfo.m_emFeccAct  = em_Fecc_CamerStop;
			}
			switch(tMdlInfo.arguments.m_byRequest)
			{
			case emModulerequestTiltUp:
				tInfo.m_emCamReq = em_Camer_Up;
				break;
			case emModulerequestTiltDown:
				tInfo.m_emCamReq = em_Camer_Down;
				break;
			case emModulerequestPanLeft:
				tInfo.m_emCamReq = em_Camer_Left;
				break;
			case emModulerequestPanRight:
				tInfo.m_emCamReq = em_Camer_Right;
				break;
			case (u8)emModulerequestTiltUp | (u8)emModulerequestPanLeft:
				tInfo.m_emCamReq = em_Camer_UpLeft;
				break;
			case (u8)emModulerequestTiltUp | (u8)emModulerequestPanRight:
				tInfo.m_emCamReq = em_Camer_UpRight;
				break;
			case (u8)emModulerequestTiltDown | (u8)emModulerequestPanLeft:
				tInfo.m_emCamReq = em_Camer_DownLeft;
				break;
			case (u8)emModulerequestTiltDown | (u8)emModulerequestPanRight:
				tInfo.m_emCamReq = em_Camer_DownRight;
				break;
			case emModulerequestZoomIn:
				tInfo.m_emCamReq = em_Camer_ZoomIN;
				break;
			case emModulerequestZoomOut:
				tInfo.m_emCamReq = em_Camer_ZoomOut;
				break;
			case emModulerequestFocusIn:
				tInfo.m_emCamReq = em_Camer_FocusIn;
				break;
			case emModulerequestFocusOut:
				tInfo.m_emCamReq = em_Camer_FocusOut;
				break;
			case emModulerequestBrightnessUp:
				tInfo.m_emCamReq = em_Camer_BrightUp;
				break;
			case emModulerequestBrightnessDown:
				tInfo.m_emCamReq = em_Camer_BrightDown;
				break;
			default:
				tInfo.m_emCamReq = em_Camer_Unknown;
				break;
				
			}
			
		}
		break;
	case emModuleactionAutoFocus:
		{
			tInfo.m_emFeccAct = em_Fecc_CamerAudoFocus;
			tInfo.m_emCamReq  = em_Camer_AudoFocus;
		}
		break;
	case emModuleactionStoreAsPreset:
		{
			tInfo.m_emFeccAct = em_Fecc_SavePos;
			tInfo.m_dwSaveNo  = tMdlInfo.arguments.m_byPresetNo;
		}
		break;
	case emModuleactionActivatePreset:
		{
			tInfo.m_emFeccAct = em_Fecc_LoadPos;
			tInfo.m_dwSaveNo  = tMdlInfo.arguments.m_byPresetNo;
		}
		break;
	case emModuleactionVideoSourceSwitched:
		{
			tInfo.m_emFeccAct = em_Fecc_SwitchVideo;
			tInfo.m_dwVidNo  = tMdlInfo.arguments.m_bySourceNo;
		}
		break;
	case emModuleactionSelectVideoSource:
		{
			tInfo.m_emFeccAct = em_Fecc_SelectVideo;
			tInfo.m_dwVidNo  = tMdlInfo.arguments.m_bySourceNo;
		}
		break;
	default:
		MdlError(Ums_Mdl_Stack, ("ConvertFeccActFromStackToUms unknow mode :%d\n", tMdlInfo.m_byAction));
		break;
	}
}

// fecc 查找空闲可用端口使用 其他业务尽量不要使用
// fecc端口使用范围 60030 ~~ 62078
BOOL32 GetFeccUsablePort( u16& wUsablePort)
{

	static u16 wEpIndex = UMS_FECC_BEGIN_PORT;
				
	u16 wForNum = 0;
	u16 wIndex = wEpIndex;
	do 
	{
		if ( wForNum >= 2 )
		{
			break ;
		}
		//依次往下找
		if ( wIndex >= UMS_FECC_END_PORT )
		{
			wForNum ++;
			wIndex = UMS_FECC_BEGIN_PORT;
		}
					
		if(CTpTypeAdpt::PortIsVaild(wIndex))
		{
			wEpIndex = wIndex + 1;
			wUsablePort = wIndex;
			return TRUE;
		}
					
		wIndex ++;
					
	} while (TRUE);


	return FALSE;
}

void ConvertFeccConfInfoFromUmsToStack( const TConfVidFeccInfo& tInfo, TPAConfVidFeccInfo& tMdlInfo )
{
	ConvertOpTypeFromUmsToStack(tInfo.m_emOpr, tMdlInfo.m_emOpr);
	tMdlInfo.m_bLastPack	= tInfo.m_bLastPack;
	tMdlInfo.m_wConfID		= tInfo.m_wConfID;
	tMdlInfo.m_wNum			= min(tInfo.m_wNum, PA_REFRESH_LIST_THREE);
	for(u16 wIndex = 0; wIndex < tMdlInfo.m_wNum; ++wIndex)
	{
		ConvertFeccInfoFromUmsToStack(tInfo.m_atVidFeccList[wIndex], tMdlInfo.m_atVidFeccList[wIndex]);
	}
}

void ConvertFeccConfEpListFromUmsToStack( const TConfEpVidFeccList&	tInfo, TPAConfEpVidFeccList& tMdlInfo )
{
	tMdlInfo.m_wNum = min(tInfo.m_wNum, PA_REFRESH_LIST_THREE);
	
	for(u16 wIndex = 0; wIndex < tMdlInfo.m_wNum; ++wIndex)
	{
		ConvertEpKeyPathFromUmsToStack(tInfo.m_atList[wIndex].m_tID, tMdlInfo.m_atList[wIndex].m_tID);
		ConvertFeccInfoFromUmsToStack(tInfo.m_atList[wIndex].m_tVidFeccInfo, tMdlInfo.m_atList[wIndex].m_tVidFeccInfo);
	}

}

void ConvertFeccInfoFromUmsToStack( const TVidFeccInfo& tInfo, TPAVidFeccInfo& tMdlInfo )
{
	tMdlInfo.m_wEpID		= tInfo.m_wEpID;
	tMdlInfo.m_bAllowFecc	= tInfo.m_bAllowFecc;
	tMdlInfo.m_byVidno		= tInfo.m_byVidno;
	ConvertFeccSourceFromUmsToStack(tInfo.m_tVidSourceInfo, tMdlInfo.m_tVidSourceInfo);
}

void ConvertFeccSourceFromUmsToStack( const TVidSourceInfo& tInfo, TPAVidSourceInfo& tMdlInfo )
{
	tMdlInfo.m_byNum = min(tInfo.m_byNum, UMS_PA_MAX_VID_SOURCE_NUM);
	s8 *pzAliasUTF8 = NULL;
	for(u16 wIndex = 0; wIndex < tMdlInfo.m_byNum; ++wIndex)
	{
		tMdlInfo.m_atVidInfo[wIndex].m_byIndex = tInfo.m_atVidInfo[wIndex].m_byIndex;
		memcpy(tMdlInfo.m_atVidInfo[wIndex].m_abyAlias, tInfo.m_atVidInfo[wIndex].m_abyAlias, 
				sizeof(tInfo.m_atVidInfo[wIndex].m_abyAlias));
		gb2312_to_utf8((s8 *)tMdlInfo.m_atVidInfo[wIndex].m_abyAlias, &pzAliasUTF8);
		strncpy((s8 *)tMdlInfo.m_atVidInfo[wIndex].m_abyAlias, pzAliasUTF8, UMS_PA_MAX_VID_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
	}
}

void ConvertFeccConfEpListFromStackToUms( const TPAConfEpVidFeccList& tMdlInfo, TConfEpVidFeccList& tInfo )
{
	tInfo.m_wNum = min(tMdlInfo.m_wNum, TP_REFRESH_LIST_THREE);
	
	for(u16 wIndex = 0; wIndex < tMdlInfo.m_wNum; ++wIndex)
	{
		strncpy(tInfo.m_atList[wIndex].m_tID.m_szEpID, tMdlInfo.m_atList[wIndex].m_tID.m_achEpID,
					TP_MAX_EPID_LEN);
		ConvertFeccInfoFromStackToUms(tMdlInfo.m_atList[wIndex].m_tVidFeccInfo, tInfo.m_atList[wIndex].m_tVidFeccInfo);
	}
}

void ConvertFeccInfoFromStackToUms( const TPAVidFeccInfo& tMdlInfo, TVidFeccInfo& tInfo )
{
	tInfo.m_wEpID		= tMdlInfo.m_wEpID;
	tInfo.m_bAllowFecc	= tMdlInfo.m_bAllowFecc;
	tInfo.m_byVidno		= tMdlInfo.m_byVidno;

	tInfo.m_tVidSourceInfo.m_byNum = min(tMdlInfo.m_tVidSourceInfo.m_byNum, UMS_MAX_VID_SOURCE_NUM);
	
	s8 *pzAliasUTF8 = NULL;
	for(u16 wIndex = 0; wIndex < tInfo.m_tVidSourceInfo.m_byNum; ++wIndex)
	{
		tInfo.m_tVidSourceInfo.m_atVidInfo[wIndex].m_byIndex = tMdlInfo.m_tVidSourceInfo.m_atVidInfo[wIndex].m_byIndex;
	
		memcpy(tInfo.m_tVidSourceInfo.m_atVidInfo[wIndex].m_abyAlias, tMdlInfo.m_tVidSourceInfo.m_atVidInfo[wIndex].m_abyAlias, 
			sizeof(tMdlInfo.m_tVidSourceInfo.m_atVidInfo[wIndex].m_abyAlias));
		utf8_to_gb2312((s8 *)tInfo.m_tVidSourceInfo.m_atVidInfo[wIndex].m_abyAlias, &pzAliasUTF8);
		strncpy((s8 *)tInfo.m_tVidSourceInfo.m_atVidInfo[wIndex].m_abyAlias, pzAliasUTF8, UMS_MAX_VID_ALIAS_LEN);
		free(pzAliasUTF8);
		pzAliasUTF8 = NULL;
	}
	
}


//////////////qt//////////////////

void ConvertQTEncryptLevelFromUmsToStack( TPIN const EmTPConfEncFrequency &emTPEncLevel, TPOUT EmQtKeyFrequency &emPaEncLevel )
{
	switch(emTPEncLevel)
	{
	case emTPConfEncFrequencyEveryConf:
		{
			emPaEncLevel = EmQtFrequencyEveryConf;
			break;
		}
	case emTPConfEncFrequencyEveryMinute:
		{
			emPaEncLevel = EmQtFrequencyEveryMinutes;
			break;
		}
	case emTPConfEncFrequencyEverySeconds:
		{
			emPaEncLevel = EmQtFrequencyEverySeconds;
			break;
		}
	default:
		break;
	}

	MdlHint( Ums_Mdl_Call, ("[ConvertQTEncryptTypeFromUmsToStack] emTPEncLevel->%d, emPaEncLevel->%d\n",
		emTPEncLevel, emPaEncLevel) );
}

void ConvertQTEncryptLevelFromStackToUms( TPIN const EmQtKeyFrequency &emPaEncLevel, TPOUT EmTPConfEncFrequency &emTPEncLevel )
{
	switch(emPaEncLevel)
	{
	case EmQtFrequencyEveryConf:
		{
			emTPEncLevel = emTPConfEncFrequencyEveryConf;
			break;
		}
	case EmQtFrequencyEveryMinutes:
		{
			emTPEncLevel = emTPConfEncFrequencyEveryMinute;
			break;
		}
	case EmQtFrequencyEverySeconds:
		{
			emTPEncLevel = emTPConfEncFrequencyEverySeconds;
			break;
		}
	default:
		break;
	}

	MdlHint( Ums_Mdl_Call, ("[ConvertQTEncryptLevelFromStackToUms] emTPEncLevel->%d, emPaEncLevel->%d\n",
		emTPEncLevel, emPaEncLevel) );
}

void ConvertQtAliasTypeFromTpToStack(TPIN const EmTpAliasType &emAliasType, TPOUT EmQtAliasType &emQtAliasType )
{
	switch(emAliasType)
	{
	case tp_Alias_h323:
		{
			emQtAliasType = EmQtAliasType_Alias;
			break;
		}
	case tp_Alias_e164:
		{
			emQtAliasType = EmQtAliasType_E164;
			break;
		}
	default:
		break;
	}
}

void ConvertRegTypeFromUmsToStack(TPIN const EmTpConfProtocol &emProType, TPOUT EmPAConfProtocol &emPAType)
{
	switch(emProType)
	{
	case emTpH323:
		{
			emPAType = emPATypeH323;
			break;
		}
	case emTpSIP:
		{
			emPAType = emPATypeSip;
			break;
		}
	case emTpAllProc:
		{
			emPAType = emPATypeAll;
			break;
		}
	default:break;
	}

	MdlHint(Ums_Mdl_Call,("ConvertRegTypeFromUmsToStack emProType->%d, emPAType->%d\n",
		emProType, emPAType));
}

void ConvertEpEncryptLevelFromUmsToStack( TPIN const EmTPConfEncFrequency &emTPEncLevel, TPOUT EmPAConfEncFrequency &emPaEncLevel )
{
	switch(emTPEncLevel)
	{
	case emTPConfEncFrequencyEverySeconds:
		{
			emPaEncLevel = emPAConfEncFrequencyEverySeconds;
			break;
		}
	case emTPConfEncFrequencyEveryMinute:
		{
			emPaEncLevel = emPAConfEncFrequencyEveryMinute;
			break;
		}
	case emTPConfEncFrequencyEveryConf:
		{
			emPaEncLevel = emPAConfEncFrequencyEveryConf;
			break;
		}
	default:
		break;
	}
	
	MdlHint( Ums_Mdl_Call, ("[ConvertEpEncryptLevelFromUmsToStack] emTPEncLevel->%d, emPaEncLevel->%d\n",
		emTPEncLevel, emPaEncLevel) );
}

void ConvertEpEncryptLevelFromStackToUms( TPIN const EmPAConfEncFrequency &emPaEncLevel, TPOUT EmTPConfEncFrequency &emTPEncLevel )
{

	switch(emPaEncLevel)
	{
	case emPAConfEncFrequencyEverySeconds:
		{
			emTPEncLevel = emTPConfEncFrequencyEverySeconds;
			break;
		}
	case emPAConfEncFrequencyEveryMinute:
		{
			emTPEncLevel = emTPConfEncFrequencyEveryMinute;
			break;
		}
	case emPAConfEncFrequencyEveryConf:
		{
			emTPEncLevel = emTPConfEncFrequencyEveryConf;
			break;
		}
	default:
		break;
	}
	MdlHint( Ums_Mdl_Call, ("[ConvertEpEncryptLevelFromStackToUms] emPaEncLevel->%d, emTPEncLevel->%d\n",
		emPaEncLevel, emTPEncLevel) );
}

void ConvertEpEncryptTypeFromStackToUms( TPIN const EmPAConfEncFrequency &emPaEncLevel, TPOUT EmTPEncryptType &emTPEncType )
{
	switch(emPaEncLevel)
	{
	case emPAConfEncFrequencyEverySeconds:
		{
			emTPEncType = emTPEncryptTypeQtEverySecond;
			break;
		}
	case emPAConfEncFrequencyEveryMinute:
		{
			emTPEncType = emTPEncryptTypeQtEveryMinute;
			break;
		}
	case emPAConfEncFrequencyEveryConf:
		{
			emTPEncType = emTPEncryptTypeQtEveryConf;
			break;
		}
	default:
		break;
	}
	MdlHint( Ums_Mdl_Call, ("[ConvertEpEncryptTypeFromStackToUms] emPaEncLevel->%d, emTPEncLevel->%d\n",
		emPaEncLevel, emTPEncType) );
}

void ConvertEpEncryptTypeFromStackToUms( TPIN const EmQtKeyFrequency &emPaEncLevel, TPOUT EmTPEncryptType &emTPEncType )
{
	switch(emPaEncLevel)
	{
	case EmQtFrequencyEverySeconds:
		{
			emTPEncType = emTPEncryptTypeQtEverySecond;
			break;
		}
	case EmQtFrequencyEveryMinutes:
		{
			emTPEncType = emTPEncryptTypeQtEveryMinute;
			break;
		}
	case EmQtFrequencyEveryConf:
		{
			emTPEncType = emTPEncryptTypeQtEveryConf;
			break;
		}
	default:
		break;
	}
	MdlHint( Ums_Mdl_Call, ("[ConvertEpEncryptTypeFromStackToUms] emPaEncLevel->%d, emTPEncLevel->%d\n",
		emPaEncLevel, emTPEncType) );
}

//////////////qt end//////////////////
