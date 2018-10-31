#ifndef _h_eventoutumsboard_h__
#define _h_eventoutumsboard_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmEventBoardMsg
{
#endif

	_ev_segment( outerumsboard )

/***********************<<֪ͨ������Ϣ>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_cardInfo_Nty )
	_body(TTPBrdInfo, 1)  //������Ϣ
	_body(s8, TP_BOARD_VERSION_LEN)  //����Ӳ���汾��
	_body(s8, TP_BOARD_VERSION_LEN)  //��������汾��
_ev_end

/***********************<<�����޸ĵ���>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event(  ev_cardModify_req )
	_body(TTPBrdCfg,	1)	//
_ev_end

/***********************<<�����޸���Ӧ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event(  ev_cardModify_rsp )
	_body(TTPBrdCfg,	1)	
	_body(EmTpBoardRet, 1)  //�������
_ev_end

/***********************<<����ɾ������>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event(  ev_cardDel_req )
	_body(TTPBrdCfg,	1)	//
_ev_end

/***********************<<����ɾ����Ӧ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event(  ev_cardDel_rsp )
	_body(TTPBrdCfg,	1)	//
	_body(EmTpBoardRet, 1)  //�������
_ev_end

/***********************<<������ӵ���>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event(  ev_cardAdd_req )
	_body(TTPBrdCfg,	1)	//
_ev_end

/***********************<<���������Ӧ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event(  ev_cardAdd_rsp )
	_body(TTPBrdCfg,	1)	//
	_body(EmTpBoardRet, 1)
_ev_end

// **********************<<������ӵ���ģʽ>>********************	
//  *[��Ϣ����]	tool  -->  ums
//  *
//  _event(  ev_cardModeAdd_req )
// 	_body(TTPBrdMdlInfo,	1)	//
// _ev_end
// 
// **********************<<����ģʽ�����Ӧ>>********************	
//  *[��Ϣ����]	ums  -->  tool
//  *
//  _event(  ev_cardModeAdd_rsp )
// 	_body(TTPBrdMdlInfo,	1)	//
// 	_body(EmTpBoardRet, 1)
// _ev_end

/***********************<<����ɾ������ģʽ>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event(  ev_cardModeDel_req )
	_body(TTPBrdMdlInfo,	1)	//
_ev_end

/***********************<<����ģʽɾ����Ӧ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event(  ev_cardModeDel_rsp )
	_body(TTPBrdMdlInfo,	1)	//
	_body(EmTpBoardRet, 1)
_ev_end

/***********************<<�����޸ĵ���ģʽ>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event(  ev_cardModeModify_req )
	_body(TTPBrdMdlInfo,	1)	//
_ev_end

/***********************<<����ģʽ�޸���Ӧ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event(  ev_cardModeModify_rsp )
	_body(TTPBrdMdlInfo,	1)	//
	_body(EmTpBoardRet, 1)
_ev_end

/***********************<<������������>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event( ev_card_reboot_req )
	_body(TTPBrdPos, 1)       
_ev_end

// **********************<<������ռ������>>********************	
//  *[��Ϣ����]	tool  -->  ums
//  *
//  _event( ev_card_audiomix_used_req )     
// _ev_end
// 
// **********************<<��ͳ����ϳ�ռ������>>********************	
//  *[��Ϣ����]	tool  -->  ums
//  *
//  _event( ev_card_vmp_used_req )     
// _ev_end
// 
// **********************<<��������ռ������>>********************	
//  *[��Ϣ����]	tool  -->  ums
//  *
//  _event( ev_card_bas_used_req )      
// _ev_end

/***********************<<����ռ���������>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event( ev_card_eqp_used_req )  
	_body(EMEqpType, 1)    //�ɵ�����em_audmix_mdl //em_bas_mdl //em_vmp_mdl //em_vmp_tp_mdl //em_audbas_mdl
_ev_end                    //��em_max_mdl��һ�η����������������ʹ�����

/***********************<<ռ�����֪ͨ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event( ev_card_used_nty )
	_body(TTPBrdUsedInfo, 1)       
_ev_end

/***********************<<����������Դռ�����֪ͨ>>********************	
 *[��Ϣ����]	ums  -->  umc
 *
 */
_event( ev_conf_bas_used_nty )
	_body(TTPBrdUsedInfo, 1)   
_ev_end

/***********************<<������������>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event( ev_card_upgrade_req )
	_body(TTPBrdUpGrade, 1)       
_ev_end

/***********************<<�����������>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event( ev_card_upgrade_res )
	_body(u8, 1)  //���Ӳ��
	_body(u8, 1)  //���Ӳۺ�
	_body(BOOL32, 1)       
_ev_end



/***********************<<����telnet��ftp��������>>********************	
 *[��Ϣ����]	tool  -->  ums
 *
 */
_event( ev_card_switchtelnetftp_req )
_body(TPBoardSwitch, 1)  
_ev_end
/***********************<<����telnet��ftp���ؽ��>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event( ev_card_switchtelnetftp_rsp )
_body(TPBoardSwitch, 1)  
_body(EmBoardSwitchRes,1)
_ev_end
/***********************<<����telnet����֪ͨ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event( ev_card_switchtelnet_ntf )
_body(TPBoardSwitch, 1)  
_ev_end
/***********************<<����ftp����֪ͨ>>********************	
 *[��Ϣ����]	ums  -->  tool
 *
 */
_event( ev_card_switchftp_ntf )
_body(TPBoardSwitch, 1)  
_ev_end


#ifndef _MakeTpEventDescription_
	_ev_segment_end( outerumsboard )
};
#endif

#endif  //_h_eventoutumsboard_h__
