
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

#define MAXLEN_RBMSG	(unsigned int)(128 * 1024)		//和mq底层库同步，最大128K
namespace rabbitmqwrap
{
	 
//exchange的类型
#define XMODE_DIRECT	"direct"
#define XMODE_FANOUT	"fanout"
#define XMODE_TOPIC		"topic"

// 接口返回值
typedef enum _RabbitRet 
{

	RT_ERROR = 0,
	RT_OK ,
} rabbitmqRt;


// 回调函数原型(声明在amqp.h,这里为方便查看摘入于此）
/*
typedef void (*ConnectionTimeout_CB) ( amqp_connection_state_t, void *, size_t );
typedef void (*ConnectionFail_CB) ( amqp_connection_state_t, void *, size_t );

typedef void (*ContenHeaderProps_CB) ( amqp_connection_state_t, void *, size_t, void *, size_t );
typedef void (*ContentBody_CB) ( amqp_connection_state_t, void *, size_t, response_type *rsp_type );

typedef void (*PublisherConfirm_CB) ( amqp_connection_state_t, void *, response_type );
typedef void (*QueueDeclare_CB) ( amqp_connection_state_t, void *, size_t );
*/


/*========================================================================================
    函数名      ：RabbitmqClntInit
    功能        ：初始化Rabbitmq客户端
    算法实现    ：
    引用全局变量：
    输入参数说明：char *pchSvrip	[i] rabbitmq server ip
				  u16   wSvrPort	[i] rabbitmq server listening port	(default is 5672)
				  char *pchVhost	[i] virtual host					(default is /)
				  char *pchName		[i] login username					(default is guest)
				  char *pchPwd		[i] login password					(default is guest)
    返回值说明  ：RT_OK表成功
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2014-2-24   5.0         xueliang       create
==========================================================================================*/
RMQ_API int RabbitmqClntInit(IN const char *pchSvrip, IN unsigned short wSvrPort = 5672, IN const char *pchVhost = "/", IN const char *pchName="guest", IN const char *pchPwd="guest" );
//amqp://dev:dev@172.16.186.81:5672/%2f,为支持url标准，%2f是百分号编码，代表着/虚拟主机
RMQ_API int RabbitmqClntInitByUrl(IN const char *pchUrl);

/*========================================================================================
    函数名      ：RabbitmqClntQuit
    功能        ：退出RabbitMQ客户端
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：RT_OK表成功
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2016-3-25   5.0         邹俊龙       create
==========================================================================================*/
RMQ_API void RabbitmqClntQuit();

typedef void(*PFOspPrintf)(signed int bScreen, signed int bFile, const char * szFormat, ...);
RMQ_API void SetOspPrintFP(PFOspPrintf pf);

/*========================================================================================
    函数名      ：CreateP
    功能        ：创建一个生产者
    算法实现    ：生成一个投递消息用的队列并指定一些回调函数
    引用全局变量：
    输入参数说明：conn_success_cb		[i] callback for connect			(default is NULL)
				  conn_disconnect_cb	[i] callback for disconnect			(default is NULL)
				  publisher_confirm_cb	[i] callback for publisher confirm	(default is NULL)
				  nHeartBeat			[i] heartbeat seconds	(心跳检测失败，将会回调	ConnectionFail_CB）	
    返回值说明  ：返回同该生产者绑定的消息队列的句柄标识，之后发消息接口中需要传入该标识，以表明是哪个生产者要发消息。
				  有错误产生时，则返回的标识为0.
------------------------------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2014-9		5.0         xueliang       create
==========================================================================================*/
//生产者断链连接失败回调，不清生产者队列消息，
//定时add_producer直到成功
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


//amqp://dev:dev@172.16.186.81:5672/%2f,为支持url标准，%2f是百分号编码，代表着/虚拟主机
RMQ_API unsigned int SafeCreateProducerByUrl(const char* pchUrl,
	ConnectionSucc_CB conn_success_cb = NULL,
	ConnectionFail_CB conn_disconnect_cb = NULL,
	PublisherConfirm_CB publisher_confirm_cb = NULL,
	int nHeartBeat = 30);
//API int DestroyP( int *pnRBmq);	//暂时不支持，且接口意义不大。

/*========================================================================================
    函数名      ：CreateC
    功能        ：创建一个消费者
    算法实现    ：创建一个消费Queue并绑定对应的回调函数
    引用全局变量：
    输入参数说明：pchQname				[i] Consume Queue name			
				  pchExchange			[i] Exchange name			(default is NULL)
				  pchRoutingkey			[i] Routing key name		(default is NULL)
				  body_cb				[i] 收到消息的消息内容回调函数指针	(default is NULL)
				  header_props_cb		[i]	消息头回调函数指针		(default is NULL)
				  anonymous_queue_declare_cb		[i] 从该回调中获取serer自动生成的queue 名字, 用于生成匿名queue
				  conn_success_cb		[i] callback for connect	(default is NULL)
				  conn_disconnect_cb	[i] callback for disconnect	(default is NULL)
				  nExclusive			[i] if exclusive attribute  (default is 1, exclusive)
											Exclusive queues may only be accessed by the current connection, 
											and are deleted when that connection closes
				  nDurable				[i] 设置Q的持久化属性		(default is 0)
				  nAutoack				[i] see 5.0 document		(default is 0)	
											The default means you want to explicitly acknowledge received messages. 
											This will keep Rabbit from sending new messages from the queue 
											until you’ve processed and acknowledged the last one you received.
											在运用于rpc模型，client端CreateC时，该值建议填1，表示自动ack
				  nPrefetch_count		[i]	see 5.0 document		(default is 1) 
											The default tells RabbitMQ not to give more than one message to a worker at a time
				  nHeartBeat			[i] heartbeat seconds	(心跳检测失败，将会回调	ConnectionFail_CB）				
    返回值说明  ：成功返回1（RT_OK); 失败返回0（RT_ERROR）
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2014-9		5.0         xueliang       create
==========================================================================================*/
typedef void(*ConnectionSuccCB) (amqp_connection_state_t conn, char *desc, char* pchTag);
typedef void(*ConnectionFailCB) (amqp_connection_state_t conn, const char *expect, const char *recv, char* pchTag);
typedef void(*ContenHeaderPropsCB) (amqp_connection_state_t conn, void *correlation_id, size_t idLen, void *replyTo, size_t replyToLen, char* pchTag);
typedef void(*ContentBodyCB) (amqp_connection_state_t conn, void *body, size_t bodyLen, response_type *rsp_type, char* pchTag);
typedef void(*AnonymousQueueDeclareCB) (amqp_connection_state_t conn, void *queueName, size_t queueNameLen, char* pchTag);

//新消费者创建接口，回调函数需要新增tag参数，业务读取tag应从新增参数读取
//原amqp_connection_state_t conn参数中的tag用于具体实现,业务应不感知
RMQ_API int SafeCreateC(IN const char *pchQname, IN const char *pchExchange = NULL, IN const char *pchRoutingkey = NULL,
	IN ContentBodyCB body_cb = NULL,
	IN ContenHeaderPropsCB header_props_cb = NULL,
	IN AnonymousQueueDeclareCB anonymous_queue_declare_cb = NULL,
	IN ConnectionSuccCB conn_success_cb = NULL,
	IN ConnectionFailCB conn_disconnect_cb = NULL,
	IN int nHeartBeat = 30,
	IN unsigned int nAttr = EXCLUSIVE, //按位或形式增加属性，如EXCLUSIVE|DURABLE
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
	IN unsigned int nAttr = EXCLUSIVE, //按位或形式增加属性，如EXCLUSIVE|DURABLE
	IN int nAutoack = 0, IN int nPrefetch_count = 1,
	IN const char *pchTag = NULL);

//amqp://dev:dev@172.16.186.81:5672/%2f,为支持url标准，%2f是百分号编码，代表着/虚拟主机
RMQ_API int SafeCreateConsumerByUrl(IN const char* pchUrl,
	IN const char *pchQname, IN const char *pchExchange = NULL, IN const char *pchRoutingkey = NULL,
	IN ContentBodyCB body_cb = NULL,
	IN ContenHeaderPropsCB header_props_cb = NULL,
	IN AnonymousQueueDeclareCB anonymous_queue_declare_cb = NULL,
	IN ConnectionSuccCB conn_success_cb = NULL,
	IN ConnectionFailCB conn_disconnect_cb = NULL,
	IN int nHeartBeat = 30,
	IN unsigned int nAttr = EXCLUSIVE, //按位或形式增加属性，如EXCLUSIVE|DURABLE
	IN int nAutoack = 0, IN int nPrefetch_count = 1,
	IN const char *pchTag = NULL);
/*========================================================================================
    函数名      ：PostMsg
    功能        ：投递消息
    算法实现    ：
    引用全局变量：
    输入参数说明：nRBmq					[i] 对应CreateP时获得的rabbitmq句柄标识
				  content				[i] message content
				  wContentlen			[i] length of the content
				  pRkey					[i] routing key name
				  pXname				[i] exchange name
										在exchange缺省模式下，routing key填对端需要消费的Queue name， Exchange不需要赋值
										在exchange为fanout类型时，routing key不需要赋值， Exchange赋上指定值
				  nPersistant			[i] 是否持久
				  nRPC_mode			    [i] 是否用RPC模式
				  correlation_id		[i] 在RPC模式下才填该值，标记此次发消息对应的ID，用于之后收到回应在header_props_cb回调中校验是否是该消息的回应
				  reply_to				[i] 在RPC模式下才填该值，指示对端要回应到哪个Queue
				  dwTTL					[i] 消息存活时间，0为永久
    返回值说明  ：RT_OK表成功
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API int PostMsg(IN unsigned int dwRBMq, IN const char* content, IN unsigned int dwContentlen, IN const char *pRkey,
	IN const char *pXname = NULL,  IN int nPersistant = 0, 
	IN int nRPC_mode = 0, IN const char *correlation_id = NULL, IN const char *reply_to = NULL, IN unsigned int dwTTL = 0);

/*========================================================================================
    函数名      ：CreateX
    功能        ：创建一个Exchagne
    算法实现    ：
    引用全局变量：
    输入参数说明：pXname				[i] exchange name
				  pXtype				[i] exchange type	（取值为XMODE_DIRECT, XMODE_FANOUT, XMODE_TOPIC中的一种）				
    返回值说明  ：RT_OK表成功
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API int CreateX(IN char *pXname, IN char *pXtype/*, IN int nDurable = 0*/);


/*========================================================================================
    函数名      ：DeleteQ
    功能        ：删除一个Queue （此接口基本用不到，不建议使用）
    算法实现    ：
    引用全局变量：
    输入参数说明：pQname				[i] Queue name
    返回值说明  ：RT_OK表成功
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API int DeleteQ(char *pQname);


/*========================================================================================
    函数名      ：setrabbitmqlvl
    功能        ：设置打印级别
    算法实现    ：
    引用全局变量：
    输入参数说明：int nlvl			[i] 打印级别
				  0 --- 关闭打印
				  1 --- 打印ERROR信息
				  2 --- 打印WARNING及ERROR信息
				  3 --- 打印所有信息
				  4 --- 打印所有信息（含时间）
    返回值说明  ：void
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2014-9		5.0         xueliang       create
==========================================================================================*/
RMQ_API void setrabbitmqlvl(IN int nlvl);

RMQ_API void showc();
RMQ_API void showp();

//"amqp://dev:dev@172.16.88.88:5672/%2f"
//可不填/%2f默认为/虚拟主机
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
