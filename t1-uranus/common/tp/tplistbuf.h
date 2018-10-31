#ifndef _h_tplistbuf_h__
#define _h_tplistbuf_h__
#include "osp.h"
#include <new>

template<class Type>
class CTpListBufData
{
public:
	CTpListBufData*	m_ptNext;    //指向下一个Block
	Type			m_tData;

	static u32		m_dwDataOffset;
public:
	CTpListBufData():m_ptNext(NULL)	{}
	CTpListBufData* Next()	{ return m_ptNext; }

};

template<class Type>
u32 CTpListBufData<Type>::m_dwDataOffset = (size_t)&(((CTpListBufData *)0)->m_tData);

template<class Type>
class CTpListBuff
{
public:
	typedef CTpListBufData<Type>	VectorData;
	typedef CTpListBufData<Type>*	VectorDataPtr;

public:
    CTpListBuff()
		:m_dwFreeBlockNum(0)
		,m_pBuff(NULL)
		,m_ptFreeBuffList(NULL)
		,m_dwBuffSize(0)
		,m_dwTotalNum(0)
	{
	}
    ~CTpListBuff()	{ Destroy(); }
	
    BOOL32 Create(u32 dwDataNum);
    void Destroy();
    
    //分配并拷贝数据
    Type*   WriteBuff(const Type& tData);
	VectorDataPtr WriteBuffItor(const Type& tData);

	Type*	AllocNode();
	Type*	GetDataByIndex(u32 wIndex);		//根据物理索引获取

	//释放数据块链
    u32 FreeBuff(Type* itor);
	u32 FreeBuff(VectorDataPtr itor);
	
    //得到总的分配的数据大小
    u32 GetAllocSize() { return m_dwBuffSize; }
	
    u32 GetFreeBlocks()		{ return m_dwFreeBlockNum; }
    u32 GetMinFreeBlocks()	{ return m_dwMinFreeBlocks; }
	u32 GetTotalNum()		{ return m_dwTotalNum; }
	void Show()	{OspPrintf(TRUE, FALSE, "\n  CTpListBuff::m_dwTotalNum:%d, m_dwFreeBlockNum:%d\n", m_dwTotalNum, m_dwFreeBlockNum);}
	
private:    
    void*   m_pBuff;                    //整个Buff的指针
	
    u32     m_dwFreeBlockNum;           //空闲块的数目
    VectorDataPtr m_ptFreeBuffList;		//空闲块链表    

    u32     m_dwBuffSize;               //实际分配缓冲大小
    u32     m_dwTotalNum;               //实际使用总块数
	u32     m_dwMinFreeBlocks;          //最小空闲数
    
};


template<class Type>
BOOL32 CTpListBuff<Type>::Create(u32 dwDataNum)
{
    if (0 == dwDataNum)
    {
        return FALSE;
    }

    //判断是否需要重新分配
    if (dwDataNum > m_dwTotalNum) 
    {
        if (NULL != m_pBuff)
        {
            free(m_pBuff);
            m_pBuff = NULL;
        }
		
		u16 wPerSize = sizeof(VectorData);
        m_pBuff = malloc(dwDataNum*wPerSize);
        if (m_pBuff == NULL)
        {
            OspPrintf(TRUE, FALSE, "CKdvListBuff Malloc Buff failed, size=%d\n", dwDataNum);
            return FALSE;
        }
    }
    
    //建立空链表
    VectorDataPtr ptTmp = (VectorDataPtr)m_pBuff;
    m_ptFreeBuffList = ptTmp;
	new (&m_ptFreeBuffList->m_tData) Type;
	
    for(u32 dwIndex = 1;  dwIndex < dwDataNum; dwIndex++)
    {
        ptTmp->m_ptNext = (VectorDataPtr)((u8*)ptTmp + sizeof(VectorData));
		new (&ptTmp->m_ptNext->m_tData) Type;
        ptTmp = ptTmp->m_ptNext;
    }
    ptTmp->m_ptNext = NULL;
	
    m_dwTotalNum      = dwDataNum;
    m_dwFreeBlockNum  = dwDataNum;
    m_dwMinFreeBlocks = dwDataNum;
	
    return TRUE;
}

template<class Type>
void CTpListBuff<Type>::Destroy()
{
	if (m_pBuff != NULL)
	{
		free(m_pBuff);
		m_pBuff = NULL;
	}
	
	m_ptFreeBuffList    =   NULL;
	m_dwFreeBlockNum    =   0;
	m_dwBuffSize        =   0;
}

template<class Type>
Type* CTpListBuff<Type>::AllocNode()
{
    if (m_ptFreeBuffList == NULL || m_dwFreeBlockNum < 1)
    {
		OspPrintf(TRUE, FALSE, "CTpListBuff::AllocNode() failed!\n");
        return NULL;
    }
	
    VectorDataPtr ptCurBlock = m_ptFreeBuffList;
	m_ptFreeBuffList = m_ptFreeBuffList->m_ptNext;
	
	ptCurBlock->m_ptNext = NULL;
	
    m_dwFreeBlockNum -= 1;
    
    //记录最小空闲块数
    if (m_dwFreeBlockNum < m_dwMinFreeBlocks)
        m_dwMinFreeBlocks = m_dwFreeBlockNum;
	
    return &ptCurBlock->m_tData;
}


template<class Type>
Type* CTpListBuff<Type>::WriteBuff(const Type& tData)
{
	if (m_ptFreeBuffList == NULL || m_dwFreeBlockNum < 1)
	{
		return NULL;
	}
	
	VectorDataPtr ptBlock = m_ptFreeBuffList;
	
	ptBlock->m_tData = tData;	
	
	m_ptFreeBuffList = ptBlock->m_ptNext; //移动空链表指针
	ptBlock->m_ptNext = NULL;    //置链表结束标志

	m_dwFreeBlockNum -- ;
	
	//记录最小空闲块数
	if (m_dwFreeBlockNum < m_dwMinFreeBlocks)
		m_dwMinFreeBlocks = m_dwFreeBlockNum;
	
	return &ptBlock->m_tData;
}

template<class Type>
CTpListBufData<Type>* CTpListBuff<Type>::WriteBuffItor(const Type& tData)
{
	if (m_ptFreeBuffList == NULL || m_dwFreeBlockNum < 1)
	{
		return NULL;
	}
	
	VectorDataPtr ptBlock = m_ptFreeBuffList;
	
	ptBlock->m_tData = tData;	
	
	m_ptFreeBuffList = ptBlock->m_ptNext; //移动空链表指针
	ptBlock->m_ptNext = NULL;    //置链表结束标志
	
	m_dwFreeBlockNum -- ;
	
	//记录最小空闲块数
	if (m_dwFreeBlockNum < m_dwMinFreeBlocks)
		m_dwMinFreeBlocks = m_dwFreeBlockNum;
	
	return ptBlock;
}




template<class Type>
Type* CTpListBuff<Type>::GetDataByIndex(u32 wIndex)
{

	if (wIndex >= m_dwTotalNum)
	{
		return NULL;
	}
	
    VectorDataPtr ptr =  (VectorDataPtr)((u8*)m_pBuff + sizeof(VectorData) * wIndex);
	
	return &ptr->m_tData;
}

template<class Type>
u32 CTpListBuff<Type>::FreeBuff(Type* itor)
{	
    s32 nBlockNum;
    if (itor == NULL)
    {
        return 0;
    }
	VectorDataPtr Ptr = VectorDataPtr(((char*)itor) - VectorData::m_dwDataOffset);

    VectorDataPtr ptTmp = Ptr;
    nBlockNum = 1;
    while(ptTmp->m_ptNext != NULL)
    {
        nBlockNum++;
        ptTmp = ptTmp->m_ptNext;
    }
    ptTmp->m_ptNext     =   m_ptFreeBuffList;
    m_ptFreeBuffList    =   Ptr;
    m_dwFreeBlockNum    +=  nBlockNum;
	
    if (m_dwFreeBlockNum > m_dwTotalNum)
    {
        OspPrintf(TRUE, FALSE, "CKdvListBuff::FreeBuff Total Block num=%d, but Free Block num=%d\n",
			m_dwTotalNum, m_dwFreeBlockNum);
        
        m_dwFreeBlockNum = m_dwTotalNum;
    }
	
    return nBlockNum;
}

template<class Type>
u32 CTpListBuff<Type>::FreeBuff(VectorDataPtr Ptr)
{	
    s32 nBlockNum;
    if (NULL == Ptr)
    {
        return 0;
    }
	
    VectorDataPtr ptTmp = Ptr;
    nBlockNum = 1;
    while(ptTmp->m_ptNext != NULL)
    {
        nBlockNum++;
        ptTmp = ptTmp->m_ptNext;
    }
    ptTmp->m_ptNext     =   m_ptFreeBuffList;
    m_ptFreeBuffList    =   Ptr;
    m_dwFreeBlockNum    +=  nBlockNum;
	
    if (m_dwFreeBlockNum > m_dwTotalNum)
    {
        OspPrintf(TRUE, FALSE, "CKdvListBuff::FreeBuff Total Block num=%d, but Free Block num=%d\n",
			m_dwTotalNum, m_dwFreeBlockNum);
        
        m_dwFreeBlockNum = m_dwTotalNum;
    }
	
    return nBlockNum;
}

#endif // _h_tplistbuf_h__
