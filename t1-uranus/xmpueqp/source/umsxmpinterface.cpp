#include "umsxmpinterface.h"
#include "umsxmpuinst.h"
#include "xmpuinterface.h"
#include "jdconfig.h"

extern CUmsXmpuApp g_cUmsXmpuApp;
extern BOOL32	g_bXmpuInit;

BOOL32 AssignXmpuEqp( TXmpuEqpParam* ptParam)
{
	if (!g_bXmpuInit)
	{
		return FALSE;
	}
	CUmsXmpuInst* pInst = (CUmsXmpuInst*)((CApp*)&g_cUmsXmpuApp)->GetInstance(1);
	return pInst->AssignEqpEx(ptParam);
}

BOOL32 ReleaseXmpuEqp( TXmpuEqpParam* ptParam )
{
	if (!g_bXmpuInit)
	{
		return FALSE;
	}
	CUmsXmpuInst* pInst = (CUmsXmpuInst*)((CApp*)&g_cUmsXmpuApp)->GetInstance(1);
	return pInst->ReleaseEqpEx(ptParam);
}

BOOL32 InitXmpuMeeting( TXmpuMettingInfo tInfo )
{
	if (!g_bXmpuInit)
	{
		return FALSE;
	}
	CUmsXmpuInst* pInst = (CUmsXmpuInst*)((CApp*)&g_cUmsXmpuApp)->GetInstance(1);
	return pInst->InitMeeting(tInfo);
}

BOOL32 ReleaseXmpuMeeting( u32 wConfID )
{
	if (!g_bXmpuInit)
	{
		return FALSE;
	}
	CUmsXmpuInst* pInst = (CUmsXmpuInst*)((CApp*)&g_cUmsXmpuApp)->GetInstance(1);
	return pInst->ReleaseMeeting(wConfID);
}

BOOL32 InitMediaClient()
{
	CUmsXmpuInst* pInst = (CUmsXmpuInst*)((CApp*)&g_cUmsXmpuApp)->GetInstance(1);
	return pInst->InitMediaClient();
}

BOOL32 CheckIdleMediaSource(u16 wVmpNum, u16 wMix8Num, u16 wMix192Num)
{
	TJDInfo tJdInfo;
	CJDConfig::GetInstance()->GetFromConfigFile(tJdInfo); 
	TMediaEqpMgr tEqpMgr;
	GetMediaSource(tJdInfo.m_abyMqUrl, tJdInfo.m_abyMachineMoid, tEqpMgr);
	if ((wVmpNum >( tEqpMgr.m_dw264VmpCnt + tEqpMgr.m_dw265_264VmpCnt)) || (wMix8Num > tEqpMgr.m_dwMixer8Cnt) || (wMix192Num > tEqpMgr.m_dwMixer192Cnt))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}