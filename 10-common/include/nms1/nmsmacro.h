#ifndef NMS_PUBLIC_MACRO_H_
#define NMS_PUBLIC_MACRO_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kdvdef.h"
#include "errorid.h"
#include "mcudrvlib.h"
#include "mtsnmp.h"
#include "vccommon.h"
#include "snmpadp.h"
#include "calladdr.h"

//���ݿ���
#define DB_NAME_MAX_LEN     (s32)16
//�û�������ĳ���
#define USER_LEN            (s32)17
#define PWD_LEN             USER_LEN
//ָʾ��״̬����
#define LED_STATUS_LEN		(s32)24

#define NMS_APP_NAME            _T("NmsServer 0xbe8e2ce1")
#define NMS_WATCHDOG_APPID      (u16)1
#define NMS_WATCHDOG_APP_NAME   _T("NmsWatchDog 0xbe8e2ce1")
#define NMS_WATCHDOG_PORT       (u16)7777

//���Ź���NMS��ͨ��Ϣ
#define NMS_WATCHDOG_MSG_START      (u16)1000   //  ��������
#define NMS_WATCHDOG_MSG_QUIT       (u16)1100   //  ���ܹر�

#define LANGUAGE_FILE_NAME      _T("nms.lan")

//������
#define ERROR_CMD_SUCCESS               0	// ���׳ɹ�
#define ERROR_DEFAULT                   ERR_SVR_BGN + 1     //ȱʡ����
#define ERROR_SVR_RESTARTING            ERR_SVR_BGN + 2     //����������������
#define ERROR_DB_UNKNOWD                ERR_SVR_BGN + 3     //���ݿ����
#define ERROR_CMD_IN_RUNNING            ERR_SVR_BGN + 4     //�������ڽ�����

#define	ERROR_NEED_MORE_PARAM           ERR_SVR_BGN + 5     //������ȫ

#define ERROR_CMD_TIMEOUT               ERR_SVR_BGN + 10    //SessionManager��ʱ
#define ERROR_CMD_TYPE_MISMATCHED       ERR_SVR_BGN + 11    //�������Ͳ�ƥ��

#define	ERROR_NO_FREEINSTANCE           ERR_SVR_BGN + 20    //CM/FMӦ��û�п��õ�ʵ��
#define	ERROR_CLIENT_MISMATCHED         ERR_SVR_BGN + 21    //�ͻ��˲�ƥ��

#define	ERROR_FM_GETALARMSTAMP_FAIL     ERR_SVR_BGN + 30    //��ȡ�澯��Ϣʧ��
#define	ERROR_FM_GETALARMSTAMP_TIMEOUT  ERR_SVR_BGN + 31    //��ȡ�澯��Ϣ��ʱ

#define	ERROR_FM_GETALARM_FAIL          ERR_SVR_BGN + 32    //��ȡ�澯ʧ��
#define	ERROR_FM_GETALARM_TIMEOUT       ERR_SVR_BGN + 33    //��ȡ�澯��ʱ

#define ERROR_CM_RESTART_UPDATING       ERR_SVR_BGN + 34    //�豸�ļ������У�����������

#define ERROR_SNMP_SEND_FAIL            ERR_SVR_BGN + 40    //����SNMP����ʧ��
#define ERROR_SNMP_RCV_FAIL             ERR_SVR_BGN + 41    //����SNMP����ʧ��

#define ERROR_FTP_RUNNING               ERR_SVR_BGN + 60    //Ftp��������ִ��
#define ERROR_FTP_DELETEFILE_FAIL       ERR_SVR_BGN + 61    //FTPɾ���ļ�ʧ��
#define ERROR_FTP_PUTFILE_FAIL          ERR_SVR_BGN + 62    //FTP�����ļ�ʧ��
#define ERROR_FTP_GETFILE_FAIL          ERR_SVR_BGN + 63    //FTP��ȡ�ļ�ʧ��

#define ERROR_EQUIPMENT_MISMATCHED      ERR_SVR_BGN + 70    //�豸���Ͳ�ƥ��

#define ERROR_LOGIN                     ERR_SVR_BGN + 80    //��¼ʧ��
#define ERROR_LOGIN_NO_USER             ERR_SVR_BGN + 81    //û������û�
#define ERROR_LOGIN_ERR_PWD             ERR_SVR_BGN + 82    //�û��������
#define ERROR_LOGIN_NO_ROLE             ERR_SVR_BGN + 83    //�û��������ڽ�ɫ
#define ERROR_CHANGE_PWD                ERR_SVR_BGN + 84    //�޸�����ʧ��
#define ERROR_PWD_MISMATCHED            ERR_SVR_BGN + 85    //���벻����
#define ERROR_USER_HAS_LOGON            ERR_SVR_BGN + 86    //�û��Ѿ���¼				

//����
#define ERROR_SET_BOARD_STATUS_FAILED       ERR_SVR_BGN + 100   //���õ���״̬ʧ��
#define ERROR_SYNC_BOARD_TIME_FAILED        ERR_SVR_BGN + 101   //ͬ������ʱ��ʧ��
#define ERROR_BOARD_BITERROR_TEST_FAILED    ERR_SVR_BGN + 102   //�������ʧ��
#define ERROR_BOARD_SELF_TEST_FAILED        ERR_SVR_BGN + 103   //�Բ�ʧ��
#define ERROR_BOARD_E1LINK_CFG_FAILED       ERR_SVR_BGN + 104   //E1��·����ʧ��



#define	DEVICE_LINK_DOWN            999
#define DEVICE_POWEROFF             998
#define DEVICE_RESTART              1000


//��������
#define OBJECT_TYPE_UNKNOWN     0   // δ֪���豸
#define OBJECT_TYPE_MCU         0x1 // MCU�豸
#define OBJECT_TYPE_MT          0x2 // �ն��豸
#define OBJECT_TYPE_PERI        0x3 // ����
#define OBJECT_TYPE_SECURITY    0x4 // ��ȫ

//Mcu ����
#define MCU_CATALOG_UNKNOWN     0x0 //δ֪Mcu
#define MCU_CATALOG_8000        0x1 //Mcu8000
#define MCU_CATALOG_8000B       0x2 //Mcu8000B
#define MCU_CATALOG_8000C       0x3 //MCU 8000C

// �ն˷���
#define MT_CATALOG_UNKNOWN				MTSYSHARDWARETYPE_UNKNOWNMTMODEL	// δ֪�ն�
#define MT_CATALOG_PC					MTSYSHARDWARETYPE_PCMT				// �����ն�
#define MT_CATALOG_EMBED_MT8010			MTSYSHARDWARETYPE_8010				// MT8010�ն�
#define MT_CATALOG_EMBED_MT8010C		MTSYSHARDWARETYPE_8010C				// MT8010C�ն�
#define MT_CATALOG_EMBED_MT8010C1		MTSYSHARDWARETYPE_8010C1			// MT8010C�ն�
#define MT_CATALOG_EMBED_IMT			MTSYSHARDWARETYPE_IMT				// Ƕ���ն�IMT
#define MT_CATALOG_EMBED_MT8010A		MTSYSHARDWARETYPE_8010A				// MT8010A�ն�
#define MT_CATALOG_EMBED_MT8010APLUS    MTSYSHARDWARETYPE_8010APLUS			// MT8010A+�ն�
#define MT_CATALOG_EMBED_MT6610			MTSYSHARDWARETYPE_6610				// TS6610
#define MT_CATALOG_EMBED_MT6610E		MTSYSHARDWARETYPE_6610E				// TS6610E
#define MT_CATALOG_EMBED_MT6210			MTSYSHARDWARETYPE_6210				// TS6210
#define MT_CATALOG_EMBED_MT5210			MTSYSHARDWARETYPE_5210				// TS5210
#define MT_CATALOG_EMBED_MT3210			MTSYSHARDWARETYPE_3210				// TS3210
#define MT_CATALOG_EMBED_MTV5			MTSYSHARDWARETYPE_V5				// TS V5
#define MT_CATALOG_EMBED_MT8010A_2		MTSYSHARDWARETYPE_8010A_2			// 8010A ���2M
#define MT_CATALOG_EMBED_MT8010A_4		MTSYSHARDWARETYPE_8010A_4			// 8010A ���4M
#define MT_CATALOG_EMBED_MT8010A_8		MTSYSHARDWARETYPE_8010A_8			// 8010A ���8M
#define MT_CATALOG_EMBED_MT7210			MTSYSHARDWARETYPE_7210				// TS7210
#define MT_CATALOG_EMBED_MT7610			MTSYSHARDWARETYPE_7610				// TS7610
#define MT_CATALOG_EMBED_MT7620_B		MTSYSHARDWARETYPE_7620_2			// TS7620_B
#define MT_CATALOG_EMBED_MT7620_A		MTSYSHARDWARETYPE_7620_4			// TS7620_A
#define MT_CATALOG_EMBED_MT5610         MTSYSHARDWARETYPE_5610              // MT5610�ն�
#define MT_CATALOG_EMBED_MT7810			MTSYSHARDWARETYPE_7810				// TS7810
#define MT_CATALOG_EMBED_MT7910			MTSYSHARDWARETYPE_7910				// TS7910
#define MT_CATALOG_EMBED_MT7820_A		MTSYSHARDWARETYPE_7820_A			// ����MT7820A
#define MT_CATALOG_EMBED_MT7820_B		MTSYSHARDWARETYPE_7820_B			// ����MT7820B
#define MT_CATALOG_EMBED_MT7920_A		MTSYSHARDWARETYPE_7920_A			// ����MT7920A
#define MT_CATALOG_EMBED_MT7920_B		MTSYSHARDWARETYPE_7920_B			// ����MT7920B


//��ȫ����
#define SECURITY_CATALOG_UNKNOWN    0x0 //δ֪
#define SECURITY_CATALOG_USER       0x1 //User
#define SECURITY_CATALOG_GROUP      0x2 //Group

//ǰ��̨��·״��
#define	LINK_DOWN       0
#define LINK_ACTIVE     1
#define LINK_UNKNOWN    255

//�������ܷ������Ĺ㲥��ַ�Ͷ˿�
#define MULTICAST_IP                (LPCSTR)_T("228.1.1.224")
#define SVR_FIND_MULTICAST_PORT     (u16)7883
#define CLT_FIND_MULTICAST_PORT     (u16)7884

// ���ܷ�������ͨѶ����
typedef struct tagTNmsEnvDataStruct
{
    tagTNmsEnvDataStruct()
    {
        ZeroMemory(this, sizeof (tagTNmsEnvDataStruct));
    }
    u32 m_dwNmsIp;  // ���ܷ�������ַ
    u16 m_wNmsPort; // ���ܷ������ڵ�˿�
} TNmsEnvDataStruct, *PTNmsEnvDataStruct;

//ʱ���ַ����ĳ���
const u8 TIME_LEN               = 20;

//IP��ַ�ַ����ĳ���
const u8 IPADDR_LEN             = 16;

//�豸�汾����
const u8 DEVICE_VER_LEN         = 20;

//DB���ӳ�ʱ���룩
const u8 MAX_DBCONNECT_TIME     = 30;

//����汾����
const u8 MAX_SOFTWARE_VER_LEN   = 255;

//�Ƶ�״̬�̶�
const u8 MAX_LED_STATUS_LEN	    = 64;

//����������
const u8 MAX_CONFNAME_LEN	    = 32;
const u8 MAX_CONFID_LEN         = MAX_CONFNAME_LEN;

const u8 PERI_STATE_LEN         = 4;    //MCU�����豸״̬����
const u8 SYNCTIME_STATE_LEN     = 3;    //MCU����ʱ��ͬ��״̬����
const u8 TEST_LEN               = 4;    //MCU�����ⳤ��(����/�Լ�)
const u8 E1_LEN                 = 12;   //E1��·���ó���

//д��־������
#define CRITICAL        1
#define IMPORTANT       2
#define APPLICATION     196
#define USERDEBUG       255


//Session ģ��App ID����
#define CSESSIONMANAGER_APPID       AID_SVR_BGN
#define CCMAPP_APPID                (AID_SVR_BGN + 1)		
#define CFMAPP_APPID                (AID_SVR_BGN + 2)

#define AID_INT_TEST_NMS            (AID_SVR_BGN + 3)

//�ļ�������ʱ��ѯ���
#define NMS_UPDATE_QUERY_TIME       (long)20 * 1000

//�ļ�������������ڴ��С
#define NMS_UPDATE_MEMORY           (int)4 * 1024

//�ļ�������ʱ��ѯ��¼
typedef struct tagUpdateFile
{
    tagUpdateFile() : m_dwClientIID(MAKEIID(INVALID_APP, INVALID_INS)),
                      m_dwClientNode(INVALID_NODE), m_dwDeviceIP(0),
                      m_dwBoardIP(0), m_dwDeviceID(0), m_nFileNum(0),
                      m_wGetSetPort(161), m_wDeviceType(0), m_byIsBoard(0),
                      m_byLayer(0), m_bySlot(0), m_byType(0)
    {
        memset( m_aszFileName, 0, sizeof (m_aszFileName) );
    }

    u32                     m_dwClientIID;  //�ͻ���IID
    u32                     m_dwClientNode; //�ͻ���NODE
    u32                     m_dwDeviceIP;   //�豸IP, ������
    u32                     m_dwBoardIP;    //����IP, ������
    u32                     m_dwDeviceID;   //�豸ID
    s32                     m_nFileNum;     //�ļ�����
    u16                     m_wGetSetPort;  //�豸�˿�, ������
    u16                     m_wDeviceType;  //�豸����
    u8                      m_byIsBoard;    //�Ƿ񵥰�
    u8                      m_byLayer;      //������
    u8                      m_bySlot;       //����ۺ�
    u8                      m_byType;       //��������
    s8                      m_aszFileName[8][64];   //�ļ���
} TUpdateFile;

// �����û���¼���ݣ�ͬʱ���������޸��û�����
typedef struct tagTNmsLogonReq
{
    tagTNmsLogonReq()
    {
        ZeroMemory(this, sizeof (tagTNmsLogonReq));
    }
	TCHAR   m_szUsrName[USER_LEN];  // �û���¼����
	TCHAR   m_szUsrPwd[PWD_LEN];    // �û���ǰ����
	TCHAR   m_szPwdNew[PWD_LEN];    // �û��¿���޸Ŀ���ʱ��Ч��

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/03/30  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "User = %d, Pwd = %s, ConfirmPwd = %s\n",
                     m_szUsrName, m_szUsrPwd, m_szPwdNew );
    }
} TNmsLogonReq, *PTNmsLogonReq;

// �����û���¼�������
typedef struct tagTNmsLogonRet
{
    tagTNmsLogonRet()
    {
        ZeroMemory(this, sizeof (tagTNmsLogonRet));
    }
    u32     m_dwResult;             // ��¼���
    TCHAR   m_szDbUser[USER_LEN];   // ���ݿ��û���
    TCHAR   m_szDbPwd[PWD_LEN];     // ���ݿ��û�����
    TCHAR   m_szDbAddr[IPADDR_LEN]; // ���ݿ��ַ
    TCHAR   m_szDbName[DB_NAME_MAX_LEN];    // ���ݿ�����
    TCHAR   m_szFtpUser[USER_LEN];  // Ftp�û� 
    TCHAR   m_szFtpPwd[PWD_LEN];    // Ftp����

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/03/30  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "RetCode = %d, DbUser = %s, DbPwd = %s, \
DbIp = %s, DbName = %s, FtpUser = %s, FtpPwd = %s\n", m_dwResult, m_szDbUser,
                     m_szDbPwd, m_szDbAddr, m_szDbName, m_szFtpUser, m_szFtpPwd );
    }
} TNmsLogonRet, *PTNmsLogonRet;


//Ftp�ļ��������Ϣ�ṹ
typedef struct tagTCmdCmFtpFile
{
    tagTCmdCmFtpFile()
    {
        ZeroMemory(this, sizeof (tagTCmdCmFtpFile));
    }

    TCHAR   m_szDeviceFileName[MAX_PATH + 1];   //Զ���ļ�ȫ��
    TCHAR   m_szNmcFileName[MAX_PATH + 1];      //�ͻ����ļ�ȫ��
//    u32     m_dwDeviceIP;                       //Զ���豸IP(������)
    u8      m_byMainType;                       //Զ���豸������(MCU/MT)
    u8      m_bySubType;                        //Զ���豸������(������/�ն�����)
    u8      m_byOsType;                         //����ϵͳ����

    //zw[08/12/2008]
    void ChangeName(void)
    {        
        if ( !strcmp("index.htm", m_szNmcFileName) )
        {   
            s8 oldName[256] = "C:\\Inetpub\\ftproot\\index.htm";
            s8 newName[256] = "C:\\Inetpub\\ftproot\\index.htm.unknown";
            remove( newName );
            rename( oldName, newName );

            STRCAT( &m_szNmcFileName[9], ".unknown\0");
            STRCAT( &m_szDeviceFileName[9], ".unknown\0");
        }
        if ( !strcmp("player.htm", m_szNmcFileName) )
        {
            s8 oldName[256] = "C:\\Inetpub\\ftproot\\player.htm";
            s8 newName[256] = "C:\\Inetpub\\ftproot\\player.htm.unknown";
            remove( newName );
            rename( oldName, newName );

            STRCAT( &m_szNmcFileName[10], ".unknown\0");
            STRCAT( &m_szDeviceFileName[10], ".unknown\0");
        }
        if ( !strcmp("mcucfg.ini", m_szNmcFileName) )
        {
            s8 oldName[256] = "C:\\Inetpub\\ftproot\\mcucfg.ini";
            s8 newName[256] = "C:\\Inetpub\\ftproot\\mcucfg.ini.unknown";
            remove( newName );
            rename( oldName, newName );

            STRCAT( &m_szNmcFileName[10], ".unknown\0");
            STRCAT( &m_szDeviceFileName[10], ".unknown\0");
        }
        if ( !strcmp("mtcfg.ini", m_szNmcFileName) )
        {
            s8 oldName[256] = "C:\\Inetpub\\ftproot\\mtcfg.ini";
            s8 newName[256] = "C:\\Inetpub\\ftproot\\mtcfg.ini.unknown";
            rename( oldName, newName );

            STRCAT( &m_szNmcFileName[9], ".unknown\0");
            STRCAT( &m_szDeviceFileName[9], ".unknown\0");
        }
    }

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/03  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "MainType = %d, SubType = %d, \
OsType = %d\nDeviceFile = %s, NmcFile = %s\n",//IP = %s
//                     CCallAddr::GetIpStr( ntohl(m_dwDeviceIP) ),
                     m_byMainType,
                     m_bySubType, m_byOsType,
                     m_szDeviceFileName,
                     m_szNmcFileName );
    }
} ICmdCmFtpFile, *PICmdCmFtpFile;


// �ļ�����������ݽṹ
typedef struct tagTFtpProcSize
{
    tagTFtpProcSize() : m_dwEventId(0), m_dwCurProcSize(0) {}

    u32 m_dwEventId;        // ��������¼�������FTP_BEGIN����ʼ���䣬
                            //      FTP_TRANSFER���ļ����ڴ���
                            //      FTP_END���ļ��������
                            //      FTP_ERROR���ļ��������
    u32 m_dwCurProcSize;    // ��Ӧ�¼������ݣ����¼�ΪFTP_BEGINʱ����ʾ�ļ����ܳ���
                            //      ���¼�ΪFTP_TRANSFERʱ����ʾ��ǰ�Ѿ������˵Ĵ�С
                            //      ���¼�ΪFTP_ENDʱ������ʾ
                            //      ���¼�ΪFTP_ERRORʱ����ʾ������

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/03/30  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "Status = %d, CurSize = %d\n", m_dwEventId,
                     m_dwCurProcSize );
    }
} TFtpProcSize, *PTFtpProcSize;


// ����澯�ĸ澯�������ݽṹ
typedef struct tagTBoard
{
    tagTBoard()
    {
        ZeroMemory(this, sizeof (tagTBoard));
    }
    u32 m_dwIPAddr;                                     //IP��ַ,������
    u32 m_dwSuperID;                                    //�ϼ�ID��ַ
    u8  m_byLayerID;                                    //���,���������ʾ��������
    u8  m_bySlotID;                                     //�ۺ�,���������ʾ����ID
    u8  m_byType;                                       //����
    u8  m_byStatus;                                     //״̬
    u8  m_byOsType;                                     //����ϵͳ����
    TCHAR   m_szSoftwareVersion[MAX_SOFTWARE_VER_LEN];  //����汾
    TCHAR   m_szPanelLed[MAX_LED_STATUS_LEN];           //�忨Led��

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/03  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "IP = %s, MasterID = %d, LayerID = %d, SlotID = %d, \
Type = %d, Status = %d, OsType = %d, SoftwareVer = %s, LED = %s\n",
                     CCallAddr::GetIpStr( ntohl( m_dwIPAddr ) ), m_dwSuperID,
                     m_byLayerID, m_bySlotID, m_byType, m_byStatus, m_byOsType,
                     m_szSoftwareVersion, m_szPanelLed );
    }
} TBoard, *PTBoard;


//DSI��
typedef struct tagTDSIBoard : public TBoard
{
    tagTDSIBoard() : m_byE1LinkCfgCount(0), m_byE1LinkStatus(0)
    {
        m_byType = DSL8000_BRD_DSI;
    }

    u8  m_byE1LinkCfgCount;         //E1��·״̬��������
    u8  m_byE1LinkStatus;           //E1��·״̬

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/03  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "Count = %d, E1Status = %d",
                     m_byE1LinkCfgCount, m_byE1LinkStatus );
        dynamic_cast<const TBoard*>(this)->Print();
    }
} TDSIBoard, *PTDSIBoard;


//Mcu����״̬�澯�������ݽṹ
typedef struct tagTMcuConfState
{
    tagTMcuConfState()
    {
        ZeroMemory( this, sizeof (tagTMcuConfState) );
    }
    u8      m_byMcuConfState;                   //����״̬
    TCHAR   m_szMcuAlias[32];                   //Mcu����
    TCHAR   m_szMcuConfName[MAX_CONFNAME_LEN];  //������
    TCHAR   m_szMcuConfId[MAX_CONFID_LEN];      //����Id
    TCHAR   m_szMcuConfTime[TIME_LEN];          // �澯����ʱ��

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/03  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE,
                     "State = %d, Alias = %s, Name = %s, ConfID = %s, Time = %s\n",
                     m_byMcuConfState, m_szMcuAlias, m_szMcuConfName,
                     m_szMcuConfId, m_szMcuConfTime );
    }
} TMcuConfState, *PTMcuConfState;


//Mt����״̬�澯�������ݽṹ
typedef struct tagTMtConfState
{
    tagTMtConfState()
    {
        ZeroMemory( this, sizeof (tagTMtConfState) );
    }
    u8      m_dwMtState;                    //Mt״̬
    TCHAR   m_szConfId[MAX_CONFID_LEN];     //����Id
    TCHAR   m_szMtAlias[MAXLEN_ALIAS];      //Mt����
    TCHAR   m_szConfTime[TIME_LEN];         //�澯����ʱ��

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/04/03  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE,
                     "State = %d, Alias = %s, ConfID = %s, Time = %s\n",
                     m_dwMtState, m_szMtAlias, m_szConfId, m_szConfTime );
    }
} TMtConfState, *PTMtConfState;


//������������ñ���
typedef struct tagSvrConfig
{
    tagSvrConfig()
    {
        ZeroMemory(this, sizeof (tagSvrConfig));
    }
    TCHAR   m_szIPAddr[IPADDR_LEN];         //������ip��ַ
    TCHAR   m_aszReadCommunity[MAX_COMMUNITY_LEN];  //����ͬ����
    TCHAR   m_aszWriteCommunity[MAX_COMMUNITY_LEN]; //д��ͬ����
    u16     m_wTrapPort;                    //����������trap�Ķ˿�
    u16     m_wOspConnPort;                 //������Osp�����˿�
    u16     m_wOspTelnetPort;               //������Telnet�˿�
    u16     m_wCmSyncPeriod;                //������ѯ�Ķ�ʱʱ��
    u16     m_wFmSyncPeriod;                //�澯��ѯ�Ķ�ʱʱ��
    u8      m_bySnmpTimeout;                //Snmp��ʱ

    TCHAR   m_szDBServer[IPADDR_LEN];       //���������ӵ����ݿ��ַ
    TCHAR   m_szDBName[DB_NAME_MAX_LEN];    //���������ӵ����ݿ���
    TCHAR   m_szDBUser[USER_LEN];           //���������ӵ��û���
    TCHAR   m_szDBPwd[PWD_LEN];             //���������ӵ��û�����

    TCHAR   m_szRemoteFtpUser[USER_LEN];    //����������agent��ftp�û���
    TCHAR   m_szRemoteFtpPwd[PWD_LEN];      //����������agent��ftp�û�����
    TCHAR   m_szLocalFtpUser[USER_LEN];     //���������ص�Ftp�û���
    TCHAR   m_szLocalFtpPwd[PWD_LEN];       //���������ص�Ftp�û�����
    TCHAR   m_szFtpLocalPath[MAX_PATH];     //���������ص�ftp·��

    u8      m_byPrintToScreenLevel;         //��������ӡ��Ļ�ĵȼ�
    u8      m_byPrintToFileLevel;           //��������־�ļ���¼�Ǽ�
    TCHAR   m_szLogFile[MAX_PATH];          //��������־�ļ���

    /*=============================================================================
    �� �� ��:Print
    ��    ��:���ݴ�ӡ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2006/03/30  4.0     ���    ����
    =============================================================================*/
    void Print(void) const
    {
        ::OspPrintf( TRUE, FALSE, "SvrIp = %s, TrapPort = %d, Read = %s, Write = %s, \
OspPort = %d, TelnetPort = %d, CmPoll = %d, FmPoll = %d, Timeout = %d, DbIp = %s, \
DbName = %s, DbUser = %s, DbPwd = %s, FtpRemoteUser = %s, FtpRemotePwd = %s, \
FtpLocalUser = %s, FtpLocalPwd = %s, FtpLocalPath = %s, Screen = %d, File = %d, \
LogPath = %s\n",
                     m_szIPAddr, m_wTrapPort, m_aszReadCommunity, m_aszWriteCommunity,
                     m_wOspConnPort, m_wOspTelnetPort, m_wCmSyncPeriod, m_wFmSyncPeriod,
                     m_bySnmpTimeout, m_szDBServer, m_szDBName, m_szDBUser,
                     m_szDBPwd, m_szRemoteFtpUser, m_szRemoteFtpPwd,
                     m_szLocalFtpUser, m_szLocalFtpPwd, m_szFtpLocalPath,
                     m_byPrintToScreenLevel, m_byPrintToFileLevel, m_szLogFile );
    }
} TSvrConfig;

#endif
