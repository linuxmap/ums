#ifndef _h_adaptercfg_h__
#define _h_adaptercfg_h__
#include "tpsys.h"
void ReadAdapterCfg();

u32 GetUmsListenIp();
u16 GetUmsListenPort();

u32	GetLocalIP();
u32 GetLocalIpByDstIp(u32 dwDstip);

#endif // _h_adaptercfg_h__
