/********************************************************************
	ģ����:      NMCLib
	�ļ���:      nmclibdef.h
	����ļ�:    
	�ļ�ʵ�ֹ��� NMCLib�д����붨�壬��Ϣ���壬�ṹ���塣
    ���ߣ�       ������
	�汾��       3.5
------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/08/03	3.5			������                  ����

*********************************************************************/
#pragma once

#include "kdvType.h"		// ��������
#include "kdvDef.h"			// ������
#include "errorid.h"

// ���������
#define ERR_NMC_AFFAIR_BGN		ERR_CLT_BGN		// ���ܿ�����뿪ʼ = 10001~12000
enum
{
	No_Error = 0,
	Err_Success_With_Info	= ERR_CLT_END,				// 12000
	Err_Env_Already = ERR_NMC_AFFAIR_BGN + 0,			// 10001--�����Ѿ�׼����
	Err_Env_Not_Prepare,								// 10002--������û��׼����

	Err_Logon_Already = ERR_NMC_AFFAIR_BGN + 50,		// 10051--�Ѿ����ڵ�¼״̬
	Err_Logoff_Already,									// 10052--�Ѿ�����ע��״̬
	Err_Logon_Not,										// 10053--���ܿ⻹û�е�¼
	Err_Logon_User_Pwd,									// 10054--�û��������

	Err_Event_Timeout = ERR_NMC_AFFAIR_BGN + 100,		// 10101--������ʱ��
	
	Err_Osp_Create = ERR_NMC_AFFAIR_BGN + 150,			// 10151--���ӷ�������ʼ��ʧ��
	Err_Osp_Connect,									// 10152--���������Ӳ��ɹ�
	Err_Osp_ReSendCommad,								// 10153--������Ϣ�ڵȴ���Ӧ��
	Err_Osp_NoRevHandle,								// 10154--��Ϣ���մ���δ������
	
	Err_Db_Odbc_Create = ERR_NMC_AFFAIR_BGN + 200,		// 10201--odbc����ʧ��
	Err_Db_Odbc_Stmt,									// 10202--���ݿ����������ʧ��
	Err_Db_Odbc_Exec,									// 10203--ֱ��ִ��ʧ��
	Err_Db_Odbc_Produce,								// 10204--�洢����ʧ��
	Err_Db_Odbc_Env,									// 10205--����
	Err_Db_Odbc_Fetch,									// 10206--�α����

	Err_Db_Odbc_Filter_Exists,							// 10207--���õĸ澯���Ѵ���
	
	Err_Log_Read_End = ERR_NMC_AFFAIR_BGN + 300,		// 10301--��־�Ѿ���ȡ���
	Err_Log_Type_Match,									// 10302--��־���Ͳ�ƥ��
	
	Err_Param_Invalid = ERR_NMC_AFFAIR_BGN + 400,		// 10401--�������Ϸ�
	
	Err_Device_Exist_Not = ERR_NMC_AFFAIR_BGN + 500,	// 10501--�豸������
	Err_Device_Type,									// 10502--�豸���ͷǷ�
	Err_Device_Ip_Already,								// 10503--�Ѿ����ڸõ�ַ���豸��
	Err_Mt_Catalog,										// 10504--�ն˷���Ƿ�
	
	Err_User_Exist_Not = ERR_NMC_AFFAIR_BGN + 600,		// 10601--���ڲ�����
	Err_User_Exist_Already,								// 10602--�û��Ѿ�����
	Err_User_Privilege,									// 10603--û��Ȩ��
	Err_User_Chg_Pwd_Other,								// 10604--�����޸����˿���
	Err_User_Group_Unlink,								// 10605--���ܶϿ����û��͸���Ĺ�ϵ
	Err_User_Del_Root,									// 10606--����ɾ�����û�

	Err_Group_Exist_Already = ERR_NMC_AFFAIR_BGN + 700,	// 10701--�����Ѿ�����
	Err_Group_Exist_Not,								// 10702--���鲻����
	Err_Group_Destroy_Forbid,							// 10703--��ֹ������
	Err_Group_Priv_Assign_Already,						// 10704--�����Ѿ�ӵ�и�Ȩ��
	Err_Group_Priv_Assign_Not,							// 10705--���黹û�з����Ȩ��
	Err_Group_User_Own_Already,							// 10706--�����Ѿ�ӵ�иó�Ա
	Err_Group_User_Own_Not,								// 10707--���黹û��ӵ�иó�Ա
	Err_Group_User_Unassign,							// 10708--���ܶϿ�����͸��û��Ĺ�ϵ
	Err_Group_Del_Root,									// 10709--����ɾ������
	
	Err_Ftp_File_Exist = ERR_NMC_AFFAIR_BGN + 800,		// 10801--�ļ����䣬�ļ�������
	Err_Ftp_File_Type,									// 10802--�ļ����ʹ���
	Err_Ftp_File_Name,									// 10803--�ļ����ƴ���
	Err_Ftp_Get_Env,									// 10804--�ļ����价��û������
	Err_Ftp_Break,										// 10805--�ļ����䱻�ж�
	
	Err_Dir_Exists_Already = ERR_NMC_AFFAIR_BGN + 900,	// 10901--�豸Ŀ¼�Ѿ�����
	Err_Dir_Exists_Not,									// 10902--�豸Ŀ¼������
	
	Err_Unknown = ~0
};



// ���峤��
enum
{
	Max_OprMask_Len = 127, //���������� 1111 1111
	Max_Scheme_Len = 200,
    
	Max_Ip_Len = 16,
	Max_Object_Len = 16,

	Max_Date_Len = 16,
	Max_DateTime_Len = 24,
	Max_DateTime_Format_Len = 20,
    
	Max_AlarmValue_Len = 16,
	Max_Pwd_Len = 16,
	Max_Phone_Len = 32,
	Max_Addr_Len = 64,
	Max_Email_Len = 32,
	Max_Remark_Len = 64,
	Max_Serial_Len = 32,

	Max_Obj_Name_Len = 64,
	Max_Logon_Len = 16,
	Max_Opr_Type_Len = 16,
	Max_Opr_Ret_Len = 8,

	Max_Introduction_Len = 200,
	Max_Describing_Len = 200,

	Max_Alias_Len = 32,
	Max_Name_Len = 32,

	Max_Board_Amount = 128                     //����λ��
};


	// ������Ч���豸���
#define INVALID_EQUIP_ID		0

	// ����Ȩ��
#define PRIVILEGE_CM_SYNC_CFG		0x00000001	// ����ͬ��
#define PRIVILEGE_CM_SYNC_TIME		0x00000002	// ʱ��ͬ��
#define PRIVILEGE_CM_FTP_DOWNLOAD	0x00000004	// �ļ�����
#define PRIVILEGE_CM_FTP_UPLOAD		0x00000008	// �ļ��ϴ�
#define PRIVILEGE_CM_RPC			0x00000010	// Զ�̿���
#define PRIVILEGE_FM_SYNC_ALARM		0x00000020	// �澯ͬ��

	
	// �ⲿ��Ϣ�ӿ� ���͵������windows��Ϣ
#define WM_NMC_BC_MESSAGE		WM_USER + 0x1000	// �㲥
#define WM_NMC_FTP_MESSAGE		WM_USER + 0x1001	// ����
#define WM_NMC_FM_MESSAGE		WM_USER + 0x1002	// ����
#define WM_NMC_PM_MESSAGE		WM_USER + 0x1003	// ����
#define WM_NMC_SM_MESSAGE		WM_USER + 0x1004	// ��ȫ

#define WM_NMC_UPDATE_FAIL      WM_USER + 0x1005

	// ����ʹ���¼�(���ܿ�ʹ�ã��������ܷ���������)
#define __EV_NMC_BGN			128 //EVENT_CTRL_END + 1	// 128��ʼ
	
#define __CM_NMC_COMMON			__EV_NMC_BGN	// 128
#define __CM_DIR_MEMBER_ADD		1	// �豸Ŀ¼��ӳ�Ա
#define __CM_DIR_MEMBER_DEL		2	// �豸Ŀ¼ɾ����Ա
#define __CM_DIR_MOVE			3	// �豸Ŀ¼�ƶ�
#define __CM_DIR_CREATE			4	// �豸Ŀ¼����
#define __CM_DIR_DESTROY		5	// �豸Ŀ¼����
#define __CM_DIR_RENAME			6	// �豸Ŀ¼����
#define __CM_DEVICE_ADD			7	// �豸����
#define __CM_DEVICE_DEL			8	// �豸ɾ��
#define __CM_DEVICE_ALIAS		9	// �����豸����
#define __CM_DEVICE_IP			10	// �����豸��ַ
#define __CM_FTP_BREAK			11	// �ж��ļ�����
#define __CM_FTP_PROGRESS		12	// �ļ��������
#define __CM_EQUIP_PROPS_UPDATE	13  // �豸���Բ�ѯ
#define __CM_EQUIP_PROPS_QUERY  14  // �豸���Ը���
#define __CM_DIR_MEMBER_POS_ADD		15	//���ӻ�������ݿ��豸����
#define __CM_DIR_GET_POS	16 //���Ľ����豸����
	
#define __FM_NMC_COMMON			__EV_NMC_BGN + 1	// 129
#define __FM_ALARM_LOG_CUR		1	// ��ѯ��ǰ�澯
#define __FM_ALARM_LOG_HIS_Q	2	// ��ѯ��ʷ�澯
#define __FM_ALARM_LOG_HIS_D	3	// ɾ����ʷ�澯
#define __FM_MOCK_QUERY			4	// ��ѯ���ܹ���
#define __FM_BOARD_QUERY		5	// ��ѯ����
#define __FM_ALARM_LOG_KONWLEDGE_BASE 6 // ��ѯ�澯֪ʶ��
#define __FM_ALARM_KNOWLEDGE_BASE_D 7	// �澯֪ʶ��ɾ��
#define __FM_ALARM_KNOWLEDGE_BASE_A 8	// �澯֪ʶ������
#define __FM_ALARM_KNOWLEDGE_BASE_M 9	// �澯֪ʶ���޸�
#define __FM_ALARM_SET_FILTER	10		// �澯����
	
#define __PM_NMC_COMMON			__EV_NMC_BGN + 2	// 130
#define __PM_LOGON				1	// ��¼
#define __PM_LOGOFF				2	// ע��
	
#define __SM_NMC_COMMON			__EV_NMC_BGN + 3	// 131
#define __SM_USER_ADD			1		// �����û�
#define __SM_USER_DEL			2		// ɾ���û�
#define __SM_USER_MODIFY		3		// �޸��û�
#define __SM_USER_QUERY			4		// ��ѯ�û���Ϣ
#define __SM_USER_ENUM			5		// ö���û�
#define __SM_USER_LINK			6		// �û�����Ȩ����
#define __SM_USER_UNLINK		7		// �û�����Ȩ����
#define __SM_USER_GROUP			8		// ��ѯ�û�Ȩ����
#define __SM_GROUP_CREATE		9		// ������
#define __SM_GROUP_DESTROY		10		// ������
#define __SM_GROUP_MODIFY		11		// �޸���
#define __SM_GROUP_PRIV			12		// ��ѯ��Ȩ��
#define __SM_GROUP_ENUM			13		// ö����
#define __SM_GROUP_USER			14		// ��ѯ���Ա
#define __SM_GROUP_ASSIGN		15		// ������Ա
#define __SM_GROUP_UNASSIGN		16		// ɾ�����Ա
#define __SM_GROUP_ADD_PRIV		17		// �����Ȩ��
#define __SM_GROUP_DEL_PRIV		18		// ��ɾ��Ȩ��
#define __SM_LOG_DEL			19		// ������־ɾ��
#define __SM_LOG_QUERY			20		// ������־��ѯ
#define __SM_USER_PRIV_STAT		21		// ͳ���û���Ȩ��
#define __SM_GROUP_DESC_MODIFY	22		// �޸��û�����

#define __BC_NMC_COMMON			__EV_NMC_BGN + 4	// 132
#define __BC_ALARM				1	// �澯�㲥
#define __BC_LINK				2	// ��·�㲥
#define __BC_FM_MOCK			3	// ���ܹ���״̬�㲥
#define __BC_FM_BOARD			4	// ����澯�㲥
#define __BC_DEVICE				5	// �豸�޸Ĺ㲥
#define __BC_USER				6	// �û�����㲥
#define __BC_GROUP				7	// �����㲥

#define __EX_QUERY				__EV_NMC_BGN + 5
#define __EX_CONF_QUERY			1
#define __EX_MT_QUREY			2
#define __EV_NMC_END			__EV_NMC_BGN + 5		// 132����
	
	
	// ����澯����
#define ALARM_LEVEL_NO_ALARM	(~0)	// û�и澯
#define ALARM_LEVEL_LINKDOWN	0		// �����澯

	// ���������������
#define OPR_OBJ_NONE		0
#define OPR_OBJ_MCU			0x0001		// MCU
#define OPR_OBJ_MT			0x0002
#define OPR_OBJ_PERI		0x0004
#define OPR_OBJ_EQP			OPR_OBJ_MCU | OPR_OBJ_MT | OPR_OBJ_PERI
#define OPR_OBJ_USER		0x0100
#define OPR_OBJ_GROUP		0x0200
#define OPR_OBJ_ALARM_HIS	0x0400
#define OPR_OBJ_ALARM_CUR	0x0800
#define OPR_OBJ_LOG			0x1000
#define OPR_OBJ_ALARM_INI	0x2000
#define OPR_OBJ_DIR			0x4000
#define OPR_OBJ_ALARM_KONWLEDGE_BASE	0x8000
#define OPR_OBJ_CONF		0x8000

	// ��������������
#define OPR_RET_NONE		(~0)
	// ������־�����ѯ
#define OPR_LOG_RET_ALL		(-1)	// ��ѯ����
#define OPR_LOG_RET_FAIL	(-2)	// ��ѯʧ�ܵ�

	// �����жϲ����Ƿ�ɹ�
#define NMCAFFAIR_SUCCEEDED(dwErr)	((dwErr) == No_Error)

	//////////////////////////////////////////////////////////////////////////
	// �����¼������ݿ�Ķ�Ӧ����ֵλ�ã��������߿�ʼ
#define OTM_ALL_OPR				128 // all operation
#define OTM_CM_CFG_SYNC			1	// ��01λ������ͬ��
#define OTM_CM_TIME_SYNC		2	// ��02λ��ʱ��ͬ��

#define OTM_FTP_PUT_FILE		3	// ��03λ��ftp�ϴ��ļ�
#define OTM_FTP_GET_FILE		4	// ��04���Լ���FTP�����ļ�

#define OTM_RPC_RESTART			5	// ��05λ���豸������
#define OTM_RPC_STOP			6	// ��06λ���豸ֹͣ
#define OTM_RPC_SELFTEST		7	// ��07λ���豸�Լ�
#define OTM_RPC_RPC_BITERRTEST	8	// ��08λ���������
#define OTM_RPC_BOARD_RESTART	9	// ��09λ�ǵ��帴λ
#define OTM_RPC_BOARD_SYMC_TIME	10	// ��10λ�ǵ���ʱ��ͬ��
#define OTM_RPC_BOARD_BITERRTEST	11	// ��11λ�ǵ����������
#define OTM_RPC_BOARD_SELF		12	// ��12λ�ǵ����Բ�

#define OTM_FM_ALARM_SYNC		16	// ��16λ�Ǹ澯ͬ��

#define OTM_SM_PWD_CHG			19	// ��19λ���޸Ŀ���
	
#define OTM_NMC_CM_DIR_MEMBER_ADD	21	// ��21λ���豸Ŀ¼��ӳ�Ա
#define OTM_NMC_CM_DIR_MEMBER_DEL	22	// ��22λ���豸Ŀ¼ɾ����Ա
#define OTM_NMC_CM_DIR_MOVE			23	// ��23λ���豸Ŀ¼�ƶ�
#define OTM_NMC_CM_DIR_CREATE		24	// ��24λ���豸Ŀ¼����
#define OTM_NMC_CM_DIR_DESTROY		25	// ��25λ���豸Ŀ¼����
#define OTM_NMC_CM_DIR_RENAME		26	// ��26λ���豸Ŀ¼����
#define OTM_NMC_CM_DEVICE_ADD		27	// ��27λ���豸����
#define OTM_NMC_CM_DEVICE_DEL		28	// ��28λ���豸ɾ��
#define OTM_NMC_CM_DEVICE_ALIAS		29	// ��29λ���޸��豸����
#define OTM_NMC_CM_DEVICE_IP		30	// ��30λ���޸��豸��ַ
#define OTM_NMC_CM_FTP_BREAK		31	// ��31λ���ж��ļ�����

#define OTM_NMC_FM_ALARM_CUR_GET	35	// ��35λ�ǲ�ѯ��ǰ�澯
#define OTM_NMC_FM_ALARM_HIS_GET	36	// ��36λ�ǲ�ѯ��ʷ�澯
#define OTM_NMC_FM_ALARM_HIS_DEL	37	// ��37λ��ɾ����ʷ�澯
#define OTM_NMC_FM_MOCK_QUERY		38	// ��38λ�ǲ�ѯ���ܹ���
#define OTM_NMC_FM_ALARM_FILTER_GET	39	// ��39λ�ǻ�ȡ�澯��������
#define OTM_NMC_FM_ALARM_FILTER_SET	40	// ��40λ�����ø澯��������
	
#define OTM_NMC_PM_LOGON			45	// ��45λ���û���¼ϵͳ
#define OTM_NMC_PM_LOGOFF			46	// ��46λ���û�ע��ϵͳ

#define OTM_NMC_SM_USER_ADD			50	// ��31λ�������û�
#define OTM_NMC_SM_USER_DEL			51	// ��32λ��ɾ���û�
#define OTM_NMC_SM_USER_MODIFY		52	// ��33λ���޸��û�
#define OTM_NMC_SM_USER_QUERY		53	// ��34λ�ǲ�ѯ�û�����
#define OTM_NMC_SM_USER_ENUM		54	// ��35λ��ö���û�
#define OTM_NMC_SM_USER_LINK		55	// ��36λ�������û�Ȩ����
#define OTM_NMC_SM_USER_UNLINK		56	// ��37λ��ȡ���û�Ȩ����
#define OTM_NMC_SM_USER_GROUP		57	// ��38λ�ǲ�ѯ�û���Ȩ����
#define OTM_NMC_SM_GROUP_CREATE		58	// ��39λ�Ǵ���Ȩ����
#define OTM_NMC_SM_GROUP_DESTROY	59	// ��40λ������Ȩ����
#define OTM_NMC_SM_GROUP_MODIFY		60	// ��41λ���޸�Ȩ����
#define OTM_NMC_SM_GROUP_PRIV		61	// ��42λ�ǲ�ѯ���Ȩ��
#define OTM_NMC_SM_GROUP_ENUM		62	// ��43λ��ö����
#define OTM_NMC_SM_GROUP_USER		63	// ��44λ�ǲ�ѯ���Ա�û�
#define OTM_NMC_SM_GROUP_ASSIGN		64	// ��45λ������ӳ�Ա
#define OTM_NMC_SM_GROUP_UNASSIGN	65	// ��46λ��ɾ�����Ա
#define OTM_NMC_SM_GROUP_ADD_PRIV	66	// ��47λ��������Ȩ��
#define OTM_NMC_SM_GROUP_DEL_PRIV	67	// ��48λ����ɾ��Ȩ��
#define OTM_NMC_SM_USER_PRIV_STAT	68	// ��49λ���û�ͳ��Ȩ��
#define OTM_NMC_SM_LOG_DEL			69	// ��50λ��ɾ��������־
#define OTM_NMC_SM_LOG_QUERY		70	// ��51λ�ǲ�ѯ������־
		
#define MAKETYPEMASKVALID(bit, val)	(val[(bit - 1)] = '1')
#define MAKETYPEMASKUNUSE(bit, val) (val[(bit - 1)] = '0')

#define MAKEEVENT(event, sub)	MAKEWORD(sub, event)
#define MAKEOBJTYPE(type, catalog) MAKEWORD(type, catalog)
#define MAKEBCTYPE(bc) MAKELONG(MAKEEVENT(__BC_NMC_COMMON, bc), 0)

#define GETBCTYPE(type) LOWORD(type)
#define GETEVENT(ev) HIBYTE(ev)
#define GETSUBEV(ev) LOBYTE(ev)
#define GETCATALOG(type) HIBYTE(type)
#define GETOBJECTTYPE(type) LOBYTE(type)
//////////////////////////////////////////////////////////////////////////
//���ýṹ����

// ������ܹ���������ݽṹ
typedef struct tagTSlotInfo
{
	u32	m_dwBoardIp;	// �忨��ip��ַ
	u8	m_byLayerIndex;	// ����Ĳ�����
	u8	m_bySlotIndex;	// ����Ĳ�λ����
	u8	m_byBoardType;	// �忨����
	u8	m_byLinkStatus;	// �������·״��
    u8  m_byOsType;     // OS����
	s8	m_szPanelLed[64]; //������źŵ����
	s8  m_szSoftwareVersion[255]; //������Ӳ���汾 gl 2008.12.17
}TSlotInfo, *PTSlotInfo;


typedef struct tagTMockMachineData
{
	u8	m_byLayerAmount;	// ����Ĳ�������������Դ
	u8	m_bySlotLayerAmount;	// ����Ĳ�λ����
	u16	m_wSlotAmount;		// �����е����������ʵ�ʲ���ģ�
	TSlotInfo m_tSlotInfo[Max_Board_Amount]; // ��λ��Ϣ
}TMockMachineData, *PTMockMachineData;

//�澯֪ʶ�������Ϣ
typedef struct tagTAlarmKBInfo
{
	u32 m_dwSerialNo;  // ���к�
	u32 m_dwAlarmCode; // �澯��
	u8  m_byLevel;	 // �澯����
	u8  m_byObjType;	 // �澯��������
	s8  m_szDescription[MAX_PATH];
	s8  m_szSolution[MAX_PATH]; 
	s8  m_szProvider[32];
	s8  m_szMemo[MAX_PATH];
}TAlarmKBInfo, *PTAlarmKBInfo;

//�澯ԭ�����������
typedef struct tagTAlarmKBCause
{
	u32 m_dwSerialNo;		// ���к�
	u32 m_dwAlarmCode;	// �澯��
	s8  m_szCause[MAX_PATH];
}TAlarmKBCause, *PTAlarmKBCause;

// ����澯��������
typedef struct tagTAlarmRemark
{
	u32	m_dwCode;				// �澯��
	s8	m_szRemark[64];			// �澯����
	u8	m_byLevel;				// �澯����
}TAlarmRemark, *PTAlarmRemark;

// ��ʷ�澯��ѯ����
typedef struct tagTHistoryAlarmCondition
{
	s8	m_szAlarmValue[Max_AlarmValue_Len];// �澯ֵ
	s8	m_szDtGenBgn[Max_DateTime_Format_Len];	// �澯�������ڡ�����ʼ
	s8	m_szDtGenEnd[Max_DateTime_Format_Len];	// �澯�������ڡ�������
	s8	m_szDtResBgn[Max_DateTime_Format_Len];	// �澯�ָ�ʱ�䡪����ʼ
	s8	m_szDtResEnd[Max_DateTime_Format_Len];	// �澯�ָ�ʱ�䡪������
	u32	m_dwCode;	// �澯��
	u32	m_dwIpAddr;	// �豸��IP��ַ
	u32	m_dwDeviceID;// �豸�ı��
	u8	m_byLevel;	// �澯����--0x01��ʾһ���澯��
						//			0x02��ʾ�����澯��
						//			0x04��ʾ�����澯
	u8	m_byObject;	// �澯���󣬼��澯�����
}THistoryAlarmCondition, *PTHistoryAlarmCondition;

// �澯���ݶ���
typedef struct tagTAlarmContent
{
	s8	m_szSerial[Max_Serial_Len]; // �澯��ˮ��
	s8	m_szRemark[Max_Remark_Len]; // �澯����
	s8	m_szGenDate[Max_DateTime_Len]; // �澯����ʱ��
	s8	m_szResDate[Max_DateTime_Len]; // �澯�ָ�ʱ��
	s8	m_szScheme[Max_Scheme_Len];	// �������
	s8	m_szAlarmValue[Max_AlarmValue_Len];	// �澯ֵ
	s8	m_szProvider[32];		// �澯��������ṩ��
	s8	m_szMemo[MAX_PATH];		// ��ע
	u32	m_dwCode;		// �澯��
	u32	m_dwDeviceID;	// �豸���
	u32	m_dwIpAddr;		// �豸��IP��ַ
	u8	m_byLevel;		// �澯����
	u8	m_byObject;		// �澯����
}TAlarmContent, *PTAlarmContent;


// �澯��ϲ�ѯ����
typedef struct tagTAlarmDiagnoseCondition
{
	u32 m_dwCode;	// �澯��
	u8  m_byLevel;	// �澯���� 
	u32 m_dwDeviceID;//�豸���
}TAlarmDiagnoseCondition, *PTAlarmDiagnoseCondition;

// �澯�������� 
typedef struct tagTAlarmFilter
{
	u32	m_dwCode;	// �澯��
	u32	m_dwIpAddr;	// �豸��IP��ַ
	u32	m_dwAlarmCode;	// �澯��
	u16	m_wBoardId;		// �豸��BOARD���(DTI)
	u16	m_wUnitId;		// �豸��UNIT���(E1)
	u8	m_byAlarmObj;	// �澯����
	u8	m_byAlarmLevel;	// �澯����
}TAlarmFilter, *PTAlarmFilter;

// �û�������Ϣ
typedef struct tagTUserBaseInfo
{
	u32 m_dwUserID;		// �û��ı��
	s8  m_szLogon[Max_Logon_Len];	// �û���¼����
	s8  m_szPwd[Max_Pwd_Len]; // �û���¼����
	s8  m_szName[Max_Logon_Len];	// �û�����
	s8  m_szTelephone[Max_Phone_Len]; // �û��ĵ绰
	s8  m_szMobile[Max_Phone_Len]; // �û����ֻ�
	s8  m_szBeep[Max_Phone_Len]; // �û��ĺ���
	s8  m_szEmail[Max_Email_Len]; // �û��ĵ�������
	s8  m_szCompany[Max_Addr_Len]; // �û��Ĺ�˾
	s8  m_szAddress[Max_Addr_Len]; // �û��ĵ�ַ
	s8  m_szIntroduction[Max_Introduction_Len]; // �û����
	u8  m_bySex; // �û��Ա�0��ʾ�У�1��ʾŮ
}TUserBaseInfo, *PTUserBaseInfo;

//�û��������Ϣ
typedef struct tagTGroupBaseInfo
{
    u32 m_dwGroupID;
    s8  m_szGroupName[Max_Name_Len];
    s8  m_szDescribing[Max_Describing_Len];
}TGroupBaseInfo, *PTGroupBaseInfo;


//������Ϣ
typedef struct tagTNameInfo
{
    u32 m_dwID;
    s8  m_szName[Max_Name_Len];
}TNameInfo, *PTNameInfo, *PTNameStruct;

//�豸Ȩ��
typedef struct tagTPrivilege
{
    u32 m_dwDeviceID;
    u32 m_dwPrivilege;
}TPrivilege, *PTPrivilege;

// �û�������־��ѯ����
typedef struct tagTOprLogCondition
{
	s8	m_szLogon[MAX_PATH];	// ��¼����
	s8	m_szObjName[Max_Obj_Name_Len];	// ������������
	s8	m_szTmBgn[Max_DateTime_Format_Len];	// �������ڡ�����ʼ
	s8	m_szTmEnd[Max_DateTime_Format_Len];	// �������ڡ�������
	s8	m_szOprTypeMask[Max_OprMask_Len + 1];	// ������������
	u32	m_dwObjID;		// ����������
	u16	m_wObjType;		// �û�������������
	u16	m_wErrorCode; // �������
}TOprLogCondition, *PTOprLogCondition;


// �û�������־�������
typedef struct tagTOprLogResult
{
	s8	m_szSerial[Max_Serial_Len]; // ��ˮ��ULONG64	m_ul64SerialNo 
	s8	m_szLogon[Max_Logon_Len]; // ��¼����
	s8	m_szOprTime[Max_DateTime_Len]; // ��������
	s8	m_szOprType[32]; // ��������u16	m_wOprType
	s8	m_szObjName[Max_Obj_Name_Len]; // ������������
	s8	m_szRemark[MAX_PATH]; // ��ע
	s8	m_dwObjID;	// ����������
	u16	m_wObjType; // ������������
	u16	m_wErrorCode;	// ������
}TOprLogResult, *PTOprLogResult;

// ���ܷ�������ͨѶ����
typedef struct tagTNmsEnvData
{
	u32	m_dwNmsIp;	// ���ܷ�������ַ
	u16	m_wNmsPort;	// ���ܷ������ڵ�˿�
}TNmsEnvData, *PTNmsEnvData;


//�豸���ڵ���� xts20080901
typedef struct tagParentEQPEnvData
{
	u32	m_dwParentEQPIp;	// ���ڵ��ַ
	u16	m_wParentEQPID;	// ���豸�ı��
}TParentEQPEnvData, *PTParentEQPEnvData;
// ���ܿͻ��˱�������ݲ���
typedef struct tagTNmcEnvData
{
	s8	m_szLogFile[MAX_PATH]; // ��־�ļ�·��
	u16	m_wNodePort; // ����ڵ㵥Ԫ���Զ˿�
}TNmcEnvData, *PTNmcEnvData;


// �����¼
typedef struct tagTConfRecord
{
	u32 m_dwSerialNo;
	s8 m_szMcuAlias[129];
	s8 m_szConfId[33];	
	s8 m_szConfName[33];  // ��������
	s8 m_szBeginTime[Max_DateTime_Format_Len];	// ���鿪ʼʱ��
	s8 m_szEndTime[Max_DateTime_Format_Len];		// �������ʱ��
}TConfRecord, *PTConfRecord;

// �����ѯ����
typedef struct tagTConfQueryCondition
{
	s8 m_szMcuAlias[129]; // MCU����
	s8 m_szConfName[33];  // ��������
	s8 m_szConfId[33];	// ����ID
	s8 m_szBeginTime[Max_DateTime_Format_Len];	// ���鿪ʼʱ��
	s8 m_szEndTime[Max_DateTime_Format_Len];		// �������ʱ��
}TConfQueryCondition, *PTConfQueryCondition; 


// �ն˼�¼
typedef struct tagTMtRecord
{
	u32 m_dwSerialNo;
	s8 m_szMtAlias[129];
	s8 m_szConfID[33];
	s8 m_szOprTime[Max_DateTime_Format_Len];
	u32  m_dwOprType; 
}TMtRecord, *PTMtRecord;
// �ն˲�ѯ����
typedef struct tagMtQueryCondition
{
	s8 m_szMtAlias[129]; // Mt����
	s8 m_szConfName[33];  // ��������
	s8 m_szConfID[33];	// ����ID
	s8 m_szOprTime[Max_DateTime_Format_Len];	// �ն˲���ʱ��
	u32 m_dwOprType;		// ��������
}TMtQueryCondition, *PTMtQueryCondition; 


// �㲥��Ϣ���ݶ���
typedef struct tagTBCMessageContent
{
	u32	m_dwBCType;		// �㲥����
	LPVOID	m_pContent;		// �㲥����: ���ݹ㲥���Ͷ��������ڸ澯�㲥
}TBCMessageContent, *PTBCMessageContent;

// ����������㲥
typedef struct tagTBCObjectChangeContent
{
	u32	m_dwObjectID;	// ����Ķ�����
	u32	m_dwTargetID;	// ����������
	u16	m_wEventID;		// ����¼�
}TBCObjectChangeContent, *PTBCObjectChangeContent;

// �澯�㲥��������
typedef struct tagTBCAlarmContent
{
	u32	m_dwAlarmCode;//�澯��	
//	u32	m_dwCode;	// �澯��
	u32	m_dwDeviceID;	// �澯������
	u32	m_dwIpAddr;	// �豸��IP��ַ
	s8	m_szTime[Max_DateTime_Len];	//�澯ʱ��
	s8	m_szAlarmValue[Max_AlarmValue_Len];	// �澯ֵ
	u8	m_byAlarmType;	// �²����ĸ澯/�澯�ָ�
	u8	m_byObjectTypeId;// �澯��������Id
	u8	m_byAlarmLevel; // �澯����
}TBCAlarmContent, *PTBCAlarmContent;

// ��·�㲥�����ù㲥
typedef struct tagTBCCmContent
{
	u32	m_dwCode;	// �澯��
	u32	m_dwIpAddr;	// �豸��IP��ַ
	u8	m_byLinkStatus;
	u8	m_byReserved;	// ����
}TBCCmContent, *PTBCCmContent;

// ����������Ϣ���ݶ���
typedef struct tagTCmMessageContent
{
	u32	m_dwRspCode;	// ��Ӧ��
	u32	m_dwCode;	// �澯��
	u32	m_dwIpAddr;	// �豸��IP��ַ
	s8	m_szRemoteFile[MAX_PATH]; // �豸�ϵ��ļ�����
	s8	m_szLocalFile[MAX_PATH]; // �����ļ�����
	u16	m_wMsgType;		// ��Ϣ����
	u8	m_byReserved;	// ����
}TCmMessageContent, *PTCmMessageContent;

// ����������Ϣ���ݶ���
typedef struct tagTFmMessageContent
{
	u32	m_dwRspCode; // ��Ӧ��
	u32	m_dwCode;	// �澯��
	u32	m_dwIpAddr;	// �豸��IP��ַ
	u16	m_wMsgType;		// ��Ϣ����
}TFmMessageContent, *PTFmMessageContent;

// ��ȫ������Ϣ���ݶ���
typedef struct tagTSmMessageContent
{
	u32	m_dwRspCode;	// ��Ӧ��
	u16	m_wMsgType;		// ��Ϣ����
	u16	m_wReserved;	// ����
}TSmMessageContent, *PTSmMessageContent;

// ������Ϣ���ݶ���
typedef struct tagTPmMessageContent
{
	u32	m_dwRspCode; // ��Ӧ��
	u16	m_wMsgType; // ��Ϣ����
	u16	m_wReserved; // ����
}TPmMessageContent, *PTPmMessageContent;

typedef struct tagTFtpParameterStruct
{
	u32	m_dwDeviceID;		// �豸���
	s8	m_szLocalFile[MAX_PATH];	// �����ļ�·������
	s8	m_szRemoteFile[MAX_PATH];	// Զ���ļ�·������
	s8	m_szObjName[Max_Obj_Name_Len];	// �豸����
	u16	m_wDeviceType;		// �豸����
	u16	m_wFtpEvent;		// �ļ����䷽��
	u16	m_wOprObjType;			// ������������
//	u8	m_byFileType;		// �ļ�����--FILE_TYPE_ASC | FILE_TYPE_BIN
    u8  m_byOsType;         //����ϵͳ����
}TFtpParameterStruct, *PTFtpParameterStruct;

typedef struct tagTEquipProperty
{
	s8	m_szAlias[Max_Name_Len+1]; // ����
	u32	m_dwEquipID;	// �豸���
	u32	m_dwIpAddr;		// �豸ip��ַ
	u32 m_dwEquipParentID; // ���豸�豸���
	u8	m_byLinkStatus; // ����״̬
}TEquipProperty, *PTEquipProperty; 

typedef struct tagTDirInfo
{
    u32 m_dwDirID;                        //�豸��ID
    u32 m_dwSuperID;                      //���豸��ID
    s8	m_szDirName[Max_Name_Len + 1];     //����
}TDirInfo, *PTDirInfo;