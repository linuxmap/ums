#ifndef _h_eventoutumsaudiomix_h__
#define _h_eventoutumsaudiomix_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumsaudiomix
{
#endif

	_ev_segment( tpumswithumsaudiomix )

 /***********************<<  �豸����������ע��ʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomixeqp -> audiomix
 *
 */
 _event(  ev_AudioMixInitCfg_NACK )
 _ev_end
   
 /***********************<<  �豸����������ע��ɹ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomixeqp -> audiomix
 *
 */
 _event(  ev_AudioMixInitCfg_ACK )
 	_body(u16,1)
	_body(TUmsRSParam, 1)
 _ev_end

   /***********************<<  ���鿪����ʼ��һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] umscall -> audiomix
 *
 */
 _event(  ev_InitOneAudMixGrp_Req )
	_body(u16,1)   //����ID
	_body(u16,1)   //��ʼ�˿�
	_body(EmTpAudioFormat,1) //��Ƶ��ʽ
	_body(EmTPEncryptType, 1) //���ܷ�ʽ
	_body(u16,1)   //������������ʱ��
 _ev_end

  /***********************<<  �������ȡ��һ����� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] umscall -> audiomix
 *
 */
 _event(  ev_QuiteOneAudMixGrp_Req )
	_body(u16, 1)
 _ev_end

 /***********************<<  �����һ·���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] umscall -> audiomix
 *
 */
 _event(  ev_OpenOneAudMixChan_Req )
	_body(u16, 1)//EpID
	_body(u16, 1)//AudSndNum
	_body(u16, 1)//Ep ChanIndex
	_body(TTPTransAddr, 1)
 _ev_end

  /***********************<<  ����ȡ��һ·���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] umscall -> audiomix
 *
 */
 _event(  ev_CloseOneAudMixChan_Req )
	_body(u16 , 1 )//EpID
	_body(u16 , 1 )//Ep Chan Index
	_body(TEqpRes , 1 )//Ep Chan Index
 _ev_end

 /***********************<<  �����һ·���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix->umscall 
 *
 */
 _event(  ev_OpenOneAudMixChan_Ind )
	_body( u16, 1 )     //EpID
	_body( u16, 1 )     //EpChanIndex
	_body( u16, 1 )  //AudMix ChanIndex
	_body( BOOL32, 1 )   //״̬
 _ev_end

 /***********************<<  ����ģ���У�MediaRcv����������ý���ʱ ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix->umscall 
 *
 */
 _event(  ev_AudMixSetMediaRev_Ind )
	_body(BOOL32, 1 )   //״̬
	_body( u16, 1 )     //EpID
 _ev_end

  /***********************<<  ����ȡ��һ·���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix->umscall 
 *
 */
 _event(  ev_CloseOneAudMixChan_Ind )
	_body(u16, 1)
	_body(BOOL32, 1)
	_body(TEqpRes, 1)
 _ev_end		

 /***********************<<  ���������ı�ʶ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix->umscall 
 *
 */
 _event(  ev_AudMixExciteToCall_Ind )
	_body(u16 , 1)
	_body(u16 , 1)
	_body(u32 , 1)
 _ev_end

  /***********************<<  �ֶ��л������˺󣬸��»����������� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix->umscall 
 *
 */
 _event(  ev_CallExciteToAudMix_Ind )
	_body(u16 , 1)
	_body(u16 , 1)
 _ev_end

  /***********************<<  ֪ͨ���������״̬ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] audiomix->CMC 
 *
 */
_event(  evtp_AudMixStatus_Notify )
	_body ( TAudMixStat  , 1  )		//����ID
_ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(tpumswithumsaudiomix)
};
#endif


#endif // _h_eventoutumsaudiomix_h__
