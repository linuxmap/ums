/*===========================================================================================
模块名：meetingtemplate
文件名   : tpdata.h                                                      
相关文件 :                                                                 
实现功能 : 会议模版变量定义及默认初始化
作者：胡子龙
版权：
----------------------------------------------------------------------------------------------
修改记录：
日期            版本            修改人            走读人         修改记录
2011-7-25       v1.0            胡子龙                           创建

==============================================================================================*/
#ifndef TPDATA_H
#define TPDATA_H


#ifdef   _VXWORKS_
	#include <inetlib.h>
	#include <semlib.h>
	#include <iolib.h>
	#include <dosfslib.h>
	#include <usrlib.h>
	#include "brddrvlib.h"
#endif

#ifdef _LINUX_
#include "brdwrapper.h"
#include "nipwrapper.h"
#endif


#include "tpstruct.h"
#include "tplog.h"


/*SECTION值*/

//有几个模板可用
const s8 validTpNum[] = "validTpNum";
const s8 validTpNumKey[] = "validTpNumKey";
const s8 validSeq_[] = "validSeq_";
const s8 template_[] = "template_";



//会议名称
const s8 tpMeetingName[] = "tpMeetingName";
//会议E164
const s8 tpE164[] = "tpE164";
//会议码率
const s8 tpConfBitRate[] = "tpConfBitRate";

const s8 tpConfDualBitRate[] = "tpConfDualBitRate";

const s8 tpConfUpBandWid[] = "tpConfUpBandWid";

const s8 tpConfDownBandWid[] = "tpConfDownBandWid";


//开始时间
const s8 tpStartTime[] = "tpStartTime";

//加密模式
const s8 tpEncryptType[] = "tpEncryptType";
const s8 tpDefaultEncrypt[] = "tpDefaultEncrypt";
const s8 tpEncryptKey[] = "tpEncryptKey";
//画面合成信息


//呼叫数量
const s8 tpEpAddrNum[] = "tpEpAddrNum";
//与会端点ID
const s8 tpEpAddrID_[] = "tpEpAddrID_";
//是否是别名+IP呼叫
const s8 tpIsAliasIP_[] = "tpIsAliasIP_";
//与会端点别名
const s8 tpEpAddrAlias_[] = "tpEpAddrAlias_";
//与会端点别名类型
const s8 tpEpAddrAliasType_[] = "tpEpAddrAliasType_";
//E164
const s8 tpEpAddrE164_[] = "tpEpAddrE164_";
//与会端点E164类型
const s8 tpEpAddrE164Type_[] = "tpEpAddrE164Type_";
//与会端点呼叫类型
const s8 toEpAddrCallType_[] = "tpEpAddrCallType_";
//IP
const s8 tpEpAddrIP_[] = "tpEpAddrIP_";
//与会端点IP类型
const s8 tpEpAddrIPType_[] = "tpEpAddrIPType_";
//讨论会场ID数组
const s8 tpAudMixID_[] = "tpAudMixID_";
//讨论开关
const s8 tpDiscussOn[] = "tpDiscussOn";
//讨论语音激励开关
const s8 tpDiscussVacOn[] = "tpDiscussVacOn";
//轮询间隔
const s8 tpTurnInterval[] = "tpTurnInterval";
//参与轮询的数量
const s8 tpTurnNum[] = "tpTurnNum";
//轮询列表ID数组
const s8 tpTurnID_[] = "tpTurnID_";
//轮询开关
const s8 tpTurnOn[] = "tpTurnOn";
//音频数量
const s8 tmAudioNum[] = "tpAudioNum";
//音频格式
const s8 tpAudioFormat_[] = "tpAudioFormat_";
//音频频率
const s8 tpAudioFreq_[] = "tpAudioFreq_";
//主音频格式
const s8 tpAudioReservel_[] = "tpAudioReservel_";
//主视频数量
const s8 tpMainVidNum[] = "tpMainVidNum";
//辅视频数量
const s8 tpMinorVidNum[] = "tpMinorVidNum";
//主视频分辨率
const s8 tpVideoMainRes_[] = "tpMainVideoRes_";
//辅视频分辨率
const s8 tpVideoMinorRes_[] = "tpMinorVideoRes_";
//主视频格式画质级别
const s8 tpMainVideoLvl_[] = "tpMainVideoLvl_";
//辅视频格式画质级别
const s8 tpMinorVideoLvl_[] = "tpMinorVideoLvl_";
//主视频帧率
const s8 tpMainVideoFrame_[] = "tpMainVideoFrame_";
//辅视频帧率
const s8 tpMinorVideoFrame_[] = "tpMinorVideoFrame_";

//合成预案类型
const s8 tpVmpPlanStyle[] = "tpVmpPlanStyle";
//合成预案Ep数量
const s8 tpVmpPlanEpNum[] = "tpVmpPlanEpNum";
//发言人跟随，双流跟随
const s8 tpVmpPlanSpeakIndex[] = "tpVmpPlanSpeakIndex";
const s8 tpVmpPlanDualIndex[] = "tpVmpPlanDualIndex";
//合成预案Ep列表
const s8 tpVmpPlanEpAlias_[] = "tpVmpPlanEpAlias_";
const s8 tpVmpPlanScrIndex_[] =  "tpVmpPlanScrIndex_";
//会场呼叫类型
const s8 tpEpCallProtocol_[] =  "tpEpCallProtocol_";

//定义配置数据
typedef struct tagAllTpConfigData
{

	TConfTemplateLocal m_tTpConfTemplate;    //会议模版

}TALLTpConfigData;


//定义存放模板数据和对应数组索引的结构体
typedef struct tagIndexALLTpConfigData
{
	TALLTpConfigData m_tALLTpConfigData;   //配置数据
	u16 m_wIndex;                         //索引值
}TIndexALLTpConfigData;


typedef struct tagTControlData
{
	u16 m_wValidNum;                           //有效值
	BOOL m_abValidSeq[TP_CONFTEMPLATE_MAXNUM];  //文件有效与否
}TControlData;


#endif
