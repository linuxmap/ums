#include "commonapi.h"

u16 CComInterface::GetNeedBasNum(TPIN const TUmsConfBase& tConfBasse)
{
	u16 wBasNum = 0;
	u16 wFormatNum = 0;

	TUmsVidFormat m_atVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	memcpy(&m_atVideoRes[0], &tConfBasse.m_atTpMainVideoRes[0], sizeof(TUmsVidFormat)*tConfBasse.m_wMainNum);
	wFormatNum = CheckAndProcConfTempFormat(m_atVideoRes, tConfBasse.m_wMainNum);

	if ( wFormatNum <= 1 )
	{
		wBasNum = 0;
	}
	else if ( wFormatNum == 2 )
	{
		if ( IsConfTempSameLvl(tConfBasse) )
		{
			wBasNum =  3 + 3 ; // 发言人 + 看主席
		}
		else
		{
			wBasNum = 3 + 3 ; //发言人 + 看主席
		}
	}
	else
	{
		wBasNum = 3 + 3 ; //发言人 + 看主席
	}

	return wBasNum;
}

u16 CComInterface::GetNeedAudBasNum(TPIN const TUmsConfBase& tConfBasse)
{
	u16 wBasNum = 0;
	u16 wFormatNum = tConfBasse.m_wAudFmtNum;

	if ( wFormatNum <= 1 )
	{
		wBasNum = 0;
	}
	else
	{
		wBasNum = 3 + 1 + 3 ; //发言人 + 混音 + 主席
	}
	
	return wBasNum;
}

BOOL32 CComInterface::IsConfTempSameLvl(const TUmsConfBase& tConfBasse)
{
	BOOL32 bHp = FALSE;
	BOOL32 bBp = FALSE;
	for (u16 wIndx = 0; wIndx < tConfBasse.m_wMainNum; wIndx ++ )
	{
		if( tConfBasse.m_atTpMainVideoRes[wIndx].m_emQualityLvl == emTPH264BP )
		{
			bBp = TRUE;
		}
		if( tConfBasse.m_atTpMainVideoRes[wIndx].m_emQualityLvl == emTPH264HP )
		{
			bHp = TRUE;
		}
	}
	
	if ( bBp && bHp )
	{
		//hp bp都存在
		return FALSE;
	}
	return TRUE;
}

u16 CComInterface::CheckAndProcConfTempFormat( TUmsVidFormat atVidFormat[], u16 wNum )
{
	u16				wIndx = 0;
	u16				wFormatNum = 0;
	TUmsVidFormat	atTmpVidFormat[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];
	TUmsVidFormat*	ptFormat = NULL;
	
	//合并筛选
	for ( wIndx = 0; wIndx < wNum; wIndx ++ )
	{
		ptFormat = &atVidFormat[wIndx];
		
		if ( ptFormat->m_emRes == emTPVResEnd )
		{
			continue;
		}
		
		for ( u16 wSecIndx = 0; wSecIndx < wNum; wSecIndx ++ )
		{
			if ( wSecIndx == wIndx )
			{
				continue;
			}
			
			if ( ptFormat->m_emRes != atVidFormat[wSecIndx].m_emRes ||
				ptFormat->m_emQualityLvl != atVidFormat[wSecIndx].m_emQualityLvl )
			{
				continue;
			}
			
			//两者分辨率相差 10 以内 可以认为是一种适配格式
			if(ptFormat->m_wFrameRate > atVidFormat[wSecIndx].m_wFrameRate)
			{
				if(ptFormat->m_wFrameRate - atVidFormat[wSecIndx].m_wFrameRate <= 60 - 50)
				{
					atVidFormat[wSecIndx].m_emRes = emTPVResEnd;
				}
			}
			else
			{
				if( atVidFormat[wSecIndx].m_wFrameRate - ptFormat->m_wFrameRate <= 60 - 50)
				{
					atVidFormat[wSecIndx].m_emRes = emTPVResEnd;
				}
			}
		}
	}
	
	memcpy(atTmpVidFormat, atVidFormat, sizeof(TUmsVidFormat)*wNum);
	memset(atVidFormat, 0, sizeof(TUmsVidFormat)*wNum);
	
	//全部整理成60 30等标准帧率格式
	for ( wIndx = 0; wIndx < wNum; wIndx ++ )
	{
		if(atTmpVidFormat[wIndx].m_emRes == emTPVResEnd)
		{
			continue;
		}
		
		if ( atTmpVidFormat[wIndx].m_wFrameRate == 50 )
		{
			atTmpVidFormat[wIndx].m_wFrameRate = 60;
		}
		
		if ( atTmpVidFormat[wIndx].m_wFrameRate == 25 )
		{
			atTmpVidFormat[wIndx].m_wFrameRate = 30;
		}
		
		memcpy(&atVidFormat[wFormatNum++], &atTmpVidFormat[wIndx], sizeof(TUmsVidFormat));
	}
	return wFormatNum;
}

