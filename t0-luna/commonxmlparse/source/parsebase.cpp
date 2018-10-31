#include "parsebase.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


CXmlParseBase::CXmlParseBase()
{
	memset( m_achLine, 0, sizeof(m_achLine) );
	memset( m_achKey,  0, sizeof(m_achKey)  );
	m_pRcBuf = NULL;
	m_dwFileSize = 0;
	m_dwCurPos = 0;
}

char* CXmlParseBase::GetKey(int pos )
{
	memset( m_achKey ,0 ,sizeof( m_achKey ) );
	if( !GetString( m_achLine ,pos ," ,\t\n:",m_achKey ,sizeof(m_achKey) ) )
	{
		return "";
	}
	return m_achKey;
}

char* CXmlParseBase::GetKey(char* lpString, int pos )
{
	memset( m_achKey ,0 ,sizeof( m_achKey ) );
	if( !GetString( lpString ,pos ," ,\t\n:",m_achKey ,sizeof(m_achKey) ) )
	{
		return "";
	}
	return m_achKey;
}

BOOL32 CXmlParseBase:: IsKey(const char* strKey ,s32 pos/* = 1*/)
{
	return ( 0 == strncmp( strKey, GetKey(1), strlen(strKey) ) );
}

BOOL32 CXmlParseBase::IsNumberString( char* string )
{
	if ( NULL == string )
	{
		return FALSE;
	}

	char chr = 0;
	while( ( chr = *string++) != 0 )
	{
		if ( chr < '0' || chr > '9' )
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL32 CXmlParseBase::IsEmptyString( char* string )
{
	char chr = 0;
	while( ( chr = *string++) != 0 )
	{
		if ( chr != '\t' && chr != '\n' && chr != ' ' && chr != '\r' )
		{
			return FALSE;
		}
	}
	return TRUE;
}


void CXmlParseBase::RemoveCharFromeString(char* lpszString ,char c )
{
	s32 len = strlen(lpszString);
	
	for( s32 i=0 ;i< len ; )
	{
		if( lpszString[i] == c )
		{
			for( s32 j= i ;j< len ;j++)
			{
				char next = lpszString[j+1];
				lpszString[j] = next;
			}
			continue;
		}
		i++;
	}
}


void CXmlParseBase::RemoveLineRear( char* lpszString )
{
	s32 i = 0;
	
	for ( ; lpszString[i] != '\0'; i++ )
	{
		if ( lpszString[i] == (char)0x0D || lpszString[i] == (char)0x0A )
		{
			lpszString[i] = 0;
			return;
		}
	}
	
}


u32 CXmlParseBase::InterpretStrToNum( const char* strNum )
{
	if ( strNum == NULL )
	{
		printf( "[InterpretStrToNum], strNum->Null! \n" );
		return 0;
	}
	
	u32 dwVal = 0;
	if ( *strNum == '0' && (*(strNum+1) == 'x' || *(strNum+1) == 'X') ) // 16进制
	{
		sscanf( strNum, "%x", &dwVal );
	}
	else
	{
		sscanf( strNum, "%d", &dwVal );
	}
	
	return dwVal;
}


u32 CXmlParseBase::Hash( char* str )
{
  u32 hash = 0;
  char* p = (char*)str;

  while (*p)
  {
     hash = (*p++) + (hash << 6) + (hash << 16) - hash;
  }

  return hash;
}


BOOL32 CXmlParseBase::GetString( char* Srcline, s32 pos, char* seps, char str[], s32 len )
{
	char* current;
	char  line[256] = { 0 };
	char  tmp[128] = { 0 };
	strcpy( line , Srcline );
	
	
	if ( !Srcline || pos == 0 )
		return NULL;
	
	current = line;
	
	while (*current == ' ' ||  *current == '\t') current++; 
	
	if ( *current == '/' || *(current+1) == '/' ) //注释
		return NULL;
	
	if ( *current == '\r' || *current == '\n' || *current == '\0' )
		return NULL;
	
	char *token;    
	token = strtok( current, seps );
	while( token != NULL && --pos ) // 定位
	{
		/* Get next token: */
		token = strtok( NULL, seps );
	}
	
	if( token )
	{
		//strncpy( str, token, len );
		//str[len-1]='\0';
		strncpy( tmp, token, len );
		tmp[len-1] = '\0';
		if ( strstr(tmp, "=") )
		{
			char *ntoken;
			ntoken = strtok( tmp, "=" ); //去除有些"="紧跟在enum成员被的情况
			strcpy( str, ntoken );	
		}
		else
		{
			strcpy( str, tmp );
		}
	
		str[len-1] = '\0';
		return TRUE;
	}
	
	return FALSE;
}

void CXmlParseBase::RelaseFile()
{
	memset( m_achLine, 0, sizeof(m_achLine) );
	memset( m_achKey,  0, sizeof(m_achKey)  );
	delete [] m_pRcBuf;
	m_pRcBuf = NULL;
	m_dwFileSize = 0;
	m_dwCurPos = 0;
}

BOOL32 CXmlParseBase::LoadFile( const char* pszFileName )
{
	if ( NULL == pszFileName )
	{
		return FALSE;
	}

	if ( NULL != m_pRcBuf )
	{
		return TRUE;
	}
	
	FILE* pFile = fopen( pszFileName, "rb");
	if ( NULL == pFile )
	{
		return FALSE;
	}	
	
	fseek(pFile, 0, SEEK_END);
	m_dwFileSize = ftell(pFile);
	
	if (m_dwFileSize > 0)
	{
		m_pRcBuf = new char[m_dwFileSize];
		if (!m_pRcBuf)
		{
			assert( false && "[LoadRc]: melloc mem failed\n" );
			return false;
		}
		
		fseek(pFile, 0, SEEK_SET);
		fread(m_pRcBuf, m_dwFileSize, 1, pFile);
	}
	
	fclose(pFile);
	return m_dwFileSize > 0;
}

s32 CXmlParseBase::ReadLine(char* pchLine, int iLen)
{
	if (!m_pRcBuf || !pchLine || iLen <= 0)
	{
		return -1;
	}
	
	int iCpPos = 0;
	--iLen;
	
	while (m_dwCurPos < m_dwFileSize )
	{
		if ( iCpPos < iLen )
		{
			if (m_pRcBuf[m_dwCurPos] == '\r')		// 以\r\n结束一行
			{
				*(pchLine + iCpPos) = '\0';
				++iCpPos;
				++m_dwCurPos;
				++m_dwCurPos; // 跳过'\n'
				return iCpPos;
			}
			pchLine[iCpPos] = m_pRcBuf[m_dwCurPos];
			++iCpPos;
			++m_dwCurPos;
		}
		else
		{
			if (m_pRcBuf[m_dwCurPos++] == '\r')
			{
				m_dwCurPos++; // 跳过 '\n'				
				*(pchLine + iLen) = '\0';
				return iCpPos;
			}
		}
	}
		
	return -1 ;
}