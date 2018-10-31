// MemManger.h: interface for the CMemManger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMMANGER_H__284F12CC_C2BA_49E7_A6FD_BFF084E12786__INCLUDED_)
#define AFX_MEMMANGER_H__284F12CC_C2BA_49E7_A6FD_BFF084E12786__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////
//  �Զ����ڴ������
//
//  [�ܿ�����(4 byte)]
//  [���ݿ�(ItemSize byte)][�Ƿ�ռ��(1 byte)][��ǰ������(4 byte)][�¿�����(4 byte)]
//  [���ݿ�(ItemSize byte)][�Ƿ�ռ��(1 byte)][��ǰ������(4 byte)][�¿�����(4 byte)]
//  ......
//  [���ݿ�(ItemSize byte)][�Ƿ�ռ��(1 byte)][��ǰ������(4 byte)][�¿�����(4 byte)]
//  [��1���п�����][��2���п�����]......[��N���п�����]
//  ������ ��1��ʼ
/////////////////////////////////////////////////////////////////
#include <singleton.h>
class CMemoryManager : public CSingleton<CMemoryManager>
{
private:
	int               m_ItemCount;  //�ܿ���
	int               m_ItemSize;   //ÿ���ֽ���
	int               m_BlockSize;  //ÿ���С=m_ItemSize+5
	int               m_FreeIndexAddr;//�����������׵�ַ
	LPVOID            pData;        //ȫ���ڴ����׵�ַ
	HANDLE            m_WaitEvent;  //�ȴ��¼�(�����ڴ治��ʱ�ȴ�)
	CRITICAL_SECTION  m_lock;       //���ݻ�����
	
	//��ʼ���ڴ�����Ԥ���ڴ�����
	BOOL Init(int iItemSize,int iItemCount);
public:
	CMemoryManager(int iItemSize,int iItemCount);
	~CMemoryManager();
	
	void Lock();
	void UnLock();
	
	//�����ڴ�����
	LPVOID New(int Len);
	//�ͷ��ڴ�����
	BOOL Delete(LPVOID p);
	
	//��ȡ���ݿ��ֽ���
	int GetItemSize();
	//��ȡ�ܿ���
	int GetItemCount();
	//��ȡ�ܿ�����
	int GetFreeCount();
	
	//��ȡ�������׵�ַ
	int GetBeginAddr(){return (int)pData;};
	
};

#endif // !defined(AFX_MEMMANGER_H__284F12CC_C2BA_49E7_A6FD_BFF084E12786__INCLUDED_)
