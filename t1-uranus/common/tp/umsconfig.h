#ifndef _h_umsconfig_h__
#define _h_umsconfig_h__

#include "tpstruct.h"
#include "umscommonstruct.h"
#include "tplog.h"
#include "umsinnerstruct.h"

using namespace UmsTpmsg;

enum EmUmsFile
{
	emUmsCfg = 0,
	emUmsCfgEx,
	emUmsExeFile,
	emUmsExceptionFile,
	emUmsUserMgrFile,
	emUmsTpFile,
	emUmsTpDownLoadFile,
	emUmsTpFolder,
	emUmsTpControlFile,
	emUmsAddrBookFile,
	emUmsLogCfgFile,
	emUmsTpDownTemplateFile,
	emUmsTpDownControlFile,
	emUmsserverLog4cplusCfg,
	emUmsLog4cpExeFile,
	emUmsLog4cpExceptionFile,
	emUmsConfig,
};

//本地ums描述
typedef struct tagTLocalUmsInfo
{
	TTPEthnetInfo	m_tEth;    //UMS IP
	TTPEthnetInfo   m_tVirEth;
	TTPEthnetInfo   m_tEth1;
	TTPEthnetInfo   m_tVirEth1;
	u16				m_wListionPortForUi;		//UI侦听结点
	u16				m_wBeginUdpTransPort;		//UDP传输起始端口
	u16				m_wNumMaxOnecCall;			//会议中，每次最大呼叫数量
	u32_ip			m_dwUmsoldIP; 
	tagTLocalUmsInfo(){ memset( this, 0, sizeof(struct tagTLocalUmsInfo) ); }
}TLocalUmsInfo;

s8* UmsGetFileName(EmUmsFile type);
BOOL UmsMakeDir(const s8* path );

//系统初始化函数
BOOL InitUmsCfg(void);
//退出系统
void QuitUmsCfg(void);
//由于UMS在修改IP后可能会5秒后重启，因此，UMS在修改IP后，触发一下立即写文件的操作
void ImmediatelySave(void);

//获取ums IP
BOOL umsGetLocalUmsIP( u32& dwIp );
//判断是不是本机ip
BOOL32 IsLocalUmsIP(u32& dwIp);
//获取ums EthInfo
BOOL umsGetLocalEthInfo( TTPEthnetInfo& tEth );
BOOL umsGetLocalVirEthInfo( TTPEthnetInfo& tEth );
BOOL umsGetLocalEth1Info( TTPEthnetInfo& tEth );
BOOL umsGetLocalVirEth1Info( TTPEthnetInfo& tEth );
//设置ums EthInfo
BOOL umsSetLocalEthInfo( const TTPEthnetInfo& tEth ,EmEthInfoType& emEthType);
//保存ums的旧ip
BOOL32 SetUmsOldIP();
BOOL32 GetUmsOldip(u32& dwIp);

//获取SIP配置
BOOL umsGetSipRegCfg(TTPSipRegistrarCfg& tSipRegCfg);
//设置SIP配置
BOOL umsSetSipRegCfg(const TTPSipRegistrarCfg& tSipRegCfg);

//获取GK配置
BOOL umsGetGKRegCfg(TTPGKCfg& tGKRegCfg);
//设置GK配置
BOOL umsSetGKRegCfg(const TTPGKCfg& tGKRegCfg);

BOOL umsSetUmsStackCfg(const TUmsStackCallCfg& tStackCfg);
BOOL umsGetUmsStackCfg(TUmsStackCallCfg& tStackCfg);

//获取umsserver的侦听结点，
BOOL umsGetUmsListenPortCfg(u16& Port);

//获取码流传输起始端口号
BOOL umsGetStartUdpPortCfg(u16& Port);

//获取会议一次最大呼叫数量
BOOL umsGetMaxOnceCallCfg(u16& Num);

//电视墙配置
BOOL umsGetHduCfg(u16 wIndex, THduCfgInfo& tInfo);
BOOL umsSetHduCfg(u16 wIndex, const THduCfgInfo& tInfo);

//电视墙风格配置
BOOL umsGetHduStyle(THduStyleCfgInfo& tHduStyle);
BOOL umsSetHduStyle(const THduStyleCfgInfo& tHduStyle);
//修改单板信息
BOOL32 umsGetBoardInfo(TTPBrdInfo& tBrdCfg, u16 wBrdIndex);
BOOL32 umsSetBoardInfo(const TTPBrdInfo& tBrdCfg, u16 wBrdIndex);
//单板模式
BOOL32 umsGetBrdModeInfo(TTPEqpCfg& tEqpCfg, u16 wIndex);
BOOL32 umsSetBrdModeInfo(const TTPEqpCfg& tEqpCfg, u16 wIndex);
//单板有效数量
BOOL32 umsGetBrdInvalidNum(u8& byNum);
BOOL32 umsSetBrdInvalidNum(const u8& byNum);


//qt
BOOL32 umsSetQTEncryptInfo( const TTPQTEncryptInfo &tTPQTEncryptInfo );
BOOL32 umsGetQTEncryptInfo( TTPQTEncryptInfo &tTPQTEncryptInfo );
//qt
BOOL32 umsSetPwdCycleInfo( const TPwdCycleInfo &tTPQTEncryptInfo );
BOOL32 umsGetPwdCycleInfo( TPwdCycleInfo &tTPQTEncryptInfo );
// ntpd
BOOL32 umsSetNtpdInfo( const TNtpdInfo &tNtpdInfo );
BOOL32 umsGetNtpdInfo( TNtpdInfo &tNtpdInfo );

void SetHostFile(s8* pszIp);
void SetGKConfigFile(s8* pszIp);

API void  ResetAllData();
API void  SaveData();


#endif//_h_umsconfig_h__

