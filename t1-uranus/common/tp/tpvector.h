#ifndef _h_tpvector_h__
#define _h_tpvector_h__



#include "osp.h"


template<class Type>
class CTpVectorData
{ 
public: 	
	CTpVectorData<Type>*	m_pcNext; 
	Type					m_tData;
	CTpVectorData<Type>() 
		:m_pcNext(NULL) 
	{ 
	} 
	Type& data ()
	{
		return m_tData;
	}
}; 
template<class Type>
class CTpVectorItor
{
typedef CTpVectorItor<Type>  iterator;
public:
	CTpVectorData<Type>* m_pcCurrent;
public:
	CTpVectorItor()
		:m_pcCurrent(NULL)
	{}
	CTpVectorItor(CTpVectorData<Type>* pcData)
		:m_pcCurrent(pcData)
	{}
	iterator& operator ++ () 
	{ //前置
		m_pcCurrent = m_pcCurrent->m_pcNext;
		return *this; 
	} 
	
	iterator operator ++ (int) 
	{ //后置
		iterator tmp = *this;
		m_pcCurrent = m_pcCurrent->m_pcNext;
		return tmp; 
	} 
	
	BOOL32 operator == (const iterator& tRhs)
	{
		return m_pcCurrent == tRhs.m_pcCurrent;
	}
	BOOL32 operator != (const iterator& tRhs)
	{
		return !(*this == tRhs);
	}
	Type& operator*()
	{
		return m_pcCurrent->m_tData;
	}
	
	Type* operator->()
	{
		return &m_pcCurrent->m_tData;
	}

};


//固定大小的数组 
//Type 必须具有operator=和operator==操作 
template<class Type> 
class CTpVector 
{ 
#define vector_invalid_index -1
public:
	typedef CTpVectorItor<Type>	iterator;
	typedef CTpVectorData<Type>	VectorDataType;
	typedef CTpVectorData<Type>*	VectorDataTypePtr;
public: 
	CTpVector() 
	{ 
		m_pcUsedListFirst = NULL; 
		m_pcUsedListLast = NULL; 
		m_ptFreeList = NULL; 
		m_pBuf = NULL; 
		m_dwUnitSize = 0; 
		m_dwFreeElement = 0; 
		m_dwUsedElement = 0; 
		m_dwTotalElement = 0; 
	} 
	~CTpVector() 
	{ 
		Destroy(); 
	} 
	BOOL32 Create(u32 dwElementNum) 
	{ 
		if (dwElementNum < 1) 
		{ 
			return FALSE; 
		} 
		m_dwUnitSize = sizeof(VectorDataType); 
		m_pBuf = new u8[m_dwUnitSize*dwElementNum]; 
		if (NULL == m_pBuf) 
		{ 
			m_dwUnitSize = 0; 
			return FALSE; 
		} 
		m_dwTotalElement = dwElementNum; 
		m_dwFreeElement = dwElementNum; 
		m_dwUsedElement = 0; 
		m_pcUsedListFirst = NULL; 
		m_pcUsedListLast = NULL; 
		m_ptFreeList = (VectorDataTypePtr)m_pBuf; 
		if ( dwElementNum == 1) 
		{ 
			m_ptFreeList->m_pcNext = NULL; 
		} 
		else 
		{ 
			VectorDataTypePtr ptItor = m_ptFreeList; 
			for (u32 wIndex = 1; wIndex < m_dwTotalElement; wIndex++) 
			{ 
				ptItor->m_pcNext = (VectorDataTypePtr)(m_pBuf + m_dwUnitSize*wIndex); 
				ptItor = ptItor->m_pcNext; 
			}                 
			ptItor->m_pcNext = NULL; 
		}          
		return TRUE; 
	} 
	void Destroy() 
	{ 
		if (m_pBuf) 
		{ 
			delete[] m_pBuf; 
			m_pBuf = 0; 
		} 
		m_pcUsedListFirst = NULL; 
		m_pcUsedListLast = NULL; 
		m_ptFreeList = NULL; 
		m_pBuf = NULL; 
		m_dwUnitSize = 0; 
		m_dwFreeElement = 0; 
		m_dwUsedElement = 0; 
		m_dwTotalElement = 0; 
	} 
	BOOL32 IsFull()        {        return m_ptFreeList == NULL; } 
	//增加一个元素 
	iterator Add(const Type& tData) 
	{ 
		if (NULL == m_ptFreeList) 
		{ 
			return NULL; 
		} 
		VectorDataTypePtr pAddNode = m_ptFreeList; 
		m_ptFreeList = m_ptFreeList->m_pcNext; 
		if (m_pcUsedListFirst == NULL) 
		{ 
			m_pcUsedListFirst = pAddNode; 
			m_pcUsedListLast = pAddNode; 
		} 
		else 
		{ 
			m_pcUsedListLast->m_pcNext = pAddNode; 
			m_pcUsedListLast = pAddNode; 
		} 
		pAddNode->m_pcNext = NULL; 
		pAddNode->m_tData = tData; 
		m_dwUsedElement++; 
		m_dwFreeElement--; 
		return iterator(pAddNode); 
	} 
	//删除第一个元素 
	iterator Del(Type& tData) 
	{ 
		VectorDataTypePtr ptPre; 
		VectorDataTypePtr ptDelNode; 
		ptPre = NULL; 
		ptDelNode = m_pcUsedListFirst; 
		while (NULL != ptDelNode) 
		{ 
			if (ptDelNode->m_tData == tData) 
			{ 
				break; 
			} 
			ptPre = ptDelNode; 
			ptDelNode = ptDelNode->m_pcNext; 
		} 
		if (NULL == ptDelNode) 
		{ 
			return NULL; 
		} 
		if (NULL == ptPre) 
		{ 
			m_pcUsedListFirst = ptDelNode->m_pcNext; 
			if (NULL == m_pcUsedListFirst) 
			{ 
				m_pcUsedListLast = NULL; 
			} 
		} 
		else 
		{ 
			ptPre->m_pcNext = ptDelNode->m_pcNext; 
			if (ptDelNode == m_pcUsedListLast) 
			{ 
				m_pcUsedListLast = ptPre; 
			} 
		} 
		//加入空闲列表 
		ptDelNode->m_pcNext = m_ptFreeList; 
		m_ptFreeList = ptDelNode; 
		m_dwUsedElement--; 
		m_dwFreeElement++; 
		return iterator(ptDelNode); 
	} 

	iterator Find(Type& tData) 
	{ 
		VectorDataTypePtr ptFindNode = m_pcUsedListFirst; 
		while (NULL != ptFindNode) 
		{ 
			if (ptFindNode->m_tData == tData) 
			{ 
				return iterator(ptFindNode); 
			} 
			ptFindNode = ptFindNode->m_pcNext; 
		} 
		return iterator(NULL); 
	} 
	u32 size()        {        return m_dwUsedElement; } 
	u32 GetFreeSize()			{ return m_dwFreeElement; } 
	iterator begin()			{ return iterator(m_pcUsedListFirst); } 
	iterator end()				{ return iterator(NULL); }

	//以下为对数组的物理索引的操作 

	
	u32 MaxSize()        {        return m_dwTotalElement; } 
	Type& operator [] ( u32 dwIndex) 
	{ 
		VectorDataTypePtr ptr = (VectorDataTypePtr)(m_pBuf + m_dwUnitSize*dwIndex);
		return ptr->m_tData;
	} 

	u16 GetItorIndex(iterator itor)
	{
		if (m_dwUnitSize == 0)
		{
			return vector_invalid_index;
		}
		return (itor.m_pcCurrent - m_pBuf) / m_dwUnitSize;
	}
	
	void clear()
	{
		m_dwFreeElement = m_dwTotalElement;
		m_dwUsedElement = 0;

		if (NULL == m_pcUsedListFirst)
		{
			return;
		}

		VectorDataTypePtr pItor = m_pcUsedListFirst;
		VectorDataTypePtr pNext;

		while(NULL != pItor)
		{
			pNext = pItor->m_pcNext;

			pItor->m_pcNext = m_ptFreeList; 
			m_ptFreeList = pItor; 

			pItor = pNext;
		}
	}
private: 
	 CTpVector& operator = (const CTpVector&); 
	 CTpVector(const CTpVector&); 
private: 
	 VectorDataTypePtr m_pcUsedListFirst;        //使用列表 
	 VectorDataTypePtr m_pcUsedListLast;        //使用列表 
	 VectorDataTypePtr m_ptFreeList;        //空闲头列表 
	 u8* m_pBuf; 
	 u32 m_dwUnitSize; 
	 u32 m_dwFreeElement; 
	 u32 m_dwUsedElement; 
	 u32 m_dwTotalElement; 
}; 

#endif // _h_tpvector_h__
