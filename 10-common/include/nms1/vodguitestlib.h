/********************************************************************
ģ����:      VOD������Կ�ģ��
�ļ���:      VodGuiTestLib.h
����ļ�:    
�ļ�ʵ�ֹ��� VOD������Կ�ӿڶ��� 
���ߣ�       �κ�ƽ  
�汾��       4.0
------------------------------------------------------------------------
�޸ļ�¼:
��		��	�汾	�޸���	�߶���	�޸�����
2005/08/11	4.0		�κ�ƽ			����

*********************************************************************/


#if !defined(AFX_VODGUITESTLIB_H__487413F5_38EB_4320_B3A1_A911CEC17636__INCLUDED_)
#define AFX_VODGUITESTLIB_H__487413F5_38EB_4320_B3A1_A911CEC17636__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "guiunit.h"
#include "VodGuiTestDef.h"
//#include "vccommon.h"

typedef struct tagUserInfo
{
	BOOL32	m_bSex;				   //�Ա�true Ϊ��,��֮ΪŮ
	LPTSTR m_szUserID;			//�û�id
	LPTSTR m_szUserName;		//�û���
	LPTSTR m_szPwd;			//�û�����
	LPTSTR m_szRole;			//�û����id
	LPTSTR m_szRoleName;		//�û������������Ա��...��
	LPTSTR m_szTel;			//
	LPTSTR m_szMobilePhone;	//
	LPTSTR m_szBP;			    //
	LPTSTR m_szEmail;			//
	LPTSTR m_szUnit;			//
	LPTSTR m_szAddr;			//
	BOOL32 m_bPassDate;		        //�Ƿ��ʺŹ��� true:�趨����ʱ��
	LPTSTR m_szDate; 		    // �ʺŹ���ʱ������ʾ����2005��08��20��
	//SYSTEMTIEM *pSysDate;         //�ʺŹ���ʱ��
	LPTSTR m_szIfAvailAlways;	//
	LPTSTR m_szvod_Schedule1;	//     �����ʽ:   9:5:16, 0:23:6     �����ʽ:  09:05:16 
	LPTSTR m_szvod_Schedule2;	// ��ֹʱ��
	LPTSTR m_szStylePath;		//
	LPTSTR m_szLocalIP;			//�û���¼ip����
}TUserInfo;

typedef struct tagFileInfo
{
	LPTSTR	 m_szClassName;		//��Ŀ����������
	LPTSTR	 m_szFileFullName;	//��Ŀ�������ƣ�������չ����
	LPTSTR	 m_szFileShortName;	//��Ŀ������ƣ�������չ����
	LPTSTR	 m_szFilePath;		//��Ŀ����·���������mms��Ŀ¼������ip��
	LPTSTR	 m_szFileType ;			//��Ŀ����
	LPTSTR	 m_szFileSize ;		//��Ŀ��С
	LPTSTR	 m_szFileSecret ;		//��Ŀ���ܵȼ�		
	LPTSTR	 m_szFileDesc ;		//��Ŀ��Ҫ����
}TFileInfo;

typedef struct tagFolderInfo
{

	LPTSTR	 m_szClassName;		//��Ŀ����������
	LPTSTR	 m_szParentClassName;	//����Ŀ����������
	LPTSTR	 m_szClassDescribe;	//��Ŀ������
}TFolderInfo;

typedef struct tagSecurityInfo
{
	BOOL bFolMag;
	BOOL bFilePub;
	BOOL bLogMag;
	BOOL bSecretFile;
}TSecurityInfo;

typedef struct tagPosMsg
{
	LPTSTR szFolder;
	LPTSTR szItem;
	LPRECT pRect;
}TPosMsg , *PTPosMsg;

class CVodGuiTestLib  
{
public:
	CVodGuiTestLib();

	virtual ~CVodGuiTestLib();
public:
	/*=============================================================================
	�� �� ����GetOutBarCtlInfo
	��    �ܣ����OutBarCtrl�ؼ���������Ϣ
	��    ����strFolderName      [in]  �����ı�
			  strItemName	 [in]	�����ı�
			  hWnd			   [in]	 �ؼ����
			  cPosRect		   [out]  �ؼ�λ��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GetOutBarCtlSubInfo(HWND hWnd, LPTSTR szFolderName, LPTSTR szItemName, RECT& rectPos);

		/*=============================================================================
	�� �� ����GetOutBarCtlMainInfo
	��    �ܣ����OutBarCtrl�ؼ���������Ϣ
	��    ����strFolderName      [in]  �����ı�
			  hWnd			   [in]	 �ؼ����
			  cPosRect		   [out]  �ؼ�λ��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GetOutBarCtlMainInfo( HWND hWnd, LPCTSTR szFolderName, RECT& rectPos ) const;
    /*=============================================================================
	�� �� ����GuiInit
	��    �ܣ���ʼ��VOD���Կ�
	��    ����strExePath      [in]  Ӧ�ó���·��
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL GuiInit(LPTSTR szExePath);	

	/*=============================================================================
	�� �� ����Login
	��    �ܣ�ϵͳ��¼
	��    ����strName     [in]  �û���
	          strPwd      [in]  ��¼���� 
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 Login(const CString& strLoginName, const CString& strLoginPwd);

	/*=============================================================================
	�� �� ����GuiInitHandle
	��    �ܣ���ʼ���������
	��    ������	          
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 GuiInitHandle();

	/*=============================================================================
	�� �� ����TransMainInterface
	��    �ܣ������л�
	��    ����strInfaceName     [in]  ��������	          
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 TransMainInterface(const CString& strInfaceName);

	/*=============================================================================
	�� �� ����TransInterface
	��    �ܣ������л�
	��    ����strInfaceName     [in]  ��������	          
	�� �� ֵ��BOOL
	=============================================================================*/
    virtual BOOL32 TransInterface(const CString& strInfaceName);

	/*=============================================================================
	�� �� ����DemondFile
	��    �ܣ��ļ��㲥
	��    ����strName     [in]  �ļ���
			  strFolName  [in]  �����ļ�����
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 DemondFile(LPTSTR strName, LPTSTR strFolName);

	/*=============================================================================
	�� �� ����DemondMeet
	��    �ܣ�����ֱ��
	��    ����strMCUName    [in]  MCU����
			  strFileName   [in]  ��������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 DemondMeet(LPTSTR strMCUName, LPTSTR strFileName);

	/*=============================================================================
	�� �� ����AddFolder
	��    �ܣ����ӽ�Ŀ��
	��    ����tFolderInfo     [in]  �½�Ŀ����Ϣ	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 AddFolder(const TFolderInfo& tFolderInfo);

	/*=============================================================================
	�� �� ����DeleteFolder
	��    �ܣ�ɾ����Ŀ��
	��    ����strName     [in]  Ҫɾ���Ľ�Ŀ�������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 DeleteFolder(LPTSTR strName);

	/*=============================================================================
	�� �� ����PubFile
	��    �ܣ��ļ�����
	��    ����tFileInfo     [in]  ���ļ���Ϣ           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 PubFile (const TFileInfo& tFileInfo);

	/*=============================================================================
	�� �� ����DeleteFile
	��    �ܣ�ɾ��ָ�����ļ�
	��    ����strName     [in]  �ļ���	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 DeleteFile(LPTSTR strName);

	/*=============================================================================
	�� �� ����ModiFolder
	��    �ܣ��޸Ľ�Ŀ��
	��    ����nIndex       [in]   ��Ŀ������
	          tFileInfo    [in]   ��Ŀ������Ϣ
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ModiFolder(LPTSTR strFolName, const TFolderInfo& tFolderInfo);

	/*=============================================================================
	�� �� ����ModiFile
	��    �ܣ��޸��ļ�
	��    ����strFileName     [in]  �ļ�����
	          tFileInfo      [in]  �ļ�����Ϣ
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ModiFile(LPTSTR strFileName, const TFileInfo& tFileInfo);

	/*=============================================================================
	�� �� ����QueryFileTal
	��    �ܣ��ļ���ѯ
	��    ����strName     [in]  �ļ���	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 QueryFileTal(const CString& strName);

	/*=============================================================================
	�� �� ����SetCurFoll
	��    �ܣ�����Ϊ��ǰ�ļ���
	��    ����strName     [in]  �ļ���	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 SetCurFoll(LPTSTR strName);

	/*=============================================================================
	�� �� ����QueryFileCur
	��    �ܣ��ļ���ѯ
	��    ����strName     [in]  �ļ���	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 QueryFileCur(const CString& strName);

	/*=============================================================================
	�� �� ����ChangePwd
	��    �ܣ���������
	��    ����strOldPwd     [in]  ������
	          strNewPwd     [in]  ������
			  strConfirPwd	[in]  ȷ������
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ChangePwd(const CString& strOldPwd, const CString& strNewPwd, 
		                 const CString& strConfirPwd);

	/*=============================================================================
	�� �� ����DeleteLog
	��    �ܣ�ɾ��ָ������־
	��    ����nIndex     [in]  ��־����	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 DeleteLog(vector<s32> nIndex);

	/*=============================================================================
	�� �� ����RegistUser
	��    �ܣ����û�ע��
	��    ����tUserInfo     [in]  ���û���Ϣ	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 RegistUser(const TUserInfo& tUserInfo);

	/*=============================================================================
	�� �� ����RefreshList
	��    �ܣ��û��б�ˢ��
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 RefreshList();

	/*=============================================================================
	�� �� ����DeleteUser
	��    �ܣ�ɾ��ָ�����û�
	��    ����strUserId     [in]  �û�ID	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 DeleteUser(LPTSTR strUserId);

	/*=============================================================================
	�� �� ����UnuseUser
	��    �ܣ�ͣ��ָ�����û�
	��    ����strUserId     [in]  �û�ID	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 UnuseUser(const CString& strUserId);

	/*=============================================================================
	�� �� ����ReuseUser
	��    �ܣ���������ָ�����û�
	��    ����strUserId     [in]  �û�ID	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ReuseUser(const CString &strUserId);

	/*=============================================================================
	�� �� ����ModiUser
	��    �ܣ��û������޸�
	��    ����strUserId     [in]  ָ�����û�ID
	          tUserInfo     [in]  �û���������Ϣ
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ModiUser(const CString& strUserId, const TUserInfo& tUserInfo);

	/*=============================================================================
	�� �� ����ModiSecuritySet
	��    �ܣ��޸İ�ȫ����
	��    ����strGroupName     [in]  �û�����
			  TSecurityInfo	   [in]  �°�ȫ��Ϣ
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ModiSecuritySet(LPTSTR strGroupName,
		                    const TSecurityInfo& tSecurityInfo);

	/*=============================================================================
	�� �� ����ResetSecurity
	��    �ܣ����ȫ������Ϣ
	��    ����strGroupName     [in]  �û�����	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ResetSecurity(LPTSTR strGroupName);

	/*=============================================================================
	�� �� ����ToFirstPage
	��    �ܣ����ص���һҳ
	��    ������           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ToFirstPage ();

	/*=============================================================================
	�� �� ����ToPrePage
	��    �ܣ����ص�ǰһҳ
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ToPrePage();

	/*=============================================================================
	�� �� ����ToNextPage
	��    �ܣ�����һҳ
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ToNextPage();

	/*=============================================================================
	�� �� ����ToLastPage
	��    �ܣ������һҳ
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ToLastPage();

	/*=============================================================================
	�� �� ����ToAppointedPage
	��    �ܣ���ָ����ҳ
	��    ����nIndex  [in]  ҳ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 ToAppointedPage (s32 nIndex);

	/*=============================================================================
	�� �� ����LogOut
	��    �ܣ�ע�������ص���¼����
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 LogOut();

	/*=============================================================================
	�� �� ����SysHelp
	��    �ܣ�ϵͳ����
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 SysHelp();

	/*=============================================================================
	�� �� ����QuitSys
	��    �ܣ��뿪ϵͳ
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	virtual BOOL32 QuitSys();

	/*=============================================================================
	�� �� ����GetPageNo
	��    �ܣ�ȡ���б�ҳ��
	��    ������	           
	�� �� ֵ��BOOL
	=============================================================================*/
	u8 GetPageNo(u8 uIndex);

	/*=============================================================================
	�� �� ����ClosePopWnd
	��    �ܣ��رյ����Ի���
	��    ������	           
	�� �� ֵ��virtual BOOL
	=============================================================================
	BOOL32 ClosePopWnd();*/
	/*=============================================================================
	�� �� ����Close
	��    �ܣ��رղ��Խӿڣ������ֳ�
	��    ������	           
	�� �� ֵ����
	=============================================================================*/
    void Close();

	CGuiUnit			m_cGuiUnit;			//����������ӿ�
	
protected:
	HWND				m_hOutBar;   //OutBarCtrl�ؼ����
	HWND				m_hQuit;            //�˳�ϵͳ��ť���

	u8					m_byCurGuiPos;		//��ǰ���ڽ���λ��
	u8					m_byCurGuiSubPos;	//��ǰ�����ӽ���λ��
	u8					m_byFolderPage;       //��ʶ��ǰҳ��
	u8					m_byFilePage;
	u8					m_byFilePubPage;
	u8					m_byPopWnd;			//��ʶ�����Ի���
	s32*				m_pnCount;
	u8					m_byLanguge;			//��ǰ����

	// TSecurityInfo		m_tSecuInfo[GROUP_KIND]; //�����û�������


	HWND				m_hHelp;            //������ť���
	HWND				m_hLogout;          //Logout��ť���
	
	/*//���������ť���ؼ��ľ��
	HWND				m_hVideoOnDemn;   //��Ƶ�㲥��ť���
	HWND				m_hFileOnDemn;    //�ļ��㲥��ť���
	HWND				m_hMeetOnDemn;    //����ֱ����ť���
	HWND				m_hFolderMag;     //��Ŀ�����ť���
	HWND				m_hFilePub;		  //�ļ�������ť���
	HWND				m_hLogMag;        //��־ά����ť���
	HWND				m_hSysSet;        //ϵͳ���ð�ť���
	HWND				m_hComDwn;        //������ذ�ť���
	HWND				m_hPwdChange;     //������İ�ť���
	HWND				m_hAboutSys;      //����ϵͳ��ť���
	HWND				m_hSecurityMag;   //��ȫ����ť���
	HWND				m_hUserMag;       //�û�����ť���
	HWND				m_hSecuritySet;   //��ȫ���ð�ť���*/


    /*�ļ��㲥�����ϵĿؼ����*/
	HWND				m_hFileFstPage;   //�ļ��㲥������ҳ��ť���
	HWND				m_hFilePrePage;   //�ļ��㲥������һҳ��ť���
	HWND				m_hFileNxtPage;   //�ļ��㲥������һҳ��ť���
	HWND				m_hFileLstPage;   //�ļ��㲥�������һҳ��ť���
	HWND				m_hFileWhich;	  //��ת�������	
	HWND				m_hFileGo;        //�ļ��㲥������ת��ť���
	HWND				m_hQueryStartCur; //�ڵ�ǰ��Ŀ���п�ʼ���Ұ�ť���
	HWND				m_hQueryStartTal; //��������Ŀ���п�ʼ���Ұ�ť���
	HWND				m_hFileNameEdit;  //��Ŀ������Edit����
	HWND				m_hFileDirTree;   //��Ŀ�������
	HWND				m_hFileList;      //��Ŀ�б���

	/*�ļ����Ž���Ŀؼ���ť���*/
	
	HWND				m_hFilPlayClose;   //�ر�
	HWND				m_hFilPlayFull;    //ȫ��
	HWND				m_hFilPlayFit;    //����
	HWND				m_hFilPlayNormal;  //ԭʼ��С

	/*����ֱ������ؼ����*/
	HWND				m_hMeetTree;	//����ֱ�������
	HWND				m_hMeetList;

	/*��Ŀ��������ؼ����*/
	HWND				m_hAddFolder;		//���ӽ�Ŀ��ť���
	HWND				m_hDelFolder;		//ɾ����Ŀ��ť���
	HWND				m_hFolFstPage;      //��ҳ��ť���
	HWND				m_hFolPrePage;      //��һҳ��ť���
	HWND				m_hFolNxtPage;      //��һҳ��ť���
	HWND				m_hFolLstPage;      //βҳ��ť���
	HWND				m_hFolWhich;
	HWND				m_hFolGo;            //��ת��ť���

    /*HWND				m_hAddFoldName;       //��Ŀ�����������
	HWND				m_hAddParerntFold;     //����Ŀ����
	HWND				m_hAddFoldDescr;       //��Ŀ����������
	HWND				m_hAddFoldClose;       //�رհ�ť�����
	HWND				m_hAddFoldSave;        //���水ť���

	HWND				m_hModFoldName;       //��Ŀ�����������
	HWND				m_hModParerntFold;     //����Ŀ����
	HWND				m_hModFoldDescr;       //��Ŀ����������
	HWND				m_hModFoldClose;       //�رհ�ť�����
	HWND				m_hModFoldSave;        //���水ť���*/

	HWND				m_hFolFolTree;         //��Ŀ�������
	HWND				m_hFolFolList;		   //��Ŀ���б���
	





	/*��Ŀ��������ؼ����*/
	HWND				m_hAddFile;		       //���ӽ�Ŀ��ť���
	HWND				m_hDelFile;	           //ɾ����Ŀ�����ť
	HWND				m_hFilpubFstPage;      //��ҳ��ť���
	HWND				m_hFilpubPrePage;      //��һҳ��ť���
	HWND				m_hFilpubNxtPage;      //��һҳ��ť���
	HWND				m_hFilpubLstPage;      //βҳ��ť���
	HWND				m_hFilpubWhich;
	HWND				m_hFilpubGo;           //��ת��ť���
	HWND				m_hFilpubTree;
	HWND				m_hFilpubList;

	/*HWND				m_hFileName;           //�ļ����������
	HWND				m_hRecvFoldName;        //������Ŀ���������
	HWND				m_hFilePath;           //��Ŀ·���������
	HWND				m_hFileTalName;        //�ļ�ȫ���������
	HWND				m_hFileSize;           //�ļ���С�������
	HWND				m_hFileDescr;          //�ļ������������
	HWND				m_hFileType;           //�ļ����;��
	HWND				m_hFileProp;           //�ļ�����
	HWND				m_hModFileClose;       //�رհ�ť���
	HWND				m_hModFileSave;        //���水ť���*/

	/*��־ά������ؼ���ť���*/
	HWND				m_hDelLog;             //ɾ����־��ť���
	HWND				m_hLogList;

	/*�������*/
	HWND				m_hOlePwdEdit;		   //������Edit����
	HWND				m_hNewPwdEdit;         //������Edit����
	HWND				m_hConfirmEdit;        //ȷ�Ͽ���

	/*�û��������*/
	HWND				m_hUserReg;            //�û�ע�ᰴť���
	HWND				m_hRefreshList;        //ˢ���б�ť���
	HWND				m_hUserCount;          //��������
	HWND				m_hUserList;

	/*�û�ע�����ؼ����*/
/*	HWND				m_hUserNextPage;       //��һҳ��ť���
	HWND				m_hUserPrePage;        //��һҳ��ť���
	HWND				m_hUserRegsit;         //ע�ᰴť���
	HWND				m_hUserCancel;         //ȡ����ť���
	HWND				m_hUserRegistId;       //�û�ID�������
	HWND				m_hUserRegistName;     //�û����������
	HWND				m_hUserRegistMale;      //�е�ѡ����
	HWND				m_hUserRegistFemale;    //Ů��ѡ����
	HWND				m_hUserRegistGroup;     //�û���ؼ����
	HWND				m_hUserRegistDate;    //���ڿ���
	HWND				m_hUserRegistNever;   //�ʺŲ����ڿ���
	HWND				m_hUserRegistPwd;     //�������
	HWND				m_hUserRegistConf;    //ȷ�Ͽ���
	HWND				m_hUserRegistIp;      //IP����

	HWND				m_hTel;  //�绰����
	HWND				m_hMobil;  //�ֻ�����
	HWND				m_hCall;   //��������
	HWND				m_hEmail;  //Email����
	HWND				m_hAddr;   //���ʿ���
	HWND				m_hCorp;   //��˾������*/

	/*��ȫ���ý���*/
	HWND			m_hSecuGroupEdit; //��ǰ�û����������
	HWND			m_hSecuFolder ;		//��Ŀ�����
	HWND			m_hSecuFilePub;		//��Ŀ����
	HWND			m_hSecuLogMag;		//����ά��
	HWND			m_hSecuSecret;    //�ۿ������ļ���
	HWND			m_hSecuTree;		//�û�������
	HWND			m_hSecuChange;		//����
	HWND			m_hSecuReset;       //�����ϴ�����

};

#endif // !defined(AFX_VODGUITESTLIB_H__487413F5_38EB_4320_B3A1_A911CEC17636__INCLUDED_)
