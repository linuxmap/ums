#ifndef TPRWNEWCFGFILE_H
#define TPRWNEWCFGFILE_H
#include "tpcfgdata.h"
#include <stdio.h>

#define TP_FILENAME_LENGTH  256

/*====================================================================
函 数 名： SaveDataToTpFile
功    能： 将内存数据结构SAVE到会议模版文件中
算法实现： 
全局变量： 
参    数： const s8 szFileName[TP_FILENAME_LENGTH],TTPConfTemplate atTPConfTemplate[TP_CONFTEMPLATE_MAXNUM]
返 回 值： BOOL 成功返回TRUE，失败返回FALSE 
--------------------------------------------------------------------
修改记录：
日  期	      版本		    修改人		走读人    修改内容
2011/7/25     1.0		    胡子龙                   创建
======================================================================*/
BOOL  SaveDataToTpFile( const s8 szFileName[TP_FILENAME_LENGTH], const TConfTemplateLocal atAllConfigData[TP_CONFTEMPLATE_MAXNUM], u16 wNum);

/*====================================================================
函 数 名： SaveDataToTpFile
功    能： 将内存数据结构SAVE到会议模版文件中
算法实现： 
全局变量： 
参    数： FILE* pfFileName,TTPConfTemplate atTPConfTemplate[TP_CONFTEMPLATE_MAXNUM]
返 回 值： BOOL 成功返回TRUE，失败返回FALSE 
--------------------------------------------------------------------
修改记录：
日  期	      版本		    修改人		走读人    修改内容
2011/7/25     1.0		    胡子龙                   创建
======================================================================*/
BOOL  SaveDataToTpFile( FILE* pfFileName, const TConfTemplateLocal atAllConfigData[TP_CONFTEMPLATE_MAXNUM], 
					   u16 wNum, s8* szFileName);

BOOL SaveDataToControlFile(const s8 *szControlFile, const TControlData tControlData);

#endif