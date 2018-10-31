#ifndef _h_umseventcomm_h__
#define _h_umseventcomm_h__

#include "tpeventcomm.h"

using namespace UmsTpmsg;

namespace UmsTpmsg {
// 消息数量定义
define_event_count( tpumswithcms, 600 );

// 这些区间段消息定义数量均需要check
define_event_count( tpumswithumssipadapter, 200 );
define_event_count( tpumswithumsaudiomix, 20 ); 
define_event_count( tpumswithmediatrans, 20 ); 
define_event_count( tpumswithumshdu2, 50 ); 


// 外部消息范围，不能超过5000
// tpeventcommon 是外部消息段的第一个区间，占用2000个
// tpumswithcms 属于外部消息段，紧接 tpeventcommon 开始，占用600个
define_event_begin( tpeventcommon, tpumswithcms );

// 这些区间段消息定义数量均需要check
// tpumswithumssipadapter 属于外部消息段，紧接 tpumswithcms 开始，占用200个
define_event_begin( tpumswithcms, tpumswithumssipadapter );
// tpumswithumsaudiomix 属于外部消息段，紧接 tpumswithumssipadapter 开始，占用20个
define_event_begin( tpumswithumssipadapter, tpumswithumsaudiomix );
// tpumswithmediatrans 属于外部消息段，紧接 tpumswithumsaudiomix 开始，占用20个
define_event_begin( tpumswithumsaudiomix, tpumswithmediatrans );
// tpumswithumshdu2 属于外部消息段，紧接 tpumswithmediatrans 开始，占用50个
define_event_begin( tpumswithmediatrans, tpumswithumshdu2 );

// 外部区间段的最大值，tpumswithumshdu2 是外部区间段的最后一个区间
const u16 last_outer_event_value = begin_tpumswithumshdu2 + event_count(tpumswithumshdu2);


//////////定义ums各段外部消息//////////////////
//ums消息定义，这些消息段都属于 tpumswithcms，总和不能超过600个，这些区间段消息定义数量均需要check
//这些消息段都是跟umc通信使用的，需要保持兼容性，不要修改已有的，只能往后添加，与umc无关的消息不要添加到这个区间
define_event_count( outerumslogin, 20 );
define_event_count( outerumsreg, 20 );
define_event_count( outerumsconftemplate, 20 );
define_event_count( outerumscall, 100 );
define_event_count( outerumscfg, 25 );
define_event_count( outerumshdu, 20 );
define_event_count( outerumseqp, 80 );
define_event_count( outerumstool, 20);
define_event_count( outerumsboard, 25);
define_event_count( outerumscommonbrd, 30);
define_event_count( outerumsrec, 35);
define_event_count( outermpu2tp, 50);
define_event_count( outerumsselview, 15);
define_event_count( outerumsbrdvmp, 30);
define_event_count( outumsmcucasecade, 50);
define_event_count( outerumsquantum, 15);
define_event_count( outerumscfgex, 20 );


// 这些区间段从begin_tpumswithcms开始，均属于tpumswithcms这个区间段
const u16 begin_outerumslogin = begin_tpumswithcms;
define_event_begin( outerumslogin, outerumsreg );
define_event_begin( outerumsreg, outerumsconftemplate );
define_event_begin( outerumsconftemplate, outerumscall );
define_event_begin( outerumscall, outerumscfg );
define_event_begin( outerumscfg, outerumshdu );
define_event_begin( outerumshdu, outerumseqp );
define_event_begin( outerumseqp, outerumstool);
define_event_begin( outerumstool, outerumsboard);
define_event_begin( outerumsboard, outerumscommonbrd);
define_event_begin( outerumscommonbrd, outerumsrec);
define_event_begin( outerumsrec, outermpu2tp);
define_event_begin( outermpu2tp, outerumsselview);
define_event_begin( outerumsselview, outerumsbrdvmp);
define_event_begin( outerumsbrdvmp, outumsmcucasecade);
define_event_begin( outumsmcucasecade, outerumsquantum);
define_event_begin( outerumsquantum, outerumscfgex);
define_event_begin( outerumscfgex, umsouteventcheck);//umsouteventcheck用于check内部消息之和是否超过最大值600
//////////定义ums各段外部消息//////////////////



// 内部消息范围
define_event_count( tpumsinner, 1000 );

// tpsys 是内部消息段的第一个区间，占用70个
// tpumsinner 属于内部消息段，紧接 tpsys 开始，总计1000个
define_event_begin( tpsys, tpumsinner );

const u16 last_inner_event_value = begin_tp_inner_event_value + event_count(tpsys) + event_count(tpumsinner);

//////////定义ums各段内部消息//////////////////
//ums消息定义，这些消息段都属于 tpumsinner，总和不能超过1000个，这些区间段消息定义数量均需要check
define_event_count( innerregsrv, 30 );
define_event_count( umsinnerserver, 10 );
define_event_count( umsinnercall, 40);
define_event_count( umsinnerconf, 60);
define_event_count( umsinnermediads, 10);
define_event_count( umsinnertvwall, 15);
define_event_count( umsinnerhdu, 35);
define_event_count( umsinneragent, 30);
define_event_count( umsinnerboard, 20);
define_event_count( umsinnermpu2, 40);
define_event_count( umsinnerrec, 70);
define_event_count( umsinnervmp, 100);
define_event_count( innerumssipadapter, 50 );
define_event_count( innerumsaudiomix, 50 );
define_event_count( innerumsmediatrans, 50 );
define_event_count( innerumsnetbuf, 50 );
define_event_count( innerumsmpc, 50 );
define_event_count( innerumsaudbas, 20 );
define_event_count( innereventxmpuvmp, 20 );
define_event_count( innereventxmpubas, 20 );
define_event_count( innereventxmpumix, 20 );
define_event_count( innereventxmpuaudbas, 20 );

// 这些区间段从begin_tpumsinner开始，均属于tpumsinner这个区间段
const u16 begin_innerregsrv = begin_tpumsinner;
define_event_begin( innerregsrv, umsinnerserver );
define_event_begin( umsinnerserver, umsinnercall );
define_event_begin( umsinnercall, umsinnerconf );
define_event_begin( umsinnerconf, umsinnermediads );
define_event_begin( umsinnermediads, umsinnertvwall );
define_event_begin( umsinnertvwall, umsinnerhdu);
define_event_begin( umsinnerhdu, umsinneragent);
define_event_begin( umsinneragent, umsinnerboard);
define_event_begin( umsinnerboard, umsinnermpu2);
define_event_begin( umsinnermpu2, umsinnerrec);
define_event_begin( umsinnerrec, umsinnervmp);
define_event_begin( umsinnervmp, innerumssipadapter );
define_event_begin( innerumssipadapter, innerumsaudiomix );
define_event_begin( innerumsaudiomix, innerumsmediatrans );
define_event_begin( innerumsmediatrans, innerumsnetbuf );
define_event_begin( innerumsnetbuf, innerumsmpc );
define_event_begin( innerumsmpc, innerumsaudbas );
define_event_begin( innerumsaudbas, innereventxmpuvmp );
define_event_begin( innereventxmpuvmp, innereventxmpubas );
define_event_begin( innereventxmpubas, innereventxmpumix );
define_event_begin( innereventxmpumix, innereventxmpuaudbas );

define_event_begin( innereventxmpuaudbas, umsinnereventcheck);//umsinnereventcheck用于check内部消息之和是否超过最大值1000
//////////定义ums各段内部消息//////////////////

} //namespace UmsTpmsg

#endif // _h_umseventcomm_h__
