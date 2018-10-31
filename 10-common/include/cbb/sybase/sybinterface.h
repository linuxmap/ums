/*****************************************************************************
ģ����      : sybinterface.lib
�ļ���      : sybinterface.h
����ļ�    : sybinterface.cpp
�ļ�ʵ�ֹ���: sybase���ݿ���ʷ�װ              
����        : ֣��
ģ��汾    : V1.0  Copyright(C) 2002-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
��  ��(y/m/d)      �ļ��汾        ������      �޸�����
2006/02/10          1.0             ֣��         ����
******************************************************************************/

#ifndef _SYB_INTERFACE_H
#define _SYB_INTERFACE_H

#ifdef _MSC_VER
#include <winsock2.h>	
#include <wtypes.h>	
#endif

#ifndef NULL
#define NULL   0
#endif

#include "kdvtype.h"
#include "ctpublic.h"

#define MAX_RECORDCOL_NUM  64   //Table�������
#define MAX_COLDATA_WIDTH  513  //����������ֽ���
#define MAX_SYB_CONNECTIONS 512 //���������

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
	ERR_SYBCB_CHANNEL_INVALID = 0,  //��Ч����
	ERR_SYBCB_OPERATION_TIMEOUT,  //������ʱ
	ERR_SYBCB_UNKNOWN      //δ֪����
}ESybCbErr;

typedef void (*SybServerCb) (CS_SERVERMSG *SrvMsg, CS_VOID *pCbData);
typedef void (*SybLocalCb) (CS_CLIENTMSG *CtMsg, CS_VOID *pCbData);

typedef struct 
{
	SybServerCb m_CbFunc;
	CS_VOID *m_CbData;
}TSrvCbInfo;

typedef struct 
{
	SybLocalCb m_CbFunc;
	CS_VOID *m_CbData;
}TCtCbInfo;

//ȫ�ֺ�������ʼ��ϵͳ�����������Ľṹ
//�ɹ�����true,ʧ�ܷ���false
bool SybInit();

//ȫ�ֺ��������ñ��������飬�ַ���
//������lpLan ������, lpCharSet �ַ���
//�ɹ�����true��ʧ�ܷ���false
bool SetDBLocale(LPCSTR lpLang, LPCSTR lpCharSet);

//ȫ�ֺ�������װCS_Lib��Ϣ���������������������Ч
//������Fuction ���������
//�ɹ�����true��ʧ�ܷ���false
bool SetupLibErrFuc(SybLocalCb CbFunc, CS_VOID *pCbData = NULL);

//ȫ�ֺ�������ȡ�ص�������
ESybCbErr GetCTCbErrCode(CS_CLIENTMSG *CtMsg);

//ȫ�ֺ��������ò�����ʱʱ��
bool SetSybTimeOut(u8 bySec);

//ȫ�ֺ�������ȡBuf���ַ�����
LPCSTR SybGetStrFromBuf(const void *pBuf, u16 wBufLen, LPSTR lpStr, u16 wStrInLen);

//ȫ�ֺ������˳�ϵͳ
//�ɹ�����true,ʧ�ܷ���false
bool SybExit();

class CSybConnection
{
// Constructors/Destruction
public:
    CSybConnection();
    ~CSybConnection();

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
    bool ConnecttoSrv(LPCSTR szUsrName,
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
    bool CloseConnection();

/*====================================================================
������      : GetCmd
����        : ��ȡ����ṹָ��
�������˵��: ��
����ֵ˵��  : ����ָ��
====================================================================*/    
    CS_COMMAND* GetCmd();

/*====================================================================
������      : SetupCtErrFuc
����        : ��װ�ͻ��˴�����Ϣ������
�������˵��: Function �������ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool SetupCtErrFuc(SybLocalCb CbFunc, CS_VOID *CbData = NULL);

/*====================================================================
������      : SetupSrvErrFuc
����        : ��װ�������˴�����Ϣ������
�������˵��: Function �������ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool SetupSrvErrFuc(SybServerCb CbFunc, CS_VOID *CbData = NULL);

/*====================================================================
������      : RemoveCallBack
����        : �Ƴ��������ϵĻص���Ϣ
�������˵��: ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    void RemoveCallBack();
	
public:
	BOOL32 m_bIsCurRsEnd;  //��ǰ��¼���Ƿ������
	BOOL32 m_bIsFinish;    //��ǰ�����Ƿ������
	
protected:
    CS_CONNECTION *m_pcConnection;  //CTLib���ӽṹָ��
	CS_COMMAND *m_pcCmd;            //CTLib����ṹָ��
	TSrvCbInfo m_tSrvCbInfo;        //����˻ص���Ϣ
	TCtCbInfo m_tCtCbInfo;          //�ͻ��˻ص���Ϣ
};

class CSybCmd;
class CSybRs
{
// Constructors/Destruction
public:
    CSybRs();
    ~CSybRs();

public:    
/*====================================================================
������      : BindData
����        : �󶨼�¼��������ռ�
�������˵��: ��
����ֵ˵��  : �󶨳ɹ�����true,���򷵻�false
====================================================================*/    
    bool BindData();

/*====================================================================
������      : MoveNext
����        : ��ָ��ָ��������һ����¼
�������˵��: ��
����ֵ˵��  : �ɹ�������ǰ�з���true,���򷵻�false
====================================================================*/    
    bool MoveNext();

/*====================================================================
������      : IsEof
����        : ��¼���Ƿ񵽴�ĩβ
�������˵��: ��
����ֵ˵��  : ����ĩβ����true,����false
====================================================================*/    
    bool IsEof();

/*====================================================================
������      : GetFieldCount
����        : ��ȡ���������
�������˵��: ��
����ֵ˵��  : ���������
====================================================================*/    
    const u16 GetFieldCount();

/*====================================================================
������      : GetFieldInfo
����        : ��ȡ�������������Ϣ
�������˵��: IN lpColName ����
              OUT fieldinfo ���и�ʽ����
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldInfo(LPCSTR lpColName, CS_DATAFMT& Fieldinfo);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, double& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, float& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, s32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, u32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, s16& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, u16& Value);
	
/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, s8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, u8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN lpColName ����
              IN wBufLen �����С
              OUT pstr �����ִ�ֵ
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, LPSTR pstr, u16 wBufLen);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ(�û��Զ������ݿ�)
�������˵��: IN lpColName ����
              IN wBufLen �����С
              OUT pBuf �����׵�ַ
			  OUT wOutLen ʵ��ȡ�����ݿ�Ĵ�С
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, void *pBuf, u16 wBufLen, u16 &wOutLen);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, double& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, float& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, s32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, u32& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, s16& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, u16& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, s8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              OUT Value ����ֵ  
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, u8& Value);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ
�������˵��: IN wIndex ������
              IN wBufLen �����С
              OUT pstr �����ִ�ֵ
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, LPSTR pstr, u16 wBufLen);

/*====================================================================
������      : GetFieldValue
����        : ��ȡĳ��ֵ(�û��Զ������ݿ�)
�������˵��: IN wIndex ������
              IN wBufLen �����С
              OUT pBuf �����׵�ַ
			  OUT wOutLen ʵ��ȡ�����ݿ�Ĵ�С
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, void *pBuf, u16 wBufLen, u16 &wOutLen);

///*====================================================================
//������      : CancelCurRs
//����        : ȡ����ǰ��¼��
//�������˵��: ��
//����ֵ˵��  : �ɹ�true,ʧ��false
//====================================================================*/    
//    bool CancelCurRs();

/*====================================================================
������      : SetCmdPt
����        : ��������ṹָ��
�������˵��: ����ṹָ��
����ֵ˵��  : ��
====================================================================*/    
    void SetCmdPt(CSybCmd*, CS_COMMAND*);

/*====================================================================
������      : GetBufDesc
����        : ��ȡȡ�������ݿ�������
�������˵��: out iodesc ���ݿ�������
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
	bool GetBufDesc(CS_IODESC &iodesc);

protected:
    s16 FindField(LPCSTR lpszName);  //������

protected:
    CSybCmd *m_pcSybCmd;  //CSybCmd��ָ��
    CS_COMMAND *m_pcCommand; //CTLib����ṹָ��
    u8 m_abyBuf[MAX_RECORDCOL_NUM*MAX_COLDATA_WIDTH]; //���浱ǰ��
    CS_DATAFMT m_atFmt[MAX_RECORDCOL_NUM]; //��ǰ��¼���ĸ�ʽ��Ϣ
	s32 m_dwColNum;   //��ǰ��¼��ʵ������
    BOOL32 m_bEnd;    //�Ƿ񵽴��¼��ĩβ
};

class CSybCmd
{
// Constructors/Destruction
public:
    CSybCmd(CSybConnection*);
	CSybCmd();
    ~CSybCmd();

public:
/*====================================================================
������      : SetConnection
����        : ָ��������������
�������˵��: ���Ӷ���ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
	bool SetConnection(CSybConnection*);

/*====================================================================
������      : UseDB
����        : ���ƶ����ݿ�
�������˵��: szDBNameĿ�����ݿ���
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool UseDB(LPCSTR szDBName);

/*====================================================================
������      : ExecSql
����        : ִ��������sql���
�������˵��: szsql sql�ִ�
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool ExecSql(LPCSTR szsql);

/*====================================================================
������      : ExecSql
����        : ִ���м�¼�����ص�sql���
�������˵��: szsql sql�ִ�
              pcRecordSet ���ؽ����ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool ExecSql(LPCSTR szsql, CSybRs *pcRecordSet);

/*====================================================================
������      : OpenCursor
����        : ���α����
�������˵��: lpCursorSql ���α�������Ĳ�ѯ���
              pcRecordSet �α귵�صļ�¼��ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
	bool OpenCursor(LPCSTR lpCursorSql, CSybRs *pcRecordSet);

/*====================================================================
������      : UpdateCurRow
����        : �����α굱ǰ��
�������˵��: lpUpdateSql ���µ�ǰ�е�sql���
			  lpTableName ���α�������ı��� 
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
	bool UpdateCurRow(LPCSTR lpUpdateSql, LPCSTR lpTableName);

/*====================================================================
������      : DelCurRow
����        : ɾ���α굱ǰ��
�������˵��: lpUpdateSql ���µ�ǰ�е�sql���
			  lpTableName ���α�������ı���
			  �ر�ע��: ���α��漰�����ʱ��ɾ����ʧ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
	bool DelCurRow(LPCSTR lpTableName);
	
/*====================================================================
������      : InsertBuf
����        : �����û��Զ���ķǽṹ�����ݵ����ݿ����
�������˵��: lpszSql ��ȡҳָ���Sql���
		      pcRecordSet ��ȡ����ָ��ʱʹ��
			  pBuf  ���ݿ��׵�ַ
              wBufLen ���ݿ鳤��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
    bool InsertBuf(LPCSTR lpszSql, CSybRs *pcRecordSet, const void *pBuf, u16 wBufLen);

/*====================================================================
������      : ExecSql
����        : ִ���ж����¼�����ص�sql���
�������˵��: szsql sql�ִ�
              wleng �ִ���
              pcRecordSet ���ؽ����ָ��
����ֵ˵��  : �ɹ�true,ʧ��false
====================================================================*/    
//    EOpCode ExecSqlWithMultiRs(LPCSTR szsql, u16 wleng, CSybRs *pcRecordSet);
	
/*====================================================================
������      : GoOnProcRes
����        : ������������
�������˵��: bIsClear �Ƿ������ǰ�����
			  �û�������Ĵ˲�����ȫ��ʹ��Ĭ��ֵ����
����ֵ˵��  : EOpCode_FindRs �����µļ�¼��
              EOpCode_Finish ������Ѵ������
			  EOpCode_BindDataErr ���ݰʧ��
              EOpCode_CmdErr ����ĳ������ִ��ʧ��
====================================================================*/    
    EOpCode GoOnProcRes(bool bIsClear = false); 

/*====================================================================
������      : GetAffectedRowCount
����        : ��ȡ�����������õļ�¼����
�������˵��: ��
����ֵ˵��  : ��¼����
====================================================================*/    
	u32 GetAffectedRowCount();

///*====================================================================
//������      : ClearResults
//����        : ������н��
//�������˵��: ��
//����ֵ˵��  : �ɹ�true,ʧ��false
//====================================================================*/    
//    bool ClearResults();

/*====================================================================
������      : IsCurRsEnd
����        : �жϵ�ǰ��¼���Ƿ��Ѵ������
�������˵��: ��
����ֵ˵��  : ������Ϸ���true,����false
====================================================================*/    
    bool IsCurRsEnd();

    //��������ԪΪ���޸ı�־λm_bIsCurRsEnd
//    friend bool CSybRs::CancelCurRs();
    friend bool CSybRs::MoveNext();

private:
/*====================================================================
������      : SendSql
����        : �������
�������˵��: szsql ���
����ֵ˵��  : ���ͳɹ�true,ʧ��false
====================================================================*/    
    bool SendSql(LPCSTR szsql); 

protected:
    CSybRs *m_pcSybRs;    //��ǰ���������
	CS_COMMAND *m_pcCommand;  //CTLib����ṹָ��
    BOOL32 *m_pbIsCurRsEnd;   //��ǰ��¼���Ƿ������
	BOOL32 *m_pbIsFinish;    //��ǰ�����Ƿ������
	u32 m_dwEffectRows;    //��ǰ������Ч�ļ�¼����
};

#endif
