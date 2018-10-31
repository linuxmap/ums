#include "umsstackinterface.h"
#include "innereventumscall.h"
#include "innereventumsconf.h"
#include "eventoutsipadapter.h"
#include "eventoutumsmcucasecade.h"
#include "tpmsg.h"
#include "umsobject.h"
#include "umsdataconvet.h"
#include "innereventregsrv.h"
#include "innereventumssipadapter.h"
#include "umsxmltype.h"
#include "eventoutumsselview.h"
#include "eventoutumsbrdvmp.h"
#include "eventoutumscall.h"
#include "umssipmcudef.h"
#include "umsapi.h"

#include "pastruct.h"
#include "protocoladapter.h"
#include "kdvcascade.h"

#include "umsapi.h"
#include "lanman.h"

#include "eventoutquantum.h"
//Protocol_file
#include "qtinterface.h"

#include "adaptercfg.h"

#include <map>

extern u32 g_dwUmsNode;
extern TUmsStackCallCfg g_tUMSStackCfg;

extern TTPQTEncryptInfo g_tTPQTEncryptInfo;
extern BOOL32 g_bKedaManuOn;

extern u32 g_dwListenIp;

typedef struct tagTCallMapInfo
{
	u32			m_dwAppCall;
	BOOL32		m_bIsMasterCall;
	BOOL32		m_bIsSip;

	BOOL32						m_bCallConnect;
	BOOL32						m_bKedaPID;
	u32							m_dwPaCall;
	EmTPEndpointType			m_emEpType;
	s8							m_acPrdutID[TP_UMS_PRDUT_ID+1];

	tagTCallMapInfo()
	{
		m_dwAppCall =0;
		m_bIsMasterCall = TRUE;
		m_bIsSip = TRUE;

		m_bCallConnect = FALSE;
		m_bKedaPID = FALSE;
		m_dwPaCall = 0;
		m_emEpType = emTPEndpointTypeUnknown;
		memset(m_acPrdutID, 0, sizeof(m_acPrdutID));
	}

	tagTCallMapInfo& operator = (const tagTCallMapInfo& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_dwAppCall = tRhs.m_dwAppCall;
		this->m_bIsMasterCall = tRhs.m_bIsMasterCall;
		this->m_bIsSip = tRhs.m_bIsSip;

		

		this->m_bCallConnect = tRhs.m_bCallConnect;
		this->m_bKedaPID = tRhs.m_bKedaPID;
		this->m_dwPaCall = tRhs.m_dwPaCall;
		this->m_emEpType = tRhs.m_emEpType;
		memcpy(this->m_acPrdutID, tRhs.m_acPrdutID, sizeof(tRhs.m_acPrdutID));

		return *this;
	}

	BOOL32 IsKedaVendor()
	{
		return m_bKedaPID;
	}

}TCallMapInfo;

std::map<u32, TCallMapInfo>	g_mapCallMapInfo;
SEMHANDLE					g_hSemCallMap = NULL;

s8 g_abyKedaPid[43][32]= {"H900_TP","H850_TP","H800_TP","H600_TP","H700_TP","Kdv7920_A","Kdv7920_B","Kdv7820_A","Kdv7820_B","Kdv7921_L","Kdv7921_H","H600_LB",\
	"H600_LC","H600_B","H600_C","H700_A","H700_B","H700_C","H800_A","H800_B","H800_C","H850_A","H850_B",\
	"H850_C","H900_A","H900_B","H900_C","H600_L_TP","Kdv8010","Kdvpcmt","ts5210","v5","ts3210","ts6610e","ts6210","Kdv7210","Kdv7610","Kdv6610","Kdv5610","KDC MCU","KDC MCU-8000C","CNSTPS","KDC MCGATEWAY"};

static BOOL32 IsKedaPid(s8* szPid)
{
	if (NULL == szPid || 0 == sizeof(szPid))
	{
		return FALSE;
	}

	for (u16 wLoop = 0; wLoop < 43; wLoop++)
	{
		if (strcmp(g_abyKedaPid[wLoop], szPid) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}

API void showcallinfo()
{
	u16 wIndex = 0;
	std::map<u32, TCallMapInfo>::iterator it;
	TUmsHandle tHandle;
	msgprintnotime("[g_mapCallMapInfo]\n");
	for (it = g_mapCallMapInfo.begin(); it != g_mapCallMapInfo.end(); it++)
	{
		wIndex++;
		tHandle.handAppCall = it->first;
		msgprintnotime("  [%d] AppHandle:%u(%d-%d), IsMaster:%d, IsSip:%d, CallConnect:%d, bKeda:%d, PaCall:%u, EpType:%d, Pid:%s.\n",
			wIndex, tHandle.handAppCall, tHandle.GetConfID(), tHandle.GetEpID(), it->second.m_bIsMasterCall, 
			it->second.m_bIsSip, it->second.m_bCallConnect, it->second.m_bKedaPID,
			it->second.m_dwPaCall, it->second.m_emEpType, it->second.m_acPrdutID);
	}
	msgprintnotime("\n");
	msgprintnotime("[g_abyKedaPid]\n");
	u16 wLoopNum = 0;
	for (wIndex = 0; wIndex < 43; wIndex++)
	{
		msgprintnotime("%d-[%s] ", wIndex, g_abyKedaPid[wIndex]);
		wLoopNum++;
		if (wLoopNum == 5)
		{
			wLoopNum = 0;
			msgprintnotime("\n");
		}
	}
	return;
}


//in
static void NotifyMsgToCall(u16 wEvent, TUmsHandle& tHandle, void* pBuf, u16 wSize)
{
	CTpMsg cMsg;	
	tHandle.m_dwAdapteID = g_tUMSStackCfg.m_dwUmsNode;
	cMsg.SetEvent(wEvent);
	cMsg.SetHomeplace(node_peer);
	cMsg.SetBody(&tHandle, sizeof(tHandle));
	if (NULL != pBuf)
	{
		cMsg.CatBody(pBuf, wSize);
	}
	cMsg.Post(MAKEIID(AID_UMSCONFMGR, CInstance::DAEMON), g_dwUmsNode, UMS_SIPADAPTER_APP_INST);
}


static BOOL UnRegResult(EmPAConfProtocol emPAType, HMDLREG hReg, HMDLAPPREG hAppReg, u8 *pBuf, s32 nLen)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppReg;
	tHandle.handPaCall = (u32)hReg;

	TUCSipRegResult tSipRegResult;
	memset(&tSipRegResult,0,sizeof(TUCSipRegResult));

	EmPARegFailedReason emRegFailedReason = emPAUnknownReason;
	do 
	{
		if(NULL == pBuf)
		{
			MdlError(Ums_Mdl_Stack, ("<< UnRegResult  Buffer is NULL. emPAType:%d\n", emPAType));
			tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_Unknow;
			break;
		}
		
		TP_SAFE_CAST(emRegFailedReason, pBuf);
		switch(emRegFailedReason)
		{
		case emPAUnknownReason:
			{
				tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_Unknow;
			}
			break;
		
		case emPARegistrarUnReachable:
			{
				tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_Unreachable;
			}
			break;
		
		case emPARegisterFailed:
			{
				tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_Fail;
			}
			break;
		
		case emPARegisterNameDup:
			{
				tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_AliasRepeat;
				
				u8* pDupBuf = pBuf + sizeof(EmPARegFailedReason);
				s32 nDupBufSize = nLen - sizeof(EmPARegFailedReason);
				if (nDupBufSize < sizeof(s32))
				{
					MdlError(Ums_Mdl_Stack, ("UnRegResult alias repeat. emPAType:%d, app:%d, nLen:%d\n", emPAType, tHandle.handAppCall, nLen));
					break;
				}

				s32 nRepeatNum;
				TP_SAFE_CAST(nRepeatNum, pDupBuf);

				if (nRepeatNum > TP_CONFTEMPGROUP_MAXNUM || nDupBufSize - sizeof(s32) < s32(nRepeatNum * sizeof(TPARegName)) )
				{
					MdlError(Ums_Mdl_Stack, ("UnRegResult alias num failed. app:%d, nRepeatNum:%d, nDupBufSize:%d, perSize:%d\n"
						, tHandle.handAppCall, nRepeatNum, nDupBufSize, sizeof(TPARegName)));
					break;
				}
				pDupBuf += sizeof(nRepeatNum);

				tSipRegResult.m_nAliasNum = nRepeatNum;	
				
				TPARegName atTPRegName;
				for( s32 nIndex = 0; nIndex < nRepeatNum; nIndex++ )
				{
					memcpy(&atTPRegName,pDupBuf,sizeof(TPARegName));
					
					switch(atTPRegName.m_emPAAddrType)
					{
					case emPAAlias:
						{
							tSipRegResult.m_atTPAlias[nIndex].m_byType = tp_Alias_h323;
							break;
						}
						
					case emPAE164Num:
						{
							tSipRegResult.m_atTPAlias[nIndex].m_byType = tp_Alias_e164;
							break;
						}
						
					default:
						{
							MdlError(Ums_Mdl_Stack, ("UnRegResult Unknow addr type:%d, nRepeatNum:%d, curIndex:%d\n", atTPRegName.m_emPAAddrType, nRepeatNum, nIndex));

							tSipRegResult.m_nAliasNum = 0;
							return TRUE;
						}
						
					}
					
					s8 *pzAliasUTF8 = NULL;					
					utf8_to_gb2312((s8 *)atTPRegName.m_achUserName, &pzAliasUTF8);
					strncpy(tSipRegResult.m_atTPAlias[nIndex].m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
					free(pzAliasUTF8);

					pDupBuf += sizeof(TPARegName);
				}//for
			}// case emPARegisterNameDup
			break;
		
		default:
			{
				MdlError(Ums_Mdl_Stack, ("<< UnRegResult  unkown reson :%d\n", emRegFailedReason));
				tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_Unknow;
			}
			break;
		}
	
	} while (0);
	
	MdlHint(Ums_Mdl_Stack, ("<< UnRegResult  nAppId:0x%x,Reason: %d, protocol: %d\n", 
							tHandle.handAppCall, emRegFailedReason, emPAType));

	if (emPATypeH323 == emPAType)
	{
		NotifyMsgToCall(evtp_ums_323_unreg_ret, tHandle, &tSipRegResult, sizeof(TUCSipRegResult));
	}
	else
	{
		NotifyMsgToCall(evtp_ums_unreg_ret, tHandle, &tSipRegResult, sizeof(TUCSipRegResult));
	}
	return TRUE;
}

BOOL PA_CALLBACK UmsCBRegistResult(EmPAConfProtocol emPAType, HMDLREG hReg, HMDLAPPREG hAppReg, BOOL32 bRegistered,
								   u8 *pAppendData, u16 wAppendDataLen )
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppReg;
	tHandle.handPaCall = (u32)hReg;
	
	MdlHint(Ums_Mdl_Stack, ("<< UmsCBRegistResult  nAppId:0x%x, pRegHandle:0x%x, protocol:%d, RegRes:%d\n", 
							tHandle.handAppCall, tHandle.handPaCall, emPAType, bRegistered));
	
	TCnsRegRetResult tRetInfo;
	switch (emPAType)
	{
	case emPATypeH323:
		{
			tRetInfo.m_emRegType = em_323_reg;
			break;
		}

	case emPATypeSip:
		{
			tRetInfo.m_emRegType = em_sip_reg;
			break;
		}
	}

	if (bRegistered)
	{
		tRetInfo.m_emReson = tp_CnsRegRet_Success;
		NotifyMsgToCall(evtp_ums_reg_ret, tHandle, &tRetInfo, sizeof(tRetInfo));
		return TRUE;
	}
	else
	{
		return UnRegResult(emPAType, hReg, hAppReg, pAppendData, wAppendDataLen);
	}
}


BOOL PA_CALLBACK UmsCBCallConnected(HMDLCALL hPACall, HMDLAPPCALL hAppCall, TModuleCallInfo *ptCallInfo, 
									  TCallInfoTP     *ptCallTP, 	EmPAConfProtocol emPAType)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
		
	TUmsCallInfo tCallInfo;
	BOOL32 bHangUp = FALSE;
	if (NULL != ptCallInfo)
	{
		ConvertMdlVendorFromStackToUms(ptCallInfo->m_emPeerVendorId, tCallInfo.m_emVendorID);

		if (emPATypeSip == emPAType)
		{
			ConvertCallInfoFromStackToUms(*ptCallInfo, tCallInfo, bHangUp);
		}
		else
		{
			ConvertCallInfoFromStackToUmsForH323(*ptCallInfo, tCallInfo);
			if (g_bKedaManuOn)
			{
				TKedaManuProductTP tKedaManuPro;
				MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::emModuleKedaManuProduct post to ....\n"));
				PA_SendConfCtrl(HMDLCALL(tHandle.handPaCall), (HMDLAPPCALL)tHandle.handAppCall, emModuleKedaManuProduct, (u8*)&tKedaManuPro, sizeof(tKedaManuPro));
			}
		}

		if (bHangUp)
		{
			MdlError(Ums_Mdl_Stack, ("<< UmsCBCallConnected this ep not ManuProduct, HangUp by Local! ConfID:%d, epID:%d, PACall:%d.\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
			PA_HangupCall((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, emModuleDisconnect_Normal);
			return TRUE;
		}
	}

	ConverStreamKeyFromStackToUms(ptCallInfo->m_tStreamKey, tCallInfo.m_tEncrypt);
	if ( ptCallInfo->m_bSignalEncrypt )
	{
		ConvertEpEncryptTypeFromStackToUms(ptCallInfo->m_tQtCallParam.m_emKeyFrequency, tCallInfo.m_tEncrypt.m_emEncryptModel);
	}

	if (NULL != ptCallTP)
	{
		ConvertSipLevelFromStackToUms(ptCallTP->m_emSipLevel, tCallInfo.m_emLevel);
	}

	ConvertProtocolFromPaToTp(emPAType, tCallInfo.m_emTpProtocol);

	MdlHint(Ums_Mdl_Stack, ("<< UmsCBCallConnected ConfID:%d, epID:%d, PACall:%d,dst:%s, src:%s, Type:%d, EndpointType:%d, PeerEndpointType:%d, BitRate:%d, PAType:%d, QtCallEncry:%d.\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias
			, tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias, tCallInfo.m_emSrcEpType, ptCallInfo->m_emEndpointType, ptCallInfo->m_emPeerEndpointType
			, tCallInfo.m_wBitRate, tCallInfo.m_emTpProtocol, tCallInfo.m_tEncrypt.IsQt()
			));
	
	MdlHint(Ums_Mdl_Stack, ("  << UmsCBCallConnected LocalProductId:%s, LocalVersionId:%s, PeerProductId:%s, PeerVersionId:%s.\n", ptCallInfo->m_achLocalProductId, ptCallInfo->m_achLocalVersionId,
		ptCallInfo->m_achPeerProductId, ptCallInfo->m_achPeerVersionId));
	
	NotifyMsgToCall(evtp_Conf_UmsCallConnect, tHandle, &tCallInfo, sizeof(tCallInfo));

	TCallMapInfo	tMapInfo;
	if (0 != tHandle.handAppCall)
	{
		OspSemTake(g_hSemCallMap);
		std::map<u32, TCallMapInfo>::iterator it = g_mapCallMapInfo.find(tHandle.handAppCall);
		if (it != g_mapCallMapInfo.end())
		{
			tMapInfo = it->second;

			tMapInfo.m_bCallConnect = TRUE;
			tMapInfo.m_dwPaCall = tHandle.handPaCall;
			tMapInfo.m_emEpType = tCallInfo.m_emSrcEpType;
			memcpy(tMapInfo.m_acPrdutID, tCallInfo.m_acPrdutID, sizeof(tCallInfo.m_acPrdutID));
			
			tMapInfo.m_bKedaPID = IsKedaPid(tMapInfo.m_acPrdutID);

			g_mapCallMapInfo[tHandle.handAppCall] = tMapInfo;
		}
		OspSemGive(g_hSemCallMap);
	}

	return TRUE;
}

BOOL PA_CALLBACK UmsCBCallDisconnected(HMDLCALL hPACall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason)
{
	
	TUmsHandle tHandle;

	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
		
	EmCnsCallReason emAppReason;
	ConvertModuleDisReasonFromStackToUms(emReason, emAppReason);
		
	MdlHint(Ums_Mdl_Stack, ("<< UmsCBCallDisconnected ConfID:%d, epID:%d, PACall:%d, PAReason:%d, umsReason(%d-%s)\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, emReason, TpEnumIdString(EmCnsCallReason, emAppReason)));
		
	NotifyMsgToCall(evtp_Conf_UmsCallDisConnect, tHandle, &emAppReason, sizeof(emAppReason));

	if (0 != tHandle.handAppCall)
	{
		OspSemTake(g_hSemCallMap);
		g_mapCallMapInfo.erase(tHandle.handAppCall);
		OspSemGive(g_hSemCallMap);
	}

	return TRUE;
}

// BOOL PA_CALLBACK UmsCBNewCallIncomingNew(EmPAConfProtocol emPAType,
// 										 HMDLCALL         hPACall, 
// 										 TModuleCallInfo *ptCallInfo, 
// 										 TMdlCallCap *ptMainCap,
// 										 TMdlTPCap *ptTPCap,  
// 										 TDualCapList *ptDualCap,
// 										 TBfcpCapSet *ptBfcpCap, 
// 										 TFeccCapbility *ptFeccCap)
// {
// 	u8 abyBuf[sizeof(TUmsCallInfo) + sizeof(TTPConfTemplate)];
// 	TUmsCallInfo tCallInfo;
// 	TTPConfTemplate* ptConfTemp = (TTPConfTemplate*)(abyBuf + sizeof(TUmsCallInfo));
// 
// 	TUmsHandle tHandle;
// 	tHandle.handAppCall = 0;
// 	tHandle.handPaCall = (u32)hPACall;
// 	
// 	tCallInfo.Clear();
// 	ptConfTemp->Clear();
// 	
// 	if (NULL != ptCallInfo)
// 	{
// 		if (emPATypeSip == emPAType)
// 		{
// 			ConvertCallInfoFromStackToUms(*ptCallInfo, tCallInfo);
// 		}
// 		else
// 		{
// 			ConvertCallInfoFromStackToUmsForH323(*ptCallInfo, tCallInfo);
// 		}
// 		
// 		if (ptCallInfo->m_bCreateConf)
// 		{
// 			ConvertCreatConfInfoFromStackToUms(*ptCallInfo, *ptConfTemp);
// 			CheckCallerIsInConfList(*ptConfTemp, *ptCallInfo, tCallInfo);
// 		}	
// 	}
// 
// 	if (NULL != ptTPCap)
// 	{
// 		ConvertSipLevelFromStackToUms(ptTPCap->m_tCallInfoTP.m_emSipLevel, tCallInfo.m_emLevel);
// 	}
// 
// 	ConvertProtocolFromPaToTp(emPAType, tCallInfo.m_emTpProtocol);
// 
// 	MdlHint(Ums_Mdl_Stack, ("<< UmsCBNewCallIncomingNew PACall:%d, dst:%s, src:%s, EPType:%d, CallType:%d, Incoming CallBitRate = %d, PAType:%d\n",
// 		tHandle.handPaCall, tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias,
// 			tCallInfo.m_emSrcEpType, tCallInfo.m_emTpCallType, tCallInfo.m_wBitRate, tCallInfo.m_emTpProtocol));
// 
// 	memcpy(abyBuf, &tCallInfo, sizeof(TUmsCallInfo));
// 	memcpy(abyBuf + sizeof(TUmsCallInfo), ptConfTemp, sizeof(TTPConfTemplate));
// 	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_CallIncoming, abyBuf, tHandle, INSIGN);
// 
// 	if (NULL != ptCallInfo)
// 	{
// 		if (ptCallInfo->m_bCreateConf)
// 		{
// 			MdlLowHint(Ums_Mdl_Stack, ("<< evtp_UmsConfCreateMeeting.\n"));
// 			NotifyMsgToCall(evtp_UmsConfCreateMeeting, tHandle, abyBuf, sizeof(abyBuf));
// 		}
// 		else
// 		{
// 			MdlLowHint(Ums_Mdl_Stack, ("<< evtp_UmsConfIncoming.\n"));
// 			NotifyMsgToCall(evtp_UmsConfIncoming, tHandle, &tCallInfo, sizeof(tCallInfo));
// 		}
// 	}
// 
// 	return TRUE;
// }

BOOL PA_CALLBACK UmsCBNewCallIncoming(EmPAConfProtocol emPAType, HMDLCALL hPACall, TModuleCallInfo* ptCallInfo,
										TCallCapbility* ptSndCap, TCallCapbility* ptRcvCap,TCallInfoTP* ptCallTP, 
										TCallDescriptTP* ptSndTP, TCallDescriptTP* ptRcvTP,
										TDualCapList *ptDualCap, TBfcpCapSet *ptBfcpCap, TFeccCapbility *ptFeccCap)
{
	u8 abyBuf[sizeof(TUmsCallInfo) + sizeof(TTPConfTemplate)];
	TUmsCallInfo tCallInfo;
	TTPConfTemplate* ptConfTemp = (TTPConfTemplate*)(abyBuf + sizeof(TUmsCallInfo));
	TUmsHandle tHandle;
	tHandle.handAppCall = 0;
	tHandle.handPaCall = (u32)hPACall;
	tCallInfo.Clear();
	ptConfTemp->Clear();

	BOOL32 bHangup = FALSE;
	if (NULL != ptCallInfo)
	{
		if (emPATypeSip == emPAType)
		{
			ConvertCallInfoFromStackToUms(*ptCallInfo, tCallInfo, bHangup);
		}
		else
		{
			ConvertCallInfoFromStackToUmsForH323(*ptCallInfo, tCallInfo);
		}

		if (bHangup)
		{
			MdlError(Ums_Mdl_Stack, ("<< UmsCBNewCallIncoming incoming ep is not ManuProduct, Reject by Local! ConfID:%d, epID:%d, PACall:%d.\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
			PA_RejectCall((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, emModuleDisconnect_Rejected);
			return TRUE;
		}

		if (ptCallInfo->m_bCreateConf)
		{
			ConvertCreatConfInfoFromStackToUms(*ptCallInfo, *ptConfTemp);
		}
	}

	if ( ptCallInfo->m_bSignalEncrypt )
	{
		ConvertEpEncryptTypeFromStackToUms(ptCallInfo->m_tQtCallParam.m_emKeyFrequency, tCallInfo.m_tEncrypt.m_emEncryptModel);
	}
	if (NULL != ptCallTP)
	{
		ConvertSipLevelFromStackToUms(ptCallTP->m_emSipLevel, tCallInfo.m_emLevel);
	}
	ConvertProtocolFromPaToTp(emPAType, tCallInfo.m_emTpProtocol);
	MdlHint(Ums_Mdl_Stack, ("<< UmsCBNewCallIncoming PACall:%d, dst:%s-%s-"TPIPFORMAT", src:%s-%s-"TPIPFORMAT", EPType:%d, CallType:%d, Incoming CallBitRate = %d, PAType:%d, IsEncrptQT:%d\n",
			tHandle.handPaCall, 
			tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, Tpu32ToIP(tCallInfo.m_tDestAddr.m_dwIP),
			tCallInfo.m_tSrcAddr.m_tAlias.m_abyAlias, tCallInfo.m_tSrcAddr.m_tE164.m_abyAlias, Tpu32ToIP(tCallInfo.m_tSrcAddr.m_dwIP),
			tCallInfo.m_emSrcEpType, tCallInfo.m_emTpCallType, tCallInfo.m_wBitRate, tCallInfo.m_emTpProtocol,
			tCallInfo.m_tEncrypt.IsQt()
			));

	// 
	memcpy(abyBuf, &tCallInfo, sizeof(TUmsCallInfo));
	memcpy(abyBuf + sizeof(TUmsCallInfo), ptConfTemp, sizeof(TTPConfTemplate));
	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_CallIncoming, abyBuf, tHandle, INSIGN);

	if (NULL != ptCallInfo)
	{
		if (ptCallInfo->m_bCreateConf)
		{
			TTPConfTemplateBuf tTemp;
			tTemp.SetValue(*ptConfTemp);
			ptConfTemp->Clear();

			u8 abyBufTemp[sizeof(TUmsCallInfo) + sizeof(TTPConfTemplateBuf1)];

			memcpy(abyBufTemp, &tCallInfo, sizeof(TUmsCallInfo));
			memcpy(abyBufTemp + sizeof(TUmsCallInfo), &tTemp.m_tTemplate1, sizeof(tTemp.m_tTemplate1)); 
			NotifyMsgToCall(evtp_UmsConfCreateMeeting, tHandle, abyBufTemp, sizeof(TUmsCallInfo) + sizeof(tTemp.m_tTemplate1));

			NotifyMsgToCall(evtp_UmsConfCreateMeeting1, tHandle, &tTemp.m_tTemplate2, sizeof(tTemp.m_tTemplate2));
			MdlLowHint(Ums_Mdl_Stack, ("<< evtp_UmsConfCreateMeeting.\n"));
		}
		else
		{
			MdlLowHint(Ums_Mdl_Stack, ("<< evtp_UmsConfIncoming.\n"));
			NotifyMsgToCall(evtp_UmsConfIncoming, tHandle, &tCallInfo, sizeof(tCallInfo));
		}
	}
	
	return TRUE;
}

BOOL PA_CALLBACK UmsCBChannelConnected(HMDLCALL hPACall, HMDLAPPCALL hAppCall, TChanConnectedInfo* atChanConnectInfo, 
										s32 nSize, TChanDescriptTP *ptDesTP)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;

	TUmsNodeCapset tNodeCap;
	if (NULL != atChanConnectInfo && 0 < nSize)
	{
		MdlHint(Ums_Mdl_Stack, ("<< UmsCBChannelConnected ConfID:%d, epID:%d, PACall:%d, chanSize:%d, chanType:%d, StreamKey(%d, %d, %s)\n"
								, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, nSize, atChanConnectInfo[0].m_tChanType.m_emAVType, 
								atChanConnectInfo[0].m_tStreamKey.m_emEncryptType, atChanConnectInfo[0].m_tStreamKey.m_byLen, atChanConnectInfo[0].m_tStreamKey.m_abyKey));

		// 协商上来的码流密钥
		ConverStreamKeyFromStackToUms(atChanConnectInfo[0].m_tStreamKey, tNodeCap.m_tEncrypt);

		if (emModuleAudioSecondType == atChanConnectInfo[0].m_tChanType.m_emAVType ||
			emModuleVideoSecondType == atChanConnectInfo[0].m_tChanType.m_emAVType)
		{
			ConverDualParamFromStackToUms(atChanConnectInfo, nSize, tNodeCap);
			
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_channelconnect, (u8*)&tNodeCap, tHandle, INSIGN);
			NotifyMsgToCall(ev_OpenDualChan_Connect, tHandle, &tNodeCap, sizeof(TUmsNodeCapset));
			
			return TRUE;
		}
		else
		{
			ConvertChanConnectParamFromStackToUms(atChanConnectInfo, nSize, ptDesTP, tNodeCap);

			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_channelconnect, (u8*)&tNodeCap, tHandle, INSIGN);
			NotifyMsgToCall(evtp_Conf_UmsChannelConnect, tHandle, &tNodeCap, sizeof(tNodeCap));

			return TRUE;
		}
	}
	else if (0 == nSize)
	{
		MdlHint(Ums_Mdl_Stack, ("<< UmsCBChannelConnected ChanSize is Zero, Notify to Call Hangup! ConfID:%d, EpId:%d, PACall:%d, chanSize:%d\n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, nSize));
		
		NotifyMsgToCall(evtp_Conf_UmsChannelConnect, tHandle, &tNodeCap, sizeof(tNodeCap));

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL PA_CALLBACK UmsCBChannelDisconnected(HMDLCALL hPACall, HMDLAPPCALL hAppCall, 
										  TChanDisConnectedInfo *ptDisConInfo, s32 nSize)
{

	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
	if (NULL == ptDisConInfo)
	{
		MdlError(Ums_Mdl_Stack, ("<< UmsCBChannelDisconnected ChanDisInfo is NULL !!! ConfID:%d, epID:%d, PACall:%d\n" 
			, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
		return FALSE;
	}
	EmChannelReason emReason = emModuleChannelReasonBegin;

	BOOL32 bIsDual = FALSE;
	s32 nIndex;
	for (nIndex = 0; nIndex < nSize; ++nIndex)
	{
		EmTPChannelReason emUms;
		ConvertEmChannelReasonFromStackToUms(ptDisConInfo->m_emReason, emUms);
		u32 dwChannedHandle = (u32)(ptDisConInfo[nIndex].m_hAppChan);
		if (CTpTypeAdpt::IsDualChannel(dwChannedHandle))
		{

			tHandle.handPaChan = dwChannedHandle;
			NotifyMsgToCall(ev_DualChan_DisConnect, tHandle, (void*)&emUms, sizeof(emUms));

			MdlHint(Ums_Mdl_Stack, ("<< UmsCBChannelDisconnected Second Stream channel disconnect.  \
									ConfID:%d, epID:%d, PACall:%d, ChanHandle:%d, reason:%d, size:%d\n"
									, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, dwChannedHandle, emUms, nSize));

			bIsDual = TRUE;
			continue;
		}
		if (emTPDualNotSend == emUms)
		{// sip 发双流失败，回调此原因，ptDisConInfo中没有赋值通道句柄，业务在此单独处理
			tHandle.handPaChan = em_second_vidsnd_handle;
			NotifyMsgToCall(ev_DualChan_DisConnect, tHandle, (void*)&emUms, sizeof(emUms));

			tHandle.handPaChan = em_second_audsnd_handle;
			NotifyMsgToCall(ev_DualChan_DisConnect, tHandle, (void*)&emUms, sizeof(emUms));
			MdlHint(Ums_Mdl_Stack, ("<< UmsCBChannelDisconnected SendDual Fail!!! ConfID:%d, epID:%d, PACall:%d, size:%d, emReason:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, nSize, emReason));
			return TRUE;
		}
	}

	if (bIsDual)
	{
		return TRUE;
	}

	if (NULL != ptDisConInfo)
	{
		tHandle.handPaChan = (s32)ptDisConInfo->m_hChan;
		emReason = ptDisConInfo->m_emReason;
	}
	
	MdlHint(Ums_Mdl_Stack, ("<< UmsCBChannelDisconnected ConfID:%d, epID:%d, PACall:%d, ChanHandle:%d, reason:%d, size:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, tHandle.handPaChan, emReason, nSize));
	
	for (nIndex = 0; nIndex < nSize; ++nIndex)
	{
		tHandle.handPaChan = (s32)ptDisConInfo[nIndex].m_hAppChan;
		NotifyMsgToCall(evtp_Conf_UmsChannelDisConnect, tHandle, NULL, 0);
	}	
	return TRUE;
}


BOOL PA_CALLBACK UmsCBChannelFastUpdate(HMDLCALL hPACall, HMDLAPPCALL hAppCall, HMDLCHANNEL hPAChan, HMDLAPPCHANNEL hAppChan )
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
	tHandle.handPaChan = (s32)hPAChan;

	MdlLowDtl(Ums_Mdl_Stack, ("UmsCBChannelFastUpdate AppCall:%d, PaCall:%d, PaChan:%d.\n",
							 tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan));

	NotifyMsgToCall(evtp_Conf_AskKeyFrame, tHandle, NULL, 0);

	return TRUE;
}

BOOL PA_CALLBACK UmsCBChannelFlowCtrl(HMDLCALL hPACall, HMDLAPPCALL hAppCall, HMDLCHANNEL hPAChan, HMDLAPPCHANNEL hAppChan, u16 wBitrate)
{
	
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
	tHandle.handPaChan = (s32)hPAChan;

	MdlLowHint(Ums_Mdl_Stack, ("UmsCBChannelFlowCtrl AppCall:%d, PaCall:%d, PaChan:%d.\n",
							 tHandle.handAppCall, tHandle.handPaCall, tHandle.handPaChan));

	NotifyMsgToCall(evtp_Chan_FlowCtrol, tHandle, (void*)&wBitrate, sizeof(u16));
	
	return TRUE;
}

// BOOL PA_CALLBACK UmsCBDualStreamConnected(HMDLCALL hPACall, HMDLAPPCALL hAppCall, HMDLCHANNEL hPAChan, HMDLAPPCHANNEL hAppChan, 
// 										  TChanConnectedInfo *ptChanInfo)
// {
// 	TUmsHandle tHandle;
// 	tHandle.handAppCall = (u32)hAppCall;
// 	tHandle.handPaCall = (u32)hPACall;
// 		
// 	u8 szBuf[sizeof(TEpKey)+sizeof(TUmsNodeCapset)];
// 		
// 	TEpKey tKey;
// 	TUmsNodeCapset tNodeCap;
// 
// 	if (NULL != ptChanInfo)
// 	{
// 		ConvertDualParamFromStackToUms(ptChanInfo, tNodeCap);
// 	}
// 		
// 	memcpy(szBuf, &tKey, sizeof(tKey));
// 	memcpy(szBuf+sizeof(tKey), &tNodeCap, sizeof(tNodeCap));
// 		
// 		
// 	if (0 == tNodeCap.m_wVidDecNum && 0 == tNodeCap.m_wVidEncNum)
// 	{
// 		MdlHint(Ums_Mdl_Stack, ("<< UmsCBDualStreamConnected ConfID:%d, epID:%d, PACall:%d\n",	
// 				tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
// 			
// 		NotifyMsgToCall(ev_OpenDualChan_Failed, tHandle, NULL, 0);
// 	}
// 	else
// 	{
// 		MdlHint(Ums_Mdl_Stack, ("<< UmsCBDualStreamConnected ConfID:%d, epID:%d, PACall:%d\n", 
// 				tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
// 			
// 		NotifyMsgToCall(ev_OpenDualChan_Connect, tHandle, szBuf, sizeof(TUmsNodeCapset)+sizeof(TEpKey));
// 	}
// 		
// 	return TRUE;
// }

void UmsGetRegInfoForSip(TUmsHandle& tHandle, const EmTpConfProtocol& emProtocol, u8* pBuf, s32 nLen, const u8  byVersion)
{
	//B1版本的全局地址薄
	if (0 == byVersion)
	{
		TTPSipRegPackInfo tUmsRegPackInfo;
		EmGetRegInfoType  emUmsRegInfoType;
		TTPSipRegInfo     tUmsSipRegInfo;
		if (NULL != pBuf)
		{
			TPARegPackInfo     tPARegPackInfo;
			EmPAGetRegInfoType emPaRegInfoType;
			TPARegInfo         tPaRegInfo;
			
			TP_SAFE_CAST(tPARegPackInfo, (u8*)pBuf);
			TP_SAFE_CAST(emPaRegInfoType, (u8*)(pBuf + sizeof(TPARegPackInfo)));
			TP_SAFE_CAST(tPaRegInfo, (u8*)(pBuf + sizeof(TPARegPackInfo) + sizeof(EmPAGetRegInfoType)));
			
			ConvertSipRegInfoFromStackToUms(tPaRegInfo, tUmsSipRegInfo);
			ConvertGetRegInfoTypeFromStackToUms(emPaRegInfoType, emUmsRegInfoType);
			ConvertSipRegPackInfoFromStackToUms(tPARegPackInfo, tUmsRegPackInfo);
			
			MdlHint(Ums_Mdl_Stack, ("<< UmsCBGetRegInfoAckTP ConfID:%d, epID:%d, PackNum:%d, SeqPack:%d, ReqType:%d, AliasNums:%d, AliasType:%d\n",
									 tHandle.GetConfID(), tHandle.GetEpID(), tUmsRegPackInfo.m_wTotalPackNum, tUmsRegPackInfo.m_wPackSeq,
									 emUmsRegInfoType, tUmsSipRegInfo.m_wAliasNum, tUmsSipRegInfo.m_emSelfType));
			
			s8 byBufSnd[sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType) + sizeof(TTPSipRegInfo)] = {0};
			memcpy(byBufSnd, &tUmsRegPackInfo, sizeof(TTPSipRegPackInfo));
			memcpy(byBufSnd + sizeof(TTPSipRegPackInfo), &emUmsRegInfoType, sizeof(EmGetRegInfoType));
			memcpy(byBufSnd + sizeof(TTPSipRegPackInfo) + sizeof(EmGetRegInfoType), &tUmsSipRegInfo, sizeof(TTPSipRegInfo));
			
			NotifyMsgToCall(ev_UmsGetRegInfo_Rsp, tHandle, byBufSnd, sizeof(byBufSnd));
			
			return ;
		}
		else
		{
			MdlHint(Ums_Mdl_Stack, ("<< UmsCBGetRegInfoAckTP Param pBuf = NULL.\n"));
			return ;
		}
		return ;
	}

	//B2版本的全局地址薄
	if (1 == byVersion)
	{
		TPARegPack tPackInfo;
		TP_SAFE_CAST(tPackInfo, pBuf);

		TRegPackInfoEx tInfoEx;
		ConvertRegPackInfoFromStackToUms(tPackInfo, tInfoEx);

		u16 wIndex = 0;
		s32 nLeftLen = nLen - sizeof(TPARegPack);

		if (emTPEndpointTypeUMS == tInfoEx.m_emEndpointType)
		{
			TUmsRegPackEx tUmsPack;
			tUmsPack.m_wSize = 0;
			TPARegInfoUms tUmsInfo;

			for (wIndex = 0; wIndex < tPackInfo.m_wTotalRegInfo; ++wIndex)
			{
				if (nLeftLen < sizeof(TPARegInfoUms))
				{
					MdlHint(Ums_Mdl_Stack, ("UmsGetRegInfoForSip Left size is invalid. Left:%d, StructSize:%d.\n",
											 nLeftLen, sizeof(TPARegInfoUms)))
					break;
				}

				TP_SAFE_CAST(tUmsInfo, pBuf+sizeof(TPARegPack)+wIndex*sizeof(TPARegInfoUms));
				ConvertUmsRegInfoFromStackToUms(tUmsInfo, tUmsPack.m_atRegInfo[wIndex]);
				MdlLowHint(Ums_Mdl_Stack, ("UmsGetRegInfoForSip PaUmsAlias:%d, TpUmsAlias.\n", 
											tUmsInfo.m_wAliasNum, tUmsPack.m_atRegInfo[wIndex].m_wAliasNum));
				++(tUmsPack.m_wSize);

				nLeftLen -= sizeof(TPARegInfoUms);
			}

			u8 abUmsBuf[sizeof(TRegPackInfoEx)+sizeof(TUmsRegPackEx)] = {0};
			memcpy(abUmsBuf, &tPackInfo, sizeof(TRegPackInfoEx));
			memcpy(abUmsBuf+sizeof(TRegPackInfoEx), &tUmsPack, sizeof(TUmsRegPackEx));

			NotifyMsgToCall(ev_UmsGetRegInfo_UmsRspEx, tHandle, abUmsBuf, sizeof(abUmsBuf));
		}
		else if (emTPEndpointTypeCNS == tInfoEx.m_emEndpointType)
		{
			TPARegInfoCns tCnsInfo;
			TCnsRegPackEx tCnsPack;
			tCnsPack.m_wSize = 0;

			for (wIndex = 0; wIndex < tPackInfo.m_wTotalRegInfo; ++wIndex)
			{
				if (nLeftLen < sizeof(TPARegInfoCns))
				{
					MdlHint(Ums_Mdl_Stack, ("UmsGetRegInfoForSip Left size is invalid. Left:%d, StructSize:%d.\n",
											 nLeftLen, sizeof(TPARegInfoCns)))
					break;
				}

				TP_SAFE_CAST(tCnsInfo, pBuf+sizeof(TPARegPack)+wIndex*sizeof(TPARegInfoCns));
				ConvertCnsRegInfoFromStackToUms(tCnsInfo, tCnsPack.m_atRegInfo[wIndex]);
				MdlLowHint(Ums_Mdl_Stack, ("UmsGetRegInfoForSip PaCnsAlias:%d, TpCnsAlias:%d.\n", 
											tCnsInfo.m_wAliasNum, tCnsPack.m_atRegInfo[wIndex].m_wAliasNum));
				++(tCnsPack.m_wSize);

				nLeftLen -= sizeof(TPARegInfoCns);
			}

			u8 abCnsBuf[sizeof(TRegPackInfoEx)+sizeof(TCnsRegPackEx)] = {0};
			memcpy(abCnsBuf, &tPackInfo, sizeof(TRegPackInfoEx));
			memcpy(abCnsBuf+sizeof(TRegPackInfoEx), &tCnsPack, sizeof(TCnsRegPackEx));

			NotifyMsgToCall(ev_UmsGetRegInfo_CnsRspEx, tHandle, abCnsBuf, sizeof(abCnsBuf));
		}
		else
		{
			MdlError(Ums_Mdl_Stack, ("UmsCBGetRegInfoAckTP Unknow type. Type:%d.\n",
									  tInfoEx.m_emEndpointType));
		}
	}
	else
	{
		MdlError(Ums_Mdl_Stack, ("UmsGetRegInfoForSip Unknow version. Version:%d.\n", byVersion));
	}	
}

void UmsGetRegInfoForH323(TUmsHandle& tHandle, const EmTpConfProtocol& emProtocol, u8* pBuf, s32 nLen)
{
	EmGetRegInfoType emGetType = emGetRegInfoType_MT;

	EmModuleGetGKInfoType emType;
	TP_SAFE_CAST(emType, pBuf);

	if (emModuleGetGKInfoType_MT == emType)
	{
		TTPMtRegInfo tMtInfo;
		emGetType = emGetRegInfoType_MT;
		TModuleMtOnlineList tMtList;
		TP_SAFE_CAST(tMtList, pBuf+sizeof(EmModuleGetGKInfoType));

		ConvertMtOnLineList(tMtList, tMtInfo);

		u8 abMtBuf[sizeof(EmGetRegInfoType)+sizeof(TTPMtRegInfo)] = {0};
		memcpy(abMtBuf, &emGetType, sizeof(EmGetRegInfoType));
		memcpy(abMtBuf+sizeof(EmGetRegInfoType), &tMtInfo, sizeof(TTPMtRegInfo));

		NotifyMsgToCall(ev_UmsGetGkRegInfo_MtRsp, tHandle, abMtBuf, sizeof(abMtBuf));
	}
	else if (emModuleGetGKInfoType_MCU == emType)
	{
		TTPMcuRegInfo tMcuInfo;
		emGetType = emGetRefInfoType_MCU;
		TModuleMcuOnlineList tMcuList;
		TP_SAFE_CAST(tMcuList, pBuf+sizeof(EmModuleGetGKInfoType));
		
		ConvertMcuOnLineList(tMcuList, tMcuInfo);

		u8 abMtBuf[sizeof(EmGetRegInfoType)+sizeof(TTPMcuRegInfo)] = {0};
		memcpy(abMtBuf, &emGetType, sizeof(EmGetRegInfoType));
		memcpy(abMtBuf+sizeof(EmGetRegInfoType), &tMcuInfo, sizeof(TTPMcuRegInfo));
		
		NotifyMsgToCall(ev_UmsGetGkRegInfo_McuRsp, tHandle, abMtBuf, sizeof(abMtBuf));
	}
	else
	{
		MdlError(Ums_Mdl_Stack, ("UmsGetRegInfoForH323 Unknow GkInfoType:%d.\n", emType));
		return ;
	}
}



BOOL PA_CALLBACK UmsCBGetRegInfoAckTP(const EmPAConfProtocol emPaType, const s32 nAppId, const u8 *pBuf, const s32 nLen, const u8 byVer)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = nAppId;

	MdlHint(Ums_Mdl_Stack, ("UmsCBGetRegInfoAckTP Protocol:%d, Version:%d.\n",
							 emPaType, byVer));

	EmTpConfProtocol emTpType = emTpInvalidConfProtocel;
	ConvertProtocolFromPaToTp(emPaType, emTpType);

	switch (emTpType)
	{
	case emTpH323:
		{
			UmsGetRegInfoForH323(tHandle, emTpType, (u8*)pBuf, nLen);
		}
		break;

	case emTpSIP:
		{
			UmsGetRegInfoForSip(tHandle, emTpType, (u8*)pBuf, nLen, byVer);
		}
		break;
		
	default:
		{
			MdlError(Ums_Mdl_Stack, ("<< UmsCBGetRegInfoAckTP Invalid protocol type. PaType:%d.\n",
									  emPaType));
			return FALSE;
		}
	}

	return TRUE;
}

BOOL PA_CALLBACK UmsCBDualStreamIncoming(HMDLCALL hPACall, HMDLAPPCALL hAppCall, TDualCapList *ptDual)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
	
	MdlHint(Ums_Mdl_Stack, ("<< UmsCBDualStreamIncoming ConfID:%d, epID:%d, PACall:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
	
	NotifyMsgToCall(ev_OpenDualChan_Incoming, tHandle, NULL, 0);
	
	return TRUE;
}

BOOL PA_CALLBACK UmsCBDualStreamIncomingBfcp(HMDLCALL hPACall, HMDLAPPCALL hAppCall, BOOL32 bNotify)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
	
	MdlHint(Ums_Mdl_Stack, ("<< UmsCBDualStreamIncomingBfcp ConfID:%d, epID:%d, PACall:%d, bNotify:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, bNotify));
	
	if (!bNotify)
	{
		NotifyMsgToCall(ev_OpenDualChan_Incoming, tHandle, NULL, 0);
	}
	
	return TRUE;
}

BOOL PACALLBACK UmsCBMMcuChanConnected(HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptChanConnectInfo)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hCall;

	tpHint(Ums_Mdl_Stack, "<< UmsCBMMcuChanConnected ConfID:%d, epID:%d, PACall:%d.\n",
		tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall);

	if (NULL != ptChanConnectInfo)
	{
		tpLowHint(Ums_Mdl_Stack, "    << UmsCBMMcuChanConnected chan:%d, appchan:%d.\n", 
			ptChanConnectInfo->m_hChan, ptChanConnectInfo->m_hAppChan);

		TUmsMcuChan tMcu;
		tMcu.m_hMcuChan = (s32)ptChanConnectInfo->m_hChan;
		tMcu.m_hMcuAppChan = (s32)ptChanConnectInfo->m_hAppChan;

		NotifyMsgToCall(evtp_MCU_UMS_CasecadeChanConnected, tHandle, &tMcu, sizeof(tMcu));
	}
	
	return TRUE;
}


BOOL PACALLBACK UmsCBMMcuMsg(HMDLCALL hCall, 
							 HMDLAPPCALL hAppCall, 
							 u16 wEvent,
							 void *pBuf, u16 wLen)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hCall;
	
	tpHint(Ums_Mdl_Stack, "<< UmsCBMMcuMsg ConfID:%d, epID:%d, PACall:%d, CBEvent:%d.\n",
		tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, wEvent);

	switch(wEvent)
	{
	case emModuleRegUnReg_Req:
		{
			TRegUnRegReq tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);

			tpLowHint(Ums_Mdl_Stack, "    << UmsCBMMcuMsg emModuleRegUnReg_Req CBLen:%d, Size:%d, bReg:%d, nReqId:%d, bMuit:%d, Name:%s, Pwd:%s.\n",
				wLen, sizeof(tIn), tIn.m_bReg, tIn.m_nReqID, tIn.m_bIsSupportMuitiCasade, tIn.m_aszUserName, tIn.m_aszUserPass);

			TUmsMcuRegUnReg tMcu;
			tMcu.m_bReg = tIn.m_bReg;
			tMcu.m_nReqID = tIn.m_nReqID;

			NotifyMsgToCall(evtp_MCU_UMS_RegUnRegReq, tHandle, &tMcu, sizeof(tMcu));
		}
		break;
	case emModuleRegUnReg_Rsp:
		{
			TRegUnRegRsp tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			
			tpLowHint(Ums_Mdl_Stack, "    << UmsCBMMcuMsg emModuleRegUnReg_Rsp CBLen:%d, Size:%d, bReg:%d, nReqId:%d, ret:%d.\n",
				wLen, sizeof(tIn), tIn.m_bReg, tIn.m_nReqID, tIn.m_emReturnVal);
			
			TUmsMcuRegUnReg tMcu;
			tMcu.m_bReg = tIn.m_bReg;
			tMcu.m_nReqID = tIn.m_nReqID;
			tMcu.m_emRet = (EmUmsMcuRet)tIn.m_emReturnVal;
			
			NotifyMsgToCall(evtp_MCU_UMS_RegUnRegRsp, tHandle, &tMcu, sizeof(tMcu));
		}
		break;
	case emModuleNewRoster_Ntf:
		{
			TRosterList tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			
			tpLowHint(Ums_Mdl_Stack, "    << UmsCBMMcuMsg emModuleNewRoster_Ntf num:%d.\n", tIn.m_nCount);
			u16 wIndex = 0;
			for (wIndex = 0; wIndex < tIn.m_nCount; wIndex++)
			{
				tpLowHint(Ums_Mdl_Stack, "        wIndex:%d, McuID:%d, MtID:%d, State:%d, bLocal%d.\n", wIndex, GETAPP(tIn.m_atRoster[wIndex].m_dwPID),
					GETINS(tIn.m_atRoster[wIndex].m_dwPID), tIn.m_atRoster[wIndex].m_emConnState, tIn.m_atRoster[wIndex].m_bLocal);
			}

			TUmsMcuRosterList tMcu;
			tMcu.m_wNum = (u16)localmin(tIn.m_nCount, UMS_MCU_ROSTER_PARTLIST_NUM);
			for (wIndex = 0; wIndex < tMcu.m_wNum; wIndex++)
			{
				tMcu.m_atRoster[wIndex].m_dwPID = tIn.m_atRoster[wIndex].m_dwPID;
				tMcu.m_atRoster[wIndex].m_byState = (u8)tIn.m_atRoster[wIndex].m_emConnState;
			}

			NotifyMsgToCall(evtp_MCU_UMS_RosterNotify, tHandle, &tMcu, sizeof(tMcu));
		}
		break;
	case emModulePartList_Rsp:
		{
			TPartListMsg tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			
			tpLowHint(Ums_Mdl_Stack, "    << UmsCBMMcuMsg emModulePartList_Rsp bLastPack:%d, nReqId:%d, ret:%d, snapshot:%d, num:%d.\n", 
				tIn.m_bLastPack, tIn.m_nReqID, tIn.m_emReturnVal, tIn.m_nSnapShot, tIn.m_dwPartCount);
			// tIn.m_nSnapShot 暂时无意义，回调上来始终为0

			u8  abyBuf[sizeof(TUmsMcuPartList) + UMS_MCU_PART_MAX_NUM*sizeof(TUmcMcuPart)] = {0};
			TUmsMcuPartList* ptMcu = (TUmsMcuPartList*)abyBuf;
			TUmcMcuPart* ptUmsPart = (TUmcMcuPart*)(abyBuf+sizeof(TUmsMcuPartList));

			ptMcu->m_nReqID			= tIn.m_nReqID;
			ptMcu->m_dwPartCount	= tIn.m_dwPartCount;
			ptMcu->m_emRet			= (EmUmsMcuRet)tIn.m_emReturnVal;
			ptMcu->m_bLastPack		= tIn.m_bLastPack;
			
			u16 wIndex = 0;
			TPart  Part;
			TPart* ptPart = &Part;
			for (wIndex = 0; wIndex < tIn.m_dwPartCount; wIndex++)
			{
				TP_SAFE_CAST(Part, (u8*)((u8*)pBuf+sizeof(TPartListMsg)+wIndex*sizeof(TPart)));
				tpLowHint(Ums_Mdl_Stack, "        wIndex:%d, McuID:%d, MtID:%d, name:%s, str:%s, desc:%s, "IPFORMAT", type:%d, state:%d, bDataMetting:%d, bMutein:%d, bMuteout:%d, bVedIn:%d, bVedOut:%d.\n", 
					wIndex, GETAPP(ptPart->m_dwPID), GETINS(ptPart->m_dwPID), ptPart->m_aszPartName, ptPart->m_aszDialStr, ptPart->m_aszEPDesc, u32ToIP(ptPart->m_dwIP),
					ptPart->m_emEPType, ptPart->m_emConnState, ptPart->m_bDataMeeting, ptPart->m_bAudioMuteIn, ptPart->m_bAudioMuteOut,
					ptPart->m_bVideoMuteIn, ptPart->m_bVideoMuteOut);


				tpLowHint(Ums_Mdl_Stack, "        bInvited:%d, bMaster:%d, startTime:%d, bFECCEnable:%d, videoIn:%d, videoOut:%d, video2In:%d, videoOut2:%d, audioIn:%d, audioOut:%d.\n",
					ptPart->m_bInvited, ptPart->m_bMaster, ptPart->m_tStartTime, ptPart->m_bFECCEnable, ptPart->m_emVideoIn, 
					ptPart->m_emVideoOut, ptPart->m_emVideo2In, ptPart->m_emVideo2Out, ptPart->m_emAudioIn, ptPart->m_emAudioOut);

				tpLowHint(Ums_Mdl_Stack, "        CasLevel:%d, MtIdentify:%s\n",
					ptPart->m_byCasLevel, ptPart->m_abyMtIdentify);
				
				memcpy(ptUmsPart->m_aszEpName, ptPart->m_aszPartName, sizeof(ptPart->m_aszPartName));
				ptUmsPart->m_dwPID		= ptPart->m_dwPID;
				ptUmsPart->m_dwIP		= ptPart->m_dwIP;
				ptUmsPart->m_byState	= ptPart->m_emConnState;
				ptUmsPart->m_bMute		= ptPart->m_bAudioMuteIn;
				ptUmsPart->m_bQuiet		= ptPart->m_bAudioMuteOut;

				ptUmsPart++;
			}
			
			wIndex = 0;
			u8* pbyBuf = abyBuf + sizeof(TUmsMcuPartList);
			TUmcMcuPart tUmsPart;
			ptUmsPart = &tUmsPart;

			u16 wBufLength = sizeof(TUmsMcuPartList) + sizeof(TUmcMcuPart)*ptMcu->m_dwPartCount;
			NotifyMsgToCall(evtp_MCU_UMS_PartListRsp, tHandle, abyBuf, wBufLength);
		}
		break;
	// mcu下级会场connect通知
	case emModuleNewPart_Ntf:
		{
			TPart tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleNewPart_Ntf McuId:%d, MtId:%d, epName:%s, epIp:"IPFORMAT", bState:%d, bMute:%d, bQuiet:%d.\n", 
				GETAPP(tIn.m_dwPID), GETINS(tIn.m_dwPID), tIn.m_aszPartName, u32ToIP(tIn.m_dwIP),
					tIn.m_emConnState, tIn.m_bAudioMuteIn, tIn.m_bAudioMuteOut);

			TUmcMcuPart  tMcuPart;
			memcpy(tMcuPart.m_aszEpName, tIn.m_aszPartName, sizeof(tIn.m_aszPartName));
			tMcuPart.m_dwPID	= tIn.m_dwPID;
			tMcuPart.m_dwIP		= tIn.m_dwIP;
			tMcuPart.m_byState	= tIn.m_emConnState;
			tMcuPart.m_bMute	= tIn.m_bAudioMuteIn;
			tMcuPart.m_bQuiet	= tIn.m_bAudioMuteOut;

			NotifyMsgToCall(evtp_MCU_UMS_PartStateNty, tHandle, &tMcuPart, sizeof(TUmcMcuPart));
		}
		break;
	// mcu添加下级会场通知
	case emModuleCall_Alerting_Ntf:
		{
			TCallNtf tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleCall_Alerting_Ntf McuId:%d, MtId:%d, epName:%s, cook:%d.\n", 
				GETAPP(tIn.m_dwPID), GETINS(tIn.m_dwPID), tIn.m_aszDialStr,
				tIn.m_nCookie);
	
			TUmcMcuPart  tMcuPart;
			// 会场上线之前是ip,上线后是会场别名
			memcpy(tMcuPart.m_aszEpName, tIn.m_aszDialStr, sizeof(tIn.m_aszDialStr));
			tMcuPart.m_dwPID	= tIn.m_dwPID;
			NotifyMsgToCall(evtp_MCU_UMS_PartStateNty, tHandle, &tMcuPart, sizeof(TUmcMcuPart));

		}
		break;
	// mcu下级会场disconnect通知
	case emModuleDisconnpart_Ntf:
		{
			TDiscPartNF tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleDisconnpart_Ntf McuId:%d, MtId:%d, DelMcu:%d, DelMt:%d, cook:%d.\n", 
				GETAPP(tIn.m_dwPID), GETINS(tIn.m_dwPID), GETAPP(tIn.m_dwNewPID), GETINS(tIn.m_dwNewPID), 
				tIn.m_nCookie);

			TUmcMcuPart  tMcuPart;
			tMcuPart.m_dwPID = tIn.m_dwPID;
			
			NotifyMsgToCall(evtp_MCU_UMS_PartStateNty, tHandle, &tMcuPart, sizeof(TUmcMcuPart));
		}
		break;
	case emModuleDeletepart_Ntf:
		{
			TDelPartNF tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleDeletepart_Ntf McuId:%d, MtId:%d, cook:%d.\n", 
				GETAPP(tIn.m_dwPID), GETINS(tIn.m_dwPID),
				tIn.m_nCookie);
			
			u32 dwDelPID = tIn.m_dwPID;
			NotifyMsgToCall(evtp_MCU_UMS_DelPartNty, tHandle, &dwDelPID, sizeof(s32));
		}
		break;
	case emModuleReinvitePart_Rsp:
		{// mcu暂无反馈
			TPartRsp tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleReinvitePart_Rsp McuId:%d, MtId:%d, ReqId:%d, ReturnRal:%d.\n", 
				GETAPP(tIn.m_dwPID), GETINS(tIn.m_dwPID),
				tIn.m_nReqID, tIn.m_emReturnVal);
		}
		break;
	case emModuleDisconnpart_Rsp:
		{// mcu暂无反馈
			TPartRsp tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleDisconnpart_Rsp McuId:%d, MtId:%d, ReqId:%d, ReturnRal:%d.\n", 
				GETAPP(tIn.m_dwPID), GETINS(tIn.m_dwPID),
				tIn.m_nReqID, tIn.m_emReturnVal);
		}
		break;
	case emModuleOutPut_Ntf:
		{
			TPartOutputNtf tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleOutPut_Ntf McuID:%d, MtId:%d, ViewId:%d.\n", 
				GETAPP(tIn.m_dwPID), GETINS(tIn.m_dwPID), tIn.m_nViewID);
		}
		break;
	case emModuleAudioInfo_Rsp:
		{
			TConfAudioInfo tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleAudioInfo_Rsp mixcount:%d, defindex:%d, ReturnRal:%d.\n", 
				tIn.m_byMixerCount, tIn.m_byDefaultMixerIndex, tIn.m_emReturnVal);
		}
		break;
	case emModuleVideoInfo_Rsp:
		{
			TConfVideoInfo tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			tpLowHint(Ums_Mdl_Stack, "UmsCBMMcuMsg emModuleVideoInfo_Rsp ViewCount:%d, defIndex:%d, bufsize:%d.\n", 
				tIn.m_byConfViewCount, tIn.m_byDefaultViewIndex, sizeof(TConfVideoInfo));
		}
		break;
	case emModuleNonStandard_Ntf:
		{
			TNonStandardMsg tIn;
			TP_SAFE_CAST(tIn, (u8*)pBuf);
			CServMsg cServMsg(tIn.m_abyMsgBuf, (u16)(tIn.m_nMsgLen));
			ProcMcuNonStandardMsg(cServMsg, tHandle);
		}
		break;
	
	default:
		{
			tpError(Ums_Mdl_Stack, "    << UmsCBMMcuMsg unkown msg! ConfID:%d, epID:%d, PACall:%d, CBEvent:%d, CBLen:%d.\n",
				tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, wEvent, wLen);
		}
		break;
	}

	return TRUE;
}

BOOL PACALLBACK UmsCBFeccChanConnected(HMDLCALL hCall, HMDLAPPCALL hAppCall, TFeccCapbility *ptFeccCap)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hCall;
	
	tpHint(Ums_Mdl_Stack, "<< UmsCBFeccChanConnected ConfID:%d, epID:%d, PACall:%d.\n",
		tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall);
	
	if (ptFeccCap)
	{
		tpHint(Ums_Mdl_Stack, "<< UmsCBFeccChanConnected rcvip:"TPIPFORMAT", rcvport:%d, sendip:"TPIPFORMAT", sendport:%d, direction:%d, SampleRate:%d, payLoad:%d.\n",
			Tpu32ToIP(ptFeccCap->m_tRecvAddress.m_dwIp), ptFeccCap->m_tRecvAddress.m_wPort,
			Tpu32ToIP(ptFeccCap->m_tSendAddress.m_dwIp), ptFeccCap->m_tSendAddress.m_wPort,
			ptFeccCap->m_byDirection, ptFeccCap->m_wSampleRate, ptFeccCap->m_byDynamicPayload);	
		//	NotifyMsgToCall(ev_OpenDualChan_Incoming, tHandle, NULL, 0);
	}
	NotifyMsgToCall(evtp_CNS_UMS_FeccChanConnected, tHandle, NULL, 0);	
	
	return TRUE;
}

BOOL PACALLBACK UmsCBFeccMsg (HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct *ptFeccStruct, TMDLTERLABEL *ptSrcLabel, 
							  TMDLTERLABEL *ptDstLabel)
{
	//BOOL PA_SendFeccMsg(HMDLCALL hPACall, HMDLAPPCALL hAppCall, TMdlFeccStruct *ptFeccAction, TMDLTERLABEL *ptSrcLabel, TMDLTERLABEL *ptDstLabel);
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hCall;

	tpHint(Ums_Mdl_Stack, "<< UmsCBFeccMsg ConfID:%d, epID:%d, PACall:%d.\n",
		tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall);
	if (!ptFeccStruct || !ptSrcLabel || !ptDstLabel)
	{
		tpError(Ums_Mdl_Stack, "<< UmsCBFeccMsg FeccStruct SrcLabel or DstLabel is null.\n");
		return FALSE;
	}

	TFeccInfo tInfo;
	ConvertFeccActFromsTackToUms(*ptFeccStruct, tInfo.m_tCamAct);
	tInfo.m_wConfID = tHandle.GetConfID();
	tInfo.m_wEpID = ptDstLabel->m_byTerNo;
	MdlHint(Ums_Mdl_Stack, (">>>> UmsCBFeccMsg SrcMcu:%d, SrcMt:%d, DstMcu:%d, DstMt:%d, FeccAct:%d, CamReq:%d\n",
		ptSrcLabel->m_byMcuNo, ptSrcLabel->m_byTerNo, ptDstLabel->m_byMcuNo, ptDstLabel->m_byTerNo,
		tInfo.m_tCamAct.m_emFeccAct, tInfo.m_tCamAct.GetFeccParam()));


	NotifyMsgToCall(evtp_CNS_UMS_FeccReq, tHandle, &tInfo, sizeof(tInfo));
	return TRUE;
}


BOOL PA_CALLBACK UmsCBConfCtrl(HMDLCALL hPACall, HMDLAPPCALL hAppCall, s32 nMsgType, u8* pBuf, s32 nSize, 	EmPAConfProtocol emPAType)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;

	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	u32 nPaID = tHandle.handPaCall;

	u16 wEvent = 0;
	switch(nMsgType)
	{
	case emModuleTerminalIDListRequest:	wEvent = evtpH323_Conf_TerminalListRequest;		break;
	case emModuleTerminalYouAreSeeing:	wEvent = evtp_Conf_YouAreSeeing_Ind;			break;
	case emMoudleVideoAliasInd:			wEvent = evtp_CNS_UMS_VidInfoNty;	break;  
	case emModuleterStatusInd:
		{
			TModuleTerStatus tTerStatus = *(TModuleTerStatus*)pBuf;
			MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::emModuleterStatusInd, ModuleTerStatus ConfID:%d,EpID:%d,PAType:%d,bIsMute:%d, bIsQuiet:%d, LocalCamNo:%d, RamCamNo:%d, bAllFecc:%d\n",
					wConfID,wEpID,emPAType,tTerStatus.m_bIsMute, tTerStatus.m_bIsQuiet, 
					tTerStatus.m_byLocalCamCtrlNo, tTerStatus.m_byRemoteCamCtrlNo, tTerStatus.m_bFECCEnalbe));
	
			MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::emModuleterStatusInd, m_byCamNum:%d, m_emVideoSrc:%d\n", 
				tTerStatus.m_byCamNum, tTerStatus.m_emVideoSrc));

			MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::emModuleterStatusInd, CamType:%d, LocalNo:%d, RmtNo:%d, CurCam:%d, CamNum:%d, state[%d|%d|%d|%d|%d|%d|%d]\n", 
				tTerStatus.m_emCamCtrlSrc, tTerStatus.m_byLocalCamCtrlNo,
				tTerStatus.m_byRemoteCamCtrlNo, tTerStatus.m_byCamNum,
				tTerStatus.m_bCamStatus[0], tTerStatus.m_bCamStatus[0],
				tTerStatus.m_bCamStatus[0], tTerStatus.m_bCamStatus[0],
				tTerStatus.m_bCamStatus[0], tTerStatus.m_bCamStatus[0],
				tTerStatus.m_bCamStatus[0]));

			if (emTpH323 == emPAType)
			{
				TEpStatusInfo tInfo;
				
				tInfo.m_tQuietInd.m_tKeyID.m_wEpID = wEpID;
				tInfo.m_tQuietInd.m_bQuiet = tTerStatus.m_bIsQuiet;

				tInfo.m_tMuteInd.m_tKeyID.m_wEpID = wEpID;
				tInfo.m_tMuteInd.m_bMute = tTerStatus.m_bIsMute;

				// 323会场当前使用中的视频源索引
				tInfo.m_byCurVidNo = (u8)tTerStatus.m_emVideoSrc;
				tInfo.m_bAllowFecc = tTerStatus.m_bFECCEnalbe;
				NotifyMsgToCall(evtp_CNS_UMS_EpStatusNty,tHandle,&tInfo,sizeof(tInfo));
			}
		}
		return TRUE;
	case emModuleKedaManuProduct:
		{
			TKedaManuProductTP tKedaManuPro = *(TKedaManuProductTP*)pBuf;
			MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::emModuleKedaManuProduct, ConfID:%d, EpID:%d, PaCall:%u, PAType:%d, buf:%u, size:%d.\n",
				wConfID, wEpID, nPaID, emPAType, tKedaManuPro.m_byAgentID, nSize));
			u8 byKedaManu = tKedaManuPro.m_byAgentID;
			NotifyMsgToCall(evtp_KedaManuProduct_Notify, tHandle, &byKedaManu, sizeof(u8));
			
// 			if (g_bKedaManuOn)
// 			{
// 				TKedaManuProductTP tKedaManuPro;
// 				MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::emModuleKedaManuProduct post to ....\n"));
// 				PA_SendConfCtrl(HMDLCALL(tHandle.handPaCall), (HMDLAPPCALL)tHandle.handAppCall, emModuleKedaManuProduct, (u8*)&tKedaManuPro, sizeof(tKedaManuPro));
// 			}
			
		}
		return TRUE;	
		

	default:
		MdlError(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl failed. unkonw stack type.  ConfID:%d, epID:%d, event:%d\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType));
		break;
	}

	switch(wEvent)
	{
	case evtpH323_Conf_TerminalListRequest:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::evtpH323_Conf_TerminalListRequest, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, NULL, 0);	
		}
		break;
	case evtp_Conf_YouAreSeeing_Ind:
		{
			TYouAreSeeing* ptPAInfo = (TYouAreSeeing*)(pBuf+sizeof(TMDLTERMINALINFO) + sizeof(BOOL32));
			TSpeakerCapTr tCap;
			tCap.m_bIsSpeaker = ptPAInfo->m_bExist;
			tCap.m_wSpeakerID = ptPAInfo->m_wCNSId;
			tCap.m_wAudSnd = (u16)ptPAInfo->m_dwAudioNum;
			tCap.m_wVidSnd = (u16)ptPAInfo->m_dwVideoNum;
			tCap.m_tEpAlias.SetAlias(tp_Alias_h323, ptPAInfo->m_achMeetingName);
			tCap.m_wSpeakerIndex = ptPAInfo->m_wSpeakerIndex;
			
			if (emPATypeSip == emPAType)
			{
				s8 *pzAliasUTF8 = NULL;
				utf8_to_gb2312((s8 *)tCap.m_tEpAlias.m_abyAlias, &pzAliasUTF8);
				strncpy((s8 *)tCap.m_tEpAlias.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}

			MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::evtp_Conf_YouAreSeeing_Ind ConfID:%d, EpID:%d, CallID:%d, vidSnd:%d, audSnd:%d, IsSpeaker:%d, SpeakerID:%d, PAType:%d\n"
				, wConfID, wEpID, nPaID, tCap.m_wVidSnd, tCap.m_wAudSnd, tCap.m_bIsSpeaker, tCap.m_wSpeakerID, emPAType));
			
			NotifyMsgToCall(wEvent, tHandle, &tCap, sizeof(tCap));	
		}
		break;
	// 会场视频源信息通知
	case evtp_CNS_UMS_VidInfoNty:
		{// pBuf : u8 vidNum + (u8 vidIndex + u8 vidAliasLen + vidAliasLen) * vidNum
			TVidSourceInfo tInfo;
			tInfo.m_byNum = *pBuf++;
			for (u16 wIndex = 0; wIndex < tInfo.m_byNum; ++wIndex)
			{
				u8 byVidIndex = *pBuf++;
				u8 byAliasLen = *pBuf++;
				
				tInfo.m_atVidInfo[wIndex].m_byIndex = byVidIndex;
				memcpy(tInfo.m_atVidInfo[wIndex].m_abyAlias, pBuf, byAliasLen);

				pBuf+=byAliasLen;
				MdlLowHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::evtp_CNS_UMS_VidInfoNty VidIndex:%d, VidAlias:%s\n"
				, tInfo.m_atVidInfo[wIndex].m_byIndex, tInfo.m_atVidInfo[wIndex].m_abyAlias));
			}

			MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl::evtp_CNS_UMS_VidInfoNty ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			
			NotifyMsgToCall(evtp_CNS_UMS_VidInfoNty, tHandle, &tInfo, sizeof(TVidSourceInfo));	
		}
		break;
	default:
		MdlError(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl failed. unkonw msg type.  ConfID:%d, epID:%d, event:%d\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType));
		break;
	}
	
	return TRUE;
}

BOOL PA_CALLBACK UmsCBConfCtrlTP(HMDLCALL hPACall, HMDLAPPCALL hAppCall, s32 nMsgType, u8* pBuf, s32 nSize, EmPAConfProtocol emPAType )
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;

	u16 wEvent = 0;
	switch(nMsgType)
	{
	case emPAConfNodeUpdateTrList:		wEvent = evtp_Conf_EpCallInfo_Update;	break;
	case emPAConfNodeUpdateB2NewTrList:	wEvent = evtp_Conf_EpChanInfo_Update;	break;
	case emPAConfNodeDelTrList:			wEvent = evtp_Conf_EpInfo_Del;			break;
	//case emModuleTerminalYouAreSeeing:	wEvent = evtp_Conf_YouAreSeeing_Ind;	break;
	case emPAConfStartPoll:				wEvent = evtp_Conf_StartPoll_cmd;		break;
	case emPAConfStartPollAck:			wEvent = evtp_Conf_StartPoll_ack;		break;
	case emPAConfPollNodeChange:		wEvent = evtp_Conf_Poll_NodeChange;		break;
	case emPAConfEndPoll:				wEvent = evtp_Conf_Poll_End;			break;
	case emPAConfPollFastUpdate:		wEvent = evtp_Conf_Poll_AskKeyFrame;	break;
//混音
//////////////////////////////////////////////////////////////////////////////////
	case emPAOpenAudChanCmd:		wEvent = evtp_OpenAudChan_Cmd;			break;
	case emPAOpenAudChanAck:		wEvent = evtp_OpenAudChan_Ack;			break;
	case emPAOpenVidChanCmd:		wEvent = evtp_OpenVidChan_Cmd;			break;
	case emPAOpenVidChanAck:		wEvent = evtp_OpenVidChan_Ack;			break;
	case emPACloseVidChanCmd:		wEvent = evtp_CloseVidChan_Cmd;			break;
	case emPAUmsDiscussScreenStat_Notify:		wEvent = evtp_UmsDiscussScreenStat_Notify; break;
	case emPAUmsCnsSpeakerIndxAdjust_Notify:	wEvent = evtp_UmsCnsSpeakerIndxAdjust_Notify; break;
	case emPAUmsDiscussFastUpdate_Req:			wEvent = evtp_UmsDiscussFastUpdate_Req; break;

	case emPAConfCascadingSpeaker:	wEvent = evtp_Conf_CnsSpeakerCascad_Notify;	break;
	case emPAConfPeerMuteCmd:		wEvent = evtp_Conf_MuteRemoteEp_Cmd;	break;		
	case emPAConfPeerMuteInd:		wEvent = evtp_Conf_MuteRemoteEp_Ind;	break;
	case emPAConfPeerSoundOffCmd:	wEvent = evtp_Conf_QuietRemoteEp_Cmd;	break;
	case emPAConfPeerSoundOffInd:	wEvent = evtp_Conf_QuietRemoteEp_Ind;	break;
	case emPAConfCallCascadingOff:	wEvent = evtp_Conf_CallExistEPTr_cmd;	break;
	case emPAConfHangUpCascadingConf:wEvent = evtp_Conf_DropEPTr_cmd;		break;
//双流
	case emPARequestDualStreamCmd:	wEvent = evtp_Conf_RequestDualStream_cmd;break;
	case emPARequestDualStreamInd:	wEvent = evtp_Conf_RequestDualStream_Ind;break;
	case emPASendDualStream:		wEvent = evtp_cascade_OpenDualChan_Cmd;	break;
	case emPASendDualStreamAck:		wEvent = evtp_cascade_OpenDualChan_Ind;	break;
	case emPAStopDualStream:		wEvent = evtp_Conf_StopSendDual_Ind;	break;
	case emPAStopRcvDualInd:		wEvent = evtp_Conf_StopRcvDual_Ind;		break;
	case emPADualStreamFastUpdate:	wEvent = evtp_Conf_DualFastUpdate_Ind;	break;
	case emPAConfStatusIndicate:	wEvent = evtp_Conf_StatusInfo_Notify; break;

	case emPATpConfStartDual_Cmd:	wEvent = ev_UmsConfStartDual_Cmd;		break;
	case emPATpConfStartDual_Ind:	wEvent = ev_UmsConfStartDual_Ind;		break;
	case emPATpConfStopDual_Cmd:	wEvent = ev_UmsConfStopDual_Cmd;		break;
	case emPATpConfStopDual_Ind:	wEvent = ev_UmsConfStopDual_Ind;		break;
	case emPATpConfDualEp_Nty:		wEvent = ev_UmsConfDualEp_Nty;			break;

	case emPAAddTvMonitorCmd:		wEvent = evtp_Conf_TvMonitor_Cmd;		break;
	case emPAAddTvMonitorInd:		wEvent = evtp_Conf_TvMonitor_Ind;		break;
	case emPAStopMonitorCmd:		wEvent = evtp_Conf_TvMonitor_stop;		break;
	case emPAAskKeybyScreen:		wEvent = evtp_Conf_AskKeyByScreen;		break;
	case emPASrcDualNameInd:		wEvent = evtp_Conf_SrcDualName_Ind;		break;
	case emPAChairCapNotify:		wEvent = evtp_Conf_ChairCap_Notify;		break;	
	case emPAConfStartPolling:		wEvent = evtp_Conf_StartPoll_Req;		break;	
	case emPAConfClosePolling:		wEvent = evtp_Conf_StopPoll_Req;		break;
		
	case emPACascadeGetVidcmd:		wEvent = evtp_cascade_GetVid_cmd;		break;
	case emPACascadeGetVidInd:		wEvent = evtp_cascade_GetVid_ack;		break;	
	case emPACascadeStopGetVidcmd:	wEvent = evtp_cascade_StopGetVid_cmd;	break;	

	case emPACascadeFlowCtrl:		wEvent = evtp_Conf_FlowCtrol;			break;
	case emPAAdjustFrameRate_Cmd:	wEvent = evtp_Conf_AdjustFrameRate;		break;
	case emPAAdjustVidRes_Cmd:		wEvent = evtp_Conf_AdjustVidRes;		break;

	case emPAStartRcvDualInd:		wEvent = evtp_Conf_StartRcvDual_Ind;	break;

	//CNS过来的UI类消息
	//////////////////////////////////////////////////////////////////////////////////
	case emPATpConfAMixUpdate_Cmd:		wEvent = ev_UmsConfAMixUpdate_Cmd;		break;
	case emPATpConfApplySpeaker_Cmd:	wEvent = ev_UmsConfApplySpeaker_Cmd;	break;
	case emPATpConfMute_Cmd:			wEvent = ev_UmsConfMute_Cmd;			break;
	case emPATpConfQuiet_Cmd:			wEvent = ev_UmsConfQuiet_Cmd;			break;
	case emPATpInviteCnsByAlias_Cmd:	wEvent = ev_UmsInviteCnsByAlias_Cmd;	break;
	case emPATpInviteCnsByEpId_Cmd:	wEvent = ev_UmsInviteCnsByEpId_Cmd;		break;
	case emPATpHangupCns_Cmd:			wEvent = ev_UmsHangupCns_Cmd;			break;
	case emPATpHangupConf_Cmd:			wEvent = ev_UmsHangupConf_Cmd;			break;

	case emPATpConfAMixUpdate_Nty:		wEvent = ev_UmsConfAMixUpdate_Nty;		break;
	case emPATpConfApplySpeaker_Nty:	wEvent = ev_UmsConfApplySpeaker_Nty;	break;
	case emPATpConfQuiet_Nty:			wEvent = ev_UmsConfQuiet_Nty;			break;
	case emPATpConfMute_Nty:			wEvent = ev_UmsConfMute_Nty;			break;
	case emPATpUpdateConfTurnlist_Nty:	wEvent = ev_UmsUpdateConfTurnlist_Nty;	break;
	case emPATpChairConfInfo_Nty:		wEvent = ev_UmsChairConfInfo_Nty;		break;
	case emPATpAudMixStatus_Nty:		wEvent = ev_UmsAudMixStatus_Nty;		break;
	case emPAUmsAudMixDisListOpr_Cmd:	wEvent = ev_UmsAudMixDisListOpr_Cmd;	break;
	case emPAUmsCommonReasonToUI_Ind:	wEvent = ev_UmsCommonReasonToUI_Ind;	break;
	case emPAUmsConfAMixVacSwitch:      wEvent = ev_UmsConfAMixVacSwitch;       break;

	case emPAUmsCascadeOpenChairChan_Cmd: wEvent = evtp_cascade_OpenChairChan_cmd; break;
	case emPAUmsCascadeOpenChairChan_Ack: wEvent = evtp_cascade_OpenChairChan_ack; break;

	case emPAUmsConfRecPlayState_Nty:	wEvent = evtp_Conf_RecPlayState_Nty;	break;
	case emPAUmsConfStopRecPlay_Req:	wEvent = evtp_Conf_StopRecPlay_Req;		break;
	case emPAChanResetFastUpdate:		wEvent = evtp_Conf_ResetFastUpdate;		break;
	case emPAUMS_UMC_SelView_Ntfy:		wEvent = ev_UMS_CNC_SelView_Ntfy;		break;
	case emPACNC_UMS_SelView_Req:		wEvent = ev_CNC_UMS_SelView_Req;		break;
	case emPAUMS_CNC_SelView_Ind:		wEvent = ev_UMS_CNC_SelView_Ind;		break;
	case emPAGetVid_Req:				wEvent = ev_GetVid_Req;					break;
	case emPAConf_SuspendPoll_Req:		wEvent = evtp_Conf_SuspendPoll_Req;		break;
	case emPAGetVid_Res:				wEvent = ev_GetVid_Res;					break;
	case emPAGetVid_Stop_Req:			wEvent = ev_GetVid_Stop_Req;			break;
	case emPAGetVid_Stop_Res:			wEvent = ev_GetVid_Stop_Res;			break;

	case emPAConf_CasecadePollEp_Req:	wEvent = evtp_Conf_CasecadePollEp_Req;	break;
	case emPAConf_CasecadePollEp_Rsp:	wEvent = evtp_Conf_CasecadePollEp_Rsp;	break;
		
	case emPACNC_UMS_RervesBrdVmp_Req:	wEvent = ev_CNC_UMS_RervesBrdVmp_Req;	break;
	case emPACNC_UMS_SetBrdVmp_Req:		wEvent = ev_CNC_UMS_SetBrdVmp_Req;		break;
	case emPACNC_UMS_BrdVmp_Req:		wEvent = ev_CNC_UMS_BrdVmp_Req;			break;
	case emPAUMS_UMS_VmpCasecade_Ntfy:	wEvent = ev_UMS_UMS_VmpCasecade_Ntfy;	break;
	case emPACNC_UMS_SaveVmpCfg_Cmd:	wEvent = ev_CNC_UMS_SaveVmpCfg_Cmd;		break;
	case emPA_CnsJoinConf_Ack:			wEvent = evtp_CnsJoinConf_Ack;			break;

	//////////////////////////////////////////////////////////////////////////
	//白板消息
	case emPAJoinWBConf_Cmd:			wEvent = evtp_JoinWBConf_Cmd;	break;
	case emPAJoinWBConf_Ind:			wEvent = evtp_JoinWBConf_Ind;	break;
	case emPAHangupWBConf_Cmd:			wEvent = evtp_HungUpWBConf_Cmd;	break;

	//////////////////////////////////////////////////////////////////////////
	// 终端控制电视墙相关消息
	case emPACNS_UMS_HduPlay_Req:				wEvent = evTPCNS_UMS_HduPlay_Req;			break;
	case emPACNS_UMS_HduStopPlay_Req:			wEvent = evTPCNS_UMS_HduStopPlay_Req;		break;
	case emPACNS_UMS_HduAllStopPlay_Req:        wEvent = evTPCNS_UMS_HduStopAllPlay_Req;	break;
	case emPACNS_UMS_HduSetVol_Req:				wEvent = evTPCNS_UMS_HduSetVol_Req;		break;
	case emPACNS_UMS_HduChangeChanMode_Req:		wEvent = evTPCNS_UMS_HduChangeChanMode_Req;break;

	//////////////////////////////////////////////////////////////////////////
	// 点名相关消息
	case emPAUmsConfRollCallUpdate_Cmd:	        wEvent = ev_UmsConfRollCallUpdate_Cmd;        break;
	case emPAUmsConfRollCallNextEp_Cmd:		    wEvent = ev_UmsConfRollCallNextEp_Cmd;	      break;
	case emPAUmsRollCallScreenStat_Notify:		wEvent = evtp_UmsRollCallScreenStat_Notify;	  break;
	case emPAUmsConfRollCallUpdate_Nty:		    wEvent = ev_UmsConfRollCallUpdate_Nty;	      break;
    case emPAUmsConfRollCallUpdataList_Cmd:     wEvent = ev_UmsConfRollCallUpdataList_Cmd;    break;
	case emPAUmsRollUpdate_PresentState:        wEvent = evtp_UmsRollUpdate_PresentState;     break;

	//////////////////////////////////////////////////////////////////////////
	// 会议混音相关消息
	case emPACNS_UMS_ConfAudMixMode_cmd:       wEvent = evtp_CNS_UMS_ConfAudMixMode_cmd;        break;
	case emPACNS_UMS_ConfAudMixList_cmd:       wEvent = evtp_CNS_UMS_ConfAudMixList_cmd;        break;
	case emPAUMS_CNS_ConfAudMixMode_Notify:    wEvent = evtp_UMS_CNS_ConfAudMixMode_Notify;     break;
	case emPAUMS_UMS_ConfAudMixMode_Notify:    wEvent = evtp_UMS_UMS_ConfAudMixMode_Notify;     break;

	/////////////////////////////////////////////////////////////////////////
	// 远遥下级通知上级远遥信息
	case emPAConf_EpVidFeccInfo_Update:		   wEvent = evtp_Conf_EpVidFeccInfo_Update;			break;

    //////////////////////////////////////////////////////////////////////////
	// QT
	//Protocol_file
	case emModuleQuantumMediaKey:		wEvent = evtp_MediaKey_Nty;		break;	 //级联上级通知下来的
    //case  ev_StkSetQTEncryptInfo_Cmd  wEvent = ev_StkSetQTEncryptInfo_Cmd;    break; //主席设置QTMT信息

	default:
		MdlError(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrlTP failed. unkonw stack type.  ConfID:%d, epID:%d, event:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType));
		break;
	}

	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	u32 nPaID = tHandle.handPaCall;

// 	MdlHint(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl event:%d->%s, ConfID:%d, EpID:%d, CallID:%d\n"
// 		, wEvent, GetEventNamebyID(wEvent), wConfID, wEpID, nPaID));

	switch(wEvent)
	{
	case evtp_Conf_EpCallInfo_Update:
		{	
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_EpCallInfo_Update ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TConfNodeCallUpdateTrList tList;
			ConvertNodeCallUpdateFromStackToUms(tList, *(TPAConfNodeUpdateTrList*)pBuf);			
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpCallInfo, (u8*)&tList, tHandle, INSIGN);
			NotifyMsgToCall(evtp_Conf_EpCallInfo_Update, tHandle, &tList, sizeof(tList));	
		}
		break;
	case evtp_Conf_EpChanInfo_Update:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_EpChanInfo_Update ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));

			TConfNodeChanUpdateTrList tList;
			ConvertNodeChanUpdateFromStackToUms(tList, *(TPAConfNodeUpdateB2NEWTrList*)pBuf);	
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpChanInfo, (u8*)&tList, tHandle, INSIGN);
			NotifyMsgToCall(evtp_Conf_EpChanInfo_Update, tHandle, &tList, sizeof(tList));	
		}
		break;
	case evtp_Conf_EpInfo_Del:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_EpInfo_Del ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TConfNodeDelTrList tList;
			ConvertNodeDelFromStackToUms(tList, *(TPAConfNodeDelTrList*)pBuf);
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpIDInfo, (u8*)&tList, tHandle, INSIGN);
			NotifyMsgToCall(evtp_Conf_EpInfo_Del, tHandle, &tList, sizeof(tList));	
		}
		break;

//轮询
	case evtp_Conf_StartPoll_cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StartPoll_cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPollCmdTr tPollInfo;			
			ConvertConfPollCmdFromStackToUms(*(TPAPollCmd*)pBuf, tPollInfo);
			NotifyMsgToCall(wEvent, tHandle, &tPollInfo, sizeof(tPollInfo));	
		}
		break;
	case evtp_Conf_StartPoll_ack:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StartPoll_ack ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPollAckTr tPollAck;	
			ConvertConfPollAckFromStackToUms(*(TPAPollAck*)pBuf, tPollAck);		
			NotifyMsgToCall(wEvent, tHandle, &tPollAck, sizeof(tPollAck));	
		}
		break;
	case evtp_Conf_Poll_NodeChange:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_Poll_NodeChange ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAPollNodeChange* pPaPoll = (TPAPollNodeChange*)pBuf;			
			TEpKey tKey;
//			strncpy(tKey.m_tKey.m_szEpID, pPaPoll->m_tNodeInfo.m_tKey.m_szEpID, TP_MAX_EPID_LEN);
			tKey.m_wEpID = pPaPoll->m_tNodeInfo.m_wEpID;
			NotifyMsgToCall(wEvent, tHandle, &tKey, sizeof(tKey));	
		}
		break;
	case evtp_Conf_Poll_End:
		{
			BOOL32 tPA = *(BOOL32*)pBuf;			
			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_Poll_End ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			NotifyMsgToCall(wEvent, tHandle, &tPA, sizeof(tPA));	
		}
		break;
	case evtp_Conf_Poll_AskKeyFrame:
		{			
			tpLowDtl(Ums_Mdl_Stack, "<<<< evtp_Conf_Poll_AskKeyFrame ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID);
			NotifyMsgToCall(wEvent, tHandle, NULL, 0);	
		}
		break;

//混音
	//////////////////////////////////////////////////////////////////////////
	case evtp_OpenAudChan_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_OpenAudChan_Cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAAudChanCmd& tPaAudCmd = *(TPAAudChanCmd*)pBuf;			
			TAudChanCmd tCmd;
			ConvertAudChanCmdFromStackToUms(tPaAudCmd, tCmd);						
			NotifyMsgToCall(wEvent, tHandle, &tCmd, sizeof(tCmd));	
		}
		break;
	case evtp_OpenAudChan_Ack:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_OpenAudChan_Ack ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAAudChanAck& tPaAudAck = *(TPAAudChanAck*)pBuf;			
			TAudChanAck tAck;
			ConvertAudChanAckFromStackToUms(tPaAudAck, tAck);						
			NotifyMsgToCall(wEvent, tHandle, &tAck, sizeof(tAck));
		}
		break;
	case evtp_OpenVidChan_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_OpenVidChan_Cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAVidChanCmd& tPaAudCmd = *(TPAVidChanCmd*)pBuf;			
			TVidChanCmd tCmd;
			ConvertVidChanCmdFromStackToUms(tPaAudCmd, tCmd);						
			NotifyMsgToCall(wEvent, tHandle, &tCmd, sizeof(tCmd));	
		}
		break;
	case evtp_OpenVidChan_Ack:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_OpenVidChan_Ack ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAVidChanAck& tPaVidCmd = *(TPAVidChanAck*)pBuf;			
			TVidChanAck tAck;
			ConvertVidChanAckFromStackToUms(tPaVidCmd, tAck);						
			NotifyMsgToCall(wEvent, tHandle, &tAck, sizeof(tAck));	
		}
		break;
	case evtp_CloseVidChan_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_CloseVidChan_Cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			//u16 wEpID = *(u16*)pBuf;
			NotifyMsgToCall(wEvent, tHandle, pBuf, sizeof(u16)+sizeof(u32));	
		}
		break;
	case evtp_UmsDiscussScreenStat_Notify:
		{
			TPADiscussCasecadeNtfy* ptPa = (TPADiscussCasecadeNtfy*) pBuf; 
			TDiscussCasecadeNtfy tUms;

			tUms.m_bIsDiscussModle = ptPa->m_bIsDiscussModle;

			u16 wIndex = 0;
			u16 wLoop = 0;
			s8 *pzAliasUTF8 = NULL;
			for (wIndex = 0; wIndex < emDiscussObjEnd; wIndex++)
			{

				tUms.m_atDiscussObj[wIndex].m_wReserve = ptPa->m_atDiscussObj[wIndex].wReserve;
				for (wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
				{
					tUms.m_atDiscussObj[wIndex].m_abIsVaild[wLoop] = ptPa->m_atDiscussObj[wIndex].m_abIsVaild[wLoop];
					ConvertAliasFromStackToUms(ptPa->m_atDiscussObj[wIndex].m_atEpAlias[wLoop], tUms.m_atDiscussObj[wIndex].m_atEpAlias[wLoop]);
					utf8_to_gb2312((s8*)tUms.m_atDiscussObj[wIndex].m_atEpAlias[wLoop].m_abyAlias, &pzAliasUTF8);
					strncpy((s8*)tUms.m_atDiscussObj[wIndex].m_atEpAlias[wLoop].m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
					free(pzAliasUTF8);
					pzAliasUTF8 = NULL;
				}
			}

			for (wIndex = 0; wIndex < PA_CONF_MAX_AUDMIXNUM; wIndex++)
			{
				tUms.m_tEpAudInfo.m_awDiscussEpId[wIndex] = ptPa->m_awDiscussEpId[wIndex];
				tUms.m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][0] = ptPa->m_abyIsRcvNModeAud[wIndex][0];
				tUms.m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][1] = ptPa->m_abyIsRcvNModeAud[wIndex][1];
				tUms.m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][2] = ptPa->m_abyIsRcvNModeAud[wIndex][2];
				if (0 != ptPa->m_awDiscussEpId[wIndex])
				{
					MdlHint(Ums_Mdl_Stack, ("To call... ConfId:%d, Ep:%d, (%d,%d,%d)\n", wConfID, ptPa->m_awDiscussEpId[wIndex],
						ptPa->m_abyIsRcvNModeAud[wIndex][0], ptPa->m_abyIsRcvNModeAud[wIndex][1], ptPa->m_abyIsRcvNModeAud[wIndex][2]));
				}
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_UmsDiscussScreenStat_Notify, ConfID:%d, EpID:%d, CallID:%d, bNtyDis:%d, obj(%d-%s,%d-%s,%d-%s), obj(%d-%s,%d-%s,%d-%s), obj(%d-%s,%d-%s,%d-%s)\n"
				, wConfID, wEpID, nPaID, tUms.m_bIsDiscussModle, 
				tUms.m_atDiscussObj[0].m_abIsVaild[0], tUms.m_atDiscussObj[0].m_atEpAlias[0].m_abyAlias, 
				tUms.m_atDiscussObj[0].m_abIsVaild[1], tUms.m_atDiscussObj[0].m_atEpAlias[1].m_abyAlias,
				tUms.m_atDiscussObj[0].m_abIsVaild[2], tUms.m_atDiscussObj[0].m_atEpAlias[2].m_abyAlias,
				tUms.m_atDiscussObj[1].m_abIsVaild[0], tUms.m_atDiscussObj[1].m_atEpAlias[0].m_abyAlias,
				tUms.m_atDiscussObj[1].m_abIsVaild[1], tUms.m_atDiscussObj[1].m_atEpAlias[1].m_abyAlias,
				tUms.m_atDiscussObj[1].m_abIsVaild[2], tUms.m_atDiscussObj[1].m_atEpAlias[2].m_abyAlias,
				tUms.m_atDiscussObj[2].m_abIsVaild[0], tUms.m_atDiscussObj[2].m_atEpAlias[0].m_abyAlias,
				tUms.m_atDiscussObj[2].m_abIsVaild[1], tUms.m_atDiscussObj[2].m_atEpAlias[1].m_abyAlias,
				tUms.m_atDiscussObj[2].m_abIsVaild[2], tUms.m_atDiscussObj[2].m_atEpAlias[2].m_abyAlias));
			MdlHint(Ums_Mdl_Stack, ("  SpeacialEp:%d.\n", tUms.m_atDiscussObj[emDiscussObjForSpeakerEp].m_wReserve));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_UmsCnsSpeakerIndxAdjust_Notify:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_UmsCnsSpeakerIndxAdjust_Notify ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TCnsSpeakerAdjust tAdjust;
			TPACascadingSpeaker* ptPA = (TPACascadingSpeaker*)pBuf;
//			strncpy(tAdjust.m_tKey.m_tKey.m_szEpID, ptPA->m_tNodeKey.m_tKey.m_szEpID, TP_MAX_EPID_LEN);
			tAdjust.m_tKey.m_wEpID = ptPA->m_tNodeKey.m_wEpID;
			tAdjust.m_wEpID = ptPA->m_wEpID;						
			tAdjust.m_wSpeakerIndex = ptPA->m_wSpeaker;
			NotifyMsgToCall(wEvent, tHandle, &tAdjust, sizeof(tAdjust));
		}
		break;
	case evtp_UmsDiscussFastUpdate_Req:
		{
			TDisAskKeyFrame tUms;
			TPADisAskKeyFrame* ptPA = (TPADisAskKeyFrame*)pBuf;
			
			tUms.m_wEpID = ptPA->m_wEpID;
			tUms.m_wScreenNo = ptPA->m_wScreenNo;
			tUms.m_bReqBySys = ptPA->m_bReqBySys;
			
			MdlLowDtl(Ums_Mdl_Stack, ("<<<< evtp_UmsDiscussFastUpdate_Req ConfID:%d, EpID:%d, CallID:%d, SrcEpID:%d, SrcScreenID:%d\n", 
				wConfID, wEpID, nPaID, tUms.m_wEpID, tUms.m_wScreenNo));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	//////////////////////////////////////////////////////////////////////////
	case evtp_Conf_CnsSpeakerCascad_Notify:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_CnsSpeakerCascad_Notify ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TCnsSpeakerAdjust tAdjust;
			TPACascadingSpeaker* ptPA = (TPACascadingSpeaker*)pBuf;
//			strncpy(tAdjust.m_tKey.m_tKey.m_szEpID, ptPA->m_tNodeKey.m_tKey.m_szEpID, TP_MAX_EPID_LEN);
			tAdjust.m_tKey.m_wEpID = ptPA->m_tNodeKey.m_wEpID;
			tAdjust.m_wEpID = ptPA->m_wEpID;						
			tAdjust.m_wSpeakerIndex = ptPA->m_wSpeaker;
			NotifyMsgToCall(wEvent, tHandle, &tAdjust, sizeof(tAdjust));
		}
		break;
	case evtp_Conf_MuteRemoteEp_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_MuteRemoteEp_Cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAPeerMuteCmd* ptMuteCmd = (TPAPeerMuteCmd*)pBuf;
			TMuteRmtEpCmd tRmtEp;
			tRmtEp.m_bMute = ptMuteCmd->m_bMute;
			tRmtEp.m_wEpID = ptMuteCmd->m_wEpId;			
			NotifyMsgToCall(wEvent, tHandle, &tRmtEp, sizeof(tRmtEp));
		}
		break;
	case evtp_Conf_MuteRemoteEp_Ind:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_MuteRemoteEp_Ind ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAPeerMuteInd* ptMuteInd = (TPAPeerMuteInd*)pBuf;
			TMuteRmtEpInd tRmtEp;
			tRmtEp.m_bMute = ptMuteInd->m_bMute;
//			strncpy(tRmtEp.m_tKeyID.m_tKey.m_szEpID, ptMuteInd->m_tPeerMute.m_tKey.m_szEpID, TP_MAX_EPID_LEN);	
			tRmtEp.m_tKeyID.m_wEpID = ptMuteInd->m_tPeerMute.m_wEpID;
			NotifyMsgToCall(wEvent, tHandle, &tRmtEp, sizeof(tRmtEp));
		}
		break;
	case evtp_Conf_QuietRemoteEp_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_QuietRemoteEp_Cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAPeerMuteCmd* ptMuteCmd = (TPAPeerMuteCmd*)pBuf;
			TQuietRmtEpCmd tRmtEp;
			tRmtEp.m_bQuiet = ptMuteCmd->m_bMute;
			tRmtEp.m_wEpID = ptMuteCmd->m_wEpId;			
			NotifyMsgToCall(wEvent, tHandle, &tRmtEp, sizeof(tRmtEp));
		}
		break;
	case evtp_Conf_QuietRemoteEp_Ind:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_QuietRemoteEp_Ind ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TPAPeerMuteInd* ptMuteInd = (TPAPeerMuteInd*)pBuf;
			TQuietRmtEpInd tRmtEp;
			tRmtEp.m_bQuiet = ptMuteInd->m_bMute;
//			strncpy(tRmtEp.m_tKeyID.m_tKey.m_szEpID, ptMuteInd->m_tPeerMute.m_tKey.m_szEpID, TP_MAX_EPID_LEN);	
			tRmtEp.m_tKeyID.m_wEpID = ptMuteInd->m_tPeerMute.m_wEpID;
			NotifyMsgToCall(wEvent, tHandle, &tRmtEp, sizeof(tRmtEp));
		}
		break;
	case evtp_Conf_CallExistEPTr_cmd:
		{
			u16 wRmtEp = *(u16*)(pBuf);
			TPAAlias tPaAlias = *(TPAAlias*)(pBuf+sizeof(u16));
			TTPAlias tAlias;
			ConvertAliasFromStackToUms(tPaAlias, tAlias);

			if (emPATypeSip == emPAType)
			{
				s8 *pzAliasUTF8 = NULL;
				utf8_to_gb2312((s8 *)tAlias.m_abyAlias, &pzAliasUTF8);
				strncpy((s8 *)tAlias.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}


			u8 abBuf[sizeof(u16)+sizeof(TTPAlias)] = {0};
			memcpy(abBuf, &wRmtEp, sizeof(u16));
			memcpy(abBuf+sizeof(u16), &tAlias, sizeof(tAlias));

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_CallExistEPTr_cmd ConfID:%d, EpID:%d, CallID:%d, CallNode:%d, Alias:%s, PAType:%d\n"
					, wConfID, wEpID, nPaID, wRmtEp, tAlias.m_abyAlias, emPAType));
			NotifyMsgToCall(wEvent, tHandle, abBuf, sizeof(u16)+sizeof(TTPAlias));
		}
		break;
	case evtp_Conf_DropEPTr_cmd:
		{
			THangupCascadingConf* ptCmd = (THangupCascadingConf*)(pBuf);
			TDropEpCmd tCmd;
			tCmd.m_wEpID = ptCmd->m_wEpId;
			tCmd.m_bDel = ptCmd->m_bClear;
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_DropEPTr_cmd ConfID:%d, EpID:%d, CallID:%d, DstID:%d, del:%d\n"
				, wConfID, wEpID, nPaID, tCmd.m_wEpID, tCmd.m_bDel));
			NotifyMsgToCall(wEvent, tHandle, &tCmd, sizeof(tCmd));
		}
		break;
	case evtp_Conf_RequestDualStream_cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_RequestDualStream_cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TDualRequest* ptPA = (TDualRequest*)pBuf;;
			TEpKeyEx tUms;
			tUms.m_wEpID = ptPA->m_nEpId;
			memcpy(tUms.m_achReserve, ptPA->m_achCascade, sizeof(ptPA->m_achCascade));
//			strncpy(tUms.m_tKey.m_szEpID, ptPA->m_achCascade, TP_MAX_EPID_LEN);
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_Conf_RequestDualStream_Ind:
		{			
			TDualRequestAckTr tUms ;			
			tUms.m_bAccept = *(BOOL32*)pBuf;
			tUms.m_dwReason = *(EmTPDualReason*)(pBuf+sizeof(BOOL32));//CTpTypeAdpt::GetDualReason(*(EmDualReason*)(pBuf+sizeof(BOOL32))) ;
			TDualRequest* ptPA = (TDualRequest*)(pBuf+sizeof(BOOL32) + sizeof(u32));
			tUms.m_tEpKey.m_wEpID = ptPA->m_nEpId;
//			strncpy(tUms.m_tEpKey.m_tKey.m_szEpID, ptPA->m_achCascade, TP_MAX_EPID_LEN);

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_RequestDualStream_Ind ConfID:%d, EpID:%d, CallID:%d, accept:%d, reason:%d, DualEpId:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_bAccept, tUms.m_dwReason, tUms.m_tEpKey.m_wEpID));

			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_cascade_OpenDualChan_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_cascade_OpenDualChan_Cmd ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TDualInfo* ptPA = (TDualInfo*)pBuf;
			TDualInfoTr tUms;
			ConvertConfDualStreamFromStackToUms(tUms, *ptPA);
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_cascade_OpenDualChan_Ind:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_cascade_OpenDualChan_Ind ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TDualInfoAck* ptPA = (TDualInfoAck*)pBuf;
			TDualInfoAckTr tUms;
			tUms.m_bAccept = ptPA->m_bAccept;
			ConvertConfDualStreamFromStackToUms(tUms.m_tDualInfo, ptPA->m_tDualInfo);
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case evtp_Conf_StopSendDual_Ind:
		{			
			TPAEpKey tPA = *(TPAEpKey*) pBuf;
			TEpKey tUms;

			ConverEpKeyFromStackToUms(tPA, tUms);
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StopSendDual_Ind ConfID:%d, EpID:%d, CallID:%d, epID:%d\n", wConfID, wEpID, nPaID, tUms.m_wEpID));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case evtp_Conf_StopRcvDual_Ind:
		{
			EmDualReason tPA = *(EmDualReason*) pBuf;
			EmTPDualReason tUms = CTpTypeAdpt::GetDualReason(tPA);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StopRcvDual_Ind ConfID:%d, EpID:%d, CallID:%d, reason:%d\n", wConfID, wEpID, nPaID, tUms));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case evtp_Conf_DualFastUpdate_Ind:
		{
			BOOL32 tPA = *(BOOL32*) pBuf;
			tpLowDtl(Ums_Mdl_Stack, "<<<< evtp_Conf_DualFastUpdate_Ind ConfID:%d, EpID:%d, CallID:%d, bSys:%d\n", wConfID, wEpID, nPaID, tPA);
			NotifyMsgToCall(wEvent, tHandle, &tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_TvMonitor_Cmd:
		{			
			TPATvMonitorCmd tPA = *(TPATvMonitorCmd*) pBuf;
			TTvMonitorCmdTr tUms;
			ConvertAddTvMonitorFromStackToUms(tUms, tPA);			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_TvMonitor_Cmd ConfID:%d, EpID:%d, CallID:%d, index:%d, dst:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wIndex, tUms.m_wEpID));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_Conf_TvMonitor_Ind:
		{			
			TTvMonitorIndTr tUms;
			TPATvMonitorInd tPA = *(TPATvMonitorInd*) pBuf;
			ConvertAddTvMonitorIndFromStackToUms(tUms, tPA);
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_TvMonitor_Ind ConfID:%d, EpID:%d, CallID:%d, index:%d, wEpID:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wIndex, tUms.m_wEpID));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_Conf_TvMonitor_stop:
		{
			u16 tUms = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_TvMonitor_stop ConfID:%d, EpID:%d, CallID:%d, wIndex:%d\n", wConfID, wEpID, nPaID, tUms));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_Conf_AskKeyByScreen:
		{
			TPAAskKeyByScreenTr* ptPaInd = (TPAAskKeyByScreenTr*)(pBuf);
			TAskKeyByScreenTr tUms;
			
			tUms.m_wEpID = ptPaInd->m_wEpID;
			tUms.m_wScreenIndex = ptPaInd->m_wScreenNum;
			tUms.m_bReqBySys = ptPaInd->m_bReqBySys;

			tUms.m_dwAskType = ptPaInd->m_dwAskType;
			tUms.m_dwRervse1 = ptPaInd->m_dwRervse1;
			tUms.m_dwRervse2 = ptPaInd->m_dwRervse2;

			MdlLowDtl(Ums_Mdl_Stack, ("<<<< evtp_Conf_AskKeyByScreen ConfID:%d, EpID:%d, CallID:%d, wDstEp:%d, Screen:%d, bSys:%d, Type:%d\n", 
										wConfID, wEpID, nPaID, tUms.m_wEpID, tUms.m_wScreenIndex, tUms.m_bReqBySys, tUms.m_dwAskType));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_Conf_StatusInfo_Notify:
		{			
			TPAConfStatusInd* ptPaInd = (TPAConfStatusInd*)(pBuf);
			TTPConfInfoNtfy tUms;
			tUms.m_wConfID = ptPaInd->m_wMeetingId;
			tUms.m_tBeginTime = ptPaInd->m_tBeginTime;			
			tUms.m_tConf.SetAlias(ptPaInd->m_achConfName);
			tUms.m_tChair.SetAlias(ptPaInd->m_achChairName);
			tUms.m_tSpeak.SetAlias(ptPaInd->m_achSpeakName);

			if (emPATypeSip == emPAType)
			{
				s8 *pzAliasUTF8 = NULL;
				utf8_to_gb2312((s8 *)tUms.m_tConf.m_abyAlias, &pzAliasUTF8);
				strncpy((s8 *)tUms.m_tConf.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;

				utf8_to_gb2312((s8 *)tUms.m_tChair.m_abyAlias, &pzAliasUTF8);
				strncpy((s8 *)tUms.m_tChair.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;

				utf8_to_gb2312((s8 *)tUms.m_tSpeak.m_abyAlias, &pzAliasUTF8);
				strncpy((s8 *)tUms.m_tSpeak.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}

			tUms.m_bMixMotive = ptPaInd->m_bMixMotive;
			tUms.m_bSpeakOnline = ptPaInd->m_bSpeakOnline;

			tUms.m_wChairVidSndCap = ptPaInd->m_wChairVidSndCap;
			tUms.m_wChairAudSndCap = ptPaInd->m_wChairAudSndCap;
		
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StatusInfo_Notify ConfID:%d, EpID:%d, CallID:%d, MeetingID:%d, Conf:%s, Chair:%s, vidNum:%d, audNum:%d, PAType:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wConfID, tUms.m_tConf.m_abyAlias, tUms.m_tChair.m_abyAlias, tUms.m_wChairVidSndCap, tUms.m_wChairAudSndCap, emPAType));

			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));			
		}
		break;
	case evtp_Conf_SrcDualName_Ind:
		{
			TPAName* ptPaInd = (TPAName*)(pBuf);
			TPAEpKey* ptPaKey = (TPAEpKey*)(pBuf + sizeof(TPAName));

	
			u8 abyBuf[sizeof(TTPAlias) + sizeof(TEpKey)];
			memset(abyBuf, 0, sizeof(abyBuf));
			TTPAlias* ptName = (TTPAlias*)abyBuf;
			TEpKey* ptKey = (TEpKey*)(abyBuf + sizeof(TTPAlias));

			ptName->SetAlias(ptPaInd->m_achAlias);
			ConvertEpKeyFromStackToUms(*ptPaKey, *ptKey);

 			if (emPATypeSip == emPAType)
 			{
 				s8 *pzAliasUTF8 = NULL;
 				utf8_to_gb2312((s8 *)ptName->m_abyAlias, &pzAliasUTF8);
 				strncpy((s8 *)ptName->m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
 				free(pzAliasUTF8);
 				pzAliasUTF8 = NULL;
 			}

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_SrcDualName_Ind ConfID:%d, EpID:%d, CallID:%d, DualName:%s, emPAType:%d\n"
				, wConfID, wEpID, nPaID, ptName->m_abyAlias, ptKey->m_wEpID, emPAType));
			
			NotifyMsgToCall(wEvent, tHandle, abyBuf, sizeof(abyBuf));
		}
		break;
	case evtp_Conf_ChairCap_Notify:
		{
			TPANodeCapsetTr* ptPA = (TPANodeCapsetTr*)(pBuf);
			TChairInfoTr tUms;
			tUms.m_wSpeakerIndex = ptPA->m_wSpeakindex;
			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_ChairCap_Notify, ConfID:%d, EpID:%d, CallID:%d, index:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wSpeakerIndex));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_Conf_StartPoll_Req:
		{			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StartPoll_Req ConfID:%d, EpID:%d\n", wConfID, wEpID));
			NotifyMsgToCall(wEvent, tHandle, NULL, 0);
		}
		break;
	case evtp_Conf_StopPoll_Req:
		{
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StopPoll_Req ConfID:%d, EpID:%d\n", wConfID, wEpID));
			NotifyMsgToCall(wEvent, tHandle, NULL, 0);
		}
		break;
		
	case evtp_cascade_GetVid_cmd:
		{			
			TPAViewCmd* ptPA = (TPAViewCmd*)(pBuf);
			TViewCmdTr tUms;
			ConvertViewCmdFromStackToUms(tUms, *ptPA);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_cascade_GetVid_cmd, ConfID:%d, EpID:%d, dst:%d, index:%d\n", wConfID, wEpID, tUms.m_wEpID, tUms.m_wIndex));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_cascade_GetVid_ack:
		{			
			TPAViewAck* ptPA = (TPAViewAck*)(pBuf);
			TViewAckTr tUms;
			ConvertViewIndFromStackToUms(tUms, *ptPA);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_cascade_GetVid_ack, ConfID:%d, EpID:%d, index:%d, ret:%d\n", wConfID, wEpID, tUms.m_wIndex, tUms.m_emRes));			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_cascade_StopGetVid_cmd:
		{
			u16 tUms = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_cascade_StopGetVid_cmd, ConfID:%d, EpID:%d, chan:%d\n", wConfID, wEpID, tUms));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;

	case evtp_Conf_StartRcvDual_Ind:
		{
			TPAEpKey* ptPA = (TPAEpKey*)pBuf;
			TEpKeyEx tUms;
		//	ConvertEpKeyFromStackToUms(*ptPA, tUms);

			tUms.m_wEpID = ptPA->m_wEpID;
			memcpy(tUms.m_achReserve, ptPA->m_tKey.m_achEpID, sizeof(ptPA->m_tKey.m_achEpID)); 

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StartRcvDual_Ind, ConfID:%d, EpID:%d, dualID:%d\n", wConfID, wEpID, tUms.m_wEpID));
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case evtp_Conf_FlowCtrol:
		{
			TPAFlowControl tPa = *(TPAFlowControl*) pBuf;
			TFlowControl tUms;
			
			ConvertEpKeyFromStackToUms(tPa.m_tEpKey, tUms.m_tEpKey);
			tUms.m_wBand = tPa.m_wBand;
			tUms.m_wEncNo = tPa.m_wEncNo;
			tUms.m_dwOpr = tPa.m_dwEnOpr;

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_FlowCtrol, ConfID:%d, EpID:%d, DstEp:%d, Band:%d\n"
				, wConfID, wEpID, tUms.m_tEpKey.m_wEpID, tUms.m_wBand));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case evtp_Conf_AdjustFrameRate:
		{
			TPAAdjustFrameRate tPa = *(TPAAdjustFrameRate*) pBuf;
			TAdjustFrameRate tUms;
			tUms.m_wEpID = tPa.m_wEpID;
			tUms.m_wFrameRate = tPa.m_wFrameRate;
			tUms.m_bReset = tPa.m_bReset;

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_AdjustFrameRate, ConfID:%d, EpID:%d, DstEp:%d, FrameRate:%d\n"
																, wConfID, wEpID, tUms.m_wEpID, tUms.m_wFrameRate));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case evtp_Conf_AdjustVidRes:
		{
			TPAAdjustVidRes tPa = *(TPAAdjustVidRes*) pBuf;	
			TAdjustVidRes tUms;
			tUms.m_wEpID = tPa.m_wEpID;
			tUms.m_wScreenIndx = tPa.m_wScreenIndx;
			tUms.m_dwVidRes = tPa.m_dwVidRes;
			tUms.m_bReset = tPa.m_bReset;

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_AdjustVidRes, ConfID:%d, EpID:%d, DstEp:%d, ScrIndx:%d, VidRes:%d\n"
																, wConfID, wEpID, tUms.m_wEpID, tUms.m_wScreenIndx, tUms.m_dwVidRes));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	//CNS过来的UI类消息
	//////////////////////////////////////////////////////////////////////////////////
	case ev_UmsConfAMixUpdate_Cmd:
		{	
			TPAConfAuxMixInfo tPa = *(TPAConfAuxMixInfo*) pBuf;
			TConfAuxMixInfo tUms;
			
			ConvertConfAuxMixInfoFromStackToUms(tPa, tUms);

			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfAMixUpdate_Cmd, ConfID:%d, EpID:%d, bStart:%d\n"
				, wConfID, wEpID, tUms.m_bStart));

			for (u16 wI = 0; wI < PA_CONF_MAX_AUDMIXNUM; wI++)
			{
				MdlHint(Ums_Mdl_Stack, ("  <<<< [%d] List EpId:%d.\n", wI, tPa.m_atAuxMixList.m_awList[wI]));
			}
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsConfApplySpeaker_Cmd:
		{
			TPAConfEpID tPa = *(TPAConfEpID*) pBuf;
			TConfEpID tUms;
			
			ConvertConfEpIDFromStackToUms(tPa, tUms);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfApplySpeaker_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));		
		}
		break;
	case ev_UmsConfApplySpeaker_Nty:
		{
			TPAConfEpID tPa = *(TPAConfEpID*) pBuf;
			TConfEpID tUms;
			
			ConvertConfEpIDFromStackToUms(tPa, tUms);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfApplySpeaker_Nty, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));		
		}
		break;
	case ev_UmsConfMute_Cmd:
		{
			TPAConfEpID tPa = *(TPAConfEpID*) pBuf;
			BOOL32 bMute = *(BOOL32*)(pBuf + sizeof(TPAConfEpID));
			TConfEpID tUms;
			
			ConvertConfEpIDFromStackToUms(tPa, tUms);

			u8 byBuf[sizeof(TConfEpID) + sizeof(BOOL32)] = {0};
			memcpy(byBuf, &tUms, sizeof(tUms));
			memcpy(byBuf + sizeof(tUms), &bMute, sizeof(BOOL32));
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfMute_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, byBuf, sizeof(byBuf));		
		}
		break;
	case ev_UmsConfQuiet_Cmd:
		{
			TPAConfEpID tPa = *(TPAConfEpID*) pBuf;
			BOOL32 bQuiet = *(BOOL32*)(pBuf + sizeof(TPAConfEpID));
			TConfEpID tUms;
			
			ConvertConfEpIDFromStackToUms(tPa, tUms);
			
			u8 byBuf[sizeof(TConfEpID) + sizeof(BOOL32)] = {0};
			memcpy(byBuf, &tUms, sizeof(tUms));
			memcpy(byBuf + sizeof(tUms), &bQuiet, sizeof(BOOL32));
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfMute_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, byBuf, sizeof(byBuf));		
		}
		break;
	case ev_UmsInviteCnsByAlias_Cmd:
		{
 			TPACallAddr tPaCallAddr = *(TPACallAddr*)pBuf;
 			TTpCallAddr tUmsCallAddr;

			ConvertAliasFromStackToUms(tPaCallAddr.m_tAlias,tUmsCallAddr.m_tAlias);
			ConvertAliasFromStackToUms(tPaCallAddr.m_tE164,tUmsCallAddr.m_tE164);
		    tUmsCallAddr.m_dwIP = tPaCallAddr.m_dwIP;   
			tUmsCallAddr.m_bAliasIP = tPaCallAddr.m_bAliasIP;
			ConvertCallTypeFromStackToUms(tPaCallAddr.m_byCallType,tUmsCallAddr.m_byCallType);

			if (emPATypeSip == emPAType)
			{
				s8 *pzAliasUTF8 = NULL;
				s8 *pzE164UTF8 = NULL;
				
				utf8_to_gb2312((s8 *)tPaCallAddr.m_tAlias.m_achAlias, &pzAliasUTF8);
				utf8_to_gb2312((s8 *)tPaCallAddr.m_tE164.m_achAlias, &pzE164UTF8);

				strncpy((s8 *)tUmsCallAddr.m_tAlias.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				strncpy((s8 *)tUmsCallAddr.m_tE164.m_abyAlias, pzE164UTF8, TP_MAX_ALIAS_LEN);

	 			free(pzAliasUTF8);
				free(pzE164UTF8);
 				pzAliasUTF8 = NULL;
				pzE164UTF8 = NULL;
			}
	 		MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsInviteCnsByAlias_Cmd, ConfID:%d, EpID:%d, PAType:%d, Alias:%s, E164:%s, IP:"TPIPFORMAT".\n", 
				wConfID, wEpID, emPAType, tPaCallAddr.m_tAlias.m_achAlias, tPaCallAddr.m_tE164.m_achAlias, Tpu32ToIP(tPaCallAddr.m_dwIP)));	
    		NotifyMsgToCall(wEvent, tHandle, &tUmsCallAddr, sizeof(tUmsCallAddr));	
		}
		break;
	case ev_UmsInviteCnsByEpId_Cmd:
		{			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsInviteCnsByEpId_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, (void*)pBuf, sizeof(u16));		
		}
		break;
	case ev_UmsHangupCns_Cmd:
		{			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsHangupCns_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, (void*)pBuf, sizeof(u16));		
		}
		break;
	case ev_UmsHangupConf_Cmd:
		{			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsHangupConf_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, NULL, 0);		
		}
		break;
	case ev_UmsConfAMixUpdate_Nty:
		{
			TPAConfAuxMixInfo& tPA = *(TPAConfAuxMixInfo*)pBuf;
			TConfAuxMixInfo tUms;
			ConvertConfAuxMixInfoFromStackToUms(tPA, tUms);			
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfAMixUpdate_Nty, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsConfQuiet_Nty:
		{
			TPAConfEpID& tPA = *(TPAConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pBuf + sizeof(TPAConfEpID));
			
			TConfEpID tUms;
			ConvertConfEpIDFromStackToUms(tPA, tUms);
			
			u8 byBuf[sizeof(TConfEpID) + sizeof(BOOL)] = {0};
			memcpy(byBuf, &tUms, sizeof(TConfEpID));
			memcpy(byBuf + sizeof(TConfEpID), &bRet, sizeof(BOOL));			
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfQuiet_Nty, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, byBuf, sizeof(byBuf));	
		}
		break;
	case ev_UmsConfMute_Nty:
		{
			TPAConfEpID& tPA = *(TPAConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pBuf + sizeof(TPAConfEpID));
			
			TConfEpID tUms;
			ConvertConfEpIDFromStackToUms(tPA, tUms);
			
			u8 byBuf[sizeof(TConfEpID) + sizeof(BOOL)] = {0};
			memcpy(byBuf, &tUms, sizeof(TConfEpID));
			memcpy(byBuf + sizeof(TConfEpID), &bRet, sizeof(BOOL));			
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfMute_Nty, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, byBuf, sizeof(byBuf));	
		}
		break;
	case ev_UmsUpdateConfTurnlist_Nty:
		{
			TPAPollListNtfy& tPA = *(TPAPollListNtfy*)pBuf;
			
			TTpPollListNtfy tUms;
			tUms.m_wConfID = tPA.m_wConfID;
			tUms.m_wInterval = tPA.m_wInterval;
			tUms.m_nFlag = tPA.m_nFlag;
			tUms.m_wCurNum = tPA.m_wCurNum;
			tUms.m_wTotalNum = tPA.m_wTotalNum;

			memcpy(tUms.m_awList, tPA.m_awList, sizeof(tPA.m_awList));
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsUpdateConfTurnlist_Nty, ConfID:%d, EpID:%d, nFlag:%d, curnum:%d, totalnum:%d\n", 
				wConfID, wEpID, tUms.m_nFlag, tUms.m_wCurNum, tUms.m_wTotalNum));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsChairConfInfo_Nty:
		{
			TPAChairConfInfo& tPA = *(TPAChairConfInfo*)pBuf;
			
			TChairConfInfo tUms;
			ConvertChairConfInfoFromStackToUms(tPA, tUms);
			
			if (emPATypeSip == emPAType)
			{
				s8 *pzAliasUTF8 = NULL;
				utf8_to_gb2312((s8 *)tUms.m_tChairName.m_abyAlias, &pzAliasUTF8);
				strncpy((s8 *)tUms.m_tChairName.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;

				utf8_to_gb2312((s8 *)tUms.m_tConfName.m_abyAlias, &pzAliasUTF8);
				strncpy((s8 *)tUms.m_tConfName.m_abyAlias, pzAliasUTF8, TP_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsChairConfInfo_Nty, ConfID:%d, EpID:%d, PAType:%d\n", wConfID, wEpID, emPAType));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsAudMixStatus_Nty:
		{
			TPAAudMixStat& tPA = *(TPAAudMixStat*)pBuf;
			
			TAudMixStat tUms;
			ConvertAudMixStatFromStackToUms(tPA, tUms);		
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsAudMixStatus_Nty, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsConfStartDual_Cmd:
		{
			TPAConfEpID& tPA = *(TPAConfEpID*)pBuf;
			
			TConfEpID tUms;
			ConvertConfEpIDFromStackToUms(tPA, tUms);	
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfStartDual_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsConfStartDual_Ind:
		{
			TPAConfEpID& tPA = *(TPAConfEpID*)pBuf;
			EmTPDualReason& emReason = *(EmTPDualReason*)(pBuf + sizeof(TPAConfEpID));
			
			TConfEpID tUms;
			ConvertConfEpIDFromStackToUms(tPA, tUms);
			
			u8 byBuf[sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
			memcpy(byBuf, &tUms, sizeof(TConfEpID));
			memcpy(byBuf + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));			
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfStartDual_Ind, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, byBuf, sizeof(byBuf));	
		}
		break;
	case ev_UmsConfStopDual_Cmd:
		{
			TPAConfEpID& tPA = *(TPAConfEpID*)pBuf;
			
			TConfEpID tUms;
			ConvertConfEpIDFromStackToUms(tPA, tUms);	
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfStopDual_Cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsConfStopDual_Ind:
		{
			TPAConfEpID& tPA = *(TPAConfEpID*)pBuf;
			EmTPDualReason& emReason = *(EmTPDualReason*)(pBuf + sizeof(TPAConfEpID));
			
			TConfEpID tUms;
			ConvertConfEpIDFromStackToUms(tPA, tUms);
			
			u8 byBuf[sizeof(TConfEpID) + sizeof(EmTPDualReason)] = {0};
			memcpy(byBuf, &tUms, sizeof(TConfEpID));
			memcpy(byBuf + sizeof(TConfEpID), &emReason, sizeof(EmTPDualReason));			
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfStopDual_Ind, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, byBuf, sizeof(byBuf));	
		}
		break;
	case ev_UmsConfDualEp_Nty:
		{
			TPAConfEpID& tPA = *(TPAConfEpID*)pBuf;
			
			TConfEpID tUms;
			ConvertConfEpIDFromStackToUms(tPA, tUms);	
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfDualEp_Nty, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsConfAMixVacSwitch:
		{
			TPAConfAuxMixVacOpr& tPA = *(TPAConfAuxMixVacOpr*)pBuf;
			TConfAuxMixVacOpr tUms;

			tUms.m_wConfID = tPA.m_wConfID;
			tUms.m_bVacOn = tPA.m_bVacOn;
			tUms.m_wOprRet = tPA.m_wOprRet;

			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsConfAMixVacSwitch, ConfID:%d, EpID:%d, bVacOn:%d\n", 
				wConfID, wEpID, tUms.m_bVacOn));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case ev_UmsAudMixDisListOpr_Cmd:
		{
			TPADisListOpr& tPA = *(TPADisListOpr*)pBuf;
			TDiscussListOpr tUms;

			tUms.m_wConfId = tPA.m_wConfId;
			tUms.m_wNum = tPA.m_wNum;
			for (u16 wIndex = 0; wIndex < tPA.m_wNum; wIndex++)
			{
				tUms.m_awEpId[wIndex] = tPA.m_awEpId[wIndex];
                tUms.m_aemRet[wIndex] = (EmDiscussOprRes)tPA.m_adwRet[wIndex];

			}
			
			switch( tPA.m_dwOprType )
			{
			case emPA_DisListOpr_Add:
				tUms.m_emOprType = em_DisListOpr_Add;
				break;
			case emPA_DisListOpr_Del:
				tUms.m_emOprType = em_DisListOpr_Del;
				break;
			default:
				MdlError(Ums_Mdl_Stack, ( "ev_UmsAudMixDisListOpr_Cmd, EmPADisListOprType Error! umsOprType:%d", tPA.m_dwOprType));
				break;
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsAudMixDisListOpr_Cmd, ConfID:%d, EpID:%d, Num:%d, OprType:%d\n", 
				wConfID, wEpID, tUms.m_wNum, tUms.m_emOprType));

			for (u16 wI = 0; wI < tPA.m_wNum; wI++)
			{
				MdlHint(Ums_Mdl_Stack, ("  <<<< [%d] List EpId:%d.\n", wI, tPA.m_awEpId[wI]));
			}
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));	
		}
		break;
	case ev_UmsCommonReasonToUI_Ind:
		{
			TPAUmsReasonInd& tPa = *(TPAUmsReasonInd*)pBuf;
			
			TTPUmsReasonInd tUms;
			tUms.m_wConfID = tPa.m_wConfID;
			tUms.m_wEpID = tPa.m_wEpID;
			tUms.m_dwReason = tPa.m_dwReason;
			tUms.m_dwReserve1 = tPa.m_dwReserve1;
			tUms.m_dwReserve2 = tPa.m_dwReserve2;
			tUms.m_dwReserve3 = tPa.m_dwReserve3;

			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UmsCommonReasonToUI_Ind, ConfID:%d, EpID:%d, CallID:%d, DstEPID:%d, Reason:%d, Reserve1:%d, Reserve2:%d, Reserve3:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wEpID, tUms.m_dwReason, tUms.m_dwReserve1, tUms.m_dwReserve2, tUms.m_dwReserve3));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_cascade_OpenChairChan_cmd:
		{
			TPACascadeOpenChanCmd* ptPA = (TPACascadeOpenChanCmd*)pBuf;
			TCascadeOpenChanCmd tUms;

			ConvertCascadeOpenChanCmdFromStackToUms(tUms, *ptPA);
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_cascade_OpenChairChan_cmd, ConfID:%d, EpID:%d\n", wConfID, wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));				
		}
		break;
	case evtp_cascade_OpenChairChan_ack:
		{
			TPACascadeOpenChanAck* ptPA = (TPACascadeOpenChanAck*)pBuf;
			TCascadeOpenChanAck tUms;
			
			ConvertCascadeOpenChanAckFromStackToUms(tUms, *ptPA);
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_cascade_OpenChairChan_ack, ConfID:%d, EpID:%d, ret:%d\n", wConfID, wEpID, tUms.m_wEpID));
			
			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));			
		}
		break;

	case evtp_Conf_StopRecPlay_Req:
		{
			u32 dwParam = 0;
			TP_SAFE_CAST(dwParam, pBuf);
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_StopRecPlay_Req, Param:%d.\n", dwParam));

			NotifyMsgToCall(wEvent, tHandle, &dwParam, sizeof(u32));
		}
		break;

	case evtp_Conf_RecPlayState_Nty:
		{
			TPAUmsUpRecPlayState tState;
			TP_SAFE_CAST(tState, pBuf);
			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_RecPlayState_Nty, IsPlaying:%d, DualPlaying:%d, FileName:%d.\n",
									tState.m_bIsPlayIng, tState.m_bIsDualPlayIng,
									tState.m_achFileName));

			TUpRecPlayState tInfo;
			tInfo.m_bIsPlayIng = tState.m_bIsPlayIng;
			tInfo.m_bIsDualPlayIng = tState.m_bIsDualPlayIng;
			memcpy(tInfo.m_achFileName, tState.m_achFileName, TP_REC_FILE_LEN);
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(TUpRecPlayState));
		}
		break;

	case evtp_Conf_ResetFastUpdate:
		{
			u32 dwVal = 0;
			TP_SAFE_CAST(dwVal, pBuf);

			MdlHint(Ums_Mdl_Stack, ("<<< evtp_Conf_ResetFastUpdate EpID:%d\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, &dwVal, sizeof(u32));
		}
		break;

	case ev_UMS_CNC_SelView_Ntfy:
		{
			TTPSelViewNtfy tNtfy;

			TPASelViewNtfy tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);
			
			ConvertSelViewNtfyFromStackToUms(tPa, tNtfy);

			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UMS_CNC_SelView_Ntfy confID:%d, epId:%d, (%d,%d; %d,%d; %d,%d;)\n", 
				tNtfy.m_wConfID, tNtfy.m_wEpID, 
				tNtfy.m_atSelView[0].m_wDstID, tNtfy.m_atSelView[0].m_emType,
				tNtfy.m_atSelView[1].m_wDstID, tNtfy.m_atSelView[1].m_emType,
				tNtfy.m_atSelView[2].m_wDstID, tNtfy.m_atSelView[2].m_emType));
			
			NotifyMsgToCall(wEvent, tHandle, &tNtfy, sizeof(tNtfy));
		}
		break;
	case ev_UMS_CNC_SelView_Ind:
		{
			TTPSelViewInd tInd;

			TPATPSelViewInd tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);
			
			ConvertSelViewIndFromStackToUms(tPa, tInd);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UMS_CNC_SelView_Ind Ret:%d, EpID:%d, ScrIndx:%d, DstID:%d\n",
				tInd.m_emRet, tInd.m_tSelView.m_wEpID, tInd.m_tSelView.m_wScreenIndx, tInd.m_tSelView.m_wDstID));
			
			NotifyMsgToCall(wEvent, tHandle, &tInd, sizeof(tInd));
		}
		break;
	case ev_CNC_UMS_SelView_Req:
		{
			TTPSelViewReq tReq;

			TPATPSelViewReq tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);
			
			ConvertSelViewReqFromStackToUms(tPa, tReq);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_CNC_UMS_SelView_Req bSel:%d, EpID:%d, ScrIndx:%d, DstID:%d, Type:%d.\n",
				tReq.m_bSel, tReq.m_wEpID, tReq.m_wScreenIndx, tReq.m_wDstID, tReq.m_emType));
			
			NotifyMsgToCall(wEvent, tHandle, &tReq, sizeof(tReq));
		}
		break;

	case ev_GetVid_Req:
		{
			TPAGetVidInfo tPaInfo;
			TP_SAFE_CAST(tPaInfo, (u8*)pBuf);

			TGetVidInfo tInfo;
			ConvertGetVidInfoFromStackToUms(tPaInfo, tInfo);
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_GetVid_Req Handle:%d, EpID:%d, Type:%d, bSmall:%d.\n", 
									tInfo.m_tBaseInfo.m_wHandle, tInfo.m_tBaseInfo.m_wEpID,
									tInfo.m_tBaseInfo.m_emType, tInfo.m_bSamll));

			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));	
		}
		break;

	case ev_GetVid_Res:
		{
			TPAGetVidInfoRes tPaInfo;
			TP_SAFE_CAST(tPaInfo, (u8*)pBuf);

			TGetVidInfoRes tInfo;
			ConvertGetVidResFromStackToUms(tPaInfo, tInfo);
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_GetVid_Res Handle:%d, EpID:%d, Type:%d, Res:%d, bSmall:%d.\n",
									tInfo.m_tInfo.m_tBaseInfo.m_wHandle, tInfo.m_tInfo.m_tBaseInfo.m_wEpID,
									tInfo.m_tInfo.m_tBaseInfo.m_emType, tInfo.m_emRes, tInfo.m_tInfo.m_bSamll));

			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));	
		}
		break;

	case ev_GetVid_Stop_Req:
		{
			TPAGetVidBaseInfo tPaInfo;
			TP_SAFE_CAST(tPaInfo, (u8*)pBuf);

			TGetVidBaseInfo tInfo;
			ConvertGetVidBaseInfoFromStackToUms(tPaInfo, tInfo);
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_GetVid_Stop_Req Handle:%d, EpID:%d, Type:%d.\n",
									tInfo.m_wHandle, tInfo.m_wEpID, tInfo.m_emType));

			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
		break;

	case ev_GetVid_Stop_Res:
		{
			TPAStopGetVid tPaInfo;
			TP_SAFE_CAST(tPaInfo, (u8*)pBuf);

			TStopGetVid tInfo;
			ConvertGetVidStopResFromStackToUms(tPaInfo, tInfo);
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_GetVid_Stop_Res Handle:%d, EpID:%d, Type:%d, Res:%d.\n",
									tInfo.m_tInfo.m_wHandle, tInfo.m_tInfo.m_wEpID, tInfo.m_tInfo.m_emType, tInfo.m_emRes));
			
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
		break;

	case evtp_Conf_SuspendPoll_Req:
		{
			BOOL32 bSuspend;
			TP_SAFE_CAST(bSuspend, (u8*)pBuf);

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_SuspendPoll_Req EpID:%d, Suspend:%d\n", tHandle.GetEpID(), bSuspend));

			NotifyMsgToCall(wEvent, tHandle, &bSuspend, sizeof(bSuspend));
		}
		break;
	case evtp_Conf_CasecadePollEp_Req:
		{
			TPACasecadePollEpReq tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);

			TCasecadePollEpReq tReq;

			ConvertCasecadePollEpReqFromStackToUms(tPa, tReq);

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_CasecadePollEp_Req EpID:%d bCreate:%d, EpID:%d, Rtp(%d, %d, %d).\n",
				tHandle.GetEpID(), tReq.m_bCreate, tReq.m_wEpID, tReq.m_atPollAddr[0].GetPort(), tReq.m_atPollAddr[1].GetPort(), tReq.m_atPollAddr[2].GetPort()));
			
			NotifyMsgToCall(wEvent, tHandle, &tReq, sizeof(tReq));
		}
		break;
	case evtp_Conf_CasecadePollEp_Rsp:
		{
			TCasecadePollEpRsp tRsp;

			TPACasecadePollEpRsp tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);

			ConvertCasecadePollEpReqFromStackToUms(tPa.m_tReq, tRsp.m_tReq);
			tRsp.m_emRes = (EmTPPollResult)tPa.m_emRes;

			MdlHint(Ums_Mdl_Stack, ("<<<< evtp_Conf_CasecadePollEp_Rsp EpID:%d bCreate:%d, EpID:%d, Rtp(%d, %d, %d) Ret:%d.\n",
				tHandle.GetEpID(), tRsp.m_tReq.m_bCreate, tRsp.m_tReq.m_wEpID, 
				tRsp.m_tReq.m_atPollAddr[0].GetPort(), tRsp.m_tReq.m_atPollAddr[1].GetPort(), tRsp.m_tReq.m_atPollAddr[2].GetPort(), tRsp.m_emRes));
			NotifyMsgToCall(wEvent, tHandle, &tRsp, sizeof(tRsp));
		}
		break;

	case ev_CNC_UMS_RervesBrdVmp_Req:
		{
			TRersvesEqpReq tRsp;
			
			TPARersvesEqpReq tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);
			
			tRsp.m_wConfID = tPa.m_wConfID;
			tRsp.m_bRersves = tPa.m_bRersves;
			ConvertEqpInfoFromStackToUms(tPa.m_tEqp, tRsp.m_tEqp);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_CNC_UMS_RervesBrdVmp_Req EpID:%d ConfID:%d, Rersves:%d, EqpID%d.\n",
							tHandle.GetEpID(), tRsp.m_wConfID, tRsp.m_bRersves, tRsp.m_tEqp.m_byEqpID));
			NotifyMsgToCall(wEvent, tHandle, &tRsp, sizeof(tRsp));
		}
		break;

	case ev_CNC_UMS_SetBrdVmp_Req:
		{
			TSetVmpInfoReq tRsp;
			
			TPASetVmpInfoReq tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);
			
			tRsp.m_wConfID = tPa.m_wConfID;
			ConvertEqpInfoFromStackToUms(tPa.m_tEqp, tRsp.m_tEqp);
			ConvertVmpStyleInfoFromStackToUms(tPa.m_tStyle, tRsp.m_tStyle);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_CNC_UMS_SetBrdVmp_Req EpID:%d ConfID:%d, EqpID:%d, Style:%d, speakerindx:%d, dualIndx:%d.\n",
				tHandle.GetEpID(), tRsp.m_wConfID, tRsp.m_tEqp.m_byEqpID, tRsp.m_tStyle.m_emVmpStyle, tRsp.m_tStyle.m_wSpeakerIndx, tRsp.m_tStyle.m_wDualIndx));
			NotifyMsgToCall(wEvent, tHandle, &tRsp, sizeof(tRsp));
		}
		break;

	case ev_CNC_UMS_BrdVmp_Req:
		{
			TBrdVmpReq tRsp;
			
			TPABrdVmpReq tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);
			
			tRsp.m_wConfID = tPa.m_wConfID;
			tRsp.m_bBrd = tPa.m_bBrd;
			ConvertEqpInfoFromStackToUms(tPa.m_tEqp, tRsp.m_tEqp);
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_CNC_UMS_BrdVmp_Req EpID:%d ConfID:%d, EqpID:%d, bBrd:%d.\n",
				tHandle.GetEpID(), tRsp.m_wConfID, tRsp.m_tEqp.m_byEqpID, tRsp.m_bBrd));
			NotifyMsgToCall(wEvent, tHandle, &tRsp, sizeof(tRsp));
		}
		break;

	case ev_UMS_UMS_VmpCasecade_Ntfy:
		{
			TVmpCasecadeNtfy tRsp;
			
			TPAVmpCasecadeNtfy tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);
			
			tRsp.m_bBrdVmp = tPa.m_bBrdVmp;
			if (2 == tPa.m_bSpeakerVmp)
			{
				tRsp.m_emSpeakerVmpType = em_Speaker_In_Vmp;
			}
			else if (1== tPa.m_bSpeakerVmp)
			{
				tRsp.m_emSpeakerVmpType = em_Chair_In_Vmp;
			}
			else
			{
				tRsp.m_emSpeakerVmpType = em_Vmp_Invalid;
			}

			strncpy(tRsp.m_szBrdVmpAlias, tPa.m_szBrdVmpAlias, sizeof(tRsp.m_szBrdVmpAlias));
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_UMS_UMS_VmpCasecade_Ntfy EpID:%d ConfID:%d, BrdAlias:%s, bBrd:%d, emSpeakerVmp:%d.\n",
				tHandle.GetEpID(), tHandle.GetConfID(),tRsp.m_szBrdVmpAlias, tRsp.m_bBrdVmp, tRsp.m_emSpeakerVmpType));
			NotifyMsgToCall(wEvent, tHandle, &tRsp, sizeof(tRsp));
		}
		break;

	case ev_CNC_UMS_SaveVmpCfg_Cmd:
		{
			TTpVmpMemberCfg tUms;
			
			TPAVmpMemberCfg tPa;
			TP_SAFE_CAST(tPa, (u8*)pBuf);

			tUms.m_wConfID = tHandle.GetConfID();
			tUms.m_emStyle = (EMVmpStyle)tPa.m_emStyle;
			tUms.m_wTotalNum = tPa.m_wTotalNum;
			tUms.m_wEpNum = tPa.m_wEpNum;
			tUms.m_wFlag = tPa.m_wFlag;
			tUms.m_wDualIndx = tPa.m_wDualIndx;
			tUms.m_wSpeakerIndx = tPa.m_wSpeakerIndx;
			tUms.m_bFirst = tPa.m_bFirst;

			for ( u16 wIndex = 0; wIndex < tUms.m_wEpNum; wIndex ++ )
			{
				ConvertAliasFromStackToUms(tPa.m_atEpList[wIndex].m_tEpAlias, tUms.m_atEpList[wIndex].m_tEpAlias);
				tUms.m_atEpList[wIndex].m_wScrIndx = tPa.m_atEpList[wIndex].m_wScrIndx;
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<<< ev_CNC_UMS_SaveVmpCfg_Cmd EpID:%d ConfID:%d, Style:%d, EpNum:%d, Flag:%d\n",
				tHandle.GetEpID(), tUms.m_wConfID, tUms.m_emStyle, tUms.m_wEpNum, tUms.m_wFlag));

			NotifyMsgToCall(wEvent, tHandle, &tUms, sizeof(tUms));
		}
		break;
	case evtp_CnsJoinConf_Ack:
		{
			TTPConfEpInfo tUmsInfo;
			TPAConfEpInfo tPaInfo;
			TP_SAFE_CAST(tPaInfo, (u8*)pBuf);
			tUmsInfo.m_bPermit = tPaInfo.m_bPermit;
			tUmsInfo.m_Index = tPaInfo.m_Index;
			tUmsInfo.m_wConfID = tPaInfo.m_wConfID;
			ConvertAliasFromStackToUms(tPaInfo.m_tCallAddr.m_tAlias,tUmsInfo.m_tCallAddr.m_tAlias );
			ConvertAliasFromStackToUms(tPaInfo.m_tCallAddr.m_tE164,tUmsInfo.m_tCallAddr.m_tE164 );
			tUmsInfo.m_tCallAddr.m_dwIP = tPaInfo.m_tCallAddr.m_dwIP;
			ConvertCallTypeFromStackToUms(tPaInfo.m_tCallAddr.m_byCallType,tUmsInfo.m_tCallAddr.m_byCallType);
			tUmsInfo.m_tCallAddr.m_bAliasIP = tPaInfo.m_tCallAddr.m_bAliasIP;
			
			NotifyMsgToCall(wEvent, tHandle, &tUmsInfo, sizeof(tUmsInfo));
		}
		break;

		//////////////////////////////////////////////////////////////////////////
		//白板
	case evtp_JoinWBConf_Cmd:
		{
			u32 dwIP = 0;
			TP_SAFE_CAST(dwIP, pBuf);
			
			MdlHint(Ums_Mdl_Stack, ("<<< evtp_JoinWBConf_Cmd EpID:%d, IP:"IPFORMAT".\n", tHandle.GetEpID(), Tpu32ToIP(dwIP)));
			NotifyMsgToCall(wEvent, tHandle, &dwIP, sizeof(u32));
		}
		break;
		
	case evtp_JoinWBConf_Ind:
		{
			BOOL32 bSuccess = FALSE;
			TP_SAFE_CAST(bSuccess, pBuf);
			
			MdlHint(Ums_Mdl_Stack, ("<<< evtp_JoinWBConf_Ind EpID:%d, Res:%d.\n", tHandle.GetEpID(), bSuccess));
			NotifyMsgToCall(wEvent, tHandle, &bSuccess, sizeof(BOOL32));
		}
		break;
		
	case evtp_HungUpWBConf_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, ("<<< evtp_HungUpWBConf_Cmd EpID:%d.\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, NULL, 0);
		}
		break;
	//////////////////////////////////////////////////////////////////////////
	// 电视墙相关
	case evTPCNS_UMS_HduPlay_Req:
		{
			TPAHduPlayReq tPaReq;
			TTPHduPlayReq tReq; 
			TP_SAFE_CAST(tPaReq, pBuf);

			ConvertHduReqInfoFromStackToUms(tPaReq, tReq);
			
			MdlHint(Ums_Mdl_Stack, ("<<< evTPCNS_UMS_HduPlay_Req EpID:%d, EmType:%d, ConfID:%d, DstID:%d, BrdAlias:%s, ScreenNum:%d, Index:%d, SubIndex:%d, IsVmp:%d.\n",
					tHandle.GetEpID(), tReq.m_emType, tReq.m_wConfID, tReq.m_wDstID, 
					tReq.m_achAlias, tReq.m_wScreenNum, tReq.m_wIndex, tReq.m_bySubIndex,
					tReq.m_bVmp));
			NotifyMsgToCall(wEvent, tHandle, &tReq, sizeof(tReq));	
		}
		break;
	case evTPCNS_UMS_HduStopPlay_Req:
		{
			TPAHduPlayReq tPaReq;
			TTPHduPlayReq tReq; 
			TP_SAFE_CAST(tPaReq, pBuf);
			
			ConvertHduReqInfoFromStackToUms(tPaReq, tReq);
			
			MdlHint(Ums_Mdl_Stack, ("<<< evTPCNS_UMS_HduStopPlay_Req EpID:%d, EmType:%d, ConfID:%d, DstID:%d, BrdAlias:%s, ScreenNum:%d, Index:%d, SubIndex:%d, IsVmp:%d.\n",
				tHandle.GetEpID(), tReq.m_emType, tReq.m_wConfID, tReq.m_wDstID, 
				tReq.m_achAlias, tReq.m_wScreenNum, tReq.m_wIndex, tReq.m_bySubIndex,
				tReq.m_bVmp));
			NotifyMsgToCall(wEvent, tHandle, &tReq, sizeof(tReq));
		}
		break;
	case evTPCNS_UMS_HduStopAllPlay_Req:
		{
			MdlHint(Ums_Mdl_Stack, ("<<< evTPCNS_UMS_HduStopAllPlay_Req EpID:%d.\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, NULL, 0);
		}
		break;
	case evTPCNS_UMS_HduSetVol_Req:
		{
			TPAHduSetVolInfo tPaInfo;
			THduSetVolInfo tInfo;
			TP_SAFE_CAST(tPaInfo, pBuf);
			
			tInfo.m_tInfo.m_wIndex     = tPaInfo.m_tInfo.m_wIndex;
			tInfo.m_tInfo.m_bySubIndex = tPaInfo.m_tInfo.m_bySubIndex;
			tInfo.m_byVol              = tPaInfo.m_byVol;
			tInfo.m_bMute              = tPaInfo.m_bMute;
			
			MdlHint(Ums_Mdl_Stack, ("<<< evTPCNS_UMS_HduSetVol_Req EpID:%d, HduInfo.index: %d, HduInfo.SubIndex:%d, byVol:%d, IsMute:%d.\n",
				tHandle.GetEpID(), tInfo.m_tInfo.m_wIndex, tInfo.m_tInfo.m_bySubIndex, tInfo.m_byVol, tInfo.m_bMute));

			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
		break;
	case evTPCNS_UMS_HduChangeChanMode_Req:
		{
			TPAHduChanModeSetInfo tPaInfo;
			THduChanModeSetInfo tInfo;
			TP_SAFE_CAST(tPaInfo, pBuf);

			tInfo.m_wIndex = tPaInfo.m_wIndex;
			tInfo.m_byMode = tPaInfo.m_byMode;
			
			MdlHint(Ums_Mdl_Stack, ("<<< evTPCNS_UMS_HduChangeChanMode_Req EpID:%d, Index:%d, Mode:%d.\n",
				tHandle.GetEpID(), tInfo.m_wIndex, tInfo.m_byMode));
			
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));	
		}
		break;


    case ev_UmsConfRollCallUpdate_Cmd:
		{
			TPAConfRollCallInfo tPaInfo;
			TConfRollCallInfo tInfo;
			TP_SAFE_CAST(tPaInfo, pBuf);

			tInfo.m_wConfID = tPaInfo.m_wConfID;
			tInfo.m_bStart = tPaInfo.m_bStart;
			tInfo.m_emRet  = (EmRollCallRspRet)tPaInfo.m_dwRet;
			tInfo.m_atRollCallMemList.m_wNum        = tPaInfo.m_atRollCallMemList.m_wNum;
			tInfo.m_atRollCallMemList.m_wRollCaller = tPaInfo.m_atRollCallMemList.m_wRollCaller;
			tInfo.m_atRollCallMemList.m_wCallTarget = tPaInfo.m_atRollCallMemList.m_wCallTarget;
			for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
			{
                tInfo.m_atRollCallMemList.m_awList[wIndex] = tPaInfo.m_atRollCallMemList.m_awList[wIndex];
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<< ev_UmsConfRollCallUpdate_Cmd EpID:%d\n", tHandle.GetEpID()));
			
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
		break;


	case ev_UmsConfRollCallNextEp_Cmd:
		{
			TPARollCallNextEpInfo tPaInfo;
			TRollCallNextEpInfo tInfo;
            TP_SAFE_CAST(tPaInfo, pBuf);

			tInfo.m_wConfID = tPaInfo.m_wConfID;
			tInfo.m_wRollCaller = tPaInfo.m_wRollCaller;
			tInfo.m_wCallTarget = tPaInfo.m_wCallTarget;
			tInfo.m_emRet       = (EmRollCallRspRet)tPaInfo.m_dwRet;

			MdlHint(Ums_Mdl_Stack, ("<<< ev_UmsConfRollCallNextEp_Cmd EpID:%d  RollCaller = %d CallTarget = %d\n", 
				                    tHandle.GetEpID(), tInfo.m_wRollCaller, tInfo.m_wCallTarget));
			
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));

		}
        break;

	case evtp_UmsRollCallScreenStat_Notify:
		{

			TPARollCallCasecadeNtfy tPaInfo;
			TRollCallCasecadeNtfy tInfo;
            TP_SAFE_CAST(tPaInfo, pBuf);

            EmPAAliasType	emPaType;  
            tInfo.m_NotyType = (EMRollCallNotyToLowUmsType)tPaInfo.m_dwNotyType;
			tInfo.m_bIsRollCallModle = tPaInfo.m_bIsRollCallModle;
			for(u16 wIndex = 0; wIndex < NUM_OF_CALLER_AND_TARGET; wIndex++)
			{
                 tInfo.m_NodeInfo[wIndex].m_wEpId = tPaInfo.m_NodeInfo[wIndex].m_wEpId;
				 tInfo.m_NodeInfo[wIndex].m_wVidSndNum = tPaInfo.m_NodeInfo[wIndex].m_wVidSndNum;
				 tInfo.m_NodeInfo[wIndex].m_wVidRcvNum = tPaInfo.m_NodeInfo[wIndex].m_wVidRcvNum;
				 tInfo.m_NodeInfo[wIndex].m_wAudSndNum = tPaInfo.m_NodeInfo[wIndex].m_wAudSndNum;
				 tInfo.m_NodeInfo[wIndex].m_wAudRcvNum = tPaInfo.m_NodeInfo[wIndex].m_wAudRcvNum;
				 tInfo.m_NodeInfo[wIndex].m_wSpeakerSeat = tPaInfo.m_NodeInfo[wIndex].m_wSpeakerSeat;


				 memcpy(tInfo.m_NodeInfo[wIndex].m_Alias.m_abyAlias, tPaInfo.m_NodeInfo[wIndex].m_Alias.m_achAlias, sizeof(tInfo.m_NodeInfo[wIndex].m_Alias.m_abyAlias));
				 
				 emPaType = tPaInfo.m_NodeInfo[wIndex].m_Alias.m_emType;
				 if (emPA_Alias_e164 == emPaType)
				 {
                     tInfo.m_NodeInfo[wIndex].m_Alias.m_byType = tp_Alias_e164;
				 }else if(emPA_Alias_h323 == emPaType )
				 {
                     tInfo.m_NodeInfo[wIndex].m_Alias.m_byType = tp_Alias_h323;
				 }else if(emPA_Alias_IP == emPaType)
				 {
                     tInfo.m_NodeInfo[wIndex].m_Alias.m_byType = tp_Alias_IP;
				 }else
				 {
				     tInfo.m_NodeInfo[wIndex].m_Alias.m_byType = tp_Alias_Unknow;
				 }
                   
			}

			MdlHint(Ums_Mdl_Stack, ("<<< evtp_UmsRollCallScreenStat_Notify EpID:%d\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}

		break;

	case ev_UmsConfRollCallUpdate_Nty:
		{
		    // 状态通知消息，cns 处理，ums 不需要处理
			MdlHint(Ums_Mdl_Stack, ("<<< ev_UmsConfRollCallUpdate_Nty EpID:%d\n", tHandle.GetEpID()));
		}
		break;

	case ev_UmsConfRollCallUpdataList_Cmd:
		{
			TPAUpdataRollCallList tPaInfo;
			TUpdataRollCallList tInfo;
            TP_SAFE_CAST(tPaInfo, pBuf);

            tInfo.m_wConfID = tPaInfo.m_wConfID;
            tInfo.m_bAdd  =   tPaInfo.m_bAdd;
            tInfo.m_atRollCallMemList.m_wNum        = tPaInfo.m_atRollCallMemList.m_wNum;
			tInfo.m_atRollCallMemList.m_wRollCaller = tPaInfo.m_atRollCallMemList.m_wRollCaller;
            tInfo.m_atRollCallMemList.m_wCallTarget = tInfo.m_atRollCallMemList.m_wCallTarget;

			for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
			{
                tInfo.m_atRollCallMemList.m_awList[wIndex] = tPaInfo.m_atRollCallMemList.m_awList[wIndex];
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<< ev_UmsConfRollCallUpdataList_Cmd EpID:%d\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
        break;

	//主席过来更新点名答到状态消息
	case evtp_UmsRollUpdate_PresentState:
		{
			TPARollCallPresentStateMsg tPaInfo;
			TRollCallPresentStateMsg tInfo;
            TP_SAFE_CAST(tPaInfo, pBuf);

            tInfo.m_wConfID   = tPaInfo.m_wConfID;
            tInfo.m_wValidNum = tPaInfo.m_wValidNum;
			for(u16 wIndex = 0; wIndex < TP_MAX_ROLLCALL_NUM; wIndex++)
			{
                tInfo.m_atEpState[wIndex].m_wEpID    = tPaInfo.m_atEpState[wIndex].m_wEpID;
				tInfo.m_atEpState[wIndex].m_wEpState = tPaInfo.m_atEpState[wIndex].m_wEpState;
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<< evtp_UmsRollUpdate_PresentState EpID:%d\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
		break;

	case evtp_CNS_UMS_ConfAudMixMode_cmd:
		{	
			TPAUmsAudMixInfo tPaInfo;
			TUmsAudMixInfo tInfo;
            TP_SAFE_CAST(tPaInfo, pBuf);

            tInfo.m_wConfId = tPaInfo.m_wConfId;
            tInfo.m_emMode  = (EmUmsAudMixMode)tPaInfo.m_dwMode;
            tInfo.m_tMixList.m_wNum = tPaInfo.m_tMixList.m_wNum;

			for(u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
                tInfo.m_tMixList.m_awMixEp[wIndex] = tPaInfo.m_tMixList.m_awMixEp[wIndex];
			}

			MdlHint(Ums_Mdl_Stack, ("<<< evtp_CNS_UMS_ConfAudMixMode_cmd EpID:%d\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
		break;

	case evtp_CNS_UMS_ConfAudMixList_cmd:
		{
			TPAUmsAudMixListCmd tPaInfo;
			TUmsAudMixListCmd tInfo;
            TP_SAFE_CAST(tPaInfo, pBuf);

			tInfo.m_wConfId = tPaInfo.m_wConfId;
            tInfo.m_emOpr   = (EmUmsAudMixListOpr)tPaInfo.m_dwOpr;

			tInfo.m_tList.m_wNum = tPaInfo.m_tList.m_wNum;
			for(u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
                tInfo.m_tList.m_awMixEp[wIndex] = tPaInfo.m_tList.m_awMixEp[wIndex];
			}
			
			MdlHint(Ums_Mdl_Stack, ("<<< evtp_CNS_UMS_ConfAudMixList_cmd EpID:%d\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));	
		}
		break;

	case evtp_UMS_CNS_ConfAudMixMode_Notify:
		{
 	        // 状态通知消息，cns 处理，ums 不需要处理
			MdlHint(Ums_Mdl_Stack, ("<<< evtp_UMS_CNS_ConfAudMixMode_Notify EpID:%d\n", tHandle.GetEpID()));	
		}
		break;

	case evtp_UMS_UMS_ConfAudMixMode_Notify:
		{
			TPAUmsAudMixCasecadeInfo tPaInfo;
			TUmsAudMixCasecadeInfo tInfo;
            TP_SAFE_CAST(tPaInfo, pBuf);

            tInfo.m_emMode = (EmUmsAudMixMode)tPaInfo.m_dwMode;
            tInfo.m_dwReserve = tPaInfo.m_dwReserve;
            tInfo.m_dwReserve1 = tPaInfo.m_dwReserve1;

			MdlHint(Ums_Mdl_Stack, ("<<< evtp_UMS_UMS_ConfAudMixMode_Notify EpID:%d\n", tHandle.GetEpID()));
			NotifyMsgToCall(wEvent, tHandle, &tInfo, sizeof(tInfo));
		}
		break;
	// 远遥下级通知上级 远遥信息
	case evtp_Conf_EpVidFeccInfo_Update:
		{
			TPAConfEpVidFeccList tPaList;
			TP_SAFE_CAST(tPaList, pBuf);
			TConfEpVidFeccList	tList;

			ConvertFeccConfEpListFromStackToUms(tPaList, tList);
			MdlHint(Ums_Mdl_Stack, (">>>>UmsCBConfCtrlTP::evtp_Conf_EpVidFeccInfo_Update, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TVidFeccInfo* ptFeccInfo = NULL;
			TVidSourceInfo* ptVidInfo = NULL;
			for (u16 wIndex = 0; wIndex < tList.m_wNum; ++wIndex)
			{
				ptFeccInfo = &tList.m_atList[wIndex].m_tVidFeccInfo;
				ptVidInfo  = &tList.m_atList[wIndex].m_tVidFeccInfo.m_tVidSourceInfo;
				MdlLowHint(Ums_Mdl_Stack, (">>>>UmsCBConfCtrlTP:: evtp_Conf_EpVidFeccInfo_Update wEpId:%d, bAllowFecc:%d, byVidNo:%d, byVidNum:%d\n", 
					ptFeccInfo->m_wEpID, ptFeccInfo->m_bAllowFecc, ptFeccInfo->m_byVidno, ptVidInfo->m_byNum));
				
				for (u16 wVidIndex = 0; wVidIndex < ptVidInfo->m_byNum; ++wVidIndex)
				{
					MdlLowHint(Ums_Mdl_Stack, ("UmsCBConfCtrlTP::evtp_Conf_EpVidFeccInfo_Update byVidIndex:%d, byVidAlias:%s\n", 
						ptVidInfo->m_atVidInfo[wVidIndex].m_byIndex, ptVidInfo->m_atVidInfo[wVidIndex].m_abyAlias));
				}
				
			}

			NotifyMsgToCall(wEvent, tHandle, &tList, sizeof(tList));

		}
		break;

	case evtp_MediaKey_Nty:
		{
			//Protocol_file
			TPAQTMediaKeyInfo& tPaInfo = *(TPAQTMediaKeyInfo*)pBuf;
			TTPMediaKeyInfo tTpInfo;
			tTpInfo.m_dwHandle = tPaInfo.m_dwHandle;
			tTpInfo.m_wIndex = tPaInfo.m_wIndex;
			
			memcpy(tTpInfo.m_szMediaKey1, tPaInfo.m_szMediaKey1, PA_MAX_MEDIAKEY_LEN/4);
			memcpy(tTpInfo.m_szMediaKey2, tPaInfo.m_szMediaKey2, PA_MAX_MEDIAKEY_LEN/4);
			memcpy(tTpInfo.m_szMediaKey3, tPaInfo.m_szMediaKey3, PA_MAX_MEDIAKEY_LEN/4);
			memcpy(tTpInfo.m_szMediaKey4, tPaInfo.m_szMediaKey4, PA_MAX_MEDIAKEY_LEN/4);
			
			tTpInfo.m_dwKeyLen = tPaInfo.m_dwKeyLen;
			ConvertEpEncryptLevelFromStackToUms(tPaInfo.m_emKeyFrequency, tTpInfo.m_emKeyFrequency);
			tTpInfo.m_dwQtFlag = tPaInfo.m_dwQtFlag;
			
			MdlHint(Ums_Mdl_Stack, ("<<< evtp_MediaKey_Nty EpID:%d, emKeyFrequency:%d, dwHandle:%d, wIndex:%d, dwKeyLen:%d.\n", 
				tHandle.GetEpID(), tPaInfo.m_emKeyFrequency, tPaInfo.m_dwHandle, tPaInfo.m_wIndex, tPaInfo.m_dwKeyLen));
			NotifyMsgToCall(wEvent, tHandle, &tTpInfo, sizeof(tTpInfo));
		}

		break;

	default:
		MdlError(Ums_Mdl_Stack, ("<<<< UmsCBConfCtrl failed. unkonw msg type.  ConfID:%d, epID:%d, event:%d\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType));
		break;
	}

	return TRUE;
}

BOOL PA_CALLBACK UmsCBChanCtrlTP(HMDLCALL hPACall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, s32 nMsgType, u8* pBuf, s32 nSize)
{
	TUmsHandle tHandle;
	tHandle.handAppCall = (u32)hAppCall;
	tHandle.handPaCall = (u32)hPACall;
	tHandle.handPaChan = (s32)hChan;
	switch(nMsgType)
	{
	case emPAConfFastUpdate:
		{
			tpLowDtl(Ums_Mdl_Stack, "<< UmsCBChanCtrlTP AskKey ConfID:%d, epID:%d, ChanID:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), hChan);
			NotifyMsgToCall(evtp_Conf_AskKeyFrame, tHandle, NULL, 0);	
		}
		break;
	case emPAChanMeetingSpeaker:
		{
			s32 nChanID = 0;
			u8 chChanID = 0;
			if (NULL != pBuf)
			{
				TP_SAFE_CAST(nChanID, pBuf);
				tpLowDtl(Ums_Mdl_Stack, "<< UmsCBChanCtrlTP ChanMeetingSpeaker chanID%x\n", nChanID);
				if (nChanID > TP_MAX_STREAMNUM)
				{
					chChanID = (u8)((nChanID & 0xFF000000)>>24);  //取高字节
				}
				else
				{
					chChanID = (u8)(nChanID);
				}
			}
			else
			{
				MdlError(Ums_Mdl_Stack, ("emPAChanMeetingSpeaker buf is NULL!!!\n"));
			}

			MdlHint(Ums_Mdl_Stack, ("<< UmsCBChanCtrlTP cns speaker ConfID:%d, epID:%d, ChanID:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), chChanID));
			NotifyMsgToCall(evtp_Conf_CnsSpeaker_Notify, tHandle, &chChanID, sizeof(chChanID));
		}
		break;
	case emPAChanSelecteCascad:
		{
			u16 tPa = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, ("<< UmsCBChanCtrlTP cns view ConfID:%d, epID:%d, ChanID:%d, dstEp:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), hChan, tPa));
			NotifyMsgToCall(evtp_Conf_ViewObj_Req, tHandle, &tPa, sizeof(tPa));
		}
		break;
	case emPAChanSelecteCascadCancel:
		{
			MdlHint(Ums_Mdl_Stack, ("<< UmsCBChanCtrlTP cns cancel view ConfID:%d, epID:%d, ChanID:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), hChan));
			NotifyMsgToCall(evtp_Conf_UndoViewObj_Req, tHandle, NULL, 0);
		}
		break;
	default:
		MdlError(Ums_Mdl_Stack, ("UmsCBChanCtrlTP failed. unkonw msg type.  ConfID:%d, epID:%d, event:%d\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType));
		break;
	}

	return TRUE;
}

// BOOL PA_CALLBACK UmsCBDualStreamReject(HMDLCALL hPACall, HMDLAPPCALL hAppCall, HMDLCHANNEL hPAChan, HMDLAPPCHANNEL hAppChan)
// {
// 	TUmsHandle tHandle;
// 	tHandle.handAppCall = (u32)hAppCall;
// 	tHandle.handPaCall = (u32)hPACall;
// 	
// 	MdlHint(Ums_Mdl_Stack, ("<<UmsCBDualStreamReject ev_DualChan_DisConnect ConfID:%d, epID:%d, PACall:%d\n"
// 		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
// 	
// 	EmTPChannelReason emUms = emTPDualOffLine;
// 	NotifyMsgToCall(ev_DualChan_DisConnect, tHandle, (void*)&emUms, sizeof(emUms));
// 	
// 	return TRUE;
// }

// BOOL PA_CALLBACK UmsCBDualStreamStop(HMDLCALL hPACall, HMDLAPPCALL hAppCall, HMDLCHANNEL hPAChan, HMDLAPPCHANNEL hAppChan)
// {
// 	TUmsHandle tHandle;
// 	tHandle.handAppCall = (u32)hAppCall;
// 	tHandle.handPaCall = (u32)hPACall;
// 	
// 	MdlHint(Ums_Mdl_Stack, ("<<UmsCBDualStreamStop ev_DualChan_DisConnect ConfID:%d, epID:%d, PACall:%d\n"
// 		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall));
// 
// 	EmTPChannelReason emUms = emTPChannelDisconnectNormal;
// 	NotifyMsgToCall(ev_DualChan_DisConnect, tHandle, (void*)&emUms, sizeof(emUms));
// 
// 	return TRUE;
// }

 
// out
u16 UmsMakeCall(const TUmsHandle& tHandle, const TMakeCallPara& tCallPara)
{
	//TUDO 
	MdlHint(Ums_Mdl_Stack, (">> UmsMakeCall ConfID:%d, epID:%d, dst alias:%s,e164:%s,ip:"TPIPFORMAT", aliasType:%d, callProtocol:%d, confID:%d, bitrate = %d, IsCallEncry:%d \n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tCallPara.m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias
		, tCallPara.m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, Tpu32ToIP(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP)
        , tCallPara.m_tCallInfo.m_tDestAddr.m_byCallType
		, tCallPara.m_tCallInfo.m_emTpProtocol, tHandle.GetConfID(), tCallPara.m_tCallInfo.m_wBitRate
		, tCallPara.m_tCallInfo.m_tEncrypt.IsQt()
		));

	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makecall, (u8*)&tCallPara, tHandle, OUTSIGN);

	//协议转化
	EmPAConfProtocol emPaProtocol;
	ConvertCallProtocolParamFromUmsToStack(tCallPara.m_tCallInfo.m_emTpProtocol, emPaProtocol);

	//呼叫信息
	TModuleCallInfo tModuleInfo;
	TCallInfoTP tCallInfo;
	if (emPATypeH323 == emPaProtocol)
	{
		ConvertCallInfoFromUmsToStackForH323(tCallPara, tModuleInfo, tCallInfo);
	}
	else
	{
		ConvertCallInfoFromUmsToStack(tCallPara, tModuleInfo, tCallInfo);
	}
	
	tModuleInfo.m_tQtCallParam.m_dwConfID = tHandle.GetConfID();

	//码流密钥带下去协商
	ConverStreamKeyFromUmsToStack(tCallPara.m_tCallInfo.m_tEncrypt, tModuleInfo.m_tStreamKey);
   
	//呼叫能力
	TCallCapbility tSendCap, tRecvCap;
	TCallDescriptTP tSendTp, tRecvTp;

//	if(!CTpTypeAdpt::PortIsVaild(60010))
//	{
//		OspPrintf(1,0,"Port:%d is Inavlid!\n", 60010);
////		return TP_RET_OK;
//	}

	TBfcpCapSet tBfcp;
	tBfcp.m_wPort = UMS_BFCP_BEGIN_PORT;
	tBfcp.m_dwConfId = tHandle.handAppCall; //根据协议建议修改，保证不同呼叫此值也不同  //tHandle.GetConfID();
	tBfcp.m_wUserId = tHandle.GetEpID();
	tBfcp.m_emSetupAttr = emPassive;
	tBfcp.m_emFloorcontrolAttr = emServerOnly;
	tBfcp.m_emConnectionAttr = emNew;
	tBfcp.m_emBfcpSdpAttr = emUdpBfcp;
	
	TMMcuCapbility tMcuCap;
	if (tCallPara.m_tCallInfo.m_bIsCasecadeMcuOn)
	{
		tMcuCap.m_tListenAddress.SetIpAddr(GetLocalIpByDstIp(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP), UMS_MCU_LISTEN_PORT);
	}

	TFeccCapbility* ptFeccCapBility = NULL;
	TFeccCapbility tFeccBaility;
	u16 wSendPort = 0;
	u16 wRcvPort = 0;
	if (GetFeccUsablePort(wSendPort) && GetFeccUsablePort(wRcvPort) && wSendPort != wRcvPort)
	{
		tFeccBaility.m_tSendAddress.SetIpAddr(GetLocalIpByDstIp(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP), wSendPort);
		tFeccBaility.m_tRecvAddress.SetIpAddr(GetLocalIpByDstIp(tCallPara.m_tCallInfo.m_tDestAddr.m_dwIP), wRcvPort);
		tFeccBaility.m_byDirection = emFECCCapReceiveAndTransmit;
		tFeccBaility.m_wSampleRate = H244_H221_SAMPLE_RATE; // 6400 or 4800
		tFeccBaility.m_byDynamicPayload = MEDIA_TYPE_H224;// 100
		tpHint(Ums_Mdl_Stack, "<< UmsMakeCall rcvip:"TPIPFORMAT", rcvport:%d, sendip:"TPIPFORMAT", sendport:%d, direction:%d, SampleRate:%d, payLoad:%d.\n",
			Tpu32ToIP(tFeccBaility.m_tRecvAddress.m_dwIp), tFeccBaility.m_tRecvAddress.m_wPort,
			Tpu32ToIP(tFeccBaility.m_tSendAddress.m_dwIp), tFeccBaility.m_tSendAddress.m_wPort,
		tFeccBaility.m_byDirection, tFeccBaility.m_wSampleRate, tFeccBaility.m_byDynamicPayload);
		
		ptFeccCapBility = &tFeccBaility;
	}

	TDualCapList tDualCapList;
	ConverDualInfoFromUmsToStack(tDualCapList, tCallPara.m_tDualCapSet);

	ConvertCapFromUmsToStack(tCallPara, tSendCap, tRecvCap, tSendTp, tRecvTp);

	PA_MakeCall(emPaProtocol, (HMDLCALL*)&(tHandle.handPaCall), (HMDLAPPCALL)tHandle.handAppCall, 
		&tModuleInfo, &tSendCap, &tRecvCap, &tCallInfo, &tSendTp, &tRecvTp, &tDualCapList, 
				(HMDLAPPCONFID)tHandle.GetConfID(), NULL, &tBfcp, ptFeccCapBility, &tMcuCap);

	TCallMapInfo	tMapInfo;
	tMapInfo.m_dwAppCall = tHandle.handAppCall;
	tMapInfo.m_bIsMasterCall = TRUE;
	tMapInfo.m_bIsSip = (emPaProtocol == emPATypeSip)?TRUE:FALSE;
	tMapInfo.m_bCallConnect = FALSE;

	if (0 != tMapInfo.m_dwAppCall)
	{
		OspSemTake(g_hSemCallMap);
		g_mapCallMapInfo[tMapInfo.m_dwAppCall] = tMapInfo;
		OspSemGive(g_hSemCallMap);
	}

	return TP_RET_OK;
}



void UmsAnswerCall( const TUmsHandle& tHandle, const BOOL32 bAnwser, const TMakeCallPara* ptCallPara, EmCnsCallReason emReason)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsAnswerCall ConfID:%d, epID:%d, bAnwser:%d, PACall:%d, reason:%d, protocol:%d, confID:%d. BirRate:%d, IsQtEncrypt:%d\n",
		tHandle.GetConfID(), tHandle.GetEpID(), bAnwser, tHandle.handPaCall, emReason, ptCallPara->m_tCallInfo.m_emTpProtocol
		, tHandle.GetConfID(), ptCallPara->m_tCallInfo.m_wBitRate
		, ptCallPara->m_tCallInfo.m_tEncrypt.IsQt()
		));

	if (NULL == ptCallPara)
	{
		MdlHint(Ums_Mdl_Stack, (">> UmsAnswerCall ptCallPara = NULL\n"));
		return ;
	}

	if (!bAnwser)
	{
		EmModuleCallDisconnectReason emModuleReason;
		ConvertCallDisconnectReasonFromUmsToStack(emReason, emModuleReason);
		PA_RejectCall((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, emModuleReason);
	}
	else
	{
		if ( ptCallPara->m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias[0] != '\0' )
		{
			QtSetConfID( (s8*)ptCallPara->m_tCallInfo.m_tDestAddr.m_tE164.m_abyAlias, tHandle.GetConfID());

		}

		if ( ptCallPara->m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias[0] != '\0')
		{
			QtSetConfID( (s8*)ptCallPara->m_tCallInfo.m_tDestAddr.m_tAlias.m_abyAlias, tHandle.GetConfID());

		}

		if ( ptCallPara->m_tCallInfo.m_tDestAddr.m_dwIP != 0)
		{
            s8	abyIpAlias[TP_MAX_ALIAS_LEN + 1];
			sprintf(abyIpAlias, "%d.%d.%d.%d", Tpu32ToIP(ptCallPara->m_tCallInfo.m_tDestAddr.m_dwIP) );
            QtSetConfID( abyIpAlias, tHandle.GetConfID());

		}

		CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_answercall, (u8*)ptCallPara, tHandle, OUTSIGN);

		//协议转化
		EmPAConfProtocol emPaProtocol;
		ConvertCallProtocolParamFromUmsToStack(ptCallPara->m_tCallInfo.m_emTpProtocol, emPaProtocol);
		//呼叫信息
		TModuleCallInfo tModuleInfo;
		TCallInfoTP tCallInfo;

		if (emPATypeH323 == emPaProtocol)
		{
			ConvertCallInfoFromUmsToStackForH323(*ptCallPara, tModuleInfo, tCallInfo, TRUE);
		}
		else
		{
			ConvertCallInfoFromUmsToStack(*ptCallPara, tModuleInfo, tCallInfo, TRUE);
		}
        tModuleInfo.m_tQtCallParam.m_dwConfID = tHandle.GetConfID();
		
		//码流密钥带下去协商
		ConverStreamKeyFromUmsToStack(ptCallPara->m_tCallInfo.m_tEncrypt, tModuleInfo.m_tStreamKey);

		//呼叫能力
		TCallCapbility tSendCap, tRecvCap;
		TCallDescriptTP tSendTp, tRecvTp;

		ConvertCapFromUmsToStack(*ptCallPara, tSendCap, tRecvCap, tSendTp, tRecvTp);


		TBfcpCapSet tBfcp;
        u32 dwTempPort = 0;

		if (ptCallPara->m_tCallInfo.m_emTpCallType == emTpAnswerUms)
		{// 60011端口固定给bfcp用于客户端绑定，被ums呼叫，上级ums是服务端，这里下级ums是客户端
			//tBfcp.m_wPort = 60011;
            for( dwTempPort = UMS_BFCP_BEGIN_PORT+1; dwTempPort <= UMS_BFCP_END_PORT; dwTempPort++)
			{
		        if(CTpTypeAdpt::PortIsVaild(dwTempPort))
		        {
                    break;
		        }

			}

			if(dwTempPort > UMS_BFCP_END_PORT)
			{
			    EmModuleCallDisconnectReason emModuleReason = emModuleDisconnect_Local;
		        PA_RejectCall((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, emModuleReason);

				return;
			}
			else
			{
			    tBfcp.m_wPort = dwTempPort;
			}
		}
		else
		{// 60010端口固定给bfcp用于服务端绑定，被终端呼叫，ums还是服务端不变。
			tBfcp.m_wPort = UMS_BFCP_BEGIN_PORT;
		}

		tBfcp.m_dwConfId = tHandle.handAppCall; // 
		tBfcp.m_wUserId = tHandle.GetEpID();
		tBfcp.m_emSetupAttr = emPassive;
		tBfcp.m_emFloorcontrolAttr = emServerOnly;
		tBfcp.m_emConnectionAttr = emNew;
		tBfcp.m_emBfcpSdpAttr = emUdpBfcp;
		
		TDualCapList tDualCapList;
		ConverDualInfoFromUmsToStack(tDualCapList, ptCallPara->m_tDualCapSet);
		
		TMMcuCapbility tMcuCap;
		if (ptCallPara->m_tCallInfo.m_bIsCasecadeMcuOn)
		{
			tMcuCap.m_tListenAddress.SetIpAddr(GetLocalIpByDstIp(ptCallPara->m_tCallInfo.m_tDestAddr.m_dwIP), 3337);
		}
		
		TFeccCapbility* ptFeccCapBility = NULL;
		TFeccCapbility tFeccBaility;
		u16 wSendPort = 0;
		u16 wRcvPort = 0;
		if (GetFeccUsablePort(wSendPort) && GetFeccUsablePort(wRcvPort) && wSendPort != wRcvPort)
		{
			tFeccBaility.m_tSendAddress.SetIpAddr(GetLocalIpByDstIp(ptCallPara->m_tCallInfo.m_tDestAddr.m_dwIP), wSendPort);
			tFeccBaility.m_tRecvAddress.SetIpAddr(GetLocalIpByDstIp(ptCallPara->m_tCallInfo.m_tDestAddr.m_dwIP), wRcvPort);
			tFeccBaility.m_byDirection = emFECCCapReceiveAndTransmit;
			tFeccBaility.m_wSampleRate = H244_H221_SAMPLE_RATE; // 6400 or 4800
			tFeccBaility.m_byDynamicPayload = MEDIA_TYPE_H224;// 100
			tpHint(Ums_Mdl_Stack, "<< UmsAnswerCall rcvip:"TPIPFORMAT", rcvport:%d, sendip:"TPIPFORMAT", sendport:%d, direction:%d, SampleRate:%d, payLoad:%d.\n",
				Tpu32ToIP(tFeccBaility.m_tRecvAddress.m_dwIp), tFeccBaility.m_tRecvAddress.m_wPort,
				Tpu32ToIP(tFeccBaility.m_tSendAddress.m_dwIp), tFeccBaility.m_tSendAddress.m_wPort,
			tFeccBaility.m_byDirection, tFeccBaility.m_wSampleRate, tFeccBaility.m_byDynamicPayload);
			
			ptFeccCapBility = &tFeccBaility;
		}

		PA_AnwserCall((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, &tModuleInfo, &tSendCap, &tRecvCap, 
				  &tCallInfo, &tSendTp, &tRecvTp, &tDualCapList, (HMDLAPPCONFID)tHandle.GetConfID(), NULL, &tBfcp, ptFeccCapBility, &tMcuCap);

		TCallMapInfo	tMapInfo;
		tMapInfo.m_dwAppCall = tHandle.handAppCall;
		tMapInfo.m_bIsMasterCall = FALSE;
		tMapInfo.m_bIsSip = (emPaProtocol == emPATypeSip)?TRUE:FALSE;
		tMapInfo.m_bCallConnect = FALSE;

		if (0 != tMapInfo.m_dwAppCall)
		{
			OspSemTake(g_hSemCallMap);
			g_mapCallMapInfo[tMapInfo.m_dwAppCall] = tMapInfo;
			OspSemGive(g_hSemCallMap);
		}

	}
}



u16 UmsMakeChan(const TUmsHandle& tHandle, TUmsNodeCapset& tNodeCap, BOOL32 bIsDual)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsMakeChan ConfID:%d, epID:%d, IsDual:%d\n", tHandle.GetConfID(), tHandle.GetEpID(), bIsDual));
	CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makechan, (u8*)&tNodeCap, tHandle, OUTSIGN);

	TChanConnectedInfo patChanConnectInfo[15];
	u8 bySize = 15;	
	ConvertChanChangeParamFromUmsToStack(patChanConnectInfo, bySize, tNodeCap, bIsDual);
	
//	PA_ChangeChannel((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, patChanConnectInfo, bySize);
	return TP_RET_OK;
}

u16 UmsCloseChan(const TUmsHandle& tHandle, const EmChanType& emType, const TUmsNodeCapset& tNode)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsCloseChan ConfID:%d, epID:%d, ChanType:(%d->%s).\n"
			, tHandle.GetConfID(), tHandle.GetEpID(), TpEnumIdString(EmChanType, emType)));


	HMDLCHANNEL ahChan[3] = {0};
	HMDLAPPCHANNEL ahAppChan[3] = {0};
	u8 bySize = 0;
	BOOL32 bIsSnd = FALSE;
	BOOL32 bIsAud = FALSE;

	if (emChanSendPrimoVideo == emType || emChanSendSecondVideo == emType || emChanSendAudio == emType)
	{
		bIsSnd = TRUE;
	}
	
	if (emChanSendAudio == emType || emChanRecvAudio == emType)
	{
		bIsAud = TRUE;
	}

	if (bIsAud)
	{
		ConvertAudChanClosedParamFromUmsToStack(ahChan, ahAppChan, bySize, bIsSnd, tNode);
	}
	else
	{
		if (emChanSendSecondVideo == emType || emChanRecvSecondVideo == emType)
		{
			ConvertDualChanClosedParamFromUmsToStack(ahChan, ahAppChan, bySize, bIsSnd, tNode);
		}
		else
		{
			ConvertChanClosedParamFromUmsToStack(ahChan, ahAppChan, bySize, bIsSnd, tNode);
		}
	}

	MdlHint(Ums_Mdl_Stack, (">>UmsCloseChan ConfId:%d, epId:%d, ChanType:(%d->%s), IsSnd:%d, Chan[0]:%d, AppChan[0]:%d, Chan[1]:%d, AppChan[1]:%d, Chan[2]:%d, AppChan[2]:%d.\n"
							, tHandle.GetConfID(), tHandle.GetEpID(), TpEnumIdString(EmChanType, emType), bIsSnd, ahChan[0], ahAppChan[0], ahChan[1], ahAppChan[1], ahChan[2], ahAppChan[2]));
	PA_CloseChannel((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, ahChan, ahAppChan, bySize);

	return TP_RET_OK;
}

u16 UmsHangUp(const TUmsHandle& tHandle, EmCnsCallReason emReason)
{
	MdlHint(Ums_Mdl_Stack, (">> UmsHangUp ConfID:%d, epID:%d, PACall:%d, emReason:%d\n"
		, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, emReason));
	
	EmModuleCallDisconnectReason emModel;
	ConvertModuleDisReasonFromUmsToStack(emReason, emModel);
	PA_HangupCall((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, emModel);

	return TP_RET_OK;
}


u16 UmsSendChanCtrl( const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize )
{	
	switch(nMsgType)
	{
	case evtp_Conf_AskKeyFrame:
		{
			tpLowDtl(Ums_Mdl_Stack, ">> AskKeyFrame, ConfID:%d, EpID:%d, CallID:%d, ChanID:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, tHandle.handPaChan);
			PA_FastUpdate((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, (HMDLCHANNEL)tHandle.handPaChan,  0);
		}
		break;
	case evtp_Chan_FlowCtrol:
		{
			u16 wBand = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">> UmsFlowControl ConfID:%d, epID:%d, ChanID:%d band:%d\n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, wBand));
		
			PA_FlowControl((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, (HMDLCHANNEL)tHandle.handPaChan, NULL, wBand);
			//PA_SendChanCtrlTP((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, (HMDLCHANNEL)tHandle.handPaChan, emPAConfFlowCtrl, (u8*)&wBand, sizeof(wBand));

		}
		break;
	case evtp_Conf_ViewObj_Ind:
		{
			TChanViewRes tRes = *(TChanViewRes*)pBuf;
			TPAChanSelecteCascadRes tPARes;
			tPARes.m_nRes = tRes.m_emRes;
			strncpy(tPARes.m_achName, tRes.m_tAlias.m_abyAlias, localmin(PA_MAX_ALIAS_LEN, TP_MAX_ALIAS_LEN));
			MdlHint(Ums_Mdl_Stack, (">> ViewObjInd ConfID:%d, epID:%d, ChanID:%d wret:%d, Name:%s\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, tRes.m_emRes, tRes.m_tAlias.m_abyAlias));
			
			if (emTpSIP == tHandle.m_emProtocol)
			{
				s8 * pzAliasUTF8 = NULL;
			    gb2312_to_utf8(tPARes.m_achName, &pzAliasUTF8);
				strncpy(tPARes.m_achName, pzAliasUTF8, PA_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}

			PA_SendChanCtrlTP((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, (HMDLCHANNEL)tHandle.handPaChan, emPAChanSelecteCascadRes, (u8*)&tPARes, sizeof(tPARes));
		}
		break;
	case evtp_Conf_UndoViewObj_Ind:
		{
			EmTPViewResult emViewResult = *(EmTPViewResult*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">> cancelViewObjInd ConfID:%d, epID:%d, ChanID:%d Reason:%d\n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, emViewResult));
			
			PA_SendChanCtrlTP((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, (HMDLCHANNEL)tHandle.handPaChan, emPAChanSelecteCascadCancelRes, (u8*)&emViewResult, sizeof(emViewResult));
		}
		break;
	case evtp_Conf_ChanSeeLocal_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">> evtp_Conf_ChanSeeLocal_Ind ConfID:%d, epID:%d, ChanID:%d \n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan));
			PA_SendChanCtrlTP((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, (HMDLCHANNEL)tHandle.handPaChan, emPAChanSeeLocal, NULL, 0);
		}
		break;
	case evtp_Conf_ChanSeeLocalCancel_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">> evtp_Conf_ChanSeeLocalCancel_Ind ConfID:%d, epID:%d, ChanID:%d \n", tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan));
			PA_SendChanCtrlTP((HMDLCALL)tHandle.handPaCall, (HMDLAPPCALL)tHandle.handAppCall, (HMDLCHANNEL)tHandle.handPaChan, emPAChanSeeLocalCancel, NULL, 0);
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, (">> UmsSendChanCtrl failed. unkonw msg type. ConfID:%d, epID:%d, ChanID:%d, event:%d\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaChan, nMsgType));
		}
		break;
	}
	return TP_RET_OK;
}


u16 UmsSendDualConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();

	switch(nMsgType)
	{
	case ev_OpenDualChan_Req:
		{
			TUmsNodeCapset* ptCapSet = (TUmsNodeCapset*)((u8*)pBuf);
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_OpenDualChan_Req, ConfID:%d, epID:%d, PACall:%d\n", tHandle.GetConfID(), tHandle.GetEpID(), nPaID));
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makesenddual, (u8*)ptCapSet, tHandle, OUTSIGN);

			TDualCapList tDualCapList;
			ConverDualInfoFromUmsToStack(tDualCapList, *ptCapSet);
			PA_SendDualSteam((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, &tDualCapList);
		}
		break;
	case ev_MakeSendDual_Answer:
		{
			BOOL32 bRes = *((BOOL32*)((u8*)pBuf));
			TUmsNodeCapset* ptCapSet = (TUmsNodeCapset*)((u8*)pBuf+sizeof(BOOL32));
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_MakeSendDual_Answer, ConfID:%d, epID:%d, PACall:%d, Res:%d.\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), nPaID, bRes));
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_makesenddual, (u8*)ptCapSet, tHandle, OUTSIGN);
			
			TDualCapList tDualCapList;
			ConverDualInfoFromUmsToStack(tDualCapList, *ptCapSet);
 			PA_AnswerDualStream((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, bRes, &tDualCapList);
		}
		break;
	case ev_DualChan_DisConnect:
		{
			EmTPChannelReason emUms = *(EmTPChannelReason*)pBuf;
			EmChannelReason emPa = emModuleChannelDisconnectNormal;
			
			if (emTPDualOffLine == emUms)
			{
				emPa = emModuleDualOffLine;
			}
			else if (emTPForceStop == emUms)
			{
				emPa = emModuleChannelDisconnectForce;
			}
			else if (emTPDualNotSend == emUms)
			{
				emPa = emModuleDualNotSend;
			}
			else
			{
				emPa = emModuleChannelDisconnectNormal;
			}

			MdlHint(Ums_Mdl_Stack, (">>>> ev_DualChan_DisConnect, ConfID:%d, epID:%d, emPa:%d.\n", 
				tHandle.GetConfID(), tHandle.GetEpID(), emPa));
			if (emTpSIP == tHandle.m_emProtocol)
			{
				PA_StopDualStream((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPa);
			}
			else
			{
				PA_StopDualStream((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID);
			}
		}
		break;
	case evtp_Conf_RequestDualStream_cmd:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_RequestDualStream_cmd, ConfID:%d, EpID:%d, CallID:%d Protocal:%d(1:323;3:sip)\n", wConfID, wEpID, nPaID, tHandle.m_emProtocol));
			TEpKeyEx* ptUms = (TEpKeyEx*)pBuf;
			if ( tHandle.m_emProtocol == emTpSIP )
			{
				TDualRequest tPA;
				tPA.m_nEpId = ptUms->m_wEpID;
				memcpy(tPA.m_achCascade, ptUms->m_achReserve, sizeof(ptUms->m_achReserve));
				PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPARequestDualStreamCmd, (u8*)&tPA, sizeof(tPA));
			}
			else
			{
				BOOL32 bOpenDual = TRUE;
				PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleChgSecVidSendCmd, (u8*)&bOpenDual, sizeof(bOpenDual));
			}
		}
		break;
	case evtp_Conf_RequestDualStream_Ind:
		{
			TDualRequestAckTr* ptUms = (TDualRequestAckTr*)pBuf;
			const u32 nSize = sizeof(BOOL32) + sizeof(u32) + sizeof(TDualRequest);
			u8 abyBuf[nSize];
			*(BOOL32*)abyBuf = ptUms->m_bAccept;
			*(u32*)(abyBuf+sizeof(BOOL32)) = (u32)ptUms->m_dwReason;
			TDualRequest* ptPA = (TDualRequest*)(abyBuf+sizeof(BOOL32) + sizeof(u32));
			ptPA->m_nEpId = ptUms->m_tEpKey.m_wEpID;
//			strncpy(ptPA->m_achCascade, ptUms->m_tEpKey.m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_RequestDualStream_Ind, ConfID:%d, EpID:%d, CallID:%d, PaDualEpID:%d, UmsDualEpID:%d\n", wConfID, wEpID, nPaID, ptPA->m_nEpId, ptUms->m_tEpKey.m_wEpID));
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPARequestDualStreamInd, abyBuf, nSize);
		}
		break;
	case evtp_cascade_OpenDualChan_Cmd:
		{
			TDualInfoTr* ptUms = (TDualInfoTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenDualChan_Cmd, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));			
			TDualInfo tPA;
			ConvertConfDualStreamFromUmsToStack(tPA, *ptUms);
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPASendDualStream, (u8*)&tPA, sizeof(tPA));	
		}
		break;
	case evtp_cascade_OpenDualChan_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenDualChan_Ind, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TDualInfoAckTr* ptUms = (TDualInfoAckTr*)pBuf;
			TDualInfoAck tPA;
			tPA.m_bAccept = ptUms->m_bAccept;
			ConvertConfDualStreamFromUmsToStack(tPA.m_tDualInfo, ptUms->m_tDualInfo);
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPASendDualStreamAck, (u8*)&tPA, sizeof(tPA));	
		}
		break;
	case evtp_Conf_StopRcvDual_Ind:
		{
			if (emTpH323 == tHandle.m_emProtocol)
			{
				s32 nAppChan = CTpTypeAdpt::GetChannelHandle(em_second_vidsnd_handle, 0);				
				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopRcvDual_Ind for H323, ConfID:%d, EpID:%d, AppChan:%d \n", wConfID, wEpID, nAppChan));
				PA_SendChanCtrl((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, NULL, (HMDLAPPCHANNEL)nAppChan, emPAStopRcvDualInd, NULL, 0);
			}
			else
			{
				EmTPDualReason* ptUms = (EmTPDualReason*)pBuf;
				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopRcvDual_Ind, ConfID:%d, EpID:%d, CallID:%d, reason:%d\n", wConfID, wEpID, nPaID, *ptUms));				
				EmDualReason tPA = CTpTypeAdpt::GetDualReason(*ptUms);		
				PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAStopRcvDualInd, (u8*)&tPA, sizeof(tPA));
			}			
		}
		break;
	case evtp_Conf_DualFastUpdate_Ind:
		{
			BOOL32 tUms = *(BOOL32*)pBuf;
			tpLowDtl(Ums_Mdl_Stack, ">>>> evtp_Conf_DualFastUpdate_Ind, ConfID:%d, EpID:%d, CallID:%d, bSys:%d\n", wConfID, wEpID, nPaID, tUms);
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPADualStreamFastUpdate, (u8*)&tUms, sizeof(BOOL32));	
		}
		break;	
	case evtp_Conf_StartRcvDual_Ind:
		{

			if (emTpH323 == tHandle.m_emProtocol)
			{
				s32 nAppChan = CTpTypeAdpt::GetChannelHandle(em_second_vidsnd_handle, 0);				
				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartRcvDual_Ind for H323, ConfID:%d, EpID:%d, AppChan:%d \n", wConfID, wEpID, nAppChan));
				PA_SendChanCtrl((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, NULL, (HMDLAPPCHANNEL)nAppChan, emPAStartRcvDualInd, NULL, 0);
			}
			else
			{
				TEpKeyEx* ptKey = (TEpKeyEx*)pBuf;
				TPAEpKey tPA;
				tPA.m_wEpID = ptKey->m_wEpID;
				memcpy(tPA.m_tKey.m_achEpID, ptKey->m_achReserve, sizeof(ptKey->m_achReserve)); 
				//ConvertEpKeyFromUmsToStack(*ptKey, tPA);				
				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartRcvDual_Ind, ConfID:%d, EpID:%d, CallID:%d, dualKey:%d\n", wConfID, wEpID, nPaID, tPA.m_wEpID));
				PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAStartRcvDualInd,  (u8*)&tPA, sizeof(tPA));
			}

		}
		break;
	case evtp_Conf_SrcDualName_Ind:
		{
			u8 abyBuf[sizeof(TPAName) + sizeof(TPAEpKey)];
			memset(abyBuf, 0, sizeof(abyBuf));
			TPAName* ptPAName = (TPAName*)abyBuf;
			TPAEpKey* ptPAKey = (TPAEpKey*)(abyBuf + sizeof(TPAName));

			TTPAlias* ptUms = (TTPAlias*)pBuf;
			TEpKey* ptKey = (TEpKey*)((u8*)pBuf + sizeof(TTPAlias));

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_SrcDualName_Ind, ConfID:%d, EpID:%d, CallID:%d, Name:%s, dualID:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_abyAlias, ptKey->m_wEpID));
			
			ptPAName->SetAlias(ptUms->m_abyAlias);
			ConvertEpKeyFromUmsToStack(*ptKey, *ptPAKey);

			if (emTpSIP == tHandle.m_emProtocol)
			{
			    s8 * pzAliasUTF8 = NULL;
			    gb2312_to_utf8(ptPAName->m_achAlias, &pzAliasUTF8);
				strncpy(ptPAName->m_achAlias, pzAliasUTF8, PA_MAX_ALIAS_LEN);
			    free(pzAliasUTF8);
			    pzAliasUTF8 = NULL;
			}

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPASrcDualNameInd, abyBuf, sizeof(abyBuf));
		}
		break;
	case evtp_Conf_StopSendDual_Ind:
		{
			TPAEpKey tPa;
			TEpKey tUms = *(TEpKey*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopSendDual_Ind, ConfID:%d, EpID:%d, CallID:%d, EpID:%d\n", wConfID, wEpID, nPaID, tUms.m_wEpID));			

			ConverEpKeyFromUmsToStack(tUms, tPa);			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAStopDualStream, (u8*)&tPa, sizeof(tPa));	
		}
		break;
	case ev_UmsConfStartDual_Cmd:
		{
			TConfEpID& tUms = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfStartDual_Cmd, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			if (emTpSIP == tHandle.m_emProtocol)
			{
				TPAConfEpID tPA;
				ConvertConfEpIDFromUmsToStack(tUms, tPA);		
				PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfStartDual_Cmd, (u8*)&tPA, sizeof(tPA));
			}
			else
			{
				BOOL32 bCmd = TRUE;
				PA_SendConfCtrl((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emModuleChgSecVidSendCmd, (u8*)&bCmd, sizeof(bCmd));
			}
		}
		break;
	case ev_UmsConfStartDual_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			EmTPDualReason& eReason = *(EmTPDualReason*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfStartDual_Ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tInd, tPA);
			
			u8 byBuf[sizeof(TPAConfEpID) + sizeof(EmTPDualReason)] = {0};
			memcpy(byBuf, &tPA, sizeof(TPAConfEpID));
			memcpy(byBuf + sizeof(TPAConfEpID), &eReason, sizeof(EmTPDualReason));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfStartDual_Ind, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsConfStopDual_Cmd:
		{
			TConfEpID& tUms = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfStopDual_Cmd, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			if (emTpSIP == tHandle.m_emProtocol)
			{
				TPAConfEpID tPA;
				ConvertConfEpIDFromUmsToStack(tUms, tPA);		
				PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfStartDual_Cmd, (u8*)&tPA, sizeof(tPA));
			}
			else
			{
				BOOL32 bCmd = FALSE;
				PA_SendConfCtrl((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emModuleChgSecVidSendCmd, (u8*)&bCmd, sizeof(bCmd));
			}
		}
		break;
	case ev_UmsConfStopDual_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			EmTPDualReason& eReason = *(EmTPDualReason*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> emPATppConfStopDual_Ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tInd, tPA);
			
			u8 byBuf[sizeof(TPAConfEpID) + sizeof(EmTPDualReason)] = {0};
			memcpy(byBuf, &tPA, sizeof(TPAConfEpID));
			memcpy(byBuf + sizeof(TPAConfEpID), &eReason, sizeof(EmTPDualReason));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfStopDual_Ind, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsConfDualEp_Nty:
		{
			TConfEpID& tUms = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfDualEp_Nty, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tUms, tPA);		
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfDualEp_Nty, (u8*)&tPA, sizeof(tPA));
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("  >> UmsSendDualConfCtrl failed. unkonw msg type. ConfID:%d, epID:%d, event:%d-%s\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType, GetEventNamebyID(nMsgType)));
			return FALSE;
		}	
	break;
	}
	return TRUE;
}

u16 UmsSendPollConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	switch(nMsgType)
	{
	case evtp_Conf_StartPoll_cmd:
		{
			TPollCmdTr& tInfo = *(TPollCmdTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartPoll_cmd, ConfID:%d, EpID:%d, CallID:%d, Interval:%d\n"
				, wConfID, wEpID, nPaID, tInfo.m_wInterval));
			
			TPAPollCmd tPA;
			ConvertConfPollCmdFromUmsToStack(tPA, tInfo);			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfStartPoll, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_StartPoll_ack:
		{
			TPollAckTr& tInfo = *(TPollAckTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartPoll_ack, ConfID:%d, EpID:%d, CallID:%d, ret:%d\n"
				, wConfID, wEpID, nPaID, tInfo.m_wReason));
			
			TPAPollAck tPA;
			ConvertConfPollAckFromUmsToStack(tPA, tInfo);	
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfStartPollAck, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_Poll_NodeChange:
		{
			TEpKey& tKey = *(TEpKey*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_Poll_NodeChange, ConfID:%d, EpID:%d, CallID:%d, childId:%d\n"
				, wConfID, wEpID, nPaID, tKey.m_wEpID));
			
			TPAPollNodeChange tPaPoll;
//			strncpy(tPaPoll.m_tNodeInfo.m_tKey.m_szEpID, tKey.m_tKey.m_szEpID, PA_NODECHANGEINFO);
			tPaPoll.m_tNodeInfo.m_wEpID = tKey.m_wEpID;
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfPollNodeChange, (u8*)&tPaPoll, sizeof(tPaPoll));	
		}
		break;
	case evtp_Conf_Poll_End:
		{
			BOOL32 tUms = *(BOOL32*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_Poll_End, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfEndPoll, (u8*)&tUms, sizeof(tUms));	
		}
		break;
	case evtp_Conf_Poll_AskKeyFrame:
		{
			tpLowDtl(Ums_Mdl_Stack, ">>>> evtp_Conf_Poll_AskKeyFrame, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID);
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfPollFastUpdate, NULL, 0);	
		}
		break;
	case evtp_Conf_PollDstName_Ind:
		{
			TPAPollDstName tPA;
			TPollInfoNtf* ptUms = (TPollInfoNtf*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_PollDstName_Ind, ConfID:%d, EpID:%d, CallID:%d, Name:%s, VidNum:%d\n", wConfID, wEpID, nPaID, ptUms->m_tAlias.m_abyAlias, ptUms->m_nScreenNum));
			
			tPA.SetAlias(ptUms->m_tAlias.m_abyAlias);
			tPA.m_dwScreenNum = ptUms->m_nScreenNum;

			if (emTpSIP == tHandle.m_emProtocol)
			{
				s8 * pzAliasUTF8 = NULL;
				gb2312_to_utf8(tPA.m_achAlias, &pzAliasUTF8);
				strncpy(tPA.m_achAlias, pzAliasUTF8, PA_MAX_ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAPollDstNameInd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_StartPoll_Ind:
		{
			EmTPPollResult tUms = *(EmTPPollResult*)pBuf;

			u32 tPA = u32(tUms);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StartPoll_Ind, ConfID:%d, EpID:%d, ret:%d\n", wConfID, wEpID, tUms));
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfStartPollingRes, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_StopPoll_Ind:
		{
			u32 tUms = *(u32*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopPoll_Ind, ConfID:%d, EpID:%d, ret:%d\n", wConfID, wEpID, tUms));
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfClosePollingRes, (u8*)&tUms, sizeof(tUms));
		}
		break;
	case evtp_Conf_PollStatus_Notif:
		{
			TTpPollStat tUms = *(TTpPollStat*)pBuf;
			EmPAPollStat tPaState;
			TPAPollStat tPa;
			tPa.m_wConfID = tUms.m_wConfID;
			
			if (tUms.m_emStat == EmPollStat_Start)
			{
				tPa.m_emStat = emPAPollStat_Start;
			}
			else if (tUms.m_emStat == EmPollStat_Stop)
			{
				tPa.m_emStat = emPAPollStat_Stop;
			}
			else if (tUms.m_emStat == EmPollStat_Suspend)
			{
				tPa.m_emStat = emPAPollStat_Suspend;
			}
			else
			{
				tPa.m_emStat = emPAPollStat_Error;
			}

			tPaState = tPa.m_emStat;

			u8 bBuf[sizeof(EmPAPollStat) + sizeof(TTpPollStat)];
			memcpy(bBuf, &tPaState, sizeof(EmPAPollStat));
			memcpy(bBuf+sizeof(EmPAPollStat), &tPa, sizeof(TTpPollStat));


			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_PollStatus_Notif, ConfID:%d, EpID:%d, Stat:%d\n", wConfID, wEpID, tPa.m_emStat));

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConfNotifyPollingRes, bBuf, sizeof(bBuf));
		}
		break;
	case ev_UmsUpdateConfTurnlist_Nty:
		{
			TTpPollListNtfy& tUms = *(TTpPollListNtfy*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsUpdateConfTurnlist_Nty, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAPollListNtfy tPA;

			tPA.m_wConfID = tUms.m_wConfID;
			tPA.m_wInterval = tUms.m_wInterval;
			tPA.m_nFlag = tUms.m_nFlag;
			tPA.m_wCurNum = tUms.m_wCurNum;
			tPA.m_wTotalNum = tUms.m_wTotalNum;

			memcpy(tPA.m_awList, tUms.m_awList, sizeof(tPA.m_awList));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpUpdateConfTurnlist_Nty, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_SuspendPoll_Ind:
		{
			u32 dwRet;
			TP_SAFE_CAST(dwRet, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_SuspendPoll_Ind EpID:%d Ret:%d.\n", tHandle.GetEpID(), dwRet));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConf_SuspendPoll_Ind, (u8*)&dwRet, sizeof(dwRet));
		}
		break;
	case evtp_Conf_CasecadePollEp_Req:
		{
			TCasecadePollEpReq tReq;
			TP_SAFE_CAST(tReq, (u8*)pBuf);
			TPACasecadePollEpReq tPa;
			ConvertCasecadePollEpReqFromUmsToStack(tReq, tPa);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CasecadePollEp_Req EpID:%d bCreate:%d, EpID:%d, Rtp(%d, %d, %d).\n",
				tHandle.GetEpID(), tReq.m_bCreate, tReq.m_wEpID, tReq.m_atPollAddr[0].GetPort(), tReq.m_atPollAddr[1].GetPort(), tReq.m_atPollAddr[2].GetPort()));
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConf_CasecadePollEp_Req, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case evtp_Conf_CasecadePollEp_Rsp:
		{
			TCasecadePollEpRsp tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);

			TPACasecadePollEpRsp tPa;
			ConvertCasecadePollEpReqFromUmsToStack(tRsp.m_tReq, tPa.m_tReq);
			tPa.m_emRes = tRsp.m_emRes;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CasecadePollEp_Rsp EpID:%d bCreate:%d, EpID:%d, Rtp(%d, %d, %d) Ret:%d.\n",
				tHandle.GetEpID(), tRsp.m_tReq.m_bCreate, tRsp.m_tReq.m_wEpID, 
				tRsp.m_tReq.m_atPollAddr[0].GetPort(), tRsp.m_tReq.m_atPollAddr[1].GetPort(), tRsp.m_tReq.m_atPollAddr[2].GetPort(), tRsp.m_emRes));

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAConf_CasecadePollEp_Rsp, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case ev_UmsUpdateConfTurnlist_Ind:
		{
			TTpPollListInd tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);

			TPAPollListInd tPa;
			tPa.m_nFlag = tRsp.m_nFlag;
			tPa.m_wConfID = tRsp.m_wConfID;
			tPa.m_wRet = tRsp.m_wRet;
			tPa.m_wCurRcvNum = tRsp.m_wCurRcvNum;

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsUpdateConfTurnlist_Ind EpID:%d ConfID:%d, Flag:%d, Ret:%d, CurRcvNum:%d.\n",
									tHandle.GetEpID(), tRsp.m_wConfID, tRsp.m_nFlag, tRsp.m_wRet, tRsp.m_wCurRcvNum));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAUmsUpdateConfTurnlist_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("  >> UmsSendPollConfCtrl failed. unkonw msg type. ConfID:%d, epID:%d, event:%d-%s\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType, GetEventNamebyID(nMsgType)));
			return FALSE;
		}	
	break;
	}
	return TRUE;
}


u16 UmsSendAudMixConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	switch(nMsgType)
	{
	case evtp_OpenAudChan_Cmd:
		{
			TAudChanCmd& tCmd = *(TAudChanCmd*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenAudChan_Cmd, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAAudChanCmd tPA;
			ConvertAudChanCmdFromUmsToStack(tCmd, tPA);			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAOpenAudChanCmd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_OpenAudChan_Ack:
		{
			TAudChanAck& tAck = *(TAudChanAck*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenAudChan_Ack, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAAudChanAck tPA;
			ConvertAudChanAckFromUmsToStack(tAck, tPA);			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAOpenAudChanAck, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_OpenVidChan_Cmd:
		{
			TVidChanCmd& tCmd = *(TVidChanCmd*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenVidChan_Cmd, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAVidChanCmd tPA;
			ConvertVidChanCmdFromUmsToStack(tCmd, tPA);			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAOpenVidChanCmd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_OpenVidChan_Ack:
		{
			TVidChanAck& tAck = *(TVidChanAck*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_OpenVidChan_Ack, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAVidChanAck tPA;
			ConvertVidChanAckFromUmsToStack(tAck, tPA);			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAOpenVidChanAck, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_CloseVidChan_Cmd:
		{
			u16 wEpIDCmd = *(u16*)pBuf;
			u32 dwType = *(u32*)((u8*)pBuf+sizeof(u16));
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_CloseVidChan_Cmd, ConfID:%d, EpID:%d, type:%d, CallID:%d\n"
				, wConfID, wEpID, dwType, nPaID));

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPACloseVidChanCmd, (u8*)pBuf, sizeof(u16)+sizeof(u32));
		}
		break;
	case evtp_UmsDiscussScreenStat_Notify:
		{
			TDiscussCasecadeNtfy* ptDisStat = (TDiscussCasecadeNtfy*)pBuf;
			TPADiscussCasecadeNtfy tPa;

			tPa.m_bIsDiscussModle = ptDisStat->m_bIsDiscussModle;
			
			u16 wIndex = 0;
			u16 wLoop = 0;
			s8 *pzAliasUTF8 = NULL;
			for (wIndex = 0; wIndex < emDiscussObjEnd; wIndex++)
			{
				tPa.m_atDiscussObj[wIndex].wReserve = ptDisStat->m_atDiscussObj[wIndex].m_wReserve;
				for (wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
				{
					tPa.m_atDiscussObj[wIndex].m_abIsVaild[wLoop] = ptDisStat->m_atDiscussObj[wIndex].m_abIsVaild[wLoop];
					ConvertAliasFromUmsToStack(ptDisStat->m_atDiscussObj[wIndex].m_atEpAlias[wLoop], tPa.m_atDiscussObj[wIndex].m_atEpAlias[wLoop]);
					gb2312_to_utf8((s8*)tPa.m_atDiscussObj[wIndex].m_atEpAlias[wLoop].m_achAlias, &pzAliasUTF8);
					strncpy((s8*)tPa.m_atDiscussObj[wIndex].m_atEpAlias[wLoop].m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
					free(pzAliasUTF8);
					pzAliasUTF8 = NULL;
				}
			}

			for (wIndex = 0; wIndex < PA_CONF_MAX_AUDMIXNUM; wIndex++)
			{
				tPa.m_awDiscussEpId[wIndex] = ptDisStat->m_tEpAudInfo.m_awDiscussEpId[wIndex];
				tPa.m_abyIsRcvNModeAud[wIndex][0] = ptDisStat->m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][0];
				tPa.m_abyIsRcvNModeAud[wIndex][1] = ptDisStat->m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][1];
				tPa.m_abyIsRcvNModeAud[wIndex][2] = ptDisStat->m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][2];

				if (0 != tPa.m_awDiscussEpId[wIndex])
				{
					MdlHint(Ums_Mdl_Stack, ("To Pa... ConfId:%d, Ep:%d, (%d,%d,%d)\n", wConfID, tPa.m_awDiscussEpId[wIndex],
						tPa.m_abyIsRcvNModeAud[wIndex][0], tPa.m_abyIsRcvNModeAud[wIndex][1], tPa.m_abyIsRcvNModeAud[wIndex][2]));
				}
			}
			
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsDiscussScreenStat_Notify, ConfID:%d, EpID:%d, CallID:%d, bNtyDis:%d, obj(%d-%s,%d-%s,%d-%s), obj(%d-%s,%d-%s,%d-%s), obj(%d-%s,%d-%s,%d-%s)\n"
				, wConfID, wEpID, nPaID, tPa.m_bIsDiscussModle, 
				tPa.m_atDiscussObj[0].m_abIsVaild[0], tPa.m_atDiscussObj[0].m_atEpAlias[0].m_achAlias, 
				tPa.m_atDiscussObj[0].m_abIsVaild[1], tPa.m_atDiscussObj[0].m_atEpAlias[1].m_achAlias,
				tPa.m_atDiscussObj[0].m_abIsVaild[2], tPa.m_atDiscussObj[0].m_atEpAlias[2].m_achAlias,
				tPa.m_atDiscussObj[1].m_abIsVaild[0], tPa.m_atDiscussObj[1].m_atEpAlias[0].m_achAlias,
				tPa.m_atDiscussObj[1].m_abIsVaild[1], tPa.m_atDiscussObj[1].m_atEpAlias[1].m_achAlias,
				tPa.m_atDiscussObj[1].m_abIsVaild[2], tPa.m_atDiscussObj[1].m_atEpAlias[2].m_achAlias,
				tPa.m_atDiscussObj[2].m_abIsVaild[0], tPa.m_atDiscussObj[2].m_atEpAlias[0].m_achAlias,
				tPa.m_atDiscussObj[2].m_abIsVaild[1], tPa.m_atDiscussObj[2].m_atEpAlias[1].m_achAlias,
				tPa.m_atDiscussObj[2].m_abIsVaild[2], tPa.m_atDiscussObj[2].m_atEpAlias[2].m_achAlias));
			MdlHint(Ums_Mdl_Stack, ("  SpeacialEp:%d.\n", tPa.m_atDiscussObj[0].wReserve));

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAUmsDiscussScreenStat_Notify, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case evtp_UmsCnsSpeakerIndxAdjust_Notify:
		{
			TCnsSpeakerAdjust* ptUms = (TCnsSpeakerAdjust*)pBuf;
			
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsCnsSpeakerIndxAdjust_Notify, ConfID:%d, EpID:%d, CallID:%d, childId:%d, Index:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_tKey.m_wEpID, ptUms->m_wSpeakerIndex));
			
			TPACascadingSpeaker tPA;			
//			strncpy(tPA.m_tNodeKey.m_tKey.m_szEpID, ptUms->m_tKey.m_tKey.m_szEpID, PA_NODECHANGEINFO);	
			tPA.m_tNodeKey.m_wEpID = ptUms->m_tKey.m_wEpID;
			tPA.m_wEpID = ptUms->m_wEpID;
			tPA.m_wSpeaker = ptUms->m_wSpeakerIndex;
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAUmsCnsSpeakerIndxAdjust_Notify, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_UmsDiscussFastUpdate_Req:
		{
			TDisAskKeyFrame* ptUms = (TDisAskKeyFrame*)pBuf;
			TPADisAskKeyFrame tPa;
			MdlLowDtl(Ums_Mdl_Stack, (">>>> evtp_UmsDiscussFastUpdate_Req, ConfID:%d, EpID:%d, CallID:%d, SrcEpID:%d, SrcScreenIndx:%d, bSys:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_wEpID, ptUms->m_wScreenNo, ptUms->m_bReqBySys));
			
			tPa.m_wEpID = ptUms->m_wEpID;
			tPa.m_wScreenNo = ptUms->m_wScreenNo;
			tPa.m_bReqBySys = ptUms->m_bReqBySys;
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAUmsDiscussFastUpdate_Req, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case ev_UmsConfAMixVacSwitchInd:
		{
			TConfAuxMixVacOpr& tUms = *(TConfAuxMixVacOpr*)pBuf;
			TPAConfAuxMixVacOpr tPA;

			tPA.m_wConfID = tUms.m_wConfID;
			tPA.m_bVacOn = tUms.m_bVacOn;
			tPA.m_wOprRet = tUms.m_wOprRet;

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfAMixVacSwitchInd, ConfID:%d, EpID:%d, CallID:%d, bVacOn:%d, wRet:%d\n"
				, wConfID, wEpID, nPaID, tPA.m_bVacOn, tPA.m_wOprRet));

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAUmsConfAMixVacSwitchInd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case ev_UmsAudMixDisListOpr_Ind:
		{
			TDiscussListOpr& tUms = *(TDiscussListOpr*)pBuf;
			
			TPADisListOpr tPA;

			tPA.m_wConfId = tUms.m_wConfId;
			tPA.m_wNum = tUms.m_wNum;
			for (u16 wIndex = 0; wIndex < tUms.m_wNum; wIndex++)
			{
				tPA.m_awEpId[wIndex] = tUms.m_awEpId[wIndex];
                tPA.m_adwRet[wIndex] = tUms.m_aemRet[wIndex];
			}
			
			switch( tUms.m_emOprType )
			{
			case em_DisListOpr_Add:
				tPA.m_dwOprType = emPA_DisListOpr_Add;
				break;
			case em_DisListOpr_Del:
				tPA.m_dwOprType = emPA_DisListOpr_Del;
				break;
			default:
				MdlError(Ums_Mdl_Stack, ( "ev_UmsAudMixDisListOpr_Ind, EmDisListOprType Error! umsOprType:%d", tUms.m_emOprType));
				break;
			}			

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsAudMixDisListOpr_Ind, ConfID:%d, EpID:%d, CallID:%d, wNum:%d, OprType:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wNum, tUms.m_emOprType));

			for (u16 wI = 0; wI < tPA.m_wNum; wI++)
			{
				MdlHint(Ums_Mdl_Stack, ("  >>>> [%d] List EpId:%d.\n", wI, tPA.m_awEpId[wI]));
			}

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAUmsAudMixDisListOpr_Ind, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case ev_UmsConfAMixUpdate_Ind:
		{
			TConfAuxMixInfo& tInd = *(TConfAuxMixInfo*)pBuf;

			TPAConfAuxMixInfo tPA;
			ConvertConfAuxMixInfoFromUmsToStack(tInd, tPA);	

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfAMixUpdate_Ind, ConfID:%d, EpID:%d, CallID:%d, Start:%d, Ret:%d.\n"
				, wConfID, wEpID, nPaID, tPA.m_bStart, tPA.m_dwRet));
			
			for (u16 wI = 0; wI < PA_CONF_MAX_AUDMIXNUM; wI++)
			{
				MdlHint(Ums_Mdl_Stack, ("  >>>> [%d] List EpId:%d.\n", wI, tPA.m_atAuxMixList.m_awList[wI]));
			}
		
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfAMixUpdate_Ind, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case ev_UmsConfAMixUpdate_Nty:
		{
			TConfAuxMixInfo& tNty = *(TConfAuxMixInfo*)pBuf;
			TPAConfAuxMixInfo tPA;
			ConvertConfAuxMixInfoFromUmsToStack(tNty, tPA);	

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfAMixUpdate_Nty, ConfID:%d, EpID:%d, CallID:%d, Start:%d, VacOn:%d.\n"
				, wConfID, wEpID, nPaID, tPA.m_bStart, tPA.m_bVacOn));

			for (u16 wI = 0; wI < PA_CONF_MAX_AUDMIXNUM; wI++)
			{
				if (tPA.m_atAuxMixList.m_awList[wI] == TP_INVALID_INDEX ||
					tPA.m_atAuxMixList.m_awList[wI] == 0)
				{
					continue;
				}
				MdlLowHint(Ums_Mdl_Stack, ("  >>>> [%d] List EpId:%d.\n", wI, tPA.m_atAuxMixList.m_awList[wI]));
			}

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfAMixUpdate_Nty, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case ev_UmsAudMixStatus_Nty:
		{
			TAudMixStat& tInd = *(TAudMixStat*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsAudMixStatus_Nty, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAAudMixStat tPa;
			ConvertAudMixStatFromUmsToStack(tInd, tPa);
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpAudMixStatus_Nty, (u8*)&tPa, sizeof(tPa));
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("  >> UmsSendAudMixConfCtrl failed. unkonw msg type. ConfID:%d, epID:%d, event:%d-%s\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType, GetEventNamebyID(nMsgType)));
			return FALSE;
		}	
	break;
	}
	return TRUE;
}


u16 UmsSendCnsUIConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize)
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();
	
	switch(nMsgType)
	{

	case ev_UmsConfApplySpeaker_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			EmTpApplySpeakerRet& emRet = *(EmTpApplySpeakerRet*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfApplySpeaker_Ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			EmPATpApplySpeakerRet emPaRet;
			ConvertConfEpIDFromUmsToStack(tInd, tPA);
			ConvertApplySpeakerRetFromUmsToStack(emRet, emPaRet);

			u8 byBuf[sizeof(TPAConfEpID) + sizeof(EmPATpApplySpeakerRet)] = {0};
			memcpy(byBuf, &tPA, sizeof(TPAConfEpID));
			memcpy(byBuf + sizeof(TPAConfEpID), &emPaRet, sizeof(EmPATpApplySpeakerRet));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfApplySpeaker_Ind, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsConfApplySpeaker_Nty:
		{
			TConfEpID& tAck = *(TConfEpID*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfApplySpeaker_Nty, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tAck, tPA);		
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfApplySpeaker_Nty, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case ev_UmsConfMute_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfMute_Ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tInd, tPA);
			
			u8 byBuf[sizeof(TPAConfEpID) + sizeof(BOOL)] = {0};
			memcpy(byBuf, &tPA, sizeof(TPAConfEpID));
			memcpy(byBuf + sizeof(TPAConfEpID), &bRet, sizeof(BOOL));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfMute_Ind, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsConfMute_Nty:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfMute_Nty, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tInd, tPA);
			
			u8 byBuf[sizeof(TPAConfEpID) + sizeof(BOOL)] = {0};
			memcpy(byBuf, &tPA, sizeof(TPAConfEpID));
			memcpy(byBuf + sizeof(TPAConfEpID), &bRet, sizeof(BOOL));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfMute_Nty, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsConfQuiet_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfQuiet_Ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tInd, tPA);
			
			u8 byBuf[sizeof(TPAConfEpID) + sizeof(BOOL)] = {0};
			memcpy(byBuf, &tPA, sizeof(TPAConfEpID));
			memcpy(byBuf + sizeof(TPAConfEpID), &bRet, sizeof(BOOL));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfQuiet_Ind, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsConfQuiet_Nty:
		{
			u8* pByBuf = (u8*)pBuf;
			TConfEpID& tInd = *(TConfEpID*)pBuf;
			BOOL& bRet = *(BOOL*)(pByBuf + sizeof(TConfEpID));
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfQuiet_Nty, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));
			
			TPAConfEpID tPA;
			ConvertConfEpIDFromUmsToStack(tInd, tPA);
			
			u8 byBuf[sizeof(TPAConfEpID) + sizeof(BOOL)] = {0};
			memcpy(byBuf, &tPA, sizeof(TPAConfEpID));
			memcpy(byBuf + sizeof(TPAConfEpID), &bRet, sizeof(BOOL));
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpConfQuiet_Nty, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsInviteCnsByAlias_Ind:
		{
	 		u8* pByBuf = (u8*)pBuf;
	 		TTpCallAddr& tInd = *(TTpCallAddr*)pBuf;
  			EmCnsCallReason& emRet = *(EmCnsCallReason*)(pByBuf + sizeof(TTpCallAddr));	

		 	TPACallAddr tPa;
		 	EmPACnsCallReason emPa;
			ConvertAliasFromUmsToStack(tInd.m_tAlias, tPa.m_tAlias);
			ConvertAliasFromUmsToStack(tInd.m_tE164, tPa.m_tE164);
			tPa.m_dwIP = tInd.m_dwIP;
			tPa.m_bAliasIP = tInd.m_bAliasIP;
			ConvertCallTypeFromUmsToStack(tInd.m_byCallType,tPa.m_byCallType);
    		ConvertCallResonFromUmsToStack(emRet, emPa);

			if (emTpSIP == tHandle.m_emProtocol)
			{
				s8 * pzAliasUTF8 = NULL;
				s8 * pzE164UTF8 = NULL;
				gb2312_to_utf8(tInd.m_tAlias.m_abyAlias, &pzAliasUTF8);
				gb2312_to_utf8(tInd.m_tE164.m_abyAlias, &pzE164UTF8);
				strncpy(tPa.m_tAlias.m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
				strncpy(tPa.m_tE164.m_achAlias, pzE164UTF8, PA_MAX_NAME_LEN);
				free(pzAliasUTF8);
				free(pzE164UTF8);
				pzAliasUTF8 = NULL;
				pzE164UTF8 =NULL;
			}
	 		MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsInviteCnsByAlias_Ind, ConfID:%d, EpID:%d, CallID:%d, gb2312 Alias:%s,E164:%s,IP:"TPIPFORMAT", utf8 Alias:%s,E164:%s,IP:"TPIPFORMAT"\n",
					wConfID, wEpID, nPaID, tInd.m_tAlias.m_abyAlias,tInd.m_tE164.m_abyAlias,Tpu32ToIP(tInd.m_dwIP),
					tPa.m_tAlias.m_achAlias,tPa.m_tE164.m_achAlias,Tpu32ToIP(tPa.m_dwIP)));

			u8 byBuf[sizeof(TPACallAddr) + sizeof(EmPACnsCallReason)] = {0};
			memcpy(byBuf, &tPa, sizeof(TPACallAddr));
			memcpy(byBuf + sizeof(TPACallAddr), &emPa, sizeof(EmPACnsCallReason));
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpInviteCnsByAlias_Ind, byBuf, sizeof(byBuf));
		}
		break;
	case ev_UmsHangupCns_Ind:
	case ev_UmsInviteCnsByEpId_Ind:
		{
			u8* pByBuf = (u8*)pBuf;
			u16& wInd = *(u16*)pBuf;
			EmCnsCallReason& emRet = *(EmCnsCallReason*)(pByBuf + sizeof(u16));
			
			EmPACnsCallReason emPa;
			ConvertCallResonFromUmsToStack(emRet, emPa);

			u8 byBuf[sizeof(u16) + sizeof(EmPACnsCallReason)] = {0};
			memcpy(byBuf, &wInd, sizeof(u16));
			memcpy(byBuf + sizeof(u16), &emPa, sizeof(EmPACnsCallReason));
			
			if ( nMsgType ==  ev_UmsInviteCnsByEpId_Ind )
			{
				MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsInviteCnsByEpId_Ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));

				PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpInviteCnsByEpId_Ind, byBuf, sizeof(byBuf));
			}
			else
			{
				MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsHangupCns_Ind, ConfID:%d, EpID:%d, CallID:%d\n"
				, wConfID, wEpID, nPaID));

				PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpHangupCns_Ind, byBuf, sizeof(byBuf));
			}
		}
		break;
	case ev_UmsChairConfInfo_Nty:
		{
			TChairConfInfo& tInd = *(TChairConfInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsChairConfInfo_Nty, ConfID:%d, EpID:%d, CallID:%d, EmProtocol:%d\n"
				, wConfID, wEpID, nPaID, tHandle.m_emProtocol));
			
			TPAChairConfInfo tPa;
			ConvertChairConfInfoFromUmsToStack(tInd, tPa);

			if (emTpSIP == tHandle.m_emProtocol)
			{
				s8 *pzAliasUTF8 = NULL;
				gb2312_to_utf8((s8 *)tPa.m_tChairName.m_achAlias, &pzAliasUTF8);
				strncpy((s8 *)tPa.m_tChairName.m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
				
				gb2312_to_utf8((s8 *)tPa.m_tConfName.m_achAlias, &pzAliasUTF8);
				strncpy((s8 *)tPa.m_tConfName.m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}
			
			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPATpChairConfInfo_Nty, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case ev_UmsCommonReasonToUI_Ind:
		{
			TTPUmsReasonInd& tUms = *(TTPUmsReasonInd*)pBuf;

			TPAUmsReasonInd tPa;
			tPa.m_wConfID = tUms.m_wConfID;
			tPa.m_wEpID = tUms.m_wEpID;
			tPa.m_dwReason = tUms.m_dwReason;
			tPa.m_dwReserve1 = tUms.m_dwReserve1;
			tPa.m_dwReserve2 = tUms.m_dwReserve2;
			tPa.m_dwReserve3 = tUms.m_dwReserve3;

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsCommonReasonToUI_Ind, ConfID:%d, EpID:%d, CallID:%d, DstEPID:%d, Reason:%d, Reserve1:%d, Reserve2:%d, Reserve3:%d\n"
				, wConfID, wEpID, nPaID, tUms.m_wEpID, tUms.m_dwReason, tUms.m_dwReserve1, tUms.m_dwReserve2, tUms.m_dwReserve3));

			PA_SendConfCtrlTP((HMDLCALL)nPaID, (HMDLAPPCALL)nAppID, emPAUmsCommonReasonToUI_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;
	default:
		{
			MdlError(Ums_Mdl_Stack, ("  >> UmsSendAudMixConfCtrl failed. unkonw msg type. ConfID:%d, epID:%d, event:%d-%s\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType, GetEventNamebyID(nMsgType)));
			return FALSE;
		}	
		break;
	}
	return TRUE;
}

s8* GetNodeObj(EMScreenObj emObj)
{
	switch(emObj)
	{
	case emObjSelf:		return "Self";
	case emObjSpeaker:	return "Speaker";
	case emObjChair:	return "Chair";
	case emObjView:		return "View";
	case emObjDiscard:	return "DisCard";
	case emObjVmpBrd:	return "VmpBrd";
	case emObjPoll:		return "Poll";
	default:	break;
	}
	return "unknow";
}

u16 UmsSendConfCtrl( const TUmsHandle& tHandle, const s32 nMsgType, u8 *pBuf, const s32 nSize )
{
	s32 nAppID = tHandle.handAppCall;
	s32 nPaID = tHandle.handPaCall;

	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();

	switch(nMsgType)
	{
	case evtp_Conf_EpCallInfo_Update:
		{	
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_EpCallInfo_Update, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));

			TConfNodeCallUpdateTrList& tUms = *(TConfNodeCallUpdateTrList*)pBuf;
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpCallInfo, (u8*)&tUms, tHandle, OUTSIGN);

			TPAConfNodeUpdateTrList tPA;			
			ConvertNodeCallUpdateFromUmsToStack(tPA, tUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfNodeUpdateTrList, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_EpChanInfo_Update:
		{			
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_EpChanInfo_Update, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TConfNodeChanUpdateTrList& tUms = *(TConfNodeChanUpdateTrList*)pBuf;
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpChanInfo, (u8*)&tUms, tHandle, OUTSIGN);

			TPAConfNodeUpdateB2NEWTrList tPAB2;	
			ConvertNodeChanUpdateFromUmsToStack(tPAB2, tUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfNodeUpdateB2NewTrList, (u8*)&tPAB2, sizeof(tPAB2));
		}
		break;
	case evtp_Conf_EpInfo_Del:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_EpInfo_Del, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));

			TConfNodeDelTrList& tUms = *(TConfNodeDelTrList*)pBuf;
			CTpTypeAdpt::PrintMsgWithStack(ums_stack_print_ConfEpIDInfo, (u8*)&tUms, tHandle, OUTSIGN);

			TPAConfNodeDelTrList tPA;
			ConvertNodeDelFromUmsToStack(tPA, tUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfNodeDelTrList, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_YouAreSeeing_Ind:
		{
			TSpeakerCapTr& tCap = *(TSpeakerCapTr*)pBuf;
		
			u8 abyBuf[sizeof(TMDLTERMINALINFO)+sizeof(BOOL32)+sizeof(TYouAreSeeing)];
			TYouAreSeeing tPAInfo;
			BOOL32 bFlag = TRUE;
			TMDLTERMINALINFO tTable;

			tTable.m_byMcuNo = (u8)tHandle.GetConfID();
			tTable.m_byTerNo = (u8)tCap.m_wSpeakerID;
			strncpy(tTable.m_achTerminalId, tCap.m_tEpAlias.m_abyAlias, MAX_TERMINALID_LEN);

			tPAInfo.m_bExist = tCap.m_bIsSpeaker;
			tPAInfo.m_wCNSId = tCap.m_wSpeakerID;
			tPAInfo.m_dwAudioNum = tCap.m_wAudSnd;
			tPAInfo.m_dwVideoNum = tCap.m_wVidSnd;

			s8 * pzAliasUTF8 = NULL;
			gb2312_to_utf8(tCap.m_tEpAlias.m_abyAlias, &pzAliasUTF8);
			strncpy(tPAInfo.m_achMeetingName, pzAliasUTF8, PA_MAX_CONF_NAME_LEN);
			free(pzAliasUTF8);
			pzAliasUTF8 = NULL;

			tPAInfo.m_wSpeakerIndex = tCap.m_wSpeakerIndex;

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_YouAreSeeing_Ind, ConfID:%d, EpID:%d, CallID:%d,  vidSnd:%d, audSnd:%d, IsSpeaker:%d, SpeakerID:%d, TerID:%d, Protocol:%d\n"
				, wConfID, wEpID, nPaID, tCap.m_wVidSnd, tCap.m_wAudSnd, tCap.m_bIsSpeaker, tCap.m_wSpeakerID, tTable.m_byTerNo, tHandle.m_emProtocol));

			memcpy(abyBuf, &tTable, sizeof(TMDLTERMINALINFO));
			memcpy(abyBuf+sizeof(TMDLTERMINALINFO), &bFlag, sizeof(BOOL32));
			memcpy(abyBuf+sizeof(TMDLTERMINALINFO)+sizeof(BOOL32), &tPAInfo, sizeof(TYouAreSeeing));

			PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleTerminalYouAreSeeing, abyBuf, sizeof(abyBuf));
		}
		break;
	case evtp_Conf_YouAreSeeingEx_Ind:
		{
			TTpYouAreSeeing& tCap = *(TTpYouAreSeeing*)pBuf;

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_YouAreSeeingEx_Ind, ConfID:%d, EpID:%d, CallID:%d, bSpeaker:%d, (%s,%d,%d), (%s,%d,%d), (%s,%d,%d)\n"
				, wConfID, wEpID, nPaID, tCap.m_bSpeaker, GetNodeObj(tCap.m_atObj[0].m_emObj), tCap.m_atObj[0].m_wVidNum, tCap.m_atObj[0].m_wAudNum,
				GetNodeObj(tCap.m_atObj[1].m_emObj), tCap.m_atObj[1].m_wVidNum, tCap.m_atObj[1].m_wAudNum,
				GetNodeObj(tCap.m_atObj[2].m_emObj), tCap.m_atObj[2].m_wVidNum, tCap.m_atObj[2].m_wAudNum
				));

			TPAYouAreSeeing tPa;
			tPa.m_wAudNum = tCap.m_wAudNum;
			tPa.m_wVidNum = tCap.m_wVidNum;
			tPa.m_bSpeaker = tCap.m_bSpeaker;
			memcpy(tPa.m_atObj, tCap.m_atObj, sizeof(tCap.m_atObj));

			s8 * pzAliasUTF8 = NULL;
			
			gb2312_to_utf8(tCap.m_atObj[0].m_tAlias.m_abyAlias, &pzAliasUTF8);
			strncpy(tPa.m_atObj[0].m_tAlias.m_achAlias, pzAliasUTF8, PA_MAX_CONF_NAME_LEN);
			free(pzAliasUTF8);
			pzAliasUTF8 = NULL;

			gb2312_to_utf8(tCap.m_atObj[1].m_tAlias.m_abyAlias, &pzAliasUTF8);
			strncpy(tPa.m_atObj[1].m_tAlias.m_achAlias, pzAliasUTF8, PA_MAX_CONF_NAME_LEN);
			free(pzAliasUTF8);
			pzAliasUTF8 = NULL;

			gb2312_to_utf8(tCap.m_atObj[2].m_tAlias.m_abyAlias, &pzAliasUTF8);
			strncpy(tPa.m_atObj[2].m_tAlias.m_achAlias, pzAliasUTF8, PA_MAX_CONF_NAME_LEN);
			free(pzAliasUTF8);
			pzAliasUTF8 = NULL;

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAYouAreSeeing_v2, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case evtp_Conf_IsChair_Notify:
		{			
			BOOL32 bIsChair = *(BOOL32*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_IsChair_Notify, ConfID:%d, EpID:%d, CallID:%d, bIsChair:%d\n"
				, wConfID, wEpID, nPaID, bIsChair));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfBeChairman, (u8*)&bIsChair, sizeof(bIsChair));
		}
		break;
	case evtp_Conf_MultConf_Notify:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_MultConf_Notify, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleMultipleConference, NULL, 0);
		}
		break;
	case evtp_Conf_CancelMultConf_Notify:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CancelMultConf_Notify, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleCancelMultipleConference, NULL, 0);
		}
		break;
	case evtp_Conf_JoinConf_Notify:
		{
			TConfEpIDInfo* ptUms = (TConfEpIDInfo*)pBuf;
			TMDLTERMINALINFO tPa;
			tPa.m_byMcuNo = (u8)ptUms->m_wConfID;
			tPa.m_byTerNo = (u8)ptUms->m_wEpID;
			strncpy(tPa.m_achTerminalId, ptUms->m_tAlias.m_abyAlias, MAX_TERMINALID_LEN);

			if (emTpSIP == tHandle.m_emProtocol)
			{
				s8 *pzAliasUTF8 = NULL;
				gb2312_to_utf8((s8 *)tPa.m_achTerminalId, &pzAliasUTF8);
				strncpy((s8 *)tPa.m_achTerminalId, pzAliasUTF8, MAX_TERMINALID_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_JoinConf_Notify, ConfID:%d, EpID:%d, DstID:%d\n", wConfID, wEpID, ptUms->m_wEpID));
			PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleTerminalJoinConf, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case evtp_Conf_LeftConf_Notify:
		{
			TConfEpIDInfo* ptUms = (TConfEpIDInfo*)pBuf;
			TMDLTERMINALINFO tPa;
			tPa.m_byMcuNo = (u8)ptUms->m_wConfID;
			tPa.m_byTerNo = (u8)ptUms->m_wEpID;
			strncpy(tPa.m_achTerminalId, ptUms->m_tAlias.m_abyAlias, MAX_TERMINALID_LEN);
			
			if (emTpSIP == tHandle.m_emProtocol)
			{
				s8 *pzAliasUTF8 = NULL;
				gb2312_to_utf8((s8 *)tPa.m_achTerminalId, &pzAliasUTF8);
				strncpy((s8 *)tPa.m_achTerminalId, pzAliasUTF8, MAX_TERMINALID_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_LeftConf_Notify, ConfID:%d, EpID:%d, DstID:%d\n", wConfID, wEpID, ptUms->m_wEpID));
			PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleterminalLeftConf, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case evtp_Conf_StatusInfo_Notify:
		{			
			TTPConfInfoNtfy* ptConf = (TTPConfInfoNtfy*)(pBuf);
			TConfInfo tPaConfInfo;
			TPAConfStatusInd tPaInd;
			tPaInd.m_wMeetingId = ptConf->m_wConfID;
			tPaInd.m_tBeginTime = ptConf->m_tBeginTime;			
			strncpy(tPaInd.m_achConfName, ptConf->m_tConf.m_abyAlias, PA_MAX_H323ALIAS_LEN);
			strncpy(tPaInd.m_achChairName, ptConf->m_tChair.m_abyAlias, PA_MAX_H323ALIAS_LEN);
			strncpy(tPaInd.m_achSpeakName, ptConf->m_tSpeak.m_abyAlias, PA_MAX_H323ALIAS_LEN);
			tPaInd.m_bMixMotive = ptConf->m_bMixMotive;
			tPaInd.m_wChairVidSndCap = ptConf->m_wChairVidSndCap;
			tPaInd.m_wChairAudSndCap = ptConf->m_wChairAudSndCap;
			tPaInd.m_bSpeakOnline = ptConf->m_bSpeakOnline;

			if (emTpSIP == tHandle.m_emProtocol )
			{
				s8 *pzAliasUTF8 = NULL;
				gb2312_to_utf8((s8 *)tPaInd.m_achConfName, &pzAliasUTF8);
				strncpy((s8 *)tPaInd.m_achConfName, pzAliasUTF8, PA_MAX_H323ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
				
				gb2312_to_utf8((s8 *)tPaInd.m_achChairName, &pzAliasUTF8);
				strncpy((s8 *)tPaInd.m_achChairName, pzAliasUTF8, PA_MAX_H323ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
				
				gb2312_to_utf8((s8 *)tPaInd.m_achSpeakName, &pzAliasUTF8);
				strncpy((s8 *)tPaInd.m_achSpeakName, pzAliasUTF8, PA_MAX_H323ALIAS_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}
			if ( emTpH323 == tHandle.m_emProtocol )
			{

				CConfId tConfIdInfo;
				tConfIdInfo.SetConfId((u8*)&ptConf->m_wConfID,sizeof(u16));
				tPaConfInfo.SetConfId(tConfIdInfo);
				TKdvTime tStartTime;
				tStartTime.SetTime(&ptConf->m_tBeginTime);
				tPaConfInfo.SetKdvStartTime(tStartTime);
				tPaConfInfo.SetConfName(ptConf->m_tConf.m_abyAlias);
				TMtAlias tMtChairInfo;
				TMtAlias tMtSpeakerInfo;
				tMtChairInfo.m_AliasType = mtAliasTypeH323ID;
				tMtSpeakerInfo.m_AliasType = mtAliasTypeH323ID;
				strncpy(tMtChairInfo.m_achAlias, ptConf->m_tChair.m_abyAlias, MAXLEN_ALIAS);

				strncpy(tMtSpeakerInfo.m_achAlias, ptConf->m_tSpeak.m_abyAlias, MAXLEN_ALIAS);
				tPaConfInfo.SetChairAlias(tMtChairInfo);
				tPaConfInfo.SetSpeakerAlias(tMtSpeakerInfo);

				//指定终端双流模式，所有终端都可以发
				TConfAttrb tConfAttrb;
				tConfAttrb.SetDualMode(TRUE);
				tPaConfInfo.SetConfAttrb(tConfAttrb);

			}
			 
			TMDLTERLABEL tLabel;
			tLabel.m_byMcuNo = (u8)ptConf->m_wConfID;
			tLabel.m_byTerNo = (u8)ptConf->m_wEpID;
			
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StatusInfo_Notify, ConfID:%d, EpID:%d, CallID:%d, MeetingID:%d, Conf:%s, Chair:%s, vidNum:%d, audNum:%d, Motive:%d\n"
				, wConfID, wEpID, nPaID, ptConf->m_wConfID, ptConf->m_tConf.m_abyAlias, ptConf->m_tChair.m_abyAlias, tPaInd.m_wChairVidSndCap, tPaInd.m_wChairAudSndCap, tPaInd.m_bMixMotive));

			if ( tHandle.m_emProtocol == emTpSIP )
			{
				PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfStatusIndicate, (u8*)&tPaInd, sizeof(tPaInd));		
			}
			else if ( tHandle.m_emProtocol == emTpH323 )
			{
				PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleTerminalNumberAssign, (u8*)&tLabel, sizeof(tLabel));
				tPaConfInfo.Print();
 				PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleConfInfoRsp, (u8*)&tPaConfInfo, sizeof(tPaConfInfo));
			}	
		}
		break;
	case evtp_Conf_CnsSpeakerCascad_Notify:
		{
			TCnsSpeakerAdjust& tAdjust = *(TCnsSpeakerAdjust*)pBuf;

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CnsSpeakerCascad_Notify, ConfID:%d, EpID:%d, CallID:%d, childId:%d, wEpID:%d\n"
				, wConfID, wEpID, nPaID, tAdjust.m_tKey.m_wEpID, tAdjust.m_wSpeakerIndex));

			TPACascadingSpeaker tPA;			
//			strncpy(tPA.m_tNodeKey.m_tKey.m_szEpID, tAdjust.m_tKey.m_tKey.m_szEpID, PA_NODECHANGEINFO);	
			tPA.m_tNodeKey.m_wEpID = tAdjust.m_tKey.m_wEpID;
			tPA.m_wEpID = tAdjust.m_wEpID;
			tPA.m_wSpeaker = tAdjust.m_wSpeakerIndex;
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfCascadingSpeaker, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_MuteRemoteEp_Cmd:
		{
			TMuteRmtEpCmd* ptRmtEp = (TMuteRmtEpCmd*)(pBuf);
			if ( tHandle.m_emProtocol == emTpSIP )
			{
				TPAPeerMuteCmd tMuteCmd;
				tMuteCmd.m_bMute = ptRmtEp->m_bMute;
				tMuteCmd.m_wEpId = ptRmtEp->m_wEpID;

				PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfPeerMuteCmd, (u8*)&tMuteCmd, sizeof(tMuteCmd));
			}
			else
			{
				TMDLTERLABEL tTer;
				tTer.m_byMcuNo = (u8)wConfID;
				tTer.m_byTerNo = (u8)ptRmtEp->m_wEpID;
				BOOL32 bMute = ptRmtEp->m_bMute;
				
				u8 abyBuf[sizeof(TMDLTERLABEL) + sizeof(BOOL32)];
				memcpy(abyBuf, &tTer, sizeof(tTer));
				memcpy(abyBuf + sizeof(tTer), &bMute, sizeof(BOOL32));
				
				PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleMakeTerMuteCmd, abyBuf, sizeof(abyBuf));
			}	

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_MuteRemoteEp_Cmd, ConfID:%d, EpID:%d, CallID:%d, bMute:%d, DstID:%d\n"
				, wConfID, wEpID, nPaID, ptRmtEp->m_bMute, ptRmtEp->m_wEpID));
			
		}
		break;
	case evtp_Conf_MuteRemoteEp_Ind:
		{
			TMuteRmtEpInd* ptRmtEp = (TMuteRmtEpInd*)(pBuf);
			TPAPeerMuteInd tMuteInd;
			tMuteInd.m_bMute = ptRmtEp->m_bMute;
//			strncpy(tMuteInd.m_tPeerMute.m_tKey.m_szEpID, ptRmtEp->m_tKeyID.m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);
			tMuteInd.m_tPeerMute.m_wEpID = ptRmtEp->m_tKeyID.m_wEpID;
			
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_MuteRemoteEp_Ind, ConfID:%d, EpID:%d, CallID:%d, bMute:%d, keyID:%s, childId:%d\n"
				, wConfID, wEpID, nPaID, tMuteInd.m_bMute, tMuteInd.m_tPeerMute.m_tKey.m_achEpID, tMuteInd.m_tPeerMute.m_wEpID));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfPeerMuteInd, (u8*)&tMuteInd, sizeof(tMuteInd));
		}
		break;
	case evtp_Conf_QuietRemoteEp_Cmd:
		{
			TQuietRmtEpCmd* ptRmtEp = (TQuietRmtEpCmd*)(pBuf);

			if ( tHandle.m_emProtocol == emTpSIP )
			{
				TPAPeerMuteCmd tMuteCmd;
				tMuteCmd.m_bMute = ptRmtEp->m_bQuiet;
				tMuteCmd.m_wEpId = ptRmtEp->m_wEpID;
				
				PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfPeerSoundOffCmd, (u8*)&tMuteCmd, sizeof(tMuteCmd));
			}
			else
			{
				TMDLTERLABEL tTer;
				tTer.m_byMcuNo = (u8)wConfID;
				tTer.m_byTerNo = (u8)ptRmtEp->m_wEpID;
				BOOL32 bQuiet = ptRmtEp->m_bQuiet;

				u8 abyBuf[sizeof(TMDLTERLABEL) + sizeof(BOOL32)];
				memcpy(abyBuf, &tTer, sizeof(tTer));
				memcpy(abyBuf + sizeof(tTer), &bQuiet, sizeof(BOOL32));

				PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleMakeTerQuietCmd, abyBuf, sizeof(abyBuf));

			}

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_QuietRemoteEp_Cmd, ConfID:%d, EpID:%d, CallID:%d, Quiet:%d, DstID:%d\n"
				, wConfID, wEpID, nPaID, ptRmtEp->m_bQuiet, ptRmtEp->m_wEpID));
		}
		break;
	case evtp_Conf_QuietRemoteEp_Ind:
		{
			TQuietRmtEpInd* ptRmtEp = (TQuietRmtEpInd*)(pBuf);
			TPAPeerMuteInd tMuteInd;
			tMuteInd.m_bMute = ptRmtEp->m_bQuiet;
//			strncpy(tMuteInd.m_tPeerMute.m_tKey.m_szEpID, ptRmtEp->m_tKeyID.m_tKey.m_szEpID, PA_MAX_H323ALIAS_LEN);	
			tMuteInd.m_tPeerMute.m_wEpID = ptRmtEp->m_tKeyID.m_wEpID;
			
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_QuietRemoteEp_Ind, ConfID:%d, EpID:%d, CallID:%d, Quiet:%d, keyID:%s, childId:%d\n"
				, wConfID, wEpID, nPaID, tMuteInd.m_bMute, tMuteInd.m_tPeerMute.m_tKey.m_achEpID, tMuteInd.m_tPeerMute.m_wEpID));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfPeerSoundOffInd, (u8*)&tMuteInd, sizeof(tMuteInd));
		}
		break;
	case evtp_Conf_CallExistEPTr_cmd:
		{
			u16 wRmtEp = *(u16*)(pBuf);
			TTPAlias tAlias = *(TTPAlias*)(pBuf+sizeof(u16));
			TPAAlias tPaAlias;
			ConvertAliasFromUmsToStack(tAlias, tPaAlias);

			if (emTpSIP == tHandle.m_emProtocol)
			{
				s8 *pzAliasUTF8 = NULL;
				gb2312_to_utf8((s8 *)tPaAlias.m_achAlias, &pzAliasUTF8);
				strncpy((s8 *)tPaAlias.m_achAlias, pzAliasUTF8, PA_MAX_NAME_LEN);
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;
			}

			u8 abBuf[sizeof(u16)+sizeof(TPAAlias)] = {0};
			memcpy(abBuf, &wRmtEp, sizeof(u16));
			memcpy(abBuf+sizeof(u16), &tPaAlias, sizeof(TPAAlias));

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CallExistEPTr_cmd, ConfID:%d, EpID:%d, CallID:%d, CallNode:%d, Alias:%s, EmProtocol:%d\n"
				, wConfID, wEpID, nPaID, wRmtEp, tAlias.m_abyAlias, tHandle.m_emProtocol));			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfCallCascadingOff, abBuf, sizeof(u16)+sizeof(TPAAlias));
		}
		break;
	case evtp_Conf_DropEPTr_cmd:
		{
			TDropEpCmd* ptCmd = (TDropEpCmd*)(pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_DropEPTr_cmd, ConfID:%d, EpID:%d, CallID:%d, DstID:%d, del:%d\n"
				, wConfID, wEpID, nPaID, ptCmd->m_wEpID, ptCmd->m_bDel));			
			THangupCascadingConf tPA;
			tPA.m_wEpId = ptCmd->m_wEpID;
			tPA.m_bClear = ptCmd->m_bDel;
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConfHangUpCascadingConf, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_TvMonitor_Cmd:
		{			
			TTvMonitorCmdTr* ptUms = (TTvMonitorCmdTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_TvMonitor_Cmd, ConfID:%d, EpID:%d, CallID:%d, index:%d, dst:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_wIndex, ptUms->m_wEpID));
			TPATvMonitorCmd tPa;
			ConvertAddTvMonitorFromUmsToStack(tPa, *ptUms);
			MdlHint(Ums_Mdl_Stack,("设给PA的结构体屏号为%d\n",tPa.m_wScreenNum));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAAddTvMonitorCmd, (u8*)&tPa, sizeof(tPa));
		}		
		break;
	case evtp_Conf_TvMonitor_Ind:
		{			
			TTvMonitorIndTr* ptUms = (TTvMonitorIndTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_TvMonitor_Ind, ConfID:%d, EpID:%d, CallID:%d, Index:%d, wEpID:%d\n"
				, wConfID, wEpID, nPaID, ptUms->m_wIndex, ptUms->m_wEpID));
			TPATvMonitorInd tPA;
			ConvertAddTvMonitorIndFromUmsToStack(tPA, *ptUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAAddTvMonitorInd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_Conf_TvMonitor_stop:
		{			
			u16* ptUms = (u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_TvMonitor_stop, ConfID:%d, EpID:%d, CallID:%d, wIndex:%d\n", wConfID, wEpID, nPaID, *ptUms));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAStopMonitorCmd, (u8*)ptUms, sizeof(u16));
		}
		break;
	case evtp_Conf_AskKeyByScreen :
		{
			TAskKeyByScreenTr* ptUms = (TAskKeyByScreenTr*)pBuf;
			TPAAskKeyByScreenTr tPa;
			tPa.m_wEpID = ptUms->m_wEpID;
			tPa.m_wScreenNum = ptUms->m_wScreenIndex;
			tPa.m_bReqBySys = ptUms->m_bReqBySys;
			tPa.m_dwAskType = ptUms->m_dwAskType;
			tPa.m_dwRervse1 = ptUms->m_dwRervse1;
			tPa.m_dwRervse2 = ptUms->m_dwRervse2;
			MdlLowDtl(Ums_Mdl_Stack, (">>>> evtp_Conf_AskKeyByScreen, ConfID:%d, EpID:%d, CallID:%d, wDstEp:%d, Screen:%d, bSys:%d, Type:%d\n", 
									wConfID, wEpID, nPaID, ptUms->m_wEpID, ptUms->m_wScreenIndex, ptUms->m_bReqBySys, tPa.m_dwAskType));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAAskKeybyScreen, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case evtp_Conf_ChairCap_Notify:
		{
			TPANodeCapsetTr tPA;
			TChairInfoTr* ptUms = (TChairInfoTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_ChairCap_Notify, ConfID:%d, EpID:%d, CallID:%d, index:%d\n", wConfID, wEpID, nPaID, ptUms->m_wSpeakerIndex));
			
			tPA.m_wSpeakindex = ptUms->m_wSpeakerIndex;
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAChairCapNotify, (u8*)&tPA, sizeof(tPA));
		}
		break;

	case evtp_Conf_CnsList_Notify:
		{
			u8 abyBuf[sizeof(TMDLTERINFOLIST) + sizeof(BOOL32) + sizeof(TConfCnsList)];
			TMDLTERINFOLIST tList;
			BOOL32 bFlag = TRUE;
			TPAConfCnsList tPA;

			TConfCnsInfo* ptUms = (TConfCnsInfo*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CnsList_Notify, ConfID:%d, EpID:%d, CallID:%d, CnsNums:%d, emOpr:%s\n",
									wConfID, wEpID, nPaID, ptUms->m_wNum, TpEnumString(EmTpOprType, ptUms->m_emOpr)));
			ConvertConfCnsListFromUmsToStack(tPA, *ptUms);

			ConvertOpTypeFromUmsToStack(ptUms->m_emOpr, tList.m_emOperateType);
			for ( u16 wIndex = 0; wIndex < ptUms->m_wNum; wIndex++ )
			{
				if (emTPEndpointTypeUMS == ptUms->m_tConfCnsList[wIndex].m_emEpType)
				{//如果节点是个ums，此节点不需要通知到终端，避免终端界面的会议列表中会显示一个模板名的会场
					continue;
				}
				tList.m_atTerInfoList[tList.m_byNum].m_byMcuNo = MCU_NO;
				tList.m_atTerInfoList[tList.m_byNum].m_byConfNo = (u8)tHandle.GetConfID();
				tList.m_atTerInfoList[tList.m_byNum].m_byTerNo = (u8)ptUms->m_tConfCnsList[wIndex].m_wEpID;
				tList.m_atTerInfoList[tList.m_byNum].m_bOnline = ptUms->m_tConfCnsList[wIndex].m_bOnline;
				tList.m_atTerInfoList[tList.m_byNum].m_bLastPack = ptUms->m_bLastPack;
				memcpy(tList.m_atTerInfoList[tList.m_byNum].m_achTerminalId, ptUms->m_tConfCnsList[wIndex].m_achRoomName, TP_MAX_ALIAS_LEN+1);
				++(tList.m_byNum);
			}
			
			memcpy(abyBuf, &tList, sizeof(TMDLTERINFOLIST));
			memcpy(abyBuf+sizeof(TMDLTERINFOLIST), &bFlag, sizeof(BOOL32));
			memcpy(abyBuf+sizeof(TMDLTERINFOLIST)+sizeof(BOOL32), &(tPA.m_tCnsList), sizeof(TConfCnsList));

			PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleTerminalIDListResponse, abyBuf, sizeof(abyBuf));
		}
		break;
	case evtp_Conf_ViewLocal_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_ViewLocal_Cmd, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAViewLocal, NULL, 0);
		}		
		break;
	case evtp_Conf_CancelViewLocal_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_CancelViewLocal_Cmd, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACancelViewlocal, NULL, 0);
		}		
		break;

	case evtp_cascade_GetVid_cmd:
		{			
			TViewCmdTr* ptUms = (TViewCmdTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_GetVid_cmd, ConfID:%d, EpID:%d, dst:%d, index:%d\n", wConfID, wEpID, ptUms->m_wEpID, ptUms->m_wIndex));
			TPAViewCmd tPA;
			ConvertViewCmdFromUmsToStack(tPA, *ptUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACascadeGetVidcmd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_cascade_GetVid_ack:
		{			
			TViewAckTr* ptUms = (TViewAckTr*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_GetVid_ack, ConfID:%d, EpID:%d, index:%d, ret:%d\n", wConfID, wEpID, ptUms->m_wIndex, ptUms->m_emRes));
			
			TPAViewAck tPA;
			ConvertViewIndFromUmsToStack(tPA, *ptUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACascadeGetVidInd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_cascade_StopGetVid_cmd:
		{
			u16 tUms = *(u16*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_StopGetVid_cmd, ConfID:%d, EpID:%d, chan:%d\n", wConfID, wEpID, tUms));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACascadeStopGetVidcmd, (u8*)&tUms, sizeof(tUms));
		}
		break;

	case evtp_Conf_FlowCtrol:
		{
			TFlowControl tUms = *(TFlowControl*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_FlowCtrol, ConfID:%d, EpID:%d, DstEp:%d, Band:%d\n"
				, wConfID, wEpID, tUms.m_tEpKey.m_wEpID, tUms.m_wBand));

			TPAFlowControl tPa;
			ConvertEpKeyFromUmsToStack(tUms.m_tEpKey, tPa.m_tEpKey);
			tPa.m_wBand = tUms.m_wBand;
			tPa.m_wEncNo = tUms.m_wEncNo;
			tPa.m_dwEnOpr = tUms.m_dwOpr;
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACascadeFlowCtrl, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case evtp_Conf_AdjustFrameRate:
		{
			TAdjustFrameRate tUms = *(TAdjustFrameRate*)pBuf;

			BOOL32 bRet = FALSE;
			if( tHandle.m_emProtocol == emTpSIP )
			{
				TPAAdjustFrameRate tPa;
				tPa.m_wEpID = tUms.m_wEpID;
				tPa.m_wFrameRate = tUms.m_wFrameRate;
				tPa.m_bReset = tUms.m_bReset;
				bRet = PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAAdjustFrameRate_Cmd, (u8*)&tPa, sizeof(tPa));

				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_AdjustFrameRate, Sip ConfID:%d, EpID:%d, DstEp:%d, FrameRate:%d, Ret:%d\n"
					, wConfID, wEpID, tUms.m_wEpID, tUms.m_wFrameRate, bRet));

			}
			else
			{
				emModuleChannelType emChnType = emModuleChanSendPrimoVideo;
				u8 byFramteR = (u8)tUms.m_wFrameRate;
				u8 abyBuf[sizeof(emModuleChannelType) + sizeof(u8)];
				memcpy(abyBuf, &emChnType, sizeof(emChnType));
				memcpy(abyBuf + sizeof(emChnType), &byFramteR, sizeof(u8));

				bRet = PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModulevideoFpsChangeCmd, abyBuf, sizeof(abyBuf));

				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_AdjustFrameRate, H323 ConfID:%d, EpID:%d, DstEp:%d, FrameRate:%d, Ret:%d\n"
					, wConfID, wEpID, tUms.m_wEpID, byFramteR, bRet));
			}
		}
		break;

	case evtp_Conf_AdjustVidRes:
		{
			TAdjustVidRes tUms = *(TAdjustVidRes*)pBuf;
			
			BOOL32 bRet = FALSE;
			if( tHandle.m_emProtocol == emTpSIP )
			{
				TPAAdjustVidRes tPa;
				tPa.m_wEpID = tUms.m_wEpID;
				tPa.m_wScreenIndx = tUms.m_wScreenIndx;
				tPa.m_dwVidRes = tUms.m_dwVidRes;
				tPa.m_bReset = tUms.m_bReset;
				bRet = PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAAdjustVidRes_Cmd, (u8*)&tPa, sizeof(tPa));

				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_AdjustVidRes, Sip ConfID:%d, EpID:%d, DstEp:%d, ScrIndx:%d, VidRes:%d, Ret:%d\n"
														, wConfID, wEpID, tUms.m_wEpID, tUms.m_wScreenIndx, tUms.m_dwVidRes, bRet));
			}
			else
			{
				//emAVType emTVType = emModuleVideoType;
				#define      LOGCHL_VIDEO					1	//主视频逻辑通道

				u32 dwTVType = LOGCHL_VIDEO;
				u8 byFramteR = VIDEO_FORMAT_HD1080;

				EmTpVideoResolution emRes = (EmTpVideoResolution)tUms.m_dwVidRes;

				ConvertMtVIDEO_FORMATFromUmsToStack(emRes, byFramteR);

				u8 abyBuf[sizeof(dwTVType) + sizeof(u8)];
				memcpy(abyBuf, &dwTVType, sizeof(dwTVType));
				memcpy(abyBuf + sizeof(dwTVType), &byFramteR, sizeof(u8));
				
				bRet = PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModulevideoFormatChangeCmd, abyBuf, sizeof(abyBuf));

				MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_AdjustVidRes, H323 ConfID:%d, EpID:%d, DstEp:%d, VidRes:%d, Ret%d\n"
														, wConfID, wEpID, tUms.m_wEpID, tUms.m_dwVidRes, bRet));
			}
		}
		break;

	case ev_MakeCall_Req:
		{
			UmsMakeCall(tHandle, *(TMakeCallPara*)pBuf);
		}
		break;
	case ev_MakeChan_Req:
		{
			BOOL32 bIsDual = *(BOOL32*)(pBuf + sizeof(TUmsNodeCapset));
			UmsMakeChan(tHandle, *(TUmsNodeCapset*)pBuf, bIsDual);
		}
		break;
	case ev_AnwserCall_IND:
		{
			s8* pData = (s8*)pBuf;
			BOOL32 bAnwser = *(BOOL32*)pData;
			EmCnsCallReason enReason = *(EmCnsCallReason*)(pData+sizeof(BOOL32));
			TMakeCallPara *ptCall = (TMakeCallPara*)(pData+sizeof(BOOL32)+sizeof(EmCnsCallReason));
			UmsAnswerCall(tHandle, bAnwser, ptCall, enReason);
		}
		break;
	case evtp_Close_Chan_Req:
		{
			s8* pData = (s8*)pBuf;
			EmChanType emType = *(EmChanType*)pData;
			TUmsNodeCapset ptNode = *(TUmsNodeCapset*)(pData + sizeof(EmChanType));

			UmsCloseChan(tHandle, emType, ptNode);
		}
		break;
	case evtp_cascade_OpenChairChan_cmd:
		{
			TCascadeOpenChanCmd* ptUms = (TCascadeOpenChanCmd*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenChairChan_cmd, ConfID:%d, EpID:%d, dst:%d\n", wConfID, wEpID, ptUms->m_wEpID));

			TPACascadeOpenChanCmd tPA;
			ConvertCascadeOpenChanCmdFromUmsToStack(tPA, *ptUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsCascadeOpenChairChan_Cmd, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case evtp_cascade_OpenChairChan_ack:
		{
			TCascadeOpenChanAck* ptUms = (TCascadeOpenChanAck*)pBuf;
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_cascade_OpenChairChan_ack, ConfID:%d, EpID:%d, ret:%d\n", wConfID, wEpID, ptUms->m_wEpID));
			
			TPACascadeOpenChanAck tPA;
			ConvertCascadeOpenChanAckFromUmsToStack(tPA, *ptUms);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsCascadeOpenChairChan_Ack, (u8*)&tPA, sizeof(tPA));
		}
		break;
	case ev_HungUp_Req:
		{
			EmCnsCallReason* ptUms = (EmCnsCallReason*)pBuf;
			UmsHangUp(tHandle, *ptUms);
		}
		break;
	case ev_Register_Req:
		{
			s8* pData = (s8*)pBuf;
			TUmsSipRegCfg tCfg = *(TUmsSipRegCfg*)pData;
			u16 wAliasNum = *(u16*)(pData+sizeof(TUmsSipRegCfg));
			TTPAlias *ptAlias = (TTPAlias*)(pData+sizeof(TUmsSipRegCfg)+sizeof(u16));

			UmsRegister(tHandle, tCfg, ptAlias, wAliasNum);
		}
		break;

	case ev_gk_Register_Req:
		{
			s8* pData = (s8*)pBuf;
			TRegCfg tCfg = *(TRegCfg*)pData;
			u16 wAliasNum = *(u16*)(pData+sizeof(TRegCfg));

			UmsGkRegister(tHandle, tCfg, wAliasNum);
		}
		break;

	case ev_UnRegister_Req:
		{
			s8* pData = (s8*)pBuf;
			EmTpRegType emType = *(EmTpRegType*)pData;
			UmsUnregister(tHandle, emType);
		}
		break;
	case ev_UmsGetRegInfo_Req:
		{
			u8* pData = (u8*)pBuf;
			TUmsSipRegCfg* ptRegCfg = (TUmsSipRegCfg*)pData;
			EmGetRegInfoType emType = *(EmGetRegInfoType*)(pData + sizeof(TUmsSipRegCfg));
			u32 dwSipHandle = 0;
			u32 dwGkhandle = 0;
			TP_SAFE_CAST(dwSipHandle, pData+sizeof(TUmsSipRegCfg)+sizeof(EmGetRegInfoType));
			TP_SAFE_CAST(dwGkhandle, pData+sizeof(TUmsSipRegCfg)+sizeof(EmGetRegInfoType)+sizeof(u32));

			MdlHint(Ums_Mdl_Stack, ("ev_UmsGetRegInfo_Req SipHandle:%d, GkHandle:%d, emType:%d.\n",
									 dwSipHandle, dwGkhandle, emType));

			TPAGetRegInfo tPAGetRegInfo;

			ConvertGetRegInfoTypeFromUmsToStack( emType, tPAGetRegInfo.m_emType );
			tPAGetRegInfo.m_dwRegIP = ptRegCfg->dwRegIP;
			tPAGetRegInfo.m_wRegPort = ptRegCfg->wRegPort;
			tPAGetRegInfo.m_dwLocalIP = GetLocalIpByDstIp(ptRegCfg->dwRegIP);//ptRegCfg->m_atAdaptAddr[0].GetIP();
			tPAGetRegInfo.m_wLocalPort = TP_UMS_SIP_LISTIEN_PORT; //ptRegCfg->m_atAdaptAddr[0].GetPort();
			PA_GetRegInfoReq(tHandle.handAppCall, (HMDLREG)dwSipHandle, (HMDLREG)dwGkhandle, tPAGetRegInfo);
		}
		break;
	case evtpH323_Conf_MultipleConference_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtpH323_Conf_MultipleConference_Ind, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			PA_SendConfCtrl(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emModuleMultipleConference, NULL, 0);
		}
		break;

	case evtp_Conf_Clear:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_Clear, ConfID:%d\n", wConfID));
			PA_MCStopConference((HMDLAPPCONFID)wConfID);
		}
		break;
		
	case evtp_Conf_StopRecPlay_Req:
		{
			u8* pData = (u8*)pBuf;
			u32 dwParam = 0;
			TP_SAFE_CAST(dwParam, pData);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_StopRecPlay_Req, Param:%d\n", dwParam));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsConfStopRecPlay_Req, (u8*)(&dwParam), sizeof(u32));
		}
		break;

	case evtp_Conf_RecPlayState_Nty:
		{
			u8* pData = (u8*)pBuf;
			TUpRecPlayState tState;
			TP_SAFE_CAST(tState, pData);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_Conf_RecPlayState_Nty, IsPlaying:%d, DualPlaying:%d, FileName:%s\n",
									tState.m_bIsPlayIng, tState.m_bIsDualPlayIng,
									tState.m_achFileName));
			
			TPAUmsUpRecPlayState tInfo;
			tInfo.m_bIsPlayIng = tState.m_bIsPlayIng;
			tInfo.m_bIsDualPlayIng = tState.m_bIsDualPlayIng;
			memcpy(tInfo.m_achFileName, tState.m_achFileName, TP_REC_FILE_LEN);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsConfRecPlayState_Nty, (u8*)(&tInfo), sizeof(TPAUmsUpRecPlayState));
		}
		break;

	case ev_UMS_CNC_SelView_Ntfy:
		{
			TTPSelViewNtfy tNtfy;
			TP_SAFE_CAST(tNtfy, (u8*)pBuf);

			TPASelViewNtfy tPa;
			ConvertSelViewNtfyFromUmsToStack(tNtfy, tPa);

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SelView_Ntfy confID:%d, epId:%d, (%d,%d; %d,%d; %d,%d;)\n", 
				tNtfy.m_wConfID, tPa.m_wEpID, 
				tPa.m_atSelView[0].m_wDstID, tPa.m_atSelView[0].m_emType,
				tPa.m_atSelView[1].m_wDstID, tPa.m_atSelView[1].m_emType,
				tPa.m_atSelView[2].m_wDstID, tPa.m_atSelView[2].m_emType));

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_UMC_SelView_Ntfy, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case ev_UMS_CNC_SelView_Ind:
		{
			TTPSelViewInd tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);

			TPATPSelViewInd tPa;
			ConvertSelViewIndFromUmsToStack(tInd, tPa);

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SelView_Ind Ret:%d, EpID:%d, ScrIndx:%d, DstID:%d\n",
				tPa.m_emRet, tPa.m_tSelView.m_wEpID, tPa.m_tSelView.m_wScreenIndx, tPa.m_tSelView.m_wDstID));

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNC_SelView_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case ev_CNC_UMS_SelView_Req:
		{
			TTPSelViewReq tReq;
			TP_SAFE_CAST(tReq, (u8*)pBuf);

			TPATPSelViewReq tPa;
			ConvertSelViewReqFromUmsToStack(tReq, tPa);

			MdlHint(Ums_Mdl_Stack, (">>>> ev_CNC_UMS_SelView_Req bSel:%d, EpID:%d, ScrIndx:%d, DstID:%d, Type:%d.\n",
				tPa.m_bSel, tPa.m_wEpID, tPa.m_wScreenIndx, tPa.m_wDstID, tPa.m_emType));

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACNC_UMS_SelView_Req, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_UMS_CNC_RervesBrdVmp_Ind:
		{
			TRersvesEqpRsp tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);
			
			TPARersvesEqpRsp tPa;
			tPa.m_emRet = tRsp.m_emRet;
			tPa.m_wConfID = tRsp.m_wConfID;
			tPa.m_tRersvesReq.m_bRersves = tRsp.m_tRersvesReq.m_bRersves;
			tPa.m_tRersvesReq.m_wConfID = tRsp.m_tRersvesReq.m_wConfID;
			ConvertEqpInfoFromUmsToStack(tRsp.m_tRersvesReq.m_tEqp, tPa.m_tRersvesReq.m_tEqp);
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_RervesBrdVmp_Ind ConfID:%d, Ret:%d, bRervers:%d, EqpID:%d.\n",
				tPa.m_wConfID, tPa.m_emRet, tPa.m_tRersvesReq.m_bRersves, tPa.m_tRersvesReq.m_tEqp.m_byEqpID));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNC_RervesBrdVmp_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_UMS_CNC_SetBrdVmp_Ind:
		{
			TSetVmpInfoRsp tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);
			
			TPASetVmpInfoRsp tPa;
			tPa.m_emRet = tRsp.m_emRet;
			tPa.m_wConfID = tRsp.m_wConfID;
			tPa.m_tReq.m_wConfID = tRsp.m_tReq.m_wConfID;
			ConvertEqpInfoFromUmsToStack(tRsp.m_tReq.m_tEqp, tPa.m_tReq.m_tEqp);
			ConvertVmpStyleInfoFromUmsToStack(tRsp.m_tReq.m_tStyle, tPa.m_tReq.m_tStyle);
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SetBrdVmp_Ind ConfID:%d, Ret:%d, EqpID:%d, Style:%d, speakerindx:%d, chairindx:%d.\n",
				tPa.m_wConfID, tPa.m_emRet, tPa.m_tReq.m_tEqp.m_byEqpID, tPa.m_tReq.m_tStyle.m_emVmpStyle, 
				tPa.m_tReq.m_tStyle.m_wSpeakerIndx, tPa.m_tReq.m_tStyle.m_wChairIndx));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNC_SetBrdVmp_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_UMS_CNC_BrdVmp_Ind:
		{
			TBrdVmpRsp tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);
			
			TPABrdVmpRsp tPa;
			tPa.m_emRet = tRsp.m_emRet;
			tPa.m_wConfID = tRsp.m_wConfID;
			tPa.m_tReq.m_wConfID = tRsp.m_tReq.m_wConfID;
			tPa.m_tReq.m_bBrd = tRsp.m_tReq.m_bBrd;
			ConvertEqpInfoFromUmsToStack(tRsp.m_tReq.m_tEqp, tPa.m_tReq.m_tEqp);
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_BrdVmp_Ind ConfID:%d, Ret:%d, EqpID:%d, bBrd:%d.\n",
				tPa.m_wConfID, tPa.m_emRet, tPa.m_tReq.m_tEqp.m_byEqpID, tPa.m_tReq.m_bBrd));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNC_BrdVmp_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_GetVid_Req:
		{
			TGetVidInfo tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);

			TPAGetVidInfo tPa;
			ConvertGetVidInfoFromUmsToStack(tInfo, tPa);

			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Req EpID:%d GetVidIndx:%d, bSmall:%d\n",tHandle.GetEpID(), tInfo.m_tBaseInfo.m_wHandle, tInfo.m_bSamll));

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAGetVid_Req, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_GetVid_Res:
		{
			TGetVidInfoRes tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);
			
			TPAGetVidInfoRes tPa;
			ConvertGetVidResFromUmsToStack(tInfo, tPa);
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Res EpID:%d GetVidIndx:%d, Ret:%d, bSmall:%d\n",
				tHandle.GetEpID(), tInfo.m_tInfo.m_tBaseInfo.m_wHandle, tPa.m_emRes, tInfo.m_tInfo.m_bSamll));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAGetVid_Res, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_GetVid_Stop_Req:
		{
			TGetVidBaseInfo tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);
			
			TPAGetVidBaseInfo tPa;
			ConvertGetVidBaseInfoFromUmsToStack(tInfo, tPa);
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Stop_Req EpID:%d GetVidIndx:%d\n",tHandle.GetEpID(), tInfo.m_wHandle));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAGetVid_Stop_Req, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_GetVid_Stop_Res:
		{
			TStopGetVid tInfo;
			TP_SAFE_CAST(tInfo, (u8*)pBuf);
			
			TPAStopGetVid tPa;
			ConvertGetVidStopResFromUmsToStack(tInfo, tPa);
			
			MdlHint(Ums_Mdl_Stack, (">>>> ev_GetVid_Stop_Res EpID:%d GetVidIndx:%d\n",tHandle.GetEpID(), tInfo.m_tInfo.m_wHandle));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAGetVid_Stop_Res, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_UMS_CNC_BrdVmp_Ntfy:
		{
			TBrdVmpResArray tRsp;
			TP_SAFE_CAST(tRsp, (u8*)pBuf);
			
			TPABrdVmpResArray tPa;

			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_BrdVmp_Ntfy epID:%d VmpNum:%d dtl info tplogdtl.\n", tHandle.GetEpID(), tRsp.m_wNum));

			TPABrdVmpResNtfy* tInd;
			for( u16 wIndex = 0; wIndex < tRsp.m_wNum; wIndex ++ )
			{
				tPa.m_wNum = 1;   // 每次只发一个
				tPa.m_atVmpNtfy[0].m_wConfID = tRsp.m_atVmpNtfy[wIndex].m_wConfID;
				tPa.m_atVmpNtfy[0].m_bVmpAuto = tRsp.m_atVmpNtfy[wIndex].m_bVmpAuto;
				tPa.m_atVmpNtfy[0].m_dwStat = tRsp.m_atVmpNtfy[wIndex].m_emStat;
				ConvertOprTypeFromUmsToStack( tRsp.m_atVmpNtfy[wIndex].m_emOpr, tPa.m_atVmpNtfy[0].m_emOpr);
				ConvertEqpInfoFromUmsToStack(tRsp.m_atVmpNtfy[wIndex].m_tEqpInfo, tPa.m_atVmpNtfy[0].m_tEqpInfo);
				ConvertVmpStyleInfoFromUmsToStack(tRsp.m_atVmpNtfy[wIndex].m_tVmpStyle, tPa.m_atVmpNtfy[0].m_tVmpStyle);
				
				tInd = &tPa.m_atVmpNtfy[0];
				MdlLowDtl(Ums_Mdl_Stack, (" auto:%d, stat:%d, eqpID:%d, style:%d, channum:%d, speakerindx:%d, chairindx:%d, %s\n", 
					tInd->m_bVmpAuto, tInd->m_dwStat, tInd->m_tEqpInfo.m_byEqpID, tInd->m_tVmpStyle.m_emVmpStyle, tInd->m_tVmpStyle.m_wChnlNum,
					tInd->m_tVmpStyle.m_wSpeakerIndx, tInd->m_tVmpStyle.m_wChairIndx, tInd->m_tEqpInfo.m_szEqpAlias));

			
				PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNC_BrdVmp_Ntfy, (u8*)&tPa, sizeof(tPa));
				tPa.Clear();
			}
		}
		break;

	case ev_CNC_UMS_SaveVmpCfg_Cmd:
		{
			TTpVmpMemberCfg tCfg;
			TP_SAFE_CAST(tCfg, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_CNC_UMS_SaveVmpCfg_Cmd EpID:%d ConfID:%d, Style:%d, Num:%d.\n",
				tHandle.GetEpID(), tCfg.m_wConfID, tCfg.m_emStyle, tCfg.m_wEpNum));
			
			TPAVmpMemberCfg tPa;
			tPa.m_wConfID = tCfg.m_wConfID;
			tPa.m_emStyle = (EmPATPVMPStyle)tCfg.m_emStyle;
			tPa.m_wTotalNum = tCfg.m_wTotalNum;
			tPa.m_wFlag = tCfg.m_wFlag;
			tPa.m_wEpNum = tCfg.m_wEpNum;
			tPa.m_bFirst = tCfg.m_bFirst;
			tPa.m_wDualIndx = tCfg.m_wDualIndx;
			tPa.m_wSpeakerIndx = tCfg.m_wSpeakerIndx;

			for ( u16 wIndex = 0; wIndex < tPa.m_wEpNum; wIndex ++ )
			{
				ConvertAliasFromUmsToStack(tCfg.m_atEpList[wIndex].m_tEpAlias, tPa.m_atEpList[wIndex].m_tEpAlias);
				tPa.m_atEpList[wIndex].m_wScrIndx = tCfg.m_atEpList[wIndex].m_wScrIndx;
			}

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACNC_UMS_SaveVmpCfg_Cmd, (u8*)&tPa, sizeof(tPa));
		}
		break;
		
	case ev_UMS_CNC_SaveVmpCfg_Ind:
		{
			TTpVmpMemberCfgInd tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UMS_CNC_SaveVmpCfg_Ind EpID:%d ConfID:%d, Flag:%d, Ret:%d.\n",tHandle.GetEpID(), tInd.m_wConfID, tInd.m_wFlag, tInd.m_bRet));
			
			TPAVmpMemberCfgInd tPa;
			tPa.m_bRet = tInd.m_bRet;
			tPa.m_wFlag = tInd.m_wFlag;
			tPa.m_wConfID = tInd.m_wConfID;
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNC_SaveVmpCfg_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case evtp_CnsJoinConf_Req:
		{
			TTPConfEpInfo tInfo;
			TP_SAFE_CAST(tInfo,(u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_CnsJoinConf_Req ConfID:%d,Index:%d,ConfName:%s\n",tInfo.m_wConfID,tInfo.m_Index,tInfo.m_tCallAddr.GetValidAlias().m_abyAlias));
			TPAConfEpInfo tPa;
			tPa.m_wConfID = tInfo.m_wConfID;
			tPa.m_Index   = tInfo.m_Index;
			tPa.m_bPermit = tInfo.m_bPermit;
			ConvertCallTypeFromUmsToStack(tInfo.m_tCallAddr.m_byCallType,tPa.m_tCallAddr.m_byCallType);
			ConvertAliasFromUmsToStack(tInfo.m_tCallAddr.m_tAlias,tPa.m_tCallAddr.m_tAlias); 
			ConvertAliasFromUmsToStack(tInfo.m_tCallAddr.m_tE164,tPa.m_tCallAddr.m_tE164); 
			tPa.m_tCallAddr.m_dwIP	   = tInfo.m_tCallAddr.m_dwIP;
			tPa.m_tCallAddr.m_bAliasIP = tInfo.m_tCallAddr.m_bAliasIP ;
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPA_CnsJoinConf_Req, (u8*)&tPa, sizeof(tPa));
		}
		break;
	case evtp_CnsJoinConf_Notify:
		{
			u16 wConfID = *(u16*)pBuf;
			TTpCallAddr* ptTAddr = (TTpCallAddr*)(pBuf + sizeof(u16));
			MdlHint(Ums_Mdl_Stack,(">>>> evtp_CnsJoinConf_Notify ConfID:%d,ConfName:%s\n",wConfID,ptTAddr->GetValidAlias().m_abyAlias));
			u8 abyBuf[sizeof(u16) + sizeof(TPACallAddr)];
			TPACallAddr tPAddr;
			ConvertCallTypeFromUmsToStack(ptTAddr->m_byCallType,tPAddr.m_byCallType);
			ConvertAliasFromUmsToStack(ptTAddr->m_tAlias ,tPAddr.m_tAlias); 
			ConvertAliasFromUmsToStack(ptTAddr->m_tE164 ,tPAddr.m_tE164); 
			tPAddr.m_dwIP	   = tPAddr.m_dwIP;
			tPAddr.m_bAliasIP = tPAddr.m_bAliasIP ;
			
			memcpy(abyBuf,&wConfID,sizeof(u16));
			memcpy(abyBuf + sizeof(u16),&tPAddr,sizeof(TPACallAddr)); 

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPACnsJoinConf_Notify, (u8*)abyBuf, sizeof(abyBuf));
		}
		break;

	case ev_UMS_UMS_VmpCasecade_Ntfy:
		{
			TVmpCasecadeNtfy tVmpCasecade ;
			TP_SAFE_CAST(tVmpCasecade,(u8*)pBuf);
			MdlHint(Ums_Mdl_Stack,(">>>> ev_UMS_UMS_VmpCasecade_Ntfy bBrdVmp:%d, emSpeakerVmp:%d\n",tVmpCasecade.m_bBrdVmp,tVmpCasecade.m_emSpeakerVmpType));
			TPAVmpCasecadeNtfy tPaVmpCasecade;
			tPaVmpCasecade.m_bBrdVmp = tVmpCasecade.m_bBrdVmp;
			tPaVmpCasecade.m_bSpeakerVmp = (BOOL32)tVmpCasecade.m_emSpeakerVmpType;
			strncpy(tPaVmpCasecade.m_szBrdVmpAlias,tVmpCasecade.m_szBrdVmpAlias, sizeof(tPaVmpCasecade.m_szBrdVmpAlias));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID),(HMDLAPPCALL)nAppID,emPAUMS_UMS_VmpCasecade_Ntfy,(u8*)&tPaVmpCasecade,sizeof(tPaVmpCasecade));

		}
		break;
	case evtp_JoinWBConf_Ind:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_JoinWBConf_Ind ConfID:%d EpID:%d \n", wConfID, wEpID));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAJoinWBConf_Ind, pBuf, nSize);
		}
		break;
		
	case evtp_JoinWBConf_Cmd:
		{
			u32 dwIP;
			TP_SAFE_CAST(dwIP, pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> emPAJoinWBConf_Cmd ConfID:%d EpID:%d Ip:"IPFORMAT"\n", wConfID, wEpID, u32ToIP(dwIP)));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAJoinWBConf_Cmd, pBuf, nSize);
		}
		break;
		
	case evtp_HungUpWBConf_Cmd:
		{
			MdlHint(Ums_Mdl_Stack, (">>>> emPAHangupWBConf_Cmd ConfID:%d EpID:%d \n", wConfID, wEpID));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAHangupWBConf_Cmd, pBuf, nSize);
		}
		break;
	////////////////////////////////////////////////////////////
	//// 电视墙消息

	case evTPUMS_CNS_hduPlan_Nty:
		{
			THduPlanPackData tPlanPackData;
			TP_SAFE_CAST(tPlanPackData, pBuf);
			TPAHduPlanPackData tPaPackData;
			
			tPaPackData.m_byCol = tPlanPackData.m_byCol;
			tPaPackData.m_byRow = tPlanPackData.m_byRow;
			tPaPackData.m_wNum  = tPlanPackData.m_wNum;
			tPaPackData.m_byFirst  = tPlanPackData.m_byFirst;
			tPaPackData.m_CurentNum  = tPlanPackData.m_CurentNum;

			MdlHint(Ums_Mdl_Stack, (">>>> emPAUMS_CNS_HduPlan_Nty ConfID:%d EpID:%d Col:%d Row:%d AllNum:%d ByFirst:%d CurrentNum:%d \n",
				wConfID, wEpID, tPaPackData.m_byCol, tPaPackData.m_byRow, tPaPackData.m_wNum
				, tPaPackData.m_byFirst, tPaPackData.m_CurentNum));
			
			for(u16 wIndex = 0;wIndex < tPaPackData.m_CurentNum; ++wIndex)
			{
				tPaPackData.m_atUnits[wIndex].m_byReged = tPlanPackData.m_atUnits[wIndex].m_byReged;
				tPaPackData.m_atUnits[wIndex].m_byValid = tPlanPackData.m_atUnits[wIndex].m_byValid;
				tPaPackData.m_atUnits[wIndex].m_wIndex = tPlanPackData.m_atUnits[wIndex].m_wIndex;
				tPaPackData.m_atUnits[wIndex].m_byVmp = tPlanPackData.m_atUnits[wIndex].m_byVmp;
				tPaPackData.m_atUnits[wIndex].m_byVol = tPlanPackData.m_atUnits[wIndex].m_byVol;
				tPaPackData.m_atUnits[wIndex].m_byMute = tPlanPackData.m_atUnits[wIndex].m_byMute;
				tPaPackData.m_atUnits[wIndex].m_byChanIndex = tPlanPackData.m_atUnits[wIndex].m_byChanIndex;
				
				s8 *pzAliasUTF8 = NULL;
				gb2312_to_utf8((s8*)tPlanPackData.m_atUnits[wIndex].m_tHduName.m_abyAlias, &pzAliasUTF8);
				memcpy(tPaPackData.m_atUnits[wIndex].m_tHduName.m_achAlias, pzAliasUTF8, PA_MAX_ALIAS_LEN);
				tPaPackData.m_atUnits[wIndex].m_tHduName.m_achAlias[PA_MAX_ALIAS_LEN-1] = '\0';
				free(pzAliasUTF8);
				pzAliasUTF8 = NULL;

				
				for(u16 wTempIndex = 0; wTempIndex < PA_MAX_VMP_SUBCHAN; ++wTempIndex)
				{
					tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wConfID = tPlanPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wConfID;	
					tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wDstID = tPlanPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wDstID;
					tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wScreenNum = tPlanPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wScreenNum;
					
					gb2312_to_utf8((s8*)tPlanPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_achAlias, &pzAliasUTF8);
					memcpy(tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_achAlias, pzAliasUTF8, PA_MAX_ALIAS_LEN);
					tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_achAlias[PA_MAX_ALIAS_LEN-1] = '\0';
					free(pzAliasUTF8);
					pzAliasUTF8 = NULL;

					ConvertViewEpTypeFromUmsToStack(tPlanPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_emType, tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_emType);
					ConvertHduRunStatusFromUmsToStack(tPlanPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_emStatus, tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_emStatus);
					
					MdlLowDtl(Ums_Mdl_Stack, (">>>> emPAUMS_CNS_HduPlan_Nty VMPIndex:%d VMPConfID:%d VMPDstID:%d , alias:%s ScreenNum:%d EpType:%d RunStatus:%d\n" 
						, wTempIndex, tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wConfID,
						tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wDstID, tPlanPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_achAlias,
						tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_wScreenNum, tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_emType,
						tPaPackData.m_atUnits[wIndex].m_atPlayInfo[wTempIndex].m_emStatus));
				}


				MdlLowDtl(Ums_Mdl_Stack, (">>>> emPAUMS_CNS_HduPlan_Nty index:%d Beged:%d Valid:%d HduIndex:%d HduName:%s Vmp:%d Vol:%d Mute:%d ChanIndex:%d \n" 
					, wIndex , tPaPackData.m_atUnits[wIndex].m_byReged, tPaPackData.m_atUnits[wIndex].m_byValid
					, tPaPackData.m_atUnits[wIndex].m_wIndex, tPlanPackData.m_atUnits[wIndex].m_tHduName.m_abyAlias
					, tPaPackData.m_atUnits[wIndex].m_byVmp, tPaPackData.m_atUnits[wIndex].m_byVol 
					, tPaPackData.m_atUnits[wIndex].m_byMute, tPaPackData.m_atUnits[wIndex].m_byChanIndex));
			}
			
			u8 byPaBuf[sizeof(tPaPackData)] = {0};
			memcpy(byPaBuf, &tPaPackData, sizeof(tPaPackData));

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_HduPlan_Nty, byPaBuf, sizeof(byPaBuf));
		}
		break;
	case evTPUMS_CNS_HduPlay_Ind:
		{
			TPHduBaseInfo tBaseInfo;
			EmTpHduPlayNackReason emReason;
			TP_SAFE_CAST(tBaseInfo, pBuf);
			TP_SAFE_CAST(emReason, pBuf+sizeof(tBaseInfo));

			TPAHduBaseInfo tPaBaseInfo;
			EmPAHduPlayNackReason emPaReason;
			ConvertHduInfoFromUmsToStack(tBaseInfo, tPaBaseInfo);
			ConvertHduReasonFromUmsToStack(emReason, emPaReason);

			u8 byPaBuf[sizeof(tPaBaseInfo)+sizeof(emPaReason)] = {0};
			
			memcpy(byPaBuf, &tPaBaseInfo, sizeof(tPaBaseInfo));
			memcpy(byPaBuf+sizeof(tPaBaseInfo), &emPaReason, sizeof(emPaReason));
			
			MdlHint(Ums_Mdl_Stack, (">>>> emPAUMS_CNS_HduPlay_Ind ConfID:%d EpID:%d index:%d SubIndex:%d reason:%d \n",
					wConfID, wEpID, tPaBaseInfo.m_wIndex, tPaBaseInfo.m_bySubIndex, emPaReason));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_HduPlay_Ind, byPaBuf, sizeof(byPaBuf));

		}
		break;
	case evTPUMS_CNS_HduStopPlay_Ind:
		{
			TPHduBaseInfo tBaseInfo;
			u16 wErrFlg = 0;
			TP_SAFE_CAST(tBaseInfo, pBuf);
			TP_SAFE_CAST(wErrFlg, pBuf+sizeof(tBaseInfo));
			
			TPAHduBaseInfo tPaBaseInfo;
			u16 wPaErrFlg = 0;
			
			ConvertHduInfoFromUmsToStack(tBaseInfo, tPaBaseInfo);
			wPaErrFlg  = wErrFlg;
			
			u8 byPaBuf[sizeof(tPaBaseInfo)+sizeof(wPaErrFlg)] = {0};
			memcpy(byPaBuf, &tPaBaseInfo, sizeof(tPaBaseInfo));
			memcpy(byPaBuf+sizeof(tPaBaseInfo), &wPaErrFlg, sizeof(wPaErrFlg));
			
			MdlHint(Ums_Mdl_Stack, (">>>> emPAUMS_CNS_HduStopPlay_Ind ConfID:%d EpID:%d index:%d SubIndex:%d reason:%d \n",
					wConfID, wEpID, tPaBaseInfo.m_wIndex, tPaBaseInfo.m_bySubIndex, wPaErrFlg));
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_HduStopPlay_Ind, byPaBuf, sizeof(byPaBuf));
		}
		break;
	case evTPUMS_CNS_HduSetVol_Ind:
		{
			THduSetVolInfo tVolInfo;
			EmTpHduSetVolRes emRes;
			TP_SAFE_CAST(tVolInfo, pBuf);
			TP_SAFE_CAST(emRes, pBuf+sizeof(tVolInfo));

			TPAHduSetVolInfo tPaVolInfo;
			EmPAHduSetVolRes emPaRes;
			
			tPaVolInfo.m_tInfo.m_wIndex     = tVolInfo.m_tInfo.m_wIndex;
			tPaVolInfo.m_tInfo.m_bySubIndex = tVolInfo.m_tInfo.m_bySubIndex;
			tPaVolInfo.m_byVol              = tVolInfo.m_byVol;
			tPaVolInfo.m_bMute              = tVolInfo.m_bMute;
			ConvertHduVolReasonFromUmsToStack(emRes, emPaRes);

			u8 byPaBuf[sizeof(tPaVolInfo)+sizeof(emPaRes)] = {0};
			memcpy(byPaBuf, &tPaVolInfo, sizeof(tPaVolInfo));
			memcpy(byPaBuf+sizeof(tPaVolInfo), &emPaRes, sizeof(emPaRes));

			MdlHint(Ums_Mdl_Stack, (">>>> emPAUMS_CNS_HduSetVol_Ind ConfID:%d EpID:%d VolInfo.Index:%d VolInfo.SubIndex:%d vol:%d, mute:%d VolRes:%d \n"
				, wConfID, wEpID, tPaVolInfo.m_tInfo.m_wIndex, tPaVolInfo.m_tInfo.m_bySubIndex
				, tPaVolInfo.m_byVol, tPaVolInfo.m_bMute, emPaRes));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_HduSetVol_Ind, byPaBuf, sizeof(byPaBuf));
		}
		break;
	case evTPUMS_CNS_HduChangeChanMode_Ind:
		{
			THduChanModeSetInfo tInfo;
			EmTpHduChangeChanModeRes emRes;
			TP_SAFE_CAST(tInfo, pBuf);
			TP_SAFE_CAST(emRes, pBuf+sizeof(tInfo));

			TPAHduChanModeSetInfo tPaInfo;
			EmPAHduChangeChanModeRes emPaRes;

			tPaInfo.m_wIndex = tInfo.m_wIndex;
			tPaInfo.m_byMode = tInfo.m_byMode;
			ConvertHduModeResFromUmsToStack(emRes, emPaRes);

			u8 byPaBuf[sizeof(tPaInfo)+sizeof(emPaRes)] = {0};
			memcpy(byPaBuf, &tPaInfo, sizeof(tPaInfo));
			memcpy(byPaBuf+sizeof(tPaInfo), &emPaRes, sizeof(emPaRes));

			MdlHint(Ums_Mdl_Stack, (">>>> emPAUMS_CNS_HduChangeChanMode_Ind ConfID:%d EpID:%d Index:%d mode:%d changeModeRes:%d \n"
				, wConfID, wEpID, tPaInfo.m_wIndex, tPaInfo.m_byMode, emPaRes));
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_HduChangeChanMode_Ind, byPaBuf, sizeof(byPaBuf));
		}
		break;


        /////////////////////////点名消息//////////////////////////////
    case ev_UmsConfRollCallUpdate_Ind:
		{
			TConfRollCallInfo tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallUpdate_Ind EpID:%d ConfID:%d, Ret:%d.\n",tHandle.GetEpID(), tInd.m_wConfID, tInd.m_emRet));
			
			TPAConfRollCallInfo tPa;

			tPa.m_wConfID = tInd.m_wConfID;
			tPa.m_bStart = tInd.m_bStart;
			tPa.m_dwRet = tInd.m_emRet;

            tPa.m_atRollCallMemList.m_wNum = tInd.m_atRollCallMemList.m_wNum;
            tPa.m_atRollCallMemList.m_wRollCaller = tInd.m_atRollCallMemList.m_wRollCaller;
            tPa.m_atRollCallMemList.m_wCallTarget = tInd.m_atRollCallMemList.m_wCallTarget;
			for(u16 wIndex = 0; wIndex < PA_APU2_MAX_CHAN_NUM; wIndex++)
			{
                tPa.m_atRollCallMemList.m_awList[wIndex] = tInd.m_atRollCallMemList.m_awList[wIndex];
			}
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsConfRollCallUpdate_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_UmsConfRollCallNextEp_Ind:
		{
			TRollCallNextEpInfo tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallNextEp_Ind EpID:%d ConfID:%d, Ret:%d.\n",tHandle.GetEpID(), tInd.m_wConfID, tInd.m_emRet));
			
			TPARollCallNextEpInfo tPa;

			tPa.m_wConfID = tInd.m_wConfID;
			tPa.m_wRollCaller = tInd.m_wRollCaller;
			tPa.m_wCallTarget = tInd.m_wCallTarget;
			tPa.m_dwRet = tInd.m_emRet;

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsConfRollCallNextEp_Ind, (u8*)&tPa, sizeof(tPa));
		}
		break;


	case ev_UmsConfRollCallUpdataList_Ind:
		{
			TUpdataRollCallListRes tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallUpdataList_Ind EpID:%d ConfID:%d, oprnum:%d\n",
				   tHandle.GetEpID(),
				   tInd.m_wConfID,
				   tInd.m_atRollCallMemList.m_wNum));
			
			TPAUpdataRollCallListRes tPa;
			
			tPa.m_wConfID = tInd.m_wConfID;
			tPa.m_bAdd    = tInd.m_bAdd;

			for(u16 wIndex = 0; wIndex < PA_MAX_ROLLCALL_NUM; wIndex++)
			{
				tPa.m_emRet[wIndex] = (u32)tInd.m_emRet[wIndex];
				tPa.m_atRollCallMemList.m_awList[wIndex] = tInd.m_atRollCallMemList.m_awList[wIndex];
				
			}
			tPa.m_atRollCallMemList.m_wNum = tInd.m_atRollCallMemList.m_wNum;
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsConfRollCallUpdataList_Ind, (u8*)&tPa, sizeof(tPa));

		}
		break;


	case evtp_UmsRoll_PresentState_Notify:
		{
			TRollCallPresentStateMsg tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsRoll_PresentState_Notify EpID:%d ConfID:%d, oprnum:%d\n",
				tHandle.GetEpID(),
				tInd.m_wConfID,
				tInd.m_wValidNum));
			
			TPARollCallPresentStateMsg tPa;
			
			tPa.m_wConfID      = tInd.m_wConfID;
			tPa.m_wValidNum    = tInd.m_wValidNum;
			
			for(u16 wIndex = 0; wIndex < PA_MAX_ROLLCALL_NUM; wIndex++)
			{
				tPa.m_atEpState[wIndex].m_wEpID    = tInd.m_atEpState[wIndex].m_wEpID;
				tPa.m_atEpState[wIndex].m_wEpState = (u16)tInd.m_atEpState[wIndex].m_wEpState;
				
			}
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsRoll_PresentState_Notify, (u8*)&tPa, sizeof(tPa));

		}
		break;

	case evtp_UmsRollCallScreenStat_Notify:
		{
			TRollCallCasecadeNtfy tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UmsRollCallScreenStat_Notify EpID:%d .\n",tHandle.GetEpID()));
			
			TPARollCallCasecadeNtfy tPa;

			tPa.m_dwNotyType = tInd.m_NotyType;
			tPa.m_bIsRollCallModle = tInd.m_bIsRollCallModle;
            EmTpAliasType	emType;
	        
			for(u16 wIndex = 0; wIndex < PA_NUM_OF_CALLER_AND_TARGET; wIndex++)
			{
                 tPa.m_NodeInfo[wIndex].m_wEpId = tInd.m_NodeInfo[wIndex].m_wEpId;
				 tPa.m_NodeInfo[wIndex].m_wVidSndNum = tInd.m_NodeInfo[wIndex].m_wVidSndNum;
				 tPa.m_NodeInfo[wIndex].m_wVidRcvNum = tInd.m_NodeInfo[wIndex].m_wVidRcvNum;
				 tPa.m_NodeInfo[wIndex].m_wAudSndNum = tInd.m_NodeInfo[wIndex].m_wAudSndNum;
				 tPa.m_NodeInfo[wIndex].m_wAudRcvNum = tInd.m_NodeInfo[wIndex].m_wAudRcvNum;
				 tPa.m_NodeInfo[wIndex].m_wSpeakerSeat = tInd.m_NodeInfo[wIndex].m_wSpeakerSeat;

				 memcpy(tPa.m_NodeInfo[wIndex].m_Alias.m_achAlias, tInd.m_NodeInfo[wIndex].m_Alias.m_abyAlias, sizeof(tPa.m_NodeInfo[wIndex].m_Alias.m_achAlias));
				 
				 emType = tInd.m_NodeInfo[wIndex].m_Alias.m_byType;
				 if (tp_Alias_e164 == emType)
				 {
                     tPa.m_NodeInfo[wIndex].m_Alias.m_emType = emPA_Alias_e164;
				 }else if (tp_Alias_h323 == emType)
				 {
                     tPa.m_NodeInfo[wIndex].m_Alias.m_emType = emPA_Alias_h323;
				 } else if(emPA_Alias_IP == emType)
				 {
                     tPa.m_NodeInfo[wIndex].m_Alias.m_emType = emPA_Alias_IP;
				 }else 
				 {
                     tPa.m_NodeInfo[wIndex].m_Alias.m_emType = emPA_Alias_Unknow;
				 }
				 
			}
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsRollCallScreenStat_Notify, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case ev_UmsConfRollCallUpdate_Nty:
		{
			TConfRollCallInfo tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> ev_UmsConfRollCallUpdate_Nty EpID:%d ConfID:%d, Ret:%d.\n",tHandle.GetEpID(), tInd.m_wConfID, tInd.m_emRet));
			
			TPAConfRollCallInfo tPa;
			
			tPa.m_wConfID = tInd.m_wConfID;
			tPa.m_bStart = tInd.m_bStart;
			tPa.m_dwRet = tInd.m_emRet;
			
            tPa.m_atRollCallMemList.m_wNum = tInd.m_atRollCallMemList.m_wNum;
            tPa.m_atRollCallMemList.m_wRollCaller = tInd.m_atRollCallMemList.m_wRollCaller;
            tPa.m_atRollCallMemList.m_wCallTarget = tInd.m_atRollCallMemList.m_wCallTarget;
			for(u16 wIndex = 0; wIndex < PA_MAX_ROLLCALL_NUM; wIndex++)
			{
                tPa.m_atRollCallMemList.m_awList[wIndex] = tInd.m_atRollCallMemList.m_awList[wIndex];
			}
			
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUmsConfRollCallUpdate_Nty, (u8*)&tPa, sizeof(tPa));
		}
		break;


        /////////////////////////会议混音//////////////////////////////
	case evtp_UMS_CNS_ConfAudMixMode_ind:
		{
			TUmsAudMixModeCmdRes tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_ConfAudMixMode_ind EpID:%d  Mod:%d  Ret:%d.\n",tHandle.GetEpID(), tInd.m_emCmdMode, tInd.m_emRes));
			
			TPAUmsAudMixModeCmdRes tPa;
			
			tPa.m_wConfId   =   tInd.m_wConfId;
			tPa.m_dwCmdMode = (u32)tInd.m_emCmdMode;
			tPa.m_dwRes     = (u32)tInd.m_emRes;

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_ConfAudMixMode_ind, (u8*)&tPa, sizeof(tPa));
		}
		break;

	case evtp_UMS_CNS_ConfAudMixList_ind:
		{
			TUmsAudMixListCmdRes tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_ConfAudMixList_ind EpID:%d \n", tHandle.GetEpID()));
			
			TPAUmsAudMixListCmdRes tPa;

	        tPa.m_wConfId      = tInd.m_wConfId;
			tPa.m_tList.m_wNum = tInd.m_tList.m_wNum;
            for(u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
                tPa.m_tList.m_awMixEp[wIndex] = tInd.m_tList.m_awMixEp[wIndex];
                tPa.m_aRes[wIndex] = tInd.m_aemRes[wIndex];
			}

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_ConfAudMixList_ind, (u8*)&tPa, sizeof(tPa));	
		}
		break;


	case evtp_UMS_CNS_ConfAudMixMode_Notify:
		{
			TUmsAudMixInfo tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_ConfAudMixMode_Notify EpID:%d confid:%d mode:%d oprNUM:%d\n",
				   tHandle.GetEpID(),
				   tInd.m_wConfId,
				   tInd.m_emMode,
				   tInd.m_tMixList.m_wNum));
			
			TPAUmsAudMixInfo tPa;


	        tPa.m_wConfId = tInd.m_wConfId;
			tPa.m_dwMode  = (u32)tInd.m_emMode;
			tPa.m_tMixList.m_wNum = tInd.m_tMixList.m_wNum;
            for(u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
			{
                tPa.m_tMixList.m_awMixEp[wIndex] = tInd.m_tMixList.m_awMixEp[wIndex];
			}

			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_ConfAudMixMode_Notify, (u8*)&tPa, sizeof(tPa));
		}
		break;


	case evtp_UMS_UMS_ConfAudMixMode_Notify:
		{

			TUmsAudMixCasecadeInfo tInd;
			TP_SAFE_CAST(tInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_UMS_ConfAudMixMode_Notify EpID:%d \n", tHandle.GetEpID()));
			
			TPAUmsAudMixCasecadeInfo tPa;

	        tPa.m_dwMode     = (u32)tInd.m_emMode;   
	        tPa.m_dwReserve  = tInd.m_dwReserve; 
	        tPa.m_dwReserve1 = tInd.m_dwReserve1;
		   
		    PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_UMS_ConfAudMixMode_Notify, (u8*)&tPa, sizeof(tPa));
		}
		break;	


	case evtp_UMS_CNS_EpInAudMix_Notify:
		{
			BOOL32 bInd;
			TP_SAFE_CAST(bInd, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_EpInAudMix_Notify EpID:%d  IsEpInAudMix:%d.\n",tHandle.GetEpID(), bInd));
			
			BOOL32 bPa;
			
			bPa  = bInd;

                                         
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_EpInAudMix_Notify, (u8*)&bPa, sizeof(bPa));
		}
		break;
	// 远遥
	case evtp_UMS_CNS_SendFecc_Cmd:
		{
			TCamAction tCamAct;
			TP_SAFE_CAST(tCamAct, (u8*)pBuf);
			TFeccMtInfo tMtInfo;
			TP_SAFE_CAST(tMtInfo, (u8*)pBuf + sizeof(TCamAction));

			MdlHint(Ums_Mdl_Stack, (">>>> evtp_SendFecc_Cmd SrcMcu:%d, SrcMt:%d, DstMcu:%d, DstMt:%d, FeccAct:%d, CamReq:%d\n",
					tMtInfo.m_bySrcMcuId, tMtInfo.m_bySrcMtId, tMtInfo.m_byDstMcuId, tMtInfo.m_byDstMtId,
					tCamAct.m_emFeccAct, tCamAct.GetFeccParam()));
			
			TMdlFeccStruct tFeccAction;
			ConvertFeccActFromUmsToStack(tCamAct, tFeccAction);
			TMDLTERLABEL tSrc;
			TMDLTERLABEL tDest;
			tSrc.m_byMcuNo = tMtInfo.m_bySrcMcuId;
			tSrc.m_byTerNo = tMtInfo.m_bySrcMtId;
			tDest.m_byMcuNo = tMtInfo.m_byDstMcuId;
			tDest.m_byTerNo = tMtInfo.m_byDstMtId;
			PA_SendFeccMsg(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, &tFeccAction, &tSrc, &tDest);
			
		}
		break;
	case evtp_UMS_CNS_VidFeccInfoNty:
		{
			TConfVidFeccInfo tVidInfo;
			TP_SAFE_CAST(tVidInfo, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_VidFeccInfoNty emOpr:%d, wConfID:%d, bLastPack:%d, m_wNum:%d\n", 
				tVidInfo.m_emOpr, tVidInfo.m_wConfID, tVidInfo.m_bLastPack, tVidInfo.m_wNum));
			
			TVidFeccInfo* ptFeccInfo = NULL;
			TVidSourceInfo* ptVidInfo = NULL;
			for (u16 wIndex = 0; wIndex < tVidInfo.m_wNum; ++wIndex)
			{
				ptFeccInfo = &tVidInfo.m_atVidFeccList[wIndex];
				ptVidInfo  = &tVidInfo.m_atVidFeccList[wIndex].m_tVidSourceInfo;
				MdlLowHint(Ums_Mdl_Stack, (">>>> evtp_UMS_CNS_VidFeccInfoNty wEpId:%d, bAllowFecc:%d, byVidNo:%d, byVidNum:%d\n", 
					ptFeccInfo->m_wEpID, ptFeccInfo->m_bAllowFecc, ptFeccInfo->m_byVidno, ptVidInfo->m_byNum));
				
				for (u16 wVidIndex = 0; wVidIndex < ptVidInfo->m_byNum; ++wVidIndex)
				{
					MdlLowHint(Ums_Mdl_Stack, ("evtp_UMS_CNS_VidFeccInfoNty byVidIndex:%d, byVidAlias:%s\n", 
						ptVidInfo->m_atVidInfo[wVidIndex].m_byIndex, ptVidInfo->m_atVidInfo[wVidIndex].m_abyAlias));
				}

			}
			TPAConfVidFeccInfo tPaVidInfo;
			ConvertFeccConfInfoFromUmsToStack(tVidInfo, tPaVidInfo);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAUMS_CNS_VidFeccInfoNty, (u8*)&tPaVidInfo, sizeof(tPaVidInfo));

		}
		break;
	case evtp_Conf_EpVidFeccInfo_Update:
		{
			TConfEpVidFeccList tList;
			TP_SAFE_CAST(tList, (u8*)pBuf);
			MdlHint(Ums_Mdl_Stack, (">>>> UmsSendConfCtrl::evtp_Conf_EpVidFeccInfo_Update, ConfID:%d, EpID:%d, CallID:%d\n", wConfID, wEpID, nPaID));
			TVidFeccInfo* ptFeccInfo = NULL;
			TVidSourceInfo* ptVidInfo = NULL;
			for (u16 wIndex = 0; wIndex < tList.m_wNum; ++wIndex)
			{
				ptFeccInfo = &tList.m_atList[wIndex].m_tVidFeccInfo;
				ptVidInfo  = &tList.m_atList[wIndex].m_tVidFeccInfo.m_tVidSourceInfo;
				MdlLowHint(Ums_Mdl_Stack, (">>>> UmsSendConfCtrl::evtp_Conf_EpVidFeccInfo_Update wEpId:%d, bAllowFecc:%d, byVidNo:%d, byVidNum:%d\n", 
					ptFeccInfo->m_wEpID, ptFeccInfo->m_bAllowFecc, ptFeccInfo->m_byVidno, ptVidInfo->m_byNum));
				
				for (u16 wVidIndex = 0; wVidIndex < ptVidInfo->m_byNum; ++wVidIndex)
				{
					MdlLowHint(Ums_Mdl_Stack, ("UmsSendConfCtrl::evtp_Conf_EpVidFeccInfo_Update byVidIndex:%d, byVidAlias:%s\n", 
						ptVidInfo->m_atVidInfo[wVidIndex].m_byIndex, ptVidInfo->m_atVidInfo[wVidIndex].m_abyAlias));
				}
			}

			TPAConfEpVidFeccList tPaVidList;
			ConvertFeccConfEpListFromUmsToStack(tList, tPaVidList);
			PA_SendConfCtrlTP(HMDLCALL(nPaID), (HMDLAPPCALL)nAppID, emPAConf_EpVidFeccInfo_Update, (u8*)&tPaVidList, sizeof(tPaVidList));
		}
		break;

	default:
		{
			MdlError(Ums_Mdl_Stack, ("  >> UmsSendConfCtrl failed. unkonw msg type. ConfID:%d, epID:%d, event:%d-%s\n"
				, tHandle.GetConfID(), tHandle.GetEpID(), nMsgType, GetEventNamebyID(nMsgType)));
		}
		break;
	}
	return TP_RET_OK;
}

u16 UmsSendMcuCtrl( const TUmsHandle& tHandle, const TUmsMcuChan& tMcuChan, const s32 nMsgType, const void *pBuf, const s32 nSize )
{
	s32 nAppCall = tHandle.handAppCall;
	s32 nPaCall = tHandle.handPaCall;
	
	u16 wConfID = tHandle.GetConfID();
	u16 wEpID = tHandle.GetEpID();

	s32 nMcuChan = tMcuChan.m_hMcuChan;
	s32 nMcuAppChan = tMcuChan.m_hMcuAppChan;

	tpHint(Ums_Mdl_Stack, ">> UmsSendMcuCtrl ConfID:%d, epID:%d, PACall:%d, McuChan:%d, McuAppChan:%d, nMsgType:%d-%s.\n",
					wConfID, wEpID, nPaCall, nMcuChan, nMcuAppChan, nMsgType, GetEventNamebyID(nMsgType));

	switch(nMsgType)
	{
		case evtp_UMS_MCU_RegUnRegReq:
			{
				TUmsMcuRegUnReg tReq;
				TP_SAFE_CAST(tReq, (u8*)pBuf);

				TRegUnRegReq tOut;
				tOut.m_bReg = tReq.m_bReg;
				tOut.m_nReqID = tReq.m_nReqID;
				tOut.m_bIsSupportMuitiCasade = TRUE;
				tOut.SetUserNameAndPass("admin", "admin");
				tOut.m_tMsgSrc.m_byCasLevel = 0; // 0
				tOut.m_tMsgDst.m_byCasLevel = 0; // 0
				memcpy(tOut.m_tMsgSrc.m_abyMtIdentify, "\0", sizeof(u8));
				memcpy(tOut.m_tMsgDst.m_abyMtIdentify, "\0", sizeof(u8));

				tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl emModuleRegUnReg_Req:%d, bReg:%d, nReqId:%d.\n",
					emModuleRegUnReg_Req, tOut.m_bReg, tOut.m_nReqID);

				PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleRegUnReg_Req, (u8*)&tOut, sizeof(tOut));
			}
			break;
		case evtp_UMS_MCU_RegUnRegRsp:
			{
				TUmsMcuRegUnReg tReq;
				TP_SAFE_CAST(tReq, (u8*)pBuf);
				
				TRegUnRegRsp tOut;
				tOut.m_bReg = tReq.m_bReg;
				tOut.m_nReqID = tReq.m_nReqID;
				tOut.m_emReturnVal = (emReturnValue)tReq.m_emRet;
				tOut.m_tMsgSrc.m_byCasLevel = 0; // 0
				tOut.m_tMsgDst.m_byCasLevel = 0; // 0
				memcpy(tOut.m_tMsgSrc.m_abyMtIdentify, "\0", sizeof(u8));
				memcpy(tOut.m_tMsgDst.m_abyMtIdentify, "\0", sizeof(u8));
			
				tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl emModuleRegUnReg_Rsp:%d, bReg:%d, nReqId:%d, emRet:%d.\n",
					emModuleRegUnReg_Rsp, tOut.m_bReg, tOut.m_nReqID, tOut.m_emReturnVal);
				
				PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleRegUnReg_Rsp, (u8*)&tOut, sizeof(tOut));
			}
			break;
		case evtp_UMS_MCU_PartListReq:
			{
				s32 nReqId = 0;
				TP_SAFE_CAST(nReqId, (u8*)pBuf);
				
				TReq tOut;
				tOut.m_nReqID = nReqId;
				tOut.SetUserNameAndPass("admin", "admin"); // 用户名密码必填 不然本消息会发送不出去
				tOut.m_tMsgSrc.m_byCasLevel = 0; // 0
				tOut.m_tMsgDst.m_byCasLevel = 0; // 0
				memcpy(tOut.m_tMsgSrc.m_abyMtIdentify, "\0", sizeof(u8));
				memcpy(tOut.m_tMsgDst.m_abyMtIdentify, "\0", sizeof(u8));
				
				tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl emModulePartList_Req:%d, nReqId:%d.\n",
					emModulePartList_Req, tOut.m_nReqID);
				
				PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModulePartList_Req, (u8*)&tOut, sizeof(tOut));
			}
			break;
		case evtp_UMS_MCU_CallDropPartReq:
			{
				TMcuEpCmd tMcu;
				TP_SAFE_CAST(tMcu, (u8*)pBuf);
				
				TPartReq tReq;
				tReq.SetUserNameAndPass("admin", "admin");
				tReq.m_dwPID = tMcu.m_dwPID;
				tReq.m_bLocal = FALSE; // 
				tReq.m_nReqID = 1;
				tReq.m_tMsgSrc.m_byCasLevel = 0; // 0
				tReq.m_tMsgDst.m_byCasLevel = 0; // 0
				memcpy(tReq.m_tMsgSrc.m_abyMtIdentify, "\0", sizeof(u8));
				memcpy(tReq.m_tMsgDst.m_abyMtIdentify, "\0", sizeof(u8));

				if (tMcu.m_bCall)
				{
					tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl emModuleReinvitePart_Req:%d,McuId:%d, MtId:%d, bCall:%d.\n",
					emModuleReinvitePart_Req, GETAPP(tMcu.m_dwPID), GETINS(tMcu.m_dwPID), tMcu.m_bCall);

					PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleReinvitePart_Req, (u8*)&tReq, sizeof(tReq));
				}
				else
				{
					tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl emModuleDisconnPart_Req:%d,McuId:%d, MtId:%d, bCall:%d.\n",
					emModuleDisconnPart_Req, GETAPP(tMcu.m_dwPID), GETINS(tMcu.m_dwPID), tMcu.m_bCall);

					PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleDisconnPart_Req, (u8*)&tReq, sizeof(tReq));
				}
			}
			break;
		case evtp_UMS_MCU_SetInReq:
			{
				u32 dwPID = 0;
				TP_SAFE_CAST(dwPID, (u8*)pBuf);
				
				tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl evtp_UMS_MCU_SetInReq:%d,McuId:%d, MtId:%d.\n",
					emModuleSetIn_Req, GETAPP(dwPID), GETINS(dwPID));
				
				// 请求下级会场回传码流
				TSetInReq tSetInReq;
				tSetInReq.m_nViewID = -1145368303; // mcut填充数据
				tSetInReq.m_bySubFrameIndex = 0; // mcu填充数据
				tSetInReq.m_dwPID   = dwPID;
				tSetInReq.m_bLocal  = FALSE;
				tSetInReq.m_nReqID  = 0;
				tSetInReq.SetUserNameAndPass("admin", "admin");
				tSetInReq.m_tMsgSrc.m_byCasLevel = 0; // 0
				tSetInReq.m_tMsgDst.m_byCasLevel = 0; // 0
				memcpy(tSetInReq.m_tMsgSrc.m_abyMtIdentify, "\0", sizeof(u8));
				memcpy(tSetInReq.m_tMsgDst.m_abyMtIdentify, "\0", sizeof(u8));
				
				PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleSetIn_Req, (u8*)&tSetInReq, sizeof(tSetInReq));
			}
			break;
		case evtp_UMS_MCU_SpeakerStatusNty:
			{
				TMcuSpeakerStausNty tMcu;
				TP_SAFE_CAST(tMcu, (u8*)pBuf);
				
				tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl evtp_UMS_MCU_SpeakerStatusNty:%d,McuId:%d, MtId:%d, Status:%d.\n",
					emModuleNonStandard_Ntf, GETAPP(tMcu.m_dwPID), GETINS(tMcu.m_dwPID), tMcu.m_dwStatus);
				
				TMtadpHeadMsg tHeadMsg;
				memset(&tHeadMsg, 0, sizeof(TMtadpHeadMsg));
				tHeadMsg.m_tMsgDst.m_dwPID = htonl( tMcu.m_dwPID );
				tHeadMsg.m_tMsgDst.m_bLocal = FALSE;
				u32 dwStatus = htonl( tMcu.m_dwStatus );

				CServMsg cMsg;
				cMsg.SetEventId(MCU_MCU_SPEAKSTATUS_NTF);
				cMsg.SetMsgBody();
				cMsg.CatMsgBody( (u8*)&tHeadMsg,sizeof( TMtadpHeadMsg ) );
				cMsg.CatMsgBody( (u8*)&dwStatus,sizeof( u32 ) );

				TNonStandardMsg tReq;
				tReq.m_nMsgLen = cMsg.GetServMsgLen();
				
				if((u32)tReq.m_nMsgLen > sizeof(tReq.m_abyMsgBuf))
				{
					tpError(Ums_Mdl_Stack, "    OnSendSpeakStatusNotify message is too large(len:%d)\n", tReq.m_nMsgLen );
					return TP_RET_OK;
				}
				memcpy( tReq.m_abyMsgBuf, cMsg.GetServMsg(), tReq.m_nMsgLen );
				
				PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleNonStandard_Ntf, (u8*)&tReq, sizeof(tReq));
			}
			break;
		case evtp_UMS_MCU_SpeakedChangeNty:
			{
				u32 dwPID = 0;
				TP_SAFE_CAST(dwPID, (u8*)pBuf);
				
				tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl emModuleAudioInfo_Rsp:%d,McuId:%d, MtId:%d.\n",
					emModuleAudioInfo_Rsp, GETAPP(dwPID), GETINS(dwPID));

				// 通知所有mcu 发言人变更
				TConfAudioInfo tAudioInfo;
				tAudioInfo.m_byDefaultMixerIndex = 0;
				tAudioInfo.m_byMixerCount = 1;
				tAudioInfo.m_tMixerList[0].m_nMixerID = 0;
				tAudioInfo.m_tMixerList[0].m_dwSpeakerPID = dwPID;
				tAudioInfo.m_tMixerList[0].m_bLocal = FALSE;
				tAudioInfo.m_emReturnVal = emReturnValue_Ok;
				tAudioInfo.m_nReqID  = 0;
				tAudioInfo.m_nSnapShot = 1663;
				tAudioInfo.m_tMsgSrc.m_byCasLevel = 0; // 0
				tAudioInfo.m_tMsgDst.m_byCasLevel = 0; // 0
				memcpy(tAudioInfo.m_tMsgSrc.m_abyMtIdentify, "\0", sizeof(u8));
				memcpy(tAudioInfo.m_tMsgDst.m_abyMtIdentify, "\0", sizeof(u8));
			
				PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleAudioInfo_Rsp, (u8*)&tAudioInfo, sizeof(TConfAudioInfo));
			}
			break;
		// 注意:当前消息有跨平台问题 vc6.0 error,  85 可用
		case evtp_UMS_MCU_MultSpyReq:
			{
				// to do ... 
				TMcuSpyReq tSelReq;
				TP_SAFE_CAST(tSelReq, (u8*)pBuf);
				
				tpLowHint(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl emModuleNonStandard_Ntf:%d, mcuid:%d, mtid:%d, emRes:%d.\n",
					emModuleNonStandard_Ntf, GETAPP(tSelReq.m_dwPID), GETINS(tSelReq.m_dwPID), tSelReq.m_emRes);
				
				
				u8 byRes = 0;// ...................


				u32 dwResW = 0;
				u32 dwResH = 0;
				u16 wTmpResW = 0;
				u16 wTmpResH = 0;
				
				CTpTypeAdpt::GetWHByVidResolution(tSelReq.m_emRes, wTmpResW, wTmpResH);
				// 根据分辨率,获得对应通用分辨率,新旧MCU都能识别的分辨率
				dwResW = htonl((u32)wTmpResW);
				dwResH = htonl((u32)wTmpResH);
				byRes = GetNormalRes(wTmpResW, wTmpResH);

				TPreSetInReq tPreSetInReq;
				TMcuSimCapSet tSimCapSet;

				tPreSetInReq.m_bySpyMode = MCU_MODE_BOTH;
				tPreSetInReq.m_tSpyMtInfo.m_tSpy.SetMcuId(GETAPP(tSelReq.m_dwPID));
				tPreSetInReq.m_tSpyMtInfo.m_tSpy.SetMtId((u8)GETINS(tSelReq.m_dwPID));


				tPreSetInReq.m_tReleaseMtInfo.m_TMCUMt.SetMcuId(65535);
				tPreSetInReq.m_tReleaseMtInfo.m_TMCUMt.SetMtId((u8)0);

				tSimCapSet = tPreSetInReq.m_tSpyMtInfo.GetSimCapset();
				tSimCapSet.SetVideoMediaType(66);
				tSimCapSet.SetVideoMaxBitRate(88);
				tSimCapSet.SetVideoFrameRate(199);
				tSimCapSet.SetVideoResolution(byRes);
				tSimCapSet.SetAudioMediaType(55);
				tPreSetInReq.m_tReleaseMtInfo.SetCount(tPreSetInReq.m_tReleaseMtInfo.GetCount() - 1);
				tPreSetInReq.m_tSpyMtInfo.SetSimCapset(tSimCapSet);

				TMtadpHeadMsg tMtadpHeadMsg;
				memset(&tMtadpHeadMsg, 0, sizeof(TMtadpHeadMsg));
				tMtadpHeadMsg.m_tMsgDst.m_dwPID = htonl( tSelReq.m_dwPID );
				tMtadpHeadMsg.m_tMsgDst.m_bLocal = FALSE;
				tMtadpHeadMsg.m_tMsgSrc.m_dwPID = 0;
				tMtadpHeadMsg.m_tMsgSrc.m_bLocal = FALSE;
				tMtadpHeadMsg.m_tMsgSrc.m_byCasLevel = 0;
				tMtadpHeadMsg.m_tMsgDst.m_byCasLevel = 0;
				memcpy(tMtadpHeadMsg.m_tMsgSrc.m_abyMtIdentify, "\0", sizeof(u8));
				memcpy(tMtadpHeadMsg.m_tMsgDst.m_abyMtIdentify, "\0", sizeof(u8));
				
				CServMsg cMsg;
				cMsg.SetEventId(MCU_MCU_PRESETIN_REQ);
				cMsg.SetMsgBody( );
				cMsg.CatMsgBody( (u8 *)&tMtadpHeadMsg, sizeof(tMtadpHeadMsg) );
				cMsg.CatMsgBody((u8 *)&tPreSetInReq, sizeof(tPreSetInReq));
				
				// 不在同一个mcu下	
				if( tPreSetInReq.m_tReleaseMtInfo.GetCount() >= 0)
				{
					TPartID tPartID;
					memset( &tPartID,0,sizeof(tPartID) );
					tPartID.m_dwPID = MAKEIID(65535, 0);
					tPartID.m_dwPID = htonl( tPartID.m_dwPID );
					cMsg.CatMsgBody((u8 *)&tPartID, sizeof(tPartID));
				}
				cMsg.CatMsgBody((u8 *)&dwResW, sizeof(u32));
				cMsg.CatMsgBody((u8 *)&dwResH, sizeof(u32));

				TNonStandardMsg tReq;
				tReq.m_nMsgLen = cMsg.GetServMsgLen();
				
				if((u32)tReq.m_nMsgLen > sizeof(tReq.m_abyMsgBuf))
				{
					tpError(Ums_Mdl_Stack, "    evtp_UMS_MCU_MultSpyReq message is too large(len:%d)\n", tReq.m_nMsgLen );
					return TP_RET_OK;
				}
				memcpy( tReq.m_abyMsgBuf, cMsg.GetServMsg(), tReq.m_nMsgLen );

			
				TPreSetInReq tInfo = *(TPreSetInReq *)(cMsg.GetMsgBody() + sizeof(TMtadpHeadMsg));
				TMtadpHeadMsg tHead = *(TMtadpHeadMsg*)(cMsg.GetMsgBody());

				tpLowHint(Ums_Mdl_Stack, "[ProcMcuMcuPreSetinReq] Recv PreSetin tSrc(%d.%d.%d) level.%d ReleaseMt(%d.%d.%d) level.%d byCount.%d!\n",
					tInfo.m_tSpyMtInfo.GetSpyMt().GetMcuId(),
					tInfo.m_tSpyMtInfo.GetSpyMt().GetMtId(),
					tHead.m_tMsgDst.m_abyMtIdentify[0],
					tHead.m_tMsgDst.m_byCasLevel,
					tInfo.m_tReleaseMtInfo.m_TMCUMt.GetMcuId(),
					tInfo.m_tReleaseMtInfo.m_TMCUMt.GetMtId(),
					tInfo.m_tReleaseMtInfo.m_abyMtIdentify[0],
					tInfo.m_tReleaseMtInfo.m_byCasLevel,
					tInfo.m_tReleaseMtInfo.GetCount()
					);
				tpLowHint(Ums_Mdl_Stack, "[ProcMcuMcuPreSetInReq] Rcv MMcu PreSetInReq SpyMode:%d , VidCap<Media.%d Res.%d BR.%d Fps.%d Profile:%d>, AudCap<Media.%d>, ReleaseCount.%d, ReleaseMt<McuId.%d, MtId.%d>[V.%d, A.%d], Ev.%d[%s]!\n",
					tInfo.m_bySpyMode,
					tInfo.m_tSpyMtInfo.GetSimCapset().GetVideoMediaType(),
					tInfo.m_tSpyMtInfo.GetSimCapset().GetVideoResolution(),
					tInfo.m_tSpyMtInfo.GetSimCapset().GetVideoMaxBitRate(),
					MEDIA_TYPE_H264 == tPreSetInReq.m_tSpyMtInfo.GetSimCapset().GetVideoMediaType() ?
					tInfo.m_tSpyMtInfo.GetSimCapset().GetUserDefFrameRate(): tPreSetInReq.m_tSpyMtInfo.GetSimCapset().GetVideoFrameRate(),
					tInfo.m_tSpyMtInfo.GetSimCapset().GetVideoProfileType(),
					tInfo.m_tSpyMtInfo.GetSimCapset().GetAudioMediaType(),
					tInfo.m_tReleaseMtInfo.GetCount(),
					tInfo.m_tReleaseMtInfo.m_TMCUMt.GetMcuId(),
					tInfo.m_tReleaseMtInfo.m_TMCUMt.GetMtId(),
					tInfo.m_tReleaseMtInfo.m_byCanReleaseVideoDstNum,
					tInfo.m_tReleaseMtInfo.m_byCanReleaseAudioDstNum,
					tInfo.GetEvId(),
					OspEventDesc((u16)tPreSetInReq.GetEvId())
												);
				
				PA_SendMMcuCtrl((HMDLCALL)nPaCall, (HMDLAPPCALL)nAppCall, (HMDLCHANNEL)nMcuChan, HMDLAPPCHANNEL(nMcuAppChan), 
					emModuleNonStandard_Ntf, (u8*)&tReq, sizeof(tReq));
			}
			break;

		default:
			{
				tpError(Ums_Mdl_Stack, "    >> UmsSendMcuCtrl unkown msg! ConfID:%d, epID:%d, PACall:%d, McuChan:%d, McuAppChan:%d, nMsgType:%d-%s.\n",
					wConfID, wEpID, nPaCall, nMcuChan, nMcuAppChan, nMsgType, GetEventNamebyID(nMsgType));
			}
			break;
	}

	return TP_RET_OK;
}


void UmsGkRegister(const TUmsHandle& tHandle, TRegCfg& tRegCfg, u16 wAliasNum)
{
	 TRegistReq tRegistInfo;

	 ConvertGkRegInfoFromUmsToStack(tRegistInfo, tRegCfg, wAliasNum);
     
	 tRegistInfo.m_tGKAddress.m_wPort = TP_DEFAULT_H245_PORT;
	 BOOL bRes = PA_Register(emPATypeH323, (HMDLREG*)&tHandle.handPaCall, (HMDLAPPREG)tHandle.handAppCall, &tRegistInfo);
	 MdlHint(Ums_Mdl_Stack, ("UmsGkRegister PACall:0x%x, AppCall:0x%x, RegIp:"TPIPFORMAT", RegPort:%d, wExpire:%d, HostIp:"TPIPFORMAT", HostPot:%d, bSuc:%d, alias:%d, QtID:%d\n"
	 		, tHandle.handPaCall, tHandle.handAppCall, Tpu32ToIP(tRegistInfo.m_tGKAddress.m_dwIp), tRegistInfo.m_tGKAddress.m_wPort
	 		, tRegistInfo.m_nTimeToLive
	 		, Tpu32ToIP(tRegistInfo.m_tLocalAddress.m_dwIp), tRegistInfo.m_tLocalAddress.m_wPort, bRes, wAliasNum, tRegistInfo.m_dwQtID));

	 TUmsHandle tOutHandle = tHandle;
	 if (bRes)
	 {
		 EmTpRegType emRegType = em_323_reg;
		 NotifyMsgToCall(ev_register_handle_info, tOutHandle, (void*)&emRegType, sizeof(EmTpRegType));
	 }
	 else
	 {
		 TUCSipRegResult tSipRegResult;
		 memset(&tSipRegResult,0,sizeof(TUCSipRegResult));
		 tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_Unknow;
		 NotifyMsgToCall(evtp_ums_323_unreg_ret, tOutHandle, (void*)&tSipRegResult, sizeof(TUCSipRegResult));
	 }
}



void UmsRegister(const TUmsHandle& tHandle, TUmsSipRegCfg& tRegCfg, TTPAlias atAlias[], u16 wAliasNum)
{	
	g_tUMSStackCfg.m_dwRegIP = tRegCfg.dwRegIP;
	g_tUMSStackCfg.m_wRegPort = tRegCfg.wRegPort;

	TPARegCfg tPaRegCfg;
	ConvertSipRegInfoFromUmsToStack(tPaRegCfg, tRegCfg, atAlias, wAliasNum);


	BOOL bRes = PA_RegisterTP((HMDLREG*)&(tHandle.handPaCall), (HMDLAPPREG)tHandle.handAppCall, &tPaRegCfg);
	MdlHint(Ums_Mdl_Stack, ("UmsRegister PACall:0x%x, AppCall:0x%x, RegIp:"TPIPFORMAT", RegPort:%d, wExpire:%d, HostIp:"TPIPFORMAT", HostPot:%d, bSuc:%d, dwQtID->%d\n"
		, tHandle.handPaCall, tHandle.handAppCall, Tpu32ToIP(tPaRegCfg.m_dwRegIP), tPaRegCfg.m_wRegPort
		, tPaRegCfg.m_wExpire
		, Tpu32ToIP(tPaRegCfg.m_dwHostIP), tPaRegCfg.m_wHostPort, bRes, tPaRegCfg.m_dwQtID));

	TUmsHandle tOutHandle = tHandle;
	if (bRes)
	{
		EmTpRegType emRegType = em_sip_reg;
		NotifyMsgToCall(ev_register_handle_info, tOutHandle, (void*)&emRegType, sizeof(EmTpRegType));
	}
	else
	{
		TUCSipRegResult tSipRegResult;
		memset(&tSipRegResult,0,sizeof(TUCSipRegResult));
		tSipRegResult.m_emTpCnsRegUms = tp_CnsRegRet_Unknow;
		NotifyMsgToCall(evtp_ums_unreg_ret, tOutHandle, (void*)&tSipRegResult, sizeof(TUCSipRegResult));
	}
}

void UmsUnregister(const TUmsHandle& tHandle, const EmTpRegType& emTpProtocol)
{
	EmPAConfProtocol emPaProtocl = emPATypeSip;
	ConvertRegProtocolFromUmsToStack(emTpProtocol, emPaProtocl);
	BOOL bRes = PA_UnRegister(emPaProtocl, (HMDLREG)tHandle.handPaCall, (HMDLAPPREG)tHandle.handAppCall);
	MdlHint(Ums_Mdl_Stack, ("UmsUnregister PACall:0x%x Protocol:%d, bSus:%d\n", tHandle.handPaCall, emPaProtocl, bRes));
}


void QueryAlias(u16 wIndex, s8 szAlias[TP_MAX_ALIAS_LEN])
{// szAlias = TP_MAX_ALIAS_LEN(LocalAlias) + EmQtAliasType + EmQtKeyFrequency + TP_MAX_ALIAS_LEN(PeerAlias) + BOOL32(IsMediaKey).
    TTPQTQueryData tDataInfo;

	tDataInfo.m_wIndex = wIndex;

	memcpy(tDataInfo.m_szAlias, szAlias, TP_MAX_ALIAS_LEN);
	tDataInfo.m_szAlias[TP_MAX_ALIAS_LEN] = '\0';

	EmQtAliasType emAliasType;
	memcpy(&emAliasType, szAlias + TP_MAX_ALIAS_LEN, sizeof(EmQtAliasType));
    tDataInfo.m_tQueryType = (u16)emAliasType;

	EmQtKeyFrequency emFrq;
	memcpy(&emFrq, szAlias + TP_MAX_ALIAS_LEN + sizeof(EmQtAliasType), sizeof(EmQtKeyFrequency));
	switch(emFrq)
	{
	case EmQtFrequencyEverySeconds:
		tDataInfo.m_emQueryFreq = emTPEncryptTypeQtEverySecond;
		break;
	case EmQtFrequencyEveryMinutes:
		tDataInfo.m_emQueryFreq = emTPEncryptTypeQtEveryMinute;
		break;
	case EmQtFrequencyEveryConf:
        tDataInfo.m_emQueryFreq = emTPEncryptTypeQtEveryConf;
		break;
    default:
        tDataInfo.m_emQueryFreq = emTPEncryptTypeNone;
		break;
	}

	memcpy(tDataInfo.m_speerAlias,  szAlias + TP_MAX_ALIAS_LEN + sizeof(EmQtAliasType) + sizeof(EmQtKeyFrequency) , TP_MAX_ALIAS_LEN);
	tDataInfo.m_speerAlias[TP_MAX_ALIAS_LEN] = '\0';

	memcpy(&tDataInfo.m_IsMedia,    szAlias + TP_MAX_ALIAS_LEN + sizeof(EmQtAliasType) + sizeof(EmQtKeyFrequency) + TP_MAX_ALIAS_LEN, sizeof(BOOL32));

	MdlHint( Ums_Mdl_Stack, ("[QueryAlias] wIndex->%d, szAlias->%s, freq->%d, Querytype->%d, pAlias->%s, isMedia->%d\n",
		wIndex, 
		tDataInfo.m_szAlias, 
        tDataInfo.m_emQueryFreq,
		tDataInfo.m_tQueryType,
		tDataInfo.m_speerAlias, 
		tDataInfo.m_IsMedia));

	TUmsHandle tHandle;
	tHandle.handAppCall = wIndex;
	tHandle.handAppCall = tHandle.handAppCall << 16;
	
	NotifyMsgToCall(evtp_QtQueryAlias_req, tHandle, &tDataInfo, sizeof(tDataInfo));
}


//Protocol_file
//码流回调秘钥
void CBMediaKey(u32 dwConfID, QTMediaKeyHandle hMediaHandle, s8 szAlias[QT_ALIAS_MAX_LEN+1], u8 acMediaKey[QT_MAX_MEDIA_KEY + 1], u32 dwKeyLen, EmQtKeyFrequency emKeyFrequency, u32 wQtFlag, u16 wIndex)
{
	MdlHint(Ums_Mdl_Stack, ("[CBMediaKey]dwConfID->%d, hMediaHandle->%d, szAlias->%s, emKeyFrequency->%d, qtFlag:%d, wIndex:%d\n",
		dwConfID, hMediaHandle, szAlias, emKeyFrequency, wQtFlag, wIndex));
	TUmsHandle tHandle;
	tHandle.handAppCall = dwConfID;
	tHandle.handAppCall = tHandle.handAppCall << 16;
	tHandle.handAppCall |= 1025;
	
	TTPMediaKeyInfo tInfo;
	tInfo.m_dwHandle = hMediaHandle;
	memcpy(tInfo.m_szAlias, szAlias, QT_ALIAS_MAX_LEN);
	tInfo.m_szAlias[QT_ALIAS_MAX_LEN] = '\0';
	tInfo.m_wIndex = wIndex;
	memcpy(tInfo.m_szMediaKey1, acMediaKey, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tInfo.m_szMediaKey2, acMediaKey + TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tInfo.m_szMediaKey3, acMediaKey + TP_MAX_MEDIAKEY_LEN/2, TP_MAX_MEDIAKEY_LEN/4);
	memcpy(tInfo.m_szMediaKey4, acMediaKey + 3*TP_MAX_MEDIAKEY_LEN/4, TP_MAX_MEDIAKEY_LEN/4);
	
	tInfo.m_dwKeyLen = dwKeyLen;
    //Protocol_file
	ConvertQTEncryptLevelFromStackToUms(emKeyFrequency, tInfo.m_emKeyFrequency);

	tInfo.m_dwQtFlag = wQtFlag;
	
	NotifyMsgToCall(evtp_MediaKey_Nty, tHandle, &tInfo, sizeof(tInfo));
}


//Protocol_file
void QtCBMediaKeyFailUms(u32 dwPeerMtIp, s8 szLocalAlias[QT_ALIAS_MAX_LEN+1], s8 szPeerAlias[QT_ALIAS_MAX_LEN+1])
{
	MdlError( Ums_Mdl_Stack, ("[QtCBMediaKeyFailUms] dwPeerMtIp->"TPIPFORMAT", szLocal->%s, szAlias->%s\n",
		Tpu32ToIP(dwPeerMtIp), szLocalAlias, szPeerAlias) );
	
	TUmsHandle tHandle;
	tHandle.handAppCall = 1;
	tHandle.handAppCall = tHandle.handAppCall << 16;
	tHandle.handAppCall |= 1025;
	
	TTPQtMediaKeyFail tFail;
	tFail.m_dwPeerIP = dwPeerMtIp;
	memcpy(tFail.m_szLocalAlias, szLocalAlias, TP_MAX_ALIAS_LEN);
	memcpy(tFail.m_szPeerAlias, szPeerAlias, TP_MAX_ALIAS_LEN);
	
	NotifyMsgToCall(evtp_QtMediaFail_Cmd, tHandle, &tFail, sizeof(tFail));
}


void QtMTState( EmQtMTState emQtMtState, void* wParam)
{
	MdlHint( Ums_Mdl_Stack, ("[QtMTState] emQtMtState:%d.\n", emQtMtState));	
}


void QtMediaHandle(u32 dwPeerMtIp, u32 dwPeerQtID, s8 szAlias[QT_ALIAS_MAX_LEN+1], EmQtAliasType emAliasType, QTMediaKeyHandle hMediaHandle)
{
    MdlHint( Ums_Mdl_Stack, ("[QtMediaHandle] dwPeerMtIp->"TPIPFORMAT", hMediaHandle->%d, dwPeerQtID->%d, szAlias->%s\n", 
    Tpu32ToIP(dwPeerMtIp), hMediaHandle, dwPeerQtID, szAlias) );
}

void QtRetReason(EmQtRetReason emQtRetReason, void* wParam)
{	
	MdlHint( Ums_Mdl_Stack, ("[QtRetReason] emQtRetReason:%d.\n", emQtRetReason));
}

void CreatQtInitParam(BOOL32 bQTOn, u32 dwQtMtIp, u32 dwQtMtId, TQtInitParam& tQtInitParam)
{
	if (bQTOn)
	{
		tQtInitParam.m_dwQtListenIp = dwQtMtIp;
		tQtInitParam.m_dwQtMtId = dwQtMtId;

	} 
	else
	{
		tQtInitParam.m_dwQtListenIp = 0;
		tQtInitParam.m_dwQtMtId = 0;
	}

	tQtInitParam.m_bPlatform = TRUE;
	tQtInitParam.m_pfCBCallHandle = NULL;
	tQtInitParam.m_pfCbBfcpHandle = NULL;
	tQtInitParam.m_pfCBMediaHandle = QtMediaHandle;
	tQtInitParam.m_pfCBMediaKey = CBMediaKey;
	tQtInitParam.m_pcCBQueryAlias = QueryAlias;
	tQtInitParam.m_pfCBState = QtMTState;
	tQtInitParam.m_pfCBRetReason = QtRetReason;

	return;
}

//init

void InitUmsStack(TUmsStackCallCfg& tCfg, TTPQTEncryptInfo &tTPQTEncryptInfo)
{
	TPAConfig tPaCfg;
	tPaCfg.m_tSipConfig.m_emEndpointType = emModuleEndpointUMS;
	tPaCfg.m_tSipConfig.m_wCallingPort = tCfg.m_wCallingPort;
	tPaCfg.m_tSipConfig.m_wSipTotalCallNum = tCfg.m_wMaxCallNum;
	tPaCfg.m_tSipConfig.m_wRegClientNum = 20; // 目前ums最多分4包注册，再加上最多16个临时会议
	tPaCfg.m_tSipConfig.m_wIfProxy = 0;   
	tPaCfg.m_tSipConfig.m_dwKeepAliveTime = tCfg.m_dwKeepAliveTime;
//	tPaCfg.m_tSipConfig.m_bFirstInviteWithDualMedia = TRUE;
	tPaCfg.m_tSipConfig.m_bSendRecv = TRUE;
	tPaCfg.m_tSipConfig.m_bSendRecvWithComCap = TRUE;
	tPaCfg.m_tSipConfig.m_bAutoAnswerFCS = FALSE;
	tPaCfg.m_tSipConfig.m_dwPaLocalIP = g_dwListenIp;

	s8 *pzAliasUTF8 = NULL;
	gb2312_to_utf8((s8 *)tCfg.m_abyProductId, &pzAliasUTF8);
	tPaCfg.m_tSipConfig.m_nProductIdSize = strlen(pzAliasUTF8);
	strncpy((s8 *)tPaCfg.m_tSipConfig.m_abyProductId, pzAliasUTF8, tPaCfg.m_tSipConfig.m_nProductIdSize);
	free(pzAliasUTF8);
	pzAliasUTF8 = NULL;

	gb2312_to_utf8((s8 *)tCfg.m_abyVersionId, &pzAliasUTF8);
	tPaCfg.m_tSipConfig.m_nVerIdSize = strlen(pzAliasUTF8);
	strncpy((s8 *)tPaCfg.m_tSipConfig.m_abyVersionId, pzAliasUTF8, tPaCfg.m_tSipConfig.m_nVerIdSize);
	free(pzAliasUTF8);
	pzAliasUTF8 = NULL;

	tPaCfg.m_tH323Config.m_dwh323StackIp = g_dwListenIp;
	tPaCfg.m_tH323Config.m_emEndpointType = emModuleEndpointUMS;
	//323呼叫数量 按照协议默认值 128
	//tPaCfg.m_tH323Config.m_wH323TotalCallNum = 64;//暂时先改成64

	CreatQtInitParam(tTPQTEncryptInfo.m_bIsEncQT, tTPQTEncryptInfo.m_dwQuanTumIP, tTPQTEncryptInfo.m_dwQuanTumID, tPaCfg.m_tQuantumInitParam);

	BOOL bRes = PA_Init(tPaCfg, FALSE);

	MdlHint(Ums_Mdl_Stack, ("<< UmsInitStackRes bSuc:%d, QtIP:"TPIPFORMAT"(port:%d), QtID:%d, IsQtEnc:%d, QtLevel:%d, ListenIP:"TPIPFORMAT"\n",
		bRes,
		Tpu32ToIP(tPaCfg.m_tQuantumInitParam.m_dwQtListenIp),
		tPaCfg.m_tQuantumInitParam.m_wQtListenPort,
		tPaCfg.m_tQuantumInitParam.m_dwQtMtId,
		tPaCfg.m_tQuantumInitParam.m_bEncryption,
		tPaCfg.m_tQuantumInitParam.m_emKeyFrequency, 
		Tpu32ToIP(g_dwListenIp)));
	

	CTpMsg cMsg;	
	cMsg.SetEvent(ev_SipAdapterInit_Ind);
	cMsg.SetBody(&bRes, sizeof(bRes));
	cMsg.Post(UMS_SIPADAPTER_APP_INST);

	TPACallBackFunc tCbFun;
	tCbFun.m_tPARegistCBFunction.m_cbRegistResult = UmsCBRegistResult;
	//tCbFun.m_tPARegistCBFunction.m_cbUnRegistResult = UmsCBUnRegResult;
	tCbFun.m_tPARegistCBFunction.m_cbGetRegInfoAckTP = UmsCBGetRegInfoAckTP;
	tCbFun.m_tPACallCBFunction.m_fpCallConnected = UmsCBCallConnected;
	tCbFun.m_tPACallCBFunction.m_fpCallDisconnected = UmsCBCallDisconnected;
	tCbFun.m_tPACallCBFunction.m_fpNewCallIncoming = UmsCBNewCallIncoming;
	tCbFun.m_tPAChannelCBFunction.m_fpChannelConnected = UmsCBChannelConnected;
	tCbFun.m_tPAChannelCBFunction.m_fpChannelDisconnected = UmsCBChannelDisconnected;
	tCbFun.m_tPAChannelCBFunction.m_fpChannelFastUpdate = UmsCBChannelFastUpdate;
	tCbFun.m_tPAChannelCBFunction.m_fpChannelFlowCtrl = UmsCBChannelFlowCtrl;
	tCbFun.m_tPAChannelCBFunction.m_fpDualStreamIncoming = UmsCBDualStreamIncoming;
	tCbFun.m_tPAChannelCBFunction.m_fpDualStreamIncomingBfcp = UmsCBDualStreamIncomingBfcp;

	tCbFun.m_tPAChannelCBFunction.m_fpConfCtrlTP = UmsCBConfCtrlTP;  // call 回调
	tCbFun.m_tPAChannelCBFunction.m_fpConfCtrl = UmsCBConfCtrl;
	
	tCbFun.m_tPAChannelCBFunction.m_fpChanCtrlTP = UmsCBChanCtrlTP;
	
 	tCbFun.m_tPAChannelCBFunction.m_fpMMcuChanConnected = UmsCBMMcuChanConnected;
 	tCbFun.m_tPAChannelCBFunction.m_fpMMcuMsg = UmsCBMMcuMsg;

	tCbFun.m_tPAChannelCBFunction.m_fpFeccChanConnected	= UmsCBFeccChanConnected;	
	tCbFun.m_tPAChannelCBFunction.m_fpFeccMsg	= UmsCBFeccMsg;	

	bRes = PA_SetCallBackFunc(tCbFun);
	MdlHint(Ums_Mdl_Stack, ("<< UmsSetCallBackFunc bSuc:%d\n", bRes));

    SetMediaKeyFailCB(QtCBMediaKeyFailUms);
	if (NULL == g_hSemCallMap)
	{
		if (!OspSemBCreate(&g_hSemCallMap))
		{
			MdlHint(Ums_Mdl_Stack, ("<< OspSemBCreate g_hSemCallMap error!\n"));
		}
	}
}

void QuitUmsStack()
{
	PA_Quit();
}

void ProcMcuNonStandardMsg( CServMsg& cServMsg, TUmsHandle& tHandle )
{
	u16 wEvent = cServMsg.GetEventId();
	u8* pbyBuf = cServMsg.GetMsgBody();

	tpHint(Ums_Mdl_Stack, "<< ProcMcuNonStandardMsg ConfID:%d, epID:%d, PACall:%d, CBEvent:%d.\n",
		tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, wEvent);
	
	switch( wEvent )
	{
		// 回传能力通知
	case MCU_MCU_MULTSPYCAP_NOTIF:
		{
			u32 dwSpyBW = 0;
			TP_SAFE_CAST(dwSpyBW, (u8*)pbyBuf);
			dwSpyBW = ntohl(dwSpyBW);
			tpLowHint(Ums_Mdl_Stack, "ProcMcuNonStandardMsg MCU_MCU_MULTSPYCAP_NOTIF dwSpyBW:%d.\n", 
				dwSpyBW);
			NotifyMsgToCall(evtp_MCU_UMS_SpyBWNty, tHandle, &dwSpyBW, sizeof(s32));
		}
		break;

	case MCU_MCU_PRESETIN_ACK:
		{// to do ...
			TPreSetInRsp tPreSetInRsp = *(TPreSetInRsp *)(cServMsg.GetMsgBody());
			tpLowHint(Ums_Mdl_Stack, "ProcMcuNonStandardMsg MCU_MCU_PRESETIN_ACK...\n");	
		}
		break;
	case MCU_MCU_PRESETIN_NACK:
		{// to do ...
			TPreSetInRsp tPreSetInRsp = *(TPreSetInRsp *)(cServMsg.GetMsgBody());
			u16 wError = cServMsg.GetErrorCode();
			tpLowHint(Ums_Mdl_Stack, "ProcMcuNonStandardMsg MCU_MCU_PRESETIN_NACK wError:%d!\n", wError);	
		}
		break;
	case MCU_MCU_SPYCHNNL_NOTIF:
		{
			tpLowHint(Ums_Mdl_Stack, "ProcMcuNonStandardMsg MCU_MCU_SPYCHNNL_NOTIF.\n");
		}
		break;
		
	case MCU_MCU_MTSTATUS_NOTIF:
		{
			tpLowHint(Ums_Mdl_Stack, "ProcMcuNonStandardMsg MCU_MCU_MTSTATUS_NOTIF.\n");
		}
		break;
	default:
		{
			tpError(Ums_Mdl_Stack, "    << ProcMcuNonStandardMsg unkown msg! ConfID:%d, epID:%d, PACall:%d, CBEvent:%d.\n",
				tHandle.GetConfID(), tHandle.GetEpID(), tHandle.handPaCall, wEvent);	
		}
		break;
			}
}

