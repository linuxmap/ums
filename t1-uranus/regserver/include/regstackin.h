#ifndef _h_regstackin_h__
#define _h_regstackin_h__

#include "kdvsipadapter.h"
#include "tpobject.h"

class CRegStackIn : public CTpObject  
{
public:
	CRegStackIn();
	virtual ~CRegStackIn();
	
	//回调函数
	s32 OnNewCall(RvSipCallLegHandle hsCall,LPRvSipAppCallLegHandle lphaCall);
	
	
	void RunSipStack();
	
	void Quit(){m_bRun = FALSE;}

protected:	
	//继承函数实现
	BOOL ObjectInit( u32 wParam, u32 lParam );
	
	//初始化协议栈
    BOOL InitAdapter( u32 wParam,u32 lParam );

	BOOL32 m_bRun;
};

typedef zTemplate<CRegStackIn,1,CRegStackIn> CRegStackInApp;



#endif // _h_regstackin_h__
