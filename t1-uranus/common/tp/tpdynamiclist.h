#ifndef __tpdynamiclist_h_
#define __tpdynamiclist_h_

#include "osp.h"

template<typename T>
class CDynamicList
{
public:
	CDynamicList();
	~CDynamicList();

public:
	//����,����ֵΪʵ�ʴ����Ĵ�С
	u16		Create(u16 wSize);
	//��С
	u16		Size() const;
	//���
	BOOL32	Add(const T& tValue);
	//����ͷ����
	T		Front();
	//ɾ��ͷ
	void	DelFront();

private:
	struct Node
	{
		T		m_value;
		Node*	m_ptNext;

		Node()
		{
			m_ptNext  = NULL;
		}
	};

	enum
	{
		em_alloc_size = 2,	//�ռ䲻��ʱĬ�Ϸ���Ĵ�С
	};

private:
	Node*	m_ptHead;	//ͷ���
	Node*	m_ptTail;	//β���
	Node*	m_ptCur;	//��ǰ�ڵ�
	u16		m_wTotal;	//������
	u16		m_wSize;	//��ǰ��С
};

template<typename T>
CDynamicList<T>::CDynamicList()
{
	m_ptHead = NULL;
	m_ptTail = NULL;
	m_ptCur  = NULL;
	m_wTotal = 0;
	m_wSize  = 0;
}

template<typename T>
CDynamicList<T>::~CDynamicList()
{

}

template<typename T>
u16 CDynamicList<T>::Create(u16 wSize)
{
	if (0 != m_wTotal)
	{
		return 0;
	}

	u16 wLen = 0;
	m_ptHead = new Node();
	if (NULL == m_ptHead)
	{
		return 0;
	}
	++wLen;

	if (wLen >= wSize)
	{
		return wLen;
	}
	
	Node* ptCurNode = m_ptHead;
	while (TRUE)
	{
		ptCurNode->m_ptNext = new Node();
		if (NULL == ptCurNode->m_ptNext)
		{
			break;
		}
		else
		{
			++wLen;
			ptCurNode = ptCurNode->m_ptNext;
		}

		if (wLen >= wSize)
		{
			break;
		}
	}

	m_ptTail = ptCurNode;
	m_ptTail->m_ptNext = m_ptHead;
	m_ptCur  = m_ptHead;
	m_wTotal = wLen;
	
	return wLen;
}

template<typename T>
inline u16 CDynamicList<T>::Size() const
{
	return m_wSize;
}

template<typename T>
BOOL32 CDynamicList<T>::Add(const T& tValue)
{
	if (0 == m_wTotal)
	{
		return FALSE;
	}

	if (m_wSize == m_wTotal)
	{
		u16 wIndex = 0;
		for (; wIndex < em_alloc_size; ++wIndex)
		{
			m_ptTail->m_ptNext = new Node();
			if (NULL == m_ptTail->m_ptNext)
			{
				break;
			}
			else
			{
				m_ptTail = m_ptTail->m_ptNext;
			}
		}

		m_ptTail->m_ptNext = m_ptHead;

		if (0 == wIndex)
		{
			return FALSE;
		}
		else
		{
			m_wTotal += wIndex;
			m_ptCur = m_ptCur->m_ptNext;
		}
	}

	m_ptCur->m_value = tValue;
	++m_wSize;
	if (m_wSize < m_wTotal)
	{
		m_ptCur = m_ptCur->m_ptNext;
	}

	return TRUE;
}

template<typename T>
inline T CDynamicList<T>::Front()
{
	if (0 == m_wSize)
	{
		return T();
	}
	else
	{
		return m_ptHead->m_value;
	}
}

template<typename T>
void CDynamicList<T>::DelFront()
{
	if (0 == m_wSize)
	{
		return ;
	}

	--m_wSize;

	if (NULL != m_ptHead->m_ptNext)
	{
		m_ptHead = m_ptHead->m_ptNext;
		m_ptTail = m_ptTail->m_ptNext;
	}
}

#endif