#include "umsconfigex.h"
#include "umsconfig.h"
#include "kdvsys.h"
#include "tpsys.h"
#include "tplog.h"


static const u8 FILE_NAME_LEN = 255;
static s8  g_ConfigExFile[FILE_NAME_LEN] = {0};

static const s8 umsSec[] = "FastUpdate";
//每多少秒对终端向广播源的关键帧请求次数重新计算
static const s8 mtKeyBeginFastUpdateInterval[] ="BeginFastUpdateInterval";
//设定的时间间隔内有效的请求次数, 如果超过这个数字就不发关键帧请求给广播源
static const s8 mtKeyBeginFastUpdateNeglectNum[] ="BeginFastUpdateNeglectNum";

//每多少秒对终端向广播源的关键帧请求次数重新计算
static const s8 mtKeyFastUpdateInterval[] ="FastUpdateInterval";
//设定的时间间隔内有效的请求次数, 如果超过这个数字就不发关键帧请求给广播源
static const s8 mtKeyFastUpdateNeglectNum[] ="FastUpdateNeglectNum";


static const s8	umsSecRSParam[] = "umsRSParamSec";
static const s8 umsKeyRsFirstTime[] = "umsFirstTime";
static const s8 umsKeyRsSecondTime[] = "umsSecondTime";
static const s8 umsKeyRsThirdTime[] = "umsThirdTime";
static const s8 umsKeyRsRejectTime[] = "umsRejectTime";

static const s8 umsCallLevel[]         = "umsCallLevel";
static const s8 umsKeyIpCallLevel[]    = "umsIpCallLevel";
static const s8 umsKeyE164CallLevel[]  = "umsE164CallLevel";
static const s8 umsKeyAliasCallLevel[] = "umsAliasCallLevel";

static const s8	umsSecMixMotive[] = "umsSecMixMotive";
static const s8 umssKeyMixProtectedTime[] = "umsMixProtectedTime";

// 四个混音器分组配置
static const s8 umsMixOneNum[] = "umsMixOneNum";
static const s8 umsMixTwoNum[] = "umsMixTwoNum";
static const s8 umsMixThreeNum[] = "umsMixThreeNum";
static const s8 umsMixFourNum[] = "umsMixFourNum";

//ums输出打印区
static const s8 umsSecPrint[] = "umsSecPrint";
static const s8 umsKeyPirntState[] = "umsPrintState";

//ums外设启用开关
static const s8 umsSecEqpMgr[] = "umsSecEqpMgr";
static const s8 umsKeyVmpUsed[] = "umsVmpUsed";
static const s8 umsKeyXmpu5Used[] = "umsXmpu5Used";

//电视墙最后显示画面
static const s8 TvWallSecLastPic[] = "TvWallSecLastPic";
static const s8 TvWallKeyLastPic[] = "TvWallLastPic";  

//是否启用虚拟轮询结点
static const s8 VirSecPoll[] = "VirSecPoll";
static const s8 VirPoll[] = "VirPoll";

//是否启用级联
static const s8 CasecadeSecMcu[]="CasecadeSecMcu";
static const s8 CasecadeMcu[]="CasecadeMcu";

//平台的合成和适配 25/50是否强制编30/60
static const s8 UmsSecEnc3060[] = "UmsSecEnc3060";
static const s8 UmsEnc3060Bas[] = "UmsEnc3060Bas";
static const s8 UmsEnc3060Vmp[] = "UmsEnc3060Vmp";


static const s8 UmsDiscussDebug[] = "UmsDiscussDebug";
static const s8 UmsDelayTime[] = "UmsDelayTime";

static const s8 UmsMpu2tpNetBandDebug[] = "UmsMpu2tpNetBandDebug";
static const s8 Mpu2tpNetBandMul[] = "Mpu2tpNetBandMul";
static const s8 VmptpStyleUp[] = "VmptpStyleUp";

//是否开启ftp
static const s8 UmsSecFtp[] = "UmsSecFtp";
static const s8 UmsFtpOn[] = "UmsFtpOn";


static const s8 UmsSecDualMix[] = "UmsSecDualMix";
static const s8 DualMixOn[] = "DualMixOn";



#define IsValidCallLevel(Calllevel)     ((Calllevel) < emTPCallLevelFirst || (Calllevel) > emTpCallLevelThird)


CUmsConfigEx* CUmsConfigEx::m_pcInstance = NULL;
void CUmsConfigEx::ShowAll()
{
	msgprintnotime("\n\n[umsConfingEx]\n");
	msgprintnotime("%s = %d\n","FastUpdateInterval",m_dwFastUpdateInterval);
	msgprintnotime("%s = %d\n","UpdateNeglectNum",m_dwFastUpdateNeglectNum);

	msgprintnotime("%s = %d\n","BeginFastUpdateInterval",m_dwBeginFastUpdateInterval);
	msgprintnotime("%s = %d\n\n","BeginUpdateNeglectNum",m_dwBeginFastUpdateNeglectNum);
	
	msgprintnotime("%s = %d\n",umsKeyRsFirstTime,m_dwRsFirstTime);
	msgprintnotime("%s = %d\n",umsKeyRsSecondTime,m_dwRsSecondTime);
	msgprintnotime("%s = %d\n",umsKeyRsThirdTime,m_dwRsThirdTime);
	msgprintnotime("%s = %d\n\n",umsKeyRsRejectTime,m_dwRsRejectTime);


	msgprintnotime("%s = %d\n\n", umsKeyPirntState, m_bIsPrintToCom);

	msgprintnotime("%s = %d\n\n", umsKeyVmpUsed, m_bVmpUsed);
	msgprintnotime("%s = %d\n\n", umsKeyXmpu5Used, m_bXmpu5Used);

	msgprintnotime("%s = %d\n\n", TvWallKeyLastPic, m_wTvWallLastPic);

	msgprintnotime("%s = %d\n\n", VirPoll, m_bVirPoll);

	msgprintnotime("%s = %d\n\n",CasecadeMcu, m_bCasecadeMcu);

	msgprintnotime("%s = %d\n", UmsEnc3060Bas, m_bEnc3060Bas);
	msgprintnotime("%s = %d\n\n", UmsEnc3060Vmp, m_bEnc3060Vmp);

	msgprintnotime("%s = %d\n\n", UmsDelayTime, m_dwDelayTime);
	msgprintnotime("%s = %d\n\n", Mpu2tpNetBandMul, m_dwmpu2tpNetBandMul);
	msgprintnotime("%s = %d\n\n", VmptpStyleUp, m_bVmptpStyleUp);

	msgprintnotime("%s = %d\n",umsKeyIpCallLevel,m_wIpCallLvl);
	msgprintnotime("%s = %d\n",umsKeyE164CallLevel,m_wE164CallLvl);
	msgprintnotime("%s = %d\n\n",umsKeyAliasCallLevel,m_wAliasCallLvl);

	msgprintnotime("%s = %d\n",umssKeyMixProtectedTime, m_nMixProtectedTime);
	msgprintnotime("UmsApu2tpMixCfgDebug = %d,%d,%d,%d.\n\n", m_wApu2MixNumOne, m_wApu2MixNumTwo, m_wApu2MixNumThree, m_wApu2MixNumFour);

	msgprintnotime("%s = %d\n\n",DualMixOn,m_bdualmix);//dual 混音开关信息

}

BOOL32 CUmsConfigEx::ReadFromFile()
{
	s32 dwVal;

	GetRegKeyInt(g_ConfigExFile,umsSec,mtKeyBeginFastUpdateInterval, 5, &dwVal);
	m_dwBeginFastUpdateInterval = (u16)dwVal;
	GetRegKeyInt(g_ConfigExFile,umsSec,mtKeyBeginFastUpdateNeglectNum, 1, &dwVal);
	m_dwBeginFastUpdateNeglectNum = (u16)dwVal;
	if (m_dwBeginFastUpdateNeglectNum > TP_KEYFRAME_STATIS)
	{
		m_dwBeginFastUpdateNeglectNum = TP_KEYFRAME_STATIS;
	}

    GetRegKeyInt(g_ConfigExFile,umsSec,mtKeyFastUpdateInterval, 30, &dwVal);
	m_dwFastUpdateInterval = (u16)dwVal;
	GetRegKeyInt(g_ConfigExFile,umsSec,mtKeyFastUpdateNeglectNum, 3, &dwVal);
	m_dwFastUpdateNeglectNum = (u16)dwVal;
	if (m_dwFastUpdateNeglectNum > TP_KEYFRAME_STATIS)
	{
		m_dwFastUpdateNeglectNum = TP_KEYFRAME_STATIS;
	}

	GetRegKeyInt(g_ConfigExFile,umsSecRSParam,umsKeyRsFirstTime, 40, &dwVal);
	m_dwRsFirstTime = (u16)dwVal;
	GetRegKeyInt(g_ConfigExFile,umsSecRSParam,umsKeyRsSecondTime, 80, &dwVal);
	m_dwRsSecondTime = (u16)dwVal;
	GetRegKeyInt(g_ConfigExFile,umsSecRSParam,umsKeyRsThirdTime, 120, &dwVal);
	m_dwRsThirdTime = (u16)dwVal;
	GetRegKeyInt(g_ConfigExFile,umsSecRSParam,umsKeyRsRejectTime, 2000, &dwVal);
	m_dwRsRejectTime = (u16)dwVal;

	GetRegKeyInt(g_ConfigExFile,umsCallLevel,umsKeyIpCallLevel, emTPCallLevelFirst, &dwVal);
	m_wIpCallLvl    = (u16)dwVal;
	GetRegKeyInt(g_ConfigExFile,umsCallLevel,umsKeyE164CallLevel, emTPCallLevelSecond, &dwVal);
	m_wE164CallLvl  = (u16)dwVal;
	GetRegKeyInt(g_ConfigExFile,umsCallLevel,umsKeyAliasCallLevel, emTpCallLevelThird, &dwVal);
	m_wAliasCallLvl = (u16)dwVal;
	
	if (IsValidCallLevel(m_wIpCallLvl) || IsValidCallLevel(m_wE164CallLvl) || IsValidCallLevel(m_wAliasCallLvl)||
		m_wIpCallLvl == m_wE164CallLvl || m_wIpCallLvl == m_wAliasCallLvl || m_wE164CallLvl == m_wAliasCallLvl)
	{
		m_wIpCallLvl     =  emTPCallLevelFirst;
		m_wE164CallLvl   =  emTPCallLevelSecond;
		m_wAliasCallLvl  =  emTpCallLevelThird;
	}

	if (GetRegKeyInt(g_ConfigExFile, umsSecMixMotive, umssKeyMixProtectedTime, 4, &dwVal))
	{
		m_nMixProtectedTime = dwVal;
	}

	if (GetRegKeyInt(g_ConfigExFile, umsSecMixMotive, umsMixOneNum, 34, &dwVal))
	{
		m_wApu2MixNumOne = (u16)(dwVal==1?0:dwVal);
	}
	
	if (GetRegKeyInt(g_ConfigExFile, umsSecMixMotive, umsMixTwoNum, 10, &dwVal))
	{
		m_wApu2MixNumTwo = (u16)(dwVal==1?0:dwVal);
	}
	
	if (GetRegKeyInt(g_ConfigExFile, umsSecMixMotive, umsMixThreeNum, 10, &dwVal))
	{
		m_wApu2MixNumThree = (u16)(dwVal==1?0:dwVal);
	}
	
	if (GetRegKeyInt(g_ConfigExFile, umsSecMixMotive, umsMixFourNum, 10, &dwVal))
	{
		m_wApu2MixNumFour = (u16)(dwVal==1?0:dwVal);
	}
	
	u16 wMixNum = m_wApu2MixNumOne+m_wApu2MixNumTwo+m_wApu2MixNumThree+m_wApu2MixNumFour;
	if (wMixNum != 64)
	{
		m_wApu2MixNumOne = 34;
		m_wApu2MixNumTwo = 10;
		m_wApu2MixNumThree = 10;
		m_wApu2MixNumFour = 10;
	}


	if (GetRegKeyInt(g_ConfigExFile, umsSecPrint, umsKeyPirntState, FALSE, &dwVal))
	{
		m_bIsPrintToCom = (BOOL32)dwVal;
	}

	if (GetRegKeyInt(g_ConfigExFile, umsSecEqpMgr, umsKeyVmpUsed, TRUE, &dwVal))
	{
		m_bVmpUsed = (BOOL32)dwVal;
	}

	if (GetRegKeyInt(g_ConfigExFile, TvWallSecLastPic, TvWallKeyLastPic, 0, &dwVal))
	{
		m_wTvWallLastPic = (u16)dwVal;
		if (TWLP_SHOW_BLACK_MODE != m_wTvWallLastPic && TWLP_SHOW_DEFPIC_MODE != m_wTvWallLastPic 
			&& TWLP_SHOW_LASTFRAME_MODE != m_wTvWallLastPic && TWLP_SHOW_USERDEFPIC_MODE != m_wTvWallLastPic)  
			m_wTvWallLastPic = TWLP_SHOW_DEFPIC_MODE;  
	}

	if (GetRegKeyInt(g_ConfigExFile, VirSecPoll, VirPoll, 0, &dwVal))
	{
		m_bVirPoll = (BOOL32)dwVal;
	}
	if (GetRegKeyInt(g_ConfigExFile,CasecadeSecMcu,CasecadeMcu,0,&dwVal))
	{
		m_bCasecadeMcu=(BOOL32)dwVal;
	}
	if (GetRegKeyInt(g_ConfigExFile, UmsSecEnc3060, UmsEnc3060Bas, FALSE, &dwVal))
	{
		m_bEnc3060Bas = (BOOL32)dwVal;
	}

	if (GetRegKeyInt(g_ConfigExFile, UmsSecEnc3060, UmsEnc3060Vmp, FALSE, &dwVal))
	{
		m_bEnc3060Vmp = (BOOL32)dwVal;
	}

	if (GetRegKeyInt(g_ConfigExFile, UmsDiscussDebug, UmsDelayTime, 1500, &dwVal))
	{
		m_dwDelayTime = dwVal;
	}

	if (GetRegKeyInt(g_ConfigExFile, UmsMpu2tpNetBandDebug, Mpu2tpNetBandMul, 20, &dwVal))
	{
		m_dwmpu2tpNetBandMul = (u32)dwVal;
	}

	//dual mix
	if (GetRegKeyInt(g_ConfigExFile, UmsSecDualMix, DualMixOn, 0, &dwVal))
	{
		m_bdualmix = (BOOL32)dwVal;
	}
	if (GetRegKeyInt(g_ConfigExFile, UmsMpu2tpNetBandDebug, VmptpStyleUp, FALSE, &dwVal))
	{
		m_bVmptpStyleUp = (BOOL32)dwVal;
	}
	
	if (GetRegKeyInt(g_ConfigExFile, umsSecEqpMgr, umsKeyXmpu5Used, TRUE, &dwVal))
	{
		m_bXmpu5Used = (BOOL32)dwVal;
	}
	return TRUE;
}


CUmsConfigEx* CUmsConfigEx::GetInstance()
{
	if ( NULL == m_pcInstance )
	{
		m_pcInstance = new CUmsConfigEx;
		if ( NULL == m_pcInstance )
		{
			msgprint( "[CUmsConfigEx::GetInstance]m_pcInstance mem alloc failed!\n" );
			return NULL;
		}
	}
	
	if( !m_pcInstance->m_bIsInited )
	{
		strncpy(g_ConfigExFile,UmsGetFileName(emUmsCfgEx),sizeof(s8)*FILE_NAME_LEN);
		m_pcInstance->m_bIsInited = m_pcInstance->ReadFromFile();
	}
    //当文件读取失败时返回默认值
	return m_pcInstance;
};






