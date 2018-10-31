#ifndef _h_innereventumsaudbas_h__
#define _h_innereventumsaudbas_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsaudbas
{
#endif

	_ev_segment( innerumsaudbas )

 /***********************<<  ��Ƶ������ע�� >>********************	
 *[��Ϣ��]			 
 *   TTPBasReg
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasEqpReg_Req )
 _body( TTPBasReg, 1 )
 _ev_end

  /***********************<<  ��Ƶ������ע�� ACK >>********************	
 *[��Ϣ��]			 
 *   TTPBasRegAck
 *[��Ϣ����]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasEqpReg_Ack )
 _body( TTPBasRegAck, 1 )
 _body( TUmsRSParam, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ע�� NACK >>********************	
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasEqpReg_NAck )
 _ev_end


  /***********************<<  ��Ƶ������״̬֪ͨ >>********************	
 *[��Ϣ��]			 
 *   TTPBasStatNtfy
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasEqpStat_Ntfy )
 _body( TTPBasStatNtfy, 1 )
 _ev_end


  /***********************<<  ��Ƶ������ ͨ�� ״̬֪ͨ >>********************	
 *[��Ϣ��]			 
 *   TTPBasStatNtfy
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasChnlStat_Ntfy )
 _body( TTPBasStatNtfy, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ �������� >>********************	
 *[��Ϣ��]			 
 *   TStartAudAdapter
 *[��Ϣ����]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasStartAdapter_Req )
 _body( TStartAudAdapter, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ ͨ�� ��������ACK >>********************	
 *[��Ϣ��]			 
 *   TTPBasRetInfo
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStartAdapter_Ack )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ ͨ�� ��������NACK >>********************	
 *[��Ϣ��]			 
 *   TTPBasStatNtfy
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStartAdapter_NAck )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ ֹͣ���� >>********************	
 *[��Ϣ��]			 
 *   TStartAudAdapter
 *[��Ϣ����]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasStopAdapter_Req )
 _body( u8, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ ͨ�� ֹͣ����ACK >>********************	
 *[��Ϣ��]			 
 *   TTPBasRetInfo
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStopAdapter_Ack )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ ͨ�� ֹͣ����NACK >>********************	
 *[��Ϣ��]			 
 *   TTPBasStatNtfy
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  ev_AudBasStopAdapter_NAck )
 _body( TTPBasRetInfo, 1 )
 _ev_end

   /***********************<<  ��Ƶ������ �������� >>********************	
 *[��Ϣ��]			 
 *   TStartAudAdapter
 *[��Ϣ����]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasChangeAdapter_Req )
 _body( TStartAudAdapter, 1 )
 _ev_end

   /***********************<<  ��Ƶ����ͨ�� ͬ��ͨ������ >>********************	
 *[��Ϣ��]			 
 *   TAudBasSyncChnl
 *[��Ϣ����]	EQP - MCUEQP
 *
 */
 _event(  ev_AudBasSetSync_Req )
 _body( TAudBasSyncChnl, 1 )
 _ev_end



 /***********************<< ֪ͨ����������Կ ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_AudBas_set_mediakey_ntfy )
 _body( u8, 1 )//eqpID
 _body( u16, 1 )//ChnlID
 _body( TTPQTMediaKeyInfo	, 1)
 _ev_end
 

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerumsaudbas)
};
#endif


#endif // _h_innereventumsaudiomix_h__
