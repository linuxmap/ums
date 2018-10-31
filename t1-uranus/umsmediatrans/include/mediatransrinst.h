#ifndef _h_mediatransrinst_h__
#define _h_mediatransrinst_h__

#include "tpobject.h"
#include "tphandle.h"
#include "dataswitch.h"
#include "mpstruct.h"
class CMpData;
class CTpTimerMgr;
class CTpMediatransInst :  public CTpObject
{
public:
    CTpMediatransInst();

public:
	void RcvTimeOut(u32 dwPort);
	void SndTimeOut(u32 dwPort);

protected:
	virtual BOOL32 ObjectInit(u32 wParam, u32 lParam);
	virtual void ObjectExit();
protected:
	virtual void InstanceDump(u32=0);
	
protected:
	void MessageProc(CTpMsg *const ptMsg);	

	void OnDisConnect(CTpMsg *const ptMsg);
	void OnRegSuccess(CTpMsg *const ptMsg);
	void OnIFrameRcvCheckRes(CTpMsg *const ptMsg);
	void OnIFrameSndCheckRes(CTpMsg *const ptMsg);
	void OnIFrameSndDisCheckRes( CTpMsg *const ptMsg );
	
	void OnAddMediaTrans(CTpMsg *const ptMsg);
	void OnDelMediaTrans(CTpMsg *const ptMsg);
	void OnClearConfTrans(CTpMsg *const ptMsg);

	void OnAddIFrameCheckBySrc(CTpMsg *const ptMsg);
	void OnAddIFrameCheckTwoRcvPort(CTpMsg *const ptMsg);
	void OnAddIFrameCheckSndBySrc(CTpMsg *const ptMsg);
	void OnDelIFrameCheck(CTpMsg *const ptMsg);
	void OnAddIFrameCheckSndDis( CTpMsg *const ptMsg );
	void OnSwitchSsh(CTpMsg *const ptMsg);
	void ConnectToUms();

protected:
	void OnMsgFromCall(CTpMsg *const ptMsg);	

	BOOL32 DelCheck(CPortVector& cVec, u16 wPort);
	BOOL32 DelChecked(CPortVector& cVec, u16 wPort);
	BOOL32 DelAllCheck();

private:
	DSID m_MediaDsID;
	CMpData* m_pcMpData;
	CUnitList m_tUnitList;

	CTpTimerMgr* m_pcTimerMgr;
};

typedef zTemplate<CTpMediatransInst, 1> CTpUmsMediatransApp;





#endif // _h_mediatransrinst_h__
