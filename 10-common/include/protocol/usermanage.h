#ifndef _UMM_H_
#define _UMM_H_

#ifdef _LINUX_
#include <unistd.h>
#endif
#include "ummessagestruct.h"
//#include "mtutilscharset.h"
//#include "mtmacro.h"
#include "protocolcommonpublic.h"

#define VER_UM (const char *)"kdvum.40.06.02.131008"

#define AID_UMSERVER                    236
#define MAX_MSG_BUFF_SIZE               (64*1024)

// ����ͳһ�Ƶ�ͷ�ļ��� [pengguofeng 5/7/2013]
#if defined( WIN32 )    /* WIN32 */
#define PATH_DATA			( LPCSTR )"data"	//��Ϣ�ļ�·��
#elif defined( VXWORKS_SIMU )
#define PATH_DATA			( LPCSTR )"data"	//��Ϣ�ļ�·��
#elif defined(_LINUX_)
#define PATH_DATA			( LPCSTR )"/usr/conf"	//��Ϣ�ļ�·��
#else                   /* vxWorks */
#define PATH_DATA			( LPCSTR )"/data"	//��Ϣ�ļ�·��
#endif

// ���뷽ʽ [pengguofeng 4/22/2013]
#define ENCODE_GBK						0
#define ENCODE_UTF8						1

// �ļ���
#define USERINFOFILENAME				( LPCSTR )"login.usr"
// �ļ�ͷ
#define UM_FILEHEAD						(const s8*)"kdvum"
// �汾��
#define UM_VER							(u32)20130422
#define MAX_FILEHEAD_LEN				32
#define USERINFO_MEMBERNUM				(u8)9			// CUserFullInfo�ĳ�Ա���� [pengguofeng 4/24/2013]
//////////////////////////////////////////////////////////////////////////

//ö�ٶ���
// ʹ��˵��:
// emType[u8] + emBufLen[u32] + emBuf[s8* ]
// ����ʹ�õķ�ΧΪ1~254 [pengguofeng 5/6/2013]
enum emType
{
	emUmStart = (u8)0,	//��ֹʹ�õ�ֵ
	emUserInfo,
	//����������չ������޵�254
	emEnd
};

class PROTO_API CUsrManage
{
public:
	/*
	 *	���캯��ʹ��˵����acFilePath�� ����Ŀ¼����������ǰ�ĺ�  ����Ҫ�޸�
	 *                    achFileName: ������ļ�������������ǰ�ĺ� ����Ҫ�޸�
	 *					  byEncoding:  �ӵ�ǰMCU/MTƽ̨��ʹ�õı��뷽ʽ �Լ��趨
	 *                    bIsMcu    :  ��MCUƽ̨��Ҫ���TRUE,����(��MT)ʹ��Ĭ�ϵ�FALSE����
	 */
	CUsrManage(); //Ĭ��
	CUsrManage( u8* pbyFilePath, u8* pbyFileName = NULL, u8 byEncoding = ENCODE_GBK, BOOL32 bIsMcu = FALSE); //���洢�û���Ϣ�ļ�·��
	~CUsrManage();
private:
	u32 m_dwError; //��Ϣ������
	CUserFullInfo m_acUsrAllMembers[MAX_USERNUM]; //�û��б�
	u8  m_byUsrNum; //�û�����
	char  m_achCurrentPath[256];//�洢�û���Ϣ�ļ�·��
	char  m_achFileName[MAX_UMFILENAME_LEN];   //�ϰ汾�洢�����û���Ϣ���ļ���
	char  m_achCurFile[MAX_UMFILENAME_LEN];    //��ǰ�洢�û���Ϣ�����ļ���
    s8 m_achMsgBuff[MAX_MSG_BUFF_SIZE];
    BOOL32 m_bSingle;
	u8	m_byPlatEncoding;                      //ƽ̨���뷽ʽ:ʹ������궨�� [pengguofeng 4/22/2013]
	u8	m_byFileEncoding;						//�ļ����뷽ʽ��ֻ�ڿ�ʼ��ʱ�����һ��
	u8  m_byEmTypeNum;							//emtype����
	u8  m_byIsMcu;								// mcuƽ̨����discription�������ֶ� [pengguofeng 7/15/2013]
	u32 m_dwMaxGuid;                           //��¼��ǰ����guid��guid�Ĺ�����һֱ��������ȡһ����guid��ʱ�򣬶�m_dwMaxGuid+1��Ȼ���������û���guid�Ƚ�û����ͬ����ɹ��������ټ�һ�ٱȽ�

public:
	CUserFullInfo m_usrCurLogin; //��ǰ��¼���û�
	//init and quit 
private:
	void	Reset(); //��������û�,��������Ա
protected:
	BOOL32 WriteAllUserBackToFile();//�����û���Ϣд���ļ�
	// lang [pengguofeng 4/22/2013]
	void SetPlatEncoding( const u8 &byEncoding = ENCODE_GBK); //����ƽ̨���뷽ʽ
	u8   GetPlatEncoding(void);
	void SetFileEncoding(const u8 &byEncoding = ENCODE_GBK);
	u8   GetFileEncoding(void);
	void SetEmTypeNum(const u8 &byEmTypeNum);
	u8   GetEmTypeNum();
	void WriteUserInfo(FILE *fp);   //���û���Ϣд���ļ������ýӿ�
	void ReadUserInfo(FILE *fp);    //���ļ��н����û���Ϣ�����ýӿ�
	u32  GetBufLen();
	u32  GetHeadLen();
	void TransEncoding(); // ת�� [pengguofeng 4/22/2013],�����������������Ҫ��������Ա��

	void UmPrint(s8 *pszFmt, ...);
	//operate
public:	
    void SetSingle(BOOL32 bSingle); //�Ƿ��û�

    BOOL32 GetAllUserFromFile();	//���ļ��ж��������û���Ϣ

    s32 GetUserNum(){return m_byUsrNum;}
    //��ȡ��nIndex�û���Ϣ�� nIndex��0��ʼ
    BOOL32 GetUserFullInfo(CUserFullInfo* pcUserInfo, s32 nIndex);

/*=============================================================================
�� �� ���� AddUser 
��    �ܣ� ����û���¼����֤��ӵļ�¼��Ψһ�Ժͼ�¼���ݵĺϷ���
��    ���� newusr���¼�����û���¼
�� �� ֵ�� ��ӵļ�¼���¼�����еļ�¼�������ظ�&&��¼���ݺϷ�&&��������&&����Ȩ������
           ��TRUE�������ɴ��û���guid����
           ����FALSE
=============================================================================*/
	BOOL32 AddUser(CUserFullInfo* pcNewusr); 

/*=============================================================================
�� �� ���� DelUser
��    �ܣ� ɾ��һ���û���¼
��    ���� oldinfo����ɾ���ļ�¼
�� �� ֵ�� ��¼����&&����Ȩ������&&�û�����Ϊadmin��TURE
           ����FALSE
=============================================================================*/
	BOOL32 DelUser(CUserFullInfo* pcOldinfo);//ɾ��һ���û�

/*=============================================================================
�� �� ���� DelAllMembers
��    �ܣ� �����ݺ��ļ���ɾ�����е��û���¼��admin�û����ᱻɾ����
��    ���� ��
�� �� ֵ�� ����Ȩ������:TRUE;����FALSE
=============================================================================*/
	BOOL32 DelAllMembers();//ɾ�������û�

/*=============================================================================
�� �� ���� ModifyInfo
��    �ܣ� �޸ļ�¼��Ϣ����¼�������޸ģ���Ҫ�޸ļ�¼����Ҫ����ɾ��Ȼ���ٴ���
��    ���� newinfo ���޸ĵļ�¼��Ϣ
�� �� ֵ�� ��¼����&&�����û���Ϊadmin�ļ�¼&&����Ȩ������
           ��TRUE
		   ����FALSE
ע	  �⣺ ������Ψһ�Լ�飬���ֺ�guid����Ӧ�Ż����
=============================================================================*/
	BOOL32 ModifyInfo(CUserFullInfo* pcNewinfo);

	BOOL32 CheckLoginValid(CLoginRequest* pcCurusr);//��鵱ǰ��¼�û���Ϣ

/*=============================================================================
�� �� ���� GetAllUser 
��    �ܣ� ��ȡ�����û���Ϣ���������߷��������û���Ϣ�б�ÿ����Ӧ��response����Ϣ�����
           15���û���Ϣ��¼���������ֲ��ö�λ�Ӧ�ķ���
��    ���� pcMsg ����ȡ�û���Ϣ��������Ϣ
�� �� ֵ�� TRUE
=============================================================================*/
	BOOL32 GetAllUser(CMessage* pcMsg); //�õ������û���Ϣ

/*=============================================================================
�� �� ���� CmdLine
��    �ܣ� ��ʾ�汾������ʾ�����û���Ϣ�б�
��    ���� cmdcode������ģʽ
�� �� ֵ�� ��
=============================================================================*/
	void CmdLine(int nCmdcode); //������ʾ��Ϣ

/*=============================================================================
�� �� ���� SetPath
��    �ܣ� ���õ�ַ����װ�غʹ洢���ļ�����ǰ��ַ���������û���¼���ȶ��������Ȼ���ٴ�
           acFilePath�ļ��ж����µ��û����ݣ��Ժ���û���¼��������Ը��ļ�
��    ���� acFilePath������ʹ洢�û���¼���ļ��� 
�� �� ֵ�� ��
=============================================================================*/
	void SetPath(char* pchFilePath); //���ñ����ļ�·��

	u16 GetLastError() //��ǰ�����Ĵ�����
	{
		return (u16)m_dwError;
	}
	void TestDelAllUser(); //���ɲ���ɾ�������û�

	// ���ļ��Ĺ̶���Ϣ [pengguofeng 5/9/2013]
	void ReadFile();  //�ļ��ӳ�Ա��������
	BOOL32 IsMatchFileHead(FILE *fp, const s8 *pFileHead = NULL);
	void WriteFileHead(FILE *fp, const s8 *pFileHead = NULL);
	BOOL32 IsMatchSoftVer(FILE *fp, const u32 &dwVer = 0);
	void WriteSoftVer(FILE *fp, const u32 &dwVer = 0);
	void ReadFileAttr(FILE *fp);
	void WriteFileAttr(FILE *fp);
	void SkipUnknownType(FILE *fp);

	u32 CreateNewUserGuid(); //�����µ��û�guid
	void UpdateMaxGuid();
	//message
private:
	void OnLigIn(CMessage* pcMsg);
	void OnAddUser(CMessage* pcMsg);
	void OnDelUser(CMessage* pcMsg);
	void OnModifyInfo(CMessage* pcMsg);
	void OnGetAllMembers(CMessage* pcMsg);
	void DisplayMenu();
	void OnDelAllMembers(CMessage* pcMsg);
	
	//interface
public:
	void ShowAll();//���������û���Ϣ
	void ProcessMsg(CMessage* pcMsg);
	void TransferToOldFile(void); // ת���汾�ӿ� [pengguofeng 4/24/2013]
}
#ifdef _VXWORKS_
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
;

PROTO_API BOOL32 InitUserManage();

#endif
