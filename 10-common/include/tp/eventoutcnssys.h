#ifndef _h_eventoutcnssys_h__
#define _h_eventoutcnssys_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSYSEVENT
{
#endif 

  _ev_segment( outercnssys  )
/***********************<< CNSЭ��ջ��ʼ�����֪ͨ >>********************** 
*[��Ϣ��]
* BOOL ��ʼ���Ƿ�ɹ�
*[��Ϣ����]
*  cncall	  -> cns
*/
	  _event(  ev_tppCnProtocalInit_Nty )
	  _body( BOOL, 1 )
_ev_end

/***********************<< ֪ͨ�᳡���� >>********************** 
*[��Ϣ��]
+s8[]		�᳡��
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_tpRoomOnline_Nty )
_body( s8, TP_MAX_NAME_LEN+1)
_ev_end

/***********************<< ֪ͨ�᳡���� >>********************** 
*[��Ϣ��]
+s8[]		�᳡��
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_tpRoomOffline_Nty )
_body( s8, TP_MAX_NAME_LEN+1)
_ev_end

/***********************<< ����cnsʱ�� >>********************** 
*[��Ϣ��]
+TTPTime		
*[��Ϣ����]
*  cns	  <- cnc
*/
_event( ev_CnSetSysTime_Cmd )
_body( TTPTime, 1 )
_ev_end

/***********************<< ��ѯcnsʱ�� >>********************** 
*[��Ϣ��]
*NULL
*[��Ϣ����]
*  cns	  <- cnc
*/
_event( ev_CnGetSysTime_Req)
_ev_end


/***********************<< ��ѯcnsʱ����Ӧ >>********************** 
*[��Ϣ��]
+TTPTime
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_CnGetSysTime_Rsp)
_body( TTPTime, 1 )
_ev_end



//============tp_sp1 ��Ϣ����

//��¼
/***********************<< ֪ͨcn�б� >>********************** 
*[��Ϣ��]
+TTPCnList
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_CnList_Nty)
_body( TTPCnList, 1 )
_ev_end

 /***********************<< ��¼���� >>********************** 
 *[��Ϣ��]
 *[��Ϣ����]
 ע userdata�а���insid
 *  cnc	  -> cns
*/
_event(  ev_CnLoginIns_Req )
_ev_end

 /***********************<< ��¼�����Ӧ >>********************** 
 *[��Ϣ��]
+TLoginRet  ��¼��Ϣ
 ע userdata�а���insid
 *[��Ϣ����]
 *  cnc	 <- cns,  tool <- cns
*/
_event(  ev_CnLoginIns_Rsp )
_body(TLoginRet,	1)
_ev_end

 /***********************<< ������ʱ��ʱ�� >>********************** 
 *[��Ϣ��]
 *NULL
 *[��Ϣ����]
 *  cns	 <- cns
*/
//
_event(  ev_CnRebootDelay_Timer )
_ev_end

 //��¼
 /***********************<< ��¼���� >>********************** 
 *[��Ϣ��]
 *NULL
 *[��Ϣ����]
 *  cnc	  -> cns, tool -> cns 
*/
_event(  ev_CnLogin_Req )
//_body( CLoginRequest, 1 )
_ev_end

 /***********************<< ��¼�����Ӧ >>********************** 
 *[��Ϣ��]
+TLoginRet  ��¼��Ϣ
 *[��Ϣ����]
 *  cnc	  <- cns�� cns -> tool
*/
_event(  ev_CnLogin_Rsp )
_body(TLoginRet,	1)
_ev_end

 /***********************<< ���û᳡��Ϣ���� >>********************** 
 *[��Ϣ��]
+TTPCnsInfo  �᳡��Ϣ
+u8   0 : CNC��Ϣ��1: ά��������Ϣ
 *[��Ϣ����]
 *  cnc	  ->  cns
*/
_event(  ev_CnCfgCnsInfo_Cmd )
_body( TTPCnsInfo,	1 )
_body( u8,	1 )
_ev_end
//����
/***********************<< ֪ͨ�᳡��Ϣ >>********************** 
*[��Ϣ��]
+TTPCnsInfo		CNS��Ϣ
+EmTPCNSInfoRst ���û᳡��Ϣ���
*[��Ϣ����]
*  cns	  -> cnc , cns -> tool
*/
_event(  ev_CnCfgCnsInfo_Ind )
_body( TTPCnsInfo,	1 )
_body( EmTPCNSInfoRst,	1 )
_ev_end


/***********************<< ����������Ϣ >>********************** 
*[��Ϣ��]
+TTPEthnetInfo		CNS����������Ϣ
*[��Ϣ����]
*  cnc	  -> cns
*/
_event( ev_CnCfgEthnet_Cmd )
_body(TTPEthnetInfo, 1 )
_ev_end

/***********************<< ֪ͨ�����Ӧ >>********************** 
*[��Ϣ��]
+TTPEthnetInfo		CNS����������Ϣ
*[��Ϣ����]
*  cns	  -> cnc
*/
_event(  ev_CnCfgEthnet_Ind )
_body(TTPEthnetInfo, 1 )
_ev_end
 
//֪ͨcnc

/***********************<< �޸����᳡������ >>********************** 
*[��Ϣ��]
+s8		�᳡��
*[��Ϣ����]
*  cns	  <- cnc
*/
_event( ev_CnSetMainRoom_Cmd )
_body( s8, TP_MAX_NAME_LEN+1 )
_ev_end

/***********************<< �޸����᳡����Ӧ >>********************** 
*[��Ϣ��]
+s8		�᳡��
*[��Ϣ����]
*  cns	  ->  cnc
*/
_event( ev_CnSetMainRoom_Ind )
_body( s8, TP_MAX_NAME_LEN+1 )
_ev_end
 

/***********************<< ֪ͨ�޸Ļ᳡�� >>********************** 
*[��Ϣ��]
+s8 �᳡��
*[��Ϣ����]
*  cnc	  -> cns
*/
_event(  ev_CnSetRoomName_Cmd )
_body( s8, TP_MAX_ALIAS_LEN + 1 )
_ev_end

/***********************<< ֪ͨ�޸Ļ᳡����� >>********************** 
*[��Ϣ��]
+s8 �᳡��
*[��Ϣ����]
*  cns	  -> cnc
*/
_event(  ev_CnSetRoomName_Ind )
_body( s8, 1 )
_ev_end

/***********************<< ˫������֪ͨ >>********************** 
*[��Ϣ��]
+NULL
*[��Ϣ����]
*  cns	  -> cnc
*/
_event(  ev_tpCnRoomDualOffline_Nty )
_ev_end

/***********************<< ��̬NAT��Ӧ >>********************** 
*[��Ϣ��]
*TTPNatCfg ��̬Nat����
*[��Ϣ����]
*  cns	  -> cnc
*/
_event( ev_tppNatReg_Nty )
_body(TTPNatCfg, 1)
_ev_end

/***********************<< ����Nat >>********************** 
*[��Ϣ��]
*TTPNatCfg ��̬Nat����
*[��Ϣ����]
*  cnc	  -> cns
*/
_event( ev_tppNatReg_Cmd )
_body(TTPNatCfg, 1)
_ev_end

 /***********************<<ϵͳ�������� >>************************	
 *[����Ϣ��]			 
 *  TTPVerFileInfo cns�����ļ���Ϣ
 *[��Ϣ����]
 *    cns <= AGENT��cnc -> cns,  cns -> cns
 */
 _event(  ev_CnUpdateSystem_Cmd  )
 _body ( TTPFTPFileInfo, 1 )
 _ev_end

/***********************<<Tpad�������� >>********************** 
*[��Ϣ��]
*EmTPUpdateType    TPad������ʽ
*TTPTPadVerInfo    TPad�İ汾��Ϣ
*[��Ϣ����]
*   cns -> cnc
*/
  _event( ev_TpadUpdateSystem_Cmd )
  _body(TTPTPadVerInfo ,1)
  _ev_end

/***********************<<Cns֪ͨ����cns���������� >>********************** 
*[��Ϣ��]
*EmTPUpdateType  CNS����������
*[��Ϣ����]
*   cns -> cnc
*/
  _event( ev_CnUpdateSystemType_Nty )
  _body(EmTPUpdateType, 1)
  _ev_end

/***********************<<cns��������� >>********************** 
*[��Ϣ��]
*BOOL  CNS�����Ľ��
*[��Ϣ����]
*   cns -> cnc , cnupdate->cnagent
*/
  _event( ev_CnUpdateSystemFile_Ind )
  _body(BOOL, 1)
  _ev_end

  /***********************<<cns��������� >>********************** 
  *[��Ϣ��]
  *BOOL  CNS�����Ľ��
  *[��Ϣ����]
  *   cns -> cns 
  */
  _event( ev_CnUpdateStart_Nty )
  _body(s32, 1)
  _ev_end

  /***********************<<  ������������ >>********************	
  *[��Ϣ��]
  * +u8 , 1  //���ڵ�index
  *  
  *[��Ϣ����]
  *  cns -> cns
  */_event(   ev_CfgNetInfSelCmd )
  _body( u8 , 1 )
  _ev_end
   

    /***********************<<  ��ʱ���ϵͳʱ�� >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  cns -> cns
  */_event(   ev_CheckSysTime_Timer )
  _ev_end

   /***********************<< ���û�����Ƶ��ѡ��ʽ����ѡ >>********************	
  *[��Ϣ��]
  *TTPVidForamt ��Ƶ��ѡ��ʽ�ͷֱ�������
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgVideoFormat_Cmd)
  _body(TTPVidForamt, 1)
  _ev_end

  /***********************<< ���û�����ѡ��ʽ����ѡ >>********************	
  *[��Ϣ��]
  *TTPVidForamt ��Ƶ��ѡ��ʽ�ͷֱ�������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgVideoFormat_Ind)
  _body(TTPVidForamt, 1)
  _ev_end

  /***********************<< ������ʾ��ѡ��ʽ����ѡ >>********************	
  *[��Ϣ��]
  *TTPVidForamt ��Ƶ��ѡ��ʽ�ͷֱ�������
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgDualVideoFormat_Cmd)
  _body(TTPVidForamt, 1)
  _ev_end

   /***********************<< ���û�����ѡ��ʽ����ѡ >>********************	
  *[��Ϣ��]
  *TTPVidForamt ��Ƶ��ѡ��ʽ�ͷֱ�������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgDualVideoFormat_Ind)
  _body(TTPVidForamt, 1)
  _ev_end

  /***********************<< ���õ������� >>********************	
  *[��Ϣ��]
  *u16 ��������
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgCallRate_Cmd)
  _body(u16, 1)
  _ev_end

   /***********************<< ���õ������� >>********************	
  *[��Ϣ��]
  *u16 ��������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgCallRate_Ind)
  _body(u16, 1)
  _ev_end

  /***********************<< ������ʾ���� >>********************	
  *[��Ϣ��]
  *u16 ��ʾ����
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgDualCallRate_Cmd)
  _body(u16, 1)
  _ev_end

   /***********************<< ������ʾ���� >>********************	
  *[��Ϣ��]
  *u16 ��������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgDualCallRate_Ind)
  _body(u16, 1)
  _ev_end

  /***********************<< ���û�����ѯ�Ƿ��� >>********************	
  *[��Ϣ��]
  *TTPPollInfo ��ѯ��Ϣ
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgConfPoll_Cmd)
  _body(TTPPollInfo, 1)
  _ev_end

   /***********************<< ���û�����ѯ�Ƿ��� >>********************	
  *[��Ϣ��]
  *TTPPollInfo ��ѯ��Ϣ
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnCfgConfPoll_Ind)
  _body(TTPPollInfo, 1)
  _ev_end

  /***********************<< ���û��������Ƿ��� >>********************	
  *[��Ϣ��]
  *BOOL �Ƿ�������
  *[��Ϣ����]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgConfDis_Cmd)
  _body(BOOL, 1)

  _ev_end

   /***********************<< ���û��������Ƿ��� >>********************	
  *[��Ϣ��]
  *Bool �Ƿ�������
  *[��Ϣ����]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnCfgConfDis_Ind)
  _body(BOOL, 1)
  _ev_end

   /***********************<< ֪ͨ��ʾ����汾��Ϣ >>********************	
  *[��Ϣ��]
  *Bool �Ƿ�������
  *[��Ϣ����]
  * cns->tptool
  */
  _event( ev_CnVerInfo_Nty)
  _body(s8, MAX_DEVICEVER_LEN)
  _ev_end

  /***********************<< ���û�����Ƶ���� >>********************** 
  *[��Ϣ��]	
  * EmTpAudioFormat				��Ƶ����		
  *[��Ϣ����]
  *  cnc	  ->  cns
  */
  _event(  ev_CnCfgAudioFormat_Cmd )
  _body( EmTpAudioFormat, 1 )
  _ev_end

  /***********************<< ���û�����Ƶ���� >>********************** 
  *[��Ϣ��]	
  * EmTpAudioFormat				��Ƶ����		
  *[��Ϣ����]
  *  cns	  ->  cnc
  */
  _event(  ev_CnCfgAudioFormat_Ind )
  _body( EmTpAudioFormat, 1 )
  _ev_end

   /***********************<< ������ʾ������ >>********************** 
  *[��Ϣ��]	
  *BOOL                         �Ƿ���ʾ����ǽ
  * TTPDisplayType				��ʾ����������(��ʾ��1�����÷��ڵ�һ����Ϣ���У���ʾ��2�����÷��ڵڶ�����Ϣ����)		
  *[��Ϣ����]
  *  cnc	  ->  cns
  *����ǽ������ʱ��֧�����÷ֱ���ʾ��1��3���ź�Դ
  */
  _event(  ev_CnCfgDisplay_Cmd )
  _body (BOOL, 1)
  _body( TTPDisplayType, 2 )
  _ev_end

  /***********************<< ������ʾ������ >>********************** 
  *[��Ϣ��]	
  *BOOL                         �Ƿ���ʾ����ǽ
  * TTPDisplayType				��ʾ����������(��ʾ��1�����÷��ڵ�һ����Ϣ���У���ʾ��2�����÷��ڵڶ�����Ϣ����)		
  *[��Ϣ����]
  *  cnc	  <-  cns
  *����ǽ������ʱ��֧�����÷ֱ���ʾ��1��3���ź�Դ
  */
  _event(  ev_CnCfgDisplay_Ind )
  _body (BOOL, 1)
  _body( TTPDisplayType, 2 )
  _body ( BOOL, 1 )
  _ev_end
#ifndef _MakeTpEventDescription_
  _ev_segment_end( outercnssys )
};

#endif
#endif //TPP_EVENT_H
