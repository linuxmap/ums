#ifndef _h_mpstruct_h__
#define _h_mpstruct_h__

#include "umscommonstruct.h"
#include "tplistbuf.h"
#include "tpsys.h"


typedef struct tagTUnitData
{
	EmTpIFrameCheckType m_emType;	//操作类型
	BOOL32	m_bIFrameCheck;			//该是否启用关键帧检测
	union
	{
		TIFrameBySrc		m_tBySrc;
		TIFrameTwoRcvPort	m_tTwoRcv;
		TIFrameSndBySrc		m_tSndBySrc;
		TIFrameSndDis		m_tSndDis;
	};
	
	tagTUnitData()
	{
		memset(this, 0, sizeof(tagTUnitData));
	}
	void Clear() {	memset(this, 0, sizeof(tagTUnitData));	}
}TUnitData;


#define CUnitList CTpListBuff<TUnitData>
#define CUnitListPtr CTpListBuff<TUnitData>::VectorDataPtr


class CUnitPer
{
public:
    CUnitPer()	:m_pHead(NULL),m_dwListNum(0) { }
    ~CUnitPer()	{ }
	CUnitPer& operator = (const CUnitPer& tRsData)
	{
		m_pHead = tRsData.m_pHead;
		m_dwListNum = tRsData.m_dwListNum;
		return *this;
	}
	
	void Insert(CUnitListPtr ptInsertNode)
	{
		ptInsertNode->m_ptNext = m_pHead;
		m_pHead = ptInsertNode;
		m_dwListNum++;
	}
	u32	GetElementNum()			{ return m_dwListNum; }
	CUnitListPtr GetHead()		{ return m_pHead; }
	
	void Clear()
	{
		m_pHead = NULL;
		m_dwListNum = 0;
	}
private:    
    CUnitListPtr	m_pHead;
	u32				m_dwListNum;
};


typedef struct tagTCheckIFrame
{	
	u32		m_dwTimerID;
	
	u16 m_wConfID;
	u16 m_wExpires;					//超时时间
	u32_ip m_dwIP;				//监听IP
	u16 m_wPort;				//监听端口

	BOOL32	m_bCheck;

	CUnitPer m_tUnit;

 	BOOL32 operator == (const tagTCheckIFrame& tRhs)	{	return m_wPort == tRhs.m_wPort;	}
	
	tagTCheckIFrame()
	{
		Clear();
	}
	tagTCheckIFrame& operator = (const tagTCheckIFrame& tRhs)	
	{	
		if (this == &tRhs)
		{
			return *this;
		}
		m_dwTimerID = tRhs.m_dwTimerID;	

		m_wConfID	= tRhs.m_wConfID;
		m_wExpires	= tRhs.m_wExpires;
		m_dwIP		= tRhs.m_dwIP;
		m_wPort		= tRhs.m_wPort;

		m_tUnit = tRhs.m_tUnit;
		
		return *this;
	}
	
	void Clear()
	{	
		m_dwTimerID = 0;
		m_tUnit.Clear();
		m_bCheck = TRUE;
	}

	void AddUnit(const TCheckIFrameBase& tBase, CUnitListPtr Itor)
	{
		m_wConfID	= tBase.m_wConfID;
		m_wExpires	= tBase.m_wExpires;
		m_dwIP		= tBase.m_dwIP;
		m_wPort		= tBase.m_wPort;
		
		m_tUnit.Insert(Itor);
	}
}TCheckIFrame;


const u16 MAX_IFRAME_PORT = 65535-20000;
#define VALID_PORT_INDEX(port)	(((port)>=20000) && ((port)<=65535))
#define GET_PORT_INDEX(port)	((port) - 20000)


class CPortVector 
{ 
public:

public: 
	CPortVector() 
	{ 
		m_pBuf = NULL; 
		m_dwUnitSize = 0; 
		m_dwFreeElement = 0; 
		m_dwTotalElement = 0; 
	} 
	~CPortVector() 
	{ 
		Destroy(); 
	} 
	BOOL32 Create(u32 dwElementNum) 
	{ 
		if (dwElementNum < 1) 
		{ 
			return FALSE; 
		} 
		m_dwUnitSize = sizeof(TCheckIFrame); 
		m_pBuf = new u8[m_dwUnitSize*dwElementNum]; 
		if (NULL == m_pBuf) 
		{ 
			m_dwUnitSize = 0; 
			return FALSE; 
		} 
		memset(m_pBuf, 0, m_dwUnitSize*dwElementNum);

		m_dwTotalElement = dwElementNum; 
		m_dwFreeElement = dwElementNum; 

		return TRUE; 
	} 
	void Destroy() 
	{ 
		if (NULL != m_pBuf) 
		{ 
			delete[] m_pBuf; 
			m_pBuf = NULL; 
		} 
		m_pBuf = NULL; 
		m_dwUnitSize = 0; 
		m_dwFreeElement = 0; 
		m_dwTotalElement = 0; 
	} 
	//增加一个元素 
	TCheckIFrame* Add(u16 wRcvPort) 
	{ 
		TCheckIFrame* pAddNode = FindByPort(wRcvPort);
		if (NULL == pAddNode)
		{
			return NULL;
		}
		return pAddNode; 
	} 

	//删除一个元素, 并返回改元素的内容
	void Del(u16 wPort) 
	{ 
		TCheckIFrame* ptIframe = FindByPort(wPort);
		if (NULL != ptIframe)
		{
			ptIframe->Clear();
		}
	} 
	
	TCheckIFrame* FindByPort(u16 wRcvPort)
	{
		if (!VALID_PORT_INDEX(wRcvPort))
		{			
			return NULL;
		}
		
		u16 wPortIndex = GET_PORT_INDEX(wRcvPort);
		return (TCheckIFrame*)(m_pBuf + m_dwUnitSize*wPortIndex);
	}

	TCheckIFrame* FindByIndex(u16 wIndex)
	{
		return (TCheckIFrame*)(m_pBuf + m_dwUnitSize*wIndex);
	}


	u32 MaxSize()        {        return m_dwTotalElement; } 

private: 
	 CPortVector& operator = (const CPortVector&); 
	 CPortVector(const CPortVector&); 
private: 
	 u8* m_pBuf; 
	 u32 m_dwUnitSize; 
	 u32 m_dwFreeElement; 
	 u32 m_dwTotalElement; 
}; 

#endif // _h_mpstruct_h__

