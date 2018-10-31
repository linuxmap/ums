/********************************************************************
ģ����:      ���ݿ����������
�ļ���:      DBOperate.h
����ļ�:    
�ļ�ʵ�ֹ��� �����ӿ�ʵ��ͷ�ļ�
���ߣ�       
�汾��       4.0
------------------------------------------------------------------------
�޸ļ�¼:
��		��	�汾	�޸���	�߶���	�޸�����
2005/08/22	4.0		�κ�ƽ

*********************************************************************/

#if !defined(AFX_DBOPERATE_H__C01764B0_66E9_471B_9931_62802DDD3E83__INCLUDED_)
#define AFX_DBOPERATE_H__C01764B0_66E9_471B_9931_62802DDD3E83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4146)

#import "C:\Program Files\Common Files\System\ADO\msado15.dll"\
	no_namespace \
rename("EOF","ISEOF")


#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#include "kdvtype.h"

//һЩ�궨��

#define  VOD_OK                 (u16)0    //VOD������ɹ� 
#define  VODERR_BASE_CODE		(u16)20000//�������׼ֵ


//��¼ʱ�������֤ʧ��
#define VODERR_DB_INDENTIFY_METHOD			(u16)(VODERR_BASE_CODE + 1) 
//����������Ϣʧ��
#define VODERR_DB_LOADCLASSINFO_METHOD		(u16)(VODERR_BASE_CODE + 2) 
//���������е��ļ���Ϣʧ��
#define VODERR_DB_LOADFILEINFO_METHOD		(u16)(VODERR_BASE_CODE + 3) 
//����������Ȩ����Ϣ
#define VODERR_DB_LOADPOPINFO_METHOD		(u16)(VODERR_BASE_CODE + 4) 
//�����û���½����
#define VODERR_DB_CHANGEPWD_METHOD			(u16)(VODERR_BASE_CODE + 5) 
//�������Ȩ�޼�
#define VODERR_DB_UPDATEPOPS_METHOD			(u16)(VODERR_BASE_CODE + 6) 
//������־��Ϣʧ��
#define VODERR_DB_LOADLOGINFO_METHOD		(u16)(VODERR_BASE_CODE + 7) 
//����һ���㲥��¼
#define VODERR_DB_ADDONELOG_METHOD			(u16)(VODERR_BASE_CODE + 8) 
//ɾ��һ���㲥��¼
#define VODERR_DB_DELONELOG_METHOD			(u16)(VODERR_BASE_CODE + 9) 
//����һ���ļ�������¼
#define VODERR_DB_ADDONEPUB_METHOD			(u16)(VODERR_BASE_CODE + 10)
//����һ���ļ�������¼
#define VODERR_DB_UPDATEONEPUB_METHOD		(u16)(VODERR_BASE_CODE + 11) 
//ɾ��һ���ļ�������¼
#define VODERR_DB_DELONEPUB_METHOD			(u16)(VODERR_BASE_CODE + 12) 
//����һ���ļ����¼
#define VODERR_DB_ADDONECLASS_METHOD		(u16)(VODERR_BASE_CODE + 13)
//����һ���ļ����¼
#define VODERR_DB_UPDATEONECLASS_METHOD		(u16)(VODERR_BASE_CODE + 14) 
//ɾ��һ���ļ����¼
#define VODERR_DB_DELONECLASS_METHOD		(u16)(VODERR_BASE_CODE + 15) 
//�����û���Ϣʧ��
#define VODERR_DB_LOADUSERINFO_METHOD		(u16)(VODERR_BASE_CODE + 16) 
//����һ���û���¼
#define VODERR_DB_ADDONEUSER_METHOD			(u16)(VODERR_BASE_CODE + 17)
//����һ���û���¼
#define VODERR_DB_UPDATEONEUSER_METHOD		(u16)(VODERR_BASE_CODE + 18) 
//ɾ��һ���û���¼
#define VODERR_DB_DELONEUSER_METHOD			(u16)(VODERR_BASE_CODE + 19) 
//����һ���û���ͣ�á����ü�¼���
#define VODERR_DB_SETONEUSERFLAG_METHOD		(u16)(VODERR_BASE_CODE + 20)
//����һ���㲥��¼
#define VODERR_DB_UPDATEONEPLAYLOG_METHOD   (u16)(VODERR_BASE_CODE + 21)
//��ѯ��ǰ�㲥����
#define VODERR_DB_QUERYNUMOFPLAYING_METHOD	(u16)(VODERR_BASE_CODE + 22);


//�����ļ����������ݿ����������Ч
#define VODERR_OPEN_DB_PARAM				(u16)(VODERR_BASE_CODE + 47) 
//�����ݿ����ӵĲ���ʧ��
#define VODERR_OPEN_DB						(u16)(VODERR_BASE_CODE + 48) 
//���ݿ�û�н������Ӳ������Դ��ڹر�״̬
#define VODERR_DB_CLOSE_STATUS				(u16)(VODERR_BASE_CODE + 49) 


//�����ļ�����ʧ��
#define VODERR_DB_INSERT_METHOD				(u16)(VODERR_BASE_CODE + 50) 
//ȡ�������ļ�����ʧ��
#define VODERR_DB_CANCEL_METHOD				(u16)(VODERR_BASE_CODE + 51) 
//��ѯ�ļ�����״̬����ʧ��
#define VODERR_DB_QUERY_METHOD				(u16)(VODERR_BASE_CODE + 52) 
//�����ļ�����״̬����ʧ��
#define VODERR_DB_UPDATE_METHOD				(u16)(VODERR_BASE_CODE + 53) 

#define MAX_LIST_PAGE_SIZE		10


//DBOperate�ඨ��

class CDBOperate  
{
public:
	CDBOperate();
	virtual ~CDBOperate();

public:
	/*=============================================================================
	�� �� ����OpenDB
	��    �ܣ������ݿ�
	��    ����szHostIP
			  szUserName
			  szPwd
			  wPort = 1433          
	�� �� ֵ��WORD      : ����VOD_OK ��ʾ�����ɹ���
	=============================================================================*/
	virtual u16 OpenDB(CString &szHostIP, CString &szUserName, CString &szPwd, u16 wPort = 1433);
	/*=============================================================================
	�� �� ����CloseDB
	��    �ܣ��ر����ݿ�
	��    ������	           
	�� �� ֵ��WORD
	=============================================================================*/
	virtual u16 CloseDB();
	/*=============================================================================
	�� �� ����GetErrorDescript
	��    �ܣ� 
	��    ������	           
	�� �� ֵ��CString
	=============================================================================*/
	 virtual CString GetErrorDescript();
	/*=============================================================================
	�� �� ����PublishOneFile
	��    �ܣ�
	��    ����szFilePath
	          szFileName
			  bSecret
	�� �� ֵ��WORD
	=============================================================================*/
	
	virtual u16 PublishOneFile(char *szFilePath, char *szFileName, u32 dwFileSize, char *szPublishTime, BOOL bSecret);
	/*=============================================================================
	�� �� ����CancelOnePublishedFile
	��    �ܣ�
	��    ����szFilePath
			  szFileName
	�� �� ֵ��WORD
	=============================================================================*/
	
	virtual u16 UpdatePublishOneFile(char *szFilePath, char *szFileName, u32 dwFileSize);
	/*=============================================================================
	�� �� ����UpdateOnePublishedFile
	��    �ܣ�
	��    ����szFilePath
			  szFileName
	�� �� ֵ��WORD
	=============================================================================*/

	virtual u16 CancelOnePublishedFile(char *szFilePath, char *szFileName);
	/*=============================================================================
	�� �� ����QueryOneFileStauts
	��    �ܣ�
	��    ����szFilePath
			  szFileName
			  bPublished
	�� �� ֵ��WORD
	=============================================================================*/
	virtual u16 QueryOneFileStauts(char *szFilePath, char *szFileName, BOOL &bPublished);	 


private:
	_ConnectionPtr m_pCon;		//���ݿ����ӱ���
	
	CString m_szErrorInfo;

	CRITICAL_SECTION  m_csdbLock;

//	static BOOL m_bComInited;
	
	BOOL m_bWSAInited;
};
#endif // !defined(AFX_DBOPERATE_H__C01764B0_66E9_471B_9931_62802DDD3E83__INCLUDED_)
