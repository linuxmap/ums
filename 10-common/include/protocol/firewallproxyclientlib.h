/****************************************************************************
  ģ����   ����Խ����ǽ&NAT����Client��
  �ļ���   ��FirewallProxyClientLib.h
  ����ļ� ��FirewallProxyClientLib.cpp
  �ļ����� �����崩Խ����ǽ&NAT
             ����ͻ���Lib��ʹ��ͷ�ļ�
  ����	   ��Tony
  �汾	   ��1.0
----------------------------------------------------------------------------
  �޸ļ�¼:
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/12/09    1.0
******************************************************************************/
#ifndef FIREWALLPROXYCLIENTLIB_H_
#define FIREWALLPROXYCLIENTLIB_H_

#include "osp.h"

#include "pxyadapter.h"
#include "protocolcommonpublic.h"
//using namespace H323ADAPTER_FOR_V50PXY;


//=================================================================================
//              Protocol type
//=================================================================================
#ifndef PROTOCOL_H323STACK
#define PROTOCOL_H323STACK            0
#define PROTOCOL_OSPSTACK             1
#endif

#define VER_PXYC (const char *)"PxyClient v40.00.01.00.140512(CBB)"

#ifdef WIN32
#define PXY_CLINET_CALLBACK __cdecl
#else
#define PXY_CLINET_CALLBACK
#endif

typedef s32 (PXY_CLINET_CALLBACK* CBPxyClientState)     (const BOOL32 bIsPxyClientRunning);
typedef s32 (PXY_CLINET_CALLBACK* CBPxyClientPowerOn)   (const BOOL32 bIsPxyClientPowerOn);

#if (defined(_IOS_PLATFORM_) || defined(_ANDROID_))
#define PXY_CLIENT_DATASWITCH_PORT 60606
#endif

//�ص�����ָ��ṹ
typedef struct tagPxyCallBackFunc
{
    CBPxyClientState	m_fpPxyClientState;
    CBPxyClientPowerOn  m_fpPxyClientPowerOn;

	tagPxyCallBackFunc()
	{
		m_fpPxyClientState      = NULL;
        m_fpPxyClientPowerOn    = NULL;
	}
}TPxyCallBackFunc, *LPTPxyCallBackFunc;

typedef struct tagClientCfgStruc
{
public:
	// Client Cfg param.
	u32 m_dwSrvIpAddr;                  // PxyServer��Ip��ַ
	u16 m_wSrvPort;                     // PxyServer��Osp�˿�
	u32 m_dwRegisterIpAddr;             // PxyClient�ı��˵�ַ
    u16 m_dwRegisterIpPort;             // ��ʱû��ʹ��
	u16 m_wStartMediaPort;              // Chan�˿ڹ�NAT��ʼ�˿�(UDP)
	u16 m_wTerminalNum;                 // �ն������Ŀ
	u8  m_chClientName[32];             // Client Name
	u16 m_wTelenetPort;                 // PxyClient ��TelenetPort
    u16 m_wRtpPort;                     // RTP�˿�
    u16 m_wRtcpPort;                    // RTCP�˿�

    //add 2007.05.30
    s32	m_nProductIdSize;
	u8	m_abyProductId[PXY_LEN_256];		// ��Ʒ��
	s32	m_nVerIdSize;
	u8	m_abyVersionId[PXY_LEN_256];		// �汾��
public:
	tagClientCfgStruc()
	{
		memset(this, 0, sizeof(tagClientCfgStruc));
	}
    void SetClientName(s8 *pszName)
    {
        if (pszName == NULL)
        {
            return;
        }

        u8 byLen = strlen(pszName);
        if (byLen > sizeof(m_chClientName)-1)
        {
            byLen = sizeof(m_chClientName)-1;
        }
        memcpy(m_chClientName, pszName, byLen);
        m_chClientName[byLen] = '\0';
        return;
    }

	//���ò�Ʒ��
	void SetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyProductId, 0, sizeof(m_abyProductId) );
		s32 nReal = min(max(PXY_LEN_1, nLen), PXY_LEN_256);
		m_nProductIdSize = nReal;
        if(nLen >= PXY_LEN_1)
		{
			memcpy(m_abyProductId, pbyId, nReal);
		}
	}
	//��ȡ��Ʒ�ų���
	s32 GetProductIdSize()
	{
		return m_nProductIdSize;
	}
	//��ȡ��Ʒ��
	s32 GetProductId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nProductIdSize); 
		memcpy(pbyId, m_abyProductId, nReal);
		return nReal;
	}
	//���ð汾��	
	void SetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return ;
		}
		memset( m_abyVersionId, 0, sizeof(m_abyVersionId) );
		s32 nReal = min(max(PXY_LEN_1, nLen), PXY_LEN_256);
		m_nVerIdSize = nReal;
        if(nLen >= PXY_LEN_1)
		{
			memcpy(m_abyVersionId, pbyId, nReal);
		}
	}
	//��ȡ�汾�ų���
	s32 GetVersionIdSize()
	{
		return m_nVerIdSize;
	}
	//��ȡ�汾��
	s32 GetVersionId(u8 *pbyId, s32 nLen)
	{
		if(pbyId == NULL|| nLen <= 0 )
		{
			return 0;
		}
		s32 nReal = min(nLen, m_nVerIdSize); 
		memcpy(pbyId, m_abyVersionId, nReal);
		return nReal;
	}
}TClientCfgStruc, *PTClientCfgStruc;

// ��ʼ��PxyClientģ��
PROTO_API u32 InitPxyClient(TClientCfgStruc &gClientCfg, u8 byProtocol);
// ����ʼ��PxyClientģ��
PROTO_API void DestroyPxyClient();

PROTO_API u32 UpdatePxyClientLocalIP(u32 dwNewLocalIP);

/*====================================================================
��	 ��   ��: SetPxyClientCallBack
��	      ��: ע��Ӧ�ûص�����
�� �� ʵ  ��: 
����ȫ�ֱ���: ��
�������˵��: lpCallBackFunc - �ص������ṹָ��
��   ��   ֵ: �ɹ� - TRUE
			  ʧ�� - FALSE
====================================================================*/
PROTO_API s32 SetPxyClientCallBack( LPTPxyCallBackFunc lpCallBackFunc);

#if (defined(_IOS_PLATFORM_) || defined(_ANDROID_))

/************************************************************************/
/*  Additional pinhole mechanism for Android and iOS systems */
/************************************************************************/
PROTO_API s32 PxyClientManualProbe(s32 hSocket, u32 dwLocalIpAddr, u16 wLocalPort, BOOL32 bRTP);

/************************************************************************/
/*  Used to control the special workflow when the process terminating or the stack restarting operations*/
/************************************************************************/
extern BOOL32 g_bLibraryTerminiting;

#endif

#endif //FIREWALLPROXYCLIENTLIB_H_
