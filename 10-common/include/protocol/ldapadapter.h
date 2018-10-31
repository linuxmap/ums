/*****************************************************************************
ģ����      : LdapAdapterLib
�ļ���      : ldapAdapter.h
����ļ�    : 
�ļ�ʵ�ֹ���: LDAP����⹫������,�ṹ��API�ӿڶ���
����        : ���Ҿ�
�汾        : V1.0  Copyright(C) 2004-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007-01-17  1.0         ���Ҿ�      ����
******************************************************************************/
#ifndef __LDAPADAPTER_H
#define __LDAPADAPTER_H

#include "osp.h"
////////////////////////////////// �궨�� ////////////////////////////////
//�汾��
#define VER_LDAPADAPTER "KDV LdapAdapter 40.01.01.00.01.070125"
#define LA_DEFAULT_SERVER_PORT      (u16)389   //Ŀ¼������Ĭ�ϼ����˿�


#define LA_LEN_DEVID           (u8)32           //�豸��ų���
#define LA_LEN_MAX_CALLNUM     (u8)16           //���к�����󳤶�
#define LA_LEN_MAX_NICKNAME    (u8)64           //�豸�ǳ���󳤶�


//LDAP�����������
#define LA_SUCCESS             (u32)0              //�ɹ�
#define LA_OPERATION_FAILED    (u32)400            //����ʧ�ܡ�ͨ�õĴ������
#define LA_CONNECT_ERROR       (u32)401            //�������޷����ӻ����
#define LA_ENTRY_NOT_EXIST     (u32)402            //���ҵ���Ŀ������
#define LA_AUTH_NEEDED         (u32)403            //Ȩ�޲���
#define LA_PARAM_ERROR         (u32)404            //��Ч������API���ò���
#define LA_CANNOT_ALLOC_MEM    (u32)405            //�������޷������ڴ�

//������LDAPЭ��ջ������룬������ʱ�á�ҵ��㲻�ع��ġ�
/*
0 - LDAP_SUCCESS 
1- LDAP_OPERATIONS_ERROR 
2 - LDAP_PROTOCOL_ERROR 
3 - LDAP_TIMELIMIT_EXCEEDED 
4 - LDAP_SIZELIMIT_EXCEEDED 
5 - LDAP_COMPARE_FALSE 
6 - LDAP_COMPARE_TRUE 
7 - LDAP_STRONG_AUTH_NOT_SUPPORTED 
8 - LDAP_STRONG_AUTH_REQUIRED 
9 - LDAP_PARTIAL_RESULTS 
10 - LDAP_REFERRAL 
11 - LDAP_ADMINLIMIT_EXCEEDED 
12 - LDAP_UNAVAILABLE_CRITICAL_EXTENSION 
13 - LDAP_CONFIDENTIALITY_REQUIRED 
14 - LDAP_SASL_BIND_IN_PROGRESS 
15 - LDAP_NO_SUCH_ATTRIBUTE 
17 - LDAP_UNDEFINED_TYPE 
18 - LDAP_INAPPROPRIATE_MATCHING 
19 - LDAP_CONSTRAINT_VIOLATION 
20 - LDAP_TYPE_OR_VALUE_EXISTS 
21 - LDAP_INVALID_SYNTAX 
32 - LDAP_NO_SUCH_OBJECT 
33 - LDAP_ALIAS_PROBLEM 
34 - LDAP_INVALID_DN_SYNTAX 
35 - LDAP_IS_LEAF 
36 - LDAP_ALIAS_DEREF_PROBLEM 
48 - LDAP_INAPPROPRIATE_AUTH 
49 - LDAP_INVALID_CREDENTIALS 
50 - LDAP_INSUFFICIENT_ACCESS 
51 - LDAP_BUSY 
52 - LDAP_UNAVAILABLE 
53- LDAP_UNWILLING_TO_PERFORM 
54 - LDAP_LOOP_DETECT 
60 - LDAP_SORT_CONTROL_MISSING 
61 - LDAP_INDEX_RANGE_ERROR 
64 - LDAP_NAMING_VIOLATION 
65 - LDAP_OBJECT_CLASS_VIOLATION 
66 - LDAP_NOT_ALLOWED_ON_NONLEAF 
67 - LDAP_NOT_ALLOWED_ON_RDN 
68 - LDAP_ALREADY_EXISTS 
69 - LDAP_NO_OBJECT_CLASS_MODS 
70 - LDAP_RESULTS_TOO_LARGE 
71 - LDAP_AFFECTS_MULTIPLE_DSAS 
80- LDAP_OTHER 
81 - LDAP_SERVER_DOWN 
82 - LDAP_LOCAL_ERROR 
83 - LDAP_ENCODING_ERROR 
84 - LDAP_DECODING_ERROR 
85 - LDAP_TIMEOUT 
86 - LDAP_AUTH_UNKNOWN 
87 - LDAP_FILTER_ERROR 
88 - LDAP_USER_CANCELLED 
89 - LDAP_PARAM_ERROR 
90 - LDAP_NO_MEMORY 
91 - LDAP_CONNECT_ERROR 
92 - LDAP_NOT_SUPPORTED 
93 - LDAP_CONTROL_NOT_FOUND 
94 - LDAP_NO_RESULTS_RETURNED 
95 - LDAP_MORE_RESULTS_TO_RETURN 
96 - LDAP_CLIENT_LOOP 
97 - LDAP_REFERRAL_LIMIT_EXCEEDED 
*/

//�ص���Ϣ���ʹ���
#define LA_EV_AUTH_RSP                (u32)100          //��֤��Ӧ
#define LA_EV_REG_RSP                 (u32)101          //ע����Ӧ
#define LA_EV_SEARCH_BY_CALLNUM_RSP   (u32)102          //�����к����ѯ������Ŀ��Ӧ
#define LA_EV_GET_LIST_RSP            (u32)103          //��ȡ��Ŀ�б���Ӧ
#define LA_EV_UNREG_RSP               (u32)104          //ע����Ӧ
#define LA_EV_DISCON_NT               (u32)105          //����֪ͨ 
#define LA_EV_CONNECT_NT              (u32)106          //Ŀ¼���������ӳɹ�
#define LA_EV_MAX_RETRY_REACHED_NT    (u32)107          //�ﵽ�������������Ȼ�޷�����



//�豸���ͳ���
enum ELADevType
{
    emldapdev_8220C =   (u8)1,  
    emldapdev_PCMT_LITE  = (u8)2,
    emldapdev_OTHER = (u8)255, 
};

//NAT���ͳ���
enum ELANatType
{ 
    emnattype_DEFAULT = (u8)1,  
    emnattype_OTHER = (u8)255, 
};
//////////////////////////////// �ṹ���� //////////////////////////////

//�豸��Žṹ
typedef struct tagDeviceID
{
    u8   m_abyDevId[LA_LEN_DEVID];   // 32λ�����ַ���

	tagDeviceID()
	{
		memset(m_abyDevId,0,sizeof(m_abyDevId));
	}

	BOOL SetDevId(u8 *pbyBuf,u8 byBufLen)
	{
		if((NULL == pbyBuf)||(byBufLen > LA_LEN_DEVID))
		{
			return FALSE;			
		}
		else
		{
			memcpy(m_abyDevId,pbyBuf,byBufLen);
			return TRUE;
		}
	}

	u8 GetDevId(u8 *pbyBuf, u8 byBufLen)
	{
		if((NULL == pbyBuf)||(byBufLen < LA_LEN_DEVID))
		{
			return 0;
		}
		else
		{
			memcpy(pbyBuf,m_abyDevId,LA_LEN_DEVID);
			return LA_LEN_DEVID;
		}
	}

	u8 GetDevLen()
	{
		return (u8)LA_LEN_DEVID;
	}	
	
}TDevId;

//���к���ṹ
typedef struct tagDialNumber
{    
    u8  m_abyDialNum[LA_LEN_MAX_CALLNUM];   // �䳤�ַ���������'\0'��ʾ����
	u8  m_byLen;                            // ���к��볤��

	tagDialNumber()
	{
		m_byLen = 0;
		memset(m_abyDialNum,0,sizeof(m_abyDialNum));
	}

	BOOL SetDialNum(u8* pbyBuf,u8 byBufLen)
	{
		if((NULL == pbyBuf)||(byBufLen > LA_LEN_MAX_CALLNUM))
		{
			return FALSE;
		}
		else
		{
			memcpy(m_abyDialNum,pbyBuf,byBufLen);
			m_byLen = byBufLen;
			return TRUE;
		}
	}

	u8 GetDialNum(u8* pbyBuf, u8 byBufLen)
	{
		if((NULL == pbyBuf)||(byBufLen < m_byLen))
		{
			return 0;
		}
		else
		{
			memcpy(pbyBuf,m_abyDialNum,byBufLen);			
			return m_byLen;
		}		
	}
	
	u8 GetDialNumLen()
	{
		return m_byLen;
	}
}TDialNum;

//�豸�ǳƽṹ
typedef struct tagTermNickName
{
	u8  m_byLen;                                   // ����
    u8  m_abyNickName[LA_LEN_MAX_NICKNAME];        // �ǳơ��䳤�ַ��������� \0 ������  

	tagTermNickName()
	{
		m_byLen = 0;
		memset(m_abyNickName,0,sizeof(m_abyNickName));
	}

	BOOL SetNickName(u8* pbyBuf,u8 byBufLen)
	{
		if((NULL == pbyBuf)||(byBufLen > LA_LEN_MAX_NICKNAME))
		{
			return FALSE;
		}
		else
		{
			memcpy(m_abyNickName,pbyBuf,byBufLen);
			m_byLen = byBufLen;
			return TRUE;
		}
	}

	u8 GetNickName(u8* pbyBuf, u8 byBufLen)
	{
		if((NULL == pbyBuf)||(byBufLen < m_byLen))
		{
			return 0;
		}
		else
		{
			memcpy(pbyBuf,m_abyNickName,byBufLen);			
			return m_byLen;
		}		
	}
	
	u8 GetNickNameLen()
	{
		return m_byLen;
	}
	
}TTermNickName;

// �ն���֤��Ϣ
typedef struct tagTermAuthInfo
{
    TDevId    m_tDevId;           // �豸���    
    TDialNum  m_tDialNum;         // ���к���
	u8        m_byDevType;        //�豸����

	tagTermAuthInfo()
	{
		m_byDevType = emldapdev_8220C;		
	}

	BOOL SetDevId(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tDevId.SetDevId(pbyBuf,byBufLen);
	}

	BOOL SetDialNum(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tDialNum.SetDialNum(pbyBuf,byBufLen);
	}

	void  SetDevType(u8 byDevType)
	{
		m_byDevType = byDevType;
	}

	u8 GetDevId(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tDevId.GetDevId(pbyBuf,byBufLen);
	}
	u8 GetDevIdLen()
	{
		return m_tDevId.GetDevLen();
	}
	u8 GetDialNum(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tDialNum.GetDialNum(pbyBuf,byBufLen);
	}
	u8 GetDialNumLen()
	{
		return m_tDialNum.GetDialNumLen();
	}
	u8 GetDevType()
	{
		return m_byDevType;
	}
}TTermAuthInfo;

// �ն�ע����Ϣ
typedef struct tagTermRegistInfo
{
    TTermNickName   m_tNickName;   // Nick name 
	TDialNum        m_tDialNum;    // ���к���
	u32             m_dwIpAddr;    //IP Addr
	u16             m_wH245Port;   //H245 ��������˿�
	u8              m_byNATType;   // NAT ����

	tagTermRegistInfo()
	{
		m_dwIpAddr = 0;
		m_wH245Port = htons(1720);
		m_byNATType = emnattype_DEFAULT;
	}

	BOOL SetNickName(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tNickName.SetNickName(pbyBuf,byBufLen);
	}

	BOOL SetDialNum(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tDialNum.SetDialNum(pbyBuf,byBufLen);
	}

	void SetIPAddr(u32 dwIP)
	{
		m_dwIpAddr = htonl(dwIP);		
	}

	void SetH245Port(u16 wH245Port)
	{
		m_wH245Port = htons(wH245Port);
	}

	void SetNatType(u8 byNatType)
	{
		m_byNATType = byNatType;
	}

	u8 GetNickNum(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tNickName.GetNickName(pbyBuf,byBufLen);
	}
	u8 GetNickNameLen()
	{
		return m_tNickName.GetNickNameLen();
	}
	
	u8 GetDialNum(u8 *pbyBuf, u8 byBufLen)
	{
		return m_tDialNum.GetDialNum(pbyBuf,byBufLen);
	}
	u8 GetDialNumLen()
	{
		return m_tDialNum.GetDialNumLen();
	}

	u32 GetIPAddr()
	{
		return ntohl(m_dwIpAddr);
	}

	u16 GetH245Port()
	{
		return ntohs(m_wH245Port);
	}

	u8 GetNatType()
	{
		return m_byNATType;
	}

}TTermRegInfo;

//��֤��Ӧ�ṹ
typedef struct tagLaAuthRsp
{
	u32 m_dwRetCode;   //������
	
	tagLaAuthRsp()
	{
		m_dwRetCode = LA_SUCCESS;
	}

	void SetRspCode(u32 dwRetCode)
	{
		m_dwRetCode = dwRetCode;
	}
	
	u32 GetRspCode()
	{
		return m_dwRetCode;
	}
	
}TLaAuthRsp;


//ע����Ӧ�ṹ
typedef struct tagLaRegRsp
{
	u32 m_dwRetCode;  //������
	
	tagLaRegRsp()
	{
		m_dwRetCode = LA_SUCCESS;
	}

	void SetRspCode(u32 dwRetCode)
	{
		m_dwRetCode = dwRetCode;
	}

	u32 GetRspCode()
	{
		return m_dwRetCode;
	}

}TLaRegRsp;

//���ҵ���ʵ����Ӧ�ṹ
typedef struct tagLaSearchRsp
{
	u32 m_dwRetCode;             //������
	u32 m_dwReqSq;              //��Ӧ�������������к�
	TTermRegInfo m_tRetEntry;   //��ȡ��ʵ��

	tagLaSearchRsp()
	{
		m_dwReqSq = 0;
		m_dwRetCode = LA_SUCCESS;
	}
	void SetRspCode(u32 dwRetCode)
	{
		m_dwRetCode = dwRetCode;
	}
	void SetReqSequece(u32 dwSequence)
	{
		m_dwReqSq = dwSequence;
	}
	u32 GetRspCode()
	{
		return m_dwRetCode;
	}
	u32 GetReqSequence()
	{
		return m_dwReqSq;
	}
}TLaSearchRsp;

//ע����Ӧ�ṹ
typedef struct tagLaUnregRsp
{
	u32 m_dwRetCode;	 //������
	tagLaUnregRsp()
	{
		m_dwRetCode = LA_SUCCESS;
	}
	void SetRspCode(u32 dwRetCode)
	{
		m_dwRetCode = dwRetCode;
	}
	u32 GetRspCode()
	{
		return m_dwRetCode;
	}
}TLaUnregRsp;


//�ص������ṹ����
//�������������ǣ��ص�����/�ص����ݳ���/�ص�����ָ��
typedef  void (*LDAPCB) (u32 dwEventId, u32 dwContLen, void* pContent);


//////////////////////////////// �ӿں���//////////////////////////
/*====================================================================
�������� InitLdapAdapter
���ܣ�   ��ʼ��LDAP�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����          
����ֵ˵�����ɹ�����0��ʧ�ܷ��ط���ֵ
====================================================================*/
BOOL32  InitLdapAdapter();  


/*====================================================================
�������� SetLdapParam
���ܣ�   ����LDAP���Ӳ�����ҵ�����ظ����ô˺������Բ�ѯ��ͬ��LDAP��������
����ȫ�ֱ�����
�������˵����
           pchHost      ������ x.x.x.x ��ʽ���������ơ�
           wPort        Ŀ¼�����������˿�.Ĭ��Ϊ389    
����ֵ˵�����ɹ�����TRUE�����򷵻�FALSE
====================================================================*/
BOOL32 SetLdapParam(const s8* pchHost, u16 wPor = LA_DEFAULT_SERVER_PORT);


/*====================================================================
��������  SetAdapterCallBack
���ܣ�    ���ûص�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          pfCBFunction �ص�����ָ��
����ֵ˵�����ɹ�����TRUE�����򷵻�FALSE
====================================================================*/
BOOL32 SetAdapterCallBack(LDAPCB pfCBFunction);


/*====================================================================
��������  SendAuthReq
���ܣ�    ������֤����.�����ն˲�����ô˽ӿڡ�
          û��ͨ����֤����û�е�����֤������ն˽�ֻ�ܽ��в�ѯ������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          ptAuthInfo ��֤��Ϣָ��
����ֵ˵�����ɹ�����TRUE�����򷵻�FALSE
====================================================================*/
BOOL32  SendAuthReq(TTermAuthInfo* ptAuthInfo);


/*====================================================================
��������  SendRegReq
���ܣ�    ����ע������.�����ն˲�����ô˽ӿڡ�
          �����Ŀ�Ѵ��ڣ��������²�����ҵ��㲻��Ҫ��֪�ǳ���ע�ỹ�Ǹ���ע�ᡣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          ptRegInfo ע����Ϣָ��
����ֵ˵�����ɹ�����0��ʧ�ܷ��ط���ֵ
====================================================================*/
BOOL32  SendRegReq(TTermRegInfo *ptRegInfo);


/*====================================================================
��������  RearchByCallNum
���ܣ�    �����к����ѯ�ն���Ϣ��
          ҵ����ṩ�������кţ���֧�ֶ����ѯ�ص�.
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          dwSequence  �������к�
          ptCallNum   ���к���ָ��
����ֵ˵�����ɹ�����0��ʧ�ܷ��ط���ֵ
====================================================================*/
BOOL32  SearchByCallNum(u32 dwSequece, TDialNum *ptCallNum);



/*====================================================================
��������  SendUnRegReg
���ܣ�    ����ע������.�����ն˲�����ô˽ӿڡ�          
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
          ptRegInfo ע����Ϣָ��
����ֵ˵�����ɹ�����0��ʧ�ܷ��ط���ֵ
====================================================================*/
BOOL32 SendUnRegReg(TTermRegInfo *ptUnRegInfo);



/*====================================================================
��������  UnitLdapAdapter
���ܣ�    �˳�LDAP����⡣          
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
����ֵ˵�����ɹ�����0��ʧ�ܷ��ط���ֵ
====================================================================*/
BOOL32 UnitLdapAdapter();






#endif //__LDAPADAPTER_H
