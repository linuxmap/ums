#ifndef _MACRO_PARSE_H_
#define _MACRO_PARSE_H_
#include "xml_vector.h"
#include "xml_com.h"
#include "ParseBase.h"
#include <memory.h>
#include <stdio.h>

typedef struct tagXmlMacroItem
{
	s32   nValue;
	char  achMacroName[XML_MAX_MACRO_CHAR_NUM+1];
public:
	tagXmlMacroItem()
	{
		memset( this, 0, sizeof(struct tagXmlMacroItem) );
	}
	void Print()
	{
		printf( "%s ( %d )\n", achMacroName, nValue );
	}
}TXmlMacroItem, *PTXmlMacroItem;

class CXmlMacroParse : public CXmlParseBase
{
public:
	CXmlMacroParse();
	~CXmlMacroParse();
	void Release();
	u32  Parse( const char* pszFileName );
	void Show();
private:
	CXmlVector<TXmlMacroItem> m_vecterXmlMacroItem;
};


#endif //_MACRO_PARSE_H_