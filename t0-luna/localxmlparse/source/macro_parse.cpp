#include "macro_parse.h"
#include <stdlib.h>


CXmlMacroParse::CXmlMacroParse()
{

}

CXmlMacroParse::~CXmlMacroParse()
{

}

void CXmlMacroParse::Release()
{
	m_vecterXmlMacroItem.Release();
}


u32 CXmlMacroParse::Parse( const char* pszFileName )
{
	if ( NULL == pszFileName )
	{
		return err_param_not_valid;
	}

	if ( !LoadFile(pszFileName) )
	{
		return err_file_open_failed;
	}
	
	while ( ReadLine(m_achLine, sizeof(m_achLine)) > 0 )
	{
		if ( 0 == strncmp( "#define", GetKey(1), 7 ) )
		{
			s32 value = 0;
			if ( !IsNumberString( GetKey(3) ) )
			{
				continue;
			}
			else
			{
				value = atoi( GetKey(3) );
			}

			PTXmlMacroItem pXmlMacroItem = new TXmlMacroItem;
			strcpy( pXmlMacroItem->achMacroName, GetKey(2) );
			pXmlMacroItem->nValue = value;
			
			m_vecterXmlMacroItem.Add( pXmlMacroItem, Hash(pXmlMacroItem->achMacroName) );
		}
	}
	
	return Xml_Succeed;
}

void CXmlMacroParse::Show()
{
	PTXmlMacroItem p;
	u32 size = m_vecterXmlMacroItem.Size();
	for ( u32 i = 0; i < size; i++ )
	{
		u32 dwCode = 0;
		p = m_vecterXmlMacroItem.At( i, dwCode );
		printf( "Code:%08u\t", dwCode);
		p->Print();
	}
}