#ifndef ARRAY_H_
#define ARRAY_H_

#include "osp.h"
#include "eventid.h"
#include "kdvtype.h"


// type define


// ��Ϣ����(���<<��ַ����Ʋο��ĵ�>>)
//////////////////////////////////////////////////////////////////////////

// ��ַ����ʼ��
OSPEVENT( ADDRBOOK_INIT,						EV_ADDRBOOK_BGN );

// ��ַ��ע��/ע��
OSPEVENT( ADDRBOOK_REGISTER_REQ,				EV_ADDRBOOK_BGN + 1 );
OSPEVENT( ADDRBOOK_REGISTER_ACK,				EV_ADDRBOOK_BGN + 2 );
OSPEVENT( ADDRBOOK_REGISTER_NACK,				EV_ADDRBOOK_BGN + 3 );
OSPEVENT( ADDRBOOK_UNREG_CMD,					EV_ADDRBOOK_BGN + 4 );

// ��ַ������Ӧ����Ϣ
OSPEVENT( ADDRBOOK_SAVE_ACK,					EV_ADDRBOOK_BGN + 5 );
OSPEVENT( ADDRBOOK_SAVE_NACK,					EV_ADDRBOOK_BGN + 6 );

// ���ַ����������Ŀ�����Ӧ��
OSPEVENT( ADDRBOOK_ADD_ENTRY_REQ,				EV_ADDRBOOK_BGN + 7 );
OSPEVENT( ADDRBOOK_ADD_ENTRY_ACK,				EV_ADDRBOOK_BGN + 8 );
OSPEVENT( ADDRBOOK_ADD_ENTRY_NACK,				EV_ADDRBOOK_BGN + 9 );

// ���ַ�������ӻ����������Ӧ��
OSPEVENT( ADDRBOOK_ADD_MULSETENTRY_REQ,			EV_ADDRBOOK_BGN + 10 );
OSPEVENT( ADDRBOOK_ADD_MULSETENTRY_ACK,			EV_ADDRBOOK_BGN + 11 );
OSPEVENT( ADDRBOOK_ADD_MULSETENTRY_NACK,		EV_ADDRBOOK_BGN + 12 );

// �ӵ�ַ����ɾ����Ŀ�����Ӧ��
OSPEVENT( ADDRBOOK_DEL_ENTRY_REQ,				EV_ADDRBOOK_BGN + 13 );
OSPEVENT( ADDRBOOK_DEL_ENTRY_ACK,				EV_ADDRBOOK_BGN + 14 );
OSPEVENT( ADDRBOOK_DEL_ENTRY_NACK,				EV_ADDRBOOK_BGN + 15);

// �ӵ�ַ����ɾ�������������Ӧ��
OSPEVENT( ADDRBOOK_DEL_MULSETENTRY_REQ,			EV_ADDRBOOK_BGN + 16 );
OSPEVENT( ADDRBOOK_DEL_MULSETENTRY_ACK,			EV_ADDRBOOK_BGN + 17 );
OSPEVENT( ADDRBOOK_DEL_MULSETENTRY_NACK,		EV_ADDRBOOK_BGN + 18 );

// ��������ն��б��м����ն������Ӧ��
OSPEVENT( ADDRBOOK_ADD_ENTRYTOMULSET_REQ,		EV_ADDRBOOK_BGN + 19 );
OSPEVENT( ADDRBOOK_ADD_ENTRYTOMULSET_ACK,		EV_ADDRBOOK_BGN + 20 );
OSPEVENT( ADDRBOOK_ADD_ENTRYTOMULSET_NACK,		EV_ADDRBOOK_BGN + 21 );

// �ӻ������ն��б���ɾ���ն������Ӧ��
OSPEVENT( ADDRBOOK_DEL_ENTRYFRMULSET_REQ,		EV_ADDRBOOK_BGN + 22 );
OSPEVENT( ADDRBOOK_DEL_ENTRYFRMULSET_ACK,		EV_ADDRBOOK_BGN + 23 );
OSPEVENT( ADDRBOOK_DEL_ENTRYFRMULSET_NACK,		EV_ADDRBOOK_BGN + 24);

// �޸���Ŀ�����Ӧ��
OSPEVENT( ADDRBOOK_MODIFYENTRY_REQ,				EV_ADDRBOOK_BGN + 25 );
OSPEVENT( ADDRBOOK_MODIFYENTRY_ACK,				EV_ADDRBOOK_BGN + 26 );
OSPEVENT( ADDRBOOK_MODIFYENTRY_NACK,			EV_ADDRBOOK_BGN + 27 );

// �޸Ļ����������Ӧ��
OSPEVENT( ADDRBOOK_MODIFYMULSETENTRY_REQ,		EV_ADDRBOOK_BGN + 28 );
OSPEVENT( ADDRBOOK_MODIFYMULSETENTRY_ACK,		EV_ADDRBOOK_BGN + 29 );
OSPEVENT( ADDRBOOK_MODIFYMULSETENTRY_NACK,		EV_ADDRBOOK_BGN + 30 );

// ��ȡ��ַ������Ŀ���ܸ��������Ӧ��
OSPEVENT( ADDRBOOK_GETENTRYNUM_REQ,				EV_ADDRBOOK_BGN + 31 );
OSPEVENT( ADDRBOOK_GETENTRYNUM_ACK,				EV_ADDRBOOK_BGN + 32 );
OSPEVENT( ADDRBOOK_GETENTRYNUM_NACK,			EV_ADDRBOOK_BGN + 33 );

// ��ȡ��ַ����������Ŀ��Ϣ�������Ӧ��
OSPEVENT( ADDRBOOK_GETENTRY_REQ,				EV_ADDRBOOK_BGN + 34 );
OSPEVENT( ADDRBOOK_GETENTRY_ACK,				EV_ADDRBOOK_BGN + 35 );
OSPEVENT( ADDRBOOK_GETENTRY_NACK,				EV_ADDRBOOK_BGN + 36 );

// ��ȡ��ַ���л������ܸ����������Ӧ��
OSPEVENT( ADDRBOOK_GETMULSETENTRYNUM_REQ,		EV_ADDRBOOK_BGN + 37 );
OSPEVENT( ADDRBOOK_GETMULSETENTRYNUM_ACK,		EV_ADDRBOOK_BGN + 38 );
OSPEVENT( ADDRBOOK_GETMULSETENTRYNUM_NACK,		EV_ADDRBOOK_BGN + 39 );

// ��ȡ��ַ�������л�������Ϣ�������Ӧ��
OSPEVENT( ADDRBOOK_GETMULSETENTRY_REQ,			EV_ADDRBOOK_BGN + 40 );
OSPEVENT( ADDRBOOK_GETMULSETENTRY_ACK,			EV_ADDRBOOK_BGN + 41 );
OSPEVENT( ADDRBOOK_GETMULSETENTRY_NACK,			EV_ADDRBOOK_BGN + 42 );

// ���»�ɾ����Ŀ��������ָʾ
OSPEVENT( ADDRBOOK_REFRESHENTRY_NOTIF,			EV_ADDRBOOK_BGN + 43 );
OSPEVENT( ADDRBOOK_DELENTRY_NOTIF,				EV_ADDRBOOK_BGN + 44 );
OSPEVENT( ADDRBOOK_REFRESHMULSETENTRY_NOTIF,	EV_ADDRBOOK_BGN + 45 );
OSPEVENT( ADDRBOOK_DELMULSETENTRY_NOTIF,		EV_ADDRBOOK_BGN + 46 );

// �����������/�����б�(���ַ��ģ�鷢��)
OSPEVENT ( ADDRBOOK_UPDATEINMT_CMD				, EV_ADDRBOOK_BGN + 47 );
OSPEVENT ( ADDRBOOK_UPDATEOUTMT_CMD				, EV_ADDRBOOK_BGN + 48 );

// ��յ�ַ������
OSPEVENT ( ADDRBOOK_CLEARALL_CMD				, EV_ADDRBOOK_BGN + 49 );

//ע������ͻ�Ӧ
OSPEVENT( ADDRBOOK_UNREG_REQ,					EV_ADDRBOOK_BGN + 50 );
OSPEVENT( ADDRBOOK_UNREG_ACK,					EV_ADDRBOOK_BGN + 51 );
//���ش�����
OSPEVENT( ADDRBOOK_UNREG_NACK,					EV_ADDRBOOK_BGN + 52 );

/*��ַ���༶֧��*/
// ��ȡ��ַ���л������ϵ�ܸ����������Ӧ��
OSPEVENT( ADDRBOOK_GETMULSETRELATIONNUM_REQ,		EV_ADDRBOOK_BGN + 53 );
OSPEVENT( ADDRBOOK_GETMULSETRELATIONNUM_ACK,		EV_ADDRBOOK_BGN + 54 );
OSPEVENT( ADDRBOOK_GETMULSETRELATIONNUM_NACK,		EV_ADDRBOOK_BGN + 55 );

// ��ȡ��ַ�������л������ϵ�������Ӧ��
OSPEVENT( ADDRBOOK_GETMULSETRELATION_REQ,			EV_ADDRBOOK_BGN + 56 );
OSPEVENT( ADDRBOOK_GETMULSETRELATION_ACK,			EV_ADDRBOOK_BGN + 57 );
OSPEVENT( ADDRBOOK_GETMULSETRELATION_NACK,			EV_ADDRBOOK_BGN + 58 );

// ���ַ�������ӻ������ϵ�����Ӧ��
OSPEVENT( ADDRBOOK_ADD_MULSETTOMULSET_REQ,			EV_ADDRBOOK_BGN + 59 );
OSPEVENT( ADDRBOOK_ADD_MULSETTOMULSET_ACK,			EV_ADDRBOOK_BGN + 60 );
OSPEVENT( ADDRBOOK_ADD_MULSETTOMULSET_NACK,		    EV_ADDRBOOK_BGN + 61 );

// �ӵ�ַ����ɾ���������ϵ�����Ӧ��
OSPEVENT( ADDRBOOK_DEL_MULSETFROMMULSET_REQ,		EV_ADDRBOOK_BGN + 62 );
OSPEVENT( ADDRBOOK_DEL_MULSETFROMMULSET_ACK,		EV_ADDRBOOK_BGN + 63 );
OSPEVENT( ADDRBOOK_DEL_MULSETFROMMULSET_NACK,		EV_ADDRBOOK_BGN + 64 );

OSPEVENT( ADDRBOOK_REFRESHMULSETRELATION_NOTIF,		EV_ADDRBOOK_BGN + 65 );


// error id
#define ADDRBOOK_NO_ERROR				(u32)25000
#define ADDRBOOK_MEMORY_ERROR			(u32)( ADDRBOOK_NO_ERROR + 1 )
#define ADDRBOOK_INVALID_POINTER		(u32)( ADDRBOOK_NO_ERROR + 2 )
#define ADDRBOOK_NO_ELEMENT				(u32)( ADDRBOOK_NO_ERROR + 3 )
#define ADDRBOOK_OUTOF_RANGE			(u32)( ADDRBOOK_NO_ERROR + 4 )
#define ADDRBOOK_SIZE_ZERO				(u32)( ADDRBOOK_NO_ERROR + 5 )
#define ADDRBOOK_NO_FREEPOS				(u32)( ADDRBOOK_NO_ERROR + 6 )
#define ADDRBOOK_FILEOPT_ERROR			(u32)( ADDRBOOK_NO_ERROR + 7 )
#define ADDRBOOK_EXIST_ELEMENT			(u32)( ADDRBOOK_NO_ERROR + 8 )
#define ADDRBOOK_REGISTER_ERROR			(u32)( ADDRBOOK_NO_ERROR + 9 )

// �����Buff����
#ifndef RES_H_
#define MAX_BUFFER_LEN  1024
#endif 

// ����ȡ��ַ����Ŀ����
const u32 MAX_GETENTRY_NUM = 25;
// ����ȡ��ַ�����������
const u32 MAX_GETGROUP_NUM = 5;
// ����ȡ��ַ���������ϵ����
const u32 MAX_GETGROUPRELATION_NUM = 40;


// ��ַ����Ŀ��������
#define ADD_ENTRY		0x01
#define MODIFY_ENTRY	0x02
#define DEL_ENTRY		0x03
#define SEARCH_ENTRY     0x04

// ��ַ����Ŀ����
#define ADDR_ENTRY			0x1
#define MULTISET_ENTRY		0x2
#define MULTISET_RELATION   0X3     //��ַ�����ϵ

#if defined(WIN32) 
#pragma pack(push)
#pragma pack(1)
#endif


// abstract array
//////////////////////////////////////////////////////////////////////////
template< class T >
class CAbArray
{
public :
	enum 
	{ 
		MAX_ARRAY_SIZE = 0xFFFFFFFF
	};
	// order type
	enum ArrayOrder
	{
		NO_ORDER,
		IN_ORDER,
		IN_REVERSE
	};

public :
	// attribute 
	u32 GetTotalSize( void ) { return m_dwArrTotalSize; }
	u32 GetUsedSize( void ) { return m_dwArrUsedSize; }
	ArrayOrder GetArrayOrder() { return m_OrderOfArr; }
	void ResetArrayOrder() { m_OrderOfArr = NO_ORDER; }
	
	// operation
	virtual BOOL32 ExpandArray( u32 dwNewSize ) = 0;
	virtual int StoreElement( T &Element, u32 dwIndex, BOOL32 bNeedSort = TRUE ) = 0;
	virtual int ReCallElement( T &Element, u32 dwIndex ) = 0;
	virtual void SwapElement( u32 dwIndex1, u32 dwIndex2 ) = 0;

	// get element by order,return physical index of element
	virtual int GetFirstElement( T &Element );
	virtual int GetNextElement( u32 dwIndex, T &Element );

	// sort
	int SortByShell();
	int ReOrder();

	// search

	// �ڴ��Ԫ�������в��ҿ�λ��
	int SearchFreePos( void );

	// ����Ԫ������λ������,����Ԫ������λ������
	int SearchPosByLine( u32 dwPhyIndex );
	// �����������в���ָ��Ԫ��
	int SearchElemByBinary( T& KeyElement, BOOL32 bNeedSort = TRUE);

	// �������б��м�������Ԫ�ص�����������
	int AddToOrderTable( u32 dwElementIndex );

	// �������б���������ɾ��Ԫ�ص�����������
	int DelFromOrderTable( u32 dwElementIndex );

	u32 GetLastError( void ) { return m_dwLastError; }

protected :
	u32		m_dwArrTotalSize;		// max size of array
	u32		m_dwArrUsedSize;		// current used size of array
	u32*		m_pdwOrderPos;			// order table
	ArrayOrder	m_OrderOfArr;			// order of array
	T			m_TempBuff1;
	T			m_TempBuff2;
	u32		m_dwLastError;			// ������


}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


// �������б��м���һ������Ԫ�ص�����������,�����������б��е�λ��
template< class T >
int CAbArray< T >::AddToOrderTable( u32 dwElementIndex )
{
	if ( m_pdwOrderPos == NULL )
	{
		m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	// ��������Ϊ��,���ڵ�һ������λ��
	if ( m_dwArrUsedSize == 0 )
	{
		m_pdwOrderPos[ 0 ] = dwElementIndex;
		m_OrderOfArr = IN_ORDER;
		m_dwArrUsedSize++;
		return 0;
	}
	// ��Ԫ������,�����ٲ���
	else if ( m_dwArrUsedSize == m_dwArrTotalSize )
	{
		m_dwLastError = ADDRBOOK_OUTOF_RANGE;
		return -1;
	}
	// һ�����,���������һ��λ��,Ȼ������
	else
	{
		m_pdwOrderPos[ m_dwArrUsedSize ] = dwElementIndex;
		m_dwArrUsedSize++;
		if ( m_OrderOfArr == IN_ORDER )
		{
			m_OrderOfArr = NO_ORDER;
			if ( SortByShell() == -1 )
				return -1;
		}
		else if ( m_OrderOfArr == IN_REVERSE )
		{
			m_OrderOfArr = NO_ORDER;
			if ( SortByShell() == -1 )
				return -1;
			if ( ReOrder() == -1 )
				return -1;
		}
		else
		{
			m_OrderOfArr = NO_ORDER;
			if ( SortByShell() == -1 )
				return -1;
		}
	}

	return 0;


}

// �������б���������ɾ��Ԫ�ص�����������
template< class T >
int CAbArray< T >::DelFromOrderTable( u32 dwElementIndex )
{
	if ( m_pdwOrderPos == NULL )
	{
		m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	if ( m_dwArrUsedSize == 0 )
	{
		m_dwLastError = ADDRBOOK_SIZE_ZERO;
		return -1;
	}

	int nIndex = SearchPosByLine( dwElementIndex );
	if ( nIndex == -1 )
		return -1;
	else
	{
		for( int i = nIndex; i < ( int )m_dwArrUsedSize - 1; i++ )
		{
			m_pdwOrderPos[ i ] = m_pdwOrderPos[ i + 1 ];			
		}
        m_pdwOrderPos[m_dwArrUsedSize-1] = INVALID_INDEX;
		m_dwArrUsedSize--;
	}

	return 0;
}

// �������б��л�ȡ��һ��Ԫ��,���ظ�Ԫ�ص�����λ������
template< class T >
int CAbArray< T >::GetFirstElement( T &Element )
{
	if ( m_pdwOrderPos == NULL )
	{
		m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}
	
	if ( m_dwArrUsedSize == 0 )
	{
		m_dwLastError = ADDRBOOK_SIZE_ZERO;
		return -1;
	}

	int nIndex = ReCallElement( Element, m_pdwOrderPos[ 0 ] );
	if ( nIndex == -1 )
		return -1;

	return m_pdwOrderPos[ 0 ];
}

// ������ǰԪ�ص�����λ������,�������б��л�ȡ��һ��Ԫ��,������һ��Ԫ�ؼ�������λ������
template< class T >
int CAbArray< T >::GetNextElement( u32 dwIndex, T &Element )
{
	if ( m_pdwOrderPos == NULL )
	{
		m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	if ( dwIndex > m_dwArrTotalSize )
	{
		m_dwLastError = ADDRBOOK_OUTOF_RANGE;
		return -1;
	}

	int nOrderIndex = SearchPosByLine( dwIndex );
    //guzh[2008/05/04] ����Խ�籣��
	if ( nOrderIndex == -1 || nOrderIndex+1 >= (int)m_dwArrTotalSize)
		return -1;

	int nPhyIndex = ReCallElement( Element, m_pdwOrderPos[ nOrderIndex + 1 ]);
	if ( nPhyIndex == -1 )
		return -1;

	return m_pdwOrderPos[ nOrderIndex + 1 ];
}

// ϣ��������
template< class T >
int CAbArray< T >::SortByShell()
{
	if ( m_pdwOrderPos == NULL )
	{
		m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}
	
	if ( m_OrderOfArr == IN_ORDER )
		return 0;

	if ( m_OrderOfArr == IN_REVERSE )
	{
		if ( ReOrder() == -1 )
			return -1;
		return 0;
	}

	u32 dwOffSet = m_dwArrUsedSize;
	u32 dwTemp;
	while( dwOffSet > 1 )
	{
		dwOffSet = dwOffSet / 2;
		do 
		{
			m_OrderOfArr = IN_ORDER;
			// �������б��л�ȡ�Ƚ�Ԫ�ص���������λ��,
			// ������������λ�û�ȡԪ������,�Ƚ�֮
			// �������б��н����໥����������ֵ
			// ʵ�ֲ��ƶ�Ԫ�ص�λ�������,�������б���ά������Ԫ�ص�������
			for( int j = 0, i = dwOffSet; j < (int)( m_dwArrUsedSize - dwOffSet ); j++, i++ )
			{
				if ( ReCallElement( m_TempBuff1, m_pdwOrderPos[ j ] ) == -1 )
					return -1;
				if ( ReCallElement( m_TempBuff2, m_pdwOrderPos[ i ] ) == -1 )
					return -1;
				
				if ( m_TempBuff1 > m_TempBuff2 )
				{
					dwTemp = m_pdwOrderPos[ j ];
					m_pdwOrderPos[ j ] = m_pdwOrderPos[ i ];
					m_pdwOrderPos[ i ] = dwTemp;
					m_OrderOfArr = NO_ORDER;
				}

			}
			
		} while( m_OrderOfArr != IN_ORDER );
	}

	return 0;
}

// ����
template< class T >	
int CAbArray< T >::ReOrder()
{
	return 0;
}

// ������λ�ò��ҿ�λ��,���ؿ�λ��������
template< class T >
int CAbArray< T >::SearchFreePos()
{
	u32	dwIndex = 0;
	BOOL32	bFound = FALSE;
	T		UnUsedBuff;		// δʹ�õĵ�ַ����Ŀ
		
	while ( ( dwIndex < m_dwArrTotalSize ) && ( !bFound ) )
	{
		int nIndex = ReCallElement( m_TempBuff1, dwIndex );
		if ( nIndex == -1 )
			return -1;

		if ( m_TempBuff1 != UnUsedBuff )
			dwIndex++;
		else
			bFound = TRUE;
	}
	
	if ( bFound )
		return dwIndex;
	else
	{
		m_dwLastError = ADDRBOOK_NO_FREEPOS;
		return -1;		
	}
	
}

// ����Ԫ�ص�����λ������,�������������б��е�λ��
template< class T >
int CAbArray< T >::SearchPosByLine( u32 dwPhyIndex )
{
	u32	dwIndex = 0;
	BOOL32	bFound = FALSE;
		
	// ������������Լ��
	if ( m_pdwOrderPos == NULL )
	{
		m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	// �������б��в���ָ��Ԫ��
	while ( ( dwIndex < m_dwArrUsedSize ) && ( !bFound ) )
	{
		if ( dwPhyIndex != m_pdwOrderPos[ dwIndex ] )
			dwIndex++;
		else
			bFound = TRUE;
	}
	
	if ( bFound )
		return dwIndex;
	else
	{
		m_dwLastError = ADDRBOOK_NO_ELEMENT;
		return -1;		
	}
	
}

// ������λ���ж��ֲ���ָ��Ԫ��,���ظ�Ԫ�ص�����λ������
template< class T >
int CAbArray< T >::SearchElemByBinary( T& KeyElement, BOOL32 bNeedSort/* = TRUE*/ )
{
	int nLowPos = 0;
	int nHighPos = m_dwArrUsedSize - 1;
	int nMidPos;
	BOOL32 bFound = FALSE;

	if ( m_pdwOrderPos == NULL )
	{
		m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	switch( m_OrderOfArr )
	{
	case NO_ORDER :
		if ( bNeedSort && SortByShell() == -1 )
			return -1;
		break;

	case IN_REVERSE :
		if ( ReOrder() == -1 )
			return -1;
		break;
    default:
        break;
	}

	while( ( nLowPos <= nHighPos ) && !bFound )
	{
		nMidPos = ( nLowPos + nHighPos ) / 2;
		if ( ReCallElement( m_TempBuff1, m_pdwOrderPos[ nMidPos ] ) == -1 )
			return -1;
		if ( KeyElement < m_TempBuff1 )
			nHighPos = nMidPos - 1;
		else if ( KeyElement > m_TempBuff1 )
			nLowPos = nMidPos + 1;
		else
			bFound = TRUE;
	}
	
	if ( bFound )
		return m_pdwOrderPos[ nMidPos ];
	else
	{
		m_dwLastError = ADDRBOOK_NO_ELEMENT;
		return -1;
	}

}



// array
//////////////////////////////////////////////////////////////////////////
template< class T >
class CAddArray : public CAbArray< T >
{
public :

	// constructor & destructor
	CAddArray( u32 dwArrSize = 0 );
	CAddArray( const CAddArray< T >& NewArray ) { ArrayCopy( NewArray ); }
	~CAddArray() 
	{ 
		this->m_dwArrTotalSize = 0;
		this->m_dwArrUsedSize = 0;
		this->m_OrderOfArr = this->NO_ORDER;
		if ( m_pArr != NULL ) 
		{
			delete []m_pArr; 
			m_pArr = NULL;
		}
		
		if ( this->m_pdwOrderPos != NULL ) 
		{
			delete [] this->m_pdwOrderPos;
			this->m_pdwOrderPos = NULL;
		}
	}
	
	// basic operation
	BOOL32 ExpandArray( u32 dwNewSize );
	int StoreElement( T &Element, u32 dwIndex, BOOL32 bNeedSort = TRUE );
    int StoreElementFromFile( T &Element, u32 dwIndex );
	int ReCallElement( T &Element, u32 dwIndex );
	void SwapElement( u32 dwIndex1, u32 dwIndex2 );

	// add & del
	int InsertElement( T &Element, u32 dwIndex = INVALID_INDEX );
    int InsertElementFromFile( T &Element, u32 dwIndex = INVALID_INDEX );
//	void DeletesElement( T &Element );
	int DeletesElement( u32 dwIndex );
//    BOOL32 IsIndexExisted( u32 dwIndex );

	// override
	CAddArray< T > &operator = ( const CAddArray< T > &NewArray )
	{
		ArrayCopy( NewArray );
		return *this;
	}

	T &operator[]( const u32 dwIndex ) { return m_pArr[ dwIndex ]; }
	

protected :
	T*	m_pArr;
	
private :

	// copy
	CAddArray< T > & ArrayCopy( const CAddArray< T >& NewArray );


}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


// ���캯��,���������鳤��
template< class T >
CAddArray< T >::CAddArray( u32 dwArrSize /* = 0 */ )
{
	this->m_dwArrTotalSize = 0;
	this->m_dwArrUsedSize = 0;
	this->m_OrderOfArr = this->NO_ORDER;
	m_pArr = NULL;
	this->m_pdwOrderPos = NULL;
	this->m_dwLastError = ADDRBOOK_NO_ERROR;

	if ( dwArrSize > 0 )
	{
		// ��������λ��
		if ( m_pArr != NULL )
		{
			delete[] m_pArr;
			m_pArr = NULL;
		}

		m_pArr = new T[ dwArrSize ];
		if ( m_pArr != NULL )
			this->m_dwArrTotalSize = dwArrSize;
		else
			this->m_dwLastError = ADDRBOOK_MEMORY_ERROR;

		// ��������ӳ���
		if ( this->m_pdwOrderPos != NULL )
		{
			delete[] this->m_pdwOrderPos;
			this->m_pdwOrderPos = NULL;
		}
		this->m_pdwOrderPos = new u32[ dwArrSize ];
		if ( this->m_pdwOrderPos == NULL)
			this->m_dwLastError = ADDRBOOK_MEMORY_ERROR;
		else
		{
			for ( int i = 0; i < (int)dwArrSize; i++ )
				this->m_pdwOrderPos[ i ] = INVALID_INDEX;
		}
	}
	else
		this->m_dwLastError = ADDRBOOK_SIZE_ZERO;
}

// ��������
template< class T >
CAddArray< T > &CAddArray< T >::ArrayCopy( const CAddArray< T >& NewArray )
{
	if ( m_pArr != NULL )
	{
		delete []m_pArr;
		m_pArr = NULL;
	}
	
	if ( this->m_pdwOrderPos != NULL )
	{
		delete [] this->m_pdwOrderPos;
		this->m_pdwOrderPos = NULL;
	}
	
	this->m_dwArrTotalSize = 0;
	this->m_dwArrUsedSize = 0;
	this->m_OrderOfArr = NewArray.m_OrderOfArr;
	m_pArr = new T[ NewArray.m_dwArrTotalSize ];
	this->m_pdwOrderPos = new u32[ NewArray.m_dwArrTotalSize ];
	if ( ( m_pArr == NULL ) || ( this->m_pdwOrderPos == NULL ) )
		this->m_dwLastError = ADDRBOOK_MEMORY_ERROR;
	else
	{
		this->m_dwArrTotalSize = NewArray.m_dwArrTotalSize;
		this->m_dwArrUsedSize = NewArray.m_dwArrUsedSize;
		memmove( m_pArr, NewArray.m_pArr, this->m_dwArrTotalSize * sizeof( T ) );
		memmove( this->m_pdwOrderPos, NewArray.m_pdwOrderPos, this->m_dwArrTotalSize * sizeof( u32 ) );
	}



	return *this;

}

// ��������
template< class T >
BOOL32 CAddArray< T >::ExpandArray( u32 dwNewSize )
{
	if ( m_pArr == NULL )
	{
		return FALSE;
	}
	return TRUE;
}

// ������Ԫ��д���±�ΪdwIndex��Ԫ��,�ɹ�����ʵ����������,����-1
template< class T >
int CAddArray< T >::StoreElement( T &Element, u32 dwIndex, BOOL32 bNeedSort /*= TRUE*/ )
{
	if ( m_pArr == NULL )
	{
		this->m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	if ( dwIndex >= this->m_dwArrTotalSize )
	{
		this->m_dwLastError = ADDRBOOK_OUTOF_RANGE;
		return -1;
	}
	
	// �Ƿ����һ����ȫ��ͬ�ĵ�ַ��Ŀ����ͬ��λ��
	int nIndex = CAbArray<T>::SearchElemByBinary( Element, bNeedSort );
	if ( ( nIndex != -1 ) && ( nIndex != (int)dwIndex ) )
	{		
		if ( ReCallElement( this->m_TempBuff1, nIndex ) == -1 )
			return -1;

		if ( this->m_TempBuff1 == Element )
		{
			this->m_dwLastError = ADDRBOOK_EXIST_ELEMENT;
			return -1;
		}
	}

	m_pArr[ dwIndex ] = Element;
	this->m_OrderOfArr = this->NO_ORDER;
	
	return dwIndex;
}

template< class T >
int CAddArray< T >::StoreElementFromFile( T &Element, u32 dwIndex )
{
    if ( m_pArr == NULL )
    {
        this->m_dwLastError = ADDRBOOK_INVALID_POINTER;
        return -1;
    }
    
    if ( dwIndex >= this->m_dwArrTotalSize )
    {
        this->m_dwLastError = ADDRBOOK_OUTOF_RANGE;
        return -1;
    }
    
    // �Ƿ����һ����ȫ��ͬ�ĵ�ַ��Ŀ����ͬ��λ��
    //	int nIndex = SearchElemByBinary( Element );
    // 	if ( ( nIndex != -1 ) && ( nIndex != (int)dwIndex ) )
    // 	{		
    // 		if ( ReCallElement( this->m_TempBuff1, nIndex ) == -1 )
    // 			return -1;
    // 
    // 		if ( this->m_TempBuff1 == Element )
    // 		{
    // 			this->m_dwLastError = ADDRBOOK_EXIST_ELEMENT;
    // 			return -1;
    // 		}
    // 	}
    
    m_pArr[ dwIndex ] = Element;
    this->m_OrderOfArr = this->NO_ORDER;
    
    return dwIndex;
}

// ���±�ΪdwIndex������Ԫ��ȡ������ǰԪ��,�ɹ�����Ԫ�ص�����������,����-1
template< class T >
int CAddArray< T >::ReCallElement( T &Element, u32 dwIndex )
{
	if ( m_pArr == NULL )
	{
		this->m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	if ( dwIndex >= this->m_dwArrTotalSize )
	{
		this->m_dwLastError = ADDRBOOK_OUTOF_RANGE;
		return -1;
	}

	Element = m_pArr[ dwIndex ];
	
	return dwIndex;
}

// ��������Ԫ��
template< class T >
void CAddArray< T >::SwapElement( u32 dwIndex1, u32 dwIndex2 )
{
	return;
}

// �������в���һ��Ԫ��,��������λ������
template< class T >
int CAddArray< T >::InsertElement( T &Element, 
								   u32 dwIndex /*= INVALID_INDEX*/ )
{
	if ( m_pArr == NULL )
	{
		this->m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	if ( this->m_dwArrUsedSize == this->m_dwArrTotalSize )
	{
		this->m_dwLastError = ADDRBOOK_OUTOF_RANGE;
		return -1;
	}

	// �����ǰ����Ԫ��û��ָ��������,������Ԫ�ط����һ���յ�����λ����
	if ( dwIndex == INVALID_INDEX )
	{
		dwIndex = this->SearchFreePos();
		if ( dwIndex == -1 )
			return -1;
	}

	if ( StoreElement( Element, dwIndex ) != -1 )
	{
		// ������Ԫ�ؼ�����������в�����
		if ( this->AddToOrderTable( dwIndex ) == -1 )
			return -1;

	}
	else
		return -1;

	return dwIndex;
}

template< class T >
int CAddArray< T >::InsertElementFromFile( T &Element, 
                                           u32 dwIndex /*= INVALID_INDEX*/ )
{
    if ( m_pArr == NULL )
    {
        this->m_dwLastError = ADDRBOOK_INVALID_POINTER;
        return -1;
    }
    
    if ( this->m_dwArrUsedSize == this->m_dwArrTotalSize )
    {
        this->m_dwLastError = ADDRBOOK_OUTOF_RANGE;
        return -1;
    }
    
    // �����ǰ����Ԫ��û��ָ��������,������Ԫ�ط����һ���յ�����λ����
    if ( dwIndex == INVALID_INDEX )
    {
        dwIndex = this->SearchFreePos();
        if ( dwIndex == -1 )
            return -1;
    }
    
    if ( StoreElementFromFile( Element, dwIndex ) != -1 )
    {
        // ������Ԫ�ؼ�����������в�����
        // 		if ( this->AddToOrderTable( dwIndex ) == -1 )
        // 			return -1;
        this->m_pdwOrderPos[ this->m_dwArrUsedSize ] = dwIndex;
        this->m_dwArrUsedSize++;
    }
    else
        return -1;
    
    return dwIndex;
}
// ɾ���±�ΪdwIndex��Ԫ��,�ɹ�����ʵ��ɾ����Ԫ������,����-1
template< class T >
int CAddArray< T >::DeletesElement( u32 dwIndex )
{
	if ( m_pArr == NULL )
	{
		this->m_dwLastError = ADDRBOOK_INVALID_POINTER;
		return -1;
	}

	if ( dwIndex >= this->m_dwArrTotalSize )
	{
		this->m_dwLastError = ADDRBOOK_OUTOF_RANGE;
		return -1;
	}

	T UnUsedBuff;
	m_pArr[ dwIndex ] = UnUsedBuff;		// ����Ӧ����λ����Ϊ��
	
	// �����������ɾ��
	if ( this->DelFromOrderTable( dwIndex ) == -1 )
		return -1;

	return dwIndex;
}

// �����Ƿ��Ѿ�����
//template< class T >
// BOOL32 CAddArray< T >::IsIndexExisted( u32 dwIndex )
// {
//     if ( this->m_pdwOrderPos == NULL )
//     {
//         this->m_dwLastError = ADDRBOOK_INVALID_POINTER;
//         return -1;
//     }
//     
//     if ( dwIndex >= this->m_dwArrTotalSize )
//     {
//         this->m_dwLastError = ADDRBOOK_OUTOF_RANGE;
//         return -1;
//     }
//     
// //     T UnUsedBuff;
// //     m_pArr[ dwIndex ] = UnUsedBuff;		// ����Ӧ����λ����Ϊ��
// //     
// //     // �����������ɾ��
// //     if ( this->DelFromOrderTable( dwIndex ) == -1 )
// //         return -1;
//     for (u32 i = 0 ; i < this->m_dwArrUsedSize; i++)
//     {
//         if (dwIndex == this->m_pdwOrderPos[i])
//         {
//             return TRUE;
//         }
//         else
//         {
//             continue;
//         }
//     }
//     
//     return FALSE;
// }

#if defined(WIN32) 
#pragma pack(pop)
#endif

#endif // ARRAY_H_
