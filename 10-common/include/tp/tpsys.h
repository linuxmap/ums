#ifndef _h_tpsys_h__
#define _h_tpsys_h__

#include "osp.h"
#include "kdvdef.h"
#include "eventid.h"

typedef BOOL32 BOOL;

#define UMS_ProductID	"UMSTPS"
//#define UMS_VerID		"1.1.6.4.1"
#define UMS_VerID	    "5.2.1.3.0"

#define UMSEP_VER		u8
#define UMS_B1			1
#define UMS_B2			2
#define CNS_B1			3
#define CNS_B2			4

#define CNS_B3			5
#define CNS_B4			6

#define UMS_B3			7
#define UMS_B4			8

#define UMS_UserName	"admin"
#define UMS_PassWord	"kedacomTP"

#define UMS_UserName_New "Keda_User"
#define UMS_PassWord_New "Pwd_Change"

#define UMSSDK_UserName	"umssdk"
#define UMSSDK_PassWord	"kedacomTP"


//aid define
 //ums aid 
#define AID_UMSDB_APP				AID_TP_BGN + 1
#define AID_UMSSERVER_APP			AID_TP_BGN + 2
#define AID_UMSSIP_APP				AID_TP_BGN + 3
#define AID_UMSCONFMGR				AID_TP_BGN + 4
#define AID_UMSUE_APP				AID_TP_BGN + 6
#define AID_UMSMEDIADS_APP			AID_TP_BGN + 7
#define AID_UMSEQP_APP				AID_TP_BGN + 8

#define AID_UMSSIPADAPTER_APP		AID_TP_BGN + 9
#define AID_UMSAUDIOMIX_APP			AID_TP_BGN + 10
#define AID_UMSMEDIATRANS_APP		AID_TP_BGN + 11
#define AID_UMSNETBUF_APP			AID_TP_BGN + 12
#define AID_UMSMPC_APP				AID_TP_BGN + 13
#define AID_UMSAGENT_APP			AID_TP_BGN + 14
#define AID_UMSGUARD_APP			AID_TP_BGN + 15
#define AID_UMSAPU2PPOWERPROC_APP	AID_TP_BGN + 26 //apu2������������APP
#define AID_UMSXMPU_APP				AID_TP_BGN + 27 //xmpu����APP


#define AID_UMSBRD_SSN_APP		78	//78 mcu���������ҵ����App  ��Ҫ��MCUͬ��
#define AID_UMSBRD_REG_APP		57  //57 mcu���������ע�ᴦ��App  ��Ҫ��MCUͬ��


//ע�������Э��ջ
#define AID_REGSIPSTACKOUT_APP		AID_TP_BGN + 40
#define AID_REGSIPSTACKIN_APP		AID_TP_BGN + 41

//ע�������APP
#define AID_REGSERVER_APP			AID_TP_BGN + 16

//����������APP
#define AID_UPDATESERVER_APP        AID_TP_BGN + 45

#define AID_CMSUE_APP				AID_TP_BGN + 17

 
#define AID_CMS2UMS_APP             AID_TP_BGN + 18
#define AID_CNC2CNS_APP             AID_TP_BGN + 19
#define AID_CNCADDRBOOK_APP         AID_TP_BGN + 20
#define AID_LOADCMC_APP             AID_TP_BGN + 21
#define AID_UPDATECMC_APP           AID_TP_BGN + 22
#define AID_UMSTOOL2UMS_APP         AID_TP_BGN + 23

//Add by tanxiaodong 2012-11-12.
#define AID_CNSTOOL2CNS_APP         AID_TP_BGN + 24

//Add by wqq 2013-04-12
#define AID_PRODUCETEST_APP         AID_TP_BGN + 25
//End to add.

//cns aid
#define	AID_CN_SYSAPI              AID_TP_BGN + 30
#define	AID_CN_SERVICE		       AID_TP_BGN + 31
#define AID_CN_TERAPI		       AID_TP_BGN + 32
#define AID_CN_UE				   AID_TP_BGN + 33
#define AID_CN_MEDIADS			   AID_TP_BGN + 34
#define AID_CN_DSMGR			   AID_TP_BGN + 35
#define AID_CN_AMix				   AID_TP_BGN + 36
#define	AID_CN_SUBROUTINEMGR	   AID_TP_BGN + 37
#define AID_CN_CALL				   AID_TP_BGN + 38
#define AID_CN_AGENT               AID_TP_BGN + 39
#define AID_CN_GUARD               AID_TP_BGN + 42
#define AID_CN_DEVCTRL             AID_TP_BGN + 43
#define AID_CN_UPDATE			   AID_TP_BGN + 44
#define AID_CN_PRODUCETEST         AID_TP_BGN + 45
#define AID_CN_TVCOMCTRL           AID_TP_BGN + 46

#define AID_UMSBOARD_APP			AID_TP_BGN + 50	//umsboard app
#define AID_MPU2TP_APP				AID_TP_BGN + 51	


#define TELNET_UMS_PORT				2500
#define TELNET_MPC_PORT		        2501

#define TELNET_MEDIATRANS_PORT		2500
#define TELNET_SIPADAPTE_PORT		2501
#define TELNET_NETBUF_PORT			2502

#define TELNET_UMSVMP_PORT			2500

#define TELNET_REG_PORT				2500
#define TELNET_UPDATESERVICE_PORT	2501

//msg define

//time define
#define TP_INTERVAL_TIME_ONE_SECOND		1000
#define TP_INTERVAL_TIME_TWO_SECOND		2000
#define TP_INTERVAL_TIME_THREE_SECOND   3000
#define TP_INTERVAL_TIME_FIVE_SECOND	5000

//LISTIEN PORT
#define UMS_LISTIONPORT_CMS				60000
#define CNS_LISTIONPORT_CMS				60002
#define REGSERVER_LISTIONPORT			60000
#define UPDATE_SERVICE_LISTION		60005 //���������������˿�
#define CNS_PRODUCETEST_LISTION   60010 //�������Է����������˿�

#define TP_DEFAULT_H225_PORT	1720
#define TP_DEFAULT_H245_PORT	1719

#define CNS_SIP_STACK_LISTION_PORT			6000

//mac define
#define TP_REC_FILE_LEN						192 //¼���ļ�����󳤶�
#define TP_MAX_RECORDER_PACK_NUM			16	//¼���ļ��б�ÿ���������

#define TP_UMS_SIP_LISTIEN_PORT	5060			//SIPЭ��ջ�����˿�
#define TP_MAX_CASECADE_NUM		10				//���������
#define TP_MAX_EPID_LEN			64				//����ʱ��ID����ַ�������

#define TP_MAX_LEN_PRODUCT_ID   128				//��ƷID��󳤶� 

#define TP_MAX_ALIAS_LEN_CNC	32				//������󳤶� Ӧ������
#define TP_MAX_ALIAS_LEN		64				//������󳤶�
#define TP_MAX_STREAMNUM		3				//�᳡�����������

#define TP_MAX_SMALLSTREAMNUM	2				//ÿ��С��������
#define TP_STREAM_LEFT			0				//��С����
#define TP_STRAEM_RIGHT			1				//��С����
#define TP_MAX_CAP_SIGN_NUM     2               //���������ұ�ʶ������

#define TP_TOOL_VERSION_LEN		32				//�汾��Ϣ����

#define TP_EXPIRE_TIME			30				// expire timer
#define TP_ROUNDTRIP_TIME		30				//roundtrip

#define TP_MAX_NUM_CALLID		128				//SIPЭ��ջ�ص���CALLID��󳤶�

#define TP_UMS_MAX_REGNUM		512				//UMS���ע��CNS����
#define TP_UMS_MAX_REGALIAS		4096			//UMS���ע��ı�������

#define TP_CONF_SND_EPNUM		32				//ÿ�η��͵����᳡�б�����

#define TP_UMS_CHAN_BITRATE		3072
#define TP_UMS_MAX_CONFNUM		16				//UMS���ͬʱ֧�ֵĻ���
#define TP_CONF_MAX_EPNUM		64				//��������������������
#define TP_CONF_MAX_CNSNUM		1024		    //�������������CNS��������������
#define TP_CONF_INVITE_MAX_CNS	64				//������������������CNS����������������

#define TP_UMS_MAX_CALLNUM		128				//UMS�����н�������
#define TP_UMS_MAX_CHANNUM		192				//UMS����������
#define TP_UMS_MAX_CASCADECHANNUM 192			//�����ͨ������

#define TP_EAPU_PROTECTTIME_MAX		255			//����������󱣻�ʱ��
#define TP_EAPU_PROTECTTIME_MIN		1			//����������С����ʱ��
#define TP_EAPU_PROTECTTIME_DEFAULT	4			//��������Ĭ�ϱ���ʱ��

#define TP_AUDMIX_MAX_CHANNUM	224				//������ҵ������ͨ������
#define TP_MAX_AUD_MIX_CHAN		224				//������ý������֧��ͨ������
#define TP_APU2_MAX_CHAN_NUM	64				//ÿ��������֧�ֵ����ͨ������
#define TP_CONF_MAX_AUDMIXNUM	27				//�������������� b1��b2 B3�汾Ϊ���۳�Ա���������4�� B4�汾����Ա����Ϊ27
#define TP_MAX_AUD_MIX_NUM      4				//������������


#define TP_MAX_ROLLCALL_NUM          64             //�������᳡��



#define TP_CONF_MAX_TURNNUM		64				 //���������ѯ����
#define TP_CONF_TURN_MIN_INTERVAL	5			 //������ѯ�����Сֵ

#define TP_CONF_MAX_AUD_FMT_NUM			4			//������Ƶ��ʽ����
#define TP_CONF_MAX_MAIN_VIDEO_RES_NUM  6           //�������Ƶ�ֱ�������
#define TP_CONF_MAX_MINOR_VIDEO_RES_NUM 6           //�����Ƶ�ֱ�������

#define TP_CONFTEMPLATE_MAXNUM	128				//������ģ������
#define TP_CONFTEMP_ALIAS_NUM	256				//ģ�����������ÿ��ģ��һ��323ID��һ��164��
#define TP_CONFTEMPGROUP_MAXNUM 64              //ģ����������64��Ϊһ����ע�������ע��
#define TP_TEMPGROUP_MAXNUM     4               //ģ�����4��ע��
#define TP_TEMPNUM_PERGROUP     32              //ģ��32����Ϊһ��

#define TP_MAX_NMSERVER			2				//������ܷ���������
#define TP_MAX_VCR				2
#define TP_MAX_HDU_NUM			5
#define MAX_LOG_USE_NUM			5

#define TP_KEEPALIVE_TIME		30				//keeplive
#define TP_KEYFRAME_STATIS		5				//�ؼ�֡��������ͳ�ƴ���

#define TP_REFRESH_LIST_THREE	3
#define TP_REFRESH_LIST_FIVE	5
#define TP_REFRESH_LIST_EIGHT	8

#define	TP_MAX_CONF_ID_LEN      16
#define	TP_MAX_CONF_E164_LEN	16
#define	TP_MAXLEN_PASSWORD      32

#define TP_MAX_MPU2TP_EQP_NUM	4				//MPU2_TP ���ϳ�������

//����ϳ����
#define TP_VMP_SCHEME_CFG_NUM		5	//����ϳ�Ԥ�跽���������
#define TP_VMP_SCHEME_CFG_ALIAS		32	//����ϳɲ������÷�����������

#define TP_VMP_BASIC_IN_CHN_NUM		4	//basicģʽǰ����4·
#define TP_VMP_EHANCE_IN_CHN_NUM	18	//ehanceģʽǰ����20·
#define TP_VMP_MAX_IN_CHN_NUM		25	//mpu2����ϳɳ�Ա�������
#define TP_VMP_MAX_OUT_CHN_NUM		9	//mpu2����ϳɺ������������

//UMS������ز���
#define TP_UMS_BRD_MAXNUM_EQP	5	//ÿ���������������õ������������
#define	TP_MAXLEN_EQP_ALIAS        32   //����ģʽ����󳤶�
#define TP_BOARD_VERSION_LEN    32  //����汾��Ϣ����
#define TP_BOARD_MAX_NUM        128   //��󵥰�����
#define TP_BOARD_MAX_LAYER      4     //���������4��
#define TP_BOARD_MAX_SLOT       17    //���������17����λ��
#define TP_UPGRADE_FILENAME_LENGTH   32 //���������ļ�����󳤶�

#define TP_MAX_NUM_CONTACT_ADDR  5			//ע���ע��������Ľ����ַ����
#define TP_UPLOAD_FILE_NAME_LENGTH	 32		//����ģ���ļ����ļ�����󳤶�

#define TP_RET_ERROR 0xFFFF
#define TP_RET_OK	0
#define TP_AUDIO_CODEC_NUM      4  //��Ƶ�������
#define TP_VIDEO_CODEC_NUM      4 //��Ƶ�������

#define TP_MAX_LOSTPACK_NUM     14 //��󶪰�·��
#define TP_MAX_VIDEO_RES_NUM     8 //�����Ƶ�������

#define TP_MAX_CNS_REG_ALIAS	2
#define TP_MAX_UMS_REG_ALIAS	64

#define TP_ENCRYPT_KEY_LEN		16  //ģ����Կ����
//˫���ն�λĬ�Ϸ����
#define TP_DUAL_POS                    CNS_MAX_TER_NODE_NUM - 1

#define	TP_MAX_MEDIAKEY_LEN		1024
#define TPOUT	//����
#define TPIN	//���

#define TPIPFORMAT     "%d.%d.%d.%d"
#define Tpu32ToIP( ip )   (u8)(ntohl(ip)>>24),\
						(u8)(ntohl(ip)>>16),\
						(u8)(ntohl(ip)>>8), \
                        (u8)ntohl(ip) 

#define TP_INTERIM_ID          0             //��ʱ����ģ��id
#define TP_INVALID_INDEX		0xFFFF
#define TP_ALLEP_INDEX			65530   //�����л᳡���в�����index
#define TP_VALID_HANDLE(handle)	(TP_INVALID_INDEX != u16(handle))

//����ΪTTPTransAddr
#define ADDRNET(addr) \
	((unsigned char *)&addr.m_dwIP)[0], \
    ((unsigned char *)&addr.m_dwIP)[1], \
    ((unsigned char *)&addr.m_dwIP)[2], \
	((unsigned char *)&addr.m_dwIP)[3], \
	addr.m_wPort

#define ADDRPORT(addr, port) \
    ((unsigned char *)&addr)[0], \
    ((unsigned char *)&addr)[1], \
    ((unsigned char *)&addr)[2], \
	((unsigned char *)&addr)[3], \
	port
#define ADDRPORT_FORMAT	 " %3d.%3d.%3d.%3d:%5d "

                      
#define     TP_MAX_PROXYSERVER_NAME_LEN	255			//�������ǽ��������󳤶�
#define		TP_MAX_H323ALIAS_LEN        64            // �ն˱�����󳤶� 
#define     TP_MAX_NAME_LEN             TP_MAX_H323ALIAS_LEN
#define     TP_MAX_PASSWORD_LEN			16           // ������󳤶�   
#define		TP_NAME_LEN_256				(u16)256
#define		TP_REGNAME_SIZE			64
#define		TP_MAX_VERSION_LEN				64


template < class T >
T TP_SAFE_CAST( T &t, u8 *p )
{
	if (NULL == p) return t;
	memcpy( &t, p, sizeof( T ) );
	return t;
}

#define TP_SAFE_DEL(p) if(NULL != p){ delete p; p = NULL;}

typedef u32   u32_ip;

//CNS Define
#define CNS_MAX_TER_NODE_NUM		4		//��һ�᳡�����ն��������
#define CNS_MAX_CONF_NODE_NUM	1		//��һCns����᳡�����
#define CNS_MAX_CHANNEL_NUM 40

//Add by tanxiaodong 2012-07-17.
#define CNS_VGA_TYPE_NUM     5         //VGA������
#define TPAD_MAX_NUM         16            //TPad������
#define MAX_DISPLAY_NUM      3             //��ʾ������
#define MAX_LIGHT_NUM        8             //�ƹ����
#define MAX_CAMERA_NUM       3             //���������
#define AUDIO_PORT_NUM       4             //ÿ������Ƶ�ӿڸ���
#define MAX_PRIM_VIDEO_INPUT_PORT_NUM  3   //��һ·��Ƶ����˿ڸ���
#define MAX_PRIM_VIDEO_OUTPUT_PORT_NUM 3   //��һ·��Ƶ����˿ڸ���
#define MAX_PRIM_AUDIO_INPUT_PORT_NUM  3   //��һ·��Ƶ����˿ڸ���
#define MAX_PRIM_AUDIO_OUTPUT_PORT_NUM 3   //��һ·��Ƶ����˿ڸ���
#define MAX_DEMO_AUDIO_PORT_NUM        6   //˫����ʾ��Ƶ����˿ڸ���
#define CPU_MAX_USE_RATE     100           //CPU���ʹ����
#define EQUQLIZER_FREQUENCY_NUM        10   //������Ƶ�ʵ����
#define MAX__TP_MEDIA_CAP_NUM          10  //ÿ��ͨ����Я�������������� 
//End to add.

#define CANNON_DEFAULT_VALUE           10  //��ũ��˻ָ�Ĭ��ֵ
#define MIXAUDIO_SINGLEDEFAULT_VALUE   1   //������·�ָ�Ĭ��ֵ
#define MIXAUDIO_DEFAULT_VALUE         3   //�������ûָ�Ĭ��ֵ

#define MAX_AUDIO_PORT_NUM     10         //��Ƶ�ӿڵ�������

#define CNS_PRODUCT_ID		"CNSTPS"
#define CNS_VERSION_ID		"1.1.4.0.1"
#define	CNS_VERSION_ID_TEMP "2."
#define CNS_CALL_PORT		CNS_SIP_STACK_LISTION_PORT
#define CNS_VIDEO_CHAN_BAND 4096
#define CNS_AUDIO_CHAN_BAND 96
#define CNS_DUAL_BAND		4096
#define CNS_PRI_FRAMERATE	50
#define CNS_DUAL_FRAMERATE	50
#define CNS_GK_PORT			1719
#define CNS_H225_PORT		1720


#define CNS_CALL_MAX_CHANNEL			14
#define CNS_Dual_MAX_CHANNEL			4

	//POS TYPE
#define SPEAKER_MASK					0x0001
#define FULLVIEW_MASK					0x0002
#define DUAL_MASK						0x0004
#define AUDIO_MASK						0x0008


#define TP_MAXLEN_ENCRYPTKEY			128

#define node_ui							0x001
#define node_cnc						0x002       //CNS����̨
#define node_ums						0x004 
#define node_cncall						0x008
#define node_cnds						0x020
#define node_amix						0x021   

//Add by tanxiaodong 2012-11-12.
#define node_cnstool2cns             0x010      //ά������
//End to add.

#define HOME_STACK						((u8)0x01)
#define HOME_SERVICE					((u8)0x02)

#define ins_each						0xff

//cns�������ʹ�õĶ˿�
#define MT_AUDIO_SND_RTP				10001  
#define MT_AUDIO_SND_RTCP				10002  
#define MT_AUDIO_SND_BRTCP				10003  

#define MT_AUDIO_RCV_RTP				10004  
#define MT_AUDIO_RCV_RTCP				10005  
#define MT_AUDIO_RCV_BRTCP				10006  

#define MT_PRIVIDEO_SND_RTP				10031  
#define MT_PRIVIDEO_SND_RTCP			10032  
#define MT_PRIVIDEO_SND_BRTCP			10033  

#define MT_PRIVIDEO_RCV_RTP				10034  
#define MT_PRIVIDEO_RCV_RTCP			10035  
#define MT_PRIVIDEO_RCV_BRTCP			10036  

#define MT_SECVIDEO_SND_RTP				10051  
#define MT_SECVIDEO_SND_RTCP			10052  
#define MT_SECVIDEO_SND_BRTCP			10053 

#define MT_SECVIDEO_RCV_RTP				10054  
#define MT_SECVIDEO_RCV_RTCP			10055  
#define MT_SECVIDEO_RCV_BRTCP			10056 

//cnsת��ģ����ʼ�˿�
#define CN_DS_BASE_PORT					25000
#define CN_DS_MAX_NUM					10000
#define CN_DS_INS_OFFSET				100

#define CN_MAX_USER_NUM					20


//cns ������ϯ�����ʶ
#define CN_INNERSPEAKER_ALL				0xff
#define CN_INNERSPEAKER_NONE			0xf0


#define ADDR_MAX_USER_NAME_LENGTH		32
#define CN_HBPARAM_HB					30
#define CN_HBPARAM_HBNUM				3

#define CN_DUAL_MULTICAST_IP            "224.0.5.000"
#define MAX_COMMUNITY_LENGTH            32  // SNMP��ͬ������󳤶�
#define MAX_CNS_SNMP_NUM                2  //��һCNS��������ܷ��������������

#define MAX_CAMERA_NAME_LEN             256
#define MAX_CNCAMERA_NUM                3  //���������
#define MAX_CENTRETV_NUM                3  //���ӻ�����
#define MAX_AC_NUM                      3  //���յ���
#define MAX_CURTAIN_NUM                 6  //�������
#define MAX_CURNAME_LEN                 64 //

#define INVALID_MIX_INDEX               0xFFFF
#define INVALID_VCR_HANDLE				0XFFFF

//���������ļ�Ŀ¼
#define	FLASHFILE_PATH_NAME             "/usr/"
#define UPDATEFILE_PATH_NAME            "/ramdisk/"
#define UPDATEFILE_PATH_FROM_UPDATESER  "/ramdisk/sysfile/"
#define LOGO_UPLOAD_PATH                "/usr/conf/" 

//�豸�汾����󳤶�
#define MAX_DEVICEVER_LEN            38
#define PRE_DEVICEVER_LEN            12
#define MAX_REG_DEVICE_NUM            6
#define MAX_DEVICE_NUM                20
#define MAX_FTP_NAME_LEN               16
const int TP_MAX_FILESRV_FILENAME_LEN  = 32;        //�����ļ�������

#define UMS_MAX_VID_SOURCE_NUM                  10			  // ��ƵԴ������
#define UMS_MAX_VID_ALIAS_LEN					16            // ��ƵԴ������󳤶�

#define MAX_VTR_NAME_LENGTH				32

#define MAX_MT_ONLINE_LIST_NUM			64	//
#define MAX_MT_ALIAS_NUM				2

#define TP_CNS_ALIAS_REG_NUM	2
#define TP_UMS_MAX_REG_DATA		3
#define TP_CNS_MAX_REG_DATA		20

//̨��·��
#define CNMP_LOGO720P_PATH      "usr/conf/confname720.bmp"
#define CNMP_LOGO1080P_PATH     "usr/conf/confname1080.bmp"

#define CNMP_LOGO720P_INITIALPATH      "usr/bin/confname720.bmp"
#define CNMP_LOGO1080P_INITIALPATH     "usr/bin/confname1080.bmp"

#define CNMP_LOGO720P_POS0_PATH      "usr/conf/logoname720p0.bmp"
#define CNMP_LOGO1080P_POS0_PATH     "usr/conf/logoname1080p0.bmp"
#define CNMP_LOGO720P_POS1_PATH      "usr/conf/logoname720p1.bmp"
#define CNMP_LOGO1080P_POS1_PATH     "usr/conf/logoname1080p1.bmp"
#define CNMP_LOGO720P_POS2_PATH      "usr/conf/logoname720p2.bmp"
#define CNMP_LOGO1080P_POS2_PATH     "usr/conf/logoname1080p2.bmp"

#define CNMP_BANNER720P_POS0_PATH      "usr/conf/bannername720p0.bmp"
#define CNMP_BANNER1080P_POS0_PATH     "usr/conf/bannername1080p0.bmp"
#define CNMP_BANNER720P_POS1_PATH      "usr/conf/bannername720p1.bmp"
#define CNMP_BANNER1080P_POS1_PATH     "usr/conf/bannername1080p1.bmp"
#define CNMP_BANNER720P_POS2_PATH      "usr/conf/bannername720p2.bmp"
#define CNMP_BANNER1080P_POS2_PATH     "usr/conf/bannername1080p2.bmp"

//̨��ͼƬռ����󳤶�  ֧��200K�ļ�����
#define CNMP_LOGO_MAX_LENGTH    184320

//���ͼƬռ����󳤶�  ֧��200K�ļ�����
#define CNMP_BANNER_MAX_LENGTH    184320


#define CONF_HP_BITRATE					2048		//˫�ٻ�������ƵΪHP��������Ϊ2Mbps
#define CONF_BP_BITRATE					4096		//˫�ٻ�������ƵΪBP��������Ϊ4Mbps

#define VRS_ProductID               	"KDCVRS2000"
#define VRS_ProductID_E               	"KDCVRS2000E"

//////////////////////////////////////////////////////////////////////////
//mpu2 tp
#define UMS_VMP_MAX_CHANNEL		4	//���ͨ������
#define UMS_VMP_MAX_RCV			10	//������·��
#define UMS_VMP_MAX_SND			1	//�����

#define UMS_VMP_ENC_KEY_LEN		16	//��Կ����

#define MAX_VIDEO_FRAME_SIZE	(u32)(512 * 1024)
#define FRAME_RATE              (u8)25

#define DEFAULT_BMP_PATH		(LPCSTR)"/usr/etc/config/dft_16to9.bmp"
#define USR_BMP_PATH			(LPCSTR)"/usr/etc/config/usr_16to9.bmp"


#define UMS_VMP_RCV_PORT		20000
#define UMS_VMP_CHAN_SPAN		1500

#define UMS_VMP_SND_PORT		30000
#define UMS_VMP_PORT_SPAN		10

#define UMS_VMPMEDIA_TYPE_H264	(u8)106 /*H.264*/


#define TP_VIDEO_TIME_SPAN             40
#define TP_VIDEO_TIMESTAMP_SPAN        90
#define TP_AUD_REC_BUFF                20  //��Ƶ���ջ���
#define TP_LOST_AUD_PACKET_NUM         10   //��Ƶ�������
#define TP_AUD_PACKET_TIMEOUT          100   //��Ƶ����ʱʱ��
#define TP_CNMP_ONLINE_DEALY_TIME      10   //cnmp���ߺ�delayʱ�䵥λ��

#define TP_SNAPSHOT_PATH       "/usr/snapshot/"
#define TP_SNAPSHOT0_PATH       "/usr/snapshot/snapshot0.jpg"   //��һ·����
#define TP_SNAPSHOT1_PATH       "/usr/snapshot/snapshot1.jpg"	//�ڶ�·����
#define TP_SNAPSHOT2_PATH       "/usr/snapshot/snapshot2.jpg"	//����·����
#define TP_SNAPSHOT3_PATH       "/usr/snapshot/snapshot3.jpg"	//˫������

#define SINGLE_NUMBER         1
#define MAX_COMMEND_LEN 255 
#define MAX_SSH_INFO 10
#endif // _h_tpsys_h__








