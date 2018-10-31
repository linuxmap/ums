#ifndef _h_stackmsgconvert_h__
#define _h_stackmsgconvert_h__

#include "umscommonstruct.h"
#include "umsinnerstruct.h"
#include "kdvsipadapter.h"
#include "regstruct.h"
#include "modulecallstruct.h"
#include "tpmodulestruct.h"


BOOL32 ConvertRegFromStackToApp(RegisterRequest& tStackInfo, TCnsRegInfo& tAppInfo);
void ConvertRegFromAppToStack(TCnsRegInfo& tAppInfo, RegisterRequest& tStackInfo);

void ConvertRegReasonFromAppToStack(TCnsRegRetResult& tAppRet, EmRegisterReason& tStackReason);

void ConvertRegInfoTypeToAppStack(EmGetRegInfoType tType, EmSIPRegNSMType& tSipType);

void ConvertTpAliasTypeToAppStack(EmTpAliasType tType ,EmSipAliasType& tSipType);

void ConvertPtTypeTpAppStack(EmTPEndpointType tType, EmSipEndpointType& tSipType);

void ConvertRegInfoFromAppToStack(const TReqRegInfoEx& tAppRegInfo, TSipRegPackXmlB2& tStackRegInfo);

void ConvertCnsRegInfoFromAppToStack(const TCnsRegData& tAppData, TSipRegInfoCns& tStackInfo);

void ConvertUmsRegInfoFromAppToStack(const TUmsRegData& tAppData, TSipRegInfoUms& tStackInfo);


void ConverUmsQueryInfoFromStackToApp(const TSipRedirectInfo& tSipInfo, TTPAlias& tAlias);

#endif // _h_stackmsgconvert_h__
