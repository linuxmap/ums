/*****************************************************************************
�ļ���      : dbinterface.h
����ļ�    : kdvtype.h
�ļ�ʵ�ֹ���: ���ݿ���ʽӿ�              
����        : ֣��
ģ��汾    : V1.0  Copyright(C) 2002-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
��  ��(y/m/d)      �ļ��汾        ������      �޸�����
2006/07/17          1.0             ֣��         ����
******************************************************************************/

#ifndef _DB_INTERFACE_H
#define _DB_INTERFACE_H

#ifdef _MSC_VER
#include <winsock2.h>	
#include <wtypes.h>	
#endif

#ifndef NULL
#define NULL   0
#endif

#include "kdvtype.h"

//���ݿ����ͺ궨��
#define DBTYPE_SYBASE     1   //sybase���ݿ�
#define DBTYPE_MYSQL      2	  //mysql ���ݿ�
#define DBTYPE_ORACLE     3   //oracle���ݿ�

#define MAX_RECORDCOL_NUM     64   //Table�������
#define MAX_COLDATA_WIDTH     2048  //����������ֽ���(�����ƴ����image,BLOB)
#define MAX_DB_CONNECTIONS    512  //���������

//�����鶨��
#define DB_LANG_ENGLISH    "us_english"
#define DB_LANG_CHINESE    "chinese"
#define DB_LANG_TCHINESE   "tchinese"  //��������

//�ַ�������
#define DB_CHARSET_ISO1       "iso_1"
#define DB_CHARSET_CP850      "cp850"
#define DB_CHARSET_EUCGB      "eucgb"
#define DB_CHARSET_GB18030    "gb18030"
#define DB_CHARSET_UTF8       "utf8"
#define DB_CHARSET_BIG5       "big5"   //���������ַ���

typedef enum
{
    EOpCode_FindRs, //�����µļ�¼��
	EOpCode_BindDataErr, //������ʧ��
    EOpCode_CmdErr,   //������ִ��ʧ��
    EOpCode_Finish, //������Ѵ������
    EOpCode_OtherErr  //��������
}EOpCode;

typedef enum
{
	ERR_DBCB_CHANNEL_INVALID = 0,  //��Ч����
	ERR_DBCB_OPERATION_TIMEOUT,  //������ʱ
	ERR_DBCB_UNKNOWN      //δ֪����
}EDBCbErr;

//�ص���������������˻ص��Ϳͻ��˻ص�
typedef void (*DBCbFunc) (u16 wErrNum, LPCSTR lpSrvMsg, void *pContext);

//ȫ�ֺ�������ʼ��ϵͳ�����������Ľṹ
//������Ҫ���ʵ����ݿ�����(Ŀǰ֧��sybase��mysql)
//�ɹ�����true,ʧ�ܷ���false
//ע�⣺�˺����������κ����ݿ���󱻴���֮ǰ����
BOOL32 DBInit(u8 byDBType = DBTYPE_SYBASE);

//ȫ�ֺ��������ñ��������飬�ַ���(���sybase���ݿ�)
//������lpLang ������, lpCharSet �ַ���
//�ɹ�����true��ʧ�ܷ���false
BOOL32 SetDBLocale(LPCSTR lpLang, LPCSTR lpCharSet);

//ȫ�ֺ�������װCS_Lib��Ϣ���������������������Ч(sybase���ݿ�)
//������Fuction ���������
//�ɹ�����true��ʧ�ܷ���false
BOOL32 SetupLibErrFuc(DBCbFunc CbFunc, void *pContext = NULL);

//ȫ�ֺ��������ò�����ʱʱ��
BOOL32 SetDBTimeOut(u8 bySec);

//ȫ�ֺ�������ȡBuf���ַ�����
LPCSTR DBGetStrFromBuf(const void *pBuf, u16 wBufLen, LPSTR lpStr, u16 wStrInLen);

//ȫ�ֺ������˳�ϵͳ
//�ɹ�����true,ʧ�ܷ���false
BOOL32 DBExit();

class CDBRs;
class CDBHandlerImp;
class CDBHandler
{
// Constructors/Destruction
public:
    CDBHandler();
    ~CDBHandler();

public:
/*====================================================================
������      : ConnecttoSrv
����        : ���������ݿ������������
�������˵��: szUsrName ��½�û���
              szPwd ����
			  szDBName ���ݿ���
              szSrvIP ���ݿ��������ַ(�ַ���IP)
              wPort �˿�
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 ConnecttoSrv(LPCSTR szUsrName,
                      LPCSTR szPwd,
					  LPCSTR szDBName,
                      LPCSTR szSrvIP,
                      u16 wPort = 5000);

/*====================================================================
������      : CloseConnection
����        : �Ͽ������ݿ������������
�������˵��: ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 CloseConnection();

/*====================================================================
������      : SetupCtErrFuc(sybase,mysql���ݿⶼ��Ч)
����        : ��װ�ͻ��˴�����Ϣ������
�������˵��: Function �������ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 SetupCtErrFuc(DBCbFunc CbFunc, void *pContext = NULL);

/*====================================================================
������      : SetupSrvErrFuc(sybase���ݿ���Ч)
����        : ��װ�������˴�����Ϣ������
�������˵��: Function �������ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 SetupSrvErrFuc(DBCbFunc CbFunc, void *pContext = NULL);

/*====================================================================
������      : RemoveCallBack(sybase���ݿ���Ч)
����        : �Ƴ��������ϵĻص���Ϣ
�������˵��: ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    void RemoveCallBack();
	
/*====================================================================
������      : UseDB
����        : ���ƶ����ݿ�
�������˵��: szDBNameĿ�����ݿ���
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 UseDB(LPCSTR szDBName);

/*====================================================================
������      : ExecSql
����        : ִ��������sql���
�������˵��: szsql sql�ִ�
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 ExecSql(LPCSTR szsql);

/*====================================================================
������      : ExecSql
����        : ִ���м�¼�����ص�sql���
�������˵��: szsql sql�ִ�
              pcRecordSet ���ؽ����ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 ExecSql(LPCSTR szsql, CDBRs *pcRecordSet);

// /*====================================================================
// ������      : OpenCursor
// ����        : ���α����
// �������˵��: lpCursorSql ���α�������Ĳ�ѯ���
//               pcRecordSet �α귵�صļ�¼��ָ��
// ����ֵ˵��  : �ɹ�true,ʧ��false
// ====================================================================*/    
// 	BOOL32 OpenCursor(LPCSTR lpCursorSql, CDBRs *pcRecordSet);
// 
// /*====================================================================
// ������      : UpdateCurRow
// ����        : �����α굱ǰ��
// �������˵��: lpUpdateSql ���µ�ǰ�е�sql���
// 			  lpTableName ���α�������ı��� 
// ����ֵ˵��  : �ɹ�true,ʧ��false
// ====================================================================*/    
// 	BOOL32 UpdateCurRow(LPCSTR lpUpdateSql, LPCSTR lpTableName);
// 
// /*====================================================================
// ������      : DelCurRow
// ����        : ɾ���α굱ǰ��
// �������˵��: lpUpdateSql ���µ�ǰ�е�sql���
// 			  lpTableName ���α�������ı���
// 			  �ر�ע��: ���α��漰�����ʱ��ɾ����ʧ��
// ����ֵ˵��  : �ɹ�true,ʧ��false
// ====================================================================*/    
// 	BOOL32 DelCurRow(LPCSTR lpTableName);
	
/*====================================================================
������      : InsertBuf(sybase���ݿ���Ч)
����        : �����û��Զ���ķǽṹ�����ݵ����ݿ����
�������˵��: lpszSql ��ȡҳָ���Sql���
		      pcRecordSet ��ȡ����ָ��ʱʹ��
			  pBuf  ���ݿ��׵�ַ
              wBufLen ���ݿ鳤��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 InsertBuf(LPCSTR lpszSql, CDBRs *pcRecordSet, const void *pBuf, u16 wBufLen);
	
/*====================================================================
������      : GoOnProcRes
����        : ������������(�����ڴ�������¼������)
�������˵��: ��
����ֵ˵��  : EOpCode_FindRs �����µļ�¼��
              EOpCode_Finish ������Ѵ������
			  EOpCode_BindDataErr ���ݰʧ��
              EOpCode_CmdErr ����ĳ������ִ��ʧ��
====================================================================*/    
    EOpCode GoOnProcRes(); 

/*====================================================================
������      : GetAffectedRowCount
����        : ��ȡ�����������õļ�¼����
�������˵��: ��
����ֵ˵��  : ��¼����
====================================================================*/    
	u32 GetAffectedRowCount();

protected:
	CDBHandlerImp *m_pcDBHandlerImp;
};

class CDBRsImp;
class CDBRs
{
// Constructors/Destruction
public:
    CDBRs();
    ~CDBRs();

public:    
/*====================================================================
������      : MoveNext
����        : ��ָ��ָ��������һ����¼
�������˵��: ��
����ֵ˵��  : �ɹ�������ǰ�з���true,���򷵻�false
====================================================================*/    
    BOOL32 MoveNext();

/*====================================================================
������      : IsEof
����        : ��¼���Ƿ񵽴�ĩβ
�������˵��: ��
����ֵ˵��  : ����ĩβ����true,����false
====================================================================*/    
    BOOL32 IsEof();

/*====================================================================
������      : GetFieldCount
����        : ��ȡ���������
�������˵��: ��
����ֵ˵��  : ���������
====================================================================*/    
    const u16 GetFieldCount();

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, double& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, float& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, s32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, u32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, s16& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, u16& Value);
	
/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, s8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, u8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              IN wBufLen �����С
              OUT pstr �����ִ�ֵ
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, LPSTR pstr, u16 wBufLen);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ(�û��Զ������ݿ�)
�������˵��: IN lpColName ����
              IN wBufLen �����С
              OUT pBuf �����׵�ַ
			  OUT wOutLen ʵ��ȡ�����ݿ�Ĵ�С
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(LPCSTR lpColName, void *pBuf, u16 wBufLen, u16 &wOutLen);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, double& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, float& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, s32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, u32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, s16& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, u16& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, s8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, u8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              IN wBufLen �����С
              OUT pstr �����ִ�ֵ
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, LPSTR pstr, u16 wBufLen);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ(�û��Զ������ݿ�)
�������˵��: IN wIndex ������
              IN wBufLen �����С
              OUT pBuf �����׵�ַ
			  OUT wOutLen ʵ��ȡ�����ݿ�Ĵ�С
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    BOOL32 GetFieldValue(u8 byIndex, void *pBuf, u16 wBufLen, u16 &wOutLen);

	CDBRsImp* GetRsImp();

protected:
	CDBRsImp *m_pcDBRsImp;
};

#endif
