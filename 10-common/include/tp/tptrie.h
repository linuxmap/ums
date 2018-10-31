/*****************************************************************************
   ģ����      : 
   �ļ���      : trie.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: �ֵ���
   ����        : ���
   �汾        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2012/03/29  1.0         ���        ����
******************************************************************************/

#ifndef TRIE_H
#define TRIE_H
#include "tpnode.h"

//�ֵ���
template<typename T>
class CTrie
{
public:
	CTrie();
	~CTrie();

public:
	//����
	BOOL32			Insert(char* szKey, const T& value);
	//����
	T*				Find(char* szKey);
	//�����ؼ��֣�ɾ���ؼ��ֶ�Ӧ��ֵ
	BOOL32			Erase(char* szKey);
	//ɾ����ͬʱɾ���ؼ��ֺͶ�Ӧ��ֵ
	BOOL32			EraseEx(char* szKey);
	//���������Ч�ڵ�����
	u16				GetTotalNodes() const;

private:
	//����ָ���Ĵ�
	CNode<T>*		FindKey(char* szKey);

private:
	CNode<T>*		m_pcRootNode;	//���ڵ�
	u16				m_wTotalNodes;	//��Ч�ڵ�����
};

template<typename T>
CTrie<T>::CTrie()
{
	m_pcRootNode	= new CNode<T>(NULL);
	m_wTotalNodes	= 0;
}

template<typename T>
CTrie<T>::~CTrie()
{
	delete m_pcRootNode;
}

/*====================================================================
������    ��Insert
����      ������ؼ��ּ����Ӧ��ֵ������ؼ����Ѿ��������������Ӧ��ֵ
�㷨ʵ��  ��
����˵��  ��[I]chkey �ؼ���	[I]value �ؼ��ֶ�Ӧ��ֵ
����ֵ˵�������ڷ���true �����ڷ���false
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/03/30  1.0   ���          ����
====================================================================*/
template<typename T>
inline BOOL32 CTrie<T>::Insert(char* szKey, const T& value)
{
	CNode<T>* pNode = FindKey(szKey);

	//�ڵ㲻���ڲ����½ڵ�
	if (NULL == pNode)
	{
		CNode<T>* pTemp = m_pcRootNode;
		u8 byIndex = 0;
		u8 byVal = szKey[byIndex];

		while (true)
		{
			byVal = szKey[byIndex];

			if (0 == byVal)
			{
				if (0 == byIndex)
				{
					return FALSE;
				}
				else
				{
					pTemp->SetValue(value);
					++m_wTotalNodes;
					break;
				}
			}
			else
			{
				pTemp = pTemp->AddChildNode(byVal);
				++byIndex;
			}
		}
	}
	else
	{
		pNode->SetValue(value);
		++m_wTotalNodes;
	}

	return TRUE;
}

/*====================================================================
������    ��Find
����      �����Ҷ�Ӧ�Ĺؼ����Ƿ����
�㷨ʵ��  ��
����˵��  ��[I]chkey �ؼ���
����ֵ˵�������ڷ��ض�Ӧ��ָ��  �����ڷ���0
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/03/30  1.0   ���          ����
====================================================================*/
template<typename T>
inline T* CTrie<T>::Find(char* szKey)
{
	CNode<T>* pNode = FindKey(szKey);
	if (NULL == pNode)
	{
		return NULL;
	}
	else
	{
		if (0 == pNode->GetValue())
		{
			return FALSE;
		}
		else
		{
			return pNode->GetValue();
		}
	}
}

/*====================================================================
������    ��Erase
����      ��ɾ��ָ���Ĵ���Ӧ����Ϣ
�㷨ʵ��  ��
����˵��  ��[I]chkey �ؼ���
����ֵ˵����ɾ���ɹ�����true  ʧ�ܷ���false
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/03/31  1.0   ���          ����
====================================================================*/
template<typename T>
inline BOOL32 CTrie<T>::Erase(char* szKey)
{
	CNode<T>* pNode = FindKey(szKey);
	if (NULL == pNode)
	{
		return FALSE;
	}
	else
	{
		if (NULL == pNode->GetValue())
		{
			return FALSE;
		}
		else
		{
			pNode->ResetValue();
			--m_wTotalNodes;
			return TRUE;
		}
	}
}

/*====================================================================
������    ��EraseEx
����      ������ɾ����ͬʱɾ���ؼ��ֺͶ�Ӧ��ֵ
�㷨ʵ��  ��
����˵��  ��[I]chkey �ؼ���
����ֵ˵����ɾ���ɹ�����true  ʧ�ܷ���false
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/03/31  1.0   ���          ����
====================================================================*/
template<typename T>
inline BOOL32 CTrie<T>::EraseEx(char* szKey)
{
	CNode<T>* pNode = FindKey(szKey);
	if (NULL == pNode)
	{
		return FALSE;
	}
	else
	{
		if (NULL == pNode->GetValue())
		{
			return FALSE;
		}
		else
		{
			pNode->ResetValue();
			--m_wTotalNodes;
			
			//ɾ�����в�������Ľڵ�
			CNode<T>* pTemp = pNode->GetParentNode();
			while (true)
			{
				if (0 != pNode->GetChilidNodeNums())
				{
					return TRUE;
				}
				else
				{
					pTemp->EraseChildNode(pNode->GetKey());
					pNode = pTemp;
					pTemp = pNode->GetParentNode();
					if (0 == pTemp)
					{
						return TRUE;
					}
				}
			}
		}
	}
}


/*====================================================================
������    ��FindKey
����      ������ָ���ؼ��ֶ�Ӧ�Ľڵ�
�㷨ʵ��  ��
����˵��  ��[I]chkey �ؼ���
����ֵ˵�������ڷ��ؽڵ��ָ�룬�����ڷ���0
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/03/30  1.0   ���          ����
====================================================================*/
template<typename T>
inline CNode<T>* CTrie<T>::FindKey(char* szKey)
{
	if (NULL == m_pcRootNode)
	{
		return NULL;
	}

	CNode<T>* pTemp = m_pcRootNode;
	u8 byIndex		= 0;
	u8 byVal		= 0;

	while (true)
	{
		byVal = szKey[byIndex];
		if (0 == byVal)
		{
			if (0 == byIndex)
			{
				return NULL;
			}
			else
			{
				return pTemp;
			}
		}
		else
		{
			if (0 == pTemp->GetChildPtr(byVal))
			{
				return 0;
			}
			else
			{
				pTemp = pTemp->GetChildPtr(byVal);
				++byIndex;
			}
		}
	}
}

/*====================================================================
������    ��GetTotalNodes
����      �����������Ч�ڵ�����
�㷨ʵ��  ��
����˵��  ����
����ֵ˵��������������Ч�ڵ�����
----------------------------------------------------------------------
�޸ļ�¼ ��
�� ��       �汾  �޸��� �߶��� �޸ļ�¼
2012/04/06  1.0   ���          ����
====================================================================*/
template<typename T>
inline u16 CTrie<T>::GetTotalNodes() const
{
	return m_wTotalNodes;
}

#endif