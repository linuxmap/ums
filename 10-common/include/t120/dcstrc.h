/*****************************************************************************
ģ����      : ���ݻ���ϵͳ��ģ��
�ļ���      : dcstrc.h
����ļ�    : ��
�ļ�ʵ�ֹ���: ���ݻ���ϵͳ��ģ�鹲�õĽṹ�����ʵ��
����        : ����
�汾        : 4.0
-----------------------------------------------------------------------------
�޸ļ�¼:
����(D/M/Y)     �汾     �޸���      �޸�����
16/08/2005      0.1      ����        ��V3.6��ֲ
******************************************************************************/

#ifndef _DCSTRC_H
#define _DCSTRC_H

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WIN32
#include "ptlib.h"
#endif

#include "dccommon.h"
#include <vector>

#ifdef WIN32
    #pragma pack( push )
    #pragma pack( 1 )
#else
    #include<sys/types.h>
    #include<sys/socket.h>
    #include <math.h>
    #define LPSTR   char *
    #define LPCSTR  const char *
#endif

typedef enum
{
    enum_MtInvited,
    enum_MtCallIn,
    enum_MtRemote
}enum_ConfMtType;


typedef enum
{
    enum_Mcu,
    enum_Mt
}enum_DeviceType;


#ifndef _KDC_INTE_TEST_

//����Žṹ
struct CConfId
{
protected:
	u8  	m_abyConfId[16];

public:
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
    u8   CConfId::GetConfId( u8   * pbyConfId, u8   byBufLen ) const
    {
		u16 wTempLen = sizeof(m_abyConfId);
		u8 byLen = wTempLen < byBufLen ? (u8)wTempLen : byBufLen ;
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
    void GetConfIdString( LPSTR lpszConfId, u8   byBufLen ) const
    {
        u8	byLoop;
        
        for( byLoop = 0; byLoop < sizeof( m_abyConfId ) && byLoop < ( byBufLen - 1 ) / 2; byLoop++ )
        {
            sprintf( lpszConfId + byLoop * 2, "%.2x", m_abyConfId[byLoop] );
        }
        lpszConfId[byLoop * 2] = '\0';
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
    void CConfId::CreateConfId( void )
    {
        struct tm	*ptmCurTime;
        time_t		tCurTime = time( NULL );
        u8	byTemp;
        u16	wTemp;
        
        memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
        
        //get current time
        ptmCurTime = localtime( &tCurTime );
        //year
        wTemp = (u16)(ptmCurTime->tm_year + 1900);
        memcpy( m_abyConfId, &wTemp, sizeof( u16 ) );
        //month
        byTemp = (u8)(ptmCurTime->tm_mon + 1);
        memcpy( m_abyConfId + 2, &byTemp, sizeof( u8 ) );
        //day
        byTemp = (u8)(ptmCurTime->tm_mday);
        memcpy( m_abyConfId + 3, &byTemp, sizeof( u8 ) );
        //hour
        byTemp = (u8)(ptmCurTime->tm_hour);
        memcpy( m_abyConfId + 4, &byTemp, sizeof( u8 ) );
        //minute
        byTemp = (u8)(ptmCurTime->tm_min);
        memcpy( m_abyConfId + 5, &byTemp, sizeof( u8 ) );
        //second
        byTemp = (u8)(ptmCurTime->tm_sec);
        memcpy( m_abyConfId + 6, &byTemp, sizeof( u8 ) );
        //msec
        wTemp = 0;
        memcpy( m_abyConfId + 7, &wTemp, sizeof( u16 ) );
        
        //rand
        wTemp = (u16)rand();
        memcpy( m_abyConfId + 9, &wTemp, sizeof( u16 ) );
    }
    
/*====================================================================
    ������      ��SetConfId
    ����        �����û��������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CConfId & cConfId, ��������
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
    void SetConfId( const CConfId & cConfId )
    {
        cConfId.GetConfId( m_abyConfId, sizeof( m_abyConfId ) );
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
    u8   SetConfId( const u8   * pbyConfId, u8   byBufLen )
    {
		u16 wTempLen = sizeof( m_abyConfId );
    	u8 bySize = wTempLen < byBufLen ? (u8)wTempLen : byBufLen ;
        
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
    u8   SetConfId( LPCSTR lpszConfId )
    {
        LPCSTR	lpszTemp = lpszConfId;
        char	achTemp[3], *lpszStop;
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
    BOOL IsNull( void ) const
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
    void SetNull( void )
    {
        memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
    }


/*====================================================================
    ������      ��operator==
    ����        ������������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����const CConfId & cConfId, ��������
    ����ֵ˵��  ����ȷ���TRUE�����򷵻�FALSE
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/31    1.0         LI Yi         ����
====================================================================*/
    BOOL operator == ( const CConfId & cConfId ) const         
    {
        u8	abyTemp[sizeof( m_abyConfId )];
        
        cConfId.GetConfId( abyTemp, sizeof( abyTemp ) );
        if( memcmp( abyTemp, m_abyConfId, sizeof( m_abyConfId ) ) == 0 )
            return( TRUE );
        else
            return( FALSE );
    }
    
	void Print( void )
	{
		char achBuf[33];
		achBuf[32] = 0;
		GetConfIdString( achBuf, 33 );
		OspPrintf( TRUE, FALSE, "%s", achBuf);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifdef SERV_MSGHEAD_LEN
    #undef SERV_MSGHEAD_LEN
#endif
#define      SERV_MSGHEAD_LEN             (u16)0x30    //��Ϣͷ����

#endif

//ҵ����Ϣ�ӿڳ�������
const u16 SERV_MSGHEAD_SRIALNO_OFFSET	= 0;	//��ˮ��ƫ����
const u16 SERV_MSGHEAD_SRIALNO_LEN		= 2;	//��ˮ���ֽ���
const u16 SERV_MSGHEAD_SRCMCUID_OFFSET	= SERV_MSGHEAD_SRIALNO_OFFSET + SERV_MSGHEAD_SRIALNO_LEN;	//ԴMCU��ƫ����
const u16 SERV_MSGHEAD_SRCMCUID_LEN		= 2;	//ԴMCU���ֽ���
const u16 SERV_MSGHEAD_SRCMTID_OFFSET	= SERV_MSGHEAD_SRCMCUID_OFFSET + SERV_MSGHEAD_SRCMCUID_LEN;	//ԴMT��ƫ����
const u16 SERV_MSGHEAD_SRCMTID_LEN		= 1;	//ԴMT���ֽ���
const u16 SERV_MSGHEAD_SRCSSNID_OFFSET	= SERV_MSGHEAD_SRCMTID_OFFSET + SERV_MSGHEAD_SRCMTID_LEN;	//ԴSESSION��ƫ����
const u16 SERV_MSGHEAD_SRCSSNID_LEN	= 1;		//ԴSESSION���ֽ���
const u16 SERV_MSGHEAD_DSTMCUID_OFFSET	= SERV_MSGHEAD_SRCSSNID_OFFSET + SERV_MSGHEAD_SRCSSNID_LEN;	//Ŀ��MCU��ƫ����
const u16 SERV_MSGHEAD_DSTMCUID_LEN		= 2;	//MCU���ֽ���
const u16 SERV_MSGHEAD_DSTMTID_OFFSET	= SERV_MSGHEAD_DSTMCUID_OFFSET + SERV_MSGHEAD_DSTMCUID_LEN;	//Ŀ��MT��ƫ����
const u16 SERV_MSGHEAD_DSTMTID_LEN		= 1;	//MT���ֽ���
const u16 SERV_MSGHEAD_CHNINDEX_OFFSET	= SERV_MSGHEAD_DSTMTID_OFFSET + SERV_MSGHEAD_DSTMTID_LEN;	//��Ƶͨ������ƫ����
const u16 SERV_MSGHEAD_CHNINDEX_LEN		= 1;	//��Ƶͨ�������ֽ���
const u16 SERV_MSGHEAD_CONFID_OFFSET	= SERV_MSGHEAD_CHNINDEX_OFFSET + SERV_MSGHEAD_CHNINDEX_LEN;	//�����ƫ����
const u16 SERV_MSGHEAD_CONFID_LEN		= 16;	//������ֽ���
const u16 SERV_MSGHEAD_EVENTID_OFFSET	= SERV_MSGHEAD_CONFID_OFFSET + SERV_MSGHEAD_CONFID_LEN;		//�¼���ƫ����
const u16 SERV_MSGHEAD_EVENTID_LEN		= 2;	//�¼����ֽ���
const u16 SERV_MSGHEAD_TIMER_OFFSET		= SERV_MSGHEAD_EVENTID_OFFSET + SERV_MSGHEAD_EVENTID_LEN;	//��ʱƫ����
const u16 SERV_MSGHEAD_TIMER_LEN		= 2;	//��ʱ�ֽ���
const u16 SERV_MSGHEAD_ERRORCODE_OFFSET	= SERV_MSGHEAD_TIMER_OFFSET + SERV_MSGHEAD_TIMER_LEN;		//������ƫ����
const u16 SERV_MSGHEAD_ERRORCODE_LEN	= 2;	//�������ֽ���
const u16 SERV_MSGHEAD_BODYLEN_OFFSET	= SERV_MSGHEAD_ERRORCODE_OFFSET + SERV_MSGHEAD_ERRORCODE_LEN;	//��Ϣ�峤��ƫ����
const u16 SERV_MSGHEAD_BODYLEN_LEN		= 2;	//��Ϣ�峤���ֽ���
const u16 SERV_MSGBODY_OFFSET			= SERV_MSGHEAD_LEN;	//��Ϣ��ƫ����


//ҵ����Ϣ�࣬�����4K������Ϣ
class C16KServMsg
{
protected:
	u8	m_abyBuffer[0x4000];		//��ϢBuffer��4K

/*====================================================================
    ����        ����ʼ��
    �������˵������
    ����ֵ˵��  ����
====================================================================*/
	void Init( void )
    {
        memset( m_abyBuffer, 0, sizeof( m_abyBuffer ) );	//����
    }

/*====================================================================
    ����        ��������Ϣ�峤��
    �������˵����wMsgBodyLen������Ϣ�峤��
    ����ֵ˵��  ����
====================================================================*/
	void SetMsgBodyLen( u16 wMsgBodyLen )
    {
        wMsgBodyLen = htons( wMsgBodyLen );
        memcpy( m_abyBuffer + SERV_MSGHEAD_BODYLEN_OFFSET, &wMsgBodyLen, SERV_MSGHEAD_BODYLEN_LEN );
    }

public:
/*====================================================================
    ����        ��constructor
    �������˵������
    ����ֵ˵��  ��
====================================================================*/
	C16KServMsg( void )
    {
        Init();
    }

/*====================================================================
    ����        ��constructor
    �������˵����u8 * const pbyMsg, Ҫ��ֵ����Ϣָ��
				  u16 wMsgLen, Ҫ��ֵ����Ϣ���ȣ�������ڵ���16
    ����ֵ˵��  ��
====================================================================*/
	C16KServMsg( u8 * const pbyMsg, u16 wMsgLen )
    {
        Init();
        
        if( wMsgLen < SERV_MSGHEAD_LEN || pbyMsg == NULL )
            return;
        
		u16 wTempLen = sizeof( m_abyBuffer ) ;
        wMsgLen = wTempLen < wMsgLen ? wTempLen : wMsgLen ;
        memcpy( m_abyBuffer, pbyMsg, wMsgLen );
        //set length
        SetMsgBodyLen( (u16)(wMsgLen - SERV_MSGHEAD_LEN) );
    }

/*====================================================================
    ����        ��distructor
    �������˵����
    ����ֵ˵��  ��
====================================================================*/
	~C16KServMsg( void )
    {
    }

/*====================================================================
    ����        ����Ϣͷ����
    �������˵����
    ����ֵ˵��  ��
====================================================================*/
	void ClearHdr( void )
    {
        u16		wBodyLen = GetMsgBodyLen();
        
        memset( m_abyBuffer, 0, SERV_MSGHEAD_LEN );	//����
        SetMsgBodyLen( wBodyLen );
    }

/*====================================================================
    ����        ����ȡ��ˮ����Ϣ
    �������˵������
    ����ֵ˵��  ����ˮ��
====================================================================*/
	u16 GetSerialNo( void ) const
    {
        u16		wTemp;
        
        memcpy( &wTemp, m_abyBuffer + SERV_MSGHEAD_SRIALNO_OFFSET, SERV_MSGHEAD_SRIALNO_LEN );
        return( ntohs( wTemp ) );
    }

/*====================================================================
    ����        ��������ˮ����Ϣ
    �������˵����u16 wSerialNo, ��ˮ��
    ����ֵ˵��  ����
====================================================================*/
	void SetSerialNo( u16 wSerialNo )
    {
        wSerialNo = htons( wSerialNo );
        memcpy( m_abyBuffer + SERV_MSGHEAD_SRIALNO_OFFSET, &wSerialNo, SERV_MSGHEAD_SRIALNO_LEN );
    }

/*====================================================================
    ����        ����ȡԴMCU����Ϣ
    �������˵������
    ����ֵ˵��  ��MCU��
====================================================================*/
	u16 GetSrcMcuId( void ) const
    {
        u16		wTemp;
        
        memcpy( &wTemp, m_abyBuffer + SERV_MSGHEAD_SRCMCUID_OFFSET, SERV_MSGHEAD_SRCMCUID_LEN );
        return( ntohs( wTemp ) );
    }

/*====================================================================
    ����        ����ȡԴMT����Ϣ
    �������˵������
    ����ֵ˵��  ��MT��
====================================================================*/
	u8 GetSrcMtId( void ) const
    {
        return( *( u8 * )( m_abyBuffer + SERV_MSGHEAD_SRCMTID_OFFSET ) );
    }

/*====================================================================
    ����        ������ԴMCU
    �������˵����u16 wSrcMcuId, MCU��
    ����ֵ˵��  ����
====================================================================*/
	void SetSrcMcu( u16 wSrcMcuId )
    {
        wSrcMcuId = htons( wSrcMcuId );
        memcpy( m_abyBuffer + SERV_MSGHEAD_SRCMCUID_OFFSET, &wSrcMcuId, SERV_MSGHEAD_SRCMCUID_LEN );
        memset( m_abyBuffer + SERV_MSGHEAD_SRCMTID_OFFSET, 0, SERV_MSGHEAD_SRCMTID_LEN );
    }

/*====================================================================
    ����        ������ԴMT
    �������˵����u16 wSrcMcuId, MCU��
				  u8 bySrcMtId, MT��
    ����ֵ˵��  ����
====================================================================*/
	void SetSrcMt( u16 wSrcMcuId, u8 bySrcMtId )
    {
        wSrcMcuId = htons( wSrcMcuId );
        memcpy( m_abyBuffer + SERV_MSGHEAD_SRCMCUID_OFFSET, &wSrcMcuId, SERV_MSGHEAD_SRCMCUID_LEN );
        memcpy( m_abyBuffer + SERV_MSGHEAD_SRCMTID_OFFSET, &bySrcMtId, SERV_MSGHEAD_SRCMTID_LEN );
    }

/*====================================================================
    ����        ����ȡ�Ự����Ϣ
    �������˵������
    ����ֵ˵��  ��Session�ţ�0��ʾ��������
====================================================================*/
	u8 GetSrcSsnId( void ) const
    {
        return( *( u8 * )( m_abyBuffer + SERV_MSGHEAD_SRCSSNID_OFFSET ) );
    }

/*====================================================================
    ����        �����ûỰ����Ϣ
    �������˵����u8 bySrcSsnId, Session�ţ�0��ʾ��������
    ����ֵ˵��  ����
====================================================================*/
	void SetSrcSsnId( u8 bySrcSsnId )
    {
        memcpy( m_abyBuffer + SERV_MSGHEAD_SRCSSNID_OFFSET, &bySrcSsnId, SERV_MSGHEAD_SRCSSNID_LEN );
    }

/*====================================================================
    ����        ��������Դ������Ӧ��
    �������˵������
    ����ֵ˵��  ����
====================================================================*/
	void SetNoSrc( void )
    {
        SetSrcMcu( 0 );
        SetSrcSsnId( 0 );
    }

/*====================================================================
    ����        ����ȡĿ��MCU����Ϣ
    �������˵������
    ����ֵ˵��  ��MCU��
====================================================================*/
	u16 GetDstMcuId( void ) const
    {
        u16		wTemp;
        
        memcpy( &wTemp, m_abyBuffer + SERV_MSGHEAD_DSTMCUID_OFFSET, SERV_MSGHEAD_DSTMCUID_LEN );
        return( ntohs( wTemp  ) );
    }

/*====================================================================
    ����        ����ȡĿ��MT����Ϣ
    �������˵������
    ����ֵ˵��  ��MT��
====================================================================*/
	u8 GetDstMtId( void ) const
    {
        return( *( u8 * )( m_abyBuffer + SERV_MSGHEAD_DSTMTID_OFFSET ) );
    }

/*====================================================================
    ����        ������Ŀ��MCU
    �������˵����u16 wDstMcuId, MCU��
    ����ֵ˵��  ����
====================================================================*/
	void SetDstMcu( u16 wDstMcuId )
    {
        wDstMcuId = htons( wDstMcuId );
        memcpy( m_abyBuffer + SERV_MSGHEAD_DSTMCUID_OFFSET, &wDstMcuId, SERV_MSGHEAD_DSTMCUID_LEN );
        memset( m_abyBuffer + SERV_MSGHEAD_DSTMTID_OFFSET, 0, SERV_MSGHEAD_DSTMTID_LEN );
    }

/*====================================================================
    ����        ������Ŀ��MT
    �������˵����u16 wDstMcuId, MCU��
				  u8 byDstMtId, MT��
    ����ֵ˵��  ����
====================================================================*/
	void SetDstMt( u16 wDstMcuId, u8 byDstMtId )
    {
        wDstMcuId = htons( wDstMcuId );
        memcpy( m_abyBuffer + SERV_MSGHEAD_DSTMCUID_OFFSET, &wDstMcuId, SERV_MSGHEAD_DSTMCUID_LEN );
        memcpy( m_abyBuffer + SERV_MSGHEAD_DSTMTID_OFFSET, &byDstMtId, SERV_MSGHEAD_DSTMTID_LEN );
    }

/*====================================================================
    ����        ��������Ŀ�ģ�����Ӧ��
    �������˵������
    ����ֵ˵��  ����
====================================================================*/
	void SetNoDst( void )
    {
        SetDstMcu( 0 );
    }

/*====================================================================
    ����        ����ȡ�������Ϣ
    �������˵������
    ����ֵ˵��  ������ţ�0��ʾ����
====================================================================*/
	CConfId GetConfId( void ) const
    {
        CConfId	cConfId;
        
        cConfId.SetConfId( m_abyBuffer + SERV_MSGHEAD_CONFID_OFFSET, SERV_MSGHEAD_CONFID_LEN );
        
        return( cConfId );
    }

/*====================================================================
    ����        �����û������Ϣ
    �������˵����const CConfId & cConfId������ţ�ȫ0��ʾ����
    ����ֵ˵��  ����
====================================================================*/
	void SetConfId( const CConfId & cConfId )
    {
        cConfId.GetConfId( m_abyBuffer + SERV_MSGHEAD_CONFID_OFFSET, SERV_MSGHEAD_CONFID_LEN );
    }

/*====================================================================
    ����        �����û������ϢΪ��
    �������˵������
    ����ֵ˵��  ����
====================================================================*/
	void SetNullConfId( void )
    {
        CConfId		cConfId;
        
        cConfId.SetNull();
        SetConfId( cConfId );
    }

/*====================================================================
    ����        ����ȡ�¼�����Ϣ
    �������˵������
    ����ֵ˵��  ���¼���
====================================================================*/
	u16 GetEventId( void ) const
    {
        u16	wTemp = 0;
        
        memcpy( &wTemp, m_abyBuffer + SERV_MSGHEAD_EVENTID_OFFSET, SERV_MSGHEAD_EVENTID_LEN );
        return( ntohs( wTemp ) );
    }

/*====================================================================
    ����        �������¼�����Ϣ
    �������˵����u16 wEventId, �¼���
    ����ֵ˵��  ����
====================================================================*/
	void SetEventId( u16 wEventId )
    {
        wEventId = htons( wEventId );
        memcpy( m_abyBuffer + SERV_MSGHEAD_EVENTID_OFFSET, &wEventId, SERV_MSGHEAD_EVENTID_LEN );
    }

/*====================================================================
    ����        ����ȡ��ʱ����Ϣ
    �������˵������
    ����ֵ˵��  ����ʱ��ʱ����0��ʾ��Ӧ��
====================================================================*/
	u16 GetTimer( void ) const
    {
        u16	wTemp = 0;
        
        memcpy( &wTemp, m_abyBuffer + SERV_MSGHEAD_TIMER_OFFSET, SERV_MSGHEAD_TIMER_LEN );
        return( ntohs( wTemp ) );
    }

/*====================================================================
    ����        �����ö�ʱ����Ϣ
    �������˵����u16 wTimer, ��ʱ��ʱ����0��ʾ��Ӧ��
    ����ֵ˵��  ����
====================================================================*/
	void SetTimer( u16 wTimer )
    {
        wTimer = htons( wTimer );
        memcpy( m_abyBuffer + SERV_MSGHEAD_TIMER_OFFSET, &wTimer, SERV_MSGHEAD_TIMER_LEN );
    }

/*====================================================================
    ����        ����ȡ��������Ϣ��NACK��Ϣ�ã�
    �������˵������
    ����ֵ˵��  ��������
====================================================================*/
	u16 GetErrorCode( void ) const
    {
        u16	wTemp = 0;
        
        memcpy( &wTemp, m_abyBuffer + SERV_MSGHEAD_ERRORCODE_OFFSET, SERV_MSGHEAD_ERRORCODE_LEN );
        return( ntohs( wTemp ) );
    }

/*====================================================================
    ����        �����ô�������Ϣ��NACK��Ϣ�ã�
    �������˵����u16 wErrorCode, ������
    ����ֵ˵��  ����
====================================================================*/
	void SetErrorCode( u16 wErrorCode )
    {
        wErrorCode = htons( wErrorCode );
        memcpy( m_abyBuffer + SERV_MSGHEAD_ERRORCODE_OFFSET, &wErrorCode, SERV_MSGHEAD_ERRORCODE_LEN );
    }

/*====================================================================
    ����        ����ȡ��Ƶͨ������
    �������˵������
    ����ֵ˵��  ����Ƶͨ������
====================================================================*/
	u8 GetChnIndex( void ) const
    {
        u8 byTemp = 0;;
        
        memcpy( &byTemp, m_abyBuffer + SERV_MSGHEAD_CHNINDEX_OFFSET, SERV_MSGHEAD_CHNINDEX_LEN );
        return( byTemp );
    }

/*====================================================================
    ����        ��������Ƶͨ������
    �������˵����u8 byIndex, ��Ƶͨ������
    ����ֵ˵��  ����
====================================================================*/
	void SetChnIndex( u8 byIndex )
    {
        memcpy( m_abyBuffer + SERV_MSGHEAD_CHNINDEX_OFFSET, &byIndex, SERV_MSGHEAD_CHNINDEX_LEN );
    }

/*====================================================================
    ����        ����ȡ��Ϣ�峤����Ϣ
    �������˵������
    ����ֵ˵��  ����Ϣ�峤��
====================================================================*/
	u16 GetMsgBodyLen( void ) const
    {
        u16 wTemp = 0;
        
        memcpy( &wTemp, m_abyBuffer + SERV_MSGHEAD_BODYLEN_OFFSET, SERV_MSGHEAD_BODYLEN_LEN );
        return( ntohs( wTemp ) );
    }

/*====================================================================
    ����        ����ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
    �������˵����u8 * pbyMsgBodyBuf, ���ص���Ϣ��
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ�峤��
====================================================================*/
	u16 GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
    {
        memcpy( pbyMsgBodyBuf, m_abyBuffer + SERV_MSGBODY_OFFSET, wBufLen );
        
		u16 wTempLen = GetMsgBodyLen();
        return wTempLen < wBufLen ? wTempLen : wBufLen;
    }

/*====================================================================
    ����        ����ȡ��Ϣ��ָ�룬�û������ṩBUFFER
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
====================================================================*/
	u8 * const GetMsgBody( void ) const
    {
        return( ( u8 * const )( m_abyBuffer + SERV_MSGBODY_OFFSET ) );
    }

/*====================================================================
    ����        ��������Ϣ��
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪNULL
    ����ֵ˵��  ����
====================================================================*/
	void SetMsgBody( u8 * const pbyMsgBody = NULL, u16 wLen = 0 )
    {
		u16 wTempLen = sizeof(m_abyBuffer) - SERV_MSGHEAD_LEN;
    	wLen = wLen < wTempLen ? wLen : wTempLen;
        
        memcpy( m_abyBuffer + SERV_MSGBODY_OFFSET, pbyMsgBody, wLen );
        SetMsgBodyLen( wLen );
    }

/*====================================================================
    ����        �������Ϣ��
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪNULL
    ����ֵ˵��  ����
====================================================================*/
	void CatMsgBody( u8 * const pbyMsgBody, u16 wLen )
    {
    	u16 wTempLen = u16( sizeof( m_abyBuffer ) - SERV_MSGHEAD_LEN - GetMsgBodyLen() );
    	wLen = wLen < wTempLen ? wLen : wTempLen;
        
        memcpy( m_abyBuffer + SERV_MSGBODY_OFFSET + GetMsgBodyLen(), pbyMsgBody, wLen );
        SetMsgBodyLen( (u16)(GetMsgBodyLen() + wLen) );
    }

/*====================================================================
    ����        ����ȡ������Ϣ����
    �������˵������
    ����ֵ˵��  ��������Ϣ����
====================================================================*/
	u16 GetServMsgLen( void ) const
    {
        return( (u16)(GetMsgBodyLen() + SERV_MSGHEAD_LEN) );
    }

/*====================================================================
    ����        ����ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
    �������˵����u8 * pbyMsgBuf, ���ص���Ϣ
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ����
====================================================================*/
	u16 GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
    {
        memcpy( pbyMsgBuf, m_abyBuffer, wBufLen );
        
        u16 wTempLen = (u16)( GetMsgBodyLen() + SERV_MSGHEAD_LEN );
        return wTempLen < wBufLen ? wTempLen : wBufLen;
    }

/*====================================================================
    ����        ����ȡ������Ϣָ�룬�û������ṩBUFFER
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
====================================================================*/
	u8 * const GetServMsg( void ) const
    {
        return( ( u8 * const )( m_abyBuffer ) );
    }

/*====================================================================
    ����        ������������Ϣ
    �������˵����u8 * const pbyMsg, �����������Ϣ
				  u16 wLen, �������Ϣ����
    ����ֵ˵��  ����
====================================================================*/
	void SetServMsg( u8 * const pbyMsg, u16 wMsgLen )
    {
        if( wMsgLen < SERV_MSGHEAD_LEN )
        {
            printf( "CServMsg: Exception -- invalid service message!\n" );
            return;
        }
        
        u16 wTempLen = sizeof(m_abyBuffer);
        wMsgLen = wTempLen < wMsgLen ? wTempLen : wMsgLen;
        
        memcpy( m_abyBuffer, pbyMsg, wMsgLen );
        SetMsgBodyLen( (u16)(wMsgLen - SERV_MSGHEAD_LEN) );
    }

/*====================================================================
    ����        ������������
    �������˵����CServMsg & cServMsg, ��ֵ����Ϣ����
    ����ֵ˵��  ��CServMsg����Ӧ��
====================================================================*/
	const C16KServMsg & operator= ( const C16KServMsg & cServMsg )
    {
        u16	wLen = cServMsg.GetServMsgLen();
        
        memcpy( m_abyBuffer, cServMsg.GetServMsg(), wLen );
        return( *this );
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//DCServer��Ϣ
struct TDCServerInfo
{
protected:
	u32	    m_dwIpAddr;						    //��������ַ,������
	char	m_achAlias[MAX_ALIAS_LENGTH];	    //����������
    u32     m_dwMcuIpAddr;                      //MCU��ַ��������
	u32		m_dwBackupMcuIpAddr;				//����MCU��ַ��������
    u16	    m_wMcuPort;					        //MCU�˿�,������
    u16     m_wBackupMcuPort;                   //����MCU�˿ڣ�������
    u32     m_dwGKIpAddr;                       //GK��ַ��������
    u16	    m_wGKPort;					        //GK�˿�,������
    char    m_achGKRegNum[16];                  //GKע��E164����
	u16	    m_wListenPort;					    //�����������˿�,������
    u16     m_wTelnetPort;                      //������Telnet�˿ڣ�������
    u16	    m_wT120Port;					    //������T120�˿�,������
    u16     m_wRasPort;                         //������RAS�˿�,������
    u16     m_wH323Port;                        //������H323�˿�,������
    char	m_achEmail[MAX_EMAIL_LENGTH];	    //������Email
    char	m_achLocation[MAX_NODELOCATION_LENGTH];	//������λ��
    char	m_achPhoneNum[MAX_ALIAS_LENGTH];	//�������绰����
	
public:
/*====================================================================
    ����        �����캯��
    �������˵������
    ����ֵ˵��  ����
====================================================================*/
	TDCServerInfo( void )
	{
		m_dwIpAddr = 0;
        memset( m_achAlias , 0, sizeof(m_achAlias) );
		//m_dwGWIpAddr = 0;
        m_dwGKIpAddr = 0;
        m_wGKPort = htons(1719);

        memset( m_achGKRegNum , 0, sizeof(m_achGKRegNum) );
        memcpy( m_achGKRegNum , "1234", sizeof(m_achGKRegNum) );
        
        m_wListenPort = htons(PORT_DCS);
        m_wTelnetPort = htons(2600);
        m_wT120Port = htons(DCS_DEFAULT_PORT);
        memset( m_achEmail , 0, sizeof(m_achEmail) );
        memset( m_achLocation , 0, sizeof(m_achLocation) );
        memset( m_achPhoneNum , 0, sizeof(m_achPhoneNum) );
	}
	
/*====================================================================
    ����        ���õ�IP��ַ
    �������˵������
    ����ֵ˵��  ���õ���Ip��ַ
====================================================================*/
	u32	GetIpAddr( void ) const
	{
		return ntohl(m_dwIpAddr);
	}

/*====================================================================
    ����        �����÷�������ַ
    �������˵����dwIpAddr����Ip��ַ
    ����ֵ˵��  ����
====================================================================*/
	void SetIpAddr( u32 dwIpAddr )
	{
		m_dwIpAddr = htonl(dwIpAddr);
	}
	
/*====================================================================
    ����        ���õ�����������
    �������˵������
    ����ֵ˵��  ���õ��ķ���������
====================================================================*/
	LPCSTR GetAlias( void ) const
	{
		return m_achAlias;
	}
    
/*====================================================================
    ����        �����÷���������
    �������˵����lpszAlias��������������
    ����ֵ˵��  ����
====================================================================*/
    void SetAlias( LPCSTR lpszAlias )
	{
        if (lpszAlias == NULL)
        {
		    m_achAlias[0] = '\0';
        }
        else
        {
		    strncpy( m_achAlias, lpszAlias, sizeof(m_achAlias) );
		    m_achAlias[sizeof(m_achAlias) - 1] = '\0';
        }
	}
	
/*====================================================================
    ����        ���õ�������MCU1��ַ
    �������˵������
    ����ֵ˵��  ��������MCU1��ַ
====================================================================*/
	u32	GetMcuIpAddr( void ) const
	{
		return ntohl(m_dwMcuIpAddr);
	}

/*====================================================================
    ����        ���õ�������MCU2��ַ
    �������˵������
    ����ֵ˵��  ��������MCU2��ַ
====================================================================*/
	u32	GetBackupMcuIpAddr( void ) const
	{
		return ntohl(m_dwBackupMcuIpAddr);
	}

/*====================================================================
    ����        �����÷�����MCU1��ַ
    �������˵����dwMcuIpAddr����MCU1 Ip��ַ
    ����ֵ˵��  ����
====================================================================*/
	void SetMcuIpAddr( u32 dwMcuIpAddr )
	{
		m_dwMcuIpAddr = htonl(dwMcuIpAddr);
	}
    
/*====================================================================
    ����        �����÷�����MCU2��ַ
    �������˵����dwMcuIpAddr����MCU2 Ip��ַ
    ����ֵ˵��  ����
====================================================================*/
	void SetBackupMcuIpAddr( u32 dwMcuIpAddr )
	{
		m_dwBackupMcuIpAddr = htonl(dwMcuIpAddr);
	}	


/*====================================================================
    ����        ���õ�������MCU1�˿�
    �������˵������
    ����ֵ˵��  ��������MCU�˿�
====================================================================*/
	u16	GetMcuPort( void ) const
	{
		return ntohs( m_wMcuPort );
	}

/*====================================================================
    ����        ���õ�������MCU2�˿�
    �������˵������
    ����ֵ˵��  ��������MCU�˿�
====================================================================*/
	u16	GetBackupMcuPort( void ) const
	{
		return ntohs( m_wBackupMcuPort );
	}

/*====================================================================
    ����        �����÷�����MCU1�˿�
    �������˵����wMcuPort����MCU�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetMcuPort( u16 wMcuPort )
	{
		m_wMcuPort = htons( wMcuPort );
	}

/*====================================================================
    ����        �����÷�����MCU2�˿�
    �������˵����wMcuPort����MCU�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetBackupMcuPort( u16 wMcuPort )
	{
		m_wBackupMcuPort = htons( wMcuPort );
	}

/*====================================================================
    ����        ���õ�������GK��ַ
    �������˵������
    ����ֵ˵��  ��������GK��ַ
====================================================================*/
	u32	GetGKIpAddr( void ) const
	{
		return ntohl(m_dwGKIpAddr);
	}

/*====================================================================
    ����        �����÷�����GK��ַ
    �������˵����dwGKIpAddr����GKIp��ַ
    ����ֵ˵��  ����
====================================================================*/
	void SetGKIpAddr( u32 dwGKIpAddr )
	{
		m_dwGKIpAddr = htonl(dwGKIpAddr);
	}
    
/*====================================================================
    ����        ���õ�������GK�˿�
    �������˵������
    ����ֵ˵��  ��������GK�˿�
====================================================================*/
	u16	GetGKPort( void ) const
	{
		return ntohs( m_wGKPort );
	}

/*====================================================================
    ����        �����÷�����GK�˿�
    �������˵����wGKPort����GK�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetGKPort( u16 wGKPort )
	{
		m_wGKPort = htons( wGKPort );
	}

/*====================================================================
    ����        ���õ�GKע�����
    �������˵������
    ����ֵ˵��  ��GKע�����
====================================================================*/
	LPCSTR GetGKRegNum( void ) const
	{
		return m_achGKRegNum;
	}
    
/*====================================================================
    ����        ������GKע�����
    �������˵����lpszGKRegNum����GKע�����
    ����ֵ˵��  ����
====================================================================*/
    void SetGKRegNum( LPCSTR lpszGKRegNum )
	{
        if (lpszGKRegNum == NULL)
        {
		    m_achGKRegNum[0] = '\0';
        }
        else
        {
		    strncpy( m_achGKRegNum, lpszGKRegNum, sizeof(m_achGKRegNum) );
		    m_achGKRegNum[sizeof(m_achGKRegNum) - 1] = '\0';
        }
	}

/*====================================================================
    ����        ���õ������������˿�
    �������˵������
    ����ֵ˵��  �������������˿�
====================================================================*/
	u16	GetListenPort( void ) const
	{
		return ntohs( m_wListenPort );
	}

/*====================================================================
    ����        �����÷����������˿�
    �������˵����wListenPort���������˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetListenPort( u16 wListenPort )
	{
		m_wListenPort = htons( wListenPort );
	}

/*====================================================================
    ����        ���õ�������Telnet�˿�
    �������˵������
    ����ֵ˵��  ��������Telnet�˿�
====================================================================*/
	u16	GetTelnetPort( void ) const
	{
		return ntohs( m_wTelnetPort );
	}

/*====================================================================
    ����        �����÷�����Telnet�˿�
    �������˵����wTelnetPort����Telnet�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetTelnetPort( u16 wTelnetPort )
	{
		m_wTelnetPort = htons( wTelnetPort );
	}

/*====================================================================
    ����        ���õ�������T120�˿�
    �������˵������
    ����ֵ˵��  ��������T120�˿�
====================================================================*/
	u16	GetT120Port( void ) const
	{
		return ntohs( m_wT120Port );
	}

/*====================================================================
    ����        �����÷�����T120�˿�
    �������˵����wT120Port����T120�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetT120Port( u16 wT120Port )
	{
		m_wT120Port = htons( wT120Port );
	}

/*====================================================================
    ����        ���õ�������RAS�˿�
    �������˵������
    ����ֵ˵��  ��������RAS�˿�
====================================================================*/
	u16	GetRasPort( void ) const
	{
		return ntohs( m_wRasPort );
	}

/*====================================================================
    ����        �����÷�����RAS�˿�
    �������˵����wRasPort����RAS�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetRasPort( u16 wRasPort )
	{
		m_wRasPort = htons( wRasPort );
	}

/*====================================================================
    ����        ���õ�������H323�˿�
    �������˵������
    ����ֵ˵��  ��������H323�˿�
====================================================================*/
	u16	GetH323Port( void ) const
	{
		return ntohs( m_wH323Port );
	}

/*====================================================================
    ����        �����÷�����H323�˿�
    �������˵����wH323Port����H323�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetH323Port( u16 wH323Port )
	{
		m_wH323Port = htons( wH323Port );
	}

/*====================================================================
    ����        ���õ�������Email
    �������˵������
    ����ֵ˵��  ���õ��ķ�����Email
====================================================================*/
	LPCSTR GetEmail( void ) const
	{
		return m_achEmail;
	}
    
/*====================================================================
    ����        �����÷�����Email
    �������˵����lpszEmail����������Email
    ����ֵ˵��  ����
====================================================================*/
    void SetEmail( LPCSTR lpszEmail )
	{
        if (lpszEmail == NULL)
        {
		    m_achEmail[0] = '\0';
        }
        else
        {
		    strncpy( m_achEmail, lpszEmail, sizeof(m_achEmail) );
		    m_achEmail[sizeof(m_achEmail) - 1] = '\0';
        }
	}

/*====================================================================
    ����        ���õ�������λ��
    �������˵������
    ����ֵ˵��  ���õ��ķ�����λ��
====================================================================*/
	LPCSTR GetLocation( void ) const
	{
		return m_achLocation;
	}
    
/*====================================================================
    ����        �����÷�����λ��
    �������˵����lpszLocation����������λ��
    ����ֵ˵��  ����
====================================================================*/
    void SetLocation( LPCSTR lpszLocation )
	{
        if (lpszLocation == NULL)
        {
		    m_achLocation[0] = '\0';
        }
        else
        {
		    strncpy( m_achLocation, lpszLocation, sizeof(m_achLocation) );
		    m_achLocation[sizeof(m_achLocation) - 1] = '\0';
        }
	}

/*====================================================================
    ����        ���õ�������PhoneNum
    �������˵������
    ����ֵ˵��  ���õ��ķ�����PhoneNum
====================================================================*/
	LPCSTR GetPhoneNum( void ) const
	{
		return m_achPhoneNum;
	}
    
/*====================================================================
    ����        �����÷�����PhoneNum
    �������˵����lpszPhoneNum����������PhoneNum
    ����ֵ˵��  ����
====================================================================*/
    void SetPhoneNum( LPCSTR lpszPhoneNum )
	{
        if (lpszPhoneNum == NULL)
        {
		    m_achPhoneNum[0] = '\0';
        }
        else
        {
		    strncpy( m_achPhoneNum, lpszPhoneNum, sizeof(m_achPhoneNum) );
		    m_achPhoneNum[sizeof(m_achPhoneNum) - 1] = '\0';
        }
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//������������Ϣ
struct TDCSConfInfo
{
protected:
    u8      m_byIsH323Call;                             //�Ƿ�ͨ��H323���� Ĭ��Ϊ0
    char    m_achE164Num[MAX_E164NUM_LENGTH];           //������E164����
	u32	    m_dwIpAddr;						            //��������ַ,������
    u16	    m_wT120Port;					            //������T120�˿�,������
    u8      m_byE164Valid;                              //Ĭ��Ϊ0
    char	m_achConfNameNum[MAX_CONFNAME_NUM_LENGTH];	//�����������������ֶ�
    char	m_achConfNameTxt[MAX_CONFNAME_TXT_LENGTH];	//���������������ı���
    char	m_achConfPasswd[MAX_DC_PASSWORD_LENGTH];	//��������
	
public:
/*====================================================================
    ����        �����캯��
    �������˵������
    ����ֵ˵��  ����
====================================================================*/
	TDCSConfInfo( void )
	{
        m_byIsH323Call = 0;
		m_dwIpAddr = 0;
        m_wT120Port = 0;
        m_byE164Valid = 0;
        memset( m_achE164Num , 0, sizeof(m_achE164Num) );
        memset( m_achConfNameNum , 0, sizeof(m_achConfNameNum) );
        memset( m_achConfNameTxt , 0, sizeof(m_achConfNameTxt) );
        memset( m_achConfPasswd , 0, sizeof(m_achConfPasswd) );
	}
	
/*====================================================================
    ����        ���õ��Ƿ�ͨ��H323����
    �������˵������
    ����ֵ˵��  ���Ƿ�ͨ��H323����
====================================================================*/
	bool IsH323Call(void) const
	{
        return m_byIsH323Call? true:false;
	}

/*====================================================================
    ����        �������Ƿ�ͨ��H323����
    �������˵����wT120Port�����Ƿ�ͨ��H323����
    ����ֵ˵��  ����
====================================================================*/
	void SetH323Call( bool bH323Call )
	{
        m_byIsH323Call = u8(bH323Call? 1:0);
	}

/*====================================================================
    ����        ���õ�������E164����
    �������˵������
    ����ֵ˵��  ���õ��ķ�����E164����
====================================================================*/
	LPCSTR GetE164Num( void ) const
	{
		return m_achE164Num;
	}
    
/*====================================================================
    ����        �����÷�����E164����
    �������˵����lpszE164Num����������E164����
    ����ֵ˵��  ����
====================================================================*/
    void SetE164Num( LPCSTR lpszE164Num )
	{
		strncpy( m_achE164Num, lpszE164Num, sizeof(m_achE164Num) );
		m_achE164Num[sizeof(m_achE164Num) - 1] = '\0';
	}

/*====================================================================
    ����        ���õ�IP��ַ
    �������˵������
    ����ֵ˵��  ���õ���Ip��ַ
====================================================================*/
	u32	GetIpAddr( void ) const
	{
		return ntohl(m_dwIpAddr);
	}

/*====================================================================
    ����        �����÷�������ַ
    �������˵����dwIpAddr����Ip��ַ
    ����ֵ˵��  ����
====================================================================*/
	void SetIpAddr( u32 dwIpAddr )
	{
		m_dwIpAddr = htonl(dwIpAddr);
	}
	
/*====================================================================
    ����        ���õ�������T120�˿�
    �������˵������
    ����ֵ˵��  ��������T120�˿�
====================================================================*/
	u16	GetT120Port( void ) const
	{
		return ntohs( m_wT120Port );
	}

/*====================================================================
    ����        �����÷�����T120�˿�
    �������˵����wT120Port����T120�˿�
    ����ֵ˵��  ����
====================================================================*/
	void SetT120Port( u16 wT120Port )
	{
		m_wT120Port = htons( wT120Port );
	}

/*====================================================================
    ����        ���õ�E164�����Ƿ���Ч
    �������˵������
    ����ֵ˵��  ��E164�����Ƿ���Ч
====================================================================*/
	bool IsE164Valid(void) const
	{
        return m_byE164Valid? true:false;
	}

/*====================================================================
    ����        ������E164�����Ƿ���Ч
    �������˵����wT120Port����E164�����Ƿ���Ч
    ����ֵ˵��  ����
====================================================================*/
	void SetE164Valid( bool bE164Valid )
	{
        m_byE164Valid = (u8)(bE164Valid? 1:0);
	}

/*====================================================================
    ����        ���õ����������ֶ�
    �������˵������
    ����ֵ˵��  ���õ��Ļ��������ֶ�
====================================================================*/
	LPCSTR GetConfNameNum( void ) const
	{
		return m_achConfNameNum;
	}
    
/*====================================================================
    ����        �����û��������ֶ�
    �������˵����lpszConfNameNum�������������ֶ�
    ����ֵ˵��  ����
====================================================================*/
    void SetConfNameNum( LPCSTR lpszConfNameNum )
	{
		strncpy( m_achConfNameNum, lpszConfNameNum, sizeof(m_achConfNameNum) );
		m_achConfNameNum[sizeof(m_achConfNameNum) - 1] = '\0';
	}
    
/*====================================================================
    ����        ���õ��������ı���
    �������˵������
    ����ֵ˵��  ���õ��Ļ������ı���
====================================================================*/
	LPCSTR GetConfNameTxt( void ) const
	{
		return m_achConfNameTxt;
	}
    
/*====================================================================
    ����        �����û������ı���
    �������˵����lpszConfNameTxt�����������ı���
    ����ֵ˵��  ����
====================================================================*/
    void SetConfNameTxt( LPCSTR lpszConfNameTxt )
	{
		strncpy( m_achConfNameTxt, lpszConfNameTxt, sizeof(m_achConfNameTxt) );
		m_achConfNameTxt[sizeof(m_achConfNameTxt) - 1] = '\0';
	}

/*====================================================================
    ����        ���õ���������
    �������˵������
    ����ֵ˵��  ���õ��Ļ�������
====================================================================*/
	LPCSTR GetConfPasswd( void ) const
	{
		return m_achConfPasswd;
	}
    
/*====================================================================
    ����        �����û�������
    �������˵����lpszConfPasswd������������
    ����ֵ˵��  ����
====================================================================*/
    void SetConfPasswd( LPCSTR lpszConfPasswd )
	{
		strncpy( m_achConfPasswd, lpszConfPasswd, sizeof(m_achConfPasswd) );
		m_achConfPasswd[sizeof(m_achConfPasswd) - 1] = '\0';
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�û���Ϣ
struct TDCUser
{
protected:
	char	m_achUserName[MAX_USER_LENGTH];         //�û���
	char	m_achPassword[MAX_PASSWORD_LENGTH];		//�û�����
	u8      m_byLevel;                              //�û��ȼ�( 0:ֻ���û�;1:�ɲ����û�;2:�����û� )
    u8      m_byOnline;                             //�û��Ƿ�����
public:
	TDCUser( void )
	{
		memset( m_achUserName , 0, sizeof(m_achUserName) );
		memset( m_achPassword , 0, sizeof(m_achPassword) );
		m_byLevel = 0;
		m_byOnline = 0;
	}
	
	~TDCUser()
	{
	}
	
/*====================================================================
    ����        ���õ��û���
    �������˵������
    ����ֵ˵��  ���û���
====================================================================*/
	LPCSTR GetUserName( void ) const
    {
        return m_achUserName;
    }

/*====================================================================
    ����        �������û���
    �������˵����achUsername�����û���
    ����ֵ˵��  ����
====================================================================*/
	void SetUserName( LPCSTR achUsername )
    {
        strncpy( m_achUserName, achUsername, sizeof(m_achUserName) );
		m_achUserName[sizeof(m_achUserName) - 1] = '\0';
    }
	
/*====================================================================
    ����        ���õ��û�����
    �������˵������
    ����ֵ˵��  ���û�����
====================================================================*/
	LPCSTR GetPassword( void ) const
    {
        return m_achPassword;
    }

/*====================================================================
    ����        �������û�����
    �������˵����achPassword�����û�����
    ����ֵ˵��  ����
====================================================================*/
	void SetPassword( LPCSTR achPassword )
    {
        strncpy( m_achPassword, achPassword, sizeof(m_achPassword) );
		m_achPassword[sizeof(m_achPassword) - 1] = '\0';
    }
	
/*====================================================================
    ����        ���õ��û��ȼ�
    �������˵������
    ����ֵ˵��  ���û��ȼ�
====================================================================*/
    u8 GetLevel(void) const
    {
        return m_byLevel;
    }

/*====================================================================
    ����        �������û��ȼ�
    �������˵����level�����û��ȼ�
    ����ֵ˵��  ����
====================================================================*/
    void SetLevel(u8 level)
    {
        m_byLevel = level;
    }
	
/*====================================================================
    ����        ���õ��û��Ƿ�����
    �������˵������
    ����ֵ˵��  ��  true��������
                    false����������
====================================================================*/
    bool IsOnline(void) const
    {
        return m_byOnline? true:false;
    }

/*====================================================================
    ����        �������û��Ƿ�����
    �������˵����bOnline�����Ƿ�����
    ����ֵ˵��  ����
====================================================================*/
    void SetOnline( bool bOnline = false )
    {
        m_byOnline = (u8)(bOnline? 1:0);
    }	

/*====================================================================
    ����        ���ж��û��Ƿ����
    �������˵����tDcUser������һ�û���Ϣ
    ����ֵ˵��  ��true�������
                  false���������
====================================================================*/
	bool IsEqual(const TDCUser& tDcUser)
	{
        return (strcmp(GetUserName(), tDcUser.GetUserName())==0)? true:false;
	}
    
/*====================================================================
    ����        ����ֵ����������
    �������˵����TDCUser& tDcUser, ��ֵ����Ϣ����
    ����ֵ˵��  ��TDCUser��������
====================================================================*/
	TDCUser& operator=(const TDCUser& tDcUser) 
	{
		SetUserName(tDcUser.GetUserName());
		SetPassword(tDcUser.GetPassword());
		SetLevel(tDcUser.GetLevel());
		SetOnline(tDcUser.IsOnline());
		return *this;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ն˼���Ϣ
struct TDCBaseMt
{
private:
	char	m_achAlias[MAX_ALIAS_LENGTH];		//�ն˱���--����
    u16     m_wMtId;                            //�ն�ID
    char    m_achE164Num[MAX_E164NUM_LENGTH];   //E164����
	u32	    m_dwIpAddr;						    //�ն˵�ַ,������
	u16	    m_wChannelPort;						//����˿�,������
    u8      m_byE164Valid;                      //E164�Ƿ���Ч(1:E164��Ч  0:Ip��Ч  Ĭ��Ϊ1)
   	char    m_achMtInfo[MAX_MT_INFO_LENGTH];    //��ע��Ϣ
	
public:
	TDCBaseMt( void )
	{
		memset( m_achAlias , 0, sizeof(m_achAlias) );
        m_wMtId = 0;
        memset( m_achE164Num , 0, sizeof(m_achE164Num) );
		m_dwIpAddr = 0;
		m_wChannelPort = htons(DCS_DEFAULT_PORT);	
        m_byE164Valid = 1;
		memset( m_achMtInfo , 0, sizeof(m_achMtInfo) );
	}

/*====================================================================
    ����        �������ն˱���
    �������˵����lpszAlias�����ն˱���
    ����ֵ˵��  ����
====================================================================*/   
	void SetAlias( LPCSTR lpszAlias )
	{
        if (lpszAlias == NULL)
        {
            m_achAlias[0] = '\0';
        }
        else
        {
		    strncpy( m_achAlias, lpszAlias, sizeof(m_achAlias) );
		    m_achAlias[sizeof(m_achAlias) - 1] = '\0';
        }
	}
    
/*====================================================================
    ����        ���õ��ն˱���
    �������˵������
    ����ֵ˵��  ���ն˱���
====================================================================*/	
	LPCSTR GetAlias( void ) const
	{
		return m_achAlias;
	}

/*====================================================================
    ����        ���õ��ն�ID
    �������˵������
    ����ֵ˵��  ���ն�ID
====================================================================*/	
	u16	GetMtId( void ) const
	{
		return ntohs( m_wMtId );
	}

/*====================================================================
    ����        �������ն�ID
    �������˵����wMtId�����ն�ID
    ����ֵ˵��  ����
====================================================================*/   
	void SetMtId( u16 wMtId )
	{
		m_wMtId = htons( wMtId );
	}

/*====================================================================
    ����        ������E164����
    �������˵����lpszE164Num����E164����
    ����ֵ˵��  ����
====================================================================*/   
	void SetE164Num( LPCSTR lpszE164Num )
	{
        if (lpszE164Num == NULL)
        {
            m_achE164Num[0] = '\0';
        }
        else
        {
		    strncpy( m_achE164Num, lpszE164Num, sizeof(m_achE164Num) );
		    m_achE164Num[sizeof(m_achE164Num) - 1] = '\0';
        }
	}
    
/*====================================================================
    ����        ���õ�E164����
    �������˵������
    ����ֵ˵��  ��E164����
====================================================================*/	
	LPCSTR GetE164Num( void ) const
	{
		return m_achE164Num;
	}

/*====================================================================
    ����        ���õ��ն˵�ַ
    �������˵������
    ����ֵ˵��  ���ն˵�ַ
====================================================================*/	
	u32	GetIpAddr( void ) const
	{
		return ntohl(m_dwIpAddr);
	}

/*====================================================================
    ����        �������ն˵�ַ
    �������˵����dwIpAddr�����ն˵�ַ
    ����ֵ˵��  ����
====================================================================*/   
	void SetIpAddr( u32 dwIpAddr )
	{
		m_dwIpAddr = htonl(dwIpAddr);
	}
	
/*====================================================================
    ����        ���õ�����˿�
    �������˵������
    ����ֵ˵��  ������˿�
====================================================================*/	
	u16	GetChannelPort( void ) const
	{
		return ntohs( m_wChannelPort );
	}

/*====================================================================
    ����        ����������˿�
    �������˵����wChannelPort��������˿�
    ����ֵ˵��  ����
====================================================================*/   
	void SetChannelPort( u16 wChannelPort )
	{
		m_wChannelPort = htons( wChannelPort );
	}

/*====================================================================
    ����        ������E164�����Ƿ���Ч
    �������˵����bE164Valid����E164�����Ƿ���Ч
    ����ֵ˵��  ����
====================================================================*/   
	void SetE164Valid( bool bE164Valid )
	{
        m_byE164Valid = bE164Valid? 1:0;
	}

/*====================================================================
    ����        ���õ�E164�����Ƿ���Ч
    �������˵������
    ����ֵ˵��  ��E164�����Ƿ���Ч
====================================================================*/	
	bool IsE164Valid( void ) const
	{
        return m_byE164Valid? true:false;
	}
	
/*====================================================================
    ����        ���õ��ն�����
    �������˵������
    ����ֵ˵��  ���ն�����
====================================================================*/
	LPCSTR GetMtInfo( void ) const
	{
		return m_achMtInfo;
	}

/*====================================================================
    ����        �������ն�����
    �������˵����lpszMtInfo�����ն�����
    ����ֵ˵��  ����
====================================================================*/
	void SetMtInfo( LPCSTR lpszMtInfo )
	{
        if (lpszMtInfo == NULL)
        {
		    m_achMtInfo[0] = '\0';
        }
        else
        {
		    strncpy( m_achMtInfo, lpszMtInfo, sizeof(m_achMtInfo) );
		    m_achMtInfo[sizeof(m_achMtInfo) - 1] = '\0';
        }
	}

/*====================================================================
    ����        ���ж��ն��Ƿ����
    �������˵����tDCBaseMt������һ�ն���Ϣ
    ����ֵ˵��  ��  true�������
                    false���������
====================================================================*/
	bool IsEqual(const TDCBaseMt& tDCBaseMt)
	{
        return (strcmp(GetAlias(), tDCBaseMt.GetAlias())==0)? true:false;
	}

/*====================================================================
    ����        ����ֵ����������
    �������˵����TDCBaseMt& tDCBaseMt, ��ֵ����Ϣ����
    ����ֵ˵��  ��TDCBaseMt��������
====================================================================*/
	TDCBaseMt& operator=(const TDCBaseMt& tDCBaseMt) 
	{
		SetAlias(tDCBaseMt.GetAlias());
        SetE164Num(tDCBaseMt.GetE164Num());
		SetIpAddr(tDCBaseMt.GetIpAddr());
		SetChannelPort(tDCBaseMt.GetChannelPort());
        SetE164Valid(tDCBaseMt.IsE164Valid());
        SetMtInfo( tDCBaseMt.GetMtInfo() );
		return *this;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//�ն���ϸ��Ϣ
struct TDCMt : public TDCBaseMt
{
protected:
    u16     m_wGKCallingPort;                           //GK���ж˿�
    enum_ConfMtType m_enumConfMtType;                   //�����е��ն�����
    enum_DeviceType m_enumDeviceType;                   //�����е��ն��豸����
	char	m_achEmail[MAX_EMAIL_LENGTH];			    //�ն�Email��ַ
	u8		m_byOnline;								    //�ն��Ƿ����
    u16     m_byChildCount;                             //ֱ���ӽڵ����
    char    m_achNodeName[MAX_NODENAME_LENGTH];         //�ڵ���
    char    m_achNodePhone[MAX_NODEPHONE_LENGTH];       //�绰����
    char    m_achNodeLocation[MAX_NODELOCATION_LENGTH]; //�ڵ�λ��
public:
	TDCMt( void )
	{
        m_wGKCallingPort = htons(1720);
        m_enumConfMtType = enum_MtInvited;
        m_enumDeviceType = enum_Mt;
		memset( m_achEmail , 0, sizeof(m_achEmail) );
		memset( m_achNodeName , 0, sizeof(m_achNodeName) );
		memset( m_achNodePhone , 0, sizeof(m_achNodePhone) );
		memset( m_achNodeLocation , 0, sizeof(m_achNodeLocation) );
		m_byOnline = 0;
        m_byChildCount = 0;
	}

/*====================================================================
    ����        ���õ�GK ���ж˿�
    �������˵������
    ����ֵ˵��  ��GK ���ж˿�
====================================================================*/	
    u16	GetGKCallingPort( void ) const
    {
        return ntohs( m_wGKCallingPort );
    }
    
/*====================================================================
    ����        ������GK ���ж˿�
    �������˵����wGKCallingPort����GK ���ж˿�
    ����ֵ˵��  ����
====================================================================*/   
    void SetGKCallingPort( u16 wGKCallingPort )
    {
        m_wGKCallingPort = htons( wGKCallingPort );
	}

/*====================================================================
    ����        ���õ������ն�����
    �������˵������
    ����ֵ˵��  �������ն�����
====================================================================*/	
	enum_ConfMtType GetConfMtType( void ) const
	{
		return (enum_ConfMtType)ntohl(m_enumConfMtType);
	}

/*====================================================================
    ����        �����û����ն�����
    �������˵����byConfMtType���������ն�����
    ����ֵ˵��  ����
====================================================================*/   
	void SetConfMtType( enum_ConfMtType enumConfMtType )
	{
		m_enumConfMtType = (enum_ConfMtType)htonl(enumConfMtType);
	}

/*====================================================================
    ����        ���õ��ն��豸����
    �������˵������
    ����ֵ˵��  ���ն��豸����
====================================================================*/	
	enum_DeviceType GetDeviceType( void ) const
	{
		return (enum_DeviceType)ntohl(m_enumDeviceType);
	}

/*====================================================================
    ����        �������ն��豸����
    �������˵����byConfMtType�����ն��豸����
    ����ֵ˵��  ����
====================================================================*/   
	void SetDeviceType( enum_DeviceType enumDeviceType )
	{
		m_enumDeviceType = (enum_DeviceType)htonl(enumDeviceType);
	}

/*====================================================================
    ����        ���õ��ն��Ƿ�����
    �������˵������
    ����ֵ˵��  ��  true��������
                    false����������
====================================================================*/
	bool IsOnline( void ) const
	{
		return m_byOnline ? true : false;
	}

/*====================================================================
    ����        �������ն��Ƿ�����
    �������˵����bOnline�����ն��Ƿ�����
    ����ֵ˵��  ����
====================================================================*/
	void SetOnline( bool bOnline = false )
	{
		m_byOnline = (u8)(bOnline? 1:0);
	}

/*====================================================================
    ����        ���õ��ն˵�ֱ���ӽڵ����
    �������˵������
    ����ֵ˵��  �� ֱ���ӽڵ����
====================================================================*/
	u16 GetChildCount( void ) const
	{
		return ntohs(m_byChildCount);
	}

/*====================================================================
    ����        �������ն˵�ֱ���ӽڵ����
    �������˵����ֱ���ӽڵ����
    ����ֵ˵��  ����
====================================================================*/
	void SetChildCount( u16 nChildCount )
	{
		m_byChildCount = htons(nChildCount);
	}

/*====================================================================
    ����        ���õ��ն�Email��ַ
    �������˵������
    ����ֵ˵��  ���ն�Email��ַ
====================================================================*/
	LPCSTR GetEmail( void ) const
	{
		return m_achEmail;
	}

/*====================================================================
    ����        �������ն�Email��ַ
    �������˵����lpszEmail�����ն�Email��ַ
    ����ֵ˵��  ����
====================================================================*/
	void SetEmail( LPCSTR lpszEmail )
	{
        if (lpszEmail == NULL)
        {
            memset(m_achEmail, 0, sizeof(m_achEmail));
        }
        else
        {
            if (lpszEmail[0] != 0)
            {
                memcpy( m_achEmail, lpszEmail, sizeof(m_achEmail) );
                m_achEmail[sizeof(m_achEmail) - 1] = '\0';
            }
            else
            {
                memset(m_achEmail, 0, sizeof(m_achEmail));
            }
        }
	}
	
/*====================================================================
    ����        ���õ��ڵ���
    �������˵������
    ����ֵ˵��  ���ڵ���
====================================================================*/
    LPCSTR GetNodeName( void ) const
    {
        return m_achNodeName;
    }
	
/*====================================================================
    ����        �����ýڵ���
    �������˵����lpszNodeName�����ڵ���
    ����ֵ˵��  ����
====================================================================*/
    void SetNodeName( LPCSTR lpszNodeName )
    {
        if (lpszNodeName == NULL)
        {
            memset(m_achNodeName, 0, sizeof(m_achNodeName));
        }
        else
        {
            if(lpszNodeName[0] != 0)
            {
                memcpy( m_achNodeName, lpszNodeName, sizeof(m_achNodeName) );
		        m_achNodeName[sizeof(m_achNodeName) - 1] = '\0';
            }
            else
            {
                memset(m_achNodeName, 0, sizeof(m_achNodeName));
            }
        }
    }
	
/*====================================================================
    ����        ���õ��绰����
    �������˵������
    ����ֵ˵��  ���绰����
====================================================================*/
    LPCSTR GetNodePhone( void ) const
    {
        return m_achNodePhone;
    }
	
/*====================================================================
    ����        �����õ绰����
    �������˵����lpszNodePhone�����绰����
    ����ֵ˵��  ����
====================================================================*/
    void SetNodePhone( LPCSTR lpszNodePhone )
    {
        if (lpszNodePhone == NULL)
        {
            memset(m_achNodePhone, 0, sizeof(m_achNodePhone));
        }
        else
        {
            if(lpszNodePhone[0] != 0)
            {
                memcpy( m_achNodePhone, lpszNodePhone, sizeof(m_achNodePhone) );
                m_achNodePhone[sizeof(m_achNodePhone) - 1] = '\0';
            }
            else
            {
                memset(m_achNodePhone, 0, sizeof(m_achNodePhone));
            }
        }
    }
	
/*====================================================================
    ����        ���õ��ڵ�λ��
    �������˵������
    ����ֵ˵��  ���ڵ�λ��
====================================================================*/
    LPCSTR GetNodeLocation( void ) const
    {
        return m_achNodeLocation;
    }
	
/*====================================================================
    ����        �����ýڵ�λ��
    �������˵����lpszNodeLocation�����ڵ�λ��
    ����ֵ˵��  ����
====================================================================*/
    void SetNodeLocation( LPCSTR lpszNodeLocation )
    {
        if (lpszNodeLocation == NULL)
        {
            memset(m_achNodeLocation, 0, sizeof(m_achNodeLocation));
        }
        else
        {
            if(lpszNodeLocation[0] != 0)
            {
                memcpy( m_achNodeLocation, lpszNodeLocation, sizeof(m_achNodeLocation) );
		        m_achNodeLocation[sizeof(m_achNodeLocation) - 1] = '\0';
            }
            else
            {
                memset(m_achNodeLocation, 0, sizeof(m_achNodeLocation));
            }
        }
    }

/*====================================================================
    ����        ���ж��ն��Ƿ����
    �������˵����tMt������һ�ն���Ϣ
    ����ֵ˵��  ��true�������
                  false���������
====================================================================*/
	bool IsEqual(const TDCMt& tMt)
	{
        return ( (strcmp(GetAlias(), tMt.GetAlias())==0) &&
                (GetConfMtType()==tMt.GetConfMtType()) )? true:false;
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//������Ϣ
struct TDataConfInfo
{
private:
	CConfId	m_cConfId;						            //�����
	char	m_achConfName[MAX_DC_CONFNAME_LENGTH];		//��������
	char	m_achConfPassword[MAX_DC_PASSWORD_LENGTH];	//��������
	
	u8	    m_byConfProperty;   //�������Բ���,��8λ,��λ��������:(�ӵ͵���)
	                            //��1λ:�Ƿ�����ն���������    (0:��֧��,1:֧��)
	                            //��2λ:�Ƿ��Զ���������ն�    (0:��֧��,1:֧��)
	                            //��3λ:�Ƿ�locked              (0:��    ,1:��  )
	                            //��4λ:������ֹ����            (0:auto  ,1:manual)
	                            //��5λ:�����Ƿ�֧����ϯ        (0:��֧��,1:֧��)
	                            //��6λ:�����Ƿ�������          (0:û��  ,1:��)
	
	u8	    m_byConfAppPara;    //����Ӧ�ò���,��8λ,��λ��������:(�ӵ͵���)
	                            //��1λ:�Ƿ�֧��Ӧ�ó�����    (0:��֧��,1:֧��)
	                            //��2λ:�Ƿ�֧�ֵ��Ӱװ�        (0:��֧��,1:֧��)
	                            //��3λ:�Ƿ�֧���ļ�����        (0:��֧��,1:֧��)
	                            //��4λ:�Ƿ�֧������            (0:��֧��,1:֧��)
	
	TDCMt	m_tChairman;	    //������ϯ�ն�
	u32	    m_dwBandwidth;		//������ߴ�������
	u16	    m_wDuration;		//�������ʱ��( ����Ϊ��λ,0��ʾ���Զ����� ),������

    u8      m_byIsLocalConf;    //�Ƿ�Ϊ���ػ���(0:����   1:��  Ĭ��Ϊ1)
    u8      m_byIsH323Call;     //�Ƿ�ͨ��H323����(0:���� 1���� Ĭ��Ϊ0);
	
public:
	TDataConfInfo( void )
	{
		memset( m_achConfName , 0, sizeof(m_achConfName) );
		memset( m_achConfPassword , 0, sizeof(m_achConfPassword) );
		m_byConfAppPara = 0;
		m_byConfProperty = 0;
		m_dwBandwidth = htonl(1024);	
		m_wDuration = 0;
        m_byIsLocalConf = 1;
        m_byIsH323Call = 0;
	}
	
/*====================================================================
    ����        ���õ������
    �������˵������
    ����ֵ˵��  �������
====================================================================*/
	const CConfId & GetConfId( void ) const
	{
		return m_cConfId;
	}
	
/*====================================================================
    ����        �����û����
    �������˵����cConfId���������
    ����ֵ˵��  ����
====================================================================*/
	void SetConfId( const CConfId & cConfId )
	{
		m_cConfId = cConfId;
	}
	
/*====================================================================
    ����        ���õ�������
    �������˵������
    ����ֵ˵��  ��������
====================================================================*/
	LPCSTR GetConfName( void ) const
	{
		return m_achConfName;
	}

/*====================================================================
    ����        �����û�����
    �������˵����lpszConfName����������
    ����ֵ˵��  ����
====================================================================*/
	void SetConfName( LPCSTR lpszConfName )
	{
        if (lpszConfName == NULL)
        {
            m_achConfName[0] = '\0';
        }
        else
        {
		    strncpy( m_achConfName, lpszConfName, sizeof(m_achConfName) );
		    m_achConfName[sizeof(m_achConfName) - 1] = '\0';
        }
	}
	
/*====================================================================
    ����        ���������Բ���
    �������˵������
    ����ֵ˵��  ���������Բ���
====================================================================*/
    u8 GetConfProperty() const
    {
        return m_byConfProperty;
    }
    
/*====================================================================
    ����        �����û������Բ���
    �������˵����byConfProperty�����������Բ���
    ����ֵ˵��  ����
====================================================================*/
    void SetConfProperty( u8 byConfProperty )
    {
        m_byConfProperty = byConfProperty;
    }
	
/*====================================================================
    ����        ���õ�����Ӧ�ò���
    �������˵������
    ����ֵ˵��  ������Ӧ�ò���
====================================================================*/
    u8 GetConfAppPara() const
    {
        return m_byConfAppPara;
    }
    
/*====================================================================
    ����        �����û���Ӧ�ò���
    �������˵����byConfPara��������Ӧ�ò���
    ����ֵ˵��  ����
====================================================================*/
    void SetConfAppPara( u8 byConfPara )
    {
        m_byConfAppPara = byConfPara;
    }

/*====================================================================
    ����        ���õ������Ƿ�֧��Ӧ�ù���
    �������˵������
    ����ֵ˵��  ��  true����֧��
                    false������֧��
====================================================================*/
	bool IsEnableAppSharing( void ) const
	{
		return ( (m_byConfAppPara & CONF_ENABLE_APPSHARING) == CONF_ENABLE_APPSHARING ) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�֧��Ӧ�ù���
    �������˵����bEnable���������Ƿ�֧��Ӧ�ù���
    ����ֵ˵��  ����
====================================================================*/
	void SetEnableAppSharing( bool bEnable = true )
	{
		if(bEnable)
			m_byConfAppPara |= CONF_ENABLE_APPSHARING;
		else
			m_byConfAppPara &= ~CONF_ENABLE_APPSHARING;
	}
	
/*====================================================================
    ����        ���õ������Ƿ�֧�ֵ��Ӱװ�
    �������˵������
    ����ֵ˵��  ��  true����֧��
                    false������֧��
====================================================================*/
	bool IsEnableWhiteboard( void ) const
	{
		return ((m_byConfAppPara & CONF_ENABLE_WHITEBOARD) == CONF_ENABLE_WHITEBOARD) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�֧�ֵ��Ӱװ�
    �������˵����bEnable���������Ƿ�֧�ֵ��Ӱװ�
    ����ֵ˵��  ����
====================================================================*/
	void SetEnableWhiteboard( bool bEnable = true )
	{
		if(bEnable)
			m_byConfAppPara |= CONF_ENABLE_WHITEBOARD;
		else
			m_byConfAppPara &= ~CONF_ENABLE_WHITEBOARD;
	}
	
/*====================================================================
    ����        ���õ������Ƿ�֧���ļ�����
    �������˵������
    ����ֵ˵��  ��  true����֧��
                    false������֧��
====================================================================*/
	bool IsEnableFileTransfer( void ) const
	{
		return ((m_byConfAppPara & CONF_ENABLE_FILETRANSFER) == CONF_ENABLE_FILETRANSFER) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�֧���ļ�����
    �������˵����bEnable���������Ƿ�֧���ļ�����
    ����ֵ˵��  ����
====================================================================*/
	void SetEnableFileTransfer( bool bEnable = true )
	{
		if(bEnable)
			m_byConfAppPara |= CONF_ENABLE_FILETRANSFER;
		else
			m_byConfAppPara &= ~CONF_ENABLE_FILETRANSFER;
	}
	
/*====================================================================
    ����        ���õ������Ƿ�֧������
    �������˵������
    ����ֵ˵��  ��  true����֧��
                    false������֧��
====================================================================*/
	bool IsEnableChat( void ) const
	{
		return ((m_byConfAppPara & CONF_ENABLE_CHAT) == CONF_ENABLE_CHAT) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�֧������
    �������˵����bEnable���������Ƿ�֧������
    ����ֵ˵��  ����
====================================================================*/
	void SetEnableChat( bool bEnable = true )
	{
		if(bEnable)
			m_byConfAppPara |= CONF_ENABLE_CHAT;
		else
			m_byConfAppPara &= ~CONF_ENABLE_CHAT;
	}
	
/*====================================================================
    ����        ���õ������Ƿ�֧���ն���������
    �������˵������
    ����ֵ˵��  ��  true����֧��
                    false������֧��
====================================================================*/
	bool IsAcceptMtCall( void ) const
	{
		return ((m_byConfProperty & CONF_ENABLE_ACCEPTMTCALL) == CONF_ENABLE_ACCEPTMTCALL) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�֧���ն���������
    �������˵����bEnable���������Ƿ�֧���ն���������
    ����ֵ˵��  ����
====================================================================*/
	void SetAcceptMtCall( bool bEnable = true )
	{
		if(bEnable)
			m_byConfProperty |= CONF_ENABLE_ACCEPTMTCALL;
		else
			m_byConfProperty &= ~CONF_ENABLE_ACCEPTMTCALL;
	}
	
/*====================================================================
    ����        ���õ������Ƿ�֧���Զ����������ն�
    �������˵������
    ����ֵ˵��  ��true����֧��
                  false������֧��
====================================================================*/
	bool IsAutoInviteMt( void ) const
	{
		return ((m_byConfProperty & CONF_ENABLE_AUTOINVITEMT) == CONF_ENABLE_AUTOINVITEMT) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�֧���Զ����������ն�
    �������˵����bEnable���������Ƿ�֧���Զ����������ն�
    ����ֵ˵��  ����
====================================================================*/
	void SetAutoInviteMt( bool bEnable = true )
	{
		if(bEnable)
			m_byConfProperty |= CONF_ENABLE_AUTOINVITEMT;
		else
			m_byConfProperty &= ~CONF_ENABLE_AUTOINVITEMT;
	}
	
/*====================================================================
    ����        ���õ������Ƿ�����
    �������˵������
    ����ֵ˵��  ��  true��������
                    false����������
====================================================================*/
	bool IsConfLocked( void ) const
	{
		return ((m_byConfProperty & CONF_ENABLE_LOCKED) == CONF_ENABLE_LOCKED) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�����
    �������˵����bEnable���������Ƿ�����
    ����ֵ˵��  ����
====================================================================*/
	void SetConfLocked( bool bEnable = true )
	{
		if(bEnable)
			m_byConfProperty |= CONF_ENABLE_LOCKED;
		else
			m_byConfProperty &= ~CONF_ENABLE_LOCKED;
	}
	
/*====================================================================
    ����        ���õ������Ƿ��ֶ���ֹ
    �������˵������
    ����ֵ˵��  ��  true�����ֶ���ֹ
                    false�������ֶ���ֹ
====================================================================*/
	bool IsConfTmManual( void ) const
	{
		return ((m_byConfProperty & CONF_ENABLE_TMMANUAL) == CONF_ENABLE_TMMANUAL) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ��ֶ���ֹ
    �������˵����bEnable���������Ƿ��ֶ���ֹ
    ����ֵ˵��  ����
====================================================================*/
	void SetConfTmManual( bool bEnable = true )
	{
		if(bEnable)
			m_byConfProperty |= CONF_ENABLE_TMMANUAL;
		else
			m_byConfProperty &= ~CONF_ENABLE_TMMANUAL;
	}
	
/*====================================================================
    ����        ���õ������Ƿ�֧����ϯ
    �������˵������
    ����ֵ˵��  ��  true����֧��
                    false������֧��
====================================================================*/
	bool IsConfSupportChairman( void ) const
	{
		return ((m_byConfProperty & CONF_SUPPORT_CHAIRMAN) == CONF_SUPPORT_CHAIRMAN) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ�֧����ϯ
    �������˵����bEnable���������Ƿ�֧����ϯ
    ����ֵ˵��  ����
====================================================================*/
	void SetConfSupportChairman( bool bEnable = true )
	{
		if(bEnable)
			m_byConfProperty |= CONF_SUPPORT_CHAIRMAN;
		else
			m_byConfProperty &= ~CONF_SUPPORT_CHAIRMAN;
	}
	
/*====================================================================
    ����        ���õ������Ƿ���Ҫ������ܼ���
    �������˵������
    ����ֵ˵��  ��  true������Ҫ
                    false��������Ҫ
====================================================================*/
	bool IsNeedPassword( void ) const
	{
        return ((m_byConfProperty & CONF_NEED_PASSWORD) == CONF_NEED_PASSWORD) ? true : false;
	}

/*====================================================================
    ����        �����û����Ƿ���Ҫ������ܼ���
    �������˵����bEnable���������Ƿ���Ҫ������ܼ���
    ����ֵ˵��  ����
====================================================================*/
	void SetNeedPassword( bool bEnable = true )
	{
		if(bEnable)
			m_byConfProperty |= CONF_NEED_PASSWORD;
		else
			m_byConfProperty &= ~CONF_NEED_PASSWORD;
	}
	
/*====================================================================
    ����        ���õ���������
    �������˵������
    ����ֵ˵��  ����������
====================================================================*/
	LPCSTR GetConfPassword( void ) const
	{
		return m_achConfPassword;
	}

/*====================================================================
    ����        �����û�������
    �������˵����lpszConfPassword������������
    ����ֵ˵��  ����
====================================================================*/
	void SetConfPassword( LPCSTR lpszConfPassword )
	{
        if (lpszConfPassword == NULL)
        {
		    m_achConfPassword[0] = '\0';
        }
        else
        {
		    strncpy( m_achConfPassword, lpszConfPassword, sizeof(m_achConfPassword) );
		    m_achConfPassword[sizeof(m_achConfPassword) - 1] = '\0';
        }
	}
	
/*====================================================================
    ����        ���õ���ϯ�ն���Ϣ
    �������˵������
    ����ֵ˵��  ����ϯ�ն���Ϣ
====================================================================*/
	TDCMt & GetChairman( void ) const
	{
		return (TDCMt&)m_tChairman;
	}
	
/*====================================================================
    ����        �����û�����ϯ�ն�
    �������˵����tChairman����������ϯ�ն�
    ����ֵ˵��  ����
====================================================================*/
	void SetChairman( const TDCMt& tChairman )
	{
		m_tChairman = tChairman;
	}
	
/*====================================================================
    ����        ���õ���������������
    �������˵������
    ����ֵ˵��  ����������������
====================================================================*/
	u32	GetBandwidth( void ) const
	{
		return ntohl( m_dwBandwidth );
	}

/*====================================================================
    ����        �����û�������������
    �������˵����dwBandwidth������������������
    ����ֵ˵��  ����
====================================================================*/
	void SetBandwidth( u32 dwBandwidth )
	{
		m_dwBandwidth = htonl( dwBandwidth );
	}
	
/*====================================================================
    ����        ���õ��������ʱ��
    �������˵������
    ����ֵ˵��  ���������ʱ��
====================================================================*/
	u16	GetDuration( void ) const
	{
		return ntohs( m_wDuration );
	}

/*====================================================================
    ����        �����û������ʱ��
    �������˵����wDuration�����������ʱ��
    ����ֵ˵��  ����
====================================================================*/
	void SetDuration( u16 wDuration )
	{
		m_wDuration = htons( wDuration );
	}

/*====================================================================
    ���ܣ�        �Ƿ�Ϊ���ػ���
    �������˵������
    ����ֵ˵��  ��true������
                  false������
====================================================================*/
    bool IsLocalConf() const
    {
        return m_byIsLocalConf? true:false;
    }
    
/*====================================================================
    ����        �������Ƿ�Ϊ���ػ���
    �������˵����bIsLocalConf�����Ƿ�Ϊ���ػ���
    ����ֵ˵��  ����
====================================================================*/
    void SetLocalConf( bool bIsLocalConf )
    {
        m_byIsLocalConf = (u8)(bIsLocalConf? 1:0);
    }

/*====================================================================
    ���ܣ�        �Ƿ�ͨ��H323����
    �������˵������
    ����ֵ˵��  ��true������
                  false������
====================================================================*/
    bool IsH323Call() const
    {
        return m_byIsH323Call? true:false;
    }
    
/*====================================================================
    ����        �������Ƿ�ͨ��H323����
    �������˵����bIsH323Call�����Ƿ�ͨ��H323����
    ����ֵ˵��  ����
====================================================================*/
    void SetH323Call( bool bIsH323Call )
    {
        m_byIsH323Call = (u8)(bIsH323Call? 1:0);
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//������ϸ��Ϣ
struct TDataConfFullInfo : public TDataConfInfo
{
protected:
	u8	    m_byMtCount;					//��ǰ���������ն�����
	TDCMt	m_tDCMt[MAX_MT_IN_DATACONF];	//���ݻ����ն��б�
public:
	TDataConfFullInfo( void )
	{
		m_byMtCount = 0;
        memset( m_tDCMt, 0, sizeof(m_tDCMt) );
	}
/*====================================================================
    ����        ���õ������ն�����
    �������˵������
    ����ֵ˵��  �������ն�����
====================================================================*/
	u8 GetMtCount( void ) const
	{
		return m_byMtCount;
	}

/*====================================================================
    ����        �����û����ն�����
    �������˵����byMtCount���������ն�����
    ����ֵ˵��  ����
====================================================================*/
    void SetMtCount( u8 byMtCount )
    {
        m_byMtCount = byMtCount;
    }

/*====================================================================
    ����        ���õ��������ն�
    �������˵����byIndex�����ն�����
    ����ֵ˵��  ���ն�ָ��
====================================================================*/
	const TDCMt* GetTDCMt( u8 byIndex ) const
	{
		if( byIndex <= (m_byMtCount-1) )
		{
		    return &(m_tDCMt[byIndex]);
		}
		else
		{
			return NULL;
		}
	}

/*====================================================================
    ����        ���õ��������ն�
    �������˵����byIndex�����ն�����
    ����ֵ˵��  ���ն�ָ��
====================================================================*/
	const TDCMt* GetTDCMt( const TDCMt& tDCMt )
	{
        for( int i=0 ; i<m_byMtCount ; i++ )
        {
            if( m_tDCMt[i].IsEqual(tDCMt) )
                return &(m_tDCMt[i]);
        }
        return NULL;
	}
	
/*====================================================================
    ����        ��  �õ������������ն�
    �������˵����  ptDCMtBuf����������ָ��
                    byBufsize�����ն�����
    ����ֵ˵��  ��  ʵ���ն�����
====================================================================*/
	u8 GetAllMt( TDCMt* ptDCMtBuf , u8 byBufsize )
	{
		byBufsize = (byBufsize<m_byMtCount) ? byBufsize : m_byMtCount;
		
		memcpy( ptDCMtBuf, m_tDCMt, sizeof(TDCMt)*byBufsize );
		return byBufsize;
	}
	
/*====================================================================
    ����        ��  �ڻ����м����ն�
    �������˵����  tDCMt�����ն���Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	bool AddMt( const TDCMt & tDCMt )
	{
		if( m_byMtCount >= MAX_MT_IN_DATACONF )
			return false;
		else
		{
			m_tDCMt[m_byMtCount] = tDCMt;
			m_byMtCount++;
			return true;
		}
	}
	
/*====================================================================
    ����        ��  �ڻ������˳��ն�
    �������˵����  tDCMt�����ն���Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	void RemoveMt( const TDCMt & tDCMt )
	{
        if(GetChairman().IsEqual(tDCMt))
        {
            TDCMt tMt;
            SetChairman(tMt);
        }
        
		for( int i = 0 ; i < m_byMtCount ; i++ )
		{
			if( m_tDCMt[i].IsEqual(tDCMt) )
			{
				for( int j = i + 1; j < m_byMtCount; j++ )
				{
					m_tDCMt[j-1] = m_tDCMt[j];
				}
				m_byMtCount--;
				return;
			}	
        }
	}
	
/*====================================================================
    ����        ��  �ڻ������˳������ն�
    �������˵����  ��
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	void RemoveAllMt( void )
	{
		m_byMtCount = 0;
        memset( m_tDCMt, 0, sizeof(m_tDCMt) );
	}
	
/*====================================================================
    ����        ��  �ж��ն��Ƿ�����
    �������˵����  tMt�����ն���Ϣ
    ����ֵ˵��  ��  true��������
                    false����������
====================================================================*/
	bool MtInConf( const TDCMt & tMt )
	{
		for( int i = 0; i < m_byMtCount; i++ )
		{
			if( m_tDCMt[i].IsEqual(tMt) )
			{
				return true;
			}
		}
		return false;
	}
    
/*====================================================================
    ����        ��  �ж��ն��Ƿ�����
    �������˵����  tMt�����ն���Ϣ
    ����ֵ˵��  ��  true��������
                    false����������
====================================================================*/
    bool MtJoinedConf( const TDCMt & tMt )
    {
        for( int i = 0; i < m_byMtCount; i++ )
        {
            if( m_tDCMt[i].IsEqual(tMt) )
            {
                return (m_tDCMt[i].IsOnline());
            }
        }
        return false;
    }
	
/*====================================================================
    ����        ��  �޸��ն�״̬
    �������˵����  tMt�����ն���Ϣ
    ����ֵ˵��  ��  ��
====================================================================*/
	void ModifyMt( const TDCMt & tDCMt )
	{
		for( int i = 0; i < m_byMtCount; i++ )
		{
			if( m_tDCMt[i].IsEqual(tDCMt) )
			{
				m_tDCMt[i] = tDCMt;
				return;
			}
		}
	}

/*====================================================================
    ����        ��  ���������ն˵����߻�����״̬
    �������˵����  bOnline�������߻�����
    ����ֵ˵��  ��  ��
====================================================================*/
	void SetAllMtsOnline(bool bOnline)
	{
		for( int i = 0; i < m_byMtCount; i++ )
		{
			m_tDCMt[i].SetOnline(bOnline);
		}
	}
	
/*====================================================================
    ����        ����ֵ����������
    �������˵����TDataConfFullInfo& tDcConf, ��ֵ����Ϣ����
    ����ֵ˵��  ��TDataConfFullInfo��������
====================================================================*/
	TDataConfFullInfo& operator=(const TDataConfFullInfo& tDCConf) 
	{
		m_byMtCount = tDCConf.GetMtCount();
		for(u8 i = 0; i < GetMtCount(); i++)
		{
			const TDCMt *pMt = tDCConf.GetTDCMt(i);
			if( pMt!=NULL )
			{
				m_tDCMt[i] = *pMt;
			}
		}
		
		SetConfId(tDCConf.GetConfId());
		SetConfName(tDCConf.GetConfName());
		SetConfPassword(tDCConf.GetConfPassword());
		
		SetConfAppPara(tDCConf.GetConfAppPara());
		SetConfProperty(tDCConf.GetConfProperty());
		SetChairman(tDCConf.GetChairman());
		SetBandwidth(tDCConf.GetBandwidth());
		SetDuration(tDCConf.GetDuration());
        SetLocalConf(tDCConf.IsLocalConf());
        SetH323Call(tDCConf.IsH323Call());
		return *this;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//ģ����Ϣ
struct TDataConfTemplate : public TDataConfInfo
{
protected:
	CConfId	m_cConfTemplateId;						        //ģ���
	char	m_achConfTemplateName[MAX_DC_CONFNAME_LENGTH];	//ģ����

    u8	        m_byBaseMtCount;					    //��ǰģ�������ն�����
    TDCBaseMt	m_tDCBaseMt[MAX_MT_IN_DATACONF];	    //ģ���ն��б�

public:
    TDataConfTemplate( void )
	{
        m_cConfTemplateId.SetNull();
		memset( m_achConfTemplateName , 0, sizeof(m_achConfTemplateName) );

        m_byBaseMtCount = 0;
        memset( m_tDCBaseMt, 0, sizeof(m_tDCBaseMt) );
	}

/*====================================================================
    ����        ��  �õ�ģ���
    �������˵����  ��
    ����ֵ˵��  ��  ģ���
====================================================================*/
	const CConfId & GetConfTemplateId( void ) const
	{
		return m_cConfTemplateId;
	}

/*====================================================================
    ����        ��  ����ģ���
    �������˵����  cConfId����ģ���
    ����ֵ˵��  ��  ��
====================================================================*/
	void SetConfTemplateId( const CConfId & cConfId )
	{
		m_cConfTemplateId = cConfId;
	}
	
/*====================================================================
    ����        ��  �õ�ģ����
    �������˵����  ��
    ����ֵ˵��  ��  ģ����
====================================================================*/
	LPCSTR GetConfTemplateName( void ) const
	{
		return m_achConfTemplateName;
	}

/*====================================================================
    ����        ��  ����ģ����
    �������˵����  lpszConfTemplateName��������ģ����
    ����ֵ˵��  ��  ��
====================================================================*/
	void SetConfTemplateName( LPCSTR lpszConfTemplateName )
	{
		strncpy( m_achConfTemplateName, lpszConfTemplateName, sizeof(m_achConfTemplateName) );
		m_achConfTemplateName[sizeof(m_achConfTemplateName) - 1] = '\0';
	}	

/*====================================================================
    ����        ���õ�ģ���ն�����
    �������˵������
    ����ֵ˵��  �������ն�����
====================================================================*/
	u8 GetBaseMtCount( void ) const
	{
		return m_byBaseMtCount;
	}

/*====================================================================
    ����        ������ģ���ն�����
    �������˵����byMtCount���������ն�����
    ����ֵ˵��  ����
====================================================================*/
    void SetBaseMtCount( u8 byBaseMtCount )
    {
        m_byBaseMtCount = byBaseMtCount;
    }

/*====================================================================
    ����        ���õ�ģ�����ն�
    �������˵����byIndex�����ն�����
    ����ֵ˵��  ���ն�ָ��
====================================================================*/
	const TDCBaseMt *GetTDCBaseMt( u8 byIndex ) const
	{
		if( byIndex <= (m_byBaseMtCount-1) )
		{
		    return &(m_tDCBaseMt[byIndex]);
		}
		else
		{
			return NULL;
		}
	}
	
/*====================================================================
    ����        ��  �õ�ģ���������ն�
    �������˵����  ptDCBaseMtBuf����������ָ��
                    byBufsize�����ն�����
    ����ֵ˵��  ��  ʵ���ն�����
====================================================================*/
	u8 GetAllBaseMt( TDCBaseMt* ptDCBaseMtBuf , u8 byBufsize )
	{
		byBufsize = (byBufsize<m_byBaseMtCount) ? byBufsize : m_byBaseMtCount;
		
		memcpy( ptDCBaseMtBuf, m_tDCBaseMt, sizeof(TDCBaseMt)*byBufsize );
		return byBufsize;
	}
	
/*====================================================================
    ����        ��  ��ģ���м����ն�
    �������˵����  tMt�����ն���Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	bool AddBaseMt( const TDCBaseMt & tMt )
	{
		if( m_byBaseMtCount >= MAX_MT_IN_DATACONF )
			return false;
		else
		{
			m_tDCBaseMt[m_byBaseMtCount] = tMt;
			m_byBaseMtCount++;
			return true;
		}
	}
	
///*====================================================================
//    ����        ��  ��ģ����ɾ���ն�
//    �������˵����  tMt�����ն���Ϣ
//    ����ֵ˵��  ��  true�����ɹ�
//                    false����ʧ��
//====================================================================*/
//	void RemoveBaseMt( const TDCBaseMt & tMt )
//	{
//		for( int i = 0 ; i < m_byBaseMtCount ; i++ )
//		{
//			if( m_tDCBaseMt[i].IsEqual(tMt) )
//			{
//				for( int j = i + 1; j < m_byBaseMtCount; j++ )
//				{
//					m_tDCBaseMt[j-1] = m_tDCBaseMt[j];
//				}
//				m_byBaseMtCount--;
//				break;
//			}
//        }
//	}
	
/*====================================================================
    ����        ��  ��ģ����ɾ�������ն�
    �������˵����  ��
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	void RemoveAllBaseMt( void )
	{
		m_byBaseMtCount = 0;
        memset( m_tDCBaseMt, 0, sizeof(m_tDCBaseMt) );
	}
	
/*====================================================================
    ����        ��  �ж��ն��Ƿ���ģ����
    �������˵����  tMt�����ն���Ϣ
    ����ֵ˵��  ��  true��������
                    false����������
====================================================================*/
	bool BaseMtInTemplate( const TDCBaseMt & tMt )
	{
		for( int i = 0; i < m_byBaseMtCount; i++ )
		{
			if( m_tDCBaseMt[i].IsEqual(tMt) )
			{
				return true;
			}
		}
		return false;
	}
    
///*====================================================================
//    ����        ��  �޸��ն�״̬
//    �������˵����  tMt�����ն���Ϣ
//    ����ֵ˵��  ��  ��
//====================================================================*/
//	void ModifyBaseMt( const TDCBaseMt & tMt )
//	{
//		for( int i = 0; i < m_byBaseMtCount; i++ )
//		{
//			if( m_tDCBaseMt[i].IsEqual(tMt) )
//			{
//				m_tDCBaseMt[i] = tMt;
//				return;
//			}
//		}
//	}

/*====================================================================
    ����        ����ֵ����������
    �������˵����TDataConfTemplate& tDcTeml, ��ֵ����Ϣ����
    ����ֵ˵��  ��TDataConfTemplate��������
====================================================================*/
	TDataConfTemplate& operator=(const TDataConfTemplate& tTemplate) 
	{
		SetConfTemplateId(tTemplate.GetConfTemplateId());
		SetConfTemplateName(tTemplate.GetConfTemplateName());
		
		m_byBaseMtCount = tTemplate.GetBaseMtCount();
		for(u8 i = 0; i < m_byBaseMtCount; i++)
		{
			const TDCBaseMt *pMt = tTemplate.GetTDCBaseMt(i);
			if( pMt!=NULL )
			{
				m_tDCBaseMt[i] = *pMt;
			}
		}
		
		SetConfId(tTemplate.GetConfId());
		SetConfName(tTemplate.GetConfName());
		SetConfPassword(tTemplate.GetConfPassword());
		
		SetConfAppPara(tTemplate.GetConfAppPara());
		SetConfProperty(tTemplate.GetConfProperty());
		SetChairman(tTemplate.GetChairman());
		SetBandwidth(tTemplate.GetBandwidth());
		SetDuration(tTemplate.GetDuration());
        SetLocalConf(tTemplate.IsLocalConf());
        SetH323Call(tTemplate.IsH323Call());

		return *this;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifdef _WIN32
//�ٽ�������
class CSection
{
private:
	CRITICAL_SECTION* m_pSection;
public:
	CSection(CRITICAL_SECTION* pSection)
	{
        m_pSection=pSection;
        EnterCriticalSection(m_pSection);
	}

	~CSection()
	{
		if(m_pSection != NULL)
			LeaveCriticalSection(m_pSection);
	}
};
#else
class PMutex;
#endif


//��ַ��
class CAddrBook_DC  
{
public:
	CAddrBook_DC()
	{
#ifdef _WIN32
        //�ٽ�����ʼ��
        InitializeCriticalSection(&m_Section_MtEntry);
        InitializeCriticalSection(&m_Section_ConfEntry);
#endif
	}
	~CAddrBook_DC()
	{
#ifdef _WIN32
        //�ٽ�������
        DeleteCriticalSection(&m_Section_MtEntry);
        DeleteCriticalSection(&m_Section_ConfEntry);
#endif
	}
	
protected:

#ifdef _WIN32
    CRITICAL_SECTION m_Section_MtEntry;     //Windows���ն��б�����ٽ���
    CRITICAL_SECTION m_Section_ConfEntry;   //Windows�»���ģ���б�����ٽ���
#else
    PMutex  m_mutex_MtEntry;        //Linux���ն��б���ʻ�����
    PMutex  m_mutex_ConfEntry;      //Linux�»���ģ���б���ʻ�����
#endif
    
    std::vector<TDCBaseMt>	m_vtDCBaseMt;						//�ն��б�
	std::vector<TDataConfTemplate>	m_vtDCTemplate;				//����ģ���б�
	typedef std::vector<TDCBaseMt>::iterator itorMt;             //�ն��б�����
	typedef std::vector<TDataConfTemplate>::iterator itorConf;   //����ģ���б�����
	
public:
    
/*====================================================================
    ����        ��  ���б��еõ��ն�
    �������˵����  tDCBaseMt�����ն�����Ϣ
                    tDCBaseMtOld�����ն�ԭ��Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
    bool GetMtEntry( const TDCBaseMt tDCBaseMt, TDCBaseMt & tDCBaseMtOld )
    {
#ifdef _WIN32
        CSection lock(&m_Section_MtEntry);
#else
        PWaitAndSignal lock(m_mutex_MtEntry);
#endif

        for( itorMt i=m_vtDCBaseMt.begin(); i<m_vtDCBaseMt.end(); i++ )
        {
            if( (*i).IsEqual(tDCBaseMt) )
            {
                tDCBaseMtOld = (*i);
                return true;
            }
        }
        return false;
    }
	
/*====================================================================
    ����        ��  ���б��еõ�����ģ��
    �������˵����  cConfId��������ģ���
                    tDCTmplOld��������ģ��ԭ��Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
    bool GetConfEntryById( const CConfId cConfId, TDataConfTemplate & tDCTmplOld )
    {
#ifdef _WIN32
        CSection lock(&m_Section_ConfEntry);
#else
        PWaitAndSignal lock(m_mutex_ConfEntry);
#endif

        for( itorConf i=m_vtDCTemplate.begin(); i<m_vtDCTemplate.end(); i++ )
        {
            if( (*i).GetConfTemplateId() == cConfId )
            {
                tDCTmplOld = (*i);
                return true;
            }
        }
        return false;
    }
    
/*====================================================================
    ����        ��  ͨ��ģ�������б��еõ�����ģ��
    �������˵����  lpszTemplateName��������ģ����
                    tDCTmplOld��������ģ��ԭ��Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
    bool GetConfEntryByName( LPCSTR lpszTemplateName, TDataConfTemplate & tDCTmplOld )
    {
#ifdef _WIN32
        CSection lock(&m_Section_ConfEntry);
#else
        PWaitAndSignal lock(m_mutex_ConfEntry);
#endif

        for( itorConf i=m_vtDCTemplate.begin(); i<m_vtDCTemplate.end(); i++ )
        {
            if( strcmp((*i).GetConfTemplateName(), lpszTemplateName)==0 )
            {
                tDCTmplOld = (*i);
                return true;
            }
        }
        return false;
    }

/*====================================================================
    ����        ��  �ж��ն����Ƿ�����
    �������˵����  
    ����ֵ˵��  ��  true��������
                    false��������
====================================================================*/
    bool IsMtEntryFull()
    {
#ifdef _WIN32
        CSection lock(&m_Section_MtEntry);
#else
        PWaitAndSignal lock(m_mutex_MtEntry);
#endif
    
        return (m_vtDCBaseMt.size()>=MAX_MTENTRY_NUM);
    }
    
/*====================================================================
    ����        ��  ���б�������ն���Ŀ
    �������˵����  tDCBaseMt�����ն���Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	bool AddMtEntry( const TDCBaseMt& tDCBaseMt )
	{
#ifdef _WIN32
        CSection lock(&m_Section_MtEntry);
#else
        PWaitAndSignal lock(m_mutex_MtEntry);
#endif
            
        if( m_vtDCBaseMt.size()>=MAX_MTENTRY_NUM )
        {
            return false;
        }
        
		for( itorMt i=m_vtDCBaseMt.begin(); i<m_vtDCBaseMt.end(); i++ )
		{
			if( (*i).IsEqual(tDCBaseMt) )
			{
				return false;
			}
		}		
		m_vtDCBaseMt.push_back( tDCBaseMt );
		return true;
	}

/*====================================================================
    ����        ��  ���б���ɾ���ն���Ŀ
    �������˵����  tDCBaseMt�����ն���Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	bool RemoveMtEntry( TDCBaseMt tDCBaseMt )
	{
#ifdef _WIN32
        CSection lock(&m_Section_MtEntry);
#else
        PWaitAndSignal lock(m_mutex_MtEntry);
#endif
            
		for( itorMt i=m_vtDCBaseMt.begin(); i<m_vtDCBaseMt.end(); i++ )
		{
			if( (*i).IsEqual(tDCBaseMt) )
			{
				m_vtDCBaseMt.erase(i);
				return true;
			}
		}
		return true;
	}

/*====================================================================
    ����        ��  ���б����޸��ն���Ŀ
    �������˵����  tDCBaseMt�����ն���Ϣ
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	bool ModifyMtEntry( const TDCBaseMt& tDCBaseMt )
	{
#ifdef _WIN32
        CSection lock(&m_Section_MtEntry);
#else
        PWaitAndSignal lock(m_mutex_MtEntry);
#endif

		for( itorMt i=m_vtDCBaseMt.begin(); i<m_vtDCBaseMt.end(); i++ )
		{
			if( (*i).IsEqual(tDCBaseMt) )
			{
				(*i) = tDCBaseMt;
				return true;
			}
		}		
		return false;
	}

/*====================================================================
    ����        ��  �ж�ģ�����Ƿ�����
    �������˵����  
    ����ֵ˵��  ��  true��������
                    false��������
====================================================================*/
    bool IsConfEntryFull()
    {
#ifdef _WIN32
        CSection lock(&m_Section_ConfEntry);
#else
        PWaitAndSignal lock(m_mutex_ConfEntry);
#endif
    
        return (m_vtDCTemplate.size()>=MAX_CONFENTRY_NUM); 
    }
	
/*====================================================================
    ����        ��  ���б�����ӻ���ģ��
    �������˵����  tDCTemplate��������ģ��
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	bool AddConfEntry( const TDataConfTemplate& tDCTemplate )
	{
#ifdef _WIN32
        CSection lock(&m_Section_ConfEntry);
#else
        PWaitAndSignal lock(m_mutex_ConfEntry);
#endif

		for( itorConf i=m_vtDCTemplate.begin(); i<m_vtDCTemplate.end(); i++ )
		{
			if( (*i).GetConfTemplateId() == tDCTemplate.GetConfTemplateId() )
			{
				return false;
			}
		}		
		m_vtDCTemplate.push_back( tDCTemplate );
		return true;
	}

/*====================================================================
    ����        ��  ���б���ɾ������ģ��
    �������˵����  cConfId��������ģ���
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
    bool RemoveConfEntry( const CConfId& cConfId )
	{
#ifdef _WIN32
        CSection lock(&m_Section_ConfEntry);
#else
        PWaitAndSignal lock(m_mutex_ConfEntry);
#endif

		for( itorConf i=m_vtDCTemplate.begin(); i<m_vtDCTemplate.end(); i++ )
		{
			if( (*i).GetConfTemplateId() == cConfId )
			{
				m_vtDCTemplate.erase(i);
				return true;
			}
		}
		return true;
	}

/*====================================================================
    ����        ��  ���б����޸Ļ���ģ��
    �������˵����  tDCTemplate��������ģ��
    ����ֵ˵��  ��  true�����ɹ�
                    false����ʧ��
====================================================================*/
	bool ModifyConfEntry( const TDataConfTemplate& tDCTemplate )
	{
#ifdef _WIN32
        CSection lock(&m_Section_ConfEntry);
#else
        PWaitAndSignal lock(m_mutex_ConfEntry);
#endif

		for( itorConf i=m_vtDCTemplate.begin(); i<m_vtDCTemplate.end(); i++ )
		{
			if( (*i).GetConfTemplateId() == tDCTemplate.GetConfTemplateId() )
			{
				(*i) = tDCTemplate;
				return true;
			}
		}		
		return false;
	}
	
/*====================================================================
    ����        ��  �õ��ն��б�
    �������˵����  ��
    ����ֵ˵��  ��  �ն��б�
====================================================================*/
    std::vector<TDCBaseMt> & GetTDCBaseMtVector()
    {
        return m_vtDCBaseMt;
    }
	
/*====================================================================
    ����        ��  �õ�����ģ���б�
    �������˵����  ��
    ����ֵ˵��  ��  ����ģ���б�
====================================================================*/
    std::vector<TDataConfTemplate> & GetTDCConfTemplate()
    {
        return m_vtDCTemplate;
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifdef WIN32
#pragma pack( pop )
#endif

#endif // _DCSTRC_H
