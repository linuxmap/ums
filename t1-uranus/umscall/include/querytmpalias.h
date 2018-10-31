#ifndef _querytmpalias_h_
#define _querytmpalias_h_

#include "tpsys.h"
#include "qtstruct.h"
#include "tpcommonstruct.h"
#include "tpcommontype.h"

#define SAVE_INDEX_INVALID  0xffff
#define INVALID_CONF_ID     0xffff

typedef struct tagTAliasDataInfo
{
	BOOL32  m_valid;
	u16  m_wConfId;
    EmTPEncryptType m_wQueryFreq;
	u16     m_wTmpConfIndex;
	s8		m_szAlias[TP_MAX_ALIAS_LEN+1];


	void clear(void)
	{
		memset(this, 0, sizeof(tagTAliasDataInfo));
		m_wConfId =  INVALID_CONF_ID;
	}

    tagTAliasDataInfo()
	{
		 clear();
	}
	
}TAliasDataInfo;



class CQueryAliasMgr{
public:
	u16  SaveQueryData(TTPQTQueryData *pTQueryInfo);
	u16  FindDataInfo(TTPQTQueryData *pTQueryInfo);
	BOOL32 GetRspQueryAliasName(u16 wIndex, s8 *pAliasBuff, u16 wAliasBuffLen);
    u16 GetConfID(u16 wIndex);
    EmTPEncryptType GetEncFrq(u16 wIndex);
    BOOL32 UpdateTempConfInfo(s8 *ptempConfName, u16 wtempConfNameBuffLen, u16 wConfId, EmTPEncryptType *pemEncType);
    void HungUpConf(s8 * pConfName);
	void  Show(void);
	
	CQueryAliasMgr()
	{
         m_wInc = 1;
		 for(u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
		 {
             m_tDataInfo[wIndex].clear();
		 }
	}

private:
    void UpDataTempId(void);
	u16  GetTempId(void);

private:
	u16              m_wInc;
    TAliasDataInfo   m_tDataInfo[TP_UMS_MAX_CONFNUM];
};


#endif