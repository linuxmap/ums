#ifndef _TINYXML_EXPORT_H_
#define _TINYXML_EXPORT_H_

#if (defined(WIN32) || defined(_WIN32) ) && !defined(TINYXML_STATICLIB)

	#ifdef _TINYXML_EXP_
		#define TINYXML_API __declspec(dllexport)
	#else
		#define TINYXML_API __declspec(dllimport)
	#endif

#else  // ����ƽ̨�ģ������Ǿ�̬����

	#define TINYXML_API 

#endif

#endif //_TINYXML_EXPORT_H_
