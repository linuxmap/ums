/*******************************************************************************
 *  模块名   :                                                                 *
 *  文件名   : persistfile.cpp                                       *
 *  相关文件 :                                                                 *
 *  实现功能 :                                                                 *
 *  作者     :                                                           *
 *  版本     : V4.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  修改记录:                                                                  *
 *    日  期      版本        修改人      修改内容                             *
 *  2005/8/26  1.0         张 飞          文件系统判断         *
 *                                                                             *
 *******************************************************************************/

#include "tppersistfile.h"
#include "tprwnewcfgfile.h"
#include <stdlib.h>
#include "tpcrc.h"
#include "string.h"
#include "tplog.h"
#include "umsconfig.h"
#include "umsobject.h"
#include "tpinfo.h"

#ifdef _VXWORKS_
#include "fpdrvlib.h"
#endif

#ifdef _LINUX_
#include "brdwrapper.h"
#include "nipwrapper.h"
#include <sys/stat.h>
#endif


#define MTCFG_0 "/usr/0templatecfg/templatecfg_"
#define MTCFG_1 "/usr/1templatecfg/templatecfg_"

#define MTCTL_0 "/usr/0templatecfg/control.ini"
#define MTCTL_1 "/usr/1templatecfg/control.ini"

//用数组维护---huzilong
CTpCfgDataManager g_cTpCfgDataMan[TP_CONFTEMPLATE_MAXNUM];

CTpCfgDataManager g_cTpControlDataMan;

CTpCfgDataManager::CTpCfgDataManager()
{
	m_bInited = FALSE;
	m_bValid  = FALSE;
	m_pbyBlockMem = NULL;
 	m_dwBlockSize  = DEFAULT_BLOCK_SIZE;
	m_aStnStatus[0] = UNUSEFUL_SECTION;
	m_aStnStatus[1] = UNUSEFUL_SECTION;
	m_wSeqNum = TP_INVALID_INDEX;
}

CTpCfgDataManager::~CTpCfgDataManager()
{
	if ( m_pbyBlockMem )
	   free( m_pbyBlockMem );
	m_pbyBlockMem = NULL;
}
	
/*====================================================================
  函 数 名： AllocBlockMem
  功    能： 
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/7/19      1.0		    张 飞                   创建
======================================================================*/
BOOL CTpCfgDataManager::AllocBlockMem()
{
    if(NULL == m_pbyBlockMem)
	{
		m_pbyBlockMem = (u8*)malloc(m_dwBlockSize);
		if(NULL == m_pbyBlockMem)
		{
			MdlError(Ums_Mdl_Cfg,("[AllocBlockMem]: alloc memery failled\n"));
			return FALSE;
		}
		memset(m_pbyBlockMem, 0, m_dwBlockSize);
	} 	
		tpHintNoFile(Ums_Mdl_Cfg,"[AllocBlockMem]: alloc memery success:%d\n",m_dwBlockSize);
	return TRUE;
}
/*====================================================================
  函 数 名： GetSectionStatus
  功    能： 
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/7/19      1.0		    张 飞                   创建
======================================================================*/
void CTpCfgDataManager::GetSectionStatus()
{	
    // 查看分区损坏情况
	memset(&m_atBlockHeader, 0, sizeof(m_atBlockHeader));
    for(u8 i=0; i < SECTION_NUM; i++)
	{
		u16 wBlockHeadSize = sizeof(_TTPBLOCKHEADER );
		u32 nReadLen = ReadData(i, (u8*)&m_atBlockHeader[i], wBlockHeadSize);
        if (nReadLen == wBlockHeadSize) 
		{
			tpHintNoFile(Ums_Mdl_Cfg,"[GetSectionStatus], GetSectionStatus: Section %d read success\n",i);
            m_aStnStatus[i] = USEFUL_SECTION;
		}
		else
		{		
			m_aStnStatus[i] = UNUSEFUL_SECTION;
			msgprint( "[CTpCfgDataManager::GetSectionStatus], Section %d read fail\n", i);
		}
	}
}
/*====================================================================
  函 数 名： ProcessTwoSections
  功    能： 
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/7/19      1.0		    张 飞                   创建
======================================================================*/
BOOL CTpCfgDataManager::ProcessTwoSections()
{
	tpHintNoFile(Ums_Mdl_Cfg,"[CCfgDataManager], ProcessTwoSections !\n");

	// 优先读取最新的配置信息
	if ( m_atBlockHeader[SECTION_TWO].dwStatus - 1 == m_atBlockHeader[SECTION_ONE].dwStatus )
	{
		BOOL bSetup = Setup( SECTION_TWO );
		if (bSetup)
		{
			m_byCurSecId = SECTION_TWO;
			return TRUE;
		}

		bSetup = Setup( SECTION_ONE );
		if (bSetup)
		{
			m_byCurSecId = SECTION_ONE;
			return TRUE;
		}
	}
	else
	{
		BOOL bSetup = Setup( SECTION_ONE );
		if (bSetup)
		{   
			m_byCurSecId = SECTION_ONE;
			return TRUE;
		}

		bSetup = Setup( SECTION_TWO );
		if (bSetup)
		{
			m_byCurSecId = SECTION_TWO;
			return TRUE;
		}
	}

	m_byCurSecId = SECTION_ONE;
	tpHintNoFile(Ums_Mdl_Cfg,"[MTCFGDATA][InitConfigure]: Setup file error %d\n",__LINE__);
	return FALSE;
}
/*====================================================================
  函 数 名： ProcessFirstSection
  功    能： 
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/7/19      1.0		    张 飞                   创建
======================================================================*/
BOOL CTpCfgDataManager::ProcessFirstSection()
{
	tpHintNoFile(Ums_Mdl_Cfg,"[CCfgDataManager], ProcessFirstSection !\n");

	m_byCurSecId = SECTION_ONE;
	BOOL bSetup = Setup( SECTION_ONE );
    if(!bSetup)
		MdlError(Ums_Mdl_Cfg,("[CCfgDataManager],ProcessFirstSection, Setup file error %d\n",__LINE__));
	return bSetup;
}
/*====================================================================
  函 数 名： ProcessSecondSection
  功    能： 
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL 
  --------------------------------------------------------------------
  修改记录：
  日  期	      版本		    修改人		走读人    修改内容
  2006/7/19      1.0		    张 飞                   创建
======================================================================*/
BOOL CTpCfgDataManager::ProcessSecondSection()
{
	tpHintNoFile(Ums_Mdl_Cfg,"[CCfgDataManager], ProcessSecondSection !\n");

	m_byCurSecId = SECTION_TWO;
	BOOL bSetup = Setup( SECTION_TWO );
	if(!bSetup)
		MdlError(Ums_Mdl_Cfg,("[CCfgDataManager], ProcessSecondSection : Setup file error %d\n",__LINE__));
	return bSetup;
}

/*=============================================================================
函 数 名：InitConfigure
功    能：初始化数据管理模块
注    意：
算法实现：
全局变量：
输入参数：pbyFilePath 配置文件路径
          
   
输出参数：
          
返 回 值：成功返回TRUE，失败返回FALSE
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
BOOL CTpCfgDataManager::InitConfigure( s8 *pbyFilePath, u16 wIndex ) 
{
	s8 achFileName[TP_FILENAME_LENGTH] = {0};
	if(TP_INVALID_INDEX == wIndex)
	{
		//控制文件
		m_wSeqNum = TP_INVALID_INDEX;
		strncpy(achFileName, pbyFilePath, sizeof(achFileName));

	}
	else
	{
		//对应_1到_128各模版文件
		m_wSeqNum = wIndex+1;
		sprintf(achFileName, "%s%d.ini", pbyFilePath, m_wSeqNum);
	}

	if (m_bInited)
	{
        tpHintNoFile(Ums_Mdl_Cfg,"[InitConfigure]: has inited\n"); 
		return TRUE;
	}
	if (NULL == achFileName)	
	{
        MdlError(Ums_Mdl_Cfg, ("[MTCFGDATA][InitConfigure]: the init file name is NULL\n")); 
		return FALSE;
	}
	
	strncpy( m_achFilePath, achFileName, sizeof(m_achFilePath) );

//不是LINUX，不用乒乓算法
#ifndef _LINUX_
	return TRUE;
#endif

	TpGenCrc4RemTbl();
 
	if(!AllocBlockMem())
	{
		return FALSE;
	}
 
 	GetSectionStatus();
    

	BOOL bFirstSection  = (m_aStnStatus[0] ==  USEFUL_SECTION);
	BOOL bSecondSection = (m_aStnStatus[1] == USEFUL_SECTION);
	
 	if ( bFirstSection && bSecondSection )
    {
		m_bInited = ProcessTwoSections();
	}
	else if(bFirstSection )
	{
		m_bInited = ProcessFirstSection();
	}
	else if(bSecondSection)
	{
		m_bInited = ProcessSecondSection();
	}
	else
	{
		m_byCurSecId = SECTION_NUM;
        tpHintNoFile(Ums_Mdl_Cfg,"[MTCFGDATA][InitConfigure]: no section could be used %d\n",
            __LINE__);
		m_bInited = FALSE;
	}


	const s8* str = (SECTION_NUM == m_byCurSecId) ? "FALSE":"TRUE";
	tpHintNoFile(Ums_Mdl_Cfg,"m_byCurSecId = %d ,%s\n",m_byCurSecId,str);


	return m_bInited;
}

/*=============================================================================
函 数 名：Setup
功    能：检测分区数据合法性
注    意：
算法实现：
全局变量：
输入参数：bySection 分区序列号
          
   
输出参数：
          
返 回 值：成功返回TRUE，失败返回FALSE
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
BOOL CTpCfgDataManager::Setup(u8 bySection)
{
	if (0 == m_atBlockHeader[bySection].dwBlockSize || 0 == strlen(m_atBlockHeader[bySection].achCheckString))
	{
		return FALSE;
	}

	char achCheckString[CHECK_STRING_LEN] = {0};
	MAKE_CHECK_STRING(achCheckString, m_atBlockHeader[bySection].dwBlockSize, m_atBlockHeader[bySection].dwStatus);
    
	// 检测此分区是否被使用过
	int nSectionIsUsed = strncmp(achCheckString, m_atBlockHeader[bySection].achCheckString, strlen(achCheckString));

	if (0 != nSectionIsUsed)
	{
		MdlError(Ums_Mdl_Cfg, ("[MTCFGDATA][Setup %d]: strncpy error: %d\n", bySection, __LINE__));
		return FALSE;
	}

	if (m_atBlockHeader[bySection].dwBlockSize <= sizeof(_TTPBLOCKHEADER))
	{
		MdlError(Ums_Mdl_Cfg, ("[MTCFGDATA][Setup%d]: BlockSize < BLOCKHEADER %d\n", bySection, __LINE__));
		return FALSE;
	}

	if (m_atBlockHeader[bySection].dwBlockSize > m_dwBlockSize)
	{
	   m_dwBlockSize = m_atBlockHeader[bySection].dwBlockSize;
	   m_pbyBlockMem = (u8*)realloc(m_pbyBlockMem, m_dwBlockSize);
	   if (m_pbyBlockMem == NULL)
	   {
		   MdlError(Ums_Mdl_Cfg, ("[MTCFGDATA]:[Setup]alloc fail, want to be realloc %d\n",m_dwBlockSize));
		   return FALSE;
	   }
	   memset(m_pbyBlockMem, 0, m_dwBlockSize);
	}

	tpHintNoFile(Ums_Mdl_Cfg, "[CCfgDataManager]:Setup, bySection->%d \n", bySection);
	
	// 先创建配置文件
	BOOL bRet = CreateCfgFile(m_achFilePath);
	if (!bRet)
	{
		MdlError(Ums_Mdl_Cfg, ("[MTCFGDATA][Setup]:%s CreateCfgFile %s Fail %d\n", __FILE__, m_achFilePath, __LINE__));
		return FALSE;
	}

	// 读取分区的文件数据（头信息+数据）
	u32 dwReadLen = ReadData(bySection, m_pbyBlockMem, m_atBlockHeader[bySection].dwBlockSize);
	if (dwReadLen != m_atBlockHeader[bySection].dwBlockSize ) 
	{
		MdlError(Ums_Mdl_Cfg,("[MTCFGDATA][Setup]: ReadData error: %d\n",__LINE__));
		return FALSE;
	}

	// 获取数据区数据长度
	int nUsefulDataLen = m_atBlockHeader[bySection].dwBlockSize - sizeof(_TTPBLOCKHEADER);
	
	// 获取数据区首地址
	u8 *pbyData = m_pbyBlockMem + sizeof(_TTPBLOCKHEADER);
	
	// 检验分区数据是否合法
	BOOL bCRC4Valid = TpIsValidCRC4(pbyData, nUsefulDataLen, m_atBlockHeader[bySection].byCheckCode);
    if (!bCRC4Valid)
	{
		MdlError(Ums_Mdl_Cfg,("check code = %d\n",m_atBlockHeader[bySection].byCheckCode ));
		m_bValid = FALSE;
		m_atBlockHeader[bySection].dwStatus = 1;
		return FALSE;
	}
	
	// 将分区数据写入conf下的配置文件
	FILE * wp = fopen(m_achFilePath, "wb");
	tpHintNoFile(Ums_Mdl_Cfg,"fopen,  m_achFilePath->%s \n", m_achFilePath);
	if (NULL == wp)
	{
		MdlError(Ums_Mdl_Cfg, ("[MTCFGDATA][Setup]:Open File %s Fail\n", m_achFilePath ));
		return FALSE;
	}
	fwrite(pbyData, 1, nUsefulDataLen, wp);
	fclose(wp);
	m_bValid = TRUE;
	return TRUE;
}


/*=============================================================================
函 数 名：SaveData
功    能：保存数据到分区
注    意：
算法实现：
全局变量：
输入参数：pbyData 缓存
          dwLen   数据长度
   
输出参数：
          
返 回 值：成功返回TRUE，失败返回FALSE
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
BOOL CTpCfgDataManager::SaveData(u8 *pbyData, u32 dwLen)
{	
	if (!pbyData || dwLen >= MAX_SETION_SIZE)
	{
		if (NULL == pbyData)
		{
			MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[SaveData] %s Save data is NULL\n", __FILE__));
		}
		if (dwLen >= MAX_SETION_SIZE)
		{
			MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[SaveData] %s file size >= MAX_SETION_SIZE\n", __FILE__));
		}
		return FALSE;
	}

	// 根据分区状态，确定保存至哪个分区
	u32 dwStatus = m_atBlockHeader[m_byCurSecId].dwStatus;
	UpdateCurSectionId();
	if (m_byCurSecId == SECTION_NUM) // 所有分区都已损坏
	{
		MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[SaveData]: all sections are destroyed\n" ));
		return FALSE;
	}

    // 分区format: block header + data
	m_atBlockHeader[m_byCurSecId].dwBlockSize = dwLen + sizeof(_TTPBLOCKHEADER);
	m_atBlockHeader[m_byCurSecId].dwStatus = dwStatus + 1; // 标记为最新
	
	if (m_atBlockHeader[m_byCurSecId].dwBlockSize > m_dwBlockSize)
	{
	   m_dwBlockSize = m_atBlockHeader[m_byCurSecId].dwBlockSize;
	   m_pbyBlockMem = (u8*)realloc(m_pbyBlockMem, m_dwBlockSize);
	   if (m_pbyBlockMem == NULL)
	   {
		   MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[SaveData]alloc fail\n" ));
		   return FALSE;
	   }
	   memset(m_pbyBlockMem, 0, m_dwBlockSize);
	}

   // 加上校验码
	m_atBlockHeader[m_byCurSecId].byCheckCode = TpGenCrc4Code(pbyData, dwLen);
   
	// 加上校验字符串
	memset( 
		m_atBlockHeader[m_byCurSecId].achCheckString,
		0, 
		sizeof( m_atBlockHeader[m_byCurSecId].achCheckString ) 
		);

	MAKE_CHECK_STRING( 
		m_atBlockHeader[m_byCurSecId].achCheckString, 
		m_atBlockHeader[m_byCurSecId].dwBlockSize, 
		m_atBlockHeader[m_byCurSecId].dwStatus 
		);

	// 加上头信息
	memcpy( 
		m_pbyBlockMem,
		&m_atBlockHeader[m_byCurSecId],
		sizeof(_TTPBLOCKHEADER) 
		);
    // 加上数据
	memcpy( 
		m_pbyBlockMem + sizeof(_TTPBLOCKHEADER),
		pbyData,
		dwLen 
		);

	m_bValid = TRUE;
	return WriteData( 
		m_byCurSecId, 
		m_pbyBlockMem, 
		m_atBlockHeader[m_byCurSecId].dwBlockSize 
		);  
}

/*=============================================================================
函 数 名：ShowCurrentSection
功    能：显示当前分区数据
注    意：
算法实现：
全局变量：
输入参数：
          
   
输出参数：
          
返 回 值：
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
void CTpCfgDataManager::ShowCurrentSection()
{
	char  *achBuf = new char[m_atBlockHeader[m_byCurSecId].dwBlockSize];
	memset( achBuf, 0, m_atBlockHeader[m_byCurSecId].dwBlockSize );
	u32 wLen = ReadData(m_byCurSecId,(u8*)achBuf,m_atBlockHeader[m_byCurSecId].dwBlockSize);

	tpHintNoFile(Ums_Mdl_Cfg,"will be read %d --- readed %d\n",	m_atBlockHeader[m_byCurSecId].dwBlockSize, wLen );
	
	for(u32 i = 0 ; i < m_atBlockHeader[m_byCurSecId].dwBlockSize ; i++)
		tpHintNoFile(Ums_Mdl_Cfg,"%c",achBuf[i]);
	
	delete [] achBuf;
	achBuf = NULL;
}

/*=============================================================================
函 数 名：GetSectionSize
功    能：获取当前分区数据长度
注    意：
算法实现：
全局变量：
输入参数：
          
   
输出参数：
          
返 回 值：数据长度
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
int CTpCfgDataManager::GetSectionSize()
{
    if ( m_bValid )
		return m_atBlockHeader[m_byCurSecId].dwBlockSize-sizeof( _TTPBLOCKHEADER );
	else
		return 0;
}

/*=============================================================================
函 数 名：UpdateCurSectionId
功    能：更新当前分区
注    意：
算法实现：乒乓策略
全局变量：
输入参数：
          
   
输出参数：
          
返 回 值：
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
void CTpCfgDataManager::UpdateCurSectionId()
{
	if (m_aStnStatus[SECTION_ONE] == USEFUL_SECTION && m_aStnStatus[SECTION_TWO] == USEFUL_SECTION)
	{
		m_byCurSecId = (m_byCurSecId == SECTION_ONE) ? SECTION_TWO : SECTION_ONE;
	}
	else if (m_aStnStatus[SECTION_ONE] == USEFUL_SECTION && m_aStnStatus[SECTION_TWO] == UNUSEFUL_SECTION)
	{
        m_byCurSecId = SECTION_ONE;
	}
	else if (m_aStnStatus[SECTION_ONE] == UNUSEFUL_SECTION && m_aStnStatus[SECTION_TWO] == USEFUL_SECTION)
	{
		m_byCurSecId = SECTION_TWO;
	}
	else
	{
	    m_byCurSecId = SECTION_NUM;
	}
}
/*=============================================================================
函 数 名：ReadData
功    能：读分区数据
注    意：
算法实现：
全局变量：
输入参数：bySection  分区序列号
          pbyData    缓存
          dwLen      缓存长度
输出参数：
          
返 回 值：成功返回TRUE，失败返回FALSE
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
u32 CTpCfgDataManager::ReadDataT2(u8 bySection, u8* pbyData, u32 dwLen)
{
	tpHintNoFile(Ums_Mdl_Cfg, "[CCfgDataManager], ReadDataT2 \n");
    tpHintNoFile(Ums_Mdl_Cfg, "[ReadDataT2], bySection->%d \n", bySection); 	
	tpHintNoFile(Ums_Mdl_Cfg, "read section = %d, data address = %x, data len = %d \n", bySection, pbyData, dwLen);
	if (NULL == pbyData) 
		return 0;

	_TTPBLOCKHEADER tHeader;
	memset(&tHeader, 0, sizeof(tHeader));	
	s8 achFileName[TP_FILENAME_LENGTH] = {0};
	FILE *pfile = NULL;
	s8 *pName = NULL;
	if (SECTION_ONE == bySection)
	{
		if(TP_INVALID_INDEX == m_wSeqNum)
		{
			strncpy(achFileName, MTCTL_0, sizeof(achFileName));
			pName = achFileName;
		}
		else
		{
			sprintf(achFileName, "%s%d.ini", MTCFG_0, m_wSeqNum);
			pName = achFileName;
		}
	}
	else if (SECTION_TWO == bySection)
	{
		if (TP_INVALID_INDEX == m_wSeqNum)
		{
			strncpy(achFileName, MTCTL_1, sizeof(achFileName));
			pName = achFileName;
		}
		else
		{
			sprintf(achFileName, "%s%d.ini", MTCFG_1, m_wSeqNum);
			pName = achFileName;
		}

	}
	
	// 打开分区文件
	pfile = fopen(pName, "rb" );
	tpHintNoFile(Ums_Mdl_Cfg, "[ReadDataT2], fopen, pName->%s \n", pName);
	// 不存在，则创建一个分区，并写头信息
	if (NULL == pfile)
	{		
		CreateCfgFile(pName);       //创建分区文件存储路径
		pfile = fopen(pName, "wb");
		if (NULL != pfile) 
		{
			fwrite(&tHeader, sizeof(tHeader), 1, pfile);
			fclose(pfile);
			return dwLen;
		}
		MdlError(Ums_Mdl_Cfg,("[ReadDataT2], fopen, rb, error! \n"));
		return 0;		
	}

	u32 dwReadLen = fread(pbyData, sizeof(u8), dwLen, pfile );

	if ( 0 == dwReadLen)
	{
		MdlError(Ums_Mdl_Cfg,("[ReadDataT2], fread, error !\n"));
		fclose(pfile);
		return 0;		
	}

	fclose(pfile);


	tpHintNoFile(Ums_Mdl_Cfg,"[ReadDataT2],Data read from rawdisk :\n");
	_TTPBLOCKHEADER* pHeader = (_TTPBLOCKHEADER*)pbyData;
	tpHintNoFile(Ums_Mdl_Cfg,"dwBlockSize = %d ;\n dwStatus = %d ;\n achVersion[40] = %s ;\n"
			  "achCheckString[CHECK_STRING_LEN] = %s ;\n byCheckCode = %d;\n",
			  pHeader[0].dwBlockSize,
			  pHeader[0].dwStatus,
			  pHeader[0].achVersion,
			  pHeader[0].achCheckString,
			  pHeader[0].byCheckCode);	

	return dwReadLen;

}



u32 CTpCfgDataManager::ReadData( u8 bySection, u8* pbyData, u32 dwLen)
{
	INT32 nResult = 0;

#ifdef WIN32
	return dwLen;	
#endif
	
#if defined(_LINUX_)
	tpHintNoFile(Ums_Mdl_Cfg,"[CCfgDataManager], ReadData \n");
	return ReadDataT2(bySection, pbyData, dwLen);	
#endif

#if defined(_VXWORKS_) || defined(_LINUX_)

		tpHintNoFile(Ums_Mdl_Cfg,"will be read data from raw disk...\n");
		tpHintNoFile(Ums_Mdl_Cfg,"read section = %d , data address = %x, data len = %d\n",
			bySection,pbyData,dwLen);

	if (NULL == pbyData) return 0;

	nResult = BrdFpReadDataFromUsrFpn( bySection, pbyData, dwLen );

	if( 0!= nResult)
	{
		tpHintNoFile(Ums_Mdl_Cfg,"read from rawdisk data is :\n\n");
		_TTPBLOCKHEADER* pHeader = (_TTPBLOCKHEADER*)pbyData;
		tpHintNoFile(Ums_Mdl_Cfg,"dwBlockSize = %d \n;dwStatus = %d\n;achVersion[40] = %s\n;"
			  "achCheckString[CHECK_STRING_LEN] = %s\n;byCheckCode = %d;\n",
			  pHeader[0].dwBlockSize,
			  pHeader[0].dwStatus,
			  pHeader[0].achVersion,
			  pHeader[0].achCheckString,
			  pHeader[0].byCheckCode);
        if(dwLen > sizeof(_TTPBLOCKHEADER))
		{
				pHeader++;
				s8* pstr = (s8*)pHeader;
				int i = nResult - sizeof(_TTPBLOCKHEADER);
				for (;i>0;i--,pstr++)
					tpHintNoFile(Ums_Mdl_Cfg,"%c",*pstr);
				tpHintNoFile(Ums_Mdl_Cfg,"\n\n\n");
		}
	}
	if( 0 == nResult)
	{
		tpHintNoFile(Ums_Mdl_Cfg,"[MTCFGDATA]:[ReadData]%s BrdFpReadDataFromUsrFpn %d\n",
			__FILE__,__LINE__);
		tpHintNoFile(Ums_Mdl_Cfg,"section is : %d\n data : %p \n len : %d\n",bySection,pbyData,dwLen);
	}
	return nResult;
#endif
}

/*=============================================================================
函 数 名：WriteData
功    能：写分区数据
注    意：
算法实现：
全局变量：
输入参数：bySection  分区序列号
          pbyData    缓存
          dwLen      缓存长度
输出参数：
          
返 回 值：成功返回TRUE，失败返回FALSE
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
=============================================================================*/
BOOL32 CTpCfgDataManager::WriteDataT2(u8 bySection, u8* pbyData, u32 dwLen)
{
	if (dwLen != 0)
	{
        tpHintNoFile(Ums_Mdl_Cfg,"[WriteDataT2], bySection->%d \n", bySection);        
		tpHintNoFile(Ums_Mdl_Cfg,"[WriteDataT2], Save data to rawdisk  \n");
		_TTPBLOCKHEADER* pHeader = (_TTPBLOCKHEADER*)pbyData;
		tpHintNoFile(Ums_Mdl_Cfg,"dwBlockSize = %d ;\n dwStatus = %d ;\n achVersion[40] = %s ;\n"
				"achCheckString[CHECK_STRING_LEN] = %s ;\n byCheckCode = %d; \n",
				pHeader[0].dwBlockSize,
				pHeader[0].dwStatus,
				pHeader[0].achVersion,
				pHeader[0].achCheckString,
				pHeader[0].byCheckCode
				  );
	}

	FILE *pfile = NULL;
	char achFileName[TP_FILENAME_LENGTH] = {0};
	if (SECTION_ONE == bySection)
	{
		if (TP_INVALID_INDEX == m_wSeqNum)
		{
			strncpy(achFileName, MTCTL_0, sizeof(achFileName));
			pfile = fopen(achFileName, "wb");
			tpHintNoFile(Ums_Mdl_Cfg, "[WriteDataT2], pfile->%s \n ", achFileName);
		}
		else
		{
			sprintf(achFileName, "%s%d.ini", MTCFG_0, m_wSeqNum);
			pfile = fopen(achFileName, "wb");
			tpHintNoFile(Ums_Mdl_Cfg, "[WriteDataT2], pfile->%s \n", achFileName);
		}
	}
	else if (SECTION_TWO == bySection)
	{		
		if (TP_INVALID_INDEX == m_wSeqNum)
		{
			strncpy(achFileName, MTCTL_1, sizeof(achFileName));
			pfile = fopen(achFileName, "wb");
			tpHintNoFile(Ums_Mdl_Cfg, "[WriteDataT2], pfile->%s \n", achFileName);
		}
		else
		{
			sprintf(achFileName, "%s%d.ini", MTCFG_1, m_wSeqNum);
			pfile = fopen(achFileName, "wb");
			tpHintNoFile(Ums_Mdl_Cfg, "[WriteDataT2], pfile->%s \n", achFileName);
		}
	}

	if (NULL == pfile)
	{
		MdlError(Ums_Mdl_Cfg, ("[WriteDataT2], fopen error, bySection->%d \n", bySection));
		return FALSE;
	}

	u32 dwWriteLen = fwrite(pbyData, dwLen,	sizeof(u8),	pfile);

	if (0 == dwWriteLen)
	{
		MdlError(Ums_Mdl_Cfg, ("[WriteDataT2], fwrite, error! \n"));
		fclose( pfile );
		return FALSE;
	}
	
	//正常关闭文件
	fclose( pfile );
	return TRUE;
}

BOOL32 CTpCfgDataManager::WriteData( u8 bySection, u8* pbyData, u32 dwLen )
{


#ifdef WIN32
	return WriteDataT2(bySection, pbyData, dwLen);
#endif

#if defined(_LINUX_) && defined(_d6446_) || defined(_HD2G_)
	return WriteDataT2(bySection, pbyData, dwLen);    
#endif
	
#if defined(_VXWORKS_) || defined(_LINUX_)
	if( dwLen != 0)
	{
		tpHintNoFile(Ums_Mdl_Cfg,"Save to rawdisk data is :\n\n");
		_TTPBLOCKHEADER* pHeader = (_TTPBLOCKHEADER*)pbyData;
		tpHintNoFile(Ums_Mdl_Cfg,"dwBlockSize = %d \n;dwStatus = %d\n;achVersion[40] = %s\n;"
				"achCheckString[CHECK_STRING_LEN] = %s\n;byCheckCode = %d;\n",
				pHeader[0].dwBlockSize,
				pHeader[0].dwStatus,
				pHeader[0].achVersion,
				pHeader[0].achCheckString,
				pHeader[0].byCheckCode
				  );
		pHeader++;
		s8* pstr = (s8*)pHeader;
		int i = dwLen - sizeof(_TTPBLOCKHEADER);

		for( i>0 ;i--;pstr++)
			tpHintNoFile(Ums_Mdl_Cfg,"%c",*pstr);
		tpHintNoFile(Ums_Mdl_Cfg,"\n\n\n");
	}

	STATUS bResult = BrdFpWriteDataToUsrFpn( bySection, pbyData, dwLen );

	if( OK == bResult)	return TRUE;
	
	tpHintNoFile(Ums_Mdl_Cfg,"[MTCFGDATA]:[WriteData]%s BrdFpWriteDataToUsrFpn %d\n",
		__FILE__,__LINE__);
	tpHintNoFile(Ums_Mdl_Cfg,"section is : %d\n data : %p \n len : %d\n",
		bySection,pbyData,dwLen);
	return FALSE;

#endif
}


/*====================================================================
    函数名      ：CreateCfgFile
    功能        ：创建配置文件
    算法实现    ：（可选项）
    引用全局变量：无
    输入参数说明：char * pbyFileName: 配置文件名
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/05    1.0         方华平          创建
====================================================================*/
#ifndef FILE_TPCFG_INI
#define FILE_TPCFG_INI (s8*)"templatecfg_"
#endif

#ifndef FILE_TPCTL_INI
#define FILE_TPCTL_INI (s8*)"control.ini"
#endif
BOOL CTpCfgDataManager::CreateCfgFile( char * pbyFileName )
{
#ifdef _LINUX_
	mode_t oldmode = 0;
#endif

	char achDirName[256]={0};
    char *pchDest = NULL;
    FILE    *stream = fopen( pbyFileName, "rb" );
	char achFileName[TP_FILENAME_LENGTH] = {0};

	//已经存在，则返回出错，
    if( stream != NULL )
    {
		fclose( stream );
        return TRUE;
    }

	/*先创建目录*/
	strncpy( achDirName, pbyFileName, sizeof(achDirName) );

	if(TP_INVALID_INDEX==m_wSeqNum)
	{
		strncpy(achFileName,FILE_TPCTL_INI,sizeof(achFileName));
	}
	else
	{
		sprintf(achFileName,"%s%d.ini",FILE_TPCFG_INI,m_wSeqNum);
	}


	pchDest = strstr( achDirName, achFileName );
	if ( !pchDest )
	{
        MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[CreateCfgFile] Wrong Get file path %s error \n",
			achDirName));
		return FALSE;
	}
	
	pchDest--;
	if ( *pchDest != '\\' && *pchDest != '/' )
	{
	    MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[CreateCfgFile] %s Wrong %s file path %d\n",
			__FILE__,pchDest,__LINE__ ));
		return FALSE;
	}
		
	*pchDest = '\0';

	if( strlen(achDirName) != 0 )
	{
#ifdef _LINUX_
		oldmode = umask(0);
#endif
		UmsMakeDir( achDirName );
#ifdef _LINUX_
		umask(oldmode);
#endif
	}
	else
	{
		MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[CreateCfgFile]  %s Wrong %s file path %d\n",
			__FILE__,achDirName,__LINE__ ));
		return FALSE;
	}

	/*创建一个空文件*/
    stream = fopen( pbyFileName, "w" );
	if ( !stream )
	{
        MdlError(Ums_Mdl_Cfg,("[MTCFGDATA]:[CreateCfgFile]  %s Wrong %s file path %d\n", 
			__FILE__,pbyFileName,__LINE__ ));
		return FALSE;
	}
	fclose( stream );

	return TRUE;
}
#undef  FILE_TPCFG_INI
/*====================================================================
  函 数 名： EraseRawDisk
  功    能： 
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： void 
  --------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2005/9/2      1.0		    张 飞                   创建
======================================================================*/
void CTpCfgDataManager::EraseRawDisk()
{
	memset( m_pbyBlockMem, 0, m_dwBlockSize );
	for ( u8 i =0; i<SECTION_NUM; i++ )
	    WriteData( i, m_pbyBlockMem, m_dwBlockSize ); 
}
