#ifndef _h_tplist_h__
#define _h_tplist_h__
#include "osp.h"
#include <new>

template <class Type> class CTpList;

template<class Type>
class CTpListData
{
private:
	CTpListData*	m_ptNext;    //ָ����һ��Block
	CTpListData*	m_ptPre;     //ָ��ǰһ��Block�� ��ָ�����ɾ��ʹ���б�ʱʹ��
	Type			m_tData;

	friend  class CTpList<Type>;

public:
	static u32		m_dwDataOffset;

public:
	CTpListData():m_ptNext(NULL), m_ptPre(NULL)	{}
	Type*			Data()	{ return &m_tData; }
	CTpListData*	Next()	{ return m_ptNext; }	

	
};
 

template<class Type>
u32 CTpListData<Type>::m_dwDataOffset = (size_t)&(((CTpListData *)0)->m_tData);


template<class Type>
class CTpList
{
public:
	typedef CTpListData<Type>	ListData;
	typedef CTpListData<Type>*	ListDataPtr;

public:
    CTpList()
		:m_dwFreeBlockNum(0)
		,m_pBuff(NULL)
		,m_ptFreeHead(NULL)
		,m_ptUsedHead(NULL)
		,m_dwBuffSize(0)
		,m_dwTotalNum(0)
	{
	}
    ~CTpList()	{ Destroy(); }
	
    BOOL32 Create(u32 dwDataNum);
    void Destroy();
    
	Type*	AllocNode();
	Type*	GetDataByIndex(u32 wIndex);		//��������������ȡ
	Type*	Head()	{	return m_ptUsedHead == NULL ? NULL : m_ptUsedHead->Data(); }
	Type*	Next(Type* ptData);

	//�ͷ����ݿ���
	u32 FreeBuff(Type* itor);	
	
    u32 GetFreeBlocks()		{ return m_dwFreeBlockNum; }
    u32 GetMinFreeBlocks()	{ return m_dwMinFreeBlocks; }
	u32 GetTotalNum()		{ return m_dwTotalNum; }
	void Show()	{OspPrintf(TRUE, FALSE, "\n  CTpList::m_dwTotalNum:%d, m_dwFreeBlockNum:%d\n", m_dwTotalNum, m_dwFreeBlockNum);}
	
protected:
	
private:    
    void*   m_pBuff;                //����Buff��ָ��
	
    u32     m_dwFreeBlockNum;       //���п����Ŀ
    ListDataPtr m_ptFreeHead;		//���п�����
	ListDataPtr m_ptUsedHead;		//ʹ�ÿ�����

    u32     m_dwBuffSize;           //ʵ�ʷ��仺���С
    u32     m_dwTotalNum;           //ʵ��ʹ���ܿ���
	u32     m_dwMinFreeBlocks;      //��С������
    
};


template<class Type>
BOOL32 CTpList<Type>::Create(u32 dwDataNum)
{
    if (0 == dwDataNum)
    {
        return FALSE;
    }

    //�ж��Ƿ���Ҫ���·���
    if (dwDataNum > m_dwTotalNum) 
    {
        if (NULL != m_pBuff)
        {
            free(m_pBuff);
            m_pBuff = NULL;
        }
		
		u16 wPerSize = sizeof(ListData);
        m_pBuff = malloc(dwDataNum*wPerSize);
        if (m_pBuff == NULL)
        {
            OspPrintf(TRUE, FALSE, "CKdvListBuff Malloc Buff failed, size=%d\n", dwDataNum);
            return FALSE;
        }
    }
    
	m_ptUsedHead = NULL;
    //����������
    ListDataPtr ptTmp = (ListDataPtr)m_pBuff;
    m_ptFreeHead = ptTmp;

	new (ptTmp->Data()) Type;
	
    for(u32 dwIndex = 1;  dwIndex < dwDataNum; dwIndex++)
    {
        ptTmp->m_ptNext = (ListDataPtr)((u8*)ptTmp + sizeof(ListData));
		new (ptTmp->m_ptNext->Data()) Type;
        ptTmp = ptTmp->m_ptNext;
    }
    ptTmp->m_ptNext = NULL;
	
    m_dwTotalNum      = dwDataNum;
    m_dwFreeBlockNum  = dwDataNum;
    m_dwMinFreeBlocks = dwDataNum;
	
    return TRUE;
}

template<class Type>
void CTpList<Type>::Destroy()
{
	if (m_pBuff != NULL)
	{
		free(m_pBuff);
		m_pBuff = NULL;
	}
	
	m_ptFreeHead    =   NULL;
	m_ptUsedHead    =   NULL;
	m_dwFreeBlockNum    =   0;
	m_dwBuffSize        =   0;
}

template<class Type>
Type* CTpList<Type>::Next(Type* ptData)
{
	ListDataPtr Ptr = ListDataPtr(((char*)ptData) - ListData::m_dwDataOffset);
	return Ptr->m_ptNext == NULL ? NULL : Ptr->m_ptNext->Data();
}

template<class Type>
Type* CTpList<Type>::AllocNode()
{
    if (m_ptFreeHead == NULL || m_dwFreeBlockNum < 1)
    {
		OspPrintf(TRUE, FALSE, "CTpList::AllocNode() failed!\n");
        return NULL;
    }
	
    ListDataPtr ptAllocBlock = m_ptFreeHead;
	m_ptFreeHead = m_ptFreeHead->m_ptNext;	
    m_dwFreeBlockNum -= 1;

	//��ʹ���������
	ptAllocBlock->m_ptNext = m_ptUsedHead;
	ptAllocBlock->m_ptPre = NULL;
	if (m_ptUsedHead != NULL)
	{
		m_ptUsedHead->m_ptPre = ptAllocBlock;
	}

	m_ptUsedHead = ptAllocBlock;
    
    //��¼��С���п���
    if (m_dwFreeBlockNum < m_dwMinFreeBlocks)
        m_dwMinFreeBlocks = m_dwFreeBlockNum;
	
    return ptAllocBlock->Data();
}

template<class Type>
u32 CTpList<Type>::FreeBuff(Type* Itor)
{	
	ListDataPtr Ptr = ListDataPtr(((char*)Itor) - ListData::m_dwDataOffset);
    if (Ptr == NULL)
    {
        return 0;
    }
	
	if (m_ptUsedHead == Ptr)	//��ʾɾ��m_ptUsedBuffList��ͷ��
	{
		m_ptUsedHead = m_ptUsedHead->m_ptNext;
		if (NULL != m_ptUsedHead)
		{
			m_ptUsedHead->m_ptPre = NULL;
		}
	}
	else
	{
		Ptr->m_ptPre->m_ptNext = Ptr->m_ptNext;
		if (NULL != Ptr->m_ptNext)
		{
			Ptr->m_ptNext->m_ptPre = Ptr->m_ptPre;
		}
	}

	Ptr->m_ptPre		=   NULL;
    Ptr->m_ptNext		=   m_ptFreeHead;
    m_ptFreeHead    =   Ptr;
    m_dwFreeBlockNum    +=  1;
	
    if (m_dwFreeBlockNum > m_dwTotalNum)
    {
        OspPrintf(TRUE, FALSE, "CKdvListBuff::FreeBuff Total Block num=%d, but Free Block num=%d\n",
			m_dwTotalNum, m_dwFreeBlockNum);
     
        m_dwFreeBlockNum = m_dwTotalNum;
    }
	
    return 1;
}


template<class Type>
Type* CTpList<Type>::GetDataByIndex(u32 wIndex)
{
	
	if (wIndex >= m_dwTotalNum)
	{
		return NULL;
	}
	
    ListDataPtr ptr =  (ListDataPtr)((u8*)m_pBuff + sizeof(ListData) * wIndex);
	
	return ptr->Data();
}


#endif // _h_tplist_h__
