#include "umshdu.h"
#include "tplog.h"

CHduChannelEx::CHduChannelEx() 
{ 	
	Clear(); 
}

CHduChannelEx::~CHduChannelEx() {}

void CHduChannelEx::Init(const THduChanInfo& tInfo)
{
//	m_bVmpChan = tInfo.m_bVmp;
	m_emOutPortType = tInfo.m_emOutPortType;
	m_emOutModeType = tInfo.m_emOutModeType;
	m_emShowMode = tInfo.m_emShowMode;
	m_emZoomRate = tInfo.m_emZoomRate;
}

void CHduChannelEx::Clear()
{
	m_byVol = 0;
	m_bMute = FALSE;
	m_bVmpChan = FALSE;
	m_emOutPortType = em_hdu_outport_unknow;
	m_emOutModeType = em_hdu_outmode_unknow;
	m_emZoomRate = em_hdu_zoomrate_unknow;
	m_emShowMode = em_hdu_showmode_unknow;

	for (u16 wIndex = 0; wIndex < HDU_MAX_VMP_SUBCHAN; ++wIndex)
	{
		m_atPlayInfo[wIndex].Clear();
	}
}

void CHduChannelEx::GetCfgInfo(THduChanInfo& tInfo)
{
	tInfo.m_bVmp = m_bVmpChan;
	tInfo.m_emOutModeType = m_emOutModeType;
	tInfo.m_emOutPortType = m_emOutPortType;
	tInfo.m_emShowMode = m_emShowMode;
	tInfo.m_emZoomRate = m_emZoomRate;
}

BOOL32 CHduChannelEx::ValidPlayInfo(u8 bySubChanIndex) const
{
	if (bySubChanIndex >= HDU_MAX_VMP_SUBCHAN)
	{
		return FALSE;
	}
	else
	{
		return EmEpType_Invalid != m_atPlayInfo[bySubChanIndex].m_emType;
	}
}

void CHduChannelEx::SetChanStatus(u8 bySubChanIndex, EmHduChanStatus emStatus)
{
	if (bySubChanIndex >= HDU_MAX_VMP_SUBCHAN)
	{
		return ;
	}
	else
	{
		m_atPlayInfo[bySubChanIndex].m_emStatus = emStatus;
	}
}

void CHduChannelEx::SetPlayInfo(u8 bySubChanIndex, const TPlayInfo& tInfo)
{
	if (bySubChanIndex >= HDU_MAX_VMP_SUBCHAN)
	{
		return ;
	}
	else
	{
		m_atPlayInfo[bySubChanIndex] = tInfo;
	}
}

void CHduChannelEx::ClearPlayInfo(u8 bySubChanIndex)
{

	if (bySubChanIndex >= HDU_MAX_VMP_SUBCHAN)
	{
		return ;
	}
	else
	{
		m_atPlayInfo[bySubChanIndex].Clear();
	}
}

BOOL32 CHduChannelEx::UseStatus() const
{
	for (u8 byIndex = 0; byIndex < HDU_MAX_VMP_SUBCHAN; ++byIndex)
	{
		if (EmEpType_Invalid != m_atPlayInfo[byIndex].m_emType)
		{
			return TRUE;
		}
	}

	return FALSE;
}

TPlayInfo CHduChannelEx::GetPlayInfo(u8 bySubChanIndex) const
{
	if (bySubChanIndex >= HDU_MAX_VMP_SUBCHAN)
	{
		return TPlayInfo();
	}
	else
	{
		return m_atPlayInfo[bySubChanIndex];
	}
}

EmHduChanStatus CHduChannelEx::GetChanStatus(u8 bySubChanIndex) const
{
	if (bySubChanIndex >= HDU_MAX_VMP_SUBCHAN)
	{
		return em_hdu_chan_invalid;
	}
	else
	{
		return m_atPlayInfo[bySubChanIndex].m_emStatus;
	}
}

CHduEx::CHduEx()
{
	for (u8 byChan = 0; byChan < HDU_MAX_CHANNEL_NUM; ++byChan)
	{
		m_acChannel[byChan].SetChanID(byChan);
	}
	ClearBrdInfo(); 
}

CHduEx::~CHduEx()
{ }

void CHduEx::Init(const THduCfgInfo& tInfo)
{
	m_byLayer = tInfo.m_byLayer;
	m_bySlot = tInfo.m_bySlot;
	m_dwIP = tInfo.m_dwIP;
	m_emBrdType = (tInfo.m_bQtHdu)?em_hdu2_qt_brd : em_hdu2_brd;

	m_tName.SetAlias(tInfo.m_tName.m_abyAlias);
	for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
	{
		m_acChannel[byIndex].Init(tInfo.m_atChanInfo[byIndex]);
	}
	m_wStartPort = tInfo.m_wStartPort;
}

void CHduEx::GetCfgInfo(THduCfgInfo& tInfo)
{
	for (u16 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
	{
		m_acChannel[byIndex].GetCfgInfo(tInfo.m_atChanInfo[byIndex]);
	}
	tInfo.m_byChanNum = HDU_MAX_CHANNEL_NUM;
	tInfo.m_byLayer = m_byLayer;
	tInfo.m_bySlot = m_bySlot;
	tInfo.m_dwIP = m_dwIP;
	tInfo.m_tName.SetAlias(m_tName.m_abyAlias);
	tInfo.m_wStartPort = m_wStartPort;
	tInfo.m_bQtHdu = (m_emBrdType == em_hdu2_qt_brd)?TRUE:FALSE;
}

void CHduEx::Dump() const
{
	msgprintnotime("Layer:%d, Slot:%d, BrdType:%d "IPFORMAT", BrReg:%d, ServiceReg:%d, Name:%s, StartPort:%d.\n",
					m_byLayer, m_bySlot, m_emBrdType, Tpu32ToIP(m_dwIP), m_bBrdReg, m_bServiceReg, m_tName.m_abyAlias, m_wStartPort);
	for (u16 wIndex = 0; wIndex < HDU_MAX_CHANNEL_NUM; wIndex++)
	{
		msgprintnotime("  ChanId:%d, Vmp:%d, Vol:%d, Mute:%d.\n", m_acChannel[wIndex].m_byChanID, m_acChannel[wIndex].m_bVmpChan, 
			m_acChannel[wIndex].m_byVol, m_acChannel[wIndex].m_bMute);
	}
	msgprintnotime("hdu:%d, addr0:%d, addr1:%d\n", this, &m_acChannel[0], &m_acChannel[1]);
	msgprintnotime("\n");
}

void CHduEx::SetBrdInfo(const TTPBrdPos& tInfo)
{
	m_byLayer = tInfo.m_byBrdLayer;
	m_bySlot = tInfo.m_byBrdSlot;
	m_dwIP = tInfo.m_dwBrdIP;
	m_emBrdType = tInfo.m_emBrdType;
}

void CHduEx::ClearBrdInfo()
{
	m_byLayer = HDU_MAX_LAYER;
	m_bySlot = HDU_MAX_SLOT;
	m_dwIP = 0;
	m_bBrdReg = FALSE;

	m_bServiceReg = FALSE;
	m_wStartPort = 0;
	m_tName.Clear();
	
	ClearServiceInfo();
}

BOOL32 CHduEx::ValidBrd() const
{
	return HDU_MAX_LAYER != m_byLayer && HDU_MAX_SLOT != m_bySlot;
}

void CHduEx::SetServiceInfo(const THduChanInfo atInfo[], const TTPName& tName)
{
	m_tName.SetAlias(tName.m_abyAlias);
	for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
	{
		m_acChannel[byIndex].Init(atInfo[byIndex]);
	}
}

CHduChannelEx* CHduEx::GetChannel(u8 byChanID)
{
	if (byChanID >= HDU_MAX_CHANNEL_NUM)
	{
		return NULL;
	}
	else
	{
		return &(m_acChannel[byChanID]);
	}
}

void CHduEx::ClearServiceInfo()
{
	m_tName.Clear();
	for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
	{
		m_acChannel[byIndex].Clear();
	}
}

void CHduEx::GetCfgInfo(THduCfg& tInfo)
{
	tInfo.m_bBrdReg = m_bBrdReg;
	tInfo.m_bServiceReg = m_bServiceReg;
	tInfo.m_byChanNum = HDU_MAX_CHANNEL_NUM;
	tInfo.m_byLayer = m_byLayer;
	tInfo.m_bySlot = m_bySlot;
	tInfo.m_dwIP = m_dwIP;
	tInfo.m_tName.SetAlias(m_tName.m_abyAlias);
	tInfo.m_emBrdType = m_emBrdType;
	
	for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
	{
		m_acChannel[byIndex].GetCfgInfo(tInfo.m_atChanInfo[byIndex]);
	}
}

BOOL32 CHduEx::IsHaveVmpChan()
{
	if (m_bServiceReg)
	{
		for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
		{
			if (m_acChannel[byIndex].IsVmpChan())
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

CHduPlan::CHduPlan() 
{
	Clear();
}

CHduPlan::~CHduPlan()
{

}


void CHduPlan::Init(u8 byRow, u8 byCol, const THduPlayUnit atUnit[])
{
	m_byRow = byRow;
	m_byCol = byCol;

	for (u16 wIndex = 0; wIndex < byRow * byCol; ++wIndex)
	{
		m_atUnit[wIndex].m_pcHdu = atUnit[wIndex].m_pcHdu;
		m_atUnit[wIndex].m_pcChannel = atUnit[wIndex].m_pcChannel;
		m_atUnit[wIndex].m_tName.SetAlias(atUnit[wIndex].m_tName.m_abyAlias);
	}
}

void CHduPlan::Clear()
{
	m_byRow = 0;
	m_byCol = 0;

	for (u16 wIndex = 0; wIndex < HDU_STYLE_MAX_NUM; ++wIndex)
	{
		m_atUnit[wIndex].m_pcHdu = NULL;
		m_atUnit[wIndex].m_pcChannel = NULL;
		m_atUnit[wIndex].m_wIndex = wIndex;
		m_atUnit[wIndex].m_tName.Clear();
	}
}

THduPlayUnit* CHduPlan::FindChannel(u8 byLayer, u8 bySlot, u8 byChanID)
{
	CHduEx* pcHdu = NULL;
	CHduChannelEx* pcChannel = NULL;
	for (u16 wIndex = 0; wIndex < m_byRow * m_byCol; ++wIndex)
	{
		pcHdu = m_atUnit[wIndex].m_pcHdu;
		pcChannel = m_atUnit[wIndex].m_pcChannel;
		if (NULL != pcHdu && NULL != pcChannel)
		{
			if (byLayer == pcHdu->Layer() && bySlot == pcHdu->Slot() && byChanID == pcChannel->GetChanID())
			{
				return &(m_atUnit[wIndex]);
			}
		}
	}

	return NULL;
}

u16 CHduPlan::GetValidNum() const
{
	u16 wNum = 0;

	for (u16 wIndex = 0; wIndex < m_byRow * m_byCol; ++wIndex)
	{
		if (NULL != m_atUnit[wIndex].m_pcHdu && NULL != m_atUnit[wIndex].m_pcChannel &&
			m_atUnit[wIndex].m_pcChannel->UseStatus())
		{
			++wNum;
		}
	}
	
	return wNum;
}

void CHduPlan::Dump() const
{
	u8 byChanID = 0;
	TPlayInfo tInfo;
	msgprintnotime("Row:%d, Col:%d.\n\n", m_byRow, m_byCol);
	for (u16 wIndex = 0; wIndex < m_byRow * m_byCol; ++wIndex)
	{
		if (NULL != m_atUnit[wIndex].m_pcHdu && NULL != m_atUnit[wIndex].m_pcChannel)
		{
			msgprintnotime("Index:%d, Layer:%d, Slot:%d, ChanID:%d, Vmp:%d, Name:%s.\n", 
							wIndex, m_atUnit[wIndex].m_pcHdu->Layer(), m_atUnit[wIndex].m_pcHdu->Slot(),
							m_atUnit[wIndex].m_pcChannel->GetChanID(), m_atUnit[wIndex].m_pcChannel->IsVmpChan(),m_atUnit[wIndex].m_tName.m_abyAlias);

			if (m_atUnit[wIndex].m_pcChannel->IsVmpChan())
			{
				for (byChanID = 0; byChanID < HDU_MAX_VMP_SUBCHAN; byChanID++)
				{
					tInfo = m_atUnit[wIndex].m_pcChannel->GetPlayInfo(byChanID);
					msgprintnotime("  SubChan:%d, ConfID:%d, DstID:%d, ScreenNum:%d, Type:%d, Status:%d.\n",
						byChanID, tInfo.m_wConfID, tInfo.m_wDstID, tInfo.m_wScreenNum, tInfo.m_emType, tInfo.m_emStatus);
				}
			}
			else
			{
				byChanID = 0;
				tInfo = m_atUnit[wIndex].m_pcChannel->GetPlayInfo(byChanID);
				msgprintnotime("  SubChan:%d, ConfID:%d, DstID:%d, ScreenNum:%d, Type:%d, Status:%d.\n",
						byChanID, tInfo.m_wConfID, tInfo.m_wDstID, tInfo.m_wScreenNum, tInfo.m_emType, tInfo.m_emStatus);
			}
		}
		msgprintnotime("hduaddr:%d, chanaddr:%d.\n", m_atUnit[wIndex].m_pcHdu, m_atUnit[wIndex].m_pcChannel);
		msgprintnotime("\n");
	}
}

THduPlayUnit* CHduPlan::GetChannel(u16 wIndex)
{
	if (wIndex >= m_byRow * m_byCol)
	{
		return NULL;
	}
	else
	{
		if (NULL == m_atUnit[wIndex].m_pcHdu || NULL == m_atUnit[wIndex].m_pcChannel)
		{
			return NULL;
		}
		else
		{
			return &(m_atUnit[wIndex]);
		}
	}
}

BOOL32 CHduPlan::SetHduName(u16 wIndex,s8* pszName)
{
	if (wIndex >= m_byRow * m_byCol)
	{
		return FALSE;
	}
	if (NULL == pszName)
	{
		return FALSE;
	}
	if (NULL == m_atUnit[wIndex].m_pcHdu || NULL == m_atUnit[wIndex].m_pcChannel)
	{
		return FALSE;
	}

	m_atUnit[wIndex].m_tName.SetAlias(pszName);
	return TRUE;
 
}

s8* CHduPlan::GetHduName(u16 wIndex)
{
	if (wIndex >= m_byRow * m_byCol)
	{
		return FALSE;
	}

	return m_atUnit[wIndex].m_tName.m_abyAlias;

}