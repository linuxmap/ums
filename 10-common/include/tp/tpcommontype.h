#ifndef _h_tpcommontype_h__
#define _h_tpcommontype_h__

//MTType begin.
#include "osp.h"

enum EmTPDevRegUpdateSer
{
	emDevInvalid = -1,
		emTPTPad_Win7,
		emTPTPad_Android,
		emTPTPad_IOS,
		emTPCns_T300A,
		emTPCns_T300B,
};

//��������
enum EmTPUpdateType  
{
	emTPUpdateForced,  //ǿ������
		emTPUpdateSelected  //ѡ������
};


/**********************************add enum begin**********************************/

enum EmWiFiLinkStat
{
	emWiFiIdle = 0,
	emWiFiConnecting,
    emWiFiConnectFailed,
    emWiFiConnected,
    emWiFiDisconnecting,
    emWiFiDisconnected
};

// enum EmWiFiLinkStatus
// {
// 	emWiFiIdle = 0,
//     emWiFiConnected,
//     emWiFiConnecting,
//     emWiFiConnectFailed,
//     emWiFiDisconnected,
//     emWiFiDisconnectFailed,
//     emWiFiDevicePullIn,
//     emWiFiDevicePullOut
// };

enum EmWiFiSelType
{
    emWiFiCfgSel = 0,
    emWiFiScanSel
};

enum EmWiFiNetType
{
    emWiFiAdHoc = 0,
    emWiFiInfra
};

enum EmWiFiEncryptType
{
    emWiFiEncryptNone = 0,
    emWiFiEncryptWep,
    emWiFiEncryptWpa,
    emWiFiEncryptWpa2
};

enum EmWiFiEncryptArithmetic
{
	emWiFiArithNone = 0,
	emWiFiArithWep40,
	emWiFiArithTkip ,
	emWiFiArithWrap,
	emWiFiArithAes,						/* aes */
	emWiFiArithWep104	
};

// VOD REJ Code 
//------------------------��Ϣ��REJ��-------------------------------------------
enum EmVODRejCode 
{	
	emVODNoReason = 0, // δ֪����
	emVODFileNotFound = 1, // �ļ�δ�ҵ�
	emVODPalyNotStarted = 2, //����δ��ʼ
	emVODMaxUser = 3, // �����û��Ѵﵽ�����������
	emVODUserNotExist = 4, // �û���������	
	emVODUserLogined = 5, // ���û��Ѿ���¼
	emVODInvalidedPassword = 6, // �������
	emVODMEDIAVODInvalidedFileNameType = 7, // Client <-- Server ,�ļ���Ϊ�ջ���ASF�ļ�
	emVODPlayBusy = 9, // Client <-- Server ,���ڷ�����һ�ε���������
	emConnectFailed = 10,
	emDisconnect = 11 ,// �����ж�
	emVODNoError      //�����ɹ�
};

//VOD ״̬
enum EmVODState
{
	emVODIdle         ,//����
	emVODLogin        ,//���ڵ�½
	emVODFileListQuery,//���ڻ�ȡ�ļ��б�
	emVODFileInfoQuery ,//���ڲ�ѯ�����ļ���Ϣ
	emVODPlay  ,//���ڲ���
	emVODPause    ,//��ͣ
	emVODStop  ,   //ֹͣ
	emVODSeek  ,   //ָ��λ�ò���
	emVODActiveEnd
};

//���
enum EmTextAlign
{
	emAlignLeft = 0,//����
	emAlignCenter,//����
	emAlignRight//����
};

enum EmRollMode
{
	emStatic = 0,
	emRight2Left,
	emDown2Up
};

enum EmRollSpeed
{
	emSlower = 0,
	emSlow,
	emNormal,
	emFast,
	emFaster
};

//����ֹͣλ����
enum EmStopBits
{
    em1StopBit =0,
    em1HalfStopBits=1,
    em2StopBits = 2
};



//����У��λ����
enum EmParityCheck
{
    emNoCheck = 0 ,//��У��
    emOddCheck =1 ,//��У��
    emEvenCheck =2,//żУ��
};

//��������
enum EmSerialType
{
    emRS232 = 0,
    emRS422 = 1,
    emRS485 = 2,
	emSerialTcpip =3,
	emRS422_1 = 4,
	emRS422_2 = 5,
	emRS422_3 = 6,
	emRSCom_1 = 7,
	emRSCom_2 = 8,
	emRSCom_3 = 9,
	emRSCom_4 = 10,
	emRSCom_5 = 11,
	emRSCom_6 = 12
};

//��������
enum EmLanguage
{
    emEnglish  = 0,
    emChineseSB = 1,
	emLangeEnd
};




//Э������
enum EmConfProtocol
{
	emH323  = 0, 
	emH320  = 1,
	emSIP   = 2,
	emSat   = 3, 
	emInvalidConfProtocel
};

//���뷽ʽ
enum EmEncodeMode
{
    emQualityFirst  = 0, 
    emSpeedFirst    = 1,
    
};

//�����ָ�����
enum EmLostPackageRestore
{
    emLPQualityFirst  = 0, 
    emLPSpeedSlow     = 1,
    emLPSpeedNormal   = 2,
    emLPSpeedFast     = 3,
};

//��������
enum EmMatrixType
{
	emMatrixInner   = 0, 
	emMatrixOuter   = 1,
	emMatrixVas     = 2,
};

//˫����ʾģʽ
enum EmDualVideoShowMode
{
    emDualVideoOnSigleScreen  =0,//����˫��
    emEachVideoOwnScreen      =1,//˫��˫��
	emTripleVideoOnSingleScn  =2 //��������
};

//��ʾ����
enum EmDisplayRatio
{
	emDR4to3      = 0, //4:3
	emDR16to9     = 1, //16:9
	emDRAuto      = 2, //0:0
};

//��Ƶ����
enum EmVideoType
{
   emPriomVideo = 0 ,//����Ƶ
   emSecondVideo = 1//�ڶ�·��Ƶ
};


//��Ƶ��ʽ����
enum EmVideoStandard
{
    emPAL  =0 ,
    emNTSC = 1 ,
//    emSECAM = 2
};

//��ƵԴ����
enum EmVideoInterface
{
    emVidVGA    = 0, 
    emSVideo = 1,
    emCVideo = 2,
};

//�ն���Ƶ�˿�
enum EmMtVideoPort
{
	//hd2.0��ƵԴ����
	emMtVGA   =0 , //VGA 
	emMtSVid    , //S ����
	emMtPC      , //PC
	emMtC1Vid   ,  //C1����   DVI 1
	emMtC2Vid   ,  //C2����   DVI 2
	emMtC3Vid   ,  //C3����   DVI 3
	emMtC4Vid   ,  //C4����   c
	emMtC5Vid   ,  //C5����   sdi 1
	emMtC6Vid   ,  //C6����   sdi 2

	emMtExternalVid = 10,//���þ���ӳ���ʼֵ
	emMtVideoMaxCount = 74, //���֧����ƵԴ����
	emMtVidInvalid = 255 
};

//Ӧ��ʽ����
enum EmTripMode
{
    emTripModeAuto      =0,  //�Զ�
    emTripModeManu      =1,  //�ֶ� 
	emTripModeNegative  =2,   //�ܾ����ر�
};

//̨������
enum EmLabelType
{
    emLabelAuto    =0,   //�Զ�
    emLabelUserDef =1,  //�Զ���
    emLabelOff     =2  //�ر�
};

//E1��·�������
enum EmDLProtocol
{
    emPPP   = 0, 
    emHDLC  = 1,
    emPPPOE = 2,
    emMP    = 3
};

//E1��֤����
enum EmAuthenticationType
{
    emPAP  = 0,
    emCHAP = 1
};

//֡�ʵ�λ����
enum EmFrameUnitType
{
    emFrameSecond =0,
    emSecondFrame =1
};

// ý������
enum EmMediaType
{
	emMediaVideo = 1, //��Ƶ
	emMediaAudio = 2, //��Ƶ
	emMediaAV    = 3, //��Ƶ����Ƶ
};


//��ƵЭ������
enum EmVideoFormat
{
    emVH261     = 0,
    emVH262     = 1,//MPEG2
    emVH263     = 2,
    emVH263plus = 3,
    emVH264     = 4,
    emVMPEG4    = 5,

	emVEnd		
};

//��ƵЭ������
enum EmAudioFormat
{
    emAG711a  = 0,
    emAG711u  = 1,
    emAG722   = 2,
    emAG7231  = 3,
    emAG728   = 4,
    emAG729   = 5,
    emAMP3    = 6,
	emAG721   = 7,
	emAG7221  = 8,
	emAG719   = 9,
	emAMpegAACLC =10,
	emAMpegAACLD = 11,

	emAEnd	 
};


//�ֱ�������
enum EmVideoResolution
{
    emVResolutionAuto     = 0,   //�Զ�
    emVSQCIF              = 1,   //SQCIF88x72
	emVQCIF               = 2,   //QCIF176x144
    emVCIF                = 3,   //CIF352x288
    emV2CIF               = 4,   //2CIF352x576
    emV4CIF               = 5,   //4CIF704x576
    emV16CIF              = 6,   //16CIF1408x1152

	emVHD480i720x480      = 7,   //480i720x480
	emVHD480p720x480      = 8,   //480p720x480
	emVHD576i720x576      = 9,   //576i720x576
	emVHD576p720x576      = 10,  //576p720x576

	emVHD720p1280x720     = 11,  //720p1280x720
	emVHD1080i1920x1080   = 12,  //1080i1920x1080
	emVHD1080p1920x1080   = 13,  //1080p1920x1080
	
		
	emVGA352x240          = 14,  //352x240
	emVGA704x480          = 15,  //704x480
	emVGA640x480          = 16,  //VGA640x480
	emVGA800x600          = 17,  //SVGA800x600
	emVGA1024x768         = 18,  //XGA1024x768
	emVGA1280x768         = 19,  //WXGA1280x768
	emVGA1280x800         = 20,  //WXGA1280x800
	emVGA1366x768         = 21,  //WXGA1366x768
	emVGA1280x854         = 22,  //WSXGA1280x854
	emVGA1440x900         = 23,  //WSXGA1440x900
	emVGA1280x1024        = 24,  //SXGA1280x1024
	emVGA1680x1050        = 25,  //SXGA+1680x1050
	emVGA1600x1200        = 26,  //UXGA1600x1200
	emVGA1920x1200        = 27,  //WUXGA1920x1200

	emVSQCIF112x96        = 28,
	emVSQCIF96x80         = 29,
	emV320x192            = 30,
	emV432x240            = 31,
	emV480x272            = 32,
	emV640x368            = 33,
	emV864x480            = 34,
	emV960x544            = 35,
	emV1440x816           = 36,

	emVResEnd = 50,
};

//QOS���ͷ���
enum EmQoS
{
   emDiffServ  = 0,      //���ַ���
   emIPPrecedence  = 1  //IP����
};

//TOS ����
enum EmTOS
{
	emTOSNone        = 0,//��ʹ��
	emTOSMinCost     = 1,//��С����
	emTOSMaxReliable = 2,//��߿ɿ���
	emTOSMaxThruput  = 3,//���������
	emTOSMinDelay    = 4,//��С�ӳ�
};


//λ��
enum EmSite
{
    emLocal = 0,  //����
    emRemote    //Զ��
};

//����10��ͨ��
enum EmChanType
{
	emChanSendAudio,
	emChanSendPrimoVideo,
	emChanSendSecondVideo,
	emChanSendFecc,
	emChanSendT120,

	//����ͨ��
	emChanRecvAudio,
	emChanRecvPrimoVideo,
	emChanRecvSecondVideo,
	emChanRecvFecc,
	emChanRecvT120,

	emChanTypeEnd	
};

//���������������
enum EmCodecComponent
{
	emPriomVideoEncoder  =0,
	emPriomVideoDecoder  ,

	emSecondVideoEncoder ,
	emSecondVideoDecoder ,

	emAudioEncoder ,
	emAudioDecoder ,
	emCodecComponentEnd,
};

//�ն��ͺ�
enum EmMtModel
{
	emUnknownMtModel=0,
	emPCMT  =1    ,//�����ն�
	em8010      ,
	em8010A     ,
	em8010Aplus ,//8010A+
	em8010C     ,
	em8010C1    ,//8010C1
	emIMT       ,
	em8220A     ,
	em8220B     ,
	em8220C     ,
	em8620A     ,
	emTS6610E   ,
	emTS6210    ,
	em8010A_2   ,
	em8010A_4   ,
	em8010A_8   ,
	em7210      ,
	em7610      ,
	emTS5610    ,
	emTS6610    ,
	em7810      ,
	em7910      ,
	em7620_A    ,
	em7620_B    ,
	em7820_A	,
	em7820_B	,
	em7920_A	,
	em7920_B	

};
// << �ļ�ϵͳ���� >>
enum EmFileSys
{
	emRAWFS=1,//raw file system [ramdisk + rawblock + tffs]
	emTFFS  //tffs
};
//�����㷨
enum EmEncryptArithmetic
{
	emEncryptNone = 0,
	emDES         = 1,
	emAES         = 2,
	emEncryptAuto = 3,

	emEncryptEnd
	
};

//����
enum EmAction
{
    emActStart,
    emActStop,
    emActPause,
    emActResume,
};

//�ն�ʹ�ܲ���
enum EmOptRet
{
	emEnable,
	emDisable,
};


//����ģʽ
enum EmConfMode
{
	emP2PConf = 0,//��Ե����
	emMCCConf = 1 //������
};


//��ַ����
enum EmMtAddrType
{
	emIPAddr =0,
	emE164   ,
	emH323id ,
	emDialNum,
	emSipAddr	
};

//���Ʒ���
enum EmDirection
{
	emUP   =0,
	emDown   ,
	emLeft   ,
	emRight 
};

//����״̬
enum EmCallState
{
	emCS_Idle  ,
	emCS_Calling ,      //���ڷ������
	emCS_P2P ,      //��Ե����
	emCS_MCC ,      //������
	emCS_Hanup        //�Ҷ�
};


//����״̬
enum EmCallSiteState
{
	emCSS_IDLE,
	emCSS_Init ,
	emCSS_Waiting ,      //���ڷ������
	emCSS_Connected ,      //��Ե����
	emCSS_Failed
};

//����ģʽ
enum EmTransMode
{
	emUnicast,  //����
	emBroadcast, //�㲥
	emMulticast //�鲥
};

//˫��Դ����
// enum EmDualSrcType
// {
//     emDualVGA = 0,
// 	emDualVideo = 1,
// 	emDualPC = 2
// };



enum EmMtInstType
{
	emMtService = 0 ,
	emMtUI          ,
	emMtConsole     ,
	emMtH323Service ,
	emMtH320Service ,
	emMtSipService  ,
	emMtH323StackIn ,
	emMtH323StackOut,
	emMtMP          ,
	emMtDevice      ,
	emMtAgent       ,
	emMtSipStackIn  ,
	emMtSipStackOut ,
};

//����ϳɷ����
enum EmVMPStyle
{
    emVMPDynamic       =   0 ,  //��̬����(���Զ��ϳ�ʱ��Ч)
    emVMPOne         =   1 ,  //һ����
    emVMPVTwo        =   2 ,  //�����棺���ҷ� 
    emVMPHTwo        =   3 ,  //������: һ��һС
    emVMPThree       =   4 ,  //������
    emVMPFour        =   5 ,  //�Ļ���
    emVMPSix         =   6 , //������ 
    emVMPEight       =   7 ,  //�˻���
    emVMPNine        =   8 ,  //�Ż���
    emVMPTen         =   9 ,  //ʮ����
    emVMPThirteen    =   10,  //ʮ������
    emVMPSixteen     =   11,  //ʮ������
    emVMPSpecFour    =   12,  //�����Ļ��� 
    emVMPSeven       =   13,  //�߻���
	emVMPSpecThirteen  =   14,  //����ʮ�����棨���ڻ�ΪMCU��
	emVMPTwenty      =   15,  //����MPU�Ķ�ʮ���棨ֻ���ڸ���MPU��
};


//����ϳɳ�Ա���Ͷ���
enum EmVMPMmbType
{
    emVMPMmbMCSspec    = 1,  //���ָ�� 
    emVMPMmbSpeaker    = 2,  //�����˸���
    emVMPMmbChairman   = 3,  //��ϯ����
    emVMPMmbPoll       = 4,  //��ѯ��Ƶ����
    emVMPMmbVAC        = 5,	//��������(��ز�Ҫ�ô�����)
};

//����Ϣҵ������
enum EmSMSType//MS
{
	emSMSSingleLine  = 0,  //����Ϣ
	emSMSPageTitle   = 1,  // ��ҳ��Ļ
	emSMSRollTitle   = 2,  // ������Ļ
	emSMSStaticTitle = 3,  // ��̬��Ļ
};


enum EmMtFile
{
    emMtFileBegin  = 0,//�ն��ļ����Ϳ�ʼ
	emMtConfigFile   =1,//�����ļ�
	emMtOldConfigBakFile     ,//�������ļ�����
	emMtDebugConfiFile, //���������ļ�
	emMtCameraCommandFile,//����ͷ�����ļ�
	emMtCameraPresetPostionFile,//����ͷԤ��λ�����ļ�
	emMtExternMaxtrixCommandFile,//���þ����������ļ�
	emMtExternMaxtrixPortNameFile,//���þ���˿����ļ�
	emMtInnerMaxtrixSchemeFile,//���þ��󷽰��ļ�
	emMtStreamMediaHtmlFile,//��ý����ҳ�ļ�
	emMtResourceFile,//�ն���Դ�ļ�
	emMtZipResourceFile,//ѹ���ն���Դ�ļ�
	emMtSymbolFile,//�ն�̨��ͼƬ�ļ�
	emMtBannerFile,//�ն˺���ļ�
	emMtStaticPicFile,//�ն˾�̬ͼƬ�ļ�
	emMtResInBin,//Bin�ļ��е���Դ�ļ�
	emMtAddressBookEx,//��չ��ַ���ļ�
	emMtUpdateSysFile,//�汾�����ļ�
	emMtMinitorFile, //�����ļ�
	emMtZipFile,//Ӧ�ó���
	emMtHintFile,//������ʾ��Դ�ļ�
	emMtKeyFile, //mclicense�ļ�
    emMtInnerPxyFile,//���ô�������������ļ�
	emMtThreadBlockFile,//�߳�������Ϣ�ļ�
	emMtLogFile,//��־�ļ�
	emMtUserWordFile,//�û��ʿ��ļ�
	emMtKdvLog, //��־�����ļ�
	emMtFileEnd //�ն��ļ����ͽ���
};
typedef u32   u32_ip;

enum EmCallRate
{
	emRaten64 = 0,							/*(0)64kbps*/
	emRaten2m64,							/*(1)2��64kbps*/
	emRaten3m64,							/*(2)3��64kbps*/
	emRaten4m64,							/*(3)4��64kbps*/
	emRaten5m64,							/*(4)5��64kbps*/
	emRaten6m64,							/*(5)6��64kbps*/
	emRater384,							/*(6)384kbps*/
	emRater1536,							/*(7)1536kbps*/
	emRater1920,							/*(8)1920kbps*/
	emRater128,							/*(9)128kbps*/
	emRater192,							/*(10)192kbps*/
	emRater256,							/*(11)256kbps*/
	emRater320,							/*(12)320kbps*/
	emRater512,							/*(13)512kbps*/
	emRater768,							/*(14)768kbps*/
	emRater1152,							/*(15)1152kbps*/
	emRater1472,							/*(16)1472kbps*/
	/*(ע��V2.0�汾������3M��4M��6M��8M����)*/
	emRater3M,							/*(17)3M(2880kbps)*/
	emRater4M,							/*(18)4M(3840kbps)*/
	emRater6M,							/*(19)6M(5760kbps)*/
	emRater8M,							/*(20)8M(7680kbps)*/
	emRaterLastOne
};


//PC windows �ɼ���ʽ
enum EmPCCapFormat
{
	emCapPCFrameBMP  = 0,//RGB24λͼ;
	emCapPCFrameUYUY = 1,//yuv4:2:2��ʽ
	emCapPCFrameI420 = 2,//yuv4:2:0��ʽ
};

//���л���ʾģʽ
enum EmPiPMode
{
	emPiPClose   = 0,//���л��ر�
	emPiPRightBottom ,//���л�С������ʾ�����½�
	emPiPLeftBottom  ,//���л�С������ʾ�����½�
	emPiPLeftTop     ,//���л�С������ʾ�����Ͻ�
	emPiPRightTop    ,//���л�С������ʾ�����Ͻ�
};
// DVB Component
enum EmDVBComponent
{
	emDVBEncoder = 0,
	emDVBPriomVideoDecoder,
	emDVBSecondVideoDecoder
};
enum EmUIPosion
{
	emMT = 0,
	emMTC = 1
};
//���йҶ�ԭ��
enum EmCallDisconnectReason
{
	emDisconnect_Busy = 1   ,//�Զ�æ
	emDisconnect_Normal     ,//�����Ҷ�
	emDisconnect_Rejected   ,//�Զ˾ܾ�
	emDisconnect_Unreachable ,//�Զ˲��ɴ�
	emDisconnect_Local       ,//����ԭ��
	emDisconnect_Nnknown      //δ֪ԭ��
};


//MC ��ģʽ
enum EmMCMode
{
	emMcSpeech  ,//�ݽ�ģʽ
	emMcDiscuss ,//����ģʽ
	emMcModeEnd
};


//��Ƕmc�Ļ���ϳɷ��
enum EmInnerVMPStyle
{
    emInnerVMPAuto = 0,
	emInnerVMPOne,
	emInnerVMPTwo,
	emInnerVMPThree,
	emInnerVMPFour,
	emInnerVMPFive,
	emInnerVMPSix,
	emInnerVMPTwoBigLittle,
	emInnerVMPThreeBigLittle,
	emInnerVMPFourBigLittle,
	emInnerVMPEnd
};

//��Ƕmc�Ľ����������
enum EmVMPComponent
{
	emVMPDecNull = 0,
	emVMPDec1th,
	emVMPDec2th,
	emVMPDec3th,
	emVMPDec4th,
	emVMPDec5th,
	emVMPDecLocal,
	emVMPEnd
};


//pcmt��ƵԴ����
enum EmCapType
{
   emAudioOnly = 1, //
   emCameraOnly,
   emACBoth,
   emDesktopOnly,
   emADBoth,
   emFileAVBoth  
};
//pppoe״̬
enum EmPPPoEState
{
	emFree,
	emLinking,
	emLinkup,
	emLinkdown,
	emUserError,
	emTimeOut,
	emAgentError
};

enum EmDhcpState
{
	emDhcpFree,
	emDhcpLinkup,
	emDhcpLinkdown,
};

enum EmAddrGroupOptType
{
    emCallIn,
	emCallOut,
	emUserDef,
	emTemplate,
	emSiteCall,
	emMissed,
	emUserDefExt0,
	emUserDefExt1,
	emUserDefExt2,
	emUserDefExt3,
	emUserDefExt4,
	emUserDefExt5,
	emInvalid
};

enum EmHotKeyType
{
	emApplySpeak,
	emApplyChair,
	emPrevPage,
	emNextPage,
	emBack,
	emLoop,
	emHotkeyEnd,
	emAEC,
	emDial,
};

enum EmMtOSType
{
	emWindows,
    emVxworks,
	emLinux
};

enum EmFxoState
{
    emFxoIdle,
    emFxoCalling, 
    emFxoConnect,
};

// ������������С����
enum EmMtLoudspeakerVal
{
	emLoudspeakerLow = 0,
	emLoudspeakerMiddle,
	emLoudspeakerHigh,
};

// �ش�ʱ��ѡ�����������
enum EmNetType
{
	emInternet = 0,
	emSpecial,
	emVPN,
};

//T2�ն�ϵͳ����״̬��־
enum EmSysRunSuccessFlag
{	
	emSysNoUpdateOperation = 0,
	emSysUpdateVersionRollBack,
	emSysUpdateVersionSuccess,
	emSysSetUpdateFlagFailed,
};

//mcu֪ͨ�ն˵���Ϣ����  
enum EmMcuNtfMsgType
{
	emMsgNoneNtf =0,
	emMsgBePolledNextNtf,
	
};




struct TDATAINFO
{
	//��������
	int type ;
	//�������ʹ�С
	int size ;
	//���ݸ���
	int arraysize;
	//���ݵ�ַƫ����
	int offset;
	//��Ա��������
	char* member;
};

struct TENUMINFO
{
	char* descrip;
	int   val;
};

// �ն�Ӳ���Զ����������� add by wangliang 2007/02/05
enum EmAutoTestType 
{
    emAutoTestTypeBegin,            //�������Ϳ�ʼ
        
    emAutoTestEth0Func,             //����0���ܲ���
	emAutoTestEth1Func,             //����1���ܲ���
	emAutoTestE1Func,               //E1���ܲ���
    emAutoTestAudioLoopBackFunc,    //��Ƶ���ع��ܲ���
    emAutoTestVideoLoopBackFunc,    //��Ƶ���ع��ܲ��� - C����  
	emAutoTestSDI1InAllOutFunc,     //����������ԣ�SDI1����
	emAutoTestSDI2InAllOutFunc,     //����������ԣ�SDI2����
	emAutoTestDVI1InAllOutFunc,     //����������ԣ�DVI1����
	emAutoTestDVI2InAllOutFunc,     //����������ԣ�DVI2����
	emAutoTestDVI3InAllOutFunc,     //����������ԣ�DVI3����
	emAuotTestCInAllOutFunc,        //����������ԣ�C��������
	emAutoTestDVI1InAllOutFunc_YPbPr,    //����������ԣ�DVI1��������
	emAutoTestDVI1InAllOutFunc_OSDYPbPr, //����OSD����������DVI1
	emAutoTestBluerayHDMIFunc,		//����DVD������ӿڽ��ն�HDMI-1�������
	emAutoTestBluerayHDMI2Func,     //����DVD������ӿڽ��ն�HDMI-2�������
	emAutoTestBluerayHDMI3Func,     //����DVD������ӿڽ��ն�HDMI-3�������
	emAutoTestBluerayRCAFunc,       //����DVD������ӿڽ��ն�RCA���������������
	emAutoTestCanonMICFunc,			//��ũMIC����
	emAutoTestDigMICFunc,			//����MIC����
    emAutoTestLoudspeakerFunc,      //���������ܲ���
    emAutoTestCameraRotaFor232Func, //232����ͷת������
	emAutoTestCameraRotaFor485Func, //485����ͷ����
    emAutoTestRTCFunc,              //RTC���ܲ���
    emAutoTestLightFunc,            //ָʾ�Ʋ���
    emAutoTestRemoteCtrlFunc,       //����ӿڹ��ܲ���
    emAutoTestSetDefault,           //�ָ����Ա�־Ĭ��ֵ
	emAutoTestRebootSysFunc,		//�����ն˲���

    emAutoTestTypeEnd               //�������ͽ���
};

enum EmGKRegFailedReason
{
	emNone,
	emGKUnReachable,
	emInvalidAliase,
	emDupAlias,
	emInvalidCallAddress,
	emResourceUnavailable,
	emUnknown
};

enum EmSleepState
{
	emSleepFail, 
	emWaitSleeping,
	emSleeping, 
	emSleeped, 
	emWaking, 
	emWakeup, 
	emWaitWaking
};

enum EmMtAppName
{
	emMtAgentApp = 0,
	emMtServiceApp,
	emMtGuardApp,
	emMtUEApp,
	emMtStackInApp,
	emMtStackOutApp,
	emMtRcpApp,
	emMtH320StackApp,
	emMtRcSimApp,
	emMtMcApp,
	emMtSnmpApp,
	emMtConfigApp,
	emMtUIApp,
	emMtDeviceApp,
	emMtCodecApp,
	emMtConsoleApp,
	emMtSysApp,
	emMtH323ServiceApp,
	emMtH320ServiceApp,
	emMtSipServiceApp,
	emMtDvbApp,
	emMtDvbssnApp,
	emMtVodClientApp,
	emMtPcdualvideoApp,
	emMtUpgradeApp,
	emMtbApp,
	emMtAutotestApp,
	emMtAutotestClientApp,
	emMtRemoteSimApp,
	emMtThreadDetectApp,
	emMtLogRecvApp,
	emMtLogIOApp,
	emMtProxyClientApp,
	emMtSipStackInApp,
	emMtSipStackOutApp,
	emMtSatServiceApp,
	emMtTpRegApp,
	emMtAppEnd = 49,
};

enum HD_PORT_MASK
{
	//PORT_HDMI =  0x01,
	//PORT_SDI =   0x02,
	PORT_SDI =  0x01,
	PORT_HDMI =   0x02,	
	PORT_YPrPb1 = 0x04,
	PORT_YPrPb2 = 0x08,	
	PORT_VGA = 0x10,
	PORT_C0 = 0x20,
};

enum EmHDAudPortIn
{
	emAudInCL  = 0,
	emAudInCR,
	emAudInCanonL,
	emAudInCanonR,
	emAudInHDMI1,
	emAudInHDMI2,
	emAudInHDMI3,
	emAudInMic1,
	emAudInMic2,
};
enum EmHDAudPortOut
{
	emAudOutCCanon  = 0,
	emAudOutHDMI1,
	emAudOutHDMI2,
	emAudOutHDMI3,
	emAudOutReproducer,
};

//��־�Ƿ��
enum EmLogStatus
{
	emLogClose = 0,
		emLogOpen,
};

//��־�������
enum EmLogExportResult
{
	emLogExportFailed = 0,	//ʧ��
	emLogExportSuccess,     //�ɹ�
	emLogExportNoDisk,		//û�в���"U"��
	emLogExportNoFile,		//û����־�ļ�
	emLogExportTransing,	//���豸���ڽ����ļ�����
};

enum EmFecModeType
{
	 emMTFECTYPENONE  =				0x00,
	 emMTFECTYPERAID5 =				0x01,
	 emMTFECTYPERAID5INTERLEAVE =	0x02,
	 emMTFECTYPERAID6 =				0x03,			//������ʱ�������������
};

enum EmLabelPosType
{ 
	emTopLeft      = 0,
	emTopRight     = 1,
	emBottomLeft   = 2,
	emBottomRight  = 3
};

enum EmMtcBoxCallIndex
{
    emShortCutCall1 = 0,
	emShortCutCall2 = 1,
	emShortCutCall3 = 2,
	emShortCutCall4 = 3 
};

enum EmSipRegFailedReason
{
	emLocalNormalUnreg = 0,
	emInvalidUserNameAndPassword,
	emRegistrarUnReachable,
	emInvalidAlias,
	emUnknownReason
};
/*ͨ����״̬*/
enum EMtRecChnnlState
{
	STATE_IDLE       = 0,	  /*������һ��δ��ͨ��*/
		
		STATE_RECREADY   = 11,	  /*׼��¼��״̬  */
		STATE_RECORDING  = 12,	  /*����¼��  */
		STATE_RECPAUSE   = 13,	  /*��ͣ¼��״̬*/
		
		STATE_PLAYREADY  = 21,	  /*׼������״̬ */
		STATE_PLAYREADYPLAY = 22,   /*���ò���׼��״̬*/
		STATE_PLAYING    = 23,	  /*���ڻ򲥷�*/
		STATE_PLAYPAUSE  = 24,	  /*��ͣ����*/
		STATE_FF         = 25,	  /*���(������ͨ����Ч)*/
		STATE_FB         = 26	  /*����(������ͨ����Ч)*/
};

/*ͨ�����Ͷ���*/
enum EMtRecChnnlType
{
	TYPE_UNUSE      =  0,	/*δʼ�õ�ͨ��*/
		TYPE_RECORD     =  1,	/*¼��ͨ��  */   
		TYPE_PLAY       =  2	/*����ͨ��  */
};

//¼��ʽ
enum EMtRecMode
{
	MODE_SKIPFRAME = 0,//��֡¼��
		MODE_REALTIME  = 1  //ʵʱ¼��
};

enum EMtRecEnum{
	MT_MAXNUM_RECORDER_CHNNL = 32,
		MT_MAXLEN_RECORD_NAME = 64,
		MT_MAXLEN_CONFNAME = 64,
		MT_RECLIST_PACKSIZE =16,
		MT_MAX_REC_NAME = 128
};
enum EmMtRegResult
{
	emMtRegSuccess = 1,
	emMtRegPosError,
	emMtRegTimeOut
};
//MTType end.

enum EmTpRet
{
	tp_Ret_FAILED,
	tp_Ret_Success,
};


//HDU PLAY NACK�Ĵ���ԭ��
enum EmTpHduPlayNackReason
{
	em_hdu_play_success,
	em_Hdu_Invalid_Index,	//��Ч��λ������
	em_Hdu_Invalid_ID,		//��Ч��ID
	em_Hdu_No_Reged,		//HDUδע��

	em_Hdu_Illegal,			//��Ч��hdu
	em_Alias_Illegal,		//��Ч�ı���
	em_Monitor_Fail,		//��ǽʧ��
	em_Hdu_PlayNack,		//����ǽ�������ܾ�
	em_Same_Alias,			//����
	em_Same_Info,			//��ͬ����Ϣ
	em_unknown,				//δ֪�Ĵ���

};

enum EmTpHduSetVolRes
{
	em_hdu_SetVol_Success,
	em_hdu_SetVol_Invalid_Index,
	em_hdu_SetVol_UnReg,    
	em_hdu_SetVol_VmpChan,  // �໭��ϳ�ģʽ���ܵ�������
};

enum EmTpHduChangeChanModeRes
{
	em_hdu_change_mode_success = 0,
	em_hdu_change_mode_error_index, // ��Ч��ͨ��
	em_hdu_change_mode_error_param, // vmp mode��������
	em_hdu_change_mode_error_regstate, // ͨ��δע��
	em_hdu_change_mode_error_onlyoneVmp, // ����ǽ����ͨ��ֻ����һ����vmpģʽ
	em_hdu_change_mode_error_workingstate, // ͨ�����ڷ�æ״̬
	em_hdu_change_mode_error_fromhdu,   // hdu�����л�ģʽ����

};

//��¼��Ϣ
enum EmTpLoginUmsRet
{
	tp_LoginUms_sucess,
	tp_LoginUms_NameError,	//�û�������
	tp_LoginUms_PwdError,	//�������
	tp_LoginUms_MaxLogin,	//�ﵽ�û���¼����
	tp_LoginUms_Logged,		//�û��Ѿ���¼
	tp_LoginUms_SysIniting,	//ϵͳ���ڳ�ʼ��
	tp_LoginUms_steals_sucess, //���ϳɹ�
	tp_LoginUms_steals_quit,    //��������
};

//��������
enum EmTpAliasType
{
	tp_Alias_Unknow,
	tp_Alias_e164,
	tp_Alias_h323,
	tp_Alias_IP,
};

//��������
enum EmTpOprType
{
	tp_OprType_Add,			//����
	tp_OprType_Del,			//ɾ��
	tp_OprType_Update,		//�޸�
	tp_OprType_NULL,		//���
};

//��ӻ���Ļ᳡
enum EmConfAddEpRet
{
	TP_ConfAddEpRet_Unknow,
	TP_ConfAddEpRet_Success,
	TP_ConfAddEpRet_MaxNum,
	TP_ConfAddEpRet_AliasReapeat,
	TP_ConfAddEpRet_ParamError,
	
};

//�ؼ�֡���
enum EmTpIFrameCheckType
{
    TP_IFrameCheck_Speaker,				//��ⷢ����
	TP_IFrameCheck_SingleSpeaker,		//
	TP_IFrameCheck_Poll,				//��ѯ����
	TP_IFrameCheck_ChairWait,			//��ϯ����ʱ���л������������ˣ���ϯ�ļ��
	TP_IFrameCheck_Dis					//B4����ƽ��
};

//��������
enum EmTPEncryptType
{
    emTPEncryptTypeNone = 0,
	emTPEncryptTypeDES  = 1,
	emTPEncryptTypeAES  = 2,
	emTPEncryptTypeH239 = 3,
	
	emTPEncryptTypeQtEverySecond	= 100,	// һ��һ��///
	emTPEncryptTypeQtEveryMinute,	// һ��һ��
	emTPEncryptTypeQtEveryConf,	// һ��һ��
};

//�ǶԳ���ʱ�����ն˽��շ���
enum EmTPRcvAlignType
{
	emTPRcvAlignTypeMidAlign,	//�м����
};
//���н��
enum EmCnsCallReason	
{
	EmCnsCallReason_success,
	EmCnsCallReason_hungup,			//���عҶ�
	EmCnsCallReason_Unreachable,	//�Զ˲����ߣ��޷�����
	EmCnsCallReason_resourcefull,	//�Զ��޿�����Դ
	EmCnsCallReason_dstnotfind,		//Ŀ�겻����
	EmCnsCallReason_Busy,			//�Զ�æ
	EmCnsCallReason_Local,			//����ԭ��
	EmCnsCallReason_NoConf,			//���鲻����
	EmCnsCallReason_Exist,			//�Զ����ڱ�������
	EmCnsCallReason_Rejected,		//�Զ˾ܾ�
	EmCnsCallReason_peerhungup,		//�Զ˹Ҷ�
//	EmCnsCallReason_AlreadyDual,    //�Զ���˫��
	EmCnsCallReason_Abnormal,       //���ص��߹Ҷ�
	EmCnsCallReason_PeerAbnormal,   //�Զ˵��߹Ҷ�
	EmCnsCallReason_ConfOver,	//�������
	EmCnsCallReason_cncallexception,	//����ģ��(cncall)����
	EmCnsCallReason_ConfExist,		//�����Ѵ���
	EmCnsCallReason_StreamEncryptFail,
	EmCnsCallReason_unknown,  
	
		//QT
    EmCnsCallReason_RegSerUnreachable,       //ע����������ɴ�
    EmCnsCallReason_AliasNotFound,      //����������
    EmCnsCallReason_StreamEncryptTypeNotEqual,      //��������֧�ֵ��������ܷ�ʽ��һ��
    EmCnsCallReason_GetSignalEncryptKeyFailed,		//��ȡ����������Կʧ��
    EmCnsCallReason_AutoGetRegSerAddrFailed,   //IP����ʱ��ȡע���������ַʧ��
    EmCnsCallReason_QTDevConnectionBroken,   //�����ն˵���
    EmCnsCallReason_CallFull,   //���о������(���ܴ��ں��о��δ�ͷŵ�����)
    EmCnsCallReason_QTDevConnectionBrokenPeer,
};

enum EmTPChannelReason
{
	emTPChannelReasonBegin,
	emTPChannelDisconnectNormal,
	emTPDualOffLine,
	emTPForceStop,  //����˫��
	emTPDualNotSend
};


//CNS���ͣ�
enum EmTpCnsType
{
	tp_CnsType_Unkonw,
	tp_CnsType_FiveScreen_FiveSpeeker,
	tp_CnsType_FiveScreen_ThreeSpeeker,
	tp_CnsType_ThreeScreen_ThreeSpeeker,
	tp_CnsType_OneScreen_OneSpeeker,
};


//CNSע��UMSʧ������
enum EmTpCnsRegUms
{
	tp_CnsRegRet_Unknow,
	tp_CnsRegRet_Success,		//�ɹ�
	tp_CnsRegRet_MaxRegNum,		//ע����
	tp_CnsRegRet_MaxAliasNum,	//ע����
	tp_CnsRegRet_MsgError,		//ע����Ϣ����
	tp_CnsRegRet_AliasRepeat,	//�����ظ�
	tp_CnsRegRet_UnReg,			//ɾ��ʱ��δ�ҵ�ɾ����¼
	tp_CnsRegRet_SysError,		//APP����
	tp_CnsRegRet_NotFind,		//����ʧ��
	tp_CnsRegRet_Fail,          //����ʧ��
	tp_CnsRegRet_Unreachable,   //���������ɴ�
	tp_CnsRegRet_UnRegister,    //δע��
	tp_CnsRegRet_E164Repeat,    //E164���ظ�
	tp_CnsRegRet_NameDup,       //����������ظ�       
};



//����ģ��������
enum EmTpConfTemplateRet
{
	TP_ConfTemplate_UnKonw,
	TP_ConfTemplate_TmpUpIng,
	TP_ConfTemplate_AddSuccess,
	TP_ConfTemplate_DelSuccess,
	TP_ConfTemplate_UpdateSuccess,
	TP_ConfTemplate_MaxNum,				//ģ��������������
	TP_ConfTemplate_E164Repeat,			//e164�����ظ�
	TP_ConfTemplate_UnFindConf,			//δ�ҵ���Ŀ
	TP_ConfTemplate_ParamInValid,		//��������
};


//��ʼ������
enum EmTpStartConfRet
{
	TP_StartConf_UnKonw,
	TP_StartConf_Success,
	TP_StartConf_ConfTemplateUnExist,	//����ģ�岻����
	TP_StartConf_ConfFull,				//UMS������
	TP_StartConf_ConfExist,
	TP_StartConf_SipUnReg,				//δע��SIP������
	TP_StartConf_ResourceFull,          //�޿�����Դ
};

enum EmTpApplySpeakerRet
{
	TP_ApplySpeaker_Success,		
	TP_ApplySpeaker_ConfUnExist,		//���鲻����
	TP_ApplySpeaker_EpIDError,			//�᳡������
	TP_ApplySpeaker_EpStateError,		//�᳡δ���߻�ͨ����δ����
};

//�Ҷϻ�����
enum EmTpDropConfRet
{
	TP_DropConf_Success,
	TP_DropConf_ConfUnExit,	//����ģ�岻����
};

//ָ�������˽��
enum EmTpApplySpeakRet
{
	TP_ApplySpeak_UnKonw,
	TP_ApplySpeak_Success,
};

//�����к��н�������״̬
enum EmUmsConfNodeState
{
	ums_UmsConfNodeState_unused,		//δ��
	ums_UmsConfNodeState_uncall,		//������У���δ��ʼ����
	ums_UmsConfNodeState_calling,		//���ں�����...
	ums_UmsConfNodeState_callfailed,	//����ʧ��
	ums_UmsConfNodeState_online,		//����
	ums_UmsConfNodeState_stopcall,		//ֹͣ����
};


enum EmFlowCtrlOpr	//flowctrl�Ĳ���
{
	emFlowCtrl_Speaker  = 1	,
	emFlowCtrl_Chair	= 2	,
	emFlowCtrl_Poll		= 4	,
	emFlowCtrl_TvWall	= 8	,
	emFlowCtrl_View		= 16,
};

//��������
enum EMBrdType
{
	em_unknow_brd,
	em_eapu_brd,
	em_mpc_brd,
	em_mpu2ecard_brd,
	em_hdu2_brd,
	em_is22_brd,
	em_cri2_brd,
	em_mpu2_tp_brd,
	em_apu2_tp_brd,
	em_mpu2basic_brd,
	em_hdu2_qt_brd,

	em_brdtype_end,
};

//��������
enum EMEqpType
{
	em_unknow_mdl,
		em_adapter_mdl,
		em_dataswitch_mdl,
		em_netbuf_mdl,
		em_audmix_mdl,
		em_mpc_mdl,
		em_bas_mdl,
		em_vmp_mdl,
		em_hdu_mdl,
		em_regserver_mdl,
		em_recorder_mdl,
		em_vmp_tp_mdl,
		em_audbas_mdl,
		em_audmix_8_mdl,

		em_max_mdl = 15,
};

//����ģʽ
enum EMEqpModleType
{
	em_unknow_eqp_mdl,
	em_bas_basic_eqp_mdl,
	em_bas_enhanced_eqp_mdl,
	em_vmp_basic_eqp_mdl,
	em_vmp_enhanced_eqp_mdl,
};

//ϵͳ����
enum EMOsType
{
	em_unknow_OsType,
	em_Win32_OsType,
	em_Linux_OsType,
	em_82xx_OsType,
	em_85xx_OsType,
};

enum EMVmpStyle
{
	tp_VmpStyle_DYNAMIC = 0,	//��̬����(���Զ��ϳ�ʱ��Ч)	0
	tp_VmpStyle_ONE,			//һ����						1
	tp_VmpStyle_VTWO,			//�����棺���ҷ�				2
	tp_VmpStyle_HTWO,			//������: һ��һС				3
	tp_VmpStyle_THREE,			//������						4
	tp_VmpStyle_FOUR,			//�Ļ���						5
	tp_VmpStyle_SIX,			//������						6
	tp_VmpStyle_EIGHT,			//�˻���						7
	tp_VmpStyle_NINE,			//�Ż���						8
	tp_VmpStyle_TEN,			//ʮ����						9
	tp_VmpStyle_THIRTEEN,		//ʮ������						10
	tp_VmpStyle_SIXTEEN,		//ʮ������						11
	tp_VmpStyle_SPECFOUR,		//�����Ļ���					12
	tp_VmpStyle_SEVEN,			//�߻���						13
	tp_VmpStyle_TWENTY,			//��ʮ����						14
	tp_VmpStyle_TEN_H,			//ˮƽ�ָ��ʮ����(��2��8)		15
	tp_VmpStyle_SIX_L2UP_S4DOWN,	//����������(��2��4)		16
	tp_VmpStyle_FOURTEEN,			//ʮ�Ļ���					17
	tp_VmpStyle_TEN_M,				//ʮ����(��4��2��4)			18
	tp_VmpStyle_THIRTEEN_M,			//ʮ������(һ�����м�)		19
	tp_VmpStyle_FIFTEEN,			//ʮ�廭��					20
	tp_VmpStyle_SIX_DIVIDE,			//������(�ȷ�)				21
	tp_VmpStyle_leftBig,			//�����棬2��С���ڵײ�����	22
	tp_VmpStyle_MidBig,				//�����棬2��С���ڵײ�����	23
	tp_VmpStyle_RightBig,			//�����棬2��С���ڵײ�����	24
	tp_VmpStyle_3VERTICAL,			//�����棬��ֱ�ȴ�			25
	tp_VmpStyle_FOUR_3BOTTOMMIDDLE,	//�Ļ��棬3���ڵײ�����		26
	tp_VmpStyle_TWENTYFIVE,			//��ʮ�廭��				27
};


//==============����ΪCNSʹ��type==============//


//��ƵЭ������
enum EmTpVideoFormat
{
    emTPVH261     = 0,
		emTPVH262     = 1,//MPEG2
		emTPVH263     = 2,
		emTPVH263plus = 3,
		emTPVH264     = 4,
		emTPVMPEG4    = 5,
		
		emTPVEnd		
};
//���뷽ʽ
enum EmTpEncodeMode
{
    emTPQualityFirst  = 0, 
		emTPSpeedFirst    = 1,
		
};

//H.264��ʽ���ʼ���
enum EmTpVideoQualityLevel
{
	emTPH264BP = 0,  //BP����
	emTPH264HP = 1,  //HP����
};
//���м���  yewending
enum EmTpCallLevel
{	
	emTpCallLevelUnknown =0,
		emTPCallLevelFirst   = 1,
		emTPCallLevelSecond  = 2,
		emTpCallLevelThird   = 3,
};

//�ֱ�������
enum EmTpVideoResolution
{
    emTPVResolutionAuto     = 0,   //�Զ�
		emTPVSQCIF              = 1,   //SQCIF88x72
		emTPVQCIF               = 2,   //QCIF176x144
		emTPVCIF                = 3,   //CIF352x288
		emTPV2CIF               = 4,   //2CIF352x576
		emTPV4CIF               = 5,   //4CIF704x576
		emTPV16CIF              = 6,   //16CIF1408x1152
		
		emTPVHD480i720x480      = 7,   //480i720x480
		emTPVHD480p720x480      = 8,   //480p720x480
		emTPVHD576i720x576      = 9,   //576i720x576
		emTPVHD576p720x576      = 10,  //576p720x576
		
		emTPVHD720p1280x720     = 11,  //720p1280x720
		emTPVHD1080i1920x1080   = 12,  //1080i1920x1080
		emTPVHD1080p1920x1080   = 13,  //1080p1920x1080
		
		
		emTPVGA352x240          = 14,  //352x240
		emTPVGA704x480          = 15,  //704x480
		emTPVGA640x480          = 16,  //VGA640x480
		emTPVGA800x600          = 17,  //SVGA800x600
		emTPVGA1024x768         = 18,  //XGA1024x768
		emTPVGA1280x768         = 19,  //WXGA1280x768
		emTPVGA1280x800         = 20,  //WXGA1280x800
		emTPVGA1366x768         = 21,  //WXGA1366x768
		emTPVGA1280x854         = 22,  //WSXGA1280x854
		emTPVGA1440x900         = 23,  //WSXGA1440x900
		emTPVGA1280x1024        = 24,  //SXGA1280x1024
		emTPVGA1680x1050        = 25,  //SXGA+1680x1050
		emTPVGA1600x1200        = 26,  //UXGA1600x1200
		emTPVGA1920x1200        = 27,  //WUXGA1920x1200
		
		emTPVSQCIF112x96        = 28,
		emTPVSQCIF96x80         = 29,
		emTPV320x192            = 30,
		emTPV432x240            = 31,
		emTPV480x272            = 32,
		emTPV640x368            = 33,
		emTPV864x480            = 34,
		emTPV960x544            = 35,
		emTPV1440x816           = 36,
		
		emTPVResEnd = 50,
};

// ý������
enum EmTpMediaType
{
	emTPMediaVideo = 1, //��Ƶ
	emTPMediaAudio = 2, //��Ƶ
	emTPMediaAV    = 3 //��Ƶ����Ƶ
};

//PC windows �ɼ���ʽ
enum EmTpPCCapFormat
{
	emTPCapPCFrameBMP  = 0,//RGB24λͼ;
		emTPCapPCFrameUYUY = 1,//yuv4:2:2��ʽ
		emTPCapPCFrameI420 = 2,//yuv4:2:0��ʽ
};

//���������������
enum EmTpCodecComponent
{
	emTPPriomVideoEncoder  =0,
		emTPPriomVideoDecoder  ,
		
		emTPSecondVideoEncoder ,
		emTPSecondVideoDecoder ,
		
		emTPAudioEncoder ,
		emTPAudioDecoder ,

		emTPSecondAudioEncoder ,
		emTPSecondAudioDecoder ,

		emTPPriomLeftVideoDecoder,
		emTPPriomRightVideoDecoder,

		emTPMiniVideoEncoder,

		emTPCodecComponentEnd,

};

//��ƵЭ������
enum EmTpAudioFormat
{
    emTPAG711a  = 0,
		emTPAG711u  = 1,
		emTPAG722   = 2,
		emTPAG7231  = 3,
		emTPAG728   = 4,
		emTPAG729   = 5,
		emTPAMP3    = 6,
		emTPAG721   = 7,
		emTPAG7221  = 8,
		emTPAG719   = 9,
		emTPAMpegAACLC =10,
		emTPAMpegAACLD = 11,
		
		emTPAEnd	 
};
//�����ָ�����
enum EmTpLostPackageRestore
{
    emTPLPQualityFirst  = 0, 
		emTPLPSpeedSlow     = 1,
		emTPLPSpeedNormal   = 2,
		emTPLPSpeedFast     = 3,
};
enum EmTpCallMode
{
	emTpJoin,
		emTpCreate,
		emTpInvite,
		emTpAnswerUms,
		emTpAnswerCns,
};
enum EmTpConnectionType
{
	emTPConnectionBegin = 0,
	emTPTCPConnection,
	emTPUDPConnection,
};
enum EmTpConfProtocol
{
	emTpInvalidConfProtocel = 0,
	emTpH323, 
	emTpH320,
	emTpSIP,
	emTpSat,
	emTpAllProc,
};


enum EmTPAddrType
{
	emTpUnknown =0,
	emTpIPAddr, 
	emTpDomain,
	emTpAlias,
	emTpE164Num,
	emTpIP6Addr,
};
enum EmTPEndpointType
{
	emTPEndpointTypeUnknown  = 0,
	emTPEndpointTypeCNS	     = 0x01,
	emTPEndpointTypeUMS		 = 0x02,
	emTPEndpointTypeRegister,
	emTPEndpointH323MT,
	emTPEndpointH323MCU,
	emTPEndpointH323SingleMCU,
	emTPEndpointH323G400,
	emTPEndPointVrs,
};
enum EmTPSipLevel
{
	emTPSipCounty,
	emTPSipCity,
	emTPSipProvince,
	emTPSipUnKnown = 255,
};


//����״̬
enum EmCALLSTATE
{
	em_CALL_IDLE    = 0,  
	em_CALL_CALLING,
	em_CALL_CONNECTED
};

//�������ͣ�CNS֪ͨCMC
enum EmCallType
{
	emCallType_Invalid = 0,
	emCallType_P2P,
	emCallType_Conf
};

enum EmTPVideoType
{
	emTpPriomVideo = 0 ,//����Ƶ
	emTpMiniVideo = 1 //С����
};


//�ն���Ƶ�˿�
enum EmTPVideoPort
{
	//hd2.0��ƵԴ����
	emTpVGA   =0 , //VGA 
	emTpSVid    , //S ����
	emTpPC      , //PC
	emTpC1Vid   ,  //C1����   DVI 1
	emTpC2Vid   ,  //C2����   DVI 2
	emTpC3Vid   ,  //C3����   DVI 3
	emTpC4Vid   ,  //C4����   c
	emTpC5Vid   ,  //C5����   sdi 1
	emTpC6Vid   ,  //C6����   sdi 2
		
	emTpExternalVid = 10,//���þ���ӳ���ʼֵ
	emTpVideoMaxCount = 74, //���֧����ƵԴ����
	emTpVidInvalid = 255 
};

enum EmTPCNSInfoRst
{
	emTPCNSInfoSuccess = 1,			//�ɹ�
	emTPCNSRepeatE164,				//E164����
	emTPCNSRepeatAliasName,			//�᳡���ظ�

};


enum EmTPRegResult
{
	emTPRegResultBegin = 0,
	emTPRegResultReg,
	emTPRegResultUnReg
};

enum EmCnMtRegResult
{
	emCnMtSuccess = 1,
	emCnMtPosError,
	emCnMtTimeOut
};

//Add��������type
//�ն��ͺ�
enum EmCnModel
{
	emUnknownCnModel=0,
	em7920,	
	T300
		
};

//�۽�ģʽ
enum EmFocusMode
{
	emFocusAuto,
	emFocusManuel
};

//�۽�
enum EmFocus
{
	emFar ,
    emNear
};

//��Ұ
enum EmZoom
{
	emTele,
    emWide
};

//����
enum EmCnAction
{
    emCnStart,
	emCnStop,
};

//����� OSD ��ʾ
enum EmOSDShow
{
	emOSDOff = 0x00,
	emOSDOn ,
};

//��ƽ��ģʽ
enum EmWBMode
{
	emWBAuto = 0x00,
	emWBManual,
	emOnePush
};

//�ع�ģʽ
enum EmExpMode
{
	emExpAuto = 0x00,
	emExpManuel
};

//����� �ع�--����
enum EmGain
{
	em0dB = 0x00,
	em3dB = 0x01,
	em6dB = 0x02,
	em9dB  ,
	em12dB ,
	em15dB ,
	em18dB ,
	em21dB ,
	em24dB ,
	em27dB ,
	em30dB ,
	em33dB ,
	em36dB ,
	em39dB ,
	em42dB = 0x0e,
};

//�����  �ع�--����
enum EmShutSpd
{                        //HD95D        Sony
	emShutSpd0  = 0x00,  // 1/60        1/1
	emShutSpd1  = 0x01,  // 1/120		1/2
	emShutSpd2  = 0x02,  // 1/250		1/4
	emShutSpd3 ,         // 1/500		1/8
	emShutSpd4 ,         // 1/1000		1/15
	emShutSpd5 ,         // 1/2000		1/30
	emShutSpd6 ,         // 1/4000		1/60
	emShutSpd7 ,         // 1/10000		1/90
	emShutSpd8 ,					//	1/100
	emShutSpd9 ,					//  1/125
	emShutSpdA ,					//  1/180
	emShutSpdB ,					//  1/250
	emShutSpdC ,					//  1/350
	emShutSpdD ,					//  1/500
	emShutSpdE ,					//  1/725
	emShutSpdF ,				    //  1/1000
	emShutSpd10,					//  1/1500
	emShutSpd11,					//  1/2000
	emShutSpd12,					//  1/3000
	emShutSpd13,					//  1/4000
	emShutSpd14,					//  1/6000
	emShutSpd15,					//  1/10000
};

//����� �ع�--����
enum EmBackLightType
{
	emBLOff    = 0x00,
	emBLmulti,
	emBLcenter,
	emBLfacedetect,
		
	emBLAuto,
};

//����� ����ģʽ
enum EmPicSceMode
{
	emLamp   = 0x00,  
	emSun    = 0x01,  
	emManuel = 0x02,
};

//����� �ֶ�ģʽ GAMMA
enum EmGamma
{
	emGammaOff  = 0x00,
	emGammaOn   = 0x01,
	emSmart1,
	emSmart2,
};

//���� ���������� ��Χ
enum EmStmClean
{
    emNRoff  = 0x00,
	emNRlow  ,
	emNRmid  ,
	emNRhigh
};

enum Em3DNR
{
	em3DNROff  = 0x00,
	em3DNROn
};

enum EmCamPowerMode
{
	emCamPowerOn,   //�ϵ�
	emCamPowerOff,  //����
	emCamPowerDowm, //�ϵ�
};

enum EmCenSchMode
{
	emSchSleep,   //����
	emSchWakeup,  //����
};

enum EmSonyIris
{
	emIrisOFF  = 0x00,
	emIrisF9_6 = 0x07,
	emIrisF8,
	emIrisF6_8,
	emIrisF5_6,
	emIrisF4_8,
	emIrisF4,
	emIrisF3_4,
	emIrisF2_8,
	emIrisF2_4,
	emIrisF2,
	emIrisF1_8,
};

//���������
enum EmCamType
{
	emCamHD95D, 
	emCamSony,  
};

//end


//�п�ģ��
//���ӻ���Դģʽ
enum EmTvPowerMode
{
	emTVPowerOFF,
	emTVPowerON,
	emTVPowerDown
};

//���ӻ��ϵ�ǰ��Դģʽ
enum EmTvSrcPowerMode
{
	emTVSrcPowerOFF,
		emTVSrcPowerON,
};

//���ӻ�����ģʽ
enum EmTVAudVisMode
{
	emTVAVStandardMode = 0,   //��׼
		emTVAVMovieMode,          //��Ӱ
		emTVAVUserMode,           //�û�
		emTVAVComputerMode        //����
};


//���ӻ���ʾģʽ
enum EmTVDisplayMode
{
	emTVDisFullScrMode  = 0,  //ȫ��
		emTVDisPanoramaMode,      //ȫ��
		emTVDisPointMode,         //���
		emTVDisStandardMode       //��׼
};

//���ӻ�����ѡ�� 
enum EmTVInputSelect
{
	emTVHDMI1  = 0,
		emTVHDMI2,
		emTVHDMI3,
		emTVHDMI4,
		emTVYpbPr,
		emTVCVBS1,
		emTVCVBS2,
		emTVComputer
};

//�ĵ�����ͷ��ƽ��ģʽ 
enum EmDCamWBMode
{
	emDcamWBAuto = 0x00,
	emDCamWBManual,
	emDCamOnePush,
	emDCamWBInvalid
};

//�ĵ�����ͷ�Զ��۽�ģʽ
enum EmDCamAFMode
{
	emDcamAFOff = 0x00,
	emDCamAFOn,
	emDCamAFToggle,
	emDCamAFInvalid
};

//�ĵ�����ͷ��������
enum EmDCamPower
{
	emDCamPowerOff = 0x00,
	emDCamPowerOn,
	emDCamPowerToggle,
	emDCamPowerDown,
	emDCamPowerInvalid
};

//�ĵ�����ͷ��Ұ����
enum EmDCamZoom
{
    emDCamZoomWide = 0x00,
	emDCamZoomTele,
	emDCamZoomInvalid
};

//�����ĵ�����ͷԤ��λ���
enum EmDCamPresetNum
{
	emDCamPresetOne = 0x00,
	emDCamPresetTwo,
	emDCamPresetThree,
	emDCamPresetInvalid
};

//�����ĵ�����ͷԤ��λ���
enum EmDCamRecallNum
{
	emDCamRecallOne = 0x00,
	emDCamRecallTwo,
	emDCamRecallThree,
	emDCamRecallInvalid
};

//������ϵͳ��Դ����
enum EmSchPower
{
	emSchPowerOff = 0x00,
	emSchPowerOn,
	emSchPowerToggle,
	emSchPowerInvalid
};

//�����ҵƹ��Դ����
enum EmSchLight
{
	emSchLightOff = 0x00,
	emSchLightOn,
	emSchLightInvalid
};

//�����Ҷ��ϵƹ��Դ����
enum EmSchMidLight
{
	emSchMidLightOff = 0x00,
	emSchMidLightOn,
	emSchMidLightInvalid
};

//�����һ���ƹ��Դ����
enum EmSchScrLight
{
	emSchScrLightOff = 0x00,
	emSchScrLightOn,
	emSchScrLightInvalid
};



//�����������Ӧ�����������
enum EmSchArgus
{
	emSchArgusUnlock = 0x00,
	emSchArgusLock,
	emSchArgusInvalid
};

//�пؿյ�ģʽ add by zhangapei
enum EmCentreACPower
{
	emCenACPowerOff,
	emCenACPowerOn,
};

//�յ��·����
enum EmCentreACAirVol
{
	emCenACVolAuto,  //�Զ�
	emCenACVol1,    
	emCenACVol2,     
	emCenACVol3,    
	emCenACVol4,  
	emCenACVol5,     
};

//�յ�ģʽ
enum EmCentreACMode
{
	emCenACBlowIn,  //�ͷ�
	emCenACheat,    //����
	emCenAcref,     //����
	emCenACAuto,    //�Զ�
	emCenACChaAir,  //����
	emCenACdeh,     //��ʪ
};


//������������
enum EmCurAction
{
	emCurUp,
	emCurDown,
	emCurStop,
};

//��������ͨ·ģʽ
enum EmCurChannelMode
{
	emCurChanFirst = 1,
	emCurChanSecond,
	emCurChanFirASec,
	emCurChanThird,
	emCurChanFirAThi,
	emCurChanSecAThi,
};

enum EmSchGatewayType
{
	emGatewayOld,
	emGatewayNew,
};

//end add

//�п� end

//==============����ΪCNSʹ��type==============//

enum EmTpMixStatus
{
	emAudMixIdle,
	emAudOpenChan_Fail,		//������ͨ��ʧ��
	emAudOpenChan_Success    //������ͨ���ɹ�
};

enum EmTPDualReason
{
	emTpDualAccept,
		emTpDualBusy,
		emTpDualPreemptive,
		emTpDualPeerReject,
		emTpDualPeerStop,
		emTpDualNoVideo,
		emTpDualLocalStop,
		emTpDualSndFail,       //����˫��ʧ��
		emTpDualInit,           //˫����ʼ����
		emTPDualBasLacking,
};

enum  EmTPPayloadType 
{
	emTpPayloadTypeBegin = 0,
		//��Ƶ��ʽ
		emTpAudioTypeBegin,
		emTpG711a,
		emTpG711u,
		emTpG722,
		emTpG7231,
		emTpG728,
		emTpG729,
		emTpMp3,  
		emTpG723,
		emTpG7221,
		emTpMpegaaclc,
		emTpMpegaacld,
		emTpG719,
		emTpAudioTypeEnd = 49,
		
		//��Ƶ��ʽ
		emTpVideoTypeBegin = 50,	
		emTpH261,
		emTpH263,
		emTpH263plus,
		emTpH264,
		emTpH262,
		emTpMpeg4,
		emTpVideoTypeEnd = 99,
        
		emTpDataTypeBegin = 100,	
		emTpT120,
		emTpH224,
		emTpDataTypeEnd = 149,
		
		emTpPayloadTypeEnd = 255
};

enum EmTPPosStatus
{
	emPosInAcitve = 0,
	emPosAcitve
};

enum EmTPPollResult
{
	emPollSucceed = 0,
	emPollFailUnKown = 1,
	emPollInvalidEp = 2,	//����Ч��ѵ�᳡
	emPollResFull,//��Դ���㣺��������
	emPollResFull_Bw,
	emPollResFull_Bas,
	emPollNoChair,//����ϯȨ��
	emPollChairNoLine,//��ϯ������
	emPollServerBusy,//������æ
};

enum EmPollStat
{
	EmPollStat_Error,
	EmPollStat_Stop,
	EmPollStat_Start,
	EmPollStat_Suspend,
};

enum EmTPViewResult
{
	emViewSucceed = 0,
	emViewFailUnKown,
	emViewFailStatusError,
	emViewFailOffline,			//�Զ˲�����
	emViewFailNotChair,			//�����ⲻ�����᳡
	emViewFailNoResource,		//û����Դ
	emViewFailDstNoVid,			//Ŀ������Ƶ
	emViewRequesting,			//�����У���ȴ�
	emViewFailIllegalPos
};


enum EmTPViewLocalResult
{
	emViewLocalSucceed = 0,
	emViewLocalFailUnKown,
	emViewLocalFailStatusError,       //״̬����ȡ��ʱ��ʾ��ǰ������VIEW LOCAL��ѡ��ʱ��ʾ���ڿ�����״̬
	emViewLocalFailOffline,
	emViewLocalFailIllegalPos
};

enum EmTPDisOprType
{
	emDisOprType_Idle,
	emDisOprType_StartAll,
	emDisOprType_AddChnl,
	emDisOprType_ChangeSeat,
	emDisOprType_RemoveChnl,
	emDisOprType_DisConnectChnl
};

enum EMPosPic
{
	emPic_Invalid = 0,
		emPic_Local,				//����
		emPic_Static,				//��̬ͼƬ
		emPic_Speaker,				//������
		emPic_Dual,					//˫��
		emPic_Poll,					//��ѯ
		emPic_SelView,              //ѡ��Զ�� 
		emPic_SelDual,              //ѡ��˫��
		emPic_SelLocal,             //ѡ������
		emPic_Discuss,             //����
		emPic_SelTVS,               //ѡ������ǽ
		emPic_Chair,
		emPic_VmpBrd,               //ѡ������ϳ�

};

enum EMDSCREATETYPE
{
	emDS_CreateType_Invalid = 0,
	emDS_CreateType_SndBoundary,
	emDS_CreateType_RcvBoundary,
	emDS_CreateType_SndAndRcvBoundary,
	emDS_CreateType_NotBoundary,
};

enum EmTPAddDualRcvResult
{
	emAddDualRcvSucceed = 0,
	emAddDualRcvFailNoDual,       //û����˫��
	emAddDualRcvFailIllegalPos,   //�Ƿ�λ��
	emAddDualRcvFailNoPos,        //û�п���λ����
	emAddDualRcvFailStatusError,  //��ǰ�Ѿ���˫��״̬��
	emAddDualRcvFailUnKown,
};

enum EmTPDeleteDualRcvResult
{
	emDeleteDualRcvSucceed = 0,
	emDeleteDualRcvFailNoDual,       //û����˫��
	emDeleteDualRcvFailIllegalPos,   //�Ƿ�λ��
	emDeleteDualRcvFailUnKown,
};

enum EmTPMtModel
{
	emTPUnknownMtModel=0,
		emTPPCMT  =1    ,//�����ն�
		emTP8010      ,
		emTP8010A     ,
		emTP8010Aplus ,//8010A+
		emTP8010C     ,
		emTP8010C1    ,//8010C1
		emTPIMT       ,
		emTP8220A     ,
		emTP8220B     ,
		emTP8220C     ,
		emTP8620A     ,
		emTPTS6610E   ,
		emTPTS6210    ,
		emTP8010A_2   ,
		emTP8010A_4   ,
		emTP8010A_8   ,
		emTP7210      ,
		emTP7610      ,
		emTPTS5610    ,
		emTPTS6610    ,
		emTP7810      ,
		emTP7910      ,
		emTP7620_A    ,
		emTP7620_B    ,
		emTP7820_A	,
		emTP7820_B	,
		emTP7920_A	,
		emTP7920_B	
		
};

enum EmDsType
{
	em_DsType_Invalid = 0,

		
		//Э�� �ⲿ�˿�
		em_Ds_Remote_ASnd_0 ,
		em_Ds_Remote_ASnd_1,
		em_Ds_Remote_ASnd_2,
		
		em_Ds_Remote_ARcv_0,
		em_Ds_Remote_ARcv_1,
		em_Ds_Remote_ARcv_2,
		
		em_Ds_Remote_VSnd_0,
		em_Ds_Remote_VSnd_1,
		em_Ds_Remote_VSnd_2,
		
		em_Ds_Remote_VRcv_0,
		em_Ds_Remote_VRcv_1,
		em_Ds_Remote_VRcv_2,
		
		em_Ds_Remote_VSnd_Mini_0,
		em_Ds_Remote_VSnd_Mini_1,
		em_Ds_Remote_VSnd_Mini_2,
		
		em_Ds_Remote_VRcv_0_Mini_0,
		em_Ds_Remote_VRcv_0_Mini_1,
		em_Ds_Remote_VRcv_1_Mini_0,
		em_Ds_Remote_VRcv_1_Mini_1,
		em_Ds_Remote_VRcv_2_Mini_0,
		em_Ds_Remote_VRcv_2_Mini_1,
		
		
		em_Ds_Remote_Mix_Snd,
		em_Ds_Remote_Mix_Rcv,

		em_Ds_RemoteDual_ASnd,
		em_Ds_RemoteDual_VSnd,
		
		em_Ds_RemoteDual_ARcv,
		em_Ds_RemoteDual_VRcv,


		//������Э��ջ����
		em_Ds_VirRemote_ASnd_0 ,
		em_Ds_VirRemote_ASnd_1,
		em_Ds_VirRemote_ASnd_2,
		
		em_Ds_VirRemote_ARcv_0,
		em_Ds_VirRemote_ARcv_1,
		em_Ds_VirRemote_ARcv_2,
		
		em_Ds_VirRemote_VSnd_0,
		em_Ds_VirRemote_VSnd_1,
		em_Ds_VirRemote_VSnd_2,
		
		em_Ds_VirRemote_VRcv_0,
		em_Ds_VirRemote_VRcv_1,
		em_Ds_VirRemote_VRcv_2,

		em_Ds_VirRemote_VSnd_Mini_0,
		em_Ds_VirRemote_VSnd_Mini_1,
		em_Ds_VirRemote_VSnd_Mini_2,
		
		em_Ds_VirRemote_VRcv_0_Mini_0,
		em_Ds_VirRemote_VRcv_0_Mini_1,
		em_Ds_VirRemote_VRcv_1_Mini_0,
		em_Ds_VirRemote_VRcv_1_Mini_1,
		em_Ds_VirRemote_VRcv_2_Mini_0,
		em_Ds_VirRemote_VRcv_2_Mini_1,

		
		em_Ds_VirRemote_Mix_Snd,
		em_Ds_VirRemote_Mix_Rcv,
		
		em_Ds_VirRemote_End = 100,

		em_Ds_MT_ASnd_0,
		em_Ds_MT_ASnd_1,
		em_Ds_MT_ASnd_2,
		em_Ds_MT_ASnd_3,
		
		em_Ds_MT_ARcv_0,
		em_Ds_MT_ARcv_1,
		em_Ds_MT_ARcv_2,
		em_Ds_MT_ARcv_3,
		
		em_Ds_MT_VSnd_0,
		em_Ds_MT_VSnd_1,
		em_Ds_MT_VSnd_2,
		em_Ds_MT_VSnd_3,
		
		em_Ds_MT_VRcv_0,
		em_Ds_MT_VRcv_1,
		em_Ds_MT_VRcv_2,
		em_Ds_MT_VRcv_3,
		
		em_Ds_MT_VSnd_Mini_0,
		em_Ds_MT_VSnd_Mini_1,
		em_Ds_MT_VSnd_Mini_2,
		
		em_Ds_MT_VRcv_0_Mini_0,
		em_Ds_MT_VRcv_0_Mini_1,
		em_Ds_MT_VRcv_1_Mini_0,
		em_Ds_MT_VRcv_1_Mini_1,
		em_Ds_MT_VRcv_2_Mini_0,
		em_Ds_MT_VRcv_2_Mini_1,
		
		em_Ds_Mt_Mix_ASnd,//mt�����˿�

		//���ں��ն˽���  Ŀǰ��ʹ��
		em_Ds_VirMt_ASnd_0,
		em_Ds_VirMt_ASnd_1,
		em_Ds_VirMt_ASnd_2,
		
		em_Ds_VirMt_ARcv_0,
		em_Ds_VirMt_ARcv_1,
		em_Ds_VirMt_ARcv_2,
		
		em_Ds_VirMt_VSnd_0,
		em_Ds_VirMt_VSnd_1,
		em_Ds_VirMt_VSnd_2,
		
		em_Ds_VirMt_VRcv_0,
		em_Ds_VirMt_VRcv_1,
		em_Ds_VirMt_VRcv_2,

		em_Ds_VirMt_VSnd_Mini_0,
		em_Ds_VirMt_VSnd_Mini_1,
		em_Ds_VirMt_VSnd_Mini_2,
		
		em_Ds_VirMt_VRcv_0_Mini_0,
		em_Ds_VirMt_VRcv_0_Mini_1,
		em_Ds_VirMt_VRcv_1_Mini_0,
		em_Ds_VirMt_VRcv_1_Mini_1,
		em_Ds_VirMt_VRcv_2_Mini_0,
		em_Ds_VirMt_VRcv_2_Mini_1,

		em_Ds_VirMt_Mix_ASnd,
	

		em_Ds_Mt_End = 200,


		em_Ds_Innerspeaker_ASnd,
		em_Ds_Innerspeaker_VSnd,
		
		em_Ds_Innerspeaker_End = 210 ,
		
		em_Ds_VirDual_ASnd,
		em_Ds_VirDual_VSnd,
		
		em_Ds_VirDual_ARcv,//˫����Ϊ�����ݲ�ʹ��
		em_Ds_VirDual_VRcv,//˫����Ϊ�����ݲ�ʹ��
		
		//�����ַ
		em_Ds_VirDual_Adapter_VSnd,
		em_Ds_MtDual_Adapter,		

		em_Ds_Dual_End = 250,

		em_Ds_Addr_Type_End = 300,


		//���²���Ҫ����˿�
		em_DsOtherType_Begin,
		
		em_Ds_VirMtToInnerspeaker_ASnd_0,
		em_Ds_VirMtToInnerspeaker_ASnd_1,
		em_Ds_VirMtToInnerspeaker_ASnd_2,
		
		em_Ds_VirMtToInnerspeaker_VSnd_0,
		em_Ds_VirMtToInnerspeaker_VSnd_1,
		em_Ds_VirMtToInnerspeaker_VSnd_2,
		
		em_Ds_DualRcvToVirMt_Rcv_0,
		em_Ds_DualRcvToVirMt_Rcv_1,
		em_Ds_DualRcvToVirMt_Rcv_2,

		em_Ds_VirRemoteToVirMt_ASnd_0,
		em_Ds_VirRemoteToVirMt_ASnd_1,
		em_Ds_VirRemoteToVirMt_ASnd_2,

		em_Ds_VirRemoteToVirMt_VSnd_0,
		em_Ds_VirRemoteToVirMt_VSnd_1,
		em_Ds_VirRemoteToVirMt_VSnd_2,

		em_Ds_VirRemoteToVirMt_ARcv_0,
		em_Ds_VirRemoteToVirMt_ARcv_1,
		em_Ds_VirRemoteToVirMt_ARcv_2,
		
		em_Ds_VirRemoteToVirMt_VRcv_0,
		em_Ds_VirRemoteToVirMt_VRcv_1,
		em_Ds_VirRemoteToVirMt_VRcv_2,

		em_Ds_VirDualNB_VRcv,
		em_Ds_VirDualNB_VSnd,

		em_Ds_VirDualNB_ARcv,
		em_Ds_VirDualNB_ASnd,
		
		em_Ds_VirRemoteToVirMt_VSnd_Mini_0,
		em_Ds_VirRemoteToVirMt_VSnd_Mini_1,
		em_Ds_VirRemoteToVirMt_VSnd_Mini_2,

		em_Ds_VirRemoteToVirMt_VRcv_0_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_0_Mini_1,
		em_Ds_VirRemoteToVirMt_VRcv_1_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_1_Mini_1,
		em_Ds_VirRemoteToVirMt_VRcv_2_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_2_Mini_1,

		em_Ds_VirRemoteToVirMt_Mix_ASnd,
		
		em_Ds_VirRemoteToPad_VSnd,
		em_Ds_VirRemoteToPad_ASnd,
		
		em_Ds_VirMidRcvToVirMt_VRcv_0,
		em_Ds_VirMidRcvToVirMt_VRcv_2,

		em_Ds_VirDual_ARcv_Pad_Begin = em_DsOtherType_Begin+1000,
		em_Ds_VirDual_ARcv_Pad_End = em_Ds_VirDual_ARcv_Pad_Begin+20,
		em_Ds_VirDual_VRcv_Pad_Begin,
		em_Ds_VirDual_VRcv_Pad_End = em_Ds_VirDual_VRcv_Pad_Begin+20,

		em_Ds_VirDual_VSnd_Pad,
		

		em_Ds_Debug = 1010,
		
};

enum EmCnAudioMixID
{
	emCnAMix_INVALID,
	emCnAMix_Speaker,    //3��1�������˻�����
	emCnAMix_Dual,       //˫��������
};

enum EmGetRegInfoType
{
	emGetRegInfoType_CNS = 0,
	emGetRegInfoType_UMS,
	emGetRegInfoType_ALL,
	emGetRegInfoType_MT,
	emGetRefInfoType_MCU,
};

enum EmGetRegInfoOpr
{
	emGetRegInfoOpr_Update = 0,//ˢ��
	emGetRegInfoOpr_Add,//����
};

enum EmTPChanType
{
	emTPChanNone,
	emTPChanRecv,
	emTPChanSend,
	emTPChanSendRecv,
	emTPChanTypeEnd = 10,
};

enum EmTPAACSampleFreq                    //sampling frequency
{
	emTPFs96000 = 0,
        emTPFs88200 = 1,
        emTPFs64000 = 2,
        emTPFs48000 = 3,
        emTPFs44100 = 4,
        emTPFs32000 = 5,
        emTPFs24000 = 6,
        emTPFs22050 = 7,
        emTPFs16000 = 8,
        emTPFs12000 = 9,
        emTPFs11025 = 10,
        emTPFs8000  = 11
};

enum EmTPG7221Rate
{
	emTPG7221Rate24   =  0x01,
	emTPG7221Rate32   =  0x02,
	emTPG7221Rate48   =  0x04
};


enum EmTPAACChnlCfg                       //channel config
{
	emTPChnlCust   = 0,
        emTPChnl1      = 1,                   //������
        emTPChnl2      = 2,                   //˫����
        emTPChnl3      = 3,
        emTPChnl4      = 4,
        emTPChnl5      = 5,
        emTPChnl5dot1  = 6,                   //5.1����
        emTPChnl7dot1  = 7                    //7.1����
};

enum EmTPTpApplySpeakerRet
{
	emTP_ApplySpeaker_Success,  
	emTP_ApplySpeaker_ConfUnExist,   //���鲻����
	emTP_ApplySpeaker_EpIDError,     //�᳡������
	emTP_ApplySpeaker_EpStateError,  //�᳡δ���߻�ͨ����δ����
};


enum EmTPChanSubType
{
	EmTPChanSubType_Normal, 
	EmTPChanSubType_Mini,
	EmTPChanSubType_Dual,   
	EmTPChanSubType_AMix,       
};

enum EmMakeCallType
{
	em_sip_call_type,
	em_323_call_type,
};

enum EmTpRegType
{
	em_sip_reg,
	em_323_reg,
};

enum EmDisListOprType
{
	em_DisListOpr_Add,
	em_DisListOpr_Del,
};

enum EmDisListOprReslt
{
	em_DisListOpr_Sucess,
	em_DisListOpr_Fail,
	em_DisListOpr_Reject,
};

//Add by tanxiaodong 2012-07-17.
//VGA����
enum EmVgaType
{
	//CNC˫����ʾԴ��ѡ������	
	emVgaTypeFullScreenCamera = 0, //ȫ�������
	emVgaType001,
	emVgaType002,
	emVgaType003,
	emVgaTypeDocCamera, //�ĵ������
	emVgaTypeInValid//��Чֵ
};

//˫����ʾԴ����ӿ�����
enum EmDualInputType
{   
   emDualInputFullScreenCamera, //ȫ�������
   emDualInput001,//��ʾԴ1
   emDualInput002,//��ʾԴ2
   emDualInput003,//��ʾԴ3
   emDualInputDocCamera,//�ĵ������
   emDualInputInvalid//��Чֵ

};

//˫����ʾԴ����ӿ�����
enum EmDualOutputType
{
	emDualOutputInvalid = 0,
	emDualOutput001,//��ʾ��1
    emDualOutput002 //��ʾ��2
};
//End to add.

//Added by meifang
enum EmVgaSwitchResult
{
	em_VgaSwitchInvalid,      //��Чֵ
	em_VgaSwitchFail = 1,     //�л�ʧ��
	em_VgaSwitchSucc,         //�л��ɹ�	
	em_CurVgaNoSignal,        //�л��ɹ�������ǰ��ʾԴ������
	em_TpNoDual,              //û�н�˫���ն�
	em_VgaBusying,            //��ʾԴ��æ���ܾ��л�
};

//��ʾԴ�л�ԭ��
enum EmVgaSwitchReason
{
	em_SwitchVgaInvalid,
		em_SwitchDemoVga = 1, //�������л�Ĭ����ʾԴ
		em_SwitchCurVga,      //�������л���ǰ��ʾԴ
		em_ResetVga,          //���ʱ����ΪĬ����ʾԴ
};

//�᳡״̬
enum EmCnState
{
	emCnsRunning, //��������
	emCnsSleep,   //����
	emCnsPoweroff, //�ػ�
};
//End to add

enum EmTPCapSign    //������ʶ�� ������
{
	emTPCapBig,  
	emTPCapLeft,
	emTPCapSmall = emTPCapLeft,  //������ʶ��ԭ���Ĵ�����ת���ɴ�С��
	//ö��ֻ��0,1,2��ԭ�������൱��С�����൱�ڽ���
	emTPCapRight,
	emTPCapEnd = emTPCapRight,
};

//Add by tanxiaodong 2012-11-22.
enum EmSwitchState
{
	emStateON = 1,   //����
	emStateOFF,      //�ػ�
	emStateStandby,  //����
};
//End to add.

//����������
enum EmTpBoardRet
{
	emTP_Board_UnKonw,                //����δ֪
	emTP_Board_AddSuccess,            //������ӳɹ�
	emTP_Board_DelSuccess,            //����ɾ���ɹ�
	emTP_Board_ModifySuccess,         //�����޸ĳɹ�
	emTP_Board_MaxNum,				  //���������ﵽ���ֵ
	emTP_Board_Mode_AddSuccess,       //����ģʽ��ӳɹ�
	emTP_Board_Mode_DelSuccess,       //����ģʽɾ���ɹ�
	emTP_Board_Mode_ModifySuccess,    //����ģʽ�޸ĳɹ�
	emTP_Board_UnFind,			      //δ�ҵ���Ŀ
	emTP_Board_UnKnowLoc,             //�����Ųۺ�δ֪
	emTP_Board_Repeat,                //�����ظ�
	emTP_BrdType_NotMatch_EqpType,    //�����������������Ͳ�ƥ��
	emTP_BrdMode_Repeat,              //Ҫ�޸ĵ�ģʽ��ԭģʽ��ͬ
	emTP_BrdMode_MaxNum,              //����ģʽ�ﵽ���ֵ
	emTP_BrdMode_NoConfig,			  //����δ����ģʽ
	emTp_BrdMode_Resource_Full,		  //ģʽ����eqpidʱ��Դռ��
	emTp_BrdMode_AudMix_MaxNum,       //�ﵽ������������·��
};

//hdu ����˿�����
enum EmHduOutPort
{
	em_hdu_outport_YPbPr = 0,
	em_hdu_outport_VGA   = 1,
	em_hdu_outport_DVI   = 2,
	em_hdu_outport_HDMI  = 3,

	em_hdu_outport_unknow,
};

//HDU ���ű���
enum EmHduZoomRate
{
	em_hdu_zoomrate_4_3  = 0,
	em_hdu_zoomrate_16_9 = 1,

	em_hdu_zoomrate_unknow,
};

//HDU �����ʽ
enum EmHduOutMode
{
	em_hdu_outmode_YPbPr_1080P_24fps = 0,
	em_hdu_outmode_YPbPr_1080P_25fps = 1,
	em_hdu_outmode_YPbPr_1080P_30fps = 2,
	em_hdu_outmode_YPbPr_1080P_50fps = 3,
	em_hdu_outmode_YPbPr_1080P_60fps = 4,
	em_hdu_outmode_YPbPr_1080i_50HZ  = 5,    //(Ĭ��)
	em_hdu_outmode_YPbPr_1080i_60HZ  = 6,
	em_hdu_outmode_YPbPr_720P_60fps  = 7,
	em_hdu_outmode_YPbPr_576i_50HZ   = 8,
	em_hdu_outmode_YPbPr_480i_60HZ   = 9,
		
	
	em_hdu_outmode_VGA_SXGA_60HZ     = 10,
	em_hdu_outmode_VGA_XGA_60HZ      = 11,     //(Ĭ��)
	em_hdu_outmode_VGA_XGA_75HZ      = 12,
	em_hdu_outmode_VGA_SVGA_60HZ     = 13,
	em_hdu_outmode_VGA_SVGA_75HZ     = 14,
	em_hdu_outmode_VGA_VGA_60HZ      = 15,
	em_hdu_outmode_VGA_VGA_75HZ      = 16,
	em_hdu_outmode_VGA_SXGA_75HZ     = 17,
	em_hdu_outmode_YPbPr_720P_50fps  = 18,  //zjl[20091216]�¼�hdu�����ʽ
	em_hdu_outmode_VGA_WXGA_1280_768_60HZ = 19,
	em_hdu_outmode_VGA_WXGA_1280_800_60HZ = 20,
	em_hdu_outmode_VGA_WSXGA_60HZ    = 21,
	em_hdu_outmode_VGA_SXGAPlus_60HZ = 22,
	em_hdu_outmode_VGA_UXGA_60HZ     = 23,
	em_hdu_outmode_YPbPr_1080P_29970HZ = 24,
	em_hdu_outmode_YPbPr_1080P_59940HZ = 25,
	em_hdu_outmode_WXGA_1280_800_75HZ  = 26,

	em_hdu_outmode_unknow,
};

//�������
enum EmHduShowMode
{
	em_hdu_showmode_NONGEOMETRIC   = 1,      //���ȱ�����
	em_hdu_showmode_CUTEDGEGEOME   = 2,      //�ñߵȱ�����
	em_hdu_showmode_BLACKEDGEGEOME = 3,      //�Ӻڱߵȱ�����

	em_hdu_showmode_unknow,
};

enum EmModifyNMServerRet
{
	em_nmserver_modify_success,		//�޸�(��ӣ��޸ģ�ɾ��)�ɹ�
	em_nmserver_resource_full,		//����������
	em_nmserver_invalid_handle,		//��Ч�ľ��
};

enum EmModifyVcrRet
{
	em_vcr_modify_success,	//�޸ĳɹ�
	em_vcr_invalid,	//��Ч��¼���
	em_vcr_full,	//¼�������
	em_vcr_no_exist,	//������
	em_vcr_exist,		//¼����Ѵ���
};

enum EmModifyHduRet
{
	em_hdu_modify_success,	//�޸ĳɹ�
	em_hdu_invalid_index,	//��Ч������
	em_hdu_brd_no_cfg,		//����δ����
	em_hdu_brd_already_cfg,			//�����Ѿ�����
	em_hdu_modify_fail,		//�޸�ʧ��
	em_hdu_invalid_brdtype,		//��Ч��brd type
};


enum EmUpdateHduRet
{
	em_hdu_update_success,	//�����ɹ�
	em_hdu_update_ing,		//��������
	em_hdu_update_unreg,	//����δע��
	em_hdu_update_unknow,	//δ֪ԭ��
};

enum EmMPCodec
{
	emMPCodec1,
	emMPCodec2,
	emMPCodec3,
	emMPDualCodec,
	emEndMPCodec
};

enum EmTPHDAudPortIn
{
	emTPAudInCanon1,
	emTPAudInCanon2,
	emTPAudInCanon3,
	emTPAudInCanon4,
	emTPAudInCanon5,
	emTPAudInCanon6,
	emTPAudInCanon7,
	emTPAudInCanon8,
	emTPAudInCanon9,
	emTPAudInCanon10,
	emTPAudInDigit0,
	emTPAudInDigit1,
	emTPAudInDigit2,
	emTPAudInEnd
};

enum EmTPHDDualAudPortIn
{	
	emTPAudInTrs1, //TRS��3.5mm���������루˫��PC���룩
	emTPAudInTrs2,
	emTPAudInTrs3,
	emTPAudInTrs4,
	emTPAudInRcaL,// RCA��L/R) �������루˫��DVD���룩
	emTPAudInRcaR,
	emTPDualAudInEnd
};

enum EmTPHDAudPortOut
{
	emTPAudOutCCanon1  ,
	emTPAudOutCCanon2,
	emTPAudOutCCanon3,
	emTPAudOutCCanon4,
	emTPAudOutCCanon5,
	emTPAudOutReproducer,//����������
	emTPAudOutEnd
};

//�ն���Ƶ����˿�
enum EmTPMtVideoPort
{
	emTPC1Vid   ,  //C1����   DVI IN 1������1
	emTPC2Vid   ,  //C2����   DVI IN 2������Ƶ1
	emTPC3Vid   ,  //C3����   DVI IN 3������2
	emTPC4Vid   ,  //C4����   DVI IN 4�� ����Ƶ2
	emTPC5Vid   ,  //C5����   DVI IN 5������3
	emTPC6Vid   ,  //C6����   DVI IN 6������Ƶ3
	emTPC7Vid   ,  //C7����	  DVI IN 7��ȫ��
	emTPC8Vid   ,  //C8����	  DVI IN 8��
	emTPC9Vid   ,  //C9����   DVI IN 9��
	emTPC10Vid   ,  //C10���� DVI IN 10��
	emTPC11Vid   ,  //C11���� DVI IN 11���ĵ�  
	emTPVidEnd
};


enum EmTPMtVideoOutPort
{
	emTPC1OutVid   ,  //C1����   DVI 1
		emTPC2OutVid   ,  //C2����   DVI 2
		emTPC3OutVid   ,  //C3����   DVI 3
		emTPC4OutVid   ,  //C4����   
		emTPC5OutVid   ,  //C5����   
		emTPVidOutEnd
};

enum EmTPAutoTestType // �������
{
    emTPAutoTestBegin,            //���Կ�ʼ
	emTPAutoTestAudioLoopBackFunc,    //��Ƶ���ع��ܲ���
	emTPAutoTestPriomVideoLoopBackFunc,    //����Ƶ���ع��ܲ��ԣ���������
	emTPAutoTestSecondVideoLoopBackFunc, //˫��
	emTPAutoTestEnd               //���Խ���
};

enum EmTPHduRunStatus
{
	emTPHduIdle,		//����״̬
	emTPHduWaiting,		//�ȴ�
	emTPHduPlaying,		//����״̬
	emTPHduUnknow,		//δ֪״̬
};

// ������������С����
enum EmTPLoudspeakerVal
{
	emTPLoudspeakerLow = 0,
		emTPLoudspeakerMiddle,
		emTPLoudspeakerHigh,
};
//֡�ʵ�λ����
enum EmTPFrameUnitType
{
    emTPFrameSecond =0,
		emTPSecondFrame =1
};

//��Ƶ��ʽ����
enum EmTPVideoStandard
{
    emTPPAL  =0 ,
		emTPNTSC = 1 ,
		//    emTPSECAM = 2
};

//̨������
enum EmTPLabelType
{
    emTPLabelAuto    =0,   //�Զ�
		emTPLabelUserDef =1,  //�Զ���
		emTPLabelOff     =2  //�ر�
};

//̨��λ������
enum EmTPLabelPosType
{ 
	emTPTopLeft      = 0,
		emTPTopRight     = 1,
		emTPBottomLeft   = 2,
		emTPBottomRight  = 3
};

//˫����ʾģʽ
enum EmTPDualVideoShowMode
{
    emTPDualVideoOnSigleScreen  =0,//����˫��
		emTPEachVideoOwnScreen      =1,//˫��˫��
		emTPTripleVideoOnSingleScn  =2 //��������
};

//��ʾ����
enum EmTPDisplayRatio
{
	emTPDR4to3      = 0, //4:3
		emTPDR16to9     = 1, //16:9
		emTPDRAuto      = 2, //0:0
};

//FEC�㷨����
enum EmTPFecModeType
{
	emTPFECTYPENONE  =				0x00,
		emTPFECTYPERAID5 =				0x01,
		emTPFECTYPERAID5INTERLEAVE =	0x02,
		emTPFECTYPERAID6 =				0x03,			//������ʱ�������������
};

// �ش�ʱ��ѡ�����������
enum EmTPNetType
{
	emTPInternet = 0,
		emTPSpecial,
		emTPVPN,
};

//������Ƶ�ʵ�
enum EmTPEqualizerRate
{
	emTPRate100,
	emTPRate200,
	emTPRate400,
	emTPRate600,
	emTPRate1k,
	emTPRate3k,
	emTPRate6k,
	emTPRate12k,
	emTPRate14k,
	emTPRate16k,
	emTPRateend
};

enum  EmTPPIPMode
{
	TP_VIDEO_PIPMODE_IDLE = 0,              //����
	TP_VIDEO_PIPMODE_LOOP = 1,                 //�Ի�
	TP_VIDEO_PIPMODE_ONE_LOCAL = 2,             //�����濴����
	TP_VIDEO_PIPMODE_ONE_OTHER = 3,             //�����濴Զ��
	TP_VIDEO_PIPMODE_ONE_AUX_LOCAL = 4,         //�����濴����˫�� 
	TP_VIDEO_PIPMODE_STATIC = 5,               //��̬ͼƬ
};

enum EmTPDVIMode
{
	TP_DVI_MODE_HDMI,
	TP_DVI_MODE_VGA,
	TP_DVI_MODE_DVI,
	TP_DVI_MODE_Ypbpr,
	TP_DVI_MODE_INVALID
};	

//MC ��ģʽ
enum EmTPMCMode
{
	emTPMcSpeech  ,//�ݽ�ģʽ
		emTPMcDiscuss ,//����ģʽ
		emTPMcModeEnd
};

//cns����״̬
enum EmCnsUpdateState
{
	emCnsIdle,
		emCnsDownloading,
		emCnsDownloaded,
		emCnsUpdating,
};

//cn��¼�����������Ľ��
enum EmTPCnLoginUpdateRet
{
	emTPCnLoginUpdateInvalid,
	emTPCnLoginUpdateFail,
	emTPCnLoginUpdateSuccess,
};

//������ʹ�ù������а汾��
enum EmTPFileSrvUsedVersion
{
    emTPFileSrvUsedVersion1     = 1,
		emTPFileSrvUsedVersion2     = 2
};

//�ļ�����
enum EmTPFileSrvFileType
{
    emTPFileSrvFileTypeUnknown      = 0,//δ֪
		emTPFileSrvFileTypeService      = 1,//ҵ���ļ�
		emTPFileSrvFileTypeConsole      = 2//����̨�ļ�
};

enum EmTPOSType
{
	emTPWindows,
	emTPLinux
};

enum EmMPAudEncCodec
{
	emMPAudEncCodec1,
	emMPAudEncCodec2,
	emMPAudEncCodec3,
	emMPAudEncDualCodec,
	emMPAudEncMixCodec,
	emEndMPAudEncCodec
};

enum EmToolType
{
	emMainTerabceTool,//ά������
	emProTestTool  //�������Թ���
};

//add by niulifu
enum EmProducetestType
{
	emProducetestTypeBegin,
	emTestVideoMAIN1InOut,
	emTestVideoMAIN2InOut,
	emTestVideoMAIN3InOut,
	emTestVideoSUB1InMAIN3AUX12Out,
	emTestDualSUB2InTurnHDMIAUX1Out,
	emTestDualAUX1InTurnHDMIAUX1Out,
	emTestDualAUX2InTurnHDMIAUX1Out,
	emTestDualAUX3InTurnHDMIAUX1Out,
	emTestDualAUX4InTurnHDMIAUX2Out,
	emTestDualAUX5InTurnHDMIAUX2Out,
	emTestDualAUX6InTurnHDMIAUX2Out,
	emTestDualSUB2InTurnVGAAUX1Out,
	emTestDualAUX1InTurnVGAAUX1Out,
	emTestDualAUX2InTurnVGAAUX1Out,
	emTestDualAUX3InTurnVGAAUX1Out,
	emTestDualAUX4InTurnVGAAUX2Out,
	emTestDualAUX5InTurnVGAAUX2Out,
	emTestDualAUX6InTurnVGAAUX2Out,
	emTestAudioMIC1InMAIN1Out,
	emTestAudioMIC2InMAIN2Out,
	emTestAudioMIC3InMAIN3Out,
	emTestAudioCANNON1InMAIN1Out,
	emTestAudioCANNON2InMAIN1Out,
	emTestAudioCANNON3InMAIN1Out,
	emTestAudioCANNON4InMAIN2Out,
	emTestAudioCANNON5InMAIN2Out,
	emTestAudioCANNON6InMAIN2Out,
	emTestAudioCANNON7InMAIN3Out,
	emTestAudioCANNON8InMAIN3Out,
	emTestAudioCANNON9InMAIN3Out,
	emTestAudioCANNON10InMAIN2Out,
	emTestAudioAUX1InAUX1Out,
	emTestAudioAUX2InAUX1Out,
	emTestAudioAUX3InAUX1Out,
	emTestAudioAUX4InAUX2Out,
	emTestAudioAUX5InAUX2Out,
	emTestAudioAUX6InAUX2Out,
	emTestUSB1Func,
	emTestUSB2Func,
	emTestRTCFunc,
	emTestLightFunc,
	emTestLAN1Func,
	emTestLAN2Func,
	emTestRS232LoopbackFunc,
	emTestRS422LoopbackFunc,
	emTestRS485LoopbackFunc,
	emTestRS232ANDCOM1LoopbackFunc,
	emTestRS422ANDCOM2LoopbackFunc,
	emTestCOM3ANDCOM4LoopbackFunc,
	emTestCOM5ANDCOM6LoopbackFunc,
	emTestInfraredRecFunc,
	emTestInfraredSendFunc,
	emTestALMLoopBackFunc,
	
	//����Ƶ����һ���Բ������ͬһ������ӿ��벻ͬ����ӿڻ���
    emTestAudioInMain1OutCannon1In,
	emTestAudioInMain1OutCannon2In,
	emTestAudioInMain1OutCannon3In,
	emTestAudioInMain1OutCannon4In,
	emTestAudioInMain1OutCannon5In,
	emTestAudioInMain1OutCannon6In,
	emTestAudioInMain1OutCannon7In,
	emTestAudioInMain1OutCannon8In,
	emTestAudioInMain1OutCannon9In,
	emTestAudioInMain1OutCannon10In, //����10��Ϊһ��������

	//���һ���Բ��������ͬ����ӿ���ͬһ������ӿڻ���
	emTestAudioOutMainL1OutCannon1In,
	emTestAudioOutMainR1OutCannon1In,
	emTestAudioOutMainL2OutCannon1In,
	emTestAudioOutMainR2OutCannon1In,
	emTestAudioOutMainL3OutCannon1In,
	emTestAudioOutMainR3OutCannon1In, //����6��Ϊһ��������
	emProducetestTypeEnd
};


//���¼����ļ������Ľ��
enum EmMdyRecFileRes
{
	em_rec_file_unknow,
	em_rec_file_success,
	em_rec_file_longnamesize,	//�������ļ���
	em_rec_file_inuse,			//�ļ����ڱ�����
	em_rec_file_nameexist,		//�ļ����Ѵ���
	em_rec_file_invalidrecorder,	//��Ч��¼���
	em_rec_file_noregisted,		//δע��
	em_rec_file_invalid_info,	
};


//��ʼ¼��Ľ��
enum EmUseReccorderRes
{
	em_rec_success,				//�ɹ�
	em_rec_invalid,				//��Ч��¼���
	em_rec_unregisted,			//δע��
	em_rec_no_resource,			//�޿�����Դ
	em_rec_invalid_conf,		//��Ч�Ļ���
	em_rec_invalid_format,		//��Ч�ĸ�ʽ
	em_rec_unknow_rectype,		//δ֪��¼������
	em_rec_invalid_mt,			//��Ч�Ļ᳡
	em_rec_recordering,			//����¼��
	em_rec_playing,				//���ڷ���
	em_rec_chair_playing,		//�ϼ����ڽ��з���
	em_rec_server_reject,		//¼���������ܾ�
	em_rec_invalid_rec_info,	//δ�ҵ���Ӧ��¼����Ϣ
	em_rec_invalid_play_info,	//δ�ҵ���Ӧ�Ĳ�����Ϣ
	em_rec_no_in_pause,			//���鲻������ͣ״̬
	em_rec_mt_offline,			//�᳡����
	em_rec_name_hasunderline,	//�����а����»���
	em_rec_longnamesize,		//�������ļ���
	em_rec_fileexist,			//�ļ��Ѿ�����
	em_rec_fileinuse,			//�ļ����ڱ�����
	em_rec_loadlib_failed,		//¼������������lib��ʧ��
	em_rec_setrecmode_failed,	//����¼��ʽʧ��
	em_rec_publicfailed,		//����ʧ��
	em_rec_inrequesting,		//��������
	em_rec_req_failed,			//����ʧ��
	em_rec_norecord,			//δ¼��
	em_rec_file_damange,		//�ļ���
	em_rec_in_stopping,			//¼�����ڱ�ֹͣ
	em_rec_in_pausing,			//¼���ڴ�����ͣ״̬
	em_rec_no_in_working,		//�����ڹ���״̬
	em_rec_invalid_channel,		//��Ч��ͨ��
	em_rec_unmatch_format,		//��ʽδƥ��
	em_rec_unknow_reason,				//δ֪����
};

//¼������
enum EmRecorderType
{
	em_rec_recorder_unknow,
	em_rec_recorder_conf,	//¼�ƻ���
	em_rec_recorder_mt,		//¼���ն�
};

//¼��״̬
enum EmConfRecState
{
	em_rec_unknow,
	em_rec_init,		//��ʼ��
	em_rec_working,		//����¼��
	em_rec_pause,		//������ͣ״̬
	em_rec_finish,		//���
};

//End Add


//add
//add
enum EmTpProfile
{
	emTpProfileBaseline = 64,
	emTpProfileMain = 32,
	emTpProfileExtend = 16,
	emTpProfileHigh = 8
};

enum EmTPHandleCfgType
{
	emTPShowCfg, //��ʾ������Ϣ
	emTPSetCfg,  //����������Ϣ
	emTPPostCfg  //����������Ϣ
};

//���������
enum EmTpCodecType
{
	emTpVEnc = 0,
		emTpVDec,
		emTpAEnc,
		emTpADec,
};

//ά������״̬
enum EmToolState
{
	em_Tool_IDLE = 0,
	em_Tool_READY
};

//��Ƶ����ģʽ
enum EmTPAudPlayMode
{
    emTP_PLAY_FULL = 0,     //3·����
    emTP_PLAY_SINGLE        //��·����	
};

//˫����Ƶ����˿�ģʽ
enum EmTPAudDualInMode
{
    emTP_AUD_DUAL_AUTO = 0,     //�Զ�     
	emTP_AUD_DUAL_HDMI,        //����hdmi
    emTP_AUD_DUAL_LINEIN,      //����RCA��TRS
};

enum EmTPDualType
{
	emTP_TPad_DUAL_VEDIO = 0,  // pc daul vedio from TPad
	emTP_DV_DUAL_VEDIO,   
	emTP_NONE_DUAL_VEDIO
};


enum EmTPDsNode
{
	emTp_Ds = 0,
	emTp_Node = 1
};

enum EMScreenLooked
{
	emScreenInvalid	=	0,		//��Ч��Ļ
	emScreenSelf	=	1,		//����
	emScreenSpeaker =	2,		//��������
	emScreenPoll	=	3,		//����ѯ
	emScreenView	=   4,		//ѡ��
	emScreenDiscard	=   5,		//������ͼ��
	emScreenRecPlay =   6,		//������
		
	emScreenLookedEnd = 7,		//��ϯ��״̬��������Ŀ
};

//////////////////////////////////////////////////////////////////////////
//mpu2tp

//����ϳɷ��
enum EmUmsVmpStyle
{
	em_ums_vmp_invalid,
	em_ums_vmp_one,
	em_ums_vmp_two_pic,		//һ��һС
	em_ums_vmp_three_pic,	//һ����С
	em_ums_vmp_four_pic,
	em_ums_vmp_five_pic,
	em_ums_vmp_six_pic,
	em_ums_vmp_seven_pic,       // 7   1��6С��С�����Դ�
	em_ums_vmp_seven_pic_380,  // 8    1��6С��С������С��
	em_ums_vmp_eight_pic,   // 9
	em_ums_vmp_nine_pic,  // 10
	em_ums_vmp_ten_pic,  // 11
};

//����ģʽ
enum EmVmpEncMode
{
	em_ums_vmp_enc_none = 0, //������
	em_ums_vmp_enc_des = 1, //des����
	em_ums_vmp_enc_aes = 2, //aes����
};

//����ͨ����ʾ����
enum EmVmpShowMode
{
	ums_vmp_black_mode = 0,			//VMP����ͨ����ʾΪ��ɫ
	ums_vmp_lastframe_mode = 1,		// VMP����ͨ����ʾ���һ֡
	ums_vmp_defaultpic_mode = 2,	// VMP����ͨ����ʾĬ��ͼƬ��480*272 
	ums_vmp_userdefpic_mode = 3,	// VMP����ͨ����ʾ�û��Զ���ͼƬ
};

//�����ϳɽ��
enum EmVmpRes
{
	em_ums_vmp_success,			//�ɹ�
	em_ums_vmp_failed,			//ʧ��
	em_ums_vmp_invalid_chan,	//��Ч�ĺϳ�ͨ��
	em_ums_vmp_chan_working,	//ͨ������ʹ����
	em_ums_vmp_invalid_param,	//��Ч�Ĳ���
	em_ums_vmp_set_param_failed,//���ò���ʧ��
};

enum EmAudPlayMode
{
	emAudMode_Invalid = 0,
	emAudMode_Synchronous = 1, //ͬ������
	emAudMode_NoSynchronous = 2, //��ͬ������
};

enum EmResetAudMode
{
	emResetAudMode_Invalid = 0,
	emResetAudMode_Start = 1, //�������ò���ģʽ
	emResetAudMode_End = 2, //�Ѿ��������ò���ģʽ
};

enum EmCheckAudPak
{
	emCheckAudPak_Invalid = 0,
	emCheckAudPak_End = 1, //������Ƶ�����
	emCheckAudPak_Start = 2, //��ʼ��Ƶ�����
};

enum EmViewEpType
{
	EmEpType_Invalid = 0,
	EmEpType_Ter,  // �᳡
	EmEpType_Eqp,  // �ϳ���
};
enum EmViewRetReason
{
	EmViewRetReason_Success,
	EmViewRetReason_Selected,//ѡ��ʱ �Ѿ�ѡ����
	EmViewRetReason_UnSelected,//ȡ��ѡ��ʱ δѡ��
	EmViewRetReason_EpNotLine,//ѡ���᳡������
	EmViewRetReason_DstEpNotLine,//��ѡ���᳡������
	EmViewRetReason_DstEqpNoExists,//��ѡ�����費����
	EmViewRetReason_SelFull,//ѡ����Դ��
	EmViewRetReason_EpTypeError,//��ѡ��Ŀ�����ʹ����նˡ�����
	EmViewRetReason_SelDstNoVid,//��ѡ��Ŀ������ƵԴ
	EmViewRetReason_SelNoVid,//ѡ���᳡����Ƶ����
	EmViewRetReason_SelDstNotLvl,//ѡ���᳡�ͱ�ѡ���᳡����һ��ͬһ����
	EmViewRetReason_NoBasRes,//��������Դ
	EmViewRetReason_InValidEp,//ѡ���᳡��Ч
	EmViewRetReason_NoBwRes,  // ѡ��������
//	EmViewRetReason_UnKnow,
};

enum EmUIType
{
	EmUI_CNC = 1,
	EmUI_UMC = 2,
	EmUI_Tools = 4
};

enum EmGetVidRes
{
	em_GetVid_Success,
	em_GetVid_Invalid_Param,	//
	em_GetVid_No_BandWidth,
	em_GetVid_No_AddrResource,
	em_GetVide_No_BasResource,
	em_GitVid_No_Resource,	//����Դ
	em_GetVid_DownUmNoVmp,
	em_GetVid_DownUmVmpDisconnect,
};

enum EmBrdVmpRet
{
	EmBrdVmpRet_Succes,
	EmBrdVmpRet_Busy,   // �ϳ����Ѵ���busy״̬ 
	EmBrdVmpRet_NoExist,  // �ϳ���������
	EmBrdVmpRet_Fail,   // δ֪ԭ�� 
	EmBrdVmpRet_DownUmsFail,  // �¼����ܹ㲥�ϳ�
};

enum EmBrdVmpStat
{
	EmBrdVmpStat_Invalid,
	EmBrdVmpStat_Idle,
	EmBrdVmpStat_Normal,
	EmBrdVmpStat_Brd,
	EmBrdVmpStat_Error,
};

enum EmRervesVmpRet
{
	EmRervesVmpRet_Success,
	EmRervesVmpRet_DisCnnt,
	EmRervesVmpRet_ResFull,
	EmRervesVmpRet_Busy,
	EmRervesVmpRet_NoExist,
	EmRervesVmpRet_unKnow
};

enum EmCnmpLogType
{
	EmCnmpLogType_Off = 0,
	EmCnmpLogType_All = 1,
	EmCnmpLogType_VSend = 2,
	EmCnmpLogType_VRcv = 3,
	EmCnmpLogType_ASend = 4,
	EmCnmpLogType_ARcv = 5,
	EmCnmpLogType_KeyFrame = 6,
};

enum EmCnmpLogCt
{	
	EmCnmpLogCt_First = 0,
	EmCnmpLogCt_Second = 1,
	EmCnmpLogCt_Third = 2,
	EmCnmpLogCt_Fourth = 3,
	EmCnmpLogCt_Fifth = 4,
	EmCnmpLogCt_All = 5,
};

enum EmAudAecType
{
	EmTpAec,
	EmTpAns,
	EmTpAgc,
};

enum EmGetVidType
{
	em_GetVid_Invalid,
	em_GetVid_View,		//ѡ�������������ȷ�ʽ������Ŀ�Ļ᳡�ķ�����ϯ������Ӧ
	em_GetVid_Poll,		//��ѵ
	em_GetVid_Vmp,		//����ϳ�
	em_GetVid_Hdu,		//����ǰ
	em_GetVid_Dis,		//����
	em_GetVid_ViewEp,	//�᳡ѡ�������������ȷ�ʽ������Ŀ�Ļ᳡��ĳ����ϯ���̶�
	em_GetVid_OnlyAud,  // ֻ����Ƶ
	em_GetVid_SdkGetAudVid,	// sdk���ڻ����е��᳡������
};

//ͼ�������������
enum EmVidEncResizeMode
{
	EmTpBlackSide = 0,//�Ӻڱߵȱ�����
	EmTpCuttingEdge = 1,//�ñߵȱ�����
	EmTpNonGeometricDrawing = 2,//���ȱ�����

};

enum EmTpVendorID
{
	EmTp_vendor_MICROSOFT_NETMEETING = 1,
	EmTp_vendor_KEDA,
	EmTp_vendor_KEDA_IPC,
	EmTp_vendor_HUAWEI,
	EmTp_vendor_POLYCOM,
	EmTp_vendor_POLYCOM_MCU,
	EmTp_vendor_TANDBERG,
	EmTp_vendor_RADVISION,
	EmTp_vendor_VCON,
	EmTp_vendor_SONY,
	EmTp_vendor_VTEL,
	EmTp_vendor_ZTE,
	EmTp_vendor_ZTE_MCU,
	EmTp_vendor_CODIAN,
	EmTp_vendor_AETHRA,
	EmTp_vendor_CHAORAN,
	EmTp_vendor_UNKNOWN,
	EmTp_vendor_END
};

enum EMScreenObj
{
	emObjSelf,		//��Ч��Ļ
	emObjSpeaker,	//��������
	emObjChair,		//����ϯ
	emObjPoll,		//����ѯ
	emObjView,		//ѡ��
	emObjDiscard,	//������ͼ��
	emObjVmpBrd,	//�㲥�ϳ�	
	emObjLookedEnd,	//��ϯ��״̬��������Ŀ
};

enum EmTpBannerTransparency //���͸����
{
	EmTpFullTransparent = 0, //ȫ͸��
		EmTpTranslucent = 1, //��͸��
		EmTpOpaque = 2, //��͸��
};

enum EmTpBannerType //������
{
	EmTpBannerType0 = 0, 
		EmTpBannerType1 = 1,
		EmTpBannerType2 = 2,
};

enum EmTpLogoType //̨����
{
	EmTpLogoType_UpperLeft = 0, //����
		EmTpLogoType_UpperMid = 1, //����
		EmTpLogoType_UpperRight = 2, //����
		EmTpLogoType_LowerLeft = 3, //����
		EmTpLogoType_LowerMid = 4, //����
		EmTpLogoType_LowerRight = 5, //����
};

enum EmTpSnapShotType
{	
	EmTpSnatShot_ThreeVideo = 0, //3·����Ƶ����
		EmTpSnatShot_PanoramicCamera = 1, //ȫ�����������
};

enum EmTpCtrlMode 
{
	emTpModeInvalid = -1,
	emTpModeCommand,
	emTpModeRequest,
};

enum EmDiscussOprRes
{// ��ӻ᳡�����۵Ľ����ע����������ɾ���᳡��ֻ�ظ�Successed����OtherFail
	em_Disucss_Opr_Successed = 0,
	
		em_Discuss_Invalid_Ep = 1,  // ��Ч�᳡
		em_Discuss_Screen_Full, // ��������
		em_Disccuss_GetVid_Error,  // ����������
		em_Discuss_No_BandWith, // ������������
		em_Discuss_AssignAudChan_Error,   // ���¼��᳡�����´���Ƶͨ��ʧ��
		em_Discuss_No_MixChan,   // ����ͨ������
		em_Discuss_OtherFail, // 

	em_Disccuss_Opr_End = 1000,
};

enum EmDiscussRspRet
{// �������۵Ľ����ע���ر����ۣ�ֻ�ظ�Ok����OtherFail
	em_DiscussOprRsp_Ok = 0,
		
		em_Start_AssginVmpFail = 1,  // �ϳ���Դ���㣬��������ʧ��
		em_Start_AssignMixFail,  // ������Դ���㣬��������ʧ��
		em_Start_AssignBasFail,  // ������Դ���㣬��������ʧ��
		em_Start_OtherFail,      // 
         
		                            //Ϊ����B4 �ں������
        em_Start_RollCall_Mode,     //����ģʽ����������ʧ��
        em_Start_ConfAudMix_Mode,   //�������ģʽ����������ʧ��

		
	em_DiscussOprRsp_End = 1000,	
};

enum EmSpeakerVmpType
{
	em_Vmp_Invalid = 0,
	em_Chair_In_Vmp,
	em_Speaker_In_Vmp,
};

enum EmRollCallRspRet
{
	em_RollCallOprRsp_Ok = 0,

	em_StartRollCall_begin = 100,    //�����رյ�����ʼ��Ϣ����Ϣ�ֶη���������
	em_StartRollCall_AssignMixFail,  // ������Դ���㣬���ܿ�������
	em_StartRollCall_DisMode,        // ��ǰΪ����ģʽ�� ���ܿ�������
    em_StartRollCall_ConfAudMixMode, // ��ǰΪ�������ģʽ�� ���ܿ�������
	em_StartRollCall_AlreadyStart,   // �ظ�������������ǰ���ǵ���ģʽ
	em_StartRollCall_AssignAddrFail, // ��������ʧ�ܣ������ַ���� ���ܿ�������
	em_StartRollCall_NotTopUms,      // ��ǰ�����Ĳ��Ƕ���UMS��������Ч
	em_StartRollCall_CreateChanFail, // �ϵ���������Ƶ��PUT��������Ƶʧ�� ���ܿ�������
	em_StartRollCall_OtherFail,      // ��ֹ���� 

	em_UpdateRollCalList_begin = 200,  //�����б���ʼ��Ϣ����Ϣ�ֶη���������
	em_UpdateRollCalList_ListFull,   // ���µ����б�����б���
	em_UpdateRollCalList_NotTopUms,  // ���µ����б���ǰ�����Ĳ��Ƕ���UMS��������Ч
	em_UpdateRollCalList_InvalidEp,  // ���µ����б�, ��Ч�᳡
	em_UpdateRollCalList_EpoffLine,  // ���µ����б�, �᳡������
	em_UpdateRollCalList_Fail,       // ���µ����б����

    em_RollCallNextEp_begin = 300,   // ������һ����ʼ��Ϣ, ��Ϣ�ֶη���������
	em_RollCallNextEp_NotStart,      // ������һ��ʱ ��δ��������ģʽ��������Ч
    em_RollCallNextEp_NotTopUms,     // ������һ��ʱ ��ǰ�����Ĳ��Ƕ���UMS��������Ч
    em_RollCallNextEp_CallerChg,     // ������һ��ʱ �����߷����˱仯 ������Ч
    em_RollCallNextEp_EpError,       // ������һ��ʱ �᳡����
	em_RollCallNextEp_CreateChanFail, // �ϵ���������Ƶ��PUT��������Ƶʧ�� �˳�����
    em_RollCallNextEp_OtherFail,
    
    /////////////////notify////////////////////
	em_RollcallNotify_begin = 400,   // notify��ʼ��Ϣ������״̬���б�����Ϣ�ֶη��������� 
	em_Error_StopRollCall,           // ���� 
	em_RollCallMixer_Error,          // ������������
	em_RollCaller_OffLine,           // �����ߵ���
	em_RollCallTarget_OffLine,       // �����ߵ���
	em_CallTarget_ReConnect_Success, //��ǰ�����ߵ��ߺ��������߳ɹ�
	em_Chair_ReConnect_notice,       //��ϯ���ߺ��������ߣ�����״̬ͬ��

	em_RollCallOprRsp_End = 1000,	
};


enum EmRollCallPresentState
{
	em_RollCallPresentState_Ok  = 0,       // �ѵ����������ɹ�
	em_RollCallPresentState_Target,        // ��ǰ������,���ڱ�������
	em_RollCallPresentState_Absent,        // δ����ȱϯ
	em_RollCallPresentState_OffLine,       // ������
	em_RollCallPresentState_PendingTarget, // ��δ����
    em_RollCallPresentState_OtherFail,     // ����
};



enum EMRollCallNotyToLowUmsType
{
	em_RollCallNotyUpNodeInfo,
	em_RollCallNotyChgCallerSteat,
};

// add for umsaudmix
enum EmUmsAudMixMode
{
	em_umsaudmixmode_idle = 0, // �ǻ������״̬

	em_umsaudmixmode_smart, // ���ܻ���
	em_umsaudmixmode_custom, // ���ƻ���
};

enum EmUmsAudMixListOpr
{
	em_umsaudmixlistopr_add,  
	em_umsaudmixlistopr_del,  

	em_umsaudmixlistopr_unkown = 100,
};

enum EmUmsAudMixRes
{
    //���о�ΪInd

	em_umsaudmixres_sucess,              // �ɹ������¾�Ϊ��������

	em_umsaudmixres_listopr_begin = 100,
	em_umsaudmixres_add_invalidep,       // ��Ч�᳡
	em_umsaudmixres_add_getaudfail,      // �ϵ��᳡��Ƶʧ��  
	em_umsaudmixres_add_assignaudfail,   // �����������᳡N-1 ��Ƶͨ��ʧ�� 
	em_umsaudmixres_add_mixchanfull,     // ����ͨ������
	em_umsaudmixres_add_repeatadd,       // �Ѿ���ͨ����

	em_umsaudmixres_del_notfind,         // Ҫɾ������ͨ�����ڻ���ͨ����

	em_umsaudmixres_modeopr_begin = 200,

	em_umsaudmixres_start_nomix,     // ����������û�л�����, �������������������
	em_umsaudmixres_start_novalidep, // ��������������Ч�����᳡������������������ 
	em_umsaudmixres_samemode,        // �������� ģʽδ�ı䣬������Ч
	em_umsaudmixres_unauthorized,    // �������� û��Ȩ�ޣ�������Ч, �ϼ�ums����ϯ���ܲ���
	em_umsaudmixres_dismode,        // �������� ģʽ��������ģʽ  ����������ܿ����ɹ�
	em_umsaudmixres_rollcallmode,   // �������� ģʽ���󣬵���ģʽ������������ܿ����ɹ�

	
	em_umsaudmixres_unkown = 300,   //δ֪����
}; 

// umsmcu����
enum EmUmsMcuRet
{
    em_umsmcuret_Ok = 0, //request��Ϣ�ѵõ���ȷ�Ĵ���
	em_umsmcuret_Error,//һ���Դ��󣬴���ԭ����
	em_umsmcuret_PartNotFound,//�������в�����������Ϣ��PIDָʾ�Ļ����Ա
	em_umsmcuret_ConfNotFound,//������Ϣ��confIDָ���Ļ����鲻����
	em_umsmcuret_ChannelNotFound,//�����Ա����Ƶ/��Ƶͨ��������
	em_umsmcuret_NoPermission,//�û���Ȩ�޲�����������Ϣ��������
	em_umsmcuret_XmlBadParams,//������Ϣ���ֶ��������ֶε�ֵ����/��Χ����
	em_umsmcuret_TimeOut,//������Ϣ����ʱ
	em_umsmcuret_NoResources,//mcuû���㹻����Դ������������Ϣ������Ƶ��Դ��Ҫ��
	em_umsmcuret_Invalid//������Ч,���ᱻ����
};



enum EmUmsGetConfBrdVidAudRet
{
	em_GetConfBrdVidAudRet_success = 0,

	em_GetConfBrdVidAudRet_idleconf,
	em_GetConfBrdVidAudRet_full,
	em_GetConfBrdVidAudRet_rereq,
	em_GetConfBrdVidAudRet_userExist,
	
	em_GetConfBrdVidAudRet_unkown = 100,
};


enum EmUmsReleaseConfBrdVidAudRet
{
	em_ReleaseConfBrdVidAudRet_success = 0,
	em_ReleaseConfBrdVidAudRet_idleconf,
	em_ReleaseConfBrdVidAudRet_unkown = 100,
};

enum EmUmsGetVmpVidRet
{
	em_GetVmpVidRet_success = 0,
		
	em_GetVmpVidRet_idleconf,
	em_GetVmpVidRet_vmpInfofull,
	em_GetVmpVidRet_assvmpfail,
	em_GetVmpVidRet_vaildformat,
	em_GetVmpVidRet_vmpUserExist,
		
	em_GetVmpVidRet_unkown = 100,
};

enum EmUmsReleaseVmpVidRet
{
	em_ReleaseVmpVidRet_success = 0,
		
	em_ReleaseVmpVidRet_idleconf,
	em_ReleaseVmpVidRet_idlevmpinfo,
		
	em_ReleaseVmpVidRet_unkown = 100,
};

enum EmUmsVmpVidRes
{
	em_VmpVidRes_success = 0,

	em_VmpVidRes_notonline,
		
	em_VmpVidRes_unkown = 100,
};

enum EmTPQTReason
{
	emTPQtRetReason_Idle = 0, 
	emTPQtRetReason_Success,
	emTPQtRetReason_Local,			//����ԭ�� 
	emTPQtRetReason_DisConnect,		//���� 
	emTPQtRetReason_ShakeFail,		//����ʧ��
	emTPQtRetReason_ReqFail,		//����ʧ�� 
	emTPQtRetReason_GetFail,		//��ȡʧ��
	emTPQtRetReason_PeerUnreach,	//���ɴ� 
	emTPQtRetReason_PeerGetFail,	//��ȡʧ�� 
	emTPQtRetReason_ClearFail,		//���ʧ�� 
	emTPQtRetReason_TimeOut,		//��ʱ
	emTPQtRetReason_NotMatch,		//��Կ��ƥ�� 
};

//qt��ԿƵ��
enum EmTPConfEncFrequency
{
	emTPConfEncFrequencyEverySeconds = 0,	//һ��һ��
	emTPConfEncFrequencyEveryMinute,	//һ��һ��
	emTPConfEncFrequencyEveryConf,		//һ��һ��
};


enum EmQueryAliasRes
{
	emQuerySuccess,
	emQueryFailed,
};

// Զң/��Դ ��������
enum EmUmsFeccActType
{
	em_Fecc_Unknown = 0,
		em_Fecc_CamerStart,
		em_Fecc_CamerStop,
		em_Fecc_CamerAudoFocus,
		em_Fecc_SavePos,
		em_Fecc_LoadPos,
		em_Fecc_SwitchVideo,
		em_Fecc_SelectVideo,
		
};

enum EmUmsCamerReqType
{
	em_Camer_Unknown = 0,
		em_Camer_Up,
		em_Camer_Down,
		em_Camer_Left,
		em_Camer_Right,
		em_Camer_UpLeft,
		em_Camer_UpRight,
		em_Camer_DownLeft,
		em_Camer_DownRight,
		em_Camer_ZoomIN,
		em_Camer_ZoomOut,
		em_Camer_AudoFocus,
		em_Camer_FocusIn,
		em_Camer_FocusOut,
		em_Camer_BrightUp,
		em_Camer_BrightDown,
};

enum EmGetEpSreenStreamRet
{
	em_GetEpSreenStreamRet_success = 0,
		em_GetEpSreenStreamRet_userExit,
		em_GetEpSreenStreamRet_idleconf,
		em_GetEpSreenStreamRet_idleEpScreen,
		em_GetEpSreenStreamRet_noStream,
		em_GetEpSreenStreamRet_full,
		
		em_GetEpSreenStreamRet_unkown = 100,
};

enum EmReleaseEpSreenStreamRet
{
	em_ReleaseEpSreenStreamRet_success = 0,
		
		em_ReleaseEpSreenStreamRet_idleconf,
		em_ReleaseEpSreenStreamRet_idleIndex,
		
		em_ReleaseEpSreenStreamRet_unkown = 100,
};

//��Կ�����Ը���ʱ��
enum EmUpdatePwdTimer
{
	em_One_Month = 0 ,
	em_Two_Month,
	em_Three_Month,
};

//���忪������
enum EmBoardSwitchType
{
	em_BoardSwitch_telnet = 0,
	em_BoardSwitch_ftp,
    em_BoardSwitch_all,

	em_BoardSwitch_end = 50,
};

//���忪�ؽ��
enum EmBoardSwitchRes
{
	em_BoardSwitchRes_ok = 0,
	em_BoardSwitchRes_offline,
	em_BoardSwitchRes_notfind,
	em_BoardSwitchRes_brderror,
	em_BoardSwitchRes_switcherr,

	em_BoardSwitchRes_end = 50,
};


//ѡ��᳡����Э�����ͽ��
enum EmAddTempConfExRes
{
	em_Addex_ok = 0,
	em_TempID_error,
	em_EplistNum_error,
	em_Eplist_error,
	em_CallProtocol_error,

	em_AddTempEx_end = 50,
};


//��������
enum EMXmpuEqpType
{
	em_Xmpu_unknow,
	em_XmpuVmp_Eqp,
	em_XmpuAudBas_Eqp,
	em_XmpuVidBas_Eqp,
	em_XmpuMix_Eqp,
	em_XmpuMix8_Eqp,
};

// xmpuͬ����������
enum EMXmpuSynType
{
	em_Xmpu_Mix_SpeakerEp,
	em_Xmpu_Mix_OtherThreeEp,
	em_Xmpu_AudBas_SpeakerEp,
	em_Xmpu_AudBas_ChairEp,
	em_Xmpu_SynIndex_End,
};

enum EmSwitchType
{
	emInvalidSwap = 0,
	emRtpSwap = 1,
	emRtcpSwap = 2,
};

enum EmEthInfoType
{
	em_eth0_type = 1,
	em_eth0_virtual_type,

	em_eth1_type = 10,
	em_eth1_virtual_type,
};

#endif // _h_tpcommontype_h__