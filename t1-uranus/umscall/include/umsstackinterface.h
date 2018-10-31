#ifndef _h_umsstackinterface_h__
#define _h_umsstackinterface_h__
#include "umsinnerstruct.h"
#include "umscommonstruct.h"

void ConvertRegResultDataFromStackToUms(const u8 *pBuf,TUCSipRegResult &tSipRegResult);

//out
u16 UmsMakeCall(const TUmsHandle& tHandle, const TMakeCallPara& tCallPara);
u16 UmsMakeChan(const TUmsHandle& tHandle, TUmsNodeCapset& tCallPara, BOOL32 bIsDual);
void UmsAnwserCall( const TUmsHandle& tHandle, const BOOL32 bAnwser, const TMakeCallPara* ptCallPara, EmCnsCallReason emReason);
u16 UmsHangUp(const TUmsHandle& tHandle, EmCnsCallReason emReason = EmCnsCallReason_hungup);
u16 UmsClearConference(const TUmsHandle& tHandle);
//add
u16 UmsCloseChan(const TUmsHandle& tHandle, const EmChanType emType, const TUmsNodeCapset& tNode);

u16 UmsMakeSendDual(const TUmsHandle& tHandle, TUmsNodeCapset& tCapSet);
u16 UmsAnswerSendDual(const TUmsHandle& tHandle, TUmsNodeCapset& tCapSet, BOOL32 bRes = TRUE);
u16 UmsStopDual(const TUmsHandle& tHandle, EmTPChannelReason emReason = emTPChannelDisconnectNormal);


u16 UmsSendConfCtrl( const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize );
u16 UmsSendChanCtrl( const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize );

void UmsRegister(const TUmsHandle& tHandle, TUmsSipRegCfg& tRegCfg, TTPAlias atAlias[], u16 wAliasNum);
void UmsGkRegister(const TUmsHandle& tHandle, TRegCfg& tRegCfg, u16 wAliasNum);
void UmsUnregister(const TUmsHandle& tHandle, EmRegType emRegType);

void UmsReqRegInfo(const TUmsHandle& tHandle, TUmsSipRegCfg& tRegCfg, const EmGetRegInfoType& tType, u32 dwSipHandle, u32 dwGkHandle);
u16 UmsSendCnsUIConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize);

u16 UmsCallSendMcuCtrl(const TUmsHandle& tHandle, const TUmsMcuChan& tMcuChan, const s32 nMsgType, const void *pBuf, const s32 nSize);

void UmsSetQTEncryptInfo( u16 wEvent, const TUmsHandle& tHandle, const void* pBuf, u16 wSize );

#endif // _h_umsstackinterface_h__
