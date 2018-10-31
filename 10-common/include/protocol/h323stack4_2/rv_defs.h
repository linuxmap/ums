/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV_DEFS_H
#define _RV_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "rvcommon.h"


/* --- transport address --- */

typedef enum
{
  cmTransportTypeIP, /* No route */
  cmTransportTypeIPStrictRoute,
  cmTransportTypeIPLooseRoute,
  cmTransportTypeNSAP,
  cmTransportTypeIPv6
} cmTransportType;

typedef enum
{
  cmDistributionUnicast,
  cmDistributionMulticast
} cmDistribution;


#if (RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_IPV4_ONLY)

typedef struct
{
    cmTransportType type; /* Type of address - must always be cmTransportTypeIP */
    RvUint32        ip; /* IPv4 address */
    RvUint16        port;
    cmDistribution  distribution; /* Distribution type of this address. Valid for H.245 addresses */
} cmTransportAddress;



#elif (RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_OLD)

#define cmRouteSize (7) /* for luck */

typedef struct
{
    RvUint16        length; /* length in bytes of route */
    RvUint32        ip; /* IPv4 address */
    RvUint16        port;
    cmTransportType type;
    RvUint32        route[cmRouteSize];
    cmDistribution  distribution; /* Distribution type of this address. Valid for H.245 addresses */
} cmTransportAddress;


#elif (RV_H323_TRANSPORT_ADDRESS == RV_H323_TRANSPORT_ADDRESS_ANY)

#define cmRouteSize (7) /* for luck */

typedef struct
{
    RvUint32        ip; /* IPv4 address */
    RvUint16        length; /* length in bytes of route */
    RvUint32        route[cmRouteSize];
} ipAddressV4;

typedef struct
{
    RvUint8         ip[16]; /* IPv6 address */
    short           scopeId;
} ipAddressV6;

union ipAddress
{
    ipAddressV4 v4;
    ipAddressV6 v6;
};

typedef struct
{
    cmTransportType type;
    union ipAddress addr;
    RvUint16        port;
    cmDistribution  distribution; /* Distribution type of this address. Valid for H.245 addresses */
} cmTransportAddress;

/* example of usage:
cmTransportAddress TA;

TA.type =           Address TYPE.
TA.addr.v6.ip =     IP v6, or-
TA.addr.v4.ip =     IP v4, and maybe-
TA.addr.v4.route =  IP v4 route.
TA.port =           Port for any IP type
TA.distribution =   Distribution for any IP type
*/

#endif



typedef enum
{
    cmQ931setup = 5,
    cmQ931callProceeding = 2,
    cmQ931connect = 7,
    cmQ931alerting = 1,
    cmQ931releaseComplete = 90,
    cmQ931status = 125,
    cmQ931facility = 98,
    cmQ931statusEnquiry = 117,
    cmQ931statusInquiry = 117,
    cmQ931progress = 3,
    cmQ931setupAck = 13,
    cmQ931setupAcknowledge = 13,
    cmQ931information = 123,
    cmQ931notify = 110,
    cmQ931userInformation = 32
} cmCallQ931MsgType;

/* The stage at which it is allowed to transfer the H.245 address to the remote */
typedef enum
{
    cmTransH245Stage_setup,             /* Earliest H.245 possible, may send/act on addresses in all messages */
    cmTransH245Stage_callProceeding,    /* The remote can send the address in the C.P. message */
    cmTransH245Stage_alerting,          /* Only in the alerting message can the remote send the address */
    cmTransH245Stage_connect,           /* The remote must wait for the connect message (normal) */
    cmTransH245Stage_early,             /* our early H.245, sends addresses in setup and connect only */
    cmTransH245Stage_facility,          /* There will be no automatic sending of the address */
    cmTransH245Stage_noH245             /* no support for H.245, sends facility NoH245  */
} cmH245Stage;

/* the way to use annex E connection for Q.931 */
typedef enum
{
    cmTransUseAnnexE,                   /* Force the use of annex E */
    cmTransNoAnnexE,                    /* Force the use of TPKT */
    cmTransPreferedAnnexE,              /* Initiate a both annex E
                                           and TPKT with preference to annex E*/
    cmTransPreferedTPKT                 /* Initiate a both annex E
                                           and TPKT with preference to TPKT*/
} cmAnnexEUsageMode;

//////////////////////////////////////////////////////////////////////////
// Quantum encryption
#if defined _ENABLE_QUANTUM_PROJECT_ && defined _KDV_RV_H323_STACK_
#ifndef LEN_DHKEY_MAX
#define LEN_DHKEY_MAX               256

#include "kdvtype.h"
#endif

#ifndef DES_ENCRYPT_BYTENUM
#define DES_ENCRYPT_BYTENUM         8 // DES 加密为8字节对齐
#define AES_ENCRYPT_BYTENUM         16// DES 加密为16字节对齐
#endif

//s8  szInitKey[AES_ENCRYPT_BYTENUM] = {0};
#define MAX_H323_DATA_BUF_SIZE      (32000<<4)
#define QT_MAX_SIGNAL_BUFFER_SIZE   (32000<<4)
#define MAX_QT_KEY_SIZE             16
#define LEN_CALLID					16

#ifndef DES_ENCRYPT_MODE
#define DES_ENCRYPT_MODE            (u8)0      //DES加密模式
#define AES_ENCRYPT_MODE            (u8)1      //AES加密模式
#define ENCRYPT_KEY_SIZE            (u8)32     //密钥长度 取其中的较大值
#define DES_ENCRYPT_KEY_SIZE        (u8)8      //DES密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_A (u8)16  //AES Mode-A 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_B (u8)24  //AES Mode-B 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_C (u8)32  //AES Mode-C 密钥长度
#endif

//#ifndef MAX_LEN_QUANTUM_ID
//    #define MAX_LEN_QUANTUM_ID 32
//#endif

#if (RV_NET_TYPE == RV_NET_IPV6)
typedef cmTransportAddress tagQTIPAddr;
#else
typedef unsigned int tagQTIPAddr;
#endif

typedef struct tagQuantumKey
{
	//HCALL		m_hsCall;
	void*		m_hsCall;
	u32         m_hQtCall;			//二期量子呼叫句柄，QtInitCall时生成
    //////////////////////////////////////////////////////////////////////////
    //Jacky Wei: Per the discussion together with TPS team, we'll use a same key
    //  for all the joint candidates of one conference (MT or MCU) which will be
    //  difference with standard H.235 encryption.
	RvUint8		szInitKey[AES_ENCRYPT_BYTENUM + 1];
    //RvUint8   szSelfKey[AES_ENCRYPT_BYTENUM];
    //RvUint8   szPeerKey[AES_ENCRYPT_BYTENUM];
    //////////////////////////////////////////////////////////////////////////

    tagQTIPAddr m_tSelfQID;
    tagQTIPAddr m_tPeerQID;
    RvInt8*     m_pszMaterialBuf;
    RvUint32    m_wMaterialBufLen;

    RvUint8     m_byAesMode;
    RvUint32    m_emDesMode;
    RvUint8     m_byEncryptMode;
    RvUint8     m_byDecryptMode;

    tagQTIPAddr m_tPeerQIP;

    //RvUint8*  m_pbyEncryptOutBuf;
    RvUint8     m_byPadNum;
    RvUint8*    m_pbyInTempBuf;
    //RvUint32  m_nRealSize;
    //RvUint8*  m_pRealData;        //只是一个指向指针，不会malloc内存
    RvUint8*    m_pbyOutBuf;        //加密或解密输出buf
	RvInt32     m_hSocket;
    /*
    tagQuantumKey()
    {
        Reset();
    }
    void Reset()
    {
        m_byEncryptMode     = AES_ENCRYPT_MODE;
        m_byDecryptMode     = DES_ENCRYPT_MODE;
        m_emDesMode         = 1;//qfDES_cbc;
        m_byAesMode         = 2;//MODE_CBC;

        const u8 initkey[]  = {8, 7, 6, 5, 4, 3, 2, 1};
        m_dwPeerIP          = 0;//inet_addr("172.16.72.230");
        memcpy(szInitKey, initkey, sizeof(initkey));
        
        m_pszMaterialBuf    = (RvInt8*)malloc(MAX_QT_KEY_SIZE + 4);
        m_wMaterialBufLen   = MAX_QT_KEY_SIZE;
        memset(m_pszMaterialBuf, 0, MAX_QT_KEY_SIZE+4);
        memcpy(m_pszMaterialBuf, szInitKey, MAX_QT_KEY_SIZE);
        
        if (m_pbyOutBuf)
        {
            delete[] m_pbyOutBuf;
            m_pbyOutBuf     = NULL;
        }
        m_pbyOutBuf         = (u8*)malloc(MAX_H323_DATA_BUF_SIZE);
        if (m_pbyInTempBuf)
        {
            delete[] m_pbyInTempBuf;
            m_pbyInTempBuf  = NULL;
        }
        m_pbyInTempBuf      = (u8*)malloc(MAX_H323_DATA_BUF_SIZE);
    }
    */
}TQuantumKey;

//RvUint16        FreeQuantumID  (IN RvUint32 dwPeerQuantumID);
// 
// #ifdef WIN32
// 	#pragma comment( lib, "ws2_32.lib" ) 
// 	#pragma pack( push )
// 	#pragma pack( 1 )
// 	#define window( x )	x
// 	#ifndef PACKED
// 		#define PACKED
// 	#endif
// #else
// 	#include <netinet/in.h>
// 	#define window( x )
// 	#if defined(__ETI_linux__)
// 		#define PACKED
// 	#else
// 		#ifdef PACKED
// 			#undef PACKED
// 		#endif
// 		#define PACKED __attribute__ ((packed))	// 取消编译器的优化对齐
// 	#endif
// #endif

#define QUANTUM_HDR_MAGIC   0xFFDEFFDF
#define QUANTUM_HDR_CHECK   0xDFFFEDFF

#pragma pack(1)   			// 1 bytes对齐
typedef struct tagQuantumHdr
{
    RvUint32    m_dwMagic;
	RvUint32    m_dwCheck;
    RvUint32    m_dwSize;
    RvUint16    m_wPadding;
	u64			m_hQtKey;	
	RvUint8     m_achCallID[LEN_CALLID];
}TQuantumHdr;
#pragma pack()			//恢复对齐状态
//__attribute__ ((packed)) TQuantumHdr ;


typedef enum HOOK_PROCESS
{
    HOOK_NORMAL = 0,
    HOOK_ENCODE,
    HOOK_DECODE,
    HOOK_IGNORE,
}HOOK_PROCESS;

#else
#define HOOK_PROCESS RvBool
#endif
//End of Quantum Project related definitions
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif


#endif  /* _RV_DEFS_H */
