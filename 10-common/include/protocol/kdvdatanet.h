/*****************************************************************************
模块名      : KdvMediaNet
文件名      : KdvMediaNet.h
相关文件    : KdvMediaNet.cpp
文件实现功能: KdvMediaSnd KdvMediaRcv类定义
作者        : 魏治兵 胡昌威
版本        : V2.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/06/03  2.0         魏治兵      Create
2003/06/03  2.0         魏治兵      Add RTP Option
2004/09/25  2.0         万春雷      增加linux版本编译支持
2004/10/19  2.0         万春雷      加入动态载荷设置以及加密接口
2004/10/19  2.0         万春雷      代码整理
2004/10/19  3.0         万春雷      增加DES加密模式支持
2004/11/30  3.0         万春雷      增加AES加密模式支持
2004/12/02  2.0         万春雷      数据帧上报时，使用m_dwContext字段上报发送端的 源IP（网络序）
2004/12/02  2.0         万春雷      取消上报:数据帧上报时，使用m_dwContext字段上报发送端的 源IP（网络序）
2004/12/22  2.0         万春雷      数据帧上报时，帧信息结构中增加一个字段上报 发送端的源IP（网络序）
******************************************************************************/


#ifndef _KDVDATANET_0302_H_
#define _KDVDATANET_0302_H_

#include "kdvtype.h"
#include "osp.h"
#include "kdvcommon.h"

#ifdef _ENABLE_QUANTUM_PROJECT_
#include "qtstruct.h"
#endif

//模块版本信息和编译时间 及 依赖的库的版本和编译时间
PROTO_EXTERN_API void kdvdatanetver();
PROTO_EXTERN_API void kdvdatanetlog(u8 level);
PROTO_EXTERN_API void printrtppacklen();
PROTO_EXTERN_API void kdvdatanetinfo(); //打印recv和send的信息

//模块帮助信息 及 依赖的库的帮助信息
PROTO_EXTERN_API void kdvdatanethelp();

#define  MAXWATCHDATASOCKPORT  (u16)10599//max watchsock port
#define  MINWATCHDATASOCKPORT  (u16)10500//min watchsock port

#define  DATA_PINHOLE_INTERVAL		10 //10s 打洞时间间隔
#define  DATANET_NO_ERROR                   (u16)0//成功返回值  

#define  ERROR_DATA_NET_BASE                (u16)16000
#define  ERROR_SND_PARAM		    (ERROR_DATA_NET_BASE+1)//设置发送模块参数出错 
#define  ERROR_SND_NOCREATE		    (ERROR_DATA_NET_BASE+2)//发送模块没有创建
#define  ERROR_SND_MEMORY		    (ERROR_DATA_NET_BASE+3)//发送模块内存操作出错
#define  ERROR_SND_CREATE_SOCK		    (ERROR_DATA_NET_BASE+4)//发送模块创建socket
#define  ERROR_RTP_SSRC                     (ERROR_DATA_NET_BASE+5)//RTP同步源错误.
#define  ERROR_LOOPBUF_CREATE               (ERROR_DATA_NET_BASE+6)//环状缓冲创建错误  
#define  ERROR_RTP_NO_INIT                  (ERROR_DATA_NET_BASE+7)//RTP类有些对象没创建
#define  ERROR_RTCP_NO_INIT                 (ERROR_DATA_NET_BASE+8)//RTCP类有些对象没创建
#define  ERROR_RTCP_SET_TIMER               (ERROR_DATA_NET_BASE+9)//RTCP设置定时器出错
#define  ERROR_RTP_SSRC_COLLISION           (ERROR_DATA_NET_BASE+10)//RTP 同步源出错
#define  ERROR_SOCK_INIT                    (ERROR_DATA_NET_BASE+11)//socket 没有初始化
#define  ERROR_H261_PACK_NUM                (ERROR_DATA_NET_BASE+12)//H261的包数不合理
#define  ERROR_PACK_TOO_LEN                 (ERROR_DATA_NET_BASE+13)//数据包太长
#define  ERROR_H263_PACK_NUM                (ERROR_DATA_NET_BASE+14)//H263的包数不合理
#define  ERROR_H263_PACK_TOOMUCH            (ERROR_DATA_NET_BASE+15)//H263的数据包太长

#define  ERROR_NET_RCV_PARAM                (ERROR_DATA_NET_BASE+100)//设置接收模块参数出错
#define  ERROR_NET_RCV_NOCREATE             (ERROR_DATA_NET_BASE+101)//接收模块没有创建
#define  ERROR_NET_RCV_MEMORY               (ERROR_DATA_NET_BASE+102)//接收模块内存操作出错
#define  ERROR_RCV_RTP_CREATE               (ERROR_DATA_NET_BASE+103)//接收模块RTP创建失败
#define  ERROR_RCV_RTP_CALLBACK             (ERROR_DATA_NET_BASE+104)//接收模块设置RTP回调函数失败
#define  ERROR_RCV_RTP_SETREMOTEADDR        (ERROR_DATA_NET_BASE+105)//接收模块设置RTP远端地址失败
#define  ERROR_CREATE_LOOP_BUF              (ERROR_DATA_NET_BASE+106)//创建环状缓冲失败
#define  ERROR_RCV_NO_CREATE                (ERROR_DATA_NET_BASE+107)//接收模块接收对象没有创建

#define  ERROR_WSA_STARTUP                  (ERROR_DATA_NET_BASE+200)//wsastartup error
#define  ERROR_CREATE_SEMAPORE              (ERROR_DATA_NET_BASE+201)//create semapore error
#define  ERROR_SOCKET_CALL                  (ERROR_DATA_NET_BASE+202)//调用socket() 函数出错
#define  ERROR_BIND_SOCKET                  (ERROR_DATA_NET_BASE+203)//socket 绑定出错
#define  ERROR_CREATE_THREAD                (ERROR_DATA_NET_BASE+204)//创建线程出错 

#define  ERROR_LOOPBUF_FULL                 (ERROR_DATA_NET_BASE+205)//循环缓冲满


#define  ERROR_SET_DECRYPTKEY               (ERROR_DATA_NET_BASE+210)//设置解密key失败
#define  ERROR_DECRYPT_FRAME                (ERROR_DATA_NET_BASE+212)//解密一帧失败
#define  ERROR_SET_ENCRYPTKEY               (ERROR_DATA_NET_BASE+213)//设置加密key失败
#define  ERROR_ENCRYPT_FRAME                (ERROR_DATA_NET_BASE+215)//加密一帧失败


#define ERROR_SND_FRAME          (s32)-1;


#ifndef DES_ENCRYPT_MODE
#define DES_ENCRYPT_MODE         (u8)0      //DES加密模式
#define AES_ENCRYPT_MODE         (u8)1      //AES加密模式
#define QT_ENCRYPT_MODE          (u8)2      //QT加密模式
#define ENCRYPT_KEY_SIZE         (u8)32     //密钥长度 取其中的较大值
#define DES_ENCRYPT_KEY_SIZE     (u8)8      //DES密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_A (u8)16  //AES Mode-A 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_B (u8)24  //AES Mode-B 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_C (u8)32  //AES Mode-C 密钥长度
#endif

#ifndef  MAX_NETSND_DEST_NUM
	#define  MAX_NETSND_DEST_NUM   5
#endif

/////////////////////////////////////////////////FECC////////////////////////////////////////////////
#define MAX_FECC_LEN 256               //最大长度

//H323 Annex Q
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
enum EmFeccAction
{
	emActionInvalid					= 0,  
	emActionStart					= 0x01,  //开始
	emActionContinue				= 0x02,  //继续
	emActionStop					= 0x03,  //停止
	emActionSelectVideoSource		= 0x04,  //选择视频源
	emActionVideoSourceSwitched		= 0x05,  //切换视频源
	emActionStoreAsPreset			= 0x06,  //存储预置位
	emActionActivatePreset			= 0x07,  //恢复到预置位
	emActionAutoFocus				= 0x11,  //自动调焦
};

//PTFZ codes, parameters for action Start, continue and stop.
enum EmFeccPTFZRequest
{
	emRequestInvalid			= 0,
	emRequestPanLeft			= 0x80,	//向左移动
	emRequestPanRight			= 0xc0,	//向右移动
	emRequestTiltUp			    = 0x30,	//向上移动
	emRequestTiltDown			= 0x20,	//向下移动
	emRequestFocusIn			= 0x03,	//近焦
	emRequestFocusOut			= 0x02,	//远焦
	
	emRequestZoomIn				= 0x0c,	//视野变小
	emRequestZoomOut			= 0x08,	//视野变大

	emRequestBrightnessUp		= 0x01,	//亮度加(nonstandard)
	emRequestBrightnessDown		= 0x04  //亮度减(nonstandard)
};

//远遥模块返回值类型
typedef enum
{
	annexQNotInited				= -20,
	annexQBindError				= -15,
	annexQParamError			= -14,
	annexQLockError				= -12,	
	annexQCodingError			= -10,
	annexQSendError				= -9,	
	annexQGeneralError			= -5,
	annexQOk					= 1
}annexQResult;

//for tanderg
enum EmFeccVideoSourceNumber
{
    emVideoSourceDefault               = 0,    //当前视频源
    emVideoSourceMainCamera            = 1,    //主视频源
    emVideoSourceAuxCamera             = 2,    //辅助视频源
    emVideoSourceDocCamera             = 3,    //文件展示台
    emVideoSourceAuxDocCamera          = 4,    //辅助文件展示台，对于泰德为vcr
    emVideoSourceVideoPlaybackSource   = 5,    //vcr，对于泰德为PC
};

////CME message type
enum EmCMEMsgType
{
	CMEInvalid,				//无效
	CMEClientListInfo,		//客户列表消息通知
	CMEClientListCommond,	//请求客户列表
	CMEExtraCapInfo,		//额外能力信息通知
	CMEExtraCapCommond,		//请求额外能力

};

//H323 Annex Q
//CME消息以及控制消息复用在一个结构体里
typedef struct PROTO_API tagFeccStruct
{
	BOOL32 m_bIsCMEMsg;		    

	u8	m_byCMEMsgType;		  //ClientListInfo/Commond,ExtraCapInfo/Commond

	u8 m_byAction;			  //start, continue, stop, video source, preset	
	union
	{
		u8 m_byRequest;		  //for PTFZ operations
		u8 m_bySourceNo;      //for VIDEO SOURCE operations
		u8 m_byPresetNo;      //for PRESET operations
	}arguments;	
	u8 m_byTimeout;			  //for start action only ,unit 50ms, 0表示800ms
public:
	tagFeccStruct()
	{
		m_bIsCMEMsg		= FALSE;
		m_byCMEMsgType	= CMEInvalid;
		m_byAction		= emActionInvalid;
		arguments.m_byRequest = 0;	
		m_byTimeout		= 0;
	}
}TFeccStruct, *PTFeccStruct;


//端口复用时需要设置streamId。
#define FECC_ENDPOINTID_LEN 32
typedef struct PROTO_API tagFeccStreamIdInfo
{
	s8  aszEndPointId[FECC_ENDPOINTID_LEN];	//终端的id, 当前仅支持e164号
	u32 IdLen;				//终端id的长度
	u32 StreamId;			//流id
	BOOL32 bSendChan;		//是否是远遥发送通道

public:
	tagFeccStreamIdInfo()
	{
		memset(aszEndPointId, 0, FECC_ENDPOINTID_LEN);
	}
}TFeccStreamIdInfo;


/*====================================================================
函数名      : kdvAnnexQInit
功能        : 远遥模块初始化
算法实现    : 无
引用全局变量: 无
输出参数说明: dwMaxFeccChannels - 最大FECC通道数
			  nDataPinhleAppID  - 打洞app的id,默认值是APPID_DATANET_PINHOLE	
			  nMinPort			- 创建watchdog socket最小端口号
			  nMaxPort			- 创建watchdog socket最大端口号
返回值说明  : annexQOk if succeed, or other if fails
====================================================================*/
PROTO_EXTERN_API s32 kdvAnnexQInit(u32 dwMaxFeccChannels, s32 nDataPinhleAppID=APPID_DATANET_PINHOLE, u16 dwMinPort=MINWATCHDATASOCKPORT, u16 dwMaxPort=MAXWATCHDATASOCKPORT);

/*====================================================================
函数名      : kdvAnnexQEnd
功能        : 关闭远遥功能
算法实现    : 无
引用全局变量: 无
输出参数说明: 无			  
返回值说明  : 无
====================================================================*/
PROTO_EXTERN_API void kdvAnnexQEnd();

/*====================================================================
函数名      : NotifyFeccMsg
功能        : H.224, H.281功能回调函数
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext   - 每个FECC通道的唯一标识，例如信道句柄
			  tFeccStruct- 远遥命令(TFeccStruct)
			  terSrc     - 源端终端列表
			  terDst     - 目的端终端列表
返回值说明  : 成功 - annexQOK
              失败 - annexQParamError
====================================================================*/
typedef s32 (PROTO_CALLBACK *NotifyFeccMsg)(MemId pContext,  TFeccStruct tFeccStruct, TTERLABEL terSrc, TTERLABEL terDst);

/*====================================================================
函	 数   名: kdvSetFeccCallBack
功	      能: 注册应用回调函数(针对所有通道设置一次，回调指针全局保存)
算 法 实  现: 
引用全局变量: 无
输入参数说明: pNotifyFeccMsg - 回调函数结构指针
返   回   值: 成功 - annexQOK
			  失败 - annexQParamError
====================================================================*/
PROTO_API s32  kdvSetFeccCallBack(IN NotifyFeccMsg pNotifyFeccMsg);

/*====================================================================
函	 数   名: kdvSetFeccChanCallBack
功	      能: 注册应用回调函数(针对每个通道设置一次，回调指针保存在每个通道信息中)
算 法 实  现: 
引用全局变量: 无
输入参数说明:	pContext	   - 每个FECC通道的唯一标识，例如信道句柄
				pNotifyFeccMsg - 回调函数结构指针
返   回   值: 成功 - annexQOK
			  失败 - annexQParamError
====================================================================*/
PROTO_API s32  kdvSetFeccChanCallBack( IN MemId pContext, IN NotifyFeccMsg pNotifyFeccMsg);

/*====================================================================
函数名      : kdvAnnexQInitSendSession
功能        : 远遥信道发送命令初始化
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext		- 每个FECC通道的唯一标识，例如信道句柄
              dwRemoteIp	- 发送通道关联的对端的IP地址
              dwRemotePort	- 发送通道关联的对端的端口号
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQInitSendSession(IN MemId pContext, IN u32 dwRemoteIp, IN u16 dwRemotePort);

/*====================================================================
函数名      : kdvAnnexQNewSendSession
功能        : 发送远遥命令
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext  - 每个FECC通道的唯一标识，例如信道句柄
			  dwLocalIp	- 发送通道的ip
			  wLocalPort- 发送通道的port
			  bSip      - 是否是sip的远摇信令
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQNewSendSession(IN MemId pContext, IN u32 dwLocalIp, IN u16 wLocalPort, IN BOOL32 bSip=FALSE);

/*====================================================================
函数名      : kdvAnnexQDeleteSendSession
功能        : 删除发送远遥数据的信道
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext  - 每个FECC通道的唯一标识，例如信道句柄			  
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQDeleteSendSession(IN MemId pContext);

/*====================================================================
函数名      : kdvAnnexQNewRecvSession
功能        : 接受远遥数据的信道
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext  - 每个FECC通道的唯一标识，例如信道句柄
              dwLocalIp	- IP地址
              wLocalPort- 端口号			  
			  bSip      - 是否是sip的远摇信令
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQNewRecvSession(IN MemId pContext, IN u32 dwLocalIp, IN u16 wLocalPort, IN BOOL32 bSip=FALSE);

/*====================================================================
函数名      : kdvAnnexQDeleteRecvSession
功能        : 删除接受远遥数据的信道
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext  - 每个FECC通道的唯一标识，例如信道句柄 			  
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQDeleteRecvSession(IN MemId pContext); 

/*====================================================================
函数名      : kdvAnnexQSetEncryptSendSession
功能        : 设置发送远遥数据信道的加密信息
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext			- 每个FECC通道的唯一标识，例如信道句柄 
			  ptEncryptSync		- 加密信息(TEncryptSync)			  
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetEncryptSendSession(IN MemId pContext, IN TEncryptSync *ptEncryptSync);

/*====================================================================
函数名      : kdvAnnexQSetDecryptRecvSession
功能        : 设置接收远遥数据信道的加密信息
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext			- 每个FECC通道的唯一标识，例如信道句柄 
			  ptEncryptSync		- 加密信息(TEncryptSync)			  
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetDecryptRecvSession(IN MemId pContext, IN TEncryptSync *ptEncryptSync);


/*====================================================================
函	 数   名: kdvFeccBind
功	      能: 多点会议中绑定远遥对象，点对点呼叫时无需绑定
算 法 实  现: 
引用全局变量: 无
输入参数说明: pContext	 - 每个FECC通道的唯一标识，例如信道句柄
              localTer   - 本地终端列表(TTERLABEL)
			  remoteTer  - 远端终端列表(TTERLABEL)
返   回   值: 成功 - annexQOk
              失败 - !annexQOk
====================================================================*/
PROTO_API s32 kdvFeccBind(IN MemId pContext, IN TTERLABEL localTer, IN TTERLABEL remoteTer, IN BOOL32 bSync = TRUE);

/*====================================================================
函	 数   名: kdvSendFeccMsg
功	      能: 通过h224通道发送远遥命令
算 法 实  现: 
引用全局变量: 无
输入参数说明: pContext	 - 每个FECC通道的唯一标识，例如信道句柄
			  feccStruct - 远遥命令(TFeccStruct)
返   回   值: 成功 - annexQOk
              失败 - !annexQOk
====================================================================*/
PROTO_API s32 kdvSendFeccMsg(IN MemId pContext, IN TFeccStruct tFeccStruct, IN BOOL32 bSync = TRUE);

/*====================================================================
函数名      : kdvFeccSetStreamId
功能        : 端口复用时设置远遥码流id
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext		- 每个FECC通道的唯一标识，例如信道句柄
			  EndPointId    - 终端的id, 当前仅支持e164号
			  IdLen         - 终端id的长度
			  StreamId      - 流id
			  bSendChan		- 是否是远遥发送通道
返回值说明  : annexQOk if succeed, or other if fails
====================================================================*/
PROTO_API s32 kdvFeccSetStreamId(IN MemId pContext, TFeccStreamIdInfo tFeccStreamIdInfo, IN BOOL32 bSync = TRUE);

/*====================================================================
函数名      : kdvAnnexQSetKeepAliveAddress
功能        : 启用h460的远遥打洞
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext  - 每个FECC通道的唯一标识，例如信道句柄
			  dwLocalIp	- KeepAlive通道的ip
			  wLocalPort- KeepAlive通道的port
              dwInterval- KeepAlive通道的打洞时间间隔
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetKeepAliveAddress(IN MemId pContext, IN u32 dwKeepAliveIp, IN u16 wKeepAlivePort, IN s32 dwInterval=0, IN BOOL32 bSync = TRUE);

#ifdef _ENABLE_QUANTUM_PROJECT_
/*====================================================================
函数名      : kdvAnnexQSetQtEncrptyHandle
功能        : 设置QT加密句柄
算法实现    : 无
引用全局变量: 无
输入参数说明: hQtCallHandle  - 量子呼叫句柄
              bQTEnable      - 量子加密
			  bSendChannel   - 通道方向

返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvAnnexQSetQTEncrptyHandle(IN MemId pContext,IN QTCALLHANDLE hQtCallHandle,IN BOOL32 bSendChannel = FALSE);
#endif

#ifdef _KDV_SRTP_SUPPORT_
/*====================================================================
函数名      : kdvFeccSetSrtp
功能        : 设置远摇通道的srtp内容
算法实现    : 无
引用全局变量: 无
输入参数说明: pContext    - 每个FECC通道的唯一标识，例如信道句柄
             bSend  	 - 通道方向，TRUE为发送通道，FALSE为接收通道
             tSrtpCrypto - srtp相关信息		  
返回值说明  : annexQOk if succeed, or annexQGeneralError if fails
====================================================================*/
PROTO_API s32 kdvFeccSetSrtp(IN MemId pContext, IN BOOL32 bSend, IN TMediaSrtpCrypto tSrtpCrypto, IN BOOL32 bSync=TRUE); 
#endif

//设置远遥TOS值
PROTO_API s32 kdvSetDataTOS(s32 nTOS);
PROTO_API s32 kdvGetDataTOS();


//Frame Header Structure
typedef struct tagH224Data
{
    u8     *m_pData;       // 数据缓冲
    u32     m_dwDataSize;  // m_pData指向的实际缓冲大小缓冲大小
}TH224Data,*PTH224Data;

typedef struct PROTO_API tagH224Session
{
public:
	TTERLABEL	m_tSrcLabel;
	TTERLABEL	m_tDstLabel;
	BOOL32      m_bSip;//sip和323的远摇信令区别：sip无界标记、字节序不反转、不带校验和、不做插0处理

public:
	tagH224Session()
	{	
		Clear();
	}
	~tagH224Session()
	{        
        Clear();
	}

	void Clear()
	{
		m_tSrcLabel.Clear();
		m_tDstLabel.Clear();
		m_bSip = FALSE;
	}
    void FeccBind(IN TTERLABEL tSrcLabel, IN TTERLABEL tDstLabel );

/*====================================================================
函数名      : kdvCreateFeccMsg
功能        : 生成FECC的消息，由TFeccStruct-->TH224Data
算法实现    : 无
引用全局变量: 无
输入参数说明: tFeccStruct	- 业务使用的远遥信息结构体TFeccStruct
			  tDataHdr		- FECC的信息，RTP数据部分
返回值说明  : TRUE if succeed, or FALSE if fails
====================================================================*/
	BOOL32  kdvCreateFeccMsg( IN TFeccStruct &tFeccStruct, OUT TH224Data &tDataHdr);

/*====================================================================
函数名      : kdvExtractFeccMsg
功能        : 解析FECC消息，由TH224Data-->TFeccStruct
算法实现    : 无
引用全局变量: 无
输入参数说明: tFeccStruct	- 业务使用的远遥信息结构体TFeccStruct
			  TH224Data		- FECC的信息，RTP数据部分
返回值说明  : TRUE if succeed, or FALSE if fails
====================================================================*/
	BOOL32  kdvExtractFeccMsg( OUT TFeccStruct &tFeccStruct, IN const TH224Data &tDataHdr);

//	void operator = (const tagH224Session& tH224Session);

private:
    u16 PackH224Payload(IN u8* h224Buf,  IN u16 h224Len, OUT u8* rawData, IN u32 rawBufLen);
	u32 ExtractH224Payload(IN u8* rawData, IN u32 rawLen, OUT u8* h224Buf, IN u16 h224BufLen);
	u16 GenCRC16Code( u8 *pbyBuff, u16 wBuffLen );
 	
}TH224Session;
  

#endif

