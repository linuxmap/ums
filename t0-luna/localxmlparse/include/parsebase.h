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
	void RemoveCharFromeString(char* lpszString ,char c ); // 去除字符串中指定的字符	
	void RemoveLineRear( char* lpszString );// 去除字符串末尾的换行回车符
	u32 InterpretStrToNum( const char* strNum );// 将数字字符串转换成u32数值
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
	char*	m_pRcBuf;		//文件内存
	s32		m_dwFileSize;		//文件总长度
	s32		m_dwCurPos;		//当前读取位置
};


#endif // _PARSE_BASE_H_