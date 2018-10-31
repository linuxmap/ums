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
{// ������ֻ����ʹ�ã�����xml���ƣ����ʺ�ģ��䴫��
	
	TSaveVmpCfg     m_tVmpCfg;			//����ϳ���Ϣ
	TTemplateConfEx m_tTempCfgEx;       //�᳡����Э��

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
/*****************����µĽṹ����Ҫ����ģ��䴫�ݣ�����Ҫxml�����ģ����Ʋ�tpcommonstruct.h�ļ���������t0-luna\commonxmlparse\commonxmlparse.bat*********/

#endif // _h_tpstruct_h__

