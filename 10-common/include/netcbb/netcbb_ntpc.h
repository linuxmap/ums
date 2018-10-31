/******************************************************************************
模块名  ： NTP-CLIENT
文件名  ： ntpc.h
相关文件：
文件实现功能：NTP-CLIENT模块对外提供的宏定义头文件
作者    ：王俊华
版本    ：1.0.0.0.0
---------------------------------------------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
07/14/2006  1.0         王俊华      创建
******************************************************************************/
#ifndef _NETCBB_NTPC_H_
#define _NETCBB_NTPC_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */


/*宏定义*/

/*请求与NTP-Servr进行时间同步的时间间隔的最小值*/
#define NETCBB_NTPC_INTERVAL_MIN                        (u32)5

/*请求与NTP-Servr进行时间同步的时间间隔的最大值*/
#define NETCBB_NTPC_INTERVAL_MAX                        (u32)1024
 

/*NTP中调用主动向NTP-Server同步时间时回调函数的消息码基址*/
#define NETCBB_NTPC_MSG_BASE			                (u32)30000

/*向NTP-Server同步时间校时成功，消息体：无*/
#define NETCBB_NTPC_SYNC_TIME_SUCCESS_MSG		        (u32)(NETCBB_NTPC_MSG_BASE + 1)

/*向NTP-Server同步时间校时失败，消息体：无*/
#define NETCBB_NTPC_SYNC_TIME_FAILED_MSG				(u32)(NETCBB_NTPC_MSG_BASE + 2)

/*回调函数类型定义*/

/*================================
函数名：NetCbbNTPCSyncTimeCallBack
功能：调用主同向NTP-Server同步系统时间时，通知用户操作结果的回调函数
算法实现：（可选项）
引用全局变量：
输入参数说明：dwMsgID：事件类型，见上面的消息类型定义
		      pMsg：与该事件类型相匹配的消息内容，目前都设置为NULL，以后可以
			  扩展
返回值说明： 暂时都定为0，以后可以扩展
==================================*/
typedef int(*NetCbbNtpcSyncTimeCallBack)(u32 dwMsgID ,void* pMsg);


/*函数接口定义*/

/*================================
函数名：NetCbbNTPCStart
功能：开启NTP-Client端功能
算法实现：（可选项）
引用全局变量：
输入参数说明：dwServerIp： NTP-Server的IP地址，网络字节序
		      dwSyncTimeInterval：与NTP-Server进行时间同步的时间间隔，以秒为单
              位，范围：64s~1024s，开启该功能之后，底层会按照用户设置的时间间隔，
              每隔一段时间便向NTP-Server同步系统时间并设置到本地系统中
返回值说明： OK/ERROR
==================================*/
s32 NetCbbNtpcStart(u32  dwServerIp,  u32  dwSyncTimeInterval, NetCbbNtpcSyncTimeCallBack  ptCallBack);

/*================================
函数名：NetCbbNTPCStop
功能：关闭NTP-Client端功能
算法实现：（可选项）
引用全局变量：
输入参数说明：无
返回值说明： OK/ERROR
备注: 不提供支持
==================================*/
s32 NetCbbNtpcStop (void);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /*_NETCBB_NTP_H_*/
