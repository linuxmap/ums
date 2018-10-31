#ifndef XML_DEFINE_H
#define XML_DEFINE_H

//����������Ϣ�壬��enum��ʵ����Ϣ��ֵ��Ψһ��
#define _ev_segment(val) ev_##val##_begin = begin_##val,
#define _event(val) val,
#define _body(val1, val2)
#define _blob(val1, val2)
#define _ev_end
#define _ev_segment_end(val) ev_##val##_end 

//��ȡ��Ϣ�ε�ʵ����Ϣ����
#define ev_segment_range(val) (ev_##val##_end - ev_##val##_begin)

//ʵ�ʷ������Ϣ����
#define ev_using_event_space  (_last_event_value_ - begin_event_value + 1)


#define define_event_count( name, count ) const u16 _##name##_event_count = count
#define event_count(name) _##name##_event_count
#define define_event_begin(base, name) const u16 begin_##name = begin_##base + event_count(base)

#define segment_begin(val)	ev_##val##_begin
#define segment_end(val)	ev_##val##_end

#endif

