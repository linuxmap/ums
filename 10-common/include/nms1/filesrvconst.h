/*=======================================================================
ģ����      : �ļ�����������
�ļ���      : filesrvconst.h
����ļ�    : ��
�ļ�ʵ�ֹ���: ��������������(���ó������Լ����ݿⳣ��)
����        : ���
�汾        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2006/12/28  1.0     ���    ����
=======================================================================*/

#ifndef _FILESRVCONST_H
#define _FILESRVCONST_H

#ifdef WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif//WIN32

#include "kdvtype.h"
#include "kdvdef.h"

//������ʹ�ù������а汾��
enum EMFileSrvUsedVersion
{
    enumFileSrvUsedVersion1     = (u32)1,
    enumFileSrvUsedVersion2     = (u32)2
};

//��������ǰ�汾�ţ�IFileSrvMsg�õ������Է��빫��ͷ�ļ�
#define FILESRV_CUR_VERSION                         (u32)enumFileSrvUsedVersion1


/*------------------------------------------------------------------------------
  ���ó�������
------------------------------------------------------------------------------*/

//��Ӧ��ID
#define AID_SUS_MTSSN           (AID_SUS_BGN)//�ն˽���
#define AID_SUS_CLIENTSSN       (AID_SUS_BGN + 1)//�ͻ��˽���
//sus�ڲ�Ӧ�ú�
#define AID_SUS_MAINCTL         (AID_SUS_BGN + 2)//����
#define AID_SUS_GUARD           (AID_SUS_BGN + 3)//����
#define AID_SUS_FILEOPR         (AID_SUS_BGN + 4)//�ļ�����


//Server��Ϣͷ��󳤶�
#define MAX_FILESRV_MSG_HEAD_LEN        (s32)(40)
//Server��Ϣ����󳤶�
#define MAX_FILESRV_MSG_LEN             (s32)(28 * 1024 - MAX_FILESRV_MSG_HEAD_LEN)

//�豸���к��ַ�����󳤶�
#define MAX_FILESRV_SERIALNO_LEN        (s32)(128)

//�ļ�������󳤶�
#define MAX_FILESRV_BUG_REPORT_LEN      (s32)(512)


//һ���豸��Ҫ�ϴ����ļ�������
#define MAX_FILESRV_DEVFILE_NUM         (s32)(4)

//�ļ�����󳤶�
#define MAX_FILESRV_FILENAME_LEN        (s32)(64)

//Ӳ���汾����󳤶�
#define MAX_FILESRV_HARDVER_LEN         (s32)(32)

//����汾��������󳤶�
#define MAX_FILESRV_SOFTVER_LEN         (s32)(64)

//IFCSrvDev�ַ�����󳤶�
#define MAX_FILESRV_DEVSTRING_LEN       (s32)(32)
//IFCSrvDev�豸������ʼλ��
#define FILESRV_DEVSTRING_TYPE_BEGIN    (s32)(0)
//IFCSrvDev�豸�����ַ�������
#define FILESRV_DEVSTRING_TYPE_LEN      (s32)(8)
//IFCSrvDev�豸�ͺ���ʼλ��
#define FILESRV_DEVSTRING_MODEL_BEGIN   (s32)(8)
//IFCSrvDev�豸�ͺ��ַ�������
#define FILESRV_DEVSTRING_MODEL_LEN     (s32)(8)
//IFCSrvDev����ϵͳ������ʼλ��
#define FILESRV_DEVSTRING_OS_BEGIN      (s32)(16)
//IFCSrvDev����ϵͳ�����ַ�������
#define FILESRV_DEVSTRING_OS_LEN        (s32)(8)

//�ļ�����
enum EMFileSrvFileType
{
    enumFileSrvFileTypeUnknown      = (u32)0,//δ֪
    enumFileSrvFileTypeService      = (u32)1,//ҵ���ļ�
    enumFileSrvFileTypeConsole      = (u32)2//����̨�ļ�
};

//�豸����
enum EMFileSrvDevType
{
    enumFileSrvDevTypeUnknown     = (u8)0,
//    enumFileSrvDevTypeMCU         = (u8)1,//MCU
    enumFileSrvDevTypeMT          = (u8)2,//MT
    enumFileSrvDevTypeFileSrv     = (u8)3,//�¼��ļ�������
    enumFileSrvDevTypeClient      = (u8)4//�ͻ���
};


//�豸�ͺ�(MCU)
//enum EMFileSrvDevMCUModel
//{
//    enumFileSrvDevModelMCU8000A    = (u8)1,//8000
//    enumFileSrvDevModelMCU8000B    = (u8)2,//8000B
//    enumFileSrvDevModelMCUWin32		 = (u8)3//Windows
//};

//�豸�ͺ�(MT)
enum EMFileSrvDevMTModel
{
    enumFileSrvDevModelMTUnknown    = (u8)0,
//    enumFileSrvDevModelMTPCMT      = (u8)1,
//    enumFileSrvDevModelMT8010      = (u8)2,
//    enumFileSrvDevModelMT8010A     = (u8)3,//8010A
//    enumFileSrvDevModelMT8010Plus  = (u8)4,
//    enumFileSrvDevModelMT8010C     = (u8)5,//8010C
//    enumFileSrvDevModelMTIMT       = (u8)6,
    enumFileSrvDevModelMTTS6610     = (u8)7,//T2 8220A
    enumFileSrvDevModelMTTS5210     = (u8)8,//T2 8220B
    enumFileSrvDevModelMTV5         = (u8)9,//T2 8220C
    enumFileSrvDevModelMTTS3210     = (u8)10,//T2 8620A
    enumFileSrvDevModelMTTS6610E    = (u8)11,
    enumFileSrvDevModelMTTS6210     = (u8)12,

    enumFileSrvDevModelMTTS5610     = (u8)13,//T2 ts5610
    enumFileSrvDevModelMTTS3610     = (u8)14,//T2 ts3610
	enumFileSrvDevModelMTTS6210E    = (u8)15,//T2 ts6210E

	enumFileSrvDevModelMTKDV7910    = (u8)16,//KDV 7910
	enumFileSrvDevModelMTKDV7810    = (u8)17,//KDV 7810
};

//����ϵͳ����
enum EMFileSrvOSType
{
    enumFileSrvOSTypeUnknown        = (u8)0,
    enumFileSrvOSTypeVxworksRaw     = (u8)1,//Vxworks �����
    enumFileSrvOsTypeVxworksTffs    = (u8)2,//Vxworks ������
    enumFileSrvOsTypeWindows        = (u8)3,//Windows
    enumFileSrvOsTypeLinuxPowerPC   = (u8)4,//PowerPC Linux
    enumFileSrvOsTypeLinuxDavinci   = (u8)5,//Davinci Arm Linux
};

//��������
enum EMFileSrvLanType
{
    enumFileSrvLanEnglish       = (u8)0,//Ӣ��
    enumFileSrvLanChinese       = (u8)1//����(����)
};

//��־����������
enum EMFileSrvLogReqMainType
{
    enumFileSrvLogReqMainTypeAll        = (u8)0x00,//������־
    enumFileSrvLogReqMainTypeCategory   = (u8)0x01,//��־����(�û�/ϵͳ)
    enumFileSrvLogReqMainTypeLevel      = (u8)0x02,//��־�ȼ�(����/��Ҫ/һ��)
    enumFileSrvLogReqMainTypeTime       = (u8)0x04,//ʱ��
    enumFileSrvLogReqMainTypeDev        = (u8)0x08,//�豸��ʶ
    enumFileSrvLogReqMainTypeResult     = (u8)0x10,//�������(�ɹ�/ʧ��)
    enumFileSrvLogReqMainTypeEvent      = (u8)0x20//�¼�����
};
//��־����������
enum EMFileSrvLogReqSubTypeCategory//��־����
{
//    enumFileSrvLogReqSubTypeCategoryAll     = (u16)0x0000,//����
    enumFileSrvLogReqSubTypeCategoryUser    = (u16)0x0001,//�û�
    enumFileSrvLogReqSubTypeCategorySystem  = (u16)0x0002//ϵͳ
};
enum EMFileSrvLogReqSubTypeLevel//��־�ȼ�
{
//    enumFileSrvLogReqSubTypeLevelAll        = (u16)0x0000,//����
    enumFileSrvLogReqSubTypeLevelWarning    = (u16)0x0001,//����
    enumFileSrvLogReqSubTypeLevelSeverity   = (u16)0x0002,//��Ҫ
    enumFileSrvLogReqSubTypeLevelCommon     = (u16)0x0004//һ��
};
enum EMFileSrvLogReqSubTypeTime//ʱ��
{
//    enumFileSrvLogReqSubTypeTimeAll         = (u16)0x0000,//����ʱ��
    enumFileSrvLogReqSubTypeTimeStart       = (u16)0x0001,//ָ����ʼʱ��
    enumFileSrvLogReqSubTypeTimeEnd         = (u16)0x0002//ָ������ʱ��
};
enum EMFileSrvLogReqSubTypeDev//�豸��ʶ
{
//    enumFileSrvLogReqSubTypeDevAll          = (u16)0x0000,//�����豸
    enumFileSrvLogReqSubTypeDevType         = (u16)0x0001,//ָ������
    enumFileSrvLogReqSubTypeDevModel        = (u16)0x0002,//ָ���ͺ�
    enumFileSrvLogReqSubTypeDevOsType       = (u16)0x0004,//ָ������ϵͳ
    enumFileSrvLogReqSubTypeDevHardVer      = (u16)0x0008//ָ��Ӳ���汾
//    enumFileSrvLogReqSubTypeDevSoftVer      = (u16)0x0010//ָ��(�������)����汾
};
enum EMFileSrvLogReqSubTypeResult//�������
{
//    enumFileSrvLogReqSubTypeResultAll       = (u16)0x0000,//����
    enumFileSrvLogReqSubTypeResultOK        = (u16)0x0001,//�ɹ�
    enumFileSrvLogReqSubTypeResultFail      = (u16)0x0002,//ʧ��
};
enum EMFileSrvLogReqSubTypeEvent//�¼�
{
//    enumFileSrvLogReqSubTypeEventAll        = (u16)0x0000,//����
    enumFileSrvLogReqSubTypeEventDevOpr     = (u16)0x0001,//�豸����
    enumFileSrvLogReqSubTypeEventClientOpr  = (u16)0x0002//�ͻ��˲���
};
enum EMFileSrvLogReqEventSubTypeDevOpr//�豸����
{
    enumFileSrvLogReqEventSubTypeDevOprAll             = (u16)0x0000,//����
    enumFileSrvLogReqEventSubTypeDevOprLogin           = (u16)0x0001,//��¼
    enumFileSrvLogReqEventSubTypeDevOprGetFile         = (u16)0x0002,//��ȡ�ļ�
    enumFileSrvLogReqEventSubTypeDevOprLogout          = (u16)0x0004//�˳�
};
enum EMFileSrvLogReqEventSubTypeClientOpr//�ͻ��˲���
{
    enumFileSrvLogReqEventSubTypeClientOprAll           = (u16)0x0000,//����
    enumFileSrvLogReqEventSubTypeClientOprLogin         = (u16)0x0001,//��¼
    enumFileSrvLogReqEventSubTypeClientOprAddUser       = (u16)0x0002,//����û�
    enumFileSrvLogReqEventSubTypeClientOprEditUser      = (u16)0x0004,//�޸��û�
    enumFileSrvLogReqEventSubTypeClientOprDelUser       = (u16)0x0008,//ɾ���û�
    enumFileSrvLogReqEventSubTypeClientOprGetLog        = (u16)0x0010,//��ѯ��־
    enumFileSrvLogReqEventSubTypeClientOprDelLog        = (u16)0x0020,//ɾ����־
    enumFileSrvLogReqEventSubTypeClientOprUpdateFile    = (u16)0x0040,//�ϴ��ļ�
    enumFileSrvLogReqEventSubTypeClientOprLogout        = (u16)0x0080,//�˳�
};
//fxh����ϴ��汾��
#define MAX_VERSIONNUM                      (s32)(5)
#define MTTYPENUM                           (s32)(10)

//����û�����
#define MAX_FILESRV_USER_NUM                (s32)(16)

//�ͻ����û�����󳤶�
#define MAX_FILESRV_USERNAME_LEN            (s32)(32)
//�ͻ���������󳤶�
#define MAX_FILESRV_PASSWORD_LEN            (s32)(32)


//FTP����
#define MAX_SUS_FTP_USERNAME_LEN    (s32)32//FTP�û�������
#define MAX_SUS_FTP_PASSWORD_LEN    (s32)32//FTP���볤��
#define MAX_SUS_FTP_PATH_LEN        (s32)128//FTP·������
#define SUS_FTP_DEFAULT_PORT        (u16)21//FTPĬ�϶˿�

//�����ļ�·��
#define MAX_SUS_LOCAL_FILE_PATH     (s32)128


//Ĭ������
#define PORT_SUS_LISTEN             (u16)60000  //�����������˿�
#define PORT_SUS_TELNET             (u16)2800   //������Telnet�˿�
#define SUS_DB_NAME                 (LPCSTR)"sus"//���ݿ���
#define SUS_DB_PORT                 (u16)5000   //���ݿ�˿�
#define SUS_WDSRV_PORT              (u16)10000  //���Ź�����˶˿�
#define SUS_WDSRV_CHECKCOUNT        (u8)10      //���Ź�����˲��Դ���
#define SUS_WDSRV_CHECKTIME         (u16)10     //���Ź�����˲��Լ��(s)
#define SUS_WDAGT_CHECKCOUNT        (u32)10     //���Ź��ͻ��˲��Դ���
#define SUS_WDAGT_REGTIME           (u32)10     //���Ź��ͻ��˲��Լ��(s)
#define SUS_DB_SUS_CONNNUM          (u32)1      //�ڲ����ݿ������̸߳���
#define SUS_DB_SUC_CONNNUM          (u32)1      //�ͻ������ݿ������̸߳���
#define SUS_DB_MT_CONNNUM           (u32)16     //�ն����ݿ������̸߳���




/*------------------------------------------------------------------------------
  ������
------------------------------------------------------------------------------*/

#define SUS_ERRORCODE_BGN                   (u32)(20000)

#define SUS_ERRORCODE_SUCCESS               (u32)(0)
#define SUS_ERRORCODE_MAXDBCONNECTION       (SUS_ERRORCODE_BGN + 1)

//�ն˴���
#define SUS_ERRORCODE_MTALREADY_CONNECT     (SUS_ERRORCODE_BGN + 1000)
#define SUS_ERRORCODE_MT_ALREADY_NEWEST     (SUS_ERRORCODE_BGN + 1001)
#define SUS_ERRORCODE_NO_OTHER_VERSION      (SUS_ERRORCODE_BGN + 1002)


//�������ڲ�����
#define SUS_ERRORCODE_MAX_SERVICE_SESSION   (SUS_ERRORCODE_BGN + 2000)
#define SUS_ERRORCODE_TIMEOUT               (SUS_ERRORCODE_BGN + 2001)
#define SUS_ERRORCODE_SUS_NOT_PREPARED      (SUS_ERRORCODE_BGN + 2002)
#define SUS_ERRORCODE_SUS_DBLOADDATA_FAIL   (SUS_ERRORCODE_BGN + 2003)
//#define SUS_ERRORCODE_SUS_FILE_NOT_PREPARED (SUS_ERRORCODE_BGN + 2004)
#define SUS_ERRORCODE_NO_SUCH_FILE          (SUS_ERRORCODE_BGN + 2005)
#define SUS_ERRORCODE_NO_SUCH_DEV           (SUS_ERRORCODE_BGN + 2006)
#define SUS_ERRORCODE_SERVER_VERUPDATE      (SUS_ERRORCODE_BGN + 2007)
#define SUS_ERRORCODE_NO_MEMORY             (SUS_ERRORCODE_BGN + 2008)
#define SUS_ERRORCODE_EXEC_DB_SQL_FAIL      (SUS_ERRORCODE_BGN + 2009)

//�ͻ��˴���
#define SUS_ERRORCODE_LOGIN_INVALID_PWD     (SUS_ERRORCODE_BGN + 3000)
#define SUS_ERRORCODE_LOGIN_NO_USERNAME     (SUS_ERRORCODE_BGN + 3001)
#define SUS_ERRORCODE_NO_RIGHT              (SUS_ERRORCODE_BGN + 3002)
#define SUS_ERRORCODE_ADDUSER_EXIST         (SUS_ERRORCODE_BGN + 3003)
#define SUS_ERRORCODE_BUSY_LAST_REQ         (SUS_ERRORCODE_BGN + 3004)
#define SUS_ERRORCODE_EDITUSER_NO_EXIST     (SUS_ERRORCODE_BGN + 3005)
#define SUS_ERRORCODE_DELUSER_NO_EXIST      (SUS_ERRORCODE_BGN + 3006)
#define SUS_ERRORCODE_EDITUSER_UP_RIGHT     (SUS_ERRORCODE_BGN + 3007)
#define SUS_ERRORCODE_EDITUSER_DW_ADMIN_RT  (SUS_ERRORCODE_BGN + 3008)
#define SUS_ERRORCODE_EDITUSER_USER_LOGIN   (SUS_ERRORCODE_BGN + 3009)
#define SUS_ERRORCODE_EDITUSER_NO_CHG_NAME  (SUS_ERRORCODE_BGN + 3010)
#define SUS_ERRORCODE_DELUSER_NO_DEL_ADMIN  (SUS_ERRORCODE_BGN + 3011)
#define SUS_ERRORCODE_DELUSER_USER_LOGIN    (SUS_ERRORCODE_BGN + 3012)
#define SUS_ERRORCODE_EDITVER_NO_DEV        (SUS_ERRORCODE_BGN + 3013)
#define SUS_ERRORCODE_SETREC_NO_NEW_FILE    (SUS_ERRORCODE_BGN + 3014)
#define SUS_ERRORCODE_SETREC_SAME_FILE      (SUS_ERRORCODE_BGN + 3015)
#define SUS_ERRORCODE_DELVER_NO_RECOMMEND   (SUS_ERRORCODE_BGN + 3016)
#define SUS_ERRORCODE_DELVER_NO_FILE        (SUS_ERRORCODE_BGN + 3017)
#define SUS_ERRORCODE_UPDATEFILE_IN_DOING   (SUS_ERRORCODE_BGN + 3018)
#define SUS_ERRORCODE_UPDATEFILE_VER_EXIST  (SUS_ERRORCODE_BGN + 3019)
#define SUS_ERRORCODE_DEV_HARDVER_CONFLICT  (SUS_ERRORCODE_BGN + 3020)
#define SUS_ERRORCODE_UPDATE_LAST_UNFINNISH (SUS_ERRORCODE_BGN + 3021)
#define SUS_ERRORCODE_UPDATE_FILE_NOTEXIST  (SUS_ERRORCODE_BGN + 3022)
#define SUS_ERRORCODE_UPDATE_FILEWRITE_FAIL (SUS_ERRORCODE_BGN + 3023)
#define SUS_ERRORCODE_UPDATE_FILE_TOTALPK   (SUS_ERRORCODE_BGN + 3024)
#define SUS_ERRORCODE_UPDATE_FILE_CURPK     (SUS_ERRORCODE_BGN + 3025)
#define SUS_ERRORCODE_UPDATE_FILE_PKSIZE    (SUS_ERRORCODE_BGN + 3026)
#define SUS_ERRORCODE_UPDATE_FILE_TYPE      (SUS_ERRORCODE_BGN + 3027)
#define SUS_ERRORCODE_UPDATE_FILE_SIZE      (SUS_ERRORCODE_BGN + 3028)
#define SUS_ERRORCODE_UPDATE_FILE_CURPK_SN  (SUS_ERRORCODE_BGN + 3029)
#define SUS_ERRORCODE_UPDATE_FILENAME       (SUS_ERRORCODE_BGN + 3030)
#define SUS_ERRORCODE_UPDATE_FILETYPE       (SUS_ERRORCODE_BGN + 3031)
#define SUS_ERRORCODE_UPDATE_PACK_SIZE      (SUS_ERRORCODE_BGN + 3032)
#define SUS_ERRORCODE_RESET_MAINTENANCE     (SUS_ERRORCODE_BGN + 3033)
#define SUS_ERRORCODE_RESET_MTLOGIN         (SUS_ERRORCODE_BGN + 3034)
//fxh
#define SUS_ERRORCODE_DEV_VERTOOMUCH        (SUS_ERRORCODE_BGN + 3035)
/*------------------------------------------------------------------------------
  ������ר�г���
------------------------------------------------------------------------------*/
//�ļ�������󳤶�(�����ļ�����5K�а�)
#define MAX_FILESRV_DEV_FILE_LEN            (s32)(5 * 1024)



/*------------------------------------------------------------------------------
  �ͻ���ר�г���
------------------------------------------------------------------------------*/
//�ͻ�������֪ͨ
enum EMFileSrvCfgNotifType
{
    enumFileSrvCfgNotifTypeReq  = (u8)1,//�ͻ�����������
    enumFileSrvCfgNotifTypeAdd  = (u8)2,//��������
    enumFileSrvCfgNotifTypeEdit = (u8)3//�޸�����
};

//���ݿⳣ��
#define MAX_DB_NAME_LEN                 (s32)64//���ݿ���
#define MAX_DB_USERNAME_LEN             (s32)64//���ݿ��û���
#define MAX_DB_USER_PWD_LEN             (s32)32//���ݿ�����

//���ݿ�����
enum EMDBEngineType
{
    enumDBEngineTypeSybase      = (u8)0,
    enumDBEngineTypeMySql       = (u8)1,
    enumDBEngineTypeOracle      = (u8)2
};

//�ļ�������󳤶�(�����ļ�����20K�а�)
#define MAX_FILESRV_CLIENT_FILE_LEN             (s32)(20 * 1024)

#endif//_FILESRVCONST_H
