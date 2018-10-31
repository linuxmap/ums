#ifndef _STRUCT_PARSE_H_
#define _STRUCT_PARSE_H_

#include "macro_parse.h"

#define FileWithoutComment_tpstruct "filewithoutcomment_tpstruct.txt"
#define FileWithoutComment_localstruct "filewithoutcomment_localstruct.txt"
#define FileWithoutCOmment_tptype "filewithoutcomment_tptype.txt"
#define FileWithoutCOmment_localtype "filewithoutcomment_localtype.txt"

#define FileWithoutBrace1_tpstruct "filewithoutbrace1_tpstruct.txt"
#define FileWithoutBrace1_localstruct "filewithoutbrace1_localstruct.txt"
#define FileWithoutBrace1_tptype "filewithoutbrace1_tptype.txt"
#define FileWithoutBrace1_localtype "filewithoutbrace1_localtype.txt"

#define FileWithoutBrace2_tpstruct "filewithoutbrace2_tpstruct.txt"
#define FileWithoutBrace2_localstruct "filewithoutbrace2_localstruct.txt"
#define FileWithoutBrace2_tptype "filewithoutbrace2_tptype.txt"
#define FileWithoutBrace2_localtype "filewithoutbrace2_localtype.txt"

#define FileWithoutKeyAndFunc_tpstruct "filewithoutkeyandfunc_tpstruct.txt"
#define FileWithoutKeyAndFunc_localstruct "filewithoutkeyandfunc_localstruct.txt"
#define FileWithoutKeyAndFunc_tptype "filewithoutkeyandfunc_tptype.txt"
#define FileWithoutKeyAndFunc_localtype "filewithoutkeyandfunc_localtype.txt"

struct TEnum
{
	char name[64];
	int  count;
	char element[256][64];
};

struct TStructMember
{
	//	int     nType;
	char    type[64];
	char    member[64];	
	BOOL32  bIsArray;
};

struct TStruct
{
	char name[64];
	int count;
	TStructMember member[256];	
};


class CStructParser : public CXmlParseBase
{
public:
	CStructParser();
	~CStructParser();
	BOOL32 CStructParser::CheckFileAttribute(const char* pszOutfile);
	u32 Create();
	u32 GenerateXMLMarshalTable(char* pszInLocaltype1,
		char* pszInLocaltype2,
		char* pszOutLocaltype,
		char* pszInLocalstruct1,
		char* pszInLocalstruct2,
		char* pszOutLocalstruct);
protected:
	char* strdel(char* str ,int index ,int count=1 );
	bool strdelspace(char* str, char* newstr);
	char* strfind(char* line ,char c);
	BOOL32 strinsert(char* line ,int index ,char c);
	char* strfilter( char* str ,char filter[] );
	s32 GetLine(FILE* f ,char* line );

	BOOL32  MakeFileWithoutComment(const char* filename, const char* outputfilename);
	BOOL32  MakeFileWithoutCommentAppend(const char* filename, const char* outputfilename);
	
	BOOL32  WipeOfftmp(char* filename ,char* outputfilename);//È¥³ý¶þ²ã´óÀ¨ºÅ
	BOOL32  WipeOffBrace(char* filename ,char* outputfilename);
	BOOL32  WipeOffKeyWordAndFunction(char* filename ,char* outputfilename);
	BOOL32  GetMember(char* line ,char* type ,char* member );
	u32     PickTpEnum(const char* filename);
	u32     PickLocalEnum(const char* filename);
	u32     PickTpStruct(const char* filename);
	u32     PickLocalStruct(const char* filename);
	void PrintEnum();
	void PrintStruct();
	BOOL32  MakeXmlTpType( const char* pszOutputHeader );
	BOOL32  MakeXmlLocalType( const char* pszOutputHeader );

	BOOL32  MakeXmlTpStruct( const char* filename );
	BOOL32  MakeXmlLocalStruct( const char* filename );

	s8* GetFileName(s8* szFilepath);

private:
	CXmlMacroParse m_cXmlMarcoParser;
	TEnum*         m_ptTpenumArray;
	TEnum*         m_ptLocalEnumArray;
	s32            m_nTpenumCount;
	s32            m_nLocalenumCount;
 	TStruct*       m_ptTpStructArray;
 	s32            m_nTpStructCount;
	TStruct*       m_ptLocalStructArray;
	s32            m_nLocalStructCount;
};

#endif //_STRUCT_PARSE_H_