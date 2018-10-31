#ifndef _MakeTpEventDescription_

#ifndef _h_tpeventcomm_h__
#define _h_tpeventcomm_h__

#include "kdvtype.h"
#include "osp.h"
#include "eventid.h"

//[2011/3/8 zhaixiaogang]: tp消息定义从40402开始
//EV_WD8000E_END	40401
//EV_TP_BGN			40402
//EV_TP_END			45402
#define EV_TP_BGN					  EV_WD8000E_END + 1
#define EV_TP_END				      EV_TP_BGN + 5000

#include "xmldefine.h"

namespace UmsTpmsg {

define_event_count( tpeventcommon, 2000 ); 


//外部消息范围，不能超过5000
//外部消息范围从EV_TP_BGN,即40402开始
//外部消息区间段从 tpeventcommon 开始，占用2000
const u16 begin_tp_event_value = EV_TP_BGN;
const u16 begin_tpeventcommon = begin_tp_event_value;

//升级服务器外部消息
//tpupdateservice属于tpeventcommon区间段，占用10个，定义的消息数量需要check
define_event_count( tpupdateservice, 10 );
const u16 begin_tpupdateservice = begin_tpeventcommon;



//内部消息区间段tpsys数量，定义的区间消息数量需要check
define_event_count( tpsys, 70 ); 


//内部消息范围
//内部消息从EV_TP_END + 1,即45403开始
//内部消息区间段从 tpsys 开始，占用70
const u16 begin_tp_inner_event_value = EV_TP_END + 1;
const u16 begin_tpsys = begin_tp_inner_event_value;


} //namespace UmsTpmsg


#define TP_EVENT_ASSERT( val )\
{\
	if ( ev_segment_range(val) >= event_count(val) )\
{\
	printf( "%s event range overloaded: real<%d>, limit<%d>\n", #val, ev_segment_range(val), event_count(val) );\
	bHaveOverloaded = TRUE;\
}\
}


#endif//_h_tpeventcomm_h__

#endif//_MakeTpEventDescription_


