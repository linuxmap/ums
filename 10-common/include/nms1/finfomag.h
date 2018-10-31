/********************************************************************
ģ����:      VODϵͳ�ļ����ļ��У���־���û�������ļ�
�ļ���:      FInfoMag.h
����ļ�:    
�ļ�ʵ�ֹ��� ��ͷ�ļ�
���ߣ�       
�汾��       4.0
------------------------------------------------------------------------
�޸ļ�¼:
��		��	�汾	�޸���	�߶���	�޸�����
2005/08/23	4.0		

*********************************************************************/


#ifndef _FInfoMag_H
#define  _FInfoMag_H

/*�궨��*/
//UserInfoMag
#define  MAX_FREE_USER_PACKET_NUM		50
#define  DEFAULT_FREE_USER_PACKET_NUM		10

//SFolderInfoMag
#define  MAX_FREE_SFOLDER_PACKET_NUM		10
#define  DEFAULT_FREE_SFOLDER_PACKET_NUM	5

//PopInfoMag
#define  MAX_FREE_POP_PACKET_NUM		50
#define  DEFAULT_FREE_POP_PACKET_NUM		10

//LogInfoMag
#define  MAX_FREE_LOG_PACKET_NUM			100
#define  DEFAULT_FREE_LOG_PACKET_NUM		10

//FolderInfoMag
#define  MAX_FREE_FOLDER_PACKET_NUM		20
#define  DEFAULT_FREE_FOLDER_PACKET_NUM		10

//FileInfoMag
#define  MAX_FREE_FILE_PACKET_NUM		50
#define  DEFAULT_FREE_FILE_PACKET_NUM		10

/************************************************************************/
/*��Ϣ�ṹ*/
//UserInfo�ļ���Ϣ
typedef struct tagUserInfo
{
	char m_szUserID[20+1];			//�û�id
	char m_szUserName[10+1];		//�û���
	char m_szPwd[20+1];				//�û�����
	char m_szSex[10+1];				//�û��Ա�
	char m_szRole[50+1];			//�û����id
	char m_szRoleName[20+1];		//�û������������Ա��...��
	char m_szIfUnused[1+1];			//�Ƿ���ͣ��
	char m_szTel[60+1];				//
	char m_szMobilePhone[60+1];		//
	char m_szBP[60+1];			//
	char m_szEmail[60+1];			//
	char m_szUnit[100+1];			//
	char m_szAddr[100+1];			//
	char m_szIfPassDate[1+1];		//�Ƿ��ʺŹ���
	char m_szUnusedDate[20+1];		//
	char m_szIfAvailAlways[20+1];	//
	char m_szvod_Schedule1[20+1];	//
	char m_szvod_Schedule2[20+1];	//
	char m_szStylePath[10+1];		//
	char m_szLocalIP[20+1];			//�û���¼ip����
}TUserInfo;

//SFolderInfoMag
//����ֱ��Դ��Ϣ
typedef struct tagSFolderInfo
{
	int		 m_nClassID;
	char	 m_szSourceIP[20+1];		//����ֱ��Դ����ip
	char	 m_szSourceDescribe[100+1];	//����ֱ��Դ����
}TSFolderInfo;

//PopInfoMag
//�ļ���Ϣ
typedef struct tagPopInfo
{
	char m_szRole[10+1];			//�û�������ƣ�����Ա��...��
	char m_szRoleName[20+1];		//�û����Ӣ�ļ��
	char m_szPopedoms[200+1];	    //�û�Ȩ�޼�
}TPopInfo;

//LogInfoMag
//�ļ���Ϣ
typedef struct tagLogInfo
{
	int  m_nRecordID;
	int  m_nFileID;
	char m_szUserID[20+1];		
	char m_szUserName[10+1];
	char m_szUserIP[15+1];
	char m_szFileName[50+1];
	char m_szBeginTime[20+1];
	char m_szEndTime[20+1];
}TLogInfo;

//FolderInfoMag
//�ļ�����Ϣ
typedef struct tagFolderInfo
{
	int		 m_nClassID;
	int		 m_nParentClassID;
	char	 m_szClassName[20+1];		//�ļ�����������
	char	 m_szParentClassName[20+1];	//���ļ�����������
	char	 m_szClassDescribe[100+1];	//�ļ�������
}TFolderInfo;


//FileInfoMag

//�ļ���Ϣ
typedef struct tagFileInfo
{
	int		 m_nFileID;
	int		 m_nClassID;
	char	 m_szClassName[20+1];		//�ļ�����������
	char	 m_szFileFullName[50+1];	//�ļ��������ƣ�������չ����
	char	 m_szFileShortName[50+1];	//�ļ�������ƣ�������չ����
	char	 m_szFilePath[100+1];		//�ļ�����·���������mms��Ŀ¼������ip��
	char	 m_szFileType[5+1];			//�ļ�����
	char	 m_szFileSize[20+1];		//�ļ���С
	char	 m_szFileSecret[4+1];		//�ļ����ܵȼ�	
	char	 m_szPublisherID[20+1];		//�ļ�������ID
	char	 m_szPublisherName[10+1];	//�ļ�����������
	char	 m_szPublishTime[20+1];		//�ļ�����ʱ��
	char	 m_szFileDesc[100+1];		//�ļ���Ҫ����
}TFileInfo;



/************************************************************************/
/*�û���Ϣ������ඨ��*/
class CUserInfoList : public CList<TUserInfo*, TUserInfo*>
{
public:
	CUserInfoList();
	virtual ~CUserInfoList();
	
	void  InitPacket(TUserInfo* pPacket);
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TUserInfo* AllocPacket();
	void FreePacket(TUserInfo* pPacket);
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TUserInfo* pPacket, BOOL bDesc = FALSE);
	TUserInfo* GetPacket(BOOL bDesc = FALSE);
	
};

class CUserInfoMag  
{
public:
	CUserInfoMag();
	virtual ~CUserInfoMag();
	
public:
	
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TUserInfo* AllocPacket();
	void FreePacket(TUserInfo* pPacket);
	void FreeAllPackets();
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TUserInfo* pPacket, BOOL bDesc = TRUE);
	TUserInfo* GetPacket(BOOL bDesc = FALSE);
	
protected:
	CUserInfoList m_cUsedUserList;
	CUserInfoList m_cUnusedUserList;
	
private:
	CRITICAL_SECTION m_cs;
};

/************************************************************************/
/*//SFolderInfoMag���ඨ��*/

class CSFolderInfoList : public CList<TSFolderInfo*, TSFolderInfo*>
{
public:
	CSFolderInfoList();
	virtual ~CSFolderInfoList();
	
	void  InitPacket(TSFolderInfo* pPacket);
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TSFolderInfo* AllocPacket();
	void FreePacket(TSFolderInfo* pPacket);

	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TSFolderInfo* pPacket, BOOL bDesc = TRUE);
	TSFolderInfo* GetPacket(BOOL bDesc = FALSE);
};

class CSFolderInfoMag  
{
public:
	CSFolderInfoMag();
	virtual ~CSFolderInfoMag();

public:
	
	DWORD GetTotalCount();
	void  DiscardAllPackets();

	//�����ⲿ���ݷ�����Ļ���
	TSFolderInfo* AllocPacket();
	void FreePacket(TSFolderInfo* pPacket);
	void FreeAllPackets();
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TSFolderInfo* pPacket, BOOL bDesc = TRUE);
	TSFolderInfo* GetPacket(BOOL bDesc = FALSE);
	
protected:
	CSFolderInfoList m_cUsedFolderList;
	CSFolderInfoList m_cUnusedFolderList;

private:
	CRITICAL_SECTION m_cs;
};

/************************************************************************/
/*PopInfoMag�ඨ��*/

class CPopInfoList : public CList<TPopInfo*, TPopInfo*>
{
public:
	CPopInfoList();
	virtual ~CPopInfoList();
	
	void  InitPacket(TPopInfo* pPacket);
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TPopInfo* AllocPacket();
	void FreePacket(TPopInfo* pPacket);
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TPopInfo* pPacket, BOOL bDesc = FALSE);
	TPopInfo* GetPacket(BOOL bDesc = FALSE);
	
};

class CPopInfoMag  
{
public:
	CPopInfoMag();
	virtual ~CPopInfoMag();
	
public:
	
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TPopInfo* AllocPacket();
	void FreePacket(TPopInfo* pPacket);
	void FreeAllPackets();

	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TPopInfo* pPacket, BOOL bDesc = TRUE);
	TPopInfo* GetPacket(BOOL bDesc = FALSE);
	
protected:
	CPopInfoList m_cUsedPopList;
	CPopInfoList m_cUnusedPopList;
	
private:
	CRITICAL_SECTION m_cs;
};


/************************************************************************/
/*LogInfoMag�ඨ��*/


class CLogInfoList : public CList<TLogInfo*, TLogInfo*>
{
public:
	CLogInfoList();
	virtual ~CLogInfoList();
	
	void  InitPacket(TLogInfo* pPacket);
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TLogInfo* AllocPacket();
	void FreePacket(TLogInfo* pPacket);
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TLogInfo* pPacket, BOOL bDesc = FALSE);
	TLogInfo* GetPacket(BOOL bDesc = FALSE);
	
};

class CLogInfoMag  
{
public:
	CLogInfoMag();
	virtual ~CLogInfoMag();
	
public:
	
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TLogInfo* AllocPacket();
	void FreePacket(TLogInfo* pPacket);
	void FreeAllPackets();
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TLogInfo* pPacket, BOOL bDesc = TRUE);
	TLogInfo* GetPacket(BOOL bDesc = FALSE);
	
protected:
	CLogInfoList m_cUsedLogList;
	CLogInfoList m_cUnsedLogList;
	
private:
	CRITICAL_SECTION m_cs;
};

/************************************************************************/
/*FolderInfoMag�ඨ��*/
class CFolderInfoList : public CList<TFolderInfo*, TFolderInfo*>
{
public:
	CFolderInfoList();
	virtual ~CFolderInfoList();
	
	void  InitPacket(TFolderInfo* pPacket);
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TFolderInfo* AllocPacket();
	void FreePacket(TFolderInfo* pPacket);

	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TFolderInfo* pPacket, BOOL bDesc = TRUE);
	TFolderInfo* GetPacket(BOOL bDesc = FALSE);
};

class CFolderInfoMag  
{
public:
	CFolderInfoMag();
	virtual ~CFolderInfoMag();

public:
	
	DWORD GetTotalCount();
	void  DiscardAllPackets();

	//�����ⲿ���ݷ�����Ļ���
	TFolderInfo* AllocPacket();
	void FreePacket(TFolderInfo* pPacket);
	void FreeAllPackets();
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TFolderInfo* pPacket, BOOL bDesc = TRUE);
	TFolderInfo* GetPacket(BOOL bDesc = FALSE);
	
protected:
	CFolderInfoList m_cUsedFolderList;
	CFolderInfoList m_cUnusedFolderList;

private:
	CRITICAL_SECTION m_cs;
};


/************************************************************************/
/*FileInfoMag�ඨ��*/


class CFileInfoList : public CList<TFileInfo*, TFileInfo*>
{
public:
	CFileInfoList();
	virtual ~CFileInfoList();
	
	void  InitPacket(TFileInfo* pPacket);
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TFileInfo* AllocPacket();
	void FreePacket(TFileInfo* pPacket);
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TFileInfo* pPacket, BOOL bDesc = TRUE);
	TFileInfo* GetPacket(BOOL bDesc = FALSE);

};

class CFileInfoMag  
{
public:
	CFileInfoMag();
	virtual ~CFileInfoMag();
	
public:
	
	DWORD GetTotalCount();
	void  DiscardAllPackets();
	
	//�����ⲿ���ݷ�����Ļ���
	TFileInfo* AllocPacket();
	void FreePacket(TFileInfo* pPacket);
	void FreeAllPackets();
	
	//�����ⲿ���ݵ�ά��
	BOOL AddPacket(TFileInfo *pPacket, BOOL bDesc = TRUE);
	TFileInfo* GetPacket(BOOL bDesc = FALSE);
	
protected:
	CFileInfoList m_cUsedFileList;
	CFileInfoList m_cUnusedFileList;
	
private:
	CRITICAL_SECTION m_cs;
};
#endif