
#ifndef _CRC_HEADER_
#define _CRC_HEADER_
#include "kdvtype.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define CRCCODE_BYTES  4

void   GenCrc4RemTbl();
BOOL32 IsValidCRC4( u8 *pDataBuf, u32 dwLen, u8 byCheckCode );
u8     GenCrc4Code( const u8 *pDataBuf, u32 dwLen );

#ifdef __cplusplus
}
#endif 

#endif 
