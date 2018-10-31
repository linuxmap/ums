/*=============================================================================
ģ   ��   ��: ���ܹ���ģ���
��   ��   ��: tplhash.h
�� ��  �� ��: ��
�ļ�ʵ�ֹ���: ����map�����ݵ�ģ����
��        ��: ���ǿ
��        ��: V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
˵        ��: 1.��Ƶ�Ŀ�����ڿ���ӳ��osp��Ϣ���䴦������
              2.�������õ���������Ϊ�򵥵����ݣ�������Ҫ��������ռ䣬������memcpyʵ�ָ�ֵ�Ĺ��ܡ�
              3.����Ԫ��(TKey)�����ǿ���<��==�Ƚϴ�С��, ����ʹ��s32��s16��s8��u32��u16��u8
              4.��ģ���಻֧��Ƕ��, ���ܺ�TplArray����
              5.����ҪMFC֧��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2005/01/27  3.6     ���ǿ      ����
2005/11/10  4.0     ���        ����ʵ��
2005/12/08  4.0     ���        ����������ļ�
=============================================================================*/

#ifndef _TPLHASH_20051208_H_
#define _TPLHASH_20051208_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DEFAULT_HASH_SIZE       (int)100    //  Ĭ�ϳ�ʼ����ռ��С

////////////////////////////////////////////////////////////////////////
// 
//  TplHash     ��ϣ���ģ����
// 
// ��ϣ��Ľṹ�������
//              ����Ԫ��
//      [----------------------|-------------------]
//      [ TKey                 |     TItem         ]
// �ڵ㰴�մ�С�����˳������
//
//  ����ڵ����
//                             TKey
//                               |
//                           Hash value
//                               |
//                 ------------------------------
//                 |                            |
//          value exist in table            value not exist
//                 |                            |
//          replace value          find appropriate place to save the value
//
//
//   ��ѯ����
//                             TKey
//                               |
//                           Hash value
//                               |
//                    Search in hash entry list
//                               |
//               ---------------------------------
//              |                                 |
//      Find match TKey, return TRUE      No match, return FALSE
//

template<class TKey, class TItem>
class TplHash
{
public:
    //�����ڵ�ṹ
    typedef struct tagHashNode
    {
        tagHashNode()
        {
            memset( &m_tKey, 1, sizeof (m_tKey) );
        }
        tagHashNode(const TKey &tKey, const TItem &tItem) : m_tKey(tKey)
        {
            m_tItem = tItem;
        }
        TKey    m_tKey;
        TItem   m_tItem;
    } THashNode;

public:
    /*=============================================================================
    �� �� ��:TplHash
    ��    ��:���캯��
    ��    ��:int nInitSize                  [in]    ��ʼ�ռ��С
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/10  4.0     ���    ����
    =============================================================================*/
    TplHash(int nInitSize = DEFAULT_HASH_SIZE);

    /*=============================================================================
    �� �� ��:TplHash
    ��    ��:�������캯��
    ��    ��:const TplArray &tplHash        [in]    Դ����
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/10  4.0     ���    ����
    =============================================================================*/
    TplHash(const TplHash &tplHash);

    /*=============================================================================
    �� �� ��:~TplHash
    ��    ��:��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/10  4.0     ���    ����
    =============================================================================*/
    ~TplHash();

    /*=============================================================================
    �� �� ��:operator=
    ��    ��:��ֵ
    ��    ��:const TplArray &tplHash        [in]    Դ����
    ע    ��:��
    �� �� ֵ:����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/09  4.0     ���    ����
    =============================================================================*/
    inline TplHash& operator=(const TplHash &tplHash);

    /*=============================================================================
    �� �� ��:IsExist
    ��    ��:�жϼ�ֵ�Ƿ����
    ��    ��:const TKey &tKey               [in]    ��ֵ
    ע    ��:��
    �� �� ֵ:����:TRUE; ������: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/09  4.0     ���    ����
    =============================================================================*/
    inline BOOL IsExist(const TKey &tKey) const { return Find( tKey ) != -1; }

    /*=============================================================================
    �� �� ��:SetAt
    ��    ��:��һ����ֵ��һ��������ע���ڱ���
    ��    ��:const TKey &tKey               [in]    ��ֵ
             const TItem &tItem             [in]    ������
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/01/26	3.6		���ǿ	����
    2005/11/09  4.0     ���    ��Ƶ���
    =============================================================================*/
    void SetAt(const TKey &tKey, const TItem &tItem);

    /*=============================================================================
    �� �� ��:GetAt
    ��    ��:��ȡ��ֵ
    ��    ��:const TKey &tKey               [in]    ��ֵ
             TItem &tItem                   [out]    ������
    ע    ��:��
    �� �� ֵ:�ҵ�����TRUE��û�ҵ�����FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/01/26	3.6		���ǿ	����
    2005/11/09  4.0     ���    ��Ƶ���
    =============================================================================*/
    inline BOOL GetAt(const TKey &tKey, TItem &tItem) const;

    /*=============================================================================
    �� �� ��:Delete
    ��    ��:ɾ����ֵ
    ��    ��:const TKey &tKey               [in]    ��ֵ
    ע    ��:��
    �� �� ֵ:�ҵ�����TRUE��û�ҵ�����FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/09  4.0     ���    ����
    =============================================================================*/
    inline BOOL Delete(const TKey &tKey);

    /*=============================================================================
    �� �� ��:GetEntryNum
    ��    ��:��ȡ�ڵ�����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�ڵ�����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/09  4.0     ���    ����
    =============================================================================*/
    inline int GetEntryNum(void) const { return m_nUsedSize; }

    /*=============================================================================
    �� �� ��:Clear
    ��    ��:���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/09  4.0     ���    ����
    =============================================================================*/
    inline void Clear(void);

private:
    /*=============================================================================
    �� �� ��:Find
    ��    ��:���Ҽ�ֵ
    ��    ��:const TKey &tKey               [in]    ��ֵ
    ע    ��:��
    �� �� ֵ:���ؼ�ֵ��m_ptHashTable��������, -1Ϊû�ҵ�
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/11/09  4.0     ���    ����
    =============================================================================*/
    inline int Find(const TKey &tKey) const;

private:
    THashNode   *m_ptHashTable; //��������Ϣ�ı�
    int         m_nTableSize;   //����ռ��С
    int         m_nUsedSize;    //ʹ�ô�С
};

/*=============================================================================
�� �� ��:TplHash
��    ��:���캯��
��    ��:int nInitSize                  [in]    ��ʼ�ռ��С
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/10  4.0     ���    ����
=============================================================================*/
template<class TKey, class TItem>
TplHash<TKey, TItem>::TplHash(int nInitSize /* = DEFAULT_HASH_SIZE */)
    : m_nUsedSize(0), m_nTableSize(nInitSize), m_ptHashTable(NULL)
{
    m_ptHashTable = (nInitSize > 0 ? new THashNode [nInitSize] : NULL);
}

/*=============================================================================
�� �� ��:TplHash
��    ��:�������캯��
��    ��:const TplArray &tplHash        [in]    Դ����
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/10  4.0     ���    ����
=============================================================================*/
template<class TKey, class TItem>
TplHash<TKey, TItem>::TplHash(const TplHash &tplHash)
    : m_nTableSize(tplHash.m_nUsedSize), m_nUsedSize(tplHash.m_nUsedSize),
      m_ptHashTable(NULL)
{
    if ( this != &tplHash && m_nUsedSize > 0 )
    {
        m_ptHashTable = new THashNode [m_nUsedSize];
        ASSERT( m_ptHashTable != NULL );
        memcpy( m_ptHashTable, tplHash.m_ptHashTable,
                sizeof (THashNode) * m_nUsedSize );
    }
}

/*=============================================================================
�� �� ��:~TplHash
��    ��:��������
��    ��:��
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/10  4.0     ���    ����
=============================================================================*/
template<class TKey, class TItem>
TplHash<TKey, TItem>::~TplHash()
{
    if ( m_ptHashTable != NULL )
    {
        delete [] m_ptHashTable;
        m_ptHashTable = NULL;
    }
}

/*=============================================================================
�� �� ��:operator=
��    ��:��ֵ
��    ��:const TplArray &tplHash        [in]    Դ����
ע    ��:��
�� �� ֵ:����
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����
=============================================================================*/
template<class TKey, class TItem>
inline TplHash<TKey, TItem>& TplHash<TKey, TItem>::operator=(const TplHash &tplHash)
{
    if ( this != &tplHash )
    {
        m_nUsedSize = tplHash.m_nUsedSize;
        m_nTableSize = m_nUsedSize;

        if ( m_ptHashTable != NULL )
        {
            delete [] m_ptHashTable;
            m_ptHashTable = NULL;
        }

        if ( m_nUsedSize > 0 )
        {
            m_ptHashTable = new THashNode [m_nUsedSize];
            ASSERT( m_ptHashTable != NULL );
            memcpy( m_ptHashTable, tplHash.m_ptHashTable,
                    sizeof (THashNode) * m_nUsedSize );
        }
    }

    return (*this);
}

/*=============================================================================
�� �� ��:Find
��    ��:���Ҽ�ֵ
��    ��:const TKey &tKey               [in]    ��ֵ
ע    ��:��
�� �� ֵ:���ؼ�ֵ��m_ptHashTable��������, -1Ϊû�ҵ�
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����
=============================================================================*/
template<class TKey, class TItem>
inline int TplHash<TKey, TItem>::Find(const TKey &tKey) const
{
    int nRight  = m_nUsedSize - 1;
    int nLeft   = 0;
    int nMid    = nRight / 2;

    if ( m_nUsedSize == 0 )
        return -1;

    while ( nRight >= nLeft )
    {
        if ( m_ptHashTable[nMid].m_tKey == tKey )
        {
            return nMid;
        }
        else if ( m_ptHashTable[nMid].m_tKey < tKey )
        {
            nLeft = nMid + 1;
        }
        else
        {
            nRight = nMid - 1;
        }

        nMid = (nRight + nLeft + 1) / 2;
    }

    return -1;
}

/*=============================================================================
�� �� ��:SetAt
��    ��:��һ����ֵ��һ��������ע���ڱ���
��    ��:const TKey &tKey               [in]    ��ֵ
         const TItem &tItem             [in]    ������
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/01/26	3.6		���ǿ	����
2005/11/09  4.0     ���    ��Ƶ���
=============================================================================*/
template<class TKey, class TItem>
void TplHash<TKey, TItem>::SetAt(const TKey &tKey, const TItem &tItem)
{
    int nRight  = m_nUsedSize - 1;
    int nLeft   = 0;
    int nMid    = nRight / 2;
    THashNode tHashNode( tKey, tItem );

    if ( m_nUsedSize == 0 )  //  ��ǰû��Ԫ�أ�ֱ�����
    {
        if ( m_nTableSize == 0 )
        {
            m_ptHashTable = new THashNode( tKey, tItem );
            ASSERT( m_ptHashTable != NULL );
            m_nTableSize = 1;
        }
        else
        {
            m_ptHashTable[0] = tHashNode;
        }
        m_nUsedSize = 1;
        return;
    }

    while ( nRight >= nLeft )
    {
        if ( m_ptHashTable[nMid].m_tKey == tKey )  //  Ԫ���Ѵ��ڣ�ˢ��
        {
            m_ptHashTable[nMid] = tHashNode;
            return;
        }
        else if ( m_ptHashTable[nMid].m_tKey < tKey )
        {
            nLeft = nMid + 1;
        }
        else
        {
            nRight = nMid - 1;
        }

        nMid = (nRight + nLeft + 1) / 2;
    }

    if ( m_nTableSize > m_nUsedSize )   //  ���пռ�
    {
        memmove( m_ptHashTable + nMid + 1, m_ptHashTable + nMid,
                 (m_nUsedSize - nMid) * sizeof (THashNode) );
    }
    else    //  ��Ҫ�������ռ�
    {
        THashNode *ptOldTable = m_ptHashTable;
        m_ptHashTable = new THashNode [m_nUsedSize + 1];
        ASSERT( m_ptHashTable != NULL );
        memcpy( m_ptHashTable, ptOldTable, nMid * sizeof (THashNode) );
        memcpy( m_ptHashTable + nMid + 1, ptOldTable + nMid,
                (m_nUsedSize - nMid) * sizeof (THashNode) );
        m_nTableSize++;
        delete [] ptOldTable;
    }
    m_ptHashTable[nMid] = tHashNode;
    m_nUsedSize++;

    return;
}

/*=============================================================================
�� �� ��:GetAt
��    ��:��ȡ��ֵ
��    ��:const TKey &tKey               [in]    ��ֵ
         TItem &tItem                   [out]    ������
ע    ��:��
�� �� ֵ:�ҵ�����TRUE��û�ҵ�����FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/01/26	3.6		���ǿ	����
2005/11/09  4.0     ���    ��Ƶ���
=============================================================================*/
template<class TKey, class TItem>
inline BOOL TplHash<TKey, TItem>::GetAt(const TKey &tKey, TItem &tItem) const
{
    int nIndex = Find( tKey );
    if ( nIndex != -1 )
    {
        tItem = m_ptHashTable[nIndex].m_tItem;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*=============================================================================
�� �� ��:Delete
��    ��:ɾ����ֵ
��    ��:const TKey &tKey               [in]    ��ֵ
ע    ��:��
�� �� ֵ:�ҵ�����TRUE��û�ҵ�����FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����
=============================================================================*/
template<class TKey, class TItem>
inline BOOL TplHash<TKey, TItem>::Delete(const TKey &tKey)
{
    int nIndex = Find( tKey );

    if ( nIndex != -1 )
    {
        memmove( m_ptHashTable + nIndex, m_ptHashTable + nIndex + 1,
                 (--m_nUsedSize - nIndex) * sizeof (THashNode) );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*=============================================================================
�� �� ��:Clear
��    ��:���
��    ��:��
ע    ��:��
�� �� ֵ:��
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2005/11/09  4.0     ���    ����
=============================================================================*/
template<class TKey, class TItem>
inline void TplHash<TKey, TItem>::Clear(void)
{
    m_nUsedSize = 0;
    // ����@2005.12.28  ����Ҫ�������״̬
    m_nTableSize = 0;
    if ( m_ptHashTable != NULL )
    {
        delete [] m_ptHashTable;
        m_ptHashTable = NULL;
    }
}

#endif  //  _TPLHASH_20051208_H_