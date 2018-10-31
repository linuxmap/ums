#ifndef _h_umsdataconvet_h__
#define _h_umsdataconvet_h__

#include "protocoladapter.h"
#include "umscommonstruct.h"
#include "pastruct.h"
#include "modulecallstruct.h"
#include "qtinterface.h"
#include "patype.h"

void ConvertMediaTransAddrFromStackToUms(TTPMediaTransAddr& tUms, const TPaMediaTransAddr& tPA);
void ConvertMediaTransAddrFromUmsToStack(TPaMediaTransAddr& tPA, const TTPMediaTransAddr& tUms);
void ConvertCallProtocolParamFromUmsToStack(const EmTpConfProtocol& emTpProtocol, EmPAConfProtocol& emPaProtocol);
void ConvertRegProtocolFromUmsToStack(const EmTpRegType& emTpProtocol, EmPAConfProtocol& emPaProtocol);
void ConvertCallInfoFromUmsToStackForH323(const TMakeCallPara& tCallPara, TModuleCallInfo& tModuleInfo, TCallInfoTP& tTpCallInfo, BOOL32 bAnswer = FALSE);
void ConvertCallInfoFromUmsToStack(const TMakeCallPara& tCallPara, TModuleCallInfo& tModuleInfo, TCallInfoTP& tTpCallInfo, BOOL32 bAnswer = FALSE);
void ConvertTpEpTypeFromUmsToStack(const EmTPEndpointType& emTpEpType, emModuleEndpointType& emPaType);
void ConvertSipLevelFromUmsToStack(const EmTPSipLevel& emTpLevel, EmPASipLevel&	emPaLevel);
void ConvertCapFromUmsToStack(const TMakeCallPara& tCallPara, TCallCapbility& tSendCap, TCallCapbility& tRecvCap,
							  TCallDescriptTP& tSendTp, TCallDescriptTP& tRecvTp);
void ConvertCallInfoFromStackToUms(const TModuleCallInfo& tModuleInfo, TUmsCallInfo& tCallInfo, BOOL32& bHangUp);
void ConvertCallInfoFromStackToUmsForH323(const TModuleCallInfo& tModuleInfo, TUmsCallInfo& tCallInfo);
void ConvertVersionIDFromStackToUms(const TModuleCallInfo& tModuleInfo, TUmsCallInfo& tCallInfo);
void ConvertSipLevelFromStackToUms(const EmPASipLevel& emPaLevel, EmTPSipLevel&	emTpLevel);
void ConvertModuleDisReasonFromStackToUms(const EmModuleCallDisconnectReason& emModuleReason, EmCnsCallReason& emCnsReason);
void ConvertModuleDisReasonFromUmsToStack(const EmCnsCallReason& emCnsReason, EmModuleCallDisconnectReason& emModuleReason);

void ConvertChanConnectParamFromStackToUms(TChanConnectedInfo* patChanConnectInfo, u8 bySize, TChanDescriptTP *ptDesTP, TUmsNodeCapset& tCapSet);
void ConvertChanChangeParamFromUmsToStack(TPOUT TChanConnectedInfo* patChanConnectInfo, TPOUT u8& byMaxSize, const TUmsNodeCapset& tCapSet, BOOL32 bIsDual);
void ConverDualParamFromStackToUms(TChanConnectedInfo* patChanConnectInfo, u8 bySize, TUmsNodeCapset& tCapSet);
//add
void ConvertChanClosedParamFromUmsToStack(TPOUT HMDLCHANNEL* phChan, TPOUT HMDLAPPCHANNEL* phAppChan, TPOUT u8& bySize, const BOOL32& bIsSnd, const TUmsNodeCapset& tNode);
void ConvertDualChanClosedParamFromUmsToStack(TPOUT HMDLCHANNEL* phChan, TPOUT HMDLAPPCHANNEL* phAppChan, TPOUT u8& bySize, const BOOL32& bIsSnd, const TUmsNodeCapset& tNode);

void ConvertCreatConfInfoFromStackToUms(const TModuleCallInfo& tModuleInfo, TPOUT TTPConfTemplate& tConf);

/*void CheckCallerIsInConfList(TTPConfTemplate& tconf, const TModuleCallInfo& tModuleInfo, TPOUT TUmsCallInfo& tCallInfo);*/

void ConvertDualParamFromStackToUms(TChanConnectedInfo *ptChanInfo, TUmsNodeCapset& tNodeCap);

void ConvertSipRegInfoFromUmsToStack(TPARegCfg& tPaRegCfg, TUmsSipRegCfg& tRegCfg, TTPAlias atAlias[], u16 wAliasNum);
void ConvertGkRegInfoFromUmsToStack(TRegistReq& tRegInfo, TRegCfg& tRegCfg, u16 wAliasNum);

void ConverDualInfoFromUmsToStack(TDualCapList& tDualCapList, const TUmsNodeCapset& tNodeCapSet);
void ConverDualInfoFromUmsToStack(TDualCapList& tDualCapList, const TUmsDualCapsetMc& tNodeCapSet);

void ConverDualInfoFromUmsToStackForMakeCall(TVideoCapbilityList& tSndDualCapList, 
											 TVideoCapbilityList& tRecvDualCapList, 
											 const TUmsDualCapsetMc& tDualCapSet);

void ConvertVideoResFromUmsToStack(const EmTpVideoResolution& emtpVideRes, EmModuleVideoResolution& emModuleVideoRes);
void ConverAddrFromUmsToStack(const TTPTransAddr& tTpAddr, TModuleTransportAddress& tModuleAddr);
u16 ConvertNodeCallUpdateFromStackToUms(TConfNodeCallUpdateTrList& tUms, const TPAConfNodeUpdateTrList& tPA);
u16 ConvertNodeChanUpdateFromStackToUms(TConfNodeChanUpdateTrList& tUms, const TPAConfNodeUpdateB2NEWTrList& tPA);
void ConvertAliasFromStackToUms(const TPAAlias& tPA, TTPAlias& tUms);
void ConvertCallTypeFromStackToUms(const EmPAAliasType& emPA, EmTpAliasType& emUms);
u16 ConvertNodeDelFromStackToUms(TConfNodeDelTrList& tUms, const TPAConfNodeDelTrList& tPA);
u16 ConvertConfPollCmdFromStackToUms(TPAPollCmd& tPA, TPollCmdTr& tPollCmd);
u16 ConvertConfPollAckFromStackToUms(TPAPollAck& tPA, TPollAckTr& tPollAck);
void ConvertConfNetAddrFromStackToUms(TTPTransAddr& tUms, const TPAIPAddress& tPA);
u16 ConvertAudChanCmdFromStackToUms(const TPAAudChanCmd& tPA, TAudChanCmd& tUms);
u16 ConvertEpKeyFromStackToUms( const TPAEpKey& tPA, TEpKey& tUms );
u16 ConvertAudChanAckFromStackToUms(const TPAAudChanAck& tPA, TAudChanAck& tUms);
u16 ConvertVidChanCmdFromStackToUms(const TPAVidChanCmd& tPA, TVidChanCmd& tUms);
u16 ConvertVidChanAckFromStackToUms(const TPAVidChanAck& tPA, TVidChanAck& tUms);
u16 ConvertConfDualStreamFromStackToUms(TDualInfoTr& tUms, const TDualInfo& tPA);
void ConverEpKeyFromStackToUms(const TPAEpKey& tPA, TEpKey& tUms);
u16 ConvertAddTvMonitorFromStackToUms(TTvMonitorCmdTr& tUms, const TPATvMonitorCmd& tPA);
u16 ConvertAddTvMonitorIndFromStackToUms(TTvMonitorIndTr& tUms, const TPATvMonitorInd& tPA);
u16 ConvertViewCmdFromStackToUms(TViewCmdTr& tUms, const TPAViewCmd& tPA);
u16 ConvertViewIndFromStackToUms(TViewAckTr& tUms, const TPAViewAck& tPA);
u16 ConvertCascadeOpenChanCmdFromStackToUms(TCascadeOpenChanCmd& tUms, const TPACascadeOpenChanCmd& tPA);
u16 ConvertCascadeOpenChanAckFromStackToUms(TCascadeOpenChanAck& tUms, const TPACascadeOpenChanAck& tPA);
u16 ConvertConfAuxMixInfoFromStackToUms(const TPAConfAuxMixInfo& tPA, TConfAuxMixInfo& tUms);
u16 ConvertConfEpIDFromStackToUms(const TPAConfEpID& tPA, TConfEpID& tUms);
u16 ConvertConfTurnInfoFromStackToUms(const TPAConfTurnInfo& tPA, TConfTurnInfo& tUms);
u16 ConvertChairConfInfoFromStackToUms(const TPAChairConfInfo& tPA, TChairConfInfo& tUms);
u16 ConvertAudMixStatFromStackToUms(const TPAAudMixStat& tPA, TAudMixStat& tUms);
u16 ConvertEmTpMixStatusFromStackToUms(const EmPATpMixStatus& tPA, EmTpMixStatus& tUms);
u16 ConvertConfDualStreamFromUmsToStack(TDualInfo& tPA, const TDualInfoTr& tUms);
void CovertConfNetAddrFromStackToUms(const TPAIPAddress& tPA,  TTPTransAddr& tUms);
void ConvertConfNetAddrFromUmsToStack(TPAIPAddress& tPA, const TTPTransAddr& tUms);
u16 ConvertEpKeyFromUmsToStack( const TEpKey& tUms, TPAEpKey& tPA );
void ConverEpKeyFromUmsToStack(const TEpKey& tUms, TPAEpKey& tPA);
u16 ConvertConfPollCmdFromUmsToStack(TPAPollCmd& tPA, const TPollCmdTr& tPollCmd);
u16 ConvertConfPollAckFromUmsToStack(TPAPollAck& tPA, const TPollAckTr& tPollAck);
u16 ConvertAudChanCmdFromUmsToStack(const TAudChanCmd& tUms, TPAAudChanCmd& tPA);
u16 ConvertAudChanAckFromUmsToStack(const TAudChanAck& tUms, TPAAudChanAck& tPA);
u16 ConvertVidChanCmdFromUmsToStack(const TVidChanCmd& tUms, TPAVidChanCmd& tPA);
u16 ConvertVidChanAckFromUmsToStack(const TVidChanAck& tUms, TPAVidChanAck& tPA);
u16 ConvertConfAuxMixInfoFromUmsToStack(const TConfAuxMixInfo& tUms, TPAConfAuxMixInfo& tPA);
u16 ConvertConfEpIDFromUmsToStack(const TConfEpID& tUms, TPAConfEpID& tPA);
u16 ConvertApplySpeakerRetFromUmsToStack(const EmTpApplySpeakerRet& tUms, EmPATpApplySpeakerRet& tPA);
void ConvertAliasFromUmsToStack(const TTPAlias& tUms, TPAAlias& tPA);
void ConvertCallTypeFromUmsToStack(const EmTpAliasType& emUms, EmPAAliasType& emPA);
//void ConvertCallResonFromUmsToStack(const EmCnsCallReason& emUms, EmPACallReason& emStack);
u16 ConvertConfTurnInfoFromUmsToStack(const TConfTurnInfo& tUms, TPAConfTurnInfo& tPA);
u16 ConvertChairConfInfoFromUmsToStack(const TChairConfInfo& tUms, TPAChairConfInfo& tPA);
u16 ConvertAudMixStatFromUmsToStack(const TAudMixStat& tUms, TPAAudMixStat& tPA);
u16 ConvertNodeCallUpdateFromUmsToStack(TPAConfNodeUpdateTrList& tPA, const TConfNodeCallUpdateTrList& tUms);
u16 ConvertNodeChanUpdateFromUmsToStack(TPAConfNodeUpdateB2NEWTrList& tPA, const TConfNodeChanUpdateTrList& tUms);
u16 ConvertEmTpMixStatusFromUmsToStack(const EmTpMixStatus& tUms, EmPATpMixStatus& tPA);
void ConvertCallResonFromUmsToStack(const EmCnsCallReason& emUms, EmPACnsCallReason& emStack);
u16 ConvertNodeDelFromUmsToStack(TPAConfNodeDelTrList& tPA, const TConfNodeDelTrList& tUms);
u16 ConvertAddTvMonitorFromUmsToStack(TPATvMonitorCmd& tPA, const TTvMonitorCmdTr& tUms);
u16 ConvertAddTvMonitorIndFromUmsToStack(TPATvMonitorInd& tPA, const TTvMonitorIndTr& tUms);
u16 ConvertConfCnsListFromUmsToStack(TPAConfCnsList& tPA, TConfCnsInfo& tUms);
u16 ConvertViewCmdFromUmsToStack(TPAViewCmd& tPA, const TViewCmdTr& tUms);
u16 ConvertViewIndFromUmsToStack(TPAViewAck& tPA, const TViewAckTr& tUms);
u16 ConvertCascadeOpenChanCmdFromUmsToStack(TPACascadeOpenChanCmd& tPA, const TCascadeOpenChanCmd& tUms);
u16 ConvertCascadeOpenChanAckFromUmsToStack(TPACascadeOpenChanAck& tPA, const TCascadeOpenChanAck& tUms);
void ConvertProtocolFromPaToTp(const EmPAConfProtocol& emPAType, EmTpConfProtocol& emTpType);
u16 ConvertGetRegInfoTypeFromUmsToStack(const EmGetRegInfoType& tUms, EmPAGetRegInfoType& tPA);
u16 ConvertSipRegInfoFromStackToUms(const TPARegInfo& tPA, TTPSipRegInfo& tUms);
u16 ConvertGetRegInfoTypeFromStackToUms(const EmPAGetRegInfoType& tPA, EmGetRegInfoType& tUms);
u16 ConvertSipRegPackInfoFromStackToUms(const TPARegPackInfo& tPA, TTPSipRegPackInfo& tUms);

u16 ConvertEmChannelReasonFromStackToUms(const EmChannelReason& tPA, EmTPChannelReason& tUms);
void ConvertEndPtTypeFromStackToUms(const TModuleCallInfo& tModuleInfo, EmTPEndpointType& emTpType, BOOL32 bIsSip);
void ConvertCallDisconnectReasonFromUmsToStack(const EmCnsCallReason& emUmsReason ,EmModuleCallDisconnectReason& emModuleReason);

void ConvertOpTypeFromUmsToStack(const EmTpOprType& emUmsOpType, EmModuleOperateType& emModuleOpType);
void ConvertOpTypeFromStackToUms(const EmModuleOperateType& emModuleOpType, EmTpOprType& emUmsOpType);

void ConvertOprTypeFromUmsToStack(const EmTpOprType& emUmsOpType, EmPAOprType& emModuleOpType);
void ConvertOprTypeFromStackToUms(const EmPAOprType& emModuleOpType, EmTpOprType& emUmsOpType);

//add
void ConvertVideoProfileFromUmsToStack(const EmTpVideoQualityLevel& emProfile, u32& emModuleProfile);
void ConvertVideoProfileFromStackToUms(EmTpVideoQualityLevel& emProfile, const u32& emModuleProfile);
void ConvertVideoResFromStackToUms(EmTpVideoResolution& emRes, const EmModuleVideoResolution& emModuleVideoRes);
void ConvertVideoFormatFromStackToUms(EmTpVideoFormat& emTpFormat, const EmModuleVideoFormat& emPaFormat);


void ConvertVidFormatFromUmsToStack(EmModuleVideoFormat& emPaFormat, const EmTpVideoFormat& emTpFormat);
void ConvertVidFormatFromUmsToStack(EmPAVideoFormat& emPaFormat, const EmTpVideoFormat& emTpFormat);
void ConvertVidFormatFromStackToUms(EmTpVideoFormat& emTpFormat, const EmPAVideoFormat& emPaFormat);
void ConvertVidResFromUmsToStack(EmPAVideoResolution& emPaRes, const EmTpVideoResolution& emTpRes);
void ConvertVidResFromStackToUms(EmTpVideoResolution& emTpRes, const EmPAVideoResolution emPaRes);
void ConvertVidProFromUmsToStack(EmPAProfileMask& emPaPro, const EmTpVideoQualityLevel& emPro);
void ConvertVidProFromStackToUms(EmTpVideoQualityLevel& emPro, const EmPAProfileMask& emPaPro);
//void ConvertAudFormatFromUmsToStack_MDL(EmModuleAudioFormat& emPaFormat, const EmTpAudioFormat& emTpFormat);
void ConvertAudFormatFromUmsToStack(EmPAAudioFormat& emPaFormat, const EmTpAudioFormat& emTpFormat);
void ConvertAudFormatFromStackToUms(EmTpAudioFormat& emTpFormat, const EmPAAudioFormat& emPaFormat);
void ConvertAudFormatFromStackToUms(const EmModuleAudioFormat& emPaFormat, EmTpAudioFormat& emTpFormat);

void ConvertChnlCfgFromUmsToStack(EmPAAACChnlCfg& emPaChnlCfg, const EmTPAACChnlCfg& emTpChnlCfg);
void ConvertChnlCfgFromStackToUms(EmTPAACChnlCfg& emTpChnlCfg, const EmPAAACChnlCfg& emPaChnlCfg);
void ConvertSampleFreqFromUmsToStack(EmPAAACSampleFreq& emPaSampleFreq, const EmTPAACSampleFreq& emTpSampleFreq);
void ConvertSampleFreqFromStackToUms(EmTPAACSampleFreq& emTpSampleFreq, const EmPAAACSampleFreq& emPaSampleFreq);

void ConvertChnlCfgFromMdlStackToUms(EmTPAACChnlCfg& emTpChnlCfg, const EmModuleAudioChnlCfg& emPaChnlCfg);
void ConvertSampleFreqFromMdlStackToUms(EmTPAACSampleFreq& emTpSampleFreq, const EmModuleAudioSampleFreq& emPaSampleFreq);

void ConvertVidInfoFromStackToUms(const TPAUmsVidFormat& tPa, TUmsVidFormat& tUms);
void ConvertVidInfoFromUmsToStack(TPAUmsVidFormat& tPa, const TUmsVidFormat& tUms);

void ConvertAudInfoFromStackToUms(const TPAUmsAudFormat& tPa, TUmsAudFormat& tUms);
void ConvertAudInfoFromUmsToStack(TPAUmsAudFormat& tPa, const TUmsAudFormat& tUms);

void ConvertAliasTypeFromStackToUms(const emModuleCallType& emPaType, TPOUT EmTpAliasType& emTpType);

void ConvertMtOnLineList(const TModuleMtOnlineList& tPaInfo, TTPMtRegInfo& tTpInfo);
void ConvertMcuOnLineList(const TModuleMcuOnlineList& tPaInfo, TTPMcuRegInfo& tTpInfo);
void ConvertModuleAliasFromStackToUms(const TModuleAlias& tPA, TTPAlias& tUms);
void ConvertTpEpTypeFromStackToUms(const emModuleEndpointType& emPaType, EmTPEndpointType& emTpEpType);
void ConvertRegPackInfoFromStackToUms(const TPARegPack& tPaInfo, TRegPackInfoEx& tTpInfo);
void ConvertUmsRegInfoFromStackToUms(TPARegInfoUms& tPaInfo, TUmsRegInfoEx& tTpInfo);
void ConvertCnsRegInfoFromStackToUms(TPARegInfoCns& tPaInfo, TCnsRegInfoEx& tTpInfo);
void ConvertAudChanClosedParamFromUmsToStack( TPOUT HMDLCHANNEL* phChan, TPOUT HMDLAPPCHANNEL* phAppChan, TPOUT u8& bySize, const BOOL32& bIsSnd, const TUmsNodeCapset& tNode );

void ConvertUITypeFromUmsToStack(const EmUIType& emTp, EmPAUIType& emPA);
void ConvertUITypeFromStackToUms(const EmPAUIType& emPA, EmUIType& emTp); 

void ConvertViewEpTypeFromUmsToStack(const EmViewEpType& emTp, EmPAViewEpType& emPA);
void ConvertViewEpTypeFromStackToUms(const EmPAViewEpType& emPA, EmViewEpType& emTp); 

void ConvertSelViewReqFromUmsToStack(const TTPSelViewReq& tTpInfo, TPATPSelViewReq& tPAInfo);
void ConvertSelViewReqFromStackToUms(const TPATPSelViewReq& tPAInfo, TTPSelViewReq& tTpInfo);

void ConvertSelViewIndFromUmsToStack(const TTPSelViewInd& tTpInfo, TPATPSelViewInd& tPAInfo);
void ConvertSelViewIndFromStackToUms(const TPATPSelViewInd& tPAInfo, TTPSelViewInd& tTpInfo);

void ConvertSelViewNtfyFromUmsToStack(const TTPSelViewNtfy& tTpInfo, TPASelViewNtfy& tPAInfo);
void ConvertSelViewNtfyFromStackToUms(const TPASelViewNtfy& tPAInfo, TTPSelViewNtfy& tTpInfo);

void ConvertMdlVendorFromStackToUms(const EmModuleVendorID emPA, EmTpVendorID& emUms );
void ConvertMdlVendorFromUmsToStack(const EmTpVendorID emUms, EmModuleVendorID& emPA );

void ConvertVendorFromStackToUms(const EmPAVendorID emPA, EmTpVendorID& emUms );
void ConvertVendorFromUmsToStack(const EmTpVendorID emUms, EmPAVendorID& emPA );

void ConvertMtVIDEO_FORMATFromStackToUms(const u8 byFramteR, EmTpVideoResolution& emUms);
void ConvertMtVIDEO_FORMATFromUmsToStack(const EmTpVideoResolution emUms, u8& byFramteR);

void ConvertGetVidBaseInfoFromUmsToStack(const TGetVidBaseInfo& tTpInfo, TPAGetVidBaseInfo& tPaInfo);
void ConvertCasecadePollEpReqFromStackToUms(const TPACasecadePollEpReq& tPa, TCasecadePollEpReq& tUms);
void ConvertGetVidInfoFromUmsToStack(const TGetVidInfo& tTpInfo, TPAGetVidInfo& tPaInfo);
void ConvertCasecadePollEpReqFromUmsToStack(const TCasecadePollEpReq& tUms, TPACasecadePollEpReq& tPa);
void ConvertGetVidResFromUmsToStack(const TGetVidInfoRes& tTpInfo, TPAGetVidInfoRes& tPaInfo);

void ConvertGetVidStopResFromUmsToStack(const TStopGetVid& tTpInfo, TPAStopGetVid& tPaInfo);
void ConvertEqpInfoFromStackToUms(const TPAEqpInfo& tPa, TEqpInfo& tUms);

void ConvertEqpInfoFromUmsToStack(const TEqpInfo& tUms, TPAEqpInfo& tPa);


void ConvertGetVidBaseInfoFromStackToUms(const TPAGetVidBaseInfo& tPaInfo, TGetVidBaseInfo& tTpInfo);
void ConvertVmpStyleInfoFromStackToUms(const TPABrdVmpStyle& tPa, TBrdVmpStyle& tUms);
void ConvertGetVidInfoFromStackToUms(const TPAGetVidInfo& tPaInfo, TGetVidInfo& tTpInfo);
void ConvertVmpStyleInfoFromUmsToStack(const TBrdVmpStyle& tUms, TPABrdVmpStyle& tPa);
void ConvertGetVidResFromStackToUms(const TPAGetVidInfoRes& tPaInfo, TGetVidInfoRes& tTpInfo);
void ConvertGetVidStopResFromStackToUms(const TPAStopGetVid& tPaInfo, TStopGetVid& tTpInfo);

void ConverStreamKeyFromStackToUms(TPIN const TModuleEncryptKey& tStreamKey, TPOUT TTPEncrypt& tEnc);
void ConverStreamKeyFromUmsToStack(TPIN const TTPEncrypt& tEnc, TPOUT TModuleEncryptKey& tStreamKey);




/////////////////////////////////////////////////////////
// 电视墙相关

void ConvertHduReqInfoFromStackToUms(const TPAHduPlayReq& tPaReq, TTPHduPlayReq& tReq);

void ConvertHduInfoFromUmsToStack(const TPHduBaseInfo& tBaseInfo, TPAHduBaseInfo& tPaBaseInfo);
void ConvertHduReasonFromUmsToStack(const EmTpHduPlayNackReason& emReason, EmPAHduPlayNackReason& emPaReason);
void ConvertHduVolReasonFromUmsToStack(const EmTpHduSetVolRes& emRes, EmPAHduSetVolRes& emPaRes);
void ConvertHduModeResFromUmsToStack(const EmTpHduChangeChanModeRes& emRes, EmPAHduChangeChanModeRes& emPaRes);

void ConvertHduRunStatusFromUmsToStack(const EmTPHduRunStatus& emTp, EmPAHduRunStatus& emPa);

///////////////////////////////////////////////////////////
// 远遥相关
void ConvertFeccActFromUmsToStack(const TCamAction& tInfo, TMdlFeccStruct& tMdlInfo);
void ConvertFeccActFromsTackToUms(const TMdlFeccStruct& tMdlInfo, TCamAction& tInfo);

void ConvertFeccConfInfoFromUmsToStack(const TConfVidFeccInfo& tInfo, TPAConfVidFeccInfo& tMdlInfo);
void ConvertOpTypeFromUmsToStack(const EmTpOprType& emUmsOpType, EmPAModuleOperateType& emModuleOpType);
void ConvertFeccConfEpListFromUmsToStack(const TConfEpVidFeccList& tInfo, TPAConfEpVidFeccList& tMdlInfo);
void ConvertFeccInfoFromUmsToStack(const TVidFeccInfo& tInfo, TPAVidFeccInfo& tMdlInfo);
void ConvertFeccSourceFromUmsToStack(const TVidSourceInfo& tInfo, TPAVidSourceInfo& tMdlInfo);

void ConvertFeccConfEpListFromStackToUms(const TPAConfEpVidFeccList& tMdlInfo, TConfEpVidFeccList& tInfo);
void ConvertFeccInfoFromStackToUms(const TPAVidFeccInfo& tMdlInfo, TVidFeccInfo& tInfo);

BOOL32 GetFeccUsablePort(u16& wUsablePort);


///////////////////////////add for qt////////////////////////////////
void ConvertQTEncryptLevelFromUmsToStack( TPIN const EmTPConfEncFrequency &emTPEncLevel, TPOUT EmQtKeyFrequency &emPaEncLevel );
void ConvertQTEncryptLevelFromStackToUms( TPIN const EmQtKeyFrequency &emPaEncLevel, TPOUT EmTPConfEncFrequency &emTPEncLevel );
void ConvertQtAliasTypeFromTpToStack(TPIN const EmTpAliasType &emAliasType, TPOUT EmQtAliasType &emQtAliasType );
void ConvertRegTypeFromUmsToStack(TPIN const EmTpConfProtocol &emProType, TPOUT EmPAConfProtocol &emPAType);

void ConvertEpEncryptLevelFromUmsToStack( TPIN const EmTPConfEncFrequency &emTPEncLevel, TPOUT EmPAConfEncFrequency &emPaEncLevel );
void ConvertEpEncryptLevelFromStackToUms( TPIN const EmPAConfEncFrequency &emPaEncLevel, TPOUT EmTPConfEncFrequency &emTPEncLevel );

void ConvertEpEncryptTypeFromStackToUms( TPIN const EmPAConfEncFrequency &emPaEncLevel, TPOUT EmTPEncryptType &emTPEncType );
void ConvertEpEncryptTypeFromStackToUms( TPIN const EmQtKeyFrequency &emPaEncLevel, TPOUT EmTPEncryptType &emTPEncType );
//////////////////////////end for qt////////////////////////////////

#endif // _h_umsdataconvet_h__
