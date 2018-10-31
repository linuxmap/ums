#ifndef _h_eqpinst_h__
#define _h_eqpinst_h__

#include "umsobject.h"
#include "umseqp.h"
#include "audiomixeqp.h"
#include "eqpinterface.h"
#include "mcudef.h"
#include "eqpmgr.h"
#include "hdueqp.h"

using namespace UmsTpmsg;

typedef struct tagTFrameStatis
{
	u32 m_dwLastTime;
	u16	m_wIntrval;
	tagTFrameStatis()
	{
		Clear();
	}

	void Clear()
	{
		m_dwLastTime = 0;
		m_wIntrval = 1;
	}

	void SetIntrval(u16 wIntrval)
	{
		m_wIntrval = wIntrval;
	}

	BOOL32 CheckFrameStatis()
	{
		time_t t;
		time(&t);
		u32 dwNow = t;

		if ( dwNow - m_dwLastTime >= m_wIntrval  )
		{
			m_dwLastTime = dwNow;
			return TRUE;
		}
		return FALSE;
	}
	
}TFrameStatis;

typedef struct tagTEqpHandle
{
	CEqpBase* m_pcEqp;
	EMEqpType m_emEqpType;

	tagTEqpHandle() { Clear(); }
	void Clear()
	{
		m_pcEqp = NULL;
		m_emEqpType = em_unknow_mdl;
	}
}TEqpHandle;

class CUmsEqpInst :  public CUmsObject
{
public:
    CUmsEqpInst();
	~CUmsEqpInst();

	enum EmEqpHandle
	{
		_CAdapterEqp,
		_CAudioMixEqp,
		_CMediaTransEqp,
		_CNbEqp,
		_CMpcEqp,
		_CVmpEqp,
		_CBasEqp,
		_CHduEqp,
		_CAudBasEqp,
		_CMpu2TpEqp,
		_EqpEnd,
	};

public:
	BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);	
	BOOL32 AssignEqpByNodeEx(TEqpParam* ptEqpParam);
	BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);

	BOOL32 GetAllEqpResEx( TEqpRes* pcEqpRes, u16 wEqpNum, EMEqpType emEqpType);
	
	CEqpMgr*	GetEqpMgr()	{ return &m_cEqpMgr; }
	CEqpBase*	GetEqp(EmEqpHandle em) { return em < _EqpEnd ? m_atEqpHandle[em].m_pcEqp : NULL; }
	CEqpBase*	GetEqp(EMEqpType em);

	BOOL32		IsUmsBrd(EMBrdType emBrdType);
protected:
	virtual BOOL PreMessageProc ( CMessage *const ptMsg ); 
	virtual void MessageProc( CTpMsg *const ptMsg);
	
	BOOL32 ObjectInit(u32 wParam, u32 lParam);
	void ObjectExit();
	
	void CallMgrMessageProc(CTpMsg *const ptMsg);
	void BrdSsnMessageProc(CTpMsg *const ptMsg);
	void ServiceMessageProc(CTpMsg *const ptMsg);

	void OnBrdReg(CTpMsg *const ptMsg);
	void OnBrdGetCfgReq(CTpMsg *const ptMsg);
	void OnBrdUpdateAck(CTpMsg *const ptMsg);
	void OnChangeEqpSndAddr(CTpMsg *const ptMsg);

	BOOL32 ProcMpu2GetCfg(TBrdEntry* ptBrdEntry, u8* abyBuffer);
	BOOL32 ProcApu2GetCfg(TBrdEntry* ptBrdEntry, u8* abyBuffer);
protected:

	virtual void InstanceDump(u32=0);
	void ShowEqp();

public:

	u16 NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen, TLogUser& tLogUser);	
	void SendToBrd(EMBrdType emBrdType, u16 wEvent, u32 dwDstIID, u32 dwNode, void* pbyBody = NULL, u16 wLen = 0);	
private:
	void OnDisconnect(CMessage *const ptMsg);

private:
	TEqpHandle		m_atEqpHandle[_EqpEnd];
	CEqpMgr			m_cEqpMgr;
};

typedef zTemplate<CUmsEqpInst, 1> CUmsEqpApp;


#endif // _h_eqpinst_h__
