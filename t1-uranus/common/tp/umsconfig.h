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

//����ums����
typedef struct tagTLocalUmsInfo
{
	TTPEthnetInfo	m_tEth;    //UMS IP
	TTPEthnetInfo   m_tVirEth;
	TTPEthnetInfo   m_tEth1;
	TTPEthnetInfo   m_tVirEth1;
	u16				m_wListionPortForUi;		//UI�������
	u16				m_wBeginUdpTransPort;		//UDP������ʼ�˿�
	u16				m_wNumMaxOnecCall;			//�����У�ÿ������������
	u32_ip			m_dwUmsoldIP; 
	tagTLocalUmsInfo(){ memset( this, 0, sizeof(struct tagTLocalUmsInfo) ); }
}TLocalUmsInfo;

s8* UmsGetFileName(EmUmsFile type);
BOOL UmsMakeDir(const s8* path );

//ϵͳ��ʼ������
BOOL InitUmsCfg(void);
//�˳�ϵͳ
void QuitUmsCfg(void);
//����UMS���޸�IP����ܻ�5�����������ˣ�UMS���޸�IP�󣬴���һ������д�ļ��Ĳ���
void ImmediatelySave(void);

//��ȡums IP
BOOL umsGetLocalUmsIP( u32& dwIp );
//�ж��ǲ��Ǳ���ip
BOOL32 IsLocalUmsIP(u32& dwIp);
//��ȡums EthInfo
BOOL umsGetLocalEthInfo( TTPEthnetInfo& tEth );
BOOL umsGetLocalVirEthInfo( TTPEthnetInfo& tEth );
BOOL umsGetLocalEth1Info( TTPEthnetInfo& tEth );
BOOL umsGetLocalVirEth1Info( TTPEthnetInfo& tEth );
//����ums EthInfo
BOOL umsSetLocalEthInfo( const TTPEthnetInfo& tEth ,EmEthInfoType& emEthType);
//����ums�ľ�ip
BOOL32 SetUmsOldIP();
BOOL32 GetUmsOldip(u32& dwIp);

//��ȡSIP����
BOOL umsGetSipRegCfg(TTPSipRegistrarCfg& tSipRegCfg);
//����SIP����
BOOL umsSetSipRegCfg(const TTPSipRegistrarCfg& tSipRegCfg);

//��ȡGK����
BOOL umsGetGKRegCfg(TTPGKCfg& tGKRegCfg);
//����GK����
BOOL umsSetGKRegCfg(const TTPGKCfg& tGKRegCfg);

BOOL umsSetUmsStackCfg(const TUmsStackCallCfg& tStackCfg);
BOOL umsGetUmsStackCfg(TUmsStackCallCfg& tStackCfg);

//��ȡumsserver��������㣬
BOOL umsGetUmsListenPortCfg(u16& Port);

//��ȡ����������ʼ�˿ں�
BOOL umsGetStartUdpPortCfg(u16& Port);

//��ȡ����һ������������
BOOL umsGetMaxOnceCallCfg(u16& Num);

//����ǽ����
BOOL umsGetHduCfg(u16 wIndex, THduCfgInfo& tInfo);
BOOL umsSetHduCfg(u16 wIndex, const THduCfgInfo& tInfo);

//����ǽ�������
BOOL umsGetHduStyle(THduStyleCfgInfo& tHduStyle);
BOOL umsSetHduStyle(const THduStyleCfgInfo& tHduStyle);
//�޸ĵ�����Ϣ
BOOL32 umsGetBoardInfo(TTPBrdInfo& tBrdCfg, u16 wBrdIndex);
BOOL32 umsSetBoardInfo(const TTPBrdInfo& tBrdCfg, u16 wBrdIndex);
//����ģʽ
BOOL32 umsGetBrdModeInfo(TTPEqpCfg& tEqpCfg, u16 wIndex);
BOOL32 umsSetBrdModeInfo(const TTPEqpCfg& tEqpCfg, u16 wIndex);
//������Ч����
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

