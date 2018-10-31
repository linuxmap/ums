#ifndef _CN_CONST_H
#define _CN_CONST_H
#include "kdvdef.h"

//MT begin.
#include "kdvtype.h"                                                                                                                                                                        
enum EmDataFormat                                                                           
{                                                                                           
	emStr  ,                                                                            
	emHex  ,                                                                            
	emBin  ,                                                                            
//	emBOOL ,                                                                            
	emOct  ,                                                                            
	emIP   ,                                                                            
	emDec  ,                                                                            
	emDW                                                                                
};                                                                                          
                                                                                            
                                                                                            
#define CALLRATE_64_SEL        0x00000001                                                   
#define CALLRATE_128_SEL       0x00000002                                                   
#define CALLRATE_192_SEL       0x00000004                                                   
#define CALLRATE_256_SEL       0x00000008                                                   
#define CALLRATE_320_SEL       0x00000010                                                   
#define CALLRATE_384_SEL       0x00000020                                                   
#define CALLRATE_448_SEL       0x00000040                                                   
#define CALLRATE_512_SEL       0x00000080                                                   
#define CALLRATE_576_SEL       0x00000100                                                   
#define CALLRATE_640_SEL       0x00000200                                                   
#define CALLRATE_704_SEL       0x00000400                                                   
#define CALLRATE_768_SEL       0x00000800                                                   
#define CALLRATE_832_SEL       0x00001000                                                   
#define CALLRATE_896_SEL       0x00002000                                                   
#define CALLRATE_960_SEL       0x00004000                                                   
#define CALLRATE_1024_SEL      0x00008000                                                   
#define CALLRATE_MASK          0x0000FFFF                                                   
                                                                                            
                                                                                             
//
// VOD Limited Condition 
//
#define VOD_DIRECTORY_SEPARATOR ( ( s8* ) "\\" )

const int VOD_MAX_CLIENT = 32; // ��������ӵĿͻ�����
const int VOD_MAX_USER_NAME_LENGTH = 32; // �û�������
const int VOD_MAX_PASSWORD_LENGTH = 32; // ���볤��
const int VOD_MAX_PATH_FILE_NAME_LENGTH = 128;  // ��·�����ļ�������
const int VOD_MAX_DIRECTIRY_NAME_LENGTH = 128; // ·��������
const int VOD_MAX_FILE_NAME_LENGTH = 50; // �ļ������� 
const int VOD_MAX_FILE_NUMBER = 64; // ͬһ�ļ���������ļ���                                                                                        
                                                                                            
                                                                                            
// ���ȶ���   
const int    MT_MAX_H323ALIAS_LEN       =   64;            // �ն˱�����󳤶�                                                                                 
const int    MT_MAX_NAME_LEN            =   MT_MAX_H323ALIAS_LEN;                                                          
const int    MT_MAX_E164NUM_LEN         =   16;            // �ն�E164��󳤶�                 
const int    MT_MAX_PORTNAME_LEN        =   16;            // ��Ƶ����˿�����󳤶�           
const int    MT_MAX_AVMATRIX_PORT_NUM   =   64;            // ��Ƶ�������˿ڸ���            
const int    MT_MAX_AVMATRIX_MODEL_NAME =   16; 
const int    MT_MAXLEN_AVMATRIX_SCHEMENAME  = 16;          //���󷽰�������󳤶�
const int    MT_MAX_AVMATRIX_PORTNAME_LEN = 16;            //����˿�����󳤶�
const int    MT_MAX_COMM_LEN            =   32;            // SNMP��ͬ������󳤶�             
const int    MT_MAX_PPPOE_USERNAME_LEN  =   16;            // PPPOE�û�����󳤶�              
const int    MT_MAX_CHANNEL_NAME_LEN    =   16;            // ��ý��Ƶ������󳤶�             
const int    MT_MAX_PASSWORD_LEN        =   16;            // ������󳤶�                     
const int    MT_MAX_FULLFILENAME_LEN    =   128;           // �����ļ�����󳤶�               
const int    MT_MAX_FILEPATH_LEN        =   128;           // ·������󳤶�                   
const int    MT_MAX_CAMERA_NUM          =   6;             // ����ͷ������ 
const int    MT_MAX_CAMERA_EX_NUM       =   64;            // �����չ����ͷ��                  
const int    MT_MAX_CAMERA_NAME_LEN     =   16;            // ����ͷ������󳤶�               
const int    MT_MAX_ETHNET_NUM          =   4;             // �ն���̫�������ֵ               
const int    MT_MAX_E1_NAME_LEN         =   32;            // E1����󳤶�                     
const int    MT_MAX_E1UNIT_NUM          =   4;             // E1ģ�����E1��                   
const int    MT_MAX_ROUTE_NUM           =   16;            // ���·����Ŀ                     
const int    MT_MAX_SERIAL_NUM          =   3 ;            //��മ����Ŀ
const int    MT_MAXNUM_MIX_MEMBER       =   10;            //������������Ա��
const int    MT_MAX_VIDEO_NUM           =   2 ;            //�����Ƶ·��
const int    MT_MAXNUM_VMP_MEMBER       =   20;            //����ϳɳ�Ա��
const int    MT_MAXNUM_SMSDST           =   64;            //����Ϣ����Ŀ�ĳ�Ա���ֵ
const int    MT_MAXLEN_SMSTEXT          =   1024;          //����Ϣ������󳤶�
const int    MT_MAX_IMAGEJUDGEPARAM_NUM =   2;             //������������� 
const int    MT_MAX_POLL_NUM		    =   16;    		   //�����ѯ�ն���
const int    MT_MAX_ADDRENTRY_NUM	    =   128;           //��ַ�������Ŀ����
const int    MT_MAX_ADDRMULTISET_NUM    =   16;            //��ַ����������
const int    MT_MAX_NETSND_DEST_NUM     =   5 ;            //˫��������͵�Ŀ�ĵ���
const int    MT_MAX_CALLSITE_TERNINAL   =   16;            //�����Ļ������
const int    MT_MAX_ADDRUSERDEF_LEN     =   1024;          //��ַ���û��Զ����ֶγ���
const int    MT_MAX_MTC_CAPSET_LEN      =   1024;          //MT��MTC���ֵ������ַ�������

const int    MT_MAXNUM_VIDSOURCE        =   10;            //�����ƵԴ��
const int    MT_MAXNUM_CALLADDR_RECORD  =   5;             //�����е�ַ��¼��

const int    MT_PPPoE_MAX_USENAME_LEN     =  255;          //PPPOE����ʱʹ�õ��û�������󳤶�
const int    MT_PPPoE_MAX_PASSWORD_LEN    =  255;          //PPPOE����ʱʹ�õ��������󳤶�
const int    MT_PPPoE_MAX_SERVERNAME_LEN  =  255;          //PPPOE����ʱʹ�õ�ָ��ISP���������ֵ���󳤶�
const int    MT_PPPoE_MAX_VERSION_LEN     =  255;          //PPPOE�汾��Ϣ����󳤶�
const int    MT_MAX_UPDATASERVER_NAME_LEN =  64;           //��������������������󳤶�
const int    MT_MAX_LDAPSERVER_NAME_LEN   =  100;          //LDAP��������������󳤶�
const int    MT_MAX_PROXYSERVER_NAME_LEN  =  255;          //�������ǽ��������󳤶�
const int    MT_MAX_H323GKSERVER_NAME_LEN =  255;          //H323ע��Gk��������󳤶�
const int    MT_MAX_HDAUDIOPORT_LEN       =  15;           //��Ƶ�˿ڸ������ֵ

//FILESRV: �������������
const int    MT_MAX_FILESRV_BUG_REPORT_LEN   = 512;       //�����汾�е��޸���bug����0
const int    MT_MAX_FILESRV_FILENAME_LEN     = 64;        //�����ļ�������
const int    MT_MAX_FILESRV_DEVFILE_NUM      = 4;         //�����ļ�����
const int    MT_MAX_FILESRV_SOFTWARE_VER_LEN = 32;        //����汾����󳤶�

const int    MT_MAX_PXYIP_NUM                =   5;            // �������pxy֧�ֵ�ip��ַ��   

//WiFi������� 
const int    MT_WIFI_MAX_NAME_LEN            =   32;
const int    MT_WIFI_MAX_PASSWORD_LEN        =   256;
const int    MT_WIFI_MAX_BSSIDCFG_NUM        =   16;  

//HD�ն˵���Ƶ����ڸ���
const int    MT_HD_MAX_AV_OUTPORT_NUM  = 4;            //�����ն˵������Ƶ����ڵĸ���

const int    MT_VIDEO_OUTPORT_NUM          = 4;    
const int    MT_INNERMATRIX_SCHEME_NUM     = 8;
const u32    MT_DVI_PORT_NUM               = 6;    

const u8     ExVideoMoudle_None = 0;
const u8     ExVideoMoudle_SDII = 1;
const u8     ExVideoMoudle_SDIO = 2;

const u8     DVI_MODE_HDMI  = 0;
const u8     DVI_MODE_DVI  = 1;
const u8     DVI_MODE_YPBPR = 2;
const u8     DVI_MODE_VGA   = 3;

//����ڵ�����Դ����
const u8     HD2G_VIDEO_IN_PVDEC   = 0;
const u8     HD2G_VIDEO_IN_SVDEC   = 1;
const u8     HD2G_VIDEO_IN_DVI1   = 2;
const u8     HD2G_VIDEO_IN_DVI2   = 3;
const u8     HD2G_VIDEO_IN_DVI3   = 4;
const u8     HD2G_VIDEO_IN_CVBS   = 5;
const u8     HD2G_VIDEO_IN_SDI1   = 6;
const u8     HD2G_VIDEO_IN_SDI2   = 7;
const u8     HD2G_VIDEO_IN_INVALID   = 255;


#define      MT_MAXNUM_MCTERMINAL        6    //�ն�MTC֧�ֺ��е�����ն���
#define      MT_MAXLEN_CAMERA_TYPE_NAME  32    //����ͷ��������󳤶�                                                                                        
//==========================================================================================
//				������س�������                                            
//==========================================================================================
                                                                                            
////////////////////////////// ����ID ////////////////////////////                          
const int    AID_MT_BEGIN        =   AID_MT_BGN;
const int    AID_MT_AGENT	     =   AID_MT_BEGIN + 1;    	//�ն˴���                          
const int    AID_MT_SERVICE      =   AID_MT_BEGIN + 2;        //�ն�ҵ��Ӧ��ID                      
const int    AID_MT_GUARD	     = 	 AID_MT_BEGIN + 3;    	//�ն�����                          
const int    AID_MT_UE		     =	 AID_MT_BEGIN + 4;    	//ҵ��ӿ�ʵ��                      
const int    AID_MT_STACKIN      =	 AID_MT_BEGIN + 5;    	//H323 Э��ջ����                   
const int    AID_MT_STACKOUT	 =	 AID_MT_BEGIN + 6;    	//H323 Э��ջ���                   
const int    AID_MT_RCP		     =	 AID_MT_BEGIN + 7;    	//MT RCP                            
const int    AID_MT_H320STACK    =   AID_MT_BEGIN + 8;        //H320 Э��ջ����Ӧ��                    
const int    AID_MT_RCSIM        =	 AID_MT_BEGIN + 9;        //ң������ģ��ģ��                  
const int    AID_MT_MC		     =	 AID_MT_BEGIN + 10;    	//MC                                
const int    AID_MT_SNMP	     =	 AID_MT_BEGIN + 11;        //SNMP                              
const int    AID_MT_CONFIG       =   AID_MT_BEGIN + 12;        //�����ļ�����Ӧ��ID                  
const int    AID_MT_UI	         =	 AID_MT_BEGIN + 13;        //�ն˽���Ӧ��                
const int    AID_MT_DEVCTRL	     =	 AID_MT_BEGIN + 14;    	//�豸����                          
const int    AID_MT_CODEC	     =	 AID_MT_BEGIN + 15;    	//�����                            
//const int    AID_ADDRBOOK	     =	 AID_MT_BEGIN + 16;    	//��ַ��                            
const int    AID_MTCONSOLE	     =	 AID_MT_BEGIN + 17;    	//�ն˿���̨ 
const int    AID_MT_SYS          =   AID_MT_BEGIN + 18;        //�ն�ϵͳӦ��ID                  
const int    AID_MT_H323SERVICE  =   AID_MT_BEGIN + 20;        //�ն�H323ҵ��Ӧ��ID                  
const int    AID_MT_H320SERVICE  =   AID_MT_BEGIN + 21;        //�ն�H320ҵ��Ӧ��ID                  
const int    AID_MT_SIPSERVICE   =   AID_MT_BEGIN + 22;        //�ն�SIPҵ��Ӧ��ID                                                                                            
const int    AID_MT_DVB          =   AID_MT_BEGIN + 23 ;        //�ն�˫����ҵ��Ӧ��ID
const int    AID_MT_DVBSSN       =   AID_MT_BEGIN + 24;        //˫���лỰӦ��
const int    AID_MT_VODCLIENT    =   AID_MT_BEGIN + 25;         //VOD�ͻ���Ӧ��ID
const int    AID_MT_PCDUALVIDEO  =   AID_MT_BEGIN + 26;         //pc˫�����Ӧ��ID
const int    AID_MT_UPGRADE      =   AID_MT_BEGIN + 27;         //�Զ�����Ӧ��ID
const int    AID_MT_BATCHCONFIG  =   AID_MT_BEGIN + 28;         //�����ļ�������Ӧ��ID
const int    AID_MT_AUTOTEST     =   AID_MT_BEGIN + 29;         //�ն�Ӳ���Զ�������Ӧ��ID   
const int    AID_MT_AUTOTESTCLIENT = AID_MT_BEGIN + 30;         // add by wangliang 2007-03-02
const int    AID_MT_REMOTESIM    =   AID_MT_BEGIN + 31;         // add by wangliang 2007-03-02
const int    AID_MT_THREADDETECT =   AID_MT_BEGIN + 32;         // add by qianshufeng 2008-01-07
const int	 AID_MT_LOG_RECV	 =   AID_MT_BEGIN + 33;			// ��־����APP
const int	 AID_MT_LOG_IO		 =   AID_MT_BEGIN + 34;			// ��־IOAPP�����̲߳������ⲿ��Ϣ
const int    AID_MT_SIPSTACK_IN  =   AID_MT_BEGIN + 35;
const int    AID_MT_SIPSTACK_OUT =   AID_MT_BEGIN + 36;
const int    AID_MT_SATINTERFACE =   AID_MT_BEGIN + 37;
const int	 AID_MT_SATSERVICE   =   AID_MT_BEGIN + 38;
const int	 AID_MT_TPREG   =   AID_MT_BEGIN + 40;
//End
#define AID_MT_CTRL     AID_MT_SERVICE

#define AID_ADDRBOOK    46
////////////////////////////// �������ȼ� ////////////////////////////                      
                                                                                            
	                                                                                    
//==========================================================================================
//			     ������س�������                                               
//==========================================================================================
                                                                                            
////////////////////////////// ��Ϣ�ṹ���� ////////////////////////////                    
                                                                                         
                                                                                            
#define     MT_MAX_CONF_ID_LEN 			16        //����ID����                         
#define     MT_MAX_CONF_NAME_LEN		64	      //�������ֳ���                       
#define     MT_MAX_CONF_E164_LEN	 	16	      //������볤��                      
#define     MT_CONF_CAPACITY			192		  //�����ն�����      
#define     MT_MAXNUM_INVITEMT			32        //�����������������ն���
#define		MT_MAX_CONF_NUM				16		  //��������

#define     MT_CONFLIST_TO_MTC			35		  //�����ն��б���mtc

#define     MT_MAXLEN_ENCRYPTKEY    64 

const int   MT_MAXLEN_MESSAGE       =   1024*24;  //�ն���Ϣ��󳤶�16K                                                                                            

#define     MT_MAXLEN_CONFGUID          16		  //����guid��󳤶�
#define     MT_MAXLEN_PASSWORD          32		  //������󳤶�
#define     MT_NAME_LEN                 16		  //�ն˱�������                      
//#define		CTRL_TERLABEL_UPPER		193			//��Ч���ն˱��    
//#define     CTRL_TERMID_LEN			128			//�����ն�ID����


// ��־����
#define		MT_LOG_ERROR		0
#define		MT_LOG_VITAL		1
#define		MT_LOG_WARNING		10
#define		MT_LOG_HINT			100
#define		MT_LOG_DETAIL		200
#define		MT_LOG_MAX			255

//����mtmp������
//[xujinxing-2006-05-15]

#define   MTMP_NO_ERROR     (u16)0
#define   MTMP_ERROR_BASE   (u16)5000
#define   ERROR_DECODER_SNAPSHOT_FAIL_H261  (u16)(MTMP_ERROR_BASE + 1)
#define   ERROR_ENCODER_SNAPSHOT_FAIL_H261  (u16)(MTMP_ERROR_BASE + 2)

//�����mc_license��صĺ� 
//[xujinxing-2006-10-13]

// License����
#define MT_KEY_FILENAME                "kedalicense.key" // "mt.key"
#define MT_KEDA_AES_KEY				  "kedacom200610101"
#define MT_KEDA_COPYRIGHT			  "Suzhou Keda Technology Co.,ltd. Tel:86-512-68418188, Fax: 86-512-68412699, http://www.kedacom.com"
// �������ݵĳ���
#define MT_LEN_KEYFILE_CONT              (u16)512

//add by xujinxing, telnet authority
#define MT_TEL_USRNAME  "admin"
#define MT_TEL_PWD      "admin"

#define MT_TELNET_PWD_MAX_LEN 32

/************************************************************************/
/* �ն�Ӳ���Զ������� wl 2007/02/06
/************************************************************************/

// �Զ�����������汾��
#define MT_AUTOTEST_VER 0x0100

// ����ʧ��ԭ��
#define AUTOTEST_NACK_REASON_OK          0  //���Խ���ɹ�
#define AUTOTEST_NACK_REASON_HDERR       1  //Ӳ������ʧ��
#define AUTOTEST_NACK_REASON_TESTING     2  //�������ڽ���
#define AUTOTEST_NACK_REASON_UNSUPPORT   3  //Ӳ����֧��
#define AUTOTEST_NACK_REASON_STATUSERROR 4  //�ն�״̬����
#define AUTOTEST_NACK_REASON_VERERROR    5  //�汾�Ŵ���

/* �Զ������Խӿں��������������� */

// VLYNQ���ܺ�������ϲ���: ����Ƶ��+����״̬+���Է���
const u8 AUTOTEST_VLYNQFUNC_FREQ_76 = 0;  // VLYNQ����Ƶ��: 76MHZ
const u8 AUTOTEST_VLYNQFUNC_FREQ_99 = 1;  // VLYNQ����Ƶ��: 99MHZ 

const u8 AUTOTEST_VLYNQFUNC_STATE_0 = 0;  // VLYNQ����״̬: ��ģʽ
const u8 AUTOTEST_VLYNQFUNC_STATE_1 = 1;  // VLYNQ����״̬: ��ģʽ

const u8 AUTOTEST_VLYNQFUNC_MODE_1  = 1;  // VLYNQ���Է���: ��Է�DSP��ַд��������
const u8 AUTOTEST_VLYNQFUNC_MODE_2  = 2;  // VLYNQ���Է���: ��Է�DSP��ַд�ݼ�����
const u8 AUTOTEST_VLYNQFUNC_MODE_3  = 3;  // VLYNQ���Է���: ���Լ�DSP��ַд��������
const u8 AUTOTEST_VLYNQFUNC_MODE_4  = 4;  // VLYNQ���Է���: ���Լ�DSP��ַд�ݼ�����
const u8 AUTOTEST_VLYNQFUNC_MODE_5  = 5;  // VLYNQ���Է���: ���Լ�DSP��ַ����������
const u8 AUTOTEST_VLYNQFUNC_MODE_6  = 6;  // VLYNQ���Է���: ���Լ�DSP��ַ���ݼ�����
const u8 AUTOTEST_VLYNQFUNC_MODE_7  = 7;  // VLYNQ���Է���: ��Է�DSP��ַ����������
const u8 AUTOTEST_VLYNQFUNC_MODE_8  = 8;  // VLYNQ���Է���: ��Է�DSP��ַ���ݼ�����

// EPLD�Ĵ�����д��ϲ���:  epld��������
const u8 AUTOTEST_EPLDFUNC_CMD_WRITECMD = 0;
const u8 AUTOTEST_EPLDFUNC_CMD_READCMD  = 1;

// ��Ƶ�Ի���ϲ���: ������+��Ƶ���ݸ�ʽ
// ������ʹ��ʱ��Ҫʹ��ʵ��ֵ
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_8000  = 0; // ������: 8000
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_32000 = 1; // ������: 32000
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_44100 = 2; // ������: 44100
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_48000 = 3; // ������: 48000

const u8 AUTOTEST_AUDIOFUNC_FORMAT_16 = 0; // ��Ƶ���ݸ�ʽ: S16_LE
const u8 AUTOTEST_AUDIOFUNC_FORMAT_32 = 1; // ��Ƶ���ݸ�ʽ: S32_LE

// ��Ƶ�Ի���ϲ���: �����ʽ+OSD��ʾ+���л���ʾ

const u8 AUTOTEST_VIDEOFUNC_OUTPUT_0  = 0;  // �����ʽ: D1
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_1  = 1;  // �����ʽ: CIF 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_2  = 2;  // �����ʽ: ZOOM 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_3  = 3;  // �����ʽ: VGA60 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_4  = 4;  // �����ʽ: VGA75 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_5  = 5;  // �����ʽ: VGA85
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_6  = 6;  // �����ʽ: SVGA60 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_7  = 7;  // �����ʽ: SVGA75
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_8  = 8;  // �����ʽ: SVGA85
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_9  = 9;  // �����ʽ: XGA60 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_10 = 10; // �����ʽ: XGA75

const u8 AUTOTEST_VIDEOFUNC_OSD_0 = 0; // OSD��ʾ: ��֧��
const u8 AUTOTEST_VIDEOFUNC_OSD_1 = 1; // OSD��ʾ: ֧��

const u8 AUTOTEST_VIDEOFUNC_PIP_0 = 0; // ���л���ʾ: ��֧��
const u8 AUTOTEST_VIDEOFUNC_PIP_1 = 1; // ���л���ʾ: ֧��

const u8 MAX_CHAIR_POLLSCHEME_NUM = 3; // ��ϯ�ն���ѯ������Ŀ

const u8 MAX_MTCBOX_SHORTCUT_CALL_NUM = 4; //MTC BOX ֧�ֵ�����ݺ�����Ŀ

//////////////////////////////////////////////////////////////////////
/*HD Macro definition BEGIN*/
#define HD_PATCH_VER_A              0
#define HD_PATCH_VER_B              1

#define HD_RESIZE_FILL              0 //�Ӻڱ�
#define HD_RESIZE_CLIP              1 //�ñ�
#define HD_RESIZE_SCALE             2 //����

#define HD_SCREENMODE_SIMPLE        0
#define HD_SCREENMODE_NORMAL        1
#define HD_SCREENMODE_ADVANCE       2


/*WIFI Macro definition BEGIN*/
#define WIFI_MAX_BSS_NUM            16
#define WIFI_MAX_KEY_LEN            64
#define WIFI_MAX_NAME_LEN           64

#define WIFI_MAX_CFG_NUM            16

#define WIFI_NET_TYPE_INFRA          0
#define WIFI_NET_TYPE_ADHOC          1

#define WIFI_AUTH_TYPE_OPEN          0
#define WIFI_AUTH_TYPE_SHARE         1
#define WIFI_AUTH_TYPE_WPA_PSK       2
#define WIFI_AUTH_TYPE_WPA2_PSK      3

#define WIFI_ENCRYTO_TYPE_WEP        0
#define WIFI_ENCRYTO_TYPE_AES        1
#define WIFI_ENCRYTO_TYPE_TKIP       2

//�ն˷���״̬����ӦMCUö��emMtSpeakerStatus��
#define MT_SPEAK_STATUS_BGN      (u32)0
#define MT_SPEAK_STATUS_WAITING  (u32)1
#define MT_SPEAK_STATUS_AGREED   (u32)2
#define MT_SPEAK_STATUS_DENIED   (u32)3
#define MT_SPEAK_STATUS_CANCELED (u32)4

//mcu����ģʽ����Ӧmcuö��emConfSpeakMode��
#define MT_SPEAK_MODE_NORMAL     (u32)0 //��ͨ����ģʽ����ϯָ��/���ָ��/һ����ն�����
#define MT_SPEAK_MODE_INSTANTLY  (u32)1 //����ģʽ
#define MT_MAX_CNS_NAME_LEN		  (u16)256



#define MT_MEPG4AAC_CHAN_MONOPHONY     (u8)1               //������
#define MT_MEPG4AAC_CHAN_BINAURAL      (u8)2               //˫����
#define MT_MEPG4AAC_IDLE_CHAN_TYPE     MT_MEPG4AAC_CHAN_MONOPHONY

#define MT_HD_IMAGE_PARAM_COUNT         4      // ��������,������SDI
#define MT_HD_IMAGE_PARAM_YPbPr0    (u8)0      // ����1��ͼ�������������
#define MT_HD_IMAGE_PARAM_YPbPr1    (u8)1      // ����2��ͼ�������������
#define MT_HD_IMAGE_PARAM_YPbPr2    (u8)2      // ����3��ͼ�������������
#define MT_HD_IMAGE_PARAM_CVBS      (u8)3      // CVBS��ͼ�������������

#define MT_HD_IMAGE_PARAM_SDI0		(u8)4      // SDI1��ͼ�������������
#define MT_HD_IMAGE_PARAM_SDI1		(u8)5	   // SDI2��ͼ�������������


#define MT_HD_IMAGE_PARAM_INVALID   (u8)0xFF   // ��Ч����
#define GetHdParamImageIndex( emMtVideoPort )\
( emMtVideoPort == emMtC1Vid ? MT_HD_IMAGE_PARAM_YPbPr0 : \
( emMtVideoPort == emMtC2Vid ? MT_HD_IMAGE_PARAM_YPbPr1 : \
( emMtVideoPort == emMtC3Vid ? MT_HD_IMAGE_PARAM_YPbPr2 : \
( emMtVideoPort == emMtC4Vid ? MT_HD_IMAGE_PARAM_CVBS : MT_HD_IMAGE_PARAM_INVALID ) ) ) )

#define MT_AACLC_IDLE_CHAN_TYPE     (u8)1


// --------------- ��ϼ���غ궨�� --------------- 
#define MT_COMBINED_HELP_RED      0   // HELP(3s) + Red
#define MT_COMBINED_HELP_YLW      1   // HELP(3s) + YLW
#define MT_COMBINED_HELP_GRN      2   // HELP(3s) + GRN

// --------------- ����ģʽ�궨�� --------------- 
#define ETH_MODE_AUTO           (u32)0
#define ETH_MODE_10M_FULL       (u32)1
#define ETH_MODE_10M_HALF       (u32)2
#define ETH_MODE_100M_FULL      (u32)3
#define ETH_MODE_100M_HALF      (u32)4

// --------------- ������ʽ�궨�� --------------- 
#define MT_HD_IMAGE_AUTOADJUST           (u32)0
#define MT_HD_IMAGE_ORIGINSIZE           (u32)1

// --------------- ͼ����������Ĳ������� ------------------
#define MT_SCALE_BRIGHTNESS     (u32)0 /* �������ȣ�  C | YPbPr */
#define MT_SCALE_CONTRAST       (u32)1 /* ���öԱȶȣ�C | YPbPr */
#define MT_SCALE_HUE            (u32)2 /* ����ɫ�ȣ�  C */
#define MT_SCALE_SATURATION     (u32)3 /* ���ñ��Ͷȣ�C | YPbPr */

// --------------- Զ�˽��˲������� --------------- 
#define MT_DIALOG_PA           (u32)0 /*��������*/
#define MT_DIALOG_MC           (u32)1 /*�ƶ�����ͷ*/
#define MT_DIALOG_CP           (u32)2 /*��������ͷ*/

// --------------- PCMT��Ƶ����뷽ʽ���� --------------- 
#define PCMT_VCODEC_SOFTWARE           (u8)0 /*��������*/
#define PCMT_VCODEC_HARDWARE           (u8)1 /*Ӳ���Կ������*/
#define PCMT_VENCODE                   (u8)0 /*����*/
#define PCMT_VDECODE                   (u8)1 /*����*/

// --------------- ����1080P/i,720--֡������ --------------- 
#define MT_HD_ORIGIN					 (u32)0
#define MT_HD_1080p_24                   (u32)1
#define MT_HD_1080p_25                   (u32)2
#define MT_HD_1080p_30                   (u32)3
#define MT_HD_1080p_50					 (u32)4
#define MT_HD_1080p_60					 (u32)5
#define MT_HD_1080i_50                   (u32)6
#define MT_HD_1080i_60                   (u32)7
#define MT_HD_720p_50				     (u32)8
#define MT_HD_720p_60					 (u32)9
#define MT_576i_50						 (u32)10
#define MT_HD_1080p_29					 (u32)11
#define MT_HD_1080p_59					 (u32)12


// --------------- VGA--Ƶ������ --------------- 
#define MT_HD_VGA_60                     (u32)0
#define MT_HD_VGA_75                     (u32)1
#define MT_HD_SVGA_60					 (u32)2
#define MT_HD_SVGA_75					 (u32)3
#define MT_HD_XGA_60					 (u32)4
#define MT_HD_XGA_75					 (u32)5
#define MT_HD_SXGA_60					 (u32)6
#define MT_HD_WSXGA_60					 (u32)7
#define MT_HD_WXGA1280x768_60			 (u32)8
#define MT_HD_WXGA1280x768_75			 (u32)9
#define MT_HD_WXGA1280x800_60			 (u32)10
#define MT_HD_WXGA1280x800_75			 (u32)11
#define MT_HD_WXGA1360x768_60			 (u32)12
#define MT_HD_UXGA_60					 (u32)13
#define MT_HD_SXGAPLUS_60				 (u32)14


//-----------------��������һ֡------------------
#define MT_HD_LastFrame					 (u32)0
#define MT_HD_BlueScreen                 (u32)1

//-----------------�Ƿ񵯳�"���뷢��"�Ŀ��ƿ�------------------
#define MT_UNPOP_CHAIRCONTROLDLG         (u32)0
#define MT_POP_CHAIRCONTROLDLG			 (u32)1

//mtcbox
#define SERIAL_232 (u8)0
#define SERIAL_485 (u8)1

//�ն˶���������������Ͳ��ֶ���
const u32 type_MtExtCfgCmdTypeBase = 0;
const u32 type_FullFrameMode       = type_MtExtCfgCmdTypeBase + 1;
const u32 type_MtVersion		   = type_MtExtCfgCmdTypeBase + 2;
const u32 type_VGAError			   = type_MtExtCfgCmdTypeBase + 3;
const u32 type_LastBlue			   = type_MtExtCfgCmdTypeBase + 4;//����ƵԴ��ʾ��������һ֡
//�ն˰汾�ţ���Ҫ�����޸���ĳЩ�ṹ���Mtc�޷��������ն�
const u32 g_dwMtVersion = 1;
/*WIFI Macro definition END*/
//MT end.

/////////////////////////////////////////////////////////////////////////////
//////////////////////////����cnagentģ��////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#define KDV_READ_COMMUNITYSTRING            	(LPCSTR)"public"
#define KDV_WRITE_COMMUNITYSTRING           	(LPCSTR)"kdv123"

#define	CN_TRAP_PORT                            162
#define	CN_GETSET_PORT                          161    

//CPU���ڴ������
#define CN_GUARD_CPUADNMEM_TIMER                    6000
#define CN_GUARD_STATISTIC_TIMER                    6000
#define CN_CPU_MAX_VALUE                            100
#define CN_MEMORY_MAX_VALUE                         100
#define CN_MEMORY_SHIFT_VALUE                       16
#define CN_LOW16_MAX_VALUE                          0xFFFF
#define CN_MEMORY_UNIT                              1024

// �ڴ�ʹ��״̬�ı�
// ʹ���ʳ���80%����
const u32 CNMEMORYUESDCRITVAL = 80;

// cpuʹ��״̬�ı�
// ʹ���ʳ���85%����
const u32 CNCPUUSEDCRITVAL = 85;


//////////////////////////�澯��Ϣ///////////////////////////////////////////
//ϵͳ״̬
const u32  CNSYSSTATE_RUNNING   = 1;//ϵͳ����
const u32  CNSYSSTATE_REBOOT	= 2;//ϵͳ����
const u32  CNSYSSTATE_DOWN   = 3;//ϵͳ�ϵ�

//////////////////////////cns�澯��///////////////////////////////////////////
#define ALARM_CN_BASE							10000L
#define ALARM_CN_CPUERROR						(ALARM_CN_BASE+1003L)   /*cpu����*/
#define ALARM_CN_MEMORYERROR                    (ALARM_CN_BASE+1001L)   /*�ڴ����*/


/* MT�澯�������� */
#define ALARMOBJ_CN_MAX                         4
#define ALARMOBJ_CN_BASE				        (u8)128
#define ALARMOBJ_CN                             (u8)(ALARMOBJ_CN_BASE + 1)

/////////////////////////////////////////////////////////////////////////////
//////////////////////////End////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//////////////////////////����cnconfigģ��///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

const int    CN_MAX_VIDEO_NUM           =   2 ;            //�����Ƶ·��

//��Ƶ��ϢĬ��ֵ
#define CN_DEFAULT_AUDIO_INPUTVOLUME                           16
#define CN_DEFAULT_AUDIO_OUTPUTVOLUME                           16
//add by wangqichang
#define CN_DEFAULT_AUDIO_OUTPUTGAIN                             20//����δ������ʱ����Ч��ͼ��Ϊ20

#define  CN_MAX_PRIOMVIDEO_1080P_FRAMERATE             60     //��һ·��Ƶ��1080p���֡��
#define  CN_MIN_VIDEO_1080P_FRAMERATE                  1      //��Ƶ��1080p��С֡��
#define  CN_DEFAULT_PRIOMVIDEO_7920_A_1080P_FRAMERATE  60     //��һ·������Ƶ��1080pĬ��֡��
#define  CN_DEFAULT_PRIOMVIDEO_7920_A_720P_FRAMERATE   60     //��һ·������Ƶ��720pĬ��֡��
#define  CN_DEFAULT_PRIOMVIDEO_1080P_FRAMERATE         25     //��һ·��Ƶ��1080pĬ��֡��
#define  CN_DEFAULT_PRIOMVIDEO_720P_FRAMERATE          50     //��һ·��Ƶ��720pĬ��֡��

#define	 CN_PRIMOVIVEO_H264IKEYRATE	     			   3000   //��һ·��ƵH264�ؼ�֡���

#define  CN_MAX_SECONDVIDEO_1080P_FRAMERATE             31     //�ڶ�·��Ƶ��1080p���֡��
#define  CN_DEFAULT_SECONDVIDEO_1080P_FRAMERATE  25     //�ڶ�·������Ƶ��1080pĬ��֡��
#define  CN_DEFAULT_SECONDVIDEO_720P_FRAMERATE   30     //�ڶ�·������Ƶ��720pĬ��֡��
// #define  CN_DEFAULT_SECONDVIDEO_1080P_FRAMERATE         25     //�ڶ�·��Ƶ��1080pĬ��֡��
// #define  CN_DEFAULT_SECONDVIDEO_720P_FRAMERATE          30     //�ڶ�·��Ƶ��720pĬ��֡��
#define	 CN_SECONDVIVEO_H264IKEYRATE				   2000    //�ڶ�·��ƵH264�ؼ�֡���

#define  CN_DEFAULT_VIDEO_VGA_FRAMERATE					20     //��Ƶ��VGAĬ��֡��
#define  CN_DEFAULT_VIDEO_D1_FRAMERATE					30     //��Ƶ��D1Ĭ��֡��

#define  CN_MIN_VIDEO_QUAL							   2      //��С��������
#define  CN_MAX_VIDEO_QUAL							   31      //�����������
#define  CN_VIDEO_IKEYRATE                             300    //�ؼ�֡���

//ͼ���������
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_BRIGHTNESS           16    //����
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_CONTRAST             16    //�Աȶ�
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_SATURATION           16    //ɫ�ʱ��Ͷ�

// #define CN_DEFAULT_PRIOM_ADJUSTIMAGE_BRIGHTNESS              128    //����
// #define CN_DEFAULT_PRIOM_ADJUSTIMAGE_CONTRAST                64    //�Աȶ�
// #define CN_DEFAULT_PRIOM_ADJUSTIMAGE_SATURATION              64    //ɫ�ʱ��Ͷ�

#define CN_DEFAULT_SECOND_ADJUSTIMAGE_BRIGHTNESS              16    //����
#define CN_DEFAULT_SECOND_ADJUSTIMAGE_CONTRAST                16    //�Աȶ�
#define CN_DEFAULT_SECOND_ADJUSTIMAGE_SATURATION              16    //ɫ�ʱ��Ͷ�

//add by wangqichang
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_NOISEREDUCTION      0    //��ʱδ֪--����--10
#define CN_DEFAULT_SECOND_ADJUSTIMAGE_NOISEREDUCTION    0    //��ʱδ֪--����--10
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_CHROMA              16    //��ʱδ֪--ͼ��ɫ��--20
#define CN_DEFAULT_SECOND_ADJUSTIMAGE_CHROMA             16    //��ʱδ֪--ͼ��ɫ��--20

// --------------- ����1080P/i,720--֡������ --------------- 
#define CN_HD_ORIGIN					 (u32)0
#define CN_HD_1080p_24                   (u32)1
#define CN_HD_1080p_25                   (u32)2
#define CN_HD_1080p_30                   (u32)3
#define CN_HD_1080p_50					 (u32)4//Ĭ��
#define CN_HD_1080p_60					 (u32)5
#define CN_HD_1080i_50                   (u32)6
#define CN_HD_1080i_60                   (u32)7
#define CN_HD_720p_50				     (u32)8
#define CN_HD_720p_60					 (u32)9
#define CN_576i_50						 (u32)10
#define CN_HD_1080p_29					 (u32)11
#define CN_HD_1080p_59					 (u32)12  
#define CN_HD_1080p_29_97				 (u32)13 //1080p 29.97fps
#define CN_HD_1080p_59_94				 (u32)14 //1080p 59.94fps

// --------------- VGA--Ƶ������ ---------------                
#define CN_HD_VGA_60                     (u32)0                 
#define CN_HD_VGA_75                     (u32)1                 
#define CN_HD_SVGA_60					 (u32)2 
#define CN_HD_SVGA_75					 (u32)3 
#define CN_HD_XGA_60					 (u32)4 
#define CN_HD_XGA_75					 (u32)5 
#define CN_HD_SXGA_60					 (u32)6 
#define CN_HD_WSXGA_60					 (u32)7 
#define CN_HD_WXGA1280x768_60			 (u32)8         
#define CN_HD_WXGA1280x768_75			 (u32)9         
#define CN_HD_WXGA1280x800_60			 (u32)10        
#define CN_HD_WXGA1280x800_75			 (u32)11        
#define CN_HD_WXGA1360x768_60			 (u32)12                                        
#define CN_HD_UXGA_60					 (u32)13                                
#define CN_HD_SXGAPLUS_60				 (u32)14
#define CN_HD_WXGA1366x768_60			 (u32)15  

//HD�ն˵���Ƶ����ڸ���
const int    CN_HD_MAX_AV_OUTPORT_NUM  = 4;            //�����ն˵������Ƶ����ڵĸ���

const int    CN_VIDEO_OUTPORT_NUM          = 4;    
const int    CN_INNERMATRIX_SCHEME_NUM     = 8;
const u32    CN_DVI_PORT_NUM               = 6;    

const u8     CN_ExVideoMoudle_None = 0;
const u8     CN_ExVideoMoudle_SDII = 1;
const u8     CN_ExVideoMoudle_SDIO = 2;

const u8     CN_DVI_MODE_HDMI  = 0;
const u8     CN_DVI_MODE_DVI  = 1;
const u8     CN_DVI_MODE_YPBPR = 2;
const u8     CN_DVI_MODE_VGA   = 3;

//��ʾ��Ϣ
#define	CN_WIN32_DEFAULT_SYMBOLPOINT_X                 20   //̨���Xλ��
#define	CN_WIN32_DEFAULT_SYMBOLPOINT_Y                 10   //̨���Yλ��

#define	CN_LINUX_DEFAULT_SYMBOLPOINT_X                 76   //̨���Xλ��
#define	CN_LINUX_DEFAULT_SYMBOLPOINT_Y                 56   //̨���Yλ��

#define CN_VGAOUTCFG_REFRESHRATE                       75   //8010c�����vga����video,��ˢ����

//FEC����
#define CN_FEC_CRCPACKNUM                              1  //fec��y�������
#define CN_FEC_DATAPACKNUM                             6  //fec��x�����ݰ�
#define CN_FEC_PACKLEN                                1408  //fec���а�����

//-----------------��������һ֡------------------
#define CN_HD_LastFrame					 (u32)0
#define CN_HD_BlueScreen                 (u32)1

#define CN_HD_BLUESCREEN_WAITTIME         5

//�����ش�����
//T2�汾
// #define	CN_INTERNET_LOSTPACKRESEND_FIRSTTIMESPAN    40       //��һ���ش�����   default 40
// #define CN_INTERNET_LOSTPACKRESEND_REJECTTIMESPAN   480         //���ڶ�����ʱ���� 
// #define CN_INTERNET_LOSTPACKRESEND_SECONDTIMESPAN   120         //�ڶ����ش�����
// #define CN_INTERNET_LOSTPACKRESEND_THIRDTIMESPAN    240         //�������ش�����
// #define CN_INTERNET_LOSTPACKRESEND_SENDBUFTIMESPAN  1500        //���ͻ���

#define	CN_LOSTPACKRESEND_FIRSTTIMESPAN    40       //��һ���ش�����   default 40
#define CN_LOSTPACKRESEND_REJECTTIMESPAN   480         //���ڶ�����ʱ���� 
#define CN_LOSTPACKRESEND_SECONDTIMESPAN   120         //�ڶ����ش�����
#define CN_LOSTPACKRESEND_THIRDTIMESPAN    240         //�������ش�����
#define CN_LOSTPACKRESEND_SENDBUFTIMESPAN  1500        //���ͻ���

#define	CN_DEFAULT_AUDIO_FILTERRATE         20         //��Ƶ�ĵ�ͨ����ͨ���˲�

//���ȶ���
const int    CN_MAX_LDAPSERVER_NAME_LEN   =  100;          //LDAP��������������󳤶�
const int    CN_MAX_H323ALIAS_LEN       =   64;            // �ն˱�����󳤶�
const int    CN_MAX_E164NUM_LEN         =   16;            // �ն�E164��󳤶�
const int    CN_MAX_UPDATASERVER_NAME_LEN =  64;           //��������������������󳤶�
const int    CN_MAXNUM_CALLADDR_RECORD  =   5;             //�����е�ַ��¼��

//��ũ��˵�����
#define  CN_MIC_CANONIN_NUM                  10



//Add by tanxiaodong 2012-12-22
//ά�������л�ȡ�������������ʺ궨��
#define NETINFO_PATH_IN_LINUX "/proc/net/dev"
#define NET_INFO_MAX_NUM     256
#define NET_ELEMENT_NUM      20
#define TRANSFER_BASE_NUM    10
#define NET_INFO_LINE_NUM    4

//ά����������ʾԴ����ӿڵĺ궨��
#define DEMO_OUTPUT_NAME_FST     "��ʾ��1"
#define DEMO_OUTPUT_NAME_SND     "��ʾ��2"
//End to add.
                        
const int    AID_CNMP_BEGIN        =   AID_MT_BGN;                        
const int    AID_CNMP_UE		     =	 AID_CNMP_BEGIN + 4;    	//ҵ��ӿ�ʵ��    


//���������û���Ŀ
#define MAX_USERNUM		128
#define MAX_CHARLENGTH		64

//Modified by tanxiaodong 2012-11-29.
//CNS���ӵ�TPad�����������Ϊ16��
#define MAX_CNC_USER 16

//����̨��ʱ�Ĺ̶�����ֵ

#define BANNER_BPM576_WIDTH    720  
#define BANNER_BPM576_HEIGHT   576

#define BANNER_BPM720_WIDTH    1280  
#define BANNER_BPM720_HEIGHT   720
#define BANNER_LOGO720_XPOS    67
#define BANNER_LOGO720_YPOS    50

#define BANNER_BPM1080_WIDTH   1920  
#define BANNER_BPM1080_HEIGHT  1080
#define BANNER_LOGO1080_XPOS    102
#define BANNER_LOGO1080_YPOS    76

#define BANNER_LOGO_BCOLOR  0
#define BANNER_LOGO_RCOLOR  255
#define BANNER_LOGO_GCOLOR  235
#define BANNER_LOGO_TRANSPARENCY  255
//���������ʵ��ֽڼ���ֵ
#define NET_SPEED_BYTE_BASE_NUM  2048

//End of the modification.

//�ն��ͺ�
const u32  TPSYSHARDWARETYPE_UNKNOWNMTMODEL   = 0;//(u32)emUnknownMtModel ;
const u32  TPSYSHARDWARETYPE_7920           = 27;//(u32)em7920_A ;  


// --------------- ��ƵĬ�ϲ���--------------- 
const u32 TP_VIDEO_PRIOME_FRAMERATE_DEFAULT = 60; //��Ƶ֡��
const u32 TP_VIDEO_MINI_FRAMERATE_DEFAULT = 30;
const u32 TP_VIDEO_MAX_KEYFRAMEINTERVER_DEFAULT = 3000; 
const u32 TP_VIDEO_PRIOM_MAX_CHANBITRATE = 8192;
const u32 TP_VIDEO_MINI_MAX_CHANBITRATE = 4096;
const u32 TP_VIDEO_MAX_QUANT_DEFAULT = 40;
const u32 TP_VIDEO_MIN_QUANT_DEFAULT = 20;
const u32 TP_VIDEO_WIDTH_DEFAULT = 1920;   
const u32 TP_VIDEO_HEIGHT_DEFAULT = 1080;
const u32 TP_VIDEO_PROFILE_DEFAULT = 1;
const u32 TP_VIEDO_AVGQPI_DEFAULT = 28;
const u32 TP_VIEDO_AVGQPP_DEFAULT = 28;
const u32 TP_VIDEO_DUAL_MAX_CHANBITRATE = 4096;
const u32 TP_VIDEO_DUAL_FRAMERATE_DEFAULT = 60;
const u32 TP_VIDEO_PRIOM_CAPEMRES_DEFAULT = 13;
const u32 TP_VIDEO_PRIOM_WXGACAPRES_DEFAULT = 20;
const u32 TP_VIDEO_DUAL_CAPEMRES_DEFAULT = 13;
const u32 TP_VIDEO_DUAL_WXGACAPRES_DEFAULT = 20;
const u32 TP_PADKEYFRAME_TIMER_DEFAULT = 30;
const u32 TP_PIPTIMER_DEFAULT = 6;
const u32 TP_VIDEO_PRIOM_DEFAULT_CHANBITRATE_HP = 2048;
const u32 TP_VIDEO_PRIOM_DEFAULT_CHANBITRATE = 2048;
const u32 TP_VIDEO_DUAL_DEFAULT_CHANBITRATE = 2048;

#define MEDIA_NUM                   2

#define TP_MAX_LOGOBMP_SIZE                153600 


const u16 TP_SERVER_PORT_DEFAULT = 5060;

//add for vcs
const u8 TP_MAX_VOLUME = 32;
const u8 TP_MCU_MAX_VOLUME = 248;
//end

#define TP_SAFE_DELETE( p ) if ( p != NULL ) { delete p; p = NULL; }
#define TP_SAFE_DELETE_ARRAY( p ) if ( p != NULL ) { delete []p; p = NULL; }

//t300Ĭ�ϻ᳡��
#define TP_MAINROOM_DEFAULT           "KEDACOM"
#define TP_ETHNET_IP_DEFAULT          "192.169.0.1"
#define TP_ETHNET_MAST_DEFAULT        "255.0.0.0"
#define TP_ETHNET_GATEWAY_DEFAULT     "0.0.0.0"


// --------------- �������--------------- 
const u16 TP_CONF_POLLEXPIRE = 20; //������ѯ���

#define TP_PRIMCHANNEL_CONNECT_DELAY_TIME 500

#define TP_CREATE_VIDEO_CODEC_DELAY_TIME  100

//����ϳɵ����ͨ����
const u8 TP_MAX_VMP_CHANNEL_NUM = 25;
#define TP_VMP_NAME  "����ϳ�"

#define TP_AGC_OFF  30
#define TP_AGC_ON   31
#define TP_ANS_OFF  10
#define TP_ANS_ON   11

#define TP_SPEECHEACTIVEKEEP_TIME  2 //������������ʱ��

#define TP_PLAYRING_TIME  5  //��������ʱ��

#define TP_VIDOE_BITRATEDECSRATIO  100
#define TP_VIDEO_BITRATEDECSRATIO_FORIPHEAD  80

//ȫ�������������
#define  MAX_PAN_NUM				4
#define  MAX_PANCAMNAME_LEN         255
#define  MAX_PRESET_NUM             16
//add end

#endif