#ifndef _TEST_MODE_H_
#define _TEST_MODE_H_

#include "osp.h"
#include "tptestcommon.h"

class CTestClientInstance : public CInstance
{
public:
	enum EmInstState
	{
		inst_idle,
		inst_run,
	};
public:
	CTestClientInstance();
	~CTestClientInstance();

public:
	virtual void DaemonInstanceEntry(CMessage *const pMsg, CApp* pcApp);
	virtual void InstanceEntry(CMessage *const pMsg){}

	virtual void DaemonInstanceDump(u32 = 0);

private:

	void EventLoginReq(CMessage *const pMsg);
	void EventTestComDataReq(CMessage *const pMsg);
	void EventTestIODataReq(CMessage *const pMsg);

	void EventLoginQuit(CMessage *const pMsg);
	void EventDisConnect(CMessage *const pMsg);

	void Show();

	void ClearClient();
private:
	u32		m_dwClientIp;
	u32		m_dwClientAppInstId;
	u32		m_dwClientNode;
	s8		m_szClientName[TEST_MODE_CLIEN_NAME_LEN+1];
};

typedef zTemplate<CTestClientInstance, 1>	CTestClientApp;

API void help();
API void quit();
API void showtest();
API void logon();
API void logoff();

//for local test
API void login();
API void loginout();
API void sendcom();
API void sendio();

API void showsock();
API void setdstip(s8* szIp);
API void testudp(s8* szData, u16 wPort);

// ≥ı ºªØ
API void TestServerInit();

#endif//_TEST_MODE_H_
