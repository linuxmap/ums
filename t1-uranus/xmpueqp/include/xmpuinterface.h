#ifndef _ums_interface_h_
#define _ums_interface_h_

#include "tpcommonstruct.h"
#include "xmpuinnerstruct.h"
#include "mediadefine.h"

// media init
BOOL32 XmpuInitMediaClient(s8* pchMqUrl, s8* pchModID);
BOOL32 MediaInitMeeting(IN TXmpuMettingInfo tInfo);
BOOL32 MediaReleaseMeeting(OUT HMEDIARES dwUserDate);
void GetMediaSource(s8* pszMqUrl, s8* pszMasterId, TMediaEqpMgr& byVmpNum);

// media vmp 
BOOL32 MediaStartVmp(OUT HMEDIARES& dwVmpHandle, IN APPHANDLE dwEqpID, IN TXmpuVmpParam tInfo); // for vmp or vmptp
void MediaReleaseVmp(IN HMEDIARES dwVmpHandle);// for vmp or vmptp
BOOL32 MediaChangeVmp(IN HMEDIARES& dwVmpHandle,  IN TTVmpStartParam tInfo, IN u8 byEncNum); // for vmp
BOOL32 MediaChangeVmpTP(IN HMEDIARES& dwVmpHandle,  IN TVmpStartInfo tInfo); // for vmptp
BOOL32 MediaUpdateLineSide(IN HMEDIARES& dwVmpHandle,  IN TVmpSpeakerFlag tInfo);
void MediaReqVmpIFrame(IN HMEDIARES dwVmpHandle, IN u32 dwChnId);
BOOL32 MediaSetVmpDecAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, IN TTPTransAddr tInAddr);
BOOL32 MediaSetVmpEncAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, IN TTPTransAddr tInAddr);
BOOL32 MediaGetVmpDecAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr);
BOOL32 MediaGetVmpEncAddr(IN HMEDIARES dwVmpHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr);
BOOL32 MediaGetVmpVipNum(IN HMEDIARES dwVmpHandle, OUT u8& byMaxStyle,OUT u8& byVipNum);

// media base
BOOL32 MediaStartBase(OUT HMEDIARES& dwBasHandle, IN APPHANDLE dwEqpID, IN TXmpuBasParam tParam);
void MediaReleaseBase(IN HMEDIARES dwBasHandle);
void MediaSetBasParam(IN HMEDIARES dwBasHandle, IN TXmpuChgBasInfo tInfo);
void MediaReqBasIFrame(IN HMEDIARES dwBasHandle, IN u8 byChnId);
BOOL32 MediaSetBasDecAddr(IN HMEDIARES dwBasHandle, IN TTPTransAddr tInAddr);
BOOL32 MediaSetBasEncAddr(IN HMEDIARES dwBasHandle, IN u8 byChnId, IN TTPTransAddr tInAddr);
BOOL32 MediaGetBasDecAddr(IN HMEDIARES dwBasHandle, OUT TTPTransAddr& tOutAddr);
BOOL32 MediaGetBasEncAddr(IN HMEDIARES dwBasHandle, IN u8 byChnId, OUT TTPTransAddr& tOutAddr);

// media mix
BOOL32 MediaStartMix(OUT HMEDIARES& dwMixHandle, IN APPHANDLE dwEqpID, IN TXmpuMixParam tParam);
BOOL32 MediaStartVac( IN HMEDIARES dwMixHandle );
void MediaStopVac( IN HMEDIARES dwMixHandle );
void MediaReleaseMix(IN HMEDIARES dwVmpHandle);
BOOL32 MediaAddMixMember( IN HMEDIARES& dwMixHandle, IN TXmpuMixMember tMember );
void MediaDelMixMember( IN HMEDIARES& dwMixHandle, IN u8 byChnID );
BOOL32 MediaGetMixNChnID( IN HMEDIARES& dwMixHandle, OUT u8& byNChnNum, OUT u8* byNChnID );
BOOL32 MediaGetMixN1ChnID( IN HMEDIARES& dwMixHandle, OUT u8& byNChnNum, OUT u8* byNChnID );
void MediaSetKeepTime(IN HMEDIARES dwMixHandle, IN u32 dwKeepTime);
void MediaSetForceMix( IN HMEDIARES dwMixHandle , IN u8 byChnID, IN BOOL32 bStart);
BOOL32 MediaGetMixDecAddr(IN HMEDIARES dwMixHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr);
BOOL32 MediaGetMixEncAddr(IN HMEDIARES dwMixHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr);
void MediaMixSetSynId(IN u32 dwSynID,  IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE64);
void MediaMixFreeSynId(IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE64);

//Aud bas
BOOL32 MediaStartAudBas(OUT HMEDIARES& dwMixHandle, IN APPHANDLE dwEqpID, IN TXmpuAudBasParam tParam);
BOOL32 MediaSetAudBasDecAddr(IN HMEDIARES dwBasHandle, IN TTPTransAddr tInAddr);
BOOL32 MediaSetAudBasEncAddr(IN HMEDIARES dwBasHandle, IN u32 dwChnId, IN TTPTransAddr tInAddr);
BOOL32 MediaGetAudBasDecAddr(IN HMEDIARES dwBasHandle, OUT TTPTransAddr& tOutAddr);
BOOL32 MediaGetAudBasEncAddr(IN HMEDIARES dwBasHandle, IN u32 dwChnId, OUT TTPTransAddr& tOutAddr);
void MediaSetAudBasParam(IN HMEDIARES dwBasHandle, IN TXmpuChgAudParam tParam);
void MediaAudBasSetSynId(IN u32 dwSynID,  IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE64);
void MediaAudBasFreeSynId( IN u8 byNum, IN TXmpuSynChn* ptSynChn, IN s8* pchE64);

u32 GetVmpEqpID(u32 dwHandle);
u32 GetBasEqpID(u32 dwHandle);
u32 GetMixEqpID(u32 dwHandle);

void ShowVmpMap();
void ShowBasMap();
void ShowMixMap();

#endif // _ums_interface_h_