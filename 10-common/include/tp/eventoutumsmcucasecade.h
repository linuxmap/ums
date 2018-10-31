#ifndef _h_eventoutumsmcucasecade_h__
#define _h_eventoutumsmcucasecade_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpoutumsmcucasecade
{
#endif
	
	_ev_segment( outumsmcucasecade )

/*[消息方向]	MCU	-->  UMS
*
 */
 _event(  evtp_MCU_UMS_Casecade_Event_Begin ) 
_ev_end

_event(  evtp_MCU_UMS_CasecadeChanConnected ) //MCU级联通道建立通知消息
_body (TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_ev_end

_event(  evtp_MCU_UMS_RegUnRegReq ) 
_body (TUmsHandle, 1) 
_body ( TUmsMcuRegUnReg  , 1  )
_ev_end

_event(  evtp_MCU_UMS_RegUnRegRsp ) 
_body (TUmsHandle, 1) 
_body ( TUmsMcuRegUnReg  , 1  )
_ev_end

_event(  evtp_MCU_UMS_RosterNotify ) 
_body (TUmsHandle, 1) 
_body ( TUmsMcuRosterList  , 1  )
_ev_end

_event(  evtp_MCU_UMS_PartListRsp ) 
_body ( TUmsHandle, 1) 
_body ( TUmsMcuPartList  , 1  )
_body ( TUmcMcuPart  , 4  )
_ev_end

_event(  evtp_MCU_UMS_PartStateNty ) 
_body ( TUmsHandle, 1) 
_body ( TUmcMcuPart  , 1  )
_ev_end

_event(  evtp_MCU_UMS_DelPartNty ) 
_body ( TUmsHandle, 1) 
_body ( u32  , 1  )
_ev_end

_event(  evtp_MCU_UMS_SpyBWNty ) 
_body ( TUmsHandle, 1) 
_body ( u32  , 1  )
_ev_end


/*[消息方向]	UMS	-->  MCU
*
 */
 _event(  evtp_UMS_MCU_Casecade_Event_Begin ) 
_ev_end

 _event(  evtp_UMS_MCU_RegUnRegReq ) 
 _body (TUmsHandle, 1) 
 _body ( TUmsMcuChan  , 1  )
 _body ( TUmsMcuRegUnReg  , 1  )
_ev_end

_event(  evtp_UMS_MCU_RegUnRegRsp ) 
_body (TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_body ( TUmsMcuRegUnReg  , 1  )
_ev_end

_event(  evtp_UMS_MCU_PartListReq ) 
_body (TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_body ( s32  , 1  ) //reqid
_ev_end

_event(  evtp_UMS_MCU_CallDropPartReq ) 
_body ( TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_body ( TMcuEpCmd  , 1  ) // MtId bCall
_ev_end

_event(  evtp_UMS_MCU_SpeakerStatusNty ) 
_body ( TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_body ( TMcuSpeakerStausNty  , 1  ) // MtId status
_ev_end

_event(  evtp_UMS_MCU_SetInReq ) 
_body ( TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_body ( u32  , 1  ) // MtId
_ev_end

_event(  evtp_UMS_MCU_SpeakedChangeNty ) 
_body ( TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_body ( u32  , 1  ) // MtId
_ev_end

_event(  evtp_UMS_MCU_MultSpyReq ) 
_body ( TUmsHandle, 1) 
_body ( TUmsMcuChan  , 1  )
_body ( TMcuSpyReq  , 1  ) // MtId
_ev_end

_event(  evtp_UMS_MCU_Casecade_Event_End ) 
_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(outumsmcucasecade)
};
#endif


#endif // _h_eventoutumsmcucasecade_h__