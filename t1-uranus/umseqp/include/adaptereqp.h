#ifndef _h_adaptereqp_h__
#define _h_adaptereqp_h__

#include "umseqp.h"

class CAdapterModle : public CEqpModle
{
public:
	EmTpConfProtocol	m_emAdatperType;
	u16					m_dwListenPort;
public:
	CAdapterModle() : 	CEqpModle(), m_emAdatperType(emTpSIP), m_dwListenPort(TP_UMS_SIP_LISTIEN_PORT) {}
};

class CAdapterEqp : public CEqpBase
{
public:
	CAdapterEqp(CUmsEqpInst* pInst);
	virtual ~CAdapterEqp();

public:
	CAdapterModle* FindIdle(u16& wEqpIndex);
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Show();

	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 AssignEqpByEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 GetAllEqpRes( TEqpRes* pcEqpRes, u16 wEqpNum );

	virtual BOOL32 OnDisConnect(u32 dwNode);
protected:
	void OnEqpReg(CTpMsg *const ptMsg);
	void OnAdaptInitSuccess(CTpMsg *const ptMsg);

	CAdapterModle m_atAdapter[MAX_ADAPTER_MDL_NUM];
};

#endif // _h_adaptereqp_h__
