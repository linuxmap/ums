/*****************************************************************************
   ģ����      : 
   �ļ���      : mempool.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: �ڴ��
   ����        : ���
   �汾        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2012/04/07  1.0         ���        ����
******************************************************************************/
#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H
#include "kdvtype.h"

/**************************************************************
 * ʹ��˫������ʵ�ֵ�һ���ڴ��,ͨ��һ��U32��ֵ����ʶԪ�ص�λ�á�
 * �����Ҫ�޸ı�������������ַ�ʽ��һ����ͨ����ӵ�ʱ�򷵻ص�
 * ID�����ַ�ʽ�ȽϿ��١�����Ҳ����ʹ�����������ң���Ƚ�����
 * ��Ϊ������ͬ�����ݴ��ڣ����Ժ���ķ�ʽ����ȷ��Ҳ���ѱ�֤��ʹ�ø���
 * Ӧ������ʹ�ú�ID��صĽӿڽ��в���������ʹ������Ҫ��֤ID����ȷ�ԡ�
***************************************************************/
template<typename T>
class CMemPool
{
public:
	CMemPool();
	~CMemPool();

public:
	//����һ���µĿռ䣬�����ظ��û�
	u32			Add();
	//����ID��ö�Ӧ��ֵ
	T*			FindByID(u32 dwID);
	//ɾ��ID��Ӧ��ֵ
	void		EraseByID(u32 dwID);
	//���
	void		Clear();
	//�����Ч����
	u32			Size() const;

public:
	//����ȡ�õ�һ������
	T*			First();
	//һ��ȡ�����������
	T*			Next();
	//��õ�ǰ�����ڵ��ID
	u32			GetCurID();

public:
	//����ֵ���в��ң������ҵ��ĵ�һ��
	T*			Find(const T& value);
	//ͨ��ֵ�ҵ���Ӧ��ID
	u32			FindID(const T& value);
	//ɾ��ָ����ֵ
	void		Erase(const T& value);

public:
	//�������
	u32			TotalSize();
	//��ǰʹ����
	u32			UseSize();

private:
	//���ø���
	CMemPool(const CMemPool<T>& );
	CMemPool<T>& operator=(const CMemPool<T>& );

private:
	//�ڵ�
	typedef struct tagNode
	{
		tagNode*	m_pNext;	//��һ��
		tagNode*	m_pFront;	//ǰһ��
		T			m_value;	//�����ֵ
	}TNode, *PTnode;
	//ÿ�ζ������Ľڵ���
	enum
	{
		ASSIGN_SIZE	=	30
	};

private:
	//��ʼ��
	void		Init(u16 wSize);
	//����ڵ�
	u16			AssignNode(u16 wSize);

public:
	TNode*		m_pHead;		//ͷ�ڵ�
	TNode*		m_pCurNode;		//��ǰ�ڵ�
	TNode*		m_pFirstNode;	//������ʼ�ڵ�
	u32			m_dwIndex;		//����������
	u32			m_dwSize;		//��Ч�ڵ����
	u32			m_dwTotal;		//�ڵ�����
	BOOL32		m_bFlag;		//������ʶ
};

template<typename T>
CMemPool<T>::CMemPool()
{
	Init(ASSIGN_SIZE);
}

template<typename T>
CMemPool<T>::~CMemPool()
{
	TNode* pNode = m_pHead;
	TNode* pNext = NULL;
	while (NULL != pNode)
	{
		pNext = pNode->m_pNext;
		delete pNode;
		pNode = pNext;
	}
}

/*====================================================================
������    ��Add
����      ���������
�㷨ʵ��  ��
����˵��  ��[I]pValue ָ��
����ֵ˵��������һ��Ψһ�ڵ�ID
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::Add()
{
	//û�нڵ�
// 	if (0 == m_dwTotal)
// 	{
// 		return 0;
// 	}

	TNode* pNode = m_pCurNode;
	//�޿��õĽڵ�
	if (0 == m_dwTotal || m_dwSize == m_dwTotal)
	{
		if (0 == AssignNode(ASSIGN_SIZE))
		{
			return 0;
		}
		else
		{
			m_pCurNode = pNode->m_pNext;
		}
	}
	pNode = m_pCurNode;

	++m_dwSize;
	if (m_dwSize != m_dwTotal)
	{
		m_pCurNode = m_pCurNode->m_pNext;
	}

	return (u32)pNode;
}

/*====================================================================
������    ��FindByID
����      ������ָ����ID��ö�Ӧֵ�����ã���������֤ID����Ч�ԣ������Ч��
			�����쳣
�㷨ʵ��  ��
����˵��  ��[I]dwID ID
����ֵ˵��������ֵ��Ӧ��ָ�룬�������0�򷵻ؿ�ָ��
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline T* CMemPool<T>::FindByID(u32 dwID)
{
	if (0 == dwID)
	{
		return NULL;
	}
	else
	{
		TNode* pNode = (TNode*)dwID;
		return &(pNode->m_value);
	}
}

/*====================================================================
������    ��Find
����      ������ֵ���в��ң����᷵���ҵ��õ�һ������������T���Ͳ�֧��
			�Ƚϲ�����(==)����Ҫ���øýӿ�
�㷨ʵ��  ��
����˵��  ��[I]value Ҫ���ҵ�ֵ
����ֵ˵��������ֵ��Ӧ��ָ�룬�������0�򷵻ؿ�ָ��
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline T* CMemPool<T>::Find(const T& value)
{
	TNode* pNode = m_pHead->m_pNext;
	for (u16 wIndex = 0; wIndex < m_dwSize; ++wIndex)
	{
		if (value == pNode->m_value)
		{
			return &(pNode->m_value);
		}
		pNode = pNode->m_pNext;
	}
	return 0;
}

/*====================================================================
������    ��FindID
����      ������ֵ���Ҷ�Ӧ��ID�����᷵���ҵ��õ�һ������������T���Ͳ�֧��
			�Ƚϲ�����(==)����Ҫ���øýӿ�
�㷨ʵ��  ��
����˵��  ��[I]value Ҫ���ҵ�ֵ
����ֵ˵��������ֵ��Ӧ��ID���������0�򷵻ؿ�ָ��
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::FindID(const T& value)
{
	TNode* pNode = m_pHead->m_pNext;
	for (u16 wIndex = 0; wIndex < m_dwSize; ++wIndex)
	{
		if (value == pNode->m_value)
		{
			return (u32)pNode;
		}
		pNode = pNode->m_pNext;
	}
	return 0;
}

/*====================================================================
������    ��EraseByID
����      ��ɾ��ָ����ID��Ӧ������,�ڲ�����֤ID����Ч�ԣ���������ڻᷢ���쳣
�㷨ʵ��  ��
����˵��  ��[I]dwID  ID
����ֵ˵������
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline void CMemPool<T>::EraseByID(u32 dwID)
{
	TNode* pNode = (TNode*)dwID;
	if (m_pCurNode == pNode)
	{
		m_pCurNode = pNode->m_pFront;
	}

	pNode->m_pFront->m_pNext = pNode->m_pNext;
	if (0 != pNode->m_pNext)
	{
		pNode->m_pNext->m_pFront = pNode->m_pFront;
	}
	delete pNode;
	--m_dwSize;
	--m_dwTotal;
}

/*====================================================================
������    ��Erase
����      ������ֵ����ɾ��������ɾ���ҵ��õ�һ������������T���Ͳ�֧��
			�Ƚϲ�����(==)����Ҫ���øýӿ�
�㷨ʵ��  ��
����˵��  ��[I]value Ҫɾ����ֵ
����ֵ˵������
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline void CMemPool<T>::Erase(const T& value)
{
	TNode* pNode = m_pHead->m_pNext;
	for (u16 wIndex = 0; wIndex < m_dwSize; ++wIndex)
	{
		if (value == pNode->m_value)
		{
			pNode->m_pFront->m_pNext = pNode->m_pNext;
			if (0 != pNode->m_pNext)
			{
				pNode->m_pNext->m_pFront = pNode->m_pFront;
			}
			delete pNode;
			--m_dwSize;
			--m_dwTotal;

			return ;
		}
		pNode = pNode->m_pNext;
	}
}

/*====================================================================
������    ��Clear
����      �����
�㷨ʵ��  ��
����˵��  ����
����ֵ˵������
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline void CMemPool<T>::Clear()
{
	m_dwSize	= 0;
	m_pCurNode	= m_pHead->m_pNext;
}
/*====================================================================
������    ��First
����      ��������õ�һ���ڵ�����
�㷨ʵ��  ��
����˵��  ����
����ֵ˵�����ɹ�����ָ�룬ʧ�ܷ���0
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline T* CMemPool<T>::First()
{
	m_dwIndex		= 0;
	if (0 == m_dwSize)
	{
		m_bFlag = FALSE;
		return NULL;
	}
	else
	{
		m_bFlag = TRUE;
		m_pFirstNode = m_pHead->m_pNext;
		return &(m_pFirstNode->m_value);
	}
}

/*====================================================================
������    ��Next
����      �������һ���ڵ㣬�������ȳɹ�����first�������ʧ��
�㷨ʵ��  ��
����˵��  ����
����ֵ˵�����ɹ�����ָ�룬ʧ�ܷ���0
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline T* CMemPool<T>::Next()
{
	if (!m_bFlag)
	{
		return NULL;
	}

	++m_dwIndex;
	if (m_dwIndex == m_dwSize)
	{
		m_bFlag = FALSE;
		return NULL;
	}
	else
	{
		m_pFirstNode = m_pFirstNode->m_pNext;
		return &(m_pFirstNode->m_value);
	}
}

/*====================================================================
������    ��GetCurID
����      ����õ�ǰ�����ڵ��ID
�㷨ʵ��  ��
����˵��  ����
����ֵ˵�������ص�ǰ�����ڵ��ID
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::GetCurID()
{
	if (!m_bFlag)
	{
		return 0;
	}
	else
	{
		return (u32)m_pFirstNode;
	}
}

/*====================================================================
������    ��Size
����      ����ȡ��Ч����
�㷨ʵ��  ��
����˵��  ����
����ֵ˵������
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/13  1.0   ���          ����
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::Size() const
{
	return m_dwSize;
}


/*====================================================================
������    ��Init
����      ����ʼ��
�㷨ʵ��  ��
����˵��  ��[I]wSize �ڵ������
����ֵ˵������
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline void CMemPool<T>::Init(u16 wSize)
{
	m_dwSize	= 0;
	m_dwTotal	= 0;
	m_dwIndex	= 0;
	m_pCurNode	= NULL;
	m_bFlag		= FALSE;
	m_pHead = new TNode();
	if (NULL == m_pHead)
	{
		return ;
	}
	else
	{
		m_pHead->m_pFront = NULL;
		m_pHead->m_pNext  = NULL;

		m_pCurNode = m_pHead;

		AssignNode(wSize);

		m_pCurNode		= m_pHead->m_pNext;
		m_pFirstNode	= m_pHead->m_pNext;
	}
}

/*====================================================================
������    ��AssignNode
����      ������ڵ�
�㷨ʵ��  ��
����˵��  ��[I]wSize �ڵ������
����ֵ˵�������ط���Ľڵ���
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/07  1.0   ���          ����
====================================================================*/
template<typename T>
inline u16 CMemPool<T>::AssignNode(u16 wSize)
{
	for (u16 wIndex = 0; wIndex < wSize; ++wIndex)
	{
		m_pCurNode->m_pNext = new TNode();
		if (NULL == m_pCurNode->m_pNext)
		{
			return wIndex;
		}
		else
		{
			m_pCurNode->m_pNext->m_pFront = m_pCurNode;
			m_pCurNode = m_pCurNode->m_pNext;
			++m_dwTotal;
		}
	}
	m_pCurNode->m_pNext = NULL;
	return wSize;
}

template<typename T>
inline u32 CMemPool<T>::TotalSize()
{
	return m_dwTotal;
}

template<typename T>
inline u32 CMemPool<T>::UseSize()
{
	return m_dwSize;
}

#endif
