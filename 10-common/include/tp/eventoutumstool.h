#ifndef  _h_eventoutumstool_h__ 
#define  _h_eventoutumstool_h__

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventToolMsg
{
#endif
	_ev_segment( outerumstool )

/***********************<<֪ͨ��Ӳ���汾��Ϣ>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_verInfo_Nty )
	_body(TUmsVersion,	1)	//�汾��Ϣ
_ev_end

/***********************<<��ȡϵͳ��Ϣ����CPU���ڴ�>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
_event(  ev_sysInfo_req )
_ev_end

/***********************<<CPU���ڴ�ϵͳ��Ϣ>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_sysInfo_Nty )
	_body(TToolSysInfo,	1)//�汾��Ϣ
_ev_end

/***********************<<���󿪻�Ļ�������>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
_event(  ev_confCount_req )
_ev_end

/***********************<<֪ͨ���������>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_confCount_Nty )
	_body(u32, 1 )	//��������
_ev_end

/***********************<<����UMS>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
_event(  ev_rebootUms_cmd )
_ev_end

/***********************<<������Ȩʹ������>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
_event(  ev_authCount_req )
_ev_end

/***********************<<��Ȩʹ����Ϣ>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_authCount_Nty )
	_body(u32, 1)	//����
	_body(u32, 1)	//��������
_ev_end

/***********************<<����ǽʹ�����>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
_event(  ev_hduCount_req )
_ev_end

/***********************<<����ǽʹ�����Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_hduCount_Nty )
	_body(TTPBrdUsedInfo,	1)
_ev_end

/***********************<<��Ȩ�ļ�����>>********************	
 *[��Ϣ����]	tool	-->  ums
 *
 */
_event(  ev_licenseOutput_req )
_ev_end

/***********************<<��Ȩ�ļ�����Ӧ��>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_licenseOutput_Ind )
_body(BOOL32, 1)	//�Ƿ�ɹ�
_body(s8, 255)	//����·��+�ļ���
_ev_end



/***********************<<tptools ����>>********************	
 *[��Ϣ����]	tool	-->  ue
 *
 */
_event(  ev_TPtoolLock_Cmd )
_body(BOOL32, 1)	//�Ƿ�����
_body(u32, 1)    	//����ԭ��enum UMS�����ͣ�ֻ����
_ev_end


/***********************<<����TPTOOL����������Tptools��ʱ���ܵ�¼>>********************	
 *[��Ϣ����]	ue	-->  tool
 *
 */
_event(  ev_TPtoolLockReason_Nty )
_body(u32_ip, 1)	//ipΪ ��������Tptool
_body(u32, 1)	    //����ԭ��enum  UMS�����ͣ�ֻ����
_ev_end


#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumstool )
};
#endif


#endif