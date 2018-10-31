#ifndef RWNEWCFGFILE_H
#define RWNEWCFGFILE_H
#include "cfgdata.h"
#include <stdio.h>
const u16 wFileNameLen = 256;
BOOL  LoadDataFromCfgFile(const s8 szFileName[wFileNameLen]);
BOOL  LoadDataFromCfgFile(FILE* pfFileName);
BOOL  SaveDataToCfgFile(const s8 szFileName[wFileNameLen],const TALLConfigData& tAllConfigData);
BOOL  SaveDataToCfgFile(FILE* pfFileName,const TALLConfigData& tAllConfigData);

#endif
