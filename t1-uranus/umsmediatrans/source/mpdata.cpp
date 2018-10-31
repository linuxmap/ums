#include "tpobject.h"
#include "mpdata.h"
#include "umsxmltype.h"
#include "dataswitch.h"

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

SEMHANDLE g_semUpdateIframeInfo = NULL;

CMpData::CMpData()
{

}
CMpData::~CMpData()
{

}

BOOL32	CreatLocalSwitchId(const DSID idMediaDsID, const TTPTransAddr tSrcAddr, DSRTPSID& dLocalId);
BOOL32	DestroyLocalSwitchId(const DSID idMediaDsID, const DSRTPSID dLocalId);
BOOL32	AddDsRule(const DSID idMediaDsID, const DSRTPSID localdsrtpsid, TUmsDsData* ptData);
BOOL32	DelDsRule(const DSID idMediaDsID, const DSRTPSID localdsrtpsid, TUmsDsData* ptData);
u32		GetStatisBySrcAddr(const DSRTPSID dLocalId, const TTPTransAddr tSrcAddr);
u32		GetStatisBySrcDstAddr(const DSRTPSID dLocalId, const TTPTransAddr tSrcAddr, const TTPTransAddr tDstAddr);

CPortVector	CMpData::m_tRcvCheck;
CPortVector	CMpData::m_tSndCheck;

BOOL32 CMpData::Init(u32 dwSwitchNum, u16 wIframePortNum)
{
	OspSemBCreate(&g_semUpdateIframeInfo);
	if (NULL == g_semUpdateIframeInfo)
	{
		msgprint("CMpData::Init Create sem failed!\n");
		return FALSE;
	}

	//不可重复创建
	u16 wIndex = 0;
	for (wIndex = 0; wIndex <TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		m_aptSwitchRulesInfo[wIndex] = new CConfSwitchRulesInfo(1000);
	}

	if (!m_tRcvCheck.Create(wIframePortNum))
	{
		msgprint("CMpData::Init Create m_tRcvCheck failed!\n");
		return FALSE;
	}

	if (!m_tSndCheck.Create(wIframePortNum))
	{
		msgprint("CMpData::Init Create m_tSndCheck failed!\n");
		return FALSE;
	}

	return TRUE;
}

BOOL32 CMpData::Quit(DSID idMediaDsID)
{
	u16 wIndex = 0;
	for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		if (m_aptSwitchRulesInfo[wIndex]->GetListNum() == 0)
		{
			continue;
		}

		ClearConfSwitch(wIndex+1, idMediaDsID);
	}
	
	TCheckIFrame* ptIFrame;
	for (wIndex = 0; wIndex < m_tRcvCheck.MaxSize(); wIndex++)
	{
		ptIFrame = m_tRcvCheck.FindByIndex(wIndex);
		if (ptIFrame->m_tUnit.GetElementNum() == 0)
		{
			continue;
		}
		dsSetFilterFunc(idMediaDsID, ptIFrame->m_dwIP, ptIFrame->m_wPort, NULL);
	}
	for (wIndex = 0; wIndex < m_tSndCheck.MaxSize(); wIndex++)
	{
		ptIFrame = m_tSndCheck.FindByIndex(wIndex);
		if (ptIFrame->m_tUnit.GetElementNum() == 0)
		{
			continue;
		}
		dsSetFilterFunc(idMediaDsID, ptIFrame->m_dwIP, ptIFrame->m_wPort, NULL);
	}
		
	m_tRcvCheck.Destroy();
	m_tSndCheck.Destroy();

	OspSemBCreate(&g_semUpdateIframeInfo);
	if (NULL != g_semUpdateIframeInfo)
	{
		OspSemDelete(g_semUpdateIframeInfo);
		g_semUpdateIframeInfo = NULL;
	}
	
	return TRUE;
}

BOOL32 CMpData::AddSwitch(DSID idMediaDsID, u16 wConfID, TUmsDsData* ptDs, DSRTPSID& dLocalId)
{
	wConfID--;
	if (wConfID >= TP_UMS_MAX_CONFNUM)
	{
		MdlError(Ums_Mdl_Media, ("CMpData::AddSwitch ConfID:%d!\n", wConfID+1))
		return FALSE;
	}

	return m_aptSwitchRulesInfo[wConfID]->Insert(idMediaDsID, *ptDs, dLocalId);
}

BOOL32 CMpData::DelSwitch(u16 wConfID, TUmsDsData* ptDs, DSRTPSID& dLocalId)
{
	wConfID--;
	if (wConfID >= TP_UMS_MAX_CONFNUM)
	{
		MdlError(Ums_Mdl_Media, ("CMpData::DelSwitch ConfID failed ConfID:%d!\n", wConfID+1));
		return FALSE;
	}
	
	return m_aptSwitchRulesInfo[wConfID]->DelNode(ptDs, dLocalId);
}

void CMpData::ClearConfSwitch(u16 wConfID, DSID dwMediaID)
{
	wConfID--;
	if (wConfID >= TP_UMS_MAX_CONFNUM)
	{
		MdlError(Ums_Mdl_Media, ("CMpData::ClearConfSwitch ConfID failed ConfID:%d!\n", wConfID+1));
		return ;
	}

	MdlHint(Ums_Mdl_Media, ("CMpData::ClearConfSwitch ConfID:%d!\n", wConfID+1));

	CConfSwitchRulesInfo* pInfo = m_aptSwitchRulesInfo[wConfID];
	CSwitchRulesBufItor ptItor = pInfo->GetHead();
	TUmsDsData tDsData;
	for (; ptItor != NULL; ptItor = ptItor->m_ptNext)
	{
		
		std::list<TUmsDsData>::iterator pListIter = ptItor->m_tData.m_lSndList.begin();
		while(pListIter!=ptItor->m_tData.m_lSndList.end())
		{
			dsRemoveManyToOne(dwMediaID, pListIter->m_tRcvFromAddr.m_dwIP, pListIter->m_tRcvFromAddr.m_wPort, 
				pListIter->m_tSndToAddr.m_dwIP, pListIter->m_tSndToAddr.m_wPort);
			pListIter++;
		}

		DestroyLocalSwitchId(dwMediaID, ptItor->m_tData.m_dLocalID);
		ptItor->m_tData.m_lSndList.clear();
	}
	pInfo->FreeALL();
}




#define PRINTNUM_CHECK(wPrintNum)				(wPrintNum)++;if((wPrintNum)>5){OspDelay(20);(wPrintNum)=0;}

inline s8* GetDsTypeName(EmSwitchType emType)
{
	switch (emType)
	{
	case emRtpSwap:
		{
			return "Rtp";
		}
	case emRtcpSwap:
		{
			return "Rtcp";
		}
	default:
		{
			return "ERR";
		}
	}
}

inline void GetDsMediaTypeName(u32 dwType, OUT s8* pszBuf, IN u16 wBufLen)
{
	if (NULL == pszBuf || wBufLen < 2)
	{
		return;
	}
	memset(pszBuf, 0, wBufLen);
	u8 byType = (u8)dwType;
	if (0 == byType)
	{
		byType = (u8)(dwType >> 8);
		if (0 != byType)
		{
			snprintf(pszBuf, wBufLen-1, "Aud:%02X", byType);
			return;
		}
	}
	else
	{
		snprintf(pszBuf, wBufLen-1, "Vid:%02X", byType);
		return;
	}
	snprintf(pszBuf, wBufLen-1, "UKN", byType);
	return;
}

void CMpData::ShowSwitch(DSID dwMediaID, u8 byPrintType /* = 0 */)
{
	msgprintnotime("DSID:%d.\n", dwMediaID);
	u16 wIndex = 0;
	u16 wPrintNum = 0;
	wPrintNum = 0;
	CConfSwitchRulesInfo* pInfo = NULL;
	u32 dwStatis = 0;
	for (wIndex = 0; wIndex < TP_UMS_MAX_CONFNUM; ++wIndex)
	{
		pInfo = m_aptSwitchRulesInfo[wIndex];
		if (pInfo->GetListNum() == 0)
		{
			continue;
		}
		msgprintnotime("\n");
		msgprintnotime("ConfID:%d, max list:%d, list:%d, ds:%d, List buf total:%d, min free:%d, free:%d.\n", 
			wIndex+1, pInfo->GetMaxListNum(), pInfo->GetListNum(), pInfo->GetDsNum(),
			pInfo->GetListBufTotalNum(), pInfo->GetListBufMinFreeNum(), pInfo->GetListBufFreeNum());
		msgprintnotime("\n");

		CSwitchRulesBufItor ptItor = pInfo->GetHead();

		s8 azBuf[8]={0};
		while(NULL!=ptItor)
		{	
			if (ptItor->m_tData.m_lSndList.empty() && 0 == byPrintType)
			{
				ptItor = ptItor->m_ptNext;
				continue;
			}

//			dwStatis = GetStatisBySrcAddr(ptItor->m_tData.m_dLocalID, ptItor->m_tData.m_tSrcAddr);

			msgprintnotime("[SWID:%u]\t\t"IPFORMAT"@%d\n",
				ptItor->m_tData.m_dLocalID,
				u32ToIP(ptItor->m_tData.m_tSrcAddr.m_dwIP), 
				ptItor->m_tData.m_tSrcAddr.m_wPort);
			PRINTNUM_CHECK(wPrintNum);

			std::list<TUmsDsData>::iterator pListIter = ptItor->m_tData.m_lSndList.begin();
			while(pListIter!=ptItor->m_tData.m_lSndList.end())
			{
//				dwStatis = GetStatisBySrcDstAddr(ptItor->m_tData.m_dLocalID, ptItor->m_tData.m_tSrcAddr, pListIter->m_tSndToAddr);

				GetDsMediaTypeName(pListIter->m_dwSrcMediaType, azBuf, 8);

				msgprintnotime("[%s][%s][ToEp:%d]\t\t|->"IPFORMAT"@%d("IPFORMAT"@%d)\n"
					, GetDsTypeName(pListIter->m_emSwitchType), 
					azBuf, pListIter->m_bNeedModifySrc,
					u32ToIP(pListIter->m_tSndToAddr.m_dwIP),
					pListIter->m_tSndToAddr.m_wPort, u32ToIP(pListIter->m_tMapedAddr.m_dwIP),
					pListIter->m_tMapedAddr.m_wPort);				
				PRINTNUM_CHECK(wPrintNum);

				pListIter++;
			}
			msgprintnotime("\n");
			ptItor = ptItor->m_ptNext;
		}
		OspDelay(20);
	}
}

CConfSwitchRulesInfo::CConfSwitchRulesInfo( u32 dwMaxListNum )
{
	m_pHead = NULL;
	m_dwDsNum = 0;
	m_dwListNum = 0;
	m_dwMaxListNum = dwMaxListNum;
	m_tSwitchRulesList.Create(dwMaxListNum);
}

CConfSwitchRulesInfo::~CConfSwitchRulesInfo()
{
	m_pHead = NULL;
	m_dwListNum = 0;
	m_dwMaxListNum = 0;
	m_dwDsNum = 0;
	m_tSwitchRulesList.Destroy();
}

BOOL32 CConfSwitchRulesInfo::Insert(const DSID idMediaDsID,  const TUmsDsData tUmsDsData , DSRTPSID& dLocalId)
{
	TSwitchRulesInfo tInsertNode;
	if (NULL == m_pHead)
	{
		if (!CreatLocalSwitchId(idMediaDsID, tUmsDsData.m_tRcvFromAddr, dLocalId))
		{
			return FALSE;
		}

		tInsertNode.m_dLocalID = dLocalId;
		tInsertNode.m_tSrcAddr = 	tUmsDsData.m_tRcvFromAddr;
		tInsertNode.m_lSndList.push_back(tUmsDsData);
		CSwitchRulesBufItor pTr = m_tSwitchRulesList.WriteBuffItor(tInsertNode);

		m_pHead = pTr;
		pTr->m_ptNext = NULL;
		m_dwListNum++;
		m_dwDsNum++;
		return TRUE;
	}

	if (m_pHead->m_tData.m_tSrcAddr == tUmsDsData.m_tRcvFromAddr)
	{
		dLocalId = m_pHead->m_tData.m_dLocalID;
		m_pHead->m_tData.m_lSndList.push_back(tUmsDsData);
		m_dwDsNum++;
		return TRUE;
	}
	else if (m_pHead->m_tData.m_tSrcAddr > tUmsDsData.m_tRcvFromAddr)
	{
		if (!CreatLocalSwitchId(idMediaDsID, tUmsDsData.m_tRcvFromAddr, dLocalId))
		{
			return FALSE;
		}

		tInsertNode.m_dLocalID = dLocalId;
		tInsertNode.m_tSrcAddr = 	tUmsDsData.m_tRcvFromAddr;
		tInsertNode.m_lSndList.push_back(tUmsDsData);
		CSwitchRulesBufItor pTr = m_tSwitchRulesList.WriteBuffItor(tInsertNode);

		pTr->m_ptNext = m_pHead;
		m_pHead = pTr;
		m_dwListNum++;
		m_dwDsNum++;
		return TRUE;
	}

	CSwitchRulesBufItor ptNode = m_pHead;
	while(NULL != ptNode->m_ptNext)
	{
		if (ptNode->m_ptNext->m_tData.m_tSrcAddr == tUmsDsData.m_tRcvFromAddr)
		{
			dLocalId = ptNode->m_ptNext->m_tData.m_dLocalID;
			ptNode->m_ptNext->m_tData.m_lSndList.push_back(tUmsDsData);
			m_dwDsNum++;
			return TRUE;
		}
		else if (ptNode->m_ptNext->m_tData.m_tSrcAddr > tUmsDsData.m_tRcvFromAddr)
		{
			break;
		}

		ptNode = ptNode->m_ptNext;
	}

	if (!CreatLocalSwitchId(idMediaDsID, tUmsDsData.m_tRcvFromAddr, dLocalId))
	{
		return FALSE;
	}

	tInsertNode.m_dLocalID = dLocalId;
	tInsertNode.m_tSrcAddr = 	tUmsDsData.m_tRcvFromAddr;
	tInsertNode.m_lSndList.push_back(tUmsDsData);
	CSwitchRulesBufItor pTr = m_tSwitchRulesList.WriteBuffItor(tInsertNode);

	pTr->m_ptNext = ptNode->m_ptNext;
	ptNode->m_ptNext = pTr;
	m_dwListNum++;
	m_dwDsNum++;

	return TRUE;
}

BOOL32 CConfSwitchRulesInfo::DelMemberFromSndList( std::list<TUmsDsData>& tList, TUmsDsData* ptDs )
{
	std::list<TUmsDsData>::iterator pIter = tList.begin();
	while(pIter!=tList.end())
	{
		if (pIter->m_tRcvFromAddr == ptDs->m_tRcvFromAddr
			&& pIter->m_tSndToAddr == ptDs->m_tSndToAddr)
		{
			ptDs->m_emSwitchType = pIter->m_emSwitchType;
			ptDs->m_tMapedAddr = pIter->m_tMapedAddr;
			tList.erase(pIter);
			m_dwDsNum--;
			return TRUE;
		}
		pIter++;
	}
	return FALSE;
}

BOOL32 CConfSwitchRulesInfo::DelNode(TUmsDsData* ptDs, DSRTPSID& dLocalId)
{
	if (NULL == ptDs || NULL == m_pHead)
	{
		return FALSE;
	}

	if (m_pHead->m_tData.m_tSrcAddr == ptDs->m_tRcvFromAddr)
	{
		DelMemberFromSndList(m_pHead->m_tData.m_lSndList, ptDs);
		dLocalId = m_pHead->m_tData.m_dLocalID;
//		if (m_pHead->m_tData.m_lSndList.empty())
//		{
//			CSwitchRulesBufItor ptDelCur = m_pHead;
//			m_pHead = m_pHead->m_ptNext;
//			ptDelCur->m_ptNext = NULL;

//			m_tSwitchRulesList.FreeBuff(ptDelCur);
//			m_dwListNum--;
//		}
		return TRUE;
	}

	CSwitchRulesBufItor ptPre = m_pHead;
	CSwitchRulesBufItor ptCur = m_pHead->m_ptNext;
	while ( ptCur )
	{
		if (ptCur->m_tData.m_tSrcAddr == ptDs->m_tRcvFromAddr)
		{
			DelMemberFromSndList(ptCur->m_tData.m_lSndList, ptDs);
			dLocalId = ptCur->m_tData.m_dLocalID;
//			if (ptCur->m_tData.m_lSndList.empty())
//			{
//				ptPre->m_ptNext = ptCur->m_ptNext;
//				ptCur->m_ptNext = NULL;

//				m_tSwitchRulesList.FreeBuff(ptCur);
//				m_dwListNum--;
//			}	
			return TRUE;
		}

		if (ptCur->m_tData.m_tSrcAddr > ptDs->m_tRcvFromAddr)
		{
			return FALSE;
		}

		ptPre = ptCur;
		ptCur = ptCur->m_ptNext;
	}
	return FALSE;
}

void CConfSwitchRulesInfo::FreeALL()
{
	m_tSwitchRulesList.FreeBuff(m_pHead);
	m_dwListNum = 0;
	m_dwDsNum = 0;
	m_pHead = NULL;
}
