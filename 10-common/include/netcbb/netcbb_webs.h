/******************************************************************************
模块名  ： WEB SERVER
文件名  ： boardwebs.h
相关文件：
文件实现功能：WEB-SERVER模块对外提供的宏定义头文件
作者    ：zhanka
版本    ：1.0.0.0.0
---------------------------------------------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
08/17/2007  1.0         zhanka      创建
******************************************************************************/
#ifndef _NETCBB_WEBS_H_
#define NETCBB_WEBS_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#define NET_WEBS_ENABLE 1
#define NET_WEBS_DISABLE 2

#define NET_WEBS_INSPECT_ENABLE 3
#define NET_WEBS_INSPECT_DISABLE 4

#define NET_WEBS_ERR_BASE 100
//返回值类型
#define NET_WEBS_PORT_ERR   NET_WEBS_ERR_BASE+1	//端口绑定出错
/*================================
函数名：NetWebsEnable
功能：启动或停止web server
算法实现：（可选项）
引用全局变量：
输入参数说明：dwEnable :BRD_WEBS_ENABLE 启动
                       :BRD_WEBS_DISABLE 停止
返回值说明： OK/ERROR
备注: port 值只在使用简化版本的httpd有效，在ligthttpd中无效.
==================================*/
s32 NetWebsEnable(s32 port);

/*================================
函数名：NetWebsEnable
功能：启动或停止web server
算法实现：（可选项）
引用全局变量：
输入参数说明：dwEnable :BRD_WEBS_ENABLE 启动
                       :BRD_WEBS_DISABLE 停止
返回值说明： OK/ERROR
==================================*/
s32 NetWebsDisable(void);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* _NETCBB_WEBS_H_ */

