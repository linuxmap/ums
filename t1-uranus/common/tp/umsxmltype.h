#ifndef _LOCAL_XML_TYPE_H_
#define _LOCAL_XML_TYPE_H_

#include "tpcommonxmltype.h"

const char XmlLocalTypeVersion[] = "2018-8-8 11:27:36";

//Local Data struct type begin
enum EmXDataLocalType
{
	emx_TUmsHandle = _placeholder_emxTpStructTypeend, //Local数据结构类型数据开始,紧接Tp结构体结束
	emx_TRegCfg,
	emx_TUmsSipRegCfg,
	emx_TCnsRegRetResult,
	emx_TPollInfoNtf,
	emx_TEpPathKey,
	emx_TEpKey,
	emx_TEpKeyEx,
	emx_TCheckIFrameBase,
	emx_TIFrameBySrc,
	emx_TIFrameTwoRcvPort,
	emx_TIFrameSndBySrc,
	emx_TUmsDsData,
	emx_TUmsNetBuf,
	emx_TConfNodeCallUpdateTr,
	emx_TConfNodeCallUpdateTrList,
	emx_TConfNodeChanUpdateTr,
	emx_TConfNodeChanUpdateTrList,
	emx_TConfNodeDelTrList,
	emx_TSpeakerCapTr,
	emx_TPollCmdTr,
	emx_TPollAckTr,
	emx_TViewCmdTr,
	emx_TViewAckTr,
	emx_TCascadeOpenChanCmd,
	emx_TCascadeOpenChanAck,
	emx_TAudMixEpCmdTr,
	emx_TAudMixEpAckTr,
	emx_TChairInfoTr,
	emx_TMuteRmtEpCmd,
	emx_TMuteRmtEpInd,
	emx_TQuietRmtEpCmd,
	emx_TQuietRmtEpInd,
	emx_TDropEpCmd,
	emx_TTvMonitorCmdTr,
	emx_TTvMonitorIndTr,
	emx_TAskKeyByScreenTr,
	emx_TFlowControl,
	emx_TUmsCallInfo,
	emx_TChanNetPara,
	emx_TUmsVidCapParam,
	emx_TUmsAudCap,
	emx_TUmsNodeCapset,
	emx_TUmsDualCapset,
	emx_TUmsDualCapsetMc,
	emx_TMakeCallPara,
	emx_TTPConfInfoNtfy,
	emx_TCnsSpeakerAdjust,
	emx_TEqpRes,
	emx_TModelProp,
	emx_TUmsStackCallCfg,
	emx_TUmsMediatransCfg,
	emx_TUmsNetbufCfg,
	emx_TDualInfoTr,
	emx_TDualInfoAckTr,
	emx_TDualRequestAckTr,
	emx_TAudChanAck,
	emx_TAudChanCmd,
	emx_TVidUpAddr,
	emx_TVidDownAddr,
	emx_TVidChanCmd,
	emx_TVidChanAck,
	emx_TDiscussObjInfo,
	emx_TDiscussEpAudInfo,
	emx_TDiscussCasecadeNtfy,
	emx_TDisScreenStat,
	emx_TDisAskKeyFrame,
	emx_TTPBrdRegInfo,
	emx_TTPMpu2CfgAck,
	emx_THduCfgAck,
	emx_TTPVmpReg,
	emx_TTPBasReg,
	emx_TTPBasRegAck,
	emx_TTPBasStatNtfy,
	emx_TTPBasChnStatNtfy,
	emx_TTPBasRetInfo,
	emx_TTPBasNAck,
	emx_THduRegInfo,
	emx_THduRegCfgAck,
	emx_TBrdVersion,
	emx_TBrdUpInfo,
	emx_TUpRecPlayState,
	emx_TReqAddrInfo,
	emx_TGetVidBaseInfo,
	emx_TGetVidInfo,
	emx_TGetVidInfoRes,
	emx_TStopGetVid,
	emx_TIFrameSndDis,
	emx_TIpmaskinfo,
	emx_TRollCallEpNodeInfo,
	emx_TRollCallCasecadeNtfy,
	emx_TUmsMcuChan,
	emx_TUmsMcuRegUnReg,
	emx_TUmsMcuRosterItem,
	emx_TUmsMcuRosterList,
	emx_TUmcMcuPart,
	emx_TMcuEpCmd,
	emx_TUmsMcuPartList,
	emx_TMcuSpeakerStausNty,
	emx_TMcuSpyReq,
	emx_TFeccMtInfo,
	emx_TEpVidFeccInfo,
	emx_TConfEpVidFeccList,
	emx_TEpStatusInfo,
	emx_TTelnetFtpStatus,
	emx_TBrdSwitchInfo,
_placeholder_emxDataTypeEnd = emxDataTypeEnd, //类型定义结束
};
//Local Data struct type end

namespace UmsTpmsg {
 
#define TpEnumIdString(type, index) index, GetTpEnumString(emx_##type, index)
#define TpEnumString(type, index) GetTpEnumString(emx_##type, index)
s8* GetTpEnumString(u16 wType, u16 wIndex);
TXDATAINFO** CombineEnumDateInfo(void);
TXDATAINFO** CombineStructDateInfo(void);
void CombineEnumXDescripTbl(void);


} //namespace UmsTpmsg
#endif //_LOCAL_XML_TYPE_H_
