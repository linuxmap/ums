#ifndef _h_eventoutcnscamera_h__
#define _h_eventoutcnscamera_h__

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCAMERAEVENT
{
#endif 
	
	_ev_segment( outercnscamera  )


/***********************<< ά�����ߵ�½֪ͨ  >>************************	
 *[��Ϣ��]		
 *
 *
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_GetCameraInfo_Req )
   _ev_end

/**********************<< �������������֪ͨ >>**********************
*[��Ϣ��]
*
*
*[��Ϣ����]
*
* UI => cns => cnDevice
*/_event( ev_Cn_LoadCameraFileNty )
  _ev_end

  /**********************<< ������ϵ�֪ͨ >>**********************
  *[��Ϣ��]
  *
  *    + BOOL    =TRUE tptools����ʱ���������ϵ��֪ͨ FALSE �������
  *
  *[��Ϣ����]
  *
  *   cnDevice => cnDevice
  */_event( ev_Cn_CameraPowerOnNty )
	_body(  BOOL,      1           )
    _ev_end


/***********************<< ���������֪ͨ  >>************************	
 *[��Ϣ��]		
 *    + TCnCameraCfg    ��ȡ������������ļ�
 *    + u8              ��ǰ���������
 *
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraCfgNty                )
   _body (  TCnCameraCfg, MAX_CNCAMERA_NUM )
   _body (  u8          ,    1             )
   _ev_end


/***********************<< ѡ��������������  >>************************	
 *[��Ϣ��]			 
 *    + u8  ����ͷ���� 0-2
 *
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraSelectCmd )
   _body (  u8         ,       1 )
   _ev_end

/***********************<< ѡ������������������  >>************************	
 *[��Ϣ��]			 
 *    + u8    ����ͷ���� 0-2
 *    + BOOL  = TRUE ѡ��ɹ� =FALSE ѡ��ʧ��
 *[��Ϣ����]
 *
 *   CNS <= CnDevice
 */_event(  ev_Cn_CameraSelectInd )
   _body (   u8         ,       1 )
   _body (   BOOL       ,       1 )
   _ev_end

/***********************<< ����ͷ�۽�����  >>************************	
 *[��Ϣ��]			 
 *    + EmFocus         emFar Զ��  emNear����
 *    + EmCnAction      emCnStart/emCnStop
 *
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraFocusCmd   )
   _body (  EmFocus        ,1 )
   _body (  EmCnAction     ,1 )
   _ev_end

/***********************<< ����ͷ�۽���������  >>************************	
 *[��Ϣ��]			 
 *    + EmFocus         emFar Զ��  emNear����
 *    + BOOL        =TRUE ���óɹ�  =FALSE ����ʧ��
 *
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraFocusInd   )
   _body (  EmFocus        ,1 )
   _body (  BOOL           ,1 )
   _ev_end

/***********************<< ����ͷ�Զ��۽�����  >>**********************	
 *[��Ϣ��]			 
 *    EmFocusMode 
 *
 *[��Ϣ����]
 *
 *   CNS      => CnDevice
 */_event(  ev_Cn_CameraAutoFocusCmd  	)
   _body (  EmFocusMode,        1  )
   _ev_end
 
/***********************<< ����ͷ�Զ��۽���������  >>**********************	
 *[��Ϣ��]			 
 * BOOL   =TRUE ���óɹ�   =FALSE ����ʧ��
 *
 *[��Ϣ����]
 *
 *   CNS      <= CnDevice
 */_event(  ev_Cn_CameraAutoFocusInd  	)
   _body (  EmFocusMode,        1  )
   _body (  BOOL ,  1)
   _ev_end


/***********************<< ������Ұ��������  >>************************	
 *[��Ϣ��]			 
 *    EmZoom          emTele ��ͷ����  emWide ��ͷ��Զ 
 *
 *[��Ϣ����]
 *
 *   CNS     => CnDevice
 */_event(  ev_Cn_CameraZoomCmd    )
   _body ( EmZoom               ,1 )
   _ev_end
 
/***********************<< ������Ұ���ڷ�������  >>************************	
 *[��Ϣ��]			 
 *    EmZoom           ����/��Զ
 *    BOOL            =TRUE ���óɹ�  =FALSE ����ʧ��  
 *
 *[��Ϣ����]
 *
 *   CNS     <=  CnDevice
 */_event(  ev_Cn_CameraZoomInd  )
   _body (  EmZoom          , 1  )
   _body (  u16             , 1  )
   _body (  BOOL            , 1  )
   _ev_end

 
/***********************<< Ԥ��λ��������  >>************************	
 *[��Ϣ��]	
 *
 *[��Ϣ����]
 *
 *   CNS    => CnDevice
 */_event(  ev_Cn_CameraPersetSaveCmd	  )
   _ev_end

/***********************<< Ԥ��λ���淵������  >>************************	
 *[��Ϣ��]	
 *    + BOOL    TRUE= ����Ԥ��λ�ɹ�   = FALSE ����ʧ��		 
 *
 *[��Ϣ����]
 *
 *   CNS    <=  CnDevice
 */_event(  ev_Cn_CameraPersetSaveInd	  )
   _body (  BOOL ,              1     )
   _ev_end

 /***********************<< �����´ο�������Ԥ��λ1  >>************************	
 *[��Ϣ��]			 
 *    + BOOL   =TURE ����  =FALSE �رյ���
 *
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraPresetCmd )
   _body (  BOOL,    1 )
   _ev_end


 /***********************<< ����Ԥ��λ���÷���ֵ  >>************************	
 *[��Ϣ��]			 
 *    + BOOL   =TURE �´ο�������Ԥ��λ1  =FALSE �رյ���  
 *    + BOOL   =TURE д��ɹ�  =FALSE д��ʧ��
 *[��Ϣ����]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraPresetInd )
   _body (  BOOL,    1 )
   _body (  BOOL,    1 )
   _ev_end

/***********************<< �ָ�������������� >>************************	
 *[��Ϣ��]			 
 * ��
 *[��Ϣ����]
 *   
 *   CNS          => CnDevice
 */_event(  ev_Cn_CameraResetCmd  )
   _ev_end

/***********************<< �ָ�������������÷�����Ϣ >>************************	
 *[��Ϣ��]			 
 *      TCnCameraCfg ��ȡ�ָ���Ĭ�ϵ������ֵ ���ظ�UI
 *      u8           �����������
 *      BOOL   =TRUE ���óɹ�  FALSE ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS          <=  CnDevice
 */_event(  ev_Cn_CameraResetInd  )
   _body (  TCnCameraCfg,      1  )
   _body (  u8   ,             1  )
   _body (  BOOL ,             1  )
   _ev_end

/***********************<< ����� ��Ұ��OSD����ʾ�������� >>************************	
 *[��Ϣ��]			 
 *   EmOSDShow     ��ʾ���� emOSDOff / emOSDOn
 * 
 *
 *[��Ϣ����]
 *
 *   CNS          =>CnDevice
 */_event(  ev_Cn_CameraOSDShowCmd  )
   _body (  EmOSDShow ,    1)
   _ev_end

/**********************<< ����� ��Ұ��OSD����ʾ������������ >>************************	
 *[��Ϣ��]			 
 *
 * EmOSDShow     emOSDOff/emOSDOn 
 * BOOL          =TRUE ���óɹ�  =FALSE ����ʧ��
 *[��Ϣ����]
 *
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraOSDShowInd  )
   _body (  EmOSDShow ,    1)
   _body (  BOOL      ,    1)
   _ev_end


/***********************<< ������Զ��ع����� >>************************	
 *[��Ϣ��]			 
 *   EmExpMode   
 *
 *[��Ϣ����]
 *   
 *   CNS          =>CnDevice
 */_event(  ev_Cn_CameraAutoExposureCmd  )
   _body (  EmExpMode,                1)
   _ev_end

 /***********************<< ������Զ��عⷵ������ >>************************	
 *[��Ϣ��]			 
 * BOOL       =TRUE ���óɹ�  =FALSE ����ʧ�� 
 *
 *[��Ϣ����]
 *   
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraAutoExposureInd  )
   _body (  EmExpMode,                1  )
   _body (  BOOL ,                    1  )
   _ev_end


/***********************<< ������ֶ��ع⡪������������� >>************************	
 *[��Ϣ��]
 *
 * EmGain  ���淶Χ 0dB  3dB  6dB ������42dB
 *
 *[��Ϣ����]
 *  
 *   CNS          => CnDevice
 */_event(  ev_Cn_CameraGainCmd  )
   _body (  EmGain    ,1)
   _ev_end
   
/***********************<< ������ֶ��ع⡪��������ڷ������� >>************************	
 *[��Ϣ��]
 *
 * EmGain  ���淶Χ 0dB  3dB  6dB ������42dB
 * BOOL    =��TRUE ���óɹ�   =FALSE ����ʧ��
 *
 *[��Ϣ����]
 *  
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraGainInd  )
   _body ( EmGain    ,1)
   _body ( BOOL      ,1)
   _ev_end

/***********************<< ������ֶ��ع⡪�����ŵ������� >>************************	
 *[��Ϣ��]
 *
 * EmShutSpd  ���ŷ�Χ 1/60  1/120 1/250.....1/4000  1/10000
 *
 *[��Ϣ����]
 *   
 *   CNS          => CnDevice
 */_event(  ev_Cn_CameraShutSpdCmd  )
   _body (  EmShutSpd    ,1)
   _ev_end

/***********************<< ������ֶ��ع⡪�����ŵ��ڷ������� >>************************	
 *[��Ϣ��]
 *
 * EmShutSpd  ���ŷ�Χ 1/60  1/120 1/250.....1/4000  1/10000
 * BOOL      =TRUE  ���óɹ�  =FALSE ����ʧ��
 *
 *[��Ϣ����]
 *   
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraShutSpdInd  )
   _body ( EmShutSpd    ,1)
   _body ( BOOL         ,1)
   _ev_end

/***********************<< ������ֶ��ع⡪������������� >>************************	
 *[��Ϣ��]
 *
 * EmBackLightType  ����ģʽ  �رգ�multi��Ĭ��7����Χ0-15����center��face detect
 * u8  0--15 multiģʽ����  ���� ֵ����Ϊ 0--15֮���ֵ
 *
 *[��Ϣ����]
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraBackLightCmd  )
   _body (  EmBackLightType    ,1)
   _body (  u8                 ,1)
   _ev_end

/***********************<< ������ֶ��ع⡪��������ڷ������� >>************************	
 *[��Ϣ��]
 *
 * EmBackLightType  ����ģʽ  �رգ�multi����Χ0-15����center��face detect
 * BOOL   =TRUE  ���óɹ�    =FALSE  ����ʧ��
 *
 *[��Ϣ����]
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraBackLightInd  )
   _body ( EmBackLightType    ,1)
   _body (  u8                ,1)
   _body ( BOOL               ,1)
   _ev_end

/***********************<< ������ֶ��ع⡪����Ȧ�������� >>************************	
 *[��Ϣ��]
 *
 * u8  ��Ȧ��С ��Χ 0--100
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraApertureCmd  )
   _body (  u8    ,1)
   _ev_end

/***********************<< ������ֶ��ع⡪����Ȧ���ڷ������� >>************************	
 *[��Ϣ��]
 *
 * u8  ��Ȧ��С ��Χ 0--100
 * BOOL   =TRUE ���óɹ�   =FALSE ����ʧ��
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraApertureInd  )
   _body (  u8    ,1)
   _body (  BOOL  ,1)
   _ev_end

/***********************<< ������Զ���ƽ������ >>************************	
 *[��Ϣ��]
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraAutoWBCmd  )
   _body (  EmWBMode,        1  )
   _ev_end

/***********************<< ������Զ���ƽ�ⷵ������ >>************************	
 *[��Ϣ��]
 *   BOOL       = TRUE  ���óɹ�  =FALSE ����ʧ��  
 *
 *[��Ϣ����]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraAutoWBInd  )
   _body (  EmWBMode,           1  )
   _body (  BOOL   ,            1  )
   _ev_end

/***********************<< ������ֶ���ƽ��--R Gain���� >>************************	
 *[��Ϣ��]
 *
 *  u16  R Gain ��Χ 0--100 
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraRGainCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< ������ֶ���ƽ��--R Gain�������� >>************************	
 *[��Ϣ��]
 *
 *  u16  R Gain ��Χ 0--100 
 *  BOOL   =TRUE ���óɹ�      =FALSE  ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraRGainInd  )
   _body (  u16       ,        1  )
   _body (  BOOL      ,        1  )
   _ev_end

/***********************<< ������ֶ���ƽ��--B Gain���� >>************************	
 *[��Ϣ��]
 *
 *  u16  B Gain ��Χ 0--100 
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraBGainCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< ������ֶ���ƽ��--B Gain�������� >>************************	
 *[��Ϣ��]
 *
 *  u16  B Gain ��Χ 0--100 
 *  BOOL    =TRUE  ���óɹ�  =FALSE ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraBGainInd  )
   _body (  u16       , 1  )
   _body (  BOOL      , 1  )
   _ev_end

 /***********************<< ���������ģʽ ���� >>************************	
 *[��Ϣ��]
 *
 *  EmPicSceMode  ����ģʽ   �չ��ģʽ  ̫����ģʽ �ֶ�ģʽ
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraPicSceneModeCmd  )
   _body (  EmPicSceMode       , 1  )
   _ev_end

 /***********************<< ���������ģʽ�������� >>************************	
 *[��Ϣ��]
 *
 *  EmPicSceMode  ����ģʽ   �չ��ģʽ  ̫����ģʽ �ֶ�ģʽ
 *  BOOL     =TRUE   ���óɹ�   =FALSE  ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraPicSceneModeInd  )
   _body (  EmPicSceMode       , 1  )
   _body (  BOOL               , 1  )
   _ev_end

/***********************<< ����� ģʽ--- �ֶ� GAMMA�������� >>************************	
 *[��Ϣ��]
 *
 *  EmGamma 
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraGammaCmd  )
   _body (  EmGamma       , 1)
   _ev_end

/***********************<< ����� ģʽ--- �ֶ� GAMMA���ڷ������� >>************************	
 *[��Ϣ��]
 *
 *  EmGamma  emGammaOff��emGammaOn ��emSmart1�� emStrat2
 *  BOOL   =TRUE  ���óɹ�   =FALSE ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraGammaInd  )
   _body (  EmGamma       , 1  )
   _body (  BOOL          , 1  )
   _ev_end

/***********************<< ����� ģʽ--- ��Ȧ�������� >>************************	
 *[��Ϣ��]
 *
 *  u8 ��Ȧ��С  1--15
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraPicSceAptCmd  )
   _body (  u8          , 1  )
   _ev_end

 /***********************<< ����� ģʽ--- ��Ȧ���ڷ������� >>************************	
 *[��Ϣ��]
 *
 *  u8 ��Ȧ��С  1--15
 *  BOOL    =TRUE  ���óɹ�   =FALSE  ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraPicSceAptInd  )
   _body (  u8          , 1  )
   _body (  BOOL        , 1  )
   _ev_end  

/***********************<< ����� ͼƬ����---�Աȶ� �������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraContrastCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< ����� ͼƬ����---�Աȶ� ���ڷ������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *  BOOL     =TRUE  ���óɹ�    =FALSE  ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        =< CnDevice
 */_event(  ev_Cn_CameraContrastInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< ����� ͼƬ����---ɫ�� �������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *
 *[��Ϣ����]
 *  
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraHueCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< ����� ͼƬ����---ɫ�� ���ڷ������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *  BOOL      =TRUE  ���óɹ�   =FALSE  ����ʧ��
 *[��Ϣ����]
 *  
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraHueInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< ����� ͼƬ����---���Ͷ� �������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraSaturatCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< ����� ͼƬ����---���Ͷ� ���ڷ������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *  BOOL      =TRUE  ���óɹ�  =FALSE ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraSaturatInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< ����� ͼƬ����---���� �������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraBrightCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< ����� ͼƬ����---���� ���ڷ������� >>************************	
 *[��Ϣ��]
 *
 *  u16  ��С  0--200
 *  BOOL       =TRUE ���óɹ�  FALSE ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraBrightInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< ����� ����---������ �������� >>************************	
 *[��Ϣ��]
 *
 *  EmStmClean  Ĭ��LOW  ��ΧOFF,LOW,MID,HIGH
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraNRStmCleanCmd  )
   _body (  EmStmClean        , 1)
   _ev_end

/***********************<< ����� ����---������ ���ڷ������� >>************************	
 *[��Ϣ��]
 *
 *  EmStmClean  Ĭ��LOW  ��ΧOFF,LOW,MID,HIGH
 *  BOOL      =TURE   ���óɹ�  =FALSE  ����ʧ��
 *[��Ϣ����]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraNRStmCleanInd  )
   _body (  EmStmClean        , 1)
   _body (  BOOL              , 1)
   _ev_end

/***********************<< ����� ����---3D���� �������� >>************************	
 *[��Ϣ��]
 *
 *  Em3DNR   em3DNROff ��OFF��em3DNROn ��
 *
 *[��Ϣ����]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_Camera3DNRCmd  )
   _body (  Em3DNR       ,  1)
   _ev_end

/***********************<< ����� ����---3D���� ���ڷ������� >>************************	
 *[��Ϣ��]
 *  Em3DNR   em3DNROff ��OFF��em3DNROn ��
 *  BOOL     =TRUE  ���óɹ�  =FALSE ����ʧ��
 *  
 *[��Ϣ����]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_Camera3DNRInd  )
   _body (  Em3DNR       ,  1)
   _body (  BOOL         , 1)
   _ev_end
		
/***********************<< ��ȷ���������zoomֵ >>************************	
 *[��Ϣ��]
 *    + u16  ������Ϣ�޷����ݸ���ֵ ��������汣����λС������100תΪu16����
 *  
 *[��Ϣ����]
 *   
 *   CNS       => CnDevice
 */_event(  ev_Cn_SetCameraZoomCmd  )
   _body (  u16        ,       1    )
   _ev_end		

 /********************<< ��ȷ���������zoomֵ����ֵ >>**********************	
 *[��Ϣ��]
 *    + u16
 *    + BOOL
 *  
 *[��Ϣ����]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_SetCameraZoomInd  )
   _body (  u16        ,       1    )
   _body (  BOOL       ,       1    )
   _ev_end
   
 /********************<< �пؿ������������Դ���� >>**********************	
 *[��Ϣ��]
 *    + EmCamPowerMode     emCamPowerOn/emCamPowerOff
 *  
 *[��Ϣ����]
 *   
 *   Centre   <= CnDevice
 */_event(  ev_Cn_SetCamPowerModeCmd  )
   _body (  EmCamPowerMode,      1    )
   _ev_end

/********************<< ���������Դ״̬֪ͨ�п�ά������ >>**********************	
 *[��Ϣ��]
 *    + EmCamPowerMode     emCamPowerOn/emCamPowerOff
 *  
 *[��Ϣ����]
 *   
 *   Centre   <= CnDevice
 */_event(  ev_Cn_CamPowerStateNty          )
   _body (  EmCamPowerMode, MAX_CNCAMERA_NUM)
   _ev_end

/********************<< ������ϵ���ʱ��ʱ�� >>**********************	
 *[��Ϣ��]
 *  
 *[��Ϣ����]
 *   
 *   CnDevice   <= CnDevice
 */_event(  ev_Cn_CamPowerOnTimer  )
   _ev_end

/********************<< ���������ѡ�� >>**********************	
 *[��Ϣ��]
 *  + EmCamType  ���������
 *[��Ϣ����]
 *   
 *   CnDevice   <= CnDevice
 */_event(  ev_Cn_SetCamType_Cmd  )
   _body(EmCamType, 1 )
   _ev_end


/***********************<< Sony���������������� >>************************	
 *[��Ϣ��]
 *  +BOOL   sony������ڿ��� = TRUE��  =FALSE ��
 *
 *[��Ϣ����]
 *   CNS        => CnDevice
 */_event(  ev_Cn_SonyBackLightCmd  )
   _body (  BOOL               ,1)
   _ev_end

/***********************<< Sony������������� >>************************	
 *[��Ϣ��]
 *    +BOOL   =TRUE  �򿪽���    =FALSE  �رս���
 *    +u8     ����ʱ��֧��level 1-5�ɵ�
 *
 *[��Ϣ����]
 *   CNS        <= CnDevice
 */_event(  ev_Cn_SonyStmClenCmd  )
   _body (  BOOL              ,1)
   _body (  u8                ,1)
   _ev_end



#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnscamera )
};
#endif
#endif 