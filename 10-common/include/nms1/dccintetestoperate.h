/*****************************************************************************
   ģ����      : DCCInteTestOperate
   �ļ���      : DCCInteTestOperate.h
   ����ļ�    : DCCInteTestOperate.cpp
   �ļ�ʵ�ֹ���: DCConsole���ɲ��Բ����ඨ��
   ����		   : ������
   �汾        : V1.0
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾     �޸���      �޸�����
   2005/01/25  1.0      ������      ����
******************************************************************************/

#if !defined(AFX_DCCINTETESTOPERATE_H__61AEC7E5_BC88_48DC_BF1A_BB0C37BE6007__INCLUDED_)
#define AFX_DCCINTETESTOPERATE_H__61AEC7E5_BC88_48DC_BF1A_BB0C37BE6007__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <CppUnit\GuiUnit.h>
#include "kdvtype.h"
#include "dcstrc.h"

class CDCCInteTestOperate  
{
public:
	CDCCInteTestOperate();
	virtual ~CDCCInteTestOperate();

/*====================================================================
    ����        ��  �Զ��������ݻ������̨����ʼ��
    �������˵����  lpszDCCHtmlFile����DCConsole.htm�ļ���·��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL StartDCCAndIni(LPCSTR lpszDCCHtmlFile);

/*====================================================================
    ����        ��  �ر����ݻ������̨
    �������˵����  ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/   
	BOOL StopDCC();

/*====================================================================
    ����        ��  �ֶ���������̨���ʼ�������ڵľ��
    �������˵����  strWndTitle��������̨�Ĵ���title
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/ 
    BOOL Ini_AllStatic_Handle(CString strWndTitle);            
    
    //////////////////////////////////////////////////////////////////////////
    //����Ϊ����
    
/*====================================================================
    ����        ��  �û���¼
    �������˵����  dwSvrIp������������ַ
                    tUser������¼���û���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL UserLogOn(DWORD dwSvrIp, TDCUser tUser);

/*====================================================================
    ����        ��  �û�ע��
    �������˵����  ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL UserLogOut();

/*====================================================================
    ����        ��  �����ն���Ŀ
    �������˵����  tMt�������ӵ��ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL AddMtEntry(TDCBaseMt tMt);

/*====================================================================
    ����        ��  ��ģ����������ն���Ŀ
    �������˵����  tMt�������ӵ��ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL AddMtEntryFromTemplate(TDCBaseMt tMt);

/*====================================================================
    ����        ��  �޸��ն���Ŀ
    �������˵����  tMt�����޸ĵ��ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL ModifyMtEntry(TDCBaseMt tMt);

/*====================================================================
    ����        ��  ɾ���ն���Ŀ
    �������˵����  lpszMtAliast������ɾ���ն˵ı���
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
	BOOL DelMtEntry(LPCSTR lpszMtAlias);
    
/*====================================================================
    ����        ��  ɾ�������ն���Ŀ
    �������˵����  ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL DelAllMtEntry();

/*====================================================================
    ����        ��  ���ӻ���ģ��
    �������˵����  tConfEntry�������ӵ�ģ����Ϣ
                    bAddAllMt�����Ƿ񽫵�ַ���е������ն˼���ģ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL AddConfEntry(TDataConfTemplate tConfEntry, BOOL bAddAllMt=FALSE);

/*====================================================================
    ����        ��  �޸Ļ���ģ��
    �������˵����  tConfEntry�����޸ĵ�ģ����Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL ModifyConfEntry(TDataConfTemplate tConfEntry);

/*====================================================================
    ����        ��  ɾ������ģ��
    �������˵����  lpszTemplateName������ɾ��ģ�������
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL DelConfEntry(LPCSTR lpszTemplateName);
    
/*====================================================================
    ����        ��  ɾ�����л���ģ��
    �������˵����  ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL DelAllConfEntry();

/*====================================================================
    ����        ��  �����û�
    �������˵����  tUser�������ӵ��û���Ϣ
                    lpszConfirmPasswd���������ȷ������
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL AddDCUser(TDCUser tUser, LPCSTR lpszConfirmPasswd="");

/*====================================================================
    ����        ��  �޸��û�
    �������˵����  tUser�����޸ĵ��û���Ϣ
                    lpszConfirmPasswd���������ȷ������
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL ModifyDCUser(TDCUser tUser, LPCSTR lpszConfirmPasswd="");

/*====================================================================
    ����        ��  ɾ���û�
    �������˵����  lpszUserName������ɾ�����û�����
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL DelDCUser(LPCSTR lpszUserName);

/*====================================================================
    ����        ��  ɾ�������û���Admin����
    �������˵����  
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL DelAllDCUser();

/*====================================================================
    ����        ��  �ֶ����������Ϣ����������
    �������˵����  tConfInfo����������Ϣ
                    bAddAllMt�����Ƿ񽫵�ַ���������ն˶��������
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL CreateConfDirect(TDataConfFullInfo tConfInfo, BOOL bAddAllMt=FALSE);
    
/*====================================================================
    ����        ��  ѡ��ģ�壬��������
    �������˵����  lpszTemplateName����ģ����
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL CreateConfByTemplate(LPCSTR lpszTemplateName);

/*====================================================================
    ����        ��  ��������
    �������˵����  lpszConfName����������
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL TermConf(LPCSTR lpszConfName);

/*====================================================================
    ����        ��  ��������е��ն�
    �������˵����  lpszConfName����������
                    tMt�����ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL InviteMtInConf(LPCSTR lpszConfName, TDCMt tMt);

/*====================================================================
    ����        ��  ���벻�ڻ����е��ն�
    �������˵����  lpszConfName����������
                    tMt�����ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL InviteMtOutConf(LPCSTR lpszConfName, TDCMt tMt);

/*====================================================================
    ����        ��  �Ҷ��ն�
    �������˵����  lpszConfName����������
                    tMt�����ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL EjectMt(LPCSTR lpszConfName, TDCMt tMt);

/*====================================================================
    ����        ��  ɾ���ն�
    �������˵����  lpszConfName����������
                    tMt�����ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL RemoveMt(LPCSTR lpszConfName, TDCMt tMt);

/*====================================================================
    ����        ��  ָ����ϯ
    �������˵����  lpszConfName����������
                    tMt������ϯ�ն���Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL SpecChairman(LPCSTR lpszConfName, TDCMt tMt);
    
/*====================================================================
    ����        ��  ȡ����ϯ
    �������˵����  lpszConfName����������
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL CancelChairman(LPCSTR lpszConfName);

/*====================================================================
    ����        ��  �������л���
    �������˵����  ��
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL TermAllConf();

/*====================================================================
    ����        ��  ����Զ�˻���
    �������˵����  tDCSConfInfo����Զ�˻�����Ϣ
    ����ֵ˵��  ��  true    �����ɹ�
                    false   ����ʧ��
====================================================================*/
    BOOL JoinRemoteConf(TDCSConfInfo tDCSConfInfo);
    
protected:

    CGuiUnit m_GuiUnit;

    HWND m_hOutLookBar;             //�������ľ��
    //�������пؼ��ľ��
    HWND m_hOutLookBar_ConfMng;     
    HWND m_hOutLookBar_Template;    
    HWND m_hOutLookBar_AddrBook;    
    HWND m_hOutLookBar_SysLog;      
    
    HWND m_hMain;           //�����ھ��
    HWND m_hMenu_Sys;       //�˵��е�ϵͳ��ť���
    HWND m_hMenu_ConfMng;   //�˵��еĻ������ť���
    HWND m_hMenu_FunMng;    //�˵��еĹ��ܹ���ť���
    HWND m_hMenu_Help;      //�˵��еİ�����ť���

    HWND m_hAddrBookMngDlg;     //��ַ���Ի���ľ��
    //��ַ���Ի����пؼ��ľ��
    HWND m_hAddrBookMngDlg_List_Mt;
    HWND m_hAddrBookMngDlg_Btn_Add;
    HWND m_hAddrBookMngDlg_Btn_Modify;
    HWND m_hAddrBookMngDlg_Btn_Del;

    HWND m_hPopupAddrBookCfgDlg;    //�������ն����öԻ���
    //�������ն����öԻ����еĿؼ����
    HWND m_hPopupAddrBookCfgDlg_Edit_Alias;
    HWND m_hPopupAddrBookCfgDlg_Combo_CallType;
    HWND m_hPopupAddrBookCfgDlg_IpAddr_MtIp;
    HWND m_hPopupAddrBookCfgDlg_Edit_MtPort;
    HWND m_hPopupAddrBookCfgDlg_Edit_MtE164;
    HWND m_hPopupAddrBookCfgDlg_Edit_MtRemark;
    HWND m_hPopupAddrBookCfgDlg_Btn_OK;
    HWND m_hPopupAddrBookCfgDlg_Btn_Cancel;

    HWND m_hTemplateMngDlg;     //����ģ��Ի���ľ��
    //����ģ��Ի����пؼ��ľ��
    HWND m_hTemplateMngDlg_List_Template;
    HWND m_hTemplateMngDlg_Btn_Add;
    HWND m_hTemplateMngDlg_Btn_Modify;
    HWND m_hTemplateMngDlg_Btn_Del;

    HWND m_hPopupTemplateCfgDlg;    //�����Ļ���ģ�����öԻ���
    //�����Ļ���ģ�����öԻ����еĿؼ����
    HWND m_hPopupTemplateCfgDlg_Edit_Name;
    HWND m_hPopupTemplateCfgDlg_Edit_BandWidth;
    HWND m_hPopupTemplateCfgDlg_Edit_PassWd;
    HWND m_hPopupTemplateCfgDlg_List_MtInConf;
    HWND m_hPopupTemplateCfgDlg_List_MtOutConf;
    HWND m_hPopupTemplateCfgDlg_List_Chairman;
    HWND m_hPopupTemplateCfgDlg_Check_H323;
    HWND m_hPopupTemplateCfgDlg_Check_PassWd;
    HWND m_hPopupTemplateCfgDlg_Check_WhiteBoard;
    HWND m_hPopupTemplateCfgDlg_Check_AppShare;
    HWND m_hPopupTemplateCfgDlg_Check_Chat;
    HWND m_hPopupTemplateCfgDlg_Check_FileTrans;
    HWND m_hPopupTemplateCfgDlg_Check_MtCallIn;
    HWND m_hPopupTemplateCfgDlg_Check_AutoReInvite;
    HWND m_hPopupTemplateCfgDlg_Check_Chairman;
    HWND m_hPopupTemplateCfgDlg_Btn_OK;
    HWND m_hPopupTemplateCfgDlg_Btn_Cancel;
    HWND m_hPopupTemplateCfgDlg_Btn_AddAllMtToConf;
    HWND m_hPopupTemplateCfgDlg_Btn_AddOneMtToConf;
    HWND m_hPopupTemplateCfgDlg_Btn_DelAllMtFromConf;
    HWND m_hPopupTemplateCfgDlg_Btn_DelOneMtFromConf;
    HWND m_hPopupTemplateCfgDlg_Btn_SpecChairman;
    HWND m_hPopupTemplateCfgDlg_Btn_CancelChairman;
    HWND m_hPopupTemplateCfgDlg_Btn_AddMt;

    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg;    //�����Ļ���ģ�����öԻ����е����������ն˶Ի���
    //�����Ļ���ģ�����öԻ����е����������ն˶Ի����еĿؼ����
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_Edit_Alias;
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_Combo_CallType;
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_IpAddr_MtIp;
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_Edit_MtPort;
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_Edit_MtE164;
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_Edit_MtRemark;
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_Btn_OK;
    HWND m_hPopupTemplateCfgDlg_PopupAddMtDlg_Btn_Cancel;

    HWND m_hConfMngDlg;     //�������Ի���ľ��
    //�������Ի����пؼ��ľ��
    HWND m_hConfMngDlg_List_Chairman;
    HWND m_hConfMngDlg_List_Mt;
    HWND m_hConfMngDlg_List_Conf;
    HWND m_hConfMngDlg_Btn_SpecChairman;
    HWND m_hConfMngDlg_Btn_CancelChairman;
    HWND m_hConfMngDlg_Btn_InviteMt;
    HWND m_hConfMngDlg_Btn_EjectMt;
    HWND m_hConfMngDlg_Btn_RemoveMt;
    HWND m_hConfMngDlg_Btn_CreateConf;
    HWND m_hConfMngDlg_Btn_TermConf;

    HWND m_hConfMngDlg_PopupCreateConfDlg;     //�������Ի����е����Ĵ�������Ի���ľ��
    //�������Ի����е����Ĵ�������Ի����еĿؼ��ľ��
    HWND m_hConfMngDlg_PopupCreateConfDlg_Edit_Name;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Edit_BandWidth;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Edit_PassWd;
    HWND m_hConfMngDlg_PopupCreateConfDlg_List_Template;
    HWND m_hConfMngDlg_PopupCreateConfDlg_List_MtInConf;
    HWND m_hConfMngDlg_PopupCreateConfDlg_List_MtOutConf;
    HWND m_hConfMngDlg_PopupCreateConfDlg_List_Chairman;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_H323;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_PassWd;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_WhiteBoard;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_AppShare;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_Chat;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_FileTrans;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_MtCallIn;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_AutoReInvite;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Check_Chairman;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_OK;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_Cancel;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_AddAllMtToConf;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_AddOneMtToConf;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_DelAllMtFromConf;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_DelOneMtFromConf;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_SpecChairman;
    HWND m_hConfMngDlg_PopupCreateConfDlg_Btn_CancelChairman;

    HWND m_hConfMngDlg_PopupInviteMtDlg;     //�������Ի����е����������ն˶Ի���ľ��
    //�������Ի����е����������ն˶Ի����еĿؼ��ľ��
    HWND m_hConfMngDlg_PopupInviteMtDlg_List_MtOutConf;
    HWND m_hConfMngDlg_PopupInviteMtDlg_Btn_OK;
    HWND m_hConfMngDlg_PopupInviteMtDlg_Btn_Cancel;

    HWND m_hPopupUserMngDlg;     //�������û�����Ի���ľ��
    //�������û�����Ի����еĿؼ��ľ��
    HWND m_hPopupUserMngDlg_List_User;
    HWND m_hPopupUserMngDlg_Btn_Add;
    HWND m_hPopupUserMngDlg_Btn_Modify;
    HWND m_hPopupUserMngDlg_Btn_Del;
    HWND m_hPopupUserMngDlg_Btn_Cancel;

    HWND m_hPopupUserCfgDlg;     //�������û����öԻ���ľ��
    //�������û����öԻ����еĿؼ��ľ��
    HWND m_hPopupUserCfgDlg_Edit_Name;
    HWND m_hPopupUserCfgDlg_Edit_Passwd;
    HWND m_hPopupUserCfgDlg_Edit_ConfirmPasswd;
    HWND m_hPopupUserCfgDlg_Combo_Level;
    HWND m_hPopupUserCfgDlg_Btn_OK;
    HWND m_hPopupUserCfgDlg_Btn_Cancel;

    HWND m_hPopupLogInDlg;     //�����ĵ�¼�Ի���ľ��
    //�����ĵ�¼�Ի����еĿؼ��ľ��
    HWND m_hPopupLogInDlg_IpAddr_DCSIp;
    HWND m_hPopupLogInDlg_Edit_UserName;
    HWND m_hPopupLogInDlg_Edit_UserPasswd;
    HWND m_hPopupLogInDlg_Btn_OK;
    HWND m_hPopupLogInDlg_Btn_Cancel;

    HWND m_hPopupGetRemoteConfDlg;     //�����Ĳ�ѯԶ�˻���Ի���ľ��
    //�����Ĳ�ѯԶ�˻���Ի����еĿؼ��ľ��
    HWND m_hPopupGetRemoteConfDlgDlg_Combo_CallType;
    HWND m_hPopupGetRemoteConfDlgDlg_Edit_SvrE164;
    HWND m_hPopupGetRemoteConfDlgDlg_IpAddr_SvrIp;
    HWND m_hPopupGetRemoteConfDlgDlg_Edit_SvrPort;
    HWND m_hPopupGetRemoteConfDlgDlg_Check_H323;
    HWND m_hPopupGetRemoteConfDlgDlg_Btn_OK;
    HWND m_hPopupGetRemoteConfDlgDlg_Btn_Cancel;

    HWND m_hPopupJoinRemoteConfDlg;     //�����ļ���Զ�˻���Ի���ľ��
    //�����ļ���Զ�˻���Ի����еĿؼ��ľ��
    HWND m_hPopupJoinRemoteConfDlgDlg_List_RemoteConf;
    HWND m_hPopupJoinRemoteConfDlgDlg_Edit_ConfPasswd;
    HWND m_hPopupJoinRemoteConfDlgDlg_Btn_OK;
    HWND m_hPopupJoinRemoteConfDlgDlg_Btn_Cancel;
    
    BOOL GuiActive();                           //�����������ʾ
    
    BOOL CloseInfoWindow(HWND hParentWnd);      //�ر���Ϣ��������

    BOOL Ini_OutLookBar_Handle();               //��ʼ���������пؼ��ľ��
    
    BOOL Ini_Menu_Handle();                     //��ʼ���˵���ť�ľ��
    
    BOOL Ini_AddrBookMng_Handle();              //��ʼ����ַ���Ի����пؼ��ľ��
    
    BOOL Ini_PopupAddrBookCfg_Handle();         //��ʼ�������ĵ�ַ���Ի����пؼ��ľ��
    
    BOOL Ini_TemplateMng_Handle();              //��ʼ������ģ��Ի����пؼ��ľ��
    
    BOOL Ini_PopupTemplateCfg_Handle();         //��ʼ�������Ļ���ģ��Ի����пؼ��ľ��
    
    BOOL Ini_PopupTemplateCfg_PopupAddMt_Handle(); //��ʼ�������������ն˶Ի����пؼ��ľ��
    
    BOOL Ini_ConfMng_Handle();                  //��ʼ���������Ի����пؼ��ľ��
    
    BOOL Ini_PopupConfCreate_Handle();          //��ʼ�������Ĵ�������Ի����пؼ��ľ��
    
    BOOL Ini_PopupInviteMt_Handle();            //��ʼ�������������ն˶Ի����пؼ��ľ��
    
    BOOL Ini_PopupUserMng_Handle();             //��ʼ���������û�����Ի����пؼ��ľ��
    
    BOOL Ini_PopupUserCfg_Handle();             //��ʼ���������û����öԻ����пؼ��ľ��
    
    BOOL Ini_PopupLogInDlg_Handle();            //��ʼ�������ĵ�¼�Ի����пؼ��ľ��
    
    BOOL Ini_PopupGetRemoteConfDlg_Handle();    //��ѯԶ�˻���Ի����пؼ��ľ��
    
    BOOL Ini_PopupJoinRemoteConfDlg_Handle();   //����Զ�˻���Ի����пؼ��ľ��
};

#endif // !defined(AFX_DCCINTETESTOPERATE_H__61AEC7E5_BC88_48DC_BF1A_BB0C37BE6007__INCLUDED_)
