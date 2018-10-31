/*****************************************************************************
   ģ����      : sitecall
   �ļ���      : sitecall.h
   ����ļ�    : sitecall.CPP
   �ļ�ʵ�ֹ���: ʵ�����к���
   ����        : ZHHE
   �汾        : V4.0  Copyright(C) 2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
******************************************************************************/

#ifndef _SITECALL_H
#define _SITECALL_H


#ifdef __cplusplus
extern "C" {
#endif

#include "transportint.h"

#if defined(_PROFESSION_) || defined(_ANDROID_) || defined(RV_42)
#include "mti.h"
typedef enum
{
	liEvRead=0x01,
	liEvWrite=0x02,
	liEvAccept=0x08,
	liEvConnect=0x10,
	liEvClose=0x20
} liEvents;
#endif

/*================================= �궨�� ================================*/	
#define NUMOFSESSION	4
#define NUMOFHOST		4
#define MAXBUFFSIZE		2048
#if defined _ENABLE_QUANTUM_PROJECT_ && defined _KDV_RV_H323_STACK_
#define RPOOLCHUNKSIZE  1460
#else
#define RPOOLCHUNKSIZE  512
#endif
#define MAXHOSTNUM		8	//client
#define MAXCONNECTION	MAXHOSTNUM	//gk
#define TRANSTIMEOUT	30000
#define SITECALLTIMEOUT	30000
	
#ifndef SITECALLPORT
#define SITECALLPORT	700
#endif

DECLARE_OPAQUE(HSITECALL);	
	
enum SiteCallState
{
	SiteCallHostClosed,
	SiteCallTimeOut,
	SiteCallHostConnected
};

/*================================= �ṹ���� ================================*/
typedef struct tagSiteCallTransHost
{
	BOOL                used;
	BOOL                incoming;
	BOOL                reported;
	HOSTSTATE           state;
	cmTransportAddress  remoteAddress;
	cmTransportAddress  localAddress;
	HTPKT               hTpkt;
	HTI					hTimer;
	void                *firstMessage;
	void                *lastMessage;
	void                *incomingMessage;
}scTransHost;

typedef struct tagSiteCallNetAddr
{
	u32 ip;
	u16 port;
}SCNetAddr;

typedef struct tagSiteCallConfig
{
	BOOL bGk;
	SCNetAddr localAddr;
	SCNetAddr GkAddr;
	int		  maxClientNum;
}SiteCallConfig, *PSiteCallConfig;

typedef int (* NotifyHostStateT)(HSITECALL hSiteCall, int state);
typedef int (* NotifyReceiveMessageT)(HSITECALL hSiteCall, unsigned char* pBuf, int nBufLen);
	
typedef  struct
{
	NotifyHostStateT					fpNotifySiteCallState;
	NotifyReceiveMessageT				fpNotifyReceiveMessage;
}TRANSEVENTS, *LPTRANSEVENTS;

typedef struct tagSiteCallTransGlobals{
    HRPOOL              messagesRPool;
    TRANSEVENTS			scEvents;
    HTPKTCTRL           tpktCntrl;
    scTransHost         *hostListen;
	scTransHost			*host[MAXHOSTNUM];
	HSTIMER				hTimer;
	SiteCallConfig		config;
    int                 codingBufferSize;
	int					curClientNum;
	int		maxUsedNumOfMessagesInRpool;
	int		curUsedNumOfMessagesInRpool;
} scTransGlobals;

extern scTransGlobals* g_ptTrans;


/*====================================================================
��	 ��   ��: SiteCallInit
��	      ��: initialize sitecall module
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ��			  
��   ��   ֵ: �ɹ� - TRUE
			  ʧ�� - FALSE		
====================================================================*/
RVAPI BOOL RVCALLCONV TransSiteCallInit(SiteCallConfig* pConfig);

/*====================================================================
��	 ��   ��: SetCallBack
��	      ��: register callback function
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: lpEvent - callback pointer
��   ��   ֵ: �ɹ� - sc_ok
			  ʧ�� - sc_err
====================================================================*/
RVAPI int RVCALLCONV TransSetCallBack(LPTRANSEVENTS lpEvent);

/*====================================================================
��	 ��   ��: CreateNewHost
��	      ��: create a new host for sitecall.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: 
��   ��   ֵ: host	- The host on which to send the messages that await to be sent.
              NULL  - failed.
====================================================================*/
RVAPI scTransHost* RVCALLCONV CreateNewHost();

/*====================================================================
��	 ��   ��: Connect2Gk
��	      ��: connect to GK server by tpkt.
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: host        - The host on which to connect.
��   ��   ֵ: sc_ok       - All is ok.
              sc_err	  - The connection is busy.
====================================================================*/
RVAPI int RVCALLCONV Connect2Gk(void* element);

/*====================================================================
��	 ��   ��: TransSiteCallHandle
��	      ��: The callback routine for a tpkt connection
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: standard input of TPKT callback	  
��   ��   ֵ: void	
====================================================================*/
void TransSiteCallHandle(HTPKT tpkt, liEvents event, int length, int error, void*context);

/*====================================================================
��	 ��   ��: SaveMsgToPool
��	      ��: This routine gets an encoded message and saves it, until it can send it.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: host         - The host on which the message is to be sent.
			  buffer       - The encoded message.
			  encMsgSize   - Its size.
			  addToTop     - TRUE: Add the message to the start of the queue
							 FALSE: Add it at the end.  
��   ��   ֵ: saved message	
====================================================================*/
RVAPI void * RVCALLCONV SiteCallSaveMsgToPool(void *element, unsigned char *buffer, int encMsgSize, BOOL addToTop = FALSE);

/*====================================================================
��	 ��   ��: ExtractMessageFromPool
��	      ��: This routine removes an encoded message from the head of the host list.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: element      - The host or session which wants to send the message.
��   ��   ֵ: next message.	
====================================================================*/
void *SiteCallExtractMessageFromPool(void *element);

/*====================================================================
��	 ��   ��: sendMessageOnHost
��	      ��: send a message on the given host according to its communication protocol.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: host        - The host on which to send the messages that await to be sent.
��   ��   ֵ: cmTransOK             - All is ok.
              cmTransConnectionBusy - The connection is still sending previous messages.
====================================================================*/
RVAPI int RVCALLCONV SendSiteCallMessage(void* element);

/*====================================================================
��	 ��   ��: TransSiteCallHostClosed
��	      ��: host closed.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: context     - The host or session which send the message.
��   ��   ֵ: void
====================================================================*/
void TransSiteCallHostClosed(void* context);

/*====================================================================
��	 ��   ��: PrintSiteCallState
��	      ��: print debug infomation.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: 
��   ��   ֵ: void
====================================================================*/
RVAPI void RVCALLCONV PrintSiteCallState();

/*====================================================================
��	 ��   ��: TransMessageTimeOut
��	      ��: host send message timeout or didn't receive response.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: context     - The host or session which send the message.
��   ��   ֵ: void
====================================================================*/
void TransMessageTimeOut(void* element);

/*====================================================================
��	 ��   ��: TransSiteCallTimeOut
��	      ��: sitecall timeout.
�� �� ʵ  ��: ��
����ȫ�ֱ���: ��
�������˵��: context     - The host to close
��   ��   ֵ: void
====================================================================*/
void TransSiteCallTimeOut(void* element);

/*====================================================================
��	 ��   ��: SiteCallClose
��	      ��: close sitecall host.
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ��			  
��   ��   ֵ: void	
====================================================================*/
RVAPI void RVCALLCONV SiteCallHostClose(void* element);

/*====================================================================
��	 ��   ��: SiteCallHostInit
��	      ��: 
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ��			  
��   ��   ֵ: void	
====================================================================*/
RVAPI void RVCALLCONV SiteCallHostInit(scTransHost* host);

/*====================================================================
��	 ��   ��: SiteCallSetGkIp
��	      ��: 
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ��			  
��   ��   ֵ: void	
====================================================================*/
RVAPI void RVCALLCONV SiteCallSetGatekeeperIp(u32 gkIp, u16 gkPort);

/*====================================================================
��	 ��   ��: SiteCallEnd
��	      ��: close sitecalll module
�� �� ʵ  ��: 
����ȫ�ֱ���: 
�������˵��: ��			  
��   ��   ֵ: void	
====================================================================*/
RVAPI void RVCALLCONV TransSiteCallEnd();


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /*_SITECALL_H*/

