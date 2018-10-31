#ifndef _h_netbufeqp_h__
#define _h_netbufeqp_h__


#include "umseqp.h"

class CNbModle : public CEqpModle
{
public:
	CNbModle() : 	CEqpModle(){}
};

class CNbEqp : public CEqpBase
{
public:
	CNbEqp(CUmsEqpInst* pInst);
	virtual ~CNbEqp();
	
public:
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Show();
	
	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);
	
	virtual BOOL32 OnDisConnect(u32 dwNode);

	
protected:
	void OnEqpReg(CTpMsg *const ptMsg);
	void OnNbInitSuccess(CTpMsg *const ptMsg);
	
	CNbModle m_tNb;
};



#endif // _h_netbufeqp_h__
