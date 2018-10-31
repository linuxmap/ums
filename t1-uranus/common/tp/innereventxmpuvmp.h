#ifndef _h_innereventxmpuvmp_h__
#define _h_innereventxmpuvmp_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpuvmp
{
#endif

	_ev_segment( innereventxmpuvmp )

	 /***********************<<  xmpu init metting rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuInitMettingRsp
 *[��Ϣ����]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_InitMetting_Rsp )
 _body( TXmpuInitMettingRsp, 1 )
 _ev_end

 	 /***********************<<  xmpu init metting Faild nty  >>********************	
 *[��Ϣ��]			 
 *   
 *[��Ϣ����] XmpuEqp - Call
 *
 */
 _event(  evXmpu_InitMettingFaild_Nty )
  _body( BOOL32, 1 )
 _ev_end

 	 /***********************<<  xmpu stop conf  >>********************	
 *[��Ϣ��]			 
 *   u16
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuStopConf_Nty )
 _body( u16, 1 )
 _ev_end

 /***********************<<  xmpu vmp connect  nty  >>********************	
 *[��Ϣ��]			 
 *   BOOL32
 *[��Ϣ����]	MediaSoruce - XmpuEqp
 *
 */
 _event(  evXmpu_VmpConnect_Nty )
 _body( TXmpuVmpNty, 1 )
 _ev_end

 /***********************<<  xmpu start vmp rsp  >>********************	
 *[��Ϣ��]			 
 *   BOOL32
 *[��Ϣ����]	MediaSoruce - XmpuEqp
 *
 */
 _event(  evXmpu_StartVmp_Rsp )
 _body( TXmpuStartVmpRsp, 1 )
 _ev_end

 
 /***********************<<  xmpu change vmp rsp  >>********************	
 *[��Ϣ��]			 ��ͳ����ϳ�ʹ�ø���Ϣ
 *   TTPBasReg
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_ChangeVmp_Req )
 _body( TXmpuStartVmpInfo, 1 )
 _ev_end

  /***********************<<  xmpu start mpu2 req  >>********************	
 *[��Ϣ��]			 �໭��ϳɿ���
 *   TTPBasReg
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_StartMpu2_Req )
 _body( TVmpStartInfo, 1 )
 _ev_end

 /***********************<<  xmpu UpdateSpeakerSide  >>********************	
 *[��Ϣ��]			 �����������ı߿����
 *   TTPBasReg
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_UpdateSpeakerSide_Req )
 _body( TVmpSpeakerFlag, 1 )
 _ev_end
 

 /***********************<<  xmpu vmp ��ums����ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   TTPBasReg
 *[��Ϣ����]	MediaSource - XmpuEqp - call
 *
 */

 _event(  evXmpu_AskVmpKey_Req ) 
 _body( TTPVmpAskFrame, 1 )
 _body(u32 , 1) 
 _ev_end

 /***********************<< ums �� xmpu vmp  ����ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   TTPBasReg
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evUms_XmpuAskVmpKey_Req )
 _body( TTPVmpAskFrame, 1 )
 _ev_end

  /***********************<<  xmpu vmp  ״̬���֪ͨ >>********************	
 *[��Ϣ��]			 
 *   TTPBasReg
 *[��Ϣ����]	XmpuEqp - Call
 *
 */
 _event(  evXmpu_VmpMdy_Nty ) 
 _body( TXmpuVmpMdyInfo, 1 )
 _ev_end

   /***********************<<  xmpu vmp  ����֪ͨ >>********************	
 *[��Ϣ��]			 
 *   TTPBasReg
 *[��Ϣ����]	 MediaSource - XmpuEqp - Calll
 *
 */
 _event(  evXmpu_VmpDisConnect_Nty ) 
 _body( u32, 1 )
 _ev_end


    /***********************<<  get all res used info  >>********************	
 *[��Ϣ��]			 
 *[��Ϣ����]	Ums - XmpuEqp 
 *
 */
 _event(  evXmpu_res_usd_info_req )
 _body( EMXmpuEqpType, 1 )		//��������
 _ev_end

 _event(  evXmpu_res_usd_info_res )
 _body( TTPBrdUsedInfo, 1 )
 _ev_end

 /***********************<<  ��Դ��ȡ��ʱ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *	��ʱ��
 */
 _event(  evXmpu_Get_Resource_Time )
 _ev_end	

  /***********************<<  xmpu vmp Update UI Nty  >>********************	
 *[��Ϣ��]			 
 *   BOOL32
 *[��Ϣ����]	XmpuEqp - umscall
 *
 */
 _event(  evXmpu_VmpRefresh_Nty )
 _body( TXmpuVmpNty, 1 )
 _ev_end

  /***********************<<  ˢ����Դ��ʱ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *	��ʱ��
 */
 _event(  evXmpu_Refresh_Resource_Time )
 _ev_end	



 #ifndef _MakeTpEventDescription_
   _ev_segment_end(innereventxmpuvmp)
};
 #endif


#endif // _h_innereventumsaudiomix_h__
