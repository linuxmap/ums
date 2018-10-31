#ifndef _MESSAGESTRUCT_H_
#define _MESSAGESTRUCT_H_

#include "umconst.h"
#include "osp.h"
#include "md5.h"
#include "protocolcommonpublic.h"

#ifdef WIN32
    #pragma pack( push )
    #pragma pack( 1 )
#endif
API void umver();
class CLoginRequest
{
private:
	char		m_achname[MAX_CHARLENGTH + 1]; //�û���
	char		m_achpassword[MAX_CHARLENGTH + 1];//����
	CMD5Encrypt m_cMd5;
public:
	CLoginRequest()
	{
		memset(m_achname,0,MAX_CHARLENGTH + 1 );
		memset(m_achpassword,0,MAX_CHARLENGTH + 1 );
	}
	//���ú͵õ��û���
	char* GetName()
	{
		return m_achname;
	}
	void  SetName(char* pchbuf)
	{
		if(pchbuf == NULL)
		{
			return;
		}
		memset(m_achname,0,MAX_CHARLENGTH + 1);
		int nlength = (strlen(pchbuf) >= MAX_CHARLENGTH ? MAX_CHARLENGTH: strlen(pchbuf));
		memcpy(m_achname,pchbuf,nlength);
		m_achname[nlength] = '\0';
	};
	//���ú͵õ�����
	char* GetPassword()
	{
		return m_achpassword;
	}
	//��������Ϊ����
	void  SetPassword(char* pchbuf)
	{
		
		m_cMd5.GetEncrypted(pchbuf,m_achpassword);
		m_achpassword[MAX_CHARLENGTH]='\0';
	}
	//����������Ѿ�������
	void SetEncryptedPassword(char* pchbuf)
	{
		if(pchbuf == NULL)
		{
			return;
		}
		memset(m_achpassword,0,MAX_CHARLENGTH + 1);
		int nlength = (strlen(pchbuf) >= MAX_CHARLENGTH ? MAX_CHARLENGTH: strlen(pchbuf));
		memcpy(m_achpassword,pchbuf,nlength);
		m_achpassword[nlength]='\0';
	}
	void Empty()
	{
		memset(m_achname,0,MAX_CHARLENGTH+1);
		memset(m_achpassword,0,MAX_CHARLENGTH+1);
	}
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
;

class PROTO_API CUserFullInfo
{
// private:
public: // ��������Ա��С [pengguofeng 5/9/2013]
	CMD5Encrypt m_cMd5;
public:
	u32         m_dwGuid;	//ÿ������Ψһ��Ӧһ��guid
	char		m_achname[MAX_CHARLENGTH+1]; //�û���
	char		m_achpassword[MAX_CHARLENGTH+1];//����
	u8			m_byActor;//Ȩ��
	char		m_achfullname[MAX_CHARLENGTH+1];//�����û���
	char		m_achdiscription[2*MAX_CHARLENGTH+1];//�û�����
public:
	CUserFullInfo()
	{
		Empty();
	}
	~CUserFullInfo(){};
	//�õ��û���
	char* GetName()
	{
		m_achname[MAX_CHARLENGTH] = '\0';
		return m_achname;
	}
	//�����û���
	void  SetName(char* pchbuf)
	{
		if(pchbuf == NULL)return;
		memset(m_achname,0,MAX_CHARLENGTH+1);
		int nlength = (strlen(pchbuf) >= MAX_CHARLENGTH ? MAX_CHARLENGTH: strlen(pchbuf));
		memcpy(m_achname,pchbuf,nlength);
		m_achname[nlength] = '\0';
	}
	//�õ�����
	char* GetPassword()
	{
		return m_achpassword;
	}
	//��������
	void  SetPassword(char* pchbuf)
	{
		m_cMd5.GetEncrypted(pchbuf,m_achpassword);
		m_achpassword[MAX_CHARLENGTH]='\0';
	}
	//�Ѿ����ܵ�����
	void  SetEncryptedPassword(char* pchbuf)
	{
		memcpy(m_achpassword,pchbuf,MAX_CHARLENGTH+1);
		m_achpassword[MAX_CHARLENGTH]='\0';
	}
	//�õ��û�������
	char* GetFullName()
	{
		return m_achfullname;
	}
	//�����û�������
	void SetFullName(char* pchbuf)
	{
		if(pchbuf == NULL)return;
		memset(m_achfullname,0,MAX_CHARLENGTH+1);
		int nlength = (strlen(pchbuf) >= MAX_CHARLENGTH ? MAX_CHARLENGTH: strlen(pchbuf));
		memcpy(m_achfullname,pchbuf,nlength);
		m_achfullname[nlength] = '\0';
	}
	//�õ��û�����
	char* GetDiscription()
	{
		return m_achdiscription;
	}
	
	//�����û�����
	void SetDiscription(char* pchbuf)
	{
		if(pchbuf == NULL)return;
		memset(m_achdiscription,0, 2*MAX_CHARLENGTH+1);
		int nlength = (strlen(pchbuf) >= 2*MAX_CHARLENGTH ?  2*MAX_CHARLENGTH: strlen(pchbuf));
		memcpy(m_achdiscription,pchbuf,nlength);
		m_achdiscription[nlength] = '\0';
	}
	//�õ�Ȩ��
	unsigned char   GetActor(){return m_byActor;}
	//����Ȩ��
	void  SetActor(unsigned char byActor){ m_byActor = byActor;}
	//����ֵ
	const CUserFullInfo& operator=(const CUserFullInfo& cNewInfo)
	{
		if (this != &cNewInfo)
		{
			memcpy(this, &cNewInfo, sizeof(CUserFullInfo));
		}
		return *this;
	}

	// ȡ���г�Ա�ĳ��� [pengguofeng 5/14/2013]
	unsigned char GetMemLen( const unsigned char &byMemId )
	{
		u8 byRet = 0;
		switch ( byMemId)
		{
		case 0:
			byRet = sizeof(m_cMd5.context.state);
			break;
		case 1:
			byRet = sizeof(m_cMd5.context.count);
			break;
		case 2:
			byRet = sizeof(m_cMd5.context.buffer);
			break;
		case 3:
			byRet = sizeof(m_achname);
			break;
		case 4:
			byRet = sizeof(m_achpassword);
			break;
		case 5:
			byRet = sizeof(m_byActor);
			break;
		case 6:
			byRet = sizeof(m_achfullname);
			break;
		case 7:
			byRet = sizeof(m_achdiscription);
			break;
		case 8:
			byRet = sizeof(m_dwGuid);
			break;
		case 9:
//			byRet = sizeof(add2);
			break;
		default:
			break;
		}

		return byRet;
	}
	//�ж�ĳһ����Ա�Ƿ�Ϊ�ַ���,0 1 2����MD5����Ϣ�������޸�
	bool IsMemString(const unsigned char &byMemId)
	{
		if ( byMemId == 3
			|| byMemId == 4
			|| byMemId == 6
			|| byMemId == 7
		/*	|| byMemId == 8
			|| byMemId == 9
		*/
			)
		{
			return TRUE;
		}
		return FALSE;
	}
	//�ж��û����Ƿ���ͬ
	bool IsEqualName(char* cNewName)
	{
		if (strlen(m_achname) != strlen(cNewName) || strlen(cNewName) == 0 )
			return FALSE;
		for (unsigned int dwIndex=0 ; dwIndex< strlen(m_achname) ; dwIndex++)
		{
			if (m_achname[dwIndex] != cNewName[dwIndex])
				return FALSE;
		}
		return TRUE;
	}	
	//�жϿ����Ƿ���ͬ
	bool IsPassWordEqual(char* pchNewPass)
	{
		size_t dwLen = strlen( pchNewPass );
		if ( dwLen > strlen(m_achpassword) )
		{
			dwLen = strlen(m_achpassword);
		}
		for (size_t i=0 ; i< dwLen; i++)
		{
			if (m_achpassword[i] != pchNewPass[i])
				return FALSE;
		}
		return TRUE;
	}
	//�ҵ��յ�
	bool IsEmpty()
	{
		if ( strlen(m_achpassword) > 16 )
		      return FALSE;
		return TRUE;
	}
	//���
	void Empty()
	{
		memset(this, 0, sizeof(CUserFullInfo));
		m_byActor = UM_OPERATOR;
	}	

}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
;
class CLongMessage
{
public:
	u8 m_uTotal; //��Ϣ��֡��
	u8 m_uCurr;  //��ǰָ֡ʾ
	u8 m_uNumUsr;//��ǰ֡�е��û���
public:
	CLongMessage()
	{
		Reset();
	}
	~CLongMessage(){};
public:
	void Reset()
	{
		m_uTotal = 0;
		m_uCurr =  0;
		m_uNumUsr = 0;
	}
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
;
#ifdef WIN32
#pragma pack( pop )
#endif
#endif
