
#include <stdlib.h>
#include "struct_parse.h"



int main(int argc, char* argv[])
{
	if (7 != argc)
	{
		printf("Error!!! please input parameters correctly!\n");
		system("pause");
		return -1;
	}

	CStructParser* p = new CStructParser;

	printf("\n");

	// 输出文件是argv[3],argv[6]
	for (int i = 3; i < argc; i = i + 3)
	{
		if (!p->CheckFileAttribute(argv[i]))
		{
			system("pause");
			return 1;
		}
	}

	p->Create();

	int ret =  p->GenerateXMLMarshalTable(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
//   
// 	
	printf("\n ret = %d, %s\n\n", ret, Xml_Succeed == ret ? "success" : "ERROR!");


#ifdef _LINUX_
	system( "rm -f filewithout*.txt" );
#else
	system( "del filewithout*.txt" );
#endif
 	system("pause");

	return 0;
}
