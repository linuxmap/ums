
#ifndef __RABBITMQWRAP__
#define __RABBITMQWRAP__

#include "amqp.h"
#include "amqp_framing.h"
#include "amqp_mq.h"
#include "event.h"

#ifdef WIN32
	#ifdef __DLL_EXPORT__
		#define RMQ_API extern "C"			__declspec(dllexport)
	#else
		#define RMQ_API extern "C"			__declspec(dllimport) 
	#endif
#else
	#define RMQ_API extern "C"
#endif
 
#ifdef WIN32
#ifdef __DLL_EXPORT__
#define RMQ_API_NOEXTERNC 	__declspec(dllexport)
#else
#define RMQ_API_NOEXTERNC 	__declspec(dllimport) 
#endif
#else
#define RMQ_API_NOEXTERNC 
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#define MAXLEN_RBMSG	(unsigned int)(128 * 1024)		//��mq�ײ��ͬ�������128K
namespace rabbitmqwrap
{
	 
//exchange������
#define XMODE_DIRECT	"direct"
#define XMODE_FANOUT	"fanout"
#define XMODE_TOPIC		"topic"

// �ӿڷ���ֵ
typedef enum _RabbitRet 
{

	RT_ERROR = 0,
	RT_OK ,
} rabbitmqRt;


// �ص�����ԭ��(������amqp.h,����Ϊ����鿴ժ���ڴˣ�
/*
typedef void (*ConnectionTimeout_CB) ( amqp_connection_state_t, void *, size_t );
typedef void (*ConnectionFail_CB) ( amqp_connection_state_t, void *, size_t );

typedef void (*ContenHeaderProps_CB) ( amqp_connection_state_t, void *, size_t, void *, size_t );
typedef void (*ContentBody_CB) ( amqp_connection_state_t, void *, size_t, response_type *rsp_type );

typedef void (*PublisherConfirm_CB) ( amqp_connection_state_t, void *, response_type );
typedef void (*QueueDeclare_CB) ( amqp_connection_state_t, void *, size_t );
*/


/*========================================================================================
    ������      ��RabbitmqClntInit
    ����        ����ʼ��Rabbitmq�ͻ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����char *pchSvrip	[i] rabbitmq server ip
				  u16   wSvrPort	[i] rabbitmq server listening port	(default is 5672)
				  char *pchVhost	[i] virtual host					(default is /)
				  char *pchName		[i] login username					(default is guest)
				  char *pchPwd		[i] login password					(default is guest)
    ����ֵ˵��  ��RT_OK��ɹ�
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2014-2-24   5.0         xueliang       create
==========================================================================================*/
RMQ_API int RabbitmqClntInit(IN const char *pchSvrip, IN unsigned short wSvrPort = 5672, IN const char *pchVhost = "/", IN const char *pchName="guest", IN const char *pchPwd="guest" );
//amqp://dev:dev@172.16.186.81:5672/%2f,Ϊ֧��url��׼��%2f�ǰٷֺű��룬������/��������
RMQ_API int RabbitmqClntInitByUrl(IN const char *pchUrl);

/*========================================================================================
    ������      ��RabbitmqClntQuit
    ����        ���˳�RabbitMQ�ͻ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��RT_OK��ɹ�
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2016-3-25   5.0         �޿���       create
==========================================================================================*/
RMQ_API void RabbitmqClntQuit();

typedef void(*PFOspPrintf)(signed int bScreen, signed int bFile, const char * szFormat, ...);
RMQ_API void SetOspPrintFP(PFOspPrintf pf);

/*========================================================================================
    ������      ��CreateP
    ����        ������һ��������
    �㷨ʵ��    ������һ��Ͷ����Ϣ�õĶ��в�ָ��һЩ�ص�����
    ����ȫ�ֱ�����
    �������˵����conn_success_cb		[i] callback for connect			(default is NULL)
				  conn_disconnect_cb	[i] callback for disconnect			(default is NULL)
				  publisher_confirm_cb	[i] callback for publisher confirm	(default is NULL)
				  nHeartBeat			[i] heartbeat seconds	(�������ʧ�ܣ�����ص�	ConnectionFail_CB��	
    ����ֵ˵��  ������ͬ�������߰󶨵���Ϣ���еľ����ʶ��֮����Ϣ�ӿ�����Ҫ����ñ�ʶ���Ա������ĸ�������Ҫ����Ϣ��
				  �д������ʱ���򷵻صı�ʶΪ0.
------------------------------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2014-9		5.0         xueliang       create
==========================================================================================*/
//�����߶�������ʧ�ܻص������������߶�����Ϣ��
//��ʱadd_producerֱ���ɹ�
RMQ_API unsigned int SafeCreateP(IN ConnectionSucc_CB conn_success_cb = NULL,
	IN ConnectionFail_CB conn_disconnect_cb = NULL, 
	IN PublisherConfirm_CB publisher_confirm_cb = NULL, 
	IN int nHeartBeat = 30/*, int nMandatory = 0, char *producertag = NULL*/ );

RMQ_API unsigned int SafeCreateProducer(const char* pchIp, uint16_t wPort,
	const char* pchVhost, const char* pchName, const char* pchPwd,
	ConnectionSucc_CB conn_success_cb = NULL,
	ConnectionFail_CB conn_disconnect_cb = NULL,
	PublisherConfirm_CB publisher_confirm_cb = NULL,
	int nHeartBeat = 30);


//amqp://dev:dev@172.16.186.81:5672/%2f,Ϊ֧��url��׼��%2f�ǰٷֺű��룬������/��������
RMQ_API unsigned int SafeCreateProducerByUrl(const char* pchUrl,
	ConnectionSucc_CB conn_success_cb = NULL,
	ConnectionFail_CB conn_disconnect_cb = NULL,
	PublisherConfirm_CB publisher_confirm_cb = NULL,
	int nHeartBeat = 30);
//API int DestroyP( int *pnRBmq);	//��ʱ��֧�֣��ҽӿ����岻��

/*========================================================================================
    ������      ��CreateC
    ����        ������һ��������
    �㷨ʵ��    ������һ������Queue���󶨶�Ӧ�Ļص�����
    ����ȫ�ֱ�����
    �������˵����pchQname				[i] Consume Queue name			
				  pchExchange			[i] Exchange name			(default is NULL)
				  pchRoutingkey			[i] Routing key name		(default is NULL)
				  body_cb				[i] �յ���Ϣ����Ϣ���ݻص�����ָ��	(default is NULL)
				  header_props_cb		[i]	��Ϣͷ�ص�����ָ��		(default is NULL)
				  anonymous_queue_declare_cb		[i] �Ӹûص��л�ȡserer�Զ����ɵ�queue ����, ������������queue
				  conn_success_cb		[i] callback for connect	(default is NULL)
				  conn_disconnect_cb	[i] callback for disconnect	(default is NULL)
				  nExclusive			[i] if exclusive attribute  (default is 1, exclusive)
											Exclusive queues may only be accessed by the current connection, 
											and are deleted when that connection closes
				  nDurable				[i] ����Q�ĳ־û�����		(default is 0)
				  nAutoack				[i] see 5.0 document		(default is 0)	
											The default means you want to explicitly acknowledge received messages. 
											This will keep Rabbit from sending new messages from the queue 
											until you��ve processed and acknowledged the last one you received.
											��������rpcģ�ͣ�client��CreateCʱ����ֵ������1����ʾ�Զ�ack
				  nPrefetch_count		[i]	see 5.0 document		(default is 1) 
											The default tells RabbitMQ not to give more than one message to a worker at a time
				  nHeartBeat			[i] heartbeat seconds	(�������ʧ�ܣ�����ص�	ConnectionFail_CB��				
    ����ֵ˵��  ���ɹ�����1��RT_OK); ʧ�ܷ���0��RT_ERROR��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2014-9		5.0         xueliang       create
==========================================================================================*/
typedef void(*ConnectionSuccCB) (amqp_connection_state_t conn, char *desc, char* pchTag);
typedef void(*ConnectionFailCB) (amqp_connection_state_t conn, const char *expect, const char *recv, char* pchTag);
typedef void(*ContenHeaderPropsCB) (amqp_connection_state_t conn, void *correlation_id, size_t idLen, void *replyTo, size_t replyToLen, char* pchTag);
typedef void(*ContentBodyCB) (amqp_connection_state_t conn, void *body, size_t bodyLen, response_type *rsp_type, char* pchTag);
typedef void(*AnonymousQueueDeclareCB) (amqp_connection_state_t conn, void *queueName, size_t queueNameLen, char* pchTag);

//�������ߴ����ӿڣ��ص�������Ҫ����tag������ҵ���ȡtagӦ������������ȡ
//ԭamqp_connection_state_t conn�����е�tag���ھ���ʵ��,ҵ��Ӧ����֪
RMQ_API int SafeCreateC(IN const char *pchQname, IN const char *pchExchange = NULL, IN const char *pchRoutingkey = NULL,
	IN ContentBodyCB body_cb = NULL,
	IN ContenHeaderPropsCB header_props_cb = NULL,
	IN AnonymousQueueDeclareCB anonymous_queue_declare_cb = NULL,
	IN ConnectionSuccCB conn_success_cb = NULL,
	IN ConnectionFailCB conn_disconnect_cb = NULL,
	IN int nHeartBeat = 30,
	IN unsigned int nAttr = EXCLUSIVE, //��λ����ʽ�������ԣ���EXCLUSIVE|DURABLE
	IN int nAutoack = 0, IN int nPrefetch_count = 1,
	IN const char *pchTag = NULL);

RMQ_API int SafeCreateConsumer(IN const char* pchIp, IN uint16_t wPort,
	IN const char* pchVhost, IN const char* pchName, IN const char* pchPwd,
	IN const char *pchQname, IN const char *pchExchange = NULL, IN const char *pchRoutingkey = NULL,
	IN ContentBodyCB body_cb = NULL,
	IN ContenHeaderPropsCB header_props_cb = NULL,
	IN AnonymousQueueDeclareCB anonymous_queue_declare_cb = NULL,
	IN ConnectionSuccCB conn_success_cb = NULL,
	IN ConnectionFailCB conn_disconnect_cb = NULL,
	IN int nHeartBeat = 30,
	IN unsigned int nAttr = EXCLUSIVE, //��λ����ʽ�������ԣ���EXCLUSIVE|DURABLE
	IN int nAutoack = 0, IN int nPrefetch_count = 1,
	IN const char *pchTag = NULL);

//amqp://dev:dev@172.16.186.81:5672/%2f,Ϊ֧��url��׼��%2f�ǰٷֺű��룬������/��������
RMQ_API int SafeCreateConsumerByUrl(IN const char* pchUrl,
	IN const char *pchQname, IN const char *pchExchange = NULL, IN const char *pchRoutingkey = NULL,
	IN ContentBodyCB body_cb = NULL,
	IN ContenHeaderPropsCB header_props_cb = NULL,
	IN AnonymousQueueDeclareCB anonymous_queue_declare_cb = NULL,
	IN ConnectionSuccCB conn_success_cb = NULL,
	IN ConnectionFailCB conn_disconnect_cb = NULL,
	IN int nHeartBeat = 30,
	IN unsigned int nAttr = EXCLUSIVE, //��λ����ʽ�������ԣ���EXCLUSIVE|DURABLE
	IN int nAutoack = 0, IN int nPrefetch_count = 1,
	IN const char *pchTag = NULL);
/*========================================================================================
    ������      ��PostMsg
    ����        ��Ͷ����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����nRBmq					[i] ��ӦCreatePʱ��õ�rabbitmq�����ʶ
				  content				[i] message content
				  wContentlen			[i] length of the content
				  pRkey					[i] routing key name
				  pXname				[i] exchange name
										��exchangeȱʡģʽ�£�routing key��Զ���Ҫ���ѵ�Queue name�� Exchange����Ҫ��ֵ
										��exchangeΪfanout����ʱ��routing key����Ҫ��ֵ�� Exchange����ָ��ֵ
				  nPersistant			[i] �Ƿ�־�
				  nRPC_mode			    [i] �Ƿ���RPCģʽ
				  correlation_id		[i] ��RPCģʽ�²����ֵ����Ǵ˴η���Ϣ��Ӧ��ID������֮���յ���Ӧ��header_props_cb�ص���У���Ƿ��Ǹ���Ϣ�Ļ�Ӧ
				  reply_to				[i] ��RPCģʽ�²����ֵ��ָʾ�Զ�Ҫ��Ӧ���ĸ�Queue
				  dwTTL					[i] ��Ϣ���ʱ�䣬0Ϊ����
    ����ֵ˵��  ��RT_OK��ɹ�
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API int PostMsg(IN unsigned int dwRBMq, IN const char* content, IN unsigned int dwContentlen, IN const char *pRkey,
	IN const char *pXname = NULL,  IN int nPersistant = 0, 
	IN int nRPC_mode = 0, IN const char *correlation_id = NULL, IN const char *reply_to = NULL, IN unsigned int dwTTL = 0);

/*========================================================================================
    ������      ��CreateX
    ����        ������һ��Exchagne
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����pXname				[i] exchange name
				  pXtype				[i] exchange type	��ȡֵΪXMODE_DIRECT, XMODE_FANOUT, XMODE_TOPIC�е�һ�֣�				
    ����ֵ˵��  ��RT_OK��ɹ�
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API int CreateX(IN char *pXname, IN char *pXtype/*, IN int nDurable = 0*/);


/*========================================================================================
    ������      ��DeleteQ
    ����        ��ɾ��һ��Queue ���˽ӿڻ����ò�����������ʹ�ã�
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����pQname				[i] Queue name
    ����ֵ˵��  ��RT_OK��ɹ�
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API int DeleteQ(char *pQname);


/*========================================================================================
    ������      ��setrabbitmqlvl
    ����        �����ô�ӡ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����int nlvl			[i] ��ӡ����
				  0 --- �رմ�ӡ
				  1 --- ��ӡERROR��Ϣ
				  2 --- ��ӡWARNING��ERROR��Ϣ
				  3 --- ��ӡ������Ϣ
				  4 --- ��ӡ������Ϣ����ʱ�䣩
    ����ֵ˵��  ��void
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API void setrabbitmqlvl(IN int nlvl);

RMQ_API void showc();
RMQ_API void showp();

//"amqp://dev:dev@172.16.88.88:5672/%2f"
//�ɲ���/%2fĬ��Ϊ/��������
extern "C" struct RMQ_API_NOEXTERNC TMqParam
{
	TMqParam();

	char m_achIp[HOSTNAME_LEN];
	uint16_t m_wPort;
	char m_achVHost[VHOST_LEN];
	char m_achUserName[USER_LEN];
	char m_achPwd[PWD_LEN];
};

RMQ_API bool GetMqParamFromUrl(const char* pchUrl, struct TMqParam* tMqParam);

}	//end of namespace "rabbitmqwrap"

#endif
