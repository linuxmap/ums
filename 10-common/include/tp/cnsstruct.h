#ifndef _h_cnstruct_h__
#define _h_cnstruct_h__
#include "tpsys.h"
#include <time.h>

#include "tpcommontype.h"
#include "tpcommonstruct.h"
#include "osp.h"
#include "cnconst.h"
#include "cnstype.h"

typedef struct tagTTPMCUSelViewReq
{
	TTPTerLabel tTerLabel;
	EmTpCtrlMode emTpCtrlMode;
	u8           byPos;
	
	tagTTPMCUSelViewReq()
	{
		memset(this, 0, sizeof(struct tagTTPMCUSelViewReq));
	}
}TTPMCUSelViewReq;

typedef struct tagTTPShowLogo
{
	s8        achLogoName[TP_MAX_ALIAS_LEN + 1];
	BOOL      bIsShowLogo;
    EmTpColor emColor;
    EmTpSize  emSize;
	EmTpLogoStyle emStyle;
	BOOL      bInit;//标识T300第一次启动
}TTPShowLogo;

typedef struct tagTTPLogoInfo
{
    TTPShowLogo tFirsLogoInfo;
	TTPShowLogo tSecondLogoInfo;
	TTPShowLogo tThirdLogoInfo;
}TTPLogoInfo;

typedef struct tagTTPShowBanner
{
	s8        achBannerName[TP_MAX_ALIAS_LEN + 1];
    BOOL      bIsShowBanner;
	EmTpColor emColor;
    EmTpSize  emSize;
	EmTpStyle emStyle;
	emTpTransparency emTransparency;
}TTPShowBanner;

typedef struct tagTTPBannerInfo
{
    TTPShowBanner tFirstBannerInfo;
	TTPShowBanner tSeconfBannerInfo;
	TTPShowBanner tThirdBannerInfo;
}TTPBannerInfo;

//add by wangqichang
//视频源名称
typedef struct tagTTPVideoSourceName
{
	EmTPMtVideoPort m_emPortType;
	s8 m_achSourceName[TP_MAX_ALIAS_LEN+1];
	public:
		tagTTPVideoSourceName()
		{
			memset(this, 0 , sizeof( tagTTPVideoSourceName ));
		}
}TTPVideoSourceName;

//维护工具上主视频设置
typedef struct tagTTPVideoInfoTool
{
	EmTPMtVideoPort        m_aemBigVideoSource[emEndMPCodec - 1];//大图像视频源
	EmTPMtVideoPort        m_aemMinVideoSource[emEndMPCodec - 1];//小图像视频源
	TTPVideoSourceName     m_atVideoSourceName[emTPC7Vid];//视频源名称(6个,全景摄像机属于双流)
	EmVidEncResizeMode     m_emVidEncResizeMode;//主视频图像比例调整策略
	BOOL                   m_bIsH323PipMerge;//H323会议画面合成
	public:
		tagTTPVideoInfoTool(){memset(this,0,sizeof(struct tagTTPVideoInfoTool));}
}TTPVideoInfoTool;

//中控电视机配置信息
typedef struct tagTCentreTVCfg
{
	EmSerialType           emSerialType;  //电视机连接串口类型
	EmTvPowerMode          emTvPowerMode; //电视机开关状态 
	EmTVAudVisMode         emAudVisMode; //电视机视听模式
	EmTVDisplayMode        emDisMode;    //电视机显示模式
	EmTVInputSelect        emInpSelect;  //电视输入选择
	EmTvSrcPowerMode	   emTvSrcPowerMode;//电视机断电前开关状态
	EmTVModle			   emTvModle;  //电视机型号   add for B4 ---2015/2/4
    
	public:
		tagTCentreTVCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreTVCfg) );
		}
		
}TCentreTVCfg;

//中控窗帘信息
typedef struct tagTCentreCurInfo
{
	BOOL			bCurOpen;
	u8				byCurNum;
	TCentreCurName  tCenCurName[MAX_CURTAIN_NUM];
	public:
		tagTCentreCurInfo()
		{
			memset( this, 0, sizeof(struct tagTCentreCurInfo) );
		}

}TCentreCurInfo;

//全景摄像机预置位名
typedef struct tagTPanCamName
{
    s8  achPanCamName[MAX_PANCAMNAME_LEN];
	public:
		tagTPanCamName()
		{
			memset( this, 0, sizeof(struct tagTPanCamName) );
		}
		
}TPanCamName;
//每个摄像机一组预置位最大为16个
typedef struct tagTPanCamGroupName
{
    TPanCamName  tPanCamName[MAX_PRESET_NUM];
	public:
		tagTPanCamGroupName()
		{
			memset( this, 0, sizeof(struct tagTPanCamGroupName) );
		}
		
}TPanCamGroupName;

//全景摄像机信息
typedef struct tagTPanCamInfo
{
	BOOL			  bPanCamOpen[MAX_PAN_NUM]; //全景摄像机状态
	u8				  byPanCamNum;              //全景摄像机总数
	TPanCamGroupName  tPCamGroupName[MAX_PAN_NUM];       
	public:
		tagTPanCamInfo()
		{
			memset( this, 0, sizeof(struct tagTPanCamInfo) );
		}
		
}TPanCamInfo;

//end add

//双流适配设置
typedef struct tagTTPVAdapterInfo
{
	BOOL    bStartAdapter; //是否开启双流适配
	u32     dwProfile;    //Hp or BP
	u32     dwWidth; 	 //适配分辨率宽度
	u32     dwHeight;	 //适配分辨率高度
	u32     dwFramerate; //适配帧率
	public:
		tagTTPVAdapterInfo(){memset(this,0,sizeof(struct tagTTPVAdapterInfo));}
}TTPVAdapterInfo;

#endif //_h_cnstruct_h__