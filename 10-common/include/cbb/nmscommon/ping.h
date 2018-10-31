/*=============================================================================
ģ   ��   ��: ��
��   ��   ��: Ping.h
�� ��  �� ��: Ping.cpp
�ļ�ʵ�ֹ���: ping����
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2006/05/31  4.0     ���        ����
=============================================================================*/

#ifndef __PING_H__
#define __PING_H__

#ifdef WIN32
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#endif  //  WIN32

//Ping��������
enum enumPingRt
{
    emPingRtNoError         = (u8)0,    //�ɹ�
    emPingRtUnreachable     = (u8)1,    //�Զ˲��ɼ�
    emPingRtTimeOut         = (u8)2,    //��ʱ
    emPingRtEnd             = (u8)3     //ȫ�����Խ���
};

//Ping�������ֵ
typedef struct tagPingRst
{
    tagPingRst() : m_bEnd(FALSE), m_nTimeCount(0), m_nTotalCount(0),
                   m_nSucCount(0), m_nEchoTime(0), m_nMinEchoTime(0),
                   m_nMaxEchoTime(0), m_nAvrEchoTime(0), m_byPingRt(0),
				   m_byTTL(0),m_nJitter(0)
    {
    }

    BOOL32  m_bEnd;     //TRUE: One Test End; FALSE: Test Begin
    s32     m_nTimeCount;//���β��Դ���
    s32     m_nTotalCount;//�ܹ����Դ���, m_bEndΪTRUE��m_byPingRtΪemPingRtEnd��Ч
    s32     m_nSucCount;//�ɹ�����, m_bEndΪTRUE��m_byPingRtΪemPingRtEnd��Ч
    s32     m_nEchoTime;//������Ӧʱ��, m_bEndΪTRUE��m_byPingRtΪemPingRtNoError��Ч
    s32     m_nMinEchoTime;//�����Ӧʱ��, m_bEndΪTRUE��m_byPingRtΪemPingRtEnd��Ч
    s32     m_nMaxEchoTime;//���Ӧʱ��, m_bEndΪTRUE��m_byPingRtΪemPingRtEnd��Ч
    s32     m_nAvrEchoTime;//ƽ����Ӧʱ��, m_bEndΪTRUE��m_byPingRtΪemPingRtEnd��Ч
	s32     m_nJitter;     //����,m_bEndΪTRUE��m_byPingRtΪemPingRtEnd��Ч
    u8      m_byPingRt; //enumPingRt, m_bEndΪTRUE��Ч
    u8      m_byTTL;    //����ʱ��, m_bEndΪTRUE��m_byPingRtΪemPingRtNoError��Ч
} TPingRst, *PTPingRst;

/*=============================================================================
�� �� ��:PFNPingResult
��    ��:�ص�����
��    ��:void *pcbData                      [in]    �ص�����
         const TPingRst &tPingRst           [in]    ����ֵ
ע    ��:��
�� �� ֵ:��������: TRUE; ֹͣping����: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/06/02  4.0     ���    ����
=============================================================================*/
typedef BOOL32 (*PFNPingResult)(void *pcbData, const TPingRst &tPingRst);

class CPing
{
public:
    /*=============================================================================
    �� �� ��:CPing
    ��    ��:���캯��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/02  4.0     ���    ����
    =============================================================================*/
    CPing();

    virtual ~CPing();

public:
    /*=============================================================================
    �� �� ��:SetParam
    ��    ��:���ò���
    ��    ��:u32 dwHostIP                   [in]    �Զ�IP��ַ(������)
             s32 nTimes                     [in]    ���Դ���
             s32 nPackSize                  [in]    ���԰���
             PFNPingResult pfnRst           [in]    �ص�����
             void *pcbData                  [in]    �ص�����
    ע    ��:��
    �� �� ֵ:���������
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    BOOL32 SetParam(u32 dwHostIP, s32 nTimes, s32 nPackSize,
                    PFNPingResult pfnRst, void *pcbData);

    /*=============================================================================
    �� �� ��:Start
    ��    ��:��ʼ����
    ��    ��:��
    ע    ��:��
    �� �� ֵ:�ɹ�: TRUE; ʧ��: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    BOOL32 Start(void);

    /*=============================================================================
    �� �� ��:GetErrStr
    ��    ��:��ȡ��������
    ��    ��:LPCSTR lptrLan                 [in]    "english"/"chinese"
    ע    ��:��
    �� �� ֵ:���������ַ���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    LPCSTR GetErrStr(LPCTSTR lptrLan);

private:
    /*=============================================================================
    �� �� ��:CheckParam
    ��    ��:������
    ��    ��:s32 nTimes                     [in]    ���Դ���
             s32 nPackSize                  [in]    ���԰���
             PFNPingResult pfnRst           [in]    �ص�����
    ע    ��:��
    �� �� ֵ:�����Ϸ�: TRUE; �����Ƿ�: FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/06/05  4.0     ���    ����
    =============================================================================*/
    BOOL32 CheckParam(s32 nTimes, s32 nPackSize, PFNPingResult pfnRst);

private:
    //  �ⲿ���ò���
    u32             m_dwHostIP; //�Զ�IP��ַ, ������
    s32             m_nTimes;   //���Դ���
    s32             m_nPackSize;//���Ͱ���
//    u8              m_byTimeout;//��ʱʱ��
    PFNPingResult   m_pfnResult;//�ص�����
    void            *m_pcbData; //�ص�����

    //  �ڲ��������
    u8              m_byErrCode;     //������
    s8              m_aszErrStr[1024];
};

#endif  //  __PING_H__