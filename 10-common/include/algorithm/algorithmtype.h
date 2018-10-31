
/*****************************************************************************
   ģ����      : Algorithm type 
   �ļ���      : algorithmType.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: �㷨���㷨�����������Ͷ���
   ����        : ��ѩ��
   �汾        : V3.6  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2005/03/29  3.6         ��ѩ��        ����
   2005/04/15  3.6         ��  ��      �������"mm.h"�ĳ�ͻ
   2005/04/18  3.6         ��  ��      �����ʹ��timing.hʱ��"basictype.h"�ĳ�ͻ
   2005/04/22  3.6         ½ѩ��	   �������u32�ϲ㶨��͵ײ㶨���ͻ����
   2005/04/28  3.6		   ½ѩ��	   �������s32,int32_t, uint32_t�ϲ㶨��͵ײ㶨���ͻ����
   2005/07/07  4.0		   �� ��	   ����Linux��غ궨��(_LINUX_,__KERNEL__)
   2006/02/22  4.0         �� ��       ����TI DM642ƽ̨�궨��(_TMS320C6400)
   2007/09/18  4.0         ������      ����TI DM6446ƽ̨�궨��(_TMS320C6400)
******************************************************************************/
#ifndef _ALGORITHM_TYPE_H_
#define _ALGORITHM_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

/*�Ƽ�ʹ��*/
//modify by huangkui


#ifndef __KERNEL__

	typedef char            s8;            
	typedef short           s16;
	
	typedef unsigned char   u8;   
	typedef unsigned short  u16;	

#endif //not __KERNEL__
//end huangkui

#if  defined _MSC_VER
    typedef unsigned __int64        x64;
    typedef __int64			s64;
    typedef unsigned __int64        u64;
    typedef long           l32;
    #ifndef __KERNEL__
        typedef unsigned long   u32;
    #endif
#elif defined _TMS320C6400
    typedef double          x64;
    typedef long long		s64;
    typedef unsigned long long      u64;
    typedef int            l32;
    typedef unsigned int   u32;
#else
    typedef long long		s64;
    typedef unsigned long long      u64;
    typedef long           l32;
    #ifndef __KERNEL__
        typedef unsigned int   u32;
    #endif
#endif 

typedef double  d64;

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

//add by luxz
#ifndef NULL
  #ifdef  __cplusplus
    #define NULL    0
  #else
    #define NULL    ((void *)0)
  #endif
#endif

#ifdef _MSC_VER
  #define INLINE __inline 
#else
  #define INLINE inline
#endif
//end add



//modify by huangkui
#ifndef _LINUX_

	//typedef int BOOL; //xuchao modify
	#if !defined(TYPE_BOOL) && !defined(__INCvxTypesh)
	typedef int BOOL, *PBOOL;
	#define TRUE 1
	#define FALSE 0
	#define TYPE_BOOL
	#endif /* BOOL */

	#if !defined(TYPE_SCODE)
	typedef int SCODE, *PSCODE;
	#define TYPE_SCODE
	#endif /* SCODE */

	/*Ϊ�����ϰ汾��ʱ���������Ƽ�ʹ��*/
	typedef char             int8_t;            
	typedef short            int16_t;
	//Modify by luxz
	//���ǵ�3.6�У��ϲ㶨��(int)�͵ײ㶨��(long)���Ͳ�ͬ�����±�������
	#ifdef _MSC_VER  
	typedef int             int32_t;
	#else
	typedef long             int32_t;
	#endif
	//End modify
	
	typedef unsigned char    uint8_t;   
	typedef unsigned short   uint16_t;
	
	//Modify by luxz
	//���ǵ�3.6�У��ϲ㶨��(unsigned int)�͵ײ㶨��(unsigned long)���Ͳ�ͬ�����±�������
	#ifdef _MSC_VER  
	typedef unsigned int    uint32_t;
	#else  
	typedef unsigned long    uint32_t;
	#endif
	//End modify
	
	#ifdef _MSC_VER
	typedef unsigned __int64      uint64_t;
	typedef __int64		      int64_t;
	#else 
	typedef unsigned long long    uint64_t;
	typedef long long	      int64_t;
	#endif
	/*Ϊ�����ϰ汾��ʱ���������Ƽ�ʹ��*/ 
	
#endif //not _LINUX_	
//end huangkui

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _ALGORITHM_TYPE_H_ */
