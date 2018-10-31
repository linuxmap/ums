#ifndef _h_umsstackinterface_h__
#define _h_umsstackinterface_h__
#include "umsinnerstruct.h"
#include "umscommonstruct.h"

class CServMsg;

//init

void InitUmsStack(TUmsStackCallCfg& tCfg, TTPQTEncryptInfo &tTPQTEncryptInfo);
void QuitUmsStack();

//in


//out
u16 UmsMakeCall(const TUmsHandle& tHandle, const TMakeCallPara& tCallPara);
u16 UmsMakeChan(const TUmsHandle& tHandle, const TUmsNodeCapset& tNodeCap, BOOL32 bIsDual);
void UmsAnswerCall( const TUmsHandle& tHandle, const BOOL32 bAnwser, const TMakeCallPara* ptCallPara, EmCnsCallReason emReason);
u16 UmsHangUp(const TUmsHandle& tHandle, EmCnsCallReason emReason);
//add
u16 UmsCloseChan(const TUmsHandle& tHandle, const EmChanType& emType, const TUmsNodeCapset& tNode);

u16 UmsSendMcuCtrl(const TUmsHandle& tHandle, const TUmsMcuChan& tMcuChan, const s32 nMsgType, const void *pBuf, const s32 nSize);
u16 UmsSendConfCtrl( const TUmsHandle& tHandle, const s32 nMsgType, u8 *pBuf, const s32 nSize );
u16 UmsSendDualConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize);
u16 UmsSendPollConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize);
u16 UmsSendAudMixConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize);
u16 UmsSendCnsUIConfCtrl(const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize);
u16 UmsSendChanCtrl( const TUmsHandle& tHandle, const s32 nMsgType, const void *pBuf, const s32 nSize );

//void PA_Register( const s32 nAppId, TPASipRegistrarCfg *pPARegister, void *pRegHandle );

void UmsRegister(const TUmsHandle& tHandle, TUmsSipRegCfg& tRegCfg, TTPAlias atAlias[], u16 wAliasNum);
void UmsGkRegister(const TUmsHandle& tHandle, TRegCfg& tRegCfg, u16 wAliasNum);
void UmsUnregister(const TUmsHandle& tHandle, const EmTpRegType& emTpProtocol);

void ProcMcuNonStandardMsg( CServMsg& cServMsg, TUmsHandle& tHandle );

#endif // _h_umsstackinterface_h__
