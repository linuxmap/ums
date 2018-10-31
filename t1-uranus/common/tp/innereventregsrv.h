#ifndef _h_innereventregsrv_h__
#define _h_innereventregsrv_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsInnerToCns
{
#endif

	_ev_segment( innerregsrv )

/***********************<<  请求注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_reg_req )
	_body ( TUmsHandle  , 1  )
	_body ( TCnsRegInfo  , 1  )
   _ev_end


 /***********************<<  更新注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_update_reg )
	_body ( EmRegGroupNum  , 1  )
   _ev_end

 /***********************<<  adapter掉线 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_adapter_regout )
 _body(BOOL32, 1) // 上线or掉线
   _ev_end


   /***********************<<  请求删除注册 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_unreg_req )
	_body ( TUmsHandle  , 1  )
	_body ( TCnsRegInfo  , 1  )
   _ev_end


   
   /***********************<<  端点查询 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_arq_req )
	_body ( TUmsHandle  , 1  )
	_body ( TTPAlias  , 1  )
   _ev_end

   /***********************<<  端点查询 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> UMS
 *
 */_event(  evtp_ums_arq_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TRegResult  , 1  )
	_body ( TCnsRegInfo  , 1  )
   _ev_end

/***********************<<	升级工具请求注册信息 >>********************    
*[消息体]			
*	NULL
*[消息方向] 	   --> RegServer
*
*/_event(  evtp_ums_RegSer_Req_RegInfo )
  _ev_end

/***********************<<	返回升级工具注册信息 >>********************    
*[消息体]			
*	NULL
*[消息方向] 	   --> RegServer UpGradeTool
*
*/_event(  evtp_ums_RegSer_Rsp_RegInfo )
   _body ( TRegInfoArray  , 1)
  _ev_end


/***********************<<  请求全局地址薄 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]
 *
 */_event(  evtp_ums_reg_info_req)
	_body ( TUmsHandle  , 1  )
	_body ( s32  ,	1  )
	_body ( EmGetRegInfoType, 1)
   _ev_end

     /***********************<<	 获取全域内CNS的全部注册信息回复 >>********************    
  *[消息体]			
  *	NULL
  *[消息方向] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GetRegInfo_Rsp )
	_body ( TTPSipRegPackInfo, 1 )
    _body ( EmGetRegInfoType, 1 )
	_body ( TTPSipRegInfo, 1 )
  _ev_end


 /***********************<<	GK 注册信息 >>********************    
  *[消息体]			
  *	NULL
  *[消息方向] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GkRegInfo_MtRsp )
	  _body ( EmGetRegInfoType, 1)
	  _body ( TTPMtRegInfo, 1)
  _ev_end

   /***********************<<	GK 注册信息 >>********************    
  *[消息体]			
  *	NULL
  *[消息方向] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GkRegInfo_McuRsp )
	  _body ( EmGetRegInfoType, 1)
	  _body ( TTPMcuRegInfo, 1)
  _ev_end

 /***********************<<	全局地址薄UMS注册信息 >>********************    
  *[消息体]			
  *	NULL
  *[消息方向] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GetRegInfo_UmsRspEx )
		_body ( TRegPackInfoEx, 1)
		_body ( TUmsRegPackEx, 1)
  _ev_end

   /***********************<<	全局地址薄CNS注册信息 >>********************    
  *[消息体]			
  *	NULL
  *[消息方向] 	   --> cnc <- cns <- ums
  *
  */_event(  ev_ums_GetRegInfo_CnsRspEx )
		_body ( TRegPackInfoEx, 1)
		_body ( TCnsRegPackEx, 1)
  _ev_end

 /***********************<<	获取全域内UMS和CNS的全部注册信息 >>********************    
  *[消息体]			
  *	NULL
  *[消息方向] 	   --> cnc -> cns -> ums
  *
  */_event(  ev_ums_GetRegInfo_Req )
  _body ( EmGetRegInfoType, 1 )
  _ev_end

/***********************<<  全局地址薄回应B1  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]
 *
 */_event(  evtp_ums_reg_info_rsp )
	_body ( TUmsHandle  , 1  )
	_body ( s32  ,	1  )
	_body ( TReqRegInfo, 1)
   _ev_end

 /***********************<<  全局地址薄回应B2  >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]
 *
 */_event(  evtp_ums_reg_info_rspEx )
	_body ( TUmsHandle  , 1  )
	_body ( s32  ,	1  )
	_body ( TReqRegInfoEx, 1)
   _ev_end


/***********************<<  rrq定时器 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  evtp_RRQ_Timer )
  _ev_end

  /***********************<<  gkrrq定时器 >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		
 *
 */_event(  evtp_GK_RRQ_Timer )
  _ev_end



      /***********************<<   >>********************	
 *[消息体]			 
 *   NULL
 *[消息方向]		--> 
 *
 */_event(  EVTPUMS_CNS_SHOW_ALLCONF )
   _ev_end	

//add
  /***********************<<  sipcfg update >>********************				 
 *[消息方向]		
 *
 */_event(  evtp_Sip_Cfg_Update )
   _body(TTPSipRegistrarCfg, 1)
  _ev_end	


  /***********************<<  gkcfg update >>********************	
 *[消息方向]		
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
