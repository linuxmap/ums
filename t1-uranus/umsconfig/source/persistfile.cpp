/*******************************************************************************
 *  ģ����   :                                                                 *
 *  �ļ���   : persistfile.cpp                                       *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� :                                                                 *
 *  ����     :                                                           *
 *  �汾     : V4.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  2005/8/26  1.0         �� ��          �ļ�ϵͳ�ж�         *
 *                                                                             *
 *******************************************************************************/

#include "persistfile.h"
#include <stdlib.h>
#include "crc.h"
#include "string.h"
#include "umsconfig.h"


#ifdef _VXWORKS_
#include "fpdrvlib.h"
#endif

#ifdef _LINUX_
#include "brdwrapper.h"
#include "nipwrapper.h"
#endif


BOOL g_bUmsShowConfig_info = FALSE;//FALSE;

#define MTCFG_0 "/usr/0umscfg.ini"
#define MTCFG_1 "/usr/1umscfg.ini"

CCfgDataManager g_cUmsCfgDataMan;

CCfgDataManager::CCfgDataManager()
{
	m_bInited = FALSE;
	m_bValid  = FALSE;
	m_pbyBlockMem = NULL;
 	m_dwBlockSize  = DEFAULT_BLOCK_SIZE;
	m_aStnStatus[0] = UNUSEFUL_SECTION;
	m_aStnStatus[1] = UNUSEFUL_SECTION;
}

CCfgDataManager::~CCfgDataManager()
{
	if ( m_pbyBlockMem )
	   free( m_pbyBlockMem );
	m_pbyBlockMem = NULL;
}
	
/*====================================================================
  �� �� ���� AllocBlockMem
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2006/7/19      1.0		    �� ��                   ����
======================================================================*/
BOOL CCfgDataManager::AllocBlockMem()
{
    if(NULL == m_pbyBlockMem)
	{
		m_pbyBlockMem = (u8*)malloc( m_dwBlockSize );
		if(NULL == m_pbyBlockMem)
		{
			msgprint("[MTCFGDATA][InitConfigure]: alloc memery failled\n");
			return FALSE;
		}
		memset( m_pbyBlockMem, 0, m_dwBlockSize );
	} 	
	if(g_bUmsShowConfig_info)
		msgprint("[MTCFGDATA][InitConfigure]: alloc memery success:%d\n",m_dwBlockSize);
	return TRUE;
}
/*====================================================================
  �� �� ���� GetSectionStatus
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2006/7/19      1.0		    �� ��                   ����
======================================================================*/
void CCfgDataManager::GetSectionStatus()
{	
    // �鿴���������
	memset(&m_atBlockHeader,0,sizeof(m_atBlockHeader));
    for( u8 i=0; i<SECTION_NUM; i++ )
	{
		u16 wBlockHeadSize = sizeof( _TBLOCKHEADER );
		u32 nReadLen = ReadData( i, (u8*)&m_atBlockHeader[i], wBlockHeadSize );

        if ( nReadLen == wBlockHeadSize ) 
		{
			if(g_bUmsShowConfig_info)
					msgprint("[CCfgDataManager], GetSectionStatus: Section %d read success\n",i);
            m_aStnStatus[i] = USEFUL_SECTION;
		}
		else
		{		
			m_aStnStatus[i] = UNUSEFUL_SECTION;
			msgprint( "[CCfgDataManager::GetSectionStatus], Section %d read fail\n", i);
		}
	}
}
/*====================================================================
  �� �� ���� ProcessTwoSections
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2006/7/19      1.0		    �� ��                   ����
======================================================================*/
BOOL CCfgDataManager::ProcessTwoSections()
{
	msgprint("[CCfgDataManager], ProcessTwoSections !\n");

	// ���ȶ�ȡ���µ�������Ϣ
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
	msgprint("[MTCFGDATA][InitConfigure]: Setup file error %d\n",__LINE__);
	return FALSE;
}
/*====================================================================
  �� �� ���� ProcessFirstSection
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2006/7/19      1.0		    �� ��                   ����
======================================================================*/
BOOL CCfgDataManager::ProcessFirstSection()
{
	msgprint("[CCfgDataManager], ProcessFirstSection !\n");

	m_byCurSecId = SECTION_ONE;
	BOOL bSetup = Setup( SECTION_ONE );
    if(!bSetup)
		msgprint("[CCfgDataManager],ProcessFirstSection, Setup file error %d\n",__LINE__);
	return bSetup;
}
/*====================================================================
  �� �� ���� ProcessSecondSection
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� BOOL 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��	      �汾		    �޸���		�߶���    �޸�����
  2006/7/19      1.0		    �� ��                   ����
======================================================================*/
BOOL CCfgDataManager::ProcessSecondSection()
{
	msgprint("[CCfgDataManager], ProcessSecondSection !\n");

	m_byCurSecId = SECTION_TWO;
	BOOL bSetup = Setup( SECTION_TWO );
	if(!bSetup)
		msgprint("[CCfgDataManager], ProcessSecondSection : Setup file error %d\n",__LINE__);
	return bSetup;
}

/*=============================================================================
�� �� ����InitConfigure
��    �ܣ���ʼ�����ݹ���ģ��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
���������pbyFilePath �����ļ�·��
          
   
���������
          
�� �� ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
BOOL CCfgDataManager::InitConfigure( s8 *pbyFilePath ) 
{
	if(g_bUmsShowConfig_info)
		msgprint("[InitConfigure]: the init file name is %s\n",pbyFilePath); 

	if (m_bInited)
	{
        if(g_bUmsShowConfig_info)
            msgprint("[InitConfigure]: has inited\n"); 
		return TRUE;
	}

	if ( NULL == pbyFilePath )	
	{
        if(g_bUmsShowConfig_info)
            msgprint("[MTCFGDATA][InitConfigure]: the init file name is NULL\n"); 
		return FALSE;
	}
	
	strncpy( m_achFilePath, pbyFilePath, sizeof(m_achFilePath) );

#ifndef _LINUX_
	return TRUE;
#endif

#ifdef _LINUX_CONFIG_DEBUG_
	return m_bInited = TRUE;
#endif
	GenCrc4RemTbl();
 
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
        msgprint("[MTCFGDATA][InitConfigure]: no section could be used %d\n",
            __LINE__);
		m_bInited = FALSE;
	}

	if (g_bUmsShowConfig_info)
	{
		const s8* str = (SECTION_NUM == m_byCurSecId) ? "FALSE":"TRUE";
		msgprint("m_byCurSecId = %d ,%s\n",m_byCurSecId,str);
	}


	return m_bInited;
}

/*=============================================================================
�� �� ����Setup
��    �ܣ����������ݺϷ���
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
���������bySection �������к�
          
   
���������
          
�� �� ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
BOOL CCfgDataManager::Setup( u8 bySection )
{
	if (0 == m_atBlockHeader[bySection].dwBlockSize || 0 == strlen(m_atBlockHeader[bySection].achCheckString))
	{
		return FALSE;
	}

	char achCheckString[CHECK_STRING_LEN] = { 0 };
	MAKE_CHECK_STRING( achCheckString,
		m_atBlockHeader[bySection].dwBlockSize,
		m_atBlockHeader[bySection].dwStatus );
    //���˷����Ƿ�ʹ�ù�

	int nSectionIsUsed =  strncmp( achCheckString,
		m_atBlockHeader[bySection].achCheckString,
		strlen( achCheckString ) ) ;

	if ( nSectionIsUsed != 0 )
	{
		msgprint("[MTCFGDATA][Setup %d]: strncpy error: %d\n",bySection,__LINE__);
		return FALSE;
	}

	if (m_atBlockHeader[bySection].dwBlockSize <= sizeof( _TBLOCKHEADER ))
	{
		msgprint("[MTCFGDATA][Setup%d]: BlockSize < BLOCKHEADER %d\n",
			bySection,__LINE__);
		return FALSE;
	}

	if ( m_atBlockHeader[bySection].dwBlockSize > m_dwBlockSize	)
	{
	   m_dwBlockSize = m_atBlockHeader[bySection].dwBlockSize;
	   m_pbyBlockMem = (u8*)realloc( m_pbyBlockMem, m_dwBlockSize );
	   if ( m_pbyBlockMem == NULL )
	   {
		   msgprint("[MTCFGDATA]:[Setup]alloc fail,want to be realloc %d\n",m_dwBlockSize);
		   return FALSE;
	   }
	   memset( m_pbyBlockMem, 0, m_dwBlockSize );
	}

	msgprint("[CCfgDataManager], Setup,  bySection->%d \n", bySection );	

	u32 dwReadLen = ReadData(bySection,m_pbyBlockMem,
		m_atBlockHeader[bySection].dwBlockSize );

	if (dwReadLen != m_atBlockHeader[bySection].dwBlockSize ) 
	{
		msgprint("[MTCFGDATA][Setup]: ReadData error: %d\n",__LINE__);
		return FALSE;
	}

	//��ȡ���������ݳ���
	int nUsefulDataLen =
		m_atBlockHeader[bySection].dwBlockSize - sizeof( _TBLOCKHEADER );
	//��ȡ�������׵�ַ
	u8 *pbyData =  m_pbyBlockMem + sizeof( _TBLOCKHEADER );

	// ���������Ƿ�Ϸ�
	BOOL bCRC4Valid = IsValidCRC4( pbyData,nUsefulDataLen,
		m_atBlockHeader[bySection].byCheckCode );

    if (!bCRC4Valid)
	{
		msgprint("check code = %d\n",m_atBlockHeader[bySection].byCheckCode );
		m_bValid = FALSE;
		m_atBlockHeader[bySection].dwStatus = 1;
		return FALSE;
	}

	BOOL bRet = CreateCfgFile( m_achFilePath );
	if (!bRet)
	{
		msgprint("[MTCFGDATA][Setup]:%s CreateCfgFile %s Fail %d\n",
			__FILE__,m_achFilePath,__LINE__ );
		return FALSE;
	}
	
	FILE * wp = fopen( m_achFilePath, "w" );
	msgprint("fopen,  m_achFilePath->%s \n", m_achFilePath);
	if ( !wp )
	{
		msgprint("[MTCFGDATA][Setup]:Open File %s Fail\n",
			m_achFilePath );
		return FALSE;
	}
	fwrite( pbyData, 1, nUsefulDataLen, wp );
	fclose( wp );
	m_bValid = TRUE;

	return TRUE;
}


/*=============================================================================
�� �� ����SaveData
��    �ܣ��������ݵ�����
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
���������pbyData ����
          dwLen   ���ݳ���
   
���������
          
�� �� ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
BOOL CCfgDataManager::SaveData( u8 *pbyData, u32 dwLen )
{
	
	if ( !pbyData || dwLen >= MAX_SETION_SIZE )
	{
		if(NULL == pbyData)
		{
			msgprint("[MTCFGDATA]:[SaveData] %s Save data is NULL\n",
				__FILE__);
		}
		if(dwLen >= MAX_SETION_SIZE)
		{
			msgprint("[MTCFGDATA]:[SaveData] %s file size >= MAX_SETION_SIZE\n",
				__FILE__);
		}
		return FALSE;
	}
	u32 dwStatus = m_atBlockHeader[m_byCurSecId].dwStatus;
	UpdateCurSectionId();
	if ( m_byCurSecId == SECTION_NUM ) //���з���������
	{
		msgprint("[MTCFGDATA]:[SaveData]: all sections are destroyed\n" );
		return FALSE;
	}
    //����format: block header + data
	m_atBlockHeader[m_byCurSecId].dwBlockSize = dwLen + sizeof( _TBLOCKHEADER );
	m_atBlockHeader[m_byCurSecId].dwStatus = dwStatus + 1; //��־Ϊ����
	
	if ( m_atBlockHeader[m_byCurSecId].dwBlockSize > m_dwBlockSize )
	{
	   m_dwBlockSize = m_atBlockHeader[m_byCurSecId].dwBlockSize;
	   m_pbyBlockMem = (u8*)realloc( m_pbyBlockMem, m_dwBlockSize );
	   if ( m_pbyBlockMem == NULL )
	   {
		   msgprint("[MTCFGDATA]:[SaveData]alloc fail\n" );
		   return FALSE;
	   }

	   memset( m_pbyBlockMem, 0, m_dwBlockSize );
	}

   //����У����
	m_atBlockHeader[m_byCurSecId].byCheckCode = GenCrc4Code( pbyData, dwLen );
   //����У���ַ���
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

	memcpy( 
		m_pbyBlockMem,
		&m_atBlockHeader[m_byCurSecId],
		sizeof( _TBLOCKHEADER ) 
		);
    
	memcpy( 
		m_pbyBlockMem+sizeof( _TBLOCKHEADER ),
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
�� �� ����ShowCurrentSection
��    �ܣ���ʾ��ǰ��������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
���������
          
   
���������
          
�� �� ֵ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
void CCfgDataManager::ShowCurrentSection()
{
	char  *achBuf = new char[m_atBlockHeader[m_byCurSecId].dwBlockSize];
	memset( achBuf, 0, m_atBlockHeader[m_byCurSecId].dwBlockSize );
	u32 wLen = ReadData(m_byCurSecId,(u8*)achBuf,m_atBlockHeader[m_byCurSecId].dwBlockSize);

	msgprint("will be read %d --- readed %d\n",	m_atBlockHeader[m_byCurSecId].dwBlockSize, wLen );
	
	for(u32 i = 0 ; i < m_atBlockHeader[m_byCurSecId].dwBlockSize ; i++)
		msgprint("%c",achBuf[i]);
	
	delete [] achBuf;
	achBuf = NULL;
}

/*=============================================================================
�� �� ����GetSectionSize
��    �ܣ���ȡ��ǰ�������ݳ���
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
���������
          
   
���������
          
�� �� ֵ�����ݳ���
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
int CCfgDataManager::GetSectionSize()
{
    if ( m_bValid )
		return m_atBlockHeader[m_byCurSecId].dwBlockSize-sizeof( _TBLOCKHEADER );
	else
		return 0;
}

/*=============================================================================
�� �� ����UpdateCurSectionId
��    �ܣ����µ�ǰ����
ע    �⣺
�㷨ʵ�֣�ƹ�Ҳ���
ȫ�ֱ�����
���������
          
   
���������
          
�� �� ֵ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
void CCfgDataManager::UpdateCurSectionId()
{
	if ( 
		m_aStnStatus[SECTION_ONE] == USEFUL_SECTION 
		&& 
		m_aStnStatus[SECTION_TWO] == USEFUL_SECTION 
		)
	{
		m_byCurSecId = (m_byCurSecId == SECTION_ONE) ?
			SECTION_TWO:SECTION_ONE;
	}
	else if ( 
		m_aStnStatus[SECTION_ONE] == USEFUL_SECTION
		&& 
		m_aStnStatus[SECTION_TWO] == UNUSEFUL_SECTION 
		)
        m_byCurSecId = SECTION_ONE;
	else if ( 
		m_aStnStatus[SECTION_ONE] == UNUSEFUL_SECTION
		&& 
		m_aStnStatus[SECTION_TWO] == USEFUL_SECTION 
		)
		m_byCurSecId = SECTION_TWO;
	else
	    m_byCurSecId = SECTION_NUM;
}
/*=============================================================================
�� �� ����ReadData
��    �ܣ�����������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
���������bySection  �������к�
          pbyData    ����
          dwLen      ���泤��
���������
          
�� �� ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
u32 CCfgDataManager::ReadDataT2( u8 bySection, u8* pbyData, u32 dwLen)
{
	if(g_bUmsShowConfig_info)
	{
		msgprint("[CCfgDataManager], ReadDataT2 \n");
        msgprint("[ReadDataT2], bySection->%d \n", bySection ); 	
		msgprint("read section = %d , data address = %x, data len = %d \n",
			bySection,pbyData,dwLen);
	}

	if (NULL == pbyData) return 0;

	_TBLOCKHEADER tHeader;
	memset( &tHeader, 0, sizeof(tHeader) );	

	FILE *pfile = NULL;
	s8 *pName = NULL;
	if ( SECTION_ONE == bySection )
	{
		pName = MTCFG_0;
	}
	else if ( SECTION_TWO == bySection )
	{
		pName = MTCFG_1;
	}

	//���ص�bugѽ
	pfile = fopen(pName, "rb" );
	msgprint("[ReadDataT2], fopen, pName->%s \n", pName );

	if ( NULL == pfile )
	{
		//�൱�봴��һ���ļ�������һ������
		//��дһ��������ͷ��Ϣ
	
		pfile = fopen(pName, "w");
		if ( NULL != pfile ) 
		{
			fwrite( &tHeader, sizeof(tHeader), 1, pfile );
			fclose(pfile);
			return dwLen;
		}
		msgprint("[ReadDataT2], fopen, rb, error! \n");
		return 0;		
	}

	u32 dwReadLen = fread(pbyData, sizeof(u8), dwLen, pfile );

	if ( 0 == dwReadLen)
	{
		msgprint("[ReadDataT2], fread, error !\n");
		fclose(pfile);
		return 0;		
	}

	fclose(pfile);

	if( g_bUmsShowConfig_info )
	{
		msgprint("[ReadDataT2],Data read from rawdisk :\n");
		_TBLOCKHEADER* pHeader = (_TBLOCKHEADER*)pbyData;
		msgprint("dwBlockSize = %d ;\n dwStatus = %d ;\n achVersion[40] = %s ;\n"
			  "achCheckString[CHECK_STRING_LEN] = %s ;\n byCheckCode = %d;\n",
			  pHeader[0].dwBlockSize,
			  pHeader[0].dwStatus,
			  pHeader[0].achVersion,
			  pHeader[0].achCheckString,
			  pHeader[0].byCheckCode);	
	}

	return dwReadLen;

}



u32 CCfgDataManager::ReadData( u8 bySection, u8* pbyData, u32 dwLen)
{
	INT32 nResult = 0;

#ifdef WIN32
	return dwLen;	
#endif
	
#if defined(_LINUX_)
	msgprint("[CCfgDataManager], ReadData \n");
	return ReadDataT2( bySection, pbyData, dwLen );	
#endif

#if defined(_VXWORKS_) || defined(_LINUX_)
	if(g_bUmsShowConfig_info)
	{
		msgprint("will be read data from raw disk...\n");
		msgprint("read section = %d , data address = %x, data len = %d\n",
			bySection,pbyData,dwLen);
	}
	if (NULL == pbyData) return 0;

	nResult = BrdFpReadDataFromUsrFpn( bySection, pbyData, dwLen );

	if(g_bUmsShowConfig_info && 0!= nResult)
	{
		msgprint("read from rawdisk data is :\n\n");
		_TBLOCKHEADER* pHeader = (_TBLOCKHEADER*)pbyData;
		msgprint("dwBlockSize = %d \n;dwStatus = %d\n;achVersion[40] = %s\n;"
			  "achCheckString[CHECK_STRING_LEN] = %s\n;byCheckCode = %d;\n",
			  pHeader[0].dwBlockSize,
			  pHeader[0].dwStatus,
			  pHeader[0].achVersion,
			  pHeader[0].achCheckString,
			  pHeader[0].byCheckCode);
        if(dwLen > sizeof(_TBLOCKHEADER))
		{
				pHeader++;
				s8* pstr = (s8*)pHeader;
				int i = nResult - sizeof(_TBLOCKHEADER);
				for (;i>0;i--,pstr++)
					msgprint("%c",*pstr);
				msgprint("\n\n\n");
		}
	}
	if( 0 == nResult && g_bUmsShowConfig_info )
	{
		msgprint("[MTCFGDATA]:[ReadData]%s BrdFpReadDataFromUsrFpn %d\n",
			__FILE__,__LINE__);
		msgprint("section is : %d\n data : %p \n len : %d\n",bySection,pbyData,dwLen);
	}
	return nResult;
#endif
}

/*=============================================================================
�� �� ����WriteData
��    �ܣ�д��������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
���������bySection  �������к�
          pbyData    ����
          dwLen      ���泤��
���������
          
�� �� ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
=============================================================================*/
u32 CCfgDataManager::WriteDataT2( u8 bySection, u8* pbyData, u32 dwLen )
{
	if(g_bUmsShowConfig_info && dwLen != 0)
	{
        msgprint("[WriteDataT2], bySection->%d \n", bySection);        
		msgprint("[WriteDataT2], Save data to rawdisk  \n");
		_TBLOCKHEADER* pHeader = (_TBLOCKHEADER*)pbyData;
		msgprint("dwBlockSize = %d ;\n dwStatus = %d ;\n achVersion[40] = %s ;\n"
				"achCheckString[CHECK_STRING_LEN] = %s ;\n byCheckCode = %d; \n",
				pHeader[0].dwBlockSize,
				pHeader[0].dwStatus,
				pHeader[0].achVersion,
				pHeader[0].achCheckString,
				pHeader[0].byCheckCode
				  );
	}

	FILE *pfile = NULL;
	if ( SECTION_ONE == bySection )
	{
		pfile = fopen(MTCFG_0, "wb");
	}
	else if ( SECTION_TWO == bySection )
	{
		pfile = fopen(MTCFG_1, "wb");
	}

	if ( NULL == pfile )
	{
		msgprint("[WriteDataT2], fopen error, bySection->%d \n", bySection );
		return FALSE;
	}

	u32 dwWriteLen = fwrite(pbyData, dwLen,	sizeof(u8),	pfile );

	if ( 0 == dwWriteLen )
	{
		msgprint("[WriteDataT2], fwrite, error! \n");
		fclose( pfile );
		return FALSE;
	}
	
	//�����ر��ļ�
	fclose( pfile );
	return dwWriteLen;
}

extern BOOL g_bCfgModuleDisable;
u32 CCfgDataManager::WriteData( u8 bySection, u8* pbyData, u32 dwLen )
{
	if( g_bCfgModuleDisable )
	{
		msgprint("[WriteDataT2]...retrun by g_bCfgModuleDisable\n");
		return TRUE;
	}

#ifdef WIN32
	return WriteDataT2( bySection, pbyData, dwLen );
#endif

#if defined(_LINUX_)
	return WriteDataT2( bySection, pbyData, dwLen );    
#endif
	
#if defined(_VXWORKS_) || defined(_LINUX_)
	if(g_bUmsShowConfig_info && dwLen != 0)
	{
		msgprint("Save to rawdisk data is :\n\n");
		_TBLOCKHEADER* pHeader = (_TBLOCKHEADER*)pbyData;
		msgprint("dwBlockSize = %d \n;dwStatus = %d\n;achVersion[40] = %s\n;"
				"achCheckString[CHECK_STRING_LEN] = %s\n;byCheckCode = %d;\n",
				pHeader[0].dwBlockSize,
				pHeader[0].dwStatus,
				pHeader[0].achVersion,
				pHeader[0].achCheckString,
				pHeader[0].byCheckCode
				  );
		pHeader++;
		s8* pstr = (s8*)pHeader;
		int i = dwLen - sizeof(_TBLOCKHEADER);
		for(; i>0 ;i--,pstr++)
			msgprint("%c",*pstr);
		msgprint("\n\n\n");
	}

	STATUS bResult = BrdFpWriteDataToUsrFpn( bySection, pbyData, dwLen );

	if( OK == bResult)	return TRUE;
	
	msgprint("[MTCFGDATA]:[WriteData]%s BrdFpWriteDataToUsrFpn %d\n",
		__FILE__,__LINE__);
	msgprint("section is : %d\n data : %p \n len : %d\n",
		bySection,pbyData,dwLen);
	return FALSE;

#endif
}
/*====================================================================
    ������      ��CreateCfgFile
    ����        �����������ļ�
    �㷨ʵ��    ������ѡ�
    ����ȫ�ֱ�������
    �������˵����char * pbyFileName: �����ļ���
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/12/05    1.0         ����ƽ          ����
====================================================================*/
#ifndef FILE_UMSCFG_INI
#define FILE_UMSCFG_INI (s8*)"umscfg.ini"
#endif

BOOL CCfgDataManager::CreateCfgFile( char * pbyFileName )
{
	char achDirName[256]={0};
    char *pchDest = NULL;
    FILE    *stream = fopen( pbyFileName, "rb" );

	//�Ѿ����ڣ��򷵻س���
    if( stream != NULL )
    {
		fclose( stream );
        return TRUE;
    }

	/*�ȴ���Ŀ¼*/
	strncpy( achDirName, pbyFileName, sizeof(achDirName) );

	pchDest = strstr( achDirName, FILE_UMSCFG_INI );
	if ( !pchDest )
	{
        msgprint("[MTCFGDATA]:[CreateCfgFile] Wrong Get file path %s error \n",
			achDirName);
		return FALSE;
	}
	
	pchDest--;
	if ( *pchDest != '\\' && *pchDest != '/' )
	{
	    msgprint("[MTCFGDATA]:[CreateCfgFile] %s Wrong %s file path %d\n",
			__FILE__,pchDest,__LINE__ );
		return FALSE;
	}
		
	*pchDest = '\0';

	if( strlen(achDirName) != 0 )
	{
		UmsMakeDir( achDirName );
	}
	else
	{
		msgprint("[MTCFGDATA]:[CreateCfgFile]  %s Wrong %s file path %d\n",
			__FILE__,achDirName,__LINE__ );
		return FALSE;
	}

	/*����һ�����ļ�*/
    stream = fopen( pbyFileName, "w" );
	if ( !stream )
	{
        msgprint("[MTCFGDATA]:[CreateCfgFile]  %s Wrong %s file path %d\n", 
			__FILE__,pbyFileName,__LINE__ );
		return FALSE;
	}
	fclose( stream );

	return TRUE;
}
/*====================================================================
  �� �� ���� EraseRawDisk
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� void 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2005/9/2      1.0		    �� ��                   ����
======================================================================*/

void CCfgDataManager::EraseRawDisk()
{
	memset( m_pbyBlockMem, 0, m_dwBlockSize );
	for ( u8 i =0; i<SECTION_NUM; i++ )
	    WriteData( i, m_pbyBlockMem, m_dwBlockSize ); 
}

/*====================================================================
  �� �� ���� ShowRawDisk
  ��    �ܣ� 
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� 
  �� �� ֵ�� API void 
  --------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
  2005/9/2      1.0		    �� ��                   ����
======================================================================*/
API void ShowRawDisk( )
{
	g_cUmsCfgDataMan.ShowCurrentSection();
}

API void ShowCfgInfo()
{
	g_bUmsShowConfig_info = !g_bUmsShowConfig_info;
	msgprint("[ShowCfgInfo], print: %s \n", (g_bUmsShowConfig_info)?"on":"off");
}
static BOOL SaveDataToFile(u8* pdata,u32 dwLen)
{
	if(!g_cUmsCfgDataMan.SaveData(pdata,dwLen))
	{
		msgprint("[MtConfig]save data to rawdisk error\n");
		return FALSE;
	}
	return TRUE;
}

API BOOL RegisterConfigFile(s8* szFileName)
{
	FILE* pfFile = fopen(szFileName,"rb");
	if(NULL == pfFile)
	{
		msgprint("[MtConfig] open cfg file %s error",szFileName);
		return FALSE;
	}
	fseek(pfFile, 0L, SEEK_END);
	u32  dwLen = ftell(pfFile);
	u8*  pbySaveData = (u8*)malloc(dwLen);
	if(NULL == pbySaveData)
	{
		msgprint("[MtConfig]realloc mem faill\n");
		return FALSE;
	}
	memset(pbySaveData,0,dwLen);
	fseek(pfFile,0L,SEEK_SET);
	u32 dwReadLen = fread(pbySaveData,sizeof(char),
		dwLen*sizeof(char),	pfFile);
	if(dwReadLen != dwLen)
	{
		msgprint("[MtConfig]write config file faill\n");
		return FALSE;
	}
	fclose(pfFile);

    return SaveDataToFile(pbySaveData,dwLen);	
}
