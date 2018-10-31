#ifndef _h_mediatrans_h__
#define _h_mediatrans_h__


#include "umseqp.h"

class CMediaTransModle : public CEqpModle
{
public:
	BOOL32	m_bIS22;
	BOOL32  m_bIsLocal;
	CMediaTransModle() : 	CEqpModle(){ m_bIS22 = FALSE;m_bIsLocal = FALSE; }

	TIpmaskinfo m_tIpMask;

	void Clear()
	{
		m_bIS22 = FALSE;
		m_bIsLocal = FALSE;
		CEqpModle::Clear();
		m_tIpMask.Clear();
	}

	void AddUse(u32 dwCount)
	{
		m_dwUsed += dwCount; 
	}

	void DelUse(u32 dwCount)
	{
		if (m_dwUsed < dwCount)
		{
			m_dwUsed = 0;
		}
		else
		{
			m_dwUsed -=dwCount;
		}
	}
};

class CMediaTransEqp : public CEqpBase
{
public:
	CMediaTransEqp(CUmsEqpInst* pInst);
	virtual ~CMediaTransEqp();
	
public:
	virtual void Handle(CTpMsg *const ptMsg);
	virtual void Show();
		
	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 AssignEqpByEqpEx(TEqpParam* ptEqpParam);
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam);
	
	virtual BOOL32 OnDisConnect(u32 dwNode);

	BOOL32	AssignDsForBas(TEqpRes* ptEqp, u32 dwCapCount);
	BOOL32	ReleaseDsForBas(u32 dwIP, u32 dwCapCount); 
	void CalcEqpUsedStat(TTPBrdUsedInfo& tUsed);
private:
	CMediaTransModle* FindIdle(u16& wEqpIndex);
	BOOL32 Assign(TMediaParam* pParam);
	

protected:
	void OnEqpReg(CTpMsg *const ptMsg);
	void OnMediatransInitSuccess(CTpMsg *const ptMsg);
	void OnMediatransSshSwitch(CTpMsg *const ptMsg);
	CMediaTransModle m_atMediaTrans[MAX_DATASWITCH_MDL_NUM];
};



#endif // _h_mediatrans_h__
