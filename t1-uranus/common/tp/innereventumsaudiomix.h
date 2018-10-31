#ifndef _h_innereventumsaudiomix_h__
#define _h_innereventumsaudiomix_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsaudiomix
{
#endif

	_ev_segment( innerumsaudiomix )

 /***********************<<  ���Ӽ�ʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_AudioMixConnectToUms_Time )
 _ev_end

  /***********************<< �������л���ʱ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_ChangeSpeakerProtect_Time )
 _ev_end

  /***********************<< �Ƿ������ظ������� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_UpdatePowerToCall_Time )
 _ev_end

  /***********************<< ����ģ�� �ص��������û��������ղ��� ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_AudMixMediaRevCB_Ind )
 _ev_end
 
   /***********************<< confinst �� apu2�������´���ר��App ���·�������Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_UpdateSpeakerInfoToApu2_Ind )
 _body( u16 , 1 )//������ 
 _body( u16 , 1 )//��ϯ
 _body( BOOL32 , 1 )//�Ƿ��ֶ�
 _ev_end

    /***********************<< apu2�������´���ר��App ֪ͨ confinst �л������� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_AudMixChangeSpeakerToCall_Cmd )
 _body( u16 , 1 )//������ 
 _body( u16 , 1 )//��ϯ
 _ev_end


//////////////////////////////////////////////////////////////////////////
//apu2����
 /***********************<< ����ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_reg )
 _body( TMixerRegInfo , 1 )
 _ev_end

  /***********************<< ����ע�� ack >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_reg_ack )
 _body( TMixRegAck , 1 )
 _ev_end

   /***********************<< ����ע�� nack >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_reg_nack )
 _ev_end

  /***********************<< ������ ״̬֪ͨ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_stat_ntfy )
 _body( TMixerStatNtfy , 1 )
 _ev_end

  /***********************<< �������� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_start_mix )
 _body( TStartMix , 1 )
 _ev_end

 /***********************<< �������� ��Ӧ�ɹ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_start_mix_ack )
 _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< �������� ��Ӧʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_start_mix_nack )
  _body( u8 , 1 )//EqpID
 _ev_end

   /***********************<< ֹͣ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_stop_mix )
 _body( u8, 1 )
 _ev_end

  /***********************<< ֹͣ���� ��Ӧ�ɹ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_stop_mix_ack )
 _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< ֹͣ���� ��Ӧʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_stop_mix_nack )
  _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< ��ӻ�����Ա >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_add_mixmember )
  _body( TTPMixMember , 1 )
 _ev_end

   /***********************<< ��ӻ�����Ա ��Ӧ�ɹ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_add_mixmember_ack )
  _body( TTPMixMember , 1 )
 _ev_end

    /***********************<< ��ӻ�����Ա ��Ӧʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_add_mixmember_nack )
  _body( TTPMixMember , 1 )
 _ev_end

     /***********************<< ɾ��������Ա >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_del_mixmember )
  _body( TTPMixMember , 1 )
 _ev_end

    /***********************<< ɾ��������Ա ��Ӧ�ɹ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_del_mixmember_ack )
  _body( TTPMixMember , 1 )
 _ev_end

    /***********************<< ɾ��������Ա ��Ӧʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_del_mixmember_nack )
  _body( TTPMixMember , 1 )
 _ev_end

   /***********************<< ���û������ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_set_depth )
 _body( TTPMixDepth , 1 )
 _ev_end

  /***********************<< ���û������ ��Ӧ�ɹ� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_set_depth_ack )
 _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< ���û������ ��Ӧʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_set_depth_nack )
  _body( u8 , 1 )//EqpID
 _ev_end

     /***********************<< ��ʼ�������� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_start_vac )
  _body( TStartMix , 1 )
 _ev_end

      /***********************<< ֹͣ�������� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_stop_vac )
 _body( u8, 1 )//EqpID
 _ev_end

       /***********************<< ����������������ʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	eqp -> ����
 *
 */
 _event(  ev_mixer_set_vac_keeptime )
 _body( u8, 1 )//eqpID
 _body( u32, 1 ) //ʱ�� ��
 _ev_end

       /***********************<< �����������֪ͨ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_vac_result_ntfy )
 _body( TMixVacResInfo, 1 )
 _ev_end

 /***********************<< ֪ͨ�����Ƿ������� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_if_snd_ntfy )
 _body( u8, 1 )//eqpID
 _body( BOOL32, 1 ) //�Ƿ�������
 _ev_end

  /***********************<< ǿ�ƻ��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_ForceActive_Cmd )
 _body( u8, 1 )//eqpID
 _body( u8, 1 )//ͨ������
 _ev_end

  /***********************<< ȡ��ǿ�ƻ��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_CancelForceActive_Cmd )
 _body( u8, 1 )//eqpID
 _ev_end

   /***********************<< ���ö�ͨ����Ƶͬ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Eqp -> ����
 *
 */
 _event(  ev_mixer_SyncChnl_Cmd )
 _body( TMixSyncChnl, 1 )
 _ev_end

    /***********************<< ɾ����ͨ����Ƶͬ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	Eqp -> ����
 *
 */
 _event(  ev_mixer_SyncChnl_Del )
 _body( TMixSyncChnl, 1 )
 _ev_end


 /***********************<< ֪ͨ����������Կ ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	���� -> eqp
 *
 */
 _event(  ev_mixer_set_mediakey_ntfy )
 _body( u8, 1 )//eqpID
 _body( TTPQTMediaKeyInfo	, 1)
 _ev_end


#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerumsaudiomix)
};
#endif


#endif // _h_innereventumsaudiomix_h__
