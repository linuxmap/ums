#include <sys/stat.h>
#include <time.h>
#include "struct_parse.h"

char TimeString[64] = {0};

CStructParser::CStructParser()
{
	m_nTpenumCount = 0;
/*	m_nUmsenumCount = 0;*/
	m_nTpStructCount = 0;
/*	m_nUmsStructCount = 0;*/

	m_ptTpenumArray = NULL;
/*	m_ptUmsenumArray = NULL;*/
	m_ptTpStructArray = NULL;
/*	m_ptUmsStructArray =NULL;*/
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
	m_ptTpenumArray = new TEnum[1024];
	if (!m_ptTpenumArray)
	{
		return err_memory_exception;
	}

	m_ptTpStructArray = new TStruct[1024];
	if (!m_ptTpStructArray)
	{
		return err_memory_exception;
	}

	memset(m_ptTpenumArray, 0, sizeof(TEnum)*1024);
	memset(m_ptTpStructArray, 0, sizeof(TStruct)*1024);

	time_t curtime;
	time(&curtime);
	struct tm *UTCTime;
	UTCTime = gmtime(&curtime);

	sprintf(TimeString, "%d-%d-%d %d:%d:%d",
		(1900+UTCTime->tm_year), (1+UTCTime->tm_mon), UTCTime->tm_mday,
		8+UTCTime->tm_hour, UTCTime->tm_min, UTCTime->tm_sec);
	printf("\ntpcommonxmltype.h and tpcommonxmlstruct.h version_time: %s\n\n", TimeString);

	return Xml_Succeed;
}


u32 CStructParser::GenerateXMLMarshalTable(const char* pszIntptype, 
		const char* pszOuttptype,
		const char* pszIntpstruct,
		const char* pszOuttpsruct)
{
	if ( !MakeFileWithoutComment(pszIntpstruct, FileWithoutComment_tpstruct)
		|| !MakeFileWithoutComment(pszIntptype, FileWithoutCOmment_tptype))
	{
		return err_file_del_comment_failed;
	}

	if ( !WipeOfftmp(FileWithoutComment_tpstruct, FileWithoutBrace1_tpstruct)
		|| !WipeOfftmp(FileWithoutCOmment_tptype, FileWithoutBrace1_tptype))
	{
		return err_file_del_brace_failed;
	}
	
	if ( !WipeOffBrace(FileWithoutBrace1_tpstruct, FileWithoutBrace2_tpstruct)
		|| !WipeOffBrace(FileWithoutBrace1_tptype, FileWithoutBrace2_tptype))
	{
		return err_file_del_brace_failed;
	}

	if ( !WipeOffKeyWordAndFunction(FileWithoutBrace2_tpstruct, FileWithoutKeyAndFunc_tpstruct)
		|| !WipeOffKeyWordAndFunction(FileWithoutBrace2_tptype, FileWithoutKeyAndFunc_tptype))
	{
		return err_file_del_key_and_func_failed;
	}


	PickTpEnum(FileWithoutKeyAndFunc_tptype);
	PickTpStruct(FileWithoutKeyAndFunc_tpstruct);

// 	PrintEnum();
// 	PrintStruct();

	if (!MakeXmlTpType(pszOuttptype))
	{
		return err_make_type_ex_file_failed;
	}

	if (!MakeXmlTpStruct(pszOuttpsruct))
	{
		return err_make_struct_cpp_file_failed;
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

	printf("The first common enum name: %s\n", m_ptTpenumArray[0].name);
	printf("The last common enum name: %s\n\n", m_ptTpenumArray[m_nTpenumCount-1].name);

// 	for( int i=0 ; i< m_nTpenumCount ;i++)
// 	{
// 		if (0 == i || m_nTpenumCount-1 == i)
// 		{
// 			printf("%s\n",m_ptTpenumArray[i].name);
// 		}
// 	}	

	RelaseFile();
	return Xml_Succeed;
}


// u32  CStructParser::PickUmsEnum(const char* filename)
// {
// 	if ( !LoadFile( filename ) )
// 		return err_file_open_failed;
// 	
// 	BOOL32 bEnumStart = FALSE;
// 	BOOL32 bStructStart = FALSE;
// 	while ( ReadLine(m_achLine, sizeof(m_achLine)) > 0 )
// 	{
// 		if ( 0 == strncmp( "enum", GetKey(1), 4 ) )
// 		{
// 			strcpy(m_ptUmsenumArray[m_nUmsenumCount].name, GetKey(2));			
// 			m_ptUmsenumArray[m_nUmsenumCount].count=0;
// 			bStructStart = FALSE;
// 			continue;
// 		}
// 		else if ( 0 == strncmp( "struct", GetKey(1), 4 ) )
// 		{
// 			bStructStart = TRUE;
// 			continue;
// 		}
// 		
// 		if ( bStructStart )
// 		{
// 			continue;
// 		}
// 		
// 		if ( bEnumStart )
// 		{
// 			char* pKey1 = GetKey(1);
// 			if ( strfind( pKey1, '{' ) )
// 			{
// 				RelaseFile();
// 				return err_enum_format_invalid;
// 			}
// 			
// 			if ( strfind( pKey1, '}' ) )
// 			{
// 				m_nUmsenumCount++;
// 				bEnumStart = FALSE;
// 				continue;
// 			}
// 			
// 			if ( !IsEmptyString(pKey1) )
// 			{
// 				strcpy( m_ptUmsenumArray[m_nUmsenumCount].element[m_ptUmsenumArray[m_nUmsenumCount].count], pKey1 );
// 				m_ptUmsenumArray[m_nUmsenumCount].count++;
// 			}
// 		}
// 		else
// 		{
// 			char* pKey1 = GetKey(1);
// 			if ( strfind( pKey1, '}' ) )
// 			{
// 				RelaseFile();
// 				return err_enum_format_invalid;
// 			}
// 			
// 			if ( strfind( pKey1, '{' ) )
// 			{
// 				bEnumStart = TRUE;
// 				continue;
// 			}
// 		}
// 	}
// 	
// 	
// 	for( int i=0 ;i < m_nUmsenumCount ;i++)
// 	{
// 		if (0 == i || m_nUmsenumCount-1 == i)
// 		{
// 			printf("%s\n",m_ptUmsenumArray[i].name);
// 		}
// 	}	
// 	
// 	RelaseFile();
// 	return Xml_Succeed;
// }


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
	
	printf("The first struct name: %s\n", m_ptTpStructArray[0].name);
	printf("The last struct name: %s\n", m_ptTpStructArray[m_nTpStructCount-1].name);

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

// u32 CStructParser::PickUmsStruct(const char* filename)
// {
// 	if ( !LoadFile( filename ) )
// 		return err_file_open_failed;
// 
// 	BOOL32 bStructStart = FALSE;
// 	BOOL32 bStruct = TRUE;
// 	while ( ReadLine(m_achLine, sizeof(m_achLine)) > 0 )
// 	{
// 		if ( IsEmptyString( m_achLine ) )
// 			continue;
// 
// 		//此处代码对存在enum的情况无能为力
// 		if ( 0 == strncmp( "typedef", GetKey(1), 6 ) )
// 		{
// 			if ( 0 == strncmp( "struct", GetKey(2), 6 ) )
// 			{
// 				bStruct = TRUE;
// 				char* pStructName = GetKey( 3 );
// 				if ( 0 == strncmp(pStructName, "tag", 3) )
// 				{
// 					m_ptUmsStructArray[m_nUmsStructCount].count=0;
// 					strcpy(m_ptUmsStructArray[m_nUmsStructCount].name, &pStructName[3]);
// 				}
// 				else
// 				{
// // 					RelaseFile();
// // 					return err_struct_format_invalid;
// 					//mtstruct.h中有不使用tag开头定义的结构，特殊处理，不做错误返回
// 					m_ptUmsStructArray[m_nUmsStructCount].count=0;
// 					strcpy(m_ptUmsStructArray[m_nUmsStructCount].name, &pStructName[0]);
// 				}
// 			}
// 			else
// 			{
// 				RelaseFile();
// 				return err_struct_format_invalid;
// 			}
// 		}
// 		else if ( 0 == strncmp( "template", GetKey(1), 8) )
// 		{
// 			bStruct = FALSE;
// 			continue;
// 		}
// 
// 		if ( bStruct )
// 		{
// 			if ( bStructStart )
// 			{
// 				char* pKey1 = GetKey(1);
// 				if ( strfind( pKey1, '{' ) )
// 				{
// 					RelaseFile();
// 					return err_enum_format_invalid;
// 				}
// 				
// 				if ( strfind( pKey1, '}' ) )
// 				{
// 					m_nUmsStructCount++;
// 					bStructStart = FALSE;
// 					continue;
// 				}
// 				
// 				if ( !IsEmptyString(pKey1) )
// 				{
// 					strcpy( m_ptUmsStructArray[m_nUmsStructCount].member[m_ptUmsStructArray[m_nUmsStructCount].count].type, GetKey(1) );
// 					char* pszName = GetKey(2);
// 					char* p = pszName;
// 					BOOL32 bIsArray = FALSE;
// 					u8 count = 0;
// 					while( (*pszName++) != 0 )
// 					{
// 						if( *pszName == '[')
// 							count++;
// 					}
// 					
// 					pszName = p;
// 					while( (*pszName++) != 0 )
// 					{
// 						if( *pszName == '[' || *pszName == ';' )
// 						{
// 							*pszName = 0;
// 							break;
// 						}
// 					}
// 					if ( count == 2 )
// 						bIsArray = TRUE;
// 					strcpy( m_ptUmsStructArray[m_nUmsStructCount].member[m_ptUmsStructArray[m_nUmsStructCount].count].member, p );
// 					m_ptUmsStructArray[m_nUmsStructCount].member[m_ptUmsStructArray[m_nUmsStructCount].count].bIsArray = bIsArray;
// 					m_ptUmsStructArray[m_nUmsStructCount].count++;
// 				}
// 			} 
// 			else
// 			{
// 				char* pKey1 = GetKey(1);
// 				if ( strfind( pKey1, '}' ) )
// 				{
// // 					RelaseFile();
// // 					return err_enum_format_invalid;
// 				}
// 				
// 				if ( strfind( pKey1, '{' ) )
// 				{
// 					bStructStart = TRUE;
// 					continue;
// 				}
// 
// 				if (pKey1 = strfind(m_achLine, ':'))
// 				{
// 					char* pKey2 = GetKey(pKey1+1, 1);
// 					if ( 0 != strncmp( "public", pKey2, 6 ) )
// 					{
// 						RelaseFile();
// 						return err_enum_format_invalid;
// 					}
// 
// 					pKey2 = GetKey(pKey1+1, 2);
// 					if ( IsEmptyString(pKey2) )
// 					{
// 						RelaseFile();
// 						return err_enum_format_invalid;
// 					}
// 					
// 					int x = strncmp("abc", "def", 3);
// 
// 					int iTmpKeyLen = strlen(pKey2);
// 					for (int iTmp = 0; iTmp < m_nUmsStructCount-1; ++iTmp)
// 					{
// 						if (0 == strncmp(m_ptUmsStructArray[iTmp].name, pKey2, iTmpKeyLen))
// 						{
// 							memcpy(m_ptUmsStructArray[m_nUmsStructCount].member, m_ptUmsStructArray[iTmp].member, m_ptUmsStructArray[iTmp].count*sizeof(TStructMember));
// 							m_ptUmsStructArray[m_nUmsStructCount].count = m_ptUmsStructArray[iTmp].count;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 		}		
// 	}
// 	
// 	for( int i=0 ;i< m_nUmsStructCount ;i++)
// 	{
// 		if (0 == i || m_nUmsStructCount-1 == i)
// 		{
// 			printf("%s\n",m_ptUmsStructArray[i].name);
// 		}
// 	}
// 
// 	RelaseFile();
// 	return Xml_Succeed;
// }

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

// static char xmlhead[]={"\
//  \n\
// #define TpEnumIdString(type, index) index, GetTpEnumString(emx_##type, index)\n\
// #define TpEnumString(type, index) GetTpEnumString(emx_##type, index)\n\
// s8* GetTpEnumString(u16 wType, u16 wIndex);\n"};

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


// static char headstruct1[]={"\
// #include \"tpstruct.h\"\n\
// #include \"umscommonstruct.h\"\n\
// #include \"xmlengine.h\"\n\
// #include \"msgmgr.h\"\n\
// #include \"umsxmltype.h\"\n"};

static char headstruct1[]={"\
#include \"xmlengine.h\"\n\
#include \"msgmgr.h\"\n\
#include \"tpcommontype.h\"\n\
#include \"tpcommonstruct.h\"\n\
#include \"tpcommonxmltype.h\"\n"};

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


// static char headgetenumfun[]={"\
// s8* GetTpEnumString(u16 type, u16 index)\n\
// {\n\
// \tu16 wTmpType = type - _placeholder_emxEnumTypeBegin - 1;\n\
// \tif (wTmpType > sizeof(enumTpXDescripTbl)/sizeof(enumTpXDescripTbl[0]))\n\
// \t\treturn \"DefaultType\";\n\
// \t\n\
// \tTXENUMINFO* pEnumInfo = enumTpXDescripTbl[wTmpType];\n\
// \twhile(NULL != pEnumInfo->descrip)\n\
// \t{\n\
// \t\tif (pEnumInfo->val == index)\n\
// \t\t\treturn pEnumInfo->descrip;\n\
// \t\tpEnumInfo++;\n\
// \t}\n\
// \treturn \"DefaultIndex\";\n\
// }\n\
// \n"};

// static char combineenumfun[] = {"\
// TXDATAINFO** CombineEnumDateInfo(void)\n\
// {\n\
// \tmemcpy(g_tTpEnumDataInfo, g_tTpEnumData, sizeof(g_tTpEnumData));\n\
// \tmemcpy(g_tTpEnumDataInfo + XML_TP_TYPE_NUM, g_tUmsEnumDataInfo, sizeof(g_tUmsEnumDataInfo));\n\
// \treturn g_tTpEnumDataInfo;\n\
// }\n\
// \n"};
// 
// static char combinestructfun[] = {"\
// TXDATAINFO** CombineStructDateInfo(void)\n\
// {\n\
// \tmemcpy(g_tTpStructDataInfo, g_tTpStructData, sizeof(g_tTpStructData));\n\
// \tmemcpy(g_tTpStructDataInfo + XML_TP_STRUCT_NUM, g_tUmsStructDataInfo, sizeof(g_tUmsStructDataInfo));\n\
// \treturn g_tTpStructDataInfo;\n\
// }\n\
// \n"};
// 
// static char gettpenumfun[] = {"\
// s8* GetTpEnumString(u16 type, u16 index)\n\
// {\n\
// \tu16 wTmpType = type - _placeholder_emxEnumTypeBegin - 1;\n\
// \tif (wTmpType >= (XML_TP_TYPE_NUM + XML_UMS_TYPE_NUM))\n\
// \t{\n\
// \t\treturn \"DefaultType\";\n\
// \t}\n\
// \telse if (wTmpType >= XML_TP_TYPE_NUM)\n\
// \t{\n\
// \t\twTmpType = wTmpType - XML_TP_TYPE_NUM;\n\
// \t\tTXENUMINFO* pEnumInfo = enumUmsXDescripTbl[wTmpType];\n\
// \t\twhile (NULL != pEnumInfo->descrip)\n\
// \t\t{\n\
// \t\t\tif (pEnumInfo->val == index)\n\
// \t\t\t\treturn pEnumInfo->descrip;\n\
// \t\t\tpEnumInfo++;\n\
// \t\t}\n\
// \t\treturn \"DefaultIndex\";\n\
// \t}\n\
// \telse\n\
// \t{\n\
// \t\tTXENUMINFO* pEnumInfo = enumTpXDescript[wTmpType];\n\
// \t\twhile (NULL != pEnumInfo->descrip)\n\
// \t\t{\n\
// \t\t\tif (pEnumInfo->val == index)\n\
// \t\t\t\treturn pEnumInfo->descrip;\n\
// \t\t\tpEnumInfo++;\n\
// \t\t}\n\
// \t\treturn \"DefaultIndex\";\n\
// \t}\n\
// }\n\
// \n"};

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

	//namespace
    fputs("\nnamespace UmsTpmsg {\n", f);
	
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
		sprintf(line, "\t{ (char*)NULL, (int)-1 }\n};\n");
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
	
	// end namespace 
	fputs("\n} //namespace UmsTpmsg\n",f);

	fputs("#endif //_TP_COMMON_XML_STRUCT_H_\n", f);

	fclose(f);
	return TRUE;	
}

// BOOL32  CStructParser::MakeXmlUmsStruct( const char* filename )
// {
// 	int i = 0;
// 	int j = 0;
// 	char line[256] = {0};
// 	
// 	FILE* f = fopen(filename ,"wt");
// 	if (NULL == f)
// 	{
// 		return FALSE;
// 	}
// // 	
// // 	fputs("#ifndef _UMS_XML_STRUCT_H_\n", f);
// // 	fputs("#define _UMS_XML_STRUCT_H_\n\n",f);
// 
// 
// /*	fputs(headstruct1, f);*/
// 	fputs("#include \"tpcommonxmlstruct.h\"\n", f);
// 	
// 	sprintf(line, "\nconst char XmlUmsStructVersion[] = \"%s\";\n\n", TimeString);
// 	fputs(line, f);
// 
// 	sprintf(line, "#define XML_UMS_TYPE_NUM      %d\n", m_nUmsenumCount);
// 	fputs(line, f);
// 	
// 	sprintf(line, "#define XML_UMS_STRUCT_NUM    %d\n", m_nUmsStructCount);
// 	fputs(line, f);
// 
// // 	fputs("char* GetTpXmlStructVer()\n",f);
// // 	fputs("{\n\treturn (char*)XmlStructVersion;\n}\n",f);
//     
// /*	fputs(headstruct, f);*/
// 	
// 	for(i = 0; i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\nENUMTYPE(%s);", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 	}
// 	
// 	fputs("\n\nTXDATAINFO* g_tUmsEnumDataInfo[]={\n", f);
// 	for(i = 0; i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 	}
// 	fputs("\t(TXDATAINFO*)NULL\n};\n", f);
// 	
// 	//数据结构
// 	for(i = 0; i < m_nUmsStructCount; i++)
// 	{
// 		sprintf(line, "\n//%s\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 		sprintf(line, "TYPESTRUCT_BEGIN( %s )\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 		
// 		for(j = 0; j < m_ptUmsStructArray[i].count; j++)
// 		{
// 			if (m_ptUmsStructArray[i].member[j].bIsArray)
// 			{
// 				sprintf(line, "    TYPESTRUCT_MATRIX( %s, %s, %s )\n", m_ptUmsStructArray[i].name
// 					,m_ptUmsStructArray[i].member[j].type 
// 					,m_ptUmsStructArray[i].member[j].member);
// 			}
// 			else
// 			{
// 				sprintf(line, "    TYPESTRUCT_MEMBER( %s, %s, %s )\n", m_ptUmsStructArray[i].name
// 					,m_ptUmsStructArray[i].member[j].type 
// 					,m_ptUmsStructArray[i].member[j].member);
// 			}
// 			
// 			fputs(line, f);
// 		}
// 		sprintf(line, "TYPESTRUCT_END(  %s )\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 	}
// 	
// 	fputs("\n//通讯数据结构编码表\n", f);
// 	fputs("TXDATAINFO* g_tUmsStructDataInfo[]={\n", f);
// 	for(i = 0; i < m_nUmsStructCount; i++)
// 	{
// 		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 	}
// 	fputs("\t(TXDATAINFO*)NULL\n};\n", f);
// 	
// 	//枚举类型
// 	for(i=0; i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\nconst TXENUMINFO enum%sDescript[]={\n", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 		for(j = 0; j < m_ptUmsenumArray[i].count;j++)
// 		{
// 			sprintf(line, "\t{ \"%s\", (int)%s },\n", m_ptUmsenumArray[i].element[j], m_ptUmsenumArray[i].element[j]);
// 			fputs(line, f);
// 		}
// 		sprintf(line, "\t{ (char*)NULL, (int)-1 }\n};\n", m_ptUmsenumArray[i].element[j], m_ptUmsenumArray[i].element[j]);
// 		fputs(line, f);
// 	}
// 	
//     fputs("\n//枚举描述字符串表\n",f);
//     fputs("TXENUMINFO* enumUmsXDescripTbl[]={\n", f);
// 	for(i = 0;i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\t(TXENUMINFO*)enum%sDescript, \n", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 	}
// 	fputs("\t(TXENUMINFO*)NULL\n};\n\n", f);
// 	
// // 	fputs("extern TXDATAINFO* g_tTpEnumData[];\n", f);
// // 	fputs("extern TXDATAINFO* g_tTpStructData[];\n", f);
// // 	fputs("extern TXENUMINFO* enumTpXDescript[];\n\n", f);
// 
// 	fputs("TXDATAINFO* g_tTpEnumDataInfo[XML_TP_TYPE_NUM + XML_UMS_TYPE_NUM + 1] = {0};\n", f);
// 	fputs("TXDATAINFO* g_tTpStructDataInfo[XML_TP_STRUCT_NUM + XML_UMS_STRUCT_NUM + 1] = {0};\n\n", f);
// 
// 	fputs(combineenumfun, f);
// 	fputs(combinestructfun, f);
// 	fputs(gettpenumfun, f);
// 	
// /*	fputs("#endif //_UMS_XML_STRUCT_H_\n", f);*/
// 
// 	fclose(f);
// 	return TRUE;	
// }
// 
// BOOL32  CStructParser::MakeXmlCnsStruct( const char* filename )
// {
// 	int i = 0;
// 	int j = 0;
// 	char line[256] = {0};
// 	
// 	FILE* f = fopen(filename ,"wt");
// 	if (NULL == f)
// 	{
// 		return FALSE;
// 	}
// // 	
// // 	fputs("#ifndef _UMS_XML_STRUCT_H_\n", f);
// // 	fputs("#define _UMS_XML_STRUCT_H_\n\n",f);
// 
// 
// /*	fputs(headstruct1, f);*/
// 	fputs("#include \"tpcommonxmlstruct.h\"\n", f);
// 	
// 	sprintf(line, "\nconst char XmlCnsStructVersion[] = \"%s\";\n\n", TimeString);
// 	fputs(line, f);
// 
// 	sprintf(line, "#define XML_CNS_TYPE_NUM      %d\n", m_nUmsenumCount);
// 	fputs(line, f);
// 	
// 	sprintf(line, "#define XML_CNS_STRUCT_NUM    %d\n", m_nUmsStructCount);
// 	fputs(line, f);
// 
// // 	fputs("char* GetTpXmlStructVer()\n",f);
// // 	fputs("{\n\treturn (char*)XmlStructVersion;\n}\n",f);
//     
// /*	fputs(headstruct, f);*/
// 	
// 	for(i = 0; i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\nENUMTYPE(%s);", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 	}
// 	
// 	fputs("\n\nTXDATAINFO* g_tUmsEnumDataInfo[]={\n", f);
// 	for(i = 0; i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 	}
// 	fputs("\t(TXDATAINFO*)NULL\n};\n", f);
// 	
// 	//数据结构
// 	for(i = 0; i < m_nUmsStructCount; i++)
// 	{
// 		sprintf(line, "\n//%s\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 		sprintf(line, "TYPESTRUCT_BEGIN( %s )\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 		
// 		for(j = 0; j < m_ptUmsStructArray[i].count; j++)
// 		{
// 			if (m_ptUmsStructArray[i].member[j].bIsArray)
// 			{
// 				sprintf(line, "    TYPESTRUCT_MATRIX( %s, %s, %s )\n", m_ptUmsStructArray[i].name
// 					,m_ptUmsStructArray[i].member[j].type 
// 					,m_ptUmsStructArray[i].member[j].member);
// 			}
// 			else
// 			{
// 				sprintf(line, "    TYPESTRUCT_MEMBER( %s, %s, %s )\n", m_ptUmsStructArray[i].name
// 					,m_ptUmsStructArray[i].member[j].type 
// 					,m_ptUmsStructArray[i].member[j].member);
// 			}
// 			
// 			fputs(line, f);
// 		}
// 		sprintf(line, "TYPESTRUCT_END(  %s )\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 	}
// 	
// 	fputs("\n//通讯数据结构编码表\n", f);
// 	fputs("TXDATAINFO* g_tUmsStructDataInfo[]={\n", f);
// 	for(i = 0; i < m_nUmsStructCount; i++)
// 	{
// 		sprintf(line, "\t(TXDATAINFO*)%smembertable,\n", m_ptUmsStructArray[i].name);
// 		fputs(line, f);
// 	}
// 	fputs("\t(TXDATAINFO*)NULL\n};\n", f);
// 	
// 	//枚举类型
// 	for(i=0; i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\nconst TXENUMINFO enum%sDescript[]={\n", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 		for(j = 0; j < m_ptUmsenumArray[i].count;j++)
// 		{
// 			sprintf(line, "\t{ \"%s\", (int)%s },\n", m_ptUmsenumArray[i].element[j], m_ptUmsenumArray[i].element[j]);
// 			fputs(line, f);
// 		}
// 		sprintf(line, "\t{ (char*)NULL, (int)-1 }\n};\n", m_ptUmsenumArray[i].element[j], m_ptUmsenumArray[i].element[j]);
// 		fputs(line, f);
// 	}
// 	
//     fputs("\n//枚举描述字符串表\n",f);
//     fputs("TXENUMINFO* enumUmsXDescripTbl[]={\n", f);
// 	for(i = 0;i < m_nUmsenumCount; i++)
// 	{
// 		sprintf(line, "\t(TXENUMINFO*)enum%sDescript, \n", m_ptUmsenumArray[i].name);
// 		fputs(line, f);
// 	}
// 	fputs("\t(TXENUMINFO*)NULL\n};\n\n", f);
// 	
// // 	fputs("extern TXDATAINFO* g_tTpEnumData[];\n", f);
// // 	fputs("extern TXDATAINFO* g_tTpStructData[];\n", f);
// // 	fputs("extern TXENUMINFO* enumTpXDescript[];\n\n", f);
// 
// 	fputs("TXDATAINFO* g_tTpEnumDataInfo[XML_TP_TYPE_NUM + XML_UMS_TYPE_NUM + 1] = {0};\n", f);
// 	fputs("TXDATAINFO* g_tTpStructDataInfo[XML_TP_STRUCT_NUM + XML_UMS_STRUCT_NUM + 1] = {0};\n\n", f);
// 
// 	fputs(combineenumfun, f);
// 	fputs(combinestructfun, f);
// 	fputs(gettpenumfun, f);
// 	
// /*	fputs("#endif //_UMS_XML_STRUCT_H_\n", f);*/
// 
// 	fclose(f);
// 	return TRUE;	
// }