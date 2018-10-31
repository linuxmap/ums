#ifndef _h_eventoutcnspancamera_h__
#define _h_eventoutcnspancamera_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSPANCAMEVENT
{
#endif 
	
	_ev_segment( outercnspancamera  )

/***********************<< ȫ�������ѡ�� >>************************	
 *[��Ϣ��]
 *  + u8  ���������
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSelectCmd )
   _body(  u8,                  1 )
   _ev_end

/***********************<< ȫ�������ѡ���� >>************************	
 *[��Ϣ��]
 *  + u8  ���������
 *  + BOOL 
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSelectInd )
   _body(  u8,                  1 )
   _body(  BOOL,				1 )
   _ev_end



/***********************<< ȫ�����������PT >>************************	
 *[��Ϣ��]
 *  + EmDirection  �ƶ�����  Up Down Left Right
 *  + EmAction     ����      emStrat  emStop
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPTCmd )
   _body(  EmDirection,     1 )
   _body(  EmCnAction ,     1 )
   _ev_end

/***********************<< ȫ��������Զ����� >>************************	
 *[��Ϣ��]
 *  
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamAutoFocusCmd )
   _ev_end

/***********************<< ȫ�������������� >>************************	
 *[��Ϣ��]
 *  + EmFocus  emFar Զ��  emNear ����
 *  + EmCnAction  ����Ϊ�ֶ�ʱ�Ĳ���
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamFocusCmd )
   _body(  EmFocus   ,         1 )
   _body(  EmCnAction,         1 )
   _ev_end

/***********************<< ȫ�������zoom���� >>************************	
 *[��Ϣ��]
 *  + EmZoom   emTele  ����   emWide ��Զ
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamZoomCmd )
   _body(  EmZoom  ,          1 )
   _ev_end

/***********************<< ȫ�����������Ԥ��λ >>************************	
 *[��Ϣ��]
 *  +  u8    Ԥ��λ����
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSavePresetCmd )
   _body(  u8  ,           1 )
   _ev_end

/***********************<< ȫ�����������Ԥ��λ���� >>************************	
 *[��Ϣ��]
 *  +  u8    Ԥ��λ����
 *  +  BOOL  ������ TRUE �ɹ�
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSavePresetInd )
   _body(  u8  ,           1 )
   _body(  BOOL,		   1 )
   _ev_end

/***********************<< ȫ�����������Ԥ��λ >>************************	
 *[��Ϣ��]
 *  +  u8    Ԥ��λ����
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetMoveCmd )
   _body(  u8  ,           1 )
   _ev_end

/***********************<< ȫ�����������Ԥ��λ���� >>************************	
 *[��Ϣ��]
 *  +  u8    Ԥ��λ����
 *  +  BOOL  ������ TRUE �ɹ�
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetMoveInd )
   _body(  u8  ,           1 )
   _body(  BOOL,		   1 )
   _ev_end

/***********************<< ȫ�������ɾ��Ԥ��λ >>************************	
 *[��Ϣ��]
 *  +  u8    Ԥ��λ����
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetDeleteCmd )
   _body(  u8  ,           1 )
   _ev_end

/***********************<< ȫ�������ɾ��Ԥ��λ���� >>************************	
 *[��Ϣ��]
 *  +  u8    Ԥ��λ����
 *  +  BOOL  ɾ�����
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetDeleteInd )
   _body(  u8		  ,		  1    )
   _body(  BOOL       ,		  1    )
   _ev_end


/***********************<< ȫ����������ȵ��� >>************************	
 *[��Ϣ��]
 *  + EmPanCamBright  up ��������  Down ���ȼ���
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamBackLightCmd )
   _body(  EmPanCamBright,         1 )
   _ev_end

/***********************<< ȫ���������Ϣ֪ͨ >>************************	
 *[��Ϣ��]
 *  +TCentrePanCamInfo   ȫ�������
 *  +u8                  ȫ���������ǰ����
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamCfgNty  )
   _body(  TPanCamInfo,       1 )
   _body(  u8		  ,       1 )
   _ev_end

/***********************<< ȫ��������������� >>************************	
 *[��Ϣ��]
 *  + u8   ȫ���������Ŀ
 *  
 *[��Ϣ����]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_SetPanCamNumCmd )
   _body(  u8    ,              1 )
   _ev_end

/***********************<< ȫ����������� >>************************	
 *[��Ϣ��]   
 * + u8    ȫ�����������
 * + BOOL  =TRUE ����ȫ������� 
 *  
 *[��Ϣ����]
 *   
 *       => Cndevice 
 */_event( ev_Cns_SetPanCamOpenCmd )
   _body(  BOOL  ,               1 )
   _body(  u8    ,				 1 )
   _ev_end

/***********************<< ά�����ߵ�½֪ͨ >>************************	
 *[��Ϣ��]
 *  
 *[��Ϣ����]
 *   
 *       => Cndevice 
 */_event( ev_cns_CnsToolsOnLineNty_Req )
   _ev_end

   /***********************<< TPad��½֪ͨ >>************************	
 *[��Ϣ��]
 *  
 *[��Ϣ����]
 *   
 *       => Cndevice 
 */_event( ev_cns_CnsTPadOnLineNty_Req )
   _ev_end

/***********************<< ȫ�������Ԥ��λ������ >>************************	
 *[��Ϣ��]
 *  + u8  Ԥ��λ����
 *  + TPanCamName  Ԥ��λ��
 *  
 *[��Ϣ����]
 *   
 *       => Cndevice 
 */_event( ev_Cns_SetPanCamNameCmd )
   _body(  u8         ,       1    )
   _body(  TPanCamName,       1    )
   _ev_end

/***********************<< ȫ�������Ԥ��λ������ >>************************	
 *[��Ϣ��]
 *  + u8  Ԥ��λ����
 *  + BOOL�������ý��
 *  + 
 *  
 *[��Ϣ����]
 *   
 *       => Cndevice 
 */_event( ev_Cns_SetPanCamNameInd )
   _body(  u8		  ,		  1    )
   _body(  BOOL       ,       1    )
   _ev_end

		
#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnspancamera )
};
#endif
#endif 
