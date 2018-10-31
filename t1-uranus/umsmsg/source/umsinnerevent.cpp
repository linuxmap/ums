#include "msgmgr.h"
#include "umsinnerevent.h"

using namespace UmsTpmsg;

namespace UmsTpmsg {
extern TXEVENTINFO*  g_tTppInnerEventInfo;
} //namespace UmsTpmsg


//1.	EventID定义
#define _Check_Event_Range_
#include "umsinnerevent.h"

namespace UmsTpmsg {
//2. 描述
void event_ums_inner_description()
{
	
#define _MakeTpEventDescription_
#define _ev_segment(val) 
#define _event(val) g_tTppInnerEventInfo[val - begin_tp_inner_event_value].eventid = val; \
	g_tTppInnerEventInfo[val - begin_tp_inner_event_value].name = #val; \
	g_tTppInnerEventInfo[val - begin_tp_inner_event_value].tDataNode = NULL; \

#define _body(val1, val2) 
#define _blob(val1, val2)
#define _ev_end 
#define _ev_segment_end(val) 
#include "umsinnerevent.h"
}





static BOOL32 event_ums_inner_xml_marshal_table_install()
{
// 	//3. 初始化event struct marshal表
// #define _MakeTpEventDescription_
// #define _ev_segment(val) 
// #define _event(val) static TXDATANODE marshal##_##val[] ={ 
// #define _body(type , num) {emx_##type, sizeof(type), #type, num },
// #define _blob(type , num) {emx_##type##_blob, sizeof(type), #type, num },
// #define _ev_end {emxDataTypeEnd, 0, 0 } };
// #define _ev_segment_end(val) 
// #include "umsinnerevent.h"
// 	
// 	
// 	//4. 初始化 XML语法表
// #define _MakeTpEventDescription_
// #define _ev_segment(val) 
// #define _event(val) g_tInnerEventInfo[val - begin_tp_inner_event_value].eventid = val; \
// 	g_tInnerEventInfo[val - begin_tp_inner_event_value].name = #val; \
// 	g_tInnerEventInfo[val - begin_tp_inner_event_value].tDataNode = marshal##_##val; \
// //	g_cMapEvtNameToEvtID.SetAt( #val, val, emSDBMHash );
// 	
// #define _body(val1, val2) 
// #define _blob(val1, val2)
// #define _ev_end 
// #define _ev_segment_end(val) 
// #include "umsinnerevent.h"
	
	return TRUE;
}


int tp_inner_ums_event_state()
{
	BOOL bHaveOverloaded = FALSE;
	
	//ums
	TP_EVENT_ASSERT( tpsys );
	TP_EVENT_ASSERT( innerregsrv );
	TP_EVENT_ASSERT( umsinnerserver );
	TP_EVENT_ASSERT( umsinnercall );
	TP_EVENT_ASSERT( umsinnerconf );
	TP_EVENT_ASSERT( umsinnermediads );
	TP_EVENT_ASSERT( umsinnertvwall );
	TP_EVENT_ASSERT( umsinnerhdu);
	TP_EVENT_ASSERT( umsinneragent);
	TP_EVENT_ASSERT( umsinnerboard );
	TP_EVENT_ASSERT( umsinnermpu2 );
	TP_EVENT_ASSERT( umsinnerrec );
	TP_EVENT_ASSERT( umsinnervmp);
	TP_EVENT_ASSERT( innerumssipadapter );
	TP_EVENT_ASSERT( innerumsaudiomix );
	TP_EVENT_ASSERT( innerumsmediatrans );
	TP_EVENT_ASSERT( innerumsnetbuf );
	TP_EVENT_ASSERT( innerumsmpc );
	TP_EVENT_ASSERT( innerumsaudbas );
 	TP_EVENT_ASSERT( innereventxmpuvmp );
 	TP_EVENT_ASSERT( innereventxmpubas );
 	TP_EVENT_ASSERT( innereventxmpumix );
	TP_EVENT_ASSERT( innereventxmpuaudbas );

	
	int x = begin_umsinnereventcheck;
	assert( !bHaveOverloaded );
	
	assert(begin_umsinnereventcheck - begin_tpumsinner < event_count(tpumsinner));

	s32 nInnerUmsEventCount = ev_innereventxmpuaudbas_end - begin_tpsys;
	printf("[tp_inner_ums_event_state] %d-%d, EventCount:%d.\n", ev_innereventxmpuaudbas_end, begin_tpsys, nInnerUmsEventCount);

	return nInnerUmsEventCount;
}


static int tp_inner_ums_event_count = tp_inner_ums_event_state();
} //namespace UmsTpmsg