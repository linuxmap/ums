#include "umsbas.h"
#include "dualmgr.h"
#include "callnodemgr.h"
#include "innereventumscall.h"
#include "umsapi.h"
#include "tperrno.h"
#include "dualmgr.h"
#include "umsnetportmgr.h"
#include "umsstackinterface.h"
#include "eventoutsipadapter.h"
#include "innereventumsmpu2.h"
#include "innereventumsaudbas.h"
#include "nodefsm.h"

#ifdef _USE_XMPUEQP_
#include "innereventxmpubas.h"
#include "innereventxmpuaudbas.h"
#include "umsxmpinterface.h"
#endif
#define ASSGIN_VID_BAS_NUM 2
CUmsBas::CUmsBas( CUmsConfInst* pcInst ):CTpHandler(pcInst)
{
	InstClear();
}

CUmsBas::~CUmsBas()
{
	InstClear();
}

void CUmsBas::InstClear()
{
	m_tConfBasMgr.Clear();
	memset(&m_cSpeaker, 0, sizeof(m_cSpeaker));
	memset(&m_cDual, 0, sizeof(m_cDual));
	memset(&m_cChair, 0, sizeof(m_cChair));

	m_wPriNum = 0;
	m_wDualNum = 0;
	memset(&m_atPriFmt, 0, sizeof(m_atPriFmt));
	memset(&m_atDualFmt, 0, sizeof(m_atDualFmt));

	for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		m_atAudBasChair[wIndex].Clear();
		m_atAudBasSpeaker[wIndex].Clear();
	}
	m_tAudBasDual.Clear();
	m_tAudBasSpeakerMix.Clear();


	if (0 != m_tChairToBasDs.GetElementNum())
	{
		CNetPortMgr::FreeMediaTrans(Inst(), m_tChairToBasDs);
		m_tChairToBasDs.Clear();
	}

	if (0 != m_tChairToBasDs.GetElementNum())
	{
		CNetPortMgr::FreeMediaTrans(Inst(), m_tToConfDsEqpDs);
		m_tToConfDsEqpDs.Clear();
	}
}

void CUmsBas::Show()
{
	CUmsConfInst* pInst = Inst();
	TUmsVidFormat* ptVidFormate= NULL;
	u8	byFormatIndx = 0;
	u8	byIndx = 0;
	u8  byInnerIndex = 0;

	msgprintnotime("BasInfo ConfID:%d\n",pInst->GetInsID());
	msgprintnotime("\n");
	//////////////////////////////////////////////////////////////////////////
	//speaker
	msgprintnotime("  SpeakerVidBasInfo-> SpeakerEpID:%d, bSpeaker:%d, ChnlType:%d(0:brd,1:sel)\n", 
				pInst->curSpeakerID(), m_tConfBasMgr.m_bSpeaker, m_cSpeaker.m_emAsgType);
	ptVidFormate = &m_cSpeaker.m_tSndVidFormat;
	msgprintnotime("	SpeakerForamt:%s, %s, %s, FrameRate:%d, BitRate:%d\n", 
		UmsVidFormatPrint(ptVidFormate->m_emFormat),
		UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
		UmsVidResPrint( ptVidFormate->m_emRes),
				ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate);
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if ( !m_cSpeaker.IsBasValid(byIndx) )
		{
			continue;
		}

#ifdef _USE_XMPUEQP_
		msgprintnotime("   EqpID:%d, State:%d(0:idle;1:start;2:run)\n", m_cSpeaker.m_atXmpuBas[byIndx].m_dwEqpID, 
			m_cSpeaker.m_atXmpuBas[byIndx].m_emStat);

		if (m_cSpeaker.m_atXmpuBas[byIndx].m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_cSpeaker.m_atXmpuBas[byIndx].m_tDecMiddleRtpAddr.GetIP()), m_cSpeaker.m_atXmpuBas[byIndx].m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_cSpeaker.m_atXmpuBas[byIndx].m_tDecRtcpAddr.GetIP()), m_cSpeaker.m_atXmpuBas[byIndx].m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_cSpeaker.m_atXmpuBas[byIndx].m_tDecRtpAddr.GetIP()), m_cSpeaker.m_atXmpuBas[byIndx].m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; byInnerIndex++)
			{
				msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(m_cSpeaker.m_atXmpuBas[byIndx].m_atEncRtpAddr[byInnerIndex].GetIP()), m_cSpeaker.m_atXmpuBas[byIndx].m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_cSpeaker.m_atXmpuBas[byIndx].m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), m_cSpeaker.m_atXmpuBas[byIndx].m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_cSpeaker.m_atXmpuBas[byIndx].m_atEncRtcpAddr[byInnerIndex].GetIP()), m_cSpeaker.m_atXmpuBas[byIndx].m_atEncRtcpAddr[byInnerIndex].GetPort());
			}
		}
	
#else
		msgprintnotime("   EqpID:%d, EqpIP:"TPIPFORMAT", ChanIndx:%d, EqpStartPort:%d, UmsStartPort:%d, DsIP:"TPIPFORMAT"\n", 
			m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_byEqpID, 
			Tpu32ToIP(m_cSpeaker.m_atBas[byIndx].m_dwEqpIp),
			m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_wChnIndx, 
			m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_wEqpStartPort,
			m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_wUmsStartPort,
			Tpu32ToIP(m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_dwMediaIP) );
#endif
	}

	TTPMediaTransAddr tAddr;
	for ( byFormatIndx = 0; byFormatIndx < m_cSpeaker.m_tVidPara.m_byParamNum; byFormatIndx ++ )
	{
		ptVidFormate = &m_cSpeaker.m_tVidPara.m_atVidParam[byFormatIndx];
		msgprintnotime("   Indx:%d, %s, %s, %s, FrameRate:%d, BitRate:%d, Port:[",
			byFormatIndx,
			UmsVidFormatPrint(ptVidFormate->m_emFormat),
			UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
			UmsVidResPrint( ptVidFormate->m_emRes),
			ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate);
		for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
		{
			if ( !IsSpeakerNeedBas(*ptVidFormate) )
			{
				continue;
			}
			GetOutChnSpeakerVidAddr(tAddr, byIndx, *ptVidFormate);
			msgprintnotime("(%d,%d)", tAddr.m_tRtpAddr.GetPort(), tAddr.m_tBackRtcpAddr.GetPort());
		}
		msgprintnotime("]\n");
		
		ptVidFormate = &m_cSpeaker.m_tRealVidPara.m_atVidParam[byFormatIndx];
		msgprintnotime("      -> %s, %s, %s, FrameRate:%d, BitRate:%d\n",
			UmsVidFormatPrint(ptVidFormate->m_emFormat),
			UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
			UmsVidResPrint( ptVidFormate->m_emRes),
			ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate);
	}

	msgprintnotime("\n");

	//////////////////////////////////////////////////////////////////////////
	//chair
	msgprintnotime("  ChairVidBasInfo-> ChairEpID:%d, bChair:%d\n", pInst->chairID(), m_tConfBasMgr.m_bChair );
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		GetOutChnChairVidAddr(tAddr, byIndx);
		if ( !m_cChair.IsBasValid(byIndx) )
		{
			continue;
		}
#ifdef _USE_XMPUEQP_
		msgprintnotime("   EqpID:%d, State:%d(0:idle;1:start;2:run)\n", m_cChair.m_atXmpuBas[byIndx].m_dwEqpID, 
			m_cChair.m_atXmpuBas[byIndx].m_emStat);

		if (m_cChair.m_atXmpuBas[byIndx].m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_cChair.m_atXmpuBas[byIndx].m_tDecMiddleRtpAddr.GetIP()), m_cChair.m_atXmpuBas[byIndx].m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_cChair.m_atXmpuBas[byIndx].m_tDecRtcpAddr.GetIP()), m_cChair.m_atXmpuBas[byIndx].m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_cChair.m_atXmpuBas[byIndx].m_tDecRtpAddr.GetIP()), m_cChair.m_atXmpuBas[byIndx].m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < 1; byInnerIndex++)
			{
				msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(m_cChair.m_atXmpuBas[byIndx].m_atEncRtpAddr[byInnerIndex].GetIP()), 
					m_cChair.m_atXmpuBas[byIndx].m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_cChair.m_atXmpuBas[byIndx].m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), 
					m_cChair.m_atXmpuBas[byIndx].m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_cChair.m_atXmpuBas[byIndx].m_atEncRtcpAddr[byInnerIndex].GetIP()), 
					m_cChair.m_atXmpuBas[byIndx].m_atEncRtcpAddr[byInnerIndex].GetPort());
			}
		}
		
#else		
		msgprintnotime("   EqpID:%d, EqpIP:"TPIPFORMAT", ChanIndx:%d, EqpStartPort:%d, UmsStartPort:%d, DsIP:"TPIPFORMAT", Port(%d,%d)\n", 
			m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_byEqpID, 
			Tpu32ToIP(m_cChair.m_atBas[byIndx].m_dwEqpIp),
			m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_wChnIndx, 
			m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_wEqpStartPort,
			m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_wUmsStartPort,
			Tpu32ToIP(m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_dwMediaIP),
			tAddr.m_tRtpAddr.GetPort(), tAddr.m_tBackRtcpAddr.GetPort());
#endif
	}
	msgprintnotime("\n");

	//////////////////////////////////////////////////////////////////////////
	//dual
	msgprintnotime("  DualVidBasInfo-> DualEpID:%d, bDual:%d, chnltype:%d(0:brd,1:sel)\n", 
			pInst->m_pcDual->GetDualID(), m_tConfBasMgr.m_bDual, m_cDual.m_emAsgType);
	
	ptVidFormate = &m_cDual.m_tEpFormat;
	msgprintnotime("	DualForamt:%s, %s, %s, FrameRate:%d, BitRate:%d\n", 
				UmsVidFormatPrint(ptVidFormate->m_emFormat),
				UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
				UmsVidResPrint( ptVidFormate->m_emRes),
				ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate);

	if( m_tConfBasMgr.m_bDual )
	{

#ifdef _USE_XMPUEQP_
		msgprintnotime("   EqpID:%d, State:%d(0:idle;1:start;2:run)\n", m_cDual.m_tXmpuBas.m_dwEqpID, 
			m_cDual.m_tXmpuBas.m_emStat);

		if (m_cDual.m_tXmpuBas.m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_cDual.m_tXmpuBas.m_tDecMiddleRtpAddr.GetIP()), m_cDual.m_tXmpuBas.m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_cDual.m_tXmpuBas.m_tDecRtcpAddr.GetIP()), m_cDual.m_tXmpuBas.m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_cDual.m_tXmpuBas.m_tDecRtpAddr.GetIP()), m_cDual.m_tXmpuBas.m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; byInnerIndex++)
			{
				msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(m_cDual.m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetIP()),
					m_cDual.m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_cDual.m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()),
					m_cDual.m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_cDual.m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetIP()),
					m_cDual.m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
			}
		}
#else
		msgprintnotime("   EqpID:%d, EqpIP:"TPIPFORMAT", ChanIndx:%d, EqpStartPort:%d, UmsStartPort:%d, DsIP:"TPIPFORMAT"\n",
									m_cDual.m_tBas.m_tBasChnInfo.m_byEqpID, 
									Tpu32ToIP(m_cDual.m_tBas.m_dwEqpIp),
									m_cDual.m_tBas.m_tBasChnInfo.m_wChnIndx, 
									m_cDual.m_tBas.m_tBasChnInfo.m_wEqpStartPort,
									m_cDual.m_tBas.m_tBasChnInfo.m_wUmsStartPort,
									Tpu32ToIP(m_cDual.m_tBas.m_tBasChnInfo.m_dwMediaIP) );
#endif
		for ( byFormatIndx = 0; byFormatIndx < m_cDual.m_tVidPara.m_byParamNum; byFormatIndx ++ )
		{
			ptVidFormate = &m_cDual.m_tVidPara.m_atVidParam[byFormatIndx];

			if ( IsDualNeedBas(*ptVidFormate) )
			{
				GetOutDualVidAddr(tAddr, *ptVidFormate);
			}
			else
			{
				tAddr.Clear();
			}
			
			msgprintnotime("   Indx:%d, %s, %s, %s, FrameRate:%d, BitRate:%d, Port(%d,%d)\n",
				byFormatIndx,
				UmsVidFormatPrint(ptVidFormate->m_emFormat),
				UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
				UmsVidResPrint( ptVidFormate->m_emRes),
				ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate,
				tAddr.m_tRtpAddr.GetPort(), tAddr.m_tBackRtcpAddr.GetPort());
			ptVidFormate = &m_cDual.m_tRealVidPara.m_atVidParam[byFormatIndx];
			msgprintnotime("      -> %s, %s, %s, FrameRate:%d, BitRate:%d\n",
				UmsVidFormatPrint(ptVidFormate->m_emFormat),
				UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
				UmsVidResPrint( ptVidFormate->m_emRes),
				ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate);

		}
	}
	msgprintnotime("\n");


	//////////////////////////////////////////////////////////////////////////
	//view poll dis 等等
	msgprintnotime("  OtherVidBasInfo->\n");
	for ( byIndx = 0; byIndx < BAS_CHN_RES_MAX_NUM; byIndx ++ )
	{
		if ( !m_tConfBasMgr.m_atBasChsRes[byIndx].IsBasValid() )
		{
			continue;
		}
		msgprintnotime(" Index:%d ->\n", byIndx);

#ifdef _USE_XMPUEQP_
		msgprintnotime("   EpID:%d, ScreenIndx:%d, EqpID:%d, State:%d(0:idle;1:start;2:run), UsdNum:%d\n", 
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_wSrcEp,
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_wSrcScreenIndx,
			m_tConfBasMgr.m_atBasChsRes[byIndx].GetBasEqpId(), 
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_emStat,
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_wUsdNum);

		if (m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_tDecMiddleRtpAddr.GetIP()), 
				m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_tDecRtcpAddr.GetIP()), 
				m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_tDecRtpAddr.GetIP()),
				m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; byInnerIndex++)
			{
				msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetIP()), 
					m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), 
					m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetIP()), 
					m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
			}
		}
	
#else
		msgprintnotime("   EpID:%d, ScreenIndx:%d, EqpID:%d, EqpIP:"TPIPFORMAT", ChanIndx:%d, EqpStartPort:%d, UmsStartPort:%d, DsIP:"TPIPFORMAT", UsdNum:%d\n", 
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_wSrcEp,
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_wSrcScreenIndx,
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
			Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_dwEqpIp),
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, 
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_wEqpStartPort,
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_wUmsStartPort,
			Tpu32ToIP(m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_dwMediaIP),
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_wUsdNum);
#endif

		for ( byFormatIndx = 0; byFormatIndx < m_tConfBasMgr.m_atBasChsRes[byIndx].m_byFormatNum; byFormatIndx ++ )
		{
			ptVidFormate = &m_tConfBasMgr.m_atBasChsRes[byIndx].m_atVidFormat[byFormatIndx];

			if( IsSpeakerNeedBas(*ptVidFormate) )
			{
				GetOutChnVidAddr(tAddr, &m_tConfBasMgr.m_atBasChsRes[byIndx], *ptVidFormate);
			}
			else
			{
				tAddr.Clear();
			}
			
			msgprintnotime("    Indx:%d, %s, %s, %s, FrameRate:%d, BitRate:%d, Port(%d, %d)\n",
				byFormatIndx,
				UmsVidFormatPrint(ptVidFormate->m_emFormat),
				UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
				UmsVidResPrint( ptVidFormate->m_emRes),
				ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate,
				tAddr.m_tRtpAddr.GetPort(), tAddr.m_tBackRtcpAddr.GetPort());
		}

		if ( byIndx == TP_MAX_STREAMNUM - 1 )
		{
			msgprintnotime("\n");
		}
	}
	msgprintnotime("\n");


	//////////////////////////////////////////////////////////////////////////
	//音频适配信息
	msgprintnotime("AudBasInfo:\n");
	msgprintnotime(" SpeakerAudBas--> SndFmt:%s\n", UmsAudFormatPrint(m_tAudBasSpeakerMix.m_tSndAudFmt.m_emFormat));
	
	TTPDsFrom tAudBasAddr;
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		GetSpeakerAudBasInAddr( byIndx, tAudBasAddr);

#ifdef _USE_XMPUEQP_
		msgprintnotime("   index:%d EqpID:%d, State:%d(0:idle;1:start;2:run)\n", byIndx,	m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_dwEqpID, 
			m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_emStat);

	    if (m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetIP()), m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_tDecRtcpAddr.GetIP()), m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_tDecRtpAddr.GetIP()), m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < AUD_BAS_MAX_OUT_CHNL_NUM; byInnerIndex++)
			{
				msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_atEncRtpAddr[byInnerIndex].GetIP()),
					m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()),
					m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_atEncRtcpAddr[byInnerIndex].GetIP()),
					m_atAudBasSpeaker[byIndx].m_tXmpuAudBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
			}
		}
		
#else
		msgprintnotime(" index:%d, EqpID:%d, ChnlIndx:%d DsIP:"TPIPFORMAT", UmsStartPort:%d, EqpStartPort:%d, Rtp:%d, Rtcp:%d\n", 
			byIndx, m_atAudBasSpeaker[byIndx].m_tEqpRes.m_tBasChnInfo.m_byEqpID,
			m_atAudBasSpeaker[byIndx].m_tEqpRes.m_tBasChnInfo.m_wChnIndx,
			u32ToIP(m_atAudBasSpeaker[byIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaIP),
			m_atAudBasSpeaker[byIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort,
			m_atAudBasSpeaker[byIndx].m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort,
			tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());
#endif		
		for ( byFormatIndx = 0; byFormatIndx < UMS_AUDBAS_ENC_NUM; byFormatIndx ++ )
		{
			if ( m_tAudBasSpeakerMix.m_atAudFmt[byFormatIndx].m_emFormat == emTPAEnd )
			{
				continue;
			}
			GetSpeakerAudBasOutAddr( byIndx, m_tAudBasSpeakerMix.m_atAudFmt[byFormatIndx].m_emFormat, tAudBasAddr);
			msgprintnotime("	FmtIndx:%d  %-9s, Rtp:%d, Rtcp:%d\n", byFormatIndx, 
									UmsAudFormatPrint(m_tAudBasSpeakerMix.m_atAudFmt[byFormatIndx].m_emFormat),
									tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());
		}
	}
	msgprintnotime("\n");

	GetSpeakerMixAudBasInAddr(tAudBasAddr);

#ifdef _USE_XMPUEQP_
		msgprintnotime("   SingleAudBas(MixChnl)  EqpID:%d, State:%d(0:idle;1:start;2:run)\n", m_tAudBasSpeakerMix.m_tXmpuAudBas.m_dwEqpID, 
			m_tAudBasSpeakerMix.m_tXmpuAudBas.m_emStat);

		if (m_tAudBasSpeakerMix.m_tXmpuAudBas.m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetIP()), m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecRtcpAddr.GetIP()), m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecRtpAddr.GetIP()), m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecRtpAddr.GetPort());
			for ( byFormatIndx = 0; byFormatIndx < AUD_BAS_MAX_OUT_CHNL_NUM; byFormatIndx ++ )
			{
				msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byFormatIndx,
					Tpu32ToIP(m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncRtpAddr[byFormatIndx].GetIP()),
					m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncRtpAddr[byFormatIndx].GetPort(), 
					Tpu32ToIP(m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byFormatIndx].GetIP()), 
					m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byFormatIndx].GetPort(), 
					Tpu32ToIP(m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncRtcpAddr[byFormatIndx].GetIP()), 
					m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncRtcpAddr[byFormatIndx].GetPort());
			}
		}
#else
	msgprintnotime(" SingleAudBas(MixChnl) EqpID:%d, ChnlIndx:%d DsIP:"TPIPFORMAT", UmsStartPort:%d, EqpStartPort:%d, Rtp:%d, Rtcp:%d\n", 
		m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_byEqpID,
		m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wChnIndx,
		u32ToIP(m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_dwMediaIP),
		m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort,
		m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort,
		tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());
#endif
	for ( byFormatIndx = 0; byFormatIndx < UMS_AUDBAS_ENC_NUM; byFormatIndx ++ )
	{
		if ( m_tAudBasSpeakerMix.m_atAudFmt[byFormatIndx].m_emFormat == emTPAEnd )
		{
			continue;
		}
		GetSpeakerMixAudBasOutAddr( m_tAudBasSpeakerMix.m_atAudFmt[byFormatIndx].m_emFormat, tAudBasAddr);
		msgprintnotime("	FmtIndx:%d  %-9s, Rtp:%d, Rtcp:%d\n", byFormatIndx, 
								UmsAudFormatPrint(m_tAudBasSpeakerMix.m_atAudFmt[byFormatIndx].m_emFormat),
								tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());
	}

	msgprintnotime("\n");

	msgprintnotime(" ChairAudBas--> SndFmt:%s\n", UmsAudFormatPrint(m_atAudBasChair[MIDSCREENINDEX].m_tSndAudFmt.m_emFormat));
	
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		GetChairAudBasInAddr( byIndx, tAudBasAddr);

#ifdef _USE_XMPUEQP_
		msgprintnotime("   index:%d EqpID:%d, State:%d(0:idle;1:start;2:run)\n", byIndx,	m_atAudBasChair[byIndx].m_tXmpuAudBas.m_dwEqpID, 
			m_atAudBasChair[byIndx].m_tXmpuAudBas.m_emStat);

		if(m_atAudBasChair[byIndx].m_tXmpuAudBas.m_emStat != EmXmpuResStatInfo_Idle)
		{
			msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
				Tpu32ToIP(m_atAudBasChair[byIndx].m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetIP()), m_atAudBasChair[byIndx].m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetPort(), 
				Tpu32ToIP(m_atAudBasChair[byIndx].m_tXmpuAudBas.m_tDecRtcpAddr.GetIP()), m_atAudBasChair[byIndx].m_tXmpuAudBas.m_tDecRtcpAddr.GetPort(), 
				Tpu32ToIP(m_atAudBasChair[byIndx].m_tXmpuAudBas.m_tDecRtpAddr.GetIP()), m_atAudBasChair[byIndx].m_tXmpuAudBas.m_tDecRtpAddr.GetPort());
			
			for(byInnerIndex = 0; byInnerIndex < AUD_BAS_MAX_OUT_CHNL_NUM; byInnerIndex++)
			{
				msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
					byInnerIndex,
					Tpu32ToIP(m_atAudBasChair[byIndx].m_tXmpuAudBas.m_atEncRtpAddr[byInnerIndex].GetIP()), 
					m_atAudBasChair[byIndx].m_tXmpuAudBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_atAudBasChair[byIndx].m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()), 
					m_atAudBasChair[byIndx].m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
					Tpu32ToIP(m_atAudBasChair[byIndx].m_tXmpuAudBas.m_atEncRtcpAddr[byInnerIndex].GetIP()), 
					m_atAudBasChair[byIndx].m_tXmpuAudBas.m_atEncRtcpAddr[byInnerIndex].GetPort());		
			}
		}	
#else
		msgprintnotime(" index:%d, EqpID:%d, ChnlIndx:%d DsIP:"TPIPFORMAT", UmsStartPort:%d, EqpStartPort:%d, Rtp:%d, Rtcp:%d\n", 
			byIndx, m_atAudBasChair[byIndx].m_tEqpRes.m_tBasChnInfo.m_byEqpID,
			m_atAudBasChair[byIndx].m_tEqpRes.m_tBasChnInfo.m_wChnIndx,
			u32ToIP(m_atAudBasChair[byIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaIP),
			m_atAudBasChair[byIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort,
			m_atAudBasChair[byIndx].m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort,
			tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());
#endif		
		for ( byFormatIndx = 0; byFormatIndx < UMS_AUDBAS_ENC_NUM; byFormatIndx ++ )
		{
			if ( m_atAudBasChair[byIndx].m_atAudFmt[byFormatIndx].m_emFormat == emTPAEnd 
				|| !IsChairNeedAudBas(m_atAudBasChair[MIDSCREENINDEX].m_atAudFmt[byFormatIndx].m_emFormat) )
			{
				continue;
			}
			GetChairAudBasOutAddr( byIndx, m_atAudBasChair[MIDSCREENINDEX].m_atAudFmt[byFormatIndx].m_emFormat, tAudBasAddr);
			msgprintnotime("	FmtIndx:%d  %-9s, Rtp:%d, Rtcp:%d\n", byFormatIndx, 
								UmsAudFormatPrint(m_atAudBasChair[MIDSCREENINDEX].m_atAudFmt[byFormatIndx].m_emFormat),
								tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());		
		}
	}

	msgprintnotime("\n");

	msgprintnotime(" DualAudBas--> SndFmt:%s\n", UmsAudFormatPrint(m_tAudBasDual.m_tSndAudFmt.m_emFormat));

	GetDualAudBasInAddr(tAudBasAddr);

#ifdef _USE_XMPUEQP_
	msgprintnotime("   EqpID:%d, State:%d(0:idle;1:start;2:run)\n", m_tAudBasDual.m_tXmpuAudBas.m_dwEqpID, 
		m_tAudBasDual.m_tXmpuAudBas.m_emStat);
	if(m_tAudBasDual.m_tXmpuAudBas.m_emStat != EmXmpuResStatInfo_Idle)
	{
		msgprintnotime("     InChn DecMidRtp:("TPIPFORMAT":%d) DecRtcp:("TPIPFORMAT":%d) DecRtp:("TPIPFORMAT":%d)\n",
			Tpu32ToIP(m_tAudBasDual.m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetIP()), m_tAudBasDual.m_tXmpuAudBas.m_tDecMiddleRtpAddr.GetPort(), 
			Tpu32ToIP(m_tAudBasDual.m_tXmpuAudBas.m_tDecRtcpAddr.GetIP()), m_tAudBasDual.m_tXmpuAudBas.m_tDecRtcpAddr.GetPort(), 
			Tpu32ToIP(m_tAudBasDual.m_tXmpuAudBas.m_tDecRtpAddr.GetIP()), m_tAudBasDual.m_tXmpuAudBas.m_tDecRtpAddr.GetPort());
		for(byInnerIndex = 0; byInnerIndex < AUD_BAS_MAX_OUT_CHNL_NUM; byInnerIndex++)
		{
			msgprintnotime("     OutChn%d EncRtp:("TPIPFORMAT":%d) EncMidRtcp:("TPIPFORMAT":%d) EncRtcp:("TPIPFORMAT":%d)\n",
				byInnerIndex,
				Tpu32ToIP(m_tAudBasDual.m_tXmpuAudBas.m_atEncRtpAddr[byInnerIndex].GetIP()),
				m_tAudBasDual.m_tXmpuAudBas.m_atEncRtpAddr[byInnerIndex].GetPort(), 
				Tpu32ToIP(m_tAudBasDual.m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetIP()),
				m_tAudBasDual.m_tXmpuAudBas.m_atEncMiddleRtcpAddr[byInnerIndex].GetPort(), 
				Tpu32ToIP(m_tAudBasDual.m_tXmpuAudBas.m_atEncRtcpAddr[byInnerIndex].GetIP()),
				m_tAudBasDual.m_tXmpuAudBas.m_atEncRtcpAddr[byInnerIndex].GetPort());
		}
	}
	
#else
	msgprintnotime("  EqpID:%d, ChnlIndx:%d DsIP:"TPIPFORMAT", UmsStartPort:%d, EqpStartPort:%d, Rtp:%d, Rtcp:%d\n", 
		m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_byEqpID,
		m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wChnIndx,
		u32ToIP(m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_dwMediaIP),
		m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort,
		m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort,
		tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());
#endif
	
	for ( byFormatIndx = 0; byFormatIndx < UMS_AUDBAS_ENC_NUM; byFormatIndx ++ )
	{
		if ( m_tAudBasDual.m_atAudFmt[byFormatIndx].m_emFormat == emTPAEnd )
		{
			continue;
		}
		GetDualAudBasOutAddr(m_tAudBasDual.m_atAudFmt[byFormatIndx].m_emFormat, tAudBasAddr);
		msgprintnotime("	FmtIndx:%d  %-9s, Rtp:%d, Rtcp:%d\n", byFormatIndx, 
							UmsAudFormatPrint(m_tAudBasDual.m_atAudFmt[byFormatIndx].m_emFormat),
							tAudBasAddr.m_tRtpAddr.GetPort(), tAudBasAddr.m_tBackRtcpAddr.GetPort());	
	}

	msgprintnotime("\n");

	return ;
}

BOOL32 CUmsBas::Handler( CTpMsg *const ptMsg )
{
	switch(ptMsg->GetEvent())
	{
	case evtp_UmsBasStart_NAck:
		OnBasNAck(ptMsg);
		break;
	case evtp_UmsBasUnReg_Notify:
		OnBasDisConnect(ptMsg);
		break;
	case evtp_UmsBasAskFrame_Req:
		OnBasAskFrame(ptMsg);
		break;
	case evtp_UmsBasChangeDsIP_Req:
		OnChangeBasSndAddr(ptMsg);
		break;
	case evtp_BasTestAdjust_Cmd:
		OnBasTestShow(ptMsg);
		break;

#ifdef _USE_XMPUEQP_
    case evXmpu_UmsStartVidBas_Nty:
    case evXmpu_SetBasEncParam_Nty:
    case evXmpu_AskBasKey_Req:
	case evXmpu_BasDisConnect_Nty:
        OnXmpuVidBasStateNty(ptMsg);
		break;

	case evXmpu_UmsStartAudBas_Nty:
	case evXmpu_SetAudBasParam_Nty:
	case evXmpu_AudBasDisConnect_Nty:
        OnXmpuAudBasStateNty(ptMsg);
		break;
#endif

	default:
		return FALSE;
	}
	return TRUE;
}

BOOL32 CUmsBas::HandlerFromStack( CTpMsg *const ptMsg )
{
	return FALSE;
}


#ifdef _USE_XMPUEQP_
BOOL32 CUmsBas::AssignSpeakerBasFromXmpu(void)
{
	CUmsConfInst* pInst = Inst();
	
	if( !pInst->IsPriNeedBas())
	{
		MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignSpeakerBasFromXmpu. not need bas! ConfID:%d, ConfTempFormatNum:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wMainNum));
		return TRUE;
	}
	
	//初始后适配格式
	ParseConfTempFirstVidFormat();
	
	TTPBasVidParam *ptBasOutParam;    // 后适配通道参数
	TUmsVidFormat  *ptBasInParam;     // 前适配最大参数
    ptBasInParam  = &m_cSpeaker.m_tVidPara.m_atVidParam[0]; //格式是经过排序的，从大到小
    ptBasOutParam = &m_cSpeaker.m_tVidPara;
	BOOL32 bError = FALSE;
    u16 wIndex = 0;
	
	for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (!AssignXmpuBas(ptBasInParam, ptBasOutParam, &m_cSpeaker.m_atXmpuBas[wIndex]))
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::AssignSpeakerBasFromXmpu. Assign Xmpu Bas Fail! ConfID:%d, Srceen:%d\n", 
				pInst->GetInsID(),  wIndex));
            bError = TRUE;
			break;
		}
	}
	
    if (bError)
	{ 
		ReleaseXmpuBas(TP_MAX_STREAMNUM, m_cSpeaker.m_atXmpuBas);
		return FALSE;
	}

	m_tConfBasMgr.m_bSpeaker = TRUE;
	
	return TRUE;
}

#else 
//开会时立即为发言人按最大能力申请适配资源
BOOL32 CUmsBas::AssignSpeakerBas()
{
	CUmsConfInst* pInst = Inst();

	if( !pInst->IsPriNeedBas())
	{
		MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignSpeakerBas. not need bas! ConfID:%d, ConfTempFormatNum:%d\n", 
															pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wMainNum));
		return TRUE;
	}

	//初始后适配格式
	ParseConfTempFirstVidFormat();

	if ( !AssignBas(m_cSpeaker.m_emAsgType, TP_MAX_STREAMNUM, m_cSpeaker.m_atBas, (u8)m_wPriNum) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignSpeakerBas. Assign Fail! ConfID:%d, FormatNum:%d\n", 
																pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wMainNum));
		return FALSE;
	}

	m_tConfBasMgr.m_bSpeaker = TRUE;
	
	return TRUE;
}

#endif

BOOL32 CUmsBas::IsDualNeedBas( TUmsVidFormat& tRcv )
{
	if (!Inst()->IsDualNeedBas())
	{
		return FALSE;
	}

	if ( CTpTypeAdpt::IsVidTransNeedBas(m_cDual.m_tEpFormat, tRcv) )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL32 CUmsBas::IsSpeakerNeedBas(TUmsVidFormat& tRcv , u16 wScreenIndex /* = TP_INVALID_INDEX */)
{
	if (!Inst()->IsPriNeedBas())
	{
		return FALSE;
	}

	TUmsVidFormat tFormat;

	if (TP_INVALID_INDEX != wScreenIndex && m_cSpeaker.IsExInfo(wScreenIndex))
	{
		tFormat = m_cSpeaker.m_tSndVidFormatEx;
	}
	else
	{
		tFormat = m_cSpeaker.m_tSndVidFormat;
	}

	if ( !CTpTypeAdpt::IsVidTransNeedBas(tFormat, tRcv) )
	{
		return FALSE;
	}
	
	return TRUE;
}

#ifdef _USE_XMPUEQP_
BOOL32 CUmsBas::AssignDualBasFromXmpuEqp(void)
{
	CUmsConfInst* pInst = Inst();
	
	if( pInst->IsDualNeedBas() && !m_tConfBasMgr.m_bDual)
	{
		ParseConfTempSecondVidFormat();
		
		TUmsVidFormat *pBasInParam;
		TTPBasVidParam *pBasOutParam;
        pBasInParam  = &m_cDual.m_tVidPara.m_atVidParam[0];
        pBasOutParam = &m_cDual.m_tVidPara;
		//	void GetDefaultMaxFormat(TUmsVidFormat& tVidFormat)
		if (!AssignXmpuBas(pBasInParam, pBasOutParam, &m_cDual.m_tXmpuBas))
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::AssignDualBasFromXmpu. Assign Xmpu Bas Fail! ConfID:%d.\n", 
				pInst->GetInsID()));
			return FALSE;
		}
		
		m_tConfBasMgr.m_bDual = TRUE;
	}
	
	if (!AssignDualAudBasFromXmpu())
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignDualBasFromXmpu. AssignDualAudBas Fail! ConfID:%d, FormatNum:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wAudFmtNum));
		ReleaseDualBas();
		return FALSE;
	}
	
	return TRUE;
}

#else

BOOL32 CUmsBas::AssignDualBasFromOldEqp(void)
{
	CUmsConfInst* pInst = Inst();
	
	if( pInst->IsDualNeedBas() && !m_tConfBasMgr.m_bDual)
	{
		ParseConfTempSecondVidFormat();
		
		if ( !AssignBas( m_cDual.m_emAsgType, 1, &m_cDual.m_tBas, (u8)m_wDualNum) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::AssignDualBasFromOldEqp. AssignDualVidBas Fail! ConfID:%d, FormatNum:%d\n", 
				pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wMinorNum));
			ReleaseDualBas();
			return FALSE;
		}
		m_tConfBasMgr.m_bDual = TRUE;
	}

	if (!AssignDualAudBas())
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignDualBasFromOldEqp. AssignDualAudBas Fail! ConfID:%d, FormatNum:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wAudFmtNum));
		ReleaseDualBas();
		return FALSE;
	}
	
	return TRUE;
}

#endif

BOOL32 CUmsBas::AssignDualBas()
{
#ifdef _USE_XMPUEQP_
    return AssignDualBasFromXmpuEqp();
#else
	return AssignDualBasFromOldEqp();
#endif
}


#ifdef _USE_XMPUEQP_
BOOL32 CUmsBas::AssignScreenBasFromXmpuEqp( CScreenBasRes*& pcBasRes, BOOL32 bSingleOut )
{
	CUmsConfInst* pInst = Inst();
	
	if( NULL != pcBasRes && pcBasRes->IsBasValid() )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromXmpuEqp. ChanRes is Valid ++! ConfID:%d, UsdNum:%d\n", pInst->GetInsID(), pcBasRes->m_wUsdNum++));
		return TRUE;
	}
	
	u16 wIndx = m_tConfBasMgr.FindIdleBasChnRes();
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromXmpuEqp. no Idle ChanRes! ConfID:%d\n", pInst->GetInsID()));
		return FALSE;
	}
	
	CScreenBasRes* ptScreenBasRes = &m_tConfBasMgr.m_atBasChsRes[wIndx];
	
	TBasParam::EmAssignType emType;
	if( !bSingleOut )
	{//按照发言人分配
		emType = m_cSpeaker.m_emAsgType;
		
		ptScreenBasRes->m_byFormatNum = m_cSpeaker.m_tVidPara.m_byParamNum;
		memcpy(&ptScreenBasRes->m_atVidFormat[0], &m_cSpeaker.m_tVidPara.m_atVidParam[0], 
			sizeof(TUmsVidFormat)*ptScreenBasRes->m_byFormatNum);
		ptScreenBasRes->m_wNeedAdjustLvl = m_cSpeaker.m_wNeedAdjustLvl;
		ptScreenBasRes->m_tNeedAdjustFmt = m_cSpeaker.m_tNeedAdjustFmt;
		
		ptScreenBasRes->m_bIsMultOut = TRUE;
	}
	else
	{
		emType = TBasParam::em_AssignType_Sel;
		
		TUmsVidFormat tVidFormat;
		GetDefaultMaxFormat(tVidFormat);
		
		ptScreenBasRes->m_byFormatNum = 1;
		memcpy(&ptScreenBasRes->m_atVidFormat[0], &tVidFormat, sizeof(TUmsVidFormat)*ptScreenBasRes->m_byFormatNum);
	}
	
    TTPBasVidParam tBasOutParam;
    TUmsVidFormat  tBasInParam;
	
    GetDefaultMaxFormat(tBasInParam);
    tBasOutParam.m_byParamNum = ptScreenBasRes->m_byFormatNum;
    memcpy(tBasOutParam.m_atVidParam, ptScreenBasRes->m_atVidFormat, sizeof(TUmsVidFormat) * ptScreenBasRes->m_byFormatNum);
	
	if (!AssignXmpuBas(&tBasInParam, &tBasOutParam, &ptScreenBasRes->m_tXmpuBas))
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromXmpuEqp. Assign Xmpu bas Fail! ConfID:%d, wIndx:%d\n", pInst->GetInsID(), wIndx));
        return FALSE;
	}
	
	
	ptScreenBasRes->m_wUsdNum ++;
	

	//设置量子码流秘钥
// 	for ( u16 wIndex = 0; wIndex < TP_MAX_OLD_KEY_NUM; wIndex ++ )
// 	{
// 		if (0 == pInst->MediaKey(wIndex).m_dwQtFlag)
// 		{
// 			continue;
// 		}
// 		
// 		SetQtMediaKeyByBasEqp(&ptScreenBasRes->m_tBasEqpRes, pInst->MediaKey(wIndex));
// 	}

	
	MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromXmpuEqp. ConfID:%d, AsgType:%d\n", pInst->GetInsID(), emType));
	
// CNetPortMgr::AdjustBasDsEqpToConfDsEqp(pInst);
	
	pcBasRes = ptScreenBasRes;
	
	return TRUE;	
}
#else

BOOL32 CUmsBas::AssignScreenBasFromOldEqp( CScreenBasRes*& pcBasRes, BOOL32 bSingleOut )
{
	CUmsConfInst* pInst = Inst();
	
	if( NULL != pcBasRes && pcBasRes->IsBasValid() )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromOldEqp. ChanRes is Valid ++! ConfID:%d, UsdNum:%d\n", pInst->GetInsID(), pcBasRes->m_wUsdNum++));
		return TRUE;
	}
	
	u16 wIndx = m_tConfBasMgr.FindIdleBasChnRes();
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromOldEqp. no Idle ChanRes! ConfID:%d\n", pInst->GetInsID()));
		return FALSE;
	}
	
	CScreenBasRes* ptScreenBasRes = &m_tConfBasMgr.m_atBasChsRes[wIndx];
	
	TBasParam::EmAssignType emType;
	if( !bSingleOut )
	{//按照发言人分配
		emType = m_cSpeaker.m_emAsgType;
		
		ptScreenBasRes->m_byFormatNum = m_cSpeaker.m_tVidPara.m_byParamNum;
		memcpy(&ptScreenBasRes->m_atVidFormat[0], &m_cSpeaker.m_tVidPara.m_atVidParam[0], 
			sizeof(TUmsVidFormat)*ptScreenBasRes->m_byFormatNum);
		ptScreenBasRes->m_wNeedAdjustLvl = m_cSpeaker.m_wNeedAdjustLvl;
		ptScreenBasRes->m_tNeedAdjustFmt = m_cSpeaker.m_tNeedAdjustFmt;
		
		ptScreenBasRes->m_bIsMultOut = TRUE;
	}
	else
	{
		emType = TBasParam::em_AssignType_Sel;
		
		TUmsVidFormat tVidFormat;
		GetDefaultMaxFormat(tVidFormat);
		
		ptScreenBasRes->m_byFormatNum = 1;
		memcpy(&ptScreenBasRes->m_atVidFormat[0], &tVidFormat, sizeof(TUmsVidFormat)*ptScreenBasRes->m_byFormatNum);
	}
	
	if ( !AssignBas(emType, 1, &ptScreenBasRes->m_tBasEqpRes, ptScreenBasRes->m_byFormatNum) )
	{
		ptScreenBasRes->Clear();
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromOldEqp. Assign Fail! ConfID:%d, wIndx:%d\n", pInst->GetInsID(), wIndx));
		return FALSE;
	}
	
	ptScreenBasRes->m_wUsdNum ++;
	
	//设置量子码流秘钥
	for ( u16 wIndex = 0; wIndex < TP_MAX_OLD_KEY_NUM; wIndex ++ )
	{
		if (0 == pInst->MediaKey(wIndex).m_dwQtFlag)
		{
			continue;
		}
		
		SetQtMediaKeyByBasEqp(&ptScreenBasRes->m_tBasEqpRes, pInst->MediaKey(wIndex));
	}
	
	
	MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignScreenBasFromOldEqp. ConfID:%d, AsgType:%d\n", pInst->GetInsID(), emType));
	
	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(pInst);
	
	pcBasRes = ptScreenBasRes;
	
	return TRUE;	
}

#endif

BOOL32 CUmsBas::AssignScreenBas( CScreenBasRes*& pcBasRes, BOOL32 bSingleOut )
{
#ifdef _USE_XMPUEQP_
    return AssignScreenBasFromXmpuEqp(pcBasRes, bSingleOut);
#else
    return AssignScreenBasFromOldEqp(pcBasRes, bSingleOut);
#endif
}


#ifdef _USE_XMPUEQP_
BOOL32 CUmsBas::AssignChairBasFromXmpu(void)
{
	CUmsConfInst* pInst = Inst();
	
	if( !pInst->IsPriNeedBas() )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignChairBasFromXmpu. not need bas! ConfID:%d, ConfTempFormatNum:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wMainNum));
		return TRUE;
	}
	
	if(TRUE == m_tConfBasMgr.m_bChair)
	{//已分配发言人看主席
        return TRUE;
	}
	
	TUmsVidFormat  tBasInParam;
	TTPBasVidParam tBasOutParam;
	BOOL32 bError = FALSE;
	u16 wIndex;
	
	//void GetDefaultMaxFormat(TUmsVidFormat& tVidFormat)
    tBasInParam = pInst->m_tConfBaseInfo.m_atTpMainVideoRes[0]; //bas 输入
	tBasOutParam.m_byParamNum = 1; //出一路
    tBasOutParam.m_atVidParam[0] = pInst->m_tConfBaseInfo.m_atTpMainVideoRes[0]; //取模板中最大格式
	
    for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
	{
		if (!AssignXmpuBas(&tBasInParam, &tBasOutParam, &m_cChair.m_atXmpuBas[wIndex]))
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::AssignChairBasFromXmpu. Assign Xmpu Bas Fail! ConfID:%d, Srceen:%d\n", pInst->GetInsID(), wIndex));
            bError = TRUE;
			break;
		}
	}
	
    if (bError)
	{
		ReleaseXmpuBas(TP_MAX_STREAMNUM, m_cChair.m_atXmpuBas);
		return FALSE;
	}

	m_tConfBasMgr.m_bChair = TRUE;
	
	return TRUE;
}

#else

BOOL32 CUmsBas::AssignChairBas()
{
	CUmsConfInst* pInst = Inst();
	
	if( !pInst->IsPriNeedBas() )
	{
		MdlHint(Ums_Mdl_Call, ("CUmsBas::AssignChairBas. not need bas! ConfID:%d, ConfTempFormatNum:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wMainNum));
		return TRUE;
	}


	if(TRUE == m_tConfBasMgr.m_bChair)
	{//已分配发言人看主席
        return TRUE;
	}


	//分配发言人看主席 适配资源
	u8 byOutNum = 1;//发言人看主席 出一路
	if ( !AssignBas(TBasParam::em_AssignType_Sel, TP_MAX_STREAMNUM, m_cChair.m_atBas, byOutNum) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignChairBas. Assign Fail! ConfID:%d, FormatNum:%d\n", 
																				pInst->GetInsID(), byOutNum));
		return FALSE;
	}
	
	m_tConfBasMgr.m_bChair = TRUE;

	return TRUE;
}

#endif

void CUmsBas::ReleaseScreenBas(CScreenBasRes*& ptScreenBasRes)
{
	CUmsConfInst* pInst = Inst();

	if ( NULL == ptScreenBasRes )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::ReleaseScreenBas. ptScreenBasRes is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	if ( !ptScreenBasRes->IsBasValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::ReleaseScreenBas. ScreenBasRes Invalid! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}

	//查找该适配资源是否存在
	u16 wIndx = m_tConfBasMgr.FindBasChnResByIndx(ptScreenBasRes);
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::ReleaseScreenBas. BasEqpRes no Exist! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
						pInst->GetInsID(), (ptScreenBasRes)->GetBasEqpId(), 
						(ptScreenBasRes)->GetBasChnIndex(), (ptScreenBasRes)->m_wSrcEp, (ptScreenBasRes)->m_wSrcScreenIndx));
		
		return ;
	}

	if ( --ptScreenBasRes->m_wUsdNum > 0  )
	{
		return ;
	}

	//调用统一释放接口 释放资源
#ifdef _USE_XMPUEQP_
	ReleaseXmpuBas(1, &m_tConfBasMgr.m_atBasChsRes[wIndx].m_tXmpuBas);
#else
	ReleaseBas(1, &m_tConfBasMgr.m_atBasChsRes[wIndx].m_tBasEqpRes);
#endif

	m_tConfBasMgr.m_atBasChsRes[wIndx].Clear();

	ptScreenBasRes = NULL;
	
	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(pInst);

	return ;
}

//双流资源释放
void CUmsBas::ReleaseDualBas()
{
	CUmsConfInst* pInst = Inst();

	if( m_tConfBasMgr.m_bDual )
	{

#ifdef _USE_XMPUEQP_
	    ReleaseXmpuBas(1, &m_cDual.m_tXmpuBas);
#else
		ReleaseBas(1, &m_cDual.m_tBas);
#endif
		m_tConfBasMgr.m_bDual = FALSE;
	}

	ReleaseDualAudBas();

	return ;
}

//分配bas统一接口
BOOL32 CUmsBas::AssignBas(TBasParam::EmAssignType emType, u8 byCapCount, TBasEqpRes atBasRes[], u8 byOutNum, u16 wAsignIndx )
{
	CUmsConfInst* pInst = Inst();
	
	BOOL32 bError = FALSE;
	TBasParam tBasParam;
	TBasEqpRes* ptEqpRes = NULL;

	u8 byIndx = 0;
	for ( byIndx = 0; byIndx < byCapCount; byIndx ++ )
	{
		memset(&tBasParam, 0, sizeof(tBasParam));
	
		if ( TP_VALID_HANDLE(wAsignIndx) && wAsignIndx != byIndx )
		{//只申请byRelIndx
			continue;
		}
		
		ptEqpRes = &atBasRes[byIndx];
		ptEqpRes->Clear();
		tBasParam.SetParam(pInst->GetInsID(), emType, byOutNum, ptEqpRes);
		
		if ( !AssignEqpEx(&tBasParam) )
		{
			bError = TRUE;
// 			MdlError(Ums_Mdl_Call, ("CUmsBas::AssignBas. ConfID:%d, FormatNum:%d, Indx:%d, AssignIndx:%d\n", 
// 															pInst->GetInsID(), byOutNum, byIndx, wAsignIndx));
			break;
		}
	}
	
	if ( bError )
	{//失败 释放以前分配的
		for ( byIndx = 0; byIndx < byCapCount; byIndx ++ )
		{
			if ( !atBasRes[byIndx].IsValid() )
			{
				continue;
			}
			
			if ( TP_VALID_HANDLE(wAsignIndx) && wAsignIndx != byIndx )
			{//只释放byRelIndx
				continue;
			}

			memset(&tBasParam, 0, sizeof(tBasParam));
			tBasParam.SetParam(pInst->GetInsID(), emType, byOutNum, &atBasRes[byIndx]);
			
			if(!ReleaseEqpEx(&tBasParam))
			{
// 				MdlError(Ums_Mdl_Call, ("CUmsBas::AssignBas. Release Fail! ConfID:%d, EqpID:%d, ChnIndx:%d\n", 
// 							pInst->GetInsID(), atBasRes[byIndx].m_tBasChnInfo.m_byEqpID, 
// 							atBasRes[byIndx].m_tBasChnInfo.m_wChnIndx));
			}

			atBasRes[byIndx].Clear();
		}	
	}
	else
	{
		for ( byIndx = 0; byIndx < byCapCount; byIndx ++ )
		{	
			if ( TP_VALID_HANDLE(wAsignIndx) && wAsignIndx != byIndx )
			{// 非本次申请
				continue;
			}

			if ( !atBasRes[byIndx].IsValid() )
			{// 资源无效
				continue;
			}
			
			ptEqpRes = &atBasRes[byIndx];
			ptEqpRes->m_tBasChnInfo.m_dwMediaNode = Inst()->GetConfEqpDs().m_dwEqpNode;
			ptEqpRes->m_tBasChnInfo.m_dwMediaIP = Inst()->GetConfEqpDs().m_dwEqpIp;
			
			//适配板 挂载到 会议转发板
			TBasSndAddr tSndAddr;
			tSndAddr.m_byEqpID =	ptEqpRes->m_tBasChnInfo.m_byEqpID;
			tSndAddr.m_dwNewDsIP = Inst()->m_tEqpConfDs.m_dwEqpIp;
			//开启适配
			CTpMsg cMsg;
			cMsg.SetEvent(ev_TPEqp_ChangeSndAddr_Req);
			cMsg.SetBody(&tSndAddr, sizeof(tSndAddr));
			cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		}
	}
	
	return !bError;	
}

void CUmsBas::ReleaseBas(u8 byCapCount, TBasEqpRes atEqpRes[], u16 wRelIndx)
{
	CUmsConfInst* pInst = Inst();
	TBasParam tBasParam;
	for (u8 byIndx = 0; byIndx < byCapCount; byIndx ++ )
	{
		if ( TP_VALID_HANDLE(wRelIndx) && wRelIndx != byIndx )
		{//只释放byRelIndx
			continue;
		}

		if ( !atEqpRes[byIndx].IsValid() )
		{
			continue;
		}

		tBasParam.m_ptEqpRes = &atEqpRes[byIndx];
		
		if(!ReleaseEqpEx(&tBasParam))
		{
// 			MdlError(Ums_Mdl_Call, ("CUmsBas::ReleaseBas. Release Fail! ConfID:%d, EqpID:%d, ChnIndx:%d\n", 
// 				pInst->GetInsID(), atEqpRes[byIndx].m_tBasChnInfo.m_byEqpID, 
// 				atEqpRes[byIndx].m_tBasChnInfo.m_wChnIndx));
		}
		
		atEqpRes[byIndx].Clear();
	}
}

//开启会议调用 ：分配主席和发言人所需的适配资源
BOOL32 CUmsBas::StartBas()
{
	//解析模板格式
	m_wPriNum = Inst()->m_tConfBaseInfo.m_wMainNum;
	memcpy(&m_atPriFmt[0], &Inst()->m_tConfBaseInfo.m_atTpMainVideoRes[0], sizeof(TUmsVidFormat)*m_wPriNum);
	m_wDualNum = Inst()->m_tConfBaseInfo.m_wMinorNum;
	memcpy(&m_atDualFmt[0], &Inst()->m_tConfBaseInfo.m_atTpMinorVideoRes[0], sizeof(TUmsVidFormat)*m_wDualNum);
	
	m_wPriNum = CheckAndProcConfTempFormat(m_atPriFmt, m_wPriNum);
	m_wDualNum = CheckAndProcConfTempFormat(m_atDualFmt, m_wDualNum);

#ifdef 	_USE_XMPUEQP_
	if ( Inst()->IsPriNeedBas() )
	{
		//7个适配通道最少需要2个合成器
		if (!CheckIdleMediaSource(ASSGIN_VID_BAS_NUM, 0, 0))
		{
			return FALSE;
		}
		//看发言人
		if(!AssignSpeakerBasFromXmpu())
		{
			return FALSE;
		}
		//发言合成
		if (CUmsConfigEx::GetInstance()->GetVmpUsed())
		{
			Inst()->TryAssignVirSingleBas();
		}
		
		//看主席
		if (!AssignChairBasFromXmpu())
		{
			return FALSE;
		}
	}
	
	if(!AssignAudBasFromXmpu())
	{
		return FALSE;
	}
#else
	if ( Inst()->IsPriNeedBas() )
	{
		//看发言人
		if(!AssignSpeakerBas())
		{
			return FALSE;
		}
		
		//看主席
		if (!AssignChairBas())
		{
			return FALSE;
		}
	}

	if(!AssignAudBas())
	{
		return FALSE;
	}

#endif
	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(Inst());
	
	return TRUE;
}


//退出会议调用 ：释放主席和发言人所占用的资源
void CUmsBas::StopBas()
{
	if ( Inst()->IsPriNeedBas() )
	{
		ReleaseSpeakerBas();
		ReleaseChairBas();

		for (u8 byIndx = 0; byIndx < BAS_CHN_RES_MAX_NUM; byIndx ++ )
		{
			if ( !m_tConfBasMgr.m_atBasChsRes[byIndx].IsBasValid() )
			{
				continue;
			}
			
			//调用统一释放接口 释放资源
#ifdef _USE_XMPUEQP_
	        ReleaseXmpuBas(1, &m_tConfBasMgr.m_atBasChsRes[byIndx].m_tXmpuBas);
#else
			ReleaseBas(1, &m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes);
#endif
			m_tConfBasMgr.m_atBasChsRes[byIndx].Clear();
		}
	}

	if( Inst()->IsDualNeedBas() )
	{
		ReleaseDualBas();
	}

	ReleaseAudBas();
	
	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(Inst());

	InstClear();

	return ;
}

#ifdef _USE_XMPUEQP_
void CUmsBas::SetXmpuSpeakerBasEncCmd(u16 wIndex /*TP_INVALID_INDEX*/, BOOL32 bAdjustAud  /*TRUE*/)
{
	CUmsConfInst* pInst = Inst();
	
	if (bAdjustAud && Inst()->IsAudNeedBas() )
	{
		AdjustSpeakerAudBas();
	}
	
	if ( !m_tConfBasMgr.m_bSpeaker )
	{
		return ;
	}
	
	u16 wEpId = pInst->curSpeakerID();
	if (pInst->GetUmsDiscuss()->IsDiscussModle() && !pInst->IsChairConf())
	{
		wEpId = pInst->chairID();
	}
	
	TCapNode* ptCapNode = pInst->m_pcNodeMgr->GetForeFatherNode(wEpId);
	if ( NULL == ptCapNode /*|| !ptCapNode->IsChanOn()*/ )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuSpeakerBasEncCmd. ptCapNode is NULL! ConfID:%d, ep:%d\n", 
			pInst->GetInsID(), wEpId));
		return ;
	}
	
	//计算当前发言人的后适配的最佳格式
	CalcBasSpeakerOutVidParam(ptCapNode->m_tVidSndFormat.m_tFormat);
	
	TXmpuChgBasInfo  tChgBasInfo;
	tChgBasInfo.m_wDynamicPayload = ptCapNode->m_tVidSndFormat.m_wDynamicPayload;
    tChgBasInfo.m_wStaticPayload  = ptCapNode->m_tVidSndFormat.m_wStaticPayload;
    tChgBasInfo.m_tEncrypt        = pInst->GetConfEncryptInfo();
    tChgBasInfo.m_tBasParam  =   m_cSpeaker.m_tRealVidPara;
    tChgBasInfo.m_wConfID  =   pInst->GetInsID();
	
	
	if( CUmsConfigEx::GetInstance()->GetEnc3060Bas() )
	{
		//发言人适配，不再出25 或 50的 防止：T300接收制式为60，导致画面卡顿
		for ( u16 wIndexFmt = 0; wIndexFmt < tChgBasInfo.m_tBasParam.m_byParamNum; wIndexFmt ++ )
		{
			if ( tChgBasInfo.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate == VID_FRAME_RATE_25 )
			{
				tChgBasInfo.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate = VID_FRAME_RATE_30;
			}
			else if ( tChgBasInfo.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate == VID_FRAME_RATE_50 )
			{
				tChgBasInfo.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate = VID_FRAME_RATE_60;
			}
		}
	}
	
	
    CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetBasEncParam_Req);
	for (u8 byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if ( !m_cSpeaker.m_atXmpuBas[byIndx].m_dwEqpID )
		{
			continue;
		}
		
		if (m_cSpeaker.IsExInfo(wIndex))
		{
			continue;
		}
		
		if ( TP_VALID_HANDLE(wIndex) && byIndx != wIndex  )
		{//wIndex有效时，只开启wIndex的通道 
			continue;
		}
		
        tChgBasInfo.m_dwEqpID = m_cSpeaker.m_atXmpuBas[byIndx].m_dwEqpID;
		cMsg.SetBody(&tChgBasInfo, sizeof(tChgBasInfo));

		cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}
	
	
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
	    AdjustScreenBas(pInst->GetSpeaker().m_pcSingleBas, ptCapNode->m_wEpID, ptCapNode->GetSpeaker());
	}
 
	//CNetPortMgr::AdjustBasDsEqpToConfDsEqp(Inst());  //外设都在会议转发板上，不需要处理
	
	return ;
}

#else
void CUmsBas::SetSpeakerBasEncCmd(u16 wIndex /* = TP_INVALID_INDEX */, BOOL32 bAdjustAud /* = TRUE */)
{
	CUmsConfInst* pInst = Inst();
	
	if (bAdjustAud && Inst()->IsAudNeedBas() )
	{
		AdjustSpeakerAudBas();
	}

	if ( !m_tConfBasMgr.m_bSpeaker )
	{
		return ;
	}

	u16 wEpId = pInst->curSpeakerID();
	if (pInst->GetUmsDiscuss()->IsDiscussModle() && !pInst->IsChairConf())
	{
		wEpId = pInst->chairID();
	}

	TCapNode* ptCapNode = pInst->m_pcNodeMgr->GetForeFatherNode(wEpId);
	if ( NULL == ptCapNode /*|| !ptCapNode->IsChanOn()*/ )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetSpeakerBasEncCmd, AdjustSpeakerBas ptCapNode is NULL! ConfID:%d, ep:%d\n", 
			pInst->GetInsID(), wEpId));
		return ;
	}
	
	//计算当前发言人的后适配的最佳格式
	CalcBasSpeakerOutVidParam(ptCapNode->m_tVidSndFormat.m_tFormat);
	
	TStartBasAdapter tTpStart;

	tTpStart.m_wStaticPayload = ptCapNode->m_tVidSndFormat.m_wStaticPayload;
	tTpStart.m_wDynamicPayload = ptCapNode->m_tVidSndFormat.m_wDynamicPayload;

	tTpStart.m_tEncrypt = pInst->GetConfEncryptInfo();

	tTpStart.m_tBasParam = m_cSpeaker.m_tRealVidPara;
	tTpStart.m_tMaxBasParam = m_cSpeaker.m_tVidPara;
	
	if (pInst->IsAudNeedBas())
	{
		tTpStart.m_emAudForamt = emTPAEnd;
	}
	else
	{
		tTpStart.m_emAudForamt = ptCapNode->m_tAudSndFormat.m_tFormat.m_emFormat;
	}
	
	if( CUmsConfigEx::GetInstance()->GetEnc3060Bas() )
	{
		//发言人适配，不再出25 或 50的 防止：T300接收制式为60，导致画面卡顿
		for ( u16 wIndexFmt = 0; wIndexFmt < tTpStart.m_tBasParam.m_byParamNum; wIndexFmt ++ )
		{
			if ( tTpStart.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate == VID_FRAME_RATE_25 )
			{
				tTpStart.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate = VID_FRAME_RATE_30;
			}
			else if ( tTpStart.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate == VID_FRAME_RATE_50 )
			{
				tTpStart.m_tBasParam.m_atVidParam[wIndexFmt].m_wFrameRate = VID_FRAME_RATE_60;
			}
		}
	}

	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBas_StartAdapter_Req);
	for (u8 byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if ( !m_cSpeaker.m_atBas[byIndx].IsValid() )
		{
			continue;
		}

		if (m_cSpeaker.IsExInfo(wIndex))
		{
			continue;
		}
		
		if ( TP_VALID_HANDLE(wIndex) && byIndx != wIndex  )
		{//wIndex有效时，只开启wIndex的通道 
			continue;
		}

		tTpStart.m_byChnID = m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_wChnIndx;

		cMsg.SetBody(&tTpStart, sizeof(TStartBasAdapter));
		cMsg.Post(m_cSpeaker.m_atBas[byIndx].m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
	}

	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		AdjustScreenBas(pInst->GetSpeaker().m_pcSingleBas, ptCapNode->m_wEpID, ptCapNode->GetSpeaker());
	}

	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(Inst());

	return ;
}

#endif

//看发言人  进行后适配通道调整
void CUmsBas::AdjustSpeakerBas(u16 wIndex /* = TP_INVALID_INDEX */, BOOL32 bAdjustAud /* = TRUE */)
{
#ifdef 	_USE_XMPUEQP_
    SetXmpuSpeakerBasEncCmd(wIndex, bAdjustAud);
#else
	SetSpeakerBasEncCmd(wIndex, bAdjustAud);
#endif
}


void CUmsBas::AdjustSpeakerBasForBrdVmp(BOOL32 bBrdVmpOn)
{
	CUmsConfInst* pInst = Inst();

	if ( !m_tConfBasMgr.m_bSpeaker || pInst->IsChairConf())
	{
		return ;
	}

	u16 wIndx = MIDSCREENINDEX;

#ifdef _USE_XMPUEQP_
    if ( !m_cSpeaker.m_atXmpuBas[wIndx].m_dwEqpID )
#else
    if ( !m_cSpeaker.m_atBas[wIndx].IsValid() )
#endif
	{
		return;
	}
	
	u16 wCapEp = pInst->chairID();
	if (!bBrdVmpOn)
	{
		m_cSpeaker.ClearExInfo();
		AdjustSpeakerBas(MIDSCREENINDEX);
		return;
	}

	TCapNode* ptCapNode = pInst->m_pcNodeMgr->GetForeFatherNode(wCapEp);
	if ( NULL == ptCapNode || !ptCapNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AdjustSpeakerBasForBrdVmp. ptSpeaker is NULL! ConfID:%d, Chair:%d, Speaker:%d, BrdVmpOn:%d.\n", 
			pInst->GetInsID(), pInst->chairID(), pInst->curSpeakerID(), bBrdVmpOn));
		return ;
	}
	
	if (m_cSpeaker.IsExInfo(wIndx) && ptCapNode->m_tVidSndFormat.m_tFormat == m_cSpeaker.m_tSndVidFormatEx)
	{
		return;
	}

	m_cSpeaker.m_wScreenEx = wIndx + 1;

	//计算当前的后适配的最佳格式
	CalcBasSpeakerOutVidParamEx(ptCapNode->m_tVidSndFormat.m_tFormat);
	CTpMsg cMsg;

#ifdef _USE_XMPUEQP_

	TXmpuChgBasInfo  tChgBasInfo;
	tChgBasInfo.m_wDynamicPayload = ptCapNode->m_tVidSndFormat.m_wDynamicPayload;
    tChgBasInfo.m_wStaticPayload  = ptCapNode->m_tVidSndFormat.m_wStaticPayload;
    tChgBasInfo.m_tEncrypt        = pInst->GetConfEncryptInfo();
    tChgBasInfo.m_tBasParam  =   m_cSpeaker.m_tRealVidPara;
    tChgBasInfo.m_wConfID  =   pInst->GetInsID();
	tChgBasInfo.m_dwEqpID = m_cSpeaker.m_atXmpuBas[wIndx].m_dwEqpID;
	cMsg.SetEvent(evXmpu_SetBasEncParam_Req);
	cMsg.SetBody(&tChgBasInfo, sizeof(tChgBasInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

#else
	TStartBasAdapter tTpStart;
	
	tTpStart.m_wStaticPayload = ptCapNode->m_tVidSndFormat.m_wStaticPayload;
	tTpStart.m_wDynamicPayload = ptCapNode->m_tVidSndFormat.m_wDynamicPayload;
	tTpStart.m_tEncrypt = pInst->GetConfEncryptInfo();

	if (pInst->IsAudNeedBas())
	{
		tTpStart.m_emAudForamt = emTPAEnd;
	}
	else
	{
		tTpStart.m_emAudForamt = ptCapNode->m_tAudSndFormat.m_tFormat.m_emFormat;
	}
	
	tTpStart.m_tBasParam = m_cSpeaker.m_tRealVidParaEx;
	tTpStart.m_tMaxBasParam = m_cSpeaker.m_tVidPara;
	

	cMsg.SetEvent(ev_TPBas_StartAdapter_Req);
	
	tTpStart.m_byChnID = m_cSpeaker.m_atBas[wIndx].m_tBasChnInfo.m_wChnIndx;
	
	cMsg.SetBody(&tTpStart, sizeof(TStartBasAdapter));
	cMsg.Post(m_cSpeaker.m_atBas[wIndx].m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));

#endif

	return ;
}


#ifdef _USE_XMPUEQP_

void CUmsBas::SetXmpuDualVidBasEncCmd(void)
{
	CUmsConfInst* pInst = Inst();
	
	if ( Inst()->IsAudNeedBas() )
	{
		AdjustDualAudBas();
	}
	
	if ( !m_tConfBasMgr.m_bDual )
	{
		return ;
	}

	TUmsVidFormat tVidFormat;
	TXmpuChgBasInfo  tChgBasInfo;

	TCapNode* ptDualNode = pInst->m_pcNodeMgr->GetForeFatherNode(pInst->m_pcDual->GetDualID());
	if ( NULL == ptDualNode || !ptDualNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuDualVidBasEncCmd. ptDualNode is NULL! ConfID:%d, DualEp:%d\n", 
			pInst->GetInsID(), pInst->m_pcDual->GetDualID()));
		return ;
	}
	
	if ( !ptDualNode->m_tRmtChan.m_tDualVidEnc.IsOpen() && !ptDualNode->m_tRmtChan.m_tDualVidDec.IsOpen() )
	{//双流视频通道没协商出来，就不在适配操作 防止异常
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuDualVidBasEncCmd. dual src ep  chan Invalid! ConfID:%d, DualEp:%d, venc:%d, vdec:%d\n", 
			pInst->GetInsID(), pInst->m_pcDual->GetDualID(), ptDualNode->m_tRmtChan.m_tDualVidEnc.IsOpen(),
			ptDualNode->m_tRmtChan.m_tDualVidDec.IsOpen()));
		return ;
	}
	
	//级联双流适配  UMS之间的双流通道只打开了上级到下级的通道
	//双流源 通道格式选择 需要特别注意！
	if ( ptDualNode->IsUms() && ptDualNode->m_wEpID != CALLER_EP_INDEX )
	{//下级发双流，则需要取接收通道格式
		tVidFormat = ptDualNode->m_tDualVidRcvFormat.m_tFormat;
		tChgBasInfo.m_wDynamicPayload = ptDualNode->m_tDualVidRcvFormat.m_wDynamicPayload;
        tChgBasInfo.m_wStaticPayload  = ptDualNode->m_tDualVidRcvFormat.m_wStaticPayload;
	}
	else
	{
		tVidFormat = ptDualNode->m_tDualVidSndFormat.m_tFormat;
		tChgBasInfo.m_wStaticPayload  = ptDualNode->m_tDualVidSndFormat.m_wStaticPayload;
		tChgBasInfo.m_wDynamicPayload = ptDualNode->m_tDualVidSndFormat.m_wDynamicPayload;
	}
	
	if ( !tVidFormat.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuDualVidBasEncCmd. dual src ep  vidformat Invalid! ConfID:%d, DualEp:%d, res:%d\n", 
			pInst->GetInsID(), pInst->m_pcDual->GetDualID(), tVidFormat.m_emRes));
		return ;
	}
	
	m_cDual.m_tEpFormat = tVidFormat;
	
	//计算双流后适配的最佳格式
	CalcBasDualOutVidParam(m_cDual.m_tEpFormat);

	tChgBasInfo.m_wConfID   = pInst->GetInsID();
	tChgBasInfo.m_dwEqpID   = m_cDual.m_tXmpuBas.m_dwEqpID;
    tChgBasInfo.m_tBasParam = m_cDual.m_tRealVidPara;
    tChgBasInfo.m_tEncrypt  = pInst->GetConfEncryptInfo();

	MdlHint(Ums_Mdl_Call, ("CUmsBas::SetXmpuDualVidBasEncCmd  snd StartAdapter_Req. ConfID:%d, DualEp:%d, EqpId:%d  DualSload:%d  Dualdload:%d baspara(%d). \n", 
		pInst->GetInsID(), pInst->m_pcDual->GetDualID(), tChgBasInfo.m_wConfID, tChgBasInfo.m_wStaticPayload, tChgBasInfo.m_wDynamicPayload,
		tChgBasInfo.m_tBasParam.m_byParamNum));
	
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetBasEncParam_Req);
	cMsg.SetBody(&tChgBasInfo, sizeof(tChgBasInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(Inst());
	
	return ;
}

#else
void CUmsBas::SetDualVidBasEncCmd(void)
{
	CUmsConfInst* pInst = Inst();
	
	if ( Inst()->IsAudNeedBas() )
	{
		AdjustDualAudBas();
		
	}
	
	if ( !m_tConfBasMgr.m_bDual )
	{
		return ;
	}
	
	
	TStartBasAdapter tTpStart;
	TUmsVidFormat tVidFormat;

	TCapNode* ptDualNode = pInst->m_pcNodeMgr->GetForeFatherNode(pInst->m_pcDual->GetDualID());
	if ( NULL == ptDualNode || !ptDualNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetDualVidBasEncCmd,  AdjustDualBas ptDualNode is NULL! ConfID:%d, DualEp:%d\n", 
			pInst->GetInsID(), pInst->m_pcDual->GetDualID()));
		return ;
	}
	
	if ( !ptDualNode->m_tRmtChan.m_tDualVidEnc.IsOpen() && !ptDualNode->m_tRmtChan.m_tDualVidDec.IsOpen() )
	{//双流视频通道没协商出来，就不在适配操作 防止异常
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetDualVidBasEncCmd, AdjustDualBas dual src ep  chan Invalid! ConfID:%d, DualEp:%d, venc:%d, vdec:%d\n", 
			pInst->GetInsID(), pInst->m_pcDual->GetDualID(), ptDualNode->m_tRmtChan.m_tDualVidEnc.IsOpen(),
			ptDualNode->m_tRmtChan.m_tDualVidDec.IsOpen()));
		return ;
	}
	
	//级联双流适配  UMS之间的双流通道只打开了上级到下级的通道
	//双流源 通道格式选择 需要特别注意！
	if ( ptDualNode->IsUms() && ptDualNode->m_wEpID != CALLER_EP_INDEX )
	{//下级发双流，则需要取接收通道格式
		tVidFormat = ptDualNode->m_tDualVidRcvFormat.m_tFormat;
		tTpStart.m_wStaticPayload = ptDualNode->m_tDualVidRcvFormat.m_wStaticPayload;
		tTpStart.m_wDynamicPayload = ptDualNode->m_tDualVidRcvFormat.m_wDynamicPayload;
		if (pInst->IsAudNeedBas())
		{
			tTpStart.m_emAudForamt = emTPAEnd;
		}
		else
		{
			tTpStart.m_emAudForamt = ptDualNode->m_tDualAudRcvFormat.m_tFormat.m_emFormat;
		}
	}
	else
	{
		tVidFormat = ptDualNode->m_tDualVidSndFormat.m_tFormat;
		tTpStart.m_wStaticPayload = ptDualNode->m_tDualVidSndFormat.m_wStaticPayload;
		tTpStart.m_wDynamicPayload = ptDualNode->m_tDualVidSndFormat.m_wDynamicPayload;
		if (pInst->IsAudNeedBas() || ptDualNode->IsSingleVidSnd())
		{
			tTpStart.m_emAudForamt = emTPAEnd;
		}
		else
		{
			tTpStart.m_emAudForamt = ptDualNode->m_tDualAudSndFormat.m_tFormat.m_emFormat;
		}
	}
	
	if ( !tVidFormat.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetDualVidBasEncCmd, AdjustDualBas dual src ep  vidformat Invalid! ConfID:%d, DualEp:%d, res:%d\n", 
			pInst->GetInsID(), pInst->m_pcDual->GetDualID(), tVidFormat.m_emRes));
		return ;
	}
	
	m_cDual.m_tEpFormat = tVidFormat;
	
	//计算双流后适配的最佳格式
	CalcBasDualOutVidParam(m_cDual.m_tEpFormat);

	tTpStart.m_byChnID = m_cDual.m_tBas.m_tBasChnInfo.m_wChnIndx;
	tTpStart.m_tBasParam = m_cDual.m_tRealVidPara;
	tTpStart.m_tMaxBasParam = m_cDual.m_tVidPara;
	tTpStart.m_tEncrypt = pInst->GetConfEncryptInfo();


	MdlHint(Ums_Mdl_Call, ("CUmsBas::SetDualVidBasEncCmd, AdjustDualBas snd StartAdapter_Req. ConfID:%d, DualEp:%d, ChnId:%d  DualSload:%d  Dualdload:%d baspara(%d, %d). \n", 
		pInst->GetInsID(), pInst->m_pcDual->GetDualID(), tTpStart.m_byChnID, tTpStart.m_wStaticPayload, tTpStart.m_wDynamicPayload,
		tTpStart.m_tBasParam.m_byParamNum,  tTpStart.m_tMaxBasParam.m_byParamNum));


	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBas_StartAdapter_Req);
	cMsg.SetBody(&tTpStart, sizeof(TStartBasAdapter));
	cMsg.Post(m_cDual.m_tBas.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));


	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(Inst());
	
	return ;
}


#endif

//看双流
void CUmsBas::AdjustDualBas()
{
#ifdef _USE_XMPUEQP_
    SetXmpuDualVidBasEncCmd();
#else
    SetDualVidBasEncCmd();
#endif
}

#ifdef _USE_XMPUEQP_
void CUmsBas::SetXmpuChairVidBasEncCmd(u16 wIndex)
{
	CUmsConfInst* pInst = Inst();

	if ( Inst()->IsAudNeedBas() && !pInst->GetRollCallMgr()->IsRollCallModle())
	{ //点名模式没有用到主席音频BAS
		AdjustChairAudBas();
	}

	if ( !m_tConfBasMgr.m_bChair )
	{
		return ;
	}

    TCapNode* ptChair = NULL;
	if (pInst->GetRollCallMgr()->IsRollCallModle())
	{
	    u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();

        if (pInst->IsChairConf())
		{ //上级
			ptChair = pInst->m_pcNodeMgr->GetForeFatherNode(wRollCaller);
			if ( NULL == ptChair || !ptChair->IsChanOn()  )
			{
				MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuChairVidBasEncCmd,  ptChair is NULL! ConfID:%d, Chair:%d\n", 
					     pInst->GetInsID(), pInst->chairID()));
				return ;
			}

		} else 
		{ //下级
			ptChair = pInst->m_pcNodeMgr->GetCapsetNode(wRollCaller);
			if(NULL != ptChair)
			{   //点名人在当前下级UMS下
                if(!ptChair->IsChanOn())
				{
					MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuChairVidBasEncCmd. rollcaller in lowums but chanoff ! ConfID:%d, rollcall:%d\n", 
				             pInst->GetInsID(), wRollCaller));
				    return;
				}
			} else {
                //点名人不在当前下级UMS下
                ptChair = pInst->m_pcNodeMgr->GetCaller();
				if (NULL == ptChair || !ptChair->IsChanOn())
				{
					MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuChairVidBasEncCmd. caller(65) not chanon ! ConfID:%d\n", 
				             pInst->GetInsID()));
                    return;
				}
			}

		}

	} else 
	{
         ptChair = pInst->m_pcNodeMgr->GetForeFatherNode(pInst->chairID());
		 if ( NULL == ptChair || !ptChair->IsChanOn()  )
		 {
			 MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuChairVidBasEncCmd. ptChair is NULL! ConfID:%d, Chair:%d\n", 
				 pInst->GetInsID(), pInst->chairID()));
			 return ;
		 }
	}

	TCapNode* ptSpeaker = pInst->m_pcNodeMgr->GetForeFatherNode(pInst->curSpeakerID());
	if ( NULL == ptSpeaker || !ptSpeaker->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AdjustSpeakerBas. ptSpeaker is NULL! ConfID:%d, Speaker:%d\n", 
			pInst->GetInsID(), pInst->curSpeakerID()));
		return ;
	}

	//按照默认最大分配
	TUmsVidFormat tVidFormat;
	GetDefaultMaxFormat(tVidFormat);

	TStartBasAdapter tTpStart;

	TXmpuChgBasInfo  tChgBasInfo;
    tChgBasInfo.m_tBasParam.m_byParamNum  =   1;
    tChgBasInfo.m_tBasParam.m_atVidParam[0] = ptSpeaker->m_tVidRcvFormat.m_tFormat;
	tChgBasInfo.m_wDynamicPayload = ptChair->m_tVidSndFormat.m_wDynamicPayload;
    tChgBasInfo.m_wStaticPayload  = ptChair->m_tVidSndFormat.m_wStaticPayload;
    tChgBasInfo.m_tEncrypt        = pInst->GetConfEncryptInfo();
    tChgBasInfo.m_wConfID         = pInst->GetInsID();

	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetBasEncParam_Req);
	for (u8 byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if ( !m_cChair.m_atXmpuBas[byIndx].m_dwEqpID )
		{
			continue;
		}

		if ( TP_VALID_HANDLE(wIndex) && byIndx != wIndex  )
		{//wIndex有效时，只开启wIndex的通道 
			continue;
		}
        tChgBasInfo.m_dwEqpID = m_cChair.m_atXmpuBas[byIndx].m_dwEqpID;
		cMsg.SetBody(&tChgBasInfo, sizeof(tChgBasInfo));
		cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}

    if (pInst->GetRollCallMgr()->IsRollCallModle())
	{
		CNetPortMgr::AdjustRollCallerToBas(Inst());
	} else 
	{
		CNetPortMgr::CreateVirChairToBas(Inst());
	}
}
#else
void CUmsBas::SetChairVidBasEncCmd(u16 wIndex)
{
	CUmsConfInst* pInst = Inst();

	if ( Inst()->IsAudNeedBas() && !pInst->GetRollCallMgr()->IsRollCallModle())
	{ //点名模式没有用到主席音频BAS
		AdjustChairAudBas();
	}

	if ( !m_tConfBasMgr.m_bChair )
	{
		return ;
	}


    TCapNode* ptChair = NULL;
	if (pInst->GetRollCallMgr()->IsRollCallModle())
	{
	    u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();

        if (pInst->IsChairConf())
		{ //上级
			ptChair = pInst->m_pcNodeMgr->GetForeFatherNode(wRollCaller);
			if ( NULL == ptChair || !ptChair->IsChanOn()  )
			{
				MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairVidBasEncCmd, AdjustChairBas ptChair is NULL! ConfID:%d, Chair:%d\n", 
					     pInst->GetInsID(), pInst->chairID()));
				return ;
			}

		} else 
		{ //下级
			ptChair = pInst->m_pcNodeMgr->GetCapsetNode(wRollCaller);
			if(NULL != ptChair)
			{   //点名人在当前下级UMS下
                if(!ptChair->IsChanOn())
				{
					MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairVidBasEncCmd, AdjustChairBas rollcaller in lowums but chanoff ! ConfID:%d, rollcall:%d\n", 
				             pInst->GetInsID(), wRollCaller));
				    return;
				}
			} else {
                //点名人不在当前下级UMS下
                ptChair = pInst->m_pcNodeMgr->GetCaller();
				if (NULL == ptChair || !ptChair->IsChanOn())
				{
					MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairVidBasEncCmd, AdjustChairBas caller(65) not chanon ! ConfID:%d\n", 
				             pInst->GetInsID()));
                    return;
				}
			}

		}

	} else 
	{
         ptChair = pInst->m_pcNodeMgr->GetForeFatherNode(pInst->chairID());
		 if ( NULL == ptChair || !ptChair->IsChanOn()  )
		 {
			 MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairVidBasEncCmd, AdjustChairBas ptChair is NULL! ConfID:%d, Chair:%d\n", 
				 pInst->GetInsID(), pInst->chairID()));
			 return ;
		 }
	}

	TCapNode* ptSpeaker = pInst->m_pcNodeMgr->GetForeFatherNode(pInst->curSpeakerID());
	if ( NULL == ptSpeaker || !ptSpeaker->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairVidBasEncCmd, AdjustSpeakerBas ptSpeaker is NULL! ConfID:%d, Speaker:%d\n", 
			pInst->GetInsID(), pInst->curSpeakerID()));
		return ;
	}

	//按照默认最大分配
	TUmsVidFormat tVidFormat;
	GetDefaultMaxFormat(tVidFormat);

	TStartBasAdapter tTpStart;

	tTpStart.m_tBasParam.m_byParamNum = 1;
	if ( ptSpeaker->m_tVidRcvFormat.m_tFormat.IsValid() )
	{
		memcpy(&tTpStart.m_tBasParam.m_atVidParam[0], &ptSpeaker->m_tVidRcvFormat.m_tFormat, sizeof(TUmsVidFormat));
	}
	else
	{//发言人无有效接收，则后适配不出
		memcpy(&tTpStart.m_tBasParam.m_atVidParam[0], &tVidFormat, sizeof(TUmsVidFormat));
		tTpStart.m_tBasParam.m_atVidParam[0].m_wBitrate = 0;
	}
	
	tTpStart.m_tMaxBasParam.m_byParamNum = 1;
	memcpy(&tTpStart.m_tMaxBasParam.m_atVidParam[0], &tVidFormat, sizeof(TUmsVidFormat));

	tTpStart.m_wStaticPayload = ptChair->m_tVidSndFormat.m_wStaticPayload;
	tTpStart.m_wDynamicPayload = ptChair->m_tVidSndFormat.m_wDynamicPayload;
	tTpStart.m_emAudForamt = ptChair->m_tAudSndFormat.m_tFormat.m_emFormat;	
	tTpStart.m_tEncrypt = pInst->GetConfEncryptInfo();

	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBas_StartAdapter_Req);
	for (u8 byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if ( !m_cChair.m_atBas[byIndx].IsValid() )
		{
			continue;
		}

		if ( TP_VALID_HANDLE(wIndex) && byIndx != wIndex  )
		{//wIndex有效时，只开启wIndex的通道 
			continue;
		}

		tTpStart.m_byChnID = m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_wChnIndx;

		cMsg.SetBody(&tTpStart, sizeof(TStartBasAdapter));
		cMsg.Post(m_cChair.m_atBas[byIndx].m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
	}

    if (pInst->GetRollCallMgr()->IsRollCallModle())
	{
		CNetPortMgr::AdjustRollCallerToBas(Inst());
	} else 
	{
		CNetPortMgr::CreateVirChairToBas(Inst());
	}
}
#endif


//看主席
void CUmsBas::AdjustChairBas(u16 wIndex)
{
#ifdef _USE_XMPUEQP_
    SetXmpuChairVidBasEncCmd(wIndex);
#else
    SetChairVidBasEncCmd(wIndex);
#endif
}

#ifdef _USE_XMPUEQP_
void CUmsBas::SetXmpuScreenBasEncCmd( CScreenBasRes* ptScreenBasRes, u16 wSrcEp, u16 wScreenIndx, u8 byFormatNum, TUmsVidFormat atVidFormat[])
{
	CUmsConfInst* pInst = Inst();
	
	if ( NULL == ptScreenBasRes )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuScreenBasEncCmd. ptScreenBasRes is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
	//查找该适配资源是否存在
	u16 wIndx = m_tConfBasMgr.FindBasChnResByIndx(ptScreenBasRes);
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuScreenBasEncCmd. BasEqpRes no Exist! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_tXmpuBas.m_dwEqpID, 
			wIndx, ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}

	//适配资源是否有效
	if ( !ptScreenBasRes->IsBasValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuScreenBasEncCmd. BasEqpRes Invalid! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_tXmpuBas.m_dwEqpID,  
			wIndx, ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}

	if ( ptScreenBasRes->m_byFormatNum == 0 )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuScreenBasEncCmd. FormatNum is 0! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_tXmpuBas.m_dwEqpID,  
			wIndx, ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}

	ptScreenBasRes->m_wSrcEp = wSrcEp;
	ptScreenBasRes->m_wSrcScreenIndx = wScreenIndx;

	TCapNode* ptSrcNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptScreenBasRes->m_wSrcEp);
	if ( NULL == ptSrcNode || !ptSrcNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuScreenBasEncCmd. ptSrcNode is NULL! ConfID:%d, SrcEpID:%d, SrcScreenIndx:%d, FormatNum:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx, ptScreenBasRes->m_byFormatNum));
		return ;
	}
		
	//调整参数
	TStartBasAdapter tTpStart;
	TXmpuChgBasInfo  tChgBasInfo;
	tChgBasInfo.m_wConfID  =   pInst->GetInsID();
    tChgBasInfo.m_tEncrypt        = pInst->GetConfEncryptInfo();

    TTPBasVidParam tMaxBasParam;

    tMaxBasParam.m_byParamNum = ptScreenBasRes->m_byFormatNum;
    u16 wMinParamNum = localmin(tMaxBasParam.m_byParamNum, TP_CONF_MAX_MINOR_VIDEO_RES_NUM);
	memcpy(tMaxBasParam.m_atVidParam, ptScreenBasRes->m_atVidFormat, sizeof(TUmsVidFormat) * wMinParamNum);

	if ( ptScreenBasRes->m_byFormatNum == 1 && !ptScreenBasRes->m_bIsMultOut)
	{
		if ( NULL == atVidFormat )
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuScreenBasEncCmd. atVidFormat is NULL! ConfID:%d\n", pInst->GetInsID()));
			return ;
		}
		if( atVidFormat[0].IsValid() )
		{
			tChgBasInfo.m_tBasParam.m_byParamNum = ptScreenBasRes->m_byFormatNum;
            wMinParamNum = localmin(tChgBasInfo.m_tBasParam.m_byParamNum, TP_CONF_MAX_MINOR_VIDEO_RES_NUM);
			memcpy(tChgBasInfo.m_tBasParam.m_atVidParam, &atVidFormat[0], sizeof(TUmsVidFormat) * wMinParamNum);
		}
		else
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuScreenBasEncCmd. atVidFormat IsInValid! ConfID:%d, EqpId:%d\n", 
				    pInst->GetInsID()));
			return;
		}
	}
	else
	{
		ptScreenBasRes->m_tSndVidFormat = ptSrcNode->m_tVidSndFormat.m_tFormat;
		//计算
		CalcBasVidParamAPI(TRUE, ptScreenBasRes->m_tSndVidFormat, tMaxBasParam, 
						tChgBasInfo.m_tBasParam, ptScreenBasRes->m_wNeedAdjustLvl, ptScreenBasRes->m_tNeedAdjustFmt);

		memcpy(&ptScreenBasRes->m_tRealVidPara, &tChgBasInfo.m_tBasParam, sizeof(TTPBasVidParam));
	}

	tChgBasInfo.m_dwEqpID = m_tConfBasMgr.m_atBasChsRes[wIndx].m_tXmpuBas.m_dwEqpID;
	tChgBasInfo.m_wDynamicPayload = ptSrcNode->m_tVidSndFormat.m_wDynamicPayload;
    tChgBasInfo.m_wStaticPayload  = ptSrcNode->m_tVidSndFormat.m_wStaticPayload;

// 	if (pInst->IsAudNeedBas())
// 	{
// 		tTpStart.m_emAudForamt = emTPAEnd;
// 	}
// 	else
// 	{
// 		tTpStart.m_emAudForamt = ptSrcNode->m_tAudSndFormat.m_tFormat.m_emFormat;
// 	}

	//调整
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetBasEncParam_Req);
    cMsg.SetBody(&tChgBasInfo, sizeof(tChgBasInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	return ;
}
#else
void CUmsBas::SetScreenBasEncCmd( CScreenBasRes* ptScreenBasRes, u16 wSrcEp, u16 wScreenIndx, u8 byFormatNum, TUmsVidFormat atVidFormat[])
{
	CUmsConfInst* pInst = Inst();
	
	if ( NULL == ptScreenBasRes )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetScreenBasEncCmd. ptScreenBasRes is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
	//查找该适配资源是否存在
	u16 wIndx = m_tConfBasMgr.FindBasChnResByIndx(ptScreenBasRes);
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetScreenBasEncCmd. BasEqpRes no Exist! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
			ptScreenBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}

	//适配资源是否有效
	if ( !ptScreenBasRes->m_tBasEqpRes.IsValid() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetScreenBasEncCmd. BasEqpRes Invalid! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
			ptScreenBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}

	if ( ptScreenBasRes->m_byFormatNum == 0 )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetScreenBasEncCmd. FormatNum is 0! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID, 
			ptScreenBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}

	ptScreenBasRes->m_wSrcEp = wSrcEp;
	ptScreenBasRes->m_wSrcScreenIndx = wScreenIndx;

	TCapNode* ptSrcNode = pInst->m_pcNodeMgr->GetForeFatherNode(ptScreenBasRes->m_wSrcEp);
	if ( NULL == ptSrcNode || !ptSrcNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetScreenBasEncCmd. ptSrcNode is NULL! ConfID:%d, SrcEpID:%d, SrcScreenIndx:%d, FormatNum:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx, ptScreenBasRes->m_byFormatNum));
		return ;
	}
		
	//调整参数
	TStartBasAdapter tTpStart;

	tTpStart.m_tMaxBasParam.m_byParamNum = ptScreenBasRes->m_byFormatNum;
	memcpy(&tTpStart.m_tMaxBasParam.m_atVidParam[0], &ptScreenBasRes->m_atVidFormat[0], 
												sizeof(TUmsVidFormat)*tTpStart.m_tMaxBasParam.m_byParamNum);


	if ( ptScreenBasRes->m_byFormatNum == 1 && !ptScreenBasRes->m_bIsMultOut)
	{
		if ( NULL == atVidFormat )
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::SetScreenBasEncCmd. atVidFormat is NULL! ConfID:%d\n", pInst->GetInsID()));
			return ;
		}
		if( atVidFormat[0].IsValid() )
		{
			tTpStart.m_tBasParam.m_byParamNum = ptScreenBasRes->m_byFormatNum;
			memcpy(&tTpStart.m_tBasParam.m_atVidParam[0], &atVidFormat[0], sizeof(TUmsVidFormat)*ptScreenBasRes->m_byFormatNum);
		}
		else
		{ 
			//如果设置了bas 后适配的格式，但格式是无效的则不编码了
			memcpy(&tTpStart.m_tBasParam, &tTpStart.m_tMaxBasParam, sizeof(tTpStart.m_tMaxBasParam));

			tTpStart.m_tBasParam.m_atVidParam[0].m_wBitrate = 0;
		}
	}
	else
	{
		ptScreenBasRes->m_tSndVidFormat = ptSrcNode->m_tVidSndFormat.m_tFormat;
		//计算
		CalcBasVidParamAPI(TRUE, ptScreenBasRes->m_tSndVidFormat, tTpStart.m_tMaxBasParam, 
						tTpStart.m_tBasParam, ptScreenBasRes->m_wNeedAdjustLvl, ptScreenBasRes->m_tNeedAdjustFmt);

		memcpy(&ptScreenBasRes->m_tRealVidPara, &tTpStart.m_tBasParam, sizeof(TTPBasVidParam));
	}

	tTpStart.m_byChnID = m_tConfBasMgr.m_atBasChsRes[wIndx].m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx;
	tTpStart.m_wStaticPayload = ptSrcNode->m_tVidSndFormat.m_wStaticPayload;
	tTpStart.m_wDynamicPayload = ptSrcNode->m_tVidSndFormat.m_wDynamicPayload;
	if (pInst->IsAudNeedBas())
	{
		tTpStart.m_emAudForamt = emTPAEnd;
	}
	else
	{
		tTpStart.m_emAudForamt = ptSrcNode->m_tAudSndFormat.m_tFormat.m_emFormat;
	}
	tTpStart.m_tEncrypt = pInst->GetConfEncryptInfo();

	//调整
	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBas_StartAdapter_Req);
	cMsg.SetBody(&tTpStart, sizeof(TStartBasAdapter));

	cMsg.Post(m_tConfBasMgr.m_atBasChsRes[wIndx].m_tBasEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));

	return ;
}

#endif


void CUmsBas::AdjustScreenBas( CScreenBasRes* ptScreenBasRes, u16 wSrcEp, u16 wScreenIndx, u8 byFormatNum, TUmsVidFormat atVidFormat[])
{
#ifdef _USE_XMPUEQP_
    SetXmpuScreenBasEncCmd(ptScreenBasRes, wSrcEp, wScreenIndx, byFormatNum, atVidFormat);
#else 
    SetScreenBasEncCmd(ptScreenBasRes, wSrcEp, wScreenIndx, byFormatNum, atVidFormat);
#endif
}

void CUmsBas::OnChangeBasSndAddr( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	TBasMediaInfo tMediaInfo;
	TP_SAFE_CAST(tMediaInfo, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("CUmsBas::OnChangeBasSndAddr. ConfID:%d, EqpID:%d, NewDsIP:"TPIPFORMAT"\n", 
													pInst->GetInsID(), tMediaInfo.m_byEqpID, Tpu32ToIP(tMediaInfo.m_dwNewDsIP)));

	u8 byIndx = 0;
	//发言人
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if(m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_byEqpID == tMediaInfo.m_byEqpID)
		{
			m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.SetMediaInfo(tMediaInfo);
		}
	}
	//主席
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if(m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_byEqpID == tMediaInfo.m_byEqpID)
		{
			m_cChair.m_atBas[byIndx].m_tBasChnInfo.SetMediaInfo(tMediaInfo);
		}
	}
	
	if( m_cDual.m_tBas.m_tBasChnInfo.m_byEqpID == tMediaInfo.m_byEqpID)
	{//双流
		m_cDual.m_tBas.m_tBasChnInfo.SetMediaInfo(tMediaInfo);
	}
	
	//其他
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if( m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_byEqpID == tMediaInfo.m_byEqpID)
		{
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.SetMediaInfo(tMediaInfo);
		}
	}

	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(pInst);

	return ;
}

void CUmsBas::OnBasDisConnect( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();

	if ( pInst->m_bIsQuiting || CUmsConfInst::inst_idle == pInst->CurState() )
	{//正在退出会议不处理
		return ;
	}

	u8 byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("CUmsBas::OnBasDisConnect. ConfID:%d, EqpID:%d\n", pInst->GetInsID(), byEqpID));

	BasEqpRetProc(CScreenBasRes::VidBasCB_DisConnect, byEqpID);

	return ;
}

void CUmsBas::OnBasNAck( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();

	if ( pInst->m_bIsQuiting || CUmsConfInst::inst_idle == pInst->CurState() )
	{//正在退出会议不处理
		return ;
	}

	TTPBasNAck tNAck;
	TP_SAFE_CAST(tNAck, ptMsg->GetBody());

	MdlHint(Ums_Mdl_Call, ("CUmsBas::OnBasNAck. ConfID:%d, EqpID:%d, ChnIndex:%d\n", 
																pInst->GetInsID(), tNAck.m_byEqpID, tNAck.m_wChnIndx));


	BasEqpRetProc(CScreenBasRes::VidBasCB_NAck, tNAck.m_byEqpID, tNAck.m_wChnIndx);

	return ;
}

void CUmsBas::BasEqpRetProc( CScreenBasRes::VidBasCBType emType, u8 byEqpID, u16 wChnIndx /*= TP_INVALID_INDEX*/ )
{
	CUmsConfInst* pInst = Inst();
	u8	byIndx = 0;
	//发言人
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if( (m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_byEqpID == byEqpID) &&
			( TP_VALID_HANDLE(wChnIndx) ? m_cSpeaker.m_atBas[byIndx].m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ))
		{
			if ( emType == CScreenBasRes::VidBasCB_NAck )
			{
				pInst->SelfHungupImmediately(TP_UMS_BasStartFail);

				return ;
			}
			else if (emType == CScreenBasRes::VidBasCB_DisConnect)
			{
				pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);

				return;
			}
			else if ( emType == CScreenBasRes::VidBasCB_AskKey )
			{
				if ( pInst->GetVmp()->IsBrdVmp() && byIndx == MIDSCREENINDEX  )
				{//广播合成 中间屏
					if (pInst->IsChairConf())
					{
						pInst->GetVmp()->AskFrameToBrdVmp(pInst->GetVmp()->GetConfBrdVmp(), pInst->curSpeakerID(), TRUE);
					}
					else
					{
						pInst->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeyBrdVmp);
					}
				}
				else if (pInst->GetUmsDiscuss()->IsDiscussModle())
				{//其次讨论
					pInst->GetUmsDiscuss()->AskKeyFrameFromBas((u16)byIndx);
				}
				else
				{
					pInst->AskKeyByScreen(pInst->curSpeakerID(), byIndx, EmAskKeySpeaker);
				}

				return ;
			}
		}
	}

	//主席
	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if( (m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_byEqpID == byEqpID) &&
			( TP_VALID_HANDLE(wChnIndx) ? m_cChair.m_atBas[byIndx].m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ))
		{

			if ( emType == CScreenBasRes::VidBasCB_DisConnect)
			{
				pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
				
				return ;
			} else if (emType == CScreenBasRes::VidBasCB_NAck)
			{
				pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
				
				return ;
			}
			else if ( emType == CScreenBasRes::VidBasCB_AskKey )
			{
				if (pInst->GetRollCallMgr()->IsRollCallModle())
				{
                    u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();
					if (pInst->IsChairConf())
					{
                        pInst->AskKeyByScreen(wRollCaller, byIndx, EmAskKeyChair);
					} 
					else 
					{
                        if (NULL != pInst->GetNodeMgr()->GetCapsetNode(wRollCaller))
						{
                            pInst->AskKeyByScreen(wRollCaller, byIndx, EmAskKeyChair);
						}
						else
						{
                            pInst->AskKeyByScreen(CALLER_EP_INDEX, byIndx, EmAskKeyChair);
						}
					}
				}
				else
				{
					pInst->AskKeyByScreen(pInst->chairID(), byIndx, EmAskKeyChair);
				}


				return ;
			}
		}
	}

	//双流
	if ( m_cDual.m_tBas.m_tBasChnInfo.m_byEqpID == byEqpID &&
		( TP_VALID_HANDLE(wChnIndx) ? m_cDual.m_tBas.m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ) )
	{
		if ( emType == CScreenBasRes::VidBasCB_DisConnect
			|| emType == CScreenBasRes::VidBasCB_NAck )
		{//stop dual
			Inst()->GetDualMgr()->OnStopDualCmdForUmcCnc();
			Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Dual_BasDisCnnt, Inst()->chairID());
			return ;
		}
		else if ( emType == CScreenBasRes::VidBasCB_AskKey )
		{
			TUmsHandle tHandle;
			tHandle.MakeAppHandle(Inst()->GetInsID(), TP_INVALID_INDEX);
			BOOL32	bReqSys = TRUE;
			CTpMsg cMsg;
			cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
			cMsg.CatBody(&bReqSys, sizeof(BOOL32));
			pInst->m_pcDual->OnAskKeyFrame(&cMsg);

			return ;
		}
	}

	for ( byIndx = 0; byIndx < BAS_CHN_RES_MAX_NUM; byIndx ++ )
	{
		if ( !m_tConfBasMgr.m_atBasChsRes[byIndx].IsBasValid() )
		{
			continue;
		}
		
		if( (m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_byEqpID == byEqpID) &&
			( TP_VALID_HANDLE(wChnIndx) ? m_tConfBasMgr.m_atBasChsRes[byIndx].m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ))
		{
			m_tConfBasMgr.m_atBasChsRes[byIndx].m_pfCB(emType, m_tConfBasMgr.m_atBasChsRes[byIndx].m_pParam, &m_tConfBasMgr.m_atBasChsRes[byIndx]);

			if(TP_VALID_HANDLE(wChnIndx))
			{//通道索引有效，认为处理结束
				return ;
			}
		}
	}

	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if( (m_atAudBasSpeaker[byIndx].m_tEqpRes.m_tBasChnInfo.m_byEqpID == byEqpID) &&
			( TP_VALID_HANDLE(wChnIndx) ? m_atAudBasSpeaker[byIndx].m_tEqpRes.m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ))
		{
			if ( emType == CScreenBasRes::VidBasCB_NAck )
			{
				pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
			}
			else
			{
				pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
			}
			return ;
		}
	}

	if( (m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_byEqpID == byEqpID) &&
		( TP_VALID_HANDLE(wChnIndx) ? m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ))
	{
		if ( emType == CScreenBasRes::VidBasCB_NAck )
		{
			pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
		}
		else
		{
			pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
		}
		return ;
	}

	for ( byIndx = 0; byIndx < TP_MAX_STREAMNUM; byIndx ++ )
	{
		if( (m_atAudBasChair[byIndx].m_tEqpRes.m_tBasChnInfo.m_byEqpID == byEqpID) &&
			( TP_VALID_HANDLE(wChnIndx) ? m_atAudBasChair[byIndx].m_tEqpRes.m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ))
		{
			if ( emType == CScreenBasRes::VidBasCB_NAck )
			{
				pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
			}
			else
			{
				pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
			}
			return ;
		}
	}

	if( (m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_byEqpID == byEqpID) &&
		( TP_VALID_HANDLE(wChnIndx) ? m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wChnIndx == wChnIndx : TRUE ))
	{
		Inst()->GetDualMgr()->OnStopDualCmdForUmcCnc();
		Inst()->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Dual_BasDisCnnt, Inst()->chairID());
		return ;
	}
	
	return ;
}

void CUmsBas::OnBasAskFrame( CTpMsg *const ptMsg )
{
	CUmsConfInst* pInst = Inst();
	u8	byEqpID;
	TP_SAFE_CAST(byEqpID, ptMsg->GetBody());
	u16 wChnIndex;
	TP_SAFE_CAST(wChnIndex, ptMsg->GetBody()+sizeof(byEqpID));

	BasEqpRetProc(CScreenBasRes::VidBasCB_AskKey, byEqpID, wChnIndex);
	
	return ;
}

BOOL32 CUmsBas::SeeSpeakerAskFrameToBas(u16 wScreenIndx)
{
	CUmsConfInst* pInst = Inst();
	
	if ( wScreenIndx >= TP_MAX_STREAMNUM )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::SeeSpeakerAskFrameToBas. ScreenIndx Invalid! ConfID:%d, ScreenIndx:%d\n", 
														pInst->GetInsID(), wScreenIndx));
		return FALSE;
	}

	MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::SeeSpeakerAskFrameToBas. ConfID:%d, ScreenIndx:%d\n", pInst->GetInsID(), wScreenIndx));
	
	CTpMsg cMsg;

#ifdef _USE_XMPUEQP_
	cMsg.SetEvent(evUms_XmpuAskBasKey_Req);
    TTPBasAskFrame tAskInfo;
    tAskInfo.m_byEqpID = (u8)m_cSpeaker.m_atXmpuBas[wScreenIndx].m_dwEqpID;
	cMsg.SetBody(&tAskInfo, sizeof(tAskInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

#else 

	cMsg.SetEvent(evtp_UmsBasAskFrame_Req);
	cMsg.SetBody(&m_cSpeaker.m_atBas[wScreenIndx].m_tBasChnInfo.m_wChnIndx, sizeof(u16));
	cMsg.Post(m_cSpeaker.m_atBas[wScreenIndx].m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
#endif


	//尝试帮适配板的前适配请求一次
	if (pInst->GetUmsDiscuss()->IsDiscussModle())
	{
		pInst->GetUmsDiscuss()->AskKeyFrameFromBas(wScreenIndx);
	}
	else
	{
		pInst->AskKeyByScreen(pInst->curSpeakerID(), wScreenIndx, EmAskKeySpeaker);
	}

	return TRUE;
}

BOOL32 CUmsBas::SeeChairAskFrameToBas(u16 wScreenIndx)
{
	CUmsConfInst* pInst = Inst();
	
	if ( wScreenIndx >= TP_MAX_STREAMNUM )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::SeeChairAskFrameToBas. ScreenIndx Invalid! ConfID:%d, ScreenIndx:%d\n", 
			pInst->GetInsID(), wScreenIndx));
		return FALSE;
	}
#ifdef _USE_XMPUEQP_
	if ( !m_cChair.m_atXmpuBas[wScreenIndx].m_dwEqpID )
#else
	if ( !m_cChair.m_atBas[wScreenIndx].IsValid() )
#endif
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::SeeChairAskFrameToBas. ScreenIndx  bas Invalid! ConfID:%d, ScreenIndx:%d\n", 
			      pInst->GetInsID(), wScreenIndx));
		return TRUE;
	}

	MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::SeeChairAskFrameToBas. ConfID:%d, ScreenIndx:%d\n", pInst->GetInsID(), wScreenIndx));
	
	CTpMsg cMsg;

#ifdef _USE_XMPUEQP_
	cMsg.SetEvent(evUms_XmpuAskBasKey_Req);
    TTPBasAskFrame tAskInfo;
    tAskInfo.m_byEqpID = (u8)m_cChair.m_atXmpuBas[wScreenIndx].m_dwEqpID;
	cMsg.SetBody(&tAskInfo, sizeof(tAskInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
#else 
	cMsg.SetEvent(evtp_UmsBasAskFrame_Req);
	cMsg.SetBody(&m_cChair.m_atBas[wScreenIndx].m_tBasChnInfo.m_wChnIndx, sizeof(u16));
	cMsg.Post(m_cChair.m_atBas[wScreenIndx].m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
#endif

	return TRUE;
}


BOOL32 CUmsBas::SeeDualAskFrameToBas()
{
	CUmsConfInst* pInst = Inst();
	MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::DualAskFrameToBas. ConfID:%d\n", pInst->GetInsID()));
	CTpMsg cMsg;

#ifdef _USE_XMPUEQP_
	cMsg.SetEvent(evUms_XmpuAskBasKey_Req);
    TTPBasAskFrame tAskInfo;
    tAskInfo.m_byEqpID = (u8)m_cDual.m_tXmpuBas.m_dwEqpID;
	cMsg.SetBody(&tAskInfo, sizeof(tAskInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
#else
	cMsg.SetEvent(evtp_UmsBasAskFrame_Req);
	cMsg.SetBody(&m_cDual.m_tBas.m_tBasChnInfo.m_wChnIndx, sizeof(u16));
	cMsg.Post(m_cDual.m_tBas.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
#endif
	
	return TRUE;
}

void CUmsBas::AskFrameToScreenBas( CScreenBasRes* ptScreenBasRes )
{
	CUmsConfInst* pInst = Inst();
	if ( NULL == ptScreenBasRes )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AskFrameToScreenBas. ptScreenBasRes is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
	//查找该适配资源是否存在
	u16 wIndx = m_tConfBasMgr.FindBasChnResByIndx(ptScreenBasRes);
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::AskFrameToScreenBas. BasEqpRes no Exist! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->GetBasEqpId(), 
			ptScreenBasRes->GetBasChnIndex(), ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}
	
	//适配资源是否有效
	if ( !ptScreenBasRes->IsBasValid() )
	{
		MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::AskFrameToScreenBas. BasEqpRes Invalid! ConfID:%d, EqpID:%d, ChnIndx:%d, SrcEp:%d, SrcScreenIndx:%d\n", 
			pInst->GetInsID(), ptScreenBasRes->GetBasEqpId(), 
			ptScreenBasRes->GetBasChnIndex(), ptScreenBasRes->m_wSrcEp, ptScreenBasRes->m_wSrcScreenIndx));
		return ;
	}

	MdlLowDtl(Ums_Mdl_Call, ("CUmsBas::AskFrameToScreenBas. ConfID:%d, ChnIndex:%d\n", 
										pInst->GetInsID(), ptScreenBasRes->GetBasChnIndex()));

	CTpMsg cMsg;
#ifdef _USE_XMPUEQP_
	cMsg.SetEvent(evUms_XmpuAskBasKey_Req);
    TTPBasAskFrame tAskInfo;
    tAskInfo.m_byEqpID = (u8)ptScreenBasRes->m_tXmpuBas.m_dwEqpID;
	cMsg.SetBody(&tAskInfo, sizeof(tAskInfo));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
#else 	
	cMsg.SetEvent(evtp_UmsBasAskFrame_Req);
	cMsg.SetBody(&ptScreenBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, sizeof(u16));
	cMsg.Post(ptScreenBasRes->m_tBasEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
#endif
	return ;
}

//////////////////////////////////////////////////////////////////////////
//下面为取得各种业务的 相关地址

//取得前适配 rtp为外设的ip和接收端口  backrtcp为ums的ip和重传接收端口
//取得后适配 rtp为ums的ip和接收端口 backrtcp为外设的ip和重传接收端口

void CUmsBas::GetInChnSpeakerVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx )
{
	CUmsConfInst* pInst = Inst();

	if ( wSrceenIndx < TP_MAX_STREAMNUM )
	{

#ifdef _USE_XMPUEQP_
        tXmpuVidBasRes* ptBasRes = &m_cSpeaker.m_atXmpuBas[wSrceenIndx];
		tAddr.m_tRtpAddr      = ptBasRes->m_tDecMiddleRtpAddr;
		tAddr.m_tBackRtcpAddr = ptBasRes->m_tDecRtcpAddr;

#else
		TBasEqpRes* ptBasRes = &m_cSpeaker.m_atBas[wSrceenIndx];
		tAddr.m_tRtpAddr.SetAddr(ptBasRes->m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wEqpStartPort);
		tAddr.m_tBackRtcpAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wEqpStartPort + 1);
#endif
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetInChnSpeakerVidAddr. ScreenIndx Invalid ! ConfID:%d, ScreenIndx:%d\n", 
											pInst->GetInsID(), wSrceenIndx));
	}

	return ;
}

void CUmsBas::GetOutChnSpeakerVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx , TUmsVidFormat& tVidFormat )
{
	CUmsConfInst* pInst = Inst();

	if ( wSrceenIndx < TP_MAX_STREAMNUM )
	{

		u16 wIndx = TP_INVALID_INDEX;

		if (m_cSpeaker.IsExInfo(wSrceenIndx))
		{
			wIndx = CTpTypeAdpt::GetRcvFormat( tVidFormat, m_cSpeaker.m_tRealVidParaEx.m_atVidParam,
																	m_cSpeaker.m_tRealVidParaEx.m_byParamNum);
		}
		else
		{
			wIndx = CTpTypeAdpt::GetRcvFormat( tVidFormat, m_cSpeaker.m_tRealVidPara.m_atVidParam,
																	m_cSpeaker.m_tRealVidPara.m_byParamNum);
		}
		
		if ( !TP_VALID_HANDLE(wIndx) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::GetOutChnSpeakerVidAddr. GetRcvFormat Invalid ! ConfID:%d, ScreenIndx:%d, (%s,%s,%s,%d,%d)\n", 
										pInst->GetInsID(), wSrceenIndx,
										UmsVidFormatPrint(tVidFormat.m_emFormat), 
										UmsVidProfilePrint(tVidFormat.m_emQualityLvl),UmsVidResPrint(tVidFormat.m_emRes), 
										tVidFormat.m_wFrameRate, tVidFormat.m_wBitrate)
											);
			return ;
		}

#ifdef _USE_XMPUEQP_
        tXmpuVidBasRes* ptBasRes = &m_cSpeaker.m_atXmpuBas[wSrceenIndx];
        tAddr.m_tRtpAddr = ptBasRes->m_atEncRtpAddr[wIndx];
        tAddr.m_tBackRtcpAddr = ptBasRes->m_atEncMiddleRtcpAddr[wIndx];
#else
		TBasEqpRes* ptBasRes = &m_cSpeaker.m_atBas[wSrceenIndx];
		tAddr.m_tRtpAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN);
		tAddr.m_tBackRtcpAddr.SetAddr(ptBasRes->m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN + 1);
#endif

	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetOutChnSpeakerVidAddr. ScreenIndx Invalid ! ConfID:%d, ScreenIndx:%d\n", 
								pInst->GetInsID(), wSrceenIndx));
	}
	
	return ;	
}

void CUmsBas::GetInChnChairVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx )
{
	CUmsConfInst* pInst = Inst();

	if ( wSrceenIndx < TP_MAX_STREAMNUM )
	{
#ifdef _USE_XMPUEQP_
		tXmpuVidBasRes* ptBasRes = &m_cChair.m_atXmpuBas[wSrceenIndx];
		tAddr.m_tRtpAddr = ptBasRes->m_tDecMiddleRtpAddr;
		tAddr.m_tBackRtcpAddr = ptBasRes->m_tDecRtcpAddr;
#else
		TBasEqpRes* ptBasRes = &m_cChair.m_atBas[wSrceenIndx];
		
		tAddr.m_tRtpAddr.SetAddr(ptBasRes->m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wEqpStartPort);
		tAddr.m_tBackRtcpAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wEqpStartPort + 1);
#endif
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetInChnChairVidAddr. ScreenIndx Invalid ! ConfID:%d, ScreenIndx:%d\n", 
									pInst->GetInsID(), wSrceenIndx));
	}
	
	return ;
}

void CUmsBas::GetOutChnChairVidAddr(TTPMediaTransAddr& tAddr, u16 wSrceenIndx )
{
	CUmsConfInst* pInst = Inst();

	if ( wSrceenIndx < TP_MAX_STREAMNUM )
	{
#ifdef _USE_XMPUEQP_
		tXmpuVidBasRes* ptBasRes = &m_cChair.m_atXmpuBas[wSrceenIndx];
		tAddr.m_tRtpAddr = ptBasRes->m_atEncRtpAddr[0];
		tAddr.m_tBackRtcpAddr =  ptBasRes->m_atEncMiddleRtcpAddr[0];
#else
		TBasEqpRes* ptBasRes = &m_cChair.m_atBas[wSrceenIndx];
		
		tAddr.m_tRtpAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wUmsStartPort);
		tAddr.m_tBackRtcpAddr.SetAddr(ptBasRes->m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wUmsStartPort + 1);
#endif
	}
	else
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetOutChnChairVidAddr. ScreenIndx Invalid ! ConfID:%d, ScreenIndx:%d\n", 
									pInst->GetInsID(), wSrceenIndx));
	}
	
	return ;
}


void CUmsBas::GetInDualVidAddr(TTPMediaTransAddr& tAddr)
{
	CUmsConfInst* pInst = Inst();

#ifdef _USE_XMPUEQP_
	tXmpuVidBasRes* ptBasRes = &m_cDual.m_tXmpuBas;	
	tAddr.m_tRtpAddr = ptBasRes->m_tDecMiddleRtpAddr;
	tAddr.m_tBackRtcpAddr = ptBasRes->m_tDecRtcpAddr;
#else
	TBasEqpRes* ptBasRes = &m_cDual.m_tBas;
	
	tAddr.m_tRtpAddr.SetAddr(ptBasRes->m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wEqpStartPort);
	tAddr.m_tBackRtcpAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wEqpStartPort + 1);
#endif	
	return ;
}

void CUmsBas::GetOutDualVidAddr(TTPMediaTransAddr& tAddr, TUmsVidFormat& tVidFormat )
{
	CUmsConfInst* pInst = Inst();

	u16 wIndx = CTpTypeAdpt::GetRcvFormat( tVidFormat, m_cDual.m_tRealVidPara.m_atVidParam,
																m_cDual.m_tRealVidPara.m_byParamNum);
	
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetOutDualVidAddr. GetRcvFormat Invalid ! ConfID:%d, (%s,%s,%s,%d,%d)\n", 
				pInst->GetInsID(), UmsVidFormatPrint(tVidFormat.m_emFormat), 
				UmsVidProfilePrint(tVidFormat.m_emQualityLvl),UmsVidResPrint(tVidFormat.m_emRes), 
				tVidFormat.m_wFrameRate, tVidFormat.m_wBitrate));
		return ;
	}

#ifdef _USE_XMPUEQP_
	tXmpuVidBasRes* ptBasRes = &m_cDual.m_tXmpuBas;
	tAddr.m_tRtpAddr = ptBasRes->m_atEncRtpAddr[wIndx];
	tAddr.m_tBackRtcpAddr =ptBasRes->m_atEncMiddleRtcpAddr[wIndx];

#else
	TBasEqpRes* ptBasRes = &m_cDual.m_tBas;
	
	tAddr.m_tRtpAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN);
	tAddr.m_tBackRtcpAddr.SetAddr(ptBasRes->m_dwEqpIp, ptBasRes->m_tBasChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN + 1);
#endif
	return ;
}


//取得前适配 rtp为外设的ip和接收端口  backrtcp为ums的ip和重传接收端口
void CUmsBas::GetInChnVidAddr(TTPMediaTransAddr& tAddr, CScreenBasRes* ptScreenRes)
{
	if ( ptScreenRes == NULL )
	{
		return ;
	}
	CUmsConfInst* pInst = Inst();
#ifdef _USE_XMPUEQP_
    tAddr.m_tRtpAddr = ptScreenRes->m_tXmpuBas.m_tDecMiddleRtpAddr;
    tAddr.m_tBackRtcpAddr = ptScreenRes->m_tXmpuBas.m_tDecRtcpAddr;
#else
	tAddr.m_tRtpAddr.SetAddr(ptScreenRes->m_tBasEqpRes.m_dwEqpIp, ptScreenRes->m_tBasEqpRes.m_tBasChnInfo.m_wEqpStartPort);
	tAddr.m_tBackRtcpAddr.SetAddr( pInst->m_tEqpConfDs.m_dwEqpIp, ptScreenRes->m_tBasEqpRes.m_tBasChnInfo.m_wEqpStartPort + 1);
#endif
	
	return ;
}

//取得后适配 rtp为ums的ip和接收端口 backrtcp为外设的ip和重传接收端口
void CUmsBas::GetOutChnVidAddr(TTPMediaTransAddr& tAddr, CScreenBasRes* ptScreenRes, TUmsVidFormat& tVidFormat )
{
	CUmsConfInst* pInst = Inst();

	tAddr.Clear();

	if ( ptScreenRes == NULL )
	{
		return ;
	}

	u16 wIndx = 0;
	if ( ptScreenRes->m_byFormatNum > 1 )
	{//一路后适配 则直接取第0路
		wIndx = CTpTypeAdpt::GetRcvFormat( tVidFormat, ptScreenRes->m_tRealVidPara.m_atVidParam, 
																ptScreenRes->m_tRealVidPara.m_byParamNum);
	}
	if ( !TP_VALID_HANDLE(wIndx) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetOutChnVidAddr. GetRcvFormat Invalid !\n"));
		return ;
	}

#ifdef _USE_XMPUEQP_
    tAddr.m_tRtpAddr = 	ptScreenRes->m_tXmpuBas.m_atEncRtpAddr[wIndx];
	tAddr.m_tBackRtcpAddr = ptScreenRes->m_tXmpuBas.m_atEncMiddleRtcpAddr[wIndx];
#else
	tAddr.m_tRtpAddr.SetAddr(pInst->m_tEqpConfDs.m_dwEqpIp, 
								ptScreenRes->m_tBasEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN);
	tAddr.m_tBackRtcpAddr.SetAddr(ptScreenRes->m_tBasEqpRes.m_dwEqpIp, 
								ptScreenRes->m_tBasEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndx*UMS_MCU_PORT_PORTSPAN + 1);
#endif
	
	return ;
}

#define CREATE_BAS_OUT_VID(cObj, wFormatNum) \
cObj.m_tVidPara.m_byParamNum = 0;\
for (u16 wIndx = 0; wIndx < wFormatNum; wIndx ++  )\
{\
	if ( atVideoRes[wIndx].m_emRes == emTPVResEnd )\
	{\
		continue;\
	}\
	memcpy(&cObj.m_tVidPara.m_atVidParam[cObj.m_tVidPara.m_byParamNum ++], &atVideoRes[wIndx], sizeof(TUmsVidFormat));\
}\
if ( CTpTypeAdpt::CalcBasOutChnEncRes((u8)cObj.m_tVidPara.m_byParamNum, cObj.m_tVidPara.m_atVidParam) <= BAS_ENCRES_1000 )\
{\
	cObj.m_emAsgType = TBasParam::em_AssignType_Sel;\
}\
else\
{\
	cObj.m_emAsgType = TBasParam::em_AssignType_Brd;\
}

void CUmsBas::ParseConfTempFirstVidFormat()
{
	CUmsConfInst* pInst = Inst();
		
	TUmsVidFormat atVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	memcpy(&atVideoRes[0], &m_atPriFmt, sizeof(TUmsVidFormat)*m_wPriNum);
	
	XmpuParseConfTempVidFormatAPI(atVideoRes, m_wPriNum, m_cSpeaker.m_wNeedAdjustLvl, m_cSpeaker.m_tNeedAdjustFmt);

	CREATE_BAS_OUT_VID(m_cSpeaker, m_wPriNum);

	return ;
}

void CUmsBas::ParseConfTempSecondVidFormat()
{
	CUmsConfInst* pInst = Inst();

	TUmsVidFormat atVideoRes[TP_CONF_MAX_MINOR_VIDEO_RES_NUM];
	memcpy(&atVideoRes[0], &m_atDualFmt[0], sizeof(TUmsVidFormat)*m_wDualNum);

	//基本思路：小于1 全部出 大于1且相同格式，尽量删除一个，出个小的。

	//UXGA 60   0.93          尽量接收自己，其次接收72060，再次接收WXGA或SXGA
	//WXGA 30 5 0.24 0.04
	//SXGA 30 5 0.32 0.05
	//4CIF 25   0.08
	//XGA 5     0.032

	//最大情况 108060 2 108030 0.5 UXGA60 0.93 WXGA30 0.24 SXGA30 0.32

	//其他HP和BP1080 720等，跟主流类似：超过3，则减掉最高一个格式，让它接收相应的

	XmpuParseConfTempVidFormatAPI(atVideoRes, m_wDualNum, m_cDual.m_wNeedAdjustLvl, m_cDual.m_tNeedAdjustFmt);

	CREATE_BAS_OUT_VID(m_cDual, m_wDualNum);
	
	return ;
}

void CUmsBas::ParseConfTempVidFormatAPI( TUmsVidFormat atVideoRes[], u16 wFormatNum, u16& wAdjustIndx, TUmsVidFormat& tNeedAdjustFmt )
{
	u16 wIndx = 0;

	wAdjustIndx = TP_INVALID_INDEX;
	tNeedAdjustFmt.m_emRes = emTPVResEnd;

	TUmsVidFormat* ptBpTmp = NULL;
	TUmsVidFormat* ptHpTmp = NULL;

	TUmsVidFormat* ptHp108060 = NULL;
	TUmsVidFormat* ptBp108060 = NULL;
	TUmsVidFormat* ptHp108030 = NULL;
	TUmsVidFormat* ptBp108030 = NULL;
	TUmsVidFormat* ptHp72060 = NULL;
	TUmsVidFormat* ptBp72060 = NULL;
	TUmsVidFormat* ptBpUXGA60 = NULL;
	u16 wHpNum = 0;
	u16 wBpNum = 0;
	
	do
	{
		u16 wEncRes = CTpTypeAdpt::CalcBasOutChnEncRes(wFormatNum, atVideoRes);

		if ( wEncRes <= BAS_ENCRES_1000 )
		{
			break;
		}

		for( wIndx = 0; wIndx < wFormatNum; wIndx ++  )
		{
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				ptHp108060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBp108060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_30 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				ptHp108030 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_30 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBp108030 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD720p1280x720 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				ptHp72060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD720p1280x720 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBp72060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVGA1600x1200 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBpUXGA60 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				wBpNum ++;
			}
			if ( atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				wHpNum ++;
			}
		}
		
		if( ptHp108060 )
		{
			ptHpTmp = ptHp108060;
		}
		else if ( ptHp108030 )
		{
			ptHpTmp = ptHp108030;
		}
		else if ( ptHp72060 ) 
		{
			ptHpTmp = ptHp72060;
		}

		if( ptBp108060 )
		{
			ptBpTmp = ptBp108060;
		}
		else if ( ptBpUXGA60 )
		{
			ptBpTmp = ptBpUXGA60;
		}
		else if ( ptBp108030 )
		{
			ptBpTmp = ptBp108030;
		}
		else if ( ptBp72060 )
		{
			ptBpTmp = ptBp72060;
		}
		
		u16 wEncHp = CTpTypeAdpt::CalcBasOutChnEncRes(1, ptHpTmp);
		u16 wEncBp = CTpTypeAdpt::CalcBasOutChnEncRes(1, ptBpTmp);
		
		if( wEncRes < 2900 )//暂定改成小的避免 接近3的时候，mpu崩溃
		{
			if( wEncRes - ( wEncHp > wEncBp ? wEncHp : wEncBp ) > BAS_ENCRES_1000 )
			{//减去最大的 仍然大于1，则全部出
				break;
			}
		}
		
		if ( IsMediaFormatSameLvl(atVideoRes, wFormatNum) )
		{//都是同Lvl的，最大格式不出
			if ( ptBpTmp )
			{
				ptBpTmp->m_emRes = emTPVResEnd;
			}
			else
			{
				ptHpTmp->m_emRes = emTPVResEnd;
			}
			break ;
		}
		
		if ( wHpNum <=1 && wBpNum <=1 )
		{
			u16 wIndexTmp = 0;
			if( wEncHp > wEncBp )
			{//BP
				wIndexTmp = 1;
			}

			wAdjustIndx = 0;

			tNeedAdjustFmt = atVideoRes[wIndexTmp];//分辨率小的，需要动态调整
			atVideoRes[wIndexTmp].m_emRes = emTPVResEnd;

			break;
		}
		else
		{
			if ( wBpNum > 1 && wHpNum > 1 )
			{
				if ( wEncBp >= wEncHp )
				{
					ptBpTmp->m_emRes = emTPVResEnd;
					wAdjustIndx = GetNeedAdjustIndx(atVideoRes, wFormatNum, ptHpTmp);
				}
				else
				{
					ptHpTmp->m_emRes = emTPVResEnd;
					wAdjustIndx = GetNeedAdjustIndx(atVideoRes, wFormatNum, ptBpTmp);
				}	
			}
			else
			{
				if ( wHpNum > 1 )
				{
					if( wEncRes <= BAS_ENCRES_3000 )
					{
						if( wEncRes - wEncHp > BAS_ENCRES_1000 )
						{//减去 仍然大于1，则全部出
							break;
						}
					}

					if( wEncBp > wEncHp )
					{
						tNeedAdjustFmt = *ptHpTmp;
					}
					
					ptHpTmp->m_emRes = emTPVResEnd;
					wAdjustIndx = GetNeedAdjustIndx(atVideoRes, wFormatNum, ptBpTmp);
				}
				else
				{
					if( wEncRes <= BAS_ENCRES_3000 )
					{
						if( wEncRes - wEncBp > BAS_ENCRES_1000 )
						{//减去 仍然大于1，则全部出
							break;
						}
					}

					if( wEncHp > wEncBp )
					{
						tNeedAdjustFmt = *ptBpTmp;
					}

					ptBpTmp->m_emRes = emTPVResEnd;
					wAdjustIndx = GetNeedAdjustIndx(atVideoRes, wFormatNum, ptHpTmp);
				}
			}
		}
		
		if( CTpTypeAdpt::CalcBasOutChnEncRes(wFormatNum, atVideoRes) > BAS_ENCRES_3000)
		{//此时还超过 3 说明同时选择了所有最大格式 
			if ( ptBpUXGA60 )
			{//此时只能删除UXGA60 让它自行选择合适码流接收 
				ptBpUXGA60->m_emRes = emTPVResEnd;
			}
		}
	}while(0);

	return ;
}

u16 CUmsBas::GetNeedAdjustIndx(TUmsVidFormat m_atVideoRes[], u16 wFormatNum, TUmsVidFormat* ptFormat)
{
	u16 wIndexTmp = 0;
	for (u16 wIndx = 0; wIndx < wFormatNum; wIndx ++ )
	{
		if ( m_atVideoRes[wIndx].m_emRes == emTPVResEnd )
		{
			continue;
		}

		if( ptFormat ==  &m_atVideoRes[wIndx] )
		{
			return wIndexTmp;
		}

		wIndexTmp ++;
	}
	return TP_INVALID_INDEX;
}

void CUmsBas::CalcBasSpeakerOutVidParam(const TUmsVidFormat& tSndVidFormat)
{
	memcpy(&m_cSpeaker.m_tSndVidFormat, &tSndVidFormat, sizeof(TUmsVidFormat));
	CalcBasVidParamAPI(FALSE, tSndVidFormat, m_cSpeaker.m_tVidPara, 
		m_cSpeaker.m_tRealVidPara, m_cSpeaker.m_wNeedAdjustLvl, m_cSpeaker.m_tNeedAdjustFmt);
	return ;
}


void CUmsBas::CalcBasSpeakerOutVidParamEx( const TUmsVidFormat& tSndVidFormat )
{
	memcpy(&m_cSpeaker.m_tSndVidFormatEx, &tSndVidFormat, sizeof(TUmsVidFormat));
	CalcBasVidParamAPI(FALSE, tSndVidFormat, m_cSpeaker.m_tVidPara, 
		m_cSpeaker.m_tRealVidParaEx, m_cSpeaker.m_wNeedAdjustLvl, m_cSpeaker.m_tNeedAdjustFmt);
	return;
}

void CUmsBas::CalcBasDualOutVidParam( const TUmsVidFormat& tSndVidFormat )
{
	CalcBasVidParamAPI(TRUE, tSndVidFormat, m_cDual.m_tVidPara, 
		m_cDual.m_tRealVidPara, m_cDual.m_wNeedAdjustLvl, m_cDual.m_tNeedAdjustFmt);
	return ;	
}

void CUmsBas::CalcBasVidParamAPI(BOOL32 bDual, const TUmsVidFormat& tSndVidFormat, 
								 TTPBasVidParam& tVidParam, TTPBasVidParam& tRealVidParam, u16 wAdjustIndx, TUmsVidFormat& tNeedAdjustFmt)
{
	CUmsConfInst* pInst = Inst();
	
	BOOL32 b5025 = FALSE;
	
	if ( tSndVidFormat.m_wFrameRate == VID_FRAME_RATE_25 || tSndVidFormat.m_wFrameRate == VID_FRAME_RATE_50 )
	{
		b5025 = TRUE;
	}
	
	u8 byIndx = 0;

	memcpy(&tRealVidParam, &tVidParam, sizeof(TTPBasVidParam));
	
	u16 wResH = 0;
	u16 wResW = 0;

	CTpTypeAdpt::GetWHByVidResolution(tSndVidFormat.m_emRes, wResW, wResH);

	u32 dwSendPower = wResH*wResW*tSndVidFormat.m_wFrameRate;

	for ( byIndx = 0; byIndx < tVidParam.m_byParamNum; byIndx ++ )
	{
		if ( !tSndVidFormat.IsValid() )
		{//如果进适配的格式无效，则后适配不出
			tRealVidParam.m_atVidParam[byIndx].m_wBitrate = 0;
			continue;
		}

		if ( tSndVidFormat.m_emRes == emTPVResolutionAuto )
		{//防止发给mpu2的长宽为0
			continue;
		}

		CTpTypeAdpt::GetWHByVidResolution(tVidParam.m_atVidParam[byIndx].m_emRes, wResW, wResH);
		//低能力发往高能力 直接过   能力=分辨率的长*宽*帧率
		//能力高的向能力低的适配  分辨率 、帧率都取低的
		if( dwSendPower <= wResW*wResH*tVidParam.m_atVidParam[byIndx].m_wFrameRate )
		{
			tRealVidParam.m_atVidParam[byIndx].m_emRes = tSndVidFormat.m_emRes;
			tRealVidParam.m_atVidParam[byIndx].m_wFrameRate = tSndVidFormat.m_wFrameRate;
		}
		else
		{
			if ( CTpTypeAdpt::ResolutionSmallOpr(tSndVidFormat.m_emRes, tVidParam.m_atVidParam[byIndx].m_emRes) )
			{
				tRealVidParam.m_atVidParam[byIndx].m_emRes = tSndVidFormat.m_emRes;
			}
			if ( tSndVidFormat.m_wFrameRate < tVidParam.m_atVidParam[byIndx].m_wFrameRate )
			{
				tRealVidParam.m_atVidParam[byIndx].m_wFrameRate = tSndVidFormat.m_wFrameRate;
			}
		}
		
		
		if( b5025 )
		{// 25 或 50 不能出30或60等
			if ( tRealVidParam.m_atVidParam[byIndx].m_wFrameRate == VID_FRAME_RATE_60 )
			{
				tRealVidParam.m_atVidParam[byIndx].m_wFrameRate = VID_FRAME_RATE_50;
			}
			else if ( tRealVidParam.m_atVidParam[byIndx].m_wFrameRate == VID_FRAME_RATE_30 )
			{
				tRealVidParam.m_atVidParam[byIndx].m_wFrameRate = VID_FRAME_RATE_25;
			}
		}
		
		if(wAdjustIndx == byIndx)
		{
			if(tSndVidFormat.m_emQualityLvl == emTPH264HP)
			{
				tRealVidParam.m_atVidParam[byIndx].m_emQualityLvl = emTPH264BP;
				tVidParam.m_atVidParam[byIndx].m_emQualityLvl = emTPH264BP;
				if( bDual )
				{
					tVidParam.m_atVidParam[byIndx].m_wBitrate = pInst->GetConfBase().m_wBpDualBitRate;
				}
				else
				{
					tVidParam.m_atVidParam[byIndx].m_wBitrate = pInst->GetConfBase().m_wBpConfBitRate;
				}
			}
			else
			{
				tRealVidParam.m_atVidParam[byIndx].m_emQualityLvl = emTPH264HP;
				tVidParam.m_atVidParam[byIndx].m_emQualityLvl = emTPH264HP;
				if( bDual )
				{
					tVidParam.m_atVidParam[byIndx].m_wBitrate = pInst->GetConfBase().m_wHpDualBitRate;
				}
				else
				{
					tVidParam.m_atVidParam[byIndx].m_wBitrate = pInst->GetConfBase().m_wConfBitRate;
				}
			}

			//根据发言人，调整后适配的帧率和分辨率
			if ( tSndVidFormat.m_emQualityLvl != tNeedAdjustFmt.m_emQualityLvl )
			{
				if ( tNeedAdjustFmt.m_emRes != emTPVResEnd )
				{
					tRealVidParam.m_atVidParam[byIndx].m_emRes = tNeedAdjustFmt.m_emRes;
					tRealVidParam.m_atVidParam[byIndx].m_wFrameRate = tNeedAdjustFmt.m_wFrameRate;
				}
			}
		}

		if ( CTpTypeAdpt::CalcBasOutChnEncRes(1, &tRealVidParam.m_atVidParam[byIndx])
			> CTpTypeAdpt::CalcBasOutChnEncRes(1, &tVidParam.m_atVidParam[byIndx]) )
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::Diaolei VICP OUT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"));
			MdlError(Ums_Mdl_Call, ("CUmsBas::Diaolei VICP OUTSnd(%s, %s, %d ), RealVid(%s, %s, %d), wIndex:%d\n", 
				UmsVidProfilePrint(tSndVidFormat.m_emQualityLvl),
				UmsVidResPrint(tSndVidFormat.m_emRes), tSndVidFormat.m_wFrameRate,
				UmsVidProfilePrint(tRealVidParam.m_atVidParam[byIndx].m_emQualityLvl),
				UmsVidResPrint(tRealVidParam.m_atVidParam[byIndx].m_emRes), tRealVidParam.m_atVidParam[byIndx].m_wFrameRate, byIndx));
		}
	}
	return ;
}

BOOL32 CUmsBas::IsMediaFormatSameLvl(TUmsVidFormat atVidFormat[], u16 wNum)
{
	CUmsConfInst* pInst = Inst();
	BOOL32 bHp = FALSE;
	BOOL32 bBp = FALSE;
	for (u16 wIndx = 0; wIndx < wNum; wIndx ++ )
	{
		if( atVidFormat[wIndx].m_emQualityLvl == emTPH264BP )
		{
			bBp = TRUE;
		}
		if( atVidFormat[wIndx].m_emQualityLvl == emTPH264HP )
		{
			bHp = TRUE;
		}
	}

	if ( bBp && bHp )
	{
		//hp bp都存在 则格式不同
		return FALSE;
	}

	return TRUE;
}

void CUmsBas::ChairChanConnect()
{//主席上线后，判断是否需要 发言人看主席适配资源
	CUmsConfInst* pInst = Inst();

	if ( !pInst->IsPriNeedBas() )
	{
		return ;
	}

	TCapNode* ptChair = pInst->GetNodeMgr()->GetForeFatherNode(pInst->chairID());
	if ( NULL == ptChair || !ptChair->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetSelBas. ptChair is NULL! ConfID:%d\n", pInst->GetInsID()));
		return ;
	}
	
	BOOL32 bNeed = FALSE;
	u16 wIndex = 0;

//音频
	if ( ptChair->IsSingleAudSnd() )
	{//主席单屏 需要释放两边
		TAudBasParam tBasParam;
		
		for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if ( wIndex == MIDSCREENINDEX )
			{
				continue;
			}

			if(m_atAudBasChair[wIndex].IsBasValid())
			{
                RealseAudBasByScreen(&m_atAudBasChair[wIndex]);
			}

		}
	}

	for ( wIndex = 0; wIndex < pInst->m_tConfBaseInfo.m_wMainNum; wIndex ++ )
	{
		if(CTpTypeAdpt::IsVidTransNeedBas( pInst->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex], ptChair->m_tVidRcvFormat.m_tFormat))
		{//有需要适配的
			bNeed = TRUE;
			break;
		}
	}

	if ( !m_tConfBasMgr.m_bChair )
	{
		return;
	}

	bNeed = FALSE;
	for ( wIndex = 0; wIndex < pInst->m_tConfBaseInfo.m_wMainNum; wIndex ++ )
	{
		if(CTpTypeAdpt::IsVidTransNeedBas( ptChair->m_tVidSndFormat.m_tFormat, pInst->m_tConfBaseInfo.m_atTpMainVideoRes[wIndex]))
		{//有需要适配的
			bNeed = TRUE;
			break;
		}
	}

	if ( !bNeed || !ptChair->IsVidSndValid() )
	{//不需要 则释放该资源
		ReleaseChairBas();
	}
	else
	{//需要
		if ( ptChair->m_wVidSndNum == 1 )
		{//单屏需要释放两边的
			 for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
			 {
				 if ( wIndex == MIDSCREENINDEX )
				 {
					 continue;
				 }
#ifdef _USE_XMPUEQP_
				 ReleaseXmpuBas(1, &m_cChair.m_atXmpuBas[wIndex]);
#else
				 ReleaseBas(1, &m_cChair.m_atBas[wIndex]);
#endif
			 }
		}
	}

	if ( pInst->IsChairConf() )
	{//发言人看主席 主席进适配板
		AdjustChairBas();
		CNetPortMgr::CreateVirChairToBas(pInst);
	}

	CNetPortMgr::AdjustBasDsEqpToConfDsEqp(pInst);

	return ;
}

void CUmsBas::ReleaseChairBas()
{
	if ( !m_tConfBasMgr.m_bChair )
	{
		return ;
	}

#ifdef _USE_XMPUEQP_
	ReleaseXmpuBas(TP_MAX_STREAMNUM, m_cChair.m_atXmpuBas);
#else
	ReleaseBas(TP_MAX_STREAMNUM, m_cChair.m_atBas);
#endif

	m_tConfBasMgr.m_bChair = FALSE;

	return ;
}

void CUmsBas::ReleaseSpeakerBas()
{
	if ( !m_tConfBasMgr.m_bSpeaker )
	{
		return ;
	}

#ifdef _USE_XMPUEQP_
	ReleaseXmpuBas(TP_MAX_STREAMNUM, m_cSpeaker.m_atXmpuBas);
#else
	ReleaseBas(TP_MAX_STREAMNUM, m_cSpeaker.m_atBas);
#endif

}

void CUmsBas::AdjustMediaTransBasToNode()
{
	CUmsConfInst* pInst = Inst();
	
	for (TCapNode* ptNode = pInst->m_pcNodeMgr->FirstNode(); ptNode != NULL; ptNode = pInst->m_pcNodeMgr->NextLoalNode(ptNode))
	{
		if(!ptNode->IsCallOn() || !ptNode->IsChanOn())
		{
			continue;
		}
		pInst->GetNodeFsm()->UpdateMediaTrans(ptNode);
	}
	
	return ;
}

//定时向适配板请求关键帧（主要用于轮询情况）
void CUmsBas::OnAskFrameTime( )
{
	CUmsConfInst* pInst = Inst();
	CScreenBasRes* ptBasRes = NULL;

	BOOL32 bAsk = FALSE;
	for( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		ptBasRes = &m_tConfBasMgr.m_atBasChsRes[wIndex];
		if ( !ptBasRes->IsBasValid() )
		{
			continue;
		}
		
		CTpMsg cMsg;
		cMsg.SetEvent(evtp_UmsBasAskFrame_Req);
		cMsg.SetBody(&ptBasRes->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx, sizeof(u16));
		cMsg.Post(ptBasRes->m_tBasEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, pInst->GetInsID()));
		
		if ( ptBasRes->m_wAskFrameNum > 0 )
		{
			ptBasRes->m_wAskFrameNum --;

			bAsk = TRUE;
		}
	}

	if( bAsk )
	{
		pInst->SetTimer(evtp_AskFrameToBas_time, ASKFRAME_TOBAS_TIME_200MS);
	}

	return ;
}

//函数功能：
//将格式按大到小排序，防止mpu2崩溃
u16 CUmsBas::CheckAndProcConfTempFormat( TUmsVidFormat atVidFormat[], u16 wNum )
{
	u16				wIndx = 0;
	TUmsVidFormat	atTmpVidFormat[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	
	memcpy(atTmpVidFormat, atVidFormat, sizeof(TUmsVidFormat)*wNum);
	memset(atVidFormat, 0, sizeof(TUmsVidFormat)*wNum);
	
	u16 wEnc = 0;
	u16 awEnc[TP_CONF_MAX_MAIN_VIDEO_RES_NUM] = {TP_INVALID_INDEX};
	
	for ( wIndx = 0; wIndx < wNum; wIndx ++ )
	{
		if(atTmpVidFormat[wIndx].m_emRes == emTPVResEnd)
		{
			continue;
		}
		
		awEnc[wIndx] = CTpTypeAdpt::CalcBasOutChnEncRes(1, &atTmpVidFormat[wIndx]);
	}
	
	u16 wMaxIndx = TP_INVALID_INDEX;
	for ( wIndx = 0; wIndx < wNum; wIndx ++ )
	{
		wMaxIndx = TP_INVALID_INDEX;
		for ( u16 wFmt = 0; wFmt < wNum; wFmt ++ )
		{
			if ( awEnc[wFmt] == TP_INVALID_INDEX )
			{
				continue;
			}
			
			if( wMaxIndx == TP_INVALID_INDEX )
			{
				wMaxIndx = wFmt;
			}
			
			if ( awEnc[wMaxIndx] < awEnc[wFmt] )
			{
				wMaxIndx = wFmt;
			}
		}
		
		awEnc[wMaxIndx] = TP_INVALID_INDEX;
		memcpy(&atVidFormat[wIndx], &atTmpVidFormat[wMaxIndx], sizeof(TUmsVidFormat));
	}
	
	return wNum;
}

void CUmsBas::OnBasTestShow( CTpMsg *const ptMsg )
{
	if ( Inst()->CurState() == CUmsConfInst::inst_run )
	{
		msgprintnotime("BasTest. Inst is running!\n");
		return ;
	}
	u16 wIndxPrs, wIndxDual;
	BOOL32 bCreate;
	TP_SAFE_CAST(wIndxPrs, ptMsg->GetBody());
	TP_SAFE_CAST(wIndxDual, ptMsg->GetBody() + sizeof(u16));
	TP_SAFE_CAST(bCreate, ptMsg->GetBody() + 2*sizeof(u16));

	//所有主流格式：
	TUmsVidFormat aPrs[17];
	u16 wPrsIndx = 0;
	u16 wIndx = 0;
	EmTpVideoQualityLevel emTmp = emTPH264HP;
	u16 wBitRate = CONF_HP_BITRATE;
	for( wIndx = 0; wIndx < 2; wIndx ++ )
	{
		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD1080p1920x1080;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 60;
		wPrsIndx++;

		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD1080p1920x1080;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 50;
		wPrsIndx++;

		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD1080p1920x1080;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 30;
		wPrsIndx++;

		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD1080p1920x1080;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 25;
		wPrsIndx++;

		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD720p1280x720;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 60;
		wPrsIndx++;

		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD720p1280x720;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 50;
		wPrsIndx++;

		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD720p1280x720;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 30;
		wPrsIndx++;

		aPrs[wPrsIndx].m_emQualityLvl = emTmp;
		aPrs[wPrsIndx].m_emRes = emTPVHD720p1280x720;
		aPrs[wPrsIndx].m_wBitrate = wBitRate;
		aPrs[wPrsIndx].m_wFrameRate = 25;
		wPrsIndx++;

		emTmp = emTPH264BP;
		wBitRate = CONF_BP_BITRATE;
	}

	aPrs[wPrsIndx].m_emQualityLvl = emTPH264BP;
	aPrs[wPrsIndx].m_emRes = emTPV4CIF;
	aPrs[wPrsIndx].m_wBitrate = wBitRate;
	aPrs[wPrsIndx].m_wFrameRate = 25;
	wPrsIndx++;

	//所有双流格式：
	TUmsVidFormat aDual[23];
	memcpy(aDual, aPrs, sizeof(aPrs));
	aDual[wPrsIndx].m_emQualityLvl = emTPH264BP;
	aDual[wPrsIndx].m_emRes = emTPVGA1600x1200;
	aDual[wPrsIndx].m_wBitrate = wBitRate;
	aDual[wPrsIndx].m_wFrameRate = 60;
	wPrsIndx++;
	aDual[wPrsIndx].m_emQualityLvl = emTPH264BP;
	aDual[wPrsIndx].m_emRes = emTPVGA1366x768;
	aDual[wPrsIndx].m_wBitrate = wBitRate;
	aDual[wPrsIndx].m_wFrameRate = 30;
	wPrsIndx++;
	aDual[wPrsIndx].m_emQualityLvl = emTPH264BP;
	aDual[wPrsIndx].m_emRes = emTPVGA1366x768;
	aDual[wPrsIndx].m_wBitrate = wBitRate;
	aDual[wPrsIndx].m_wFrameRate = 5;
	wPrsIndx++;
	aDual[wPrsIndx].m_emQualityLvl = emTPH264BP;
	aDual[wPrsIndx].m_emRes = emTPVGA1280x1024;
	aDual[wPrsIndx].m_wBitrate = wBitRate;
	aDual[wPrsIndx].m_wFrameRate = 30;
	wPrsIndx++;
	aDual[wPrsIndx].m_emQualityLvl = emTPH264BP;
	aDual[wPrsIndx].m_emRes = emTPVGA1280x1024;
	aDual[wPrsIndx].m_wBitrate = wBitRate;
	aDual[wPrsIndx].m_wFrameRate = 5;
	wPrsIndx++;
	aDual[wPrsIndx].m_emQualityLvl = emTPH264BP;
	aDual[wPrsIndx].m_emRes = emTPVGA1024x768;
	aDual[wPrsIndx].m_wBitrate = wBitRate;
	aDual[wPrsIndx].m_wFrameRate = 5;
	wPrsIndx++;

	if( bCreate )
	{
		do
		{
		srand(time(NULL));
		//随机构造主流和双流模板配置
		u16 awIndx[23] = { 0 };
		u16 wFmtIndx = 0;
		u16 wIndxTmp = 0;
		u16 wIndxSort = 0;
		u16 wFmtNum = rand()%TP_CONF_MAX_MAIN_VIDEO_RES_NUM +1;
		if ( wFmtNum <= 1 )
		{
			continue;
		}
		
		//产生随机数
		for( wIndx = 0; wIndx < wFmtNum; wIndx ++ )
		{
			awIndx[wIndx] = rand()%17;
		}

		//排序
		for( wIndx = 0; wIndx < wFmtNum; wIndx ++ )
		{
			wIndxTmp = awIndx[wIndx];

			for ( wIndxSort = wIndx + 1; wIndxSort < wFmtNum; wIndxSort ++ )
			{
				if ( wIndxTmp > awIndx[wIndxSort] )
				{
					awIndx[wIndx] = awIndx[wIndxSort];
					awIndx[wIndxSort] = wIndxTmp;
					wIndxTmp = awIndx[wIndx];
				}
			}
		}


		TUmsVidFormat t;
		t.m_emQualityLvl = emTPH264HP;
		t.m_emRes = emTPVHD1080p1920x1080;
		t.m_wBitrate = 2048;
		t.m_wFrameRate = 60;

		TUmsVidFormat t1;
		t1.m_emQualityLvl = emTPH264HP;
		t1.m_emRes = emTPVHD720p1280x720;
		t1.m_wBitrate = 2048;
		t1.m_wFrameRate = 60;

		memcpy(&(Inst()->GetConfBase().m_atTpMainVideoRes[0]), &t, sizeof(TUmsVidFormat));
		t.m_wFrameRate = 30;
		memcpy(&(Inst()->GetConfBase().m_atTpMainVideoRes[1]), &t, sizeof(TUmsVidFormat));

		memcpy(&(Inst()->GetConfBase().m_atTpMainVideoRes[2]), &t1, sizeof(TUmsVidFormat));

		t.m_emQualityLvl = emTPH264BP;
		t.m_wFrameRate = 30;
		memcpy(&(Inst()->GetConfBase().m_atTpMainVideoRes[3]), &t, sizeof(TUmsVidFormat));

		t1.m_emQualityLvl = emTPH264BP;
		memcpy(&(Inst()->GetConfBase().m_atTpMainVideoRes[4]), &t1, sizeof(TUmsVidFormat));

		t1.m_emRes = emTPV4CIF;
		t1.m_wBitrate = 2048;
		t1.m_wFrameRate = 30;

		memcpy(&(Inst()->GetConfBase().m_atTpMainVideoRes[5]), &t1, sizeof(TUmsVidFormat));

		Inst()->GetConfBase().m_wMainNum = 6;
		
		//////////////////////////////////////////////////////////////////////////
		//双流
		wFmtNum = rand()%TP_CONF_MAX_MINOR_VIDEO_RES_NUM +1;
		if ( wFmtNum <= 1 )
		{
			continue;
		}
		
		memset(awIndx, 0, sizeof(awIndx));
		//产生随机数
		for( wIndx = 0; wIndx < wFmtNum; wIndx ++ )
		{
			awIndx[wIndx] = rand()%23;
		}

		//排序
		for( wIndx = 0; wIndx < wFmtNum; wIndx ++ )
		{
			wIndxTmp = awIndx[wIndx];
			
			for ( wIndxSort = wIndx + 1; wIndxSort < wFmtNum; wIndxSort ++ )
			{
				if ( wIndxTmp > awIndx[wIndxSort] )
				{
					awIndx[wIndx] = awIndx[wIndxSort];
					awIndx[wIndxSort] = wIndxTmp;
					wIndxTmp = awIndx[wIndx];
				}
			}
		}

		TUmsVidFormat tDual;
		tDual.m_emQualityLvl = emTPH264HP;
		tDual.m_emRes = emTPVHD1080p1920x1080;
		tDual.m_wBitrate = 2048;
		tDual.m_wFrameRate = 60;
		memcpy(&(Inst()->GetConfBase().m_atTpMinorVideoRes[0]), &tDual, sizeof(TUmsVidFormat));
		tDual.m_emQualityLvl = emTPH264HP;
		tDual.m_emRes = emTPVHD1080p1920x1080;
		tDual.m_wBitrate = 2048;
		tDual.m_wFrameRate = 30;
		memcpy(&(Inst()->GetConfBase().m_atTpMinorVideoRes[1]), &tDual, sizeof(TUmsVidFormat));
		tDual.m_emQualityLvl = emTPH264BP;
		tDual.m_emRes = emTPVHD1080p1920x1080;
		tDual.m_wBitrate = 2048;
		tDual.m_wFrameRate = 30;
		memcpy(&(Inst()->GetConfBase().m_atTpMinorVideoRes[2]), &tDual, sizeof(TUmsVidFormat));
		tDual.m_emQualityLvl = emTPH264BP;
		tDual.m_emRes = emTPVHD720p1280x720;
		tDual.m_wBitrate = 2048;
		tDual.m_wFrameRate = 60;
		memcpy(&(Inst()->GetConfBase().m_atTpMinorVideoRes[3]), &tDual, sizeof(TUmsVidFormat));
		tDual.m_emQualityLvl = emTPH264BP;
		tDual.m_emRes = emTPV4CIF;
		tDual.m_wBitrate = 2048;
		tDual.m_wFrameRate = 30;
		memcpy(&(Inst()->GetConfBase().m_atTpMinorVideoRes[4]), &tDual, sizeof(TUmsVidFormat));
		tDual.m_emQualityLvl = emTPH264BP;
		tDual.m_emRes = emTPVGA1600x1200;
		tDual.m_wBitrate = 2048;
		tDual.m_wFrameRate = 60;
		memcpy(&(Inst()->GetConfBase().m_atTpMinorVideoRes[5]), &tDual, sizeof(TUmsVidFormat));
		Inst()->GetConfBase().m_wMinorNum = 6;

				
		memset(&m_cSpeaker, 0, sizeof(m_cSpeaker));
		memset(&m_cDual, 0, sizeof(m_cDual));

		//解析模板格式
		m_wPriNum = Inst()->m_tConfBaseInfo.m_wMainNum;
		memcpy(&m_atPriFmt[0], &Inst()->m_tConfBaseInfo.m_atTpMainVideoRes[0], sizeof(TUmsVidFormat)*m_wPriNum);
		m_wDualNum = Inst()->m_tConfBaseInfo.m_wMinorNum;
		memcpy(&m_atDualFmt[0], &Inst()->m_tConfBaseInfo.m_atTpMinorVideoRes[0], sizeof(TUmsVidFormat)*m_wDualNum);
		
		m_wPriNum = CheckAndProcConfTempFormat(m_atPriFmt, m_wPriNum);
		m_wDualNum = CheckAndProcConfTempFormat(m_atDualFmt, m_wDualNum);

		ParseConfTempFirstVidFormat();
		ParseConfTempSecondVidFormat();

		msgprintnotime("BasTest CreateBasFormat Success!! MainNum:%d, MinorNum:%d\n", 
							Inst()->GetConfBase().m_wMainNum , Inst()->GetConfBase().m_wMinorNum);

		break;
		}while(1);

		return ;
	}

	BasShow(wIndxPrs, wIndxDual);

	return ;
}

void CUmsBas::BasShow( u16 wIndxPrs, u16 wIndxDual )
{
	CalcBasSpeakerOutVidParam(Inst()->GetConfBase().m_atTpMainVideoRes[wIndxPrs]);
	CalcBasDualOutVidParam(Inst()->GetConfBase().m_atTpMinorVideoRes[wIndxDual]);
	
	TUmsVidFormat tDualTmp;
	memcpy(&tDualTmp, &m_cDual.m_tEpFormat, sizeof(TUmsVidFormat));
	memcpy(&m_cDual.m_tEpFormat, &Inst()->GetConfBase().m_atTpMinorVideoRes[wIndxDual], sizeof(TUmsVidFormat));
	
	BOOL32 bDual = m_tConfBasMgr.m_bDual;
	m_tConfBasMgr.m_bDual = TRUE;
	msgprintnotime("BasTest PrsIndx:%d, DualIndx:%d\n", wIndxPrs, wIndxDual);
	Show();
	m_tConfBasMgr.m_bDual = bDual;
	
	TUmsVidFormat* ptVidFormateSnd = NULL;
	TUmsVidFormat* ptVidFormateRcv = NULL;
	BOOL32 bBas = TRUE;
	
	msgprintnotime("-------------PrsVid--------------\n");
	TUmsVidFormat* ptVidFormate = &m_cSpeaker.m_tSndVidFormat;
	msgprintnotime("	SpeakerForamt:%s, %s, %s, FrameRate:%d, BitRate:%d\n", 
		UmsVidFormatPrint(ptVidFormate->m_emFormat),
		UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
		UmsVidResPrint( ptVidFormate->m_emRes),
				ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate);
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < Inst()->GetConfBase().m_wMainNum; wIndex ++ )
	{
		ptVidFormateRcv = NULL;
		ptVidFormateSnd = &Inst()->GetConfBase().m_atTpMainVideoRes[wIndex];
		
		bBas = IsSpeakerNeedBas(Inst()->GetConfBase().m_atTpMainVideoRes[wIndex]);
		if( bBas )
		{
			ptVidFormateRcv = 
				&m_cSpeaker.m_tRealVidPara.m_atVidParam[CTpTypeAdpt::GetRcvFormat( Inst()->GetConfBase().m_atTpMainVideoRes[wIndex], 
				m_cSpeaker.m_tRealVidPara.m_atVidParam,
				m_cSpeaker.m_tRealVidPara.m_byParamNum)];
		}
		else
		{
			ptVidFormateRcv = &m_cSpeaker.m_tSndVidFormat;
		}
		msgprintnotime("%s, %s, %s, %d -- Real %s, %s, %s, %d, needBas:%d\n",
			UmsVidFormatPrint(ptVidFormateSnd->m_emFormat),
			UmsVidProfilePrint(ptVidFormateSnd->m_emQualityLvl),
			UmsVidResPrint( ptVidFormateSnd->m_emRes),
			ptVidFormateSnd->m_wFrameRate, 
			
			UmsVidFormatPrint(ptVidFormateRcv->m_emFormat),
			UmsVidProfilePrint(ptVidFormateRcv->m_emQualityLvl),
			UmsVidResPrint( ptVidFormateRcv->m_emRes),
			ptVidFormateRcv->m_wFrameRate, bBas
			);
	}
	
	msgprintnotime("-------------DualVid--------------\n");
	ptVidFormate = &m_cDual.m_tEpFormat;
	msgprintnotime("	DualForamt:%s, %s, %s, FrameRate:%d, BitRate:%d\n", 
		UmsVidFormatPrint(ptVidFormate->m_emFormat),
		UmsVidProfilePrint(ptVidFormate->m_emQualityLvl),
		UmsVidResPrint( ptVidFormate->m_emRes),
				ptVidFormate->m_wFrameRate, ptVidFormate->m_wBitrate);
	u16 wDDDDD = 0;
	for ( wIndex = 0; wIndex < Inst()->GetConfBase().m_wMinorNum; wIndex ++ )
	{
		ptVidFormateRcv = NULL;
		ptVidFormateSnd = &Inst()->GetConfBase().m_atTpMinorVideoRes[wIndex];
		
		bBas = IsDualNeedBas(Inst()->GetConfBase().m_atTpMinorVideoRes[wIndex]);
		if( bBas )
		{
			wDDDDD = CTpTypeAdpt::GetRcvFormat( Inst()->GetConfBase().m_atTpMinorVideoRes[wIndex], 
				m_cDual.m_tRealVidPara.m_atVidParam,
				m_cDual.m_tRealVidPara.m_byParamNum);
			ptVidFormateRcv = 
				&m_cDual.m_tRealVidPara.m_atVidParam[wDDDDD];
		}
		else
		{
			ptVidFormateRcv = &m_cDual.m_tEpFormat;
		}
		msgprintnotime("Ep:%s, %s, %s, %d -- RealRcv: %s, %s, %s, %d, needBas:%d\n",
			UmsVidFormatPrint(ptVidFormateSnd->m_emFormat),
			UmsVidProfilePrint(ptVidFormateSnd->m_emQualityLvl),
			UmsVidResPrint( ptVidFormateSnd->m_emRes),
			ptVidFormateSnd->m_wFrameRate, 
			
			UmsVidFormatPrint(ptVidFormateRcv->m_emFormat),
			UmsVidProfilePrint(ptVidFormateRcv->m_emQualityLvl),
			UmsVidResPrint( ptVidFormateRcv->m_emRes),
			ptVidFormateRcv->m_wFrameRate, bBas
			);
	}
	
	memcpy(&m_cDual.m_tEpFormat, &tDualTmp, sizeof(TUmsVidFormat));
	
	return ;
}



void CUmsBas::AdjustConfBitrateForBas( u16 wConfBitrate )
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < m_wPriNum; wIndex++)
	{
		m_atPriFmt[wIndex].m_wBitrate = wConfBitrate;
	}

	// speaker
	for (wIndex = 0; wIndex < m_cSpeaker.m_tVidPara.m_byParamNum; wIndex++)
	{
		m_cSpeaker.m_tVidPara.m_atVidParam[wIndex].m_wBitrate = wConfBitrate;
	}

}

void CUmsBas::AdjustDualBitrateForBas( u16 wDualBitrate )
{
	u16 wIndex = 0;
	for (wIndex; wIndex < m_wDualNum; wIndex ++)
	{
		m_atDualFmt[wIndex].m_wBitrate = wDualBitrate;
	}

	// dual
	for (wIndex = 0; wIndex < m_cSpeaker.m_tVidPara.m_byParamNum; wIndex++)
	{
		m_cDual.m_tVidPara.m_atVidParam[wIndex].m_wBitrate = wDualBitrate;
	}
}


//////////////////////////////////////////////////////////////////////////
//B4音频适配


void CUmsBas::ReleaseAudBas()
{
	u16 wIndex = 0;
	for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		if(!m_atAudBasSpeaker[wIndex].IsBasValid())
		{
			continue;
		}

		RealseAudBasByScreen(&m_atAudBasSpeaker[wIndex]);
		m_atAudBasSpeaker[wIndex].ClearBas();
	}
	
	if(m_tAudBasSpeakerMix.IsBasValid())
	{
	    RealseAudBasByScreen(&m_tAudBasSpeakerMix);
		m_tAudBasSpeakerMix.ClearBas();
	}
	
	for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		if(!m_atAudBasChair[wIndex].IsBasValid())
		{
			continue;
		}
		
		RealseAudBasByScreen(&m_atAudBasChair[wIndex]);
		m_atAudBasChair[wIndex].ClearBas();
	}

	return ;
}

BOOL32 CUmsBas::IsSpeakerNeedAudBas(EmTpAudioFormat emFmt)
{
	if ( !Inst()->IsAudNeedBas() )
	{
		return FALSE;
	}

	// 音频适配会议，虚拟发言人广播码流都从适配取，不再从虚拟发言人取，避免切换发言会场时，终端收到不一致的音频码流

	return TRUE;
}

#ifdef _USE_XMPUEQP_
void CUmsBas::SetXmpuSpeakerAudBasEncCmd(void)
{
	if (!Inst()->IsAudNeedBas() )
	{
		return;
	}
	
	u16 wEpId = Inst()->curSpeakerID();
	if ((Inst()->GetAudMix()->IsAudMixMode() || Inst()->GetUmsDiscuss()->IsDiscussModle()) && !Inst()->IsChairConf())
	{
		wEpId = Inst()->chairID();
	}
	
	TCapNode* ptCapNode = Inst()->GetNodeMgr()->GetForeFatherNode(wEpId);
	if ( NULL == ptCapNode || !ptCapNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuSpeakerAudBasEncCmd. ptCapNode Invalid! ConfID:%d, Ep:%d\n", 
			Inst()->GetInsID(), wEpId));
		return ;
	}
	
	m_tAudBasSpeakerMix.m_tSndAudFmt = ptCapNode->m_tAudSndFormat.m_tFormat;
	m_tAudBasSpeakerMix.m_tSndAudFmt.m_byReserve1 = ptCapNode->m_tAudSndFormat.m_wDynamicPayload;
	
	TXmpuChgAudParam tBasParam;
	tBasParam.m_tAudDec = ptCapNode->m_tAudSndFormat.m_tFormat;
	tBasParam.m_tEncrypt = Inst()->GetConfEncryptInfo();

	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetAudBasParam_Req);
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
        tBasParam.m_dwEqpID = m_atAudBasSpeaker[wIndex].GetBasEqpId();
		cMsg.SetBody(&tBasParam, sizeof(tBasParam));
		cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}

	tBasParam.m_dwEqpID = m_tAudBasSpeakerMix.GetBasEqpId();
	cMsg.SetBody(&tBasParam, sizeof(tBasParam));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	SetSpeakerAudBasSyncForXmpu();
	
	return ;
}

#else

void CUmsBas::SetSpeakerAudBasEncCmd(void)
{
	if (!Inst()->IsAudNeedBas() )
	{
		return;
	}

	u16 wEpId = Inst()->curSpeakerID();
	if ((Inst()->GetAudMix()->IsAudMixMode() || Inst()->GetUmsDiscuss()->IsDiscussModle()) && !Inst()->IsChairConf())
	{
		wEpId = Inst()->chairID();
	}

	TCapNode* ptCapNode = Inst()->GetNodeMgr()->GetForeFatherNode(wEpId);
	if ( NULL == ptCapNode || !ptCapNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetSpeakerAudBasEncCmd, AdjustSpeakerAudBas ptCapNode Invalid! ConfID:%d, Ep:%d\n", 
			Inst()->GetInsID(), wEpId));
		return ;
	}

	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < localmin(Inst()->m_tConfBaseInfo.m_wAudFmtNum, UMS_AUDBAS_ENC_NUM); wIndex ++ )
	{//
		m_tAudBasSpeakerMix.m_atAudFmt[wIndex] = Inst()->m_tConfBaseInfo.m_atAudFmt[wIndex];
	}

	m_tAudBasSpeakerMix.m_tSndAudFmt = ptCapNode->m_tAudSndFormat.m_tFormat;
	m_tAudBasSpeakerMix.m_tSndAudFmt.m_byReserve1 = ptCapNode->m_tAudSndFormat.m_wDynamicPayload;

	TStartAudAdapter tTPStart;
	tTPStart.m_tAudDec = ptCapNode->m_tAudSndFormat.m_tFormat;
	memcpy(tTPStart.m_atAudEnc, m_tAudBasSpeakerMix.m_atAudFmt, sizeof(tTPStart.m_atAudEnc));

	// 加密参数
	tTPStart.m_tEncrypt = Inst()->GetConfEncryptInfo();

	CTpMsg cMsg;
	cMsg.SetEvent(ev_AudBasStartAdapter_Req);
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		tTPStart.m_byEqpID = m_atAudBasSpeaker[wIndex].m_tEqpRes.m_tBasChnInfo.m_byEqpID;
		tTPStart.m_byChnlIndx = m_atAudBasSpeaker[wIndex].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		cMsg.SetBody(&tTPStart, sizeof(tTPStart));
		cMsg.Post(m_atAudBasSpeaker[wIndex].m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}

	tTPStart.m_byEqpID = m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_byEqpID;
	tTPStart.m_byChnlIndx = m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
	cMsg.SetBody(&tTPStart, sizeof(tTPStart));
	cMsg.Post(m_tAudBasSpeakerMix.m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	SetSpeakerAudBasSync();
	
	return ;
}

#endif


void CUmsBas::AdjustSpeakerAudBas()
{
#ifdef _USE_XMPUEQP_
    SetXmpuSpeakerAudBasEncCmd();
#else
    SetSpeakerAudBasEncCmd();
#endif
	return;
}

void CUmsBas::GetSpeakerAudBasInAddr( u16 wScreenIndx, TTPDsFrom& tAddr )
{
	if ( wScreenIndx >= TP_MAX_STREAMNUM )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetSpeakerAudBasInAddr. wScreenIndx Invalid! ConfID:%d, wScreenIndx:%d\n", Inst()->GetInsID(), wScreenIndx));
		return ;
	}

#ifdef _USE_XMPUEQP_
	tAddr.m_tRtpAddr = m_atAudBasSpeaker[wScreenIndx].m_tXmpuAudBas.m_tDecMiddleRtpAddr;
	tAddr.m_tBackRtcpAddr = m_atAudBasSpeaker[wScreenIndx].m_tXmpuAudBas.m_tDecRtcpAddr;
	tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;

#else
	tAddr.m_tRtpAddr.SetAddr(m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_dwEqpIp, 
							m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort + 2);

	tAddr.m_tBackRtcpAddr.SetAddr(m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + 2 + 1);

	tAddr.m_dwEqpNode = m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

void CUmsBas::GetSpeakerAudBasOutAddr( u16 wScreenIndx, EmTpAudioFormat emFmt, TTPDsFrom& tAddr )
{
	if ( wScreenIndx >= TP_MAX_STREAMNUM )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetSpeakerAudBasOutAddr. wScreenIndx Invalid! ConfID:%d, wScreenIndx:%d\n", Inst()->GetInsID(), wScreenIndx));
		return ;
	}

	if ( emFmt == emTPAEnd )
	{
		return ;
	}

	u16 wIndex = m_tAudBasSpeakerMix.FindIndex(emFmt);

	if ( !TP_VALID_HANDLE(wIndex) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetSpeakerAudBasOutAddr. emFmt not find! ConfID:%d, emFmt:%d\n", Inst()->GetInsID(), emFmt));
		return ;
	}
	
#ifdef _USE_XMPUEQP_
    tAddr.m_tRtpAddr = m_atAudBasSpeaker[wScreenIndx].m_tXmpuAudBas.m_atEncRtpAddr[wIndex];
	tAddr.m_tBackRtcpAddr =  m_atAudBasSpeaker[wScreenIndx].m_tXmpuAudBas.m_atEncMiddleRtcpAddr[wIndex];
	tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
#else
	tAddr.m_tRtpAddr.SetAddr(m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2);
	
	tAddr.m_tBackRtcpAddr.SetAddr(m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_dwEqpIp,
							m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2 + 1);

	tAddr.m_dwEqpNode = m_atAudBasSpeaker[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

void CUmsBas::GetSpeakerMixAudBasInAddr( TTPDsFrom& tAddr )
{
#ifdef _USE_XMPUEQP_
    tAddr.m_tRtpAddr = m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecMiddleRtpAddr;
    tAddr.m_tBackRtcpAddr = m_tAudBasSpeakerMix.m_tXmpuAudBas.m_tDecRtcpAddr;
    tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
#else
	tAddr.m_tRtpAddr.SetAddr(m_tAudBasSpeakerMix.m_tEqpRes.m_dwEqpIp, 
							m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort + 2);
	
	tAddr.m_tBackRtcpAddr.SetAddr(m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + 2 + 1);

	tAddr.m_dwEqpNode = m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

void CUmsBas::GetSpeakerMixAudBasOutAddr( EmTpAudioFormat emFmt, TTPDsFrom& tAddr )
{
	if ( emFmt == emTPAEnd )
	{
		return ;
	}
	
	u16 wIndex = m_tAudBasSpeakerMix.FindIndex(emFmt);
	
	if ( !TP_VALID_HANDLE(wIndex) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetSpeakerMixAudBasOutAddr. emFmt not find! ConfID:%d, emFmt:%d\n", Inst()->GetInsID(), emFmt));
		return ;
	}

#ifdef _USE_XMPUEQP_
	tAddr.m_tRtpAddr = m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncRtpAddr[wIndex];
	tAddr.m_tBackRtcpAddr = m_tAudBasSpeakerMix.m_tXmpuAudBas.m_atEncMiddleRtcpAddr[wIndex];
    tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
#else
	tAddr.m_tRtpAddr.SetAddr(m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2);
	
	tAddr.m_tBackRtcpAddr.SetAddr(m_tAudBasSpeakerMix.m_tEqpRes.m_dwEqpIp,
							m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2 + 1);

	tAddr.m_dwEqpNode = m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

BOOL32 CUmsBas::IsChairNeedAudBas(EmTpAudioFormat emFmt)
{
	if ( !Inst()->IsAudNeedBas() )
	{
		return FALSE;
	}
	
	if ( m_atAudBasChair[MIDSCREENINDEX].m_tSndAudFmt.m_emFormat == emFmt )
	{
		return FALSE;
	}
	return TRUE;
}

#ifdef _USE_XMPUEQP_
void CUmsBas::SetXmpuChairAudBasEncCmd(void)
{

	if (!Inst()->IsAudNeedBas() )
	{
		return;
	}
	
	TCapNode* ptChair = Inst()->GetNodeMgr()->GetForeFatherNode(Inst()->chairID());
	if ( NULL == ptChair && !ptChair->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuChairAudBasEncCmd. Chair Invalid! ConfID:%d, dualEp:%d\n", 
			    Inst()->GetInsID(), Inst()->chairID()));
		return ;
	}
	
	TCapNode* ptSpeaker = Inst()->GetNodeMgr()->GetForeFatherNode(Inst()->curSpeakerID());
	if ( NULL == ptSpeaker && !ptSpeaker->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuChairAudBasEncCmd. Speaker Invalid! ConfID:%d, dualEp:%d\n",
			    Inst()->GetInsID(), Inst()->curSpeakerID()));
		return ;
	}

	m_atAudBasChair[MIDSCREENINDEX].m_tSndAudFmt = ptChair->m_tAudSndFormat.m_tFormat;
	m_atAudBasChair[MIDSCREENINDEX].m_tSndAudFmt.m_byReserve1 = ptChair->m_tAudSndFormat.m_wDynamicPayload;


	TXmpuChgAudParam tBasParam;
	tBasParam.m_tAudDec = ptChair->m_tAudSndFormat.m_tFormat;
	tBasParam.m_tEncrypt = Inst()->GetConfEncryptInfo();
	
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetAudBasParam_Req);
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{
		if (!m_atAudBasChair[wIndex].IsBasValid())
		{
			continue;
		}
        tBasParam.m_dwEqpID = m_atAudBasChair[wIndex].GetBasEqpId();
		cMsg.SetBody(&tBasParam, sizeof(tBasParam));
		cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}
	
	CNetPortMgr::CreateVirChairToBas(Inst());

	SetChairAudBasSyncForXmpu();
	return ;
}

#else

void CUmsBas::SetChairAudBasEncCmd(void)
{
	if (!Inst()->IsAudNeedBas() )
	{
		return;
	}
	
	TCapNode* ptChair = Inst()->GetNodeMgr()->GetForeFatherNode(Inst()->chairID());
	if ( NULL == ptChair && !ptChair->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairAudBasEncCmd, AdjustChairAudBas Chair Invalid! ConfID:%d, dualEp:%d\n", Inst()->GetInsID(), Inst()->chairID()));
		return ;
	}

	TCapNode* ptSpeaker = Inst()->GetNodeMgr()->GetForeFatherNode(Inst()->curSpeakerID());
	if ( NULL == ptSpeaker && !ptSpeaker->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairAudBasEncCmd, AdjustChairAudBas Speaker Invalid! ConfID:%d, dualEp:%d\n", Inst()->GetInsID(), Inst()->curSpeakerID()));
		return ;
	}

	u16 wFmt = 0;
	u16 wIndex = 0;
	for ( wIndex = 0; wIndex < localmin(Inst()->m_tConfBaseInfo.m_wAudFmtNum, UMS_AUDBAS_ENC_NUM); wIndex ++ )
	{// 主席固定，可以少出一路
		if (ptChair->m_tAudSndFormat.m_tFormat.m_emFormat == Inst()->m_tConfBaseInfo.m_atAudFmt[wIndex].m_emFormat)
		{
			continue;
		}

		m_atAudBasChair[MIDSCREENINDEX].m_atAudFmt[wFmt++] = Inst()->m_tConfBaseInfo.m_atAudFmt[wIndex];
	}

	m_atAudBasChair[MIDSCREENINDEX].m_tSndAudFmt = ptChair->m_tAudSndFormat.m_tFormat;
	m_atAudBasChair[MIDSCREENINDEX].m_tSndAudFmt.m_byReserve1 = ptChair->m_tAudSndFormat.m_wDynamicPayload;

	TStartAudAdapter tTPStart;
	tTPStart.m_tAudDec = ptChair->m_tAudSndFormat.m_tFormat;
	memcpy(tTPStart.m_atAudEnc, m_atAudBasChair[MIDSCREENINDEX].m_atAudFmt, sizeof(tTPStart.m_atAudEnc));
	
	// 加密参数
	tTPStart.m_tEncrypt = Inst()->GetConfEncryptInfo();
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_AudBasStartAdapter_Req);
	for (wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if (!m_atAudBasChair[wIndex].m_tEqpRes.IsValid())
		{
			continue;
		}

		tTPStart.m_byEqpID = m_atAudBasChair[wIndex].m_tEqpRes.m_tBasChnInfo.m_byEqpID;
		tTPStart.m_byChnlIndx = m_atAudBasChair[wIndex].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		cMsg.SetBody(&tTPStart, sizeof(tTPStart));
		cMsg.Post(m_atAudBasChair[wIndex].m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}

	CNetPortMgr::CreateVirChairToBas(Inst());

	SetChairAudBasSync();
	
	return ;
}

#endif

void CUmsBas::AdjustChairAudBas()
{
#ifdef _USE_XMPUEQP_
    SetXmpuChairAudBasEncCmd();
#else
    SetChairAudBasEncCmd();
#endif
	return ;
}

void CUmsBas::GetChairAudBasInAddr(u16 wScreenIndx,  TTPDsFrom& tAddr )
{
	if ( wScreenIndx >= TP_MAX_STREAMNUM )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetChairAudBasInAddr. wScreenIndx Invalid! ConfID:%d, wScreenIndx:%d\n", Inst()->GetInsID(), wScreenIndx));
		return ;
	}

#ifdef _USE_XMPUEQP_
	tAddr.m_tRtpAddr = m_atAudBasChair[wScreenIndx].m_tXmpuAudBas.m_tDecMiddleRtpAddr;
    tAddr.m_tBackRtcpAddr = m_atAudBasChair[wScreenIndx].m_tXmpuAudBas.m_tDecRtcpAddr;
    tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
#else
	tAddr.m_tRtpAddr.SetAddr(m_atAudBasChair[wScreenIndx].m_tEqpRes.m_dwEqpIp, 
							m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort + 2);
	
	tAddr.m_tBackRtcpAddr.SetAddr(m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + 2 + 1);

	tAddr.m_dwEqpNode = m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

void CUmsBas::GetChairAudBasOutAddr(u16 wScreenIndx,  EmTpAudioFormat emFmt, TTPDsFrom& tAddr )
{
	if ( wScreenIndx >= TP_MAX_STREAMNUM )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetChairAudBasOutAddr. wScreenIndx Invalid! ConfID:%d, wScreenIndx:%d\n", Inst()->GetInsID(), wScreenIndx));
		return ;
	}

	u16 wIndex = m_atAudBasChair[MIDSCREENINDEX].FindIndex(emFmt);
	if ( !TP_VALID_HANDLE(wIndex) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetChairAudBasOutAddr. emFmt not find! ConfID:%d, emFmt:%d\n", Inst()->GetInsID(), emFmt));
		return ;
	}

#ifdef _USE_XMPUEQP_
    tAddr.m_tRtpAddr = m_atAudBasChair[wScreenIndx].m_tXmpuAudBas.m_atEncRtpAddr[wIndex];
    tAddr.m_tBackRtcpAddr = m_atAudBasChair[wScreenIndx].m_tXmpuAudBas.m_atEncMiddleRtcpAddr[wIndex];
	tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
#else
	tAddr.m_tRtpAddr.SetAddr(m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2);
	
	tAddr.m_tBackRtcpAddr.SetAddr(m_atAudBasChair[wScreenIndx].m_tEqpRes.m_dwEqpIp,
							m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2 + 1);

	tAddr.m_dwEqpNode = m_atAudBasChair[wScreenIndx].m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

BOOL32 CUmsBas::IsDualNeedAudBas(EmTpAudioFormat emFmt)
{
	if ( !Inst()->IsAudNeedBas() && !m_tAudBasDual.IsBasValid())
	{
		return FALSE;
	}
	
	return TRUE;
}

#ifdef _USE_XMPUEQP_
void CUmsBas::SetXmpuDualAudBasEncCmd(void)
{
	if (!m_tAudBasDual.IsBasValid())
	{
		return;
	}
	
	TCapNode* ptDualNode = Inst()->GetNodeMgr()->GetForeFatherNode(Inst()->GetDualMgr()->GetDualID());
	if ( NULL == ptDualNode && !ptDualNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetXmpuDualAudBasEncCmd. DualNode Invalid! ConfID:%d, dualEp:%d\n", 
			Inst()->GetInsID(), Inst()->GetDualMgr()->GetDualID()));
		return ;
	}
	
	//级联双流适配  UMS之间的双流通道只打开了上级到下级的通道
	//双流源 通道格式选择 需要特别注意！
	if ( ptDualNode->IsUms() && ptDualNode->m_wEpID != CALLER_EP_INDEX )
	{//下级发双流，则需要取接收通道格式
		m_tAudBasDual.m_tSndAudFmt = ptDualNode->m_tDualAudRcvFormat.m_tFormat;
	}
	else
	{
		m_tAudBasDual.m_tSndAudFmt = ptDualNode->m_tDualAudSndFormat.m_tFormat;
	}
	
	m_tAudBasDual.m_tSndAudFmt.m_byReserve1 = ptDualNode->m_tDualAudSndFormat.m_wDynamicPayload;
	
	TXmpuChgAudParam tBasParam;
	tBasParam.m_tAudDec =  ptDualNode->m_tAudSndFormat.m_tFormat;
	tBasParam.m_tEncrypt = Inst()->GetConfEncryptInfo();
	
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_SetAudBasParam_Req);
    tBasParam.m_dwEqpID = m_tAudBasDual.m_tXmpuAudBas.m_dwEqpID;
	cMsg.SetBody(&tBasParam, sizeof(tBasParam));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
}
#else
void CUmsBas::SetDualAudBasEncCmd()
{
	
	if (!m_tAudBasDual.m_tEqpRes.IsValid())
	{
		return;
	}
	
	TCapNode* ptDualNode = Inst()->GetNodeMgr()->GetForeFatherNode(Inst()->GetDualMgr()->GetDualID());
	if ( NULL == ptDualNode && !ptDualNode->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetDualAudBasEncCmd, AdjustDualAudBas DualNode Invalid! ConfID:%d, dualEp:%d\n", 
			Inst()->GetInsID(), Inst()->GetDualMgr()->GetDualID()));
		return ;
	}
	
	//级联双流适配  UMS之间的双流通道只打开了上级到下级的通道
	//双流源 通道格式选择 需要特别注意！
	if ( ptDualNode->IsUms() && ptDualNode->m_wEpID != CALLER_EP_INDEX )
	{//下级发双流，则需要取接收通道格式
		m_tAudBasDual.m_tSndAudFmt = ptDualNode->m_tDualAudRcvFormat.m_tFormat;
	}
	else
	{
		m_tAudBasDual.m_tSndAudFmt = ptDualNode->m_tDualAudSndFormat.m_tFormat;
	}
	
	for ( u16 wIndex = 0; wIndex < localmin(Inst()->m_tConfBaseInfo.m_wAudFmtNum, UMS_AUDBAS_ENC_NUM); wIndex ++ )
	{
		m_tAudBasDual.m_atAudFmt[wIndex] = Inst()->m_tConfBaseInfo.m_atAudFmt[wIndex];
	}
	
	m_tAudBasDual.m_tSndAudFmt.m_byReserve1 = ptDualNode->m_tDualAudSndFormat.m_wDynamicPayload;
	
	TStartAudAdapter tTPStart;
	tTPStart.m_tAudDec = ptDualNode->m_tAudSndFormat.m_tFormat;
	memcpy(tTPStart.m_atAudEnc, m_tAudBasDual.m_atAudFmt, sizeof(tTPStart.m_atAudEnc));
	
	// 加密参数
	tTPStart.m_tEncrypt = Inst()->GetConfEncryptInfo();
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_AudBasStartAdapter_Req);
	
	tTPStart.m_byEqpID = m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_byEqpID;
	tTPStart.m_byChnlIndx = m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
	
	cMsg.SetBody(&tTPStart, sizeof(tTPStart));
	cMsg.Post(m_tAudBasDual.m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
}

#endif

void CUmsBas::AdjustDualAudBas()
{
#ifdef _USE_XMPUEQP_
    SetXmpuDualAudBasEncCmd();
#else
    SetDualAudBasEncCmd();
#endif
}

void CUmsBas::GetDualAudBasInAddr( TTPDsFrom& tAddr )
{
#ifdef _USE_XMPUEQP_
    tAddr.m_tRtpAddr = m_tAudBasDual.m_tXmpuAudBas.m_tDecMiddleRtpAddr;
    tAddr.m_tBackRtcpAddr = m_tAudBasDual.m_tXmpuAudBas.m_tDecRtcpAddr;
	tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
#else
	tAddr.m_tRtpAddr.SetAddr(m_tAudBasDual.m_tEqpRes.m_dwEqpIp, 
							m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wEqpStartPort + 2);
	
	tAddr.m_tBackRtcpAddr.SetAddr(m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + 2 + 1);

	tAddr.m_dwEqpNode = m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

void CUmsBas::GetDualAudBasOutAddr( EmTpAudioFormat emFmt, TTPDsFrom& tAddr )
{
	if ( emFmt == emTPAEnd )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetDualAudBasOutAddr. emFmt is End! ConfID:%d\n", Inst()->GetInsID()));
		return ;
	}
	
	u16 wIndex = m_tAudBasDual.FindIndex(emFmt);
	
	if ( !TP_VALID_HANDLE(wIndex) )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::GetDualAudBasOutAddr. emFmt not find! ConfID:%d, emFmt:%d\n", Inst()->GetInsID(), emFmt));
		return ;
	}
	
#ifdef _USE_XMPUEQP_
    tAddr.m_tRtpAddr = m_tAudBasDual.m_tXmpuAudBas.m_atEncRtpAddr[wIndex];
    tAddr.m_tBackRtcpAddr = m_tAudBasDual.m_tXmpuAudBas.m_atEncMiddleRtcpAddr[wIndex];
	tAddr.m_dwEqpNode = Inst()->GetConfEqpDs().m_dwEqpNode;
#else
	tAddr.m_tRtpAddr.SetAddr(m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_dwMediaIP, 
							m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2);
	
	tAddr.m_tBackRtcpAddr.SetAddr(m_tAudBasDual.m_tEqpRes.m_dwEqpIp,
							m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wUmsStartPort + wIndex*UMS_MCU_PORT_PORTSPAN + 2 + 1);

	tAddr.m_dwEqpNode = m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_dwMediaNode;
#endif
}

//分配bas统一接口 
BOOL32 CUmsBas::AssignBas(TBasEqpRes& tRes, u16 wReqNum /* = 1 */, u32 dwNode /* = 0 */)
{
	CUmsConfInst* pInst = Inst();

	tRes.Clear();

	TAudBasParam tBasParam;
	tBasParam.SetParam(pInst->GetInsID(), &tRes, wReqNum, dwNode);

	if ( !AssignEqpEx(&tBasParam) )
	{
		return FALSE;
	}

	tRes.m_tBasChnInfo.m_dwMediaNode = Inst()->GetConfEqpDs().m_dwEqpNode;
	tRes.m_tBasChnInfo.m_dwMediaIP = Inst()->GetConfEqpDs().m_dwEqpIp;
	//适配板 挂载到 会议转发板
	TBasSndAddr tSndAddr;
	tSndAddr.m_byEqpID =	tRes.m_tBasChnInfo.m_byEqpID;
	tSndAddr.m_dwNewDsIP = Inst()->m_tEqpConfDs.m_dwEqpIp;
	//开启适配
	CTpMsg cMsg;
	cMsg.SetEvent(ev_TPEqp_ChangeSndAddr_Req);
	cMsg.SetBody(&tSndAddr, sizeof(tSndAddr));
	cMsg.Post(UMS_EQP_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

	return TRUE;	
}


#ifdef _USE_XMPUEQP_
BOOL32 CUmsBas::AssignDualAudBasFromXmpu(void)
{
    CUmsConfInst* pInst = Inst();
	
	if ( !Inst()->IsAudNeedBas() )
	{
		return TRUE;
	}
	
	if (m_tAudBasDual.m_tXmpuAudBas.m_dwEqpID)
	{
		return TRUE;
	}
	
    TUmsAudFormat *pBasInParam =  &(Inst()->GetConfBase().m_atAudFmt[0]); //取其中一个格式
	u32 dwOutCh = Inst()->GetConfBase().m_wAudFmtNum;
	TUmsAudFormat *pBasOutParam = Inst()->GetConfBase().m_atAudFmt;
	for ( u16 wIndex = 0; wIndex < dwOutCh; wIndex ++ )
	{
		m_tAudBasDual.m_atAudFmt[wIndex] = pBasOutParam[wIndex];
	}

	if (!AssignXmpuAudBas(pBasInParam, m_tAudBasDual.m_atAudFmt, dwOutCh, &m_tAudBasDual.m_tXmpuAudBas))
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignDualAudBasFromXmpu. AssignAud Fail! ConfID:%d, FormatNum:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wAudFmtNum));
		
	}
	
	return TRUE;
}

#else

BOOL32 CUmsBas::AssignDualAudBas()
{
	CUmsConfInst* pInst = Inst();

	if ( !Inst()->IsAudNeedBas() )
	{
		return TRUE;
	}

	if (m_tAudBasDual.m_tEqpRes.IsValid())
	{
		return TRUE;
	}

	if(!AssignBas(m_tAudBasDual.m_tEqpRes, 1))
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::AssignDualAudBas. AssignAud Fail! ConfID:%d, FormatNum:%d\n", 
			pInst->GetInsID(), pInst->m_tConfBaseInfo.m_wAudFmtNum));
		return FALSE;
	}

	return TRUE;
}
#endif

void CUmsBas::ReleaseDualAudBas()
{
	if(m_tAudBasDual.IsBasValid())
	{
		RealseAudBasByScreen(&m_tAudBasDual);
		m_tAudBasDual.ClearBas();
	}
	return;
}

#ifdef _USE_XMPUEQP_
void CUmsBas::SetSpeakerAudBasSyncForXmpu(void)
{
	TCallNode* ptSpeaker = Inst()->GetNodeMgr()->GetNode(Inst()->curSpeakerID());
	if ( NULL == ptSpeaker && !ptSpeaker->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetSpeakerAudBasSyncForXmpu. Speaker Invalid! ConfID:%d, dualEp:%d\n", Inst()->GetInsID(), Inst()->curSpeakerID()));
		return ;
	}

	TXmpuAudBasSynInfo tSetSync;
    tSetSync.m_emSynType = em_Xmpu_AudBas_SpeakerEp;
	if (Inst()->GetAudMix()->IsAudMixMode() || Inst()->GetRollCallMgr()->IsRollCallModle())
	{
		//开启会议混音或点名三屏会场，  目的三屏只有中间屏有音频，不需要音频同步
		tSetSync.m_adwEqpID[1] = m_atAudBasSpeaker[1].GetBasEqpId();
		
	} else if ( Inst()->GetUmsDiscuss()->IsDiscussModle() )
	{
		if ( Inst()->GetUmsDiscuss()->IsMaxVmpSameEp() )
		{ 
			tSetSync.m_adwEqpID[0] = m_atAudBasSpeaker[0].GetBasEqpId();
			tSetSync.m_adwEqpID[1] = m_atAudBasSpeaker[1].GetBasEqpId();
			tSetSync.m_adwEqpID[2] = m_atAudBasSpeaker[2].GetBasEqpId();
		}
	}
	else if ( ptSpeaker->IsThreeAudSnd() )
	{
		tSetSync.m_adwEqpID[0] = m_atAudBasSpeaker[0].GetBasEqpId();
		tSetSync.m_adwEqpID[1] = m_atAudBasSpeaker[1].GetBasEqpId();
		tSetSync.m_adwEqpID[2] = m_atAudBasSpeaker[2].GetBasEqpId();

	}else if ( ptSpeaker->IsSingleAudSnd() )
	{
		tSetSync.m_adwEqpID[1] = m_atAudBasSpeaker[1].GetBasEqpId();
	}

	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_AudBasSetSyn_Req);
	cMsg.SetBody(&tSetSync, sizeof(tSetSync));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
}

#else

void CUmsBas::SetSpeakerAudBasSync()
{
	TCallNode* ptSpeaker = Inst()->GetNodeMgr()->GetNode(Inst()->curSpeakerID());
	if ( NULL == ptSpeaker && !ptSpeaker->IsChanOn() )
	{
		MdlError(Ums_Mdl_Call, ("CUmsBas::SetSpeakerAudBasSync. Speaker Invalid! ConfID:%d, dualEp:%d\n", Inst()->GetInsID(), Inst()->curSpeakerID()));
		return ;
	}

	TAudBasSyncChnl tSync;

	tSync.m_bSet = 1;

	tSync.m_byEqpID = m_atAudBasSpeaker[0].m_tEqpRes.m_tBasChnInfo.m_byEqpID;

	if (Inst()->GetAudMix()->IsAudMixMode() || Inst()->GetRollCallMgr()->IsRollCallModle())
	{
		//开启会议混音或点名三屏会场，  目的三屏只有中间屏有音频，不需要音频同步
		tSync.m_abyChanId[1] = m_atAudBasSpeaker[1].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;

	} else if ( Inst()->GetUmsDiscuss()->IsDiscussModle() )
	{
		if ( Inst()->GetUmsDiscuss()->IsMaxVmpSameEp() )
		{
			tSync.m_abyChanId[0] = m_atAudBasSpeaker[0].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
			tSync.m_abyChanId[1] = m_atAudBasSpeaker[1].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
			tSync.m_abyChanId[2] = m_atAudBasSpeaker[2].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		}
	}
	else if ( ptSpeaker->IsThreeAudSnd() )
	{
		tSync.m_abyChanId[0] = m_atAudBasSpeaker[0].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		tSync.m_abyChanId[1] = m_atAudBasSpeaker[1].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		tSync.m_abyChanId[2] = m_atAudBasSpeaker[2].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
	}
	else if ( ptSpeaker->IsSingleAudSnd() )
	{
		tSync.m_abyChanId[1] = m_atAudBasSpeaker[1].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
	}
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_AudBasSetSync_Req);
	cMsg.SetBody(&tSync, sizeof(TAudBasSyncChnl));
	cMsg.Post(m_atAudBasSpeaker[0].m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
}

#endif


#ifdef _USE_XMPUEQP_
void CUmsBas::SetChairAudBasSyncForXmpu(void)
{
	TXmpuAudBasSynInfo tSetSync;
    tSetSync.m_emSynType = em_Xmpu_AudBas_ChairEp;
	if( Inst()->GetChairCap().IsChairSingleAudSnd() )
	{//主席为 单屏不需要同步	
		return ;
	}
	
    if ( Inst()->GetChairCap().IsChairThreeAudSnd() && !Inst()->GetUmsDiscuss()->IsDiscussModle())
	{
		TCallNode* ptSpeaker = Inst()->GetNodeMgr()->GetNode(Inst()->curSpeakerID());
		if ( NULL == ptSpeaker && !ptSpeaker->IsChanOn() )
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairAudBasSyncForXmpu. Speaker Invalid! ConfID:%d, dualEp:%d\n", Inst()->GetInsID(), Inst()->curSpeakerID()));
			return ;
		}
		
		if ( ptSpeaker->IsThreeAudSnd() )
		{
			tSetSync.m_adwEqpID[0] = m_atAudBasChair[0].GetBasEqpId();
			tSetSync.m_adwEqpID[1] = m_atAudBasChair[1].GetBasEqpId();
			tSetSync.m_adwEqpID[2] = m_atAudBasChair[2].GetBasEqpId();
		}else if ( ptSpeaker->IsSingleAudSnd() )
		{
			tSetSync.m_adwEqpID[1] = m_atAudBasChair[1].GetBasEqpId();
		}
	}
	
	CTpMsg cMsg;
	cMsg.SetEvent(evXmpu_AudBasSetSyn_Req);
	cMsg.SetBody(&tSetSync, sizeof(tSetSync));
	cMsg.Post(UMS_XMPU_APP_INST, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
}

#else
void CUmsBas::SetChairAudBasSync()
{
	TAudBasSyncChnl tSync;
	
	tSync.m_bSet = 2;
	
	tSync.m_byEqpID = m_atAudBasChair[0].m_tEqpRes.m_tBasChnInfo.m_byEqpID;
	
	
	if( Inst()->GetChairCap().IsChairSingleAudSnd() )
	{//主席为 单屏不需要同步
		tSync.m_abyChanId[1] = m_atAudBasChair[1].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		
		return ;
	}
	else if ( Inst()->GetChairCap().IsChairThreeAudSnd() && !Inst()->GetUmsDiscuss()->IsDiscussModle())
	{
		TCallNode* ptSpeaker = Inst()->GetNodeMgr()->GetNode(Inst()->curSpeakerID());
		if ( NULL == ptSpeaker && !ptSpeaker->IsChanOn() )
		{
			MdlError(Ums_Mdl_Call, ("CUmsBas::SetChairAudBasSync. Speaker Invalid! ConfID:%d, dualEp:%d\n", Inst()->GetInsID(), Inst()->curSpeakerID()));
			return ;
		}
		
		if ( ptSpeaker->IsThreeAudSnd() )
		{
			tSync.m_abyChanId[0] = m_atAudBasChair[0].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
			tSync.m_abyChanId[1] = m_atAudBasChair[1].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
			tSync.m_abyChanId[2] = m_atAudBasChair[2].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		}
		else if ( ptSpeaker->IsSingleAudSnd() )
		{
			tSync.m_abyChanId[1] = m_atAudBasChair[1].m_tEqpRes.m_tBasChnInfo.m_wChnIndx;
		}
	}
	
	CTpMsg cMsg;
	cMsg.SetEvent(ev_AudBasSetSync_Req);
	cMsg.SetBody(&tSync, sizeof(TAudBasSyncChnl));
	cMsg.Post(m_atAudBasChair[0].m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
}

#endif


void CUmsBas::SetQtMediaKey( const TTPQTMediaKeyInfo& tInfo )
{
	u16 wIndex = 0;
	CTpMsg cMsg;
	
	//////////////////////////////////////////////////////////////////////////
	//视频适配
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( m_cSpeaker.m_atBas[wIndex].IsValid() )
		{
			cMsg.SetEvent(ev_TPBas_SetMediaKey_Req);
			cMsg.SetBody(&(m_cSpeaker.m_atBas[wIndex].m_tBasChnInfo.m_byEqpID), sizeof(u8));
			cMsg.CatBody(&(m_cSpeaker.m_atBas[wIndex].m_tBasChnInfo.m_wChnIndx), sizeof(u16));
			cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
			cMsg.Post(m_cSpeaker.m_atBas[wIndex].m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		}
	}
	
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( m_cChair.m_atBas[wIndex].IsValid() )
		{
			cMsg.SetEvent(ev_TPBas_SetMediaKey_Req);
			cMsg.SetBody(&(m_cChair.m_atBas[wIndex].m_tBasChnInfo.m_byEqpID), sizeof(u8));
			cMsg.CatBody(&(m_cChair.m_atBas[wIndex].m_tBasChnInfo.m_wChnIndx), sizeof(u16));
			cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
			cMsg.Post(m_cChair.m_atBas[wIndex].m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		}
	}
	
	if ( m_cDual.m_tBas.IsValid() )
	{
		cMsg.SetEvent(ev_TPBas_SetMediaKey_Req);
		cMsg.SetBody(&(m_cDual.m_tBas.m_tBasChnInfo.m_byEqpID), sizeof(u8));
		cMsg.CatBody(&(m_cDual.m_tBas.m_tBasChnInfo.m_wChnIndx), sizeof(u16));
		cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
		cMsg.Post(m_cDual.m_tBas.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}
	
	for ( wIndex = 0; wIndex < BAS_CHN_RES_MAX_NUM; wIndex ++ )
	{
		if(m_tConfBasMgr.BasChnRes(wIndex)->IsBasValid())
		{
			cMsg.SetEvent(ev_TPBas_SetMediaKey_Req);
			cMsg.SetBody(&(m_tConfBasMgr.BasChnRes(wIndex)->m_tBasEqpRes.m_tBasChnInfo.m_byEqpID), sizeof(u8));
			cMsg.CatBody(&(m_tConfBasMgr.BasChnRes(wIndex)->m_tBasEqpRes.m_tBasChnInfo.m_wChnIndx), sizeof(u16));
			cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
			cMsg.Post(m_tConfBasMgr.BasChnRes(wIndex)->m_tBasEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	//音频适配
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( m_atAudBasSpeaker[wIndex].m_tEqpRes.IsValid() )
		{
			cMsg.SetEvent(ev_AudBas_set_mediakey_ntfy);
			cMsg.SetBody(&(m_atAudBasSpeaker[wIndex].m_tEqpRes.m_tBasChnInfo.m_byEqpID), sizeof(u8));
			cMsg.CatBody(&(m_atAudBasSpeaker[wIndex].m_tEqpRes.m_tBasChnInfo.m_wChnIndx), sizeof(u16));
			cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
			cMsg.Post(m_atAudBasSpeaker[wIndex].m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		}
	}
	
	for ( wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
	{
		if ( m_atAudBasChair[wIndex].m_tEqpRes.IsValid() )
		{
			cMsg.SetEvent(ev_AudBas_set_mediakey_ntfy);
			cMsg.SetBody(&(m_atAudBasChair[wIndex].m_tEqpRes.m_tBasChnInfo.m_byEqpID), sizeof(u8));
			cMsg.CatBody(&(m_atAudBasChair[wIndex].m_tEqpRes.m_tBasChnInfo.m_wChnIndx), sizeof(u16));
			cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
			cMsg.Post(m_atAudBasChair[wIndex].m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
		}
	}
	
	if ( m_tAudBasSpeakerMix.m_tEqpRes.IsValid() )
	{
		cMsg.SetEvent(ev_AudBas_set_mediakey_ntfy);
		cMsg.SetBody(&(m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_byEqpID), sizeof(u8));
		cMsg.CatBody(&(m_tAudBasSpeakerMix.m_tEqpRes.m_tBasChnInfo.m_wChnIndx), sizeof(u16));
		cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
		cMsg.Post(m_tAudBasSpeakerMix.m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}
	
	if ( m_tAudBasDual.m_tEqpRes.IsValid() )
	{
		cMsg.SetEvent(ev_AudBas_set_mediakey_ntfy);
		cMsg.SetBody(&(m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_byEqpID), sizeof(u8));
		cMsg.CatBody(&(m_tAudBasDual.m_tEqpRes.m_tBasChnInfo.m_wChnIndx), sizeof(u16));
		cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
		cMsg.Post(m_tAudBasDual.m_tEqpRes.m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));
	}
}



void CUmsBas::SetQtMediaKeyByBasEqp(const TBasEqpRes *ptBasEqpRes, const TTPQTMediaKeyInfo& tInfo)
{
	CUmsConfInst *pInst = Inst();
	TTPQTMediaKeyInfo  *pMediaKey = NULL;

	if (NULL == ptBasEqpRes)
	{
        return;
	}

    CTpMsg cMsg;
	cMsg.SetEvent(ev_TPBas_SetMediaKey_Req); 
	cMsg.SetBody(&(ptBasEqpRes->m_tBasChnInfo.m_byEqpID), sizeof(u8));
	cMsg.CatBody(&(ptBasEqpRes->m_tBasChnInfo.m_wChnIndx), sizeof(u16));
	cMsg.CatBody(&tInfo, sizeof(TTPQTMediaKeyInfo));
	cMsg.Post(ptBasEqpRes->m_dwEqpInst, 0, MAKEIID(AID_UMSCONFMGR, Inst()->GetInsID()));

    return;
}


#ifdef _USE_XMPUEQP_
BOOL32 CUmsBas::AssignAudBasFromXmpu(void)
{
	if ( !Inst()->IsAudNeedBas() )
	{
		return TRUE;
	}

    TUmsAudFormat *pBasInParam = NULL;
	TUmsAudFormat *pBasOutParam = NULL;
	u16 dwOutCh = 0;
    u16 wIndex = 0;
	BOOL32 bError = FALSE;

	do {
		// 申请发言人适配
		pBasInParam = &(Inst()->GetConfBase().m_atAudFmt[0]); //取其中一个格式
		dwOutCh = Inst()->GetConfBase().m_wAudFmtNum;
		pBasOutParam = Inst()->GetConfBase().m_atAudFmt;
		//发言人和单屏共用一套格式
		for ( wIndex = 0; wIndex < dwOutCh; wIndex ++ )
		{//
			m_tAudBasSpeakerMix.m_atAudFmt[wIndex] = pBasOutParam[wIndex];
		}
		for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
		    m_atAudBasSpeaker[wIndex].m_tXmpuAudBas.m_dwEqpID = 0;
			if (!AssignXmpuAudBas(pBasInParam, m_tAudBasSpeakerMix.m_atAudFmt, dwOutCh, &m_atAudBasSpeaker[wIndex].m_tXmpuAudBas))
			{
				bError = TRUE;
				break;
			}
		}
		
		if (bError)
		{
			break;
		}

		//申请单屏适配
		m_tAudBasSpeakerMix.m_tXmpuAudBas.m_dwEqpID = 0;
	    if (!AssignXmpuAudBas(pBasInParam, m_tAudBasSpeakerMix.m_atAudFmt, dwOutCh, &m_tAudBasSpeakerMix.m_tXmpuAudBas))
		{
			bError = TRUE;
			break;
		}

		//申请主席适配
		for ( wIndex = 0; wIndex < dwOutCh; wIndex ++ )
		{
			m_atAudBasChair[MIDSCREENINDEX].m_atAudFmt[wIndex] = pBasOutParam[wIndex];
		}
		for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			m_atAudBasChair[wIndex].m_tXmpuAudBas.m_dwEqpID = 0;
			if (!AssignXmpuAudBas(pBasInParam, m_atAudBasChair[MIDSCREENINDEX].m_atAudFmt, dwOutCh, &m_atAudBasChair[wIndex].m_tXmpuAudBas))
			{
				bError = TRUE;
				break;
			}

		}

	} while(0);

    if (bError)
	{
        for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
	        if (m_atAudBasSpeaker[wIndex].m_tXmpuAudBas.m_dwEqpID)
			{
				ReleaseXmpuAudBas(&m_atAudBasSpeaker[wIndex].m_tXmpuAudBas);
			    m_atAudBasSpeaker[wIndex].m_tXmpuAudBas.Clear();
			}

			if (m_atAudBasChair[wIndex].m_tXmpuAudBas.m_dwEqpID)
			{
				ReleaseXmpuAudBas(&m_atAudBasChair[wIndex].m_tXmpuAudBas);
				m_atAudBasChair[wIndex].m_tXmpuAudBas.Clear();
			}

		}

		if (m_tAudBasSpeakerMix.m_tXmpuAudBas.m_dwEqpID)
		{
			ReleaseXmpuAudBas(&m_tAudBasSpeakerMix.m_tXmpuAudBas);
			m_tAudBasSpeakerMix.m_tXmpuAudBas.Clear();
		}

		return FALSE;
	}

	return TRUE;
}

#else

BOOL32 CUmsBas::AssignAudBas()
{
	if ( !Inst()->IsAudNeedBas() )
	{
		return TRUE;
	}
	
	u16 wIndex = 0;
	u32 dwNode = 0;
	if (!AssignBas(m_atAudBasSpeaker[0].m_tEqpRes, TP_MAX_STREAMNUM))
	{
		return FALSE;
	}
	dwNode = m_atAudBasSpeaker[0].m_tEqpRes.m_dwEqpNode;
	for(wIndex = 1; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{// 保证发言人三路音频适配在同一个apu2板卡上
		if(!AssignBas(m_atAudBasSpeaker[wIndex].m_tEqpRes, TP_MAX_STREAMNUM, dwNode))
		{
			return FALSE;
		}
	}
	
	if(!AssignBas(m_tAudBasSpeakerMix.m_tEqpRes, 1))
	{
		return FALSE;
	}
	
	
	if (!AssignBas(m_atAudBasChair[0].m_tEqpRes, TP_MAX_STREAMNUM))
	{
		return FALSE;
	}
	dwNode = m_atAudBasChair[0].m_tEqpRes.m_dwEqpNode;	
	for(wIndex = 1; wIndex < TP_MAX_STREAMNUM; wIndex ++)
	{// 保证主席三路音频适配在同一个apu2板卡上
		if(!AssignBas(m_atAudBasChair[wIndex].m_tEqpRes, TP_MAX_STREAMNUM, dwNode))
		{
			return FALSE;
		}
	}
	
	return TRUE;
}

#endif

void CUmsBas::RealseAudBasByScreen(TAudBasScreen *ptScreenBas)
{
	if (!ptScreenBas)
	{
		return;
	}
	
#ifdef _USE_XMPUEQP_
	ReleaseXmpuAudBas(&ptScreenBas->m_tXmpuAudBas);
#else
	TAudBasParam tBasParam;
	tBasParam.SetParam(Inst()->GetInsID(), &ptScreenBas->m_tEqpRes);
	ReleaseEqpEx(&tBasParam);
#endif
}


#ifdef _USE_XMPUEQP_

BOOL32 CUmsBas::AssignXmpuBas(const TUmsVidFormat *pBasInParam, const TTPBasVidParam *pBasOutParam, tXmpuVidBasRes *pBasRes)
{
	CUmsConfInst* pInst = Inst();
	TXmpuBasParam  tBasParam;
	TXmpuEqpRes tRes;

	if(!pBasInParam || !pBasOutParam || !pBasRes)
	{
        return FALSE;
	}

	if (pBasRes->m_dwEqpID)
	{
        return FALSE;
	}
	
    tBasParam.m_emEqpType    = em_XmpuVidBas_Eqp;
    tBasParam.m_ptEqp        = &tRes;
	tBasParam.m_wConfID      = pInst->GetInsID();
	tBasParam.m_dwMediaIp    = pInst->m_tEqpConfDs.m_dwEqpIp;
    //tBasParam.m_wEncAbility
	tBasParam.m_tBasParam    = *pBasOutParam;
    tBasParam.m_tMaxBasParam = *pBasInParam;
	tBasParam.m_wStaticPayload  = MEDIA_TYPE_H264;
	tBasParam.m_wDynamicPayload = MEDIA_TYPE_H264;
	tBasParam.m_tEncrypt = pInst->GetConfEncryptInfo();

    if (!AssignXmpuEqp(&tBasParam))
	{
		return FALSE;
	}
	
	pBasRes->m_dwEqpID = tBasParam.m_ptEqp->m_dwEqpID;
	pBasRes->m_wConfID = pInst->GetInsID();
    pBasRes->m_emStat  = EmXmpuResStatInfo_Starting;

	pBasRes->m_tDecMiddleRtpAddr = tBasParam.m_tDecMiddleRtpAddr;
    pBasRes->m_tDecRtcpAddr      = tBasParam.m_tDecRtcpAddr;
    pBasRes->m_byEncChnNum       = pBasOutParam->m_byParamNum;

    memcpy(pBasRes->m_atEncRtpAddr, tBasParam.m_atEncRtpAddr, TP_CONF_MAX_MAIN_VIDEO_RES_NUM * sizeof(TTPTransAddr));
    memcpy(pBasRes->m_atEncMiddleRtcpAddr, tBasParam.m_atEncMiddleRtcpAddr, TP_CONF_MAX_MAIN_VIDEO_RES_NUM * sizeof(TTPTransAddr));

	return TRUE;
}

void CUmsBas::ReleaseXmpuBas(u8 byCapCount, tXmpuVidBasRes *pBasRes)
{
    if (!pBasRes || !byCapCount)
	{
        return;
	}

    TXmpuEqpParam tBas;
	TXmpuEqpRes	  tEqp;
	tBas.m_ptEqp = &tEqp;
	tBas.m_emEqpType = em_XmpuVidBas_Eqp;

	for (u16 wIndex = 0; wIndex < byCapCount; wIndex++)
	{
        tBas.m_ptEqp->m_dwEqpID = pBasRes[wIndex].m_dwEqpID;
		if (tBas.m_ptEqp->m_dwEqpID == 0)
		{
            continue;
		}

		ReleaseXmpuEqp( &tBas);

		if (pBasRes[wIndex].m_tMidAddrDs.GetElementNum() != 0)
		{
			CNetPortMgr::FreeMediaTrans(Inst(), pBasRes[wIndex].m_tMidAddrDs);
		}

        pBasRes[wIndex].Clear();
	}

	return;
}

void CUmsBas::OnXmpuVidBasStateNty(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	u16 wIndex = 0;

	if ( pInst->m_bIsQuiting || CUmsConfInst::inst_idle == pInst->CurState() )
	{//正在退出会议不处理
		return ;
	}

    TXmpuStartBasNty tStartBastNty;
	TXmpuSetBasEncNty tSetBasEncNty;
	u16 wEqpId;

    u16 wEvent = ptMsg->GetEvent();
	switch(wEvent)
	{
    case evXmpu_UmsStartVidBas_Nty:	
		TP_SAFE_CAST(tStartBastNty, ptMsg->GetBody());
		wEqpId = tStartBastNty.m_dwEqpID;
        break;
    case evXmpu_SetBasEncParam_Nty:
		TP_SAFE_CAST(tSetBasEncNty, ptMsg->GetBody());
		wEqpId = tSetBasEncNty.m_dwEqpID;
        break;
    case evXmpu_AskBasKey_Req:
		TP_SAFE_CAST(wEqpId, ptMsg->GetBody());
        break;
	case evXmpu_BasDisConnect_Nty:
		TP_SAFE_CAST(wEqpId, ptMsg->GetBody());
		break;

	default:
		return;
	}

	if (0 == wEqpId)
	{
		return;
	}

	do {
		for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (TRUE == m_tConfBasMgr.m_bSpeaker &&  wEqpId == m_cSpeaker.m_atXmpuBas[wIndex].m_dwEqpID)
			{
				HandleXmpuSpeakerVidBasStateNty(wEvent, pInst, &m_cSpeaker.m_atXmpuBas[wIndex], ptMsg->GetBody(), &wIndex );
   			    break;
			} else if (TRUE == m_tConfBasMgr.m_bChair && wEqpId == m_cChair.m_atXmpuBas[wIndex].m_dwEqpID)
			{
				HandleXmpuChairVidBasStateNty(wEvent, pInst, &m_cChair.m_atXmpuBas[wIndex], ptMsg->GetBody(), &wIndex );
				break;
			}
		}

		if (TRUE == m_tConfBasMgr.m_bDual && wEqpId == m_cDual.m_tXmpuBas.m_dwEqpID)
		{
			HandleXmpuDualVidBasStateNty(wEvent, pInst, &m_cDual.m_tXmpuBas, ptMsg->GetBody());
			break;
		}

		for(wIndex = 0; wIndex < BAS_CHN_RES_MAX_NUM; wIndex++)
		{
            if (m_tConfBasMgr.m_atBasChsRes[wIndex].m_tXmpuBas.m_dwEqpID == wEqpId)
			{
                tXmpuBasCbData tCbData;
                tCbData.pService = pInst;
                tCbData.pRes     = &m_tConfBasMgr.m_atBasChsRes[wIndex];
                tCbData.pData    = ptMsg->GetBody();
                tCbData.pParam   = m_tConfBasMgr.m_atBasChsRes[wIndex].m_pParam;

				m_tConfBasMgr.m_atBasChsRes[wIndex].m_pfCB(wEvent, &tCbData, NULL);
				break;
			}
		}

	} while(0);

    return;
}

void CUmsBas::OnXmpuAudBasStateNty(CTpMsg *const ptMsg)
{
	CUmsConfInst* pInst = Inst();
	u16 wIndex = 0;
	
	if ( pInst->m_bIsQuiting || CUmsConfInst::inst_idle == pInst->CurState() )
	{//正在退出会议不处理
		return ;
	}

    TXmpuStartAudBasNty tStartAudBasNty;
	BOOL32   bState;
	u16 wEqpId = 0;

	u16 wEvent = ptMsg->GetEvent();
	switch(wEvent)
	{
	case evXmpu_UmsStartAudBas_Nty:	
		TP_SAFE_CAST(tStartAudBasNty, ptMsg->GetBody());
		wEqpId = tStartAudBasNty.m_dwEqpID;
		break;
	case evXmpu_SetAudBasParam_Nty:
		TP_SAFE_CAST(bState, ptMsg->GetBody());
		//wEqpId = bState.m_dwEqpID;  updating.....
		break;
	case evXmpu_AudBasDisConnect_Nty:
		TP_SAFE_CAST(wEqpId, ptMsg->GetBody());
		break;

	default:
		return;
	}

	if (0 == wEqpId)
	{
		return;
	}

	do {
		for(wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex++)
		{
			if (wEqpId == m_atAudBasSpeaker[wIndex].m_tXmpuAudBas.m_dwEqpID)
			{
				HandleXmpuSpeakerAudBasStateNty(wEvent, pInst, &m_atAudBasSpeaker[wIndex].m_tXmpuAudBas, ptMsg->GetBody(), &wIndex );
				break;
			} else if (wEqpId == m_atAudBasChair[wIndex].m_tXmpuAudBas.m_dwEqpID)
			{
				HandleXmpuChairAudBasStateNty(wEvent, pInst, &m_atAudBasChair[wIndex].m_tXmpuAudBas, ptMsg->GetBody(), &wIndex );
				break;
			}
		}
		
		if (m_tAudBasDual.m_tXmpuAudBas.m_dwEqpID == wEqpId)
		{
		    HandleXmpuDualAudBasStateNty(wEvent, pInst, &m_tAudBasDual.m_tXmpuAudBas, ptMsg->GetBody());
			break;
		}
		
		if (m_tAudBasSpeakerMix.m_tXmpuAudBas.m_dwEqpID == wEqpId)
		{
			HandleXmpuSigleAudBasStateNty(wEvent, pInst, &m_tAudBasSpeakerMix.m_tXmpuAudBas, ptMsg->GetBody());
			break;
		}
			
	} while(0);

	return;
}


void CUmsBas::HandleXmpuSpeakerVidBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuVidBasRes* pBasRes, void* pData, void* param)
{
	u16 wScreenIndex = 0;
	if (param)
	{
		wScreenIndex = *(u16 *)param;
	}
	
	TXmpuStartBasNty tStartBastNty;
	u16 wEqpId;
	
	if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		memcpy(&tStartBastNty, pData, sizeof(tStartBastNty));  
		wEqpId = tStartBastNty.m_dwEqpID;
		if (!tStartBastNty.m_bSuccess)
		{
			pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
			
			MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuSpeakerVidBasStateNty. fail! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d, bSuccess:%d\n", 
				pInst->GetInsID(), wEqpId, wScreenIndex, tStartBastNty.m_bSuccess));
			return;
		}
		pBasRes->m_emStat = EmXmpuResStatInfo_Running;
		pInst->GetBas()->SetXmpuVidBasAssignAddr(pBasRes, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);
		CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, pBasRes);
		AdjustSpeakerBas();

			
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		// 

	} else if (dwType == evXmpu_AskBasKey_Req)
	{
		if ( pInst->GetVmp()->IsBrdVmp() && wScreenIndex == MIDSCREENINDEX  )
		{//广播合成 中间屏
			if (pInst->IsChairConf())
			{
				pInst->GetVmp()->AskFrameToBrdVmp(pInst->GetVmp()->GetConfBrdVmp(), pInst->curSpeakerID(), TRUE);
			}
			else
			{
				pInst->AskKeyByScreen(CALLER_EP_INDEX, MIDSCREENINDEX, EmAskKeyBrdVmp);
			}
		}
		else if (pInst->GetUmsDiscuss()->IsDiscussModle())
		{//其次讨论
			pInst->GetUmsDiscuss()->AskKeyFrameFromBas((u16)wScreenIndex);
		}
		else
		{
			pInst->AskKeyByScreen(pInst->curSpeakerID(), wScreenIndex, EmAskKeySpeaker);
		}
		
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
		memcpy(&wEqpId, pData, sizeof(wEqpId));  
		pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
		MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuSpeakerVidBasStateNty. BasDisConnect! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d.\n", 
			pInst->GetInsID(), wEqpId, wScreenIndex));
	}
	
}


void CUmsBas::HandleXmpuChairVidBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuVidBasRes* pBasRes, void* pData, void* param)
{
	u16 wScreenIndex = 0;
	if (param)
	{
        wScreenIndex = *(u16 *)param;
	}
	
	TXmpuStartBasNty tStartBastNty;
	u16 wEqpId;
	
	if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		memcpy(&tStartBastNty, pData, sizeof(tStartBastNty));  
		wEqpId = tStartBastNty.m_dwEqpID;
		if (!tStartBastNty.m_bSuccess)
		{
			pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
			
			MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuChairVidBasStateNty. fail! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d, bSuccess:%d\n", 
				pInst->GetInsID(), wEqpId, wScreenIndex, tStartBastNty.m_bSuccess));
			return;
		}
		pBasRes->m_emStat = EmXmpuResStatInfo_Running;
		pInst->GetBas()->SetXmpuVidBasAssignAddr(pBasRes, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);
		CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, pBasRes);
		AdjustChairBas();
		
		
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		//	
	} else if (dwType == evXmpu_AskBasKey_Req)
	{
		if (pInst->GetRollCallMgr()->IsRollCallModle())
		{
			u16 wRollCaller = pInst->GetRollCallMgr()->GetRollCallerEpId();
			if (pInst->IsChairConf())
			{
				pInst->AskKeyByScreen(wRollCaller, wScreenIndex, EmAskKeyChair);
			} 
			else 
			{
				if (NULL != pInst->GetNodeMgr()->GetCapsetNode(wRollCaller))
				{
					pInst->AskKeyByScreen(wRollCaller, wScreenIndex, EmAskKeyChair);
				}
				else
				{
					pInst->AskKeyByScreen(CALLER_EP_INDEX, wScreenIndex, EmAskKeyChair);
				}
			}
		}
		else
		{
			pInst->AskKeyByScreen(pInst->chairID(), wScreenIndex, EmAskKeyChair);
		}
		
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
		memcpy(&wEqpId, pData, sizeof(wEqpId));  
		pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
		
		MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuChairVidBasStateNty. BasDisConnect! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d.\n", 
			pInst->GetInsID(), wEqpId, wScreenIndex));	
   }
}

void CUmsBas::HandleXmpuDualVidBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuVidBasRes* pBasRes, void* pData)
{
	TXmpuStartBasNty tStartBastNty;
	u16 wEqpId;
	BOOL32 bError = FALSE;
	
	if (dwType == evXmpu_UmsStartVidBas_Nty)
	{
		memcpy(&tStartBastNty, pData, sizeof(tStartBastNty));  
		wEqpId = tStartBastNty.m_dwEqpID;
		if (!tStartBastNty.m_bSuccess)
		{
			bError = TRUE;
			MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuDualVidBasStateNty. fail! Stop Dual! ConfID:%d, EqpID:%d, bSuccess:%d\n", 
				pInst->GetInsID(), wEqpId, tStartBastNty.m_bSuccess));
		}
		pBasRes->m_emStat = EmXmpuResStatInfo_Running;
		pInst->GetBas()->SetXmpuVidBasAssignAddr(pBasRes, &tStartBastNty.m_tDecRtpAddr, tStartBastNty.m_atEncRtcpAddr, tStartBastNty.m_byEncNum);
		CNetPortMgr::AdjustXmpuMiddleAddrToVidBas(pInst, pBasRes);
		AssignDualBas();
		
	} else if (dwType == evXmpu_SetBasEncParam_Nty)
	{
		//
		
	} else if (dwType == evXmpu_AskBasKey_Req)
	{
		TUmsHandle tHandle;
		tHandle.MakeAppHandle(Inst()->GetInsID(), TP_INVALID_INDEX);
		BOOL32	bReqSys = TRUE;
		CTpMsg cMsg;
		cMsg.SetBody(&tHandle, sizeof(TUmsHandle));
		cMsg.CatBody(&bReqSys, sizeof(BOOL32));
		pInst->m_pcDual->OnAskKeyFrame(&cMsg);
		
	} else if (dwType == evXmpu_BasDisConnect_Nty)
	{
		memcpy(&wEqpId, pData, sizeof(wEqpId));  	
		MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuDualVidBasStateNty. BasDisConnect! Stop Dual! ConfID:%d, EqpID:%d.\n", 
			     pInst->GetInsID(), wEqpId));	
   }

	if(	bError)
	{	
		pInst->GetDualMgr()->OnStopDualCmdForUmcCnc();
	    pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Dual_BasDisCnnt, Inst()->chairID());
	}
}

void CUmsBas::HandleXmpuSpeakerAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData, void* param)
{
	u16 wScreenIndex = 0;
	if (param)
	{
		wScreenIndex = *(u16 *)param;
	}
	
	TXmpuStartAudBasNty tStartAudBasNty;
	u16 wEqpId;
	
	if (dwType == evXmpu_UmsStartAudBas_Nty)
	{
		memcpy(&tStartAudBasNty, pData, sizeof(tStartAudBasNty));  
		wEqpId = tStartAudBasNty.m_dwEqpID;
		if (!tStartAudBasNty.m_bSuccess)
		{
			pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
			
			MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuSpeakerAudBasStateNty. fail! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d, bSuccess:%d\n", 
				pInst->GetInsID(), wEqpId, wScreenIndex, tStartAudBasNty.m_bSuccess));
			return;
		}
		pBasRes->m_emStat = EmXmpuResStatInfo_Running;
		pInst->GetBas()->SetXmpuAudBasAssignAddr(pBasRes, &tStartAudBasNty.m_tDecRtpAddr, tStartAudBasNty.m_atEncRtcpAddr, AUD_BAS_MAX_OUT_CHNL_NUM);
		CNetPortMgr::AdjustXmpuMiddleAddrToAudBas(pInst, pBasRes);
		
	} else if (dwType == evXmpu_SetAudBasParam_Nty)
	{
		//
	} else if (dwType == evXmpu_AudBasDisConnect_Nty)
	{
		memcpy(&wEqpId, pData, sizeof(wEqpId));  
		pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
		
		MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuSpeakerAudBasStateNty. BasDisConnect! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d.\n", 
			pInst->GetInsID(), wEqpId, wScreenIndex));	
	}

}

void CUmsBas::HandleXmpuChairAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData, void* param)
{
	u16 wScreenIndex = 0;
	if (param)
	{
		wScreenIndex = *(u16 *)param;
	}
	
	TXmpuStartAudBasNty tStartAudBasNty;
	u16 wEqpId;
	
	if (dwType == evXmpu_UmsStartAudBas_Nty)
	{
		memcpy(&tStartAudBasNty, pData, sizeof(tStartAudBasNty));  
		wEqpId = tStartAudBasNty.m_dwEqpID;
		if (!tStartAudBasNty.m_bSuccess)
		{
			pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
			
			MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuChairAudBasStateNty. fail! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d, bSuccess:%d\n", 
				pInst->GetInsID(), wEqpId, wScreenIndex, tStartAudBasNty.m_bSuccess));
			return;
		}
		pBasRes->m_emStat = EmXmpuResStatInfo_Running;
		pInst->GetBas()->SetXmpuAudBasAssignAddr(pBasRes, &tStartAudBasNty.m_tDecRtpAddr, tStartAudBasNty.m_atEncRtcpAddr, AUD_BAS_MAX_OUT_CHNL_NUM);
		CNetPortMgr::AdjustXmpuMiddleAddrToAudBas(pInst, pBasRes);
		
	} else if (dwType == evXmpu_SetAudBasParam_Nty)
	{
		//
	} else if (dwType == evXmpu_AudBasDisConnect_Nty)
	{
		memcpy(&wEqpId, pData, sizeof(wEqpId));  
		pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
		
		MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuChairAudBasStateNty. BasDisConnect! Stop Conf! ConfID:%d, EqpID:%d, ScreenIndex:%d.\n", 
			pInst->GetInsID(), wEqpId, wScreenIndex));	
	}

}

void CUmsBas::HandleXmpuSigleAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData)
{
	TXmpuStartAudBasNty tStartAudBasNty;
	u16 wEqpId;
	
	if (dwType == evXmpu_UmsStartAudBas_Nty)
	{
		memcpy(&tStartAudBasNty, pData, sizeof(tStartAudBasNty));  
		wEqpId = tStartAudBasNty.m_dwEqpID;
		if (!tStartAudBasNty.m_bSuccess)
		{
			pInst->SelfHungupImmediately(TP_UMS_BasStartFail);
			
			MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuSigleAudBasStateNty. fail! Stop Conf! ConfID:%d, EqpID:%d, bSuccess:%d\n", 
				pInst->GetInsID(), wEqpId, tStartAudBasNty.m_bSuccess));
			return;
		}
		pBasRes->m_emStat = EmXmpuResStatInfo_Running;
		pInst->GetBas()->SetXmpuAudBasAssignAddr(pBasRes, &tStartAudBasNty.m_tDecRtpAddr, tStartAudBasNty.m_atEncRtcpAddr, AUD_BAS_MAX_OUT_CHNL_NUM);
		CNetPortMgr::AdjustXmpuMiddleAddrToAudBas(pInst, pBasRes);
		
	} else if (dwType == evXmpu_SetAudBasParam_Nty)
	{
		//

	} else if (dwType == evXmpu_AudBasDisConnect_Nty)
	{
		memcpy(&wEqpId, pData, sizeof(wEqpId));  
		pInst->SelfHungupImmediately(TP_UMS_BasDisConnect);
		
		MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuSigleAudBasStateNty. BasDisConnect! Stop Conf! ConfID:%d, EqpID:%d\n", 
			pInst->GetInsID(), wEqpId));	
	}
}

void CUmsBas::HandleXmpuDualAudBasStateNty(u32 dwType, CUmsConfInst *pInst, tXmpuAuddBasRes* pBasRes, void* pData)
{	
	TXmpuStartAudBasNty tStartAudBasNty;
	u16 wEqpId = 0;
	BOOL32 bError = FALSE;
	
	if (dwType == evXmpu_UmsStartAudBas_Nty)
	{
		memcpy(&tStartAudBasNty, pData, sizeof(tStartAudBasNty));  
		wEqpId = tStartAudBasNty.m_dwEqpID;
		if (!tStartAudBasNty.m_bSuccess)
		{
            bError = TRUE;
			MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuDualAudBasStateNty. fail! Stop Conf! ConfID:%d, EqpID:%d, bSuccess:%d\n", 
				pInst->GetInsID(), wEqpId, tStartAudBasNty.m_bSuccess));
		}
		pBasRes->m_emStat = EmXmpuResStatInfo_Running;
		pInst->GetBas()->SetXmpuAudBasAssignAddr(pBasRes, &tStartAudBasNty.m_tDecRtpAddr, tStartAudBasNty.m_atEncRtcpAddr, AUD_BAS_MAX_OUT_CHNL_NUM);
		CNetPortMgr::AdjustXmpuMiddleAddrToAudBas(pInst, pBasRes);
		
	} else if (dwType == evXmpu_SetAudBasParam_Nty)
	{
	

	} else if (dwType == evXmpu_AudBasDisConnect_Nty)
	{
        bError = TRUE;
		
		MdlError(Ums_Mdl_Call, ("CUmsBas::HandleXmpuDualAudBasStateNty. BasDisConnect! Stop Conf! ConfID:%d, EqpID:%d\n", 
			pInst->GetInsID(), wEqpId));	
	}

	if(bError)
	{
		pInst->GetDualMgr()->OnStopDualCmdForUmcCnc();
		pInst->NotifyReasonToUI( EmUI_CNC|EmUI_UMC, TP_UMS_Dual_BasDisCnnt, pInst->chairID());
	}
}

BOOL32 CUmsBas::AssignXmpuAudBas(const TUmsAudFormat *pBasInParam, const TUmsAudFormat *pBasOutParam, u16 dwOutCh, tXmpuAuddBasRes *pBasRes)
{
    TXmpuAudBasParam tBasParam;
	TXmpuEqpRes  tRes;
    CUmsConfInst* pInst = Inst();
	u16 dwMinOutCh = 0;

	if (!pBasInParam || !pBasOutParam || !dwOutCh ||!pBasRes)
	{
        return FALSE;
	}

	if (pBasRes->m_dwEqpID)
	{
        return FALSE;
	}

    tBasParam.m_ptEqp = &tRes;
	tBasParam.m_emEqpType = em_XmpuAudBas_Eqp;
	tBasParam.m_wConfID      = pInst->GetInsID();
	tBasParam.m_dwMediaIP    = pInst->m_tEqpConfDs.m_dwEqpIp;
    tBasParam.m_tEncrypt = pInst->GetConfEncryptInfo();

	memcpy(&tBasParam.m_tAudDec, pBasInParam, sizeof(TUmsAudFormat));	
    dwMinOutCh = localmin(dwOutCh, AUD_BAS_MAX_OUT_CHNL_NUM);
	memcpy(tBasParam.m_atAudEnc, pBasOutParam, sizeof(TUmsAudFormat) * dwMinOutCh);

    if (!AssignXmpuEqp(&tBasParam))
	{
		return FALSE;
	}

	pBasRes->m_dwEqpID = tBasParam.m_ptEqp->m_dwEqpID;
    pBasRes->m_wConfID = pInst->GetInsID();
    pBasRes->m_emStat  = EmXmpuResStatInfo_Starting;
    pBasRes->m_tDecMiddleRtpAddr  =  tBasParam.m_tDecMiddleRtpAddr;
    pBasRes->m_tDecRtcpAddr       =  tBasParam.m_tDecRtcpAddr;
	memcpy(pBasRes->m_atEncRtpAddr, tBasParam.m_atEncRtpAddr, AUD_BAS_MAX_OUT_CHNL_NUM * sizeof(TTPTransAddr));
    memcpy(pBasRes->m_atEncMiddleRtcpAddr, tBasParam.m_atEncMiddleRtcpAddr, AUD_BAS_MAX_OUT_CHNL_NUM * sizeof(TTPTransAddr));

	return TRUE;
}

void CUmsBas::ReleaseXmpuAudBas(tXmpuAuddBasRes *pBasRes)
{
    if (!pBasRes || !pBasRes->m_dwEqpID)
	{
        return ;
	}

	TXmpuEqpParam tBas;
	TXmpuEqpRes	  tEqp;
	tBas.m_ptEqp = &tEqp;
	tBas.m_emEqpType = em_XmpuAudBas_Eqp;

	tBas.m_ptEqp->m_dwEqpID = pBasRes->m_dwEqpID;
	ReleaseXmpuEqp( &tBas);

	if (pBasRes->m_tMidAddrDs.GetElementNum() != 0)
	{
		CNetPortMgr::FreeMediaTrans(Inst(), pBasRes->m_tMidAddrDs);	
	}

	pBasRes->Clear();

	return;
}

void CUmsBas::SetXmpuVidBasAssignAddr(tXmpuVidBasRes *pBasRes, TTPTransAddr *pDecRtpAddr, TTPTransAddr *pEncRtcpAddr, u16 wEncAddrNum)
{
    if (!pBasRes || !pDecRtpAddr || !pEncRtcpAddr || !wEncAddrNum)
	{
        return;
	}

    pBasRes->m_tDecRtpAddr = *pDecRtpAddr;
	u16 wEncChn = localmin(TP_CONF_MAX_MAIN_VIDEO_RES_NUM, wEncAddrNum);
	memcpy(pBasRes->m_atEncRtcpAddr, pEncRtcpAddr, wEncChn * sizeof(TTPTransAddr));

}

void CUmsBas::SetXmpuAudBasAssignAddr(tXmpuAuddBasRes *pBasRes, TTPTransAddr *pDecRtpAddr, TTPTransAddr *pEncRtcpAddr, u16 wEncAddrNum)
{
    if (!pBasRes || !pDecRtpAddr || !pEncRtcpAddr || !wEncAddrNum)
	{
        return;
	}
	
    pBasRes->m_tDecRtpAddr = *pDecRtpAddr;
	//u16 wEncChn = localmin(AUD_BAS_MAX_OUT_CHNL_NUM, wEncAddrNum);
	memcpy(pBasRes->m_atEncRtcpAddr, pEncRtcpAddr, AUD_BAS_MAX_OUT_CHNL_NUM * sizeof(TTPTransAddr));
}

#endif //_USE_XMPUEQP_

void CUmsBas::XmpuParseConfTempVidFormatAPI( TUmsVidFormat atVideoRes[], u16 wFormatNum, u16& wAdjustIndx, TUmsVidFormat& tNeedAdjustFmt )
{
	u16 wIndx = 0;

	wAdjustIndx = TP_INVALID_INDEX;
	tNeedAdjustFmt.m_emRes = emTPVResEnd;

	TUmsVidFormat* ptBpTmp = NULL;
	TUmsVidFormat* ptHpTmp = NULL;

	TUmsVidFormat* ptHp108060 = NULL;
	TUmsVidFormat* ptBp108060 = NULL;
	TUmsVidFormat* ptHp108030 = NULL;
	TUmsVidFormat* ptBp108030 = NULL;
	TUmsVidFormat* ptHp72060 = NULL;
	TUmsVidFormat* ptBp72060 = NULL;
	TUmsVidFormat* ptBpUXGA60 = NULL;
	u16 wHpNum = 0;
	u16 wBpNum = 0;

	do
	{
		u16 wEncRes = CTpTypeAdpt::CalcBasOutChnEncRes(wFormatNum, atVideoRes);
		if ( wEncRes <= BAS_ENCRES_1000 )
		{
			break;
		}
		for( wIndx = 0; wIndx < wFormatNum; wIndx ++  )
		{
	
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				ptHp108060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBp108060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_30 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				ptHp108030 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD1080p1920x1080 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_30 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBp108030 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD720p1280x720 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				ptHp72060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVHD720p1280x720 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBp72060 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emRes == emTPVGA1600x1200 &&
				atVideoRes[wIndx].m_wFrameRate == VID_FRAME_RATE_60 &&
				atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				ptBpUXGA60 = &atVideoRes[wIndx];
			}
			if ( atVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
			{
				wBpNum ++;
			}
			if ( atVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
			{
				wHpNum ++;
			}
		}

		if( ptHp108060 )
		{
			ptHpTmp = ptHp108060;
		}
		else if ( ptHp108030 )
		{
			ptHpTmp = ptHp108030;
		}
		else if ( ptHp72060 ) 
		{
			ptHpTmp = ptHp72060;
		}

		if( ptBp108060 )
		{
			ptBpTmp = ptBp108060;
		}
		else if ( ptBpUXGA60 )
		{
			ptBpTmp = ptBpUXGA60;
		}
		else if ( ptBp108030 )
		{
			ptBpTmp = ptBp108030;
		}
		else if ( ptBp72060 )
		{
			ptBpTmp = ptBp72060;
		}

		u16 wEncHp = CTpTypeAdpt::CalcBasOutChnEncRes(1, ptHpTmp);
		u16 wEncBp = CTpTypeAdpt::CalcBasOutChnEncRes(1, ptBpTmp);


		if ( IsMediaFormatSameLvl(atVideoRes, wFormatNum) )
		{//都是同Lvl的，最大格式不出
			if ( ptBpTmp )
			{
				ptBpTmp->m_emRes = emTPVResEnd;
			}
			else
			{
				ptHpTmp->m_emRes = emTPVResEnd;
			}
			break ;
		}

		if ( wHpNum <=1 && wBpNum <=1 )
		{
			u16 wIndexTmp = 1;
// 			if( wEncHp > wEncBp )
// 			{//BP
// 				wIndexTmp = 1;
// 			}

			wAdjustIndx = 0;

			tNeedAdjustFmt = atVideoRes[wIndexTmp];//分辨率小的，需要动态调整
			atVideoRes[wIndexTmp].m_emRes = emTPVResEnd;

			break;
		}
		else
		{
				if ( wHpNum > 1 )
				{
					if( wEncBp > wEncHp )
					{
						tNeedAdjustFmt = *ptHpTmp;
					}

					ptHpTmp->m_emRes = emTPVResEnd;
					wAdjustIndx = GetNeedAdjustIndx(atVideoRes, wFormatNum, ptBpTmp);
				}
				else if ( wBpNum > 1)
				{
					if( wEncHp > wEncBp )
					{
						tNeedAdjustFmt = *ptBpTmp;
					}

					ptBpTmp->m_emRes = emTPVResEnd;
					wAdjustIndx = GetNeedAdjustIndx(atVideoRes, wFormatNum, ptHpTmp);
				}
			
		}

		if( CTpTypeAdpt::CalcBasOutChnEncRes(wFormatNum, atVideoRes) > BAS_ENCRES_1500)
		{//此时还超过 1500说明选择了UXG60格式
			if ( ptBpUXGA60 )
			{//将UXGA转换为720p60
				ptBpUXGA60->m_emRes = emTPVHD720p1280x720;
				ptBpUXGA60->m_wFrameRate = VID_FRAME_RATE_60;
				ptBpUXGA60->m_emQualityLvl = emTPH264BP;
			}
		}
	}while(0);

	return ;
}

BOOL32 CUmsBas::IsSpeakBasAssigned()
{
	for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM ; ++wIndex)
	{
		if (EmXmpuResStatInfo_Running != m_cSpeaker.m_atXmpuBas[wIndex].m_emStat)
		{
			return FALSE;
		}	
	}
	return TRUE;
}

BOOL32 CUmsBas::IsChairBasAssigned()
{
	CUmsConfInst* pInst = Inst();
	TCapNode* ptChair = pInst->GetNodeMgr()->GetForeFatherNode(pInst->chairID());
	if (NULL == ptChair)
	{
		return FALSE;
	}
	//单屏主席，只用一个适配
	if ( ptChair->m_wVidSndNum == 1 )
	{
		if (EmXmpuResStatInfo_Running != m_cChair.m_atXmpuBas[MIDSCREENINDEX].m_emStat)
		{
			return FALSE;
		}	
	}
	else
	{
		for(u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM ; ++wIndex)
		{
			if (EmXmpuResStatInfo_Running != m_cChair.m_atXmpuBas[wIndex].m_emStat)
			{
				return FALSE;
			}	
		}
	}
	
	return TRUE;
}
