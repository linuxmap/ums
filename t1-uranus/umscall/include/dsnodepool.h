/********************************************************************
	created:	2012/02/20
	created:	20:2:2012   15:02
	filename: 	Professional_VOB\50-mars\common\tp\cndsnodepool.h
	file path:	Professional_VOB\50-mars\common\tp
	file base:	cndsnodepool
	file ext:	h
	author:		fanjunshuang
	
	purpose:	manage ds in adjacency list
*********************************************************************/
#ifndef _h_DSNODEPOOL_h__
#define _h_DSNODEPOOL_h__
#ifdef WIN32
#pragma warning(disable : 4786) 
#endif
#include <list>
#include <map>
#include "umscommonstruct.h"
#include "callinnerstruct.h"
#include "osp.h"

//ds  struct and constant 
#define TP_DS_MAX_NAME_LEN 32
class CDsPortNode;
class CDsEdge;

enum EMDS_SUBTYPE
{
	emDS_SubType_Unknow = 0,
	emDS_SubType_RTP = 1,
	emDS_SubType_RTCP   
};
typedef struct tagTDsType
{
	u32  dwHandle;
	u32  dwDsType;
	u16  wSubDsType;
	u8   achAlias[TP_DS_MAX_NAME_LEN+1];

	void clear()
	{
		memset(this, 0, sizeof(tagTDsType));
	}
	tagTDsType()
	{
		clear();
	}

	tagTDsType& operator = (const tagTDsType& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->dwHandle = tRhs.dwHandle;
		this->dwDsType = tRhs.dwDsType;
		this->wSubDsType = tRhs.wSubDsType;
		memcpy( this->achAlias, tRhs.achAlias,sizeof(achAlias) ) ;
		return *this;
	}
	BOOL operator == (const tagTDsType& tRhs)
	{
		if ( this->dwHandle == tRhs.dwHandle
			&&this->dwDsType == tRhs.dwDsType
			&&this->wSubDsType == tRhs.wSubDsType )
		{
			return TRUE;
		}
		return FALSE;
	}
}TDsType;


typedef struct tagTTPDsData
{
	TTPTransAddr m_tRcvFromAddr;
	TTPTransAddr m_tSndToAddr;
	TTPTransAddr m_tMapedAddr;
	
	void clear()
	{
		memset(this, 0, sizeof(tagTTPDsData));
	}
	tagTTPDsData()
	{
		clear();
	}
	tagTTPDsData& operator = (const tagTTPDsData& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_tRcvFromAddr = tRhs.m_tRcvFromAddr;
		this->m_tSndToAddr = tRhs.m_tSndToAddr;
		this->m_tMapedAddr = tRhs.m_tMapedAddr;
		return *this;
	}
	BOOL operator == (const tagTTPDsData& tRhs)
	{
		if ( this->m_tSndToAddr.m_dwIP == tRhs.m_tSndToAddr.m_dwIP
			&&this->m_tRcvFromAddr.m_dwIP == tRhs.m_tRcvFromAddr.m_dwIP
			&&this->m_tSndToAddr.m_wPort == tRhs.m_tSndToAddr.m_wPort
			&&this->m_tRcvFromAddr.m_wPort == tRhs.m_tRcvFromAddr.m_wPort)
		{
			return TRUE;
		}
		return FALSE;
	}
}TTPDsData;

typedef void (*TFDsPoolCB)( const TTPDsData& tCnDsData );
// end struct and constant


class CDsEdge
{
public:
	CDsEdge(){ clear(); };
	~CDsEdge(){};
	void clear()
	{
		
		m_vtDsType.clear();
		m_pcRemoteNode = 0;
		m_bIsActive = FALSE;
	};
	
	BOOL IsEmpty( );
	BOOL IsAcitve( );
	void SetAcitve( BOOL bActive ){ m_bIsActive = bActive; } ;
	
	BOOL IsExistDsType( u32 dwHandle, u32 dwType );
	void AddDsType( const TDsType& tDsType );
	
	void RemoveDsType( u32 dwHandle, u32 dwType );
	
	BOOL IsExistDsHandle( u32 dwHandle );
	void RemoveDsHandle( u32 dwHandle );
	
public:
	std::list<TDsType>	m_vtDsType;
	BOOL					m_bIsActive;
	CDsPortNode*			m_pcRemoteNode;
};


class CDsPortNode
{
public:
	enum EmPortColour
	{
		EmColour_White = 1,
			EmColour_Gray,
			EmColour_Black
	};
public:
	CDsPortNode( const TTPTransAddr &tAddr );
	~CDsPortNode();
	
	void Init( const TTPTransAddr &tAddr );
	void Destroy( );
	
	BOOL operator < ( const CDsPortNode &tRhs )
	{
		return this->m_tAddr < tRhs.m_tAddr;
	};
	
	BOOL operator == ( const CDsPortNode &tRhs )
	{
		return this->m_tAddr == tRhs.m_tAddr;
	};
	
	BOOL AddDsEdge( const TDsType& tDsType, CDsPortNode* pcRemoteNode );
	std::list<CDsEdge>::iterator FindDsEdge( CDsPortNode* pcRemoteNode );
	
	BOOL AddRefDsEdge( CDsPortNode*	pcRefNode );
	std::list<CDsPortNode*>::iterator FindRefDsEdge( CDsPortNode* pcRefNode );
	void RemoveRefDsEdge( CDsPortNode* pcRefNode );
	
	void RemoveDsEdge( CDsPortNode* pcNode );
	
	TTPTransAddr GetAddr(){ return m_tAddr; };
	
	BOOL IsExistHandleInRef( u32 hHandle );
	void ShowNode( u8 byOffset );
	void ShowEdge( u8 byOffset, std::list<CDsEdge>::iterator itIterator );
	
	//add 
	BOOL IsExistHandle( u32 dwHandle );
	BOOL IsTypeEmpty( );
	BOOL IsExistPortType( const TDsType& tDsType );
	BOOL IsExistPortType( u32 dwHandle, u32 dwType );
	
	void SetPortType( const TDsType& tPortType );
	void RemovePortType( u32 dwHandle, u32 dwType );
	
	
	void SetAddr( const TTPTransAddr &tAddr ){ m_tAddr = tAddr; };
	
	BOOL IsRcving();//rtcp can rcv many data，rcp can't
private:
	
	
public:
	std::list<CDsEdge>		m_vtEdge;
	std::list<CDsPortNode*>	m_vpRefEdge;
	std::list<TDsType>		m_vtPortType;
	EmPortColour			m_emPortColour;
	TTPTransAddr			m_tAddr;
protected:
private:
	
	TTPCnNetBufPara			m_tCnNetBufPara;	
};


class CDsPortPool
{
public:
	static CDsPortPool* GetInstance()
	{
		static CDsPortPool scDsPool;
		return &scDsPool;
	};
	CDsPortPool();
	virtual ~CDsPortPool();
	

//for ums	
public:
	void AddDs(  u32 Handle, TUmsDsData* const aNewDsData, u16 wDsNumm );
	void DelDs(  u32 Handle, CDsListPtr pcDelList );
private:
	//添加新地址节点，如果存在则返回对应指针
	CDsPortNode* AddPort(  u32 Handle ,const TTPTransAddr& tAddr );
	BOOL DestroyDs(  CDsPortNode* pRcvFrom,  CDsPortNode* pSndTo );
// end for ums

public:
	u32 GetDSHandle();
	
	CDsPortNode * AddPort(  const TTPTransAddr& tAddr, const TDsType& tPortType );
	
	BOOL AddDs( const TDsType &tEdge, 
		 CDsPortNode* pcPortRcvFrom ,
		 CDsPortNode* pcPortSndTo,
				TTPDsData& tDsData);

	void Show(  u32 Handle, EmTPDsNode emDsNode );
	void Dfs_Init( u32 Handle, EmTPDsNode emDsNode );
	void Dfs( CDsPortNode* pcNode, u8 byDepth );
protected:
	
	void Destroy();
private:
	std::map<TTPTransAddr,CDsPortNode>    m_mapPort;
	u32									  m_dwDsNum;
	u32								      m_hLastHandle;
};


//







#endif // _h_mediatransinit_h__
