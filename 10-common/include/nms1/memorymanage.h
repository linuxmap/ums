// MemoryManage.h: interface for the CMemoryManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYMANAGE_H__7C6E73D3_62C0_46F7_B3B9_C195F48AC87E__INCLUDED_)
#define AFX_MEMORYMANAGE_H__7C6E73D3_62C0_46F7_B3B9_C195F48AC87E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "safeadapter.h"

/*
�����ڴ�ʾ��ͼ
|																															 |
|--------------------------------------------------  ���ڴ�  ----------------------------------------------------------------|
|																															 |

|------------||------------||------------||------------||------------||------------||------------||------------||------------|

  TMemBlock1     TMemBlock2   TMemBlock3     TMemBlock4   TMemBlock5    TMemBlock6    TMemBlock7     TMemBlock8   TMemBlock9

  
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2010/12/17  4.0     ��  ��    ����
*/



//tagMemBlock�������б�Ľڵ�
typedef struct tagMemBlock
{
public:

	tagMemBlock			*pNext;					//�¿�MemBlock��λ��
	char				*pBlock;				//���MemBlock��ָ����ʵ�ڴ����ʼλ��
	int					nDataSize;				//������ʵ���ݵĳ���
	int					nOccupyBlockSize;		//�������Ҫռ�����飨�����ݵ�Ҫռ�����飩 
												//ռһ������      ��ֵΪ1
												//ռ����������    ��һ���ֵΪ��ռ�Ŀ��� �����ĸ�ֵ�Ķ�Ϊ-1
												//���ڴ�û��ʱֵΪ0	
	tagMemBlock()
	{
		Init();
	}

	void Init()
	{
		pBlock = NULL;
		nDataSize = 0;
		nOccupyBlockSize = 0;
		pNext = NULL;
	}

	//������TMemBlock����
	//decreaseblocknum ���ٵĿ��п���   OccupyBlockSizeռ�ü����ڴ��  pdataҪ��ŵ���ʵ����  datasize���ݴ�С
	char* SetData( int OccupyBlockSize, char* pdata , int datasize )
	{

		nDataSize = datasize;
		nOccupyBlockSize = OccupyBlockSize;
		memcpy( pBlock, pdata, datasize );
		
		return pBlock;
	}

	//������TMemBlock����
	//psource ��ȡ���ݵ�ָ��   OccupyBlockSizeռ�ü����ڴ��  datasize  �����Block�п�����������
	void GetData(char *psource, int &OccupyBlockSize, int &datasize)
	{
		OccupyBlockSize = nOccupyBlockSize;
		datasize   = nDataSize;

		memcpy( psource, pBlock, nDataSize );
		nDataSize = 0;
		nOccupyBlockSize = 0;


	}

}TMemBlock, *PTMemBlock;




typedef struct tagBlocksManageBorder
{
	char* startpos;
	char* endpos;
	
	tagBlocksManageBorder()
	{
		Init();
	}
	
	void Init()
	{
		startpos = 0;
		endpos = 0;
	}
}TBlockBorder, *PTBlockBorder;


#define ErrNum(num)		num,
#define ErrDesc(str)	
#define _ITEMEND	


enum EmMemoryError
{
	ErrNum( emMemNoERROR )
	ErrDesc("")
	_ITEMEND
	
	
	ErrNum(emMemErrNewError)
	ErrDesc("newʱ����")
	_ITEMEND
	
	
	ErrNum(emMemErrNotEnoughError)
	ErrDesc("û���㹻���ڴ�")
	_ITEMEND


	ErrNum(emMemErrNotFound)
	ErrDesc("û���ҵ��ڴ�")
	_ITEMEND

	ErrNum(emMemErrReIniting)
	ErrDesc("�������·����ڴ�")
	_ITEMEND		
};



#define DEFAULTBLOCKSIZE	(int) 5000
#define DEFAULTBLOCKNUM		(int) 1000

class CMemoryManage //: public CTAapater<CMemoryManage>
{
public:

	/*=============================================================================
	�� �� ��:  InputData
	��    ��:  �����ݵ��ڴ�
	��    ��:  [in]pdata ����ָ��   [in]len Ҫ�������ݵĴ�С     [pout]  Ҫ�洢�������� ��������׵�ַ
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
		=============================================================================*/
	EmMemoryError	InputData(char *pdata, int len, char **pout);

	/*=============================================================================
	�� �� ��:  GettData
	��    ��:  �������
	��    ��:  [in]pdata Ҫ���ҵ�����ָ��    [out]pout ������ݵ�ָ�� [out]len�������
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
		=============================================================================*/
	EmMemoryError	GetData(char *pdata, char *pout, int &len);

	/*=============================================================================
	�� �� ��:  InitMemoryManage
	��    ��:  ��ʼ���ڴ�
	��    ��:  [in]blocksize ���С   [in]blocknum   �����Ŀ
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
		=============================================================================*/
	EmMemoryError	InitMemoryManage(int blocksize = DEFAULTBLOCKSIZE , int blocknum = DEFAULTBLOCKNUM);

	/*=============================================================================
	�� �� ��:  ResetVal
	��    ��:  ���ó�ʼ��ֵ
	��    ��:  
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
		=============================================================================*/
	void			ResetVal();

	/*=============================================================================
	�� �� ��:  GetDropApplyTimes
	��    ��:  ��������ڴ�ʧ�ܵĴ���
	��    ��:  
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
	=============================================================================*/
	DWORD			GetDropApplyTimes() { return m_dwDropApplyTimes ;}

	/*=============================================================================
	�� �� ��:  ClearAllMemory
	��    ��:  ɾ�������ڴ�
	��    ��:  
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
	=============================================================================*/
	void			ClearAllMemory();

	/*=============================================================================
	�� �� ��:  ReInit
	��    ��:  ���·����ڴ�
	��    ��:  
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
	=============================================================================*/
	EmMemoryError	ReInit( int blocksize = DEFAULTBLOCKSIZE, int blocknum = DEFAULTBLOCKNUM );


	/*=============================================================================
	�� �� ��:  CheckMemory
	��    ��:  ����ڴ��Ƿ���Է���
	��    ��:  [in]len Ϊ�ܳ���    [out]numblock��Ҫ���ڴ��
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
	=============================================================================*/
	EmMemoryError	CheckMemory(int len, int &numblock)
	{
		return CheckMemorySize( len,  numblock);
	}

	/*=============================================================================
	�� �� ��:  GetBlockBorder
	��    ��:  ����ڴ��һ�����ʼ��ַ ���һ�����ʼ��ַ
	��    ��:  [out]tBorder  λ��
	ע    ��:��
	�� �� ֵ:��
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��      ��  �汾    �޸���  �޸�����
	2010/12/17  4.0     ��  ��    ����
	=============================================================================*/
	void			GetBlockBorder(TBlockBorder &tBorder)
	{
		int	nCount = m_nMemoryTotalSize / m_nBlockSize;	
		tBorder.startpos = m_pMemStart;
		tBorder.endpos = m_pMemStart + m_nBlockSize *(nCount - 1);

	}

	void GetInfo(int &TotalMemory, int &BlockSize, int &ApplyDropTimes  )
	{
		TotalMemory = m_nMemoryTotalSize;
		BlockSize = m_nBlockSize;
		ApplyDropTimes = m_dwDropApplyTimes;
	}

	void GetManageInfo(int &NowFreeBlock, int &MaxUsingBlocks)
	{
		NowFreeBlock = m_nFreeBlock;
		MaxUsingBlocks = m_nMaxUsingBlocks;
	}

	CMemoryManage();
	virtual ~CMemoryManage();

protected:
	PTMemBlock		FindPos( char* point );
	EmMemoryError	CheckMemorySize(int len, int &numblock);	
	char* SetData(PTMemBlock pBlock, int OccupyBlockSize, char* pdata , int datasize )
	{
		m_nFreeBlock--;
		return pBlock->SetData( OccupyBlockSize,  pdata , datasize );
	}

	void GetData(PTMemBlock pBlock, char *psource, int &OccupyBlockSize, int &datasize)
	{
		m_nFreeBlock++;
		pBlock->GetData( psource, OccupyBlockSize, datasize);
	}
private:


	char		* m_pMemStart;			//���λ����ͷָ�루�����ı䣩
	PTMemBlock	m_pMemBlockStart;		//ָ��TMemBlock�ĵ�һ��ָ�루�����ı䣩
	PTMemBlock	m_pCurrentBlock;		//��ǰ���Դ�ŵ����ݵ�TMemBlockָ��
	int			m_nMemoryTotalSize;		//���ٵ������ڴ��С
	int			m_nBlockSize;			//ÿ��Block�Ĵ�С


	DWORD		m_dwDropApplyTimes;		//û������ɹ��Ĵ���
	int			m_nMaxUsingBlocks;		//ʹ����߷�ʱ ���˼���Block

	BOOL		m_bReInting;			//�������·����ڴ�
	
	
	int			m_nFreeBlock;			//��ǰ�ڴ����м��������ʹ��
};



//typedef  CTAapater< CMemoryManage >  CSafeCMemManager;


#endif // !defined(AFX_MEMORYMANAGE_H__7C6E73D3_62C0_46F7_B3B9_C195F48AC87E__INCLUDED_)
