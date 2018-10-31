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
#define ASSGIN_DIS_VMP_NUM 7   // ��������ϳ���Դ
#define ASSGIN_DIS_MIX_NUM 7		// �������������Դ
// ������Ŀ����ͳһ����
#define UmsDiscussOprCycle(wIII, wIIIEnd, OprFun)\
	for (wIII = 0; wIII < wIIIEnd; wIII++)\
	{\
	    OprFun;}\
		
inline u16 GetNextIndex( u16 wScreenIndex )
{
	// �� 1 0 2��˳��
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
/////////////////////��������ģʽ������//////////////////////////////
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
	case ev_UmsConfAMixUpdate_Cmd:    // ��ϯcnc��Ϣ�������͹ر����ۣ��������£���ɾ���ۻ᳡��
		{
			OnDiscussStatusCmd(ptMsg);   
		}
		break;
	case ev_UmsAudMixDisListOpr_Cmd:   // ��ϯcnc��Ϣ�������£���ɾ���ۻ᳡
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

// ���鿪ʼʱ������Ԥ�������б�����������
void CUmsDiscussMgr::InitDiscuss( TAuxMixList& tAuxMixList )
{
	CUmsConfInst* pInst = Inst();
	
	if (!pInst->IsChairConf())
	{// ���ϼ�������
		return ;
	}
	
	MdlHint(Ums_Mdl_Call, ("[InitDiscuss] ConfID:%d, bDiscussOn:%d, bVacOn:%d\n", pInst->GetInsID(), 
		tAuxMixList.m_bAudMixOn, tAuxMixList.m_bVacOn));
	
	TConfAuxMixInfo tAudMix;
	tAudMix.m_wConfID = pInst->GetInsID();
	tAudMix.m_bStart = tAuxMixList.m_bAudMixOn;
	tAudMix.m_atAuxMixList = tAuxMixList;
	tAudMix.m_bVacOn = tAuxMixList.m_bVacOn;
	m_bUIVacOn = tAudMix.m_bVacOn;  // ������۲�Ԥ�ÿ����Ļ��������OnDiscussStatusCmd�ǲ��ᱣ����������״̬�ģ������ȱ����¡�����
	
	//ģ���е�EpID�Ǵ�0��ʼ����Ҫ��ҵ��ͬ����ҵ���1��ʼ��
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
		//���͸�����
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

// ��������ʱ���ͷ����������Դ
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

// �����ڻ᳡����
void CUmsDiscussMgr::OnChanConnect( TCallNode* ptNode )
{		
	CUmsConfInst* pInst = Inst();

	u16 wIndex = m_tDiscussInfo.m_tDiscussEpFromUI.FindIndexByEp(ptNode->m_wEpID); 
	TDiscussEpInfo* ptEpInfo = m_tDiscussInfo.FindEpById(ptNode->m_wEpID);

	if (ptNode->IsUms())
	{// ��ums�Ĵ���
		if (TP_VALID_HANDLE(wIndex) && pInst->IsChairConf())
		{// ums���������۳�Ա�У���Ҫɾ��
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
		{// ums���ߺ������ǰ������״̬����Ҫ֪ͨ��ȥ
			TCapNode* ptFatherNode = pInst->GetNodeMgr()->GetForeFatherNode(ptNode);
			if (NULL != ptFatherNode && ptNode == ptFatherNode)
			{// 
				TUmsHandle tHandle;
				TDiscussCasecadeNtfy tNtfy;
				
				MakeCasecadeObjNtfy(ptFatherNode, tNtfy);

				pInst->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
				UmsSendConfCtrl(tHandle, evtp_UmsDiscussScreenStat_Notify, &tNtfy, sizeof(tNtfy));
				
				// �е�����
				pInst->GetNodeFsm()->StartDis(ptFatherNode);
			}
		}
		return;
	}

	// �Ի᳡�Ĵ���

	if ( !pInst->IsChairConf() )
	{// ���ϼ�������
		return;
	}

	if (!TP_VALID_HANDLE(wIndex))
	{// ���������б���
		MdlHint(Ums_Mdl_Call, ("[OnChanConnect] ep is not in Dis! ConfId:%d, epId:%d, discussScreenNum:%d\n",
			pInst->GetInsID(), ptNode->m_wEpID, m_tDiscussInfo.m_wTotalScreenNum));
		return;
	}

	if (!m_bUIDiscussStatus)
	{
		MdlHint(Ums_Mdl_Call, ("[OnChanConnect] Now is not Dis Modle! ConfId:%d, epId:%d\n", pInst->GetInsID(), ptNode->m_wEpID));
		return;
	}

	// �������б��Ա���ߴ���
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
			// ��ʾ��������ʧ��
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

// �Ҷ������ڻ᳡
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
	{// �����õĻ�����
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
	{// for specialĿ��
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
	{//ȡ���Ի᳡Ŀ��
		ptInfo = &m_atDiscussObj[emDiscussObjForSpeakerEp];	
	}
	else if (ptNode->IsThreeVidRcv())
	{//ȡ����Ŀ��
		ptInfo = &m_atDiscussObj[emDiscussObjForThreeScrEp];
	}
	else
	{//ȡ����Ŀ��
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

	// vmp�ص�����
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
				{// �û᳡��ϯ��С�������������������������
					pInst->GetBas()->AskFrameToScreenBas(ptEpInfo->m_apcBas[wSeatIndex]);
				}
				else
				{// ��᳡��Ӧ��������
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

	// vmp�ص�����
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
		// �õ��ؼ�֡Ŀ�Ļ᳡����ϯ
		m_apcDisObj[emDiscussObjForSingleScrEp]->GetVmpMemberEpByIndex(MIDSCREENINDEX, wMemberIndx, wEpId, wSeatIndex);		
		TDiscussEpInfo* ptEpInfo = GetDiscussEpInfoById(wEpId);
		if (NULL != ptEpInfo && ptEpInfo->IsValid())
		{
			if (NULL != ptEpInfo->m_apcBas[wSeatIndex] && 0 != wMemberIndx)
			{// �û᳡��ϯ��С�������������������������
				pInst->GetBas()->AskFrameToScreenBas(ptEpInfo->m_apcBas[wSeatIndex]);
			}
			else
			{// ��᳡��Ӧ������
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
				{// ���ֱ��ʣ���С����
					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wIndex, emTPV480x272);
					ptEpInfo->m_aemVideoRes[wIndex] = emTPV480x272;
				}
				break;
			}
		}
		
		CNetPortMgr::AdjustDiscussEpToBas(pInst, ptEpInfo);
		
		// ��Ҫˢ�½��ϳ����Ľ���
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
			tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 2; //  �¼����ϼ��ĵ����㲥�ϳ�����ؼ�֡ 
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
		{// �¼����ͷŴ�������Դ
			pInst->GetBas()->ReleaseScreenBas(pInst->GetSpeaker().m_pcSingleBas);
			pInst->GetSpeaker().m_pcSingleBas = NULL;
			
			//����Դ���¼��������Կ�����Ŀ�����ϯ ���м���
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
	{// �����쳣

		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (NULL != ptEpInfo->m_apcBas[wIndex] && ptBasRes == ptEpInfo->m_apcBas[wIndex])
			{	
				pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wIndex]);
				ptEpInfo->m_apcBas[wIndex] = NULL;

				// �ٳ�������
				if (pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wIndex]))
				{// ���䵽������
					ptEpInfo->m_apcBas[wIndex]->SetCB(DiscussBasCB, this);
					// �����������ʽ
					TUmsVidFormat tVidFormat;
					tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
					tVidFormat.m_emRes = emTPV480x272;
					tVidFormat.m_wFrameRate = 15;
					pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wIndex], ptEpInfo->m_wEpID, wIndex, 1, &tVidFormat);
				}
				else
				{
					if (ptEpInfo->m_bMtAdjustRes && emTPVResEnd == ptEpInfo->m_aemVideoRes[wIndex])
					{// ���ֱ��ʣ���С����
						pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wIndex, emTPV480x272);
						ptEpInfo->m_aemVideoRes[wIndex] = emTPV480x272;
					}
				}
				break;
			}
		}

		// 
		CNetPortMgr::AdjustDiscussEpToBas(pInst, ptEpInfo);

		// ��Ҫˢ�½��ϳ����Ľ���
		UmsDiscussOprCycle(wIndex, emDiscussObjEnd,
			m_apcDisObj[(EmDiscussModleObj)wIndex]->UptateDstVidToVmpTp(&m_tDiscussInfo));
	}
	else
	{// ��᳡��Ӧ������ؼ�֡
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
		{// �¼����ͷŴ�������Դ
			pInst->GetBas()->ReleaseScreenBas(pInst->GetSpeaker().m_pcSingleBas);
			pInst->GetSpeaker().m_pcSingleBas = NULL;

			//����Դ���¼��������Կ�����Ŀ�����ϯ ���м���
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
		tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 2; //  �¼����ϼ��ĵ����㲥�ϳ�����ؼ�֡ 
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
	// ���
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
	{ // û��С����, ���Դ�������ȡС����
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
			{// ����ն˽��˷ֱ��ʣ��������ȡ
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
	// ���
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
	// ���
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
	{// �����᳡û�л���
		tAddr.m_tAddr.m_tRtpAddr = ptEpInfo->m_tGetAddr.m_atAudAddr[MIDSCREENINDEX].m_tRtpAddr;
		tAddr.m_tAddr.m_tBackRtcpAddr = ptEpInfo->m_tGetAddr.m_atAudAddr[MIDSCREENINDEX].m_tBackRtcpAddr;
		tAddr.m_dwMediaNode = ptEpInfo->m_tGetAddr.m_dwMedia;
	}
	else
	{// ���Դ����
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
{ // wScreenIndexΪ0 1 2ʱ����Ӧ�����ĸ�������Ϊ3ʱ����Ӧ����
	tAddr.Clear();

	CUmsConfInst* pInst = Inst();
	TAudMixInfo* pMixRes = GetObjMixRes(emType, wScreenindex); // wScreenindex��emTypeΪemDiscussObjForSingleScrEp��ȡ��Դʱ����
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
	{// ���������еĻ᳡��Ҫȡnģʽ
		if (bFromPutAud)
		{// ͨ��putaud��ȥ��Ϊ�¼������ۻ᳡ȡ������ֻ�ܴ���ȥn-1����ʽ����ƥ��
			pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptNode->m_tAudRcvFormat.m_tFormat);
			return;
		}
		pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptFatherNode->m_tAudRcvFormat.m_tFormat);
		return;
	}
	
	if (TP_INVALID_INDEX != pMixRes->GetIndx(wEpId, wScreenindex))
	{
		if (!bFromPutAud && ptNode != ptFatherNode)
		{// ����putaud��ȥ��Ϊ�¼������ۻ᳡�����Ի᳡��ȡ������ֻȡnģʽ�����ռ�����ʽ���¼�ռ�����䣩
			return;
		}
		pInst->GetEapu()->GetMixerChnOutAddr(pMixRes, tAddr, wEpId, wScreenindex);
	}
	else if (ptNode->IsThreeVidSnd() && TP_INVALID_INDEX != pMixRes->GetIndx(wEpId, TP_MAX_STREAMNUM))
	{// �����᳡����ֻ����Ӧ����mix��Ҳ����ֱ���û�����mix
		if (!bFromPutAud && ptNode != ptFatherNode)
		{// ����putaud��ȥ��Ϊ�¼������ۻ᳡�����Ի᳡��ȡ������ֻȡnģʽ�����ռ�����ʽ���¼�ռ�����䣩
			return;
		}
		pInst->GetEapu()->GetMixerChnOutAddr(pMixRes, tAddr, wEpId, TP_MAX_STREAMNUM);
	}
	else 
	{// ȡnģʽ

		if (bFromPutAud)
		{// ͨ��putaud��ȥ��Ϊ�¼������ۻ᳡ȡ������ֻ�ܴ���ȥn-1����ʽ����ƥ��
			pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptNode->m_tAudRcvFormat.m_tFormat);
			return;
		}
		pInst->GetEapu()->GetNModeAudRcvAddr(pMixRes, tAddr, ptFatherNode->m_tAudRcvFormat.m_tFormat);
	}

	return;
}

void CUmsDiscussMgr::AskKeyFrameFromEp( TCapNode* ptNode, u16 wScreenIndex, BOOL32 bReqBySys )
{// �᳡����ؼ�֡
	CUmsConfInst* pInst = Inst();

	if (pInst->IsChairConf())
	{
		AskKeyFrameToVmpByNode(ptNode, (TCallNode*)ptNode, wScreenIndex, bReqBySys);
	}
	else
	{
		BOOL32 bFlag = IsSpeacialEp(ptNode->m_wEpID);
		if (!bFlag && pInst->curSpeakerID() != ptNode->m_wEpID)
		{// �¼��᳡����յ��ǹ㲥�������������򱾼���������ؼ�֡
			if (ptNode->IsThreeVidRcv())
			{//����Ŀ��
				if (pInst->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat))
				{// ����������
					pInst->GetBas()->SeeSpeakerAskFrameToBas(wScreenIndex);
					return;
				}
			}
			else
			{//����Ŀ��
				if (m_pcConf->GetBas()->IsSpeakerNeedBas(ptNode->m_tVidRcvFormat.m_tFormat))
				{// �����㲥��������
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

		// ���ϼ�����
		TDisAskKeyFrame tDis;
		tDis.m_wEpID = ptNode->m_wEpID; // �¼��᳡��id
		tDis.m_bReqBySys = bReqBySys;
		tDis.m_wScreenNo = wScreenIndex;
		
		TUmsHandle tOutHandle;
		pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
		UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));	
	}

	return;
}

void CUmsDiscussMgr::AskKeyFrameFromBas( u16 wScreenIndex )
{// �����£��㲥�����������Ӻϳ������뷢���������С�����
	CUmsConfInst* pInst = Inst();
	if (pInst->IsChairConf())
	{
		AskKeyFrameToVmp(emDiscussObjForThreeScrEp, wScreenIndex);
	}
	else
	{// ���ϼ�����

		TDisAskKeyFrame tDis;
		tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 1; //  �¼����ϼ��������㲥�ϳ�����ؼ�֡ 
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

    // 0,1,2 ���������е� ���У��ң�3 ����ϳɵĵ�����4����������Ƶ

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
	 { //����

		 if (pInst->IsChairConf())
		 {
			 AskKeyFrameToVmp(emDiscussObjForThreeScrEp, wOprScreenIndex);
		 }
		 else
		 {// ���ϼ�����
			 
			 TDisAskKeyFrame tDis;
			 tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 1; //  �¼����ϼ��������㲥�ϳ�����ؼ�֡ 
			 tDis.m_bReqBySys = FALSE;
			 tDis.m_wScreenNo = wOprScreenIndex;
			 
			 TUmsHandle tOutHandle;
			 pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			 UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));
		 }

	 } 


     if (TP_MAX_STREAMNUM == wScreenIndex || wScreenIndex == TP_MAX_STREAMNUM + 1)
	 { //���� 
		 if (pInst->IsChairConf())
		 {
			 AskKeyFrameToVmp(emDiscussObjForSingleScrEp, MIDSCREENINDEX);
		 }
		 else
		 {
			 TDisAskKeyFrame tDis;
			 tDis.m_wEpID = TP_CONF_MAX_CNSNUM + 2; //  �¼����ϼ��ĵ����㲥�ϳ�����ؼ�֡ 
			 tDis.m_bReqBySys = FALSE;
			 tDis.m_wScreenNo = MIDSCREENINDEX;
			 
			 TUmsHandle tOutHandle;
			 pInst->m_pcNodeMgr->MakeCallerHandle(tOutHandle, CALLER_EP_INDEX);
			 UmsSendConfCtrl(tOutHandle, evtp_UmsDiscussFastUpdate_Req, &tDis, sizeof(tDis));
		 }
	 } 
	 
	 return;
}



// ������ر����ۡ��������£����������б��Ա
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
	{// ����δ������cmd�������۳�Ա�б�
		
		UptateDiscussListFromUI(tAudMix.m_atAuxMixList);
	}
	else if (tAudMix.m_bStart && !m_bUIDiscussStatus)
	{// ����δ������cmd��������, �ȸ��������۳�Ա�б�
		
		if (tAudMix.m_atAuxMixList.GetMixNum() == 0)
		{// ���۳�ԱΪ�գ��Զ��ѷ��Ի᳡�ӽ�����
			tAudMix.m_atAuxMixList.AddMixID(pInst->curSpeakerID());
		}

		UptateDiscussListFromUI(tAudMix.m_atAuxMixList);
		
		tAudMix.m_emRet = AssignResource();// ��Դ����
		if (em_DiscussOprRsp_Ok != tAudMix.m_emRet)
		{
			return;
		}
		
		// ���������Ƿ���
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
	{// �����Ѿ�������cmd�ر�����
	
		//UptateDiscussListFromUI(tAudMix.m_atAuxMixList);
		StopDiscussModle();
		m_bUIVacOn = tAudMix.m_bVacOn;
	}
	else
	{// �����Ѿ������������б�
		if (tAudMix.m_atAuxMixList.GetMixNum() == 0)
		{// ���۳�ԱΪ�գ��Զ��ѷ��Ի᳡�ӽ�����
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

// �����£����Ӻ�ɾ���᳡
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

	//�ظ�umc �������
	pInst->NotifyMsgToServiceForUI(evtp_UpdateAudMixInfo_Ind, &tDisList, sizeof(TDiscussListOpr), &tLogUser);

	return;
}

void CUmsDiscussMgr::DiscussListOprFormUmcCnc(TDiscussListOpr& tDisList, EmUIType emType)
{
	CUmsConfInst* pInst = Inst();

	tDisList.ResetOprRes();

	if (!m_bUIDiscussStatus)
	{// �������£���Ӻ�ɾ���᳡������һ������
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
			{// ���ʧ��
				wFailNum++;
			}
		}
		
		if (wFailNum == tDisList.m_wNum)
		{// ȫʧ���ˣ�����
			MdlError(Ums_Mdl_Call, ("[DiscussListOprFormUmcCnc] Add Ep All Fail! ConfID:%d, num:%d\n", 
				pInst->GetInsID(), tDisList.m_wNum));
			return;
		}

		// to do ����Ŀ��
		AdjustDiscussStatus(EmDisChnAddEp);
	}		
	else if (em_DisListOpr_Del == tDisList.m_emOprType)
	{
		// ɾ��
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
			// to do ����Ŀ��
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

	//�ظ�umc �������
	pInst->NotifyMsgToServiceForUI(ev_AuxMixVacSwitchInd, &tVacOpr, sizeof(TConfAuxMixVacOpr), &tLogUser);

	return;
}

void CUmsDiscussMgr::DiscussMixVacOprFormUmcCnc(TConfAuxMixVacOpr& tVacOpr)
{
	CUmsConfInst* pInst = Inst();
	tVacOpr.m_wOprRet = TP_RET_OK;
	
	if (tVacOpr.m_bVacOn != m_bUIVacOn)
	{// �ı���������״̬
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
		
		//���Ǳ�����㣬��ȡ�øû᳡�ı���EpID
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
	{// �ϼ�֪ͨ�¼���������(��������)

		memcpy(m_atDiscussObj, tNtfy.m_atDiscussObj, sizeof(TDiscussObjInfo)*emDiscussObjEnd);
		memcpy(&m_tEpAudInfo, &tNtfy.m_tEpAudInfo, sizeof(TDiscussEpAudInfo));
		m_tDiscussInfo.SetSpecialEp(m_atDiscussObj[emDiscussObjForSpeakerEp].m_wReserve); 
		

		pInst->GetBas()->AdjustChairAudBas();
		pInst->GetBas()->AdjustSpeakerBas();

		if (m_bDiscussStaus)
		{// ����
			pInst->TryAdjustVirSingleBas();

			AdjustAllNodeToDiscuss(TRUE);
		}
		else
		{
			// ��������㲥��������
			pInst->TryAssignVirSingleBas();

			m_bDiscussStaus = TRUE;
			AdjustAllNodeToDiscuss(FALSE);
		}
	}
	else 
	{// �ϼ�֪ͨ�¼��˳�����

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
		{// ����������
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
		{// ����������
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

			// ��ʾ��������ʧ��
			pInst->NotifyReasonToUI( emType, TP_UMS_Discard_AddEp, pInst->chairID(), pEpInfo->m_wEpID, (u32)emOprRes);
			RemoveEpFromDiscussChan(pEpInfo);
		}
	}

	if (wFailNum == wEpNum)
	{// ȫʧ���ˣ����ۿ�ʼʧ��
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
		{// �����µ�list�У�ɾ��
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
		{// ����list�У����
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
				{// ��ʾ��������ʧ��
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
	{// �Ƿ�����Ч�᳡
		MdlError(Ums_Mdl_Call, ("[AddEpInListFormUI] EpID InValid! ConfID:%d, EpID:%d\n", 
			pInst->GetInsID(), wEpId));
		return em_Discuss_Invalid_Ep;
	}
	
	if (!m_tDiscussInfo.m_tDiscussEpFromUI.AddMixID(wEpId))
	{// ��ӻ᳡����ӵ����
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
	{// �ϵ��������������ϼ����ã�
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
	{// �¼��᳡
		// �򿪵��¼���һ·��Ƶͨ��
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
	{// �����۵��ն˷���ͨ����Ϊ0����ҪУ���»���ͨ���Ƿ����
		MdlError(Ums_Mdl_Call, ("[AddEpInDiscussChan] pMixRes is Full! EpID:%d, ConfID:%d\n", 
			ptEpInfo->m_wEpID, pInst->GetInsID()));
		
		return em_Discuss_No_MixChan;
	}

	// �᳡�ķ���ͨ��û�д򿪣���ռ�û���ͨ��
	if (ptNode->IsVidSndValid() && ptNode->IsAudSndValid())
	{
		pInst->GetEapu()->AddMember(pMixRes, ptEpInfo->m_wEpID, TP_MAX_STREAMNUM);
	}
#endif

	// ����ʶ��˻᳡��������
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
	// �᳡�˳�����������Ŀ���Ӧ�Ļ�������
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

	// �ͷ��´���Ƶͨ��
	if (ptNode != ptForeFatherNode && ptNode->IsAudRcvValid())
	{
        pInst->GetPutAudMgr()->ReleaseAudChnl(ptNode->m_wEpID, em_putauduser_discuss);
		CNetPortMgr::FreeMediaTrans(pInst, ptEpInfo->m_cToPutAuddrDsInfo);
		ptEpInfo->ClearPutAuddr();
	}

	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		// �ͷ�����
		if (ptEpInfo->m_awGetIndex[wIndex] < TP_UMS_MAX_CALLNUM)
		{
			pInst->GetVidAudEx()->Release(pInst, ptEpInfo->m_awGetIndex[wIndex]);
		}
	}
	ptEpInfo->ClearGetVidAddr();


	if (!ptEpInfo->m_bIsSmallChanOn)
	{//û��С�������ն��˳����ۣ������ͷ����䣬�ָ��ֱ���
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
	
	// �����ڷ��Ի᳡����
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
			{// �Ҳ������Ի᳡��ֱ�ӷ���
				MdlError(Ums_Mdl_Call, ("[AdjustDiscussStatus] Can't Find Vaild Ep! ConfId:%d, OprType:%s, OprEp:%d, SpeakerId:%d\n", pInst->GetInsID(), 
					GetOprTypeName(emType), wOprEpId, pInst->curSpeakerID()));
				return;
			}
		}
		wSpeakerIdInDiscuss = ptEpInfo->m_wEpID;
	}
	// ��¼���Ի᳡
	m_tDiscussInfo.m_tSpeakerRec.AddRec(wSpeakerIdInDiscuss);
	
	u16 wIndex = 0;
	TDiscussOprInfo tOprInfo;
	tOprInfo.m_emOprType = emType;
	tOprInfo.m_wEpID = wOprEpId;
	
	// ����Ŀ��
	UmsDiscussOprCycle(wIndex, emDiscussObjEnd, 
		m_apcDisObj[(EmDiscussModleObj)wIndex]->AdjustDstEpInfo(&m_tDiscussInfo, tOprInfo, wSpeakerIdInDiscuss));
	
	// CUmsDiscussMgrҲ������һ��Ŀ�꣬��Ҫ����֪ͨ������Ҳ��Ҫ������
	UptateDiscussObjInfo();

	// ������ؽ����ĵ�������Ϊ�������ο��ǣ�
	u8 byAdjustType; // 0: ����->������; 1: ������->������; 2: ����->���ۣ�3: ������->����
	if (!m_atDiscussObj[emDiscussObjForSpeakerEp].IsVaildObj())
	{// ���Ի᳡Ŀ����Ч��˵����ʱ������ֻ��һ�����Ի᳡����
	//  ���֮ǰ������״̬������Ҫ��Ϊ������״̬�����֮ǰ�Ƿ�����״̬����ά�ֲ���
		if (m_bDiscussStaus)
		{
			m_bDiscussStaus = FALSE;
			byAdjustType = 0; // ����->������
		}
		else
		{
			byAdjustType = 1; // ������->������
		}
	}
	else
	{
		if (m_bDiscussStaus)
		{
			byAdjustType = 2; // ����->����
		}
		else
		{
			m_bDiscussStaus = TRUE;
			byAdjustType = 3; // ������->����
		}
	}

	MdlHint(Ums_Mdl_Call, ("[AdjustDiscussStatus] ConfId:%d, OprType:%s, OprEp:%d, SpeakerId:%d, byAdjustType:%d\n", pInst->GetInsID(), 
		GetOprTypeName(emType), wOprEpId, pInst->curSpeakerID(), byAdjustType));


	if (1 < byAdjustType)
	{// ��������
#ifndef Test_No_Res
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{// ����û��С�����᳡�����䣨���ڴ�С����ʱ�������������䣩
			ptEpInfo = &m_tDiscussInfo.m_atDiscussEpInfo[wIndex];
			if (!ptEpInfo->m_bUsed || !ptEpInfo->IsValid() || ptEpInfo->m_bIsSmallChanOn)
			{
				continue;
			}

			AdjustBasForDiscussEpBakMethod(ptEpInfo);
		}
		
		if (wSpeakerIdInDiscuss != pInst->curSpeakerID() && 2 == byAdjustType && 0 != pInst->GetDelayTime())
		{// ����� pInst->curSpeakerID() ���Ϸ�����
			SetDelayStat(1);
			FreeDsForNewAndOldSpeaker(wSpeakerIdInDiscuss, pInst->curSpeakerID());
		}

		if (EmDisChnEpChangeSeat == emType)
		{// ����ϯ��ֻ��Ҫ���������᳡Ŀ���vmp�����Ի᳡Ҳ�����ǵ�����
			m_apcDisObj[emDiscussObjForSpeakerEp]->AdjustDstVidToVmpTpDsInfo(&m_tDiscussInfo, wSpeakerIdInDiscuss);
			m_apcDisObj[emDiscussObjForSingleScrEp]->AdjustDstVidToVmpTpDsInfo(&m_tDiscussInfo, wSpeakerIdInDiscuss);
		}
		else
		{
			// ����Ŀ�굽�ϳɺͻ����Ľ���
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

		// �Ƿ���Ҫ�з��Ի᳡
		if (wSpeakerIdInDiscuss != pInst->curSpeakerID())
		{
			pInst->ChangeSpeaker(wSpeakerIdInDiscuss, NULL);
			//֪ͨCNS�����˱��
			pInst->NotifyApplySpeakerToUI();
		}
		else
		{
			CNetPortMgr::CreateSpeakerToVirSpeaker(pInst);
		}
		// �������᳡�����۽���
		AdjustAllNodeToDiscuss(2==byAdjustType);

	}
	else
	{// �˳�����
		// �Ƿ���Ҫ�з��Ի᳡
		if (wSpeakerIdInDiscuss != pInst->curSpeakerID())
		{
			pInst->ChangeSpeaker(wSpeakerIdInDiscuss, NULL);
			pInst->GetVmp()->AdjustSpeakerVmp(TRUE);
			if (1 == byAdjustType)
			{
				pInst->AdjustNewSpeakerToAllNode();
			}
			//֪ͨCNS�����˱��
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

		// ���л᳡��һ�ιؼ�֡
		ptNode->m_tRmtChan.ResetFastStatis();

		if (ptNode->IsUms() && ptNode->m_wEpID != Inst()->chairID())
		{// 
			if (pInst->IsChairConf() && m_bDiscussStaus)
			{// ���ϼ���n-1ģʽ��Ƶ�����´�
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
            
			// ֪ͨ�����ڱ�����ums����״̬
			MakeCasecadeObjNtfy(ptNode, tNtfy);
			
			pInst->GetNodeMgr()->MakeCallerHandle(tHandle, ptNode->m_wEpID);
			UmsSendConfCtrl(tHandle, evtp_UmsDiscussScreenStat_Notify, &tNtfy, sizeof(tNtfy));
		}

		if (bAdjust)
		{// �����µ�������ҲҪ��youareseeing
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

	//������᳡����һ�ιؼ�֡
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
	{// �������
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
	{// ������������
		if (!pMixRes->m_bMixMotive)
		{
			pInst->GetEapu()->StartVac(pMixRes);
		}
	}
	else
	{// �ر���������
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
{// ���½��洫���������۳�Ա�б�
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
		{// Mcu �¼��᳡������Ϊ���۵ĳ�Ա�����ܵ�ȡ������
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
		
		m_atDiscussObj[(EmDiscussModleObj)wType].Clear();  // �����
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atDiscussObj[EmDiscussModleObj(wType)].m_abIsVaild[wIndex] = ptInfo->m_atScreenInfo[wIndex].IsScreenValid();
			m_atDiscussObj[EmDiscussModleObj(wType)].m_atEpAlias[wIndex] = ptInfo->m_atScreenInfo[wIndex].m_tAlias;
		}
	}

	if (m_tDiscussInfo.IsSpecialEpVaild())
	{// ���Ի᳡�ǵ�����ʱ������������specialĿ��
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
		m_tEpAudInfo.Clear(); // ֪ͨ��ɺ����

		if (m_tDiscussInfo.IsSpecialEpVaild())
		{// ������speicalep�ڴ�ums���¼�����ô��Ҫ֪ͨ��ȥ
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

	/*�ж��Ƿ��п��õ�ý����Դ*/
	//�������,����������ռ�������ϳ���
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
		//�����˺ϳɴ��ڣ�������6���ϳ���
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
	
	// ֪ͨ��ϯ��������״̬
	Inst()->NotifyConfCtrlMsgToCns(ev_UmsConfAMixUpdate_Nty,  Inst()->chairID(), &tDisInfo, sizeof(tDisInfo));
	
	// ֪ͨumc
	Inst()->NotifyMsgToServiceForUI(evtp_AuxMixInfo_Notify, &tDisInfo, sizeof(TConfAuxMixInfo));
	return;
}

// void CUmsDiscussMgr::AdjustBasForDiscussEp( TDiscussEpInfo* ptEpInfo )
// {// û��С�����Ļ᳡
// //	 a����Ҫ��ʾ���ն˴�Сͼ��ʱ����С���������ռ��������Դ����������Դ����Сͼ����ʾ��̬ͼƬ 
// //	    ��ע�������ն��Ƿ�֧�ֽ��ֱ��ʣ���Ҫ��֤��ͼ���������
// //   b��ֻ��Ҫ��ʾ�ն�Сͼ��ʱ�����ն�ֱ�ӽ��ֱ���
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
// 	{// ��������̬�������䣻���ռ��7��
// 		
// 		wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
// 		if (IsNeedBasForDiscussEp(ptEpInfo->m_wEpID, wCurIndex))
// 		{// ��Ҫ���棬��û�з������䣬���Է���
// 			if (NULL != ptEpInfo->m_apcBas[wCurIndex])
// 			{// �Ѿ������ˣ������ظ�����
// 				continue;
// 			}
// 			
// 			if (!pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
// 			{// û�з��䵽���䣬���֮ǰ���˷ֱ��ʣ��ͻָ�����֤��ͼ������
// 				if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
// 				{// 
// 					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
// 					ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
// 				}
// 				continue;
// 			}
// 
// 			ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
// 			// �����������ʽ
// 			TUmsVidFormat tVidFormat;
// 			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
// 			tVidFormat.m_emRes = emTPV480x272;
// 			tVidFormat.m_wFrameRate = 15;
// 			pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
// 			
// 			if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
// 			{// ���뵽�����䣬�ָ������ֱ��ʣ����ڽ����棬С����������
// 				pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
// 				ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
// 			}
// 		}
// 		else
// 		{// ����Ҫ����
// 			
// 			if (ptEpInfo->m_bMtAdjustRes)
// 			{// �ܽ��ֱ����ն�
// 				if (NULL != ptEpInfo->m_apcBas[wCurIndex])
// 				{
// 					pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wCurIndex]);
// 					ptEpInfo->m_apcBas[wCurIndex] = NULL;
// 				}
// 
// 				if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex])
// 				{// ���ֱ��ʣ���С����
// 					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, emTPV480x272);
// 				    ptEpInfo->m_aemVideoRes[wCurIndex] = emTPV480x272;
// 				}
// 			}
// 			else
// 			{// ���ܽ��ֱ����նˣ���Ҫ������ܽ�С����
// 				if (NULL == ptEpInfo->m_apcBas[wCurIndex])
// 				{// 
// 					if (pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
// 					{// ��������
// 						ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
// 						// �����������ʽ
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
{// û��С�����Ļ᳡
	//	 a����Ҫ��ʾ���ն˴�Сͼ��ʱ����С���������ռ��������Դ����������Դ���򽵷ֱ��� 
	//   b��ֻ��Ҫ��ʾ�ն�Сͼ��ʱ����ռ��������Դ���ն�ֱ�ӽ��ֱ��ʣ�����ն˲�֧�ֽ��ֱ��ʣ��ų�����������
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
	{// ��������̬�������䣻���ռ��7��
		
		wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;
		if (IsNeedBasForDiscussEp(ptEpInfo->m_wEpID, wCurIndex))
		{// ��Ҫ���棬��û�з������䣬���Է���
			if (NULL != ptEpInfo->m_apcBas[wCurIndex])
			{// �Ѿ������ˣ������ظ�����
			    ptEpInfo->m_awBasUserinfo[wCurIndex].m_wDisUserCount = 1;
				continue;
			}
			
			if (!pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
			{// û�з��䵽���䣬��Ҫ���Խ��ֱ���
				if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex] && ptEpInfo->m_bMtAdjustRes)
				{// 
					pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, emTPV480x272);
					ptEpInfo->m_aemVideoRes[wCurIndex] = emTPV480x272;
				}
				continue;
			}

            ptEpInfo->m_awBasUserinfo[wCurIndex].m_wDisUserCount = 1;

			
			ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
			// �����������ʽ
			TUmsVidFormat tVidFormat;
			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
			tVidFormat.m_emRes = emTPV480x272;
			tVidFormat.m_wFrameRate = 15;
			pInst->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
			
			if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
			{// ���뵽�����䣬�ָ������ֱ��ʣ����ڽ����棬С����������
				pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
				ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
			}
		}
		else
		{// ����Ҫ����
			
			if (ptEpInfo->m_bMtAdjustRes)
			{// �ܽ��ֱ����ն�
				ptEpInfo->m_awBasUserinfo[wCurIndex].m_wDisUserCount = 0;

				if ( 0 == ptEpInfo->m_awBasUserinfo[wCurIndex].m_wSelUserCount)
				{
					if (NULL != ptEpInfo->m_apcBas[wCurIndex])
					{
						pInst->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wCurIndex]);
						ptEpInfo->m_apcBas[wCurIndex] = NULL;
					}
					
					if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex])
					{// ���ֱ��ʣ���С����
						pInst->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, emTPV480x272);
						ptEpInfo->m_aemVideoRes[wCurIndex] = emTPV480x272;
					}
				}

			}
			else
			{// ���ܽ��ֱ����նˣ���Ҫ������ܽ�С����
				if (NULL == ptEpInfo->m_apcBas[wCurIndex])
				{// 
					if (pInst->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
					{// ������������
						ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
						// �����������ʽ
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
		{// �ָ��ֱ���
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
{// ��ϳ�������ؼ�֡

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
	{//���Ի᳡��special�᳡��������, ��ϳ�������ؼ��ؼ�֡
		AskKeyFrameToVmp(emDiscussObjForSpeakerEp, wScreenIndex);
	}
	else if (ptNode->IsThreeVidRcv())
	{//����Ŀ��
		if (pInst->GetBas()->IsSpeakerNeedBas(ptFatherNode->m_tVidRcvFormat.m_tFormat))
		{// ����������
			pInst->GetBas()->SeeSpeakerAskFrameToBas(wScreenIndex);
		}
		else
		{// ��ϳ�������
			AskKeyFrameToVmp(emDiscussObjForThreeScrEp, wScreenIndex);
		}
	}
	else
	{//����Ŀ��
		if (m_pcConf->GetBas()->IsSpeakerNeedBas(ptFatherNode->m_tVidRcvFormat.m_tFormat))
		{// ����������
			pInst->GetBas()->AskFrameToScreenBas(pInst->GetSpeaker().m_pcSingleBas);
		}
		else
		{// ��ϳ�������
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
	{// ��ɾ�����ֵ��·����˵Ľ���
		m_wNewSpeaker = ptNode->m_wEpID;

		if (ptNode->IsUms() || !ptNode->IsVidRcvValid())
		{
			break;
		}

		bIsSpecialEp = IsSpeacialEp(ptNode->m_wEpID);

		if (ptNode->IsSingleVidRcv())
		{// ����
			if (ptNode->m_aemObj[MIDSCREENINDEX] == emObjDiscard)
			{// Ŀ�������ۣ���ɾ��Ƶ
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				wDelNum++;
			}

			// ����������Ƶʼ��ȡ��ͬһ����������û��Ҫɾ��
		}
		else if (ptNode->IsThreeVidRcv() && bIsSpecialEp)
		{// �л��Ǹ�����Ļ᳡������
		//  spcialep�ֳ�Ϊ�����ˣ��������᲻��ģ�ֻ���м�ͺã������е������ԣ����ٴ��л�����������ԣ������������Σ�

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
		{// ����
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
	{// ɾ�����ֵ��Ϸ����˵Ľ���
		m_wOldSpeaker = ptNode->m_wEpID;

		if (ptNode->IsUms() || !ptNode->IsVidRcvValid())
		{
			break;
		}

		bIsSpecialEp = IsSpeacialEp(ptNode->m_wEpID);

		if (ptNode->IsSingleVidRcv())
		{// ����
			if (ptNode->m_aemObj[MIDSCREENINDEX] == emObjDiscard)
			{// Ŀ�������ۣ���ɾ��Ƶ
				atDelToSndAddr[wDelNum] = ptNode->m_tRmtChan.m_atVidDec[MIDSCREENINDEX].m_tChanAddr.m_tRtpAddr;
				atDelFromRcvAddr[wDelNum] = ptNode->m_aptChanAddr[MIDSCREENINDEX]->m_tVid.m_tRtcpForSnd;
				wDelNum++;
			}

			// ����������Ƶʼ��ȡ��ͬһ����������û��Ҫɾ��
		}
		else if (ptNode->IsThreeVidRcv() && bIsSpecialEp)
		{// �Ϸ����˳�Ϊ�Ǹ�spcialep���������᲻��ģ�ֻ���м�ͺã������е������Ի�����������Σ�
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
			// ����
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
		{// �¼����Ի᳡��speaciaep��nģʽ������ϯͨ��ȡ
			return;
		}

		TTPDsFrom tScrAddr;
		if (ptNode->IsThreeAudRcv())
		{
			if (pInst->GetBas()->IsSpeakerNeedAudBas(ptNode->m_tAudRcvFormat.m_tFormat.m_emFormat))
			{// ����Ƶ������ȡ
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
			{// ����Ƶ������ȡ
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
{   // wScreenIndex Ϊ 0 ��1��2 Ϊ�᳡��Ӧ���ָ��ֱ���
	// wScreenIndex Ϊ 3(TP_MAX_STREAMNUM) Ϊ�᳡�������ָ��ֱ���

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
	{ // �������۳�Ա, ���ûָ��ֱ���

		MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::RestoreAdjustedResForSelEp  EpNotDisMember  ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n", 
			                   m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex));

		return TRUE;
	}

	if (ptEpInfo->m_bIsSmallChanOn )
	{  // û��С�����Ļ᳡�Żή�ֱ��ʣ���С�����Ļ��鲻��Ҫ�ָ�������
		return TRUE;
	}


	if (ptNode->IsSingleVidSnd())
	{
		// �����Ҫ�ָ��Ļ᳡�ǵ�����ֱ�ӻָ��м���
        wScreenIndex = MIDSCREENINDEX;
	}


	BOOL32 errorflag = FALSE;
	u8 aAssignIndex[TP_MAX_STREAMNUM] = {0};

	u16 wIndex;
    s32 symbolflag = 1;
	u16 wCurIndex;

	if(wScreenIndex < TP_MAX_STREAMNUM)
	{// �ָ�ĳ��

		if (NULL != ptEpInfo->m_apcBas[wScreenIndex])
		{   // �Ѿ������ˣ������ظ�����
			MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::RestoreAdjustedResForSelEp  ScreenBas != NULL  ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n", 
				    m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex));

			ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount++; // bas ���ü�����sel ʹ�ã�
			return TRUE;
		}
		
		if (!m_pcConf->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wScreenIndex]))
		{// û�з��䵽����, ���ָܻ�
			
			MdlError(Ums_Mdl_Call, ("RestoreAdjustedResForSelEp  no bas resource confid:%d  seltargetep:%d .\n", 
				m_pcConf->GetInsID(), wSelTargetEp));
			
			return FALSE;
		}

		ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount++;
		
		ptEpInfo->m_apcBas[wScreenIndex]->SetCB(DiscussBasCB, this);
		// �����������ʽ
		TUmsVidFormat tVidFormat;
		tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
		tVidFormat.m_emRes = emTPV480x272;
		tVidFormat.m_wFrameRate = 15;
		m_pcConf->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wScreenIndex], ptEpInfo->m_wEpID, wScreenIndex, 1, &tVidFormat);
		
		if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wScreenIndex])
		{// ���뵽�����䣬�ָ������ֱ��ʣ����ڽ����棬С����������
			m_pcConf->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wScreenIndex, ptEpInfo->m_aemVideoRes[wScreenIndex], TRUE);
			ptEpInfo->m_aemVideoRes[wScreenIndex] = emTPVResEnd;
		}
	}
	else 
	{// �ָ��᳡������

		symbolflag = 1;
		for (wIndex = 1; wIndex <= ptEpInfo->m_wStrceenNum; ++wIndex, symbolflag *= -1)
		{
			wCurIndex = MIDSCREENINDEX + wIndex / 2 * symbolflag;

			if (NULL != ptEpInfo->m_apcBas[wCurIndex])
			{// �Ѿ������ˣ������ظ�����
				MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::RestoreAdjustedResForSelEp  ScreenBas != NULL Continue ConfID:%d, OprEpId:%d, ScreenIndex:%d.\n", 
					m_pcConf->GetInsID(), wSelTargetEp,  wCurIndex));

				continue;
			}
			
			if (!m_pcConf->GetBas()->AssignScreenBas(ptEpInfo->m_apcBas[wCurIndex]))
			{// û�з��䵽����, ���ָܻ�
				
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

			ptEpInfo->m_awBasUserinfo[wCurIndex].m_wSelUserCount++; //bas ���ü���
			
			ptEpInfo->m_apcBas[wCurIndex]->SetCB(DiscussBasCB, this);
			// �����������ʽ
			TUmsVidFormat tVidFormat;
			tVidFormat = ptNode->m_tVidSndFormat.m_tFormat;
			tVidFormat.m_emRes = emTPV480x272;
			tVidFormat.m_wFrameRate = 15;
			m_pcConf->GetBas()->AdjustScreenBas(ptEpInfo->m_apcBas[wCurIndex], ptEpInfo->m_wEpID, wCurIndex, 1, &tVidFormat);
			
			if (emTPVResEnd != ptEpInfo->m_aemVideoRes[wCurIndex])
			{// ���뵽�����䣬�ָ������ֱ��ʣ����ڽ����棬С����������
				m_pcConf->GetNodeMgr()->AdjustNodeRes(ptEpInfo->m_wEpID, wCurIndex, ptEpInfo->m_aemVideoRes[wCurIndex], TRUE);
				ptEpInfo->m_aemVideoRes[wCurIndex] = emTPVResEnd;
			}

		}

	}


	CNetPortMgr::AdjustDiscussEpToBas(m_pcConf, ptEpInfo);


	// ˢ�µ�VMP �Ľ���
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
	{ // �������۳�Ա, ���ûָ��ֱ���
		return TRUE;
	}
	
	if (ptEpInfo->m_bIsSmallChanOn  )
	{  // û��С�����Ļ᳡�Żή�ֱ��ʣ���С�����Ļ��鲻��Ҫ�ָ�������
		return TRUE;
	}

	BOOL32 bAdjustDs = FALSE;

	u16 wIndex;
    s32 symbolflag = 1;
	u16 wCurIndex;

    if(wScreenIndex < TP_MAX_STREAMNUM)
	{ //�ͷ�ĳһ����

	  MdlHint(Ums_Mdl_Call, ("CUmsDiscussMgr::AdjustResForUnSelEp  ConfID:%d, OprEpId:%d, ScreenIndex:%d, Userinfo[%d] = %d. \n", 
			m_pcConf->GetInsID(), wSelTargetEp,  wScreenIndex, wScreenIndex, ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount));
		
       if(ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount > 0)
	   {
           ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount--;

		   if (0 == ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wSelUserCount &&
			   0 == ptEpInfo->m_awBasUserinfo[wScreenIndex].m_wDisUserCount)
		   {
			   
			   if (ptEpInfo->m_bMtAdjustRes)
			   {// �ܽ��ֱ����ն�
				   if (NULL != ptEpInfo->m_apcBas[wScreenIndex])
				   {
					   m_pcConf->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wScreenIndex]);
					   ptEpInfo->m_apcBas[wScreenIndex] = NULL;
				   }
				   
				   if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wScreenIndex])
				   {// ���ֱ��ʣ���С����
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
					{// �ܽ��ֱ����ն�
						if (NULL != ptEpInfo->m_apcBas[wCurIndex])
						{
							m_pcConf->GetBas()->ReleaseScreenBas(ptEpInfo->m_apcBas[wCurIndex]);
							ptEpInfo->m_apcBas[wCurIndex] = NULL;
						}
						
						if (emTPVResEnd == ptEpInfo->m_aemVideoRes[wCurIndex])
						{// ���ֱ��ʣ���С����
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
		//���������ͷŲ��彻��
		CNetPortMgr::AdjustDiscussEpToBas(m_pcConf, ptEpInfo);

		// ˢ�µ�VMP �Ľ���
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
/////////////////////////����Ŀ�������//////////////////////////////
/////////////////////////////////////////////////////////////////////

//////////////////////////////////////////
////////////// ����Ŀ��ʵ�� //////////////
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
{// ����Ŀ����Դ���룬���ش���
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
	u32 dwNode = m_atMix[wIndex].m_ptMixRes->m_tEqpRes.m_dwEqpNode; // ��֤�����õĻ���������ͬһ��apu2�忨

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
{// ����Ŀ����Դ�ͷţ����ش���
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
{// ����Ŀ����Դ�鿴�����ش���
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
{// ����Ŀ����Դ���ش���
	if (wScreenIndex < TP_MAX_STREAMNUM)
	{
		return m_atVmpTp[wScreenIndex].m_pcVmpTpRes;
	}
	return NULL;
}

TAudMixInfo* CDiscussObjectBase::GetMixRes( u16 wScreenIndex )
{// ����Ŀ����Դ���ش���
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
	{// ���node�������ڵ�ȷ���ķ��Ի᳡����һ������m_pcConf->currspeakerID
		m_tDstEpInfo.Clear();
		ptDiscussInfo->ResetSpecialEp();
		return;
	}

	if (NULL == ptDiscussInfo->GetFirstVaildEp(wSpeakerId))
	{// ����������ֻ��һ�����Ի᳡��Ŀ����Ϣ��Ҫ���
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
{//ȷ��ĳ���᳡�����Ƿ�����Ŀ��Ĵ�ͼ�񣨼��費��Ҫ��ͼ��
	return VALID_SCREEN_INDEX(m_tDstEpInfo.GetIndexByEp(wEpId, wScreenIndex));
}

TDiscussDstEpInfo* CDiscussObjectBase::GetDiscussObj()
{
	return &m_tDstEpInfo;
}

void CDiscussObjectBase::FillUpSingleScrEp(TDiscussInfo* ptDiscussInfo, TDiscussDstEpInfo* ptDstEpInfo, TDiscussDstEpInfo* ptDstEpTemp /* = NULL */)
{// ������״̬��������䵥���᳡��ΪĿ��
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
{// ����Ŀ���У�ɾ���᳡��᳡���ߣ����ܻᵼ�´�ͼ��Ϊ�գ����԰�������Ŀ���ϵ������᳡�ӽ�������Ӧ����
	u16 wThreeScrEp = ptDstEpInfo->FindThreeScreenDstEp();
	if (TP_INVALID_INDEX == wThreeScrEp)
	{// û�������᳡��ΪĿ�귵��
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
{// �����Ŀ��᳡�Ƿ��������У����ڵĻ���ɾ��
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
{// �˺���Ŀ�ģ���֤Ŀ����wAddIndex����ptNode
	// �������Σ�1. ptNode����Ŀ���У���ôptNodeȡ��wAddIndex��ԭ��Ŀ��
	// 2. ptNode��Ŀ���У����ǲ���wAddIndex�ϣ���ô��wAddIndex��ԭ��Ŀ���ptNode�Ե�
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
{// �������������м䣬����ߣ����ұߵ�˳������������ӻ᳡��Сͼ������������������
// ���᳡�������У���ʼ�����м�����ǰ��
	u16 wIndex = 0;
	u16 wAddEpId = 0;
	u16 wAddIndex = MIDSCREENINDEX;
	TCallNode* ptAddNode = NULL;
	
	// �����
	UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
		m_tDstEpInfo.m_atScreenInfo[wIndex].ClearVmpEpInfo());

	BOOL32 bIsChairSingle = FALSE;
	wAddEpId = m_pcConf->chairID();
	ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
	if (NULL != ptAddNode && ptAddNode->IsVidSndValid() && ptAddNode->IsInMix())
	{// ���᳡�������У������м��ǰ��
		m_tDstEpInfo.AddVmpDstEp(ptAddNode, wAddIndex);
		wAddIndex = GetNextIndex(wAddIndex);
		bIsChairSingle = ptAddNode->IsSingleVidSnd();
	}

	for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
	{// ����˳���3��
		wAddEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
		if (!TP_VALID_HANDLE(wAddEpId))
		{
			break;
		}

		if (wAddEpId == m_pcConf->chairID())
		{// ��ϯ�ų��������ظ�
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
	{// ����˳��ӵ���
		wAddEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
		if (!TP_VALID_HANDLE(wAddEpId))
		{
			break;
		}

		if (wAddEpId == m_pcConf->chairID())
		{// ��ϯ�ų��������ظ�
			continue;
		}

		ptAddNode = m_pcConf->GetNode(wAddEpId);
		if (NULL != ptAddNode && ptAddNode->IsInMix() && ptAddNode->IsSingleVidSnd())
		{

			if (bIsChairSingle)
			{// ���᳡�ǵ������м�����Ҫ�������������Ա�֤�Գ�
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
				{// ���������3���ٻ���һ����
					wAddIndex = GetNextIndex(wAddIndex);
					wAddNum = 0;
				}
			}
		}
	}
	return;
}

void CDiscussObjectBase::AdjustVmpEpInfoForSingleScreen( TDiscussInfo* ptDiscussInfo )
{// �Ե���������������᳡����δ�ͼ����һ��������Ҳ���������ʾ��������ϯ���ٴ�����з��Լ�¼�Ļ᳡�������ʣ�������
	u16 wIndex = 0;
	u16 wAddEpId = 0;
	TCallNode* ptAddNode = NULL;
	TDiscussEpInfo* ptEpInfo = NULL;
	// �����
	m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX].ClearVmpEpInfo();

	wAddEpId = m_pcConf->chairID();
	ptAddNode = m_pcConf->GetNodeMgr()->GetNode(wAddEpId);
	if (NULL != ptAddNode && ptAddNode->IsVidSndValid() && ptAddNode->IsInMix())
	{// ���᳡�������У�����ǰ��
		m_tDstEpInfo.AddVmpDstEp(ptAddNode, MIDSCREENINDEX);
	}

	// �����ͼ����һ�������᳡�����Ȱ�������ϯҲ�ӽ�С����
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
	{// ������ӷ����ԵĻ᳡(Index��1��ʼ����Ϊ0Ϊ��ǰ���Ի᳡)
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
	{// �������᳡
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
		// �����ptNode�������¼��Ļ᳡�����ϼ��ķ��������䣬�ǰ��ռ�����ʽ����

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
			//�㲥��ϳ��������ٳ�25 �� 50�� ��ֹ��T300������ʽΪ60�����»��濨��
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
{// ����������������18��1��6С��������Ҫ��С��
	tVmpStylle.m_byMemberNum = ptInfo->m_wVmpEpNum + 1; // Сͼ���һ·��ͼ�񣬼�ʹ��ͼ��Ŀ���ǿյ�
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

	// ��0·����ʹû��Ŀ�꣬dwHandle������0������vmp��Ϊ��Ч���������TP_INVALID_INDEX;
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
{// ��֤�����᳡�յ����������ظ���new: ����Ŀ���У���ͼ������������᳡�����ֻ��һ�������������᳡��ϯ��Ӧ������������
	TDiscussScreenInfo* pScrInfo = &tScreenInfo->m_atScreenInfo[wScreenIndex];

	u16 wOprEp = 0;
	u16 wLoop = 0;

	wOprEp = pScrInfo->m_atMember[0].GetHandleOne();
	wLoop = pScrInfo->m_atMember[0].GetHandleTwo();

	if (wThreeScreenEp >0 && wThreeScreenEp < TP_CONF_MAX_CNSNUM)
	{
		tNewMixMember.AddMixMember(wThreeScreenEp, wScreenIndex); // �������᳡Ŀ�꣬��Ӧ������Ӧ������
	}

	if (wOprEp > 0 && wOprEp < TP_CONF_MAX_CNSNUM && wOprEp != wThreeScreenEp)
	{
		tNewMixMember.AddMixMember(wOprEp, wLoop); // �ȰѴ�ͼ��Ӧ�᳡��ϯ�ӽ�������
	}

	for (u16 wIndex = 1; wIndex < UMS_VMP_MAX_RCV;)
	{// ����Сͼ��
		if (0 == pScrInfo->m_atMember[wIndex].m_dwHandle)
		{
			break;
		}
		wOprEp = pScrInfo->m_atMember[wIndex].GetHandleOne();
		if (wOprEp == pScrInfo->m_atMember[wIndex+1].GetHandleOne())
		{// Сͼ���Ǹ�3��
			if (!VALID_SCREEN_INDEX(tScreenInfo->GetIndexByEp(wOprEp)))
			{// Сͼ��ʹ�ͼ��û���ظ���������
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
////////////// ���Ի᳡Ŀ�� //////////////
//////////////////////////////////////////
void CDiscussObjectForSpeakerEp::AdjustDstVidToVmpTpDsInfo(TDiscussInfo* ptDiscussInfo, u16 wSpeakerId)
{// ���Ի᳡�ǵ���������������Ҫ����
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
		{// ��������ʱ�����ߺϳ�����specialEp�᳡��
			pScrInfo = &ptDiscussInfo->m_tSpecialDst.m_atScreenInfo[wIndex];
			GetVmpEncParam(tVmpParam.m_tEncParam, ptSpecialNode, FALSE); // ��specialEp�᳡���ո�ʽ��������᳡���¼��᳡��Ҳ��Ҫ������᳡�Ľ��ո�ʽ���������Ǽ�����ʽ��	
		}
		else if (ptSpeaker->IsSingleVidSnd() && MIDSCREENINDEX != wIndex)
		{// �������ԣ����ߺϳ����ò���ʱ���������
			continue;
		}
		else
		{
			pScrInfo = &m_tDstEpInfo.m_atScreenInfo[wIndex];
			GetVmpEncParam(tVmpParam.m_tEncParam, ptSpeaker, FALSE); // ���Ի᳡Ŀ�꣬�����Ի᳡���ո�ʽ�� ������᳡���¼��᳡��Ҳ��Ҫ������᳡�Ľ��ո�ʽ���������Ǽ�����	
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
{// ���Ի᳡�ǵ���������������Ҫ����
	TCallNode* ptSpeaker = m_pcConf->GetNodeMgr()->GetNode(wSpeakerId);
	if (NULL == ptSpeaker || !ptSpeaker->IsVidSndValid())
	{
		return;
	}

	TDiscussDstEpInfo* ptDstInfo = NULL;
	if (ptSpeaker->IsSingleVidSnd() && ptDiscussInfo->IsSpecialEpVaild())
	{// ��������������᳡���ڣ������˵�����������ȫ�����������᳡ʹ�� �������᳡���ԣ���n-1������
		ptDstInfo = &ptDiscussInfo->m_tSpecialDst;
	}
	else if (ptSpeaker->IsSingleVidSnd())
	{// �������ԣ�û������᳡����������������ʱ����
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
	pMixSync.m_bSpeakerObject = TRUE;//������Ŀ��
	if (wThreeScreenDstEp > 0 && wThreeScreenDstEp < TP_CONF_MAX_CNSNUM)
	{// �������᳡��Ϊ��ͼ���ҵ���Ӧ��ϯ����Ӧ�������ĵ�ͨ������
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			byChanId = m_atMix[wIndex].m_ptMixRes->GetIndx(wThreeScreenDstEp, wIndex);

			pMixSync.Add(m_atMix[wIndex].m_ptMixRes, byChanId);
			m_atMix[wIndex].m_ptMixRes->SetSyncChnl(byChanId);
		}
		// ����ͬ��
		m_pcConf->GetEapu()->SetMixerSyncChnl(pMixSync);
	}
	else
	{// ȡ��ͬ�� to do ...

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
		{// ˫������
			continue;
		}
		
		wEpId = ptMixInfo->m_atChnl[byCanId].m_wEpID;			
		
		bRet = pScrInfo0->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust0 = 1;
			abyFlag0[byAdd] = 1;
			if (bRet)
			{// ����Сͼ����һ����ȫ����
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
			{// ����Сͼ����һ����ȫ����
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
			{// ����Сͼ����һ����ȫ����
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

// ��ʼ״̬��1. ���Ի᳡���ȿ����᳡�������������������ε���
void CDiscussObjectForSpeakerEp::InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	// �����
	m_tDstEpInfo.Clear();

	u16        wIndex = 0;
	u16        wEpId  = 0;
	TCallNode* ptNode = NULL;

	// �������᳡
	wEpId = m_pcConf->chairID();
	ptNode = m_pcConf->GetNode(wEpId);
	if (wEpId == ptSpeakerNode->m_wEpID || NULL == ptNode || !ptNode->IsVidSndValid() || !ptNode->IsInMix())
	{// ���᳡�Ƿ��Ի᳡�����᳡���������У����������б���Ѱ��
		u16 wEpIdTemp1 = 0;  // ��¼��һ�������᳡
		u16 wEpIdTemp2 = 0;  // ��¼��һ�������᳡
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			wEpId = ptDiscussInfo->m_tDiscussEpFromUI.m_awList[wIndex];
			if (!TP_VALID_HANDLE(wEpId))
			{
				break;
			}
			
			if (wEpId == ptSpeakerNode->m_wEpID)
			{// �ų��Լ�
				continue;
			}
			
			ptNode = m_pcConf->GetNode(wEpId);
			if (NULL != ptNode && ptNode->IsInMix())
			{
				if (ptNode->IsThreeVidSnd())
				{// �ҵ�����������ѭ��
					wEpIdTemp1 = wEpId;
					break;
				}
				else if (ptNode->IsSingleVidSnd())
				{// ֻ��¼��һ������
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

		// ������������ε���
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

	// �ҵ���ptNode��Ϊ���Ի᳡Ŀ��
	if (NULL != ptNode && ptNode->IsVidSndValid() && ptNode->IsInMix())
	{
		if (ptSpeakerNode->IsThreeVidSnd())
		{// ���Ի᳡������
			if (ptNode->IsThreeVidSnd())
			{// Ŀ����������һһ��Ӧ
				UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM, 
					m_tDstEpInfo.AddDstEp(ptNode, wIndex, wIndex));
			}
			else
			{// Ŀ���ǵ��������ڷ��Ի᳡���м���
				m_tDstEpInfo.AddDstEp(ptNode, MIDSCREENINDEX, MIDSCREENINDEX);
				
				// �����Ƿ�������������Ҳ�ӽ���
				FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
				
			}
			AdjustVmpEpInfoForThreeScreen(ptDiscussInfo); // Сͼ��
		}
		else
		{// ���Ի᳡�ǵ���
			m_tDstEpInfo.AddDstEp(ptNode, ptNode->GetSpeaker(), MIDSCREENINDEX);
			AdjustVmpEpInfoForSingleScreen(ptDiscussInfo);// Сͼ��
		}
	}
	return;
}

void CDiscussObjectForSpeakerEp::UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	u16 wIndex;
	
	if (ptDiscussInfo->m_wChairEpId!=TP_INVALID_INDEX && ptDiscussInfo->m_wChairEpId != ptSpeakerNode->m_wEpID)
	{// ��ϯ��������Ҳ�Ϊ�����ˣ�������Ŀ��ʼ��Ϊ��ϯ
		if (ptSpeakerNode->IsThreeVidSnd())
		{
			ptDiscussInfo->ResetSpecialEp();
		}
		else if (!ptDiscussInfo->IsSpecialEpVaild())
		{
			TCallNode* ptOldSpeaker = m_pcConf->GetNode(m_pcConf->curSpeakerID());
			if (NULL != ptOldSpeaker && ptOldSpeaker->IsThreeVidSnd())
			{// ��������Ϊ��������ʱ���ϵķ��Ի᳡����Ŀ����Ҫ���⴦��
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
			{// �л�������specialEp������ʱ��Ŀ�겻�ܴӴ���ͨ����Ŀ���л�ȡ
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
			{// ��������Ϊ��������ʱ���ϵķ��Ի᳡����Ŀ����Ҫ���⴦��
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
	{// ��ϯ��������Ҳ�Ϊ�����ˣ�������Ŀ��ʼ��Ϊ��ϯ
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
			// ������䵥��
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
	{// ��ϯ��������Ҳ�Ϊ�����ˣ�������Ŀ��ʼ��Ϊ��ϯ
		InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
		return;
	}

	if (m_pcConf->curSpeakerID() != ptSpeakerNode->m_wEpID)
	{// ˵��ɾ�������Ϸ��Ի᳡, ��ô�Ϸ��Ի᳡Ŀ�꣬�����������·��Ի᳡��������Ҫ�ȵ�bak��ȡ��ӦĿ��
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

	// ɾ���Ļ᳡�п�����Ŀ����
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
////////////// ��ͨ����Ŀ�� //////////////
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
		GetVmpEncParam(tVmpParam.m_tEncParam, ptSpeaker, TRUE); // �㲥����Ŀ�꣬�����Ի᳡���͸�ʽ��	
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
	{// �������᳡��Ϊ��ͼ���ҵ���Ӧ��ϯ����Ӧ�������ĵ�ͨ������
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			byChanId = m_atMix[wIndex].m_ptMixRes->GetIndx(wThreeScreenDstEp, wIndex);

			pMixSync.Add(m_atMix[wIndex].m_ptMixRes, byChanId);
			m_atMix[wIndex].m_ptMixRes->SetSyncChnl(byChanId);
		}
		// ����ͬ��
		m_pcConf->GetEapu()->SetMixerSyncChnl(pMixSync);
	}
	else
	{// ȡ��ͬ�� to do ...
		for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{	
			pMixSync.Add(m_atMix[wIndex].m_ptMixRes, byChanId);
			m_atMix[wIndex].m_ptMixRes->SetSyncChnl(byChanId);
		}
		// ȡ��ͬ��
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
		{// ˫������
			continue;
		}
		
		wEpId = ptMixInfo->m_atChnl[byCanId].m_wEpID;			
		
		bRet = pScrInfo0->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust0 = 1;
			abyFlag0[byAdd] = 1;
			if (bRet)
			{// ����Сͼ����һ����ȫ����
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
			{// ����Сͼ����һ����ȫ����
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
			{// ����Сͼ����һ����ȫ����
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

// ��ʼ�������᳡Ŀ��
void CDiscussObjectForThreeScreenEp::InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	// �����
	m_tDstEpInfo.Clear();

	u16 wIndex = 0;
	if (ptSpeakerNode->IsThreeVidSnd())
	{// ���Ի᳡������, Ŀ������һһ��Ӧ
		UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
			m_tDstEpInfo.AddDstEp(ptSpeakerNode, wIndex, wIndex));
	}
	else
	{// ���Ի᳡�ǵ������Ȱѷ��Ի᳡�����м��������໹�е�����������˳��Ҳ�ӽ��������3��
		m_tDstEpInfo.AddDstEp(ptSpeakerNode, MIDSCREENINDEX, MIDSCREENINDEX);

		FillUpSingleScrEp(ptDiscussInfo, &m_tDstEpInfo);
	}

	// ����Сͼ��
	AdjustVmpEpInfoForThreeScreen(ptDiscussInfo);
	// ����һ��
	UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
		ptDiscussInfo->m_atThreeScrBak[wIndex] = m_tDstEpInfo.m_atScreenInfo[wIndex]);

	return;
}

void CDiscussObjectForThreeScreenEp::UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	u16 wIndex = 0;
	if (ptSpeakerNode->IsThreeVidSnd())
	{// ���Ի᳡������, ��ͼ��һһ��Ӧ��ֱ���滻֮ǰĿ��
		m_tDstEpInfo.m_wAddIndex = MIDSCREENINDEX;
		UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
			m_tDstEpInfo.AddDstEp(ptSpeakerNode, wIndex, wIndex));
	}
	else
	{// ���Ի᳡�ǵ���				
		u16 wAddIndex = TP_INVALID_INDEX;
		if (!VALID_SCREEN_INDEX(m_tDstEpInfo.GetIndexByEp(ptSpeakerNode->m_wEpID)))
		{
			wAddIndex = m_tDstEpInfo.FindAddScrIndex();
			if (!VALID_SCREEN_INDEX(wAddIndex))
			{// ��������Ŀ�궼�ǵ����᳡����ô����AddIndex��ʼ�滻
				wAddIndex = m_tDstEpInfo.m_wAddIndex;
				m_tDstEpInfo.m_wAddIndex = GetNextIndex(wAddIndex);
			}
			m_tDstEpInfo.AddDstEp(ptSpeakerNode, MIDSCREENINDEX, wAddIndex);
		}

		if (ptDiscussInfo->IsSpecialEpVaild())
		{// ������Ŀ��Ĵ���
			AdjustDstForSpecialEp(wAddIndex, ptSpeakerNode, ptDiscussInfo);
		}
	}

	// �㲥����Ŀ�꣬�з��Ի᳡������Сͼ����Ҫ����

	// ����һ��
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

		// ����һ��
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
		{// ���Ի᳡��ɾ�ˣ���ͨ�������µķ��Ի᳡
			m_tDstEpInfo.Clear();
			UmsDiscussOprCycle(wIndex, TP_MAX_STREAMNUM,
				m_tDstEpInfo.AddDstEp(ptSpeakerNode, wIndex, wIndex));
		}
	}
	else
	{
		CheckOutDstInfo(ptDiscussInfo, &m_tDstEpInfo);
		
		if (!VALID_SCREEN_INDEX(m_tDstEpInfo.GetIndexByEp(ptSpeakerNode->m_wEpID)))
		{// ���Ի᳡����Ŀ����
			wIndex = m_tDstEpInfo.FindIdleScrIndex();// �϶����ҵ�
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
////////////// ��ͨ����Ŀ�� //////////////
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
		GetVmpEncParam(tVmpParam.m_tEncParam, ptSpeaker, TRUE);// �㲥����Ŀ�꣬�����Ի᳡���͸�ʽ��
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
{// ����ͨ���������������������ۻ᳡������˫������
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
		// ���������������᳡ͳһ��3����˫��ҵ�񱣳�һ��
		tInfo.AddMixMember(pEpInfo->m_wEpID, TP_MAX_STREAMNUM);
	}

	BOOL32 bIsAddDualAud = FALSE;
	if (m_pcConf->GetDualMgr()->IsStart())
	{
		wTemp = m_pcConf->GetDualMgr()->GetDualID();
		TCallNode* ptDualNode = m_pcConf->GetNode(wTemp);
		if (NULL != ptDualNode && ptDualNode->IsCns() && 
			emTPAEnd != ptDualNode->m_tDualAudSndFormat.m_tFormat.m_emFormat)
		{// ��������������˫����4
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
		{// ˫������
			continue;
		}
		
		wEpId = ptMixInfo->m_atChnl[byCanId].m_wEpID;			
		bRet = pScrInfo->FindVmpIndexbyEpId(wEpId, byAdd);
		if (byAdd < UMS_VMP_MAX_RCV)
		{
			byAdjust = 1;
			abyFlag[byAdd] = 1;
			if (bRet)
			{// ����Сͼ����һ����ȫ����
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

// ��ʼ������Ŀ��
void CDiscussObjectForSingleScreenEp::InitDstEpInfo(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	m_tDstEpInfo.AddDstEp(ptSpeakerNode, ptSpeakerNode->GetSpeaker(), MIDSCREENINDEX);
	AdjustVmpEpInfoForSingleScreen(ptDiscussInfo);
	// ����һ��
	ptDiscussInfo->m_tSingleScrBak = m_tDstEpInfo.m_atScreenInfo[MIDSCREENINDEX];
	return;
}

void CDiscussObjectForSingleScreenEp::UptateDstEpInfoByChangeSpeaker(TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo)
{
	InitDstEpInfo(ptSpeakerNode, ptDiscussInfo);
	return;
}

void CDiscussObjectForSingleScreenEp::UptateDstEpInfoByChangeSeat( TCallNode* ptSpeakerNode, TDiscussInfo* ptDiscussInfo, TDiscussOprInfo tOprInfo )
{// ���Ի᳡����ϯʱ������Ҫ����
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





