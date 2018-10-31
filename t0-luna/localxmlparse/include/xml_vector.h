#ifndef _XML_VECTOR_H_
#define _XML_VECTOR_H_
#include <memory.h>
#include <assert.h>
#include <string.h>
#include "xmltype.h"


template <class T>
class CXmlVector
{
	typedef struct _Itirator
	{
		T*  pBody;
		u32 dwVal;
		_Itirator*  pNext;
	public:
		_Itirator()
		{
			memset( this, 0, sizeof( struct _Itirator) );
		}
	} TItirator, *PTItirator;
	
public:
	CXmlVector()
	{
		Init();
	}
	~CXmlVector()
	{
		Init();
	}

	void  Release()
	{
		PTItirator p = m_START;
		while( p )	
		{
			PTItirator pBackUp = p;
			p = p->pNext;
			delete pBackUp;			
		}
		
		Init();
	}

	void  Update( u32 index, u32 val )
	{
		PTItirator p = Drop( index );
		p->dwVal = val;
		AddExist( p );
	}

	void  Add( T* data, u32 val )
	{
		PTItirator pNewItem = new TItirator();
		pNewItem->pBody = data;
		pNewItem->dwVal = val;

		if ( 0 == m_Size )
		{			
			m_START = pNewItem;
			m_END = pNewItem;
			m_Size++;
		}
		else
		{
			PTItirator p = m_START;
			PTItirator p_previous = NULL;
			
			while( p )
			{
				if ( m_bBigEndian )
				{
					if ( p->dwVal > val )
					{
						p_previous = p;
						p = p->pNext;					
					}
					else
					{
						break;
					}
				}
				else
				{
					if ( p->dwVal < val )
					{
						p_previous = p;
						p = p->pNext;					
					}
					else
					{
						break;
					}
				}
			}
			
			if ( NULL == p ) // insert data at the rear
			{
				assert( p_previous == m_END );
				m_END->pNext = pNewItem;
				m_END = pNewItem;
				m_END->pNext = NULL;
			}
			else if ( NULL == p_previous ) // insert data at the beginning
			{
				assert( p == m_START );
				pNewItem->pNext = m_START;
				m_START = pNewItem;
			}
			else // insert data amid the vector
			{
				assert( p_previous->pNext == p );
				PTItirator pTemp = p_previous->pNext;
				p_previous->pNext = pNewItem;
				pNewItem->pNext = pTemp;
			}
			m_Size++;
		}
	}


	T* Delete( u32 index )
	{
		if ( index >= m_Size || 0 == m_Size )
			return NULL;
		
		T* pRet = NULL;
		if ( 1 == m_Size )
		{
			assert( 0 == index );
			T* pRet = m_START->pBody;
			Release();
			return pRet;
		}
		
		if ( 0 == index )
		{
			PTItirator pTemp = m_START;
			pRet = pTemp->pBody;
			m_START = m_START->pNext;
			delete pTemp;
			m_Size--;
			return pRet;
		}
		
		PTItirator p = m_START;
		PTItirator p_previous = NULL;
		while( index-- && p )
		{
			p_previous = p;
			p = p->pNext;
		}
		
		assert( p_previous->pNext == p );
		if ( p == m_END )
		{
			m_END = p_previous;
		}
		pRet = p->pBody;
		p_previous->pNext = p->pNext;
		delete p;
		m_Size--;
		return pRet;
	}

	void  SetEndianType( BOOL32 bBigEndian )
	{
		m_bBigEndian = bBigEndian;
	}

	T*    At( u32 index, u32 &dwVal )
	{
		if ( index >= m_Size )
			return NULL;
		
		if ( index == m_Size-1 )
		{
			dwVal = m_END->dwVal;
			return m_END->pBody;
		}
		
		PTItirator p = m_START;
		while( index-- && p )
		{
			p = p->pNext;
		}
		
		dwVal = p->dwVal;
		return p->pBody;
	}

	T*    Get( u32 val, u32& index )
	{
		PTItirator p = m_START;
		index = 0;
		while( p )
		{
			if ( p->dwVal == val )
				return p->pBody;
			p = p->pNext;
			index++;
		}
		
		return NULL;
	}

	T*    Get( u32 val )
	{
		PTItirator p = m_START;
		while( p )
		{
			if ( p->dwVal == val )
				return p->pBody;
			p = p->pNext;
		}
		
		return NULL;
	}

	u32  Size(){ return m_Size; }

private:
	void  Init()
	{
		m_START   = NULL;
		m_END     = NULL;
		m_Size    = 0;
		m_bBigEndian = TRUE;
	}

	void  AddExist( PTItirator pItirator )
	{
		if ( 0 == m_Size )
		{
			m_START = pItirator;
			m_END = pItirator;
			m_Size++;
		}
		else
		{
			PTItirator p = m_START;
			PTItirator p_previous = NULL;
			
			while( p )
			{
				if ( m_bBigEndian )
				{
					if ( p->dwVal > pItirator->dwVal )
					{
						p_previous = p;
						p = p->pNext;					
					}
					else
					{
						break;
					}
				}
				else
				{
					if ( p->dwVal < pItirator->dwVal )
					{
						p_previous = p;
						p = p->pNext;					
					}
					else
					{
						break;
					}
				}
			}
			
			if ( NULL == p ) // insert data at the rear
			{
				assert( p_previous == m_END );
				m_END->pNext = pItirator;
				m_END = pItirator;
				m_END->pNext = NULL;
			}
			else if ( NULL == p_previous ) // insert data at the beginning
			{
				assert( p == m_START );
				pItirator->pNext = m_START;
				m_START = pItirator;
			}
			else // insert data amid the vector
			{
				assert( p_previous->pNext == p );
				PTItirator pTemp = p_previous->pNext;
				p_previous->pNext = pItirator;
				pItirator->pNext = pTemp;
			}
			m_Size++;
		}
	}

	PTItirator Drop( u32 index )
	{
		if ( index >= m_Size || 0 == m_Size )
			return NULL;
		
		if ( 1 == m_Size )
		{
			assert( 0 == index );
			PTItirator pTemp = m_START;
			m_START = NULL;
			m_END = NULL;
			m_Size = 0;
			return pTemp;
		}
		
		if ( 0 == index )
		{
			PTItirator pTemp = m_START;
			m_START = m_START->pNext;
			m_Size--;
			return pTemp;
		}
		
		PTItirator p = m_START;
		PTItirator p_previous = NULL;
		while( index-- && p )
		{
			p_previous = p;
			p = p->pNext;
		}
		
		assert( p_previous->pNext == p );
		if ( p == m_END )
		{
			m_END = p_previous;
		}
		p_previous->pNext = p->pNext;
		m_Size--;
		return p;
	}

private:
	PTItirator     m_START;
	PTItirator     m_END;
	u32            m_Size;
	BOOL32         m_bBigEndian;
};

#endif