/********************************************************************
ģ����:      ���ܿͻ��˽�����Կ�
�ļ���:      NmcCom.h
����ļ�:    
�ļ�ʵ�ֹ��� ���ܿͻ��˺궨��
���ߣ�       ������
�汾��       3.5
------------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/10/15	3.5			������                  ����
*********************************************************************/
#if _MSC_VER	> 1000
#pragma	once
#endif	// _MSG_VER > 1000

#include <vector>
using namespace std;


//������ԴIDȡ��ԭ���ܿͻ���resource.h�е�id
// �˵���ԴID
#define IDR_MENU_LOGON                  131		//�������˵�
#define IDR_MENU_POPUP                  137		//�����˵�
// ��¼������ԴID----------------------------------------------------------
#define IDC_COMBO_NMS                   1231	//���ܷ�����ѡ��	Combox
#define IDC_COMBO_USER_LOGON            1230	//��¼�û���		Combox
#define IDC_EDIT_PWD_LOGON              1007	//��¼����			Edit
#define IDC_BTN_REFRESH_SERVER          1005	//ˢ�·�����		Button
#define IDC_BTN_LOGON                   1004	//��¼				Button

// ���ϲ�ѯ������ԴID--------------------------------------------------------
#define IDC_COMBO_ALARM_CODE            1241	//�澯�����		Combox
#define IDC_EDIT_DEVICE_ID              1226	//�豸���			Edit
#define IDC_CHECK_ALARM_LEVEL_1         1035	//�澯����1��		CheckBox
#define IDC_CHECK_ALARM_LEVEL_2         1036	//�澯����2��		CheckBox
#define IDC_CHECK_ALARM_LEVEL_3         1037	//�澯����3��		CheckBox
//�澯����ʱ��
#define IDC_RADIO_ALARM_HIS_GEN_TIME_ALL		1131	//����ʱ��			RadioButton
#define IDC_RADIO_ALARM_TIME_GENERATE_MONTH		1038	//ǰ������			RadioButton
#define IDC_EDIT_ALARM_TIME_GENERATE_MONTH		1041	//ǰ������			Edit
#define IDC_RADIO_ALARM_TIME_GENERATE_DAY		1039	//ǰ����			RadioButton
#define IDC_EDIT_ALARM_TIME_GENERATE_DAY		1043	//ǰ����			Edit
#define IDC_RADIO_ALARM_TIME_GENERATE_BETWEEN	1040	//����ĳ��ʱ��	RadioButton
#define IDC_DATETIMEPICKER_ALARM_TIME_GENERATE_BGN_DATE 1045//��ʼ����	DateTimeCtrl
#define IDC_DATETIMEPICKER_ALARM_TIME_GENERATE_BGN_TIME 1046//��ʼʱ��	DateTimeCtrl
#define IDC_DATETIMEPICKER_ALARM_TIME_GENERATE_END_DATE 1047//��������	DateTimeCtrl
#define IDC_DATETIMEPICKER_ALARM_TIME_GENERATE_END_TIME 1048//����ʱ��	DateTimeCtrl
//�澯�ָ�ʱ��
#define IDC_RADIO_ALARM_HIS_RES_TIME_ALL		1130	//����ʱ��			RadioButton
#define IDC_RADIO_ALARM_TIME_RESTORE_MONTH		1049	//ǰ������			RadioButton
#define IDC_EDIT_ALARM_TIME_RESTORE_MONTH		1052	//ǰ������			Edit
#define IDC_RADIO_ALARM_TIME_RESTORE_DAY		1050	//ǰ����			RadioButton
#define IDC_EDIT_ALARM_TIME_RESTORE_DAY			1054	//ǰ����			Edit
#define IDC_RADIO_ALARM_TIME_RESTORE_BETWEEN	1051	//����ĳ��ʱ��		RadioButton
#define IDC_DATETIMEPICKER_ALARM_TIME_RESTORE_BGN_DATE 1056//��ʼ����	DateTimeCtrl
#define IDC_DATETIMEPICKER_ALARM_TIME_RESTORE_BGN_TIME 1057//��ʼʱ��	DateTimeCtrl
#define IDC_DATETIMEPICKER_ALARM_TIME_RESTORE_END_DATE 1058//��������	DateTimeCtrl
#define IDC_DATETIMEPICKER_ALARM_TIME_RESTORE_END_TIME 1059//����ʱ��	DateTimeCtrl

//////////////////////////////////////////////////////////////////////////
//MCU������־�Ի���
#define IDC_LIST_CONFINFO               1000      //������־��Ϣ      ListCtrl


//��־��ѯ������ԴID----------------------------------------------------------------
#define IDC_EDIT_OPRLOG_USER_MATCH      1009	//�û���			Edit	
#define IDC_SEL_ALL_OPER                1345	//ȫѡ				Button
#define IDC_UNSEL_ALL_OPER              1347	//ȫ��ѡ			Button
#define IDC_LIST_OPRLOG_OPRTYPE         1047	//��������			CheckBoxList
//��������ʱ��
#define IDC_RADIO_OPR_TIME_ALL          1125	//����ʱ��			RadioButton
#define IDC_RADIO_MONTH_LATEST          1011	//ǰ������			RadioButton
#define IDC_EDIT_OPR_DT_LATEST_MONTH    1012	//ǰ������			Edit
#define IDC_RADIO_DAY_LATEST            1014	//ǰ����			RadioButton
#define IDC_EDIT_OPR_DT_LATEST_DAY      1015	//ǰ����			Edit
#define IDC_RADIO_OPR_DT_BETWEEN        1017	//����ĳ��ʱ��		RadioButton
#define IDC_DATETIMEPICKER_BGN_DATE     1018	//��ʼ����			DateTimeCtrl
#define IDC_DATETIMEPICKER_END_DATE     1019	//��������			DateTimeCtrl
#define IDC_DATETIMEPICKER_BGN_TIME     1020	//��ʼʱ��			DateTimeCtrl
#define IDC_DATETIMEPICKER_END_TIME     1021	//����ʱ��			DateTimeCtrl
//��������
#define IDC_COMBO_OPR_OBJ_TYPE          1022	//������������		Combox
#define IDC_EDIT_OBJ_TYPE_NAME          1235	//��������			Edit
#define IDC_CHECK_LABEL_OBJ_ID          1239	//������			CheckButton
#define IDC_EDIT_OBJ_TYPE_ID            1237	//������			Edit
//�������
#define IDC_CHECK_OPR_RESULT_SUCC       1048	//�ɹ�				CheckButton
#define IDC_CHECK_OPR_RESULT_FAIL       1105	//ʧ��				CheckButton

//�澯��ѯ����־��ѯ--������ť-------------------
#define IDC_BTN_SEARCH_BEGIN            1002	//��ʼ����			Button
#define IDC_BTN_SEARCH_STOP             1003	//ֹͣ����			Button
#define IDC_BTN_LOG_DELETE              1243	//ȫ��ɾ��			Button

//�û����������ԴID-------------------------------------------------------
//��������
#define IDC_EDIT_USER_ID                1233	//�û����			Edit
#define IDC_EDIT_USER_INFO_LOGON_NAME   1065	//�û���			Edit
#define IDC_EDIT_USER_INFO_PWD_LOGON    1066	//�û�����			Edit	
#define IDC_EDIT_USER_INFO_PWD_CONFIRM  1067	//����ȷ��			Edit
#define IDC_EDIT_USER_INFO_NAME         1068	//�û���Ϣ�û���	Edit
#define IDC_RADIO_USER_INFO_SEX_MALE    1069	//�Ա���			RadioButton
#define IDC_RADIO_USER_INFO_SEX_FEMALE  1070	//�Ա�Ů			RadioButton
#define IDC_EDIT_USER_INFO_PHONE        1071	//�绰				Edit
#define IDC_EDIT_USER_INFO_MOBILE       1072	//�ֻ�				Edit
#define IDC_EDIT_USER_INFO_BEEP         1073	//����				Edit
#define IDC_EDIT_USER_INFO_EMAIL        1074	//Email				Edit
#define IDC_EDIT_USER_INFO_COMPANY      1075	//��λ				Edit
#define IDC_EDIT_USER_INFO_ADDRESS      1076	//סַ				Edit
#define IDC_EDIT_USER_INFO_REMARK       1082	//��ע				Edit
#define IDC_BTN_USER_ADD_SAVE           1103	//�û���ӣ����棩	Button
#define IDC_BTN_USER_INFO_MODIFY        1079	//�û��޸�			Button
#define IDC_BTN_USER_INFO_DEL           1080	//�û�ɾ��			Button
//Ȩ����Ϣ
#define IDC_LIST_USER_INFO_GROUPS       1063	//�û�Ȩ����Ϣ�б�	ListBox
#define IDC_BTN_USER_INFO_GROUP_ADD     1077	//�����			Button
#define IDC_BTN_USER_INFO_GROUP_DEL     1078	//ɾ����			Button	
#define IDC_BTN_USER_INFO_PRIV_STAT     1081	//ͳ��Ȩ��			Button

//�û�����������ԴID---------------------------------------------------
#define IDC_EDIT_GROUPNAME              1264	//������			Edit
#define IDC_EDIT_GROUP_DESCRIBING       1184	//������			Edit
#define IDC_BTN_GROUP_ADD_SAVE          1183	//�鴴��			Button
#define IDC_BTN_GROUP_MODIFY            1185	//���޸�			Button
#define IDC_BTN_GROUP_DESTROY           1182	//��ɾ��			Button
#define IDC_LIST_GROUP_INFO_USERS       1083	//��Ա�û��б�		List
#define IDC_BTN_GROUP_INFO_USER_ADD     1084	//��ӳ�Ա�û�		Button
#define IDC_BTN_GROUP_INFO_USER_DEL     1085	//ɾ����Ա�û�		Button
#define IDC_BTN_GROUP_INFO_PRIV_SET     1087	//Ȩ������			Button
#define IDC_LIST_GROUP_INFO_PRIVILEGE   1086	//Ȩ����Ϣ�б�		List

//�����豸��Ի�����ԴID��������������������������������������������������������
#define IDC_EDIT_DIR_NAME               1213	//�豸������		Edit
#define IDC_LIST_DEVICE_ALL             1214	//�豸��Ա�б�		List
#define IDC_BTN_DIR_CREATE_OK           1216	//ȷ�������豸��	Button
#define IDC_BTN_DIR_CREATE_CANCEL       1215	//ȡ�������豸��	Button
#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//�����豸�Ի�����ԴID------------------------------------------------------
#define IDC_COMBO_EQP_TYPE              1204	//�豸����			Combox
#define IDC_COMBO_CATALOG               1210	//�豸������		Combox
#define IDC_IPADDRESS_SELF              1206	//IP��ַ			IpAddrCtrl
//#define IDC_EDIT_ALIAS_SELF             1207	//�豸����			Edit
#define IDC_BTN_EQUIP_CANCEL            1208	//ȡ������			Button
#define IDC_BTN_EQUIP_ADD               1209	//����				Button
//#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//���Ӹ澯֪ʶ��Ի�����ԴID--------------------------------------------------
#define IDC_EDIT_ALARMCODE              1264	//�澯��			Edit
#define IDC_EDIT_LEVEL                  1354	//�澯����			Edit
#define IDC_EDIT_DESCRIPTION            1265	//�澯����			Edit
#define IDC_COMBO_OBJTYPE               1355	//�澯��������		Combox
#define IDC_EDIT_PROVIDER               1267	//�����ṩ��		Edit
#define IDC_EDIT_MEMO                   1268	//��ע				Edit
#define IDC_LIST_ALARM_CAUSE            1348	//�澯ԭ��			List
#define IDC_LIST_ALARM_SOLUTION         1347	//�������			List
#define IDC_EDIT_CAUSE_SOLUTION         1350	//�澯ԭ��򷽰�	Edit
#define IDC_BTN_INPUT                   1353	//ȷ������һ��ԭ��򷽰�	Button
#define IDC_BTN_ADD                     1281	//ȷ������һ��֪ʶ��Button
//#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//��Աѡ��Ի�����ԴID��������������������������������������������������������
#define IDC_LIST_MEMBER_ALL             1090	//�豸��Ա�б�		List
#define IDC_LIST_MEMBER_NEW             1091	//��ѡ�豸��Ա�б�	List
#define IDC_BTN_MEMBER_ALL_ADD_ALL      1094	// >>				Button
#define IDC_BTN_MEMBER_ALL_ADD_ONE      1095	// >				Button
#define IDC_BTN_MEMBER_NEW_DEL_ONE      1096	// <				Button
#define IDC_BTN_MEMBER_NEW_DEL_ALL      1097	// <<				Button
#define IDC_BTN_MEMBER_MODIFY_OK        1092	//ȷ���޸�			Button
#define IDC_BTN_MEMBER_MODIFY_CANCEL    1093	//ȡ���޸�			Button
//#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//�������öԻ�����ԴID��������������������������������������������������������
#define IDC_EDIT_1                      1264	//					Edit
#define IDC_EDIT_2                      1265	//					Edit
#define IDC_EDIT_3                      1266	//					Edit
#define IDC_EDIT_4                      1267	//					Edit
#define IDC_EDIT_5                      1268	//					Edit
#define IDC_EDIT_6                      1269	//					Edit
#define IDC_EDIT_7                      1270	//					Edit
#define IDC_EDIT_8                      1271	//					Edit
//#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//��·����Ping�Ի�����ԴID������������������������������������������������
#define IDC_EDIT_TIMES                  1247	//����				Edit
#define IDC_EDIT_PACKAGE                1248	//����С			Edit
#define IDC_BTN_PING_PROCESS            1155	//��ʼ����			Button
#define IDC_BTN_PING_STOP               1158	//�жϲ���			Button
#define IDC_BTN_PING_CANCEL             1156	//ȡ������			Button
//#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//�豸����Ȩ����Ϣ���öԻ�����ԴID����������������������������������������
#define IDC_LIST_EQUIP_PRIVILEGE        1197	//�豸Ȩ���б�		CheckBoxList
//#define IDC_LIST_DEVICE_ALL             1214	//�豸��Ա�б�		List
#define IDC_BTN_PRIV_SET_OK             1195	//ȷ������Ȩ����Ϣ	Button
#define IDC_BTN_PRIV_SET_CANCEL         1196	//ȡ������Ȩ����Ϣ	Button
//#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//�޸�����Ի�����ԴID����������������������������������������������������������
#define IDC_EDIT_PWD_OLD                1198	//������			Edit
#define IDC_EDIT_PWD_NEW                1199	//������			Edit
#define IDC_EDIT_PWD_CONFIRM            1200	//����ȷ��			Edit
#define IDC_BTN_PWD_CHANGE              1201	//ȷ���޸�����		Button
#define IDC_BTN_PWD_CANCEL              1202	//ȡ���޸�����		Button
//#define IDC_CLOSE_BTN                   1361	//�رմ���			Button

//�豸�����������������Ϣ��ԴID������������������������������������������������
#define IDC_LIST_RESULT                 1389    //�豸�������      List
#define IDC_TEXT_EDIT                   1375    //WarnDlg           Text

//�豸����ҳ����������Ϣ��ԴID������������������������������������������������
#define IDC_EDIT_CFGVER                 1030	//���ð汾��		Edit
#define IDC_EDIT_MCUID                  1031	//mcu���			Edit
#define IDC_EDIT_MCUALIAS               1032	//mcu����			Edit
#define IDC_EDIT_E164NUM                1033	//mcu��E164��		Edit
#define IDC_COMBO_NEEDBAS               1343	//����ʱ�Ƿ���Ҫ��������	Combox

//�豸����ҳ��������������ԴID������������������������������������������������
#define IDC_EDIT_LAYER                  1265	//���				Edit
#define IDC_EDIT_SLOT                   1266	//�ۺ�				Edit
#define IDC_COMBO_BOARDTYPE             1357	//������			Combox
#define IDC_IPADDRESS_IP                1287	//IP��ַ			IpAddrCtrl
#define IDC_BTN_CONFIRM                 1259	//ȷ���޸�			Button
#define IDC_BTN_CANCEL                  1260	//ȡ���޸�			Button
#define IDC_LIST_BOARD                  1021	//�����б�			List

//�豸����ҳ��������������ԴID������������������������������������������������
#define IDC_GK_IP                       1290	//GK��IP��ַ		IpAddrCtrl
#define IDC_MULTICAST_IP                1291	//mcu�鲥ip			IpAddrCtrl
#define IDC_EDIT_RECVSTARTPORT          1034	//����������ʼ�˿�	Edit
#define IDC_EDIT_MULTICASTPORT          1033	//mcu�鲥�˿�		Edit
#define IDC_CHECK_FW                    1048	//�Ƿ�ʹ��mpcת��	CheckBox
#define IDC_CHECK_PS                    1049	//�Ƿ�ʹ��mpc����Э��ջ	CheckBox
#define IDC_LIST_TRAPRECV               1020	//����trap�������б�	List
//#define IDC_IPADDRESS_IP                1287	//IP��ַ			IpAddrCtrl
#define IDC_EDIT_COMMUNITY              1264	//community			Edit
//#define IDC_BTN_CONFIRM                 1259	//ȷ���޸�			Button
//#define IDC_BTN_CANCEL                  1260	//ȡ���޸�			Button

//�豸����ҳ��������ͬ��������ԴID������������������������������������������������
#define IDC_COMBO_NETSYN_MODE           1342	//����ͬ��ģʽ				Combox
#define IDC_EDIT_NETSYNCDTSLOT          1033	//ͬ������ʱʹ�õ�DT���	Edit
#define IDC_EDIT_NETSYNCE1INDEX         1034	//ͬ������ʱʹ�õ�E1���	Edit

//�豸����ҳ������������1��ԴID������������������������������������������������
#define IDC_LIST_MIXER                  1022	//������			List
#define IDC_LIST_RECORDER               1023	//¼/�����			List
#define IDC_LIST_TVWALL                 1024	//����ǽ			List

//�豸����ҳ������������2��ԴID������������������������������������������������
#define IDC_EDIT_DCSERVERID             1039	//���ݻ�����������Edit
#define IDC_LIST_BAS                    1025	//����������		List
#define IDC_LIST_VMP                    1026	//����ϳ���		List

//�豸����ҳ�������ش�������ԴID������������������������������������������������
#define IDC_EDIT_PRSID                  1036	//�豸���			Edit
#define IDC_EDIT_PRSMCUSTARTPORT        1037	//mcu��ʼ�˿ں�		Edit
#define IDC_EDIT_PRSSWITCHBRDID         1040	//��������		Edit
#define IDC_EDIT_PRSALIAS               1039	//����				Edit
#define IDC_EDIT_PRSRUNNINGBRDID        1045	//���а�������		Edit
#define IDC_EDIT_PRSSTARTPORT           1038	//Prs��ʼ�˿ں�		Edit
#define IDC_EDIT_PRSFIRSTTIMESPAN       1041	//��һ�ش�����	Edit
#define IDC_EDIT_PRSSECONDTIMESPAN2     1044	//�ڶ��ش�����	Edit
#define IDC_EDIT_PRSTHIRDTIMESPAN3      1042	//�����ش�����	Edit
#define IDC_EDIT_PRSREJECTTIMESPAN4     1043	//ʱ����			Edit

//�澯����
#define IDC_LIST_ALARM_CODE             1165	//�澯�����		ListBox
//#define IDC_CHECK_ALARM_LEVEL_1         1035	//�澯����1��		CheckBox
//#define IDC_CHECK_ALARM_LEVEL_2         1036	//�澯����2��		CheckBox
//#define IDC_CHECK_ALARM_LEVEL_3         1037	//�澯����3��		CheckBox

//mcu�豸����ID
//���˳��Ϊ���¶���: 10001, 10002, 10003, 10004
#define IDC_BASIC_LAYER0				10000	//��Ż�id
//�ۺ�Ϊ�������: 1001, 1002, ..., 1017
#define IDC_BASIC_SLOT0					1000	//�ۺŻ�id

//�Ի�����ԴID����������������������������������������������������������
#define IDD_ABOUTBOX                    100		//about				Dlg
#define IDD_DLG_ALARM_SOLUTION          192		//�澯�������		Dlg
#define IDD_DLG_CONFINFO                193		//������Ϣ			Dlg
#define IDD_DLG_DEVICE_DIR_CREATE       170		//�豸�鴴��		Dlg
#define IDD_DLG_DEVICE_PROPS_BASIC      178		//�豸��������		Dlg
#define IDD_DLG_DIR_PROPS_BASIC         172		//�ļ��л�������	Dlg
#define IDD_DLG_EQUIP_ADD               168		//�����豸			Dlg
#define IDD_DLG_FTP_PROGRESS            150		//Ftp�ϴ�/����		Dlg
#define IDD_DLG_KNOWLEDGE_BASE_ADD      197		//�澯֪ʶ�����	Dlg
#define IDD_DLG_MEMBER_SEL              141		//��Ա����			Dlg
#define IDD_DLG_PERI_CFG                201		//��������			Dlg
#define IDD_DLG_PING                    151		//��·����			Dlg
#define IDD_DLG_PRIVILEGE_INFO          160		//Ȩ����Ϣ����		Dlg
#define IDD_DLG_PWD_CHANGE              161		//�޸�����			Dlg
#define IDD_DSI_E1_CFG                  196		//Dsi_E1����		Dlg
#define IDD_NMCALARMQUERY_FORM          104		//�澯��ѯ����		Dlg
#define IDD_NMCGROUP_FORM               115		//�û���			Dlg
#define IDD_NMCLOGQUERY_FORM            106		//��־��ѯ����		Dlg
#define IDD_NMCUSER_FORM                101		//�û���Ϣ			Dlg
#define IDD_NMCWELCOMEVIEW_FORM         117		//��¼				Dlg
#define IDD_PAGE_ALARM_FILTER_CODE      152		//�澯���ˣ��澯��	Dlg
#define IDD_PAGE_ALARM_FILTER_LEVEL     153		//�澯���ˣ��澯����Dlg
#define IDD_PAGE_ALARM_FILTER_OBJECT    154		//�澯���ˣ��澯����Dlg
#define IDD_PROPPAGE_PERICFG2           183		//�豸���ԣ���������2		Dlg
#define IDD_PROPPAGE_BASEINFO           184		//�豸���ԣ�������Ϣ		Dlg
#define IDD_PROPPAGE_BOARDCFG           185		//�豸���ԣ���������		Dlg
#define IDD_PROPPAGE_NETCFG             186		//�豸���ԣ���������		Dlg
#define IDD_PROPPAGE_NETSYNCCFG         187		//�豸���ԣ�����ͬ��		Dlg
#define IDD_PROPPAGE_PERICFG1           188		//�豸���ԣ���������1
#define IDD_PROPPAGE_PRSCFG             189		//�豸���ԣ������ش�����	Dlg
#define IDD_WARN                        307		//��Ϣ��ʾ��				Dlg

//����Ϊ�˵���������
//��¼��˵�ID���壭��������������������������������������������������������������
#define MENU_SYS						(u8)0		//ϵͳ
#define MENU_CM							(u8)1		//���ù���
#define MENU_FM							(u8)2		//���Ϲ���
#define	MENU_SM							(u8)3		//��ȫ����

//ϵͳ
#define UI_SYS_LOGOFF					(u8)0		//ע��
                                                    //1-Separator
#define UI_APP_EXIT                     (u8)2     //�˳�

//���ù���
#define UI_CM_DEVICE_ADD				(u8)0		//�����豸
#define UI_CM_DIR_CREATE				(u8)1		//�����豸��
													//2-Separator
#define UI_CM_DEVICE_DIR				(u8)3		//�豸Ŀ¼��

//���Ϲ���
#define UI_FM_CUR_ALARM					(u8)0		//��ǰ�澯
#define UI_FM_HIS_ALARM					(u8)1		//��ʷ�澯
													//2-Separator
#define UI_FM_KB_ALARM					(u8)3		//�澯֪ʶ��
#define UI_FM_FILTER_ALARM				(u8)4		//�澯����
													//5-Separator
#define UI_FM_MOCK_ALARM				(u8)6		//���ܹ���ͼ

//��ȫ����
#define UI_SM_USER						(u8)0		//�û�����
#define UI_SM_LOG						(u8)1		//������־����
													//2-Separator
#define UI_SM_MODIFY_PWD				(u8)3		//�޸Ŀ���
													//4-Separator
#define UI_SM_CONFINFO					(u8)5		//MCU������־��Ϣ

//�豸�����˵�ID���壭������������������������������������������������
#define UI_DEVICE_MOCK					(u8)0		//���ܹ���ͼ
													//1-Separator
#define UI_DEVICE_SNMP					(u8)2		//Snmp����
#define UI_DEVICE_SYNCTIME				(u8)3		//ʱ��ͬ��
													//4-Separator
#define UI_DEVICE_RESET					(u8)5		//Զ�̸�λ
													//6-separator
#define UI_DEVICE_SYNCALARM				(u8)7		//�澯ͬ��
#define UI_DEVICE_CURALARM				(u8)8		//��ǰ�澯
#define UI_DEVICE_HISALARM				(u8)9		//��ʷ�澯
													//10-separator
#define UI_DEVICE_DOWNLOAD				(u8)11	//�ļ�����
#define UI_DEVICE_UPLOAD				(u8)12	//�ļ��ϴ�
#define UI_DEVICE_UPLOADFILES           (u8)12    //�ļ�װ��
													//13-separator
#define UI_DEVICE_PING					(u8)14	//��·����
													//15-separator
#define UI_DEVICE_DEL					(u8)16	//ɾ��
													//17-separator
#define UI_DEVICE_DIAGNOSE				(u8)18	//�澯���
#define UI_DEVICE_PROS					(u8)19	//�豸����

//�豸����ڵ�����˵�ID���壭����������������������������������
#define UI_DIRROOT_OPEN                 (u8)0     //��
                                                    //1-separator
#define UI_DIRROOT_CREATE               (u8)2     //�����豸��
                                                    //3-separator
#define UI_DIRROOT_REFRESH              (u8)4     //�豸ˢ��
                                                    //5-separator
#define UI_DIRROOT_MEMBERADD            (u8)6     //�����豸

//�豸������˵�ID���壭����������������������������������������
#define UI_DIR_DISPALL					(u8)0		//��ʾ�����豸
#define UI_DIR_OPEN						(u8)1		//��
													//2-Separator
#define UI_DIR_CREATE					(u8)3		//�����豸��
#define UI_DIR_DEL						(u8)4		//ɾ���豸��
													//5-separator
#define UI_DIR_ASSIGN					(u8)6		//�����豸
#define UI_DIR_UNASSIGN					(u8)7		//ȡ������
													//8-separator
#define UI_DIR_REFRESH					(u8)9		//�豸ˢ��
#define UI_DIR_ARRANGE                  (u8)10    //����ͼ��
													//11-separator
#define UI_DIR_MEMBERADD				(u8)12	//�����豸
#define UI_DIR_PROS						(u8)13	//�豸������

//�豸����ڵ��Ӧ���豸�б�ĵ����˵�
#define UI_EQPLIST_ROOT_ADD          (u8)0     //�����豸
#define UI_EQPLIST_ROOT_REFRESH      (u8)1     //ˢ���豸
#define UI_EQPLIST_ROOT_ARRANGE      (u8)2     //����ͼ��

//�豸���Ӧ���豸�б�ĵ����˵�
#define UI_EQPLIST_SHOWALL          (u8)0     //��ʾ�����豸
                                                //1
#define UI_EQPLIST_CREATE           (u8)2     //�����豸��
#define UI_EQPLIST_DEL              (u8)3     //ɾ���豸��
                                                //4
#define UI_EQPLIST_ASSIGN           (u8)5     //�����豸
#define UI_EQPLIST_CANCEL           (u8)6     //ȡ���豸
                                                //7
#define UI_EQPLIST_REFRESH          (u8)8     //�豸ˢ��
#define UI_EQPLIST_ARRANGE          (u8)9     //����ͼ��
                                                //10
#define UI_EQPLIST_ADD              (u8)11    //�����豸
#define UI_EQPLIST_PROS             (u8)12    //�豸������

//�û��������û������˵�����������������������������������������
#define UI_USER_DEL                     (u8)0     //ɾ��
                                                    //1
#define UI_USER_ADDPRIV                 (u8)2     //����Ȩ����
#define UI_USER_DELPRIV                 (u8)3     //����Ȩ����
                                                    //4
#define UI_USER_PROP                    (u8)5     //����

//�û�������������˵�������������������������������������������
#define UI_USERGROUP_DEL                (u8)0     //ɾ��
                                                    //1
#define UI_USERGROUP_ADDMEMBER          (u8)2     //��ӳ�Ա
#define UI_USERGROUP_DELMEMBER          (u8)3     //ɾ����Ա
                                                    //4
#define UI_USERGROUP_PRIVSET            (u8)5     //����Ȩ��
                                                    //6
#define UI_USERGROUP_PROP               (u8)7     //����

//��������˵�ID���壭������������������������������������������
#define UI_BOARD_REBOOT					(u8)0		//������
#define UI_BOARD_SYNCTIME				(u8)1		//ʱ��ͬ��
#define UI_BOARD_CODETEST				(u8)2		//�������
#define UI_BOARD_SELFTEST				(u8)3		//�����Լ�
#define UI_BOARD_LINKCFG				(u8)4		//��·����
#define UI_BOARD_DOWNLOAD				(u8)5		//�ļ�����
#define UI_BOARD_UPLOAD					(u8)6		//�ļ��ϴ�
													//7-separator
#define UI_BOARD_REFRESH				(u8)8		//ˢ��

//mcu�豸�����޸ģ��������ý���trap�ķ������б�˵�����
#define RCVTRAP_ADD						(u8)0
#define RCVTRAP_MODIFY					(u8)1
#define RCVTRAP_DEL						(u8)2

//mcu�豸�����޸ģ��������ò˵�����
#define BRDCFG_ADD						(u8)0
#define BRDCFG_MODIFY					(u8)1
#define BRDCFG_DEL						(u8)2

//mcu�豸�����޸ģ��������ò˵�����
#define PERICFG_ADD						(u8)0
#define PERICFG_MODIFY					(u8)1
#define PERICFG_DEL						(u8)2



//����õ��ľ���Ϸ���, ��ӡ�����������ļ���������
#define CHECK_HANDLE(hWnd)															\
	if(hWnd == NULL)																\
	{																				\
		CString strName = __FILE__;													\
		s32 nLeft = strName.ReverseFind('\\');										\
		TRACE("�ļ�%s�е�%d��---�ؼ�����Ƿ�!\n", strName.Mid(nLeft+1), __LINE__);	\
		return FALSE;																\
	}

//�ȴ�500ms
#define SLEEP_500	m_bOprDelay ? Sleep(500) : NULL

//�ȴ�1s
#define SLEEP_1000	m_bOprDelay ? Sleep(1000) : NULL

//Ϊ��ʵ�ֽ�����������������������ʱ
#define SLEEP_SYS	Sleep(500)

//Ӧ�ó�����
#define APP_TITLE_NAME	_T("���ܿͻ���")
#define APP_EXE_NAME	_T("NmsClient.exe")

//ϵͳĬ���û�����
#define DEF_USER		_T("admin")
#define DEF_GROUP		_T("Administrators")

//���嵱ǰ���ڲ�������id
#define POS_INVALID				(u8)0	//�Ƿ�ֵ
#define POS_HISALARM			(u8)1 //��ʷ�澯
#define POS_USER				(u8)2 //�û�����
#define POS_LOG					(u8)3 //��־����
#define POS_EQP					(u8)4 //�豸����
#define POS_CURALARM			(u8)5	//��ǰ�澯
#define POS_ALARMKB				(u8)6	//�澯֪ʶ��
#define POS_MOCK				(u8)7	//���ܹ���ͼ

//  xsl [11/25/2004] ��Ȩ�����ú궨��--�����ö���Ȩ�޽������ȡ"��"
#define GROUP_PRIV_SNMP			0x0001	//SNMP����
#define GROUP_PRIV_SYNTIME		0x0002	//ʱ��ͬ��
#define GROUP_PRIV_DOWNLOAD		0x0004	//�ļ�����
#define GROUP_PRIV_UPLOAD		0x0008	//�ļ��ϴ�
#define GROUP_PRIV_REMOTECTRL	0x0010	//Զ�̿���
#define GROUP_PRIV_SYNALARM		0x0020	//�澯ͬ��

//�����豸ʱ���Ͷ���
//�豸����
#define EQPADD_TYPE_MCU			(u8)0	//MCU
#define EQPADD_TYPE_MT			(u8)1	//�ն�
//�ն��豸������
#define EQPADD_SUBTYPE_PCMT         (u8)0	//�����ն�
#define EQPADD_SUBTYPE_8010         (u8)1	//Ƕ��ʽ8010
#define EQPADD_SUBTYPE_8010C        (u8)2	//Ƕ��ʽ8010C
#define EQPADD_SUBTYPE_IMT          (u8)3	//Ƕ���ն�IMT
#define EQPADD_SUBTYPE_8010A        (u8)4   //Ƕ��ʽ8010A
#define EQPADD_SYBTYPE_8010APLUS    (u8)5   //Ƕ��ʽ8010A+

//mcu�豸������
#define EQPADD_SUBTYPE_MCU8000	(u8)0
#define EQPADD_SUBTYPE_MCU8000B	(u8)1

//MCU��������ʱҳ����������
#define MCUCFG_BASICINFO		(u8)0	//������Ϣ
#define MCUCFG_NET				(u8)1	//��������	
#define MCUCFG_BOARD			(u8)2	//��������	
#define MCUCFG_PERI1			(u8)3	//��������1
#define MCUCFG_PERI2			(u8)4	//��������2
#define MCUCFG_PRS				(u8)5	//���ش�����
#define MCUCFG_NETSYNC			(u8)6	//��ͬ������

//�澯(��־)����(�ָ�)ʱ�����Ͷ���
#define DT_ALLTIME				(u8)0	//����ʱ��
#define DT_LATEST_MONTH			(u8)1	//ǰN��	
#define DT_LATEST_DAY			(u8)2	//ǰN��
#define DT_BETWEEN				(u8)3	//����


/* MCU�澯�������� */
#define ALARMOBJ_MCU						(u8)1
#define ALARMOBJ_MCU_BOARD					(u8)11
#define ALARMOBJ_MCU_LINK					(u8)12
#define ALARMOBJ_MCU_TASK					(u8)13
#define ALARMOBJ_MCU_SDH					(u8)14
#define ALARMOBJ_MCU_POWER					(u8)15
#define ALARMOBJ_MCU_MODULE					(u8)16
#define ALARMOBJ_MCU_SOFTWARE				(u8)17
#define ALARMOBJ_MCU_BRD_FAN				(u8)18

/* MT�澯�������� */
#define ALARMOBJ_MT_BASE				(u8)128
#define ALARMOBJ_MT                     (u8)(ALARMOBJ_MT_BASE + 1)
#define ALARMOBJ_MT_E1                  (u8)(ALARMOBJ_MT_BASE + 11)
#define ALARMOBJ_MT_MAP					(u8)(ALARMOBJ_MT_BASE + 12)
#define ALARMOBJ_MT_CCI					(u8)(ALARMOBJ_MT_BASE + 13)
#define ALARMOBJ_MT_STREAM				(u8)(ALARMOBJ_MT_BASE + 14)
#define ALARMOBJ_MT_ETHERNET			(u8)(ALARMOBJ_MT_BASE + 15)
#define ALARMOBJ_MT_TASK				(u8)(ALARMOBJ_MT_BASE + 16)
#define ALARMOBJ_MT_FAN					(u8)(ALARMOBJ_MT_BASE + 17)
#define ALARMOBJ_MT_V35					(u8)(ALARMOBJ_MT_BASE + 18)

typedef struct tagSingleBoard
{
    CString csMcuName;      //�豸��
    u8      bySlot;         //�ۺ�
    u8      bylayer;        //���
}TSingleBoard, *PTSingleBoard;

//��ʷ�澯��ѯ�����ṹ����
typedef struct tagHisAlarmCondition
{	
	CString csAlarmType;				//�澯��𣭸澯����Ӧ�ĸ澯����	
	u32     dwEqpId;						//�豸��ţ�Ĭ��Ϊ0	
	u8      byAlarmLevel;					//�澯����001Ϊһ���澯��010Ϊ�����澯��100Ϊ�����澯

	//�澯����ʱ��	
	u8      byGenType;					//���ͣ������涨�� 	
	u8      byGenMonth;					//ǰn��	
	u8      byGenDay;						//ǰn��	
	SYSTEMTIME timeGenBgn;				//����
	SYSTEMTIME timeGenEnd;
	
	//�澯�ָ�ʱ��	
	u8      byResType;					//���ͣ������涨��	
	u8      byResMonth;					//ǰn��	
	u8      byResDay;						//ǰn��	
	SYSTEMTIME timeResBgn;				//����
	SYSTEMTIME timeResEnd;	

	//Ĭ��ֵ
	tagHisAlarmCondition()
	{
		csAlarmType = "���и澯";
		dwEqpId = 0;
		byAlarmLevel = 7;
		byGenType = DT_ALLTIME;
		byGenMonth = 0;
		byGenDay = 0;
		memset(&timeGenBgn, 0, sizeof(SYSTEMTIME));
		memset(&timeGenEnd, 0, sizeof(SYSTEMTIME));
		byResType = DT_ALLTIME;
		byResMonth = 0;
		byResDay = 0;
		memset(&timeResBgn, 0, sizeof(SYSTEMTIME));
		memset(&timeResEnd, 0, sizeof(SYSTEMTIME));	
	};

}THisAlarmCondition;

//��־��ѯ�ṹ����
typedef struct tagLogCondition
{
	CString csLogonName;				//��¼�û���	
	BOOL32	bSelAll;					//�Ƿ�ȫѡ
    vector<s32> vecIndex;                //����������������0��ʼ��bSelAllΪFALSEʱ��Ч��
	u8      byOprTimeType;				//����ʱ������-�����涨��	
	u8      byDay;						//ǰn��	
	u8      byMonth;					//ǰn��	
	SYSTEMTIME	timeOprBgn;				//������ʼʱ��	
	SYSTEMTIME	timeOprEnd;				//��������ʱ�� 	
	CString csOprObj;					//��������	
	CString csObjName;					//������������	
	BOOL32	bCheckObjID;				//����������CheckButton	
	u32	    dwObjID;					//��������id
	BOOL32  bSuccess;					//����������ɹ�	
	BOOL32  bFail;						//ʧ��

	//Ĭ��ֵ
	tagLogCondition()
	{
		csLogonName = "";
		bSelAll = FALSE;
		byOprTimeType = DT_ALLTIME;
		byDay = 0; 
		byMonth = 0;
		memset(&timeOprBgn, 0, sizeof(SYSTEMTIME));	
		memset(&timeOprEnd, 0, sizeof(SYSTEMTIME));			
		csOprObj = "";
		csObjName = "";
		bCheckObjID = FALSE;
		dwObjID = 0;
		bSuccess = FALSE;
		bFail = FALSE;
        vecIndex.clear();
	};

}TLogCondition;

//mcu�豸���ã��������Ͷ���
#define PERI_MIXER			(u8)0	//������
#define PERI_REC			(u8)1	//¼�����
#define PERI_TW				(u8)2	//����ǽ
#define PERI_BAS			(u8)3	//����������
#define PERI_VMP			(u8)4	//����ϳ���

//mcu�豸���ã��������ã�����trap�ķ�������Ϣ
typedef struct tagRcvTrapSvr
{
	CString csIP;
	CString csCommunity;
    CString csModifyIP;   //Ҫ�޸ĵ�IP  [zhuyr][4/27/2005]
}TRcvTrapSvr;

//mcu�豸���ã�����������Ϣ
typedef struct tagBrdCfg
{
	u16     wIndex;						//������
	u16     wLayer;						//���
	u16     wSlot;						//�ۺ�
	CString csType;						//������
	CString csIP;						//����IP

}TBrdCfg;

//mcu�豸���ã�������������Ϣ
typedef struct tagMixerCfg
{
	u8  byNum;						//���
	u32 dwMcuBgnPort;				//mcu��ʼ�˿ں�
	u32 dwSwitchIndex;				//����������
	CString csAlias;				//����
	u32 dwRunIndex;					//���а�����
	u32 dwMixerBgnPort;				//��������ʼ�˿ں�
	u32 dwMaxGrpNum;				//ÿ��map����������
	CString strMapId;				//map���

}TMixerCfg;

//mcu�豸���ã�¼���������Ϣ
typedef struct tagRecCfg
{
	u8  byNum;						//���
	u32 dwMcuBgnPort;				//mcu��ʼ�˿ں�
	u32 dwSwitchIndex;				//����������
	CString csAlias;				//����
	CString csIP;					//ip��ַ
	u32 dwRecBgnPort;				//¼�������ʼ�˿ں�
	u32 dwRecChnn;					//¼��ͨ����
	u32 dwPlayChnn;					//����ͨ����
	
}TRecCfg;

//mcu�豸���ã�����ǽ������Ϣ
typedef struct tagTVWallCfg
{
	u8  byNum;						//���
	CString csAlias;				//����
	u32 dwRunIndex;					//���а�����
	u32 dwTWBgnPort;				//����ǽ��ʼ�˿ں�
	u32 dwSplitType;				//�ָʽ
	u32 dwSplitNum;					//�ָ����
    CString strMapId;               //map���

}TTVWallCfg;

//mcu�豸���ã�����������������Ϣ
typedef struct tagBasVmpCfg
{
	u8 byNum;						//���
	u32 dwMcuBgnPort;				//mcu��ʼ�˿�
	u32 dwSwitchIndex;				//����������
	CString csAlias;				//����
	u32 dwRunIndex;					//���а�����
	u32 dwBgnPort;					//��ʼ�˿�
	CString strMapId;				//map���

}TBasVmpCfg;

//mcu�豸���ã�����ϳ���������Ϣ
typedef struct tagVmpCfg
{
	u8 byNum;						//���
	u32 dwMcuBgnPort;				//mcu��ʼ�˿�
	u32 dwSwitchIndex;				//����������
	CString csAlias;				//����
	u32 dwRunIndex;					//���а�����
	u32 dwBgnPort;					//��ʼ�˿�
    u32 dwCount;                    //����·��
	CString strMapId;				//map���

}TVmpCfg;

//mcu������Ϣ����
typedef struct tagMcuCfgInfo
{
	//������Ϣ����	
	CString	csCfgVer;					//���ð汾��	
	CString csMcuId;					//mcu���	
	CString csMcuAlias;					//mcu����	
	CString csMcuE164;					//mcu��E164��	
	BOOL32  bNeedBas;					//����ʱ�Ƿ���Ҫ��������

	//��������	
	CString csNetGkIP;					//Gk��ip��ַ	
	CString csNetMcuMcIP;				//mcu�鲥��ַ	
	u32     dwNetRcvBgnPort;				//����������ʼ�˿�	
	u32     dwNetMcuMcPort;			    	//mcu�鲥�˿�	
	BOOL32 bNetMpcTrans;					//�Ƿ�ʹ��mpcת������	
	BOOL32 bNetMpcPS;						//�Ƿ�ʹ��mpc����Э��ջ	
	vector<TRcvTrapSvr> vtTrapSvrAdd;	//���ӵ�trap������	
	vector<TRcvTrapSvr> vtTrapSvrModify;//�޸ĵ�trap������	
	vector<CString> vtTrapSvrDel;		//ɾ����trap������ - ����ip��ַɾ��

	//��������	
	vector<TBrdCfg>		vtBrdCfgAdd;	//���ӵ���	
	vector<TBrdCfg>		vtBrdCfgModify;	//�޸ĵ���	
	vector<u16>		    vtBrdCfgDel;	//ɾ������ - ����������ɾ��

	//��������	
	vector<TMixerCfg>	vtMixerAdd;		//�������ֻ�����	
	vector<TMixerCfg>	vtMixerModify;	//�޸����ֻ�����	
	vector<u8>	    	vtMixerDel;		//ɾ�����ֻ����� �� ���ݱ��ɾ��
	
	vector<TRecCfg>		vtRecAdd;		//����¼/�����
	vector<TRecCfg>		vtRecModify;	//�޸�¼/�����	
	vector<u8>	    	vtRecDel;		//ɾ��¼/����� - ���ݱ��ɾ��
	
	vector<TTVWallCfg>	vtTWAdd;		//���ӵ���ǽ	
	vector<TTVWallCfg>	vtTWModify;		//�޸ĵ���ǽ	
	vector<u8>	    	vtTWDel;		//ɾ������ǽ - ���ݱ��ɾ��	
	
	vector<TBasVmpCfg>	vtBasAdd;		//��������������		
	vector<TBasVmpCfg>	vtBasModify;	//�޸�����������	
	vector<u8>	    	vtBasDel;		//ɾ������������ - ���ݱ��ɾ��
	
	vector<TVmpCfg>	    vtVmpAdd;		//���ӻ���ϳ���	
	vector<TVmpCfg>	    vtVmpModify;	//�޸Ļ���ϳ���	
	vector<u8>	    	vtVmpDel;		//ɾ������ϳ��������ݱ��ɾ��

	//���ش�����	
	u32     dwPrsNum;					//�豸���		
	u32     dwPrsMcuBgnPort;			//mcu��ʼ�˿ں�	
	u32     dwPrsSwitchIndex;			//��������	
	CString csPrsAlias;					//����	
	u32     dwPrsRunIndex;				//���а�����	
	u32     dwPrsBgnPort;				//Prs��ʼ�˿ں�	
	u32     dwPrsFstTime;				//��1�ش�����	
	u32     dwPrsSndTime;				//��2�ش�����	
	u32     dwPrsThdTime;				//��3�ش�����	
	u32     dwPrsTimeSpan;				//���ڶ�����ʱ����

	//��ͬ������	
	CString csNetSyncMode;				//ͬ��ģʽ	
	u8	    byNetSyncDTNum;				//��ͬ������ʱʹ�õ�DT���	
	u8	    byNetSyncE1Num;				//��ͬ������ʱʹ�õ�E1���
	
}TMcuCfgInfo;

//�û���Ȩ������
typedef struct tagEqpPrivSet
{
	CString csEqpIP;					//�豸ip��ַ
	u32  dwPriv;						//Ȩ��
}TEqpPrivSet;

typedef struct tagGroupPriv
{
	CString csGroupName;
	vector<TEqpPrivSet> vtEqpPriv;

}TGroupPriv;

//�����豸
typedef struct tagEqpAdd
{
	u8  byEqpType;						//�豸����
	u8  bySubType;						//�豸������
	u32 dwIP;							//�豸ip��ַ

}TEqpAdd;

//��·����
typedef struct tagPingTest
{
	CString csEqpName;					//�豸����
	u16	wTimes;					    	//����
	u16	wPackSize;				    	//����С

}TPingTest;

//�豸�ļ��ϴ�/����
typedef struct tagFileUpDown
{
	CString csEqpName;					//�豸����
	CString csFileName;					//�ļ���

}TFileUpDown;

//�û�����/ȡ��Ȩ����, Ȩ�������/ɾ���û���Ա
typedef struct tagUserWithGroup
{
	vector<CString> vtArray;		//Ȩ��������û�����
	CString csName;					//�û�����Ȩ������
	
}TUserWithGroup;

//�޸ĵ�ǰ�û�����
typedef struct tagModifyUserPwd
{
	CString csOldPwd;
	CString csNewPwd;
    CString csNewComPwd;
	
}TModifyUserPwd;

//�澯����
typedef struct tagEqpAlarmFilter
{
	u8  byLevel;
	vector<CString> vtCode;
	
}TEqpAlarmFilter;

typedef struct tagAlarmKBCauseTest
{
	u32     m_dwSerialNo;  // ���к�
    CString m_szCase;
}TAlarmKBCauseTest;

//�澯֪ʶ��
typedef struct tagAlarmKB
{
	u32     m_dwAlarmCode;  // �澯��
	u8      m_byLevel;	    // �澯����
	u8      m_byObjType;	// �澯��������(ALARMOBJ_MCU, ALARMOBJ_MT��)
	CString  m_szDescription;       //����
	CString  m_szProvider;          //�ṩ��
	CString  m_szMemo;              //��ע
    vector<CString> m_vecCause;     //�澯ԭ��
    vector<CString> m_vecSolution;  //�澯�������
    //����Ϊ�޸�ɾ��
    vector<TAlarmKBCauseTest> m_vecModifyCause;     //�澯ԭ��
    vector<u32> m_vecDelCause;
    vector<TAlarmKBCauseTest> m_vecModifySolution;  //�澯�������
    vector<u32> m_vecDelSolution;
}TAlarmKB;