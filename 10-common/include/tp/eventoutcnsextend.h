#ifndef _h_eventoutcnsextend_h__
#define _h_eventoutcnsextend_h__

#include "cnseventcomm.h"
#include "cnsstruct.h"

#ifndef _MakeTpEventDescription_
enum EmCNSEXTENDEVENT
{
#endif 

  _ev_segment( outercnsextend  )



  /***********************<<  ��������û� >>********************	
  *[��Ϣ����]	CNC	-->  CNS
  *����û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSAddUserReq )
  _ev_end



  
  /***********************<< �ظ�����û�  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *��ӷ���
  */
  _event(  ev_CNSAddUserRet )
  _body(EmTpRet,	1)	//�������
  _ev_end
  



  /***********************<<  ����ɾ���û� >>********************	
  *[��Ϣ����]	CNC	-->  CNS
  *ɾ���û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSDelUserReq )
  _ev_end	
  



  /***********************<<  �ظ�ɾ���û� >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *ɾ������
  */
  _event(  ev_CNSDelUserRet )
  _body(EmTpRet,	1)	//�������
  _ev_end
  



  /***********************<<  �����޸����� >>********************	
  *[��Ϣ����]	CNC	-->  CNS
  *�޸��û����룬����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSChangePWDReq )
  _ev_end	
  



  /***********************<<   �ظ��޸�����  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *�޸ķ���
  */
  _event(  ev_CNSChangePWDRet )
  _body(EmTpRet,	1)	//�������
  _ev_end	
  



  /***********************<< ��һ���û���¼  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSAddUser_Notify )
  _ev_end	
  



  /***********************<< ��һ���û��˳���¼  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSDelUser_Notify )
  _ev_end	
  



  /***********************<< �޸��û�  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSUpdateUser_Notify )
  _ev_end	
  
  

  /***********************<<�û��������ط���¼  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *
  */
  _event(  ev_CNSLoginByOther_Notify )
  _body(u32_ip, 1)
_ev_end	

  
  /***********************<< CNS����CNAdapter����Gkע�� >>********************** 
*[��Ϣ��]
* TTPGkRegistrarCfg	ע�������������Ϣ
* u32					ע����
*[��Ϣ����]
*  CNS	 ->  CnAdapter
*/
_event(  ev_Cn_GkRegister_Cmd )
_body( TTPGkRegistrarCfg, 1 )
_body( u32, 1 )
_ev_end


  /***********************<< ������֪ͨ >>********************** 
*[��Ϣ��]	
* TCnsCapset				������(��������ȷ�������)		
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallAddrCapset_Nty )
//_body( TCnsAddrCapset, 1 )
_body( TTPCnUnpackStream, CNS_CALL_MAX_CHANNEL )
_body( u16, 1 )
_body( u32, 1 )
_body( u8, 1 )
_ev_end

  /***********************<< ˫��������֪ͨ >>********************** 
*[��Ϣ��]	
* TCnsCapset				������(��������ȷ�������)		
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallDualCapset_Nty )
_body( TTPDualCap, 1 )
_ev_end

 /***********************<< ��Ƶ����֪ͨ >>********************** 
*[��Ϣ��]	
* EmTpAudioFormat				��Ƶ����		
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_AudioFormat_Nty )
_body( EmTpAudioFormat, 1 )
_ev_end

/***********************<< cncѡ������ >>********************	
 *[��Ϣ��]
 * TTPSelViewReq ѡ������
 *[��Ϣ����]
 *  cnc -> cns, cns	 ->  ums, cns-> mcu
*/
	  _event(  ev_Cn_SelView_Req  )
	  _body( TTPSelViewReq ,1 )			
	  _ev_end

/***********************<< cncѡ������ >>********************	
 *[��Ϣ��]
 * TTPSelViewInd ѡ������
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums
*/
	  _event(  ev_UMS_CNC_ByCNS_SelView_Ind  )
	  _body( TTPSelViewInd ,1 )			
	  _ev_end

/***********************<< cncѡ������ >>********************	
 *[��Ϣ��]
 * TTPSelViewInd ѡ������
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums
*/
	  _event(  ev_UMS_CNC_ByCNS_SelView_Ntfy  )
	  _body( TTPSelViewNtfy ,1 )			
	  _ev_end

/***********************<< ����������������  >>********************	
  *[��Ϣ��]
  *TTpEncryptKey ������Ϣ
  *[��Ϣ����]	  CNC	-->  CNS
  *
  */
  _event( ev_tppSetEncryptInfo_Cmd )
  _body( TTpEncryptKey, 1 )
  _ev_end
  
  /***********************<< ������������֪ͨ  >>********************	
  *[��Ϣ��]
  *TTpEncryptKey ������Ϣ
  *[��Ϣ����]	  CNS	-->  CNC
  *
  */
  _event( ev_tppSetEncryptInfo_Nty )
  _body( TTpEncryptKey, 1 )
  _ev_end

   /***********************<< ��������������Ӧ  >>********************	
  *[��Ϣ��]
  *TTpEncryptKey ������Ϣ
  *BOOL ������Ϣ�Ƿ�д�������ļ�
  *[��Ϣ����]	  CNS	-->  CNC
  *
  */
  _event( ev_tppSetEncryptInfo_Ind )
  _body( TTpEncryptKey, 1 )
  _body( BOOL, 1 )
_ev_end

// ���ݻ���ģ�����Tpad��cns������Ϣ add by niu 2014-03-12

 /***********************<<  Tpad֪ͨ���˵�CNS�Ѿ������װ���� >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cnc(Tpad) -> cns 
  */_event( ev_tpp_DSIPAddr_Nty )
  _ev_end

  /***********************<<  Cns���Tpad�û� >>********************	
  *[��Ϣ��] 0��������뿪���ݻ����ʶ 1����ѯ���ط������ݻ���Tpad�û���ʶ
  *[��Ϣ����]
  *  cns -> cns(cnue) 
  */_event( ev_tpp_GetConfTpadUser_Cmd )
  _body( u8 , 1 )
  _ev_end

  /***********************<<  Cnue���Tpad�û���֪ͨ���˵�CNS >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns(cnue) -> cns 
  */_event( ev_tpp_GetConfTpadUser_Ind )
  _body( u8 , 1 )
  _body( TTPTPadList , 1 )
  _ev_end

  /***********************<<  Cnue���Tpad�û���֪ͨ���˵�CNS >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns(cnue) -> cns 
  */_event( ev_tpp_NewTpadJoinConf_Nty )
  _ev_end

  /***********************<< ����CNS�������ݻ��������IP��ַ֪ͨ���˿����װ����Tpad���������ӵ���������ϵ�Tpad����װ���� >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cnc(Tpad) 
  */_event( ev_tpp_JoinWBConf_Cmd )
  _body( TTPDataConfInfo , 1 )
  _body( TTPCnsConfStatus, 1)//���ݻ�������
  _ev_end

//   /***********************<< ����װ����ɹ���Tpad�ѻ���״̬����Ϊ�ڻ�״̬ >>********************	
//   *[��Ϣ��]
//   *[��Ϣ����]
//   *  cnc(Tpad) -> cns 
//   */_event( ev_tpp_JoinWBConf_Ind )
//   _body( u32 , 1 )
//   _ev_end

  /***********************<< �������ʻ��飬CNS֪ͨ�������������������Tpad�뿪�װ���� >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cnc(Tpad) 
  */_event( ev_tpp_LeaveWBConf_Nty )
  _body( TTPDataConfInfo , 1 )
   _body( TTPCnsConfStatus, 1)//���ݻ�������
  _ev_end

  /***********************<< �»������������Tpad�Ƿ���� >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cnc(Tpad) 
  */_event( ev_tpp_NewConfCall_Req )
  _body( TTPCnsConfStatus, 1)//���ݻ�������
  _ev_end

  /***********************<< ���ݷ�����������������  >>********************	
  *[��Ϣ��]
  *u32_ip   ���ݷ�����������Ϣ
  *[��Ϣ����]	  TPad	-->  CNS
  *
  */
  _event( ev_tppSetDataServerInfo_Cmd )
  _body( TTPDataConfInfo, 1 )
  _ev_end
  
  /***********************<< ���ݷ�������������֪ͨ  >>********************	
  *[��Ϣ��]
  *u32_ip   ���ݷ�����������Ϣ
  *[��Ϣ����]	  CNS	-->  TPad
  *
  */
  _event( ev_tppSetDataServerInfo_Nty )
  _body( TTPDataConfInfo, 1 )
  _ev_end
  
  /***********************<< ���ݷ���������������Ӧ  >>********************	
  *[��Ϣ��]
  *u32_ip   ���ݷ�����������Ϣ
  *BOOL ���ݷ����������Ƿ�ɹ�
  *[��Ϣ����]	  CNS	-->  TPad
  *
  */
  _event( ev_tppSetDataServerInfo_Ind )
  _body( TTPDataConfInfo, 1 )
  _body( BOOL, 1 )
  _ev_end

/***********************<< ֪ͨ���ݻ������Ƶ�TPad  >>********************	
  *[��Ϣ��]
  *u32_ip   ���ݷ�����������Ϣ
  *BOOL ���ݷ����������Ƿ�ɹ�
  *[��Ϣ����]	  CNS	-->  TPad
  *
  */
  _event( ev_tpp_DataConfName_Nty )
  _body( TTPCnsConfStatus, 1 )
  _ev_end

    /***********************<< Tpad�Ƿ�������ݻ���״̬֪ͨ >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cnc(Tpad) -> cns 
  */
  _event( ev_tppDataConfState_Nty )
  _body( BOOL , 1 )
  _ev_end
  //end by niu

  /***********************<<˫������֪ͨ��Կ  >>************************
*[��Ϣ��] ����˫��֪ͨ��Կ
*[��Ϣ����]
*  cns	   -> cnc
*/
_event( ev_tppCodecEncryptKey_Nty )
_body( TTpEncryptKey, 1 )
_ev_end

/***********************<<��ͣ��ѯ  >>************************
*[��Ϣ��] �Ƿ���ͣ��ѯ
*[��Ϣ����]
*  cns	   <-  cnc
*/
_event( ev_Cn_Conf_SuspendPoll_Req )
_body ( BOOL32, 1 )
_ev_end

/***********************<<��ͣ��ѯ���  >>************************
*[��Ϣ��] ��ͣ��ѯ���
*[��Ϣ����]
*  cns	   ->  cnc
*/
_event( ev_Cn_Conf_SuspendPoll_Ind )
_body ( EmTPPollResult, 1 ) //���
_ev_end

/***********************<<������ѯ�б�  >>************************
*[��Ϣ��] ������ѯ�б�
*[��Ϣ����]
*  cns	   <->  cnc
*/
_event(  ev_Cn_UpdateConfTurnlist_Nty )
_body ( TTpPollListNtfy , 1 )	
_ev_end

/***********************<<������ѯ�б��Ӧ  >>************************
*[��Ϣ��] ������ѯ�б���
*[��Ϣ����]
*  cns	   ->  cnc
*/
_event(  ev_Cn_UpdateConfTurnlist_Ind )
_body ( TTpPollListInd , 1 )	
_ev_end

/***********************<<CNC ���� ռ�úϳ�  >>************************
*[��Ϣ��] �Ƿ�ռ�úϳ���Ϣ
*[��Ϣ����]
*  cns	   <-  cnc
*/
_event( ev_Cn_RervesBrdVmp_Req )
_body(TRersvesEqpReq, 1)
_ev_end

/***********************<<CNC ���� ռ�úϳɻ�Ӧ  >>************************
*[��Ϣ��] �Ƿ�ռ�úϳ���Ϣ
*[��Ϣ����]
*  cns	   ->  cnc
*/
_event( ev_Cn_RervesBrdVmp_Ind )
_body(TRersvesEqpRsp, 1)
_ev_end

/***********************<<CNC �������û���ϳ�  >>************************
*[��Ϣ��] �Ƿ����úϳ���Ϣ
*[��Ϣ����]
*  cns	   <-  cnc
*/
_event( ev_Cn_SetBrdVmp_Req )
_body(TSetVmpInfoReq, 1)
_ev_end

/***********************<<CNC �������û���ϳɻ�Ӧ  >>************************
*[��Ϣ��] �Ƿ����úϳ���Ϣ
*[��Ϣ����]
*  cns	   ->  cnc
*/
_event( ev_Cn_SetBrdVmp_Ind )
_body(TSetVmpInfoRsp, 1)
_ev_end

/***********************<<CNC ����㲥����ϳ�  >>************************
*[��Ϣ��] �Ƿ�㲥�ϳ���Ϣ
*[��Ϣ����]
*  cns	   <-  cnc
*/
_event( ev_Cn_BrdVmp_Req )
_body(TBrdVmpReq, 1)
_ev_end

/***********************<<CNC ����㲥����ϳɻ�Ӧ  >>************************
*[��Ϣ��] �Ƿ�㲥�ϳ���Ϣ
*[��Ϣ����]
*  cns	   ->  cnc
*/
_event( ev_Cn_BrdVmp_Ind )
_body(TBrdVmpRsp, 1)
_ev_end

/***********************<<֪ͨCNC�ĺϳ���״̬  >>************************
*[��Ϣ��] �ϳ���״̬
*[��Ϣ����]
*  cns	   ->  cnc
*/
_event( ev_Cn_BrdVmp_Ntfy )
_body(TBrdVmpResArray, 1)
_ev_end

/***********************<<���󱣴滭��ϳ�Ԥ��  >>************************
*[��Ϣ��] ����ϳ�Ԥ��
*[��Ϣ����]
*  cns	   <->  cnc , cns <-> ums
* 
*/
_event(ev_Cn_SaveVmpCfg_Cmd)
_body(TTpVmpMemberCfg, 1)
_ev_end

/***********************<<���󱣴滭��ϳ�Ԥ����Ӧ  >>************************
*[��Ϣ��] ����ϳ�Ԥ��
*[��Ϣ����]
*  cns	   ->  cnc
*/
_event(ev_CnSaveVmpCfg_Ind)
_body(TTpVmpMemberCfgInd, 1)
_ev_end

/***********************<<����/�ر�ums����������  >>************************
*[��Ϣ��] ����/�ر���������
*[��Ϣ����]
*  cns	   <-  cnc
*/
_event(ev_Cn_ConfAMixVacSwitch_Cmd)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<<����/�ر�ums������������Ӧ  >>************************
*[��Ϣ��] ����/�ر���������
*[��Ϣ����]
*  cns	   <-  cnc
*/
_event(ev_Cn_ConfAMixVacSwitch_Ind)
_body(TConfAuxMixVacOpr, 1)
_ev_end

/***********************<< MCU������cncѡ����Ӧ >>********************	
 *[��Ϣ��]
 * BOOL  �Ƿ�ѡ���ɹ�
 * u8 �����
 *[��Ϣ����]
 *  cnc <- cns,  cns  <-  mcu
*/
_event(  ev_Cn_MCU_SelView_Ind  )
_body( BOOL ,1 )
_body( u8, 1 )			
_ev_end

/***********************<< cncѡ������ >>********************	
 *[��Ϣ��]
 * TTPSelViewInd ѡ������
 *[��Ϣ����]
 *  cnc <- cns, cns	 <-  ums, cnc <- mcu
*/
	  _event(  ev_Cn_SelView_Ind  )
	  _body( TTPSelViewInd ,1 )			
	  _ev_end

/***********************<< cnc̨����ʾ���� >>********************	
 *[��Ϣ��]
 * TTPShowLogo ̨����ʾ����
 *[��Ϣ����]
 *  
*/
_event(  ev_CnIsShowLogo_Cmd  )
_body( TTPLogoInfo ,1 )			
_ev_end

/***********************<< cnc̨����ʾ�����Ӧ >>********************	
 *[��Ϣ��]
 * TTPShowLogo ̨����ʾ����
 *[��Ϣ����]
 *  
*/
_event(  ev_CnIsShowLogo_Ind  )
_body( BOOL ,1 )//�Ƿ�ɹ�
_body( TTPLogoInfo ,1 )			
_ev_end

/***********************<< cnc̨����ʾ֪ͨ >>********************	
 *[��Ϣ��]
 * TTPShowLogo ̨����ʾ����
 *[��Ϣ����]
 *  
*/
_event(  ev_CnIsShowLogo_Nty  )
_body( TTPLogoInfo ,1 )			
_ev_end

/***********************<< cnc�����ʾ���� >>********************	
 *[��Ϣ��]
 * TTPShowBanner �����ʾ����
 *[��Ϣ����]
 *  
*/
_event(  ev_CnIsShowBanner_Cmd  )
_body( TTPBannerInfo ,1 )			
_ev_end

/***********************<< cnc�����ʾ�����Ӧ >>********************	
 *[��Ϣ��]
 * TTPShowBanner �����ʾ����
 *[��Ϣ����]
 *  
*/
_event(  ev_CnIsShowBanner_Ind  )
_body( BOOL ,1 )//�Ƿ�ɹ�
_body( TTPBannerInfo ,1 )			
_ev_end

/***********************<< cnc�����ʾ֪ͨ >>********************	
 *[��Ϣ��]
 * TTPShowBanner �����ʾ����
 *[��Ϣ����]
 *  
*/
_event(  ev_CnIsShowBanner_Nty  )
_body( TTPBannerInfo ,1 )			
_ev_end

//add by wangqichang
/***********************<< �����ָ����� >>********************	
  *[��Ϣ��]
  *EmTpLostPackageRestore �����ָ�����
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgLostPackageRestore_Cmd)
  _body(EmTpLostPackageRestore, 1)
  _ev_end
  
  /***********************<< �����ָ����� >>********************	
  *[��Ϣ��]
  *EmTpLostPackageRestore �����ָ�����
  *BOOL ���ò������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgLostPackageRestore_Ind)
  _body(EmTpLostPackageRestore, 1)
  _body(BOOL, 1)
  _ev_end

  /***********************<< ��Ƶ���� >>********************	
  *[��Ϣ��]
  *TTPMPAudioInfo ��Ƶ���ò���
  //ֻ��AEC��AGC��ANS��3·��Ƶ�����������Ч�����������������ûᱻ���ε�
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetAudioInfo_Cmd)
  _body(TTPMPAudioInfo, 1)
  _ev_end
  
  /***********************<< ��Ƶ���� >>********************	
  *[��Ϣ��]
  *TTPMPAudioInfo ��Ƶ���ò���
  *BOOL ���ò������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetAudioInfo_Ind)
  _body(TTPMPAudioInfo, 1)
  _body(BOOL, 1)
  _ev_end
  
  /***********************<< �������������� >>********************	
  *[��Ϣ��]
  *u32 �����˿ںţ�0��1��2��
  *BOOL �Ƿ���
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnWhiteNoise_Req)
  _body(u32 , 1)
  _body(BOOL, 1)
  _ev_end
  
  /***********************<< ������������Ӧ >>********************	
  *[��Ϣ��]
  *BOOL �Ƿ���*u32 �˿�
  *BOOL �Ƿ���
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnWhiteNoise_Rsp)
  _body(u32 , 1)
  _body(BOOL, 1)
  _ev_end
  
  /***********************<< ���������Ŷ�ʱ����һ· >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cns
  */
  _event(ev_timer_WhiteNoise_MP1)
  _ev_end
  
  /***********************<< ���������Ŷ�ʱ���ڶ�· >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cns
  */
  _event(ev_timer_WhiteNoise_MP2)
  _ev_end
  
  /***********************<< ���������Ŷ�ʱ������· >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cns
  */
  _event(ev_timer_WhiteNoise_MP3)
  _ev_end
  
  /***********************<< ���������Ž��� >>********************	
  *[��Ϣ��]
  *u32 ���������
  *u8  ����ʱ��
  *[��Ϣ����]
  *  cns -> tptool 
  */
  _event(ev_WhiteNoiseRate_Notify)
  _body(u32 , 1)    //0��1��2
  _body(u8  , 1)    //1 - 89
  _ev_end
  
  /***********************<< �ָ�Ĭ����Ƶ���� >>********************	
  *[��Ϣ��]
  *TTPMPAudioInfo ��Ƶ���ò���
  //ֻ��AEC��AGC��ANS��3·��Ƶ�����������Ч�����������������ûᱻ���ε�
  //��������Ӧ����Ĭ������
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultAudioInfo_Cmd)
  _body(TTPMPAudioInfo, 1)
  _ev_end
  
  /***********************<< �ָ�Ĭ����Ƶ������Ӧ >>********************	
  *[��Ϣ��]
  *BOOL ���ò������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultAudioInfo_Ind)
  _body(TTPMPAudioInfo, 1)
  _body(BOOL, 1)
  _ev_end

  /***********************<< ����Ƶ�������� >>********************	
  *[��Ϣ��]
  *TTPVideoInfoTool    ����Ƶ������
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetVedioInfoTool_Cmd)
  _body(TTPVideoInfoTool , 1)
  _ev_end
  
  /***********************<< ����Ƶ���û�Ӧ >>********************	
  *[��Ϣ��]
  *TTPVideoInfoTool    ����Ƶ������
  *BOOL                �������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetVedioInfoTool_Ind)
  _body(TTPVideoInfoTool , 1)
  _body(BOOL , 1 )
  _ev_end
  
  /***********************<< ����Ƶ�ָ�Ĭ������ >>********************	
  *[��Ϣ��]
  *TTPVideoInfoTool    ����Ƶ������
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultVedioInfoTool_Cmd)
  _body(TTPVideoInfoTool , 1)
  _ev_end
  
  /***********************<< ����Ƶ�ָ�Ĭ��������Ӧ >>********************	
  *[��Ϣ��]
  *BOOL               �������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultVedioInfoTool_Ind)
  _body(TTPVideoInfoTool , 1)
  _body(BOOL , 1 )
  _ev_end
  
  /***********************<< �������� >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnSetSnapShotCmd )
  _ev_end
  
  /***********************<< ���ջظ� >>********************	
  *[��Ϣ��]
  *BOOL               �������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnSetSnapShotInd )
  _body ( BOOL    , 1    )
  _ev_end

/***********************<< ��ʾԴ����-ά������ >>********************	
  *[��Ϣ��]
  *TVgaInfo  ��ʾԴ����
  *TTPDualDisPlayStrategy ˫����ʾ���Խṹ��
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDisplaySourceTool_Cmd)       
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _ev_end
  
  /***********************<< ��ʾԴ���û�Ӧ-ά������ >>********************	
  *[��Ϣ��]
  *TVgaInfo  ��ʾԴ����
  *TTPDualDisPlayStrategy ˫����ʾ���Խṹ��
  *EmVgaType Ĭ����ʾԴ
  *BOOL �������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDisplaySourceTool_Ind)
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _body(BOOL , 1)
  _ev_end
  
  /***********************<< �ָ���ʾԴĬ������-ά������ >>********************	
  *[��Ϣ��]
  *TVgaInfo  ��ʾԴ����
  *TTPDualDisPlayStrategy ˫����ʾ���Խṹ��
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultDisplaySourceTool_Cmd)       
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _ev_end
  
  /***********************<< �ָ���ʾԴĬ�����û�Ӧ-ά������ >>********************	
  *[��Ϣ��]
  *TVgaInfo  ��ʾԴ����
  *TTPDualDisPlayStrategy ˫����ʾ���Խṹ��
  *EmVgaType Ĭ����ʾԴ
  *BOOL �������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultDisplaySourceTool_Ind)
  _body(TVgaInfo, 5)
  _body(TTPDualDisplayStrategy, 1)
  _body(TVgaInfo, 1)
  _body(BOOL , 1)
  _ev_end

  /***********************<< ���ͼ��������� >>********************	
  *[��Ϣ��]
  *TTPImageAdjustParam ���ͼ������ṹ��
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetImageAdjust_Cmd)       
  _body(TTPImageAdjustParam, 3)
  _ev_end
  
  /***********************<< ���ͼ��������� >>********************	
  *[��Ϣ��]
  *TTPImageAdjustParam ���ͼ������ṹ��
  *BOOL �������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetImageAdjust_Ind)
  _body(TTPImageAdjustParam, 3)
  _body(BOOL , 1)
  _ev_end
  
  /***********************<< ���ͼ������ָ�Ĭ������ >>********************	
  *[��Ϣ��]
  *TTPImageAdjustParam ���ͼ������ṹ��
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnSetDefaultImageAdjust_Cmd)       
  _body(TTPImageAdjustParam, 3)
  _ev_end
  
  /***********************<< ���ͼ������ָ�Ĭ������ >>********************	
  *[��Ϣ��]
  *BOOL �������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnSetDefaultImageAdjust_Ind)
  _body(BOOL , 1)
  _ev_end
//end add

  /***********************<< ����ƵԴ�������� >>********************	
  *[��Ϣ��]
  *u8                 �����
  *EmTPMtVideoPort    ����ƵԴ����
  *[��Ϣ����]
  *  cnc -> cns
  */
  _event(ev_CnSetVedioInfo_Cmd)
  _body(u8, 1)
  _body(EmTPMtVideoPort , 1)
  _ev_end
  
  /***********************<< ����Ƶ���û�Ӧ >>********************	
  *[��Ϣ��]
  *u8                 �����
  *EmTPMtVideoPort    ����ƵԴ����
  *BOOL                �������
  *[��Ϣ����]
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
