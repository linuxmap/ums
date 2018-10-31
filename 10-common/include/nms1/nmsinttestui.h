/*=============================================================================
ģ   ��   ��: ���ܷ��������������
��   ��   ��: nmsinttestui.h
�� ��  �� ��: nmsinttestui.cpp
�ļ�ʵ�ֹ���: ���������
��        ��: ���
��        ��: V4.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2005/07/26  4.0     ���        ����
=============================================================================*/

#ifndef _NMSINTTESTUI_20050726_H_
#define _NMSINTTESTUI_20050726_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiUnit.h"
#include "nmsmacro.h"
#include "nmsuiconst.h"

//  nms���ò������������Ϊ0����
typedef struct tagNmsGuiCfg
{
    tagNmsGuiCfg()
    {
        ZeroMemory(this, sizeof (tagNmsGuiCfg));
    }

    TCHAR   m_aszServerIpAddr[16];          //  nms IP��ַ
    u16     m_wTrapPort;                    //  nms trap�˿�
    u16     m_wCmSyncPeriod;                //  ������ѯ���
    u16     m_wFmSyncPeriod;                //  �澯��ѯ���
    u8      m_wSnmpTimeout;                 //  snmp��ʱʱ��
    TCHAR   m_aszDBIpAddr[16];              //  ���ݿ������IP��ַ
    TCHAR   m_aszDBUser[USER_LEN];          //  ���ݿ��û���
    TCHAR   m_aszDBPwd[PWD_LEN];            //  ���ݿ�����
    TCHAR   m_aszFTPRemoteUser[USER_LEN];   //  FTPԶ���û���
    TCHAR   m_aszFTPRemotePwd[PWD_LEN];     //  FTPԶ������
    TCHAR   m_aszFTPLocalUser[USER_LEN];    //  FTP�����û���
    TCHAR   m_aszFTPLocalPwd[PWD_LEN];      //  FTP��������
    TCHAR   m_aszFTPLocalPath[MAX_PATH];    //  FTP����Ŀ¼
    u8      m_byPrint2ScreenLevel;          //  ��ӡ����Ļ����
    u8      m_byPrint2FileLevel;            //  ��ӡ���ļ�����
} TNmsGuiCfg;

class CNmsIntTestUI
{
public:
    CNmsIntTestUI();
    virtual ~CNmsIntTestUI() {}

public:
    /*=============================================================================
    �� �� ��:GetNms
    ��    ��:��ȡNMS����
    ��    ��:LPCTSTR pszProcessName            [in]    ������
    ע    ��:��Ҫ�ֹ�����NMS
    �� �� ֵ:TRUE:�ɹ�; FALSE:ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/08/17  4.0     ���    ����
    =============================================================================*/
    virtual BOOL32 GetNms(LPCTSTR pszProcessName = NMS_EXE_NAME);

    /*=============================================================================
    �� �� ��:StartNms
    ��    ��:����nms
    ��    ��:��
    ע    ��:Nms�����Ѿ����
    �� �� ֵ:TRUE:�����ɹ�; FALSE:����ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/08/17  4.0     ���    ����
    =============================================================================*/
    virtual BOOL32 StartNms(void);

    /*=============================================================================
    �� �� ��:StopNms
    ��    ��:ֹͣnms
    ��    ��:��
    ע    ��:Nms�����Ѿ����
    �� �� ֵ:TRUE:�����ɹ�; FALSE:����ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/08/17  4.0     ���    ����
    =============================================================================*/
    virtual BOOL32 StopNms(void);

    /*=============================================================================
    �� �� ��:CfgNms
    ��    ��:����nms
    ��    ��:const TNmsGuiCfg &tNmsCfg          [in]    nms���ò���
    ע    ��:Nms�����Ѿ����
    �� �� ֵ:TRUE:�����ɹ�; FALSE:����ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2005/08/17  4.0     ���    ����
    =============================================================================*/
    virtual BOOL32 CfgNms(const TNmsGuiCfg &tNmsCfg);

protected:
    CGuiUnit    m_cGuiUnit;             //����������ӿ�

    HWND        m_hStartBtn;            //��ʼ��ť���
    HWND        m_hStopBtn;             //ֹͣ��ť���
    HWND        m_hConfigBtn;           //���ð�ť���
};

#endif  //  _NMSINTTESTUI_20050726_H_