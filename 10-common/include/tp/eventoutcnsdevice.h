#ifndef _h_eventoutcnsdevice_h__
#define _h_eventoutcnsdevice_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSDEVICEEVENT
{
#endif 

  _ev_segment( outercnsdevice  )

	  //serial begin.
	  /*********************<< ���ô��ڲ���  >>****************************	
 *[��Ϣ��]			 
 *    + EmSerialType     232/422/485
 *    + TSerialCfg
 *
 *[��Ϣ����]
 *
 *   UI          => MtService
 *   MtService   => MtDevice
 */_event(  ev_SerialPortConfigCmd  )
   _body ( EmSerialType ,1 )
   _body ( TSerialCfg   ,1 )
   _ev_end

/*********************<< ����͸����������  >>****************************	
 *[��Ϣ��]			 
 *    + TTransparentSerial
 *[��Ϣ����]
 *
 *   MtService   => UI
 */_event(  ev_TransparentSerialDataCmd )
   _body ( TTransparentSerial ,1 )
   _ev_end
   

/*********************<< ����͸����������  >>****************************	
 *[��Ϣ��]			 
 *    + TTransparentSerial
 *[��Ϣ����]
 *
 *   MtService   => UI
 */_event(  ev_TransparentSerialDataInd)
   _body ( TTransparentSerial ,1 )
   _ev_end
	  //serial end.

	  //file_trans begin.
	  /***********************<< MTC���������ļ� >>********************	
	  *[��Ϣ��]			 
	  *   + u8	�ļ�����
	  *[��Ϣ����]
	  *    MTC => UE
	  */_event(  ev_FTDownLoadReq )
	  _body ( u8    ,1         )
	  _ev_end
	  
	  /***********************<< MTC���������ļ����ܾ� >>********************	
	  *[��Ϣ��]			 
	  *   + u8	ԭ��
	  *[��Ϣ����]
	  *    UE => MTC
	  */_event(  ev_FTDownLoadNACK )
	  _body ( u8    ,1         )
	  _ev_end
	  
	  /***********************<< MTC���������ļ���ͬ�� >>********************	
	  *[��Ϣ��]			 
	  *   + TDownLoadPara	�ļ������б�
	  *[��Ϣ����]
	  *    UE => MTC
	  */_event(  ev_FTDownLoadACK )
	  _body ( TDownLoadPara    ,1         )
	  _ev_end
	  
	  /***********************<< MTC�����ļ���� >>********************	
	  *[��Ϣ��]			 
	  *   
	  *[��Ϣ����]
	  *    MTC => UE
	  */_event(  ev_FTDownLoadFinish  )
      _ev_end
	  //file_trans end.

      //conferenceex begin.
      /**********************<< ������ϢӦ�� >>**************	
 *[��Ϣ��]			 
 *  TMtConfInfo
 *  
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfConfInfoInd   ) 
   _body ( TMtConfInfo, 1 )
   _body ( BOOL, 1 )
   _ev_end


/**********************<< ��ʼ�Զ��໭��ϳ����� >>**************	
 *[��Ϣ��]			 
 * +TMtVMPParam

 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfStartVMPReq   )
   _body( TMtVMPParam, 1 )
   _ev_end


/**********************<< ֹͣ�Զ��໭��ϳ����� >>**************	
 *[��Ϣ��]			 
 * +TMtVMPParam
 *
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfStopVMPReq   )
   _body( TMtVMPParam, 1 )
   _ev_end


/**********************<< ֹͣ�Զ��໭��ϳ�Ӧ�� >>**************	
 *[��Ϣ��]	
 *  +BOOL    TRUE=ͬ��
 *  
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfStopVMPRsp   ) 
   _body ( BOOL      , 1          )
   _ev_end


/**********************<< �����Զ��໭��ϳɲ������� >>**************	
 *[��Ϣ��]	
 *  +TMtVMPParam
 *  
 *  
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfSetVMPParamReq   ) 
   _body ( TMtVMPParam   , 1          )
   _ev_end


/**********************<< ��ȡ�Զ��໭��ϳ�Ӧ�����Ӧ�� >>**************	
 *[��Ϣ��]	
 *  +TMtVMPParam
 *  
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfGetVMPParamRsp   ) 
   _body ( TMtVMPParam   , 1          )
   _ev_end
	  //conferenceex end.

	  //config begin.
	  /***********************<< ����ָʾ>>************************	
 *[��Ϣ��]			 
 *    + TGuideCfg
 *[��Ϣ����]
 *   MtService => UI
 */_event(  ev_CfgGuidInd  )
   _body( TGuideCfg       ,1  ) 
   _ev_end



/***********************<< ��������>>************************	
 *[��Ϣ��]			 
 *    + TGuideCfg
 *[��Ϣ����]
 *    UI< = MtService
 */_event(  ev_CfgGuidCmd  )
   _body( TGuideCfg       ,1  ) 
   _ev_end

/***********************<< ��ʾ����ָʾ >>************************	
 *[��Ϣ��]			 
 *    + TDisplay (TOsdCfg)
 *[��Ϣ����]
 *    MtService => UI
 */_event(  ev_CfgDisplayInd  )
   _body( TOsdCfg    ,1  ) 
   _ev_end

/***********************<< ��̫��ָʾ >>************************	
 *[��Ϣ��]			 
 *    + u8 ��̫������ (0-eth0   )
 *    + TEthnetInfo
 *[��Ϣ����]
 *    MtService => UI
 */_event(  ev_CfgEthnetInd  )
   _body( u8          ,1  )
   _body( TEthnetInfo ,1  )
   _ev_end


/***********************<< ��̫������ >>************************	
 *[��Ϣ��]			 
 *    + u8 ��̫������ (0-eth0   )
 *    + TEthnetInfo
 *[��Ϣ����]
 *    UI< = MtService
 */_event(  ev_CfgEthnetCmd  )
   _body( u8          ,1  )
   _body( TEthnetInfo ,1  )
   _ev_end


/***********************<< PPPOE���� >>************************	
 *[��Ϣ��]			 
 *    + TPPPOECfg
 *[��Ϣ����]
 *    UI< = MtService
 */_event(  ev_CfgPPPOECmd  )
   _body( TPPPOECfg ,1  )
   _ev_end


/***********************<< ����ǽ���� >>************************	
 *[��Ϣ��]			 
 *    + TEmbedFwNatProxy
 *[��Ϣ����]
 *    UI< = MtService
 */_event(  ev_CfgFireWallCmd  )
   _body( TEmbedFwNatProxy ,1  )
   _ev_end

/***********************<< ����Ĭ������ >>**********************	
 *[��Ϣ��]			 
 *  + u32_ip    Ĭ������
  *[��Ϣ����]
 *  UI => MtService
 */_event(  ev_CfgDefaultGatewayCmd )
   _body (  u32_ip    ,1            )
   _ev_end
   
   /***********************<< ����DNS Server >>**********************	
 *[��Ϣ��]			 
 *  + u32_ip    DNS Server ip
 *[��Ϣ����]
 *  MtService => UI
 */_event(  ev_CfgDNSServerCmd )
   _body (  u32_ip    ,1            )
   _ev_end

     /***********************<< DNS Serverָʾ >>**********************	
 *[��Ϣ��]			 
 *  + u32_ip    DNS Server ip
 *[��Ϣ����]
 *  MtService => UI
 */_event(  ev_CfgDNSServerInd )
   _body (  u32_ip    ,1            )
   _ev_end
  
//////////////////////////////////////////////////////////////////////////
//[xujinxing-2006-10-17]
/***********************<< ��Ƕmc���� >>************************	
 *[��Ϣ��]		 
 *  + TInnerMcCfg //mc���õĽṹ    
 *[��Ϣ����
 *   ui => mtservice => mcservice
 */_event ( ev_CfgInnerMcCmd )
  _body ( TInnerMcCfg , 1 )
  _ev_end
  
//////////////////////////////////////////////////////////////////////////
//[xujinxing-2006-10-17]
/***********************<< ��Ƕmc����ָʾ >>************************	
 *[��Ϣ��]		 
 *  + TInnerMcCfg //mc���õĽṹ    
 *[��Ϣ����
 *   ui <= mtservice 
 */_event ( ev_CfgInnerMcInd )
  _body ( TInnerMcCfg , 1 )
  _ev_end
  
  //////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< ��־״ָ̬ʾ >>************************	
*[��Ϣ��]		 
*  + u8    
*[��Ϣ����
*   ui => mtservice 
*/_event ( ev_CfgLogStatusCmd )
_body ( u8 , 1 )
_ev_end

//////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< ��־״ָ̬ʾ >>************************
*[��Ϣ��]		 
*  + u8    
*[��Ϣ����
*   ui <= mtservice 
*/_event ( ev_CfgLogStatusInd )
_body ( u8 , 1 )
_ev_end

//////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< ������־ָʾ >>************************	
*[��Ϣ��]		 
*  + u8    
*[��Ϣ����
*   ui => mtservice 
*/_event ( ev_CfgLogExportCmd )
_body ( u8 , 1 )
_ev_end

//////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< ������־ָʾ >>************************
*[��Ϣ��]		 
*  + u8    
*[��Ϣ����
*   ui <= mtservice 
*/_event ( ev_CfgLogExportInd )
_body ( u8 , 1 )
_ev_end


/***********************<< ����GK�������� >>************************	
 *[��Ϣ��]		 
 *  + TInnerGK     
 *[��Ϣ����
 *   ui <= mtservice 
 */_event ( ev_CfgInnerGKCmd )
  _body( TInnerGKCfg, 1 )
  _ev_end

/***********************<< ����GK����ָʾ >>************************	
 *[��Ϣ��]		 
 *  + TInnerGK     
 *[��Ϣ����
 *   ui <= mtservice 
 */_event ( ev_CfgInnerGKInd )
  _body( TInnerGKCfg, 1 ) 
  _ev_end 


/***********************<< �����øĶ���Ҫ�������� >>************************	
 *[��Ϣ��]		 
   
 *[��Ϣ����
 *   ui => mtservice 
 */_event ( ev_GuideNeedRebootCmd )
  _ev_end

/***********************<< ��������WAN/LANѡ������ >>************************	
 *[��Ϣ��]		 
 * + u8   ������λ���� MT/GK/PXY, 1��ʾѡ��LAN
 *[��Ϣ����
 *   ui => mtservice 
 */_event ( ev_CfgSetNetSelectMaskCmd )
  _body( u8          ,1 )
  _ev_end

/***********************<< ��������WAN/LANѡ��ָʾ >>************************	
 *[��Ϣ��]		 
 * + u8   ������λ���� MT/GK/PXY, 1��ʾѡ��LAN
 *[��Ϣ����
 *   mtservice => ui
 */_event ( ev_CfgSetNetSelectMaskInd )
  _body( u8          ,1 )
  _ev_end
   
/***********************<<  ����ldap��������ַ��ѯ >>********************	
 *[��Ϣ��]
 * +s8 , MT_MAX_LDAPSERVER_NAME_LEN  //�Զ˵�����
 *  
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapServerIPCfgCmd )
   _body( s8 , MT_MAX_LDAPSERVER_NAME_LEN )
   _ev_end

/***********************<<  ����ldap��������ַ��ѯָʾ >>********************	
 *[��Ϣ��]
 * +s8 , MT_MAX_LDAPSERVER_NAME_LEN  //�Զ˵�����
 *  
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapServerIPCfgInd )
   _body( s8 , MT_MAX_LDAPSERVER_NAME_LEN )
   _ev_end
	  //config end.

      //codec begin.
      /***********************<< ����˫����ʾģʽ >>**********************	
 *[��Ϣ��]			 
 *  +EmDualVideoShowMode
 *[��Ϣ����]
 * UI         ->MtService
 */_event( ev_CodecDualShowModeCmd )
   _body ( EmDualVideoShowMode    , 1    )
   _ev_end


/***********************<< ������ʾ����ģʽ >>**********************	
 *[��Ϣ��]			 
 *  +EmDisplayRatio
 *[��Ϣ����]
 * UI         ->MtService
 */_event( ev_CodecDisplayRatioCmd )
   _body ( u8				, 1		)
   _body ( EmDisplayRatio    , 1    )
   _ev_end

/***********************<< ̨���������� >>************************	
 *[��Ϣ��]		 
 * +BOOL
 * +TSymboPoint
 * +s8[MT_MAX_NAME_LEN] 
 *[��Ϣ����]
 *    MtMP => MtService 
 */ _event ( ev_CodecSetLogoCmd )
   _body  ( BOOL, 1  )
   _body  ( TSymboPoint ,1 )
   _body  ( s8   ,MT_MAX_NAME_LEN )
   _ev_end

/***********************<< �����Զ����л�  >>************************
 *[��Ϣ��] 
 *  +BOOL             TRUE/ FALSE
 *[��Ϣ����]
 *
 *    MtService => mtmp
 */_event(  ev_CodecAutoPIPCmd   )
   _body ( BOOL            , 1 )//TRUE=�Զ����л�,FALSE =��
   _ev_end

   _event(  ev_tppreg_timer )
  _ev_end
  
  _event(  ev_tppStartreg_cmd )
  _ev_end

  _event(  ev_tppStopreg_cmd )
  _ev_end
  
  _event(  ev_tppreg_connect_time_out_timer )
  _ev_end
	  //codec end.

      //dhcp begin.
	  /***********************<< DHCP ����ʧ��  >>************************
 *[��Ϣ��]			 
 *  + BOOL  TRUE = ע��ɹ� FALSEʧ��
 *
 *[��Ϣ����]
 *
 *    MtService => UI
 *
 */_event(  ev_DHCPIpDown   )
  _body(u8,1 )/*ȡ��/ʧȥIP��ַ�����ں�*/
  _body(u32_ip,1 )/*ȡ��/ʧȥ��IP��ַ�������ֽ���*/
  _body(u32_ip,1 )/*ȡ��/ʧȥ��IP��ַ�������룬�����ֽ���*/
  _body(u32_ip,1 )/*ȡ��/ʧȥ��Ĭ�����أ������ֽ����п���Ϊ0����Ϊ�е�DHCP-Server��һ��Ϊ�豸ָ��Ĭ������*/
   _ev_end
   
  /***********************<< ����DHCP  >>************************
 *[��Ϣ��]			 
 * BOOL �Ƿ�����DHCP
 *[��Ϣ����]
 *
 *    UI | MTC       => MtService 
 *
 */_event(  ev_CfgDHCPIPCmd   )
	_body(BOOL , 1)
   _ev_end

  /***********************<< ����DHCPָʾ  >>************************
 *[��Ϣ��]			 
 *  ��	
 *[��Ϣ����]
 *
 *    MtService => UI | MTC
 *
 */_event(  ev_CfgDHCPIPInd   )
   _body(BOOL , 1)
   _ev_end
   
  /***********************<< ֪ͨServeci DHCP IP����ɹ�  >>************************
 *[��Ϣ��]			 
 * u32_ip  DHCP IP ��ַ
 * u32_ip  DHCP ���ص�ַ
 *[��Ϣ����]
 *
 *    HDCP server        => MtService 
 *
 */_event(  ev_NewDHCPIpInd   )
  _body(u8,1 )/*ȡ��/ʧȥIP��ַ�����ں�*/
  _body(u32_ip,1 )/*ȡ��/ʧȥ��IP��ַ�������ֽ���*/
  _body(u32_ip,1 )/*ȡ��/ʧȥ��IP��ַ�������룬�����ֽ���*/
  _body(u32_ip,1 )/*ȡ��/ʧȥ��Ĭ�����أ������ֽ����п���Ϊ0����Ϊ�е�DHCP-Server��һ��Ϊ�豸ָ��Ĭ������*/
  _ev_end     
   
 /***********************<< ֪ͨService DHCP IP����ʧ��  >>************************
 *[��Ϣ��]			 
 * u32_ip  DHCP IP ��ַ
 * u32_ip  DHCP ���ص�ַ
 *[��Ϣ����]
 *
 *    HDCP server        => MtService 
 *
 */_event(  ev_RenewDHCPIpFailInd   )
  _body(u8,1 )/*ʧȥIP��ַ�����ں�*/
  _body(u32_ip,1 )/*ʧȥ��IP��ַ�������ֽ���*/
  _body(u32_ip,1 )/*ʧȥ��IP��ַ�������룬�����ֽ���*/
  _body(u32_ip,1 )/*ʧȥ��Ĭ�����أ������ֽ����п���Ϊ0����Ϊ�е�DHCP-Server��һ��Ϊ�豸ָ��Ĭ������*/
  _ev_end     
	  //dhcp end.

	  //extend begin.
	  /***********************<<  ������ֱ������ָʾ  >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ����ð�����ֱ������
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgHDResOutputInd  )
   _body( u32     , 1 )
   _body( u32     , 1 )//Reversed 1
   _body( u32     , 1 )//Reversed 2  
   _ev_end  

/***********************<<  ���ģʽ֡��������ʾ  >>********************	
 *[��Ϣ��]			 
 *     TVideoOutputFrm  ���֡��
 *[��Ϣ����]
 *    MtService <= MTC/MTMP
 */_event( ev_CfgHDVideoFrmInd  )
   _body( TVideoDisplayFrm      , 1 )
   _ev_end
	  //extend end.
	  
/***********************<< �������Թ��ߵ�½������Ϣ >>********************** 
*[��Ϣ��]
*CLoginRequest
*[��Ϣ����]
*    Ӧ���ն� <- cns 
*/
_event( ev_CNPRODUCETESTLOGIN_REQ )
//_body(CLoginRequest ,1)
_ev_end

/***********************<< �������Թ��߲�����������Ϣ >>********************** 
*[��Ϣ��]
*TCnProduceTestMsg
*[��Ϣ����]
*    Ӧ���ն� -> cns 
*/
_event( ev_CNPRODUCETEST_CMD )
_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��ߵ�½��Ӧ�ɹ���Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]
*    Ӧ���ն� -> cns 
*/
_event( ev_CNPRODUCETESTLOGIN_ACK )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��ߵ�½��Ӧʧ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]
*    Ӧ���ն� -> cns 
*/
_event( ev_CNPRODUCETESTLOGIN_NACK )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��߲��Խ����Ϣ >>********************** 
*[��Ϣ��]
*TCnProduceTestMsg
*[��Ϣ����]
*    Ӧ���ն� <- cns 
*/
_event( ev_CNPRODUCETESTRESULT_NTY )
_body(TCnProduceTestMsg ,1)
_body(BOOL , 5)
_ev_end
	  
/***********************<< �������Թ������Ӷ�ʱ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTCONNECT_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��ߵ�½ע�ᶨʱ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLOGIN_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ���ָʾ�ƶ�ʱ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLIGHT_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��߻ָ�Ĭ��ֵ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]Ӧ�� -> cns
*    
*/
_event( ev_CNPRODUCETESTDEFAULT_CMD )
//_body(TCnProduceTestMsg ,1)
_ev_end
 
/***********************<< �������Թ��߻ָ�Ĭ��ֵӦ�� >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTDEFAULT_NTY )
_body(BOOL ,1)
_ev_end

/***********************<< �������Թ��ߺ������IR OUT ����LED�ƶ�ʱ�� >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLED_TIMER )
//_body(BOOL ,1)
_ev_end
 
#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsdevice )
};
#endif
#endif //TPP_EVENT_H
