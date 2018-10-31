#ifndef _TEMP_ARRAY_H_
#define _TEMP_ARRAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdvtype.h"


#define TEMP_ARRAY_DEFAULT_SIZE					5 //  默认初始数组个数
#define TEMP_ARRAY_DEFAULT_STEP					5 //  默认空间增加步长

#define TEMP_ARRAY_INVAILD_INDEX				0xFFFFFFFF

template<class TItem> class TempArray
{
public:

	TempArray(u32 dwInitSize = TEMP_ARRAY_DEFAULT_SIZE, u32 dwStep = TEMP_ARRAY_DEFAULT_STEP);

	TempArray(const TempArray &tempArray);

	~TempArray() { delete [] m_ptData; }

	inline TempArray& operator=(const TempArray &tempArray);

	u32 Add(const TItem *pTItemTable, u32 dwCount = 1);


	u32 Insert(u32 dwIndex, TItem *pTItemTable, u32 dwCount = 1);


	u32 Delete(u32 dwIndex, u32 dwCount = 1);


	inline BOOL32 SetAt(u32 dwIndex, TItem *pTItem);


	inline TItem& GetAt(u32 dwIndex) const;


	inline const TItem* GetItemPtr(u32 dwIndex) const;

	inline BOOL32 IsEmpty(void) const { return m_dwCount == 0; }

	inline u32 Size(void) const { return m_dwCount; }

	inline void Clear(void);

	inline TItem& operator[](u32 dwIndex) const { return GetAt(dwIndex); }

	inline TItem* GetData(void) const { return m_ptData; }


	static TItem	m_tDefault;		 //  默认元素

private:

	inline void MallocBuffer(void);
	inline void GetSpace(u32 dwNewItemCount);

private:

	TItem           *m_ptData;       //  记录数组元素的数据指针
	u32             m_dwMaxSize;     //  当前数组的最大元素个数
	u32             m_dwCount;       //  当前数组实际的元素个数
	u32             m_dwStep;        //  再分配空间时的递增的步长
};


template<class TItem> TItem TempArray<TItem>::m_tDefault;


template<class TItem>
TempArray<TItem>::TempArray(u32 dwInitSize /* = TEMP_DEFAULT_ARRAY_SIZE */,
	u32 dwStep /* = TEMP_DEFAULT_ARRAY_STEP */)
{
	m_dwMaxSize = dwInitSize;
	m_dwCount = 0;
	m_dwStep = (0 == dwStep ? TEMP_ARRAY_DEFAULT_STEP : dwStep);
	m_ptData = NULL;
	MallocBuffer();
}


template<class TItem>
TempArray<TItem>::TempArray(const TempArray &tempArray)
{
	m_dwMaxSize = tempArray.m_dwCount;
	m_dwCount = tempArray.m_dwCount;
	m_dwStep = (0 == tempArray.m_dwStep ? TEMP_ARRAY_DEFAULT_STEP : tempArray.m_dwStep);
	m_ptData = NULL;
	MallocBuffer();
	if ( tempArray.m_ptData != NULL )
	{
		memcpy( m_ptData, tempArray.m_ptData, sizeof (TItem) * m_dwCount );
	}
}


template<class TItem>
inline TempArray<TItem>& TempArray<TItem>::operator=(const TempArray &tempArray)
{
	if ( &tempArray != this )
	{
		m_dwMaxSize = tempArray.m_dwCount;
		m_dwStep = tempArray.m_dwStep;
		m_dwCount = tempArray.m_dwCount;

		MallocBuffer();
		if ( tempArray.m_ptData != NULL )
		{
			memcpy( m_ptData, tempArray.m_ptData, sizeof (TItem) * m_dwCount );
		}
	}

	return (*this);
}


template<class TItem>
u32 TempArray<TItem>::Add(const TItem *pTItemTable, u32 dwCount /* = 1 */)
{
	if (NULL == pTItemTable || 0 == dwCount)
	{
		return TEMP_ARRAY_INVAILD_INDEX;
	}

	GetSpace( dwCount );
	memcpy( m_ptData + m_dwCount, pTItemTable, dwCount * sizeof (TItem) );
	m_dwCount += dwCount;

	return m_dwCount - 1;
}


template<class TItem>
u32 TempArray<TItem>::Insert(u32 dwIndex, TItem *pTItemTable, u32 dwCount /* = 1 */)
{

	if ( dwIndex >= m_dwCount || NULL == pTItemTable || 0 == dwCount) 
	{
		return TEMP_ARRAY_INVAILD_INDEX;
	}

	GetSpace( dwCount );

	memmove( m_ptData + dwIndex + dwCount, m_ptData + dwIndex, 
		(m_dwCount - dwIndex) * sizeof (TItem) );
	memcpy( m_ptData + dwIndex, pTItemTable, dwCount * sizeof (TItem) );

	m_dwCount += dwCount;

	return dwIndex;
}


template<class TItem>
u32 TempArray<TItem>::Delete(u32 dwIndex, u32 dwCount /* = 1 */)
{
	if (dwIndex >= m_dwCount || 0 == dwCount) 
	{
		return TEMP_ARRAY_INVAILD_INDEX;
	}

	dwCount = (m_dwCount > dwIndex + dwCount) ? dwCount : (m_dwCount - dwIndex);

	memmove( m_ptData + dwIndex, m_ptData + dwIndex + dwCount,
		(m_dwCount - dwCount - dwIndex) * sizeof (TItem) );
	memset( m_ptData + (m_dwCount - dwCount), 0, dwCount * sizeof (TItem) );
	m_dwCount -= dwCount;

	return dwCount;
}


template<class TItem>
inline BOOL32 TempArray<TItem>::SetAt(u32 dwIndex, TItem *pTItem)
{
	if (dwIndex >= m_dwCount || pTItem == NULL ) 
	{
		return FALSE;
	}
	else
	{
		memcpy( m_ptData + dwIndex, pTItem, sizeof (TItem) );
		return TRUE;
	}
}


template<class TItem>
inline TItem& TempArray<TItem>::GetAt(u32 dwIndex) const
{
	if (dwIndex >= m_dwCount) 
	{
		return m_tDefault;
	}
	else
	{
		return m_ptData[dwIndex];
	}
}


template<class TItem>
inline const TItem* TempArray<TItem>::GetItemPtr(u32 dwIndex) const
{
	if (dwIndex >= m_dwCount) 
	{
		return NULL;
	}
	else
	{
		return m_ptData + dwIndex;
	}
}


template<class TItem>
inline void TempArray<TItem>::Clear(void)
{
	if ( m_ptData != NULL )
	{
		delete [] m_ptData;
		m_ptData = NULL;
	}
	m_dwCount = 0;
	m_dwMaxSize = 0;
}


template<class TItem>
inline void TempArray<TItem>::MallocBuffer(void)
{
	if ( m_ptData != NULL )
	{
		delete [] m_ptData;
		m_ptData = NULL;
	}

	if ( m_dwMaxSize > 0 )
	{
		m_ptData = new TItem [m_dwMaxSize];
		memset( m_ptData, 0, m_dwMaxSize * sizeof (TItem) );
	}
}


template<class TItem>
inline void TempArray<TItem>::GetSpace(u32 dwNewItemCount)
{
	u32 dwNewCount = m_dwCount + dwNewItemCount;
	if (m_dwStep == 0)
	{
		m_dwStep = TEMP_ARRAY_DEFAULT_STEP;
	}
	if (dwNewCount > m_dwMaxSize) 
	{
		m_dwMaxSize = (dwNewCount / m_dwStep + 1 ) * m_dwStep;

		TItem *ptOldTable = m_ptData;
		m_ptData = new TItem [m_dwMaxSize];
		if ( ptOldTable != NULL )
		{
			memcpy( m_ptData, ptOldTable, m_dwCount * sizeof (TItem) );
			delete [] ptOldTable;
		}
	}
}

#endif  //  _TEMP_ARRAY_H_
