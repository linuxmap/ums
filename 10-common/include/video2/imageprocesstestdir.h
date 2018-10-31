/******************************************************************************
ģ����	    ��imageprocesstestdir                       
�ļ���	    ��imageprocesstestdir.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ�ƴ���ļ�·��
����		��ZouWenyi
�汾		��1.0
-------------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2005/05/10  1.0        ZouWenyi                 ����
******************************************************************************/
//ͼ�����н��в��Ե�֡��
#define TESTNUM 1

#ifndef _IMAGEPROCESSTESTDIR_H_
#define _IMAGEPROCESSTESTDIR_H_

static s8 * ImageProcessStrCat( const s8 *ps8FileName )
{
	static const s8  *ps8Resource = "e:\\testvideo\\";
	static s8 ps8String[1024];
	strcpy( ps8String, ps8Resource );
	return strcat( ps8String, ps8FileName );
}

static s8 * ProcessResultStrCat( const s8 *ps8FileName )
{
#if  defined(OPTIMIZE_FOR_EQUATOR) 
    static const s8  *ps8ResourceResult = "e:\\testvideo\\map_result\\";
#elif defined(OPTIMIZE_FOR_MMX)
    static const s8  *ps8ResourceResult = "e:\\testvideo\\mmx_result\\";
#elif defined(OPTIMIZE_FOR_BLACKFIN)
    static const s8  *ps8ResourceResult = "e:\\testvideo\\blackfin_result\\";
#else 
    static const s8  *ps8ResourceResult = "e:\\testvideo\\c_result\\";
#endif	
	static s8 ps8StringResult[1024];
	strcpy( ps8StringResult, ps8ResourceResult );
    strcat( ps8StringResult, ps8FileName );
	return ps8StringResult;
}

#endif // _IMAGEPROCESSTESTDIR_H_
