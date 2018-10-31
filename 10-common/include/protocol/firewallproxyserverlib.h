/****************************************************************************
  ģ����   ����Խ����ǽ&NAT����Server��                        
  �ļ���   ��FirewallProxyServerLib.h
  ����ļ� ��FirewallProxyServerLib.cpp
  �ļ����� �����崩Խ����ǽ&NAT
             ��������Lib��ʹ��ͷ�ļ�
  ����	   ��Tony
  �汾	   ��1.0
----------------------------------------------------------------------------
  �޸ļ�¼:
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2004/12/09    1.0         
******************************************************************************/
#ifndef FIREWALLPROXYSERVERLIB_H_
#define FIREWALLPROXYSERVERLIB_H_

#include "osp.h"

//#define UNIT_TEST
extern u16     UNIT_TEST_TYPE;

#define VER_PXYS (const char *)"PxyServer40.00.01.06.131108(CBB)"

// add by gxb 2011-11-24
#define MAX_VIRTUAL_IP_COUNT    (u16)10
#define MAX_DMZ_IP_COUNT        (u16)3

//Proxy Server������Ϣ
struct TProxyServerCfg
{
	BOOL32  m_bStartPxy;
    BOOL32  m_bStartMp;
    u32     m_dwGKIpAddr;                           //GK��IP��ַ
	u16     m_wGKRasPort;                           //GK��Ras�˿�
	u32     m_dwSrvIpAddr;                          //PROXY SERVERʹ�õ�IP��ַ
	u16     m_wSrvRasPort;                          //PROXY SERVER������˿�
	u16     m_wSrvH245Port;
	u16     m_wOspTcpPort;
    u16     m_wRtpPort;                             //RTP�˿�
    u16     m_wRtcpPort;                            //RTCP�˿�
    u16     m_wMediaBasePort;                       //������ʼ�˿ڵ�ַ
	u16     m_wVirtualIPNum;                        //����IP������
	u32     m_dwVirtualIPAddr[MAX_VIRTUAL_IP_COUNT];//����IP�ĵ�ַ
	BOOL32  m_bIsForceGKRoute;                      //�Ƿ�ʹ��GK·�� 2013/05/09
    BOOL32  m_bUseDmzAddr;                          //�Ƿ����ô��������DMZӳ��
#ifdef _ENABLE_MULTIPLUE_DMZ_SUPPORT_
    //DMZ support for PXYSVR
    u32     m_dwSrvDmzRouterIP[MAX_DMZ_IP_COUNT];	    //���������DMZӳ���ַ
    u32     m_dwSrvDmzHostIP[MAX_DMZ_IP_COUNT];	    //���������DMZӳ���ַ
#else
    u32     m_dwSrvDmzIpAddr;
#endif
    //To be confirmed whether has something to do with DMZ
    BOOL32	m_b323UseSpecialIP;                     //323ָ��ʹ��m_dwSrvIpAddr�ĵ�ַ
};

extern u16 InitPxy();
extern u16 InitPxyServer(TProxyServerCfg &tCfg);
extern void UnInitPxyServer();


#endif

