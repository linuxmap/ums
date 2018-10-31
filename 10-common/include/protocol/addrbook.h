#ifndef ADDR_BOOK_H
#define ADDR_BOOK_H

#include "osp.h"
#include "eventid.h"
#include "kdvtype.h"

const u8  HOST_ORDER = 1;				// �ֽ���
const u8  NET_ORDER = 2;				// ������
#define	  MAX_NAME_LEN   32				// ������ֳ�(�궨����������parse error)
const u32 MAX_H323ALIAS_LEN = 32;		// ����������
const u32 MAX_E164NUM_LEN = 16;		    // �����볤��
const u32 MAX_H320ID_LEN  = 48;		    // ���H320ID����
const u32 MAX_IPADDR_LEN  = 15;		    // ���IP��ַ����
const u32 MAX_ADDRENTRY = 5000;			// ��ַ�����ɵ�����ַ��Ŀ
const u32 MAX_ADDRGROUP = 64;			// ��ַ�����ɵ���������
const u32 MAXNUM_ENTRY_TABLE = 192;	    // ����ն��б����
const u32 MAXNUM_GROUP_TABLE = 128;	    // ���������б����
const u32 INVALID_INDEX = 0xFFFFFFFF;   // ��Ϊ��ʼ������
const u32 MAX_GROUP_USERDATA_LEN = 256; // �������û�������󳤶�
const u16 MAX_DELENTRY_NUM = 512;       // һ��ɾ����Ŀ������
const u32 MULTI_ENTRY = 0xFEFEFEFE;     // ɾ����Ŀ������Ŀʱ������ʾ����

const u32 VERSION1_ADDRENTRY_LENGTH = 143;     // �汾1�ĵ�ַ��Ŀ����
const u32 VERSION1_MULTISETENTRY_LENGTH = 813; // �汾1������Ŀ����

const u32 VERSION_MARK = 0x00000000;         //��ϵͳ��ַ���ļ����ݺ�汾��ʶ
const u32 VERSION_ID1   = 110825;             //addrbook.kdv�汾ID,�ð汾��ַ���������ʲ�����
const u32 VERSION_ID2   = 120215;             //���л�������Ŀ��νṹ�ĵ�ַ��
const u32 VERSION_ID    = 120215/*110923*/;



#include "array.h"

#define     ADDRBOOK_PATH_LEN       256
#define		ADDRBOOK_APPID	        46	//��ַ��
#define		ADDRBOOK_LOG_HINT		100
#define		ADDRBOOK_LOG_ERROR	    0


#if defined(WIN32) 
#pragma pack(push)
#pragma pack(1)
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

// ��ַ����Ŀ��Ϣ
struct tagAddrEntryInfo
{
	char	achEntryName[ MAX_NAME_LEN + 1 ];		// ��Ŀ����
	char	achMtAlias[ MAX_H323ALIAS_LEN + 1 ];	// ���б���
	u32	    dwMtIpAddr;								// IP��ַ(������)
	char	achMtNumber[ MAX_E164NUM_LEN + 1 ];		// ���к���
	u8      bH320Terminal;                          // 0:H323�ն�; ��0:H320�ն�
	char    achH320Id[MAX_H320ID_LEN];              // H320ID
	u16	    wCallRate;								// ��������

public:
    void print()
    {
        OspPrintf(TRUE,FALSE, "tagAddrEntryInfo:==========\n");
        if ( bH320Terminal != (u8)0 )
        {
            OspPrintf( TRUE, FALSE, "H320Id : %s\n", achH320Id);
            OspPrintf( TRUE, FALSE, "======================\n" );
            return;
        }
        
        if ( achEntryName == NULL )
            OspPrintf( TRUE, FALSE, "Name    : 0\n" );
        else
            OspPrintf( TRUE, FALSE, "Name    : %s\n", achEntryName );
        
        if ( achMtAlias == NULL )
            OspPrintf( TRUE, FALSE, "Alias	 : 0\n" );
        else
            OspPrintf( TRUE, FALSE, "Alias	 : %s\n", achMtAlias );
        
        if ( achMtNumber == NULL )
            OspPrintf( TRUE, FALSE, "Number  : 0\n" );
        else
            OspPrintf( TRUE, FALSE, "Number  : %s\n", achMtNumber );
        
        OspPrintf( TRUE, FALSE, "IP      : 0x%x\n", dwMtIpAddr );
        OspPrintf( TRUE, FALSE, "Rate    : 0x%x\n", wCallRate );
        OspPrintf( TRUE, FALSE, "======================\n" );
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

typedef tagAddrEntryInfo TADDRENTRYINFO;

// ��������Ϣ
struct tagMultiSetEntryInfo
{
    tagMultiSetEntryInfo() {achGroupName[0]='\0'; dwUserDataLen = 0;}
    char achGroupName[ MAX_NAME_LEN + 1 ];	// ����
	u32	dwMcuIpAddr;						// MCU��ַ(������)
	u16	wConfBitRate;						// ��������
	u8	byOpen;								// ������(0:����	1:�ǿ���)
    u32 dwUserDataLen;                            // �û����ݳ���
    u8  byUserData[MAX_GROUP_USERDATA_LEN];                          // �û�����256�ֽ�
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
typedef tagMultiSetEntryInfo TMULTISETENTRYINFO;

//�༶������ṹ����
struct TMultiLevel
{
private:
    u32 m_byGroupIndex;
    u32 m_byUpGroupIndex;
public:
    TMultiLevel()
    {
        Clear();
    }
    
    void Clear()
    {
        m_byGroupIndex = INVALID_INDEX;
        m_byUpGroupIndex = INVALID_INDEX;
    }

    BOOL32 IsNull()
    {
        if ( m_byGroupIndex == INVALID_INDEX ||
             m_byUpGroupIndex == INVALID_INDEX)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    u32 GetGroupIndex(){ return ntohl(m_byGroupIndex); }
    void SetGroupIndex( u32 dwGroupIndex ){ m_byGroupIndex = htonl(dwGroupIndex); }
    
    u32 GetUpGroupIndex(){ return ntohl(m_byUpGroupIndex); }
    void SetUpGroupIndex( u32 dwUpGroupIndex ){ m_byUpGroupIndex = htonl(dwUpGroupIndex); } 
    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


class CAddrBook;


// ��ַ����Ŀ
////////////////////////////////////////////////////////////////////////////////////
class CAddrEntry
{
	friend class CAddrBook;
public :
	// constructor,destructor,copy-constructor,assign
	/*
	====================================================================
    ����        ���޲ι��캯��
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrEntry();

	/*
	====================================================================
    ����        ������ַ����Ŀ��Ϣ�ṹ�����Ĺ��캯��
    �������˵������ַ��Ŀ��Ϣ�ṹ
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrEntry( const TADDRENTRYINFO &tAddrEntryInfo );

	/*
	====================================================================
    ����        ������ַ����Ŀ��������Ĺ��캯��
    �������˵������ַ��Ŀ����
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrEntry( const CAddrEntry &cNewAddrEntry );

	/*
	====================================================================
    ����        ����������
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	~CAddrEntry();

	/*
	====================================================================
    ����        ����ֵ���غ���
    �������˵����
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrEntry &operator = ( const CAddrEntry &cOtherAddrEntry );

	// get entry
	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ�ֽ���
    �������˵������
    ����ֵ˵��  ����ǰ��Ŀ���ֽ���
	====================================================================
	*/
	const u8 GetEntryByteOrder( void ) const
		{ return m_byByteOrder; }
	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ����(��ַ��Ŀ�����û������޸�)
    �������˵������
    ����ֵ˵��  ����ַ��Ŀ������λ������
	====================================================================
	*/
	const u32 GetEntryIndex( void ) const
		{ return m_dwAddrEntryIndex; }

	/*
	====================================================================
    ����        �����õ�ַ��Ŀ����
    �������˵������ַ����Ŀ����
    ����ֵ˵��  ����ַ��Ŀ������λ������
	====================================================================
	*/
    const void SetEntryIndex(u32 AddrEntryIndex)
    {
        m_dwAddrEntryIndex = AddrEntryIndex;
    }
	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ��Ϣ
    �������˵���������Ŀ��Ϣ�Ļ�����
    ����ֵ˵��  ��ptAddrEntryInfo -- ��Ŀ��Ϣ
	====================================================================
	*/
	void GetEntryInfo( TADDRENTRYINFO *ptAddrEntryInfo );

	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ����
    �������˵���������Ŀ���ƵĻ����� + ����������
    ����ֵ˵��  ��pchEntryName -- ��Ŀ����
	====================================================================
	*/
	void GetEntryName( char* pchEntryName, u32 dwNameLen );

	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ��H323����
    �������˵�������H323�����Ļ����� + ����������
    ����ֵ˵��  ��pchMtAlias -- �ն˱���
	====================================================================
	*/
	void GetMtAlias( char* pchMtAlias, u32 dwAliasLen );

	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ��IP��ַ
    �������˵�������IP��ַ�Ļ����� + ����������
    ����ֵ˵��  ��pchMtIpAddr -- �ն�IP��ַ
	====================================================================
	*/
	 void GetMtIpAddr( char* pchMtIpAddr, u32 dwIpAddrLen );
	 u32  GetMtIpAddr() const
	{
		return this->m_tAddrEntryInfo.dwMtIpAddr;
	}
	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ�ĺ���
    �������˵������ź���Ļ����� + ����������
    ����ֵ˵��  ��pchMtNumber -- �ն˺���
	====================================================================
	*/
	void GetMtNumber( char* pchMtNumber, u32 dwNumberLen );
	
	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ�ĺ�������
    �������˵������
    ����ֵ˵��  ���������ʣ�kbps��
	====================================================================
	*/
	const u16 GetCallRate( void ) 
		{ return m_tAddrEntryInfo.wCallRate; }

	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ���Ƴ���
    �������˵������
    ����ֵ˵��  ����ַ��Ŀ���Ƴ���
	====================================================================
	*/
	const u32 GetEntryNameLen( void ) 
		{ return strlen( m_tAddrEntryInfo.achEntryName ); }

	/*
	====================================================================
    ����        ����ȡ��ַ��ĿH323��������
    �������˵������
    ����ֵ˵��  ��H323��������
	====================================================================
	*/
	const u32 GetMtAliasLen( void ) 
		{ return strlen( m_tAddrEntryInfo.achMtAlias ); }

	/*
	====================================================================
    ����        ����ȡ��ַ��Ŀ�绰���볤��
    �������˵������
    ����ֵ˵��  ���绰���볤��
	====================================================================
	*/
	const u32 GetMtNumberLen( void ) 
		{ return strlen( m_tAddrEntryInfo.achMtNumber ); }

	/*
	====================================================================
    ����        ����ȡH320��ַ��Ŀ
    �������˵�������H320����Ļ����� + ����������
    ����ֵ˵��  ��pchH320MtId -- �ն˺���
	====================================================================
	*/
	void GetH320MtId( char* pchH320MtId, u32 dwIdLen ); 

	
	/*
	====================================================================
    ����        ����ȡH320��ַ��Ŀ�ĳ���
    �������˵������
    ����ֵ˵��  ��H320��ַ��Ŀ�ĳ���
	====================================================================
	*/
	const u32  GetH320MtIdLen(void) 
	{ return strlen( m_tAddrEntryInfo.achH320Id); }
	
	
	/*
	====================================================================
    ����        ����ȡ��ַ��ĿH323��������
    �������˵������
    ����ֵ˵��  ��H323��������
	====================================================================
	*/
	 bool IsH320Terminal( void )
		{ return  m_tAddrEntryInfo.bH320Terminal != (u8)0; }

	/*
	====================================================================
    ����        �����õ�ַ��������Ϣ�ṹ
    �������˵������ַ����Ϣ�ṹ
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryInfo( const TADDRENTRYINFO &tAddrEntryInfo );

	/*
	====================================================================
    ����        ��������Ŀ����
    �������˵��������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SetEntryName( const char* pchEntryName );

	/*
	====================================================================
    ����        �������ն˱���
    �������˵����������Ϣ
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SetMtAlias( const char* pchMtAlias );

	/*
	====================================================================
    ����        �������ն�IP��ַ
    �������˵����IP��ַ(�ַ���)
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SetMtIpAddr( const char* pchMtIpAddr );

	/*
	====================================================================
    ����        �������ն˺���
    �������˵�����ն˺���(�ַ���)
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SetMtNumber( const char* pchMtNumber );

	/*
	====================================================================
    ����        �������ն˺�������
    �������˵������������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetCallRate( u16 wCallRate ) 
		{ m_tAddrEntryInfo.wCallRate = wCallRate; } 

	/*
	====================================================================
    ����        ������H320��ַ��Ŀ
    �������˵����H320����
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SetH320MtId( const char* pchH320MtId); 
	
	/*
	====================================================================
    ����        �����øõ�ַ��ĿΪһ��H320/H323�ĵ�ַ��Ŀ
    �������˵����Ture������ΪH320���͵��նˣ�False:����ΪH323���͵��նˡ�
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetTerminalType( const bool bH320)
	{ (bH320 ? (m_tAddrEntryInfo.bH320Terminal = (u8)1) : (m_tAddrEntryInfo.bH320Terminal = (u8)0));}

	// print for test
	/*
	====================================================================
    ����        ����ӡ����ַ����Ŀ��Ϣ(���ڲ���)
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	void PrintEntry( )
	{
		OspPrintf( TRUE, FALSE, "======================\n" );
		OspPrintf( TRUE, FALSE, "Index   : %d\n", m_dwAddrEntryIndex );
        m_tAddrEntryInfo.print();
		
// 		if ( m_tAddrEntryInfo.bH320Terminal != (u8)0 )
// 		{
// 			OspPrintf( TRUE, FALSE, "H320Id : %s\n", m_tAddrEntryInfo.achH320Id);
// 			OspPrintf( TRUE, FALSE, "======================\n" );
// 			return;
// 		}
// 		
// 		if ( m_tAddrEntryInfo.achEntryName == NULL )
// 			OspPrintf( TRUE, FALSE, "Name    : 0\n" );
// 		else
// 			OspPrintf( TRUE, FALSE, "Name    : %s\n", m_tAddrEntryInfo.achEntryName );
// 
// 		if ( m_tAddrEntryInfo.achMtAlias == NULL )
// 			OspPrintf( TRUE, FALSE, "Alias	 : 0\n" );
// 		else
// 			OspPrintf( TRUE, FALSE, "Alias	 : %s\n", m_tAddrEntryInfo.achMtAlias );
// 
// 		if ( m_tAddrEntryInfo.achMtNumber == NULL )
// 			OspPrintf( TRUE, FALSE, "Number  : 0\n" );
// 		else
// 			OspPrintf( TRUE, FALSE, "Number  : %s\n", m_tAddrEntryInfo.achMtNumber );
// 
// 		OspPrintf( TRUE, FALSE, "IP      : 0x%x\n", m_tAddrEntryInfo.dwMtIpAddr );
// 		OspPrintf( TRUE, FALSE, "Rate    : 0x%x\n", m_tAddrEntryInfo.wCallRate );
        OspPrintf( TRUE, FALSE, "Byte Order is:%d\n", m_byByteOrder);

		OspPrintf( TRUE, FALSE, "======================\n" );

	}


	// compare
	/*
	====================================================================
    ����        ��С������
    �������˵����
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator < ( CAddrEntry &cAddrEntry )
	{
		int i = memcmp( &m_tAddrEntryInfo, 
						&cAddrEntry.m_tAddrEntryInfo,
						sizeof( m_tAddrEntryInfo ) );

		return ( i < 0 ) ? TRUE : FALSE; 
	}

	/*
	====================================================================
    ����        ��С�ڵ�������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator <= ( CAddrEntry &cAddrEntry )
	{
		int i = memcmp( &m_tAddrEntryInfo, 
						&cAddrEntry.m_tAddrEntryInfo,
						sizeof( m_tAddrEntryInfo ) );
		return ( i <= 0 ) ? TRUE : FALSE; 
	}

	/*
	====================================================================
    ����        ����������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator > ( CAddrEntry &cAddrEntry )
	{
		int i = memcmp( &m_tAddrEntryInfo, 
						&cAddrEntry.m_tAddrEntryInfo,
						sizeof( m_tAddrEntryInfo ) );
		return ( i <= 0 ) ? FALSE : TRUE; 
	}

	/*
	====================================================================
    ����        �����ڵ�������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator >= ( CAddrEntry &cAddrEntry )
	{
		int i = memcmp( &m_tAddrEntryInfo, 
						&cAddrEntry.m_tAddrEntryInfo,
						sizeof( m_tAddrEntryInfo ) );
		
		return ( i < 0 ) ? FALSE : TRUE; 
	}

	/*
	====================================================================
    ����        �����������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/ 
	BOOL32 operator == ( CAddrEntry &cAddrEntry )
	{
		if ( memcmp( &m_tAddrEntryInfo, &cAddrEntry.m_tAddrEntryInfo, 
										sizeof( m_tAddrEntryInfo ) ) == 0 )
			return TRUE;
		else
			return FALSE;
	}

	/*
	====================================================================
    ����        ��������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator != ( CAddrEntry &cAddrEntry )
	{
		if ( memcmp( &m_tAddrEntryInfo, &cAddrEntry.m_tAddrEntryInfo,
			                     sizeof( m_tAddrEntryInfo ) ) !=0 ) 
			return TRUE;
		else
			return FALSE;
	}

	// order convert
	/*
	====================================================================
    ����        ���ѵ�ǰ��ַ����Ŀת��Ϊ������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	void OrderHton( BOOL32 bIsNoChangeRateOrter = TRUE );

	/*
	====================================================================
    ����        ���ѵ�ǰ��ַ����Ŀת��Ϊ������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	void OrderNtoh( BOOL32 bIsNoChangeRateOrter = TRUE );

private :
	u32			m_dwAddrEntryIndex;		// ��Ŀ����
	TADDRENTRYINFO	m_tAddrEntryInfo;		// ��Ŀ�����Ϣ
	u8			m_byByteOrder;			// ��ǰ�ֽ���
	
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ������
//////////////////////////////////////////////////////////////////////////

class CAddrMultiSetEntry
{
	friend class CAddrEntry;
	friend class CAddrBook;

public :
	// constructor & destructor & copy-constructor & assign
	/*
	====================================================================
    ����        ���޲ι��캯��
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrMultiSetEntry();

	/*
	====================================================================
    ����        �����ι��캯��
    �������˵������������Ϣ�ṹ
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrMultiSetEntry( const TMULTISETENTRYINFO &tMultiSetEntryInfo );

	/*
	====================================================================
    ����        �����ι��캯��
    �������˵�������������
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrMultiSetEntry( const CAddrMultiSetEntry &cNewMultiSetEntry );

	/*
	====================================================================
    ����        ����������
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	~CAddrMultiSetEntry();

	/*
	====================================================================
    ����        ����ֵ����
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrMultiSetEntry &operator = ( const CAddrMultiSetEntry &cOtherMultiSetEntry );


	// get
	/*
	====================================================================
    ����        ����ȡ�������ֽ���
    �������˵������
    ����ֵ˵��  ����ǰ��������ֽ���
	====================================================================
	*/
	const u8 GetGroupByteOrder( void ) const
		{ return m_byByteOrder; }

	/*
	====================================================================
    ����        ����ȡ�������������������
    �������˵������
    ����ֵ˵��  ��������������
	====================================================================
	*/
	const u32 GetGroupIndex( void ) const
		{ return m_dwMultiSetEntryIndex; }

	/*
	====================================================================
    ����        ����ȡ��������Ϣ
    �������˵������Ż�������Ϣ�Ľṹ
    ����ֵ˵��  ��ptMultiSetEntryInfo -- ��������Ϣ
	====================================================================
	*/
	void GetGroupInfo( TMULTISETENTRYINFO *ptMultiSetEntryInfo );

	/*
	====================================================================
    ����        ����ȡ����������
    �������˵������Ż��������ƵĻ����� + ����������
    ����ֵ˵��  ��pchGroupName -- ����������
	====================================================================
	*/
	void GetGroupName( char* pchGroupName, u32 dwNameLen );

	/*
	====================================================================
    ����        ����ȡ������MCU��ַ
    �������˵�������IP��ַ�Ļ����� + ����������
    ����ֵ˵��  ��pchMcuIpAddr -- �ն�IP��ַ
	====================================================================
	*/
	void GetMcuIpAddr( char* pchMcuIpAddr, u32 dwIpAddrLen );

	/*
	====================================================================
    ����        ����ȡ��������
    �������˵������
    ����ֵ˵��  ����������
	====================================================================
	*/
	u16 GetConfBitRate( void ) 
		{ return m_wConfBitRate; }

    /*
	====================================================================
    ����        ����ȡ�û����ݳ���
    �������˵������
    ����ֵ˵��  ���û����ݳ���
	====================================================================
	*/
    u32 GetUserDataLen();

    /*
	====================================================================
    ����        ����ȡ�û�����
    �������˵������
    ����ֵ˵��  ���ɹ�TRUE
	====================================================================
	*/
	BOOL32 GetUserData(u8* pbyBuf, u32 dwBufLen);

	/*
	====================================================================
    ����        ����ȡ���鿪������
    �������˵������
    ����ֵ˵��  ����������(0:������, 1: ����)
	====================================================================
	*/
	u8 GetConfOpen( void ) 
		{ return m_byOpen; }

	/*
	====================================================================
    ����        ����ȡ���������Ƴ���
    �������˵������
    ����ֵ˵��  �����Ƴ���
	====================================================================
	*/
	u32 GetGroupNameLen( void ) 
		{ return strlen( m_achGroupName ); }

	// get mttable
	/*
	====================================================================
    ����        ����ȡ�������ն��б�
    �������˵������
    ����ֵ˵��  ���ն��б�ͷָ��
	====================================================================
	*/
	u32* GetEntryTable( void ) 
			{ return m_adwConfEntryTable; }

	/*
	====================================================================
    ����        ����ȡ�������ն˸���(�ն��б���)
    �������˵������
    ����ֵ˵��  ���б���
	====================================================================
	*/
	const u8 GetEntryCount( void );
	
	// Set
	/*
	====================================================================
    ����        �����û�������Ϣ
    �������˵������������Ϣ�ṹ
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetGroupInfo( const TMULTISETENTRYINFO &tMultiSetEntryInfo );

	/*
	====================================================================
    ����        �����û�������
    �������˵��������������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SetGroupName( const char* pchGroupName );
	/*
	====================================================================
    ����        ������MCU IP��ַ
    �������˵����IP��ַ
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SetMcuIpAddr( const char* pchIpAddr );


	/*
	====================================================================
    ����        �����û�������
    �������˵������������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetConfBitRate( const u16 wConfBitRate ) 
		{ m_wConfBitRate = wConfBitRate; }

	/*
	====================================================================
    ����        �����û���Ŀ�������
    �������˵������������(0: ������,1: ����)
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetConfOpen( const u8 byOpen )
		{ m_byOpen = byOpen; }

    /*
	====================================================================
    ����        �������û�����
    �������˵������
    ����ֵ˵��  ����������
	====================================================================
	*/
	BOOL32 SetUserData(u8* pbyBuf, u32 dwBufLen);

	/*
	====================================================================
    ����        �����������ն��б��м����ն�
    �������˵�����ն�����
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 AddEntryToMultiSetList( const u32 dwEntryIndex );


	// compare
	/*
	====================================================================
    ����        ��С������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator < ( CAddrMultiSetEntry &cAddrMultiSetEntry )
	{
        int i = memcmp(m_achGroupName, 
                       cAddrMultiSetEntry.m_achGroupName, 
                       sizeof( m_achGroupName ));

		return ( i < 0 ) ? TRUE : FALSE; 
	}

	/*
	====================================================================
    ����        ��С�ڵ�������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator <= ( CAddrMultiSetEntry &cAddrMultiSetEntry )
	{
        int i = memcmp(m_achGroupName, 
                       cAddrMultiSetEntry.m_achGroupName, 
                       sizeof( m_achGroupName ));
        
        return ( i <= 0 ) ? TRUE : FALSE; 
	}

	/*
	====================================================================
    ����        ����������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator > ( CAddrMultiSetEntry &cAddrMultiSetEntry )
	{
        int i = memcmp(m_achGroupName, 
                       cAddrMultiSetEntry.m_achGroupName, 
                       sizeof( m_achGroupName ));
        
        return ( i > 0 ) ? TRUE : FALSE; 
    }
    
	/*
	====================================================================
    ����        �����ڵ���
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator >= ( CAddrMultiSetEntry &cAddrMultiSetEntry )
	{
        int i = memcmp(m_achGroupName, 
            cAddrMultiSetEntry.m_achGroupName, 
            sizeof(m_achGroupName));
        
        return ( i >= 0 ) ? TRUE : FALSE; 
    }
    
	/*
	====================================================================
    ����        �����������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/ 
	BOOL32 operator == ( CAddrMultiSetEntry &cAddrMultiSetEntry )
	{
        if ( memcmp(m_achGroupName, 
					cAddrMultiSetEntry.m_achGroupName, 
					sizeof(m_achGroupName) ) == 0 )
			return TRUE;
		else
			return FALSE;
	}

	/*
	====================================================================
    ����        ������������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	BOOL32 operator != ( CAddrMultiSetEntry &cAddrMultiSetEntry )
	{
        if (memcmp(m_achGroupName, 
                   cAddrMultiSetEntry.m_achGroupName, 
				   sizeof(m_achGroupName)) != 0 )
			return TRUE;
		else
			return FALSE;
	}

	/*
	====================================================================
    ����        ����ӡ����������Ϣ(���ڲ���)
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	void PrintGroup( void )
	{
		OspPrintf( TRUE, FALSE, "index  : %d\n", m_dwMultiSetEntryIndex );

		if ( m_achGroupName != NULL )
			OspPrintf( TRUE, FALSE, "Name   : %s\n", m_achGroupName );
		else
			OspPrintf( TRUE, FALSE, "Name   : \n" );

		OspPrintf( TRUE, FALSE, "McuIp  : 0x%x\n", m_dwMcuIpAddr );
		OspPrintf( TRUE, FALSE, "Rate   : %d\n", m_wConfBitRate );
		OspPrintf( TRUE, FALSE, "Open   : %d\n", m_byOpen );
        OspPrintf( TRUE, FALSE, "Userlen: %d\n", m_dwUserDataLen);
		OspPrintf( TRUE, FALSE, "Entry Table, size = %d\n", GetEntryCount() );
		for ( int i = 0; i < GetEntryCount(); i++ )
			OspPrintf(TRUE, FALSE,  "%d ,", m_adwConfEntryTable[ i ] );
		OspPrintf( TRUE, FALSE, "\n" );
	}

	// order convert
	/*
	====================================================================
    ����        ���ѵ�ǰ������ת��Ϊ������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	void OrderHton( void );

	/*
	====================================================================
    ����        ���ѵ�ǰ������ת��Ϊ������
    �������˵������
    ����ֵ˵��  ���ȽϽ��
	====================================================================
	*/
	void OrderNtoh( void );

private :
	u32					m_dwMultiSetEntryIndex;						// ����������
	//TMULTISETENTRYINFO	m_tMultiSetEntryInfo;						// ��������Ϣ
    //����Ϣ
    char m_achGroupName[ MAX_NAME_LEN + 1 ];	// ����
    u32	m_dwMcuIpAddr;						// MCU��ַ(������)
    u16	m_wConfBitRate;						// ��������
    u8	m_byOpen;						    // ������(0:����	1:�ǿ���)

	u32	m_adwConfEntryTable[ MAXNUM_ENTRY_TABLE ];	// �ն��б�
	u8	m_byByteOrder;								// ��ǰ�ֽ���

    u32 m_dwUserDataLen;                            // �û����ݳ���
    u8  m_byUserData[MAX_GROUP_USERDATA_LEN];                          // �û�����256�ֽ�
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct tagAddrEntry
{
private :
	u32 dwEntryIndex;				// ��Ŀ����
	TADDRENTRYINFO tAddrEntryInfo;	// ��Ŀ��Ϣ

public :
	tagAddrEntry() : dwEntryIndex( 0xFF )
	{
		memset( &tAddrEntryInfo, 0, sizeof( tAddrEntryInfo ) );
	}
    void print()
    {
        OspPrintf( TRUE, FALSE, "======================\n" );
        OspPrintf( TRUE, FALSE, "Index   : %d\n", dwEntryIndex );
        
        tAddrEntryInfo.print();
            
        OspPrintf( TRUE, FALSE, "======================\n" );
    }

    /*
    ====================================================================
    ����        ����ȡ��Ŀ����
    �������˵������
    ����ֵ˵��  ����Ŀ����
    ====================================================================
    */	
    u32 GetEntryIndex()
    { return ntohl( dwEntryIndex ); }
    
    /*
    ====================================================================
    ����        ��������Ŀ����
    �������˵������
    ����ֵ˵��  ����
    ====================================================================
    */
    void SetEntryIndex( u32 dwIndex )
    { dwEntryIndex = htonl( dwIndex ); }

	/*
	====================================================================
    ����        ����ȡ��Ŀ��Ϣ
    �������˵������
    ����ֵ˵��  ����Ŀ��Ϣ�ṹ
	====================================================================
	*/
	TADDRENTRYINFO GetEntryInfo()
	{
		TADDRENTRYINFO tTempAddrEntryInfo;
		memset( &tTempAddrEntryInfo, 0, sizeof( tTempAddrEntryInfo ) );
		memcpy( &tTempAddrEntryInfo, &tAddrEntryInfo, sizeof( tTempAddrEntryInfo ) );
		tTempAddrEntryInfo.wCallRate = ntohs( tTempAddrEntryInfo.wCallRate );

		return tTempAddrEntryInfo;
	}

	/*
	====================================================================
    ����        ��������Ŀ��Ϣ
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryInfo( TADDRENTRYINFO *ptAddrEntryInfo )
	{
		if ( ptAddrEntryInfo == NULL )
			return;

		memset( &tAddrEntryInfo, 0, sizeof( tAddrEntryInfo ) );
		memcpy( &tAddrEntryInfo, ptAddrEntryInfo, sizeof( tAddrEntryInfo ) );
		tAddrEntryInfo.wCallRate = htons( tAddrEntryInfo.wCallRate );
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
typedef tagAddrEntry TADDRENTRY;
typedef TADDRENTRY *PTADDRENTRY;


struct tagAddrMultiSetEntry
{
private :
	u32 dwEntryIndex;								// ��Ŀ����
	TMULTISETENTRYINFO tAddrMultiSetEntryInfo;		// ��Ŀ��Ϣ
	u32 dwListEntryNum;							// ����ն˸���
	u32 adwListEntryIndex[ MAXNUM_ENTRY_TABLE ];	// ����ն�����

public :
	tagAddrMultiSetEntry():dwEntryIndex(0xFF),dwListEntryNum(0xFF)
	{
		memset( &tAddrMultiSetEntryInfo, 0, sizeof( tAddrMultiSetEntryInfo ) );
		memset( adwListEntryIndex, 0xFF, MAXNUM_ENTRY_TABLE * sizeof( u32 ) );
	}
	/*
	====================================================================
    ����        ����ȡ��Ŀ����
    �������˵������
    ����ֵ˵��  ����Ŀ��Ŀ����
	====================================================================
	*/
	u32 GetEntryIndex()
		{ return ntohl( dwEntryIndex ); }

	/*
	====================================================================
    ����        ��������Ŀ����
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryIndex( u32 dwIndex )
		{ dwEntryIndex = htonl( dwIndex ); }

	/*
	====================================================================
    ����        ����ȡ��Ŀ��Ϣ
    �������˵������
    ����ֵ˵��  ����Ŀ��Ϣ�ṹ
	====================================================================
	*/
	TMULTISETENTRYINFO GetEntryInfo()
	{
		TMULTISETENTRYINFO tTempAddrMultiSetEntryInfo;
		memset( &tTempAddrMultiSetEntryInfo, 0, sizeof( tTempAddrMultiSetEntryInfo ) );
		memcpy( &tTempAddrMultiSetEntryInfo, &tAddrMultiSetEntryInfo, 
					sizeof( tTempAddrMultiSetEntryInfo ) );
		tTempAddrMultiSetEntryInfo.wConfBitRate = ntohs( tTempAddrMultiSetEntryInfo.wConfBitRate );
        tTempAddrMultiSetEntryInfo.dwUserDataLen = ntohl( tTempAddrMultiSetEntryInfo.dwUserDataLen );

		return tTempAddrMultiSetEntryInfo;
	}

	/*
	====================================================================
    ����        ��������Ŀ��Ϣ
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryInfo( TMULTISETENTRYINFO *ptAddrMultiSetEntryInfo )
	{
		if ( ptAddrMultiSetEntryInfo == NULL )
			return;

		memset( &tAddrMultiSetEntryInfo, 0, sizeof( tAddrMultiSetEntryInfo ) );
		memcpy( &tAddrMultiSetEntryInfo, ptAddrMultiSetEntryInfo, sizeof( tAddrMultiSetEntryInfo ) );
		tAddrMultiSetEntryInfo.wConfBitRate = htons( tAddrMultiSetEntryInfo.wConfBitRate );
        tAddrMultiSetEntryInfo.dwUserDataLen = htonl( tAddrMultiSetEntryInfo.dwUserDataLen );
	}

	/*
	====================================================================
    ����        ����ȡ����б��ն˸���
    �������˵������
    ����ֵ˵��  ���ն˸���
	====================================================================
	*/
	u32 GetListEntryNum()
		{ return ntohl( dwListEntryNum ); }

	/*
	====================================================================
    ����        ����������б��ն˸���
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetListEntryNum( u32 dwNum )
	{ 
        //guzh 2008/06/06
        if ( dwNum > MAXNUM_ENTRY_TABLE )
			dwNum = MAXNUM_ENTRY_TABLE;

        dwListEntryNum = htonl( dwNum ); 
    }

	/*
	====================================================================
    ����        ����ȡ����б�
    �������˵�����������б�Ļ����� + ����������
    ����ֵ˵��  ����
	====================================================================
	*/
	void GetListEntryIndex( u32* padwListEntryIndex, u32 dwNum )
	{
		if ( dwNum > MAXNUM_ENTRY_TABLE )
			dwNum = MAXNUM_ENTRY_TABLE;

		for ( int i = 0; i < (int)dwNum; i++ )
			padwListEntryIndex[ i ] = ntohl( adwListEntryIndex[ i ] );
	}

	/*
	====================================================================
    ����        ����������б�
    �������˵�����������б�Ļ����� + ����ն˸���
    ����ֵ˵��  ����
	====================================================================
	*/	
	void SetListEntryIndex( u32* padwListEntryIndex, u32 dwNum )
	{
		int i;
        for ( i = 0; i < MAXNUM_ENTRY_TABLE; i++ )
			adwListEntryIndex[ i ] = INVALID_INDEX;

		if ( dwNum > MAXNUM_ENTRY_TABLE )
			dwNum = MAXNUM_ENTRY_TABLE;

		for ( i = 0; i < (int)dwNum; i++ )
		{
			adwListEntryIndex[ i ] = htonl( *( padwListEntryIndex + i ) );
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
typedef tagAddrMultiSetEntry TADDRMULTISETENTRY;
typedef TADDRMULTISETENTRY *PTADDRMULTISETENTRY;

// ��Ŀ���� + ��Ŀ���� + �������� + ��Ŀ���� + ��Ϣ���� + ��Ϣ��
const u16 ADDRBOOK_MSGHEAD_LEN					= 12;
const u16 ADDRBOOK_MSGHEAD_ENTRYTYPE_OFFSET	= 0;
const u16 ADDRBOOK_MSGHEAD_ENTRYTYPE_LEN		= 1;
const u16 ADDRBOOK_MSGHEAD_NUM_OFFSET			= ADDRBOOK_MSGHEAD_ENTRYTYPE_OFFSET +  ADDRBOOK_MSGHEAD_ENTRYTYPE_LEN;
const u16 ADDRBOOK_MSGHEAD_NUM_LEN				= 4;
const u16 ADDRBOOK_MSGHEAD_OPTTYPE_OFFSET		= ADDRBOOK_MSGHEAD_NUM_OFFSET + ADDRBOOK_MSGHEAD_NUM_LEN;
const u16 ADDRBOOK_MSGHEAD_OPTTYPE_LEN			= 1;
const u16 ADDRBOOK_MSGHEAD_ENTRYINDEX_OFFSET	= ADDRBOOK_MSGHEAD_OPTTYPE_OFFSET + ADDRBOOK_MSGHEAD_OPTTYPE_LEN;
const u16 ADDRBOOK_MSGHEAD_ENTRYINDEX_LEN		= 4;
const u16 ADDRBOOK_MSGHEAD_MSGLEN_OFFSET		= ADDRBOOK_MSGHEAD_ENTRYINDEX_OFFSET + ADDRBOOK_MSGHEAD_ENTRYINDEX_LEN;
const u16 ADDRBOOK_MSGHEAD_MSGLEN_LEN			= 2;
const u16 ADDRBOOK_MSGBODY_OFFSET				= ADDRBOOK_MSGHEAD_LEN;

class CAddrBookMsg
{
protected :
	u8	m_abyBuffer[ 0x1800 ];			// buff
	
private :

public :
	CAddrBookMsg()
	{
		memset( m_abyBuffer, 0, sizeof( m_abyBuffer ) );
		u16 wLen = ADDRBOOK_MSGHEAD_LEN;
		wLen = htons( wLen );
		memcpy( m_abyBuffer + ADDRBOOK_MSGHEAD_MSGLEN_OFFSET, &wLen,
					ADDRBOOK_MSGHEAD_MSGLEN_LEN );
	}
	
	// get & set
	/*
	====================================================================
    ����        ����ȡ��Ŀ�����ֶ�
    �������˵������
    ����ֵ˵��  ����Ŀ����
	====================================================================
	*/
	u8 GetEntryType() const 
	{ 	
		return ( *( u8* )( m_abyBuffer + ADDRBOOK_MSGHEAD_ENTRYTYPE_OFFSET ) ); 
	}

	/*
	====================================================================
    ����        ��������Ŀ�����ֶ�
    �������˵��: ��Ŀ����
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryType( u8 byEntryType )
	{
		*( m_abyBuffer + ADDRBOOK_MSGHEAD_ENTRYTYPE_OFFSET ) = byEntryType;
	}
	

	/*
	====================================================================
    ����        ����ȡ��Ŀ�����ֶ�
    �������˵������
    ����ֵ˵��  ����Ŀ����
	====================================================================
	*/
	u32 GetEntryNum() const
	{ 
		u32 dwEntryNum = 0;
		
		memcpy( &dwEntryNum, m_abyBuffer + ADDRBOOK_MSGHEAD_NUM_OFFSET, 
					ADDRBOOK_MSGHEAD_NUM_LEN );
		return ntohl( dwEntryNum ); 
	}

	/*
	====================================================================
    ����        ��������Ŀ�����ֶ�
    �������˵������Ŀ����
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryNum( u32 dwEntryNum )
	{ 
		dwEntryNum = htonl( dwEntryNum ); 
		memcpy( m_abyBuffer + ADDRBOOK_MSGHEAD_NUM_OFFSET, &dwEntryNum,
				 ADDRBOOK_MSGHEAD_NUM_LEN );
	}

	/*
	====================================================================
    ����        ����ȡ��Ŀ���������ֶ�
    �������˵������
    ����ֵ˵��  ����Ŀ��������
	====================================================================
	*/
	u8 GetEntryOptType() const
	{ 	
		return ( *( u8* )( m_abyBuffer + ADDRBOOK_MSGHEAD_OPTTYPE_OFFSET ) ); 
	}

	/*
	====================================================================
    ����        ��������Ŀ���������ֶ�
    �������˵������������(����/ɾ��)
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryOptType( u8 byOptType )
	{
		*( m_abyBuffer + ADDRBOOK_MSGHEAD_OPTTYPE_OFFSET ) = byOptType;
	}

	/*
	====================================================================
    ����        ����ȡ��Ŀ�����ֶ�
    �������˵������
    ����ֵ˵��  ����Ŀ����
	====================================================================
	*/
	u32 GetEntryIndex() const
	{ 
		u32 dwEntryIndex = 0;
		
		memcpy( &dwEntryIndex, m_abyBuffer + ADDRBOOK_MSGHEAD_ENTRYINDEX_OFFSET, 
					ADDRBOOK_MSGHEAD_ENTRYINDEX_LEN );
		return ntohl( dwEntryIndex ); 
	}

	/*
	====================================================================
    ����        ��������Ŀ�����ֶ�
    �������˵������Ŀ����
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetEntryIndex( u32 dwIndex )
	{ 
		dwIndex = htonl( dwIndex ); 
		memcpy( m_abyBuffer + ADDRBOOK_MSGHEAD_ENTRYINDEX_OFFSET, &dwIndex,
				 ADDRBOOK_MSGHEAD_ENTRYINDEX_LEN );
	}

	/*
	====================================================================
    ����        ����ȡ����ͨ����Ϣ�ĳ���
    �������˵������
    ����ֵ˵��  ����Ϣ����
	====================================================================
	*/
	u16 GetMsgLen() const 
	{
		u16 wMsgLen = 0;

		memcpy( &wMsgLen, m_abyBuffer + ADDRBOOK_MSGHEAD_MSGLEN_OFFSET,
				ADDRBOOK_MSGHEAD_MSGLEN_LEN	);
		
		return ntohs( wMsgLen );
	}

    /*
	====================================================================
    ����        ����ȡ��Ϣ�峤��
    �������˵������
    ����ֵ˵��  ����Ϣ�峤��
	====================================================================
	*/
    u16 GetMsgBodyLen() const
    {        
		return GetMsgLen() - ADDRBOOK_MSGHEAD_LEN;
    }

	/*
	====================================================================
    ����        ������ͨ����Ϣ��
    �������˵������Ϣ�建���� + ����������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetMsgBody( const u8 *pbyMsgBody = NULL, u16 wLen = 0 )
	{
		wLen = (u16)min( wLen, sizeof( m_abyBuffer ) - ADDRBOOK_MSGHEAD_LEN );
		memcpy( m_abyBuffer + ADDRBOOK_MSGBODY_OFFSET, pbyMsgBody, wLen );

		wLen = htons( wLen + ADDRBOOK_MSGHEAD_LEN );
		memcpy( m_abyBuffer + ADDRBOOK_MSGHEAD_MSGLEN_OFFSET, &wLen,
					ADDRBOOK_MSGHEAD_MSGLEN_LEN );
	}

	/*
	====================================================================
    ����        ����ȡͨ����Ϣ��
    �������˵������
    ����ֵ˵��  ��ͨ����Ϣ��ͷָ��
	====================================================================
	*/
	u8 *GetMsgBody( void ) const
	{
		return ( ( u8* )( m_abyBuffer + ADDRBOOK_MSGBODY_OFFSET ) );
	}

	/*
	====================================================================
    ����        ����ȡ����ͨ����Ϣ������
    �������˵������
    ����ֵ˵��  ��������ͷָ��
	====================================================================
	*/
	u8 *GetAddrBookMsg( void ) const
	{
		return ( ( u8* )m_abyBuffer );
	}

	/*
	====================================================================
    ����        ����������ͨ����Ϣ�Ļ�����
    �������˵���������� + ����������
    ����ֵ˵��  ����
	====================================================================
	*/
	void SetAddrBookMsg( const u8 *pbyMsg, u16 wMsgLen )
	{
		if( wMsgLen < ADDRBOOK_MSGHEAD_LEN )
		{
//			OspPrintf( TRUE, FALSE, "CAddrBookMsg: Exception -- invalid addrbook message!\n" );
			return;
		}

		wMsgLen = min( wMsgLen, sizeof( m_abyBuffer ) );
		memcpy( m_abyBuffer, pbyMsg, wMsgLen );
// 		memcpy( m_abyBuffer + ADDRBOOK_MSGHEAD_MSGLEN_OFFSET, &wMsgLen,
// 					ADDRBOOK_MSGHEAD_MSGLEN_LEN );
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// ��ַ��
//////////////////////////////////////////////////////////////////////////////////////
class CAddrBook
{	
public :
/*
	enum EntryType
	{
		ADDR_ENTRY,
		MULTISET_ENTRY
	};
*/


	// constructor,destructor,copy-constructor, assign
	/*
	====================================================================
    ����        �����ι��캯��
    �������˵��������ַ����Ŀ���� + �����������
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrBook( u32 dwAddrEntrySize = MAX_ADDRENTRY,
			   u32 dwAddrGroupSize = MAX_ADDRGROUP );

	/*
	====================================================================
    ����        �����ι��캯��
    �������˵������ַ������
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrBook( const CAddrBook &cNewAddrBook );

	/*
	====================================================================
    ����        ����ֵ����
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	CAddrBook &operator = ( const CAddrBook &cOtherAddrBook );

	/*
	====================================================================
    ����        ����������
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	~CAddrBook();

	// ��ȡ��ַ���������
	//////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ����ȡ���һ�δ�����
    �������˵������
    ����ֵ˵��  ��������
	====================================================================
	*/
	const u32 GetLastError( void )
			{	return m_dwLastError; }

	/*
	====================================================================
    ����        ����ȡ��ַ����Ŀ��������
    �������˵������
    ����ֵ˵��  ����Ŀ������
	====================================================================
	*/
	const u32 GetAddrEntryTotalSize( void )
			{	return m_cAddrBook.GetTotalSize(); }

	/*
	====================================================================
    ����        ����ȡ��ǰʹ�õĵ�ַ����Ŀ����
    �������˵������
    ����ֵ˵��  ��ʹ�õĵ�ַ����Ŀ����
	====================================================================
	*/
	const u32 GetAddrEntryUsedSize( void )
			{ return m_cAddrBook.GetUsedSize(); }

	/*
	====================================================================
    ����        ����ȡ��ַ��������������
    �������˵������
    ����ֵ˵��  ��������������
	====================================================================
	*/
	const u32 GetAddrGroupTotalSize( void )
			{ return m_cAddrMultiSetEntry.GetTotalSize(); }

	/*
	====================================================================
    ����        ����ȡ��ǰʹ�õĵ�ַ�����������
    �������˵������
    ����ֵ˵��  ��ʹ�õĻ��������
	====================================================================
	*/
	const u32 GetAddrGroupUsedSize( void )
			{ return m_cAddrMultiSetEntry.GetUsedSize(); }


	// �����ȡ��ַ����Ŀ���ַ��������
	/////////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ����ȡ������е�һ����ַ��Ŀ(�����)
    �������˵������ŵ�ַ����Ŀ�Ļ�����
    ����ֵ˵��  ��pcAddrEntry -- ��һ����ַ����Ŀ
				  �ɹ� -- ������Ŀ����
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 GetFirstAddrEntry( CAddrEntry* pcAddrEntry );

	/*
	====================================================================
    ����        ����ȡ������е�һ��������(�����)
    �������˵������ŵ�ַ��������Ļ�����
    ����ֵ˵��  ��pcAddrMultiSetEntry -- ��һ��������
				  �ɹ� -- ���ػ���������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 GetFirstAddrMultiSetEntry( CAddrMultiSetEntry* pcAddrMultiSetEntry );

	/*
	====================================================================
    ����        ����ȡ������е�ǰ��Ŀ��̵Ķ����ַ����Ŀ(�����)
    �������˵������ǰ��Ŀ���� + ��ź�̵�ַ��Ŀ�б����� + �б���󳤶� 
    ����ֵ˵��  ��pcEntryTable -- ʵ�ʻ�ȡ����Ŀ�б�
				  �ɹ� -- ����ʵ�ʻ�ȡ����Ŀ����
				  ʧ�� -- ����0(�������Ϸ���ʵ����Ŀû�е����)
	====================================================================
	*/
	u32 GetNextAddrEntry( u32 dwCurEntryIndex, CAddrEntry* pcEntryTable, 
							u32 dwEntryNum = 1 );

	/*
	====================================================================
    ����        ����ȡ������е�ǰ�������̵Ķ��������(�����)
    �������˵������ǰ���������� + ��ź�̻������б����� + �б���󳤶�
    ����ֵ˵��  ��pcGroupTable -- ʵ�ʻ�ȡ�Ļ������б�
				  �ɹ� -- ����ʵ�ʻ�ȡ�Ļ��������
				  ʧ�� -- ����0(�������Ϸ���ʵ����Ŀû�е����)
	====================================================================
	*/
	u32 GetNextAddrMultiSetEntry( u32 dwCurGroupIndex, CAddrMultiSetEntry* pcGroupTable,
									u32 dwGroupNum = 1 );
	
	bool IsAddrEntryValid( u32 dwAddrEntryIndex);
	bool IsAddrMultiSetEntryValid( u32 dwAddrMultiSetEntryIndex);
		
	// ������ȫƥ�����Ŀ�������
	//////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ��������ȫƥ�����Ŀ
    �������˵������ַ����Ŀ��Ϣ(����������Ϣ)
    ����ֵ˵��  ��u32  ��Ŀ����
				  �ɹ� -- ���ز�����Ŀ������ֵ
				  ʧ�� -- INVALID_INDEX
	====================================================================
	*/
	u32 IsAddrEntryExist( TADDRENTRYINFO tAddrEntryInfo );
	/*
	====================================================================
    ����        ��	������ȫƥ��Ļ�����
    �������˵����	��ַ����������Ϣ(����������Ϣ)
    ����ֵ˵��  ��	u32  ����������
					�ɹ� -- ���ز��һ����������ֵ
					ʧ�� -- INVALID_INDEX
	====================================================================
	*/
	u32 IsAddrMultiSetEntryExist( TMULTISETENTRYINFO tMultiSetEntryInfo );
	
	// ��ȡָ����ַ����Ŀ��������
	//////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ��ͨ��������ȡָ���ĵ�ַ����Ŀ
    �������˵������ŵ�ַ����Ŀ�Ļ����� + ����(Ĭ��0)
    ����ֵ˵��  ��pcAddrEntry -- ָ���ĵ�ַ����Ŀ
				  �ɹ� -- ������Ŀ����
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32  GetAddrEntry( CAddrEntry *pcAddrEntry, u32 dwEntryIndex = 0 );

	/*
	====================================================================
    ����        ��ͨ��������ȡָ���ĵ�ַ��������
    �������˵������ŵ�ַ��������Ļ����� + ����( Ĭ��0 )
    ����ֵ˵��  ��pcMultiSetEntry -- ָ���Ļ�����
				  �ɹ� -- ���ػ���������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32  GetAddrMultiSetEntry( CAddrMultiSetEntry* pcMultiSetEntry, 
									u32 dwGroupIndex = 0 );



	// �ڵ�ַ���в������ƥ������е�ַ����Ŀ�������
	//////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ��������Ŀ���Ʋ�������ƥ����Ŀ
    �������˵������Ŀ���� + ���ƥ����Ŀ�б�Ļ����� + �б���󳤶�
    ����ֵ˵��  ��pcEntryTable -- ʵ����Ŀ�б�
				  �ɹ� -- ����ʵ��ƥ�����Ŀ����
				  ʧ�� -- ����0(�������Ϸ���ʵ����Ŀû�е����)
	====================================================================
	*/
	u32 GetAddrEntryByName( char* pchEntryName, CAddrEntry* pcEntryTable, 
						u32 dwEntryNum = 1 );

	/*
	====================================================================
    ����        �������ն�H323������������ƥ�����Ŀ
    �������˵�����ն�H323���� + ���ƥ����Ŀ�б�Ļ����� + �б���󳤶�
    ����ֵ˵��  ��pcEntryTable -- ʵ����Ŀ�б�
				  �ɹ� -- ����ʵ��ƥ�����Ŀ����
				  ʧ�� -- ����0(�������Ϸ���ʵ����Ŀû�е����)
	====================================================================
	*/
	u32 GetAddrEntryByAlias( char* pchMtAlias, CAddrEntry* pcEntryTable,
						u32 dwEntryNum = 1 );

	/*
	====================================================================
    ����        �������ն˵�ַ��������ƥ�����Ŀ
    �������˵�����ն˵�ַ + ���ƥ����Ŀ�б�Ļ����� + �б���󳤶�
    ����ֵ˵��  ��pcEntryTable -- ʵ����Ŀ�б�
				  �ɹ� -- ����ʵ��ƥ�����Ŀ����
				  ʧ�� -- ����0(�������Ϸ���ʵ����Ŀû�е����)
	====================================================================
	*/
	u32 GetAddrEntryByAddr( char* pchIpAddr, CAddrEntry* pcEntryTable,
						u32 dwEntryNum = 1 );

	/*
	====================================================================
    ����        �������ն˺����������ƥ�����Ŀ
    �������˵�����ն˺��� + ���ƥ����Ŀ�б�Ļ����� + �б����󳤶�
    ����ֵ˵��  ��pcEntryTable -- ʵ����Ŀ�б�
				  �ɹ� -- ����ʵ��ƥ�����Ŀ����
				  ʧ�� -- ����0(�������Ϸ���ʵ����Ŀû�е����)
	====================================================================
	*/
	u32 GetAddrEntryByNumber( char* pchMtNumber, CAddrEntry* pcEntryTable,
						u32 dwEntryNum = 1 );

	/*
	====================================================================
    ����        �����ݻ��������Ʋ�������ƥ�����Ŀ
    �������˵�������������� + ���ƥ��������б�Ļ����� + �б���󳤶�
    ����ֵ˵��  ��pcGroupTable -- ʵ�ʻ������б�
				  �ɹ� -- ����ʵ��ƥ��Ļ��������
				  ʧ�� -- ����0(�������Ϸ���ʵ����Ŀû�е����)
	====================================================================
	*/
	u32 GetAddrMultiSetEntry( char* pchGroupName, CAddrMultiSetEntry* pcGroupTable,
								u32 dwGroupNum = 1 );


	// ���ַ���м�����Ŀ�������
	//////////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        �����ַ���м���һ����Ŀ
    �������˵������Ŀ���� + �ն˱��� + �ն˵�ַ + �ն˺��� + �ն�����
    ����ֵ˵��  ���ɹ� -- ���ظ���Ŀ������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrEntry( const char* pchEntryName,
						const char* pchMtAlias = NULL,
						const char* pchMtIpAddr = NULL,
						const char* pchMtNumber = NULL,
						const u16  wCallRate = 0 );

	/*
	====================================================================
    ����        �����ַ���м���һ��������
    �������˵�������������� + �������� + ���鿪������
    ����ֵ˵��  ���ɹ� -- ���ظû����������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrMultiSetEntry( const char* pchGroupName,
								const char* pchMcuIpAddr = NULL,
								const u16 wBitRate = 0,
								const u8 byOpen = 0 );

	/*
	====================================================================
    ����        �����ַ���м���һ����Ŀ
    �������˵������Ŀ����
    ����ֵ˵��  ���ɹ� -- ���ؼ�����Ŀ������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrEntry( /*const*/ CAddrEntry &cAddrEntry );

    /*
	====================================================================
    ����        �����ӵ�ַ���ļ��ж�ȡ����Ŀ�����ַ��������
    �������˵������Ŀ����
    ����ֵ˵��  ���ɹ� -- ���ؼ�����Ŀ������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
    u32 AddAddrEntryFromFile( /*const*/ CAddrEntry &cAddrEntry );

	/*
	====================================================================
    ����        �����ַ���м���һ��������
    �������˵�������������
    ����ֵ˵��  ���ɹ� -- ���ؼ�������������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrMultiSetEntry( /*const*/ CAddrMultiSetEntry &cAddrMultiSetEntry );
	
	/*
	====================================================================
    ����        �����ַ���м���һ����Ŀ
    �������˵������Ŀ��Ϣ
    ����ֵ˵��  ���ɹ� -- ���ؼ�����Ŀ������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrEntry( const TADDRENTRYINFO &tAddrEntryInfo, 
						u32 dwIndex = INVALID_INDEX );

	/*
	====================================================================
    ����        �����ַ���м���һ��������
    �������˵������������Ϣ
    ����ֵ˵��  ���ɹ� -- ���ؼ�������������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrMultiSetEntry( const TMULTISETENTRYINFO &tMultiSetEntryInfo, 
								u32 dwIndex = INVALID_INDEX );

	// ��������м����ַ����Ŀ
	/////////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ����ָ���Ļ������м���һ���Ѵ��ڵ���Ŀ
    �������˵�������������� + ��Ŀ����
    ����ֵ˵��  ���ɹ� -- ���ؼ�����Ŀ������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrEntry( u32 dwGroupIndex, u32 dwEntryIndex );

	/*
	====================================================================
    ����        ����ָ���Ļ������м���һ����Ŀ
    �������˵�������������� + ��Ŀʵ��
    ����ֵ˵��  ���ɹ� -- ���ؼ�����Ŀ������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrEntry( u32 dwGroupIndex, /*const*/ CAddrEntry &cAddrEntry );

	/*
	====================================================================
    ����        ����ָ���Ļ������м���һ����Ŀ
    �������˵�������������� + ��Ŀ��Ϣ
    ����ֵ˵��  ���ɹ� -- ���ؼ�����Ŀ������
				  ʧ�� -- ���طǷ�����INVALID_INDEX
	====================================================================
	*/
	u32 AddAddrEntry( u32 dwGroupIndex, const TADDRENTRYINFO &tAddrEntryInfo );


	// �ӵ�ַ����ɾ����Ŀ�������
	//////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        �����������ַ��
    �������˵������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 ClearAddrBook( void );

	/*
	====================================================================
    ����        ���ӵ�ַ����ɾ��ָ���ĵ�ַ����Ŀ
    �������˵������Ŀ����
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 DelAddrEntry( u32 dwEntryIndex, u32* pdwGroupIndexTable = NULL, u16* dwGroupNum = NULL );

	/*
	====================================================================
    ����        ���ӵ�ַ����ɾ��ָ���Ļ�����
    �������˵��������������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 DelAddrMultiSetEntry( u32 dwGroupIndex );

	// �ӻ�������ɾ����Ŀ
	////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ���ӻ�������ɾ��ָ������Ŀ(�����ӵ�ַ����ɾ��)
    �������˵�������������� + ��Ŀ����
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 DelAddrEntry( u32 dwGroupIndex, u32 dwEntryIndex );

	// �޸ĵ�ַ����Ŀ�������
	////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        ���޸�ָ���ĵ�ַ����Ŀ
    �������˵������Ŀʵ��
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 ModifyAddrEntry( const CAddrEntry &cAddrEntry );

	/*
	====================================================================
    ����        ���޸�ָ���Ļ�����
    �������˵����������ʵ��
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 ModifyAddrGroup( const CAddrMultiSetEntry &cAddrMultiSetEntry );

	/*
	====================================================================
    ����        ���޸�ָ���ĵ�ַ����Ŀ
    �������˵������Ŀ���� + ��Ŀ��Ϣ
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 ModifyAddrEntry( u32 dwEntryIndex, const TADDRENTRYINFO &tAddrEntryInfo );

	/*
	====================================================================
    ����        ���޸�ָ���Ļ��������Ϣ,���޸��ն��б�
    �������˵�������������� + ��������Ϣ
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 ModifyAddrGroupInfo( u32 dwGroupIndex, 
							  const TMULTISETENTRYINFO &tMultiSetEntryInfo );

	/*
	====================================================================
    ����        ���޸�ָ���Ļ�����,�����ն��б�
    �������˵�������������� + ��������Ϣ + �б��� + �б�����
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 ModifyAddrGroup( u32 dwGroupIndex, 
						  const TMULTISETENTRYINFO &tMultiSetEntryInfo,
						  u8 byMtListLen = 0,
						  u32 *pdwMtList = NULL);

	// ����������ַ��
	////////////////////////////////////////////////////////////////////////
	/*
	====================================================================
    ����        �����ļ������ַ��
    �������˵������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 LoadAddrBook( const char* pchLoadPath = NULL, BOOL32 bKeepRateNetOrder = TRUE );

	/*
	====================================================================
    ����        �������ַ�����ļ�
    �������˵������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
	BOOL32 SaveAddrBook( const char* pchSavePath = NULL, BOOL32 bIsRateIsNetOrder = TRUE );
	
	// test 
	/*
	====================================================================
    ����        ����ӡ��ַ����Ϣ(���ڲ���)
    �������˵������
    ����ֵ˵��  ����
	====================================================================
	*/
	void PrintAddrBook( void );
    
    /*
	====================================================================
    ����        ����ȡ������༶��ϵ��
    �������˵����TMultiLevel *tMultiLevel:���ر�����
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
    BOOL32 GetMultiLevelTable( TMultiLevel *tMultiLevel);

    /*
	====================================================================
    ����        ����ĳһ������Ϊ��һ������¼�����
    �������˵����u32 dwGroupIndex���¼����������� 
                  u32 dwUpGroupIndex���ϼ�����������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
    BOOL32 AddGroupToGroup( const u32 dwGroupIndex, const u32 dwUpGroupIndex );

    /*
	====================================================================
    ����        ��ɾ��һ������Ϊ��һ������¼���ϵ
    �������˵����u32 dwGroupIndex���¼����������� 
                  u32 dwUpGroupIndex���ϼ�����������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
    BOOL32 DeleteGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex ); 

     /*
	====================================================================
    ����        ���ҵ���һ�������л�����
    �������˵����u32 *dwOneLevelGroup�������һ������������
                  Ҫ���㹻�ռ䣨���������
    ����ֵ˵��  ��u32����һ�����������
	====================================================================
	*/
    u32 FindLevelOneGroup( u32 *dwOneLevelGroup );

    /*
	====================================================================
    ����        ���ҵ�ĳһ��������ϼ�����
    �������˵����u32 dwGroupIndex����������
    ����ֵ˵��  ��u32���ϼ���������
	====================================================================
	*/
    u32 FindUpGroupOfGroupByIndex( u32 dwGroupIndex );

    /*
	====================================================================
    ����        ���ҵ�������������¼�������������б�
    �������˵����u32 dwUpGroupIndex���ϼ�����������
                  u32 *dwLowGroupIndex�������¼������������б�
    ����ֵ˵��  ��u32���¼����������,����ʱ����INVALID_INDEX
	====================================================================
	*/
    u32 FindLowGroupOfGroupByIndex( u32 dwUpGroupIndex, u32 *dwLowGroupIndex );
    
    /*
	====================================================================
    ����        ��������ֱ�Ӳ㼶��ϵ��ӡ
    �������˵����void
    ����ֵ˵��  ��void
	====================================================================
	*/
    void PrintGroupRelation();

    /*
	====================================================================
    ����        ����ȡ��������������Ŀ
    �������˵����u32 dwGroupIndext������������
                  u32* pdwEntrySetIndext����Ŀ����ָ��
    ����ֵ˵��  ��u32:����������Ŀ����
	====================================================================
	*/
    u32 GetGroupAllEntrySet( u32 dwGroupIndext, u32* pdwEntrySetIndext );
	
    /*
	====================================================================
    ����        ����õ�ǰ�ж�������ϵ
    �������˵����
    ����ֵ˵��  ������ϵ��
	====================================================================
	*/
    u16 GetMultiLevelUsedSize();

    /*
	====================================================================
    ����        ����ò������ϵ��
    �������˵����u32 dwStartIndex:��ʼλ��
                  u32 dwGetNum:������õ���Ŀ
    ����ֵ˵��  ��TMultiLevel* tMultiLevel(����ϵ��)
                  u32 ʵ�ʻ�õ���Ŀ
	====================================================================
	*/
    u32 GetMultiLevelPartByIndex(u32 dwStartIndex, u32 dwGetNum, TMultiLevel* tMultiLevel);

protected :

    /*
    ====================================================================
    ����        ����ȡ������༶��ϵָ��
    �������˵����
    ����ֵ˵��  ��TMultiLevel *tMultiLevel:���ر�����
    ====================================================================
    */
    TMultiLevel* GetMultiLevel();

    /*
	====================================================================
    ����        �����������༶��ϵ��
    �������˵����TMultiLevel *tMultiLevel:������
    ����ֵ˵��  ���ɹ����
	====================================================================
	*/
    BOOL32 SaveMultiLevelTable( TMultiLevel *tMultiLevel, u16 wMultiLevelSize);

    /*
	====================================================================
    ����        �����������������������Ĳ㼶��ϵ
    �������˵����u32 dwGroupIndex:����������
    ����ֵ˵��  ��void
	====================================================================
	*/
    void ClearGroupRelation( u32 dwGroupIndex );

    /*
	====================================================================
    ����        ��������֮���Ƿ�Ϊ���¼���ϵ������ֱ�Ӻͼ�����¼���ϵ
    �������˵����u32 dwGroupIndext������������
                  u32 dwUpGroupIndext���ϼ�������
    ����ֵ˵��  ��BOOL32:�Ƿ����ϼ�
	====================================================================
	*/
    BOOL32 IsUpLevelGroup( u32 dwGroupIndext, u32 dwUpGroupIndext );

    /*
	====================================================================
    ����        �����õ�ǰ�ж�������ϵ
    �������˵����
    ����ֵ˵��  ������ϵ��
	====================================================================
	*/
    void SetMultiLevelUsedSize( u16 wSize);

    /*
	====================================================================
    ����        ����������ϵ��ȥ�������ڵĻ���
    �������˵����
    ����ֵ˵��  ��TMultiLevel* tMultiLevel(����ϵ��)
                  u16 wUsedSize(���С)
	====================================================================
	*/
    u16 PackMultiLevelTable(TMultiLevel* tMultiLevel, u16 wUsedSize);


private :

	FILE*	m_fpAddrBook;

	// ��ַ����Ŀ�������
	CAddArray< CAddrEntry >			m_cAddrBook;

	// ��ַ���������������
	CAddArray< CAddrMultiSetEntry >		m_cAddrMultiSetEntry;

	u32	m_dwAddrEntryTotalSize;			// ��ַ��Ŀ������
	u32	m_dwAddrGroupTotalSize;			// ������������
	u32	m_dwLastError;
    TMultiLevel* m_tMultiLevelTable;
    u16 m_wMultiLevelUsedSize;
		
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;





BOOL32 InitAddressBook( u32 dwEntryNum = MAX_ADDRENTRY, 
					  u32 dwMultiSetNum = MAX_ADDRGROUP,
                      const char* pchAddrBookPath = NULL);


API void addrhelp();
API void addrbookver();
API void prtaddrbook();
API void addrlogon();
API void addrlogoff();

#if defined(WIN32) 
#pragma pack(pop)
#endif

#endif // ADDR_BOOK_H


