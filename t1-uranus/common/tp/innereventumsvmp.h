#ifndef __inner_event_umsvmp_h_
#define __inner_event_umsvmp_h_

#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmumsinnerVmp
{
#endif
	_ev_segment( umsinnervmp )

	_event ( ev_vmp_Start_Req )
		_body( TVmpStartInfo, 1)
	_ev_end

	_event ( ev_vmp_Start_Res )
		_body( TVmpStartResult, 1)
	_ev_end

	_event ( ev_vmp_Stop_Req )
		_body( TServiceBaseInfo, 1)
	_ev_end

	_event ( ev_vmp_Stop_Res )
		_body( TVmpStartResult, 1)
	_ev_end

	_event ( ev_vmp_Mdy_Style_Req )
		_body( TVmpMdyInfo, 1)
	_ev_end

	_event ( ev_vmp_Mdy_Style_Res )
		_body( TVmpMdyResult, 1)
	_ev_end

	_event(  ev_save_vmpcfg_req  )
	_body ( TSaveVmpPlanInfo  , 1  )
	_ev_end

	_event(  ev_vmp_Assgin_Req  )
	_body ( TServiceBaseInfo  , 1  )
	_ev_end

	_event ( ev_vmp_Assgin_Res )
	_body( TVmpStartResult, 1)
	_ev_end

	_event ( ev_vmp_UpdateSpeakerSide_Req )
	_body( TVmpSpeakerFlag, 1)
	_ev_end


	_event ( ev_vmp_SetMediaKey_Req )
	_body( u16, 1)
	_body( TTPQTMediaKeyInfo, 1)
	_ev_end

	//更改合成器IP
	_event(ev_vmp_ChangeDsIP_Req)
	_body(TSndDsAddr, 1)
	_ev_end

#ifndef _MakeTpEventDescription_
	_ev_segment_end(umsinnervmp)
};
#endif

#endif