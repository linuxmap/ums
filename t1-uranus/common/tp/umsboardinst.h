#ifndef _h_umsboardinst_h__
#define _h_umsboardinst_h__


#include "tpobject.h"
#include "tphandle.h"
#include "tpsys.h"
#include "umscommonstruct.h"
#include "umsinnerstruct.h"
#include "umsboardcfg.h"

#define UPDATE_SUCCESS			0			//升级成功
#define UPDATE_APP_ERROR		1			//app 升级错误
#define UPDATE_0S_ERROR			2			//OS 升级错误
#define UPDATE_BOOT_ERROR		3			//Boot 升级错误
#define UPDATE_SET_FLAG_ERROR	4			//Set Flag 升级错误
#define UPDATE_ERROR			-1			//升级失败

typedef void (*StartCallBack)(u32 dwNode);
BOOL StartBoardServer(EMBrdType emBrdType, StartCallBack callBack, StartCallBack ReCallBcak = NULL);
void StopBoardServer();
u8	 GetBrdLayer();
u8	 GetBrdSlot();

class CTpBoardServer :  public CTpObject
{
public:
	CTpBoardServer();
	~CTpBoardServer();
protected:
	BOOL32		m_bInit;
protected:
	virtual BOOL32	ObjectInit(u32 wParam, u32 lParam);
	virtual void	ObjectExit();
	void	InstanceDump(u32 wParam);
protected:
	virtual void	MessageProc(CTpMsg *const ptMsg);

	void	Init();
	void	OnDisConnect(CTpMsg *const ptMsg);
	void	OnBrdRegSuccess(CTpMsg *const ptMsg);
	void	OnBrdRegNack(CTpMsg *const ptMsg);
	void	OnBrdGetCfgAck(CTpMsg *const ptMsg);
	void	OnBrdGetCfgNack(CTpMsg *const ptMsg);
	void	OnBrdRebootCmd(CTpMsg *const ptMsg);
	void	OnBrdSetSysTime(CTpMsg *const ptMsg);
	void	OnBrdUpdate(CTpMsg *const ptMsg);
	void	OnBrdGetVer(CTpMsg *const ptMsg);
	void	OnTaskReturn(CTpMsg *const ptMsg);
	void	ShowBrdCfg();

	void    OnBrdSwitch(CTpMsg *const ptMsg);    //telnet ftp

private:
	void	SendMsgToEqp(u16 wEvent, u8 * const pbyMsg = NULL, u16 wLen = 0 );
	s8*		BoardGetHardwareVer();
	s8*		BoardGetSoftwareVer();

	void    SwitchTelnetFtp(EmBoardSwitchType emBrdSwitchType,BOOL32 bBrdSwitch);                    //开关Telnet Ftp    
public:
	EMBrdType	GetBrdType() { return m_tBrdCfg.m_tBrdPos.m_emBrdType; } //获取板子类型
	u32			GetNode() { return m_tBrdCfg.m_dwUmsNode; }
private:
	BOOL32		ConnectToUms();
	u16			CountArrayIndex(TTPBrdPos tPos);
public:

	u32		m_dwWdGuardTime;
protected:
	TBrdCfgBase	m_tBrdCfg;
private:
	BOOL32		m_bIsUpdate;
	EMEqpType	m_emEqpMdl;
	
};

typedef zTemplate<CTpBoardServer, 1> CTpUmsBoardApp;


//升级线程类
class CTaskUpdate
{
public:
	CTaskUpdate();
	~CTaskUpdate();
public:
	BOOL32		BrdFileIsUngz(s8 * const sFileName); //板子升级文件是否为压缩包
	BOOL32		UpdateDavinciLinuxSys(s8 * const szFileName); //.gz包升级
	BOOL32		UpdateDavinciLinuxSys_Ungz(s8 * const szFileName); //.bin包升级
	BOOL32		CheckBrdUpdatePackage(s8 *pszFileName); //板子升级包的校验
	BOOL32		BoardSysUpGrade(s8* pszFileName);  //板子升级
	BOOL32		BoardRemoveFile(const s8* pszFileName);  //删除文件
	s8*			GetBoardRandomInfo(s8* pszFileName);		//获取相应板子的冗余信息

public:
	s8*			GetUpdateName() { return m_achFileName; }
	void		SetUpdateName(s8* pszName) { memcpy(m_achFileName, pszName, sizeof(m_achFileName)); }
	EMBrdType	GetBrdType() { return m_emBrdType; }
	void		SetBrdType(EMBrdType emType) { m_emBrdType = emType; }
public:
	void		Clear();
private:
	s8			m_achFileName[TP_UPGRADE_FILENAME_LENGTH];
	EMBrdType	m_emBrdType;
};
#endif