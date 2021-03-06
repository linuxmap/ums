#ifndef _H323CONFNONSTDSTRUCT_H
#define _H323CONFNONSTDSTRUCT_H

//#include "cm.h"
#include <time.h>
#include <math.h>

#include "kdv323common.h"


//#define IPV6_NAME_LEN		(u16)64  //IPv6地址名长度
// #define INVALID_NODEID      RV_PVT_INVALID_NODEID
// #define TYPE_NONE           RV_ADDRESS_TYPE_NONE         //表示为未定义地址
// #define TYPE_IPV4           RV_ADDRESS_TYPE_IPV4         //表示支持IPv4地址
// #define TYPE_IPV6           RV_ADDRESS_TYPE_IPV6         //表示支持IPv6地址
//#define TYPE_SCTP           RV_NET_SCTP         //表示同事支持IPv4、IPv6地址

//#define LEN_MTNUM_PERCONF	(u16)192				//每个会议中的最大呼叫数



//修改需和kdvpts保持一致
//#define KDV_NSM_MAX_LEN        (s32)1300  //暂时1300字节
/*#define KDV_NSM_MAX_LEN        (s32)(1024*10)  */

// 非标消息错误号定义
// typedef enum
// {
// 	KDVP_NSM_SUCCESS		= 0,  
// 	KDVP_NSM_SER_DB_ERR,
// 
// #ifdef _KDV_V50
// 	KDVP_NSM_TIMEOUT_ERR,				//2
// 	KDVP_NSM_NOTE164_ERR,				//3
// 	KDVP_NSM_DATA_ERR,                  //4
// 	KDVP_NSM_MCU_NOIDLEVPU,             //5  没有足够能力的空闲媒体处理器
// 	KDVP_NSM_MCU_MINIMEDIACONFMTNUM,    //6  超过小型媒体会议入会终端限制
// 	KDVP_NSM_MCU_MAXCONFNUM,            //7  已达最大会议数
// 	KDVP_NSM_MCU_ENCRYPEERR,            //8  与会议加密模式不符
// 	KDVP_NSM_MCU_CONFNOTEXIST,          //9  会议不存在
// 	KDVP_NSM_MCU_MAXMTNUM,              //10 达到最大参会人员数
// 	KDVP_NSM_GK_MPCD_DISCONNECTED,      //11 MPCD与GK断链
// 	KDVP_NSM_MCU_CONFRESUMING,          //12 MCU真正恢复中
// 	KDVP_NSM_MCU_PASSERR,               //13 会议密码错误
// 	KDVP_NSM_MCU_NSATPMS,               //14 无卫星权限
// 	KDVP_NSM_MCU_NSATDADDR,             //15 没有组播地址
// 	KDVP_NSM_MCU_CONFE164REPEAT,        //16 会议E164号重复
// 	KDVP_NSM_MCU_UNDEFINED,             //17
// #endif //_KDV_V50
// 
// };




//非标参数类型
enum NonstandardType 
{
    emNonstandardTypeInvalidType = 0,
    emNonstandardTypeRequest,
    emNonstandardTypeResponse,
    emNonstandardTypeCommand,
    emNonstandardTypeIndication
};

//会议操作:makeTerminalBroadcaster和sendThisSource的操作方式
enum CtrlMode 
{
	mode_invalid = -1,
	mode_command,
	mode_request
};

typedef enum
{
	emChanUnkown = 0,
	emChanVideo1 = 1,
	emChanAudio	 = 2,
	emChanVideo2 = 3
}emChanID;

typedef enum
{
    emComUnkown  = 0,
    emComRS232   = 1,
    emComRS422   = 2,
    emComRS485   = 3,
    emComEnd
    
}emComType;


/*
该功能主要用于在会议中A终端从串口读到的数据 通过网络传输给对端 
消息内容
  1.数据类型    //初步用 1 -RS232串口数据  2 =RS422 3=RS485 
  2.数据长度
  3.数据
*/
typedef struct tagCOMData
{
    emComType  m_emComType;
    s32 m_nDataLen;
    s8  m_achData[128];
    
public:
    tagCOMData()
    {
        Clear();
    }

    void Clear()
    {
        m_emComType = emComUnkown;
        memset(m_achData, 0, sizeof(m_achData));
        m_nDataLen = 0;
    }

    void host2net(BOOL32 bhton)
    {
        s32 nType = m_emComType;
        if (bhton)
        {
            m_emComType  = (emComType)htonl(nType);
            m_nDataLen   = htonl(m_nDataLen);
        }
        else
        {
            m_emComType  = (emComType)ntohl(nType);
            m_nDataLen   = ntohl(m_nDataLen);
        }
    }

    void SetComType(emComType emType)
    {
        m_emComType = emType;
    }

    emComType GetComType()
    {
        return m_emComType;
    }

    void SetComData(s8 *pData, s32 nLen)
    {
        if (NULL == pData || nLen < 0)
        {
            return;
        }

        m_nDataLen = Minimum(nLen, (s32)sizeof(m_achData));
        memset(m_achData, 0, sizeof(m_achData));
        memcpy(m_achData, pData, m_nDataLen);
        m_achData[m_nDataLen] = '\0';
    }

    s32 GetComDataLen()
    {
        return m_nDataLen;
    }

    s8* GetComData()
    {
        return m_achData;
    }

}TCOMDATA, *PTCOMDATA;

typedef struct tagChanMultiCast
{
	u8  m_byChanID;    //1视频，2音频，3第二路视频
	u32 m_dwIP;        //组播地址
	u16 m_wPort;       //组播端口
	//add by yj for ipv6
	u8          m_byIPType;                                 //支持的 IP地址类型
	u8          m_dwIP_ipv6[IPV6_NAME_LEN];			         //组播地址ipv6，非网络序;
	s16         m_swScopeId;                                //获取或设置 IPv6 地址范围标识符
	//end

    tagChanMultiCast()
    {
        Clear();
    }

    void Clear()
    {
        m_byChanID = emChanUnkown;
        m_dwIP = 0;
        m_wPort = 0;
		//add by yj for ipv6
		m_byIPType = TYPE_NONE;   
	    memset(m_dwIP_ipv6, 0, sizeof(m_dwIP_ipv6));
		m_swScopeId = -1;
        //end
    }

    void host2net(BOOL32 bhton)
    {
        if (bhton)
        {
            m_dwIP  = htonl(m_dwIP);
            m_wPort = htons(m_wPort);
        }
        else
        {
            m_dwIP  = ntohl(m_dwIP);
            m_wPort = ntohs(m_wPort);
        }
    }

    void SetChanID(u8 byChan)
    {
        m_byChanID = byChan;
    }
	
    u8 GetChanID()
    {
        return m_byChanID;
    }

    //add by yj for ipv6
	//设置ip地址类型
	void SetChanAddr_Type (u8 byIPType)
	{
		m_byIPType = byIPType;
	}
	u8 GetChanAddr_Type( )
	{
		return	m_byIPType;
	}
	//设置ScopeId(ipv6)值
	s16 GetChanAddr_Ipv6_ScopeId( )
	{
		return	m_swScopeId;
	}
	void SetChanAddr_Ipv6_ScopeId(s16 swScopeId)
	{
		m_swScopeId = swScopeId;
	}
	//设置协议栈运行IP(ipv6)
	void SetChanAddr_Ipv6(u8 *dwIP_ipv6)
	{
		memcpy(m_dwIP_ipv6, dwIP_ipv6, sizeof(m_dwIP_ipv6));	
	}
	u8 *GetChanAddr_Ipv6()
	{
		return m_dwIP_ipv6;
	}
	

	//end

    void SetChanAddr(u32 ip, u16 port)
    {
        m_dwIP = ip;
        m_wPort = port;
    }

    u32 GetChanIp()
    {
        return m_dwIP;
    }

    u16 GeChantPort()
    {
        return m_wPort;
    }
    
}TCHANMULTICAST, *PTCHANMULTICAST;

/*
多点会议中厂商能力指示
*/
typedef struct tagCapInfo
{   
    s32  m_nVendor;                     //厂商ID
    BOOL32 m_bIsMCU;                      //FALSE:MT, TRUE:MCU
    BOOL32 m_bMix;                        //混音
    BOOL32 m_bVAC;                        //语音激励
    BOOL32 m_bCustomVMP;                  //定制画面合成
    BOOL32 m_bAutoVMP;                    //自动画面合成
    BOOL32 m_bEndConf;                    //结束会议
    BOOL32 m_bInvateMt;                   //邀请终端
    BOOL32 m_bDropMt;                     //删除终端
    BOOL32 m_bSelSpeaker;                 //指定/取消发言人
    BOOL32 m_bSelChair;                   //指定/放弃主席
    BOOL32 m_bSelSource;                  //选看终端
    BOOL32 m_bFECC;                       //远程摄像头遥控
    BOOL32 m_bQuiet;                      //远端静音
    BOOL32 m_bMute;                       //远端哑音
    BOOL32 m_bConfReq;                    //会议申请处理
    BOOL32 m_bOnlineList;                 //在线终端列表
    BOOL32 m_bOfflineList;                //离线终端列表
    BOOL32 m_bSelSpeakingUser;            //点名
    BOOL32 m_bPicSwitch;                  //单多画面切换
    BOOL32 m_bMustSeeSpeaker;             //强制广播
    //...                                
                            

    tagCapInfo()
    {
        Clear();
    }

    void Clear();

}TCAPINFO, *PTCAPINFO;


typedef struct tagMultiPic
{
	u8  m_byMcuNo;
	u8  m_byStyle;//emPicStyle
	TTERLABEL m_tTer[16];
	
	tagMultiPic()
	{
		Clear();
	}

	void Clear()
	{
		m_byMcuNo = 0;
		m_byStyle = 0;
		memset(m_tTer, 0, sizeof(m_tTer));//Huawei默认都为0
	}
	
}TMultiPic, *PTMultiPic;












///////////////////全部加入 ////////////////////////

#ifndef H323CASCADE_H_

#define CASCADE_PORT		    (s32)3337
/*#define CASCADE_USERNAME_MAXLEN     (s32)32*/
/*#define CASCADE_USERPASS_MAXLEN     (s32)32 */
#define CASCADE_NONSTANDARDMSG_MAXLEN (u32)1536
#define PART_NUM			     (s32)192//
#define STR_LEN                  (s32)16
#define CONFID_BYTELEN                   (s32)12// 
#define PID_POS                          (s32)4//
//#define MAX_VIEWS_PER_CONF               (s32)2
#define MAX_VIEWS_PER_CONF               (s32)4
#define MAX_GEOMETRYS_PER_VIEW           (s32)5
#define MAX_SUBFRAMES_PER_GEOMETRY       (s32)16
#define MAX_VIDEOSCHEMES_PER_VIEW        (s32)4
#define MAX_MIXERS_PER_CONF              (s32)16

#define MCU_PID                          (u32)0XFFFFFFFF
#define CACSCONF_ID                      (u32)0XFFFFFFFF
#define EMPTY_MT_PID                     (u32)0x0


#define E_TOO_MANY_ITEMS                 (s32)-1
#define E_ALREADY_EXISTED                (s32)-2
#define E_INVALID_PARAMETER              (s32)-3
#define E_NOT_EXISTED                    (s32)-4
#define E_SUBFRAMES_CONTRIBUTERS_UNMATCH (s32)-5
//#define S_RIGHT                             (s32)1
#define S_REPLACED                       (s32)2
#define S_RIGHT                          (s32)1

enum emConnState
{
	    emConnStateUnknown,                 //该MT,MCU的连接状态未知，表明它从未
		emConnStateConnected,               //"connected"
		emConnStateDisconnected,            //"disconnected"
		emConnStateConnecting               //"alerting"
};

enum emEPType
{
    	emEPTypeUndefined,                  //不明类型
		emEPTypeMCU,                        //mcu,但是它已一个普通终端的身份参加级联会议或是会议
		emEPTypeTerminal,                   //普通终端
		emEPTypeCascConf,                    //mcu,并且参加了级联会议
		emEPTypeTerPhone                    //电话终端 [2012/05/03]		
};


//time config struct
typedef struct tagTimeSpec
{
    s8 day;
    s8 hour;
    s8 minute;
    s8 second;
    s16 year;
    s8 month;
}TTimeSpec,*PTTimeSpec;

//标准请求头,他是所有请求的基类
// typedef struct tagRequest
// {
//     s32  m_nReqID;//流水号/系列号
// 	s8   m_aszUserName[CASCADE_USERNAME_MAXLEN];//帐号
// 	s8   m_aszUserPass[CASCADE_USERPASS_MAXLEN];//密码
// 	//设置帐号和密码
// 	inline void SetUserNameAndPass(const s8 * aszUserName, const s8 *aszUserPass)
// 	{
// 		strncpy(m_aszUserName, aszUserName, CASCADE_USERNAME_MAXLEN-1);
// 		m_aszUserName[CASCADE_USERNAME_MAXLEN-1] = '\0';
// 		strncpy(m_aszUserPass, aszUserPass, CASCADE_USERPASS_MAXLEN-1);
// 		m_aszUserPass[CASCADE_USERPASS_MAXLEN-1] = '\0';
// 	}
// }TReq;


//非标级联消息的基类
typedef struct tagNonStandardMsg
{
	s32 m_nMsgLen;//消息长度
	u8	m_abyMsgBuf[CASCADE_NONSTANDARDMSG_MAXLEN];//消息体
}TNonStandardMsg;

//非标(自定义)请求消息
typedef struct tagNonStandardReq: public TReq, public TNonStandardMsg{}TNonStandardReq;

//response消息的返回值字段
enum emReturnValue
{
    emReturnValue_Ok				= 0,	//request消息已得到正确的处理
    emReturnValue_Error				= 1,	//一般性错误，错误原因不明
    emReturnValue_PartNotFound		= 2,	//会议组中不存在请求消息中PID指示的会议成员
    emReturnValue_ConfNotFound		= 3,	//请求消息中confID指明的会议组不存在
    emReturnValue_ChannelNotFound	= 4,	//会议成员的音频/视频通道不存在
    emReturnValue_NoPermission		= 5,	//用户的权限不够，请求消息不被处理
    emReturnValue_XmlBadParams		= 6,	//请求消息中字段名或是字段的值类型/范围错误
    emReturnValue_TimeOut			= 7,	//请求消息处理超时
    emReturnValue_NoResources		= 8,	//mcu没有足够的资源来满足请求消息对音视频资源的要求
    emReturnValue_Invalid			= 9		//请求无效,不会被处理
};
typedef struct tagResponse           //Request消息的回应消息(response消息)
{                           
    s32    m_nReqID;//流水号/系列号,它匹配request中的流水号/系列号
    emReturnValue m_emReturnVal;//request处理结果指示符
    tagResponse()
    {
        m_emReturnVal = emReturnValue_Ok;
        m_nReqID =((s32)time(NULL))%((s32)0x7fffffff);
    }
}TRsp;

//非标(自定义)response消息
typedef struct tagNonStandardRsp: public TRsp, public TNonStandardMsg{}TNonStandardRsp;


//通知类型消息(notification)的基类
typedef struct tagNotification
{
    s32    m_nCookie;//cookie值
}TNtf;

//获取MCU上的服务列表的请求消息,它向对端mcu请求此mcu上所有已经定义的服务模板的信息
#define TMCUServiceListReq TReq

//获取MCU上当前召开的所有会议相关信息的列表
typedef struct tagMCUConfListReq: public TReq
{
	s32 m_nSnapShot;//MCU快照值
}TMCUConfListReq;

//通过会议名字获得会议ID的请求消息
typedef struct tagGetConfIDByNameReq:public TReq
{
	s8 m_aszConfName[STR_LEN];//会议名称
	s8 m_aszConfPass[STR_LEN];//会议密码,mcu管理者的密码也同样有效
}TGetConfIDByNameReq;

//请求进行会议级联的注册注销请求
// typedef struct tagRegUnReg: public TReq     //向对端mcu注册注销的请求消息
// {
//     BOOL32 m_bReg;               //true:注册;false 注销
// }TRegUnRegReq;

//请求进行会议级联的注册/注销的回应消息(成功 m_emReturnVal为true，否则)
typedef struct tagRegUnRegRsp :public TRsp 
{
	BOOL32 m_bReg;  //true:注册;false 注销            
}TRegUnRegRsp;


typedef struct tagPartID           //会议参加者的ID,唯一的表示级连MCU会议中一个参与者
                                  //其中m_dwPID＝0xffffffff表示级连子会议;
{
    u32         m_dwPID;          // part id
    BOOL32      m_bLocal;         // true:会议参加者直接与本地MCU相连 
                                 // false:会议参加者直接与对端MCU相连
    tagPartID ()
    {
        m_dwPID = 0;
        m_bLocal =FALSE;
    }
    inline BOOL32 IsSamePart(tagPartID tPeerPart)
    {
        if(m_dwPID == tPeerPart.m_dwPID && m_bLocal == tPeerPart.m_bLocal)
        {
            return TRUE;
        }
        return FALSE;
    }
    inline BOOL32 IsSamePart(u32 dwPID, BOOL32 bLocal)
    {
        if(m_dwPID == dwPID && m_bLocal == bLocal)
        {
            return TRUE;
        }
        return FALSE;
    }
    inline u32    GetPid() { return m_dwPID ;}
    inline void   SetPid(u32 dwPID) { m_dwPID = dwPID;}
    inline BOOL32 IsLocalPart(){ return m_bLocal;}
    inline BOOL32 IsRemotePart(){ return !m_bLocal;}
    inline BOOL32 IsEmptyPart(){ return m_dwPID == EMPTY_MT_PID;}
    inline void   SetEmpty(){ m_dwPID = EMPTY_MT_PID; m_bLocal = FALSE; }
    inline void   SetIsLocalPart(BOOL32 bLocal = TRUE) { m_bLocal = bLocal; }
    //
    inline BOOL32 IsLocalKdvMCU(){  return (m_dwPID  == CACSCONF_ID && m_bLocal);}
    inline BOOL32 IsRemoteRadMcu(){ return (m_dwPID == CACSCONF_ID && !m_bLocal);}

    inline void SetPartGid(u32 dwPid, BOOL32 bLocal)
    {
        m_dwPID  = dwPid;
        m_bLocal = bLocal;
    }
    
    inline void GetPartGid(u32 *pdwPid, BOOL32 *pbLocal)
    {
        if(pdwPid)
        {
            *pdwPid = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        return;
    }
}TPartID;

//获取MCU上当前召开的所有会议的profile
//我们暂时未定义它的响应消息的结构
typedef struct tagConfProfileReq:public TReq
{
    s32 m_nSnapShot;//
}TConfProfileReq;

//
typedef struct tagPartReq: public TPartID, public TReq{}TPartReq;

//新发言人(Floor)通知
typedef struct tagNewSpeakerNtf:public TPartID,public TNtf
{
    s32 m_nMixerID;  //Mixer ID
    tagNewSpeakerNtf(){memset(this, 0, sizeof(*this)); }
}TNewSpeakerNtf,*PTNewSpeakerNtf;

//
typedef enum 
{
        emMediaTypeNone,    //unknown,invalid
        emMediaTypeVideo,   //video
        emMediaTypeAudio,   //audio
        emMediaTypeData     //data
}emMediaType;               //媒体类型

typedef enum 
{
    emDirectionNone,       //unknown,invalid
    emDirectionIn,        //从终端到MCU
    emDirectionOut       //从MCU到终端
}emMuteDirection;          //某一类媒体流的流向

typedef struct tagPartMediaChan:public TPartID
{
    emMediaType      m_emMediaType;        //媒体类型
    emMuteDirection  m_emMuteDirection;    //媒体流流动方向
    BOOL32           m_bMute;              //true:切断该方向的流动，false:打开该方向的媒体流动
    tagPartMediaChan(){memset(this, 0, sizeof(*this)); }
}TPartMediaChan; 

//会议成员音/视/数据通道打开/关闭通知
typedef struct tagPartMediaChanNtf:public TPartMediaChan,public TNtf{}TPartMediaChanNtf;

//会议成员音/视/数据通道打开/关闭请求
typedef struct tagPartMediaChanReq:public TPartMediaChan,public TReq{}TPartMediaChanReq;

// 一个从MCU到终端的视频输出规范的定义
typedef struct tagViewOutInfo:public TPartID 
{    
    s32 m_nOutViewID;         //LayoutID,输出的会议视图ID
    s32 m_nOutVideoSchemeID;  //VideoSchemeID,视频输出方案ID
}TViewOutInfo,*PTViewOutInfo;

//请求MCU输出视频流到会议成员
typedef struct tagSetOutReq :public TReq
{
    s32              m_dwPartCount;           //请求MCU输出视频到自己的终端数目
    TViewOutInfo     m_tPartOutInfo[PART_NUM];//视频输出规范的列表，每一个列表元素定义了一个终端的视频输出请求

private:
    
     BOOL32 FindPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 &nPartIndex);

public: 
    tagSetOutReq(){memset(this, 0, sizeof(*this)); }

    inline s32 GetPartCount(){ return m_dwPartCount;}

    s32 AddNewPartViewOutItem(u32 dwPartId, BOOL32 bLocal, s32 nOutViewID, s32 m_nOutVideoSchemeID);
 
    ////////////////
    s32 DelPartViewOutItem(u32 dwPartId, BOOL32 bLocal);
    
    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 &nViewId, s32 &nVideoSchemeId);

    s32 GetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut);

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,s32 nViewId, s32 nVideoSchemeId);

    s32 SetPartViewOutItem(u32 dwPartId, BOOL32 bLocal,TViewOutInfo &tPartViewOut);

    inline TViewOutInfo * GetItemByIndex(s32 nIndex)
    { return (nIndex >= 0 && nIndex < m_dwPartCount) ? &(m_tPartOutInfo[nIndex]) : NULL; }

}TSetOutReq,*PTSetOutReq;

//MCU输出视频流到会议成员的通知
typedef struct tagPartOutputNtf:public TPartID,public TNtf
{
    s32 m_nViewID; //终端输出到的会议视图ID
    inline tagPartOutputNtf()
    {
        m_nViewID = m_dwPID = 0;
        m_bLocal = FALSE;
    }
}TPartOutputNtf, *PTPartOutPutNtf;


// 会议花名册的一项,表示一个与会成员的基本信息
typedef struct tagTRosterItem:public TPartID
{
    emConnState  m_emConnState;    //连接状态
}TRosterItem, *PTRosterItem;

// 会议花名册通知
typedef struct tagRosterList:public TNtf
{
    s32          m_nCount;               //花名册记录条数目
    TRosterItem  m_atRoster[PART_NUM];   //记录条列表
private: 
    BOOL32 FindRosterItem(u32 dwPartId, BOOL32 bLocal, s32 &nIndex);

public:

    inline tagRosterList(){ memset(this, 0, sizeof(*this));}

    BOOL32 AddRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState);
    
    BOOL32 DelRosterItem(u32 dwPartId, BOOL32 bLocal, emConnState emState);
    
    inline TRosterItem * GetItemByIndex(s32 nIndex)
    { return (nIndex >= 0 && nIndex < m_nCount) ? &(m_atRoster[nIndex]) : NULL; }

}TRosterList, *PTRosterList;

//会议视图子窗口的位置标志
typedef struct 
{
    s32  m_nViewID;//会议视图ID
    u8   m_bySubframeIndex;//子窗口在会议视图中位置(按照从左到右从上到下的顺序从0开始计数)
}TViewPos;

//(voice activate)语音激活请求,把当前说话人/或者音量最大的会议成员的视频放置在视图的那个子窗口中
typedef struct tagVAReq:public TReq, public TViewPos{}TVAReq;

//会议成员的视频输出输入信息
typedef struct tagPartVideoInfo
{
    s32       m_nViewCount;                    //终端(会议成员)的视频总共输出到的视图数目
    TViewPos  m_anViewPos[MAX_VIEWS_PER_CONF]; //终端在哪些视图里
    s32       m_nOutputViewID;                 //终端接收哪个视图
    s32       m_nOutVideoSchemeID;             //输入到终端的视频方案ID(当一个会议支持两种会议格式)                        
    
private:
    BOOL32 FindViewPos(s32 nViewID, u8 bySubframeIndex, s32 &nIndex);

public:
    tagPartVideoInfo()
    {
        memset(this,0,sizeof(*this));
    }
    BOOL32 AddViewPos(s32 nViewID,u8 bySubframeIndex);
   
    BOOL32 DelViewPos(s32 nViewID,u8 bySubframeIndex);

    BOOL32 IsViewPosExist(s32 nViewID, u8 bySubframeIndex);

    inline void SetVideoSpec(s32 nNewLID, s32 nNewSchemeID, s32 *nOldLID = NULL, s32 *nOldSchemeID = NULL)
    {
        if(nOldLID)
        {
            *nOldLID = m_nOutputViewID;
        }
        if(nOldSchemeID)
        {
            *nOldSchemeID = m_nOutVideoSchemeID;
        }
        m_nOutputViewID        = nNewLID;
        m_nOutVideoSchemeID = nNewSchemeID;
        return;
    }

    inline void GetVideoSpec(s32 *pnLID, s32 *pnSchemeID)
    {
        if(pnLID)
        {
            *pnLID = m_nOutputViewID;
        }
        if(pnSchemeID)
        {
            *pnSchemeID = m_nOutVideoSchemeID;
        }
    }

}TPartVideoInfo,*PTPartVideoInfo;


/*
 *与会者的视频，音频输入输出的统计信息，包括（带宽，发送/接受的包数目，乱序包数目，
 抖动(jitter)缓冲等,目前没有具体定义
*/
typedef struct tagPartAVStatis
{
  u32 m_dwTotalInBandWidth;
  u32 m_dwTotalOutBandWidth;
  u32 m_dwUnused_AudioIn;
  u32 m_dwUnused_AudioOut;
  u32 m_dwUnused_VideoIn;
  u32 m_dwUnused_VideoOut;
  // Currently We Define the bandwith with fixed value
  // because we did not decide to get extra info about part
  // Once we change to get the extra info, we should rewrite this code here.
  tagPartAVStatis()
  {
      m_dwTotalInBandWidth = 437720;
      m_dwTotalOutBandWidth = 437720; 
      m_dwUnused_AudioIn  = 0;
      m_dwUnused_AudioOut = 0;
      m_dwUnused_VideoIn  = 0;
      m_dwUnused_VideoOut = 0;
      
  }
}TPartAVStatis;

// 
// /*
//  *与会者的信息
// */
typedef struct tagPart:public TPartID
{
    s8			m_aszPartName[STR_LEN];     //part name
    s8			m_aszDialStr[STR_LEN];      //dial string
    u32			m_dwIP;            //part ip
    emEPType	m_emEPType;        //part type
    s8          m_aszEPDesc[STR_LEN];       //part des(product id)
    PayloadType m_emVideoIn;       //video in format (H263、G711.....None)
    PayloadType m_emVideoOut;      //.....
    PayloadType m_emVideo2In;      //.....
    PayloadType m_emVideo2Out;     //..... 
    PayloadType m_emAudioIn;       //.....
    PayloadType m_emAudioOut;      //..... 
    BOOL32      m_bDataMeeting;    //data meeting  
    BOOL32      m_bVideoMuteIn;    //whether or not video in mute(no camera)
    BOOL32      m_bVideoMuteOut;   //....(no dispaly)
    BOOL32      m_bAudioMuteIn;    //....(no mic)
	BOOL32      m_bAudioMuteOut;   //....(no audio player)
    BOOL32      m_bInvited;        //whether or not is Invited
    BOOL32      m_bMaster;         //whether or not Master ternial
    TTimeSpec   m_tStartTime;      //call start time
    emConnState m_emConnState;     //connect state
    BOOL32      m_bFECCEnable;     //whether or not enable FECC
    TPartVideoInfo m_tPartVideoInfo;   //视频输出输入信息
    TPartAVStatis  m_tAVStatis;    //视频音频输入输出统计信息

    tagPart()
    {
        memset(this, 0, sizeof(*this));
    }
    inline void SetVideoAttr(PayloadType emVideoIn, PayloadType emVideoOut, 
                                PayloadType emVideo2In, PayloadType emVideo2Out, 
                                BOOL32 bVideoMuteIn, BOOL32 bVideoMuteOut)
    {
         m_emVideoIn      = emVideoIn;      
         m_emVideoOut     = emVideoOut; 
         m_emVideo2In      = emVideo2In;      
         m_emVideo2Out     = emVideo2Out; 
         m_bVideoMuteIn   = bVideoMuteIn;    
         m_bVideoMuteOut  = bVideoMuteOut;   
    }

    inline void GetVideoAttr(PayloadType *pemVideoIn, PayloadType *pemVideoOut, 
                                PayloadType *pemVideo2In, PayloadType *pemVideo2Out,
                                BOOL32 *pbVideoMuteIn, BOOL32 *pbVideoMuteOut)
    {
        if(pemVideoIn)
        { 
            *pemVideoIn = m_emVideoIn;
        }
        if(pemVideoOut)
        { 
            *pemVideoOut = m_emVideoOut; 
        }
        if(pemVideo2In)
        { 
            *pemVideo2In = m_emVideo2In;
        }
        if(pemVideo2Out)
        { 
            *pemVideo2Out = m_emVideo2Out; 
        }
        if(pbVideoMuteIn)
        { 
            *pbVideoMuteIn = m_bVideoMuteIn;
        }
        if(pbVideoMuteOut)
        { 
            *pbVideoMuteOut = m_bVideoMuteOut;
        }
        return;
    }
    
    inline void SetViewInAndOutAttr(TPartVideoInfo &tPartVideoInfo)
    {
        memcpy(&m_tPartVideoInfo, &tPartVideoInfo,sizeof(TPartVideoInfo));
    }

    inline TPartVideoInfo* GetViewInAndOutAttr()
    {
        return &m_tPartVideoInfo;
    }
    
    inline void SetAudioAttr(PayloadType emAudioIn, PayloadType emAudioOut, BOOL32 bAudioMuteIn, BOOL32 bAudioMuteOut)
    {
        m_emAudioIn      = emAudioIn;      
        m_emAudioOut     = emAudioOut;     
        m_bAudioMuteIn   = bAudioMuteIn;    
        m_bAudioMuteOut  = bAudioMuteOut;   
    }

    inline void GetAudioAttr(PayloadType *pemAudioIn, PayloadType *pemAudioOut, BOOL32 *pbAudioMuteIn, BOOL32 *pbAudioMuteOut)
    {
        if(pemAudioIn)
        { 
            *pemAudioIn = m_emAudioIn;
        }
        if(pemAudioOut)
        { 
            *pemAudioOut = m_emAudioOut; 
        }
        if(pbAudioMuteIn)
        { 
            *pbAudioMuteIn = m_bAudioMuteIn;
        }
        if(pbAudioMuteOut)
        { 
            *pbAudioMuteOut = m_bAudioMuteOut;
        }
        return;
    }

    inline void SetNameAttr(const s8 *pszName, s32 nNameLen, const s8 *pszDescr, s32 nDescrLen)
    {
        // assert(pszName != NULL);
        s32 nStrLen = (nNameLen >= sizeof(m_aszPartName) ? sizeof(m_aszPartName) - 1 : nNameLen );
        strncpy(m_aszPartName, pszName, nStrLen);
        m_aszPartName[nStrLen] = '\0';

        if(pszDescr != NULL && nDescrLen > 0)
        {
            nStrLen = (nDescrLen >= sizeof(m_aszDialStr) ? sizeof(m_aszDialStr) -1 : nDescrLen );
            strncpy(m_aszDialStr, pszDescr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';
        }
        else
        {
            m_aszDialStr[0] = '\0';
        }
    }

    inline void GetNameAttr(s8 *pszName, s32 nNameLen, s8 *pszDescr, s32 nDescrLen)
    {
        if(pszName != NULL && nNameLen > 0)
        {
            s32 nStrLen = (nNameLen >= STR_LEN ? STR_LEN -1 : nNameLen );
            strncpy(pszName, m_aszPartName, nStrLen);
            pszName[nStrLen] = '\0';  
        }

        if(pszDescr != NULL && nDescrLen > 0)
        {
            s32 nStrLen = (nDescrLen >= STR_LEN ? STR_LEN -1 : nDescrLen);
            strncpy(pszDescr, m_aszDialStr, nStrLen);     
            pszDescr[nStrLen] = '\0';
        }
    }

    inline void SetDialStr(const s8 *pszDialStr, s32 nLen)
    {
       if(pszDialStr !=NULL && nLen >0)
       {
           s32 nStrLen = (nLen >= STR_LEN ? STR_LEN -1 : nLen);
           strncpy(m_aszDialStr, pszDialStr, nStrLen);
           m_aszDialStr[nStrLen] = '\0';
       }
    }

    inline s8 * GetDialStr() { return this->m_aszDialStr; }

    inline void SetEntityAttr(emConnState emState, emEPType emEntityType, BOOL32 bFECCEnable, BOOL32 bMaster, BOOL32 bInvited)
    {
        m_emConnState    = emState;  
        m_emEPType       = emEntityType;
        m_bFECCEnable    = bFECCEnable;     
        m_bMaster        = bMaster;       
        m_bInvited       = bInvited;       
    }
    inline BOOL32 IsFECCEnable(){ return m_bFECCEnable;}
    inline BOOL32 IsMaster() { return m_bMaster;}
    inline BOOL32 IsInvited() { return m_bInvited;}
    inline emConnState GetConnState() { return m_emConnState;}
    inline void   SetConnState(emConnState emState) { m_emConnState = emState;}
    inline void   StopAsVideoSrc() { m_tPartVideoInfo.m_nViewCount = 0;}
    inline BOOL32 IsVideoSrc() { return (m_tPartVideoInfo.m_nViewCount > 0);}
    inline u32    GetTotalBandWith() { return m_tAVStatis.m_dwTotalInBandWidth + m_tAVStatis.m_dwTotalOutBandWidth;}

    inline void GetEntityAttr(emConnState *pemState, BOOL32 *pbFECCEnable, BOOL32 *pbMaster, BOOL32 *pbInvited)
    {
        if(pemState)
        { 
            *pemState = m_emConnState;
        }
        if(pbFECCEnable)
        { 
            *pbFECCEnable = m_bFECCEnable; 
        }
        if(pbMaster)
        { 
            *pbMaster = m_bMaster;
        }
        if(pbInvited)
        { 
            *pbInvited = m_bInvited;
        }
        return;
    }
    inline void GetVideoScheme(s32 *pnViewId, s32 *pnVideoSchemeId)
    {
        m_tPartVideoInfo.GetVideoSpec(pnViewId,pnVideoSchemeId);
    }
    inline void SetVideoScheme(s32 nViewId, s32 nVideoSchemeId)
    {
        m_tPartVideoInfo.SetVideoSpec(nViewId, nVideoSchemeId, NULL, NULL);
    }
}TPart,*PTPart;

// 级连会议与会者的信息
typedef struct tagConfPartInfo
{
    s32    m_dwPartCount;       //fact part count
    s32    m_nSnapShot;         //会议的快照值
        //The first Element Denotes MCU, The Record series from second Denote Terminals 
    TPart  m_atParts[PART_NUM]; // part list 
 private:
     BOOL32 FindPart(u32 dwPartId, BOOL32 bLocal, s32 &nIndex)
	 {
		 for(nIndex =0; nIndex < m_dwPartCount; nIndex++)
		 {
			 if(m_atParts[nIndex].IsEmptyPart())
			 {
				 return FALSE;
			 }
			 if(m_atParts[nIndex].IsSamePart(dwPartId, bLocal))
			 {
				 return TRUE;
			 }
		 }
		 return FALSE;
	}
		 
 public:
     void Clear()
     {
         memset(this, 0, sizeof(*this));
     }
     tagConfPartInfo()
     {
         memset(this, 0, sizeof(*this));
     }
     s32 AddPart(TPart &tPart, BOOL32 bReplace = TRUE)
	 {
		 s32  nPartIndex = 0;
		 if(FindPart(tPart.m_dwPID, tPart.m_bLocal, nPartIndex))
		 {
			 if(bReplace)
			 {
				 memcpy(&m_atParts[nPartIndex], &tPart, sizeof(TPart));
				 return S_RIGHT;
			 }
			 else
			 {
				 return E_ALREADY_EXISTED;
			 }
		 }
		 if( nPartIndex >= PART_NUM)
		 {
			 return E_TOO_MANY_ITEMS;
		 }
		 
		 memcpy(&m_atParts[nPartIndex], &tPart, sizeof(TPart));
		 m_dwPartCount ++;
		 return S_RIGHT;
}

    s32 DelPart(u32 dwPartId, BOOL32 bLocal);
    
     s32 Disconnect(u32 dwPartId, BOOL32 bLocal, u32 dwNewPartId);
    
     TPart *GetPart(u32 dwPartId, BOOL32 bLocal);

     inline TPart *GetLocalMCU()
     {
         return GetPart(CACSCONF_ID, TRUE);
     }

     inline TPart *GetPeerMCU()
     {
         return GetPart(CACSCONF_ID, FALSE);
     }

     BOOL32 IsPartExist(u32 dwPartId, BOOL32 bLocal);
     
     inline TPart *GetItemByIndex(s32 nPosFrom)
     {
         return (nPosFrom >= 0 && m_dwPartCount > nPosFrom ? &m_atParts[nPosFrom] : NULL);
     }
     
}TConfPartInfo;

// 对方MCU级连子会议的回应列表
typedef struct tagPartListRsp :public TConfPartInfo,public TRsp
{
   BOOL32 m_bLastPack;			//whether or not last pack，used only while receiving
   public:
    tagPartListRsp() { m_emReturnVal = emReturnValue_Ok; m_bLastPack = TRUE;}
    void Clear()
    { 
        memset(this, 0, sizeof(*this));
        m_emReturnVal = emReturnValue_Ok; 
        m_bLastPack = TRUE;
    }
    void BuildToPartListRsp(TConfPartInfo &tConfPart);
    
    BOOL32 ExtractConfPartList(TConfPartInfo &tConfPart);
  
}TPartListRsp,*PTPartListRsp;

//PartList消息收发头结构，后面跟m_dwPartCount个TPart结构
typedef struct tagPartListMsg: public TRsp
{
    s32    m_dwPartCount;       //fact part count
    s32    m_nSnapShot;         //会议的快照值
    BOOL32 m_bLastPack;         //whether or not last pack，used only while receiving
} TPartListMsg,*PTPartListMsg;


// 邀请终端加入会议的参数
typedef struct tagInvitePart
{
    s8   m_aszDialStr[STR_LEN];   //dial string ("123"、"100.1.1.1"、"h323id")
    u32  m_dwCallRate;                //call rate (kbps)
    
    //optional,advanced invitation parameter
    TPartVideoInfo m_tPartVideoInfo;
    
    tagInvitePart()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void SetBasicInviteeParam(const s8 *pszDialStr, s32 nStrLen, u32 dwCallRate);

    void GetBasicInviteeParam(s8 *pszDialStr, s32 nStrLen, u32 *pdwCallRate);

    inline void SetInviteeSetInAndOutAttr(TPartVideoInfo &tPartVideoInfo)
    {
        memcpy(&m_tPartVideoInfo, &tPartVideoInfo, sizeof(TPartVideoInfo));
    }

    inline TPartVideoInfo GetInviteeSetInAndOutAttr()
    {
       return m_tPartVideoInfo;
    }
  
}TInvitePart,*PTInvitePart;


// /*
//   邀请对象加入级连会议的消息体  
// */
typedef struct tagInvitePartReq: public TReq
{
	s32          m_nCount;           //同时受要求的对象的数目
    TInvitePart  m_atPart[PART_NUM]; //受邀请对象信息
public:
     tagInvitePartReq()
     {
        memset(this, 0, sizeof(*this));
     }

     inline BOOL32 AddInvitee(TInvitePart &tInvitee)
     {
         if(m_nCount >= PART_NUM)
         {
             return FALSE;
         }
         memcpy(&m_atPart[m_nCount], &tInvitee,sizeof(TInvitePart));
         m_nCount++;
         return TRUE;
     }

     inline TInvitePart *GetItemByIndex(s32 nPos)
     { return (nPos >= 0 && nPos < m_nCount) ? &(m_atPart[nPos]) : NULL; }

}TInvitePartReq;

//重新要求已经断开的终端加入会议
typedef struct tagReinvitePartReq: public TPartID, public TReq{}TReInvitePartReq;

//MCU_MCU_CALL_ALERTING_NTF 消息体
typedef struct tagCallNtf : public TPartID, public TNtf
{
	s8   m_aszDialStr[STR_LEN];   //dial string ("123"、"100.1.1.1"、"h323id")
   
    tagCallNtf()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void inline GetPartCallingParam(s32 *pdwPartId, BOOL32 *pbLocal,s8 *pszDialStr, s32 nStrLen)
    {
        if(pdwPartId)
        {
            *pdwPartId = m_dwPID;
        }
        if(pbLocal)
        {
            *pbLocal = m_bLocal;
        }
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(pszDialStr, m_aszDialStr, nStrLen);
            pszDialStr[nStrLen] = '\0';
        }
    }

    void inline SetPartCallingParam(u32 dwPartId, BOOL32 bLocal,s8 *pszDialStr, s32 nStrLen)
    {
        m_dwPID  = dwPartId;
        m_bLocal = bLocal;
        if(pszDialStr != NULL && nStrLen >0)
        {
            nStrLen = (nStrLen >= STR_LEN ? STR_LEN -1 : nStrLen );
            strncpy(m_aszDialStr, pszDialStr, nStrLen);
            m_aszDialStr[nStrLen] = '\0';
        }
    }
}TCallNtf;

//请求终端输出图像到会议的某个视图
typedef struct tagSetInReq:public TPartID, public TReq
{
    s32 m_nViewID;          //图像输出到达的会议视图
    u8  m_bySubFrameIndex;  //会议视图中的子图像(subframe)索引
    tagSetInReq()
    {
        memset(this, 0, sizeof(*this));
    }
    
    void SetPartSetInParam(u32 dwPartId, BOOL32 bLocal, s32 nViewID, u8 bySubFrameIndex);

    void GetPartSetInParam(s32 *pdwPartId, BOOL32 *pbLocal, s32 *pnViewID, u8 *pbySubFrameIndex);
    
}TSetInReq;

/*
 *与会者从级连会议中断开的通告，
*/
typedef struct tagDiscPartNF : public TPartID, public TNtf
{
    u32 m_dwNewPID;   //new part id
    tagDiscPartNF()
    {
        m_dwNewPID = 0;
    }
}TDiscPartNF,*PTDiscPartNF;

//混音器信息，可能会有多个speaker，这里只是制定一个
typedef struct tagAudioMixerInfo
{
    s32    m_nMixerID;             //mixer ID
    u32    m_dwSpeakerPID;         //speaker Pid
    BOOL32 m_bLocal;               //romote or local?
    tagAudioMixerInfo()
    {
        m_nMixerID = m_dwSpeakerPID = 0;
        m_bLocal = FALSE;
    }
    inline BOOL32 IsSpeakerExist(u32 dwPartId, BOOL32 bLocal)
    {
        return (m_dwSpeakerPID == dwPartId && m_bLocal == bLocal);
    }
}TAudioMixerInfo, *PTAudioMixerInfo;

//MCU的混音器的信息
typedef struct tagConfAudioInfo:public TRsp
{
    u8 m_byMixerCount;                                 //混音器数目
    u8 m_byDefaultMixerIndex;                          //缺省混音器，以索引表示,它也是当前正在播音的混音器
    s32 m_nSnapShot;                                    //会议快照值
    TAudioMixerInfo m_tMixerList[MAX_MIXERS_PER_CONF]; //混音器列表

 private:
     BOOL32 FindSpeaker(u32 dwPartId, BOOL32 bLocal, s32 &nMixerIndex);

 public:
     tagConfAudioInfo()
     {
         memset(this, 0, sizeof(*this));
         m_emReturnVal = emReturnValue_Ok;
         m_nSnapShot = 0;
     }

     void Clear(void)
     {
         memset(this, 0, sizeof(*this));
         m_emReturnVal = emReturnValue_Ok;
         m_nSnapShot = 0;
     }
     
     BOOL32 AddNewSpeaker(u32 dwPartId, BOOL32 bLocal, s32 nMixerId);
     
     BOOL32 DelSpeaker(u32 dwPartId, BOOL32 bLocal);
     
     inline void GetCurrentSpeaker(u32 &dwPartId, BOOL32 &bLocal)
     {
         dwPartId = m_tMixerList[m_byDefaultMixerIndex].m_dwSpeakerPID;
         bLocal   = m_tMixerList[m_byDefaultMixerIndex].m_bLocal;
     }

     s32 SetCurrentSpeaker(u32 dwPartId, BOOL32 bLocal);

     inline BOOL32 IsCurrentSpeaker(u32 dwPartId, BOOL32 bLocal)
     {
         return (m_tMixerList[m_byDefaultMixerIndex].m_dwSpeakerPID == dwPartId
                && m_tMixerList[m_byDefaultMixerIndex].m_bLocal == bLocal);
     }
}TConfAudioInfo;



//会议视图几何布局变更通知
typedef struct tagConfViewChgNtf: public TNtf
{
    s32                   m_nViewID;                                 //发生几何布局变化的会议视图ID
    u8                    m_dwSubFrameCount;                           //变化后的几何布局划分成的子图像数目(subframe)
}TConfViewChgNtf;

//MCU的视频输出方案
typedef struct tagOutPutVideoSchemeInfo
{
    s32           m_nOutputVideoSchemeID;   //视频输出方案ID
    u32           m_dwMaxRate;              //max rate (kbps)
    u32           m_dwMinRate;              //min rate (kbps)
    BOOL32        m_bCanUpdateRate;         // whether or not enable update rate
    s32           m_nFrameRate;             // frame rate (30、25)
    PayloadType   m_emPayLoad;              // payload    (h261,h263,etc)
    tagOutPutVideoSchemeInfo()
    {
        memset(this, 0, sizeof(*this));
    }
}TOutPutVideoSchemeInfo,*PTOutPutVideoSchemeInfo;


//一个会议视图的定义，它包括一系列的几何布局，一系列的视图视频源(由pid来标志)的列表，
//以及可选的输出该会议视图的几个视频输出方案(rad mcu 中最多四个).
typedef struct tagViewInfo
{
    s32                m_nViewId;                                           //会议视图 ID
    emResolution       m_emRes;                                             //会议视图图像的分辨率
    u8                 m_byCurrentGeometryIndex;                            //会议视图当前正在使用(输出)的几何布局,以在几何布局列表中的索引来标明
    u8                 m_byGeometryCount;                                   //几何布局的数目
    u8                 m_abyGeometryInfo[MAX_GEOMETRYS_PER_VIEW];            //几何布局列表
    u8                 m_byContributePIDCount;                              //会议视图的视频源的数目
    TPartID            m_atContributePIDs[MAX_SUBFRAMES_PER_GEOMETRY];         //视频源列表
    u8                 m_byVideoSchemeCount;                                //可选的视频输出方案数目
    TOutPutVideoSchemeInfo    m_atVideoSchemeList[MAX_VIDEOSCHEMES_PER_VIEW];     //视频输出方案列表
  
    //add 2007.04.28
    BOOL32             m_bAutoSwitchStatus;
    BOOL32             m_bDynamic;
    s32                m_nAutoSwitchTime;
    s32                m_nVideoRole;
    

    inline tagViewInfo()
    {
        memset(this, 0, sizeof(*this));
    }
    
    inline void SetViewResolution(emResolution emRes)
    {
        m_emRes = emRes;
    }
    
    inline emResolution GetViewResolution()
    {
        return m_emRes;
    }
    
    inline void GetCurrentContributerList(TPartID **pptContributerParts, s32 &nArrayLen, s32 *pnCurrentSubframes)
    {
        if(pptContributerParts)
        {
           *pptContributerParts = m_atContributePIDs;
            nArrayLen = m_byContributePIDCount;
        }
        if(pnCurrentSubframes)
        {
           *pnCurrentSubframes = m_abyGeometryInfo[m_byCurrentGeometryIndex];
        }
        return;
    }

    inline BOOL32 SetCurrentContributerList(TPartID *ptContributerParts, s32 nArrayLen)
    {
        if(ptContributerParts != NULL && nArrayLen > 0)
        {
            s32 nSubFrameCount = 0;
            nSubFrameCount =(nArrayLen <= MAX_SUBFRAMES_PER_GEOMETRY ?
                                     nArrayLen : MAX_SUBFRAMES_PER_GEOMETRY);
            s32 nIndex = 0;
            while(nIndex < MAX_SUBFRAMES_PER_GEOMETRY && m_abyGeometryInfo[nIndex] != 0 && m_abyGeometryInfo[nIndex] != nSubFrameCount)
            {
                nIndex ++;
            }
            if(nIndex >= MAX_SUBFRAMES_PER_GEOMETRY)
            {
                return FALSE;
            }
            if(m_abyGeometryInfo[nIndex] == 0)
            {
                m_byContributePIDCount ++;
                m_byGeometryCount ++;
                m_abyGeometryInfo[nIndex] = nSubFrameCount;  
            }
            m_byCurrentGeometryIndex = nIndex;
            memcpy(m_atContributePIDs, ptContributerParts, sizeof(TPartID)*nSubFrameCount);
        }
        else
        {
            m_byGeometryCount        = 1;
            m_abyGeometryInfo[0]     = 1;
            m_byCurrentGeometryIndex = 0;
            m_byContributePIDCount   = 0;
        }
        return TRUE;
    }

    inline void SetGeometryList(u8 *pbyGeometryList, s32 nItemCount, s32 nIndexCurrentGeometry = 0)
    {
        s32 nGeometryCount = 0;
        nGeometryCount = (nItemCount < MAX_GEOMETRYS_PER_VIEW ?
                         nItemCount : MAX_GEOMETRYS_PER_VIEW);
        memcpy(m_abyGeometryInfo, pbyGeometryList,nGeometryCount * sizeof(u8));
        m_byGeometryCount = nGeometryCount;
        m_byCurrentGeometryIndex = ((m_byGeometryCount -1 > nIndexCurrentGeometry) ?
                                    nIndexCurrentGeometry : m_byGeometryCount -1);
        return;
    }
    
    inline void GetGeometryList(u8 **ppbyGeometryList, s32 *pnItemCount, s32 *pnIndexCurrentGeometry = NULL)
    {
        if(ppbyGeometryList && pnItemCount) 
        {
            *ppbyGeometryList = m_abyGeometryInfo;
            *pnItemCount      = m_byGeometryCount;
        }
        if(pnIndexCurrentGeometry)
        {
            *pnIndexCurrentGeometry = m_byCurrentGeometryIndex;
        }
        return;
    }
    
    inline void SetVideoSchemeList(TOutPutVideoSchemeInfo *ptSchemeList, s32 nItemCount)
    {
        this->m_byVideoSchemeCount = nItemCount;
        memcpy(this->m_atVideoSchemeList, ptSchemeList, nItemCount * sizeof(TOutPutVideoSchemeInfo));
    }

    inline void GetVideoSchemeList(TOutPutVideoSchemeInfo **pptSchemeList, s32 &nItemCount)
    {
        *pptSchemeList = this->m_atVideoSchemeList;
        nItemCount = this->m_byVideoSchemeCount;
        return;
    }
    
    inline s32 GetViewId() { return m_nViewId;}
    inline void SetViewId(s32 nViewId) { m_nViewId = nViewId;}

}TView, *PTView;

//
typedef struct tagConfVideInfoReq: public TReq
{
    u8          m_bFullInfo;    //是否请求发送几何布局视图
    tagConfVideInfoReq(){ m_bFullInfo = TRUE; }
}TConfVideInfoReq;

//级连会议在单个MCU上的视频输入输出信息
typedef struct tagConfVideoInfo:public TRsp
{
    u8          m_byConfViewCount;                              //会议视图的数目
    //默认使用的会议视图,如果与该MCU直连的终端或是MCU在连接建立时没有指定会议视图信息，
    //则默认观看该会议视图
    u8          m_byDefaultViewIndex;                            //默认会议视图索引
    u8          m_bFullInfo;                                     //是否发送几何布局视图
    s32         m_nSnapShot;                                     //会议快照值
    TView       m_atViewInfo[MAX_VIEWS_PER_CONF]; //会议视图列表
    
    private:
        BOOL32 FindView(s32 nViewId, s32 &nViewIndex);
        
    public:

        inline tagConfVideoInfo()
        {
            m_byConfViewCount = m_byDefaultViewIndex = 0;
            m_emReturnVal = emReturnValue_Ok;
            m_bFullInfo = TRUE;
        }
        inline void Clear(void)
        {
            memset(this, 0, sizeof(*this));
            m_byConfViewCount = m_byDefaultViewIndex = 0;
            m_emReturnVal = emReturnValue_Ok;
        }
        s32 AddView(TView &tView, BOOL32 bDefaultView = FALSE, BOOL32 bReplace = TRUE);
        
        s32 DelView(s32 nViewId);
        
        s32 GetView(s32 nViewId, TView **pptView);
        
        BOOL32 IsViewExist(s32 nViewId);

        inline TView* GetItemByIndex(s32 nIndex)
        {
           return nIndex >= 0 && nIndex < m_byConfViewCount ?
               &m_atViewInfo[nIndex] : NULL;
        }
        
        inline s32 GetDefaultViewId()
        { 
            return m_atViewInfo[m_byDefaultViewIndex].GetViewId();
        }

        void DelPartRelationship(s32 nPId, BOOL32 bLocal);
     
}TConfVideoInfo;


//add 2007.04.28
typedef struct tagAutoswitchReq: public TReq     //
{
  
    s32         m_nLid;
    s32         m_nAutoSwitchTime;
    s32         m_nAutoSwitchLevel;
    BOOL32      m_bAutoSwitchOn;

public: 
    tagAutoswitchReq()
    {
        Clear();
    }


    void Clear()
    {
        memset(this, 0, sizeof(tagAutoswitchReq));
    }
    
    void SetLid(s32 nLid)
    {
        m_nLid = nLid;
    }

    s32  GetLid()
    {
        return m_nLid;
    }

    void SetAutoSwitchTime(s32 nTime)
    {
        m_nAutoSwitchTime = nTime;
    }

    s32 GetAutoSwitchTime()
    {
        return m_nAutoSwitchTime;
    }

    void SetAutoSwitchLevel(s32 nLevel)
    {
        m_nAutoSwitchLevel = nLevel;
    }

    s32 GetAutoSwitchLevel()
    {
        return m_nAutoSwitchLevel;
    }
    
    void SetAutoSwitchOn(BOOL32 bOn)
    {
        m_bAutoSwitchOn = bOn;
    }

    BOOL32 GetAutoSwitchOn()
    {
        return m_bAutoSwitchOn;
    }

}TAutoswitchReq, *PTAutoswitchReq;

typedef struct tagAutoswitchRsp: public TRsp{}TAutoswitchRsp, PTAutoswitchRsp;

#endif //_H323CONFNONSTDSTRUCT_H

/////////////////////////  从kdv323adapter.h中提出的级联会议消息和结构体 end    /////////
//防串货渠道标识， mt<-->mcu，暂定此非标内容长度为一个BYTE，用于存储渠道标识代号
//对应非标消息h_ctrl_KedaManuProduct					= 1121
typedef struct tagKedaManuProduct
{
	u8	m_byAgentID; //暂定此非标内容长度为一个BYTE，用于存储渠道标识代号
	tagKedaManuProduct()
	{
		m_byAgentID = 0;
	}
}TKedaManuProduct;

#endif	//_H323CONFNONSTDSTRUCT_H


