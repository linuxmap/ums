/*************************************************************************
    > File Name: Netcbb_serv.h
    > Author: zengmengqiu
    > Mail: zengmengqiu@kedacom.com 
    > Created Time: Thu 19 Jun 2014 09:38:52 AM CST
 ************************************************************************/
#ifndef _NETCBB_SERV_H
#define _NETCBB_SERV_H

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#define NETSERVICE_TELNETD	"telnetd" 	//宏定义telnetd  
#define NETSERVICE_FTPD	    "ftpd"  	//宏定义ftpd
#define NETSERVICE_TFTPD	"tftpd"		//宏定义tftpd
#define NETSERVICE_HTTPD	"httpd"		//宏定义httpd

#define NETPROTO_TCP "tcp"
#define NETPROTO_UDP "udp"


typedef struct {
	s8  *pchServName;//服务名
	u16  wPort;//服务端口号
	s8  *pchProto;//协议类型
	s8  *pchArgPath;
}TServInfo;


/*函数接口定义*/
/*================================
函数名：NetServiceStart
功能：开启服务功能
算法实现：（可选项）
引用全局变量：
输入参数说明：pchServName：服务名
		                          ptParaM：指向TServInfo 的结构体指针
返回值说明：      OK/ERROR
==================================*/
s32 NetServiceStart(s8 *pchServName, TServInfo * ptParaM);

/*================================
函数名：NetServiceStop
功能：关闭服务功能
算法实现：（可选项）
引用全局变量：
输入参数说明：
返回值说明： OK/ERROR
==================================*/
s32 NetServiceStop(s8 *pchServName);

#ifdef __cplusplus 
} 
#endif /* __cplusplus */
#endif