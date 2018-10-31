/*****************************************************************************
ģ����	��
�ļ���	��Connon.h
����ļ�	��
�ļ�ʵ�ֹ��ܣ���صĺ궨�壬��Ϣ����
����		��
�汾		��
---------------------------------------------------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
04/10/2007	1.0          ĳĳ        ĳĳ      ------------
******************************************************************************/


#ifndef COMMON_H
#define COMMON_H

#include "osp.h"

//�������
#define PT_PROCEDURE_MAX		(u8)16
#define PT_MAX_NO_PER_PROCEDURE   (u8)6

//�����ӵ�����������Կ���̨��
#define PT_CONFIG_MAX		(u8)1

//�����ӵ�����������Բ���̨��������������
#define PT_PROCEDURE_TOTAL_MAX		(u16)PT_PROCEDURE_MAX*PT_MAX_NO_PER_PROCEDURE

//�������˿ں�
#define PT_SERVRT_PORT     (u16)70000

//������APP
#define PT_SERVER_CONTROL_APP           (u16)1
#define PT_SERVER_CONTROL_INS_NUM       (u16)1
#define PT_SERVER_PROCEDURE_APP         (u16)2
#define PT_SERVER_PROCEDURE_INS_NUM     (u16)PT_PROCEDURE_TOTAL_MAX
#define PT_SERVER_CONFIG_APP            (u16)3
#define PT_SERVER_CONFIG_INS_NUM        (u16)1
#define PT_SERVER_APP_PRI               (u8)100

//����̨APP
#define PT_TEST_APP		(u16)4
#define PT_TEST_INS_NUM	(u16)1

//����̨APP
#define PT_CONFIG_APP		(u16)5
#define PT_CONFIG_INS_NUM	(u16)1


#define PT_MAX_SERIAL_LENGTH		(u8)32		//���кŵ���󳤶�
#define PT_MAX_MAC_LENGTH			(u8)20		//MAC��ַ��󳤶�
#define PT_MAX_IP_LENGTH			(u8)16		//IP��ַ��󳤶�
#define PT_MAX_EMPLOYEENO_LENGTH	(u8)32		//������󳤶�
#define PT_MAX_DATETIME_LENGTH		(u8)20		//����ʱ����󳤶�
#define PT_MAX_DATE_LENGTH		    (u8)12		//������󳤶�
#define PT_MAX_FILE_NAME_LENGTH	    (u8)32		//�ļ�����󳤶�
#define PT_MAX_NAME_LENGTH			(u8)32		//������󳤶�
#define PT_MAX_PATH_LENGTH          (u8)200		//·����󳤶�
#define PT_MAX_SQL_LENGTH           (u16)1000	//sql�����󳤶�
#define PT_MAX_TEST_ITEM            (u16)100	//���������ֵ
#define PT_MAX_DESC_LENGTH          (u8)32		//������Ϣ�ĳ���
#define PT_MAX_DEVICE_TYPE          (u8)20		//����豸������
#define PT_MAX_DEVTYPELEN           (u8)10      //�豸���͵������������
#define PT_MAX_FILE_TYPE            (u8)8		//����ļ�������
#define PT_RECORDNUM_PER_PACK       (u32)100    //������Խ��������¼��
//�������Ͷ���
#define		TEST_TYPE_FXO               1			//FXO��·����
#define		TEST_TYPE_SERIAL            2		    //���ڲ���
#define		TEST_TYPE_ETH               3			//���ڹ��ܲ���
#define		TEST_TYPE_USB               4			//USB���ܲ���
#define		TEST_TYPE_AUDIO             5		    //��Ƶ���ع��ܲ���
#define		TEST_TYPE_C1VGA             6		    //��Ƶ��������VGA������ܲ���
#define		TEST_TYPE_C1C               7           //��Ƶ��������C����������ܲ���
#define		TEST_TYPE_C2VGA  	        8           //��Ƶ��������VGA������ܲ���
#define		TEST_TYPE_C2C  	    	    9           //��Ƶ��������C����������ܲ���
#define		TEST_TYPE_LOUDSPEAKER       10	        //���������ܲ���
#define		TEST_TYPE_MIC               11			//MIC���ܲ���
#define		TEST_TYPE_CAMERAROTA        12	        //����ͷת������
#define		TEST_TYPE_RTC               13			//RTC���ܲ���
#define		TEST_TYPE_LIGHT             14		    //ָʾ�Ʋ���
#define		TEST_TYPE_REMOTECTRL        15	        //����ӿڹ��ܲ���
#define     TEST_TYPE_MAX               15

//�ļ����Ͷ���
#define  PT_FILE_TYPE_SYS          1//sys�ļ�����
#define  PT_FILE_TYPE_MAX          1

//��Ϣ�������
#define      PT_SERV_MSG_LEN					0x7000  //��Ϣ����
#define      PT_SERV_MSGHEAD_LEN				28      //��Ϣͷ����

//�����쳣״̬
#define PT_ERROR_OSP_DISCONNECT		(s32)1			//���豸�����Ӷ���

#define PT_TIMEOUT_SECOND           (u16)6          //�趨��ʱʱ��
/*****************************testClient<-->DBServer****************************/
//������Ϣ����  testClient-->DBServer
//testClient���͵�½����DBServer����Ϣ��Ϊ ITestLoginRequest
OSPEVENT( EV_TESTCLIENT_TO_DBSERVER_MSGTYPE_LOGIN_REQ,		1 );

//testClient������Ϣ��DBServer��ȡ������Ϣ����Ϣ��Ϊ ��
OSPEVENT( EV_TESTCLIENT_TO_DBSERVER_MSGTYPE_CONFIG_REQ,	2 );

//testClient��DBServer��ȡ������豸��IP��MAC����Ϣ��Ϊ���к� IDeviceAssign
OSPEVENT( EV_TESTCLIENT_TO_DBSERVER_MSGTYPE_IPMAC_REQ,	4 );

//testClient���Ͳ��Խ����DBServer����Ϣ��Ϊ IAutoTestResult
OSPEVENT( EV_TESTCLIENT_TO_DBSERVER_MSGTYPE_RESULT_SEND,	5 );


//������Ϣ����  DBServer-->testClient
//DBServer���͵�½Ӧ��ɹ���Ϣ��testClient����Ϣ��Ϊ ��
OSPEVENT( EV_DBSERVER_TO_TESTCLIENT_MSGTYPE_LOGIN_ACK,	1 );

//DBServer���͵�½Ӧ��ʧ����Ϣ��testClient����Ϣ��Ϊ ITestLoginNAck
OSPEVENT( EV_DBSERVER_TO_TESTCLIENT_MSGTYPE_LOGIN_NACK,	2 );

//DBServer����Ӧ��ͻ��˵�������Ϣ����testClient����Ϣ��Ϊ TPTTestItem+IDeviceInfo
OSPEVENT( EV_DBSERVER_TO_TESTCLIENT_MSGTYPE_CONFIG_ACK,	3 );

//DBServer����Ӧ��ͻ��˵�IPMAC����testClient����Ϣ��Ϊ IDeviceAssign
OSPEVENT( EV_DBSERVER_TO_TESTCLIENT_MSGTYPE_IPMAC_ACK,	4 );

 /***********************END testClient<-->DBServer****************************/



/*****************************configClient<-->DBServer****************************/
//������Ϣ����  configClient-->DBServer
//configClient���͵�½/�ǳ�����DBServer����Ϣ��Ϊ IConfigLoginRequest
OSPEVENT( EV_CONFIGCLIENT_TO_DBSERVER_MSGTYPE_LOGIN_REQ,		1 );

//configClient����������Ϣ��DBServer����Ϣ��Ϊ IServerConfigInfo
OSPEVENT( EV_CONFIGCLIENT_TO_DBSERVER_MSGTYPE_CONFIG_SET,	3 );

//configClient������Ϣ��DBServer������ǰ������Ϣ����Ϣ��Ϊ ��
OSPEVENT( EV_CONFIGCLIENT_TO_DBSERVER_MSGTYPE_TESTINFO_QUERY,	4 );

//configClient������Ϣ��DBServer������ǰ������Ϣ����Ϣ��Ϊ ��
OSPEVENT( EV_CONFIGCLIENT_TO_DBSERVER_MSGTYPE_CONFIG_QUERY,	5 );

//configClient������Ϣ��DBServer��������������Ĳ��Խ������Ϣ��Ϊ IQueryTestResultCondition
OSPEVENT( EV_CONFIGCLIENT_TO_DBSERVER_MSGTYPE_RESULT_QUERY,	6 );

//configClient������Ϣ��DBServer�������ʼ�����ݣ���Ϣ��Ϊ ��
OSPEVENT( EV_CONFIGCLIENT_TO_DBSERVER_MSGTYPE_INITDATA_QUERY,	7 );

//������Ϣ����  DBServer-->configClient
//DBServer���͵�½Ӧ��ɹ���Ϣ��configClient����Ϣ��Ϊ ��
OSPEVENT( EV_DBSERVER_TO_CONFIGCLIENT_MSGTYPE_LOGIN_ACK,	1 );

//DBServer���͵�½Ӧ��ʧ����Ϣ��configClient����Ϣ��Ϊ ITestLoginNAck
OSPEVENT( EV_DBSERVER_TO_CONFIGCLIENT_MSGTYPE_LOGIN_NACK,	2 );

//configClient����������Ϣ��DBServer����Ϣ��Ϊ IConfigSetAck
OSPEVENT( EV_DBSERVER_TO_CONFIGCLIENT_MSGTYPE_CONFIG_SET_ACK,	3 );

//DBServer����Ӧ�������Ϣ��configClient����Ϣ��Ϊ IServerInfo
OSPEVENT( EV_DBSERVER_TO_CONFIGCLIENT_MSGTYPE_TESTINFO_ACK,	4 );

//DBServer����Ӧ��������Ϣ��configClient����Ϣ��Ϊ IServerConfigInfo
OSPEVENT( EV_DBSERVER_TO_CONFIGCLIENT_MSGTYPE_CONFIG_QUERY_ACK,	5 );

//DBServer����Ӧ����Խ����configClient����Ϣ��Ϊ TTestNote  ����Ϊsizeof(TTestNote)*n
OSPEVENT( EV_DBSERVER_TO_CONFIGCLIENT_MSGTYPE_RESULT_QUERY_ACK,	6 );

//DBServer����Ӧ���ʼ�����ݵ�configClient����Ϣ��Ϊ IInitConsoleInfo
OSPEVENT( EV_DBSERVER_TO_CONFIGCLIENT_MSGTYPE_INITDATA_QUERY_ACK,	7 );

/**************************END configClient<-->DBServer****************************/

//���Բ���̨��½�ṹ��
typedef struct tagTestLoginRequest
{
    private:
	    s8	m_szEmployeeNo[PT_MAX_EMPLOYEENO_LENGTH];	//����
	    s8  m_szPassword[PT_MAX_NAME_LENGTH];	        //����(��ʱû��������֤)
        u8  m_byProcedure;                              //����(�����������̨��½ʱ���ӵ���Ϣ)
        u8  m_byState;                                  //״̬ 1 ��½  0�ǳ�
        u8  padding[2];//���λ
    public:
        tagTestLoginRequest()
        {
            memset(m_szEmployeeNo,0,PT_MAX_NAME_LENGTH);
            memset(m_szPassword,0,PT_MAX_NAME_LENGTH);
            m_byProcedure = 0;
            memset(padding,0,2);
        }

        void setEmployeeNo(s8 * szNo){ strcpy(m_szEmployeeNo, szNo);}
        s8 * getEmployeeNo(){ return m_szEmployeeNo;}
        
        void setPassword(s8 * szPassword){ strcpy(m_szPassword, szPassword);}
        s8 * getPassword(){ return m_szPassword;}

        void setProcedure(u8 byProcedure){ m_byProcedure = byProcedure;}
        u8 getProcedure(){ return m_byProcedure;}

        void setState(u8 byState){ m_byState = byState;}
        u8 getState(){ return m_byState;}
        
}ITestLoginRequest;

//���ÿ���̨��½�ṹ��
typedef ITestLoginRequest IConfigLoginRequest;

//��½Ӧ��ʧ�ܽṹ��
typedef struct tagTestLoginNAck
{
    private:
        u8 m_byReason;//��½ʧ�ܵ�ԭ��1 �û���������� 2 ��½�û��� 3 �������������ݿ�ʧ��
        u8 padding[3];//���λ
    public:
        tagTestLoginNAck()
        {
            m_byReason = 0;
            memset(padding,0,3);
        }

        void setReason(u8 byReason){ m_byReason = byReason;}
        u8 getReason(){ return m_byReason;}
}ITestLoginNAck;

//������Ա��½��Ϣ
typedef struct tagTestLoginInfo 
{
	private:
		u32 m_dwIP;//����̨IP
	public:
		ITestLoginRequest m_ILoginReq;
		
		tagTestLoginInfo()
		{
			m_dwIP = 0;
		}
		
		void setIP(u32 dwIP){ m_dwIP = dwIP;}
		u32 getIP(){ return m_dwIP;}
}ITestLoginInfo;

//��������Ӧ��ṹ��
typedef struct tagConfigSetAck
{
    private:
        u8 m_byResult;//��� 1 �ɹ� 0 ʧ��
        u8 m_byReason;//����ʧ�ܵ�ԭ��1 �������ݿ�ʧ�� 2 ���ڲ����У������޸�����
        u8 padding[2];//���λ
    public:
		ITestLoginInfo m_ILoginInfo[5];//���ڲ����е���Ա��Ϣ�����5�����ٶ���û����

        tagConfigSetAck()
        {
            m_byResult = 0;
            m_byReason = 0;
            memset(padding,0,2);
        }

        void setResult(u8 byResult){ m_byResult = byResult;}
        u8 getResult(){ return m_byResult;}

        void setReason(u8 byReason){ m_byReason = byReason;}
        u8 getReason(){ return m_byReason;}
}IConfigSetAck;

//������
typedef struct tagPTTestItem
{
    public:
        u8      m_byTestItem[PT_MAX_TEST_ITEM+1];//�±��ʾ������,����0��ʾ����
		u8		padding[3];//���λ

        tagPTTestItem()
        {
            memset(m_byTestItem,0,PT_MAX_TEST_ITEM+1);
			memset(padding,0,3);
        }
}TPTTestItem;

//����ʱ��ṹ
typedef struct tagDateTime
{
	private:
		u16 m_wYear;	//��
		u8 m_byMonth;	//��
		u8 m_byDay;		//��
		u8 m_byHour;	//ʱ
		u8 m_byMinute;	//��
		u8 m_bySecond;	//��
		u8 padding;//���λ
	public:
		tagDateTime()
		{
			m_wYear = htons(2007);
			m_byMonth = 1;
			m_byDay = 1;
			m_byHour = 0;
			m_byMinute = 0;
			m_bySecond = 0;
			padding = 0;
		}

		void setYear(u16 wYear){ m_wYear = htons(wYear);}
        u16 getYear(){ return ntohs(m_wYear);}

		void setMonth(u8 byMonth){ m_byMonth = byMonth;}
        u8 getMonth(){ return m_byMonth;}

		void setDay(u8 byDay){ m_byDay = byDay;}
        u8 getDay(){ return m_byDay;}

		void setHour(u8 byHour){ m_byHour = byHour;}
        u8 getHour(){ return m_byHour;}

		void setMinute(u8 byMinute){ m_byMinute = byMinute;}
        u8 getMinute(){ return m_byMinute;}

		void setSecond(u8 bySecond){ m_bySecond = bySecond;}
        u8 getSecond(){ return m_bySecond;}
}IDateTime;

//���Խ����ѯ����
typedef struct tagQueryTestResultCondition
{
    private:
        u8 m_byCondition;			//0 ��ѯȫ�������  1 �����豸���Ͳ�ѯ  2 ���ݲ��Խ����ѯ 3 �����豸���ͺͲ��Խ����ϲ�ѯ
		u8 m_byTestResult;			//���Խ�� 1 ���Գɹ� 2 ����ʧ��
		u8 padding[2];//���λ
        u32	m_dwDeviceType;			//�豸����
		u32 m_dwStart;				//��ǰ��ѯ��ʼ��¼�ţ���1��ʼ
        u32 m_dwCount;				//��ѯ���������
    public:
		IDateTime m_IStartDateTime;//��ѯ��ʼʱ��
		IDateTime m_IEndDateTime;//��ѯ����ʱ��

        tagQueryTestResultCondition()
        {
            m_byCondition = 0;
			memset(padding,0,2);
            m_dwDeviceType = 0;
			m_byTestResult = 0;
            m_dwStart = 0;
            m_dwCount = 0;
        }

        void setCondition(u8 byCondition){ m_byCondition = byCondition;}
        u8 getCondition(){ return m_byCondition;}

		void setTestResult(u8 byTestResult){ m_byTestResult = byTestResult;}
        u8 getTestResult(){ return m_byTestResult;}
		
		u8 getOpositTestResult()
		{
			if(1 == getTestResult())
			{
				return 2;
			}
			else if(2 == getTestResult())
			{
				return 1;
			}

		}
		
        void setDeviceType(u32 dwDeviceType){ m_dwDeviceType = htonl(dwDeviceType);}
        u32 getDeviceType(){ return ntohl(m_dwDeviceType);}

        void setStart(u32 dwStart){ m_dwStart = htonl(dwStart);}
        u32 getStart(){ return ntohl(m_dwStart);}

        void setCount(u32 dwCount){ m_dwCount = htonl(dwCount);}
        u32 getCount(){ return ntohl(m_dwCount);}
}IQueryTestResultCondition;
// ���Խ����¼�ṹ��
typedef struct tagTestNote
{
    private:
        s8		m_szSerial[PT_MAX_SERIAL_LENGTH];	    //���к�
        s8	    m_szIP[PT_MAX_IP_LENGTH];		        //IP
        s8	    m_szMACOne[PT_MAX_MAC_LENGTH];		    //��һ����MAC
        s8	    m_szMACTwo[PT_MAX_MAC_LENGTH];		    //�ڶ�����MAC
        s8		m_szDateTime[PT_MAX_DATETIME_LENGTH];	//��������ʱ�� ��ʽ: "2007-06-14 14-45-45\0"
        u32		m_dwDeviceType;				        //�豸����
    public:
        TPTTestItem	m_TTestItem;				    //0 δ��  1 ͨ��   2 ��ͨ��

        tagTestNote()
        {
            memset(m_szSerial,0,PT_MAX_SERIAL_LENGTH);
            memset(m_szIP,0,PT_MAX_IP_LENGTH);
            memset(m_szMACOne,0,PT_MAX_MAC_LENGTH);
            memset(m_szMACTwo,0,PT_MAX_MAC_LENGTH);
            memset(m_szDateTime,0,PT_MAX_DATETIME_LENGTH);
            m_dwDeviceType = 0;
        }

        void setSerial(s8 * szSerial){ strcpy(m_szSerial, szSerial);}
        s8 * getSerial(){ return m_szSerial;}

        void setIP(s8 * szIP){ strcpy(m_szIP, szIP);}
        s8 * getIP(){ return m_szIP;}

        void setMACOne(s8 * szMAC){ strcpy(m_szMACOne, szMAC);}
        s8 * getMACOne(){ return m_szMACOne;}

        void setMACTwo(s8 * szMAC){ strcpy(m_szMACTwo, szMAC);}
        s8 * getMACTwo(){ return m_szMACTwo;}

        void setDateTime(s8 * szDateTime){ strcpy(m_szDateTime, szDateTime);}
        s8 * getDateTime(){ return m_szDateTime;}

        void setDeviceType(u32 dwDeviceType){ m_dwDeviceType = htonl(dwDeviceType);}
        u32 getDeviceType(){ return ntohl(m_dwDeviceType);}
}TTestNote;

// ���Խ����Ϣ�ṹ
typedef struct tagAutoTestResult
{
    private:
        //����״̬0 ������1�쳣��ָ�豸����������δ���������豸���ߵ������ĳ�����δͨ�������쳣��
        u8	    m_byTestState;
        u8      m_byIsLoad;                         //0 ����  1 ����
        u8		m_byProcedure;						//����
        u8      padding;//���λ
    public:
        TTestNote m_tTestNote;

        tagAutoTestResult()
        {
            m_byTestState = 0;
            m_byIsLoad = 0;
            m_byProcedure = 0;
            padding = 0;
        }

        void setTestState(u8 byTestState){ m_byTestState = byTestState;}
        u8 getTestState(){ return m_byTestState;}

        void setIsLoad(u8 byIsLoad){ m_byIsLoad = byIsLoad;}
        u8 getIsLoad(){ return m_byIsLoad;}

        void setProcedure(u8 byProcedure){ m_byProcedure = byProcedure;}
        u8 getProcedure(){ return m_byProcedure;}
}IAutoTestResult;

//���豸����IP��MAC�Ľṹ��
typedef struct tagDeviceAssign
{
    private:
        s8  m_szSerial[PT_MAX_SERIAL_LENGTH];	    //���к�
        s8	m_szIP[PT_MAX_IP_LENGTH];		    //IP
        s8	m_szMACOne[PT_MAX_MAC_LENGTH];	    //��һ�����ڵ�MAC
        s8  m_szMACTwo[PT_MAX_MAC_LENGTH];     //�ڶ������ڵ�MAC
    public:
        tagDeviceAssign()
        {
            memset(m_szSerial,0,PT_MAX_SERIAL_LENGTH);
            memset(m_szIP,0,PT_MAX_IP_LENGTH);
            memset(m_szMACOne,0,PT_MAX_MAC_LENGTH);
            memset(m_szMACTwo,0,PT_MAX_MAC_LENGTH);
        }

        void setSerial(s8 * szSerial){ strcpy(m_szSerial, szSerial);}
        s8 * getSerial(){ return m_szSerial;}

        void setIP(s8 * szIP){ strcpy(m_szIP, szIP);}
        s8 * getIP(){ return m_szIP;}

        void setMACOne(s8 * szMACOne){ strcpy(m_szMACOne, szMACOne);}
        s8 * getMACOne(){ return m_szMACOne;}

        void setMACTwo(s8 * szMACTwo){ strcpy(m_szMACTwo, szMACTwo);}
        s8 * getMACTwo(){ return m_szMACTwo;}
}IDeviceAssign;

//���ص��ļ���
typedef struct tagLoadFileName
{
    private:
        u8 m_byFileType;//�ļ�����
		u8 padding[3];//���λ
        s8 m_szName[PT_MAX_NAME_LENGTH];//�ļ�����
    public:
        tagLoadFileName()
        {
            m_byFileType = 0;
            memset(m_szName,0,PT_MAX_NAME_LENGTH);
			memset(padding,0,3);
        }
        
        void setFileType(u8 byFileType){ m_byFileType = byFileType;}
        u8 getFileType(){ return m_byFileType;}
        
        void setName(s8 * szName){ strcpy(m_szName,szName);}
        s8 * getName(){ return m_szName;}
}ILoadFileName;

//�豸��Ϣ�ṹ��
typedef struct tagDeviceInfo
{
    private:
        s8	m_szFirstIP[PT_MAX_IP_LENGTH];		    //��ʼIP
        s8	m_szFirstMACOne[PT_MAX_MAC_LENGTH];	    //��һ�����ڵ���ʼMAC
        s8  m_szFirstMACTwo[PT_MAX_MAC_LENGTH];     //�ڶ������ڵ���ʼMAC
        s8  m_szServerPath[PT_MAX_PATH_LENGTH];     //�������˲��Խ�������Ŀ¼,Ĭ���Ǳ�����C�̸�Ŀ¼
        s8  m_szOperatorPath[PT_MAX_PATH_LENGTH];   //����̨�˲��Խ�������Ŀ¼,Ĭ���Ǳ�����C�̸�Ŀ¼(��ʱ����)
        s8	m_szDate[PT_MAX_DATE_LENGTH];		    //�豸���������� ��ʽ: "2007-06-14\0"
        u32 m_dwCount;						    //���β��Ե��豸����
        u32	m_dwDeviceType;					    //�豸����
        u8	m_bySerialLength;					//���к�λ��
        u8	m_byHardwareVersion;				//Ӳ���汾
        u8	m_byE2promInfo;					    //E2prom��Ϣ
        u8	m_byE2promFlag;					    //E2prom��־
        u8  m_byAbort;                          //�������쳣����� 1--������һ����� 0--��ֹ���� Ĭ����0
        u8  m_byTestDelay;                      //ÿһ����Խ�������ӳ٣����������Ա�۲���Խ��
		u8  m_byResume;							//�Ƿ�ָ�Ĭ�ϳ������ã�1 �ָ� 0 ���ָ�
        u8  padding;//���λ
    public:
        ILoadFileName m_ILoadFile[PT_MAX_FILE_TYPE];    //�����ص��ļ�(���ļ���Ϣ���ڲ������ã�ֻ�ܲ�ѯ)

        tagDeviceInfo()
        {
            memset(m_szFirstIP,0,PT_MAX_IP_LENGTH);
            memset(m_szFirstMACOne,0,PT_MAX_MAC_LENGTH);
            memset(m_szFirstMACTwo,0,PT_MAX_MAC_LENGTH);
            memset(m_szServerPath,0,PT_MAX_PATH_LENGTH);
            memset(m_szOperatorPath,0,PT_MAX_PATH_LENGTH);
            memset(m_szDate,0,PT_MAX_DATE_LENGTH);
            m_dwCount = 0;
            m_dwDeviceType = 0;
            m_bySerialLength = 0;
            m_byHardwareVersion = 0;
            m_byE2promInfo = 0;
            m_byE2promFlag = 0;
            m_byAbort = 0;
            m_byTestDelay = 2;
			m_byResume = 0;
            padding = 0;
        }

		s8 * getLoadFile(u8 byFileType)
		{
			static s8 buf[2] = "";
			for(int i=0; i<PT_MAX_FILE_TYPE; i++)
			{
				if(m_ILoadFile[i].getFileType() == byFileType)
				{
					return m_ILoadFile[i].getName();
				}
			}
			return buf;
		}

        void setFirstIP(s8 * szFirstIP){ strcpy(m_szFirstIP, szFirstIP);}
        s8 * getFirstIP(){ return m_szFirstIP;}

        void setFirstMACOne(s8 * szFirstMACOne){ strcpy(m_szFirstMACOne, szFirstMACOne);}
        s8 * getFirstMACOne(){ return m_szFirstMACOne;}

        void setFirstMACTwo(s8 * szFirstMACTwo){ strcpy(m_szFirstMACTwo, szFirstMACTwo);}
        s8 * getFirstMACTwo(){ return m_szFirstMACTwo;}

        void setServerPath(s8 * szPath){ strcpy(m_szServerPath, szPath);}
        s8 * getServerPath(){ return m_szServerPath;}

        void setOperatorPath(s8 * szPath){ strcpy(m_szOperatorPath, szPath);}
        s8 * getOperatorPath(){ return m_szOperatorPath;}

        void setDate(s8 * szDate){ strcpy(m_szDate, szDate);}
        s8 * getDate(){ return m_szDate;}

        void setCount(u32 dwCount){ m_dwCount = htonl(dwCount);}
        u32 getCount(){ return ntohl(m_dwCount);}

        void setSerialLength(u8 bySerialLength){ m_bySerialLength = bySerialLength;}
        u8 getSerialLength(){ return m_bySerialLength;}

        void setDeviceType(u32 dwDeviceType){ m_dwDeviceType = htonl(dwDeviceType);}
        u32 getDeviceType(){ return ntohl(m_dwDeviceType);}

        void setHardwareVersion(u8 byHardwareVersion){ m_byHardwareVersion = byHardwareVersion;}
        u8 getHardwareVersion(){ return m_byHardwareVersion;}

        void setE2promInfo(u8 byE2promInfo){ m_byE2promInfo = byE2promInfo;}
        u8 getE2promInfo(){ return m_byE2promInfo;}

        void setE2promFlag(u8 byE2promFlag){ m_byE2promFlag = byE2promFlag;}
        u8 getE2promFlag(){ return m_byE2promFlag;}

        void setAbort(u8 byAbort){ m_byAbort = byAbort;}
        u8 getAbort(){ return m_byAbort;}

        void setTestDelay(u8 byTestDelay){ m_byTestDelay = byTestDelay;}
        u8 getTestDelay(){ return m_byTestDelay;}

		void setResume(u8 byResume){ m_byResume = byResume;}
        u8 getResume(){ return m_byResume;}
}IDeviceInfo;

//��������Ϣ���ýṹ��
typedef struct tagServerConfigInfo
{
    private:
        u8   m_byProcedureMax;					            //���õ��������
        u8   padding[3];//���λ
    public:
        TPTTestItem m_IProcedureInfo[PT_PROCEDURE_MAX];		//����������Ϣ
        IDeviceInfo   m_IDeviceInfo;                        //�豸��Ϣ

        tagServerConfigInfo()
        {
            m_byProcedureMax = 0;
            memset(padding,0,3);
        }

        void setProcedureMax(u8 byProcedureMax){ m_byProcedureMax = byProcedureMax;}
        u8 getProcedureMax(){ return m_byProcedureMax;}
}IServerConfigInfo;

//��������Ϣ����δʹ�ã�
typedef struct tagServerInfo
{
    //BOOL m_bDBState;        //���ݿ�״̬
}IServerInfo;

//�豸��ʼ����Ϣ
typedef struct tagDeviceTypeDesc
{
    private:
        u32 m_dwDeviceType;//�豸����
        s8  m_szDesc[PT_MAX_DESC_LENGTH];//�豸����
    public:
        u8  m_byFileType[PT_MAX_FILE_TYPE];//�豸���ļ�������Ϣ0 ��Ҫ���� 1Ҫ����
        TPTTestItem m_ITestItemInfo; //�豸�Ĳ�������Ϣ0 ���� 1 Ҫ��

        tagDeviceTypeDesc()
        {
            m_dwDeviceType = 0;
            memset(m_szDesc,0,PT_MAX_DESC_LENGTH);
            memset(m_byFileType,0,PT_MAX_FILE_TYPE);
        }

        void setDeviceType(u32 dwDeviceType){ m_dwDeviceType = dwDeviceType;}
        u32 getDeviceType(){ return m_dwDeviceType;}

        void setDesc(s8 * szDesc){ strcpy(m_szDesc,szDesc);}
        s8 * getDesc(){ return m_szDesc;}
}IDeviceTypeDesc;

//��������Ϣ
typedef struct tagTestItemDesc
{
    private:
        u8 m_byTestItem;//������
		u8 padding[3];//���λ
        s8 m_szDesc[PT_MAX_DESC_LENGTH];//����������
    public:
        tagTestItemDesc()
        {
            m_byTestItem = 0;
			memset(padding,0,3);
            memset(m_szDesc,0,PT_MAX_DESC_LENGTH);
        }

        void setTestItem(u8 byTestItem){ m_byTestItem = byTestItem;}
        u8 getTestItem(){ return m_byTestItem;}
    
        void setDesc(s8 * szDesc){ strcpy(m_szDesc,szDesc);}
        s8 * getDesc(){ return m_szDesc;}
}ITestItemDesc;

//�����ļ���Ϣ
typedef struct tagFileTypeDesc
{
    private:
        u8 m_byFileType;//�ļ�����
		u8 padding[3];//���λ
        s8 m_szDesc[PT_MAX_DESC_LENGTH];//�ļ�����
    public:
        tagFileTypeDesc()
        {
            m_byFileType = 0;
            memset(m_szDesc,0,PT_MAX_DESC_LENGTH);
			memset(padding,0,3);
        }

        void setFileType(u8 byFileType){ m_byFileType = byFileType;}
        u8 getFileType(){ return m_byFileType;}
        
        void setDesc(s8 * szDesc){ strcpy(m_szDesc,szDesc);}
        s8 * getDesc(){ return m_szDesc;}
}IFileTypeDesc;

//����̨�ĳ�ʼ����Ϣ�ṹ��
typedef struct tagInitConsoleInfo
{
    private:
        u8 m_byDeviceTypeNum;//�豸������
        u8 m_byTestItemMax;//������������ ����������1��ʼ�ۼ�
        u8 m_byFileTypeMax;//����ļ����� �ļ����ͱ����1��ʼ�ۼ�
		u8 padding;//���λ
    public:
        IDeviceTypeDesc m_IDevice[PT_MAX_DEVICE_TYPE];
        ITestItemDesc   m_ITestItem[PT_MAX_TEST_ITEM];
        IFileTypeDesc   m_IFileType[PT_MAX_FILE_TYPE];
        IServerConfigInfo m_IConfigInfo;

        tagInitConsoleInfo()
        {
            m_byDeviceTypeNum = 0;
            m_byTestItemMax = 0;
            m_byFileTypeMax = 0;
			padding = 0;
        }

        void setDeviceTypeNum(u8 byDeviceTypeNum){ m_byDeviceTypeNum = byDeviceTypeNum;}
        u8 getDeviceTypeNum(){ return m_byDeviceTypeNum;}

        void setTestItemMax(u8 byTestItemMax){ m_byTestItemMax = byTestItemMax;}
        u8 getTestItemMax(){ return m_byTestItemMax;}

        void setFileTypeMax(u8 byFileTypeMax){ m_byFileTypeMax = byFileTypeMax;}
        u8 getFileTypeMax(){ return m_byFileTypeMax;}
}IInitConsoleInfo;


//ҵ����Ϣ�࣬�����28K������Ϣ
class CPTServMsg
{
protected:
	u16     m_wSerialNO;            //��ˮ��
	u16		m_wEventId;             //�¼���
	u16		m_wErrorCode;           //������
	u16		m_wMsgBodyLen;          //��Ϣ�峤��
    u32     m_byTotalPktNum;        //�ܰ�����������Ҫ�а����͵���Ϣ��
    u32     m_byCurPktIdx;          //��ǰ����������0��ʼ��
	u8      m_abyReserverd[12];     //�����ֽ�
	u8      m_abyMsgBody[PT_SERV_MSG_LEN-PT_SERV_MSGHEAD_LEN];    //��Ϣ��
public:
	void  SetSerialNO(u16  wSerialNO){ m_wSerialNO = htons(wSerialNO);} 
    u16   GetSerialNO( void ) const { return ntohs(m_wSerialNO); }

    void  SetEventId(u16  wEventId){ m_wEventId = htons(wEventId);} 
    u16   GetEventId( void ) const { return ntohs(m_wEventId); }

    void  SetErrorCode(u16  wErrorCode){ m_wErrorCode = htons(wErrorCode);} 
    u16   GetErrorCode( void ) const { return ntohs(m_wErrorCode); }

    void  SetTotalPktNum(u32 byPktNum) { m_byTotalPktNum = htonl(byPktNum); }
    u32    GetTotalPktNum( void ) { return ntohl(m_byTotalPktNum); }
	
    void  SetCurPktIdx(u32 byPktIdx) { m_byCurPktIdx = htonl(byPktIdx); }
    u32    GetCurPktIdx( void ) { return ntohl(m_byCurPktIdx); }
	
	void Init( void );
	void SetMsgBodyLen( u16  wMsgBodyLen );
	CPTServMsg( void );//constructor
	CPTServMsg( u8   * const pbyMsg, u16  wMsgLen );//constructor
	~CPTServMsg( void );//distructor
	void ClearHdr( void );//��Ϣͷ����
	u16  GetMsgBodyLen( void ) const;//��ȡ��Ϣ�峤����Ϣ
	u16  GetMsgBody( u8   * pbyMsgBodyBuf, u16  wBufLen ) const;//��ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
	u8   * const GetMsgBody( void ) const;//��ȡ��Ϣ��ָ�룬�û������ṩBUFFER
	void SetMsgBody( u8   * const pbyMsgBody = NULL, u16  wLen = 0 );//������Ϣ��
	void CatMsgBody( u8   * const pbyMsgBody, u16  wLen );//�����Ϣ��
	u16  GetServMsgLen( void ) const;//��ȡ������Ϣ����
	u16  GetServMsg( u8   * pbyMsgBuf, u16  wBufLen ) const;//��ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
	u8   * const GetServMsg( void ) const;//��ȡ������Ϣָ�룬�û������ṩBUFFER
	void SetServMsg( u8   * const pbyMsg, u16  wLen );//����������Ϣ
	const CPTServMsg & operator= ( const CPTServMsg & cServMsg );//����������
};

/*-------------------------------------------------------------------
                               CPTServMsg                              
--------------------------------------------------------------------*/

/*====================================================================
    ������      ��CPTServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CPTServMsg::CPTServMsg( void )
{
	Init();
}

/*====================================================================
    ������      ��CPTServMsg
    ����        ��constructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, Ҫ��ֵ����Ϣָ��
				  u16 wMsgLen, Ҫ��ֵ����Ϣ���ȣ�������ڵ��� PT_SERV_MSGHEAD_LEN
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CPTServMsg::CPTServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	Init();
	
	if( wMsgLen < PT_SERV_MSGHEAD_LEN || pbyMsg == NULL )
		return;
	
	wMsgLen = min( wMsgLen, PT_SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	
	//set length
	SetMsgBodyLen( wMsgLen - PT_SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��~CPTServMsg
    ����        ��distructor
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline CPTServMsg::~CPTServMsg( void )
{

}

/*====================================================================
    ������      ��Init
    ����        ��BUFFER��ʼ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CPTServMsg::Init( void )
{
	memset( this, 0, PT_SERV_MSG_LEN );	//����
}

/*====================================================================
    ������      ��ClearHdr
    ����        ����Ϣͷ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����
    ����ֵ˵��  ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CPTServMsg::ClearHdr( void )
{
	u16		wBodyLen = GetMsgBodyLen();

	memset( this, 0, PT_SERV_MSGHEAD_LEN );	//����
	SetMsgBodyLen( wBodyLen );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ��Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ����Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CPTServMsg::GetMsgBodyLen( void ) const
{
	return( ntohs( m_wMsgBodyLen ) );
}

/*====================================================================
    ������      ��SetMsgBodyLen
    ����        ��������Ϣ�峤����Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u16 wMsgBodyLen, ��Ϣ�峤��
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CPTServMsg::SetMsgBodyLen( u16 wMsgBodyLen )
{
	m_wMsgBodyLen = htons( wMsgBodyLen );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ��ָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CPTServMsg::GetMsgBody( void ) const
{
	return( ( u8 * const )m_abyMsgBody );
}

/*====================================================================
    ������      ��GetMsgBodyLen
    ����        ����ȡ������Ϣ����
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��������Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u16 CPTServMsg::GetServMsgLen( void ) const
{
	return( GetMsgBodyLen() + PT_SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ��Ϣ�壬���û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBodyBuf, ���ص���Ϣ��
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ�峤��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CPTServMsg::GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
{
    u16 wActLen = min( GetMsgBodyLen(), wBufLen );
	memcpy( pbyMsgBodyBuf, m_abyMsgBody, wActLen );
	return wActLen;
}

/*====================================================================
    ������      ��SetMsgBody
    ����        ��������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CPTServMsg::SetMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        SetMsgBodyLen( 0 );
        return;
    }
    */
	wLen = min( wLen, PT_SERV_MSG_LEN - PT_SERV_MSGHEAD_LEN );
	memcpy( m_abyMsgBody, pbyMsgBody, wLen );
	SetMsgBodyLen( wLen );
}

/*====================================================================
    ������      ��CatMsgBody
    ����        �������Ϣ��
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsgBody, �������Ϣ�壬ȱʡΪNULL
				  u16 wLen, �������Ϣ�峤�ȣ�ȱʡΪ0
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/11/07    1.0         Liaoweijiang  ����
====================================================================*/
inline void CPTServMsg::CatMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        return;
    }
    */
	wLen = min( wLen, PT_SERV_MSG_LEN - PT_SERV_MSGHEAD_LEN - GetMsgBodyLen() );
	memcpy( m_abyMsgBody + GetMsgBodyLen(), pbyMsgBody, wLen );
	SetMsgBodyLen( GetMsgBodyLen() + wLen );
}

/*====================================================================
    ������      ��GetMsgBody
    ����        ����ȡ������Ϣָ�룬�û������ṩBUFFER
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵������
    ����ֵ˵��  ��u8 * constָ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline u8 * const CPTServMsg::GetServMsg( void ) const
{
	return( ( u8 * const )( this ) );
}

/*====================================================================
    ������      ��GetServMsg
    ����        ����ȡ������Ϣ�����û�����BUFFER�������С���ضϴ���
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * pbyMsgBuf, ���ص���Ϣ
				  u16 wBufLen, BUFFER��С
    ����ֵ˵��  ��ʵ�ʷ��ص���Ϣ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline u16 CPTServMsg::GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
{
	wBufLen = min(PT_SERV_MSG_LEN,wBufLen);
	memcpy( pbyMsgBuf, this, wBufLen );
	return( min( GetMsgBodyLen() + PT_SERV_MSGHEAD_LEN, wBufLen ) );
}

/*====================================================================
    ������      ��SetServMsg
    ����        ������������Ϣ
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����u8 * const pbyMsg, �����������Ϣ
				  u16 wMsgLen, �������Ϣ����
    ����ֵ˵��  ����
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/15    1.0         LI Yi         ����
====================================================================*/
inline void CPTServMsg::SetServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	if( wMsgLen < PT_SERV_MSGHEAD_LEN )
	{
		OspPrintf( TRUE, FALSE, "CPTServMsg: SetServMsg() Exception -- invalid MsgLen!\n" );
		return;
	}

	wMsgLen = min( wMsgLen, PT_SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	SetMsgBodyLen( wMsgLen - PT_SERV_MSGHEAD_LEN );
}

/*====================================================================
    ������      ��operator=
    ����        ������������
    �㷨ʵ��    ��
    ����ȫ�ֱ�����
    �������˵����CPTServMsg & CPTServMsg, ��ֵ����Ϣ����
    ����ֵ˵��  ��CPTServMsg����Ӧ��
----------------------------------------------------------------------
    �޸ļ�¼    ��
    ��  ��      �汾        �޸���        �޸�����
    02/07/26    1.0         LI Yi         ����
====================================================================*/
inline const CPTServMsg & CPTServMsg::operator= ( const CPTServMsg & cServMsg )
{
	u16	wLen = cServMsg.GetServMsgLen();

	memcpy( this, cServMsg.GetServMsg(), wLen );
	return( *this );
}

#endif





















