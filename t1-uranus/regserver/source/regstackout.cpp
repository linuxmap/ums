#include "regstackout.h"
#include "eventoutsipadapter.h"
#include "innereventregsrv.h"
#include "eventtpsys.h"
#include "stackmsgconvert.h"
#include "tpxmltype.h"
#include "umsobject.h"
#include "regstruct.h"

using namespace UmsTpmsg;

extern SEMHANDLE g_SipSem;
void PrintReqInfo(TUmsHandle& tHandle, u16 wMsgType, const void* pBuf, u16 wBufLen);


CTpRegStackOutApp g_cTPRegStackOutApp;
API BOOL StartupRegStackOutApp()
{
	g_cTPRegStackOutApp.CreateApp("REGSIPOUT",AID_REGSIPSTACKOUT_APP,100);

	CTpMsg cMsg;
	cMsg.SetEvent( ev_kdvmsg_sys_init );
	cMsg.Post( MAKEIID(AID_REGSIPSTACKOUT_APP,1) );
	return TRUE;
}



void CTpRegStackOut::MessageProc( CTpMsg *const ptMsg)
{
	RvStatus tRet = RV_FALSE;
	u16 wEvent = ptMsg->GetEvent();
	TUmsHandle* ptHandle = (TUmsHandle*)ptMsg->GetBody();
	u8* pData = ptMsg->GetBody() + sizeof(TUmsHandle);
	
	PrintReqInfo(*ptHandle, wEvent, pData, ptMsg->GetBodyLen() - sizeof(TUmsHandle));

	EmRegisterReason emStackReason = emRegNone;
	RegisterRequest tStackRegInfo;
	if (wEvent != evtp_ums_reg_info_rsp && wEvent != evtp_ums_reg_info_rspEx)
	{
		TCnsRegRetResult* ptRegRet = (TCnsRegRetResult*)pData;
		ConvertRegReasonFromAppToStack(*ptRegRet, emStackReason);
		ConvertRegFromAppToStack(*(TCnsRegInfo*)(pData+sizeof(TCnsRegRetResult)), tStackRegInfo);
	}

	
	if(!OspSemTake( g_SipSem ))
	{
		ObjError(("CTpRegStackOut OspSemTake ERROR!\n"));
		return;
	}

	switch (wEvent)
	{
	case evtp_ums_reg_ret:
		{
			if ( emStackReason == emRegNameDup )
			{
				u8 abyBufReson[sizeof(EmRegisterReason)+sizeof(s32)+sizeof(TSipRegName)*MAX_NUM_REGNAME_SIZE] = {0};
				
				EmRegisterReason* pReason = (EmRegisterReason*)abyBufReson;
				s32*			  pnAliasNum = (s32*)( abyBufReson + sizeof(EmRegisterReason));
				TSipRegName*	  ptSipRegName = (TSipRegName*)(abyBufReson+sizeof(s32)+sizeof(EmRegisterReason));

				*pReason = emStackReason;
				*pnAliasNum = tStackRegInfo.m_nSipRegArraySize;
				memcpy( ptSipRegName, tStackRegInfo.m_atSipRegName, sizeof(TSipRegName) * (*pnAliasNum));

				tRet = CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(ptHandle->handPaCall), h_ums_registrationind, abyBufReson, sizeof(abyBufReson));

			}
			else
			{
				u8 abyBufReson[sizeof(EmRegisterReason)+sizeof(RegisterResponse)];
				
				EmRegisterReason* pReason = (EmRegisterReason*)abyBufReson;
				RegisterResponse* pReasonInfo = (RegisterResponse*)(abyBufReson+sizeof(EmRegisterReason));
				
				*pReason = emStackReason;
				pReasonInfo->m_tContactAddr = tStackRegInfo.m_atContactAddr[0];

				tRet = CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(ptHandle->handPaCall), h_ums_registrationind, abyBufReson, sizeof(abyBufReson));
			}
		}
		break;
	case evtp_ums_unreg_ret:
		{	
			tRet = CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(ptHandle->handPaCall), h_ums_unregistrationind, (u8*)&emStackReason, sizeof(EmRegisterReason));
		}
		break;
	case evtp_ums_arq_ret:
		{	
			u8 abyBufReson[sizeof(EmRegisterReason)+sizeof(RegisterResponse)];
			
			EmRegisterReason* pReason = (EmRegisterReason*)abyBufReson;
			RegisterResponse* pReasonRes = (RegisterResponse*)(abyBufReson+sizeof(EmRegisterReason));

			RegisterResponse tRes;
			
			*pReason = emStackReason;
			tRes.m_tContactAddr.m_dwIP =  tStackRegInfo.m_atContactAddr[0].m_dwIP;
			tRes.m_tContactAddr.m_wPort = tStackRegInfo.m_atContactAddr[0].m_wPort;
			tRes.m_emSipConnection = tStackRegInfo.m_emSipConnection;

			tRes.m_dwQtID = tStackRegInfo.m_dwQtID;

			memcpy(pReasonRes, &tRes, sizeof(RegisterResponse));

			tRet = CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(ptHandle->handPaCall), h_ums_answer, abyBufReson, sizeof(abyBufReson));
		}
		break;

	case evtp_ums_reg_info_rsp:
		{
			u8 abyBuf[sizeof(s32)+sizeof(TSipRegPackXml)]={0};
			s32* psAppId = (s32*)((u8*)abyBuf);
			TSipRegPackXml* ptSipXml = (TSipRegPackXml*)(((u8*)abyBuf)+sizeof(s32));
			
			s32* psDestAppId = (s32*)pData;
			TReqRegInfo* ptRegInfo = (TReqRegInfo*)(pData + sizeof(s32));
			
			*psAppId = *psDestAppId;
			ConvertRegInfoTypeToAppStack(ptRegInfo->m_tRegType, ptSipXml->emType);
			ptSipXml->tPackInfo.m_wTotalPackNum = ptRegInfo->m_wTotalPackNum;
			ptSipXml->tPackInfo.m_wPackSeq = ptRegInfo->m_wPackSeq;
			ConvertPtTypeTpAppStack(ptRegInfo->m_emSelfType, ptSipXml->tRegInfo.m_emSelfType);
			ptSipXml->tRegInfo.m_wAliasNum = ptRegInfo->m_wAliasNum;
			for (u16 wIndex = 0; wIndex != ptRegInfo->m_wAliasNum; ++wIndex)
			{
				memcpy(ptSipXml->tRegInfo.m_atAlias[wIndex].m_achAlias, ptRegInfo->m_atAlias[wIndex].m_abyAlias, LEN_USERNAME);
				ConvertTpAliasTypeToAppStack(ptRegInfo->m_atAlias[wIndex].m_byType, ptSipXml->tRegInfo.m_atAlias[wIndex].m_emType); 
			}
			
			ObjHint(("evtp_ums_reg_info_rsp\n"));
			tRet = CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(ptHandle->handPaCall), h_ums_getregack, 
												 abyBuf, sizeof(abyBuf));
		}
		break;

	case evtp_ums_reg_info_rspEx:	
		{
			s32 nAppID;
			TReqRegInfoEx tRegInfoEx;
			TP_SAFE_CAST(nAppID, pData);
			TP_SAFE_CAST(tRegInfoEx, pData+sizeof(s32));

			switch (tRegInfoEx.m_emSelfType)
			{
			case emTPEndpointTypeUMS:		tRet = PostUmsRegInfo(*ptHandle, nAppID, tRegInfoEx, pData+sizeof(s32)+sizeof(TReqRegInfoEx));
											break;

			case emTPEndpointTypeCNS:		tRet = PostCnsRegInfo(*ptHandle, nAppID, tRegInfoEx, pData+sizeof(s32)+sizeof(TReqRegInfoEx));
											break;
				
			default:						msgprintnotime("evtp_ums_reg_info_rspEx UnKnow type:%d.\n", tRegInfoEx.m_emSelfType);
											break;
			}
		}	
		break;
	default:
		break;
	}

	if(!OspSemGive( g_SipSem ))
	{
		ObjError(("CTpRegStackOut OspSemGive ERROR!\n"));
		return;
	}

	if (RV_TRUE != tRet)
	{
		ObjError(("SendUMSCtrlMsg failed. event:%d-%s, handle:0x%x\n"
			, wEvent, GetEventNamebyID(wEvent), ptHandle->handPaCall));
	}
}


BOOL32 CTpRegStackOut::ObjectInit(u32 wParam, u32 lParam)
{
	SetLogTitle("CTpRegStackOut");
	return TRUE;
}

RvStatus CTpRegStackOut::PostUmsRegInfo(const TUmsHandle& tHandle, s32 nAppID, const TReqRegInfoEx& tRegInfo, u8* pData)
{
	CTpMsg cMsg;
	cMsg.SetBody(&nAppID, sizeof(s32));
	
	TSipRegPackXmlB2 tSipReg;
	ConvertRegInfoFromAppToStack(tRegInfo, tSipReg);
	cMsg.CatBody(&tSipReg, sizeof(TSipRegPackXmlB2));
	
	for (u16 wIndex = 0; wIndex < tRegInfo.m_wDataNum; ++wIndex)
	{
		TUmsRegData tRegData;
		memcpy(&tRegData, pData+wIndex*sizeof(TUmsRegData), sizeof(TUmsRegData));
		
		TSipRegInfoUms tUmsInfo;
		ConvertUmsRegInfoFromAppToStack(tRegData, tUmsInfo);
		cMsg.CatBody(&tUmsInfo, sizeof(TSipRegInfoUms));
	}
	
	return CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(tHandle.handPaCall), h_ums_getregack_B2, cMsg.GetBody(), cMsg.GetBodyLen());
}

RvStatus CTpRegStackOut::PostCnsRegInfo(const TUmsHandle& tHandle, s32 nAppID, const TReqRegInfoEx& tRegInfo, u8* pData)
{
	CTpMsg cMsg;
	cMsg.SetBody(&nAppID, sizeof(s32));

	TSipRegPackXmlB2 tSipReg;
	ConvertRegInfoFromAppToStack(tRegInfo, tSipReg);
	cMsg.CatBody(&tSipReg, sizeof(TSipRegPackXmlB2));

	for (u16 wIndex = 0; wIndex < tRegInfo.m_wDataNum; ++wIndex)
	{
		TCnsRegData tRegData;
		memcpy(&tRegData, pData+wIndex*sizeof(TCnsRegData), sizeof(TCnsRegData));

		TSipRegInfoCns tCnsInfo;
		ConvertCnsRegInfoFromAppToStack(tRegData, tCnsInfo);
		cMsg.CatBody(&tCnsInfo, sizeof(TSipRegInfoCns));
	}

	return CSipInterface::SendUMSCtrlMsg(RvSipTranscHandle(tHandle.handPaCall), h_ums_getregack_B2, cMsg.GetBody(), cMsg.GetBodyLen());
}


void PrintReqInfo(TUmsHandle& tHandle, u16 wMsgType, const void* pBuf, u16 wBufLen)
{
	if(IsCanPrint(Ums_Mdl_RegServer, enLogHint))
	{
		s8 achPrintAlias[MAX_MSG_LEN_TMP + 1];
		switch(wMsgType)
		{
		case h_ums_registrationcmd:
			{
				RegisterRequest* pRegInfo = (RegisterRequest*)pBuf;
				msgprint("<< Reg Req stackID:%d, CallID:", tHandle.handPaCall);
				printcallid((u8*)pRegInfo->m_achCallId, MAX_NUM_CALLID);

				u16 i;
				u16 wPrintNum = 0;
				msgprintnotime("<< Reg alias num:%d\n", pRegInfo->m_nSipRegArraySize);
				for (i=1; i<pRegInfo->m_nSipRegArraySize; i+=2)
				{
					wPrintNum += 2;
					snprintf(achPrintAlias, MAX_MSG_LEN_TMP, "type:alias %d:%s  %d:%s"
						, pRegInfo->m_atSipRegName[i-1].m_emSipAddrType, pRegInfo->m_atSipRegName[i-1].m_achUserName
						, pRegInfo->m_atSipRegName[i].m_emSipAddrType, pRegInfo->m_atSipRegName[i].m_achUserName);

					msgprintnotime("<<   %s\n", achPrintAlias);
				}
				if (wPrintNum < pRegInfo->m_nSipRegArraySize)
				{
					i = pRegInfo->m_nSipRegArraySize - 1;
					msgprintnotime("<<   type:alias %d:%s\n", pRegInfo->m_atSipRegName[i].m_emSipAddrType, pRegInfo->m_atSipRegName[i].m_achUserName);
				}
				

				msgprintnotime("<< TimeOut:%d, SN:%d, CallType:%d\n", pRegInfo->m_dwExpires, pRegInfo->m_nCSqence, pRegInfo->m_emSipConnection);
				for (i=0; i<MAX_NUM_CONTACT_ADDR; ++i)
				{
					if (pRegInfo->m_atContactAddr[i].m_dwIP == 0)
					{
						break;
					}
					msgprintnotime("<<   addr %d:"ADDRPORT_FORMAT"\n", i+1, ADDRPORT(pRegInfo->m_atContactAddr[i].m_dwIP,pRegInfo->m_atContactAddr[i].m_wPort));
				}

				msgprintnotime("<<   LocalInfo EpType:%d, LocalIP:"TPIPFORMAT", EPVersion:%s, CompileTime:%s\n", 
										pRegInfo->m_tLocalInfo.m_emEndpointType, 
										Tpu32ToIP(pRegInfo->m_tLocalInfo.m_dwLocalIP), 
										pRegInfo->m_tLocalInfo.m_achSoftVersion,
										pRegInfo->m_tLocalInfo.m_achCompileTime);
			}
			break;

		case h_ums_unregistrationcmd:
			{
				RegisterRequest* pRegInfo = (RegisterRequest*)pBuf;
				msgprintnotime("<< UnReg Req stackID:%d, CallID:%s\n", tHandle.handPaCall, pRegInfo->m_achCallId);
			}
			break;

		case h_ums_query:
			{
				TSipRedirectInfo* tSipInfo = (TSipRedirectInfo*)pBuf;
				msgprintnotime("<< Arq Req stackID:%d, Type:%d, Alias:%s\n", tHandle.handPaCall, tSipInfo->m_emType, tSipInfo->m_achBuf);
			}
			break;

		case evtp_ums_reg_ret:
			{
				TCnsRegRetResult* ptRegRet = (TCnsRegRetResult*)pBuf;
				TCnsRegInfo* tRegInfo = (TCnsRegInfo*)((u8*)pBuf+sizeof(TCnsRegRetResult));
				msgprintnotime(">> reg ack stackID:%d, ret:(%d->%s), CallID:", tHandle.handPaCall, TpEnumIdString(EmTpCnsRegUms, ptRegRet->m_emReson));
				printcallid((u8*)tRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);

				u16 i;
				u16 wPrintNum = 0;
				msgprintnotime("<< Reg alias num:%d\n", tRegInfo->m_tCsnNodeInfo.m_wAliasNum);
				for (i=1; i<tRegInfo->m_tCsnNodeInfo.m_wAliasNum; i+=2)
				{
					wPrintNum += 2;
					snprintf(achPrintAlias, MAX_MSG_LEN_TMP, "type:alias %d:%s  %d:%s"
						, tRegInfo->m_tCsnNodeInfo.m_atAlias[i-1].m_byType, tRegInfo->m_tCsnNodeInfo.m_atAlias[i-1].m_abyAlias
						, tRegInfo->m_tCsnNodeInfo.m_atAlias[i].m_byType, tRegInfo->m_tCsnNodeInfo.m_atAlias[i].m_abyAlias);
					
					msgprintnotime("<<   %s\n", achPrintAlias);
				}
				if (wPrintNum < tRegInfo->m_tCsnNodeInfo.m_wAliasNum)
				{
					i = tRegInfo->m_tCsnNodeInfo.m_wAliasNum - 1;
					msgprintnotime("<<   type:alias %d:%s\n", tRegInfo->m_tCsnNodeInfo.m_atAlias[i].m_byType, tRegInfo->m_tCsnNodeInfo.m_atAlias[i].m_abyAlias);
				}

				msgprintnotime(">>   TimeOut:%d, SN:%d, CallType:%d\n", tRegInfo->m_tCsnNodeInfo.m_dwExpires, tRegInfo->m_tCsnNodeInfo.m_nCSqence, tRegInfo->m_dwCallType);
				for (i=0; i<MAX_NUM_CONTACT_ADDR; ++i)
				{
					if (tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[i].m_dwIP == 0)
					{
						break;
					}
					msgprintnotime(">>   addr %d:"ADDRPORT_FORMAT"\n", i+1, ADDRPORT(tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[i].m_dwIP,tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[i].m_wPort));
				}
			}
			break;

		case evtp_ums_unreg_ret:
			{	
				TCnsRegRetResult* ptRegRet = (TCnsRegRetResult*)pBuf;
				TCnsRegInfo* tRegInfo = (TCnsRegInfo*)((u8*)pBuf+sizeof(TCnsRegRetResult));
				msgprintnotime(">> Unreg ack stackID:%d,  ret:(%d->%s), CallID:", tHandle.handPaCall, TpEnumIdString(EmTpCnsRegUms, ptRegRet->m_emReson));
				printcallid((u8*)tRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
				for (u16 wIndex = 0; wIndex < tRegInfo->m_tCsnNodeInfo.m_wAliasNum; ++wIndex)
				{
					msgprintnotime(">>   alias:%s\n", tRegInfo->m_tCsnNodeInfo.m_atAlias[wIndex].m_abyAlias);
				}
				msgprintnotime(">>   TimeOut:%d, SN:%d,\n", tRegInfo->m_tCsnNodeInfo.m_dwExpires, tRegInfo->m_tCsnNodeInfo.m_nCSqence);
				for (u32 i=0; i<MAX_NUM_CONTACT_ADDR; ++i)
				{
					if (tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[i].m_dwIP == 0)
					{
						break;
					}
					msgprintnotime(">>   addr %d:"ADDRPORT_FORMAT"\n", i+1, ADDRPORT(tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[i].m_dwIP,tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[i].m_wPort));
				}
			}
			break;

		case evtp_ums_arq_ret:
			{				
				TCnsRegRetResult* ptRegRet = (TCnsRegRetResult*)pBuf;
				TCnsRegInfo* tRegInfo = (TCnsRegInfo*)((u8*)pBuf+sizeof(TCnsRegRetResult));
				msgprintnotime(">> arq ack stackID:%d, ret:(%d->%s), callType:%d, CallID:"
					, tHandle.handPaCall, TpEnumIdString(EmTpCnsRegUms, ptRegRet->m_emReson), tRegInfo->m_dwCallType);
				printcallid((u8*)tRegInfo->m_tCsnNodeInfo.m_aCallId, TP_MAX_NUM_CALLID);
				msgprintnotime(">>   alias:%s\n", tRegInfo->m_tCsnNodeInfo.m_atAlias[0].m_abyAlias);	
				msgprintnotime(">>   addr("ADDRPORT_FORMAT")\n", ADDRPORT(tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[0].m_dwIP,tRegInfo->m_tCsnNodeInfo.m_atCalledAddr[0].m_wPort));

		        msgprintnotime(">>   QtID:"TPIPFORMAT"\n", Tpu32ToIP(tRegInfo->m_tCsnNodeInfo.m_dwSelfQtID));

            }
			break;
			
		case h_ums_getregreq:
			{
				s32* pnAppid = (s32*)((u8*)pBuf);
				EmSIPRegNSMType* pemReqType = (EmSIPRegNSMType*)(((u8*)pBuf)+sizeof(s32));
				msgprintnotime(">> h_ums_getregreq AppID:%d, ReqType:%d\n", *pnAppid, *pemReqType);
			}	
			break;

		case evtp_ums_reg_info_rsp:
			{
				s32* pnAppID = (s32*)((u8*)pBuf);
				TReqRegInfo* ptRegInfo = (TReqRegInfo*)(((u8*)pBuf)+sizeof(s32));
				msgprintnotime(">> ev_ums_GetRegInfo_Rsp AppID:%d, ReqType:%d, TotalPack:%d, CurPack:%d, AliasType:%d, AliasNum:%d\n",
								*pnAppID, ptRegInfo->m_tRegType, ptRegInfo->m_wTotalPackNum, ptRegInfo->m_wPackSeq, 
								ptRegInfo->m_emSelfType, ptRegInfo->m_wAliasNum);
			}	
			break;

		case evtp_ums_reg_info_rspEx:	
			{
				s32* pnAppID = (s32*)((u8*)pBuf);
				TReqRegInfoEx* ptRegInfo = (TReqRegInfoEx*)(((u8*)pBuf)+sizeof(s32));
				u8* pData = (u8*)(pBuf)+sizeof(s32)+sizeof(TReqRegInfoEx);

				msgprintnotime(">> evtp_ums_reg_info_rspEx AppID:%d, ReqType:%d, TotalPack:%d, CurPack:%d, DataNum:%d, EpType:%d.\n",
								*pnAppID, ptRegInfo->m_tRegType, ptRegInfo->m_wTotalPackNum, ptRegInfo->m_wPackSeq,
								ptRegInfo->m_wDataNum, ptRegInfo->m_emSelfType);

				if (emTPEndpointTypeUMS == ptRegInfo->m_emSelfType)
				{
					TUmsRegData tUmsReg;
					for (u16 wUmsIndex = 0; wUmsIndex < ptRegInfo->m_wDataNum; ++wUmsIndex)
					{
						memcpy(&tUmsReg, pData+sizeof(TUmsRegData)*wUmsIndex, sizeof(TUmsRegData));
						msgprintnotime(">> evtp_ums_reg_info_rspEx UmsAliasNum:%d.\n", tUmsReg.m_wAliasNum);
					}
				}
				else if (emTPEndpointTypeCNS == ptRegInfo->m_emSelfType)
				{
					TCnsRegData tCnsReg;
					for (u16 wCnsIndex = 0; wCnsIndex < ptRegInfo->m_wDataNum; ++wCnsIndex)
					{
						memcpy(&tCnsReg, pData+sizeof(TCnsRegData)*wCnsIndex, sizeof(TCnsRegData));
						msgprintnotime(">> evtp_ums_reg_info_rspEx CnsAliasNum:%d.\n", tCnsReg.m_wAliasNum);
					}
				}
			}
			break;

		default:
			break;
		}
		
	}	
}



