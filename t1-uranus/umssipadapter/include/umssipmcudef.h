#ifndef _h_umssipmcudef_h__
#define _h_umssipmcudef_h__

#include "osp.h"
#include "kdvcascade.h"

#define     MAXLEN_CONFID                   16

//��Ϣ�������
#define      SERV_MSG_LEN					0x7000  //��Ϣ����
#define      SERV_MSGHEAD_LEN				0x30    //��Ϣͷ����

#define CASCADE_SPY_STARTPORT			(u16)30000	// 30000��37000 �ϼ����ɻش�Դ�˿ڣ�10 * 512 = 5120; ���� 1880 
#define  PORTSPAN                       (u16)10     // �˿ڵļ��

//����Žṹ (len:16)
struct CMcuConfId
{
protected:
	u8  	m_abyConfId[MAXLEN_CONFID];
	
public:
	u8   GetConfId( u8   * pbyConfId, u8   byBufLen ) const; //��û��������
	void CreateConfId( u8 byUsrGrpId );                               //���������
	void GetConfIdString( LPSTR lpszConfId, u8   byBufLen ) const;//��û�����ַ���
	void SetConfId( const CMcuConfId & CMcuConfId );                  //���û����
	u8   SetConfId( const u8   * pbyConfId, u8   byBufLen );          //���û��������
	u8   SetConfId( LPCSTR lpszConfId );                          //���û��������	
	BOOL IsNull( void ) const;                                  //�жϻ�����Ƿ�Ϊ��
	void SetNull( void );                                       //���û����Ϊ��
	BOOL operator == ( const CMcuConfId & CMcuConfId ) const;         //����������
    // ���񻪣���CMcuConfId�������û������Ϣ
    u8   GetUsrGrpId() const 
    {
        return m_abyConfId[MAXLEN_CONFID-1];
    }
    void SetUsrGrpId(u8 byGrpId)
    {
        m_abyConfId[MAXLEN_CONFID-1] = byGrpId;
    }
	
	//fuxiuhua,���ӻ��鷢����Ϣ
	//����ID����ɣ�MCU��(2Byte)/��������(1Byte)/��������ֵ(1Byte)/����Ų�������(4Byte)/
	//              δ��(6Byte)/��������(1Byte)/���(1Byte)
	void SetConfSource( u8 byConfSource )
	{
		m_abyConfId[MAXLEN_CONFID - 2] = byConfSource;
	}
	u8   GetConfSource()
	{
		return m_abyConfId[MAXLEN_CONFID - 2];
	}
	
	void Print( void ) const
	{
		// 		s8 achBuf[MAXLEN_CONFID*2+1];
		// 		memset(achBuf, 0, sizeof(achBuf));
		// 		GetConfIdString( achBuf, sizeof(achBuf) );
		// 		StaticLog("%s\n", achBuf);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//ҵ����Ϣ�࣬�����28K������Ϣ
class CServMsg
{
protected:
	u16     m_wSerialNO;            //��ˮ��
	u8      m_bySrcDriId;           //ԴDRI���
	u8      m_bySrcMtId;            //Դ�ն˺�
	u8      m_bySrcSsnId;           //Դ�Ự��
	u8      m_byDstDriId;           //Ŀ��DRI���
    u8      m_byDsTMCUMtId;            //Ŀ���ն˺�
	u8      m_byMcuId;              //MCU��
	u8      m_byChnIndex;           //ͨ��������
    u8      m_byConfIdx;            //����������
	CMcuConfId m_CMcuConfId;        //�����
	u16		m_wEventId;             //�¼���
	u16		m_wTimer;               //��ʱ
	u16		m_wErrorCode;           //������
	u16		m_wMsgBodyLen;          //��Ϣ�峤��
    u8      m_byTotalPktNum;        //�ܰ�����������Ҫ�а����͵���Ϣ��
    u8      m_byCurPktIdx;          //��ǰ����������0��ʼ��
	u8      m_abyReserverd[12];     //�����ֽ�
	u8      m_abyMsgBody[SERV_MSG_LEN-SERV_MSGHEAD_LEN];    //��Ϣ��
public:
	void  SetSerialNO(u16  wSerialNO){ m_wSerialNO = htons(wSerialNO);} 
    u16   GetSerialNO( void ) const { return ntohs(m_wSerialNO); }
    void  SetSrcDriId(u8   bySrcDriId){ m_bySrcDriId = bySrcDriId;} 
    u8    GetSrcDriId( void ) const { return m_bySrcDriId; }
    void  SetSrcMtId(u8   bySrcMtId){ m_bySrcMtId = bySrcMtId;} 
    u8    GetSrcMtId( void ) const { return m_bySrcMtId; }
    void  SetSrcSsnId(u8   bySrcSsnId){ m_bySrcSsnId = bySrcSsnId;} 
    u8    GetSrcSsnId( void ) const { return m_bySrcSsnId; }
    void  SetDstDriId(u8   byDstDriId){ m_byDstDriId = byDstDriId;} 
    u8    GetDstDriId( void ) const { return m_byDstDriId; }  
    void  SetDsTMCUMtId(u8   byDsTMCUMtId){ m_byDsTMCUMtId = byDsTMCUMtId;} 
    u8    GetDsTMCUMtId( void ) const { return m_byDsTMCUMtId; }
    void  SetMcuId(u8   byMcuId){ m_byMcuId = byMcuId;} 
    u8    GetMcuId( void ) const { return m_byMcuId; }
    void  SetChnIndex(u8   byChnIndex){ m_byChnIndex = byChnIndex;} 
    u8    GetChnIndex( void ) const { return m_byChnIndex; }
    void  SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx;} 
    u8    GetConfIdx( void ) const { return m_byConfIdx; } 
    void  SetEventId(u16  wEventId){ m_wEventId = htons(wEventId);} 
    u16   GetEventId( void ) const { return ntohs(m_wEventId); }
    void  SetTimer(u16  wTimer){ m_wTimer = htons(wTimer);} 
    u16   GetTimer( void ) const { return ntohs(m_wTimer); }
    void  SetErrorCode(u16  wErrorCode){ m_wErrorCode = htons(wErrorCode);} 
    u16   GetErrorCode( void ) const { return ntohs(m_wErrorCode); }
    void  SetTotalPktNum(u8 byPktNum) { m_byTotalPktNum = byPktNum; }
    u8    GetTotalPktNum( void ) { return m_byTotalPktNum; }
    void  SetCurPktIdx(u8 byPktIdx) { m_byCurPktIdx = byPktIdx; }
    u8    GetCurPktIdx( void ) { return m_byCurPktIdx; }
	
	void Init( void );
	void SetNoSrc(){ SetSrcSsnId( 0 ); }
	void SetMsgBodyLen( u16  wMsgBodyLen );
	CServMsg( void );//constructor
	CServMsg( u8   * const pbyMsg, u16  wMsgLen );//constructor
	~CServMsg( void );//distructor
	void ClearHdr( void );//��Ϣͷ����
	CMcuConfId GetConfId( void ) const;//��ȡ�������Ϣ
	void SetConfId( const CMcuConfId & CMcuConfId );//���û������Ϣ
	void SetNullConfId( void );//���û������ϢΪ��
	u16  GetMsgBodyLen( void ) const;//��ȡ��Ϣ�峤����Ϣ
	u16  GetMsgBody( u8   * pbyMsgBodyBuf, u16  wBufLen ) const;//��ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
	u8   * const GetMsgBody( void ) const;//��ȡ��Ϣ��ָ�룬�û������ṩBUFFER
	void SetMsgBody( u8   * const pbyMsgBody = NULL, u16  wLen = 0 );//������Ϣ��
	void CatMsgBody( u8   * const pbyMsgBody, u16  wLen );//�����Ϣ��
	u16  GetServMsgLen( void ) const;//��ȡ������Ϣ����
	u16  GetServMsg( u8   * pbyMsgBuf, u16  wBufLen ) const;//��ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
	u8   * const GetServMsg( void ) const;//��ȡ������Ϣָ�룬�û������ṩBUFFER
	void SetServMsg( u8   * const pbyMsg, u16  wLen );//����������Ϣ
	const CServMsg & operator= ( const CServMsg & cServMsg );//����������
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
/*-------------------------------------------------------------------
                               CServMsg                              
--------------------------------------------------------------------*/

/*====================================================================
    ������      ��CServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::CServMsg( void )
{
	Init();
}

/*====================================================================
    ������      ��CServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, Ҫ��ֵ����Ϣָ��
				  u16 wMsgLen, Ҫ��ֵ����Ϣ���ȣ�������ڵ��� SERV_MSGHEAD_LEN
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::CServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	Init();
	
	if( wMsgLen < SERV_MSGHEAD_LEN || pbyMsg == NULL )
		return;
	
	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	
	//set length
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��~CServMsg
    ����        ��distructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CServMsg::~CServMsg( void )
{

}

/*====================================================================
    ������      ��Init
    ����        ��BUFFER��ʼ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::Init( void )
{
	memset( this, 0, SERV_MSG_LEN );	//����
}

/*====================================================================
    ������      ��ClearHdr
    ����        ����Ϣͷ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::ClearHdr( void )
{
	u16		wBodyLen = GetMsgBodyLen();

	memset( this, 0, SERV_MSGHEAD_LEN );	//����
	SetMsgBodyLen( wBodyLen );
}

/*====================================================================
    ������      ��GetConfId
    ����        ����ȡ�������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ������ţ�ȫ0��ʾ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
    02/12/24    1.0         LI Yi         �޸Ľӿ�
====================================================================*/
inline CMcuConfId CServMsg::GetConfId( void ) const
{
	return( m_CMcuConfId );
}

/*====================================================================
    ������      ��SetConfId
    ����        �����û������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CMcuConfId & CMcuConfId������ţ�ȫ0��ʾ����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
    02/12/24    1.0         LI Yi         �޸Ľӿ�
====================================================================*/
inline void CServMsg::SetConfId( const CMcuConfId & CMcuConfId )
{
	m_CMcuConfId = CMcuConfId;
}

/*====================================================================
    ������      ��SetNullConfId
    ����        �����û������ϢΪ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/06/06    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetNullConfId( void )
{
	CMcuConfId		CMcuConfId;
	
	CMcuConfId.SetNull();
	SetConfId( CMcuConfId );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ��Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetMsgBodyLen( void ) const
{
	return( ntohs( m_wMsgBodyLen ) );
}

/*====================================================================
    ������      ��SetMsgBodyLen
    ����        ��������Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u16 wMsgBodyLen, ��Ϣ�峤��
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetMsgBodyLen( u16 wMsgBodyLen )
{
	m_wMsgBodyLen = htons( wMsgBodyLen );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ��ָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CServMsg::GetMsgBody( void ) const
{
	return( ( u8 * const )m_abyMsgBody );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ������Ϣ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��������Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetServMsgLen( void ) const
{
	return( GetMsgBodyLen() + SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBodyBuf, ���ص���Ϣ��
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
{
    u16 wActLen = min( GetMsgBodyLen(), wBufLen );
	memcpy( pbyMsgBodyBuf, m_abyMsgBody, wActLen );
	return wActLen;
}

/*====================================================================
    ������      ��SetMsgBody
    ����        ��������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        SetMsgBodyLen( 0 );
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN );
	memcpy( m_abyMsgBody, pbyMsgBody, wLen );
	SetMsgBodyLen( wLen );
}

/*====================================================================
    ������      ��CatMsgBody
    ����        �������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/11/07    1.0         Liaoweijiang  ����
====================================================================*/
inline void CServMsg::CatMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN - GetMsgBodyLen() );
	memcpy( m_abyMsgBody + GetMsgBodyLen(), pbyMsgBody, wLen );
	SetMsgBodyLen( GetMsgBodyLen() + wLen );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ������Ϣָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CServMsg::GetServMsg( void ) const
{
	return( ( u8 * const )( this ) );
}

/*====================================================================
    ������      ��GetServMsg
    ����        ����ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBuf, ���ص���Ϣ
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CServMsg::GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
{
	wBufLen = min(SERV_MSG_LEN,wBufLen);
	memcpy( pbyMsgBuf, this, wBufLen );
	return( min( GetMsgBodyLen() + SERV_MSGHEAD_LEN, wBufLen ) );
}

/*====================================================================
    ������      ��SetServMsg
    ����        ������������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, �����������Ϣ
				  u16 wMsgLen, �������Ϣ����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CServMsg::SetServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	if( wMsgLen < SERV_MSGHEAD_LEN )
	{
		OspPrintf( TRUE, FALSE, "CServMsg: SetServMsg() Exception -- invalid MsgLen!\n" );
		return;
	}

	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��operator=
    ����        ������������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����CServMsg & cServMsg, ��ֵ����Ϣ����
    ����ֵ˵��  ��CServMsg����Ӧ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline const CServMsg & CServMsg::operator= ( const CServMsg & cServMsg )
{
	u16	wLen = cServMsg.GetServMsgLen();

	memcpy( this, cServMsg.GetServMsg(), wLen );
	return( *this );
}

/*-------------------------------------------------------------------
                               CMcuConfId                                  
--------------------------------------------------------------------*/

/*====================================================================
    ������      ��GetConfId
    ����        ����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyConfId, �����BUFFER����ָ�룬�������ػ����
			      u8 byBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��������С
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline u8 CMcuConfId::GetConfId( u8 * pbyConfId, u8 byBufLen ) const
{
	u8	byLen = min( sizeof( m_abyConfId ), byBufLen );
	memcpy( pbyConfId, m_abyConfId, byLen );

	return( byLen );
}

/*====================================================================
    ������      ��GetConfIdString
    ����        ����û�����ַ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����LPSTR lpszConfId, ������ַ���BUFFER����ָ�룬����
	                   ����0��β������ַ���
			      u8 byBufLen, BUFFER��С
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline void CMcuConfId::GetConfIdString( LPSTR lpszConfId, u8 byBufLen ) const
{
	u8	byLoop;

	for( byLoop = 0; byLoop < sizeof( m_abyConfId ) && byLoop < ( byBufLen - 1 ) / 2; byLoop++ )
	{
		sprintf( lpszConfId + byLoop * 2, "%.2x", m_abyConfId[byLoop] );
	}
	lpszConfId[byLoop * 2] = '\0';
}

/*====================================================================
    ������      ��SetConfId
    ����        �����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CMcuConfId & CMcuConfId, ��������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline void CMcuConfId::SetConfId( const CMcuConfId & CMcuConfId )
{
	CMcuConfId.GetConfId( m_abyConfId, sizeof( m_abyConfId ) );
}

/*====================================================================
    ������      ��SetConfId
    ����        �����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const u8 * pbyConfId, ���������ָ��
			      u8 byBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�����������С
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline u8 CMcuConfId::SetConfId( const u8 * pbyConfId, u8 byBufLen )
{
	u8	bySize = min( byBufLen, sizeof( m_abyConfId ) );
	
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	memcpy( m_abyConfId, pbyConfId, bySize );

	return( bySize );
}
	
/*====================================================================
    ������      ��SetConfId
    ����        �����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����LPCSTR lpszConfId, ����Ļ�����ַ���
    ����ֵ˵��  ��ʵ�����������С
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline u8 CMcuConfId::SetConfId( LPCSTR lpszConfId )
{
	LPCSTR	lpszTemp = lpszConfId;
	s8	achTemp[3], *lpszStop;
	u8	byCount = 0;

	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	while( lpszTemp != NULL && lpszTemp + 1 != NULL && byCount < sizeof( m_abyConfId ) )
	{
		memcpy( achTemp, lpszTemp, 2 );
		achTemp[2] = '\0';
		m_abyConfId[byCount] = ( u8 )strtoul( achTemp, &lpszStop, 16 );
		byCount++;
		lpszTemp += 2;
	}

	return( byCount );
}

/*====================================================================
    ������      ��CreateConfId
    ����        �����������
    �㷨ʵ��    �����ݵ�ǰʱ������ֵ
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/06/06    1.0         LI Yi         ����
====================================================================*/
inline void CMcuConfId::CreateConfId( u8 byUsrGrpId )
{
	struct tm	*ptmCurTime;
	time_t		tCurTime = time( NULL );
	u8	byTemp;
	u16	wTemp;

	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	
	//get current time
	ptmCurTime = localtime( &tCurTime );
	//year
	wTemp = ptmCurTime->tm_year + 1900;
	memcpy( m_abyConfId, &wTemp, sizeof( u16 ) );
	//month
	byTemp = ptmCurTime->tm_mon + 1;
	memcpy( m_abyConfId + 2, &byTemp, sizeof( u8 ) );
	//day
	byTemp = ptmCurTime->tm_mday;
	memcpy( m_abyConfId + 3, &byTemp, sizeof( u8 ) );
	//hour
	byTemp = ptmCurTime->tm_hour;
	memcpy( m_abyConfId + 4, &byTemp, sizeof( u8 ) );
	//minute
	byTemp = ptmCurTime->tm_min;
	memcpy( m_abyConfId + 5, &byTemp, sizeof( u8 ) );
	//second
	byTemp = ptmCurTime->tm_sec;
	memcpy( m_abyConfId + 6, &byTemp, sizeof( u8 ) );
	//msec
	wTemp = 0;
	memcpy( m_abyConfId + 7, &wTemp, sizeof( u16 ) );

	//rand
	wTemp = rand();
	memcpy( m_abyConfId + 9, &wTemp, sizeof( u16 ) );

    // ���� [6/21/2006]
    // ���λ��ʾ��ID
    SetUsrGrpId( byUsrGrpId );
}

/*====================================================================
    ������      ��IsNull
    ����        ���жϻ�����Ƿ�Ϊ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��TRUE/FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/03/31    1.0         LI Yi         ����
====================================================================*/
inline BOOL CMcuConfId::IsNull( void ) const
{
	u8	abyNull[sizeof( m_abyConfId )];

	memset( abyNull, 0, sizeof( abyNull ) );
	if( memcmp( m_abyConfId, abyNull, sizeof( m_abyConfId ) ) == 0 )
		return( TRUE );
	else
		return( FALSE );
}

/*====================================================================
    ������      ��SetNull
    ����        �����û����Ϊ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/03/31    1.0         LI Yi         ����
====================================================================*/
inline void CMcuConfId::SetNull( void )
{
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
}

/*====================================================================
    ������      ��operator==
    ����        ������������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CMcuConfId & CMcuConfId, ��������
    ����ֵ˵��  ����ȷ���TRUE�����򷵻�FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
inline BOOL CMcuConfId::operator == ( const CMcuConfId & CMcuConfId ) const
{
	u8	abyTemp[sizeof( m_abyConfId )];

	CMcuConfId.GetConfId( abyTemp, sizeof( abyTemp ) );
	if( memcmp( abyTemp, m_abyConfId, sizeof( m_abyConfId ) ) == 0 )
		return( TRUE );
	else
		return( FALSE );
}

//�豸���ඨ��
#define		MCU_TYPE_MCU                     	 1   //MCU
#define		MCU_TYPE_MCUPERI                     2   //MCU����
#define		MCU_TYPE_MT                          3   //�ն�
//conf id len
#define     MCU_MAXLEN_CONFID                   16
#define     MCU_LOCAL_MCUID                     192					//����MCU ID 
#define		MCU_LOCAL_MCUIDX					19200				//����MCU IDX
#define		MCU_INVALID_MCUIDX					0xffff				//�Ƿ�mcuidx��

// ��ȡ������Ƶ��ͼ
#define     MAXNUM_VIEWINCONF				5    //ÿ������������ͼ��
#define     MAXNUM_GEOINVIEW				5    //ÿ����ͼ����󼸺β�����
#define		MAXNUM_SUBFRAMEINGEO            16   //ÿ�����β��ֵ�����Ա��
#define     MAXNUM_VSCHEMEINVIEW			4    //ÿ����ͼ�����Ƶ������
#define     MAXNUM_MIXERINCONF              16   //ÿ�������е���������  
#define     MAXNUM_ADDMT                    10   //һ�����ӵ����MT�� 

#define		INVALID_MCUIDX					0xffff				//�Ƿ�mcuidx��
#define		LOCAL_MCUIDX					19200				//����MCU IDX

/*ý�����Ͷ���*/

#define   MCU_MEDIA_TYPE_NULL                 (u8)255  /*ý������Ϊ��*/

/*��Ƶ*/

#define	  MCU_MEDIA_TYPE_MP3	              (u8)96  /*mp3 mode 0-4*/

#define   MCU_MEDIA_TYPE_G7221C	              (u8)98  /*G722.1.C Siren14*/

#define   MCU_MEDIA_TYPE_G719	              (u8)99  /*G719 non-standard of polycom serial 22*/

#define   MCU_MEDIA_TYPE_PCMA		          (u8)8   /*G.711 Alaw  mode 5*/

#define   MCU_MEDIA_TYPE_PCMU		          (u8)0   /*G.711 ulaw  mode 6*/

#define   MCU_MEDIA_TYPE_G721		          (u8)2   /*G.721*/

#define   MCU_MEDIA_TYPE_G722		          (u8)9   /*G.722*/

#define	  MCU_MEDIA_TYPE_G7231		          (u8)4   /*G.7231*/

#define   MCU_MEDIA_TYPE_ADPCM                (u8)5   /*DVI4 ADPCM*/

#define	  MCU_MEDIA_TYPE_G728		          (u8)15  /*G.728*/

#define	  MCU_MEDIA_TYPE_G729		          (u8)18  /*G.729*/
#define   MCU_MEDIA_TYPE_G7221                (u8)13  /*G.7221*/

#define   MCU_MEDIA_TYPE_AACLC                (u8)102 /*AAC LC*/
#define   MCU_MEDIA_TYPE_AACLD                (u8)103 /*AAC LD*/

/*��Ƶ*/

#define   MCU_MEDIA_TYPE_MP4	              (u8)97  /*MPEG-4*/

#define   MCU_MEDIA_TYPE_H261	              (u8)31  /*H.261*/

#define   MCU_MEDIA_TYPE_H262	              (u8)33  /*H.262 (MPEG-2)*/

#define   MCU_MEDIA_TYPE_H263	              (u8)34  /*H.263*/

#define   MCU_MEDIA_TYPE_H263PLUS             (u8)101 /*H.263+*/

#define   MCU_MEDIA_TYPE_H264	              (u8)106 /*H.264*/

#define   MCU_MEDIA_TYPE_H264_ForHuawei       (u8)105 /*H.264*/

/*����*/
#define   MCU_MEDIA_TYPE_H224	              (u8)100  /*H.224 Payload �ݶ�100*/
#define   MCU_MEDIA_TYPE_T120                 (u8)200  /*T.120ý������*/
#define   MCU_MEDIA_TYPE_H239                 (u8)239  /*H.239�������� */
#define   MCU_MEDIA_TYPE_MMCU                 (u8)120  /*��������ͨ�� */

#define     MCU_VIDEO_FPS_USRDEFINED            128 //�Զ���֡��(>=128,��ȥ128��Ϊʵ��֡��)
//��Ƶ��ʽ����
#define     MCU_VIDEO_FORMAT_INVALID            255
#define		MCU_VIDEO_FORMAT_SQCIF				1   //SQCIF(128*96)
#define		MCU_VIDEO_FORMAT_QCIF				2   //SCIF(176*144)
#define		MCU_VIDEO_FORMAT_CIF                3   //CIF(352*288)  - P��
#define     MCU_VIDEO_FORMAT_2CIF               4   //2CIF(352*576) - p
#define		MCU_VIDEO_FORMAT_4CIF               5   //4CIF(704*576) - P��(H264�´˺�ָ��D1(720*576)   - P�ƣ�N��D1��720*480��)
#define		MCU_VIDEO_FORMAT_16CIF				6   //16CIF(1408*1152)
#define		MCU_VIDEO_FORMAT_AUTO				7   //����Ӧ��������MPEG4

#define		MCU_VIDEO_FORMAT_SIF                8   //SIF(352*240)  - N��
#define     MCU_VIDEO_FORMAT_2SIF               9   //2SIF
#define		MCU_VIDEO_FORMAT_4SIF               10  //4SIF(704*480) - N��

#define     MCU_VIDEO_FORMAT_VGA                11  //VGA(640*480)
#define		MCU_VIDEO_FORMAT_SVGA               12  //SVGA(800*600)
#define		MCU_VIDEO_FORMAT_XGA                13  //XGA(1024*768)
#define     MCU_VIDEO_FORMAT_WXGA               14  //WXGA(1280*768 | 1280*800)

//�������ն˷ֱ��ʸı�
#define		MCU_VIDEO_FORMAT_SQCIF_112x96       21  //SQCIF(112*96)
#define		MCU_VIDEO_FORMAT_SQCIF_96x80        22  //SQCIF(96*80)

// ����ֱ���
#define     MCU_VIDEO_FORMAT_W4CIF              31  //Wide 4CIF(1024*576)
#define     MCU_VIDEO_FORMAT_HD720              32  //720 1280*720
#define     MCU_VIDEO_FORMAT_SXGA               33  //SXGA 1280*1024
#define     MCU_VIDEO_FORMAT_UXGA               34  //UXGA 1600*1200
#define     MCU_VIDEO_FORMAT_HD1080             35  //1080  1920*1088(p) 1920*544(i)

//�Ǳ�ֱ��ʣ�1080p��ͼ���������ն˷ֱ��ʸı�
#define     MCU_VIDEO_FORMAT_1440x816           41  //1440��816(3/4)
#define     MCU_VIDEO_FORMAT_1280x720           42  //1280��720(2/3)
#define     MCU_VIDEO_FORMAT_960x544            43  // 960��544(1/2)
#define     MCU_VIDEO_FORMAT_640x368            44  // 640��368(1/3)
#define     MCU_VIDEO_FORMAT_480x272            45  // 480��272(1/4)
#define     MCU_VIDEO_FORMAT_384x272            46  // 384��272(1/5)

//�Ǳ�ֱ��ʣ�720p��ͼ�� �������ն˷ֱ��ʸı�
#define     MCU_VIDEO_FORMAT_720_960x544        51  //960��544(3/4)
#define     MCU_VIDEO_FORMAT_720_864x480        52  //864��480(2/3)
#define     MCU_VIDEO_FORMAT_720_640x368        53  //640��368(1/2)
#define     MCU_VIDEO_FORMAT_720_432x240        54  //432��240(1/3)
#define     MCU_VIDEO_FORMAT_720_320x192        55  //320��192(1/4)

//�Ǳ�ֱ��ʣ�1080p��ͼ���������ն˷ֱ��ʸı�
#define		MCU_VIDEO_FORMAT_640x544			56	//640x544
#define		MCU_VIDEO_FORMAT_320x272			57	//320x272

//Resolutions that can be acceptable
#define		MCU_MAXNUM_ACCEPTABLE_RES			(u8)57

#define MCU_F_WHNONELARGER			-2	// none larger in both
#define MCU_F_HLARGER				-1	// only larger in height
#define MCU_WHEQUAL					0	// equal
#define MCU_F_WLARGER				1	// only larger in width
#define MCU_F_WHLARGER				2	// larger in both

//����ͼ����������ģʽ
#define		MCU_MODE_NONE			             0	  //����Ƶ������
#define		MCU_MODE_VIDEO						 1	  //ֻ����Ƶ����ѯ��Ƶ��ֻ�����ع㲥��
#define		MCU_MODE_AUDIO						 2	  //ֻ����Ƶ
#define		MCU_MODE_BOTH						 3    //����Ƶ��������ѯ�����ˣ�ֻ�����ع㲥��
#define     MCU_MODE_DATA                        4    //���� 
#define     MCU_MODE_SECVIDEO                    5    //�ڶ�·��Ƶ


inline void GetWHByRes(u8 byRes, u16 &wWidth, u16 &wHeight)
{
    wWidth = 0;
    wHeight = 0;
    
    switch(byRes)
    {
    case MCU_VIDEO_FORMAT_SQCIF_112x96:
        wWidth = 112;
        wHeight = 96;
        break;
        
    case MCU_VIDEO_FORMAT_SQCIF_96x80:
        wWidth = 96;
        wHeight = 80;
        break;
        
    case MCU_VIDEO_FORMAT_SQCIF:
        wWidth = 128;
        wHeight = 96;
        break;
        
    case MCU_VIDEO_FORMAT_QCIF:
        wWidth = 176;
        wHeight = 144;
        break;
        
    case MCU_VIDEO_FORMAT_CIF:
        wWidth = 352;
        wHeight = 288;
        break;
        
    case MCU_VIDEO_FORMAT_2CIF:
        wWidth = 352;
        wHeight = 576;
        break;
        
    case MCU_VIDEO_FORMAT_4CIF:
        
        //���ھ����ܲ��ſ��ǣ�����ȡ��ֵ
        wWidth = 704;
        wHeight = 576;
        break;
        
    case MCU_VIDEO_FORMAT_16CIF:
        wWidth = 1048;
        wHeight = 1152;
        break;
        
    case MCU_VIDEO_FORMAT_AUTO:
		// ����auto�ֱ��ʽ���Ϊcif
        wWidth = 352;
        wHeight = 288;      
        break;
        
    case MCU_VIDEO_FORMAT_SIF:
        wWidth = 352;
        wHeight = 240;
        break;
        
    case MCU_VIDEO_FORMAT_2SIF:
        wWidth = 352;
        wHeight = 480;
        break;
        
    case MCU_VIDEO_FORMAT_4SIF:
        wWidth = 704;
        wHeight = 480;
        break;
        
    case MCU_VIDEO_FORMAT_VGA:
        wWidth = 640;
        wHeight = 480;
        break;
        
    case MCU_VIDEO_FORMAT_SVGA:
        wWidth = 800;
        wHeight = 608;   //600-->608
        break;
        
    case MCU_VIDEO_FORMAT_XGA:
        wWidth = 1024;
        wHeight = 768;
        break;

    case MCU_VIDEO_FORMAT_W4CIF:
        wWidth = 1024;
        wHeight = 576;
        break;

    case MCU_VIDEO_FORMAT_HD720:
        wWidth = 1280;
        wHeight = 720;
        break;

    case MCU_VIDEO_FORMAT_SXGA:
        wWidth = 1280;
        wHeight = 1024;
        break;

    case MCU_VIDEO_FORMAT_UXGA:
        wWidth = 1600;
        wHeight = 1200;
        break;

    case MCU_VIDEO_FORMAT_HD1080:
        wWidth = 1920;
        wHeight = 1088;
        break;
		//�Ǳ�ֱ��ʣ�1080p��ͼ��
	case MCU_VIDEO_FORMAT_1440x816:
		wWidth = 1440;
		wHeight = 816;
        break;

	case MCU_VIDEO_FORMAT_1280x720:
		wWidth = 1280;
		wHeight = 720;
		break;
	
	case MCU_VIDEO_FORMAT_960x544:
		wWidth = 960;
		wHeight = 544;
		break;

	case MCU_VIDEO_FORMAT_640x368:
		wWidth = 640;
		wHeight =368;
		break;

	case MCU_VIDEO_FORMAT_480x272:
		wWidth = 480;
		wHeight =272;
		break;
		
	case MCU_VIDEO_FORMAT_384x272:
		wWidth = 384;
		wHeight =272;
		break;

	//�Ǳ�ֱ��ʣ�720p��ͼ��
	case MCU_VIDEO_FORMAT_720_960x544:
		wWidth = 960;
		wHeight =544;
		break;

	case MCU_VIDEO_FORMAT_720_864x480:
		wWidth = 864;
		wHeight =480;
		break;

	case MCU_VIDEO_FORMAT_720_640x368:
		wWidth = 640;
		wHeight =368;
		break;

	case MCU_VIDEO_FORMAT_720_432x240:
		wWidth = 432;
		wHeight =240;
		break;

	case MCU_VIDEO_FORMAT_720_320x192:
		wWidth = 320;
		wHeight =192;
		break;
	case MCU_VIDEO_FORMAT_640x544:
		wWidth = 640;
		wHeight =544;
		break;
	case MCU_VIDEO_FORMAT_320x272:
		wWidth = 320;
		wHeight =272;
		break;
    default:
        break;
    }
    return;
}

/*==============================================================================
������    :  WHCmp
����      :  ĳ�߿�ֱ�ͬ��һ�߿�Ƚ�
�㷨ʵ��  :  
����˵��  :  
����ֵ˵��:  s32 
             ��߾�С���� F_WHNONELARGER
			 ��С�ߴ󷵻� F_HLARGER
			 ��߾���ȷ��� WHEQUAL
			 ����С���� F_WLARGER
			 ��߾��󷵻� F_WHLARGER
-------------------------------------------------------------------------------
�޸ļ�¼  :  
��  ��       �汾          �޸���          �߶���          �޸ļ�¼
2009-10-20                  Ѧ��                            ����
==============================================================================*/
inline s32 WHCmp(u16 wSrcWidth, u16 wSrcHeight, u16 wDstWidth, u16 wDstHeight)
{
	//�������
	//VIDEO_FORMAT_480x272 ����>�Ƚ�ʱͳһ���䵽480 x 288
	wSrcHeight = (wSrcHeight == 272) ? 288 : wSrcHeight;
	wDstHeight = (wDstHeight == 272) ? 288 : wDstHeight;
	
	//ǰ�߾������ں���
	if ( (wSrcWidth == wDstWidth) && (wSrcHeight == wDstHeight) )
	{
		return MCU_WHEQUAL;  //��߾���  (equal in width and height)
	}
	else if( ( wSrcWidth <= wDstWidth ) && (wSrcHeight <= wDstHeight) )
	{
		return MCU_F_WHNONELARGER; //��߾�С����ȸ�С����С�ߵ� (none bigger in both width and height)
	}
	//ǰ��������һ����ں���
	else if ( (wSrcWidth <= wDstWidth) && (wSrcHeight >= wDstHeight) )
	{
		return MCU_F_HLARGER; //��С�ߴ󣬿�ȸߴ�  (only bigger in height)
	}
	else if ( (wSrcWidth >= wDstWidth) && (wSrcHeight <= wDstHeight) )
	{
		return MCU_F_WLARGER;  //����С�����ߵ�  (only bigger in width)
	}
	else 
	{
		return MCU_F_WHLARGER; //��߾���			 (bigger both in width and height)
	}
}
/////////////// mcu ��ش� /////////////////////

#define ISHDFORMAT(byRes) \
	(VIDEO_FORMAT_W4CIF == byRes || VIDEO_FORMAT_HD720 == byRes || \
	VIDEO_FORMAT_SXGA == byRes || VIDEO_FORMAT_UXGA == byRes || \
         VIDEO_FORMAT_HD1080 == byRes)

// H264��������(HP/BP) [12/8/2011 chendaiwei]
enum emMcuProfileAttrb
{
	emmcuBpAttrb,	//BP
		emmcuHpAttrb,	//HP
};

struct TMCUMt;
//�����MCU���ն˻�����ṹ (len:6)
struct TMCUMtNoConstruct
{
protected:
    u8          m_byMainType;   //�豸����
    u8  		m_bySubType;	//�豸����
	u8  		m_byMcuId;		//MCU��
	u8  		m_byEqpId;	    //�豸��	
	u8          m_byConfDriId;  //DRI���
    u8          m_byConfIdx;    //���������ţ�������ʵ���� 1 - MAXNUM_MCU_CONF

public:
	// ���ýṹ����
	void   SetType( u8   byType )
	{ 
		m_byMainType = ( (m_byMainType & 0xf0) | (byType & 0xf) ) ; 
	}         

	// �õ��ṹ����
	u8     GetType( void ) const { return m_byMainType & 0xf; }     
	
	// fxh ��GetMcuIdƥ�����������ԭu8ͬ������
	void   SetMcuId( u16  wMcuId )	{ SetMcuIdx(wMcuId); } 
    
	// �õ�McuId
	u16     GetMcuId( void ) const { return GetMcuIdx(); }

	// �ж�TMtNoConstruct��TMtNoConstruct�Ƿ����
	BOOL   operator ==( const TMCUMtNoConstruct & tObj ) const;    

	//����MCU����
	//����MCU
	void   SetMcu( u16   wMcuIdx );                         
	void   SetMcuType( u8  byMcuType )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCU); 
		m_bySubType = ((m_byMainType & 0xf0)| (byMcuType&0xf) ); 
	}

	u8     GetMcuType( void ) const { return m_bySubType & 0xf; }

	// �������躯��
	// ����MCU����
	void   SetMcuEqp( u8   byMcuId, u8   byEqpId, u8   byEqpType );  
	
	// ����MCU��������
	void   SetEqpType( u8   byEqpType )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCUPERI); 
		m_bySubType = ((m_byMainType & 0xf0)| (byEqpType&0xf) ); 		
	}  
	
	u8     GetEqpType( void ) const { return m_bySubType & 0xf; }
	
	void   SetEqpId( u8   byEqpId )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCUPERI);
		m_byEqpId = byEqpId; 
	}

	u8     GetEqpId( void ) const { return m_byEqpId; }
	
	//�����ն˺���
	void   SetMt( u16   wMcuIdx, u8   byMtId, u8   m_byDriId = 0, u8   m_byConfIdx = 0);
	void   SetMt( TMt tMt);
	void   SetMtId( u8   byMtId )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MT);	
		m_byEqpId = byMtId; 
	}
	u8     GetMtId( void ) const { return m_byEqpId; }//�����ն�
	void   SetMtType( u8   byMtType ) 
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MT);		
		m_bySubType = ( (m_bySubType & 0xf0 ) | ( byMtType & 0xf ) );
	}
	u8     GetMtType( void ) const { return m_bySubType & 0xf; }  	
    void   SetDriId(u8   byDriId){ m_byConfDriId = byDriId; }
    u8     GetDriId( void ) const { return m_byConfDriId; }
    void   SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx; } 
    u8     GetConfIdx( void ) const { return m_byConfIdx; }
	void   SetNull( void ){ 
		m_byMainType = m_bySubType = m_byMcuId = m_byEqpId = m_byConfDriId = 0;
		SetMcuIdx( INVALID_MCUIDX );
	}
	BOOL   IsNull ( void ) const{ return ( TYPE_MCU != GetType() && m_byEqpId == 0 ) || GetMcuIdx() == INVALID_MCUIDX; }
	BOOL   IsMcuIdLocal() const {	return (m_byMcuId == LOCAL_MCUID );	}

	// ��LOCAL_MCUIDX��ΪLOCAL_MCUID
	BOOL   IsLocal() const 
	{
		// [11/9/2010 liuxu] ���趼�Ǳ����ã�ֱ�ӷ���TRUE
		if (TYPE_MCUPERI == GetType())
		{
			return TRUE;
		}
		
		return (GetMcuIdx() == LOCAL_MCUIDX );		
	}

//[0901]fxh����mcuidx�����걸mcu��ʶ���б��ػ����ɱ���mcuid����ʵ��ϸ�ڽ��з�װ�����ɽ׶Σ����������ӿڽ�ֹ������ã�֮��Ὣ��˽�л�
// private:
	u16	   GetMcuIdx() const {
		return ( (( m_byMainType & 0xf0 ) << 8 ) 
			+ (( m_bySubType & 0xf0) << 4 ) 
			+ m_byMcuId );
	}

	void   SetMcuIdx( u16 wMcuIdx ){ 
		m_byMainType = m_byMainType & 0x0f;
		m_bySubType = m_bySubType & 0x0f;

		m_byMainType |= ( ( wMcuIdx >> 8 ) & 0xf0 );
		m_bySubType |= ( ( wMcuIdx & 0xf00 ) >> 4 );
		m_byMcuId = (wMcuIdx & 0xff);
	}

	// [11/4/2011 liuxu] ��Ӵ�ӡ��Ϣ
	static void PrintTitle()  
	{
	//	StaticLog("|-----------------------------------------------|\n");
	//	StaticLog("| %5s | %5s | %5s | %5s | %5s | %5s |\n", "MainT", "SubT", "McuId", "MtId", "DriId", "Conf");
	//	StaticLog("|-----------------------------------------------|\n");
	}
	
	// [11/4/2011 liuxu] ��ӡ����
	void PrintContent() const 
	{
	//	StaticLog("| %5d | %5d | %5d | %5d | %5d | %5d |\n", GetType(), GetEqpType(), GetMcuIdx(), GetMtId(), GetDriId(), GetConfIdx());
	}
}
PACKED
;

//�����MCU���ն˻�����ṹ (len:6)
struct TMCUMt : public TMCUMtNoConstruct
{
	// [5/25/2011 liuxu] TMCUMt��TMCUMtNoConstruct��ȡ���׽ṹ,���ݻ���һ��, ά��������,
	// Ҳ���ںܴ������. �����������������. TMCUMtNoConstruct��ʱ���ܱ��ϳ�,ԭ��(Դ��zjj):
	// ���ǵĴ������õ��˺ܶ�������ṹ,�����������г�Ա�����й��캯��,��TMCUMt���ڹ��캯��
	// ����������Ҫ�������캯����TMCUMtNoConstruct.
	
public:
	// ���캯��
	TMCUMt()
	{
		memset( this,0,sizeof(TMCUMt) );
		SetMcuIdx( INVALID_MCUIDX );
	}
	
	// ���캯��
	TMCUMt( const TMCUMtNoConstruct& tOther )
	{
		memcpy( this, &tOther, sizeof(TMCUMtNoConstruct) );
	}
}
PACKED
;

//������Ƶý���ʽ������(len:5)
struct TMcuVideoStreamCap
{
public:
    u16		m_wMaxBitRate;  // ���λ��ʶHP/BP���ԣ�Ϊ1��ʶHP��Ϊ0��ʾBP [12/2/2011 chendaiwei]
    u8		m_byMediaType;   
    u8      m_byResolution;	//�ֱ��� VIDEO_FORMAT_AUTO, ...
	u8      m_byFrameRate;  //֡�� MPI������ H.264 ���� FPS
    
public:
    TMcuVideoStreamCap() { Clear(); }
    TMcuVideoStreamCap(u8 byMediaType,u8 byRes,u8 byFrameRate,emMcuProfileAttrb emAttrb,u16 wMaxRate) 
	{
		SetMediaType(byMediaType);
		SetResolution(byRes);
		MCU_MEDIA_TYPE_H264 == byMediaType ? SetUserDefFrameRate(byFrameRate) : SetFrameRate(byFrameRate);
		SetMaxBitRate(wMaxRate);
		SetH264ProfileAttrb(emAttrb);
	}
    
    void    Clear(void)
    {
        m_wMaxBitRate = 0;
        m_byFrameRate = 0;
        m_byMediaType = MCU_MEDIA_TYPE_NULL;
        m_byResolution = MCU_VIDEO_FORMAT_CIF;
    }   
    
    void	SetMediaType(u8 byMediaType)  {  m_byMediaType = byMediaType; }	
    u8		GetMediaType() const { return m_byMediaType; }
    
    void    SetResolution(u8 byRes) {   m_byResolution = byRes;    }
    u8      GetResolution(void) const   {   return m_byResolution;    }

    void    SetFrameRate(u8 byFrameRate)
    {
        if ( MCU_MEDIA_TYPE_H264 == m_byMediaType )
        {
           // StaticLog("Function has been preciated, try SetUserDefFrameRate\n" );
            return;
        }
        m_byFrameRate = byFrameRate;
    }
    u8      GetFrameRate(void) const
    {
        if ( MCU_MEDIA_TYPE_H264 == m_byMediaType )
        {
            //StaticLog("Function has been preciated, try GetUserDefFrameRate\n" );
            return 0;
        }
        return m_byFrameRate;
    }

    // guzh [12/1/2007] �Զ���֡�ʵı���/��ȡ
    void    SetUserDefFrameRate(u8 byActFrameRate) { m_byFrameRate = MCU_VIDEO_FPS_USRDEFINED+byActFrameRate; }
    BOOL32  IsFrameRateUserDefined() const {return (m_byFrameRate>MCU_VIDEO_FPS_USRDEFINED); }
    u8      GetUserDefFrameRate(void) const { return IsFrameRateUserDefined() ? m_byFrameRate-MCU_VIDEO_FPS_USRDEFINED : m_byFrameRate; }
    
	// m_wMaxBitRate�ĵ�15λ��ʶbitRate [12/2/2011 chendaiwei]
    void	SetMaxBitRate(u16 wMaxRate) 
	{ 
		//m_wMaxBitRate = (m_wMaxBitRate & 0x8000) | htons(wMaxRate);
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		wTmpBitRate = (wTmpBitRate & 0x8000) | ( wMaxRate & 0x7FFF );
		m_wMaxBitRate = htons( wTmpBitRate );
	}

    u16		GetMaxBitRate() const 
	{ 
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		wTmpBitRate = wTmpBitRate & 0x7FFF;
		return wTmpBitRate; 
	}

	BOOL32  IsSupportHP() const
	{ 
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		if(wTmpBitRate & 0x8000)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	
	/*====================================================================
	������      ��SetH264ProfileAttrb
	����        ������H264��HP/BP����

	�㷨ʵ��    ��
	����ȫ�ֱ�����
	�������˵����[IN]emMcuProfileAttrb emAttb��ʶHP/BP����

	����ֵ˵��  ��
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��      �汾        �޸���        �޸�����
	2011/11/28  4.0         chendaiwei       ����
	====================================================================*/
	void SetH264ProfileAttrb(emMcuProfileAttrb emAttrb)
	{
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		switch(emAttrb)
		{
		case emmcuHpAttrb:
			//m_wMaxBitRate = m_wMaxBitRate|0x8000 ;
			wTmpBitRate = wTmpBitRate | 0x8000;			
			break;
		case emmcuBpAttrb:
			//m_wMaxBitRate = m_wMaxBitRate&0x7FFF ;
			wTmpBitRate = wTmpBitRate & 0x7FFF;
			break;
		}
		m_wMaxBitRate = htons( wTmpBitRate );

		return;
	}

		/*====================================================================
	������      :GetH264ProfileAttrb
	����        ����ȡH264��HP/BP����

	�㷨ʵ��    ��
	����ȫ�ֱ�����
	�������˵����

	����ֵ˵��  ��[OUT]emMcuProfileAttrb emAttb��ʶHP/BP����
	----------------------------------------------------------------------
	�޸ļ�¼    ��
	��  ��      �汾        �޸���        �޸�����
	2011/11/28  4.0         chendaiwei       ����
	====================================================================*/
	emMcuProfileAttrb GetH264ProfileAttrb ( void ) const
	{
		u16 wTmpBitRate = ntohs( m_wMaxBitRate );
		if(wTmpBitRate & 0x8000)
		{
			return emmcuHpAttrb;
		}
		else
		{
			return emmcuBpAttrb;
		}
	}

	//TODO �Ƿ����HP/BP�ıȽ� [12/2/2011 chendaiwei]
	BOOL32 IsH264CapLower(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// ����֡��>30, ֡�ʰ�ʵ��25�Ƚ�
		u8 byDstFR = GetUserDefFrameRate();
		if(!ISHDFORMAT(m_byResolution) && byDstFR > 30 )
		{
			byDstFR = 25;
		}
		
		if(!ISHDFORMAT(bySrcRes) && bySrcFR > 30 )
		{
			bySrcFR = 25;
		}
		
		if ((wDstWidth * wDstHeight * byDstFR) < (wSrcWidth * wSrcHeight * bySrcFR))
		{
			return TRUE;
		}
		return FALSE;
	}
	
	//�ж������Ƿ����
	BOOL32 IsH264CapEqual(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// ����֡��>30, ֡�ʰ�ʵ��25�Ƚ�
		u8 byDstFR = GetUserDefFrameRate();
		if(!ISHDFORMAT(m_byResolution) && byDstFR > 30 )
		{
			byDstFR = 25;
		}
		
		if(!ISHDFORMAT(bySrcRes) && bySrcFR > 30 )
		{
			bySrcFR = 25;
		}
		
		if ((wDstWidth * wDstHeight * byDstFR) == (wSrcWidth * wSrcHeight * bySrcFR))
		{
			return TRUE;
		}
		return FALSE;
	}

    BOOL32 IsResLower(u8 bySrcRes, u8 byDstRes) const
    {
        if (!IsResMatched(bySrcRes, byDstRes))
        {
            return FALSE;
        }
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;

        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
        if (wSrcWidth < wDstWidth &&
            wSrcHeight < wDstHeight)
        {
            return TRUE;
        }
        return FALSE;
    }

	BOOL32 IsResLowerWithOutMatched(u8 bySrcRes, u8 byDstRes) const
    {
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;
		
        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
        if (wSrcWidth < wDstWidth &&
            wSrcHeight < wDstHeight)
        {
            return TRUE;
        }
        return FALSE;
    }
	// ����ֱ���֡�ʳ˻����Ƚϴ�С [2012/09/12 nizhijun]
	BOOL32 IsSrcCapLowerThanDst(u8 bySrcRes, u8 bySrcFrameRate, u8 byDstRes,u8 byDstFrameRate) const
    {
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;
		
        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
		u32 wSrcProduct = wSrcWidth*wSrcHeight*bySrcFrameRate;
		u32 wDstProduct = wDstWidth*wDstHeight*byDstFrameRate;
        if ( wSrcProduct < wDstProduct)
        {
            return TRUE;
        }
        return FALSE;
    }

	// ����ֱ��ʳ˻����Ƚϴ�С [1/16/2012 chendaiwei]
	BOOL32 IsResLowerInProduct(u8 bySrcRes, u8 byDstRes) const
    {
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;
		
        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
		u32 wSrcProduct = wSrcWidth*wSrcHeight;
		u32 wDstProduct = wDstWidth*wDstHeight;
        if ( wSrcProduct < wDstProduct)
        {
            return TRUE;
        }
        return FALSE;
    }

    BOOL32   operator ==( const TMcuVideoStreamCap & TMcuVideoStreamCap ) const
    {
        u8 byFrameRate;
        if (MCU_MEDIA_TYPE_H264 == TMcuVideoStreamCap.GetMediaType())
        {
            byFrameRate = TMcuVideoStreamCap.GetUserDefFrameRate() + MCU_VIDEO_FPS_USRDEFINED;
        }
        else
        {
            byFrameRate = TMcuVideoStreamCap.GetFrameRate();
        }
        if ((TMcuVideoStreamCap.GetMediaType() == m_byMediaType &&
            TMcuVideoStreamCap.GetResolution() == m_byResolution &&
            byFrameRate == m_byFrameRate &&
			TMcuVideoStreamCap.IsSupportHP() == IsSupportHP()) ||
            (TMcuVideoStreamCap.GetMediaType() == MCU_MEDIA_TYPE_NULL && m_byMediaType == MCU_MEDIA_TYPE_NULL))
        {
            return TRUE;
        }
        
        return FALSE;
    }

	// ������ӡ [12/12/2011 chendaiwei]
	void Print( void )
	{
	//	StaticLog("MediaType:%d  Res:%d  HP:%d  FPs:%d  BR:%d\n",
		//	GetMediaType(),GetResolution(),GetH264ProfileAttrb(),GetUserDefFrameRate(),GetMaxBitRate());
	}

private:
    void GetWHByRes(u8 byRes, u16 &wWidth, u16 &wHeight) const
    {
        wWidth = 0;
        wHeight = 0;
    
        switch(byRes)
        {
        case MCU_VIDEO_FORMAT_SQCIF_112x96:
            wWidth = 112;
            wHeight = 96;
            break;
        
        case MCU_VIDEO_FORMAT_SQCIF_96x80:
            wWidth = 96;
            wHeight = 80;
            break;
        
        case MCU_VIDEO_FORMAT_SQCIF:
            wWidth = 128;
            wHeight = 96;
            break;
        
        case MCU_VIDEO_FORMAT_QCIF:
            wWidth = 176;
            wHeight = 144;
            break;
        
        case MCU_VIDEO_FORMAT_CIF:
            wWidth = 352;
            wHeight = 288;
            break;
        
        case MCU_VIDEO_FORMAT_2CIF:
            wWidth = 352;
            wHeight = 576;
            break;
        
        case MCU_VIDEO_FORMAT_4CIF:
        
            //���ھ����ܲ��ſ��ǣ�����ȡ��ֵ
            wWidth = 704;
            wHeight = 576;
            break;
        
        case MCU_VIDEO_FORMAT_16CIF:
            wWidth = 1048;
            wHeight = 1152;
            break;
        
        case MCU_VIDEO_FORMAT_AUTO:
            //������
            break;
        
        case MCU_VIDEO_FORMAT_SIF:
            wWidth = 352;
            wHeight = 240;
            break;
        
        case MCU_VIDEO_FORMAT_2SIF:
            wWidth = 352;
            wHeight = 480;
            break;
        
        case MCU_VIDEO_FORMAT_4SIF:
            wWidth = 704;
            wHeight = 480;
            break;
        
        case MCU_VIDEO_FORMAT_VGA:
            wWidth = 640;
            wHeight = 480;
            break;
        
        case MCU_VIDEO_FORMAT_SVGA:
            wWidth = 800;
            wHeight = 600;
            break;
        
        case MCU_VIDEO_FORMAT_XGA:
            wWidth = 1024;
            wHeight = 768;
            break;

        case MCU_VIDEO_FORMAT_W4CIF:
            wWidth = 1024;
            wHeight = 576;
            break;

        case MCU_VIDEO_FORMAT_HD720:
            wWidth = 1280;
            wHeight = 720;
            break;

        case MCU_VIDEO_FORMAT_SXGA:
            wWidth = 1280;
            wHeight = 1024;
            break;

        case MCU_VIDEO_FORMAT_UXGA:
            wWidth = 1600;
            wHeight = 1200;
            break;

        case MCU_VIDEO_FORMAT_HD1080:
            wWidth = 1920;
            wHeight = 1088;
            break;
			//�Ǳ�ֱ��ʣ�1080p��ͼ��
		case MCU_VIDEO_FORMAT_1440x816:
			wWidth = 1440;
			wHeight = 816;
			break;
			
		case MCU_VIDEO_FORMAT_1280x720:
			wWidth = 1280;
			wHeight = 720;
			break;
			
		case MCU_VIDEO_FORMAT_960x544:
			wWidth = 960;
			wHeight = 544;
			break;
			
		case MCU_VIDEO_FORMAT_640x368:
			wWidth = 640;
			wHeight =368;
			break;
			
		case MCU_VIDEO_FORMAT_480x272:
			wWidth = 480;
			wHeight =272;
			break;
			
		case MCU_VIDEO_FORMAT_384x272:
			wWidth = 384;
			wHeight =272;
			break;

			//�Ǳ�ֱ��ʣ�720p��ͼ��
		case MCU_VIDEO_FORMAT_720_960x544:
			wWidth = 960;
			wHeight =544;
			break;
			
		case MCU_VIDEO_FORMAT_720_864x480:
			wWidth = 864;
			wHeight =480;
			break;
			
		case MCU_VIDEO_FORMAT_720_640x368:
			wWidth = 640;
			wHeight =368;
			break;
			
		case MCU_VIDEO_FORMAT_720_432x240:
			wWidth = 432;
			wHeight =240;
			break;
			
		case MCU_VIDEO_FORMAT_720_320x192:
			wWidth = 320;
			wHeight =192;
			break;
		case MCU_VIDEO_FORMAT_640x544:
			wWidth = 640;
			wHeight =544;
			break;
		case MCU_VIDEO_FORMAT_320x272:
			wWidth = 320;
			wHeight =272;
			break;
        default:
            break;
        }
        if ( 0 == wHeight || 0 == wWidth )
        {
            //StaticLog("[TMcuVideoStreamCap::GetWHByRes] unexpected res.%d, ignore it\n", byRes );
        }
        return;
    }

    BOOL32 IsResMatched(u8 bySrcRes, u8 byDstRes) const
    {
        BOOL32 bMatched = FALSE;
        if (IsResPresentation(bySrcRes) && IsResPresentation(byDstRes))
        {
            bMatched = TRUE;
        }
        else if (IsResLive(bySrcRes) && IsResLive(byDstRes))
        {
            bMatched = TRUE;
        }
        return bMatched;
    }
    
    BOOL32 IsResPresentation(u8 byRes) const
    {
        BOOL32 bPresentation = FALSE;
        
        switch(byRes)
        {
        case MCU_VIDEO_FORMAT_VGA:
        case MCU_VIDEO_FORMAT_SVGA:
        case MCU_VIDEO_FORMAT_XGA:
        case MCU_VIDEO_FORMAT_SXGA:
        case MCU_VIDEO_FORMAT_UXGA:
            bPresentation = TRUE;
            break;
        default:
            break;
        }
        return bPresentation;
    }
    
    BOOL32 IsResLive(u8 byRes) const 
    {
        BOOL32 bLive = FALSE;
        
        switch(byRes)
        {
        case MCU_VIDEO_FORMAT_CIF:
        case MCU_VIDEO_FORMAT_2CIF:
        case MCU_VIDEO_FORMAT_4CIF:
        case MCU_VIDEO_FORMAT_16CIF:
            
        case MCU_VIDEO_FORMAT_SIF:
        case MCU_VIDEO_FORMAT_2SIF:
        case MCU_VIDEO_FORMAT_4SIF:
            
        case MCU_VIDEO_FORMAT_W4CIF:
        case MCU_VIDEO_FORMAT_HD720:
        case MCU_VIDEO_FORMAT_HD1080:
            bLive = TRUE;
            break;
        //����������
        case MCU_VIDEO_FORMAT_AUTO:
        case MCU_VIDEO_FORMAT_SQCIF_112x96:
        case MCU_VIDEO_FORMAT_SQCIF_96x80:
            break;
        default:
            break;
        }
        return bLive;
    }


}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

// zw [06/27/2008] ��m_byAudioMediaType��װΪTMcuAudioStreamCap��������ΪTAudAACCap����
//������Ƶý���ʽ������(len:1)
struct TMcuAudioStreamCap
{
protected:
	u8 m_byAudioMediaType;
	
public:
	TMcuAudioStreamCap() { Clear(); }
	
	void Clear(void)
    {
        m_byAudioMediaType = MEDIA_TYPE_NULL;
    }
	
    void SetMediaType(u8 byAudioMediaType) { m_byAudioMediaType = byAudioMediaType; }	
    u8	 GetMediaType() const { return m_byAudioMediaType; }
}
PACKED
;


//ͬʱ�������ṹ(len:6)
struct TMcuSimCapSet
{
protected:
	TMcuVideoStreamCap  m_tVideoCap;
    TMcuAudioStreamCap  m_tAudioCap;
//	u8  m_byAudioMediaType;  

public:
    TMcuSimCapSet( void )	{ Clear(); }

	void SetVideoMediaType( u8 byMediaType ) { m_tVideoCap.SetMediaType(byMediaType); }
    u8   GetVideoMediaType( void ) const { return m_tVideoCap.GetMediaType(); }

	void SetVideoResolution( u8 byRes ) { m_tVideoCap.SetResolution(byRes); }
    u8   GetVideoResolution( void ) const { return m_tVideoCap.GetResolution(); }

	void SetVideoMaxBitRate( u16 wMaxRate ) { m_tVideoCap.SetMaxBitRate(wMaxRate); }
	u16  GetVideoMaxBitRate( void ) const { return m_tVideoCap.GetMaxBitRate(); }

    void SetVideoFrameRate(u8 byFrameRate) { m_tVideoCap.SetFrameRate(byFrameRate); }
    u8   GetVideoFrameRate(void) const { return m_tVideoCap.GetFrameRate(); }

	void SetVideoProfileType(emMcuProfileAttrb emProf) { m_tVideoCap.SetH264ProfileAttrb(emProf); }
    emMcuProfileAttrb   GetVideoProfileType(void) const { return m_tVideoCap.GetH264ProfileAttrb(); }

    // guzh [12/1/2007] �Զ���֡�ʵı���/��ȡ
    void SetUserDefFrameRate(u8 byActFrameRate) { m_tVideoCap.SetUserDefFrameRate(byActFrameRate); }
    BOOL32 IsFrameRateUserDefined() const {return m_tVideoCap.IsFrameRateUserDefined(); }
    u8   GetUserDefFrameRate(void) const { return m_tVideoCap.GetUserDefFrameRate(); }
    
    void SetAudioMediaType( u8 byAudioMediaType ) { m_tAudioCap.SetMediaType(byAudioMediaType);}
    u8   GetAudioMediaType( void ) const { return m_tAudioCap.GetMediaType(); }

    void SetVideoCap( TMcuVideoStreamCap &tVidCap ){ memcpy(&m_tVideoCap, &tVidCap, sizeof(TMcuVideoStreamCap)); }
    TMcuVideoStreamCap   GetVideoCap( void ) const { return m_tVideoCap; }
	
	BOOL32   operator ==( const TMcuSimCapSet & tSimCapSet ) const  //�ж��Ƿ����(ֻ�ж�����ͼ��)
	{
		if( GetVideoMediaType() == tSimCapSet.GetVideoMediaType() && 
			GetAudioMediaType() == tSimCapSet.GetAudioMediaType() &&
            GetVideoMediaType() != MEDIA_TYPE_NULL && 
            GetAudioMediaType() != MEDIA_TYPE_NULL)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
    
//     BOOL32 operator < (const TSimCapSet &tSimCapSet) //�ж�С��
//     {
//         if (tSimCapSet.IsNull())
//         {
//             return FALSE;
//         }
//         if (GetVideoMediaType() != tSimCapSet.GetVideoMediaType() /*&& 
// 			GetAudioMediaType() != tSimCapSet.GetAudioMediaType()*/)
//         {
//             //�������䣺��ƥ����ΪС��
//             return TRUE;
//         }
//         
//         u8 bySrcFrmRate = MEDIA_TYPE_H264 == GetVideoMediaType() ? GetUserDefFrameRate() : GetVideoFrameRate();
//         u8 byDstFrmRate = MEDIA_TYPE_H264 == tSimCapSet.GetVideoMediaType() ? tSimCapSet.GetUserDefFrameRate() : tSimCapSet.GetVideoFrameRate(); 
//         if (m_tVideoCap.IsResLower(GetVideoResolution(), tSimCapSet.GetVideoResolution()) ||
//             GetVideoMaxBitRate() < tSimCapSet.GetVideoMaxBitRate())
//         {
//             return TRUE;
//         }
// 
//         if((abs(bySrcFrmRate-byDstFrmRate) == 5) &&
//             (bySrcFrmRate == 30 || byDstFrmRate == 30))
//         {
//             return FALSE;
//         }
// 
//         if (bySrcFrmRate < byDstFrmRate)
//         {
//             return TRUE;
//         }
//         
//         return FALSE;
//     }
    
	BOOL32 operator < (const TMcuSimCapSet &tSimCapSet) const //�ж�С��
	{
		if (MEDIA_TYPE_NULL != GetVideoMediaType() && 
			MEDIA_TYPE_NULL != tSimCapSet.GetVideoMediaType() &&
			GetVideoMediaType() != tSimCapSet.GetVideoMediaType())
		{
			return TRUE;
		}
		else if(m_tVideoCap.IsResLower(GetVideoResolution(), tSimCapSet.GetVideoResolution()))
		{
			return TRUE;
		}
		else if (GetVideoMaxBitRate() < tSimCapSet.GetVideoMaxBitRate())
		{
			return TRUE;
		}
		else
		{
			if (MEDIA_TYPE_H264 == GetVideoMediaType() && 
				MEDIA_TYPE_H264 == tSimCapSet.GetVideoMediaType())
			{
				if ( m_tVideoCap.GetH264ProfileAttrb() != tSimCapSet.m_tVideoCap.GetH264ProfileAttrb() )
				{
					return TRUE;
				}

				//Դ������h264 cif 30fps Ŀ������:h264 cif 25fps ��������
				if(VIDEO_FORMAT_CIF == GetVideoResolution() && VIDEO_FORMAT_CIF == tSimCapSet.GetVideoResolution() &&
				   GetUserDefFrameRate() == 25 && tSimCapSet.GetUserDefFrameRate() == 30)
				{
					return FALSE;
				}
				
// 				//Ŀǰ��ʱ��720 60 ���Դ��1080 30
// 				if ( GetVideoResolution() != tSimCapSet.GetVideoResolution() &&
// 					 GetUserDefFrameRate() < tSimCapSet.GetUserDefFrameRate() 
// 					 )
// 				{
// 					return TRUE;
// 				}

				return m_tVideoCap.IsH264CapLower(tSimCapSet.GetVideoResolution(), tSimCapSet.GetUserDefFrameRate());
			}
			else
			{
				if (GetVideoFrameRate() < tSimCapSet.GetVideoFrameRate())
				{
					return TRUE;
				}
			}
		}
		return FALSE;
	}

    BOOL32 operator != (const TSimCapSet &tSim)
    {
        if(tSim.IsNull())
        {
            return FALSE;
        }
        if(GetVideoMediaType() != tSim.GetVideoMediaType())
        {
            return TRUE;
        }
        if(m_tVideoCap.IsResLower(GetVideoResolution(), tSim.GetVideoResolution()) ||
           GetVideoMaxBitRate() < tSim.GetVideoMaxBitRate())
        {
            return TRUE;
        }
        u8 bySrcFrmRate = MEDIA_TYPE_H264 == GetVideoMediaType() ? GetUserDefFrameRate() : GetVideoFrameRate();
        u8 byDstFrmRate = MEDIA_TYPE_H264 == tSim.GetVideoMediaType() ? tSim.GetUserDefFrameRate() : tSim.GetVideoFrameRate(); 
        
        if((abs(bySrcFrmRate-byDstFrmRate) == 5) &&
           (bySrcFrmRate == 30 || byDstFrmRate == 30))
        {
            return FALSE;
        }
        if(bySrcFrmRate != byDstFrmRate)
        {
            return TRUE;
        }
        return FALSE;
    }
    
	BOOL32   IsNull( void ) const
	{
		if(	GetVideoMediaType() == MEDIA_TYPE_NULL && GetAudioMediaType() == MEDIA_TYPE_NULL )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	void  Clear( void )
	{
        m_tVideoCap.Clear();
        SetAudioMediaType(MEDIA_TYPE_NULL);
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//���崫���ַ�ṹ(len:6)
struct TMcuTransportAddr
{
public:
	u32   		m_dwIpAddr;		//IP��ַ, ������
	u16 		m_wPort;		//�˿ں�, ������
public:
	void   SetNull(void)
	{
		m_dwIpAddr = 0;
		m_wPort = 0;
	}
	
	// [6/2/2011 liuxu] ����ж�
	BOOL32 IsNull()
	{
		return GetIpAddr() == 0 || GetIpAddr() == ~0 || GetPort() == 0;
	}

    void   SetNetSeqIpAddr(u32    dwIpAddr){ m_dwIpAddr = dwIpAddr; } 
    u32    GetNetSeqIpAddr( void ) const { return m_dwIpAddr; }
    void   SetIpAddr(u32    dwIpAddr){ m_dwIpAddr = htonl(dwIpAddr); } 
    u32    GetIpAddr( void ) const { return ntohl(m_dwIpAddr); }
    void   SetPort(u16  wPort){ m_wPort = htons(wPort); } 
    u16    GetPort( void ) const { return ntohs(m_wPort); }
	BOOL32 operator == (const TMcuTransportAddr &tTransportAddr)
	{
		//[2011//11/09/zhangli]��ֵΪ��������ֵΪ��������ֵ�ĳ�������
		//return m_dwIpAddr == tTransportAddr.GetIpAddr() && m_wPort == tTransportAddr.GetPort() ;
		return GetIpAddr() == tTransportAddr.GetIpAddr() && GetPort() == tTransportAddr.GetPort();
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

// [pengjie 2010/9/11] ��ش��߼�������һ�������ݳ�Ա��Ϊ˽�еĲ��ٱ�¶���ⲿ���ⲿֱ�ӵ��ӿ�
struct TSpyResource         // ��ش�������Ϣ (len: 36)
{
public:
	TMCUMt		      m_tSpy;		     // �ش�Դ(Mt)
	TMcuSimCapSet     m_TMcuSimCapSet;     // ��Ӧ�ش�ʵ����������� ( �ûش�Դ ���ش����� �ش�Ŀ�Ķ˵� ���� )
	TMcuTransportAddr m_tSpyAddr;       // ��Ӧ�ش�ʵ��Ļش�ͨ����ַ��Ϣ
	TMcuTransportAddr m_tVideoRtcpAddr; // [liu lijiu][20100823]��¼�¼�����RTCP�ĵ�ַ
	TMcuTransportAddr m_tAudioRtcpAddr; // [liu lijiu][20100823]��¼�¼��������RTCP�ĵ�ַ
	u8		       m_bySpyMode;	     // AUDIO,VIDEO,BOTH
	u8             m_byReserved1;    // Ԥ���ֶ�
	u32            m_dwReserved2;    // Ԥ���ֶ�
	
public:
	TSpyResource()
	{
		Clear();
	}
	
	u16 GetSpyChnnl()
	{
		return ( m_tSpyAddr.GetPort()  - CASCADE_SPY_STARTPORT ) / PORTSPAN;
	}
	
	void Clear( void )
	{
		memset( this, 0, sizeof(TSpyResource) );
		m_TMcuSimCapSet.Clear();
	}
	
	TMCUMt GetSpyMt( void ) const { return m_tSpy; }
	void SetSpyMt( const TMCUMt &tSpyMt ) { m_tSpy = tSpyMt; }
	
	TMcuSimCapSet GetSimCapset( void ) const { return m_TMcuSimCapSet; }
	void SetSimCapset( const TMcuSimCapSet &tSimCapset ) { m_TMcuSimCapSet = tSimCapset; }
	
	TMcuTransportAddr GetSpyAddr( void ) { return m_tSpyAddr; }
	void SetSpyAddr( const TMcuTransportAddr &tSpyAddr ) { m_tSpyAddr = tSpyAddr; }
	
	u8 GetSpyMode( void ) { return m_bySpyMode; }
	void SetSpyMode( const u8 bySpyMode ) { m_bySpyMode = bySpyMode; }
	
	void SetVidSpyBackRtcpAddr(TMcuTransportAddr tVideoRtcpAddr) { m_tVideoRtcpAddr = tVideoRtcpAddr; }
	TMcuTransportAddr GetVidSpyBackRtcpAddr(void) const { return m_tVideoRtcpAddr; }
	
	void SetAudSpyBackRtcpAddr(TMcuTransportAddr tAudioRtcpAddr) { m_tAudioRtcpAddr = tAudioRtcpAddr; }
	TMcuTransportAddr GetAudSpyBackRtcpAddr(void) const { return m_tAudioRtcpAddr; }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMcuPreReleaseMtInfo
{
	TMCUMt         m_TMCUMt;
	u8          m_byCasLevel; //����뱾�����ն������������е���Ծ�ļ�����
	u8          m_abyMtIdentify[MAX_CASCADELEVEL]; //��Ӧ�������ն˵ı�ʶ 
	u8 m_byCanReleaseMode;	//���ͷ�ģʽ
private:
	s16 m_swCount;			//�����mt��Ϣ�Ǳ����µ�mcu��Ϣ��С��0 ,����Ϊ0
public:
	u8 m_byIsNeedRelease;	//���ظ��ϼ�mcu�жϸÿ��ͷ��ն������Ƿ���Ҫ�ͷ�
	u8 m_byCanReleaseVideoDstNum;//�����ͷŵ���ƵĿ����
	u8 m_byCanReleaseAudioDstNum;//�����ͷŵ���ƵĿ����
	u8 m_byIsReuseBasChl;//�Ƿ����ÿ��ͷ��ն���ռ�õ�basͨ��
	//==MODE_VIDEO��Ƶbas�ɸ��ã�==MODE_AUDIO��Ƶbas�ɸ��ã�MODE_BOTH����Ƶbas���ɸ���
	
public:
	TMcuPreReleaseMtInfo()
	{
		memset( this, 0, sizeof(TMcuPreReleaseMtInfo) );
	}
	
	//����������[3/7/2012 chendaiwei]
	void SetCount( s16 swCount )
	{
		m_swCount = htons(swCount);
	}
	
	//����������
	s16 GetCount( void ) const
	{
		return ntohs(m_swCount);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpySwitchInfo     // ѡ����صĶ�ش���ʼ��Ϣ
{
	//u8    m_byMcInstId;   // ĳ����ص�id
	u8    m_byDstChlIdx;  // Ŀ��ͨ������
	u8    m_bySrcChlIdx;  // Դͨ��������
	TMCUMtNoConstruct   m_tDstMt;       // Ŀ���նˣ���Ϊ��ؼ�أ�Ŀ�Ķ�Ϊ�գ�
	
private:
	u32   m_dwMcIp;       //���IP
	u32   m_dwMcSSRC;    //��������
public:
	void SetMcIp(u32 dwMcIp)
	{
		m_dwMcIp = htonl(dwMcIp);
		return;
	}
	
	u32 GetMcIp(void) const
	{
		return ntohl(m_dwMcIp);
	}
	
	void SetMcSSRC(u32 dwMcSSRC)
	{
		m_dwMcSSRC = htonl(dwMcSSRC);
		return;
	}
	
	u32 GetMcSSRC(void) const
	{
		return ntohl(m_dwMcSSRC);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

typedef TMCUMtNoConstruct TEqpNoConstruct;

struct TSpyHduInfo     // ���������ǽ��صĶ�ش���ʼ��Ϣ
{
	u8    m_bySrcMtType;  // ����ǽԴͨ����Ա����
	u8    m_bySchemeIdx;  // Ԥ��������
	u8    m_byDstChlIdx;  // HDUĿ��ͨ������
	TEqpNoConstruct  m_tHdu;         // ������Ϣ
private:
	u8    m_bySubChnIdx;	//HDU�໭����ͨ��
public:
	void SetSubChnIdx(u8 bySubChnIdx)
	{
		m_bySubChnIdx = bySubChnIdx;
	}
	u8 GetSubChnIdx(void) const
	{
		return m_bySubChnIdx;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyPollInfo     // ��ѯ��صĶ�ش���ʼ��Ϣ
{
	u16   m_wKeepTime;        //�ն���ѯ�ı���ʱ�� ��λ:��(s)
	u8    m_byPollingPos;        //�ն���ѯ�Ĵ���
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyTVWallInfo     // ������ǽ��صĶ�ش���ʼ��Ϣ
{
	u8    m_bySrcMtType;  // ����ǽԴͨ����Ա����
	u8    m_bySchemeIdx;  // Ԥ��������
	u8    m_byDstChlIdx;  // TVWallĿ��ͨ������
	TEqpNoConstruct  m_tTvWall;      // ������Ϣ
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyVmpInfo //����ϳ���صĶ�ش���Ϣ
{
	//	u8		m_byRes;	//�ֱ�������
	u8		m_byPos;	//ͨ��λ��
	//	u8		m_byKeepOrgRes;	//������ʹ�¼������˷ֱ���(�����keda��)���ϼ����ǿ���������ȫ�ֱ��ʽ�
    u8		m_byMemberType;     //����ϳɳ�Ա����,�μ�vccommon.h�л���ϳɳ�Ա���Ͷ���
    u8		m_byMemStatus;      //��Ա״̬(MT_STATUS_CHAIRMAN, MT_STATUS_SPEAKER, MT_STATUS_AUDIENCE)
	TEqpNoConstruct    m_tVmp;             // ����ϳ�����
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyRollCallInfo     // ��ش����������Ϣ
{
	TMCUMtNoConstruct m_tCaller;        // ������
	TMCUMtNoConstruct m_tOldCaller;     // �ϵĵ�����
	TMCUMtNoConstruct m_tOldCallee;     // �ϵı������� 
	//u8			   m_byMcInstId;   // ĳ����ص�id
private:
	u32   m_dwMcIp;       //���IP
	u32   m_dwMcSSRC;     //��������
public:
	void SetMcIp(u32 dwMcIp)
	{
		m_dwMcIp = htonl(dwMcIp);
		return;
	}
	
	u32 GetMcIp(void) const
	{
		return ntohl(m_dwMcIp);
	}
	
	void SetMcSSRC(u32 dwMcSSRC)
	{
		m_dwMcSSRC = htonl(dwMcSSRC);
		return;
	}
	
	u32 GetMcSSRC(void) const
	{
		return ntohl(m_dwMcSSRC);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// size = 11
struct TMcuRecStartPara
{
protected:
    u8   m_byRecMode;         //¼��ģʽ
    u8   m_byPublishMode;     //����ģʽ
    u8   m_byPublishLevel;    //�������
    u8   m_byIsRecLowStream;  //�Ƿ�¼��������
    u8   m_byIsRecMainVideo;  //�Ƿ�¼����ʽ��Ƶ����
    u8   m_byIsRecMainAudio;  //�Ƿ�¼����ʽ��Ƶ����
    u8   m_byIsRecDStream;    //�Ƿ�¼˫��
	u16  m_wRecBitrate;       //¼������
    u16  m_wRecBitrateSec;    //¼��˫������
}
/*
#ifndef WIN32
__attribute__((packed))
#endif
*/
PACKED
;

#define MCU_KDV_MAX_PATH            (u16)256

struct TMcuSpyRecInfo     //¼���·��
{
	TMcuRecStartPara m_tRecPara;
	u8   m_byRecMode;                 // 0����¼��1�ն�¼��
	TEqpNoConstruct m_tRec;                      // ¼�������           
	s8   m_szRecFullName[MCU_KDV_MAX_PATH];   // ¼������·��
	u16  m_wSerialNO;				  // �ظ�mcs����ˮ��
	//u8   m_byMcInstId;				  // ĳ����ص�id
private:
	u32   m_dwMcIp;       //���IP
	u32   m_dwMcSSRC;     //��������
public:
/*	TMcuSpyRecInfo()
	{
		memset(this, 0, sizeof(TMcuSpyRecInfo));
	}
*/
	void SetMcIp(u32 dwMcIp)
	{
		m_dwMcIp = htonl(dwMcIp);
		return;
	}
	
	u32 GetMcIp(void) const
	{
		return ntohl(m_dwMcIp);
	}
	
	void SetMcSSRC(u32 dwMcSSRC)
	{
		m_dwMcSSRC = htonl(dwMcSSRC);
		return;
	}
	
	u32 GetMcSSRC(void) const
	{
		return ntohl(m_dwMcSSRC);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpySwitchDstInfo
{
	//u8				m_byMcInstId;   // ĳ����ص�id
	u8				m_bySrcChnnl;		//Դͨ���ţ������ն�Ŀǰֻ��0�����������ж���ѡ��
	TMcuTransportAddr	m_tDstVidAddr;		//Ŀ����Ƶ��ip��port
	TMcuTransportAddr  m_tDstAudAddr;		//Ŀ����Ƶ��ip��port ��ĿǰVid��Aud��Ip����ͬ�ģ���port��ͬ��
private:
	u32   m_dwMcIp;       //���IP
    u32   m_dwMcSSRC;
public:
	void SetMcIp(u32 dwMcIp)
	{
		m_dwMcIp = htonl(dwMcIp);
		return;
	}
	
	u32 GetMcIp(void) const
	{
		return ntohl(m_dwMcIp);
	}
	
	void SetMcSSRC(u32 dwMcSSRC)
	{
		m_dwMcSSRC = htonl(dwMcSSRC);
		return;
	}
	
	u32 GetMcSSRC(void) const
	{
		return ntohl(m_dwMcSSRC);
	}
}

#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


union USpyInfo
{
	TSpySwitchInfo   m_tSpySwitchInfo;   // ѡ���������Ϣ
	TSpyHduInfo      m_tSpyHduInfo;      // ���������ǽ�������Ϣ
	TSpyPollInfo     m_tSpyPollInfo;     // ��ѯ�����Ϣ
	TSpyTVWallInfo   m_tSpyTVWallInfo;   // ������ǽ�������Ϣ
	TSpyVmpInfo	     m_tSpyVmpInfo;		 // VMP��ض�����Ϣ
	TSpyRollCallInfo m_tSpyRollCallInfo; // ���������Ϣ
	TMcuSpyRecInfo		 m_TMcuSpyRecInfo;		 //¼���
	TSpySwitchDstInfo	m_tSpySwitchDstInfo;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// [pengjie 2010/9/11] ��ش��߼�����
struct TPreSetInReq            // �ش���ʼ��Ϣ
{
	//protected: ��һ�����ٱ�¶��Ա��Ϣ
private:
	u32 m_dwEvId;             // ��¼�ڽ��лش�����ǰ������Ӧ��ִ�е���Ϣ����ı䷢���ˣ��ն�ѡ���ȣ�
public:
	u8  m_bySpyMode;          // ����Ļش�ģʽ
    TSpyResource m_tSpyMtInfo;    // ����ش����ն���Ϣ
	USpyInfo    m_tSpyInfo;   // ��ش���ҵ����ص�һЩ��Ҫ����Ϣ
	TMcuPreReleaseMtInfo m_tReleaseMtInfo;
	
public:
	TPreSetInReq()
	{
		memset( this, 0, sizeof(TPreSetInReq) );
	}
	
	//���ô���������[3/7/2012 chendaiwei]
	void SetEvId( u32 dwEvId)
	{
		m_dwEvId = htonl(dwEvId);
	}
	
	//��ȡ����������
	u32 GetEvId( void ) const
	{
		return ntohl(m_dwEvId);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPreSetInRsp			// PreSetIn Ӧ����Ϣ
{
	// [pengjie 2010/7/30] TPreSetInReq �ṹ����, ��Ҫ�����ش�Ŀ�Ķ���Ϣ
	TPreSetInReq m_tSetInReqInfo; // ��¼�ϼ�Ҫ��Ļش������Ϣ
	u8  m_byRspSpyMode;		// �¼������ܴﵽ�Ļش�ģʽ(BOTH/V/A )
	
private:
	u32	m_dwVidSpyBW;		// �ش���Ƶ��ռ�ö��ٴ���
	u32	m_dwAudSpyBW;		// �ش���Ƶ��ռ�ö��ٴ���
	// 	TTransportAddr m_tAudBackRtcp;//[liu lijiu][20100901]��¼��������Ϊ�¼�����������ƵRTCP�˿�
	// 	TTransportAddr m_tVidBackRtcp;//[liu lijiu][20100901]��¼��������Ϊ�¼�����������ƵRTCP�˿�
	
public:
	TPreSetInRsp()
	{
		memset( this, 0, sizeof(TPreSetInRsp) );
	}
	
	void SetVidSpyRtcpAddr(TMcuTransportAddr tVideoRtcpAddr)
	{
		m_tSetInReqInfo.m_tSpyMtInfo.SetVidSpyBackRtcpAddr( tVideoRtcpAddr );
	}
	void SetAudSpyRtcpAddr(TMcuTransportAddr tAudioRtcpAddr)
	{
		m_tSetInReqInfo.m_tSpyMtInfo.SetAudSpyBackRtcpAddr( tAudioRtcpAddr );
	}
	TMcuTransportAddr GetVidSpyRtcpAddr(void) const
	{
		return m_tSetInReqInfo.m_tSpyMtInfo.GetVidSpyBackRtcpAddr();
	}
	TMcuTransportAddr GetAudSpyRtcpAddr(void) const
	{
		return m_tSetInReqInfo.m_tSpyMtInfo.GetAudSpyBackRtcpAddr();
	}
	
	//������������� [3/7/2012 chendaiwei]
	void SetVidSpyBW( u32 dwSpyBW )
	{
		m_dwVidSpyBW = htonl(dwSpyBW);
	}
	
	//�������������
	void SetAudSpyBW( u32 dwSpyBw )
	{
		m_dwAudSpyBW = htonl(dwSpyBw);
	}
	
	//����������  [3/7/2012 chendaiwei]
	u32 GetVidSpyBW ( void )
	{
		return ntohl(m_dwVidSpyBW);
	}
	
	//����������
	u32 GetAudSpyBW ( void )
	{
		return ntohl(m_dwAudSpyBW);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


/*====================================================================
������      : GetNormalRes
����        : ���ݿ��,���һ��ͨ�õķֱ���,���ֱ�����
�㷨ʵ��    ��
����ȫ�ֱ�����
�������˵����u16 wResW ��,u16 wResH ��
����ֵ˵��  ��v4r7ǰmcu֧�ֵķֱ���
----------------------------------------------------------------------
�޸ļ�¼    ��
��  ��      �汾        �޸���        �޸�����
09/13/2012              yanghuaizhi     ����
====================================================================*/
u8 GetNormalRes(u16 wResW, u16 wResH)
{
	// ֧�ֵ��ֱ��ʵ�ͨ�÷ֱ����б�,��mcu֧��
	u8 abyAcceptableRes[MCU_MAXNUM_ACCEPTABLE_RES] = 
	{
		MCU_VIDEO_FORMAT_HD1080,
			MCU_VIDEO_FORMAT_1440x816,
			MCU_VIDEO_FORMAT_HD720,
			MCU_VIDEO_FORMAT_960x544,
			MCU_VIDEO_FORMAT_720_864x480,	//TS Vmp ����Ҫ�÷ֱ���
			MCU_VIDEO_FORMAT_4CIF,
			MCU_VIDEO_FORMAT_4SIF,
			MCU_VIDEO_FORMAT_640x368,
			MCU_VIDEO_FORMAT_480x272,
			MCU_VIDEO_FORMAT_CIF,
			MCU_VIDEO_FORMAT_720_432x240,	// need by 8000G vmp 
			MCU_VIDEO_FORMAT_720_320x192,	// need by 8000G vmp
			MCU_VIDEO_FORMAT_QCIF,			//old vmp ���ܻ���ҪQCIF
			MCU_VIDEO_FORMAT_2CIF
	}; 
	
	u8 byExistRes = MCU_VIDEO_FORMAT_INVALID;	//�Ѵ��ڷֱ���
	u8 bySuitableRes = MCU_VIDEO_FORMAT_INVALID;	//��ӽ��ķֱ���,��߳˻�С�ڵ��ڴ˷ֱ��ʵ�����
	u16 wWidth = 0;
	u16 wHeight = 0;
	for(u8 byLoop = 0; byLoop < MCU_MAXNUM_ACCEPTABLE_RES; byLoop ++)
	{
		if( abyAcceptableRes[byLoop] == 0 )
		{
			break;
		}
		GetWHByRes( abyAcceptableRes[byLoop], wWidth, wHeight);
		// ���б����ж���,ֱ��ʹ��
		if (MCU_WHEQUAL == WHCmp (wWidth, wHeight, wResW, wResH))
		{
			byExistRes = abyAcceptableRes[byLoop];
			break;
		}
		// ��߳ɼ�С�ڴ˷ֱ���,������ӽ����Ǹ�����
		if (wWidth * wHeight < wResW * wResH)
		{
			if (MCU_VIDEO_FORMAT_INVALID == bySuitableRes)
			{
				bySuitableRes = abyAcceptableRes[byLoop];
			}
		}
	}
	
	// �д��ڵķֱ���,���ش��ڵ�,����,���غ��ʵ�
	if (MCU_VIDEO_FORMAT_INVALID != byExistRes)
	{
		return byExistRes;
	}
	else
	{
		return bySuitableRes;
	}
}



const u16 EV_MCUMCU_STD_BGN =  25402;
const u16 EV_MCUMCU_KDV_BGN =  25953;

//�����������缶����״̬֪ͨ����Ϣ�壺TMCUMt �� u8 byMode ( emAgreed )
OSPEVENT( MCU_MCU_SPEAKSTATUS_NTF,			EV_MCUMCU_STD_BGN + 68 ); // 25470

/************************************************************************/
/* �Զ��� ������ش���Ϣ                                                */
/************************************************************************/
//mcu�Ƿ�֧�ֶ�ش�������̽��Ϣ,u32 �ش�����
OSPEVENT(MCU_MCU_MULTSPYCAP_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 1 );

//�ϼ�mcu�����¼�mcu��Ҫ���м�����ش���setin ǰ��׼������
//�¼�mcu���ݴ��ж��Լ��Ƿ��ܻش����������¼��ܴ����ն˻ش����ʣ�
//��ϢӦ������Ҫ�ش����նˣ��ش���mode(AUDIO��VIDEO��BOTH)���ش���ý���ʽ�����ʡ�֡��
OSPEVENT(MCU_MCU_PRESETIN_REQ,	    	     EV_MCUMCU_KDV_BGN + 2 ); 
//�ϼ�������SMCU����ACK/NACK, �ж����ܷ����㹻����������һ��spy,��Ϣ��
//�����¼�mcu��������ش�ͨ����Ҫ�Ĵ����¼��ն��Ƿ�֧�ֵ��ֱ��ʵı�־
OSPEVENT(MCU_MCU_PRESETIN_ACK,	    	     EV_MCUMCU_KDV_BGN + 3 );
OSPEVENT(MCU_MCU_PRESETIN_NACK,	    	     EV_MCUMCU_KDV_BGN + 4 );

//֪ͨ�¼�mcu���ϼ����Խ�����ش������Ĵ���
OSPEVENT(MCU_MCU_SPYCHNNL_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 5 );

//֪ͨ�¼�mcu���ϼ�mcu�����㣬���ܽ��м�����ش�
OSPEVENT(MCU_MCU_REJECTSPY_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 6 );

//�ϼ�mcu�����¼����ͷ�һ·������Ƶ�ش�ͨ����CMD�����ջش�ͨ��
OSPEVENT(MCU_MCU_BANISHSPY_CMD,	    	     EV_MCUMCU_KDV_BGN + 7 );

// �¼�mcu�����ϼ����ͷ�һ·������Ƶ�ش�ͨ����֪ͨ���ϼ��յ����ͷ��Լ���Ӧ��������Ƶ�ش�ͨ����Դ
//lukunpeng 2010/06/10 �������������ϼ������¼�����ռ��������ʲ���Ҫ��ͨ���¼�֪ͨ�ϼ�
//OSPEVENT(MCU_MCU_BANISHSPY_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 8 );

// ������ش��ؼ�֡������Ϣ����Ϣ��Ϊ��u8 byMode + TMCUMt  (����Ƶģʽ + ����ƵԴ)
OSPEVENT(MCU_MCU_SPYFASTUPDATEPIC_CMD,	     EV_MCUMCU_KDV_BGN + 9 );

//֪ͨ�Է�MCU�Լ�ĳһ����ֱ���ն�״̬,��Ϣ��TMcu
OSPEVENT(MCU_MCU_MTSTATUS_NOTIF,			EV_MCUMCU_STD_BGN + 95 );



//////////////////////////////////////////////////////////////////////////
//�����
const u16     ERR_MCU_BGN = 20001;
#define DefineError(err, num )   \
const u16 err = num;

//���鲻֧�ֶ�ش�
DefineError( ERR_MCU_CONFNOTSUPPORTMULTISPY				 , ERR_MCU_BGN + 1738)
//����ش���������
DefineError( ERR_MCU_CONFSNDBANDWIDTHISFULL				 , ERR_MCU_BGN + 1739)
//��������������
DefineError( ERR_MCU_CASDBASISNOTENOUGH					 , ERR_MCU_BGN + 1740)










#endif // _h_umssipmcudef_h__