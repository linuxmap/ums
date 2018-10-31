#ifndef _h_innereventumsmpu2_h__
#define _h_innereventumsmpu2_h__

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Eminnerumsmpu2
{
#endif

	_ev_segment( umsinnermpu2 )
	
	/***********************<<  Vmp消息-Begin >>*********************/
	_event(  ev_TPVmp_Begin )
	_ev_end

	_event(  ev_TPVmp_Reg_Req ) //brdApp -> EqpApp
	_body( TTPVmpReg, 1 )
	_ev_end
	
	_event(  ev_TPVmp_Reg_Ack ) //EqpApp -> brdApp
	_body( TTPVmpRegAck, 1 )
	_body( TUmsRSParam, 1)
	_ev_end
	
	_event(  ev_TPVmp_Reg_NAck ) //EqpApp -> brdApp
	_body( u16, 1 )
	_ev_end
	
	_event(  ev_TPVmp_State_Nty ) //brdApp -> EqpApp
	_body( TTPVmpStatNtfy, 1 )
	_ev_end
	
	_event(  ev_TPVmp_StartMix_Req ) //EqpApp -> brdApp
	_body( u8, 1 )//存储EqpID  用来在ack中识别是那个外设 
	_body( TTPVMPParam, 1 )
	_ev_end
	
	_event(  ev_TPVmp_StartMix_NAck ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_StartMix_Ack ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_StartMix_Ntfy ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_ChangeMixParam_Req ) //EqpApp -> brdApp
	_body( u8, 1 )//存储EqpID  用来在ack中识别是那个外设 
	_body( TTPVMPParam, 1 )
	_ev_end
	
	_event(  ev_TPVmp_ChangeMixParam_NAck ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_ChangeMixParam_Ack ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_ChangeMixParam_Ntfy ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_StopMix_Req ) //brdApp -> EqpApp
	_body( u8, 1 )//存储EqpID  用来在ack中识别是那个外设 
	_ev_end
	
	_event(  ev_TPVmp_StopMix_NAck ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_StopMix_Ack ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_StopMix_Ntfy ) //brdApp -> EqpApp
	_body( TTPVmpRetInfo, 1 )//EqpID
	_ev_end
	
	_event(  ev_TPVmp_FastUpdate_Req ) //brdApp -> EqpApp 或 EqpApp -> brdApp
	_body( TTPVmpAskFrame, 1 )
	_ev_end
	
	_event(  ev_TPVmp_StartStopChn_Req ) //EqpApp -> brdApp
	_body( u8, 1 )//EqpID
	_body( u8, 1 )//ChanIndx
	_body( u8, 1 )//0为停输出通道 1为开输出通道
	_ev_end


	_event(  ev_TPVmp_SetMediaKey_Req ) //EqpApp -> brdApp
	_body( u8, 1 )
	_body( TTPQTMediaKeyInfo, 1 )
	_ev_end

	_event(  ev_TPVmp_End )
	_ev_end
	/***********************<<  Vmp消息-End >>*********************/

	/***********************<<  Bas消息-Beg >>*********************/
	_event(  ev_TPBas_Begin )
	_ev_end

	_event(  ev_TPBas_Reg_Req ) //brdApp -> EqpApp
	_body( TTPBasReg, 1 )
	_ev_end

	_event(  ev_TPBas_Reg_NAck ) //EqpApp -> brdApp
	_body( u16, 1 )
	_ev_end

	_event(  ev_TPBas_Reg_Ack ) //EqpApp -> brdApp
	_body( u16, 1 )
	_ev_end

	_event(  ev_TPBas_State_Nty ) //brdApp -> EqpApp
	_body( TTPBasStatNtfy, 1 )
	_ev_end

	_event(  ev_TPBas_ChnState_Nty ) //brdApp -> EqpApp
	_body( TTPBasChnStatNtfy, 1 )
	_ev_end

	_event(  ev_TPBas_StartAdapter_Req ) //EqpApp -> brdApp
	_body(TStartBasAdapter, 1)
	_ev_end
	
	_event(  ev_TPBas_SetAdapterParam_Req ) //EqpApp -> brdApp
	_body(TStartBasAdapter, 1)
	_ev_end

	_event(  ev_TPBas_StopAdapter_Req )		//EqpApp -> brdApp
	_body( u8, 1 )
	_ev_end

	_event(  ev_TPBas_StartAdapter_Ack ) //brdApp -> EqpApp
	_body( TTPBasRetInfo, 1 )
	_ev_end

	_event(  ev_TPBas_StartAdapter_NAck ) //brdApp -> EqpApp
	_body( TTPBasRetInfo, 1 )
	_ev_end

	_event(  ev_TPBas_StopAdapter_Ack ) //brdApp -> EqpApp
	_body( TTPBasRetInfo, 1 )
	_ev_end

	_event(  ev_TPBas_StopAdapter_NAck ) //brdApp -> EqpApp
	_body( TTPBasRetInfo, 1 )
	_ev_end

	_event(  ev_TPBas_FastUpdate_Req ) //brdApp -> EqpApp 或 EqpApp -> brdApp
	_body( TTPBasAskFrame, 1 )
	_ev_end

	_event(  ev_TPBas_SetMediaKey_Req ) //EqpApp -> brdApp
	_body( u8, 1 )
	_body( u16, 1 )
	_body( TTPQTMediaKeyInfo, 1 )
	_ev_end

	_event(  ev_TPBas_End )
	_ev_end
	/***********************<<  Bas消息-End >>*********************/

	_event(  ev_TPEqp_ChangeSndAddr_Req )//所有外设板子通用
	_body( TBasMediaInfo, 1)//新的转发板ip
	_ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(umsinnermpu2)
};
#endif




#endif // _h_innereventumsmpu2_h__
