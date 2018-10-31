#ifndef _h_innereventumshdu_h__
#define _h_innereventumshdu_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emumsinnerhdu
{
#endif

	_ev_segment( umsinnerhdu )

	//����ǽҵ��ע��
	_event(  ev_hdu_reg_req ) 
		_body( THduRegInfo, 1 )
	_ev_end
		
	//reg ack
	_event(  ev_hdu_req_ack )
		_body( TUmsRSParam,    1 )
		_body( THduRegCfgAck,  1 )
	_ev_end
		
	//reg nack
	_event(  ev_hdu_req_nack )
	_ev_end

	//�޸İ���������Ϣ
	_event( ev_hdu_brd_modify)
		_body(TTPBrdPos,	1)
	_ev_end

	//��������
	_event( ev_hdu_update_req)
		_body(TTPBrdUpGrade, 1)
	_ev_end

	_event( ev_hdu_update_res)
		_body(THduUpdateRes, 1)
	_ev_end

	//�������ӽ��
	_event( ev_hdu_update_nty)
		_body(TTPBrdUpGrade, 1)
		_body(EmUpdateHduRet, 1)
	_ev_end

	//�޸�ͨ����Ϣ
	_event( ev_hdu_chan_modify)
		_body(THduInfo,		1)
	_ev_end

	//ɾ��ͨ��
	_event( ev_hdu_chan_del)
		_body(TTPBrdPos,	1)
	_ev_end

	//����
	_event( ev_hdu_reboot)
	_body(TTPBrdPos,	1)
	_ev_end

	//֪ͨeqp������Ϣ
	_event( ev_hdu_cfg_info)
		_body(THduCfgInfo, 1)
	_ev_end

	_event( ev_hdu_disconnect)
	_ev_end

	//֪ͨservice����ע��״̬
	_event( ev_hdu_brd_reg_res)
		_body(THduRegStatus, 1)
	_ev_end

	//���°�����ҵ���ע��״̬
	_event( ev_hdu_service_reg_res)
		_body(THduRegStatus, 1)
		_body(u16, 1)
	_ev_end
		
	//�޸�ͨ����Ϣ
	_event( ev_hdu_notify_channel)
		_body(THduInfo, 1)
	_ev_end

	//ɾ������ǽ��Ϣ
	_event( ev_hdu_del )
		_body(u8, 1)	//���
		_body(u8, 1)	//�ۺ�
	_ev_end

	//��������
	_event( ev_hdu_play_req)
		_body(THduPlayInfo, 1)
		_body(TAddTvMonitorAck, 1)
	_ev_end

	//��������Ӧ��
	_event ( ev_hdu_play_ack)
		_body(THduPlayInfo, 1)
	_ev_end

	//��������Ӧ��
	_event ( ev_hdu_play_nack)
		_body(THduPlayInfo, 1)
	_ev_end

	//ֹͣ��������
	_event( ev_hdu_stop_play_req)
		_body(THduPlayInfo, 1)
	_ev_end

	_event( ev_hdu_stop_play_ack)
		_body(THduPlayInfo, 1)
	_ev_end

	_event( ev_hdu_stop_play_nack)
		_body(THduPlayInfo, 1)
	_ev_end

	//����ͨ��״̬
	_event( ev_hdu_update_chan_status)
		_body(THduChanStatus, 1)
	_ev_end

	//����ؼ�֡
	_event( ev_hdu_req_iframe)
		_body(THduIFrameInfo, 1)
	_ev_end

	//ҵ�����״̬
	_event( ev_hdu_updata_status)
		_body(THduUpdateInfo, 1)
	_ev_end

	//��������
	_event(ev_hdu_set_vol)
		_body(THduVolInfo, 1)
	_ev_end

	_event(ev_hdu_set_vol_res)
		_body(THduVolInfo, 1)
		_body(EmTpHduSetVolRes, 1)
	_ev_end

	// �л�ͨ������ģʽ
	_event(ev_hdu_change_chan_mode)
	_body(THduChanModeInfo, 1)
	_ev_end
	
	_event(ev_hdu_change_chan_mode_res)
	_body(THduChanModeInfo, 1)
	_body(EmTpHduChangeChanModeRes, 1)
	_ev_end


	//nty qt media key
	_event( ev_hdu_media_key_nty)
	_body(THduPlayInfo, 1)
	_body(TTPQTMediaKeyInfo, 1)
	_ev_end	


#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnerhdu)
};
#endif

#endif