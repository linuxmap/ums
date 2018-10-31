#ifndef _h_eventoutcnssipreg_h__
#define _h_eventoutcnssipreg_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSIPREGEVENT
{
#endif 

  _ev_segment( outercnssipreg  )

	 //ע��
/***********************<<ע�����ʷ�������ʱ��  >>************************
*[��Ϣ��]
*NULL
*[��Ϣ����]
*  cns	   -> cns
*/
	 _event(  ev_tppRegisterRs_Timer )
	 _ev_end
  
/***********************<<ע�����ʷ���������  >>************************
*[��Ϣ��]
*TTPSipRegistrarCfg  SIP Register����
*[��Ϣ����]
*  cns	   -> cns��cns->cnc,cns->tool
*/
	 _event(  ev_tppRegisterRs_Req )
	 _body( TTPSipRegistrarCfg,1 )
	 _ev_end

/***********************<<ע�����ʷ���������Ļ�Ӧ  >>************************
*[��Ϣ��]
*EmTpConfProtocol  ����Э��
*u32���
*EmTPRegResult ע����
*[��Ϣ����]
*  cns	   -> cncall
*/
	_event(  ev_tppRegisterRs_Rsp )
	_body( EmTpConfProtocol,1 )
	_body( u32,1 )						//���
	_body( EmTPRegResult,1 )			//ע����
	_ev_end
	
/***********************<<ȡ��ע�����ʷ���������  >>************************
*[��Ϣ��]
*NULL
*[��Ϣ����]
*  cns	   -> cns
*/
	_event(  ev_tppUnRegisterRs_Req )
	 _ev_end

/***********************<<ȡ��ע�����ʷ���������Ļ�Ӧ  >>************************
*[��Ϣ��]
*EmTpConfProtocol  ����Э��
*EmTPRegResult ע�����ʷ��������
*EmTpCnsRegUms ע��ums���
*s32
*TTPRegName ע�����ʷ���������
*u32        ȡ��ע��ص��������
*[��Ϣ����]
*  cns	   -> cncall
*/
	_event(  ev_tppUnRegisterRs_Rsp )
	_body( EmTpConfProtocol,1 )
	_body( EmTPRegResult,1 )
	_body( EmTpCnsRegUms,1 )
	_body( s32, 1 )
	_body( TTPRegName,2 )
	_body( u32, 1 )
	_ev_end

	/***********************<< ֪ͨע������Ӧ >>********************** 
*[��Ϣ��]
+BOO	TRUE :�ɹ�  FALSE:ʧ��
+s8[]		�᳡��
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_tpRegisterResult_Nty )
_body( BOOL , 1)
_body( s8, TP_MAX_NAME_LEN+1)
_ev_end



/***********************<< ֪ͨע������Ӧ--ʧ�� >>********************** 
*[��Ϣ��]
+s8[]		�᳡��
*EmTpCnsRegUms ע��UMS���
*TTPRegNameRepeatInfo ע������ظ���Ϣ
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_tpRegisterResultFail_Nty )
//_body( BOOL , 1)
_body( s8, TP_MAX_NAME_LEN+1)
_body( EmTpCnsRegUms, 1)
//_body( s32, 1 )
//_body( TTPRegName,2 )
_body(TTPRegNameRepeatInfo, 1)
_ev_end
  
/***********************<< ��ȡȫ����UMS��CNS��ȫ��ע����Ϣ >>********************** 
*[��Ϣ��]
*EmGetRegInfoType ��ȡע����Ϣ
*[��Ϣ����]
*  cnc	  -> cns
*/
_event( ev_tppGetRegInfo_Req )
_body( EmGetRegInfoType, 1 )
_ev_end

/***********************<< ��ȡȫ����UMS��CNS��ȫ��ע����Ϣ�ظ� >>********************** 
*[��Ϣ��]
*TTPSipRegPackInfo ע�����ʷ�������Ϣ��
*EmGetRegInfoType ��ȡע����Ϣ
*TTPSipRegInfo ��SIPע��������õ�ȫ����Ϣ
*[��Ϣ����]
* cncall->cns, cns	  -> cnc
*/
_event( ev_tppGetRegInfo_Rsp )
_body( TTPSipRegPackInfo, 1 )
_body( EmGetRegInfoType, 1 )
_body( TTPSipRegInfo, 1 )
_ev_end
/***********************<< ֪ͨcncȫ����UMS��CNS��ȫ��ע����Ϣ >>********************** 
*[��Ϣ��]
*TTPSipRegInfo ��SIPע��������õ�ȫ����Ϣ
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_tppGetRegInfo_Nty )
_body( TTPSipRegInfo, 1 )
_ev_end

/***********************<< gk���� >>********************** 
*[��Ϣ��]
* TTPGKCfg ע��GK����
*[��Ϣ����]
*  cns	 <- cnc��cns <- tool
*/
_event( ev_CnsGKReg_Cmd )
_body(TTPGKCfg, 1)
_ev_end

/***********************<< gk���û�Ӧ >>********************** 
*[��Ϣ��]
*TTPGKCfg ע��GK����
*[��Ϣ����]
*  cns	  -> cnc��cns->tool
*/
_event( ev_CnsGKReg_Nty )
//_body(BOOL, 1 )
_body(TTPGKCfg, 1)
_ev_end

/***********************<< gkע���� >>********************** 
*[��Ϣ��]
* TUCSipRegResult UMS,CNS����Э��ջע������Ϣ
*[��Ϣ����]
*  cns	  -> cnc��cns->tool
*/
_event( ev_CnsGKReg_Ret )
_body(TUCSipRegResult, 1)
_ev_end

/***********************<< ȫ�ֵ�ַ������ >>********************** 
*[��Ϣ��]
*NULL
*[��Ϣ����]
*cns -> cns
*/
_event( ev_UnlockRegList_Timer )
_ev_end

/***********************<<  ��ʱ�Զ����� >>********************** 
*[��Ϣ��]
*NULL
*[��Ϣ����]
*cns -> cns
*/
_event( ev_TppAutoMakeCall_Cmd_timer )
_ev_end

/***********************<<  ȡ��GKע������ >>********************** 
*[��Ϣ��]
*NULL
*[��Ϣ����]
*cns -> cns
*/
_event( ev_tppUnGkRegisterRs_Req )
_ev_end

/***********************<<  GKע�ᶨʱ�� >>********************** 
*[��Ϣ��]
*NULL
*[��Ϣ����]
*cns -> cns
*/
_event( ev_tppGkRegisterRs_Timer )
_ev_end

/***********************<<  ע���� >>********************** 
*[��Ϣ��]
*EmTpConfProtocol �������Э��
*u32 ע����
*[��Ϣ����]
*cncall -> cns
*/
_event( ev_tppRegisterHandle_Nty )
_body(EmTpConfProtocol, 1)
_body( u32, 1)
_ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipreg )
};
#endif
#endif //TPP_EVENT_H
