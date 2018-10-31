/*****************************************************************************
   ģ����      : DCCInteTestQuery
   �ļ���      : DCCInteTestQuery.h
   ����ļ�    : DCCInteTestQuery.cpp
   �ļ�ʵ�ֹ���: DCConsole���ɲ��Բ�ѯ�ඨ��
   ����		   : ������
   �汾        : V1.0
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾     �޸���      �޸�����
   2005/01/25  1.0      ������      ����
******************************************************************************/

#if !defined(AFX_CDCCInteTestQuery_H__50DF2EB4_4FD2_48D1_B016_C9F0315611FF__INCLUDED_)
#define AFX_CDCCInteTestQuery_H__50DF2EB4_4FD2_48D1_B016_C9F0315611FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CppUnit\GuiUnit.h>
#include "kdvtype.h"
#include "dcstrc.h"

class CDCCInteTestQuery  
{
public:
	CDCCInteTestQuery();
	virtual ~CDCCInteTestQuery();

/*====================================================================
    ����        ��  ��DCC�Ĳ���ʵ������
    �������˵����  dwIPAddr����DCC��IP��ַ
                    wListenPort����DCC����ʵ���������˿�
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL ConnectToDCCTestApp(DWORD dwIPAddr=inet_addr("127.0.0.1") , WORD wListenPort=2095);

/*====================================================================
    ����        ��  ��DCC�Ĳ���ʵ������
    �������˵����  ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL DisconnectToDCCTestApp();

    //////////////////////////////////////////////////////////////////////////
    //��ʼ������ 

/*====================================================================
    ����        ��  ��ʼ������ʱ�����ĸ����ڵľ��
    �������˵����  ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL Ini_AllStatic_Handle(CString strWndTitle); 
    
    //////////////////////////////////////////////////////////////////////////
    //����Ϊ����

/*====================================================================
    ����        ��  ��ѯ�û��Ƿ��ѵ�¼
    �������˵����  tUser������¼���û���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsUserLogOn(TDCUser tUser);

/*====================================================================
    ����        ��  ��ѯ�û��Ƿ����
    �������˵����  tUser������¼���û���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsUserExist(TDCUser tUser);

/*====================================================================
    ����        ��  ��ѯ�ն��Ƿ����
    �������˵����  tMt�����ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsMtEntryExist(TDCBaseMt tMt);

/*====================================================================
    ����        ��  ��ѯģ���Ƿ����
    �������˵����  tTemplate����ģ����Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsTemplateExist(TDataConfTemplate tTemplate);

/*====================================================================
    ����        ��  ��ѯ�����Ƿ����
    �������˵����  tConfInfo����������Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsConfExist(TDataConfFullInfo tConfInfo);

/*====================================================================
    ����        ��  ��ѯ�ն��Ƿ��ڻ�����
    �������˵����  tConfInfo����������Ϣ
                    tMt�����ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsMtInConf(TDataConfFullInfo tConfInfo, TDCMt tMt);
    
/*====================================================================
    ����        ��  ��ѯ�ն��Ƿ�����
    �������˵����  tConfInfo����������Ϣ
                    tMt�����ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsMtOnline(TDataConfFullInfo tConfInfo, TDCMt tMt);

/*====================================================================
    ����        ��  ��ѯ��ϯ�Ƿ���ڣ�������ڣ����ж��Ƿ����tMt
    �������˵����  tConfInfo����������Ϣ
                    tMt������ϯ�ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsChairmanExist(TDataConfFullInfo tConfInfo, TDCMt tMt);

/*====================================================================
    ����        ��  ��ѯԶ�˻����Ƿ����
    �������˵����  tDCSConfInfo����Զ�˻�����Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL IsRemoteConfExist(TDCSConfInfo tDCSConfInfo);

protected:

    DWORD m_dwDCCTestNodeId;        //DCC����ʵ����nodeid

    CGuiUnit m_GuiUnit;

    HWND m_hOutLookBar;             //�������ľ��
    //�������пؼ��ľ��
    HWND m_hOutLookBar_ConfMng;     
    HWND m_hOutLookBar_Template;    
    HWND m_hOutLookBar_AddrBook;    
    HWND m_hOutLookBar_SysLog;  
    
    HWND m_hMain;               //�����ھ��
    HWND m_hMenu_Sys;           //�˵��е�ϵͳ��ť���
    HWND m_hMenu_ConfMng;       //�˵��еĻ������ť���
    HWND m_hMenu_FunMng;        //�˵��еĹ��ܹ���ť���
    HWND m_hMenu_Help;         //�˵��еİ�����ť���
    
    HWND m_hAddrBookMngDlg;     //��ַ���Ի���ľ��
    //��ַ���Ի����пؼ��ľ��
    HWND m_hAddrBookMngDlg_List_Mt;

    HWND m_hTemplateMngDlg;     //����ģ��Ի���ľ��
    //����ģ��Ի����пؼ��ľ��
    HWND m_hTemplateMngDlg_List_Template;

    HWND m_hConfMngDlg;     //�������Ի���ľ��
    //�������Ի����пؼ��ľ��
    HWND m_hConfMngDlg_List_Chairman;
    HWND m_hConfMngDlg_List_Mt;
    HWND m_hConfMngDlg_List_Conf;

    HWND m_hPopupUserMngDlg;     //�������û�����Ի���ľ��
    //�������û�����Ի����еĿؼ��ľ��
    HWND m_hPopupUserMngDlg_List_User;
    HWND m_hPopupUserMngDlg_Btn_Cancel;

    HWND m_hPopupLogInDlg;     //�����ĵ�¼�Ի���ľ��
    //�����ĵ�¼�Ի����еĿؼ��ľ��
    HWND m_hPopupLogInDlg_IpAddr_DCSIp;
    HWND m_hPopupLogInDlg_Edit_UserName;
    HWND m_hPopupLogInDlg_Edit_UserPasswd;
    HWND m_hPopupLogInDlg_Btn_OK;
    HWND m_hPopupLogInDlg_Btn_Cancel;

    BOOL GuiActive();                   //�����������ʾ

    BOOL Ini_OutLookBar_Handle();       //��ʼ���������пؼ��ľ��
    
    BOOL Ini_Menu_Handle();             //��ʼ���˵���ť�ľ��
    
    BOOL Ini_AddrBookMng_Handle();      //��ʼ����ַ���Ի����пؼ��ľ��
    
    BOOL Ini_TemplateMng_Handle();      //��ʼ������ģ��Ի����пؼ��ľ��
    
    BOOL Ini_ConfMng_Handle();          //��ʼ���������Ի����пؼ��ľ��
    
    BOOL Ini_PopupUserMng_Handle();     //��ʼ���������û�����Ի����пؼ��ľ��
    
    BOOL Ini_PopupLogInDlg_Handle();    //��ʼ�������ĵ�¼�Ի����пؼ��ľ��
};

#endif // !defined(AFX_CDCCInteTestQuery_H__50DF2EB4_4FD2_48D1_B016_C9F0315611FF__INCLUDED_)
