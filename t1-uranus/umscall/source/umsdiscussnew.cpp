#include "umsdiscussnew.h"
#include "eventoutsipadapter.h"
#include "eventoutumscall.h"
#include "umsconfinst.h"
#include "callnodemgr.h"
#include "umseapu.h"
#include "tperrno.h"
#include "umsstackinterface.h"
#include "vmpserviecehandler.h"
#include "umsnetportmgr.h"
#include "callmgr.h"
#include "eqpinterface.h"
#include "umsconfigex.h"
#include "innereventumsaudiomix.h"
#include "umsbas.h"
#include "nodefsm.h"
#include "dualmgr.h"
#include "pollmgr.h"
#include "procnodeds.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpubas.h"
#include "innereventxmpumix.h"
#include "umsxmpinterface.h"
#endif

#define VALID_SCREEN_INDEX(INDEX)  (INDEX < TP_MAX_STREAMNUM)
#define ASSGIN_DIS_VMP_NUM 7   // 讨论所需合成资源
#define ASSGIN_DIS_MIX_NUM 7		// 讨论所需混音资源
// 对讨论目标类统一操作
#define UmsDiscussOprCycle(wIII, wIIIEnd, OprFun)\
	for (wIII = 0; wIII < wIIIEnd; wIII++)\
	{\
	    OprFun;}\
		
inline u16 GetNextIndex( u16 wScreenIndex )
{
	// 按 1 0 2的顺序
	if (wScreenIndex == 0)
	{
		return 2;
	}
	else if (wScreenIndex == 1)
	{
		return 0;
	}
	return 1;
}

inline s8* GetObjTypeName(EmDiscussModleObj emType)
{
	switch (emType)
	{
	case emDiscussObjForSpeakerEp:
		{
			return "SpeakerEpObj";
		}
	case emDiscussObjForThreeScrEp:
		{
			return "ThreeScrEpObj";
		}
	case emDiscussObjForSingleScrEp:
		{
			return "SingleScrEpObj";
		}
	default:
		{
			return "Error Type";
		}
	}
}

inline s8* GetOprTypeName(EmDisChnOprType emType)
{
	switch (emType)
	{
	case EmDisChnAllStart:
		{
			return "AllStart";
		}
	case EmDisChnAddEp:
		{
			return "Add";
		}
	case EmDisChnEpConnect:
		{
			return "Connect";
		}
	case EmDisChnDelEp:
		{
			return "Del";
		}
	case EmDisChnEpDisConnect:
		{
			return "Disconnect";
		}
	case EmDisChnEpChangeSeat:
		{
			return "ChangeSeat";
		}
	case EmDisChnChangeSpeakerEp:
		{
			return "ChangeSpeaker";
		}
	default:
		{
			return "Error Type";
		}
	}
}

static void ShowDstInfo(TDiscussDstEpInfo* ptDstInfo)
{
	TDiscussScreenInfo* ptScreenInfo = NULL;
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; ++wIndex)
	{
		ptScreenInfo = &ptDstInfo->m_atScreenInfo[wIndex];
		if (ptScreenInfo->IsScreenValid())
		{
			msgprintnotime("[%d] DstEp: (%d-%d), AllVmpEp: |", wIndex,
				ptScreenInfo->m_atMember[0].GetHandleOne(),
				ptScreenInfo->m_atMember[0].GetHandleTwo());
			
			for (u16 wLittleIndex = 1; wLittleIndex < UMS_VMP_MAX_RCV; ++wLittleIndex)
			{
				if (0 == ptScreenInfo->m_atMember[wLittleIndex].m_dwHandle)
				{
					continue;
				}
				msgprintnotime("(%d-%d)", ptScreenInfo->m_atMember[wLittleIndex].GetHandleOne(),
					ptScreenInfo->m_atMember[wLittleIndex].GetHandleTwo());
				if (!ptScreenInfo->m_atMember[wLittleIndex].m_bMerged)
				{
					msgprintnotime("|");
				}
				else
				{
					msgprintnotime(" ");
				}
			}
			msgprintnotime("\n");
		}
	}
	return;
}

static void ShowMixMember( TAudMixMemberInfo* ptMixInfo, u16 wScrIndex)
{	
	for (u16 wIndex = 0; wIndex < TP_APU2_MAX_CHAN_NUM; wIndex++)
	{
		if (0 != ptMixInfo->m_awEpId[wIndex])
		{
			msgprintnotime("<%d-%d> ",ptMixInfo->m_awEpId[wIndex], ptMixInfo->m_awScrIndx[wIndex]);
		}
	}
	msgprintnotime("\n");
	return;
}

void DiscussVmpCB(const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, void* param, u16 wTmp1)
{
	CUmsConfInst* pcInst = (CUmsConfInst*)param;
	CUmsDiscussMgr* ptDiscussMgr = pcInst->GetUmsDiscuss();
	ptDiscussMgr->VmpCB(pcService, emOpType, emRes, wTmp1);

	return;
}

void DiscussBasCB(u32 dwType, void* param1, void* param2)
{
#ifdef _USE_XMPUEQP_
    tXmpuBasCbData *pBasCbData = (tXmpuBasCbData *)param1;
	CUmsConfInst* pInst = (CUmsConfInst*)pBasCbData->pService;
	CUmsDiscussMgr* ptDiscussMgr = pInst->GetUmsDiscuss();
	ptDiscussMgr->XmpuBasCB(dwType, (CScreenBasRes *)pBasCbData->pRes, pBasCbData->pData);
#else
	CScreenBasRes::VidBasCBType emType = (CScreenBasRes::VidBasCBType)dwType;
	CUmsDiscussMgr* ptDiscussMgr = (CUmsDiscussMgr*)param1;
	CScreenBasRes* ptBasRes = (CScreenBasRes*)param2;
	
	ptDiscussMgr->BasCB(emType, ptBasRes);
#endif
	return;
}

void DiscussMixCB(u32 dwType, void* param1, void* param2)
{
#ifdef _USE_XMPUEQP_
	tXmpuMixCbData* ptCbData = (tXmpuMixCbData* )param1;
    CUmsConfInst*	pInst = (CUmsConfInst*)ptCbData->pService;
    CUmsDiscussMgr* ptMgr = pInst->GetUmsDiscuss();
    ptMgr->XmpuMixCB( dwType, (TAudMixInfo*)ptCbData->pRes, ptCbData->pData );
#else
	TAudMixInfo::EmCBOprType emType = (TAudMixInfo::EmCBOprType)dwType;
	TAudMixInfo* ptMixInfo = (TAudMixInfo*)param1;
	
	CUmsConfInst* pcInst = (CUmsConfInst*)param2;
	CUmsDiscussMgr* ptDiscussMgr = pcInst->GetUmsDiscuss();
	
	ptDiscussMgr->MixCB(emType, ptMixInfo);

#endif
	return;
}

/////////////////////////////////////////////////////////////////////
/////////////////////会议讨论模式管理类//////////////////////////////
/////////////////////////////////////////////////////////////////////

CUmsDiscussMgr::~CUmsDiscussMgr()
{
	for ( u16 wIndex = 0; wIndex < emDiscussObjEnd; wIndex ++ )
	{
		if(NULL == m_apcDisObj[wIndex])
		{
			continue;
		}
		
		delete m_apcDisObj[wIndex];
		m_apcDisObj[wIndex] = NULL;
	}

}

void CUmsDiscussMgr::Enter()
{
	for (u16 wIndex = 0; wIndex < emDiscussObjEnd; wIndex++)
	{
		m_apcDisObj[wIndex] = NULL;
	}

	m_apcDisObj[emDiscussObjForSpeakerEp] = new CDiscussObjectForSpeakerEp(m_pcConf);
	if (NULL == m_apcDisObj[emDiscussObjForSpeakerEp])
	{
		return;
	}
	m_apcDisObj[emDiscussObjForThreeScrEp] = new CDiscussObjectForThreeScreenEp(m_pcConf);
	if (NULL == m_apcDisObj[emDiscussObjForThreeScrEp])
	{
		return;
	}
	m_apcDisObj[emDiscussObjForSingleScrEp] = new CDiscussObjectForSingleScreenEp(m_pcConf);
	if (NULL == m_apcDisObj[emDiscussObjForSingleScrEp])
	{
		return;
	}

	Init();
	return;
}

void CUmsDiscussMgr::Exit()
{
	for (u16 wIndex = 0; wIndex < emDiscussObjEnd; wIndex++)
	{
		if (NULL == m_apcDisObj[wIndex])
		{
			continue;
		}
		delete m_apcDisObj[wIndex];
		m_apcDisObj[wIndex] = NULL;
	}

}

void CUmsDiscussMgr::Init()
{
	u16 wIII = 0;
	UmsDiscussOprCycle(wIII, emDiscussObjEnd, m_apcDisObj[(EmDiscussModleObj)wIII]->Init();\
		m_atDiscussObj[(EmDiscussModleObj)wIII].Clear());

	m_bUIVacOn = FALSE;
	m_bUIDiscussStatus = FALSE;
	m_bDiscussStaus = FALSE;
	m_tDiscussInfo.Clear();	
	m_tEpAudInfo.Clear();

	m_byDelayStat = 0;
	m_wNewSpeaker = 0;
	m_wOldSpeaker = 0;

}

// TTPMediaTransAddr
#define UmsDiscussPrintAddr(Index, Addr) if (1){\
	msgprintnotime("  Index:%d, Rtp("ADDRPORT_FORMAT"), BackRtcp("ADDRPORT_FORMAT")\n"\
	, Index, ADDRNET(Addr.m_tRtpAddr), ADDRNET(Addr.m_tBackRtcpAddr));}

void CUmsDiscussMgr::Show()
{
	CUmsConfInst* pInst = Inst();
	msgprintnotime("[CUmsDiscussMgr Info] ConfID:%d, DisMdl:%d, UIDisMdl:%d, VacOn:%d, ToTalScreenNum:%d, CurSpeakerId:%d, DelayStat:%d, ChairInDisucss:%d.\n", 
		pInst->GetInsID(), m_bDiscussStaus, m_bUIDiscussStatus, m_bUIVacOn, m_tDiscussInfo.m_wTotalScreenNum, pInst->curSpeakerID(), m_byDelayStat, m_tDiscussInfo.m_wChairEpId);
	
	u16 wIndex = 0;
	u16 byInnerIndex = 0;
	u16 wLoop = 0;
	msgprintnotime("\n<DiscussListInfoFromUI>\n");	
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex ++)
	{
		if (!VALID_ALL_EPID(m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex]))
		{
			continue;
		}
		msgprintnotime("[%d] wEpId:%d\n", wIndex, m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex]);
	}

	TDiscussEpInfo* pEpInfo = NULL;
	msgprintnotime("\n<DiscussListInfo>\n");	
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{
		pEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
		if (pEpInfo->m_bUsed)
		{
			msgprintnotime("[%d] wEpId:%d, wScreenNum:%d, bSmallChanOn:%d, bMtAdjustRes:%d, BasUserInfo:(%d/%d,%d/%d,%d/%d)wGetVidAudIndex:(%d,%d,%d), wMediaNode:%d\n", wIndex, 
				pEpInfo->m_wEpID, pEpInfo->m_wStrceenNum, pEpInfo->m_bIsSmallChanOn, pEpInfo->m_bMtAdjustRes, 
				pEpInfo->m_awBasUserinfo[0].m_wDisUserCount, pEpInfo->m_awBasUserinfo[0].m_wSelUserCount,
				pEpInfo->m_awBasUserinfo[1].m_wDisUserCount, pEpInfo->m_awBasUserinfo[1].m_wSelUserCount,
				pEpInfo->m_awBasUserinfo[2].m_wDisUserCount, pEpInfo->m_awBasUserinfo[2].m_wSelUserCount,
				pEpInfo->m_awGetIndex[0], pEpInfo->m_awGetIndex[1], pEpInfo->m_awGetIndex[2], pEpInfo->m_tGetAddr.m_dwMedia);

			if (!pEpInfo->IsValid())
			{
				continue;
			}

			if (!pInst->IsChairConf() || !VALID_LOCAL_EPID(pEpInfo->m_wEpID))
			{
				msgprintnotime("PutAudAddr:\n");
				if (pEpInfo->IsSingleScr())
				{
					UmsDiscussPrintAddr(MIDSCREENINDEX, pEpInfo->m_atPutAuddr[MIDSCREENINDEX]);
				}
				else
				{
					UmsDiscussOprCycle(wLoop, TP_MAX_STREAMNUM, UmsDiscussPrintAddr(wLoop, pEpInfo->m_atPutAuddr[wLoop]));
				}
			}
			
			if (pInst->IsChairConf())
			{	
				if (pEpInfo->IsSingleScr())
				{
					msgprintnotime("Vid:\n");
					UmsDiscussPrintAddr(MIDSCREENINDEX, pEpInfo->m_tGetAddr.m_atVidAddr[MIDSCREENINDEX]);
					msgprintnotime("Aud:\n");
					UmsDiscussPrintAddr(MIDSCREENINDEX, pEpInfo->m_tGetAddr.m_atAudAddr[MIDSCREENINDEX]);
					if (NULL != pEpInfo->m_apcBas[MIDSCREENINDEX])
					{
						msgprintnotime("Bas For SmallVid:\n");
#ifdef _USE_XMPUEQP_
						msgprintnotime("  Index:%d, emVideoRes:%s, BasEqpId:%d, State:%d(0:idle;1:start;2:run)\n", 
							MIDSCREENINDEX, UmsVidResPrint(pEpInfo->m_aemVideoRes[MIDSCREENINDEX]),
							pEpInfo->m_apcBas[MIDSCREENINDEX]->GetBasEqpId(), 
							pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_emStat);

						if(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_emStat != EmXmpuResStatInfo_Idle)
						{
							msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
								Tpu32ToIP(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_tDecMiddleRtpAddr.GetIP()), pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_tDecMiddleRtpAddr.GetPort(), 
								Tpu32ToIP(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_tDecRtcpAddr.GetIP()), pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_tDecRtcpAddr.GetPort(), 
								Tpu32ToIP(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_tDecRtpAddr.GetIP()), pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_tDecRtpAddr.GetPort());
							
							for(byInnerIndex = 0; byInnerIndex < 1; byInnerIndex++)
							{
								msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
									byInnerIndex,
									Tpu32ToIP(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetIP()), pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
									Tpu32ToIP(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
									Tpu32ToIP(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetIP()), pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
							}
						}	
#else
						msgprintnotime("  Index:%d, emVideoRes:%s, BasId:%d, ChnIndx:%d, UmsStartPort:%d, EqpStartPort:%d, DsIP:"TPIPFORMAT"\n", 
							MIDSCREENINDEX, UmsVidResPrint(pEpInfo->m_aemVideoRes[MIDSCREENINDEX]),
							pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
							pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx,
							pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tBasEqpRes.m_tBasChnInfo.m_wUmsStartPort,
							pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tBasEqpRes.m_tBasChnInfo.m_wEqpStartPort,
							u32ToIP(pEpInfo->m_apcBas[MIDSCREENINDEX]->m_tBasEqpRes.m_tBasChnInfo.m_dwMediaIP));
#endif
					}
					else
					{
						msgprintnotime("Adjust For SmallVid:\n");
						msgprintnotime("  Index:%d, emVideoRes:%s\n", MIDSCREENINDEX, UmsVidResPrint(pEpInfo->m_aemVideoRes[MIDSCREENINDEX]));
					}
				}
				else
				{
					msgprintnotime("Vid:\n");
					UmsDiscussOprCycle(wLoop, TP_MAX_STREAMNUM, UmsDiscussPrintAddr(wLoop, pEpInfo->m_tGetAddr.m_atVidAddr[wLoop]));
					msgprintnotime("Aud:\n");
					UmsDiscussOprCycle(wLoop, TP_MAX_STREAMNUM, UmsDiscussPrintAddr(wLoop, pEpInfo->m_tGetAddr.m_atAudAddr[wLoop]));
					msgprintnotime("Mix:\n");
					UmsDiscussPrintAddr(MIDSCREENINDEX, pEpInfo->m_tGetAddr.m_tMixAddr);
					if (pEpInfo->m_bIsSmallChanOn)
					{
						msgprintnotime("SmallVid:\n");
						UmsDiscussOprCycle(wLoop, TP_MAX_STREAMNUM, UmsDiscussPrintAddr(wLoop, pEpInfo->m_tGetAddr.m_atSmallAddr[wLoop]));
					}
					else
					{
						msgprintnotime("Bas or Adjust For SmallVid:\n");
						for (wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
						{
							if (NULL != pEpInfo->m_apcBas[wLoop])
							{
#ifdef _USE_XMPUEQP_
								msgprintnotime("  Index:%d, emVideoRes:%s, BasEqpId:%d, State:%d(0:idle;1:start;2:run)\n", 
									wLoop, UmsVidResPrint(pEpInfo->m_aemVideoRes[wLoop]),
									pEpInfo->m_apcBas[wLoop]->GetBasEqpId(), 
									pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_emStat);
								
								if (pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_emStat != EmXmpuResStatInfo_Idle)
								{
									msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
										Tpu32ToIP(pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_tDecMiddleRtpAddr.GetIP()), pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_tDecMiddleRtpAddr.GetPort(), 
										Tpu32ToIP(pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_tDecRtcpAddr.GetIP()), pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_tDecRtcpAddr.GetPort(), 
										Tpu32ToIP(pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_tDecRtpAddr.GetIP()), pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_tDecRtpAddr.GetPort());
									
									for(byInnerIndex = 0; byInnerIndex < 1; byInnerIndex++)
									{
										msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
											byInnerIndex,
											Tpu32ToIP(pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetIP()), pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
											Tpu32ToIP(pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
											Tpu32ToIP(pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetIP()), pEpInfo->m_apcBas[wLoop]->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
									}
								}
#else
								msgprintnotime("  Index:%d, emVideoRes:%s, BasId:%d, ChnIndx:%d, UmsStartPort:%d, EqpStartPort:%d, DsIP:"TPIPFORMAT"\n", 
									wLoop, UmsVidResPrint(pEpInfo->m_aemVideoRes[wLoop]),
									pEpInfo->m_apcBas[wLoop]->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
									pEpInfo->m_apcBas[wLoop]->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx,
									pEpInfo->m_apcBas[wLoop]->m_tBasEqpRes.m_tBasChnInfo.m_wUmsStartPort,
									pEpInfo->m_apcBas[wLoop]->m_tBasEqpRes.m_tBasChnInfo.m_wEqpStartPort,
									u32ToIP(pEpInfo->m_apcBas[wLoop]->m_tBasEqpRes.m_tBasChnInfo.m_dwMediaIP));
#endif
							}
							else
							{
								msgprintnotime("  Index:%d, emVideoRes:%s\n", wLoop, UmsVidResPrint(pEpInfo->m_aemVideoRes[wLoop]));
							}
						}
					}
				}
			}
			msgprintnotime("\n");
		}
	}

	if (pInst->IsChairConf())
	{
		msgprintnotime("\n<SpeakerEpRecInfo>\n");
		for (wIndex = 0; wIndex < UmsDiscuss_VmpEp_Max_Num; wIndex++)
		{
			if (0 != m_tDiscussInfo.m_tSpeakerRec.m_awSpeakerRec[wIndex])
			{
				msgprintnotime("[%d] RecEp:%d\n", wIndex, m_tDiscussInfo.m_tSpeakerRec.m_awSpeakerRec[wIndex]);
				continue;
			}
		}
		
		msgprintnotime("\n<DiscussObjInfo>\n");
		UmsDiscussOprCycle(wIndex, emDiscussObjEnd, m_apcDisObj[(EmDiscussModleObj)wIndex]->Show());

		msgprintnotime("[ForSpecialEpObj]-[%d]\n",m_tDiscussInfo.m_wSpecialEp);
		ShowDstInfo(&m_tDiscussInfo.m_tSpecialDst);
		msgprintnotime("\n");
	}
	else
	{
		msgprintnotime("\n<EpAudInfo>\n");

		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			if (0 == m_tEpAudInfo.m_awDiscussEpId[wIndex])
			{
				break;
			}

			msgprintnotime("  [%d] EpId:%d, IsRcvNMode(%d,%d,%d)\n", wIndex, m_tEpAudInfo.m_awDiscussEpId[wIndex],
				m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][0], m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][1],
				m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][2]);
		}

		msgprintnotime("[ForSpecialEpObj]-[%d]\n",m_tDiscussInfo.m_wSpecialEp);

		msgprintnotime("\n");
	}
	
	TDiscussObjInfo* pInfo = NULL;
	for (wIndex = 0; wIndex < emDiscussObjEnd; wIndex++)
	{
		pInfo = &m_atDiscussObj[(EmDiscussModleObj)wIndex];
		msgprintnotime("[%s]-[%d]\n", GetObjTypeName((EmDiscussModleObj)wIndex), pInfo->m_wReserve);
		for (wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
		{
			msgprintnotime("[%d] bIsVaild:%d, Name:%s\n", wLoop, pInfo->m_abIsVaild[wLoop], pInfo->m_atEpAlias[wLoop].m_abyAlias);
		}
	}

	msgprintnotime("\n");
	msgprintnotime("  [PutAudMgr].\n");
	pInst->GetPutAudMgr()->Show();
	msgprintnotime("\n[CUmsDiscussMgr Info] End!\n");
	
	return;
}

BOOL32 CUmsDiscussMgr::HandlerFromStack( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();


	switch (ptMsg->GetEvent())
	{
	case ev_UmsConfAMixUpdate_Cmd:    // 主席cnc消息：开启和关闭讨论，非讨论下，增删讨论会场；
		{
			OnDiscussStatusCmd(ptMsg);   
		}
		break;
	case ev_UmsAudMixDisListOpr_Cmd:   // 主席cnc消息：讨论下，增删讨论会场
		{
			OnDiscussListOprCmd(ptMsg);
		}
		break;
	case ev_UmsConfAMixVacSwitch:
		{
			OnDiscussMixVacOprCmd(ptMsg);
		}
		break;
	case evtp_UmsDiscussScreenStat_Notify:
		{
			OnCasecadeDiscussNtfy(ptMsg);
		}
		break;
	case evtp_UmsDiscussFastUpdate_Req:
		{
			OnAskKeyFrameFromDown(ptMsg);
		}
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL32 CUmsDiscussMgr::HandlerFromUmc( CTpMsg *const ptMsg )
{
	switch (ptMsg->GetEvent())
	{
	case evtp_StartAuxMix_cmd:
		{
			OnDiscussStatusCmdFromUmc(ptMsg);
		}
		break;
	case evtp_UpdateAudMixInfo_cmd:
		{
			OnDiscussListOprFromUmc(ptMsg);
		}
		break;
	case ev_AuxMixVacSwitch:
		{
			OnDiscussMixVacOprCmdFromUmc(ptMsg);
		}
		break;
	case evtp_Ums_For_Discuss_Timer:
		{
			MdlHint(Ums_Mdl_Call, ("Timer is Coming...ConfId:%d.\n", Inst()->GetInsID()));
			SetDelayStat(2);
			AdjustAllNodeToDiscuss(TRUE);
			m_wNewSpeaker = 0;
			m_wOldSpeaker = 0;
		}
		break;
	default:
		{
			return FALSE;
		}
	}
	return TRUE;
}

// 会议开始时，可以预置讨论列表，并开启讨论
void CUmsDiscussMgr::InitDiscuss( TAuxMixList& tAuxMixList )
{
	CUmsConfInst* pInst = Inst();
	
	if (!pInst->IsChairConf())
	{// 非上级不处理
		return ;
	}
	
	MdlHint(Ums_Mdl_Call, ("[InitDiscuss] ConfID:%d, bDiscussOn:%d, bVacOn:%d\n", pInst->GetInsID(), 
		tAuxMixList.m_bAudMixOn, tAuxMixList.m_bVacOn));
	
	TConfAuxMixInfo tAudMix;
	tAudMix.m_wConfID = pInst->GetInsID();
	tAudMix.m_bStart = tAuxMixList.m_bAudMixOn;
	tAudMix.m_atAuxMixList = tAuxMixList;
	tAudMix.m_bVacOn = tAuxMixList.m_bVacOn;
	m_bUIVacOn = tAudMix.m_bVacOn;  // 如果讨论不预置开启的话，下面的OnDiscussStatusCmd是不会保存语音激励状态的，这里先保存下。。。
	
	//模板中的EpID是从0开始，需要和业务同步（业务从1开始）
	for ( u16 wIndx = 0; wIndx < TP_CONF_MAX_AUDMIXNUM; wIndx ++ )
	{
		if( !TP_VALID_HANDLE(tAudMix.m_atAuxMixList.m_awList[wIndx]) )
		{
			continue;
		}
		tAudMix.m_atAuxMixList.m_awList[wIndx]++;
	}

	TLogUser tUser;
	CTpMsg cMsg;
	cMsg.SetBody(&tUser, sizeof(tUser));
	cMsg.CatBody(&tAudMix, sizeof(tAudMix));
	EmDiscussRspRet  emRet = OnDiscussStatusCmdFromUmc(&cMsg);
	if (emRet)
	{
		//发送给界面
		TTPUmsReasonInd tInd;
		tInd.m_wConfID = pInst->GetInsID();
		switch(emRet)
		{
		case em_Start_AssginVmpFail:
			tInd.m_dwReason = TP_Discuss_AssignVmpFail;
			break;
		case em_Start_AssignMixFail:
			tInd.m_dwReason = TP_Discuss_AssignMixFail;
			break;
		case em_Start_AssignBasFail:
			tInd.m_dwReason = TP_Discuss_AssignVBasFail;
			break;
		default:
			tInd.m_dwReason = TP_Discuss_OtherFail;
			break;
		}
		pInst->NotifyMsgToServiceForUI(evtp_UmsCommonReasonToUI_Ind, &tInd, sizeof(tInd));
	}		
	return ;	
}

// 结束会议时，释放讨论相关资源
void CUmsDiscussMgr::ReleaseDiscuss()
{
	if (Inst()->IsChairConf())
	{
		StopDiscussModle();
	}
	Init();

	Inst()->GetPutAudMgr()->ReleaseAll(em_putauduser_discuss);

	return;
}

// 讨论内会场上线
void CUmsDiscussMgr::OnChanConnect( TCallNode* ptNode )
{		
	CUmsConfInst* pInst = Inst();

	u16 wIndex = m_tDiscussInfo.m_tDiscussEpFromUI.FindIndexByEp(ptNode->m_wEpID); 
	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(ptNode->m_wEpID);

	if (ptNode->IsUms())
	{// 对ums的处理
		if (TP_VALID_HANDLE(wIndex) && pInst->IsChairConf())
		{// ums出现在讨论成员中，需要删除
			m_tDiscussInfo.m_tDiscussEpFromUI.DelMixId(ptNode->m_wEpID);

			if (m_bUIDiscussStatus)
			{
				if (NULL != ptEpInfo)
				{
					m_tDiscussInfo.DelEpById(ptEpInfo->m_wEpID);
				}

				pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Discard_EpOnLine, pInst->chairID(), ptNode->m_wEpID, (u32)em_Discuss_OtherFail);

				if (m_tDiscussInfo.m_tDiscussEpFromUI.GetMixNum() < 1)
				{
					pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_NoVaildEp, pInst->chairID());
					StopDiscussModle();
				}
			}
			DiscussInfoNotify();
		}

		if (m_bDiscussStaus)
		{// ums上线后，如果当前是讨论状态，需要通知下去
			TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
			if (NULL != ptFatherNode && ptNode == ptFatherNode)
			{// 
				TUmsHandle tHandle;
				TDiscussCasecadeNtfy tNtfy;
				
				MakeCasecadeObjNtfy(ptFatherNode, tNtfy);

				pInst->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
				UmsSendConfCtrl(tHandle, evtp_UmsDiscussScreenStat_Notify, &tNtfy, sizeof(tNtfy));
				
				// 切到讨论
				pInst->GetNodeFsm()->StartDis(ptFatherNode);
			}
		}
		return;
	}

	// 对会场的处理

	if ( !pInst->IsChairConf() )
	{// 非上级不处理
		return;
	}

	if (!TP_VALID_HANDLE(wIndex))
	{// 不在讨论列表中
		MdlHint(Ums_Mdl_Call, ("[OnChanConnect] ep is not in Dis! ConfId:%d, epId:%d, discussScreenNum:%d\n",
			pInst->GetInsID(), ptNode->m_wEpID, m_tDiscussInfo.m_wTotalScreenNum));
		return;
	}

	if (!m_bUIDiscussStatus)
	{
		MdlHint(Ums_Mdl_Call, ("[OnChanConnect] Now is not Dis Modle! ConfId:%d, epId:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
		return;
	}

	// 对讨论列表成员上线处理
	do 
	{
		if (NULL == ptEpInfo)
		{
			ptEpInfo = m_tDiscussInfo.AddEpID(ptNode);
			if (NULL == ptEpInfo)
			{
				MdlError(Ums_Mdl_Call, ("[OnChanConnect] list Is Full. ConfID:%d, EpId:%d\n", 
					pInst->GetInsID(), ptNode->m_wEpID));
				break;
			}
		}
		
		EmDiscussOprRes emOprRes = AddEpInDiscussChan(ptEpInfo);
		if (em_Disucss_Opr_Successed != emOprRes)
		{
			// 提示进入讨论失败
			pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Discard_EpOnLine, pInst->chairID(), ptEpInfo->m_wEpID, (u32)emOprRes);
			RemoveEpFromDiscussChan(ptEpInfo);

			if (m_tDiscussInfo.m_tDiscussEpFromUI.GetMixNum() < 1)
			{
				pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_NoVaildEp, pInst->chairID());
				StopDiscussModle();
			}

			break;
		}

		AdjustDiscussStatus(EmDisChnEpConnect, ptNode->m_wEpID);
		return;	
		
	} while (0);
	
	DiscussInfoNotify();

	return;
}

// 挂断讨论内会场
void CUmsDiscussMgr::OnHungUpNode(TCallNode* ptNode, EmCnsCallReason emReason /* = EmCnsCallReason_success */)
{
	CUmsConfInst* pInst = Inst();

	if (pInst->m_bIsQuiting)
	{
		MdlHint(Ums_Mdl_Call, ("[CUmsDiscussMgr::OnHungUpNode] Now Is Quiting Conf! ConfId:%d, epId:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
		return;
	}

	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(ptNode->m_wEpID);
	if (NULL != ptEpInfo)
	{
		if (!pInst->IsChairConf())
		{	
			ptNode->m_wMixIndex = TP_INVALID_INDEX;
			m_tDiscussInfo.DelEpById(ptNode->m_wEpID);
		}
		else
		{
			if (emReason == EmCnsCallReason_hungup || emReason == EmCnsCallReason_peerhungup)
			{
				RemoveEpFromDiscussChan(ptEpInfo);
			}
			else
			{
				DelEpInDiscussChan(ptEpInfo);
				m_tDiscussInfo.m_tSpeakerRec.DelRec(ptEpInfo->m_wEpID);
				m_tDiscussInfo.DelEpChanInfo(ptEpInfo->m_wEpID);
			}
			
			if (0 == m_tDiscussInfo.m_wTotalScreenNum)
			{
				pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_NoVaildEp, pInst->chairID());
				StopDiscussModle();
			}
			else
			{
				AdjustDiscussStatus(EmDisChnEpDisConnect, ptNode->m_wEpID);
			}
			DiscussInfoNotify();
		}
	}

	if (ptNode->IsUms())
	{
		u16 awChildEpID[TP_CONF_MAX_CNSNUM];
		u16 wEpChildNum = pInst->GetNodeMgr()->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, ptNode);
		for (u16 wI = 0; wI < wEpChildNum; ++wI)
		{
			ptEpInfo = m_tDiscussInfo.FindEpById(awChildEpID[wI]);
			if (NULL != ptEpInfo)
			{
				RemoveEpFromDiscussChan(ptEpInfo);

				if (0 == m_tDiscussInfo.m_wTotalScreenNum)
				{
					pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_NoVaildEp, pInst->chairID());
					StopDiscussModle();
				}
				else
				{
					AdjustDiscussStatus(EmDisChnEpDisConnect, ptEpInfo->m_wEpID);
				}
			}
			else
			{
				m_tDiscussInfo.m_tDiscussEpFromUI.DelMixId(awChildEpID[wI]);
			}
		}
		DiscussInfoNotify();
	}

	return;
}

void CUmsDiscussMgr::OnChangerSpeaker( TCallNode* ptSpeakerNode)
{
	AdjustDiscussStatus(EmDisChnChangeSpeakerEp, ptSpeakerNode->m_wEpID);
	return;
}

void CUmsDiscussMgr::OnAdjustInnerSpeaker( TCallNode* ptNode )
{
	AdjustDiscussStatus(EmDisChnEpChangeSeat, ptNode->m_wEpID);
	return;
}

void CUmsDiscussMgr::UpdateMixDepthChanID(TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum)
{
	CUmsConfInst* pInst = Inst();
	if (NULL == pInst || NULL == ptMixInfo || 0 == byNum)
	{
		return;
	}

	EmDiscussModleObj emType = emDiscussObjEnd;
	u16 wScreenIndex = TP_MAX_STREAMNUM;
	if (ptMixInfo == pInst->GetSpeaker().m_ptAudMix)
	{// 单屏用的混音器
		emType = emDiscussObjForSingleScrEp;
		wScreenIndex = MIDSCREENINDEX;
	}
	else
	{
		if (!FindDiscussObjTypebyMixRes(ptMixInfo->m_tEqpRes.m_byEqpID, emType, wScreenIndex))
		{
			MdlError(Ums_Mdl_Call, ("[UpdateMixDepthChanID] FindDiscussObjTypebyMixRes fail!! ConfID:%d, MixId:%d.\n",
				pInst->GetInsID(), ptMixInfo->m_tEqpRes.m_byEqpID));
			return;
		}
	}

	if (emType < emDiscussObjEnd)
	{
		m_apcDisObj[emType]->UpdateSpeakerSideLine(&m_tDiscussInfo, ptMixInfo, byChanId, byNum, wScreenIndex);
	}

	return;
}

void CUmsDiscussMgr::AdjustDualAudMedia()
{
	m_apcDisObj[emDiscussObjForSingleScrEp]->AdjustDstAudToApu2TpDsInfo(&m_tDiscussInfo, m_pcConf->curSpeakerID());
}

BOOL32 CUmsDiscussMgr::AdjustGetVidFailed( u16 wGetIndex )
{
	if (wGetIndex < TP_UMS_MAX_CALLNUM)
	{
		TDiscussEpInfo* ptEpInfo = NULL;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			ptEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
			if (ptEpInfo->IsEqualGetVidIndx(wGetIndex))
			{
				Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Discard_AddEp, Inst()->chairID(), ptEpInfo->m_wEpID, (u32)em_Disccuss_GetVid_Error);
				RemoveEpFromDiscussChan(ptEpInfo);				
				if (m_tDiscussInfo.m_wTotalScreenNum == 0)
				{
					Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_NoVaildEp, Inst()->chairID());
					StopDiscussModle();
				}
				else
				{
					AdjustDiscussStatus(EmDisChnDelEp, ptEpInfo->m_wEpID);
				}

				DiscussInfoNotify();

				return TRUE;
			}
		}
	}
	return FALSE;
}

void CUmsDiscussMgr::GetDiscussStateInfo( TConfAuxMixInfo& tInfo )
{
	tInfo.m_bStart = m_bUIDiscussStatus;
	tInfo.m_bVacOn = m_bUIVacOn;
	tInfo.m_wConfID = Inst()->GetInsID();
	tInfo.m_atAuxMixList = m_tDiscussInfo.m_tDiscussEpFromUI;
	return;
}

void CUmsDiscussMgr::GetDiscussObjInfo(TCapNode* ptNode, TTpObj& tObj, u16 wScreenIndex)
{
	CUmsConfInst* pInst = Inst();
	
	TDiscussObjInfo* ptInfo = NULL;

	tObj.m_emObj = emObjDiscard;
	tObj.m_wScrIndx = wScreenIndex;
	
	if (IsSpeacialEp(ptNode->m_wEpID))
	{// for special目标
		if (MIDSCREENINDEX == wScreenIndex)
		{
			ptInfo = &m_atDiscussObj[emDiscussObjForThreeScrEp];
		}
		else
		{
			ptInfo = &m_atDiscussObj[emDiscussObjForSpeakerEp];
		}
	}
	else if (pInst->curSpeakerID() == ptNode->m_wEpID)
	{//取发言会场目标
		ptInfo = &m_atDiscussObj[emDiscussObjForSpeakerEp];	
	}
	else if (ptNode->IsThreeVidRcv())
	{//取三屏目标
		ptInfo = &m_atDiscussObj[emDiscussObjForThreeScrEp];
	}
	else
	{//取单屏目标
		ptInfo = &m_atDiscussObj[emDiscussObjForSingleScrEp];
	}
	
	tObj.m_tAlias = ptInfo->m_atEpAlias[wScreenIndex];
	tObj.m_wVidNum = ptInfo->m_abIsVaild[wScreenIndex]?1:0;
	tObj.m_wAudNum = tObj.m_wVidNum;
	
	return;
}

void CUmsDiscussMgr::VmpCB( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wMemberIndx )
{
	CUmsConfInst* pInst = Inst();

	// vmp回调处理
	if ( em_Res_Success != emRes )
	{
		MdlError(Ums_Mdl_Call, ("[VmpCB] ConId:%d, ServiceId:%d, OprType:%d, Res:%d, MemberIndex:%d\n", 
			pInst->GetInsID(), pcService->GetServiceID(), emOpType, emRes, wMemberIndx));
		pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_VmpError, pInst->chairID());
		StopDiscussModle();
		DiscussInfoNotify();
		return;
	}

	if (em_Frame_Service == emOpType)
	{
		MdlLowDtl(Ums_Mdl_Call, ("[VmpCB] ConId:%d, ServiceId:%d, OprType:%d, Res:%d, MemberIndex:%d\n", 
			pInst->GetInsID(), pcService->GetServiceID(), emOpType, emRes, wMemberIndx));

		EmDiscussModleObj emType = emDiscussObjEnd;
		u16 wScreenIndex = TP_INVALID_INDEX;
		u16 wEpId = TP_INVALID_INDEX;
		u16 wSeatIndex = TP_INVALID_INDEX;
		if (FindDiscussObjTypebyVmpRes(pcService->GetServiceID(), emType, wScreenIndex))
		{
			if (m_tDiscussInfo.IsSpecialEpVaild() && emDiscussObjForSpeakerEp == emType && MIDSCREENINDEX != wScreenIndex)
			{
				wEpId = m_tDiscussInfo.m_tSpecialDst.m_atScreenInfo[wScreenIndex].m_atMember[wMemberIndx].GetHandleOne();
				wSeatIndex = m_tDiscussInfo.m_tSpecialDst.m_atScreenInfo[wScreenIndex].m_atMember[wMemberIndx].GetHandleTwo();
			}
			else
			{
				m_apcDisObj[emType]->GetVmpMemberEpByIndex(wScreenIndex, wMemberIndx, wEpId, wSeatIndex);
			}
	
			TDiscussEpInfo* ptEpInfo = GetDiscussEpInfoById(wEpId);
			if (NULL != ptEpInfo && ptEpInfo->IsValid())
			{
				if (NULL != ptEpInfo->m_apcBas[wSeatIndex] && 0 != wMemberIndx)
				{// 该会场座席的小码流从适配出，则向适配请求
					pInst->GetBas()->AskFrameToScreenBas(ptEpInfo->m_apcBas[wSeatIndex]);
				}
				else
				{// 向会场对应的屏请求
					if ( wSeatIndex < TP_MAX_STREAMNUM && ptEpInfo->m_awGetIndex[wSeatIndex] < TP_UMS_MAX_CALLNUM )
					{
						pInst->GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[wSeatIndex]);
					}
				}
			}
		}
	}

	return ;
}

void CUmsDiscussMgr::VmpCBForSingle( const CBaseService* pcService, const EmServiceOpType emOpType, const EmServiceRes emRes, u16 wMemberIndx )
{
	CUmsConfInst* pInst = Inst();
	
	if (pcService != pInst->GetSpeaker().m_pcSingleVmp)
	{
		return;
	}

	// vmp回调处理
	if ( em_Res_Success != emRes )
	{
		MdlError(Ums_Mdl_Call, ("[VmpCBForSingle] ConId:%d, ServiceId:%d, OprType:%d, Res:%d, MemberIndex:%d\n", 
			pInst->GetInsID(), pcService->GetServiceID(), emOpType, emRes, wMemberIndx));
		pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_VmpError, pInst->chairID());
		StopDiscussModle(TRUE, FALSE);
		DiscussInfoNotify();
		m_pcConf->GetVmp()->StopSpeakerVmp();
		return;
	}
	
	if (em_Frame_Service == emOpType)
	{
		MdlLowDtl(Ums_Mdl_Call, ("[VmpCBForSingle] ConId:%d, ServiceId:%d, OprType:%d, Res:%d, MemberIndex:%d\n", 
			pInst->GetInsID(), pcService->GetServiceID(), emOpType, emRes, wMemberIndx));
		
		u16 wEpId = TP_INVALID_INDEX;
		u16 wSeatIndex = TP_INVALID_INDEX;
		// 得到关键帧目的会场和座席
		m_apcDisObj[emDiscussObjForSingleScrEp]->GetVmpMemberEpByIndex(MIDSCREENINDEX, wMemberIndx, wEpId, wSeatIndex);		
		TDiscussEpInfo* ptEpInfo = GetDiscussEpInfoById(wEpId);
		if (NULL != ptEpInfo && ptEpInfo->IsValid())
		{
			if (NULL != ptEpInfo->m_apcBas[wSeatIndex] && 0 != wMemberIndx)
			{// 该会场座席的小码流从适配出，则向适配请求
				pInst->GetBas()->AskFrameToScreenBas(ptEpInfo->m_apcBas[wSeatIndex]);
			}
			else
			{// 向会场对应屏请求
				if ( wSeatIndex < TP_MAX_STREAMNUM && ptEpInfo->m_awGetIndex[wSeatIndex] < TP_UMS_MAX_CALLNUM )
				{
					pInst->GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[wSeatIndex]);
				}
			}
		}
	}
	
	return ;
}


#ifdef  _USE_XMPUEQP_
void CUmsDiscussMgr::XmpuMixCB( u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData )
{
	TXmpuStartMixNty  tStartInfo;
    TXmpuAddMixMemNty tAddMemInfo;
	
	BOOL32 bError = FALSE;
	
    if (dwEvent == evXmpu_UmsStartMix_Nty)
	{
        memcpy(&tStartInfo, pData, sizeof(tStartInfo));
		if (!tStartInfo.m_bSuccess)
		{
            bError = TRUE;
		}
	} else if (dwEvent == evUms_XmpuAddMixMember_Nty)
	{
		memcpy(&tAddMemInfo, pData, sizeof(TXmpuAddMixMemNty));
		if (!tAddMemInfo.m_bSuccess)
		{
			bError = TRUE;
		}
	} else if (dwEvent == evXmpu_VacActive_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixVoiceDetection_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixDisConnect_Nty)
	{
		bError = TRUE;
	}
	
	if (bError)
	{
		MdlError(Ums_Mdl_Call, ("[CUmsDiscussMgr::XmpuMixCB] ConId:%d, CBType:%d(startfail:%d, addmemfail:%d, discon:%d ), StopDiscuss\n", 
			    Inst()->GetInsID(), dwEvent, evXmpu_UmsStartMix_Nty, evUms_XmpuAddMixMember_Nty, evXmpu_MixDisConnect_Nty));
	    Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_MixError, Inst()->chairID());
	    StopDiscussModle();
	    DiscussInfoNotify();
	}

	return;
}

void CUmsDiscussMgr::XmpuMixCBForSingle(u32 dwEvent, TAudMixInfo* ptMixInfo, void* pData)
{
	TXmpuStartMixNty  tStartInfo;
    TXmpuAddMixMemNty tAddMemInfo;
	
	BOOL32 bError = FALSE;
	
    if (dwEvent == evXmpu_UmsStartMix_Nty)
	{
        memcpy(&tStartInfo, pData, sizeof(tStartInfo));
		if (!tStartInfo.m_bSuccess)
		{
            bError = TRUE;
		}
	} else if (dwEvent == evUms_XmpuAddMixMember_Nty)
	{
		memcpy(&tAddMemInfo, pData, sizeof(TXmpuAddMixMemNty));
		if (!tAddMemInfo.m_bSuccess)
		{
			bError = TRUE;
		}
	} else if (dwEvent == evXmpu_VacActive_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixVoiceDetection_Ntf)
	{
		
	} else if (dwEvent == evXmpu_MixDisConnect_Nty)
	{
		bError = TRUE;
	}
	
	if (bError)
	{
		MdlError(Ums_Mdl_Call, ("[CUmsDiscussMgr::XmpuMixCBForSingle] ConId:%d, CBType:%d(startfail:%d, addmemfail:%d, discon:%d ), StopDiscuss\n", 
			Inst()->GetInsID(), dwEvent, evXmpu_UmsStartMix_Nty, evUms_XmpuAddMixMember_Nty, evXmpu_MixDisConnect_Nty));
	
	    Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_MixError, Inst()->chairID());
	    StopDiscussModle(FALSE, TRUE);
	    DiscussInfoNotify();		
	
	    if (m_pcConf->GetDualMgr()->IsStart())
		{
		    m_pcConf->GetDualMgr()->OnStopDualCmdForUmcCnc();
		}
	
	}
	
	return;
}

#else 
void CUmsDiscussMgr::MixCB( TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo )
{// mixCB

	if (NULL == ptMixInfo)
	{
		return;
	}

	MdlError(Ums_Mdl_Call, ("[MixCB] ConId:%d, EqpId:%d, CBType:%d\n", 
		Inst()->GetInsID(), ptMixInfo->m_tEqpRes.m_byEqpID, emType));

	Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_MixError, Inst()->chairID());
	StopDiscussModle();
	DiscussInfoNotify();
	
	return;
}

void CUmsDiscussMgr::MixCBForSingle( TAudMixInfo::EmCBOprType emType, TAudMixInfo* ptMixInfo )
{// mixCB

	if (ptMixInfo != Inst()->GetSpeaker().m_ptAudMix)
	{
		return;
	}

	MdlError(Ums_Mdl_Call, ("[MixCBForSingle] ConId:%d, EqpId:%d, CBType:%d\n", 
		m_pcConf->GetInsID(), ptMixInfo->m_tEqpRes.m_byEqpID, emType));

	Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_MixError, Inst()->chairID());
	StopDiscussModle(FALSE, TRUE);
	DiscussInfoNotify();		

	// stopdual?
	if (m_pcConf->GetDualMgr()->IsStart())
	{
		m_pcConf->GetDualMgr()->OnStopDualCmdForUmcCnc();
	}
	
	return;
}
#endif


#ifdef _USE_XMPUEQP_
void CUmsDiscussMgr::XmpuBasCB(u32 dwType, CScreenBasRes* ptBasRes, void *pData)
{//BasCB
	if (NULL == ptBasRes)
	{
		return;
	}
	CUmsConfInst* pInst = Inst();
	u16 wScreen = ptBasRes->m_wSrcScreenIndx;
	if (TP_INVALID_INDEX == wScreen)
	{
       return;
	}

	MdlHint(Ums_Mdl_Call, ("[CUmsDiscussMgr::XmpuBasCB] ConfID:%d, BasEqpID:%d, CBType:%d, ScrEp:%d, screen:%d\n", 
		pInst->GetInsID(), ptBasRes->GetBasEqpId(),  dwType, ptBasRes->m_wSrcEp, wScreen));
	
	TXmpuStartBasNty tStartBastNty;
	BOOL32 bError = FALSE;

	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(ptBasRes->m_wSrcEp);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{
		return;
	}
	TCallNode* ptNode = pInst->GetNode(ptEpInfo->m_wEpID);
	if (NULL == ptNode)
	{
		return;
	}

    if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		memcpy(&tStartBastNty, pData, sizeof(tStartBastNty));  
		if (!tStartBastNty.m_bSuccess)
		{
			bError = TRUE;
			MdlError(Ums_Mdl_Call, ("CUmsDiscussMgr::XmpuBasCB. AssignBas Fail!  ConfID:%d, EqpID:%d, ScreenIndex:%d, bSuccess:%d\n", 
				pInst->GetInsID(), ptBasRes->GetBasEqpId(), wScreen, tStartBastNty.m_bSuccess));
		} else
		{
			ptBasRes->m_tXmpuBas.m_emStat = EmXmpuResStatInfo_Running;
			pInst->GetBas()->SetXmpuVidBasAssignAddr(&ptBasRes->m_tXmpuBas, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);
			CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, &ptBasRes->m_tXmpuBas);

			TUmsVidFormat tVidFormat;
			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
			tVidFormat.m_emRes = emTPV480x272;
			tVidFormat.m_wFrameRate = 15;
			pInst->GetBas()->AdjustScreenBas(ptBasRes, ptBasRes->m_wSrcEp, wScreen, 1, &tVidFormat);
		}
		
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		// CNetPortMgr::AdjustDiscussEpToBas(pInst, ptEpInfo);

	} else if (dwType == evXmpu_AskBasKey_Req)
	{
		if ( wScreen < TP_MAX_STREAMNUM && ptEpInfo->m_awGetIndex[wScreen] < TP_UMS_MAX_CALLNUM )
		{
			pInst->GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[wScreen]);
		}
			
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
		bError = TRUE;
		MdlError(Ums_Mdl_Call, ("CUmsDiscussMgr::XmpuBasCB. ABasDisConnect!  ConfID:%d, EqpID:%d, ScreenIndex:%d\n", 
			pInst->GetInsID(), ptBasRes->GetBasEqpId(), wScreen));
	}
	
	if (bError)
	{
		u16 wIndex = 0;

		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (NULL != ptEpInfo->m_apcBas[wIndex] && ptBasRes == ptEpInfo->m_apcBas[wIndex])
			{	
				pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wIndex]);
				ptEpInfo->m_apcBas[wIndex] = NULL;
				
				if (ptEpInfo->m_bMtAdjustRes && emTPVResEnd == ptEpInfo->m_aemVideoRes[wIndex])
				{// 降分辨率，进小画面
					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wIndex, emTPV480x272);
					ptEpInfo->m_aemVideoRes[wIndex] = emTPV480x272;
				}
				break;
			}
		}
		
		CNetPortMgr::AdjustDiscussEpToBas(pInst, ptEpInfo);
		
		// 需要刷新进合成器的交换
		UmsDiscussOprCycle(wIndex, emDiscussObjEnd,
			m_apcDisObj[(EmDiscussModleObj)wIndex]->UptateDstVidToVmpTp(&m_tDiscussInfo));
	}

	return;
}

void CUmsDiscussMgr::XmpuBasCBForSingle(u32 dwType, CScreenBasRes* ptBasRes, void *pData)
{
	CUmsConfInst* pInst = Inst();
	if (ptBasRes != pInst->GetSpeaker().m_pcSingleBas)
	{
		return;
	}
	
	TXmpuStartBasNty tStartBastNty;
	BOOL32 bError = FALSE;
	if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		memcpy(&tStartBastNty, pData, sizeof(tStartBastNty));  
		if (!tStartBastNty.m_bSuccess)
		{
			bError = TRUE;
			MdlError(Ums_Mdl_Call, ("CUmsDiscussMgr::XmpuBasCBForSingle. AssignBas Fail!  ConfID:%d, EqpID:%d, bSuccess:%d\n", 
				pInst->GetInsID(), ptBasRes->GetBasEqpId(),  tStartBastNty.m_bSuccess));
		} else
		{
			ptBasRes->m_tXmpuBas.m_emStat = EmXmpuResStatInfo_Running;
			pInst->GetBas()->SetXmpuVidBasAssignAddr(&ptBasRes->m_tXmpuBas, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);			
	    	CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, &ptBasRes->m_tXmpuBas);
			pInst->TryAdjustVirSingleBas();
		}
		
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		// CNetPortMgr::CreateVirSpeakerToBas(pInst);
		
	} else if (dwType == evXmpu_AskBasKey_Req)
	{
		if (pInst->IsChairConf())
		{
			AskKeyFrameToVmp(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
		}
		else
		{
			TDisAskKeyFrame tDis;
			tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 2; //  下级向上级的单屏广播合成请求关键帧 
			tDis.m_bReqBySys = FALSE;
			tDis.m_wScreenNo = MIDSCREENINDEX;
			
			TUmsHandle tOutHandle;
			pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));
		}
		
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
		bError = TRUE;
		MdlError(Ums_Mdl_Call, ("CUmsDiscussMgr::XmpuBasCBForSingle. BasDisConnect!  ConfID:%d, EqpID:%d\n", 
			pInst->GetInsID(), ptBasRes->GetBasEqpId()));
	}
	
	if (bError)
	{
		if (pInst->IsChairConf()) 
		{
			pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_BasError, pInst->chairID());
			StopDiscussModle(TRUE, FALSE);
			DiscussInfoNotify();
			m_pcConf->GetVmp()->StopSpeakerVmp();
		}
		else
		{// 下级，释放此适配资源
			pInst->GetBas()->ReleaseScreenBas(pInst->GetSpeaker().m_pcSingleBas);
			pInst->GetSpeaker().m_pcSingleBas = NULL;
			
			//无资源后，下级单屏尝试看三屏目标的坐席 或中间屏
			m_pcConf->GetVmp()->StopSpeakerVmp();
		}
	}

	return;
}

#else

void CUmsDiscussMgr::BasCB( CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes )
{//BasCB
	if (NULL == ptBasRes)
	{
		return;
	}

	CUmsConfInst* pInst = Inst();
	MdlLowDtl(Ums_Mdl_Call, ("[BasCB] ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, CBType:%d, ScrEp:%d, ScreenIndex:%d\n", 
		pInst->GetInsID(), ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
		ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, emType, ptBasRes->m_wSrcEp, ptBasRes->m_wSrcScreenIndx));
	
	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(ptBasRes->m_wSrcEp);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{
		return;
	}
	TCallNode* ptNode = pInst->GetNode(ptEpInfo->m_wEpID);
	if (NULL == ptNode)
	{
		return;
	}

	if ( CScreenBasRes::VidBasCB_AskKey != emType)
	{// 出现异常

		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (NULL != ptEpInfo->m_apcBas[wIndex] && ptBasRes == ptEpInfo->m_apcBas[wIndex])
			{	
				pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wIndex]);
				ptEpInfo->m_apcBas[wIndex] = NULL;

				// 再尝试申请
				if (pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wIndex]))
				{// 分配到适配了
					ptEpInfo->m_apcBas[wIndex]->SetCB(DiscussBasCB, this);
					// 调整后适配格式
					TUmsVidFormat tVidFormat;
					tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
					tVidFormat.m_emRes = emTPV480x272;
					tVidFormat.m_wFrameRate = 15;
					pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wIndex], ptEpInfo->m_wEpID, wIndex, 1, &tVidFormat);
				}
				else
				{
					if (ptEpInfo->m_bMtAdjustRes && emTPVResEnd == ptEpInfo->m_aemVideoRes[wIndex])
					{// 降分辨率，进小画面
						pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wIndex, emTPV480x272);
						ptEpInfo->m_aemVideoRes[wIndex] = emTPV480x272;
					}
				}
				break;
			}
		}

		// 
		CNetPortMgr::AdjustDiscussEpToBas(pInst, ptEpInfo);

		// 需要刷新进合成器的交换
		UmsDiscussOprCycle(wIndex, emDiscussObjEnd,
			m_apcDisObj[(EmDiscussModleObj)wIndex]->UptateDstVidToVmpTp(&m_tDiscussInfo));
	}
	else
	{// 向会场对应屏请求关键帧
		u16 wSeatIndex = ptBasRes->m_wSrcScreenIndx;
		if ( wSeatIndex < TP_MAX_STREAMNUM && ptEpInfo->m_awGetIndex[wSeatIndex] < TP_UMS_MAX_CALLNUM )
		{
			pInst->GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[wSeatIndex]);
		}
	}
	
	return;
}

void CUmsDiscussMgr::BasCBForSingle( CScreenBasRes::VidBasCBType emType, CScreenBasRes* ptBasRes )
{
	CUmsConfInst* pInst = Inst();
	if (ptBasRes != pInst->GetSpeaker().m_pcSingleBas)
	{
		return;
	}

	if ( CScreenBasRes::VidBasCB_AskKey != emType)
	{
		MdlError(Ums_Mdl_Call, ("[BasCBForSingle] ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, CBType:%d, ScrEp:%d\n", 
			pInst->GetInsID(), ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
			ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, emType, ptBasRes->m_wSrcEp));
		if (pInst->IsChairConf()) 
		{
			pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_Discuss_StopByUms_BasError, pInst->chairID());
			StopDiscussModle(TRUE, FALSE);
			DiscussInfoNotify();
			m_pcConf->GetVmp()->StopSpeakerVmp();
		}
		else
		{// 下级，释放此适配资源
			pInst->GetBas()->ReleaseScreenBas(pInst->GetSpeaker().m_pcSingleBas);
			pInst->GetSpeaker().m_pcSingleBas = NULL;

			//无资源后，下级单屏尝试看三屏目标的坐席 或中间屏
			m_pcConf->GetVmp()->StopSpeakerVmp();
		}
		return;
	}
	
	MdlLowDtl(Ums_Mdl_Call, ("[BasCBForSingle] ConfID:%d, BasEqpID:%d, BasEqpChnlIndx:%d, CBType:%d, ScrEp:%d\n", 
		pInst->GetInsID(), ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
		ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, emType, ptBasRes->m_wSrcEp));

	if (pInst->IsChairConf())
	{
		AskKeyFrameToVmp(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
	}
	else
	{
		TDisAskKeyFrame tDis;
		tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 2; //  下级向上级的单屏广播合成请求关键帧 
		tDis.m_bReqBySys = FALSE;
		tDis.m_wScreenNo = MIDSCREENINDEX;
		
		TUmsHandle tOutHandle;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));
	}

	return;
}
#endif

void CUmsDiscussMgr::GetDiscussEpSmallVidAddr(u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr)
{
	// 清空
	tAddr.Clear();

	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEpId);
	TCapNode*  ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("[GetDiscussEpSmallVidToVmp] FineNode Error! ConfID:%d, Ep:%d, Screen:%d\n", 
			pInst->GetInsID(), wEpId, wScreenIndex));
		return;
	}
	
	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(wEpId);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{
		return;
	}
	
	if (ptEpInfo->m_bIsSmallChanOn)
	{
		tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tGetAddr.m_atSmallAddr[wScreenIndex].m_tRtpAddr;
		tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tGetAddr.m_atSmallAddr[wScreenIndex].m_tBackRtcpAddr;
		tAddr.m_dwMediaNode = ptEpInfo->m_tGetAddr.m_dwMedia;
	}
	else
	{ // 没有小码流, 尝试从适配中取小码流
		if (NULL != ptEpInfo->m_apcBas[wScreenIndex])
		{
			TTPMediaTransAddr tBasOutAddr;
			TUmsVidFormat tVidFormat;
			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
			tVidFormat.m_emRes = emTPV480x272;
			tVidFormat.m_wFrameRate = 15;
			pInst->GetBas()->GetOutChnVidAddr(tBasOutAddr, ptEpInfo->m_apcBas[wScreenIndex], tVidFormat);
			
			tAddr.m_tAddr.m_tRtpAddr = tBasOutAddr.m_tRtpAddr;
			tAddr.m_tAddr.m_tBackRtcpAddr = tBasOutAddr.m_tBackRtcpAddr;
			tAddr.m_dwMediaNode = pInst->GetConfEqpDs().m_dwEqpNode;
		}
		else
		{
			if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wScreenIndex])
			{// 如果终端降了分辨率，则从主流取
				tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tGetAddr.m_atVidAddr[wScreenIndex].m_tRtpAddr;
				tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tGetAddr.m_atVidAddr[wScreenIndex].m_tBackRtcpAddr;
				tAddr.m_dwMediaNode = ptEpInfo->m_tGetAddr.m_dwMedia;
			}
		}
	}
	return;
}

void CUmsDiscussMgr::GetDiscussEpVidAddr( u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr )
{
	// 清空
	tAddr.Clear();

	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEpId);
	TCapNode*  ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("[GetDiscussEpVidAddr] FineNode Error! ConfID:%d, Ep:%d, Screen:%d\n", 
			pInst->GetInsID(), wEpId, wScreenIndex));
		return;
	}
	
	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(wEpId);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{
		MdlError(Ums_Mdl_Call, ("[GetDiscussEpVidAddr] FineEPInfo Error! ConfID:%d, Ep:%d, Screen:%d\n", 
			pInst->GetInsID(), wEpId, wScreenIndex));
		return;
	}
	
	tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tGetAddr.m_atVidAddr[wScreenIndex].m_tRtpAddr;
	tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tGetAddr.m_atVidAddr[wScreenIndex].m_tBackRtcpAddr;
	tAddr.m_dwMediaNode = ptEpInfo->m_tGetAddr.m_dwMedia;
	
	return;
}

void CUmsDiscussMgr::GetDiscussEpAudAddr( u16 wEpId, u16 wScreenIndex, TServiceAddr& tAddr )
{
	// 清空
	tAddr.Clear();

	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEpId);
	TCapNode*  ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("[GetDiscussEpAudAddr] FineNode Error! ConfID:%d, Ep:%d, Screen:%d\n", 
			pInst->GetInsID(), wEpId, wScreenIndex));
		return;
	}
	
	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(wEpId);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{
		MdlError(Ums_Mdl_Call, ("[GetDiscussEpAudAddr] FineEpInfo Error! ConfID:%d, Ep:%d, Screen:%d\n", 
			pInst->GetInsID(), wEpId, wScreenIndex));
		return;
	}
	
	if (wScreenIndex < TP_MAX_STREAMNUM)
	{
		tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tGetAddr.m_atAudAddr[wScreenIndex].m_tRtpAddr;
		tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tGetAddr.m_atAudAddr[wScreenIndex].m_tBackRtcpAddr;
		tAddr.m_dwMediaNode = ptEpInfo->m_tGetAddr.m_dwMedia;
	}
	else if (ptEpInfo->IsSingleScr())
	{// 单屏会场没有混音
		tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tGetAddr.m_atAudAddr[MIDSCREENINDEX].m_tRtpAddr;
		tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tGetAddr.m_atAudAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
		tAddr.m_dwMediaNode = ptEpInfo->m_tGetAddr.m_dwMedia;
	}
	else
	{// 尝试打混音
		tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tGetAddr.m_tMixAddr.m_tRtpAddr;
		tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tGetAddr.m_tMixAddr.m_tBackRtcpAddr;
		tAddr.m_dwMediaNode = ptEpInfo->m_tGetAddr.m_dwMedia;
	}
	
	return;
}

void CUmsDiscussMgr::GetObjVmpOutAddr( EmDiscussModleObj emType, u16 wScreenIndex, TServiceAddr& tAddr )
{
	tAddr.Clear();

	const CBaseService* pVmpRes = GetObjVmpRes(emType, wScreenIndex);
	if (NULL == pVmpRes)
	{
		return;
	}
	Inst()->GetVmpServiceHandle()->GetSndChanAddr(tAddr, pVmpRes);
	return;
}

void CUmsDiscussMgr::GetObjMixOutAddr(EmDiscussModleObj emType, u16 wScreenindex, u16 wEpId, BOOL32 bToVirSpeaker, TServiceAddr& tAddr, BOOL32 bFromPutAud /* = FALSE */)
{ // wScreenIndex为0 1 2时，对应三屏的各个屏，为3时，对应混音
	tAddr.Clear();

	CUmsConfInst* pInst = Inst();
	TAudMixInfo* pMixRes = GetObjMixRes(emType, wScreenindex); // wScreenindex在emType为emDiscussObjForSingleScrEp，取资源时忽略
	if (NULL == pMixRes) 
	{
		return;
	}
	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(wEpId);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{
		return;
	}
	
	if (bToVirSpeaker)
	{
		pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptFatherNode->m_tAudSndFormat.m_tFormat);
		return;
	}

	if (!ptNode->IsInMix())
	{// 不在讨论中的会场需要取n模式
		if (bFromPutAud)
		{// 通过putaud下去，为下级的讨论会场取码流，只能打下去n-1，格式才能匹配
			pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptNode->m_tAudRcvFormat.m_tFormat);
			return;
		}
		pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptFatherNode->m_tAudRcvFormat.m_tFormat);
		return;
	}
	
	if (TP_INVALID_INDEX != pMixRes->GetIndx(wEpId, wScreenindex))
	{
		if (!bFromPutAud && ptNode != ptFatherNode)
		{// 不走putaud下去，为下级的讨论会场（发言会场）取码流，只取n模式（按照级联格式，下级占用适配）
			return;
		}
		pInst->GetEapu()->GetMixerChnOutAddr(pMixRes, tAddr, wEpId, wScreenindex);
	}
	else if (ptNode->IsThreeVidSnd() && TP_INVALID_INDEX != pMixRes->GetIndx(wEpId, TP_MAX_STREAMNUM))
	{// 三屏会场可能只有相应屏进mix，也可能直接用混音进mix
		if (!bFromPutAud && ptNode != ptFatherNode)
		{// 不走putaud下去，为下级的讨论会场（发言会场）取码流，只取n模式（按照级联格式，下级占用适配）
			return;
		}
		pInst->GetEapu()->GetMixerChnOutAddr(pMixRes, tAddr, wEpId, TP_MAX_STREAMNUM);
	}
	else 
	{// 取n模式

		if (bFromPutAud)
		{// 通过putaud下去，为下级的讨论会场取码流，只能打下去n-1，格式才能匹配
			pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptNode->m_tAudRcvFormat.m_tFormat);
			return;
		}
		pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptFatherNode->m_tAudRcvFormat.m_tFormat);
	}

	return;
}

void CUmsDiscussMgr::AskKeyFrameFromEp( TCapNode* ptNode, u16 wScreenIndex, BOOL32 bReqBySys )
{// 会场请求关键帧
	CUmsConfInst* pInst = Inst();

	if (pInst->IsChairConf())
	{
		AskKeyFrameToVmpByNode(ptNode, (TCallNode*)ptNode, wScreenIndex, bReqBySys);
	}
	else
	{
		BOOL32 bFlag = IsSpeacialEp(ptNode->m_wEpID);
		if (!bFlag && pInst->curSpeakerID() != ptNode->m_wEpID)
		{// 下级会场如果收的是广播码流，尝试先向本级适配请求关键帧
			if (ptNode->IsThreeVidRcv())
			{//三屏目标
				if (pInst->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat))
				{// 向适配请求
					pInst->GetBas()->SeeSpeakerAskFrameToBas(wScreenIndex);
					return;
				}
			}
			else
			{//单屏目标
				if (m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat))
				{// 向单屏广播适配请求
					if (NULL != pInst->GetSpeaker().m_pcSingleBas)
					{
						pInst->GetBas()->AskFrameToScreenBas(pInst->GetSpeaker().m_pcSingleBas);
					}
					else
					{
						u16 wSeatIndex = MIDSCREENINDEX;
						pInst->GetBas()->SeeSpeakerAskFrameToBas(wSeatIndex);
					}
					return;
				}
			}
		}

		// 向上级请求
		TDisAskKeyFrame tDis;
		tDis.m_wEpID = ptNode->m_wEpID; // 下级会场的id
		tDis.m_bReqBySys = bReqBySys;
		tDis.m_wScreenNo = wScreenIndex;
		
		TUmsHandle tOutHandle;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));	
	}

	return;
}

void CUmsDiscussMgr::AskKeyFrameFromBas( u16 wScreenIndex )
{// 讨论下，广播三屏的码流从合成器打入发言人适配中。。。
	CUmsConfInst* pInst = Inst();
	if (pInst->IsChairConf())
	{
		AskKeyFrameToVmp(emDiscussObjForThreeScrEp, wScreenIndex);
	}
	else
	{// 向上级请求

		TDisAskKeyFrame tDis;
		tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 1; //  下级向上级的三屏广播合成请求关键帧 
		tDis.m_bReqBySys = FALSE;
		tDis.m_wScreenNo = wScreenIndex;
		
		TUmsHandle tOutHandle;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));
	}
	return;
}

void  CUmsDiscussMgr::AskKeyFrameForConfBrdUser(u16 wScreenIndex)
{
    CUmsConfInst* pInst = Inst();

    // 0,1,2 代表三屏中的 左，中，右，3 代表合成的单屏，4代表所有视频

    if (wScreenIndex > TP_MAX_STREAMNUM + 1)
	{
        return;
	}

	u16 wOprScreenIndex = wScreenIndex;
	if (wScreenIndex == TP_MAX_STREAMNUM + 1)
	{
         wOprScreenIndex = MIDSCREENINDEX;
	}

    if (wScreenIndex < TP_MAX_STREAMNUM || wScreenIndex == TP_MAX_STREAMNUM + 1)
	 { //三屏

		 if (pInst->IsChairConf())
		 {
			 AskKeyFrameToVmp(emDiscussObjForThreeScrEp, wOprScreenIndex);
		 }
		 else
		 {// 向上级请求
			 
			 TDisAskKeyFrame tDis;
			 tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 1; //  下级向上级的三屏广播合成请求关键帧 
			 tDis.m_bReqBySys = FALSE;
			 tDis.m_wScreenNo = wOprScreenIndex;
			 
			 TUmsHandle tOutHandle;
			 pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			 UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));
		 }

	 } 


     if (TP_MAX_STREAMNUM == wScreenIndex || wScreenIndex == TP_MAX_STREAMNUM + 1)
	 { //单屏 
		 if (pInst->IsChairConf())
		 {
			 AskKeyFrameToVmp(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
		 }
		 else
		 {
			 TDisAskKeyFrame tDis;
			 tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 2; //  下级向上级的单屏广播合成请求关键帧 
			 tDis.m_bReqBySys = FALSE;
			 tDis.m_wScreenNo = MIDSCREENINDEX;
			 
			 TUmsHandle tOutHandle;
			 pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			 UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));
		 }
	 } 
	 
	 return;
}



// 开启或关闭讨论、非讨论下，更新讨论列表成员
void CUmsDiscussMgr::OnDiscussStatusCmd( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TConfAuxMixInfo tAudMix;
	TP_SAFE_CAST( tAudMix, ptMsg->GetBody()+sizeof(TUmsHandle));

	if ( !CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
	{
		return ;
	}
	
	MdlHint(Ums_Mdl_Call, ("[OnDiscussStatusCmd] ConfID:%d, CmdStart:%d, CurrentDisStat:%d\n", 
		pInst->GetInsID(), tAudMix.m_bStart, m_bUIDiscussStatus));

	DiscussStatusCmdFromUmcCnc(tAudMix, EmUI_CNC);

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UmsConfAMixUpdate_Ind, &tAudMix, sizeof(TConfAuxMixInfo));

	DiscussInfoNotify();

	return;
}

EmDiscussRspRet CUmsDiscussMgr::OnDiscussStatusCmdFromUmc( CTpMsg* const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TConfAuxMixInfo tAudMix;
	TP_SAFE_CAST( tAudMix, ptMsg->GetBody()+sizeof(TLogUser));
	
	if (!pInst->IsChairConf())
	{
		tAudMix.m_emRet = em_Start_OtherFail;
		pInst->NotifyMsgToServiceForUI(evtp_StartAuxMix_ind, &tAudMix, sizeof(TConfAuxMixInfo), &tLogUser);
		return tAudMix.m_emRet;
	}
	
	MdlHint(Ums_Mdl_Call, ("[OnDiscussStatusCmdFromUmc] ConfID:%d, CmdStart:%d, CurrentDisStat:%d\n", 
		pInst->GetInsID(), tAudMix.m_bStart, m_bUIDiscussStatus));
	
	DiscussStatusCmdFromUmcCnc(tAudMix, EmUI_UMC);

	DiscussInfoNotify();

	pInst->NotifyMsgToServiceForUI(evtp_StartAuxMix_ind, &tAudMix, sizeof(TConfAuxMixInfo), &tLogUser);
	
	return tAudMix.m_emRet;
}

void CUmsDiscussMgr::DiscussStatusCmdFromUmcCnc(TConfAuxMixInfo& tAudMix, EmUIType emType)
{
	CUmsConfInst* pInst = Inst();
	
	tAudMix.m_emRet = em_DiscussOprRsp_Ok;
	
	if (tAudMix.m_bStart)
	{
		if (pInst->GetRollCallMgr()->IsUIRollCallOn())
		{
			tAudMix.m_emRet = em_Start_RollCall_Mode;
		    return;
		}

		if (pInst->GetAudMix()->IsAudMixMode())
		{
			tAudMix.m_emRet = em_Start_ConfAudMix_Mode;
		    return;
		}
	}

	if (!tAudMix.m_bStart && !m_bUIDiscussStatus)
	{// 讨论未开启，cmd更新讨论成员列表
		
		UptateDiscussListFromUI(tAudMix.m_atAuxMixList);
	}
	else if (tAudMix.m_bStart && !m_bUIDiscussStatus)
	{// 讨论未开启，cmd开启讨论, 先更新下讨论成员列表
		
		if (tAudMix.m_atAuxMixList.GetMixNum() == 0)
		{// 讨论成员为空，自动把发言会场加进讨论
			tAudMix.m_atAuxMixList.AddMixID(pInst->curSpeakerID());
		}

		UptateDiscussListFromUI(tAudMix.m_atAuxMixList);
		
		tAudMix.m_emRet = AssignResource();// 资源申请
		if (em_DiscussOprRsp_Ok != tAudMix.m_emRet)
		{
			return;
		}
		
		// 语音激励是否开启
		AdjustAudMixVacStatus(tAudMix.m_bVacOn);
		
		if (StartDiscussModle(emType))
		{
		//	pInst->GetPollMgr()->TrySuspendPoll();
			AdjustDiscussStatus(EmDisChnAllStart);
		}
		else
		{
			ResetDiscussInfo();
			tAudMix.m_emRet = em_Start_OtherFail;
		}
	}
	else if (!tAudMix.m_bStart && m_bUIDiscussStatus)
	{// 讨论已经开启，cmd关闭讨论
	
		//UptateDiscussListFromUI(tAudMix.m_atAuxMixList);
		StopDiscussModle();
		m_bUIVacOn = tAudMix.m_bVacOn;
	}
	else
	{// 讨论已经开启，更新列表
		if (tAudMix.m_atAuxMixList.GetMixNum() == 0)
		{// 讨论成员为空，自动把发言会场加进讨论
			tAudMix.m_atAuxMixList.AddMixID(pInst->curSpeakerID());
		}
		UptateDiscussListFromUI(tAudMix.m_atAuxMixList);

		if (UpdateDiscussModle(emType))
		{
			AdjustDiscussStatus(EmDisChnAllStart);
		}
		else
		{
			StopDiscussModle();
			tAudMix.m_emRet = em_Start_OtherFail;
		}		
	}
	
	return;
}

// 讨论下，增加和删除会场
void CUmsDiscussMgr::OnDiscussListOprCmd( CTpMsg *const ptMsg )
{		
	CUmsConfInst* pInst = Inst();

	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TDiscussListOpr tDisList;
	TP_SAFE_CAST( tDisList, ptMsg->GetBody()+sizeof(TUmsHandle));

	if (!CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[OnUmsDisListOprCmd] ConfID:%d, EpNum:%d, OprType:%d (0-add, 1-del), CurrentDisStat:%d\n", 
		pInst->GetInsID(), tDisList.m_wNum, tDisList.m_emOprType, m_bUIDiscussStatus));

	DiscussListOprFormUmcCnc(tDisList, EmUI_CNC);

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UmsAudMixDisListOpr_Ind, &tDisList, sizeof(TDiscussListOpr));

	DiscussInfoNotify();
	return;
}

void CUmsDiscussMgr::OnDiscussListOprFromUmc( CTpMsg* const ptMsg )
{
	CUmsConfInst*	pInst = Inst();
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TDiscussListOpr tDisList;
	TP_SAFE_CAST( tDisList, ptMsg->GetBody()+sizeof(TLogUser));

	if (!pInst->IsChairConf())
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[OnDiscussListOprFromUmc] ConfID:%d, EpNum:%d, OprType:%d (0-add, 1-del), CurrentDisStat:%d\n", 
		pInst->GetInsID(), tDisList.m_wNum, tDisList.m_emOprType, m_bUIDiscussStatus));

	DiscussListOprFormUmcCnc(tDisList, EmUI_UMC);

	DiscussInfoNotify();

	//回复umc 操作结果
	pInst->NotifyMsgToServiceForUI(evtp_UpdateAudMixInfo_Ind, &tDisList, sizeof(TDiscussListOpr), &tLogUser);

	return;
}

void CUmsDiscussMgr::DiscussListOprFormUmcCnc(TDiscussListOpr& tDisList, EmUIType emType)
{
	CUmsConfInst* pInst = Inst();

	tDisList.ResetOprRes();

	if (!m_bUIDiscussStatus)
	{// 非讨论下，添加和删除会场，走另一条信令
		MdlError(Ums_Mdl_Call, ("[DiscussListOprFormUmcCnc] Now is not Discuss status! ConfID:%d\n", 
			pInst->GetInsID()));
		return;
	}
	
	if (0 == tDisList.m_wNum)
	{
		MdlError(Ums_Mdl_Call, ("[DiscussListOprFormUmcCnc] Opr Ep num is 0! ConfID:%d, num:%d\n", 
			pInst->GetInsID(), tDisList.m_wNum));
		return;
	}

	u16 wIndex = 0;
	u16 wFailNum = 0;
	if (em_DisListOpr_Add == tDisList.m_emOprType)
	{
		for (wIndex = 0; wIndex < tDisList.m_wNum; wIndex++)
		{
			tDisList.m_aemRet[wIndex] = AddEpInListFormUI(tDisList.m_awEpId[wIndex]);
			if (em_Disucss_Opr_Successed != tDisList.m_aemRet[wIndex])
			{// 添加失败
				wFailNum++;
			}
		}
		
		if (wFailNum == tDisList.m_wNum)
		{// 全失败了，返回
			MdlError(Ums_Mdl_Call, ("[DiscussListOprFormUmcCnc] Add Ep All Fail! ConfID:%d, num:%d\n", 
				pInst->GetInsID(), tDisList.m_wNum));
			return;
		}

		// to do 更新目标
		AdjustDiscussStatus(EmDisChnAddEp);
	}		
	else if (em_DisListOpr_Del == tDisList.m_emOprType)
	{
		// 删除
		TDiscussEpInfo* ptEpInfo = NULL;
		for (wIndex = 0; wIndex < tDisList.m_wNum; wIndex++)
		{
			ptEpInfo = m_tDiscussInfo.FindEpById(tDisList.m_awEpId[wIndex]);
			if (NULL != ptEpInfo)
			{
				RemoveEpFromDiscussChan(ptEpInfo);
				tDisList.m_aemRet[wIndex] = em_Disucss_Opr_Successed;
			}
			else
			{
				MdlError(Ums_Mdl_Call, ("[DiscussListOprFormUmcCnc] Ep is not in Dis For Del! ConfId:%d, EpId:%d\n",
					pInst->GetInsID(), tDisList.m_awEpId[wIndex]));
			}
		}

		if (0 == m_tDiscussInfo.m_wTotalScreenNum)
		{
			StopDiscussModle();
		}
		else
		{
			// to do 更新目标
			AdjustDiscussStatus(EmDisChnDelEp);
		}
		
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("[OnUmsDisListOprCmd] OprType InValid. ConfID:%d\n", pInst->GetInsID()));
	}

	return;
}

void CUmsDiscussMgr::OnDiscussMixVacOprCmd( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle tHandle;
	TP_SAFE_CAST( tHandle, ptMsg->GetBody());
	TConfAuxMixVacOpr tVacOpr;
	TP_SAFE_CAST( tVacOpr, ptMsg->GetBody()+sizeof(TUmsHandle));

	if (!CheckMsgFromChair(pInst, tHandle.GetEpID()) || !pInst->IsChairConf())
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[OnDiscussMixVacOprCmd] ConfID:%d, bVac:%d, CurrentVacStat:%d, CurrentDisStat:%d\n", 
		pInst->GetInsID(), tVacOpr.m_bVacOn, m_bUIVacOn, m_bUIDiscussStatus));
	
	DiscussMixVacOprFormUmcCnc(tVacOpr);

	TUmsHandle tOutHandle;
	pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, tHandle.GetEpID());
	UmsSendConfCtrl(tOutHandle, ev_UmsConfAMixVacSwitchInd, &tVacOpr, sizeof(TConfAuxMixVacOpr));
	
	DiscussInfoNotify();

	return;
}

void CUmsDiscussMgr::OnDiscussMixVacOprCmdFromUmc( CTpMsg *const ptMsg )
{
	CUmsConfInst*	pInst = Inst();
	TLogUser tLogUser;
	TP_SAFE_CAST( tLogUser, ptMsg->GetBody());
	TConfAuxMixVacOpr tVacOpr;
	TP_SAFE_CAST( tVacOpr, ptMsg->GetBody()+sizeof(TLogUser));
	
	if (!pInst->IsChairConf())
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[OnDiscussMixVacOprCmdFromUmc] ConfID:%d, bVac:%d, CurrentVacStat:%d, CurrentDisStat:%d\n", 
		pInst->GetInsID(), tVacOpr.m_bVacOn, m_bUIVacOn, m_bUIDiscussStatus));
	
	DiscussMixVacOprFormUmcCnc(tVacOpr);
	
	DiscussInfoNotify();

	//回复umc 操作结果
	pInst->NotifyMsgToServiceForUI(ev_AuxMixVacSwitchInd, &tVacOpr, sizeof(TConfAuxMixVacOpr), &tLogUser);

	return;
}

void CUmsDiscussMgr::DiscussMixVacOprFormUmcCnc(TConfAuxMixVacOpr& tVacOpr)
{
	CUmsConfInst* pInst = Inst();
	tVacOpr.m_wOprRet = TP_RET_OK;
	
	if (tVacOpr.m_bVacOn != m_bUIVacOn)
	{// 改变语音激励状态
		if (m_bUIDiscussStatus)
		{
			if (!AdjustAudMixVacStatus(tVacOpr.m_bVacOn))
			{
				tVacOpr.m_wOprRet = TP_RET_ERROR;
				MdlError(Ums_Mdl_Call, ("[DiscussMixVacOprFormUmcCnc] Opr Error!! ConfID:%d, bVac:%d, CurrentVacStat:%d, CurrentDisStat:%d\n", 
					pInst->GetInsID(), tVacOpr.m_bVacOn, m_bUIVacOn, m_bUIDiscussStatus));
			}
		}
		else
		{
			m_bUIVacOn = tVacOpr.m_bVacOn;
		}
	}
	else
	{
		tVacOpr.m_wOprRet = TP_RET_ERROR;
		MdlError(Ums_Mdl_Call, ("[DiscussMixVacOprFormUmcCnc] VacStat is not Changed!! ConfID:%d, bVac:%d, CurrentVacStat:%d, CurrentDisStat:%d\n", 
			pInst->GetInsID(), tVacOpr.m_bVacOn, m_bUIVacOn, m_bUIDiscussStatus));
	}

	return;
}

void CUmsDiscussMgr::OpenEpDownAudCmd( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TVidChanCmd* ptVidCmd = (TVidChanCmd*)(ptMsg->GetBody() + sizeof(TUmsHandle));

	EmPutAudUser emUser = (EmPutAudUser)ptVidCmd->m_atUpRtp[1].m_tAddr.m_wPort;
	if (em_putauduser_discuss != emUser)
	{
		return;
	}

	TCallNode* ptNode = pInst->GetNodeMgr()->GetNode(ptVidCmd->m_tEpKey.m_wEpID);
	TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
	if (NULL == ptNode || NULL == ptFatherNode)
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[OpenEpDownAudCmd] ConfID:%d, wEpID:%d\n", pInst->GetInsID(), ptNode->m_wEpID));

	if (pInst->IsChairConf())
	{
		return;
	}

	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.AddEpID(ptNode);
	if (NULL == ptEpInfo)
	{
		MdlError(Ums_Mdl_Call, ("[OpenEpDownAudCmd] Ep Is Full. ConfID:%d, EpId:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
		return;
	}

	m_tDiscussInfo.AddEpChanInfo(ptNode, ptEpInfo->m_wIndex);
	ptNode->m_wMixIndex = ptEpInfo->m_wIndex;

	pInst->GetPutAudMgr()->GetAudLocalAddr(ptNode->m_wEpID, em_putauduser_discuss, ptEpInfo->m_atPutAuddr);

	return;
}

void CUmsDiscussMgr::OpenEpDownAudAck( CTpMsg *const ptMsg )
{
	if (Inst()->IsChairConf())
	{
		TUmsHandle tInHandle = *(TUmsHandle*)(ptMsg->GetBody());
		TVidChanAck tVidAck = *(TVidChanAck*)(ptMsg->GetBody() + sizeof(TUmsHandle));

		EmPutAudUser emUser = tVidAck.m_atUpBackRtcp[1].m_tAddr.m_wPort;
		if (em_putauduser_discuss != emUser)
		{
			return;
		}

		TCapNode* ptForeNode = Inst()->GetNodeMgr()->GetCapsetNode(tInHandle.GetEpID());
		if ( NULL == ptForeNode )
		{
			MdlError(Ums_Mdl_Call, ("[OpenEpDownAudAck] ptSrcCapNode is NULL . ConfID:%d, handleEpID:%d\n", Inst()->GetInsID(), tInHandle.GetEpID()));
			return ;
		}
		
		//不是本级结点，则取得该会场的本级EpID
		if ( ptForeNode->IsUms() )
		{
			TCallNode* ptNode = Inst()->GetNodeMgr()->GetNodeByChildEpID(ptForeNode, tVidAck.m_tEpKey.m_wEpID);
			if ( NULL == ptNode || !ptNode->m_bUsed )
			{
				MdlError(Ums_Mdl_Call, ("[OpenEpDownAudAck] ptNode is NULL . ConfID:%d, EpID:%d\n", Inst()->GetInsID(), tVidAck.m_tEpKey.m_wEpID));
				return ;
			}
			tVidAck.m_tEpKey.m_wEpID = ptNode->m_wEpID;
		}

		MdlHint(Ums_Mdl_Call, ("[OpenEpDownAudAck] ConfID:%d, wEpID:%d\n", Inst()->GetInsID(), tVidAck.m_tEpKey.m_wEpID));

		TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(tVidAck.m_tEpKey.m_wEpID);
		if (NULL != ptEpInfo && tVidAck.m_wReason != TP_RET_OK)
		{
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Discard_AddEp, Inst()->chairID(), ptEpInfo->m_wEpID, (u32)em_Discuss_AssignAudChan_Error);
			RemoveEpFromDiscussChan(ptEpInfo);

			if (m_tDiscussInfo.m_wTotalScreenNum == 0)
			{
				StopDiscussModle();
			}
			else
			{
				AdjustDiscussStatus(EmDisChnDelEp, ptEpInfo->m_wEpID);
			}

			DiscussInfoNotify();
		}
	}
	return;
}

void CUmsDiscussMgr::CloseEpDownAudCmd( CTpMsg *const ptMsg )
{
	u16 wEpID;
	u32	dwType;
	TP_SAFE_CAST( wEpID, ptMsg->GetBody() + sizeof(TUmsHandle));
	TP_SAFE_CAST( dwType, ptMsg->GetBody() + sizeof(TUmsHandle) + sizeof(u16));

	EmPutAudUser emUser = (EmPutAudUser)dwType;
	if (emUser != em_putauduser_discuss)
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[CloseEpDownAudCmd] ConfID:%d, wEpID:%d, user:%d.\n", Inst()->GetInsID(), wEpID, emUser));
	
	if (Inst()->IsChairConf())
	{
		return;
	}

	TCallNode* ptNode = Inst()->GetNodeMgr()->GetNode(wEpID);
	if (NULL == ptNode)
	{
		return;
	}

	ptNode->m_wMixIndex = TP_INVALID_INDEX;

	m_tDiscussInfo.DelEpById(wEpID);

	return;
}

void CUmsDiscussMgr::OnCasecadeDiscussNtfy( CTpMsg *const ptMsg )
{

	CUmsConfInst* pInst = Inst();

	TDiscussCasecadeNtfy tNtfy;	
	TP_SAFE_CAST(tNtfy, ptMsg->GetBody() + sizeof(TUmsHandle));

	MdlHint(Ums_Mdl_Call, ("[OnCasecadeDiscussNtfy] ConfID:%d, NtfyDiscussModle:%d, NowDiscussModle:%d, SpeacialEp:%d.\n",
		pInst->GetInsID(), tNtfy.m_bIsDiscussModle, m_bDiscussStaus, tNtfy.m_atDiscussObj[emDiscussObjForSpeakerEp].m_wReserve));

	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{	
		if (0 != tNtfy.m_tEpAudInfo.m_awDiscussEpId[wIndex])
		{
			MdlHint(Ums_Mdl_Call, ("  From Adapter... Ep:%d, (%d,%d,%d)\n", tNtfy.m_tEpAudInfo.m_awDiscussEpId[wIndex],
				tNtfy.m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][0], tNtfy.m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][1],
				tNtfy.m_tEpAudInfo.m_abyIsRcvNModeAud[wIndex][2]));
		}
	}

	if (pInst->IsChairConf())
	{
		return;
	}


	if (tNtfy.m_bIsDiscussModle)
	{// 上级通知下级进入讨论(包括调整)

		memcpy(m_atDiscussObj, tNtfy.m_atDiscussObj, sizeof(TDiscussObjInfo)*emDiscussObjEnd);
		memcpy(&m_tEpAudInfo, &tNtfy.m_tEpAudInfo, sizeof(TDiscussEpAudInfo));
		m_tDiscussInfo.SetSpecialEp(m_atDiscussObj[emDiscussObjForSpeakerEp].m_wReserve); 
		

		pInst->GetBas()->AdjustChairAudBas();
		pInst->GetBas()->AdjustSpeakerBas();

		if (m_bDiscussStaus)
		{// 调整
			pInst->TryAdjustVirSingleBas();

			AdjustAllNodeToDiscuss(TRUE);
		}
		else
		{
			// 尝试申请广播单屏适配
			pInst->TryAssignVirSingleBas();

			m_bDiscussStaus = TRUE;
			AdjustAllNodeToDiscuss(FALSE);
		}
	}
	else 
	{// 上级通知下级退出讨论

		pInst->GetBas()->AdjustChairAudBas();
		pInst->GetBas()->AdjustSpeakerBas();

		if(m_bDiscussStaus)
		{			
			UmsDiscussOprCycle(wIndex, emDiscussObjEnd, 
				m_atDiscussObj[(EmDiscussModleObj)wIndex].Clear());
			m_bDiscussStaus = FALSE;
			m_tDiscussInfo.Clear();
			m_tEpAudInfo.Clear();

			AdjustAllNodeToDiscuss(FALSE);
		}

		pInst->TryReleaseVirSingleBas();
	}	

	// 
	CNetPortMgr::CreateSpeakerToVirSpeaker(pInst);

	return;
}

void CUmsDiscussMgr::OnAskKeyFrameFromDown( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TUmsHandle& tHandle = *(TUmsHandle*)ptMsg->GetBody();
	TDisAskKeyFrame* ptDis = (TDisAskKeyFrame*)(ptMsg->GetBody() + sizeof(TUmsHandle));
	
	if (!m_bDiscussStaus)
	{//
		return ;
	}
	
	tpLowDtl(Ums_Mdl_Call, "OnAskKeyFrameFromDown. ConfID:%d, handleEpID:%d,SrcEp:%d, SrcScreenIndx:%d\n", 
		pInst->GetInsID(), tHandle.GetEpID(), ptDis->m_wEpID, ptDis->m_wScreenNo);
	
	u16 wEpID = TP_INVALID_INDEX;
	TCapNode* ptForeNode = pInst->m_pcNodeMgr->GetCapsetNode(tHandle.GetEpID());
	if ( NULL == ptForeNode || !ptForeNode->IsUms())
	{
		tpLowDtl(Ums_Mdl_Call, "OnAskKeyFrameFromDown ptSrcCapNode is NULL or is not Ums. ConfID:%d, EpID:%d, handleEpID:%d\n", 
			pInst->GetInsID(), ptDis->m_wEpID, tHandle.GetEpID());
		return ;
	}

	if (ptDis->m_wEpID == TP_CONF_MAX_CNSNUM + 1)
	{
		if (pInst->GetBas()->IsSpeakerNeedBas(ptForeNode->m_tVidRcvFormat.m_tFormat))
		{// 向适配请求
			pInst->GetBas()->SeeSpeakerAskFrameToBas(ptDis->m_wScreenNo);
		}
		else
		{
			AskKeyFrameToVmp(emDiscussObjForThreeScrEp, ptDis->m_wScreenNo);
		}
	}
	else if (ptDis->m_wEpID == TP_CONF_MAX_CNSNUM + 2)
	{
		if (m_pcConf->GetBas()->IsSpeakerNeedBas(ptForeNode->m_tVidRcvFormat.m_tFormat))
		{// 向适配请求
			pInst->GetBas()->AskFrameToScreenBas(pInst->GetSpeaker().m_pcSingleBas);
		}
		else
		{
			AskKeyFrameToVmp(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
		}
	}
	else
	{
		TCallNode* ptNode = pInst->m_pcNodeMgr->GetNodeByChildEpID(ptForeNode, ptDis->m_wEpID);
		if ( NULL == ptNode || !ptNode->m_bUsed )
		{
			tpLowDtl(Ums_Mdl_Call, "OnAskKeyFrameFromDown ptNode is NULL. ConfID:%d, EpID:%d\n", pInst->GetInsID(), ptDis->m_wEpID);
			return ;
		}

		AskKeyFrameToVmpByNode(ptForeNode, ptNode, ptDis->m_wScreenNo, ptDis->m_bReqBySys);
	}

	return;
}

BOOL32 CUmsDiscussMgr::StartDiscussModle(EmUIType emType)
{
	CUmsConfInst* pInst = Inst();

	UptateDiscussEpInfo();

	u16 wEpNum = m_tDiscussInfo.m_tDiscussEpFromUI.GetMixNum();
	if (wEpNum < 1)
	{
		MdlError(Ums_Mdl_Call, ("[StartUmsDisModle] Error! EpNum:%d, Conf:%d\n", m_tDiscussInfo.m_tDiscussEpFromUI.GetMixNum(),
			pInst->GetInsID()));
		return FALSE;
	}

	MdlHint(Ums_Mdl_Call, ("[StartUmsDisModle] Conf:%d\n", pInst->GetInsID()));
	
	m_bUIDiscussStatus = TRUE;

	u16 wIndex = 0;
	u16 wFailNum = 0;
	TDiscussEpInfo* pEpInfo = NULL;
	EmDiscussOprRes emOprRes;
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
	{
		pEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
		if (NULL == pEpInfo || !pEpInfo->m_bUsed)
		{
			continue;
		}

		emOprRes = AddEpInDiscussChan(pEpInfo);
		if (em_Disucss_Opr_Successed != emOprRes)
		{
			wFailNum++;

			// 提示进入讨论失败
			pInst->NotifyReasonToUI( emType, TP_UMS_Discard_AddEp, pInst->chairID(), pEpInfo->m_wEpID, (u32)emOprRes);
			RemoveEpFromDiscussChan(pEpInfo);
		}
	}

	if (wFailNum == wEpNum)
	{// 全失败了，讨论开始失败
		return FALSE;
	}

	return TRUE;
}

void CUmsDiscussMgr::StopDiscussModle(BOOL32 bVmpError /* = FALSE */, BOOL32 bMixError /* = FALSE */)
{
	CUmsConfInst* pInst = Inst();	
	
	if (!m_bUIDiscussStatus)
	{
		return;
	}

	MdlHint(Ums_Mdl_Call, ("[StopUmsDisModle] Conf:%d\n", Inst()->GetInsID()));

	for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
	{
		if (!m_tDiscussInfo.m_atDiscussEpInfo[wIndex].m_bUsed)
		{
			continue;
		}
		DelEpInDiscussChan(&m_tDiscussInfo.m_atDiscussEpInfo[wIndex]);
	}

	ResetDiscussInfo();

	pInst->GetBas()->AdjustSpeakerAudBas();
	pInst->GetBas()->AdjustChairAudBas();

	CNetPortMgr::CreateSpeakerToVirSpeaker(pInst);

	if (!bVmpError)
	{
		pInst->GetVmp()->AdjustSpeakerVmp(TRUE, FALSE);
	}
	
	if (!bMixError)
	{
		pInst->GetDualMgr()->AdjustDualMediaForDiscuss();
	}

	AdjustAllNodeToDiscuss(FALSE);

	return;
}

BOOL32 CUmsDiscussMgr::UpdateDiscussModle(EmUIType emType)
{
	CUmsConfInst* pInst = Inst();

	MdlHint(Ums_Mdl_Call, ("[UpdateDiscussModle] Conf:%d\n", pInst->GetInsID()));
	
	u16 wIndex = 0;
	TDiscussEpInfo* pEpInfo = NULL;
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
	{
		pEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
		if (NULL == pEpInfo || !pEpInfo->m_bUsed)
		{
			continue;
		}

		if (TP_INVALID_INDEX == m_tDiscussInfo.m_tDiscussEpFromUI.FindIndexByEp(pEpInfo->m_wEpID))
		{// 不在新的list中，删掉
			RemoveEpFromDiscussChan(pEpInfo);
		}
	}

	u16 wEpId = 0;
	TCallNode* ptNode =NULL;
	EmDiscussOprRes emOprRes = em_Disucss_Opr_Successed;
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
	{
		wEpId = m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex];
		if (wEpId == TP_INVALID_INDEX)
		{
			continue;
		}

		if (NULL == m_tDiscussInfo.FindEpById(wEpId))
		{// 不在list中，添加
			ptNode = pInst->GetNodeMgr()->GetNode(wEpId);
			if (NULL == ptNode || !ptNode->m_bUsed || ptNode->IsUms())
			{
				m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex] = TP_INVALID_INDEX;
				continue;
			}
			pEpInfo = m_tDiscussInfo.AddEpID(ptNode);
			if (NULL != pEpInfo)
			{
				emOprRes = AddEpInDiscussChan(pEpInfo);
				if (em_Disucss_Opr_Successed != emOprRes)
				{// 提示进入讨论失败
					pInst->NotifyReasonToUI( emType, TP_UMS_Discard_AddEp, pInst->chairID(), pEpInfo->m_wEpID, (u32)emOprRes);
					RemoveEpFromDiscussChan(pEpInfo);
				}
			}
			else
			{
				m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex] = TP_INVALID_INDEX;
			}
		}
	}

	if (0 == m_tDiscussInfo.m_wTotalScreenNum)
	{
		return FALSE;
	}

	return TRUE;
}

EmDiscussOprRes CUmsDiscussMgr::AddEpInListFormUI( u16 wEpId )
{
	CUmsConfInst* pInst = Inst();
	TDiscussEpInfo* ptEpInfo = NULL;
	
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(wEpId);
    TCapNode* ptNodeFar  = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if ( NULL == ptNode || NULL == ptNodeFar || !ptNode->m_bUsed 
		|| ptNode->IsUms() || !ptNode->IsChanOn() 
		|| (ptNodeFar->IsMcu() && ptNode!=ptNodeFar))
	{// 是否是有效会场
		MdlError(Ums_Mdl_Call, ("[AddEpInListFormUI] EpID InValid! ConfID:%d, EpID:%d\n", 
			pInst->GetInsID(), wEpId));
		return em_Discuss_Invalid_Ep;
	}
	
	if (!m_tDiscussInfo.m_tDiscussEpFromUI.AddMixID(wEpId))
	{// 添加会场，添加到最后
		MdlError(Ums_Mdl_Call, ("[AddEpInListFormUI] EpID Add Failed! ConfID:%d, EpID:%d\n", 
			pInst->GetInsID(), wEpId));
		return em_Discuss_OtherFail;
	}
	//
	ptEpInfo = m_tDiscussInfo.AddEpID(ptNode);
	if (NULL == ptEpInfo)
	{
		MdlError(Ums_Mdl_Call, ("[AddEpInListFormUI] list Is Full. ConfID:%d, EpId:%d\n", 
			pInst->GetInsID(), wEpId));
		return em_Discuss_OtherFail;
	}
	
	EmDiscussOprRes emOprRes = AddEpInDiscussChan(ptEpInfo);
	if (em_Disucss_Opr_Successed != emOprRes)
	{
		RemoveEpFromDiscussChan(ptEpInfo);
		
		MdlError(Ums_Mdl_Call, ("[AddEpInListFormUI] AddEpInDiscussChan Failed. ConfID:%d, EpId:%d\n", 
			pInst->GetInsID(), wEpId));
		return emOprRes;
	}
	
	MdlHint(Ums_Mdl_Call, ("[AddEpInListFormUI] success! ConfID:%d, EpId:%d\n", 
		pInst->GetInsID(), wEpId));
	
	return em_Disucss_Opr_Successed;
}

EmDiscussOprRes CUmsDiscussMgr::AddEpInDiscussChan( TDiscussEpInfo* ptEpInfo )
{
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(ptEpInfo->m_wEpID);
	TCapNode* ptForeFatherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if ( NULL == ptNode || NULL == ptForeFatherNode )
	{
		MdlError(Ums_Mdl_Call, ("[AddEpInDiscussChan] Failed! EpID:%d, ConfID:%d\n", 
			ptEpInfo->m_wEpID, pInst->GetInsID()));
		return em_Discuss_Invalid_Ep;
	}

	if (!ptNode->IsChanOn())
	{
		MdlHint(Ums_Mdl_Call, ("[AddEpInDiscussChan] Ep OffLine! ConfID:%d, EpID:%d\n", pInst->GetInsID(), ptEpInfo->m_wEpID));
		return em_Disucss_Opr_Successed;
	}

	if (ptNode->m_wVidSndNum + m_tDiscussInfo.m_wTotalScreenNum > TP_CONF_MAX_AUDMIXNUM)
	{
		MdlError(Ums_Mdl_Call, ("[AddEpInDiscussChan] Screen Num Is Full! ConfID:%d, EpID:%d, totalNum:%d, addNum:%d\n", 
			pInst->GetInsID(), ptNode->m_wEpID, m_tDiscussInfo.m_wTotalScreenNum, ptNode->m_wVidSndNum));
		
		return em_Discuss_Screen_Full;
	}

	m_tDiscussInfo.AddEpChanInfo(ptNode, ptEpInfo->m_wIndex);

	if (ptNode->IsVidSndValid())
	{// 上调码流（本级和上级都用）
		TCallVidFormat tFormat;
		TGetVidAddr tAddr;

		ptForeFatherNode->m_tRmtChan.ResetFastStatis();

		EmGetVidRes emRes = em_GetVid_Success;
		BOOL32 bError = FALSE;
		ForEachChanList(ptNode->m_wVidSndNum,
			emRes = CUmsConfInst::GetVidAudEx()->AssignByScreen(Inst(), ptNode->m_wEpID, ewIndex, em_GetVid_Dis, 
								tFormat, ptEpInfo->m_bIsSmallChanOn, tAddr, 
								ptEpInfo->m_awGetIndex[ewIndex]);\
			if ( em_GetVid_Success != emRes )\
			{\
			bError = TRUE;\
			break;\
			}\
			ptEpInfo->SetGetVidAddr(ewIndex, tAddr);
			CUmsConfInst::GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[ewIndex]);
			);
			
		if ( bError )
		{
			ForEachChanList(ptNode->m_wVidSndNum,
				if ( ptEpInfo->m_awGetIndex[ewIndex] < TP_UMS_MAX_CALLNUM )\
				{\
					CUmsConfInst::GetVidAudEx()->Release(Inst(), ptEpInfo->m_awGetIndex[ewIndex]);\
					ptEpInfo->m_awGetIndex[ewIndex] = TP_INVALID_INDEX;
				}\
				);

			memset(&ptEpInfo->m_tGetAddr, 0, sizeof(ptEpInfo->m_tGetAddr));

			MdlError(Ums_Mdl_Call, ("[AddEpInDiscussChan] GetVidAud Error! ConfID:%d, EpID:%d, Res:%d.\n", 
				pInst->GetInsID(), ptNode->m_wEpID, emRes));
				
			return em_GetVid_No_BandWidth == emRes ? em_Discuss_No_BandWith : em_Disccuss_GetVid_Error;
		}
	}
	
	if (ptNode != ptForeFatherNode && ptNode->IsAudRcvValid())
	{// 下级会场
		// 打开到下级的一路音频通道
        if (!pInst->GetPutAudMgr()->AssignAudChnl(ptNode->m_wEpID, em_putauduser_discuss, ptEpInfo->m_atPutAuddr))
		{
			MdlError(Ums_Mdl_Call, ("[AddEpInDiscussChan] AssignAudChnl Fail! ConfID:%d, EpID:%d\n", 
				pInst->GetInsID(), ptNode->m_wEpID));
			return em_Discuss_AssignAudChan_Error;
		}
	}
 
#ifndef Test_No_Res
	TAudMixInfo* pMixRes = GetObjMixRes(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
	if (NULL == pMixRes)
	{
		MdlError(Ums_Mdl_Call, ("[AddEpInDiscussChan] Find pMixRes Failed! EpID:%d, ConfID:%d\n", 
			ptEpInfo->m_wEpID, pInst->GetInsID()));
		//	RemoveEpFromDiscussChan(ptEpInfo);
		return em_Discuss_No_MixChan;
	}
	
	if (ptNode->IsVidSndValid() && pMixRes->IdleChanNum() < 1)
	{// 进讨论的终端发送通道不为0，需要校验下混音通道是否充足
		MdlError(Ums_Mdl_Call, ("[AddEpInDiscussChan] pMixRes is Full! EpID:%d, ConfID:%d\n", 
			ptEpInfo->m_wEpID, pInst->GetInsID()));
		
		return em_Discuss_No_MixChan;
	}

	// 会场的发送通道没有打开，不占用混音通道
	if (ptNode->IsVidSndValid() && ptNode->IsAudSndValid())
	{
		pInst->GetEapu()->AddMember(pMixRes, ptEpInfo->m_wEpID, TP_MAX_STREAMNUM);
	}
#endif

	// 用于识别此会场在讨论中
	ptNode->m_wMixIndex = ptEpInfo->m_wIndex;

	if (ptNode->m_wEpID == pInst->chairID())
	{
		m_tDiscussInfo.m_wChairEpId = ptNode->m_wEpID;
	}

	return em_Disucss_Opr_Successed;
}

void CUmsDiscussMgr::DelEpInDiscussChan( TDiscussEpInfo* ptEpInfo )
{
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = pInst->m_pcNodeMgr->GetNode(ptEpInfo->m_wEpID);
	TCapNode* ptForeFatherNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
	if ( NULL == ptNode || NULL == ptForeFatherNode)
	{
		MdlError(Ums_Mdl_Call, ("[DelEpInDiscussChan] Find Node Fail! EpID:%d, ConfID:%d\n", 
			ptEpInfo->m_wEpID, pInst->GetInsID()));
		return ;
	}

	if ( !ptNode->IsChanOn() )
	{
		MdlHint(Ums_Mdl_Call, ("[DelEpInDiscussChan] Ep OffLine! ConfID:%d, EpID:%d\n", pInst->GetInsID(), ptEpInfo->m_wEpID));
		return ;
	}

	if (ptNode->m_wEpID == pInst->chairID())
	{
		m_tDiscussInfo.m_wChairEpId = TP_INVALID_INDEX;
	}

	ptNode->m_wMixIndex = TP_INVALID_INDEX;

#ifndef Test_No_Res
	// 会场退出混音（单屏目标对应的混音器）
	TAudMixInfo* pMixRes = GetObjMixRes(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
	if (NULL != pMixRes && ptNode->IsVidSndValid())
	{
		pInst->GetEapu()->DelMember(pMixRes, ptEpInfo->m_wEpID, TP_MAX_STREAMNUM);
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("[DelEpInDiscussChan] Find pMixRes Failed! EpID:%d, ConfID:%d\n", 
			ptEpInfo->m_wEpID, pInst->GetInsID()));
	}
#endif

	// 释放下传音频通道
	if (ptNode != ptForeFatherNode && ptNode->IsAudRcvValid())
	{
        pInst->GetPutAudMgr()->ReleaseAudChnl(ptNode->m_wEpID, em_putauduser_discuss);
		CNetPortMgr::FreeMediaTrans(pInst, ptEpInfo->m_cToPutAuddrDsInfo);
		ptEpInfo->ClearPutAuddr();
	}

	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		// 释放码流
		if (ptEpInfo->m_awGetIndex[wIndex] < TP_UMS_MAX_CALLNUM)
		{
			pInst->GetVidAudEx()->Release(pInst, ptEpInfo->m_awGetIndex[wIndex]);
		}
	}
	ptEpInfo->ClearGetVidAddr();


	if (!ptEpInfo->m_bIsSmallChanOn)
	{//没有小码流的终端退出讨论，尝试释放适配，恢复分辨率
		ReleaseBasForDiscussEp(ptEpInfo);
		CNetPortMgr::FreeMediaTrans(pInst, ptEpInfo->m_cToBasDsInfo);
		ptEpInfo->ClearBasInfo();
	}

	MdlHint(Ums_Mdl_Call, ("[DelEpInDiscussChan] EpID:%d, ConfID:%d\n", ptEpInfo->m_wEpID, pInst->GetInsID()));
	return;
}


void CUmsDiscussMgr::RemoveEpFromDiscussChan(TDiscussEpInfo* ptEpInfo)
{
	if (!m_bUIDiscussStatus)
	{
		return ;
	}

	m_tDiscussInfo.m_tDiscussEpFromUI.DelMixId(ptEpInfo->m_wEpID);

	DelEpInDiscussChan(ptEpInfo);
	m_tDiscussInfo.m_tSpeakerRec.DelRec(ptEpInfo->m_wEpID);
	m_tDiscussInfo.DelEpById(ptEpInfo->m_wEpID);

	MdlHint(Ums_Mdl_Call, ("[RemoveEpFromDiscussChan] EpID:%d, ConfID:%d\n", ptEpInfo->m_wEpID, Inst()->GetInsID()));

	return;
}

void CUmsDiscussMgr::AdjustDiscussStatus(EmDisChnOprType emType, u16 wOprEpId /* = TP_INVALID_INDEX */)
{
	CUmsConfInst* pInst = Inst();
	if ( !m_bUIDiscussStatus )
	{
		return ;
	}
	
	// 讨论内发言会场处理
	TDiscussEpInfo* ptEpInfo = NULL;
	u16 wSpeakerIdInDiscuss = 0;
	if (emType == EmDisChnChangeSpeakerEp)
	{
		wSpeakerIdInDiscuss = wOprEpId;
	}
	else
	{
		ptEpInfo = m_tDiscussInfo.FindEpById(pInst->curSpeakerID());
		if (NULL == ptEpInfo || !ptEpInfo->IsValid())
		{
			ptEpInfo = m_tDiscussInfo.GetFirstVaildEp();
			if (NULL == ptEpInfo)
			{// 找不到发言会场，直接返回
				MdlError(Ums_Mdl_Call, ("[AdjustDiscussStatus] Can't Find Vaild Ep! ConfId:%d, OprType:%s, OprEp:%d, SpeakerId:%d\n", pInst->GetInsID(), 
					GetOprTypeName(emType), wOprEpId, pInst->curSpeakerID()));
				return;
			}
		}
		wSpeakerIdInDiscuss = ptEpInfo->m_wEpID;
	}
	// 记录发言会场
	m_tDiscussInfo.m_tSpeakerRec.AddRec(wSpeakerIdInDiscuss);
	
	u16 wIndex = 0;
	TDiscussOprInfo tOprInfo;
	tOprInfo.m_emOprType = emType;
	tOprInfo.m_wEpID = wOprEpId;
	
	// 计算目标
	UmsDiscussOprCycle(wIndex, emDiscussObjEnd, 
		m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustDstEpInfo(&m_tDiscussInfo, tOprInfo, wSpeakerIdInDiscuss));
	
	// CUmsDiscussMgr也保存有一份目标，主要用于通知，这里也需要更新下
	UptateDiscussObjInfo();

	// 讨论相关交换的调整，分为四种情形考虑：
	u8 byAdjustType; // 0: 讨论->非讨论; 1: 非讨论->非讨论; 2: 讨论->讨论，3: 非讨论->讨论
	if (!m_atDiscussObj[emDiscussObjForSpeakerEp].IsVaildObj())
	{// 发言会场目标无效，说明此时讨论内只有一个发言会场在线
	//  如果之前是讨论状态，则需要切为非讨论状态，如果之前是非讨论状态，则维持不变
		if (m_bDiscussStaus)
		{
			m_bDiscussStaus = FALSE;
			byAdjustType = 0; // 讨论->非讨论
		}
		else
		{
			byAdjustType = 1; // 非讨论->非讨论
		}
	}
	else
	{
		if (m_bDiscussStaus)
		{
			byAdjustType = 2; // 讨论->讨论
		}
		else
		{
			m_bDiscussStaus = TRUE;
			byAdjustType = 3; // 非讨论->讨论
		}
	}

	MdlHint(Ums_Mdl_Call, ("[AdjustDiscussStatus] ConfId:%d, OprType:%s, OprEp:%d, SpeakerId:%d, byAdjustType:%d\n", pInst->GetInsID(), 
		GetOprTypeName(emType), wOprEpId, pInst->curSpeakerID(), byAdjustType));


	if (1 < byAdjustType)
	{// 进入讨论
#ifndef Test_No_Res
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{// 调整没有小码流会场的适配（存在大小画面时，尝试申请适配）
			ptEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
			if (!ptEpInfo->m_bUsed || !ptEpInfo->IsValid() || ptEpInfo->m_bIsSmallChanOn)
			{
				continue;
			}

			AdjustBasForDiscussEpBakMethod(ptEpInfo);
		}
		
		if (wSpeakerIdInDiscuss != pInst->curSpeakerID() && 2 == byAdjustType && 0 != pInst->GetDelayTime())
		{// 这里的 pInst->curSpeakerID() 是老发言人
			SetDelayStat(1);
			FreeDsForNewAndOldSpeaker(wSpeakerIdInDiscuss, pInst->curSpeakerID());
		}

		if (EmDisChnEpChangeSeat == emType)
		{// 切坐席，只需要调整单屏会场目标的vmp（发言会场也可能是单屏）
			m_apcDisObj[emDiscussObjForSpeakerEp]->AdjustDstVidToVmpTpDsInfo(&m_tDiscussInfo, wSpeakerIdInDiscuss);
			m_apcDisObj[emDiscussObjForSingleScrEp]->AdjustDstVidToVmpTpDsInfo(&m_tDiscussInfo, wSpeakerIdInDiscuss);
		}
		else
		{
			// 更新目标到合成和混音的交换
			UmsDiscussOprCycle(wIndex, emDiscussObjEnd,
				m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustDstVidToVmpTpDsInfo(&m_tDiscussInfo, wSpeakerIdInDiscuss);\
				m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustDstAudToApu2TpDsInfo(&m_tDiscussInfo, wSpeakerIdInDiscuss);\
				m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustApu2MixForceActiveInfo(wSpeakerIdInDiscuss, !m_bUIVacOn));
		}
#endif
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			ptEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
			if (ptEpInfo->IsValid())
			{
				for (u16 wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
				{
					if (ptEpInfo->m_awGetIndex[wLoop] 
						< TP_UMS_MAX_CALLNUM)
					{
						pInst->GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[wLoop], TRUE);
					}

					if (NULL != ptEpInfo->m_apcBas[wLoop])
					{
						pInst->GetBas()->AskFrameToScreenBas(ptEpInfo->m_apcBas[wLoop]);
					}
				}
			}
		}

		// 是否需要切发言会场
		if (wSpeakerIdInDiscuss != pInst->curSpeakerID())
		{
			pInst->ChangeSpeaker(wSpeakerIdInDiscuss, NULL);
			//通知CNS发言人变更
			pInst->NotifyApplySpeakerToUI();
		}
		else
		{
			CNetPortMgr::CreateSpeakerToVirSpeaker(pInst);
		}
		// 调整到会场的讨论交换
		AdjustAllNodeToDiscuss(2==byAdjustType);

	}
	else
	{// 退出讨论
		// 是否需要切发言会场
		if (wSpeakerIdInDiscuss != pInst->curSpeakerID())
		{
			pInst->ChangeSpeaker(wSpeakerIdInDiscuss, NULL);
			pInst->GetVmp()->AdjustSpeakerVmp(TRUE);
			if (1 == byAdjustType)
			{
				pInst->AdjustNewSpeakerToAllNode();
			}
			//通知CNS发言人变更
			pInst->NotifyApplySpeakerToUI();
		}
		else
		{
			if (0 == byAdjustType)
			{
				CNetPortMgr::CreateSpeakerToVirSpeaker(pInst);
				pInst->GetVmp()->AdjustSpeakerVmp(TRUE, FALSE);
			}
		}

		if (0 == byAdjustType)
		{
			pInst->GetDualMgr()->AdjustDualMediaForDiscuss();
			AdjustAllNodeToDiscuss(FALSE);
		}
	}
	
	return;
}

void CUmsDiscussMgr::AdjustAllNodeToDiscuss(BOOL32 bAdjust)
{//
	CUmsConfInst* pInst = Inst();
	TCallNode* ptSpeaker = pInst->m_pcNodeMgr->GetNode(Inst()->curSpeakerID());
	TCapNode* ptSpeakFarther = pInst->m_pcNodeMgr->GetForeFatherNode(Inst()->curSpeakerID());	
	if (NULL == ptSpeakFarther || NULL == ptSpeaker)
	{
		MdlError(Ums_Mdl_Call, ("[ChangAllNodeToDiscuss] speaker invalid! confID:%d, speaker:%d\n", pInst->GetInsID(), pInst->curSpeakerID()));
		return ;
	}

	TUmsHandle tHandle;
	TDiscussCasecadeNtfy tNtfy;

	u8  wTimerNum = 0;
	u16 wIndex = 0;
	u16 awChildEpID[TP_CONF_MAX_CNSNUM] = {0};
	u16 wEpChildNum = 0;
	TCallNode* ptChildNode = NULL;
	for (TCapNode* ptNode = pInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pInst->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}

		if (1==m_byDelayStat)
		{
			if (ptNode->m_wEpID == m_wNewSpeaker || ptNode->m_wEpID == m_wOldSpeaker)
			{
				wTimerNum++;
			}
		}

		if (2==m_byDelayStat)
		{
			if (ptNode->m_wEpID != m_wNewSpeaker && ptNode->m_wEpID != m_wOldSpeaker)
			{
				continue;
			}

			if (ptNode->IsUms())
			{
				continue;
			}
		}

		// 所有会场清一次关键帧
		ptNode->m_tRmtChan.ResetFastStatis();

		if (ptNode->IsUms() && ptNode->m_wEpID != Inst()->chairID())
		{// 
			if (pInst->IsChairConf() && m_bDiscussStaus)
			{// 最上级将n-1模式音频码流下传
				wEpChildNum = pInst->GetNodeMgr()->GetAllChildNodeByRoot(awChildEpID, TP_CONF_MAX_CNSNUM, (TCallNode*)ptNode);
				for (wIndex = 0; wIndex < wEpChildNum; wIndex++)
				{
					ptChildNode = pInst->GetNodeMgr()->GetNode(awChildEpID[wIndex]);
					if (NULL != ptChildNode && ptChildNode->IsInMix() && ptChildNode->IsAudRcvValid())
					{
						CNetPortMgr::PutAudDownToDiscussEp(pInst, ptChildNode, &m_tEpAudInfo);
					}
				}
			}
            
			// 通知挂载在本级的ums讨论状态
			MakeCasecadeObjNtfy(ptNode, tNtfy);
			
			pInst->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			UmsSendConfCtrl(tHandle, evtp_UmsDiscussScreenStat_Notify, &tNtfy, sizeof(tNtfy));
		}

		if (bAdjust)
		{// 讨论下调整交换也要发youareseeing
			pInst->GetNodeFsm()->UpdateMediaTrans(ptNode, TRUE);
		}
		else
		{
			if (m_bDiscussStaus)
			{
				pInst->GetNodeFsm()->StartDis(ptNode);
			}
			else
			{
				pInst->GetNodeFsm()->StopDis(ptNode);
			}
		}
	}

	if (0!=wTimerNum)
	{
		pInst->KillTimer(evtp_Ums_For_Discuss_Timer);
		pInst->SetTimer(evtp_Ums_For_Discuss_Timer, pInst->GetDelayTime());
		MdlHint(Ums_Mdl_Call, ("Set Timer...ConfId:%d, wTimerNum:%d.\n", pInst->GetInsID(), wTimerNum));
	}

	SetDelayStat(0);

	//主动帮会场请求一次关键帧
	if (!m_bDiscussStaus)
	{
		if (pInst->IsPriNeedBas())
		{
			UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
				pInst->GetBas()->SeeSpeakerAskFrameToBas(wIndex);
			    pInst->GetBas()->SeeChairAskFrameToBas(wIndex));
		}
		else
		{
			pInst->AskKeyByEpID(pInst->curSpeakerID(), EmAskKeySpeaker);
			if (pInst->curSpeakerID() != pInst->chairID())
			{
				pInst->AskKeyByEpID(pInst->chairID(), EmAskKeyChair);
			}
		}

		if (pInst->IsChairConf())
		{
			TUmsVidFormat tVidFormat;
			pInst->GetVmp()->AskFrameToSpeakerVmp(tVidFormat);
		}

		return;
	}

	if (pInst->IsPriNeedBas())
	{// 适配会议
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			pInst->GetBas()->SeeSpeakerAskFrameToBas(wIndex);
		}

		if (NULL != pInst->GetSpeaker().m_pcSingleBas)
		{
			pInst->GetBas()->AskFrameToScreenBas(pInst->GetSpeaker().m_pcSingleBas);
		}

		AskKeyFrameToVmp(emDiscussObjForSpeakerEp, TP_INVALID_INDEX);
	}
	else
	{
		AskKeyFrameToVmp(emDiscussObjForSpeakerEp, TP_INVALID_INDEX);
		AskKeyFrameToVmp(emDiscussObjForThreeScrEp, TP_INVALID_INDEX);
		AskKeyFrameToVmp(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
	}

	return;
}

BOOL32 CUmsDiscussMgr::AdjustAudMixVacStatus( BOOL32 bVacOn )
{
	CUmsConfInst* pInst = Inst();
#ifndef Test_No_Res
	TAudMixInfo* pMixRes = GetObjMixRes(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
	if (NULL == pMixRes)
	{
		MdlError(Ums_Mdl_Call, ("[AdjustAudMixVacStatus] Find pMixRes Failed! ConfID:%d, CurrentVacStat:%d, DiscussStat:%d\n",
			pInst->GetInsID(), m_bUIVacOn, m_bUIDiscussStatus));
		return FALSE;
	}
	
	if (bVacOn)
	{// 开启语音激励
		if (!pMixRes->m_bMixMotive)
		{
			pInst->GetEapu()->StartVac(pMixRes);
		}
	}
	else
	{// 关闭语音激励
		if (pMixRes->m_bMixMotive)
		{
			pInst->GetEapu()->StopVac(pMixRes);
		}
	}

	u16 wIndex;
	UmsDiscussOprCycle(wIndex, emDiscussObjEnd,
			m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustApu2MixForceActiveInfo(pInst->curSpeakerID(), !bVacOn));

#endif	
	m_bUIVacOn = bVacOn;
	
	return TRUE;
}

void CUmsDiscussMgr::UptateDiscussListFromUI(TAuxMixList& tAuxDisList)
{// 更新界面传过来的讨论成员列表
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = NULL;
	TCapNode*  ptNodeFar = NULL;
	u16 wEpId = 0;
	m_tDiscussInfo.m_tDiscussEpFromUI.Clear();
	m_tDiscussInfo.m_tDiscussEpFromUI.m_bAudMixOn = tAuxDisList.m_bAudMixOn;
	m_tDiscussInfo.m_tDiscussEpFromUI.m_bVacOn = tAuxDisList.m_bAudMixOn;
	for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{
		wEpId = tAuxDisList.m_awList[wIndex];
		if (!VALID_ALL_EPID(wEpId))
		{
			tAuxDisList.m_awList[wIndex] = TP_INVALID_INDEX;
			continue;
		}
		
		ptNode = pInst->m_pcNodeMgr->GetNode(wEpId);
		if (NULL == ptNode || !ptNode->m_bUsed || ptNode->IsUms())
		{// 
			tAuxDisList.m_awList[wIndex] = TP_INVALID_INDEX;
			continue;
		}

        ptNodeFar = pInst->m_pcNodeMgr->GetForeFatherNode(ptNode);
		if (NULL == ptNodeFar || (ptNodeFar->IsMcu() && ptNodeFar != ptNode))
		{// Mcu 下级会场不能做为讨论的成员，不能调取其码流
            tAuxDisList.m_awList[wIndex] = TP_INVALID_INDEX;
			continue;
		}

		if (!m_tDiscussInfo.m_tDiscussEpFromUI.AddMixID(wEpId))
		{
			tAuxDisList.m_awList[wIndex] = TP_INVALID_INDEX;
			continue;
		}
	}
	return;
}

void CUmsDiscussMgr::UptateDiscussEpInfo()
{
	CUmsConfInst* pInst = Inst();
	TCallNode* ptNode = NULL;

	for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{
		if (TP_INVALID_INDEX == m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex])
		{
			continue;
		}

		ptNode = pInst->m_pcNodeMgr->GetNode(m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex]);

		if (NULL == ptNode || !ptNode->m_bUsed || ptNode->IsUms())
		{
			m_tDiscussInfo.m_tDiscussEpFromUI.m_awList[wIndex] = TP_INVALID_INDEX;
			continue;
		}
		m_tDiscussInfo.AddEpID(ptNode);
	}
	return;
}

void CUmsDiscussMgr::UptateDiscussObjInfo()
{
	u16 wIndex = 0;
	TDiscussDstEpInfo* ptInfo = NULL;
	
	for (u16 wType = 0; wType < emDiscussObjEnd; wType++)
	{
		ptInfo = m_apcDisObj[(EmDiscussModleObj)wType]->GetDiscussObj();
		
		m_atDiscussObj[(EmDiscussModleObj)wType].Clear();  // 先清空
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atDiscussObj[EmDiscussModleObj(wType)].m_abIsVaild[wIndex] = ptInfo->m_atScreenInfo[wIndex].IsScreenValid();
			m_atDiscussObj[EmDiscussModleObj(wType)].m_atEpAlias[wIndex] = ptInfo->m_atScreenInfo[wIndex].m_tAlias;
		}
	}

	if (m_tDiscussInfo.IsSpecialEpVaild())
	{// 发言会场是单屏的时候，两边用来存special目标
		m_atDiscussObj[emDiscussObjForSpeakerEp].m_abIsVaild[0] = m_tDiscussInfo.m_tSpecialDst.m_atScreenInfo[0].IsScreenValid();
		m_atDiscussObj[emDiscussObjForSpeakerEp].m_atEpAlias[0] = m_tDiscussInfo.m_tSpecialDst.m_atScreenInfo[0].m_tAlias;
		m_atDiscussObj[emDiscussObjForSpeakerEp].m_abIsVaild[2] = m_tDiscussInfo.m_tSpecialDst.m_atScreenInfo[2].IsScreenValid();
		m_atDiscussObj[emDiscussObjForSpeakerEp].m_atEpAlias[2] = m_tDiscussInfo.m_tSpecialDst.m_atScreenInfo[2].m_tAlias;
	}

	return;
}

void CUmsDiscussMgr::MakeCasecadeObjNtfy( TCapNode* ptUmsNode, TDiscussCasecadeNtfy& tNtfy )
{
	tNtfy.Clear();
	if (!ptUmsNode->IsUms())
	{
		MdlError(Ums_Mdl_Call, ("MakeCasecadeObjNtfy error!!! Node is not ums! Conf:%d, Ep:%d\n", 
			Inst()->GetInsID(), ptUmsNode->m_wEpID));
		return;
	}

	if (m_bDiscussStaus)
	{
		tNtfy.m_bIsDiscussModle = TRUE;
		memcpy(tNtfy.m_atDiscussObj, m_atDiscussObj, sizeof(TDiscussObjInfo)*emDiscussObjEnd);
		memcpy(&tNtfy.m_tEpAudInfo, &m_tEpAudInfo, sizeof(TDiscussEpAudInfo));
		m_tEpAudInfo.Clear(); // 通知完成后，清空

		if (m_tDiscussInfo.IsSpecialEpVaild())
		{// 如果这个speicalep在此ums的下级，那么需要通知下去
			TCallNode* pNode = Inst()->GetNodeMgr()->GetNodeUnderThisUms(ptUmsNode, m_tDiscussInfo.m_wSpecialEp);
			if (NULL != pNode)
			{
				tNtfy.m_atDiscussObj[emDiscussObjForSpeakerEp].m_wReserve = pNode->m_wLowChildEpID;
			}
		}
	}
	else
	{
		tNtfy.m_bIsDiscussModle = FALSE;
	}
	return;
}

EmDiscussRspRet CUmsDiscussMgr::AssignResource()
{
#ifndef Test_No_Res
	u16 wIndex = 0;
	EmDiscussRspRet emRet = em_DiscussOprRsp_Ok;

	/*判断是否有可用的媒体资源*/
	//适配会议,适配器最少占用两个合成器
	if (m_pcConf->IsPriNeedBas() && (!m_pcConf->IsAssignBasReady()))       
	{
		if (!CheckIdleMediaSource(ASSGIN_DIS_VMP_NUM + 2, 0, 0))
		{
			MdlError(Ums_Mdl_Call, ("AssignResource: Need Vmp Number  9!\n"));
			return em_Start_AssginVmpFail;
		}
	}
	else
	{
		if (NULL == m_pcConf->GetSpeaker().m_pcSingleVmp)
		{
			if (!CheckIdleMediaSource(ASSGIN_DIS_VMP_NUM, 0, 0))
			{
				MdlError(Ums_Mdl_Call, ("AssignResource: Need Vmp Number 7!\n"));
				return em_Start_AssginVmpFail;
			}
		}
		//发言人合成存在，再申请6个合成器
		else 
		{
			if (!CheckIdleMediaSource(ASSGIN_DIS_VMP_NUM - 1, 0, 0))
			{
				MdlError(Ums_Mdl_Call, ("AssignResource:Need Vmp Number 6!\n"));
				return em_Start_AssginVmpFail;
			}
		}
	}
	

	if (!CheckIdleMediaSource(0, 0, ASSGIN_DIS_MIX_NUM))
	{
		return em_Start_AssignMixFail;
	}
	for (wIndex = 0; wIndex < emDiscussObjEnd; wIndex++)
	{
		emRet = m_apcDisObj[(EmDiscussModleObj)wIndex]->AssignResource(Inst());
		if (em_DiscussOprRsp_Ok != emRet)
		{
			UmsDiscussOprCycle(wIndex, emDiscussObjEnd, 
				m_apcDisObj[(EmDiscussModleObj)wIndex]->FreeResource());
			return emRet;
		}
	}
#endif
	return em_DiscussOprRsp_Ok;
}

void CUmsDiscussMgr::ResetDiscussInfo()
{
	m_bUIVacOn = FALSE;
	m_bUIDiscussStatus = FALSE;
	m_bDiscussStaus = FALSE;
	m_tDiscussInfo.ResetDiscussInfo();
	m_tEpAudInfo.Clear();

	m_byDelayStat = 0;
	m_wNewSpeaker = 0;
	m_wOldSpeaker = 0;

	u16 wIndex = 0;
	UmsDiscussOprCycle(wIndex, emDiscussObjEnd, 
		m_apcDisObj[(EmDiscussModleObj)wIndex]->FreeResource();\
		m_atDiscussObj[(EmDiscussModleObj)wIndex].Clear());
	
	return;
}

void CUmsDiscussMgr::DiscussInfoNotify()
{
	CUmsConfInst* pcInst = Inst();
	
	if (!pcInst->IsChairConf())
	{
		return;
	}

	TConfAuxMixInfo tDisInfo;
	GetDiscussStateInfo(tDisInfo);
	
	// 通知主席会议讨论状态
	Inst()->NotifyConfCtrlMsgToCns(ev_UmsConfAMixUpdate_Nty,  Inst()->chairID(), &tDisInfo, sizeof(tDisInfo));
	
	// 通知umc
	Inst()->NotifyMsgToServiceForUI(evtp_AuxMixInfo_Notify, &tDisInfo, sizeof(TConfAuxMixInfo));
	return;
}

// void CUmsDiscussMgr::AdjustBasForDiscussEp( TDiscussEpInfo* ptEpInfo )
// {// 没有小码流的会场
// //	 a、需要显示该终端大小图像时，则小码流需额外占用适配资源。无适配资源，则小图像显示静态图片 
// //	    备注：无论终端是否支持降分辨率，均要保证大图像的清晰度
// //   b、只需要显示终端小图像时，则终端直接降分辨率
// 	if (ptEpInfo->m_bIsSmallChanOn || !ptEpInfo->IsValid())
// 	{
// 		return;
// 	}
// 
// 	CUmsConfInst* pInst = Inst();
// 	s32 symbolflag = 1;
// 	u16 wCurIndex = 0;
// 	TCallNode* ptNode = NULL;
// 	ptNode = pInst->GetNodeMgr()->GetNode(ptEpInfo->m_wEpID);
// 	if (NULL == ptNode || !ptNode->IsChanOn())
// 	{
// 		return;
// 	}
// 
// 	for (u16 wIndex = 1; wIndex <= ptEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
// 	{// 按屏来动态分配适配；最多占用7个
// 		
// 		wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
// 		if (IsNeedBasForDiscussEp(ptEpInfo->m_wEpID, wCurIndex))
// 		{// 需要大画面，且没有分配适配，尝试分配
// 			if (NULL != ptEpInfo->m_apcBas[wCurIndex])
// 			{// 已经申请了，无须重复申请
// 				continue;
// 			}
// 			
// 			if (!pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
// 			{// 没有分配到适配，如果之前降了分辨率，就恢复，保证大图像质量
// 				if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
// 				{// 
// 					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
// 					ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
// 				}
// 				continue;
// 			}
// 
// 			ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
// 			// 调整后适配格式
// 			TUmsVidFormat tVidFormat;
// 			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
// 			tVidFormat.m_emRes = emTPV480x272;
// 			tVidFormat.m_wFrameRate = 15;
// 			pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
// 			
// 			if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
// 			{// 申请到了适配，恢复该屏分辨率，用于进大画面，小画面从适配出
// 				pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
// 				ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
// 			}
// 		}
// 		else
// 		{// 不需要大画面
// 			
// 			if (ptEpInfo->m_bMtAdjustRes)
// 			{// 能降分辨率终端
// 				if (NULL != ptEpInfo->m_apcBas[wCurIndex])
// 				{
// 					pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wCurIndex]);
// 					ptEpInfo->m_apcBas[wCurIndex] = NULL;
// 				}
// 
// 				if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex])
// 				{// 降分辨率，进小画面
// 					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, emTPV480x272);
// 				    ptEpInfo->m_aemVideoRes[wCurIndex] = emTPV480x272;
// 				}
// 			}
// 			else
// 			{// 不能降分辨率终端，需要适配才能进小画面
// 				if (NULL == ptEpInfo->m_apcBas[wCurIndex])
// 				{// 
// 					if (pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
// 					{// 申请适配
// 						ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
// 						// 调整后适配格式
// 						TUmsVidFormat tVidFormat;
// 						tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
// 						tVidFormat.m_emRes = emTPV480x272;
// 						tVidFormat.m_wFrameRate = 15;
// 						pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
// 					}
// 				}
// 			}
// 		}
// 	}
// 	
// 	CNetPortMgr::AdjustDiscussEpToBas(pInst, ptEpInfo);
// 	
// 	return;
// }

void CUmsDiscussMgr::AdjustBasForDiscussEpBakMethod( TDiscussEpInfo* ptEpInfo )
{// 没有小码流的会场
	//	 a、需要显示该终端大小图像时，则小码流需额外占用适配资源，无适配资源，则降分辨率 
	//   b、只需要显示终端小图像时，则不占用适配资源，终端直接降分辨率，如果终端不支持降分辨率，才尝试申请适配
	if (ptEpInfo->m_bIsSmallChanOn || !ptEpInfo->IsValid())
	{
		return;
	}
	
	CUmsConfInst* pInst = Inst();
	s32 symbolflag = 1;
	u16 wCurIndex = 0;
	TCallNode* ptNode = NULL;
	ptNode = pInst->GetNodeMgr()->GetNode(ptEpInfo->m_wEpID);
	if (NULL == ptNode || !ptNode->IsChanOn())
	{
		return;
	}
	
	for (u16 wIndex = 1; wIndex <= ptEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
	{// 按屏来动态分配适配；最多占用7个
		
		wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
		if (IsNeedBasForDiscussEp(ptEpInfo->m_wEpID, wCurIndex))
		{// 需要大画面，且没有分配适配，尝试分配
			if (NULL != ptEpInfo->m_apcBas[wCurIndex])
			{// 已经申请了，无须重复申请
			    ptEpInfo->m_awBasUserinfo[wCurIndex].m_wDisUserCount = 1;
				continue;
			}
			
			if (!pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
			{// 没有分配到适配，需要尝试降分辨率
				if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex] && ptEpInfo->m_bMtAdjustRes)
				{// 
					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, emTPV480x272);
					ptEpInfo->m_aemVideoRes[wCurIndex] = emTPV480x272;
				}
				continue;
			}

            ptEpInfo->m_awBasUserinfo[wCurIndex].m_wDisUserCount = 1;

			
			ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
			// 调整后适配格式
			TUmsVidFormat tVidFormat;
			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
			tVidFormat.m_emRes = emTPV480x272;
			tVidFormat.m_wFrameRate = 15;
			pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
			
			if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
			{// 申请到了适配，恢复该屏分辨率，用于进大画面，小画面从适配出
				pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
				ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
			}
		}
		else
		{// 不需要大画面
			
			if (ptEpInfo->m_bMtAdjustRes)
			{// 能降分辨率终端
				ptEpInfo->m_awBasUserinfo[wCurIndex].m_wDisUserCount = 0;

				if ( 0 == ptEpInfo->m_awBasUserinfo[wCurIndex].m_wSelUserCount)
				{
					if (NULL != ptEpInfo->m_apcBas[wCurIndex])
					{
						pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wCurIndex]);
						ptEpInfo->m_apcBas[wCurIndex] = NULL;
					}
					
					if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex])
					{// 降分辨率，进小画面
						pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, emTPV480x272);
						ptEpInfo->m_aemVideoRes[wCurIndex] = emTPV480x272;
					}
				}

			}
			else
			{// 不能降分辨率终端，需要适配才能进小画面
				if (NULL == ptEpInfo->m_apcBas[wCurIndex])
				{// 
					if (pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
					{// 尝试申请适配
						ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
						// 调整后适配格式
						TUmsVidFormat tVidFormat;
						tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
						tVidFormat.m_emRes = emTPV480x272;
						tVidFormat.m_wFrameRate = 15;
						pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
					}
				}
			}
		}
	}
	
	CNetPortMgr::AdjustDiscussEpToBas(pInst, ptEpInfo);
	
	return;
}

void CUmsDiscussMgr::ReleaseBasForDiscussEp( TDiscussEpInfo* ptEpInfo)
{
	CUmsConfInst* pInst = Inst();
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (NULL != ptEpInfo->m_apcBas[wIndex])
		{
			pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wIndex]);
			ptEpInfo->m_apcBas[wIndex] = NULL;
		}
		
		if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wIndex] && ptEpInfo->m_bMtAdjustRes)
		{// 恢复分辨率
			pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wIndex, ptEpInfo->m_aemVideoRes[wIndex], TRUE);
		}
	}
	return;
}

BOOL32 CUmsDiscussMgr::IsNeedBasForDiscussEp(u16 wEpId , u16 wScreenIndex)
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (m_apcDisObj[(EmDiscussModleObj)wIndex]->IsDiscussObjDstEp(wEpId, wScreenIndex))
		{
			return TRUE;
		}
	}

	if (m_tDiscussInfo.IsSpecialEpVaild() && MIDSCREENINDEX != wScreenIndex)
	{
		if (VALID_SCREEN_INDEX(m_tDiscussInfo.m_tSpecialDst.GetIndexByEp(wEpId, wScreenIndex)))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CUmsDiscussMgr::AskKeyFrameToVmp( EmDiscussModleObj emType, u16 wScreenIndex )
{// 向合成器请求关键帧

	if (!Inst()->IsChairConf())
	{
		return;
	}

	if (!VALID_SCREEN_INDEX(wScreenIndex))
	{
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			const CBaseService* pcVmpRes = NULL;
			pcVmpRes = GetObjVmpRes(emType, wIndex);
			
			if (NULL != pcVmpRes)
			{
				Inst()->GetVmpServiceHandle()->AskFrameToBaseService(pcVmpRes);
			}
		}
		return;
	}

	const CBaseService* pcVmpRes = NULL;
	pcVmpRes = GetObjVmpRes(emType, wScreenIndex);
	
	if (NULL != pcVmpRes)
	{
		Inst()->GetVmpServiceHandle()->AskFrameToBaseService(pcVmpRes);
	}
	
	return;
}

void CUmsDiscussMgr::AskKeyFrameToVmpByNode(TCapNode* ptFatherNode, TCallNode* ptNode, u16 wScreenIndex, BOOL32 bReqBySys)
{
	if (!VALID_SCREEN_INDEX(wScreenIndex))
	{
		return;
	}

	CUmsConfInst* pInst = Inst();
	BOOL32 bFlag = IsSpeacialEp(ptNode->m_wEpID);

	if ((pInst->curSpeakerID() == ptNode->m_wEpID) || (bFlag && MIDSCREENINDEX != wScreenIndex))
	{//发言会场或special会场的两边屏, 向合成器请求关键关键帧
		AskKeyFrameToVmp(emDiscussObjForSpeakerEp, wScreenIndex);
	}
	else if (ptNode->IsThreeVidRcv())
	{//三屏目标
		if (pInst->GetBas()->IsSpeakerNeedBas(ptFatherNode->m_tVidRcvFormat.m_tFormat))
		{// 向适配请求
			pInst->GetBas()->SeeSpeakerAskFrameToBas(wScreenIndex);
		}
		else
		{// 向合成器请求
			AskKeyFrameToVmp(emDiscussObjForThreeScrEp, wScreenIndex);
		}
	}
	else
	{//单屏目标
		if (m_pcConf->GetBas()->IsSpeakerNeedBas(ptFatherNode->m_tVidRcvFormat.m_tFormat))
		{// 向适配请求
			pInst->GetBas()->AskFrameToScreenBas(pInst->GetSpeaker().m_pcSingleBas);
		}
		else
		{// 向合成器请求
			AskKeyFrameToVmp(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
		}
	}
	return;
}

BOOL32 CUmsDiscussMgr::FindDiscussObjTypebyVmpRes(u16 wResId, TPOUT EmDiscussModleObj& emType, TPOUT u16& wScreenIndex)
{
	const CBaseService* pcVmpRes = NULL;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		pcVmpRes = GetObjVmpRes(emDiscussObjForSpeakerEp, wIndex);
		if (NULL != pcVmpRes && wResId == pcVmpRes->GetServiceID())
		{
			emType = emDiscussObjForSpeakerEp;
			wScreenIndex = wIndex;
			return TRUE;
		}

		pcVmpRes = GetObjVmpRes(emDiscussObjForThreeScrEp, wIndex);
		if (NULL != pcVmpRes && wResId == pcVmpRes->GetServiceID())
		{
			emType = emDiscussObjForThreeScrEp;
			wScreenIndex = wIndex;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL32 CUmsDiscussMgr::FindDiscussObjTypebyMixRes( u16 wResId, TPOUT EmDiscussModleObj& emType, TPOUT u16& wScreenIndex )
{
	TAudMixInfo* pcMixRes = NULL;
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		pcMixRes = GetObjMixRes(emDiscussObjForSpeakerEp, wIndex);
		if (NULL != pcMixRes && wResId == pcMixRes->m_tEqpRes.m_byEqpID)
		{
			emType = emDiscussObjForSpeakerEp;
			wScreenIndex = wIndex;
			return TRUE;
		}
		
		pcMixRes = GetObjMixRes(emDiscussObjForThreeScrEp, wIndex);
		if (NULL != pcMixRes && wResId == pcMixRes->m_tEqpRes.m_byEqpID)
		{
			emType = emDiscussObjForThreeScrEp;
			wScreenIndex = wIndex;
			return TRUE;
		}
	}
	return FALSE;
}

const CBaseService* CUmsDiscussMgr::GetObjVmpRes( EmDiscussModleObj emType, u16 wScreenIndex )
{//
	if (emType < emDiscussObjEnd)
	{
		return m_apcDisObj[emType]->GetVmpRes(wScreenIndex);
	}
	return NULL;
}

TAudMixInfo* CUmsDiscussMgr::GetObjMixRes( EmDiscussModleObj emType, u16 wScreenIndex )
{//
	if(emType < emDiscussObjEnd)
	{
		return m_apcDisObj[emType]->GetMixRes(wScreenIndex);
	}
	return NULL;
}

void CUmsDiscussMgr::FreeDsForNewAndOldSpeaker(u16 wNewSpeaker, u16 wOldSpeaker)
{
	CUmsConfInst* pInst = Inst();

	TCapNode* ptNode = pInst->GetNodeMgr()->GetForeFatherNode(wNewSpeaker);
	TCapNode* ptNodeTemp = pInst->GetNodeMgr()->GetForeFatherNode(wOldSpeaker);

	if (NULL == ptNodeTemp || NULL == ptNode)
	{
		SetDelayStat(0);
		return;
	}

	if (ptNode->m_wEpID == ptNodeTemp->m_wEpID)
	{
		SetDelayStat(0);
		return;
	}

	if (ptNodeTemp->IsUms() && ptNode->IsUms())
	{
		SetDelayStat(0);
		return;
	}
	
	u16 wIndex = 0;
	u16 wLoop = 0;
	BOOL32 bAddFlag = FALSE;
	BOOL32 bIsSpecialEp = FALSE;

	TTPTransAddr  atDelToSndAddr[6];
	TTPTransAddr  atDelFromRcvAddr[6];
	u16 wDelNum = 0;

	u16 wOldDsNum = 0;
	TUmsDsData atOldDsData[30];
	u16 wNewDsNum = 0;
	TUmsDsData atNewDsData[30];

	do 
	{// 先删掉部分到新发言人的交换
		m_wNewSpeaker = ptNode->m_wEpID;

		if (ptNode->IsUms() || !ptNode->IsVidRcvValid())
		{
			break;
		}

		bIsSpecialEp = IsSpeacialEp(ptNode->m_wEpID);

		if (ptNode->IsSingleVidRcv())
		{// 单屏
			if (ptNode->m_aemObj[MIDSCREENINDEX] == emObjDiscard)
			{// 目标是讨论，才删视频
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				wDelNum++;
			}

			// 到单屏的音频始终取自同一个混音器，没必要删；
		}
		else if (ptNode->IsThreeVidRcv() && bIsSpecialEp)
		{// 切回那个特殊的会场发言人
		//  spcialep又成为发言人，两边屏会不变的，只拆中间就好（三屏切单屏发言，又再次切回这个三屏发言，就是这种情形）

			if (ptNode->m_aemObj[MIDSCREENINDEX] == emObjDiscard)
			{//
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				wDelNum++;
			}

			atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atAudDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
			atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tAud.m_tRtcpForSnd;
			wDelNum++;

		}
		else
		{// 三屏
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				if (ptNode->m_aemObj[wIndex] == emObjDiscard)
				{
					atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
					atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForSnd;
					wDelNum++;
				}
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForSnd;
				wDelNum++;
			}
		}

		MdlHint(Ums_Mdl_Call, ("DestroyMediaTrans new speaker Ds....ConfID:%d, newspeaker:%d, IsSpecialEp:%d, wDelNum:%d.\n", 
			pInst->GetInsID(), ptNode->m_wEpID, bIsSpecialEp, wDelNum));

		if (0 == wDelNum)
		{
			break;
		}

		ptNode->m_tDsList.GetMediaTrans(atOldDsData, wOldDsNum);	

		for (wIndex = 0; wIndex < wOldDsNum; wIndex++)
		{
			bAddFlag = TRUE;
			for (wLoop = 0; wLoop < wDelNum; wLoop++)
			{
				if (atOldDsData[wIndex].m_tSndToAddr == atDelToSndAddr[wLoop]
					|| atOldDsData[wIndex].m_tRcvFromAddr == atDelFromRcvAddr[wLoop])
				{
					bAddFlag = FALSE;
					break;
				}
			}

			if (bAddFlag)
			{
				atNewDsData[wNewDsNum] = atOldDsData[wIndex];
				wNewDsNum++;
			}
		}
		
		CNetPortMgr::MergerDsList(pInst, ptNode->m_tDsList, atNewDsData, wNewDsNum, "DestroyMediaTrans new speaker");
	
	}while (0);

	ptNode = ptNodeTemp;

	wDelNum = 0;
	memset(atDelToSndAddr, 0, sizeof(atDelToSndAddr));
	memset(atDelFromRcvAddr, 0, sizeof(atDelFromRcvAddr));
	wOldDsNum = 0;
	wNewDsNum = 0;
	memset(atNewDsData, 0, sizeof(atNewDsData));
	memset(atOldDsData, 0, sizeof(atOldDsData));

	do
	{// 删掉部分到老发言人的交换
		m_wOldSpeaker = ptNode->m_wEpID;

		if (ptNode->IsUms() || !ptNode->IsVidRcvValid())
		{
			break;
		}

		bIsSpecialEp = IsSpeacialEp(ptNode->m_wEpID);

		if (ptNode->IsSingleVidRcv())
		{// 单屏
			if (ptNode->m_aemObj[MIDSCREENINDEX] == emObjDiscard)
			{// 目标是讨论，才删视频
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				wDelNum++;
			}

			// 到单屏的音频始终取自同一个混音器，没必要删；
		}
		else if (ptNode->IsThreeVidRcv() && bIsSpecialEp)
		{// 老发言人成为那个spcialep，两边屏会不变的，只拆中间就好（三屏切单屏发言会出现这种情形）
			if (ptNode->m_aemObj[MIDSCREENINDEX] == emObjDiscard)
			{//
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				wDelNum++;
			}

			atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atAudDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
			atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tAud.m_tRtcpForSnd;
			wDelNum++;
		}
		else
		{
			// 三屏
			for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
			{
				if (ptNode->m_aemObj[wIndex] == emObjDiscard)
				{
					atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[wIndex].m_tChanAddr.m_tRtpAddr;
					atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[wIndex]->m_tVid.m_tRtcpForSnd;
					wDelNum++;
				}
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atAudDec[wIndex].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[wIndex]->m_tAud.m_tRtcpForSnd;
				wDelNum++;
			}
		}
		
		
		MdlHint(Ums_Mdl_Call, ("DestroyMediaTrans old speaker Ds....ConfID:%d, oldspeaker:%d, IsSpecialEp:%d, wDelNum:%d.\n", 
			pInst->GetInsID(), ptNode->m_wEpID, bIsSpecialEp, wDelNum));
		
		if (0 == wDelNum)
		{
			break;
		}
		
		ptNode->m_tDsList.GetMediaTrans(atOldDsData, wOldDsNum);	
		
		for (wIndex = 0; wIndex < wOldDsNum; wIndex++)
		{
			bAddFlag = TRUE;
			for (wLoop = 0; wLoop < wDelNum; wLoop++)
			{
				if (atOldDsData[wIndex].m_tSndToAddr == atDelToSndAddr[wLoop] 
					|| atOldDsData[wIndex].m_tRcvFromAddr == atDelFromRcvAddr[wLoop])
				{
					bAddFlag = FALSE;
					break;
				}
			}
			
			if (bAddFlag)
			{
				atNewDsData[wNewDsNum] = atOldDsData[wIndex];
				wNewDsNum++;
			}
		}
		
		CNetPortMgr::MergerDsList(pInst, ptNode->m_tDsList, atNewDsData, wNewDsNum, "DestroyMediaTrans old speaker");
		
	}while (0);
	
	return;
}

BOOL32 CUmsDiscussMgr::IsNeedDelay( u16 wEpId )
{
	if (0 == wEpId || 1 != m_byDelayStat)
	{
		return FALSE;
	}

	if (wEpId == m_wNewSpeaker || wEpId == m_wOldSpeaker)
	{
		return TRUE;
	}

	return FALSE;
}

void CUmsDiscussMgr::GetMixOutAddrForDown(TCapNode* ptNode, u16 wScreenIndex, TServiceAddr& tAddr)
{
	CUmsConfInst* pInst = Inst();
	tAddr.Clear();
	if (pInst->IsChairConf() || !ptNode->IsInMix())
	{
		return;
	}

	BOOL32 bIsSpeaciaEp = ptNode->m_wEpID == GetSpeacialEp();
	BOOL32 bIsSpeaker = ptNode->m_wEpID == pInst->curSpeakerID();

	if (m_tEpAudInfo.IsRcvNNmodeAud(ptNode->m_wEpID, wScreenIndex))
	{
		if (bIsSpeaker || bIsSpeaciaEp)
		{// 下级发言会场或speaciaep的n模式，在主席通道取
			return;
		}

		TTPDsFrom tScrAddr;
		if (ptNode->IsThreeAudRcv())
		{
			if (pInst->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat))
			{// 从音频适配中取
				pInst->GetBas()->GetSpeakerAudBasOutAddr(wScreenIndex, ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tScrAddr);
				tAddr.m_tAddr.m_tRtpAddr = tScrAddr.m_tRtpAddr;
				tAddr.m_tAddr.m_tBackRtcpAddr = tScrAddr.m_tBackRtcpAddr;
				tAddr.m_dwMediaNode = tScrAddr.m_dwEqpNode;
			}
			else
			{
				tAddr.m_tAddr.m_tRtpAddr = pInst->GetSpeakerAudDec(wScreenIndex).m_tRtpAddr;
				tAddr.m_tAddr.m_tBackRtcpAddr = pInst->GetSpeakerAudDec(wScreenIndex).m_tBackRtcpAddr;
				tAddr.m_dwMediaNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				tAddr.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			}
		}
		else
		{
			if (pInst->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat))
			{// 从音频适配中取
				pInst->GetBas()->GetSpeakerMixAudBasOutAddr(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat, tScrAddr);
				tAddr.m_tAddr.m_tRtpAddr = tScrAddr.m_tRtpAddr;
				tAddr.m_tAddr.m_tBackRtcpAddr = tScrAddr.m_tBackRtcpAddr;
				tAddr.m_dwMediaNode = tScrAddr.m_dwEqpNode;
			}
			else
			{
				tAddr.m_tAddr.m_tRtpAddr = pInst->GetSpeakerAudMix().m_tRtpAddr;
				tAddr.m_tAddr.m_tBackRtcpAddr = pInst->GetSpeakerAudMix().m_tBackRtcpAddr;
				tAddr.m_dwMediaNode = ptNode->m_tMediaEqp.m_dwEqpNode;
				tAddr.m_tAddr.m_tRtpAddr.SetIP(ptNode->m_tMediaEqp.m_dwEqpIp);
			}
		}

	}
	else
	{
		TDiscussEpInfo* ptEpInfo = GetDiscussEpInfoById(ptNode->m_wEpID);
		if (NULL != ptEpInfo)
		{
			tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_atPutAuddr[wScreenIndex].m_tRtpAddr;
			tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_atPutAuddr[wScreenIndex].m_tBackRtcpAddr;
			tAddr.m_dwMediaNode = m_pcConf->GetConfEqpDs().m_dwEqpNode;
		}
	}
}

BOOL32 CUmsDiscussMgr::IsMaxVmpSameEp()
{
	if ( m_atDiscussObj[emDiscussObjForThreeScrEp].m_atEpAlias[0] == m_atDiscussObj[emDiscussObjForThreeScrEp].m_atEpAlias[1]
		&& m_atDiscussObj[emDiscussObjForThreeScrEp].m_atEpAlias[1] == m_atDiscussObj[emDiscussObjForThreeScrEp].m_atEpAlias[2])
	{
		return TRUE;
	}
	return FALSE;
}




BOOL32  CUmsDiscussMgr::RestoreAdjustedResForSelEp(u16 wSelTargetEp, u16 wScreenIndex)
{   // wScreenIndex 为 0 、1、2 为会场对应屏恢复分辨率
	// wScreenIndex 为 3(TP_MAX_STREAMNUM) 为会场所有屏恢复分辨率

	MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::RestoreAdjustedResForSelEp  ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n",
		    m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex));


    if (!m_pcConf->IsChairConf())
	{
        return FALSE;
	}

	if (!IsDiscussModle())
	{
        return TRUE;
	}

	if (wScreenIndex > TP_MAX_STREAMNUM)
	{
        return FALSE;
	}

	TCallNode* ptNode = NULL;
	ptNode = m_pcConf->GetNodeMgr()->GetNode(wSelTargetEp);
	if (NULL == ptNode || !ptNode->IsChanOn())
	{
		return FALSE;
	}

    TDiscussEpInfo* ptEpInfo = GetDiscussEpInfoById(wSelTargetEp);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{ // 不是讨论成员, 不用恢复分辨率

		MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::RestoreAdjustedResForSelEp  EpNotDisMember  ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n", 
			                   m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex));

		return TRUE;
	}

	if (ptEpInfo->m_bIsSmallChanOn )
	{  // 没有小码流的会场才会降分辨率，有小码流的会议不需要恢复操作，
		return TRUE;
	}


	if (ptNode->IsSingleVidSnd())
	{
		// 如果需要恢复的会场是单屏，直接恢复中间屏
        wScreenIndex = MIDSCREENINDEX;
	}


	BOOL32 errorflag = FALSE;
	u8 aAssignIndex[TP_MAX_STREAMNUM] = {0};

	u16 wIndex;
    s32 symbolflag = 1;
	u16 wCurIndex;

	if(wScreenIndex < TP_MAX_STREAMNUM)
	{// 恢复某屏

		if (NULL != ptEpInfo->m_apcBas[wScreenIndex])
		{   // 已经申请了，无须重复申请
			MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::RestoreAdjustedResForSelEp  ScreenBas != NULL  ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n", 
				    m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex));

			ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount++; // bas 引用计数（sel 使用）
			return TRUE;
		}
		
		if (!m_pcConf->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wScreenIndex]))
		{// 没有分配到适配, 不能恢复
			
			MdlError(Ums_Mdl_Call, ("RestoreAdjustedResForSelEp  no bas resource confid:%d  seltargetep:%d .\n", 
				m_pcConf->GetInsID(), wSelTargetEp));
			
			return FALSE;
		}

		ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount++;
		
		ptEpInfo->m_apcBas[wScreenIndex]->SetCB(DiscussBasCB, this);
		// 调整后适配格式
		TUmsVidFormat tVidFormat;
		tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
		tVidFormat.m_emRes = emTPV480x272;
		tVidFormat.m_wFrameRate = 15;
		m_pcConf->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wScreenIndex], ptEpInfo->m_wEpID, wScreenIndex, 1, &tVidFormat);
		
		if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wScreenIndex])
		{// 申请到了适配，恢复该屏分辨率，用于进大画面，小画面从适配出
			m_pcConf->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wScreenIndex, ptEpInfo->m_aemVideoRes[wScreenIndex], TRUE);
			ptEpInfo->m_aemVideoRes[wScreenIndex] = emTPVResEnd;
		}
	}
	else 
	{// 恢复会场所有屏

		symbolflag = 1;
		for (wIndex = 1; wIndex <= ptEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

			if (NULL != ptEpInfo->m_apcBas[wCurIndex])
			{// 已经申请了，无须重复申请
				MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::RestoreAdjustedResForSelEp  ScreenBas != NULL Continue ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n", 
					m_pcConf->GetInsID(), wSelTargetEp,  wCurIndex));

				continue;
			}
			
			if (!m_pcConf->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
			{// 没有分配到适配, 不能恢复
				
				MdlError(Ums_Mdl_Call, ("RestoreAdjustedResForSelEp  no bas resource confid:%d   seltargetep:%d .\n", 
					m_pcConf->GetInsID(), wSelTargetEp));
				
				errorflag = TRUE;
				break;
			}

			aAssignIndex[wCurIndex] = 1;
		}


		if (errorflag)
		{
            symbolflag = 1;
		    for (wIndex = 1; wIndex <= ptEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
			{
			    wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

				if (0 != aAssignIndex[wCurIndex])
				{
					m_pcConf->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wCurIndex]);
					ptEpInfo->m_apcBas[wCurIndex] = NULL;
				}
			}



			MdlError(Ums_Mdl_Call, ("RestoreAdjustedResForSelEp no enough bas resource  confid:%d  seltargetep:%d.\n", 
				m_pcConf->GetInsID(), wSelTargetEp));


			return FALSE;
		}



		symbolflag = 1;
		for (wIndex = 1; wIndex <= ptEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
		{
	        wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

			ptEpInfo->m_awBasUserinfo[wCurIndex].m_wSelUserCount++; //bas 引用计数
			
			ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
			// 调整后适配格式
			TUmsVidFormat tVidFormat;
			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
			tVidFormat.m_emRes = emTPV480x272;
			tVidFormat.m_wFrameRate = 15;
			m_pcConf->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
			
			if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
			{// 申请到了适配，恢复该屏分辨率，用于进大画面，小画面从适配出
				m_pcConf->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
				ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
			}

		}

	}


	CNetPortMgr::AdjustDiscussEpToBas(m_pcConf, ptEpInfo);


	// 刷新点VMP 的交换
	UmsDiscussOprCycle(wIndex, emDiscussObjEnd,
			m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustDstVidToVmpTpDsInfo(&m_tDiscussInfo, m_pcConf->curSpeakerID()););


	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{
		ptEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
		if (ptEpInfo->IsValid())
		{
			for (u16 wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
			{
				if (ptEpInfo->m_awGetIndex[wLoop] 
					< TP_UMS_MAX_CALLNUM)
				{
					m_pcConf->GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[wLoop], TRUE);
				}
				
				if (NULL != ptEpInfo->m_apcBas[wLoop])
				{
					m_pcConf->GetBas()->AskFrameToScreenBas(ptEpInfo->m_apcBas[wLoop]);
				}
			}
		}
	}

	return TRUE;
}


BOOL32  CUmsDiscussMgr::AdjustResForUnSelEp(u16 wSelTargetEp, u16 wScreenIndex)
{

	MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::AdjustResForUnSelEp  ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n", 
		m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex));
	
	if (!m_pcConf->IsChairConf())
	{
        return FALSE;
	}
	
	if (!IsDiscussModle())
	{
        return TRUE;
	}
	
	if (wScreenIndex > TP_MAX_STREAMNUM)
	{
        return FALSE;
	}
	
	TCallNode* ptNode = NULL;
	ptNode = m_pcConf->GetNodeMgr()->GetNode(wSelTargetEp);
	if (NULL == ptNode || !ptNode->IsChanOn())
	{
		return FALSE;
	}
	
    TDiscussEpInfo* ptEpInfo = GetDiscussEpInfoById(wSelTargetEp);
	if (NULL == ptEpInfo || !ptEpInfo->IsValid())
	{ // 不是讨论成员, 不用恢复分辨率
		return TRUE;
	}
	
	if (ptEpInfo->m_bIsSmallChanOn  )
	{  // 没有小码流的会场才会降分辨率，有小码流的会议不需要恢复操作，
		return TRUE;
	}

	BOOL32 bAdjustDs = FALSE;

	u16 wIndex;
    s32 symbolflag = 1;
	u16 wCurIndex;

    if(wScreenIndex < TP_MAX_STREAMNUM)
	{ //释放某一个屏

	  MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::AdjustResForUnSelEp  ConfID:%d, OprEpId:%d, ScreenIndex:%d, Userinfo[%d] = %d. \n", 
			m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex, wScreenIndex, ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount));
		
       if(ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount > 0)
	   {
           ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount--;

		   if (0 == ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount &&
			   0 == ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wDisUserCount)
		   {
			   
			   if (ptEpInfo->m_bMtAdjustRes)
			   {// 能降分辨率终端
				   if (NULL != ptEpInfo->m_apcBas[wScreenIndex])
				   {
					   m_pcConf->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wScreenIndex]);
					   ptEpInfo->m_apcBas[wScreenIndex] = NULL;
				   }
				   
				   if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wScreenIndex])
				   {// 降分辨率，进小画面
					   m_pcConf->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wScreenIndex, emTPV480x272);
					   ptEpInfo->m_aemVideoRes[wScreenIndex] = emTPV480x272;
				   }
				   
				   bAdjustDs = TRUE;
			   }
		   }
	   }


	}
	else
	{
		symbolflag = 1;
		for (wIndex = 1; wIndex <= ptEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
		{
	        wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;


			MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::AdjustResForUnSelEp  ConfID:%d, OprEpId:%d, ScreenIndex:%d, Userinfo[%d] = %d. \n", 
				m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex, wCurIndex, ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount));


			if(ptEpInfo->m_awBasUserinfo[wCurIndex].m_wSelUserCount > 0)
			{
				ptEpInfo->m_awBasUserinfo[wCurIndex].m_wSelUserCount--;

				if (0 == ptEpInfo->m_awBasUserinfo[wCurIndex].m_wSelUserCount &&
					0 == ptEpInfo->m_awBasUserinfo[wCurIndex].m_wDisUserCount)
				{
					
					if (ptEpInfo->m_bMtAdjustRes)
					{// 能降分辨率终端
						if (NULL != ptEpInfo->m_apcBas[wCurIndex])
						{
							m_pcConf->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wCurIndex]);
							ptEpInfo->m_apcBas[wCurIndex] = NULL;
						}
						
						if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex])
						{// 降分辨率，进小画面
							m_pcConf->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, emTPV480x272);
							ptEpInfo->m_aemVideoRes[wCurIndex] = emTPV480x272;
						}
						
						bAdjustDs = TRUE;
					}
				} 
			}
		}
	}



	if (bAdjustDs)
	{
		//所有屏都释放才清交换
		CNetPortMgr::AdjustDiscussEpToBas(m_pcConf, ptEpInfo);

		// 刷新点VMP 的交换
		UmsDiscussOprCycle(wIndex, emDiscussObjEnd,
			m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustDstVidToVmpTpDsInfo(&m_tDiscussInfo, m_pcConf->curSpeakerID()););	


		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			ptEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
			if (ptEpInfo->IsValid())
			{
				for (u16 wLoop = 0; wLoop < TP_MAX_STREAMNUM; wLoop++)
				{
					if (ptEpInfo->m_awGetIndex[wLoop] 
						< TP_UMS_MAX_CALLNUM)
					{
						m_pcConf->GetVidAudEx()->AskKeyFrame(ptEpInfo->m_awGetIndex[wLoop], TRUE);
					}
					
					if (NULL != ptEpInfo->m_apcBas[wLoop])
					{
						m_pcConf->GetBas()->AskFrameToScreenBas(ptEpInfo->m_apcBas[wLoop]);
					}
				}
			}
		}
	
	}


	return TRUE;
}


/////////////////////////////////////////////////////////////////////
/////////////////////////讨论目标操作类//////////////////////////////
/////////////////////////////////////////////////////////////////////

//////////////////////////////////////////
////////////// 基类目标实现 //////////////
//////////////////////////////////////////
void CDiscussObjectBase::Init()
{
	m_tDstEpInfo.Clear();
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		m_atVmpTp[wIndex].Clear();
		m_atMix[wIndex].Clear();
	}
	return;
}

void CDiscussObjectBase::Show()
{
	msgprintnotime("[%s]\n", GetObjTypeName(m_emDisObj));
	
	ShowDstInfo(&m_tDstEpInfo);
	
	ShowResourse();
	
	msgprintnotime("\n");
}

EmDiscussRspRet CDiscussObjectBase::AssignResource( CUmsConfInst* param )
{// 单屏目标资源申请，重载处理
	u16 wIndex = 0;	

	m_atVmpTp[wIndex].m_pcVmpTpRes = m_pcConf->GetVmpServiceHandle()->Assign(DiscussVmpCB, param);		
	if (NULL == m_atVmpTp[wIndex].m_pcVmpTpRes)
	{
		return em_Start_AssginVmpFail;
	}
	m_atMix[wIndex].m_ptMixRes = m_pcConf->GetEapu()->AssignMixer(DiscussMixCB, param, UMS_VMP_MAX_RCV, TP_MAX_STREAMNUM);
	if (NULL == m_atMix[wIndex].m_ptMixRes)
	{
		return em_Start_AssignMixFail;
	}
	u32 dwNode = m_atMix[wIndex].m_ptMixRes->m_tEqpRes.m_dwEqpNode; // 保证三屏用的混音器来自同一个apu2板卡

	for (wIndex = 1; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		m_atVmpTp[wIndex].m_pcVmpTpRes = m_pcConf->GetVmpServiceHandle()->Assign(DiscussVmpCB, param);		
		if (NULL == m_atVmpTp[wIndex].m_pcVmpTpRes)
		{
			return em_Start_AssginVmpFail;
		}
		m_atMix[wIndex].m_ptMixRes = m_pcConf->GetEapu()->AssignMixer(DiscussMixCB, param, UMS_VMP_MAX_RCV, TP_MAX_STREAMNUM, dwNode);
		if (NULL == m_atMix[wIndex].m_ptMixRes)
		{
			return em_Start_AssignMixFail;
		}
	}
	
	return em_DiscussOprRsp_Ok;
}

void CDiscussObjectBase::FreeResource()
{// 单屏目标资源释放，重载处理
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (NULL != m_atVmpTp[wIndex].m_pcVmpTpRes)
		{
			m_pcConf->GetVmpServiceHandle()->Release(m_atVmpTp[wIndex].m_pcVmpTpRes);
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_atVmpTp[wIndex].m_cToVmpDsInfo);
		}
		if (NULL != m_atMix[wIndex].m_ptMixRes)
		{
			m_pcConf->GetEapu()->ReleaseMixer(m_atMix[wIndex].m_ptMixRes);
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_atMix[wIndex].m_cToMixDsInfo);
		}
	}
	Init();
	return;
}

void CDiscussObjectBase::ShowResourse()
{// 单屏目标资源查看，重载处理
	TAudMixInfo* pMix = NULL;
	const CBaseService* pVmp = NULL;

	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		pMix = m_atMix[wIndex].m_ptMixRes;
		if (NULL != pMix)
		{
#ifdef _USE_XMPUEQP_
			msgprintnotime(" %d-MixEqpId:%d, ChanNum:%d.\n", wIndex,
				pMix->m_tEqpRes.m_byEqpID, pMix->m_tEqpRes.m_wChanNum);
#else
			msgprintnotime(" %d-MixId:%d, ChanNum:%d, UmsStartPort:%d, EqpRtpStartPort:%d, EqpRtcpstartPort:%d, \n", wIndex,
				pMix->m_tEqpRes.m_byEqpID, pMix->m_tEqpRes.m_wChanNum, pMix->m_tEqpRes.m_wUmsStartPort, pMix->m_tEqpRes.m_wEqpStartPort,
				pMix->m_tEqpRes.m_wEqpRtcpStartPort);
#endif
		}
	}
	
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		pVmp = m_atVmpTp[wIndex].m_pcVmpTpRes;
		if (NULL != pVmp)
		{
			m_pcConf->GetVmpServiceHandle()->Show(pVmp);
		}
	}

	return;
}

const CBaseService* CDiscussObjectBase::GetVmpRes( u16 wScreenIndex )
{// 单屏目标资源重载处理
	if (wScreenIndex < TP_MAX_STREAMNUM)
	{
		return m_atVmpTp[wScreenIndex].m_pcVmpTpRes;
	}
	return NULL;
}

TAudMixInfo* CDiscussObjectBase::GetMixRes( u16 wScreenIndex )
{// 单屏目标资源重载处理
	if (wScreenIndex < TP_MAX_STREAMNUM)
	{
		return m_atMix[wScreenIndex].m_ptMixRes;
	}
	return NULL;
}

void CDiscussObjectBase::AdjustDstEpInfo(TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo, u16 wSpeakerId)
{
	MdlHint(Ums_Mdl_Call, ("[AdjustDstEpInfo] ConfId:%d, OprType:%s, OprEp:%d, ObjName:%s\n", m_pcConf->GetInsID(), 
		GetOprTypeName(tOprInfo.m_emOprType), tOprInfo.m_wEpID, GetObjTypeName(m_emDisObj)));
	TCallNode* ptSpeakerNode = m_pcConf->GetNodeMgr()->GetNode(wSpeakerId);	
	if (NULL == ptSpeakerNode || !ptSpeakerNode->IsChanOn())
	{// 这个node是讨论内的确定的发言会场，不一定等于m_pcConf->currspeakerID
		m_tDstEpInfo.Clear();
		ptDiscussInfo->ResetSpecialEp();
		return;
	}

	if (NULL == ptDiscussInfo->GetFirstVaildEp(wSpeakerId))
	{// 讨论内里面只有一个发言会场，目标信息需要清空
		m_tDstEpInfo.Clear();
		ptDiscussInfo->ResetSpecialEp();
		return;
	}
	
	switch (tOprInfo.m_emOprType)
	{
	case EmDisChnAllStart:
		{
			ptDiscussInfo->ResetSpecialEp();
			InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
		}
		break;
	case EmDisChnAddEp:
	case EmDisChnEpConnect:
		{
			UptateDstEpInfoByAdd(ptSpeakerNode, ptDiscussInfo);
		}
		break;
	case EmDisChnEpDisConnect:
	case EmDisChnDelEp:
		{
			UptateDstEpInfoByDel(ptSpeakerNode, ptDiscussInfo);
		}
		break;
	case EmDisChnEpChangeSeat:
		{// 
			UptateDstEpInfoByChangeSeat(ptSpeakerNode, ptDiscussInfo, tOprInfo);
		}
		break;
	case EmDisChnChangeSpeakerEp:
		{
			UptateDstEpInfoByChangeSpeaker(ptSpeakerNode, ptDiscussInfo);
		}
		break;
	default:
		{
			return;
		}
	}
	
#ifdef _WIN32
	Show();
#endif
	
	return;
}

void CDiscussObjectBase::AdjustApu2MixForceActiveInfo( u16 wSpeakerId, BOOL32 bForceActiveOn )
{
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (NULL != m_atMix[wIndex].m_ptMixRes)
		{
			m_pcConf->GetEapu()->AdjustForceActive(m_atMix[wIndex].m_ptMixRes, bForceActiveOn ? wSpeakerId : TP_INVALID_INDEX);
		}
	}

	return;
}

void CDiscussObjectBase::GetVmpMemberEpByIndex(u16 wScreenIndex, u16 wMemberIndx, TPOUT u16& wEpId, TPOUT u16& wSeatIndex)
{
	if (wScreenIndex < TP_MAX_STREAMNUM && wMemberIndx < UMS_VMP_MAX_RCV)
	{
		wEpId = m_tDstEpInfo.m_atScreenInfo[wScreenIndex].m_atMember[wMemberIndx].GetHandleOne();
		wSeatIndex = m_tDstEpInfo.m_atScreenInfo[wScreenIndex].m_atMember[wMemberIndx].GetHandleTwo();
	}
	return;
}

BOOL32 CDiscussObjectBase::IsDiscussObjDstEp(u16 wEpId, u16 wScreenIndex)
{//确定某个会场的屏是否属于目标的大图像（即需不需要大图像）
	return VALID_SCREEN_INDEX(m_tDstEpInfo.GetIndexByEp(wEpId, wScreenIndex));
}

TDiscussDstEpInfo* CDiscussObjectBase::GetDiscussObj()
{
	return &m_tDstEpInfo;
}

void CDiscussObjectBase::FillUpSingleScrEp(TDiscussInfo* ptDiscussInfo, TDiscussDstEpInfo* ptDstEpInfo, TDiscussDstEpInfo* ptDstEpTemp /* = NULL */)
{// 给空闲状态的屏，填充单屏会场作为目标
	u16 wIndex = 0;
	u16 wEpId = 0;
	u16 wAddIndex = 0;
	TCallNode* ptNode = NULL;
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{
		wEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
		if (!TP_VALID_HANDLE(wEpId))
		{
			break;
		}
		
		wAddIndex = ptDstEpInfo->FindIdleScrIndex();
		if (!VALID_SCREEN_INDEX(wAddIndex))
		{
			break;
		}
		
		ptNode = m_pcConf->GetNode(wEpId);
		if (NULL != ptNode && ptNode->IsSingleVidSnd() && ptNode->IsInMix())
		{
			if (!VALID_SCREEN_INDEX(ptDstEpInfo->GetIndexByEp(ptNode->m_wEpID)))
			{
				ptDstEpInfo->AddDstEp(ptNode, MIDSCREENINDEX, wAddIndex);
				if (NULL != ptDstEpTemp && MIDSCREENINDEX == wAddIndex)
				{
					AdjustDstForSpecialEp(wAddIndex, ptNode, ptDiscussInfo);
				}
			}
		}
	}
	return;
}


void CDiscussObjectBase::FillUpThreeScrEp(TDiscussDstEpInfo* ptDstEpInfo)
{// 三屏目标中，删除会场或会场掉线，可能会导致大图像为空，尝试把其他屏目标上的三屏会场加进来（对应屏）
	u16 wThreeScrEp = ptDstEpInfo->FindThreeScreenDstEp();
	if (TP_INVALID_INDEX == wThreeScrEp)
	{// 没有三屏会场作为目标返回
		return;
	}

	TCallNode* ptNode = m_pcConf->GetNodeMgr()->GetNode(wThreeScrEp);
	if (NULL == ptNode || !ptNode->IsThreeVidSnd())
	{
		MdlError(Ums_Mdl_Call, ("[CDiscussObjectBase::FillUpThreeScrEp] ptNode is not vaild, IsNull:%d!\n", (NULL == ptNode)?1:0));
		return;
	}

	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (!ptDstEpInfo->m_atScreenInfo[wIndex].IsDstEpValid())
		{
			ptDstEpInfo->AddDstEp(ptNode, wIndex, wIndex);
		}
	}
	return;
}


void CDiscussObjectBase::CheckOutDstInfo( TDiscussInfo* ptDiscussInfo, TDiscussDstEpInfo* ptDstEpInfo)
{// 检查下目标会场是否还在讨论中，不在的话，删除
	u16 wIndex = 0;
	u16 wEpId = 0;
	TDiscussEpInfo* pEpInfo = NULL;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		wEpId = ptDstEpInfo->m_atScreenInfo[wIndex].m_atMember[0].GetHandleOne();
		if (0 != wEpId)
		{
			pEpInfo = ptDiscussInfo->FindEpById(wEpId);
			if (NULL == pEpInfo)
			{
				ptDstEpInfo->m_atScreenInfo[wIndex].ClearDstEpInfo();
			}
		}
	}
	return;
}

void CDiscussObjectBase::AdjustDstForSpecialEp( u16 wAddIndex, TCallNode* ptNode, TDiscussInfo* ptDiscussInfo )
{// 此函数目的：保证目标在wAddIndex上是ptNode
	// 可能情形：1. ptNode不在目标中，那么ptNode取代wAddIndex的原有目标
	// 2. ptNode在目标中，但是不在wAddIndex上，那么将wAddIndex的原有目标和ptNode对调
	if (VALID_SCREEN_INDEX(wAddIndex))
	{
		u16 wTempEp = ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wAddIndex].m_atMember[0].GetHandleOne();
		u16 wIndex = ptDiscussInfo->m_tSpecialDst.GetIndexByEp(ptNode->m_wEpID);
		
		if (!VALID_SCREEN_INDEX(wIndex))
		{
			ptDiscussInfo->m_tSpecialDst.AddDstEp(ptNode, MIDSCREENINDEX, wAddIndex);
		}
		else
		{
			if (wIndex != wAddIndex)
			{
				ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex].ClearDstEpInfo();
				ptDiscussInfo->m_tSpecialDst.AddDstEp(ptNode, MIDSCREENINDEX, wAddIndex);
				
				TCallNode* ptNodeTemp = m_pcConf->GetNode(wTempEp);
				if (NULL != ptNodeTemp && ptNodeTemp->IsSingleVidSnd() && ptNodeTemp->IsInMix())
				{
					ptDiscussInfo->m_tSpecialDst.AddDstEp(ptNodeTemp, MIDSCREENINDEX, wIndex);
				}
			}
		}
	}
	return;
}

void CDiscussObjectBase::AdjustVmpEpInfoForThreeScreen(TDiscussInfo* ptDiscussInfo)
{// 对三屏，按先中间，后左边，再右边的顺序轮流依次添加会场进小图像，先添三屏，再添单屏
// 主会场在讨论中，则始终在中间屏的前面
	u16 wIndex = 0;
	u16 wAddEpId = 0;
	u16 wAddIndex = MIDSCREENINDEX;
	TCallNode* ptAddNode = NULL;
	
	// 先清空
	UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
		m_tDstEpInfo.m_atScreenInfo[wIndex].ClearVmpEpInfo());

	BOOL32 bIsChairSingle = FALSE;
	wAddEpId = m_pcConf->chairID();
	ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
	if (NULL != ptAddNode && ptAddNode->IsVidSndValid() && ptAddNode->IsInMix())
	{// 主会场在讨论中，放在中间的前面
		m_tDstEpInfo.AddVmpDstEp(ptAddNode, wAddIndex);
		wAddIndex = GetNextIndex(wAddIndex);
		bIsChairSingle = ptAddNode->IsSingleVidSnd();
	}

	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{// 按屏顺序加3屏
		wAddEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
		if (!TP_VALID_HANDLE(wAddEpId))
		{
			break;
		}

		if (wAddEpId == m_pcConf->chairID())
		{// 主席排除，避免重复
			continue;
		}

		ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
		if (NULL != ptAddNode && ptAddNode->IsInMix() && ptAddNode->IsThreeVidSnd())
		{
			m_tDstEpInfo.AddVmpDstEp(ptAddNode, wAddIndex);
			wAddIndex = GetNextIndex(wAddIndex);
		}
	}

	u16 wAddNum = 0;
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{// 按屏顺序加单屏
		wAddEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
		if (!TP_VALID_HANDLE(wAddEpId))
		{
			break;
		}

		if (wAddEpId == m_pcConf->chairID())
		{// 主席排除，避免重复
			continue;
		}

		ptAddNode = m_pcConf->GetNode(wAddEpId);
		if (NULL != ptAddNode && ptAddNode->IsInMix() && ptAddNode->IsSingleVidSnd())
		{

			if (bIsChairSingle)
			{// 主会场是单屏，中间屏需要补两个单屏，以保证对称
				m_tDstEpInfo.AddVmpDstEp(ptAddNode, MIDSCREENINDEX);
				wAddNum++;
				if (2 == wAddNum)
				{
					bIsChairSingle = FALSE;
					wAddNum = 0;
				}
			}
			else
			{
				m_tDstEpInfo.AddVmpDstEp(ptAddNode, wAddIndex);
				wAddNum++;
				if (TP_MAX_STREAMNUM == wAddNum)
				{// 单屏添加满3个再换下一个屏
					wAddIndex = GetNextIndex(wAddIndex);
					wAddNum = 0;
				}
			}
		}
	}
	return;
}

void CDiscussObjectBase::AdjustVmpEpInfoForSingleScreen( TDiscussInfo* ptDiscussInfo )
{// 对单屏，优先添加主会场，其次大图像是一个三屏，也优先添加显示其所有坐席，再次添加有发言记录的会场，最后有剩余再添加
	u16 wIndex = 0;
	u16 wAddEpId = 0;
	TCallNode* ptAddNode = NULL;
	TDiscussEpInfo* ptEpInfo = NULL;
	// 先清空
	m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX].ClearVmpEpInfo();

	wAddEpId = m_pcConf->chairID();
	ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
	if (NULL != ptAddNode && ptAddNode->IsVidSndValid() && ptAddNode->IsInMix())
	{// 主会场在讨论中，放在前面
		m_tDstEpInfo.AddVmpDstEp(ptAddNode, MIDSCREENINDEX);
	}

	// 如果大图像是一个三屏会场，优先把其余坐席也加进小画面
	if (m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX].IsDstEpThreeScr())
	{
		wAddEpId = m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX].m_atMember[0].GetHandleOne();
		ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
		if (NULL != ptAddNode && ptAddNode->IsInMix() && ptAddNode->IsThreeVidSnd())
		{
			m_tDstEpInfo.AddVmpDstEp(ptAddNode, MIDSCREENINDEX);
		}
	}

	TDiscussSpeakerRec* pSpeakerRec = &ptDiscussInfo->m_tSpeakerRec;	
	for (wIndex = 1; wIndex < UmsDiscuss_VmpEp_Max_Num; wIndex++)
	{// 优先添加发过言的会场(Index从1开始，因为0为当前发言会场)
		wAddEpId = pSpeakerRec->m_awSpeakerRec[wIndex];
		if (0 == wAddEpId)
		{
			break;
		}
		
		ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
		if (NULL != ptAddNode && ptAddNode->IsInMix() && ptAddNode->IsVidSndValid())
		{
			m_tDstEpInfo.AddVmpDstEp(ptAddNode, MIDSCREENINDEX);
		}
	}
	
	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{// 添加其余会场
		wAddEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
		if (!TP_VALID_HANDLE(wAddEpId))
		{
			break;
		}

		ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
		if (NULL != ptAddNode && ptAddNode->IsInMix() && ptAddNode->IsVidSndValid())
		{
			m_tDstEpInfo.AddVmpDstEp(ptAddNode, MIDSCREENINDEX);
		}
	}
	return;
}

void CDiscussObjectBase::GetVmpEncParam( TVmpEncParam& tEncParam, TCallNode* ptNode, BOOL32 bSnd )
{
	if (bSnd)
	{
		TCapNode* ptFatherNode = m_pcConf->GetNodeMgr()->GetForeFatherNode(ptNode); 
		// 这里的ptNode可能是下级的会场，进上级的发言人适配，是按照级联格式来的

		tEncParam.m_byEncType = CTpTypeAdpt::GetVidPayloadValue(ptFatherNode->m_tVidSndFormat.m_tFormat.m_emFormat);
		tEncParam.m_byFrameRate = ptFatherNode->m_tVidSndFormat.m_tFormat.m_wFrameRate;
		if ( ptFatherNode->m_tVidSndFormat.m_tFormat.m_emQualityLvl == emTPH264HP )
		{
			tEncParam.m_byProfileType = 1;
		}
		else if( ptFatherNode->m_tVidSndFormat.m_tFormat.m_emQualityLvl == emTPH264BP )
		{
			tEncParam.m_byProfileType = 0;
		}
		tEncParam.m_wBitRate = ptFatherNode->m_tVidSndFormat.m_tFormat.m_wBitrate;
		CTpTypeAdpt::GetWHByVidResolution(ptFatherNode->m_tVidSndFormat.m_tFormat.m_emRes,
			tEncParam.m_wVideoWidth, tEncParam.m_wVideoHeight);
		
		if( CUmsConfigEx::GetInstance()->GetEnc3060Vmp() )
		{
			//广播类合成器，不再出25 或 50的 防止：T300接收制式为60，导致画面卡顿
			if ( tEncParam.m_byFrameRate == VID_FRAME_RATE_25 )
			{
				tEncParam.m_byFrameRate = VID_FRAME_RATE_30;
			}
			if ( tEncParam.m_byFrameRate == VID_FRAME_RATE_50 )
			{
				tEncParam.m_byFrameRate = VID_FRAME_RATE_60;
			}
		}

	}
	else
	{
		tEncParam.m_byEncType = CTpTypeAdpt::GetVidPayloadValue(ptNode->m_tVidRcvFormat.m_tFormat.m_emFormat);
		tEncParam.m_byFrameRate = ptNode->m_tVidRcvFormat.m_tFormat.m_wFrameRate;
		if ( ptNode->m_tVidRcvFormat.m_tFormat.m_emQualityLvl == emTPH264HP )
		{
			tEncParam.m_byProfileType = 1;
		}
		else if( ptNode->m_tVidRcvFormat.m_tFormat.m_emQualityLvl == emTPH264BP )
		{
			tEncParam.m_byProfileType = 0;
		}
		tEncParam.m_wBitRate = ptNode->m_tVidRcvFormat.m_tFormat.m_wBitrate;
		CTpTypeAdpt::GetWHByVidResolution(ptNode->m_tVidRcvFormat.m_tFormat.m_emRes,
			tEncParam.m_wVideoWidth, tEncParam.m_wVideoHeight);
	}
	return;
}

void CDiscussObjectBase::GetVmpStyleInfo(TVmpStyleInfo& tVmpStylle, TDiscussScreenInfo* ptInfo, BOOL32 bUseSmallSenvenStyle)
{// 讨论内总屏数大于18，1大6小画面风格需要用小的
	tVmpStylle.m_byMemberNum = ptInfo->m_wVmpEpNum + 1; // 小图像加一路大图像，即使大图像目标是空的
	tVmpStylle.m_emShowMode = ums_vmp_lastframe_mode;

	//////////////////////////////////////////////////////////////////////////
	if ( tVmpStylle.m_byMemberNum < 7 || (tVmpStylle.m_byMemberNum == 7 && !bUseSmallSenvenStyle))
	{
		tVmpStylle.m_emVmpStyle = (EmUmsVmpStyle)(tVmpStylle.m_byMemberNum);
	}
	else
	{
		tVmpStylle.m_emVmpStyle = (EmUmsVmpStyle)(tVmpStylle.m_byMemberNum+1);
	}

	// 第0路，即使没有目标，dwHandle不能填0，否则vmp认为无效，这里填个TP_INVALID_INDEX;
	tVmpStylle.m_atDoublePayload[0] = ptInfo->m_atPayload[0];
	tVmpStylle.m_atMemberInfo[0].m_dwHandle = (0 != ptInfo->m_atMember[0].m_dwHandle)?ptInfo->m_atMember[0].m_dwHandle:TP_INVALID_INDEX;
	tVmpStylle.m_atMemberInfo[0].m_bMerged = ptInfo->m_atMember[0].m_bMerged;

	u16 wIndex;
	for (wIndex = 1; wIndex < UMS_VMP_MAX_RCV; wIndex++)
	{
		tVmpStylle.m_atDoublePayload[wIndex] = ptInfo->m_atPayload[wIndex];
		tVmpStylle.m_atMemberInfo[wIndex] = ptInfo->m_atMember[wIndex];
	}
	return;
}

void CDiscussObjectBase::GetNewMixMember(TAudMixMemberInfo& tNewMixMember, TDiscussDstEpInfo* tScreenInfo, u16 wScreenIndex, u16 wThreeScreenEp)
{// 保证三屏会场收到的声音不重复，new: 三屏目标中，大图像如果有三屏会场（最多只有一个），此三屏会场坐席对应进三个混音器
	TDiscussScreenInfo* pScrInfo = &tScreenInfo->m_atScreenInfo[wScreenIndex];

	u16 wOprEp = 0;
	u16 wLoop = 0;

	wOprEp = pScrInfo->m_atMember[0].GetHandleOne();
	wLoop = pScrInfo->m_atMember[0].GetHandleTwo();

	if (wThreeScreenEp >0 && wThreeScreenEp < TP_CONF_MAX_CNSNUM)
	{
		tNewMixMember.AddMixMember(wThreeScreenEp, wScreenIndex); // 有三屏会场目标，对应屏进对应混音器
	}

	if (wOprEp > 0 && wOprEp < TP_CONF_MAX_CNSNUM && wOprEp != wThreeScreenEp)
	{
		tNewMixMember.AddMixMember(wOprEp, wLoop); // 先把大图对应会场座席加进混音器
	}

	for (u16 wIndex = 1; wIndex < UMS_VMP_MAX_RCV;)
	{// 遍历小图像
		if (0 == pScrInfo->m_atMember[wIndex].m_dwHandle)
		{
			break;
		}
		wOprEp = pScrInfo->m_atMember[wIndex].GetHandleOne();
		if (wOprEp == pScrInfo->m_atMember[wIndex+1].GetHandleOne())
		{// 小图像是个3屏
			if (!VALID_SCREEN_INDEX(tScreenInfo->GetIndexByEp(wOprEp)))
			{// 小图像和大图像没有重复，进混音
				tNewMixMember.AddMixMember(wOprEp, TP_MAX_STREAMNUM);
			}
			wIndex+=3;
		}
		else
		{
			if (!VALID_SCREEN_INDEX(tScreenInfo->GetIndexByEp(wOprEp)))
			{
				tNewMixMember.AddMixMember(wOprEp, MIDSCREENINDEX);
			}
			wIndex++;
		}
	}

#ifdef _WIN32
	msgprintnotime("[%s]-[MixAudMember]-[%d]\n", GetObjTypeName(m_emDisObj), wScreenIndex);
	ShowMixMember(&tNewMixMember, wScreenIndex);
#endif

	return;
}

//////////////////////////////////////////
////////////// 发言会场目标 //////////////
//////////////////////////////////////////
void CDiscussObjectForSpeakerEp::AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId)
{// 发言会场是单屏还是三屏，需要区分
	TCallNode* ptSpeaker = m_pcConf->GetNodeMgr()->GetNode(wSpeakerId);
	if (NULL == ptSpeaker || !ptSpeaker->IsVidSndValid())
	{
		return;
	}

	BOOL32 bFlag = TRUE;
	TCallNode* ptSpecialNode = m_pcConf->GetNodeMgr()->GetNode(ptDiscussInfo->m_wSpecialEp);
	if (NULL == ptSpecialNode || !ptSpecialNode->IsVidSndValid())
	{
		bFlag = FALSE;
	}

	TDiscussScreenInfo* pScrInfo = NULL;
	TVmpUseParam tVmpParam;
	TTPEncrypt tEncrypt = m_pcConf->GetConfEncryptInfo();
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{	

		if (ptSpeaker->IsSingleVidSnd() && MIDSCREENINDEX != wIndex && bFlag)
		{// 单屏发言时，两边合成器给specialEp会场用
			pScrInfo = &ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex];
			GetVmpEncParam(tVmpParam.m_tEncParam, ptSpecialNode, FALSE); // 按specialEp会场接收格式出（这个会场是下级会场，也需要按这个会场的接收格式出，而不是级联格式）	
		}
		else if (ptSpeaker->IsSingleVidSnd() && MIDSCREENINDEX != wIndex)
		{// 单屏发言，两边合成器用不到时，无须调整
			continue;
		}
		else
		{
			pScrInfo = &m_tDstEpInfo.m_atScreenInfo[wIndex];
			GetVmpEncParam(tVmpParam.m_tEncParam, ptSpeaker, FALSE); // 发言会场目标，按发言会场接收格式出 （这个会场是下级会场，也需要按这个会场的接收格式出，而不是级联）	
		}

		memcpy(&tVmpParam.m_tEncrypt, &tEncrypt, sizeof(TTPEncrypt));
		GetVmpStyleInfo(tVmpParam.m_tStyleInfo, pScrInfo, ptDiscussInfo->m_wTotalScreenNum > 18);
		if (m_atVmpTp[wIndex].m_bIsVmpStart)
		{
			m_pcConf->GetVmpServiceHandle()->ChangeMode(m_atVmpTp[wIndex].m_pcVmpTpRes, &tVmpParam);
		}
		else
		{
			m_pcConf->GetVmpServiceHandle()->Start(m_atVmpTp[wIndex].m_pcVmpTpRes, &tVmpParam);
			m_atVmpTp[wIndex].m_bIsVmpStart = TRUE;
		}
		tVmpParam.Clear();
		
		CNetPortMgr::AdjustDiscussObjToVmpTp(m_pcConf, &m_atVmpTp[wIndex], pScrInfo);
	}
	return;
}

void CDiscussObjectForSpeakerEp::AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId)
{// 发言会场是单屏还是三屏，需要区分
	TCallNode* ptSpeaker = m_pcConf->GetNodeMgr()->GetNode(wSpeakerId);
	if (NULL == ptSpeaker || !ptSpeaker->IsVidSndValid())
	{
		return;
	}

	TDiscussDstEpInfo* ptDstInfo = NULL;
	if (ptSpeaker->IsSingleVidSnd() && ptDiscussInfo->IsSpecialEpVaild())
	{// 单屏发言且特殊会场存在，发言人的三个混音器全部给这个特殊会场使用 （单屏会场发言，听n-1混音）
		ptDstInfo = &ptDiscussInfo->m_tSpecialDst;
	}
	else if (ptSpeaker->IsSingleVidSnd())
	{// 单屏发言，没有特殊会场，这三个混音器暂时闲置
		return;
	}
	else
	{
		ptDstInfo = &m_tDstEpInfo;
	}

	u16 wThreeScreenDstEp = ptDstInfo->FindThreeScreenDstEp();
	u16 wIndex = 0;
	TAudMixMemberInfo tMemberInfo;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		tMemberInfo.Clear();
		GetNewMixMember(tMemberInfo, ptDstInfo, wIndex, wThreeScreenDstEp);
		m_pcConf->GetEapu()->AdjustAudMixMember(m_atMix[wIndex].m_ptMixRes, &tMemberInfo, wThreeScreenDstEp, wIndex);
		CNetPortMgr::AdjustDiscussObjToMix(m_pcConf, &m_atMix[wIndex], &tMemberInfo);
	}

	u8 byChanId = 0xff;
	TMixSync pMixSync;
	pMixSync.m_bSpeakerObject = TRUE;//发言人目标
	if (wThreeScreenDstEp > 0 && wThreeScreenDstEp < TP_CONF_MAX_CNSNUM)
	{// 有三屏会场作为大图像，找到对应坐席进对应混音器的的通道索引
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			byChanId = m_atMix[wIndex].m_ptMixRes->GetIndx(wThreeScreenDstEp, wIndex);

			pMixSync.Add(m_atMix[wIndex].m_ptMixRes, byChanId);
			m_atMix[wIndex].m_ptMixRes->SetSyncChnl(byChanId);
		}
		// 设置同步
		m_pcConf->GetEapu()->SetMixerSyncChnl(pMixSync);
	}
	else
	{// 取消同步 to do ...

		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			pMixSync.Add(m_atMix[wIndex].m_ptMixRes, byChanId);
			m_atMix[wIndex].m_ptMixRes->SetSyncChnl(byChanId);
		}

		m_pcConf->GetEapu()->SetMixerSyncChnl(pMixSync);
	}

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{	
		m_pcConf->GetEapu()->CheckDelMember(m_atMix[wIndex].m_ptMixRes);
	}

	return;
}


void CDiscussObjectForSpeakerEp::UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo)
{
	TDiscussScreenInfo* pScrInfo = NULL;
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{	
		
		if (NULL == m_atVmpTp[wIndex].m_pcVmpTpRes)
		{
			continue;
		}
		
		if (wIndex != MIDSCREENINDEX && ptDiscussInfo->IsSpecialEpVaild())
		{
			pScrInfo = &ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex];
		}
		else
		{
			pScrInfo = &m_tDstEpInfo.m_atScreenInfo[wIndex];
		}

		if (!pScrInfo->IsScreenValid())
		{
			continue;
		}
		
		CNetPortMgr::AdjustDiscussObjToVmpTp(m_pcConf, &m_atVmpTp[wIndex], pScrInfo);
	}
	return;
}


void CDiscussObjectForSpeakerEp::UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex)
{
	u8 byAdd = 0;
	
	TDiscussScreenInfo* pScrInfo0 = NULL;
	TDiscussScreenInfo* pScrInfo1 = NULL;
	TDiscussScreenInfo* pScrInfo2 = NULL;
	
	u8 abyFlag0[UMS_VMP_MAX_RCV] = {0};
	u8 abyFlag1[UMS_VMP_MAX_RCV] = {0};
	u8 abyFlag2[UMS_VMP_MAX_RCV] = {0};
	u8 byAdjust0 = 0;
	u8 byAdjust1 = 0;
	u8 byAdjust2 = 0;
	
	
	u8 byCanId = 0;
	u16 wEpId = 0;
	u16 wLoop = 0;
	BOOL32 bRet = FALSE;
	
	if (ptDiscussInfo->IsSpecialEpVaild())
	{
		pScrInfo0 = &ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[0];
		pScrInfo1 = &m_tDstEpInfo.m_atScreenInfo[1];
		pScrInfo2 = &ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[2];
	}
	else
	{
		pScrInfo0 = &m_tDstEpInfo.m_atScreenInfo[0];
		pScrInfo1 = &m_tDstEpInfo.m_atScreenInfo[1];
		pScrInfo2 = &m_tDstEpInfo.m_atScreenInfo[2];
	}
	
	for (wLoop = 0; wLoop < byNum; wLoop++)
	{
		byCanId = byChanId[wLoop];
		if (byCanId >= TP_APU2_MAX_CHAN_NUM)
		{
			break;
		}
		
		if (ptMixInfo->m_atChnl[byCanId].m_wScrIndx > TP_MAX_STREAMNUM)
		{// 双流忽略
			continue;
		}
		
		wEpId = ptMixInfo->m_atChnl[byCanId].m_wEpID;			
		
		bRet = pScrInfo0->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust0 = 1;
			abyFlag0[byAdd] = 1;
			if (bRet)
			{// 三屏小图像，有一个亮全部亮
				abyFlag0[byAdd+1] = 1;
				abyFlag0[byAdd+2] = 1;
			}
		}
		
		bRet = pScrInfo1->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust1 = 1;
			abyFlag1[byAdd] = 1;
			if (bRet)
			{// 三屏小图像，有一个亮全部亮
				abyFlag1[byAdd+1] = 1;
				abyFlag1[byAdd+2] = 1;
			}
		}
		
		bRet = pScrInfo2->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust2 = 1;
			abyFlag2[byAdd] = 1;
			if (bRet)
			{// 三屏小图像，有一个亮全部亮
				abyFlag2[byAdd+1] = 1;
				abyFlag2[byAdd+2] = 1;
			}
		}

	}
	
	if (byAdjust0)
	{
		m_pcConf->GetVmpServiceHandle()->UpdateSpeakerSideLine(m_atVmpTp[0].m_pcVmpTpRes, abyFlag0, UMS_VMP_MAX_RCV);
	}
	
	if (byAdjust1)
	{
		m_pcConf->GetVmpServiceHandle()->UpdateSpeakerSideLine(m_atVmpTp[1].m_pcVmpTpRes, abyFlag1, UMS_VMP_MAX_RCV);
	}
	
	if (byAdjust2)
	{
		m_pcConf->GetVmpServiceHandle()->UpdateSpeakerSideLine(m_atVmpTp[2].m_pcVmpTpRes, abyFlag2, UMS_VMP_MAX_RCV);
	}
	
	return;
}

// 初始状态：1. 发言会场优先看主会场，其次优先三屏，再其次单屏
void CDiscussObjectForSpeakerEp::InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	// 先清空
	m_tDstEpInfo.Clear();

	u16        wIndex = 0;
	u16        wEpId  = 0;
	TCallNode* ptNode = NULL;

	// 优先主会场
	wEpId = m_pcConf->chairID();
	ptNode = m_pcConf->GetNode(wEpId);
	if (wEpId == ptSpeakerNode->m_wEpID || NULL == ptNode || !ptNode->IsVidSndValid() || !ptNode->IsInMix())
	{// 主会场是发言会场或主会场不在讨论中，则在讨论列表中寻找
		u16 wEpIdTemp1 = 0;  // 记录第一个三屏会场
		u16 wEpIdTemp2 = 0;  // 记录第一个单屏会场
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			wEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
			if (!TP_VALID_HANDLE(wEpId))
			{
				break;
			}
			
			if (wEpId == ptSpeakerNode->m_wEpID)
			{// 排除自己
				continue;
			}
			
			ptNode = m_pcConf->GetNode(wEpId);
			if (NULL != ptNode && ptNode->IsInMix())
			{
				if (ptNode->IsThreeVidSnd())
				{// 找到三屏，跳出循环
					wEpIdTemp1 = wEpId;
					break;
				}
				else if (ptNode->IsSingleVidSnd())
				{// 只记录第一个单屏
					if (0 == wEpIdTemp2)
					{
						wEpIdTemp2 = wEpId;
					}
				}
				else
				{
					continue;
				}
			}
		}

		// 优先三屏，其次单屏
		if (0 != wEpIdTemp1)
		{
			ptNode = m_pcConf->GetNode(wEpIdTemp1);
		}
		else if (0 != wEpIdTemp2)
		{
			ptNode = m_pcConf->GetNode(wEpIdTemp2);
		}
		else
		{
			ptNode = NULL;
		}
	}

	// 找到的ptNode即为发言会场目标
	if (NULL != ptNode && ptNode->IsVidSndValid() && ptNode->IsInMix())
	{
		if (ptSpeakerNode->IsThreeVidSnd())
		{// 发言会场是三屏
			if (ptNode->IsThreeVidSnd())
			{// 目标是三屏，一一对应
				UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM, 
					m_tDstEpInfo.AddDstEp(ptNode, wIndex, wIndex));
			}
			else
			{// 目标是单屏，放在发言会场的中间屏
				m_tDstEpInfo.AddDstEp(ptNode, MIDSCREENINDEX, MIDSCREENINDEX);
				
				// 查找是否还有其他单屏，也加进来
				FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
				
			}
			AdjustVmpEpInfoForThreeScreen(ptDiscussInfo); // 小图像
		}
		else
		{// 发言会场是单屏
			m_tDstEpInfo.AddDstEp(ptNode, ptNode->GetSpeaker(), MIDSCREENINDEX);
			AdjustVmpEpInfoForSingleScreen(ptDiscussInfo);// 小图像
		}
	}
	return;
}

void CDiscussObjectForSpeakerEp::UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	u16 wIndex;
	
	if (ptDiscussInfo->m_wChairEpId!=TP_INVALID_INDEX && ptDiscussInfo->m_wChairEpId != ptSpeakerNode->m_wEpID)
	{// 主席在讨论里，且不为发言人，发言人目标始终为主席
		if (ptSpeakerNode->IsThreeVidSnd())
		{
			ptDiscussInfo->ResetSpecialEp();
		}
		else if (!ptDiscussInfo->IsSpecialEpVaild())
		{
			TCallNode* ptOldSpeaker = m_pcConf->GetNode(m_pcConf->curSpeakerID());
			if (NULL != ptOldSpeaker && ptOldSpeaker->IsThreeVidSnd())
			{// 由三屏切为单屏发言时，老的发言会场讨论目标需要特殊处理
				ptDiscussInfo->SetSpecialEp(ptOldSpeaker->m_wEpID);
				UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
					ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex] = m_tDstEpInfo.m_atScreenInfo[wIndex]);
			}
		}
		else
		{

		}
		InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);

		return;
	}

	if (ptSpeakerNode->IsThreeVidSnd())
	{
		m_tDstEpInfo.Clear();
		if (ptDiscussInfo->IsSpecialEpVaild())
		{
			if (ptDiscussInfo->m_wSpecialEp == ptSpeakerNode->m_wEpID)
			{// 切回三屏（specialEp）发言时，目标不能从从普通三屏目标中获取
				UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
						m_tDstEpInfo.m_atScreenInfo[wIndex] = ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex]);
			}
			else
			{
				UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM, 
					m_tDstEpInfo.m_atScreenInfo[wIndex] = ptDiscussInfo->m_atThreeScrBak[wIndex]);
			}
			ptDiscussInfo->ResetSpecialEp();
		}
		else
		{			
			UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM, 
				m_tDstEpInfo.m_atScreenInfo[wIndex] = ptDiscussInfo->m_atThreeScrBak[wIndex]);
		}
	}
	else
	{
		if (!ptDiscussInfo->IsSpecialEpVaild())
		{
			TCallNode* ptOldSpeaker = m_pcConf->GetNode(m_pcConf->curSpeakerID());
			if (NULL != ptOldSpeaker && ptOldSpeaker->IsThreeVidSnd())
			{// 由三屏切为单屏发言时，老的发言会场讨论目标需要特殊处理
				ptDiscussInfo->SetSpecialEp(ptOldSpeaker->m_wEpID);
				UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
					ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex] = m_tDstEpInfo.m_atScreenInfo[wIndex]);
			}
		}

		m_tDstEpInfo.Clear();
		m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX] = ptDiscussInfo->m_tSingleScrBak;

		AdjustVmpEpInfoForSingleScreen(ptDiscussInfo);
	}
	return;
}

void CDiscussObjectForSpeakerEp::UptateDstEpInfoByChangeSeat( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo )
{	
	TCallNode* ptOprNode = m_pcConf->GetNodeMgr()->GetNode(tOprInfo.m_wEpID);
	if (NULL == ptOprNode || !ptOprNode->IsVidSndValid())
	{
		return;
	}
	
	if (ptSpeakerNode->IsSingleVidSnd())
	{
		if (ptOprNode->m_wEpID == m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX].m_atMember[0].GetHandleOne())
		{
			m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX].UptateDstEpSeat(ptOprNode);
		}
	}
	return;
}

void CDiscussObjectForSpeakerEp::UptateDstEpInfoByAdd( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo )
{
	if (ptDiscussInfo->m_wChairEpId!=TP_INVALID_INDEX && ptDiscussInfo->m_wChairEpId != ptSpeakerNode->m_wEpID)
	{// 主席在讨论里，且不为发言人，发言人目标始终为主席
		InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
		return;
	}

	if (!m_tDstEpInfo.IsDstEpVaild())
	{
		InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
	}
	else
	{
		if (ptSpeakerNode->IsThreeVidSnd())
		{
			// 尝试填充单屏
			FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
			AdjustVmpEpInfoForThreeScreen(ptDiscussInfo);
		}
		else
		{
			AdjustVmpEpInfoForSingleScreen(ptDiscussInfo);
		}
	}

	return;
}

void CDiscussObjectForSpeakerEp::UptateDstEpInfoByDel( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo )
{
	if (ptDiscussInfo->m_wChairEpId!=TP_INVALID_INDEX && ptDiscussInfo->m_wChairEpId != ptSpeakerNode->m_wEpID)
	{// 主席在讨论里，且不为发言人，发言人目标始终为主席
		InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
		return;
	}

	if (m_pcConf->curSpeakerID() != ptSpeakerNode->m_wEpID)
	{// 说明删除的是老发言会场, 那么老发言会场目标，不再适用于新发言会场，所以需要先到bak中取相应目标
		if (ptSpeakerNode->IsThreeVidSnd())
		{
			UptateDstEpInfoByChangeSpeaker(ptSpeakerNode, ptDiscussInfo);
		}
		else
		{
			m_tDstEpInfo.Clear();
			m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX] = ptDiscussInfo->m_tSingleScrBak;
		}
	}

	// 删除的会场中可能在目标中
	CheckOutDstInfo(ptDiscussInfo, &m_tDstEpInfo);

	if (!m_tDstEpInfo.IsDstEpVaild())
	{
		InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
	}
	else
	{
		if (ptSpeakerNode->IsThreeVidSnd())
		{
			FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
			AdjustVmpEpInfoForThreeScreen(ptDiscussInfo);
		}
		else
		{
			AdjustVmpEpInfoForSingleScreen(ptDiscussInfo);
		}
	}

	return;
}

//////////////////////////////////////////
////////////// 普通三屏目标 //////////////
//////////////////////////////////////////
void CDiscussObjectForThreeScreenEp::AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId)
{
	TCallNode* ptSpeaker = m_pcConf->GetNodeMgr()->GetNode(wSpeakerId);
	if (NULL == ptSpeaker || !ptSpeaker->IsVidSndValid())
	{
		return;
	}
	TVmpUseParam tVmpParam;	
	TTPEncrypt tEncrypt = m_pcConf->GetConfEncryptInfo();
	for (u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{		
		memcpy(&tVmpParam.m_tEncrypt, &tEncrypt, sizeof(TTPEncrypt));
		GetVmpEncParam(tVmpParam.m_tEncParam, ptSpeaker, TRUE); // 广播三屏目标，按发言会场发送格式出	
		GetVmpStyleInfo(tVmpParam.m_tStyleInfo, &m_tDstEpInfo.m_atScreenInfo[wIndex], ptDiscussInfo->m_wTotalScreenNum > 18);
		if (m_atVmpTp[wIndex].m_bIsVmpStart)
		{
			m_pcConf->GetVmpServiceHandle()->ChangeMode(m_atVmpTp[wIndex].m_pcVmpTpRes, &tVmpParam);
		}
		else
		{
			m_pcConf->GetVmpServiceHandle()->Start(m_atVmpTp[wIndex].m_pcVmpTpRes, &tVmpParam);
			m_atVmpTp[wIndex].m_bIsVmpStart = TRUE;
		}
		tVmpParam.Clear();
		
		CNetPortMgr::AdjustDiscussObjToVmpTp(m_pcConf, &m_atVmpTp[wIndex], &m_tDstEpInfo.m_atScreenInfo[wIndex]);
	}
	return;
}

void CDiscussObjectForThreeScreenEp::AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId)
{
	u16 wIndex = 0;
	u16 wThreeScreenDstEp = m_tDstEpInfo.FindThreeScreenDstEp();
	TAudMixMemberInfo tMemberInfo;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		tMemberInfo.Clear();
		GetNewMixMember(tMemberInfo, &m_tDstEpInfo, wIndex, wThreeScreenDstEp);
		m_pcConf->GetEapu()->AdjustAudMixMember(m_atMix[wIndex].m_ptMixRes, &tMemberInfo, wThreeScreenDstEp, wIndex);
		CNetPortMgr::AdjustDiscussObjToMix(m_pcConf, &m_atMix[wIndex], &tMemberInfo);
	}

	u8 byChanId = 0xff;
	TMixSync pMixSync;
	pMixSync.m_bSpeakerObject = FALSE;
	if (wThreeScreenDstEp > 0 && wThreeScreenDstEp < TP_CONF_MAX_CNSNUM)
	{// 有三屏会场作为大图像，找到对应坐席进对应混音器的的通道索引
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			byChanId = m_atMix[wIndex].m_ptMixRes->GetIndx(wThreeScreenDstEp, wIndex);

			pMixSync.Add(m_atMix[wIndex].m_ptMixRes, byChanId);
			m_atMix[wIndex].m_ptMixRes->SetSyncChnl(byChanId);
		}
		// 设置同步
		m_pcConf->GetEapu()->SetMixerSyncChnl(pMixSync);
	}
	else
	{// 取消同步 to do ...
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{	
			pMixSync.Add(m_atMix[wIndex].m_ptMixRes, byChanId);
			m_atMix[wIndex].m_ptMixRes->SetSyncChnl(byChanId);
		}
		// 取消同步
		m_pcConf->GetEapu()->SetMixerSyncChnl(pMixSync);
	}

	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{	
		m_pcConf->GetEapu()->CheckDelMember(m_atMix[wIndex].m_ptMixRes);
	}

	return;
}

void CDiscussObjectForThreeScreenEp::UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo)
{
	TDiscussScreenInfo* pScrInfo = NULL;
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{	
		
		if (NULL == m_atVmpTp[wIndex].m_pcVmpTpRes)
		{
			continue;
		}
		
		pScrInfo = &m_tDstEpInfo.m_atScreenInfo[wIndex];
		if (!pScrInfo->IsScreenValid())
		{
			continue;
		}
		
		CNetPortMgr::AdjustDiscussObjToVmpTp(m_pcConf, &m_atVmpTp[wIndex], pScrInfo);
	}
	return;
}

void CDiscussObjectForThreeScreenEp::UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex)
{
	u8 byAdd = 0;

	TDiscussScreenInfo* pScrInfo0 = NULL;
	TDiscussScreenInfo* pScrInfo1 = NULL;
	TDiscussScreenInfo* pScrInfo2 = NULL;

	u8 abyFlag0[UMS_VMP_MAX_RCV] = {0};
	u8 abyFlag1[UMS_VMP_MAX_RCV] = {0};
	u8 abyFlag2[UMS_VMP_MAX_RCV] = {0};
	u8 byAdjust0 = 0;
	u8 byAdjust1 = 0;
	u8 byAdjust2 = 0;

	u8 byCanId = 0;
	u16 wEpId = 0;
	u16 wLoop = 0;
	BOOL32 bRet = FALSE;

	pScrInfo0 = &m_tDstEpInfo.m_atScreenInfo[0];
	pScrInfo1 = &m_tDstEpInfo.m_atScreenInfo[1];
	pScrInfo2 = &m_tDstEpInfo.m_atScreenInfo[2];
	
	for (wLoop = 0; wLoop < byNum; wLoop++)
	{
		byCanId = byChanId[wLoop];
		if (byCanId >= TP_APU2_MAX_CHAN_NUM)
		{
			break;
		}
		
		if (ptMixInfo->m_atChnl[byCanId].m_wScrIndx > TP_MAX_STREAMNUM)
		{// 双流忽略
			continue;
		}
		
		wEpId = ptMixInfo->m_atChnl[byCanId].m_wEpID;			
		
		bRet = pScrInfo0->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust0 = 1;
			abyFlag0[byAdd] = 1;
			if (bRet)
			{// 三屏小图像，有一个亮全部亮
				abyFlag0[byAdd+1] = 1;
				abyFlag0[byAdd+2] = 1;
			}
		}

		bRet = pScrInfo1->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust1 = 1;
			abyFlag1[byAdd] = 1;
			if (bRet)
			{// 三屏小图像，有一个亮全部亮
				abyFlag1[byAdd+1] = 1;
				abyFlag1[byAdd+2] = 1;
			}
		}

		bRet = pScrInfo2->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust2 = 1;
			abyFlag2[byAdd] = 1;
			if (bRet)
			{// 三屏小图像，有一个亮全部亮
				abyFlag2[byAdd+1] = 1;
				abyFlag2[byAdd+2] = 1;
			}
		}

	}

	if (byAdjust0)
	{
		m_pcConf->GetVmpServiceHandle()->UpdateSpeakerSideLine(m_atVmpTp[0].m_pcVmpTpRes, abyFlag0, UMS_VMP_MAX_RCV);
	}

	if (byAdjust1)
	{
		m_pcConf->GetVmpServiceHandle()->UpdateSpeakerSideLine(m_atVmpTp[1].m_pcVmpTpRes, abyFlag1, UMS_VMP_MAX_RCV);
	}

	if (byAdjust2)
	{
		m_pcConf->GetVmpServiceHandle()->UpdateSpeakerSideLine(m_atVmpTp[2].m_pcVmpTpRes, abyFlag2, UMS_VMP_MAX_RCV);
	}
	
	return;
}

// 初始化三屏会场目标
void CDiscussObjectForThreeScreenEp::InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	// 先清空
	m_tDstEpInfo.Clear();

	u16 wIndex = 0;
	if (ptSpeakerNode->IsThreeVidSnd())
	{// 发言会场是三屏, 目标正好一一对应
		UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
			m_tDstEpInfo.AddDstEp(ptSpeakerNode, wIndex, wIndex));
	}
	else
	{// 发言会场是单屏，先把发言会场放在中间屏，其余还有单屏，按界面顺序，也加进来，最多3个
		m_tDstEpInfo.AddDstEp(ptSpeakerNode, MIDSCREENINDEX, MIDSCREENINDEX);

		FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
	}

	// 更新小图像
	AdjustVmpEpInfoForThreeScreen(ptDiscussInfo);
	// 保存一份
	UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
		ptDiscussInfo->m_atThreeScrBak[wIndex] = m_tDstEpInfo.m_atScreenInfo[wIndex]);

	return;
}

void CDiscussObjectForThreeScreenEp::UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	u16 wIndex = 0;
	if (ptSpeakerNode->IsThreeVidSnd())
	{// 发言会场是三屏, 大图像一一对应，直接替换之前目标
		m_tDstEpInfo.m_wAddIndex = MIDSCREENINDEX;
		UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
			m_tDstEpInfo.AddDstEp(ptSpeakerNode, wIndex, wIndex));
	}
	else
	{// 发言会场是单屏				
		u16 wAddIndex = TP_INVALID_INDEX;
		if (!VALID_SCREEN_INDEX(m_tDstEpInfo.GetIndexByEp(ptSpeakerNode->m_wEpID)))
		{
			wAddIndex = m_tDstEpInfo.FindAddScrIndex();
			if (!VALID_SCREEN_INDEX(wAddIndex))
			{// 三个屏的目标都是单屏会场，那么根据AddIndex开始替换
				wAddIndex = m_tDstEpInfo.m_wAddIndex;
				m_tDstEpInfo.m_wAddIndex = GetNextIndex(wAddIndex);
			}
			m_tDstEpInfo.AddDstEp(ptSpeakerNode, MIDSCREENINDEX, wAddIndex);
		}

		if (ptDiscussInfo->IsSpecialEpVaild())
		{// 对特殊目标的处理
			AdjustDstForSpecialEp(wAddIndex, ptSpeakerNode, ptDiscussInfo);
		}
	}

	// 广播三屏目标，切发言会场操作，小图像不需要更新

	// 保存一份
	UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
		ptDiscussInfo->m_atThreeScrBak[wIndex] = m_tDstEpInfo.m_atScreenInfo[wIndex]);

	return;
}

void CDiscussObjectForThreeScreenEp::UptateDstEpInfoByAdd( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo )
{
	if (!m_tDstEpInfo.IsDstEpVaild())
	{
		InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
	}
	else
	{
		if (ptDiscussInfo->IsSpecialEpVaild())
		{
			FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo, &ptDiscussInfo->m_tSpecialDst);
			FillUpSingleScrEp(ptDiscussInfo, &ptDiscussInfo->m_tSpecialDst);
		}
		else
		{
			FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
		}

		AdjustVmpEpInfoForThreeScreen(ptDiscussInfo);

		u16 wIndex = 0;
		if (ptDiscussInfo->IsSpecialEpVaild())
		{
			UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM, 
				ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex].CopyVmpEpInfo(m_tDstEpInfo.m_atScreenInfo[wIndex]));
		}

		// 保存一份
		UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
			ptDiscussInfo->m_atThreeScrBak[wIndex] = m_tDstEpInfo.m_atScreenInfo[wIndex]);
	}

	return;
}

void CDiscussObjectForThreeScreenEp::UptateDstEpInfoByDel( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo )
{
	u16 wIndex = TP_INVALID_INDEX;
	
	if (ptSpeakerNode->IsThreeVidSnd())
	{
		if (ptSpeakerNode->m_wEpID != m_pcConf->curSpeakerID())
		{// 发言会场被删了，普通三屏看新的发言会场
			m_tDstEpInfo.Clear();
			UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
				m_tDstEpInfo.AddDstEp(ptSpeakerNode, wIndex, wIndex));
		}
	}
	else
	{
		CheckOutDstInfo(ptDiscussInfo, &m_tDstEpInfo);
		
		if (!VALID_SCREEN_INDEX(m_tDstEpInfo.GetIndexByEp(ptSpeakerNode->m_wEpID)))
		{// 发言会场不在目标中
			wIndex = m_tDstEpInfo.FindIdleScrIndex();// 肯定能找到
			m_tDstEpInfo.AddDstEp(ptSpeakerNode, MIDSCREENINDEX, wIndex);
		}

		if (ptDiscussInfo->IsSpecialEpVaild())
		{
			if (!ptDiscussInfo->CheckSpecialEp())
			{
				ptDiscussInfo->ResetSpecialEp();
			}
			else
			{
				CheckOutDstInfo(ptDiscussInfo, &ptDiscussInfo->m_tSpecialDst);
				
				if (!ptDiscussInfo->m_tSpecialDst.IsDstEpVaild())
				{
					ptDiscussInfo->ResetSpecialEp();
				}
				else
				{
					AdjustDstForSpecialEp(wIndex, ptSpeakerNode, ptDiscussInfo);
				}
			}
		}

		if (ptDiscussInfo->IsSpecialEpVaild())
		{
			FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo, &ptDiscussInfo->m_tSpecialDst);
			FillUpSingleScrEp(ptDiscussInfo, &ptDiscussInfo->m_tSpecialDst);
		}
		else
		{
			FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
		}
	}

	AdjustVmpEpInfoForThreeScreen(ptDiscussInfo);

	if (ptDiscussInfo->IsSpecialEpVaild())
	{
		UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM, 
			ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex].CopyVmpEpInfo(m_tDstEpInfo.m_atScreenInfo[wIndex]));
	}

	UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
			ptDiscussInfo->m_atThreeScrBak[wIndex] = m_tDstEpInfo.m_atScreenInfo[wIndex]);

	return;
}

//////////////////////////////////////////
////////////// 普通单屏目标 //////////////
//////////////////////////////////////////
EmDiscussRspRet CDiscussObjectForSingleScreenEp::AssignResource(CUmsConfInst* param)
{
	if (NULL == m_pcConf->GetSpeaker().m_pcSingleVmp)
	{
		m_pcConf->GetSpeaker().m_pcSingleVmp = m_pcConf->GetVmpServiceHandle()->Assign(VirSingleVmpCB, m_pcConf);
		if (NULL == m_pcConf->GetSpeaker().m_pcSingleVmp)
		{
			return em_Start_AssginVmpFail;
		}
	}

	if (NULL == m_pcConf->GetSpeaker().m_ptAudMix)
	{
		m_pcConf->GetSpeaker().m_ptAudMix = m_pcConf->GetEapu()->AssignMixer(VirSingleMixCB, m_pcConf);		
		if (NULL == m_pcConf->GetSpeaker().m_ptAudMix)
		{
			return em_Start_AssignMixFail;
		}
	}

	if (!m_pcConf->TryAssignVirSingleBas())
	{
		return em_Start_AssignBasFail;
	}
			
	return em_DiscussOprRsp_Ok;
}

void CDiscussObjectForSingleScreenEp::FreeResource()
{
	if (!m_pcConf->GetDualMgr()->IsStart())
	{
		if (NULL != m_pcConf->GetSpeaker().m_ptAudMix)
		{
			
			m_pcConf->GetEapu()->ReleaseMixer(m_pcConf->GetSpeaker().m_ptAudMix);
			m_pcConf->GetSpeaker().m_ptAudMix = NULL;
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_pcConf->GetSpeaker().m_tToAudMixDs);
		}
	}

	if (!m_pcConf->GetVmp()->IsSpeakVmpOn())
	{
		if (NULL != m_pcConf->GetSpeaker().m_pcSingleVmp)
		{
			m_pcConf->GetVmpServiceHandle()->Release(m_pcConf->GetSpeaker().m_pcSingleVmp);
			m_pcConf->GetSpeaker().m_pcSingleVmp = NULL;
			m_pcConf->GetSpeaker().m_bSingleVmpStart = FALSE;
			CNetPortMgr::FreeMediaTrans(m_pcConf, m_pcConf->GetSpeaker().m_tToVmpDs);
		}

		if (NULL != m_pcConf->GetSpeaker().m_pcSingleBas)
		{
			m_pcConf->GetBas()->ReleaseScreenBas(m_pcConf->GetSpeaker().m_pcSingleBas);
			m_pcConf->GetSpeaker().m_pcSingleBas = NULL;
		}
	}

	Init();
	return;
}

void CDiscussObjectForSingleScreenEp::ShowResourse()
{
	TAudMixInfo* pMix = NULL;
	const CBaseService* pVmp = NULL;
	CScreenBasRes* pBas = NULL;
	pMix = m_pcConf->GetSpeaker().m_ptAudMix;
	if (NULL != pMix)
	{
#ifdef _USE_XMPUEQP_
		msgprintnotime("1-MixEqpId:%d, ChanNum:%d.\n", 
			pMix->m_tEqpRes.m_byEqpID, pMix->m_tEqpRes.m_wChanNum);
#else
		msgprintnotime("1-MixId:%d, ChanNum:%d, UmsStartPort:%d, EqpRtpStartPort:%d, EqpRtcpstartPort:%d, \n", 
			pMix->m_tEqpRes.m_byEqpID, pMix->m_tEqpRes.m_wChanNum, pMix->m_tEqpRes.m_wUmsStartPort, pMix->m_tEqpRes.m_wEqpStartPort,
            pMix->m_tEqpRes.m_wEqpRtcpStartPort);
#endif
	}

	pVmp = m_pcConf->GetSpeaker().m_pcSingleVmp;
	if (NULL != pVmp)
	{
		m_pcConf->GetVmpServiceHandle()->Show(pVmp);
	}
	pBas = m_pcConf->GetSpeaker().m_pcSingleBas;
	if (NULL != pBas)
	{

#ifdef  _USE_XMPUEQP_
		u16 byInnerIndex = 0;
		msgprintnotime(" SingleVidBas EqpId:%d, State:%d(0:idle;1:start;2:run)\n", 
			pBas->GetBasEqpId(), 
			pBas->m_tXmpuBas.m_emStat);

		if (pBas->m_tXmpuBas.m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("   InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(pBas->m_tXmpuBas.m_tDecMiddleRtpAddr.GetIP()), pBas->m_tXmpuBas.m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(pBas->m_tXmpuBas.m_tDecRtcpAddr.GetIP()), pBas->m_tXmpuBas.m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(pBas->m_tXmpuBas.m_tDecRtpAddr.GetIP()), pBas->m_tXmpuBas.m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; byInnerIndex++)
			{
				msgprintnotime("   OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(pBas->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetIP()), pBas->m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(pBas->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), pBas->m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(pBas->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetIP()), pBas->m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
			}	
		}
																																			
#else
		msgprintnotime(" BasId:%d, ChnIndx:%d, UmsStartPort:%d, EqpStartPort:%d, DsIP:"TPIPFORMAT"\n", pBas->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
			pBas->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, pBas->m_tBasEqpRes.m_tBasChnInfo.m_wUmsStartPort, 
			pBas->m_tBasEqpRes.m_tBasChnInfo.m_wEqpStartPort, u32ToIP(pBas->m_tBasEqpRes.m_tBasChnInfo.m_dwMediaIP));
#endif
	}
	
	return;
}

const CBaseService* CDiscussObjectForSingleScreenEp::GetVmpRes( u16 wScreenIndex )
{
	return m_pcConf->GetSpeaker().m_pcSingleVmp;
}

TAudMixInfo* CDiscussObjectForSingleScreenEp::GetMixRes( u16 wScreenIndex )
{
	return m_pcConf->GetSpeaker().m_ptAudMix;
}

void CDiscussObjectForSingleScreenEp::AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId)
{
	if (NULL != m_pcConf->GetSpeaker().m_pcSingleVmp)
	{
		TCallNode* ptSpeaker = m_pcConf->GetNodeMgr()->GetNode(wSpeakerId);
		if (NULL == ptSpeaker || !ptSpeaker->IsVidSndValid())
		{
			return;
		}
		TVmpUseParam tVmpParam;	
		TTPEncrypt tEncrypt = m_pcConf->GetConfEncryptInfo();
		memcpy(&tVmpParam.m_tEncrypt, &tEncrypt, sizeof(TTPEncrypt));
		GetVmpEncParam(tVmpParam.m_tEncParam, ptSpeaker, TRUE);// 广播单屏目标，按发言会场发送格式出
		GetVmpStyleInfo(tVmpParam.m_tStyleInfo, &m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX], ptDiscussInfo->m_wTotalScreenNum > 18);

		if (m_pcConf->GetSpeaker().m_bSingleVmpStart)
		{
			m_pcConf->GetVmpServiceHandle()->ChangeMode(m_pcConf->GetSpeaker().m_pcSingleVmp, &tVmpParam);
		}
		else
		{
			m_pcConf->GetVmpServiceHandle()->Start(m_pcConf->GetSpeaker().m_pcSingleVmp, &tVmpParam);
			m_pcConf->GetSpeaker().m_bSingleVmpStart = TRUE;
		}

		CNetPortMgr::AdjustSingleDiscussObjToVmpTp(m_pcConf, &m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX]);
	}
	return;
}

void CDiscussObjectForSingleScreenEp::AdjustDstAudToApu2TpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId)
{// 进普通单屏混音器的是所有讨论会场混音和双流声音
	u16 wTemp = 0;
	TAudMixMemberInfo tInfo;
	TDiscussEpInfo* pEpInfo = NULL;
	for (wTemp = 0; wTemp < TP_CONF_MAX_AUDMIXNUM; wTemp++)
	{
		pEpInfo = &ptDiscussInfo->m_atDiscussEpInfo[wTemp];
		if (NULL == pEpInfo || !pEpInfo->IsValid())
		{
			continue;
		}
		// 进单屏混音器，会场统一填3，跟双流业务保持一致
		tInfo.AddMixMember(pEpInfo->m_wEpID, TP_MAX_STREAMNUM);
	}

	BOOL32 bIsAddDualAud = FALSE;
	if (m_pcConf->GetDualMgr()->IsStart())
	{
		wTemp = m_pcConf->GetDualMgr()->GetDualID();
		TCallNode* ptDualNode = m_pcConf->GetNode(wTemp);
		if (NULL != ptDualNode && ptDualNode->IsCns() && 
			emTPAEnd != ptDualNode->m_tDualAudSndFormat.m_tFormat.m_emFormat)
		{// 进单屏混音器，双流填4
			tInfo.AddMixMember(wTemp, TP_MAX_STREAMNUM+1);
			bIsAddDualAud = TRUE;
		}
	}
				
	m_pcConf->GetEapu()->AdjustAudMixMember(m_pcConf->GetSpeaker().m_ptAudMix, &tInfo);
	CNetPortMgr::AdjustSingleDiscussObjToMix(m_pcConf, bIsAddDualAud);
	return;
}

void CDiscussObjectForSingleScreenEp::AdjustApu2MixForceActiveInfo( u16 wSpeakerId, BOOL32 bForceActiveOn )
{
	m_pcConf->GetEapu()->AdjustForceActive(m_pcConf->GetSpeaker().m_ptAudMix, bForceActiveOn ? wSpeakerId : TP_INVALID_INDEX);
}


void CDiscussObjectForSingleScreenEp::UptateDstVidToVmpTp(TDiscussInfo* ptDiscussInfo)
{
	CNetPortMgr::AdjustSingleDiscussObjToVmpTp(m_pcConf, &m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX]);
	return;
}

void CDiscussObjectForSingleScreenEp::UpdateSpeakerSideLine(TDiscussInfo* ptDiscussInfo, TAudMixInfo* ptMixInfo, u8 byChanId[], u8 byNum, u16 wScreenIndex)
{
	TDiscussScreenInfo* pScrInfo = NULL;
	const CBaseService* pVmp = m_pcConf->GetSpeaker().m_pcSingleVmp;
	
	u8 abyFlag[UMS_VMP_MAX_RCV] = {0};
	u8 byAdd = 0;
	u8 byAdjust = 0;
	u8 byCanId = 0;
	u16 wEpId = 0;
	u16 wLoop = 0;
	BOOL32 bRet = FALSE;
	
	pScrInfo = &m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX];
	if (NULL == pVmp || !pScrInfo->IsVmpEpValid())
	{
		return;
	}
	
	for (wLoop = 0; wLoop < byNum; wLoop++)
	{
		byCanId = byChanId[wLoop];
		if (byCanId >= TP_APU2_MAX_CHAN_NUM)
		{
			break;
		}
		
		if (ptMixInfo->m_atChnl[byCanId].m_wScrIndx > TP_MAX_STREAMNUM)
		{// 双流忽略
			continue;
		}
		
		wEpId = ptMixInfo->m_atChnl[byCanId].m_wEpID;			
		bRet = pScrInfo->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust = 1;
			abyFlag[byAdd] = 1;
			if (bRet)
			{// 三屏小图像，有一个亮全部亮
				abyFlag[byAdd+1] = 1;
				abyFlag[byAdd+2] = 1;
			}
		}
	}
	
	if (byAdjust)
	{
		m_pcConf->GetVmpServiceHandle()->UpdateSpeakerSideLine(pVmp, abyFlag, UMS_VMP_MAX_RCV);
	}

	return;
}

// 初始化单屏目标
void CDiscussObjectForSingleScreenEp::InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	m_tDstEpInfo.AddDstEp(ptSpeakerNode, ptSpeakerNode->GetSpeaker(), MIDSCREENINDEX);
	AdjustVmpEpInfoForSingleScreen(ptDiscussInfo);
	// 保存一份
	ptDiscussInfo->m_tSingleScrBak = m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX];
	return;
}

void CDiscussObjectForSingleScreenEp::UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
	return;
}

void CDiscussObjectForSingleScreenEp::UptateDstEpInfoByChangeSeat( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo )
{// 发言会场切坐席时，才需要更新
	if (ptSpeakerNode->m_wEpID != tOprInfo.m_wEpID)
	{
		return;
	}

	m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX].UptateDstEpSeat(ptSpeakerNode);
	ptDiscussInfo->m_tSingleScrBak = m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX];

	return;
}

void CDiscussObjectForSingleScreenEp::UptateDstEpInfoByAdd( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo )
{
	InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
	return;
}

void CDiscussObjectForSingleScreenEp::UptateDstEpInfoByDel( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo )
{
	InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);	
	return;
}





