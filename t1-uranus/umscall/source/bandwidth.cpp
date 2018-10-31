#include "bandwidth.h"

void CBandwidth::StartConf( u32 wUpBW, u32 wDownBW )
{
#ifdef _WIN32
	if ( wUpBW == 0 )
	{
		m_wUpBWCfg = TP_INVALID_INDEX;
	}
	else
	{
		m_wUpBWCfg = wUpBW;
	}
	if ( wDownBW == 0 )
	{
		m_wDownBWCfg = TP_INVALID_INDEX;
	}
	else
	{
		m_wDownBWCfg = wDownBW;
	}
	return ;
#endif
	m_wUpBWCfg = wUpBW;
	m_wDownBWCfg = wDownBW;
}

void CBandwidth::StopConf()
{
	memset(this, 0, sizeof(CBandwidth));
}

BOOL32 CBandwidth::AssigneUpBW( u32 wBW, EmViewType eType )
{
	if(!IsUpBw(wBW) || eType >= em_View_End)
	{
		return FALSE;
	}

	m_wUpBW += wBW;

	m_atUpBW[eType].m_wBW += wBW;

	return TRUE;
}

BOOL32 CBandwidth::AssigneDownBW( u32 wBW, EmViewType eType )
{
	if(!IsDownBw(wBW) || eType >= em_View_End)
	{
		return FALSE;
	}
	
	m_wDownBW += wBW;
	
	m_atDownBW[eType].m_wBW += wBW;
	
	return TRUE;
}

void CBandwidth::ReleaseUpBW( u32 wBW, EmViewType eType )
{
	if(eType >= em_View_End || wBW > m_wUpBW || wBW > m_atUpBW[eType].m_wBW )
	{
		return ;
	}

	m_wUpBW -= wBW;
	
	m_atUpBW[eType].m_wBW -= wBW;

	return;
}

void CBandwidth::ReleaseDownBW( u32 wBW, EmViewType eType )
{
	if(eType >= em_View_End || wBW > m_wDownBW || wBW > m_atDownBW[eType].m_wBW )
	{
		return ;
	}
	
	m_wDownBW -= wBW;
	
	m_atDownBW[eType].m_wBW -= wBW;
}

u32 CBandwidth::GetBwInfoByType( EmViewType eType )
{
	return 0;
}

s8* GetTypeRes(EmViewType emType)
{
	switch(emType)
	{
	case em_View_SelView:
		return "SelView";
	case em_View_TV:
		return "TvWall";
	case em_View_Dis:
		return "Dis";
	case em_View_Poll:
		return "Poll";
	case em_View_Vmp:
		return "Vmp";
	}
	return "InvalidEnd";
}

void CBandwidth::ShowBW()
{
	msgprintnotime(" UpCfg:%d, DownCfg:%d, Up:%d, Down:%d\n", m_wUpBWCfg, m_wDownBWCfg, m_wUpBW, m_wDownBW);

	for ( u32 dwIndex = 0; dwIndex < em_View_End; dwIndex ++ )
	{
		msgprintnotime(" Type:%s, Up:%d, Down:%d\n", GetTypeRes((EmViewType)dwIndex), m_atUpBW[dwIndex].m_wBW, m_atDownBW[dwIndex].m_wBW);
	}
}
