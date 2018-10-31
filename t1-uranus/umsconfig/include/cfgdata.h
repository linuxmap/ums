/*******************************************************************************
 *  ģ����   :                                                                 *
 *  �ļ���   : sysdata.h                                                       *
 *  ����ļ� :                                                                 *
 *  ʵ�ֹ��� :                                                                 *
 *  ����     : �� ��                                                           *
 *  �汾     : V4.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  �޸ļ�¼:                                                                  *
 *    ��  ��      �汾        �޸���      �޸�����                             *
 *  2005/8/9      1.0         �� ��       ����                                 *
 *                                                                             *
 *******************************************************************************/
#ifndef SYSDATA_H
#define SYSDATA_H

#include "umsconfig.h"
#include "umsinnerstruct.h"

#ifdef   _VXWORKS_
	#include <inetlib.h>
	#include <semlib.h>
	#include <iolib.h>
	#include <dosfslib.h>
	#include <usrlib.h>
	#include "brddrvlib.h"
#endif

#ifdef _LINUX_
#include "brdwrapper.h"
#include "nipwrapper.h"
#endif


//ϵͳ��Ϣ
const 	  s8 umsSecSystem[] = "umsSystem";
//�����ļ����汾
const     s8 umsKeySysConfigFileVersion[] = "umssysConfigFileVersion";
//�����ļ�����ʱ��
const     s8 umsKeySysConfigFileDate[] = "umssysConfigFileDate";
//�����ļ��汾��
const   u8 mtConfigFileVersion = 4 ;


/************************************************************************/
/*                         ����Ums����                                  */
/************************************************************************/
const	s8 umsLocalInfo[] = "LocalInfo";
//����CNS IP
const	s8 umsKeyUmsIp[] = "LocalIp";
const	s8 umsKeyNetMask[] = "LocalNetMask";
const	s8 umsKeyGateWay[] = "LocalGateWay";

/************************************************************************/
/*                         ����Ums��������                                  */
/************************************************************************/
const	s8 umsLocalInfoVir[] = "LocalInfoVir";
//����CNS IP
const	s8 umsKeyUmsIpVir[] = "LocalIp";
const	s8 umsKeyNetMaskVir[] = "LocalNetMask";
const	s8 umsKeyGateWayVir[] = "LocalGateWay";
/************************************************************************/
/*                         ����Ums����1                                  */
/************************************************************************/
const	s8 umsLocalInfoEth1[] = "LocalInfoEth1";
//����CNS IP
const	s8 umsKeyUmsIpEth1[] = "LocalIp";
const	s8 umsKeyNetMaskEth1[] = "LocalNetMask";
const	s8 umsKeyGateWayEth1[] = "LocalGateWay";
/************************************************************************/
/*                         ����Ums��������1                                  */
/************************************************************************/
const	s8 umsLocalInfoEth1Vir[] = "LocalInfoEth1Vir";
//����CNS IP
const	s8 umsKeyUmsIpEth1Vir[] = "LocalIp";
const	s8 umsKeyNetMaskEth1Vir[] = "LocalNetMask";
const	s8 umsKeyGateWayEth1Vir[] = "LocalGateWay";
//udp������ʼ�˿�
const	s8 umsKeyBeginUdpTransPort[] = "BeginUdpTransPort";

//CMS�����˿�
const	s8 umsKeyListionPortForUi[] = "ListionPortForUi";

//һ������������
const	s8 umsKeyNumMaxOnecCall[] = "NumMaxOnecCall";
//ums old ip
const   s8 umsKeyOldIP[] = "UmsOldIP";



/************************************************************************/
/*                         SIPע����Ϣ����                              */
/************************************************************************/
const   s8 umsSipReg[] = "SipRegInfo";
//�Ƿ�ע��
const   s8 umsKeySipRegUsed[] = "bUsed";
//ע�������IP
const   s8 umsKeySipRegIP[] = "ServiceIp";
//ע��������˿�
const   s8 umsKeySipRegPort[] = "ServicePort";
//��ʱʱ��
const   s8 umsKeySipRegExpire[] = "wExpire";


const   s8 umsGKReg[] = "GKRegInfo";
//�Ƿ�ע��
const   s8 umsKeyGKRegUsed[] = "bUsed";
//ע�������IP
const   s8 umsKeyGKRegIP[] = "GKIp";
//��ʱʱ��
const   s8 umsKeyGKRegExpire[] = "wExpire";


/************************************************************************/
/*                         SIP������Ϣ����                              */
/************************************************************************/
const   s8 umsSipCall[] = "SipCallInfo";
//���ж˿�
const   s8 umsKeySipCallingPort[] = "CallingPort";
//��������
const   s8 umsKeySipMaxCallNum[] = "MaxCallNum";
//��ʱʱ��
const   s8 umsKeySipCallKeepAliveTime[] = "KeepAliveTime";


/************************************************************************/
/*                         HDU��Ϣ����                              */
/************************************************************************/
const   s8 umsHduInfo[] = "HduInfo_";
const   s8 umsKeyHduLayer[] = "HduLayer";
const   s8 umsKeyHduSlot[] = "HduSlot";
const   s8 umsKeyBQtHdu[] = "bQtHdu";
const   s8 umsKeyHduIp[] = "HduIp";
const   s8 umsKeyHduAlias[] = "HduAlias";
const   s8 umsKeyHduStartPort[] = "HduStartPort";
const   s8 umsKeyHduChanNum[] = "HduChanNum";
const	s8 umsKeyHduVmp[] = "HduVmp";
const   s8 umsKeyHduOutTypeChan_[] = "HduOutTypeChan_";
const   s8 umsKeyHduOutModeChan_[] = "HduOutModeChan_";
const   s8 umsKeyHduZoomRateChan_[] = "HduZoomRateChan_";
const   s8 umsKeyHduShowModeChan_[] = "HduShowModeChan_";

/************************************************************************/
/*                         HDU�����Ϣ����                              */
/************************************************************************/
const	s8 umsHduStyleInfo[] = "umsHduStyleInfo";
const	s8 umsKeyHduStyleRow[] = "HduStyleRow";
const	s8 umsKeyHduStyleCol[] = "HduStyleCol";
const	s8 umsKeyHduStyleLayer_[] = "HduStyleLayer_";
const	s8 umsKeyHduStyleSlot_[] = "HduStyleSlot_";
const	s8 umsKeyHduStyleChanIndex_[] = "HduStyleChanIndex_";
const	s8 umsKeyHduStyleChanName_[] = "HduStyleChanName_";
const	s8 umsKeyHduStyleVmp_[] = "HduStyleVmp_";

/************************************************************************/
/*                         ������Ϣ����                             */
/************************************************************************/
const s8 umsBoardInfo[] = "umsBoardInfo";
const s8 umsBoardValidNum[] = "umsBoardValidNum";
//����
const s8 umsBoardInfo_[] = "BoardInfo_";
const s8 umsBoardID_[] = "umsBoardID_";
const s8 umsBoardType_[] = "umsBoardType_";
const s8 umsBoardLayer_[] = "umsBoardLayer_";
const s8 umsBoardSlot_[] = "umsBoardSlot_";
const s8 umsBoardIP_[] = "umsBoardIP_";
const s8 umsBoardState_[] = "umsBoardState_";
//����ģʽ
const s8 umsBoardModeType_[] = "umsBoardModeType_";
const s8 umsBoardModeAlias_[] = "umsBoardModeAlias_";
const s8 umsBoardEqpModeType_[] = "umsBoardEqpModeType_";
const s8 umsBoardModeEapId_[] = "umsBoardModeEapId_";
const s8 umsAudmixChanNum_[] = "umsAudmixChanNum_"; //����������·��

/************************************************************************/
/*                 ���Ӽ�������                                            */
/************************************************************************/
const s8 umsSecQuanTumEncInfo[] = "umsSecQuanTumEncInfo";
const s8 umsKeyQtOn[] = "umsQTOn";
const s8 umsKeyQTIP[] = "umsKeyQTIP";
const s8 umsKeyQTID[] = "umsKeyQTID";

/************************************************************************/
/*                 ���������������                                            */
/************************************************************************/
const s8 umsPwdCycleInfo[] = "umsPwdCycleInfo";
const s8 umsPwdCycleUsed[] = "bStart";
const s8 umsPwdCycleTimer[] = "umsPwdCycle";

/************************************************************************/
/*					mpc��ʱ��ͬ������                                            */
/************************************************************************/
const s8 umsNtpdInfo[] = "ntpdInfo";
const s8 umsNtpdIp[] = "NtpdIp";

typedef struct tagTALLConfigData
{
	TLocalUmsInfo       m_tLocalCnsInfo;
	TTPSipRegistrarCfg  m_tTPSipRegistrarCfg;
	TTPGKCfg			m_tGKRegCfg;
	TUmsStackCallCfg	m_tSipStackCallCfg;

	TTPBrdInfo          m_atBrdCfg[TP_BOARD_MAX_NUM];//����������Ϣ����
	u8					m_byBrdValidNum;             //��Ч���������
	THduCfgInfo         m_atHduCfg[HDU_MAX_NUM];     //����ǽ������Ϣ����
	THduStyleCfgInfo	m_tHduStyleCfg;				 //����ǽ���������Ϣ

    TTPQTEncryptInfo    m_tTPQTEncryptInfo;          //QTMT IP  QTID������Ϣ
	TPwdCycleInfo       m_tPwdCycleInfo;
	TNtpdInfo			m_tNtpdInfo;

}TALLConfigData,*PTALLConfigData;

extern TALLConfigData g_tALLConfigData;
/*====================================================================
    ������      ��SetFileReadOnly
    ����        ����ָ���ļ����ó�ֻ��
    �㷨ʵ��    ������ѡ�
    ����ȫ�ֱ�����
    �������˵����char* pchFileName:�ļ���
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/08/10    1.0         jianghy         ����
====================================================================*/
inline void SetFileReadOnly(char* pchFileName)
{
#ifdef _VXWORKS_
	struct stat fileStat;
	int fd;

	fd = open (pchFileName, O_RDONLY, 0);     /* open file */
	if( fd != ERROR )
	{
		fstat (fd, &fileStat);                    /* get file status */
		ioctl (fd, FIOATTRIBSET, (fileStat.st_attrib | DOS_ATTR_RDONLY)); /*set read-only flag*/
		close (fd);     /*close file*/                         
	}
#endif
	return;

}

/*====================================================================
    ������      ��SetFileReadWrite
    ����        ����ָ���ļ����óɿ�д
    �㷨ʵ��    ������ѡ�
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    03/08/10    1.0         jianghy         ����
====================================================================*/
inline void SetFileReadWrite(char* pchFileName)
{
#ifdef _VXWORKS_
	struct stat fileStat;
	int fd;

	fd = open (pchFileName, O_RDONLY, 0);     /*open file*/
	if( fd != ERROR )
	{
		fstat (fd, &fileStat);                    /*get file status*/
		ioctl (fd, FIOATTRIBSET, fileStat.st_attrib & !DOS_ATTR_RDONLY ); /*reset read-only flag*/                                         /* set read-only flag */
		close (fd);     /*close file*/                        
	}
#endif
	return;
}

class CFileAttrib
{
public:
	CFileAttrib( const s8 pbyFileName[] )
	{
#ifdef _VXWORKS_
		memset( m_abyFileName, 0, sizeof(m_abyFileName) );
		strncpy( (char*)m_abyFileName, (char*)pbyFileName, sizeof(m_abyFileName) );
		SetFileReadWrite( (char*)m_abyFileName );
#endif		
	}

	~CFileAttrib()
	{
#ifdef _VXWORKS_
		SetFileReadOnly( (char*)m_abyFileName );
#endif
	}

private:
	u8 m_abyFileName[256];
};


BOOL InitData();
#endif
