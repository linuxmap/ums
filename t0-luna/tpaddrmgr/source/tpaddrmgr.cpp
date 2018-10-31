#include "tpaddrmgr.h"

BOOL CTPAddrMgr::IsEnableUpdateAndSetStatus( EmGetRegInfoType emType )
{
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		{
			if( em_Idle == m_emStatus )
			{
				SetStatus( em_Updating_CNS );
				return TRUE;
			}
			else if( em_Updating_CNS == m_emStatus )
			{
				return FALSE;
			}
			else if( em_Updating_UMS == m_emStatus )
			{
				SetStatus( em_Updating_ALL );
				return TRUE;
			}
			else if( em_EnableNty == m_emStatus )
			{
				msgprint("[CTPAddrMgr::IsEnableUpdateAndSetStatus]type->%d, status->%d\n", emType, m_emStatus );
				return FALSE;
			}
		}
		break;
	case emGetRegInfoType_UMS:
		{
			if( em_Idle == m_emStatus )
			{
				SetStatus( em_Updating_UMS );
				return TRUE;
			}
			else if( em_Updating_UMS == m_emStatus )
			{
				return FALSE;
			}
			else if( em_Updating_CNS == m_emStatus )
			{
				SetStatus( em_Updating_ALL );
				return TRUE;
			}
			else if( em_EnableNty == m_emStatus )
			{
				msgprint("[CTPAddrMgr::IsEnableUpdateAndSetStatus]type->%d, status->%d\n", emType, m_emStatus );
				return FALSE;
			}
		}
	case emGetRegInfoType_ALL:
		{
			if( em_Idle == m_emStatus )
			{
				SetStatus( em_Updating_ALL );
				return TRUE;
			}
			else if( em_Updating_UMS == m_emStatus )
			{
				SetStatus( em_Updating_ALL );
				return TRUE;
			}
			else if( em_Updating_CNS == m_emStatus )
			{
				SetStatus( em_Updating_ALL );
				return TRUE;
			}
			else if( em_EnableNty == m_emStatus )
			{
				msgprint("[CTPAddrMgr::IsEnableUpdateAndSetStatus]type->%d, status->%d\n", emType, m_emStatus );
				return FALSE;
			}
		}
		break;
	default:
		msgprint("[CTPAddrMgr::IsEnableUpdateAndSetStatus]type->%d, status->%d\n", emType, m_emStatus );
		break;
	}

		return FALSE;
}

void CTPAddrMgr::StatusStrategy( EmGetRegInfoType emType )
{
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		if( em_Updating_CNS == m_emStatus )
		{
			SetStatus( em_EnableNty );
		}
		else if( em_Updating_ALL == m_emStatus )
		{
			SetStatus( em_Updating_UMS );
		}
		else
		{
			msgprint("[CTPAddrMgr::StatusStrategy]error type->%d, status->%d\n", emType, m_emStatus);
		}
		break;
	case emGetRegInfoType_UMS:
		if( em_Updating_UMS == m_emStatus )
		{
			SetStatus( em_EnableNty );
		}
		else if( em_Updating_ALL == m_emStatus )
		{
			SetStatus( em_Updating_CNS );
		}
		else
		{
			msgprint("[CTPAddrMgr::StatusStrategy]error type->%d, status->%d\n", emType, m_emStatus);
		}
		break;
	case emGetRegInfoType_ALL:
		SetStatus( em_EnableNty );
		break;
	default:
		msgprint("[CTPAddrMgr::StatusStrategy]default error type->%d, status->%d\n", emType, m_emStatus);
		break;
	}
}

void CTPAddrMgr::AddOneUserNty( const TTPAddrNtyUser &tTPAddNtyUser )
{
	m_tNtyUserList.push_back( tTPAddNtyUser );
}

u16 CTPAddrMgr::GetUserNtyNum( )
{
	if( m_tNtyUserList.empty() )
	{
		return 0;
	}
	return m_tNtyUserList.size();
}              


void CTPAddrMgr::AddOnePack( const TTPSipRegPackInfo &tPackInfo,
							 const TTPSipRegInfo &tSipRegInfo,
							 const EmGetRegInfoType &emType )
{
	if( 0 == tPackInfo.m_wTotalPackNum )
	{
		//无此类信息,清楚BAK
		m_cSipRegInfo.RemoveAllBak( emGetRegInfoType_ALL );
	}
	else
	{
		if( 1 == tPackInfo.m_wPackSeq )
		{
			//第一包清BAK
			m_cSipRegInfo.RemoveAllBak( emGetRegInfoType_ALL );
		}
		//来一包加一包
 		m_cSipRegInfo.AddSipRegInfoBak( tSipRegInfo );
	}
	//全部发完,包括没包的情况下
	if( tPackInfo.m_wPackSeq == tPackInfo.m_wTotalPackNum )
	{
	 	//替换，由于发送给界面的每次在一个函数内完成，因此不用担心正在发送给界面数据时候被替换
	 	m_cSipRegInfo.Replace( emType );

		StatusStrategy( emType );
		
		//设置状态，可以通知界面
		SetStatus( em_EnableNty );
	}
}


BOOL CTPAddrMgr::GetUserNty( TTPAddrNtyUser *ptTPAddrNtyUser, u16 wSize )
{
	if( NULL == ptTPAddrNtyUser )
	{
		msgprint("[CTPAddrMgr::GetUserNty] ptTPAddrNtyUser = NULL\n");
		return FALSE;
	}
	if( m_tNtyUserList.empty() )
	{
		return TRUE;
	}
	std::list<TTPAddrNtyUser>::iterator iterator;
	u16 wIndex = 0;
	for( iterator = m_tNtyUserList.begin(); iterator != m_tNtyUserList.end(); ++iterator )
	{
		if( wIndex >= wSize )
		{
			msgprint("[CTPAddrMgr::GetUserNty]wIndex->%d>= wSize->%d\n", wIndex, wSize);
			return FALSE;
		}
		ptTPAddrNtyUser[wIndex] = *iterator;
		++wIndex;
	}
	return TRUE;

}

	
CSipRegInfo::CSipRegInfo()
{
	Clear();
}

void CSipRegInfo::Clear()
{
	m_tSipRegInfoList.clear();
	m_tSipRegInfoList_Bak.clear();
}


void CSipRegInfo::RemoveAll( EmGetRegInfoType emType )
{
	if( m_tSipRegInfoList.empty() )
	{
		return;
	}
	if( emGetRegInfoType_ALL == emType )
	{
		m_tSipRegInfoList.clear();
		return;
	}
	EmTPEndpointType emEndType = emTPEndpointTypeUnknown;
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		emEndType = emTPEndpointTypeCNS;
		break;
	case emGetRegInfoType_UMS:
		emEndType = emTPEndpointTypeUMS;
		break;
	default:
		emEndType = emTPEndpointTypeUnknown;
		msgprint("[RemoveAll]Unknown Type ->%d\n", emType);
		return;
	}
	std::list<TTPSipRegInfo>::iterator iterator;
	for( iterator = m_tSipRegInfoList.begin(); iterator != m_tSipRegInfoList.end(); )
	{
		if( emEndType == iterator->m_emSelfType )
		{
			iterator = m_tSipRegInfoList.erase( iterator );
		}
		else
		{
			++iterator;
		}
	}
}


void CSipRegInfo::AddSipRegInfo( const TTPSipRegInfo &tSipRegInfo )
{
	m_tSipRegInfoList.push_back( tSipRegInfo );
}

void CSipRegInfo::RemoveAllBak( EmGetRegInfoType emType )
{
	if( m_tSipRegInfoList_Bak.empty() )
	{
		return;
	}
	if( emGetRegInfoType_ALL == emType )
	{
		m_tSipRegInfoList_Bak.clear();
		return;
	}
	EmTPEndpointType emEndType = emTPEndpointTypeUnknown;
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		emEndType = emTPEndpointTypeCNS;
		break;
	case emGetRegInfoType_UMS:
		emEndType = emTPEndpointTypeUMS;
		break;
	default:
		emEndType = emTPEndpointTypeUnknown;
		msgprint("[RemoveAllBak]Unknown Type ->%d\n", emType);
		return;
	}
	std::list<TTPSipRegInfo>::iterator iterator;
	for( iterator = m_tSipRegInfoList_Bak.begin(); iterator != m_tSipRegInfoList_Bak.end(); )
	{
		if( emEndType == iterator->m_emSelfType )
		{
			iterator = m_tSipRegInfoList_Bak.erase( iterator );
		}
		else
		{
			++iterator;
		}
	}
}
	
void CSipRegInfo::AddSipRegInfoBak( const TTPSipRegInfo &tSipRegInfo )
{
	m_tSipRegInfoList_Bak.push_back( tSipRegInfo );
}
	
	
void CSipRegInfo::Replace( EmGetRegInfoType emType )
{
	RemoveAll( emType );
	std::list<TTPSipRegInfo>::iterator iterator;
	if(m_tSipRegInfoList_Bak.empty())
	{
		return;
	}
	for( iterator = m_tSipRegInfoList_Bak.begin(); iterator != m_tSipRegInfoList_Bak.end(); iterator++ )
	{
		m_tSipRegInfoList.push_back( *iterator );
	}

	RemoveAllBak( emGetRegInfoType_ALL );
}
	
u16 CSipRegInfo::GetPackTotalNum( EmGetRegInfoType emType )
{
	u16 wIndex = 0;
	u16 wNum = 0;
	if( m_tSipRegInfoList.empty() )
	{
		return 0;
	}
	std::list<TTPSipRegInfo>::iterator iterator;
		
	if( emGetRegInfoType_ALL == emType )
	{
		wNum = m_tSipRegInfoList.size();
		return wNum;
	}
	EmTPEndpointType emEndType = emTPEndpointTypeUnknown;
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		emEndType = emTPEndpointTypeCNS;
		break;
	case emGetRegInfoType_UMS:
		emEndType = emTPEndpointTypeUMS;
		break;
	default:
		emEndType = emTPEndpointTypeUnknown;
		msgprint("[GetPackTotalNum]Unknown Type ->%d\n", emType);
		return 0;
	}

	for( iterator = m_tSipRegInfoList.begin(); iterator != m_tSipRegInfoList.end(); iterator++ )
	{
		if( emEndType == iterator->m_emSelfType )
		{
			++wNum;
		}
	}
	return wNum;
}


u16 CSipRegInfo::GetPackTotalNumBak( EmGetRegInfoType emType )
{
	u16 wIndex = 0;
	u16 wNum = 0;
	if( m_tSipRegInfoList_Bak.empty() )
	{
		return 0;
	}
	std::list<TTPSipRegInfo>::iterator iterator;
	
	if( emGetRegInfoType_ALL == emType )
	{
		wNum = m_tSipRegInfoList_Bak.size();
		return wNum;
	}
	EmTPEndpointType emEndType = emTPEndpointTypeUnknown;
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		emEndType = emTPEndpointTypeCNS;
		break;
	case emGetRegInfoType_UMS:
		emEndType = emTPEndpointTypeUMS;
		break;
	default:
		emEndType = emTPEndpointTypeUnknown;
		msgprint("[GetPackTotalNumBak]Unknown Type ->%d\n", emType);
		return 0;
	}
		
	for( iterator = m_tSipRegInfoList_Bak.begin(); iterator != m_tSipRegInfoList_Bak.end(); iterator++ )
	{
		if( emEndType == iterator->m_emSelfType )
		{
			++wNum;
		}
	}
	return wNum;
}


BOOL CSipRegInfo::GetPack( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize )
{
	if( m_tSipRegInfoList.empty() )
	{
		return TRUE;
	}
	if( NULL == ptSipRegInfo )
	{
		return FALSE;
	}
	std::list<TTPSipRegInfo>::iterator iterator;
	u16 wIndex = 0;

	//全部，取出全包
	if( emGetRegInfoType_ALL == emType )
	{
		for( iterator = m_tSipRegInfoList.begin(); iterator!=m_tSipRegInfoList.end(); iterator++ )
		{
			if( wIndex < wSize )
			{
				ptSipRegInfo[wIndex] = *iterator;
				++wIndex;
			}
			else
			{
				msgprint("[GetPack]OutOfBounds, emType->%d, wIndex->%d, wSize->%d\n",emType, wIndex, wSize );
				return FALSE;
			}
		}
		return TRUE;
	}
	EmTPEndpointType emEndType = emTPEndpointTypeUnknown;
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		emEndType = emTPEndpointTypeCNS;
		break;
	case emGetRegInfoType_UMS:
		emEndType = emTPEndpointTypeUMS;
		break;
	default:
		emEndType = emTPEndpointTypeUnknown;
		msgprint("[GetPack]Unknown Type ->%d\n", emType);
		return FALSE;
	}
	for( iterator = m_tSipRegInfoList.begin(); iterator!=m_tSipRegInfoList.end(); iterator++ )
	{
		if( emEndType == iterator->m_emSelfType )
		{
			if( wIndex < wSize )
			{
				ptSipRegInfo[wIndex] = *iterator;
				++wIndex;
			}
			else
			{
				msgprint("[GetPack]OutOfBounds, emEndType->%d, wIndex->%d, wSize->%d\n",emEndType, wIndex, wSize );
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CSipRegInfo::GetPackBak( EmGetRegInfoType emType, TTPSipRegInfo *ptSipRegInfo, u16 wSize )
{
	if( m_tSipRegInfoList_Bak.empty() )
	{
		return TRUE;
	}
	if( NULL == ptSipRegInfo )
	{
		return FALSE;
	}
	std::list<TTPSipRegInfo>::iterator iterator;
	u16 wIndex = 0;

	//全部，取出全包
	if( emGetRegInfoType_ALL == emType )
	{
		for( iterator = m_tSipRegInfoList_Bak.begin(); iterator != m_tSipRegInfoList_Bak.end(); iterator++ )
		{
			if( wIndex < wSize )
			{
				ptSipRegInfo[wIndex] = *iterator;
				++wIndex;
			}
			else
			{
				msgprint("[GetPackBak]OutOfBounds, emType->%d, wIndex->%d, wSize->%d\n",emType, wIndex, wSize );
				return FALSE;
			}
				
		}
		return TRUE;
	}
	EmTPEndpointType emEndType = emTPEndpointTypeUnknown;
	switch( emType )
	{
	case emGetRegInfoType_CNS:
		emEndType = emTPEndpointTypeCNS;
		break;
	case emGetRegInfoType_UMS:
		emEndType = emTPEndpointTypeUMS;
		break;
	default:
		emEndType = emTPEndpointTypeUnknown;
		msgprint("[GetPackBak]Unknown Type ->%d\n", emType);
		return FALSE;
	}
	for( iterator = m_tSipRegInfoList_Bak.begin(); iterator != m_tSipRegInfoList_Bak.end(); iterator++ )
	{
		if( emEndType == iterator->m_emSelfType )
		{
			if( wIndex < wSize )
			{
				ptSipRegInfo[wIndex] = *iterator;
				++wIndex;
			}
			else
			{
				msgprint("[GetPackBak]OutOfBounds, emEndType->%d, wIndex->%d, wSize->%d\n",emEndType, wIndex, wSize );
				return FALSE;
			}
		}
	}
	return TRUE;
}



void CSipRegInfo::OutputAll()
{
	std::list<TTPSipRegInfo>::iterator iterator;
	msgprint("***********InfoList*****************\n");
	//u16 wIndex = 0;
	u16 wIndex2 = 0;
	for( iterator = m_tSipRegInfoList.begin(); iterator != m_tSipRegInfoList.end(); iterator++ )
	{
		//MsgPrintHintLog("******%d********\n", wIndex);
		msgprint("***Type = %d*****\n", iterator->m_emSelfType);
		for( wIndex2 = 0; wIndex2 < iterator->m_wAliasNum; wIndex2++ )
		{
			msgprint("Alias Type->%d, Alias Name->%s\n", iterator->m_atAlias[wIndex2].m_byType, iterator->m_atAlias[wIndex2].m_abyAlias );
		}
		
	}
	
	msgprint("\n\n\n**********InfoListBak*****************\n");
	//wIndex = 0;
	for( iterator = m_tSipRegInfoList_Bak.begin(); iterator != m_tSipRegInfoList_Bak.end(); iterator++ )
	{
		//MsgPrintHintLog("******%d********\n", wIndex);
		msgprint("***Type = %d*****\n", iterator->m_emSelfType);
		for( wIndex2 = 0; wIndex2 < iterator->m_wAliasNum; wIndex2++ )
		{
			msgprint("Alias Type->%d, Alias Name->%s\n", iterator->m_atAlias[wIndex2].m_byType, iterator->m_atAlias[wIndex2].m_abyAlias );
		}	
	}
}

CTPAddrMgrEx::CTPAddrMgrEx()
{
	m_bSipEnd = FALSE;
	m_bGkEnd = FALSE;
	m_wUseCount = 2;
}

CTPAddrMgrEx::~CTPAddrMgrEx()
{

}

CTPAddrMgrEx& CTPAddrMgrEx::Instance()
{
	static CTPAddrMgrEx cMgr;
	return cMgr;
}

void CTPAddrMgrEx::AddPack(const TRegPackInfoEx& tPackInfo, const TUmsRegPackEx& tRegInfo)
{
	if (!m_bSipEnd)
	{
		m_umsInfo.push_back(tRegInfo);
	}

	if (tPackInfo.m_tPackInfo.m_wTotalPackNum == tPackInfo.m_tPackInfo.m_wPackSeq)
	{
		m_bSipEnd = TRUE;
	}
}

void CTPAddrMgrEx::AddPack(const TRegPackInfoEx& tPackInfo, const TCnsRegPackEx& tRegInfo)
{
	if (!m_bSipEnd)
	{
		m_cnsInfo.push_back(tRegInfo);
	}
	
	if (tPackInfo.m_tPackInfo.m_wTotalPackNum == tPackInfo.m_tPackInfo.m_wPackSeq)
	{
		m_bSipEnd = TRUE;
	}
}

void CTPAddrMgrEx::AddPack(const TTPMtRegInfo& tMtInfo)
{
	if (!m_bGkEnd)
	{
		m_mtInfo.push_back(tMtInfo);
	}

	if (tMtInfo.m_bIsEnd)
	{
		m_bGkEnd = TRUE;
	}
}

void CTPAddrMgrEx::AddPack(const TTPMcuRegInfo& tMcuInfo)
{
	if (!m_bGkEnd)
	{
		m_mcuInfo.push_back(tMcuInfo);
	}

	if (tMcuInfo.m_bIsEnd)
	{
		m_bGkEnd = TRUE;
	}
}

BOOL32 CTPAddrMgrEx::IsSipEnd() const
{
	return m_bSipEnd;
}

BOOL32 CTPAddrMgrEx::IsGkEnd() const
{
	return m_bGkEnd;
}

void CTPAddrMgrEx::ClearSipInfo()
{
	m_cnsInfo.clear();
	m_umsInfo.clear();
	m_bSipEnd = FALSE;

	ClearUser();
}

//Add by tanxiaodong 2013-08-07.
void CTPAddrMgrEx::ClearCnsInfo()
{
	m_cnsInfo.clear();
	m_bSipEnd = FALSE;
}

void CTPAddrMgrEx::ClearUmsInfo()
{
	m_umsInfo.clear();
	m_bSipEnd = FALSE;
}
//End to add.

void CTPAddrMgrEx::ClearGkInfoForCns()
{
	m_mtInfo.clear();
	m_bGkEnd = FALSE;
}

void CTPAddrMgrEx::ClearGkInfo()
{
	m_mtInfo.clear();
	m_mcuInfo.clear();
	m_bGkEnd = FALSE;

	ClearUser();
}

void CTPAddrMgrEx::AddUser(const TTPAddrNtyUser& tUser)
{
	for (u16 wIndex = 0; wIndex < m_userList.size(); ++wIndex)
	{
		if (m_userList[wIndex].m_dwIID == tUser.m_dwIID)
		{
			return ;
		}
	}

	m_wUseCount = 2;
	m_userList.push_back(tUser);
}

void CTPAddrMgrEx::AddUserForCns(const TTPAddrNtyUser& tUser)
{
	for (u16 wIndex = 0; wIndex < m_userList.size(); ++wIndex)
	{
		if (m_userList[wIndex].m_wUserData == tUser.m_wUserData)
		{
			return ;
		}
	}
	
	m_wUseCount = 2;
	m_userList.push_back(tUser);
}

void CTPAddrMgrEx::DelUser(const TTPAddrNtyUser& tUser)
{
	for (u16 wIndex = 0; wIndex < m_userList.size(); ++wIndex)
	{
		if (m_userList[wIndex].m_dwIID == tUser.m_dwIID)
		{
			m_userList.erase(m_userList.begin()+wIndex);
			break;
		}
	}
}

void CTPAddrMgrEx::ClearUser()
{
	--m_wUseCount;
	if (0 == m_wUseCount)
	{
		m_userList.clear();
	}
}

u16 CTPAddrMgrEx::GetUserNums() const
{
	return m_userList.size();
}

u16 CTPAddrMgrEx::GetUserNty(TTPAddrNtyUser *ptTPAddrNtyUser, u16 wSize)
{
	if(NULL == ptTPAddrNtyUser || 0 == wSize)
	{
		return 0;
	}

	if(m_userList.empty() )
	{
		return 0;
	}

	std::vector<TTPAddrNtyUser>::iterator iterator;
	u16 wIndex = 0;
	for( iterator = m_userList.begin(); iterator != m_userList.end(); ++iterator )
	{
		if( wIndex >= wSize )
		{
			return wIndex;
		}
		ptTPAddrNtyUser[wIndex] = *iterator;
		++wIndex;
	}

	return wIndex;
}

u16 CTPAddrMgrEx::GetCnsPackNum() const
{
	return m_cnsInfo.size();
}

u16 CTPAddrMgrEx::GetCnsRegPack(TCnsRegPackEx* ptCnsInfo, u16 wSize)
{
	if (NULL == ptCnsInfo || 0 == wSize)
	{
		return 0;
	}

	if (0 == m_cnsInfo.size())
	{
		return 0;
	}

	std::vector<TCnsRegPackEx>::iterator iterator;
	u16 wIndex = 0;
	for( iterator = m_cnsInfo.begin(); iterator != m_cnsInfo.end(); ++iterator )
	{
		if( wIndex >= wSize )
		{
			return wIndex;
		}
		ptCnsInfo[wIndex] = *iterator;
		++wIndex;
	}
	
	return wIndex;
}

u16 CTPAddrMgrEx::GetUmsPackNum() const
{
	return m_umsInfo.size();
}

u16 CTPAddrMgrEx::GetUmsRegPack(TUmsRegPackEx* ptUmsInfo, u16 wSize)
{
	if (NULL == ptUmsInfo || 0 == wSize)
	{
		return 0;
	}
	
	if (0 == m_umsInfo.size())
	{
		return 0;
	}
	
	std::vector<TUmsRegPackEx>::iterator iterator;
	u16 wIndex = 0;
	for( iterator = m_umsInfo.begin(); iterator != m_umsInfo.end(); ++iterator )
	{
		if( wIndex >= wSize )
		{
			return wIndex;
		}
		ptUmsInfo[wIndex] = *iterator;
		++wIndex;
	}
	
	return wIndex;
}

u16 CTPAddrMgrEx::GetMtPackNum() const
{
	return m_mtInfo.size();
}

u16 CTPAddrMgrEx::GetMtRegPack(TTPMtRegInfo* ptMtInfo, u16 wSize)
{
	if (NULL == ptMtInfo || 0 == wSize)
	{
		return 0;
	}
	
	if (0 == m_mtInfo.size())
	{
		return 0;
	}
	
	std::vector<TTPMtRegInfo>::iterator iterator;
	u16 wIndex = 0;
	for( iterator = m_mtInfo.begin(); iterator != m_mtInfo.end(); ++iterator )
	{
		if( wIndex >= wSize )
		{
			return wIndex;
		}
		ptMtInfo[wIndex] = *iterator;
		++wIndex;
	}
	
	return wIndex;
}

u16 CTPAddrMgrEx::GetMcuPackNum() const
{
	return m_mcuInfo.size();
}

u16 CTPAddrMgrEx::GetMcuRegPack(TTPMcuRegInfo* ptMcuInfo, u16 wSize)
{
	if (NULL == ptMcuInfo || 0 == wSize)
	{
		return 0;
	}
	
	if (0 == m_mcuInfo.size())
	{
		return 0;
	}
	
	std::vector<TTPMcuRegInfo>::iterator iterator;
	u16 wIndex = 0;
	for( iterator = m_mcuInfo.begin(); iterator != m_mcuInfo.end(); ++iterator )
	{
		if( wIndex >= wSize )
		{
			return wIndex;
		}
		ptMcuInfo[wIndex] = *iterator;
		++wIndex;
	}
	
	return wIndex;
}