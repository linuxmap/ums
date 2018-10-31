#include "eqpinterface.h"
#include "eqpinst.h"


extern CUmsEqpApp g_cUmsEqpApp;


BOOL32 AssignEqpEx( TEqpParam* ptEqpParam )
{
	CUmsEqpInst* pInst = (CUmsEqpInst*)((CApp*)&g_cUmsEqpApp)->GetInstance(1);
	return pInst->AssignEqpEx(ptEqpParam);
}

BOOL32 AssignEqpByNodeEx( TEqpParam* ptEqpParam )
{
	CUmsEqpInst* pInst = (CUmsEqpInst*)((CApp*)&g_cUmsEqpApp)->GetInstance(1);
	return pInst->AssignEqpByNodeEx(ptEqpParam);
}

BOOL32 ReleaseEqpEx( TEqpParam* ptEqpParam )
{
	CUmsEqpInst* pInst = (CUmsEqpInst*)((CApp*)&g_cUmsEqpApp)->GetInstance(1);
	return pInst->ReleaseEqpEx(ptEqpParam);
}

BOOL32 GetAllEqpRes( TEqpRes* pcEqpRes, u16 wEqpNum, EMEqpType emEqpType )
{
	CUmsEqpInst* pInst = (CUmsEqpInst*)((CApp*)&g_cUmsEqpApp)->GetInstance(1);
	return pInst->GetAllEqpResEx(pcEqpRes, wEqpNum, emEqpType);
}
