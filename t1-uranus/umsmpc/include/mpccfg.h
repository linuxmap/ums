#ifndef _h_mpccfg_h__
#define _h_mpccfg_h__


#include "tpsys.h"
#include "tpstruct.h"
void ReadMpcCfg();

u32 GetUmsListenIp();
u16 GetUmsListenPort();

u32 GetLocalIP();
u16 GetStartPort();

u16 GetMpcVersion();
const s8* GetMpcAlias();

void WriteSetTime();


#endif // _h_mpccfg_h__

