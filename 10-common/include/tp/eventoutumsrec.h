#ifndef __h_eventoutumsrec_h_
#define __h_eventoutumsrec_h_

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventRecMsg
{
#endif
	_ev_segment( outerumsrec )

/***********************<<֪ͨ¼��������������Ϣ>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
_event(  ev_rec_base_info_nty )
	_body(TRecBaseInfo,	TP_MAX_VCR)	
_ev_end

/***********************<<����¼��������ע��״̬>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
_event(  ev_rec_reg_status_nty )
	_body(u8, 1)	//�豸ID
	_body(BOOL32, 1) //�Ƿ�ע��
_ev_end


/***********************<<¼���������ļ��б�>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
_event(  ev_rec_file_list_info )
	_body( TRecFileListInfo, 1)	//�ļ��б���Ϣ
_ev_end

/***********************<<ɾ���ļ�>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
_event(  ev_rec_del_file_req )
	_body( TRecFileInfo, 1)	//�ļ��б���Ϣ
_ev_end

/***********************<<ɾ���ļ��ɹ�>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
_event( ev_rec_del_file_ack)
_ev_end

/***********************<<ɾ���ļ�ʧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
_event( ev_rec_del_file_nack)
	_body(EmMdyRecFileRes, 1)
_ev_end

/***********************<<�޸��ļ�>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
_event(  ev_rec_mdy_file_req )
	_body( TRecFileInfo, 1)	//�޸�ǰ����Ϣ
	_body( TRecFileInfo, 1)	//�޸ĺ����Ϣ
_ev_end

//�޸�ʧ��
_event(  ev_rec_mdy_file_nack )
	_body( TRecFileInfo, 1)	//�޸�ǰ����Ϣ
	_body( TRecFileInfo, 1)	//�޸ĺ����Ϣ
	_body( EmMdyRecFileRes, 1)//����ԭ��
_ev_end

//�޸ĳɹ�
_event(  ev_rec_mdy_file_ack )
	_body( TRecFileInfo, 1)	//�޸�ǰ����Ϣ
	_body( TRecFileInfo, 1)	//�޸ĺ����Ϣ
_ev_end

/***********************<<����¼����Ϣ>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
_event( ev_rec_conf_rec_info)
	_body(TConRecState, 1)
_ev_end

/***********************<<���������Ϣ>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
_event( ev_rec_conf_play_info)
	_body(TConfPlayStatus, 1)
_ev_end


/***********************<<����¼������>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_recorder_conf_req)
	_body(TRecConfInfo, 1)
 _ev_end

 /***********************<<����¼��Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_recorder_conf_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end

 /***********************<<��ͣ����¼��>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_pause_conf_req)
	_body(TRecConfRes, 1)
 _ev_end

  /***********************<<��ͣ����¼��Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_pause_conf_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end

 /***********************<<��������¼��>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_resume_conf_req)
	_body(TRecConfRes, 1)
 _ev_end

  /***********************<<��������¼��Ӧ��>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_resume_conf_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end


/***********************<<ֹͣ¼��>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_stop_recorder_req)
	_body(TRecConfRes, 1)
 _ev_end

  /***********************<<ֹͣ¼��Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_stop_recorder_rsp)
	_body(TRecConfRes, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end

 /***********************<<��������>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_start_play_req)
	_body(TRecPlayInfo, 1)
 _ev_end

 /***********************<<����Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_start_play_rsp)
	_body(TRecPlayInfo, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end

 /***********************<<��ͣ����>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_pause_play_req)
	_body(TPlayStatusMdyInfo, 1)
 _ev_end

 /***********************<<��ͣ����Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_pause_play_rsp)
	_body(TPlayStatusMdyInfo, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end

  /***********************<<��������>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_resume_play_req)
	_body(TPlayStatusMdyInfo, 1)
 _ev_end

 /***********************<<Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_resume_play_rsp)
	_body(TPlayStatusMdyInfo, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end

/***********************<<ֹͣ����>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_stop_play_req)
	_body(TPlayStatusMdyInfo, 1)
 _ev_end

  /***********************<<ֹͣ����Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_stop_play_rsp)
	_body(TPlayStatusMdyInfo, 1)
	_body(EmUseReccorderRes, 1)	//���
 _ev_end

/***********************<<����᳡��ʽ>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event( ev_rec_mt_format)
	_body(u16,	1)	//����ID
	_body(u16, 1)	//�᳡ID
 _ev_end

 /***********************<<����᳡��ʽ���>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event( ev_rec_mt_format_rsp)
	_body(TTPRecMtFormat,	1)	//����ID
 _ev_end




#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumsrec )
};
#endif

#endif
