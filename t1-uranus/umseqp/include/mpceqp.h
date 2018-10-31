#ifndef _h_mpceqp_h__
#define _h_mpceqp_h__


#include "umseqp.h"
#include "tpsys.h"
#include "eqpinterface.h"

enum EMMpcNum
{
	MPC_INVALID,
	MPC_ONE,
	MPC_TWO,
};

class CMpcModle : public CEqpModle
{
public:
	BOOL32 m_bMaster;        //Ö÷±¸
public:
	CMpcModle() : 	CEqpModle(){ m_bMaster = FALSE; }
};

class CMpcEqp : public CEqpBase
{
public:
	CMpcEqp(CUmsEqpInst* pInst);
	virtual ~CMpcEqp();
	
public:
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Show();
	
	virtual BOOL32 AssignEqp(u16 wCapCount, TEqpRes& tEqp) { return FALSE; };
	virtual BOOL32 ReleaseEqp(u16 wEqpIndex, u16 wCapCount) { return FALSE; };
	
	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);
	
	virtual BOOL32 OnDisConnect(u32 dwNode);

protected:
	void OnEqpReg(CTpMsg *const ptMsg);
	void OnEqpSetTime(CTpMsg* const ptMsg);
	void NotifyMsgToService(u16 wEvent, void* body, u16 bodyLen);

	CMpcModle* AnotherMpc(EMMpcNum emMpc);
	
	CMpcModle m_tMpc1;
	CMpcModle m_tMpc2;
	EMMpcNum  m_emUsedMpc;

	TTPTime m_tSetTime;
};


#endif // _h_mpceqp_h__
