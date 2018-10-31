/*****************************************************************************
   模块名      : kdv323adapter
   文件名      : kdv323adapter.h
   相关文件    : kdv323adapter.cpp
   文件实现功能: 给上层应用提供API函数和回调函数原型
   作者        : 邓辉
   版本        : V3.0  Copyright(C) 2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2003/07/25  3.0         邓  辉      创建
   2004/07/19  3.1         魏治兵      代码优化
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

///////////////////////////////// KDV H323 协议版本号 ///////////////////////////////
// 用于 TH323CONFIG.SetVersionId
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


///////////////////////////////// 调试函数 ///////////////////////////////



//恢复别名结构
PROTO_API BOOL32 NSM_DecodeAlias(IN u8 *pbyAliasBuf, IN u16 wAliasNum, IN u32 dwAliasBufLen, OUT TALIASADDR* atAlias, IN u16 wMaxAliasNum);
/***********************mmcu define**************************/


//初始化级联库
PROTO_API BOOL32 MMcuStackInit(u16 wListenPort,BOOL32 bSockInit = FALSE);
//解初始化级联库
PROTO_API BOOL32 MMcuStackClean(BOOL32 bSockClean = FALSE);

//新的会议级联成功通知
#define 	H_CASCADE_NEW_CALL_NTF   (s32)CASCADE_MSGTYPE_ENDING  
//会议级联断开通知
#define     H_CASCADE_DROP_CALL_NTF  (s32)(H_CASCADE_NEW_CALL_NTF+1)
PROTO_EXTERN_API void mmcusetlog(u8 level);
PROTO_EXTERN_API void mmcuhelp();


///////////////////////////////// Outgoing Interface ////////////////////////////////

/*====================================================================
函数名      : NotifyNewCallT
功能        : 交换呼叫句柄
算法实现    : 无
引用全局变量: 无
输入参数说明: hsCall   - 协议栈呼叫句柄
    		  lphaCall - 应用程序呼叫句柄
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyNewCallT)(HCALL hsCall, LPHAPPCALL lphaCall);
//add by daiqing 20100723 for 460 kdv
/*====================================================================
函数名      : NotifyNew460CallT
功能        : 交换呼叫句柄
算法实现    : 无
引用全局变量: 无
输入参数说明: hsCall   - 协议栈呼叫句柄
    		  lphaCall - 应用程序呼叫句柄
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyNew460CallT)(HCALL hsCall, LPHAPPCALL lphaCall , const void* pBuf , u16 nBufLen );
//end
/*====================================================================
函数名      : NotifyNewChanT
功能        : 交换信道句柄
算法实现    : 无
引用全局变量: 无
输入参数说明: haCall - 应用程序呼叫句柄
			  hsCall - 协议栈呼叫句柄
			  hsChan - 协议栈信道句柄
			  lphaChan - 应用程序信道句柄
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyNewChanT)(HAPPCALL haCall,HCALL hsCall,HCHAN hsChan,
										  LPHAPPCHAN lphaChan);

/*====================================================================
函数名      : NotifyCallCtrlMsgT
功能        : 呼叫控制通知函数
算法实现    : 无
引用全局变量: 无
输入参数说明: haCall  - 应用程序呼叫句柄
			  hsCall  - 协议栈呼叫句柄
			  msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyCallCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,u16 msgType,
											  const void* pBuf,u16 nBufLen);

/*====================================================================
函数名      : NotifyChanCtrlMsgT
功能        : 信道控制通知函数
算法实现    : 无
引用全局变量: 无
输入参数说明: haCall  - 应用程序呼叫句柄
              hsCall  - 协议栈呼叫句柄
              haChan  - 应用程序信道句柄
			  hsChan  - 协议栈信道句柄
			  msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyChanCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
											  u16 msgType,const void* pBuf,u16 nBufLen);

/*====================================================================
函数名      : NotifyConfCtrlMsgT
功能        : 会议控制通知函数
算法实现    : 无
引用全局变量: 无
输入参数说明: haCall  - 应用程序呼叫句柄
			  hsCall  - 协议栈呼叫句柄
			  msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyConfCtrlMsgT)(HAPPCALL haCall, HCALL hsCall,u16 msgType,const void* pBuf,
											  u16 nBufLen);

/*====================================================================
函数名      : NotifyRasCtrlMsgT
功能        : RAS信息通知函数
算法实现    : 无
引用全局变量: 无
输入参数说明: haCall  - 应用程序呼叫句柄
              hsCall  - 协议栈呼叫句柄
              haRas   - 应用程序RAS句柄
			  hsRas   - 协议栈RAS句柄
			  msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK* NotifyRasCtrlMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPRAS haRas, HRAS hsRas,u16 msgType,
											 const void* pBuf,u16 nBufLen);

/*====================================================================
函数名      : NotifyFeccMsgT
功能        : H.224, H.281功能回调函数
算法实现    : 无
引用全局变量: 无
输入参数说明: hsCall     - 协议栈呼叫句柄
              hsChan     - 协议栈信道句柄
			  feccStruct - 远遥命令(TFeccStruct)
			  terSrc     - 源端终端列表
			  terDst     - 源端终端列表
返回值说明  : 成功 - cb_ok
              失败 - cb_err
====================================================================*/
typedef s32 (PROTO_CALLBACK *NotifyFeccMsgT)(HCALL hsCall, HCHAN hsChan, 
										  TFeccStruct feccStruct,
										  TTERLABEL terSrc, TTERLABEL terDst);

//MMcu 会议级联控制消息回调函数
typedef int (PROTO_CALLBACK *NotifyMMcuMsgT)(HAPPCALL haCall,HCALL hsCall,HAPPCHAN haChan,HCHAN hsChan,
                                          u16 msgType,const void* pBuf,u16 nBufLen);


//回调函数指针结构
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
函	 数   名: kdvInitH323Adapter
功	      能: 初始化H323适配模块
算 法 实  现: 
引用全局变量: g_hApp
输入参数说明: sConfigFile(IN), 协议栈配置文件名
              keyParams(INOUT), 协议栈关键配置参数:
			  empFail,失败原因
	        1> 从配置文件初始化失败时，根据这些参数初始化协议栈
			2> 从配置文件初始化成功时，从配置文件读取一些参数到该结构中，以备后用
			  
返   回   值: 成功 - &g_hApp
			  失败 - NULL		
====================================================================*/
PROTO_API void* kdvInitH323Adapter(IN s8* pchConfigFile, IN TH323CONFIG *ptKeyParams, INOUT emInitFailReason *empFail=NULL);


/*====================================================================
函	 数   名: kdvSetStackAdditionalConfig
功	      能: 设置协议栈配置
算 法 实  现: 
引用全局变量: 
输入参数说明: ptStackConfig   - 协议栈配置
返   回   值: 成功 - act_ok
失败 - act_err
====================================================================*/
PROTO_API s32 kdvSetStackAdditionalConfig(IN TAdditionalConfig* ptStackConfig);

/*====================================================================
函	 数   名: kdvCloseH323Adapter
功	      能: 关闭H323适配模块
算 法 实  现: 
引用全局变量: 无
输入参数说明: 无
返   回   值: 无
====================================================================*/
PROTO_API void kdvCloseH323Adapter();

/*====================================================================
函	 数   名: kdvSetAppCallBack
功	      能: 注册应用回调函数
算 法 实  现: 
引用全局变量: 无
输入参数说明: lpEvent - 回调函数结构指针
返   回   值: 成功 - act_ok
			  失败 - act_err
====================================================================*/
PROTO_API s32  kdvSetAppCallBack(IN LPH323EVENT lpEvent);

/*====================================================================
函	 数   名: kdvCheckMessage
功	      能: 检查协议栈是否收到H.323消息
算 法 实  现: 
引用全局变量: 无
输入参数说明: 
返   回   值: 
====================================================================*/
PROTO_API void kdvCheckMessage();

/*====================================================================
函	 数   名: kdvCreateNewCall
功	      能: 创建新的呼叫，主叫在发送呼叫消息前调用,必须先创建再呼叫
算 法 实  现: 
引用全局变量: 无
输 入 参  数: haCall -   应用程序呼叫句柄
输 出 参  数: lphsCall - 协议栈呼叫句柄
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvCreateNewCall(IN HAPPCALL haCall, OUT LPHCALL lphsCall, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvCreateNewChan
功	      能: 创建新的呼叫，主叫在发送信道消息前调用,必须先创建再操作
算 法 实  现: 
引用全局变量: 无
输 入 参  数: hsCall -   协议栈呼叫句柄
			  haChan -   应用程序信道句柄
输 出 参  数: lphsCall - 协议栈信道句柄
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvCreateNewChan(IN HCALL hsCall, IN HAPPCHAN haChan, 
                     OUT LPHCHAN lphsChan, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvCreateRASStartTransaction
功	      能: 创建RAS的Transaction，必须先创建再操作
算 法 实  现: 
引用全局变量: 无
输 入 参  数: haRas       -   应用程序RAS句柄
              transaction -   RAS事件类型
              destAddress -   对于终端是GK地址，对于GK是终端地址
              hsCall      -   协议栈呼叫句柄
输 出 参  数: lphsRas -  协议栈RAS句柄
返   回   值: 成功 - act_ok
失败 - act_err
====================================================================*/
PROTO_API s32 kdvCreateRASStartTransaction(IN  HAPPRAS          haRas,
                                 OUT LPHRAS           lphsRas,
                                 IN  cmRASTransaction transaction,
                                 IN  TNETADDR*        destAddress,
                                 IN  HCALL            hsCall,
                                 IN  bool             bSync = true);

/*====================================================================
函	 数   名: kdvSendRasCtrlMsg
功	      能: 发送RAS控制消息
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall  - 呼叫句柄
              hsRas   - RAS句柄
              msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvSendRasCtrlMsg(IN HCALL hsCall, IN HRAS hsRas, IN u16 msgType,
                      IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvSendCallCtrlMsg
功	      能: 发送呼叫控制消息
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall  - 呼叫句柄
              msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvSendCallCtrlMsg(IN HCALL hsCall,IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvSendChanCtrlMsg
功	      能: 发送信道控制消息
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsChan  - 信道句柄
              msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvSendChanCtrlMsg(IN HCHAN hsChan, IN u16 msgType,
                       IN const void* pBuf,IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvSendConfCtrlMsg
功	      能: 发送会议控制消息
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall  - 呼叫句柄
              msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvSendConfCtrlMsg(IN HCALL hsCall, IN u16 msgType,
                       IN const void* pBuf, IN u16 nBufLen, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvCheckValid
功	      能: 检查呼叫句柄的合法性
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall	- 呼叫句柄
输出参数说明：
返   回   值: FALSE - 无效
              TRUE  - 有效
====================================================================*/
PROTO_API BOOL32 kdvCheckValid(IN HCALL hsCall);

/*====================================================================
函	 数   名: kdvCheckValid
功	      能: 检查通道句柄的合法性
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsChan    - 通道句柄
输出参数说明：
返   回   值: FALSE - 无效
              TRUE  - 有效
====================================================================*/
PROTO_API BOOL32 kdvCheckValid(IN HCHAN hsChan);

/*====================================================================
函	 数   名: kdvCallSetHandle
功	      能: 设置hsCall的应用层句柄
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall - 协议栈呼叫句柄
              haCall - 应用句柄
			  bSync  - 是否同步
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvCallSetHandle(IN HCALL hsCall, IN HAPPCALL haCall, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvCallGetHandle
功	      能: 获得应用句柄
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall - 协议栈呼叫句柄              
			  bSync  - 是否同步
输出参数说明: haCall - 应用句柄
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvCallGetHandle(IN HCALL hsCall, OUT HAPPCALL* haCall, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvRasUpdateRegAliasList
功	      能: 更新本端别名
算 法 实  现: 
引用全局变量: g_hApp
输入参数说明: alias  - 别名数组
			  size	 - 别名个数              
返   回   值: 成功   - act_ok
              失败   - act_err
====================================================================*/
PROTO_API s32 kdvRasUpdateRegAliasList(IN cmAlias alias[], IN s32 size);

/*====================================================================
函	 数   名: kdvSetGKRASAddress
功	      能: 设置gk地址
算 法 实  现: 
引用全局变量: 
输入参数说明: hApp - HAPP
              tr   - GK地址              
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvSetGKRASAddress(IN HAPP hApp, IN cmTransportAddress tr, bool bSync = true );

/*====================================================================
函	 数   名: kdvGetCallParam
功	      能: 获得呼叫参数
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall	- 呼叫句柄
			  cpt		- 呼叫参数类型
			  bSync		- 是否同步
输出参数说明：pBuf		- 参数值
			  nBufLen	- 参数长度
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvGetCallParam(IN HCALL hsCall, IN CallParamType cpt, 
                    OUT void* pBuf, OUT u16 nBufLen, IN bool bSync = true);

/*====================================================================
函	 数   名: kdvIsMasterCall
功	      能: 检查是否主叫
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall    - 呼叫句柄
输出参数说明：
返   回   值: FALSE - 被叫
              TRUE  - 主叫
====================================================================*/
PROTO_API BOOL32 kdvIsMasterCall(IN HCALL hsCall);

/*====================================================================
函	 数   名: kdvIsMasterTerminal
功	      能: 检查主从决定的结果是否master
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall    - 呼叫句柄
输出参数说明：
返   回   值: FALSE - slave
              TRUE  - master
====================================================================*/
PROTO_API BOOL32 kdvIsMasterTerminal(IN HCALL hsCall);

/*====================================================================
函	 数   名: kdvGetLocalCallIPAddress
功	      能: 获取本端呼叫的真实IP
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall    - 呼叫句柄
输出参数说明：
返   回   值: 网络序的IP地址
====================================================================*/
#if ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_ANY)
PROTO_API ipAddress kdvGetLocalCallIPAddress(IN HCALL hsCall);
#elif ( RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_OLD)
PROTO_API u32 kdvGetLocalCallIPAddress(HCALL hsCall);
#endif

/*====================================================================
函	 数   名: IsAudioType
功	      能: 判断是否音频类型
算 法 实  现: 
引用全局变量: 无
输入参数说明: wPayLoadType	 - 载荷类型
返   回   值: 成功 - 大于0
              失败 - 小于0
====================================================================*/
inline BOOL32 IsAudioType(IN u16 wPayLoadType)
{
	return PayloardIsAudioType(wPayLoadType); 
}

/*====================================================================
函	 数   名: IsVideoType
功	      能: 判断是否视频类型
算 法 实  现: 
引用全局变量: 无
输入参数说明: wPayLoadType	 - 载荷类型
返   回   值: 成功 - 大于0
              失败 - 小于0
====================================================================*/
inline BOOL32 IsVideoType(IN u16 wPayLoadType)
{
	return PayloardIsVideoType(wPayLoadType);
}

/*====================================================================
函	 数   名: IsDataType
功	      能: 判断是否数据类型
算 法 实  现: 
引用全局变量: 无
输入参数说明: wPayLoadType	 - 载荷类型
返   回   值: 成功 - 大于0
              失败 - 小于0
====================================================================*/
inline BOOL32 IsDataType(IN u16 wPayLoadType)
{
	return PayloardIsDataType(wPayLoadType);
}

/* 输出有关协议栈的函数，并增加信号量保护 */
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
函	 数   名: kdvRASSetCallAddress
功	      能: 设置注册呼叫地址
算 法 实  现: 
引用全局变量: 
输入参数说明: ta   - 呼叫信令地址
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvRASSetCallAddress(IN HAPP hApp, IN cmTransportAddress tr);

/*====================================================================
函	 数   名: kdvSetlocalRASAddress
功	      能: 设置注册RAS地址
算 法 实  现: 
引用全局变量: 
输入参数说明: ta   - 本地RAS地址
返   回   值: 成功 - act_ok
              失败 - act_err
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
函	 数   名: kdvUpdateGatekeeperID
功	      能: 更新GatekeeperID
算 法 实  现: 
引用全局变量: 
输入参数说明: tGKID   - gatekeeperid
返   回   值: 成功 - act_ok
失败 - act_err
====================================================================*/
PROTO_API s32 kdvUpdateGatekeeperID(IN HAPP hApp, IN cmAlias tGKID);

//用于加密
PROTO_API BOOL32 GetDesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);
PROTO_API BOOL32 GetAesDHKey(HCALL hsCall, u8 **pBuf, s32 *pnBits);

//发送会议级联控制消息
PROTO_API int kdvSendMMcuCtrlMsg(HCHAN hsChan,u16 msgType,const void* pBuf,u16 nBufLen,bool bSync = true);

/**说明***********************************************************************
*
1.关于双向逻辑通道(单独协议通道)(I incoming, O out )
> 逻辑通道冲突时， master 终端拒绝incoming channel
> I 方，方主动tcp connect时，ack消息不需带单独协议通道监听地址
> O 方，当ack带有单独协议通道监听地址，且I没有主动tcp connect时,发起tcp connect
2.级联通道
>h_chan_open,h_chan_openAck 只需填写payload, m_tRtp.ip.
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

//设置IRR信息，用于不依赖HCALL的场合，测试用。
PROTO_API s32 kdvSetRasIRR(HRAS hsRas, TIRRINFO* ptIRRInfo, bool bSync);

//消息体的主机序和网络序的转换
PROTO_API s32 kdvH323Adapterhton(u16 msgType, void* pBuf, u16 nBufLen, BOOL32 bhton);

//设置H323TOS值
PROTO_API s32 kdvSetH323TOS(IN s32 nTOS, IN bool bSync = true);
//获取H323TOS值
PROTO_API s32 kdvGetH323TOS();

//设置远遥TOS值, 函数体在kdvdatanet库中定义
// API s32 kdvSetDataTOS(s32 nTOS);
// API s32 kdvGetDataTOS();

PROTO_API s8* GetPeerVersionID(HCALL hsCall);
PROTO_API s8* GetPeerProductID(HCALL hsCall);
PROTO_API BOOL32 IsPeerSupportNewG7221c(HCALL hsCall);  //对端是否支持正确字节序的G7221C音频码流

PROTO_API void KdvSetIsH460GW(BOOL32 bIsGw);

PROTO_API int KdvSendTpktPinhole(HCALL hsCall, cmTpktChanHandleType type, BOOL32 bSync = TRUE);
PROTO_API void KdvSetH460Config(BOOL32 bSupportH460, BOOL32 bMediaTraversalServer, BOOL32 bSupportTransMultiMedia);
PROTO_API void KdvSetCallApplicationHandle(HCALL hsCall, void* haCall);

// 设置本地是否为UTF8编码
PROTO_EXTERN_API void kdvSetLocalIsUTF8(BOOL32 bIsUtf8);


/*====================================================================
函	 数   名: kdvSetKDV323
功	      能: 更新协议栈发送协议格式
算 法 实  现: 
引用全局变量: 
输入参数说明: bIsKDV323
			  TRUE - 发送格式为KD H.323
			  FALSE - 发送的格式为标准H.323
返   回   值: 成功 - act_ok
			  失败 - act_err
====================================================================*/
PROTO_EXTERN_API s32 kdvSetKDV323(IN BOOL32 bIsKDV323);

/*====================================================================
函	 数   名: kdvEnableQuantumCall
功	      能: 更新协议栈发送协议格式
算 法 实  现: 
引用全局变量: 
输入参数说明: bIsQuantumCall
			  TRUE  - Quantum Call
			  FALSE - Common  Call
返   回   值: 成功 - act_ok
			  失败 - act_err
====================================================================*/
PROTO_EXTERN_API s32 kdvEnableQuantumCall(IN BOOL32 bIsQuantumCall);

/*====================================================================
函	 数   名: kdv323std
功	      能: 打印协议栈发送协议格式
算 法 实  现: 
引用全局变量: 
输入参数说明: 

返   回   值: 成功 - TRUE
             失败 - FALSE
====================================================================*/
PROTO_EXTERN_API BOOL32 kdv323std();

//add by zhanghb for kdvp2.0 MT SendNSM
/*====================================================================
函	 数   名: kdvManualRASSendNSM
功	      能: MT为手动RAS时发送非标消息,仅用于手动RAS
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall  - 呼叫句柄
              hsRas   - RAS句柄
              msgType - 消息类型
			  pBuf    - 参数缓冲区
			  nBufLen - 参数长度
			  ptDstNetAddr - 目的地址
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvManualRASSendNSM(IN HCALL hsCall,IN HRAS hsRas,IN u16 msgType,
						IN const void* pBuf,IN u16 nBufLen,IN TNETADDR * ptDstNetAddr,IN bool bSync = true);
//end add 
/*====================================================================
函	 数   名: kdvSetH460Feature
功	      能: 设置支持460特性
算 法 实  现: 
引用全局变量: 
输入参数说明: bSupportH460   
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvSetH460Feature(IN BOOL32 bSupportH460);

/*====================================================================
函	 数   名: kdvCloseCall
功	      能: 关闭呼叫句柄
算 法 实  现: 
引用全局变量: 无
输 入 参  数: hCall -   呼叫句柄
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32 kdvCloseCall( IN HCALL hCall, IN bool bSync = true );

/*====================================================================
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall    - 呼叫句柄
输出参数说明：
返   回   值: 网络序的IP地址
====================================================================*/
PROTO_API u32 kdvGetLocalTCPAddress(HCALL hsCall, TNETADDR *tAddress );

/*====================================================================
函	 数   名: kdvConnectMMCU
功	      能: 连接MCU
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall    - 呼叫句柄
              hsChan    - 通道句柄
              tDstAddr  - 连接地址
输出参数说明：
返   回   值: 成功 - act_ok
              失败 - act_err
====================================================================*/
PROTO_API s32	 kdvConnectMMCU(IN HCALL hsCall, IN HCHAN hsChan, IN  TNETADDR tDstAddr);


/*====================================================================
函	 数   名: kdvGetH225Ver
功	      能: 获取H225版本号
算 法 实  现: 
引用全局变量: 无
输入参数说明: hsCall    - 呼叫句柄
输出参数说明：
返   回   值: 
====================================================================*/
PROTO_API u32	 kdvGetH225Ver(IN HCALL hsCall);

// [12/3/2008 zhangzhihua]add.手动删除远遥所占资源.
PROTO_API s32 KdvH323FreeFeccRcvSession(IN HCHAN hsChan);
PROTO_API s32 KdvH323FreeFeccSendSession(IN HCHAN hsChan);

#ifdef _ENABLE_QUANTUM_PROJECT_
PROTO_EXTERN_API void QtInfo();
PROTO_EXTERN_API void QtCallAutoHangUp(BOOL32 bAutoHangUp);

/*====================================================================
函	 数   名: kdvSetQuantumLevel
功	      能: 设置呼叫量子加密等级
算 法 实  现: 
引用全局变量: 
输入参数说明: haCall			- 本端呼叫应用层句柄
			  hsCall			- 本端呼叫协议层句柄（调用kdvCreateNewCall生成的句柄）
			  tQtCallParam      - 需要添加本端呼叫加密等级和对端的别名信息
返   回   值: 成功 - act_ok
失败 - act_err
====================================================================*/
PROTO_API s32 kdvSetQuantumLevel(IN HAPPCALL haCall, IN HCALL hsCall, IN TQtCallParam &tQtCallParam);

/*====================================================================
函	 数   名: kdvAdapterQuantumInit
功	      能: 设置本端量子加密初始化参数（若有配置变更，就需调该接口）
算 法 实  现: 
引用全局变量: 
输入参数说明: tQuantumInitParam			- 本端量子加密初始化参数
			 
返   回   值: 成功 - TRUE
失败 - FALSE
====================================================================*/
PROTO_API BOOL32 kdvAdapterQuantumInit(TQtInitParam &tQuantumInitParam);
#endif

#endif //_H323ADAPTER_H
