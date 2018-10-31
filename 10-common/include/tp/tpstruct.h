#ifndef _h_tpstruct_h__
#define _h_tpstruct_h__
//#include "tpsys.h"
//#include <time.h>
//#include "mtmacro.h"
//#include "tphdu2.h"

//MTStruct begin.
//#include "kdvtype.h"
//#include "mtmacro.h"
//#include "tptype.h"
//#include "osp.h"
//#include "cnconst.h"
#include "tpcommonstruct.h"
#include "cnsstruct.h"
#include "cnstype.h"

// Attention!
// the struct defined here need not xml parse...

typedef struct tagTConfTemplateLocal : public TTPConfTemplate
{// 此子类只本地使用，由于xml限制，不适合模块间传递
	
	TSaveVmpCfg     m_tVmpCfg;			//画面合成信息
	TTemplateConfEx m_tTempCfgEx;       //会场呼叫协议

	tagTConfTemplateLocal()
	{
		m_tVmpCfg.Clear();
		m_tTempCfgEx.clear();
		TTPConfTemplate::Clear();
	}

	tagTConfTemplateLocal& operator = (const tagTConfTemplateLocal& tRhs)
	{
		if(this == &tRhs)
            return *this;
		
		this->m_tVmpCfg = tRhs.m_tVmpCfg;
		this->m_tTempCfgEx = tRhs.m_tTempCfgEx;
		TTPConfTemplate::operator = (tRhs);
		return *this;
	}

	tagTConfTemplateLocal& operator = (const tagTTPConfTemplate& tRhs)
	{
		memcpy(this, &tRhs, sizeof(tagTTPConfTemplate));
		return *this;
	}

	void Clear()
	{
		m_tVmpCfg.Clear();
		m_tTempCfgEx.clear();
		TTPConfTemplate::Clear();
	}

}TConfTemplateLocal;



// Attention!
/*****************添加新的结构体需要进行模块间传递，即需要xml解析的，请移步tpcommonstruct.h文件，并运行t0-luna\commonxmlparse\commonxmlparse.bat*********/

#endif // _h_tpstruct_h__

