#ifndef _h_eventoutumsconftemplate_h__
#define _h_eventoutumsconftemplate_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumsconftemplate
{
#endif
	
	_ev_segment( outerumsconftemplate )
		
/***********************<<  ������ӻ���ģ�� >>********************	
 *[��Ϣ����]	CMS	-->  UMS   
 *
 */_event(  evtp_AddConfTemplate_req )//����
	_body ( TTPConfTemplateBuf1  , 1  )	
	_ev_end
	
	/***********************<<  ������ӻ���ģ�� >>********************	
 *[��Ϣ����]	CMS	-->  UMS    ����Ϣֱ����OSP���ͣ�������XML�����
 *
 */_event(  evtp_AddConfTemplate_req1 )
	_blob ( u8  , sizeof(TTPConfTemplate)  )				//��ѯ�б��м���
	_ev_end

/***********************<<  ����ɾ������ģ�� >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *����Ϊm_wID
 */_event(  evtp_DelConftemplate_Req )
	_body ( u16  , 1  )
   _ev_end

/***********************<<  ������»���ģ�� >>********************	
 *[��Ϣ����]	CMS	-->  UMS  
 *��m_wIDΪ����
 */
 _event(  evtp_Updateconftemplate_Req ) //����
	_body ( TTPConfTemplateBuf1  , 1  )
	_ev_end
	
	/***********************<<  ������»���ģ�� >>********************	
 *[��Ϣ����]	CMS	-->  UMS   ����Ϣֱ����OSP���ͣ�������XML�����
 *��m_wIDΪ����
 */_event(  evtp_Updateconftemplate_Req1 )
	_blob ( u8  , sizeof(TTPConfTemplate)  )
	_ev_end

/***********************<<  ����ģ�������� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *��ӣ�ɾ�������¶��Է��ش���Ϣ������ԭ���ڽṹ�ж���
 */_event(  evpt_OperatorConfTemplate_Ret )		
	_body ( TOprConfTmpResult  , 1  )
   _ev_end


/***********************<<  UMS֪ͨCMS����ģ���б� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *��¼�������ʱ�����Դ���Ϣ���������ģ���б�
 */_event(  evtp_AddConftemplate_Notify )	//����	
	_body ( TTPConfTemplateBuf1  , 1  )
	_ev_end
	
	/***********************<<  UMS֪ͨCMS����ģ���б� >>********************	
 *[��Ϣ����]	UMS	-->  CMS   ����Ϣֱ����OSP���ͣ�������XML�����
 *��¼�������ʱ�����Դ���Ϣ���������ģ���б�
 */_event(  evtp_AddConftemplate_Notify1 )		
	_blob ( u8  , sizeof(TTPConfTemplate)  )
	_body ( BOOL32 , 1) //Ϊ�������ˢ������Ƿ�Ϊ���һ����־λ
	_ev_end

/***********************<<  UMS֪ͨCMSɾ����ģ���б� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */_event(  evtp_Delconftemplate_Notify )
	_body ( TDelRefreshConfTemplate  , 1  )
   _ev_end

/***********************<<  UMS֪ͨCMS�޸ĵ�ģ���б� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */_event(  evtp_Updateconftemplate_Notify ) //����
	_body ( TTPConfTemplateBuf1  , 1  )
   _ev_end

   /***********************<<  UMS֪ͨCMS�޸ĵ�ģ���б� >>********************	
 *[��Ϣ����]	UMS	-->  CMS  ����Ϣֱ����OSP���ͣ�������XML�����
 *
 */_event(  evtp_Updateconftemplate_Notify1 )
	_blob ( u8  , sizeof(TTPConfTemplate)  )
	_body ( BOOL32 , 1)
   _ev_end


/***********************<<����ģ���ļ�>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
_event(  ev_uploadConftemp_req )
	_body(s8, TP_UPLOAD_FILE_NAME_LENGTH)	//ģ���ļ���  ��󳤶�Ϊ TP_UPLOAD_FILE_NAME_LENGTH
_ev_end


/***********************<<����ģ���ļ����>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_uploadConftemp_rsq )
	_body(BOOL32, 1 )
_ev_end


/***********************<<����ģ���ļ�����>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
 _event(  ev_downloadConftemp_req )
_ev_end


/***********************<<����ģ���ļ�Ӧ��>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
 _event(  ev_downloadConftemp_rsq  )
	_body(s8, TP_UPLOAD_FILE_NAME_LENGTH)	//ģ���ļ���  ��󳤶�Ϊ TP_UPLOAD_FILE_NAME_LENGTH
_ev_end

/***********************<<ɾ��ȫ��ģ����Ϣ>>********************	
 *[��Ϣ����]	umc	-->  ums
 *
 */
 _event(  ev_del_all_conftemp_req  )
_ev_end

/***********************<<ɾ��ȫ��ģ����ϢӦ��>>********************	
 *[��Ϣ����]	ums	-->  umc
 *
 */
 _event(  ev_del_all_conftemp_rsp  )
	_body ( TOprConfTmpResult  , 1  )
 _ev_end



 


#ifndef _MakeTpEventDescription_
		_ev_segment_end(outerumsconftemplate)
};
#endif


#endif // _h_eventoutumsconftemplate_h__
