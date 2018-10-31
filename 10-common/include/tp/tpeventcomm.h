#ifndef _MakeTpEventDescription_

#ifndef _h_tpeventcomm_h__
#define _h_tpeventcomm_h__

#include "kdvtype.h"
#include "osp.h"
#include "eventid.h"

//[2011/3/8 zhaixiaogang]: tp��Ϣ�����40402��ʼ
//EV_WD8000E_END	40401
//EV_TP_BGN			40402
//EV_TP_END			45402
#define EV_TP_BGN					  EV_WD8000E_END + 1
#define EV_TP_END				      EV_TP_BGN + 5000

#include "xmldefine.h"

namespace UmsTpmsg {

define_event_count( tpeventcommon, 2000 ); 


//�ⲿ��Ϣ��Χ�����ܳ���5000
//�ⲿ��Ϣ��Χ��EV_TP_BGN,��40402��ʼ
//�ⲿ��Ϣ����δ� tpeventcommon ��ʼ��ռ��2000
const u16 begin_tp_event_value = EV_TP_BGN;
const u16 begin_tpeventcommon = begin_tp_event_value;

//�����������ⲿ��Ϣ
//tpupdateservice����tpeventcommon����Σ�ռ��10�����������Ϣ������Ҫcheck
define_event_count( tpupdateservice, 10 );
const u16 begin_tpupdateservice = begin_tpeventcommon;



//�ڲ���Ϣ�����tpsys�����������������Ϣ������Ҫcheck
define_event_count( tpsys, 70 ); 


//�ڲ���Ϣ��Χ
//�ڲ���Ϣ��EV_TP_END + 1,��45403��ʼ
//�ڲ���Ϣ����δ� tpsys ��ʼ��ռ��70
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


