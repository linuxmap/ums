#ifndef _h_eventtpsys_h__
#define _h_eventtpsys_h__


#include "tpeventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsInnersys
{
#endif

	_ev_segment( tpsys )

   //mtsysevent begin
   /***********************<< ϵͳ��ʼ����Ϣ >>**********************	
 *[��Ϣ��]			 
 *  + u32 ����1
 *  + u32 ����2
 *[��Ϣ����]
 *
 */_event( ev_SysInitCmd )
   _body ( u32    , 1    )
   _body ( u32    , 1    )
   _ev_end

/***********************<< Ӧ�ö����ʼ�����ָʾ >>**********************	
 *[��Ϣ��]			 
 *  + u8    appid
 *  + u8    instid
 *  + BOOL  TRUE =��ʼ���ɹ� FALSE=��ʼ��ʧ��
 *[��Ϣ����]
 *
 */_event(  ev_SysInitInd )
   _ev_end


 /***********************<< Ӧ���˳���Ϣ >>********************	
 *[��Ϣ��]			 
 * ����Ϣ��
 *[��Ϣ����]
 *
 */_event(  ev_SysExitCmd  )
   _ev_end


/***********************<< Ӧ���˳���Ϣָʾ >>********************	
 *[��Ϣ��]			 
 * ����Ϣ��
 *[��Ϣ����]
 *
 */_event(  ev_SysExitInd  )
   _ev_end


/***********************<< ϵͳӦ��ģ�鿪ʼ��ʼ�� >> **************	
 *[��Ϣ��]			 
 * ����Ϣ��
 *[��Ϣ����]
 *
 */_event(  ev_SysModuleStartCmd )
   _ev_end


/***********************<< ϵͳ��Ӧ��ģ��ʼ�����ָʾ >> **************	
 *[��Ϣ��]			 
 * ����Ϣ��
 *[��Ϣ����]
 *
 */_event(  ev_SysAppInitCompleteInd )
   _ev_end

/***********************<< �ն��������� >>********************	
 *[��Ϣ��]			 
 * ����Ϣ��
 *[��Ϣ����]
 *
 */_event(  ev_SysRebootCmd  )
   _ev_end
      
/***********************<< PC˫�������½ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysPCLoginInd  )
   _ev_end

/***********************<< PC˫������˳�ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysPCLogoutInd )
   _ev_end

/***********************<< �ն˿���̨��½ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysMTCLoginInd  )
   _ev_end

/***********************<< �ն˿���̨��½ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysMTCLogoutInd )
   _ev_end

/******************<< �ն˿���̨�������ݷ�����Ϣ  >>**********************	
 *[��Ϣ��]			 
 *  BOOL   ����״̬ 0 key down 1 key up
 *  u8    �������� OLD_REMOTE NEW_REMOTE UNKNOW_REMOTE 
 *  u8    ��ֵ
 *  u16   ��������
 *[��Ϣ����]
 *   UTC  => MTUE
 *   MTUE => UI
 */_event( ev_SysMTCKeyboardContent  )
   _body(  BOOL   ,   1        )
   _body(  u8     ,   1        )
   _body(  u8     ,   1        )
   _body(  u16    ,   1        )
   _ev_end

 /***********************<< ֪ͨ��������>>************************	
 *[��Ϣ��]			 
 *    + u8     node_ui/node_mtc
 *
 *[��Ϣ����]
 *   �ڲ�
 */_event(  ev_NotifyObserverCmd  )
   _body ( u8    ,1               )
   _ev_end


/***********************<< ��������ģ��>>************************	
 *[��Ϣ��]			 
 *    + u8     node_ui/node_mtc
 *
 *[��Ϣ����]
 *   �ڲ�
 */_event(  ev_ModuleStartupCmd  )
   _body ( u8    ,1               )
   _ev_end


/***********************<< ����Ϣ��ҳ��ʱ����Ϣ>>************************	
 *[��Ϣ��]			 
 *     
 *
 *[��Ϣ����]
 *   �ڲ�
 */_event(  ev_SMSPageTieleInd   )
   _ev_end

/***********************<< ��̬�ı���ʱ����Ϣ>>************************	
 *[��Ϣ��]			 
 *     
 *
 *[��Ϣ����]
 *   �ڲ�
 */_event(  ev_SMSStaticTitleInd   )
   _ev_end
   
/***********************<< �����������     >>**********************	
 *[��Ϣ��]			 
 *  ��  
 *[��Ϣ����]
 *    MtService = > embed UI
 */_event( ev_ApplySleepCmd  )
   _ev_end

/***********************<< �ն˴�������  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   UI = > MtService
 */_event( ev_MtSleepCmd  )
   _ev_end

/***********************<< �ն˴�����������  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   UI = > MtService
 */_event( ev_MtWakeupCmd  )
   _ev_end
/***********************<< ����״ָ̬ʾ  >>**********************	
 *[��Ϣ��]			 
 *  u8     0 = ���������
 1 = ���ڴ��� 
 2 = ����
 3 = ���ڻ���
 4 = ����
		   5 = �ȴ�����
 *[��Ϣ����]
 *    MtService = > embed UI
 */_event( ev_SleepStateInd  )
    _body(  u8   , 1        )
   _ev_end

/******************<< UEһ�������յ�����������Ϣ��ָʾ  >>**********************	
 *[��Ϣ��]			 
 *  u32   �յ���Ϣ��
 *[��Ϣ����]
 *   UE => MtService 
 */_event( ev_UserOperationInd  )
   _body(  u32   , 1        )
   _ev_end



/******************<< IP��ͻָʾ/���ڷ�T2  >>**********************	
 *[��Ϣ��]			 
 *  BOOL   TRUE=��ͻ
 *[��Ϣ����]
 *   MtService => MTC/MTUI
 */_event( ev_IPConflictInd  )
   _body(  BOOL   , 1        )
   _ev_end

/******************<< IP��ͻ��ʱ��  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MTC/MTUI
 */_event( ev_IPConflictTimer )
   _ev_end

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/******************<< IP��ͻ�ϱ�ָʾ/����T2  >>**********************	
 *[��Ϣ��]			 
 *  BOOL   Master�Ƿ��ͻ
 *  u32    Master��ͻIP
 *  BOOL   Slave�Ƿ��ͻ
 *  u32    Slave��ͻIP
 *[��Ϣ����]
 *   MtService => MTC/MTUI
 */_event( ev_T2IPConflictInd  )
   _body (  BOOL   , 1        )
   _body (  u32    , 1        )
   _body (  BOOL   , 1        )
   _body (  u32    , 1        )
   _ev_end

/******************<< IP��ͻָʾ/����T2��davinci >>**********************	
 *[��Ϣ��]			 
 *  s8   MAC��ַ
 *  u32  ��ͻIP
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2IPConflictMasterInd  )
   _body(  s8     , 6        )
   _body(  u32    , 1        )
   _ev_end

/******************<< IP��ͻָʾ/����T2��davinci >>**********************	
 *[��Ϣ��]			 
 *  s8   MAC��ַ
 *  u32  ��ͻIPͻ
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2IPConflictSlaveInd  )
   _body(  s8     , 6        )
   _body(  u32    , 1        )
   _ev_end 

/******************<< Master IP��ͻ��ʱ��  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2MasterIPConflictTimer )
   _ev_end

/******************<< Slave IP��ͻ��ʱ��1  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2SlaveIPConflictTimer1 )
   _ev_end

/******************<< Slave IP��ͻ��ʱ��2  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2SlaveIPConflictTimer2 )
   _ev_end

/******************<< Slave IP��ͻ��ʱ��3  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2SlaveIPConflictTimer3 )
   _ev_end
#if 0
/******************<< Slave IP��ͻ��ʱ��4  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2SlaveIPConflictTimer4 )
   _ev_end

/******************<< Slave IP��ͻ��ʱ��5  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2SlaveIPConflictTimer5 )
   _ev_end

/******************<< Slave IP��ͻ��ʱ��6  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2SlaveIPConflictTimer6 )
   _ev_end
#endif
/***********************<< �ͻ��������¼��Ϣ >>********************	
 *[��Ϣ��]			 
 *   + u8[32]         //ͨ�����ݽṹ�汾����
 *   + CLoginRequest
 *[��Ϣ����]
 *    MTC => UE
 */_event(  ev_UMLoginReq   )
   _ev_end



/***********************<< �ͻ��������¼ȷ��Ӧ�� >>********************	
 *[��Ϣ��]			 
 *   ����Ϣ��
 *[��Ϣ����]
 *   UE <= MTC
 */_event(  ev_UMLoginAck   )
   _ev_end



 /***********************<< �ͻ��������¼�ܾ�Ӧ�� >>********************	
 *[��Ϣ��]
 *   + CUserFullInfo  //�ѵ�½�û���Ϣ
 *   + u8[32]         //ͨ�����ݽṹ�汾����
 *   + u8             // ��½ʧ��ԭ��   0=�û�����ģ�� 1=�����û���½ 2������汾��ƥ��
 *   + u16            // �û�����ģ������
 *   + u32            //�ѵ�½�û�IP
 *[��Ϣ����]
 *   UE => MTC
 */_event(  ev_UMLoginNack   )
   _ev_end

/******************<< Slave IP��ͻ��ʱ��7  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2SlaveIPConflictTimer7 )
   _ev_end  

/******************<< T2 IP��ͻѭ����鶨ʱ��  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_T2CheckIPConflictTimer )
   _ev_end
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



/******************<< ��̫���ڶ�����ⶨʱ��  >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *   MtService => MtService
 */_event( ev_EthnetStatusTimer )
   _ev_end

/*********************** << CPU idle ���ڴ��ѯ�ӿ� >>************************
 *[��Ϣ��]    
 *            ��
 *[��Ϣ����]
 *
 *                UI    =   >     MtService
 */_event(ev_GetSystemStateCmd)
   _ev_end
 /***********************<<CPU idle ���ڴ��ѯ�ӿ�>> ************************
 *[��Ϣ��]    
 *            +u8             //��ǰcpu�Ŀ��аٷֱ�
 *            +u32             //ϵͳ�ܵ�sdram,��λ  �ֽ�Ϊ��λ
 *            +u32            //��ǰ���е��ڴ��С���ֽ�Ϊ��λ
 *            +u32            //��ǰ�ѷ�����ڴ��С���ֽ�Ϊ��λ
 *[��Ϣ����]
 *
 *                MtService    =   >     UI
 */_event(ev_GetSystemStateInd)
     _body    (u8                          ,  1 )
     _body    (u32                         ,  1 )
     _body    (u32                         ,  1 )
     _body    (u32                         ,  1 )
   _ev_end

/***********************<<�ն���Ϣ>> ************************
 *[��Ϣ��]    
 *            +u8             //Ӳ���汾��
 *            +EmMtOSType     //����ϵͳ����
 *            +s8             //����ϵͳ�汾
 *            +s8             //����汾��
 *            +s8             //MAC��ַ
 
 *[��Ϣ����]
 *
 *            MtService    =   >     UI
 */_event(ev_TerminalInformationInd)
     _body    (u8                         ,   1  )
	 _body    (u8						  ,   1  )
	 _body    (EmMtOSType                 ,   1  )
     _body    (s8                         ,   256 )
     _body    (s8                         ,   256 )
     _body    (s8                         ,   256 )
   _ev_end
   
/**********************<< mt�豸����ָʾ  >>********************	
 *[��Ϣ��]
 * +TMtEquipmentCapset  //mt�豸������
 *[��Ϣ����]
 *    mtservice  = > ui/mtc
 */_event( ev_MtEquipmentCapsetInd )
   _body( TMtEquipmentCapset, 1 )
   _ev_end

/**********************<< ��ϼ��ϱ�  >>********************	
 *[��Ϣ��]
 * +TMtEquipmentCapset  //mt�豸������
 *[��Ϣ����]
 *    mtservice  = > ui/mtc
 */_event( ev_MtCombinationKeyInd )
   _body( u8, 1 )
   _ev_end

/**********************<< �ϱ������������ >>********************	
 *[��Ϣ��]
  *[��Ϣ����]
 *      = > mtservice
 */_event( ev_HintNotify )
   _body( u16, 1 )
   _ev_end

/***********************<< MTB��¼ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysMTBLoginInd )
   _ev_end


/***********************<< MTB�˳�ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysMTBLogoutInd )
   _ev_end

/***********************<< ����ϵͳʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysSetTimeCmd )
   _body( TMtKdvTime, 1 )
   _ev_end

/***********************<< ��ѯϵͳʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysTimeCmd )
   _ev_end

/***********************<< ϵͳʱ��ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  ev_SysTimeInd )
   _body( TMtKdvTime, 1 )
   _ev_end

/***********************<< ��ӵ�ַ����Ŀ >>********************	
 *[��Ϣ��]			 
 *   TADDRENTRYINFO
 *[��Ϣ����]
 *
 */_event(  ev_SysAddCallOutEntryCmd )
   _body( TAddrEntry, 1 )
   _ev_end

/***********************<< telnet password indication >>********************	
 *[��Ϣ��]			 
 *   password 
 *[��Ϣ����]
 *mt-->mtc
 */
 _event(  ev_SysTelnetPwdInd)
   _body(s8         ,   MT_TELNET_PWD_MAX_LEN )
   _ev_end

/***********************<< change telnet password  req>>********************	
 *[��Ϣ��]			 
 *   password
 *[��Ϣ����]
 *mtc-->mt
 */
 _event(  ev_SysChangeTelnetPwdCmd)
   _body(s8         ,   MT_TELNET_PWD_MAX_LEN )
 _ev_end   

 
/**********************<< MTC�����ն�ʱ������������������ >>*********************
 *[��Ϣ��]			 
 *s8[16+1]: ϵ��		//HD2
 *s8[16+1]: ��Ʒ�ͺ�	//MT_7920A
 *s8[8+1] : ֧��XML���	//TRUE
 *s8[32+1]: XML�汾		//VER_XMLENGINE "xmlengine.40.00.00.01.04.100302"
 *[��Ϣ����]: MTC ==> UE
 */_event(  ev_UMConnectInitReq  )
   _ev_end

/**********************<< MTC�����ն�ʱ���ֻظ������������� >>*********************
 *[��Ϣ��]			 
 *s8[16+1]: ϵ��		//HD2
 *s8[16+1]: ��Ʒ�ͺ�	//MT_7920A
 *s8[8+1] : ֧��XML���	//TRUE
 *s8[32+1]: XML�汾		//VER_XMLENGINE "xmlengine.40.00.00.01.04.100302"
 *[��Ϣ����]: UE ==> MTC
 */_event(  ev_UMConnectInitAck  )
   _ev_end
   
 /***********************<< NotifyObzerver���� >>********************	
 *[��Ϣ��]			 
 *   ��
 *[��Ϣ����]
 *    UE => UE
 */_event(  ev_NotifyObzerverCompletedInd  )
   _ev_end
   //mtsysevent end
 /***********************<<  ��ʱ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *	һ�붨ʱ��
 */
 _event(  EVTP_TIMER_PER_SECOND )
 _ev_end	

 /***********************<<  ��ʱ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *	���붨ʱ��
 */
 _event(  EVTP_TIMER_FIVE_SECOND )
 _ev_end	

/***********************<<  ҵ����������  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */_event(  EVTP_RUNNING )
   _ev_end	

   
/***********************<<  ι����ʱ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */_event(  EVTP_TIMER_WatchdogNotify )
   _ev_end	

/***********************<<  ҵ����������  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  evtp_sys_init )
 _ev_end

 //innermisc.h��ת��,֮ǰΪmtobject����.
 _event( ev_ThreadDetectReq )
 _ev_end

 _event( ev_ThreadDetectAck )
 _ev_end
 //

#ifndef _MakeTpEventDescription_
   _ev_segment_end(tpsys)
};
#endif




#endif // _h_eventtpsys_h__
