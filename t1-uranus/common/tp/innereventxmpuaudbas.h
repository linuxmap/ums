#ifndef _h_innereventxmpuaudbas_h__
#define _h_innereventxmpuaudbas_h__

#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Eminnereventxmpuaudbas
{
#endif

	_ev_segment( innereventxmpuaudbas )


   /***********************<<  xmpu start audbas rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartAudBasRsp
 *[��Ϣ����]	MediaSource - XmpuEqp
 *
 */
 _event(  evXmpu_StartAudBas_Rsp )
 _body( TXmpuStartAudBasRsp, 1 )
 _ev_end

  /***********************<<  xmpu start aud bas Nty  >>********************	
 *[��Ϣ��]			 
 *   TXmpuStartAudBasNty
 *[��Ϣ����]	XmpuEQP - Call
 *
 */
 _event(  evXmpu_UmsStartAudBas_Nty )
 _body( TXmpuStartAudBasNty, 1 )
 _ev_end

    /***********************<<  xmpu set audbas req  >>********************	
 *[��Ϣ��]			 
 *   TXmpuAudBasParam
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_SetAudBasParam_Req )
 _body( TXmpuChgAudParam, 1 )
 _ev_end

    /***********************<<  xmpu set audbas rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuSetAudBasRsp
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_SetAudBasParam_Rsp )
 _body( TXmpuSetAudBasRsp, 1 )
 _ev_end

    /***********************<<  xmpu set audbas Nty  >>********************	
 *[��Ϣ��]			 
 *   BOOL32
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_SetAudBasParam_Nty )
 _body( BOOL32, 1 )
 _ev_end

   /***********************<<  xmpu start audbas rsp  >>********************	
 *[��Ϣ��]			 
 *   TXmpuSetAudSynInfo
 *[��Ϣ����]	Call - XmpuEqp
 *
 */
 _event(  evXmpu_AudBasSetSyn_Req )
 _body( TXmpuAudBasSynInfo, 1 )
 _ev_end

  /***********************<<  xmpu audbas disConnect rsp  >>********************	
 *[��Ϣ��]			 
 *   u32
 *[��Ϣ����]	MCUEQP - EQP
 *
 */
 _event(  evXmpu_AudBasDisConnect_Nty )
 _body( u32, 1 )
 _ev_end

 

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innereventxmpuaudbas)
};
#endif


#endif // _h_innereventumsaudiomix_h__
