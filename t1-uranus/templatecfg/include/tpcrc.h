
#ifndef _TPCRC_HEADER_
#define _TPCRC_HEADER_
#include "kdvtype.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define CRCCODE_BYTES  4

void   TpGenCrc4RemTbl();
BOOL32 TpIsValidCRC4( u8 *pDataBuf, u32 dwLen, u8 byCheckCode );
u8     TpGenCrc4Code( const u8 *pDataBuf, u32 dwLen );

#ifdef __cplusplus
}
#endif 

#endif 
