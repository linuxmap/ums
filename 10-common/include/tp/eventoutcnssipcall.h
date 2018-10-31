#ifndef _h_eventoutcnssipcall_h__
#define _h_eventoutcnssipcall_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCALLEVENT
{
#endif 

_ev_segment( outercnssipcall  )
/***********************<< ���л������� >>********************	
 *[��Ϣ��]
 * TTPDialParam ���в���
 *[��Ϣ����]
 *  cnc -> cns, cns	 ->  cncall
*/
	  _event(  ev_TppMakeCall_Cmd )
	  _body( TTPDialParam ,1 )			
	  _ev_end

	  _event(  ev_TppAnswerCall_Cmd )
	  _ev_end

 /***********************<< �Ҷϻ������� >>********************	
 *[��Ϣ��]
 * NULL
 *[��Ϣ����]
 * cnc -> cns, cns	 ->  cncall
 */
	  _event(  ev_TppHangUp_Cmd )
	  _ev_end
	  
 /***********************<< ���л�����Ӧ >>********************	
 *[��Ϣ��]
 * s32 ����ID
 * TTPDialParam ���в���
 *[��Ϣ����]
 *  cns	 <-  cncall
 */	  
	  _event(  ev_TppCallIncoming_Ind )
	  _body( s32 ,1 )						// ����ID
	  _body( TTPDialParam ,1 )				//���в���
	  _ev_end

 /***********************<< ˫��ͨ������ʧ�ܻ�Ӧ >>********************	
 *[��Ϣ��]
 * NULL
 *[��Ϣ����]
 *  cns	 <-  cncall
 */	
	  _event( ev_TppDualChannelEstablishFail_Ind )
	  _ev_end

 /***********************<< ����ͨ�����ӻ�Ӧ >>********************	
 *[��Ϣ��]
 * s32
 * s32
 * TTPCapPack
 *[��Ϣ����]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppChannelConnect_Ind )
	  _body( s32 , 1)								//����ID
	  _body( s32, 1)								//����������
	  _body( TTPCapPack, 1)							//���
	  _ev_end
	
 /***********************<< �Ͽ�ͨ�����ӵĻ�Ӧ >>********************	
 *[��Ϣ��]
 * s32
 * s32
 * EmTPChannelReason
 *[��Ϣ����]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppChannelDisConnect_Ind )
	  _body( s32 , 1)					//����ID
	  _body( s32, 1)					//ͨ��ID
	  _body( EmTPChannelReason, 1)		//ͨ���Ͽ�ԭ��
	  _ev_end
	
 /***********************<< �����������ӵĻ�Ӧ >>********************	
 *[��Ϣ��]
 * s32 ����ID
 * TTPDialParam ���в���
 *[��Ϣ����]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppCallConnect_Ind )
	  _body( s32, 1 )
	  _body( TTPDialParam, 1 )
	  _ev_end
	
 /***********************<< �����������ӵĻ�Ӧ >>********************	
 *[��Ϣ��]
 * s32 ����ID
 * TTPDialParam ���в���
 *[��Ϣ����]
 *  cns	 <-  cncall
 */
	  _event(  ev_TppCallDisconnect_Ind )
	  _body( s32, 1 )					//����ID
	  _body( EmCnsCallReason, 1)		//�Ͽ�ԭ��
	  _ev_end
	  
	  _event(  ev_TppCapSet_Nty )
	  _ev_end
	
 /***********************<< �Ҷϻ�Ӧ >>********************** 
*[��Ϣ��]
+EmCnsCallReason
*[��Ϣ����]
*  cns	  ->  cnc
*/
_event(  ev_TppHangUp_Ind )
_body ( EmCnsCallReason, 1 )
_ev_end
 

 /***********************<< ������ӻ���ģ�� >>********************** 
*[��Ϣ��]
+TTPConfTemplate
*[��Ϣ����]
*  cnc	  ->  cns
*/
_event(  ev_CnAddConfTemplate_Req )
_body ( TTPConfTemplate    , 1    )
 _ev_end


  /***********************<< ������ӻ���ģ���� >>********************** 
*[��Ϣ��]
+TTPConfTemplate
*[��Ϣ����]
*  cnc	  ->  cns
*/
_event(  ev_CnAddConfTemplate_Rsp )
_body ( TTPConfTemplate    , 1    )
_body( TOprConfTmpResult, 1 )
_ev_end


  /***********************<< CNS����CNCALLЭ��ջ��ʼ�� >>********************** 
*[��Ϣ��]
* TTPDialParam			���в���
*[��Ϣ����]
*  cns	  ->  cncall
*/
_event(  ev_Cn_MakeCall_Cmd )
_body( TTPDialParam, 1 )
_ev_end


  /***********************<< CNS����CNCALLЭ��ջ��ʼ�� >>********************** 
*[��Ϣ��]
* s32				����ID
* BOOL32			��ӦAnswer
* TTPDialParam		���в���
* EmCnsCallReason	����Reason	
*[��Ϣ����]
*  cns	  ->  cncall
*/
_event(  ev_Cn_AnswerCall_Cmd )
_body( s32, 1 )
_body( BOOL32, 1 )
_body( TTPDialParam, 1 )
_body( EmCnsCallReason, 1)
_ev_end


  /***********************<< CNS����CNCALLЭ��ջ��ʼ�� >>********************** 
*[��Ϣ��]
* s32					����ID
* EmCnsCallReason		�Ҷ�ԭ��
*[��Ϣ����]
*  cns	  ->  cncall
*/
_event(  ev_Cn_HangUp_Cmd )
_body( s32, 1 )
_body( EmCnsCallReason, 1 )
_ev_end


  /***********************<< CNS����CNCALLЭ��ջ��ʼ�� >>********************** 
*[��Ϣ��]
* s32		����ID
* s32		ͨ��ID
* s32		��Ϣ����
* u16		���ݳ���
* u8*		����
*[��Ϣ����]
*  cns	  ->  cncall
*/
_event(  ev_Cn_SendChanCtrl_Cmd )
_body( s32, 1 )
_body( s32, 1 )
_body( s32, 1 )
_body( u16, 1 )
_body( u8, TP_NAME_LEN_256 )
_ev_end


  /***********************<< CNS����CNAdapter����Sipע�� >>********************** 
*[��Ϣ��]
* TTPSipRegistrarCfg	ע�������������Ϣ
* u32					ע����
*[��Ϣ����]
*  CNS	 ->  CnAdapter
*/
_event(  ev_Cn_Register_Cmd )
_body( TTPSipRegistrarCfg, 1 )
_body( u32, 1 )
_ev_end


  /***********************<< CNS����CNAdapter����ע�� >>********************** 
*[��Ϣ��]
* u32					ע����
*[��Ϣ����]
*  CNS	  ->  CnAdapter
*/
_event(  ev_Cn_UnRegister_Cmd )
_body( u32, 1 )
_ev_end


  /***********************<< CNS����CNAdapter���� >>********************** 
*[��Ϣ��]
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SetStrategy_Cmd )
_ev_end


  /***********************<< CNS����CNAdapter���ûص����� >>********************** 
*[��Ϣ��]
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SetPAEvent_Cmd )
_ev_end


  /***********************<< CNS����CNAdapter���� >>********************** 
*[��Ϣ��]
* s32					����ID
* s32					��Ϣ����
* u16					buf����
* u8*					buf
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SendConfCtrl_Cmd )
_body( s32, 1 )
_body( s32, 1 )
_body( u16, 1 )
_body( u8, TP_NAME_LEN_256 )
_ev_end


  /***********************<< CNS����CNAdapter�˳� >>********************** 
*[��Ϣ��]
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_Quit_Cmd )
_ev_end


  /***********************<< CNS����CNAdapter����˫�� >>********************** 
*[��Ϣ��]
* s32					����ID
* TTPMediaStream		˫��
* s32					cap����
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_SendDual_Cmd )
_body( s32, 1 )
_body( TTPDualCap, 1 )
_ev_end


  /***********************<< CNS����CNAdapter˫��Ӧ�� >>********************** 
*[��Ϣ��]
* s32					����ID
* CPAMediaStream		˫��
* s32					cap����
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_AnswerDual_Cmd )
_body( s32, 1 )
_body( TTPDualCap, 1 )
_ev_end


  /***********************<< CNS����CNAdapterֹͣ˫�� >>********************** 
*[��Ϣ��]
* s32					����ID
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event( ev_Cn_StopDual_Cmd )
_body( s32, 1 )
_ev_end


  /***********************<< CNS����CNAdapter��ӡ >>********************** 
*[��Ϣ��]
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_Cn_Printf_Cmd )
_ev_end


  /***********************<< CNAdapter����CNS����ע�� >>********************** 
*[��Ϣ��]
*[��Ϣ����]
*  CNAdapter    ->  CNS
*/
_event(  ev_tppregcncall_req )
_ev_end


  /***********************<< CNS�ظ�CNAdapterע������ >>********************** 
*[��Ϣ��]
*[��Ϣ����]
*  CNS	  ->  CNAdapter
*/
_event(  ev_tppregistercall_rsp )
_ev_end


  /***********************<< ������֪ͨ >>********************** 
*[��Ϣ��]	
* TCnsCapset				������(��������ȷ�������)		
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallAVCapset_Nty )
_body( TCnsAVCapset, 1 )
_ev_end

  /***********************<< ȫ�ֵ�ַ����ȡ >>********************** 
*[��Ϣ��]	
	
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_GetRegInfo )
_body( u32, 1 )
_body( TTPGetRegInfo, 1 )
_ev_end

  /***********************<< CNS����CNAdapter����h323ȥע�� >>********************** 
*[��Ϣ��]
* u32					ע����
*[��Ϣ����]
*  CNS	  ->  CnAdapter
*/
_event(  ev_Cn_UnGkRegister_Cmd )
_body( u32, 1 )
_ev_end

  /***********************<< ������Ƶ����֪ͨ>>********************** 
*[��Ϣ��]
* EmTpAudioFormat					
*[��Ϣ����]
*  CNS	  ->  CnAdapter
*/
_event(  ev_tppSetAudioFromat_Cmd )
_body( EmTpAudioFormat, 1 )
_ev_end

/***********************<< cns�Զ��ҵ���ʱ��>>********************** 
*					
*[��Ϣ����]
*  CNS	  ->  CNS
*/
_event(  ev_TppAutoHangup_Cmd_timer )
_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnssipcall )
};
#endif
#endif //TPP_EVENT_H