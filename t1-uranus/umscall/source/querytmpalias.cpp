
#include "querytmpalias.h"
#include "tplog.h"
#include "umsobject.h"

// "的临时会议" GB2312编码
const u8 g_abyTempConfStrGB2312[] = {0xB5, 0xC4, 0xC1, 0xD9, 0xCA, 0xB1, 0xBB, 0xE1, 0xD2, 0xE9, 0x0};
 
u16 CQueryAliasMgr::SaveQueryData(TTPQTQueryData *pTQueryInfo)
{
	u16 wSaveIndex = SAVE_INDEX_INVALID;
	u16 wIndex;
	s32 dwretct;
	s8  abyAlias[TP_MAX_ALIAS_LEN + TP_MAX_ALIAS_LEN];

	dwretct = snprintf(abyAlias, sizeof(abyAlias), "%s%s", pTQueryInfo->m_speerAlias, (s8 *)g_abyTempConfStrGB2312);

	if (dwretct < 0  || dwretct >= TP_MAX_ALIAS_LEN)
	{
        return wSaveIndex;
	}

	for(wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
         if (m_tDataInfo[wIndex].m_valid && 0 == strncmp( m_tDataInfo[wIndex].m_szAlias, abyAlias, dwretct))
		 {
			 wSaveIndex = wIndex;
			 break;
		 } 
	}

	if (wSaveIndex > TP_UMS_MAX_CONFNUM)
	{
        for(wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
		{
            if (!m_tDataInfo[wIndex].m_valid)
			{
                 wSaveIndex = wIndex;
				 break;
			}
		}
	}

	if (wSaveIndex > TP_UMS_MAX_CONFNUM)
	{
       return wSaveIndex;
	}

	tpHint(Ums_Mdl_Call,"[CQueryAliasMgr::SaveQueryData] Index:%d SaveQtFrq:%d TempConfname:%s TempId:%d\n",
		  wSaveIndex, 
		  pTQueryInfo->m_emQueryFreq,
		  abyAlias,
		  GetTempId());
    
    memcpy(m_tDataInfo[wSaveIndex].m_szAlias, abyAlias, dwretct);
    m_tDataInfo[wSaveIndex].m_szAlias[dwretct] ='\0';

    m_tDataInfo[wSaveIndex].m_wTmpConfIndex = GetTempId();
    m_tDataInfo[wSaveIndex].m_valid = TRUE;
	m_tDataInfo[wSaveIndex].m_wConfId = INVALID_CONF_ID;
    m_tDataInfo[wSaveIndex].m_wQueryFreq = pTQueryInfo->m_emQueryFreq;
    UpDataTempId();

	return wSaveIndex;
}

u16  CQueryAliasMgr::FindDataInfo(TTPQTQueryData *pTQueryInfo)
{
	u16 wIndex;
	s32 dwretct;

    s8 abyAlias[TP_MAX_ALIAS_LEN +TP_MAX_ALIAS_LEN];

	dwretct = snprintf(abyAlias, sizeof(abyAlias), "%s%s", pTQueryInfo->m_speerAlias, g_abyTempConfStrGB2312);
	
	if (dwretct < 0  || dwretct >= TP_MAX_ALIAS_LEN)
	{
        return SAVE_INDEX_INVALID;
	}

	for(wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		if (m_tDataInfo[wIndex].m_valid && (0 == strncmp( m_tDataInfo[wIndex].m_szAlias, abyAlias, dwretct)))
		{
			tpHint(Ums_Mdl_Call,"[CQueryAliasMgr::FindDataInfo] findout! index:%d\n", wIndex);
			return  wIndex;
		} 
	}

	return SAVE_INDEX_INVALID;
}

void  CQueryAliasMgr::UpDataTempId(void)
{
     ++m_wInc;
	 if (m_wInc > TP_UMS_MAX_CONFNUM)
	 {
         m_wInc = 1;
	 }
}


u16  CQueryAliasMgr::GetTempId(void)
{
	return m_wInc;
}

BOOL32 CQueryAliasMgr::GetRspQueryAliasName(u16 wIndex, s8 *pAliasBuff, u16 wAliasBuffLen)
{
     if (wIndex >= TP_UMS_MAX_CONFNUM || NULL == pAliasBuff || 0 == wAliasBuffLen)
	 {
         return FALSE;
	 }

	 if ( !m_tDataInfo[wIndex].m_valid)
	 {
          return FALSE;
	 }

     snprintf(pAliasBuff, wAliasBuffLen, "%s%d", m_tDataInfo[wIndex].m_szAlias, m_tDataInfo[wIndex].m_wTmpConfIndex);
	 
	 tpHint(Ums_Mdl_Call,"[CQueryAliasMgr::GetRspQueryAliasName] rsp tmpconfname:%s\n", pAliasBuff);

	 return TRUE;
}

u16 CQueryAliasMgr::GetConfID(u16 wIndex)
{
	if (wIndex >= TP_UMS_MAX_CONFNUM )
	{
		return INVALID_CONF_ID;
	}

	if ( !m_tDataInfo[wIndex].m_valid)
	{
		return INVALID_CONF_ID;
	}
    
	return m_tDataInfo[wIndex].m_wConfId;
}


EmTPEncryptType CQueryAliasMgr::GetEncFrq(u16 wIndex)
{
	if (wIndex >= TP_UMS_MAX_CONFNUM )
	{
		return emTPEncryptTypeNone;
	}
	
	if ( !m_tDataInfo[wIndex].m_valid)
	{
		return emTPEncryptTypeNone;
	}

    return m_tDataInfo[wIndex].m_wQueryFreq;
}

BOOL32 CQueryAliasMgr::UpdateTempConfInfo(s8 *ptempConfName, u16 wtempConfNameBuffLen, u16 wConfId, EmTPEncryptType *pemEncType)
{
    if (NULL == ptempConfName)
	{
        return FALSE;
	}

	if (wConfId == 0 || wConfId >= TP_UMS_MAX_CONFNUM)
	{
        return FALSE;
	}

	s32 dwtempConfNameLen = strlen(ptempConfName);
	if (dwtempConfNameLen >= TP_MAX_ALIAS_LEN || dwtempConfNameLen > wtempConfNameBuffLen)
	{
        return FALSE;
	}

    for(u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
        if (m_tDataInfo[wIndex].m_valid && (0 == strncmp( ptempConfName, m_tDataInfo[wIndex].m_szAlias, dwtempConfNameLen)))
		{
		    snprintf(ptempConfName, wtempConfNameBuffLen, "%s%d", m_tDataInfo[wIndex].m_szAlias, m_tDataInfo[wIndex].m_wTmpConfIndex);
            *pemEncType = m_tDataInfo[wIndex].m_wQueryFreq;
            m_tDataInfo[wIndex].m_wConfId = wConfId;

		    tpHint(Ums_Mdl_Call,"[CQueryAliasMgr::UpdateTempConfInfo] updataconfname:%s updatafreq:%d saveconfid:%d\n",
				  ptempConfName, 
				  m_tDataInfo[wIndex].m_wQueryFreq, 
				  wConfId);

			return TRUE;
		} 
	}
    

	return FALSE;
}

void CQueryAliasMgr::HungUpConf(s8 * pConfName)
{
    if (NULL == pConfName)
	{
        return;
	}

    s8 abyAlias[TP_MAX_ALIAS_LEN +TP_MAX_ALIAS_LEN];
	s32 dwAliasLen;

	s32 dwConfNameLen = strlen(pConfName);

	for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
         dwAliasLen = snprintf(abyAlias, sizeof(abyAlias), "%s%d", m_tDataInfo[wIndex].m_szAlias, m_tDataInfo[wIndex].m_wTmpConfIndex);
		 if (dwAliasLen == dwConfNameLen  && 0 == strncmp(abyAlias, pConfName, dwConfNameLen))
		 {
			 tpHint(Ums_Mdl_Call,"[ CQueryAliasMgr::HungUpConf] confname:%s confid:%d\n",pConfName, m_tDataInfo[wIndex].m_wConfId);
             m_tDataInfo[wIndex].clear();
			 break;
		 }
	}

	return;
}

void CQueryAliasMgr::Show(void)
{

	tpHint(Ums_Mdl_Call,"--------------CQueryAliasMgr::Show() TempIndex:%d------------\n", m_wInc);

    for (u16 wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; wIndex++)
	{
		tpHint(Ums_Mdl_Call,"Index:%d ConfId:%d QtFrq:%d TempConfname:%s TempId:%d\n",
			  wIndex, 
			  m_tDataInfo[wIndex].m_wConfId,
			  m_tDataInfo[wIndex].m_wQueryFreq,
			  m_tDataInfo[wIndex].m_szAlias,
              m_tDataInfo[wIndex].m_wTmpConfIndex);
	}

	tpHint(Ums_Mdl_Call,"-----------------------------------------------------------\n\n");
}
