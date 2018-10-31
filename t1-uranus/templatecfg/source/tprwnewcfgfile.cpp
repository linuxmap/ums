#include "tprwnewcfgfile.h"
#include "tpstruct.h"
#include "kdvsys.h"
#include <string.h>
#include "tplog.h"
#include "umsobject.h"
#include "umsconfig.h"

#include "umsxmltype.h"

static FILE* s_pfCfgFile = NULL;
               
static BOOL IsValidFile( FILE *pfFile )
{
	fseek(pfFile,0,SEEK_END);
	u32 length = ftell(pfFile);
	if(length>0)
	{
		fseek(pfFile,0,SEEK_SET);
		return TRUE;
	}
	else
	{
		fseek(pfFile,0,SEEK_SET);
		return FALSE;
	}


}

/*====================================================================
�� �� ���� ReadSimpleValFromTPFile
��    �ܣ� ģ�溯�������ݴ����Ƭ��ֵ����ֵ���������Ҫ������ֵ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� s8 *pchBuf ����Ĵ�����ݵĻ���
           u16 ���ݵĳ���
		   T &val ģ������
		   const s8 *const pchSection �����ļ��е�Ƭ��ֵ
		   const s8 *const pchKey �����ļ��еļ�ֵ
		   wIndex 

�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
template<class T>  
static BOOL ReadSimpleValFromTPFile( s8 *pchBuf,
								  u16 wLen,
								  T &val,
								  const s8 *const  pchSection,
								  const s8 *const  pchKey )
{
	if ( NULL == s_pfCfgFile )
	{
		MdlError(Ums_Mdl_Cfg, ("[ReadSimpleValFromTPFile]The FILE pointer is NULL at %s :%d\n",
			__FILE__, __LINE__ ));
		return FALSE;
	}
	BOOL bResult = FALSE;
	memset( pchBuf, 0, wLen );
	bResult = GetRegKeyString2( s_pfCfgFile, pchSection, pchKey, "", pchBuf, wLen );
	if( !bResult ) 
	{
		MdlError(Ums_Mdl_Cfg, ("[ReadSimpleValFromTPFile]Read TP INI File Fail When %s, %s, val is %s\n", pchSection, pchKey, pchBuf ));
		return FALSE;
	}
	if( 0 == strlen(pchBuf) ) 
	{
		MdlError(Ums_Mdl_Cfg, ("[ReadSimpleValFromTPFile]Read empty data at %s : %d\n", __FILE__, __LINE__ ));
		return FALSE;
	}
	
	s32 dwVal = 0;
	dwVal = atol(pchBuf);
	val = (T)dwVal;
	return TRUE;
}


/*====================================================================
�� �� ���� ReadStringValFromTPFile
��    �ܣ� ���ݴ����Ƭ��ֵ����ֵ���������Ҫ������ֵ
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� s8 *pchBuf ����������ڴ�����ݵĻ���
           u16 wLen   ���ݵĳ���
		   T &val ģ������
		   const s8*const  pchSection �����ļ��е�Ƭ��ֵ
	       const s8*const pchKey      �����ļ��еļ�ֵ

�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static inline BOOL  ReadStringValFromTPFile(s8* const pchBuf,
										   u16 wLen,
								           const s8*const pchSection,
								           const s8*const pchKey)
{
	s8 achTemp[256] = {0};
	BOOL bResult = GetRegKeyString2(s_pfCfgFile,pchSection,
		pchKey,"",achTemp,sizeof(achTemp));
	if(!bResult) return FALSE;
	
	strncpy(pchBuf,achTemp,wLen);
	pchBuf[wLen -1] = '\0';
	return TRUE;
}


/*====================================================================
�� �� ���� WriteSimpleValToTPFile
��    �ܣ� ģ�溯�������ݴ���Ĳ�ͬ�����͵���ֵ��д���ļ���Ӧ
           ��Ƭ�κͼ�ֵ��
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� T val ģ������
		   const s8 *const pchSection �����ļ��е�Ƭ��ֵ
		   const s8 *const pchKey �����ļ��еļ�ֵ
		   u16 �ļ�����

�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
template<class T>
static inline BOOL WriteSimpleValToTPFile( T val,
										 const s8 *const  pchSection,
										 const s8 *const  pchKey,
										 s8* szFileName )
{
	if ( !SetRegKeyInt( szFileName, pchSection, pchKey, ( s32 )val ) )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}

/*====================================================================
�� �� ���� WriteStringValToTPFile
��    �ܣ� ���ݴ�����ַ�����д���Ӧ��Ƭ��ֵ�ͼ�ֵ
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� s8 *pchVal �ַ���
		   const s8 *const pchSection �����ļ��е�Ƭ��ֵ
		   const s8 *const pchKey �����ļ��еļ�ֵ

�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static inline BOOL WriteStringValToTPFile( const s8 *pchVal,
										 const s8 *const  pchSection,
										 const s8 *const  pchKey,
										 s8* szFileName)
{
	if ( !SetRegKeyString( szFileName, pchSection, pchKey, pchVal ) )
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}

/*====================================================================
�� �� ���� SaveConfName
��    �ܣ� �����������
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveConfName( const s8 achConfName[], u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteStringValToTPFile( achConfName, 
		                  achSectionBuf, 
						  tpMeetingName, szFileName);
}

/*====================================================================
�� �� ���� SaveConfE164
��    �ܣ� �������E164
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveConfE164( const s8 achConfE164[], u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteStringValToTPFile( achConfE164, 
		                  achSectionBuf, 
						  tpE164, szFileName);
}


/*====================================================================
�� �� ���� SaveStartTime
��    �ܣ� ������鿪ʼʱ��
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveStartTime( time_t tStartTime, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( tStartTime, 
		                  achSectionBuf, 
						  tpStartTime, szFileName);
}


/*====================================================================
�� �� ���� SaveEncryptInfo
��    �ܣ� ����������ģʽ
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2014/10/27     1.0		    Ҷ�ȶ�                 ����
======================================================================*/

static void SaveEncryptInfo( TTPEncrypt tEncrypt,BOOL32 bDefaultEncrypt, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[16] = "";
	memset(achSectionBuf,0,sizeof(achSectionBuf));
	sprintf(achSectionBuf,"%s%d",template_,wIndex+1 );
	
	if (strlen(tEncrypt.m_achEncKey) > TP_ENCRYPT_KEY_LEN)	            
	{
		return ;
	}
	WriteSimpleValToTPFile(tEncrypt.m_emEncryptModel,achSectionBuf,tpEncryptType,szFileName);
	WriteStringValToTPFile(tEncrypt.m_achEncKey,achSectionBuf,tpEncryptKey,szFileName);
	WriteSimpleValToTPFile(bDefaultEncrypt,achSectionBuf,tpDefaultEncrypt,szFileName);
	
}

static void SaveVmpMemberCfg(const TSaveVmpCfg tCfg, u16 wIndex, s8* pszFileName)
{
	s8 achSectionBuf[64] = {0};
	sprintf(achSectionBuf, "%s%d", template_, wIndex + 1);
 
	u16 wEpIndex = 0;
	s8 achVmpEpList[64] = {0};
	//����ϳɷ��
	WriteSimpleValToTPFile( tCfg.m_emStyle, achSectionBuf, tpVmpPlanStyle, pszFileName);
	WriteSimpleValToTPFile( tCfg.m_wEpNum, achSectionBuf, tpVmpPlanEpNum, pszFileName);
	WriteSimpleValToTPFile(tCfg.m_wSpeakerIndx,achSectionBuf,tpVmpPlanSpeakIndex,pszFileName);
	WriteSimpleValToTPFile(tCfg.m_wDualIndx,achSectionBuf,tpVmpPlanDualIndex,pszFileName);

	for(wEpIndex = 0; wEpIndex < tCfg.m_wEpNum; ++wEpIndex)
	{		
		memset( achVmpEpList, 0, sizeof( achVmpEpList ) );
		sprintf( achVmpEpList, "%s%d", tpVmpPlanEpAlias_, wEpIndex+1 );
 	 	WriteStringValToTPFile( tCfg.m_atEpList[wEpIndex].m_tEpAlias.m_abyAlias, achSectionBuf, achVmpEpList, pszFileName);
		
		memset( achVmpEpList , 0 ,sizeof( achVmpEpList ));
		sprintf( achVmpEpList, "%s%d", tpVmpPlanScrIndex_, wEpIndex+1 );
		WriteSimpleValToTPFile( tCfg.m_atEpList[wEpIndex].m_wScrIndx, achSectionBuf, achVmpEpList,pszFileName);
	}
}

/*====================================================================
�� �� ���� SaveEpAddrNum
��    �ܣ� ��������������
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveEpAddrNum( u16 wNum, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wNum,
						  achSectionBuf,
						  tpEpAddrNum, szFileName);
}


/*====================================================================
�� �� ���� SaveCnsList
��    �ܣ� ����������˵�LIST��Ϣ
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveCnsList( const TEpAddr tCnsList[], u16 wIndex, u16 wAddrNum, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	u16 wListIndex = 0;
	s8 achBuf[64] = "";

	if( 0 == wAddrNum)
	{
		return;
	}

	for ( wListIndex = 0; wListIndex < wAddrNum; ++wListIndex )
	{
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpAddrID_, wListIndex+1 );
		WriteSimpleValToTPFile( tCnsList[wListIndex].m_wEpID,
						      achSectionBuf,
							  achBuf, szFileName);
		memset( achBuf, 0 ,sizeof( achBuf ));
		sprintf( achBuf, "%s%d",tpIsAliasIP_,wListIndex+1 );
		WriteSimpleValToTPFile(tCnsList[wListIndex].m_tEpAddr.m_bAliasIP,
								achSectionBuf,
								achBuf,szFileName);

		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpAddrAliasType_, wListIndex+1 );
		WriteSimpleValToTPFile( tCnsList[wListIndex].m_tEpAddr.m_tAlias.m_byType, 
			                  achSectionBuf,
							  achBuf, szFileName);
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpAddrAlias_, wListIndex+1 );
		WriteStringValToTPFile( tCnsList[wListIndex].m_tEpAddr.m_tAlias.m_abyAlias,
							  achSectionBuf,
							  achBuf,szFileName);
		//164
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpAddrE164Type_, wListIndex+1 );
		WriteSimpleValToTPFile( tCnsList[wListIndex].m_tEpAddr.m_tE164.m_byType, 
			achSectionBuf,
			achBuf, szFileName);
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpAddrE164_, wListIndex+1 );
		WriteStringValToTPFile( tCnsList[wListIndex].m_tEpAddr.m_tE164.m_abyAlias,
			achSectionBuf,
			achBuf,szFileName);

		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", toEpAddrCallType_, wListIndex+1 );
		WriteSimpleValToTPFile( tCnsList[wListIndex].m_tEpAddr.m_byCallType,
			achSectionBuf,
			achBuf,szFileName);

		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpAddrIPType_, wListIndex+1 );
		WriteSimpleValToTPFile( tp_Alias_IP, 
			achSectionBuf,
			achBuf, szFileName);
		
		s8	abyIP[TP_MAX_ALIAS_LEN + 1] = {0};
		sprintf(abyIP, ""TPIPFORMAT"", Tpu32ToIP(tCnsList[wListIndex].m_tEpAddr.m_dwIP));
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpAddrIP_, wListIndex+1 );
		WriteStringValToTPFile( abyIP,
			achSectionBuf,
			achBuf,szFileName);

	}
}

//�������ۿ���
static void SaveAudMixSwitch(BOOL32 bSwitch, u16 wIndex, s8* pszFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( bSwitch, achSectionBuf, tpDiscussOn, pszFileName);
}

//����������������
static void SaveDiscussVacSwitch(BOOL32 bSwitch, u16 wIndex, s8* pszFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( bSwitch, achSectionBuf, tpDiscussVacOn, pszFileName);
}

/*====================================================================
�� �� ���� SaveAuxMixList
��    �ܣ� ��������б���Ϣ
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveAuxMixList( const u16 awList[], u16 wIndex, u16 wAudNum,s8* pszFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	u16 wListIndex = 0;
	s8 achBuf[64] = "";
	for ( wListIndex = 0; wListIndex < wAudNum; ++wListIndex )
	{
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpAudMixID_, wListIndex+1);
		WriteSimpleValToTPFile( awList[wListIndex], achSectionBuf, achBuf, pszFileName);
	}
}

//������ѯ����
static void SaveTurnSwitch(BOOL32 bSwitch, u16 wIndex, s8* pszFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( bSwitch, achSectionBuf, tpTurnOn, pszFileName);	
}

/*====================================================================
�� �� ���� SaveTurnInterval
��    �ܣ� ������ѯʱ����
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveTurnInterval( u16 wInterval, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wInterval, 
		                  achSectionBuf, 
						  tpTurnInterval,szFileName);
}

/*====================================================================
�� �� ���� SaveTurnNum
��    �ܣ� ������ѯ����
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveTurnNum( u16 wNum, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wNum,
						  achSectionBuf,
						  tpTurnNum,szFileName);
}

/*====================================================================
�� �� ���� SaveTurnList
��    �ܣ� ������ѯ�б���Ϣ
     
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� 

�� �� ֵ�� 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
static void SaveTurnList( const u16 awList[], u16 wIndex, u16 wTurnNum, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );

	if ( 0 == wTurnNum )
	{
		return;
	}

	u16 wListIndex = 0;
	s8 achBuf[64] = "";
	for ( wListIndex = 0; wListIndex < wTurnNum; ++wListIndex )
	{
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpTurnID_, wListIndex+1);
		WriteSimpleValToTPFile( awList[wListIndex], 
							  achSectionBuf,
							  achBuf,szFileName);
	}
}

static void SaveMainVidNum(u16 wNum, u16 wIndex, s8* szFileName) //
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wNum,
						  achSectionBuf,
						  tpMainVidNum,szFileName);
}

static void SaveAudioNum(u16 wNum, u16 wIndex, s8* szFileName) 
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wNum,
						  achSectionBuf,
						  tmAudioNum,szFileName);
}

//������Ƶ��ʽ
static void SaveAudioRes(const TUmsAudFormat tRes[], u16 wIndex, u16 wAudioNum, s8* pszFileName)
{
	s8 achSectionBuf[64] = {0};
	sprintf(achSectionBuf, "%s%d", template_, wIndex + 1);
	
	if (0 == wAudioNum)
	{
		return;
	}
	
	if (wAudioNum > TP_CONF_MAX_AUD_FMT_NUM)
	{
		return;
	}
	
	u16 wResIndex = 0;
	s8 achBuf[64] = {0};
	
	for(wResIndex = 0; wResIndex < wAudioNum; ++wResIndex)
	{
		
		//��ƵЭ������
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d",tpAudioFormat_ , wResIndex+1 );
		WriteSimpleValToTPFile( tRes[wResIndex].m_emFormat, achSectionBuf, achBuf, pszFileName);
		//��ƵƵ��
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d",tpAudioFreq_ , wResIndex+1 );
		WriteSimpleValToTPFile( tRes[wResIndex].m_emSampleFreq, achSectionBuf, achBuf, pszFileName);
		
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d",tpAudioReservel_ , wResIndex+1 );
		WriteSimpleValToTPFile( tRes[wResIndex].m_byReserve1, achSectionBuf, achBuf, pszFileName);
		
	}

}
//��������Ƶ��ʽ
static void SaveViedoMainRes(const TUmsVidFormat tRes[], u16 wIndex, u16 wVideoNum, s8* pszFileName)
{
	s8 achSectionBuf[64] = {0};
	sprintf(achSectionBuf, "%s%d", template_, wIndex + 1);
	
	if (0 == wVideoNum)
	{
		return;
	}
	
	if (wVideoNum > TP_CONF_MAX_MINOR_VIDEO_RES_NUM)
	{
		return;
	}

	u16 wMainResIndex = 0;
	s8 achBuf[64] = {0};

	for(wMainResIndex = 0; wMainResIndex < wVideoNum; ++wMainResIndex)
	{

		//��Ƶ���ʼ���
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpMainVideoLvl_, wMainResIndex+1 );
		WriteSimpleValToTPFile( tRes[wMainResIndex].m_emQualityLvl, achSectionBuf, achBuf, pszFileName);
			
		//��Ƶ�ֱ���
		memset(achBuf, 0, sizeof(achBuf));
		sprintf(achBuf, "%s%d", tpVideoMainRes_, wMainResIndex +1);
		WriteSimpleValToTPFile(tRes[wMainResIndex].m_emRes, achSectionBuf, achBuf, pszFileName);
			
		//��Ƶ֡��
		memset(achBuf, 0, sizeof(achBuf));
		sprintf(achBuf, "%s%d", tpMainVideoFrame_, wMainResIndex + 1);
		WriteSimpleValToTPFile(tRes[wMainResIndex].m_wFrameRate, achSectionBuf, achBuf, pszFileName);	
	}
}

static void SaveMinorVidNum(u16 wNum, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wNum,
						  achSectionBuf,
						  tpMinorVidNum,szFileName);
}

//���渨��Ƶ��ʽ
static void SaveVideoMinorRes(const TUmsVidFormat tRes[], u16 wIndex, u16 wVidNum, s8* pszFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex + 1);
	
	if (0 == wVidNum)
	{
		return;
	}
	
	u16 wMinorResIndex = 0;
	s8 achBuf[64] = "";
	
	for(wMinorResIndex = 0; wMinorResIndex < wVidNum; ++wMinorResIndex)
	{
		//���ʼ���
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpMinorVideoLvl_, wMinorResIndex+1 );
		WriteSimpleValToTPFile( tRes[wMinorResIndex].m_emQualityLvl, achSectionBuf, achBuf, pszFileName);
		
		//��Ƶ�ֱ���
		memset(achBuf, 0, sizeof(achBuf));
		sprintf(achBuf, "%s%d", tpVideoMinorRes_, wMinorResIndex +1);
		WriteSimpleValToTPFile(tRes[wMinorResIndex].m_emRes, achSectionBuf, achBuf, pszFileName);
		
		//��Ƶ֡��
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpMinorVideoFrame_, wMinorResIndex+1 );
		WriteSimpleValToTPFile( tRes[wMinorResIndex].m_wFrameRate, achSectionBuf, achBuf, pszFileName);
	}
}

static void SaveConfUpBandWid(u32 wBandWid, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wBandWid,
						  achSectionBuf,
						  tpConfUpBandWid, 
						  szFileName);
}

static void SaveConfDownandWid(u32 wBandWid, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wBandWid,
						  achSectionBuf,
						  tpConfDownBandWid, 
						  szFileName);
}

static void SaveHpConfBitRate(u16 wConfBitRate, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	WriteSimpleValToTPFile( wConfBitRate,
						  achSectionBuf,
						  tpConfBitRate, 
						  szFileName);
}

static void SaveHpConfDualBitRate(u16 wConfBitRate, u16 wIndex, s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );	
	WriteSimpleValToTPFile( wConfBitRate,
						  achSectionBuf,
						  tpConfDualBitRate,
						  szFileName);
}
//����᳡����Э����Ϣ
static void SaveEpCallProtocol(const u16 wEpID[],const EmTpConfProtocol emcallPro[],u16 wNum,u16 wIndex,s8* szFileName)
{
	s8 achSectionBuf[64] = "";
	sprintf(achSectionBuf, "%s%d", template_, wIndex+1 );
	u16 wListIndex = 0;
	s8 achBuf[64] = "";
	for ( wListIndex = 0; wListIndex < wNum; ++wListIndex )
	{
		memset( achBuf, 0, sizeof( achBuf ) );
		sprintf( achBuf, "%s%d", tpEpCallProtocol_, wEpID[wListIndex] + 1);	

		WriteStringValToTPFile( TpEnumString(EmTpConfProtocol, emcallPro [wListIndex]),
			             achSectionBuf, 
						  achBuf, szFileName);
		


	}	
}
/*====================================================================
�� �� ���� SaveDataToTpFile
��    �ܣ� ���ڴ����ݽṹSAVE������ģ���ļ���
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� const s8 szFileName[TP_FILENAME_LENGTH],TTPConfTemplate atTPConfTemplate[TP_CONFTEMPLATE_MAXNUM]
�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
BOOL  SaveDataToTpFile( const s8 szFileName[TP_FILENAME_LENGTH], const TConfTemplateLocal atAllTpData[TP_CONFTEMPLATE_MAXNUM], u16 wNum )
{
	s8 achFullFileName[TP_FILENAME_LENGTH+1] = {0};

	if ( NULL == szFileName )
	{
		MdlError(Ums_Mdl_Cfg, ("[SaveDataToTpFile]The File name is NULL\n"));
		
		return FALSE;
	}
	
	sprintf(achFullFileName,"%s%d.ini",szFileName,wNum+1);
	
	FILE* pfFileName = fopen( achFullFileName,"wb" );

	if(NULL == pfFileName)
	{
		MdlError(Ums_Mdl_Cfg,("[SaveDataToTpFile] SaveDataToTpFile %s error ", achFullFileName ));
		return FALSE;
	}
	BOOL bResult = SaveDataToTpFile( pfFileName, atAllTpData, wNum, achFullFileName);
	fclose(pfFileName);
	return bResult;
}



/*====================================================================
�� �� ���� SaveDataToTpFile
��    �ܣ� ���ڴ����ݽṹSAVE������ģ���ļ���
�㷨ʵ�֣� 
ȫ�ֱ����� 
��    ���� FILE* pfFileName,TTPConfTemplate atTPConfTemplate[TP_CONFTEMPLATE_MAXNUM]
�� �� ֵ�� BOOL �ɹ�����TRUE��ʧ�ܷ���FALSE 
--------------------------------------------------------------------
�޸ļ�¼��
��  ��	      �汾		    �޸���		�߶���    �޸�����
2011/7/25     1.0		    ������                   ����
======================================================================*/
BOOL  SaveDataToTpFile( FILE* pfFileName, const TConfTemplateLocal atAllTpData[TP_CONFTEMPLATE_MAXNUM],u16 wNum, s8* szFileName)
{

	if ( NULL == pfFileName )
	{
		MdlError(Ums_Mdl_Cfg, ("[SaveDataToTpFile]The File point is NULL\n" ));
		return FALSE;
	}
	
	//��ָ̬���ʼ��
	s_pfCfgFile = pfFileName;
	
	SaveConfName(atAllTpData[wNum].m_achConfName, wNum, szFileName);
	SaveConfE164(atAllTpData[wNum].m_achConfE164, wNum, szFileName);
	SaveStartTime(atAllTpData[wNum].m_tStartTime, wNum, szFileName);
	SaveEpAddrNum(atAllTpData[wNum].m_atEpList.m_wNum, wNum, szFileName);
	SaveCnsList(atAllTpData[wNum].m_atEpList.m_tCnsList, wNum, atAllTpData[wNum].m_atEpList.m_wNum, szFileName);

	SaveTurnSwitch(atAllTpData[wNum].m_tTurnList.m_bPollOn, wNum, szFileName);
	SaveTurnInterval(atAllTpData[wNum].m_tTurnList.m_wInterval, wNum, szFileName);
	SaveTurnNum(atAllTpData[wNum].m_tTurnList.m_wNum, wNum, szFileName);
	SaveTurnList(atAllTpData[wNum].m_tTurnList.m_awList, wNum, atAllTpData[wNum].m_tTurnList.m_wNum, szFileName);

	SaveAudMixSwitch(atAllTpData[wNum].m_atAuxMixList.m_bAudMixOn, wNum, szFileName);
	SaveDiscussVacSwitch(atAllTpData[wNum].m_atAuxMixList.m_bVacOn,wNum, szFileName);
	SaveAuxMixList(atAllTpData[wNum].m_atAuxMixList.m_awList, wNum, atAllTpData[wNum].m_atAuxMixList.GetMixNum(),szFileName);
	//����ģ����Ƶ��ʽ����
	SaveAudioNum(atAllTpData[wNum].m_wAudFmtNum, wNum, szFileName);
	SaveAudioRes(atAllTpData[wNum].m_atAudFmt,wNum,atAllTpData[wNum].m_wAudFmtNum,szFileName);
	//����������Ƶ�ֱ���
	SaveMainVidNum(atAllTpData[wNum].m_wMainNum, wNum, szFileName);
	SaveViedoMainRes(atAllTpData[wNum].m_atTpMainVideoRes, wNum, atAllTpData[wNum].m_wMainNum, szFileName);
	SaveMinorVidNum(atAllTpData[wNum].m_wMinorNum, wNum, szFileName);
	SaveVideoMinorRes(atAllTpData[wNum].m_atTpMinorVideoRes, wNum, atAllTpData[wNum].m_wMinorNum,szFileName);

	SaveHpConfBitRate(atAllTpData[wNum].m_wConfBitRate, wNum, szFileName);
	SaveHpConfDualBitRate(atAllTpData[wNum].m_wHpDualBitRate, wNum, szFileName);

	SaveConfUpBandWid(atAllTpData[wNum].m_wUpBandWid, wNum, szFileName);
	SaveConfDownandWid(atAllTpData[wNum].m_wDownBandWid, wNum, szFileName);
	//���������Կģʽ������
	SaveEncryptInfo(atAllTpData[wNum].m_tEncrypt,atAllTpData[wNum].m_bDefaultEncrypt,wNum,szFileName);

	//����ģ�廭��ϳ�Ԥ��
	SaveVmpMemberCfg(atAllTpData[wNum].m_tVmpCfg,wNum,szFileName);
	
	SaveEpCallProtocol(atAllTpData[wNum].m_tTempCfgEx.m_awEpID,atAllTpData[wNum].m_tTempCfgEx.m_aemCallProtocol,
		                atAllTpData[wNum].m_tTempCfgEx.m_wNum,wNum,szFileName);
	s_pfCfgFile = NULL;
	return TRUE;

}

BOOL SaveDataToControlFile(const s8 *szControlFile, const TControlData tControlData)
{
	if( NULL == szControlFile )
	{
		MdlError(Ums_Mdl_Cfg,("[SaveDataToControlFile]pointer NULL error\n"));
		return FALSE;
	}

	FILE *pFile = fopen(szControlFile,"wb");

	if( NULL == pFile )
	{
		return FALSE;
	}
	
	fclose(pFile);

	BOOL bret = SetRegKeyInt(szControlFile,validTpNum,validTpNumKey,tControlData.m_wValidNum);

	s8 achSectionName[256] = {0};
	u16 wTotalValidNum = 0;

	for(u16 wIndex = 0; wIndex<TP_CONFTEMPLATE_MAXNUM; ++wIndex)
	{
		memset(achSectionName,0,sizeof(achSectionName));

		if(tControlData.m_abValidSeq[wIndex])
		{
			sprintf(achSectionName,"%s%d",validSeq_,wTotalValidNum+1);
			SetRegKeyInt(szControlFile,validTpNum,achSectionName,wIndex+1);
			++wTotalValidNum;
		}
	}

	return bret;
}