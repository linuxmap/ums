#include <sys/stat.h>
#include <time.h>
#include "struct_parse.h"

char TimeString[64] = {0};

s8* g_pszoutxmltypename = NULL;
s8* g_pszinstructname1 = NULL;
s8* g_pszinstructname2 = NULL;

CStructParser::CStructParser()
{
	m_nTpenumCount = 0;
	m_nLocalenumCount = 0;
	m_nTpStructCount = 0;
	m_nLocalStructCount = 0;

	m_ptTpenumArray = NULL;
	m_ptLocalEnumArray = NULL;
	m_ptTpStructArray = NULL;
	m_ptLocalStructArray =NULL;
}

CStructParser::~CStructParser()
{

}

char* CStructParser::strdel(char* str ,int index ,int count/*=1*/ )
{
	int len = strlen(str);
	int i;
	if( count == 0)
		return str;
	if( count==-1)
		count = len-index;
	for(  i=index ;i<len-count ;i++)
		str[i]=str[i+count];
	
	for( i= len-count ;i< len ;i++)
		str[i]=0;
	return str;
}

bool CStructParser::strdelspace(char* str, char* newstr)
{
	int len = strlen(str);
	char tmpstr[256] = {0};
	char outstr[256] = {0};
	int i = 0;
	int count = 0;
	bool bstart = TRUE;

	if( len == 0)
		return FALSE;
	
	//去掉第一个字符前的空格和制表符
	for ( i = 0; i < len+1; i++)
	{
		if ( (' ' == str[i] || '\t' == str[i]) && bstart )
		{
			continue;	
		}
		else 
		{
			bstart = FALSE;
		}

		if ( ' ' == str[i+1] && '\t' == str[i+1] )
		{
			continue;
		}

		tmpstr[count++] = str[i];
	}
	
	i     = 0;
	count = 0;
	bool bfirstspace = TRUE;
	len = strlen(tmpstr);
	//去掉第一个空格和制表符之后的所有空格和制表符
	for ( i = 0; i < len+1; i++)
	{
		if ( (' ' == str[i] || '\t' == str[i]) && bfirstspace )
		{
			newstr[count++] = tmpstr[i];
			bfirstspace = FALSE;
			continue;
		}
		else if ( ' ' != str[i] && '\t' != str[i] )
		{
			newstr[count++] = tmpstr[i];
		}
	}

	return TRUE;
}

char* CStructParser::strfind(char* line ,char c)
{
	int len = strlen(line);
	for(int i=0 ;i< len ;i++)
	{
		if( line[i]==c )
			return &line[i];
	}
	return NULL;	
}

BOOL32 CStructParser::strinsert(char* line ,int index ,char c)
{
	int len =strlen(line);
	for(int i=len+1 ;i >= index ;i--)
	{
		line[i+1]= line[i];
	}
	line[index]=c;
	return TRUE;
}

char* CStructParser::strfilter( char* str ,char filter[] )
{
	int filterlen = strlen(filter);
	int len = strlen(str);
	for( size_t i=0 ;i< strlen(str) ;i++)
	{
		for( int j=0 ;j< filterlen ;j++)
		{
			if( str[i]== filter[j] )
			{
				strdel(str,i);
			}
		}
	}
	return str;
}

BOOL32 CStructParser::CheckFileAttribute(const char* pszOutfile)
{
	struct stat fileattr;
	memset(&fileattr, 0, sizeof(fileattr));

	if (0 != stat(pszOutfile, &fileattr))
	{
		printf( "%s不存在，已创建！\n", pszOutfile);
		FILE* pFile =fopen(pszOutfile, "w+");
		fclose(pFile);
		return TRUE;
	}
	else
	{
		if ((fileattr.st_mode & S_IREAD) && (fileattr.st_mode & S_IWRITE))
		{
			printf( "%s文件具备读写属性，pass!\n", pszOutfile);
			return TRUE;
		}
		else
		{
			printf( "%s文件只读，请check out!\n", pszOutfile);
			return FALSE;
		}
	}
}


u32 CStructParser::Create()
{
// 	m_ptTpenumArray = new TEnum[1024];
// 	if (!m_ptTpenumArray)
// 	{
// 		return err_memory_exception;
// 	}

	m_ptLocalEnumArray = new TEnum[1024];
	if (!m_ptLocalEnumArray)
	{
		return err_memory_exception;
	}

// 	m_ptTpStructArray = new TStruct[1024];
// 	if (!m_ptTpStructArray)
// 	{
// 		return err_memory_exception;
// 	}

	m_ptLocalStructArray = new TStruct[1024];
	if (!m_ptLocalStructArray)
	{
		return err_memory_exception;
	}

/*	memset(m_ptTpenumArray, 0, sizeof(TEnum)*1024);*/
	memset(m_ptLocalEnumArray, 0, sizeof(TEnum)*1024);
/*	memset(m_ptTpStructArray, 0, sizeof(TStruct)*1024);*/
	memset(m_ptLocalStructArray, 0, sizeof(TStruct)*1024);


	time_t curtime;
	time(&curtime);
	struct tm *UTCTime;
	UTCTime = gmtime( &curtime );
// 	printf("%d%d%d\n", (1900+UTCTime->tm_year), (1+UTCTime->tm_mon), UTCTime->tm_mday);
// 	printf("%d%d%d\n", UTCTime->tm_hour, UTCTime->tm_min, UTCTime->tm_sec);
	sprintf(TimeString, "%d-%d-%d %d:%d:%d",
		(1900+UTCTime->tm_year), (1+UTCTime->tm_mon), UTCTime->tm_mday,
		8+UTCTime->tm_hour, UTCTime->tm_min, UTCTime->tm_sec );
	printf("\n localxmltype.h and localxmlstruct.cpp version time: %s\n\n", TimeString);

	return Xml_Succeed;
}

u32 CStructParser::GenerateXMLMarshalTable(char* pszInLocaltype1,
										   char* pszInLocaltype2, 
										   char* pszOutLocaltype, 
										   char* pszInLocalstruct1, 
										   char* pszInLocalstruct2,
										   char* pszOutLocalstruct)
{

	// enum
	if ((0 != strncmp(pszInLocaltype1, "NULL", 4)))
	{
		if ( !MakeFileWithoutComment(pszInLocaltype1, FileWithoutCOmment_localtype)
			|| !MakeFileWithoutCommentAppend(pszInLocaltype2, FileWithoutCOmment_localtype))
		{
			return err_file_del_comment_failed;
		}
		
		if ( !WipeOfftmp(FileWithoutCOmment_localtype, FileWithoutBrace1_localtype))
		{
			return err_file_del_brace_failed;
		}
		
		if ( !WipeOffBrace(FileWithoutBrace1_localtype, FileWithoutBrace2_localtype))
		{
			return err_file_del_brace_failed;
		}
		
		if ( !WipeOffKeyWordAndFunction(FileWithoutBrace2_localtype, FileWithoutKeyAndFunc_localtype))
		{
			return err_file_del_key_and_func_failed;
		}

		PickLocalEnum(FileWithoutKeyAndFunc_localtype);
	}
	else
	{
		printf("none of input local enum file !\n");
	}

	// struct
	if ((0 != strncmp(pszInLocalstruct1, "NULL", 4)))
	{
		if ( !MakeFileWithoutComment(pszInLocalstruct1, FileWithoutComment_localstruct)
			|| !MakeFileWithoutCommentAppend(pszInLocalstruct2, FileWithoutComment_localstruct))
		{
			return err_file_del_comment_failed;
		}
		
		if ( !WipeOfftmp(FileWithoutComment_localstruct, FileWithoutBrace1_localstruct))
		{
			return err_file_del_brace_failed;
		}
		
		if ( !WipeOffBrace(FileWithoutBrace1_localstruct, FileWithoutBrace2_localstruct))
		{
			return err_file_del_brace_failed;
		}
		
		if ( !WipeOffKeyWordAndFunction(FileWithoutBrace2_localstruct, FileWithoutKeyAndFunc_localstruct))
		{
			return err_file_del_key_and_func_failed;
		}

		PickLocalStruct(FileWithoutKeyAndFunc_localstruct);

		g_pszinstructname1 = GetFileName(pszInLocalstruct1);
		g_pszinstructname2 = GetFileName(pszInLocalstruct2);
	}
	else
	{
		printf("none of input local struct file !\n");
	}

	
// 	PickTpEnum(FileWithoutKeyAndFunc_tptype);
// 	PickTpStruct(FileWithoutKeyAndFunc_tpstruct);

	

	g_pszoutxmltypename = GetFileName(pszOutLocaltype);
	
	printf("structname1 = %s\n", g_pszinstructname1);
	printf("structname2 = %s\n", g_pszinstructname2);
	printf("outtypename = %s\n", g_pszoutxmltypename);



// 	PrintEnum();
// 	PrintStruct();

// 
// 	if (!MakeXmlTpType(pszOuttptype))
// 	{
// 		return err_make_type_ex_file_failed;
// 	}
// 
// 	if (!MakeXmlTpStruct(pszOuttpsruct))
// 	{
// 		return err_make_struct_cpp_file_failed;
// 	}

	if (!MakeXmlLocalStruct(pszOutLocalstruct))
	{
		return err_make_struct_cpp_file_failed;
	}

	if (!MakeXmlLocalType(pszOutLocaltype))
	{
		return err_make_type_ex_file_failed;
	}

	return Xml_Succeed;
}

s32 CStructParser::GetLine(FILE* f ,char* line )
{
	int i,k;
	int len;
	
	while( !feof(f) )
	{
		memset(line,0,256);
		if( NULL == fgets(line ,256 ,f) )
			return -1;
		
		len = strlen( line );
		if( len <2 ) return strlen(line);
		
		//去除空格 \t
		while( line[0]==' ' || line[0]=='\t') strdel(line,0);
		
		len = strlen(line);
		if( len <2 ) return strlen(line);
		//去除注释
		i=0;
		for( i=0 ;i< len-1 ;i++ )
		{
			if(line[i]!='/')
				continue;
			
			if(line[i+1]=='\0x0')
				return -1;//error;
			if(line[i+1]=='/')
			{// 行注释//
				strdel(line,i,-1);
				
				return strlen(line);
			}
			
			if(line[i+1]=='*')
			{// 注释/*
				// 查找 */
				k = i+2;
				
				BOOL32 bFind = FALSE;
				char tmpline[256]={0};
				strcpy(tmpline ,line);
				strdel(line ,i,-1);
				
				do
				{
					len = strlen(tmpline);
					if( 2 <= len)
					{
						
						for( ;k< len-1 ;k++)
						{
							if( tmpline[k]=='*' && tmpline[k+1]=='/' )
							{
								strdel(tmpline ,k ,-1);
								return strlen(line);
							}
						}
						
						k=0;
					}
					if( NULL == fgets(tmpline ,256 ,f) )
						return -1;
				}while(   !feof( f )  );
				
			}
			
		}
		strfilter(line,"\n");
		return strlen(line);
		
	}
	return -1;
}

BOOL32  CStructParser::WipeOfftmp(char* filename ,char* outputfilename)
{
	FILE *fr,*fw;
	char line[256];
	fr = fopen(filename ,"rt");
	if(!fr)return FALSE;
	fw = fopen(outputfilename ,"wt");
	if(!fw) 
	{
		fclose(fr);
		return FALSE;
	}
	
	//确保每行只有一个大括号
	int count =0;
	char* pl;
	char* pr;
	while( 0 <= GetLine(fr ,line) )
	{
		
		pl=strfind(line ,'{');
		while( pl )
		{
			strinsert(pl,0,'\n');
			pl +=2;
			pl=strfind(pl ,'{');
		}
		
		pr=strfind(line ,'}');
		while( pr )
		{
			strinsert(pr,0,'\n');
			pr +=2;
			pr=strfind(pr ,'}');
		}
		fputs(line,fw);
		fputs("\n",fw);
	}
	
	
	
	fclose(fr);
	fclose(fw);
	return TRUE;
}


BOOL32  CStructParser::WipeOffBrace(char* filename ,char* outputfilename)
{
	FILE *fr,*fw;
	char line[256];
	fr = fopen(filename ,"rt");
	if(!fr)return FALSE;
	fw = fopen(outputfilename ,"wt");
	if(!fw) 
	{
		fclose(fr);
		return FALSE;
	}
	
    //确保每行只有一个大括号
	int count =0;
	char* pl;
	char* pr;
	while ( 0 <= GetLine(fr ,line) )
	{
		pl=strfind(line ,'{');
		pr=strfind(line ,'}');
		
		if (pl)
			count++;

		if ( 0 == count )
		{
			strfilter(line,"\n");
			if( 0 < strlen(line) )
			{
				fputs(line,fw);
				fputs("\n",fw);
			}
		}
		else if ( 1 == count )
		{
			char outline[256] = {0};
			strdelspace( line, outline );
			strfilter(outline,"\n");
			if( 0 < strlen(outline) )
			{
				fputs(outline,fw);
				fputs("\n",fw);
			}
		}
		
		if(pr)
			count--;
	}
	
	
	
	fclose(fr);
	fclose(fw);
	return TRUE;
}


BOOL32  CStructParser::WipeOffKeyWordAndFunction(char* filename ,char* outputfilename)
{
	FILE *fr,*fw;
	char line[256];
	char* token;
	fr = fopen(filename ,"rt");
	if(!fr)return FALSE;
	fw = fopen(outputfilename ,"wt");
	if(!fw) 
	{
		fclose(fr);
		return FALSE;
	}
	
    //确保每行只有一个大括号
	int count =0;
	char* pl;
	char* pr;
	while( 0<= GetLine(fr ,line) )
	{
	/*	printf("\t%s\n",line);*/
		pl=strfind(line ,'(');
		pr=strfind(line ,')');
		
		if(pl || pr )
		{
			/*printf("function  %s\n",line);*/
			//	getchar();
			continue;
		}
		
		char fun[256];
		strcpy(fun,line);
		token = strtok(fun," :\t");
		if( token && 
			(0==strcmp(token,"public") ||
			0==strcmp(token,"protected")||
			0==strcmp(token,"private")		)	)
		{
			/*printf("find key %s\n",token);*/
			//getchar();
			continue;
		}
		fprintf(fw ,"%s\n",line);
		//	printf(line);
		//getchar();
		
	}	
	
	fclose(fr);
	fclose(fw);
	return TRUE;
}

BOOL32 CStructParser::MakeFileWithoutComment(const char* filename, const char* outputfilename)
{
	FILE *fr,*fw;
	char line[256];

	fr = fopen( filename, "rt" );
	if ( !fr ) return FALSE;

	fw = fopen( outputfilename, "wt" );
	if ( !fw ) 
	{
		fclose( fr );
		return FALSE;
	}	
	
	while( 0 <= GetLine( fr ,line ) )
	{
		//	strfilter(line ,"\0x09");
		fputs( line, fw );		
		fputs( "\n", fw );
	}
	
	fclose( fr );
	fclose( fw );
	return TRUE;
}

BOOL32  CStructParser::MakeFileWithoutCommentAppend(const char* filename, const char* outputfilename)
{
	FILE *fr,*fw;
	char line[256];

	if (0 == strncmp(filename, "NULL", 4))
	{
		return TRUE;
	}
	
	fr = fopen( filename, "rt" );
	if ( !fr ) return FALSE;
	
	fw = fopen( outputfilename, "at" );
	if ( !fw ) 
	{
		fclose( fr );
		return FALSE;
	}	
	
	while( 0 <= GetLine( fr ,line ) )
	{
		//	strfilter(line ,"\0x09");
		fputs( line, fw );		
		fputs( "\n", fw );
	}
	
	fclose( fr );
	fclose( fw );
	return TRUE;
}

BOOL32 CStructParser::GetMember(char* line ,char* type ,char* member )
{
	char* token;
	char sep[]=" []=;,\t\n";
	token = strtok(line,sep);
	if( token && type)
		strcpy(type,token);
	token = strtok(NULL,sep);
	if( token && member)
		strcpy(member,token);
	return TRUE;
}

u32  CStructParser::PickTpEnum(const char* filename)
{
	if ( !LoadFile( filename ) )
		return err_file_open_failed;

	BOOL32 bEnumStart = FALSE;
	BOOL32 bStructStart = FALSE;
	while ( ReadLine(m_achLine, sizeof(m_achLine)) > 0 )
	{
		if ( 0 == strncmp( "enum", GetKey(1), 4 ) )
		{
			strcpy(m_ptTpenumArray[m_nTpenumCount].name, GetKey(2));			
			m_ptTpenumArray[m_nTpenumCount].count=0;
			bStructStart = FALSE;
			continue;
		}
		else if ( 0 == strncmp( "struct", GetKey(1), 4 ) )
		{
			bStructStart = TRUE;
			continue;
		}

		if ( bStructStart )
		{
			continue;
		}

		if ( bEnumStart )
		{
			char* pKey1 = GetKey(1);
			if ( strfind( pKey1, '{' ) )
			{
				RelaseFile();
				return err_enum_format_invalid;
			}
			
			if ( strfind( pKey1, '}' ) )
			{
				m_nTpenumCount++;
				bEnumStart = FALSE;
				continue;
			}
		
			if ( !IsEmptyString(pKey1) )
			{
				strcpy( m_ptTpenumArray[m_nTpenumCount].element[m_ptTpenumArray[m_nTpenumCount].count], pKey1 );
				m_ptTpenumArray[m_nTpenumCount].count++;
			}
		}
		else
		{
			char* pKey1 = GetKey(1);
			if ( strfind( pKey1, '}' ) )
			{
				RelaseFile();
				return err_enum_format_invalid;
			}

			if ( strfind( pKey1, '{' ) )
			{
				bEnumStart = TRUE;
				continue;
			}
		}
	}
	
	printf("The fisrt Tp enum name: %s\n", m_ptTpenumArray[0].name);
	printf("The last Tp enum name: %s\n\n", m_ptTpenumArray[m_nTpenumCount-1].name);

// 	for( int i=0 ;i< m_nTpenumCount ;i++)
// 	{
// 		if (0 == i || m_nTpenumCount-1 == i)
// 		{
// 			printf("%s\n",m_ptTpenumArray[i].name);
// 		}
// 	}	

	RelaseFile();
	return Xml_Succeed;
}


u32  CStructParser::PickLocalEnum(const char* filename)
{
	if ( !LoadFile( filename ) )
		return err_file_open_failed;
	
	BOOL32 bEnumStart = FALSE;
	BOOL32 bStructStart = FALSE;
	while ( ReadLine(m_achLine, sizeof(m_achLine)) > 0 )
	{
		if ( 0 == strncmp( "enum", GetKey(1), 4 ) )
		{
			strcpy(m_ptLocalEnumArray[m_nLocalenumCount].name, GetKey(2));			
			m_ptLocalEnumArray[m_nLocalenumCount].count=0;
			bStructStart = FALSE;
			continue;
		}
		else if ( 0 == strncmp( "struct", GetKey(1), 4 ) )
		{
			bStructStart = TRUE;
			continue;
		}
		
		if ( bStructStart )
		{
			continue;
		}
		
		if ( bEnumStart )
		{
			char* pKey1 = GetKey(1);
			if ( strfind( pKey1, '{' ) )
			{
				RelaseFile();
				return err_enum_format_invalid;
			}
			
			if ( strfind( pKey1, '}' ) )
			{
				m_nLocalenumCount++;
				bEnumStart = FALSE;
				continue;
			}
			
			if ( !IsEmptyString(pKey1) )
			{
				strcpy( m_ptLocalEnumArray[m_nLocalenumCount].element[m_ptLocalEnumArray[m_nLocalenumCount].count], pKey1 );
				m_ptLocalEnumArray[m_nLocalenumCount].count++;
			}
		}
		else
		{
			char* pKey1 = GetKey(1);
			if ( strfind( pKey1, '}' ) )
			{
				RelaseFile();
				return err_enum_format_invalid;
			}
			
			if ( strfind( pKey1, '{' ) )
			{
				bEnumStart = TRUE;
				continue;
			}
		}
	}
	
	printf("The first Ums enum name: %s\n", m_ptLocalEnumArray[0].name);
	printf("The last Ums enum name: %s\n\n", m_ptLocalEnumArray[m_nLocalenumCount-1].name);
	
// 	for( int i=0 ;i < m_nUmsenumCount ;i++)
// 	{
// 		if (0 == i || m_nUmsenumCount-1 == i)
// 		{
// 			printf("%s\n",m_ptUmsenumArray[i].name);
// 		}
// 	}	
	
	RelaseFile();
	return Xml_Succeed;
}


u32 CStructParser::PickTpStruct(const char* filename)
{
	if ( !LoadFile( filename ) )
		return err_file_open_failed;

	BOOL32 bStructStart = FALSE;
	BOOL32 bStruct = TRUE;
	while ( ReadLine(m_achLine, sizeof(m_achLine)) > 0 )
	{
		if ( IsEmptyString( m_achLine ) )
			continue;

		//此处代码对存在enum的情况无能为力
		if ( 0 == strncmp( "typedef", GetKey(1), 6 ) )
		{
			if ( 0 == strncmp( "struct", GetKey(2), 6 ) )
			{
				bStruct = TRUE;
				char* pStructName = GetKey( 3 );
				if ( 0 == strncmp(pStructName, "tag", 3) )
				{
					m_ptTpStructArray[m_nTpStructCount].count=0;
					strcpy(m_ptTpStructArray[m_nTpStructCount].name, &pStructName[3]);
				}
				else
				{
// 					RelaseFile();
// 					return err_struct_format_invalid;
					//mtstruct.h中有不使用tag开头定义的结构，特殊处理，不做错误返回
					m_ptTpStructArray[m_nTpStructCount].count=0;
					strcpy(m_ptTpStructArray[m_nTpStructCount].name, &pStructName[0]);
				}
			}
			else
			{
				RelaseFile();
				return err_struct_format_invalid;
			}
		}
		else if ( 0 == strncmp( "template", GetKey(1), 8) )
		{
			bStruct = FALSE;
			continue;
		}

		if ( bStruct )
		{
			if ( bStructStart )
			{
				char* pKey1 = GetKey(1);
				if ( strfind( pKey1, '{' ) )
				{
					RelaseFile();
					return err_enum_format_invalid;
				}
				
				if ( strfind( pKey1, '}' ) )
				{
					m_nTpStructCount++;
					bStructStart = FALSE;
					continue;
				}
				
				if ( !IsEmptyString(pKey1) )
				{
					strcpy( m_ptTpStructArray[m_nTpStructCount].member[m_ptTpStructArray[m_nTpStructCount].count].type, GetKey(1) );
					char* pszName = GetKey(2);
					char* p = pszName;
					BOOL32 bIsArray = FALSE;
					u8 count = 0;
					while( (*pszName++) != 0 )
					{
						if( *pszName == '[')
							count++;
					}
					
					pszName = p;
					while( (*pszName++) != 0 )
					{
						if( *pszName == '[' || *pszName == ';' )
						{
							*pszName = 0;
							break;
						}
					}
					if ( count == 2 )
						bIsArray = TRUE;
					strcpy( m_ptTpStructArray[m_nTpStructCount].member[m_ptTpStructArray[m_nTpStructCount].count].member, p );
					m_ptTpStructArray[m_nTpStructCount].member[m_ptTpStructArray[m_nTpStructCount].count].bIsArray = bIsArray;
					m_ptTpStructArray[m_nTpStructCount].count++;
				}
			} 
			else
			{
				char* pKey1 = GetKey(1);
				if ( strfind( pKey1, '}' ) )
				{
// 					RelaseFile();
// 					return err_enum_format_invalid;
				}
				
				if ( strfind( pKey1, '{' ) )
				{
					bStructStart = TRUE;
					continue;
				}

				if (pKey1 = strfind(m_achLine, ':'))
				{
					char* pKey2 = GetKey(pKey1+1, 1);
					if ( 0 != strncmp( "public", pKey2, 6 ) )
					{
						RelaseFile();
						return err_enum_format_invalid;
					}

					pKey2 = GetKey(pKey1+1, 2);
					if ( IsEmptyString(pKey2) )
					{
						RelaseFile();
						return err_enum_format_invalid;
					}
					
					int x = strncmp("abc", "def", 3);

					int iTmpKeyLen = strlen(pKey2);
					for (int iTmp = 0; iTmp < m_nTpStructCount-1; ++iTmp)
					{
						if (0 == strncmp(m_ptTpStructArray[iTmp].name, pKey2, iTmpKeyLen))
						{
							memcpy(m_ptTpStructArray[m_nTpStructCount].member, m_ptTpStructArray[iTmp].member, m_ptTpStructArray[iTmp].count*sizeof(TStructMember));
							m_ptTpStructArray[m_nTpStructCount].count = m_ptTpStructArray[iTmp].count;
							break;
						}
					}
				}
			}
		}		
	}
	
	printf("The first Tp struct name: %s\n", m_ptTpStructArray[0].name);
	printf("The last Tp struct name: %s\n\n", m_ptTpStructArray[m_nTpStructCount-1].name);

// 	for( int i=0 ;i< m_nTpStructCount ;i++)
// 	{
// 		if (0 == i || m_nTpStructCount-1 == i)
// 		{
// 			printf("%s\n",m_ptTpStructArray[i].name);
// 		}
// 	}

	RelaseFile();
	return Xml_Succeed;
}

u32 CStructParser::PickLocalStruct(const char* filename)
{
	if ( !LoadFile( filename ) )
		return err_file_open_failed;

	BOOL32 bStructStart = FALSE;
	BOOL32 bStruct = TRUE;
	while ( ReadLine(m_achLine, sizeof(m_achLine)) > 0 )
	{
		if ( IsEmptyString( m_achLine ) )
			continue;

		//此处代码对存在enum的情况无能为力
		if ( 0 == strncmp( "typedef", GetKey(1), 6 ) )
		{
			if ( 0 == strncmp( "struct", GetKey(2), 6 ) )
			{
				bStruct = TRUE;
				char* pStructName = GetKey( 3 );
				if ( 0 == strncmp(pStructName, "tag", 3) )
				{
					m_ptLocalStructArray[m_nLocalStructCount].count=0;
					strcpy(m_ptLocalStructArray[m_nLocalStructCount].name, &pStructName[3]);
				}
				else
				{
// 					RelaseFile();
// 					return err_struct_format_invalid;
					//mtstruct.h中有不使用tag开头定义的结构，特殊处理，不做错误返回
					m_ptLocalStructArray[m_nLocalStructCount].count=0;
					strcpy(m_ptLocalStructArray[m_nLocalStructCount].name, &pStructName[0]);
				}
			}
			else
			{
				RelaseFile();
				return err_struct_format_invalid;
			}
		}
		else if ( 0 == strncmp( "template", GetKey(1), 8) )
		{
			bStruct = FALSE;
			continue;
		}

		if ( bStruct )
		{
			if ( bStructStart )
			{
				char* pKey1 = GetKey(1);
				if ( strfind( pKey1, '{' ) )
				{
					RelaseFile();
					return err_enum_format_invalid;
				}
				
				if ( strfind( pKey1, '}' ) )
				{
					m_nLocalStructCount++;
					bStructStart = FALSE;
					continue;
				}
				
				if ( !IsEmptyString(pKey1) )
				{
					strcpy( m_ptLocalStructArray[m_nLocalStructCount].member[m_ptLocalStructArray[m_nLocalStructCount].count].type, GetKey(1) );
					char* pszName = GetKey(2);
					char* p = pszName;
					BOOL32 bIsArray = FALSE;
					u8 count = 0;
					while( (*pszName++) != 0 )
					{
						if( *pszName == '[')
							count++;
					}
					
					pszName = p;
					while( (*pszName++) != 0 )
					{
						if( *pszName == '[' || *pszName == ';' )
						{
							*pszName = 0;
							break;
						}
					}
					if ( count == 2 )
						bIsArray = TRUE;
					strcpy( m_ptLocalStructArray[m_nLocalStructCount].member[m_ptLocalStructArray[m_nLocalStructCount].count].member, p );
					m_ptLocalStructArray[m_nLocalStructCount].member[m_ptLocalStructArray[m_nLocalStructCount].count].bIsArray = bIsArray;
					m_ptLocalStructArray[m_nLocalStructCount].count++;
				}
			} 
			else
			{
				char* pKey1 = GetKey(1);
				if ( strfind( pKey1, '}' ) )
				{
// 					RelaseFile();
// 					return err_enum_format_invalid;
				}
				
				if ( strfind( pKey1, '{' ) )
				{
					bStructStart = TRUE;
					continue;
				}

				if (pKey1 = strfind(m_achLine, ':'))
				{
					char* pKey2 = GetKey(pKey1+1, 1);
					if ( 0 != strncmp( "public", pKey2, 6 ) )
					{
						RelaseFile();
						return err_enum_format_invalid;
					}

					pKey2 = GetKey(pKey1+1, 2);
					if ( IsEmptyString(pKey2) )
					{
						RelaseFile();
						return err_enum_format_invalid;
					}
					
					int x = strncmp("abc", "def", 3);

					int iTmpKeyLen = strlen(pKey2);
					for (int iTmp = 0; iTmp < m_nLocalStructCount-1; ++iTmp)
					{
						if (0 == strncmp(m_ptLocalStructArray[iTmp].name, pKey2, iTmpKeyLen))
						{
							memcpy(m_ptLocalStructArray[m_nLocalStructCount].member, m_ptLocalStructArray[iTmp].member, m_ptLocalStructArray[iTmp].count*sizeof(TStructMember));
							m_ptLocalStructArray[m_nLocalStructCount].count = m_ptLocalStructArray[iTmp].count;
							break;
						}
					}
				}
			}
		}		
	}
	
	printf("The first Ums struct name: %s\n", m_ptLocalStructArray[0].name);
	printf("The last Ums struct name: %s\n\n", m_ptLocalStructArray[m_nLocalStructCount-1].name);

// 	for( int i=0 ;i< m_nUmsStructCount ;i++)
// 	{
// 		if (0 == i || m_nUmsStructCount-1 == i)
// 		{
// 			printf("%s\n",m_ptUmsStructArray[i].name);
// 		}
// 	}

	RelaseFile();
	return Xml_Succeed;
}

void CStructParser::PrintEnum()
{
	for(int i=0 ;i< m_nTpenumCount ;i++)
	{
		printf(" %s\n",m_ptTpenumArray[i].name);
		for(int j=0 ;j< m_ptTpenumArray[i].count ;j++)
		{
			printf("\t%s\n",m_ptTpenumArray[i].element[j]);
		}
	}
}

void CStructParser::PrintStruct()
{
	for(int i=0 ;i< m_nTpStructCount ;i++)
	{
		printf(" %s\n",m_ptTpStructArray[i].name);
		for(int j=0 ;j< m_ptTpStructArray[i].count ;j++)
		{
			printf("\t%s  %s\n",m_ptTpStructArray[i].member[j].type ,
				m_ptTpStructArray[i].member[j].member);
		}
	}
}

static char xmlhead[]={"\
 \n\
#define TpEnumIdString(type, index) index, GetTpEnumString(emx_##type, index)\n\
#define TpEnumString(type, index) GetTpEnumString(emx_##type, index)\n\
s8* GetTpEnumString(u16 wType, u16 wIndex);\n"};

BOOL32 CStructParser::MakeXmlTpType(const char* pszOutputHeader)
{
	char line[256] = {0};

	FILE* fw = fopen(pszOutputHeader, "wt");
	if (NULL == fw)
	{
		printf("Open file %s error!\n", pszOutputHeader );
		return FALSE;
	}

	int i = 0;

	fputs("#ifndef _TP_COMMON_XML_TYPE_H_\n", fw);
	fputs("#define _TP_COMMON_XML_TYPE_H_\n\n",fw);
	fputs("#include \"msgmgr.h\"\n",fw);
	fputs("#include \"xmlengine.h\"\n\n",fw);

	sprintf(line, "const char XmlTpTypeVersion[] = \"%s\";\n\n", TimeString);
	fputs(line, fw);

	fputs("// Tp Data struct type begin\n",fw);
	fputs("enum EmXDataTpType\n{\n",fw);
				
	fputs("  _placeholder_emxEnumTypeBegin = emxEnumTypeBegin, // Tp枚举类型数据开始\n", fw);
	for( i=0 ;i< m_nTpenumCount ;i++)
	{
		sprintf(line ,"\temx_%s,\n",m_ptTpenumArray[i].name);
		fputs(line,fw);
	}

/*	sprintf(line, "_placeholder_emxEnumTptypeEnd, //Tp枚举类型数据结束");*/
	fputs("_placeholder_emxEnumTptypeEnd, //Tp枚举类型数据结束", fw);
	/*fputs("  _placeholder_emxEnumTptypeEnd,   //Tp枚举类型数据结束\n", fw);*/

	fputs(" \n _placeholder_emxStructTypeBegin = emxStructTypeBegin, //Tp数据结构类型数据开始\n", fw);	
	for( i=0 ;i< m_nTpStructCount ;i++)
	{
		sprintf(line, "\temx_%s,\n", m_ptTpStructArray[i].name);
		fputs(line,fw);
	}
	
/*	sprintf(line, "_placeholder_emxTpStructTypeend, //Tp数据结构类型数据结束", m_ptTpStructArray[m_nTpStructCount-1].name);*/
	fputs("_placeholder_emxTpStructTypeend, //Tp数据结构类型数据结束", fw);

/*	fputs("  _placeholder_emxTpStructTypeend,  //Tp数据结构类型数据结束\n};\n", fw);*/

	fputs("\n};\n//Tp Data struct type end\n",fw);

/*	fputs(xmlhead, fw);*/

	fputs("\n#endif //_TP_COMMON_XML_TYPE_H_\n", fw);
	fclose(fw);	
	
	return TRUE;
}

BOOL32 CStructParser::MakeXmlLocalType(const char* pszOutputHeader)
{
	FILE *fw;
	char line[256];
	
	//	rename(filename,bak);
	fw = fopen(pszOutputHeader, "wt");
	if ( !fw )
	{
		printf("Open file %s error!\n", pszOutputHeader );
		return FALSE;
	}
	int i;
	
	fputs("#ifndef _LOCAL_XML_TYPE_H_\n",fw);
	fputs("#define _LOCAL_XML_TYPE_H_\n\n",fw);
// 	fputs("//#include \"msgmgr.h\"\n",fw);
// 	fputs("//#include \"xmlengine.h\"\n",fw);
	fputs("#include \"tpcommonxmltype.h\"\n\n", fw);

	sprintf(line, "const char XmlLocalTypeVersion[] = \"%s\";\n\n", TimeString);
	fputs(line, fw);		
	
	if (0 != m_nLocalenumCount || 0 != m_nLocalStructCount)
	{
		fputs("//Local Data struct type begin\n",fw);
		fputs("enum EmXDataLocalType\n{\n", fw);

		if (0 != m_nLocalenumCount)
		{
			sprintf(line, "\temx_%s = _placeholder_emxEnumTptypeEnd, //Local枚举类型数据开始,紧接Tp枚举结束\n", m_ptLocalEnumArray[0].name);
			fputs(line, fw);
			/*fputs("  _placeholder_emxEnumUmsTypeBegin = _placeholder_emxEnumTptypeEnd, //Ums枚举类型数据开始,紧接Tp枚举结束\n", fw);*/
			for( i=1 ; i< m_nLocalenumCount ; i++)
			{
				sprintf(line ,"\temx_%s,\n",m_ptLocalEnumArray[i].name);
				fputs(line, fw);
			}
		}

		if (0 != m_nLocalStructCount)
		{
			sprintf(line, "\temx_%s = _placeholder_emxTpStructTypeend, //Local数据结构类型数据开始,紧接Tp结构体结束\n", m_ptLocalStructArray[0].name);
			fputs(line, fw);
			
			/*fputs("  _placeholder_emxStructUmsTypeBegin = _placeholder_emxTpStructTypeend, //ums数据结构类型数据开始,紧接Tp结构体结束\n", fw);*/
			
			for( i=1 ;i< m_nLocalStructCount ;i++)
			{
				sprintf(line ,"\temx_%s,\n",m_ptLocalStructArray[i].name);
				fputs(line,fw);
			}	
		}
		fputs("_placeholder_emxDataTypeEnd = emxDataTypeEnd, //类型定义结束\n};\n",fw);
		sprintf(line,"//Local Data struct type end\n");
		fputs( line, fw );
	}


	//namespace
    fputs( "\nnamespace UmsTpmsg {\n", fw );
	
	fputs( xmlhead, fw );

	fputs("TXDATAINFO** CombineEnumDateInfo(void);\n", fw);
	fputs("TXDATAINFO** CombineStructDateInfo(void);\n", fw);
	fputs("void CombineEnumXDescripTbl(void);\n\n", fw);
	
	//end namespace 
	fputs( "\n} //namespace UmsTpmsg\n", fw );

	fputs("#endif //_LOCAL_XML_TYPE_H_\n", fw);
	fclose(fw);	
	
	return TRUE;
}

static char headstruct1[]={"\
#include \"tpstruct.h\"\n\
#include \"umscommonstruct.h\"\n\
#include \"xmlengine.h\"\n\
#include \"msgmgr.h\"\n\
#include \"umsxmltype.h\"\n"};

static char headstruct[]={"\
\n\
#define ENUMTYPE( type )\\\n\
\tconst TXDATAINFO type##membertable[] = {#type,emx_##type,\"enum\",4,1,0,0,(char*)#type};\n\
\n\
#define TYPESTRUCT_BEGIN( s )\\\n\
\tconst TXDATAINFO s##membertable[]={\n\
#define TYPESTRUCT_MEMBER( s,type ,m )\\\n\
\t{#s,emx_##type,#type,sizeof(type),XML_SizeOfMember(s,m)/sizeof(type),0,XML_OffSetOf(s,m),(char*)#m},\n\
#define TYPESTRUCT_MATRIX( s,type ,m )\\\n\
\t{#s,emx_##type,#type,sizeof(type),XML_SizeOfMember(s,m)/sizeof(type),XML_SizeOfMatrix(s,type,m),XML_OffSetOf(s,m),(char*)#m},\n\
#define TYPESTRUCT_END( s )\\\n\
\t{#s,emxDataTypeEnd,0,sizeof(s),0,0,0,#s}};\n"};


static char headgetenumfun[]={"\
s8* GetTpEnumString(u16 type, u16 index)\n\
{\n\
\tif (NULL == enumTpXDescripTbl[0])\n\
\t{\n\
\t\tCombineEnumXDescripTbl();\n\
\t}\n\n\
\tu16 wTmpType = type - _placeholder_emxEnumTypeBegin - 1;\n\
\tif (wTmpType > sizeof(enumTpXDescripTbl)/sizeof(enumTpXDescripTbl[0]))\n\
\t\treturn \"DefaultType\";\n\
\t\n\
\tTXENUMINFO* pEnumInfo = enumTpXDescripTbl[wTmpType];\n\
\twhile(NULL != pEnumInfo->descrip)\n\
\t{\n\
\t\tif (pEnumInfo->val == index)\n\
\t\t\treturn pEnumInfo->descrip;\n\
\t\tpEnumInfo++;\n\
\t}\n\
\treturn \"DefaultIndex\";\n\
}\n\
\n"};

static char combineenumfun[] = {"\
TXDATAINFO** CombineEnumDateInfo(void)\n\
{\n\
\tmemcpy(g_tTpEnumDataInfo, g_tTpEnumData, sizeof(g_tTpEnumData));\n\
\tmemcpy(g_tTpEnumDataInfo + XML_TP_TYPE_NUM, g_tLocalEnumDataInfo, sizeof(g_tLocalEnumDataInfo));\n\
\treturn g_tTpEnumDataInfo;\n\
}\n\
\n"};

static char combinestructfun[] = {"\
TXDATAINFO** CombineStructDateInfo(void)\n\
{\n\
\tmemcpy(g_tTpStructDataInfo, g_tTpStructData, sizeof(g_tTpStructData));\n\
\tmemcpy(g_tTpStructDataInfo + XML_TP_STRUCT_NUM, g_tLocalStructDataInfo, sizeof(g_tLocalStructDataInfo));\n\
\treturn g_tTpStructDataInfo;\n\
}\n\
\n"};

static char combineenumtblfun[] = {"\
void CombineEnumXDescripTbl(void)\n\
{\n\
\tmemcpy(enumTpXDescripTbl, enumTpXDescript, sizeof(enumTpXDescript));\n\
\tmemcpy(enumTpXDescripTbl + XML_TP_TYPE_NUM, enumLocalXDescripTbl, sizeof(enumLocalXDescripTbl));\n\
}\n\
\n"};

static char gettpenumfun[] = {"\
s8* GetTpEnumString(u16 type, u16 index)\n\
{\n\
\tu16 wTmpType = type - _placeholder_emxEnumTypeBegin - 1;\n\
\tif (wTmpType >= (XML_TP_TYPE_NUM + XML_LOCAL_TYPE_NUM))\n\
\t{\n\
\t\treturn \"DefaultType\";\n\
\t}\n\
\telse if (wTmpType >= XML_TP_TYPE_NUM)\n\
\t{\n\
\t\twTmpType = wTmpType - XML_TP_TYPE_NUM;\n\
\t\tTXENUMINFO* pEnumInfo = enumLocalXDescripTbl[wTmpType];\n\
\t\twhile (NULL != pEnumInfo->descrip)\n\
\t\t{\n\
\t\t\tif (pEnumInfo->val == index)\n\
\t\t\t\treturn pEnumInfo->descrip;\n\
\t\t\tpEnumInfo++;\n\
\t\t}\n\
\t\treturn \"DefaultIndex\";\n\
\t}\n\
\telse\n\
\t{\n\
\t\tTXENUMINFO* pEnumInfo = enumTpXDescript[wTmpType];\n\
\t\twhile (NULL != pEnumInfo->descrip)\n\
\t\t{\n\
\t\t\tif (pEnumInfo->val == index)\n\
\t\t\t\treturn pEnumInfo->descrip;\n\
\t\t\tpEnumInfo++;\n\
\t\t}\n\
\t\treturn \"DefaultIndex\";\n\
\t}\n\
}\n\
\n"};

BOOL32  CStructParser::MakeXmlTpStruct( const char* filename )
{
	int i = 0;
	int j = 0;
	char line[256] = {0};
	
	FILE* f = fopen(filename ,"wt");
	if (NULL == f)
	{
		return FALSE;
	}

	fputs("#ifndef _TP_COMMON_XML_STRUCT_H_\n", f);
	fputs("#define _TP_COMMON_XML_STRUCT_H_\n\n",f);

	fputs(headstruct1, f);
/*	fputs("#include \"tpcommonxmltype.h\"\n", f);*/
/*	fputs("#include \"tpcommonstruct.h\"\n", f);*/

	sprintf(line, "\nconst char XmlTpStructVersion[] = \"%s\";\n\n", TimeString);
	fputs(line, f);

	sprintf(line, "#define XML_TP_TYPE_NUM      %d\n", m_nTpenumCount);
	fputs(line, f);

	sprintf(line, "#define XML_TP_STRUCT_NUM    %d\n", m_nTpStructCount);
	fputs(line, f);

// 	fputs("char* GetTpXmlStructVer()\n",f);
// 	fputs("{\n\treturn (char*)XmlStructVersion;\n}\n",f);
    
	fputs(headstruct, f);
	
	// 写宏定义ENUMTYPE
	for(i = 0; i < m_nTpenumCount; i++)
	{
		sprintf(line, "\nENUMTYPE(%s);", m_ptTpenumArray[i].name);
		fputs(line, f);
	}

	// 写TP枚举编码表
	fputs("\n\nTXDATAINFO* g_tTpEnumData[]={\n", f);
	for(i = 0; i < m_nTpenumCount; i++)
	{
		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptTpenumArray[i].name);
		fputs(line, f);
	}
	fputs("\t(TXDATAINFO*)NULL\n};\n",f);

	//写结构体描述
	for(i = 0; i< m_nTpStructCount; i++)
	{
		sprintf(line, "\n//%s\n", m_ptTpStructArray[i].name);
		fputs(line, f);
		sprintf(line, "TYPESTRUCT_BEGIN( %s )\n", m_ptTpStructArray[i].name);
		fputs(line, f);
		
		for(j = 0; j < m_ptTpStructArray[i].count; j++)
		{
			if (m_ptTpStructArray[i].member[j].bIsArray)
			{
				sprintf(line, "    TYPESTRUCT_MATRIX( %s, %s, %s )\n", m_ptTpStructArray[i].name
					,m_ptTpStructArray[i].member[j].type 
					,m_ptTpStructArray[i].member[j].member);
			}
			else
			{
				sprintf(line, "    TYPESTRUCT_MEMBER( %s, %s, %s )\n", m_ptTpStructArray[i].name
					,m_ptTpStructArray[i].member[j].type 
					,m_ptTpStructArray[i].member[j].member);
			}

			fputs(line, f);
		}
		sprintf(line, "TYPESTRUCT_END(  %s )\n", m_ptTpStructArray[i].name);
		fputs(line, f);
	}
	
	fputs("\n//通讯数据结构编码表\n", f);
	fputs("TXDATAINFO* g_tTpStructData[]={\n", f);
	for(i = 0; i < m_nTpStructCount; i++)
	{
		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptTpStructArray[i].name);
		fputs(line, f);
	}
	fputs("\t(TXDATAINFO*)NULL\n};\n",f);
	
	//枚举类型
	for(i = 0; i < m_nTpenumCount; i++)
	{
		sprintf(line, "\nconst TXENUMINFO enum%sDescript[]={\n", m_ptTpenumArray[i].name);
		fputs(line, f);
		for(j = 0; j < m_ptTpenumArray[i].count; j++)
		{
			sprintf(line, "\t{ \"%s\", (int)%s },\n", m_ptTpenumArray[i].element[j], m_ptTpenumArray[i].element[j]);
			fputs(line, f);
		}
		sprintf(line, "\t{ (char*)NULL, (int)-1 }\n};\n", m_ptTpenumArray[i].element[j], m_ptTpenumArray[i].element[j]);
		fputs(line, f);
	}
	
    fputs("\n//枚举描述字符串表\n", f);
    fputs("TXENUMINFO* enumTpXDescript[]={\n", f);
	for(i = 0; i < m_nTpenumCount; i++)
	{
		sprintf(line, "\t(TXENUMINFO*)enum%sDescript, \n", m_ptTpenumArray[i].name);
		fputs(line, f);
	}
	fputs("\t(TXENUMINFO*)NULL\n};\n\n", f);
	
/*	fputs(headgetenumfun,f);*/
	
	fputs("#endif //_TP_COMMON_XML_STRUCT_H_\n", f);

	fclose(f);
	return TRUE;	
}

BOOL32  CStructParser::MakeXmlLocalStruct( const char* filename )
{
	int i = 0;
	int j = 0;
	char line[256] = {0};
	
	FILE* f = fopen(filename ,"wt");
	if (NULL == f)
	{
		printf("open file: %s error !!!\n", filename);
		return FALSE;
	}
// 	
// 	fputs("#ifndef _UMS_XML_STRUCT_H_\n", f);
// 	fputs("#define _UMS_XML_STRUCT_H_\n\n",f);


/*	fputs(headstruct1, f);*/
	fputs("#include \"tpcommonxmlstruct.h\"\n", f);

	if (NULL != g_pszoutxmltypename)
	{
		sprintf(line, "#include \"%s\"\n", g_pszoutxmltypename);
		fputs(line, f);
	}
	
//	if (NULL == g_pszinstructname1 && NULL == g_pszinstructname2)
	{
		fputs("#include \"tpstruct.h\"\n", f);
	}
//	else 
	{
// 		if (0 != strncmp(g_pszinstructname1, "tpstruct", 8) && 0 != strncmp(g_pszinstructname2, "tpstruct", 8))
// 		{
// 			fputs("#include \"tpstruct.h\"\n", f);
// 		}

		if (NULL != g_pszinstructname1)
		{
// 			if (0 != strncmp(g_pszinstructname1, "tpstruct", 8))
// 			{
// 				fputs("#include \"tpstruct.h\"\n", f);
// 			}
			sprintf(line, "#include \"%s\"\n", g_pszinstructname1);
			fputs(line, f);
		}
		if (NULL != g_pszinstructname2)
		{
			sprintf(line, "#include \"%s\"\n", g_pszinstructname2);
			fputs(line, f);
		}
	}

/*	fputs("#include \"tpstruct.h\"\n", f);*/
// 	
// 	fputs("#include \"umscommonstruct.h\"\n", f);
	
	sprintf(line, "\nconst char XmlLocalStructVersion[] = \"%s\";\n\n", TimeString);
	fputs(line, f);

	sprintf(line, "#define XML_LOCAL_TYPE_NUM      %d\n", m_nLocalenumCount);
	fputs(line, f);
	
	sprintf(line, "#define XML_LOCAL_STRUCT_NUM    %d\n", m_nLocalStructCount);
	fputs(line, f);

// 	fputs("char* GetTpXmlStructVer()\n",f);
// 	fputs("{\n\treturn (char*)XmlStructVersion;\n}\n",f);
    
/*	fputs(headstruct, f);*/

	//namespace 
	fputs("\nnamespace UmsTpmsg {\n", f);
	
	for(i = 0; i < m_nLocalenumCount; i++)
	{
		sprintf(line, "\nENUMTYPE(%s);", m_ptLocalEnumArray[i].name);
		fputs(line, f);
	}
	
	fputs("\n\nTXDATAINFO* g_tLocalEnumDataInfo[]={\n", f);
	for(i = 0; i < m_nLocalenumCount; i++)
	{
		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptLocalEnumArray[i].name);
		fputs(line, f);
	}
	fputs("\t(TXDATAINFO*)NULL\n};\n", f);
	
	//数据结构
	for(i = 0; i < m_nLocalStructCount; i++)
	{
		sprintf(line, "\n//%s\n", m_ptLocalStructArray[i].name);
		fputs(line, f);
		sprintf(line, "TYPESTRUCT_BEGIN( %s )\n", m_ptLocalStructArray[i].name);
		fputs(line, f);
		
		for(j = 0; j < m_ptLocalStructArray[i].count; j++)
		{
			if (m_ptLocalStructArray[i].member[j].bIsArray)
			{
				sprintf(line, "    TYPESTRUCT_MATRIX( %s, %s, %s )\n", m_ptLocalStructArray[i].name
					,m_ptLocalStructArray[i].member[j].type 
					,m_ptLocalStructArray[i].member[j].member);
			}
			else
			{
				sprintf(line, "    TYPESTRUCT_MEMBER( %s, %s, %s )\n", m_ptLocalStructArray[i].name
					,m_ptLocalStructArray[i].member[j].type 
					,m_ptLocalStructArray[i].member[j].member);
			}
			
			fputs(line, f);
		}
		sprintf(line, "TYPESTRUCT_END(  %s )\n", m_ptLocalStructArray[i].name);
		fputs(line, f);
	}
	
	fputs("\n//通讯数据结构编码表\n", f);
	fputs("TXDATAINFO* g_tLocalStructDataInfo[]={\n", f);
	for(i = 0; i < m_nLocalStructCount; i++)
	{
		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptLocalStructArray[i].name);
		fputs(line, f);
	}
	fputs("\t(TXDATAINFO*)NULL\n};\n", f);
	
	//枚举类型
	for(i=0; i < m_nLocalenumCount; i++)
	{
		sprintf(line, "\nconst TXENUMINFO enum%sDescript[]={\n", m_ptLocalEnumArray[i].name);
		fputs(line, f);
		for(j = 0; j < m_ptLocalEnumArray[i].count;j++)
		{
			sprintf(line, "\t{ \"%s\", (int)%s },\n", m_ptLocalEnumArray[i].element[j], m_ptLocalEnumArray[i].element[j]);
			fputs(line, f);
		}
		sprintf(line, "\t{ (char*)NULL, (int)-1 }\n};\n");
		fputs(line, f);
	}
	
    fputs("\n//枚举描述字符串表\n",f);
    fputs("TXENUMINFO* enumLocalXDescripTbl[]={\n", f);
	for(i = 0;i < m_nLocalenumCount; i++)
	{
		sprintf(line, "\t(TXENUMINFO*)enum%sDescript, \n", m_ptLocalEnumArray[i].name);
		fputs(line, f);
	}
	fputs("\t(TXENUMINFO*)NULL\n};\n\n", f);
	
// 	fputs("extern TXDATAINFO* g_tTpEnumData[];\n", f);
// 	fputs("extern TXDATAINFO* g_tTpStructData[];\n", f);
// 	fputs("extern TXENUMINFO* enumTpXDescript[];\n\n", f);

	fputs("TXDATAINFO* g_tTpEnumDataInfo[XML_TP_TYPE_NUM + XML_LOCAL_TYPE_NUM + 1] = {NULL};\n", f);
	fputs("TXDATAINFO* g_tTpStructDataInfo[XML_TP_STRUCT_NUM + XML_LOCAL_STRUCT_NUM + 1] = {NULL};\n", f);
	fputs("TXENUMINFO* enumTpXDescripTbl[XML_TP_TYPE_NUM + XML_LOCAL_TYPE_NUM + 1] = {NULL};\n\n", f);

	fputs(combineenumfun, f);
	fputs(combinestructfun, f);
	fputs(combineenumtblfun, f);

	fputs(headgetenumfun, f);

	//end namespace 
    fputs("\n} //namespace UmsTpmsg\n", f);
/*	fputs(gettpenumfun, f);*/
	
/*	fputs("#endif //_UMS_XML_STRUCT_H_\n", f);*/

	fclose(f);
	return TRUE;	
}

s8* CStructParser::GetFileName(s8* szFilepath )
{
	if (NULL == szFilepath || 0 == strncmp(szFilepath, "NULL", 4))
	{
		return NULL;
	}

	s8* szfilename = NULL;
	u16 lenth = strlen(szFilepath);
	u16 wI = 0;
	for (wI = 1; wI < lenth + 1; wI++)
	{
		if (0 == strncmp(szFilepath+lenth-wI, "\\", 1))
		{
			wI--;
			szfilename = szFilepath + lenth - wI;
			break;
		}
	}
	if (wI == lenth + 1)
	{
		szfilename = szFilepath;
	}
	return szfilename;
}
