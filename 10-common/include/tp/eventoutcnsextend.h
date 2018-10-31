#ifndef _h_eventoutcnsextend_h__
#define _h_eventoutcnsextend_h__

#include "cnseventcomm.h"
#include "cnsstruct.h"

#ifndef _MakeTpEventDescription_
enum EmCNSEXTENDEVENT
{
#endif 

  _ev_segment( outercnsextend  )



  /***********************<<  请求添加用户 >>********************	
  *[消息方向]	CNC	-->  CNS
  *添加用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSAddUserReq )
  _ev_end



  
  /***********************<< 回复添加用户  >>********************	
  *[消息方向]	CNS	-->  CNC
  *添加反馈
  */
  _event(  ev_CNSAddUserRet )
  _body(EmTpRet,	1)	//操作结果
  _ev_end
  



  /***********************<<  请求删除用户 >>********************	
  *[消息方向]	CNC	-->  CNS
  *删除用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSDelUserReq )
  _ev_end	
  



  /***********************<<  回复删除用户 >>********************	
  *[消息方向]	CNS	-->  CNC
  *删除反馈
  */
  _event(  ev_CNSDelUserRet )
  _body(EmTpRet,	1)	//操作结果
  _ev_end
  



  /***********************<<  请求修改密码 >>********************	
  *[消息方向]	CNC	-->  CNS
  *修改用户密码，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSChangePWDReq )
  _ev_end	
  



  /***********************<<   回复修改密码  >>********************	
  *[消息方向]	CNS	-->  CNC
  *修改反馈
  */
  _event(  ev_CNSChangePWDRet )
  _body(EmTpRet,	1)	//操作结果
  _ev_end	
  



  /***********************<< 有一个用户登录  >>********************	
  *[消息方向]	CNS	-->  CNC
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSAddUser_Notify )
  _ev_end	
  



  /***********************<< 有一个用户退出登录  >>********************	
  *[消息方向]	CNS	-->  CNC
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSDelUser_Notify )
  _ev_end	
  



  /***********************<< 修改用户  >>********************	
  *[消息方向]	CNS	-->  CNC
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSUpdateUser_Notify )
  _ev_end	
  
  

  /***********************<<用户在其它地方登录  >>********************	
  *[消息方向]	CNS	-->  CNC
  *
  */
  _event(  ev_CNSLoginByOther_Notify )
  _body(u32_ip, 1)
_ev_end	

  
  /***********************<< CNS发送CNAdapter请求Gk注册 >>********************** 
*[消息体]
* TTPGkRegistrarCfg	注册服务器配置信息
* u32					注册句柄
*[消息方向]
*  CNS	 ->  CnAdapter
*/
_event(  ev_Cn_GkRegister_Cmd )
_body( TTPGkRegistrarCfg, 1 )
_body( u32, 1 )
_ev_end


  /***********************<< 能力集通知 >>********************** 
*[消息体]	
* TCnsCapset				能力集(拆包发，先发能力集)		
*[消息方向]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallAddrCapset_Nty )
//_body( TCnsAddrCapset, 1 )
_body( TTPCnUnpackStream, CNS_CALL_MAX_CHANNEL )
_body( u16, 1 )
_body( u32, 1 )
_body( u8, 1 )
_ev_end

  /***********************<< 双流能力集通知 >>********************** 
*[消息体]	
* TCnsCapset				能力集(拆包发，先发能力集)		
*[消息方向]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallDualCapset_Nty )
_body( TTPDualCap, 1 )
_ev_end

 /***********************<< 音频类型通知 >>********************** 
*[消息体]	
* EmTpAudioFormat				音频类型		
*[消息方向]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_AudioFormat_Nty )
_body( EmTpAudioFormat, 1 )
_ev_end

/***********************<< cnc选看命令 >>********************	
 *[消息体]
 * TTPSelViewReq 选看参数
 *[消息方向]
 *  cnc -> cns, cns	 ->  ums, cns-> mcu
*/
	  _event(  ev_Cn_SelView_Req  )
	  _body( TTPSelViewReq ,1 )			
	  _ev_end

/***********************<< cnc选看命令 >>********************	
 *[消息体]
 * TTPSelViewInd 选看参数
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums
*/
	  _event(  ev_UMS_CNC_ByCNS_SelView_Ind  )
	  _body( TTPSelViewInd ,1 )			
	  _ev_end

/***********************<< cnc选看命令 >>********************	
 *[消息体]
 * TTPSelViewInd 选看参数
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums
*/
	  _event(  ev_UMS_CNC_ByCNS_SelView_Ntfy  )
	  _body( TTPSelViewNtfy ,1 )			
	  _ev_end

/***********************<< 加密配置设置请求  >>********************	
  *[消息体]
  *TTpEncryptKey 加密信息
  *[消息方向]	  CNC	-->  CNS
  *
  */
  _event( ev_tppSetEncryptInfo_Cmd )
  _body( TTpEncryptKey, 1 )
  _ev_end
  
  /***********************<< 加密配置设置通知  >>********************	
  *[消息体]
  *TTpEncryptKey 加密信息
  *[消息方向]	  CNS	-->  CNC
  *
  */
  _event( ev_tppSetEncryptInfo_Nty )
  _body( TTpEncryptKey, 1 )
  _ev_end

   /***********************<< 加密配置设置响应  >>********************	
  *[消息体]
  *TTpEncryptKey 加密信息
  *BOOL 加密信息是否写到配置文件
  *[消息方向]	  CNS	-->  CNC
  *
  */
  _event( ev_tppSetEncryptInfo_Ind )
  _body( TTpEncryptKey, 1 )
  _body( BOOL, 1 )
_ev_end

// 数据会议模块添加Tpad和cns交换消息 add by niu 2014-03-12

 /***********************<<  Tpad通知本端的CNS已经开启白板会议 >>********************	
  *[消息体]
  *[消息方向]
  *  cnc(Tpad) -> cns 
  */_event( ev_tpp_DSIPAddr_Nty )
  _ev_end

  /***********************<<  Cns获得Tpad用户 >>********************	
  *[消息体] 0：加入或离开数据会议标识 1：查询本地发起数据会议Tpad用户标识
  *[消息方向]
  *  cns -> cns(cnue) 
  */_event( ev_tpp_GetConfTpadUser_Cmd )
  _body( u8 , 1 )
  _ev_end

  /***********************<<  Cnue获得Tpad用户后通知本端的CNS >>********************	
  *[消息体]
  *[消息方向]
  *  cns(cnue) -> cns 
  */_event( ev_tpp_GetConfTpadUser_Ind )
  _body( u8 , 1 )
  _body( TTPTPadList , 1 )
  _ev_end

  /***********************<<  Cnue获得Tpad用户后通知本端的CNS >>********************	
  *[消息体]
  *[消息方向]
  *  cns(cnue) -> cns 
  */_event( ev_tpp_NewTpadJoinConf_Nty )
  _ev_end

  /***********************<< 本端CNS发送数据会议服务器IP地址通知除了开启白板会议Tpad外所有连接到其服务器上的Tpad加入白板会议 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cnc(Tpad) 
  */_event( ev_tpp_JoinWBConf_Cmd )
  _body( TTPDataConfInfo , 1 )
  _body( TTPCnsConfStatus, 1)//数据会议名称
  _ev_end

//   /***********************<< 加入白板会议成功的Tpad把会议状态设置为在会状态 >>********************	
//   *[消息体]
//   *[消息方向]
//   *  cnc(Tpad) -> cns 
//   */_event( ev_tpp_JoinWBConf_Ind )
//   _body( u32 , 1 )
//   _ev_end

  /***********************<< 结束网呈会议，CNS通知连接在其服务器的所有Tpad离开白板会议 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cnc(Tpad) 
  */_event( ev_tpp_LeaveWBConf_Nty )
  _body( TTPDataConfInfo , 1 )
   _body( TTPCnsConfStatus, 1)//数据会议名称
  _ev_end

  /***********************<< 新会议呼进来请求Tpad是否加入 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cnc(Tpad) 
  */_event( ev_tpp_NewConfCall_Req )
  _body( TTPCnsConfStatus, 1)//数据会议名称
  _ev_end

  /***********************<< 数据服务器配置设置请求  >>********************	
  *[消息体]
  *u32_ip   数据服务器配置信息
  *[消息方向]	  TPad	-->  CNS
  *
  */
  _event( ev_tppSetDataServerInfo_Cmd )
  _body( TTPDataConfInfo, 1 )
  _ev_end
  
  /***********************<< 数据服务器配置设置通知  >>********************	
  *[消息体]
  *u32_ip   数据服务器配置信息
  *[消息方向]	  CNS	-->  TPad
  *
  */
  _event( ev_tppSetDataServerInfo_Nty )
  _body( TTPDataConfInfo, 1 )
  _ev_end
  
  /***********************<< 数据服务器配置设置响应  >>********************	
  *[消息体]
  *u32_ip   数据服务器配置信息
  *BOOL 数据服务器配置是否成功
  *[消息方向]	  CNS	-->  TPad
  *
  */
  _event( ev_tppSetDataServerInfo_Ind )
  _body( TTPDataConfInfo, 1 )
  _body( BOOL, 1 )
  _ev_end

/***********************<< 通知数据会议名称到TPad  >>********************	
  *[消息体]
  *u32_ip   数据服务器配置信息
  *BOOL 数据服务器配置是否成功
  *[消息方向]	  CNS	-->  TPad
  *
  */
  _event( ev_tpp_DataConfName_Nty )
  _body( TTPCnsConfStatus, 1 )
  _ev_end

    /***********************<< Tpad是否加入数据会议状态通知 >>********************	
  *[消息体]
  *[消息方向]
  *  cnc(Tpad) -> cns 
  */
  _event( ev_tppDataConfState_Nty )
  _body( BOOL , 1 )
  _ev_end
  //end by niu

  /***********************<<双流加密通知密钥  >>************************
*[消息体] 开启双流通知密钥
*[消息方向]
*  cns	   -> cnc
*/
_event( ev_tppCodecEncryptKey_Nty )
_body( TTpEncryptKey, 1 )
_ev_end

/***********************<<暂停轮询  >>************************
*[消息体] 是否暂停轮询
*[消息方向]
*  cns	   <-  cnc
*/
_event( ev_Cn_Conf_SuspendPoll_Req )
_body ( BOOL32, 1 )
_ev_end

/***********************<<暂停轮询结果  >>************************
*[消息体] 暂停轮询结果
*[消息方向]
*  cns	   ->  cnc
*/
_event( ev_Cn_Conf_SuspendPoll_Ind )
_body ( EmTPPollResult, 1 ) //结果
_ev_end

/***********************<<更新轮询列表  >>************************
*[消息体] 更新轮询列表
*[消息方向]
*  cns	   <->  cnc
*/
_event(  ev_Cn_UpdateConfTurnlist_Nty )
_body ( TTpPollListNtfy , 1 )	
_ev_end

/***********************<<更新轮询列表回应  >>************************
*[消息体] 更新轮询列表结果
*[消息方向]
*  cns	   ->  cnc
*/
_event(  ev_Cn_UpdateConfTurnlist_Ind )
_body ( TTpPollListInd , 1 )	
_ev_end

/***********************<<CNC 请求 占用合成  >>************************
*[消息体] 是否占用合成信息
*[消息方向]
*  cns	   <-  cnc
*/
_event( ev_Cn_RervesBrdVmp_Req )
_body(TRersvesEqpReq, 1)
_ev_end

/***********************<<CNC 请求 占用合成回应  >>************************
*[消息体] 是否占用合成信息
*[消息方向]
*  cns	   ->  cnc
*/
_event( ev_Cn_RervesBrdVmp_Ind )
_body(TRersvesEqpRsp, 1)
_ev_end

/***********************<<CNC 请求配置画面合成  >>************************
*[消息体] 是否配置合成信息
*[消息方向]
*  cns	   <-  cnc
*/
_event( ev_Cn_SetBrdVmp_Req )
_body(TSetVmpInfoReq, 1)
_ev_end

/***********************<<CNC 请求配置画面合成回应  >>************************
*[消息体] 是否配置合成信息
*[消息方向]
*  cns	   ->  cnc
*/
_event( ev_Cn_SetBrdVmp_Ind )
_body(TSetVmpInfoRsp, 1)
_ev_end

/***********************<<CNC 请求广播画面合成  >>************************
*[消息体] 是否广播合成信息
*[消息方向]
*  cns	   <-  cnc
*/
_event( ev_Cn_BrdVmp_Req )
_body(TBrdVmpReq, 1)
_ev_end

/***********************<<CNC 请求广播画面合成回应  >>************************
*[消息体] 是否广播合成信息
*[消息方向]
*  cns	   ->  cnc
*/
_event( ev_Cn_BrdVmp_Ind )
_body(TBrdVmpRsp, 1)
_ev_end

/***********************<<通知CNC的合成器状态  >>************************
*[消息体] 合成器状态
*[消息方向]
*  cns	   ->  cnc
*/
_event( ev_Cn_BrdVmp_Ntfy )
_body(TBrdVmpResArray, 1)
_ev_end

/***********************<<请求保存画面合成预案  >>************************
*[消息体] 画面合成预案
*[消息方向]
*  cns	   <->  cnc , cns <-> ums
* 
*/
_event(ev_Cn_SaveVmpCfg_Cmd)
_body(TTpVmpMemberCfg, 1)
_ev_end

/***********************<<请求保存画面合成预案回应  >>************************
*[消息体] 画面合成预案
*[消息方向]
*  cns	   ->  cnc
*/
_event(ev_CnSaveVmpCfg_Ind)
_body(TTpVmpMemberCfgInd, 1)
_ev_end

/***********************<<开启/关闭ums端语音激励  >>************************
*[消息体] 开启/关闭语音激励
*[消息方向]
*  cns	   <-  cnc
*/
_event(ev_Cn_ConfAMixVacSwitch_Cmd)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<<开启/关闭ums端语音激励回应  >>************************
*[消息体] 开启/关闭语音激励
*[消息方向]
*  cns	   <-  cnc
*/
_event(ev_Cn_ConfAMixVacSwitch_Ind)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<< MCU会议中cnc选看回应 >>********************	
 *[消息体]
 * BOOL  是否选看成功
 * u8 屏序号
 *[消息方向]
 *  cnc <- cns,  cns  <-  mcu
*/
_event(  ev_Cn_MCU_SelView_Ind  )
_body( BOOL ,1 )
_body( u8, 1 )			
_ev_end

/***********************<< cnc选看命令 >>********************	
 *[消息体]
 * TTPSelViewInd 选看参数
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums, cnc <- mcu
*/
	  _event(  ev_Cn_SelView_Ind  )
	  _body( TTPSelViewInd ,1 )			
	  _ev_end

/***********************<< cnc台标显示命令 >>********************	
 *[消息体]
 * TTPShowLogo 台标显示参数
 *[消息方向]
 *  
*/
_event(  ev_CnIsShowLogo_Cmd  )
_body( TTPLogoInfo ,1 )			
_ev_end

/***********************<< cnc台标显示命令回应 >>********************	
 *[消息体]
 * TTPShowLogo 台标显示参数
 *[消息方向]
 *  
*/
_event(  ev_CnIsShowLogo_Ind  )
_body( BOOL ,1 )//是否成功
_body( TTPLogoInfo ,1 )			
_ev_end

/***********************<< cnc台标显示通知 >>********************	
 *[消息体]
 * TTPShowLogo 台标显示参数
 *[消息方向]
 *  
*/
_event(  ev_CnIsShowLogo_Nty  )
_body( TTPLogoInfo ,1 )			
_ev_end

/***********************<< cnc横幅显示命令 >>********************	
 *[消息体]
 * TTPShowBanner 横幅显示参数
 *[消息方向]
 *  
*/
_event(  ev_CnIsShowBanner_Cmd  )
_body( TTPBannerInfo ,1 )			
_ev_end

/***********************<< cnc横幅显示命令回应 >>********************	
 *[消息体]
 * TTPShowBanner 横幅显示参数
 *[消息方向]
 *  
*/
_event(  ev_CnIsShowBanner_Ind  )
_body( BOOL ,1 )//是否成功
_body( TTPBannerInfo ,1 )			
_ev_end

/***********************<< cnc横幅显示通知 >>********************	
 *[消息体]
 * TTPShowBanner 横幅显示参数
 *[消息方向]
 *  
*/
_event(  ev_CnIsShowBanner_Nty  )
_body( TTPBannerInfo ,1 )			
_ev_end

//add by wangqichang
/***********************<< 丢包恢复配置 >>********************	
  *[消息体]
  *EmTpLostPackageRestore 丢包恢复类型
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgLostPackageRestore_Cmd)
  _body(EmTpLostPackageRestore, 1)
  _ev_end
  
  /***********************<< 丢包恢复配置 >>********************	
  *[消息体]
  *EmTpLostPackageRestore 丢包恢复类型
  *BOOL 设置操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgLostPackageRestore_Ind)
  _body(EmTpLostPackageRestore, 1)
  _body(BOOL, 1)
  _ev_end

  /***********************<< 音频设置 >>********************	
  *[消息体]
  *TTPMPAudioInfo 音频设置参数
  //只有AEC、AGC、ANS和3路音频增益的设置有效，其他的配置项设置会被屏蔽掉
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetAudioInfo_Cmd)
  _body(TTPMPAudioInfo, 1)
  _ev_end
  
  /***********************<< 音频设置 >>********************	
  *[消息体]
  *TTPMPAudioInfo 音频设置参数
  *BOOL 设置操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetAudioInfo_Ind)
  _body(TTPMPAudioInfo, 1)
  _body(BOOL, 1)
  _ev_end
  
  /***********************<< 白噪音播放请求 >>********************	
  *[消息体]
  *u32 开启端口号（0、1、2）
  *BOOL 是否开启
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnWhiteNoise_Req)
  _body(u32 , 1)
  _body(BOOL, 1)
  _ev_end
  
  /***********************<< 白噪音播放响应 >>********************	
  *[消息体]
  *BOOL 是否开启*u32 端口
  *BOOL 是否开启
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnWhiteNoise_Rsp)
  _body(u32 , 1)
  _body(BOOL, 1)
  _ev_end
  
  /***********************<< 白噪音播放定时器第一路 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cns
  */
  _event(ev_timer_WhiteNoise_MP1)
  _ev_end
  
  /***********************<< 白噪音播放定时器第二路 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cns
  */
  _event(ev_timer_WhiteNoise_MP2)
  _ev_end
  
  /***********************<< 白噪音播放定时器第三路 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cns
  */
  _event(ev_timer_WhiteNoise_MP3)
  _ev_end
  
  /***********************<< 白噪音播放进度 >>********************	
  *[消息体]
  *u32 编码器编号
  *u8  播放时间
  *[消息方向]
  *  cns -> tptool 
  */
  _event(ev_WhiteNoiseRate_Notify)
  _body(u32 , 1)    //0、1、2
  _body(u8  , 1)    //1 - 89
  _ev_end
  
  /***********************<< 恢复默认音频设置 >>********************	
  *[消息体]
  *TTPMPAudioInfo 音频设置参数
  //只有AEC、AGC、ANS和3路音频增益的设置有效，其他的配置项设置会被屏蔽掉
  //设置数据应该是默认配置
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultAudioInfo_Cmd)
  _body(TTPMPAudioInfo, 1)
  _ev_end
  
  /***********************<< 恢复默认音频设置响应 >>********************	
  *[消息体]
  *BOOL 设置操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultAudioInfo_Ind)
  _body(TTPMPAudioInfo, 1)
  _body(BOOL, 1)
  _ev_end

  /***********************<< 主视频设置请求 >>********************	
  *[消息体]
  *TTPVideoInfoTool    主视频配置项
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetVedioInfoTool_Cmd)
  _body(TTPVideoInfoTool , 1)
  _ev_end
  
  /***********************<< 主视频设置回应 >>********************	
  *[消息体]
  *TTPVideoInfoTool    主视频配置项
  *BOOL                操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetVedioInfoTool_Ind)
  _body(TTPVideoInfoTool , 1)
  _body(BOOL , 1 )
  _ev_end
  
  /***********************<< 主视频恢复默认设置 >>********************	
  *[消息体]
  *TTPVideoInfoTool    主视频配置项
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultVedioInfoTool_Cmd)
  _body(TTPVideoInfoTool , 1)
  _ev_end
  
  /***********************<< 主视频恢复默认设置响应 >>********************	
  *[消息体]
  *BOOL               操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultVedioInfoTool_Ind)
  _body(TTPVideoInfoTool , 1)
  _body(BOOL , 1 )
  _ev_end
  
  /***********************<< 快照命令 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnSetSnapShotCmd )
  _ev_end
  
  /***********************<< 快照回复 >>********************	
  *[消息体]
  *BOOL               操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnSetSnapShotInd )
  _body ( BOOL    , 1    )
  _ev_end

/***********************<< 演示源设置-维护工具 >>********************	
  *[消息体]
  *TVgaInfo  演示源名称
  *TTPDualDisPlayStrategy 双流演示策略结构体
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDisplaySourceTool_Cmd)       
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _ev_end
  
  /***********************<< 演示源设置回应-维护工具 >>********************	
  *[消息体]
  *TVgaInfo  演示源名称
  *TTPDualDisPlayStrategy 双流演示策略结构体
  *EmVgaType 默认演示源
  *BOOL 操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDisplaySourceTool_Ind)
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _body(BOOL , 1)
  _ev_end
  
  /***********************<< 恢复演示源默认设置-维护工具 >>********************	
  *[消息体]
  *TVgaInfo  演示源名称
  *TTPDualDisPlayStrategy 双流演示策略结构体
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultDisplaySourceTool_Cmd)       
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _ev_end
  
  /***********************<< 恢复演示源默认设置回应-维护工具 >>********************	
  *[消息体]
  *TVgaInfo  演示源名称
  *TTPDualDisPlayStrategy 双流演示策略结构体
  *EmVgaType 默认演示源
  *BOOL 操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultDisplaySourceTool_Ind)
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _body(BOOL , 1)
  _ev_end

  /***********************<< 输出图像参数设置 >>********************	
  *[消息体]
  *TTPImageAdjustParam 输出图像参数结构体
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetImageAdjust_Cmd)       
  _body(TTPImageAdjustParam, 3)
  _ev_end
  
  /***********************<< 输出图像参数设置 >>********************	
  *[消息体]
  *TTPImageAdjustParam 输出图像参数结构体
  *BOOL 操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetImageAdjust_Ind)
  _body(TTPImageAdjustParam, 3)
  _body(BOOL , 1)
  _ev_end
  
  /***********************<< 输出图像参数恢复默认设置 >>********************	
  *[消息体]
  *TTPImageAdjustParam 输出图像参数结构体
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultImageAdjust_Cmd)       
  _body(TTPImageAdjustParam, 3)
  _ev_end
  
  /***********************<< 输出图像参数恢复默认设置 >>********************	
  *[消息体]
  *BOOL 操作结果
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultImageAdjust_Ind)
  _body(BOOL , 1)
  _ev_end
//end add

  /***********************<< 主视频源设置请求 >>********************	
  *[消息体]
  *u8                 屏序号
  *EmTPMtVideoPort    主视频源类型
  *[消息方向]
  *  cnc -> cns
  */
  _event(ev_CnSetVedioInfo_Cmd)
  _body(u8, 1)
  _body(EmTPMtVideoPort , 1)
  _ev_end
  
  /***********************<< 主视频设置回应 >>********************	
  *[消息体]
  *u8                 屏序号
  *EmTPMtVideoPort    主视频源类型
  *BOOL                操作结果
  *[消息方向]
  *  cns -> cnc
  */
  _event(ev_CnSetVedioInfo_Ind)
  _body(u8, 1)
  _body(EmTPMtVideoPort , 1)
  _body(BOOL , 1 )
  _ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsextend )
};
#endif
#endif //TPP_EVENT_H
