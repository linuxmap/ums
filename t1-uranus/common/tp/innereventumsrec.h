#ifndef __inner_event_umsrec_h_
#define __inner_event_umsrec_h_

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmumsinnerRec
{
#endif
	_ev_segment( umsinnerrec )
	
	//���¼��������������Ϣ
	_event ( ev_rec_add_cfg )
		_body( TRecorderCfg, 1)
	_ev_end

	//����¼��������������Ϣ
	_event( ev_rec_mdy_cfg)
		_body( TRecorderCfg, 1)	//�ϵ�������Ϣ
		_body( TRecorderCfg, 1)	//�µ�������Ϣ
	_ev_end

	//ɾ��������Ϣ
	_event( ev_rec_del_cfg)
		_body( TRecorderCfg, 1)
	_ev_end

	//ɾ��ע��
	_event( ev_rec_disconnect)
	_ev_end

	//����ע��״̬
	_event( ev_rec_update_reg)
		_body(TRecRegStatus, 1)
	_ev_end

	//����¼��ʹ�õ�ת����
	_event( ev_rec_update_media)
		_body(TRecUseMedia, 1)
	_ev_end

	//ע��
	_event(  ev_rec_reg_req ) 
		_body( TRecRegInfo, 1 )
	_ev_end

	//ע��ʧ��
	_event( ev_rec_req_nack)
	_ev_end

	//ע��ɹ�
	_event( ev_rec_req_ack)
		_body(TRecRegAck, 1)
	_ev_end

	//����״̬
	_event( ev_rec_status_nty)
		_body(TRecStatusNty, 1)
	_ev_end

	//�����ļ��б�
	_event( ev_rec_file_list_req)
		_body(u8, 1)	//�豸ID
	_ev_end

	//�����ļ��б�ʧ��
	_event( ev_rec_file_list_nack)
		_body(u8, 1)	//�豸ID
	_ev_end

	//�ļ��б�
	_event( ev_rec_file_list)
		_body(TRecFileList, 1)
	_ev_end

	//ɾ���ļ�
	_event( ev_recDelFile)
		_body(TRecMdyFileInfo, 1)
	_ev_end

	//ɾ���ļ��ɹ�
	_event( ev_recDelFile_ack)
	_ev_end

	//ɾ���ļ�ʧ��
	_event( ev_recDelFile_nack)
		_body(EmMdyRecFileRes, 1)
	_ev_end

	//�޸��ļ�
	_event(ev_recMdyFile)
		_body(TRecMdyFileInfo, 1)	//
		_body(TRecMdyFileInfo, 1s)
	_ev_end

	//�޸��ļ��ɹ�
	_event(ev_recMdyFile_ack)
	_ev_end

	//�޸��ļ�ʧ��
	_event(ev_recMdyFile_nack)
		_body(EmMdyRecFileRes, 1)
	_ev_end

	//У��¼�����
	_event(ev_rec_check_param)
		_body(TStartRecInfo, 1)
	_ev_end

	//У��¼��������
	_event(ev_rec_check_param_rsp)
		_body(EmUseReccorderRes, 1)
		_body(TStartRecInfo, 1)
	_ev_end

	//¼������
	_event( ev_rec_recorder_conf)
		_body(TStartRecInfo, 1)
	_ev_end

	//¼������ɹ�
	_event( ev_rec_recorder_conf_ack)
		_body(TRecConfResult, 1)
	_ev_end

	//¼������ʧ��
	_event( ev_rec_recorder_conf_nack)
		_body(TRecConfResult, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//����¼�񽻻�
	_event( ev_recBulidRecTrans)
		_body(TRecConfTrans, 1)
	_ev_end

	//��������ʧ��
	_event( ev_recBuildRecTrans_rsp)
		_body(BOOL32,	1)
		_body(TRecConfTrans, 1)
	_ev_end

	//�������
	_event( ev_recDesRecTrans)
		_body(TRecConfTrans, 1)
	_ev_end

	//ɾ�����񽻻�
	_event( ev_recDesPlayTrans)
	_ev_end

	//�������񽻻�
	_event( ev_recBuildPlayTrans)
		_body(TPlayTrans, 1)
	_ev_end

	//���·��񽻻�
	_event( ev_recUpdatePlayTrans)
		_body(TPlayTrans, 1)
	_ev_end

	//�������񽻻��ɹ�
	_event( ev_recBuildPlayTrans_rsp)
		_body(BOOL32, 1)
		_body(TPlayTrans, 1)
	_ev_end


	//��ͣ����¼��
	_event( ev_recPauseConfRec)
		_body(TRecPauseInfo, 1)
	_ev_end

	//��ͣ����ɹ�
	_event( ev_recPauseConfRec_ack)
		_body(TRecPauseInfo, 1)
	_ev_end

	//��ͣ����ʧ��
	_event( ev_recPauseConfRec_nack)
		_body(TRecPauseInfo, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//����¼��
	_event(ev_recResumeConfRec)
		_body(TRecPauseInfo, 1)
	_ev_end

	_event(ev_recResumeConfRec_ack)
		_body(TRecPauseInfo, 1)
	_ev_end

	_event(ev_recResumeConfRec_nack)
		_body(TRecPauseInfo, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//ֹͣ¼��
	_event( ev_recStopConfRec)
		_body(TRecPauseInfo, 1)
	_ev_end

	//ֹͣ¼��ɹ�
	_event( ev_recStopConfRec_ack)
		_body(TRecPauseInfo, 1)
	_ev_end

	//ֹͣ¼��ʧ��
	_event( ev_recStopConfRec_nack)
		_body(TRecPauseInfo, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//���������
	_event( ev_rec_check_play_param)
		_body(TConfPlayInfo, 1)
	_ev_end

	//���������Ӧ��
	_event( ev_rec_check_play_param_rsp)
		_body(EmUseReccorderRes, 1)
		_body(TConfPlayInfo, 1)
	_ev_end

	//��������
	_event( ev_recPlay)
		_body(TConfPlayInfo, 1)
	_ev_end

	//��������ɹ�
	_event( ev_recPlay_ack)
		_body(TConfPlayAck, 1)
	_ev_end

	//��������ʧ��
	_event( ev_recPlay_nack)
		_body(TConfPlayNack, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//��ͣ����
	_event( ev_recPauseFilePlay)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recPauseFilePlay_ack)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recPauseFilePlay_nack)
		_body(TMdyFilePlay, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//��������
	_event( ev_recResumeFilePlay)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recResumeFilePlay_ack)
		_body(TMdyFilePlay, 1)
	_ev_end

	_event( ev_recResumeFilePlay_nack)
		_body(TMdyFilePlay, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//ֹͣ����
	_event( ev_recStopFilePlay)
		_body(TMdyFilePlay, 1)
	_ev_end

	//ֹͣ����ɹ�
	_event( ev_recStopFilePlay_ack)
		_body(TMdyFilePlay, 1)
	_ev_end

	//ֹͣ����ʧ��
	_event( ev_recStopFilePlay_nack)
		_body(TMdyFilePlay, 1)
		_body(EmUseReccorderRes, 1)
	_ev_end

	//����ͨ��״̬
	_event( ev_recUpdataChanStatus)
		_body(TRecChanStatus, 1)
	_ev_end

	//�ؼ�֡����
	_event( ev_recIFrameReq)
		_body(TRecIFrameReq, 1)
	_ev_end

	//���񽻻��������
	_event( ev_recSwitch_nty)
		_body(TMdyFilePlay, 1)
	_ev_end

	//����ͨ������
	_event( ev_recUpdateProg)
		_body(TRecChanProgInfo, 1)
	_ev_end

	//�Ҷ��ն�¼��
	_event( ev_rec_hungup_mt_rec)
		_body(THungupRecInfo,	1)
	_ev_end

	//������ʧ��
	_event( ev_rec_getvid_failed)
		_body(TRecGetVidInfo, 1)
	_ev_end

	//�Ҷϻ���¼��
	_event( ev_rec_hungup_conf_rec)
		_body(THungupRecInfo,	1)
	_ev_end

	//�Ҷϻ᳡����
	_event( ev_rec_hungun_conf_play)
		_body(THungupRecInfo,	1)
	_ev_end

	//����᳡��ʽ
	_event( ev_recMtFormat_req)
		_body(TLogUser, 1)
		_body(u16, 1)
	_ev_end

	//�᳡��ʽӦ��
	_event( ev_recMtFormat_rsp)
		_body(TLogUser, 1)
		_body(TTPRecMtFormat, 1)
	_ev_end

#ifndef _MakeTpEventDescription_
	_ev_segment_end(umsinnerrec)
};
#endif

#endif