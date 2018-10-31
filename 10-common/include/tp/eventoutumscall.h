#ifndef _h_eventoutumscall_h__
#define _h_eventoutumscall_h__


#include "tpeventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumscall
{
#endif
	
	_ev_segment( outerumscall )

// Notify����Ϣ
/***********************<<  UMS֪ͨUMC���ӻ����б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
 _event(  evtp_AddConfList_Notify )
_body ( TAddConfList  , 1  )
 _ev_end

/***********************<<  UMS֪ͨUMCɾ���Ļ����б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */_event(  evtp_DelConflist_Notify )
	_body ( TDelConfList  , 1  )
   _ev_end

/***********************<<  UMS֪ͨUMC����᳡�б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */_event(  evtp_UpdateConfCnsList_Notify )
	_body ( TConfCnsInfo  , 1  )
   _ev_end

/***********************<<  UMS֪ͨUMC�����˸ı� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_SpeakerChange_Notify )  //brd
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMS֪ͨCMS��ϯ�ı� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */
_event(  evtp_ChairManChange_Notify )
_body ( TConfEpID  , 1  )
_ev_end

/***********************<<  UMS֪ͨUMC��ϯ��Ļ״̬ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_ChairStreenStatus_Notify )  //brd
_body ( TChairStreenInfo, 1)
_ev_end

// begin edit by gaoyong
/***********************<<  UMS֪ͨUMC���������б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_AuxMixInfo_Notify ) //brd
_body ( TConfAuxMixInfo  , 1  )
_ev_end

/***********************<<  UMS֪ͨUMC������ѯ�б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_UpdateConfTurnlist_Notify )  //brd
_body ( TTpPollListNtfy  , 1  )
_ev_end


// cmd��Ϣ
/***********************<<  UMC����UMS��Ӻ�ɾ�����۳�Ա���������ã� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_UpdateAudMixInfo_cmd )
_body (TDiscussListOpr , 1 )
_ev_end


/***********************<<  ��Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_UpdateAudMixInfo_Ind )
_body (TDiscussListOpr , 1 )
_ev_end

/***********************<<  UMC����UMS�����͹ر����ۣ������͹ر����������� ���߷������£��������۳�Ա >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_StartAuxMix_cmd )
_body (TConfAuxMixInfo , 1 )
_ev_end


/***********************<<  ��Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_StartAuxMix_ind )
_body (TConfAuxMixInfo , 1 )
_ev_end

/***********************<< �������������͹ر�  >>********************	
*[��Ϣ����]	umc	-->  ums
*
*/
_event( ev_AuxMixVacSwitch)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<< �������������͹رջ�Ӧ  >>********************	
*[��Ϣ����]	ums	-->  umc
*
*/
_event( ev_AuxMixVacSwitchInd)
_body(TConfAuxMixVacOpr, 1)
_ev_end 

/***********************<<  UMC����UMS������ѯ�б� >>********************	
*[��Ϣ����]	  UMC	-->  UMS
*
*/
_event(  evtp_UpdateTurn_cmd )
_body ( TTpPollListNtfy  , 1  )
_ev_end


/***********************<<  UMC����UMS������ѯ�б��Ӧ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_UpdateTurn_ind )
_body ( TTpPollListInd  , 1  )
_ev_end

/***********************<<  UMC����UMS������ѯ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_StartTurn_cmd )
_body ( TTpPollInterval  , 1  )
_ev_end

/***********************<<  UMC����UMS������ѯ��Ӧ>>********************	
*[��Ϣ����]	UMS -->  UMC
*	����Ϊ����ID
*/
_event(  evtp_StartTurn_ind )
_body ( u16  , 1  )
_body ( EmTPPollResult, 1)
_ev_end


/***********************<<  UMC����UMS�ر���ѯ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_StopTurn_cmd )
_body ( u16  , 1  )
_ev_end

/***********************<<  UMC����UMS�ر���ѯ��Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*	����Ϊ����ID
*/
_event(  evtp_StopTurn_ind )
_body ( u16  , 1  )
_body ( EmTPPollResult, 1) 
_ev_end

/***********************<<  UMC����UMS��ͣ��ͣ��ѯ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_SuspendTurn_cmd )
_body ( u16  , 1  )
_body ( BOOL32, 1 )
_ev_end

/***********************<<  UMC����UMS��ͣ��ͣ��ѯ��Ӧ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_SuspendTurn_ind )
_body ( u16  , 1  )
_body ( EmTPPollResult, 1)
_ev_end

/***********************<<  UMS֪ͨUMC��ѯ״̬ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*	����Ϊ����ID
*/
_event(  evtp_TurnStat_ntfy )
_body ( TTpPollStat  , 1  )
_ev_end

/***********************<<  UMC����UMSѡ���᳡ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_ViewObj_cmd )
_body ( TConfEpID  , 1  ) // �����id����Ҫѡ���᳡��id
_body ( u16  , 1  ) // // ѡ������� 0 1 2
_ev_end

/***********************<<  UMC����UMSѡ���᳡��Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*	����Ϊ����ID
*/
_event(  evtp_ViewObj_ind )
_body ( TConfEpID  , 1  ) // �����id����Ҫѡ���᳡��id
_body ( u16  , 1  ) // // ѡ������� 0 1 2
_body ( TChanViewRes, 1) 
_ev_end

/***********************<<  UMC����UMSȡ��ѡ���᳡ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_UndoViewObj_cmd )
_body ( u16  , 1) // confid
_body ( u16, 1)  // ѡ��������� 0 1 2
_ev_end


/***********************<<  UMC����UMSȡ��ѡ���᳡��Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*	����Ϊ����ID
*/
_event(  evtp_UndoViewObj_ind )
_body ( u16  , 1  ) // confid
_body ( u16, 1)  // ѡ��������� 0 1 2
_body ( EmTPViewResult, 1) 
_ev_end

// end edit by gaoyong 

/***********************<<  CMS�����ٿ����� >>********************	
*[��Ϣ����]	UMS	-->  CMS
*
*/
_event(  evtp_StartConfTemplate_Req )
_body ( u16  , 1  )
_ev_end


/***********************<<  CMS����UMS�ٿ������� >>********************	
*[��Ϣ����]	CMS	-->  UMS
*
*/
_event(  evtp_StartConfTemplate_Ret )
_body ( TStartConfResult  , 1  )
_ev_end


/***********************<<  CMS����UMS�Ҷϻ��� >>********************	
*[��Ϣ����]	CMS	-->  UMS
*	����Ϊ����ID
*/	
_event(  evtp_HungUpConf_cmd )
_body ( u16  , 1  )
_ev_end

/***********************<<  CMS����UMS�Ҷϻ����� >>********************	
*[��Ϣ����]	UMS	-->  CMS
*	����Ϊ����ID
*/	
_event(  evtp_HungUpConf_result )
_body ( u16  , 1  )			//����ID
_body ( EmTpDropConfRet, 1) //���
_ev_end


// begin edit by gaoyong
/***********************<<  UMC��ʱ����EP >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/ 
_event(  evtp_CallEP_cmd )
_body ( TConfCallEpAddr  , 1  )
_ev_end


/***********************<<  UMC����UMS�����Ѿ����ڵ�EP : δ���� >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_CallExistEP_cmd )
_body ( TConfEpID  , 1  )
_ev_end

/***********************<<  UMC��ʱ����EP��� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_CallEP_result )
_body ( TConfCallEpAddr  , 1  )
_body ( EmCnsCallReason  , 1  )
_ev_end

/***********************<<  UMC����UMS�����Ѿ����ڵ�EP���>>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_CallExistEP_result )
_body ( TConfEpID  , 1  )
_body ( EmCnsCallReason  , 1  )
_ev_end

/***********************<<  UMC����UMS�Ҷ�EP >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_DropEp_cmd )
_body ( TConfEpID  , 1  )	
_ev_end


/***********************<<  UMC����UMS�Ҷ�EP��� >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_DropEp_Ind )
_body ( TConfEpID  , 1  )
_body ( EmCnsCallReason, 1)	//EmCnsCallReason_hungup ���عҶϳɹ�  EmCnsCallReason_dstnotfind Ŀ�겻����
_ev_end

/***********************<<  CMS����UMSɾ��EP >>********************	
*[��Ϣ����]	CMS	-->  UMS   // umsδ����
*
*/
_event(  evtp_DeleteEp_cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMC����UMSָ�������� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_ApplySpeaker_cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMS֪ͨUMCָ�������˽�� >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_ApplySpeaker_result )
_body ( TConfEpID  , 1  )	
_body ( EmTpApplySpeakerRet  , 1  )	
_ev_end


/***********************<<  UMCָ��Զ������ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_MuteEp_cmd )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ��������FALSEȡ��Զ������
_ev_end

/***********************<<  UMCָ��Զ��������Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_MuteEp_Ind )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ��������FALSEȡ��Զ������
_ev_end


/***********************<<  UMCָ��Զ�˾��� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_QuietEp_cmd )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<<  UMCָ��Զ�˾�����Ӧ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_QuietEp_Ind )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end


/***********************<<  ������˫�� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_StartDual_Cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  ������˫�����  >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_StartDual_Ind )
_body ( TConfEpID  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end

/***********************<<  ����ر�˫�� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_StopDual_Cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  ����ر�˫�����  >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_StopDual_Ind )
_body ( TConfEpID  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end
// end eidt by gaoyong 

/***********************<<  UMS֪ͨCMS˫��Դ�ı� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */
_event(  evtp_DualEp_Notify )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<< ֪ͨ��ϯ������Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CMS
*
*/
_event(  evtp_ChairConfInfo_Notify )
_body ( TChairConfInfo  , 1  )	
_ev_end

/***********************<< ����Ҷϵ�ԭ��  >>********************	
*[��Ϣ����]	UMS	-->  CMS
*
*/
_event(  evtp_HungUp_Conf_Reason)
_body ( u16,   1  )    //ConfID
_body ( u32  , 1  )	   //�Ҷ�ԭ��
_ev_end

/***********************<< ֪ͨUMC��ʾ��Ϣ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_UmsCommonReasonToUI_Ind )
_body ( TTPUmsReasonInd, 1 )
_ev_end
/***********************<< UMS�����������Ӧ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_UmsJoinConf_Req )
_body ( TTPConfEpInfo, 1 )
_ev_end


/***********************<< UMS�����������Ӧ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_UmsJoinConf_Ack )
_body ( TTPConfEpInfo, 1 )
_ev_end
/***********************<< UMS����֪ͨ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_UmsJoinConf_Notify )
_body ( u16, 1 )
_body ( TTpCallAddr ,1)
_ev_end


/***********************<< CNS�����������Ӧ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_CnsJoinConf_Req )
_body ( TUmsHandle  , 1  )	
_body ( TTPConfEpInfo, 1 )
_ev_end


/***********************<< CNS�����������Ӧ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_CnsJoinConf_Ack )
_body ( TUmsHandle  , 1  )	
_body ( TTPConfEpInfo, 1 )
_ev_end

/***********************<< CNS����֪ͨ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_CnsJoinConf_Notify )
_body ( TUmsHandle  , 1  )	
_body ( u16, 1 )
_body ( TTpCallAddr ,1)
_ev_end

_event(  evtp_Ums_For_Discuss_Timer )
_ev_end






/***********************<< UMC����/�رյ��� >>********************
*[��Ϣ����] UMC -- > UMS
*
*/
_event(  evtp_StartRollCall_cmd )
_body (TConfRollCallInfo , 1 )
_ev_end



/***********************<<  ��Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_StartRollCall_Ind )
_body (TConfRollCallInfo , 1 )
_ev_end



/***********************<< UMC������һ�� >>********************
*[��Ϣ����] UMC -- > UMS
*
*/
_event(  evtp_RollCallNext_cmd )
_body (TRollCallNextEpInfo , 1 )
_ev_end



/***********************<<  ��Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_RollCallNext_Ind )
_body (TRollCallNextEpInfo , 1 )
_ev_end


/***********************<<  ���ɾ�������б� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_RollCallUpdateList_cmd )
_body (TUpdataRollCallList , 1 )
_ev_end



/***********************<<  ���ɾ�������б��Ӧ >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_RollCallUpdateList_Ind )
_body (TUpdataRollCallListRes , 1 )
_ev_end



/***********************<<  ���»᳡����� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(evtp_RollCall_PresentState)
_body (TRollCallPresentStateMsg , 1 )
_ev_end



/***********************<<  ���»᳡�����֪ͨ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(evtp_RollCall_PresentState_Notify)
_body (TRollCallPresentStateMsg , 1 )
_ev_end



/***********************<<  UMS֪ͨUMC״̬ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_RollCallState_Notify ) 
_body ( TConfRollCallInfo  , 1  )
_ev_end


// �������
/***********************<<  �������ܻ������������ƻ�����ֹͣ����cmd��Ϣ���� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 ��ע���������ܻ�����ֹͣ�����������Σ�����TUmsAudMixInfo�����m_tMixList�ֶ�
 *
 */
_event(  evtp_ConfAudMixMode_cmd ) 
_body ( TUmsAudMixInfo  , 1  )
_ev_end

/***********************<<  �������ܻ������������ƻ�����ֹͣ����ind��Ϣ���� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_ConfAudMixMode_ind ) 
_body ( TUmsAudMixModeCmdRes  , 1  )
_ev_end

/***********************<< �޸Ļ�����Ա�б�cmd��Ϣ���ǻ���ģʽҲ��Ч >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_ConfAudMixList_cmd ) 
_body ( TUmsAudMixListCmd  , 1  )
_ev_end

/***********************<<  �޸Ļ�����Ա�б�cmd��Ϣ��Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_ConfAudMixList_ind ) 
_body ( TUmsAudMixListCmdRes  , 1  )
_ev_end


/***********************<<  �������֪ͨ��Ϣ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_ConfAudMixMode_Notify ) 
_body ( TUmsAudMixInfo  , 1  )
_ev_end




/***********************<<  ��ȡ����㲥����Ƶ >>********************	
 *[��Ϣ����]	UMC	-->  UMC
 *
 */
_event(  evtp_GetConfBrdVidAud_cmd ) 
_body ( TUmsGetConfBrdVidAudInfo  , 1 )
_ev_end


/***********************<<  ��ȡ����㲥����Ƶ�� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_GetConfBrdVidAud_ind ) 
_body ( TUmsGetConfBrdVidAudInfo  , 1 )
_ev_end


/***********************<<  �ͷ� ԭ��ȡ����㲥����Ƶ >>********************	
 *[��Ϣ����]	UMC	-->  UMC
 *
 */
_event(  evtp_ReleasConfBrdVidAud_cmd ) 
_body ( TUmsReleaseConfBrdVidAudInfo  , 1 )
_ev_end


/***********************<<  �ͷ� ԭ��ȡ����㲥����Ƶ �� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_ReleasConfBrdVidAud_ind ) 
_body ( TUmsReleaseConfBrdVidAudInfo  , 1 )
_ev_end


/***********************<< ����㲥��Ƶ����ؼ�֡ >>********************	
 *[��Ϣ����]	UMC	-->  UMC
 *
 */
_event(  evtp_GetConfBrdVidAudAskKey ) 
_body ( TUmsGetConfBrdVidAudAskKey  , 1 )
_ev_end

/***********************<<  ����� �����ȡ���黭��ϳ����� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_GetConfVmpVid_cmd ) 
_body ( TUmsGetVmpVidInfo  , 1 )
_ev_end

/***********************<<  ����� �����ȡ���黭��ϳ����� �� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_GetConfVmpVid_ind ) 
_body ( TUmsGetVmpVidInfo  , 1 )
_ev_end

/***********************<<  ����� �ͷ�ԭ��ȡ���黭��ϳ����� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_ReleaseConfVmpVid_cmd ) 
_body ( TUmsReleaseVmpVidInfo  , 1 )
_ev_end

/***********************<<  ����� �ͷ�ԭ��ȡ���黭��ϳ�����  �� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event( evtp_ReleaseConfVmpVid_ind ) 
_body ( TUmsReleaseVmpVidInfo  , 1 )
_ev_end

/***********************<<  ����� �����ȡ���黭��ϳ������ؼ�֡ >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_GetConfVmpVidAskKey_cmd ) 
_body ( TUmsGetVmpVidAskKey  , 1 )
_ev_end

/***********************<<  ����� ����ϳ���״̬���֪ͨ  �� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event( evtp_ConfVmpVid_nty ) 
_body ( TUmsVmpVidData  , 1 )
_ev_end

// ȫ����������״̬֪ͨ��umc
_event(evtp_ConfAllEpQuietMuteStatus_Nty)
_body(u16,1)// ����id
_body(BOOL32,1) // �Ƿ�ȫ�־���
_body(BOOL32, 1) // �Ƿ�ȫ������
_ev_end

/***********************<<  ������������� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_FeccCamera_Req ) 
_body ( TCamReq  , 1 )
_ev_end

/***********************<<  ���󱣴� ����Ԥλ�� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_FeccPrePos_Req ) 
_body ( TPrePos  , 1 )
_ev_end

/***********************<<  ��������ƵԴ >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_FeccSelVid_Req ) 
_body ( TSelVid  , 1 )
_ev_end

/***********************<<  ��Դ Զң ��Ϣ֪ͨ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event( evtp_VidFeccMsg_Nty ) 
_body ( TConfVidFeccInfo  , 1 )
_ev_end

 /*********************<<  CMS�����ٿ���ʱ���� >>********************	
 *[��Ϣ����]	UMS	-->  CMS     ����Ϣֱ����OSP���ͣ�������XML�����
 */
 _event(  evtp_StartInterimMeeting_Req )
 _blob ( u8  , sizeof(TTPConfMeet)  )
_ev_end

/***********************<<  ����� ���� ����᳡ָ����������Ƶ���� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_GetEpSreenStream_cmd ) 
_body ( TGetEpScreenInfo  , 1 )
_ev_end

/***********************<<  ����� ���� ����᳡ָ����������Ƶ���� ��Ӧ >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_GetEpSreenStream_Ind ) 
_body ( TGetEpScreenInd  , 1 )
_ev_end


/***********************<<  ����� �ͷ� ����᳡ָ����������Ƶ���� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_ReleaseEpSreenStream_cmd ) 
_body ( TReleaseEpScreenInfo  , 1 )
_ev_end

/***********************<<  ����� �ͷ� ����᳡ָ����������Ƶ���� ��Ӧ>>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_ReleaseEpSreenStream_Ind ) 
_body ( TReleaseEpScreenInfo  , 1 )
_ev_end

/***********************<<  ����� ���� ����᳡ָ������ �ؼ�֡ >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event( evtp_GetEpSreenAskKey_cmd ) 
_body ( TGetEpScreenAskKey  , 1 )
_ev_end



#ifndef _MakeTpEventDescription_
		_ev_segment_end(outerumscall)
};


#endif


#endif // _h_eventoutumscall_h__
