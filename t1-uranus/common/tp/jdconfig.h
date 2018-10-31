#ifndef _h_jdconfig_h__
#define _h_jdconfig_h__


#include "osp.h"
#include "tptype.h"
#include "tpstruct.h"
#include "umsinnertype.h"
#include "tpcommonstruct.h"




class CJDConfig
{	
	
private:
	static CJDConfig *m_pcInstance;
	BOOL32 m_bIsInited;
public:
	CJDConfig()
	{
 		m_bIsInited = FALSE;
	}
	CJDConfig(CJDConfig&){}

public:
	BOOL32 ReadFromConfigFile();
	void GetFromConfigFile(TJDInfo &tJDInfo);

private:
	BOOL32   GetIPValue(FILE*pfFile,u32& dwVal,const s8* const szSection ,const s8* const szKey );
	BOOL32   GetMoidValue(FILE*pfFile,s8* szMoidVal,const s8* const szSection,const s8* const szKey );

public:
	virtual ~CJDConfig()
	{
		if ( m_pcInstance != NULL )
		{
			delete m_pcInstance;
			m_pcInstance = NULL;
		}
	}
public:
	static CJDConfig* GetInstance();
	TJDInfo m_tJDInfo;
	//显示所有私有信息
    void ShowAll(void);
};
#endif // _h_jdconfig_h__
