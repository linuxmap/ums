#include "msgmgr.h"
#include "hashtable.h"
#include "osp.h"
#include "tplog.h"
#include "tplogmgr.h"


namespace UmsTpmsg {

extern u32 g_dwKdvShowMsg;
extern s32 g_nXMLIndex;
//MsgMgr : 消息管理
class CTpMsgMgr
{
protected:
	u32 m_dwOutEventNum;
	u32 m_dwInnerEventNum;

	TTpMsgInfo m_tMsg;
public:
	CTpMsgMgr()
	{
		m_dwOutEventNum = 0;
		m_dwInnerEventNum = 0;
	}

	BOOL32 Init(TTpMsgInfo& tMsg)
	{
		if (tMsg.m_dwOutMinEventValue > tMsg.m_dwOutMaxEventValue)
		{
			return FALSE;
		}
		if (tMsg.m_dwInnerMinEventValue > tMsg.m_dwInnerMaxEventValue)
		{
			return FALSE;
		}

		memcpy(&m_tMsg, &tMsg, sizeof(tMsg));
		m_dwOutEventNum = tMsg.m_dwOutMaxEventValue - tMsg.m_dwOutMinEventValue;
		m_dwInnerEventNum = tMsg.m_dwInnerMaxEventValue - tMsg.m_dwInnerMinEventValue;
		return TRUE;
	}

	u32 GetOutMinValue()	{ return m_tMsg.m_dwOutMinEventValue; }
	u32 GetOutMaxValue()	{ return m_tMsg.m_dwOutMaxEventValue; }
	u32 GetOutEventNum()	{ return m_dwOutEventNum; }

	u32 GetInnerMinValue()	{ return m_tMsg.m_dwInnerMinEventValue; }
	u32 GetInnerMaxValue()	{ return m_tMsg.m_dwInnerMaxEventValue; }
	u32 GetInnerEventNum()	{ return m_dwInnerEventNum; }

	

	TXDATAINFO** GetEnumDataInfo()		{ return m_tMsg.m_ptMsgEnumDataInfo; }
	TXDATAINFO** GetStructDataInfo()	{ return m_tMsg.m_ptMsgStructDataInfo; }
};

CTpMsgMgr g_cKdvMsgMgr;


TXEVENTINFO*  g_tTppEventInfo = NULL;
TXEVENTINFO*  g_tTppInnerEventInfo = NULL;
CMapStrToInt g_cTppMapEvtNameToEvtID;



#define ATOMTYPE( type )\
const TXDATAINFO type##membertable[] = {#type,emx_##type,#type,sizeof(type),1,0,0,(char*)#type};
#define BLOBTYPE( type )\
const TXDATAINFO type##_blobmembertable[] = {#type,emx_##type##_blob,#type,sizeof(type),1,0,0,(char*)#type};

ATOMTYPE(s32);
ATOMTYPE(BOOL32);
ATOMTYPE(BOOL);
ATOMTYPE(u8);
ATOMTYPE(s8);
ATOMTYPE(u16);
ATOMTYPE(u32);
ATOMTYPE(time_t);
ATOMTYPE(u32_ip);
BLOBTYPE(u8);

TXDATAINFO* g_tMsgAtomDataInfo[]={
	(TXDATAINFO*)s32membertable,
	(TXDATAINFO*)BOOL32membertable,
	(TXDATAINFO*)BOOLmembertable,
	(TXDATAINFO*)u8membertable,
	(TXDATAINFO*)s8membertable,
	(TXDATAINFO*)u16membertable,
	(TXDATAINFO*)u32membertable,
	(TXDATAINFO*)time_tmembertable,
	(TXDATAINFO*)u32_ipmembertable,
	(TXDATAINFO*)u8_blobmembertable,
};


BOOL32 InitEventMgr(TTpMsgInfo& tInfo)
{
	if (!g_cKdvMsgMgr.Init(tInfo))
	{
		return FALSE;
	}

	g_tTppEventInfo = new TXEVENTINFO[g_cKdvMsgMgr.GetOutEventNum()];
	memset(g_tTppEventInfo, 0, sizeof(TXEVENTINFO)*g_cKdvMsgMgr.GetOutEventNum());

	g_cTppMapEvtNameToEvtID.SetBlockSize(g_cKdvMsgMgr.GetOutEventNum()*3/2);

	g_tTppInnerEventInfo = new TXEVENTINFO[g_cKdvMsgMgr.GetInnerEventNum()];
	memset(g_tTppInnerEventInfo, 0, sizeof(TXEVENTINFO)*g_cKdvMsgMgr.GetInnerEventNum());

#define _InitAtomType( type ) InitAtomType_##type( emx_##type )
#define _InitBlobType( type ) InitAtomType_##type##_blob( emx_##type##_blob )
	
	_InitAtomType( s32    ); 
	_InitAtomType( BOOL32 ); 
	_InitAtomType( BOOL   ); 
	_InitAtomType( u8     ); 
	_InitAtomType( s8     ); 
	_InitAtomType( u16    ); 
	_InitAtomType( u32    ); 
	_InitAtomType( u32_ip ); 
	_InitBlobType( u8     ); 
	_InitAtomType( time_t ); 

	g_nXMLIndex = InitXMLEngine( g_tMsgAtomDataInfo, g_cKdvMsgMgr.GetEnumDataInfo(), g_cKdvMsgMgr.GetStructDataInfo(), 
		emxAtomTypeBegin, emxEnumTypeBegin, emxStructTypeBegin, emxDataTypeEnd); 
	if ( g_nXMLIndex == XML_INVALID_INDEX )
	{
		return FALSE;
	}
	return TRUE;

}

void ExitEventMgr()
{
	if (g_tTppEventInfo)
	{
		delete[] g_tTppEventInfo;
		g_tTppEventInfo = NULL;
	}
	if (g_tTppInnerEventInfo)
	{
		delete[] g_tTppInnerEventInfo;
		g_tTppInnerEventInfo = NULL;
	}
}




static BOOL32 CheckEventIdRange( u16 wEvent )
{
	return g_cKdvMsgMgr.GetOutMinValue() <= wEvent && wEvent < g_cKdvMsgMgr.GetOutMaxValue();
}


TXEVENTINFO* GetTppEventInfo( u16 wEventId )
{
	if ( !CheckEventIdRange(wEventId) )
	{
		printf( "Input event %d is out of range!\n", wEventId );
		return NULL;
	}
	
	return &g_tTppEventInfo[wEventId - g_cKdvMsgMgr.GetOutMinValue()];
}

API void showtppevent( u16 wEvent )
{
	if ( 0 == wEvent )
	{
		u16 wIndex = 0;
		msgprint("outer msg num:%d\n", g_cKdvMsgMgr.GetOutEventNum());
		for( wIndex = 0; wIndex < g_cKdvMsgMgr.GetOutEventNum(); wIndex++ )
		{
			if ( 0 == g_tTppEventInfo[wIndex].eventid || NULL == g_tTppEventInfo[wIndex].name )
			{
				continue;
			}
			
			TXDATANODE* tTmp = g_tTppEventInfo[wIndex].tDataNode; 
			u32 dwLen = 0;	
			while ( 0 != g_tTppEventInfo[wIndex].eventid && NULL != tTmp && emxDataTypeEnd != tTmp[0].type )
			{
				dwLen += tTmp[0].pretypesize * tTmp[0].arraynum;
				tTmp++;
			}
			OspDelay(20);
			msgprintnotime( "event:%d, name:%s, len:%d\n", g_tTppEventInfo[wIndex].eventid, g_tTppEventInfo[wIndex].name, dwLen );
		}

		msgprint("inner msg num:%d\n", g_cKdvMsgMgr.GetInnerEventNum());
		for( wIndex = 0; wIndex < g_cKdvMsgMgr.GetInnerEventNum(); wIndex++ )
		{
			if ( 0 == g_tTppInnerEventInfo[wIndex].eventid || NULL == g_tTppInnerEventInfo[wIndex].name )
			{
				continue;
			}
			
			TXDATANODE* tTmp = g_tTppInnerEventInfo[wIndex].tDataNode; 
			u32 dwLen = 0;	
			while ( 0 != g_tTppInnerEventInfo[wIndex].eventid && NULL != tTmp && emxDataTypeEnd != tTmp[0].type )
			{
				dwLen += tTmp[0].pretypesize * tTmp[0].arraynum;
				tTmp++;
			}
			OspDelay(20);
			msgprintnotime( "event:%d, name:%s, len:%d\n", g_tTppInnerEventInfo[wIndex].eventid, g_tTppInnerEventInfo[wIndex].name, dwLen );
		}
	}
	else
	{
		if ( g_cKdvMsgMgr.GetOutMinValue() > wEvent || wEvent > g_cKdvMsgMgr.GetOutMaxValue() )
		{
			msgprint( "Input event: %d is out of range!\n", wEvent );
			return;
		}
		
		msgprint( "event:%d %s\n", g_tTppEventInfo[wEvent - g_cKdvMsgMgr.GetOutMinValue()].eventid
			, g_tTppEventInfo[wEvent - g_cKdvMsgMgr.GetOutMinValue()].name);
		TXDATANODE* tTmp = g_tTppEventInfo[wEvent - g_cKdvMsgMgr.GetOutMinValue()].tDataNode;
		u32 dwLen = 0;
		
		while ( 0 != g_tTppEventInfo[wEvent - g_cKdvMsgMgr.GetOutMinValue()].eventid && NULL != tTmp && emxDataTypeEnd != tTmp->type )
		{
			msgprintnotime( "type: %d, typesize:%d, pretype:%s, arraynum:%d\n", 
				tTmp->type, tTmp->pretypesize, tTmp->pretype, tTmp->arraynum );
			dwLen += tTmp[0].pretypesize * tTmp[0].arraynum;
			tTmp++;
		}	
		msgprintnotime( "%s len :%d\n", g_tTppEventInfo[wEvent - g_cKdvMsgMgr.GetOutMinValue()].name, dwLen );
	}
}

static void ShowMsgContentInfo(u32 dwType)
{
	if ( emxStructTypeBegin < dwType && dwType < emxDataTypeEnd)
	{
		TXDATAINFO* p =  g_cKdvMsgMgr.GetStructDataInfo()[dwType - emxStructTypeBegin-1];
	}

	else if ( emxAtomTypeBegin < dwType && dwType < emxEnumTypeBegin )
	{
		
	}
	else if ( emxEnumTypeBegin < dwType && dwType < emxStructTypeBegin )
	{

	}
	else
	{
	}
}

API void ShowEventInfo(u16 wEventID, s8* pTitle)
{
	if (pTitle == NULL)
	{
		pTitle = "";
	}


	if ( g_cKdvMsgMgr.GetOutMinValue() <= wEventID && wEventID <= g_cKdvMsgMgr.GetOutMaxValue() )
	{
		msgprint( "[%s] event:%d %s\n", pTitle, g_tTppEventInfo[wEventID - g_cKdvMsgMgr.GetOutMinValue()].eventid
			, g_tTppEventInfo[wEventID - g_cKdvMsgMgr.GetOutMinValue()].name);
		TXDATANODE* tTmp = g_tTppEventInfo[wEventID - g_cKdvMsgMgr.GetOutMinValue()].tDataNode;
		u32 dwLen = 0;
		
		if (g_dwKdvShowMsg > 1)
		{
			while ( 0 != g_tTppEventInfo[wEventID - g_cKdvMsgMgr.GetOutMinValue()].eventid && NULL != tTmp && emxDataTypeEnd != tTmp->type )
			{
				msgprint( "type: %d, typesize:%d, pretype:%s, num:%d\n", 
					tTmp->type, tTmp->pretypesize, tTmp->pretype, tTmp->arraynum );
				
				ShowMsgContentInfo(tTmp->type);
				
				dwLen += tTmp[0].pretypesize * tTmp[0].arraynum;
				tTmp++;
			}
		}
		
	}
	
	else if ( g_cKdvMsgMgr.GetInnerMinValue() <= wEventID && wEventID <= g_cKdvMsgMgr.GetInnerMaxValue() )
	{
		msgprint( "[%s] event:%d %s\n", pTitle, g_tTppInnerEventInfo[wEventID - g_cKdvMsgMgr.GetInnerMinValue()].eventid
			, g_tTppInnerEventInfo[wEventID - g_cKdvMsgMgr.GetInnerMinValue()].name);

		TXDATANODE* tTmp = g_tTppInnerEventInfo[wEventID - g_cKdvMsgMgr.GetInnerMinValue()].tDataNode;
		u32 dwLen = 0;
		
		if (g_dwKdvShowMsg > 1)
		{
			while ( 0 != g_tTppInnerEventInfo[wEventID - g_cKdvMsgMgr.GetInnerMinValue()].eventid && NULL != tTmp && emxDataTypeEnd != tTmp->type )
			{
				msgprint( "type: %d, typesize:%d, type:%s, num:%d\n", 
					tTmp->type, tTmp->pretypesize, tTmp->pretype, tTmp->arraynum );

				ShowMsgContentInfo(tTmp->type);

				dwLen += tTmp[0].pretypesize * tTmp[0].arraynum;
				tTmp++;
			}
		}
	}
	else
	{
		msgprint( "[%s]Input event: %d is out of range!\n", pTitle,  wEventID );
		return;
	}
}


u16 GetEventbyName(  s8 abyEventName[50] )
{	
	u16 wMax = u16(g_cKdvMsgMgr.GetOutMaxValue() - g_cKdvMsgMgr.GetOutMinValue());
	u16 wLoop = 0;
	for ( ; wLoop < wMax; wLoop++ )
	{
		if ( g_tTppEventInfo[wLoop].name
			&&!strcmp( g_tTppEventInfo[wLoop].name, abyEventName ))
		{
			return u16(wLoop + g_cKdvMsgMgr.GetOutMinValue());
		}
	}
	wMax = u16(g_cKdvMsgMgr.GetInnerMaxValue() - g_cKdvMsgMgr.GetInnerMinValue());
	wLoop = 0;
	for ( ; wLoop < wMax; wLoop++ )
	{
		if ( g_tTppInnerEventInfo[wLoop].name
			&&!strncmp( g_tTppInnerEventInfo[wLoop].name, abyEventName, strlen(g_tTppInnerEventInfo[wLoop].name) ))
		{
			return u16(wLoop + g_cKdvMsgMgr.GetInnerMinValue());
		}
	}
	return 0;	
}

char* GetEventNamebyID( u32 wEvent )
{	
	if ( g_cKdvMsgMgr.GetOutMinValue() <= wEvent && wEvent <= g_cKdvMsgMgr.GetOutMaxValue() )
	{
		return g_tTppEventInfo[wEvent - g_cKdvMsgMgr.GetOutMinValue()].name;	
	}
	else if ( g_cKdvMsgMgr.GetInnerMinValue() <= wEvent && wEvent <= g_cKdvMsgMgr.GetInnerMaxValue() )
	{
		return g_tTppInnerEventInfo[wEvent - g_cKdvMsgMgr.GetInnerMinValue()].name;	
	}
	else
	{
		return " Message is not init!";
	}	
}

} //namespace UmsTpmsg