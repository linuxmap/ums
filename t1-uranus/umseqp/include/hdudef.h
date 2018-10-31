//HDU 相关参数定义

#ifndef  _hdu_def_h__
#define	 _hdu_def_h__
#include "mcudef.h"

//HDU 运行状态
enum EmRunState
{
	emhduidle,
	emhduMonitorIng,
	emhduMonitored,
};

#define     HDU_OUTPUTMODE_NONE               0   //无输出模式
#define     HDU_OUTPUTMODE_AUDIO              1   //音频输出模式
#define     HDU_OUTPUTMODE_VIDEO              2   //视频输出模式
#define     HDU_OUTPUTMODE_BOTH               3   //音视频输出模式

//  [1/8/2010 pengjie] Modify
// HDU 子画面空闲时显示模式
// HDU空闲通道显示为黑色
#define HDU_SHOW_BLACK_MODE           0
// HDU空闲通道显示最后一帧
#define HDU_SHOW_LASTFRAME_MODE       1 
// HDU空闲通道显示默认图片，1280*720
#define HDU_SHOW_DEFPIC_MODE          2
// HDU空闲通道显示用户自定义图片
#define HDU_SHOW_USERDEFPIC_MODE      3

//HDU业务信息
const u16    EV_UMS_HDU_BGN = 26441;
OSPEVENT( UMS_HDU_REG_REQ,			    EV_UMS_HDU_BGN );		//业务注册
OSPEVENT( UMS_HDU_REG_ACK,			    EV_UMS_HDU_BGN + 1 );	//业务注册ACK
OSPEVENT( UMS_HDU_REG_NACK,			    EV_UMS_HDU_BGN + 2 );	//业务注册NACK

//播放
OSPEVENT( UMS_HDU_START_PLAY_REQ,		EV_UMS_HDU_BGN + 3);	//播放请求
OSPEVENT( UMS_HDU_PLAY_ACK,				EV_UMS_HDU_BGN + 4);
OSPEVENT( UMS_HDU_PLAY_NACK,			EV_UMS_HDU_BGN + 5);

//通道停止播放
OSPEVENT( UMS_HDU_STOP_PLAY_REQ,		EV_UMS_HDU_BGN + 6 );
OSPEVENT( UMS_HDU_STOP_PLAY_ACK,		EV_UMS_HDU_BGN + 7 );
OSPEVENT( UMS_HDU_STOP_PLAY_NACK,		EV_UMS_HDU_BGN + 8 );

//请求外设状态
OSPEVENT( UMS_HDU_GETSTATUS_REQ,		    EV_UMS_HDU_BGN + 9 );  // hdu2不处理
OSPEVENT( HDU_UMS_GETSTATUS_ACK,		    EV_UMS_HDU_BGN + 10 ); // hdu2不处理
OSPEVENT( HDU_UMS_GETSTATUS_NACK,		    EV_UMS_HDU_BGN + 11 ); // hdu2不处理
OSPEVENT( HDU_UMS_STATUS_NOTIF,			    EV_UMS_HDU_BGN + 12 );

//--------请求关键帧-------
OSPEVENT( HDU_UMS_NEEDIFRAME_CMD,		    EV_UMS_HDU_BGN + 13 );
//--------调节音量---------
//消息体：FIXME。涉及chnlid,vol
OSPEVENT( UMS_HDU_SETCHNNLVOL_CMD,			EV_UMS_HDU_BGN + 14 ); // hdu2不处理
//某通道音量通知消息
OSPEVENT( HDU_UMS_CHNNLVOL_NOTIF,			EV_UMS_HDU_BGN + 15 ); // hdu2不处理
//通道状态通知
OSPEVENT( HDU_UMS_CHNNLSTATUS_NOTIF,		EV_UMS_HDU_BGN + 16 ); // 

//改变输入输出制式及显示比例通知
OSPEVENT( UMS_HDU_CHANGEMODEPORT_NOTIF,		EV_UMS_HDU_BGN + 17 ); 

// 设置音量大小命令
OSPEVENT( UMS_HDU_CHANGEVOLUME_CMD,		    EV_UMS_HDU_BGN + 19 ); 

// 变更模式
OSPEVENT( UMS_HDU_CHANGEMODE_CMD,		    EV_UMS_HDU_BGN + 20 ); // hdu2不处理

//通道空闲显示策略变更
OSPEVENT( UMS_HDU_CHANGEPLAYPOLICY_NOTIF,   EV_UMS_HDU_BGN + 21 ); 

//HDU通道模式切换(多画面或单通道)
OSPEVENT( UMS_HDU_CHGHDUVMPMODE_REQ,		EV_UMS_HDU_BGN + 22 ); // hdu2支持，ums未处理
OSPEVENT( HDU_UMS_CHGHDUVMPMODE_ACK,		EV_UMS_HDU_BGN + 23 ); // hdu2支持，ums未处理
OSPEVENT( HDU_UMS_CHGHDUVMPMODE_NACK,		EV_UMS_HDU_BGN + 24 ); // hdu2支持，ums未处理

//刷新音频载荷
OSPEVENT( UMS_HDU_FRESHAUDIO_PAYLOAD_CMD, 	EV_UMS_HDU_BGN + 25 );  // hdu2支持，ums未处理

//通知电视墙码流密钥 量子
OSPEVENT(UMS_HDU_MEDIAKEY_NTY,              EV_UMS_HDU_BGN + 30 );

const u16	 EV_UMS_HDU_END	= UMS_HDU_MEDIAKEY_NTY;	//HDU业务消息结束，必须和最后一个最大的值相等

#define		QT_MAX_MEDIAKEY_LEN		1024
struct TQTMediaKeyInfo
{
	u32		m_dwChnlNo;
	u32		m_dwHandle;
	u16		m_wIndex;
	s8      m_szAlias[TP_MAX_ALIAS_LEN + 1];
	u8		m_szMediaKey1[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u8		m_szMediaKey2[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u8		m_szMediaKey3[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u8		m_szMediaKey4[QT_MAX_MEDIAKEY_LEN/4 + 1];
	u32     m_dwKeyLen;//码流密钥实际长度
	u32		m_dwKeyFrequency;//(0:一秒一秘; 1:一分一秘; 2:一会一秘)
	u32		m_dwQtFlag;
	
	TQTMediaKeyInfo()
	{
		memset(this, 0, sizeof(TQTMediaKeyInfo));
	}
	
	void clear()
	{
		memset(this, 0, sizeof(struct TQTMediaKeyInfo));
		m_dwHandle = TP_INVALID_INDEX;
		m_wIndex = TP_INVALID_INDEX ;
		m_dwKeyLen = 0;
		m_dwKeyFrequency = 2;//2:一会一秘
		m_dwQtFlag = 0;
		m_dwChnlNo = 0;
	}
	
	void SetChnlNo(u32 dwChnlNo) { m_dwChnlNo = htonl(dwChnlNo); }
	u32 GetChnlNo(){ return ntohl(m_dwChnlNo); }
	
	void SetHandle(u32 dwHandle) { m_dwHandle = htonl(dwHandle); }
	u32 GetHandle(){ return ntohl(m_dwHandle); }
	
	void SetIndex(u16 wIndex) { m_wIndex = htons(wIndex); }
	u16 GetIndex(){ return ntohs(m_wIndex); }
	
	void SetKeyLen(u32 dwLen) { m_dwKeyLen = htonl(dwLen); }
	u32 GetKeyLen(){ return ntohl(m_dwKeyLen); }
	
	void SetKeyFrequency(u32 dwFreq) { m_dwKeyFrequency = htonl(dwFreq); }
	u32 GetKeyFrequency(){ return ntohl(m_dwKeyFrequency); }
	
	void SetQtFlag(u32 dwFlag) { m_dwQtFlag = htonl(dwFlag); }
	u32 GetQtFlag(){ return ntohl(m_dwQtFlag); }
	
	void GetAlias(s8* pszBuf, u16 wLen) 
	{
		memcpy(pszBuf, m_szAlias, min( TP_MAX_ALIAS_LEN, wLen)); 
	}
	
	void GetKey(u8* pszBuf, u16 wLen)
	{
		if ( wLen < QT_MAX_MEDIAKEY_LEN )
		{
			return ;
		}
		memcpy(pszBuf, m_szMediaKey1, QT_MAX_MEDIAKEY_LEN/4);
		memcpy(pszBuf + QT_MAX_MEDIAKEY_LEN/4, m_szMediaKey2, QT_MAX_MEDIAKEY_LEN/4);
		memcpy(pszBuf + QT_MAX_MEDIAKEY_LEN/2, m_szMediaKey3, QT_MAX_MEDIAKEY_LEN/4);
		memcpy(pszBuf + 3*QT_MAX_MEDIAKEY_LEN/4, m_szMediaKey4, QT_MAX_MEDIAKEY_LEN/4);
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

struct TEqpHduCfgInfo : public TEqpCfgInfo 
{
protected:
	
    THduChnlModePort atHduChnlModePort[MAXNUM_HDU_CHANNEL];    
	u8	m_byStartMode;//启动模式：(0: hdu_2 1:hdu_1 2:hdu_L )
public:
	TEqpHduCfgInfo()
	{
        memset(&atHduChnlModePort, 0X0, sizeof(atHduChnlModePort));
		SetStartMode(STARTMODE_HDU_M);
	}

	void SetStartMode(u8 byStartMode){m_byStartMode = byStartMode; }
	u8   GetStartMode(){ return m_byStartMode; }

	void GetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			tHduChnModePort.SetOutModeType( atHduChnlModePort[byNum].GetOutModeType() );
			tHduChnModePort.SetOutPortType( atHduChnlModePort[byNum].GetOutPortType() );
		    tHduChnModePort.SetZoomRate( atHduChnlModePort[byNum].GetZoomRate() );
			tHduChnModePort.SetScalingMode( atHduChnlModePort[byNum].GetScalingMode() );
		}
		else
		{
			return;			
		}
		
		return;
	}
	
    void SetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			atHduChnlModePort[byNum].SetOutModeType( tHduChnModePort.GetOutModeType() );
			atHduChnlModePort[byNum].SetOutPortType( tHduChnModePort.GetOutPortType() );
            atHduChnlModePort[byNum].SetZoomRate( tHduChnModePort.GetZoomRate() );
			atHduChnlModePort[byNum].SetScalingMode(tHduChnModePort.GetScalingMode());
		}
		else
		{
			return;	
		}
		
		return;
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

#endif