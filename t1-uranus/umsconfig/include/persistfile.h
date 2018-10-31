
#ifndef PERSISTFILE_H
#define PERSISTFILE_H

#include "osp.h"
#include "kdvsys.h"
#include <string.h>
#include "kdvtype.h"
#include "tpsys.h"

const u8 CHECK_STRING_LEN = 20;

#ifdef WIN32
#pragma  pack(push)
#pragma  pack(1)
#endif

struct tagBlockHeader
{
    u32 dwBlockSize;
    u32 dwStatus;
    char achVersion[40];
	char achCheckString[CHECK_STRING_LEN];
	u8 byCheckCode;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifdef WIN32
#pragma  pack(pop)
#endif
typedef struct tagBlockHeader _TBLOCKHEADER;
typedef struct tagBlockHeader *PTBLOCKHEADER;

class CCfgDataManager
{
public:
	CCfgDataManager();
    virtual ~CCfgDataManager();
public:
	BOOL InitConfigure( s8 *pbyFilePath );
    BOOL SaveData( u8 *pbyData, u32 dwLen );	
	void EraseRawDisk();
	void ShowCurrentSection();
	int  GetSectionSize();
	u8   GetSectionId(){return m_byCurSecId;}
	void GetSavedFileName(s8 achFilePath[MAX_PATH])
		{
			strncpy(achFilePath,m_achFilePath,sizeof(m_achFilePath));
		}
protected:
	enum {DEFAULT_BLOCK_SIZE = 16*1024,MAX_SETION_SIZE = 128*1024};
	enum {SECTION_NUM = 2,SECTION_TWO = 1,SECTION_ONE  = 0};
	enum {USEFUL_SECTION = 1,UNUSEFUL_SECTION = 2};
	void MAKE_CHECK_STRING( char* const szBuffer, u32 dwValue1, u32 dwValue2 ) 
	{
        sprintf( szBuffer, "%8x&%8x", dwValue1, dwValue2 );
	}
protected:
	u32 ReadData( u8 bySection, u8* pbyData, u32 dwLen);
	u32 WriteData( u8 bySection, u8* pbyData, u32 dwLen );
    BOOL CreateCfgFile( char * pbyFileName );
    BOOL Setup( u8 bySection );   
	void UpdateCurSectionId();
private:
	BOOL AllocBlockMem();
	void GetSectionStatus();
	BOOL ProcessTwoSections();
	BOOL ProcessFirstSection();
	BOOL ProcessSecondSection();
	
	u32 WriteDataT2( u8 bySection, u8* pbyData, u32 dwLen );
	u32 ReadDataT2( u8 bySection, u8* pbyData, u32 dwLen );
private:
    _TBLOCKHEADER   m_atBlockHeader[SECTION_NUM];      // 分区头信息
    u8  m_aStnStatus[SECTION_NUM];                     // 分区好坏状况1
	u8  m_byCurSecId;                                  // 当前分区
	s8  m_achFilePath[MAX_PATH];                       // 配置文件路径
	BOOL m_bInited;                                    // 初始化标志
	BOOL m_bValid;                                     // 数据有效
	u8 *m_pbyBlockMem;								//块内存
 	u32 m_dwBlockSize;								//块内存大小
};
//是否显示配置文件信息
API void ShowCfgInfo(void);
//显示写进rawdisk中的内存数据
API void ShowRawDisk(void);
#endif
