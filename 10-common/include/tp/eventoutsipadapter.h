#ifndef _h_eventoutsipadapter_h__
#define _h_eventoutsipadapter_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumssipadaper
{
#endif
	
	_ev_segment( tpumswithumssipadapter )
		
 
/***********************<<  ums������� >>********************/
_event(  ev_MakeCall_Req )
	_body ( TUmsHandle  , 1  )	
	_body(TMakeCallPara, 1)
_ev_end

/***********************<<  ���з������Э�� >>********************/
_event(  ev_MakeChan_Req )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_body(BOOL32, 1) //�Ƿ���˫��
_ev_end

/***********************<<  umsӦ����� >>*********************/
_event(  ev_AnwserCall_IND )
	_body ( TUmsHandle  , 1  )	
	_body(BOOL32, 1)
	_body(EmCnsCallReason, 1)
	_body(TMakeCallPara, 1)
_ev_end
 
/***********************<<  ums���¼�����ϯͨ�� >>*********************/
_event(  evtp_cascade_OpenChairChan_cmd )
_body ( TUmsHandle  , 1  )	
_body(TCascadeOpenChanCmd, 1)
_ev_end

/***********************<<  ums���¼�����ϯӦ�� >>*********************/
_event(  evtp_cascade_OpenChairChan_ack )
_body ( TUmsHandle  , 1  )	
_body(TCascadeOpenChanAck, 1)
_ev_end


 /***********************<<  ums�ҶϺ��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_HungUp_Req )
_body ( TUmsHandle  , 1  )	
_body ( EmCnsCallReason  , 1  )	
 _ev_end

 /***********************<<  ums����ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_Register_Req )
_body ( TUmsHandle  , 1  )	
_body ( TUmsSipRegCfg  , 1  )	
_body ( u16  , 1  )	
_body ( TTPAlias  , TP_CONFTEMPGROUP_MAXNUM  )		
 _ev_end

  /***********************<<  ums����gkע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_gk_Register_Req )
_body ( TUmsHandle  , 1  )	
_body ( TRegCfg  , 1  )	
_body ( u16  , 1  )		
 _ev_end

   /***********************<<  ע������Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_register_handle_info )
_body ( TUmsHandle  , 1  )	
_body ( EmTpRegType  , 1  )		
 _ev_end

 /***********************<<  ע���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */
 _event(  evtp_ums_reg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TCnsRegRetResult  , 1  )
 _ev_end	


 /***********************<<  ums����ȡ��ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_UnRegister_Req )
_body ( TUmsHandle  , 1  )	
_body (EmTpRegType, 1 )
 _ev_end

 /***********************<<  ����ɾ��ע���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_unreg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TUCSipRegResult  , 1  )
   _ev_end	

 /***********************<<  323ע��ʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_323_unreg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TUCSipRegResult  , 1  )
   _ev_end	

/***********************<<  ���е��� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_UmsConfIncoming )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_ev_end

/***********************<<  ����������Ϣ��һ���� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	sipadapter	--> call
 *
 */
_event(  evtp_UmsConfCreateMeeting )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_body ( TTPConfTemplateBuf1  , 1  )
_ev_end

/***********************<<   ����������Ϣ�ڶ����� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	sipadapter	--> call
 *
 */
_event(  evtp_UmsConfCreateMeeting1 )
_body ( TUmsHandle  , 1  )
_body ( TTPConfTemplateBuf2  , 1  )
_ev_end

/***********************<<   ����������Ϣcall��Ϻ󣬷���service >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_UmsConfCreateMeetingMsg )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
//_body ( TConfTemplateLocal  , 1  ) // ������Ϣ���ڲ���Ϣ������Ҫ����xml,
                                    //��Ϣ���ݰ�����TConfTemplateLocal������TConfTemplateLocalδxml���������±��벻��������ע�͵�
_ev_end

/***********************<<  �᳡���гɹ� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsCallConnect )
_body ( TUmsHandle  , 1  )		
_body ( TUmsCallInfo, 1)
_ev_end

/***********************<<  ����Ҷ� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsCallDisConnect )
_body ( TUmsHandle  , 1  )	
_body ( EmCnsCallReason  , 1  )	
_ev_end


/***********************<<  ͨ���� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsChannelConnect )
_body ( TUmsHandle  , 1  )	
_body ( TUmsNodeCapset  , 1  )	
_ev_end

/***********************<<  ͨ���ر� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsChannelDisConnect )
_body ( TUmsHandle  , 1  )	
_ev_end


 /***********************<<  ͨ����Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_ChanBegin )
_ev_end


/***********************<<  �ؼ�֡���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_AskKeyFrame )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  CNS֪ͨUms�᳡������ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CnsSpeaker_Notify )
_body ( TUmsHandle  , 1  )
_body(u8, 1)	
_ev_end

/***********************<<   >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Chan_FlowCtrol )
_body ( TUmsHandle  , 1  )	
_body( u16 , 1)//����
_ev_end


/***********************<<  ֪ͨͨ��������  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_ChanSeeLocal_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end



/***********************<<  ֪ͨͨ��ȡ��������  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_ChanSeeLocalCancel_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ѡ�����  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_ViewObj_Ind )
_body ( TUmsHandle  , 1  )	
_body( TChanViewRes, 1)	
_ev_end


/***********************<<  ȡ��ѡ�����  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_UndoViewObj_Ind )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)	//����	
_ev_end



 /***********************<<  ˫����Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_DualBegin )
_ev_end


/***********************<<  ��˫��ͨ�� >>********************/
_event(  ev_OpenDualChan_Req )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  ��˫��ͨ�� >>********************/
_event(  ev_OpenDualChan_Incoming )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ˫��ͨ����Ӧ�� >>********************/
_event(  ev_MakeSendDual_Answer )
_body ( TUmsHandle  , 1  )
_body ( BOOL32, 1)	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  ˫��ͨ���� >>********************/
_event(  ev_OpenDualChan_Connect )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  ˫��ͨ���Ͽ�>********************/
_event(  ev_OpenDualChan_Failed )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ֹͣ˫�� >>********************/
_event(  ev_DualChan_DisConnect )
_body ( TUmsHandle  , 1  )
_body ( EmTPChannelReason, 1 )	
_ev_end

/************************<<  ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_RequestDualStream_cmd  )
_body ( TUmsHandle  , 1  )	
_body( TEpKeyEx, 1)	
_ev_end

/************************<<  ����˫����� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_RequestDualStream_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TDualRequestAckTr, 1)	
_ev_end


/************************<<  ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_cascade_OpenDualChan_Cmd  )
_body ( TUmsHandle  , 1  )	
_body(TDualInfoTr, 1)	
_ev_end


/************************<<  ����˫��Ӧ�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_cascade_OpenDualChan_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TDualInfoAckTr, 1)	
_ev_end

/************************<<  ֹͣ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopRcvDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end

/************************<<  ����˫���ؼ�֡ >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_DualFastUpdate_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( BOOL32  , 1  )	
_ev_end

/************************<<  ��ʼ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StartRcvDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( TEpKeyEx  , 1  )		//���ͷ�
_ev_end


/************************<<  ֹͣ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopSendDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( TEpKey  , 1  )	
_ev_end


/************************<<  ˫��Դ����֪ͨ >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_SrcDualName_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TTPAlias, 1)
_body ( TEpKey  , 1  )	
_ev_end


/***********************<<������˫������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfStartDual_Cmd )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end

/***********************<<������˫������Ӧ��  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfStartDual_Ind )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_body ( EmTPDualReason , 1 )
_ev_end

/***********************<<������ͣ˫������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfStopDual_Cmd )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end

/***********************<<������˫������Ӧ��  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfStopDual_Ind )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_body ( EmTPDualReason , 1 )
_ev_end

/***********************<<������˫���᳡�㲥֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfDualEp_Nty )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end




 /***********************<<  ��ѯ��Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_PollBegin )
_ev_end

/************************<<  ��ǰ��ѯĿ������� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_PollDstName_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TPollInfoNtf, 1)
_ev_end

/***********************<<  �ϼ������¼���ʼ��ѯ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_StartPoll_cmd )
_body ( TUmsHandle  , 1  )	
_body( TPollCmdTr, 1)	
_ev_end
		
/***********************<<  �¼�Ӧ���ϼ���ʼ��ѯ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_StartPoll_ack )
_body ( TUmsHandle  , 1  )	
_body( TPollAckTr, 1)	
_ev_end
/***********************<<  �¼�֪ͨ�ϼ���ѯ���任 >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_Poll_NodeChange )
_body ( TUmsHandle  , 1  )	
_body( TEpKey, 1)	
_ev_end
/***********************<<  ֪ͨ��ѯ���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *	UMS -> UMS
 */
_event( evtp_Conf_Poll_End )	
_body ( TUmsHandle  , 1  )	
_body ( BOOL32	 , 1  )		//�Ƿ���ͣ
_ev_end

/***********************<<  ��ѯ�ؼ�֡���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_Poll_AskKeyFrame )	
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ������ѯ  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StartPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_ev_end


/***********************<<  ������ѯ���  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StartPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( EmTPPollResult, 1)	//���	
_ev_end

/***********************<<  ֹͣ��ѯ  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ֹͣ��ѯ���  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( EmTPPollResult, 1)	//���	
_ev_end

/***********************<<  ��ͣ��ѯ  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_SuspendPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_body ( BOOL32, 1 )
_ev_end

/***********************<<  ��ͣ��ѯ���  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_SuspendPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( EmTPPollResult, 1)	//���	
_ev_end

/***********************<<  ���� ֪ͨ�¼� �µ���ѯĿ��  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_CasecadePollEp_Req	 )
_body ( TUmsHandle  , 1  )	
_body( TCasecadePollEpReq, 1) 	
_ev_end

/***********************<<  ���� ��Ӧ�ϼ� ��ѯĿ��������  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_CasecadePollEp_Rsp	 )
_body ( TUmsHandle  , 1  )	
_body( TCasecadePollEpRsp, 1) 	
_ev_end


/***********************<<  ֪ͨCNS��ǰ��ѯ״̬  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_PollStatus_Notif	 )
_body ( TUmsHandle  , 1  )	
_body( TTpPollStat, 1)//�Ƿ�����ѯ	
_ev_end


/***********************<<  ѡ��  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_ViewObj_Req )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)	
_ev_end





/***********************<<  ȡ��ѡ��  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_UndoViewObj_Req )
_body ( TUmsHandle  , 1  )	
_ev_end



/***********************<< ������ѯ�б�  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsUpdateConfTurnlist_Nty )
_body (TUmsHandle, 1)
_body ( TTpPollListNtfy , 1 )	
_ev_end

/***********************<< ������ѯ�б��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsUpdateConfTurnlist_Ind )
_body (TUmsHandle, 1)
_body ( TTpPollListInd , 1 )	
_ev_end


 /***********************<<  ������Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_UmsDiscussBegin )
_ev_end

/***********************<< ���������ۿ���  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfAMixUpdate_Cmd )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

  /***********************<<  �ϼ�UMS�����һ·��Ƶͨ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �ϼ�UMS - �¼�UMS 
 *
 */
 _event(  evtp_OpenVidChan_Cmd )
 	_body (TUmsHandle, 1)
 	_body(TVidChanCmd, 1)
 _ev_end


  /***********************<<  �¼��ظ��ϼ�����Ƶͨ����ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �¼�UMS - �ϼ�UMS 
 *
 */
 _event(  evtp_OpenVidChan_Ack )
 	_body (TUmsHandle, 1)
 	_body(TVidChanAck, 1)
 _ev_end

   /***********************<<  ֪ͨ�¼�ֹͣ��Ƶͨ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �¼�UMS - �ϼ�UMS 
 *
 */
 _event(  evtp_CloseVidChan_Cmd )
 	_body (TUmsHandle, 1)
 	_body(u16, 1)
	_body(u32, 1) // need add
 _ev_end

 /***********************<<  ֪ͨCNS��������״̬�ͱ��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS->CNS 
 *
 */
_event(  evtp_UmsDiscussScreenStat_Notify )
	_body (TUmsHandle, 1)
	_body ( TDiscussCasecadeNtfy  , 1  )	
_ev_end

 /***********************<<  ��������ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS->CNS 
 *
 */
_event(  evtp_UmsDiscussFastUpdate_Req )
	_body (TUmsHandle, 1)
	_body (TDisAskKeyFrame  , 1  )	
_ev_end


/***********************<< ���ۻ᳡��������ӡ�ɾ����  >>********************	
*[��Ϣ����]	CNC - UMS
*
*/
_event(  ev_UmsAudMixDisListOpr_Cmd )
_body (TUmsHandle, 1)
_body (TDiscussListOpr , 1 )	
_ev_end

/***********************<< ���ۻ᳡��������ӡ�ɾ����  >>********************	
*[��Ϣ����]	CNC - UMS
*
*/
_event(  ev_UmsAudMixDisListOpr_Ind )
_body (TUmsHandle, 1)
_body (TDiscussListOpr , 1 )	
_ev_end

/***********************<< ���������ۿ�����Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfAMixUpdate_Ind )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

/***********************<< ���������ۿ���֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfAMixUpdate_Nty )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

/***********************<< �������������͹ر�  >>********************	
*[��Ϣ����]	cns	-->  ums
*
*/
_event( ev_UmsConfAMixVacSwitch)
_body(TUmsHandle, 1)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<< �������������͹رջ�Ӧ  >>********************	
*[��Ϣ����]	cns	-->  ums
*
*/

_event( ev_UmsConfAMixVacSwitchInd)
_body(TUmsHandle, 1)
_body(TConfAuxMixVacOpr, 1)
_ev_end 

 /***********************<<  �������������Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_UmsEapuBegin )
_ev_end

/***********************<< �᳡��������״̬֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsAudMixStatus_Nty )
_body (TUmsHandle, 1)
_body ( TAudMixStat , 1 )	
_ev_end

 /***********************<<  ֪ͨ�¼���CNS���»᳡�ķ�����ϯ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS->CNS 
 *
 */
_event(  evtp_UmsCnsSpeakerIndxAdjust_Notify )
	_body (TUmsHandle, 1)
	_body (TCnsSpeakerAdjust  , 1  )	
_ev_end

/***********************<<  �ϼ������һ·��Ƶͨ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS - �¼�UMS 
 *
 */
 _event(  evtp_OpenAudChan_Cmd )
	_body (TUmsHandle, 1)
	_body(TAudChanCmd, 1)
 _ev_end

   /***********************<<  �¼��ظ��ϼ�����Ƶͨ����ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �¼�UMS - �ϼ�UMS 
 *
 */
 _event(  evtp_OpenAudChan_Ack )
 	_body (TUmsHandle, 1)
 	_body(TAudChanAck, 1)
 _ev_end

 /***********************<<  ��Ҫ֪ͨCNS�Ļ���״̬��Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_CnsConfStatBegin )
_ev_end

//////////////////////////////////////////////////////////////////////////
//֪ͨUI��״̬��Ϣ����Ϊ��Sip���͸�CNS


/***********************<< �������л�������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfApplySpeaker_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )	
_ev_end

/***********************<< �������л������˻�Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfApplySpeaker_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( EmTpApplySpeakerRet , 1 )
_ev_end

/***********************<< �������л�������֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfApplySpeaker_Nty )
_body ( TUmsHandle, 1 )
_body ( TConfEpID , 1 )	
_ev_end

/***********************<< ���������Զ������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfMute_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<< ���������Զ��������Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfMute_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<< ���������Զ������֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfMute_Nty )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<< ���������Զ�˾���  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfQuiet_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<< ���������Զ�˾�����Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfQuiet_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<<���������Զ�˾���֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfQuiet_Nty )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<<��������ͨ�����������б��в����ڵĻ᳡  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsInviteCnsByAlias_Cmd )
	_body (TUmsHandle, 1)
	_body ( TTpCallAddr , 1 )
_ev_end

/***********************<<��������ͨ�����������б��в����ڵĻ᳡��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsInviteCnsByAlias_Ind )
	_body (TUmsHandle, 1)
	_body ( TTpCallAddr , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<��������ͨ�����ֺ����б��д��ڵĲ����߻᳡  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsInviteCnsByEpId_Cmd )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
_ev_end

/***********************<<��������ͨ�����ֺ����б��д��ڵĲ����߻᳡��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsInviteCnsByEpId_Ind )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<���Ҷ�ָ���᳡  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsHangupCns_Cmd )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
_ev_end

/***********************<<���Ҷ�ָ���᳡��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsHangupCns_Ind )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<�Ҷϻ���  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsHangupConf_Cmd )
	_body (TUmsHandle, 1)
_ev_end

/***********************<< ֪ͨ��ϯ������Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsChairConfInfo_Nty )
	_body (TUmsHandle, 1)
	_body ( TChairConfInfo , 1 )	
_ev_end

/***********************<< ֪ͨ����ԭ����ʾ ͨ��  >>********************	
*[��Ϣ����]	UMS	-->  CNS -> cnc
*
*/
_event(  ev_UmsCommonReasonToUI_Ind )
	_body (TUmsHandle, 1)
	_body ( TTPUmsReasonInd , 1 )	
_ev_end


_event( ev_SipAdapter_GetVid_Begin )
_ev_end

/***********************<<  �ϼ������¼�����Ƶͼ�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_cascade_GetVid_cmd )
_body ( TUmsHandle  , 1  )	
_body( TViewCmdTr, 1)	
_ev_end
		
/***********************<<  �ϼ������¼�����Ƶͼ��Ӧ�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_cascade_GetVid_ack )
_body ( TUmsHandle  , 1  )	
_body( TViewAckTr, 1)	
_ev_end

/***********************<<  �ϼ�ֹͣ�¼���ͼ�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_cascade_StopGetVid_cmd )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)		//���
_ev_end




 /***********************<<  ������Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_OtherConfBegin )
_ev_end

/***********************<<��ȡȫ����UMS��CNS��ȫ��ע����Ϣ  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsGetRegInfo_Req )
	_body ( TUmsHandle, 1)
	_body ( TUmsSipRegCfg, 1)
	_body ( EmGetRegInfoType , 1 )
	_body ( u32,	1)	//SIP ע����
	_body ( u32,	1)	//GK ע����
_ev_end

/***********************<< ��ȡȫ����CNS��ȫ��ע����Ϣ�ظ�  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_Rsp )
	_body ( TUmsHandle, 1)
	_body ( TTPSipRegPackInfo , 1 )
	_body ( EmGetRegInfoType , 1 )
	_body ( TTPSipRegInfo , 1 )
_ev_end

/***********************<< ȫ�ֵ�ַ��UMSע����Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_UmsRspEx )
_body ( TUmsHandle, 1)
_body ( TRegPackInfoEx, 1)
_body ( TUmsRegPackEx, 1)
_ev_end

/***********************<< ȫ�ֵ�ַ��CNSע����Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_CnsRspEx )
_body ( TUmsHandle, 1)
_body ( TRegPackInfoEx, 1)
_body ( TCnsRegPackEx, 1)
_ev_end

/***********************<< MT ע����Ϣ  >>********************	
*
*/
_event(  ev_UmsGetGkRegInfo_MtRsp )
_body ( TUmsHandle, 1)
_body ( EmGetRegInfoType, 1)
_body ( TTPMtRegInfo, 1)
_ev_end

/***********************<< MCU ע����Ϣ  >>********************	
*
*/
_event(  ev_UmsGetGkRegInfo_McuRsp )
_body ( TUmsHandle, 1)
_body ( EmGetRegInfoType, 1)
_body ( TTPMcuRegInfo, 1)
_ev_end


/***********************<<  �¼����ϼ����»����� >>********************	 
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event(  evtp_Conf_EpCallInfo_Update )
_body ( TUmsHandle  , 1  )	
_body ( TConfNodeCallUpdateTrList, 1 )
_ev_end

/***********************<<  �¼����ϼ����»����� >>********************	 
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event(  evtp_Conf_EpChanInfo_Update )
_body ( TUmsHandle  , 1  )	
_body ( TConfNodeChanUpdateTrList, 1 )
_ev_end

/***********************<<  �¼����ϼ�ɾ�������� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event(  evtp_Conf_EpInfo_Del )
_body ( TUmsHandle  , 1  )	
_body( TConfNodeDelTrList, 1)
_ev_end

/***********************<<  �ϼ����¼�֪ͨ���������� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_YouAreSeeing_Ind )
_body ( TUmsHandle  , 1  )	
_body( TSpeakerCapTr, 1)
_ev_end

/***********************<<  ֪ͨ�ն��ڶ������� H323 >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����] �ն� - > UMS	
 *
 */
_event( evtpH323_Conf_MultipleConference_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  �����ն��б� H323 >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����] �ն� - > UMS	
 *
 */
_event( evtpH323_Conf_TerminalListRequest )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums֪ͨCNS��ϯ��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_IsChair_Notify )
_body ( TUmsHandle  , 1  )	
_body( BOOL32, 1)
_ev_end

/***********************<<  Ums֪ͨ��ϯ�л᳡��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_LeftConf_Notify )
_body ( TUmsHandle  , 1  )	
_body( TConfEpIDInfo, 1)
_ev_end

/***********************<<  Ums֪ͨ��ϯ�л᳡��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_JoinConf_Notify )
_body ( TUmsHandle  , 1  )	
_body( TConfEpIDInfo, 1)
_ev_end

/***********************<<  Ums֪ͨCNS���������  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_MultConf_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums֪ͨCNS�뿪������  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CancelMultConf_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums֪ͨCNS����״̬ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_StatusInfo_Notify )
_body ( TUmsHandle  , 1  )	
_body( TTPConfInfoNtfy, 1)
_ev_end


/***********************<<  Ums֪ͨUms�᳡������ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CnsSpeakerCascad_Notify )
_body ( TUmsHandle  , 1  )	
_body(TCnsSpeakerAdjust, 1)
_ev_end

/***********************<<  ֪ͨԶ������ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_MuteRemoteEp_Cmd )
_body ( TUmsHandle  , 1  )	
_body(TMuteRmtEpCmd, 1)
_ev_end


/***********************<<  Զ������ָʾ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_MuteRemoteEp_Ind )
_body ( TUmsHandle  , 1  )	
_body(TMuteRmtEpInd, 1)
_ev_end


/***********************<<  ֪ͨԶ�˾��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_QuietRemoteEp_Cmd )
_body ( TUmsHandle  , 1  )	
_body(TQuietRmtEpCmd, 1)
_ev_end


/***********************<<  Զ�˾���ָʾ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_QuietRemoteEp_Ind )
_body ( TUmsHandle  , 1  )	
_body(TQuietRmtEpInd, 1)
_ev_end

/***********************<<  ����δ���߻᳡ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CallExistEPTr_cmd )
_body ( TUmsHandle  , 1  )	
_body(u16, 1)	//epID
_body(TTPAlias, 1)
_ev_end

/***********************<<  �Ҷϻ᳡ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_DropEPTr_cmd )
_body ( TUmsHandle  , 1  )	
_body(TDropEpCmd, 1)	
_ev_end

/************************<<  ����ǽ��� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_TvMonitor_Cmd  )
_body ( TUmsHandle  , 1  )	
_body( TTvMonitorCmdTr, 1)
_ev_end

/************************<<  ����ǽ��� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_TvMonitor_Ind  )
_body ( TUmsHandle  , 1  )	
_body( TTvMonitorIndTr, 1)
_ev_end

/************************<<  ����ǽ��� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_TvMonitor_stop  )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)
_ev_end

/************************<<  �ؼ�֡���� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_AskKeyByScreen  )
_body ( TUmsHandle  , 1  )	
_body( TAskKeyByScreenTr, 1)
_ev_end


/***********************<<  Ums֪ͨUMS��ϯ���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_ChairCap_Notify )
_body ( TUmsHandle  , 1  )	
_body( TChairInfoTr, 1)
_ev_end


/***********************<<  UMS֪ͨCMS����CNS�б� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */_event(  evtp_Conf_CnsList_Notify )
 _body ( TUmsHandle  , 1  )	
	_body ( TConfCnsInfo  , 1  )
   _ev_end

   /************************<<  viewlocal >>********************
   *[��Ϣ��]			 
   *   NULL	
   *[��Ϣ����]	
   *
   */
   _event( evtp_Conf_ViewLocal_Cmd  )
   _body ( TUmsHandle  , 1  )	
   _ev_end
   
   /************************<<  cannelviewlocal >>********************
   *[��Ϣ��]			 
   *   NULL	
   *[��Ϣ����]	
   *
   */
   _event( evtp_Conf_CancelViewLocal_Cmd  )
   _body ( TUmsHandle  , 1  )	
   _ev_end
   
/***********************<<   >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_FlowCtrol )
_body ( TUmsHandle  , 1  )	
_body ( TFlowControl  , 1  )	
_ev_end

/***********************<<  ����֡�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_AdjustFrameRate )
_body ( TUmsHandle  , 1  )	
_body ( TAdjustFrameRate  , 1  )	
_ev_end

/***********************<<  �����ֱ��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_AdjustVidRes )
_body ( TUmsHandle  , 1  )	
_body ( TAdjustVidRes  , 1  )	
_ev_end


/***********************<<���������Ϣ   >>********************
 */
_event( evtp_Conf_Clear )
_body ( TUmsHandle  , 1  )	
_ev_end


/***********************<<����״̬����  >>********************
 */
_event( evtp_Conf_RecPlayState_Nty )
_body ( TUmsHandle  , 1  )
_body ( TUpRecPlayState, 1)
_ev_end

/***********************<< �ϼ�֪ͨ�¼�ֹͣ����  >>********************
 */

 _event( evtp_Conf_StopRecPlay_Req )
 _body ( TUmsHandle  , 1  )
 _body ( u32,	1)
_ev_end


/***********************<< ����ؼ�֡����  >>********************
 */

 _event( evtp_Conf_ResetFastUpdate )
 _body ( TUmsHandle  , 1  )
 _body ( u32,	1)
_ev_end

/***********************<< �ر�ͨ������  >>********************
 */

 _event( evtp_Close_Chan_Req )
 _body ( TUmsHandle  , 1  )
 _body ( EmChanType,	1) //�ر�ͨ������
 _body ( TUmsNodeCapset, 1)
_ev_end


//////////////////////////////////////////////////////////////////////////
//��������
 _event(ev_GetVid_Req)
 	_body (TUmsHandle, 1)
 	_body(TGetVidInfo, 1)
 _ev_end

 _event(ev_GetVid_Res)
	_body (TUmsHandle, 1)
 	_body(TGetVidInfoRes, 1)
 _ev_end

 _event(ev_GetVid_Stop_Req)
 	_body (TUmsHandle, 1)
 	_body(TGetVidBaseInfo, 1)
 _ev_end

 _event(ev_GetVid_Stop_Res)
 	_body (TUmsHandle, 1)
 	_body(TStopGetVid, 1)
 _ev_end


 /***********************<<  B4֪ͨ�ն�����Ŀ�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_YouAreSeeingEx_Ind )
_body ( TUmsHandle  , 1  )	
_body( TTpYouAreSeeing, 1)
_ev_end

/***********************<< ����װ����  >>********************
 */
 _event( evtp_JoinWBConf_Cmd )
 _body ( TUmsHandle  , 1  )
 _body( u32, 1)
 _ev_end

 
/***********************<< ����װ������  >>********************
 */
 _event( evtp_JoinWBConf_Ind )
 _body ( TUmsHandle  , 1  )
 _body( BOOL32, 1)
 _ev_end

 /***********************<< �װ�������  >>********************
 */
 _event( evtp_HungUpWBConf_Cmd )
 _body ( TUmsHandle  , 1  )
 _ev_end

 //////////////////////////////////////////////////////////////////////////
// �ն˲�������ǽ���

/***********************<<  ֪ͨ�ն˵���ǽ���ͨ����Ϣ >>********************
 *[��Ϣ����]	ums	--> cns
 *
 */
 _event( evTPUMS_CNS_hduPlan_Nty )
 _body ( TUmsHandle  , 1  )
 _body ( THduPlanPackData  , 1  )
 _ev_end


 /***********************<<  ���ŵ���ǽĳ��ͨ������ >>********************
 *[��Ϣ����]	cns	--> ums
 *
 */
 _event( evTPCNS_UMS_HduPlay_Req )
 _body ( TUmsHandle  , 1  )
 _body ( TTPHduPlayReq  , 1  )
 _ev_end

 /***********************<<  ���ŵ���ǽĳ��ͨ����Ӧ >>********************
 *[��Ϣ����]	ums	--> cns
 *
 */
 _event( evTPUMS_CNS_HduPlay_Ind )
 _body ( TUmsHandle  , 1  )
 _body ( TPHduBaseInfo  , 1  )
 _body ( EmTpHduPlayNackReason  , 1  )
 _ev_end

 /***********************<<  ֹͣ���ŵ���ǽĳ��ͨ������ >>********************
 *[��Ϣ����]	cns	--> ums
 *
 */
 _event( evTPCNS_UMS_HduStopPlay_Req )
 _body ( TUmsHandle  , 1  )
 _body ( TTPHduPlayReq  , 1  )
 _ev_end

/***********************<<  ֹͣ���ŵ���ǽĳ��ͨ����Ӧ >>********************
 *[��Ϣ����]	ums	--> cns
 *
 */
 _event( evTPUMS_CNS_HduStopPlay_Ind )
 _body ( TUmsHandle  , 1  )
 _body ( TPHduBaseInfo   , 1  )
 _body ( u16   , 1  )
 _ev_end

 /***********************<<  ֹͣ�������е���ǽͨ������ >>********************
 *[��Ϣ����]	cns	--> ums
 *
 */
 _event( evTPCNS_UMS_HduStopAllPlay_Req )
 _body ( TUmsHandle  , 1  )
 _ev_end

 /***********************<<  ���õ���ǽͨ���������� >>********************
 *[��Ϣ����]	cns	--> ums
 *
 */
 _event( evTPCNS_UMS_HduSetVol_Req )
 _body ( TUmsHandle  , 1  )
 _body ( THduSetVolInfo  , 1  )
 _ev_end

 /***********************<<  ���õ���ǽͨ��������Ӧ >>********************
 *[��Ϣ����]	cns	--> ums
 *
 */
 _event( evTPUMS_CNS_HduSetVol_Ind )
 _body ( TUmsHandle  , 1  )
 _body ( THduSetVolInfo  , 1  )
 _body ( EmTpHduSetVolRes  , 1  )
 _ev_end

/***********************<<  ���õ���ǽͨ���໭��͵��������� >>********************
 *[��Ϣ����]	cns	--> ums
 *
 */
 _event( evTPCNS_UMS_HduChangeChanMode_Req )
 _body ( TUmsHandle  , 1  )
 _body ( THduChanModeSetInfo  , 1  )
 _ev_end

 /***********************<<  ���õ���ǽͨ���໭��͵������Ӧ >>********************
 *[��Ϣ����]	cns	--> ums
 *
 */
 _event( evTPUMS_CNS_HduChangeChanMode_Ind )
 _body ( TUmsHandle  , 1  )
 _body ( THduChanModeSetInfo  , 1  )
 _body ( EmTpHduChangeChanModeRes  , 1  )
 _ev_end


/***********************<< �������������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfRollCallUpdate_Cmd )
_body (TUmsHandle, 1)
_body ( TConfRollCallInfo , 1 )	
_ev_end



/***********************<< ���������������Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfRollCallUpdate_Ind )
_body (TUmsHandle, 1)
_body ( TConfRollCallInfo , 1 )	
_ev_end




/***********************<< �������������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfRollCallNextEp_Cmd )
_body (TUmsHandle, 1)
_body ( TRollCallNextEpInfo , 1 )	
_ev_end



/***********************<< ���������������Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfRollCallNextEp_Ind )
_body (TUmsHandle, 1)
_body ( TRollCallNextEpInfo , 1 )	
_ev_end


/***********************<< ��������µ����б�  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfRollCallUpdataList_Cmd )
_body (TUmsHandle, 1)
_body ( TUpdataRollCallList , 1 )	
_ev_end



/***********************<< ��������µ����б��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfRollCallUpdataList_Ind )
_body (TUmsHandle, 1)
_body ( TUpdataRollCallListRes , 1 )	
_ev_end



 /***********************<<  ��ϯ���µ�������� >>********************	
 *[��Ϣ����] CNS->UMS
 *
 */
_event(  evtp_UmsRollUpdate_PresentState )
	_body (TUmsHandle, 1)
	_body ( TRollCallPresentStateMsg  , 1  )	
_ev_end




 /***********************<<  ��������� ͬ�� >>********************	
 *[��Ϣ����] CNS->UMS
 *
 */
_event(  evtp_UmsRoll_PresentState_Notify )
	_body (TUmsHandle, 1)
	_body ( TRollCallPresentStateMsg  , 1  )	
_ev_end





 /***********************<<  ֪ͨ�¼�UMS �����ߺͱ������ >>********************	
 *[��Ϣ����] UMS->UMS
 *
 */
_event(  evtp_UmsRollCallScreenStat_Notify )
	_body (TUmsHandle, 1)
	_body ( TRollCallCasecadeNtfy  , 1  )	
_ev_end



/***********************<< ���������״̬֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfRollCallUpdate_Nty )
_body (TUmsHandle, 1)
_body ( TConfRollCallInfo , 1 )	
_ev_end



// �������
/***********************<<  �������ܻ������������ƻ�����ֹͣ����cmd��Ϣ���� >>********************	
 *[��Ϣ����]	CNS	-->  UMS
 ��ע���������ܻ�����ֹͣ�����������Σ�����TUmsAudMixInfo�����m_tMixList�ֶ�
 *
 */
_event(  evtp_CNS_UMS_ConfAudMixMode_cmd )
_body (TUmsHandle, 1) 
_body ( TUmsAudMixInfo  , 1  )
_ev_end

/***********************<<  �������ܻ������������ƻ�����ֹͣ����ind��Ϣ���� >>********************	
 *[��Ϣ����]	UMS	-->  CNS
 *
 */
_event(  evtp_UMS_CNS_ConfAudMixMode_ind ) 
_body (TUmsHandle, 1) 
_body ( TUmsAudMixModeCmdRes  , 1  )
_ev_end

/***********************<< �޸Ļ�����Ա�б�cmd��Ϣ���ǻ���ģʽҲ��Ч >>********************	
 *[��Ϣ����]	CNS	-->  UMS
 *
 */
_event(  evtp_CNS_UMS_ConfAudMixList_cmd ) 
_body (TUmsHandle, 1) 
_body ( TUmsAudMixListCmd  , 1  )
_ev_end

/***********************<<  �޸Ļ�����Ա�б�cmd��Ϣ��Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  CNS
 *
 */
_event(  evtp_UMS_CNS_ConfAudMixList_ind ) 
_body (TUmsHandle, 1) 
_body ( TUmsAudMixListCmdRes  , 1  )
_ev_end


/***********************<<  �������֪ͨ��Ϣ >>********************	
 *[��Ϣ����]	UMS	-->  CNS
 *
 */
_event(  evtp_UMS_CNS_ConfAudMixMode_Notify ) 
_body (TUmsHandle, 1) 
_body ( TUmsAudMixInfo  , 1  )
_ev_end

/***********************<<  �����������֪ͨ��Ϣ >>********************	
 *[��Ϣ����]	UMS	-->  UMS
 *
 */
_event(  evtp_UMS_UMS_ConfAudMixMode_Notify ) 
_body (TUmsHandle, 1) 
_body ( TUmsAudMixCasecadeInfo  , 1  )
_ev_end


/***********************<<  �᳡�Ƿ��ڻ�������� >>********************	
 *[��Ϣ����]	UMS	-->  CNS
 *
 */
_event(  evtp_UMS_CNS_EpInAudMix_Notify ) 
_body (TUmsHandle, 1) 
_body ( BOOL32  , 1  )
_ev_end

/***********************<<  323������Ϣ >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	cns	--> ums
 *
 */
_event(  evtp_KedaManuProduct_Notify ) 
_body (TUmsHandle, 1) 
_body ( u8  , 1  )
_ev_end

/***********************<<  Զңͨ���� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	cns	--> ums
 *
 */
_event(  evtp_CNS_UMS_FeccChanConnected )
_body ( TUmsHandle  , 1  )
_ev_end

/***********************<< ums���͸�cns���¼�ums Զң��Ϣ >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	
 *
 */
_event(  evtp_UMS_CNS_SendFecc_Cmd )
_body ( TUmsHandle  , 1  )
_body ( TCamAction  , 1  )
_body ( TFeccMtInfo  , 1  )
_ev_end

/***********************<<  �յ�cns���ϼ�ums Զң��Ϣ >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	cns	--> ums
 *
 */
_event(  evtp_CNS_UMS_FeccReq )
_body ( TUmsHandle  , 1  )
_body ( TFeccInfo  , 1  )
_ev_end

/***********************<<  �յ�����cns����ƵԴ��Ϣ֪ͨ >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	cns	--> ums
 *
 */
_event(  evtp_CNS_UMS_VidInfoNty )
_body ( TUmsHandle  , 1  )
_body ( TVidSourceInfo, 1)
_ev_end

/***********************<<  ���͸�cns����ƵԴ��Զң��Ϣ֪ͨ >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	ums	--> cns
 *
 */
_event(  evtp_UMS_CNS_VidFeccInfoNty )
_body ( TUmsHandle  , 1  )
_body ( TConfVidFeccInfo, 1)
_ev_end

/***********************<<  �յ�cns ��ǰʹ�õ���ƵԴ ֪ͨ >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	cns	--> ums
 *
 */
_event(  evtp_CNS_UMS_EpStatusNty )
_body ( TUmsHandle  , 1  )
_body ( TEpStatusInfo, 1)
_ev_end

/***********************<<  �¼����ϼ����� �᳡Զң ��ƵԴ��Ϣ >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	ums	--> ums
 *
 */
_event(  evtp_Conf_EpVidFeccInfo_Update )
_body ( TUmsHandle  , 1  )
_body ( TConfEpVidFeccList, 1)
_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(tpumswithumssipadapter)
};
#endif


#endif // _h_eventoutsipadapter_h__