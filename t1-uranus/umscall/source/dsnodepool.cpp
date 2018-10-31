#include "dsnodepool.h"
#include "tptype.h"
#include "tpxmltype.h"
#include "tplog.h"


/********************************************************************
	函 数 名:    CDsPortPool
	全    名:  	 CDsPortPool::CDsPortPool
	访问权限:    public 
	返 回 值:    
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
CDsPortPool::CDsPortPool()
{
	m_hLastHandle = 0;
}

/********************************************************************
	函 数 名:    ~CDsPortPool
	全    名:  	 CDsPortPool::~CDsPortPool
	访问权限:    public 
	返 回 值:    
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
CDsPortPool::~CDsPortPool()
{
	Destroy();
}

void CDsPortPool::AddDs( u32 Handle, TUmsDsData * const aNewDsData, u16 wDsNumm )
{
	u16 wIndex = 0;
    CDsPortNode* pRcvFrom;
	CDsPortNode* pSndTo;
    TDsType tEdge;
	tEdge.dwHandle = Handle;
	tEdge.dwDsType = 0;
	tEdge.wSubDsType = emDS_SubType_Unknow;
 
	TTPDsData tDsData;

	for( wIndex = 0; wIndex < wDsNumm; wIndex++ )
	{
		pRcvFrom = AddPort( Handle, aNewDsData[wIndex].m_tRcvFromAddr );
		pSndTo = AddPort( Handle, aNewDsData[wIndex].m_tSndToAddr );
		AddDs( tEdge, &*pRcvFrom, &*pSndTo, tDsData );
	}
	
}

void CDsPortPool::DelDs( u32 Handle, CDsListPtr pcDelList )
{
	CDsListPtr pTmp = pcDelList;
    CDsPortNode* pRcvFrom;
	CDsPortNode* pSndTo;

	while( pTmp )
	{
		pRcvFrom = AddPort( Handle, pTmp->m_tData.m_tRcvFromAddr );
		pSndTo = AddPort( Handle, pTmp->m_tData.m_tSndToAddr );

		DestroyDs( &*pRcvFrom, &*pSndTo );
		pTmp = pTmp->m_ptNext;
	}
}

BOOL CDsPortPool::DestroyDs( CDsPortNode* pRcvFrom,  CDsPortNode* pSndTo )
{
	BOOL bRet = FALSE;
	std::list<CDsEdge>::iterator itIterator;
	TTPDsData  tCnDsData;
	for ( itIterator = pRcvFrom->m_vtEdge.begin(); itIterator != pRcvFrom->m_vtEdge.end();  )
	{
		if ( itIterator->m_pcRemoteNode == &(*pSndTo) )
		{
			//删除对此edge的引用
			itIterator->m_pcRemoteNode->RemoveRefDsEdge( &(*pRcvFrom) );
			//删除此edge
			itIterator = pRcvFrom->m_vtEdge.erase( itIterator );
			bRet = TRUE;					
		}
		else
		{
			itIterator++;
		}
	}

	if( pRcvFrom->m_vpRefEdge.empty() && pRcvFrom->m_vtEdge.empty() )
	{
		m_mapPort.erase( pRcvFrom->GetAddr() );
	}

	if( pSndTo->m_vpRefEdge.empty() && pSndTo->m_vtEdge.empty() )
	{
		m_mapPort.erase( pSndTo->GetAddr() );
	}
	return bRet;
}

CDsPortNode*  CDsPortPool::AddPort(  u32 dwHandle, const TTPTransAddr& tAddr  )
{
	CDsPortNode cPortNode(tAddr);
	TDsType tPortType;
	tPortType.dwHandle = dwHandle;
	cPortNode.SetPortType( tPortType );
	TTPTransAddr tAddr1 = tAddr;
	std::pair<std::map <TTPTransAddr,CDsPortNode> ::iterator,bool> ret;
	ret = m_mapPort.insert( std::make_pair( tAddr1,cPortNode ) );
	return &ret.first->second;
		
	
}

/********************************************************************
	函 数 名:    GetDSHandle
	全    名:  	 CDsPortPool::GetDSHandle
	访问权限:    public 
	返 回 值:    u32
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
u32 CDsPortPool::GetDSHandle()
{
	return ++m_hLastHandle;
}


BOOL CDsPortPool::AddDs( const TDsType &tEdge, 
		 CDsPortNode* pcPortRcvFrom ,
		 CDsPortNode* pcPortSndTo,
				TTPDsData& tDsData)
{
	if ( !pcPortRcvFrom || !pcPortSndTo )
	{
		msgprint( "[error] [CDsPortPool::AddDs]pcPortRcv or pcPortSnd is null\n");
		return FALSE;
	}

	//写入输出值
	tDsData.m_tRcvFromAddr = pcPortRcvFrom->GetAddr();
	tDsData.m_tSndToAddr = pcPortSndTo->GetAddr();

	if ( !pcPortRcvFrom->AddDsEdge( tEdge, pcPortSndTo ) )
	{
		return FALSE;
	}
	
	if ( !pcPortSndTo->AddRefDsEdge( pcPortRcvFrom ) )
	{
		msgprint("[CDsPortPool::AddRefDsEdge] [error] AddRefDsEdge dwTpye->%d, ("TPIPFORMAT":%d)->("TPIPFORMAT":%d)\n",
			tEdge.dwDsType,
			Tpu32ToIP(pcPortRcvFrom->GetAddr().m_dwIP),pcPortRcvFrom->GetAddr().m_wPort,
			Tpu32ToIP(pcPortSndTo->GetAddr().m_dwIP),pcPortSndTo->GetAddr().m_wPort);
		return FALSE;
	}
	return TRUE;
}

/********************************************************************
	@brief    	Dfs_Init
	@param  	CDsPortPool::Dfs_Init
	@return    	void
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/03/14     1.0		  sernger			create
*********************************************************************/
void CDsPortPool::Dfs_Init( u32 dwHandle, EmTPDsNode emDsNode )
{
	m_dwDsNum = 0;
	u32 PortNum = 0;
	if ( !m_mapPort.empty() )
	{
		std::map<TTPTransAddr,CDsPortNode>::iterator  iter;
		for(iter = m_mapPort.begin(); iter != m_mapPort.end(); iter++)
		{
			iter->second.m_emPortColour = CDsPortNode::EmColour_White;
		}
		
		u8 byDepth = 0;
		if ( emTp_Ds == emDsNode )
		{
			for(iter = m_mapPort.begin(); iter != m_mapPort.end(); iter++)
			{		
				if ( !iter->second.IsExistHandleInRef( dwHandle )
					&& CDsPortNode::EmColour_White == iter->second.m_emPortColour
					&& iter->second.IsExistHandle( dwHandle ) 
					&& !iter->second.m_vtEdge.empty() )
				{
					PortNum++;
					byDepth = 0;
					OspPrintf( 1, 0, "\n| handle:%d",  dwHandle );
					Dfs( &iter->second, byDepth );
				}
			}

			OspPrintf( 1, 0, "\n \n dwHandle:%d  Ds Num:%d\n",  dwHandle, m_dwDsNum );
		}
		else if( emTp_Node == emDsNode )
		{
			OspPrintf( 1, 0, "\n| handle:%d ",  dwHandle );
			for(iter = m_mapPort.begin(); iter != m_mapPort.end(); iter++)
			{		
				if (  CDsPortNode::EmColour_White == iter->second.m_emPortColour
					&& iter->second.IsExistHandle( dwHandle ))
				{
					PortNum++;
					byDepth = 0;					
					iter->second.ShowNode( byDepth );
				}
			}

			OspPrintf( 1, 0, "\n \n dwHandle:%d  PortNum:%d \n",  dwHandle, PortNum );

		}
	
	}
}

/********************************************************************
	@brief    	Dfs
	@param  	CDsPortPool::Dfs
	@return    	void
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/03/14     1.0		  sernger			create
*********************************************************************/
void CDsPortPool::Dfs( CDsPortNode* pcNode, u8 byDepth )
{
	if ( !m_mapPort.empty() )
	{
		pcNode->m_emPortColour = CDsPortNode::EmColour_Gray;

		if ( byDepth >= 255 )
		{
			msgprint("[CDsPortPool::Dfs] too deep \n" );
			return;
		}

		pcNode->ShowNode( byDepth );
		byDepth += 3;		
		std::list<CDsEdge>::iterator itIterator;
		if ( !pcNode->m_vtEdge.empty() )
		{
			for ( itIterator = pcNode->m_vtEdge.begin(); itIterator != pcNode->m_vtEdge.end(); itIterator++ )
			{
				m_dwDsNum++;
				pcNode->ShowEdge( byDepth, itIterator );
				Dfs( itIterator->m_pcRemoteNode, byDepth );
			}
		}
		pcNode->m_emPortColour = CDsPortNode::EmColour_Black;
	}	
}
/********************************************************************
	函 数 名:    Show
	全    名:  	 CDsPortPool::Show
	访问权限:    public 
	返 回 值:    void
	参    数: 	 u32 Handle
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
void CDsPortPool::Show(  u32 Handle, EmTPDsNode emDsNode )
{
	Dfs_Init( Handle, emDsNode );
}

/********************************************************************
	函 数 名:    Destroy
	全    名:  	 CDsPortPool::Destroy
	访问权限:    protected 
	返 回 值:    void
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
void CDsPortPool::Destroy()
{
	//销毁node链表
}



////////////
CDsPortNode::CDsPortNode( const TTPTransAddr &tAddr )
{
	Init( tAddr );

}

CDsPortNode::~CDsPortNode()
{

}

/********************************************************************
	函 数 名:    Init
	全    名:  	 CDsPortNode::Init
	访问权限:    public 
	返 回 值:    void
	参    数: 	 const TTPTransAddr &tAddr
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
void CDsPortNode::Init( const TTPTransAddr &tAddr )
{
	SetAddr( tAddr );
	memset( &m_tCnNetBufPara, 0, sizeof(m_tCnNetBufPara) );
	m_vtEdge.clear();
	m_vpRefEdge.clear();
}

/********************************************************************
	函 数 名:    Destroy
	全    名:  	 CDsPortNode::Destroy
	访问权限:    public 
	返 回 值:    void
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
void CDsPortNode::Destroy( )
{
	m_vtEdge.clear();
	m_vpRefEdge.clear();
	m_tAddr.Clear();
	memset( &m_tCnNetBufPara, 0, sizeof(TTPCnNetBufPara) );
}

/********************************************************************
	@brief    	AddDsEdge
	@param  	CDsPortNode::AddDsEdge
	@return    	BOOL
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/02/29     1.0		  sernger			create
*********************************************************************/
BOOL CDsPortNode::AddDsEdge( const TDsType& tDsType, CDsPortNode* pcRemoteNode )
{
	std::list<CDsEdge>::iterator itIterator;
	itIterator = FindDsEdge( pcRemoteNode );
	if ( itIterator != m_vtEdge.end() )
	{
		
		itIterator->AddDsType( tDsType );
		
		//Set active when adding edge
		if ( itIterator->IsAcitve() )
		{
			return FALSE;
		}
		else
		{
			itIterator->SetAcitve( TRUE );
			return TRUE;
		}	
	}
	else
	{
		CDsEdge cDsEdge;
		cDsEdge.m_pcRemoteNode = pcRemoteNode;
		cDsEdge.AddDsType( tDsType );
		//Set active when adding edge
		cDsEdge.SetAcitve( TRUE );

		m_vtEdge.push_back( cDsEdge );
		return TRUE;
	}
	
}

/********************************************************************
	@brief    	FindDsEdge
	@param  	CDsPortNode::FindDsEdge
	@return    	std::list<CDsEdge>::iterator
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/02/29     1.0		  sernger			create
*********************************************************************/
std::list<CDsEdge>::iterator CDsPortNode::FindDsEdge( CDsPortNode* pcRemoteNode )
{
	std::list<CDsEdge>::iterator itIterator;
	if ( !m_vtEdge.empty() )
	{
		for ( itIterator = m_vtEdge.begin(); itIterator != m_vtEdge.end(); itIterator++ )
		{
			if ( pcRemoteNode->GetAddr() == itIterator->m_pcRemoteNode->GetAddr() )
			{
				return itIterator;
			}
		}
	}	
	return m_vtEdge.end(); 
}

/********************************************************************
	@brief    	AddRefDsEdge
	@param  	CDsPortNode::AddRefDsEdge
	@return    	BOOL
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/02/29     1.0		  sernger			create
*********************************************************************/
BOOL CDsPortNode::AddRefDsEdge( CDsPortNode* pcRefNode )
{
	std::list<CDsPortNode*>::iterator itIterator;
	itIterator = FindRefDsEdge( pcRefNode );
	if ( itIterator !=  m_vpRefEdge.end() )
	{
		msgprint("[CDsPortNode::AddRefDsEdge] "TPIPFORMAT":%d,already exist\n", 
			Tpu32ToIP( pcRefNode->GetAddr().GetIP() ) ,
			pcRefNode->GetAddr().GetPort() );
		return TRUE;
	}
	else
	{
		m_vpRefEdge.push_back( pcRefNode );
		return TRUE;
	}
	return FALSE;
}

/********************************************************************
	@brief    	FindRefDsEdge
	@param  	CDsPortNode::FindRefDsEdge
	@return    	std::list<CDsPortNode*>::iterator
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/02/29     1.0		  sernger			create
*********************************************************************/
std::list<CDsPortNode*>::iterator CDsPortNode::FindRefDsEdge( CDsPortNode* pcRefNode )
{
	std::list<CDsPortNode*>::iterator itIterator;
	if ( !m_vpRefEdge.empty() )
	{
		for ( itIterator = m_vpRefEdge.begin(); itIterator != m_vpRefEdge.end(); itIterator++ )
		{
			if ( pcRefNode->GetAddr() == (*itIterator)->GetAddr() )
			{
				return itIterator;
			}
		}
	}	
	return m_vpRefEdge.end(); 
}


BOOL CDsPortNode::IsRcving()
{
	std::list<CDsPortNode*>::iterator itIterator;
	if ( !m_vpRefEdge.empty() )
	{
		for ( itIterator = m_vpRefEdge.begin(); itIterator != m_vpRefEdge.end(); itIterator++ )
		{
			std::list<CDsEdge>::iterator itEdge;

			for ( itEdge = (*itIterator)->m_vtEdge.begin(); itEdge != (*itIterator)->m_vtEdge.end(); itEdge++ )
			{
				if ( itEdge->IsAcitve() && GetAddr() == itEdge->m_pcRemoteNode->GetAddr() ) 
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
/********************************************************************
	@brief    	RemoveRefDsEdge
	@param  	CDsPortNode::RemoveRefDsEdge
	@return    	void
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/02/29     1.0		  sernger			create
*********************************************************************/
void CDsPortNode::RemoveRefDsEdge( CDsPortNode* pcRefNode )
{
	std::list<CDsPortNode*>::iterator itIterator;
	if ( !m_vpRefEdge.empty() )
	{
		for ( itIterator = m_vpRefEdge.begin(); itIterator != m_vpRefEdge.end();  )
		{
			if ( pcRefNode->GetAddr() == (*itIterator)->GetAddr() )
			{
				itIterator = m_vpRefEdge.erase( itIterator );
			}
			else
			{
				itIterator++;
			}
		}
	}
}


void CDsPortNode::RemoveDsEdge( CDsPortNode* pcNode )
{
	std::list<CDsEdge>::iterator itIterator;
	if ( !m_vtEdge.empty() )
	{
		for ( itIterator = m_vtEdge.begin(); itIterator != m_vtEdge.end();  )
		{
			if ( pcNode->GetAddr() == itIterator->m_pcRemoteNode->GetAddr() )
			{
				itIterator = m_vtEdge.erase( itIterator );
			}
			else
			{
				itIterator++;
			}
		}
	}
}



/********************************************************************
	@brief    	IsExistHandleInRef
	@param  	CDsPortNode::IsExistHandleInRef
	@return    	BOOL
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/03/14     1.0		  sernger			create
*********************************************************************/
BOOL CDsPortNode::IsExistHandleInRef( u32 hHandle )
{
	std::list<CDsPortNode*>::iterator itIterator;
	if ( !m_vpRefEdge.empty() )
	{
		for ( itIterator = m_vpRefEdge.begin(); itIterator != m_vpRefEdge.end(); itIterator++ )
		{
			if ( (*itIterator)->IsExistHandle( hHandle ) )
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

/********************************************************************
	函 数 名:    Show
	全    名:  	 CDsPortNode::Show
	访问权限:    public 
	返 回 值:    void
	作    者： 	 范军爽
	版    本： 	  1.0
-------------------------------------------------------------------
   修改记录
=========日期========版本==========修改人==========修改内容=======
   2012/02/03     1.0		  范军爽			创建
*********************************************************************/
static s8 g_schSpace[256] = {0};
void CDsPortNode::ShowNode( u8 byOffset )
{
	if ( byOffset > 255 )
	{
		msgprint("[CDsPortNode::Show]byOffset:%d too large\n", byOffset );
		return;
	}

	u16 wLoop =0;
	for ( wLoop = 0; wLoop < byOffset; wLoop++ )
	{
		g_schSpace[wLoop] = ' ';
	}
	g_schSpace[byOffset] = 0; 

	OspPrintf( 1, 0, "\n" );
	OspPrintf( 1, 0, "%s|->"TPIPFORMAT":%d ", 
		g_schSpace,
		Tpu32ToIP( m_tAddr.GetIP() ),
					m_tAddr.GetPort() );

	std::list<TDsType>::iterator itPortType;
	for ( itPortType = m_vtPortType.begin(); itPortType != m_vtPortType.end(); itPortType++ )
	{
		
		OspPrintf( 1, 0, " (%d:%d:%d:%s)",itPortType->dwHandle,itPortType->dwDsType,
								itPortType->wSubDsType,itPortType->achAlias );	
	}
	
	OspPrintf( 1, 0, "\n" );


	


}



void CDsPortNode::SetPortType( const TDsType& tPortType )
{
 	std::list<TDsType>::iterator itIterator;
 	if ( !m_vtPortType.empty() )
 	{
 		for ( itIterator = m_vtPortType.begin(); itIterator != m_vtPortType.end(); itIterator++ )
 		{
 			if ( tPortType.dwHandle == itIterator->dwHandle 
 				&& tPortType.dwDsType == itIterator->dwDsType 
 				&& emDS_SubType_Unknow != tPortType.wSubDsType )
 			{
 				itIterator->wSubDsType = tPortType.wSubDsType;
 				return;
 			}
 		}
 	}
 	m_vtPortType.push_back( tPortType );

}

void CDsPortNode::RemovePortType( u32 dwHandle, u32 dwType )
{
 	std::list<TDsType>::iterator itIterator;
 	
 	if ( !m_vtPortType.empty() )
 	{
 		for ( itIterator = m_vtPortType.begin(); itIterator != m_vtPortType.end(); )
 		{
 			if ( dwHandle == itIterator->dwHandle && dwType == itIterator->dwDsType )
 			{
 				itIterator = m_vtPortType.erase( itIterator );
 			}
 			else
 			{
 				itIterator++;
 			}
 		}
 	}
}

BOOL CDsPortNode::IsExistHandle( u32 dwHandle )
{
	std::list<TDsType>::iterator itIterator;
	if ( !m_vtPortType.empty() )
	{
		for ( itIterator = m_vtPortType.begin(); itIterator != m_vtPortType.end(); itIterator++ )
		{
			if ( dwHandle == itIterator->dwHandle )
			{
				return TRUE;
			}
		}
	}
	
	return FALSE; 
}

BOOL CDsPortNode::IsExistPortType( const TDsType& tDsType )
{
	std::list<TDsType>::iterator itIterator;
	if ( !m_vtPortType.empty() )
	{
		for ( itIterator = m_vtPortType.begin(); itIterator != m_vtPortType.end(); itIterator++ )
		{
			if ( tDsType.dwHandle == itIterator->dwHandle 
				&& tDsType.dwDsType == itIterator->dwDsType 
				&& tDsType.wSubDsType == itIterator->wSubDsType )
			{
				return TRUE;
			}
		}
	}
	
	return FALSE; 
}


BOOL CDsPortNode::IsExistPortType( u32 dwHandle, u32 dwType )
{
	std::list<TDsType>::iterator itIterator;
	if ( !m_vtPortType.empty() )
	{
		for ( itIterator = m_vtPortType.begin(); itIterator != m_vtPortType.end(); itIterator++ )
		{
			if ( dwHandle == itIterator->dwHandle && dwType == itIterator->dwDsType )
			{
				return TRUE;
			}
		}
	}
	
	return FALSE; 
}

BOOL CDsPortNode::IsTypeEmpty( )
{
	return m_vtPortType.empty();
}

/********************************************************************
	@brief    	ShowEdge
	@param  	CDsPortNode::ShowEdge
	@return    	void
	author	 	sernger
	version 	1.0
-------------------------------------------------------------------
   Modify Record
=====data========version==========person==========modify content======
   2012/02/29     1.0		  sernger			create
*********************************************************************/
void CDsPortNode::ShowEdge( u8 byOffset, std::list<CDsEdge>::iterator itIterator )
{
	if ( byOffset > 255 )
	{
		msgprint("[CDsPortNode::ShowEdge]byOffset:%d too large\n", byOffset );
		return;
	}

	u16 wLoop =0;
	for ( wLoop = 0; wLoop < byOffset; wLoop++ )
	{
		g_schSpace[wLoop] = ' ';
	}
	g_schSpace[byOffset] = 0; 

	OspPrintf( 1, 0, "%s|", g_schSpace );
	std::list<TDsType>::iterator itCnDsType;
	for ( itCnDsType = itIterator->m_vtDsType.begin(); itCnDsType != itIterator->m_vtDsType.end(); itCnDsType++ )
	{
		
		OspPrintf( 1, 0, " (%d:%d:%d:%s)",itCnDsType->dwHandle,itCnDsType->dwDsType,
								itCnDsType->wSubDsType,itCnDsType->achAlias );	
	}
}
//////////////



void CDsEdge::AddDsType( const TDsType& tDsType )
{

	std::list<TDsType>::iterator itIterator;
	if ( !m_vtDsType.empty() )
	{
		for ( itIterator = m_vtDsType.begin(); itIterator != m_vtDsType.end(); itIterator++ )
		{
			if ( tDsType.dwDsType == itIterator->dwDsType && tDsType.dwHandle == itIterator->dwHandle )
			{
				itIterator->wSubDsType = tDsType.wSubDsType;
				return;
			}
		}
	}

	m_vtDsType.push_back( tDsType );
}

BOOL CDsEdge::IsExistDsType(  u32 dwHandle, u32 dwType )
{
	std::list<TDsType>::iterator itIterator;
	if ( !m_vtDsType.empty() )
	{
		for ( itIterator = m_vtDsType.begin(); itIterator != m_vtDsType.end(); itIterator++ )
		{
			if ( dwType == itIterator->dwDsType && dwHandle == itIterator->dwHandle )
			{
				return TRUE;
			}
		}
	}

	return FALSE; 
}



BOOL CDsEdge::IsAcitve( )
{
	return m_bIsActive;
}


BOOL CDsEdge::IsEmpty( )
{
	return m_vtDsType.empty();
}


void CDsEdge::RemoveDsType( u32 dwHandle, u32 dwType )
{
	std::list<TDsType>::iterator itIterator;
	
	if ( !m_vtDsType.empty() )
	{
		for ( itIterator = m_vtDsType.begin(); itIterator != m_vtDsType.end(); )
		{
		    if ( dwType == itIterator->dwDsType && dwHandle == itIterator->dwHandle )
			{
				itIterator = m_vtDsType.erase( itIterator );
			}
			else
			{
				itIterator++;
			}
		}
	}
}

BOOL CDsEdge::IsExistDsHandle( u32 dwHandle )
{
	std::list<TDsType>::iterator itIterator;
	if ( !m_vtDsType.empty() )
	{
		for ( itIterator = m_vtDsType.begin(); itIterator != m_vtDsType.end(); itIterator++ )
		{
			if ( dwHandle == itIterator->dwHandle )
			{
				return TRUE;
			}
		}
	}
	
	return FALSE; 
}

void CDsEdge::RemoveDsHandle( u32 dwHandle )
{
	std::list<TDsType>::iterator itIterator;
	
	if ( !m_vtDsType.empty() )
	{
		for ( itIterator = m_vtDsType.begin(); itIterator != m_vtDsType.end(); )
		{
			if ( dwHandle == itIterator->dwHandle )
			{
				itIterator = m_vtDsType.erase( itIterator );
			}
			else
			{
				itIterator++;
			}
		}
	}
}


