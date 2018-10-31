/*============================================================================*\
  模块名：ENFC
  文件名：api_enfc.h
  功能：
          DCB向外部提供的调用接口有：启动模块、关闭模块、一次检测发起、流控发起/
          重置、流控停止、触发流控计算、流控算法可替换定制、负载均衡算法可替换定制、
          获取指定通道组的负载量及全局负载比、设置指定通道组的负载量及全局负载比、
          设置全局默认码率、设置接口可用带宽。

  作者：  高祺
  版本：  0.5
  修改记录：
	日期			版本		修改人		走读人		修改内容
	1/5/2007		0.5			高祺							初稿
	1/30/2007		1.0			高祺							修改部分接口
	7/16/2007		1.1			高祺							修改接口dcb_flowctrl_trigger
\*============================================================================*/
// File Name: api_enfc.h

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------
#ifndef _INCLUDE_ENFC_H_
# define _INCLUDE_ENFC_H_

#include "kdvtype.h"
// ----------------------------------------------------------------------------
// Constants and Defines
// ----------------------------------------------------------------------------
//# define MODULE "ENFC"	//Module Name

enum
{
    DEFAULT_ALG,
    WIRED_ALG,
    WIRELESS_ALG
};

// Error codes
// ...

# ifdef __cplusplus
extern "C" {
# endif

// ----------------------------------------------------------------------------
// APIs
// ----------------------------------------------------------------------------
// 1.1              启动ENFC
// ----------------------------------------------------------------------------
// 接口形式：       
//                                  s32 dcb_start(u32 ctrl_port,
//                                                     u32 start_data_port,
//                                                     u32 extra_data_port_num,
//                                                     u32 start_inner_port,
//                                                     u32 extra_inner_port_num
//                                                     );
// 描述：           在上层用户要求启动时注册、加载，并在本地所有接口的指定端口上
//                  侦听带宽检测请求(信令)，如不指定侦听端口，则在缺省的端口上侦听；
//                  其次，本模块将根据指定起始端口号和端口数，在后续可能的检测发起中
//                  选取指定范围内可用的端口进行检测流量接收(数据)；
//                  第三，本模块也将启动全局负载平衡子模块、获取各接口的物理带宽
//                  并设置相关参数，申请必要的资源
// 参数：           u32 ctrl_port，带宽检测请求侦听端口；
//                            u32 start_data_port，带宽检测数据接收端口可用范围起始值；
//                            u32 extra_data_port_num，带宽检测数据接收端口额外可用数量，0表示只有
//                                           起始值可用，1表示可用端口范围为[start_data_port, start_data_port+1]，
//                                           依此类推
//                            u32 start_inner_port，WIN32环境下内部使用端口可用范围起始值；
//                            u32 extra_inner_port_num，WIN32环境下内部使用端口额外可用数量，0表示只有
//                                           起始值可用，1表示可用端口范围为[start_inner_port, start_inner_port+1]，
//                                           依此类推
// 返回值：         0表示启动成功，-1表示启动失败
// 编号：
s32 dcb_start(u32 ctrl_port, u32 start_data_port, u32 extra_data_port_num, u32 start_inner_port, u32 extra_inner_port_num);

// ----------------------------------------------------------------------------
// 1.2              关闭ENFC
// ----------------------------------------------------------------------------
// 接口形式：       s32 dcb_stop(void);
// 描述：           关闭所有接口上对带宽检测报文的侦听；同时，关闭全局负载平衡
//                  子模块和各流控子模块，释放资源
// 参数：           无
// 返回值：         0表示关闭成功，-1表示关闭失败
// 编号：
s32 dcb_stop(void);

// ----------------------------------------------------------------------------
// 1.3              一次检测发起
// ----------------------------------------------------------------------------
// 接口形式：       s32 dcb_detect(u32 peeraddr,
//                                                       u32 port,
//                                                       u32 init_dt_bw,
//                                                       u32 dtcb_context,
//                                                       void (*detect_callback)(u32 peeraddr, u32 sgstrate, u32 dtcb_context)
//                                                       );
// 描述：           检测从本端到指定地址的全程可用带宽
// 参数：           u32 peeraddr，对端网络地址，用于标识通道组及发起检测；
//                  u32 port，对端检测侦听端口；
//                  u32 init_dt_bw，检测初始建议发送码率，单位bit/s；
//                  u32 dtcb_context，检测回调上下文参数，由调用者传入，不作任何改变传出；
//                  void (*detect_callback)(u32 peeraddr, u32 sgstrate, u32 dtcb_context)，调用者提供的回调函数指针，
//                                        检测子线程将通过调用者提供的该函数通知
//                                        调用者计算结果
// 返回值：         0表示发起成功，-1表示发起失败
// 编号：
s32 dcb_detect(u32 peeraddr, u32 port, u32 init_dt_bw, u32 dtcb_context, void(*detect_callback)(u32 peeraddr, u32 sgstrate, u32 dtcb_context));

// ----------------------------------------------------------------------------
// 1.4              流控发起/重置
// ----------------------------------------------------------------------------
// 接口形式：       s32 dcb_flowctrl_set(u32 peeraddr,
//                                       u32 ci,
//                                       u32 tcb_context,
//                                       void (*timeout_callback)(u32 peeraddr, u32 time_stamp, u32 tcb_context),
//                                       u32 ccb_context,
//                                       void (*calc_callback)(u32 peeraddr, u32 sgstrate, u32 ccb_context)
//                                       );
// 描述：           按指定时间间隔对去往指定对端的通道组启动/重置自动流量控制。
//                  启动流控（通道组标识参数未被引用过）时将创建相应的线程；
//                  重置流控（通道组标识参数已被引用但定时器间隔改变）时将改变
//                  定时器大小
// 参数：           u32 peeraddr，对端网络地址，用于标识通道组；
//                  u32 ci，流控间隔，以毫秒计，合理取值范围为<1000, 60000>，为较精确地
//                                      跟踪码流实际收发情况，该值建议设置范围为<1000, 5000>；
//                  u32 tcb_context，超时回调上下文参数，由调用者传入，不作任何改变传出；
//                  void (*timeout_callback)(u32 peeraddr, u32 time_stamp, u32 tcb_context)，调用者提供的回调函数
//                                      指针，流控子线程将通过调用者提供的该函数通知调用者
//                                      定时器到期；
//                  u32 ccb_context，流控计算回调上下文参数，由调用者传入，不作任何改变传出；
//                  void (*calc_callback)(u32 peeraddr, u32 sgstrate, u32 ccb_context)，调用者提供的回调函数指针，
//                                      流控子线程将通过调用者提供的该函数通知调用者计算结果
// 返回值：         0表示创建流控子线程或重置流控间隔成功，-1表示启动流控（创建
//                  流控子线程）或重置流控间隔失败
// 编号：
s32 dcb_flowctrl_set(u32 peeraddr, u32 ci, u32 tcb_context, void(*timeout_callback)(u32 peeraddr, u32 time_stamp, u32 tcb_context), u32 ccb_context, void(*calc_callback)(u32 peeraddr, u32 sgstrate, u32 ccb_context));

// ----------------------------------------------------------------------------
// 1.5              流控停止
// ----------------------------------------------------------------------------
// 接口形式：       s32 dcb_flowctrl_deset(u32 peeraddr);
// 描述：           关闭对去往指定对端的通道组的流量控制
// 参数：           u32 peeraddr，对端网络地址字符串，用于标识通道组
// 返回值：         0表示关闭流控子线程成功，-1表示关闭流控子线程失败
// 编号：
s32 dcb_flowctrl_deset(u32 peeraddr);

// ----------------------------------------------------------------------------
// 1.6              触发流控计算
// ----------------------------------------------------------------------------
// 接口形式：       s32 dcb_flowctrl_trigger(u32 peeraddr,
//                                           u32 pktsize,
//                                           u32 pktnum,
//                                           u64 t1,
//                                           u64 t2,
//                                           u64 t3,
//                                           u64 t4,
//                                           double lossrate
//                                           );
// 描述：           对去往指定对端的通道组的流量，根据其监测统计参数，计算建议
//                  发送码率并返回给调用者
// 参数：           u32 peeraddr，对端网络地址，用于标识通道组；
//                  u32 pktsize，报文数据载荷大小（不包括UDP/IP首部，仅包括RTP首部及数据）；
//                  u32 pktnum，流控间隔期报文发送数量(实际计算时可以用接收端收包数代替)；
//                  u64 t1~t4，实测RTCP报文自发送端出发/接收端接收/接收端返回/发送端接收
//                               4个时间点的UTC时间，以微秒计；
//                  double lossrate，实际统计报文丢失率
// 返回值：         0表示调用成功，-1表示调用失败；真正计算出的建议发送码率将
//                  通过dcb_flowctrl_set中注册的回调函数通知调用者
// 编号：
s32 dcb_flowctrl_trigger(u32 peeraddr, u32 pktsize, u32 pktnum, u64 t1, u64 t2, u64 t3, u64 t4, double lossrate);

// ----------------------------------------------------------------------------
// 1.7              设置全局默认码率
// ----------------------------------------------------------------------------
// 接口形式：       s32 dcb_if_def_rate_set(u32 if_index,
//                                           u32 rate
//                                           );
// 描述：           设置指定接口的全局默认码率--对于指定出接口的所有通道组，如
//                  不执行发送前检测，要求按照某个指定的码率开始码流发送
// 参数：           u32 if_index，接口索引，接口号；
//                  u32 rate，默认发送速率，单位为bit/s
// 返回值：         0表示成功设置，-1表示设置失败
// 编号：
//s32 dcb_if_def_rate_set(u32 if_index, u32 rate);

// ----------------------------------------------------------------------------
// 1.8              设置接口可用带宽
// ----------------------------------------------------------------------------
// 接口形式：       s32 dcb_if_avl_bw_set(u32 if_index,
//                                           u32 bw
//                                           );
// 描述：           设置指定接口的总可用带宽--通过物理方法获取的值可能是错误的、
//                  有误导的--以便于发起检测和负载均衡计算
// 参数：           u32 if_index，接口索引，接口号；
//                  u32 bw，总可用带宽，单位为bit/s
// 返回值：         0表示成功设置，-1表示设置失败
// 编号：
//s32 dcb_if_avl_bw_set(u32 if_index, u32 bw);

//// ----------------------------------------------------------------------------
//// 1.9              流控算法可替换定制
//// ----------------------------------------------------------------------------
//// 接口形式：       s32 dcb_fc_alg_set(u32 peeraddr,
////                                        u32 fc_alg_index,
////                                        …);
//// 描述：           指定应用于从本端到某指定远端的通道组的流控算法及其调节因子
//// 参数：           u32 peeraddr，对端网络地址，用于标识通道组；
////                  u32 fc_alg_index，流控算法全局索引；
////                  …，其它可变参数
//// 返回值：         0表示替换定制成功，-1表示替换定制失败
//// 编号：
//s32 dcb_fc_alg_set(u32 peeraddr, u32 fc_alg_index, …);

//// ----------------------------------------------------------------------------
//// 1.10             负载均衡算法可替换定制
//// ----------------------------------------------------------------------------
//// 接口形式：       s32 dcb_lb_alg_set(u32 lb_alg_index,
////                                        …);
//// 描述：           指定全局负载均衡算法及其调节因子
//// 参数：           u32 lb_alg_index，负载均衡算法全局索引；
////                  …，其它可变参数
//// 返回值：         0表示替换定制成功，-1表示替换定制失败
//// 编号：
//s32 dcb_lb_alg_set(u32 lb_alg_index, …);

//// ----------------------------------------------------------------------------
//// 1.11             获取指定通道组的负载量及全局负载比
//// ----------------------------------------------------------------------------
//// 接口形式：       s32 dcb_loadblc_get(u32 peeraddr,
////                                        struct load_proportion *lp
////                                        );
//// 描述：           获取指定通道组的负载量及全局负载比
//// 参数：           u32 peeraddr，对端网络地址，用于标识通道组；
////                  struct load_proportion *lp，负载量及负载比结果数据结构指针
//// 返回值：         0表示获取成功，-1表示获取失败
//// 编号：
//s32 dcb_loadblc_get(u32 peeraddr, struct load_proportion *lp);

//// ----------------------------------------------------------------------------
//// 1.12             设置指定通道组的负载量及全局负载比
//// ----------------------------------------------------------------------------
//// 接口形式：       s32 dcb_loadblc_set(u32 peeraddr,
////                                        struct load_proportion *lp
////                                        );
//// 描述：           设置指定通道组的负载量及全局负载比
//// 参数：           u32 peeraddr，对端网络地址，用于标识通道组；
////                  struct load_proportion *lp，负载量及负载比结果数据结构指针
//// 返回值：         0表示设置成功，-1表示设置失败
//// 编号：
//s32 dcb_loadblc_set(u32 peeraddr, struct load_proportion *lp);

// ----------------------------------------------------------------------------
// 1.13            通知ENFC组件KdvMediaNet发送速率大小
// ----------------------------------------------------------------------------
// 接口形式：       s32 enfc_inform_kmn_rate (u32 rate)
// 描述：           通知ENFC组件KdvMediaNet当前设置的发送速率大小
// 参数：           u32 rate，KdvMediaNet实际发送速率；
// 返回值：         永远返回0，表示调用成功
// 编号：
// ----------------------------------------------------------------------------
s32 enfc_inform_kmn_rate (u32 rate);

// ----------------------------------------------------------------------------
// 1.14            获取ENFC组件版本日期
// ----------------------------------------------------------------------------
// 接口形式：       s32 enfc_get_version (s8 *version)
// 描述：           获取组件编译版本日期信息
// 参数：           s8 *version，指向编译版本日期信息字符串数组；
// 返回值：         0表示调用成功，-1表示失败
// 编号：
// ----------------------------------------------------------------------------
s32 enfc_get_version (s8 *version);

# ifdef __cplusplus
}
# endif

#endif

