#ifndef _h_innereventregsrv_h__
#define _h_innereventregsrv_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsInnerToCns
{
#endif

	_ev_segment( innerregsrv )

/***********************<<  ����ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_reg_req )
	_body ( TUmsHandle  , 1  )
	_body ( TCnsRegInfo  , 1  )
   _ev_end


 /***********************<<  ����ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_update_reg )
	_body ( EmRegGroupNum  , 1  )
   _ev_end

 /***********************<<  adapter���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_adapter_regout )
 _body(BOOL32, 1) // ����or����
   _ev_end


   /***********************<<  ����ɾ��ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_unreg_req )
	_body ( TUmsHandle  , 1  )
	_body ( TCnsRegInfo  , 1  )
   _ev_end


   
   /***********************<<  �˵��ѯ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_arq_req )
	_body ( TUmsHandle  , 1  )
	_body ( TTPAlias  , 1  )
   _ev_end

   /***********************<<  �˵��ѯ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_arq_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TRegResult  , 1  )
	_body ( TCnsRegInfo  , 1  )
   _ev_end

/***********************<<	������������ע����Ϣ >>********************    
*[��Ϣ��]			
*	NULL
*[��Ϣ����] 	   --> RegServer
*
*/_event(  evtp_ums_RegSer_Req_RegInfo )
  _ev_end

/***********************<<	������������ע����Ϣ >>********************    
*[��Ϣ��]			
*	NULL
*[��Ϣ����] 	   --> RegServer UpGradeTool
*
*/_event(  evtp_ums_RegSer_Rsp_RegInfo )
   _body ( TRegInfoArray  , 1)
  _ev_end


/***********************<<  ����ȫ�ֵ�ַ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  evtp_ums_reg_info_req)
	_body ( TUmsHandle  , 1  )
	_body ( s32  ,	1  )
	_body ( EmGetRegInfoType, 1)
   _ev_end

     /***********************<<	 ��ȡȫ����CNS��ȫ��ע����Ϣ�ظ� >>********************    
  *[��Ϣ��]			
  *	NULL
  *[��Ϣ����] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GetRegInfo_Rsp )
	_body ( TTPSipRegPackInfo, 1 )
    _body ( EmGetRegInfoType, 1 )
	_body ( TTPSipRegInfo, 1 )
  _ev_end


 /***********************<<	GK ע����Ϣ >>********************    
  *[��Ϣ��]			
  *	NULL
  *[��Ϣ����] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GkRegInfo_MtRsp )
	  _body ( EmGetRegInfoType, 1)
	  _body ( TTPMtRegInfo, 1)
  _ev_end

   /***********************<<	GK ע����Ϣ >>********************    
  *[��Ϣ��]			
  *	NULL
  *[��Ϣ����] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GkRegInfo_McuRsp )
	  _body ( EmGetRegInfoType, 1)
	  _body ( TTPMcuRegInfo, 1)
  _ev_end

 /***********************<<	ȫ�ֵ�ַ��UMSע����Ϣ >>********************    
  *[��Ϣ��]			
  *	NULL
  *[��Ϣ����] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GetRegInfo_UmsRspEx )
		_body ( TRegPackInfoEx, 1)
		_body ( TUmsRegPackEx, 1)
  _ev_end

   /***********************<<	ȫ�ֵ�ַ��CNSע����Ϣ >>********************    
  *[��Ϣ��]			
  *	NULL
  *[��Ϣ����] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GetRegInfo_CnsRspEx )
		_body ( TRegPackInfoEx, 1)
		_body ( TCnsRegPackEx, 1)
  _ev_end

 /***********************<<	��ȡȫ����UMS��CNS��ȫ��ע����Ϣ >>********************    
  *[��Ϣ��]			
  *	NULL
  *[��Ϣ����] 	   --> cnc -> cns -> ums
  *
  */_event(  ev_ums_GetRegInfo_Req )
  _body ( EmGetRegInfoType, 1 )
  _ev_end

/***********************<<  ȫ�ֵ�ַ����ӦB1  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  evtp_ums_reg_info_rsp )
	_body ( TUmsHandle  , 1  )
	_body ( s32  ,	1  )
	_body ( TReqRegInfo, 1)
   _ev_end

 /***********************<<  ȫ�ֵ�ַ����ӦB2  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]
 *
 */_event(  evtp_ums_reg_info_rspEx )
	_body ( TUmsHandle  , 1  )
	_body ( s32  ,	1  )
	_body ( TReqRegInfoEx, 1)
   _ev_end


/***********************<<  rrq��ʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  evtp_RRQ_Timer )
  _ev_end

  /***********************<<  gkrrq��ʱ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		
 *
 */_event(  evtp_GK_RRQ_Timer )
  _ev_end



      /***********************<<   >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> 
 *
 */_event(  EVTPUMS_CNS_SHOW_ALLCONF )
   _ev_end	

//add
  /***********************<<  sipcfg update >>********************				 
 *[��Ϣ����]		
 *
 */_event(  evtp_Sip_Cfg_Update )
   _body(TTPSipRegistrarCfg, 1)
  _ev_end	


  /***********************<<  gkcfg update >>********************	
 *[��Ϣ����]		
 *
 */_event(  evtp_GK_Cfg_Update )
   _body(TTPGKCfg, 1)
  _ev_end	
//end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innerregsrv)
};
#endif



#endif // _h_innereventregsrv_h__
