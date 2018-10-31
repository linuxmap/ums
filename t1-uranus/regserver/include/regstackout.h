#ifndef _h_regstackout_h__
#define _h_regstackout_h__


#include "tpobject.h"
#include "regstruct.h"
#include "rverror.h"

class CTpRegStackOut :  public CTpObject
{
public:
    CTpRegStackOut(){ }

protected:
	virtual void	MessageProc( CTpMsg *const ptMsg);
	BOOL32			ObjectInit(u32 wParam, u32 lParam);

private:
	RvStatus	PostUmsRegInfo(const TUmsHandle& tHandle, s32 nAppID, const TReqRegInfoEx& tRegInfo, u8* pData);
	RvStatus	PostCnsRegInfo(const TUmsHandle& tHandle, s32 nAppID, const TReqRegInfoEx& tRegInfo, u8* pData);
};


typedef zTemplate<CTpRegStackOut, 1> CTpRegStackOutApp;


#endif // _h_regstackout_h__
