#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "msgmgr.h"
#include "hashtable.h"
#include "umsxmltype.h"
#include "tpstruct.h"
#include "umscommonstruct.h"
#include "tplog.h"

using namespace UmsTpmsg;

namespace UmsTpmsg {

extern CMapStrToInt g_cTppMapEvtNameToEvtID;
extern TXEVENTINFO*  g_tTppEventInfo;

#define  VER_umsmsg_ver UMS_VerID
API void msgver()
{
	msgprint("umsmsg ver: %s  compile time: %s:%s\n",
		VER_umsmsg_ver, __DATE__,  __TIME__);
}

} //namespace UmsTpmsg


//1. 定义消息ID
#define _Check_Event_Range_
#include "umsoutevent.h"



namespace UmsTpmsg {

static BOOL32 event_xml_marshal_table_install()
{
//3. 初始化event struct marshal表
#define _MakeTpEventDescription_
#define _ev_segment(val) 
#define _event(val) static TXDATANODE marshal##_##val[] ={ 
#define _body(type , num) {emx_##type, sizeof(type), #type, num },
#define _blob(type , num) {emx_##type##_blob, sizeof(type), #type, num },
#define _ev_end {emxDataTypeEnd, 0, 0 } };
#define _ev_segment_end(val) 
#include "umsoutevent.h"


//4. 初始化 XML语法表
#define _MakeTpEventDescription_
#define _ev_segment(val) 
#define _event(val) g_tTppEventInfo[val - begin_tp_event_value].eventid = val; \
	g_tTppEventInfo[val - begin_tp_event_value].name = #val; \
	g_tTppEventInfo[val - begin_tp_event_value].tDataNode = marshal##_##val; \
	g_cTppMapEvtNameToEvtID.SetAt( #val, val, emSDBMHash );

#define _body(val1, val2) 
#define _blob(val1, val2)
#define _ev_end 
#define _ev_segment_end(val) 
#include "umsoutevent.h"
	
	return TRUE;
}


static int tp_event_state()
{
	BOOL bHaveOverloaded = FALSE;
	
	//ums
	TP_EVENT_ASSERT( outerumslogin );
	TP_EVENT_ASSERT( outerumsreg );
	TP_EVENT_ASSERT( outerumsconftemplate );
	TP_EVENT_ASSERT( outerumscall );
	TP_EVENT_ASSERT( outerumscfg );
	TP_EVENT_ASSERT( outerumshdu );	
	TP_EVENT_ASSERT( outerumseqp );
	TP_EVENT_ASSERT( outerumstool );
	TP_EVENT_ASSERT( outerumsboard );
	TP_EVENT_ASSERT( outerumscommonbrd );
	TP_EVENT_ASSERT( outerumsrec);
	TP_EVENT_ASSERT( outermpu2tp);
	TP_EVENT_ASSERT( outerumsselview);
	TP_EVENT_ASSERT( outerumsbrdvmp);
	TP_EVENT_ASSERT( outumsmcucasecade);
	TP_EVENT_ASSERT( outerumsquantum);
	TP_EVENT_ASSERT( outerumscfgex);
	TP_EVENT_ASSERT( tpumswithumssipadapter );
	TP_EVENT_ASSERT( tpumswithumsaudiomix );
	TP_EVENT_ASSERT( tpumswithmediatrans );
	TP_EVENT_ASSERT( tpumswithumshdu2 );
	
	//添加对升级服务器消息的校验
	TP_EVENT_ASSERT( tpupdateservice );

	assert( begin_umsouteventcheck - begin_tpumswithcms < event_count(tpumswithcms));	//各模块总数判断
	assert( !bHaveOverloaded );

	s32 nTPEventCount = ev_tpumswithumshdu2_end - begin_tpeventcommon;
	printf("[tp_event_state] %d-%d, EventCount:%d.\n", ev_tpumswithumshdu2_end, begin_tpeventcommon, nTPEventCount);

	return nTPEventCount;
}
static int tp_event_count = tp_event_state();


void event_ums_inner_description();
void event_ums_inner_xml_marshal_table_install();
void event_cns_inner_description();


void InitTpEvent()
{
	TTpMsgInfo tInfo;
	tInfo.m_dwOutMinEventValue = begin_tp_event_value;
	tInfo.m_dwOutMaxEventValue = last_outer_event_value;
	
	tInfo.m_dwInnerMinEventValue = begin_tp_inner_event_value;
	tInfo.m_dwInnerMaxEventValue = last_inner_event_value;
 

	tInfo.m_ptMsgEnumDataInfo = CombineEnumDateInfo();
	tInfo.m_ptMsgStructDataInfo = CombineStructDateInfo();

	if (NULL == tInfo.m_ptMsgEnumDataInfo || NULL == tInfo.m_ptMsgStructDataInfo)
	{
		msgprint("InitTpEvent fail, please check out!!!\n\n");
	}

	msgprint("[InitTpEvent] begin_tp_event_value:%d, last_outer_event_value:%d, begin_tp_inner_event_value:%d, last_inner_event_value:%d.\n",
		begin_tp_event_value, last_outer_event_value, begin_tp_inner_event_value, last_inner_event_value);

	InitEventMgr(tInfo);
	
	event_xml_marshal_table_install();
	
}



void InitUmsEvent()
{
	InitTpEvent();
	event_ums_inner_description();
}


void regist_tpmsg_commond()
{
#ifdef _LINUX_
	OspRegCommand("msgver", (void*)msgver, "API void msgver()");
#endif // _LINUX_
}


} //namespace UmsTpmsg

//END OF FILE


