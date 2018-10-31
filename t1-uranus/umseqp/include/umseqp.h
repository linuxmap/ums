#ifndef _h_umseqp_h__
#define _h_umseqp_h__
#include "umsobject.h"
#include "umsinnerstruct.h"
#include "umscommonstruct.h"
#include "eqpinterface.h"

#define EQP_SERVER_INST 1

using namespace UmsTpmsg;

class CEqpModle
{
public:
	u32 m_dwUserNode;
	u32 m_dwUserInst;
	BOOL32 m_bRegsited;
	TModelProp m_tRegInfo;
	
	u32 m_dwUsed;	//已经使用的能力数量
	
	CEqpModle()
	{
		Clear();
	}
	
	void Clear()
	{
		m_dwUserNode = 0;
		m_dwUserInst = 0;
		m_tRegInfo.Clear();
		m_dwUsed = 0;
		m_bRegsited = FALSE;
	}
	BOOL32 IsIdle()const	
	{	
		return 0 == m_dwUserNode; 
	} 	
};

class CEqpSem
{
public:
	CEqpSem(s8* pszPos, u32 dwLine);
	~CEqpSem();
};
#define CHECK_EQP_SEM CEqpSem cCheckEqpSem_Macro(__FILE__, __LINE__);


class CUmsEqpInst;
class CEqpBase
{
public:
	CEqpBase(CUmsEqpInst* pInst);
	virtual ~CEqpBase();
	
public:
	virtual BOOL32 OnDisConnect(u32 dwNode) = 0;
	
	virtual void Init();	
	
	virtual BOOL32 AssignEqpByEqpEx(TEqpParam* ptEqpParam) { return FALSE; }
	virtual BOOL32 AssignEqpEx(TEqpParam* ptEqpParam) = 0;
	virtual BOOL32 ReleaseEqpEx(TEqpParam* ptEqpParam) = 0;
	
	virtual BOOL32 GetAllEqpRes( TEqpRes* pcEqpRes, u16 wEqpNum ) { return FALSE;}
	
	virtual void Show();
	virtual void CalcEqpUsedStat(TTPBrdUsedInfo& tUsed){ return; }
	void NotifyMsgToEqp(u32 dwDstNode, u32 dwDstInst, u16 wEvent, void* body, u16 bodyLen);
	
public:
	
public:
	virtual void Handle(CTpMsg *const ptMsg) = 0;
	
protected:
	CUmsEqpInst* m_pcInst;
	
};
#endif // _h_umseqp_h__

