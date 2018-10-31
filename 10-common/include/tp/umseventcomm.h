#ifndef _h_umseventcomm_h__
#define _h_umseventcomm_h__

#include "tpeventcomm.h"

using namespace UmsTpmsg;

namespace UmsTpmsg {
// ��Ϣ��������
define_event_count( tpumswithcms, 600 );

// ��Щ�������Ϣ������������Ҫcheck
define_event_count( tpumswithumssipadapter, 200 );
define_event_count( tpumswithumsaudiomix, 20 ); 
define_event_count( tpumswithmediatrans, 20 ); 
define_event_count( tpumswithumshdu2, 50 ); 


// �ⲿ��Ϣ��Χ�����ܳ���5000
// tpeventcommon ���ⲿ��Ϣ�εĵ�һ�����䣬ռ��2000��
// tpumswithcms �����ⲿ��Ϣ�Σ����� tpeventcommon ��ʼ��ռ��600��
define_event_begin( tpeventcommon, tpumswithcms );

// ��Щ�������Ϣ������������Ҫcheck
// tpumswithumssipadapter �����ⲿ��Ϣ�Σ����� tpumswithcms ��ʼ��ռ��200��
define_event_begin( tpumswithcms, tpumswithumssipadapter );
// tpumswithumsaudiomix �����ⲿ��Ϣ�Σ����� tpumswithumssipadapter ��ʼ��ռ��20��
define_event_begin( tpumswithumssipadapter, tpumswithumsaudiomix );
// tpumswithmediatrans �����ⲿ��Ϣ�Σ����� tpumswithumsaudiomix ��ʼ��ռ��20��
define_event_begin( tpumswithumsaudiomix, tpumswithmediatrans );
// tpumswithumshdu2 �����ⲿ��Ϣ�Σ����� tpumswithmediatrans ��ʼ��ռ��50��
define_event_begin( tpumswithmediatrans, tpumswithumshdu2 );

// �ⲿ����ε����ֵ��tpumswithumshdu2 ���ⲿ����ε����һ������
const u16 last_outer_event_value = begin_tpumswithumshdu2 + event_count(tpumswithumshdu2);


//////////����ums�����ⲿ��Ϣ//////////////////
//ums��Ϣ���壬��Щ��Ϣ�ζ����� tpumswithcms���ܺͲ��ܳ���600������Щ�������Ϣ������������Ҫcheck
//��Щ��Ϣ�ζ��Ǹ�umcͨ��ʹ�õģ���Ҫ���ּ����ԣ���Ҫ�޸����еģ�ֻ��������ӣ���umc�޹ص���Ϣ��Ҫ��ӵ��������
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


// ��Щ����δ�begin_tpumswithcms��ʼ��������tpumswithcms��������
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
define_event_begin( outerumscfgex, umsouteventcheck);//umsouteventcheck����check�ڲ���Ϣ֮���Ƿ񳬹����ֵ600
//////////����ums�����ⲿ��Ϣ//////////////////



// �ڲ���Ϣ��Χ
define_event_count( tpumsinner, 1000 );

// tpsys ���ڲ���Ϣ�εĵ�һ�����䣬ռ��70��
// tpumsinner �����ڲ���Ϣ�Σ����� tpsys ��ʼ���ܼ�1000��
define_event_begin( tpsys, tpumsinner );

const u16 last_inner_event_value = begin_tp_inner_event_value + event_count(tpsys) + event_count(tpumsinner);

//////////����ums�����ڲ���Ϣ//////////////////
//ums��Ϣ���壬��Щ��Ϣ�ζ����� tpumsinner���ܺͲ��ܳ���1000������Щ�������Ϣ������������Ҫcheck
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

// ��Щ����δ�begin_tpumsinner��ʼ��������tpumsinner��������
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

define_event_begin( innereventxmpuaudbas, umsinnereventcheck);//umsinnereventcheck����check�ڲ���Ϣ֮���Ƿ񳬹����ֵ1000
//////////����ums�����ڲ���Ϣ//////////////////

} //namespace UmsTpmsg

#endif // _h_umseventcomm_h__
