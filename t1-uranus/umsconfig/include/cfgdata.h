/*******************************************************************************
 *  模块名   :                                                                 *
 *  文件名   : sysdata.h                                                       *
 *  相关文件 :                                                                 *
 *  实现功能 :                                                                 *
 *  作者     : 张 飞                                                           *
 *  版本     : V4.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  修改记录:                                                                  *
 *    日  期      版本        修改人      修改内容                             *
 *  2005/8/9      1.0         张 飞       创建                                 *
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


//系统信息
const 	  s8 umsSecSystem[] = "umsSystem";
//配置文件主版本
const     s8 umsKeySysConfigFileVersion[] = "umssysConfigFileVersion";
//配置文件生成时间
const     s8 umsKeySysConfigFileDate[] = "umssysConfigFileDate";
//配置文件版本号
const   u8 mtConfigFileVersion = 4 ;


/************************************************************************/
/*                         本地Ums配置                                  */
/************************************************************************/
const	s8 umsLocalInfo[] = "LocalInfo";
//本地CNS IP
const	s8 umsKeyUmsIp[] = "LocalIp";
const	s8 umsKeyNetMask[] = "LocalNetMask";
const	s8 umsKeyGateWay[] = "LocalGateWay";

/************************************************************************/
/*                         本地Ums虚拟配置                                  */
/************************************************************************/
const	s8 umsLocalInfoVir[] = "LocalInfoVir";
//本地CNS IP
const	s8 umsKeyUmsIpVir[] = "LocalIp";
const	s8 umsKeyNetMaskVir[] = "LocalNetMask";
const	s8 umsKeyGateWayVir[] = "LocalGateWay";
/************************************************************************/
/*                         本地Ums配置1                                  */
/************************************************************************/
const	s8 umsLocalInfoEth1[] = "LocalInfoEth1";
//本地CNS IP
const	s8 umsKeyUmsIpEth1[] = "LocalIp";
const	s8 umsKeyNetMaskEth1[] = "LocalNetMask";
const	s8 umsKeyGateWayEth1[] = "LocalGateWay";
/************************************************************************/
/*                         本地Ums虚拟配置1                                  */
/************************************************************************/
const	s8 umsLocalInfoEth1Vir[] = "LocalInfoEth1Vir";
//本地CNS IP
const	s8 umsKeyUmsIpEth1Vir[] = "LocalIp";
const	s8 umsKeyNetMaskEth1Vir[] = "LocalNetMask";
const	s8 umsKeyGateWayEth1Vir[] = "LocalGateWay";
//udp传输起始端口
const	s8 umsKeyBeginUdpTransPort[] = "BeginUdpTransPort";

//CMS侦听端口
const	s8 umsKeyListionPortForUi[] = "ListionPortForUi";

//一次最大呼叫数量
const	s8 umsKeyNumMaxOnecCall[] = "NumMaxOnecCall";
//ums old ip
const   s8 umsKeyOldIP[] = "UmsOldIP";



/************************************************************************/
/*                         SIP注册信息配置                              */
/************************************************************************/
const   s8 umsSipReg[] = "SipRegInfo";
//是否注册
const   s8 umsKeySipRegUsed[] = "bUsed";
//注册服务器IP
const   s8 umsKeySipRegIP[] = "ServiceIp";
//注册服务器端口
const   s8 umsKeySipRegPort[] = "ServicePort";
//超时时间
const   s8 umsKeySipRegExpire[] = "wExpire";


const   s8 umsGKReg[] = "GKRegInfo";
//是否注册
const   s8 umsKeyGKRegUsed[] = "bUsed";
//注册服务器IP
const   s8 umsKeyGKRegIP[] = "GKIp";
//超时时间
const   s8 umsKeyGKRegExpire[] = "wExpire";


/************************************************************************/
/*                         SIP呼叫信息配置                              */
/************************************************************************/
const   s8 umsSipCall[] = "SipCallInfo";
//呼叫端口
const   s8 umsKeySipCallingPort[] = "CallingPort";
//最大呼叫数
const   s8 umsKeySipMaxCallNum[] = "MaxCallNum";
//超时时间
const   s8 umsKeySipCallKeepAliveTime[] = "KeepAliveTime";


/************************************************************************/
/*                         HDU信息配置                              */
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
/*                         HDU风格信息配置                              */
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
/*                         单板信息配置                             */
/************************************************************************/
const s8 umsBoardInfo[] = "umsBoardInfo";
const s8 umsBoardValidNum[] = "umsBoardValidNum";
//单板
const s8 umsBoardInfo_[] = "BoardInfo_";
const s8 umsBoardID_[] = "umsBoardID_";
const s8 umsBoardType_[] = "umsBoardType_";
const s8 umsBoardLayer_[] = "umsBoardLayer_";
const s8 umsBoardSlot_[] = "umsBoardSlot_";
const s8 umsBoardIP_[] = "umsBoardIP_";
const s8 umsBoardState_[] = "umsBoardState_";
//单板模式
const s8 umsBoardModeType_[] = "umsBoardModeType_";
const s8 umsBoardModeAlias_[] = "umsBoardModeAlias_";
const s8 umsBoardEqpModeType_[] = "umsBoardEqpModeType_";
const s8 umsBoardModeEapId_[] = "umsBoardModeEapId_";
const s8 umsAudmixChanNum_[] = "umsAudmixChanNum_"; //混音器混音路数

/************************************************************************/
/*                 量子加密配置                                            */
/************************************************************************/
const s8 umsSecQuanTumEncInfo[] = "umsSecQuanTumEncInfo";
const s8 umsKeyQtOn[] = "umsQTOn";
const s8 umsKeyQTIP[] = "umsKeyQTIP";
const s8 umsKeyQTID[] = "umsKeyQTID";

/************************************************************************/
/*                 密码更新周期配置                                            */
/************************************************************************/
const s8 umsPwdCycleInfo[] = "umsPwdCycleInfo";
const s8 umsPwdCycleUsed[] = "bStart";
const s8 umsPwdCycleTimer[] = "umsPwdCycle";

/************************************************************************/
/*					mpc板时间同步配置                                            */
/************************************************************************/
const s8 umsNtpdInfo[] = "ntpdInfo";
const s8 umsNtpdIp[] = "NtpdIp";

typedef struct tagTALLConfigData
{
	TLocalUmsInfo       m_tLocalCnsInfo;
	TTPSipRegistrarCfg  m_tTPSipRegistrarCfg;
	TTPGKCfg			m_tGKRegCfg;
	TUmsStackCallCfg	m_tSipStackCallCfg;

	TTPBrdInfo          m_atBrdCfg[TP_BOARD_MAX_NUM];//板子配置信息数组
	u8					m_byBrdValidNum;             //有效单板的数量
	THduCfgInfo         m_atHduCfg[HDU_MAX_NUM];     //电视墙配置信息数组
	THduStyleCfgInfo	m_tHduStyleCfg;				 //电视墙风格配置信息

    TTPQTEncryptInfo    m_tTPQTEncryptInfo;          //QTMT IP  QTID配置信息
	TPwdCycleInfo       m_tPwdCycleInfo;
	TNtpdInfo			m_tNtpdInfo;

}TALLConfigData,*PTALLConfigData;

extern TALLConfigData g_tALLConfigData;
/*====================================================================
    函数名      ：SetFileReadOnly
    功能        ：将指定文件设置成只读
    算法实现    ：（可选项）
    引用全局变量：
    输入参数说明：char* pchFileName:文件名
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/08/10    1.0         jianghy         创建
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
    函数名      ：SetFileReadWrite
    功能        ：将指定文件设置成可写
    算法实现    ：（可选项）
    引用全局变量：
    输入参数说明：
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/08/10    1.0         jianghy         创建
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
