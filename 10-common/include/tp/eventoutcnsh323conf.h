#ifndef _h_eventoutcnsh323conf_h__
#define _h_eventoutcnsh323conf_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSH323CONFEVENT
{
#endif 

  _ev_segment( outercnsh323conf  )


/***********************<< ��ʼ������ָʾ >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleMultipleConference )
_ev_end
	  
/***********************<< ȡ��������ָʾ >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelMultipleConference )
_ev_end

/***********************<< �����ն˱�� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalNumberAssign )
_body(TTPTerLabel, 1)
_ev_end

/***********************<< �����˿��������� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleSeenByAll )
_ev_end

/***********************<< ȡ�������˿� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelSeenByAll )
_ev_end

/***********************<< �����б� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalListRequest )

_ev_end

/***********************<< �����б� >>********************** 
*[��Ϣ��]

*[��Ϣ����]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalIDListRequest )

_ev_end



/***********************<< ������� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalJoinConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< �뿪���� >>********************** 
*[��Ϣ��]
TTPMDLTERLABEL
*[��Ϣ����]
*  cns	  <- cncall
*/
_event(  ev_CnModuleterminalLeftConf )
_body( TCnsInfo, 1 )
_ev_end

  
#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsh323conf )
};
#endif
#endif //TPP_EVENT_H
