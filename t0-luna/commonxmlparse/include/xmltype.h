#ifndef _XML_TYPE_H_
#define _XML_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef int		s32, BOOL32;
typedef unsigned long   u32;
typedef unsigned char	u8;
typedef unsigned short  u16;
typedef short           s16;
typedef char            s8;

#ifndef _MSC_VER
#ifndef LPSTR
#define LPSTR   char *
#endif
#ifndef LPCSTR
#define LPCSTR  const char *
#endif
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif //_XML_TYPE_H_