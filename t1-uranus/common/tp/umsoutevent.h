
//统一所有消息的定义

#if defined(_Check_Event_Range_) || defined(_MakeTpEventDescription_)

//ums

	#include "eventoutumsreg.h"
	#undef _h_eventoutumsreg_h__

	#include "eventoutumsconftemplate.h"
	#undef _h_eventoutumsconftemplate_h__

	#include "eventoutumscall.h"
	#undef _h_eventoutumscall_h__

	#include "eventoutumslogin.h"
	#undef _h_eventoutumslogin_h__

	#include "eventoutumscfg.h"
	#undef _h_eventoutumscfg_h__

	#include "eventoutumshdu.h"
	#undef _eventoutumshdu_h_

	#include "eventoutumseqp.h"
	#undef _h_eventoutumseqp_h__
	
	#include "eventoutumstool.h"
	#undef _h_eventoutumstool_h__

	#include "eventoutumsboard.h"
	#undef _h_eventoutumsboard_h__

	#include "eventoutumsrec.h"
	#undef __h_eventoutumsrec_h_
	
	#include "eventoutmpu2tp.h"
	#undef _h_eventoutmpu2tp_h_

	#include "eventoutumsselview.h"
	#undef _h_eventoutumsselview_h_

	#include "eventoutumsbrdvmp.h"
	#undef _h_eventoutumsbrdvmp_h_

    #include "eventoutquantum.h"
    #undef _h_eventoutquantum_h__
	
    #include "eventoutcfgex.h"
	#undef _h_eventoutcfgex_h__

    #include "eventoutumsmcucasecade.h"
	#undef _h_eventoutumsmcucasecade_h__

//umssipadapte
	#include "eventoutsipadapter.h"
	#undef _h_eventoutsipadapter_h__
//umsaudiomix
	#include "eventoutumsaudiomix.h"
	#undef _h_eventoutumsaudiomix_h__

	#include "eventoutumsmediatrans.h"
	#undef _h_eventoutumsmediatrans_h__	

//umshdu2
	#include "eventoutumshdu2.h"
	#undef _eventoutumshdu2_h__	

//commonbrd	
	#include "eventoutumscommonbrd.h"
	#undef _h_eventoutumscommonbrd_h__	

//通用服务器类消息 暂且用 umsmsg， 故放在这里
	#include "eventoutupdateservice.h"
	#undef _h_eventoutupdateservice_h__	

	#undef _ev_segment
	#undef _event
	#undef _body
	#undef _blob
	#undef _ev_end
	#undef _ev_segment_end

#undef _Check_Event_Range_
#undef _MakeTpEventDescription_

#endif

#ifndef _h_tpeventmsgr_h__
#define _h_tpeventmsgr_h__


#endif // _h_tpeventmsgr_h__


//END OF FILE

