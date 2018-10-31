

#include "tpmsg.h"
#include "tplog.h"
#include "msgmgr.h"
#include "hashtable.h"
#include "xmlengine.h"

using namespace UmsTpmsg;

namespace UmsTpmsg {

TXEVENTINFO* GetTppEventInfo( u16 wEventId );
extern CMapStrToInt g_cTppMapEvtNameToEvtID;


static EMHashType s_emLocalHashType  = emSDBMHash;
static EMHashType s_emRemoteHashType = emHashNone;
s32 g_nXMLIndex = XML_INVALID_INDEX;
s32 g_nMtXmlIndex = -1;

u8 kdvGetLocalHashType()
{
	return s_emLocalHashType;
}

u8 kdvGetRemoteHashType()
{
	return s_emRemoteHashType;
}

void kdvSetLocalHashType( u8 byType )
{
	s_emLocalHashType = (EMHashType)byType;
}

void kdvSetRemoteHashType( u8 byType )
{
	s_emRemoteHashType = (EMHashType)byType;
}


BOOL CTpMsg::Decode(u16 wEvent ,u8* buf ,int len)
{
	m_wEvent = wEvent;
	if( len < CODEC_BODY )
		return FALSE;

	u8 abyEncType = *(u8*)buf;

	switch ( abyEncType )
	{
		case CODEC_NONE:
		{
			memcpy( m_abyMsg ,buf ,len );
			m_wBodyLen = (u16)(len - CODEC_BODY);
			break;
		}
		case CODEC_XML_MARSHAL:
		case CODEC_XML_COMPRESS:
		{			
			int wEvt = 0;
			if ( kdvGetRemoteHashType() == kdvGetLocalHashType() )
			{
				int dwHash = 0;
				if ( XML_GetEventHash( (s8*)buf+CODEC_BODY, 
										len-CODEC_BODY, 
										em_XMLNone, 
										dwHash, 
										(CODEC_XML_COMPRESS == abyEncType) ? 1:0 ) )
				{
					if ( 0 != dwHash )
					{
						wEvt = g_cTppMapEvtNameToEvtID.GetValueAt( (void*)dwHash );
					}
				}
			}
			else
			{
				s8 achEventName[64] = {0};
				if ( XML_GetEventName( (s8*)buf+CODEC_BODY, 
										len-CODEC_BODY, 
										em_XMLNone, 
										achEventName, 
										(CODEC_XML_COMPRESS == abyEncType) ? 1:0 ) )
				{
					g_cTppMapEvtNameToEvtID.Lookup( achEventName, wEvt );
				}
			}
			
			if ( 0 != wEvt && wEvt != m_wEvent )
			{
				m_wEvent = wEvt;
			}

			memcpy( m_abyMsg, buf, CODEC_BODY );
			m_abyMsg[CODEC_FLAG] = CODEC_NONE;
			TXEVENTINFO* ptEventInfo = NULL;
			u32 dwXmlBodyLen = 0;
			ptEventInfo = GetTppEventInfo( m_wEvent );
			if ( NULL == ptEventInfo )
			{
				msgprint( "CKdvMsg::Post, get NULL for event %d!\n", m_wEvent );
				return -1;
			}
			
			if ( !XML_Decode( ptEventInfo->tDataNode, 
							  (s8*)(buf+CODEC_BODY), 
							  len-CODEC_BODY,
							  em_XMLNone,
							  m_abyMsg+CODEC_BODY, 
							  dwXmlBodyLen,
							  (CODEC_XML_COMPRESS == abyEncType) ? 1:0,
							  m_wEvent,
							  ptEventInfo->name,
							  g_nXMLIndex ) )
			{
				msgprint("CKdvMsg::Post, %s(%d), XML_Decode return FALSE!\n", 
					GetEventNamebyID(m_wEvent), m_wEvent );
				m_wBodyLen = (u16)dwXmlBodyLen;
				return FALSE;
			}
			
			m_wBodyLen = (u16)dwXmlBodyLen;
			break;
		}		
		default :
			return FALSE;
	}

	return TRUE;
}



int CTpMsg::Post(u32 dstid,
				 u32 dstnode/*=0*/,	
				 u32 srciid /*=MAKEIID(INVALID_APP, INVALID_INS)*/, 
			     u32 srcnode /*=INVALID_NODE*/)
{	
	if( 0 == m_wEvent )
	{
		msgprint("[CKdvMsg] post event= 0 failed!\n");
        return -10;
	}

	if ( dstnode )
	{
		u32 dwBuflen   = 0;
		u32 dwOverFlow = 0;
		u8  buf[sizeof(m_abyMsg)]={0};
		memcpy( buf, m_abyMsg, CODEC_BODY );
		TXEVENTINFO* ptEventInfo = NULL;
		ptEventInfo = GetTppEventInfo( m_wEvent );
		if ( NULL == ptEventInfo || NULL == ptEventInfo->tDataNode )
		{
			msgprint( "CKdvMsg::Post, get NULL for event %s(%d)!\n", GetEventNamebyID(m_wEvent), m_wEvent );
			return -1;
		}
		u32 dwEventHash = 0;
		if ( !g_cTppMapEvtNameToEvtID.Hash( GetEventNamebyID(m_wEvent), dwEventHash, (EMHashType)kdvGetLocalHashType() ))
		{
			msgprint( "Hash %s(%d) Error!\n", GetEventNamebyID(m_wEvent), m_wEvent );
		}

		if ( !XML_Encode( ptEventInfo->tDataNode, 
						  m_abyMsg+CODEC_BODY, 
						  m_wBodyLen,
						  em_XMLNone,
						  (s8*)(buf+(u16)CODEC_BODY), 
						  dwBuflen, 
						  dwOverFlow,
						  ptEventInfo->eventid,
						  ptEventInfo->name,
						  dwEventHash,
						  g_nXMLIndex ) )
		{
			msgprint( "CKdvMsg::Post, Post, %s(%d), XML_Encode return FALSE!\n",
				GetEventNamebyID(m_wEvent), m_wEvent );
			return -1;
		}

		switch ( dwOverFlow )
		{
			case 2:
			{
				buf[CODEC_FLAG] = CODEC_NONE;
				break;
			}					
			case 1:
			{
				buf[CODEC_FLAG] = CODEC_XML_COMPRESS;
				break;
			}
			case 0:
			{	
				buf[CODEC_FLAG] = CODEC_XML_MARSHAL;
				break;
			}
			default:
				buf[CODEC_FLAG] = CODEC_XML_MARSHAL;
				break;
		}
		
		if ( 0 <= dwBuflen )
		{
			s32 ret = ::OspPost( dstid, m_wEvent, buf, (int)dwBuflen+CODEC_BODY, dstnode, srciid, srcnode);
			if (ret)
			{
				msgprint("CTpMsg::Post. XML OspPost Fail! ret:%d, wEvent:%d, wBufLen:%d, dstnode:%d, dstid:%d\n", 
					ret, m_wEvent, dwBuflen, dstnode, dstid);
			}
			return ret;
		}

	}
	else
	{	
		m_abyMsg[CODEC_FLAG] = CODEC_NONE;
		s32 ret = ::OspPost( dstid ,m_wEvent ,GetMsg() ,GetMsgLen() ,dstnode ,srciid ,srcnode);
		if (ret)
		{
			msgprint("CTpMsg::Post. OspPost Fail! ret:%d, wEvent:%d, wBufLen:%d, dstnode:%d, dstid:%d\n", 
				ret, m_wEvent, GetMsgLen(), dstnode, dstid);
		}
		return ret;
	}
	
	return 0;
}

} //namespace UmsTpmsg


//END OF FILE

