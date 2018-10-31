#ifndef _h_innereventumsaudiomix_h__
#define _h_innereventumsaudiomix_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnerumsaudiomix
{
#endif

	_ev_segment( innerumsaudiomix )

 /***********************<<  连接计时器 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_AudioMixConnectToUms_Time )
 _ev_end

  /***********************<< 发言人切换定时保护 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_ChangeSpeakerProtect_Time )
 _ev_end

  /***********************<< 是否向主控更新能量 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_UpdatePowerToCall_Time )
 _ev_end

  /***********************<< 接收模块 回调函数设置混音器接收参数 出错 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_AudMixMediaRevCB_Ind )
 _ev_end
 
   /***********************<< confinst 向 apu2能量更新处理专用App 更新发言人信息 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_UpdateSpeakerInfoToApu2_Ind )
 _body( u16 , 1 )//发言人 
 _body( u16 , 1 )//坐席
 _body( BOOL32 , 1 )//是否手动
 _ev_end

    /***********************<< apu2能量更新处理专用App 通知 confinst 切换发言人 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	
 *
 */
 _event(  ev_AudMixChangeSpeakerToCall_Cmd )
 _body( u16 , 1 )//发言人 
 _body( u16 , 1 )//坐席
 _ev_end


//////////////////////////////////////////////////////////////////////////
//apu2接入
 /***********************<< 外设注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_reg )
 _body( TMixerRegInfo , 1 )
 _ev_end

  /***********************<< 外设注册 ack >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_reg_ack )
 _body( TMixRegAck , 1 )
 _ev_end

   /***********************<< 外设注册 nack >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_reg_nack )
 _ev_end

  /***********************<< 混音器 状态通知 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_stat_ntfy )
 _body( TMixerStatNtfy , 1 )
 _ev_end

  /***********************<< 开启混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_start_mix )
 _body( TStartMix , 1 )
 _ev_end

 /***********************<< 开启混音 响应成功 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_start_mix_ack )
 _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< 开启混音 响应失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_start_mix_nack )
  _body( u8 , 1 )//EqpID
 _ev_end

   /***********************<< 停止混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_stop_mix )
 _body( u8, 1 )
 _ev_end

  /***********************<< 停止混音 响应成功 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_stop_mix_ack )
 _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< 停止混音 响应失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_stop_mix_nack )
  _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< 添加混音成员 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_add_mixmember )
  _body( TTPMixMember , 1 )
 _ev_end

   /***********************<< 添加混音成员 响应成功 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_add_mixmember_ack )
  _body( TTPMixMember , 1 )
 _ev_end

    /***********************<< 添加混音成员 响应失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_add_mixmember_nack )
  _body( TTPMixMember , 1 )
 _ev_end

     /***********************<< 删除混音成员 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_del_mixmember )
  _body( TTPMixMember , 1 )
 _ev_end

    /***********************<< 删除混音成员 响应成功 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_del_mixmember_ack )
  _body( TTPMixMember , 1 )
 _ev_end

    /***********************<< 删除混音成员 响应失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_del_mixmember_nack )
  _body( TTPMixMember , 1 )
 _ev_end

   /***********************<< 设置混音深度 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_set_depth )
 _body( TTPMixDepth , 1 )
 _ev_end

  /***********************<< 设置混音深度 响应成功 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_set_depth_ack )
 _body( u8 , 1 )//EqpID
 _ev_end

    /***********************<< 设置混音深度 响应失败 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_set_depth_nack )
  _body( u8 , 1 )//EqpID
 _ev_end

     /***********************<< 开始语音激励 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_start_vac )
  _body( TStartMix , 1 )
 _ev_end

      /***********************<< 停止语音激励 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_stop_vac )
 _body( u8, 1 )//EqpID
 _ev_end

       /***********************<< 设置语音激励保护时间 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	eqp -> 外设
 *
 */
 _event(  ev_mixer_set_vac_keeptime )
 _body( u8, 1 )//eqpID
 _body( u32, 1 ) //时间 秒
 _ev_end

       /***********************<< 语音激励结果通知 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_vac_result_ntfy )
 _body( TMixVacResInfo, 1 )
 _ev_end

 /***********************<< 通知外设是否发送码流 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_if_snd_ntfy )
 _body( u8, 1 )//eqpID
 _body( BOOL32, 1 ) //是否发送码流
 _ev_end

  /***********************<< 强制混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_ForceActive_Cmd )
 _body( u8, 1 )//eqpID
 _body( u8, 1 )//通道索引
 _ev_end

  /***********************<< 取消强制混音 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
 *
 */
 _event(  ev_mixer_CancelForceActive_Cmd )
 _body( u8, 1 )//eqpID
 _ev_end

   /***********************<< 设置多通道音频同步 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	Eqp -> 外设
 *
 */
 _event(  ev_mixer_SyncChnl_Cmd )
 _body( TMixSyncChnl, 1 )
 _ev_end

    /***********************<< 删除多通道音频同步 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	Eqp -> 外设
 *
 */
 _event(  ev_mixer_SyncChnl_Del )
 _body( TMixSyncChnl, 1 )
 _ev_end


 /***********************<< 通知外设码流秘钥 量子 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]	外设 -> eqp
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
