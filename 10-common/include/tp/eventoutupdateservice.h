#ifndef _h_eventoutupdateservice_h__
#define _h_eventoutupdateservice_h__


#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emtpouterupdateservice
{
#endif
	_ev_segment( tpupdateservice )

	/***********************<<Զ��������������������¼���� >>********************** 
	*[��Ϣ��]
	*	TTPLocalDevVerInfo Զ�˱��ذ汾��Ϣ
	*[��Ϣ����]
	*  Զ�� -> updateserver
	*/
	_event( ev_CnLogin_UpdateSer_Req )
		_body( TTPLocalDevVerInfo, 1 )
	_ev_end

	/***********************<<Զ���յ����������������¼�Ļظ���Ϣ >>********************** 
	*[��Ϣ��]
	*EmTPCnLoginUpdateRet ��¼�Ƿ�ɹ�
	*[��Ϣ����]
	*  Զ�� <- updateserver
	*/
	_event( ev_CnLogin_UpdateSer_Rsp )
	_body(EmTPCnLoginUpdateRet, 1)
	_ev_end

	/***********************<<Զ������������������ >>********************** 
	*[��Ϣ��]
	* EmTPUpdateSysFileType  �����豸����
	*TTPLocalDevVerInfo      Զ�˰汾��Ϣ
	*[��Ϣ����]
	*  Զ�� -> updateserver
	*/
	_event( ev_UpdateSystem_Req )
		_body(TTPLocalDevVerInfo, 1)
	_ev_end

	/***********************<<Զ���յ��������������͵�������Ӧ��Ϣ >>********************** 
	*[��Ϣ��]
	*TTPDevVerInfo       Զ�� �汾��Ϣ
	*[��Ϣ����]
	*   Զ�� <- updateserver
	*/
	_event( ev_UpdateSystem_Rsp )
	_body(TTPDevVerInfo ,1)
	_ev_end

	/***********************<<Զ���յ�����������������֪ͨ������Ϣ >>********************** 
	*[��Ϣ��]
	*TTPDevVerInfo  Զ�� �汾��Ϣ
	*[��Ϣ����]
	*   Զ�� <- updateserver
	*/
	_event( ev_UpdateSystem_Nty )
		_body(TTPDevVerInfo ,1)
	_ev_end

	/***********************<<����reload ���ر��������ļ� >>********************** 
	*[��Ϣ��]
	*TTPDevVerInfo  Զ�� �汾��Ϣ
	*[��Ϣ����]
	*   Զ�� <- updateserver
	*/
	_event( ev_ReloadCfg_Req )
	_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(tpupdateservice)
};
#endif


#endif // _h_eventoutupdateservice_h__
