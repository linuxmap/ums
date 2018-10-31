#ifndef _h_eventoutmpu2tp_h_
#define _h_eventoutmpu2tp_h_

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventMpu2tpMsg
{
#endif
	_ev_segment( outermpu2tp )
 
	//vmp ע��
	_event(ev_mpu2tp_regist)
		_body(TVmpRegistInfo, 1)
	_ev_end

	//vmp ע��ɹ�
	_event(ev_mpu2tp_regist_ack)
		_body(TVmpRegAck, 1)
		_body(TVmpTimeSpan, 1)
		_body(u32, 1)
	_ev_end

	//vmp ע��ʧ��
	_event(ev_mpu2tp_regist_nack)
	_ev_end
 
	//�����ϳ�
	_event(ev_mpu2tp_start_req)
		_body(TVmpStartParam, 1)
	_ev_end
	//���
	_event(ev_mpu2tp_start_res)
		_body(TVmpStartRes, 1)
	_ev_end
 
	//�޸ĺϳɲ���
	_event(ev_mpu2tp_mdy_param)
		_body(TVmpMdyInfo, 1)
	_ev_end

	//�޸ĺϳɲ������
	_event(ev_npu2tp_mdy_param_res)
		_body(TVmpMdyRes, 1)
	_ev_end
 
	//ֹͣ����ϳ�
	_event(ev_mpu2tp_stop_req)
	_ev_end

	//ֹͣ����ϳɽ��
	_event(ev_mpu2tp_stop_res)
		_body(TVmpStopRes, 1)
	_ev_end
 
	 //���ͨ��
	 _event(ev_mpu2tp_addchan_req)
		_body(TVmpChanInfo, 1)
	 _ev_end

	 //���ͨ�����
	_event(ev_mpu2tp_addchan_res)
		_body(TVmpChanRes, 1)
	_ev_end

	//ɾ��ͨ��
	_event(ev_mpu2tp_delchan_req)
		_body(TVmpChanInfo, 1)
	_ev_end

	//ɾ��ͨ��
	_event(ev_mpu2tp_delchan_res)
		_body(TVmpChanRes, 1)
	_ev_end

	//���ϳɳ�Ա�Ƿ���Ҫ�ؼ�֡
	_event(ev_mpu2tp_NeedFrame_Timer)
	_ev_end

	//���ϳɳ�Ա�Ƿ���Ҫ�ؼ�֡
	_event(ev_mpu2tp_AskFrame_Req)
	_body(TVmpAskFrame, 1)
	_ev_end

	//���ĺϳ���IP
	_event(ev_mpu2tp_ChangeUmsIP_Req)
	_body(TVmpRegAck, 1)
	_ev_end

	//���µ�ǰ����ͨ���ı�ʶ
	_event(ev_mpu2tp_SpeakerFlag_Ntfy)
	_body(TVmpSpeakerFlag, 1)
	_ev_end

	//���µ�ǰ����ͨ���ı�ʶ 400ms��֪ͨ���ԭ����ɫ
	_event(ev_mpu2tp_UpdateFlag400_Timer)
	_ev_end

	//���µ�ǰ����ͨ���ı�ʶ 200ms��֪ͨ��ɷ�������ɫ
	_event(ev_mpu2tp_UpdateFlag200_Timer)
	_ev_end


	// qt mediakey
	_event(ev_mpu2tp_SetMediaKey_Req)
	_body(TTPMediaKeyInfo, 1)
	_ev_end

#ifndef _MakeTpEventDescription_
	_ev_segment_end( outermpu2tp )
};
#endif

#endif