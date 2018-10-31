#ifndef _h_eventoutcnscentre_h__
#define _h_eventoutcnscentre_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCENTREEVENT
{
#endif 
	
	_ev_segment( outercnscentre  )


/***********************<< TPad��½֪ͨ >>************************	
 *[��Ϣ��]
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_TPadOnLine_Req )
   _ev_end

/***********************<< CnTools��½֪ͨ >>************************	
 *[��Ϣ��]
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_CnsToolsOnLine_Req )
   _ev_end

/***********************<< ֪ͨ������ӻ����� >>************************	
 *[��Ϣ��]
 *  + TCentreTVCfg
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVStateNty       )
   _body(   TCentreTVCfg, MAX_CENTRETV_NUM)
   _ev_end

/***********************<< ֪ͨ�����ĵ���������� >>************************	
 *[��Ϣ��]
 *   + TCentreDCamCfg
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreDCamStateNty  )
   _body(   TCentreDCamCfg,       1  )
   _ev_end

/***********************<< ֪ͨ����ʩ�͵����� >>************************	
 *[��Ϣ��]
 *   + TCentreSchCfg
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreSchStateNty  )
   _body(   TCentreSchCfg,       1  )
   _ev_end

/***********************<< �п�ѡ����ӻ��������� >>************************	
 *[��Ϣ��]
 *     + u8  ���ӻ�����
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreselectTV_cmd )
   _body(   u8   ,       1    )
   _ev_end

/***********************<< �п�ѡ����ӻ������������� >>************************	
 *[��Ϣ��]
 *     + u8     ���ӻ�����
 *     + BOOL   �����ɹ�/ʧ��
 *  
 *[��Ϣ����]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreselectTV_Ind )
   _body(   u8   ,       1    )
   _body(   BOOL ,       1    )
   _ev_end

/***********************<< �п� ���õ���ģʽ���� >>************************	
 *[��Ϣ��]
 *     +  EmTvMode   ���ӻ�ģʽ  	emTVPowerOFF/emTVPowerON ��Դ��/��
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVMode_cmd )
   _body(   EmTvPowerMode,     1    )
   _body(   u8           ,     1    )
   _ev_end

/***********************<< �п� ���õ���ģʽ�������� >>************************	
 *[��Ϣ��]
 *     + EmTvMode   ���ӻ�ģʽ  	emTVPowerOFF/emTVPowerON ��Դ��/��
 *     + BOOL       ���óɹ�/ʧ��
 *  
 *[��Ϣ����]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVMode_Ind )
   _body(   EmTvPowerMode,     1    )
   _body(	u8	,	           1    )
   _body(   BOOL         ,     1    )
   _ev_end

/***********************<< �п� ���õ�������ģʽ���� >>************************	
 *[��Ϣ��]
 *     +  EmTVAudVisMode   ���ӻ�����ģʽ  	
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVAudVisMode_cmd )
   _body(   EmTVAudVisMode   ,       1    )
   _ev_end

/***********************<< �п� ���õ�������ģʽ�������� >>************************	
 *[��Ϣ��]
 *     + EmTVAudVisMode   ���ӻ�����ģʽ  	
 *     + BOOL           ���óɹ�/ʧ��
 *  
 *[��Ϣ����]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVAudVisMode_Ind )
   _body(   EmTVAudVisMode   ,       1    )
   _body(   BOOL       ,       1    )
   _ev_end


/***********************<< �п� ���õ�����ʾģʽ���� >>************************	
 *[��Ϣ��]
 *     +  EmTVDisplayMode   ���ӻ�����ģʽ  	
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVDisMode_cmd )
   _body(   EmTVDisplayMode   ,       1    )
   _ev_end

/***********************<< �п� ���õ�����ʾģʽ�������� >>************************	
 *[��Ϣ��]
 *     + EmTVDisplayMode   ���ӻ�����ģʽ  	
 *     + BOOL            ���óɹ�/ʧ��
 *  
 *[��Ϣ����]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVDisMode_Ind )
   _body(   EmTVDisplayMode   ,       1    )
   _body(   BOOL       ,       1    )
   _ev_end

/***********************<< �п� ���õ�������ѡ������ >>************************	
 *[��Ϣ��]
 *  u8 �����
 *     +  EmTVInputSelect   ���ӻ�����ѡ��  	
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVInpSelect_cmd )
   _body( u8, 1 )
   _body(   EmTVInputSelect   ,       1    )
   _ev_end

/***********************<< �п� ���õ�������ѡ�񷵻����� >>************************	
 *[��Ϣ��]
 *  u8 �����
 *     + EmTVInputSelect   ���ӻ�����ѡ��  	
 *     + BOOL            ���óɹ�/ʧ��
 *  
 *[��Ϣ����]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVInpSelect_Ind )
   _body( u8, 1 )
   _body(   EmTVInputSelect   ,       1    )
   _body(   BOOL            ,       1    )
   _ev_end
   
  //Add by panhaiyang
/***********************<< ���ÿ����ĵ�����ͷ������ָ�� >>************************	
 *[��Ϣ��]			 
 *    + s8  ����ĵ�����ͷ�Ŀ���ָ��
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_DCam_Set_Cmd )
   _body (   s8        ,    1 )
   _ev_end

// **********************<< �ĵ����������ѡ��   >>************************	
//  *[��Ϣ��]			 
//  *EmDCamPower:�ĵ�����ͷ��������ѡ��
//   emDCamPowerOn        ����
//   emDCamPowerOff       ����
//   emDCamPowerToggle    �����뻽�ѿ����л� 
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamPower_Cmd )
   _body( EmDCamPower, 1 )
   _ev_end
// 
//  **********************<< �ĵ�������Զ��۽�ѡ��   >>************************	
//  *[��Ϣ��]			 
//  *EmDCamAFMode: �ĵ�������Զ��۽�ѡ��
//   emDCamAFOn          �����Զ��۽�
//   emDcamAFOff         �ر��Զ��۽�
//   emDCamAFToggle      �Զ��۽������л� 
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamAFMode_Cmd )
   _body( EmDCamAFMode, 1 )
   _ev_end
// 
//  **********************<< �ĵ��������ƽ��ģʽѡ��   >>************************	
//  *[��Ϣ��]			 
//  *EmDCamBWMode: �ĵ��������ƽ��ģʽѡ��
//   emDcamWBAuto         �����Զ���ƽ��ģʽ
//   emDCamWBManual       �����ֶ���ƽ��ģʽ 
//   emDCamOnePush        ����һ��ʽ��ƽ��ģʽ
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamWBMode_Cmd )
   _body( EmDCamWBMode, 1 )
   _ev_end
// 
//  **********************<< �ĵ�����ͷ��Ұ����   >>************************	
//  *[��Ϣ��]
//  *EmCnAction         emCnStart,  emCnStop			 
//  *EmDCamZoom �ĵ�����ͷ��Ұ����
//   emDCamZoomWide       �Ŵ���Ұ
//   emDCamZoomTele       ��С��Ұ 
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamZoom_Cmd )
   _body( EmCnAction, 1 )
   _body( EmDCamZoom, 1 )
   _ev_end
// 
// 
//  **********************<< �����ĵ�����ͷԤ��λ   >>************************	
//  *[��Ϣ��]			 
//  *EmDCamPresetNum      �����Ԥ��λ���
//   emDCamPresetOne      ����Ԥ��λ1
//   emDCamPresetTwo      ����Ԥ��λ2 
//   emDCamPresetThree    ����Ԥ��λ3
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamPreset_Cmd )
   _body( EmDCamPresetNum, 1 )
   _ev_end
// 
//  **********************<< �����ĵ�����ͷԤ��λ   >>************************	
//  *[��Ϣ��]			 
//  *EmDCamRecallNum      ���ȵ�Ԥ��λ���
//   emDCamRecallOne      ����Ԥ��λ1
//   emDCamRecallTwo      ����Ԥ��λ2 
//   emDCamRecallThree    ����Ԥ��λ3
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamRecall_Cmd )
   _body( EmDCamRecallNum, 1 )
   _ev_end
// 
//  **********************<< �ĵ�����ͷ����ѡ���Ӧ   >>************************	
//  *[��Ϣ��]			 
//  *BOOL = TRUE ����ѡ��ɹ���= FALSE ����ѡ��ʧ��
//  *EmDCamPower:�ĵ�����ͷ��������ѡ��
//   emDCamPowerOn        ����
//   emDCamPowerOff       ����
//   emDCamPowerToggle    �����뻽�ѿ����л�  
//  *[��Ϣ����]
//  *
//  *  CnDevice => CNS
   _event(  ev_Cn_DCamPower_Ind )
   _body( BOOL, 1)
   _body( EmDCamPower, 1 )
   _ev_end
// 
//  **********************<< �ĵ�����ͷ�Զ��۽����ڻ�Ӧ   >>************************	
//  *[��Ϣ��]			 
//  *BOOL = TRUE �����ɹ���= FALSE ����ʧ��
//  *EmDCamAFMode: �ĵ�������Զ��۽�ѡ��
//   emDCamAFOn          �����Զ��۽�
//   emDcamAFOff         �ر��Զ��۽�
//   emDCamAFToggle      �Զ��۽������л�
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamAFMode_Ind )
   _body( BOOL, 1)
   _body( EmDCamAFMode, 1 )
   _ev_end
// 
//  **********************<< �ĵ�����ͷ��ƽ��ģʽ���û�Ӧ   >>************************	
//  *[��Ϣ��]			 
//  *BOOL = TRUE �����ɹ���= FALSE ����ʧ��
//  *EmDCamBWMode: �ĵ��������ƽ��ģʽѡ��
//   emDcamWBAuto         �����Զ���ƽ��ģʽ
//   emDCamWBManual       �����ֶ���ƽ��ģʽ 
//   emDCamOnePush        ����һ��ʽ��ƽ��ģʽ
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamWBMode_Ind )
   _body( BOOL, 1)
   _body( EmDCamWBMode, 1 )
   _ev_end
// 
//  **********************<< �ĵ�����ͷ��Ұ���ڻ�Ӧ   >>************************	
//  *[��Ϣ��]			 
//  *BOOL = TRUE �����ɹ���= FALSE ����ʧ��
//  *EmDCamZoom �ĵ�����ͷ��Ұ����
//   emDCamZoomWide       �Ŵ���Ұ
//   emDCamZoomTele       ��С��Ұ
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamZoom_Ind )
   _body( BOOL, 1)
   _body( EmDCamZoom, 1 )
   _ev_end
// 
// 
//  **********************<< �����ĵ�����ͷԤ��λ��Ӧ   >>************************	
//  *[��Ϣ��]			 
//  *BOOL = TRUE �����ɹ���= FALSE ����ʧ��
//  *EmDCamPresetNum      �����Ԥ��λ���
//   emDCamPresetOne      ����Ԥ��λ1
//   emDCamPresetTwo      ����Ԥ��λ2 
//   emDCamPresetThree    ����Ԥ��λ3
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamPreset_Ind )
   _body( BOOL, 1)
   _body( EmDCamPresetNum, 1 )
   _ev_end
// 
//  **********************<< �����ĵ�����ͷԤ��λ��Ӧ   >>************************	
//  *[��Ϣ��]			 
//  *BOOL = TRUE �����ɹ���= FALSE ����ʧ��
//  *EmDCamRecallNum      ���ȵ�Ԥ��λ���
//   emDCamRecallOne      ����Ԥ��λ1
//   emDCamRecallTwo      ����Ԥ��λ2 
//   emDCamRecallThree    ����Ԥ��λ3
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamRecall_Ind )
   _body( BOOL, 1)
   _body( EmDCamRecallNum, 1 )
   _ev_end
   
//  **********************<< �ĵ�����ͷ����ָ��ظ���ʱ   >>************************	
//  *[��Ϣ��]			 
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamCmdAck_Timer )
   _ev_end

//  **********************<< ����ϵͳ��Դ����   >>************************	
//  *[��Ϣ��]			 
//  *EmSchPower           ����ϵͳ��Դ����ѡ��
//   emSchPowerOff        �رջ���ϵͳ��Դ
//   emSchPowerOn         ��������ϵͳ��Դ
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_Sch_Power_Cmd )
   _body( EmSchPower, 1 )
   _ev_end

//  **********************<< ϵͳ��Դ���ػ�Ӧ   >>************************	
//  *[��Ϣ��]
//  *BOOL    = TRUE �����ɹ��� = FALSE ����ʧ��   		 
//  *EmSchPower           ����ϵͳ��Դ����ѡ��
//   emSchPowerOff        �رջ���ϵͳ��Դ
//   emSchPowerOn         ��������ϵͳ��Դ
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Power_Ind )
   _body( BOOL, 1)
   _body( EmSchPower, 1 )
   _ev_end

//  **********************<< ʩ�͵µ���ϵͳ��Դ���ط���   >>************************	
//  *[��Ϣ��]			 
//  *EmSchPower           ����ϵͳ��Դ����ѡ����
//   emSchPowerOff        ��������ϵͳ��Դ�ѱ��ر�
//   emSchPowerOn         ��������ϵͳ��Դ�ѱ�����
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Power_FB_Notify )
   _body( EmSchPower, 1 )
   _ev_end

//  **********************<< ���Ƶƹ�ϵͳ��Դ����   >>************************	
//  *[��Ϣ��]			 
//  *EmSchLight           ����ϵͳ��Դ����ѡ��
//   emSchLightOff        �رյƹ�ϵͳ��Դ
//   emSchLightOn         �����ƹ�ϵͳ��Դ
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_Sch_Light_Cmd )
   _body( EmSchLight, 1 )
   _ev_end

//  **********************<<  ���Ƶƹ�ϵͳ��Դ���ػ�Ӧ  >>************************	
//  *[��Ϣ��]			 
//  *BOOL    = TRUE �����ɹ��� = FALSE ����ʧ��   		 
//  *EmSchLight           ����ϵͳ��Դ����ѡ��
//   emSchLightOff        �رյƹ�ϵͳ��Դ
//   emSchLightOn         �����ƹ�ϵͳ��Դ
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Light_Ind )
   _body( BOOL, 1)
   _body( EmSchLight, 1 )
   _ev_end

//  **********************<< ʩ�͵µ���ϵͳ�ƹ⿪�ط���   >>************************	
//  *[��Ϣ��]			 
//  *EmSchLight           �ƹ��Դ����ѡ����
//   emSchLightOff        �����ƹ��Դ�ѱ��ر�
//   emSchLightOn         �����ƹ��Դ�ѱ�����
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Light_FB_Notify )
   _body( EmSchLight, 1 )
   _ev_end

//  **********************<< ���ƶ�����ǰ�ŵƹ⿪��   >>************************	
//  *[��Ϣ��]			 
//  *EmSchMidLight           ����ϵͳ������ǰ�ŵƹ⿪��ѡ��
//   emSchMidLightOff        �رն�����ǰ�ŵƹ��Դ
//   emSchMidLightOn         ����������ǰ�ŵƹ��Դ
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_Sch_MidLight_Cmd )
   _body( EmSchMidLight, 1 )
   _ev_end
   
//  **********************<<  ���ƶ�����ǰ�ŵƹ⿪�ػ�Ӧ  >>************************	
//  *[��Ϣ��]			 
//  *BOOL    = TRUE �����ɹ��� = FALSE ����ʧ��   		 
//  *EmSchMidLight           ����ϵͳ������ǰ�ŵƹ⿪��ѡ��
//   emSchMidLightOff        �رն�����ǰ�ŵƹ��Դ
//   emSchMidLightOn         ����������ǰ�ŵƹ��Դ
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_MidLight_Ind )
   _body( BOOL, 1)
   _body( EmSchMidLight, 1 )
   _ev_end
   
//  **********************<< ʩ�͵µ���ϵͳ������ǰ�ŵƹ⿪�ؿ��ط���   >>************************	
//  *[��Ϣ��]			 
//  *EmSchMidLight           ������ǰ�ŵƹ⿪��ѡ����
//   emSchMidLightOff        ����������ǰ�ŵƹ��ѱ��ر�
//   emSchMidLightOn         ����������ǰ�ŵƹ��ѱ�����
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_MidLight_FB_Notify )
   _body( EmSchMidLight, 1 )
   _ev_end

   //  **********************<< ���ƻ������ƿ���   >>************************	
   //  *[��Ϣ��]			 
   //  *EmSchScrLight           ����ϵͳ������ǰ�ŵƹ⿪��ѡ��
   //   emSchScrLightOff        �رջ������Ƶ�Դ
   //   emSchScrLightOn         �����������Ƶ�Դ
   //  *[��Ϣ����]
   //  *
   //  *   CNS => CnDevice
   _event(  ev_Cn_Sch_ScrLight_Cmd )
   _body( EmSchScrLight, 1 )
   _ev_end
   
   //  **********************<<  ���ƻ������ƿ��ػ�Ӧ  >>************************	
   //  *[��Ϣ��]			 
   //  *BOOL    = TRUE �����ɹ��� = FALSE ����ʧ��   		 
   //  *EmSchScrLight           ����ϵͳ������ǰ�ŵƹ⿪��ѡ��
   //   emSchScrLightOff        �رջ������Ƶ�Դ
   //   emSchScrLightOn         �����������Ƶ�Դ
   //  *[��Ϣ����]
   //  *
   //  *   CnDevice => CNS
   _event(  ev_Cn_Sch_ScrLight_Ind )
   _body( BOOL, 1)
   _body( EmSchScrLight, 1 )
   _ev_end
   
   //  **********************<< ʩ�͵µ���ϵͳ���ƻ������ƿ��ط���   >>************************	
   //  *[��Ϣ��]			 
   //  *EmSchScrLight           ������ǰ�ŵƹ⿪��ѡ����
   //   emSchScrLightOff        �������������ѱ��ر�
   //   emSchScrLightOn         �������������ѱ�����
   //  *[��Ϣ����]
   //  *
   //  *   CnDevice => CNS
   _event(  ev_Cn_Sch_ScrLight_FB_Notify )
   _body( EmSchScrLight, 1 )
   _ev_end


//  **********************<< ���������Ӧ�������������   >>************************	
//  *[��Ϣ��]			 
//  *EmSchArgus           �����Ӧ��������������ѡ��
//   emSchArgusUnlock     ��������Ӧ��������
//   emSchArgusLock       ���������Ӧ��
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_Sch_Argus_Cmd )
   _body( EmSchArgus, 1 )
   _ev_end

//  **********************<< ʩ�͵µ���ϵͳ��Ӧ�����������״̬����   >>************************	
//  *[��Ϣ��]			 
//  *EmSchArgus           ���������Ӧ��������������״̬
//   emSchArgusUnlock     ���������Ӧ���ѱ�����
//   emSchArgusLock       ���������Ӧ���ѱ�����
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Argus_FB_Notify )
   _body( EmSchArgus, 1 )
   _ev_end

//  **********************<< ʩ�͵µ���ϵͳ�����¶ȷ���   >>************************	
//  *[��Ϣ��]			 
//  *u16 Ԥ��λ���
//  *[��Ϣ����]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Temp_FB_Notify )
   _body( u16, 1)
   _ev_end

//  **********************<< ʩ�͵µ�������ָ��ظ���ʱ   >>************************	
//  *[��Ϣ��]			 
//  *[��Ϣ����]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_SchCmdAck_Timer )
   _ev_end

/***********************<< ��ʩ�͵µ���ϵͳ�����������ָ�� >>************************	
 *[��Ϣ��]			 
 *    + s8  д��ʩ�͵µ������ƴ��ڵĲ���ָ��
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_Sch_Set_Cmd )
   _body (   s8        ,    1 )
   _ev_end

/***********************<< �趨T300�ر�ϵͳ��Դ���������Ӧ�������ĳ�ʱ >>************************	
 *[��Ϣ��]			 
 *
 *[��Ϣ����]
 *
 *   CnDevice => CnDevice
 */_event(  ev_Cn_Sch_UnlockArgus_Timer )
   _ev_end

/***********************<< ϵͳǿ�翪��֪ͨ >>************************	
 *[��Ϣ��]			 
 //  *EmSchPower           ����ϵͳ��Դ����ѡ��
 //   emSchPowerOff        �رջ���ϵͳ��Դ
 //   emSchPowerOn         ��������ϵͳ��Դ
 *[��Ϣ����]
 *
 *   CnDevice => CnDevice
 */_event(  ev_Cn_Cenctrl_SysPower_Nty )
   _body( EmSchPower, 1 )
   _ev_end

//End Add

//add for air-control by zhangapei
/***********************<< ֪ͨ����յ����� >>************************	
 *[��Ϣ��]
 *  + TCentreACCfg   �յ������б�
 *  + BOOL           �յ��б�  TRUE ��λ�ÿյ����� FALSE ��λ�ÿյ�������
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreACStateNty   )
   _body(   TCentreACCfg, MAX_AC_NUM  )
   _body(   BOOL        , MAX_AC_NUM  )
   _ev_end

/***********************<< �趨�пؿյ����� >>************************	
 *[��Ϣ��]	
 *    + EmCentreACPower  Off/On
 *
 *[��Ϣ����]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACPowerCmd )
   _body(   u8             ,      1  )
   _body(   EmCentreACPower,      1  )
   _ev_end

/***********************<< �趨�пؿյ����ط�����Ϣ >>************************	
 *[��Ϣ��]	
 *    + EmCentreACPower  Off/On
 *    + BOOL ���óɹ�TRUE�� ʧ��FALSE
 *
 *[��Ϣ����]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACPowerInd )
   _body(   u8             ,      1  )
   _body(   EmCentreACPower,      1  )
   _body(   BOOL ,                1  )
   _ev_end

/***********************<< �趨�пؿյ��¶����� >>************************	
 *[��Ϣ��]	
 *    + u8   �¶�  17��C -- 30��C
 *
 *[��Ϣ����]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACTempCmd )
   _body(  u8   ,                1  )
   _ev_end

/***********************<< �趨�пؿյ��¶ȷ�����Ϣ >>************************	
 *[��Ϣ��]	
 *    + u8   �¶�  17��C -- 30��C
 *    + BOOL ���óɹ�TRUE�� ʧ��FALSE
 *
 *[��Ϣ����]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACTempInd )
   _body(   u8   ,                1  )
   _body(   BOOL ,                1  )
   _ev_end


/***********************<< �趨�пؿյ�ģʽ >>************************	
 *[��Ϣ��]		
 *     + EmCentreACMode    
 *
 *[��Ϣ����]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACModeCmd )
   _body(   EmCentreACMode  ,     1  )
   _ev_end

/***********************<< �趨�пؿյ�ģʽ������Ϣ >>************************	
 *[��Ϣ��]		
 *     + EmCentreACMode 
 *     + BOOL          ���óɹ�TRUE/ʧ��FALSE
 *
 *[��Ϣ����]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACModeInd )
   _body(   EmCentreACMode  ,     1  )
   _body(   BOOL ,                1  )
   _ev_end


/***********************<< �趨�пؿյ��·���� >>************************	
 *[��Ϣ��]		
 *     + EmCentreACAirVol   �Զ���1--5 
 *
 *[��Ϣ����]
 *
 *   Cns=> CnDevice
 */_event(  ev_Cn_CentreSetACAirVolCmd )
   _body(   EmCentreACAirVol,     1  )
   _ev_end


/***********************<< �趨�пؿյ��·����������Ϣ >>************************	
 *[��Ϣ��]		
 *     + u8    ��9��   
 *     + BOOL  ���óɹ�TRUE �� ʧ�� FALSE
 *
 *[��Ϣ����]
 *
 *   Cns=> CnDevice
 */_event(  ev_Cn_CentreSetAirVolInd )
   _body(   EmCentreACAirVol,     1  )
   _body(   BOOL ,                1  )
   _ev_end

/***********************<< ��յ��豸�����������ָ�� >>************************	
*[��Ϣ��]			 
*    + s8  д��յ����ƴ��ڵĲ���ָ��
*[��Ϣ����]
*
*   CnDevice => CnDevice
*/_event(  ev_Cn_AC_Set_Cmd )
  _body (   s8        ,    1 )
  _ev_end

//add end

//set Timer for sleep  
/***********************<< ����״̬֪ͨ >>************************	
 *[��Ϣ��]		
 *     +EmCALLSTATE  	em_CALL_IDLE      ����
 *						em_CALL_CALLING   ���ں���
 *						em_CALL_CONNECTED ���
 *
 *[��Ϣ����]  
 * CnCall => CnDevice
 */_event(  ev_Cn_CallStateNty     )
   _body(   EmCALLSTATE,         1 )
   _ev_end

/***********************<< �趨������ʱ�� >>************************	
 *[��Ϣ��]		
 *NULL
 *
 *[��Ϣ����]  
 * CnDevice => CnDevice
 */_event(  ev_Cn_DeviceSleep_Timer )
   _ev_end

/***********************<< ʩ�͵´���/����֪ͨ >>************************	
 *[��Ϣ��]		
 *    +EmCenSchMode     emSchSleep/����   emSchWakeUp/����
 *
 *[��Ϣ����]  
 *
 * CnDevice => CnDevice
 */_event(  ev_Cn_CentreSchSleepNty )
   _body(   EmCenSchMode,       1   )
   _ev_end

/***********************<< ���ô�����Ϣ >>************************	
 *[��Ϣ��]		
 *    + TTPSleepInfo ������Ϣ����
 *
 *[��Ϣ����]  
 *
 * UE => CnDevice
 */_event(  ev_Cn_SetSleepInfoCmd )
   _body(   TCenDevSleepInfo ,   1    )
   _ev_end

/***********************<< ���ô�����ϢӦ�� >>************************	
 *[��Ϣ��]		
 *    + TTPSleepInfo ������Ϣ����
 *    + Bool  =FALSE �޸�ʧ�ܣ�= TRUE �޸ĳɹ�
 *
 *[��Ϣ����]  
 *
 * UE => CnDevice
 */_event(  ev_Cn_SetSleepInfoInd )
   _body(   TCenDevSleepInfo , 1  )
   _body(   BOOL             , 1  )
   _ev_end

/***********************<< �������֪ͨ >>************************	
 *[��Ϣ��]		
 *    +u8    node_cnc/node_cnstools
 *
 *[��Ϣ����]  
 *
 * UE => CnDevice
 */_event(  ev_Cn_UEMsgNty )
   _body(   u8 ,      1    )
   _ev_end

/***********************<< �пش���֪ͨ���� >>************************	
 *[��Ϣ��]		
 *
 *[��Ϣ����]  
 *
 * UE <= CnDevice
 */_event(  ev_Cn_CentreSleepNty )
   _ev_end

 /***********************<< �յ�ѡ����Ϣ >>************************	
 *[��Ϣ��]
 *  + u8   �յ�ѡ������
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreSelectAC_Cmd   )
   _body(   u8            ,         1   )
   _ev_end

 /***********************<< �յ�ѡ�񷵻���Ϣ >>************************	
 *[��Ϣ��]
 *  + u8   �յ�ѡ������
 *  + BOOL �������
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreSelectAC_Ind   )
   _body(   u8            ,         1   )
   _body(   BOOL          ,         1   )
   _ev_end

/***********************<< �յ����ÿ��� >>************************	
 *[��Ϣ��]
 *  + u8        ѡ�пյ�������
 *  + BOOL      Ҫ�޸ĵĿյ��б� = TRUE Ҫ�����޸� =FALSE ����Ҫ�޸�
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreACCopyCmd   )
   _body(   u8        , 1            )
   _body(   BOOL      , MAX_AC_NUM   )
   _ev_end

/***********************<< �յ����ÿ���������Ϣ >>************************	
 *[��Ϣ��]
 *  + BOOL      Ҫ�޸ĵĿյ��б�
 *  + BOOL      �޸Ľ��
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreACCopyInd   )
   _body(   BOOL        , MAX_AC_NUM )
   _body(   BOOL        , 1          )
   _ev_end

/***********************<< CNC��ַ������֪ͨ >>************************	
 *[��Ϣ��]
 *
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_cns_cncAddrBookNty   )
   _ev_end

/***********************<< ϵͳ�����ϵ���ʱ�򿪵��ӻ� >>************************	
 *[��Ϣ��]
 *
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_SetTvPowerTimer   )
   _ev_end
   
/*************************<< �пأ�������������  >>******************************	
 *[��Ϣ��]
 * +BOOL         �����б�=TRUE��ʶѡ����Ҫ�޸ģ�=FALSE��ʶ��û��ѡ��
 * +EmCurAction  ����������emCurUp ���� emCurDown �½� emCurStop ֹͣ
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurActCmd      )
   _body(BOOL       , MAX_CURTAIN_NUM  )
   _body(EmCurAction, 1                )
   _ev_end

/*************************<< �пأ�������������  >>******************************	
 *[��Ϣ��]
 * +BOOL         �����б�=TRUE��ʶѡ����Ҫ�޸ģ�=FALSE��ʶ��û��ѡ��
 * +EmCurAction  ����������emCurUp ���� emCurDown �½� emCurStop ֹͣ
 * +BOOL         ���������б� =TRUE���óɹ�  =FALSE ����ʧ��      
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurActInd      )
   _body(BOOL       , MAX_CURTAIN_NUM  )
   _body(EmCurAction, 1                )
   _body(BOOL       , MAX_CURTAIN_NUM  )
   _ev_end

/*************************<< �пأ���������֪ͨ  >>******************************	
 *[��Ϣ��]
 *
 * +TCentreCurInfo ������Ϣ
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurInfoNty)
   _body(TCentreCurInfo,		1 )
   _ev_end

/**********************<< �������������֮��ʱ����Ԥ��λ >>*************************	
 *[��Ϣ��]
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_SetDocRecallPresetTimer  )
   _ev_end

/**********************<< ��Ӧ�������������ʱ�ر����д��������· >>*************************	
 *[��Ϣ��]
 *  
 *[��Ϣ����]
 *   
 *      cns => cns 
 */_event(  ev_Cn_SetCurtainPowerDownTimer  )
   _ev_end


 /***********************<< �������ݷ���  >>************************	
 *[��Ϣ��]		
 *    + u8    ��������
 *    + u8    ��������
 *
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_SerialRecvByteInd  )
   _body (  u8          ,    1  )
   _body (  u8          ,    1  )
   _ev_end

   _event(  ev_cns_centreTV0InputSelKeepTimer  )
   _ev_end

   _event(  ev_cns_centreTV1InputSelKeepTimer  )
   _ev_end

   _event(  ev_cns_centreTV2InputSelKeepTimer  )
   _ev_end
   
   
//Add end
/***********************<< ϵͳ�����ϵ���ʱ�򿪵��ӻ� >>************************	
 *[��Ϣ��]
 *
 *  
 *[��Ϣ����]
 *   
 *      cns => cns 
 */_event(  ev_Cn_SetTvInpSelectTimer   )
   _ev_end

/***********************<< �ĵ��������Դ���ر�����ʱ�� >>************************	
 *[��Ϣ��]
 *
 *  
 *[��Ϣ����]
 *   
 *      cns => cns 
 */_event(  ev_Cn_SetDCamPowerKeepTimer   )
   _ev_end

/*************************<< �����пش�������  >>******************************	
 *[��Ϣ��]
 * +u8  ��������
 * +s8  ������
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurNameCmd  )
   _body(	u8            ,      1  )
   _body(   TCentreCurName,		 1  )
   _ev_end

/*************************<< �����пش����Ƿ����  >>******************************	
 *[��Ϣ��]
 *  +BOOL  = TURE �������ڣ�= FALSE ������
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurOpenCmd  )
   _body(	BOOL          ,      1  )
   _ev_end

/*************************<< �����пش�����  >>******************************	
 *[��Ϣ��]
 *  +u8   num ������
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurNumCmd  )
   _body(	u8           ,      1  )
   _ev_end

/*************************<< �����пص��ӻ��ͺ�  >>******************************	
 *[��Ϣ��]
 * +u8  ��������
 * +s8  ������
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreTVModleCmd  )
   _body(	EmTVModle        ,      1  )
   _ev_end

/*************************<< ���ӻ��ͺ����÷���  >>******************************	
 *[��Ϣ��]
 * +u8  ��������
 * +s8  ������
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreTVModleInd  )
   _body(	EmTVModle        ,      1  )
   _body(   BOOL			 ,		1  )
   _ev_end

//�ĵ����������¹���  2015/3/16 
/*************************<< �ĵ�������������  >>******************************	
 *[��Ϣ��]
 * +EmFocus  emNear ����  emFar ��Զ
 *  
 *[��Ϣ����]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_DCamFocusCmd  )
   _body(	EmFocus       ,    1  )
   _ev_end

/***********************<< ������Զ��ع����� >>************************	
 *[��Ϣ��]			 
 *   EmExpMode   
 *
 *[��Ϣ����]
 *   
 *   cnc => cns 
 */_event(  ev_Cn_DCamAutoExposureCmd  )
   _body (  EmExpMode,                1)
   _ev_end

/***********************<< ������ֶ��ع⡪������������� >>************************	
 *[��Ϣ��]
 *
 * EmGain  ���淶Χ 0dB  3dB  6dB ������42dB
 *
 *[��Ϣ����]
 *  
 *   cnc => cns 
 */_event(  ev_Cn_DCamGainCmd  )
   _body (  EmGain    ,1)
   _ev_end
   

/***********************<< ������ֶ��ع⡪�����ŵ������� >>************************	
 *[��Ϣ��]
 *
 * EmShutSpd  ���ŷ�Χ 1/60  1/120 1/250.....1/4000  1/10000
 *
 *[��Ϣ����]
 *   
 *   cnc => cns 
 */_event(  ev_Cn_DCamShutSpdCmd  )
   _body (  EmShutSpd    ,1)
   _ev_end


/***********************<< ������ֶ��ع⡪����Ȧ�������� >>************************	
 *[��Ϣ��]
 *
 * u8  ��Ȧ��С ��Χ 0--100
 *
 *[��Ϣ����]
 *   
 *   cnc => cns 
 */_event(  ev_Cn_DCamApertureCmd)
   _body (  EmSonyIris    ,     1)
   _ev_end

//add end


		
#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnscentre )
};
#endif
#endif 
