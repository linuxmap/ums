#ifndef _h_eventoutcncode_h__
#define _h_eventoutcncode_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNCODEEVENT
{
#endif 
	
	_ev_segment( outercncode  )

/***********************<< ������Ƶ������� >>**********************	
*[��Ϣ��]			 
*  +EmTpCodecComponent  =emAudioDecoder 
*  +EmTpAudioFormat 
*[��Ϣ����]
* cn  = > cnmpctrl
*/_event( ev_tppCodecAudioDecodeParamCmd )
_body ( EmTpCodecComponent    , 1    )
_body ( EmTpAudioFormat       , 1    )
_body ( u16       , 1    )  
_ev_end

/***********************<< ������Ƶ������� >>**********************	
 *[��Ϣ��]			 
 *  +EmTpCodecComponent  =emAudioEncoder
 *  + EmAudioFormat 
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecAudioEncodeParamCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( EmTpAudioFormat    , 1    )
   _body ( u16       , 1    )
   _ev_end

/***********************<< ������Ƶ������� >>**********************	
 *[��Ϣ��]			 
 *  +EmTpCodecComponent  
 *  + EmTpLostPackageRestore �� �����ָ���ʽ
 *  + EmTpVideoFormat    �������ʽ
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecVideoDecodeParamCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( EmTpLostPackageRestore    , 1    )
   _body ( EmTpVideoFormat    , 1    )
   _body ( u8    , 1    )
   _ev_end

/***********************<< ���ö�̬�غ� >>**********************	
 *[��Ϣ��]			 
 *  +EmTpCodecComponent ���������
 *  +u8	����̬�غ�ֵ
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecDynamicPayloadCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( u8    , 1    )
   _body ( u8    , 1    )
   _ev_end

/***********************<< ���ý��������յ�ַ >>**********************	
 *[��Ϣ��]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP���յ�ַ      
 *  + TIPTransAddr      RTCP���յ�ַ
 *  + TIPTransAddr      RTCP����Ŀ�ĵ�ַ
 *  + u32               ���պ����ص�ָ��(H320)
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecRecvAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( u32             , 1    )
   _body ( u16             , 1    )
   _ev_end

   /***********************<< ���ý��������͵�ַ >>**********************	
 *[��Ϣ��]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP����Ŀ�ĵ�ַ 
 *  + TIPTransAddr      RTCP����Ŀ�ĵ�ַ
 *  + TIPTransAddr      RTCP���յ�ַ
 *  + u32               ���ͺ����ص�ָ��(H320)
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecSendAddrCmd )
   _body ( EmTpCodecComponent, 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( u32             , 1    )
   _body ( u16             , 1    )
   _ev_end

      /***********************<< ���ñ��������ص�ַ >>**********************	
 *[��Ϣ��]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP����Ŀ�ĵ�ַ 
 *  + TIPTransAddr      RTCP����Ŀ�ĵ�ַ
 *  + TIPTransAddr      RTCP���յ�ַ
 *  + u32               ���ͺ����ص�ָ��(H320)
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecLocalAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPCnMediaTransPort    , 1    )
   _body ( BOOL    , 1    )
   _ev_end

 /********************<< ����Ƶ�������Կ  >>*****************************
 *[��Ϣ��]	
 *    + EmTpCodecComponent
 *    + TEncryptKey
 *[��Ϣ����]
 *  cn  = > cnmpctrl
*/_event ( ev_tppCodecEncryptKeyCmd )
  _body ( EmTpCodecComponent , 1 )
  _body ( TTpEncryptKey, 1 )
  _body ( u16             , 1    )
  _ev_end

  /***********************<< ������Ƶ������� >>**********************	
 *[��Ϣ��]			 
 *  + EmTpCodecComponent  =emPriomVideoEncoder/emSecondVideoEncoder
 *  + TVideoEncodeParameter 
 *	+ BOOL				ʹ�ڶ�·�Ĳ�����Ҫֱ�����õ��ײ�
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecVideoEncodeParamCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( TTPMtVideoEncodeParameter    , 1    )
   _body ( u8, 1 )
   _ev_end

     /***********************<< ������Ƶ������� >>**********************	
 *[��Ϣ��]			 
 *  + TTPVideoParam  ��Ƶ����
 *	+ EmTpVideoFormat  ��ƵЭ������
 *  + EmTpVideoResolution  �ֱ�������
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */_event( ev_tppNotifyVideoEncodeParamCmd )
   _body ( TTPVideoParam    , 1    )
   _body ( EmTpVideoFormat    , 1    )
   _body ( EmTpVideoResolution    , 1    )
   _body ( u8, 1 )
   _ev_end

  /***********************<< ����ep�б� >>********************	
 *[��Ϣ��]
s8* �ļ�ȫ·����
 *[��Ϣ����]
 *  cn  = > cnmpctrl
*/
_event(  ev_tppMTAutoTest_Cmd )
_body ( EmTPAutoTestType , 1 )
_ev_end

/***********************<< ����������ͳ����Ϣ >>************************	
 *[��Ϣ��]		 
 *   �� 
 *[��Ϣ����]
 *  cn  = > cnmpctrl 
 */
 _event ( ev_tppCodecPackStatCmd )
 _ev_end


 /***********************<< ����������ͳ����Ϣ >>************************	
 *[��Ϣ��]		 
 *   �� 
 *[��Ϣ����]
 *   cn  = > cnmpctrl 
 */
 _event ( ev_tppCodecPackStatInd )
 _body ( TTPCodecPackStat    , 1          )
 _ev_end

 /***********************<< ����������������Ϣ >>************************	
 *[��Ϣ��]		 
 *  +BOOL  TRUE= ���� ;FALSE=�ر�
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */
 _event ( ev_tppCodecLostPackCmd )
  _body ( BOOL, 1 )
 _ev_end
 
 /***********************<< �������ʵ�ʵ����ʷֱ���ͳ����Ϣָʾ >>************************	
 *[��Ϣ��]		 
 *  +TTPVideoEncDecResPack  //��������ֱ���

 *[��Ϣ����]
 *    cnmpctrl  = > cn
 */
 _event ( ev_tppCodecVideoEncDecResInd ) 
 _body ( TTPVideoEncDecResPack, 1 )
 _ev_end

/***********************<< �ӱ�������ȡ�ĵ�һ·֡���ϱ� >>************************	
 *[��Ϣ��]		 
 *  +TTPVideoFrameRatePack6  //��Ƶ֡��

 *[��Ϣ����]
 *    cnmpctrl  = > cn
 */_event ( ev_tppVidFramerateInd )
  _body ( TTPVideoFrameRatePack, 1 )
  _ev_end

  /***********************<< ����Ƶ������ >>************************	
 *[��Ϣ��]
 * u8  �����ʣ��԰ٷֱȱ�ʾ

 *[��Ϣ����]
 *   cnmpctrl  = > cn
 */_event ( ev_tppCodecLostPackInd )
  _body ( u8, 1 )
  _ev_end

 /***********************<< ��������û����ƵԴ����>>************************	
 *[��Ϣ��]		 
 *  +TTPVideoRecv  //���������û����ƵԴ����
 *[��Ϣ����]
 *  cnmpctrl  = > cn
 */
 _event ( ev_tppCodecVideoRecvInd ) 
 _body ( TTPVideoRecv, 1 )
 _ev_end
 
 /***********************<<  ������Ƶ�˿�ѡ������    >>********************	
 *[��Ϣ��]			 
 *     +TTPHdAudioPort  ��Ƶ�˿�
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */
 _event( ev_tppCfgHDAudioInPortCmd  ) 
 _body ( TTPHdAudioPort   ,1) 
 _ev_end

  /***********************<<  ������Ƶ���Ŷ˿�ѡ������    >>********************	
 *[��Ϣ��]			 
 *     +TTPHdAudioOutPort  ��Ƶ�˿�
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */
 _event( ev_tppCfgHDAudioOutPortCmd  ) 
 _body ( TTPHdAudioOutPort   ,1) 
 _ev_end

  /***********************<<  ˫��������Ƶ�˿�ѡ������    >>********************	
 *[��Ϣ��]			 
 *     +THdAudioPort  ��Ƶ�˿�
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */
 _event( ev_tppCfgHDDualAudioInPortCmd  ) 
 _body ( TTPHdDualAudioPort   ,1)
 _body ( BOOL   ,1)
 _ev_end

 /***********************<< ����/�ر��Զ�������� >>**********************	
 *[��Ϣ��]			 
 *  +BOOL  TRUE= ���� ;FALSE=�ر�   
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppAGCCmd )
   _body ( BOOL    , 1    )
   _body ( u8    , 1    )
   _ev_end


   /**********************<< Mic�������  >>********************	
 *[��Ϣ��]
 * +EmTPHDAudPortIn ��Ƶ�˿�
 * +u8 mic����ֵ ���淶Χ1��31
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppMicAdjustCmd )
   _body(EmTPHDAudPortIn, 1)
   _body( u8, 1 )
   _body ( u8    , 1    )
   _ev_end

   /***********************<<  ������ֱ������ָʾ  >>********************	
 *[��Ϣ��]			 
 * +u32   �������ģʽ
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppCfgHDResOutputInd  )
   _body( u32     , 1 )
   _body( u8     , 1 )
   _ev_end

   /***********************<<  ���ģʽ֡��������ʾ  >>********************	
 *[��Ϣ��]			 
 *     TTPVideoDisplayFrm  ���֡��
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */_event( ev_tppCfgHDVideoFrmInd  )
   _body( TTPVideoDisplayFrm      , 1 )
   _body( u8     , 1 )
   _ev_end


   /***********************<< ����˫����ʾģʽ >>**********************	
 *[��Ϣ��]			 
 *  +EmDualVideoShowMode  ˫����ʾģʽ
 *[��Ϣ����]
 *cn  = > cnmpctrl
 */_event( ev_tppCodecDualShowModeCmd )
   _body ( EmTPDualVideoShowMode    , 1    )
   _body( u8     , 1 )
   _ev_end
/***********************<< ������ʾ����ģʽ >>**********************	
 *[��Ϣ��]
 *  +u8   0:����Ƶ�� 1:˫��
 *  +EmDisplayRatio ��ʾ����
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecDisplayRatioCmd )
   _body ( u8				, 1		)
   _body ( EmTPDisplayRatio    , 1    )
   _body( u8     , 1 )
   _ev_end

   /***********************<< ��Ƶ��������  >>************************	
 *[��Ϣ��]			 
 *    +TImageAdjustParam  ͼ���������
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event(  ev_tppCodecImageAdjustParamCmd  )
   _body( TTPImageAdjustParam ,1           )  
   _body( u8     , 1 )
   _ev_end

/***********************<< ���ö���ʱ������������  >>************************
 *[��Ϣ��] 
 *  +TBitRateAdjust  ����ʱ������������
 *[��Ϣ����]
 *
 *  cn  = > cnmpctrl
 */_event(  ev_tppCodecRateAdjustCmd   )
   _body ( TTPBitRateAdjust      , 1 )//����ʱ������������
   _body( u8     , 1 )
   _ev_end


/**********************<< �����ʽ���һ������  >>********************	
 *[��Ϣ��]
 * u8  ���Ϊ95�������ʵ�����ԭ����95%
 * u8  ����ipͷ�����࣬��Ҫ�ٽ��������ʽ���һ��ֵ
       Ĭ����90%������Ϊԭ����90%�������������Ϊԭ����ֵ,�������ʽ�
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */_event( ev_tppCodecBitRateDecsRatioCmd )
  _body( u8, 1 )
  _body( u8, 1 )
  _body( u8, 1 )
   _ev_end 

/***********************<< ���;�̬ͼƬ >>**********************	
 *[��Ϣ��]			 
 *  +BOOL TRUE=��ʼ����  ��FALSE=ֹͣ����
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppSendPictureCmd )
   _body ( BOOL    , 1    )
   _body( u8, 1 )
   _ev_end


   /***********************<< �Ի����� >>**********************	
 *[��Ϣ��]			 
 *  +BOOL      TRUE=��ʼ����  ��FALSE=ֹͣ����
 *  u8         �����������
 *  EmToolType ��������
 *  u8         ��������ܸ���
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppLoopbackTestCmd )
   _body ( BOOL    , 1    )
   _body( u8, 1 )
   _body( EmToolType, 1)
   _body( u8, 1 )
   _ev_end

    /***********************<< �Ի����Ի�Ӧ >>**********************	
 *[��Ϣ��]
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppLoopbackTestInd )
	_body( u8, 1 )
	_body( EmToolType, 1)
   _ev_end

   //add by niu 2014-04-23
    /***********************<< ���������Ի����Ի�Ӧ >>**********************	
 *[��Ϣ��]
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppAutoLoopbackTestInd )
	_body( BOOL, 1 )
	_body( EmToolType, 1)
   _ev_end

   /***********************<< ������������������ͳ����Ϣ >>************************	
 *[��Ϣ��]		 
 *   �� 
 *[��Ϣ����]
 *  cn  = > cnmpctrl 
 */
	 _event ( ev_tppAutoCodecPackStatCmd )
	 _ev_end

 /***********************<< ������������������ͳ����Ϣ��Ӧ >>************************	
 *[��Ϣ��]		 
 *   �� 
 *[��Ϣ����]
 *   cn  = > cnmpctrl 
 */
	_event ( ev_tppAutoCodecPackStatInd )
	_body( BOOL, 1 )
	_body ( TTPAudPower, 1          )
	_ev_end

	  /***********************<< �Ի��������Կ����رհ����� >>**********************	
   *[��Ϣ��]
   *  +EmTpMediaType      ý������
   *  +BOOL             TRUE=��������  ��FALSE=ֹͣ����
   *  +u32              ��ũ�˿�
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestAudNoisePlayCmd )
   _body ( BOOL           , 1    )
   _body( u32, 1 )
   _ev_end

   //end add by niu

   /***********************<<  ���ö����ش�����    >>********************	
 *[��Ϣ��]			 
 *     +TLostPackResend
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecLostPackResendCmd  )
   _body ( TTPLostPackResend   ,1)
   _body( u8, 1 )
   _ev_end

 /***********************<<  �ӿڲ�������   >>********************	
 *[��Ϣ��]			 
 * TTPAutoTestMsg    
 *[��Ϣ����]
 *  cn  = > cnmpctrl
 */_event( ev_tppAutoTestCmd  )
   _body ( TTPAutoTestMsg   ,1)
   _ev_end


 /***********************<<  ��ʾ����Ƶ�������Ϣ   >>********************	
 *[��Ϣ��]			 
 * +u8             
 * +EmTpCodecType  ���������
 *[��Ϣ����]
 *    cnmpctrl  = > cnmpctrl
 */_event( ev_tppShowCodecInfoCmd  ) 
   _body ( EmTpCodecType   ,1)
   _body ( u8   ,1)
   _ev_end

 /***********************<<  �����ն���Ƶ�ı����ʽ   >>********************	
 *[��Ϣ��]			 
 *     
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetAudForPriStrategyCmd  )
   _body ( EmTpAudioFormat   ,1)
   _body ( u8   ,1)
   _ev_end


   
 /***********************<<  ���þ�����(3·����Ƶ)  >>********************	
 *[��Ϣ��]			 
 * +TTPEqualizer  ����������  
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetAudioEqualizerCmd  )
   _body ( TTPEqualizer   ,1)
   _body ( u8   ,1)
   _ev_end

 /***********************<<  ������Ƶ�ĵ�ͨ����ͨ���˲�  >>********************	
 *[��Ϣ��]			 
 *  a.��ͨ�˲�����ֹƵ��20Khz
	b.��ͨ�˲�����ֹƵ��20hz   
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetAudioFilterRateCmd  )
   _body ( u32   ,1)
   _body ( u8   ,1)
   _ev_end

    /***********************<<  ������Ƶ�ı�������˥��  >>********************	
 *[��Ϣ��]			 
 *  +u8 ��������˥����Χ0-15dB  
 *[��Ϣ����]
 *   cn  = > cnmpctrl 
 */_event( ev_tppSetAudioBNACmd  )
   _body ( u8   ,1)
   _body ( u8   ,1)
   _ev_end
   

       /***********************<<  ����FEC������Ϣ  >>********************	
 *[��Ϣ��]			 
 * +TTPFecInfo  FEC������Ϣ
 *[��Ϣ����]
 *   cn  = > cnmpctrl 
 */_event( ev_tppSetFecInfoCmd  )
   _body ( TTPFecInfo   ,1)
   _body ( u8   ,1)
   _ev_end

       /***********************<<  ���л�����  >>********************	
 *[��Ϣ��]			 
 *   + TTPPIPMod
 *[��Ϣ����]
 *   cn  = > cnmpctrl 
 */_event( ev_tppSetPIPModCmd  )
   _body ( TTPPIPMod   ,1)
   _ev_end
   
   /***********************<<  ָʾ��ǰ�ľ�������    >>********************	
 *[��Ϣ��]			 
 *     +TTPVideoPort ��Ƶ�˿�
 *[��Ϣ����]
 *    cn  = > cnmpctrl 
 */_event( ev_tppMatrixCmd  )
   _body ( TTPVideoPort   ,1)
   _ev_end


   /***********************<< ����MTU���� >>************************	
  *[��Ϣ��]		 
  * + u32   MTUֵ
  *[��Ϣ����
  *   cn  = > cnmpctrl 
  */_event ( ev_tppCfgSetMTUCmd )
   _body( u32          ,1 )
   _ev_end

   /***********************<< ���������������� >>************************	
 *[��Ϣ��]		 
 * + u32   �������ȵȼ�
 *[��Ϣ����
 *   cn  = > cnmpctrl
 */_event ( ev_tppCfgSetAudioPrecedenceCmd )
  _body( u32         ,1 )
  _body( u8, 1 )
  _ev_end 

     /***********************<< ��ũ��˻��󹩵翪�� >>************************	
 *[��Ϣ��]
 * +EmTPHDAudPortIn ��Ƶ����˿�  
 * +BOOL  TRUE= ���� ;FALSE=�ر�
 *[��Ϣ����
 *   cn  = > cnmpctrl
 */_event ( ev_tppSimplexPoweringCmd )
  _body( EmTPHDAudPortIn         ,1 )
  _body( BOOL         ,1 )
  _body( u8, 1 )
  _ev_end 


     /***********************<< ��ⶪ����ʱ�� >>**********************	
 *[��Ϣ��]			 
* ��
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_timer_check_lostpack )
   _ev_end


   /***********************<< ����LOOP��ַ >>**********************	
 *[��Ϣ��]			 
 *  + TTpCodecComponent
 *  + TTPCnMediaTransPort  ���յ�ַ
 *  + BOOL   TRUE ��ӵ�ַ��FALSE ɾ����ַ
 *[��Ϣ����]
 *    cn  = > cnmpctrl
 */_event( ev_tppCodecLoopAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPCnMediaTransPort    , 1    )
   _body ( BOOL, 1)
   _ev_end
   
   /***********************<< �����������ͳ����Ϣ��ʱ�� >>**********************	
 *[��Ϣ��]			 
* ��
 *[��Ϣ����]
 *cnmpctrl  = > cnmpctrl
 */_event( ev_timer_tpppriomdecstatis1 )
   _ev_end
   _event( ev_timer_tpppriomdecstatis2 )
   _ev_end
   _event( ev_timer_tpppriomdecstatis3 )
   _ev_end
   _event( ev_timer_tpppriomdecstatis4 )
   _ev_end

    /***********************<< ���ȫ���������Ƿ񶪰���ʱ��  >>**********************	
 *[��Ϣ��]			 
 * ��
 *[��Ϣ����]
 *cnmpctrl  = > cnmpctrl
 */_event( ev_timer_tppcheckviddec_lostpack1 )
   _ev_end
   _event( ev_timer_tppcheckviddec_lostpack2 )
   _ev_end
   _event( ev_timer_tppcheckviddec_lostpack3 )
   _ev_end
   _event( ev_timer_tppcheckviddec_lostpack4 )
   _ev_end
   
      /**********************<< ��ũ���������Ϣ  >>********************	
 *[��Ϣ��]
 * +TTPSingleAudioPortCfg  ��ũ���������Ϣ
 * +EmTPHDAudPortIn  ��˶˿�
 *[��Ϣ����]
 *    cn  = > cnmpctrl
 */_event( ev_tpSgAudioPortCfgCmd )
   _body( TTPSingleAudioPortCfg, 1 )
   _body ( EmTPHDAudPortIn    , 1    )
   _body ( u8    , 1    )
   _ev_end

  /**********************<< ����������  >>********************	
 *[��Ϣ��]
 * +BOOL  TRUEΪ��������ȣ�FALSEΪ�ر�������
 *[��Ϣ����]
 *    cn  = > cnmpctrl
 */_event( ev_tppSetEncQualityEnhanceCmd )
   _body ( BOOL    , 1    )
   _body ( u8    , 1    )
   _ev_end

   /**********************<< ͼ�����Ҳñ�  >>********************	
 *[��Ϣ��]
 * +TTPVidSrcCutLines ͼ�����Ҳñ�
 *[��Ϣ����]
 *    cn  = > cnmpctrl
 */_event( ev_tppSetVidSrcCutLinesCmd )
   _body ( TTPVidSrcCutLines    , 1    )
   _ev_end


 /***********************<< ����������������ʱ�䣬��λ�� >>**********************	
 *[��Ϣ��]			 
 *  + u32
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetSpeechTimeCmd )
   _body ( u32    , 1    )
   _ev_end
   

   /***********************<< DSP �������� >>************************	
   *[��Ϣ��]		 
   * 
   *[��Ϣ����]
   *    cn  = > cnmpctrl
   */ _event ( ev_tppCodecDspSleepCmd )
   _ev_end
   
   /***********************<< DSP �������� >>************************	
   *[��Ϣ��]		 
   * 
   *[��Ϣ����]
   *    cn  = > cnmpctrl
   */ _event ( ev_tppCodecDspWakeupCmd )
    _ev_end


   /***********************<< MtMP DSP ״ָ̬ʾ >>************************	
   *[��Ϣ��]		 
   *  + BOOL     TRUE =���� FALSE =����
   *[��Ϣ����]
   *    cnmpctrl  = > cn
   */ _event ( ev_tppCodecDspSleepStateInd )
   _body(   BOOL   , 1          )
    _ev_end

	/***********************<<  AEC΢������ >>********************	
	*[��Ϣ��]
	+ u32 ��Χ0-60
	*[��Ϣ����]
	*   cn  = > cnmpctrl
	*/_event( ev_tppCfgAECAdjustCmd )
	_body( u32, 1 )
	_body ( u8    , 1    )
   _ev_end

   /***********************<<  AEC΢����ʱ�� >>********************	
	*[��Ϣ��]
	+
	*[��Ϣ����]
	*   cnmpctrl  = > cn
	*/_event( ev_tpp_timer_setaecdbg_code1 )
   _ev_end

   _event( ev_tpp_timer_setaecdbg_code2 )
   _ev_end

   _event( ev_tpp_timer_setaecdbg_code3 )
   _ev_end

   _event( ev_tpp_timer_setaecdbg_dualcode )
   _ev_end
   
   /**********************<< ��Ƶ�ź�����ָʾ  >>********************	
   *[��Ϣ��]
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppCodecVideoInputCmd )
   _body( u8, 1 )
   _ev_end

    /**********************<< ��Ƶ�ź�����ָʾ  >>********************	
   *[��Ϣ��]
   * BOOL         //��һ·��Ƶ�Ƿ����ź�
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppCodecVideoInputInd )
   _body( BOOL , 1 )
   _body( u8, 1 )
   _ev_end

    /***********************<< �����Ƶ������Ϣ�Ƿ��ж϶�ʱ��  >>**********************	
 *[��Ϣ��]			 
 * ��
 *[��Ϣ����]
 *
 */_event( ev_tpp_timer_checkvideoinput1 )
   _ev_end
   _event( ev_tpp_timer_checkvideoinput2 )
   _ev_end
   _event( ev_tpp_timer_checkvideoinput3 )
   _ev_end
   _event( ev_tpp_timer_checkvideoinput4 )
   _ev_end

   /**********************<< VGA�ֱ�������  >>********************	
   *[��Ϣ��]
   * TTPVGAInfo         
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppVGAfpsCmd )
   _body( TTPVGAInfo , 1 )
   _ev_end

   /**********************<<  VGA�ֱ��ʻ�Ӧ    >>********************	
   *[��Ϣ��]
   * u32 VGAPC
   * u32 VGAFS
   * u32 Res
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppVGAfpsInd )
   _body( u32, 1 )
   _body( u32, 1 )
   _body( u32, 1 )  
   _ev_end

   //Add by tanxiaodong 2013-03-15.
   /**********************<<  ̨��Logo��������    >>********************	
   *[��Ϣ��]
   *BOOL �Ƿ���̨��
   *u8   0 : CNC��Ϣ��1: ά��������Ϣ
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppSetBannerLogo_Cmd )
   _body( BOOL, 1 )
   //_body( TTPFullLogoParam, 1 )
   _body( u8, 1 )
   _body( TTPAddLogoPos, 2 )
   _ev_end
   //End  to add.

   
   /***********************<< �Ի��������� >>**********************	
   *[��Ϣ��]
   *  +EmTpMediaType      ý������
   *  +BOOL             TRUE=��ʼ����  ��FALSE=ֹͣ����
   *  +BOOL             TRUE=��С������FALSE=����С����
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestLoopbackCmd )
   _body ( EmTpMediaType    , 1    )
   _body ( BOOL           , 1    )
   _body( u8, 1 )
   _body( BOOL , 1 )
   _ev_end

   /**********************<< ��������������  >>********************	
   *[��Ϣ��]
   * + EmMtLoudspeakerVal 1
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppLoudspeakerTestCmd )
   _body( EmMtLoudspeakerVal, 1 )
   _body( u8, 1 )
   _ev_end

   /**********************<< ����������ָʾ  >>********************	
   *[��Ϣ��]
   * + EmMtLoudspeakerVal 1
   *[��Ϣ����]
   *   cn  <= cnmpservice
   */_event( ev_tppLoudspeakerTestInd )
   _body( EmMtLoudspeakerVal, 1 )
   _ev_end

    /***********************<< ���������Զ�ʱ��  >>**********************	
 *[��Ϣ��]			  
 * ��
 *[��Ϣ����]
 *
 */_event( ev_timer_loudspeaker_test1 )
   _ev_end
   _event( ev_timer_loudspeaker_test2 )
   _ev_end
   _event( ev_timer_loudspeaker_test3 )
   _ev_end

    /***********************<< �Ի���������(1��2��) >>**********************	
   *[��Ϣ��]
   *  +BOOL             TRUE=��ʼ����  ��FALSE=ֹͣ����
   *  +u8               ������
   *  +u8               ��һ��������
   *  +u8               �ڶ�������������
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestOneInTowOutCmd )
   _body ( BOOL           , 1    )
   _body( u8, 1 )
   _body( u8, 1 )
   _body( u8, 1 )
   _ev_end

    /***********************<< ���ñ����������Ƶȼ���Ŀǰֻ��Կ�ũ��˷磩 >>**********************	
   *[��Ϣ��]
   *  +EmTPHDAudPortIn    ��Ƶ�˿�
   *  +BOOL    TRUE ʹ��������ǿ�� FALSE ֹͣʹ��������ǿ
   *  +u32               �����������Ƶȼ���0-3��
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppSetSpeLevelCmd )
   _body ( EmTPHDAudPortIn           , 1    )
   _body ( BOOL           , 1    )
   _body( u32, 1 )
   _body( u8, 1 )
   _ev_end


    /***********************<< ��ʼ/ֹͣ ���� >>**********************	
   *[��Ϣ��]
   *   * TTPVAdapterInfo  ˫���������
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppStartAdapterCmd )
   _body ( TTPVAdapterInfo           , 1    )
   _ev_end
	
    /***********************<< ��������ؼ�֡ >>**********************	
   *[��Ϣ��]
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppFastUpdateAdaCmd )
   _ev_end
	
    /***********************<< �Ի����Իظ� >>**********************	
   *[��Ϣ��]
   *  +BOOL             TRUE=��ʼ����  ��FALSE=ֹͣ����
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestLoopbackInd )
   _body ( TTPSingleLoopInfo           , 1    )
   _ev_end


      /***********************<< ���ý��������͵�ַ >>**********************	
 *[��Ϣ��]			 
 *  + TTpCodecComponent
 *  + BOOL              TRUE ����·��͵�ַ�� FALSEɾ�����͵�ַ
 *  + TIPTransAddr      RTP����Ŀ�ĵ�ַ 
 *  + TIPTransAddr      RTCP����Ŀ�ĵ�ַ
 *  + TIPTransAddr      BRTCP����Ŀ�ĵ�ַ
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetSendAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( BOOL,               1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _ev_end
	
   /***********************<< ������Ƶ����ģʽ >>**********************	
   *[��Ϣ��]
   *  +TTPAudPlayMode     ��Ƶ����ģʽ
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppSetAudPlayModeCmd )
   _body ( TTPAudPlayMode           , 1    )
   _body ( BOOL           , 1    )
   _ev_end

   /***********************<< ����֡�� >>**********************	
   *[��Ϣ��]
   *  +TAdjustFrameRate     ����֡�� 
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppAdjustFrameRate_Cmd )
   _body ( TAdjustFrameRate           , 1    )
   _body ( u8,               1    )
   _ev_end

   /***********************<< ���ڷֱ��� >>**********************	
   *[��Ϣ��]
   *  +TAdjustVidRes     ���ڷֱ���
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppAdjustVidRes_Cmd )
   _body ( TAdjustVidRes           , 1    )
   _body ( u8,               1    )
   _ev_end


   /***********************<< �޸Ľ��������յ�ַ >>**********************	
 *[��Ϣ��]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP���յ�ַ      
 *  + TIPTransAddr      RTCP���յ�ַ
 *  + TIPTransAddr      RTCP����Ŀ�ĵ�ַ
 *[��Ϣ����]
 *   cn  = > cnmpctrl
 */_event( ev_tppModifyRecvAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _ev_end


   /***********************<< ����С����λ�� >>**********************	
   *[��Ϣ��]
   *  +TTPSmallPicRectInfo     С����λ����Ϣ
   *  +u8 �������
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppSetSmallPicRect )
   _body ( TTPSmallPicRectInfo           , 1    )
   _body ( u8   , 1  )
   _ev_end


         /***********************<< ���˫������Դ >>**********************	
 *[��Ϣ��]			 
* ��
 *[��Ϣ����]
 *cnmpctrl  = > cnmpctrl
 */_event( ev_timer_checkdualinput )
   _ev_end


   /***********************<< ����˫����Ƶ����˿�ģʽ >>**********************	
   *[��Ϣ��]
   *  +EmTPAudDualInMode     ˫����Ƶ����˿�ģʽ
   *  +u8 �������
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppSetAudDualInModeCmd )
   _body ( EmTPAudDualInMode           , 1    )
   _body ( u8   , 1  )
   _ev_end

   /***********************<< ����ͼ��ƫ��  >>**********************	
   *[��Ϣ��]
   *  +TTPVidOffsetParam     ����ͼ��ƫ�� 
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppSetVidOffsetParam  )
   _body ( TTPVidOffsetParam           , 1    )
   _ev_end


   /***********************<< ������Ƶ˫�����ز���  >>**********************	
   *[��Ϣ��]
   *  BOOL    TRUE:��Ƶ˫�����ز���; FALSE:�Ǳ��ز���
   *[��Ϣ����]
   *cn  = > cnmpctrl
   */_event( ev_tppSetAudSubPlay  )
   _body ( BOOL          , 1    )
   _ev_end

	   /***********************<< �м����Ƿ�����ʾ˫������ >>**********************	
 *[��Ϣ��]			 
 *  +BOOL      TRUE=�м�����ʾ˫��  ��FALSE=����ʾ˫��
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppShowDualCmd )
   _body ( BOOL    , 1    )
   _ev_end

   	   /***********************<< ������Ƶ������ >>**********************	
 *[��Ϣ��]			 
 *  +TTPAudPackCheckInfo
 *[��Ϣ����]
 * cn  = > cnmpctrl
 */_event( ev_tppSetAudPackCheckTimeCmd )
   _body ( TTPAudPackCheckInfo    , 1    )
   _ev_end

   /***********************<< AEC,AGC,ANS���� >>**********************	
   *[��Ϣ��]			 
   *  +EmAudAecType  ��Ƶ����
   *  +BOOL  �����ر�
   *[��Ϣ����]
   * cn  = > cnmpctrl
   */_event( ev_tppSetAecParamCmd )
   _body ( EmAudAecType    , 1    )
   _body ( BOOL    , 1    )
   _ev_end

      /***********************<< ���ÿ������� >>**********************	
   *[��Ϣ��]			 
   *  +EmTpSnapShotType ��������
   *  +u8      ��ǰ���������������
   *  +u8      Ҫ�����Ԥ��λ��
   *[��Ϣ����]
   * cn  = > cnmpctrl
   */_event( ev_tppSetSnapShotCmd )
   _body ( EmTpSnapShotType    , 1)
   _body ( u8				   , 1)
   _body ( u8				   , 1)
   _ev_end

     /***********************<< ���� >>**********************	
   *[��Ϣ��]
   *  +u8 BOOL TRUE���ճɹ���FALSE����ʧ��
   *  +EmTpSnapShotType ��������
   *[��Ϣ����]
   * cnmp  = > cn
   */_event( ev_tppSetSnapShotInd )
   _body ( EmTpSnapShotType    , 1)
   _body ( u8				   , 1)
   _body ( u8				   , 1)
   _body ( BOOL                , 1)
   _ev_end

    /***********************<< ����ϳ� >>**********************	
   *[��Ϣ��]
   *  +u8 BOOL TRUE��ʼ����ϳɣ�FALSEȡ������ϳ�
   *[��Ϣ����]
   * cnmp  = > cn
   */_event( ev_tppSetPipMergeCmd )
   _body ( BOOL    , 1    )
   _ev_end
   
    /***********************<< ����ǰ������ԣ��Ӻڱߣ��ñߵȣ� >>**********************	
   *[��Ϣ��]
   *  +EmVidEncResizeMode ͼ�������������
   *  +u8 �������
   *[��Ϣ����]
   * cnmp  = > cn
   */_event( ev_tppSetVidEncResizeModeCmd )
   _body ( EmVidEncResizeMode    , 1    )
   _body ( u8   , 1  )
   _ev_end

    /**********************<<  ̨����������    >>********************	
   *[��Ϣ��]
   *TTPLogoParam ̨����Ϣ
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppSetLogo_Cmd )
   _body( TTPLogoParam, 1 )
   _ev_end

    /**********************<<  �����������    >>********************	
   *[��Ϣ��]
   *TTPBannerParam �����Ϣ
   *[��Ϣ����]
   *   cn  = > cnmpctrl
   */_event( ev_tppSetBanner_Cmd )
   _body( TTPBannerParam, 1 )
   _ev_end

      /***********************<< ����������������� >>********************	
 *[��Ϣ��]
 * u8 �������
 * u8 �������λ��
 *[��Ϣ����]
 *  cns	  -> cnmp
 */
_event( ev_tppSetSingleAudOutputVolCmd )
   _body ( u8    , 1    )
   _body ( u8, 1 )
   _ev_end

     /***********************<< ��˫��ʱ�������� >>********************	
 *[��Ϣ��]
 * BOOL   TRUE��ʹ�ü�������FALSE�����ü�����
 *[��Ϣ����]
 *  cns	  -> cnmp
 */
  _event( ev_tppSetFakeCapacityCmd )
   _body ( BOOL    , 1    )
   _ev_end
#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercncode )
};
#endif
#endif