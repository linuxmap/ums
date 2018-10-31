/*****************************************************************************
   ģ����      : kdv323adapter
   �ļ���      : kdv323adapter.h
   ����ļ�    : kdv323adapter.cpp
   �ļ�ʵ�ֹ���: ���ϲ�Ӧ���ṩAPI�����ͻص�����ԭ��
   ����        : �˻�
   �汾        : V3.0  Copyright(C) 2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2003/07/25  3.0         ��  ��      ����
   2004/07/19  3.1         κ�α�      �����Ż�
******************************************************************************/

#ifndef _H323ADAPTER_H
#define _H323ADAPTER_H

#include "osp.h"
//#define RV_H323_TRANSPORT_ADDRESS RV_H323_TRANSPORT_ADDRESS_ANY
//end
#include "h323stack4_2/cm.h"
#include <time.h>
#include <math.h>

#ifdef _ENABLE_QUANTUM_PROJECT_
#include "qtinterface.h"
#endif

#ifdef _LINUX_
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#endif//!_LINUX_

///////////////////////////////// KDV H323 Э��汾�� ///////////////////////////////
// ���� TH323CONFIG.SetVersionId
#define KDVH323_VERID      (u8*)"8"
#define LEN_KDVH323_VERID  strlen((s8*)KDVH323_VERID)
///////////////////////////////////////////////////////////////////////////////////

#include "h323callstdstruct.h" 
#include "h323confstdstruct.h"
#include "h323confnonstdstruct.h"
#include "h323callstdmsg.h"
#include "h323confstdmsg.h"
#include "h323confnonstdmsg.h"
#include "kdvdatanet.h"


///////////////////////////////// ���Ժ��� ///////////////////////////////



//�ָ������ṹ
PROTO_API BOOL32 NSM_DecodeAlias(IN u8 *pbyAliasBuf, IN u16 wAliasNum, IN u32 dwAliasBufLen, OUT TALIASADDR* atAlias, IN u16 wMaxAliasNum);
/***********************mmcu define**************************/


//��ʼ��������
PROTO_API BOOL32 MMcuStackInit(u16 wListenPort,BOOL32 bSockInit = FALSE);
//���ʼ��������
PROTO_API BOOL32 MMcuStackClean(BOOL32 bSockClean = FALSE);

//�µĻ��鼶���ɹ�֪ͨ
#define 	H_CASCADE_NEW_CALL_NTF   (s32)CASCADE_MSGTYPE_ENDING  
//���鼶���Ͽ�֪ͨ
#define     H_CASCADE_DROP_CALL_NTF  (s32)(H_CASCADE_NEW_CALL_NTF+1)
PROTO_EXTERN_API void mmcusetlog(u8 level);
PROTO_EXTERN_API void mmcuhelp();


///////////////////////////////// Outgoing Interface ////////////////////////////////

/*====================================================================
������      : NotifyNewCallT
����        : �������о��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall   - Э��ջ���о��
    		  lphaCall - Ӧ�ó�����о��
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyNewCallT)(HCALL hsCall, LPHAPPCALL lphaCall);
//add by daiqing 20100723 for 460 kdv
/*====================================================================
������      : NotifyNew460CallT
����        : �������о��
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall   - Э��ջ���о��
    		  lphaCall - Ӧ�ó�����о��
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyNew460CallT)(HCALL hsCall, LPHAPPCALL lphaCall , const void* pBuf , u16 nBufLen );
//end
/*====================================================================
������      : NotifyNewChanT
����        : �����ŵ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall - Ӧ�ó�����о��
			  hsCall - Э��ջ���о��
			  hsChan - Э��ջ�ŵ����
			  lphaChan - Ӧ�ó����ŵ����
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyNewChanT)(HAPPCALL haCall,HCALL hsCall,HCHAN hsChan,
										  LPHAPPCHAN lphaChan);

/*====================================================================
������      : NotifyCallCtrlMsgT
����        : ���п���֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
			  hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyCallCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,u16 msgType,
											  const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyChanCtrlMsgT
����        : �ŵ�����֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haChan  - Ӧ�ó����ŵ����
			  hsChan  - Э��ջ�ŵ����
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyChanCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
											  u16 msgType,const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyConfCtrlMsgT
����        : �������֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
			  hsCall  - Э��ջ���о��
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyConfCtrlMsgT)(HAPPCALL haCall, HCALL hsCall,u16 msgType,const void* pBuf,
											  u16 nBufLen);

/*====================================================================
������      : NotifyRasCtrlMsgT
����        : RAS��Ϣ֪ͨ����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: haCall  - Ӧ�ó�����о��
              hsCall  - Э��ջ���о��
              haRas   - Ӧ�ó���RAS���
			  hsRas   - Э��ջRAS���
			  msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyRasCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPRAS haRas, HRAS hsRas,u16 msgType,
											 const void* pBuf,u16 nBufLen);

/*====================================================================
������      : NotifyFeccMsgT
����        : H.224, H.281���ܻص�����
�㷨ʵ��    : ��
����ȫ�ֱ���: ��
�������˵��: hsCall     - Э��ջ���о��
              hsChan     - Э��ջ�ŵ����
			  feccStruct - Զң����(TFeccStruct)
			  terSrc     - Դ���ն��б�
			  terDst     - Դ���ն��б�
����ֵ˵��  : �ɹ� - cb_ok
              ʧ�� - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK *NotifyFeccMsgT)(HCALL hsCall, HCHAN hsChan, 
										  TFeccStruct feccStruct,
										  TTERLABEL terSrc, TTERLABEL terDst);

//MMcu ���鼶��������Ϣ�ص�����
typedef int (PROTO_CALLBACK *NotifyMMcuMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
                                          u16 msgType,const void* pBuf,u16 nBufLen);


//�ص�����ָ��ṹ
typedef struct 
{
    NotifyNewCallT		fpNewCall;
    NotifyNewChanT		fpNewChan;
    NotifyCallCtrlMsgT  fpCallCtrlMsg;
    NotifyChanCtrlMsgT  fpChanCtrlMsg;
    NotifyConfCtrlMsgT	fpConfCtrlMsg;
    NotifyRasCtrlMsgT	fpRasCtrlMsg;
    NotifyFeccMsgT      fpFeccMsg;  
    NotifyMMcuMsgT      fpMMcuMsg;    
	NotifyNew460CallT   fpNew460Call;
}H323EVENT,*LPH323EVENT;

///////////////////////////////// Incoming Interface ////////////////////////////////

/*====================================================================
��	 ��   ��: kdvInitH323Adapter
��	      ��: ��ʼ��H323����ģ��
�� �� ʵ  ��: 
����ȫ�ֱ���: g_hApp
�������˵��: sConfigFile(IN), Э��ջ�����ļ���
              keyParams(INOUT), Э��ջ�ؼ����ò���:
			  empFail,ʧ��ԭ��
	        1> �������ļ���ʼ��ʧ��ʱ��������Щ������ʼ��Э��ջ
			2> �������ļ���ʼ���ɹ�ʱ���������ļ���ȡһЩ�������ýṹ�У��Ա�����
			  
��   ��   ֵ: �ɹ� - &g_hApp
			  ʧ�� - NULL		
====================================================================*/
PROTO_API void* kdvInitH323Adapter(IN s8* pchConfigFile, IN TH323CONFIG *ptKeyParams, INOUT emInitFailReason *empFail=NULL);


/*====================================================================
��	 ��   ��: kdvSetStackAdditionalConfig
��	      ��: ����Э��ջ����
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ptStackConfig   - Э��ջ����
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSetStackAdditionalConfig(IN TAdditionalConfig* ptStackConfig);

/*====================================================================
��	 ��   ��: kdvCloseH323Adapter
��	      ��: �ر�H323����ģ��
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: ��
��   ��   ֵ: ��
====================================================================*/
PROTO_API void kdvCloseH323Adapter();

/*====================================================================
��	 ��   ��: kdvSetAppCallBack
��	      ��: ע��Ӧ�ûص�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: lpEvent - �ص������ṹָ��
��   ��   ֵ: �ɹ� - act_ok
			  ʧ�� - act_err
====================================================================*/
PROTO_API s32  kdvSetAppCallBack(IN LPH323EVENT lpEvent);

/*====================================================================
��	 ��   ��: kdvCheckMessage
��	      ��: ���Э��ջ�Ƿ��յ�H.323��Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: 
��   ��   ֵ: 
====================================================================*/
PROTO_API void kdvCheckMessage();

/*====================================================================
��	 ��   ��: kdvCreateNewCall
��	      ��: �����µĺ��У������ڷ��ͺ�����Ϣǰ����,�����ȴ����ٺ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: haCall -   Ӧ�ó�����о��
�� �� ��  ��: lphsCall - Э��ջ���о��
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvCreateNewCall(IN HAPPCALL haCall, OUT LPHCALL lphsCall, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCreateNewChan
��	      ��: �����µĺ��У������ڷ����ŵ���Ϣǰ����,�����ȴ����ٲ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: hsCall -   Э��ջ���о��
			  haChan -   Ӧ�ó����ŵ����
�� �� ��  ��: lphsCall - Э��ջ�ŵ����
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvCreateNewChan(IN HCALL hsCall, IN HAPPCHAN haChan, 
                     OUT LPHCHAN lphsChan, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCreateRASStartTransaction
��	      ��: ����RAS��Transaction�������ȴ����ٲ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: haRas       -   Ӧ�ó���RAS���
              transaction -   RAS�¼�����
              destAddress -   �����ն���GK��ַ������GK���ն˵�ַ
              hsCall      -   Э��ջ���о��
�� �� ��  ��: lphsRas -  Э��ջRAS���
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvCreateRASStartTransaction(IN  HAPPRAS          haRas,
                                 OUT LPHRAS           lphsRas,
                                 IN  cmRASTransaction transaction,
                                 IN  TNETADDR*        destAddress,
                                 IN  HCALL            hsCall,
                                 IN  bool             bSync = true);

/*====================================================================
��	 ��   ��: kdvSendRasCtrlMsg
��	      ��: ����RAS������Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall  - ���о��
              hsRas   - RAS���
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSendRasCtrlMsg(IN HCALL hsCall, IN HRAS hsRas, IN u16 msgType,
                      IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvSendCallCtrlMsg
��	      ��: ���ͺ��п�����Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall  - ���о��
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSendCallCtrlMsg(IN HCALL hsCall,IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvSendChanCtrlMsg
��	      ��: �����ŵ�������Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsChan  - �ŵ����
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSendChanCtrlMsg(IN HCHAN hsChan, IN u16 msgType,
                       IN const void* pBuf,IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvSendConfCtrlMsg
��	      ��: ���ͻ��������Ϣ
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall  - ���о��
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSendConfCtrlMsg(IN HCALL hsCall, IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCheckValid
��	      ��: �����о���ĺϷ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall	- ���о��
�������˵����
��   ��   ֵ: FALSE - ��Ч
              TRUE  - ��Ч
====================================================================*/
PROTO_API BOOL32 kdvCheckValid(IN HCALL hsCall);

/*====================================================================
��	 ��   ��: kdvCheckValid
��	      ��: ���ͨ������ĺϷ���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsChan    - ͨ�����
�������˵����
��   ��   ֵ: FALSE - ��Ч
              TRUE  - ��Ч
====================================================================*/
PROTO_API BOOL32 kdvCheckValid(IN HCHAN hsChan);

/*====================================================================
��	 ��   ��: kdvCallSetHandle
��	      ��: ����hsCall��Ӧ�ò���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall - Э��ջ���о��
              haCall - Ӧ�þ��
			  bSync  - �Ƿ�ͬ��
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvCallSetHandle(IN HCALL hsCall, IN HAPPCALL haCall, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvCallGetHandle
��	      ��: ���Ӧ�þ��
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall - Э��ջ���о��              
			  bSync  - �Ƿ�ͬ��
�������˵��: haCall - Ӧ�þ��
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvCallGetHandle(IN HCALL hsCall, OUT HAPPCALL* haCall, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvRasUpdateRegAliasList
��	      ��: ���±��˱���
�� �� ʵ  ��: 
����ȫ�ֱ���: g_hApp
�������˵��: alias  - ��������
			  size	 - ��������              
��   ��   ֵ: �ɹ�   - act_ok
              ʧ��   - act_err
====================================================================*/
PROTO_API s32 kdvRasUpdateRegAliasList(IN cmAlias alias[], IN s32 size);

/*====================================================================
��	 ��   ��: kdvSetGKRASAddress
��	      ��: ����gk��ַ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: hApp - HAPP
              tr   - GK��ַ              
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSetGKRASAddress(IN HAPP hApp, IN cmTransportAddress tr, bool bSync = true );

/*====================================================================
��	 ��   ��: kdvGetCallParam
��	      ��: ��ú��в���
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall	- ���о��
			  cpt		- ���в�������
			  bSync		- �Ƿ�ͬ��
�������˵����pBuf		- ����ֵ
			  nBufLen	- ��������
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvGetCallParam(IN HCALL hsCall, IN CallParamType cpt, 
                    OUT void* pBuf, OUT u16 nBufLen, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvIsMasterCall
��	      ��: ����Ƿ�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: FALSE - ����
              TRUE  - ����
====================================================================*/
PROTO_API BOOL32 kdvIsMasterCall(IN HCALL hsCall);

/*====================================================================
��	 ��   ��: kdvIsMasterTerminal
��	      ��: ������Ӿ����Ľ���Ƿ�master
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: FALSE - slave
              TRUE  - master
====================================================================*/
PROTO_API BOOL32 kdvIsMasterTerminal(IN HCALL hsCall);

/*====================================================================
��	 ��   ��: kdvGetLocalCallIPAddress
��	      ��: ��ȡ���˺��е���ʵIP
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: �������IP��ַ
====================================================================*/
#if ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_ANY)
PROTO_API ipAddress kdvGetLocalCallIPAddress(IN HCALL hsCall);
#elif ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_OLD)
PROTO_API u32 kdvGetLocalCallIPAddress(HCALL hsCall);
#endif

/*====================================================================
��	 ��   ��: IsAudioType
��	      ��: �ж��Ƿ���Ƶ����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: wPayLoadType	 - �غ�����
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
inline BOOL32 IsAudioType(IN u16 wPayLoadType)
{
	return PayloardIsAudioType(wPayLoadType); 
}

/*====================================================================
��	 ��   ��: IsVideoType
��	      ��: �ж��Ƿ���Ƶ����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: wPayLoadType	 - �غ�����
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
inline BOOL32 IsVideoType(IN u16 wPayLoadType)
{
	return PayloardIsVideoType(wPayLoadType);
}

/*====================================================================
��	 ��   ��: IsDataType
��	      ��: �ж��Ƿ���������
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: wPayLoadType	 - �غ�����
��   ��   ֵ: �ɹ� - ����0
              ʧ�� - С��0
====================================================================*/
inline BOOL32 IsDataType(IN u16 wPayLoadType)
{
	return PayloardIsDataType(wPayLoadType);
}

/* ����й�Э��ջ�ĺ������������ź������� */
PROTO_API s32 kdvCmCallGetParam(IN HCALL hsCall, IN cmCallParam param, IN s32 index,
                      INOUT s32* value, OUT s8* svalue, IN bool bSync = true);

PROTO_API s32 kdvCmRASStartTransaction(IN  HAPP hApp, IN  HAPPRAS haRas, OUT LPHRAS lphsRas,
                             IN  cmRASTransaction transaction, IN cmRASTransport* destAddress,
                             IN  HCALL hsCall, IN  bool bSync = true);

PROTO_API s32 kdvCmRASSetParam(IN HRAS hsRas, IN cmRASTrStage trStage, IN cmRASParam param,
                     IN s32 index, IN s32 value, IN char* svalue, IN bool bSync = true);

PROTO_API s32 kdvCmRASGetParam(IN HRAS hsRas, IN  cmRASTrStage trStage, IN  cmRASParam param,
                     IN s32 index, IN OUT s32* value, /* value or length */
                     IN s8* svalue, IN bool bSync = true);

PROTO_API s32 kdvCmRASRequest(IN  HRAS hsRas, IN  bool bSync = true);

PROTO_API s32 kdvCmRASClose(IN  HRAS hsRas, IN bool bSync = true);

/*====================================================================
��	 ��   ��: kdvRASSetCallAddress
��	      ��: ����ע����е�ַ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ta   - ���������ַ
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvRASSetCallAddress(IN HAPP hApp, IN cmTransportAddress tr);

/*====================================================================
��	 ��   ��: kdvSetlocalRASAddress
��	      ��: ����ע��RAS��ַ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ta   - ����RAS��ַ
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSetlocalRASAddress(IN HAPP hApp, IN cmTransportAddress tr);

PROTO_API const s8* GetCmAliasType		(AliasType dwAliasType);
PROTO_API const s8* GetCmAliasType		(cmAliasType dwAliasType);
PROTO_API const s8* GetCmPayloadString	(u16 wSubMsgType);
PROTO_API const s8* GetCmConfMsgString	(u16 wSubMsgType);
PROTO_API const s8* GetCmChanMsgString	(u16 wSubMsgType);
PROTO_API const s8* GetCmCallMsgString	(u16 wPayload);
PROTO_API const s8* GetCmRasMsgString	(u16 wSubMsgType);

/*====================================================================
��	 ��   ��: kdvUpdateGatekeeperID
��	      ��: ����GatekeeperID
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: tGKID   - gatekeeperid
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvUpdateGatekeeperID(IN HAPP hApp, IN cmAlias tGKID);

//���ڼ���
PROTO_API BOOL32 GetDesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);
PROTO_API BOOL32 GetAesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);

//���ͻ��鼶��������Ϣ
PROTO_API int kdvSendMMcuCtrlMsg(HCHAN hsChan,u16 msgType,const void* pBuf,u16 nBufLen,bool bSync = true);

/**˵��***********************************************************************
*
1.����˫���߼�ͨ��(����Э��ͨ��)(I incoming, O out )
> �߼�ͨ����ͻʱ�� master �ն˾ܾ�incoming channel
> I ����������tcp connectʱ��ack��Ϣ���������Э��ͨ��������ַ
> O ������ack���е���Э��ͨ��������ַ����Iû������tcp connectʱ,����tcp connect
2.����ͨ��
>h_chan_open,h_chan_openAck ֻ����дpayload, m_tRtp.ip.
*
******************************************************************************/

/************************** DNS Trans *****************************************/
typedef enum
{
    DNS_SUCCESS = 0,
    DNS_TIMEOUT,
    DNS_NOTFOUND,
    DNS_FAILED,
} dnsResult;

typedef s32 (*DnsCallBackT)(s32 nUserID, dnsResult eResult, s32 nIpNum, u32* adwIP);

PROTO_API int kdvDnsRequest(s8* pchName, u32 dwDnsServer, u32 dwUserID, 
                      DnsCallBackT ptDnsCallbackFunc, IN  BOOL32 bSync);

/******************************************************************************/

//����IRR��Ϣ�����ڲ�����HCALL�ĳ��ϣ������á�
PROTO_API s32 kdvSetRasIRR(HRAS hsRas, TIRRINFO* ptIRRInfo, bool bSync);

//��Ϣ�����������������ת��
PROTO_API s32 kdvH323Adapterhton(u16 msgType, void* pBuf, u16 nBufLen, BOOL32 bhton);

//����H323TOSֵ
PROTO_API s32 kdvSetH323TOS(IN s32 nTOS, IN bool bSync = true);
//��ȡH323TOSֵ
PROTO_API s32 kdvGetH323TOS();

//����ԶңTOSֵ, ��������kdvdatanet���ж���
// API s32 kdvSetDataTOS(s32 nTOS);
// API s32 kdvGetDataTOS();

PROTO_API s8* GetPeerVersionID(HCALL hsCall);
PROTO_API s8* GetPeerProductID(HCALL hsCall);
PROTO_API BOOL32 IsPeerSupportNewG7221c(HCALL hsCall);  //�Զ��Ƿ�֧����ȷ�ֽ����G7221C��Ƶ����

PROTO_API void KdvSetIsH460GW(BOOL32 bIsGw);

PROTO_API int KdvSendTpktPinhole(HCALL hsCall, cmTpktChanHandleType type, BOOL32 bSync = TRUE);
PROTO_API void KdvSetH460Config(BOOL32 bSupportH460, BOOL32 bMediaTraversalServer, BOOL32 bSupportTransMultiMedia);
PROTO_API void KdvSetCallApplicationHandle(HCALL hsCall, void* haCall);

// ���ñ����Ƿ�ΪUTF8����
PROTO_EXTERN_API void kdvSetLocalIsUTF8(BOOL32 bIsUtf8);


/*====================================================================
��	 ��   ��: kdvSetKDV323
��	      ��: ����Э��ջ����Э���ʽ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: bIsKDV323
			  TRUE - ���͸�ʽΪKD H.323
			  FALSE - ���͵ĸ�ʽΪ��׼H.323
��   ��   ֵ: �ɹ� - act_ok
			  ʧ�� - act_err
====================================================================*/
PROTO_EXTERN_API s32 kdvSetKDV323(IN BOOL32 bIsKDV323);

/*====================================================================
��	 ��   ��: kdvEnableQuantumCall
��	      ��: ����Э��ջ����Э���ʽ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: bIsQuantumCall
			  TRUE  - Quantum Call
			  FALSE - Common  Call
��   ��   ֵ: �ɹ� - act_ok
			  ʧ�� - act_err
====================================================================*/
PROTO_EXTERN_API s32 kdvEnableQuantumCall(IN BOOL32 bIsQuantumCall);

/*====================================================================
��	 ��   ��: kdv323std
��	      ��: ��ӡЭ��ջ����Э���ʽ
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: 

��   ��   ֵ: �ɹ� - TRUE
             ʧ�� - FALSE
====================================================================*/
PROTO_EXTERN_API BOOL32 kdv323std();

//add by zhanghb for kdvp2.0 MT SendNSM
/*====================================================================
��	 ��   ��: kdvManualRASSendNSM
��	      ��: MTΪ�ֶ�RASʱ���ͷǱ���Ϣ,�������ֶ�RAS
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall  - ���о��
              hsRas   - RAS���
              msgType - ��Ϣ����
			  pBuf    - ����������
			  nBufLen - ��������
			  ptDstNetAddr - Ŀ�ĵ�ַ
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvManualRASSendNSM(IN HCALL hsCall,IN HRAS hsRas,IN u16 msgType,
						IN const void* pBuf,IN u16 nBufLen,IN TNETADDR * ptDstNetAddr,IN bool bSync = true);
//end add 
/*====================================================================
��	 ��   ��: kdvSetH460Feature
��	      ��: ����֧��460����
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: bSupportH460   
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSetH460Feature(IN BOOL32 bSupportH460);

/*====================================================================
��	 ��   ��: kdvCloseCall
��	      ��: �رպ��о��
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�� �� ��  ��: hCall -   ���о��
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvCloseCall( IN HCALL hCall, IN bool bSync = true );

/*====================================================================
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: �������IP��ַ
====================================================================*/
PROTO_API u32 kdvGetLocalTCPAddress(HCALL hsCall, TNETADDR *tAddress );

/*====================================================================
��	 ��   ��: kdvConnectMMCU
��	      ��: ����MCU
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
              hsChan    - ͨ�����
              tDstAddr  - ���ӵ�ַ
�������˵����
��   ��   ֵ: �ɹ� - act_ok
              ʧ�� - act_err
====================================================================*/
PROTO_API s32	 kdvConnectMMCU(IN HCALL hsCall, IN HCHAN hsChan, IN  TNETADDR tDstAddr);


/*====================================================================
��	 ��   ��: kdvGetH225Ver
��	      ��: ��ȡH225�汾��
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: hsCall    - ���о��
�������˵����
��   ��   ֵ: 
====================================================================*/
PROTO_API u32	 kdvGetH225Ver(IN HCALL hsCall);

// [12/3/2008 zhangzhihua]add.�ֶ�ɾ��Զң��ռ��Դ.
PROTO_API s32 KdvH323FreeFeccRcvSession(IN HCHAN hsChan);
PROTO_API s32 KdvH323FreeFeccSendSession(IN HCHAN hsChan);

#ifdef _ENABLE_QUANTUM_PROJECT_
PROTO_EXTERN_API void QtInfo();
PROTO_EXTERN_API void QtCallAutoHangUp(BOOL32 bAutoHangUp);

/*====================================================================
��	 ��   ��: kdvSetQuantumLevel
��	      ��: ���ú������Ӽ��ܵȼ�
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: haCall			- ���˺���Ӧ�ò���
			  hsCall			- ���˺���Э�����������kdvCreateNewCall���ɵľ����
			  tQtCallParam      - ��Ҫ��ӱ��˺��м��ܵȼ��ͶԶ˵ı�����Ϣ
��   ��   ֵ: �ɹ� - act_ok
ʧ�� - act_err
====================================================================*/
PROTO_API s32 kdvSetQuantumLevel(IN HAPPCALL haCall, IN HCALL hsCall, IN TQtCallParam &tQtCallParam);

/*====================================================================
��	 ��   ��: kdvAdapterQuantumInit
��	      ��: ���ñ������Ӽ��ܳ�ʼ���������������ñ����������ýӿڣ�
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: tQuantumInitParam			- �������Ӽ��ܳ�ʼ������
			 
��   ��   ֵ: �ɹ� - TRUE
ʧ�� - FALSE
====================================================================*/
PROTO_API BOOL32 kdvAdapterQuantumInit(TQtInitParam &tQuantumInitParam);
#endif

#endif //_H323ADAPTER_H
