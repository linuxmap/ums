#ifndef _PA_EventDescription_

#ifndef PAEVENTCOM_H
#define PAEVENTCOM_H

#include "kdvtype.h"
#include "osp.h"
#include "eventid.h"
//������Ϣ��ʼ��

const u16 pabegin_event_value = OSP_USEREVENT_BASE + 300;
//The end of message value is not using for mt,
//because the message which defined in below is 
//the inner message for mt
const u16 paend_event_value = OSP_USEREVENT_BASE + 500; 


//����ÿ�ε���Ϣ����
#define begin_define_event_count 
#define define_event_count( name, count ) \
const u16 _##name##_event_count = count
#define end_define_event_count

begin_define_event_count
define_event_count( event_value, 1 ); 
define_event_count( paconfevent, 160 );		
define_event_count( paend, 1 );
end_define_event_count

//������Ϣ��Χ
#define event_count(name) _##name##_event_count


#define begin_define_event_range(base) \
const u16 _first_event_value_ = pabegin_##base;
#define define_event_range(base,name) \
const u16 pabegin_##name = pabegin_##base + event_count(base)
#define outerevent_define_event_range(base)\
const u16 _ounterevent_event_value_ = pabegin_##base + event_count(base) +1;
#define end_define_event_range(base)\
const u16 _last_event_value_ = pabegin_##base + event_count(base)+1;
#define pcdvevent_define_event_range(base)\
const u16 _pcdvevent_event_value_ = pabegin_##base + event_count(base) + 1;

begin_define_event_range(event_value)
define_event_range(event_value,paconfevent);
end_define_event_range( paconfevent )






//����������Ϣ�壬��enum��ʵ����Ϣ��ֵ��Ψһ��
#define _paev_segment(val) ev_##val##_begin = pabegin_##val,
#define _paevent(val) val,
#define _pabody(val1, val2)
#define _pablob(val1, val2)
#define _paev_end
#define _paev_segment_end(val) ev_##val##_end 


//��ȡ��Ϣ�ε�ʵ����Ϣ����
//#define paev_segment_range(val) (ev_##val##_end - ev_##val##_begin)
//���һ����Ϣ������ֵ
//#define paev_last_event_val     _last_event_value_
//ʵ�ʷ������Ϣ����
//#define paev_using_event_space  (_last_event_value_ - _first_event_value_ + 1)
//���һ���ⲿ��Ϣ������ֵ
//#define paev_outerevent_last_event_val _ounterevent_event_value_
//#define paev_pcdv_event_val  _pcdvevent_event_value_          

//��ȡÿһ�εĵ�һ����Ϣ����ֵ
//#define paget_first_event_val(val) (ev_##val##_begin)
//��ȡÿһ�ε����һ����Ϣ����ֵ
//#define paget_last_event_val(val)  (ev_##val##_end)
//�ⲿ��Ϣ������ʼ��
//const u16  paev_appinner_begin = ev_last_event_val + 1 ;

#endif

#endif



