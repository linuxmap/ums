#ifndef _eventoutumshdu2_h__
#define _eventoutumshdu2_h__
#include "umseventcomm.h"

#ifndef _MakeTpEventDescription_
enum Emouterumshdu2
{
#endif
	
	_ev_segment( tpumswithumshdu2 )
	
	/***********************<<����ǽ��Ϣ>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_hduInfo_Nty )
	_body(THduCfg, 1)	
_ev_end

	/***********************<<��������ǽ����>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_hduUpdate_req )
	_body(TTPBrdUpGrade, 1)	
_ev_end

	/***********************<<��������ǽ������>>********************	
 *[��Ϣ����]	ums	-->  tool
 *
 */
_event(  ev_hduUpdate_rsp )
	_body(TTPBrdUpGrade, 1)	
	_body(EmUpdateHduRet, 1)
_ev_end

/***********************<<��ӵ���ǽ����>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduBrdAdd_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<��ӵ���ǽ����>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduBrdAdd_rsp )
	_body(EmModifyHduRet, 1)
	_body(TTPBrdPos, 1)	
_ev_end


/***********************<<�޸ĵ���ǽ����>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduBrdModify_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<�޸ĵ���ǽ����Ӧ��>>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduBrdModify_rsp )
	_body(EmModifyHduRet, 1)	//ԭ�� 
	_body(TTPBrdPos, 1)			//�޸���Ϣ
_ev_end

/***********************<<���ͨ��>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduChanAdd_req )
	_body(THduInfo, 1)	
_ev_end


/***********************<<���ͨ������Ӧ��>>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduChanAdd_rsp )
	_body(EmModifyHduRet, 1)	//ԭ�� 
	_body(THduInfo, 1)	
_ev_end

/***********************<<�޸�ͨ������>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduChanModify_req )
	_body(THduInfo, 1)	
_ev_end

/***********************<<�޸�ͨ������Ӧ��>>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduChanModify_rsp )
	_body(EmModifyHduRet, 1)	//ԭ�� 
	_body(THduInfo, 1)	
_ev_end

/***********************<<ɾ������ǽͨ������>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduChanDel_req )
	_body(TTPBrdPos, 1)	
_ev_end


/***********************<<ɾ������ǽͨ������>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduChanDel_rsp )
	_body(EmModifyHduRet, 1)	//ԭ�� 
	_body(TTPBrdPos, 1)	
_ev_end


/***********************<<ɾ������ǽ>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduDel_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<ɾ������ǽ����Ӧ��>>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduDel_rsp )
	_body(EmModifyHduRet, 1)	//�������
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<��������ǽ>>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduReboot_req )
	_body(TTPBrdPos, 1)	
_ev_end

/***********************<<��������ǽӦ��>>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduReboot_rsp )
	_body(EmModifyHduRet, 1)
	_body(TTPBrdPos, 1)	
_ev_end



/*				����ǽ�����Ϣ                               */
/***********************<<֪ͨ����ǽ���>>********************	
 *[��Ϣ����]	ums -->  tool/
 *
 */
_event(  ev_hduStyle_Nty )
	_body(THduStyleData,	1)
_ev_end

/***********************<<֪ͨ����ǽ���>>********************	
 *[��Ϣ����]	ums -->  umc   ����Ϣֱ����OSP���ͣ�������XML�����
 *
 */
_event(  ev_hduPlan_Nty )
	_body(THduPlanData,	1)
_ev_end

/***********************<< ��ӵ���ǽ��� >>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduStyle_Add )
	_body(THduStyleData,	1)
_ev_end

/***********************<< ��ӵ���ǽ���Ӧ�� >>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduStyle_Add_Rsp )
	_body(EmModifyHduRet, 1)	//�������
	_body(THduStyleData, 1)
_ev_end

/***********************<< ɾ������ǽԤ������ >>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduStyle_Del_Req )
_ev_end

/***********************<< ɾ������ǽԤ��Ӧ�� >>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduStyle_Del_Rsp )
	_body(EmModifyHduRet, 1)	//ɾ�����
_ev_end

/***********************<< ���µ���ǽԤ�� >>********************	
 *[��Ϣ����]	tool -->  ums
 *
 */
_event(  ev_hduStyle_update_Req )
	_body(THduStyleData, 1)	
_ev_end

/***********************<< ���µ���ǽԤ�� >>********************	
 *[��Ϣ����]	ums -->  tool
 *
 */
_event(  ev_hduStyle_update_Rsp )
	_body(EmModifyHduRet, 1)
	_body(THduStyleData, 1)
_ev_end

/*				����ǽͬUMC ������Ϣ                       */
/***********************<<  ���󲥷�  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	umc	--> ums
 *
 */
 _event(  ev_HduPlay_Req )
	_body( TTPHduPlayReq,		1)	//��Ϣ
_ev_end

/***********************<<  ���󲥷Ż�Ӧ  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums	--> umc
 *
 */
 _event(  ev_HduPlay_Ack )
	_body(u16,		1)
	_body(u8,		1) // ������
 _ev_end

/***********************<<  ���󲥷Ż�Ӧ  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums	--> umc
 *
 */
 _event(  ev_HduPlay_NAck )
	_body( u16,		1)
	_body( EmTpHduPlayNackReason,     1)
	_body(u8,		1) // ������
_ev_end

/************************<<֪ͨ����᳡�Ƿ�������>>*************************
*[��Ϣ��]			 
*   NULL
*[��Ϣ����]	ums  -->  umc	
*
*/_event(  ev_HduCall_Valid )
		_body( TTPHduPlayReq,      1)
		_body( BOOL32,				  1)
  _ev_end

/***********************<<  ֹͣ����  >>********************	
 *[��Ϣ��]			 ɾ������ǽ�ļ��
 *   NULL
 *[��Ϣ����]	umc	--> ums
 *
 */	_event(  ev_HduAllStopPlay_Req )
	_ev_end

/***********************<<  ֹͣ����  >>********************	
 *[��Ϣ��]			 ɾ������ǽ�ļ��
 *   NULL
 *[��Ϣ����]	umc	--> ums
 *
 */_event(  ev_HduStopPlay_Req )
	_body( TTPHduPlayReq,		1)	//��Ϣ
	_ev_end

/***********************<<  ֹͣ����Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */_event(  ev_HduStopPlay_Ack )
	_body(TPHduBaseInfo,		1)
	_ev_end

/***********************<<  ֹͣ����Ӧ��  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_HduStopPlay_NAck )
	_body(TPHduBaseInfo,		1)
_ev_end

/***********************<<  HDUע��״̬  >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	ums  -->  umc	
 *
 */
 _event(  ev_HduReg_Status_Nty )
	_body( u16, 1) //����
	_body( BOOL32, 1)	//�Ƿ�������
_ev_end

_event( ev_Hdu_SetVol)
	_body(THduSetVolInfo, 1)
_ev_end

_event( ev_Hdu_SetVol_Res)
	_body(THduSetVolInfo, 1)
	_body(EmTpHduSetVolRes, 1)
_ev_end	

_event( ev_Hdu_ChangeChanMode_Req)
	_body(THduChanModeSetInfo, 1)
_ev_end	

_event( ev_Hdu_ChangeChanMode_Rsp)
    _body(THduChanModeSetInfo, 1)
	_body(EmTpHduChangeChanModeRes, 1)
_ev_end	
		
#ifndef _MakeTpEventDescription_
	_ev_segment_end(tpumswithumshdu2)
};
#endif


#endif