#ifndef _NETCBB_INTERFACE_H_
#define _NETCBB_INTERFACE_H_

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

/*以太网相关的结构定义*/
/* 以太网参数结构 */
typedef struct{
    u32 dwIpAdrs;/*网络字节序*/
    u32 dwIpMask; /*网络字节序*/
    u8  byMacAdrs[6];
}TNetEthParam;

/* 以太网mac地址结构*/
typedef struct{
    u8  byMacAdrs[6];
}TNetEthMac;

/* 以太网参数结构 */
typedef struct{
    u32 dwIpNum;/*有效的IP地址数*/
    TNetEthParam atNetEthParam[IP_ADDR_MAX_NUM];/*存放IP地址等信息的数组*/
}TNetEthParamAll;

/* 单个路由参数结构 */
typedef struct{
    u32 byEthId;		 /*网口id*/	
    u32 dwDesIpNet;      /* 目的子网，网络字节序	*/
    u32 dwDesIpMask;     /* 掩码，网络字节序	*/
    u32 dwGwIpAdrs;      /* 网关ip地址，网络字节序*/
    u32 dwRoutePri;		 /* 路由优先级(1-255)，默认为0*/
}TNetIpRouteParam;

/*多个路由参数结构 */
typedef struct{
    u32 dwIpRouteNum;    /* 得到的实际路由个数 */
    TNetIpRouteParam tNetIpRouteParam[IP_ROUTE_MAX_NUM];
}TNetAllIpRouteInfo;


#define NETCBB_IP_CONFLICT	1
#define NETCBB_MAC_CONFLICT	2
/*IP地址冲突回调函数类型定义*/
typedef void (*TIpConflictCallBack)(u32 dwType, u8 *pbyMacAddr, u32 dwIpAdrs);

/*TPingCallBack回调的返回值，对应参数为nResult*/
#define PING_REPLY     0
#define PING_TIMEOUT   1   /*暂不支持*/
#define PING_ERROR     2
/*NetPing接口传入参数结构体*/
typedef struct{
    s32 nPktSize;/*要ping的数据报的大小，以字节为单位*/
    s32 nTimeOut;/*ping的超时值，以秒为单位*/
    s32 nTtl;/*TTL值*/
}TPingOpt;

/*Ping回调函数类型定义*/
/*参数说明：
只支持nResult参数，该值提供ping的返回值.其余的值为0
*/
typedef int(*TPingCallBack)(s32 nResult,s32 nTtl,s32 nTripTime,s32 nUserID,s32 nErrType,s32 nErrCode);

/*================================
函数名：NetGetEthParam
功能：读取以太网参数，含ip、mask、mac
算法实现：（可选项）
引用全局变量：
输入参数说明：  byEthId --- 以太网ID号（0~x）;
                TNetEthParam *ptNetEthParam --- 存放以太网信息的结构指针。
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
==================================*/
s32 NetGetEthParam(u32 byEthId, TNetEthParam *ptNetEthParam);

/*================================
函数名：NetGetEthMac
功能：读取以太网mac地址
算法实现：（可选项）
引用全局变量：
输入参数说明： byEthId --- 以太网ID号（0~x）;
                TNetEthMac *ptNetEthMac  --- 存放以太网信息的结构指针。
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
备注: 该api不提供支持，和NetGetEthParam有重合地方。
==================================*/
s32 NetGetEthMac(u32 byEthId, TNetEthMac *ptNetEthMac);

/*================================
函数名：NetGetEthParam
功能：获取一个网口上所有的以太网参数，多个IP地址的情况
算法实现：（可选项）
引用全局变量：
输入参数说明：  byEthId --- 以太网ID号（0~x）;
                NetEthParamAll *ptNetEthParamAll --- 存放以太网信息的结构指针。
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
==================================*/
s32 NetGetEthParamAll(u32 byEthId, TNetEthParamAll *ptNetEthParamAll);


/*================================

函数名：NetGetEthParamSecIP
功能：获取一个网口上所有第二IP地址
算法实现：（可选项）
引用全局变量：
输入参数说明：  byEthId --- 以太网ID号（0~x）;
                NetEthParamAll *ptNetEthParamAll --- 存放以太网信息的结构指针，此结构是
                用于返回第二IP地址的，返回的地址个数由dwIpNum指定，结构中的
                atNetEthParam数组成员只由IP 和Mask有效, Mac 地址没有效
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
备注:不提供支持，和NetGetEthParamAll重复，读取NetGetEthParamAll的第2、3数组可以获取到对应的ip
==================================*/
s32 NetGetEthParamSecIP(u32 byEthId, TNetEthParamAll *ptNetEthParamAll);


/*================================
函数名：NetSetEthParam
功能：设置以太网参数
算法实现：（可选项）
引用全局变量：
输入参数说明：  byEthId：以太网的编号（0 ~ X）X视不同板子而定；
                byIpOrMac：为设置命令选择(见Netcbb_def.h中相关的宏定义),可以
                                     设置主IP,第二IP和Mac.
                                       Net_SET_IP_AND_MASK         1       设置IP地址和子网掩码
                                       Net_SET_MAC_ADDR            2       设置MAC地址(设mac功能不支持，无实际意义)
                                       Net_SET_ETH_ALL_PARAM       3       设置以太网的IP地址、子网掩码和MAC地址(不支持)
                                       Net_SET_ETH_SEC_IP          4       设置以太网第二IP 地址
                ptNetEthParam：指向存放设定值的TNetEthParam数据结构的指针
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
==================================*/
s32 NetSetEthParam(u32 byEthId, u32 byIpOrMac, TNetEthParam *ptNetEthParam);


/*================================
函数名：NetDelEthParamSecIP
功能：删除第二IP地址
算法实现：（可选项）
引用全局变量：
输入参数说明：  byEthId：以太网的编号（0 ~ X）X视不同板子而定；
                ptNetEthParam：指向存放设定值的TNetEthParam数据结构的指针
                                           结构中只有IP和 Mask有效.
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
备注 :不提供支持，和NetDelEthParamIPAndMask重复。
==================================*/
s32 NetDelEthParamSecIP(u32 byEthId, TNetEthParam *ptNetEthParam);


/*================================
函数名：NetDelEthParamIPAndMask
功能：删除指定 IP地址
算法实现：（可选项）
引用全局变量：
输入参数说明：  byEthId：以太网的编号（0 ~ X）X视不同板子而定；               
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
==================================*/
s32 NetDelEthParamIPAndMask(u32 byEthId, TNetEthParam *ptNetEthParam);


/*================================
函数名：NetDelEthParam
功能：删除指定的以太网接口
算法实现：（可选项）
引用全局变量：
输入参数说明：  byEthId：以太网的编号（0 ~ X）X视不同板子而定；
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
注意：在Linux下，一个网口可以配置多个IP地址，该接口会删除该接口上的所有IP地址。
==================================*/
s32 NetDelEthParam(u32 byEthId);


/*================================
函数名：NetSetDefGateway
功能：设置默认网关ip
算法实现：（可选项）
引用全局变量：
输入参数说明：  dwGateway：默认网关ip地址，长整型，网络序
返回值说明： 出错返回ERROR；成功返回OK。ERROR = -1 ; OK = 0
==================================*/
s32 NetSetDefGateway(u32 byEthId, u32 dwGateway);

/*================================
函数名：NetGetDefGateway
功能：获取默认网关ip
算法实现：（可选项）
引用全局变量：
输入参数说明： 无
返回值说明： 错误返回ERROR=-1；成功返回OK=0
==================================*/
 s32 NetGetDefGateway(u32 *pdwGateway);

/*================================
函数名：NetDelDefGateway
功能：删除默认网关ip
算法实现：（可选项）
引用全局变量：
输入参数说明： 无
返回值说明： 错误返回ERROR；成功返回OK ERROR = -1 ; OK = 0
==================================*/
s32 NetDelDefGateway(void);

/*================================
函数名：NetGetNextHopIpAddr
功能：获取通往指定ip的第一跳路由ip地址
算法实现：（可选项）
引用全局变量：
输入参数说明：dwDstIpAddr：目的ip地址，长整型，网络序
		    dwDstMask：目的掩码，长整型，网络序
返回值说明： 成功返回第一跳路由ip地址，长整型
备注 : 暂不支持，意义不大，实现较麻烦。完全可以由NetPing 来判断地址是否可以到达。
==================================*/
u32 NetGetNextHopIpAddr(u32 dwDstIpAddr,u32 dwDstMask);

/*================================
函数名：NetAddOneIpRoute
功能：增加一条路
算法实现：（可选项）
引用全局变量：
输入参数说明：ptNetIpRouteParam：指向存放路由信息的TNetIpRouteParam结构指针
返回值说明： 错误返回ERROR；成功返回OK. ERROR = -1 ; OK = 0
==================================*/
s32 NetAddOneIpRoute(u32 byEthId, TNetIpRouteParam *ptNetIpRouteParam);

/*================================
函数名：NetDelOneIpRoute
功能：删除一条路
算法实现：（可选项）
引用全局变量：
输入参数说明：ptNetIpRouteParam：指向存放路由信息的TNetIpRouteParam结构指针
返回值说明： 错误返回ERROR；成功返回OK
==================================*/
s32 NetDelOneIpRoute(u32 byEthId, TNetIpRouteParam *ptNetIpRouteParam);

/*================================
函数名：NetGetAllIpRoute
功能：读取所有路由信息
算法实现：（可选项）
引用全局变量：
输入参数说明：ptNetAllIpRouteInfo：指向存放返回路由信息的TNetAllIpRouteInfo结构指针
返回值说明： 错误返回ERROR；成功返回OK. ERROR = -1 ; OK = 0
==================================*/
s32 NetGetAllIpRoute(TNetAllIpRouteInfo *ptNetAllIpRouteInfo);

/*================================
函数名：NetIpConflictCallBackReg
功能：注册ip地址冲突时回调函数,当设备的IP地址和外部设备冲突时，会调用该函数通知业务程序
算法实现：（可选项）
引用全局变量：
输入参数说明：ptFunc：执行业务程序注册的回调函数指针
返回值说明： 错误返回ERROR；成功返回OK. ERROR = -1 ; OK = 0
==================================*/
s32 NetIpConflictCallBackReg (TIpConflictCallBack  ptFunc);

/*================================
函数名：NetIpOnceConflicted
功能：查询系统是否发生过ip地址冲突
算法实现：（可选项）
引用全局变量：
输入参数说明：无
返回值说明： TRUE or FALSE
==================================*/
BOOL32 NetIpOnceConflicted (void);

/*================================
函数名：NetPing
功能：以太网ping接口
算法实现：（可选项）
引用全局变量：
输入参数说明：pchDestIP:Ping的目的IP地址，为点分十进制
              ptPingOpt：Ping的参数结构体指针
              nUserID:用户ID标志，用户区分不同的用户调用
              ptCallBackFunc:Ping结果的回调函数
返回值说明： TRUE--传入的参数合法，该函数调用成功，但是否ping通需要用户注册的回调函数来判断
             FALSE--传入的参数非法，该函数调用失败
==================================*/
BOOL32 NetPing(char* pchDestIP,TPingOpt* ptPingOpt,s32 nUserID,TPingCallBack ptCallBackFunc);

/*================================
函数名：NetSetDscp
功能：设置ip包头dscp值(0-63)
算法实现：（可选项）
引用全局变量：
输入参数说明：nSockfd ; 要设置的套接字描述符
              byDscp ; 要设置的dscp值(0-63)
返回值说明： OK/ERROR ERROR = -1 ; OK = 0
             OK 成功; ERROR 失败
==================================*/
s32 NetSetDscp(s32 nSockfd, u8 byDscp);

/*================================
函数名：NetInterfaceShutdown
功能：关闭所选接口
算法实现：（可选项）
引用全局变量：
输入参数说明：byEthId：以太网的编号		

返回值说明： OK/ERROR ERROR = -1 ; OK = 0
==================================*/
s32 NetInterfaceShutdown(u32 byEthId);

/*================================
函数名：NetInterfaceNoShutdown
功能：打开所选接口
算法实现：（可选项）
引用全局变量：
输入参数说明：byEthId：以太网的编号			

返回值说明： OK/ERROR ERROR = -1 ; OK = 0
==================================*/
s32 NetInterfaceNoShutdown(u32 byEthId);

/*================================
函数名：NetCheckTheSameNet
功能：校验网络参数
算法实现：（可选项）
引用全局变量：
输入参数说明：dwIpAddr   :  ip 地址
              dwMask     :  掩码
              dwGateway  :  网关

返回值说明： OK : 校验成功, 在同一个网段
             NET_NOT_THE_SAME_NET  : 不在同一个网段
             NET_INVALID_PARAMETER : 参数本身错误
==================================*/
s32 NetCheckTheSameNet(u32 dwIpAddr, u32 dwMask,u32 dwGateway);

/*================================
函数名：NetGetEthNum
功能：检测网卡数量
算法实现：（可选项）
引用全局变量：
输入参数说明： *pnEthNum: 指向需要获取的端口号
返回值说明： OK                成功
                                     ERROR          失败
==================================*/
s32 NetGetEthNum(s32 *pnEthNum);
#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /*_NETCBB_INTERFACE_H_*/
