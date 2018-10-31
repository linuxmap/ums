#include "tpcommonxmlstruct.h"
#include "umsxmltype.h"
#include "tpstruct.h"
#include "umscommonstruct.h"

const char XmlLocalStructVersion[] = "2018-8-8 11:27:36";

#define XML_LOCAL_TYPE_NUM      0
#define XML_LOCAL_STRUCT_NUM    106

namespace UmsTpmsg {


TXDATAINFO* g_tLocalEnumDataInfo[]={
	(TXDATAINFO*)NULL
};

//TUmsHandle
TYPESTRUCT_BEGIN( TUmsHandle )
    TYPESTRUCT_MEMBER( TUmsHandle, u32, handPaCall )
    TYPESTRUCT_MEMBER( TUmsHandle, u32, handAppCall )
    TYPESTRUCT_MEMBER( TUmsHandle, s32, handPaChan )
    TYPESTRUCT_MEMBER( TUmsHandle, u32, m_dwAdapteID )
    TYPESTRUCT_MEMBER( TUmsHandle, EmTpConfProtocol, m_emProtocol )
TYPESTRUCT_END(  TUmsHandle )

//TRegCfg
TYPESTRUCT_BEGIN( TRegCfg )
    TYPESTRUCT_MEMBER( TRegCfg, BOOL, m_bUsed )
    TYPESTRUCT_MEMBER( TRegCfg, TTPAlias, m_tAlias )
    TYPESTRUCT_MEMBER( TRegCfg, s8, m_achEPID )
    TYPESTRUCT_MEMBER( TRegCfg, s32, m_nTimeToLive )
    TYPESTRUCT_MEMBER( TRegCfg, TTPTransAddr, m_tLocalAddress )
    TYPESTRUCT_MEMBER( TRegCfg, TTPTransAddr, m_tGKAddress )
    TYPESTRUCT_MEMBER( TRegCfg, u32, m_dwQTId )
TYPESTRUCT_END(  TRegCfg )

//TUmsSipRegCfg
TYPESTRUCT_BEGIN( TUmsSipRegCfg )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, BOOL, bUsed )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, u32_ip, dwRegIP )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, u16, wRegPort )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, s8, achRegDomain )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, u16, wExpire )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, s8, achHostDomain )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, TTPTransAddr, m_atAdaptAddr )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, s8, achCompileTm )
    TYPESTRUCT_MEMBER( TUmsSipRegCfg, u32, m_dwQTId )
TYPESTRUCT_END(  TUmsSipRegCfg )

//TCnsRegRetResult
TYPESTRUCT_BEGIN( TCnsRegRetResult )
    TYPESTRUCT_MEMBER( TCnsRegRetResult, EmTpCnsRegUms, m_emReson )
    TYPESTRUCT_MEMBER( TCnsRegRetResult, EmTpRegType, m_emRegType )
TYPESTRUCT_END(  TCnsRegRetResult )

//TPollInfoNtf
TYPESTRUCT_BEGIN( TPollInfoNtf )
    TYPESTRUCT_MEMBER( TPollInfoNtf, TTPAlias, m_tAlias )
    TYPESTRUCT_MEMBER( TPollInfoNtf, u32, m_nScreenNum )
TYPESTRUCT_END(  TPollInfoNtf )

//TEpPathKey
TYPESTRUCT_BEGIN( TEpPathKey )
    TYPESTRUCT_MEMBER( TEpPathKey, s8, m_szEpID )
TYPESTRUCT_END(  TEpPathKey )

//TEpKey
TYPESTRUCT_BEGIN( TEpKey )
    TYPESTRUCT_MEMBER( TEpKey, u16, m_wEpID )
TYPESTRUCT_END(  TEpKey )

//TEpKeyEx
TYPESTRUCT_BEGIN( TEpKeyEx )
    TYPESTRUCT_MEMBER( TEpKeyEx, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TEpKeyEx, s8, m_achReserve )
TYPESTRUCT_END(  TEpKeyEx )

//TCheckIFrameBase
TYPESTRUCT_BEGIN( TCheckIFrameBase )
    TYPESTRUCT_MEMBER( TCheckIFrameBase, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TCheckIFrameBase, u16, m_wExpires )
    TYPESTRUCT_MEMBER( TCheckIFrameBase, EmTpIFrameCheckType, m_emType )
    TYPESTRUCT_MEMBER( TCheckIFrameBase, u32_ip, m_dwIP )
    TYPESTRUCT_MEMBER( TCheckIFrameBase, u16, m_wPort )
TYPESTRUCT_END(  TCheckIFrameBase )

//TIFrameBySrc
TYPESTRUCT_BEGIN( TIFrameBySrc )
    TYPESTRUCT_MEMBER( TIFrameBySrc, u16, m_wChanIndex )
    TYPESTRUCT_MEMBER( TIFrameBySrc, u16, m_wNewSpeakerID )
    TYPESTRUCT_MEMBER( TIFrameBySrc, u32_ip, m_dwOldIP )
    TYPESTRUCT_MEMBER( TIFrameBySrc, u32_ip, m_dwNewIP )
    TYPESTRUCT_MEMBER( TIFrameBySrc, u16, m_wOldPort )
    TYPESTRUCT_MEMBER( TIFrameBySrc, u16, m_wNewPort )
    TYPESTRUCT_MEMBER( TIFrameBySrc, BOOL32, m_bUsedNew )
TYPESTRUCT_END(  TIFrameBySrc )

//TIFrameTwoRcvPort
TYPESTRUCT_BEGIN( TIFrameTwoRcvPort )
    TYPESTRUCT_MEMBER( TIFrameTwoRcvPort, u16, m_wNewPort )
    TYPESTRUCT_MEMBER( TIFrameTwoRcvPort, u16, m_wOldPort )
    TYPESTRUCT_MEMBER( TIFrameTwoRcvPort, BOOL32, m_bTrans )
    TYPESTRUCT_MEMBER( TIFrameTwoRcvPort, u16, m_wChanIndex )
    TYPESTRUCT_MEMBER( TIFrameTwoRcvPort, u16, m_wPollEp )
TYPESTRUCT_END(  TIFrameTwoRcvPort )

//TIFrameSndBySrc
TYPESTRUCT_BEGIN( TIFrameSndBySrc )
    TYPESTRUCT_MEMBER( TIFrameSndBySrc, u32_ip, m_dwCheckIp )
    TYPESTRUCT_MEMBER( TIFrameSndBySrc, u16, m_wCheckPort )
    TYPESTRUCT_MEMBER( TIFrameSndBySrc, u32_ip, m_dwDstIp )
    TYPESTRUCT_MEMBER( TIFrameSndBySrc, u16, m_wDstPort )
    TYPESTRUCT_MEMBER( TIFrameSndBySrc, u16, m_wRcvPort )
TYPESTRUCT_END(  TIFrameSndBySrc )

//TUmsDsData
TYPESTRUCT_BEGIN( TUmsDsData )
    TYPESTRUCT_MEMBER( TUmsDsData, u32, m_dwEqpNode )
    TYPESTRUCT_MEMBER( TUmsDsData, TTPTransAddr, m_tRcvFromAddr )
    TYPESTRUCT_MEMBER( TUmsDsData, TTPTransAddr, m_tSndToAddr )
    TYPESTRUCT_MEMBER( TUmsDsData, TTPTransAddr, m_tMapedAddr )
    TYPESTRUCT_MEMBER( TUmsDsData, BOOL32, m_bNeedModifySrc )
    TYPESTRUCT_MEMBER( TUmsDsData, EmSwitchType, m_emSwitchType )
    TYPESTRUCT_MEMBER( TUmsDsData, u32, m_dwSrcMediaType )
TYPESTRUCT_END(  TUmsDsData )

//TUmsNetBuf
TYPESTRUCT_BEGIN( TUmsNetBuf )
    TYPESTRUCT_MEMBER( TUmsNetBuf, TTPTransAddr, m_wSndAddr )
    TYPESTRUCT_MEMBER( TUmsNetBuf, TTPTransAddr, m_tRcvRtpAddr )
    TYPESTRUCT_MEMBER( TUmsNetBuf, TTPTransAddr, m_tRcvRtcpAddr )
    TYPESTRUCT_MEMBER( TUmsNetBuf, TTPTransAddr, m_tRmtRtcpAddr )
TYPESTRUCT_END(  TUmsNetBuf )

//TConfNodeCallUpdateTr
TYPESTRUCT_BEGIN( TConfNodeCallUpdateTr )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, TEpPathKey, m_tID )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, EmTPEndpointType, m_emEpType )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, EmTpVendorID, m_emVendorID )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, EmUmsConfNodeState, m_emCallState )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, EmCnsCallReason, m_emCallReason )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, TTpCallAddr, m_tCalledAddr )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, TTPAlias, m_tConfName )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, EmTPSipLevel, m_emLevel )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, EmTPRcvAlignType, m_enRcvAlignType )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, BOOL32, m_bMute )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, BOOL32, m_bQuiet )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, u16, m_wSpearkIndex )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTr, u16, m_wDualIndex )
TYPESTRUCT_END(  TConfNodeCallUpdateTr )

//TConfNodeCallUpdateTrList
TYPESTRUCT_BEGIN( TConfNodeCallUpdateTrList )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTrList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfNodeCallUpdateTrList, TConfNodeCallUpdateTr, m_atList )
TYPESTRUCT_END(  TConfNodeCallUpdateTrList )

//TConfNodeChanUpdateTr
TYPESTRUCT_BEGIN( TConfNodeChanUpdateTr )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TEpKey, tID )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, u16, wEpID )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, BOOL32, bChanOpen )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, BOOL32, bSmallOpenEnc )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, BOOL32, bSmallOpenDec )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, u16, wVidSnd )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, u16, wVidRcv )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, u16, wAudSnd )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, u16, wAudRcv )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsVidFormat, tVidRcv )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsAudFormat, tAudRcv )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsVidFormat, tVidSnd )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsAudFormat, tAudSnd )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsVidFormat, tDualVidRcv )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsAudFormat, tDualAudRcv )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsVidFormat, tDualVidSnd )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, TUmsAudFormat, tDualAudSnd )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, u16, awPd )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTr, BOOL32, bInPoll )
TYPESTRUCT_END(  TConfNodeChanUpdateTr )

//TConfNodeChanUpdateTrList
TYPESTRUCT_BEGIN( TConfNodeChanUpdateTrList )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTrList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfNodeChanUpdateTrList, TConfNodeChanUpdateTr, m_atList )
TYPESTRUCT_END(  TConfNodeChanUpdateTrList )

//TConfNodeDelTrList
TYPESTRUCT_BEGIN( TConfNodeDelTrList )
    TYPESTRUCT_MEMBER( TConfNodeDelTrList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfNodeDelTrList, TEpKey, m_atList )
TYPESTRUCT_END(  TConfNodeDelTrList )

//TSpeakerCapTr
TYPESTRUCT_BEGIN( TSpeakerCapTr )
    TYPESTRUCT_MEMBER( TSpeakerCapTr, BOOL32, m_bIsSpeaker )
    TYPESTRUCT_MEMBER( TSpeakerCapTr, u16, m_wSpeakerID )
    TYPESTRUCT_MEMBER( TSpeakerCapTr, u16, m_wVidSnd )
    TYPESTRUCT_MEMBER( TSpeakerCapTr, u16, m_wAudSnd )
    TYPESTRUCT_MEMBER( TSpeakerCapTr, TTPAlias, m_tEpAlias )
    TYPESTRUCT_MEMBER( TSpeakerCapTr, u16, m_wSpeakerIndex )
TYPESTRUCT_END(  TSpeakerCapTr )

//TPollCmdTr
TYPESTRUCT_BEGIN( TPollCmdTr )
    TYPESTRUCT_MEMBER( TPollCmdTr, TTPMediaTransAddr, m_tAddr )
    TYPESTRUCT_MEMBER( TPollCmdTr, u16, m_wBitrate )
    TYPESTRUCT_MEMBER( TPollCmdTr, u16, m_wInterval )
TYPESTRUCT_END(  TPollCmdTr )

//TPollAckTr
TYPESTRUCT_BEGIN( TPollAckTr )
    TYPESTRUCT_MEMBER( TPollAckTr, u16, m_wReason )
    TYPESTRUCT_MEMBER( TPollAckTr, TTPMediaTransAddr, m_tAddr )
TYPESTRUCT_END(  TPollAckTr )

//TViewCmdTr
TYPESTRUCT_BEGIN( TViewCmdTr )
    TYPESTRUCT_MEMBER( TViewCmdTr, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TViewCmdTr, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TViewCmdTr, u32, m_dwType )
    TYPESTRUCT_MEMBER( TViewCmdTr, u16, m_wSrcScreenIndex )
    TYPESTRUCT_MEMBER( TViewCmdTr, TTPMediaTransAddr, m_atAddr )
    TYPESTRUCT_MEMBER( TViewCmdTr, BOOL32, m_abOpen )
    TYPESTRUCT_MEMBER( TViewCmdTr, TTPMediaTransAddr, m_atAudAddr )
    TYPESTRUCT_MEMBER( TViewCmdTr, TTPMediaTransAddr, m_tMixAddr )
    TYPESTRUCT_MEMBER( TViewCmdTr, BOOL32, m_bViewSpeaker )
    TYPESTRUCT_MEMBER( TViewCmdTr, BOOL32, m_bNeedBas )
TYPESTRUCT_END(  TViewCmdTr )

//TViewAckTr
TYPESTRUCT_BEGIN( TViewAckTr )
    TYPESTRUCT_MEMBER( TViewAckTr, EmTPViewResult, m_emRes )
    TYPESTRUCT_MEMBER( TViewAckTr, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TViewAckTr, TTPMediaTransAddr, m_atAddr )
    TYPESTRUCT_MEMBER( TViewAckTr, BOOL32, m_abOpen )
    TYPESTRUCT_MEMBER( TViewAckTr, TTPMediaTransAddr, m_atAudAddr )
    TYPESTRUCT_MEMBER( TViewAckTr, TTPMediaTransAddr, m_tMixAddr )
TYPESTRUCT_END(  TViewAckTr )

//TCascadeOpenChanCmd
TYPESTRUCT_BEGIN( TCascadeOpenChanCmd )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, TTPMediaTransAddr, m_atVidAddr )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, TTPMediaTransAddr, m_atAudAddr )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, TTPMediaTransAddr, m_tMixAudAddr )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, TTPMediaTransAddr, m_tDisSingleVid )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, TTPMediaTransAddr, m_tDisSingleAud )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, BOOL32, m_abVidOpen )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, BOOL32, m_abAudOpen )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, BOOL32, m_bMixAudOpen )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, BOOL32, m_bDisSingleVid )
    TYPESTRUCT_MEMBER( TCascadeOpenChanCmd, BOOL32, m_bDisSingleAud )
TYPESTRUCT_END(  TCascadeOpenChanCmd )

//TCascadeOpenChanAck
TYPESTRUCT_BEGIN( TCascadeOpenChanAck )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, TTPMediaTransAddr, m_atVidAddr )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, TTPMediaTransAddr, m_atAudAddr )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, TTPMediaTransAddr, m_tMixAudAddr )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, TTPMediaTransAddr, m_tDisSingleVid )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, TTPMediaTransAddr, m_tDisSingleAud )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, BOOL32, m_abVidOpen )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, BOOL32, m_abAudOpen )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, BOOL32, m_bMixAudOpen )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, BOOL32, m_bDisSingleVid )
    TYPESTRUCT_MEMBER( TCascadeOpenChanAck, BOOL32, m_bDisSingleAud )
TYPESTRUCT_END(  TCascadeOpenChanAck )

//TAudMixEpCmdTr
TYPESTRUCT_BEGIN( TAudMixEpCmdTr )
    TYPESTRUCT_MEMBER( TAudMixEpCmdTr, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAudMixEpCmdTr, u16, m_wLocalID )
    TYPESTRUCT_MEMBER( TAudMixEpCmdTr, TTPTransAddr, m_tRtpAddr )
    TYPESTRUCT_MEMBER( TAudMixEpCmdTr, TTPTransAddr, m_tBackRtpAddr )
TYPESTRUCT_END(  TAudMixEpCmdTr )

//TAudMixEpAckTr
TYPESTRUCT_BEGIN( TAudMixEpAckTr )
    TYPESTRUCT_MEMBER( TAudMixEpAckTr, u16, m_wReason )
    TYPESTRUCT_MEMBER( TAudMixEpAckTr, u16, m_wLocalID )
    TYPESTRUCT_MEMBER( TAudMixEpAckTr, TTPTransAddr, m_tRtpAddr )
    TYPESTRUCT_MEMBER( TAudMixEpAckTr, TTPTransAddr, m_tBackRtpAddr )
TYPESTRUCT_END(  TAudMixEpAckTr )

//TChairInfoTr
TYPESTRUCT_BEGIN( TChairInfoTr )
    TYPESTRUCT_MEMBER( TChairInfoTr, u16, m_wSpeakerIndex )
TYPESTRUCT_END(  TChairInfoTr )

//TMuteRmtEpCmd
TYPESTRUCT_BEGIN( TMuteRmtEpCmd )
    TYPESTRUCT_MEMBER( TMuteRmtEpCmd, BOOL32, m_bMute )
    TYPESTRUCT_MEMBER( TMuteRmtEpCmd, u16, m_wEpID )
TYPESTRUCT_END(  TMuteRmtEpCmd )

//TMuteRmtEpInd
TYPESTRUCT_BEGIN( TMuteRmtEpInd )
    TYPESTRUCT_MEMBER( TMuteRmtEpInd, BOOL32, m_bMute )
    TYPESTRUCT_MEMBER( TMuteRmtEpInd, TEpKey, m_tKeyID )
TYPESTRUCT_END(  TMuteRmtEpInd )

//TQuietRmtEpCmd
TYPESTRUCT_BEGIN( TQuietRmtEpCmd )
    TYPESTRUCT_MEMBER( TQuietRmtEpCmd, BOOL32, m_bQuiet )
    TYPESTRUCT_MEMBER( TQuietRmtEpCmd, u16, m_wEpID )
TYPESTRUCT_END(  TQuietRmtEpCmd )

//TQuietRmtEpInd
TYPESTRUCT_BEGIN( TQuietRmtEpInd )
    TYPESTRUCT_MEMBER( TQuietRmtEpInd, BOOL32, m_bQuiet )
    TYPESTRUCT_MEMBER( TQuietRmtEpInd, TEpKey, m_tKeyID )
TYPESTRUCT_END(  TQuietRmtEpInd )

//TDropEpCmd
TYPESTRUCT_BEGIN( TDropEpCmd )
    TYPESTRUCT_MEMBER( TDropEpCmd, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TDropEpCmd, BOOL32, m_bDel )
TYPESTRUCT_END(  TDropEpCmd )

//TTvMonitorCmdTr
TYPESTRUCT_BEGIN( TTvMonitorCmdTr )
    TYPESTRUCT_MEMBER( TTvMonitorCmdTr, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TTvMonitorCmdTr, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTvMonitorCmdTr, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( TTvMonitorCmdTr, TTPMediaTransAddr, m_tVidAddr )
    TYPESTRUCT_MEMBER( TTvMonitorCmdTr, TTPMediaTransAddr, m_tAudAddr )
TYPESTRUCT_END(  TTvMonitorCmdTr )

//TTvMonitorIndTr
TYPESTRUCT_BEGIN( TTvMonitorIndTr )
    TYPESTRUCT_MEMBER( TTvMonitorIndTr, BOOL32, m_bAccept )
    TYPESTRUCT_MEMBER( TTvMonitorIndTr, u16, m_wIndex )
    TYPESTRUCT_MEMBER( TTvMonitorIndTr, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTvMonitorIndTr, u16, m_wScreenNum )
    TYPESTRUCT_MEMBER( TTvMonitorIndTr, TTPMediaTransAddr, m_tVidAddr )
    TYPESTRUCT_MEMBER( TTvMonitorIndTr, TTPMediaTransAddr, m_tAudAddr )
TYPESTRUCT_END(  TTvMonitorIndTr )

//TAskKeyByScreenTr
TYPESTRUCT_BEGIN( TAskKeyByScreenTr )
    TYPESTRUCT_MEMBER( TAskKeyByScreenTr, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TAskKeyByScreenTr, u16, m_wScreenIndex )
    TYPESTRUCT_MEMBER( TAskKeyByScreenTr, BOOL32, m_bReqBySys )
    TYPESTRUCT_MEMBER( TAskKeyByScreenTr, u32, m_dwAskType )
    TYPESTRUCT_MEMBER( TAskKeyByScreenTr, u32, m_dwRervse1 )
    TYPESTRUCT_MEMBER( TAskKeyByScreenTr, u32, m_dwRervse2 )
TYPESTRUCT_END(  TAskKeyByScreenTr )

//TFlowControl
TYPESTRUCT_BEGIN( TFlowControl )
    TYPESTRUCT_MEMBER( TFlowControl, TEpKey, m_tEpKey )
    TYPESTRUCT_MEMBER( TFlowControl, u16, m_wEncNo )
    TYPESTRUCT_MEMBER( TFlowControl, u16, m_wBand )
    TYPESTRUCT_MEMBER( TFlowControl, u32, m_dwOpr )
TYPESTRUCT_END(  TFlowControl )

//TUmsCallInfo
TYPESTRUCT_BEGIN( TUmsCallInfo )
    TYPESTRUCT_MEMBER( TUmsCallInfo, EmTPEndpointType, m_emSrcEpType )
    TYPESTRUCT_MEMBER( TUmsCallInfo, EmTpCallMode, m_emTpCallType )
    TYPESTRUCT_MEMBER( TUmsCallInfo, EmTpConfProtocol, m_emTpProtocol )
    TYPESTRUCT_MEMBER( TUmsCallInfo, EmTpVendorID, m_emVendorID )
    TYPESTRUCT_MEMBER( TUmsCallInfo, u16, m_wBitRate )
    TYPESTRUCT_MEMBER( TUmsCallInfo, EmTPSipLevel, m_emLevel )
    TYPESTRUCT_MEMBER( TUmsCallInfo, TTpCallAddr, m_tDestAddr )
    TYPESTRUCT_MEMBER( TUmsCallInfo, TTpCallAddr, m_tSrcAddr )
    TYPESTRUCT_MEMBER( TUmsCallInfo, u8, m_byVer )
    TYPESTRUCT_MEMBER( TUmsCallInfo, BOOL32, m_bIsCreatConf )
    TYPESTRUCT_MEMBER( TUmsCallInfo, s8, m_acPrdutID )
    TYPESTRUCT_MEMBER( TUmsCallInfo, TTPEncrypt, m_tEncrypt )
    TYPESTRUCT_MEMBER( TUmsCallInfo, BOOL32, m_bIsCasecadeMcuOn )
TYPESTRUCT_END(  TUmsCallInfo )

//TChanNetPara
TYPESTRUCT_BEGIN( TChanNetPara )
    TYPESTRUCT_MEMBER( TChanNetPara, BOOL32, m_bIsChanOn )
    TYPESTRUCT_MEMBER( TChanNetPara, TTPMediaTransAddr, m_tChanAddr )
    TYPESTRUCT_MEMBER( TChanNetPara, s32, m_tPAHandle )
TYPESTRUCT_END(  TChanNetPara )

//TUmsVidCapParam
TYPESTRUCT_BEGIN( TUmsVidCapParam )
    TYPESTRUCT_MEMBER( TUmsVidCapParam, TUmsVidFormat, m_tHp )
    TYPESTRUCT_MEMBER( TUmsVidCapParam, TUmsVidFormat, m_tBp )
    TYPESTRUCT_MEMBER( TUmsVidCapParam, u16, m_wDynamicPayload )
TYPESTRUCT_END(  TUmsVidCapParam )

//TUmsAudCap
TYPESTRUCT_BEGIN( TUmsAudCap )
    TYPESTRUCT_MEMBER( TUmsAudCap, u16, m_wAudFmtNum )
    TYPESTRUCT_MEMBER( TUmsAudCap, TUmsAudFormat, m_atAudFmt )
    TYPESTRUCT_MEMBER( TUmsAudCap, u16, m_wBitrate )
TYPESTRUCT_END(  TUmsAudCap )

//TUmsNodeCapset
TYPESTRUCT_BEGIN( TUmsNodeCapset )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, u16, m_wVidEncNum )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, u16, m_wVidDecNum )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, u16, m_wAudEncNum )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, u16, m_wAudDecNum )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_atVidEnc )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_atVidDec )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_atAudEnc )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_atAudDec )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_atSmallVidEnc )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_atSmallVidDec )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_tAudMixEnc )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TChanNetPara, m_tAudMixDec )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TTPEncrypt, m_tEncrypt )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TUmsVidCapParam, m_tVidRcvCap )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TUmsVidCapParam, m_tVidSndCap )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TUmsAudCap, m_tAudRcvCap )
    TYPESTRUCT_MEMBER( TUmsNodeCapset, TUmsAudCap, m_tAudSndCap )
TYPESTRUCT_END(  TUmsNodeCapset )

//TUmsDualCapset
TYPESTRUCT_BEGIN( TUmsDualCapset )
    TYPESTRUCT_MEMBER( TUmsDualCapset, TChanNetPara, m_tVid )
    TYPESTRUCT_MEMBER( TUmsDualCapset, TChanNetPara, m_tAud )
    TYPESTRUCT_MEMBER( TUmsDualCapset, EmTPEncryptType, m_byEncryptBits )
    TYPESTRUCT_MEMBER( TUmsDualCapset, TTpEncryptKey, m_tEnc )
    TYPESTRUCT_MEMBER( TUmsDualCapset, u16, m_byFECBits )
    TYPESTRUCT_MEMBER( TUmsDualCapset, u16, m_wMaxBitRate )
    TYPESTRUCT_MEMBER( TUmsDualCapset, TTPVideoCap, m_tVidCap )
    TYPESTRUCT_MEMBER( TUmsDualCapset, TTPAudCap, m_tAudCap )
TYPESTRUCT_END(  TUmsDualCapset )

//TUmsDualCapsetMc
TYPESTRUCT_BEGIN( TUmsDualCapsetMc )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, TChanNetPara, m_tVidEnc )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, TChanNetPara, m_tVidDec )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, TChanNetPara, m_tAudEnc )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, TChanNetPara, m_tAudDec )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, u16, m_wMaxBitRate )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, TUmsVidCapParam, m_tVidRcvCap )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, TUmsVidCapParam, m_tVidSndCap )
    TYPESTRUCT_MEMBER( TUmsDualCapsetMc, TUmsAudCap, m_tAudCap )
TYPESTRUCT_END(  TUmsDualCapsetMc )

//TMakeCallPara
TYPESTRUCT_BEGIN( TMakeCallPara )
    TYPESTRUCT_MEMBER( TMakeCallPara, TUmsCallInfo, m_tCallInfo )
    TYPESTRUCT_MEMBER( TMakeCallPara, TUmsNodeCapset, m_tCapSet )
    TYPESTRUCT_MEMBER( TMakeCallPara, TUmsDualCapsetMc, m_tDualCapSet )
TYPESTRUCT_END(  TMakeCallPara )

//TTPConfInfoNtfy
TYPESTRUCT_BEGIN( TTPConfInfoNtfy )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, u16, m_wConfID )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, time_t, m_tBeginTime )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, TTPName, m_tConf )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, TTPName, m_tChair )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, TTPName, m_tSpeak )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, u16, m_wChairVidSndCap )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, u16, m_wChairAudSndCap )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, BOOL32, m_bMixMotive )
    TYPESTRUCT_MEMBER( TTPConfInfoNtfy, BOOL32, m_bSpeakOnline )
TYPESTRUCT_END(  TTPConfInfoNtfy )

//TCnsSpeakerAdjust
TYPESTRUCT_BEGIN( TCnsSpeakerAdjust )
    TYPESTRUCT_MEMBER( TCnsSpeakerAdjust, TEpKey, m_tKey )
    TYPESTRUCT_MEMBER( TCnsSpeakerAdjust, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TCnsSpeakerAdjust, u16, m_wSpeakerIndex )
TYPESTRUCT_END(  TCnsSpeakerAdjust )

//TEqpRes
TYPESTRUCT_BEGIN( TEqpRes )
    TYPESTRUCT_MEMBER( TEqpRes, u32, m_dwEqpNode )
    TYPESTRUCT_MEMBER( TEqpRes, u32, m_dwEqpInst )
    TYPESTRUCT_MEMBER( TEqpRes, u32, m_dwEqpIp )
    TYPESTRUCT_MEMBER( TEqpRes, u16, m_wEqpIndex )
TYPESTRUCT_END(  TEqpRes )

//TModelProp
TYPESTRUCT_BEGIN( TModelProp )
    TYPESTRUCT_MEMBER( TModelProp, EMEqpType, m_wEqpType )
    TYPESTRUCT_MEMBER( TModelProp, s8, m_achAlias )
    TYPESTRUCT_MEMBER( TModelProp, u32, m_dwCapSet )
    TYPESTRUCT_MEMBER( TModelProp, u32_ip, m_dwEqpIP )
    TYPESTRUCT_MEMBER( TModelProp, u16, m_wVersion )
TYPESTRUCT_END(  TModelProp )

//TUmsStackCallCfg
TYPESTRUCT_BEGIN( TUmsStackCallCfg )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, u32, m_dwUmsNode )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, u16, m_wUmsIndex )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, u16, m_wCallingPort )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, u16, m_wMaxCallNum )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, u32, m_dwKeepAliveTime )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, u32_ip, m_dwRegIP )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, u16, m_wRegPort )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, s32, m_nProductIdSize )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, s8, m_abyProductId )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, s32, m_nVerIdSize )
    TYPESTRUCT_MEMBER( TUmsStackCallCfg, s8, m_abyVersionId )
TYPESTRUCT_END(  TUmsStackCallCfg )

//TUmsMediatransCfg
TYPESTRUCT_BEGIN( TUmsMediatransCfg )
    TYPESTRUCT_MEMBER( TUmsMediatransCfg, u32, m_dwUmsNode )
    TYPESTRUCT_MEMBER( TUmsMediatransCfg, u16, m_wUmsIndex )
TYPESTRUCT_END(  TUmsMediatransCfg )

//TUmsNetbufCfg
TYPESTRUCT_BEGIN( TUmsNetbufCfg )
    TYPESTRUCT_MEMBER( TUmsNetbufCfg, u32, m_dwUmsNode )
    TYPESTRUCT_MEMBER( TUmsNetbufCfg, u16, m_wUmsIndex )
TYPESTRUCT_END(  TUmsNetbufCfg )

//TDualInfoTr
TYPESTRUCT_BEGIN( TDualInfoTr )
    TYPESTRUCT_MEMBER( TDualInfoTr, s32, m_nScreenNo )
    TYPESTRUCT_MEMBER( TDualInfoTr, TEpKey, m_tKey )
    TYPESTRUCT_MEMBER( TDualInfoTr, TUmsDualCapset, m_tDualCap )
TYPESTRUCT_END(  TDualInfoTr )

//TDualInfoAckTr
TYPESTRUCT_BEGIN( TDualInfoAckTr )
    TYPESTRUCT_MEMBER( TDualInfoAckTr, BOOL32, m_bAccept )
    TYPESTRUCT_MEMBER( TDualInfoAckTr, TDualInfoTr, m_tDualInfo )
TYPESTRUCT_END(  TDualInfoAckTr )

//TDualRequestAckTr
TYPESTRUCT_BEGIN( TDualRequestAckTr )
    TYPESTRUCT_MEMBER( TDualRequestAckTr, BOOL32, m_bAccept )
    TYPESTRUCT_MEMBER( TDualRequestAckTr, EmTPDualReason, m_dwReason )
    TYPESTRUCT_MEMBER( TDualRequestAckTr, TEpKey, m_tEpKey )
TYPESTRUCT_END(  TDualRequestAckTr )

//TAudChanAck
TYPESTRUCT_BEGIN( TAudChanAck )
    TYPESTRUCT_MEMBER( TAudChanAck, u16, m_wReason )
    TYPESTRUCT_MEMBER( TAudChanAck, TEpKey, m_tEpKey )
    TYPESTRUCT_MEMBER( TAudChanAck, TTPTransAddr, m_atBackRtcpAddr )
    TYPESTRUCT_MEMBER( TAudChanAck, TTPTransAddr, m_tMixBackRtcpAddr )
TYPESTRUCT_END(  TAudChanAck )

//TAudChanCmd
TYPESTRUCT_BEGIN( TAudChanCmd )
    TYPESTRUCT_MEMBER( TAudChanCmd, TEpKey, m_tEpKey )
    TYPESTRUCT_MEMBER( TAudChanCmd, TTPTransAddr, m_atRtpAddr )
    TYPESTRUCT_MEMBER( TAudChanCmd, TTPTransAddr, m_tMixRtpAddr )
TYPESTRUCT_END(  TAudChanCmd )

//TVidUpAddr
TYPESTRUCT_BEGIN( TVidUpAddr )
    TYPESTRUCT_MEMBER( TVidUpAddr, TTPTransAddr, m_tAddr )
    TYPESTRUCT_MEMBER( TVidUpAddr, TTPTransAddr, m_tSmallAddr )
TYPESTRUCT_END(  TVidUpAddr )

//TVidDownAddr
TYPESTRUCT_BEGIN( TVidDownAddr )
    TYPESTRUCT_MEMBER( TVidDownAddr, TTPTransAddr, m_tAddr )
    TYPESTRUCT_MEMBER( TVidDownAddr, TTPTransAddr, m_tSmallAddrL )
    TYPESTRUCT_MEMBER( TVidDownAddr, TTPTransAddr, m_tSmallAddrR )
TYPESTRUCT_END(  TVidDownAddr )

//TVidChanCmd
TYPESTRUCT_BEGIN( TVidChanCmd )
    TYPESTRUCT_MEMBER( TVidChanCmd, TEpKey, m_tEpKey )
    TYPESTRUCT_MEMBER( TVidChanCmd, TVidUpAddr, m_atUpRtp )
    TYPESTRUCT_MEMBER( TVidChanCmd, TVidDownAddr, m_atDownBackRtcp )
    TYPESTRUCT_MEMBER( TVidChanCmd, TTPTransAddr, m_atAudBackRtcp )
TYPESTRUCT_END(  TVidChanCmd )

//TVidChanAck
TYPESTRUCT_BEGIN( TVidChanAck )
    TYPESTRUCT_MEMBER( TVidChanAck, u16, m_wReason )
    TYPESTRUCT_MEMBER( TVidChanAck, TEpKey, m_tEpKey )
    TYPESTRUCT_MEMBER( TVidChanAck, TVidUpAddr, m_atUpBackRtcp )
    TYPESTRUCT_MEMBER( TVidChanAck, TVidDownAddr, m_atDownRtp )
    TYPESTRUCT_MEMBER( TVidChanAck, TTPTransAddr, m_atAudRtp )
TYPESTRUCT_END(  TVidChanAck )

//TDiscussObjInfo
TYPESTRUCT_BEGIN( TDiscussObjInfo )
    TYPESTRUCT_MEMBER( TDiscussObjInfo, u16, m_wReserve )
    TYPESTRUCT_MEMBER( TDiscussObjInfo, BOOL32, m_abIsVaild )
    TYPESTRUCT_MEMBER( TDiscussObjInfo, TTPAlias, m_atEpAlias )
TYPESTRUCT_END(  TDiscussObjInfo )

//TDiscussEpAudInfo
TYPESTRUCT_BEGIN( TDiscussEpAudInfo )
    TYPESTRUCT_MEMBER( TDiscussEpAudInfo, u16, m_awDiscussEpId )
    TYPESTRUCT_MATRIX( TDiscussEpAudInfo, u8, m_abyIsRcvNModeAud )
TYPESTRUCT_END(  TDiscussEpAudInfo )

//TDiscussCasecadeNtfy
TYPESTRUCT_BEGIN( TDiscussCasecadeNtfy )
    TYPESTRUCT_MEMBER( TDiscussCasecadeNtfy, BOOL32, m_bIsDiscussModle )
    TYPESTRUCT_MEMBER( TDiscussCasecadeNtfy, TDiscussObjInfo, m_atDiscussObj )
    TYPESTRUCT_MEMBER( TDiscussCasecadeNtfy, TDiscussEpAudInfo, m_tEpAudInfo )
TYPESTRUCT_END(  TDiscussCasecadeNtfy )

//TDisScreenStat
TYPESTRUCT_BEGIN( TDisScreenStat )
    TYPESTRUCT_MEMBER( TDisScreenStat, BOOL32, m_bInDiscard )
    TYPESTRUCT_MEMBER( TDisScreenStat, u16, m_wEpIDDst )
    TYPESTRUCT_MEMBER( TDisScreenStat, EmTPDisOprType, m_emOprType )
    TYPESTRUCT_MEMBER( TDisScreenStat, u16, m_awScreenNum )
    TYPESTRUCT_MEMBER( TDisScreenStat, u16, m_awSpeakerIndx )
    TYPESTRUCT_MEMBER( TDisScreenStat, TTPAlias, m_atAlias )
TYPESTRUCT_END(  TDisScreenStat )

//TDisAskKeyFrame
TYPESTRUCT_BEGIN( TDisAskKeyFrame )
    TYPESTRUCT_MEMBER( TDisAskKeyFrame, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TDisAskKeyFrame, u16, m_wScreenNo )
    TYPESTRUCT_MEMBER( TDisAskKeyFrame, BOOL32, m_bReqBySys )
TYPESTRUCT_END(  TDisAskKeyFrame )

//TTPBrdRegInfo
TYPESTRUCT_BEGIN( TTPBrdRegInfo )
    TYPESTRUCT_MEMBER( TTPBrdRegInfo, TTPBrdPos, m_tBrdPos )
    TYPESTRUCT_MEMBER( TTPBrdRegInfo, u8, m_byNetIndx )
    TYPESTRUCT_MEMBER( TTPBrdRegInfo, EMOsType, m_emOsType )
TYPESTRUCT_END(  TTPBrdRegInfo )

//TTPMpu2CfgAck
TYPESTRUCT_BEGIN( TTPMpu2CfgAck )
    TYPESTRUCT_MEMBER( TTPMpu2CfgAck, EMEqpModleType, m_byEqpMdlType )
    TYPESTRUCT_MEMBER( TTPMpu2CfgAck, u8, m_byEqpId )
    TYPESTRUCT_MEMBER( TTPMpu2CfgAck, u8, m_byEqpId2 )
    TYPESTRUCT_MEMBER( TTPMpu2CfgAck, u16, m_wEqpRcvStartPort )
    TYPESTRUCT_MEMBER( TTPMpu2CfgAck, u16, m_wEqpRcvStartPort2 )
TYPESTRUCT_END(  TTPMpu2CfgAck )

//THduCfgAck
TYPESTRUCT_BEGIN( THduCfgAck )
    TYPESTRUCT_MEMBER( THduCfgAck, u8, m_byStartMode )
    TYPESTRUCT_MEMBER( THduCfgAck, u8, m_byEqpID )
TYPESTRUCT_END(  THduCfgAck )

//TTPVmpReg
TYPESTRUCT_BEGIN( TTPVmpReg )
    TYPESTRUCT_MEMBER( TTPVmpReg, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPVmpReg, EMEqpModleType, m_emEqpMdlType )
    TYPESTRUCT_MEMBER( TTPVmpReg, u32, m_dwEqpIPAddr )
    TYPESTRUCT_MEMBER( TTPVmpReg, u32, m_dwEqpPort )
    TYPESTRUCT_MEMBER( TTPVmpReg, u32, m_dwEqpVer )
TYPESTRUCT_END(  TTPVmpReg )

//TTPBasReg
TYPESTRUCT_BEGIN( TTPBasReg )
    TYPESTRUCT_MEMBER( TTPBasReg, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPBasReg, EMEqpModleType, m_emEqpMdlType )
    TYPESTRUCT_MEMBER( TTPBasReg, u32, m_dwEqpIPAddr )
    TYPESTRUCT_MEMBER( TTPBasReg, u32, m_dwEqpPort )
    TYPESTRUCT_MEMBER( TTPBasReg, u32, m_dwEqpVer )
TYPESTRUCT_END(  TTPBasReg )

//TTPBasRegAck
TYPESTRUCT_BEGIN( TTPBasRegAck )
    TYPESTRUCT_MEMBER( TTPBasRegAck, u32, m_dwIpAddr )
    TYPESTRUCT_MEMBER( TTPBasRegAck, u16, m_wStartPort )
    TYPESTRUCT_MEMBER( TTPBasRegAck, s8, m_szAlias )
    TYPESTRUCT_MEMBER( TTPBasRegAck, u16, m_wEqpStartPort )
    TYPESTRUCT_MEMBER( TTPBasRegAck, u8, m_byEqpId )
TYPESTRUCT_END(  TTPBasRegAck )

//TTPBasStatNtfy
TYPESTRUCT_BEGIN( TTPBasStatNtfy )
    TYPESTRUCT_MEMBER( TTPBasStatNtfy, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPBasStatNtfy, s8, m_szAlias )
TYPESTRUCT_END(  TTPBasStatNtfy )

//TTPBasChnStatNtfy
TYPESTRUCT_BEGIN( TTPBasChnStatNtfy )
    TYPESTRUCT_MEMBER( TTPBasChnStatNtfy, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPBasChnStatNtfy, u8, m_byChnIndx )
    TYPESTRUCT_MEMBER( TTPBasChnStatNtfy, u8, m_byStat )
TYPESTRUCT_END(  TTPBasChnStatNtfy )

//TTPBasRetInfo
TYPESTRUCT_BEGIN( TTPBasRetInfo )
    TYPESTRUCT_MEMBER( TTPBasRetInfo, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPBasRetInfo, u8, m_byChnID )
TYPESTRUCT_END(  TTPBasRetInfo )

//TTPBasNAck
TYPESTRUCT_BEGIN( TTPBasNAck )
    TYPESTRUCT_MEMBER( TTPBasNAck, u8, m_byEqpID )
    TYPESTRUCT_MEMBER( TTPBasNAck, u16, m_wChnIndx )
TYPESTRUCT_END(  TTPBasNAck )

//THduRegInfo
TYPESTRUCT_BEGIN( THduRegInfo )
    TYPESTRUCT_MEMBER( THduRegInfo, u8, m_byLayer )
    TYPESTRUCT_MEMBER( THduRegInfo, u8, m_bySlot )
    TYPESTRUCT_MEMBER( THduRegInfo, u32, m_dwIpAddr )
    TYPESTRUCT_MEMBER( THduRegInfo, u16, m_wStartPort )
    TYPESTRUCT_MEMBER( THduRegInfo, u8, m_byChannlNum )
    TYPESTRUCT_MEMBER( THduRegInfo, s8, m_achAlias )
    TYPESTRUCT_MEMBER( THduRegInfo, u16, m_wVersion )
    TYPESTRUCT_MEMBER( THduRegInfo, BOOL, m_bHDEqp )
TYPESTRUCT_END(  THduRegInfo )

//THduRegCfgAck
TYPESTRUCT_BEGIN( THduRegCfgAck )
    TYPESTRUCT_MEMBER( THduRegCfgAck, u16, m_wStartPort )
    TYPESTRUCT_MEMBER( THduRegCfgAck, s8, m_szAlias )
    TYPESTRUCT_MEMBER( THduRegCfgAck, THduChanInfo, m_atChanInfo )
TYPESTRUCT_END(  THduRegCfgAck )

//TBrdVersion
TYPESTRUCT_BEGIN( TBrdVersion )
    TYPESTRUCT_MEMBER( TBrdVersion, u16, m_wBrdIndex )
    TYPESTRUCT_MEMBER( TBrdVersion, u8, m_achBrdVer )
    TYPESTRUCT_MEMBER( TBrdVersion, u8, m_achSoftVer )
TYPESTRUCT_END(  TBrdVersion )

//TBrdUpInfo
TYPESTRUCT_BEGIN( TBrdUpInfo )
    TYPESTRUCT_MEMBER( TBrdUpInfo, u8, m_byIndex )
    TYPESTRUCT_MEMBER( TBrdUpInfo, u8, m_byNum )
    TYPESTRUCT_MEMBER( TBrdUpInfo, u8, m_byNameLen )
    TYPESTRUCT_MEMBER( TBrdUpInfo, s8, m_szFileName )
TYPESTRUCT_END(  TBrdUpInfo )

//TUpRecPlayState
TYPESTRUCT_BEGIN( TUpRecPlayState )
    TYPESTRUCT_MEMBER( TUpRecPlayState, BOOL32, m_bIsPlayIng )
    TYPESTRUCT_MEMBER( TUpRecPlayState, BOOL32, m_bIsDualPlayIng )
    TYPESTRUCT_MEMBER( TUpRecPlayState, s8, m_achFileName )
TYPESTRUCT_END(  TUpRecPlayState )

//TReqAddrInfo
TYPESTRUCT_BEGIN( TReqAddrInfo )
    TYPESTRUCT_MEMBER( TReqAddrInfo, u32, m_dwSipHandle )
    TYPESTRUCT_MEMBER( TReqAddrInfo, u32, m_dwGkHandle )
TYPESTRUCT_END(  TReqAddrInfo )

//TGetVidBaseInfo
TYPESTRUCT_BEGIN( TGetVidBaseInfo )
    TYPESTRUCT_MEMBER( TGetVidBaseInfo, u16, m_wHandle )
    TYPESTRUCT_MEMBER( TGetVidBaseInfo, u16, m_wEpID )
    TYPESTRUCT_MEMBER( TGetVidBaseInfo, u16, m_wScreenIndex )
    TYPESTRUCT_MEMBER( TGetVidBaseInfo, EmGetVidType, m_emType )
TYPESTRUCT_END(  TGetVidBaseInfo )

//TGetVidInfo
TYPESTRUCT_BEGIN( TGetVidInfo )
    TYPESTRUCT_MEMBER( TGetVidInfo, TGetVidBaseInfo, m_tBaseInfo )
    TYPESTRUCT_MEMBER( TGetVidInfo, BOOL32, m_bSamll )
    TYPESTRUCT_MEMBER( TGetVidInfo, TTPMediaTransAddr, m_atVidAddr )
    TYPESTRUCT_MEMBER( TGetVidInfo, TTPMediaTransAddr, m_atAudAddr )
    TYPESTRUCT_MEMBER( TGetVidInfo, TTPMediaTransAddr, m_atSmallVid )
    TYPESTRUCT_MEMBER( TGetVidInfo, TTPMediaTransAddr, m_tMixAddr )
TYPESTRUCT_END(  TGetVidInfo )

//TGetVidInfoRes
TYPESTRUCT_BEGIN( TGetVidInfoRes )
    TYPESTRUCT_MEMBER( TGetVidInfoRes, EmGetVidRes, m_emRes )
    TYPESTRUCT_MEMBER( TGetVidInfoRes, TGetVidInfo, m_tInfo )
TYPESTRUCT_END(  TGetVidInfoRes )

//TStopGetVid
TYPESTRUCT_BEGIN( TStopGetVid )
    TYPESTRUCT_MEMBER( TStopGetVid, TGetVidBaseInfo, m_tInfo )
    TYPESTRUCT_MEMBER( TStopGetVid, EmGetVidRes, m_emRes )
TYPESTRUCT_END(  TStopGetVid )

//TIFrameSndDis
TYPESTRUCT_BEGIN( TIFrameSndDis )
    TYPESTRUCT_MEMBER( TIFrameSndDis, BOOL32, m_bCheck )
    TYPESTRUCT_MEMBER( TIFrameSndDis, u32_ip, m_dwDstIp )
    TYPESTRUCT_MEMBER( TIFrameSndDis, u16, m_wDstPort )
    TYPESTRUCT_MEMBER( TIFrameSndDis, u16, m_wOldPort )
TYPESTRUCT_END(  TIFrameSndDis )

//TIpmaskinfo
TYPESTRUCT_BEGIN( TIpmaskinfo )
    TYPESTRUCT_MEMBER( TIpmaskinfo, u32_ip, m_dwIpa )
    TYPESTRUCT_MEMBER( TIpmaskinfo, u32_ip, m_dwMaska )
    TYPESTRUCT_MEMBER( TIpmaskinfo, u32_ip, m_dwIpb )
    TYPESTRUCT_MEMBER( TIpmaskinfo, u32_ip, m_dwMaskb )
    TYPESTRUCT_MEMBER( TIpmaskinfo, u32_ip, m_dwOutIp )
TYPESTRUCT_END(  TIpmaskinfo )

//TRollCallEpNodeInfo
TYPESTRUCT_BEGIN( TRollCallEpNodeInfo )
    TYPESTRUCT_MEMBER( TRollCallEpNodeInfo, u16, m_wEpId )
    TYPESTRUCT_MEMBER( TRollCallEpNodeInfo, u16, m_wVidSndNum )
    TYPESTRUCT_MEMBER( TRollCallEpNodeInfo, u16, m_wVidRcvNum )
    TYPESTRUCT_MEMBER( TRollCallEpNodeInfo, u16, m_wAudSndNum )
    TYPESTRUCT_MEMBER( TRollCallEpNodeInfo, u16, m_wAudRcvNum )
    TYPESTRUCT_MEMBER( TRollCallEpNodeInfo, u16, m_wSpeakerSeat )
    TYPESTRUCT_MEMBER( TRollCallEpNodeInfo, TTPAlias, m_Alias )
TYPESTRUCT_END(  TRollCallEpNodeInfo )

//TRollCallCasecadeNtfy
TYPESTRUCT_BEGIN( TRollCallCasecadeNtfy )
    TYPESTRUCT_MEMBER( TRollCallCasecadeNtfy, EMRollCallNotyToLowUmsType, m_NotyType )
    TYPESTRUCT_MEMBER( TRollCallCasecadeNtfy, BOOL32, m_bIsRollCallModle )
    TYPESTRUCT_MEMBER( TRollCallCasecadeNtfy, TRollCallEpNodeInfo, m_NodeInfo )
TYPESTRUCT_END(  TRollCallCasecadeNtfy )

//TUmsMcuChan
TYPESTRUCT_BEGIN( TUmsMcuChan )
    TYPESTRUCT_MEMBER( TUmsMcuChan, s32, m_hMcuChan )
    TYPESTRUCT_MEMBER( TUmsMcuChan, s32, m_hMcuAppChan )
TYPESTRUCT_END(  TUmsMcuChan )

//TUmsMcuRegUnReg
TYPESTRUCT_BEGIN( TUmsMcuRegUnReg )
    TYPESTRUCT_MEMBER( TUmsMcuRegUnReg, BOOL32, m_bReg )
    TYPESTRUCT_MEMBER( TUmsMcuRegUnReg, s32, m_nReqID )
    TYPESTRUCT_MEMBER( TUmsMcuRegUnReg, EmUmsMcuRet, m_emRet )
TYPESTRUCT_END(  TUmsMcuRegUnReg )

//TUmsMcuRosterItem
TYPESTRUCT_BEGIN( TUmsMcuRosterItem )
    TYPESTRUCT_MEMBER( TUmsMcuRosterItem, u8, m_byState )
    TYPESTRUCT_MEMBER( TUmsMcuRosterItem, u32, m_dwPID )
TYPESTRUCT_END(  TUmsMcuRosterItem )

//TUmsMcuRosterList
TYPESTRUCT_BEGIN( TUmsMcuRosterList )
    TYPESTRUCT_MEMBER( TUmsMcuRosterList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TUmsMcuRosterList, TUmsMcuRosterItem, m_atRoster )
TYPESTRUCT_END(  TUmsMcuRosterList )

//TUmcMcuPart
TYPESTRUCT_BEGIN( TUmcMcuPart )
    TYPESTRUCT_MEMBER( TUmcMcuPart, u32, m_dwPID )
    TYPESTRUCT_MEMBER( TUmcMcuPart, s8, m_aszEpName )
    TYPESTRUCT_MEMBER( TUmcMcuPart, u32, m_dwIP )
    TYPESTRUCT_MEMBER( TUmcMcuPart, u8, m_byState )
    TYPESTRUCT_MEMBER( TUmcMcuPart, BOOL32, m_bMute )
    TYPESTRUCT_MEMBER( TUmcMcuPart, BOOL32, m_bQuiet )
TYPESTRUCT_END(  TUmcMcuPart )

//TMcuEpCmd
TYPESTRUCT_BEGIN( TMcuEpCmd )
    TYPESTRUCT_MEMBER( TMcuEpCmd, u32, m_dwPID )
    TYPESTRUCT_MEMBER( TMcuEpCmd, BOOL32, m_bCall )
TYPESTRUCT_END(  TMcuEpCmd )

//TUmsMcuPartList
TYPESTRUCT_BEGIN( TUmsMcuPartList )
    TYPESTRUCT_MEMBER( TUmsMcuPartList, s32, m_nReqID )
    TYPESTRUCT_MEMBER( TUmsMcuPartList, EmUmsMcuRet, m_emRet )
    TYPESTRUCT_MEMBER( TUmsMcuPartList, s32, m_dwPartCount )
    TYPESTRUCT_MEMBER( TUmsMcuPartList, BOOL32, m_bLastPack )
TYPESTRUCT_END(  TUmsMcuPartList )

//TMcuSpeakerStausNty
TYPESTRUCT_BEGIN( TMcuSpeakerStausNty )
    TYPESTRUCT_MEMBER( TMcuSpeakerStausNty, u32, m_dwPID )
    TYPESTRUCT_MEMBER( TMcuSpeakerStausNty, u32, m_dwStatus )
TYPESTRUCT_END(  TMcuSpeakerStausNty )

//TMcuSpyReq
TYPESTRUCT_BEGIN( TMcuSpyReq )
    TYPESTRUCT_MEMBER( TMcuSpyReq, u32, m_dwPID )
    TYPESTRUCT_MEMBER( TMcuSpyReq, EmTpVideoResolution, m_emRes )
TYPESTRUCT_END(  TMcuSpyReq )

//TFeccMtInfo
TYPESTRUCT_BEGIN( TFeccMtInfo )
    TYPESTRUCT_MEMBER( TFeccMtInfo, u8, m_bySrcMcuId )
    TYPESTRUCT_MEMBER( TFeccMtInfo, u8, m_bySrcMtId )
    TYPESTRUCT_MEMBER( TFeccMtInfo, u8, m_byDstMcuId )
    TYPESTRUCT_MEMBER( TFeccMtInfo, u8, m_byDstMtId )
TYPESTRUCT_END(  TFeccMtInfo )

//TEpVidFeccInfo
TYPESTRUCT_BEGIN( TEpVidFeccInfo )
    TYPESTRUCT_MEMBER( TEpVidFeccInfo, TEpPathKey, m_tID )
    TYPESTRUCT_MEMBER( TEpVidFeccInfo, TVidFeccInfo, m_tVidFeccInfo )
TYPESTRUCT_END(  TEpVidFeccInfo )

//TConfEpVidFeccList
TYPESTRUCT_BEGIN( TConfEpVidFeccList )
    TYPESTRUCT_MEMBER( TConfEpVidFeccList, u16, m_wNum )
    TYPESTRUCT_MEMBER( TConfEpVidFeccList, TEpVidFeccInfo, m_atList )
TYPESTRUCT_END(  TConfEpVidFeccList )

//TEpStatusInfo
TYPESTRUCT_BEGIN( TEpStatusInfo )
    TYPESTRUCT_MEMBER( TEpStatusInfo, TQuietRmtEpInd, m_tQuietInd )
    TYPESTRUCT_MEMBER( TEpStatusInfo, TMuteRmtEpInd, m_tMuteInd )
    TYPESTRUCT_MEMBER( TEpStatusInfo, u8, m_byCurVidNo )
    TYPESTRUCT_MEMBER( TEpStatusInfo, BOOL32, m_bAllowFecc )
TYPESTRUCT_END(  TEpStatusInfo )

//TTelnetFtpStatus
TYPESTRUCT_BEGIN( TTelnetFtpStatus )
    TYPESTRUCT_MEMBER( TTelnetFtpStatus, BOOL32, m_bTelnetStatus )
    TYPESTRUCT_MEMBER( TTelnetFtpStatus, BOOL32, m_bFtpStatus )
TYPESTRUCT_END(  TTelnetFtpStatus )

//TBrdSwitchInfo
TYPESTRUCT_BEGIN( TBrdSwitchInfo )
    TYPESTRUCT_MEMBER( TBrdSwitchInfo, u16, m_wBrdIndex )
    TYPESTRUCT_MEMBER( TBrdSwitchInfo, BOOL32, m_bSwitch )
    TYPESTRUCT_MEMBER( TBrdSwitchInfo, EmBoardSwitchType, m_emType )
TYPESTRUCT_END(  TBrdSwitchInfo )

//通讯数据结构编码表
TXDATAINFO* g_tLocalStructDataInfo[]={
	(TXDATAINFO*)TUmsHandlemembertable,
	(TXDATAINFO*)TRegCfgmembertable,
	(TXDATAINFO*)TUmsSipRegCfgmembertable,
	(TXDATAINFO*)TCnsRegRetResultmembertable,
	(TXDATAINFO*)TPollInfoNtfmembertable,
	(TXDATAINFO*)TEpPathKeymembertable,
	(TXDATAINFO*)TEpKeymembertable,
	(TXDATAINFO*)TEpKeyExmembertable,
	(TXDATAINFO*)TCheckIFrameBasemembertable,
	(TXDATAINFO*)TIFrameBySrcmembertable,
	(TXDATAINFO*)TIFrameTwoRcvPortmembertable,
	(TXDATAINFO*)TIFrameSndBySrcmembertable,
	(TXDATAINFO*)TUmsDsDatamembertable,
	(TXDATAINFO*)TUmsNetBufmembertable,
	(TXDATAINFO*)TConfNodeCallUpdateTrmembertable,
	(TXDATAINFO*)TConfNodeCallUpdateTrListmembertable,
	(TXDATAINFO*)TConfNodeChanUpdateTrmembertable,
	(TXDATAINFO*)TConfNodeChanUpdateTrListmembertable,
	(TXDATAINFO*)TConfNodeDelTrListmembertable,
	(TXDATAINFO*)TSpeakerCapTrmembertable,
	(TXDATAINFO*)TPollCmdTrmembertable,
	(TXDATAINFO*)TPollAckTrmembertable,
	(TXDATAINFO*)TViewCmdTrmembertable,
	(TXDATAINFO*)TViewAckTrmembertable,
	(TXDATAINFO*)TCascadeOpenChanCmdmembertable,
	(TXDATAINFO*)TCascadeOpenChanAckmembertable,
	(TXDATAINFO*)TAudMixEpCmdTrmembertable,
	(TXDATAINFO*)TAudMixEpAckTrmembertable,
	(TXDATAINFO*)TChairInfoTrmembertable,
	(TXDATAINFO*)TMuteRmtEpCmdmembertable,
	(TXDATAINFO*)TMuteRmtEpIndmembertable,
	(TXDATAINFO*)TQuietRmtEpCmdmembertable,
	(TXDATAINFO*)TQuietRmtEpIndmembertable,
	(TXDATAINFO*)TDropEpCmdmembertable,
	(TXDATAINFO*)TTvMonitorCmdTrmembertable,
	(TXDATAINFO*)TTvMonitorIndTrmembertable,
	(TXDATAINFO*)TAskKeyByScreenTrmembertable,
	(TXDATAINFO*)TFlowControlmembertable,
	(TXDATAINFO*)TUmsCallInfomembertable,
	(TXDATAINFO*)TChanNetParamembertable,
	(TXDATAINFO*)TUmsVidCapParammembertable,
	(TXDATAINFO*)TUmsAudCapmembertable,
	(TXDATAINFO*)TUmsNodeCapsetmembertable,
	(TXDATAINFO*)TUmsDualCapsetmembertable,
	(TXDATAINFO*)TUmsDualCapsetMcmembertable,
	(TXDATAINFO*)TMakeCallParamembertable,
	(TXDATAINFO*)TTPConfInfoNtfymembertable,
	(TXDATAINFO*)TCnsSpeakerAdjustmembertable,
	(TXDATAINFO*)TEqpResmembertable,
	(TXDATAINFO*)TModelPropmembertable,
	(TXDATAINFO*)TUmsStackCallCfgmembertable,
	(TXDATAINFO*)TUmsMediatransCfgmembertable,
	(TXDATAINFO*)TUmsNetbufCfgmembertable,
	(TXDATAINFO*)TDualInfoTrmembertable,
	(TXDATAINFO*)TDualInfoAckTrmembertable,
	(TXDATAINFO*)TDualRequestAckTrmembertable,
	(TXDATAINFO*)TAudChanAckmembertable,
	(TXDATAINFO*)TAudChanCmdmembertable,
	(TXDATAINFO*)TVidUpAddrmembertable,
	(TXDATAINFO*)TVidDownAddrmembertable,
	(TXDATAINFO*)TVidChanCmdmembertable,
	(TXDATAINFO*)TVidChanAckmembertable,
	(TXDATAINFO*)TDiscussObjInfomembertable,
	(TXDATAINFO*)TDiscussEpAudInfomembertable,
	(TXDATAINFO*)TDiscussCasecadeNtfymembertable,
	(TXDATAINFO*)TDisScreenStatmembertable,
	(TXDATAINFO*)TDisAskKeyFramemembertable,
	(TXDATAINFO*)TTPBrdRegInfomembertable,
	(TXDATAINFO*)TTPMpu2CfgAckmembertable,
	(TXDATAINFO*)THduCfgAckmembertable,
	(TXDATAINFO*)TTPVmpRegmembertable,
	(TXDATAINFO*)TTPBasRegmembertable,
	(TXDATAINFO*)TTPBasRegAckmembertable,
	(TXDATAINFO*)TTPBasStatNtfymembertable,
	(TXDATAINFO*)TTPBasChnStatNtfymembertable,
	(TXDATAINFO*)TTPBasRetInfomembertable,
	(TXDATAINFO*)TTPBasNAckmembertable,
	(TXDATAINFO*)THduRegInfomembertable,
	(TXDATAINFO*)THduRegCfgAckmembertable,
	(TXDATAINFO*)TBrdVersionmembertable,
	(TXDATAINFO*)TBrdUpInfomembertable,
	(TXDATAINFO*)TUpRecPlayStatemembertable,
	(TXDATAINFO*)TReqAddrInfomembertable,
	(TXDATAINFO*)TGetVidBaseInfomembertable,
	(TXDATAINFO*)TGetVidInfomembertable,
	(TXDATAINFO*)TGetVidInfoResmembertable,
	(TXDATAINFO*)TStopGetVidmembertable,
	(TXDATAINFO*)TIFrameSndDismembertable,
	(TXDATAINFO*)TIpmaskinfomembertable,
	(TXDATAINFO*)TRollCallEpNodeInfomembertable,
	(TXDATAINFO*)TRollCallCasecadeNtfymembertable,
	(TXDATAINFO*)TUmsMcuChanmembertable,
	(TXDATAINFO*)TUmsMcuRegUnRegmembertable,
	(TXDATAINFO*)TUmsMcuRosterItemmembertable,
	(TXDATAINFO*)TUmsMcuRosterListmembertable,
	(TXDATAINFO*)TUmcMcuPartmembertable,
	(TXDATAINFO*)TMcuEpCmdmembertable,
	(TXDATAINFO*)TUmsMcuPartListmembertable,
	(TXDATAINFO*)TMcuSpeakerStausNtymembertable,
	(TXDATAINFO*)TMcuSpyReqmembertable,
	(TXDATAINFO*)TFeccMtInfomembertable,
	(TXDATAINFO*)TEpVidFeccInfomembertable,
	(TXDATAINFO*)TConfEpVidFeccListmembertable,
	(TXDATAINFO*)TEpStatusInfomembertable,
	(TXDATAINFO*)TTelnetFtpStatusmembertable,
	(TXDATAINFO*)TBrdSwitchInfomembertable,
	(TXDATAINFO*)NULL
};

//枚举描述字符串表
TXENUMINFO* enumLocalXDescripTbl[]={
	(TXENUMINFO*)NULL
};

TXDATAINFO* g_tTpEnumDataInfo[XML_TP_TYPE_NUM + XML_LOCAL_TYPE_NUM + 1] = {NULL};
TXDATAINFO* g_tTpStructDataInfo[XML_TP_STRUCT_NUM + XML_LOCAL_STRUCT_NUM + 1] = {NULL};
TXENUMINFO* enumTpXDescripTbl[XML_TP_TYPE_NUM + XML_LOCAL_TYPE_NUM + 1] = {NULL};

TXDATAINFO** CombineEnumDateInfo(void)
{
	memcpy(g_tTpEnumDataInfo, g_tTpEnumData, sizeof(g_tTpEnumData));
	memcpy(g_tTpEnumDataInfo + XML_TP_TYPE_NUM, g_tLocalEnumDataInfo, sizeof(g_tLocalEnumDataInfo));
	return g_tTpEnumDataInfo;
}

TXDATAINFO** CombineStructDateInfo(void)
{
	memcpy(g_tTpStructDataInfo, g_tTpStructData, sizeof(g_tTpStructData));
	memcpy(g_tTpStructDataInfo + XML_TP_STRUCT_NUM, g_tLocalStructDataInfo, sizeof(g_tLocalStructDataInfo));
	return g_tTpStructDataInfo;
}

void CombineEnumXDescripTbl(void)
{
	memcpy(enumTpXDescripTbl, enumTpXDescript, sizeof(enumTpXDescript));
	memcpy(enumTpXDescripTbl + XML_TP_TYPE_NUM, enumLocalXDescripTbl, sizeof(enumLocalXDescripTbl));
}

s8* GetTpEnumString(u16 type, u16 index)
{
	if (NULL == enumTpXDescripTbl[0])
	{
		CombineEnumXDescripTbl();
	}

	u16 wTmpType = type - _placeholder_emxEnumTypeBegin - 1;
	if (wTmpType > sizeof(enumTpXDescripTbl)/sizeof(enumTpXDescripTbl[0]))
		return "DefaultType";
	
	TXENUMINFO* pEnumInfo = enumTpXDescripTbl[wTmpType];
	while(NULL != pEnumInfo->descrip)
	{
		if (pEnumInfo->val == index)
			return pEnumInfo->descrip;
		pEnumInfo++;
	}
	return "DefaultIndex";
}


} //namespace UmsTpmsg
