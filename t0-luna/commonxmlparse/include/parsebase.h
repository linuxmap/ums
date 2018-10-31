#ifndef _PARSE_BASE_H_
#define _PARSE_BASE_H_


#include "xmltype.h"
#include "xml_com.h"

class CXmlParseBase
{
public:
	CXmlParseBase();
	virtual ~CXmlParseBase(){};

	char* GetKey(int pos );
	char* GetKey(char* lpString, int pos );
	BOOL32 IsKey(const char* strKey ,s32 pos = 1);	
	void RemoveCharFromeString(char* lpszString ,char c ); // ȥ���ַ�����ָ�����ַ�	
	void RemoveLineRear( char* lpszString );// ȥ���ַ���ĩβ�Ļ��лس���
	u32 InterpretStrToNum( const char* strNum );// �������ַ���ת����u32��ֵ
	u32 Hash( char* str );	
	s32 ReadLine(char* pchLine, int iLen);
	BOOL32 IsNumberString( char* string );
	BOOL32 IsEmptyString( char* string );

	
protected:
	BOOL32 GetString( char* Srcline, s32 pos, char* seps, char str[], s32 len );
	BOOL32 LoadFile( const char* pszFileName );
	void   RelaseFile();
	s32    GetCurPos()const{ return m_dwCurPos; }
	s32    GetFileSize()const{ return m_dwFileSize; }

protected:	
	char    m_achLine[XML_MAX_FILE_LINE_LEN];
	char    m_achKey[XML_MAX_MACRO_CHAR_NUM+1];
private:
	char*	m_pRcBuf;		//�ļ��ڴ�
	s32		m_dwFileSize;		//�ļ��ܳ���
	s32		m_dwCurPos;		//��ǰ��ȡλ��
};


#endif // _PARSE_BASE_H_