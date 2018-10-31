#ifndef _h_umsboardcfg_h__
#define _h_umsboardcfg_h__

#include "tpsys.h"
#include "umsboardcfg.h"
#include "tpstruct.h"
#include "kdvsys.h"
#include "umsxmltype.h"
#include "tplog.h"

typedef  struct tagTBrdCfgBase
{
	u32			m_dwUmsNode;
	u32			m_dwUmsListenIp;
	u16			m_wUmsListenPort;
	u32			m_dwHardVer;   //Ó²¼þ°æ±¾ºÅ
	TTPBrdPos	m_tBrdPos;
	
	tagTBrdCfgBase()
	{
		m_dwUmsNode = INVALID_NODE;
		m_dwUmsListenIp = 0;
		m_wUmsListenPort = UMS_LISTIONPORT_CMS;
		m_dwHardVer = 0;
		m_tBrdPos.Clear();
	}
	void Clear()
	{
		tagTBrdCfgBase();
	}
	void Disconnect()
	{
		m_dwUmsNode = INVALID_NODE;
	}
	u16 GetBrdIndex(TTPBrdPos tBrd)
	{
		return (tBrd.m_byBrdLayer * TP_BOARD_MAX_SLOT + tBrd.m_byBrdSlot);
	}

	EMBrdType GetBrdType()
	{
		return (m_tBrdPos.m_emBrdType);
	}
}TBrdCfgBase;

void		ReadBrdCfgBaseInfo();
void		WriteDefautCfgToFile();
TBrdCfgBase	GetBrdCfgBase();
void		SetBrdCfgBase(const TBrdCfgBase& tCfg);
EMBrdType	ConverBrdID(u32 dwID);

#endif