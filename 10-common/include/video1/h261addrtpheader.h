#ifndef _H261ADDRTPHEADER_H_
#define _H261ADDRTPHEADER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef  _VXWORKS_
#include "algorithmtype.h"
#else
#include "kdvtype.h"
#define l32 s32
#endif



#define ERR_OK          1
#define ERR_ERROR       0

typedef int RESULT ;
//��H.261�������RTP header
RESULT  H261AddRTPHeader(u8 *pu8H320Bitstream, l32 s32H320BitstreamLen, u8 *pu8H323Bitstream,  l32 *ps32H323BitstreamLen);

//����H261���RTP header�İ汾��Ϣ
void	GetH261AddRTPHeaderVersion(void *pVer, l32 iBufLen, l32 *pVerLen);

#ifdef __cplusplus
};
#endif 

#endif //_H261ADDRTPHEADER_H_
