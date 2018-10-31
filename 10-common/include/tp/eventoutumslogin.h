#ifndef _h_eventoutumslogin_h__
#define _h_eventoutumslogin_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumslogin
{
#endif
	
	_ev_segment( outerumslogin )
		
/***********************<<   >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *��¼���󣬲���ΪCLoginReques������Ϣֱ����OSP���ͣ�������XML�����
 */
_event(  ev_UMSLoginReq )
	_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *��¼����
 */
_event(  ev_UMSLoginRet )
	_body(TLoginRet,	1)
	_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *����û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
 */
_event(  ev_UMSAddUserReq )
	_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *��ӷ���
 */
_event(  ev_UMSAddUserRet )
	_body(EmTpRet,	1)	//�������
	_body(u16,	1)		//������룬������󣬴˴�Ϊ����ԭ��
	_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *ɾ���û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
 */
_event(  ev_UMSDelUserReq )
	_ev_end	

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *ɾ������
 */
_event(  ev_UMSDelUserRet )
	_body(EmTpRet,	1)	//�������
	_body(u16,	1)	//������룬������󣬴˴�Ϊ����ԭ��
	_ev_end

/***********************<<   >>********************	
 *[��Ϣ����]	CMS	-->  UMS
 *�޸��û����룬����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
 */
_event(  ev_UMSChangePWDReq )
	_ev_end	

/***********************<<   >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *�޸ķ���
 */
_event(  ev_UMSChangePWDRet )
	_body(EmTpRet,	1)	//�������
	_body(u16,	1)	//������룬������󣬴˴�Ϊ����ԭ��
	_ev_end	

/***********************<< UMS֪ͨCMS����һ���û���¼  >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
 */
_event(  ev_UmsAddUser_Notify )
_ev_end	
	
/***********************<< UMS֪ͨCMS����һ���û��˳���¼  >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
 */
_event(  ev_UmsDelUser_Notify )
_ev_end	
	
/***********************<< UMS֪ͨCMS���޸��û�  >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
 */
_event(  ev_UmsUpdateUser_Notify )
_ev_end	


/***********************<< UMS֪ͨCMS���û��������ط���¼  >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */
_event(  ev_UmsLoginByOther_Notify )
_body(u32_ip, 1)
_ev_end	


#ifndef _MakeTpEventDescription_
		_ev_segment_end(outerumslogin)
};
#endif




#endif // _h_eventoutumslogin_h__
