#ifndef _h_umssipmcudef_h__
#define _h_umssipmcudef_h__

#include "osp.h"
#include "kdvcascade.h"

#define     MAXLEN_CONFID                   16

//消息长度相关
#define      SERV_MSG_LEN					0x7000  //消息长度
#define      SERV_MSGHEAD_LEN				0x30    //消息头长度

#define CASCADE_SPY_STARTPORT			(u16)30000	// 30000～37000 上级接纳回传源端口：10 * 512 = 5120; 空闲 1880 
#define  PORTSPAN                       (u16)10     // 端口的间隔

//会议号结构 (len:16)
struct CMcuConfId
{
protected:
	u8  	m_abyConfId[MAXLEN_CONFID];
	
public:
	u8   GetConfId( u8   * pbyConfId, u8   byBufLen ) const; //获得会议号数组
	void CreateConfId( u8 byUsrGrpId );                               //创建会议号
	void GetConfIdString( LPSTR lpszConfId, u8   byBufLen ) const;//获得会议号字符串
	void SetConfId( const CMcuConfId & CMcuConfId );                  //设置会议号
	u8   SetConfId( const u8   * pbyConfId, u8   byBufLen );          //设置会议号数组
	u8   SetConfId( LPCSTR lpszConfId );                          //设置会议号数组	
	BOOL IsNull( void ) const;                                  //判断会议号是否为空
	void SetNull( void );                                       //设置会议号为空
	BOOL operator == ( const CMcuConfId & CMcuConfId ) const;         //操作符重载
    // 顾振华，在CMcuConfId中内置用户组的信息
    u8   GetUsrGrpId() const 
    {
        return m_abyConfId[MAXLEN_CONFID-1];
    }
    void SetUsrGrpId(u8 byGrpId)
    {
        m_abyConfId[MAXLEN_CONFID-1] = byGrpId;
    }
	
	//fuxiuhua,增加会议发起方信息
	//会议ID的组成：MCU号(2Byte)/会议类型(1Byte)/会议索引值(1Byte)/会议号产生次数(4Byte)/
	//              未用(6Byte)/发起方类型(1Byte)/组号(1Byte)
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


//业务消息类，最大处理28K长度消息
class CServMsg
{
protected:
	u16     m_wSerialNO;            //流水号
	u8      m_bySrcDriId;           //源DRI板号
	u8      m_bySrcMtId;            //源终端号
	u8      m_bySrcSsnId;           //源会话号
	u8      m_byDstDriId;           //目的DRI板号
    u8      m_byDsTMCUMtId;            //目的终端号
	u8      m_byMcuId;              //MCU号
	u8      m_byChnIndex;           //通道索引号
    u8      m_byConfIdx;            //会议索引号
	CMcuConfId m_CMcuConfId;        //会议号
	u16		m_wEventId;             //事件号
	u16		m_wTimer;               //定时
	u16		m_wErrorCode;           //错误码
	u16		m_wMsgBodyLen;          //消息体长度
    u8      m_byTotalPktNum;        //总包数（用于需要切包发送的消息）
    u8      m_byCurPktIdx;          //当前包索引（从0开始）
	u8      m_abyReserverd[12];     //保留字节
	u8      m_abyMsgBody[SERV_MSG_LEN-SERV_MSGHEAD_LEN];    //消息体
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
	void ClearHdr( void );//消息头清零
	CMcuConfId GetConfId( void ) const;//获取会议号信息
	void SetConfId( const CMcuConfId & CMcuConfId );//设置会议号信息
	void SetNullConfId( void );//设置会议号信息为空
	u16  GetMsgBodyLen( void ) const;//获取消息体长度信息
	u16  GetMsgBody( u8   * pbyMsgBodyBuf, u16  wBufLen ) const;//获取消息体，由用户申请BUFFER，如果过小做截断处理
	u8   * const GetMsgBody( void ) const;//获取消息体指针，用户不需提供BUFFER
	void SetMsgBody( u8   * const pbyMsgBody = NULL, u16  wLen = 0 );//设置消息体
	void CatMsgBody( u8   * const pbyMsgBody, u16  wLen );//添加消息体
	u16  GetServMsgLen( void ) const;//获取整个消息长度
	u16  GetServMsg( u8   * pbyMsgBuf, u16  wBufLen ) const;//获取整个消息，由用户申请BUFFER，如果过小做截断处理
	u8   * const GetServMsg( void ) const;//获取整个消息指针，用户不需提供BUFFER
	void SetServMsg( u8   * const pbyMsg, u16  wLen );//设置整个消息
	const CServMsg & operator= ( const CServMsg & cServMsg );//操作符重载
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
/*-------------------------------------------------------------------
                               CServMsg                              
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：CServMsg
    功能        ：constructor
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::CServMsg( void )
{
	Init();
}

/*====================================================================
    函数名      ：CServMsg
    功能        ：constructor
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsg, 要赋值的消息指针
				  u16 wMsgLen, 要赋值的消息长度，必须大于等于 SERV_MSGHEAD_LEN
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
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
    函数名      ：~CServMsg
    功能        ：distructor
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::~CServMsg( void )
{

}

/*====================================================================
    函数名      ：Init
    功能        ：BUFFER初始化
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::Init( void )
{
	memset( this, 0, SERV_MSG_LEN );	//清零
}

/*====================================================================
    函数名      ：ClearHdr
    功能        ：消息头清零
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::ClearHdr( void )
{
	u16		wBodyLen = GetMsgBodyLen();

	memset( this, 0, SERV_MSGHEAD_LEN );	//清零
	SetMsgBodyLen( wBodyLen );
}

/*====================================================================
    函数名      ：GetConfId
    功能        ：获取会议号信息
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：会议号，全0表示创建
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
    02/12/24    1.0         LI Yi         修改接口
====================================================================*/
inline CMcuConfId CServMsg::GetConfId( void ) const
{
	return( m_CMcuConfId );
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号信息
    算法实现    ：
    引用全局变量：
    输入参数说明：const CMcuConfId & CMcuConfId，会议号，全0表示创建
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
    02/12/24    1.0         LI Yi         修改接口
====================================================================*/
inline void CServMsg::SetConfId( const CMcuConfId & CMcuConfId )
{
	m_CMcuConfId = CMcuConfId;
}

/*====================================================================
    函数名      ：SetNullConfId
    功能        ：设置会议号信息为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/06    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetNullConfId( void )
{
	CMcuConfId		CMcuConfId;
	
	CMcuConfId.SetNull();
	SetConfId( CMcuConfId );
}

/*====================================================================
    函数名      ：GetMsgBodyLen
    功能        ：获取消息体长度信息
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：消息体长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetMsgBodyLen( void ) const
{
	return( ntohs( m_wMsgBodyLen ) );
}

/*====================================================================
    函数名      ：SetMsgBodyLen
    功能        ：设置消息体长度信息
    算法实现    ：
    引用全局变量：
    输入参数说明：u16 wMsgBodyLen, 消息体长度
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetMsgBodyLen( u16 wMsgBodyLen )
{
	m_wMsgBodyLen = htons( wMsgBodyLen );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取消息体指针，用户不需提供BUFFER
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：u8 * const指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u8 * const CServMsg::GetMsgBody( void ) const
{
	return( ( u8 * const )m_abyMsgBody );
}

/*====================================================================
    函数名      ：GetMsgBodyLen
    功能        ：获取整个消息长度
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：整个消息长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetServMsgLen( void ) const
{
	return( GetMsgBodyLen() + SERV_MSGHEAD_LEN );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取消息体，由用户申请BUFFER，如果过小做截断处理
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyMsgBodyBuf, 返回的消息体
				  u16 wBufLen, BUFFER大小
    返回值说明  ：实际返回的消息体长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
{
    u16 wActLen = min( GetMsgBodyLen(), wBufLen );
	memcpy( pbyMsgBodyBuf, m_abyMsgBody, wActLen );
	return wActLen;
}

/*====================================================================
    函数名      ：SetMsgBody
    功能        ：设置消息体
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsgBody, 传入的消息体，缺省为NULL
				  u16 wLen, 传入的消息体长度，缺省为0
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
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
    函数名      ：CatMsgBody
    功能        ：添加消息体
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsgBody, 传入的消息体，缺省为NULL
				  u16 wLen, 传入的消息体长度，缺省为0
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/11/07    1.0         Liaoweijiang  创建
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
    函数名      ：GetMsgBody
    功能        ：获取整个消息指针，用户不需提供BUFFER
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：u8 * const指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline u8 * const CServMsg::GetServMsg( void ) const
{
	return( ( u8 * const )( this ) );
}

/*====================================================================
    函数名      ：GetServMsg
    功能        ：获取整个消息，由用户申请BUFFER，如果过小做截断处理
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyMsgBuf, 返回的消息
				  u16 wBufLen, BUFFER大小
    返回值说明  ：实际返回的消息长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
{
	wBufLen = min(SERV_MSG_LEN,wBufLen);
	memcpy( pbyMsgBuf, this, wBufLen );
	return( min( GetMsgBodyLen() + SERV_MSGHEAD_LEN, wBufLen ) );
}

/*====================================================================
    函数名      ：SetServMsg
    功能        ：设置整个消息
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsg, 传入的整个消息
				  u16 wMsgLen, 传入的消息长度
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
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
    函数名      ：operator=
    功能        ：操作符重载
    算法实现    ：
    引用全局变量：
    输入参数说明：CServMsg & cServMsg, 赋值的消息引用
    返回值说明  ：CServMsg对象应用
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
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
    函数名      ：GetConfId
    功能        ：获得会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyConfId, 传入的BUFFER数组指针，用来返回会议号
			      u8 byBufLen, BUFFER大小
    返回值说明  ：实际返回数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CMcuConfId::GetConfId( u8 * pbyConfId, u8 byBufLen ) const
{
	u8	byLen = min( sizeof( m_abyConfId ), byBufLen );
	memcpy( pbyConfId, m_abyConfId, byLen );

	return( byLen );
}

/*====================================================================
    函数名      ：GetConfIdString
    功能        ：获得会议号字符串
    算法实现    ：
    引用全局变量：
    输入参数说明：LPSTR lpszConfId, 传入的字符串BUFFER数组指针，用来
	                   返回0结尾会议号字符串
			      u8 byBufLen, BUFFER大小
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
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
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：const CMcuConfId & CMcuConfId, 输入会议号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline void CMcuConfId::SetConfId( const CMcuConfId & CMcuConfId )
{
	CMcuConfId.GetConfId( m_abyConfId, sizeof( m_abyConfId ) );
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：const u8 * pbyConfId, 传入的数组指针
			      u8 byBufLen, BUFFER大小
    返回值说明  ：实际设置数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CMcuConfId::SetConfId( const u8 * pbyConfId, u8 byBufLen )
{
	u8	bySize = min( byBufLen, sizeof( m_abyConfId ) );
	
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	memcpy( m_abyConfId, pbyConfId, bySize );

	return( bySize );
}
	
/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：LPCSTR lpszConfId, 传入的会议号字符串
    返回值说明  ：实际设置数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
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
    函数名      ：CreateConfId
    功能        ：创建会议号
    算法实现    ：根据当前时间和随机值
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/06    1.0         LI Yi         创建
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

    // 顾振华 [6/21/2006]
    // 最低位表示组ID
    SetUsrGrpId( byUsrGrpId );
}

/*====================================================================
    函数名      ：IsNull
    功能        ：判断会议号是否为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/03/31    1.0         LI Yi         创建
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
    函数名      ：SetNull
    功能        ：设置会议号为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/03/31    1.0         LI Yi         创建
====================================================================*/
inline void CMcuConfId::SetNull( void )
{
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
}

/*====================================================================
    函数名      ：operator==
    功能        ：操作符重载
    算法实现    ：
    引用全局变量：
    输入参数说明：const CMcuConfId & CMcuConfId, 输入会议号
    返回值说明  ：相等返回TRUE，否则返回FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
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

//设备主类定义
#define		MCU_TYPE_MCU                     	 1   //MCU
#define		MCU_TYPE_MCUPERI                     2   //MCU外设
#define		MCU_TYPE_MT                          3   //终端
//conf id len
#define     MCU_MAXLEN_CONFID                   16
#define     MCU_LOCAL_MCUID                     192					//本地MCU ID 
#define		MCU_LOCAL_MCUIDX					19200				//本地MCU IDX
#define		MCU_INVALID_MCUIDX					0xffff				//非法mcuidx号

// 获取会议视频视图
#define     MAXNUM_VIEWINCONF				5    //每个会议的最大视图数
#define     MAXNUM_GEOINVIEW				5    //每个视图的最大几何布局数
#define		MAXNUM_SUBFRAMEINGEO            16   //每个几何布局的最大成员数
#define     MAXNUM_VSCHEMEINVIEW			4    //每个视图里的视频方案数
#define     MAXNUM_MIXERINCONF              16   //每个会议中的最大混音数  
#define     MAXNUM_ADDMT                    10   //一次增加的最大MT数 

#define		INVALID_MCUIDX					0xffff				//非法mcuidx号
#define		LOCAL_MCUIDX					19200				//本地MCU IDX

/*媒体类型定义*/

#define   MCU_MEDIA_TYPE_NULL                 (u8)255  /*媒体类型为空*/

/*音频*/

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

/*视频*/

#define   MCU_MEDIA_TYPE_MP4	              (u8)97  /*MPEG-4*/

#define   MCU_MEDIA_TYPE_H261	              (u8)31  /*H.261*/

#define   MCU_MEDIA_TYPE_H262	              (u8)33  /*H.262 (MPEG-2)*/

#define   MCU_MEDIA_TYPE_H263	              (u8)34  /*H.263*/

#define   MCU_MEDIA_TYPE_H263PLUS             (u8)101 /*H.263+*/

#define   MCU_MEDIA_TYPE_H264	              (u8)106 /*H.264*/

#define   MCU_MEDIA_TYPE_H264_ForHuawei       (u8)105 /*H.264*/

/*数据*/
#define   MCU_MEDIA_TYPE_H224	              (u8)100  /*H.224 Payload 暂定100*/
#define   MCU_MEDIA_TYPE_T120                 (u8)200  /*T.120媒体类型*/
#define   MCU_MEDIA_TYPE_H239                 (u8)239  /*H.239数据类型 */
#define   MCU_MEDIA_TYPE_MMCU                 (u8)120  /*级联数据通道 */

#define     MCU_VIDEO_FPS_USRDEFINED            128 //自定义帧率(>=128,减去128即为实际帧率)
//视频格式定义
#define     MCU_VIDEO_FORMAT_INVALID            255
#define		MCU_VIDEO_FORMAT_SQCIF				1   //SQCIF(128*96)
#define		MCU_VIDEO_FORMAT_QCIF				2   //SCIF(176*144)
#define		MCU_VIDEO_FORMAT_CIF                3   //CIF(352*288)  - P制
#define     MCU_VIDEO_FORMAT_2CIF               4   //2CIF(352*576) - p
#define		MCU_VIDEO_FORMAT_4CIF               5   //4CIF(704*576) - P制(H264下此宏指代D1(720*576)   - P制（N制D1：720*480）)
#define		MCU_VIDEO_FORMAT_16CIF				6   //16CIF(1408*1152)
#define		MCU_VIDEO_FORMAT_AUTO				7   //自适应，仅用于MPEG4

#define		MCU_VIDEO_FORMAT_SIF                8   //SIF(352*240)  - N制
#define     MCU_VIDEO_FORMAT_2SIF               9   //2SIF
#define		MCU_VIDEO_FORMAT_4SIF               10  //4SIF(704*480) - N制

#define     MCU_VIDEO_FORMAT_VGA                11  //VGA(640*480)
#define		MCU_VIDEO_FORMAT_SVGA               12  //SVGA(800*600)
#define		MCU_VIDEO_FORMAT_XGA                13  //XGA(1024*768)
#define     MCU_VIDEO_FORMAT_WXGA               14  //WXGA(1280*768 | 1280*800)

//仅用于终端分辨率改变
#define		MCU_VIDEO_FORMAT_SQCIF_112x96       21  //SQCIF(112*96)
#define		MCU_VIDEO_FORMAT_SQCIF_96x80        22  //SQCIF(96*80)

// 高清分辨率
#define     MCU_VIDEO_FORMAT_W4CIF              31  //Wide 4CIF(1024*576)
#define     MCU_VIDEO_FORMAT_HD720              32  //720 1280*720
#define     MCU_VIDEO_FORMAT_SXGA               33  //SXGA 1280*1024
#define     MCU_VIDEO_FORMAT_UXGA               34  //UXGA 1600*1200
#define     MCU_VIDEO_FORMAT_HD1080             35  //1080  1920*1088(p) 1920*544(i)

//非标分辨率（1080p底图）－用于终端分辨率改变
#define     MCU_VIDEO_FORMAT_1440x816           41  //1440×816(3/4)
#define     MCU_VIDEO_FORMAT_1280x720           42  //1280×720(2/3)
#define     MCU_VIDEO_FORMAT_960x544            43  // 960×544(1/2)
#define     MCU_VIDEO_FORMAT_640x368            44  // 640×368(1/3)
#define     MCU_VIDEO_FORMAT_480x272            45  // 480×272(1/4)
#define     MCU_VIDEO_FORMAT_384x272            46  // 384×272(1/5)

//非标分辨率（720p底图） －用于终端分辨率改变
#define     MCU_VIDEO_FORMAT_720_960x544        51  //960×544(3/4)
#define     MCU_VIDEO_FORMAT_720_864x480        52  //864×480(2/3)
#define     MCU_VIDEO_FORMAT_720_640x368        53  //640×368(1/2)
#define     MCU_VIDEO_FORMAT_720_432x240        54  //432×240(1/3)
#define     MCU_VIDEO_FORMAT_720_320x192        55  //320×192(1/4)

//非标分辨率（1080p底图）－用于终端分辨率改变
#define		MCU_VIDEO_FORMAT_640x544			56	//640x544
#define		MCU_VIDEO_FORMAT_320x272			57	//320x272

//Resolutions that can be acceptable
#define		MCU_MAXNUM_ACCEPTABLE_RES			(u8)57

#define MCU_F_WHNONELARGER			-2	// none larger in both
#define MCU_F_HLARGER				-1	// only larger in height
#define MCU_WHEQUAL					0	// equal
#define MCU_F_WLARGER				1	// only larger in width
#define MCU_F_WHLARGER				2	// larger in both

//传送图像声音参数模式
#define		MCU_MODE_NONE			             0	  //音视频都不传
#define		MCU_MODE_VIDEO						 1	  //只传视频（轮询视频：只给本地广播）
#define		MCU_MODE_AUDIO						 2	  //只传音频
#define		MCU_MODE_BOTH						 3    //音视频都传（轮询发言人：只给本地广播）
#define     MCU_MODE_DATA                        4    //数据 
#define     MCU_MODE_SECVIDEO                    5    //第二路视频


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
        
        //基于尽可能播放考虑，这里取大值
        wWidth = 704;
        wHeight = 576;
        break;
        
    case MCU_VIDEO_FORMAT_16CIF:
        wWidth = 1048;
        wHeight = 1152;
        break;
        
    case MCU_VIDEO_FORMAT_AUTO:
		// 对于auto分辨率解析为cif
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
		//非标分辨率（1080p底图）
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

	//非标分辨率（720p底图）
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
函数名    :  WHCmp
功能      :  某高宽分别同另一高宽比较
算法实现  :  
参数说明  :  
返回值说明:  s32 
             宽高均小返回 F_WHNONELARGER
			 宽小高大返回 F_HLARGER
			 宽高均相等返回 WHEQUAL
			 宽大高小返回 F_WLARGER
			 宽高均大返回 F_WHLARGER
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2009-10-20                  薛亮                            创建
==============================================================================*/
inline s32 WHCmp(u16 wSrcWidth, u16 wSrcHeight, u16 wDstWidth, u16 wDstHeight)
{
	//特殊调整
	//VIDEO_FORMAT_480x272 ——>比较时统一扩充到480 x 288
	wSrcHeight = (wSrcHeight == 272) ? 288 : wSrcHeight;
	wDstHeight = (wDstHeight == 272) ? 288 : wDstHeight;
	
	//前者均不大于后者
	if ( (wSrcWidth == wDstWidth) && (wSrcHeight == wDstHeight) )
	{
		return MCU_WHEQUAL;  //宽高均等  (equal in width and height)
	}
	else if( ( wSrcWidth <= wDstWidth ) && (wSrcHeight <= wDstHeight) )
	{
		return MCU_F_WHNONELARGER; //宽高均小，宽等高小，宽小高等 (none bigger in both width and height)
	}
	//前者至少有一项大于后者
	else if ( (wSrcWidth <= wDstWidth) && (wSrcHeight >= wDstHeight) )
	{
		return MCU_F_HLARGER; //宽小高大，宽等高大  (only bigger in height)
	}
	else if ( (wSrcWidth >= wDstWidth) && (wSrcHeight <= wDstHeight) )
	{
		return MCU_F_WLARGER;  //宽大高小，宽大高等  (only bigger in width)
	}
	else 
	{
		return MCU_F_WHLARGER; //宽高均大			 (bigger both in width and height)
	}
}
/////////////// mcu 多回传 /////////////////////

#define ISHDFORMAT(byRes) \
	(VIDEO_FORMAT_W4CIF == byRes || VIDEO_FORMAT_HD720 == byRes || \
	VIDEO_FORMAT_SXGA == byRes || VIDEO_FORMAT_UXGA == byRes || \
         VIDEO_FORMAT_HD1080 == byRes)

// H264画质属性(HP/BP) [12/8/2011 chendaiwei]
enum emMcuProfileAttrb
{
	emmcuBpAttrb,	//BP
		emmcuHpAttrb,	//HP
};

struct TMCUMt;
//定义简化MCU、终端或外设结构 (len:6)
struct TMCUMtNoConstruct
{
protected:
    u8          m_byMainType;   //设备主类
    u8  		m_bySubType;	//设备子类
	u8  		m_byMcuId;		//MCU号
	u8  		m_byEqpId;	    //设备号	
	u8          m_byConfDriId;  //DRI板号
    u8          m_byConfIdx;    //会议索引号，即会议实例号 1 - MAXNUM_MCU_CONF

public:
	// 设置结构主类
	void   SetType( u8   byType )
	{ 
		m_byMainType = ( (m_byMainType & 0xf0) | (byType & 0xf) ) ; 
	}         

	// 得到结构主类
	u8     GetType( void ) const { return m_byMainType & 0xf; }     
	
	// fxh 与GetMcuId匹配操作，对于原u8同样兼容
	void   SetMcuId( u16  wMcuId )	{ SetMcuIdx(wMcuId); } 
    
	// 得到McuId
	u16     GetMcuId( void ) const { return GetMcuIdx(); }

	// 判断TMtNoConstruct与TMtNoConstruct是否相等
	BOOL   operator ==( const TMCUMtNoConstruct & tObj ) const;    

	//操作MCU函数
	//设置MCU
	void   SetMcu( u16   wMcuIdx );                         
	void   SetMcuType( u8  byMcuType )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MCU); 
		m_bySubType = ((m_byMainType & 0xf0)| (byMcuType&0xf) ); 
	}

	u8     GetMcuType( void ) const { return m_bySubType & 0xf; }

	// 操作外设函数
	// 设置MCU外设
	void   SetMcuEqp( u8   byMcuId, u8   byEqpId, u8   byEqpType );  
	
	// 设置MCU外设类型
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
	
	//操作终端函数
	void   SetMt( u16   wMcuIdx, u8   byMtId, u8   m_byDriId = 0, u8   m_byConfIdx = 0);
	void   SetMt( TMt tMt);
	void   SetMtId( u8   byMtId )
	{ 
		m_byMainType = ((m_byMainType & 0xf0)| TYPE_MT);	
		m_byEqpId = byMtId; 
	}
	u8     GetMtId( void ) const { return m_byEqpId; }//设置终端
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

	// 将LOCAL_MCUIDX改为LOCAL_MCUID
	BOOL   IsLocal() const 
	{
		// [11/9/2010 liuxu] 外设都是本级得，直接返回TRUE
		if (TYPE_MCUPERI == GetType())
		{
			return TRUE;
		}
		
		return (GetMcuIdx() == LOCAL_MCUIDX );		
	}

//[0901]fxh对于mcuidx是由完备mcu标识进行本地化构成本地mcuid，该实现细节进行封装，过渡阶段，以下两个接口禁止对象调用，之后会将其私有化
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

	// [11/4/2011 liuxu] 添加打印信息
	static void PrintTitle()  
	{
	//	StaticLog("|-----------------------------------------------|\n");
	//	StaticLog("| %5s | %5s | %5s | %5s | %5s | %5s |\n", "MainT", "SubT", "McuId", "MtId", "DriId", "Conf");
	//	StaticLog("|-----------------------------------------------|\n");
	}
	
	// [11/4/2011 liuxu] 打印内容
	void PrintContent() const 
	{
	//	StaticLog("| %5d | %5d | %5d | %5d | %5d | %5d |\n", GetType(), GetEqpType(), GetMcuIdx(), GetMtId(), GetDriId(), GetConfIdx());
	}
}
PACKED
;

//定义简化MCU、终端或外设结构 (len:6)
struct TMCUMt : public TMCUMtNoConstruct
{
	// [5/25/2011 liuxu] TMCUMt和TMCUMtNoConstruct采取两套结构,内容基本一致, 维护不方便,
	// 也存在很大的冗余. 于是在这里进行整理. TMCUMtNoConstruct暂时不能被废除,原因(源自zjj):
	// 我们的代码中用到了很多联合体结构,但是联合体中成员不能有构造函数,但TMCUMt存在构造函数
	// 所以我们需要不带构造函数的TMCUMtNoConstruct.
	
public:
	// 构造函数
	TMCUMt()
	{
		memset( this,0,sizeof(TMCUMt) );
		SetMcuIdx( INVALID_MCUIDX );
	}
	
	// 构造函数
	TMCUMt( const TMCUMtNoConstruct& tOther )
	{
		memcpy( this, &tOther, sizeof(TMCUMtNoConstruct) );
	}
}
PACKED
;

//定义视频媒体格式的属性(len:5)
struct TMcuVideoStreamCap
{
public:
    u16		m_wMaxBitRate;  // 最高位标识HP/BP属性，为1标识HP，为0表示BP [12/2/2011 chendaiwei]
    u8		m_byMediaType;   
    u8      m_byResolution;	//分辨率 VIDEO_FORMAT_AUTO, ...
	u8      m_byFrameRate;  //帧率 MPI，对于 H.264 则是 FPS
    
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

    // guzh [12/1/2007] 自定义帧率的保存/获取
    void    SetUserDefFrameRate(u8 byActFrameRate) { m_byFrameRate = MCU_VIDEO_FPS_USRDEFINED+byActFrameRate; }
    BOOL32  IsFrameRateUserDefined() const {return (m_byFrameRate>MCU_VIDEO_FPS_USRDEFINED); }
    u8      GetUserDefFrameRate(void) const { return IsFrameRateUserDefined() ? m_byFrameRate-MCU_VIDEO_FPS_USRDEFINED : m_byFrameRate; }
    
	// m_wMaxBitRate的低15位标识bitRate [12/2/2011 chendaiwei]
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
	函数名      ：SetH264ProfileAttrb
	功能        ：设置H264的HP/BP属性

	算法实现    ：
	引用全局变量：
	输入参数说明：[IN]emMcuProfileAttrb emAttb标识HP/BP属性

	返回值说明  ：
	----------------------------------------------------------------------
	修改记录    ：
	日  期      版本        修改人        修改内容
	2011/11/28  4.0         chendaiwei       创建
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
	函数名      :GetH264ProfileAttrb
	功能        ：获取H264的HP/BP属性

	算法实现    ：
	引用全局变量：
	输入参数说明：

	返回值说明  ：[OUT]emMcuProfileAttrb emAttb标识HP/BP属性
	----------------------------------------------------------------------
	修改记录    ：
	日  期      版本        修改人        修改内容
	2011/11/28  4.0         chendaiwei       创建
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

	//TODO 是否加入HP/BP的比较 [12/2/2011 chendaiwei]
	BOOL32 IsH264CapLower(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// 标清帧率>30, 帧率按实际25比较
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
	
	//判断能力是否相等
	BOOL32 IsH264CapEqual(u8 bySrcRes, u8 bySrcFR) const
	{
		u16 wSrcWidth  = 0;
		u16 wSrcHeight = 0;
		u16 wDstWidth  = 0;
		u16 wDstHeight = 0;
		GetWHByRes(m_byResolution, wDstWidth, wDstHeight);
		GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
		
		// 标清帧率>30, 帧率按实际25比较
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
	// 计算分辨率帧率乘积，比较大小 [2012/09/12 nizhijun]
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

	// 计算分辨率乘积，比较大小 [1/16/2012 chendaiwei]
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

	// 新增打印 [12/12/2011 chendaiwei]
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
        
            //基于尽可能播放考虑，这里取大值
            wWidth = 704;
            wHeight = 576;
            break;
        
        case MCU_VIDEO_FORMAT_16CIF:
            wWidth = 1048;
            wHeight = 1152;
            break;
        
        case MCU_VIDEO_FORMAT_AUTO:
            //不解析
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
			//非标分辨率（1080p底图）
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

			//非标分辨率（720p底图）
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
        //不解析以下
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

// zw [06/27/2008] 将m_byAudioMediaType封装为TMcuAudioStreamCap，并且作为TAudAACCap父类
//定义音频媒体格式的属性(len:1)
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


//同时能力集结构(len:6)
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

    // guzh [12/1/2007] 自定义帧率的保存/获取
    void SetUserDefFrameRate(u8 byActFrameRate) { m_tVideoCap.SetUserDefFrameRate(byActFrameRate); }
    BOOL32 IsFrameRateUserDefined() const {return m_tVideoCap.IsFrameRateUserDefined(); }
    u8   GetUserDefFrameRate(void) const { return m_tVideoCap.GetUserDefFrameRate(); }
    
    void SetAudioMediaType( u8 byAudioMediaType ) { m_tAudioCap.SetMediaType(byAudioMediaType);}
    u8   GetAudioMediaType( void ) const { return m_tAudioCap.GetMediaType(); }

    void SetVideoCap( TMcuVideoStreamCap &tVidCap ){ memcpy(&m_tVideoCap, &tVidCap, sizeof(TMcuVideoStreamCap)); }
    TMcuVideoStreamCap   GetVideoCap( void ) const { return m_tVideoCap; }
	
	BOOL32   operator ==( const TMcuSimCapSet & tSimCapSet ) const  //判断是否相等(只判断语音图像)
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
    
//     BOOL32 operator < (const TSimCapSet &tSimCapSet) //判断小于
//     {
//         if (tSimCapSet.IsNull())
//         {
//             return FALSE;
//         }
//         if (GetVideoMediaType() != tSimCapSet.GetVideoMediaType() /*&& 
// 			GetAudioMediaType() != tSimCapSet.GetAudioMediaType()*/)
//         {
//             //基于适配：不匹配认为小于
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
    
	BOOL32 operator < (const TMcuSimCapSet &tSimCapSet) const //判断小于
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

				//源能力：h264 cif 30fps 目的能力:h264 cif 25fps 不走适配
				if(VIDEO_FORMAT_CIF == GetVideoResolution() && VIDEO_FORMAT_CIF == tSimCapSet.GetVideoResolution() &&
				   GetUserDefFrameRate() == 25 && tSimCapSet.GetUserDefFrameRate() == 30)
				{
					return FALSE;
				}
				
// 				//目前暂时让720 60 可以打给1080 30
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

//定义传输地址结构(len:6)
struct TMcuTransportAddr
{
public:
	u32   		m_dwIpAddr;		//IP地址, 网络序
	u16 		m_wPort;		//端口号, 网络序
public:
	void   SetNull(void)
	{
		m_dwIpAddr = 0;
		m_wPort = 0;
	}
	
	// [6/2/2011 liuxu] 添加判断
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
		//[2011//11/09/zhangli]左值为网络序，右值为主机序，左值改成主机序
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

// [pengjie 2010/9/11] 多回传逻辑整理，下一步将数据成员变为私有的不再暴露给外部，外部直接调接口
struct TSpyResource         // 多回传基本信息 (len: 36)
{
public:
	TMCUMt		      m_tSpy;		     // 回传源(Mt)
	TMcuSimCapSet     m_TMcuSimCapSet;     // 对应回传实体的能力描述 ( 该回传源 所回传到的 回传目的端的 能力 )
	TMcuTransportAddr m_tSpyAddr;       // 对应回传实体的回传通道地址信息
	TMcuTransportAddr m_tVideoRtcpAddr; // [liu lijiu][20100823]记录下级接收RTCP的地址
	TMcuTransportAddr m_tAudioRtcpAddr; // [liu lijiu][20100823]记录下级会议接收RTCP的地址
	u8		       m_bySpyMode;	     // AUDIO,VIDEO,BOTH
	u8             m_byReserved1;    // 预留字段
	u32            m_dwReserved2;    // 预留字段
	
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
	u8          m_byCasLevel; //相对与本级，终端所处级联树中的跳跃的级别数
	u8          m_abyMtIdentify[MAX_CASCADELEVEL]; //对应级别中终端的标识 
	u8 m_byCanReleaseMode;	//可释放模式
private:
	s16 m_swCount;			//如果该mt信息非本级下的mcu信息就小于0 ,否则为0
public:
	u8 m_byIsNeedRelease;	//返回给上级mcu判断该可释放终端最终是否需要释放
	u8 m_byCanReleaseVideoDstNum;//可以释放的视频目的数
	u8 m_byCanReleaseAudioDstNum;//可以释放的音频目的数
	u8 m_byIsReuseBasChl;//是否重用可释放终端所占用的bas通道
	//==MODE_VIDEO视频bas可复用，==MODE_AUDIO音频bas可复用，MODE_BOTH音视频bas都可复用
	
public:
	TMcuPreReleaseMtInfo()
	{
		memset( this, 0, sizeof(TMcuPreReleaseMtInfo) );
	}
	
	//传入主机序[3/7/2012 chendaiwei]
	void SetCount( s16 swCount )
	{
		m_swCount = htons(swCount);
	}
	
	//传出主机序
	s16 GetCount( void ) const
	{
		return ntohs(m_swCount);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpySwitchInfo     // 选看相关的多回传初始信息
{
	//u8    m_byMcInstId;   // 某个会控的id
	u8    m_byDstChlIdx;  // 目的通道索引
	u8    m_bySrcChlIdx;  // 源通道索引号
	TMCUMtNoConstruct   m_tDstMt;       // 目的终端（若为会控监控，目的端为空）
	
private:
	u32   m_dwMcIp;       //会控IP
	u32   m_dwMcSSRC;    //会控随机数
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

struct TSpyHduInfo     // 进高清电视墙相关的多回传初始信息
{
	u8    m_bySrcMtType;  // 电视墙源通道成员类型
	u8    m_bySchemeIdx;  // 预案索引号
	u8    m_byDstChlIdx;  // HDU目的通道索引
	TEqpNoConstruct  m_tHdu;         // 外设信息
private:
	u8    m_bySubChnIdx;	//HDU多画面子通道
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

struct TSpyPollInfo     // 轮询相关的多回传初始信息
{
	u16   m_wKeepTime;        //终端轮询的保留时间 单位:秒(s)
	u8    m_byPollingPos;        //终端轮询的次数
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyTVWallInfo     // 进电视墙相关的多回传初始信息
{
	u8    m_bySrcMtType;  // 电视墙源通道成员类型
	u8    m_bySchemeIdx;  // 预案索引号
	u8    m_byDstChlIdx;  // TVWall目的通道索引
	TEqpNoConstruct  m_tTvWall;      // 外设信息
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyVmpInfo //画面合成相关的多回传信息
{
	//	u8		m_byRes;	//分辨率上限
	u8		m_byPos;	//通道位置
	//	u8		m_byKeepOrgRes;	//表明即使下级调不了分辨率(比如非keda的)，上级还是可以让其以全分辨率进
    u8		m_byMemberType;     //画面合成成员类型,参见vccommon.h中画面合成成员类型定义
    u8		m_byMemStatus;      //成员状态(MT_STATUS_CHAIRMAN, MT_STATUS_SPEAKER, MT_STATUS_AUDIENCE)
	TEqpNoConstruct    m_tVmp;             // 画面合成外设
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyRollCallInfo     // 多回传点名相关信息
{
	TMCUMtNoConstruct m_tCaller;        // 点名人
	TMCUMtNoConstruct m_tOldCaller;     // 老的点名人
	TMCUMtNoConstruct m_tOldCallee;     // 老的被点名人 
	//u8			   m_byMcInstId;   // 某个会控的id
private:
	u32   m_dwMcIp;       //会控IP
	u32   m_dwMcSSRC;     //会控随机数
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
    u8   m_byRecMode;         //录像模式
    u8   m_byPublishMode;     //发布模式
    u8   m_byPublishLevel;    //发布层次
    u8   m_byIsRecLowStream;  //是否录低速码流
    u8   m_byIsRecMainVideo;  //是否录主格式视频码流
    u8   m_byIsRecMainAudio;  //是否录主格式音频码流
    u8   m_byIsRecDStream;    //是否录双流
	u16  m_wRecBitrate;       //录像码率
    u16  m_wRecBitrateSec;    //录像双流码率
}
/*
#ifndef WIN32
__attribute__((packed))
#endif
*/
PACKED
;

#define MCU_KDV_MAX_PATH            (u16)256

struct TMcuSpyRecInfo     //录像机路径
{
	TMcuRecStartPara m_tRecPara;
	u8   m_byRecMode;                 // 0会议录像，1终端录像
	TEqpNoConstruct m_tRec;                      // 录像机外设           
	s8   m_szRecFullName[MCU_KDV_MAX_PATH];   // 录像机存放路径
	u16  m_wSerialNO;				  // 回给mcs的流水号
	//u8   m_byMcInstId;				  // 某个会控的id
private:
	u32   m_dwMcIp;       //会控IP
	u32   m_dwMcSSRC;     //会控随机数
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
	//u8				m_byMcInstId;   // 某个会控的id
	u8				m_bySrcChnnl;		//源通道号（对于终端目前只填0，对于外设有多种选择）
	TMcuTransportAddr	m_tDstVidAddr;		//目的视频的ip和port
	TMcuTransportAddr  m_tDstAudAddr;		//目的音频的ip和port （目前Vid和Aud的Ip是相同的，仅port不同）
private:
	u32   m_dwMcIp;       //会控IP
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
	TSpySwitchInfo   m_tSpySwitchInfo;   // 选看的相关信息
	TSpyHduInfo      m_tSpyHduInfo;      // 进高清电视墙的相关信息
	TSpyPollInfo     m_tSpyPollInfo;     // 轮询相关信息
	TSpyTVWallInfo   m_tSpyTVWallInfo;   // 进电视墙的相关信息
	TSpyVmpInfo	     m_tSpyVmpInfo;		 // VMP相关额外信息
	TSpyRollCallInfo m_tSpyRollCallInfo; // 点名相关信息
	TMcuSpyRecInfo		 m_TMcuSpyRecInfo;		 //录像机
	TSpySwitchDstInfo	m_tSpySwitchDstInfo;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// [pengjie 2010/9/11] 多回传逻辑调整
struct TPreSetInReq            // 回传初始信息
{
	//protected: 下一步不再暴露成员信息
private:
	u32 m_dwEvId;             // 记录在进行回传交互前，本来应该执行的消息（如改变发言人，终端选看等）
public:
	u8  m_bySpyMode;          // 最初的回传模式
    TSpyResource m_tSpyMtInfo;    // 请求回传的终端信息
	USpyInfo    m_tSpyInfo;   // 与回传各业务相关的一些必要的信息
	TMcuPreReleaseMtInfo m_tReleaseMtInfo;
	
public:
	TPreSetInReq()
	{
		memset( this, 0, sizeof(TPreSetInReq) );
	}
	
	//设置传入主机序[3/7/2012 chendaiwei]
	void SetEvId( u32 dwEvId)
	{
		m_dwEvId = htonl(dwEvId);
	}
	
	//获取返回主机序
	u32 GetEvId( void ) const
	{
		return ntohl(m_dwEvId);
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPreSetInRsp			// PreSetIn 应答信息
{
	// [pengjie 2010/7/30] TPreSetInReq 结构整理, 主要调整回传目的端信息
	TPreSetInReq m_tSetInReqInfo; // 记录上级要求的回传相关信息
	u8  m_byRspSpyMode;		// 下级真正能达到的回传模式(BOTH/V/A )
	
private:
	u32	m_dwVidSpyBW;		// 回传视频将占用多少带宽
	u32	m_dwAudSpyBW;		// 回传音频将占用多少带宽
	// 	TTransportAddr m_tAudBackRtcp;//[liu lijiu][20100901]记录本级会议为下级会议分配的音频RTCP端口
	// 	TTransportAddr m_tVidBackRtcp;//[liu lijiu][20100901]记录本级会议为下级会议分配的视频RTCP端口
	
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
	
	//传入主机序参数 [3/7/2012 chendaiwei]
	void SetVidSpyBW( u32 dwSpyBW )
	{
		m_dwVidSpyBW = htonl(dwSpyBW);
	}
	
	//传入主机序参数
	void SetAudSpyBW( u32 dwSpyBw )
	{
		m_dwAudSpyBW = htonl(dwSpyBw);
	}
	
	//返回主机序  [3/7/2012 chendaiwei]
	u32 GetVidSpyBW ( void )
	{
		return ntohl(m_dwVidSpyBW);
	}
	
	//返回主机序
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
函数名      : GetNormalRes
功能        : 根据宽高,获得一个通用的分辨率,调分辨率用
算法实现    ：
引用全局变量：
输入参数说明：u16 wResW 宽,u16 wResH 高
返回值说明  ：v4r7前mcu支持的分辨率
----------------------------------------------------------------------
修改记录    ：
日  期      版本        修改人        修改内容
09/13/2012              yanghuaizhi     创建
====================================================================*/
u8 GetNormalRes(u16 wResW, u16 wResH)
{
	// 支持调分辨率的通用分辨率列表,旧mcu支持
	u8 abyAcceptableRes[MCU_MAXNUM_ACCEPTABLE_RES] = 
	{
		MCU_VIDEO_FORMAT_HD1080,
			MCU_VIDEO_FORMAT_1440x816,
			MCU_VIDEO_FORMAT_HD720,
			MCU_VIDEO_FORMAT_960x544,
			MCU_VIDEO_FORMAT_720_864x480,	//TS Vmp 会需要该分辨率
			MCU_VIDEO_FORMAT_4CIF,
			MCU_VIDEO_FORMAT_4SIF,
			MCU_VIDEO_FORMAT_640x368,
			MCU_VIDEO_FORMAT_480x272,
			MCU_VIDEO_FORMAT_CIF,
			MCU_VIDEO_FORMAT_720_432x240,	// need by 8000G vmp 
			MCU_VIDEO_FORMAT_720_320x192,	// need by 8000G vmp
			MCU_VIDEO_FORMAT_QCIF,			//old vmp 可能会需要QCIF
			MCU_VIDEO_FORMAT_2CIF
	}; 
	
	u8 byExistRes = MCU_VIDEO_FORMAT_INVALID;	//已存在分辨率
	u8 bySuitableRes = MCU_VIDEO_FORMAT_INVALID;	//最接近的分辨率,宽高乘积小于等于此分辨率的能力
	u16 wWidth = 0;
	u16 wHeight = 0;
	for(u8 byLoop = 0; byLoop < MCU_MAXNUM_ACCEPTABLE_RES; byLoop ++)
	{
		if( abyAcceptableRes[byLoop] == 0 )
		{
			break;
		}
		GetWHByRes( abyAcceptableRes[byLoop], wWidth, wHeight);
		// 在列表中有定义,直接使用
		if (MCU_WHEQUAL == WHCmp (wWidth, wHeight, wResW, wResH))
		{
			byExistRes = abyAcceptableRes[byLoop];
			break;
		}
		// 宽高成绩小于此分辨率,存入最接近的那个能力
		if (wWidth * wHeight < wResW * wResH)
		{
			if (MCU_VIDEO_FORMAT_INVALID == bySuitableRes)
			{
				bySuitableRes = abyAcceptableRes[byLoop];
			}
		}
	}
	
	// 有存在的分辨率,返回存在的,若无,返回合适的
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

//二级级联：跨级发言状态通知。消息体：TMCUMt ＋ u8 byMode ( emAgreed )
OSPEVENT( MCU_MCU_SPEAKSTATUS_NTF,			EV_MCUMCU_STD_BGN + 68 ); // 25470

/************************************************************************/
/* 自定义 级联多回传消息                                                */
/************************************************************************/
//mcu是否支持多回传能力互探消息,u32 回传带宽
OSPEVENT(MCU_MCU_MULTSPYCAP_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 1 );

//上级mcu告诉下级mcu将要进行级联多回传（setin 前的准备），
//下级mcu将据此判断自己是否还能回传（根据上下级总带宽及终端回传码率）
//消息应包括需要回传的终端，回传的mode(AUDIO，VIDEO，BOTH)，回传的媒体格式、码率、帧率
OSPEVENT(MCU_MCU_PRESETIN_REQ,	    	     EV_MCUMCU_KDV_BGN + 2 ); 
//上级将根据SMCU给的ACK/NACK, 判断其能否有足够带宽来收容一个spy,消息体
//包括下级mcu建立这个回传通道需要的带宽，下级终端是否支持调分辨率的标志
OSPEVENT(MCU_MCU_PRESETIN_ACK,	    	     EV_MCUMCU_KDV_BGN + 3 );
OSPEVENT(MCU_MCU_PRESETIN_NACK,	    	     EV_MCUMCU_KDV_BGN + 4 );

//通知下级mcu，上级可以接受其回传码流的带宽
OSPEVENT(MCU_MCU_SPYCHNNL_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 5 );

//通知下级mcu，上级mcu带宽不足，不能进行级联多回传
OSPEVENT(MCU_MCU_REJECTSPY_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 6 );

//上级mcu发给下级的释放一路音、视频回传通道的CMD，回收回传通道
OSPEVENT(MCU_MCU_BANISHSPY_CMD,	    	     EV_MCUMCU_KDV_BGN + 7 );

// 下级mcu发给上级的释放一路音、视频回传通道的通知，上级收到后释放自己相应的音、视频回传通道资源
//lukunpeng 2010/06/10 由于现在是由上级管理下级带宽占用情况，故不需要再通过下级通知上级
//OSPEVENT(MCU_MCU_BANISHSPY_NOTIF,	    	 EV_MCUMCU_KDV_BGN + 8 );

// 级联多回传关键帧请求消息，消息体为：u8 byMode + TMCUMt  (音视频模式 + 音视频源)
OSPEVENT(MCU_MCU_SPYFASTUPDATEPIC_CMD,	     EV_MCUMCU_KDV_BGN + 9 );

//通知对方MCU自己某一所在直连终端状态,消息体TMcu
OSPEVENT(MCU_MCU_MTSTATUS_NOTIF,			EV_MCUMCU_STD_BGN + 95 );



//////////////////////////////////////////////////////////////////////////
//错误号
const u16     ERR_MCU_BGN = 20001;
#define DefineError(err, num )   \
const u16 err = num;

//会议不支持多回传
DefineError( ERR_MCU_CONFNOTSUPPORTMULTISPY				 , ERR_MCU_BGN + 1738)
//会议回传带宽已满
DefineError( ERR_MCU_CONFSNDBANDWIDTHISFULL				 , ERR_MCU_BGN + 1739)
//级联适配器不足
DefineError( ERR_MCU_CASDBASISNOTENOUGH					 , ERR_MCU_BGN + 1740)










#endif // _h_umssipmcudef_h__