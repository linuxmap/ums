#ifndef TEMPLATECLASS_H
#define TEMPLATECLASS_H
/*---------------------------------------------------------------------
* ��	����Singleton
* ��    �ܣ�������ͳһ�ӿ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/09	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )
#include <assert.h>
#include <string>
#include <map>
namespace AutoUIFactory
{

/*****************************************************************************
	* ����:��������	 
	* @remarks	�û��������������г�ʼ���ȴ�����������ֱ��ͨ��GetSingletonPtr()����ȡָ�� 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2012/11/29     1.0         �����      ����
 ******************************************************************************/
template<class T> class ISingleTon
{
	protected:
		static T* ms_pSingleton; 
	
	
		ISingleTon( void )
		{  
		}

	public:
		~ISingleTon( void )
		{
		   RemoveInstance();
			
		}
	 
		static T* GetSingletonPtr( void )
		{  
			if ( NULL == ms_pSingleton )
			{
				ms_pSingleton = new T ;
			}
			return ms_pSingleton;
		}


		static void RemoveInstance()
		{
			if(ms_pSingleton)
			{
				delete ms_pSingleton;
			}
			ms_pSingleton = NULL;
		}
};

template <class T> T * ISingleTon<T>::ms_pSingleton = NULL;
 

template<class T> class Singleton
{
protected:
	static T* ms_pSingleton;
public:
	Singleton( void )
	{
		assert( !ms_pSingleton );
		ms_pSingleton = static_cast<T*>(this);
	}
	~Singleton( void )
	{
		assert( ms_pSingleton );
		ms_pSingleton = 0;
	}
	static T& GetSingleton( void )
	{
		assert( ms_pSingleton );
		return ( *ms_pSingleton );
	}
	static T* GetSingletonPtr( void )
	{
		return ms_pSingleton;
	}

    static void RemoveInstance( void )
    {
        if(ms_pSingleton)
        {
            delete ms_pSingleton;
        }
        ms_pSingleton = NULL;
	}
};

class IArgs
{
public:
	IArgs( std::string strType ) : m_strType( strType ){}
	virtual ~IArgs(){}
	std::string GetType() const { return m_strType; } 
protected:
	std::string m_strType;
};

class IObserver
{
public:
	virtual ~IObserver(){}
	virtual void Update( IArgs* pArgs ) = 0;
};

/*---------------------------------------------------------------------
* ��	����ICallBackFuncBase
* ��    �ܣ��ص������ӿ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2010/08/20	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class ICallBackFuncBase
{
public:
	virtual ~ICallBackFuncBase(){}
	virtual bool operator()( const IArgs& args ) = 0;
};

/*---------------------------------------------------------------------
* ��	����CMemberCallBackFunc
* ��    �ܣ�Ϊ��Ա��������Ļص�����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2010/08/20	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
template<class T> class CMemberCallBackFunc : public ICallBackFuncBase
{
public:
    //����ص������ĸ�ʽ
    typedef bool (T::*MemberFunctionType)( const IArgs& args );
	
	// �����ʱ����ҪΪ������ֵ
    CMemberCallBackFunc( MemberFunctionType pFunc, T* pObject ) : m_pObject(pObject), m_pFuc( pFunc ) {}
	
    virtual bool operator()( const IArgs& args )
    {
        return (m_pObject->*m_pFuc)( args );
    }
	
private:
	T* m_pObject;
    MemberFunctionType m_pFuc;	
};

/*---------------------------------------------------------------------
* ��	����CMemberCallBackFunc
* ��    �ܣ�Ϊ��Ա��������Ļص�����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2010/08/20	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CCallBackFunc : public ICallBackFuncBase
{
public:
	virtual bool operator()( const IArgs& args)
	{
		return m_pFuc(args);
	}
	
    //����ص������ĸ�ʽ
    typedef bool (CallBackFunc)( const IArgs& args);
	
	// �����ʱ����ҪΪ������ֵ
    CCallBackFunc(CallBackFunc* pFunc) : m_pFuc( pFunc ) {}
	
private:
    CallBackFunc* m_pFuc;	
};

//----------------------------------------------------------
//��    ��: IItem
//��    ��: ��Ŀ���� ����Compositeģʽ
//��Ҫ�ӿ�: �ṩɾ������ӡ����á��Ȳ���,
//����˵��: DATA��Ҫ���ز�����== = �Լ�Clone���� ����ʹ����map��KEY��Ҫ����<������
//�޸ļ�¼:
//����		�汾		�޸���		�޸ļ�¼
//2010/4/26	V1.0		muxingmao	����
//----------------------------------------------------------
enum EmItemType
{
	emItem,
	emGroup
};
template<class DATA,typename KEY>
class IItem 
{
public:
	IItem()
	{
		m_emItemType	= emItem;
		m_pParentItem	= 0;
	}
	virtual ~IItem()
	{
		if ( 0 != m_ptItemData )
		{
			delete m_ptItemData;
			m_ptItemData = 0;
		}
	}
	
	// ������� �ڲ��´��һ�Σ��������������new�Ĳ�����������delete
	virtual IItem<DATA,KEY>*	AddItem( KEY key, IItem<DATA,KEY>* pItem ) {return 0;}
	virtual IItem<DATA,KEY>*	AddItem( KEY key, DATA* pData, EmItemType emType ) {return 0;}

	// �������
	virtual IItem<DATA,KEY>*	GetItemByKey( KEY key ){ return 0; }
	// �������
	virtual IItem<DATA,KEY>*	GetItemByIndex( int nIndex ){ return 0; }
	// �������
	virtual IItem<DATA,KEY>*	GetItemByData( DATA* pData ){ return 0; }
	// ɾ������
	virtual bool				DeleteItem( KEY key, bool bDeleteData = true ) { return false; }
	// ɾ����������
	virtual bool				DeleteAllItem( bool bDeleteData = true ) { return false; }
	// �����������
	virtual DATA*				GetItemData(){ return m_ptItemData; }
	// ������Ŀ����
	virtual bool		SetItemData( DATA* ptItemData )
	{ 
		if ( m_ptItemData == ptItemData || ptItemData == 0 )
		{
			return false;
		}
		if ( m_ptItemData != 0 )
		{
			delete m_ptItemData;
			m_ptItemData = 0;
		}
		m_ptItemData = ptItemData->Clone();
		return true; 
	}

	// �����Ŀ����
	virtual int					GetItemCount() = 0;
	// �洢��ȡ��Ŀ �����л������ʱ�����
	//	virtual void				Serialize( CArchive& ar ) = 0;
	// �޸���Ŀ
	virtual bool				ModifyItemKey( KEY keyNew ) = 0;
	
	// �޸���Ŀ����
	virtual IItem<DATA,KEY>*	ModifyItem( KEY key, DATA* pData ) { return 0; }
	// �����Ŀ����
	virtual KEY					GetItemName(){ return m_keyName; }
	// �����Ŀ����
	virtual EmItemType			GetItemType(){ return m_emItemType; }
	// ��ø��ڵ�
	virtual IItem<DATA,KEY>*	GetParentItem(){ return m_pParentItem; }
	// ������Ŀ
	virtual IItem<DATA,KEY>*		Clone() = 0;
	// ��Ŀ��
	KEY		m_keyName;
	// ��Ŀ����
	DATA					*m_ptItemData;	
	// ��Ŀ����
	EmItemType	m_emItemType;
	// ����Ŀ �û��޸���Ŀ
	IItem<DATA,KEY>*		m_pParentItem;
};


//----------------------------------------------------------
//��    ��: CItem
//��    �ܣ���Ŀ��
//��Ҫ�ӿ�: ͬ����
//�޸ļ�¼:
//����		�汾		�޸���		�޸ļ�¼
//2010/4/26	V1.0		muxingmao	����
//----------------------------------------------------------
template<class DATA,typename KEY>
class CItem : public IItem<DATA,KEY> 
{
public:
	CItem()
	{
		m_emItemType = emItem;
		m_ptItemData = 0;
	}
	virtual bool	DeleteItem( KEY key, bool bDeleteData = true ) { return false; }
	virtual bool	DeleteAllItem( bool bDeleteData = true ) { return false; }
	virtual int		GetItemCount() { return 0; };	
		
	virtual bool	ModifyItemKey( KEY keyNew )
	{
		if ( m_pParentItem == 0)
		{
			return false;
		}
		
		IItem<DATA,KEY>* pItem = Clone();
		
		if ( m_pParentItem->AddItem( keyNew, pItem ) != 0 )
		{
			m_pParentItem->DeleteItem( m_keyName );
			
			return true;
		}
		
		return false;
	}
	
	virtual IItem<DATA,KEY>*	Clone()
	{
		IItem<DATA,KEY>* pItem = new CItem<DATA,KEY>();
		pItem->m_keyName = m_keyName;
		pItem->SetItemData( m_ptItemData );
		pItem->m_pParentItem = m_pParentItem;
		
		return pItem;
	}
};

//----------------------------------------------------------
//��    ��: CItemGroup
//��    �ܣ���Ŀ����
//��Ҫ�ӿ�: ͬ����
//�޸ļ�¼: 
//����		�汾		�޸���		�޸ļ�¼
//2010/4/26	V1.0		muxingmao	����
//----------------------------------------------------------
template<class DATA,typename KEY>
class CItemGroup : public IItem<DATA,KEY>
{
public:
	CItemGroup()
	{
		m_emItemType = emGroup;
		m_ptItemData = 0;
	}
	
	~CItemGroup()
	{
		DeleteAllItem();
	}
	
	virtual int			GetItemCount()
	{	
		return m_pList.size(); 
	}
	
	virtual IItem<DATA,KEY>* AddItem( KEY key, IItem<DATA,KEY>* pItem )
	{
		if ( GetItemByKey( key ) == 0)
		{		
			IItem<DATA,KEY>* pTemp = pItem->Clone();
			
			pTemp->m_pParentItem = this;
			
			pTemp->m_keyName = key;
			
			m_pList.insert( map<KEY,IItem<DATA,KEY>*>::value_type( key, pTemp ));
			
			return pTemp;
		}
		return 0;
	}

	virtual IItem<DATA,KEY>* AddItem( KEY key, DATA* pData, EmItemType emType )
	{
		if ( GetItemByKey( key ) == 0)
		{		
			IItem<DATA,KEY>* pTemp = 0;
			if ( emType == emItem )
			{
				pTemp = new CItem<DATA,KEY>;
			}
			else if ( emType == emGroup )
			{
				pTemp = new CItemGroup<DATA,KEY>;
			}
			if ( pTemp == 0 )
			{
				return pTemp;
			}
			
			pTemp->m_pParentItem = this;
			
			pTemp->m_keyName = key;

            pTemp->m_ptItemData = pData->Clone();
			
			m_pList.insert( map<KEY,IItem<DATA,KEY>*>::value_type( key, pTemp ));
			
			return pTemp;
		}
		return 0;
	}
	
	virtual IItem<DATA,KEY>*		GetItemByKey( KEY key )
	{
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.find( key );
		
		IItem<DATA,KEY>* pItem = 0;
		if ( itr != m_pList.end() )
		{
			pItem = itr->second;
		}
		return pItem;
	}
	
	virtual IItem<DATA,KEY>*		GetItemByIndex( int nIndex )
	{
		IItem<DATA,KEY>* pItem = 0;
		if ( nIndex >= m_pList.size() )
		{
			return pItem;
		}
		
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while ( nIndex > 0 )
		{
			itr++;
			nIndex--;
		}
		pItem = itr->second;
		
		return pItem;
	}

	virtual IItem<DATA,KEY>*		GetItemByData( DATA* pData )
	{
		IItem<DATA,KEY>* pItem = 0;
		if ( pData == 0 )
		{
			return pItem;
		}
		
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while ( itr != m_pList.end() )
		{
			pItem = itr->second;
			if ( pItem != 0 && pItem->GetItemData() == pData )
			{
				return pItem;
			}
			itr++;
		}	
		return 0;
	}

	virtual bool		DeleteItem( KEY key, bool bDeleteData = true )
	{
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.find( key );
		
		if ( m_pList.end() == itr )
		{
			return false;
		}
		
		if ( bDeleteData == true )
		{
			delete itr->second;
			
			itr->second = 0;
		}
		
		m_pList.erase( itr );
		
		return true;
	}
	
	virtual bool		DeleteAllItem( bool bDeleteData = true )
	{
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while( itr != m_pList.end() )
		{
			itr->second->DeleteAllItem( bDeleteData );
			if ( bDeleteData == true )
			{
				delete itr->second;
				itr->second = 0;
			}			
			itr++;
		}
		
		m_pList.clear();
		
		return true;
	}
	/*	�����л������ʱ�����
	virtual void		Serialize( CArchive& ar ) 
	{
	if (ar.IsStoring())
	{
	int nItem = m_pList.size();
	
	  ar << nItem;
	  m_keyName.Serialize( ar );
	  
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();		
		for ( ; itr != m_pList.end(); itr++ )
		{
		
		  KEY key = (*itr).first;
		  key.Serialize( ar );
		  IItem<DATA,KEY> *pItem = itr->second;	
		  
			ar << (WORD)pItem->m_emItemType;
			
			  pItem->Serialize(ar);
			  }
			  }
			  else
			  {
			  int nItem = 0;
			  ar >> nItem;
			  m_keyName.Serialize( ar );
			  
				for (int i = 0; i < nItem; i++ )
				{
				IItem<DATA,KEY> *pItem;
				
				  KEY key;
				  key.Serialize( ar );
				  
					WORD wType;
					ar >> wType;
					
					  EmItemType emType = (EmItemType)wType;
					  switch (emType)
					  {
					  case emItem:
					  {
					  pItem = new CItem<DATA,KEY>;
					  }
					  break;
					  case emGroup:
					  {
					  pItem = new CItemGroup<DATA,KEY>;
					  }
					  break;
					  default:
					  {
					  pItem = new CItem<DATA,KEY>;
					  }	
					  break;
					  }
					  pItem->Serialize(ar);
					  AddItem(key,pItem);
					  }
					  }
					  }
	*/
	virtual bool		ModifyItemKey( KEY keyNew )
	{		
		if ( m_pParentItem == 0)
		{
			m_keyName = keyNew;
			return false;
		}
		
		m_pParentItem->DeleteItem( m_keyName, false );
		m_keyName = keyNew;
		if ( m_pParentItem != 0 )
		{			
			CItemGroup* pParentItem = (CItemGroup*)m_pParentItem;
			pParentItem->m_pList.insert( map<KEY,IItem<DATA,KEY>*>::value_type( keyNew, this ));
		}
		
		return true;
	}

	virtual IItem<DATA,KEY>*	ModifyItem( KEY key, DATA* pData )
	{
		if ( pData == 0 )
		{
			return 0;
		}
		IItem<DATA,KEY>* pItem = GetItemByKey( key );
		if ( pItem == 0 )
		{
			return AddItem( key, pData, emGroup );
		}
		pItem->SetItemData( pData );
		return pItem;
	}
	
	virtual IItem<DATA,KEY>*		Clone()
	{
		IItem<DATA,KEY>* pGroup = new CItemGroup<DATA,KEY>();
		pGroup->m_keyName = m_keyName;
		pGroup->m_pParentItem = m_pParentItem;
		if ( m_ptItemData != 0 )
		{
			pGroup->SetItemData( m_ptItemData );
		}
		
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while ( itr != m_pList.end() )
		{
			pGroup->AddItem( itr->first, itr->second );
			itr++;	
		}
		return pGroup;
	}
public:
	// ��Ŀ�б�
	std::map<KEY,IItem<DATA,KEY>*> m_pList;
};

/*---------------------------------------------------------------------
* ��	����INoncopyable
* ��    �ܣ����ڲ��ɿ�����Ļ��࣬�ȷ�˵һЩȫ�ֵ���Դ
* ����˵�������Ҫʹ�ã�����private�̳�
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/07/19	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class INoncopyable
{
protected:
	INoncopyable() {}
	~INoncopyable() {}
private:  // emphasize the following members are private
	   INoncopyable( const INoncopyable& );
	   const INoncopyable& operator=( const INoncopyable& );
};

} // namespace AutoUIFactory end
#endif