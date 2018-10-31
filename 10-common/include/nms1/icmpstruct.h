/*=============================================================================
ģ   ��   ��: ��
��   ��   ��: IcmpStruct.h
�� ��  �� ��: ��
�ļ�ʵ�ֹ���: ICMPЭ�� �ṹ����
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2006/05/30  4.0     ���        ����
=============================================================================*/

#ifndef __ICMPSTRUCT_H__
#define __ICMPSTRUCT_H__

#include "kdvtype.h"

#ifdef WIN32
#include <WINSOCK2.H>
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#endif  //  WIN32

//IPͷ�汾
enum enumIPVersion
{
    emIPv4  = (u8)4 << 4,       //  01000000    4 << 4
    emIpv6  = (u8)6 << 4        //  01100000    6 << 4
};

//IPͷ��С����, ��u32����
#define MIN_IPHEADER_LEN        (u8)5

//ICMP������Ϣ��󳤶�, ��u8����
#define MAX_ICMP_SENDMSG_LEN    (u16)10 * 1024

//IPͷ��������
enum enumPrecedence
{
    emNetworkControl        = (u8)7 << 5,   //  111 - Network Control
    emInternetworkControl   = (u8)6 << 5,   //  110 - Internetwork Control
    emCRITICECP             = (u8)5 << 5,   //  101 - CRITIC/ECP
    emFlashOverride         = (u8)4 << 5,   //  100 - Flash Override
    emFlash                 = (u8)3 << 5,   //  011 - Flash
    emImmediate             = (u8)2 << 5,   //  010 - Immediate
    emPriority              = (u8)1 << 5,   //  001 - Priority
    emRoutine               = (u8)0 << 5,   //  000 - Routine
};

//ICMP��Ϣ����
enum enumIcmpType
{
    emDstUnreachable        = (u8)3,        // �Զ˲��ɼ�
    emTimeExceeded          = (u8)11,       // ��ʱ
    emParamError            = (u8)12,       // ��������
    emSourceQuench          = (u8)4,        // Source Quench
    emRedirect              = (u8)5,        // �ض���
    emEcho                  = (u8)8,        // ��Ӧ
    emEchoReply             = (u8)0,        // ��Ӧ��Ӧ
    emTimeStamp             = (u8)13,       // ʱ���
    emTimeStampReply        = (u8)14,       // ʱ�����Ӧ
    emInfoReq               = (u8)15,       // ��Ϣ����
    emInfoReply             = (u8)16,       // ��Ϣ��Ӧ
};

//�Զ˲��ɼ�ԭ��
enum enumIcmpCodeUnreachable
{
    emUnreachNet        = (u8)0,// net unreachable
    emUnreachHost       = (u8)1,// host unreachable
    emUnreachProt       = (u8)2,// protocol unreachable
    emUnreachPort       = (u8)3,// port unreachable
    emUnreachFrag       = (u8)4,// fragmentation needed and DF set
    emUnreachRoute      = (u8)5 // source route failed
};

//��ʱԭ��
enum enumIcmpCodeTime
{
    emTimeTTL           = (u8)0,// time to live exceeded in transit
    emTimefrag          = (u8)1 // fragment reassembly time exceeded
};

//�ض���ԭ��
enum enumIcmpCodeRedirect
{
    emRedirectNet       = (u8)0,// Redirect datagrams for the Network
    emRedirectHost      = (u8)1,// Redirect datagrams for the Host
    emRedirectTOSNet    = (u8)2,// Redirect datagrams for the Type of Service and Network
    emRedirectTOSHost   = (u8)3 // Redirect datagrams for the Type of Service and Host
};

//  IP Header -- RFC 791
//    0                   1                   2                   3   
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |Version|  IHL  |Type of Service|          Total Length         |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |         Identification        |Flags|      Fragment Offset    |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |  Time to Live |    Protocol   |         Header Checksum       |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                       Source Address                          |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                    Destination Address                        |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                    Options                    |    Padding    |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIPHDR
{
    /*=============================================================================
    �� �� ��:tagIPHDR
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    tagIPHDR()
    {
        memset( this, 0, sizeof (tagIPHDR) );
    }

    /*=============================================================================
    �� �� ��:SetVersion
    ��    ��:���ð汾��
    ��    ��:enumIPVersion enumVersion      [in]    emIPv4/emIpv6
    ע    ��:The Version field indicates the format of the internet header
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline void SetVersion(enumIPVersion emIPVersion)
    { m_byVIHL = (m_byVIHL & 0x0F) | (emIPVersion); }

    /*=============================================================================
    �� �� ��:GetVersion
    ��    ��:��ȡ�汾��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�汾��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline enumIPVersion GetVersion(void) const
    { return static_cast<enumIPVersion>(m_byVIHL & 0xF0); }

    /*=============================================================================
    �� �� ��:SetIHL
    ��    ��:����Internet Header Length
    ��    ��:u8 byIHL                       [in]    MIN_IPHEADER_LEN
    ע    ��:The length of the internet header in 32 bit words.
             The minimum value for a correct header is 5
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline void SetIHL(u8 byIHL)
    { m_byVIHL = (m_byVIHL & 0xF0) | (byIHL & 0x0F); }

    /*=============================================================================
    �� �� ��:GetIHL
    ��    ��:��ȡInternet Header Length
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Internet Header Length
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline u8 GetIHL(void) const { return (m_byVIHL & 0x0F); }

    /*=============================================================================
    �� �� ��:SetPrecedence
    ��    ��:������������
    ��    ��:enumPrecedence emPrecedence    [in]    Precedence
    ע    ��:Several networks offer service precedence, which somehow treats high
               precedence traffic as more important than other traffic (generally
               by accepting only traffic above a certain precedence at time of
               high load).
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline void SetPrecedence(enumPrecedence emPrecedence)
    { m_byTOS = ( m_byTOS & 0x1F ) | ( emPrecedence); }

    /*=============================================================================
    �� �� ��:SetPrecedence
    ��    ��:��ȡ��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline enumPrecedence GetPrecedence(void) const
    { return static_cast<enumPrecedence>(m_byTOS & ~0x1F); }

    /*=============================================================================
    �� �� ��:SetLowDelay
    ��    ��:������ʱ����
    ��    ��:BOOL32 bLowDelay               [in]    TRUE: ����ʱ; FALSE: ������ʱ
    ע    ��:The use of the Delay, Throughput, and Reliability indications may
               increase the cost (in some sense) of the service.
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline void SetLowDelay(BOOL32 bLowDelay)
    { bLowDelay ? m_byTOS |= 0x10 : m_byTOS &= ~0x10; }

    /*=============================================================================
    �� �� ��:IsLowDelay
    ��    ��:�Ƿ����ʱ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:TRUE: ����ʱ; FALSE: ������ʱ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline BOOL32 IsLowDelay(void) const { return (m_byTOS & 0x10) > 0; }

    /*=============================================================================
    �� �� ��:SetHighThroughput
    ��    ��:���ø�������
    ��    ��:BOOL32 bHighThroughput         [in]    TRUE: ������; FALSE: ��������
    ע    ��:The use of the Delay, Throughput, and Reliability indications may
               increase the cost (in some sense) of the service.
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline void SetHighThroughput(BOOL32 bHighThroughput)
    { bHighThroughput ? m_byTOS |= 0x08 : m_byTOS &= ~0x08; }

    /*=============================================================================
    �� �� ��:IsHighThroughput
    ��    ��:�Ƿ��������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:TRUE: ����ʱ; FALSE: ������ʱ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline BOOL32 IsHighThroughput(void) const { return (m_byTOS & 0x08) > 0; }

    /*=============================================================================
    �� �� ��:SetHighRelibility
    ��    ��:���ø߿ɿ���
    ��    ��:BOOL32 bHighRelibility         [in]    TRUE: �߿ɿ�; FALSE: �����ɿ�
    ע    ��:The use of the Delay, Throughput, and Reliability indications may
               increase the cost (in some sense) of the service.
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline void SetHighRelibility(BOOL32 bHighRelibility)
    { bHighRelibility ? m_byTOS |= 0x04 : m_byTOS &= ~0x04; }

    /*=============================================================================
    �� �� ��:IsHighRelibility
    ��    ��:�Ƿ�߿ɿ���
    ��    ��:��
    ע    ��:��
    �� �� ֵ:TRUE: �߿ɿ���; FALSE: �����ɿ���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/15  4.0     ���    ����
    =============================================================================*/
    inline BOOL32 IsHighRelibility(void) const { return (m_byTOS & 0x04) > 0; }

    /*=============================================================================
    �� �� ��:SetTotalLen
    ��    ��:���ð���
    ��    ��:u16 wTotalLen                  [in]    ����(������)
    ע    ��:Total Length is the length of the datagram, measured in octets,
               including internet header and data. All hosts must be prepared
               to accept datagrams of up to 576 octets(whether they arrive whole
               or in fragments).
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline void SetTotalLen(u16 wTotalLen) { m_wTotalLen = htons( wTotalLen ); }

    /*=============================================================================
    �� �� ��:GetTotalLen
    ��    ��:��ȡ����(������)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:����, ����ͷ������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline u16 GetTotalLen(void) const { return ntohs( m_wTotalLen ); }

    /*=============================================================================
    �� �� ��:SetID
    ��    ��:����Identification
    ��    ��:u16 wID                        [in]    ID(������)
    ע    ��:An identifying value assigned by the sender to aid in assembling the
               fragments of a datagram.
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline void SetID(u16 wID) { m_wID = htons( wID ); }

    /*=============================================================================
    �� �� ��:GetID
    ��    ��:��ȡIdentification(������)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Identification
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline u16 GetID(void) const { return ntohs( m_wID ); }

    /*=============================================================================
    �� �� ��:SetNoFragment
    ��    ��:���ò�����ֿ�
    ��    ��:��
    ע    ��:�����Fragment��Offset
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline void SetNoFragment(void) { m_wFlagOff = htons( 0x4000 ); }

    /*=============================================================================
    �� �� ��:IsNoFragment
    ��    ��:�ж��Ƿ�����ֿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:������ֿ�: TRUE; ����ֿ�: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline BOOL32 IsNoFragment(void) const
    { return ( ntohs( m_wFlagOff ) & 0x4000 ) == 0; }

    /*=============================================================================
    �� �� ��:SetLastFragment
    ��    ��:���ñ���Ϊ���һ���ֿ�
    ��    ��:��
    ע    ��:����������ֿ�, Ȼ�����ñ�����Last Fragment
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline void SetLastFragment(void)
    {
        u16 wFlagOff = ntohs( m_wFlagOff );
        wFlagOff &= ~0x4000;
        wFlagOff &= ~0x2000;
        m_wFlagOff = htons( wFlagOff );
    }

    /*=============================================================================
    �� �� ��:IsLastFragment
    ��    ��:�жϱ����Ƿ�Ϊ���һ���ֿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:����ֿ�, �ұ��������һ��: TRUE; ������ֿ�, �򱾰��������һ��: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline BOOL32 IsLastFragment(void) const
    {
        u16 wFlagOff = ntohs( m_wFlagOff );
        return ((wFlagOff & 0x4000) == 0) && ((wFlagOff & 0x2000) == 0);
    }

    /*=============================================================================
    �� �� ��:SetMoreFragment
    ��    ��:���ñ����������һ���ֿ�
    ��    ��:��
    ע    ��:����������ֿ�, Ȼ�����ñ����������һ��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline void SetMoreFragment(void)
    {
        u16 wFlagOff = ntohs( m_wFlagOff );
        wFlagOff &= ~0x4000;
        wFlagOff |= 0x2000;
        m_wFlagOff = htons( wFlagOff );
    }

    /*=============================================================================
    �� �� ��:IsMoreFragment
    ��    ��:�жϱ����Ƿ������һ���ֿ�
    ��    ��:��
    ע    ��:��
    �� �� ֵ:����ֿ�, �ұ����������һ��: TRUE; ������ֿ�, �򱾰��������һ��: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline BOOL32 IsMoreFragment(void) const
    {
        u16 wFlagOff = ntohs( m_wFlagOff );
        return ((wFlagOff & 0x4000) == 0) && ((wFlagOff & 0x2000) > 0);
    }

    /*=============================================================================
    �� �� ��:SetFragmentOffset
    ��    ��:���ÿ�λ��
    ��    ��:u16 wOffset                    [in]    ��λ��(ֻ�к�13bit��Ч)
    ע    ��:Where in the datagram this fragment belongs.
               The fragment offset is measured in units of 8 octets (64 bits).
               The first fragment has offset zero.
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline void SetFragmentOffset(u16 wOffset)
    {
        u16 wFlagOff = ntohs( m_wFlagOff );
        wFlagOff |= (wOffset & 0x1FFF);
        m_wFlagOff = htons( wFlagOff );
    }

    /*=============================================================================
    �� �� ��:GetFragmentOffset
    ��    ��:��ȡ��λ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��λ��(ֻ�к�13bit��Ч)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline u16 GetFragmentOffset(void) const
    {
        return ( ntohs( m_wFlagOff ) & 0x1FFF );
    }

    /*=============================================================================
    �� �� ��:SetTimeToLive
    ��    ��:��������ʱ��
    ��    ��:u8 byTTL                       [in]    ����ʱ��
    ע    ��:The maximum time the datagram is allowed to remain in the internet system.
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline void SetTimeToLive(u8 byTTL) { m_byTTL = byTTL; }

    /*=============================================================================
    �� �� ��:GetTimeToLive
    ��    ��:��ȡ����ʱ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:����ʱ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/16  4.0     ���    ����
    =============================================================================*/
    inline u8 GetTimeToLive(void) const { return m_byTTL; }

    /*=============================================================================
    �� �� ��:SetProtocol
    ��    ��:����Э������
    ��    ��:u8 byProtocol                  [in]    Э������IPPROTO_TCP/IPPROTO_ICMP��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline void SetProtocol(u8 byProtocol) { m_byProtocol = byProtocol; }

    /*=============================================================================
    �� �� ��:GetProtocol
    ��    ��:��ȡЭ������
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Э������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline u8 GetProtocol(void) const { return m_byProtocol; }

    /*=============================================================================
    �� �� ��:SetCheckSum
    ��    ��:����У����
    ��    ��:u16 wCheckSum                  [in]    У����(����ϵͳ˳��)
    ע    ��:ʹ��MakeCheckSum����У����
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline void SetCheckSum(u16 wCheckSum) { m_wCheckSum = wCheckSum; }

    /*=============================================================================
    �� �� ��:GetCheckSum
    ��    ��:��ȡУ����
    ��    ��:��
    ע    ��:ʹ��MakeCheckSum����У����
    �� �� ֵ:У����(����ϵͳ˳��)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline u16 GetCheckSum(void) const { return m_wCheckSum; }

    /*=============================================================================
    �� �� ��:SetSrcIPAddr
    ��    ��:����ԴIP��ַ
    ��    ��:u32 dwSrcIPAddr            [in]    ԴIP��ַ(������)
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline void SetSrcIPAddr(u32 dwSrcIPAddr)
    { m_dwSrcIPAddr = htonl( dwSrcIPAddr ); }

    /*=============================================================================
    �� �� ��:GetSrcIPAddr
    ��    ��:��ȡԴIP��ַ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:ԴIP��ַ(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline u32 GetSrcIPAddr(void) const { return ntohl( m_dwSrcIPAddr ); }

    /*=============================================================================
    �� �� ��:SetDstIPAddr
    ��    ��:����Ŀ��IP��ַ
    ��    ��:u32 dwSrcIPAddr            [in]    Ŀ��IP��ַ
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline void SetDstIPAddr(u32 dwDstIPAddr)
    { m_dwDstIPAddr = htonl( dwDstIPAddr ); }

    /*=============================================================================
    �� �� ��:GetDstIPAddr
    ��    ��:��ȡĿ��IP��ַ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Ŀ��IP��ַ(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/25  4.0     ���    ����
    =============================================================================*/
    inline u32 GetDstIPAddr(void) const { return ntohl( m_dwDstIPAddr ); }

private:
    u8      m_byVIHL;       // Version and IHL

//  Bits 0-2:  Precedence.
//      Bit    3:  0 = Normal Delay,      1 = Low Delay.
//      Bits   4:  0 = Normal Throughput, 1 = High Throughput.
//      Bits   5:  0 = Normal Relibility, 1 = High Relibility.
//      Bit  6-7:  Reserved for Future Use.
//
//         0     1     2     3     4     5     6     7
//      +-----+-----+-----+-----+-----+-----+-----+-----+
//      |                 |     |     |     |     |     |
//      |   PRECEDENCE    |  D  |  T  |  R  |  0  |  0  |
//      |                 |     |     |     |     |     |
//      +-----+-----+-----+-----+-----+-----+-----+-----+
//
//        Precedence
//
//          111 - Network Control
//          110 - Internetwork Control
//          101 - CRITIC/ECP
//          100 - Flash Override
//          011 - Flash
//          010 - Immediate
//          001 - Priority
//          000 - Routine
    u8      m_byTOS;        // Type Of Service
    u16     m_wTotalLen;    // Total Length(������)
    u16     m_wID;          // Identification

//  Flags: 3 bits
//      Various Control Flags.
//      Bit 0: reserved, must be zero
//      Bit 1: (DF) 0 = May Fragment, 1 = Don��t Fragment.
//      Bit 2: (MF) 0 = Last Fragment, 1 = More Fragments.
//
//        0   1   2
//      +---+---+---+
//      |   | D | M |
//      | 0 | F | F |
//      +---+---+---+
//Fragment Offset: 13 bits
//      This field indicates where in the datagram this fragment belongs.
//      The fragment offset is measured in units of 8 octets (64 bits). The
//      first fragment has offset zero.
    u16     m_wFlagOff;     // Flags and Fragment Offset

    u8      m_byTTL;        // Time To Live
    u8      m_byProtocol;   // Protocol(IPPROTO_IP/IPPROTO_ICMP/IPPROTO_TCP...)
    u16     m_wCheckSum;    // Checksum(����ϵͳ˳��)
    u32     m_dwSrcIPAddr;  // Internet Address - Source(������)
    u32     m_dwDstIPAddr;  // Internet Address - Destination(������)
} IIPHDR, *PIIPHDR;

//ICMPЭ���µ�IPͷ�ṹ
typedef struct tagIPHDRINICMP
{
public:
    /*=============================================================================
    �� �� ��:tagIPHDRINICMP
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    tagIPHDRINICMP() : m_byType(0), m_byCode(0), m_wIcmpCheckSum(0)
    {
        m_tIPHdr.SetVersion( emIPv4 );
        m_tIPHdr.SetTotalLen( MIN_IPHEADER_LEN );
        m_tIPHdr.SetProtocol( IPPROTO_ICMP );
    }

    /*=============================================================================
    �� �� ��:SetType
    ��    ��:��������
    ��    ��:enumIcmpType emIcmpType    [in]    ICMP��Ϣͷ����
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    inline void SetType(enumIcmpType emIcmpType) { m_byType = emIcmpType; }

    /*=============================================================================
    �� �� ��:GetType
    ��    ��:��ȡ����
    ��    ��:�� 
    ע    ��:��
    �� �� ֵ:ICMP��Ϣͷ����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    inline enumIcmpType GetType(void) const
    { return static_cast<enumIcmpType>(m_byType); }

    /*=============================================================================
    �� �� ��:SetCode
    ��    ��:����ԭ��
    ��    ��:u8 byCode                  [in]    ICMP��Ϣ���Ͳ���ԭ��
    ע    ��:0/enumIcmpCodeUnreachable/enumIcmpCodeTime/enumIcmpCodeRedirect
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    inline void SetCode(u8 byCode) { m_byCode = byCode; }

    /*=============================================================================
    �� �� ��:GetCode
    ��    ��:��ȡԭ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:0/enumIcmpCodeUnreachable/enumIcmpCodeTime/enumIcmpCodeRedirect
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    inline u8 GetCode(void) const { return m_byCode; }

    /*=============================================================================
    �� �� ��:SetIcmpCheckSum
    ��    ��:����ICMPУ����
    ��    ��:u16 wCheckSum              [in]    У����(����ϵͳ˳��)
    ע    ��:����SetCheckSum()
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    inline void SetIcmpCheckSum(u16 wCheckSum) { m_wIcmpCheckSum = wCheckSum; }

    /*=============================================================================
    �� �� ��:GetIcmpCheckSum
    ��    ��:��ȡICMPУ����
    ��    ��:��
    ע    ��:����GetCheckSum()
    �� �� ֵ:У����(����ϵͳ˳��)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    inline u16 GetIcmpCheckSum(void) const { return m_wIcmpCheckSum; }

public:
    IIPHDR  m_tIPHdr;       // IPͷ
private:
    u8      m_byType;       // Type
    u8      m_byCode;       // Code
    u16     m_wIcmpCheckSum;// CheckSum(����ϵͳ˳��)
} IIPHDRINICMP, *PIIPHDRINICMP;

//IMCP��Ϣ�ṹ
typedef struct tagICMPMsg
{
    /*=============================================================================
    �� �� ��:tagICMPMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    tagICMPMsg()
    {
        memset( m_abyBuf, 0, sizeof (m_abyBuf) );
    }

    IIPHDRINICMP    m_tIPHdr;       // IPͷ + ICMP����ͷ
    u8              m_abyBuf[MAX_ICMP_SENDMSG_LEN + sizeof (u16) * 2];
} IICMPMsg, *PIICMPMsg;

//ICMP��Ϣ�޷�����ṹ
//  If, according to the information in the gateway��s routing 
//tables, the network specified in the internet destination field 
//of a datagram is unreachable, e.g., the distance to the network 
//is infinity, the gateway may send a destination unreachable 
//message to the internet source host of the datagram. In addition, 
//in some networks, the gateway may be able to determine if the 
//internet destination host is unreachable. Gateways in these 
//networks may send destination unreachable messages to the source 
//host when the destination host is unreachable.
//  If, in the destination host, the IP module cannot deliver the
//datagram because the indicated protocol module or process port is
//not active, the destination host may send a destination
//unreachable message to the source host.
//  Another case is when a datagram must be fragmented to be 
//forwarded by a gateway yet the Don��t Fragment flag is on. In this 
//case the gateway must discard the datagram and may return a 
//destination unreachable message.
//  Codes 0, 1, 4, and 5 may be received from a gateway. Codes 2 and
//3 may be received from a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |     Code      |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|                             unused                            |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Internet Header + 64 bits of Original Data Datagram      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpUnreachMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpUnreachMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    tagIcmpUnreachMsg() : m_dwReserved(0), m_dwIntHeader(0)
    {
        m_tIPHdr.SetType( emDstUnreachable );
        memset( m_abyDataGram, 0, sizeof (m_abyDataGram) );
    }

    /*=============================================================================
    �� �� ��:GetCode
    ��    ��:��ȡԭ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:enumIcmpCodeUnreachable
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/29  4.0     ���    ����
    =============================================================================*/
    inline enumIcmpCodeUnreachable GetCode(void) const
    { return static_cast<enumIcmpCodeUnreachable>(m_tIPHdr.GetCode()); }

    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
    u32             m_dwReserved;
    u32             m_dwIntHeader;      // Internet Header
    u8              m_abyDataGram[8];   // 64 bits of Original Data Datagram
} IIcmpUnreachMsg, *PIIcmpUnreachMsg;

//ICMP��ʱ��Ϣ�ṹ
//  If the gateway processing a datagram finds the time to live 
//field is zero it must discard the datagram. The gateway may also 
//notify the source host via the time exceeded message.
//  If a host reassembling a fragmented datagram cannot complete 
//the reassembly due to missing fragments within its time limit it 
//discards the datagram, and it may send a time exceeded message.
//  If fragment zero is not available then no time exceeded need be 
//sent at all.
//  Code 0 may be received from a gateway. Code 1 may be received 
//from a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Type     |     Code      |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|                             unused                            |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Internet Header + 64 bits of Original Data Datagram       |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpTimeMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpTimeMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpTimeMsg() : m_dwReserved(0), m_dwIntHeader(0)
    {
        m_tIPHdr.SetType( emTimeExceeded );
        memset( m_abyDataGram, 0, sizeof (m_abyDataGram) );
    }

    /*=============================================================================
    �� �� ��:GetCode
    ��    ��:��ȡԭ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:enumIcmpCodeTime
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline enumIcmpCodeTime GetCode(void) const
    { return static_cast<enumIcmpCodeTime>(m_tIPHdr.GetCode()); }

    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
    u32             m_dwReserved;
    u32             m_dwIntHeader;      // Internet Header
    u8              m_abyDataGram[8];   // 64 bits of Original Data Datagram
} IIcmpTimeMsg, *PIIcmpTimeMsg;

//ICMP����������Ϣ�ṹ
//  If the gateway or host processing a datagram finds a problem 
//with the header parameters such that it cannot complete processing 
//the datagram it must discard the datagram. One potential source of 
//such a problem is with incorrect arguments in an option. The 
//gateway or host may also notify the source host via the parameter 
//problem message. This message is only sent if the error caused 
//the datagram to be discarded.
//  The pointer identifies the octet of the original datagram's 
//header where the error was detected (it may be in the middle of an
//option). For example, 1 indicates something is wrong with the 
//Type of Service, and (if there are options present) 20 indicates 
//something is wrong with the type code of the first option.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |     Code      |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|    Pointer    |                   unused                      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Internet Header + 64 bits of Original Data Datagram      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpParamMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpParamMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpParamMsg() : m_byPtr(0), m_dwIntHeader(0)
    {
        m_tIPHdr.SetType( emParamError );
        memset( m_abyReserved, 0, sizeof (m_abyReserved) );
        memset( m_abyDataGram, 0, sizeof (m_abyDataGram) );
    }

    /*=============================================================================
    �� �� ��:GetErrPtr
    ��    ��:��ȡ����ָ��λ��
    ��    ��:��
    ע    ��:����: 1: Type of Service; 20: Type; 21: Code
    �� �� ֵ:ָ��λ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline s32 GetErrPtr(void) const
    { return static_cast<s32>(m_byPtr); }

    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
    u8              m_byPtr;            // ����ָ���ַ
    u8              m_abyReserved[3];
    u32             m_dwIntHeader;      // Internet Header
    u8              m_abyDataGram[8];   // 64 bits of Original Data Datagram
} IIcmpParamMsg, *PIIcmpParamMsg;

//ICMPԴ��ֹͣ��Ϣ�ṹ
//  A gateway may discard internet datagrams if it does not have 
//the buffer space needed to queue the datagrams for output to the 
//next network on the route to the destination network. If a gateway 
//discards a datagram, it may send a source quench message to the 
//internet source host of the datagram. A destination host may also 
//send a source quench message if datagrams arrive too fast to be 
//processed. The source quench message is a request to the host to 
//cut back the rate at which it is sending traffic to the internet 
//destination. The gateway may send a source quench message for 
//every message that it discards. On receipt of a source quench 
//message, the source host should cut back the rate at which it is 
//sending traffic to the specified destination until it no longer 
//receives source quench messages from the gateway. The source host 
//can then gradually increase the rate at which it sends traffic to 
//the destination until it again receives source quench messages.
//  The gateway or host may send the source quench message when it 
//approaches its capacity limit rather than waiting until the 
//capacity is exceeded. This means that the data datagram which 
//triggered the source quench message may be delivered.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |     Code      |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|                             unused                            |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Internet Header + 64 bits of Original Data Datagram      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpQuenchMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpQuenchMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpQuenchMsg() : m_dwReserved(0), m_dwIntHeader(0)
    {
        m_tIPHdr.SetType( emSourceQuench );
        memset( m_abyDataGram, 0, sizeof (m_abyDataGram) );
    }

    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
    u32             m_dwReserved;
    u32             m_dwIntHeader;      // Internet Header
    u8              m_abyDataGram[8];   // 64 bits of Original Data Datagram
} IIcmpQuenchMsg, *PIIcmpQuenchMsg;

//ICMP�ض�����Ϣ�ṹ
//  The gateway sends a redirect message to a host in the following 
//situation. A gateway, G1, receives an internet datagram from a 
//host on a network to which the gateway is attached. The gateway, 
//G1, checks its routing table and obtains the address of the next 
//gateway, G2, on the route to the datagram��s internet destination 
//network, X. If G2 and the host identified by the internet source 
//address of the datagram are on the same network, a redirect 
//message is sent to the host. The redirect message advises the 
//host to send its traffic for network X directly to gateway G2 as 
//this is a shorter path to the destination. The gateway forwards 
//the original datagram��s data to its internet destination.
//  For datagrams with the IP source route options and the gateway 
//address in the destination address field, a redirect message is 
//not sent even if there is a better route to the ultimate 
//destination than the next address in the source route.
//  Codes 0, 1, 2, and 3 may be received from a gateway.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |     Code      |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|                 Gateway Internet Address                      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Internet Header + 64 bits of Original Data Datagram      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpRedirectMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpRedirectMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpRedirectMsg() : m_dwGatewayAddr(0), m_dwIntHeader(0)
    {
        m_tIPHdr.SetType( emRedirect );
        memset( m_abyDataGram, 0, sizeof (m_abyDataGram) );
    }

    /*=============================================================================
    �� �� ��:GetCode
    ��    ��:��ȡԭ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:enumIcmpCodeRedirect
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline enumIcmpCodeRedirect GetCode(void) const
    { return static_cast<enumIcmpCodeRedirect>(m_tIPHdr.GetCode()); }

    /*=============================================================================
    �� �� ��:GetGatewayAddr
    ��    ��:��ȡ���ص�ַ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:���ص�ַ(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u32 GetGatewayAddr(void) const
    { return ntohl(m_dwGatewayAddr); }

public:
    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
private:
    u32             m_dwGatewayAddr;    // ���ص�ַ(������)
public:
    u32             m_dwIntHeader;      // Internet Header
    u8              m_abyDataGram[8];   // 64 bits of Original Data Datagram
} IIcmpRedirectMsg, *PIIcmpRedirectMsg;

//ICMP��Ӧ��Ϣ�ṹ
//  The data received in the echo message must be returned in the 
//echo reply message.
//  The identifier and sequence number may be used by the echo 
//sender to aid in matching the replies with the echo requests.
//For example, the identifier might be used like a port in TCP or 
//UDP to identify a session, and the sequence number might be 
//incremented on each echo request sent. The echoer returns these 
//same values in the echo reply.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |     Code      |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|           Identifier          |        Sequence Number        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Data ...
//+-+-+-+-+-
typedef struct tagIcmpEchoMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpEchoMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpEchoMsg() : m_wID(0), m_wSerialNo(0)
    {
        m_tIPHdr.SetType( emEcho );
        memset( m_abyData, 0, sizeof (m_abyData) );
    }

    /*=============================================================================
    �� �� ��:GetID
    ��    ��:��ȡIdentifier
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Identifier(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetID(void) const { return ntohs(m_wID); }

    /*=============================================================================
    �� �� ��:SetID
    ��    ��:����Identifier
    ��    ��:u16 wID                        [in]    Identifier(������)
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    inline void SetID(u16 wID) { m_wID = htons(wID); }

    /*=============================================================================
    �� �� ��:GetSerialNo
    ��    ��:��ȡSequence Number
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Sequence Number(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetSerialNo(void) const { return ntohs(m_wSerialNo); }

    /*=============================================================================
    �� �� ��:SetSerialNo
    ��    ��:����Sequence Number
    ��    ��:u16 wSN                        [in]    Sequence Number(������)
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    inline u16 SetSerialNo(u16 wSN) { m_wSerialNo = htons(wSN); }

public:
    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
private:
    u16             m_wID;              // Identifier(������)
    u16             m_wSerialNo;        // Sequence Number(������)
public:
    u8              m_abyData[MAX_ICMP_SENDMSG_LEN];
} IIcmpEchoMsg, *PIIcmpEchoMsg;

//ICMP��Ӧ��Ӧ��Ϣ�ṹ
//  The data received in the echo message must be returned in the 
//echo reply message.
//  The identifier and sequence number may be used by the echo 
//sender to aid in matching the replies with the echo requests.
//For example, the identifier might be used like a port in TCP or 
//UDP to identify a session, and the sequence number might be 
//incremented on each echo request sent. The echoer returns these 
//same values in the echo reply.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |     Code      |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|           Identifier          |        Sequence Number        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Data ...
//+-+-+-+-+-
typedef struct tagIcmpEchoReplyMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpEchoMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpEchoReplyMsg() : m_wID(0), m_wSerialNo(0)
    {
        m_tIPHdr.SetType( emEchoReply );
        memset( m_abyData, 0, sizeof (m_abyData) );
    }

    /*=============================================================================
    �� �� ��:GetID
    ��    ��:��ȡIdentifier
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Identifier(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetID(void) const { return ntohs(m_wID); }

    /*=============================================================================
    �� �� ��:GetSerialNo
    ��    ��:��ȡSequence Number
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Sequence Number(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetSerialNo(void) const { return ntohs(m_wSerialNo); }

public:
    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
private:
    u16             m_wID;              // Identifier(������)
    u16             m_wSerialNo;        // Sequence Number(������)
public:
    u8              m_abyData[MAX_ICMP_SENDMSG_LEN];
} IIcmpEchoReplyMsg, *PIIcmpEchoReplyMsg;

//ICMPʱ�����Ϣ�ṹ
//  The data received (a timestamp) in the message is returned in 
//the reply together with an additional timestamp. The timestamp 
//is 32 bits of milliseconds since midnight UT.
//  The Originate Timestamp is the time the sender last touched the 
//message before sending it, the Receive Timestamp is the time the 
//echoer first touched it on receipt, and the Transmit Timestamp is 
//the time the echoer last touched the message on sending it.
//  If the time is not available in milliseconds or cannot be 
//provided with respect to midnight UT then any time can be inserted 
//in a timestamp provided the high order bit of the timestamp is also 
//set to indicate this non-standard value.
//  The identifier and sequence number may be used by the echo sender 
//to aid in matching the replies with the requests. For example, the 
//identifier might be used like a port in TCP or UDP to identify a 
//a session, and the sequence number might be incremented on each 
//request sent. The destination returns these same values in the reply.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Type     |      Code     |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|           Identifier          |        Sequence Number        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Originate Timestamp                                      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Receive Timestamp                                        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Transmit Timestamp                                       |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpTimestampMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpTimestampMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpTimestampMsg() : m_wID(0), m_wSerialNo(0), m_dwOrigStamp(0),
                            m_dwRecvStamp(0), m_dwTranStamp(0)
    {
        m_tIPHdr.SetType( emTimeStamp );
    }

    /*=============================================================================
    �� �� ��:GetID
    ��    ��:��ȡIdentifier
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Identifier(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetID(void) const { return ntohs(m_wID); }

    /*=============================================================================
    �� �� ��:GetSerialNo
    ��    ��:��ȡSequence Number
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Sequence Number(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetSerialNo(void) const { return ntohs(m_wSerialNo); }

    /*=============================================================================
    �� �� ��:GetOrigStamp
    ��    ��:��ȡOriginate Timestamp(����)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Originate Timestamp(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u32 GetOrigStamp(void) const { return ntohl(m_dwOrigStamp); }

    /*=============================================================================
    �� �� ��:GetRecvStamp
    ��    ��:��ȡTransmit Timestamp(����)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Transmit Timestamp(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u32 GetRecvStamp(void) const { return ntohl(m_dwRecvStamp); }

    /*=============================================================================
    �� �� ��:GetTranStamp
    ��    ��:��ȡTransmit Timestamp(����)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Transmit Timestamp(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u32 GetTranStamp(void) const { return ntohl(m_dwTranStamp); }

public:
    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
private:
    u16             m_wID;              // Identifier(������)
    u16             m_wSerialNo;        // Sequence Number(������)
    u32             m_dwOrigStamp;      // Originate Timestamp(����)(������)
    u32             m_dwRecvStamp;      // Receive Timestamp(����)(������)
    u32             m_dwTranStamp;      // Transmit Timestamp(����)(������)
} IIcmpTimestampMsg, *PIIcmpTimestampMsg;

//ICMPʱ�����Ӧ��Ϣ�ṹ
//  The data received (a timestamp) in the message is returned in 
//the reply together with an additional timestamp. The timestamp 
//is 32 bits of milliseconds since midnight UT.
//  The Originate Timestamp is the time the sender last touched the 
//message before sending it, the Receive Timestamp is the time the 
//echoer first touched it on receipt, and the Transmit Timestamp is 
//the time the echoer last touched the message on sending it.
//  If the time is not available in milliseconds or cannot be 
//provided with respect to midnight UT then any time can be inserted 
//in a timestamp provided the high order bit of the timestamp is also 
//set to indicate this non-standard value.
//  The identifier and sequence number may be used by the echo sender 
//to aid in matching the replies with the requests. For example, the 
//identifier might be used like a port in TCP or UDP to identify a 
//a session, and the sequence number might be incremented on each 
//request sent. The destination returns these same values in the reply.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Type     |      Code     |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|           Identifier          |        Sequence Number        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Originate Timestamp                                      |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Receive Timestamp                                        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|      Transmit Timestamp                                       |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpTimestampReplyMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpTimestampReplyMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpTimestampReplyMsg() : m_wID(0), m_wSerialNo(0), m_dwOrigStamp(0),
                                 m_dwRecvStamp(0), m_dwTranStamp(0)
    {
        m_tIPHdr.SetType( emTimeStampReply );
    }

    /*=============================================================================
    �� �� ��:GetID
    ��    ��:��ȡIdentifier
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Identifier(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetID(void) const { return ntohs(m_wID); }

    /*=============================================================================
    �� �� ��:GetSerialNo
    ��    ��:��ȡSequence Number
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Sequence Number(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetSerialNo(void) const { return ntohs(m_wSerialNo); }

    /*=============================================================================
    �� �� ��:GetOrigStamp
    ��    ��:��ȡOriginate Timestamp(����)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Originate Timestamp(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u32 GetOrigStamp(void) const { return ntohl(m_dwOrigStamp); }

    /*=============================================================================
    �� �� ��:GetRecvStamp
    ��    ��:��ȡTransmit Timestamp(����)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Transmit Timestamp(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u32 GetRecvStamp(void) const { return ntohl(m_dwRecvStamp); }

    /*=============================================================================
    �� �� ��:GetTranStamp
    ��    ��:��ȡTransmit Timestamp(����)
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Transmit Timestamp(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u32 GetTranStamp(void) const { return ntohl(m_dwTranStamp); }

public:
    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
private:
    u16             m_wID;              // Identifier(������)
    u16             m_wSerialNo;        // Sequence Number(������)
    u32             m_dwOrigStamp;      // Originate Timestamp(����)(������)
    u32             m_dwRecvStamp;      // Receive Timestamp(����)(������)
    u32             m_dwTranStamp;      // Transmit Timestamp(����)(������)
} IIcmpTimestampReplyMsg, *PIIcmpTimestampReplyMsg;

//ICMP��Ϣ����ṹ
//  This message may be sent with the source network in the IP 
//header source and destination address fields zero (which means 
//"this" network). The replying IP module should send the reply 
//with the addresses fully specified. This message is a way for 
//a host to find out the number of the network it is on.
//  The identifier and sequence number may be used by the echo 
//sender to aid in matching the replies with the requests. For 
//example, the identifier might be used like a port in TCP or UDP 
//to identify a session, and the sequence number might be 
//incremented on each request sent. The destination returns these 
//same values in the reply.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |      Code     |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|          Identifier           |        Sequence Number        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpInfoReqMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpInfoReqMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpInfoReqMsg() : m_wID(0), m_wSerialNo(0)
    {
        m_tIPHdr.SetType( emInfoReq );
    }

    /*=============================================================================
    �� �� ��:GetID
    ��    ��:��ȡIdentifier
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Identifier(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetID(void) const { return ntohs(m_wID); }

    /*=============================================================================
    �� �� ��:GetSerialNo
    ��    ��:��ȡSequence Number
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Sequence Number(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetSerialNo(void) const { return ntohs(m_wSerialNo); }

public:
    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
private:
    u16             m_wID;              // Identifier(������)
    u16             m_wSerialNo;        // Sequence Number(������)
} IIcmpInfoReqMsg, *PIIcmpInfoReqMsg;

//ICMP��Ϣ��Ӧ�ṹ
//  This message may be sent with the source network in the IP 
//header source and destination address fields zero (which means 
//"this" network). The replying IP module should send the reply 
//with the addresses fully specified. This message is a way for 
//a host to find out the number of the network it is on.
//  The identifier and sequence number may be used by the echo 
//sender to aid in matching the replies with the requests. For 
//example, the identifier might be used like a port in TCP or UDP 
//to identify a session, and the sequence number might be 
//incremented on each request sent. The destination returns these 
//same values in the reply.
//  Code 0 may be received from a gateway or a host.
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|     Type      |      Code     |          Checksum             |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//|          Identifier           |        Sequence Number        |
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
typedef struct tagIcmpInfoReplyMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpInfoReplyMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    tagIcmpInfoReplyMsg() : m_wID(0), m_wSerialNo(0)
    {
        m_tIPHdr.SetType( emInfoReply );
    }

    /*=============================================================================
    �� �� ��:GetID
    ��    ��:��ȡIdentifier
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Identifier(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetID(void) const { return ntohs(m_wID); }

    /*=============================================================================
    �� �� ��:GetSerialNo
    ��    ��:��ȡSequence Number
    ��    ��:��
    ע    ��:��
    �� �� ֵ:Sequence Number(������)
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/05/30  4.0     ���    ����
    =============================================================================*/
    inline u16 GetSerialNo(void) const { return ntohs(m_wSerialNo); }

public:
    IIPHDRINICMP    m_tIPHdr;           // IPͷ + ICMP����ͷ
private:
    u16             m_wID;              // Identifier(������)
    u16             m_wSerialNo;        // Sequence Number(������)
} IIcmpInfoReplyMsg, *PIIcmpInfoReplyMsg;


//ICMP�Զ��巢����Ϣ�ṹ����
typedef struct tagIcmpSendMsg
{
    /*=============================================================================
    �� �� ��:tagIcmpSendMsg
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    tagIcmpSendMsg() : m_byType(emEcho), m_byCode(0), m_wCheckSum(0),
                       m_wID(0), m_wSerialNo(0), m_dwTimeStamp(0)
    {
        memset( m_abyBuf, 0, sizeof (m_abyBuf) );
    }

    /*=============================================================================
    �� �� ��:SetID
    ��    ��:����Identifier
    ��    ��:u16 wID                [in]    Identifier(������)
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    inline void SetID(u16 wID) { m_wID = htons(wID); }

    /*=============================================================================
    �� �� ��:SetSerialNo
    ��    ��:����Sequence Number
    ��    ��:u16 wSN                [in]    Sequence Number(������)
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    inline void SetSerialNo(u16 wSN) { m_wSerialNo = htons(wSN); }

    /*=============================================================================
    �� �� ��:SetCheckSum
    ��    ��:����У����
    ��    ��:u16 wCheckSum          [in]    У����(����ϵͳ˳��)
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    inline void SetCheckSum(u16 wCheckSum) { m_wCheckSum = wCheckSum; }

    /*=============================================================================
    �� �� ��:SetTimeStamp
    ��    ��:����ʱ���
    ��    ��:u32 dwTimeStamp        [in]    ʱ���(������)
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    inline void SetTimeStamp(u32 dwTimeStamp) { m_dwTimeStamp = htonl(dwTimeStamp); }

private:
    u8              m_byType;       //��Ϣ����
    u8              m_byCode;       //0
    u16             m_wCheckSum;    //У����(����ϵͳ˳��)
    u16             m_wID;          //Identifier(������)
    u16             m_wSerialNo;    //Sequence Number(������)
    u32             m_dwTimeStamp;  //ʱ���, �Ǳ�׼Э���ֶ�
public:
    u8              m_abyBuf[MAX_ICMP_SENDMSG_LEN];
} IIcmpSendMsg, *PIIcmpSendMsg;

/*=============================================================================
�� �� ��:MakeCheckSum
��    ��:����У����
��    ��:u8 *pbyStruct              [in]    �ڴ�ṹ
         s32 nStructLen             [in]    �ṹ����
ע    ��:��
�� �� ֵ:У����(����ϵͳ˳��)
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/05/30  4.0     ���    ����
=============================================================================*/
inline u16 MakeCheckSum(u8 *pbyStruct, s32 nStructLen)
{
    register u32 dwSum = 0;
    u16 wCheckSum = 0;
    //  16bit�ۼ�
    for ( s32 nIndex = 0; nIndex < nStructLen; nIndex += 2 )
    {
        dwSum += static_cast<u32>(*reinterpret_cast<u16*>(pbyStruct + nIndex));
    }
    //  ���λ��Ϊ����, ��Ҫ�ۼ����һλ
    if ( ( nStructLen % 2 ) > 0 )
    {
        dwSum += static_cast<u32>(pbyStruct[nStructLen - 1]);
    }

    dwSum = (dwSum >> 16) + (dwSum & 0xFFFF);
    dwSum += (dwSum >> 16);
    wCheckSum = static_cast<u16>(~dwSum);
    return wCheckSum;
}

#endif  //  __ICMPSTRUCT_H__