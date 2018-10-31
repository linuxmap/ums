#ifndef _TEST_MODE_H_
#define _TEST_MODE_H_

#include "osp.h"
#include "tptestcommon.h"
#include "tptestapi.h"

class CLockSemHandle
{
public:
	CLockSemHandle(){
		OspSemBCreate(&m_semLock);
	}
	virtual ~CLockSemHandle(){
		OspSemDelete(m_semLock);
	}

	void LOCK(){
		OspSemTake(m_semLock);
	}

	void UNLOCK(){
		OspSemGive(m_semLock);
	}

private:
	SEMHANDLE m_semLock;
};

class CTPSHandleManger
{
public:

	virtual ~CTPSHandleManger(){
		if (NULL!=m_pcInst){
			delete m_pcInst;
			m_pcInst = NULL;
		}
	}

	// handle从1开始，最大为TPSSDKHANDLE_MAX_NUM
	// 分配使用数量最少的
	u16 AssignHandle(u32 dwIp){
		m_cLock.LOCK();
		int wIndexRet = 0;

		do 
		{
			if (0 == dwIp){
				break;
			}

			u16 wIndex;
			BOOL32 bExit = FALSE;
			for (wIndex = 0; wIndex < TPTESTHANDLE_MAX_NUM; wIndex++){
				if (dwIp == m_adwRemoteIP[wIndex]){
					bExit = TRUE;
					break;
				}
			}

			if (bExit){
				break;
			}

			u32 dwNumTemp = 0xfffffffe;
			for (wIndex = 0; wIndex < TPTESTHANDLE_MAX_NUM; wIndex++){
				if (0 == m_adwRemoteIP[wIndex] && m_adwUseNum[wIndex] < dwNumTemp){
					dwNumTemp = m_adwUseNum[wIndex];
					wIndexRet = wIndex+1;
				}
			}

		} while (0);

		if (0 != wIndexRet){
			m_adwRemoteIP[wIndexRet-1] = dwIp;
			m_adwUseNum[wIndexRet-1]++;
		}

		m_cLock.UNLOCK();
		return wIndexRet;
	}

	BOOL32 ReleaseHandle(u16 hHandle){
		m_cLock.LOCK();
		BOOL32 bRet = FALSE;
		do 
		{
			if (!IS_VAILD_TPTESTHANDLE(hHandle)){
				break;
			}

			if (0 != m_adwRemoteIP[hHandle-1]){
				m_adwRemoteIP[hHandle-1] = 0;
				m_bLogined[hHandle-1] = FALSE;
				bRet = TRUE;
			}

		} while (0);
		m_cLock.UNLOCK();
		return bRet;
	}

	void SetLoginOk(u16 hHandle){
		m_cLock.LOCK();
		do 
		{
			if (!IS_VAILD_TPTESTHANDLE(hHandle)){
				break;
			}

			if (0 != m_adwRemoteIP[hHandle-1]){
				m_bLogined[hHandle-1]=TRUE;
			}

		} while (0);
		m_cLock.UNLOCK();
		return;
	}

	BOOL32 IsLoginOk(u16 hHandle){
		m_cLock.LOCK();
		BOOL32 bRet = FALSE;
		do 
		{
			if (!IS_VAILD_TPTESTHANDLE(hHandle)){
				break;
			}

			if (0 != m_adwRemoteIP[hHandle-1]){
				bRet = m_bLogined[hHandle-1];
			}

		} while (0);
		m_cLock.UNLOCK();
		return bRet;
	}

	void Show(){
		m_cLock.LOCK();
		OspPrintf(1, 0, "CTPSHandleManger Show:\n");
		for (u16 wIndex = 0; wIndex < TPTESTHANDLE_MAX_NUM; wIndex++){
			OspPrintf(1, 0, "  [%d] Num:%d, Ip:"u32IpForMat", bLogined:%d.\n", wIndex+1, m_adwUseNum[wIndex],
				u32ToIp(m_adwRemoteIP[wIndex]), m_bLogined[wIndex]);
		}
		m_cLock.UNLOCK();
		return;
	}

	static CTPSHandleManger* GetInst(){
		if (NULL == m_pcInst){
			m_pcInst = new CTPSHandleManger;
		}
		return m_pcInst;
	}

protected:
	CTPSHandleManger(){
		for (u16 wIndex = 0; wIndex < TPTESTHANDLE_MAX_NUM; wIndex++){
			m_adwRemoteIP[wIndex] = 0;
			m_adwUseNum[wIndex] = 0;
			m_bLogined[wIndex] = FALSE;
		}
	}

private:
	static CTPSHandleManger*		m_pcInst;
	CLockSemHandle					m_cLock;
	u32								m_adwRemoteIP[TPTESTHANDLE_MAX_NUM];
	u32								m_adwUseNum[TPTESTHANDLE_MAX_NUM];
	BOOL32							m_bLogined[TPTESTHANDLE_MAX_NUM];
}; 

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
	virtual void InstanceEntry(CMessage *const pMsg);

	virtual void DaemonInstanceDump(u32 = 0){}
	virtual void InstanceDump(u32 = 0);

private:

	void EventLoginReq(CMessage *const pMsg);
	void EventLoginRspOk(CMessage *const pMsg);
	void EventLoginRspFail(CMessage *const pMsg);

	void EventTestComDataReq(CMessage *const pMsg);
	void EventTestComDataRspOk(CMessage *const pMsg);
	void EventTestComDataRspFail(CMessage *const pMsg);
	
	void EventTestIODataReq(CMessage *const pMsg);
	void EventTestIODataRspOk(CMessage *const pMsg);
	void EventTestIODataRspFail(CMessage *const pMsg);

	void EventLoginQuit(CMessage *const pMsg);
	void EventDisConnect(CMessage *const pMsg);

	void Show();

	void ClearInst();
private:
	u32					m_dwServerIp;
	u32					m_dwServerNode;

	TPTestCBDefine		m_fCB;
	USERHANDLE			m_hUserHandle;
};

typedef zTemplate<CTestClientInstance, TPTESTHANDLE_MAX_NUM>	CTestClientApp;

API void testhelp();
API void showtest();
API void logon();
API void logoff();

API BOOL32 TestClientInit(s8* szName = NULL);

#endif//_TEST_MODE_H_
