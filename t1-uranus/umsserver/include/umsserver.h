#ifndef _h_umsapp_h__
#define _h_umsapp_h__

#include "umsobject.h"
#include "tphandle.h"

using namespace UmsTpmsg;

enum EmAppState
{
	AppIdle ,//����
	AppStarting,//��������
	AppRunning//����
};

class CTpTimerMgr;
class CTpUmsServer :  public CUmsObject
{
public:
    CTpUmsServer();

protected:
	
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit();

public:
	enum EmService
	{
		_CUmsConfTemplateHandleService,
		_CUmsCallHandleService,
		_CUmsRegHandleService,
		_CUmsToolHandleService,
		_CUmsHduHandleService,
		_CUmsBoardHandleService,
		_CUmsLicenseService,
		EndService,
	};

public:
	static u32	  GetLocalIP()	
	{
		return m_dwLocalIP;
	}

    static s8*        GetSubServiceName(u8 byIndex)
	{
		if( byIndex >= EndService )
			return NULL;
		return m_apcServiceName[byIndex];
    }

	//��ȡ����
	CTpHandler*     GetService(EmService emService)
	{
		if( emService >= EndService )
			return NULL;
		return m_apcService[emService];
	}

	u32 AddTimer(u32 dwInterval, u32 pCallBack, void* context);
	s32 DelTimer(u32 dwTime);
	
	void NotifySelf(u16 wEvent, u8* pData, u16 wDataSize);
	void NotifyCall(u16 wEvent, u8* pData, u16 wDataSize);

	void EvStartModule();

	BOOL32 EvUserLogin(CTpMsg *const ptMsg);
	BOOL32 EvSetIpCfg(CTpMsg *const ptMsg);
	BOOL32 EvSetSysTime(CTpMsg *const ptMsg);
	BOOL32 EvGetSysTime(CTpMsg *const ptMsg);

	BOOL32 EvProcQTmsg(CTpMsg *const ptMsg);
	BOOL32 EvProcCfgExmsg(CTpMsg *const ptMsg);
    BOOL32 EvSetQTEncryptInfoCmd(CTpMsg *const ptMsg);
	BOOL32 EvSetPwdCycleInfo(CTpMsg *const ptMsg);

	BOOL32 EvNtpdCfgInfo(CTpMsg *const ptMsg);
	BOOL32 DownloadLogInfo(CTpMsg *const ptMsg);
public:
	//�������汾
	s8*		GetSoftVersion();
	//���Ӳ���汾
	s8*		GetHardVersion();

protected:
	virtual void InstanceDump(u32=0);
	
protected:
	BOOL32 OnTick();

protected:
	void MessageProc(CTpMsg *const ptMsg);
	BOOL32 ForEach(CTpMsg *const ptMsg);
	BOOL32 BroadCast(CTpMsg *const ptMsg);
	BOOL32 OnModulRun(CTpMsg *const ptMsg);
	BOOL32 IsAllAppRuning();//ȫ��Ӧ���Ƿ�����

	void  SysReboot(void);

protected:
	CTpHandler*		m_apcService[EndService];
	u32				m_dwWdGuardTime;    //ι����ʱ�����(��λ:ms)
	CTpTimerMgr*	m_pcTimerMgr;
	
protected:
	static s8*			m_apcServiceName[EndService];
	static u32			m_dwLocalIP;		//���ص�ַ
	static EmAppState	m_emCallApp;
	static EmAppState	m_emEqpApp;
	static EmAppState	m_emXmpuApp;
};

typedef zTemplate<CTpUmsServer, 1> CTpUmsServerApp;





#endif // _h_umsapp_h__
